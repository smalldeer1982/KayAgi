# Directing Edges

## 题目描述

You are given a graph consisting of $ n $ vertices and $ m $ edges. It is not guaranteed that the given graph is connected. Some edges are already directed and you can't change their direction. Other edges are undirected and you have to choose some direction for all these edges.

You have to direct undirected edges in such a way that the resulting graph is directed and acyclic (i.e. the graph with all edges directed and having no directed cycles). Note that you have to direct all undirected edges.

You have to answer $ t $ independent test cases.

## 说明/提示

Explanation of the second test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1385E/d35669c68d98d1dcefc83e24fe388de76c760c1f.png)

Explanation of the third test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1385E/641ca4dc132da9f3a738d8606128481e262df751.png)

## 样例 #1

### 输入

```
4
3 1
0 1 3
5 5
0 2 1
1 1 5
1 5 4
0 5 2
1 3 5
4 5
1 1 2
0 4 3
1 3 1
0 2 3
1 2 4
4 5
1 4 1
1 1 3
0 1 2
1 2 4
1 3 2```

### 输出

```
YES
3 1
YES
2 1
1 5
5 4
2 5
3 5
YES
1 2
3 4
3 1
3 2
2 4
NO```

# 题解

## 作者：MY（一名蒟蒻） (赞：55)

