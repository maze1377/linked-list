#include <stdio.h>
struct Node {
	int data;
	Node *next;
};
void printList_received_uptoend(Node *list){
	if(list==NULL){
		return;
	}
	printf("%d",list->data);
	printList_received_uptoend(list->next);
}
void printList_received_endtoup(Node *list){
	if(list==NULL){
		return;
	}
	printList_received_endtoup(list->next);
	printf("%d",list->data);
}
void printList_unreceived(Node *list){
	while (list!=NULL){
		printf("%d",list->data);
		list=list->next;
	}
}
void deleteList_received(Node *&list){
	if (list == NULL)
		return;
	deleteList_received(list->next);
	delete list;
	list = NULL;
}
void deleteList_unreceived(Node *&list){
	Node *temp=list;
	while(list!=NULL){
		temp=list->next;
		delete list;
		list = NULL;
		list=temp;
	}
}
Node* find_received(Node *list, int data){
	if (list == NULL)
		return NULL;
	if(list->data==data) return list;
	else
		find_received(list->next,data);
}
Node* find_unreceived(Node *list, int data){
	while(list!=NULL){
		if(list->data==data) return list;
		list=list->next;
	}
	return NULL;
}
void append(Node *&list, int data){
	Node *temp=new Node;
	temp->data=data;
	temp->next=NULL;
	if(list==NULL){
		list=temp;
		return;
	}
	else{
		Node *last=list;
		while(last->next != NULL)
			last=last->next;
		last->next=temp;
	}
}
void insertAfter(Node *p, int data){
	if(p==NULL){
		printf("not to add");
		return;
	}
	Node *temp=new Node;
	temp->data=data;
	temp->next=p->next;
	p->next=temp;
}
void insertAtFront(Node *&p, int data){
	Node *temp=new Node;
	temp->data=data;
	temp->next=p->next;
	p=temp;
}
int main(){
	Node *list = NULL;
	append(list,10);
	append(list,20);
	append(list,30);
	append(list,40);
	append(list,50);
	insertAfter(find_received(list,30),60);
	printList_received_uptoend(list);
	deleteList_received(list);
	printf("\n");
}
