# [ABC224H] Security Camera 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc224/tasks/abc224_h

左側に $ L $ 個、右側に $ R $ 個の頂点を有する二部グラフがあります。  
 高橋君は、この二部グラフの各頂点にカメラを設置することにしました。  
 カメラは $ 1 $ 個設置するごとに以下に示す金額のコストが掛かります。

- $ i $ $ (1\ \le\ i\ \le\ L) $ 番目の左側頂点に $ 1 $ 個のカメラを設置するのに $ A_i $ 円
- $ j $ $ (1\ \le\ j\ \le\ R) $ 番目の右側頂点に $ 1 $ 個のカメラを設置するのに $ B_j $ 円

また、 $ 1 $ つの頂点に複数個のカメラを設置してもよいです。

高橋君が以下の条件を満たすようにカメラを設置する時、必要な最小金額を求めてください。

- $ 1\ \le\ i\ \le\ L,\ 1\ \le\ j\ \le\ R $ を満たす全ての整数組 $ (i,j) $ について、 $ i $ 番目の左側頂点と $ j $ 番目の右側頂点にカメラが合計で $ C_{i,j} $ 個以上設置されている。

## 说明/提示

### 制約

- 入力は全て整数である
- $ 1\ \le\ L,R\ \le\ 100 $
- $ 1\ \le\ A_i,B_i\ \le\ 10 $
- $ 0\ \le\ C_{i,j}\ \le\ 100 $

### Sample Explanation 1

以下のようにカメラを設置することで金額 $ 37 $ 円を達成することができ、これが最小です。 - $ 1 $ 番目の左側頂点にカメラを $ 2 $ つ設置する。 - $ 2 $ 番目の左側頂点にカメラを $ 3 $ つ設置する。 - $ 3 $ 番目の左側頂点にカメラを $ 2 $ つ設置する。 - $ 1 $ 番目の右側頂点にカメラを $ 1 $ つ設置する。 - $ 3 $ 番目の右側頂点にカメラを $ 1 $ つ設置する。

### Sample Explanation 2

$ 1 $ つもカメラを設置する必要がないケースもあります。

## 样例 #1

### 输入

```
3 4
4 3 6
5 2 3 4
1 2 3 2
2 1 2 3
3 2 1 2```

### 输出

```
37```

## 样例 #2

### 输入

```
1 1
10
10
0```

### 输出

```
0```

## 样例 #3

### 输入

```
5 6
3 2 6 7 5
4 9 8 6 2 3
2 0 2 1 1 0
2 3 2 1 0 0
2 2 4 0 2 2
4 1 0 3 0 2
1 0 0 2 2 5```

### 输出

```
79```

# 题解

## 作者：Arghariza (赞：4)

直接糊一手线性规划对偶板板。

$$\max c^Tx:A^Tx\le b,x\ge 0\Leftrightarrow \min b^Ty:Ay\ge c,y\ge 0$$

其中 $A$ 为 $m\times n$ 的矩阵，$x,c$ 为长度为 $m$ 的列向量，$y,b$ 为长度为 $n$ 的列向量。$n$ 为点数，$m$ 为限制数。

不难看出：

$$b_i=\begin{cases}A_i&\quad i\le L\\B_{i-L}&\quad i>L\end{cases}$$

$$A_{i,j}=\begin{cases}1&\quad j=u_i/j=L+v_i\\0&\quad \text{otherwise}\end{cases}$$

$$c_i=C_i$$

然后对偶一下就变成了：

$$A^T_{i,j}=\begin{cases}[u_j=i]&\quad i\le L\\ [v_j=i-L]&\quad i>L\end{cases}$$

$$(A^Tx)_i=\begin{cases}\sum\limits_{k=1}^m[u_k=i]x_k&\quad i\le L\\\sum\limits_{k=1}^m[v_k=i-L]x_k&\quad i>L\end{cases}$$

然后就直接费用流建图：

- $S\to x(1\le x\le L)$，流量为 $A_i$，费用为 $0$。
- $x(L<x\le R)\to T$，流量为 $B_i$，费用为 $0$。
- $u_i\to v_i+L$，流量为 $∞$，费用为 $C_i$。

求出最大费用就是答案。不难发现费用最大时必定流满，所以最大费用最大流就是答案。

