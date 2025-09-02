# [JOI 2016 Final] 铁路票价 / Train Fare

## 题目描述

JOI 国有 $N$  个城市，编号分别为 $1, 2, \ldots, N$ 。城市 $1$  是 JOI 国的首都。  

JOI 国只有一家铁路公司，该公司在 JOI 国内共有 $M$  条线路，这些线路编号分别为 $1, 2, \ldots, M$ 。每条线路都可看作一条无向边，线路 $i(1\le i\le N)$  连接城市 $U_i$  和 $V_i$ 。假设你只能依靠铁路运输在不同的城市间来往。当然你可以换乘不同线路。保证任意两个城市间都有线路直接或间接连接。  

目前，任何线路的票价是 1 日元。该公司经营不善，只好计划在未来 $Q$  年里提高票价。从提价计划开始的第 $j$  年初 $(1\le j\le Q)$ ，线路 $R_j$  的票价会从 1 日元升至 2 日元。 之后该线路票价一直保持在 2 日元，不会再提高。

该公司每年都会对每个城市的居民进行满意度调查。在提价计划开始之前，任何一个城市的居民都对该公司感到满意。但由于价格上涨，可能有一些城市的居民会不满。每年的满意度调查都在当年提价后进行。因此，计划开始后第 $j$  年 $(1\le j\le Q)$ 进行满意度调查时，线路 $R_1,R_2,\ldots,R_j$  已经提价，剩余线路的票价暂无变化。  

在第 $j$  年的满意度调查中，如果**当年城市 $k(2\le k\le N)$  到首都的最低总票价 大于 提价计划开始前城市 $k$  到首都的最低总票价**，城市 $k$  的居民会对铁路公司感到不满。  

使用多条路线的费用是每条路线的运费的总和。首都人民不会对该公司感到不满。提价后最低费用的路线可能与计划开始前最低费用的路线有所不同。

## 说明/提示

【数据范围与约定】

对于全部数据，均满足：

- $2\le N\le 100000,1\le Q\le M\le 200000$。
- $1 \le U_i \le N (1\le i\le M),1\le V_i\le N (1\le i\le M),U_i \neq V_i(1\le i\le M)$。
- $1\le R_j\le M (1\le j\le Q),R_j\neq R_k(1\le j<k\le Q)$。
- 对于任意两个城市，直接连接它们的线路不超过一条。
- 对于任何一个城市，都可以从该城市前往另一个城市。

---

1.Subtask $1$ （$12$ pts）：$N\le 100,M\le 4950,Q\le 30$。

2.Subtask $2$ （$14$ pts）：$Q\le 30$。

3.Subtask $3$ （$35$ pts）：答案中出现的整数少于 $50$ 种。

4.Subtask $4$ （$39$ pts）：无特殊限制。

## 样例 #1

### 输入

```
5 6 5
1 2
1 3
4 2
3 2
2 5
5 3
5
2
4
1
3```

### 输出

```
0
2
2
4
4```

## 样例 #2

### 输入

```
4 6 6
1 2
1 3
1 4
2 3
2 4
3 4
1
4
2
5
3
6```

### 输出

```
1
1
2
2
3
3```

## 样例 #3

### 输入

```
2 1 1
1 2
1```

### 输出

```
1```

# 题解

## 作者：ldyldy (赞：6)

## 一个基于离线特性而比较容易理解的题解
有一个特性：

**把一条边边权增大，之后包含它的路径一定比原最短路权值大。**

也就意味着加权值的操作效益等同于**删边**。

再看到输入的**离线**特性，就容易想到将边加一个第二权值，定义为  **此边何时被删去**。

定义一条 $1$ 到 $i$ 点的最短路被破坏，即为无论如何 $1$ 到 $i$ 点的路径无法小于等于原最短路的长度。

因为所有边长度为 $1$ ，故我们可以使用 BFS 来求单源最短路，顺便求 $1$ 到 $i$ 点的最短路被破坏的时间。

需要注意的是，此处 BFS 来求单源最短路时要考虑到最短路路径相等时也要更新答案。