[原题传送门](https://www.luogu.com.cn/problem/CF1385E)

题面翻译得已经非常清晰了，唯一的缺点是没有给出输入输出解释。

不过观察样例可知，第一个数为数据组数，接下来每一个数据第一行输入 $\text{n m}$ ，表示这是一个 $\text{n}$ 个点， $\text{m}$ 条边的图。结点编号从 $1$ 开始。接下来 $\text{m}$ 行，输入 $\text{type,u,v}$ ，表示这条边连接了两个顶点 $\text{u}$ 和 $\text{v}$ ，如果 $\text{type=1}$ ，则这条边是一条 $\text{u}$ 到 $\text{v}$ 的有向边，否则是一条无向边。

要求输出该图指的是按原来的有向边输入格式输出原有有向边和定向后的无向边。

具体大家一会儿可以看代码，此处不再赘述。

---
接下来讲解做法。

首先无解的情况必然是原图有向边成环的情况。

那么我们就在求解的过程中判断原图是否已经有环即可。

考虑**有解的情况，原图中给出的有向边必然形成DAG**。

想到拓扑排序。

在拓扑排序中，所有的有向边都是**拓扑序小的点指向拓扑序大的点**。

那么我们只要**对原有的有向边进行拓扑排序，然后判断有没有环，最后有解的话，先输出所有有向边，然后让无向边中拓扑序小的指向大的再输出即可。**

## Code
```cpp
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

const int N=2e5+10;

int t,n,m,top[N],fir[N],tot,q[N][2],cnt,du[N];
queue <int> que;
struct node {int to,nex;} e[N];

void add(int u,int v)
{
	e[++tot].to=v;
	du[v]++;
	e[tot].nex=fir[u];
	fir[u]=tot;
	return ;
}

bool top_sort()//核心
{
	int u,sum=0;
	for(int i=1;i<=n;i++) if(!du[i]) que.push(i);
	while(!que.empty())
	{
		u=que.front(); que.pop();
		top[u]=++sum;//注意这里的拓扑序
		for(int i=fir[u];i;i=e[i].nex)
		{
			du[e[i].to]--;
			if(!du[e[i].to]) que.push(e[i].to);
		}
	}
	if(sum != n) return false;
	return true;//如果可以拓扑每个点一定都入队了一次
}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&t);
	int op,u,v;
	while(t--)
	{
		scanf("%d%d",&n,&m);
		tot=cnt=0;//多组数据的初始化
		while(!que.empty()) que.pop();
		for(int i=1;i<=n;i++) {fir[i]=du[i]=0; top[i]=1e9;}//注意这里初始拓扑序为正无穷
		while(m--)
		{
			scanf("%d%d%d",&op,&u,&v);
			if(op) add(u,v);//对于边的种类分别处理
			else {q[++cnt][0]=u; q[cnt][1]=v;}
		}
		if(top_sort())
		{
			puts("YES");
			for(int i=1;i<=n;i++)
				for(int j=fir[i];j;j=e[j].nex)
					printf("%d %d\n",i,e[j].to);
			for(int i=1;i<=cnt;i++)
				if(top[q[i][0]] > top[q[i][1]]) printf("%d %d\n",q[i][1],q[i][0]);//拓扑序小的指向拓扑序大的
				else printf("%d %d\n",q[i][0],q[i][1]);
		}
		else puts("NO");
	}
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
感谢阅读！如果这篇题解能帮到您，就请您留下您的赞吧！您的点赞和评论是对作者最大的鼓励！

---

## 作者：iMya_nlgau (赞：12)

#### 题目大意

给你一张图，有些边是有向边，有一些是无向边，让你给无向边添上方向，使这张图成为一个有向无环图。

#### 思路

先忽略无向边，只添加有向边，进行拓扑排序。若存在环，则问题无解，然后考虑给无向边添上方向。因为 DAG 的边都是从拓扑序小的节点指向拓扑序大的节点，所以我们添加的边也从拓扑序小的节点指向拓扑序大的节点，就一定不会出现环。

程序中，若第 $i$ 条边是无向边，则暂时储存在 $und$ 中，是有向边则加入图中。若拓扑排序中出现环 $(tot<n$，返回 $\text{false})$，输出 `NO`，否则，输出 `YES`，先输出图中的有向边，再考虑 $und$ 中的无向边 $(x,y)$，若 $x$ 的拓扑序小于 $y$ 的 $(topo[x]<topo[y])$，输出边 $(x,y)$，否则输出边 $(y,x)$。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
#define rgi register int
#define mp make_pair
#define fi first
#define se second
using namespace std;
const int maxn=2e5+10;
const int maxm=2e5+10;
struct edge{
	int to,nxt;
}e[maxm];
int head[maxn],cnt;
int deg[maxn],topo[maxn],tot;
inline void addedge(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
	deg[v]++;
}
inline bool toposort(int n){
	queue<int> q;
	for(rgi i=1;i<=n;i++)
		if(deg[i]==0) q.push(i);
	while(!q.empty()){
		int x=q.front(); q.pop();
		topo[x]=++tot;
		for(rgi i=head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(--deg[y]==0) q.push(y);
		}
	}
	if(tot<n) return false;
	return true;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m;
		scanf("%d%d",&n,&m);
		memset(head,0,sizeof(head));
		memset(deg,0,sizeof(deg));
		cnt=tot=0;
		vector<pair<int,int> > und;
		for(rgi i=1;i<=m;i++){
			int t,x,y;
			scanf("%d%d%d",&t,&x,&y);
			if(t==1) addedge(x,y);
			else und.push_back(mp(x,y));	
		}
		if(!toposort(n)){
			puts("NO"); continue;
		}
		puts("YES");
		for(rgi i=1;i<=n;i++)
			for(rgi j=head[i];j;j=e[j].nxt)
				printf("%d %d\n",i,e[j].to);
		for(rgi i=0;i<und.size();i++){
			int x=und[i].fi,y=und[i].se;
			if(topo[x]<topo[y]) printf("%d %d\n",x,y);
			else printf("%d %d\n",y,x);
		}
	}
	return 0;
} 
```

---

## 作者：_lyx111 (赞：4)

# CF1385E Directing Edges

[link](https://codeforces.com/problemset/problem/1385/E)

## 题意

给定一个由有向边与无向边组成的图。将所有的无向边定向，使得形成的图中没有环。

$2\le n\le 2\times 10^5,1\le m\le 2\times 10^5$

## 分析

首先考虑什么时候才会无解：已经存在 SCC （ 强连通分量 ），此时直接输出 NO 即可。下面来考虑一定有解的情况（ 不存在 SCC ）。

显然的，最终定向完整个图将变成一个 DAG （ 有向无环图 ），由此我们联想到 toposort （ 拓扑排序 ）。对原图的有向边我们先找到一个可行的拓扑序 $t_1,t_2,\dots,t_n$，对于一条 $u,v$ 之间的无向边，设：$t_i=u,t_j=v$，那么我们以如下方式连边即可满足题意；

- $i<j$ 时，边的起点为 $u$，终点为 $v$

- $i>j$ 时，边的起点为 $v$，终点为 $u$

总结一下算法流程：

1. 对原图的有向边我们先找到一个可行的拓扑序 $t_1,t_2,\dots,t_n$

2. 给每条无向边定向

## 一些细节

1. 多测要清空！

2. 存图的时候只要存有向边即可，无向边用一个数组记录就好了

## 代码

~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10,MAXM=2e5+10; //最大点数 MAXN，最大边数 MAXM 
int n,m;
struct node
{
	int to,nxt;
} edg[MAXM]; //链式前向星存图（只存有向边） 
int cnt,hea[MAXN];
void add(int u,int v)
{
	cnt++;
	edg[cnt].to=v;
	edg[cnt].nxt=hea[u];
	hea[u]=cnt;
}
int deg[MAXN]; //只有有向边的图中的入度 
int tot,e[MAXM][2]; //存无向边 
int id,t[MAXN]; //合法的拓扑序中每个点所对编号 
queue<int>que; //拓扑排序需要用的队列 
bool toposort() //寻找合法的拓扑序 
{
	for(int i=1;i<=n;i++)
		if(!deg[i]) que.push(i); //将入度为 0 的点入队 
	while(!que.empty()) //队列不为空 
	{
		int u=que.front(); que.pop(); //取队首 
		id++; t[u]=id; //记录 u 在合法拓扑序中的位置 
		for(int i=hea[u];i;i=edg[i].nxt) //将 u 能到达的所有点的入度减一 
		{
			int v=edg[i].to;
			deg[v]--;
			if(!deg[v]) que.push(v);
		}
	}
	if(id==n) return 1; //存在合法的拓扑序 
	else return 0; //无解 
}
void init()
{
	cnt=0; memset(hea,0,sizeof(hea)); //链式前向星清空 
	tot=0; //无向边边数初始化为 0 
	id=0; memset(t,0x3f,sizeof(t)); //初始拓扑序为无穷大 
	while(!que.empty()) que.pop(); //清空队列 
	memset(deg,0,sizeof(deg)); //入度清空 
}
int main()
{
	int T; scanf("%d",&T); //多次询问 
	while(T--)
	{
		scanf("%d%d",&n,&m);
		init(); //多测清空 
		for(int i=1;i<=m;i++)
		{
			int opt,u,v; scanf("%d%d%d",&opt,&u,&v);
			if(opt==1) { add(u,v); deg[v]++;} //有向边 u->v
			else { tot++; e[tot][0]=u; e[tot][1]=v;}
		}
		if(toposort()) //有解 
		{
			printf("YES\n");
			for(int i=1;i<=n;i++)
				for(int j=hea[i];j;j=edg[j].nxt)
					printf("%d %d\n",i,edg[j].to); //输出所有有向边 
			for(int i=1;i<=tot;i++)
				if(t[e[i][0]]<t[e[i][1]])
					printf("%d %d\n",e[i][0],e[i][1]);
				else
					printf("%d %d\n",e[i][1],e[i][0]); //给无向边定向 
		}
		else printf("NO\n"); //无解 
	}
	return 0;
}
~~~

[AC记录](https://codeforces.com/problemset/submission/1385/175240726)

## 写在最后

笔者水平有限，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正

---

## 作者：Emp7iness (赞：3)

判断无解的方法很容易想到，就是给定的有向边就已经构成一个有环图。

如何判断这点呢？用拓扑排序。先对有向边建图，跑一遍拓扑排序，如果跑完之后还有点没有被删去就说明有环。

如果不无解就说明有解。那么如何将无向边变成有向边呢？

我们在跑拓扑排序的时候顺便记录一下每个点的拓扑序，再按拓扑序小的节点指向拓扑序大的节点，将无向边变成有向边即可。

因为有多组数据，不要忘了**清空数组**

代码：

```cpp
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int T,n,m,t,k,a[200005],b[200005],s[200005],in[200005];
//a，b数组记录边，s数组记录拓扑序，in数组记录入度
vector<int> g[200005]; //存图的
queue<int> q; //用来跑拓扑的
void topological_sort() //基本是拓扑排序板子
{
	while(!q.empty())	q.pop();
	for(int i=1;i<=n;i++)
	{
		if(!in[i])	q.push(i);
	}
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		s[x]=++k;//关键步骤，记录拓扑序
		for(int i:g[x])
		{
			in[i]--;
			if(!in[i])	q.push(i);
		}
	}
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=1;i<=m;i++)
		{
			cin>>t>>a[i]>>b[i];
			if(t)
			{
				in[b[i]]++;
				g[a[i]].push_back(b[i]);
			}
		}
		topological_sort();
		if(n>k)	cout<<"NO"<<endl; //判断是否无解
		else
		{
			cout<<"YES"<<endl;
			for(int i=1;i<=m;i++)
			{
				if(s[a[i]]<s[b[i]])	cout<<a[i]<<" "<<b[i]<<endl; //拓扑序小的节点指向拓扑序大的节点
				else	cout<<b[i]<<" "<<a[i]<<endl;
			}
		}
		k=0;
		for(int i=1;i<=n;i++)
		{
			s[i]=in[i]=0;
			g[i].clear();
		} //清空数组
	}
	return 0;
}
```


---

## 作者：钓鱼王子 (赞：3)

一个图是有向无环图，那么它一定可以拓扑排序。

尝试对图进行拓扑排序。

先给出方法：不管无向边，用有向边计算入度直接拓扑排序，然后无向边边拓扑边连。假设边连接 $x,y$， 那么在拓扑排序中 $x$ 先出现则连接 $x,y$。

为什么这样是对的呢？

令某一条无向边为 $x,y$。

当我们连接 $x,y$ 时，若 $y$ 之前有入度，那么这样肯定更优。否则，$y$ 的入度也不会改变，因为 $x$ 是被删去的点。也就是说，当 $x,y$ 入度均为 $0$ 时，出现的顺序不会影响结果。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[200002],b[200002],ans,head[200002],cnt,rd[200002];
bool vis[200002];
struct edge{
	int to,next,w;
}e[2000002];
inline void add(re int x,re int y,re int z){
	e[++cnt]=(edge){y,head[x],z};
	head[x]=cnt;
}
queue<int>q;
int main(){
	t=read();
	while(t--){
		re int tot=0;
		n=read();m=read();
		for(re int i=1;i<=n;++i)rd[i]=vis[i]=head[i]=0;
		for(re int i=1,x,y,z;i<=m;++i){
			x=read(),y=read(),z=read();
			if(!x){
				add(y,z,1),add(z,y,1);
			}
			else add(y,z,0),++rd[z];
		}
		for(re int i=1;i<=n;++i)if(!rd[i])q.push(i);
		while(!q.empty()){
			re int x=q.front();q.pop();vis[x]=1;
			for(re int i=head[x];i;i=e[i].next){
				if(vis[e[i].to])continue;//printf("%d %d\n",x);
				if(e[i].w)a[++tot]=x,b[tot]=e[i].to;
				else{
					a[++tot]=x,b[tot]=e[i].to;
					--rd[e[i].to];
					if(!rd[e[i].to])q.push(e[i].to);
				}
			}
		}
		if(tot^m)puts("NO");
		else{
			puts("YES");
			for(re int i=1;i<=m;++i){
				printf("%d %d\n",a[i],b[i]);
			}
		}
	}
}
```


---

## 作者：KellyFrog (赞：1)

有史以来涨分做多的一次，涨了一百九十分。。

这题挺有意思的。

给出$n$个点$m$条边，有些是标上方向的，有些没有，让给没有标上方向的点标上方向，使得图上没有环。

最初的想法是选出一个点没有出度的点$u$，将跟这个点有关的边都指向$u$，然后这些边就都被干掉了，不可能会有环。

这个点解决后其他点的出度也要更新，因为到$u$的边一定成不了环（因为$u$没有出边）

出度不好维护，我们考虑建图：

只建方向确定的边的反向边，然后进行拓扑排序，记录拓扑排序的顺序，第$i$个点是第$od_i$个被拓扑排序排到的。

如果最终无法排完，则图上有环，输出`NO`，否则一定是有解的。

对于一条没方向边$u,v$，如果$od_u<od_v$，则建出来的图上一定没有$v$到$u$的路径，原图上就一定没有$u$到$v$的路径，可以建边$v,u$，这不会成环。
```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 2e5 + 5;
const int MAXM = 2e5 + 5;

vector<int> adj[MAXN];
int in[MAXN], od[MAXN];
vector<pair<int, int> > qr;

void Solve() {
	int n, m, cnt = 0, no = 0;
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++) {
		adj[i].clear();
		in[i] = 0, od[i] = -1;
	}
	
	qr.clear();
	for(int i = 1; i <= m; i++) {
		int x, u, v;
		cin >> x >> u >> v;
		if(x == 0) {
			qr.push_back(make_pair(u, v));
		} else {
			adj[v].push_back(u);
			in[u]++;
		}
	}
	queue<int> q;
	for(int i = 1; i <= n; i++) {
		if(in[i] == 0) {
			q.push(i), cnt++;
		}
	}
	
	while(!q.empty()) {
		int u = q.front(); q.pop();
		od[u] = ++no;
		for(auto v : adj[u]) {
			in[v]--;
			if(in[v] == 0) {
				q.push(v), cnt++, od[v] = ++no;
			}
		}
	}
	
	if(cnt != n) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		
		for(auto i : qr) {
			if(od[i.first] < od[i.second]) {
				cout << i.second << ' ' << i.first << endl;
			} else {
				cout << i.first << ' ' << i.second << endl;
			}
		}
		for(int i = 1; i <= n; i++) {
			for(auto v : adj[i]) {
				cout << v << ' ' << i << endl;
			}
		}
		
	}
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		Solve();
	}
}
```

---

## 作者：Zirnc (赞：0)

欢迎访问我的博客：[blog.chungzh.cn](https://blog.chungzh.cn/)

[CF-1385E Directing Edges](https://codeforces.com/problemset/problem/1385/E)

前置知识：[拓扑排序](https://blog.chungzh.cn/articles/topo-sort/)

## 题意

给定一个由有向边与无向边组成的图，现在需要你把所有的无向边变成有向边，使得形成的图中**没有环**。

如果可以做到请输出该图，否则直接输出"NO"。

## 分析

我们先只连接有向边，然后做一遍拓扑排序，如果失败了，就说明有环，输出 “NO”。

然后处理剩下的无向边。对于无向边 $(u, v)$，如果 $u$ 的拓扑序小于 $v$，那么令这条边的方向是 $u\rightarrow v$。否则，方向就是 $v\rightarrow u$。因为这条边是从拓扑序小的点指向拓扑序大的点，所以必然不会形成环。

这里用 DFS 的算法实现拓扑排序。

[RECORD](https://codeforces.com/contest/1385/submission/169677796)

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
const int MAXN = 200005;
int n, m;
vector<int> G[MAXN];
int c[MAXN], topo[MAXN], id[MAXN], t, bn, x[MAXN], y[MAXN];
bool dfs(int u) {
  c[u] = -1;
  for (auto v : G[u]) {
    if (c[v] < 0)
      return false;
    else if (c[v] == 0 && !dfs(v))
      return false;
  }
  c[u] = 1;
  topo[--t] = u;
  id[u] = t;
  return true;
}
bool toposort() {
  t = n;
  memset(c, 0, sizeof(c));
  memset(id, 0, sizeof(id));
  memset(topo, 0, sizeof(topo));
  for (int i = 1; i <= n; i++)
    if (!c[i])
      if (!dfs(i)) return false;
  return true;
}
int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) G[i].clear();
    bn = 0;
    for (int i = 0; i < m; i++) {
      int ti, tx, ty;
      cin >> ti >> tx >> ty;
      if (ti == 0) {  // 无向
        x[++bn] = tx;
        y[bn] = ty;
      } else {
        G[tx].push_back(ty);
      }
    }
    if (!toposort()) {
      cout << "NO\n";
      continue;
    }
    cout << "YES\n";
    for (int i = 1; i <= bn; i++) {
      if (id[x[i]] <= id[y[i]])
        cout << x[i] << " " << y[i] << endl;
      else
        cout << y[i] << " " << x[i] << endl;
    }
    for (int i = 1; i <= n; i++) {
      for (auto j : G[i]) { cout << i << " " << j << endl; }
    }
  }
  return 0;
}
```

