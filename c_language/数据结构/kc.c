#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//2026年1月14日09:49:59
//*************************************************************
/* void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    printf("a=%d,b=%d\n",*a,*b);
}
int main()
{
    int m=5;
    int n=10;
    swap(&m,&n);
    return 0;
} */
//*************************************************************
//获取数组长度
/* for(int i=0;i<sizeof(a)/sizeof(a[0]);i++);
{
    printf("%d\n",*(p+i));
} */
//指针的算数运算
/*给指针加上整数，实际上是加上整数与指针数据类型的乘积，例如上面的内容中，加上的实际上是1*4;*/
//*************************************************************
//结构体的使用
/* struct point
{
    int x;
    int y;
}; */
/* struct point createpoint(int x,int y)
{
    struct point temp;
    temp.x=x;
    temp.y=y;
    return temp;
}

int main(int argc, char const *argv[])
{
    struct point p;
    p=createpoint(5,10);
    printf("%d\n",p.x);
    printf("%d\n",p.y);
    return 0;
} */
/* int main(int argc, char const *argv[])
{
    struct point p;
    p.x=5;
    p.y=10;
    struct point *pp;
    pp=&p;
    pp->x=10;
    pp->y=5;
    printf("x=%d,y=%d\n",p.x,p.y);
    return 0;
} */
//？结构体中的补位：占据内存的大小
//*************************************************************
//类型定义typedef
/* 格式：typedef 类型 名称;
eg. typedef int mytype;
用途:可能存在大量需要进行类型修改的地方。 */
//在结构体上的应用
/* typedef struct
{
    int x;
    int y;
}po;//别名 
int main(int argc, char const *argv[])
{
    po p;
    p.x=5;
    p.y=10;
    po *pp;
    pp=&p;
    pp->x=10;
    pp->y=5;
    printf("x=%d,y=%d\n",p.x,p.y);
    return 0;
} */
//*************************************************************
//内存的分类:静态|全局内存；自动内存（栈内存）；动态内存（堆内存）
//动态内存分配 步骤:使用malloc进行内存分配；使用分配的内存；free函数释放内存
/* typedef struct
{
    int x;
    int y;
}po;//别名 
int main(int argc, char const *argv[])
{
    po *p;
    p=(po*)malloc(sizeof(po));
    p->x=5;

    p->y=10;
    printf("%d %d\n",p->x,p->y);
    return 0;
} */










//2026年1月14日17:02:40
//*************************************************************
/* typedef struct 
{
   char ISBN[10];
   char bookName[20]; 
   double price;
}book;
int main(int argc, char const *argv[])
{
    book b1;
    strcpy(b1.ISBN,"114514");
    strcpy(b1.bookName,"原理");
    b1.price=100;
    return 0;
} */









//2026年1月15日08:34:53
//*************************************************************
//顺序表的初始化
/* #define MAX 100
typedef int elemtype;
typedef struct 
{
    elemtype data[MAX];//seqlist第一个元素是数组，第二个是一个整数
    int length;
}seqlist;
void initlist(seqlist *L)//顺序表的初始化
{
    L->length=0;
}
int main(int argc, char const *argv[])
{
    seqlist list;
    initlist(&list);

    return 0;
} */
//*************************************************************
//顺序表在尾部插入元素
/* int appendelem(seqlist *L,elemtype e)//参数一是指向seqlist类型结构体的指针，参数二是要写入的数据
{
    if(L->length>=MAX)
    {
        printf("顺序表已满\n");
    }
    else
    {
        L->data[L->length]=e;
        L->length++;
    }
} */
//*************************************************************
//遍历
/* void listElem(seqlist *L)
{
    for (int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n");
} */
//*************************************************************
//顺序表插入元素
/* int insertelem(seqlist *L,int pos,elemtype e)
{
    if(pos<=L->length)
    {//因为后面是空位可以直接进行替换，不用创造中间变量，从后遍历数组更佳
        for(int i=L->length-1;i>=pos-1;i--)//第一个减一是为了进行移位，第二个减一是因为位置与数组下标错一位
        {
            L->data[i+1]=L->data[i];
        }//循环后空出需要添加元素的位置
        L->data[pos-1]=e;
        L->length++;
    }
} */
//顺序表的插入时间复杂度为O(n)。
//*************************************************************
//顺序表删除元素
/* int deletelem(seqlist *L,int pos,elemtype e)//e的作用见下
{
    if(pos<=L->length)
    {//因为后面是空位可以直接进行替换，不用创造中间变量，从后遍历数组更佳
        for(int i=pos;i>=L->length;i++)//第一个减一是为了进行移位，第二个减一是因为位置与数组下标错一位
        {
            L->data[i-1]=L->data[i];
        }//循环后空出需要添加元素的位置
        L->length--;
    }
} */
/* 在理解中，删除元素后，后面的元素占据了数组中前一个元素的位置，
但是实际上，在内存空间中，元素的绝对储存位置并没有发生变化，
也就是说删除元素依然在原来的内存地址中储存着，可以通过一个
指向这个地址的指针来调取这个删除元素（elemtype deldata;&deldata; *e=L->data[pos-1]） 
对数组来说，修改后的length后一位上储存的还是之前的最后一位的值，因为数组的内存空间是连续的*/
//*************************************************************
// 查找
/* int findElem(seqlist *L, elemtype e)
{
    for (int i = 0; i < L->length; i++)
    {
        if (L->data[i] == e)
        {
            return i + 1;//返回位置值，是下标加1
        }
    }
    return 0;
} */
//*************************************************************
//顺序表的动态分配内存地址初始化（使用堆内存）
/* typedef struct 
{
    int *data;
    int length;
}seqlist;
seqlist* initlist()//堆内存的初始化函数
{
    seqlist *L=(seqlist*)malloc(sizeof(seqlist));//将结构体创建在堆内存中
    L->data=(int*)malloc(sizeof(int)*100);//将data数组创建在堆内存中
    L->length=0;
    return L; //L指向堆内存中的顺序表
} */
//之后可以定义seqlist *list =initlist();
/* 此时的list不再是上面的一个结构体变量，而是一个结构体指针，
也就是说上面编写的函数再一次使用时不需要对list取地址了。 */










