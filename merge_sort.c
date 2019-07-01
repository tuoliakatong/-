#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include "lib.h"
/*typedef struct word{
	char s[20];	//单词的字符串
	int num = 0;	//单词的数目
}word;	
*/
typedef struct word{
	char s[30];
	int num;
}word;

int isequal(void *a, void *b);
int compare(void *a, void *b);

int main(){
	FILE *fp;
	if((fp = fopen("Harry.txt", "r")) == NULL){	//	以只读的方式打开文件 
		printf("file cannot open\n");
		return -1;
	}

	node *head = init();	//初始化一个双向链表
	/*读文件并统计单词个数*/
	char ch;
	int size = sizeof(word), i;
	while((ch = getc(fp)) != EOF){	//未到文件末尾则继续往下读
		if(islower(ch) || isupper(ch)){		//当首字符是字母时是单词
			word a;		//结构a记录该单词的数据
			a.s[0] = ch;
			for(i = 1; islower(a.s[i] = getc(fp)) || isupper(a.s[i]); i++);
			a.s[i] = '\0';	
			void *data = &a;
			node *p = search(head, data, isequal);
			if(p){		//	当查找成功时，不需要将该单词插入链表
				(*(word*)p -> content).num++;	//该单词数量加1
			}else{	//查找失败时，将该单词插入链表
				a.num = 1;
				insert(head, data, size);
			}
		}
	}
	/*排序*/
	node *p = head -> next;
	node *ptr = merge_sort(p, compare); 	
	/*接上头结点*/
	ptr -> pre = head;
	head -> next = ptr; 
	/*遍历输出*/
	while(ptr){
		printf("%7d %s\n", (*(word*)ptr -> content).num, (*(word*)ptr -> content).s);
		ptr = ptr -> next;
	}
	
	return 0;
}

int isequal(void *a, void *b){
	if(strcmp((*(word*)a).s, (*(word*)b).s) == 0){	//两结点中的单词相同
		return 1;
	}else{
		return 0;
	}
}

int compare(void *a, void *b){
	if((*(word*)a).num < (*(word*)b).num){
		return 1;
	}else if((*(word*)a).num == (*(word*)b).num){
		char m[30], n[30];
		int i;
		for(i = 0; (m[i] = tolower((*(word*)a).s[i])) != '\0'; i++);
		for(i = 0; (n[i] = tolower((*(word*)b).s[i])) != '\0'; i++);
		if(strcmp(m, n) < 0){
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}
