# Edge Deletion

## 题目描述

给一个$n$个点,$m$条边的无向简单带权连通图, 要求删边至最多剩余$k$条边.

定义"好点"是指删边后, 1号节点到它的最短路长度仍然等于原图最短路长度的节点.

最大化删边后的好点个数.

## 说明/提示

$n, m \le 3 \times 10^5$.

## 样例 #1

### 输入

```
3 3 2
1 2 1
3 2 1
1 3 3
```

### 输出

```
2
1 2 ```

## 样例 #2

### 输入

```
4 5 2
4 1 8
2 4 1
2 1 3
3 4 9
3 1 5
```

### 输出

```
2
3 2 ```

# 题解

## 作者：xixiup (赞：15)

#### 思路分享

阅读题意可知，一个“好点”的性质完美的符合了最短路径树中对于一个结点的定义，又因为树是边数最少的连通图，所以我们就可以把保留的边建成一棵树。

关于最短路径树，可以参考我的题解[题解 CF1005F 【Berland and the Shortest Paths】](https://www.luogu.com.cn/blog/Manvski/solution-cf1005f)，里面有较完备的阐述。

得到最小路径树后，我们就可以考虑如何选边，其实也就是如何选点。

众所周知，一个有$m$个节点的树有$m-1$条边，所以我们就可以在最短路径树中选出$min(k+1,n)$个节点。

又因为要保证图的连通，所以可以直接从$1$节点开始$DFS$选点。

#### 代码展示

下面展示部分代码，其中求最短路径树部分前文中题解已提到，不在这里展示。其余部分详解在注释中。

（弱弱的说一句，这道题要开$longlong$）

```cpp
void out(){//如果k>=n-1就直接输出最短路径树
	cout<<n-1<<"\n";
	for(int i=2;i<=n;i++){
		printf("%lld ",nu[ed[i]]);
	}
}
void work(){
	for(int i=2;i<=n;i++){
		pd[ed[i]]=1;//ed[i]表示每一个节点的对应的边
					//pd[i]为1表示第i条边在我们所选的最短路径树上
	}
}
void DaFaShi(int x){//DFS选点
	for(int i=bg[x];i;i=ne[i]){
		int y=to[i];
		if(s<e&&pd[i]==1){
			s++;
			pd[i]=2;//pd[i]为2表示选择该边保留。
			DaFaShi(y);
		}
	}
}
```


---

## 作者：YGB_XU (赞：7)

我们发现这道题要求删边时到达一些点的最短距离不变，于是想到反向操作：直接正向得到并保留 到达这些点 所需的**最短路上的边**，而剩下的边都可以删去，因为删去后仍可以通过保留的边经过最短距离到达这些点。

本篇题解的代码的不同之处在于：只需要从头做一遍 djikstra，在过程中输出答案即可，而不需要先建立[最短路树](https://baike.baidu.com/item/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84%E6%A0%91/22787159?fr=aladdin)，再做一遍搜索答案。具体来讲，在算法更新最近的节点时，我们额外记录一个信息：更新这次最短路的前驱边，这样在得到一个新的点时，可以便捷地输出其最短路所需的新边。

另外，对于一个节点数为 $n$ 的连通图，想使其全部最短路保留，最多只需要保留一棵树，即保留 $n-1$ 条边，所以 $k$ 应与其取较小值。

详见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
	int ret=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while('0'<=c&&c<='9'){
		ret=(ret<<1)+(ret<<3)+(int)(c-'0');
		c=getchar();
	}
	return ret*f;
}

inline void write(int x){
	if(x>=10) write(x/10);
	putchar('0'+x%10);
}

const int NR=3e5+5;
long long dis[NR];
struct Edge{
	int to,w,id;//id为这条边的编号
};
vector<Edge>g[NR];
struct Node{
	int to,id;//id为“前驱边”的编号
	long long w;
	bool operator < (const Node &B)const{
		return w>B.w;
	}
};

int k;
bool vis[NR];
inline void dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	priority_queue<Node>q;
	dis[1]=0;
	q.push(Node{1,0,0ll});
	while(!q.empty()){
		int x=q.top().to,ret=q.top().id;
		q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		if(ret>0&&k>0){
			k--;
			write(ret);
			putchar(' ');
		}
		if(k==0) return;//可保留的边数已经用完
		for(unsigned int i=0;i<g[x].size();i++){
			int y=g[x][i].to,w=g[x][i].w,id=g[x][i].id;
			if(dis[y]>dis[x]+1ll*w){
				dis[y]=dis[x]+1ll*w;
				q.push(Node{y,id,dis[y]});
			}
		}
	}
}

