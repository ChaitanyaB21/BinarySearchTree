#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    // char name;
    int weight;
    struct Node *left;
    struct Node *right;
};

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
        p = (struct Node *)malloc(sizeof(struct Node));
        p->weight = weight;
        p->left = p->right = NULL;
        root = p;
        // free(p);
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

int findAncestor(int num1, int num2)
{
    struct Node *p;
    p = root;
    printf("\nWeight of the root is %d\n" , p->weight);
    while (p != NULL)
    {
        if (num1 <= p->weight && p->weight <= num2)
        {
            printf("\nInside first if statement\n");
            return p->weight;
            break;
        }

        else if (p->weight < num1 && p->weight < num2)
        {
            printf("\nInside sec if statement\n");
            p = p->right;
        }
        else if (p->weight > num1 && p->weight > num2)
        {
            printf("\nInside third if statement\n");
            p = p->left;
        }
        else{
            printf("\nJust continuing\n");
        }
    }

    free(p);
}

void Inorder(struct Node *p)
{
    if (p)
    {
        Inorder(p->left);
        printf("%d ", p->weight);
        Inorder(p->right);
    }
}

int main()
{
    int n;
    scanf("%d ", &n);
    int numLis[n];
    char strLis[n][20];

    for (int i = 0; i < n; i++)
    {
        scanf("%s", strLis[i]);
        scanf("%d", &numLis[i]);
    }

    // create(numLis, n);
    for (int i = 0; i < n; i++)
    {
        Insert(numLis[i]);
    };

    char str1[10];
    scanf("%s", str1);
    char str2[10];
    scanf("%s", str2);
    int index1;
    int index2;

    // printf("%s" , strLis[3]);

    for (int i = 0; i < n; i++)
    {
        if (!strcmp(strLis[i], str1)) // strcmp(strLis[i] , str1)
        {
            // printf("\nEntered first if statement i = %d\n" , i);
            index1 = i;
        }
        else if (!strcmp(strLis[i], str2))
        {
            // printf("\nEntered second if statement i = %d\n" , i);
            index2 = i;
        }
    };

    if(!strcmp(str1 , str2)){
        index2 = index1;
    }

    printf("These are the entered indexes %d %d\n" , index1 , index2);

    int finalInt;

    if (numLis[index1] < numLis[index2])
    {
        finalInt = findAncestor(numLis[index1], numLis[index2]);
    }
    else
    {
        finalInt = findAncestor(numLis[index2], numLis[index1]);
    }

    // int finalInt = findAncestor(numLis[index1], numLis[index2]);
    int intIndex;
    for (int i = 0; i < n; i++)
    {
        if (numLis[i] == finalInt)
        {
            intIndex = i;
        }
    }

    printf("%s", strLis[intIndex]);
    // Inorder(root);
    return 0;
}