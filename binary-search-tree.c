/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node  //node 구조체 선언
{
	int key; //int형 변수 key선언
	struct node *left; //노드 구조체의 포인터 left 선언
	struct node *right; //노드 구조체의 포인터 right 선언
} Node; //구조체 별칭 Node로 설정

int initializeBST(Node** h); //headNode에 메모리를 할당하는 함수 선언

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  //중위 순회를 위한 재귀 함수 선언
void preorderTraversal(Node* ptr);    //전위 순회를 위한 재귀 함수 선언
void postorderTraversal(Node* ptr);	  //후위 순회를 위한 재귀 함수 선언
int insert(Node* head, int key);  //트리에 노드를 삽입하기 위한 함수 선언으로 head는 루트 노드를 가리키고 key는 삽입할 값
int deleteLeafNode(Node* head, int key);  //키에 해당하는 리프 노드를 삭제하기 위한 함수 선언, head는 루트 노드
Node* searchRecursive(Node* ptr, int key);  //키에 해당하는 노드를 재귀적으로찾기 위한 함수 선언, ptr은 현재 노드를 가리킴
Node* searchIterative(Node* head, int key);  //키에 해당하는 노드를 반복적으로 찾기 위한 함수 선언, head는 루트 노드
int freeBST(Node* head); //트리에 할당된 메모리를 해제하기 위한 함수 선언, head는 루트 노드

/* you may add your own defined functions if necessary */


int main()
{
	char command; //char형 변수 command 선언
	int key; //int형 변수 key 선언
	Node* head = NULL; //Node에 대한 포인터 head 선언 후 NULL값 할당
	Node* ptr = NULL;	/* temp */ //Node에 대한 포인터 ptr 선언 후 NULL값 할당

    printf("-----[신혜원] [2023041057]-----");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': //대소문자 z를 입력받았을 때
			initializeBST(&head); //head의 주소를 매개인자로 받아 initializeBST 함수 호출
			break;
		case 'q': case 'Q': //대소문자 q를 입력받았을 때
			freeBST(head); //head를 매개인자로 받아 freeBST함수 호출
			break;
		case 'n': case 'N': //대소문자 n를 입력받았을 때
			printf("Your Key = ");
			scanf("%d", &key); //key값 입력
			insert(head, key); //포인터 head와 key를 매개인자로 받아 insert 함수 호출
			break;
		case 'd': case 'D': //대소문자 d를 입력받았을 때
			printf("Your Key = ");
			scanf("%d", &key); //key값 입력
			deleteLeafNode(head, key); //포인터 head와 key를 매개인자로 받아 deleteLeafNode 함수 호출
			break;
		case 'f': case 'F': //대소문자 f를 입력받았을 때
			printf("Your Key = ");
			scanf("%d", &key); //key값 입력
			ptr = searchIterative(head, key); //포인터 ptr에 포인터 head와 key값을 매개인자로 받아 searchIteractive 함수의 리턴 값을 할당해줌
			if(ptr != NULL) //포인터 ptr의 값이 NULL이 아니면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 키 값(탐색된 값)과 ptr(노드) 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //노드를 찾지 못했다고 출력
			break;
		case 's': case 'S': //대소문자 s를 입력받았을 때
			printf("Your Key = ");
			scanf("%d", &key); //key값 입력
			ptr = searchRecursive(head->left, key); //포인터 ptr에 포인터 head의 left와 key값을 매개인자로 받아 searchRecursive 함수의 리턴 값을 할당 
			if(ptr != NULL) //포인터 ptr의 값이 NULL이 아니면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 키 값(탐색된 값)과 ptr(노드) 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //노드를 찾지 못했다고 출력
			break;

		case 'i': case 'I': //대소문자 i를 입력받았을 때
			inorderTraversal(head->left); //포인터 head의 left를 매개인자로 받아 inorderTraversal 함수 호출
			break;
		case 'p': case 'P': //대소문자 p를 입력받았을 때
			preorderTraversal(head->left); //포인터 head의 left를 매개인자로 받아 preorderTraversal 함수 호출
			break;
		case 't': case 'T': //대소문자 t를 입력받았을 때
			postorderTraversal(head->left); //포인터 head의 left를 매개인자로 받아 postorderTraversal 함수 호출
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //집중!! 츨력
			break;
		}

	}while(command != 'q' && command != 'Q'); //q가 입력되지 않을동안 반복

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //포인터 h가 가리키는 값이 NULL이 아니면
		freeBST(*h); //포인터 h를 매개인자로 받아 freBST 함수 호출

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //포인터 h에 Node 크기만큼 동적메모리 할당
	(*h)->left = NULL;	/* root */ //포인터 h의 left 선언 후 NULL값 할당
	(*h)->right = *h; //포인터 h의 right 선언 후 포인터 h값 할당
	(*h)->key = -9999; //포인터 h의 key 선언 후 -9999값 할당
	return 1;
}



