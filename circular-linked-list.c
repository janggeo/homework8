/*
	[2021076029] [장정환]
	수정사항
	1)main함수에서 헤더노드를 동적할당하여 insertNode함수를 바로 사용하도록 수정
	2)오름차순으로 정렬해주는 함수 추가
	3)
*/

#include<stdio.h>
#include<stdlib.h>	//malloc, free

typedef struct Node{	//노드 구조체
	int key;
	struct Node* llink;
	struct Node* rlink;
}listNode;

/* 함수 리스트 */
int initialize(listNode** h);			//리스트를 초기화해주는 함수

int freeList(listNode* h);				//리스트의 노드 동적할당 해제
int insertLast(listNode* h, int key);	//리스트 마지막에 노드 추가
int deleteLast(listNode* h);			//리스트 마지막 노드 제거
int insertFirst(listNode* h, int key);	//리스트 처음에 노드추가
int deleteFirst(listNode* h);			//리스트 처음 노드 제거
int invertList(listNode* h);			//리스트 역순으로 배열
int insertNode(listNode* h, int key);	//노드를 오름차순으로 추가
int deleteNode(listNode* h, int key);	//입력받은 key 값을 가지는 노드 제거

void printList(listNode* h);			//리스트 print
listNode* SortList(listNode* h);				//오름차순으로 정렬	