---

## 作者：yi_fan0305 (赞：0)

题目传送门：[CF1385E](https://www.luogu.com.cn/problem/CF1385E)

翻译描述的不是很好，讨论区有更好的翻译。

做法其实很简单：

先将已经确定了方向的边作为图的边读入，然后在这个有向图的基础上跑拓扑排序，记录下每个节点的拓扑序。

最后输出答案的时候，对于没有确定方向的边，将其方向改为从拓扑排序序号小的节点指向序号大的节点，因为拓扑序小的先出队列，肯定入度也小。

这样，肯定是满足拓扑排序的要求的，即谁在谁前面先输出。

然后如果拓扑排序做不了的话(我们已经确定方向的边生成的有向图的基础上做的)，说明已经有环了，则无解；否则按照上面的方案输出就好，一定有解。

上代码：
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read()//快读
{
	ll x=0;
	bool fg=false;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		fg|=(ch=='-');
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return fg?~x+1:x;
}
const int N=2e5+5;
int T,n,m,cnt2,cnt1;
int h[N],ej[N][2],du[N],top[N];//ej 没确定方向的边 du 入度 top 拓扑序
queue<int> q;
struct edge 
{
	int v,nxt;
}e[N];
void add(int u,int v)
{
	e[++cnt1].v=v;
	du[v]++;
	e[cnt1].nxt=h[u];
	h[u]=cnt1;
}
bool topsort()
{
	int u,sum=0;
	for(int i=1;i<=n;++i)
	{
		if(!du[i])	q.push(i);//读入入度为0的点
	}
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		top[u]=++sum;//记录拓扑序
		for(int i=h[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			du[v]--;
			if(!du[v])	q.push(v);
		}
	}
	if(sum!=n)	return false;//序号不等于n，说明有环，直接返回false
	return true;
}
int main()
{
	T=read();
	for(int t=1;t<=T;++t)
	{
		n=read(),m=read();
		cnt2=cnt1=0;
		while(!q.empty())	q.pop();
		memset(h,0,sizeof h);
		memset(du,0,sizeof du);
		for(int i=1;i<=n;++i)
		{
			top[i]=1e9;
		}
		for(int i=1;i<=m;++i)
		{
			int op=read(),x=read(),y=read();
			if(op)	add(x,y);
			else
			{
				ej[++cnt2][0]=x;ej[++cnt2][1]=y;
			}
		}
		if(topsort())
		{
			printf("YES\n");
			for(int i=1;i<=n;++i)//先输出有序的
			{
				for(int j=h[i];j;j=e[j].nxt)
				{
					int v=e[j].v;
					printf("%d %d\n",i,v);
				}
			}
			for(int i=1;i<=cnt2;++i)//指向为拓扑序小的指向拓扑序大的
			{
				if(top[ej[i][0]]>top[ej[i][1]])	printf("%d %d\n",ej[i][1],ej[i][0]);
				else	printf("%d %d\n",ej[i][0],ej[i][1]);
			}
		}
		else	printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Mine_King (赞：0)

## Problem

[CF1385E Directing Edges](https://www.luogu.com.cn/problem/CF1385E)

**题目大意：**

给你一张 $n$ 个点 $m$ 条边的图，其中一些边是有向边，其他的是无向边。现在要你给无向边定向使得最终的图示 DAG。问是否可行，若可行则给出每条边的方向。

## Solution

我们首先考虑如果全是无向边怎么做。  

我们知道一张 DAG 会有一个拓扑序。那么我们对于原图随便写个拓扑序，然后枚举每条边，让他从拓扑序小的点连向拓扑序大的点，可以确保这是一个 DAG。原因？只会从拓扑序小的点走向拓扑序大的点，所以不会出现环。  
这同时也告诉我们，如果全是无向边则一定有解。

现在有了有向边，那么我们不妨把图分开，有向边一组，无向边一组。  
对于有向边，如果出现环则一定无解。否则，相当于告诉了我们几组点的拓扑序大小关系。那么我们不妨直接在有向图上求拓扑序，这样有向图的条件就可以满足。  
然后我们就已经有了一个拓扑序，不需要再考虑有向边，于是问题就转化成了上面的全是无向边的问题。

所以这题的方法就是对于无向边跑出拓扑序，然后枚举每条边，使其从拓扑序小的点连向拓扑序大的点即可。

## Code

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=2e5+5;
int T,n,m,cnt;
int in[MAXN],topo[MAXN];
int t[MAXN],u[MAXN],v[MAXN];
struct graph
{
	int tot;
	int hd[MAXN];
	int nxt[MAXN],to[MAXN];
	void clear(int num)
	{
		tot=0;
		for(int i=1;i<=num;i++) hd[i]=0;
		return ;
	}
	void add(int u,int v)
	{
		nxt[++tot]=hd[u];
		hd[u]=tot;
		to[tot]=v;
		return ;
	}
}g;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		g.clear(n);
		for(int i=1;i<=n;i++) in[i]=topo[i]=0;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&t[i],&u[i],&v[i]);
			if(t[i]==1) g.add(u[i],v[i]),in[v[i]]++;
		}
		queue<int>q;
		for(int i=1;i<=n;i++)
			if(!in[i]) q.push(i);
		cnt=0;
		while(!q.empty())
		{
			int now=q.front();
			q.pop();
			topo[now]=++cnt;
			for(int i=g.hd[now];i;i=g.nxt[i])
				if(!--in[g.to[i]]) q.push(g.to[i]);
		}
		for(int i=1;i<=n;i++)
			if(in[i]){puts("NO");goto END;}
		puts("YES");
		for(int i=1;i<=m;i++)
			if(topo[u[i]]<topo[v[i]]) printf("%d %d\n",u[i],v[i]);
			else printf("%d %d\n",v[i],u[i]);
		END:;
	}
	return 0;
}
```

---

## 作者：HohleFeuerwerke (赞：0)

[引流](https://www.cnblogs.com/AllWeKnow/p/15521717.html)。

## 题目大意

给定一张 $n$ 个点，$m$ 条边的图 $G$，其中一部分边是有向边，一部分边是无向边。需要给所有给无向边定向，使得组成的新图是一个 DAG。

多测，$T\leq 2\times10^4$，$\sum n,\sum m\leq 2\times 10^5$。

## 符号及约定

$\operatorname{edge}(u,v)$ 表示节点 $u$ 和 $v$ 之间的边。$u\to v$ 表示一条从 $u$ 到 $v$ 的有向边。

## Solution

先忽视所有无向边。如果剩余的所有有向边不能组成 DAG，那么无论无向边怎么定向也没用。

接下来考虑有向边没有问题时如何构造可行解即可。

不妨对有向边组成的 DAG 进行 topo sort，得到第 $i$ 个节点的 topo sort 序不妨记为 $\operatorname{ord}(i)$。

任取一条无向边 $\operatorname{edge}(u,v)$，不妨令 $\operatorname{ord}(u)<\operatorname{ord}(v)$（反正是无向边，并且方向待定，没有区别）。那么直接令 $\operatorname{edge}(u,v)=u\to v$ 即可。原因是因为 $\forall u,v\in G'$（这里 $G'$ 是一个 DAG）满足 $\operatorname{ord}(u)<\operatorname{ord}(v)$，则不存在 $v\to u$ 这条边。

我们不妨形象地将 topo sort 所得的点序排列成一行，从左到右分别为 $\operatorname{ord}(u)=1,2,3,...,n$ 的节点。那么已经存在的构成 DAG 的边必然通通指向右边。

接下来我们也只需要保证我们所连的边也朝右，那么必然不可能存在环。

## 代码

```cpp
#include<bits/stdc++.h>
#define HohleFeuerwerke using namespace std
#pragma GCC optimize(3,"Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#define int long long
HohleFeuerwerke;
inline int read(){
	int s=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) s=s*10+c-'0';
	return s*f;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar('0'+x%10);
}
const int MAXN=1e6+5;
int T,n,m,cntEdge,head[MAXN],ind[MAXN];
struct edge{
	int type;
	int from,to,next;
}e[MAXN];
vector<int> topo;
int refl[MAXN];
inline void add(int t,int u,int v){
	cntEdge++; e[cntEdge].type=t;
	e[cntEdge].from=u,e[cntEdge].to=v;
	e[cntEdge].next=head[u],head[u]=cntEdge;
}
deque<int> q;
inline bool bfs(){
	for(int i=1;i<=n;i++){
		if(ind[i]==0) q.push_back(i);
	}
	while(!q.empty()){
		int u=q.front(); q.pop_front();
		topo.push_back(u);
		for(int i=head[u];i;i=e[i].next){
			if(e[i].type==1){
				int v=e[i].to;
				if(--ind[v]==0) q.push_back(v);
			}
		}
	}
	if(topo.size()==n) return true;
	return false;
}
signed main()
{
	T=read();
	while(T--){
		n=read(),m=read(),cntEdge=0;
		topo.clear(); q.clear();
		for(int i=1;i<=n+5;i++) ind[i]=head[i]=refl[i]=0;
		for(int i=1;i<=m;i++){
			int type=read();
			int u=read(),v=read();
			if(type==1) add(1,u,v),ind[v]++;
			else add(0,u,v);
		}
		if(bfs()){
			puts("YES");
			for(int i=1;i<=n;i++) refl[topo[i-1]]=i;
			for(int i=1;i<=m;i++){
				if(e[i].type==0){
					if(refl[e[i].to]<refl[e[i].from])	
						write(e[i].to),putchar(' '),write(e[i].from),puts("");
					else write(e[i].from),putchar(' '),write(e[i].to),puts("");
				}
				else write(e[i].from),putchar(' '),write(e[i].to),puts("");
			}
		}
		else puts("NO");
	}
}
```

---

## 作者：chenxia25 (赞：0)

>### [CF题目页面传送门](https://codeforces.com/contest/1385/problem/E)

>有一张$n$个点$m$条边的混合图，你需要给所有无向边定向，使得最终得到的有向图无环。或报告无解。本题多测。

>$\sum n\in\left[2,2\times10^5\right],\sum m\in\left[1,2\times10^5\right]$。

~~事实证明，这是本场最难的一题，因为我到最后才想出来~~

首先注意到，若不考虑所有无向边，剩下来的有向图是有环的，那显然无解。

然后呢？当时顺序做到这题的时候我想了DFS，Tarjan缩点（这个一年没写了，我已经不会了），都没有思路，却没有考虑到有向图上经常用到的拓扑排序（最后才想到）。考虑对不考虑所有无向边得到的有向图拓扑排序，那么无向边的定向方案很容易构造：拓扑序小的连向拓扑序大的即可保证无环。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int N=200000;
int n,m;
vector<pair<int,int> > nei[N+1];
int ideg[N+1];
vector<int> topo;
int id[N+1];
void toposort(){//拓扑排序 
	topo.clear();
	queue<int> q;
	for(int i=1;i<=n;i++)if(!ideg[i])q.push(i);
	while(q.size()){
		int x=q.front();
		q.pop();
		topo.pb(x);
		for(int i=0;i<nei[x].size();i++){
			int y=nei[x][i].X,z=nei[x][i].Y;
			if(z)/*不考虑无向边*/if(!--ideg[y])q.push(y);
		}
	}
}
void mian(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)ideg[i]=0,nei[i].clear();
	while(m--){
		int x,y,z;
		scanf("%d%d%d",&z,&x,&y);
		if(z)nei[x].pb(mp(y,z)),ideg[y]++;
		else nei[x].pb(mp(y,z)),nei[y].pb(mp(x,z));
	}
	toposort();
	if(topo.size()!=n)return puts("NO"),void();//无解 
	puts("YES");
	for(int i=0;i<n;i++)id[topo[i]]=i;
	for(int i=1;i<=n;i++)for(int j=0;j<nei[i].size();j++){
		int x=nei[i][j].X,y=nei[i][j].Y;
		if(y)printf("%d %d\n",i,x);
		else if(id[i]<id[x])printf("%d %d\n",i,x);//拓扑序小的连向拓扑序大的 
	}
}
int main(){
	int testnum;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

