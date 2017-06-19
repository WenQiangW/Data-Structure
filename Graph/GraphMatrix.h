#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

//�ڽӾ���

template<class V, class W>
class GraphMatrix
{
public:
	GraphMatrix(const V* pVer, size_t size, bool isDirected = false)
		:_IsDirected(isDirected)
	{
		_ver.resize(size);
		_edge.resize(size);
		for (size_t i = 0; i < size; ++i)
		{
			_ver[i] = pVer[i];
			_edge[i].resize(size);
		}
	}
	int GetIndexOfVertex(const V& v)//���ؽڵ���±�
	{
		for (size_t i = 0; i < _ver.size(); ++i)
		{
			if (_ver[i] == v)
				return i;
		}
		assert(false);
		return -1;
	}
	void AddEdge(const V& v1, const V& v2, const W& weight)
	{
		int row = GetIndexOfVertex(v1);
		int col = GetIndexOfVertex(v2);
		if (_IsDirected)//����ͼ
		{
			_edge[row][col] = weight;
		}
		else//����ͼ
		{
			_edge[row][col] = weight;
			_edge[col][row] = weight;
		}
	}
	void Print()
	{
		for (size_t i = 0; i < _edge.size(); ++i)
		{
			for (size_t j = 0; j < _edge[i].size(); ++j)
			{
				cout << _edge[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
private:
	vector<V> _ver;//��Ž�� ���� char A B;
	vector<vector<W> > _edge;//��űߵ�Ȩֵ
	bool _IsDirected; //true Ϊ����ͼ
};


void TestGraphMatrix()
{
	int arr[] = { 0, 1, 2 ,};
	GraphMatrix<int, int> m(arr, 3, true);
	m.AddEdge(0, 1, 1);
	m.AddEdge(1, 0, 1);
	m.AddEdge(1, 2, 1);
	m.Print();
}