int main(void){
	printf("[----- [장정환]  [2021076029] -----]");
	char command;	//메뉴선택 
	int key;		//새로운 노드에 추가할 key값
	
	//헤더노드를 가리킬 headnode 동적할당 및 초기화
	listNode* headnode=NULL;
	headnode=(listNode*)malloc(sizeof(listNode));
	headnode->rlink=headnode;
	headnode->llink=headnode;
	headnode->key=-9999;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf(" Sort List	   = s\n");
		printf("----------------------------------------------------------------\n");

		printf("command = ");
		scanf("%c",&command);	//수행하고자 하는 기능 입력

		switch(command){
			case 'z': case 'Z':
				initialize(&headnode);	//리스트 초기화
				break;

			case 'i': case 'I':
				printf("Your key = ");
				scanf("%d", &key);
				insertNode(headnode,key);	//입력받은 key값을 가지는 노드  리스트에 추가
				break;

			case 'n': case 'N':
				printf("Your key = ");
				scanf("%d", &key);
				insertLast(headnode,key);	//리스트 마지막에 노드추가
				break;

			case 'f': case 'F':
				printf("Your key = ");
				scanf("%d", &key);
				insertFirst(headnode,key);	//리스트 처음에 노드추가
				break;

			case 'd': case 'D':
				printf("Your key = ");
				scanf("%d", &key);
				deleteNode(headnode,key);	//입력받은 key 값을 가지는 노드 해제
				break;

			case 'e': case'E':
				deleteLast(headnode);		//리스트 마지막 노드 제거
				break;
			
			case 't': case'T':
				deleteFirst(headnode);		//리스트 처음 노드 제거
				break;

			case 'r': case 'R':
				invertList(headnode);		//리스트를  역순으로
				break;
			
			case 'p': case 'P':
				printList(headnode);		//리스트 출력
				break;
			case 's': case 'S':
				headnode=SortList(headnode);
				break;

			case 'q': case 'Q':
				freeList(headnode);			//리스트 해제
				break;
			default:
				printf("\n		>>>> 	Concentration!!		<<<<	\n");
				break;
			}
			getchar();	//버퍼비우기
	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(listNode** h){
	//리스트에 노드가 있을경우(빈 리스트가 아닐경우)
	if(*h !=NULL){
		freeList(*h); 
	}
	//동적할당 및 초기화
	*h=(listNode*)malloc(sizeof(listNode));
	(*h)->llink=NULL;
	(*h)->rlink=NULL;
	(*h)->key=-9999;

	return 1;
}

int freeList(listNode* h){
	//헤더노드만 존재할 경우
	if(h->rlink==h){
		free(h);	//헤더 free
		return 1;
	}
	//헤더포인터는 옮기면 안되기 때문에 노드를 가리킬 포인터 선언
	listNode* prev = NULL;
	listNode* p = h->rlink;
	//헤더포인터 제외 나머지 해제
	while(p != NULL && p != h){
		prev = p;
		p=p->rlink;
		free(prev);
	}
	//헤더 포인터 해제
	free(h);
	return 0;
}

int insertLast(listNode* h, int key){
	//헤더 노드가 동적할당 되지 않았을 경우 리턴-1
	if (h ==NULL) return -1;

	//새로 추가할 노드 동적할당 및 초기화
	listNode* Node = (listNode*)malloc(sizeof(listNode));
	Node->key = key;
	Node->llink = NULL;
	Node->rlink = NULL;

	//헤더노드만 있을경우
	if(h->rlink == h){
		/*헤더 노드 좌우링크를 새로운 노드와 연결
		  새로운 노드 좌우링크를 헤더 노드와 연결*/
		h->rlink=Node;
		Node->llink=h;
		Node->rlink=h;
		h->llink=Node;
	}
	else{
		/*헤더노드 왼쪽노드(즉, 기존 마지막 노드)를 새로운 노드와 연결
		  헤더노드 왼쪽 링크를 새로운 노드와 연결
		  새로운 노드를 헤더노드 왼쪽노드, 헤더노드와 연결*/
		h->llink->rlink=Node;
		Node->llink=h->llink;
		h->llink=Node;
		Node->rlink=h;
	}
	
	return 1;
}
int deleteLast(listNode* h){
	//헤더노드만 존재할 경우 or 헤더노드도 없을 경우
	if(h->rlink == h || h == NULL){
		printf("nothing to delte.\n");
		return 1;
	}
	else{/*헤더노드왼쪽노드(마지막 노드)의 왼쪽 노드와 헤더노드를 연결
			헤더노드 왼쪽 노드는 해제*/
		listNode* nodetoremove=h->llink;	//해제할 노드 저장
		nodetoremove->llink->rlink=h;
		h->llink=nodetoremove->llink;
		free(nodetoremove);
	}
	return 1;
}
int insertFirst(listNode* h, int key){
	//새로운 노드 동적할당 및 초기화
	listNode* Node = (listNode*)malloc(sizeof(listNode));
	Node->key=key;
	Node->llink=NULL;
	Node->rlink=NULL;

	//새로운 노드를 리스트 제일 앞에 추가
	//기존 리스트 노드 개수 상관없이 추가 가능
	Node->llink=h;
	Node->rlink=h->rlink;
	h->rlink->llink=Node;
	h->rlink=Node;

	return 1;
}
int deleteFirst(listNode* h){
	if(h->rlink == h || h == NULL){	//헤더 노드만 있을경우 or 헤더노드도 없을경우
		printf("nothing to delete..\n");	//오류메시지 출력
		return 0;
	}
	else{
		listNode* nodetoremove=h->rlink;	//제일 앞 노드를 가리킬 포인터
		/*link 정리*/
		h->rlink=h->rlink->rlink;			
		h->rlink->llink=h;
		free(nodetoremove);	//제일 앞 노드 해제
	}
	return 1;
}
/*리스트의 링크를 역순으로 재배치*/
int invertList(listNode* h){
	if(h->rlink==h || h==NULL){	//헤더 노드만 있을경우 or 헤더노드도 없을경우
		printf("nothing to invert..\n");	//오류메시지 출력
		return 0;
	}
	else{
		listNode *n = h->rlink;
		listNode *middle = h;
		/*최종 바뀔 링크 유지*/
		h->llink=h->rlink;

		while(n !=NULL && n != h){
			middle=n;
			n=n->rlink;
			/*middle이 가리키는 노드링크 좌우 반전*/
			middle->rlink=middle->llink;
			middle->llink=n;
		}

		h->rlink=middle;

		return 0;
	}
}
/*리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입(오름차순)*/
int insertNode(listNode* h, int key){
	/*헤더 노드가 없을경우 리턴*/
	if(h == NULL) return -1;
	/*새로 추가할 노드 동적할당 및 초기화*/
	listNode* Node=(listNode*)malloc(sizeof(listNode));
	Node->key=key;
	Node->llink=NULL;
	Node->rlink=NULL;
	/*첫노드를 가리키도록 초기화*/
	listNode* n=h->rlink;
	/*마지막 노드까지 반복*/
	while(n != h && n !=NULL){
		if(n->key >= Node->key){ //n의 key가 새로운 노드의 key보다 같거나 클경우 break;
			break;
		}
		n=n->rlink;
	}
	/*새로운 노드를 끼워넣는다*/
	Node->rlink=n;
	Node->llink=n->llink;
	n->llink->rlink=Node;
	n->llink=Node;

	return 1;
}
int deleteNode(listNode* h, int key){
	/*헤더노드가 없거나 헤더노드만 있을경우*/
	if(h == NULL || h->rlink == h){
		printf("nothing to delete.\n");
		return 0;
	}

	else{
		listNode* n = h;
		while(n->rlink != h){	
			n=n->rlink;
			/*입력받은 키와 일치하는 노드를 찾은경우*/
			if(n->key == key){
				/*link 수정 후 해제*/
				n->rlink->llink=n->llink;
				n->llink->rlink=n->rlink;
				free(n);
				break;
			}
		}
		return 1;
	}
	printf("cannot find the node for key =%d\n",key);
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {	//헤더 노드가 없을경우
		printf("Nothing to print....\n");
		return;
	}
	//처음 노드를 가리키도록 초기화
	p = h->rlink;

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
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

listNode* SortList(listNode* h){
	if(h == NULL || h->rlink ==h){
		printf("nothing to sort.\n");
		return h;
	}
	
	/*새로운 헤더 포인터 선언 및 초기화*/
	listNode* hh=(listNode*)malloc(sizeof(listNode));
	hh->key=-9999;
	hh->llink=hh;
	hh->rlink=hh;
	
	listNode* n=h->rlink;
	/*insertNode함수를 호출 하며 새로운 노드들을 오름차순으로 리스트에 추가*/
	while(n !=h && n!=NULL){
		insertNode(hh,n->key);
		n=n->rlink;
	}
	printf("6");
	/*기존 리스트 해제*/
	freeList(h);
	return hh;
}