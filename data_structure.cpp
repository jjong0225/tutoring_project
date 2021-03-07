#include "objects.h"
#include "data_structure.h"

void LeftR(UserTreeNode *root);
void LeftR2(MetroTreeNode *root);
void RigR(UserTreeNode *root);
void RigR2(MetroTreeNode *root);


// 1. UserTreeNode 대하여 Tree구조 형성 
UserTreeNode *search(UserTreeNode *root, int key) // 데이터에 대한 UserTreeNode 포인터 반환
{
	UserTreeNode* temp;
	return temp;
}

void insert_node(UserTreeNode *root, int key)
{
}

void delete_node(UserTreeNode *root, int key)
{
	UserTreeNode *remove = root;
	UserTreeNode *change;
	UserTreeNode *check;
	check = root;
	bool colorcheck;


	//지울노드 찾기
	while(root->data.get_id() != key){
		if(root->data.get_id() < key){
			root = root->right;
		}
		else{
			root = root-> left;
		}
	}

	remove = root;
	colorcheck = root->color;

	//노드 삭제하기
	if(root->left == NULL && root->right == NULL){
		if(root->parent->left == root){
			root->parent->left = NULL;
		} 
		else{
			root->parent->right = NULL;
		}
	}
	else if(root->left == NULL && root->right != NULL){
		if(root->parent->left == root){
			root->parent->left = root->right;
			root->right->parent = root->parent;
			root = root->right;
		} 
		else{
			root->parent->right = root->right;
			root->right->parent = root->parent;
			root = root->right;
		}
	}
	else if(root->left != NULL && root->right == NULL){
		if(root->parent->left == root){
			root->parent->left = root->left;
			root->left->parent = root->parent;
			root = root->left;
		} 
		else{
			root->parent->right = root->left;
			root->left->parent = root->parent;
			root = root->left;
		}
	}
	else{  //자식2개있을때
		remove = remove->right;

		while(remove->left != NULL){
			remove = remove->left;
		}
		
		if(remove->right != NULL){
			remove->parent->left = remove->right;
			remove->right->parent = remove->parent;
			remove->parent = NULL;
		}
		else{
			remove->parent->left = NULL;
			remove->parent = NULL;
		}
		if(root->parent->left == root){
			root->parent->left = remove;
			remove->left = root->left;
			remove->right = root->right;
			remove->parent = root->parent;

			root = remove;
		} 
		else{
			root->parent->right = remove;
			remove->left = root->left;
			remove->right = root->right;
			remove->parent = root->parent;
			root = remove;
		}
	}
	//왼쪽에 있는 경우와 오른쪽에 있는 경우를 분리해서 red_black트리 조건 충족시키기

	
	if(colorcheck == BLACK){
		while(root != check && root->color == BLACK){

			if(root->parent->left == root){  //case 1
				if(root->parent->right->color == RED){
					root->parent->right->color = BLACK;
					root->parent->color = RED;
					change = root->parent;
					LeftR(root->parent);

				} //case 2
				if(root->parent->right->color == BLACK && root->parent->right->left->color ==BLACK&&root->parent->right->right->color ==BLACK){
					root->parent->right->color = RED;
					root = root->parent;
				} //case3
				else{
					if(root->parent->right->color == BLACK&& root->parent->right->left->color == RED && root->parent->right->right->color == BLACK){
						root->parent->right->color = RED;
						root->parent->right->left->color= BLACK;
						RigR(root->parent->right);



					}
					//case4
					root->parent->right->color = root->parent->color;
					root->parent = BLACK;
					root->parent->right->right->color = BLACK;
					LeftR(root->parent);
					root = check;


					
				}
			}

			else{ //오른쪽자식일때
				if(root->parent->left->color == RED){ //case1
					root->parent->left->color = BLACK;
					root->parent->color = RED;
					RigR(root->parent);

				} //case 2
				if(root->parent->left->color == BLACK && root->parent->left->left->color ==BLACK&&root->parent->left->right->color ==BLACK){
					root->parent->left->color = RED;
					root = root->parent;

				} //case3
				else{
					if(root->parent->left->color == BLACK&& root->parent->left->left->color == RED && root->parent->left->right->color == BLACK){
						root->parent->left->color = RED;
						root->parent->left->left->color= BLACK;
						LeftR(root->parent->left);
						


					}//case4
					
					root->parent->left->color = root->parent->color;
					root->parent = BLACK;
					root->parent->left->left->color = BLACK;
					RigR(root->parent);
					root = check;


					
				}

			}
		}
		root->color = BLACK;
		root->color = BLACK;

	}


}

// 2. MetroTreeNode에 대하여 Tree구조 형성 
MetroTreeNode *search(MetroTreeNode *root, int key)
{
	MetroTreeNode* temp;
	return temp;
}

void insert_node(MetroTreeNode *root, int key)
{
}

