#include "objects.h"
#include "data_structure.h"
#include <iostream>
// 1. UserTreeNode 대하여 Tree구조 형성 

void insert_node(UserTreeNode *&root, User &userNode)
{
    UserTreeNode * this_node = root;
    if(root == NULL){    //루트노드인지 판별
        //동적할당 
        root = new UserTreeNode
        {
            User(userNode),
            BLACK, nullptr, nullptr, nullptr
        };
        list<Schedule> input_list = userNode.get_schedule_list();
        list<Schedule>::iterator input = input_list.begin();
        for(int i=0; i< input_list.size(); i++){
            root->data.insert_schedule(*input);
            input++;
        }
        return;
    }
    else{
        int user_id = userNode.get_id();
        while (true)
        {
            UserTreeNode * tmpNode = this_node;
            int this_id = this_node->data.get_id();
            int flag = 0;
            if(this_id < user_id)//루트노드 id 보다 크면
            {
                if(this_node->right != nullptr)
                    this_node = this_node->right;
                else
                    flag = 1;
            }
            else if(this_id > user_id)//루트노드 id 보다 작으면
            {
                if(this_node->left != nullptr)
                    this_node = this_node->left;
                else
                    flag = 2;
            }

            if(flag != 0)
            {
                UserTreeNode * new_node = new UserTreeNode
                {
                    User(userNode),
                    RED, nullptr, nullptr, nullptr
                };
                list<Schedule> input_list = userNode.get_schedule_list();
                list<Schedule>::iterator input = input_list.begin();
                for(int i=0; i< input_list.size(); i++){
                    new_node->data.insert_schedule(*input);
                    input++;
                }
                if(flag == 1)
                {
                    this_node -> right = new_node;
                    new_node -> parent = this_node;
                    this_node = this_node -> right;
                }
                if(flag == 2)
                {
                    this_node -> left = new_node;
                    new_node -> parent = this_node;
                    this_node = this_node -> left;
                }
                break;
            }
        }
    }
    reviseTree(root, this_node);//리스트럭쳐 리컬러링 확인/적용 함수 추가
}

template <typename T>
T *uncle(T * node)
{
    if(node->parent->data.get_id() < node->parent->parent->data.get_id())
        return node->parent->parent->right;
    else
        return node->parent->parent->left;
}

template <typename T>
T *parent(T * node)
{
    if(node == NULL)    
        return NULL;
    if(node -> parent == NULL)
        return NULL;
    return node -> parent;
}

template <typename T>
T *grandparent(T * node)
{
    T * tmp_node = parent(node);
    if(tmp_node == NULL) 
        return NULL;
    if(tmp_node->parent == NULL)
        return NULL;
    return tmp_node->parent;
}

template <typename T>
void recoloring(T *&root, T * node)
{
    T *now_node, *parent_node, *grand_node, *uncle_node;
    now_node= node;
    parent_node = parent(now_node);
    grand_node = grandparent(now_node);
    uncle_node = uncle(now_node);

    parent_node->color = BLACK;
    uncle_node->color = BLACK;
    grand_node->color = RED;
    reviseTree(root, grand_node);
}

template <typename T>
void rotate_left(T *&root, T * n)
{
    T *c, *p;
    c = n -> right;
    p = n -> parent;
    if(c->left != NULL)
        c->left->parent = n;
    
    n->right = c->left;
    n->parent = c;
    c->left = n;
    c->parent = p;

    if (p != NULL) {
        if (p->left == n)
            p->left = c;
        else
            p->right = c;
    }    
    else
        root = c;
}

template <typename T>
void rotate_right(T *&root, T * n)
{
    T *c, *p;
    c = n -> left;
    p = n -> parent;
    if(c->right != NULL)
        c->right->parent = n;
    
    n->left = c->right;
    n->parent = c;
    c->right = n;
    c->parent = p;

    if (p != NULL) {
        if (p->right == n)
            p->right = c;
        else
            p->left = c;
    }    
    else
        root = c;
}

