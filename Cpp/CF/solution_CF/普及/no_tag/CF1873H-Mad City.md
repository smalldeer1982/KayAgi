# Mad City

## 题目描述

Marcel 和 Valeriu 住在一座包含 $n$ 座建筑物和 $n$ 条无向边的城市。

初始时，Marcel 和 Valeriu 分别处于建筑物 $a$ 和建筑物 $b$。 Marcel 想要抓住 Valeriu。Valeriu 被 Marcel 抓住，当且仅当二人在某一时刻处于同一条边或同一座建筑物中。

在每次行动中，他们会选择移动到一个相邻的建筑物中，或停留在原地。由于 Valeriu 十分了解 Marcel，Valeriu 能够预测出 Marcel 的下一步行动。Valeriu 可以利用这些信息来制定行动路线。二人同时开始和结束行动。

对于任何两个建筑物，有且仅有一条路径将二者相连。

假设二人都绝顶聪明，判断 Valeriu 是否能够永远不被 Marcel 抓住。

## 样例 #1

### 输入

```
6
3 2 1
2 1
3 2
1 3
4 1 4
1 4
1 2
1 3
2 3
4 1 2
1 2
2 3
2 4
3 4
7 1 1
4 1
2 1
5 3
4 6
4 2
7 5
3 4
8 5 3
8 3
5 1
2 6
6 8
1 2
4 8
5 7
6 7
10 6 1
1 2
4 3
5 8
7 8
10 4
1 9
2 4
8 1
6 2
3 1```

### 输出

```
YES
NO
YES
NO
NO
YES```

# 题解

## 作者：_Ink (赞：21)

## 题意

给出一张有 $n$ 个点与 $n$ 条边的无向图，图上 $a,b$ 两点分别站了两个人 $A,B$。$A$ 要试图抓住 $B$。

对于一次行动，两人可选择移向另一个点或者留在原地不动。对于每次行动，两人均同时开始与结束移动。

他们互相知道对方的位置，且两人都足够聪明。问 $B$ 是否能永远逃脱 $A$。

### 数据范围

多组测试数据。测试数据个数 $t$ 满足 $1\le t \le1000$。

$3\le n \le 2⋅10^5$，$1\le a,b \le n$

所有测试数据的 $n$ 之和不超过 $2⋅10^5$。

保证数据无自环，无重边。

## 题解

首先，给出的图满足有 $n$ 个点与 $n$ 条边，也就是点与边数相同。换言之，这个图是一颗基环树，也就是仅有一个环的“树”（可以理解为一棵树加了一条边）。

而 B 想要永久逃脱 A，那么，只要 B 到达了环上，由于 A,B 同时开始与结束移动，这样就能满足永久逃脱的条件了。

而基环树中仅有一个环，所以显然的是，如果 B 最开始的时候不在环上，那么对 B 来说，有且仅有一个点可以让他走到环上。如果把环删去，图分为多个子区域，这个点就是环与 B 所在子区域的连接点。

