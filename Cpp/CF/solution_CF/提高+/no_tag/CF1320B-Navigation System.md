# Navigation System

## 题目描述

The map of Bertown can be represented as a set of $ n $ intersections, numbered from $ 1 $ to $ n $ and connected by $ m $ one-way roads. It is possible to move along the roads from any intersection to any other intersection. The length of some path from one intersection to another is the number of roads that one has to traverse along the path. The shortest path from one intersection $ v $ to another intersection $ u $ is the path that starts in $ v $ , ends in $ u $ and has the minimum length among all such paths.

Polycarp lives near the intersection $ s $ and works in a building near the intersection $ t $ . Every day he gets from $ s $ to $ t $ by car. Today he has chosen the following path to his workplace: $ p_1 $ , $ p_2 $ , ..., $ p_k $ , where $ p_1 = s $ , $ p_k = t $ , and all other elements of this sequence are the intermediate intersections, listed in the order Polycarp arrived at them. Polycarp never arrived at the same intersection twice, so all elements of this sequence are pairwise distinct. Note that you know Polycarp's path beforehand (it is fixed), and it is not necessarily one of the shortest paths from $ s $ to $ t $ .

Polycarp's car has a complex navigation system installed in it. Let's describe how it works. When Polycarp starts his journey at the intersection $ s $ , the system chooses some shortest path from $ s $ to $ t $ and shows it to Polycarp. Let's denote the next intersection in the chosen path as $ v $ . If Polycarp chooses to drive along the road from $ s $ to $ v $ , then the navigator shows him the same shortest path (obviously, starting from $ v $ as soon as he arrives at this intersection). However, if Polycarp chooses to drive to another intersection $ w $ instead, the navigator rebuilds the path: as soon as Polycarp arrives at $ w $ , the navigation system chooses some shortest path from $ w $ to $ t $ and shows it to Polycarp. The same process continues until Polycarp arrives at $ t $ : if Polycarp moves along the road recommended by the system, it maintains the shortest path it has already built; but if Polycarp chooses some other path, the system rebuilds the path by the same rules.

Here is an example. Suppose the map of Bertown looks as follows, and Polycarp drives along the path $ [1, 2, 3, 4] $ ( $ s = 1 $ , $ t = 4 $ ):

