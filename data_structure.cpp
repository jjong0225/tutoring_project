#include "objects.h"
#include "data_structure.h"

// 1. UserTreeNode 대하여 Tree구조 형성 
UserTreeNode *search(UserTreeNode *root, int key) // 데이터에 대한 UserTreeNode 포인터 반환
{
    UserTreeNode *leftNode, *rightNode;
    if (root == nullptr)
        return nullptr;
    if(root->data.get_id() == key)
        return root;
    else if (root->data.get_id() < key)
        rightNode = search(root->right, key);
    else if (root->data.get_id() > key)
        leftNode = search(root->left, key);
    
    if(rightNode == nullptr && leftNode ==nullptr)
        return nullptr;
    else if(rightNode == nullptr)
        return leftNode;
    else
        return rightNode;
}

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
        list<Schedule>::iterator input = userNode.get_schedule_list().begin();
        for(int i=0; i< userNode.get_schedule_list().size(); i++){
            root->data.insert_schedule(*input);
        }
        return;
    }
    else{
        while (true)
        {
            UserTreeNode * tmpNode = this_node;
            if(this_node->data.get_id() < userNode.get_id() && this_node->right == nullptr)//루트노드 id 보다 크고 right가 null이면
            {
                this_node->right = new UserTreeNode
                {
                    User(userNode),
                    RED, nullptr, nullptr, nullptr
                };
                this_node = this_node->right;
                list<Schedule>::iterator input = userNode.get_schedule_list().begin();
                for(int i=0; i< userNode.get_schedule_list().size(); i++){
                    this_node->data.insert_schedule(*input);
                }
                this_node->parent = tmpNode;
                break;
            }
            else if(this_node->data.get_id() > userNode.get_id() && this_node->left == nullptr)//루트노드 id 보다 크고 right가 null이면
            {
                this_node->left = new UserTreeNode
                {
                    User(userNode),
                    RED, nullptr, nullptr, nullptr
                };
                this_node = this_node->left;
                list<Schedule>::iterator input = userNode.get_schedule_list().begin();
                for(int i=0; i< userNode.get_schedule_list().size(); i++){
                    this_node->data.insert_schedule(*input);
                }
                this_node->parent = tmpNode;
                break;
            }
            else if(this_node->data.get_id() < userNode.get_id())//루트노드 id 보다 크면
            {
                this_node = this_node->right;
            }
            else if(this_node->data.get_id() > userNode.get_id())//루트노드 id 보다 작으면
            {
                this_node = this_node->left;
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
void reviseTree(T *&root, T *node)
{
    //부모 노드가 레드인데, 부모님의 형제가 없거나 블랙일 때 - 회전
    //부모 노드가 레드인데, 부모님의 형제가 레드일 때 - 색상 변환
    T *now, *parent, *grand;
    now= node;
    parent= node->parent;
    grand= node->parent->parent;
    while (true)
    {
        if(now->parent->parent == nullptr || now->parent == nullptr) break;
        if(now->color == RED && now->parent->color==RED && (uncle(now)==nullptr || uncle(now)->color==BLACK))
        {//회전 
            if(now->data.get_id() > now->parent->data.get_id())
            {
                if(grand->data.get_id() > parent->data.get_id())
                {
                    grand->left= now;
                    now->parent= parent;
                    if (now->left != nullptr)
                    {
                        now->left->parent = parent;
                    }
                    parent->right = now->left;
                    now->left= parent;
                    parent->parent= now;
                }
                else if(grand->data.get_id() < parent->data.get_id())
                {
                    parent->color= BLACK;
                    grand->color= RED;
                    if(grand->parent == nullptr)
                    {
                        parent->parent = nullptr;
                        root = parent;
                    }
                    else{
                        if(grand->parent->right != nullptr && grand->data.get_id() > grand->parent->data.get_id())
                            grand->parent->right= parent;
                        else if(grand->parent->left != nullptr && grand->data.get_id() < grand->parent->data.get_id())
                            grand->parent->left= parent;
                        parent->parent= grand->parent;
                    }
                    grand->right= parent->left;
                    if(parent->left!=nullptr)
                        parent->left->parent= grand;
                    grand->parent = parent;
                    parent->left = grand;
                }
                now=parent;
                parent=now->parent;
                grand=parent->parent;
            }
            else if(now->data.get_id()==now->parent->left->data.get_id())
            {
                if(grand->data.get_id() > parent->data.get_id())
                {
                    parent->color= BLACK;
                    grand->color= RED;
                    if(grand->parent == nullptr)
                    {
                        parent->parent = nullptr;
                        root = parent;
                    }
                    else{
                        if(grand->parent->right != nullptr && grand->data.get_id() > grand->parent->data.get_id())
                            grand->parent->right= parent;
                        else if(grand->parent->left != nullptr && grand->data.get_id() < grand->parent->data.get_id())
                            grand->parent->left= parent;
                        parent->parent= grand->parent;
                    }
                    grand->left= parent->right;
                    if(parent->right != nullptr)
                    {
                        parent->right->parent= grand;
                    }
                    grand->parent= parent;
                    parent->right= grand;
                }
                else if(grand->data.get_id() < parent->data.get_id())//
                {
                    parent->color= BLACK;
                    grand->color= RED;
                    if(grand->parent == nullptr)
                    {
                        parent->parent = nullptr;
                        root = parent;
                    }
                    else{
                        if(grand->parent->right != nullptr && grand->data.get_id() > grand->parent->data.get_id())
                            grand->parent->right= parent;
                        else if(grand->parent->left != nullptr && grand->data.get_id() < grand->parent->data.get_id())
                            grand->parent->left= parent;
                        parent->parent= grand->parent;
                    }
                    grand->right= now;
                    now->parent= grand;
                    grand->parent= parent;
                    parent->left= grand;
                }
                break;
            }
        }
        else if(now->color == RED && now->parent->color==RED && uncle(now)->color==RED)
        {//색상변환
            now->parent->color=BLACK;
            uncle(now)->color=BLACK;
            if(now->parent->parent->parent != nullptr)//조부모가 루트가 아닐 때
                now->parent->parent->color = RED;
            now=now->parent;
            parent=now->parent;
            grand=parent->parent;
            break;
        }
        else
        {
            break;
        }
    }
}

void delete_node(UserTreeNode *root, int key)
{
    
}



// 2. MetroTreeNode에 대하여 Tree구조 형성 
// MetroTreeNode *search(MetroTreeNode *root, int key)
// {
//     MetroTreeNode *leftNode, *rightNode;
//     if (root == nullptr)
//         return nullptr;
//     if(root->data.station_code == key)
//         return root;
//     else if (root->data.station_code < key)
//         rightNode = search(root->right, key);
//     else if (root->data.station_code > key)
//         leftNode = search(root->left, key);
    
//     if(rightNode == nullptr && leftNode ==nullptr)
//         return nullptr;
//     else if(rightNode == nullptr)
//         return leftNode;
//     else
//         return rightNode;
// }

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