#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>
#include <algorithm>
#include "UnionFindSet.h"
using namespace std;
//�ڽӱ�

template<class W>
struct LinkEdge
{
	W _edge;//Ȩֵ
	size_t _srcIndex;
	size_t _desIndex;
	struct LinkEdge<W>* _pNext;
	
	LinkEdge(size_t srcIdx, size_t desIdx, const W& weight)
		: _edge(weight)
		, _srcIndex(srcIdx)
		, _desIndex(desIdx)
		, _pNext(NULL)
	{}

};


template<class V, class W>
class GraphLink
{
public:
	GraphLink()
	{}
	GraphLink(const V* pVex, size_t size, bool isDirected)
	{
		_vex.resize(size);
		_LinkTable.resize(size, NULL);
		for (size_t i = 0; i < size; ++i)
			_vex[i] = pVex[i];
	}
	
	//ͷ�巨
	void _AddEdge(int srcIdx, int desIdx,const  W& weight)//Ϊ�˷�ֹ�����ظ�
	{
		LinkEdge<W>* pEdge = new LinkEdge<W>(srcIdx, desIdx, weight);
		pEdge->_pNext = _LinkTable[srcIdx];
		_LinkTable[srcIdx] = pEdge;

	}
	void AddEdge(const V& v1, const V& v2, const W& weight)
	{
		int srcIdx = GetIndexOfVertex(v1);
		int desIdx = GetIndexOfVertex(v2);
		assert(srcIdx != desIdx);

		//�ж��Ƿ�Ϊ����ͼ:����ͼ����Ȩֵ��ֻ����һ��
		_AddEdge(srcIdx, desIdx, weight);
		if (!_IsDirected)
			_AddEdge(desIdx, srcIdx, weight);
	}
	//��ȡĳ���ڵ�Ķ���������ͼ���Ⱥ����
	int GetDev(const V& v)
	{
		//�������(����ͼ������ͼ ��Ҫ��)
		int VertexIdx = GetIndexOfVertex(v);
		//��������
		int InCount = 0;
		LinkEdge<W> *pEdge = _LinkTable[VertexIdx];
		while (pEdge)
		{
			++InCount;
			pEdge = pEdge->_pNext;
		}
		//�����
		int OutCount = 0;
		if (_IsDirected)
		{
			for (size_t i = 0; i < _LinkTable.size(); ++i)
			{
				LinkEdge<W> *pEdge = _LinkTable[i];
				if (i != VertexIdx)
				{
					while (pEdge)
					{
						if (pEdge->_desIndex == VertexIdx)
							++OutCount;
					}
				}
			}
		}

		return InCount + OutCount;
	}

	void Print()
	{
		cout << " ͼ�Ĺ��ɣ�" << endl;
		for (size_t i = 0; i < _LinkTable.size(); ++i)
		{
			LinkEdge<W>* pCur = _LinkTable[i];
			cout << i;
			while (pCur)
			{
				cout << " -->" << pCur->_desIndex << "[" << pCur->_edge << "]";
				pCur = pCur->_pNext;
			}
			cout << " -->NULL" << endl;
		}
		cout << endl;
	}

	//������ȱ���ͼ������
	void BFS(const V& v)
	{
		cout << "������ȱ�����" << endl;
		vector<bool> visited(_vex.size(), false);
		_BFS(v, visited);

		//����ͨ�ķ���
		for (size_t i = 0; i < _vex.size(); ++i)
		{
			if (!visited[i])
				_BFS(_vex[i],visited);
		}
		cout << "NULL" << endl;
	}

	//������ȱ�����
	void DFS(const V& v)
	{
		cout << "������ȱ�����" << endl;
		vector<bool> visited(_vex.size(), false);
		int idx = GetIndexOfVertex(v);
		_DFS(idx, visited);

		//����ͨ�ķ���
		for (size_t i = 0; i < _vex.size(); ++i)
		{
			if (!visited[i])
				_BFS(i, visited);
		}
		cout << "NULL" << endl;
	}

	struct Compare
	{
		bool operator()(LinkEdge<W>* Left, LinkEdge<W>* Right)
		{
			return Left->_edge <  Right->_edge;
		}
	};

