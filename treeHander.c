#include "treeHander.h"

//创建新节点
linkTree CreateNode(int data){
	linkTree lnew = (linkTree)malloc(sizeof(treenode));

	if(lnew != NULL){
		lnew->data = data;
		lnew->lchild = lnew->rchild = lnew->parent = lnew->uncle = NULL;
		lnew->color = red;

		return lnew;
	}

	return NULL;
}

/************************************************************************************************
 * 插入节点使用的函数
 ************************************************************************************************/
void rb_rotate_left(linkTree *proot,linkTree anew){
	linkTree rchild = anew->rchild,
			 parent = anew->parent;
	
	anew->rchild = rchild->lchild;
	rchild->lchild = anew;
	anew->parent = rchild;
	rchild->parent = parent;
	if(parent == NULL){
		*proot = rchild;
	}else{
		if(parent->lchild == anew){
			parent->lchild = rchild;
		}else if(parent->rchild == anew){
			parent->rchild = rchild;
		}
	}
}

void rb_rotate_right(linkTree *proot,linkTree anew){
	linkTree lchild = anew->lchild,
			 parent = anew->parent;

	anew->lchild = lchild->rchild;
	lchild->rchild = anew;
	anew->parent = lchild;
	lchild->parent = parent;
	if(parent == NULL){
		*proot = lchild;
	}else{
		if(parent->lchild == anew){
			parent->lchild = lchild;
		}else if(parent->rchild == anew){
			parent->rchild = lchild;
		}
	}
}

linkTree bst_insert(linkTree root, lintTree anew){
	if(root == NULL){
		return anew;
	}

	anew->parent = root;
	if(root->data > anew->data){
		root->lchild = bst_insert(root->lchild, anew);
	}else if(root->data < anew->data){
		root->rchild = bst_insert(root->rchild, anew);
	}else{
		printf("%d exist.\n", anew->data);
	}

	return root;
}

//获取节点的uncle
linkTree uncle(linkTree node){
	linkTree parent = node->parent;
	linkTree grandPa = NULL;
	linkTree uncle = NULL;
	
	if(parent == NULL){
		return NULL;
	}

	grandPa = parent->parent;
	uncle =  grandPa!=NULL ? (grandPa->lchild== parent ? grandPa->rchild : grandPa->lchild) : NULL;

	return uncle;
}

//获取节点的grandpa
linkTree grandpa(linkTree node){
	linkTree parent = node->parent;

	return (parent!=NULL ? parent->parent : NULL)
}

void insert_case3(linkTree *root,linkTree anew){
	//红父 + 黑叔
	anew->parent->color = black;
	grandpa(anew)->color = red;

	if(anew==anew->parent->lchild && anew->parent==grandpa(anew)->lchild){
		rb_rotate_right(root, anew->parent);
	}else{
		rb_rotate_left(root, anew->parent);
	}
}

void insert_case2(linkTree *root,linkTree anew){
	//红父 + 黑叔
	if(anew==anew->parent->rchild && anew->parent==grandpa(anew)->lchild){
		rb_rotate_left(root,anew);
		anew = anew->lchild;
	}else if(anew==anew->parent->lchild && anew->parent==grandpa(anew)->rchild){
		rb_rotate_right(root, anew);
		anew = anew->rchild;
	}

	insert_case3(root, anew);
}

void insert_case1(linkTree *root,linkTree anew){
	//红父 + 红叔
	if(uncle(anew)!=NULL && uncle(anew)->color==red){
		anew->parent->color = black;
		uncle(anew)->color = black;
		grandpa(anew)->color = red;

		insert_fixup(root,grandpa(anew));
	}else{
		insert_case2(root, anew);
	}
}

void insert_fixup(linkTree *root,linkTree anew){
	if(anew->parent == NULL){
		anew->color = black;
		*root = anew;
		return;
	}

	if(anew->parent->color == black){
		return;
	}else{
		insert_case1(root, anew);
	}
}
/********************** end *********************/

//插入节点
linkTree InsertNode(linkTree anew,linkTree *root){
	*root = bst_insert(*root, anew);
	insert_fixup(root, anew);
}

//删除节点
linkTree DelNode(linkTree *root,int sdata){
}
