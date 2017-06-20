#include"BinaryTree.hpp"
#include<list>

//����������������͹�������

// ��Ϊ����������
template<class T>
BinaryTreeNode<T>* GetLastCommomParent(BinaryTreeNode<T>* pRoot,int data1,int data2)
{
	if (pRoot)
	{
		if (data1 < pRoot->_data && data2 < pRoot->_data)
			return GetLastCommomParent(pRoot->_pLeftChild,data1,data2);
		else if (data1 > pRoot->_data && data2 > pRoot->_data)
			return GetLastCommomParent(pRoot->_pRightChild, data1, data2);
		else
			return pRoot;
	}
	return NULL;
}

//���еĽ����ָ�򸸽ڵ��ָ��


//���еĽ��û��ָ�򸸽ڵ��ָ��
//����������ֱ𱣴�Ӹ��ڵ㵽����������ڵ��·����Ȼ�������ת���������������󹫹��ڵ㡣

//�ݹ��㷨��
template<class T>
bool FindNode(BinaryTreeNode<T> * pRoot,BinaryTreeNode<T> *pNode)
{
	if (pRoot == NULL || pNode == NULL)
		return false;
	if (pRoot == pNode)
		return true;
	bool found = FindNode(pRoot->_pLeftChild,pNode);
	if (!found)
		return FindNode(pRoot->_pRightChild,pNode);
}
template<class T>
BinaryTreeNode<T>* GetLastCommomParent(BinaryTreeNode<T>* pRoot, BinaryTreeNode<T>* pNode1, BinaryTreeNode<T>* pNode2)
{
	if (FindNode(pRoot->_pLeftChild, pNode1))
	{
		if (FindNode(pRoot->_pRightChild, pNode2))
			return pRoot;
		else
			return GetLastCommomParent(pRoot->_pLeftChild,pNode1,pNode2);
	}
	else
	{
		if (FindNode(pRoot->_pLeftChild, pNode2))
			return pRoot;
		else
			return GetLastCommomParent(pRoot->_pRightChild,pNode1,pNode2);
	}
}


//�ǵݹ�ⷨ��
//����Ӹ��ڵ㵽�����ڵ��·����Ȼ���ٱȽ϶�Ӧ·���Ľڵ���У����һ����ͬ�Ľڵ�Ҳ���������ڶ������е���͹������Ƚڵ�

template<class T>
bool GetPath(BinaryTreeNode<T>* pRoot,BinaryTreeNode<T>* pNode,list<BinaryTreeNode<T>*>& path)
{
	if (pRoot == NULL || pNode == NULL)
		return  false;
	path.push_back(pRoot);
	if (pRoot == pNode)
		return true;
	bool found = false;
	found = GetPath(pRoot->_pLeftChild,pNode,path);
	if (!found)
		found = GetPath(pRoot->_pRightChild,pNode,path);
	if (!found)
		path.pop_back();
	return found;
}
template<class T>
BinaryTreeNode<T>* GetLastCommomAcess(BinaryTreeNode<T>* pRoot, BinaryTreeNode<T>* pNode1, BinaryTreeNode<T>* pNode2)
{
	if (pRoot == NULL || pNode1 == NULL || pNode2 == NULL)
		return NULL;
	list<BinaryTreeNode<T>*> path1;
	bool res1 = GetPath(pRoot,pNode1,path1);
	list<BinaryTreeNode<T>*> path2;
	bool res2 = GetPath(pRoot, pNode2, path2);
	if (!res1 || !res2)
		return NULL;
	//����������Ĺ����ڵ�
	BinaryTreeNode<T>* Ancestor = NULL;
	list<BinaryTreeNode<T>*>::const_iterator iter1 = path1.end();
	list<BinaryTreeNode<T>*>::const_iterator iter2 = path2.end() ;
	while (--iter1 != path1.begin() && --iter2 != path2.begin())
	{
		if (*iter1 == *iter2)
		{
			Ancestor = *iter1;
			break;
		}
	}
	return Ancestor;
}

void TestGetAncestor()
{
	char *pTreeInfo = "abd###ce##f";
	BinaryTree<char> tree(pTreeInfo, strlen(pTreeInfo));
	BinaryTreeNode<char>* pRoot = tree.GetRoot();
	BinaryTreeNode<char>* Node1 = tree.Find('e');
	BinaryTreeNode<char>* Node2 = tree.Find('f');
	BinaryTreeNode<char>* Ancestot = GetLastCommomAcess(pRoot,Node1,Node2);
}