Check the picture by the link [http://tk.codeforces.com/a.png](//tk.codeforces.com/a.png)

1. When Polycarp starts at $ 1 $ , the system chooses some shortest path from $ 1 $ to $ 4 $ . There is only one such path, it is $ [1, 5, 4] $ ;
2. Polycarp chooses to drive to $ 2 $ , which is not along the path chosen by the system. When Polycarp arrives at $ 2 $ , the navigator rebuilds the path by choosing some shortest path from $ 2 $ to $ 4 $ , for example, $ [2, 6, 4] $ (note that it could choose $ [2, 3, 4] $ );
3. Polycarp chooses to drive to $ 3 $ , which is not along the path chosen by the system. When Polycarp arrives at $ 3 $ , the navigator rebuilds the path by choosing the only shortest path from $ 3 $ to $ 4 $ , which is $ [3, 4] $ ;
4. Polycarp arrives at $ 4 $ along the road chosen by the navigator, so the system does not have to rebuild anything.

Overall, we get $ 2 $ rebuilds in this scenario. Note that if the system chose $ [2, 3, 4] $ instead of $ [2, 6, 4] $ during the second step, there would be only $ 1 $ rebuild (since Polycarp goes along the path, so the system maintains the path $ [3, 4] $ during the third step).

The example shows us that the number of rebuilds can differ even if the map of Bertown and the path chosen by Polycarp stays the same. Given this information (the map and Polycarp's path), can you determine the minimum and the maximum number of rebuilds that could have happened during the journey?

## 样例 #1

### 输入

```
6 9
1 5
5 4
1 2
2 3
3 4
4 1
2 6
6 4
4 2
4
1 2 3 4```

### 输出

```
1 2```

## 样例 #2

### 输入

```
7 7
1 2
2 3
3 4
4 5
5 6
6 7
7 1
7
1 2 3 4 5 6 7```

### 输出

```
0 0```

## 样例 #3

### 输入

```
8 13
8 7
8 6
7 5
7 4
6 5
6 4
5 3
5 2
4 3
4 2
3 1
2 1
1 8
5
8 7 5 2 1```

### 输出

```
0 3```

# 题解

## 作者：xht (赞：6)

当一次决策不是最优的时候，必须 rebuild。

当一次决策是最优的，但是同时还有其他最优的决策，可以 rebuild。

当一次决策是最优的，同时没有其他最优的决策，不能 rebuild。

因此建反图跑一遍最短路，由于边权为 $1$，bfs 即可。

```cpp
const int N = 2e5 + 7;
int n, m, k, v[N], a[N], d[N];
vi e[N], g[N];
queue<int> q;

int main() {
	rd(n), rd(m);
	for (int i = 1, x, y; i <= m; i++)
		rd(x), rd(y), e[x].pb(y), g[y].pb(x);
	rd(k), rda(a, k);
	q.push(a[k]), v[a[k]] = 1;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (auto y : g[x])
			if (!v[y]) q.push(y), d[y] = d[x] + 1, v[y] = 1;
	}
	int c1 = 0, c2 = 0;
	for (int i = 1; i < k; i++) {
		int x = a[i], y = a[i+1];
		bool b1 = 0, b2 = 0;
		for (auto z : e[x])
			if (d[z] < d[y]) b1 = 1;
			else if (y != z && d[z] == d[y]) b2 = 1;
		if (b1) ++c1;
		else if (b2) ++c2;
	}
	print(c1, ' '), print(c1 + c2);
	return 0;
}
```

---

## 作者：123456zmy (赞：3)

题意：  
给你一张有向图，再给你一个路径，在路径的每一步上都维护最短路，如果不是按照最短路走就更新最短路，输出最小或最大更新次数（有最小或最大是因为最短路不唯一）。
___
要求到同一点的最短路，考虑把图反向再进行计算，先用一遍 BFS 跑出最短路（因为边权都为 $1$ 所以用 BFS）如果一个点到终点的最短路有不是去要去下一个去地方那么最大答案 $+1$ ，如果要去的下一个地方没在目前任何一条到终点的最短路上，则最小答案 $+1$ （这东西可以在 BFS 的时候顺便求出来）。~~交了 5 遍身败名裂~~。

代码：（~~邪教码风，建议不要学习~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,a[200001],a1[200001],a2[200001],k,p[200001],ansl,ansr,dis[200001],p1[200001],ans1[200001],ans2[200001];
void bfs(int i)
{
	queue<int>q;
	q.push(i);
	while(!q.empty())
	{
		int a3=a2[q.front()];
		while(a3)
		{
			if(dis[a[a3]]==0||dis[a[a3]]==dis[q.front()]+1)
			{
				dis[a[a3]]=dis[q.front()]+1;
				if(dis[a[a3]]==0)q.push(a[a3]);
				if(p1[a[a3]])
				{
					if(p[p1[q.front()]-1]==a[a3])++ans1[a[a3]];
					else ++ans2[a[a3]];
				}
			}
			a3=a1[a3];
		}
		q.pop();
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		a[i]=u;
		a1[i]=a2[v];
		a2[v]=i;
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&p[i]);
		p1[p[i]]=i;
	}
	dis[p[k]]=1;
	bfs(p[k]);
	for(int i=1;i<=n;i++)
	{
		if(ans2[i])
		{
			++ansr;
			if(!ans1[i])++ansl;
		}
	}
	printf("%d %d",ansl,ansr);
	return 0;
}
```

---

## 作者：formkiller (赞：3)

### Problem:
给出 $N$ 个点，$M$ 条边的有向图，且边的长度均为 $1$。现有个导航系统，你事先知道目的地，系统会帮你规划一条最短路径（如果有很多条会选其中一条）。给出你的行进路线（不一定是最短路径），行进路线末尾一定是终点。当你走到的下一个点不是规划路径的下一个点时，系统会重新规划路径。求系统规划路径改变次数的最大值和最小值。


------------
### Solution:
显然如果我们可以处理出每个点到终点的最短路径长度那么答案就可以直接通过行进路线两两比较得出。但是由于 $N$ 太大不能直接做 $N$ 次最短路，但是我们注意到他们的终点是一定的，所以我们考虑从终点开始反向求最短路，所以存边的时候要反向建一条从 $v$ 到 $u$ 的边，并打上标记区别原来的边和反向边。

行进路线中，若从点 $c_i$ 行进到 $c_{i+1}$ 没有重新规划，仅当 $f(c_i) == f(c_{i+1}) + 1$ 时，否则一定发生了重新规划。我们用一个变量 $ans$ 记录下一定发生了重新规划的次数。同时注意到若点 $c_{i+1}$ 存在不止一条的最短路径，那么从点 $c_i$ 行进到 $c_{i+1}$ 也可能发生重构。我们将可能发生重构的次数用变量 $Ans$ 保存。最短路路径数在一开始求最短路的时候可以用数组记录。

**要注意的是：** 我们求最短路时可以发现我们是用离终点近的点去更新离终点远的点，所以我们要用 bfs 求最短路，而不是 dfs。 

### Code:

```cpp
//good luck
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <string>
# include <algorithm>

#define LL long long
#define maxn int(4e5+5)
#define is(a) (a>='0'&&a<='9')

using namespace std;

int N,M,K,ans,Ans,a[maxn],f[maxn],cnt[maxn];
int ver[2][maxn],nt[2][maxn],hd[2][maxn],tot[2];
int tail,que[maxn],vis[maxn],q[maxn];

inline void read(int &x)
{
  x=0;bool f=0;char ch=getchar();
  for (;!is(ch);ch=getchar()) f|=ch=='-';
  for (;is(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
  x=f?-x:x;
}

inline void addedge(int x,int y,int v)
{
	++tot[v]; nt[v][tot[v]] = hd[v][x]; ver[v][tot[v]] = y; hd[v][x] = tot[v];
}

inline void Bfs1(int x,int v)
{
	que[++tail] = x; vis[x] = 1; q[1] = x;
	int h=1,t=1;
	while (h<=t)
	{
		int x = q[h];
		for (int i = hd[v][x]; i ;  i = nt[v][i])
		{
			int y = ver[v][i];
			if (vis[y]) continue;
			vis[y]=1;
			que[++tail] = y;
			q[++t] = y;
		}
		++h;
	}
}

inline void Dfs2(int x,int v)
{
	vis[x] = 1;
	for (int i = hd[v][x]; i ; i = nt[v][i])
	{
		int y = ver[v][i];
		if (f[y]!=1e9)
		{
			if (f[x]>f[y]+1) f[x]=f[y]+1,cnt[x]=1;
			else if (f[x]==f[y]+1) ++cnt[x];
		}
	}
}

int main()
{
//	freopen("a.in","r",stdin);
	read(N); read(M);
	for (int i = 1; i <= M; ++i)
	{
		int x,y;
		read(x); read(y);
		addedge(x,y,0);
		addedge(y,x,1);
	}
	read(K);
	for (int i = 1; i <= K; ++i) read(a[i]);
	Bfs1(a[K],1);
	for (int i = 1; i <= N; ++i) f[i]=1e9,cnt[i]=1,vis[i]=0;
	f[a[K]]=0;
	for (int i = 1; i <= N; ++i)
	{
		Dfs2(que[i],0);
	}
	for (int i = 2; i <= K; ++i)
	{
		if (f[a[i]]!=f[a[i-1]]-1) ++ans;
		else
		{
			if (cnt[a[i-1]]>1) ++Ans;
		}
	}
	printf("%d %d\n",ans,ans+Ans);
    return 0;
}
```

---

## 作者：K0stlin (赞：3)

被这题坑了4次。。。

首先要想知道导航提供的最短路径，必须反向从t点跑最短路。倘若Polycarp下一个要走的点不是最短路径中的，ans1++,ans2++;倘若Polycarp下一个要走的点是最短路径中的，但有多条最短路径，ans2++。

![](https://cdn.luogu.com.cn/upload/image_hosting/rjbi410k.png)

（u是当前点）
### 注意：如果直接用最短路计数的话，u点最短路径有2条，但都是u->v后的，这是导航无法提供另一条路径，所以要对u指向的每个点进行计数（除了Polycarp要走的点）。

CODE:
```cpp
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N=2e5+5;
int n,m,cnt,a[N],hd[N],num,x,y,f[N],ans1,ans2;
struct cz {
	int nxt,to;
}e[N<<1];
struct jd {
	int x,s;
	bool operator <(const jd &w) const {
		return s>w.s;
	}
}k;
priority_queue<jd> q;
bool vis[N];
inline int read() {
	int x=0,flag=0;char ch=getchar();
	while(ch<'0'||ch>'9'){flag|=(ch=='-');ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return flag?-x:x;
}
inline void add(int x,int y) {
	e[++num]=(cz) {hd[x],y};
	hd[x]=num;
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;++i) {
		x=read();y=read();
		add(x,y);add(y,x);//i&1说明是正向边，反之为反向边
	}
	cnt=read();
	for(int i=1;i<=cnt;++i)
		a[i]=read();
	memset(f,127,sizeof f);
	f[a[cnt]]=0;
	q.push((jd){a[cnt],0});
	while(!q.empty()) {//dijstra,当然可以用BFS，因为边权为1
		k=q.top();q.pop();
		if(vis[k.x]) continue;
		vis[k.x]=1;
		for(int i=hd[k.x];i;i=e[i].nxt) {
			if(i&1) continue;
			if(f[e[i].to]>f[k.x]+1) {
				f[e[i].to]=f[k.x]+1;
				if(!vis[e[i].to]) q.push((jd){e[i].to,f[e[i].to]});
			}
		}
	}
	for(int i=1;i<cnt;i++) {
		int u=a[i],tot=0;
		for (int j=hd[u];j;j= e[j].nxt) {
			if(!(j&1)) continue;
			int v=e[j].to;
			if(f[u]==f[v]+1)
				tot++;
		}
		if(f[u]==f[a[i+1]]+1)
		{
			if(tot>1)
				ans2++;
		} else {
			ans1++;
			ans2++;
		}
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}

```
-完-

---

## 作者：liqiqi (赞：0)

题意：
给定经过k个点的路径，问这个k个点中每个点到达终点的最短路径是否会由原来的路径改变。输出最小改变次数和最大改变次数。


1.设（u，v）为u点到达v点，因为每个点的终点都是最后一个点，所以我们可以反向建边，终点跑迪杰斯特拉。

2.d[ ]是该点到终点的最短路径，如果d[u]!=d[u+1]+1说明导航给的路径不是最短路径，需要重新设计路线，则ans1++,ans2++。

3，如果d[u]==d[u+1]+1，说明该路线是最短路径，再判断是否还有其他路径，如果有的话ans2++。
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>g[200001];
typedef pair<int, int>p;
int v[200001];
vector<int> h[200001];
int d[200001];
int n, m;
int a[200001];
int w;
void dij()
{

	priority_queue<p, vector<p>, greater<p> >q;
	q.push(make_pair(0, a[w]));
	fill(d+1, d +n+1, 1e8);
	d[a[w]] = 0;
	while (q.size())
	{
		p node = q.top();
		q.pop();
		if (v[node.second])
			continue;
		v[node.second] = 1;
		for (int i = 0; i < h[node.second].size(); i++)
		{
			
			
			if (d[h[node.second][i]] > d[node.second] + 1)
			{
				d[h[node.second][i]] = d[node.second] + 1;
				q.push(make_pair(d[h[node.second][i]], h[node.second][i]));
					
			}
			
		}

	}


}
int main()
{
	
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		h[y].push_back(x);
	}
	
	cin >> w;
	for (int i = 1; i <= w; i++)
	{
		cin >> a[i];
		
	}
	dij();
	int ans1= 0;
	int ans2 = 0;
	for (int i = 1; i < w; i++)
	{
		int x = a[i], y = a[i + 1];
		if (d[x] != d[y] + 1)
		{
			ans1++;
			ans2++;
		}
		else
		{
			for (int j = 0; j < g[x].size(); j++)
			{
				int e = g[x][j];
				if (d[e] == d[x] - 1 && e != y)
				{
					ans2++;
					break;
				}
			}
		}
	}
	cout << ans1 << " " << ans2 << endl;
}
```



---

## 作者：Fairicle (赞：0)

## 题意简述

这是一个 $n$ 个节点，$m$条边的有向图。

Polycarp 住在 $s$ 点，他每天会经过 $k$ 个不重复的点到达  $t$ 点，也就是说 $k_1=s,k_2=t$。

他的导航是这样的：在当前的点 $k_i$，会在 $k_i$ 所有的前往 $t$ 点的最短路线中选择一条。如果移动到下一个点 $k_{i+1}$ 且没有按照导航的规划路线走，导航会**重新规划**。

你需要求出最小和最大的重新规划次数。

看到这道题我第一想法就是最短路。事实上我们确实需要跑一遍最短路，我的做法是建立反图，以 $t$ 点为源点跑单源最短路，求出每个点的 $dis$。

接下来我们考虑如何统计答案。

假设现在是在 $k_i$，离 $t$ 点的最短距离为 $dis_{k_i}$。
 
#### case 1：$dis_{k_i}$ $+$ $1$ $=$ $dis_{k_{i+1}}$

此时一定可以做到不加最小规划次数，而是否加最大规划次数取决于 $k_i$ 是否有其他的儿子（暂且这么称呼） $j$ 使得 $dis_j$ $=$ $dis_{k_{i+1}}$。如果有，最大规划次数加一，因为可以选这条最短路而不选 $k_{i+1}$。

#### case 2：$dis_{k_i}+1$ $\ne$ $dis_{k_{i+1}}$

此时 $dis_{k_i}$ 必然小于等于 $dis_{k_{i+1}}$ ~~（想一想，为什么）~~

则 $dis_{k_i}$ 一定是由另外一个dis更小的儿子加一更新而来，所以此时必定重新规划，最小最大规划次数都加一。

code：
```
#include"bits/stdc++.h"
using namespace std;
#define ll long long
int head[200010],revhead[200010],wl,revwl;
struct node{
	int nxt,to;
}star[200010],revstar[200010];
inline void add(int from,int to){
	wl++;
	star[wl].to=to;
	star[wl].nxt=head[from];
	head[from]=wl;
}
inline void revadd(int from,int to){
	revwl++;
	revstar[wl].to=to;
	revstar[wl].nxt=revhead[from];
	revhead[from]=revwl;
}
int k,p[200010],t,s,dis[200010];
queue<int> q;
inline void bfs(){
	q.push(t);
	memset(dis,0x3f,sizeof(dis));
	dis[t]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(ri i=revhead[u];i;i=revstar[i].nxt)
		{
			int v=revstar[i].to;
			if(dis[v]==0x3f3f3f3f) dis[v] = dis[u] + 1,q.push(v);
 		}
	}
}
int n,m,ans,tot;
int main()
{
	n=read(),m=read();
	for(ri i=1;i<=m;++i)
	{
		int x,y;
		x=read(),y=read();
		add(x,y);revadd(y,x);
	}
	k=read();
	for(ri i=1;i<=k;++i) p[i]=read();
	s=p[1],t=p[k];
	bfs();
	for(ri i=1;i<k;++i)
	{
		int u=p[i];
		if(dis[p[i+1]]+1!=dis[p[i]]) ans++;
		else
		{
			for(ri j=head[u];j;j=star[j].nxt)
			{
				int v=star[j].to;
				if(v==p[i+1]) continue;
				if(dis[v]==dis[p[i+1]])
				{
					tot++;
					break;
				}
			}
		}
	}
	cout<<ans<<" "<<ans+tot<<endl;
    return 0;
}
```


---

## 作者：Scintilla (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1320B) && [CF传送门](https://codeforces.com/contest/1320/problem/B)
### 思路
显然我们需要处理出每个点到终点的最短距离，因为没有边权，反向建图 $BFS$ 跑一遍即可。记 $d[i]$ 为终点到 $i$ 的最短距离，$nmin,nmax$ 分别为最小和最大的可能值。

对于 $\forall1<i<p$ ，若 $d[p[i]]>=d[p[i - 1]]$ ，那意味着这一步不是最优，所以当前路径肯定会重建， $nmin,nmax$ 都要加一。

否则当前这一步即是最优解。此时若由 $p[i-1]$ 可以走到不少于两个这样的最优解，则把 $nmax$ 加一，因为系统有可能选择的是另一条路径。

最后输出 $nmin,nmax$ 即可~~水~~过此题。

注意，这个思路需要建两个图：正向图用来枚举 $p[i-1]$ 可以走到的点；反向图用来求最短距离。

### $Code:$
```cpp
//author: TYGZ
//result: Accepted
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define mp make_pair
#define pb push_back
#define Rep(i, s, e) for (re int i = s; i <= e; ++i)
#define Dep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

const int N = 200010;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = false; c = getchar();}
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

int n, m, k, p[N];

struct EE {
    int tot, head[N];
    struct node {int nxt, to;} edge[N];
    il void Add_New(int u, int v) {edge[++tot].nxt = head[u]; edge[tot].to = v, head[u] = tot;}
} pre, dic;

int d[N];
bool used[N];

il void BFS(int s) {
    queue<pair<int, int> > Q;
    Q.push(mp(s, 0));
    while (!Q.empty()) {
        int u = Q.front().first, dis = Q.front().second; Q.pop();
        if (used[u]) continue;
        used[u] = true, d[u] = dis;
        for (int e = dic.head[u]; e; e = dic.edge[e].nxt) Q.push(mp(dic.edge[e].to, dis + 1));
    }
    return;
}

int nmin, nmax;
int main() {
    n = read(), m = read();
    Rep(i, 1, m) {
        int u = read(), v = read();
        dic.Add_New(v, u), pre.Add_New(u, v);
    }
    k = read();
    Rep(i, 1, k) p[i] = read();
    BFS(p[k]);
    Rep(i, 2, k - 1) {
        if (d[p[i]] >= d[p[i - 1]]) ++nmin, ++nmax;
        else {
            int tp = 0;
            for (int e = pre.head[p[i - 1]]; e; e = pre.edge[e].nxt) {
                if (d[pre.edge[e].to] == d[p[i - 1]] - 1) {
                    ++tp; //即最优解数量
                    if (tp >= 2) break;
                }
            }
            if (tp >= 2) ++nmax;
        }
    }
    printf("%d %d", nmin, nmax);
    return 'P' & 'Y' & 'Q' & 'T' & 'Q' & 'L' & '%' & '%' & '%'; //顺便膜一发我们机房的神仙pyqpyq
}
```

---

## 作者：legend_life (赞：0)

# [CF1320B Navigation System](http://codeforces.com/contest/1320/problem/B)

~~毒瘤题干：题干过长，引起不适~~（逃

**简单BFS**

从终点往BFS一遍，记录每个点的 $dis$ 和 $num$ 值。

分情况讨论，

## 1. 如果 $dis_{p_{i}} \ne dis_{p_{i + 1}} + 1$  
下一步肯定要更新，因为 $p_{k}$ 到 $p_{i}$ 的最短路肯定	不会经过 $p_{i + 1}$ 这个点（读者可自行画图理解）  

这样更新即可：
	
```cpp
++ mn, ++ mx;
```

## 2. 如果 $dis_{p_{i}} = dis_{p_{i + 1}} + 1$  
### I. 如果 $num_{p_{i}} = 1$  
不可能导航到另一条路上，直接过就好
### II. 如果 $num_{p_{i}} > 1$
可能导航到另一条路上，也可能导航准确

这样更新即可：

```cpp
++ mx;
```

注意：我代码里的 $num$ 数组全部减了一

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;

int read()
{
	char c = getchar(); int flag = 1, ans = 0;
	while (c < '0' || c > '9') {if (c == '-') flag = -flag; c = getchar();}
	while (c >= '0' && c <= '9') {ans = ans * 10 + c - '0'; c = getchar();}
	return ans * flag;
}

const ll INF = 1e16;
const int MAXN = 200020;
int head1[MAXN], head[MAXN], d[MAXN], a[MAXN], num[MAXN];
bool vis[MAXN];
int n, m, cnt, cnt1, k, mx, mn;

struct Edge
{
	int to;
	int nxt;
}e[MAXN], e1[MAXN];

void AddEdge (int from, int to)
{
	e1[++ cnt1].to = to;
	e1[cnt1].nxt = head1[from];
	head1[from] = cnt1;
	
	e[++ cnt].to = from;
	e[cnt].nxt = head[to];
	head[to] = cnt;
}

void bfs()
{
	for (int i = 1; i <= n; ++ i)
		d[i] = 0x3f3f3f3f;
	queue<int> q;
	q.push(a[k]);
	d[a[k]] = 0;
	while (!q.empty())
	{
		int tmp = q.front();
		q.pop();
		vis[tmp] = true;
		for (int i = head[tmp]; i; i = e[i].nxt)
		{
			int v = e[i].to;
			if (vis[v] == true)
				continue;
			if (d[v] > d[tmp] + 1)
			{
				d[v] = d[tmp] + 1;
				q.push(v);
			}
			else if (d[v] == d[tmp] + 1)
				++ num[v];
		}
	}
}

int main()
{
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= m; ++ i)
	{
		int u, v;
		scanf ("%d%d", &u, &v);
		AddEdge (u, v);
	}
	scanf ("%d", &k);
	for (int i = 1; i <= k; ++ i)
		scanf ("%d", &a[i]);
	bfs();
	for (int i = 1; i < k; ++ i)
	{
		if (d[a[i + 1]] + 1 == d[a[i]])
			mx += min (num[a[i]], 1);
		else
			++ mn, ++ mx;
	}
	//for (int i = 1; i <= n; ++ i)
	//	printf ("%d %d %d\n", i, d[i], num[i]);
	printf ("%d %d\n", mn, mx);
	return 0;
}
```

---

## 作者：Reanap (赞：0)

这道题不难，大家应该都可以在读完题后5分钟内想到思路。

从问题的本质进行分析，我们有一个最清真的想法：

枚举他所走的地点，看当前走的地点是否存在一条最短路。

这显然是一个$n^2$的做法，很麻烦。

所以我们可以考虑预处理出下一个位置是否是当前位置到目标位置的一条最短路之一。

怎么办呢？我们可以建立每一个点到达终点的最短距离用$dis$数组保存，如果$dis_{p_i} = dis_{p_{i+1}}$,那么这就可以是导航所导出来的一条路。关于这个$dis$数组，我们可以建立一个反图，然后从终点开始跑DFS,这样就好了。

然后分类讨论：

1、求最少导航，即若下一个位置可以是导航导出来的$ans$就不变，否则$ans+1$

2、求最多导航，即下一个位置只要不是唯一的最短路，$ans$就加一。


```cpp
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 2e5 + 5;
vector <int> G1[MAXN];
vector <int> G2[MAXN];
int n , m , k , p[MAXN] , dis[MAXN];
int ans1 , ans2;
void bfs() {
	queue <int> q;
	q.push(p[k]);
	dis[p[k]] = 1; 
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G2[x].size(); ++i) {
			if(!dis[G2[x][i]]) {
				dis[G2[x][i]] = dis[x] + 1;
				q.push(G2[x][i]);
			}
		}
	}
}
void dfs1(int id) {
	if(id == k) return;
	int x = p[id];
	if(dis[p[id + 1]] == dis[x] - 1) dfs1(id + 1);
	else {
		ans1 ++;
		dfs1(id + 1); 
	}
}
void dfs2(int id) {
	if(id == k) return;
	int x = p[id];
	if(dis[p[id + 1]] != dis[x] - 1) {
		ans2 ++;
		dfs2(id + 1);
		return;
	}
	for (int i = 0; i < G1[x].size(); ++i) {
		if(G1[x][i] != p[id + 1] && dis[G1[x][i]] == dis[x] - 1) {
			ans2 ++;
			dfs2(id + 1);
			return;
		}
	}
	dfs2(id + 1);
	return;
}
int main() {
	scanf("%d %d" , &n , &m);
	for (int i = 1; i <= m; ++i) {
		int u , v;
		scanf("%d %d" , &u , &v);
		G1[u].push_back(v);
		G2[v].push_back(u);
	}
	scanf("%d" , &k);
	for (int i = 1; i <= k; ++i) scanf("%d" , &p[i]);
	bfs();
	dfs1(1);
	dfs2(1);
	printf("%d %d" , ans1 , ans2);
	return 0;
}
```

---

## 作者：dead_X (赞：0)

## 1 题意简述
输入起点，终点，和一张 $n$ 个点， $m$ 条边的稀疏图  $(n,m\leq2\times10^5)$ ，并输入一条长度为 $q$ ，起点终点确定的路径，求路径中有几条边在当前起点对应最终终点的最短路径上。
## 2 思路简述
反向连边

稀疏图跑dij，记录最短路以及最短路的条数

然而记录最短路条数需要重新正向连一次边
## 3 代码
```
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int to=0,nxt=0;
}a[1000003],b[1000003];
int HEad[1000003],hEAd[1000003],cnt=0,cnT=0,dis[1000003];
int vis[1000003];
inline int read()
{
	int x=0; char ch=getchar();
	while(ch<'0' || ch>'9') ch=getchar();
	while(ch>='0' && ch<='9') x*=10,x+=(int)ch-48,ch=getchar();
	return x;
}
inline void add(int u,int v)
{
	a[++cnt].to=v,a[cnt].nxt=HEad[u],HEad[u]=cnt;
	int uu=v,vv=u;
	b[++cnT].to=vv,b[cnT].nxt=hEAd[uu],hEAd[uu]=cnT;
}
int p[1000003],qwq[1000003];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q;
int main()
{
	int n=read(),m=read(),u,v;
	for(int i=1; i<=n; ++i) dis[i]=999999999;
	for(int i=1; i<=m; ++i) u=read(),v=read(),add(v,u);
	int q=read();
	for(int i=1; i<=q; i++) p[i]=read();
	int sdt=p[q];
	dis[sdt]=0,Q.push(make_pair(0,sdt));
	while(!Q.empty())
	{	
		int x=Q.top().first,y=Q.top().second;
		Q.pop();
		if(vis[y]) continue; else vis[y]=1;
		for(int i=HEad[y]; i; i=a[i].nxt) if(dis[a[i].to]>x+1) 
		{
			dis[a[i].to]=x+1;
			if(!vis[a[i].to]) Q.push(make_pair(dis[a[i].to],a[i].to));
		}
	}
	//for(int i=1; i<=n; i++) cout<<dis[i]<<' '; cout<<'\n';
	for(int i=1; i<=n; i++) for(int j=hEAd[i]; j; j=b[j].nxt) 
	{
		if(dis[b[j].to]==dis[i]-1) qwq[i]++;
	}
	//for(int i=1; i<=n; i++) cout<<qwq[i]<<' '; cout<<'\n';
	int Min=0,Max=0;
	for(int i=1; i<q; i++) if(dis[p[i]]!=dis[p[i+1]]+1) ++Min,++Max; else if(qwq[p[i]]>1) ++Max; 
	cout<<Min<<' '<<Max;
	return 0;
}
```
## 4 评价
赛时想出做法所用时间:0min

比赛A掉所用时间:35min

建议难度:绿

dij好难调/kk

---

