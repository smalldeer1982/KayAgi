# [ABC239E] Subtree K-th Max

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc239/tasks/abc239_e

$ N $ 頂点の根付き木があります。頂点には $ 1 $ から $ N $ の番号がついており、根は頂点 $ 1 $ です。  
 $ i $ 番目の辺は頂点 $ A_i $ と $ B_i $ を結んでいます。  
 頂点 $ i $ には整数 $ X_i $ が書かれています。

$ Q $ 個のクエリが与えられます。$ i $ 番目のクエリでは整数の組 $ (V_i,K_i) $ が与えられるので、次の問題に答えてください。

- 問題：頂点 $ V_i $ の部分木に含まれる頂点に書かれた整数のうち、大きい方から $ K_i $ 番目の値を求めよ

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\leq\ X_i\leq\ 10^9 $
- $ 1\leq\ A_i,B_i\leq\ N $
- $ 1\leq\ Q\ \leq\ 10^5 $
- $ 1\leq\ V_i\leq\ N $
- $ 1\leq\ K_i\leq\ 20 $
- 与えられるグラフは木である
- 頂点 $ V_i $ の部分木は頂点を $ K_i $ 個以上持つ
- 入力に含まれる値は全て整数である

### Sample Explanation 1

この入力において与えられる木は下図のようなものです。 !\[図\](https://img.atcoder.jp/ghi/e2bc1237d64f79f33181e6f54c9f7ce7.png) $ 1 $ 番目のクエリでは、頂点 $ 1 $ の部分木に含まれる頂点 $ 1,2,3,4,5 $ に書かれた数のうち大きい方から $ 2 $ 番目である $ 4 $ を出力します。 $ 2 $ 番目のクエリでは、頂点 $ 2 $ の部分木に含まれる頂点 $ 2,3,5 $ に書かれた数のうち大きい方から $ 1 $ 番目である $ 5 $ を出力します。

## 样例 #1

### 输入

```
5 2
1 2 3 4 5
1 4
2 1
2 5
3 2
1 2
2 1```

### 输出

```
4
5```

## 样例 #2

### 输入

```
6 2
10 10 10 9 8 8
1 4
2 1
2 5
3 2
6 4
1 4
2 2```

### 输出

```
9
10```

## 样例 #3

### 输入

```
4 4
1 10 100 1000
1 2
2 3
3 4
1 4
2 3
3 2
4 1```

### 输出

```
1
10
100
1000```

# 题解

## 作者：xiaohaoaibiancheng66 (赞：6)

# 思路
数据范围中有一条非常有用：$k\le20$。这意味着只需存**每个节点的子树的前 $20$ 大的数**即可。而空间使用为 $4\times10^5\times20=8\times10^6\approx8$ MB，并不会爆内存。

所以就可得到思路：
1. 建树
2. dfs 遍历每个节点，并且把该节点的**每个子节点的子树**的前二十大的数字，包括当前节点的权值放在一起，挑出前 $20$ 大即可。

对于第二个步骤，如何取前 $20$ 大？排序一下即可。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;

int ans[100000+10][20+2];
vector<int> bian[100000+10];
vector<int> child[100000+10];
int hs[2000000+10];
int a[100000+10];

bool cmp(int a,int b)//注意是从大到小排序，所以需要自定义cmp。当然存负数等方法也可以。
{
	return a>b;
}

void dfs1(int i,int fa)//建树
{
	for(auto v:bian[i])
	{
		if(v==fa)continue;
		child[i].push_back(v);
		dfs1(v,i);
	}
}

void dfs2(int i)
{
	int len=-1;
	for(auto v:child[i])
	{
		dfs2(v);
	}
	for(auto v:child[i])
	{
		for(int j=1;j<=ans[v][0];j++)
			hs[++len]=ans[v][j];//将前二十大放入。
	}
	hs[++len]=a[i];
	sort(hs,hs+len+1,cmp);//排序
	ans[i][0]=min(20,len+1);//ans[i][0]存个数：如果节点没达到20个则为节点数。
	for(int j=1;j<=ans[i][0];j++)ans[i][j]=hs[j-1];
}

int main()
{
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)
	{
		int s,t;
		cin>>s>>t;
		bian[s].push_back(t);
		bian[t].push_back(s); 
	 } 
	dfs1(1,0);
	dfs2(1);
	while(q--)
	{
		int a,b;
		cin>>a>>b;
		cout<<ans[a][b]<<'\n';
	}
}
```
AC code


---

