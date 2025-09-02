# [USACO22DEC] Breakdown P

## 题目描述

Farmer John 的农场可以用一个带权有向图表示，道路（边）连接不同的结点，每条边的权值是通过道路所需的时间。每天，Bessie 喜欢从牛棚（位于结点 $1$）经过恰好 $K$ 条道路前往草地（位于结点 $N$），并希望在此限制下尽快到达草地。然而，在某些时候，道路停止维护，一条一条地开始破损，变得无法通行。帮助 Bessie 求出每一时刻从牛棚到草地的最短路径！

形式化地说，我们从一个 $N$ 个结点（$1 \le N \le 300$）和 $N^2$ 条边的带权有向完全图开始：对于 $1 \le i,j \le N$ 的每一对 $(i,j)$ 存在一条边（注意存在 $N$ 个自环）。每次移除一条边后，输出从 $1$ 到 $N$ 的所有路径中经过恰好 $K$ 条边（不一定各不相同）的路径的最小权值（$2 \le K \le 8$）。注意在第 $i$ 次移除后，该图还剩下 $N^2-i$ 条边。

路径的权值定义为路径上所有边的权值之和。注意一条路径可以包含同一条边多次或同一个结点多次，包括结点 $1$
和 $N$。

## 说明/提示

### 样例 1 解释

第一次移除后，最短的经过 $4$ 条边的路径为：

$$1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 3$$

第二次移除后，最短的经过 $4$ 条边的路径为：

$$1 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 3$$

第三次移除后，最短的经过 $4$ 条边的路径为：

$$1 \rightarrow 3 \rightarrow 3 \rightarrow 3 \rightarrow 3$$

六次移除后，不再存在经过 $4$ 条边的路径。 

### 测试点性质

 - 对于 $2 \le T \le 14$，测试点 $T$ 满足 $K=\lfloor \dfrac{T+3}{2} \rfloor$。 

## 样例 #1

### 输入

```
3 4
10 4 4
9 5 3
2 1 6
3 1
2 3
2 1
3 2
2 2
1 3
3 3
1 1
1 2```

### 输出

```
11
18
22
22
22
-1
-1
-1
-1```

# 题解

## 作者：Alex_Wei (赞：13)

[P8906 [USACO22DEC] Breakdown P](https://www.luogu.com.cn/problem/P8906)

首先折半搜，将问题形式转化为维护 $1$ 到每个点经过 $k$ 条边的最短路 $h_i$，其中 $k\leq 4$。我们只考虑 $k = 4$。

删边倒过来变成加边。

考虑时刻维护任意两点间经过两条边的最短路 $f_{i, j}$。加边时只会对 $i = u$ 或 $j = v$ 的 $f_{i, j}$ 产生修改，共 $\mathcal{O}(n)$ 种情况。对于 $h_i$，枚举中转点 $j$ ，计算 $f_{1, j} + f_{j, i}$。注意到当且仅当 $i$ 或 $j$ 等于 $u$ 或 $v$ 时才会因 $f$ 的修改而对 $h$ 产生贡献，因此对于 $i\neq u, v$，只需用 $f_{1, u / v} + f_{u / v, i}$ 更新，对于 $i = u$ 或 $v$ 用所有 $f_{1, j} + f_{j, i}$ 更新。

单次加边的时间复杂度均摊 $\mathcal{O}(n)$，注意特判 $u = 1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 300 + 5;
constexpr int M = 1e5 + 5;
int n, m, k;
int ans[M], u[M], v[M], e[N][N];
void cmin(int &x, int y) {
  x = x < y ? x : y;
}
struct solver {
  int st, k;
  int e[N][N], f[N][N], h[N];
  void init(int _k, int _st) {
    k = _k, st = _st;
    memset(e, 0x3f, sizeof(e));
    memset(f, 0x3f, sizeof(f));
    memset(h, 0x3f, sizeof(h));
    if(!k) {
      h[st] = 0;
    }
  }
  void add(int u, int v, int w) {
    e[u][v] = w;
    if(!k) return;
    if(k == 1) {
      if(u == st) {
        h[v] = w;
      }
      return;
    }
    for(int i = 1; i <= n; i++) {
      cmin(f[i][v], e[i][u] + w);
      cmin(f[u][i], w + e[v][i]);
    }
    if(k == 2) {
      for(int i = 1; i <= n; i++) {
        cmin(h[i], f[st][i]);
      }
    }
    auto p = k == 3 ? e : f;
    if(k > 2) {
      if(u == st) {
        for(int i = 1; i <= n; i++) {
          for(int j = 1; j <= n; j++) {
            cmin(h[j], f[st][i] + p[i][j]);
          }
        }
      }
      else {
        for(int i = 1; i <= n; i++) {
          cmin(h[i], f[st][v] + p[v][i]);
          cmin(h[i], f[st][u] + p[u][i]);
          cmin(h[u], f[st][i] + p[i][u]);
          cmin(h[v], f[st][i] + p[i][v]);
        }
      }
    }
  }
} _1, _n;
int main() {
  #ifdef ALEX_WEI
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k, m = n * n;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      cin >> e[i][j];
    }
  }
  for(int i = 1; i <= m; i++) {
    cin >> u[i] >> v[i];
  }
  int L = k >> 1, R = k - L;
  _1.init(L, 1), _n.init(R, n);
  for(int i = m; i; i--) {
    ans[i] = 0x3f3f3f3f;
    for(int p = 1; p <= n; p++) {
      cmin(ans[i], _1.h[p] + _n.h[p]);
    }
    _1.add(u[i], v[i], e[u[i]][v[i]]);
    _n.add(v[i], u[i], e[u[i]][v[i]]);
  }
  for(int i = 1; i <= m; i++) {
    if(ans[i] > 1e9) cout << "-1\n";
    else cout << ans[i] << "\n";
  }
  return 0;
}
```

---

## 作者：EXODUS (赞：10)


# Part 1：前言
神奇的折半，BenQ 的神仙题/bx（虽然是蛮套路的）。
# Part 2：正文

看见删边直接时间倒流，下面的讨论全部是在加边意义下的。

首先看到 $k=8$ 就知道这个题的 $k$ 可能是在指数位置了。对于这种特定步数问题，不是邻接矩阵快速幂就是对于经过多长路径的分类维护，由于这里 $k$ 不大，故考虑第二种情况。

不妨折半，设 $f(k,i,0/1)$ 表示从 $1/i$ 经过 $k$ 条道路到达 $i/n$ 的最短路径长度，答案为
$$
\min_{p+q=k}f(p,i,0)+f(p,i,1)
$$
这个东西似乎没法做。对第 $i$ 层单次进行转移的复杂度是 $O(n^{k-2})$ 的，而一共转移 $n^2$ 次，总复杂度达到了 $O(n^k)$。

这里似乎要提及一下转移，我们只讨论从 $1$ 到 $i$ 的转移，$i$ 到 $n$ 同理。一个不精细的单次 $O(n^k)$ 的实现枚举 $1$ 经过的 $k$ 个点并暴力对中点取最小值，但是我们仔细想想会发现当前这条加的边如果对答案有贡献则其一定存在于更新的路径中，也就是说路径上必定有两个相邻的点是 $u,v$，这样我们就能少枚举两个点，复杂度降低为 $O(n^{k-2})$。

当然上述是存在一个 bug 的，即当 $(u,v)$ 是第一条边时，由于此时第一个点已经确定，所以只能多确定一个点。我们不难发现，能形成这样转移的边最多有 $n$ 条（$u=1$），故总复杂度仍是 $O(n^k)$ 的。

然后我就止步于此了/cf。

能不能更快一点？我们不妨把此时单次维护的复杂度列出来

$$
\begin{cases}
k=1&O(1)\\
k=2&O(1)\\
k=3&O(n)\\
k=4&O(n^2)\\
\end{cases}
$$

注意到瓶颈是 $k=4$，我们不妨对 $k=2$ 和 $k=4$ 做一个复杂度均摊，我们不止维护当 $k=2$ 时 $1/i$ 到 $i/n$ 经过两条边的最短路径，转而维护所有点对之间经过两条边的最短路径，此时 $k=2$ 的复杂度变为 $O(n)$，而无论一条边是一条长度为四的路径的第几条边，一定存在一条该路径的子路径，满足其不经过该边的前提下长度至少为二，也就是我们一定能够少枚举一个点，故时间复杂度将为 $O(n)$。

总时间复杂度因此是 $O(n^3)$

# Part 3：代码
代码感觉还是比较好懂的
```cpp
int Datas=0,T=1;
const int N=307;
int n,K;
vector<np>delt;
ll g[N][N];
ll ans[N*N];
ll dis1[N][N],dis2[N][N],dis3[N][2],dis4[N][2];

