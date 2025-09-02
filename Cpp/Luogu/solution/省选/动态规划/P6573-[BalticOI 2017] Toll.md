# [BalticOI 2017] Toll

## 题目背景

作为一个合格的货运公司，在送达货物的同时也要让花的钱最少。

## 题目描述

这座城市有 $n$ 个地点，这 $n$ 个地点之间有 $m$ 条边。  
货运公司接到了 $o$ 个订单，他们要想方设法的让路途中花的钱最少。  
对于每条路，都有三个信息：  
- $a,b$ 代表从 $a$ 连到 $b$；
- $t$ 代表这条路需要多少钱。  

并且对于每个订单，都给出 $a$ 和 $b$ 代表要把物品从 $a$ 运到 $b$ ，求每个订单需要花的最少的钱；如果无法送达就输出 $-1$。  
特别的，对于两个编号为 $a,b$ 的路，一定满足：
$$\left\lfloor\dfrac{b}{k}\right\rfloor=1+\left\lfloor\dfrac{a}{k}\right\rfloor$$
（$k$ 是一个给定的常数）。

## 说明/提示

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（7 pts）：$k=1$。
- Subtask 2（10 pts）：每个订单中的 $a=0$。
- Subtask 3（8 pts）：$o \le 100$。
- Subtask 4（31 pts）：$o \le 3000$。
- Subtask 5（44 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 50000$，$1 \le o \le 10000$，$1 \le k \le 5$，$0 \le a < b < n$，$1 \le t \le 10000$。

#### 说明

**翻译自 [BOI 2017 D1](https://boi.cses.fi/files/boi2017_day1.pdf) T3 Toll。**  
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。   
**本题强制 $O2$ 优化。**

## 样例 #1

### 输入

```
5 14 5 5
0 5 9
5 12 10
0 7 7
7 12 8
4 7 10
0 12
0 5
0 7
7 12
0 13```

### 输出

```
15
9
7
8
-1```

# 题解

## 作者：Tweetuzki (赞：8)

> 给出一张 $n$ 个点，$m$ 条边的有向图，$q$ 次询问任意两点间最短路。
> 
> 给出一常数 $k$，保证每条边 $(u, v)$ 保证 $\left\lfloor \frac{u}{k} \right\rfloor + 1 = \left\lfloor \frac{v}{k} \right\rfloor$。
> 
> $n \le 50\ 000$，$q \le 10\ 000$，$k \le 5$。

感觉 NOIP2018 普及了动态 DP 以后，这题变简单了。

对于每个块维护一个矩阵做动态 DP。

设进入这个块时，从起点到每个点的距离依次为

$$
\begin{bmatrix}
f_0 & f_1 & \cdots & f_{k - 1} 
\end{bmatrix}
$$

出完这个块之后，需要从这个块内的边走出去，更新矩阵变成

$$
\begin{bmatrix}
g_0 & g_1 & \cdots & g_{k - 1}
\end{bmatrix}
$$

首先有一个暴力 DP：

$$
g_j = \min\limits_{i = 0} ^ {k - 1} \left(f_i + w_{i, j}\right)
$$

其中 $i, j$ 表示该块内的 $i$ 号点连向下一个块内 $j$ 号点的边的边权，没有设为 $+\infty$。

学习了动态 DP 之后，知道这个东西是可以写成矩阵 “乘法” 形式的，转移矩阵是：

$$
\begin{bmatrix}
w_{0, 0} & w_{0, 1} & \cdots & w_{0, k - 1} \\
w_{1, 0} & w_{1, 1} & \cdots & w_{1, k - 1} \\
\vdots   & \vdots   & \ddots & \vdots \\
w_{k - 1, 0} & w_{k - 1, 1} & \cdots & w_{k - 1, k - 1}
\end{bmatrix}
$$

这个东西是 $\min$ 和 $+$ 套起来，是有结合律的。所以倍增或线段树维护一下区间连乘积，每次查询的时候直接乘即可。

经过一些细节优化可以做到，时间复杂度 $\mathcal{O}((n + q) k ^ 2 \log n)$。

代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>

const int MaxN = 50000, MaxK = 5;
const int MaxLog = 16;
const int INF = 0x3F3F3F3F;

int N, M, K, Q;

struct matrix_t {
  int mat[MaxK][MaxK];
  matrix_t() { memset(mat, 0x3F, sizeof mat); }

  inline friend matrix_t operator*(const matrix_t &a, const matrix_t &b) {
    matrix_t c;
    for (int i = 0; i < K; ++i)
      for (int j = 0; j < K; ++j) {
        int x = INF;
        for (int k = 0; k < K; ++k)
          x = std::min(x, a.mat[i][k] + b.mat[k][j]);
        c.mat[i][j] = x;
      }
    return c;
  }
};

struct vector_t {
  int mat[MaxK];
  vector_t() { memset(mat, 0x3F, sizeof mat); }

  inline friend vector_t operator*(const vector_t &a, const matrix_t &b) {
    vector_t c;
    for (int i = 0; i < K; ++i)
      for (int j = 0; j < K; ++j)
        c.mat[j] = std::min(c.mat[j], a.mat[i] + b.mat[i][j]);
    return c;
  }
};

matrix_t F[MaxLog + 1][MaxN + 5];

void init() {
  scanf("%d %d %d %d", &K, &N, &M, &Q);
  for (int i = 1; i <= M; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    F[0][u / K].mat[u % K][v % K] = std::min(F[0][u / K].mat[u % K][v % K], w);
  }
}

inline void query(vector_t &f, int l, int r) {
  int x = l;
  for (int i = MaxLog; i >= 0; --i)
    if ((r - l + 1) & (1 << i)) {
      f = f * F[i][x];
      x += (1 << i);
    }
}

void solve() {
  for (int i = 1; (1 << i) <= N / K + 1; ++i)
    for (int j = 0; j + (1 << i) - 1 < (N / K + 1); ++j)
      F[i][j] = F[i - 1][j] * F[i - 1][j + (1 << (i - 1))];
  for (int q = 1; q <= Q; ++q) {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a / K == b / K) puts("-1");
    else {
      vector_t f;
      f.mat[a % K] = 0;
      query(f, a / K, b / K - 1);
      if (f.mat[b % K] == INF) puts("-1");
      else printf("%d\n", f.mat[b % K]);
    }
  }
}

