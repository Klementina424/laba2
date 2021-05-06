#pragma once
#include "LinkedList.h"
#include <iostream>

enum NodeColor { BLACK, RED };

template<class NODE_TYPE_1, class NODE_TYPE_2>
class RB_TREE_Node
{
public:
	~RB_TREE_Node();
	void NIL_N_Root();
	void Left_Rotate(RB_TREE_Node* node_x);
	void Right_Rotate(RB_TREE_Node* node_y);
	void Insert(NODE_TYPE_1 key, NODE_TYPE_2 data);
	void Insert_Fixup(RB_TREE_Node* node_z);
	void Transplant(RB_TREE_Node* u, RB_TREE_Node* v);
	void Remove(NODE_TYPE_1 key);
	void Remove_Fixup(RB_TREE_Node* node_x);
	RB_TREE_Node* Find(NODE_TYPE_1 key, RB_TREE_Node* node_x);
	void Clear(RB_TREE_Node* tree);
	void Get_Keys(RB_TREE_Node* node_x, LinkedList<NODE_TYPE_1>* List_of_Keys);
	void Get_Values(RB_TREE_Node* node_x, LinkedList<NODE_TYPE_2>* List_of_Values);
	void Print(RB_TREE_Node* node_x);
	RB_TREE_Node* Get_Root() { return root; }
	RB_TREE_Node* Get_Parent() { return parent; }

	template<class ARRAY_TYPE>
	void Fill_Array(RB_TREE_Node* node_x, ARRAY_TYPE* array, const char* key_or_data)
	{
		static int i = 0;
		if (key_or_data == "data")
		{
			if (node_x->Get_Parent() == NULL)
				throw "RB Tree is empty";
			if (node_x == NIL)
				return;
			else
			{
				array[i++] = node_x->data;
				if (node_x->left != NIL)
					Fill_Array(node_x->left, array, key_or_data);
			}
			if (node_x->right != NIL)
				Fill_Array(node_x->right, array, key_or_data);
		}
		else if (key_or_data == "key")
		{
			if (node_x->Get_Parent() == NULL)
				throw "RB Tree is empty";
			if (node_x == NIL)
				return;
			else
			{
				array[i++] = node_x->key;
				if (node_x->left != NIL)
					Fill_Array(node_x->left, array, key_or_data);
			}
			if (node_x->right != NIL)
				Fill_Array(node_x->right, array, key_or_data);
		}
	}
	
	NODE_TYPE_2& operator[] (const NODE_TYPE_1 key)
	{
		RB_TREE_Node* node = Find(key, root);
		return node->data;
	}

	void operator = (NODE_TYPE_2 new_data)
	{
		data = new_data;
	}

	void operator ++ () { ++data; }
	unsigned Get_Size() { return size; }
	RB_TREE_Node* Tree_Minimum(RB_TREE_Node* node_x);

private:

	RB_TREE_Node* left, * right, * parent;
	RB_TREE_Node* root;
	RB_TREE_Node* NIL;
	NodeColor color;
	NODE_TYPE_1 key;
	NODE_TYPE_2 data;
	unsigned size;
};

#include "Tree.inl"