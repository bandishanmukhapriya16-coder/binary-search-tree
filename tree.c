/*
 * ============================================================
 *   BINARY SEARCH TREE (BST)
 *   Operations : Insert | Search | Traversals (In/Pre/Post)
 *
 *   BST Property : left child < parent < right child
 *
 *   Time  : O(log n) average  |  O(n) worst (skewed tree)
 *   Space : O(n) for tree     |  O(h) for recursion stack
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* ─────────────────────────────────────────────────────────────
   STRUCTURE : Node
   PURPOSE   : Represents one node in the BST
───────────────────────────────────────────────────────────── */
struct Node
{
    int         data;   /* value stored in this node     */
    struct Node *left;  /* pointer to left  child        */
    struct Node *right; /* pointer to right child        */
};

/* Shorter alias for convenience */
typedef struct Node Node;

/* ─────────────────────────────────────────────────────────────
   FUNCTION : createNode
   PURPOSE  : Allocate and initialise a new BST node
   RETURNS  : Pointer to the newly created node
───────────────────────────────────────────────────────────── */
Node* createNode(int value)
{
    Node *newNode = (Node*) malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("ERROR: Memory allocation failed!\n");
        exit(1);
    }

    newNode->data  = value;
    newNode->left  = NULL;   /* no children yet */
    newNode->right = NULL;

    return newNode;
}

/* ─────────────────────────────────────────────────────────────
   FUNCTION : insert
   PURPOSE  : Insert a value into the BST (recursive)
   RETURNS  : Pointer to the (possibly updated) root
   RULE     : Go left if value < node, right if value > node
───────────────────────────────────────────────────────────── */
Node* insert(Node *root, int value)
{
    /* Case 1: Tree is empty OR we reached the correct spot */
    if (root == NULL)
    {
        return createNode(value);  /* insert here */
    }

    /* Case 2: Value is smaller → go to left subtree */
    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }

    /* Case 3: Value is larger → go to right subtree */
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }

    /* Case 4: Duplicate value → ignore (no duplicates in BST) */
    else
    {
        printf("  Note: %d already exists. Duplicates ignored.\n", value);
    }

    return root;   /* return unchanged root */
}

/* ─────────────────────────────────────────────────────────────
   FUNCTION : search
   PURPOSE  : Search for a value in the BST (recursive)
   RETURNS  : Pointer to node if found, NULL if not found
───────────────────────────────────────────────────────────── */
Node* search(Node *root, int key)
{
    /* Base case 1: Empty tree or key not found */
    if (root == NULL)
    {
        return NULL;
    }

    /* Base case 2: Key matches current node */
    if (root->data == key)
    {
        return root;
    }

    /* Recursive case: search left or right based on BST property */
    if (key < root->data)
    {
        printf("  %d < %d → go LEFT\n",  key, root->data);
        return search(root->left,  key);
    }
    else
    {
        printf("  %d > %d → go RIGHT\n", key, root->data);
        return search(root->right, key);
    }
}

/* ─────────────────────────────────────────────────────────────
   TRAVERSALS
   In-order  : Left → Root → Right  (gives SORTED output)
   Pre-order : Root → Left → Right  (useful for copying tree)
   Post-order: Left → Right → Root  (useful for deletion)
───────────────────────────────────────────────────────────── */

void inOrder(Node *root)
{
    if (root == NULL) return;
    inOrder(root->left);       /* 1. visit left  */
    printf("%d ", root->data); /* 2. print root  */
    inOrder(root->right);      /* 3. visit right */
}

void preOrder(Node *root)
{
    if (root == NULL) return;
    printf("%d ", root->data); /* 1. print root  */
    preOrder(root->left);      /* 2. visit left  */
    preOrder(root->right);     /* 3. visit right */
}

void postOrder(Node *root)
{
    if (root == NULL) return;
    postOrder(root->left);     /* 1. visit left  */
    postOrder(root->right);    /* 2. visit right */
    printf("%d ", root->data); /* 3. print root  */
}

