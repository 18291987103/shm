#include"dblinklist.h"

/*
 *
 * 初始化双链表
 *
 */

void DLinkListInit(DLinkNode** phead)
{
    if(phead == NULL)
    {
        return;//非法输入
    }
    *phead = (DLinkNode*)malloc(sizeof(DLinkNode));
    (*phead) -> data = 0;
    (*phead) -> next = *phead;
    (*phead) -> prev = *phead;
}

/*
 *
 * 创建一个新节点
 *
 */
DLinkNode* DLinkNodeCreat(DLinkType value)
{
    DLinkNode* new_node = (DLinkNode*)malloc(sizeof(DLinkNode));
    if(new_node == NULL)
    {
        return NULL;//内存分配失败
    }
    new_node -> data = value;
    new_node -> next = new_node;
    new_node -> prev = new_node;
    return new_node;
}
/*
 *
 * 销毁一个节点
 *
 */

void DLinkNodeDstroy(DLinkNode* to_delete)
{
    free(to_delete);
    to_delete = NULL;
}
/*
 *
 * 尾插一个节点
 *
 */

DLinkNode* DLinkListPushBack(DLinkNode* head, DLinkType value)
{
    if(head == NULL)
    {
        return NULL;//非法输入
    }
    
    DLinkNode* new_node = DLinkNodeCreat(value);
    DLinkNode* next = head -> next;
    new_node -> next = next;
    next -> prev = new_node;
    head -> next = new_node;
    new_node -> prev = head;
    return head;
}

/*
 *
 * 头插一个节点
 *
 */

void DLinkListPushFront(DLinkNode* head, DLinkType value)
{
    if(head == NULL)
    {
        return;//非法输入
    }
    DLinkNode* new_node = DLinkNodeCreat(value);
    DLinkNode* prev = head;
    DLinkNode* next = head -> next;
    prev -> next = new_node;
    new_node -> prev = prev;
    new_node -> next = next;
    next -> prev = new_node;
}

/*
 *
 * 头删一个节点
 *
 */
void DLinkListPopFront(DLinkNode* head)
{
    if(head == NULL)
    {
        return;//非法输入
    }

    if(head -> next == head)
    {
        return;//空链表
    }
    DLinkNode* to_delete = head -> next;
    DLinkNode* next = to_delete -> next;
    head -> next = next;
    next -> prev = head;
    DLinkNodeDstroy(to_delete);
}

/*
 *
 * 尾删一个元素
 *
 */

void DLinkListPopBack(DLinkNode* head)
{
    if(head == NULL)
    {
        return;//非法输入
    }
    if(head -> next == head)
    {
        return;//删除空链表
    }

    DLinkNode* to_delete = head -> prev;
    DLinkNode* prev = to_delete -> prev;
    head -> prev = prev;
    prev -> next = head;
    DLinkNodeDstroy(to_delete);
}

DLinkNode* DLinkListFind(DLinkNode* head, DLinkType to_find)
{
    if(head == NULL)
    {
        return NULL;//非法输入
    }
    if(head -> next == head)
    {
        return NULL;
    }

    DLinkNode* cur = head -> next;
    for(; cur != head; cur = cur -> next)
    {
        if(cur -> data == to_find)
        {
            return cur;
        }
    }
    return NULL;//没有找到
}

/*
 *
 * 往 pos 所对应的位置处插入 value 
 *
 *
 */

void DLinkListInsert(DLinkNode* pos, DLinkType value)
{
    if(pos == NULL)
    {
        return;//非法输入
    }
    DLinkNode* new_node = DLinkNodeCreat(value);
    DLinkNode* prev = pos -> prev;
    //prev vs new_node
    prev -> next = new_node;
    new_node -> prev = prev;
    //new_node vs pos
    new_node -> next = pos;
    pos -> prev = new_node;
}

/*
 *
 * 往指定位置之后插入一个元素
 *
 */

void DLinkListInsertAfter(DLinkNode* pos, DLinkType value)
{
    if(pos == NULL)
    {
        return;//非法输入
    }

    DLinkNode* new_node = DLinkNodeCreat(value);
    DLinkNode* next = pos -> next;
    pos -> next = new_node;
    new_node -> prev = pos;
    new_node -> next = next;
    next -> prev = new_node;
}

/*
 *
 * 删除某个元素对应的结点
 *
 */

void DLinkListErase(DLinkNode* head, DLinkType to_delete)
{
    if(head == NULL)
    {
        return;//非法输入
    }

    if(head -> next == NULL)
    {
        return;//删除空链表
    }
    DLinkNode* cur = DLinkListFind(head, to_delete);
    if(cur == NULL)
    {
        return;//删除不存在的节点
    }
    DLinkNode* prev = cur -> prev;
    DLinkNode* next = cur -> next;
    prev -> next = next;
    next -> prev = prev;
    DLinkNodeDstroy(cur);
}

/*
 *
 * 求链表长度
 *
 */

size_t DLinkListSize(DLinkNode* head)
{
    DLinkNode* cur = head -> next;
    size_t size = 0;
    while(cur != head)
    {
        cur = cur -> next;
        size++;
    }
    return size;
}

/*
 *
 * 链表判空
 *
 */

int DLinkListEmpty(DLinkNode* head)
{
    if(head == NULL)
    {
        return -1;//非法输入
    }
    if(head -> next == head)
    {
        return 1;
    }
    return 0;
}

