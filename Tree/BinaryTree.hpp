#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
#include<stack>
using namespace std;
int leafCountt = 0;
template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
	:_data(data)
	, _pLeftChild(NULL)
	, _pRightChild(NULL)
	{}

	T _data;
	BinaryTreeNode<T>* _pLeftChild;
	BinaryTreeNode<T>* _pRightChild;
};
template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_pRoot(NULL)
	{}
	BinaryTree(const T array[], size_t size)
		:_pRoot(NULL)
	{
		size_t index = 0;
		_CreatBinaryTree(_pRoot, array, size, index);
	}
	BinaryTree(BinaryTree<T>& tree)
	{
		_pRoot = _CopyBinartTree(tree._pRoot);
	}
	BinaryTree<T>& operator=(BinaryTree<T>& tree)
	{
		if (this != &tree)
		{
			this->~BinaryTree();
			_pRoot = _CopyBinartTree(tree._pRoot);
		}
		return *this;
	}
	void PreOrder() //�ݹ� abdcef
	{
		cout << "ǰ�����" << endl;
		_PreOreder(_pRoot);
		cout << endl;
	}
	void PreOrder_Nor() //�ǵݹ�
		//��ջ�д�ţ�����ȳ��� �ȴ���Һ��ӣ��ٴ������
	{
		cout << "ǰ�����" << endl;
		if (_pRoot == NULL)
			return;
		stack<BinaryTreeNode<T>*> s;
		s.push(_pRoot);
		while (!s.empty())
		{
			BinaryTreeNode<T>* pCur = s.top();
			cout << pCur->_data << " ";
			s.pop();
			if (pCur->_pRightChild)
				s.push(pCur->_pRightChild);
			if (pCur->_pLeftChild)
				s.push(pCur->_pLeftChild);
		}
		cout << endl;
	}
	void InOrder() //�ݹ飺dbaecf
	{
		cout << "�������" << endl;
		_InOrder(_pRoot);
		cout << endl;
	}
	void InOrder_Nor() //�ǵݹ�
		//��ŵ�ջ�� ���ҵ�����ߵĽڵ㣨���δ�ţ�
	{
		cout << "�������" << endl;
		if (NULL == _pRoot)
			return;

		BinaryTreeNode<T>* pCur = _pRoot;
		stack<BinaryTreeNode<T>*> s;
		while (NULL != pCur || !s.empty())
		{
			while (pCur) //��Žڵ㣬�ҵ�����ߵĽڵ�
			{
				s.push(pCur);
				pCur = pCur->_pLeftChild;
			}

			BinaryTreeNode<T>* pTop = s.top();
			cout << pTop->_data << " ";
			pCur = pTop->_pRightChild; //���ҵ�ǰ�ڵ���������������
			s.pop();
		}
		cout << endl;
	}
	void InOrder_Nor2()
		//�Ӹ��ڵ㿪ʼ��ֻ�е�ǰ�ڵ���ڻ���ջ��Ϊ�գ����ظ�����Ĺ���
		//1�����ǰ�����ڣ����ջ������������
		//2������ջ�����ʣ�Ȼ�����������
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* pCur = _pRoot;
		BinaryTreeNode<T>* top = NULL;
		while (NULL != pCur || !s.empty())
		{
			if (pCur != NULL) //��ָ���ջ������������
			{
				s.push(pCur);
				pCur = pCur->_pLeftChild;
			}
			else
			{
				//��ָ����ջ�������ʸ��ڵ㣬����������
				top = s.top();
				cout << top->_data << "";
				s.pop();
				pCur = pCur->_pRightChild;
			}
		}
	}
	void PostOrder() //�ݹ�  dbefca
	{
		cout << "�������" << endl;
		_PostOrder(_pRoot);
		cout << endl;
	}
	void PostOrder_Nor() //�ǵݹ�
		// ��ŵ�ջ�У����ҵ���������ߣ�
	{
		cout << "�������" << endl;
		if (NULL == _pRoot)
			return;
		BinaryTreeNode<T> *pCur = _pRoot;
		BinaryTreeNode<T>* pPre = NULL; //�����ѷ��ʹ���������
		stack<BinaryTreeNode<T>*> s;
		while (NULL != pCur || !s.empty())
		{
			while (pCur) //����������
			{
				s.push(pCur);
				pCur = pCur->_pLeftChild;
			}
			BinaryTreeNode<T>* pTop = s.top();
			if (NULL == pTop->_pRightChild || pTop->_pRightChild == pPre) //�ж��������Ƿ�Ϊ�ջ��߷��ʹ�
			{
				cout << pTop->_data << " ";
				pPre = pTop;//�����ѷ��ʹ��Ľ��
				s.pop();
			}
			else
			{
				pCur = pTop->_pRightChild;
			}
		}
		cout << endl;
	}

	~BinaryTree()
	{
		_DestoryBinaryTree(_pRoot);
	}

	void LevelOrder() //�������
		//����ڶ����У��ȴ�Ÿ��ڵ㣬�ٴ�����ӣ��ٴ���Һ���
	{
		cout << "��α���" << endl;
		if (NULL == _pRoot)
			return;
		queue<BinaryTreeNode<T> *> q;
		if (_pRoot)
			q.push(_pRoot);
		while (!q.empty())
		{
			BinaryTreeNode<T>* pCur = q.front();
			cout << pCur->_data << " ";
			q.pop();	
			if (pCur->_pLeftChild)
				q.push(pCur->_pLeftChild);
			if (pCur->_pRightChild)
				q.push(pCur->_pRightChild);
		}
		cout << endl;
	}

	BinaryTreeNode<T>* GetLeftChild(BinaryTreeNode<T>* pCur)
	{
		return (NULL == pCur->_pLeftChild) ? NULL : pCur->_pLeftChild;
	}
	BinaryTreeNode<T>* GetRightChild(BinaryTreeNode<T>* pCur)
	{
		return (NULL == pCur->_pRightChild) ? NULL : pCur->_pRightChild;
	}
	BinaryTreeNode<T>* GetParent(BinaryTreeNode<T>* pChild)
	{
		if (pChild == NULL || _pRoot == NULL || _pRoot == pChild)
			return NULL;
		return _GetParent(_pRoot, pChild);
	}
	BinaryTreeNode<T>* GetRoot()
	{
		return _pRoot;
	}
	BinaryTreeNode<T>* Find(const T& data)
	{
		if (NULL == _pRoot)
			return NULL;
		return	_Find(_pRoot, data);
	}

	size_t Height()
	{
		return _Height(_pRoot);
	}
	size_t GetLeafNodeNum()
	{
		return _GetLeafNodeNum(_pRoot);
	}
	size_t GetNodeNum()
	{
		return _GetNodeNum(_pRoot);
	}
	size_t GetKthLeverNodeNum(size_t k)
	{
		return _GetKthLeverNodeNum(_pRoot,k);
	}
	//�ж������������Ľṹ�Ƿ���ͬ
	bool StructureCmp(BinaryTreeNode<T> *pRoot1, BinaryTreeNode<T> *pRoot2)
	{
		if (pRoot1 == NULL && pRoot2 == NULL) // ��Ϊ�գ�������  
			return true;
		else if (pRoot1 == NULL || pRoot2 == NULL) // ��һ��Ϊ�գ�һ����Ϊ�գ����ؼ�  
			return false;
		bool resultLeft = StructureCmp(pRoot1->m_pLeft, pRoot2->m_pLeft); // �Ƚ϶�Ӧ������   
		bool resultRight = StructureCmp(pRoot1->m_pRight, pRoot2->m_pRight); // �Ƚ϶�Ӧ������  
		return (resultLeft && resultRight);
	}
	//ǰ������ ����������
	void ReBuildBinaryTree(T pre[], size_t preSize, T in[], size_t inSize)
	{
		size_t index = 0;
		_ReBuildBinaryTree(_pRoot, pre, index, preSize, in, inSize, 0, inSize);
	}
	void RebuildBinaryTreee(T pre[],T In[],size_t len)
	{
		if (NULL == pre || NULL == In || len < 0)
			return ;
		_pRoot =  _ConstructTree(pre, pre + len - 1,In,In+len-1);
	}


	//�ж�һ�ö������Ƿ�Ϊ��ȫ������
	//����������������ö��еķ�ʽ
	bool IsCompleteBinaryTree(BinaryTreeNode<T> *pRoot )
	{
		//����Ҳ����ȫ������
		if (pRoot == NULL)
			return true; 
		queue<BinaryTreeNode<T>*> q;
		q.push(pRoot); //���ڵ����
		bool mustLeft = false;
		bool result = true;
		while (!q.empty())
		{
			BinaryTreeNode<T> *pCur = q.front();
			q.pop();
			if (mustLeft) //������ �������Ľڵ�
			{
				if (pCur->_pLeftChild != NULL || pCur->_pRightChild != NULL)
				{
					result = false;
					break;
				}
			}
			else 
			{
				if (pCur->_pLeftChild != NULL && pCur->_pRightChild != NULL)
				{
					q.push(pCur->_pLeftChild);
					q.push(pCur->_pRightChild);
				}
				else if (pCur->_pLeftChild == NULL && pCur->_pRightChild != NULL)
				{
					result = false;
					break;
				}
				else if (pCur->_pRightChild == NULL && pCur->_pLeftChild != NULL)
				{
					q.push(pCur->_pLeftChild);
					mustLeft = true;
				}
				else
				{
					mustLeft = true;
				}
			}
		}
		return result;
	}
	//������������������еĽڵ����
	bool IsCompleteTree(BinaryTreeNode<T> *pRoot)
	{
		if (pRoot == NULL)
			return true;
		queue<BinaryTreeNode<T>*> q;
		q.push(pRoot);
		BinaryTreeNode<T>* pCur = NULL;
		//������������� ,�������սڵ����˳�
		while ((pCur = q.front()) != NULL)
		{
			q.pop();
			q.push(pCur->_pLeftChild);
			q.push(pCur->_pRightChild);
		}
		q.pop();//�ѵ�ǰ�ڵ�Ϊ�ճ���
		//�鿴ʣ��������Ƿ��в�Ϊ�յĽڵ�

		pCur = q.front();
		if (pCur != NULL)
			return false;
		return true;
	}
	//��������ľ���
	BinaryTreeNode<T>* Mirror(BinaryTreeNode<T> * pRoot)
	{
		if (pRoot == NULL) // ����NULL  
			return NULL;
		BinaryTreeNode<T> * pLeft = Mirror(pRoot->_pLeftChild); // ������������  
		BinaryTreeNode<T> * pRight = Mirror(pRoot->_pRightChild); // ������������  
		// ������������������  
		pRoot->_pLeftChild = pRight;
		pRoot->_pRightChild = pLeft;
		return pRoot;
	}

	//����������ת����˫������
	BinaryTreeNode<T>* Convert(BinaryTreeNode<T>* pRootInTree)
	{
		BinaryTreeNode<T>* pLastNodeInList = NULL;

		ConvertNode(pRootInTree, &pLastNodeInList);

		//pLastNodeInListָ��˫�������β��㣬�ٴα����ҵ�ͷ���  
		BinaryTreeNode<T>* pHeadOfList = pLastNodeInList;
		while (pHeadOfList != NULL && pHeadOfList->_pLeftChild != NULL)
			pHeadOfList = pHeadOfList->_pLeftChild;

		return pHeadOfList;
	}
