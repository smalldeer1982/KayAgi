# Madoka and The First Session

## 题目描述

给出整数 $n$ 和 $m$ 对整数$(v_i,u_i)$。同时有一个序列 $B$ ,长度为 $n$ ，保证一开始全为 $0$ 。

然后对于每一对 $(v_i,u_i)$，可以执行两种操作中的一种:

1. $b_{v_i}\gets b_{v_i}-1，b_{u_i}\gets b_{u_i}+1$
2. $b_{v_i}\gets b_{v_i}+1，b_{u_i}\gets b_{u_i}-1$

然后还会给你两个序列 $A$，$S$  长度均为 $n$，保证当 $s_i=0$ 时，$a_i=0$ 。

问你在在所有操作方案中，是否有一种可以使得对于任意的 $s_i=1$，都有 $a_i=b_i$。

## 说明/提示

### 样例解释

在第一个示例中，数组 $b$ 将发生如下变化：$[0,0,0,0,0] \rightarrow [-1,0,0,1,0] \rightarrow [-2,0,0,1,1] \rightarrow [-2,0,1,0,1] \rightarrow [-2,0,2,0,0] \rightarrow [-2,0,2,1,-1]$。从 $1$ 到 $5$ 的所有 $i$ 中满足$a_i = b_i$ 。

在第二个示例中，我们只需将 $b_2 = 1$ 放在末尾即可，因为只有 $s_2 = 1$ 。

在第三个示例中，操作无法按要求进行。

## 样例 #1

### 输入

```
5 5
1 1 1 1 1
-2 0 2 1 -1
1 5
1 4
3 5
3 4
4 5```

### 输出

```
YES
1 5
1 4
5 3
4 3
5 4```

## 样例 #2

### 输入

```
5 5
0 1 0 1 0
0 1 0 0 0
1 3
2 3
3 5
3 4
4 5```

### 输出

```
YES
1 3
3 5
3 2
4 3
5 4```

## 样例 #3

### 输入

```
4 4
1 1 1 1
0 2 -2 2
1 3
1 4
2 3
2 4```

### 输出

```
NO```

# 题解

## 作者：DaiRuiChen007 (赞：10)

# CF1717F 题解

## 思路分析

考虑把原题转化成一个图论题，即给定一张无向图，将其中的每条边规定一个方向使得对于所有 $u\in \mathbf S$ 有 $\operatorname{InDegree}(u)-\operatorname{OutDegree}(u)=a_u$，其中 $\mathbf S$ 是题目中所有 $s_i=1$ 的 $i$ 构成的集合。

注意到 $\operatorname{InDegree}(u)+\operatorname{OutDegree}(u)=\operatorname{Degree}(u)$ 已经确定，因此该限制等价于 $\operatorname{InDegree}(u)=\dfrac{a_u+\operatorname{Degree}(u)}2$，记为 $f_u$，显然，如果某个 $f_u\not\in \mathbb N$ 则无解。

考虑建模成网络流模型，对于每个点和每个边分别建立节点，显然先将每个边节点向其连接的两个点的对应节点连接一条任意边权的边，以边权为 $1$ 为例。

由于每条边只能流向一个端点且每条边只能选择一次，因此从源点向每个边节点连一条边权为 $1$ 的边。

此时，每向某个点 $u$ 对应的节点流 $1$ 的流量，即等价于使 $\operatorname{InDegree}(u)\gets \operatorname{InDegree}(u)+1$。

然后考虑在当前限制下能不能让 $\mathbf S$ 中的元素 $i$ 流过 $f_i$ 的流量，因此对于 $\mathbf S$ 中的每个 $i$ 对应的节点都向汇点连一条边权为 $f_i$ 的边，如果最终的最大流等于 $\mathbf S$ 中 $f_i$ 的和则表示存在一种方式使得对于原问题中每一个 $s_i=1$ 有 $a_i=b_i$。

考虑如下数据：

```
3 3
1 1 1
0 -1 0
1 2
2 3
3 1
```

