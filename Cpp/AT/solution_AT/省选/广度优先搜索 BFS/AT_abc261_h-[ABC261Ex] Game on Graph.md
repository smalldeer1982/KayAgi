# [ABC261Ex] Game on Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc261/tasks/abc261_h

$ N $ 頂点 $ M $ 辺の有向グラフがあります。辺 $ i $ は頂点 $ A_i $ から $ B_i $ への有向辺で、重みが $ C_i $ です。

最初、頂点 $ v $ に駒が置かれています。高橋君と青木君が交互に次のように駒を動かすゲームを行います。

- 駒が置かれている頂点から出る辺が存在しないとき、ゲームを終了する。
- 駒が置かれている頂点から出る辺が存在するとき、そのうちいずれかの辺を選び、選んだ辺に沿って駒を移動する。

ゲームは高橋君から始め、高橋君はゲームが終了するまでに通った辺の重みの和を小さくしようとし、青木君は大きくしようとします。  
 $ 2 $ 人が目指すものはより厳密には、次の通りです。  
 高橋君は、ゲームを有限回の操作で終了させることを最優先し、それが可能ならば、ゲームが終了するまでに通る辺の重みの和を小さくしようとします。  
 青木君は、ゲームを有限回の操作で終了させないことを最優先し、それが不可能ならば、ゲームが終了するまでに通る辺の重みの和を大きくしようとします。  
 （駒が同じ辺を複数回通った場合は、重みはその回数だけ加算されるものとします。）

$ 2 $ 人が最善を尽くしたときゲームが有限回の操作で終了するか判定し、終了するならば、ゲームが終了するまでに通る辺の重みの和を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ v\ \leq\ N $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- 多重辺は存在しない。すなわち $ i\neq\ j $ のとき $ (A_i,B_i)\neq(A_j,B_j) $
- 自己辺は存在しない。すなわち $ A_i\neq\ B_i $
- $ 0\ \leq\ C_i\ \leq\ 10^9 $
- 入力に含まれる値は全て整数

### Sample Explanation 1

まず高橋君は頂点 $ 3 $ に駒を動かし、次に青木君が頂点 $ 7 $ に駒を動かし、ゲームが終了します。 ゲームが終了するまでに通る辺の重みの和は $ 10+30=40 $ になります。

### Sample Explanation 2

有限回の操作でゲームは終了しません。

### Sample Explanation 3

$ 1\to\ 2\ \to\ 3\ \to\ 1\ \to\ 2\to\ 4 $ と駒は動かされます。

## 样例 #1

### 输入

```
7 6 1
1 2 1
1 3 10
2 4 100
2 5 102
3 6 20
3 7 30```

### 输出

```
40```

## 样例 #2

### 输入

```
3 6 3
1 2 1
2 1 2
2 3 3
3 2 4
3 1 5
1 3 6```

### 输出

```
INFINITY```

## 样例 #3

### 输入

```
4 4 1
1 2 1
2 3 1
3 1 1
2 4 1```

### 输出

```
5```

# 题解

## 作者：Graphcity (赞：12)

考虑动态规划。$f_{i,0}$ 表示 Takahashi 在 $i$ 点先手时的得分，$f_{i,1}$ 表示 Aoki 先手的得分。显然有

$$
\begin{aligned}
f_{i,0}=\min_{i\to j}f_{j,1}+w(i,j)\\
f_{i,1}=\max_{i\to j}f_{j,0}+w(i,j)
\end{aligned}
$$

如果这个有向图是个 DAG，那就非常好解决。现在这个图有环了，处理动态规划转移顺序的问题就会比较棘手。

有一种想法是在环中直接输出 `INFINITY`。但是样例三就否定了这个想法。尝试去改进它：

- 对于 $f_{i,0}$：如果存在一个出点 $j$ 满足 $f_{j,1}$ 有值，都可以被更新。

- 对于 $f_{i,1}$：只有它的所有出点 $j$ 均满足 $f_{j,0}$ 有值，才可以去更新它。

我们用类似 Dijkstra 的方法去做转移：维护一个优先队列，每当得到一个 $f_{x,k}$ 时，就在反向图中松弛 $f_{y,1-k}$（存在边 $x\to y$）。再套用上面的更新规则往优先队列中加点即可。