int main() {
  init();
  solve();
  return 0;
}
```

---

## 作者：7KByte (赞：6)

根本不需要矩阵，直接倍增 DP 即可。

记录状态 $f_{i,u,v,k}$ 表示从第 $i$ 层的第 $u$ 个节点出发，到第 $i+2^k$ 层的第 $v$ 个节点结束的最短路。

枚举中转点转移 $f_{i,u,v,k}=\min\limits_{p}\{f_{i,u,p,k - 1} + f_{i +2^{k - 1},p,v,k - 1}\}$。时间复杂度 $\mathcal{O}(K^3N\log N)$。

事实上我们直接写分治算法可以做到 $\mathcal{O}(K^2N\log N)$ 的复杂度，对于跨中点的询问，分别计算两边然后将答案拼起来。

```cpp
#define N 50005
int k, n, m, o, f[N][5][5][16], t;
int main() {
	k = read(), n = read(), m = read(), o = read();
	n = n / k, t = log2(n);
	memset(f, 0x3f, sizeof(f));
	while(m--){
		int a = read(), b = read(), c = read();
		f[a / k][a % k][b % k][0] = c;
	}
	rp(j, t)rep(i, 0, n - (1 << j))rep(u, 0, k - 1)rep(v, 0, k - 1)rep(p, 0, k - 1)
		cmn(f[i][u][v][j], f[i][u][p][j - 1] + f[i + (1 << (j - 1))][p][v][j - 1]);
	while(o--){
		int a = read(), b = read();
		if(a / k >= b / k)puts("-1");
		else{
			int p[5], q[5], w = (b / k - a / k); 
			memset(p, 0x3f, sizeof(p));
			p[a % k] = 0, a /= k;
			pre(i, t, 0)if((w >> i) & 1){
				memset(q, 0x3f, sizeof(q));
				rep(u, 0, k - 1)rep(v, 0, k - 1)
					cmn(q[u], p[v] + f[a][v][u][i]);
				rep(u, 0, k - 1)p[u] = q[u];
				a += 1 << i;
			}
			if(p[b % k] < 0x3f3f3f3f)printf("%d\n", p[b % k]); else puts("-1");
		}
	}
	return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：5)

观察一下，发现整个图其实是一个分层图，每层有 $k$ 个点，边只在相邻两层连边。

因为 $k$ 非常小只有 $5$，我们可以使用邻接矩阵维护相邻两层之间的最短路。

然后询问操作本质上是询问一个区间中的矩阵广义乘起来之后某个位置的值。

那么直接拿线段树维护区间广义矩阵乘法即可。

> 广义矩阵乘法：

> $$c_{i,j}=\min_{k}a_{i,k}+b_{k,j}$$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,m,o,lim;
struct node{
	int a[6][6];
}tree[200005];
const node operator *(const node &x,const node &y){
	node z;memset(z.a,0x3f,sizeof(z.a));
	for(int i=0;i<k;i++)
		for(int j=0;j<k;j++)
			for(int p=0;p<k;p++)z.a[i][j]=min(z.a[i][j],x.a[i][p]+y.a[p][j]);
	return z;
}
void build(int k,int l,int r){
	memset(tree[k].a,0x3f,sizeof(tree[k].a));
	if(l==r)return;
	int mid=l+r>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
}
void change(int k,int l,int r,int x,int a,int b,int y){
	if(l==r){
		tree[k].a[a][b]=y;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)change(k*2,l,mid,x,a,b,y);
	else change(k*2+1,mid+1,r,x,a,b,y);
	tree[k]=tree[k*2]*tree[k*2+1];
}
node query(int k,int l,int r,int x,int y){
	if(l>=x&&r<=y)return tree[k];
	int mid=l+r>>1;
	if(y<=mid)return query(k*2,l,mid,x,y);
	else if(x>mid)return query(k*2+1,mid+1,r,x,y);
	else return query(k*2,l,mid,x,y)*query(k*2+1,mid+1,r,x,y);
}
int main(){
	scanf("%d%d%d%d",&k,&n,&m,&o);lim=(n-1)/k+1;
	build(1,1,lim);
	for(int i=1;i<=m;i++){
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		change(1,1,lim,x/k+1,x%k,y%k,z);
	}
	for(int i=1;i<=o;i++){
		int x,y;scanf("%d%d",&x,&y);
		if(x/k==y/k)puts("-1");
		else{
			node res=query(1,1,lim,x/k+1,y/k);
			if(res.a[x%k][y%k]==0x3f3f3f3f)puts("-1");
			else printf("%d\n",res.a[x%k][y%k]);
		}
	}
	return 0;
}
```

---

## 作者：一扶苏一 (赞：4)

## 【动态 dp】【P6573】 [BOI 2017] Toll

### Analysis

我们注意到 $\left\lfloor\frac x k\right\rfloor$ 只有 $k$ 个。因此这张图可以被分成 $\left\lfloor\frac {n - 1} k\right\rfloor$ 层，每层只会向下一层连边，是一个 DAG，每个节点的度数不会超过 $k$。

因为是一个 DAG，所以可以 dp。设 $f_u$ 是从 $u$ 到 $b$ 的最短路，转移为 $f_{u} = \min\{f_v + t_{u, v}\}$。

把除以 $k$ 下取整相同的所有 $f$ 值按照模 $k$ 的大小顺序依次放到一个 $1 \times k$ 的矩阵里，那么转移可以写成

$$\begin{bmatrix} f_a &f_b & \dots \end{bmatrix} \times \begin{bmatrix} t_{a, x} &t_{a,y} & \dots \\ t_{b, x} & t_{b, y} &\dots \\ \dots\end{bmatrix}= \begin{bmatrix} f_x &f_y & \dots \end{bmatrix}$$

这里的矩阵乘法定义为 $(AB)_{i, j} = \min_{x = 0}^{k - 1}\{A_{i, x} + B_{x, j}\}$。因为加法对最值运算有分配律，所以这样定义的矩阵乘法有结合律。

把所有的转移矩阵用线段树维护，可以发现每次查询就是查询一个区间乘积。做法类似于 [GSS3](https://www.luogu.com.cn/problem/SP1716) 的 ddp 做法，时间复杂度 $O(nk^3\log n )$。

### Code

```cpp
namespace Fusu {

const int maxn = 50005;
const int maxt = 5;
const int INF = 0x3f3f3f3f;

int t, n, m, q;
int bel[maxn], res[maxn];

struct Mat {
  int mt[maxt][maxt];

  Mat() { memset(mt, 0x3f, sizeof mt); }
  Mat(const int x) { 
    memset(mt, 0x3f, sizeof mt); 
    for (int i = 0; i < t; ++i) mt[i][i] = 0; 
  }