void Main(){
	n=read(),K=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			g[i][j]=read();
	for(int i=1;i<=n*n;i++){
		int u=read(),v=read();
		delt.eb(mp(u,v));
	}
	memset(dis1,0x3f,sizeof(dis1));
	memset(dis2,0x3f,sizeof(dis2));
	memset(dis3,0x3f,sizeof(dis3));
	memset(dis4,0x3f,sizeof(dis4));
	memset(ans,0x3f,sizeof(ans));
	for(int _=n*n;_>=1;_--){
		if(K==2)for(int i=1;i<=n;i++)ans[_]=min(ans[_],dis1[1][i]+dis1[i][n]);
		if(K==3)for(int i=1;i<=n;i++)ans[_]=min(ans[_],dis2[1][i]+dis1[i][n]);
		if(K==4)for(int i=1;i<=n;i++)ans[_]=min(ans[_],dis2[1][i]+dis2[i][n]);
		if(K==5)for(int i=1;i<=n;i++)ans[_]=min(ans[_],dis2[1][i]+dis3[i][1]);
		if(K==6)for(int i=1;i<=n;i++)ans[_]=min(ans[_],dis3[i][0]+dis3[i][1]);
		if(K==7)for(int i=1;i<=n;i++)ans[_]=min(ans[_],dis4[i][0]+dis3[i][1]);
		if(K==8)for(int i=1;i<=n;i++)ans[_]=min(ans[_],dis4[i][0]+dis4[i][1]);
		if(ans[0]==ans[_])ans[_]=-1;
		int u=delt.back().fi,v=delt.back().se;
		delt.ppb();int w=g[u][v];
		dis1[u][v]=w;
		for(int i=1;i<=n;i++){
			dis2[u][i]=min(dis2[u][i],w+dis1[v][i]);
			dis2[i][v]=min(dis2[i][v],dis1[i][u]+w);
		}
		if(u==1)for(int i=1;i<=n;i++)dis3[i][0]=min(dis3[i][0],w+dis2[v][i]);
		if(v==n)for(int i=1;i<=n;i++)dis3[i][1]=min(dis3[i][1],dis2[i][u]+w);
		for(int i=1;i<=n;i++){
			dis3[i][0]=min(dis3[i][0],dis1[1][u]+w+dis1[v][i]);
			dis3[i][1]=min(dis3[i][1],dis1[i][u]+w+dis1[v][n]);
		}
		dis3[v][0]=min(dis3[v][0],dis2[1][u]+w);
		dis3[u][1]=min(dis3[u][1],w+dis2[v][n]);
		if(u==1)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
			dis4[i][0]=min(dis4[i][0],w+dis1[v][j]+dis2[j][i]);
		if(v==n)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
			dis4[i][1]=min(dis4[i][1],dis2[i][j]+dis1[j][u]+w);
		for(int i=1;i<=n;i++){
			dis4[i][0]=min(dis4[i][0],dis1[1][u]+w+dis2[v][i]);
			dis4[i][0]=min(dis4[i][0],dis2[1][u]+w+dis1[v][i]);
			dis4[i][1]=min(dis4[i][1],dis1[i][u]+w+dis2[v][n]);
			dis4[i][1]=min(dis4[i][1],dis2[i][u]+w+dis1[v][n]);
		}
		dis4[v][0]=min(dis4[v][0],dis3[u][0]+w);
		dis4[u][1]=min(dis4[u][1],w+dis3[v][1]);
	}
	for(int i=1;i<=n*n;i++)printf("%lld\n",ans[i]);
	return;
}
```

---

## 作者：pigstd (赞：8)

好像感觉我的做法和其他人都不一样，写一下。

----

每条边有个被删除的时间，那么一条路径只要考虑这个时间最小的边。

考虑 meet-in-middle，那么转化成 $k=4$，然后从 $1$ 到达任意一个点 $x$，然后最小时间为 $t$ 的答案（到 $n$ 的同理，这样刚好 $\mathcal{O}(n^3)$ 个要求的东西）。

然后再枚举一遍中间的这个点 $y$，然后变成 $1\to y,y\to x$ 并且各经过两条边的情况。这个时候 $1\to y$ 只有 $\mathcal{O}(n)$ 种方案，$y \to x$ 也只有 $\mathcal{O}(n)$ 种方案。而且我们只注意最小值，最小值也只有 $\mathcal{O}(n)$ 种，那么把这 $\mathcal{O}(n)$ 种方案全部预处理出来然后排序，双指针即可。

规避排序的 $\log$ 可以基排，或者预处理一些东西，反正都是很平凡的东西。总的时间复杂度 $\mathcal{O}(n^3)$。不过写出来常数很大。[代码实现](https://www.luogu.com.cn/paste/vqkb6n7l)。

---

## 作者：EnofTaiPeople (赞：8)

其实从 $k$ 极小就能看出是分层图，为了优化常数，我采用了 $\text{meet in the middle}$ 的优化，即维护起点到任意点经过 $\lfloor\dfrac k 2\rfloor$ 和任意点到终点经过 $\lceil\dfrac k 2\rceil$ 条边的最短路，对于打到 $\text{P}$ 组的人来说理解这应当不难。

不过题目中要求的是删边，所以这里需要运用经典的化删为加套路，应当学过并查集应用的人都会，就是将边反过来，不是反向，是将所有边之间的顺序反过来。

考虑如何添加一条边，在这里只需要依次扫过分层图的每一层，如果某一个点在之前已经被松驰过，就将它的所有出边都松弛一遍。

这样最坏复杂度是 $O(n^4k)$ 的，但是我不会卡，出题人也没有卡，就过了：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
using ll=long long;
using ul=unsigned long long;
int n,k,_w[N][N];
int _X[N*N],_Y[N*N];
ll w[N][N],ans[N*N];
struct spfa{
	ll d[N][5];
	int vs[N][5],st,k;
	void init(int x,int p){
		memset(d,0x1f,sizeof(d));
		d[x][0]=0,st=x,k=p;
	}
	void upd(int x){
		memset(vs,0,sizeof(vs));
		int i,y;
		for(i=0;i<k;++i)vs[x][i]=1;
		for(i=0;i<k;++i)
			for(x=1;x<=n;++x)
				if(vs[x][i])
					for(y=1;y<=n;++y)
						if(d[y][i+1]>d[x][i]+w[x][y]){
							vs[y][i+1]=1;
							d[y][i+1]=d[x][i]+w[x][y];
						}
	}
}p1;
struct spfa_{
	ll d[N][5];
	int vs[N][5],st,k;
	void init(int x,int p){
		memset(d,0x1f,sizeof(d));
		d[x][0]=0,st=x,k=p;
	}
	void upd(int x){
		memset(vs,0,sizeof(vs));
		int i,y;
		for(i=0;i<k;++i)vs[x][i]=1;
		for(i=0;i<k;++i)
			for(x=1;x<=n;++x)
				if(vs[x][i])
					for(y=1;y<=n;++y)
						if(d[y][i+1]>d[x][i]+w[y][x]){
							vs[y][i+1]=1;
							d[y][i+1]=d[x][i]+w[y][x];
						}
	}
}p2;
int main(){
#ifdef MYdef
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	int i,j,k,l,r,x,y,X,Y;
	cin>>n>>k;
	for(x=1;x<=n;++x)
		for(y=1;y<=n;++y)
			cin>>_w[x][y],w[x][y]=1e18;
	for(i=1;i<=n*n;++i)cin>>_X[i]>>_Y[i];
	p1.init(1,k>>1),p2.init(n,k+1>>1);
	for(i=n*n;i;--i){
		ans[i]=1e15;
		for(x=1;x<=n;++x)
			ans[i]=min(ans[i],p1.d[x][k>>1]+p2.d[x][k+1>>1]);
		if(ans[i]>=9e14)ans[i]=-1;
		w[_X[i]][_Y[i]]=_w[_X[i]][_Y[i]];
//		printf("x:%d y:%d w:%lld\n",_X[i],_Y[i],w[_X[i]][_Y[i]]);
		p1.upd(_X[i]),p2.upd(_Y[i]);
//		for(x=1;x<=n;++x)p1.upd(x),p2.upd(x);
	}
	for(i=1;i<=n*n;++i)
		printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：luoguhandongheng (赞：6)

感觉这道题和 [CSPS2022T1](https://www.luogu.com.cn/problem/P8817) 有点像。正解做法都是拆开来拼，只不过这道题允许经过重复的点，所以 $K$ 被加强到了 $8$（前者固定经过 $4$ 个不同的点。）

显然正过来删边肯定不如倒过来加边容易，故以下讨论均在加边的情况下。

先来说正解，再来说我的~~乱搞~~做法。

### 正解

首先，经过 $K$ 条边的最短路很容易让人想到矩阵乘法，可是不断加边的时候如果每次都重跑一边 $O(N^3 \log K)$ 的矩阵快速幂肯定会爆炸。

关注到，$K \le 2$ 时，最短路矩阵是好维护的。记$K=k$ 时的最短路矩阵为 $dis_k$。$K = 1$ 时，如果加入一条边 $u\to v$，边权为 $w$。直接 ${dis_1}_{u,v} \gets w$ 即可。定义广义矩阵乘法 $G=A \times B \iff G_{i,j}=\min_{k=1}^{k\le n}(A_{i,k}+B_{k,j})$，则 $dis_2 = dis_1 \times dis_1$。改变 ${dis_1}_{u,v} $ 只影响 $dis_2$ 中的第 $u$ 行和第 $v$ 列。具体地，${dis_2}_{u,k} \gets \min({dis_2}_{u,k},{dis_1}_{u,v}+{dis_1}_{v,k})$，${dis_2}_{k,v} \gets \min({dis_2}_{k,v},{dis_1}_{k,u}+{dis_1}_{u,v})$。由于 $1\le k \le n $，所以每次加边时只需要 $O(N)$ 来维护 $K\le 2$ 时的全源最短路。

接下来考虑查询对象 $1 \to N$ 经过 $K$ 条边的最短路 $L_K$。如果我们能维护 $F_{i,k}$ 表示 $1 \to i$ 经过 $k$ 条边的最短路和 $f_{i,k}$ 表示 $i\to N$ 经过 $k$ 条边的最短路。那么 $L_K = \min_{i=1}^{i\le n}(F_{i,\lfloor {K\over 2}\rfloor}+f_{i,\lceil {K\over 2}\rceil},f_{i,\lfloor {K\over 2}\rfloor}+F_{i,\lceil {K\over 2}\rceil})$。

考虑维护 $F_{i,k}$ 和 $f_{i,k}$。由于 $K\le 8$，只需维护 $k \le 4$ 的情况即可。$F_{i,k}$ 与 $f_{i,k}$ 是对称的，接下来只讨论 $F_{i,k}$。

如加入一条边 $u\to v $，边权为 $w$。

1. 对于 $F_{i,1}$ 和 $F_{i,2}$：

由于上面已经维护了 $dis$，只需要 $F_{i,1} \gets {dis_1}_{1,i},F_{i,2} \gets {dis_2}_{1,i}$ 即可。

2. 对于 $F_{i,3}$：

$F_{i,3} \gets \min(F_{u,1}+w+{dis_1}_{v,i},F_{i,3 })$

$\text{if} \ u=1 \ \text{then } F_{i,3} \gets \min(w+{dis_2}_{v,i},F_{i,3})$  

$F_{v,3} \gets \min(F_{v,3},F_{u,2}+w)$  

3. 对于 $F_{i,4}$：

$F_{i,4} \gets \min(F_{u,1} + w + {dis_2}_{v,i} , F_{u,2} + w + {dis_1}_{v,i},F_{i,4})$

$\text{if} \ u=1 \ \text{then } F_{i,4} \gets \min_{j=1}^{j\le n}(w+{dis_2}_{v,j}+{dis_1}_{j,i},F_{i,4})$

$F_{v,4} \gets \min(F_{v,4},F_{u,3}+w)$

还是挺好懂的吧。

算一下复杂度，对于 $u\ne 1$ 时，每次维护是 $O(N)$ 的，对于 $u = 1$ 时，每次维护是 $O(N^2)$ 的。

总复杂度 $N(N-1)\times O(N) + N \times O(N^2)=O(N^3)$。

贴个代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=305;
ll dis[3][N][N],F[5][N],f[5][N];
int w[N][N],n,k;
void chmin(ll &a,ll b){
    a=min(a,b);
}
void adde(int u,int v){
    chmin(dis[1][u][v],w[u][v]);
    for(int k=1;k<=n;++k){
        chmin(dis[2][u][k],dis[1][u][v]+dis[1][v][k]);
        chmin(dis[2][k][v],dis[1][k][u]+dis[1][u][v]);
    }
    for(int i=1;i<=n;++i){
        F[1][i]=dis[1][1][i];
        F[2][i]=dis[2][1][i];

        f[1][i]=dis[1][i][n];
        f[2][i]=dis[2][i][n];

        chmin(F[3][i],F[1][u]+w[u][v]+dis[1][v][i]);
        chmin(f[3][i],f[1][v]+w[u][v]+dis[1][i][u]);
        if(u==1){
            chmin(F[3][i],w[u][v]+dis[2][v][i]);
        }
        if(v==n){
            chmin(f[3][i],w[u][v]+dis[2][i][u]);
        }

        chmin(F[4][i],min(F[1][u]+w[u][v]+dis[2][v][i],F[2][u]+w[u][v]+dis[1][v][i]));
        chmin(f[4][i],min(f[1][v]+w[u][v]+dis[2][i][u],f[2][v]+w[u][v]+dis[1][i][u]));
        if(u==1){
            for(int j=1;j<=n;++j){
                chmin(F[4][i],w[u][v]+dis[2][v][j]+dis[1][j][i]);
            }
        }
        if(v==n){
            for(int j=1;j<=n;++j){
                chmin(f[4][i],w[u][v]+dis[2][j][u]+dis[1][i][j]);
            }
        }
    }
    chmin(f[3][u],f[2][v]+w[u][v]);
    chmin(F[3][v],F[2][u]+w[u][v]);

    chmin(F[4][v],F[3][u]+w[u][v]);
    chmin(f[4][u],f[3][v]+w[u][v]);

}
ll query(){
    ll ret=f[0][0];
    for(int i=1;i<=n;++i){
        chmin(ret,min(f[k>>1][i]+F[(k+1)>>1][i],f[(k+1)>>1][i]+F[k>>1][i]));
    }
    return ret;
}
vector<pair<int,int> > add;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    memset(f,0x3f,sizeof(f));
    memset(F,0x3f,sizeof(F));
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            cin>>w[i][j];
        }
    }
    for(int i=1;i<=n*n;++i){
        int u,v;
        cin>>u>>v;
        add.push_back({u,v});
    }
    stack <ll> ans;
    for(int i=n*n-1;i>=0;--i){
		ans.push(query());
        adde(add[i].first,add[i].second);
    }
    while(!ans.empty()){
        cout<<(ans.top()==f[0][0] ? -1 : ans.top())<<'\n';
        ans.pop();
    }
    return 0;
}
```

