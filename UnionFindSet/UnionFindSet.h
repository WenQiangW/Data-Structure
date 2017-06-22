#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;


// 0   1   2   3   4   5    6
// -1  -1  -1  -1  -1
class UnionFindSet
{
public:
	UnionFindSet(size_t size)
	{
		s.resize(size, -1);
	}
	size_t FindIdx(int x)//找该位置的根节点的下标
	{
		int root = x;
		while (s[root] >= 0)
			root = s[root];
		return root;
	}
	void Union(int x1, int x2)//合并两个
	{
		int root1 = FindIdx(x1);
		int root2 = FindIdx(x2);
		if (root1 != root2)
		{
			s[root1] += s[root2];
			s[root2] = root1;
		}
	}
	bool IsSameSet(int x1, int x2)//判断两个集合是否相等
	{
		return FindIdx(x1) == FindIdx(x2);
	}
	size_t SetSize()//求有几个集合 0 不是一个集合
	{
		size_t count = 0;
		for (size_t i = 0; i < s.size(); ++i)
		{
			if (s[i] < 0)
				count++;
		}
		return count - 1;
	}

	void PrintSet()
	{
		for (size_t i = 0; i < s.size(); ++i)
			cout << i << "  ";
		cout << endl;
		for (size_t i = 0; i < s.size(); ++i)
		{
			if (s[i] < 0)
				cout << s[i] << " ";
			else
				cout << s[i] << "  ";
		}
		cout << endl;
	}
private:
	vector<int> s;
};

void Test()
{
	UnionFindSet un(8);
	un.Union(1, 3);
	un.Union(3, 7);
	un.Union(2, 4);
	un.Union(4, 5);
	un.Union(5, 6);
	
	un.PrintSet();
	cout<< un.SetSize()<<endl;
}