  Mat operator*(const Mat &o) const {
    Mat ret;
    for (int i = 0; i < t; ++i) {
      for (int j = 0; j < t; ++j) {
        ret.mt[i][j] = INF;
        for (int k = 0; k < t; ++k) {
          ret.mt[i][j] = std::min(ret.mt[i][j], mt[i][k] + o.mt[k][j]);
        }
      }
    }
    return ret;
  }
  
  void debug() {
    for (int i = 0; i < t; ++i) {
      for (int j = 0; j < t; ++j) {
        printf("%d   ", mt[i][j]);
      }
      putchar('\n');
    }
  }
};
Mat mat[maxn];

struct Node {
  int l, r;
  Mat v;
  Node *ls, *rs;

  inline void pushup() {
    v = ls->v * rs->v;
  }

  Mat qry(const int L, const int R) {
    if ((L <= l) && (r <= R)) return v;
    if ((r < L) || (l > R)) return Mat(0);
    return ls->qry(L, R) * rs->qry(L, R);
  }
};
Node Mem[maxn << 1], *pool = Mem;
Node *New(const int L, const int R) {
  auto u = pool++;
  if ((u->l = L) == (u->r = R)) {
    u->v = mat[L];
  } else {
    int M = (L + R) >> 1;
    u->ls = New(L, M);
    u->rs = New(M + 1, R);
    u->pushup();
  }
//  printf("OvO%d %d\n", L, R);
//  u->v.debug();
  return u;
}

void Main() {
  qr(t); qr(n); qr(m); qr(q);
  for (int i = 0; i < n; ++i) {
    bel[i] = i / t;
    res[i] = i - t * bel[i];
  }
  for (int u, v, w; m; --m) {
    qr(u); qr(v); qr(w);
    mat[bel[u]].mt[res[u]][res[v]] = w;
  }
  auto rot = New(0, bel[n - 1]);
  for (int u, v; q; --q) {
    qr(u); qr(v);
    if (bel[u] >= bel[v]) {
      puts("-1");
      continue;
    }
    auto k = rot->qry(bel[u], bel[v] - 1);
    int w = k.mt[res[u]][res[v]];
    qw(w == INF ? -1 : w, '\n');
  }
}

} // namespace Fusu
```

~~怎么最近做的全是矩乘题~~



---

## 作者：Jerrywang09 (赞：2)

我的第一篇文章区题解～

做法很多，本人使用线段树。

原图可以看作分层 DAG，每层结点有 $k$ 个，而 $k\le 5$。

假设每层的点编号 $0\sim k-1$。从 $l$ 到 $r$ 层的路径，在线段树上用区间 $[l,r-1]$ 表示。线段树上每个结点都存储表示最段路的矩阵，合并时使用 Floyd。

另外，需要特判询问中是否两个点在同一层里，这样一定不连通。

```cpp
// Title:  Toll
// Source: P6573
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=50010, M=5;
using namespace std;

int k, n, m, T; vector<pii> g[N][M];
struct node
{
    int l, r, d[M][M];
    void clr() {memset(d, 0x3f, sizeof d);}
} t[N<<2];
#define lc p<<1
#define rc p<<1|1
void up(node &a, node l, node r)
{
    a.clr();
    rep(w, 0, k-1) rep(u, 0, k-1) rep(v, 0, k-1)
        a.d[u][v]=min(a.d[u][v], l.d[u][w]+r.d[w][v]);
}
void build(int p, int l, int r)
{
    t[p]={l, r};
    if(l==r)
    {
        t[p].clr();
        rep(u, 0, k-1) for(auto [v,w]:g[l][u])
            t[p].d[u][v]=w;
        return;
    }
    int m=l+r>>1;
    build(lc, l, m), build(rc, m+1, r);
    up(t[p], t[lc], t[rc]);
}
node query(int p, int l, int r)
{
    if(l<=t[p].l && t[p].r<=r) return t[p];
    int m=t[p].l+t[p].r>>1; node res;
    if(r<=m) return query(lc, l, r);
    if(l>m)  return query(rc, l, r);
    up(res, query(lc, l, r), query(rc, l, r));
    return res;
}

int main()
{
    #ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin);
    #endif
    scanf("%d%d%d%d", &k, &n, &m, &T);
    rep(i, 1, m)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        g[u/k][u%k].push_back({v%k, w});
    }
    build(1, 0, n);
    while(T--)
    {
        int u, v; scanf("%d%d", &u, &v);
        int lu=u/k, lv=v/k;
        if(lu==lv) {puts("-1"); continue;}
        node t=query(1, lu, lv-1);
        int res=t.d[u%k][v%k];
        printf("%d\n", res==0x3f3f3f3f?-1:res);
    }

    return 0;
}
```

---

## 作者：wjh213 (赞：2)

观察数据范围，发现可以使用分块解决。

因为 $k\le 5$，$1\le n\le 50000$，考虑 $ 240\times 240 = 57600>50000$，且 $1\sim 5$ 中的所有数都可以被 $240$ 整除，所以以 $240$ 作为一个块的固定大小是比较合适的。

在每个块内，因为实际是 DAG，可以以 $O(\sqrt{n}^2)$ 的复杂度递推处理每个块内多源最短路，然后考虑如何合并各个块。

如果询问在同一个块，直接查表解决即可。否则考虑在经过每个块的时候只有前一个块的后 $k$ 个点会与下一个块的前 $k$ 个点连接。我们可以先找出 $x$ 到它自己的块的后 $k$ 个点的值的最短路，然后再递推到下一个块的前 $k$ 个点最短路，依此类推。

时间复杂度 $O(n\sqrt n +k^2\sqrt n )$。

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pr pair<int, int>
#define fi first
#define se second
int const INF = 0x3f3f3f3f3f3f3f3f;
int const MAX = 50500;
int const lg = 240;
bool st;
int dp[245][245][245];
vector<pr> V[MAX];
int dp2[2][7];
bool ed;
signed main() {
    auto qind = [&](int t1) { return t1 / lg; };
    auto qid = [&](int t1) { return t1 % lg; };
    auto toy = [&](int t1, int t2) { return t1 * lg + t2; };
    // cerr<<(&ed-&st)/1024.0/1024.0;
    int k, n, m, o;
    cin >> k >> n >> m >> o;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        V[u].push_back({ v, w });
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= n / lg; i++) {
        for (int j = 0; j < lg; j++) {
            if (toy(i, j) >= n)
                break;
            dp[i][j][j] = 0;
            for (int k = j; k < lg; k++) {
                if (toy(i, k) >= n)
                    break;
                for (auto qw : V[toy(i, k)]) {
                    int it = qw.fi;
                    if (qind(it) != i)
                        continue;
                    dp[i][j][qid(it)] = min(dp[i][j][qid(it)], dp[i][j][k] + qw.se);
                }
            }
        }
    }
    // for(int i=0;i<=n;i++){
    //	for(int j=0;j<=n;j++){
    //		cerr<<dp[0][i][j]<<" ";
    //	}
    //	cerr<<"\n";
    //}
    while (o--) {
        int x, y;
        cin >> x >> y;
        if (qind(x) == qind(y)) {
            int ans = dp[qind(x)][qid(x)][qid(y)];
            cout << (ans == INF ? -1 : ans) << "\n";
        } else {
            int l = qind(x), r = qind(y);
            memset(dp2, 0x3f, sizeof(dp2));
            for (int i = 0; i < k; i++) {
                dp2[l % 2][i] = dp[l][qid(x)][lg - (k - i)];
            }
            for (int i = l + 1; i < r; i++) {
                memset(dp2[i % 2], 0x3f, sizeof(dp2[i % 2]));
                int ls = i - 1;
                for (int j = 0; j < k; j++) {
                    if (dp2[ls % 2][j] == INF)
                        continue;
                    int tp = (ls + 1) * lg - (k - j);
                    for (auto it : V[tp]) {
                        for (int l = 0; l < k; l++) {
                            dp2[i % 2][l] =
                                min(dp2[i % 2][l], dp2[ls % 2][j] + it.se + dp[i][qid(it.fi)][lg - (k - l)]);
                        }
                    }
                }
            }
            int ans = INF;
            for (int i = 0; i < k; i++) {
                int ls = (r - 1);
                int tp = (ls + 1) * lg - (k - i);
                for (auto it : V[tp]) {
                    ans = min(ans, dp2[ls % 2][i] + it.se + dp[r][qid(it.fi)][qid(y)]);
                }
            }
            cout << (ans == INF ? -1 : ans) << "\n";
        }
    }
    return 0;
}
```