### 另解

考虑拆点。将每个点 $u$ 拆成 $K+1$ 个点，所有点分为 $K+1$ 层。第 $i$ 层相当于经过 $i$ 条边。记第 $i$ 层的 $u$ 节点为 $u(i)$。对于一条 $u \to v$ 的边，对所有 $0 \le i <k$，$u(i)$ 都向 $v(i+1)$ 建边。那么答案就是第 $0$ 层的节点 $1$ 到第 $K$ 层的 $n$ 之间的最短路。

由于这个图只有从上一层到下一层的边，且是一个 DAG。可以考虑类似 SPFA 的方法来求最短路。每加一条边，就跑一遍最短路。每次跑的时候，只需要看加进这条边的时候上一层哪些点成功被松弛了，扩展他们在下一层的邻居即可。

每加一条边最坏时间复杂度是 $O(KN^2)$，总的最坏时间复杂度应该是 $O(KN^4)$。我感觉可以用势能分析证明出一个每次均摊 $O(KN)$，~~但我不会~~，希望能有 dalao 来卡一下这种做法或者给出时间复杂度的证明。

贴个代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=305,K=10;
vector <pii > e[N*K];
int n,k,w[N][N];
ll dis[N*K];
int f(int u,int k){
    return k*n+u;
}
void adde(int u,int v){
    vector <int> now,nxt;
    for(int i=0;i<k;++i){
        int uu=f(u,i),vv=f(v,i+1);
        if(dis[vv]>dis[uu]+w[u][v]){
        	dis[vv]=dis[uu]+w[u][v];
            now.push_back(vv);
        }
        while(!now.empty()){
            int x=now.back();
            now.pop_back();
            for(auto t:e[x]){
                int y=t.first,w=t.second;
                if(dis[y]>dis[x]+w){
                	dis[y]=dis[x]+w; 
                    nxt.push_back(y);
                }
            }
        }
        swap(now,nxt);
    }
    for(int i=0;i<k;++i){
        e[f(u,i)].push_back(pii{f(v,i+1),w[u][v]});
    }
}
vector <pii > add;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            cin>>w[i][j];
        }
    }
    for(int i=1;i<=n*n;++i){
        int u,v;
        cin>>u>>v;
        add.push_back({u,v});
    }
    stack <ll> ans;
    for(int i=n*n-1;i>=0;--i){
		ans.push(dis[f(n,k)]);
        adde(add[i].first,add[i].second);
    }
    while(!ans.empty()){
        cout<<(ans.top()==dis[0] ? -1 : ans.top())<<'\n';
        ans.pop();
    }
    return 0;
}
```

实测正解做法不加快读快写 [8.16s](https://www.luogu.com.cn/record/187407544)，另解做法不加快读快写 [1.90s](https://www.luogu.com.cn/record/187383306)，跑得飞快。

---

## 作者：IamZZ (赞：4)

**P组练习总结#6**

stO **Benq** Orz

### 题目大意

奶牛 Bessie 很喜欢散步！

具体的说，FJ 的农场由 $n(n\le300)$ 个谷仓组成，这些谷仓通过 $n^2$ 条小路连成了一个完全图（有 $n$ 个自环），每条小路有一个长度 $w_{i,j}$。

定义 $k$ 路径为恰好经过 $k$ 条小路的一条路径，输入会给出 $k(k\leq8)$。

如今，破烂不堪的农场正在~~分崩离析~~！在第 $i(i\leq n^2)$ 时刻，$(u_i,v_i)$ 这条边会断裂，保证 $(u_i,v_i)$ 互不相同，即每条边只断一次。

现在，Bessie 想知道从 1 到 $n$ 的最短 $k$ 路径，输出最小的长度，如果没有合法路径，输出 -1 即可。

### 解题思路

删边总是很难处理，正难则反，我们考虑倒序操作，一条一条加边！

$k$ 很小，但是还是很致命。

那我们就让 $k$ 更小吧！折半处理后，似乎还是很难接受……

这就体现 **Benq** 的毒瘤智慧了！一次折半不够，就利用性质，再来一次！

两次折半之后，我们考虑怎么做：

我们设 $f_{i,j}$ 表示从 1 到 $j$ 的 $i(i\leq4)$ 路径，$g_{i,j}$ 表示 $j$ 到 $n$ 的 $i(i\leq4)$ 路径，$h_{i,j,k}$ 表示 $j$ 到 $k$ 的 $i(i\leq2)$ 路径。

考虑这种方法转移的可行性？

我们一步一步推：

假设我们加入了一条边 $(a,b)$，会带来什么影响呢？

处理 $h$，$h_{1,a,b}$ 会更新为 $w_{a,b}$，我们可以枚举一个 $i$，更新 $h_{2,i,b}$ 和 $h_{2,a,i}$，这两个都很简单。

至此，所有加入 $(a,b)$ 会影响到的 $h$ 都更新到了！$h$ 数组已经已经更新到最新版本，可以放心使用了。

来，现在我们处理 $f,g$，易知：$f_{i,j}=h_{i,1,j},g_{i,j}=h_{i,j,n}(i\le2)$，我们可以快速处理出 $i=1$ 或者 $i=2$ 时的 $f,g$。

那 $i=3$ 时怎么办啊？

我们枚举 $(a,b)$ 是这三条边中的第几条，如果是第一条（前提 $a=1$ 更新 $f$ 或 $b=n$ 更新 $g$），枚举 $j$，$f_{3,j}=\min w_{a,b}+h_{2,b,j}$；

如果是第二条，还是枚举 $j$，$f_{3,j}=\min f_{1,a}+w_{a,b}+h_{1,b,j}$；

若是第三条，$f_{3,b}=\min f_{2,a}+w_{a,b}$；几个操作对 $g$ 来说同理的。

那 $i=4$​ 呢？

是第二，三条边时，拆成三部分，几乎没有什么区别；

如果是第四条边，$f_{4,b}=\min f_{3,a}+w_{a,b}$；老样子，$g$ 同理！

最后这是题目中稍微有一点思维的地方……额，真的只有一点思维。

若是第一条边，我们会发现，只用一个 $h$ 不够了，需要枚举一个中间点，把三条边拆成两部分！

仔细一想，这个，枚举最终点 $v$，中间点 $u$，这怎么是 $n^2$ 的复杂度啊？再加上前面 $n^2$ 的加边，似乎不能接受啊！

敲黑板，别忘了一个重要的前置条件！

第一条边！$a=1$ 才可能是第一条边啊！那 $a=1$ 的边，一共也就 $n$ 条，跑 $n$ 次 $n^2$，区区 $n^3$ 的复杂度，可以接受好吧，$f_{4,v}=\min w_{a,b}+h_{1,b,u}+h_{2,u,v}$。

对 $g$ 来说，则需要 $b=n$​，复杂度也是一样的。

就这样，我们维护好了所有的 $f,g,h$，可以算答案了，枚举一个点 $i$ 做中间点，$ans=\min_{i=1}^nf_{\lfloor\frac k 2\rfloor,i}+g_{\lceil\frac k 2\rceil,i}$。

如果两个根本不联通，稍微判断一下就好啦！

总复杂度也不过 $\Theta(n^3)$，足以通过此题！

完结撒花(●'◡'●)！

（这个转移式差不多都写出来了，应该还能看懂吧？）

### 参考代码

乱七八糟，勿喷(⊙_⊙;)……

```c++
#include<bits/stdc++.h>
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
typedef long long ll;
using namespace std;
const int N=305;
int n,k,f[5][N],g[5][N],h[3][N][N],w[N][N],z,m[N*N];
struct node
{
	int x,y;
}q[N*N];
void solve(int p)
{
	int i,j,a=q[p].x,b=q[p].y,c=w[a][b];
	m[p]=1e9;
	for(i=1;i<=n;++i)//ans的处理
	  m[p]=min(min(f[z][i]+g[k-z][i],f[k-z][i]+g[z][i]),m[p]);
	if(m[p]==1e9)//根本不联通
	  m[p]=-1;
	h[1][a][b]=c;//h[1]
	for(i=1;i<=n;++i)//h[2]
	  h[2][i][b]=min(h[2][i][b],h[1][i][a]+c);
	for(i=1;i<=n;++i)
	  h[2][a][i]=min(h[2][a][i],c+h[1][b][i]);
	for(i=1;i<=2;++i)
	{
		for(j=1;j<=n;++j)//f[1],f[2],g[1],g[2]
		  f[i][j]=h[i][1][j],g[i][j]=h[i][j][n];
	}
	f[3][b]=min(f[3][b],h[2][1][a]+c);//f[3]
	for(i=1;i<=n;++i)
	  f[3][i]=min(f[3][i],f[1][a]+c+h[1][b][i]);
	g[3][a]=min(g[3][a],c+h[2][b][n]);//g[3]
	for(i=1;i<=n;++i)
	  g[3][i]=min(g[3][i],h[1][i][a]+c+g[1][b]);
	if(a==1)
	{
		for(i=1;i<=n;++i)
		  f[3][i]=min(f[3][i],c+h[2][b][i]);
		for(i=1;i<=n;++i)//特殊的，第一条边时的f[4]
		{
			for(j=1;j<=n;++j)
			  f[4][i]=min(f[4][i],min(c+h[1][b][j]+h[2][j][i],c+h[2][b][j]+h[1][j][i]));
		}
	}
	if(b==n)
	{
		for(i=1;i<=n;++i)
		  g[3][i]=min(g[3][i],h[2][i][a]+c);
		for(i=1;i<=n;++i)
		{
			for(j=1;j<=n;++j)//特殊的，第一条边时的g[4]
			  g[4][i]=min(g[4][i],min(h[1][i][j]+h[2][j][a]+c,h[2][i][j]+h[1][j][a]+c));
		}
	}
	f[4][b]=min(f[4][b],f[3][a]+c);//f[4]
	g[4][a]=min(g[4][a],c+g[3][b]);//g[4]
	for(i=1;i<=n;++i)
	  f[4][i]=min(f[4][i],min(f[1][a]+c+h[2][b][i],f[2][a]+c+h[1][b][i]));
	for(i=1;i<=n;++i)
	  g[4][i]=min(g[4][i],min(h[1][i][a]+c+g[2][b],h[2][i][a]+c+g[1][b]));
	return ;
}
int main()
{
	int i,j;
	scanf("%d%d",&n,&k);
	z=k>>1;
	for(i=1;i<=n;++i)
	{
		for(j=1;j<=n;++j)
		  scanf("%d",w[i]+j);
	}
	for(i=1;i<=4;++i)
	{
		for(j=1;j<=n;++j)
		  f[i][j]=g[i][j]=1e9;
	}
	for(i=1;i<=n;++i)
	{
		for(j=1;j<=n;++j)
		  h[1][i][j]=h[2][i][j]=1e9;
	}
	for(i=1;i<=n*n;++i)
	  scanf("%d%d",&q[i].x,&q[i].y);
	for(i=n*n;i;--i)
	  solve(i);
	for(i=1;i<=n*n;++i)
	  printf("%d\n",m[i]);
	return 0;
}
```



---

## 作者：_jimmywang_ (赞：4)

大家好，我喜欢套娃。

首先时间倒流变加边+折半。

然后我不会处理折半，于是我进行一个折半的折半。

--------------

考虑对于每个时刻处理出 $dis[i](1\leq i \leq n)$ 表示当前 $1$ 到 $i$ 走 $4$ 步的最短路，不存在即为 $\inf$。

（$i$ 到 $n$ 同理，这里只讨论一半。）

然后我不会维护 $dis$，于是我进行一个**再次折半**。

设 $D[i][j][k]$ 表示从 $i$ 出发，依次走 $(i,j)$ 与 $(j,k)$ 边的距离，不存在记为 $\inf$。

可以发现当且仅当在这两条边迟**加入**（因为时间倒流所以是加边）的那一条加入的时刻，$D[i][j][k]$ 会发生改变。

于是维护 $D$ 的**总**复杂度为 $O(n^3)$。

设 $L[i][j]$ 表示从 $i$ 出发走 $2$ 步到达 $j$ 的最短路，不存在同样记为 $\inf$。

于是有 $L[i][j]=\min_{k=1}^nD[i][k][j]$。

可以发现当 $D[i][j][k]$ 被修改时，$L[i][k]$ 会被取 $\min$。因此 $L$ 总的修改次数不超过 $O(n^3)$。

接下来考虑如何用 $L$ 来维护 $dis$。

首先，当 $L[i][j]$ 被修改时，$dis[j]$ 会被修改，因为存在一条路径 $(1,?,i,?,j)$。

此时变化为 `dis[j]=min(dis[j],L[1][i]+L[i][j])`，这个过程记为 ①。

但是当 $i=1$ 的时候，由于存在 $(1,?,j,?,u)(1\leq u \leq n)$，我们要对每个 $1 \leq u \leq n$ 执行 `dis[u]=min(dis[u],L[1][j]+L[j][u])`，这个过程记为 ②。

这样看起来复杂度不是很对，达到了 $O(n^3 \times n)=O(n^4)$，但是其实不是。

执行 ① 的次数等于 $L$ 修改的次数，为 $O(n^3)$。

但是执行 ② 的次数等于 $L[1][*]$ 的修改次数，再往前导就是 $D[1][*][*]$ 的修改次数，为 $O(n^2)$。

所以 ② 的总复杂度仍为 $O(n^3)$。程序的总复杂度为 $O(n^3)$。

---

## 作者：vectorwyx (赞：4)

> 这是一个复杂度没有保证的做法。

时间倒流，变删边为加边。怎么限制路径长度？无脑分层图。将图分为 $k+1$ 层，第 $i$ 层向第 $i+1$ 层连边，然后跑 spfa。

总共有 $nk$ 个点，$n^2k$ 条边，理论复杂度飞天，但是数据没卡。

```cpp
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