//2026年1月16日16:56:01
//*************************************************************
//单链表
/* typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *next;
}Node;
//初始化链表
Node* initList()
{
    Node *head=(Node*)malloc(sizeof(Node));
    head->data=-1;
    head->next=NULL;
    return head;
}
//头插法
int insertHead(Node*L,ElemType e)
{
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    p->next=L->next;
    L->next=p;
    return 1;
}
//遍历
void listNode(Node*L)
{
    Node *p = L->next; // 从第一个有效节点开始
    while(p!=NULL)
    {
        printf("%d\n",p->data);
        p=p->next;
    }
    printf("\n");
}
//获取尾部节点
Node* get_tail(Node*L)
{
    Node *p = L; // 从链表头开始遍历
    while (p->next!=NULL)
    {
        p=p->next;
    }
    return p;
}
//尾插法
Node* insertTail(Node *tail,ElemType e)
{
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    tail->next = p; // 核心：将新节点链接到原尾节点后
    p->next=NULL; 
    return p;
}
//指定位置插入
int insertNode(Node *L,int pos,ElemType e)
{
    Node *p=L;//保存前驱节点
    int i=0;
    while (i<pos-1)
    {
        i++;
        p=p->next;
        if (p==NULL)
        {
            return 0;
        }
    } 
    //需要插入的新节点
    Node *q=(Node*)malloc(sizeof(Node));
    q->data=e;
    q->next=p->next;
    p->next=q;
    return 1;
}
//指定位置删除
int deleteNode(Node *L,int pos)
{
    Node *p=L;//要删除的指针前驱
    int i;
    while (i<pos-1)
    {
        i++;
        p=p->next;
        if (p==NULL)
        {
            return 0;
        }
    }
    Node *q=p->next;
    p->next=q->next;
    free(q);
    return 1;
}
//获取链表长度
int listlength(Node *L)
{
    Node *p=L->next;
    int len=0;
    while (p!=NULL)
    {
        p=p->next;
        len++;
    }
    return len;
}
//释放链表
void freeList(Node *L)
{
    Node *p=L->next;
    Node *q;
    while (p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL; 
}
//主函数 
int main(int argc, char const *argv[])
{
    Node *list=initList();
    Node *tail=get_tail(list);
    tail=insertTail(tail,10);
    tail=insertTail(tail,20);
    tail=insertTail(tail,30);
    listNode(list);
    insertNode(list,2,15);
    listNode(list);
    deleteNode(list,2);
    listNode(list);
    printf("%d\n",listlength(list));
    return 0;
} */