```cpp
// Problem: [ABC224H] Security Camera 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc224_h
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

struct Flow {
	const int inf = 0x3f3f3f3f;
	int n, s, t, tot;
	struct edge { int to, nxt, w, c; };
	vector<int> hd, cr, d, vs;
	vector<edge> e;
	Flow (int _n) : n(_n), tot(-1) { hd.resize(n + 5, -1), d.resize(n + 5), vs.resize(n + 5), e.clear(); }
	void add_edge(int u, int v, int w, int c) { e.pb((edge) { v, hd[u], w, c }), hd[u] = ++tot; }
	void add_flow(int u, int v, int w, int c) { add_edge(u, v, w, c), add_edge(v, u, 0, -c); }
	bool spfa() {
		fill(d.begin(), d.end(), inf);
		queue<int> q; q.push(s), d[s] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop(), vs[u] = 0;
			for (int i = hd[u]; ~i; i = e[i].nxt) {
				int v = e[i].to;
				if (!e[i].w) continue;
				if (d[v] > d[u] + e[i].c) {
					d[v] = d[u] + e[i].c;
					if (!vs[v]) q.push(v), vs[v] = 1;
				}
			}
		}
		return d[t] != inf;
	}
	int dfs(int u, int in) {
		if (u == t) return in;
		vs[u] = 1;
		int out = 0;
		for (int &i = cr[u]; ~i; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].w && !vs[v] && d[v] == d[u] + e[i].c) {
				int res = dfs(v, min(in, e[i].w));
				e[i].w -= res, e[i ^ 1].w += res;
				in -= res, out += res;
			}
			if (!in) break;
		}
		vs[u] = 0;
		return out;
	}
	pi dinic() {
		int mc = 0, mf = 0;
		while (spfa()) {
			cr = hd;
			int res = dfs(s, inf);
			mc += res * d[t], mf += res;
		}
		return mp(mf, mc);
	}
};

const int N = 150;
int n, m, k, a[N], b[N];

void solve() {
	cin >> n >> m; Flow G(n + m + 2); G.s = n + m + 1, G.t = n + m + 2;
	for (int i = 1; i <= n; i++) cin >> a[i], G.add_flow(G.s, i, a[i], 0);
	for (int i = 1; i <= m; i++) cin >> b[i], G.add_flow(i + n, G.t, b[i], 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1, x; j <= m; j++)
			cin >> x, G.add_flow(i, j + n, G.inf, -x);
	cout << -G.dinic().se << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：EuphoricStar (赞：4)

直接糊一手线性规划对偶板板。

要求：

$$\min \sum A_i l_i + \sum B_i r_i$$

$$\forall i, j, l_i + r_j \ge C_{i, j}$$

$$l_i, r_i \ge 0$$

$$l_i, r_i \in \mathbb{Z}$$

可以证明 $l_i, r_i$ 为整数的限制可以去掉，因为取到最优解时 $l_i, r_i$ 一定顶着整数。

对偶相当于变量和限制互换，$\min, \max$ 互换，不等式符号改变，变成：

$$\max \sum w_{i, j} C_{i, j}$$

$$\sum\limits_j w_{i, j} \le A_i$$

$$\sum\limits_i w_{i, j} \le B_j$$

我去这不是费用流板板吗。$w_{i, j}$ 相当于 $i \to j'$ 的流量，$C_{i, j}$ 相当于这条边的费用，$\le A_i$ 和 $\le B_j$ 的限制相当于和源点与汇点的边的容量。那么：

- 连边 $S \to i$，容量为 $A_i$，费用为 $0$；
- 连边 $i \to j'$，容量为 $+\infty$，费用为 $C_{i, j}$；
- 连边 $j \to T$，容量为 $B_i$，费用为 $0$。

跑一遍最大费用最大流即可。

最大费用最大流可以把费用全部取反跑最小费用最大流，最后把费用再取反。

[code](https://atcoder.jp/contests/abc224/submissions/47183719)

---

## 作者：Graphcity (赞：4)

线性规划对偶热身题。

先写出目标函数和约束条件：

$$
\begin{aligned}
\min \sum_iA_il_i+\sum_iB_ir_i\\
\forall x,y,\  l_x+r_y\ge C_{x,y}
\end{aligned}
$$

转化成标准形式：

$$
\begin{aligned}
\max \sum_i(-A_i)l_i+\sum_i(-B_i)r_i\\
\forall x,y,\  -l_x-r_y\le -C_{x,y}
\end{aligned}
$$

对偶，设 $w_{x,y}$ 为 $C_{x,y}$ 所在限制的对偶变量：

$$
\begin{aligned}
\min \sum_{x,y}(-C_{x,y})w_{x,y}\\
\sum_i-w_{x,i}\ge -A_x\\
\sum_i-w_{i,y}\ge -B_y
\end{aligned}
$$

转化一下：

$$
\begin{aligned}
\min \sum_{x,y}(-C_{x,y})w_{x,y}\\
\sum_i w_{x,i}\le A_x\\
\sum_i w_{i,y}\le B_y
\end{aligned}
$$

这个容易用费用流表示：对于左部点 $x$，连接 $s\to x$，流量为 $A_x$，费用为 $0$ 的边；对于右部点 $y$，连接 $y'\to t$，流量为 $B_y$，费用为 $0$ 的边；连接 $x\to y'$，流量为 $\infty$，费用为 $-C_{x,y}$ 的边。

答案即为最小费用的相反数。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e6,Maxm=5e6;
const int inf=1e9;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
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

struct Node{int to,nxt,w,cst;} Edge[Maxm*2+5];
int tot=1,Head[Maxn+5],cur[Maxn+5];
inline void Addedge(int x,int y,int z,int w)
{
    Edge[++tot]=(Node){y,Head[x],z,w},Head[x]=tot;
    Edge[++tot]=(Node){x,Head[y],0,-w},Head[y]=tot;
}

int n,m,s,t,maxf,minc;
int dis[Maxn+5],vis[Maxn+5];
queue<int> q;

inline int bfs()
{
    For(i,1,t) dis[i]=inf,vis[i]=0,cur[i]=Head[i];
    dis[s]=0,vis[s]=1,q.push(s);
    while(!q.empty())
    {
        int x=q.front(); q.pop(),vis[x]=0;
        for(int i=Head[x];i;i=Edge[i].nxt)
        {
            int y=Edge[i].to;
            if(Edge[i].w && dis[x]+Edge[i].cst<dis[y])
            {
                dis[y]=dis[x]+Edge[i].cst;
                if(!vis[y]) vis[y]=1,q.push(y);
            }
        }
    }
    return (dis[t]<inf);
}
inline int dfs(int x,int flow)
{
    if(vis[x]) return 0;
    if(x==t || !flow) {maxf+=flow; return flow;}
    int used=0,res=0; vis[x]=1;
    for(int i=cur[x];i && used<flow;i=Edge[i].nxt)
    {
        int y=Edge[i].to; cur[x]=i;
        if(Edge[i].w && dis[y]==dis[x]+Edge[i].cst)
            if(res=dfs(y,min(Edge[i].w,flow-used)))
            {
                used+=res,Edge[i].w-=res,Edge[i^1].w+=res;
                minc+=res*Edge[i].cst;
            }
    }
    vis[x]=0; return used;
}

int main()
{
    n=read(),m=read(),s=n+m+1,t=n+m+2;
    For(i,1,n) Addedge(s,i,read(),0);
    For(i,1,m) Addedge(i+n,t,read(),0);
    For(i,1,n) For(j,1,m) Addedge(i,j+n,inf,-read());
    while(bfs()) dfs(s,inf);
    printf("%d\n",-minc);
    return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

众所周知 CTT 之前不能考单纯性算法，但没说不能考线性规划的对偶。

容易发现每个数最多为 $100$，所以显然可以拆点之后最小割建模，复杂度堪忧。

写成线性规划的形式：

给定变量 $x_{1,2,\cdots,L}$ 和 $y_{1,2,\cdots,R}$ 满足 $x_i,y_i \ge 0$，有限制 $x_{u_i} + y_{v_i} \ge w_i$，最小化 $\sum_{i=1}^L A_ix_i + \sum_{i=1}^R B_iy_i$。

显然要进行对偶。不是有 $m$ 条限制吗，我们给它写成这样：

$$
\text{minimize}_{x,y \ge 0} \text{maximize}_{\lambda \ge 0} \sum_{i=1}^L A_ix_i + \sum_{i=1}^R B_iy_i + \sum_{i=1}^m (w_i - x_{u_i} - y_{v_i})\lambda_i
$$

如果有 $w_i \ge x_{u_i} + y_{v_i}$，就可以通过调整 $\lambda$ 使得右边这个式子无穷大，自然不会最终有用。

通过对偶原则，把最大化和最小化颠倒顺序，得到：

$$
\text{maximize}_{\lambda \ge 0}
\text{minimize}_{x,y \ge 0}  \sum_{i=1}^L A_ix_i + \sum_{i=1}^R B_iy_i + \sum_{i=1}^m (w_i - x_{u_i} - y_{v_i})\lambda_i
$$

这时候把 $\lambda$ 当做决策变量，$x_i$、$y_i$ 当做约束条件，即：

$$
A_i \ge \sum_{e=(i,j)} \lambda_e
$$

以及

$$
B_i \ge \sum_{e=(j,i)} \lambda_e
$$

并且最大化 $\sum_{i=1}^m w_i \lambda_i$。

这个东西就是费用流模板了。

这是一个最大费用最大流，不好。但是注意到总的最大流是确定的（贪心保证），所以可以用一个极大的数 $N$ 减去边权，得到新的费用，转化为最小费用最大流问题。

如果你在费用流里面套一个原始对偶，可以做到 $O(n^3 + n^2 A \log n)$。但是我懒。

这是代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXV=200+10,MAXE=100000+10;
int lim,ll,rr,m,s,t,mc,mf,tmp,tot=1,ev,deg[MAXV],hd[MAXV],cur[MAXV],dis[MAXV],vis[MAXV];
struct Edge {int to,nxt,f,c;}edge[MAXE];
void add_edge(int u,int v,int f,int c) {return edge[++tot]={v,hd[u],f,c},hd[u]=tot,edge[++tot]={u,hd[v],0,-c},hd[v]=tot,void();}
int spfa(int s,int t) {
	ffor(i,s,t) dis[i]=0x3f3f3f3f,vis[i]=0,cur[i]=hd[i];
	queue<int> q;
	dis[s]=0,q.push(s);
	while(!q.empty()) {
		int u=q.front();
		vis[u]=0,q.pop();
		for(int i=hd[u];i;i=edge[i].nxt) {
			int to=edge[i].to,f=edge[i].f,c=edge[i].c;
			if(!f||dis[to]<=dis[u]+c) continue ;
			dis[to]=dis[u]+c;
			if(!vis[to]) vis[to]=1,q.push(to);
		}
	}
	return dis[t]!=0x3f3f3f3f;
}
int dinic(int u,int mx,int s,int t) {
	if(u==t) return mx;
	int res=0;
	vis[u]=1;
	for(int i=cur[u];i;i=edge[i].nxt) {
		int to=edge[i].to,f=edge[i].f,c=edge[i].c; cur[u]=i;
		if(dis[to]!=dis[u]+c||vis[to]||!f) continue ;
		int tmp=dinic(to,min(mx,f),s,t);
		if(tmp) {
			res+=tmp,mx-=tmp,mc+=c*tmp,edge[i].f-=tmp,edge[i^1].f+=tmp;
			if(!mx) break;
		}
		else dis[to]=0x3f3f3f3f;
	}
	return vis[u]=0,res;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>ll>>rr;
	s=0,t=ll+rr+1;
	ffor(i,1,ll) cin>>lim,add_edge(s,i,lim,0);
	ffor(i,1,rr) cin>>lim,add_edge(i+ll,t,lim,0);
	ffor(i,1,ll) ffor(j,1,rr) cin>>lim,add_edge(i,j+ll,10000000,100-lim);
	while(spfa(s,t)) while(lim=dinic(s,10000000,s,t)) mf+=lim;
	cout<<100*mf-mc;
	return 0;
}
```