//15:47~15:56~16:01

const int N=3005,M=301*301,inf=1e9;
vector<pii> e[N];
int n,k,mp[N][N],ans[M],dis[N],t,inq[N];
pii ee[M];

#define upda(x,v,y){\
	if(dis[x]+v<dis[y]){\
		dis[y]=dis[x]+v;\
		if(!inq[y]) inq[y]=1,q.push(y);\
	}\
}

signed main(){
	cin>>n>>k;k++;t=n*k;
	fo(i,1,n) fo(j,1,n) mp[i][j]=read();
	fo(i,1,n*n){
		int x=read(),y=read();
		ee[i]=mk(x,y);
	}
	fo(i,2,n*k) dis[i]=inf;
	go(tt,n*n,1){
//		printf("%d!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",tt);
		ans[tt]=dis[t]<inf?dis[t]:-1;
		int x=ee[tt].fi,y=ee[tt].se;
		queue<int> q;
		fo(j,0,k-1){
			int X=x+j*n,Y=y+(j+1)*n;
			upda(X,mp[x][y],Y);
			e[X].eb(Y,mp[x][y]);
		}
		while(!q.empty()){
			int xx=q.front();q.pop();
			inq[xx]=0;
			for(auto i:e[xx]) upda(xx,i.se,i.fi);
		}
	}
	fo(i,1,n*n) cout<<ans[i]<<'\n';
	return 0;
}
}