---

## 作者：lfxxx (赞：1)

考虑把所有点按照除以 $k$ 下取整的值分类。

然后所有边一定是类别为 $x$ 的点连向类别为 $x+1$ 的点，也就是一张分层图。

然后每一层的边数只有 $k$，所以考虑将相邻两层之间的转移矩阵维护出来，那么从点 $u$ 到点 $v$ 的路径就是一个长度为 $k$ 的向量与两点所在层间的转移矩阵乘起来，这里的乘是 $c_{i,j} = \min(a_{i,k} + b_{k,j})$。

由于是静态的，所以考虑线段树先 $O(n k^3)$ 预处理出每一层的矩阵，然后查询时将 $O(\log n)$ 个矩阵与向量依次乘到一起，复杂度是 $O(q \log n k^2)$ 的。

至此本题得到解决。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 1e13+114;
const int maxn = 1e5+114;
struct Matrix{
    int a[5][5];
    int n,m;
    Matrix(int N=0,int M=0,int C=0){
        n=N,m=M;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++) a[i][j]=C;
    }
    Matrix operator*(const Matrix &x){
        Matrix res=Matrix(n,x.m,inf);
        for(int i=0;i<=n;i++)
            for(int k=0;k<=m;k++)
                for(int j=0;j<=x.m;j++) res.a[i][j]=min(res.a[i][j],a[i][k]+x.a[k][j]);
        return res;
    }
}e;
vector<int> edge[maxn];
Matrix a[maxn];
int n,k,m,q;
Matrix tr[maxn<<2];
void pushup(int cur){
    tr[cur]=tr[cur<<1]*tr[cur<<1|1];
}
void build(int cur,int lt,int rt){
    if(lt==rt){
        tr[cur]=a[lt];
        return ;
    }
    int mid=(lt+rt)>>1;
    build(cur<<1,lt,mid);
    build(cur<<1|1,mid+1,rt);
    pushup(cur);
    return ;
}
vector<Matrix> nxt;
void ask(int cur,int lt,int rt,int l,int r){
    if(rt<l||r<lt) return ;
    if(l<=lt&&rt<=r){
        nxt.push_back(tr[cur]);
        return ;
    }
    int mid=(lt+rt)>>1;
    ask(cur<<1,lt,mid,l,r);
    ask(cur<<1|1,mid+1,rt,l,r);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>k>>n>>m>>q;
    e=Matrix(k-1,k-1,inf);
    for(int i=0;i<=k-1;i++)
        for(int j=0;j<=k-1;j++) e.a[i][j]=0;
    for(int i=1;i<=(n/k)+1;i++) a[i]=Matrix(k-1,k-1,inf);
    for(int i=1;i<=m;i++){
        int u,v,t;
        cin>>u>>v>>t;
        a[(u/k)+1].a[u%k][v%k]=min(a[(u/k)+1].a[u%k][v%k],t);
    }
    build(1,1,(n/k)+1);
    while(q--){
        int u,v;
        cin>>u>>v;
        if((u/k)>=(v/k)) cout<<"-1\n";
        else{
            Matrix now=Matrix(0,k-1,inf);
            now.a[0][u%k]=0;
            nxt.clear();
            ask(1,1,(n/k)+1,(u/k)+1,(v/k));
            for(Matrix x:nxt) now=now*x;
            cout<<(now.a[0][v%k]>=inf?-1:now.a[0][v%k])<<'\n';
        }
    }
    return 0;
}
```


---

## 作者：bigmurmur (赞：1)

# 思路流程

先观察题目，发现这是一个分层图，并且询问最短路，肯定是一道DP类的题目。

发现询问超级多，如果暴力跑DP肯定会T掉，于是观察分层图每层的点数，只有最多5个，说明相邻两层的点相连关系可以用矩阵（临接矩阵）表示。

建临接矩阵时可以把在左侧的一层点命名为 $0$ ~ $K$ , 把右侧的一层点命名为 $K+1$ ~ $2K$

如样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/573xszb1.png)

可以初步建出 $1$ -> $2$ , $2$ -> $3$ 层的临接矩阵
```
1-2。
INF	INF	INF	INF	INF	9	INF	7	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	10	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF
```

2-3。（此处 $5$ ~ $9$ 节点为了方便存储暂时命名为 $0$ ~ $4$ , $10$ ~ $13$ 命名为 $5$ ~ $8$ ）

```
INF	INF	INF	INF	INF	INF	INF	10	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	8	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF	
INF	INF	INF	INF	INF	INF	INF	INF	INF	INF
```


考虑拥有 $1$ -> $2$  和 $2$ -> $3$ 层的临接矩阵后如何得到 $1$ -> $3$ 的最短路矩阵

再广义一点，就是说我们已经能够得到 $a$ -> $b$ 层 和 $b$ -> $c$ 层的最短路矩阵，如何得到 $a$ -> $c$ 层的最短路矩阵。

此时我们需要用到的点共有三层。其中这三层的点命名不能重合，不妨令最左边的 $a$ 层点的编号为 $0$ ~ $K$ ,同理可得：$b$ 层： $K+1$ ~ $2K$ , c层 : $2K+1$ ~ $3K$

观察发现左边的 $a$ -> $b$ 层矩阵中的点编号也是 $0$ ~ $K$ 和 $K+1$ ~ $2K$,运算过程中该最短路矩阵不需要改变。

很遗憾的是 $b$ -> $c$ 层矩阵中的点编号也是 $0$ ~ $K$ 和 $K+1$ ~ $2K$ ，那么在运算过程中需要把矩阵二的点编号重排一下,转成 $2K+1$ ~ $3K$，从而变成一个 $3K \times 3K$ 的矩阵：
```
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF 10  INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF 8   INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF 
INF INF INF INF INF INF INF INF INF INF INF INF INF INF INF
```

那么根据我们以往的方法，直接用矩阵一乘上矩阵二就可以得到 $a$ ~ $c$ 层的最短路矩阵

这里的乘法定义为 :

 $(A \times B)_{i,j} =\min_{p=0}^{K-1} (A_{i,x} + B_{x,j})$
 
 不难发现矩阵相乘的运算法则类似于做了一遍奇怪的 $Floyed$ 。
 
 $Tip.$ 算完之后记得把 $c$ 层点的编号($2K+1$ ~ $3K$ ) 转回 $K+1$ ~ $2K$ 的点编号形式得到一个 $2K \times 2K$ 的 $a$ -> $c$ 最短路矩阵
 
 至此，我们还需要能在 $O(logn \times K^3)$ 求出任意两层点的最短路矩阵
 
 不难考虑到线段树，RMQ等算法
 
 这里给出线段树的做法及代码
 
 ```cpp