template <typename T>
T *sibling(T * n)
{
    if(n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

template <typename T>
void replace_node(T *n, T *child)
{
    child->parent = n -> parent;
    if(n->parent->left == n)
        n->parent->left = child;
    else if(n->parent->right == n)
        n->parent->right = child;
}

template <typename T>
void delete_one_child(T *n, T *root)
{
    T *child;
    if(n -> right == NULL) 
        child = n -> left;
    else
        child = n -> right;
    replace_node(n, child);

    if(n->color == BLACK)
    {
        if(child->color == RED) // 루트 체크
            child->color = BLACK;
        else
            delete_case1(child, root);
    }
    free(n);
}

template <typename T>
void delete_case1(T *n, T *root)
{
    if(n->parent != NULL)
        delete_case2(n, root);
}

template <typename T>
void delete_case2(T *n, T *root)
{
    if(n->parent != NULL) // Sibilling
    {
        T *s = sibling(n);
        if(s->color == RED)
        {
            n->parent->color = RED;
            s->color = BLACK;
            if(n == n->parent->left)
                rotate_left(n->parent, root);
            else
                rotate_right(n->parent, root);
        }
    }
    delete_case3(n, root);
}

template <typename T>
void delete_case3(T *n, T *root)
{
    T *s = sibling(n);
    if((n->parent->color == BLACK) && (s->color == BLACK) 
    && (s->left->color == BLACK) && (s->right->color == BLACK))
        {
            s->color = RED;
            delete_case1(n->parent, root);
        }
    else
        delete_case4(n, root);
}

template <typename T>
void delete_case4(T *n, T *root)
{
    T *s = sibling(n);

    if((n->parent->color == RED) && (s->color == BLACK) &&
    (s->left->color == BLACK) && (s->right->color == BLACK))
    {
        s->color = RED;
        n->parent->color = BLACK;
    }
    else
        delete_case5(n, root);
}

template <typename T>
void delete_case5(T *n, T *root)
{
    T *s = sibling(n);
    if(s->color == BLACK)
    {
        if((n == n->parent->left) && (s->right->color == BLACK) && s->left->color == RED)
        {
            s->color = RED;
            s->left->color = BLACK;
            rotate_right(s, root);
        }else if ((n == n->parent->right) && (s->left->color == BLACK) && (s->right->color == RED))
        {
            s->color = RED;
            s->right->color = BLACK;
            rotate_left(s, root);
        }
    }
    delete_case6(n, root);
}

template <typename T>
void delete_case6(T *n, T *root)
{
    T *s = sibling(n);
    s->color = n->parent->color;
    n->parent->color = BLACK;
    if(n == n->parent->left)
    {
        s->right->color = BLACK;
        rotate_left(n->parent, root);
    }
    else
    {
        s->left->color = BLACK;
        rotate_right(n->parent, root);
    }
}


template <typename T>
void reviseTree(T *&root, T *node)
{
    //부모 노드가 레드인데, 부모님의 형제가 없거나 블랙일 때 - 회전
    //부모 노드가 레드인데, 부모님의 형제가 레드일 때 - 색상 변환
    if(node->parent == NULL)
    {
        node -> color = BLACK;
        return;
    }
    if(node->parent->color == BLACK)
        return;
 
    T *now_node, *parent_node, *grand_node, *uncle_node;
    now_node= node;
    parent_node = parent(now_node);
    grand_node = grandparent(now_node);
    uncle_node = uncle(now_node);

    if(uncle_node != NULL && uncle_node->color == RED)
        recoloring(root, now_node);
    else
    {
        if(now_node == parent_node->right && parent_node == grand_node->left)
        {
            rotate_left(root, parent_node);
            now_node = now_node -> left;
        }
        else if(now_node == parent_node->left && parent_node == grand_node->right)
        {
            rotate_right(root, parent_node);
            now_node = now_node -> right;
        }
        grand_node = grandparent(now_node);
        parent_node = parent(now_node);
        parent_node->color = BLACK;
        grand_node->color = RED;
        if(now_node == parent_node->left)
            rotate_right(root, grand_node);
        else
            rotate_left(root, grand_node);
    }
}

void delete_node(UserTreeNode *root, int key)
{
    UserTreeNode *now_node = search(root, key);
    if(now_node == NULL || now_node->data.get_id() != key)
    {
        std::cout << "Wrong station number error : Please enter the correct name of the station\n";
        return;
    }
    if(now_node->parent == NULL) // root는 제거 불가!
        return;

    if(now_node->left == NULL && now_node->right == NULL)
    {
        if(now_node->parent->left == now_node)
            now_node->parent->left = NULL;
        else
            now_node->parent->right = NULL;
        free(now_node);
        return;
    }

    UserTreeNode *successor_node = now_node -> right;
    if(successor_node == NULL)
        delete_one_child(now_node, root);
    else
    {
        while(successor_node->left != NULL)
            successor_node = successor_node->left;
        now_node->data = successor_node->data;
        delete_one_child(successor_node, root);
    }
}



// 2. MetroTreeNode에 대하여 Tree구조 형성 

void insert_node(MetroTreeNode *&root, Metro &metroNode)
{
    MetroTreeNode * this_node = root;
    if(root == NULL){    //루트노드인지 판별
        //동적할당 
        root = new MetroTreeNode
        {
            Metro(metroNode),
            BLACK, nullptr, nullptr, nullptr
        };
        list<Departure> input_list = metroNode.get_departure_list();
        list<Departure>::iterator input = input_list.begin();
        for(int i=0; i< input_list.size(); i++){
            root->data.insert_departure(*input);
            input++;
        }
        return;
    }
    else{
        int metro_id = metroNode.get_id();
        while (true)
        {
            MetroTreeNode * tmpNode = this_node;
            int this_id = this_node->data.get_id();
            int flag = 0;
            if(this_id < metro_id)//루트노드 id 보다 크면
            {
                if(this_node->right != nullptr)
                    this_node = this_node->right;
                else
                    flag = 1;
            }
            else if(this_id > metro_id)//루트노드 id 보다 작으면
            {
                if(this_node->left != nullptr)
                    this_node = this_node->left;
                else
                    flag = 2;
            }

            if(flag != 0)
            {
                MetroTreeNode * new_node = new MetroTreeNode
                {
                    Metro(metroNode),
                    RED, nullptr, nullptr, nullptr
                };
                list<Departure> input_list = metroNode.get_departure_list();
                list<Departure>::iterator input = input_list.begin();
                for(int i=0; i< input_list.size(); i++){
                    new_node->data.insert_departure(*input);
                    input++;
                }
                if(flag == 1)
                {
                    this_node -> right = new_node;
                    new_node -> parent = this_node;
                    this_node = this_node -> right;
                }
                if(flag == 2)
                {
                    this_node -> left = new_node;
                    new_node -> parent = this_node;
                    this_node = this_node -> left;
                }
                break;
            }
        }
    }
    reviseTree(root, this_node);//리스트럭쳐 리컬러링 확인/적용 함수 추가
}


void delete_node(MetroTreeNode *root, int key)
{
    MetroTreeNode *now_node = search(root, key);
    if(now_node == NULL || now_node->data.get_id() != key)
    {
        std::cout << "Wrong station number error : Please enter the correct name of the station\n";
        return;
    }
    if(now_node->parent == NULL) // root는 제거 불가!
        return;

    if(now_node->left == NULL && now_node->right == NULL)
    {
        if(now_node->parent->left == now_node)
            now_node->parent->left = NULL;
        else
            now_node->parent->right = NULL;
        free(now_node);
        return;
    }

    MetroTreeNode *successor_node = now_node -> right;
    if(successor_node == NULL)
        delete_one_child(now_node, root);
    else
    {
        while(successor_node->left != NULL)
            successor_node = successor_node->left;
        now_node->data = successor_node->data;
        delete_one_child(successor_node, root);
    }
}
