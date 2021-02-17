#include "objects.h"

typedef struct TreeNode {
  User data; // user의 id값을 바탕으로 tree 구성
  struct TreeNode *left, *right;
} UserTreeNode;
 
UserTreeNode *search(UserTreeNode *node, int key);
void insert_node(UserTreeNode *root, int key);
void delete_node(UserTreeNode *root, int key);



typedef struct TreeNode_2 {
  Metro data; // metro의 id값을 바탕으로 tree 구성
  struct TreeNode_2 *left, *right;
} MetroTreeNode;
 
MetroTreeNode *search(MetroTreeNode *node, int key);
void insert_node(MetroTreeNode *root, int key);
void delete_node(MetroTreeNode *root, int key);