int main(){
	int n,m;
	n=read();m=read();k=read();
	k=min(k,n-1);
	write(k);
	putchar('\n');
	for(int i=1,u,v,w;i<=m;i++){
		u=read();v=read();w=read();
		g[u].push_back(Edge{v,w,i});
		g[v].push_back(Edge{u,w,i});
	}
	dijkstra();
	return 0;
}
```


---

## 作者：GIFBMP (赞：3)

**Change Log:代码部分增加了 dijkstra 的一个小优化（不然会 TLE #64）以及特判 $k=0$ 的情况**

### 正题（Upd on 2020/9/20）

~~过了一个月发现被 hack 了，回来补题解~~

首先我们构造以 $1$ 为根的最短路树，对于非树边，由于不影响答案，可以随便删。

对于树边，我们每次找到一个叶子节点 $x$ 并删除 $E(fa_x,x)$，这样每次只会使得点 $x$ 成为不是“好的”节点。可以证明，这样一定最优。用 dfs 实现即可。

记得特判 $k=0$ 的情况。

时间复杂度：$\Theta(m\log n+n\log n)$ 

（输出标号作者用了 map 实现）

Code:

```cpp
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <cstdlib>
using namespace std ;
typedef long long ll ;
typedef pair <ll , int> P ;
const int MAXN = 3e5 + 10 ;
int n , m , k , fr[MAXN] , to[MAXN] , c[MAXN] ;
ll dis[MAXN] ;
bool vis[MAXN] ;
map <pair <int , int> , int> a ;
struct edge {
	int v , w ;
	edge (int vv = 0 , int ww = 0) {v = vv ; w = ww ;}
} ;
int min (int a , int b) {
	return a < b ? a : b ;
}
vector <edge> G[MAXN] ;
void dijkstra () {
	priority_queue <P , vector <P> , greater <P> > q ;
	memset (dis , 0x3f , sizeof (dis)) ;
	dis[1] = 0 ; q.push (make_pair (0 , 1)) ;
	while (!q.empty ()) {
		P p = q.top () ; 
		int x = q.top ().second ;
		q.pop () ;
		if (p.first > dis[x]) continue ;
		for (int i = 0 ; i < G[x].size () ; i++) {
			int v = G[x][i].v , w = G[x][i].w ;
			if (dis[x] + w < dis[v]) {
				dis[v] = dis[x] + w ;
				q.push (make_pair (dis[v] , v)) ;
			}
		}
	}
}
void dfs (int x) {
	if (!k) exit (0) ;
	vis[x] = 1 ;
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i].v , w = G[x][i].w ;
		if (dis[x] + w != dis[v] || vis[v]) continue ; 
		printf ("%d " , a[make_pair (x , v)]) ;
		k-- ;
		if (!k) exit (0) ;
		dfs (v) ;
	}	
}
int main () {
	scanf ("%d %d %d" , &n , &m , &k) ;
	for (int i = 1 ; i <= m ; i++) {
		scanf ("%d %d %d" , &fr[i] , &to[i] , &c[i]) ;
		G[fr[i]].push_back (edge (to[i] , c[i])) ;
		G[to[i]].push_back (edge (fr[i] , c[i])) ; 
		a[make_pair (fr[i] , to[i])] = a[make_pair (to[i] , fr[i])] = i ;
	}
	dijkstra () ; 
	printf ("%d\n" , min (n - 1 , k)) ;
	dfs (1) ;
	return 0 ;
}
```

---

## 作者：RuntimeErr (赞：2)

# SPT 练习题

首先我们看一下题意，要求我们删掉一些边，某些点仍满足 **1 号节点到它的最短路长度**仍然等于**原图最短路长度**的节点，这让我们联想到了 SPT 的性质：SPT 上根结点到一个点的距离等于原图中源点到该点的最短距离。

如果不清楚 SPT 的话可以看一下我的[这篇博客](https://www.luogu.com.cn/blog/RuntimeErrror/solution-cf545e)。

由于 SPT 只需要 $n-1$ 条边，我们删边只需要留下 $\min(k,n-1)$ 条边就行。Dijkstra 做完后 dfs 判断是否为 SPT 上的边并输出就行。记得考虑 $k=0$ 的情况。

## $Code:$

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
using namespace std;

const int N=3e5+10,M=N<<1;
typedef long long ll;

int n,m,k,cnt;
int h[N],e[M],ne[M],idx;
ll w[M],dis[N];
int pre[N];bool vis[N];
struct node{
	int to;ll w;
	inline bool operator <(const node& a)const{
		return w>a.w;
	}
};
priority_queue<node>q;

inline void add(int a,int b,ll c){
	e[++idx]=b;ne[idx]=h[a];w[idx]=c;h[a]=idx;
}

void dij(int s){
	memset(dis,0x7f,sizeof dis);
	dis[s]=0;q.push((node){s,0});
	while(!q.empty()){
		int u=q.top().to;q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=h[u];i;i=ne[i]){
			int v=e[i];
			if(dis[v]>=dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				q.push((node){v,dis[v]});
				pre[v]=i;
			}
		}
	}
}
void dfs(int u){
	for(int i=h[u];i;i=ne[i]){
		int v=e[i];
		if(i==pre[v]){
			++cnt;
			if(cnt>k||cnt==n)exit(0);
			printf("%d ",i+1>>1);
			dfs(v);
		}
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;++i){
		int a,b;ll c;scanf("%d%d%lld",&a,&b,&c);
		add(a,b,c);add(b,a,c);
	}
	dij(1);
	printf("%d\n",k>n-1?n-1:k);
	dfs(1);
	return 0;
}
```