![](https://cdn.luogu.com.cn/upload/image_hosting/3045cqmk.png)

就像这张图，如果 B 在 $6,7,8,9$ 这几个点上，那么他必须走到 $5$ 号点才会到达环上。这个点存在且仅有唯一一个。

我们记这个点为 $\text{tag}$ 点。判断 A 是否能够抓到 B 显然就取决于 A, B 分别到 $\text{tag}$ 点的距离。如果 A 能提前于 B 到 $\text{tag}$ 点，A 就能截住 B。反之，B 就可以成功到环上。

拿上面的图举例来说，假设 A 在 $10$，如果 $B$ 在 $9$，显然他们离 $5$ 号点的距离都为 $3$，A 恰好能截住 B；而如果 B 在 $8$，B 与 $\text{tag}$ 的距离为 $2$，此时 A 来不及在 $5$ 号点截住 B，B 就能无限期逃脱了。

所以我们显然就能得出结论：**如果 B 开始不在环上，当 $dis_{A,tag} > dis_{B,tag}$，B 能够永久逃脱，否则，B 就会被抓住。**

当然，如果 B 一开始便在环上且 A, B 的起始位置不同，那也是必然能逃脱的。

---

$\\$

所以到此为止，这道题的瓶颈便在于：如果 B 不在环上，如何求得 $\text{tag}$ 点，并求出 A, B 与 $\text{tag}$ 点的距离。

首先是求 $\text{tag}$ 点。显然 $\text{tag}$ 点必然在环上，我们需要去判环。在这里，我认为最适合判环的工具是**拓扑**，我们可以在拓扑的过程中，顺便把 $\text{tag}$ 点的位置处理出来。

如何用拓扑处理呢？

我们知道拓扑排序的过程中会一步步去删点删边，最后只剩下一个环。所以我们可以把 $\text{tag}$ 值初始化为 B 所在的点。当 $\text{tag}$ 所在的点将被删时，由拓扑排序的特性，此时仅有一条边与其相连，所以我们可以在删这个点时顺势把 $\text{tag}$ 值更新到与被删点相连的那个点上。

由于拓扑排序不会删掉环上的点，所以当 $\text{tag}$ 值不停更新，直到更新到环上的点时就不再发生变化。此时，$\text{tag}$ 值就是我们想要的那个点的编号了。

获得了 $\text{tag}$ 点的位置，那么求得 A, B 与其的距离其实就很简单了——直接爆搜。从 $\text{tag}$ 点开始搜索，搜到 A, B 就记录与其的距离即可。

按照上述结论判断大小关系就可以了。当然如果 B 就在环上且 A, B 不在同一个位置，那直接输出 `YES` 就行。判断 B 是否在环上，只需要判断在拓扑删点删边后 B 所在的点入度是否为 $0$ 即可。

（需要注意的是，本题建图为无向图，所以拓扑时点可删去的条件为该点入度为 $1$，当点入度大等于 $2$ 时这个点是删不掉的。删点后，剩余的在环上的点入度均为 $2$）

这个做法相当的暴力且优雅，时间复杂度 $O(n)$。

## $\text{Code:}$

```cpp

#include<bits/stdc++.h>
#define maxn 200060
#define inf 0x3f3f3f3f
using namespace std;

int t;
int n, a, b;
int head[maxn << 1], nxt[maxn << 1], to[maxn << 1], cnt, rd[maxn];
//建无向图，一定要开二倍空间！！
bool vist[maxn], visd[maxn];
int tagn, disa, disb;

void add_edge(int u, int v)//链式前向星建图
{
	nxt[++ cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}

void clean()
{
	memset(rd, 0, sizeof(int)*(n + 10));
	memset(head, 0, sizeof(int)*(n + 10));
	memset(nxt, 0, sizeof(int)*(n + 10));
	memset(to, 0, sizeof(int)*(n + 10));
	memset(visd, false, sizeof(bool)*(n + 10));
	memset(vist, false, sizeof(bool)*(n + 10));
	tagn = 0, cnt = 0, disa = inf, disb = inf;
}

void topu(int x) //拓扑
{
	vist[x] = true;
	for(int i = head[x]; i; i = nxt[i])
	{
		int y = to[i];
		if(vist[y] || rd[y] == 0) continue;
		rd[y] --; rd[x] --;
		if(x == tagn) tagn = y; //点被删，转移 tag 位置 
		if(rd[y] != 1) continue;
		topu(y);
	}
	vist[x] = false;
}

void dfs(int x, int js) //爆搜搜距离 
{
	visd[x] = true;
	if(x == a) disa = min(disa, js);
	if(x == b) disb = min(disb, js);
	for(int i = head[x]; i; i = nxt[i])
	{
		int y = to[i];
		if(visd[y]) continue;
		dfs(y, js + 1);
	}
	visd[x] = false;
}

void _run()
{	
	cin >> n >> a >> b;
	clean();
	tagn = b;
	for(int i = 1; i <= n; i ++)
	{
		int u, v;
		cin >> u >> v;
		add_edge(u, v);
		add_edge(v, u);
		rd[u] ++; rd[v] ++;
	}
	
	for(int i = 1; i <= n; i ++)
		if(rd[i] == 1) topu(i);
	
	if(rd[b] >= 2 && a != b) {cout << "YES\n"; return;}
	else if(a == b) {cout << "NO\n"; return;}
	
	dfs(tagn, 0);
	if(disa > disb) cout << "YES\n";
	else cout << "NO\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t --) _run();
	
	return 0;
}
```

---

## 作者：I_am_AKed_by_NOI (赞：2)

## 前言

模拟赛最简单的一道题，我因为把 `NO` 打成了 `No`，痛失 $100$ 分，警示后人。

## 简化题意

给你由 $n$ 个点、$n$ 条边组成的无向图，$A,B$ 两人站在图上某两点，每一次行动，两人可移向相邻的点或原地不动。他们互相知道对方的位置，且两人都采取最优策略。问 $B$ 是否能永远不与 $A$ 相遇。

## 正解

由题可知，所给的图是一个基环树（有且仅有一个环的图。）

显然，如果在某一时刻， $A$ 和 $B$ 同处于基环树的环上，那么 $B$ 只要每一次都走与 $A$ 走的相同的方向，那么 $B$ 可以永远不与 $A$ 相遇。

有上可知，$B$ 的目标是要跑到一个环上，而 $A$ 的目标是要堵住 $B$ 的入环点，由基环树的性质可得， $B$ 的入环点有且仅有一个。更具体一点，统计 $B$ 到环的最短距离 $x$，统计 $A$ 到 $B$ 入环点的最短距离 $y$，比较两者大小，若 $y\le x$，输出 `NO`，否则输出 `YES`。

那么这就是一个在基环树上面找环的一个经典问题，我用的是拓扑排序找环。然后求最短距离的基本思想是深搜。代码如下，有注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
queue<int> q;
vector<int> son[N];
int T,n,a,b;
int u,v;
int vis[N],deg[N],judge[N];
int step,final,flag,step2;
queue<int> que;
int dist[N];
void top_sort() //类似于拓扑，把除了环以外的点全部标记，剩下的点就是环上的了
{
	while(!q.empty())
	{
		int now=q.front();
		vis[now]=1;
		q.pop();
		for(int i=0;i<son[now].size();i++)
		{
			int y=son[now][i];
			if(vis[y]==1) continue; //如果这个点的度为 1 那么它一定不再环上
			deg[y]--;
			if(deg[y]==1) 
			{
				q.push(y);
			}
		}
	}
}
void dfs1(int now,int fa,int dis) //找到到环的最短距离
{
	if(step!=-1) return ;
	if(vis[now]==0)
	{
		step=dis;
		final=now;
		return ;
	}
	for(int i=0;i<son[now].size();i++)
	{
		int y=son[now][i];
		if(y==fa) continue;
		dfs1(y,now,dis+1);
	}
}
void clean() //清空
{
	flag=0;
	step=-1,step2=114514191;
	final=0;
	for(int i=1;i<=n;i++)
	{
		son[i].clear();
		deg[i]=0;
		judge[i]=0;
		vis[i]=0;
		dist[i]=0;
	}
}
void bfs1(int x,int final) //找到入环点的最短距离
{
	que.push(x);
	judge[x]=1;
	dist[x]=0;
	while(!que.empty())
	{
		int now=que.front();
		que.pop();
		for(int i=0;i<son[now].size();i++)
		{
			int y=son[now][i];
			if(judge[y]==0) 
			{
				dist[y]=dist[now]+1;
				judge[y]=1;
				que.push(y);
			}
		}
	}
	step2=dist[final];
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&a,&b);
		clean();
		for(int i=1;i<=n;i++)
		{
			cin>>u>>v;
			son[u].push_back(v);
			son[v].push_back(u);
			deg[u]++;
			deg[v]++;
		}
		for(int i=1;i<=n;i++)
		{
			if(deg[i]==1)
			{
				q.push(i);
			}
		}
		top_sort();
		dfs1(b,-114514,0);
		bfs1(a,final);
		//cout<<step<<" "<<step2;
		if(step2<=step) //比较距离
		{
			cout<<"NO\n";
		}
		else
		{
			cout<<"YES\n";
		}
	}
}
/*
1
7 3 7
1 3
1 2
2 4
3 5
5 4
4 6
6 7
*/