void inorderTraversal(Node* ptr)
{
    if(ptr) //포인터 ptr이 NULL이 아니면
    {
        inorderTraversal(ptr->left); //ptr의 left를 매개인자로 받는 inorderTraversal 함수 호출
        printf("[%d]",ptr->key); //ptr의 key 값 출력
        inorderTraversal(ptr->right); //ptr의 right를 매개인자로 받는 inorderTraversal 함수 호출
    }

}

void preorderTraversal(Node* ptr)
{
    if(ptr) //포인터 ptr이 NULL이 아니면
    {
        printf("[%d]",ptr->key); //node의 key 값 출력
        preorderTraversal(ptr->left); //ptr의 left를 매개인자로 받는 preorderTraversal 함수 호출
        preorderTraversal(ptr->right); ////ptr의 right를 매개인자로 받는 preorderTraversal 함수 호출
    }

}

void postorderTraversal(Node* ptr)
{
    if(ptr) //포인터 ptr이 NULL이 아니면
    {
        postorderTraversal(ptr->left); //ptr의 left를 매개인자로 받는 postorderTraversal 함수 호출
        postorderTraversal(ptr->right); //ptr의 right를 매개인자로 받는 postorderTraversal 함수 호출
        printf("[%d]",ptr->key); //node의 key 값 출력
    }

}


int insert(Node* head, int key)
{
    Node* newNode=(Node*)malloc(sizeof(Node)); //Node의 포인터 newNode를 Node의 크기만큼 동적메모리 할당
    newNode->key=key; //newNode의 key에 Key 값 할당
    newNode->left=NULL; //newNode의 left에 NULL값 할당
    newNode->right=NULL; //newNode의 right에 NULL 값 할당

    if(head->left==NULL) //포인터 head의 left가 NULL값과 같다면
    {
        head->left=newNode; //포인터 head의 left에 newNode값 할당
        return 1; //리턴 1
    }

    Node* ptr= head-> left; //Node의 포인터 ptr에 head의 left값 할당

    Node* parentNode=NULL; //Node의 포인터 parentNode에 NULL값 할당
    while(ptr != NULL) //ptr이 NULL이 아닐동안
    {
        if(ptr->key == key) //ptr의 key값이 key값과 같다면
        {
            return 1; //리턴 1
        }

        parentNode = ptr; //parentNode에 ptr값 할당
        if(ptr->key < key) //ptr의 key값이 key값 보다 작으면
        {
            ptr= ptr->right; //ptr에 ptr의 right값 할당
        }
        else
        {
            ptr=ptr->left; //ptr에 ptr의 left값 할당
        }
    }

        if(parentNode->key > key) //ptr의 key값이 key값 보다 크면
        {
            parentNode->left=newNode; //parentNode의 left에 newNode값 할당
        }
        else
        {
            parentNode-> right = newNode; //parentNode의 right에 newNode값 할당
        }
        return 1;

}