---

## 作者：LawrenceSivan (赞：2)

# CF1076D Edge Deletion（最短路径树）

# 前言

最近在刷最短路径树。

先给大家推荐几道题：

[CF545E Paths and Trees](https://www.luogu.com.cn/problem/CF545E)

[CF1005F Berland and the Shortest Paths](https://www.luogu.com.cn/problem/CF1005F)

都是最短路径树的题目。

~~（其实个人觉得可以当做三倍经验来做）~~

## 前置知识：最短路径树（SPT）

关于最短路树的讲解，可以看看我的[这一篇题解](https://www.luogu.com.cn/blog/LawrenceSivan/cf545e-paths-and-trees-zui-duan-lu-jing-shu-post)，这里就不再赘述了。

这里仅帮助大家复习一下最短路树的定义：

SPT，就是从一张连通图中，有树满足从根节点到任意点的路径都为原图中根到任意点的最短路径的树。

## 题意及思路：

>给一个 $n$ 个点,$m$ 条边的无向简单带权连通图, 要求删边至最多剩余 $k$ 条边.

>定义"好点"是指删边后, $1$ 号节点到它的最短路长度仍然等于原图最短路长度的节点.

>最大化删边后的好点个数。

题目要求我们删除节点以后最短路长度不变。

根据最短路树的定义，可以发现，不在最短路径树上的边被删除对最短路是不会有影响的。

于是可以想到，我们需要保留的就是最短路径树上的边。

如果最短路上的边数小于等于 $k$，那么我们直接把最短路树上的边全部保留，否则我们在最短路径树上选择 $k$ 条边留下即可。

由于需要保证删掉以后图是联通的，所以我们从节点 $1$ 开始遍历，找到 $k$ 条边留下即可。

```cpp
#define P pair <long long,int>
#define mp(x,y) make_pair(x,y)

inline void Dijkstra(int s){//求出最短路树
	priority_queue <P,vector<P>,greater<P> > q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(mp(dis[s],s));
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x])continue;
		vis[x]=true;
		for(re int i=head[x];i;i=nxt[i]){
			int v=to[i],pos=id[i];
			if(dis[v]>dis[x]+w[i]){
				dis[v]=dis[x]+w[i];
				pre[v]=pos;
				q.push(mp(dis[v],v));
			}
		}
	}
} 

int ans[maxn],h,tot;

void dfs(int u){//遍历找k个边
	if(tot>=k)return;
	vis[u]=true;
	for(re int i=head[u];i;i=nxt[i]){
		int v=to[i],pos=id[i];
		if(vis[v])continue;
		if(dis[v]==dis[u]+w[i]){
			ans[++h]=pos;
			tot++;
			dfs(v);
			if(tot>=k)return;//回溯的时候也要判断，要不然会wa的
		}
	}
}
```

## 细节相关：

- 开 longlong

- 输出的时候变量编号问题一定要注意，具体看[这里](https://www.luogu.com.cn/blog/LawrenceSivan/cf545e-paths-and-trees-zui-duan-lu-jing-shu-post)

## 后记

这题其实只是很基础的最短路径树的题目，并没有一些更深入的东西。

如果真的想要好好练习最短路径树，请一定要做上面列出的那两道题目。


---

## 作者：Hexarhy (赞：2)

### Preface

最短路径树 SPT 练习题，难度相当于模板。

### Solution

读题发现有删边后最短路不变的性质，暗示我们求 SPT，于是我们把这个 SPT 建出来。

SPT 上每个点到节点 $1$ 都是最短路径，经过的边都是对最短路有贡献的，剩下的边都可以删。因此 SPT 上的边便是最优方案。

同时，从节点 $1$ 出发，对这个 SPT 遍历 $\min\{k,n-1\}$ 条边，记录边的编号输出即可。这样也能保证图的连通。

### Code

```cpp
// Problem: CF1076D Edge Deletion
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1076D
// Memory Limit: 250 MB
// Time Limit: 2500 ms
// Author: Hexarhy
//
// Powered by CP Editor (https://cpeditor.org)

typedef long long ll;//开 ll 
typedef const int cint;
cint MAXN=3e5+5;
int n,m,k,sum;
struct node
{
	int to;ll val;int id;
	bool operator<(const node& a)const
	{
		return val>a.val;
	}
};
vector<node> edge[MAXN];
vector<int> ans;
struct Edge
{
	int u,v;ll w;
}e[MAXN];
ll dis[MAXN];
int pre[MAXN];
bool visit[MAXN];

void dijkstra(void)
{
	priority_queue<node> q;
	for(int i=1;i<=n;i++)	dis[i]=LLONG_MAX;
	dis[1]=0;
	q.emplace(node{1,0,0});
	while(!q.empty())
	{
		cint u=q.top().to;q.pop();
		if(visit[u])	continue;
		visit[u]=true;
		for(const auto& it:edge[u])
		{
			cint v=it.to,w=it.val,id=it.id;
			if(dis[v]>=dis[u]+w)
			{
				if(dis[v]>dis[u]+w || e[pre[v]].w>w)	pre[v]=id;//习惯了求最小最短路径树 MSPT
				if(dis[v]>dis[u]+w)
				{
					dis[v]=dis[u]+w;
					q.emplace(node{v,dis[v],0});	
				}
			}
		}
	}
}

void dfs(cint cur,cint fa)
{
	if(sum>=k)	return;
	visit[cur]=true;
	for(const auto& it:edge[cur])
	{
		cint v=it.to,id=it.id;
		if(visit[v])	continue;
		if(pre[v]==id)
		{
			ans.emplace_back(id);
			++sum;
			dfs(v,cur);
			if(sum>=k)	return;//注意回溯时要判断是否已经达到 k
		}
	}
}

int main()
{
	read(n,m,k);
	for(int i=1;i<=m;i++)
	{
		int u,v;ll w;read(u,v,w);
		e[i]=Edge{u,v,w};
		edge[u].emplace_back(node{v,w,i});
		edge[v].emplace_back(node{u,w,i});
	}
	dijkstra();
	memset(visit,false,sizeof(visit));
	dfs(1,0);
	cout<<min(n-1,k)<<endl;
	for(const auto& Ans:ans)	cout<<Ans<<' ';
	return 0;
}
```

---

## 作者：Link_Space (赞：1)

题意已经说得很清楚了，我就不再赘述，根据题意我们可以想到最短路径树，因为最短路径树性质即为树上任意两点间的路径长度为原图的最短路，要使好点个数最大就要尽量多地保存最短路径树上的边，而最短路径树共有 $n-1$ 条边，所以除了这 $n-1$ 条边以外的边都可以直接删去，如果还不够的话，就从最短路径树里面删边即可。

至于最短路径树的求法可以看代码内注释

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int head[N], ver[N], nxt[N], link[N], cnt;
void add(int x,int y,int z)
{
	nxt[++cnt] = head[x];
	head[x] = cnt;
	ver[cnt] = y;
	link[cnt] = z;
}
int tot;
int pre[N];
typedef pair<int, int> PII;
priority_queue<PII,vector<PII>,greater<PII> > q;
bool aim[N];
int dis[N];
void djslm()
{
	memset(dis, 0x7f, sizeof dis);
	dis[1] = 0;
	q.push({0, 1});
	while(!q.empty())
	{
		PII temp = q.top();
		q.pop();
		int lea = temp.first;
		int now = temp.second;
		if(aim[now])
			continue;
		aim[now] = 1;
		for (int i = head[now]; i;i=nxt[i])
		{
			int v0 = ver[i];
			if(dis[v0]>=lea+link[i])
			{
				dis[v0] = lea + link[i];
				q.push({dis[v0], v0});
				pre[v0] = i;//在Dijkstra的时候记录当前点的最短路是从哪个点转移过来的，据此便可找出最短路径树上的边
			}
		}
	}
}
int n, m, k;
void dfs(int now)
{
	for (int i = head[now]; i;i=nxt[i])
	{
		int v0 = ver[i];
		if(pre[v0]==i)//当前边为最短路径树上的边
		{
			tot++;
			if(tot>k||tot==n)//保留够了或是不能再保留了就退出
			{
				puts("");
				exit(0);
			}
			printf("%lld ", i + 1 >> 1);//由于是建双向边，所以需要序号除以二
			dfs(v0);
		}
	}
}
signed main()
{
	scanf("%lld%lld%lld", &n, &m, &k);
	for (int i = 1; i <= m;i++)
	{
		int a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	djslm();
	printf("%lld\n", min(n - 1, k));
	dfs(1);
	puts("");
}
```


---

## 作者：Itst (赞：1)

### ~~题目并不难~~
### 既然我们需要保证尽量多的点的最短路与原图的最短路一致，那么我们一定是希望选中的$k$条边每条边都能产生贡献，使得一个新的点成为好点。
### 我们可以构建原图中的一棵最短路树，选择最短路树上的边，并且保证选择的边连接的点能够构成一个包含$1$号点的一个连通块，答案就是最优的，因为原图中的每一条边在新图上最多只能贡献$1$的答案，而这种方案下选择的所有边都贡献了$1$的答案。
```cpp
#include<bits/stdc++.h>
//This code is written by Itst
using namespace std;

inline int read(){
    int a = 0;
    bool f = 0;
    char c = getchar();
    while(c != EOF && !isdigit(c)){
        if(c == '-')
            f = 1;
        c = getchar();
    }
    while(c != EOF && isdigit(c)){
        a = (a << 3) + (a << 1) + (c ^ '0');
        c = getchar();
    }
    return f ? -a : a;
}

const int MAXN = 300010;
struct Edge{
    int end , upEd , w;
}Ed[MAXN << 1];
int head[MAXN] , N , M , k , cntEd = 1;
bool vis[MAXN];
long long minDis[MAXN];
priority_queue < pair < long long , int > > q;

inline void addEd(int a , int b , int c){
    Ed[++cntEd].end = b;
    Ed[cntEd].upEd = head[a];
    Ed[cntEd].w = c;
    head[a] = cntEd;
}

void Dijk(){
    memset(minDis , 0x7f , sizeof(minDis));
    minDis[1] = 0;
    q.push(make_pair(0 , 1));
    while(!q.empty()){
        pair < long long , int > t = q.top();
        q.pop();
        if(-t.first > minDis[t.second])
            continue;
        for(int i = head[t.second] ; i ; i = Ed[i].upEd)
            if(minDis[Ed[i].end] > minDis[t.second] + Ed[i].w){
                minDis[Ed[i].end] = minDis[t.second] + Ed[i].w;
                q.push(make_pair(-minDis[Ed[i].end] , Ed[i].end));
            }
    }
}

void dfs(int now){
    vis[now] = 1;
    for(int i = head[now] ; i ; i = Ed[i].upEd)
        if(!vis[Ed[i].end] && minDis[Ed[i].end] == minDis[now] + Ed[i].w){
            printf("%d " , (i >> 1));
            if(!--k)
                exit(0);
            dfs(Ed[i].end);
        }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1076D.in" , "r" , stdin);
    //freopen("1076D.out" , "w" , stdout);
#endif
    N = read();
    M = read();
    k = read();
    printf("%d\n" , min(N - 1 , k));
    if(!k)
        return 0;
    for(int i = 1 ; i <= M ; i++){
        int a = read() , b = read() , c = read();
        addEd(a , b , c);
        addEd(b , a , c);
    }
    Dijk();
    dfs(1);
    return 0;
}

```

---

## 作者：CPPfive (赞：0)

这题目蛮搞心态的。。虽然是一道蓝题但做法非常简单，主要是可以帮助我们认识到一些最短路算法的性质。

## 题目分析
我们先来看一个 dijkstra 算法的性质。如果我们在更新每一个点的最短路的同时维护每一个点的前驱——即从起点到这个点的最短路上，这个点的前一个点，并且将每个点和它的前驱连边，那么连出来的新图会是一个树。

除了起点外，每一个点只有一个前驱；起点没有前驱，所以新图确实是一个树。最短路中还有一些类似的性质，例如从一个点出发到另一个点的所有最短路径的并集是一个 DAG，感兴趣的可以去做[这道题](https://www.luogu.com.cn/problem/P2149)。

回到这道题目中。题目要求删除一些边直到剩余的边的数量少于 $K$，我们不妨反过来考虑，即加入 $K$ 后使得好点个数最多。

我们发现，加边的过程实际上是一个从起点逐步扩张的过程（加边顺序是无所谓的，并且每个好点一定和起点相连接，所以可以这样认为）。因此每次加一个边，增加的好点的个数至多是 $1$。

我们利用前面提到的性质，跑一遍 dijkstra 并把那棵树建出来。那么只要加入的每一条边都是在那个树上的边，在好点个数达到 $N$ 之前，每加入一条边都能增加一个好点。也就是说这种加边方法达到了理论上限，所以这是最优的。

这个过程没啥难的，注意在 $K>N-1$ 的时候也只需要加入 $N-1$ 条边，再注意一下题目的数据范围就可以了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,int> pli;
const int MAXN=300050;
int N,M,K,fa[MAXN],id[MAXN];
//fa表示每个点的前驱，id表示通往这个前驱的边的编号 
int h[MAXN],to[MAXN<<1],nxt[MAXN<<1],d[MAXN<<1],tot;
int h1[MAXN],to1[MAXN],nxt1[MAXN],tot1,ans[MAXN],cnt;
bool vis[MAXN];
LL dist[MAXN];
inline void add(int u,int v,int w){
	to[++tot]=v,nxt[tot]=h[u],d[tot]=w,h[u]=tot;
}
inline void add1(int u,int v){
	to1[++tot1]=v,nxt1[tot1]=h1[u],h1[u]=tot1;
}
//注意这个图是无向图，每条边插入了两次
inline int getid(int x){
	return (x-1)/2+1;
}
void dij(){
	priority_queue<pli,vector<pli>,greater<pli> > pq;
	pq.push(make_pair(0,1));
	memset(dist,0x3f,sizeof(dist));
	dist[1]=0;
	while(!pq.empty()){
		pli temp=pq.top();pq.pop();
		if(vis[temp.second]) continue;
		vis[temp.second]=1;
		for(int i=h[temp.second];i;i=nxt[i]){
			if(dist[to[i]]>dist[temp.second]+d[i]){
				dist[to[i]]=dist[temp.second]+d[i];pq.push(make_pair(dist[to[i]],to[i]));
				fa[to[i]]=temp.second,id[to[i]]=i;
			}
		}
	}
}
void dfs(int x){
	if(id[x]) ans[++cnt]=id[x];
	for(int i=h1[x];i;i=nxt1[i]){
		if(to1[i]==fa[x]) continue;
		dfs(to1[i]);
	}
}

int main()
{
	scanf("%d%d%d",&N,&M,&K);
	for(int i=1;i<=M;++i){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	dij();
	for(int i=1;i<=N;++i) add1(fa[i],i);
	dfs(1);
	K=min(K,N-1);
	printf("%d\n",K);
	for(int i=1;i<=K;++i) printf("%d%c",getid(ans[i])," \n"[i==K]);
	
	return 0;
}
```


---

## 作者：优秀的渣渣禹 (赞：0)


题目大意：给定 N 个点 M 条边的无向简单联通图，留下最多 K 条边，求剩下的点里面从 1 号顶点到其余各点最短路大小等于原先最短路大小的点最多怎么构造。

这个题贪心+dijkstra

我们可以在第一次跑 dij 时直接采用贪心策略，即：若当前答案集合的大小小于 K 且优先队列非空，则继续优先队列遍历，每次把一条边加入到答案集合中。

因为是在求解最短路过程中向答案集合中加边，可知这就是一种最优策略。

```cpp
#define B cout << "BreakPoint" << endl;
#define O(x) cout << #x << " " << x << endl;
#define O_(x) cout << #x << " " << x << " ";
#define Msz(x) cout << "Sizeof " << #x << " " << sizeof(x)/1024/1024 << " MB" << endl;
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>
#define LL long long
const int inf = 1e9 + 9;
const int N = 5e5 + 5;
using namespace std;
inline int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')
			w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}
typedef pair<LL,int> pii;
struct node{
    int nxt,to,w;
}e[N<<1];
int head[N],n,m,k,pre[N],vis[N],tot = 1;
inline void add(int x,int y,int w){
    e[++tot] = node{head[x],y,w},head[x] = tot;
}
LL dis[N];
vector<int> ans;
priority_queue<pii> q;
void init(){
    n = read(),m = read(),k = read();
    for(int i = 1;i <= m;i++){
        int x = read(),y = read(),w = read();
        add(x,y,w),add(y,x,w);
    }
}
void dij(){
    for(int i = 2;i <= n;i++) dis[i] = 1e15;
    q.push(make_pair(0,1));
    while(!q.empty() && ans.size() < k){
        int u = q.top().second;
		q.pop();
        if(vis[u]) continue;
        if(u ^ 1) ans.push_back(pre[u] / 2);
        vis[u] = 1;
        for(int i = head[u];i;i = e[i].nxt){
            int v = e[i].to,w = e[i].w;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w,pre[v] = i;
                q.push(make_pair(-dis[v],v));
            }
        }
    }
}
void solve(){
    dij();
    k = ans.size();
    printf("%d\n",k);
    for(int i = 0;i < k;i++) printf("%d ",ans[i]);
}
int main(){
    init();
    solve();
    return 0;
}
```



---