```


---

## 作者：reclusive (赞：2)

[my blog](https://i.cnblogs.com/posts/edit;postId=17723861)

## 题意描述

马塞尔和瓦勒里乌（Valeriu）所在的疯狂城市由 $n$ 栋建筑和 $n$ 条双向道路组成。

马塞尔和瓦勒里乌（Valeriu）分别从 $a$ 号和 $b$ 号建筑开始。马塞尔想赶上瓦勒里乌（换句话说，与他在同一栋楼里或在同一条路上相遇）。

在每次移动过程中，他们都会选择前往当前建筑的邻近建筑或留在同一建筑中。由于瓦勒里乌（Valeriu）对马塞尔（Marcel）非常了解，因此瓦勒里乌（Valeriu）可以预测马塞尔（Marcel）下次搬家时会去哪里。瓦勒里乌（Valeriu）可以利用这些信息进行移动。他们同时开始和结束移动。

可以保证任何一对建筑物之间都有路径相连，而且任何一对建筑物之间最多只有一条路。

假设两位棋手都以最优方式下棋，请回答瓦勒里乌（Valeriu）是否有无限期逃离马塞尔（Marcel）的策略。

## 具体思路

我们知道树是 $n-1$ 条边的，因此再多加一条边，即 $n$ 条边的话就会出现环。

设逃离抓捕的人为 $s$，抓捕的人为 $t$。

根据样例 $1$，我们发现，如果 $s$ 在环上，那么 $t$ 将永远无法抓到 $s$。

![image](https://cdn.luogu.com.cn/upload/image_hosting/kkms8eq0.png?x-oss-process=image)

那么思路就很显然了。我们就是要尽量让 $s$ 快一点跑到环上。这不就是最短路？

当然如果 $s$ 一开始就在环上，那么就直接输出 YES 就好了。

我一开始的思路是先跑一遍 Tarjan 求出边双连通分量，即环。然后缩点，比较 $s$ 和 $t$ 到环的距离.

设 $dist(x)$ 表示点 $x$ 到环的距离。

若 $dist(s) \ge dist(t)$，那么就是让 $t$ 先到环上，那么输出 NO。

但是这种思路是有问题的。

![image](https://cdn.luogu.com.cn/upload/image_hosting/x3d7q1yd.png?x-oss-process=image)


如果 $s$ 是 $1$，$t$ 是 $5$，那么这两个点到环上的距离都是 $1$ ，理应输出 NO，但是我们发现，$s$ 跑到 $2$ 后，由于他们没有重合，因此 $t$ 将永远抓不到 $s$。

于是思路就变成了对 $s$ 找到环上最近的点，然后找 $t$ 到该点的距离，然后比较一下即可。

你可能会问 $s$ 不会与环上多个点相连吗？显然是不会的，因为你要是和两个点相连，那么就有两个环了，那么总边数就不是 $n$ 了。

设 $s$ 到环上最近的点为 $x$。

至于找 $t$ 到 $x$ 的距离，$O(Tn\log n)$ 感觉过不去，于是我用 $dfs$ 的方式来找 $t$ 到 $x$ 的距离。这样时间复杂度就是 $O(Tn)$ 的，感觉可过。

然后就又发现问题了。

![image](https://cdn.luogu.com.cn/upload/image_hosting/x7jm2pli.png?x-oss-process=image)

$s$ 是 $1$，$t$ 是 $7$，那么 $s$ 到环上最近点 $x$ 就是 $3$。你以为 $t$ 到 $3$ 的路径是 7-6-3 吗？不是！因为你是一个环，所以跑 dfs 的话有可能路径是 7-6-5-4-3，这个时候你算出来的 $t$ 到 $x$ 的距离就会变长，答案也就错了。

因此只能用最短路了。用 spfa 显然是复杂度爆炸，于是采用 dijkstra 来看看能不能水过。最后过啦！

**时间复杂度：**$O(Tn \log n)$。

**注意：**

样例中有一组 $s$ 和 $t$ 重合的样例，直接输出 NO。记得一开始就要判掉。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>PII;
const int N=411000;
struct edge{int x,y,pre;}a[N];
int last[N],alen;
void ins(int x,int y){
	a[++alen]=edge{x,y,last[x]};
	last[x]=alen;
}
int dfn[N],low[N],id;
int bridge[N];
int cnt,c[N];
void tarjan(int x,int in_edge){
	dfn[x]=low[x]=++id;
	for(int k=last[x];k;k=a[k].pre){
		int y=a[k].y;
		if(!dfn[y]){
			tarjan(y,k);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]){
				bridge[k]=bridge[k^1]=1;
			}
		}
		else if(k!=(in_edge^1)){
			low[x]=min(low[x],dfn[y]);
		}
	}
}
int bk;
void dfs(int x,int siz){
	c[x]=cnt;
	if(siz>1)bk=cnt;
	for(int k=last[x];k;k=a[k].pre){
		int y=a[k].y;
		if(c[y]||bridge[k])continue;
		dfs(y,siz+1);
	}
}
int v[N];
int dis_st,dis_ed,flag,d;
void dfs_st(int x,int dep){
	if(c[x]==bk){
		dis_st=dep;
		d=x;
		flag=1;
		return;
	}
	v[x]=1;
	for(int k=last[x];k;k=a[k].pre){
		int y=a[k].y;
		if(v[y])continue;
		dfs_st(y,dep+1);
		if(flag)return;
	}
}
int dis[N],vis[N];
void dijkstra(int st){
	memset(dis,0x3f,sizeof(dis));dis[st]=0;
	memset(vis,0,sizeof(vis));vis[st]=1;
	priority_queue<PII,vector<PII>,greater<PII>>Q;
	Q.push({0,st});
	while(!Q.empty()){
		int x=Q.top().second;Q.pop();
		for(int k=last[x];k;k=a[k].pre){
			int y=a[k].y;
			if(dis[y]>dis[x]+1){
				dis[y]=dis[x]+1;
				if(!vis[y]){
					vis[y]=1;
					Q.push({dis[y],y});
				}
			}
		}
		vis[x]=0;
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,st,ed;scanf("%d%d%d",&n,&ed,&st);
		alen=1;memset(last,0,sizeof(last));
		id=0;
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		dis_st=0,dis_ed=0;
		cnt=0;d=0;bk=0;
		memset(c,0,sizeof(c));
		memset(bridge,0,sizeof(bridge));
		for(int i=1;i<=n;i++){
			int x,y;scanf("%d%d",&x,&y);
			ins(x,y);ins(y,x); 
		}
		if(st==ed){puts("NO");continue;}
		for(int i=1;i<=n;i++){
			if(!dfn[i])tarjan(i,0);
		}
		for(int i=1;i<=n;i++){
			if(!c[i]){
				cnt++;
				dfs(i,1);
			}
		}
		memset(v,0,sizeof(v));
		flag=0;dfs_st(st,0);
		dijkstra(ed);
		if(dis_st>=dis[d])puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：igAC (赞：2)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1873H)

[CFlink](https://codeforces.com/problemset/problem/1873/H)

简要题意：

小 A 和小 B 在一棵基环树上，小 A 正在追捕小 B。

小 B 能够预测小 A 下一步的动作，问小 B 能否永远不被小 A 抓住。

# $\text{Solution}$

如果你打了 [RiOI-R1](https://www.luogu.com.cn/contest/96467) 你会发现这道题是 [P8943](https://www.luogu.com.cn/problem/P8943)，三叉树未卜先知了属于是。

我们发现如果小 B 能够成功走到环上，那么就能够逃离。

于是处理每个节点到环上的距离以及环上任意两点的距离。

判断小 A 是否能在小 B 到达环上前拦截，这道题就做完了。

要判断小 A 是否和小 B 在同一个点上。

基环树的基本操作相信大家都会就不再赘述。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,n,q,rt,s,t;
int head[N],tot;
struct Edge{
	int to,nxt;
}e[N<<1];
bool vis[N],find_cir;
int fa[N],deep[N];
int Fa[N],d1[N],cnt;
void add_edge(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
void gettag(int x){
	int now=x;find_cir=true;
	x=fa[x],d1[now]=++cnt;
	while(now!=x){
		d1[x]=++cnt;
		x=fa[x];
	}
}
void dfs1(int x,int f){
	if(vis[x]){
		if(!find_cir) gettag(x);
		return;
	}
	vis[x]=true;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f) continue;
		fa[y]=x;
		dfs1(y,x);
	}
}
void dfs2(int x,int f){
	deep[x]=deep[f]+1;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f || d1[y]) continue;
		Fa[y]=Fa[x];
		dfs2(y,x);
	}
}
void solve(){
	n=read(),t=read(),s=read(),tot=cnt=find_cir=0;
	for(int i=1;i<=n;++i) head[i]=vis[i]=deep[i]=d1[i]=fa[i]=Fa[i]=0;
	for(int i=1;i<=n;++i){
		int x=read(),y=read();
		add_edge(x,y);
		add_edge(y,x);
	}
	if(s==t){
		puts("NO");
		return;
	}
	dfs1(1,0);
	for(int i=1;i<=n;++i) if(d1[i]) Fa[i]=i;
	for(int i=1;i<=n;++i) if(d1[i]) deep[i]=-1,dfs2(i,i);
	int dis1=deep[s],dis2=deep[t]+min(abs(d1[Fa[s]]-d1[Fa[t]]),cnt-abs(d1[Fa[s]]-d1[Fa[t]]));
	puts(dis1<dis2?"YES":"NO");
}
int main(){
	T=read();
	while(T--) solve();
	return 0; 
}
```

