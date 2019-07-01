typedef struct doublelinked_node{
	struct doublelinked_node *pre;
	struct doublelinked_node *next;
	void *content;
}node;

/*初始化双向链表*/
node *init();

/*搜索*/
node *search(node *head, void *data, int (*isequal)(void *, void *));

/*插入*/
void insert(node *head, void *data, int size);

/*删除*/
void delete(node *head, void *data, int (*isequal)(void *, void *));

/*排序*/
void sort(node *head, int size, int (*compare)(void *, void *));

/*归并排序*/
node *merge_sort(node *p, int (*compare)(void *, void *));
