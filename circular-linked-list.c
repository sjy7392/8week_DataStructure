#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf("[----- [Son Ji Yeon] [2020039104] -----]\n");	
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	//h의 오른쪽 링크를 시작으로 리스트 순
	listNode* p = h->rlink;
	listNode* prev = NULL;

	//리스트 순회하며 각 노드 해제
	while(p!=h && p!=NULL){
		prev=p;
		p=p->rlink;
		free(prev);
	}
	//헤드노드 해제
	free(h);

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	//p에 값이 없거나 h에 도달 직전까지 key 값 출력
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);

	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	//p에 값이 없거나 h에 도달 직전까지 key 값 주소, llink값 주소, rlink값 주소 출력
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	//새 노드 생성 후 key 설정
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key=key;

	//리스트의 마지막 위치를 찾음
	listNode* p=h;
	while(p->rlink != h){
		p=p->rlink;
	}

	//마지막에 새로운 노드 추가
	//새로운 노드의 왼쪽 링크는 이전 노드, 오른쪽 링크는 헤드를 가리키게 함
	p->rlink=node;
	node->llink=p;
	node->rlink=h;
	h->llink=node; //헤드노드의 왼쪽 링크를 노드로 지정

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	//헤드노드를 가리키는 포인터 p 지정
	listNode* p=h;

	//마지막 이전 노드 찾음
	while(p->rlink->rlink!=h){
		p=p->rlink;
	}
	//마지막 노드 지정 후, 마지막 이전 노드의 오른쪽 링크를 헤드 노드로 변경
	listNode* lastNode=p->rlink;
	p->rlink=h;
	p->rlink=h;
	h->llink=p;
	free(lastNode); //마지막 노드 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	//새 노드 생성 후 key 설정
	listNode* node=(listNode*)malloc(sizeof(listNode));
	node->key=key;
	//새 노드의 링크 설정한 후 오른쪽 링크는 첫번째 노드, 왼쪽 링크는 헤드 노드를 가리키게 함
	node->rlink=h->rlink;
	node->llink=h;
	h->rlink->llink=node; //첫번째 노드의 왼쪽 링크 업데이트
	h->rlink=node; //헤드 노드의 오른쪽 링크 새 노드로 변경

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	//첫번째 노드 저장 후, 헤드 노드의 오른쪽 링크를 두번째 노드로 변경
	listNode* firstNode = h->rlink;
	h->rlink = firstNode->rlink;
	firstNode->rlink->llink=h; //두번째 노드의 왼쪽 링크를 헤드 노드로 변경
	free(firstNode); //첫번째 노드 메모리 해제

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	//p는 현재 노드, q는 이전 노드, r은 이전의 이전 노드
	listNode* p=h->rlink;
	listNode* q=NULL;
	listNode* r=NULL;
	//p가 h에 도달할 때까지 리스트를 순회하며 링크 방향 변경
	while(p!=h){
		r=q;
		q=p;
		p=p->rlink;
		q->rlink=r;
		q->llink=p;
	}
	h->rlink=q; //헤드 노드의 오른쪽 링크를 마지막 노드로 변경
	h->llink=p; //헤드 노드의 왼쪽 링크를 첫 번째 노드로 변경

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	//새 노드 생성 후 key 설정
    listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key=key;
	//헤드 노드에서 시작해 오른쪽으로 이동하며 key보다 큰 값을 찾음
	listNode* p=h;
	while(p->rlink!=h&&p->rlink->key<key){
		p=p->rlink;
	}
	//찾은 노드 앞에 새 노드 삽입한 후 새 노드의 오른쪽 링크는 찾은 노드, 왼쪽 링크는 찾은 노드의 이전 노드 가리키게 
	node->rlink=p->rlink;
	node->llink=p;
	p->rlink->llink=node; //찾은 노드의 왼쪽 링크 새 노드로 변경
	p->rlink=node; //이전 노드의 오른쪽 링크 새 노드로 변경
	
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	//현재 노드를 가리키는 포인터 p 설정
	listNode* p = h;
	// p의 오른쪽 링크가 헤드 노드를 가리키지 않고, p의 오른쪽 노드의 키가 찾는 키와 같지 않을 때까지 반복
    while(p->rlink != h && p->rlink->key != key) {
        p = p->rlink;
    }
	// p의 오른쪽 링크가 헤드 노드가 아닌 경우에 실행
    if (p->rlink != h) {
        listNode* toDelete = p->rlink; // 삭제할 노드를 가리키는 포인터 toDelete 설정
        p->rlink = toDelete->rlink; // 이전 노드(p)의 오른쪽 링크를 삭제할 노드의 다음 노드로 연결
        toDelete->rlink->llink = p; // 삭제할 노드의 다음 노드의 왼쪽 링크를 이전 노드(p)로 연결
        free(toDelete); // 삭제할 노드를 해제
    }
	return 0;
}