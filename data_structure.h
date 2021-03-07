#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "objects.h"
#include <stack>

#define RED 1
#define BLACK 0
// 1. User객체를  저장하는 Tree인 UserTreeNode구현
typedef struct TreeNode {
  User data; // user의 id값을 바탕으로 tree 구성
  bool color;
  struct TreeNode *parent;
  struct TreeNode *left, *right;
} UserTreeNode;

UserTreeNode *search(UserTreeNode *node, int key);
void insert_node(UserTreeNode *&root, User &userNode);
void delete_node(UserTreeNode *root, int key);

template <typename T>
void reviseTree(T *&, T *);

template <typename T>
void print_node(T * root){
    stack<T*> s;
    s.push(root);
    while(!s.empty()){
        T* now = s.top();
        s.pop();
        printf("id: %d, color: %d\n", now->data.get_id(), now->color);
        if(now->right != nullptr)
            s.push(now->right);
        if(now->left != nullptr)
            s.push(now->left);
    }
}

// 2. Metro객체를  저장하는 Tree인 MetroTreeNode구현
// 위의 구현과 똑같이 하면 된다. 단 참조하는 데이터가 달라진다는 점만 유의!
typedef struct TreeNode_2 {
  Metro data; // metro의 id값을 바탕으로 tree 구성
  bool color;
  struct TreeNode_2 *parent;
  struct TreeNode_2 *left, *right;
} MetroTreeNode;

MetroTreeNode *search(MetroTreeNode *node, int key);
void insert_node(MetroTreeNode *&root, Metro &metroNode);
void delete_node(MetroTreeNode *root, int key);



// 3. 역간의 연결을 표현하는 Graph
typedef struct node
{
    int station_id;
    vector<pair<struct node *, int>>station_ptr; // (연결된 역, 걸리는 시간) 쌍의 벡터
} Node;
#endif