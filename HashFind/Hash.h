#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;


//����̽��
enum State
{
	EMPTY,
	EXIST,
	DELETE
};

template<class T>
class HashTable
{
public:
	HashTable(size_t capacity = 10)
		:_capacity(capacity)
		, _size(0)
	{
		_hashTable = new T[_capacity];
		_state = new State[_capacity];
		memset(_state, EMPTY, sizeof(_state)*_capacity);
	}
	bool Insert(const T& key)
		// �����ж��Ƿ�Ϊ���˿��Բ���
		// ���ж��Ƿ���ڣ��Ƿ�Ϊkeyֵ
		//���Ϊkeyֵ�Ļ�������true 
		//�����Ϊkeyֵ�Ļ������������ң�ֱ������Ϊ�յ�λ�û���ɾ�� Ȼ��ֱ�Ӳ���
	{
		if (_size >= _capacity)
			return false;
		size_t index = HashFuncation(key);
		while (_state[index] == EXIST)
		{
			if (_hashTable[index] == key)
				return true;

			index++;
			index %= _capacity;
		}
		_state[index] = EXIST;
		_hashTable[index] = key;
		_size++;
		return true;
	}
	bool Find(const T& key, size_t& hashIdx)
		//hashIdx�൱����Ϊ����ֵ����
	{
		size_t index = HashFuncation(key);
		size_t startIdx = index;//�����ʼλ�ã���ֹ��һȦ��������ѭ��
		while (_state[index] != EMPTY)
			//����ѭ������������ �ж��Ƿ���ڣ���Ϊ����delete״̬���������delete������ѭ����delete�����Ԫ�ؾ�û����
		{
			if (_hashTable[index] == key && _state[index] == EXIST)
			{
				hashIdx = index;
				return true;
			}
			index++;
			index %= _capacity;
			if (index == startIdx) //����һȦ��
				break;
		}
		return false;
	}
	bool Remove(const T& key)
		//���ҵ�ǰindex�Ƿ�Ϊkeyֵ���������������
	{
		size_t index = 0;
		if (Find(key, index))
		{
			_state[index] = DELETE;
			_size--;
			return true;
		}
		return false;
	}
	~HashTable()
	{
		if (_hashTable)
		{
			delete[] _hashTable;
			_hashTable = NULL;
		}
		if (_state)
		{
			delete[] _state;
			_state = NULL;
		}
	}
private:
	int HashFuncation(const T& key)
	{
		return key % 10;
	}
private:
	T* _hashTable;
	State * _state;
	size_t _capacity;
	size_t _size;
};

void TestHash()
{
	HashTable<int> ht;
	size_t index = 0;
	ht.Insert(10);
	ht.Insert(20);
	ht.Insert(30);
	ht.Insert(40);
	ht.Insert(50);
	ht.Insert(60);
	ht.Insert(70);
	ht.Insert(80);
	ht.Insert(90);
	ht.Insert(9);
	ht.Remove(20);
	ht.Insert(3);
	ht.Find(3, index);
	bool res = ht.Insert(20);
}