#include <cstdio>
#include <cstring>
using namespace std;
inline int getint() {
    char c;
    int ans = 0;
    while (c = getchar(), c > '9' || c < '0');
    while (ans = ans * 10 + c - '0', c = getchar(), c >= '0' && c <= '9');
    return ans;
}
const int N = 50010, M = 11, H_M = 16;
int n, m, K, q;
int id[N];
struct H_Matrix {
    int m[H_M][H_M];
};
struct Matrix {
    int m[M][M];
} null;
struct Segment {
    int l, r, ls, rs;
    Matrix dat;
} t[N << 2];
struct Map {
    Matrix g;
} a[N];
int pug[N];
int sum_g, Root, tot;

inline int min(int a, int b) { return a < b ? a : b; }
inline void print(H_Matrix x) {
    for (register int i = 1; i <= (K << 1) + K; ++i) {
        for (register int j = 1; j <= (K << 1) + K; ++j)
            if (x.m[i][j] >= 0x3f3f3f3f)
                printf("INF ");
            else
                printf("%d   ", x.m[i][j]);
        puts("");
    }
    puts("");
}
Matrix operator * (Matrix a, Matrix b) {
	//这里直接在乘法中进行编号扩展，再赋值回去，能省很多空间。
    int sx = K << 1;
    Matrix res;
    H_Matrix c, ans;
    memset(ans.m, 0x3f, sizeof ans.m);
    memset(c.m, 0x3f, sizeof c.m);
    memset(res.m, 0x3f, sizeof res.m);
    for (register int i = K + 1; i <= sx + K; ++i)
        for (register int j = K + 1; j <= sx + K; ++j) c.m[i][j] = b.m[i - K][j - K];
    for (register int i = 1; i <= sx + K; ++i) {
        for (register int k = 1; k <= sx + K; ++k) {
            for (register int j = 1; j <= sx + K; ++j) {
                ans.m[i][j] = min(ans.m[i][j], a.m[i][k] + c.m[k][j]);
            }
        }
    }
    for (register int i = 1; i <= K; ++i) {
        for (register int j = sx + 1; j <= sx + K; ++j) {
            res.m[i][j - K] = ans.m[i][j];
        }
    }
    return res;
}

