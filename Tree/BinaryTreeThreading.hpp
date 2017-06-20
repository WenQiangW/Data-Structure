#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

enum Info
{
	LINK,
	THREAD
};
template<class T>
struct BinaryTreeNodeThd
{
	BinaryTreeNodeThd(const T& data)
	: _data(data)
	, _pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	, _LeftThread(LINK)
	, _RightThread(LINK)
	{}
	T _data;
	BinaryTreeNodeThd<T>* _pLeft;
	BinaryTreeNodeThd<T>* _pRight;
	BinaryTreeNodeThd<T>* _pParent;
	Info _LeftThread;
	Info _RightThread;
};

template<class T>
class BinaryTreeThd
{
public:
	BinaryTreeThd()
		:_pRoot(NULL)
	{
	}
	BinaryTreeThd(T array[], size_t size)
		:_pRoot(NULL)
	{
		size_t index = 0;
		_CreatBinaryTree(_pRoot, array, size, index);
	}
	//ǰ��������
	void PreThread()
	{
		BinaryTreeNodeThd<T>* prev = NULL;
		_preThread(_pRoot, prev);
	}
	void PreOrder()
	{
		_PreOrder(_pRoot);
	}
	//����������
	void InThread()
	{
		BinaryTreeNodeThd<T>* prev = NULL;
		_InThread(_pRoot, prev);
	}
	void InOrder()
	{
		_InOrder(_pRoot);
	}

	//����
	void PostThread()
	{
		BinaryTreeNodeThd<T>* prev = NULL;
		_PostThread(_pRoot, prev);
	}
	void PostOrder()
	{
		_PostOrder(_pRoot);
	}

private:
	//          0
	//      1      2
	//    3   4   5
	//     6
	void _CreatBinaryTree(BinaryTreeNodeThd<T>*& pRoot, T array[], size_t size, size_t& index)
	{
		if (index < size && '#' != array[index])
		{
			pRoot = new BinaryTreeNodeThd<T>(array[index]);
			_CreatBinaryTree(pRoot->_pLeft, array, size, ++index);
			if (pRoot->_pLeft)
				pRoot->_pLeft->_pParent = pRoot;
			_CreatBinaryTree(pRoot->_pRight, array, size, ++index);
			if (pRoot->_pRight)
				pRoot->_pRight->_pParent = pRoot;
		}
	}

	void _preThread(BinaryTreeNodeThd<T>* pRoot, BinaryTreeNodeThd<T>*& prev)
	{
		if (pRoot)
		{
			//��������ǰ�ڵ����ָ����
			if (NULL == pRoot->_pLeft)
			{
				pRoot->_pLeft = prev;
				pRoot->_LeftThread = THREAD;
			}
			//��������ǰ�ڵ��ǰ�̽ڵ����ָ����
			if (prev && NULL == prev->_pRight)
			{
				prev->_pRight = pRoot;
				prev->_RightThread = THREAD;
			}
			prev = pRoot;
			if (LINK == pRoot->_LeftThread)
				_preThread(pRoot->_pLeft, prev);
			if (LINK == pRoot->_RightThread)
				_preThread(pRoot->_pRight, prev);
		}

	}
	void _PreOrder(BinaryTreeNodeThd<T>* pRoot) //ǰ����� 0136425
	{
		BinaryTreeNodeThd<T>* pCur = pRoot;

		while (pCur) //���ѭ��
		{
			// �ҵ�����ߵĽڵ�
			while (LINK == pCur->_LeftThread)
			{
				cout << pCur->_data << " ";
				pCur = pCur->_pLeft;
			}
			//��ʱpCurΪ����ߵĽڵ㻹û�з���
			cout << pCur->_data << " ";

			//�����Һ���
			pCur = pCur->_pRight;
			/*
			while (THREAD == pCur->_RightThread) //����3��������
			{
				pCur = pCur->_pRight;
				cout << pCur->_data << " ";
			}
			if (LINK == pCur->_LeftThread)   //����4��������
			{
				cout << pCur->_data << " ";
				pCur = pCur->_pLeft;
			}
			else
			{
				pCur = pCur->_pRight;
			}*/
		}
		cout << endl;
	}

	void _InThread(BinaryTreeNodeThd<T>* pRoot, BinaryTreeNodeThd<T>*& prev)
	{
		if (pRoot)
		{
			_InThread(pRoot->_pLeft, prev);

			if (NULL == pRoot->_pLeft)
			{
				pRoot->_pLeft = prev;
				pRoot->_LeftThread = THREAD;

			}
			if (prev && NULL == prev->_pRight)
			{
				prev->_pRight = pRoot;
				prev->_RightThread = THREAD;
			}

			prev = pRoot;
			if (LINK == pRoot->_RightThread)
				_InThread(pRoot->_pRight, prev);
		}
	}
	void _InOrder(BinaryTreeNodeThd<T>* pRoot) //3614052
	{
		BinaryTreeNodeThd<T>* pCur = pRoot;
		while (pCur)
		{
			//�ҵ�����ߵĽڵ�
			while (LINK == pCur->_LeftThread)
			{
				pCur = pCur->_pLeft;
			}
			//���ʵ�ǰ�ڵ�
			cout << pCur->_data << " ";

			//���ʵ�ǰ�ڵ�ĺ��
			while (pCur && pCur->_RightThread == THREAD) //ע����֧ pCurΪ��
			{
				pCur = pCur->_pRight;
				cout << pCur->_data << " ";
			}
			//û�к�̣���������
			if (pCur)
			{
				pCur = pCur->_pRight;
			}
		}
	}

