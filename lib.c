#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lib.h"

/*初始化一个双向链表*/
node *init(){
	node *head = (node*)malloc(sizeof(node*));
	head -> pre = NULL;
	head -> next = NULL;
	
	return head;
}
/*查找元素*/
node *search(node *head, void *data, int (*isequal)(void *, void *)){
	node *ptr = head -> next;
	/*通过比较进行查找*/	
	while(ptr && !isequal(ptr -> content, data)){
		ptr = ptr -> next;
	}
		
	if(!ptr){
		//printf("未查找到该元素\n");
		return NULL;
	}
	return ptr;	//返回查找到的节点指针
}	

/*插入节点*/
void insert(node *head, void *data, int size){
	/*if(search(head, data, isequal)){	//若存在，则不需插入
		printf("双向链表中已存在该元素，插入失败!\n");
		return;
	}else{		//若不存在，插入节点
*/		node *new = (node*)malloc(sizeof(node*));	//为插入节点申请空间
		if(!new){
			printf("为新节点分配空间失败\n");
			return;
		}
		new -> content = malloc(size);
		memcpy(new -> content, data, size);
		/*插入*/
		node *s = head -> next;
		head -> next = new;
		new -> pre = head;
		new -> next = s;
		if(s)	s -> pre = new;
		//printf("插入成功\n");
	return;
}

/*删除节点*/
void delete(node *head, void *data, int (*isequal)(void *, void *)){	
	/*查找双向链表中是否存在该元素*/
	node *p = search(head, data, isequal);
	if(!p){	//若不存在，则不需删除
		printf("双向链表中不存在该元素，删除失败!\n");
		return;
	}else{		//若存在，删除节点
		/*删除节点*/
		p -> pre -> next = p -> next;
		p -> next -> pre = p -> pre;
		free(p -> content);
		free(p);	//释放p所指向节点的空间
		//printf("删除成功\n");
	}
	return;
}

/*排序*/
void sort(node *head, int size, int (*compare)(void *, void *)){
	if(head -> next == NULL)
		return;
	node *ptr = head; 	//工作指针
	/*找到尾结点的指针*/
	while(ptr -> next){
		ptr = ptr -> next;
	}
	node *tail = ptr;
	ptr = head -> next;
	
	/*冒泡*/
	while(tail != head -> next){	//当tail指向第一个结点时冒泡结束
		while(ptr != tail){	//当ptr等于tail时一轮冒泡结束
			if(compare(ptr -> content, ptr -> next -> content)){	//交换两结点content所指向的内容
				void *tmp = malloc(size);
				memcpy(tmp, ptr -> content, size);
				memcpy(ptr -> content, ptr -> next -> content, size);
				memcpy(ptr -> next -> content, tmp, size);
			}
			ptr = ptr -> next;
		}
		ptr = head -> next;	//重置工作指针
		tail = tail -> pre;	//tail指向前一个结点
	}	
	return;
}
/*归并排序*/
node *merge_sort(node *p, int (*compare)(void *, void *)){
	/*对边界条件的处理*/
	if(p -> next == NULL){
		return p;
	}
	/*使用fast-slow方法将链表二分*/
	node *fast = p -> next;
	node *slow = p;
	while(fast != NULL && fast -> next != NULL){
		fast = fast -> next -> next;
		slow = slow -> next;
	}
	node *left = p;
	node *right = slow -> next;
	right -> pre = NULL;
	slow -> next = NULL;	//分割两链表	
	/*递归处理左右链表*/	
	node *leftnode = merge_sort(left, compare);
	node *rightnode = merge_sort(right, compare);

	/*合并左右链表*/
	/*处理第一个结点*/
	node *newlist;
	if(!compare(leftnode -> content, rightnode -> content)){
		newlist = leftnode;
		leftnode = leftnode -> next;
	}else{
		newlist = rightnode;
		rightnode = rightnode -> next;
	}
	/*处理后续结点*/
	node *ptr = newlist;	
	while(leftnode != NULL && rightnode != NULL){
			if(!compare(leftnode -> content, rightnode -> content)){	//摘下leftnode
				ptr -> next = leftnode;
				leftnode -> pre = ptr;
				ptr = ptr -> next;
				leftnode = leftnode -> next;
			}else{	//摘下rightnode
				ptr -> next = rightnode;
				rightnode -> pre = ptr;
				ptr = ptr -> next;
				rightnode = rightnode -> next;
			}
	}
	if(leftnode == NULL){	//将剩下的右链表链上
		ptr -> next = rightnode;
		rightnode -> pre = ptr;
	}else{			//将剩下的左链表链上
		ptr -> next = leftnode;
		leftnode -> pre = ptr;
	}

	return newlist;	//返回合并后链表的首结点的指针
}	