---

## 作者：封禁用户 (赞：1)

# 第一步:看题+思路

考虑什么时候不会被抓上，说明是在一个环上。在一条链上的话，无论怎样都会走到尽头，绝对会被抓住，那不就简单了，我们把所有构成了环的点标记，然后再从两个起始位置分别跑一遍最短路，然后枚举构成了环的点，如果被抓的人能够比抓的人更早到达一个环内的点的话，就输出是对的，否则是错的。

# 第二步:写法

用广搜求最短路。

时间复杂度为 $O(n+m)$。

# 第三步:喜闻乐见的代码~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 4000010

int low[N], dfn[N], timestamp;
int h[N], e[N], ne[N], idx;
int stk[N], id[N], top, cnt;
int Size[N];
vector<int> ys[N];

bool st[N];
bool pd[N];

int s,t,n,m;

void add(int a, int b){
    e[idx] = b;
	ne[idx] = h[a];
	h[a] = idx++;
}

queue<int> q;

void tarjan(int u, int from){
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(!dfn[j]){
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
        }
        else if(i != (from ^ 1)){
            low[u] = min(low[u], dfn[j]);
        }
    }
    if(low[u] == dfn[u]){
        cnt++;
        int y;
        do{
            y = stk[top--];
            Size[cnt]++;
            ys[cnt].push_back(y);
            id[y] = cnt;
        }
		while(u != y);
    }
}

int cnt[N][4];

void bfs(int u){
    int ip;
    if(u == s){
        ip = 1;
    }
    else{
    	ip = 2;
	}
    for(int i = 1; i <= n; i++){
    	st[i] = 0;
	}
    q.push(u);
    st[u] = true;
    while(q.size()){
        int t = q.front();
        q.pop();
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(!st[j]){
                st[j] = true;
                cnt[j][ip] = cnt[t][ip] + 1;
                q.push(j);
            }
        }
    }
}

void init()
{
    top = 0;
    cnt = 0;
    timestamp = 0;
    idx = 0;
    memset(h, -1, sizeof(h));
    for(int i = 1; i <= n; i++){
        ys[i].clear();
        cnt[i][1] = 0, cnt[i][2] = 0;
        pd[i] = 0;
		Size[i] = 0;
        dfn[i] = 0;
		low[i] = 0;
		id[i] = 0;
    }
}

