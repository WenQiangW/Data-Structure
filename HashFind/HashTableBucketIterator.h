
//ʵ�ֵ�����
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include"common.h"

using namespace std;

template<class K, class V>
struct HashTableNode
{
	HashTableNode(const pair<K, V>& kv)
	: _kv(kv)
	, _next(NULL)
	{}

	HashTableNode<K, V>* _next;
	pair<K, V> _kv;
};
template<class K, class V, class _HashFun = HashFunDef<K>>
class HashTableBucket;


//��������������Ա����:������ָ��ǰ�Ľڵ㣬HashTableBucket
template<class K, class V, class Ref, class Ptr, class _HashFun> //����������Ϊ���ã����ĸ�����Ϊָ��
struct _HashTableIterator
{
	typedef HashTableNode<K, V> Node;
	Node* _node;
	HashTableBucket<K, V, _HashFun>* _ht;

	typedef _HashTableIterator<K, V, Ref, Ptr, _HashFun> iterator;
	//���캯��
	_HashTableIterator(Node* pNode, HashTableBucket<K, V, _HashFun>* ht)
		: _node(pNode)
		, _ht(ht)
	{}
	Ref operator*() const
	{
		return _node->_kv;
	}
	Ptr operator->() const
	{
		return &(operator*());
	}

	iterator& operator++() //ǰ��++
	{
		Node* pCur = _node;
		_node = _node->_next;
		if (!_node)
		{
			size_t hashIdx = _ht->HashFun(pCur->_kv.first);
			while (!_node && ++hashIdx < _ht->_HashTable.size())
			{
				_node = _ht->_HashTable[hashIdx];
			}
		}
		return *this;
	}
	iterator operator++(int) //����++
	{
		iterator temp = *this;
		++(*this);
		return temp;
	}

	bool operator==(const iterator& ite)
	{
		return _node == ite._node;
	}
	bool operator!=(const iterator& ite)
	{
		return _node != ite._node;
	}

};

template<class K, class V, class _HashFun >
class HashTableBucket
{
public:
	friend _HashTableIterator<K, V, pair<K, V>&, pair<K, V>*, _HashFun>;
	typedef _HashTableIterator<K, V, pair<K, V>&, pair<K, V>*, _HashFun> Iterator;
	typedef _HashTableIterator<K, V, const pair<K, V>&, const pair<K, V>*, _HashFun> ConstIterator;

	HashTableBucket(size_t size = 10)
		: _size(0)
	{
		_HashTable.resize(GetNextPrim(size));
	}
	pair<bool, Iterator> Insert(const pair<K, V>& kv)
	{
		CheckCapacity();

		size_t index = HashFun(kv.first);
		HashTableNode<K, V> *pCur = _HashTable[index];
		while (NULL != pCur)
		{
			if (pCur->_kv.first == kv.first)
				return make_pair(false, Iterator(pCur, this));
			pCur = pCur->_next;
		}


		HashTableNode<K, V> *pNewNode = new HashTableNode<K, V>(kv);
		pNewNode->_next = _HashTable[index];
		_HashTable[index] = pNewNode;
		++_size;

		return make_pair(true, Iterator(pNewNode, this));
	}
	bool Find(const K& key)
	{
		size_t index = HashFun(key);
		HashNode<K, V> *pCur = _HashTable[index];
		while (NULL != pCur)
		{
			if (pCur->_kv.first == key)
				return true;
			pCur = pCur->_next;
		}
		return false;
	}
	bool Remove(const K& key)
	{
		size_t index = HashFun(key);
		HashNode<K, V> *pCur = _HashTable[index];
		HashNode<K, V> *prev = pCur;
		while (NULL != pCur)
		{
			if (pCur->_kv.first == key)
			{
				if (pCur == _HashTable[index]) //ɾ����Ϊͷ
				{
					_HashTable[index] = prev->_next;
				}
				else
				{
					prev->_next = pCur->_next;
				}
				delete pCur;
				--_size;
				return true;
			}
			prev = pCur;
			pCur = pCur->_next;
		}
		return false;
	}
	void Clear()
	{
		for (size_t idx = 0; idx < _HashTable.size(); ++idx) //vector��size == capacity
		{
			while (_HashTable[idx])
			{
				HashTableNode<K, V>* pDel = _HashTable[idx];
				_HashTable[idx] = pDel->_next;
				delete pDel;
			}
		}
		_size = 0;
	}
	~HashTableBucket()
	{
		Clear();
	}
	//[]������ ���ؼ�ֵ��
	V& operator[](const K& key)
	{
		size_t idx = HashFun(key);
		HashTableNode<K, V>* pCur = _HashTable[idx];
		while (pCur)
		{
			if (pCur->_kv.first == key)
				return pCur->_kv.second;
			pCur = pCur->_next;
		}
		//����ѭ�� ��ʾû�ҵ��������׳��쳣��
		throw::exception("ket not find");
	}
	Iterator Begin()
	{
		for (size_t index = 0; index < _HashTable.size(); ++index)
		{
			if (_HashTable[index])
				return Iterator(_HashTable[index], this);
		}

		return Iterator(NULL, this);
	}
	Iterator End()
	{
		return Iterator(NULL, this);
	}
private:
	void ResizeHashTable() //
	{

	}
	void CheckCapacity()
	{
		if (_size == _HashTable.capacity()) //�������Ԫ�ص���vector������,
		{
			HashTableBucket<K, V> temp(GetNextPrim(_size));
			for (size_t idx = 0; idx < _HashTable.size(); ++idx)
			{
				HashTableNode<K, V>* pCur = _HashTable[idx];
				HashTableNode<K, V>* pPre = NULL;
				while (pCur)
				{
					pPre = pCur;
					pCur = pCur->_next;
					//��λ�µ�temp��Ͱ
					size_t hashIdx = temp.HashFun(pPre->_kv.first);
					//���ӵ�temp._hashTable��
					pPre->_next = temp._HashTable[hashIdx];
					temp._HashTable[hashIdx] = pPre;
					temp._size++;
				}
				_HashTable[idx] = NULL;
			}
			_HashTable.swap(temp._HashTable);

		}
	}
	size_t HashFun(const K& key)
	{
		return _HashFun()(key) % _HashTable.size();
	}
private:
	vector<HashTableNode<K, V>*> _HashTable;
	size_t _size;
};
void TestIterator()
{

	HashTableBucket<string, string> ht;
	ht.Insert(make_pair("1","���"));
	ht.Insert(make_pair("2","С��Ů"));
	ht.Insert(make_pair("3","�����"));
	ht.Insert(make_pair("4","�ض�"));
	ht.Insert(make_pair("5","��а"));
	cout<<ht["1"]<<endl;
	HashTableBucket<string, string>::Iterator it = ht.Begin();

	while(it != ht.End())
	{
		cout<<(*it).second<<endl;
		++it;
	}
}