此时得到的流量网络如下图：

[![voG2bn.png](https://s1.ax1x.com/2022/09/03/voG2bn.png)](https://imgse.com/i/voG2bn)

其中 $e1\sim e3$ 表示三条边分别对应的节点，$n1\sim n3$ 是三个节点对应的节点，$S,T$ 是源点和汇点。

上图的最大流为 $2$，满足条件，但是原数据并没有解，因为图上 $S\to e2$ 的边无论如何都不能流，否则就无解了。

由于，网络流只能保证每条边**至多**选择一次而不是**恰好**选择一次，因此我们最后还需要**在刚才求过最大流的图中**，把不在 $\mathbf S$ 里的节点都向汇点连一条边权为 $\infty$ 的边，再求一次最大流，如果两次最大流得到的结果的和为 $m$ 才能说明我们选择了所有的边。

输出答案的时候只需要考虑每条边节点的流量流向哪个节点即可。

时间复杂度 $\Theta((n+m)\sqrt m)$，证明参见官方题解。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;

namespace Dinic {

const int MAXN=2e4+5,MAXM=1e5+5,INF=1e18;
struct node {
	int des,val,lst;
}	edge[MAXM];
int head[MAXN],cur[MAXN],dep[MAXN],tot=1;
int S,T;
bool inq[MAXN];
inline void add(int u,int v,int w) {
	edge[++tot]=(node){v,w,head[u]};
	head[u]=tot;
}
inline bool bfs() {
	queue <int> q;
	memset(dep,0,sizeof(dep));
	memcpy(cur,head,sizeof(cur));
	q.push(S),dep[S]=1;
	while(!q.empty()) {
		int p=q.front();
		q.pop();
		for(int i=head[p];i;i=edge[i].lst) {
			int v=edge[i].des;
			if(!edge[i].val||dep[v]) continue;
			dep[v]=dep[p]+1;
			q.push(v);
		}
	}
	return dep[T]>0;
}
inline int dfs(int p,int MaxFlow) {
	if(p==T||!MaxFlow) return MaxFlow;
	int RestFlow=MaxFlow;
	for(int i=cur[p];i;i=edge[i].lst) {
		cur[p]=i;
		int v=edge[i].des;
		if(dep[v]==dep[p]+1&&edge[i].val) {
			int GetFlow=dfs(v,min(RestFlow,edge[i].val));
			if(!GetFlow) dep[v]=INF;
			edge[i].val-=GetFlow;
			edge[i^1].val+=GetFlow;
			RestFlow-=GetFlow;
			if(!RestFlow) break;
		}
	}
	return MaxFlow-RestFlow;
}
inline int solve(int Source,int Dest) {
	S=Source,T=Dest;
	int MaxFlow=0;
	while(bfs()) MaxFlow+=dfs(S,INF);
	return MaxFlow;
}

}

inline int link(int u,int v,int w) {
	Dinic::add(v,u,0);
	Dinic::add(u,v,w);
	return Dinic::tot;
}
inline int value(int id) {
	return Dinic::edge[id].val;
}

const int MAXN=1e4+1,INF=1e18;
int a[MAXN],s[MAXN],p[MAXN];
struct node {
	int src,des;
}	edge[MAXN];

signed main() {
	int n,m;
	scanf("%lld%lld",&n,&m);
	int S=n+m+1,T=n+m+2;
	for(int i=1;i<=n;++i) scanf("%lld",&s[i]);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=m;++i) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		++a[u],++a[v];
		edge[i]=(node){u,v};
		link(S,n+i,1);
		p[i]=link(n+i,u,1);
		link(n+i,v,1);
	}
	int tot=0,res=0;
	for(int i=1;i<=n;++i) {
		if(!s[i]) continue;
		if(a[i]<0||a[i]%2==1) return 0&puts("NO");
		a[i]>>=1;
		link(i,T,a[i]);
		tot+=a[i];
	}
	res=Dinic::solve(S,T);
	if(res!=tot) return 0&puts("NO");
	for(int i=1;i<=n;++i) if(!s[i]) link(i,T,INF);
	res+=Dinic::solve(S,T);
	if(res!=m) return 0&puts("NO");
	puts("YES");
	for(int i=1;i<=m;++i) {
		if(value(p[i])>0) printf("%lld %lld\n",edge[i].src,edge[i].des);
		else printf("%lld %lld\n",edge[i].des,edge[i].src);
	}
	return 0;
}
```



---

## 作者：Aria_Math (赞：2)

不是很一样。

容易转化为图论问题：给每条边定向，使得 $s_i=1$ 的点满足 $b_i = in_i-out_i$ 恰好为 $a_i$。

**处理这种问题的常见方法是先钦定每条边的方向。** 

我们钦定每条边是 $u \rightarrow v$，则给边转向相当于把 $b_u$ 减 $2$，给 $b_v$ 加 $2$。则问题相当于有一个初始全为 $0$ 的序列，每次可以选择把一个数减 $2$，把一个数加 $2$，问是否可达序列 $a$。

显然 $a_i$ 为奇数无解。否则给所有数除以 $2$。
因为序列有正有负，所以给所有数加上一个极大值 $\Delta$。容易用上下界网络流建图：$S$ 到 $i$ 连 $[\Delta,\Delta]$ 的边，$i$ 到 $j$ 连 $[0,1]$ 的边，若 $s_i=0$ 则到 $T$ 连 $[0,\infty]$，否则连 $[a_i+\Delta,a_i+\Delta]$。直接求有源汇上下界可行流即可。


## Code

```cpp
// They say that life is always easier
// After you let yourself come undone
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int NN = 1e4 + 10;
const int MM = 4e4 + 10;
const int INF = 1e9;
const ll INFLL = 1e18;
struct Edge {
	int nxt, v; ll w;
} G[MM * 2];
int S, T, head[NN], cnt = 1, dep[NN], cur[NN];
void Add(int u, int v, ll w) {
	G[++cnt] = {head[u], v, w}, head[u] = cnt;
	G[++cnt] = {head[v], u, 0}, head[v] = cnt;
}
bool Bfs() {
	memset(dep, 0, sizeof(dep));
	memcpy(cur, head, sizeof(cur));
	static int q[NN], h, t;
	q[h = t = 0] = S , dep[S] = 1;
	while(h <= t) {
		int u = q[h++];
		for(int i = head[u]; i; i = G[i].nxt) if(G[i].w && !dep[G[i].v])
			dep[G[i].v] = dep[u] + 1, q[++t] = G[i].v;
	}
	return dep[T];
}
ll Dfs(int u = S, ll flow = INFLL) {
	if(u == T) return flow; ll rest = flow;
	for(int i = cur[u]; i && rest; i = G[i].nxt) {
		int v = G[i].v; ll w = G[i].w; cur[u] = i;
		if(w && dep[v] == dep[u] + 1) {
			ll sum = Dfs(v, rest < w ? rest : w);
			if(!sum) dep[v] = 0;
			rest -= sum, G[i].w -= sum, G[i ^ 1].w += sum;
		}
	}
	return flow - rest;
}
ll Dinic() {
	ll ans = 0;
	while(Bfs()) ans += Dfs();
	return ans;
}
const int N = 1e4 + 10;
struct Node {
	int u, v;
} E[N];
int n, m, s[N], opt[N];
ll deg[N], a[N], b[N], now[N];
vector<pair<int, int>> V[N];
signed main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m; 
	for(int i = 1; i <= n; ++i) cin >> s[i];
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		E[i] = {u, v}, V[v].push_back({u, i});
		++a[u], --a[v], Add(v, u, 1);
	}
	for(int i = 1; i <= n; ++i) 
		if(s[i] && (a[i] % 2 + 2) % 2 == 1) return printf("NO\n"), 0;
		else a[i] = a[i] / 2 + INF;
	for(int i = 1; i <= n; ++i)
		deg[n + 1] -= INF, deg[i] += INF;
	for(int i = 1; i <= n; ++i) 
		if(s[i]) deg[i] -= a[i], deg[n + 2] += a[i];
		else Add(i, n + 2, INFLL);
	Add(n + 2, n + 1, INFLL);
	S = n + 3, T = S + 1;
	for(int i = 1; i <= n + 2; ++i)
		if(deg[i] < 0) Add(i, T, -deg[i]);
		else if(deg[i] > 0) Add(S, i, deg[i]);
	Dinic();
	for(int i = head[S]; i; i = G[i].nxt) if(G[i].w) 
		return printf("NO\n"), 0;
	for(int i = head[T]; i; i = G[i].nxt) if(G[i ^ 1].w)
		return printf("NO\n"), 0;
	for(int u = 1; u <= n; ++u)
		for(int i = head[u]; i; i = G[i].nxt) if(G[i].v <= n && !(i & 1)) {
			if(!G[i].w) opt[V[u].back().second] = 1;
			V[u].pop_back();
		}
	printf("YES\n");
	for(int i = 1; i <= m; ++i)
		if(!opt[i]) printf("%d %d\n", E[i].u, E[i].v);
		else printf("%d %d\n", E[i].v, E[i].u);
	return 0;
}
```

---

## 作者：pengyule (赞：2)

做完这道题后，居然发现题解区都是长篇大论！

看到 $n,m\le 10000$ 的数据范围和题目的应用背景，不难想到这是一道流题。

对于“二选一”的限制，自然转化为先全部 $a_{u_i}\gets a_{u_i}+1,a_{v_i}\gets a_{v_i}-1$，然后就变成了“是否选择将 $a_{u_i}\gets a_{u_i}-2,a_{v_i}\gets a_{v_i}+2$”。

此时如果 $\exists 2\nmid a_i$，无解。

那么自然将 $±2$ 看作 $±1$，连边 $(u_i,v_i,1,0)$。

现在要把 $s_i=1$ 的所有 $a_i$ 全部归零，$s_i=0$ 的随便剩多少都可以。

自然对于所有 $s_i=1$，当 $a_i>0$ 时连 $(S,i,\frac {a_i} 2,-\inf)$，当 $a_i<0$ 时连 $(i,T,-\frac {a_i}2,-\inf)$。这就是可行流的平衡流量的步骤。换句话说，如果 $a_i>0$ 就一定会优先增广这一条边，导致真正的出流总是比入流多 $\frac {a_i}2$，也就代表最终 $a_i$ 会减去 $a_i$ 变成 $0$。

最后对于 $s_i=0$，入流出流可以不平衡，所以加 $(S,i,\inf,0),(i,T,\inf,0)$ 即可。

最后判断是否“真的”归零了。这也是可行流的必要检验步骤。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace IO {
const int buflen=1<<21;
int x;
bool f;
char ch,buf[buflen],*p1=buf,*p2=buf;
inline char gc(){return p1==p2&&(p2=buf+fread(p1=buf,1,buflen,stdin),p1==p2)?EOF:*p1++;}
inline int read(){
	x=0,f=1,ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=gc();
	return f?x:-x;
}
}
using IO::read;
const int N=1e4+5,E=6e4+5;
int n,m,S,T,tot=1,a[N],s[N],we[E],dis[N],u[N],v[N];
bool inq[N];
struct Edge {
	int y,z,c;
}fr[N];
vector<Edge>G[N];
queue<int>Q;
inline void adde(int u,int v,int w,int c){
	G[u].emplace_back(Edge{v,++tot,c}),we[tot]=w;
	G[v].emplace_back(Edge{u,++tot,-c}),we[tot]=0;
}
bool spfa(){
	memset(dis,0x3f,sizeof dis);
	Q.push(S);dis[S]=0;
	while(!Q.empty()){
		int x=Q.front();Q.pop();inq[x]=0;
		for(auto e:G[x]){
			int y=e.y,z=e.z,c=e.c;
			if(we[z]&&dis[y]>dis[x]+c){
				dis[y]=dis[x]+c;
				fr[y]=Edge{x,z,c};
				if(!inq[y])Q.push(y),inq[y]=1;
			}
		}
	}
	return dis[T]!=dis[0];
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)s[i]=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)u[i]=read(),v[i]=read(),a[u[i]]++,a[v[i]]--;
	for(int i=1;i<=n;i++)if(s[i]&&(a[i]&1)){puts("NO");return 0;}
	for(int i=1;i<=m;i++)adde(u[i],v[i],1,0);
	S=n+1,T=n+2;
	for(int i=1;i<=n;i++){
		if(s[i]){
			if(a[i]>0)adde(S,i,a[i]/2,-100);
			if(a[i]<0)adde(i,T,-a[i]/2,-100);
		}
		else adde(S,i,1000000,0),adde(i,T,1000000,0);
	}
	while(spfa()){
		int mn=1e9;
		for(int i=T;i!=S;i=fr[i].y)mn=min(mn,we[fr[i].z]);
		if(dis[T]>=0)break;
		for(int i=T;i!=S;i=fr[i].y)we[fr[i].z]-=mn,we[fr[i].z^1]+=mn;
	}
	for(int i=1;i<=m;i++)if(we[2*i+1])a[u[i]]-=2,a[v[i]]+=2;
	//for(int i=1;i<=n;i++)cerr<<a[i]<<';';
	for(int i=1;i<=n;i++)if(s[i]&&a[i]){puts("NO");return 0;}
	puts("YES");
	for(int i=1;i<=m;i++)if(we[2*i+1])cout<<v[i]<<' '<<u[i]<<'\n';else cout<<u[i]<<' '<<v[i]<<'\n';
	return 0;
}
/*
g++ -o CF0529.exe CF0529.cpp -O2 -lm -std=c++14 -Wall -Wextra
./CF0529.exe<in
*/
```

