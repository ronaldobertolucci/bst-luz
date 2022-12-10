#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct tree 
{
    struct node *root;
};

typedef struct node Node;
typedef struct tree Tree;

Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Tree *createTree()
{
    Tree *tree = malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

void insert(Tree *tree, int data)
{
    Node *current = NULL;
    Node *parent = NULL;
    if (tree->root == NULL)
        tree->root = createNode(data);
    else
    {
        current = tree->root;
        while (current != NULL)
        {
            parent = current;
            if (data < current->data)
                current = current->left;
            else
                current = current->right;
        }
        if (data < parent->data)
            parent->left = createNode(data);
        else
            parent->right = createNode(data);
    }
}

void preorderUtil(Node *root) //r-e-d
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorderUtil(root->left);
    preorderUtil(root->right);
}

void preorder(Tree *tree) 
{
    printf("\n");
    preorderUtil(tree->root);
    printf("\n");
}

void inorderUtil(Node *root) //e-r-d
{
    if (root == NULL)
        return;

    inorderUtil(root->left);
    printf("%d ", root->data);
    inorderUtil(root->right);
}

void inorder(Tree *tree) 
{
    printf("\n");
    inorderUtil(tree->root);
    printf("\n");
}

void postorderUtil(Node *root) //e-d-r
{
    if (root == NULL)
        return;

    postorderUtil(root->left);
    postorderUtil(root->right);
    printf("%d ", root->data);
}

void postorder(Tree *tree)
{
    printf("\n");
    postorderUtil(tree->root);
    printf("\n");
}

Node *minLeftValue(Node *root)
{
    Node *current = root;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, int data)
{

    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = minLeftValue(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int totalNodes(Node *root)
{
    if (root == NULL)
        return 0;
    else
        return (totalNodes(root->left) + totalNodes(root->right) + 1);
}

int Height(Node *root)
{
    int leftHeight, rightHeight;
    if (root == NULL)
        return -1;

    leftHeight = Height(root->left);
    rightHeight = Height(root->right);

    if (leftHeight > rightHeight)
        return (leftHeight + 1);
    else
        return (rightHeight + 1);
}

void deleteTree(Tree *tree)
{
    if (tree->root != NULL)
    {
        // postorder
        deleteTree(tree->root->left);
        deleteTree(tree->root->right);
        free(tree->root);
    }
    else
        free(tree);
}

void clearBuffer() {
    while (getchar() != '\n');    
}

void leftViewUtil(Node *root, int level, int *max)
{
    // a ideia é printar o primeiro elemento em cada nível

    if (root == NULL)
        return;
    
    if (*max < level) { // rastrear o max_level
        printf("%d ", root->data);
        *max = level; // aumentar o max_level
    }
    
    // primeiro passar pelo esquerdo, pois, se encontrar, não printará o direito, pois max incrementou
    leftViewUtil(root->left, level + 1, max);
    leftViewUtil(root->right, level + 1, max);
}
 
void leftView(Tree *tree)
{
    int max = 0;
    printf("\n");
    leftViewUtil(tree->root, 1, &max);
    printf("\n");
}

void menu(Tree *tree) 
{
    int i, tn, height;
    int option;
    
    do
    {
        printf("\nEscolha : ");
        printf("\n1 - Inserir elemento");
        printf("\n2 - Pre-ordem");
        printf("\n3 - Ordem");
        printf("\n4 - Pos-ordem");
        printf("\n5 - Excluir elemento pelo valor");
        printf("\n6 - Total de nodes");
        printf("\n7 - Altura da arvore");
        printf("\n8 - Esquerda da arvore");
        printf("\n0 - Apagar lista e sair\n\n");
        scanf("%d", &option);
        clearBuffer();

        switch (option)
        {
        case 1:
            printf("\nInsira o valor do elemento: ");
            scanf("%d", &i);
            insert(tree, i);
            clearBuffer();
            break;
        case 2:
            preorder(tree);
            break;
        case 3:
            inorder(tree);
            break;
        case 4:
            postorder(tree);
            break;
        case 5:
            printf("\nEscolha o elemento a apagar: ");
            scanf("%d", &i);
            clearBuffer();
            tree->root = deleteNode(tree->root, i);
            break;
        case 6:
            tn = totalNodes(tree->root);
            printf("\nO total de nodes: %d\n", tn);
            break;
        case 7:
            height = Height(tree->root);
            printf("\nA altura da arvore: %d\n", height);
            break;
        case 8:
            leftView(tree);
            break;
        case 0:
            deleteTree(tree);
            break;
        default:
            printf("\nIncorreto. Tente novamente.\n");
            break;
        }
    } while (option != 0);
}

int main()
{
    Tree *tree = createTree();
    menu(tree);
}