signed main(){re vectorwyx::main();}


```

---

## 作者：KellyFrog (赞：2)

靠谱做法，事实上这个题 $k\ge 9$ 是没法做的。

考场上首先观察出 $k\le 8$，那一眼指数/meet in the middle，这个指数没有很好可以枚举的集合，那考虑 meet in the middle。

常见套路，删边变倒序加边。记 $d_{i,j}$ 表示 $1$ 到 $i$ 恰经过 $j$ 条边（其中 $j\in [1,4]$）的最短路，这是路径的前一半，后一半也同理，我们只需要在加边过程中动态维护这玩意就行了。

考虑加的一条边在什么位置，只有两种情况不能直接做，一种是在第一条边（即 $u=1$），一种是在第二条边，下面分别分析。

当在第一条边的时候，路径是 $1=u\stackrel{w}{\rightarrow}v\rightarrow x\rightarrow y\rightarrow z$，注意此时 $(u,v,w)$ 总共只有 $n$ 个，因此我们可以承受 $O(n^2)$ 的枚举量。除了 $d_{z,4}$ 都是好做的，不妨枚举 $x,z$，另外处理出 $d'_{x,z}$ 表示 $x\rightarrow y\rightarrow z$ 的最短路，处理的部分加入每条边时可以 $O(n)$ 更新，这样复杂度是一条边 $O(n^2)$，可以接受。

当在第二条边的时候，路径是 $1\rightarrow u\stackrel{w}{\rightarrow}v\rightarrow x\rightarrow y$，$d_{y,4}$ 借助 $d'$ 更新，复杂度 $O(n)$。

这样总复杂度 $O(n^3)$，有理有据，$k$ 更大时就不能 $O(n^3)$ 了。

剩下的部分比较简单，参考代码不难。

赛时代码：

```cpp
// Problem: Problem 1. Breakdown
// Contest: USACO - USACO 2022 December Contest, Platinum
// URL: http://usaco.org/index.php?page=viewproblem&cpid=1248
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// Create Time: 2022-12-18 12:55:34
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 305;
const ll inf = 1e18;