//2026年1月16日20:13:32
//*************************************************************
//例题，寻找链表倒数某一位上的值，解法：快慢双指针
/* typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *next;
}Node;
//初始化链表
Node* initList()
{
    Node *head=(Node*)malloc(sizeof(Node));
    head->data=-1;
    head->next=NULL;
    return head;
}
int findNodeFS(Node *L,int k)
{
    Node *fast=L->next;
    Node *slow=L->next;
    for(int i=0;i<k;i++)
    {
        fast=fast->next;
    }
    while (fast!=NULL)
    {
        fast=fast->next;
        slow=slow->next;
    }
    printf("%d   %d\n",k,slow->data);
    return 1;
} */
















//2026年1月17日07:58:55
//例题2
//*************************************************************
/* //两个字符串结尾共用相同，寻找相同首字母
Node* findIntersectionNode(Node *headA,Node *headB)
{
    if (headA==NULL||headB==NULL)//判断是否存在空链表
    {
        return NULL;
    }
    int lenA=0,lenB=0;//分别遍历AB链表，获得两个链表的长度
    Node *p=headA;
    while (p!=NULL)
    {
        p=p->next;
        lenA++;
    }
    p=headB;
    while (p!=NULL)
    {
        p=p->next;
        lenB++;
    }
    Node *f;
    Node *s;
    int step;
    step=fabs(lenA-lenB);//计算两个链表长度的差值
    if (lenA>lenB)//选择快慢指针
    {
        f=headA;
        s=headB;
    }
    else
    {
        s=headA;
        f=headB;
    }
    for (int i = 0; i < step; i++)//让快指针先走step步
    {
        f=f->next;
    }
    while (f!=s)//两个指针同时走，直到找到相同地址
    {
        f=f->next;
        s=s->next;
    }
    return f;//返回地址
}
//例题3 思想：用空间换取时间
//删除链表数据中绝对值相同的节点  
void removeNode(Node *L,int n)
{
    Node *p=L;
    int index;//index为数组下标值
    int *q=(int*)malloc(sizeof(int)*(n+1));//创建一个数组q，第x位上存储的是链表data域x值，当数组值为0时说明是第一次遇到该值
    for (int i = 0; i < n+1; i++)//q数组初始化
    {
        *(q+i)=0;
    }
    while (p->next!=NULL)
    {
        index=fabs(p->next->data);//将data域值赋值给q数组下标
        if (*(q+index)==0)//当下标储存值为0，就是第一次遇见
        {
            *(q+index)=1;//将下标储存值设置为1，当下一次读取到相同绝对值的值时进行if判断就进入else
            p=p->next;
        }
        else//删除重复值
        {
            Node *temp=p->next;
            p->next=temp->next;
            free(temp);
        }
    }
    free(q);
}
//例题4 思想：快慢指针不同速度
//反转链表
Node* reverseList(Node* head)
{
    Node *first=NULL;
    Node *second=head->next;
    Node *third=second->next;
    while (second!=NULL)
    {
        third=second->next;//先保存下一个节点的值不丢失
        second->next=first;//反转链表方向
        first=second;
        second=third;
    }
    Node *hd=initList();//创建新的头节点
    hd->next=first;
    return hd;
}
//删除链表的最中间节点
int delMiddleNode(Node *L)
{
    Node *first=head->next;//要删除某一位，需要找到前一位
    Node *slow=head;
    while (first!=NULL&&first->next!=NULL)
    {
        first=first->next->next;//快指针速度是慢指针两倍
        slow=slow->next;
    }
    Node *q=slow->next;
    slow->next=slow->next->next;//跳过要删除的节点
    free(q);//删除
    return 1;
}
//特殊排序
void reOrderList(Node *head)
{
    Node *fast=head->next;//寻找中间位置(的前置节点)
    Node *slow=head;
    while (fast!=NULL&&fast->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
    }
    Node *first=NULL;//分割链表，后半部分反向排序
    Node *second=slow->next;
    slow->next=NULL;
    Node *third=NULL;
    while (second!=NULL)
    {
        third=second->next;
        second->next=first;
        first=second;
        second=third;
    }
    Node *p1=head->next;//进行插空插入，p1指向第一个链表
    Node *q1=first;//q2指向第二个链表
    Node *p2,*q2;
    while (p1!=NULL&&p2!=NULL)
    {
        p2=p1->next;//对q1，q2进行定义
        q2=q1->next;

        p1->next=q1;//按照顺序进行连接
        q1->next=p2;

        p1=p2;//移位
        q1=q2;
    }
}
/* 单链表具有局限性，只能朝着一个方向前进，一旦涉及到需要回头的程序，
处理起来就非常麻烦，这个问题可以用双链表或者循环链表解决。 */