void delete_node(MetroTreeNode *root, int key)
{
	MetroTreeNode *remove = root;
	MetroTreeNode *change;
	MetroTreeNode *check;
	check = root;
	bool colorcheck;


	//지울노드 찾기
	while(root->data.get_id() != key){
		if(root->data.get_id() < key){
			root = root->right;
		}
		else{
			root = root-> left;
		}
	}

	remove = root;
	colorcheck = root->color;

	//노드 삭제하기
	if(root->left == NULL && root->right == NULL){
		if(root->parent->left == root){
			root->parent->left = NULL;
		} 
		else{
			root->parent->right = NULL;
		}
	}
	else if(root->left == NULL && root->right != NULL){
		if(root->parent->left == root){
			root->parent->left = root->right;
			root->right->parent = root->parent;
			root = root->right;

		} 
		else{
			root->parent->right = root->right;
			root->right->parent = root->parent;
			root = root->right;
		}
	}
	else if(root->left != NULL && root->right == NULL){
		if(root->parent->left == root){
			root->parent->left = root->left;
			root->left->parent = root->parent;
			root = root->left;
		} 
		else{
			root->parent->right = root->left;
			root->left->parent = root->parent;
			root = root->left;
		}
	}
	else{  //자식2개있을때
		remove = remove->right;

		while(remove->left != NULL){
			remove = remove->left;
		}
		
		if(remove->right != NULL){
			remove->parent->left = remove->right;
			remove->right->parent = remove->parent;
			remove->parent = NULL;
		}
		else{
			remove->parent->left = NULL;
			remove->parent = NULL;
		}
		if(root->parent->left == root){
			root->parent->left = remove;
			remove->left = root->left;
			remove->right = root->right;
			remove->parent = root->parent;
			root = remove;
		} 
		else{
			root->parent->right = remove;
			remove->left = root->left;
			remove->right = root->right;
			remove->parent = root->parent;
			root = remove;
		}
	}
	//왼쪽에 있는 경우와 오른쪽에 있는 경우를 분리해서 red_black트리 조건 충족시키기

	
	if(colorcheck == BLACK){
		while(root != check && root->color == BLACK){

			if(root->parent->left == root){  //case 1
				if(root->parent->right->color == RED){
					root->parent->right->color = BLACK;
					root->parent->color = RED;
					change = root->parent;
					LeftR2(root->parent);

				} //case 2
				if(root->parent->right->color == BLACK && root->parent->right->left->color ==BLACK&&root->parent->right->right->color ==BLACK){
					root->parent->right->color = RED;
					root = root->parent;
				} //case3
				else{
					if(root->parent->right->color == BLACK&& root->parent->right->left->color == RED && root->parent->right->right->color == BLACK){
						root->parent->right->color = RED;
						root->parent->right->left->color= BLACK;
						RigR2(root->parent->right);



					}
					//case4
					root->parent->right->color = root->parent->color;
					root->parent = BLACK;
					root->parent->right->right->color = BLACK;
					LeftR2(root->parent);
					root = check;


					
				}
			}

			else{ //오른쪽자식일때
				if(root->parent->left->color == RED){ //case1
					root->parent->left->color = BLACK;
					root->parent->color = RED;
					RigR2(root->parent);

				} //case 2
				if(root->parent->left->color == BLACK && root->parent->left->left->color ==BLACK&&root->parent->left->right->color ==BLACK){
					root->parent->left->color = RED;
					root = root->parent;

				} //case3
				else{
					if(root->parent->left->color == BLACK&& root->parent->left->left->color == RED && root->parent->left->right->color == BLACK){
						root->parent->left->color = RED;
						root->parent->left->left->color= BLACK;
						LeftR2(root->parent->left);
						


					}//case4
					
					root->parent->left->color = root->parent->color;
					root->parent = BLACK;
					root->parent->left->left->color = BLACK;
					RigR2(root->parent);
					root = check;


					
				}

			}
		}
		root->color = BLACK;
		root->color = BLACK;

	}
}

// 왼쪽 회전
void LeftR(UserTreeNode *root){ // 원래 루트의 부모를 받아서 오기
	UserTreeNode *b;
	UserTreeNode *c;

	b = root->right;
	c = b->left;
	b->parent = root->parent;
	if(root->parent->left == root){
			root->parent->left = b;
	}
	else if(root->parent->right == root){
		root->parent->right = b;
	}

	b->left = root;
	root->right = c;
	root->parent = b;
	if(c != NULL){
		c->parent = root;
	}

}

void LeftR2(MetroTreeNode *root){ // 원래 루트의 부모를 받아서 오기
	MetroTreeNode *b;
	MetroTreeNode *c;

	b = root->right;
	c = b->left;
	b->parent = root->parent;
	if(root->parent->left == root){
			root->parent->left = b;
	}
	else if(root->parent->right == root){
		root->parent->right = b;
	}

	b->left = root;
	root->right = c;
	root->parent = b;
	if(c != NULL){
		c->parent = root;
	}

}


void RigR(UserTreeNode *root){  // 오른쪽 회전
	UserTreeNode *b;
	UserTreeNode *c;

	b = root->left;
	c = b->right;

	b->parent = root->parent;
	if(root->parent->left == root){
			root->parent->left = b;
	}
	else if(root->parent->right == root){
		root->parent->right = b;
	}

	b->right = root;
	root->left = c;
	root->parent = b;
	if(c != NULL){
		c->parent = root;
	}

}

void RigR2(MetroTreeNode *root){  // 오른쪽 회전
	MetroTreeNode *b;
	MetroTreeNode *c;

	b = root->left;
	c = b->right;

	b->parent = root->parent;
	if(root->parent->left == root){
			root->parent->left = b;
	}
	else if(root->parent->right == root){
		root->parent->right = b;
	}

	b->right = root;
	root->left = c;
	root->parent = b;
	if(c != NULL){
		c->parent = root;
	}

}

