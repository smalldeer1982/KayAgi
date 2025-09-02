# Medals

## 题目描述

[problemUrl]: https://atcoder.jp/contests/snuke21/tasks/snuke21_g



# 题解

## 作者：xuan_gong_dong (赞：2)

## 题面

[Medals](https://www.luogu.com.cn/problem/AT_snuke21_g)

翻译：有 $n$ 个人进行比赛，选手的编号是从 $1$ 到 $n$。不会存在排名相同的情况。给定 $m$ 个关系，满足 $a_i$ 的排名在 $b_i$ 的前面，问前三名的合法方案有多少种。

## 分析
不妨把每一个关系转换为一条边来建图，之后再拓扑排序一遍得到可以求答案的图，在个图上将点分为 $4$ 的集合，分别包含度数为 $0$ 的点， 度数为 $1$ 的点，度数为 $2$ 的点，其他剩余节点，发现只有前三个集合内的点才有可能是答案。

（下文的 $0$ 表示第一个集合的点，$1,2$ 同理）

可能是答案的方案有：

`000`

`001`

`011`

`012`

依次计算上述方案数，求和即为答案。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int>oe[100010],be[100010],du[5],fa[100010];
int in[100010];
int n,m,sum;
queue < int > q;
bool book[100010];
inline int read()
{
	int x=0;
	char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x;
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		int u,v;
		u=read(),v=read();
		be[v].push_back(u);
		oe[u].push_back(v);
		in[v]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(in[i]==0)
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=0;i<be[x].size();i++)
		{
			if(book[be[x][i]]==1)
			{
				book[x]=1;
				fa[x].clear();
				break;
			}	
			fa[x].push_back(be[x][i]);
			for(int j=0;j<fa[be[x][i]].size();j++)
			{
				fa[x].push_back(fa[be[x][i]][j]);
			}
		}
		if(!book[x])
		{
			sort(fa[x].begin(),fa[x].end());
			fa[x].erase(unique(fa[x].begin(),fa[x].end()),fa[x].end());
			if(fa[x].size()>=3)
			{
				book[x]=1;
				fa[x].clear();
			}
		}
		for(int i=0;i<oe[x].size();i++)
		{
			in[oe[x][i]]--;
			if(in[oe[x][i]]==0)
			{
				q.push(oe[x][i]);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!book[i])
		{
			du[fa[i].size()].push_back(i);
		}
	}
	sum+=(du[0].size())*(du[0].size()-1)*(du[0].size()-2);//000
	sum+=(du[1].size())*(du[0].size()-1)*3;//001
	for(int i=0;i<du[0].size();i++)
	{
		int x=du[0][i];
		sort(oe[x].begin(),oe[x].end());
		oe[x].erase(unique(oe[x].begin(),oe[x].end()),oe[x].end());
		int num=0;
		for(int j=0;j<oe[x].size();j++)
		{
			if(fa[oe[x][j]].size()==1)
			{
				num++;
			}
		}
		sum+=num*(num-1);//011
	}
	for(int i=0;i<du[2].size();i++)
	{
		int x=du[2][i];
		if(fa[fa[x][0]].size()==0&&fa[fa[x][1]].size()==0)
		{
			sum++;
		}
		sum++;
	}
	printf("%lld",sum);
	return 0;
}
/*
3 1 
1 2




6 8
2 1
6 4
3 4
1 6
3 1
5 4
2 6
2 6

*/
```


---