---

## 作者：I_am_Accepted (赞：2)

深感 wxw 爆叉 $33$ 人的强大，以及数据人和题解人的行为过于摆烂。

耗在这道题上一天了捏。

## 分析

先将每一条边的两端均 $-1$，则接下来我们要对于每一条边选一个端点 $+2$。

为方便，不妨设 $b_i=\dfrac{a_i+deg_i}{2}$。

相当于每个点现在是 $-b_i$，对于每一条边选一个端点 $+1$，问是否存在全部清零的方案。

先排掉三类非法情况：

* 存在 $b_i$ 为负数。
* 存在 $b_i$ 不为整数。
* $b_i$ 之和 $>m$。

## 建图

网络流，将每条边也建新点（算进源汇共 $n+m+2$ 个点）。

以下方括号内的两个数字代表流量上下界。

对于每一条边 $x:(u,v)$（$x$ 为边所对应的点标号），建边
$$
S\to x[1,1]\quad x\to u[0,1]\quad x\to v[0,1]
$$
对于每一个 $s=1$ 的点 $x$

$$
x\to T[b_x,b_x]
$$

对于每一个 $s=0$ 的点 $x$

$$
x\to T[0,\infty]
$$

跑上下界可行流即可。

~~先上代码，时间复杂度先别急。~~