	//����ͼ����С������
	pair<GraphLink<V, W>, bool> GetMinTree()
	{

		//1 �����еı߷���vector�У����˵��ظ��ı�
		vector<LinkEdge<W> *> edge;
		for (size_t i = 0; i < _LinkTable.size(); ++i)
		{
			LinkEdge<W> * pCur = _LinkTable[i];
			while (pCur)
			{
				if (pCur->_srcIndex < pCur->_desIndex)//���˵��ظ��ı�
					edge.push_back(pCur);
				pCur = pCur->_pNext;
			}
		}
		//2 ��vector ����
		sort(edge.begin(), edge.end(), Compare());
		//3 ��vector��ȡ����Сֵ����ӵ�ͼ��
		GraphLink<V, W> g;
		g._vex.resize(_vex.size());
		for (size_t idx = 0; idx < _vex.size(); ++idx)
			g._vex[idx] = _vex[idx];
		g._LinkTable.resize(_LinkTable.size(), NULL);
		g._IsDirected = false;

		//���鼯������Ƿ񹹳��˻�
		UnionFindSet un(_vex.size());
		int count = 0;//ͳ�Ƽ���ı�����
		for (size_t j = 0; j < edge.size(); ++j)
		{
			LinkEdge<W>* pEdge = edge[j];
			if (!(un.IsSameSet(pEdge->_srcIndex,pEdge->_desIndex)))
			{
				g._AddEdge(pEdge->_srcIndex,pEdge->_desIndex, pEdge->_edge);
				un.Union(pEdge->_srcIndex, pEdge->_desIndex);
				if (++count == _vex.size() - 1)
				{
					g._LinkTable.resize(count);
					return make_pair(g, true);
				}				
			}
		}

		return make_pair(g, false);

	}
	struct Biger
	{
		bool operator()(LinkEdge<W>* Left, LinkEdge<W>* Right)
		{
			return Left->_edge >  Right->_edge;
		}
	};
	//��С������prime�㷨
	pair<GraphLink<V, W>, bool> Prime(const V& vertex)
	{
		GraphLink<V, W> g;
		g._vex.resize(_vex.size());
		for (size_t idx = 0; idx < _vex.size(); ++idx)
			g._vex[idx] = _vex[idx];
		g._IsDirected = false;
		g._LinkTable.resize(_vex.size()-1, NULL);

		//��һ����ʼ���㣬������Ϊ���ı߷ŵ���С����,ÿ�δ���С����ȡ�Ѷ��ӵ�ͼ��(�ж��Ƿ��Ѿ�����)
		vector<bool> flag(_vex.size(), false);//��Ƕ����Ƿ��Ѿ�����ͼ�� 
		vector<LinkEdge<W> *> vEdge;
		int index = GetIndexOfVertex(vertex);
		LinkEdge<W> *pCur = _LinkTable[index];
		while (pCur)
		{
			vEdge.push_back(pCur);
			pCur = pCur->_pNext;
		}
		make_heap(vEdge.begin(), vEdge.end(), Biger());
		
		int count = 0;//ͳ�Ƽ���ߵ�����
		while (true)
		{
			//����С����ȡ��
			pCur = vEdge[0];
			pop_heap(vEdge.begin(), vEdge.end(), Biger());
			vEdge.pop_back();
			if (!flag[pCur->_desIndex])
			{
				g._AddEdge(pCur->_srcIndex, pCur->_desIndex, pCur->_edge);
				if (++count == _vex.size() - 1)
					return make_pair(g, true);
				flag[pCur->_srcIndex] = true;
			}
			index = pCur->_desIndex;
			if (!flag[index])
			{
				pCur = _LinkTable[index];
				while (pCur)
				{
					if (!flag[pCur->_desIndex])
					{
						vEdge.push_back(pCur);
						push_heap(vEdge.begin(), vEdge.end(), Biger());
					}	
					pCur = pCur->_pNext;
				}	
			}
			
		}
		
		return make_pair(g, false);
	}

private:

	void _BFS(const V& v,vector<bool>& visited)
	{
		queue<size_t> q;
		int idx = GetIndexOfVertex(v);
		q.push(idx);
		while(!q.empty())
		{
			if (!visited[idx])
			{
				cout << idx << "-->";
				visited[idx] = true;
				q.pop();
				LinkEdge<W>* pCur = _LinkTable[idx];
				while (pCur)
				{
					q.push(pCur->_desIndex);
					pCur = pCur->_pNext;
				}
			}
		}		

	}

	void _DFS(size_t idx, vector<bool>& visited)
	{
		if (!visited[idx])
		{
			cout << idx << "-->";
			visited[idx] = true;

			LinkEdge<W>* pCur = _LinkTable[idx];
			while (pCur)
			{
				_DFS(pCur->_desIndex, visited);
				pCur = pCur->_pNext;
			}
		}
	}
	//��ȡ������±�
	size_t GetIndexOfVertex(const V& v)
	{
		for (size_t i = 0; i < _vex.size(); ++i)
		{
			if (_vex[i] == v)
				return i;
		}
		assert(false);
		return -1;
	}

private:
	vector<V> _vex;
	vector<LinkEdge<W>*> _LinkTable;
	bool _IsDirected;
};


void TestGraphLink()
{
	char vex[] = { 'A', 'B', 'C', 'D' };
	GraphLink<char, int> link(vex, 4, false);


	link.AddEdge('A', 'B', 1);
	link.AddEdge('B', 'C', 2);
	link.AddEdge('D', 'C', 3);
	link.AddEdge('A', 'D', 4);
	link.Print();
	
	cout << link.GetDev('A');
	link.BFS('A');
	link.DFS('A');
	pair<GraphLink<char, int>, bool> res;
	res = link.Prime('A');
	res.first.Print();
}

void TestGetMinTree()
{

}