//2026年1月17日11:00:10
//*************************************************************
//单向循环链表
/* //判断是否成环
int isCycle(Node *head)//原理：不成环的链表的两个不同速度的指针不可能相遇
{
    Node *fast=head;
    Node *slow=head;
    while (fast!=NULL&&fast->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
        if (fast==slow)
        {
            return 1;
        }
    }
    return 0;
}
//寻找环的入口
//原理:先判断环的节点数，让快指针先走这个数字，然后两个指针同时走，相遇的地址就是环的入口
Node* findBegin(Node *head)
{
    Node *fast=head;
    Node *slow=head;
    while (fast!=NULL&&fast->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
        if (fast==slow)//说明存在环
        {
            int count=1;
            while (fast->next!=slow)//判断节点个数
            {
                count++;
                fast=fast->next;
            }
            fast=head;//两个指针回到头结点
            slow=head;
            for (int i = 0; i < count; i++)//让快指针先走count步数
            {
                fast=fast->next;
            }
            while (fast!=slow)//两个指针同时行动，直到相遇
            {
                fast=fast->next;
                slow=slow->next;
            }
            return slow;//返回入环点
        }
    }
    return NULL;
} */










//2026年1月19日10:56:53
//双向链表
/* typedef int Elemtype;
typedef struct node
{
    Elemtype data;
    struct node *next,*prev;
}Node;

//初始化链表
Node* initList()
{
    Node *head=(Node*)malloc(sizeof(Node));
    head->data=-1;
    head->next=NULL;
    head->prev=NULL;
    return head;
}
//头插法
int insertHead(Node *L,Elemtype e)
{
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    p->prev=L;
    p->next=L->next;
    if (L->next!=NULL)
    {
        L->next->prev=p;
    }
    L->next=p;
    return 1;
    
}
//遍历
void listNode(Node*L)
{
    Node *p = L->next; // 从第一个有效节点开始
    while(p!=NULL)
    {
        printf("%d\n",p->data);
        p=p->next;
    }
    printf("\n");
}
//尾插法
int insertTail(Node *L,Elemtype e)
{
    Node *p=(Node*)malloc(sizeof(Node));
    p->data = e;
    p->next = NULL;       // 新节点作为尾节点，next指向NULL
    p->prev = L;       // 新节点的前驱指向原尾节点
    L->next = p;       // 原尾节点的后继指向新节点
    return 1;
}
//在指定位置插入数据
int insertNode(Node *L,int pos,ElemType e)
{
    Node *p=L;//保存前驱节点
    int i=0;
    while (i<pos-1)
    {
        i++;
        p=p->next;
        if (p==NULL)
        {
            return 0;
        }
    } 
    //需要插入的新节点
    Node *q = (Node*)malloc(sizeof(Node));
    q->data = e;
    q->prev = p;
    q->next = p->next;
    p->next->prev = q;
    p->next = q;
    return 1;
} 
//指定位置删除
int deleteNode(Node *L,int pos)
{
    Node *p=L;//要删除的指针前驱
    int i;
    while (i<pos-1)
    {
        i++;
        p=p->next;
        if (p==NULL)
        {
            return 0;
        }
    }
    Node *q=p->next;
    p->next=q->next;
    q->next->prev=p;
    free(q);
    return 1;
}
int main(int argc, char const *argv[])
{
    Node *list=initList();
    insertHead(list,10);
    insertHead(list,20);
    insertTail(list,30);
    insertTail(list,0);
    insertTail(list,60);
    listNode(list);
    return 0;
} */











//2026年1月20日07:45:19
//栈的顺序实现
/* #define MAXSIZE 100
typedef int ElemType;
typedef struct 
{
    ElemType data[MAXSIZE];//数组
    int top;
}Stack;
//初始化
void initStack(Stack *s)
{
    s->top=-1;//top保存的是栈顶元素的下标值，第一位才是0
}
//判断栈是否为空栈
int isEmpty(Stack *s)
{
    if (s->top=-1)
    {
        printf("空栈\n");
        return 1;
    }
    else
    {
        return 0;
    }
    
}
//压栈
int push(Stack *s,ElemType e)
{
    if (s->top>MAXSIZE-1)
    {
        printf("满了\n");
        return 0;
    }
    s->top++;
    s->data[s->top]=e;
    return 1;                   
}
//出栈
int push(Stack *s,ElemType *e)//e用来储存取出的值
{
    if (s->top=-1)
    {
        printf("空的\n");
        return 0;
    }
    *e=s->data[s->top];
    s->top--;
    return 1;                   
}
//获取栈顶元素
int push(Stack *s,ElemType *e)//e用来储存栈顶的值
{
    if (s->top=-1)
    {
        printf("空的\n");
        return 0;
    }
    *e=s->data[s->top];
    return 1;                   
} */