void solve()
{
    cin >> n;
    cin >> s >> t;
    init();
    for(int i = 1; i <= n; i++){
        int a, b;
        cin >> a >> b;
        add(a, b);
		add(b, a);
    }
    bfs(s);
	bfs(t);
    for(int i = 1; i <= n; i++){
        if(!dfn[i]){
            tarjan(i, 0);
        }
    }
    for(int i = 1; i <= cnt; i++){
        if(Size[i] > 2){
            for(auto t : ys[i]){
                pd[t] = 1;
            }
        }
    }
    if(s == t){
        cout << "NO" << endl;
        return;
    }
    if(pd[t]){
        cout << "YES" << endl;
        return;
    }
    for(int i = 1; i <= n; i++){
        if(pd[i]){
            if(cnt[i][1] > cnt[i][2]){
                cout << "YES" << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
    return;
    
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}

```

大家可以进行参考，谢谢!

C++，**启动**!

---

## 作者：bloodstalk (赞：1)

## Description
[WSXZCLXS](https://www.luogu.com.cn/user/780168) 给的简要题意很明确了：

小 A 和小 B 在一棵基环树上，小 A 正在追捕小 B。

小 B 能够预测小 A 下一步的动作，问小 B 能否永远不被小 A 抓住。
## Solution
首先 $n$ 个点 $n$ 条边，我们很容易就想到基环树(比正常的树多了一条边，形成了一个环)，不会也没关系，这题跟基环树其实关系不大。

首先，我们可以发现一个关键性质：如果 A 提前进入了基环树里的这个环，那么他就可以和 B 周旋，这样 B 就永远都抓不到 A；相反的，如果 B 赶在 A 之前就把 A 通往环内的那个点就封死了，那么 A 就只能静待被抓了。

想到这里其实思路就很明了了，我们需要预处理出这些东西：

- 求出这个环；

- 求出每个不在环上的点到环的距离以及最初到环上的哪个点；

- 求出环内点与点之间的距离。

这里找环我用的边双，当然也可以用拓扑来解决。

对于第二个问题，我们 $O(n)$ 枚举每一条边，如果出现了点 $x$ 在环内点 $y$ 不在环内的情况，我们从 $y$ 开始进行广搜给 $y$ 延伸出来的子树打上标记。

对于第三个问题，我们随便断掉环上的一条边，这样形成的就是一条链，我们在链上以断的那条边的其中一个端点为起点再进行一次广搜，处理出环上每个点到这个端点的距离，那么最后环上两个点 $x,y$ 的最短距离就是 $\min(\lvert len_x-len_y \rvert,size- \lvert len_x-len_y \rvert)$，其中 $size$ 表示的是这个环的大小。

由此可知，总复杂度是线性的，可以通过。

## Code
```cpp
#include<bits/stdc++.h>
//define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 4e5 + 5;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int T,a,b,n,u,v,cnt,tot,idx,ans,k,cutx,cuty,maxsiz;
int low[N],dfn[N],stk[N],belong[N],len[N];
struct Node{
	int tp,dep;//tp表示这个不在环上的点通过哪个点进入环，以及到环的距离
}f[N];
vector <int> vec[N];
struct node{
	int u,v,next;
}edge[N<<1]; int head[N],num_edge;

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

il void add(int from,int to)
{
	edge[++num_edge] = (node){from,to,head[from]};
	head[from] = num_edge;
}

il void tarjan(int x,int in_edge)//边双缩点
{
	dfn[x] = low[x] = ++tot;
	stk[++idx] = x;
	for(re int i=head[x];i;i=edge[i].next)
	{
		int y = edge[i].v;
		if(!dfn[y])
		{
			tarjan(y,i);
			low[x] = min(low[x],low[y]);
		}
		else if(i != (in_edge^1)) low[x] = min(low[x],dfn[y]);
	}
	if(dfn[x] == low[x])
	{
		++cnt;
		while(x != stk[idx+1])
		{
			vec[cnt].push_back(stk[idx]);
			belong[stk[idx]] = cnt;
			idx--;
		}
	}
}

il void bfs(int tp,int x,int dep)//求不在环上的点从哪个点入环，路径长度是多少
{
	f[x] = (Node){tp,dep};
	queue <int> q;
	q.push(x);
	while(!q.empty())
	{
		u = q.front(); q.pop();
		for(re int i=head[u];i;i=edge[i].next)
		{
			v = edge[i].v;
			if(v == tp) continue;
			if(!f[v].dep)
			{
				f[v].dep = f[u].dep + 1 , f[v].tp = tp;
				q.push(v);
			}
		}
	}
}

il void circle()//求断边后链上路径长
{
	memset(len , -1 , sizeof len);
	len[cutx] = 0;
	queue <int> q;
	q.push(cutx);
	while(!q.empty())
	{
		u = q.front(); q.pop();
		for(re int i=head[u];i;i=edge[i].next)
		{
			v = edge[i].v;
			if((u == cutx && v == cuty) || (v == cutx && u == cuty)) continue;
			if(belong[v] != k) continue;
			if(len[v] == -1)
			{
				len[v] = len[u] + 1;
				q.push(v);
			}
		}
	}
}

il void Main()
{
	for(re int i=1;i<=n;i++) dfn[i] = low[i] = stk[i] = belong[i] = len[i] = head[i] = 0 , f[i].dep = f[i].tp = 0;
	for(re int i=1;i<=cnt;i++) vec[i].clear();
	n = read() , a = read() , b = read();
	num_edge = 1 , cnt = tot = idx = cutx = cuty = ans = k = 0;
	for(re int i=1;i<=n;i++)
	{
		u = read() , v = read();
		add(u,v) , add(v,u);
	}
	tarjan(1,1);//边双缩点找环
	for(re int i=1;i<=cnt;i++) if(vec[i].size() > 1) { k = i , maxsiz = vec[i].size(); break; }//找哪个是环,步骤一
	for(re int i=2;i<=num_edge;i++)
	{
		u = edge[i].u , v = edge[i].v;
		if(belong[u] == belong[v]) { cutx = u , cuty = v ; continue; }//随便找一条在环上的边
		if(belong[u] == k && belong[v] != k) bfs(u,v,1);//一个在环上一个不在环上,进行步骤二
	}
	circle();//步骤三
	int siz = vec[k].size() , disu , disv;
	u = b , v = a;
	if(a == b) { puts("No"); return ; }
	if(belong[u] == k) { cout << "Yes" << "\n"; return ; }//原本就在环里那直接跑了
	disu = f[u].dep;//计算路径长度
	if(belong[v] == k) disv = min(abs(len[f[u].tp]-len[v]),siz-abs(len[f[u].tp]-len[v]));//B要拦截的距离就是B到环的距离B的tp和A的tp之间的距离
	else disv = f[v].dep + min(abs(len[f[u].tp]-len[f[v].tp]),siz-abs(len[f[u].tp]-len[f[v].tp]));
	if(disu < disv) cout << "Yes" << "\n";
	else cout << "No" << "\n";
}

signed main()
{
	T = read();
	while(T--) Main();
	return 0;
}
```


---

## 作者：rui_er (赞：1)

其他题解怎么又 Tarjan 又 Dijkstra 的，这是 div4H 的样子吗，来个简单好写的做法。

题面里的人名太复杂了，本题解中称为警察和小偷。

注意到，如果小偷成功到达了环上，那么一定不会被警察抓到。因为小偷知道警察下一步会走到哪里，他可以执行相同的操作（顺时针/逆时针/静止），使得他和警察之间的距离不变。

那么问题就是警察是否可以在小偷到达环上之前就蹲守在小偷的必经之路上，也就是环上离小偷最近的那个点。如果我们知道这个点，还知道任意两个点之间的距离，那么判断一下哪个更大就解决了。

下面是比较简单的实现方法。

维护一个并查集记录任意两个点是否连通，在加边的过程中，如果两端未连通，就加这条边，否则不加边并把两个端点记录为 $ext_u,ext_v$。在处理完所有边后，我们得到了原基环树的一棵生成树，以及被删掉的那条环上的边的两端点。

通过树上倍增实现生成树的 LCA，然后使用树上差分可以求得生成树上任意两点间距离，设为 $dis_T(u,v)$。考虑原基环树上两点间距离是什么，有两种情况，一种是只走生成树边，另一种是经过了被删除的边。前者即 $dis_T(u,v)$，后者根据经过方向不同又有两种情况，分别是 $dis_T(u,ext_u)+1+dis_T(ext_v,v)$ 和 $dis_T(u,ext_v)+1+dis_T(ext_u,v)$，意思是 $u\stackrel{*}{\to} ext_u\to ext_v\stackrel{*}{\to} v$ 和 $u\stackrel{*}{\to} ext_v\to ext_u\stackrel{*}{\to} v$ 两条路径。因此，原基环树上两点间距离 $dis_G(u,v)=\min\{dis_T(u,v),dis_T(u,ext_u)+1+dis_T(ext_v,v),dis_T(u,ext_v)+1+dis_T(ext_u,v)\}$。

标记环上的点的方法是求出 $ext_u$ 和 $ext_v$ 的 LCA，并暴力跳父亲标记 $ext_u$ 和 $ext_v$ 之间的所有点。求环上离小偷最近的点只需要枚举所有点 $u$，判断是否在环上，如果在环上就取出 $dis_G(u,b)$ 最小的点，记作 $pos$。然后比较 $dis_G(pos,a)$ 和 $dis_G(pos,b)$ 的大小关系即可得到答案。

时间复杂度 $O(n\log n)$。

```cpp
// LUOGU_RID: 126418248
// Problem: H. Mad City
// Contest: Codeforces - Codeforces Round 898 (Div. 4)
// URL: https://codeforces.com/contest/1873/problem/H
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 2e5+5;

int T, n, a, b, ext_u, ext_v, dis[N], fa[19][N], cyc[N];
vector<int> e[N];

struct Dsu {
    int fa[N];
    void init(int x) {rep(i, 1, x) fa[i] = i;}
    int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
    bool same(int x, int y) {return find(x) == find(y);}
    bool merge(int x, int y) {
        if(same(x, y)) return false;
        x = find(x); y = find(y);
        fa[x] = y;
        return true;
    }
}dsu;

void dfs(int u, int f) {
    dis[u] = dis[f] + 1;
    fa[0][u] = f;
    rep(i, 1, 18) fa[i][u] = fa[i-1][fa[i-1][u]];
    for(int v : e[u]) if(v != f) dfs(v, u);
}

inline int LCA(int u, int v) {
    if(dis[u] < dis[v]) swap(u, v);
    per(i, 18, 0) if(dis[fa[i][u]] >= dis[v]) u = fa[i][u];
    if(u == v) return u;
    per(i, 18, 0) if(fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
    return fa[0][u];
}

inline int disT(int u, int v) {
    return dis[u] + dis[v] - 2 * dis[LCA(u, v)];
}

inline int disReal(int u, int v) {
    return min({disT(u, v), disT(u, ext_u) + disT(ext_v, v) + 1, disT(u, ext_v) + disT(v, ext_u) + 1});
}

int main() {
    for(scanf("%d", &T); T; T--) {
        scanf("%d%d%d", &n, &a, &b);
        dsu.init(n);
        rep(i, 1, n) {
            int u, v;
            scanf("%d%d", &u, &v);
            if(dsu.same(u, v)) {
                ext_u = u;
                ext_v = v;
            }
            else {
                e[u].push_back(v);
                e[v].push_back(u);
                dsu.merge(u, v);
            }
        }
        dfs(1, 0);
        int p = LCA(ext_u, ext_v);
        for(int u = ext_u; u != p; u = fa[0][u]) cyc[u] = 1;
        for(int v = ext_v; v != p; v = fa[0][v]) cyc[v] = 1;
        cyc[p] = 1;
        int d = n, pos = 0;
        rep(i, 1, n) if(cyc[i]) if(disReal(b, i) < d) d = disReal(b, i), pos = i;
        puts(d < disReal(a, pos) ? "YES" : "NO");
        // clear
        rep(i, 1, n) {
            dis[i] = cyc[i] = 0;
            rep(j, 0, 18) fa[j][i] = 0;
            e[i].clear();
        }
        ext_u = ext_v = 0;
    }
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

$n$ 个点 $n$ 条边的联通无向图，这说明是基环树。

先找出环，然后算出树里面的深度，判断逃的人先到环上还是抓的人先到逃的人所在的树中即可。

因为假若逃的人先到环上，那么就永远不可能抓到，反之一定可以抓到。

注意不要不小心把空间写爆。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+114;
int n,a,b,fa[N];
bitset<N> vis,use;
int dep[N],father[N];
int dfn[N],dfncnt;
vector<int> v[N];
inline int find(int p){
	if(fa[p]!=p)fa[p]=find(fa[p]);
	return fa[p];
}
inline void dfs(int p,int e,vector<int> &ans){
	vis[p]=1;
	if(p==e){
		sort(ans.begin(),ans.end());
		for(auto i:ans) use[i]=true;
		return;
	}
	for(auto i:v[p]){
		if(vis[i])continue;
		ans.push_back(i);
		dfs(i,e,ans);
		ans.resize(ans.size()-1);
	}
	return;
}
void DFS(int u){
    dfn[u]=++dfncnt;
    for(int nxt:v[u]){
        if(use[nxt]==true&&dfn[nxt]==0) DFS(nxt);
    }
}
vector<int> tmp;
queue<int> q;
void work(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++) fa[i]=i,dfn[i]=father[i]=dep[i]=0,vis[i]=use[i]=false,v[i].clear();
    dfncnt=0;
    bool flag=true;
    for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
		int fx=find(x),fy=find(y);
		if(fx==fy){
			tmp.clear();
			tmp.push_back(x);
			dfs(x,y,tmp);
		}else fa[fx]=fy;
    }
    for(int i=1;i<=n;i++) if(use[i]==true) dep[i]=0,q.push(i),father[i]=i;;
    for(int i=1;i<=n;i++){
        if(use[i]==true&&dfn[i]==0) DFS(i);
    }
    while(q.size()>0){
        int u=q.front();
        q.pop();
        for(int nxt:v[u]){
            if(use[nxt]==true||dep[nxt]>0) continue;
            dep[nxt]=dep[u]+1;
            father[nxt]=father[u];
            q.push(nxt);
        }
    }
    cout<<(((dep[a]+min(abs(dfn[father[a]]-dfn[father[b]]),dfncnt-abs(dfn[father[a]]-dfn[father[b]])))>dep[b])?"YES\n":"NO\n");
}
int t;
int main(){
    cin>>t;
    while(t--) work();
}
```


---

## 作者：ZZZZZZZF (赞：0)

# 题意  有坑？

原文： 

_It is guaranteed that any pair of buildings is connected by some path and **there is at most one road between any pair of buildings.**_ 

什么叫 _“任何一对建筑物之间最多只有一条路”_ ？？

第一眼两种理解：

1. 任意两个城之间只有一条路。

2. 无重边。


看数据范围不难猜测是第二种，是一棵基环树。

~~但是对于懒得看英语题面的懒人真的很搞~~

# 思路

人名容易搞混，下文简称警察和小偷。

显然，当小偷被抓前到达环时就可以逃脱。

所以我们先 dfs 找环。

再考虑什么情况下警察能抓住小偷：

1. 如果两人到达环的点为同一点，只需判断两人到环的距离即可

2. 如果两人入环点不同，且小偷在环外（出生在环内直接逃了）。那么警察只需先到达（或者同时）小偷的入环点就可以抓住小偷。

那么我们需要计算 $3$ 个值：警察到环的距离 $dis[1]$，小偷到环的距离 $dis[2]$，两人入环点的距离 $d$，简单判断即可得出能否被抓。

# Code
```cpp
#include<bits/stdc++.h>

//奇怪的快读
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

#define N 200010
#define M 200010
#define inf 10000000
using namespace std;

struct edge{
    int v,next;
}e[M*2];//双向边

int m,n,tt,top,c,a,b,dis[3],p[3],D;
int head[N],vis[N];
int f[N],stk[N],inC[N];

void add(int u,int v) { 
    e[++tt].next = head[u]; 
    e[tt].v = v;  
    head[u] =  tt;
    return;
}


//dfs找环
void dfs(int u){
    //压栈记录路径
    stk[++top] = u;
    for(int i = head[u];i;i = e[i].next){
        if(f[u] == e[i].v) continue;

        if(f[e[i].v]){
            while(stk[top]!=e[i].v){
                inC[stk[top]] = 1;
                top--;
            }
            //标记已经找到环
            inC[e[i].v] = 1;
            c = 1;
            return;
        }
        f[e[i].v] = u;
        dfs(e[i].v);
        if(c == 1) return;
    }
    top--;
    return;
}

//计算到入环点的距离
void getDis(int u,int d,int m){
    if(inC[u]){
        p[m] = u;
        dis[m] = d;
        return;
    }
    for(int i = head[u];i;i = e[i].next){
        if(vis[e[i].v]) continue;
        vis[e[i].v] = 1;
        getDis(e[i].v,d+1,m);
        if(p[m]!=0)return;
    }
    return;
}

//因为实在懒得起名字，干脆重载得了
void getDis(int u,int d){
  
    if(u == b){
 
        //这个只因环树是真的坑，我去cf搞了好久才发现D可能会算长了
        if(D>d)
            D = d;
        return;
    }
    for(int i = head[u];i;i = e[i].next){
        if(vis[e[i].v]) continue;
        vis[e[i].v] = 1;
        getDis(e[i].v,d+1);
        vis[e[i].v] = 0;
    }
    return;
}

//检查图
void test(){
    for(int u = 1;u<=n;u++){
        for(int i = head[u];i;i = e[i].next){
            printf("%d--->%d \n",u,e[i].v);
        }
        printf("\n");
    }
}

int main(){
    int T = 0;
    scanf("%d",&T);
    while(T--){
        n = read(),a = read(),b = read();
        
        //记得要初始化stk，wa了一次
        for(int i = 1;i<=n;i++){
            f[i] = inC[i] = head[i] = stk[i] = 0;
        }
        dis[1] = dis[2] = p[1] = p[2] = tt = c = 0;
        D = inf;
        top = 0;
        for(int i = 1,u,v;i<=n;i++){
            u = read();v = read();
            add(u,v);
            add(v,u);
        }

        f[1] = -1;
        dfs(1);
        
	//丑陋的初始化
        for(int i = 1;i<=n;i++) vis[i] = 0;
        vis[a] = 1;
        getDis(a,0,1);

        for(int i = 1;i<=n;i++) vis[i] = 0;
        vis[b] = 1;
        getDis(b,0,2);

        for(int i = 1;i<=n;i++) vis[i] = 0;
        vis[a] = 1;
        getDis(a,0);

	//判断两入环点
        if(p[1] == p[2]){
            if(dis[1]<=dis[2]){
                printf("NO\n");
                continue;
            }
            else{
                printf("YES\n");
                continue;
            }
        }
        else{
        
            //计算入环点距离d
            int d = D-dis[1]-dis[2];
            if(dis[1]+d>dis[2]){
                printf("YES\n");
                continue;
            }
            else{
                printf("NO\n");
                continue;
            }
        }
    }
    return 0;
}
```

---

## 作者：FwbAway (赞：0)

## 题意

有两个人，小 A 和小 B，他们在一棵**基环树**上，小 A 正在抓小 B。

每一次行动，小 B 都能得知小 A 下一步的动作，那请问小 B 能否一直不被小 A 抓住（即一直在运动）。

### 这里科普一下**基环树**：

基环树，就是 $n$ 个点 $n$ 条边的树，因为这个图相当于在树上加了一条边，故一定会形成一个环。

所以基环树上的问题大多数都是先处理以环上的点为根节点的子树的值，然后在环上做 dp 类的算法操作。

找到环是基环树上的问题的重要一步，可以记录下来每个点的时间戳，若一个点的子节点被访问过了，那么这两个点一定是环上的节点，以这两个点为首尾讲一个环找到。

如果你不懂**时间戳**的话，换种说法。基环树的关键就是找到环，可以先把环当作这个无根树的 “根” ，也就是把环当成一个点（先不管它），这样一颗基环树就变成了一个普通的树，然后我们先按照解决普通树的方法对“根”的所有子树依次处理求解答案，最后在单独对环上所有的点进行操作求解最终答案即可。

如果用基环树进行简单拓扑的话：

无向图：

```c++
void topsort(){
   
    int l=0,r=0;
    for (int i=1;i<=n;i++) 
      if(in[i]==1) q[++r]=i;
    while(l<r) {
   
        int now=q[++l];
        for (int i=ls[now];i;i=a[i].next){
   
            int y=a[i].to;
            if(in[y]>1){
   
                in[y]--;
                if(in[y]==1) q[++r]=y;
            }
        }
    }
}
```

有向图的深搜解决方法：

```c++
void check_c(int x)
{
   
    v[x]=true;
    if(v[d[x]]) mark=x;//环上的一点
    else check_c(father[x]);
    return;
}

```

当然，以上两份代码对这道题没有太大的帮助，以下是思路和解析的关键。

## 思路

首先要会三个算法：倍增、LCA、并查集。

这道题概括一下题意，其实就是上面讲的基环树的应用，**本质就是在基环树上找环**，可以使用以 dfs 和 dij 为基本思想的拓扑排序。

首先我们要想了，什么情况下小 A 不会抓住小 B 呢？很明显的，当小 B 跑到了**一个环上**，小 A 就只能堵住如环的那**一个点**，如果如环的点有两个，那很明显，小 A 无法抓住小 B。

所以我们就要分别求出小 A 和小 B 分别到达环的最短路径，判断即可。

和其他题解不同的是，我们可以使用 SPFA 或者 dij 或者拓扑排序，这里比较推荐 dij 或者拓扑排序，因为它可以更快的帮助你的手法和考试的时候的灵机应变的能力。

## 代码提示

存图：

```c++
for(int i = 1; i <= n; i++){
	int u, v;
	scanf("%d%d", &u, &v);
	vt[u].push_back(v);
	vt[v].push_back(u);
	rudu[u] += 1;
	rudu[v] += 1;
}
```

可以特判（如果代码能力强可以不特判）：

```c++
if (in_a == in_b) {//a和b如果在一个位置，就会被抓
	printf("NO\n");//无法逃跑
	break;//别忘了，小心两个答案
}
```

可以使用 `while` 语句进行广搜（bfs/dij），提供 bfs 的代码：

```c++
//queue定义的q
while(!q.empty()){
	int f = q.front();//注意queue是front，不是top
	q.pop();//特别容易忘记的一句话
	for (auto nxt : vt[u]){//可能有的编译器不支持，那就老老实实的写 i=0;i<vt[u].size();i++ 吧！
		if (dis[nxt]) continue;
		q.push(nxt);
		dis[nxt] = ++dis[f];
		dis[f]--;//这两句话等价于dis[nxt]=dis[f]+1;
	}
}
```

明显的，广搜下，最后判断 $dis[in\_a]$ 和 $dis[in\_b]$ 的值。

@[LIUYC_C](https://www.luogu.com.cn/user/819273) 提供的 tarjan 的算法也很不错，但是没有 dij 和 bfs 好理解，这里没有放 dij/SPFA 的代码，为了让读者更好的发挥自己真正的实力，更好的锻炼自己。

终。

---

## 作者：ArcherHavetoLearnWhk (赞：0)

（前言：前几天刚做了一道图搜的题，一个月前还做出来一道拓扑 DP 题，做起来还是比较熟练的，切出来感觉真爽。）

### 题意

参考了神犇 [WSXZCLXS](https://www.luogu.com.cn/user/780168) 的题意。

A 和 B 在一个 $n$ 个点 $n$ 条边的图的结点上，A 在追捕 B，B 能够预测 A 下一步的动作，给出图和他们的初始位置，问 B 能否永远不被 A 抓住。

### 分析

首先，开始时 A 和 B 有可能在同一个结点，这种情况开局就被抓，直接特判输出 `NO`。

然后开始分析。图有 $n$ 个点 $n$ 条边，可知这是一棵基环树，只有一个环。

所以，B 要跑上这个环跟 A 绕圈子，这样他就能永远不被抓，能活。**基环树可以看成将一个森林的所有树的根结点连成环**。如果 B 不上环，就只能向这些树的叶子结点跑去，最终在叶子结点上被堵死。这里有个基环树参考图可以看着想一想。

![](https://cdn.luogu.com.cn/upload/image_hosting/z433w12b.png)

如果 B 开始时就在环上，他就能活，A 来了直接开始绕圈子。

如果 B 开始时不在环上呢？参考前面的图，B 只能从他所在的组成森林的树的根结点跑上环。如上图，假如 B 在图中 $2,3$ 这两个点上就要从结点 $1$ 上环。这个点称为 $root$。

B 要赶在 A 到达 $root$ 堵住他之前跑到 $root$ 从而上环。如果不能，则 A 提前到达，B 无法跑上环，就寄了。所以判断 A 和 B 分别到 $root$ 的距离的大小即可。

### 做法

要找到 $root$ 就先得找到这个环，我选择使用比较熟练的拓扑排序。普通拓扑的过程就不放了。

过程与普通 DAG 拓扑的不同或补充如下：

- 拓扑前标记 $root$ 为 B 的初始位置。

- 将度数为 $1$ 的“叶子结点”入队，从它们开始拓扑。

- 每次，对于某一个被删除的点 $u$ 的未被删除的邻点 $v$ ，若在 $u$ 和它的边被删之后 $v$ 度数为 $1$ 就将 $v$ 入队，因为 $v$ 此时成为了新的“叶子结点”。

- 每次若删除的点为标记的 $root$ 就将 $root$ 标记为为当前被删除的结点 $u$ 的未被删除的邻点。你可以理解成，B 所在的树在拓扑开始时“叶子结点”上站着人，他们总向着“根结点”走，并将 $root$ 推向根结点。若走到某个岔路口，可以走向远离“根结点”的方向，那他就退出。

- 若度数为 $1$ 的点已经删完，那么拓扑结束。大家都知道，拓扑排序会剩下一些环，此时 $root$ 已经被推到环上正确的位置了，而环上的点不会被删掉，所以我们成功求出了 $root$。

找到 $root$ 之后就好办了。可以直接开始广搜并记录各店到 $root$ 的距离，用 $\{dis_n\}$ 记录。若 $dis_A>dis_B$，B 就能永远不被抓，反之亦然。

当然广搜时先搜到 A 则 B 死，先搜到 B 且 A 不在当前层 B 活，或者深搜也都可以。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,in[200005],dis[200005];
vector<int>e[200005];
queue<int>Q;
int main(){
	cin>>t;
	while(t--){
		int n,a,b;
		cin>>n>>a>>b;
		memset(in,0,sizeof(in));
		memset(dis,0,sizeof(dis));
		for(int i=1;i<=n;i++)e[i]=vector<int>(); //清空数组和邻接表
		for(int i=1;i<=n;i++){
			int u,v;
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
			in[u]++,in[v]++;
		} //读图，记录点度数
		if(a==b){
			cout<<"NO\n";
			continue;
		} //两人开始在一个点上一定会被抓
		Q=queue<int>();
		for(int i=1;i<=n;i++)
			if(in[i]==1)Q.push(i); //准备拓扑 从度数为1的点开始拓扑
		int root=b; //root开始设为b的位置 因为要求b到环的最短距离
		while(!Q.empty()){
			int u=Q.front();
			Q.pop();
			in[u]=-1;
			for(auto v:e[u]){
				in[v]--;
				if(in[v]<=0)continue;
				if(in[v]==1)Q.push(v); //下次继续从度数为1的点开始
				if(u==root)root=v; //更新root
			}
		}
		if(in[b]>=2){
			cout<<"YES\n";
			continue;
		} //删完点后b度数大于2意味着它在环上 一定能逃
		Q=queue<int>();
		Q.push(root); //从root开始广搜找最短路
		dis[root]=1; //dis数组可以当作visit数组使用 设为1因为root已经访问过
		while(!Q.empty()){ //bfs找root到每个点最短距离
			int u=Q.front();
			Q.pop();
			for(auto v:e[u]){
				if(!dis[v]){
					Q.push(v);
					dis[v]=dis[u]+1;
				}
			}
		}
		if(dis[a]>dis[b])cout<<"YES\n"; //a与root距离比b的更远 没法阻止b上环逃跑
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：LIUYC_C (赞：0)


## 大体思路：

拿到题读完基本就会了。

读题，发现是在图上，看着像是博弈论，实际上想一想就是一个性质题，考虑什么时候不会被抓上，不用想也是在一个环上，在一条链上的话，无论怎样都会走到尽头，绝对会被抓住，那不就简单了，我们把所有构成了环的点标记，然后再从两个起始位置分别跑一遍最短路，然后枚举构成了环的点，如果被抓的人能够比抓的人更早到达一个环内的点的话，就输出 YES，否则实在不行就输出 NO，然后注意特判一些点就好了，比如说两个人在一起，或者被抓的人一开始就在环内，感觉没什么难的。

求最短路的话用 bfs 就好了，毕竟权值为 1，然后找环我用的是 tarjan，好像用拓扑排序也可以。

**时间复杂度：$O(n+m)$**，tarjan 的时间复杂度。

## 代码实现：
```
#include <bits/stdc++.h>
using namespace std;
const int N=4e5+10;

int low[N],dfn[N],timestamp;
int h[N],e[N],ne[N],idx;
int stk[N],id[N],top,scc_cnt;
int Size[N];
vector<int>ys[N];

bool st[N];
bool pd[N];

int s,t,n,m;



void add(int a,int b){
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
queue<int>q;
void tarjan(int u,int from){
    dfn[u]=low[u]=++timestamp;
    stk[++top]=u;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j=e[i];
        if(!dfn[j]){
            tarjan(j,i);
            low[u]=min(low[u],low[j]);
        }
        else if(i!=(from^1)){
            low[u]=min(low[u],dfn[j]);
        }
    }
    if(low[u]==dfn[u]){
        scc_cnt++;
        int y;
        do{
            y=stk[top--];
            Size[scc_cnt]++;
            ys[scc_cnt].push_back(y);
            id[y]=scc_cnt;
        }while(u!=y);
    }
}

int cnt[N][4];

void bfs(int u){
    int ip;
    if(u==s){
        ip=1;
    }
    else ip=2;
    for(int i=1;i<=n;i++)st[i]=0;
    q.push(u);
    st[u]=true;
    while(q.size()){
        int t=q.front();
        q.pop();
        for(int i=h[t];i!=-1;i=ne[i]){
            int j=e[i];
            if(!st[j]){
                st[j]=true;
                cnt[j][ip]=cnt[t][ip]+1;
                q.push(j);
            }
        }
    }
}

void init(){
     top=0;
     scc_cnt=0;
     timestamp=0;
     idx=0;
     memset(h,-1,sizeof h);
     for(int i=1;i<=n;i++){
        ys[i].clear();
        cnt[i][1]=0,cnt[i][2]=0;
        pd[i]=0,Size[i]=0;
        dfn[i]=0,low[i]=0,id[i]=0;;
    }
}

void solve(){
    cin>>n;
    cin>>s>>t;
    init();//初始化不说
    
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    bfs(s),bfs(t);//最短路
    
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
        }
    }//tarjan找边双
    
    for(int i=1;i<=scc_cnt;i++){
        if(Size[i]>2){//大于2的才是环
            for(auto t:ys[i]){
                pd[t]=1;
            }
        }
    }
    //特判
    if(s==t){
        cout<<"NO"<<endl;
        return;
    }
    if(pd[t]){
        cout<<"YES"<<endl;
        return;
    }
    
    for(int i=1;i<=n;i++){
        if(pd[i]){
            if(cnt[i][1]>cnt[i][2]){
                cout<<"YES"<<endl;
                return;
            }
        }
    }
    cout<<"NO"<<endl;
    return;
    
}

signed main(){
    int T;
    /*freopen("bigdate.in","r",stdin);
    freopen("second.out","w",stdout);*/
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}


```


---