void DLinkListRemoveAll(DLinkNode** phead)
{
    if(phead == NULL)
    {
        return;//非法输入
    }
    if(*phead == NULL)
    {
        return;//非法输入
    }
    if((*phead) -> next == *phead)
    {
        DLinkNodeDstroy(*phead);
        return;
    }
    int size = DLinkListSize(*phead);
    for(; size > 0; size--)
    {
        DLinkListPopBack(*phead);
    }
    DLinkNodeDstroy(*phead);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////以下是测试代码
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TESTHEADER printf("\n=================%s======================\n", __FUNCTION__)

void TestPrintChar(DLinkNode* head, char* msg)
{
    printf("[%s]\n", msg);

    printf("[%d | %p] => ", (int)head -> data, head);
    DLinkNode* cur = head -> next;
    for(; cur != head; cur = cur -> next)
    {
        printf("[%c | %p] => ", cur -> data, cur);
    }
    printf("\n");

    for(cur = head -> prev; cur != head; cur = cur -> prev)
    {
        printf("[%c | %p] <= ", cur -> data, cur);
    }
    printf("[%d | %p] <= ", (int)head -> data, head);
    printf("\n");
}

void TestInit()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    TestPrintChar(head, "初始化双链表");
}

void TestCreate()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkNode* ret = DLinkNodeCreat('a');
    printf("[%c | %p]\n", ret -> data, ret -> next);
    printf("[%c | %p]\n", ret -> data, ret -> prev);
}

void TestPushBack()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    TestPrintChar(head, "尾插四个元素");
}

void TestPopBack()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    TestPrintChar(head, "尾插四个元素");
    DLinkListPopBack(head);
    DLinkListPopBack(head);
    TestPrintChar(head, "尾删两个元素");
    DLinkListPopBack(head);
    DLinkListPopBack(head);
    TestPrintChar(head, "再尾删两个元素");
    DLinkListPopBack(head);
    TestPrintChar(head, "尝试删除空链表");

}

void TestPushFront()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head, '1');
    DLinkListPushFront(head, '2');
    DLinkListPushFront(head, '3');
    DLinkListPushFront(head, '4');
    TestPrintChar(head, "头插四个元素");
}

void TestPopFront()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head, '1');
    DLinkListPushFront(head, '2');
    DLinkListPushFront(head, '3');
    DLinkListPushFront(head, '4');
    TestPrintChar(head, "头插四个元素");
    DLinkListPopFront(head);
    DLinkListPopFront(head);
    TestPrintChar(head, "头删两个节点");
    DLinkListPopFront(head);
    DLinkListPopFront(head);
    TestPrintChar(head, "再头删两个节点");
    DLinkListPopFront(head);
    TestPrintChar(head, "尝试删除空链表");
}

void TestInsert()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head, '1');
    DLinkListPushFront(head, '2');
    DLinkListPushFront(head, '3');
    DLinkListPushFront(head, '4');
    TestPrintChar(head, "头插四个元素");
    DLinkListInsert(head -> next -> next, 'x');
    TestPrintChar(head, "往 3 前面插入 x ");
}

void TestFind()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head, '1');
    DLinkListPushFront(head, '2');
    DLinkListPushFront(head, '3');
    DLinkListPushFront(head, '4');
    TestPrintChar(head, "头插四个元素");
    DLinkNode* ret = DLinkListFind(head, '3');
    printf("expected ret = 3, actual ret = %c\n", ret -> data);
    DLinkNode* ret2 = DLinkListFind(head, 'x');
    printf("expected ret = NULL, actual ret = %p\n", ret2);
}

void TestInsertAfter()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head, '1');
    DLinkListPushFront(head, '2');
    DLinkListPushFront(head, '3');
    DLinkListPushFront(head, '4');
    TestPrintChar(head, "头插四个元素");
    DLinkListInsertAfter(head -> next -> next, 'q');
    TestPrintChar(head, "往 3 后面插入 q");
}

void TestErase()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head, '1');
    DLinkListPushFront(head, '2');
    DLinkListPushFront(head, '3');
    DLinkListPushFront(head, '4');
    TestPrintChar(head, "头插四个元素");
    DLinkListErase(head, '3');
    TestPrintChar(head, "删除 3 对应的节点");
    DLinkListErase(head, '5');
    TestPrintChar(head, "删除一个不存在的元素");
}

void TestSize()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head, '1');
    DLinkListPushFront(head, '2');
    DLinkListPushFront(head, '3');
    DLinkListPushFront(head, '4');
    TestPrintChar(head, "头插四个元素");
    int size = DLinkListSize(head);
    printf("expected size = 4, actual size = %d\n", size);
}

void TestEmpty()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    int ret1 = DLinkListEmpty(head);
    printf("expected ret1 = 1, actual ret1 = %d\n", ret1);
    DLinkListPushFront(head, '1');
    DLinkListPushFront(head, '2');
    DLinkListPushFront(head, '3');
    DLinkListPushFront(head, '4');
    TestPrintChar(head, "头插四个元素");
    int ret = DLinkListEmpty(head);
    printf("expected ret = 0, actual ret = %d\n", ret);
}

void TestRemoveAll()
{
    TESTHEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head, '1');
    DLinkListPushFront(head, '2');
    DLinkListPushFront(head, '3');
    DLinkListPushFront(head, '4');
    TestPrintChar(head, "头插四个元素");
    DLinkListRemoveAll(&head);
    TestPrintChar(head, "删除所有元素");
}

int main()
{
    TestInit();
    TestCreate();
    TestPushBack();
    TestPushFront();
    TestPopFront();
    TestPopBack();
    TestFind();
    TestInsert();
    TestInsertAfter();
    TestErase();
    TestSize();
    TestEmpty();
    TestRemoveAll();
    return 0;
}