最后把时间计数排序一下，再用前缀和算一下此时已有多少路径被破坏，然后按 $q$ 输出。

本题，完。
```
#include <bits/stdc++.h>
using namespace std;
struct edge
{
	int u,v,lo;
	bool operator <(const edge &a)const
	{
		return lo>a.lo;
	}
}ed[1000005];
vector <edge>a[100005];
int n,m,q,dis[1000005],dis2[1000005],tpx[1000005],sum[1000005];
void bfs()
{
	for(int i=1;i<=1000000;i++) dis[i]=99999999;
	dis2[1]=99999999;
	dis[1]=0;
	queue<int> q;
	q.push(1);
	long long flag=1;
	while(q.size())
	{
		int now=q.front();
		q.pop();
		for(int i=0;i<a[now].size();i++)
		{
			if(flag)
			{
				if(dis[a[now][i].v]>dis[now]+1)
				{
					q.push(a[now][i].v);
					dis[a[now][i].v]=dis[now]+1;
					dis2[a[now][i].v]=min(dis2[now],a[now][i].lo);
				}
				if(dis[a[now][i].v]==dis[now]+1)
				{
					dis2[a[now][i].v]=max(dis2[a[now][i].v],min(dis2[now],a[now][i].lo));
				}

			}
		}
	}
}
int main()
{
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++)
	{
		cin>>ed[i].u>>ed[i].v;
		ed[i].lo=99999999;
	}
	for(int i=1;i<=q;i++)
	{
		int x;
		cin>>x;
		ed[x].lo=i;
	}
	for(int i=1;i<=m;i++)
	{
		a[ed[i].u].push_back(ed[i]);
		a[ed[i].v].push_back({ed[i].v,ed[i].u,ed[i].lo});
	}
	bfs();
	for(int i=1;i<=n;i++)
	{
		if(dis2[i]<1000000)tpx[dis2[i]]++;
	}
	for(int i=1;i<=q;i++)
	{
		sum[i]=sum[i-1]+tpx[i];
		cout<<sum[i]<<endl;
	}
	return 0;
}
```

---

## 作者：_lmh_ (赞：2)

把一条边边权增大相当于删掉这条边，因为包含它的路径的长度一定不可能和原来的最短路一样。

先 bfs 一遍找出所有点和 $1$ 的距离，以及最短路上可能的前驱个数，删一条边的时候如果发现它指向的节点所有前驱都废掉了就把它也废掉，然后删除它的所有出边。这个点的最短路长度变大，所以经过它的最短路径长度也变大。

每个点和每条边最多被删一次，总复杂度 $O(m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007;
struct edge{ll to,nxt;}e[N<<1];
ll n,m,k,x,ans,nE=1,hd[N],dis[N],cnt[N],ok[N<<1];
queue<int> q;
void add(int u,int v){e[++nE]=(edge){v,hd[u]};hd[u]=nE;}
void del(int x){
	int u=e[x^1].to,v=e[x].to;
	if (ok[x]||dis[v]!=dis[u]+1) return;
//	cout<<"del "<<u<<' '<<v<<'\n';
//	cout<<"erase "<<v<<endl;
	ok[x]=1;
	if ((--cnt[v])==0){
//		cout<<"bad "<<v<<'\n';
		++ans;
		for (int i=hd[v];i;i=e[i].nxt) del(i);
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	memset(dis,0x3f,sizeof(dis));dis[1]=0;
	cin>>n>>m>>k;
	for (int u,v,i=1;i<=m;++i){
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	q.push(1);
	while(!q.empty()){
		int u=q.front();q.pop();
		for (int v,i=hd[u];i;i=e[i].nxt){
			v=e[i].to;
			if (dis[v]<=dis[u]) continue;
			if (dis[v]==dis[u]+1) ++cnt[v];
			else{
				dis[v]=dis[u]+1;cnt[v]=1;q.push(v);
			}
		}
	}
	while(k--){
		cin>>x;del(x<<1);del(x<<1|1);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