private:
	//������������ת��˫������
	void ConvertNode(BinaryTreeNode<T>* pNode, BinaryTreeNode<T>** pLastNodeInList)
	{
		if (pNode == NULL)
			return;
		BinaryTreeNode<T>* pCurrent = pNode;
		//�ݹ鴦��������  
		if (pCurrent->_pLeftChild != NULL)
			ConvertNode(pNode->_pLeftChild, pLastNodeInList);
		//����ǰ���              
		pCurrent->_pLeftChild = *pLastNodeInList;    //����ǰ������ָ��ָ���Ѿ�ת���õ���������һ��λ��  
		if (*pLastNodeInList != NULL)
			(*pLastNodeInList)->_pRightChild = pCurrent;//����ת���õ���������һ��������ָ��ָ��ǰ���  

		*pLastNodeInList = pCurrent;//������������һ�����  
		//�ݹ鴦��ǰ����������  
		if (pCurrent->_pRightChild != NULL)
			ConvertNode(pNode->_pRightChild, pLastNodeInList);
	}

	void _CreatBinaryTree(BinaryTreeNode<T>*& pRoot, const T array[], size_t size, size_t& index)
	{
		if (index < size && '#' != array[index])
		{
			pRoot = new BinaryTreeNode<T>(array[index]);
			_CreatBinaryTree(pRoot->_pLeftChild, array, size, ++index);
			_CreatBinaryTree(pRoot->_pRightChild, array, size, ++index);
		}
	}
	BinaryTreeNode<T>*& _CopyBinartTree(BinaryTreeNode<T>*& pRoot)
	{
		if (pRoot)
		{
			BinaryTreeNode<T>* pNewRoot = new BinaryTreeNode<T>(pRoot->_data);
			pNewRoot->_pLeftChild = _CopyBinartTree(pRoot->_pLeftChild);
			pNewRoot->_pRightChild = _CopyBinartTree(pRoot->_pRightChild);
			return pNewRoot;
		}

	}
	void _DestoryBinaryTree(BinaryTreeNode<T>*& pRoot)
	{
		if (pRoot)
		{
			_DestoryBinaryTree(pRoot->_pLeftChild);
			_DestoryBinaryTree(pRoot->_pRightChild);
			delete pRoot;
			pRoot = NULL;
		}
	}

	void _PreOreder(BinaryTreeNode<T>* proot) //ǰ�����
	{
		if (proot)
		{
			cout << proot->_data << " ";
			_PreOreder(proot->_pLeftChild);
			_PreOreder(proot->_pRightChild);
		}
	}
	void _InOrder(BinaryTreeNode<T>* proot) //�������
	{
		if (proot)
		{
			_InOrder(proot->_pLeftChild);
			cout << proot->_data << " ";
			_InOrder(proot->_pRightChild);
		}
	}
	void _PostOrder(BinaryTreeNode<T>* proot)  //��������
	{
		if (proot)
		{
			_PostOrder(proot->_pLeftChild);
			_PostOrder(proot->_pRightChild);
			cout << proot->_data << " ";
		}
	}

	BinaryTreeNode<T>* _GetParent(BinaryTreeNode<T>* pRoot, BinaryTreeNode<T>* pChild)
	{
		if (NULL == pRoot)
			return NULL;
		if (pRoot->_pLeftChild == pChild || pRoot->_pRightChild == pChild)
			return pRoot;
		BinaryTreeNode<T>* pParent;
		if (pParent = _GetParent(pRoot->_pLeftChild, pChild))
			return pParent;
		return _GetParent(pRoot->_pRightChild, pChild);

	}
	BinaryTreeNode<T>* _Find(BinaryTreeNode<T>* pRoot, const T& data)
	{
		if (pRoot == NULL)
			return NULL;
		if (pRoot->_data == data)
			return pRoot;
		BinaryTreeNode<T>* find;
		if (find = _Find(pRoot->_pLeftChild, data))
			return find;
		return _Find(pRoot->_pRightChild, data);
	}
	size_t _Height(BinaryTreeNode<T>* pRoot)
	{
		if (NULL == pRoot)
			return 0;
		if (NULL == pRoot->_pLeftChild && NULL == pRoot->_pRightChild)
			return 1;
		size_t LHeigt = _Height(pRoot->_pLeftChild);
		size_t RHeight = _Height(pRoot->_pRightChild);
		return (LHeigt > RHeight) ? (LHeigt + 1) : (RHeight + 1);
	}
	size_t _GetLeafNodeNum(BinaryTreeNode<T>* pRoot)
		// ���õݹ��㷨�������������0�����ֻ��һ���ڵ�(���ڵ�)����1������Ϊ����������Ҷ�ӽ����֮��
	{
		size_t leafCount = 0;
		if (pRoot == NULL)
			leafCount = 0;
		else if (pRoot->_pLeftChild == NULL && pRoot->_pRightChild == NULL)
			leafCount = 1;
		else
			leafCount = _GetLeafNodeNum(pRoot->_pLeftChild) + _GetLeafNodeNum(pRoot->_pRightChild);
		return leafCount;
	}
	void _GetLeafNodeNum2(BinaryTreeNode<T>* pRoot)
		//�������ͳ��Ҷ�ӽ��
	{
		if (pRoot != NULL)
		{
			_GetLeafNodeNum2(pRoot->_pLeftChild);
			_GetLeafNodeNum2(pRoot->_pRightChild);
			if (pRoot->_pLeftChild == NULL && pRoot->_pRightChild == NULL)
				leftCountt++;
		}
	}
	size_t _GetNodeNum(BinaryTreeNode<T>* pRoot)
	{
		if (pRoot == NULL)
			return 0;
		else
			return _GetNodeNum(pRoot->_pLeftChild) + _GetNodeNum(pRoot->_pRightChild) + 1;
	}
	size_t _GetKthLeverNodeNum(BinaryTreeNode<T>* pRoot,size_t k)
		//����1�����������Ϊ�ջ���k<1����0
		//��2�������������Ϊ�ղ���k == 1������1
		//��3�������������Ϊ����k>1��������������k - 1��Ľڵ������������k - 1��ڵ����֮��
	{
		if (pRoot == NULL || k == 0)
			return 0;
		if (k == 1 && pRoot != NULL)
			return 1;
		int leftNum = _GetKthLeverNodeNum(pRoot->_pLeftChild,k-1);
		int rightNum = _GetKthLeverNodeNum(pRoot->_pRightChild,k-1);
		return leftNum + rightNum;
	}
	void _ReBuildBinaryTree(BinaryTreeNode<T>*& pRoot,T pre[],size_t& index,size_t preSize,T in[],size_t InSize,size_t left,size_t right)
	{
		if (left >= right || preSize != InSize)
			return;
		//ǰ������ȡһ��Ԫ��
		// ����������ǰ��index��Ԫ��
		size_t idx = left;
		while (idx < right)
		{
			if (pre[index] == in[idx])
				break;
			idx++;
		}
		if (idx == right)
			return;
		pRoot = new BinaryTreeNode<T>(pre[index]);

		if (left < idx) //����������
		_ReBuildBinaryTree(pRoot->_pLeftChild, pre, ++index, preSize, in, InSize,left, idx);

		if (idx + 1 < right)
			_ReBuildBinaryTree(pRoot->_pRightChild, pre, ++index, preSize, in, InSize, idx + 1, right);

	}
	//ǰ�����ؽ�������
	BinaryTreeNode<T>* _ConstructTree(T *startPreOrder,T *endPreOrder,T *startInOrder,T *endInOrder)
	{
		//ǰ������ĵ�һ�����Ϊ���ڵ�
		T rootValue = startPreOrder[0];
		BinaryTreeNode<T>* pRoot = new	BinaryTreeNode<T>(rootValue);
		//ֻ��һ��Ԫ��
		if (startPreOrder == endPreOrder && *startInOrder == *startPreOrder)
			return pRoot;
		//������������ҵ����ڵ��ֵ
		T* rootInOreder = startInOrder;
		while (rootInOreder <= endInOrder && *rootInOreder != rootValue)
		{
			++rootInOreder;
		}//����ѭ������û���ҵ�
		if (*rootInOreder != rootValue)
			throw std::exception("Invalid input");

		int leftlength = rootInOreder - startInOrder; //�������ĳ���
		T *leftPreEnd = startPreOrder + leftlength; //ǰ����������endλ��
		if (leftlength > 0)//����������
		{
			pRoot->_pLeftChild = _ConstructTree(startPreOrder + 1, leftPreEnd, startInOrder, rootInOreder - 1);
		}
		if (leftlength < endPreOrder - startPreOrder)//����������
		{
			pRoot->_pRightChild = _ConstructTree(leftPreEnd + 1, endPreOrder, rootInOreder + 1, endInOrder);
		}
		return pRoot;
	}