---

## 作者：Locix_Elaina_Celome (赞：0)

不会线性规划，我们就充分发挥人类智慧，使用最小割解决。

先 $S$ 连向左部点边权 $+\infty$，右部点连边 $T$ 边权 $+\infty$。

对于左部每一个点 $i$，拉出一条链，边权为 $100a_i,99a_i,98a_i,\dots 2a_i,a_i$。把这些点设为 $f_{i,100},f_{i,99},\dots ,f_{i,1}$，这些点就表示 $i$ 这里放多少个摄像头。

右部也一样。点设为 $g_{i,100},g_{i,99},\dots ,g_{i,1}$。

然后对于一个限制，点 $i$ 和 $j$ 总共要有 $x$ 个摄像头。我们枚举一个 $k\in[0,x]$ 连边 $(f_{i,k},g_{j,x-k+1},+\infty)$。

然后跑最小割就好了。

但是可能会发现 TLE 了两个点。只需要动用人类智慧卡一卡就过去了，比如到 uoj 的网络流模板题复制一个跑得快的。然后就可以以比正解慢一百倍的速度通过此题。

代码把网络流部分扣了。

```cpp

int n,m;
int cnt;
int S,T;
int a[N],b[N];
int id[M][M];
int cc[M][M];
int ma[M],mb[M];
int main(){
	read(n);
	read(m);
	cnt=n+m;
	S=++cnt;
	T=++cnt;
	for(int i=1;i<=n;i++)add(S,i,INF);
	for(int i=1;i<=m;i++)add(i+n,T,INF);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=m;i++)read(b[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			read(cc[i][j]),ma[i]=Max(ma[i],cc[i][j]),mb[j]=Max(mb[j],cc[i][j]);
	for(int i=1;i<=n;i++){
		id[i][ma[i]]=++cnt;
		add(i,id[i][ma[i]],ma[i]*a[i]);
		for(int j=ma[i]-1;j>0;j--){
			id[i][j]=++cnt;
			add(id[i][j+1],id[i][j],a[i]*j);
		}
	}
	for(int i=1;i<=m;i++){
		id[i+n][mb[i]]=++cnt;
		add(id[i+n][mb[i]],i+n,mb[i]*b[i]);
		for(int j=mb[i]-1;j>0;j--){
			id[i+n][j]=++cnt;
			add(id[i+n][j],id[i+n][j+1],b[i]*j);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=cc[i][j];
			for(int k=x;k;k--)add(id[i][k],id[j+n][x-k+1],INF);
		}
	}
	write(solve(g,S-1,T-1));
	return 0;
}

```

---