int deleteLeafNode(Node* head, int key)
{
    if(head==NULL) //head가 NULL이면
    {
        printf("\nnNothing to delete\n"); //지울게 없다고 출력
        return -1; //리턴 -1
    }

    if(head->left==NULL) //head의 left가 NULL이면
    {
        printf("\nNothing to delete\n"); //지울게 없다고 출력
        return -1; //리턴 -1
    }

    Node* ptr = head->left; //Node의 포인터 ptr에 head의 left값 할당

    Node* parentNode=head; //Node의 포인터 ptr에 head값 할당

    while(ptr!=NULL) //ptr이 NULL이 아닐동안
    {
        if(ptr->key==key) //ptr의 key가 key값과 같다면
        {
            if(ptr->left==NULL && ptr->right==NULL) //ptr의 left와 right가 모두 NULL이면
            {
                if(parentNode==head) //parentNode가 head와 같다면
                {
                    head->left=NULL; //head의 left에 NULL값 할당
                }

                if(parentNode->left==ptr) //parentNode의 left가 ptr과 같다면
                {
                    parentNode->left=NULL; //parentNode의 left에 NULL값 할당
                }
                else{
                    parentNode->right=NULL; //parentNode의 right에 NULL값 할당
                }
                free(ptr); //ptr 할당된 메모리 해제
            }
            else
            {
                printf("the node [%d] is not a leaf\n",ptr->key); // ptr의 key가 노드의 leaf가 아니라고 출력
            }
            return 1;
        }

        parentNode=ptr; //parentNode에 ptr값 할당

        if(ptr->key < key) //ptr의 key가 key보다 작다면
        {
            ptr=ptr->right; //ptr에 ptr의 right값 할당
        }
        else
        {
            ptr=ptr->left; //ptr에 ptr의 left값 할당
        }
    }
    printf("Cannot find the node for key [%d]\n",key); //key에 해당하는 node를 찾지 못 했다고 출력
    return 1;

}

Node* searchRecursive(Node* ptr, int key)
{
    if(ptr==NULL) //ptr이 NULL이면
    {
        return NULL; //리턴 NULL
    }

    if(ptr->key < key) //ptr의 key가 key보다 작다면
    {
        ptr=searchRecursive(ptr->right, key); //ptr에 ptr의 right와 key값을 매개인자로 받은 searchRecursive 함수의 리턴값을 할당
    }
    else if(ptr->key > key) //ptr의 keyrk key보다 크면
    {
        ptr=searchRecursive(ptr->left, key); //ptr에 ptr의 left와 key 값을 매개인자로 받은 searchRecursive 함수의 리턴 값을 할당
    }

    return ptr; //리턴 ptr

}

Node* searchIterative(Node* head, int key)
{
    Node* ptr = head-> left; //Node의 포인터 ptr에 head의 left값 할당
    while(ptr != NULL) //ptr이 NULL이 아니면
    {
        if(ptr->key=key) //ptr의 key값이 key와 같다면
        {
            return ptr; //리턴 ptr
        }
        
        if(ptr->key < key) //ptr의 key값이 key값 보다 작으면
        {
            ptr=ptr->right; //ptr에 ptr의 right값 할당
        }
        else
        {
            ptr = ptr->left; //ptr에 ptr의 left값 할당
        }
    }
    return NULL; //리턴 NULL

}

void freeNode(Node* ptr)
{
    if(ptr) //ptr 값이 NULL이 아니면
    {
        freeNode(ptr->left); //ptr의 left값을 매개인자로 받은 freeNode 함수 호출
        freeNode(ptr->right); //ptr의 right값을 매개인자로 받은 freeNode 함수 호출
        free(ptr); //ptr에 할당된 메모리 해제
    }
}

int freeBST(Node* head)
{
    if(head->left == head) //head의 left가 head와 같다면
    {
        free(head); //head에 할당된 메모리 해제
        return 1;
    }

    Node* p = head->left; //Node의 포인터 p에 head의 left값 할당

    freeNode(p); //p에 할당된 메모리 해제
    free(head); //head에 할당된 메모리 해제
    return 1;

}