//栈的链式实现
/* typedef int ElemType ;
typedef struct stack
{
    ElemType data;
    struct stack *next;
}Stack;
Stack* initStack()
{
    Stack *s=(Stack*)malloc(sizeof(Stack));
    s->data=0;
    s->next=NULL;
    return s;
} */











//2026年1月22日12:04:18
//队列
/* #define MAXSIZE 100
typedef int Elemtype; */
/* typedef struct 
{
    Elemtype data[MAXSIZE];
    int front;
    int rear;
}Queue;

//初始化
void initQueue(Queue *Q)
{
    Q->front=0;
    Q->rear=0;
}
//判断队列是否为空
int isEmpty(Queue *Q)
{
    if (Q->front==Q->rear)
    {
        printf("空的\n");
        return 1;
    }
    else
    {
        return 0;
    }
}
//出对
Elemtype dequeue(Queue *Q)
{
    if (Q->front==Q->rear)
    {
        printf("空的\n");
        return 0;
    }
    else
    {
        Elemtype e=Q->data[Q->front];
        Q->front++;
        return e;
    } 
} 
//判断队列是否真的已满，调整队列
int queueFull(Queue *Q)
{
    if(Q->front>0)
    {
        int step=Q->front;//计算要移动的步数
        for(int i=Q->front;i<=Q->rear;++i)
        {
            Q->data[i-step]=Q->data[i];//将数组中的数据移位
        }
        Q->front=0;//队头归零
        Q->rear=Q->rear-step;//队尾
        return 1;
    }
    else
    {
        printf("满了\n");
        return 0;
    }
    
}
//入队
int equeue(Queue *Q,Elemtype e)
{
    if(Q->rear>=MAXSIZE)
    {
        if(!queueFull(Q))
        {
            return 0;
        }
    }
    Q->data[Q->rear]=e;
    Q->rear++;
    return 1;
}
//获取队头数据
int getHead(Queue *Q,Elemtype *e)
{
    if (Q->front==Q->rear)
    {
        printf("空的\n");
        return 0;
    }
    *e=Q->data[Q->front];
    return 1;  
} */


/* typedef struct 
{
    Elemtype *data;
    int front;
    int rear;
}Queue;

//堆内存初始化
Queue *initQueue()
{
    Queue *q=(Queue*)malloc(sizeof(Queue));
    q->data=(Elemtype*)malloc(sizeof(Elemtype)*MAXSIZE);
    q->front=0;
    q->rear=0;
    return q;
}
//循环队列
//入队
int equeue(Queue *Q,Elemtype e)
{
    if ((Q->rear+1)%MAXSIZE==Q->front)
    {
        printf("满了\n");
        return 0;
    }
    Q->data[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXSIZE;
    return 1;
}
//出队
int dequeue(Queue *Q,Elemtype *e)
{
    if(Q->front==Q->rear)
    {
        printf("空的\n");
        return 0;
    }
    *e=Q->data[Q->front];
    Q->front=(Q->front+1)%MAXSIZE;
    return 1;
} */

//队列的链式结构
//定义
/* typedef struct QueueNode
{
    Elemtype data;
    struct QueueNode *next;
}QueueNode;
typedef struct 
{
    QueueNode *front;//总是指向头结点
    QueueNode *rear;//总是指向尾节点
}Queue;
//初始化
Queue* initQueue()
{
    Queue *q=(Queue*)malloc(sizeof(Queue));
    QueueNode *node=(QueueNode*)malloc(sizeof(QueueNode));
    node->data=0;
    node->next=NULL;
    q->front=node;
    q->rear=node;
    return q;
}
//入队
void equeue(Queue *Q,Elemtype e)
{
    QueueNode *node=(QueueNode*)malloc(sizeof(QueueNode));
    node->data=e;
    node->next=NULL;
    Q->rear->next=node;
    Q->rear=node;
}
//出队
int dequeue(Queue *q, Elemtype *e)
{
    QueueNode *node = q->front->next;
    *e = node->data;
    q->front->next = node->next;
    if (q->rear == node)//如果出的是尾节点
    {
        q->rear = q->front;
    }
    free(node);
    return 1;
} 
//提取队头元素
int getFront(Queue *q)
{
    if (isEmpty(q))
    {
        printf("空的\n");
        return 0;
    }
    return q->front->next->data;
} */