## 如何建图及时间复杂度

我们建这些边（$E$ 为 $m$ 条边的集合，$S',T'$ 为原图的源汇，$S,T$ 为上下界建图的源汇）：
$$
\begin{array}{rll|l}
S&\to e&:1&e\in E
\\
S'&\to T&:1&
\\
S&\to T'&:\sum_i b_i&
\\
(u,v) &\to u&:1& (u,v)\in E
\\
(u,v) &\to v&:1&
\\
x &\to T&:b_x&s_x=1
\\
x &\to T'&:\color{red}\infty&s_x=0
\\
T' &\to S'&:\color{blue}\infty
\end{array}
$$
发现一个点 $x$ 的入流量不超过 $deg_x$，所以 ${\color{red}\infty}\Rightarrow deg_x$。

发现原图的总流量最大不超过 $m$，所以 ${\color{blue}\infty}\Rightarrow m$。

跑 Dinic，由于最多增广 $n-1$ 次，而且每次增广时间不会超过总容量 $O(n+m)$，所以复杂度为 $O(n(n+m))$。

## 代码

```cpp
/*
* Author: ShaoJia
* Last Modified time: 2022-09-03 20:47:59
* Motto: We'll be counting stars.
*/
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define debug(...) cerr<<"#"<<__LINE__<<": "<<__VA_ARGS__<<endl
const int N=10010,M=40010;
int n,m,sum=0,a[N],deg[N],p[N],L[N],R[N];
bool s[N];
struct edge{
	int nxt,to,flow;
}e[M<<1];
int mf=0,dis[N<<1],cur[N<<1],head[N<<1],S0,T0,S,T,tot=1,v[N],ans[N];
inline void adde(int x,int y,int z){
	// cout<<x<<" "<<y<<":"<<z<<endl;
	e[++tot]=(edge){head[x],y,z}; head[x]=tot;
	e[++tot]=(edge){head[y],x,0}; head[y]=tot;
}
queue<int> q;
bool bfs(){
	fill(dis+1,dis+1+T,0);
	dis[S]=1;
	q.push(S);
	int x;
	while(!q.empty()){
		x=q.front();
		q.pop();
		cur[x]=head[x];
		for(int i=head[x],to;i;i=e[i].nxt){
			to=e[i].to;
			if(!e[i].flow) continue;
			if(!dis[to]){
				dis[to]=dis[x]+1;
				q.push(to);
			}
		}
	}
	return dis[T];
}
int dfs(int x,int flow){
	if(x==T) return flow;
	int res=0;
	for(int &i=cur[x],to,tmp;i;i=e[i].nxt){
		to=e[i].to;
		if(!e[i].flow || dis[to]!=dis[x]+1) continue;
		tmp=dfs(to,min(flow,e[i].flow));
		flow-=tmp;
		res+=tmp;
		e[i].flow-=tmp;
		e[i^1].flow+=tmp;
		if(!flow) break;
	}
	return res;
}
void Dinic(){
	while(bfs()) mf+=dfs(S,m+sum);
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>m;
	S0=n+m+1; T0=S0+1; S=T0+1; T=S+1;
	For(i,1,n) cin>>s[i];
	int x,y;
	For(i,1,n) cin>>a[i];
	For(i,1,m){
		cin>>x>>y;
		deg[x]++,deg[y]++;
		L[i]=x,R[i]=y;
	}
	For(i,1,n){
		if(s[i]){
			a[i]+=deg[i];
			if(a[i]<0 || a[i]&1) return cout<<"NO"<<endl,0;
			a[i]>>=1;
		}else a[i]=0;
	}
	// debug("?");
	For(i,1,n) sum+=a[i];
	if(sum>m) return cout<<"NO"<<endl,0;
	For(i,1,m){
		adde(S,i+n,1);
		p[i]=tot+1;
		adde(i+n,L[i],1);
		adde(i+n,R[i],1);
	}	
	adde(S0,T,m);
	adde(S,T0,sum);
	adde(T0,S0,m);
	For(i,1,n)
		if(s[i]) adde(i,T,a[i]);
		else adde(i,T0,deg[i]);
	Dinic();
	if(mf!=m+sum) return cout<<"NO"<<endl,0;
	cout<<"YES"<<endl;
	For(i,1,m){
		if(e[p[i]].flow) cout<<L[i]<<" "<<R[i]<<endl;
		else cout<<R[i]<<" "<<L[i]<<endl;
	}
return 0;}
```