/* ─────────────────────────────────────────────────────────────
   FUNCTION : printTree
   PURPOSE  : Print a simple sideways view of the BST
   NOTE     : Rotated 90° — right subtree appears at top
───────────────────────────────────────────────────────────── */
void printTree(Node *root, int level)
{
    int i;

    if (root == NULL) return;

    printTree(root->right, level + 1);   /* right branch first */

    for (i = 0; i < level; i++)
        printf("    ");                   /* indentation */
    printf("[%d]\n", root->data);

    printTree(root->left, level + 1);    /* left branch last */
}

/* ─────────────────────────────────────────────────────────────
   FUNCTION : height
   PURPOSE  : Return the height of the BST (edge count)
───────────────────────────────────────────────────────────── */
int height(Node *root)
{
    int leftH, rightH;

    if (root == NULL)       return -1;   /* empty tree: -1 edges */
    if (root->left == NULL && root->right == NULL) return 0; /* leaf */

    leftH  = height(root->left);
    rightH = height(root->right);

    return 1 + (leftH > rightH ? leftH : rightH);
}

/* ─────────────────────────────────────────────────────────────
   FUNCTION : countNodes
   PURPOSE  : Return total number of nodes in BST
───────────────────────────────────────────────────────────── */
int countNodes(Node *root)
{
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

/* ─────────────────────────────────────────────────────────────
   MAIN
───────────────────────────────────────────────────────────── */
int main()
{
    Node *root = NULL;   /* start with empty tree */
    Node *found;
    int  value;

    printf("============================================\n");
    printf("       BINARY SEARCH TREE PROGRAM          \n");
    printf("============================================\n");

    /* ── Build the BST with some values ── */
    printf("\n--- Building BST ---\n");
    printf("Inserting values: 50, 30, 70, 20, 40, 60, 80\n\n");

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    /* ── Display tree structure ── */
    printf("\n--- BST Structure (rotated 90 degrees) ---\n");
    printf("(read from bottom to top = left to right)\n\n");
    printTree(root, 0);

    /* ── Tree statistics ── */
    printf("\n--- Tree Statistics ---\n");
    printf("  Total nodes : %d\n", countNodes(root));
    printf("  Height      : %d (edge count)\n", height(root));

    /* ── Traversals ── */
    printf("\n--- Traversals ---\n");

    printf("  In-order   (sorted): ");
    inOrder(root);
    printf("\n");

    printf("  Pre-order  (copy)  : ");
    preOrder(root);
    printf("\n");

    printf("  Post-order (delete): ");
    postOrder(root);
    printf("\n");

    /* ── Interactive Search ── */
    printf("\n============================================\n");
    printf("            SEARCH IN BST                  \n");
    printf("============================================\n");

    do
    {
        printf("\nEnter value to search (0 to quit): ");
        scanf("%d", &value);

        if (value == 0) break;

        printf("\n  Searching for %d ...\n", value);
        found = search(root, value);

        if (found != NULL)
            printf("  ✔ %d FOUND in the BST!\n", value);
        else
            printf("  ✘ %d NOT FOUND in the BST.\n", value);

    } while (1);

    /* ── Interactive Insert ── */
    printf("\n============================================\n");
    printf("            INSERT INTO BST                \n");
    printf("============================================\n");

    do
    {
        printf("\nEnter value to insert (0 to quit): ");
        scanf("%d", &value);

        if (value == 0) break;

        root = insert(root, value);

        printf("\n  Updated BST Structure:\n\n");
        printTree(root, 0);

        printf("\n  In-order: ");
        inOrder(root);
        printf("\n");

    } while (1);

    printf("\n--- Final BST ---\n");
    printTree(root, 0);
    printf("\nTotal nodes: %d  |  Height: %d\n",
           countNodes(root), height(root));

    printf("\nProgram ended.\n");

    return 0;
}

/*
 * ============================================================
 *   SAMPLE RUN
 *   Inserted: 50, 30, 70, 20, 40, 60, 80
 *
 *   Tree structure:
 *           [80]
 *       [70]
 *           [60]
 *   [50]
 *           [40]
 *       [30]
 *           [20]
 *
 *   In-order   : 20 30 40 50 60 70 80   ← always sorted!
 *   Pre-order  : 50 30 20 40 70 60 80
 *   Post-order : 20 40 30 60 80 70 50
 *
 *   Search 40 :
 *     40 < 50 → go LEFT
 *     40 > 30 → go RIGHT
 *     ✔ 40 FOUND!
 * ============================================================
 */