时间复杂度 $O(m\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef pair<int,int> Pair;
const int Maxn=2e5;
const ll inf=1e18;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,s,oud[Maxn+5][2];
int vis[Maxn+5][2]; ll f[Maxn+5][2];
vector<Pair> v[Maxn+5],w[Maxn+5];
struct Node{int x,y; ll z;};
bool operator<(Node a,Node b) {return a.z>b.z;}
priority_queue<Node> q;

inline void bfs()
{
    while(!q.empty())
    {
        Node k=q.top(); q.pop();
        int x=k.x,t=k.y;
        if(vis[x][t]) continue;
        vis[x][t]=1;
        for(auto i:w[x])
        {
            int y=i.first,z=i.second; oud[y][t^1]--;
            if(t==1) f[y][0]=min(f[y][0],f[x][1]+z);
            if(t==0) f[y][1]=max(f[y][1],f[x][0]+z);
            if(!oud[y][t^1]) q.push((Node){y,t^1,f[y][t^1]});
            else if(t==1) q.push((Node){y,0,f[y][0]});
        }
    }
}

int main()
{
    n=read(),m=read(),s=read();
    For(i,1,m)
    {
        int a=read(),b=read(),c=read();
        v[a].push_back(make_pair(b,c));
        w[b].push_back(make_pair(a,c));
        oud[a][0]++,oud[a][1]++;
    }
    For(i,1,n) f[i][0]=inf;
    For(i,1,n)
        if(!oud[i][0])
        {
            f[i][0]=f[i][1]=0;
            q.push((Node){i,0,0});
            q.push((Node){i,1,0});
        }
    bfs();
    if(!vis[s][0]) printf("INFINITY\n");
    else printf("%lld\n",f[s][0]);
    return 0;
}
```

---

## 作者：Reunite (赞：10)

主要来说明一下正确性。

### 一
---
转移方程就不写了，大家都会，和其他题解相同，因为不是 DAG，无法直接 dp。这时候一般会考虑使用最短路算法进行转移，但要求是转移都是同号的，如都是 $\max$ 或者都是 $\min$，但在这题的转移当中，同时需要取 $\max,\min$，而这是 Dijkstra 无法处理的。

如果我们直接丢到 Dijkstra 里面去做，显然会错，因为我们可能把还没有决策完的一个 $f_{u,1}=x$ 丢到堆里，但实际上 $f_{u,1}=y>x$，然后在后续的更新中，我们用较小的 $x$ 去更新了 $f_{v,0}$，这显然是不合法的。

按照上面的过程，我们希望对于 $f_{u,1}$ 能在取完最大值后再去更新其他点，而 $f_{u,0}$ 则可以**直接更新别的点**。

为什么是对的呢，因为我们这样操作，相当于做了一步确定主元，我们是以 $f_{u,0}$ 为主元，算法的目标就是获得所有正确的 $f_{u,0}$，而 $f_{u,1}$ 则是辅助我们转移的。因此可以将整个过程看成对 $f_{u,0}$ 求最短路（实际上我们就是在求最短路），而有引理：Dijkstra 算法中，**取出的结点 $u$ 最短路均已经被确定，即满足 $D(u) = dis(u)$**。这个可以通过反证法证明，具体见 [oi-wiki 最短路 正确性证明](https://oi-wiki.org/graph/shortest-path/#dijkstra-%E7%AE%97%E6%B3%95)。因此我们每次拿出去转移 $f_{u,0}$ 的值都是正确的，而因此更新的 $f_{v,1}$ 也是正确的，不会出现类似的用未取到最小的 $f_{u,0}$ 去给 $f_{v,1}$ 取 $\max$，而这样当我们能更新 $f_{v,1}$ 的全部更新之后，$f_{v,1}$ 就是确定且正确的了，这时候我，再把它丢到堆里面，去更新以后的 $f_{u,0}$。

我们使用了类似递归证明的方法，而这个递归证明是有边界的（出度为 $0$ 的点已确定），这样，我们证明了这一做法的正确性。所以，这并不是所谓的魔改或者是玄学或是感性理解，这是可以证明且确定的。

复杂度 $O(m\log m)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define int long long
using namespace std;

int n,m,S;
int ind[200005];
int f[200005][2];
bool vis[200005][2];
struct node{int u,ok,d;};
bool operator < (node p,node q){return p.d>q.d;}
priority_queue <node> q;
vector <pair <int,int>> g[200005];

signed main(){
	scanf("%lld%lld%lld",&n,&m,&S);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		g[v].push_back({u,w});
		ind[u]++;
	}
	for(int i=1;i<=n;i++)
		if(ind[i]==0) q.push({i,0,0}),q.push({i,1,0});
		else f[i][0]=1e18;
	while(!q.empty()){
		auto tmp=q.top();
		q.pop();
		if(vis[tmp.u][tmp.ok]) continue;
		vis[tmp.u][tmp.ok]=1;
		int u=tmp.u,ok=tmp.ok;
		for(auto tmp:g[u]){
			int v=tmp.first,w=tmp.second;
			if(!ok){
				ind[v]--;
				f[v][1]=max(f[v][1],f[u][0]+w);
				if(!ind[v]) q.push({v,1,f[v][1]});
			}
			else{
				if(f[v][0]>f[u][1]+w){
					f[v][0]=f[u][1]+w;
					if(!vis[v][0]) q.push({v,0,f[v][0]});
				}
			}
		}
	}
	if(f[S][0]==1e18) puts("INFINITY");
	else printf("%lld\n",f[S][0]);

	return 0;
}
```

---

## 作者：Sonnety (赞：3)

样例分析：

~~（题意我觉得说的挺明白的）~~

不会就先分析样例，把图都画出来：

![样例图](https://cdn.luogu.com.cn/upload/image_hosting/qhy7aucx.png)

* 样例 #1：排除贪心，如果是贪心应该先走左边，但显然我们的 `Takahashi` 和 `Aoki` 都是绝顶聪明的，应该考虑动态规划。

* 样例 #2：如果有一个图没有任何一个点出度为 $0$，该图没有结果。

* 样例 #3：不是只要有环该图就没有结果，要考虑在当前点的人是谁，希望跑大的 `Aoki` 肯定跑死循环，但是希望跑小的 `Takahashi` 肯定跑通向结束的边，因此我们的动态规划设计中应该包含“在该点的人”的信息。

设计方程：

我们先假设这是一个有向无环图，那么设 $f_{u,[0/1]}$ 表示 `Takahashi` 和 `Aoki` 在点 $u$ 时，游戏结束的值。

有：

$$

\begin{aligned}

&f_{u,0}=\min_{u\to v}(f_{v,1}+val_{u,v})\\

&f_{u,1}=\max_{u\to v}(f_{v,0}+val_{u,v})

\end{aligned}

$$

根据这个方程我们建反图，从没有出度的点往上跑。

所以设有出度的点 $i$ 的 $f_{i,0}$ 为极大值，$f_{i,1}$ 为 $0$。

然后考虑两个人该怎么更新他们的方程：

* 希望跑小值的 `Takahashi` 就可以直接跑最小值，和我们正常的 Dijkstra 相同。

* 希望跑大值甚至死循环的 `Aoki` 就要等到其所在的点的子节点全部更新完在走，所以每走到他的一次子节点，我们给他的出度减 $1$，直到其出度为 $0$，我们再放入小根堆中。

所以这样就解决了环的问题。

最终答案是 $f_{s,0}$，如果是极大值那么输出 `INFINITY`。

```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define rg register int
#define next Hatsune
typedef long double llf;
typedef long long ll;
typedef pair<int,int> PII;
const double eps=1e-8;
namespace mystd{
	il int Max(int a,int b)<%if(a<b) return b;return a; %>
	il int Min(int a,int b)<%if(a>b) return b;return a; %>
	il int Abs(int a)<% if(a<0) return a*(-1);return a; %>
	il double fMax(double a,double b)<%if(a<b) return b;return a; %>
	il double fMin(double a,double b)<%if(a>b) return b;return a; %>
	il double fAbs(double a)<% if(a<0) return a*(-1);return a; %>
	il int dcmp(double a){
		if(a<-eps)	return -1;
		if(a>eps)	return 1;
		return 0;
	}
}const int maxn=2e5+50,maxm=2e5+50;
const ll MYMAX=(ll)0x3f3f3f3f3f3f3f3f;

int n,m,s,du[maxn];
bool vis[maxn][2];
ll f[maxn][2];

int head[maxm<<1],t;
struct edge{
	int u,v,w;
	int next;
};edge e[maxm<<1];
il void add_edge(int u,int v,int w){
	e[++t].u=u;
	e[t].v=v;
	e[t].w=w;
	e[t].next=head[u];
	head[u]=t;
}

struct Node{
	int v;
	char type;
	ll w;
};
bool operator>(Node n1,Node n2){
	return n1.w>n2.w;
}
priority_queue<Node,vector<Node>,greater<Node> >q;

void dijkstra(){
	
	while(!q.empty()){
		Node s=q.top();
		q.pop();
		int u=s.v,type=s.type-'0';
		if(vis[u][type]==true)	continue;
		vis[u][type]=true;
		if(type==1){
			for(rg i=head[u];i;i=e[i].next){
				int to=e[i].v;
				if(f[to][0]>f[u][1]+e[i].w){
					f[to][0]=f[u][1]+e[i].w;
					q.push({to,'0',f[to][0]});
				}
			}
		}
		else{
			for(rg i=head[u];i;i=e[i].next){
				int to=e[i].v;
				--du[to];
				if(f[to][1]<f[u][0]+e[i].w)	f[to][1]=f[u][0]+e[i].w;
				if(du[to]==0){
					q.push({to,'1',f[to][1]});
				}
			}
		}
	}
}

il void pre(){
	for(rg i=1;i<=n;++i){
		if(du[i]==0){
			Node s;
			s.v=i;
			s.type='0';
			s.w=0;
			q.push(s);
			s.type='1';
			q.push(s);
		}
		else	f[i][0]=MYMAX;
	}
}

il void input(){
	scanf("%d %d %d",&n,&m,&s);
	int u,v,w;
	for(rg i=1;i<=m;++i){
		scanf("%d %d %d",&u,&v,&w);
		++du[u];
		add_edge(v,u,w);
	}
}

int main(){
	input();
	pre();
	dijkstra();
	if(f[s][0]>1e18)	<% printf("INFINITY");return 0; %>
	else	printf("%lld",f[s][0]);
	return 0;
}
```

---

## 作者：Coffee_zzz (赞：2)

定义 $f_{u,0}$ 表示 Takahashi 在点 $u$ 先手时的得分，$f_{u,1}$ 表示 Aoki 在点 $u$ 先手时的得分。

初始时，所有出度为 $0$ 的结点 $u$ 所对应的 $f_{u,0}$ 和 $f_{u,1}$ 的值均为 $0$。为了方便，令出度不为 $0$ 的结点 $u$ 所对应的 $f_{u,0}$ 的值为极大值，并令其对应的 $f_{u,1}$ 的值为 $0$。

当图是 DAG 时，容易得到转移方程：

$$
f_{u,0}=\min_{(u,v)\in E} f_{v,1}+w(u,v)\\
f_{u,1}=\max_{(u,v)\in E} f_{v,0}+w(u,v)\\
$$

接下来考虑怎么处理环。

由于 Takahashi 的目标是最小化得分，所以 $f_{u,0}$ 可以直接用 Dijkstra 计算；而 Aoki 的目标是最大化得分，如果有无限循环的方法一定会选择无限循环，所以只有点 $u$ 的所有出边都被处理过时才能更新 $f_{u,1}$ 的值，在判断后进行转移即可。

计算完成后，若 $f_{s,0}$ 为极大值则游戏无法结束，否则 $f_{s,0}$ 即为答案。

时间复杂度 $\mathcal O (m \log m)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
const int N=2e5+5,inf=4e18;
int n,m,s,deg[N],f[N][2];
vector <pii> ve[N];
bool vis[N][2];
struct Nod{
	int u,t,w;
};
bool operator > (Nod a,Nod b){
	return a.w>b.w;
}
pq <Nod,vector<Nod>,greater<Nod> > q;
void solve(){
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		deg[u]++;
		ve[v].pb({w,u});
	}
	for(int u=1;u<=n;u++){
		if(deg[u]) f[u][0]=inf;
		else q.push({u,0,0}),q.push({u,1,0});
	}
	while(!q.empty()){
		int u=q.top().u,t=q.top().t;
		q.pop();
		if(vis[u][t]) continue;
		vis[u][t]=1;
		for(auto p:ve[u]){
			int w=p.fi,v=p.se;
			if(t==0){
				deg[v]--;
				f[v][1]=max(f[v][1],f[u][0]+w);
				if(deg[v]==0) q.push({v,1,f[v][1]});
			}
			else if(f[v][0]>f[u][1]+w){
				f[v][0]=f[u][1]+w;
				q.push({v,0,f[v][0]});
			}
		}
	}
	if(f[s][0]==inf) cout<<"INFINITY"<<endl;
	else cout<<f[s][0]<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc261_h)

**题目大意**

> 给定 $n$ 个点 $m$ 条边的带权有向图，棋子初始在 $s$，双方不断移动棋子，先手想最小化棋子移动总路程，后手想最大化总路程，求最终棋子移动总路程。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

先考虑朴素 dp：$f_{u,0/1}$ 表示当前轮到先手 / 后手，转移为：
$$
\begin{aligned}
f_{u,0}&=\min_{(u,v)\in E}f_{v,1}+w(u,v)\\
f_{u,1}&=\max_{(u,v)\in E}f_{v,0}+w(u,v)
\end{aligned}
$$
只有第一类转移的时候可以 Dijkstra 维护，每次弹堆就立刻得到 $f_{u,0}$ 的值，而 $f_{u,1}$ 我们需要滞后更新，记录 $f_{u,1}$ 的度数，直到所有入边都被处理后更新即可。

时间复杂度 $\mathcal O(m\log m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
const ll inf=1e18;
struct Edge { int v,w; };
vector <Edge> G[MAXN];
int n,m,s,deg[MAXN];
ll f[MAXN][2];
bool vis[MAXN][2];
signed main() {
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1,u,v,w;i<=m;++i) {
		scanf("%d%d%d",&u,&v,&w);
		G[v].push_back({u,w}),++deg[u];
	}
	priority_queue <array<ll,3>,vector<array<ll,3>>,greater<array<ll,3>>> Q;
	for(int i=1;i<=n;++i) {
		if(!deg[i]) Q.push({0,i,0}),Q.push({0,i,1});
		else f[i][0]=inf;
	}
	while(Q.size()) {
		int u=Q.top()[1],c=Q.top()[2]; Q.pop();
		if(vis[u][c]) continue; vis[u][c]=true;
		for(auto e:G[u]) {
			int v=e.v;
			if(!c) {
				--deg[v],f[v][1]=max(f[v][1],f[u][0]+e.w);
				if(!deg[v]) Q.push({f[v][1],v,1});
			} else if(f[v][0]>f[u][1]+e.w) {
				Q.push({f[v][0]=f[u][1]+e.w,v,0});
			}
		}
	}
	if(f[s][0]==inf) puts("INFINITY");
	else printf("%lld\n",f[s][0]);
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

神仙题，自己想不出来这个更新的技巧。

大概是这样的，这题容易想到这样一个动态规划：

我们设 $f_{i,0/1}$ 表示当前在点 $i$，负责移动的是先手/后手，此情况下的答案，那么有：

$$
\begin{aligned}
f_{i,0}&=\min_{i\to j}(f_{j,1}+val(i\to j))\\
f_{i,1}&=\max_{i\to j}(f_{j,0}+val(i\to j))
\end{aligned}
$$

由于图上可能有环，我们不能直接动态规划。

我们考虑写一个 Dijkstra，来更新 $f_{i,0/1}$，但是堆优化 Dijkstra 利用的是优先队列内部的递增性质，我们这里，一边是最大值，一边是最小值，怎么办呢？

解决方法是，我们跑 $f_{i,0}$ 的结果显然是没有问题的，找机会更新 $f_{i,1}$，那么我们可以用类似拓扑的方法，只有所有的 $j(i\to j)$ 更新好了我们才把 $f_{i,1}$ 放入优先队列。

都解释到这里了，正确性显然。

时间复杂度为 $\mathcal O((n+m)\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
const LL inf=1e15;
LL n,m,s,du[N][2],f[N][2],vis[N][2];

struct node
{
	LL x,t,val;
	bool operator<(const node &b)const
	{
		return val>b.val;
	}
};
struct edge
{
	LL to,w;
};
vector<edge>v[N];
priority_queue<node>p;
int main()
{
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++)
	{
		LL x,y,z;
		cin>>x>>y>>z;
		du[x][0]++,du[x][1]++;
		v[y].push_back({x,z});
	}
	for(int i=1;i<=n;i++)
	{
		f[i][0]=inf;
	}
	for(int i=1;i<=n;i++)
	{
		if(!du[i][0])
		{
			f[i][0]=f[i][1]=0;
			p.push({i,0,f[i][0]});
			p.push({i,1,f[i][1]});
		}
	}
	while(!p.empty())
	{
		node t=p.top();
		p.pop();
		if(vis[t.x][t.t])continue;
		vis[t.x][t.t]=1;
		for(edge i:v[t.x])
		{
			du[i.to][1-t.t]--;
			if(t.t==1)f[i.to][0]=min(f[i.to][0],t.val+i.w);
			else f[i.to][1]=max(f[i.to][1],t.val+i.w);
			if(du[i.to][1-t.t]==0)p.push({i.to,1-t.t,f[i.to][1-t.t]});
			else if(t.t==1)p.push({i.to,0,f[i.to][0]});
		}
	}
	if(f[s][0]==inf)puts("INFINITY");
	else printf("%lld",f[s][0]);
}
``

---

## 作者：iCostalymh (赞：1)

[题目链接](https://atcoder.jp/contests/abc261/tasks/abc261_h)

[我的博客](https://www.cnblogs.com/Chronologika/p/17632019.html)

前言：震惊！这个题竟然被神犇 szs 归进了博弈论里！我真的没看出来除了题面还有哪里像博弈论（也许是因为我菜）。

转移方式很显然，按照题面说的做就行了。那么正解也就呼之欲出了。

但是我知道大家都会正解，就是魔改的堆优化 Dijkstra，参考上一篇题解即可。所以我想说的是一种歪解，以及它是歪解的原因。

这个歪解是记搜。那么为什么记搜就是歪解呢？魔改的堆优化 Dijkstra 又是干什么的呢？

我的歪解[提交记录](https://atcoder.jp/contests/abc261/submissions/44604800)。在比赛的时候用这个歪解可以 AC，但是新加了 hack 数据以后就不行了。

我们回头看一下 Takahashi 和 Aoki 的转移，前者是尽可能最小，后者是尽可能最大，前者尽可能不走环，后者尽可能走环。我们举一些例子可以发现 Takahashi 的转移会受到出边的顺序的影响，而 Aoki 不会。

在 dfs 的时候，因为我们要对环进行处理，所以我们不能边递归边赋值。但是这会导致我们接下来递归到某一个节点，这个节点的后继节点本来是最优策略，但是因为它先被递归到了，没办法继续往下走了。所以枚举出边的顺序不同会导致每局所有可能选择的策略不同，也就是我们上一段所说的 Takahashi 的转移会受到出边的顺序的影响，而 Aoki 不会。

这里奉上一个相关的样例，如果有不懂的可以用这个来手模一下：
```
Input:
6 10 3
2 4 5
2 3 2
3 2 3
4 3 8
1 2 4
2 6 7
2 1 1
1 6 3
3 1 6
5 3 6

Output:
17
```
那么魔改的堆优化 Dijkstra 就是来保证枚举点的顺序正确的。正确性就不证明了。

---

## 作者：Unnamed114514 (赞：0)

这种非传统的博弈论一般要么是 dp 要么就是直接贪，本题是 dp。

先建反图，便于 dp 时转移。

定义 $f_{u,0/1}$ 表示当前在 $u$ 上，是先手/后手操作的最优得分，答案显然就是 $f_{s,0}$。

转移是朴素的，问题在于有环的情况不一定无解，有解的时候怎么转移。

显然没有一个点入度为 $0$ 的时候答案是 $\infty$，因为没有终止状态。 

我们把从这里走出去，双方按照最优策略会走到环的状态定为 `-1`（当然定为 $\infty$ 会更好，做的时候脑抽了）。

- 对于 $f_{u,0}$ 的转移，他显然不会走到环里面，所以只要有一个点 $v$ 保证 $f_{v,1}\ne -1$ 能转移到他就行了。

- 对于 $f_{u,1}$ 的转移，他能走到环就一定往环里走，所以只有所有能转移到它的节点 $v$ 都满足 $f_{v,0}\ne -1$ 才能转移，这一部分可以用类似拓扑排序的方法转移。

用优先队列广搜实现即可。

---