---

## 作者：Leasier (赞：1)

前置芝士：[费用流](https://oi-wiki.org/graph/flow/min-cost/)

一个加一一个减一不便操作，不妨先对每个操作 $(u, v)$，把 $a_u, a_v$ 各减一，把操作变成：

- 让 $a_u$ 或 $a_v$ 加二。

现在问题变为求每个操作二选一执行时能否把 $a_u$ 变为 $0$。

首先有一些显然的无解条件（下面均为对 $1 \leq i \leq n, s_i = 1$ 的讨论）：

- $a_i > 0$
- $a_i \bmod 2 \neq 0$

把这些情况判掉后，为了方便，令 $a_i \leftarrow -\frac{a_i}{2}$。

下面是我的赛时 AC 但赛后 WA 的做法：

注意到操作是二选一，考虑通过网络流的流量来对此进行限制。

考虑对每个操作 $i$ 建点 $i$，对每个元素 $j$ 建点 $j'$。

- $S \to^1 i, i \to^1 u_i', i \to^1 v_i'$，这份流量要么前往 $u_i'$，要么前往 $v_i'$。
- $\forall s_i = 0, i' \to^{\infty} T$，对于无限制的点，其流量之和无限制。
- $\forall s_i = 1, i' \to^{a_i} T$，对于有限制的点，其流量必须恰为 $a_i$。

建图跑最大流即可。最后若某个操作没有被执行或有限制的点没有流满时均无解。输出方案时看一下对于每个操作 $i$，其流量是流向了 $u_i'$ 还是 $v_i'$ 即可。

然而赛后再次提交却显示 WA on 67 /fn

仔细想一想会发现这种做法是有问题的，问题出在对无限制的点的讨论上，因为我们只需要有限制的点满流。

考虑不建出无限制的点相关的边。

我们现在对上述建图进行修正：

- $S \to^1 i$，操作 $i$ 至多一份流向有限制的点的流量。
- 若 $s_{u_i} = 1$，$i \to^1 u_i'$，这份流量可以前往 $u_i'$。
- 若 $s_{v_i} = 1$，$i \to^1 v_i'$，这份流量可以前往 $v_i'$。
- $\forall s_i = 1, i' \to^{a_i} T$，对于有限制的点，其流量必须恰为 $a_i$。

建图跑最大流即可。最后若有限制的点没有流满时均无解。

但这里有一处与上述不同，输出方案时有如下两种可能：

1. 这条边没有流量

若 $s_{u_i} = 1$ 且 $s_{v_i} = 1$，无解；若 $s_{u_i} = 0$，输出 $(u_i, v_i)$；否则，输出 $(v_i, u_i)$。

2. 这条边有流量

若 $s_{u_i} = 1$ 且 $i \to u_i'$ 这条边流满了，输出 $(u_i, v_i)$；否则，输出 $(v_i, u_i)$。

然而还是显示 WA on 68 /fn

现在的问题在于也许某条满足 $s_{u_i} = 1$ 且 $s_{v_i} = 1$ 的边有流量时可行，但没有流量时可以由其他边补足，而此时会输出无解。

所以我们要优先考虑满足 $s_{u_i} = 1$ 且 $s_{v_i} = 1$ 的边，所以考虑给这几条边赋费用 $1$，给其他边赋费用 $0$。

建图跑费用流即可。注意需要写 zkw 费用流，直接跑 SSP 算法会 TLE on 15。

代码：
```cpp
#include <iostream>
#include <queue>

using namespace std;

typedef struct {
	int nxt;
	int end;
	int dis;
	int cost;
} Edge;

int cnt = 1, tm = 0;
int s[10007], a[10007], u[10007], v[10007], head[20007], operation[10007], choice[10007], full[10007], dis[20007], vis1[20007];
bool vis2[20007];
Edge edge[80007];
queue<int> q;

inline void init(int n){
	for (register int i = 0; i <= n; i++){
		dis[i] = -2e9;
		vis1[i] = false;
	}
}

inline void add_edge(int start, int end, int dis, int cost){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
	edge[cnt].dis = dis;
	edge[cnt].cost = cost;
}

inline void spfa(int start){
	dis[start] = 0;
	vis2[start] = true;
	q.push(start);
	while (!q.empty()){
		int cur = q.front();
		q.pop();
		vis2[cur] = false;
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			if (edge[i].dis == 0){
				int x = edge[i].end, y = dis[cur] - edge[i].cost;
				if (dis[x] < y){
					dis[x] = y;
					if (!vis2[x]){
						vis2[x] = true;
						q.push(x);
					}
				}
			}
		}
	}
}

int dfs(int u, int flow, int end){
	if (u == end) return flow;
	int ans = 0;
	vis1[u] = tm;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (vis1[x] != tm && edge[i].dis != 0 && dis[x] == dis[u] - edge[i].cost){
			int t = dfs(x, min(flow - ans, edge[i].dis), end);
			edge[i].dis -= t;
			edge[i ^ 1].dis += t;
			ans += t;
			if (ans == flow) return ans;
		}
	}
	return ans;
}

inline bool update(int n, int start){
	int delta = -2e9;
	for (register int i = 0; i <= n; i++){
		if (vis1[i] == tm){
			for (register int j = head[i]; j != 0; j = edge[j].nxt){
				if (edge[j].dis != 0){
					int x = edge[j].end;
					if (vis1[x] != tm) delta = max(delta, dis[x] - dis[i] + edge[j].cost);
				}
			}
		}
	}
	if (delta == -2e9) return false;
	for (register int i = 0; i <= n; i++){
		if (vis1[i] == tm) dis[i] += delta;
	}
	return dis[start] != 0x80000000;
}
	 
inline pair<int, int> maxcost_maxflow(int n, int start, int end){
	pair<int, int> ans(0, 0);
	init(n);
	spfa(end);
	do {
		int flow = 0;
		while (true){
			int t;
			tm++;
			t = dfs(start, 0x7fffffff, end);
			if (t == 0) break;
			flow += t;
		}
		ans.first += flow;
		ans.second += flow * dis[start];
	} while (update(n, start));
	return ans;
}

int main(){
	int n, m, end;
	cin >> n >> m;
	end = n + m + 1;
	for (register int i = 1; i <= n; i++){
		cin >> s[i];
	}
	for (register int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (register int i = 1; i <= m; i++){
		int cost;
		cin >> u[i] >> v[i];
		cost = s[u[i]] == 1 && s[v[i]] == 1 ? 1 : 0;
		add_edge(0, i, 1, cost);
		operation[i] = cnt;
		add_edge(i, 0, 0, -cost);
		if (s[u[i]] == 1){
			int u_ = u[i] + m;
			a[u[i]]--;
			add_edge(i, u_, 1, 0);
			choice[i] = cnt;
			add_edge(u_, i, 0, 0);
		}
		if (s[v[i]] == 1){
			int v_ = v[i] + m;
			a[v[i]]--;
			add_edge(i, v_, 1, 0);
			add_edge(v_, i, 0, 0);
		}
	}
	for (register int i = 1; i <= n; i++){
		if (s[i] != 0){
			if (a[i] > 0 || a[i] % 2 != 0){
				cout << "NO";
				return 0;
			}
			int i_ = i + m;
			add_edge(i_, end, -a[i] / 2, 0);
			full[i] = cnt;
			add_edge(end, i_, 0, 0);
		}
	}
	maxcost_maxflow(end, 0, end);
	for (register int i = 1; i <= n; i++){
		if (s[i] == 1 && edge[full[i]].dis != 0){
			cout << "NO";
			return 0;
		}
	}
	for (register int i = 1; i <= m; i++){
		if (s[u[i]] == 1 && s[v[i]] == 1 && edge[operation[i]].dis != 0){
			cout << "NO";
			return 0;
		}
	}
	cout << "YES" << endl;
	for (register int i = 1; i <= m; i++){
		if (edge[operation[i]].dis == 0){
			if (choice[i] != 0 && edge[choice[i]].dis == 0){
				cout << u[i] << " " << v[i] << endl;
			} else {
				cout << v[i] << " " << u[i] << endl;
			}
		} else if (s[u[i]] == 0){
			cout << u[i] << " " << v[i] << endl;
		} else {
			cout << v[i] << " " << u[i] << endl;
		}
	}
	return 0;
}
```

---