int n, k; 
int du[N*N], dv[N*N];
ll d1[N][5], d2[N][5], d3[N][N], w[N][N], adj[N][N];;
ll ans[N*N];

void upd1(int u, int v, ll d[N][5]) {
	int s = 1;
	//1
	if(u == s) {
		d[v][1] = min(d[v][1], w[u][v]);
		rep(i, 1, n) d[i][2] = min(d[i][2], w[u][v] + w[v][i]);
		rep(i, 1, n) d[i][3] = min(d[i][3], w[u][v] + d3[v][i]);
		rep(i, 1, n) rep(j, 1, n) d[j][4] = min(d[j][4], w[u][v] + w[v][i] + d3[i][j]);
	}
	//2
	d[v][2] = min(d[v][2], w[s][u] + w[u][v]);
	rep(i, 1, n) d[i][3] = min(d[i][3], w[s][u] + w[u][v] + w[v][i]);
	rep(i, 1, n) d[i][4] = min(d[i][4], w[s][u] + w[u][v] + d3[v][i]);
	//3
	d[v][3] = min(d[v][3], d[u][2] + w[u][v]);
	rep(i, 1, n) d[i][4] = min(d[i][4], d[v][3] + w[v][i]);
	//4
	d[v][4] = min(d[v][4], d[u][3] + w[u][v]);
}