	void _PostThread(BinaryTreeNodeThd<T>* pRoot, BinaryTreeNodeThd<T>*& prev)
	{
		if (pRoot)
		{
			_PostThread(pRoot->_pLeft,prev);
			_PostThread(pRoot->_pRight,prev);

			if (pRoot->_pLeft == NULL)
			{
				pRoot->_LeftThread = THREAD;
				pRoot->_pLeft = prev;
			}
			
			if (prev && prev->_pRight == NULL)
			{
				prev->_RightThread = THREAD;
				prev->_pRight = pRoot;
			}
			prev = pRoot;
		}
	}
	void _PostOrder(BinaryTreeNodeThd<T>* pRoot) //6341520
		/* ˼·��1�����ҵ�����ߵĽڵ�
				 2��Ȼ������ڵ�ĺ��(ע����֧�����)
				 3����������û�к��ʱ �ж��Ƿ񵽴���ڵ㣺������ڵ㣨������ڵ�û�������������ʸ��ڵ� return����
				 4��				   û�е�����ڵ㣺�ҵ�ǰ�ڵ��˫�׽ڵ㣬
				 5��һֱ�ҵ����ڵ㣬�����жϸ��ڵ��Ƿ�����������
		*/
	{
		BinaryTreeNodeThd<T>* pCur = pRoot;
		BinaryTreeNodeThd<T>* prev = NULL;
		while (pCur)
		{
			//������ߵĽڵ�
			while (pCur->_LeftThread == LINK && pCur->_pLeft != prev) //��ֹ������ѭ��  
			{
				pCur = pCur->_pLeft;
			} //����ѭ����������pCurΪ����ߵĽڵ�
			
			//���ʽڵ�ĺ��
			while (pCur && THREAD == pCur->_RightThread) // ��֧������������ж�pCur�Ƿ�Ϊ��
			{
				cout << pCur->_data << " ";
				prev = pCur; //perv��¼�Ѿ����ʹ��Ľڵ�
				pCur = pCur->_pRight;
			}//����ѭ����������pCurΪ�գ�����֧��������߽ڵ������������߽ڵ�Ϊ���ڵ�

			//����ѭ�����ж��Ƿ�Ϊ���ڵ�
			if (pCur == pRoot && pCur->_pRight == prev)
			{
				cout << pCur->_data << " ";
				return;
			}
			//���Ǹ��ڵ㣬���ʵ�ǰ�ڵ��˫�׽ڵ�
			while (pCur && pCur->_pRight == prev) // ע�� �ҵ�֧�����ʱpCur == pRoot
			{
				cout << pCur->_data << " ";
				prev = pCur;
				pCur = pCur->_pParent;
			}

			// �жϸ��ڵ��Ƿ���������
			if (pCur && pCur->_RightThread == LINK )
			{
				if (pCur->_pRight == NULL) //��������û���Һ��ӣ�û��������ΪLINK����ΪNULL
					cout << pCur->_data << " ";
				pCur = pCur->_pRight;
			}
		}
	}
private:
	BinaryTreeNodeThd<T>* _pRoot;
};

void FunTest()
{
	char *pTreeInfo = "abd###ce##f";
	BinaryTreeThd<char> bt(pTreeInfo,strlen(pTreeInfo));
	bt.PreThread();
}

void FunTest1()
{
	char* pTreeInfo = "013#6##4##25";
	BinaryTreeThd<char> bt(pTreeInfo,strlen(pTreeInfo));
	//bt.InThread();
	bt.PreThread();
	bt.PreOrder();
	bt.PostThread();
	bt.PostOrder();
}

void FunTest2() //�жϵ�һ��ѭ���ķ�ֹ������ѭ����
{
	char* pTreeInfo = "1245##6#7###3";
	BinaryTreeThd<char> bt(pTreeInfo, strlen(pTreeInfo));
	bt.PostThread();
	bt.PostOrder();
}

void FunTest3() // �ҵ�֧ ���ж��Ƿ�Ϊ��������¼ӵ������� pCur->_pRight == prev
{
	char* pTreeInfo = "1#2#3#4";
	BinaryTreeThd<char> bt(pTreeInfo, strlen(pTreeInfo));
	bt.PostThread();
	bt.PostOrder();
}

void FunTest4() //������֧
{
	char* pTreeInfo = "1#2#3#4";
	BinaryTreeThd<char> bt(pTreeInfo, strlen(pTreeInfo));
	bt.PostThread();
	bt.PostOrder();
}

void FunTest5()
{
	char* pTreeInfo1 = "0124##5##3";
	char* pTreeInfo2 = "01#2";
	BinaryTreeThd<char> bt(pTreeInfo2, strlen(pTreeInfo2));
	bt.PostThread();
	bt.PostOrder();
}