private:
	BinaryTreeNode<T>* _pRoot;
};

void Test()
{
	char *pTreeInfo = "abd###ce##f";
	BinaryTree<char> tree(pTreeInfo,strlen(pTreeInfo));
	BinaryTree<char> t1(tree);
	BinaryTree<char> t2;
	t2 = tree;
	tree.PreOrder(); 
	tree.PreOrder_Nor();
	tree.InOrder();
	tree.InOrder_Nor();
	tree.PostOrder();
	tree.PostOrder_Nor();
	BinaryTreeNode<char>* Node = tree.Find('e');
	BinaryTreeNode<char>* Parent = tree.GetParent(Node);
	BinaryTreeNode<char>* Child1 = tree.GetLeftChild(Parent);
	BinaryTreeNode<char>* Child2 = tree.GetRightChild(Parent);
	size_t h = tree.Height();
}

void Test2()
{
	char* pre = "abdcef";
	char* in = "dbaecf";
	BinaryTree<char> t;
	t.ReBuildBinaryTree(pre,strlen(pre),in,strlen(in));
	t.PreOrder();
	t.InOrder();
}
void Test3()
{
	char* pre = "abdcef";
	char* in = "dbaecf";
	BinaryTree<char> t;
	t.RebuildBinaryTreee(pre, in,strlen(pre));
	t.PreOrder();
	t.InOrder();
}

void TestIsCompleteTree()
{
	char *pTreeInfo = "abd###ce##f";
	BinaryTree<char> tree(pTreeInfo, strlen(pTreeInfo));
	BinaryTreeNode<char>* proot = tree.GetRoot();
	bool a = tree.IsCompleteBinaryTree(proot);
	bool b = tree.IsCompleteTree(proot);
}