void upd2(int u, int v, ll d[N][5]) {
	int t = n;
	//1
	if(v == n) {
		d[u][1] = min(d[u][1], w[u][v]);
		rep(i, 1, n) d[i][2] = min(d[i][2], w[i][u] + w[u][v]);
		rep(i, 1, n) d[i][3] = min(d[i][3], d3[i][u] + w[u][v]);
		rep(i, 1, n) rep(j, 1, n) d[i][4] = min(d[i][4], d3[i][j] + w[j][u] + w[u][v]);
	}
	//2
	d[u][2] = min(d[u][2], w[u][v] + w[v][t]);
	rep(i, 1, n) d[i][3] = min(d[i][3], w[i][u] + w[u][v] + w[v][t]);
	rep(i, 1, n) d[i][4] = min(d[i][4], d3[i][u] + w[u][v] + w[v][t]);
	//3
	d[u][3] = min(d[u][3], w[u][v] + d[v][2]);
	rep(i, 1, n) d[i][4] = min(d[i][4], w[i][u] + d[u][3]);
	//4
	d[u][4] = min(d[u][4], w[u][v] + d[v][3]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k;
	rep(i, 1, n) rep(j, 1, n) cin >> adj[i][j];
	rep(i, 1, n*n) cin >> du[i] >> dv[i];
	
	rep(i, 1, n) rep(j, 1, n) w[i][j] = d3[i][j] = inf;
	rep(i, 1, n) rep(j, 0, 4) d1[i][j] = d2[i][j] = inf;
	rep(i, 1, n*n+1) ans[i] = inf;

	per(i, 1, n*n) {
		int u = du[i], v = dv[i];
		w[u][v] = adj[u][v];
		rep(u0, 1, n) d3[u0][v] = min(d3[u0][v], w[u0][u] + w[u][v]);
		rep(u0, 1, n) d3[u][u0] = min(d3[u][u0], w[u][v] + w[v][u0]);
		upd1(u, v, d1);
		upd2(u, v, d2);
		if(k <= 4) ans[i] = d1[n][k];
		else rep(j, 1, n) ans[i] = min(ans[i], d1[j][4] + d2[j][k-4]);
	}

	rep(i, 2, n*n+1) cout << (ans[i] == inf ? -1 : ans[i]) << "\n";
	
	return 0;
}

```

---

## 作者：xuanxuan001 (赞：1)

没太关注，这次 USACO 的题搬进主题库了现在才发现。

终于调过了，发篇题解纪念一下。

本来以为这次的 Pt 组会跟二月那次一样两黑一紫的，所以就带着刚 T1 的心态去打的，结果没想到两紫一蓝。上来想了一会切了 T1 还感觉不错，结果那时候可能脑子有点昏，细节题写得漏洞百出，调了一整场都没调出来。

赛时的光辉战绩：

![](https://cdn.luogu.com.cn/upload/image_hosting/ww1lls7a.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

赛后又改了一下，最后直到今天看见洛谷里的这道题后又看了看代码才改过最后 $k=5,7$ 的情况，不知道当时写代码的时候在想啥能写出这么多错。

大概是个 meet-in-middle 套 meet-in-middle，真不知道 $\color{black}B\color{red}{enq}$ 是怎么出出这种阴间题的。

$k \le 8$，所以下面直接考虑 $k=8$ 的情况，其他的类似。

首先先来一个 meet-in-middle 记录 $dis_{1/n,i,j}$ 表示从 $1/n$ 经过 4 条边到 $i$ 不用最先删的 $j$ 条边的最小代价，不能达到记为 INF，那么这个的状态数就是刚好 $O(n^3)$ 的。最终第 $i$ 行的答案就是 $\min\limits_{j=1}^n dis_{1,j,i}+dis_{n,j,i}$。

虽然状态数正确，但下面还需要考虑怎么求，这时再来一个 meet-in-middle。记录 $dp_{i,j,k}$ 表示从 $i$ 经过 2 条边到 $j$ 不用最先删的 $k$ 条边的最小代价。那么这个是 $O(n^4)$ 的，不行。但是发现有效位置最多只有 $n$ 个，因为考虑中间经过的那个点只有 $n$ 个取值，所以只记录这 $O(n)$ 个位置。

然后在求 $dis_{1/n,i,j} = \min\limits_{p=1}^n dp_{1/n,p,j} + dp{p,i,j}$ 时发现确定 $i$ 后一个 $p$ 只会贡献 $O(n)$ 种取值，而这只需要将两边的 $dp$ 做一个类似归并排序的东西就行了。对一整段取 $\min$ 的操作可以先只更新最大的那个最后求一遍后缀 $\min$。

实现的时候还要注意如果把上面那三个 $n^3$ 的数组都开出来会 MLE（我不知道别人是不是，反正我是）。所以我是滚动了 $dis$，每次求出对于一个 $i$ 的之后就直接更新答案然后丢弃。

感觉 $\color{black}B\color{red}{enq}$ 造数据是用心了的，我赛时求 $dis$ 的地方出了个问题拍了几千组才拍出来，规模开满也没用，结果交上去一个点也过不了~~我也不知道他为啥不卡一下SPFA~~。

极其丑陋的代码：
```
#include<cstdio>
#include<algorithm>
#define TY int
#define MAXN 302
#define MAXM 90002
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
using namespace std;
typedef long long ll;
const TY M=998244353;//答案不会超过 8e8，所以选择这个作为 INF 即可
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw1(TY a){if(a>9)qw1(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw1(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY n,m,k,u,p,q,w[MAXN][MAXN],id[MAXN][MAXN],t[MAXN],x[MAXN],l[MAXN][MAXN],ds1[MAXM],dsn[MAXM],ans[MAXM];
struct node{TY x,y;}ds[MAXN][MAXN][MAXN],ar[MAXN],tmp;bool operator<(node a,TY b){return a.x<b;}
int main(){
	n=qr();k=qr();FOR(i,1,n)FOR(j,1,n)w[i][j]=qr();
	m=n*n;FOR(i,1,m){u=qr();id[u][qr()]=i;ans[i]=M;}
	if(k==2){
		FOR(i,1,n){
			u=minn(id[1][i],id[i][n]);
			ans[u]=minn(ans[u],w[1][i]+w[i][n]);
		}ROF(i,m-1,1)ans[i]=minn(ans[i],ans[i+1]);
		FOR(i,1,m)if(ans[i]==M)ans[i]=-1;
		FOR(i,2,m)qw(ans[i],'\n');printf("-1");return 0;
	}if(k==3){//k<=3 的可以直接暴力（其实 k=4 也可以放在这里解决） 
		FOR(i,1,n)FOR(j,1,n){
			u=minn(id[1][i],minn(id[i][j],id[j][n]));
			ans[u]=minn(ans[u],w[1][i]+w[i][j]+w[j][n]);
		}ROF(i,m-1,1)ans[i]=minn(ans[i],ans[i+1]);
		FOR(i,1,m)if(ans[i]==M)ans[i]=-1;
		FOR(i,2,m)qw(ans[i],'\n');printf("-1");return 0;
	}FOR(i,1,n)FOR(j,1,n){//求 dis 数组 
		fOR(k,u=0,n)t[k]=0;
		FOR(k,1,n){
			ar[k].x=minn(id[i][k],id[k][j]);
			ar[k].y=w[i][k]+w[k][j];
			++t[ar[k].x%n];
		}fOR(k,1,n)t[k]+=t[k-1];
		FOR(k,1,n)x[t[ar[k].x%n]--]=k;
		FOR(k,0,n)t[k]=0;FOR(k,1,n)++t[ar[k].x/n];
		FOR(k,1,n)t[k]+=t[k-1];//用 sort 会被卡 log，所以需要基数排序 
		ROF(k,n,1)ds[i][j][t[ar[x[k]].x/n]--]=ar[x[k]];
		fOR(k,1,n)if(ds[i][j][k].x>ds[i][j][k+1].x){printf("!!!");return 0;}
		FOR(k,1,n){//用单调栈去掉重复元素 
			if(u&&ds[i][j][u].x==ds[i][j][k].x){
				ds[i][j][k].y=minn(ds[i][j][u].y,ds[i][j][k].y);u=~-u;
			}while(u&&ds[i][j][u].y>=ds[i][j][k].y)u=~-u;ds[i][j][u=-~u]=ds[i][j][k];
		}l[i][j]=u;
	}FOR(i,1,n){
		FOR(j,1,m)ds1[j]=dsn[j]=M;
		FOR(j,1,n){//求 dis 数组 
			p=q=1;while(p<=l[1][j]&&q<=l[j][i]){
				u=minn(ds[1][j][p].x,ds[j][i][q].x);
				ds1[u]=minn(ds1[u],ds[1][j][p].y+ds[j][i][q].y);
				if(ds[1][j][p].x<ds[j][i][q].x)p=-~p;
				else q=-~q;
			}
		}ROF(j,m-1,1)ds1[j]=minn(ds1[j],ds1[j+1]);
		if(k==4){if(i==n)FOR(j,1,m)ans[j]=ds1[j];continue;}//k=4 不需要第二次 meet-in-middle，直接更新答案即可 
		if(k==5){//k=5 的另一边就是原图的边 
			FOR(j,1,id[i][n])ans[j]=minn(ans[j],ds1[j]+w[i][n]);continue;
		}if(k==6)FOR(j,1,l[i][n])dsn[ds[i][n][j].x]=ds[i][n][j].y;//k=6 的另一边就是 dis 数组 
		else if(k==7)FOR(j,1,n){
			u=lower_bound(ds[i][j]+1,ds[i][j]+l[i][j]+1,id[j][n])-ds[i][j];
			if(u<=l[i][j])dsn[id[j][n]]=minn(dsn[id[j][n]],ds[i][j][u].y+w[j][n]);
			fOR(k,0,u)dsn[ds[i][j][k].x]=minn(dsn[ds[i][j][k].x],ds[i][j][k].y+w[j][n]);
		}else FOR(j,1,n){//k=8 需要求第二遍 dis 数组 
			p=q=1;while(p<=l[i][j]&&q<=l[j][n]){
				u=minn(ds[i][j][p].x,ds[j][n][q].x);
				dsn[u]=minn(dsn[u],ds[i][j][p].y+ds[j][n][q].y);
				if(ds[i][j][p].x<ds[j][n][q].x)p=-~p;
				else q=-~q;
			}u=minn(ds[i][j][p].x,ds[j][n][q].x);
			dsn[u]=minn(dsn[u],ds[i][j][p].y+ds[j][n][q].y);
		}ROF(j,m-1,1)dsn[j]=minn(dsn[j],dsn[j+1]);
		FOR(j,1,m)ans[j]=minn(ans[j],ds1[j]+dsn[j]);
	}FOR(i,1,m)if(ans[i]==M)ans[i]=-1;
	FOR(i,2,m)qw(ans[i],'\n');printf("-1");return 0;
}
```

---

