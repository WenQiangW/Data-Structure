#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>
#include <algorithm>
#include "UnionFindSet.h"
using namespace std;
//邻接表

template<class W>
struct LinkEdge
{
	W _edge;//权值
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
	
	//头插法
	void _AddEdge(int srcIdx, int desIdx,const  W& weight)//为了防止代码重复
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

		//判断是否为有向图:有向图插入权值，只插入一次
		_AddEdge(srcIdx, desIdx, weight);
		if (!_IsDirected)
			_AddEdge(desIdx, srcIdx, weight);
	}
	//获取某个节点的度数：有向图出度和入度
	int GetDev(const V& v)
	{
		//先求出度(有向图和无向图 都要求)
		int VertexIdx = GetIndexOfVertex(v);
		//遍历链表
		int InCount = 0;
		LinkEdge<W> *pEdge = _LinkTable[VertexIdx];
		while (pEdge)
		{
			++InCount;
			pEdge = pEdge->_pNext;
		}
		//求出度
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
		cout << " 图的构成：" << endl;
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

	//广度优先遍历图：队列
	void BFS(const V& v)
	{
		cout << "广度优先遍历：" << endl;
		vector<bool> visited(_vex.size(), false);
		_BFS(v, visited);

		//非连通的访问
		for (size_t i = 0; i < _vex.size(); ++i)
		{
			if (!visited[i])
				_BFS(_vex[i],visited);
		}
		cout << "NULL" << endl;
	}

	//深度优先遍历：
	void DFS(const V& v)
	{
		cout << "深度优先遍历：" << endl;
		vector<bool> visited(_vex.size(), false);
		int idx = GetIndexOfVertex(v);
		_DFS(idx, visited);

		//非连通的访问
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

	//无向图的最小生成树
	pair<GraphLink<V, W>, bool> GetMinTree()
	{

		//1 将所有的边放在vector中，过滤掉重复的边
		vector<LinkEdge<W> *> edge;
		for (size_t i = 0; i < _LinkTable.size(); ++i)
		{
			LinkEdge<W> * pCur = _LinkTable[i];
			while (pCur)
			{
				if (pCur->_srcIndex < pCur->_desIndex)//过滤掉重复的边
					edge.push_back(pCur);
				pCur = pCur->_pNext;
			}
		}
		//2 将vector 排序
		sort(edge.begin(), edge.end(), Compare());
		//3 从vector中取出最小值，添加到图中
		GraphLink<V, W> g;
		g._vex.resize(_vex.size());
		for (size_t idx = 0; idx < _vex.size(); ++idx)
			g._vex[idx] = _vex[idx];
		g._LinkTable.resize(_LinkTable.size(), NULL);
		g._IsDirected = false;

		//并查集，检测是否构成了环
		UnionFindSet un(_vex.size());
		int count = 0;//统计加入的边数量
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
	//最小生成树prime算法
	pair<GraphLink<V, W>, bool> Prime(const V& vertex)
	{
		GraphLink<V, W> g;
		g._vex.resize(_vex.size());
		for (size_t idx = 0; idx < _vex.size(); ++idx)
			g._vex[idx] = _vex[idx];
		g._IsDirected = false;
		g._LinkTable.resize(_vex.size()-1, NULL);

		//给一个起始顶点，将顶点为起点的边放到最小堆中,每次从最小堆中取堆顶加到图中(判断是否已经加入)
		vector<bool> flag(_vex.size(), false);//标记顶点是否已经加入图中 
		vector<LinkEdge<W> *> vEdge;
		int index = GetIndexOfVertex(vertex);
		LinkEdge<W> *pCur = _LinkTable[index];
		while (pCur)
		{
			vEdge.push_back(pCur);
			pCur = pCur->_pNext;
		}
		make_heap(vEdge.begin(), vEdge.end(), Biger());
		
		int count = 0;//统计加入边的数量
		while (true)
		{
			//从最小堆中取出
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
	//获取顶点的下标
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
