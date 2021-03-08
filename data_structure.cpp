#include "objects.h"
#include "data_structure.h"

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
        list<Departure>::iterator input = metroNode.get_departure_list().begin();
        for(int i=0; i< metroNode.get_departure_list().size(); i++){
            root->data.insert_departure(*input);
        }
		return;
    }
    else{
        while (true)
        {
            MetroTreeNode * tmpNode = this_node;
            if(this_node->data.get_id() < metroNode.get_id() && this_node->right == nullptr)//루트노드 id 보다 크고 right가 null이면
            {
                this_node->right = new MetroTreeNode
                {
                    Metro(metroNode),
                    RED, nullptr, nullptr, nullptr
                };
                this_node = this_node->right;
                list<Departure>::iterator input = metroNode.get_departure_list().begin();
                for(int i=0; i< metroNode.get_departure_list().size(); i++){
                    this_node->data.insert_departure(*input);
                }
                this_node->parent = tmpNode;
                break;
            }
            else if(this_node->data.get_id() > metroNode.get_id() && this_node->left == nullptr)//루트노드 id 보다 크고 right가 null이면
            {
                this_node->left = new MetroTreeNode
                {
                    Metro(metroNode),
                    RED, nullptr, nullptr, nullptr
                };
                this_node = this_node->left;
                list<Departure>::iterator input = metroNode.get_departure_list().begin();
                for(int i=0; i< metroNode.get_departure_list().size(); i++){
                    this_node->data.insert_departure(*input);
                }
                this_node->parent = tmpNode;
                break;
            }
            else if(this_node->data.get_id() < metroNode.get_id())//루트노드 id 보다 크면
            {
                this_node = this_node->right;
            }
            else if(this_node->data.get_id() > metroNode.get_id())//루트노드 id 보다 작으면
            {
                this_node = this_node->left;
            }
        }
    }
    reviseTree(root, this_node);//리스트럭쳐 리컬러링 확인/적용 함수 추가
}

void delete_node(MetroTreeNode *root, int key)
{
}