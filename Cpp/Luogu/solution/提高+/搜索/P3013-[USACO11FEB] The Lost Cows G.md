# [USACO11FEB] The Lost Cows G

## 题目描述

给定一张 $n(3\leq n\leq 200)$ 个点的图，每个点都恰好有 $m(1\leq m\leq 200)$ 条出边，第 $i$ 个点的第 $j$ 条出边指向 $a_{i,j}$。

现在这张图上每个点都有一头牛。每次你可以报出一个数 $x(1\leq x\leq m)$，这会使得每一头牛沿着当前所在的点的第 $x$ 条边走一步（即当前在点 $u$ 的牛移动到点 $a_{u,x}$）。

你需要发出不超过 $5\times 10^6$ 条指令，使得在所有的指令执行完后，所有的牛都在编号为 $1$ 的点上。

## 样例 #1

### 输入

```
4 3 
4 4 1 3 
1 3 2 4 
4 2 3 1 
```

### 输出

```
1 
2 
1 
2 
3 
1 
3 
```

# 题解

## 作者：Argon_Cube (赞：4)

重测了，以前输出样例水过去的都被制裁了。首 A 来一发题解。

显然如果两个人走到一个点上了以后就永远不会再分开，因为保证有解显然任意两个出发点都存在一种走到同一个点上的方案，并且步数显然不会超过 $\binom n2$。

那么我们考虑每次合并两个不在同一点上的人，路径可以通过一次 BFS 得到，最多合并 $n-1$ 次共 $(n-1)\binom n2\leq4\times 10^6$ 次操作。

可以直接让被合并的人在 $1$ 汇合，但是注意到我们需要维护每个点的位置，只能 $\Theta(nk)$ 其中 $k$ 是指令条数。为了让 $k$ 小一些防止超时，我们每次选步数最小的两个人合并，最后所有人会合并在一个点上。再走最多 $n-1$ 步即可让所有人到达 $1$。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <random>
#include <ctime>
#include <array>
#include <queue>

using namespace std;

array<array<vector<pair<int,int>>,201>,201>	igraph;
array<array<int,201>,201>					graph,dists;
queue<pair<int,int>>						BFSque;
array<int,201>								curnds,dists2;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt,cnte;
	cin>>cnt>>cnte;
	for(int i=1;i<=cnte;i++)
		for(int j=1;j<=cnt;j++)
			cin>>graph[j][i];
	for(int i=1;i<=cnte;i++)
		for(int j=1;j<=cnt;j++)
			for(int k=1;k<=cnt;k++)
				igraph[graph[j][i]][graph[k][i]].emplace_back(j,k);
	for(int i=1;i<=cnt;i++)
		curnds[i]=i,dists[i][i]=1,BFSque.emplace(i,i);
	while(!BFSque.empty())
	{
		int u=BFSque.front().first,v=BFSque.front().second,u0,v0;
		BFSque.pop();
		for(const auto& i:igraph[u][v])
			if(!dists[u0=i.first][v0=i.second])
			{
				dists[u0][v0]=dists[u][v]+1;
				BFSque.emplace(u0,v0);
			}
	}
	BFSque.emplace(1,1);
	dists2[1]=1;
	while(!BFSque.empty())
	{
		int u=BFSque.front().first,u0;
		BFSque.pop();
		for(const auto& i:igraph[u][u])
			if(u0=i.first,!dists2[u0]&&i.first==i.second)
			{
				dists2[u0]=dists2[u]+1;
				BFSque.emplace(u0,u0);
			}
	}
	dists[0][0]=16777216;
	while(true)
	{
		int u=0,v=0,u0,v0;
		for(int i=1;i<=cnt;i++)
			for(int j=i+1;j<=cnt;j++)
				if(curnds[i]!=curnds[j]&&dists[curnds[u]][curnds[v]]>dists[curnds[i]][curnds[j]])
					u=i,v=j;
		if(!u)
			break;
		while((u0=curnds[u])!=(v0=curnds[v]))
		{
			for(int i=1;i<=cnte;i++)
				if(dists[graph[u0][i]][graph[v0][i]]<dists[u0][v0])
				{
					cout<<i<<'\n';
					for(int j=1;j<=cnt;j++)
						curnds[j]=graph[curnds[j]][i];
					break;
				}	
		}
	}
	int u=curnds[1];
	while(u!=1)
		for(int i=1;i<=cnte;i++)
			if(dists2[graph[u][i]]<dists2[u])
				cout<<i<<'\n',u=graph[u][i];
	return 0;
}

```

---