inline void update(int p) {
    if (t[p].ls && t[p].rs)
        t[p].dat = t[t[p].ls].dat * t[t[p].rs].dat;
    else
        t[p].dat = t[t[p].ls | t[p].rs].dat;
}
inline void build_tree(int &p, int left, int right) {
    if (!p)
        p = ++tot;
    t[p].l = left, t[p].r = right;
    if (left == right) {
        t[p].dat = a[left].g;
        return;
    }
    int mid = left + right >> 1;
    build_tree(t[p].ls, left, mid);
    build_tree(t[p].rs, mid + 1, right);
    update(p);
}
inline Matrix ask(int p, int left, int right) {
    if (!p)
        return null;
    if (t[p].l >= left && t[p].r <= right)
        return t[p].dat;
    int mid = t[p].l + t[p].r >> 1;
    if (left <= mid && right <= mid)
        return ask(t[p].ls, left, right);
    if (left > mid && right > mid)
        return ask(t[p].rs, left, right);
    if (left <= mid && right > mid)
        return ask(t[p].ls, left, right) * ask(t[p].rs, left, right);
}
signed main() {
    memset(null.m, 0, sizeof null.m);
    K = getint(), n = getint(), m = getint(), q = getint();
    if (n % K)
        n = n / K * K + K;
    for (register int i = 1; i <= n; ++i) id[i] = (i - 1) / K + 1;
    sum_g = n / K;
    int a_, b, t;
    for (register int i = 1; i < sum_g; ++i) {
        memset(a[i].g.m, 0x3f, sizeof a[i].g.m);
    }
    for (register int i = 1; i <= m; ++i) {
        a_ = getint(), b = getint(), t = getint();
        ++a_, ++b;
        a[id[a_]].g.m[(a_ - 1) % K + 1][(b - 1) % K + 1 + K] = t;
    }
    build_tree(Root, 1, sum_g - 1);
    while (q--) {
        a_ = getint(), b = getint();
        if (a_ == b) {
            puts("0");
            continue;
        }
        ++a_, ++b;
        if (id[a_] >= id[b]) {
            puts("-1");
            continue;
        }
        Matrix ans = ask(1, id[a_], id[b] - 1);
        int p = ans.m[(a_ - 1) % K + 1][(b - 1) % K + 1 + K];
        if (p >= 0x3f3f3f3f)
            puts("-1");
        else
            printf("%d\n", p);
    }
    return 0;
}


 
 ```



---

## 作者：翼德天尊 (赞：1)

观察到题目中的特殊式子有些怪异，且 $k$ 又十分小，仔细思考一下，发现其实就相当于是给定了一张每一层节点个数都为 $k$ 的分层 DAG.

先思考一下朴素的算法应该怎么做：不妨设 $dp_i$ 表示到达 $i$ 的最少价钱，则每次询问就需要从 $a$ 到 $b$ 跑一边类似于拓扑排序的过程，状态转移方程为：
$$
dp_u=\min_{v\to u}(dp_v+t_{v,u})
$$
考虑到 $k$ 十分小，所以我们可以将每一层节点的转移方程压成一个转移矩阵（矩阵相较于普通转移方程，额外满足了结合律）此时我们便可以使用数据结构维护转移矩阵的区间积，此时对于每次询问，我们只需要知道 $a$ 和 $b$ 所在的层数，在数据结构中查到转移矩阵，用初始向量与之相乘即可。

时间复杂度 $O(nk^3+qk^3\log n)$.

注意到瓶颈是在查询，将查询时的矩阵乘矩阵优化为向量乘矩阵可以优化掉一个常数  $k$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=50005;
const int K=5;
const int INF=1e15;
int p,n,m,q;
struct Matrix{
	int a[K][K];
	Matrix(){
		memset(a,0x3f,sizeof(a));
	}
}Z[N],ans;
Matrix operator*(const Matrix&x,const Matrix&y){
	Matrix z;
	for (int k=0;k<p;k++)
		for (int i=0;i<p;i++)
			for (int j=0;j<p;j++)
				z.a[i][j]=min(z.a[i][j],x.a[i][k]+y.a[k][j]);
	return z;
}
struct Tree{
	Matrix t[N<<2];
	void pushup(int i){
		t[i]=t[i<<1]*t[i<<1|1];
	}
	void build(int i,int l,int r){
		if (l==r){
			t[i]=Z[l];
			return;
		}
		int mid=l+r>>1;
		build(i<<1,l,mid);
		build(i<<1|1,mid+1,r);
		pushup(i);
	}
	void query(int i,int l,int r,int ql,int qr){
		if (ql<=l&&r<=qr){
			ans=ans*t[i];
			return;
		}
		int mid=l+r>>1;
		if (ql<=mid) query(i<<1,l,mid,ql,qr);
		if (mid<qr) query(i<<1|1,mid+1,r,ql,qr);
	}
}T;
int read(){
	int w=0,f=1;
	char ch=getchar();
	while (ch>'9'||ch<'0') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}
int bel(int x){
	return (x-1)/p+1;
}
int quyu(int x){
	return (x-1)%p;
}
signed main(){
	p=read(),n=read(),m=read(),q=read();
	for (int i=1;i<=m;i++){
		int u=read()+1,v=read()+1,now=bel(u),w=read();
		int uy=quyu(u),vy=quyu(v);
		Z[now].a[uy][vy]=w;
	}
	int all=bel(n);
	T.build(1,1,all);
	while (q--){
		int x=read()+1,y=read()+1,bx=bel(x),by=bel(y),ux=quyu(x),uy=quyu(y);
		if (bx==by) puts("-1");
		else{
			for (int i=0;i<p;i++)
				if (i==ux) ans.a[0][i]=0;
				else ans.a[0][i]=INF;
			T.query(1,1,all,bx,by-1);
			if (ans.a[0][uy]>=1e9) puts("-1");
			else cout<<ans.a[0][uy]<<"\n";
		}
	}
	return 0;  
}

```

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑 DP。定义状态函数 $f_{i,0/1}$ 表示走到点 $i$，且现在没有或有船时的最小代价。记 $v$ 为上一步的点，$u$ 为当前点。那么有：

$$
f_{u,0}=\min(f_{v,0},f_{v,1})+w1_{v,u}\\
f_{u,1}=\min(f_{v,1}+w2_{v,u},f_{v,0}+L+w2_{v,u})
$$

其中 $w1_{u,v}=a_i,w2_{u,v}=a_i +z_i(a_i-z_i)$。

边权转点权。

$$
f_{u,0}=\min(f_{v,0},f_{v,1})+w1_{u}\\
f_{u,1}=\min(f_{v,1}+w2_{u},f_{v,0}+L+w2_{u})
$$

我们树剖维护，写成矩阵的形式：

$$
\begin{bmatrix} f_{n-1,0} & f_{n-1,1} \end{bmatrix}
\begin{bmatrix} w1_u & w2_u+L \\ w1_u & w2_u \end{bmatrix}
=
\begin{bmatrix} f_{n,0} & f_{n,1} \end{bmatrix}
$$

这是个 $(\min,+)$ 矩阵。做完了，时间复杂度 $O(n\log^2 n)$。

## 代码

