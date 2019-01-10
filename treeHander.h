#ifndef _RED_BLACK_TREE_H
#define _RED_BLACK_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum MyColor{ red, black } MyColor;

typedef struct _tree_node{
	int data;
	struct _tree_node *lchild;
	struct _tree_node *rchild;
	struct _tree_node *parent;
	struct _tree_node *uncle;
	MyColor color;
}treenode, *linktree;

//创建节点
linkTree CreateNode(int data);

//插入节点
linkTree InsertNode(linkTree anew,linkTree *root);

//删除节点
linkTree DelNode(linkTree *root,int sdata);

#endif
