#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "objects.h"

// 1. User객체를  저장하는 Tree인 UserTreeNode구현
typedef struct TreeNode {
  User data; // user의 id값을 바탕으로 tree 구성
  struct TreeNode *left, *right;
} UserTreeNode;

UserTreeNode *search(UserTreeNode *node, int key);
void insert_node(UserTreeNode *root, int key);
void delete_node(UserTreeNode *root, int key);



// 2. Metro객체를  저장하는 Tree인 MetroTreeNode구현
// 위의 구현과 똑같이 하면 된다. 단 참조하는 데이터가 달라진다는 점만 유의!
typedef struct TreeNode_2 {
  Metro data; // metro의 id값을 바탕으로 tree 구성
  struct TreeNode_2 *left, *right;
} MetroTreeNode;

MetroTreeNode *search(MetroTreeNode *node, int key);
void insert_node(MetroTreeNode *root, int key);
void delete_node(MetroTreeNode *root, int key);



// 3. 역간의 연결을 표현하는 Graph
typedef struct node
{
    int station_id;
    vector<tuple<int,struct node *, int>>station_ptr; // (연결된 역, 걸리는 시간) 쌍의 벡터
} Node;
#endif