```cpp
const int N=2e5+10;
int n,L,m;
int w1[N],w2[N],w3[N];
struct node{int y,a,z,type;};
vector<node> e[N];
struct Tree{
	int l,r;
	int c[2][2][2];
}tr[N<<2];
int dep[N],siz[N],mson[N],f[N];
int top[N],dfn[N],id[N],cnt;

il void dfs1(int u,int fa){
	f[u]=fa,dep[u]=dep[fa]+1,siz[u]=1;
	for(auto v:e[u])
	if(v.y!=fa){
		dfs1(v.y,u);
		siz[u]+=siz[v.y];
		if(siz[mson[u]]<siz[v.y]) mson[u]=v.y;
		w1[v.y]=v.a;
		w2[v.y]=v.a+(v.type==0?(-1):1)*v.z;//从v到u 
		w3[v.y]=v.a+(v.type==1?(-1):1)*v.z;//从u到v 
	}
	return ;
}
il void dfs2(int u,int tp){
	top[u]=tp,dfn[u]=++cnt,id[cnt]=u;
	if(mson[u]) dfs2(mson[u],tp);
	for(auto v:e[u])
	if(v.y!=f[u]&&v.y!=mson[u]) dfs2(v.y,v.y);
	return ;
}
il void up(Tree &u,Tree x,Tree y){
	for(re int i=0;i<2;++i)
	for(re int j=0;j<2;++j)
		u.c[0][i][j]=min(y.c[0][i][0]+x.c[0][0][j],y.c[0][i][1]+x.c[0][1][j]);
	for(re int i=0;i<2;++i)
	for(re int j=0;j<2;++j)
		u.c[1][i][j]=min(x.c[1][i][0]+y.c[1][0][j],x.c[1][i][1]+y.c[1][1][j]);	
	return ;
}
il void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r;
	if(l==r){
		int x=id[l];
		memset(tr[u].c,0x3f,sizeof(tr[u].c));
		tr[u].c[0][0][0]=tr[u].c[0][1][0]=w1[x];
		tr[u].c[0][0][1]=w2[x]+L,tr[u].c[0][1][1]=w2[x];
		tr[u].c[1][0][0]=tr[u].c[1][1][0]=w1[x];
		tr[u].c[1][0][1]=w3[x]+L,tr[u].c[1][1][1]=w3[x];
		return ;		
	}
	int mid=l+r>>1;
	build(ls(u),l,mid),build(rs(u),mid+1,r);
	return up(tr[u],tr[ls(u)],tr[rs(u)]),void(0);
}
il Tree query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r) return tr[u];
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid&&mid< r){
		Tree res;
		memset(&res,0x3f,sizeof(res));
		up(res,query(ls(u),l,r),query(rs(u),l,r));
		return res;
	}
	if(l<=mid) return query(ls(u),l,r);
	if(mid< r) return query(rs(u),l,r);
}
il int Query(int x,int y){
	Tree A,B,V;
	memset(&A,0x3f,sizeof(A));
	memset(&B,0x3f,sizeof(B));
	memset(&V,0x3f,sizeof(V));
	for(re int k=0;k<2;++k)
	for(re int i=0;i<2;++i)
		A.c[k][i][i]=B.c[k][i][i]=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>=dep[top[y]]){
			Tree U=query(1,dfn[top[x]],dfn[x]);
			x=f[top[x]],up(A,U,A);
		}
		else{
			Tree U=query(1,dfn[top[y]],dfn[y]);
			y=f[top[y]],up(B,U,B);
		}
	}
	if(dep[x]>dep[y]){
		Tree U=query(1,dfn[y]+1,dfn[x]);
		up(A,U,A);
	}
	if(dep[y]>dep[x]){
		Tree U=query(1,dfn[x]+1,dfn[y]);
		up(B,U,B);		
	}
	for(re int i=0;i<2;++i)
	for(re int j=0;j<2;++j) swap(A.c[0][i][j],A.c[1][i][j]);
	up(A,A,B),V.c[1][0][0]=0,up(V,V,A);
	return min(V.c[1][0][0],V.c[1][0][1]);
}

il void solve(){
	n=rd,L=rd,m=rd;
	for(re int i=1;i< n;++i){
		int u=rd,v=rd,a=rd,z=rd,type=rd;
		e[u].push_back({v,a,z,type}),
		e[v].push_back({u,a,z,type^1});
	}
	dfs1(1,0),dfs2(1,1),build(1,1,n);
	while(m--){
		int x=rd,y=rd;
		printf("%lld\n",Query(x,y));
	}
    return ;
}
```

---

## 作者：Helloworldwuyuze (赞：0)

# P6573 [BalticOI 2017] Toll

## Des

$n$ 个点 $m$ 条边的有向图，每条边形如 $(x,y,z)$ 表示 $x\to y$ 且权值为 $z$，$q$ 次询问 $(x,y)$ 的最短路。其中每条边保证 $\frac{x}{k} +1 = \frac{y}{k}$。

## Sol

考虑将点每 $k$ 个分成一块，那么就只能够从第 $i$ 块到第 $i+1$ 块的路径。

而我们又知道最短路是可以用传递闭包转移的。

这里的 $k$ 很小，正好适合我们从 $i$ 转移到 $i+1$ 块。

因此，对于一条路径 $(x,y,k)$，我们在 $\frac{x}{k}\to \frac{y}{k}$ 的转移矩阵上设置 $a_{x\bmod k,y\bmod k} = z$，那么答案就是：
$$
(\prod_{i=\frac{x}{k}}^{\frac{y}{k}-1} A_i)_{x\bmod k,y\bmod k}
$$
然后区间的矩阵乘法使用线段树即可。

代码也十分好写，矩阵类加上线段树即可。

```cpp
const int INF = 0x3f3f3f3f;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
const int N = 5e4 + 10;
const int MOD = 998244353;
inline int min(int x,int y){ return x < y ? x : y; }
inline int max(int x,int y){ return x < y ? y : x; }

struct matrix{
	int a[5][5], n, m;
	matrix(){ n = m = -1; memset(a, 0x3f, sizeof(a)); }
	matrix(int _n, int _m) : n(_n), m(_m) { memset(a, 0x3f ,sizeof(a)); }
	inline void E(int _n){ n = m = _n; for(int i=0;i<n;++i) for(int j=0;j<n;++j) a[i][j] = (i == j) ? 0 : INF; }
}t[N<<2], mat[N];

matrix operator *(const matrix &x, const matrix &y){
	matrix ans(x.n, y.m);
	if(x.m != y.n)	return matrix();
	for(int i=0;i<x.n;++i)
		for(int j=0;j<y.m;++j)
			for(int k=0;k<x.m;++k)
				ans.a[i][j] = min(ans.a[i][j], x.a[i][k] + y.a[k][j]);
	return ans;
}

int n, k, m, q;
void build(int p,int l,int r){
	if(l == r)	return t[p] = mat[l], void();
	int mid = l+r>>1;
	build(p<<1, l, mid), build(p<<1|1, mid+1, r);
	t[p] = t[p<<1] * t[p<<1|1];
}
matrix query(int p,int l,int r,int left,int right){
	if(left <= l && r <= right)	return t[p];
	int mid = l+r>>1;
	matrix ls(k, k), rs(k, k); ls.E(k), rs.E(k);
	if(left <= mid)	ls = query(p<<1, l, mid, left, right);
	if(right > mid)	rs = query(p<<1|1, mid+1, r, left, right);
	return ls * rs;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>k>>n>>m>>q;
	for(int i=1,x,y,z;i<=m;++i){
		cin>>x>>y>>z;
		mat[x/k].a[x%k][y%k] = z;
	}
	for(int i=0;i<=n/k;++i)	mat[i].n = mat[i].m = k;//, mat[i].print();
	build(1, 0, n/k);
	while(q--){
		int x, y; cin>>x>>y;
		if(x == y){ cout<<0<<endl; continue; }
		if(x / k == y / k){ cout<<-1<<endl; continue; }
		matrix tmp = query(1, 0, n/k, x/k, y/k-1);
		if(tmp.a[x%k][y%k] == INF)	cout<<-1<<endl;
		else	cout<<tmp.a[x%k][y%k]<<endl;
	}
	return 0;
}
```

