#include <stdio.h>
#include <stdlib.h>

struct Node
{
    
    int weight;
    struct Node *left;
    struct Node *right;
};

struct Queue
{
    int size;
    int front;
    int rear;
    struct Node **q;
};

void create(struct Queue *q, int size)
{
    q->size = size;
    q->q = (struct Node **)malloc(size * sizeof(struct Node *));
    q->front = q->rear = -1;
}

void enqueue(struct Queue *q, struct Node *x)
{
    if ((q->rear + 1) % q->size == q->front)
    {
    }
    else
    {
        q->rear = (q->rear + 1) % q->size;
        q->q[q->rear] = x;
    }
}

struct Node *dequeue(struct Queue *q)
{
    struct Node *x = NULL;
    if (q->front == q->rear)
    {
    }
    else
    {
        q->front = (q->front + 1) % q->size;
        x = q->q[q->front];
    }
    return x;
}

int isEmpty(struct Queue q)
{
    return q.front == q.rear;
}

struct Node *root = NULL;

void Insert(int weight)
{
    struct Node *t = root;
    struct Node *r = NULL, *p;

    p = (struct Node *)malloc(sizeof(struct Node));
    p->weight = weight;
    p->left = p->right = NULL;

    if (root == NULL)
    {
        
        root = p;
        return;
    }
    while (t != NULL)
    {
        r = t;
        if (weight < t->weight)
            t = t->left;
        else if (weight > t->weight)
            t = t->right;
        else
            return;
    }

    if (weight < r->weight)
        r->left = p;
    else
        r->right = p;
}

struct Node *InSucc(struct Node *p)
{
    while (p && p->left != NULL)
        p = p->left;
    return p;
}

struct Node *InPre(struct Node *p)
{
    while (p && p->right != NULL)
        p = p->right;
    return p;
}

struct Node *Delete(struct Node *p, int value)
{
    struct Node *q, *t;

    if (p == NULL)
    {
        return NULL;
    }

    if (p->left == NULL && p->right == NULL)
    {
        if (p == root)
        {
            root = NULL;
        }
        free(p);
        return NULL;
    }

    if (value < p->weight)
    {
        p->left = Delete(p->left, value);
    }
    else if (value > p->weight)
    {
        p->right = Delete(p->right, value);
    }
    else
    {
        q = InSucc(p->right);
        t = InPre(p->left);
        if (q)
        {
            p->weight = q->weight;
            p->right = Delete(p->right, q->weight);
        }
        else
        {
            p->weight = t->weight;
            p->left = Delete(p->left, t->weight);
        }
    }

    return p;
}

int Preorderarr[1000];
int arrindex = 0;

void Preorder(struct Node *p)
{
    

    if (p)
    {
        
        Preorderarr[arrindex++] = p->weight;
        Preorder(p->left);
        Preorder(p->right);
    }
}

void levelOrder(struct Node *p)
{
    struct Queue q;
    create(&q, 1000);
    
    enqueue(&q, p);
    while (!isEmpty(q))
    {
        p = dequeue(&q);
        if (p->left != NULL)
        {
            printf("%d ", p->left->weight);
            enqueue(&q, p->left);
        }
        if (p->right != NULL)
        {
            printf("%d ", p->right->weight);
            enqueue(&q, p->right);
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int A[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
        Insert(A[i]);
    }

    int del;
    scanf("%d", &del);
    int num;
    for (int i = 0; i < n; i++)
    {
        if (A[i] == del)
        {
            num = i + 1;
            break;
        }
    }

    if (num == n)
    {
        num = -1;
    }
    else
    {
        num = num;
    }

    Preorder(root);

    struct Node *p;
    p = Delete(root, del);

    levelOrder(root);
    int index;
    for (int i = 0; i < n; i++)
    {
        if (Preorderarr[i] == del)
        {
            index = i;

            break;
        }
    }

    if (index == n - 1)
    {
        printf("\n%d", -1);
    }
    else
    {
        printf("\n%d", Preorderarr[index + 1]);
    }

    return 0;
}