---

## 作者：Forever1507 (赞：0)

## P6573

简要题意：多次询问，任意查询有向图中两点最短路。特别的，图中所有边 $(a,b)$ 都满足 $\lfloor\frac{b}{k}\rfloor=1+\lfloor\frac{a}{k}\rfloor$。

感觉边的限制条件基本已经在明示做法了啊（？

考虑以块长为 $k$ 分块，就会发现一条边只会从左往右连接相邻的两个块，于是图上问题就转化成了一个序列问题。

只对相邻的位置有直接贡献的序列问题非常自然的想到倍增，具体来说：$f_{i,j,k,p}$ 表示第 $i$ 个块的第 $j$ 个点跳到第 $i+2^k$ 个块的第 $p$ 个点（为了方便理解才这么写，实际编写代码的过程中显然应该把 $i,j$ 压到一位里）的最小代价，转移的话直接合并就可以了。

然后查询的时候也是一个特别平凡的倍增，直接枚举最大能跳的步数直接跳就可以了。

时间复杂度 $O(n\log n k^2)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,m,o;
int f[50005][16][6];
#define pii pair<int,int>
#define fi first
#define se second
pii get(int x){
    return {x/k,x%k};
}
int calc(int i,int j){
    return i*k+j;
}
int ans[6],tmp[6];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>k>>n>>m>>o;
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        f[u][0][get(v).se]=w;
    }
    for(int len=1;len<=16;++len){
        for(int i=0;i+(1<<len)<=n/k;++i){
            for(int p=0;p<k;++p){
                for(int q=0;q<k;++q){
                    for(int t=0;t<k;++t){
                        f[calc(i,p)][len][q]=min(f[calc(i,p)][len][q],f[calc(i,p)][len-1][t]+f[calc(i+(1<<len-1),t)][len-1][q]);
                    }
                }
            }
        }
    }
    while(o--){
        int a,b;
        cin>>a>>b;
        if(get(a).fi>=get(b).fi){
            cout<<-1<<'\n';
            continue;
        }
        memset(ans,0x3f,sizeof(ans));
        ans[get(a).se]=0;
        int now=get(a).fi;
        for(int i=16;i>=0;--i){
            if(get(b).fi-now>=(1<<i)){
                memcpy(tmp,ans,sizeof(tmp));
                memset(ans,0x3f,sizeof(ans));
                for(int j=0;j<k;++j){
                    for(int p=0;p<k;++p){
                        ans[p]=min(ans[p],tmp[j]+f[calc(now,j)][i][p]);
                    }
                }
                now+=(1<<i);
            }
        }
        if(ans[get(b).se]>1e9)ans[get(b).se]=-1;
        cout<<ans[get(b).se]<<'\n';
    }
    return 0;
}
```

---

## 作者：Nangu (赞：0)

一个与现有题解都不相同的思路，无需线段树、矩阵乘法。

题意就是一个有向图，每条边都保证只跨越相邻的块，多次询问两点间最短路。

对于一个询问 $u, v$，其所在的块分别为 $bu, bv$，显然当 $bu<bv$ 答案才可能不为 $-1$。$bu+1=bv$ 是平凡的，考虑 $bu+1<bv$，则必有对于任意一个块 $bk$ 满足 $bu<bk$ 且 $bk<bv$，有 $u$ 到 $v$ 的最短路内包含且仅包含块 $bk$ 内的一点。因此可以对任意一个 $bk$ 中的所有点求最短路，则两端点分别在块 $bk$ 两侧的答案即为 $\min dis_u+dis_v$。

于是考虑分治，每次枚举中间块 $bk$，可将两端点分别在 $bk$ 两侧的点的答案求出，再向左右两边递归即可。

时间复杂度 $O(kn\log^2n)$，常数较小。

```cpp
#include<bits/stdc++.h>
#define rep(i, j, k) for(int i=(j); i<=(k); ++i)
#define per(i, j, k) for(int i=(j); i>=(k); --i)
#define G(v, i, u) for(int i=head[u], v=e[i].v; i; v=e[i=e[i].nxt].v)
#define de(x) cout<<#x<<" "<<x<<"  "
#define nd cout<<endl
#define fin(x) freopen(x, "r", stdin)
#define fout(x) freopen(x, "w", stdout)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N=5e4+7;
const ll INF=1e15;
struct node{
    int v; ll w;
    bool operator<(const node a) const{
        return w>a.w;
    }
};
priority_queue<node> q;
struct query{
    int u, v, id;
};
int k, n, m, o;
ll dis1[N], dis2[N], res[N];
vector<pii> G[N], H[N];

void dij(int l, int r, int st, ll *dis, vector<pii> *G){
    fill(dis+l, dis+r+1, INF);
    q.push({st, dis[st]=0});
    while(!q.empty()){
        int u=q.top().v; ll w=q.top().w; q.pop();
        if(w!=dis[u]) continue;
        for(auto v:G[u]) 
            if(dis[v.first]>w+v.second && l<=v.first && v.first<=r) 
                q.push({v.first, dis[v.first]=w+v.second});
    }
}

void solve(int l, int r, vector<query> &q){
    if(l>r) return;
    int mid=l+r>>1;
    vector<query> ls, rs, now;
    for(auto x:q)
        if(x.v/k<mid)
            ls.emplace_back(x);
        else if(x.u/k>mid)
            rs.emplace_back(x);
        else 
            now.emplace_back(x);
    solve(l, mid-1, ls), solve(mid+1, r, rs);
    rep(u, mid*k, mid*k+k-1){
        dij(l*k, mid*k+k-1, u, dis1, H);
        dij(mid*k, r*k+k-1, u, dis2, G);
        for(auto x:now) res[x.id]=min(res[x.id], dis1[x.u]+dis2[x.v]);
    }
}

signed main(){
    // fin("toll.in"), fout("toll.out");
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin>>k>>n>>m>>o;
    rep(i, 1, m){
        int u, v, w;
        cin>>u>>v>>w;
        G[u].emplace_back(v, w);
        H[v].emplace_back(u, w);
    }
    vector<query> q; query tmp;
    rep(i, 0, o-1){
        cin>>tmp.u>>tmp.v, tmp.id=i;
        if(tmp.u/k>tmp.v/k) continue;
        q.emplace_back(tmp);
    }
    fill(res, res+o, INF);
    solve(0, (n-1)/k, q);
    rep(i, 0, o-1) cout<<(res[i]==INF?-1:res[i])<<'\n';
}

---

