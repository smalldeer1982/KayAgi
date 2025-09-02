# [ABC348E] Minimize Sum of Distances

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc348/tasks/abc348_e

$ N $ 頂点からなる木が与えられます。頂点は $ 1 $ から $ N $ までの番号がついており、 $ i $ 番目の辺は頂点 $ A_i,\ B_i $ を結んでいます。

長さ $ N $ の正整数列 $ C\ =\ (C_1,\ C_2,\ \ldots\ ,C_N) $ が与えられます。$ d(a,\ b) $ を頂点 $ a,\ b $ の間にある辺の数とし、 $ x\ =\ 1,\ 2,\ \ldots\ ,N $ に対して $ \displaystyle\ f(x)\ =\ \sum_{i=1}^{N}\ (C_i\ \times\ d(x,\ i)) $ とします。$ \displaystyle\ \min_{1\ \leq\ v\ \leq\ N}\ f(v) $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 与えられるグラフは木である。
- $ 1\ \leq\ C_i\ \leq\ 10^9 $

### Sample Explanation 1

例として、 $ f(1) $ を求めることを考えます。$ d(1,\ 1)\ =\ 0,\ d(1,\ 2)\ =\ 1,\ d(1,\ 3)\ =\ 1,\ d(1,\ 4)\ =\ 2 $ です。 よって、 $ f(1)\ =\ 0\ \times\ 1\ +\ 1\ \times\ 1\ +\ 1\ \times\ 1\ +\ 2\ \times\ 2\ =\ 6 $ となります。 同様に、 $ f(2)\ =\ 5,\ f(3)\ =\ 9,\ f(4)\ =\ 6 $ です。$ f(2) $ が最小なので `5` を出力します。

### Sample Explanation 2

$ f(2)\ =\ 1 $ で、これが最小です。

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
1 1 1 2```

### 输出

```
5```

## 样例 #2

### 输入

```
2
2 1
1 1000000000```

### 输出

```
1```

## 样例 #3

### 输入

```
7
7 3
2 5
2 4
3 1
3 6
2 1
2 7 6 9 3 4 6```

### 输出

```
56```

# 题解

## 作者：f_hxr_ (赞：42)

[锣鼓传送门](https://www.luogu.com.cn/problem/AT_abc348_e) [AT 传送门](https://atcoder.jp/contests/abc348/tasks/abc348_e)

[双倍经验](https://www.luogu.com.cn/problem/P2986)

[三倍经验](https://www.luogu.com.cn/problem/AT_abc220_f)

[四倍经验](https://www.luogu.com.cn/problem/CF1092F)

[五倍经验](https://www.luogu.com.cn/problem/P3478)

[六倍经验](https://www.luogu.com.cn/problem/CF1187E)

[七倍经验](https://www.luogu.com.cn/problem/P1395)

[八倍经验](https://www.luogu.com.cn/problem/P1364)

先考虑暴力做法。

如何求出结点 $i$ 的答案呢？显然可以直接从结点 $i$ 开始 DFS 一遍就行。

这样的时间复杂度为 $O(N^2)$。怎么优化呢？

请看下面这张图片：

![](https://cdn.luogu.com.cn/upload/image_hosting/uzpmsjpj.png)

定义 $size_u$ 表示 $u$ 的子树内所有结点的 $C$ 的和，$ALL$ 为所有结点的 $C$ 的和。

如图，假设钦定 $0$ 为根节点，并已经计算出了以 $0$ 为根节点的答案，现在该如何计算以 $2$ 为根节点的答案呢？

我们发现，整棵树可以分成两部分，一部分是 $2$ 的子树，我们叫它 $A$，即蓝框框起来的地方。剩下的一部分我们叫它 $B$，也就是用黄框框起来的地方。

我们注意到，$A$ 部分的每个结点到结点 $2$ 的距离，正好比到结点 $0$ 的距离多 $1$（显然自己到自己的距离是 $0$）。

由于每个结点的贡献和距离成正比。距离多 $1$，也就意味着答案也要增加。

增加多少呢？当然就是 $A$ 部分的大小。即 $ALL-size_2$。

换句话说，$ans_2=ans_0+\text{A的大小}$。

上面的式子不完整，还有一个 $B$ 呢！同理可得，由于 $B$ 到 $2$ 的距离比到 $0$ 的距离要短，答案也要少一个 $B$。即 $ans_2=ans_0+\text{A的大小}-\text{B的大小}$。

$B$ 的大小也就是 $size_2$。

这样我们通过 $ans_0$ 推出了 $ans_2$。聪明的你突发奇想，可不可以继续向下推呢？当然可以。我们也可以推出 $2$ 的儿子的答案，儿子的儿子的答案……。

等等，这个过程不就是又一个 DFS 吗？

总结一下我们的算法流程：

1. 先钦定一个结点为根，暴力预处理一遍它得答案。并求出其子树大小。

2. 然后从根节点开始 DFS，按照上面的方法递推出每个该结点的答案。

3. 取最小值即可。时间复杂度 $O(N)$。

这种方法叫“换根 DP”，也叫“二次换根与扫描法”。你也可以在各种各样的算法书上看到这类题，也算是经典咏流传了。~~不然为什么有八倍经验。~~

[AC ](https://www.luogu.com.cn/record/154736491)代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+7;
const long long inf=1e20+7;
int N;
long long f[maxn],dep[maxn],sz[maxn],ALL,coin[maxn];
int head[maxn<<1],nxt[maxn<<1],to[maxn<<1],cnt_edge;
void AddEdge(int u,int v)
{nxt[++cnt_edge]=head[u];to[cnt_edge]=v;head[u]=cnt_edge;}
void dfs(int u,int fa,long long dep){
	f[1]+=coin[u]*dep;sz[u]=coin[u];
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];if(v==fa)continue;
		dfs(v,u,dep+1);sz[u]+=sz[v];
	}
}
void solve(int u,int fa,long long ans){
	f[u]=ans;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];if(v==fa)continue;
		long long dans=ans;
		dans-=sz[v];dans+=ALL-sz[v];//递推计算，你没看错，就这么简单。
		solve(v,u,dans);
	}
}
int main(){
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{int a,b;scanf("%d %d",&a,&b);AddEdge(a,b);AddEdge(b,a);}
	for(int i=1;i<=N;i++)scanf("%lld",&coin[i]),ALL+=coin[i];
	dfs(1,0,0);solve(1,0,f[1]);
	f[0]=inf;for(int i=1;i<=N;i++)f[0]=min(f[0],f[i]);
	printf("%lld",f[0]);
	return 0;
}
```

---

## 作者：___PatrickChen___ (赞：11)

#### 题目大意

给你一棵有 $N$ 个顶点的树。顶点编号为 $1$ 到 $N$，第 $i$  条边连接顶点 $A_i$ 和 $B_i$ 。

我们还给出了一个长度为 $N$ 的正整数序列 $C=(C_1,C_2, \ldots,C_N)$。设 $d(a,b)$ 是顶点 $a$ 和 $b$ 之间的距离，对于任意的 $x=1,2,\ldots,N$，有 $\displaystyle f(x) =\sum_{i=1}^{N}(C_i\times d(x,i))$。求 $\displaystyle \min_{1\le v\le N}f(v)$。

#### 解法

首先注意到这是一棵树，考虑使用树形 dp。

设 $s_i$ 表示以 $i$ 为根的子树的点权之和，当前节点为 $u$，更新节点为 $v$。我们把转移方程式分为两部分来考虑：
- 到 $v$ 的子树中的所有节点的距离减少 $1$，所以减去 $v$ 的子树中的点权和 $s_v$。
- 到非 $v$ 的子树中的所有节点的距离增加 $1$，所以加上非 $v$ 的子树中的点权和 $s_1-s_v$。

那么我们最终得到的转移方程式就是 $f_v=f_u-s_v+(s_1-s_v)$。

使用两次 dfs，第一次计算 $s$ 和 $f_1$，第二次进行 dp 即可。

代码：
```cpp
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

using ll=long long;

int n,head[100005],d[100005];//d 表示深度
ll a[100005],s[100005],f[100005],ans=LONG_LONG_MAX;
struct edge{
	int v,next;
}e[200005];

void add(int u,int v){
	static int cnt=0;
	e[++cnt]={v,head[u]};
	head[u]=cnt;
}

void dfs1(int u,int fa){
	f[1]+=d[u]*a[u];//计算 f[1]：由于 d[0] 为 0，所以根节点到 u 的距离为 d[u]
	s[u]=a[u];//初始化 s
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa)continue;
		d[v]=d[u]+1;//计算深度 d[v]
		dfs1(v,u);
		s[u]+=s[v];//计算 s[u]
	}
}

void dfs2(int u,int fa){
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa)continue;
		f[v]=f[u]-s[v]*2+s[1];//dp
		dfs2(v,u);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for(int i=1,u,v;i<n;++i){
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;++i)cin >> a[i];
	dfs1(1,1);
	dfs2(1,1);
	for(int i=1;i<=n;++i)ans=min(ans,f[i]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：6)

考虑树形 dp。

第一次 dfs 的作用是求出 $f(1)$，这部分不难（板子），不讲了。但是我们还要顺便求出 $sc(i)$，也就是 $\sum c_{v\in \text{以 i 为根节点的这颗子树的节点}}$（要为后面 dp 的部分做准备）。

第二次 dfs 可以考虑换根。$f(u)$ 可以由它的父节点转移过来，转移方程为 $f(u)=f(fa)-sc(u)+sc(1)-sc(u)$，可以配合下面这张图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/n90f7agt.png)



```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
vector<int> G[N];
int c[N],sc[N],dep[N],f[N];
int f1;
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	f1+=c[u]*dep[u];
	sc[u]=c[u];
	for(auto v:G[u]) if(v!=fa){
		dfs(v,u);
		sc[u]+=sc[v];
	}
}
void dfs1(int u,int fa){
	if(u!=1){
		f[u]=f[fa]-sc[u]+sc[1]-sc[u];
	}
	for(auto v:G[u]) if(v!=fa) dfs1(v,u);
}
signed main(){
	int n;
	cin>>n;
	int u,v;
	for(int i=1;i<n;++i){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;++i) cin>>c[i];
    dep[0]=-1;
	dfs(1,0);
	f[1]=f1;
	dfs1(1,0);
    int ans=1e19;
    for(int i=1;i<=n;++i) ans=min(ans,f[i]);
    cout<<ans<<endl;
	return 0;
}
```

---

## 作者：spfa_ (赞：5)

[[ABC348E] Minimize Sum of Distances](https://www.luogu.com.cn/problem/AT_abc348_e)

[P2986](https://www.luogu.com.cn/problem/P2986) 的弱化版。

### 题目简述

有一棵树，边权为 $1$，每个点上有 $c_i$ 头奶牛。选一个点为根，使得所有奶牛到根的最小值，输出最小值。

### 题目分析

换根 dp。记 $f_i$ 表示选 $i$ 为根的最小值。我们先钦定 $1$ 为根，然后我们就可以预处理出每个子树的奶牛的个数 $num_i$，以及 $f_1$。接下来再在树上进行一次 dfs。若当前的边为 $(u,v)$，则将根 $u$ 换到 $v$ 的过程中 $v$ 的子树中的奶牛都减去了 $1$ 的距离，而其余点的奶牛都增加了 $1$ 的距离，所以有动态转移方程

$$f_v=f_u-num_u+num_1-num_u=f_u+num_1-2\times num_u$$

### code

```cpp
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

typedef vector <int> vi;
typedef pair <int, int> pii;

inline int rd() { int x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
inline ll rdll() { ll x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
template <typename T> inline void write(T x) { if (x < 0) x = -x, putchar('-'); if (x > 9) write(x/10); putchar(x%10+48); }

const int N = 1e5+5;
int n, ans, a[N], d[N], f[N], num[N];
vi E[N];

void dfs1(int x, int fa) {
	d[x] = d[fa]+1, f[1] += a[x]*d[x], num[x] = a[x];
	for (int y:E[x]) if (y != fa) dfs1(y, x), num[x] += num[y];
}

void dfs2(int x, int fa) {
	for (int y:E[x]) if (y != fa) {
		f[y] = f[x]+num[1]-2*num[y], ans = min(ans, f[y]);
		dfs2(y, x);
	}
}

signed main() {
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int x = rd(), y = rd();
		E[x].pb(y), E[y].pb(x);
	}
	for (int i = 1; i <= n; ++i) cin >> a[i];
	d[0] = -1, dfs1(1, 0);
	ans = f[1], dfs2(1, 0);
	cout << ans;
	return 0;
}
```

---

## 作者：Fiendish (赞：3)

经典的换根 dp。

首先我们算出 $F(1)$，然后进行转移。设当前节点为 $u$，其父节点为 $fa$，$ \displaystyle w_u=\sum_{i\in \text{subtree}(u)}C_i$，$\displaystyle sum=\sum_{i=1}^{n}C_i$；

考虑从 $fa$ 转移到  $u$ 时答案的变化，首先 $\text{subtree}(u)$ 中的节点到 $u$ 的距离比其到 $fa$ 的距离小 $1$，而 $\text{subtree}(fa)$ 中的节点到 $u$ 的距离比其到 $fa$ 的距离大 $1$，于是：
$$\begin{aligned}F(u)&=F(fa)+w_{fa}-w_u\\&=F(fa)+(sum-w_u)-w_u\\&=F(fa)+sum-2w_u\end{aligned}$$
于是此题解决。

注意一个问题，本题答案较大，取 $\min$ 时变量初值要赋成 $9\times10^{18}$，否则会 WA（本人因此喜提罚时）。

```cpp
#include<vector>
#include<iostream>
#define int long long
using namespace std;
vector<int> v[100010];
long long dp[100010],c[100010],sum,w[100010],ans;
int n;
void dfs(int u,int fa,long long dep){//计算F(1)和w数组
	ans+=dep*c[u];
	for(auto i:v[u]){
		if(i!=fa){
			dfs(i,u,dep+1);
			w[u]+=w[i];
		}
	}
	w[u]+=c[u];
}
void dping(int u,int fa){//dp
	if(u!=1) dp[u]=dp[fa]+sum-2*w[u];
	for(auto i:v[u])
		if(i!=fa) dping(i,u);
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		v[x].push_back(y),v[y].push_back(x);
	}
	for(int i=1;i<=n;i++) cin>>c[i],sum+=c[i];
	dfs(1,0,0);
	dp[1]=ans;
	dping(1,0);
	long long minn=9e18;
	for(int i=1;i<=n;i++) minn=min(minn,dp[i]);
	cout<<minn;
}
```

---

## 作者：2huk (赞：2)

- 给定一颗 $n$ 个节点的树和长度为 $n$ 的序列 $c_1 \dots c_n$。设 $f(x) = \sum\limits_{i=1}^n (c_i \times \operatorname{dis}_{i, x})$，求 $\min\limits_{1 \le v \le n} f(v)$。其中 $\operatorname{dis}_{a, b}$ 表示树上 $a, b$ 的简单路径上边的数量。
- $n \le 10^5$，$c_i \le 10^9$。

令 $1$ 为根。设 $T(x)$ 表示以 $x$ 为根的子树。

显然可以轻易地求出 $f(1)$。思考当 $v$ 的值发生变化时，$f(v)$ 的变化。

如果 $v$ 从本身移动到了它的某个儿子，那么 $v$ 到 $T(v)$ 中的每个点的距离都减少了 $1$，$v$ 到 $T(v)$ 外的每个点的距离都增加了 $1$。

由于在题目中 $f$ 值计算时，距离前面有一个系数 $c_i$，那么 $v$ 到 $T(v)$ 中的每个点的距离减少 $1$ 等价于 $f(v)$ 的值减少了 $\sum_{u \in T(v)} c_u$，$v$ 到 $T(v)$ 外的每个点的距离增加 $1$ 等价于 $f(v)$ 的值增加了 $\sum_{u \not \in T(v)} c_u$。

然后像这样类似 DP 地转移即可。


```cpp
int n, u, v, w[N];
int h[N], e[N], ne[N], idx;
int res, sum;

void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int dep[N], S;
int F[N];

void dfs(int u, int f) {
	dep[u] = dep[f] + 1;
	sum += (dep[u] - 1) * w[u];
	F[u] = w[u];
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == f) continue;
		dfs(v, u);
		F[u] += F[v];
	}
	return;
}

void dfs2(int u, int f) {
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == f) continue;
		sum -= F[v];
		sum += S - F[v];
		res = min(res, sum);
		dfs2(v, u);
		sum -= S - F[v];
		sum += F[v];
	}
	return;
}

void solve() {
	memset(h, -1, sizeof h);
	fin >> n;
	for (int i = 1; i < n; ++ i ) {
		fin >> u >> v;
		add(u, v), add(v, u);
	}
	for (int i = 1; i <= n; ++ i ) fin >> w[i], S += w[i];
	dfs(1, 0);
	res = sum;
	dfs2(1, 0);
	fout << res;
}
```

---

## 作者：JuRuoOIer (赞：1)

# 题解 ABC348E - Minimize Sum of Distances

前排提示：本题解为 **树形 DP** 做法。

### 如果你正解 WA 了

请注意你记录最小值的变量的初始值。为了通过官方数据，它至少应该是 $1.5\times10^{18}$，为此你显然需要开 `long long`。

### 题意

已提交翻译。

给定一棵 $n$ 个节点的树，每个点有点权 $c_i$。设 $ \displaystyle\ f(x)\ =\ \sum_{i=1}^{n}\ (c_i\ \times\ d(x,\ i)) $，求 $ \displaystyle\ \min_{1\ \leq\ v\ \leq\ n}\ f(v) $，其中 $d(x,y)$ 为 $x$ 到 $y$ 的树上距离。

数据范围：$n \le 10^5,c_i \le 10^9$。

### 做法

在树上统计这种奇奇怪怪的东西，这题树形 DP 实锤了。

而树形 DP 比较好做的是统计子树内的东西（直接 DFS），因此考虑先统计以每个点为根的子树内每个点到该点的距离乘点权之和（即只考虑以该点为根的子树时该点的 $f$）（代码中的 $d$ 数组），再计算。

于是先考虑求 $d$ 数组。

显然对于一个叶子节点 $x$，$d_x=0$。如果这个节点的父亲是 $y$，则它会对 $d_y$ 产生 $c_x$ 的贡献；若 $y$ 的父亲是 $z$，则会对 $d_z$ 产生 $2\times c_x$ 的贡献……可以发现，从第 $k$ 级祖先到第 $k+1$ 级祖先时，它对第 $k+1$ 级祖先的贡献是在对第 $k$ 级祖先的贡献的基础上再加 $c_x$，这样我们就搞清楚了一个点的贡献。

以某个叶子第 $k$ 级祖先为根的子树内每个节点，走到第 $k+1$ 级祖先时，所增加的贡献都是这个节点的点权（距离增加了 $1$），我们显然想给它们一起算，所以我们可以在计算 $d$ 数组的同时计算一个 $sz$ 数组，记录以每个节点（含）为根的子树中所有点的点权 $c$ 之和，计算方法和普通的统计子树大小相同。这样我们就得到了计算一个非叶子节点 $x$ 的 $d$ 值的公式：

$$d_x=\sum_{y\in son(x)}d_y+sz_y$$

于是 $d$ 数组和 $sz$ 数组就可以通过一遍 DFS 完成计算。

现在问题就剩一个了：$d$ 数组只考虑了以当前节点为根的子树内的答案，那这棵树剩余的部分怎么办呢？

画个图分析一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/i2dzcj0q.png)

首先，假设我们以 $1$ 为根，此时显然有 $f(1)=d_1$。现在要求出 $f(2)$ 的值，此时我们把树分成两部分考虑：
- 以 $2$ 为根的子树，贡献就是 $d_2$。
- 除以 $2$ 为根的子树之外的部分（即图中画红圈的部分），需要在走到 $1$ 的基础上再多走一格。
  - 这些点走到 $1$ 的总贡献，是 $d_1-(d_2+sz_2)$，其中 $d_2+sz_2$ 就是刚才计算以 $2$ 为根的子树内的所有节点。
  - 这些点从 $1$ 走到 $2$ 的总贡献，就是这些点的 $c$ 之和，即 $sz_1-sz_2$。

于是，我们想求一个点 $x$ 的 $f$（前提是它父亲的 $f$ 已知），公式就是：

$$f(x)=d_x+d_{fa_x}-d_x-sz_x+sz_{fa_x}-sz_x$$

用一遍 DFS 求这个就能确保每个点求之前其父亲是已知的。我是求完直接覆盖到 $d$ 数组里了，~~个人感觉比较方便~~。

于是我们总共用了两次 DFS 就把每个点的 $f$ 给求出来了，因此时空复杂度均为 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll n,c[100010],u,v,mn=500000000000000000ll,sz[100010],d[100010];
vector<ll> a[100010]; 
void dfs(ll now,ll fa){
	sz[now]=c[now];
	for(int i=0;i<a[now].size();i++){
		if(a[now][i]!=fa){
			dfs(a[now][i],now);
			sz[now]+=sz[a[now][i]];
			d[now]+=d[a[now][i]]+sz[a[now][i]];
		}
	} 
}
void dfs2(ll now,ll fa){
	if(fa)d[now]+=d[fa]-d[now]-sz[now]+sz[1]-sz[now];
	mn=min(mn,d[now]);
	for(int i=0;i<a[now].size();i++){
		if(a[now][i]!=fa){
			dfs2(a[now][i],now);
		}
	} 
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	for(int i=1;i<=n;i++)cin>>c[i];
	dfs(1,0);
	dfs2(1,0);
	cout<<mn;
	return 0;
}
```

---

## 作者：__Floze3__ (赞：1)

## 思路简介

如果只需要统计一个点的 $f$ 值，只需要一次 dfs 即可，时间复杂度为 $O(n)$。但是，我们不可能对于每个点都这样进行统计。我们可以先以 $1$ 号节点为根进行一次答案统计，考虑如何从一个点的答案转化为另一个答案。

考虑从树上的一个点 $u$ 的父节点 $fa$ 转移到 $u$，设$sum_u$ 表示以 $u$ 为根的子树上所有节点的 $C$ 值之和。那么 $f_u$ 相比于 $f_{fa}$，减少的是 $sum_u$，增加的是 $sum_1 - sum_u$。我们不难写出这样的式子：

$$
\begin{aligned}
    f_u &= f_{fa} - sum_u + (sum_1 - sum_u) \\
        &= f_{fa} + sum_1 - 2 \times sum_u
\end{aligned}
$$

显然，这是一个换根 dp，我们只需要再对这棵树进行一次 dfs，统计每个节点的答案即可。时间复杂度为 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define read std::cin
#define write std::cout
typedef long long ll;

const int N = 1e5 + 5;
const ll inf = 1e18;

int n, dep[N];
ll c[N], res = inf, sum[N], f[N];

std::vector<int> g[N];

void dfs1(int u, int fa) {
    f[1] += dep[u] * c[u];
    sum[u] = c[u];
    for (int v : g[u]) {
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        sum[u] += sum[v];
    }
    return ;
}

void dfs2(int u, int fa) {
    if (u != 1) {
        f[u] = f[fa] + sum[1] - 2 * sum[u];
        res = std::min(res, f[u]);
    }
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs2(v, u);
    }
    return ;
}

int main() {
    std::ios::sync_with_stdio(false);
    read.tie(0), write.tie(0);
    read >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        read >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) read >> c[i];
    dfs1(1, 0);
    res = f[1];
    dfs2(1, 0);
    write << res;
    return 0;
}
```

---

## 作者：Xuan_qwq (赞：1)

### 题面大意
给定一颗 $N$ 个节点的树，第 $i$ 号节点有一个权值 $c_i$。

定义 $f(u)$ 为树上每个点的权值乘上该点到 $u$ 的最短距离，求最小的 $f(u)$。
### 大致思路

首先我们肯定不能直接去计算每个点对应的 $f(u)$ 值，时间绝对爆炸。

我们又观察到这是一棵树，那么就可以想办法用相邻节点的 $f$ 值来求当前点的 $f$ 值。

如图，这是第三个样例对应的树。

![](https://cdn.luogu.com.cn/upload/image_hosting/2y9bkc8r.png)

点 $1$ 所对应的 $f(1)$ 中，每个节点权值被乘的树如图中红色数字。

![](https://cdn.luogu.com.cn/upload/image_hosting/7slpp7jw.png)

点 $2$ 所对应的 $f(2)$ 中，每个节点权值被乘的树如图中红色数字。

![](https://cdn.luogu.com.cn/upload/image_hosting/bq9n9tao.png)

发现了吗？以节点 $2$ 为根的子树中的节点，权值被乘的数都减一，剩下的加一。

就是说，$f(2)$ 相对于 $f(1)$ 来说，减去了以节点 $2$ 为根的子树中的节点权值之和，加上了其余所有节点的权值之和。这相当于**加上了整棵树的权值之和，减去了 $2$ 倍的以节点 $2$ 为根的子树中的节点权值之和**。

如果我们设以 $i$ 为根的子树中节点的权值之和为 $cnt_i$，以 $1$ 为树根，那么由此我们可以得到普遍规律：

如果 $u$ 是 $v$ 的父节点，则$f(v)=f(u)+cnt_1-2\times cnt_v$。

所以我们可以先遍历一遍整棵树，求出 $f(1)$ 和整个 $cnt$ 数组，再从树根开始遍历一遍从而得到 $f(u)$ 的最小值，时间复杂度是线性的。

好了接下来是代码。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>G[100005];
int c[100005];
long long f[100005],cnt[100005],ans;//f数组，cnt数组，答案 
void dfs(int u,int fa){//求解f[1]和cnt数组 
	cnt[u]=c[u];
	for(auto v:G[u]){
		if(v==fa)continue;
		dfs(v,u);
		cnt[u]+=cnt[v];
		f[u]+=f[v]+cnt[v];
	}
}
void ddd(int u,int fa){//求解最小的f值 
	for(auto v:G[u]){
		if(v==fa)continue;
		f[v]=f[u]+cnt[1]-2*cnt[v];
		ans=min(ans,f[v]); 
		ddd(v,u);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	dfs(1,-1);
	ans=f[1];
	ddd(1,-1);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

## 分析

看到 $f(v)$ 这种式子的计算，不难想到换根 dp，考虑先计算出 $f(1)$，接下来怎么转移呢？不难发现，从一个节点 $u$ 转移到某个儿子 $v$ 的时候，有一部分的节点 $c_i$ 会被加一，整棵树以外的部分的 $c_i$ 会被减一，这里放一下样例里面 $f(1)$ 转移到 $f(2)$ 的情况：

![image](https://cdn.luogu.com.cn/upload/image_hosting/7b4z9qu9.png?x)

如图，记画了 `-` 的部分的 $c_i$ 总和为 $del$，画了 `+` 的部分的 $c_i$ 总和为 $add$，则 $f(2)=f(1)-del+add$，又因为 $del+add=\sum c_i$，$\therefore f(2)=f(1)-((\sum c_i)-add)+add=f(1)-(\sum c_i)+2\times add$。记 $sum_x$ 为节点 $x$ 子树内 $c_i$ 的总和，观察例子不难发现 $add=sum_2$，因此 $f(2)=f(1)-(\sum c_i)+2\times sum_2$，推广一下不难得到转移方程 $f(u)=f(fa)-(\sum c_i)+2\times sum_u$，其中 $fa$ 为 $u$ 的父亲（假定 $1$ 为根）。

推导完转移之后实现就不难了，先 dfs 一次求出每个 $sum_i$，然后求出 $f(1)$，之后 dp 就行了。

## AC Code
[Code](https://atcoder.jp/contests/abc348/submissions/52096401)

---

## 作者：xiayz2010 (赞：1)

#### 题意

给定一个 $N$ 个节点的树，每个点拥有一个权值 $C_i$，设 $d(a,b)$ 为顶点 $a$ 和 $b$ 之间的边数，对于 $x = 1, 2, \ldots, N$，设 $\displaystyle f(x) = \sum_{i=1}^{N} (C_i \times d(x, i))$。求出 $\displaystyle \min_{1 \leq v \leq N} f(v)$。

#### 题解

不妨设 $1$ 为树的根节点，定义 $siz(i)$ 为以 $1$ 为根节点时以节点 $i$ 为根的子树中所有节点的权值之和。

对于每个 $x$ 暴力求出 $f(x)$ 非常费时，但是对于任意一条连接 $a$ 和 $b$ 的边（$a$ 是 $b$ 的父节点），若已知 $f(a)$ 就可以得出 $f(b)$，这样就可以用 $O(N)$ 的时间复杂度求出所有 $f(x)$。具体方法如下：

容易发现，从 $f(a)$ 向 $f(b)$ 转移时，以 $b$ 为根的子树中的任意一个节点 $i$ 都满足 $d(b,i)=d(a,i)-1$，而不属于以 $b$ 为根的子树中的任意一个节点 $i$ 都满足 $d(b,i)=d(a,i)+1$。

以 $b$ 为根的子树中所有节点的权值之和为 $siz(b)$，所有不属于以 $b$ 为根的子树的节点的权值之和为 $siz(1)-siz(b)$。根据 $f$ 的定义，容易得到状态转移方程：$f(b) = f(a) - 2 \times siz(b) + siz(1)$

只需要在程序的开头通过一次树的遍历求出 $siz$ 数组以及 $f(1)$ 就可以算出所有 $f(x)$ 了。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, M = 200010;

int n; LL c[N];
int h[N], e[M], ne[M], idx;
LL f[N], siz[N], dep[N];

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void init(int u, int father){
    siz[u] = c[u], dep[u] = dep[father] + 1;
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == father) continue;
        init(v, u);
        siz[u] += siz[v];
    }
}

void dp(int u, int father){
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == father) continue;
        f[v] = f[u] - 2 * siz[v] + siz[1];
        dp(v, u);
    }
}

int main(){
    scanf("%d", &n);
    memset(h, -1, sizeof(h));
    for(int i = 1; i < n; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    for(int i = 1; i <= n; i++)
        scanf("%lld", &c[i]);
    dep[0] = -1;
    init(1, 0);
    for(int i = 1; i <= n; i++) f[1] += dep[i] * c[i];
    dp(1, 0);
    LL ans = 0x3f3f3f3f3f3f3f3f;
    for(int i = 1; i <= n; i++)
        if(ans > f[i])
            ans = f[i];
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Butterfly_qwq (赞：0)

看一下题目条件，可以发现这是带权重心的性质。

证明：

我们先找到一个不是重心的点 $u$，调整 $u$ 到相邻节点，看看能不能使得 $\sum\limits_{v=1}^n d(u,v)\times c_v$ 更小。

事实上，以 $u$ 为根，寻找他的儿子中子树权值和大于以 $u$ 为根的子树权值和的一半的点，令其为 $k$。

则其他的点多了 $c_i$，这个子树内的点少了 $c_i$，那么 $f(k)<f(u)$。

然后我们发现找最小点的这个过程其实就是我们找重心的过程！

那么，使得 $f(u)$ 最小的 $u$ 点就是整棵树的带权重心。

实现的时候不必像上述调整法一样找中心，直接按着我们最初的定义找就行了。

附一个这道题的动态版：[P3345 [ZJOI2015] 幻想乡战略游戏](https://www.luogu.com.cn/problem/P3345)。

[接下来就是代码了。](https://atcoder.jp/contests/abc348/submissions/52111034)

---

## 作者：Lele_Programmer (赞：0)

# AT_abc348_e 题解

## 题目大意

给定一棵有 $N$ 个节点的树，顶点编号从 $1$ 到 $N$，第 $i$ 条边连接着 $A_i$ 与 $B_i$，再给定一个长度为 $N$ 的正整数序列 $C$，记顶点 $a$ 和 $b$ 之间的边数是 $d(a,b)$，对于 $1$ 到 $N$ 的每一个 $x$，设 $f(x)=\sum\limits_{i=1}^{N}(C_i \times d(x,i))$，求 $\min\limits_{1 \le v \le N} f(v)$。

## 思路

可以把 $C_i$ 看作每一个点的权值，记一个点的 $f$ 值为该点与所有节点的距离分别乘上那个节点的权值之和。

求一个点的 $f$ 值，当然可以直接枚举每一个点，很容易就可以得到，但是题目求的是所有节点的 $f$ 值的最小值，这样一来，时间复杂度就变成了 $O(N^2)$，妥妥 TLE。

仔细想一想，可以发现，只要得出了一个点的 $f$ 值，便可以直接求与之相邻的点的 $f$ 值。假设现在知道了一个点的 $f$ 值，向它的一个子节点移动，也就是向这个子节点的子树中的每一个节点靠近了 $1$ 的距离，并且向其它的节点远离了 $1$ 的距离，于是，将当前的 $f$ 值加上以子节点为根的子树的所有点的 $C$ 值之和，再减去除去这些点以外的所有点的 $C$ 值之和，便是这一个子节点的 $f$ 值。

这样一来，把节点 $1$ 作为根，只需要 dfs 一遍，将每一个点与其子树的 $C_i$ 值之和、每一个点的深度、所有 $C_i$ 值之和求出来，枚举每个节点，求出 $f(1)$ 的值，然后再次 dfs，从 $1$ 出发，便可以用 $O(1)$ 求出一个点的 $f$，最后，取 $f$ 值的最小值并输出即可。

时间复杂度：$O(N)$

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N=100005;
const int M=200005;

int n;
int c[N]; // 记录每一个点的 C 值
int e[M],ne[M],h[N],tot; // 前向星存图
int d[N]; // dis[1,i]
int s[N]; // sum
int s_all; // s[1]+...+s[n]
int f[N]; // f(i)

void add(int a,int b) {
    e[tot]=b,ne[tot]=h[a],h[a]=tot++;
}

// 第一次 dfs，求出每一个点的深度和子树 C 值之和
void dfs1(int u,int fa) {
    s[u]=c[u];
    for (int i=h[u];~i;i=ne[i]) {
        if (e[i]==fa) continue;
        d[e[i]]=d[u]+1;
        dfs1(e[i],u);
        s[u]+=s[e[i]];
    }
}

// 第二次 dfs，求出每个点的 f 值
void dfs2(int u,int fa) {
    for (int i=h[u];~i;i=ne[i]) {
        if (e[i]==fa) continue;
        f[e[i]]=f[u]-s[e[i]]+s_all-s[e[i]];
        dfs2(e[i],u);
    }
}

signed main() {
    memset(h,-1,sizeof(h));
    scanf("%lld",&n);
    for (int i=1;i<=n-1;++i) {
        int a,b;
        scanf("%lld %lld",&a,&b);
        add(a,b);
        add(b,a);
    }
    for (int i=1;i<=n;++i) {
        scanf("%lld",&c[i]);
        s_all+=c[i];
    }
    dfs1(1,0);
    for (int i=1;i<=n;++i) {
        f[1]=f[1]+(c[i]*d[i]);
    }
    dfs2(1,0);
    int ans=9000000000000000000LL;
    for (int i=1;i<=n;++i) {
        ans=min(ans,f[i]);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

容易想到，经过一次对整棵树的遍历可以得到一个节点的 $f$ 值。我们既然不能暴力计算每一个节点，那就考虑处理每个 $f$ 值之间的关系。

这里建议画一下树。我们先随意确定一个点作为根节点，算出它的 $f$ 值。我们发现，接下来如果往它的一个子节点移动，那么该子节点所领子树上的所有节点到我们所在节点的距离都会 $-1$，相应的在 $f(v)$ 中这些节点的权值贡献就会减去一倍；而其他节点到我们所在节点的距离都会 $+1$，相应的在 $f(v)$ 中这些节点的权值贡献就会增加一倍。

这样我们就可以以 $O(1)$ 的复杂度将答案由一个节点推到另一个节点。此时我们只需要先遍历一遍整棵树，记录每个节点的子树的权值和；再遍历一遍整棵树，计算出 $f(1)$ 的值；然后再遍历一遍整棵树，由 $f(1)$ 推出每个节点的 $f$ 值，并选取最小的一个输出，即可。

PS：这种思想的学名叫换根 DP。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,a[1000005],f[1000005],minn;
int ver[1000005],ne[1000005],head[1000005],tot;
void add(int x,int y){
	ver[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
bool flag[1000005];
void init(int root){
	flag[root]=1;
	for(int i=head[root];~i;i=ne[i]){
		if(flag[ver[i]]) continue;
		init(ver[i]);
		f[root]+=f[ver[i]];
	}
	f[root]+=a[root];
	return;
}
void build(int x,int k){
	flag[x]=1;
	minn+=a[x]*k;
	for(int i=head[x];~i;i=ne[i]){
		if(flag[ver[i]]) continue;
		build(ver[i],k+1);
	}
}
void dfs(int x,long long sum){
	flag[x]=1;
	minn=min(minn,sum);
	for(int i=head[x];~i;i=ne[i]){
		if(flag[ver[i]]) continue;
		dfs(ver[i],sum-f[ver[i]]+(f[1]-f[ver[i]]));
	}
}
int main(){
	scanf("%d",&n);
	memset(head,-1,sizeof(head));
	for(int i=1;i<n;i++){
		scanf("%d %d",&x,&y);
		add(x,y),add(y,x);//建树
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	init(1);//计算每个节点的子树权值和
	for(int i=1;i<=n;i++) flag[i]=0;
	build(1,0);//计算出f(1)的值
	for(int i=1;i<=n;i++) flag[i]=0;
	dfs(1,minn);//推出每个f(i)
	printf("%lld",minn);//输出最小值
	return 0;
}
```

---

## 作者：Sorato_ (赞：0)

# ABC348E Minimize Sum of Distances

## 题目大意

给定一棵共 $n$ 个节点的树， 第 $i$ 个点的权重为 $c_i$。定义 $f(x)$ 表示树上所有点到节点 $x$ 的距离乘上权重，即 $f(x)=\sum\limits_{i=1}^n(c_i\times dis(x, i))$。求 $\min\limits_{u=1}^nf(u)$。

## Solve

一眼换根。

考虑先以节点 $1$ 为根，则 $f(1)=\sum\limits_{i=1}^n(c_i\times d_i)$，（$d_i$ 表示 $i$ 的深度）。然后考虑换根求 $f(u),u\in[2,n]$。

![image-20240409193224147](https://img2.imgtp.com/2024/04/09/uUd1USET.png)

如图，以 $u=2$ 时为例。记 $sum_u$ 为当以 $1$ 为根时 $u$ 的子树内的点的权值和。当根从 $fa_2=1$ 转移至 $2$ 时，对于在 $2$ 的子树里的节点，他们的深度都减少了 $1$，那么 $\sum\limits_{i\in son_2}(c_i\times d_i)$ 就总共减少了 $sum_u$；对于不在 $2$ 的子树里的点，他们的深度都增加了 $1$，共增加 $sum_1-sum_u$。整理一下并推广至所有 $u\in [2,n]$，有： $f(u)=f(fa_u)-sum_u+sum_1-sum_u$。

## Code

```c++
#include<bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n,a,b,c[100010],f[100010],ans;
vector<int>e[100010];
void dfs(int u,int fa,int d)
{
	f[1]+=d*c[u];
	for(auto i:e[u])
		if(i!=fa)	dfs(i,u,-~d),c[u]+=c[i];
}
void dp(int u,int fa)
{
	for(auto i:e[u])
		if(i!=fa)	f[i]=f[u]-c[i]+c[1]-c[i],dp(i,u);
}
signed main()
{
	n=read();
	for(int i=1;i<n;i=-~i)
		a=read(),b=read(),
		e[a].push_back(b),e[b].push_back(a);
	for(int i=1;i<=n;i=-~i)	c[i]=read();
	dfs(1,0,0);ans=f[1];dp(1,0);
	for(int i=1;i<=n;i=-~i)	ans=min(ans,f[i]);
	return printf("%lld",ans),0;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

给你一棵有 $n$ 个顶点的树和一个长度为 $n$ 的序列 $C$。

定义 $dis(a,b)$ 表示 $a$ 到 $b$ 简单路径上经过的边数。

定义：

$$f(x) = \sum_{i=1}^{N} (C_i \times dis(x, i))$$

求出：
$$\min_{1 \leq v \leq N} f(v)$$

### 思路：

~~换根 DP 板子题。~~

先考虑求出 $f(1)$，然后定义 $p_u$ 表示 $u$ 子树内 $C$ 的权值和。

那么我们可以发现，在 $fa_u$ 的基础上：

$$dis(x,u)= \begin{cases} dis(x,fa_u)-1 & 当 x 在 u 子树内时 \\ dis(x,fa_u)+1 & 当 x 在 u 子树外时\end{cases}$$

就相当于：

$$\begin{aligned} f(u) &= \sum_{i=1}^{N} (C_i \times (dis(i,fa_u) \pm 1)) \\ &=f(fa_u)-p_u+ (p_1-p_u) \\ &=f(fa_u)+p_1-2 \times p_u\end{aligned}$$

于是就可以通过 $f(1)$ 的值，再深搜一遍求出所有节点的值。

最后求一遍最小即可，时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=100100,INF=LONG_LONG_MAX;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,ans=INF;
ll a[N],d[N],p[N],f[N];
vector<ll> E[N];
void add(ll u,ll v){
	E[u].push_back(v);
	E[v].push_back(u);
}
void dfs1(ll u,ll fa){
	p[u]=a[u];
	for(auto v:E[u]){
		if(v==fa)
		  continue;
		d[v]=d[u]+1;
		dfs1(v,u);
		p[u]+=p[v];
	}
}
void dfs2(ll u,ll fa){
	for(auto v:E[u]){
		if(v==fa)
		  continue;
		f[v]=f[u]+(p[1]-p[v])-p[v];
		dfs2(v,u);
	}
}
int main(){
	n=read();
	for(int u,v,i=1;i<n;i++){
		u=read(),v=read();
		add(u,v);
	}
	for(int i=1;i<=n;i++)
	  a[i]=read();
	dfs1(1,0);
	for(int i=1;i<=n;i++)
	  f[1]+=d[i]*a[i];
	dfs2(1,0);
	for(int i=1;i<=n;i++)
	  ans=min(ans,f[i]);
	write(ans);
	return 0;
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc348_e)
## 思路
这是一道非常经典的换根树动规题。  
先把这棵树当成以 $1$ 为根，命 $f_i$ 为考虑以 $i$ 为根的子树贡献，则 $f_i$ 就等于以 $i$ 的儿子节点为根的子树的总贡献加上 $i$ 的儿子为根的总 $c_i$ 的和。命 $v_i$ 为 $i$ 号点父亲带来的贡献，$v_i$ 就等于 $i$ 号点父亲的总贡献减去 $i$ 号点的贡献加上所有点的 $c_i$ 和减去以 $i$ 为根的子树的 $c_i$ 和。
## AC code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
const I N = 1000010;
vector<I>edges[N];
I n;
LL f[N],v[N],c[N],sum[N],al;
bool b[N];
void up(I x){
	b[x] = true;
	f[x] = 0;
	sum[x] = c[x]; 
	for(auto i : edges[x]){
		if(!b[i]){
			up(i);
			f[x] += f[i] + sum[i];
			sum[x] += sum[i];//ci和
		}
	}
}
void down(I x){
	b[x] = true;
	for(auto i : edges[x]){
		if(!b[i]){
			v[i] = (f[x] + v[x] - f[i] - sum[i]) + (al - sum[i]);
			down(i);
		}
	}
}
I main(){
	scanf("%d",&n);
	if(!n){
		printf("0\n");
		return 0;
	}
	for(I i = 1;i < n;i++){
		I u,v;
		scanf("%d%d",&u,&v);
		edges[u].pb(v);
		edges[v].pb(u); 
	}
	for(I i = 1;i <= n;i++){
		scanf("%lld",&c[i]);
		al += c[i];
	}
	for(I i = 1;i <= n;i++) b[i] = false;
	up(1);//儿子的贡献
	for(I i = 1;i <= n;i++) b[i] = false;
	down(1);//父亲的贡献
	LL ans = 9e18 + 10;
	for(I i = 1;i <= n;i++){
		//printf("%lld %lld\n",f[i],v[i]);
		//printf("%lld\n",f[i] + v[i]);
		ans = min(ans,f[i] + v[i]);//求答案
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：0)

原题。

写两个 dfs，第一个维护该节点子树上所有节点到根的距离，第二个计算子树外的，然后就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ff[200005], c[200005], r[200005], f[200005];
int n;
long long sm, ans = LLONG_MAX;
struct node{
    int v, c;
};
vector<node> G[200005];
long long dfs(int u, int fa){//第一个 dfs
    long long ans = 0;
    for (auto vv : G[u]){
    	int v = vv.v;
    	if (v != fa){
    		long long ss = dfs(v, u);
    		ff[u] += ff[v] + vv.c * ss;
    	//	cout << ff[u] << " " << u << "\n";
    		ans += ss;
		}
	}
	r[u] = ans + c[u];
    return r[u];
}
void ddfs(int u, int fa){//第二个 dfs
	for (auto vv : G[u]){
		int v = vv.v;
		if(v != fa){
		//	cout << v << " " << r[v] << " " << sm << "\n";
			f[v] = f[u] - r[v] * vv.c + (sm - r[v]) * vv.c;
			ddfs(v, u);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++){
		int u, v;
		cin >> u >> v;
		G[u].push_back({v, 1});
		G[v].push_back({u, 1});
	}
	for (int i = 1; i <= n; i++){
		cin >> c[i];
		sm += c[i];
	}
    dfs(1, 0);
    ddfs(1, 0);
	for (int i = 1; i <= n; i++)
		ans = min(ans, f[i]);
    cout << ans + ff[1];
}
```

---

## 作者：破壁人罗辑 (赞：0)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/AT_abc348_e)/[AtCoder](https://atcoder.jp/contests/abc348/tasks/abc348_e)

## 题目大意

给出一棵树以及每个节点的权重 $c_i$，求树上一个节点到其它节点的路程乘以对应节点权重的和的最小值。

## 解题思路

深度优先搜索 dfs 两遍，第一遍求一个节点的子树到这个节点的距离与权重的乘积和，第二遍求除了子树之外的其它节点到这个节点的距离与权重的乘积和。

## AC 代码

### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[100001];
bool vis[100001];
long long sum[100001],num[100001],sumc;
int c[100001];
void dfsd(int i){
	num[i]=c[i];vis[i]=1;
	for(auto j:v[i])if(!vis[j]){dfsd(j);sum[i]+=sum[j]+num[j];num[i]+=num[j];}
}
void dfsu(int i){
	vis[i]=1;
	for(auto j:v[i])if(!vis[j]){sum[j]+=sum[i]-sum[j]-(num[j]<<1)+sumc;dfsu(j);}
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<n;i++){
		int a,b;scanf("%d%d",&a,&b);v[a].push_back(b);v[b].push_back(a);
	}
	for(int i=1;i<=n;i++){scanf("%d",c+i);sumc+=c[i];}
	dfsd(1);memset(vis,0,sizeof(vis));dfsu(1);long long ans=sum[1];
	for(int i=2;i<=n;i++)ans=min(ans,sum[i]);
	printf("%lld",ans);
	return 0;
}
```

### Python
```python
import sys
sys.setrecursionlimit(1919810)
n=int(input())
e=[[] for i in range(n)]
for i in range(n-1):
    [u,v]=input().split()
    e[int(u)-1].append(int(v)-1)
    e[int(v)-1].append(int(u)-1)
v=[0 for i in range(n)]
num=[0 for i in range(n)]
c=input().split()
su=0
for i in range(n):
    c[i]=int(c[i])
    su=su+c[i]

def ddfs(i):
    global num,c,v,e,vis
    vis[i]=True
    num[i]=c[i]
    for j in e[i]:
        if not vis[j]:
            ddfs(j)
            v[i]=v[i]+v[j]+num[j]
            num[i]=num[i]+num[j]
            
def udfs(i):
    global num,v,e,su,vis
    vis[i]=True
    for j in e[i]:
        if not vis[j]:
            v[j]=su-num[j]+v[i]-num[j]
            udfs(j)

vis=[False for i in range(n)]
ddfs(0)
vis=[False for i in range(n)]
udfs(0)
ans=v[0]
for i in range(n):
    ans=min(ans,v[i])
print(ans)
```

---

## 作者：kczw (赞：0)

# 题意
给定一棵 $N$ 个点的树，点 $i$ 有值 $C_i$，令 $f(x)=\sum_{i=1}^N dis(x,i)\times C_i$，其中 $dis(x,i)$ 指点 $x$ 与点 $i$ 间边数。

求 $\displaystyle\ \min_{1\le v\le n}{f(v)}$
# 思路
我们令一个以点 $i$ 为根的子树的 $C$ 值和为 $sum_i$。然后先以某点为根（为方便，此处取点 $1$ 为根）遍历一遍树更新其 $sum$ 值，同时求出 $f(1)$ 的值。

不难理解，某点 $sum$ 时等于其所有儿子的 $sum$ 值及此点的 $C$ 值的和。

然后就是求得 $f(1)$，你大可暴力求出每点深度，然后与其 $C$ 值相乘求和。这里有一个递推写法，我们令 $F(x)$ 为一点子树内所有点到其距离乘以其 $C$ 值，所以父节点 $F$ 值为所有儿子的 $F$ 以及 $sum$ 值之和，这个不难理解。

求得一点的 $f$ 值后就可以开始递推了，我们来分析以下图：
```
    1
   / \
  2   3
 / \
4   5
```
令我们此时已经得到了值 $f(1)$，那么是否可以有一种方法可以快速得到 $f(2)$ 呢？

不难发现，$f(1)$ 相比较和 $f(2)$ 的多了点 $2$ 为根的子树内的 $C$ 值（即 $sum_2$）和少了已经除了点 $2$ 为根的子树外的点的 $C$ 值（即 $sum_1-sum_2$）。

从另外一个角度考虑，如果要从 $f(1)$ 转换到 $f(2)$，那么之前点 $2$ 子树内的点到点 $1$ 的距离转化为到点 $2$ 的距离，每个点计算的 $dis$ 统统减少了 $1$，同时其他点原本计算的到点 $1$ 的距离现在转为到点 $2$ 的距离，于是它们计算的 $dis$ 统统增加了 $1$。

总而言之 $f(son)=f(fa)-sum_{son}+(sum_{root}-sum_{son})$，这里 $fa$ 为父节点，$son$ 指子节点，而 $root$ 指根。

于是只需要再次深搜求得每个点 $f$ 值，比较出最小值即可。
# 代码
```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N=1e5+5;

int n;
int c[N];
int f[N],sum[N];
int ans=0x3f3f3f3f3f3f3f3f;

vector<int> e[N];

inline void dfs(int u,int faa){

    sum[u]=c[u];

    for(auto v:e[u])
        if(v!=faa){

            dfs(v,u);

            f[u]+=f[v]+sum[v];
            sum[u]+=sum[v];
    }
}

inline void DFS(int u,int faa){

    for(auto v:e[u])
        if(v!=faa){

            f[v]=f[u]+sum[1]-sum[v]*2;

            ans=min(ans,f[v]);
            DFS(v,u);
    }
}

signed main(){

    scanf("%lld",&n);

    for(int i=2,u,v;i<=n;i++){

        scanf("%lld%lld",&u,&v);

        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++)
        scanf("%lld",&c[i]);

    dfs(1,0);
    ans=f[1];
    DFS(1,0);

    printf("%lld",ans);
    return 0;
}
```

---

## 作者：cancan123456 (赞：0)

基础换根题，令 $s(u)$ 为 $u$ 的子树所有节点构成的集合，$S(u)$ 为 $u$ 的子节点构成的集合，$f(u)$ 为 $u$ 的父节点，特别地，$f(1)$ 无意义。

预处理 $D_u=\sum_{v\in s(u)}C_v$，按照套路，设 $f_u=\sum_{v\in s(u)}C_v\times d(u,v)$，显然有：

$$f_u=\sum_{v\in S(u)}f_v+D_v$$

设 $g_u=\sum_{v=1}^nC_v\times d(u,v)$，则 $g_1=f_1$，考虑以 $u$ 为根时 $g_u$ 如何计算：

+ $f(u)$ 对应子树的贡献为 $g_{f(u)}-f_u-D_u$。
+ $u$ 原有子树的贡献为 $f_u+D_1-D_u$。

所以 $g_u=g_{f(u)}+D_1-2D_u$。

时间复杂度为 $O(n)$，可以通过此题。

这个题不用换根 DP，但是我赛时没发现，所以下面的代码采用了换根 DP 的写法。

```cpp
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 100005;
struct Edge {
	int v, next;
} edge[2 * N];
int head[N];
int cnt;
void add_edge(int u, int v) {
	cnt++;
	edge[cnt].v = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}
ll C[N], f[N];
void dfs(int u, int fa) {
	for (int v, i = head[u]; i != 0; i = edge[i].next) {
		v = edge[i].v;
		if (v != fa) {
			dfs(v, u);
			C[u] += C[v];
			f[u] += C[v] + f[v];
		}
	}
}
ll g[N];
void dfs2(int u, int fa, ll g_fa) {
	if (u == 1) {
		g[1] = f[1];
	} else {
		g[u] = f[u] + C[1] - C[u] + g_fa;
	}
	for (int v, i = head[u]; i != 0; i = edge[i].next) {
		v = edge[i].v;
		if (v != fa) {
			dfs2(v, u, g[u] - f[v] - C[v]);
		}
	}
}
ll min(ll a, ll b) {
	return a < b ? a : b;
}
int main() {
	int n;
	scanf("%d", &n);
	for (int u, v, i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	for (int u = 1; u <= n; u++) {
		scanf("%lld", &C[u]);
	}
	dfs(1, 0);
	g[1] = f[1];
	dfs2(1, 0, 0);
	ll ans = g[1];
	for (int u = 2; u <= n; u++) {
		ans = min(ans, g[u]);
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：eb0ycn (赞：0)

传送门：[AT_abc348_e](https://www.luogu.com.cn/problem/AT_abc348_e)。

## 题意

给定一棵树，每个节点有点权 $C_x$，每条边的边权为 $1$，定义 $d(a,b)$ 为 $a$ 到 $b$ 之间的路径长度，$f(x)=\sum_{i=1}^n (C_i \times d(i,x))$，求 $f(x)$ 的最小值。

## 思路

先对 $f(x)$ 进行转化。容易知道当 $x$ 为根节点时，$C_i$ 就是 $i$ 的深度。

所以问题就转化成了选择根节点。

先钦定 $1$ 是根节点，考虑怎么计算 $f(1)$。显然，节点 $x$ 对答案的贡献就是 $x$ 的子树和，记为 $s_x$。

考虑怎么从 $f(1)$ 推广到 $f(x)$。

设有**相连**的两个节点 $u$ 和 $v$，我们已经算出了 $f(u)$，则 $f(v) \gets f(u)+s_1-2\times s_v$。

上面的式子其实很简单。因为每次根节点移动一格，就会让 $v$ 子树内的节点深度减少一，字树外的节点深度增加一。

然后就做完了，树形 dp 即可。

## 代码

```cpp
#include<cstdio>
using namespace std;
int n,head[100001],to[200001],nxt[200001],c[100001],u,v,tot;
long long ans=0x3f3f3f3f3f3f3f3f,s[100001],ret;
long long min(long long a,long long b){return a>b?b:a;}
void dfs(int x,int fa){
	for(int i=head[x];i;i=nxt[i]){
		if(fa==to[i])continue;
		dfs(to[i],x),s[x]+=s[to[i]],ret+=s[to[i]];
	}s[x]+=c[x];
}
void d(int x,int fa){
	ret+=s[1]-s[x]-s[x],ans=min(ans,ret);
	for(int i=head[x];i;i=nxt[i]){
		if(to[i]==fa)continue;
		d(to[i],x);
	}ret-=s[1]-s[x]-s[x];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i)scanf("%d%d",&u,&v),nxt[++tot]=head[u],head[u]=tot,to[tot]=v,nxt[++tot]=head[v],to[tot]=u,head[v]=tot;
	for(int i=1;i<=n;++i)scanf("%d",c+i);dfs(1,-1),ret+=s[1],d(1,-1);
	return 0&printf("%lld",ans);
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc348_e)

首先在一棵树上，有一个很明显的结论。

设每个点到点 $i$ 的边数和为 $f_i$。

则如果有一个点 $v$ 的父亲是 $u$ ，那么 $f_v$ 和 $f_u$ 的差距就在于以点 $v$ 为根的子树的上的所有点到 $v$ 的边数与到点 $u$ 的边数相比少了 $1$，其余的点到 $v$ 的边数则都增加了 $1$。

现在题目中又加入了一个 $c$ 序列，但是也不难。原本的边数少 $1$ 在本题中就变成了权值少 $c_x$，边数多 $1$ 则变为权值多 $c_x$。

于是 $f_v$ 和 $f_u$ 的差距就变为减去以点 $v$ 为根的子树上的点相对应的在 $c$ 中的数的和，加上其余的点在 $c$ 中相对应的数的和。

求以点 $v$ 为根的子树上的点相对应的在 $c$ 中的数的和的处理可以先深搜求 dfs 序，然后就可以保证子树中的所有点的 dfs 序具有连续性，就可以使用前缀和来实现。

求其余的点在 $c$ 中相对应的数的和的处理只需要用 $c$ 中的所有数的总和减去以点 $v$ 为根的子树上的点相对应的在 $c$ 中的数的和就行了。

不过赛时傻了，没用前缀和而是使用线段树，所以代码当中对于前缀和的区间求和操作也就变成使用线段树来实现了。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define lc k<<1
#define rc k<<1|1
using namespace std;
int n;
vector<int> g[100010];
bool b[100010];
int dfn[100010],dy[100010],tot=0;
ll z[100010];
ll tr[400010]={0};
ll dp[100010];
ll siz[100010];
ll ans=6e18,s=0;
inline void dfs(int k)
{
	b[k]=1,siz[k]=1;
	for(int i=0;i<g[k].size();i++)
	{
		int x=g[k][i];
		if(b[x]) continue;
		tot++,dfn[x]=tot,dy[tot]=x,dfs(x),siz[k]+=siz[x];
	}
}
inline void build(int l,int r,int k)
{
	if(l==r)
	{
		tr[k]=z[dy[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	tr[k]=tr[lc]+tr[rc];
}
inline ll query(int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr) return tr[k];
	int mid=(l+r)>>1;
	ll sum=0;
	if(ql<=mid) sum=query(l,mid,ql,qr,lc);
	if(mid<qr) sum+=query(mid+1,r,ql,qr,rc);
	return sum;
}
inline void dfs1(int k,ll len)
{
	dp[1]+=z[k]*len,b[k]=1;
	for(int i=0;i<g[k].size();i++)
	{
		int x=g[k][i];
		if(b[x]) continue;
		b[x]=1,dfs1(x,len+1);
	}
}
inline void dfs2(int fa,int k)
{
	if(fa)
		dp[k]=dp[fa]+s-2*query(1,n,dfn[k],dfn[k]+siz[k]-1,1);
	b[k]=1;
	for(int i=0;i<g[k].size();i++)
	{
		int x=g[k][i];
		if(b[x]) continue;
		b[x]=1,dfs2(k,x);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v),g[v].push_back(u);
	}
	for(int i=1;i<=n;i++) scanf("%lld",&z[i]),s+=z[i];
	dfs(1);
	for(int i=1;i<=n;i++) b[i]=0;
	dfs1(1,0);
	build(1,n,1);
	for(int i=1;i<=n;i++) b[i]=0;
	dfs2(0,1);
	for(int i=1;i<=n;i++)
		ans=min(ans,dp[i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

这道题，和 CF1092F 非常像，只是把最大值改成了最小值而已。

设 $ans_x$ 表示 $f(x)$，同时我们假设节点 $1$ 为根，那么 $f(1) = \sum_{i=1}^{n}dep_i \times C_i$。其中 $dep_i$ 表示以节点 $1$ 为根时第 $i$ 个节点的深度，可以使用 dfs 快速求出。

那么求出了 $f(1)$ 如何求出剩下的呢？我们从根节点开始，按深度从小到大进行求解。设 $fa_i$ 表示 $i$ 的父亲节点，$subtree(i)$ 表示 $i$ 的子树集合。则 $f(i) = f(fa_i)  + \sum_{x \in subtree(i)}C_x - (\sum_{x=1}^{n}C_x - \sum_{x \in subtree(i)}C_x)$。为什么？因为对于中心节点从 $fa_i$ 转移到 $i$ 的过程中，$i$ 的子树部分与中心节点的距离会减少 $1$，也就是第 $x$ 个节点减少 $C_x$。而其他部分会增加 $1$。

那么 $\sum_{x \in subtree(i)}C_x$ 可以通过 dfs 的回溯过程中进行，访问到 $x$ 节点之后第一步就是计算 $f(x)$ 的值，然后取最小值即可。

P.S.一定要开 unsigned long long！我就在比赛时卡了这个卡了最后 20 分钟没调出来。

代码放一下。（这个代码其实基本上都是从CF那边拿过来改的）

```cpp
#include <iostream>
#include <vector>
using namespace std;

unsigned long long n, a[200005], fa[200005], dep[200005], su, sum[200005], ans[200005], minn = 10000000000000000000;
vector <unsigned long long> edge[200005];

unsigned long long min(unsigned long long x, unsigned long long y) {
	if(x > y) return y;
	else return x;
}

void build(unsigned long long x, unsigned long long de) {
	unsigned long long len = edge[x].size();
	dep[x] = de;
	su += de * a[x];
	for(unsigned long long i = 0; i < len; i++) {
		unsigned long long y = edge[x][i];
		if(y != fa[x]) {
			fa[y] = x;
			build(y, de + 1);
			sum[x] += sum[y];
		}
	}
}

void change(unsigned long long x) {
	if(x != 1) {
		ans[x] = ans[fa[x]] - sum[x] + sum[1] - sum[x];
		minn = min(ans[x], minn);
	}
	unsigned long long len = edge[x].size();
	for(unsigned long long i = 0; i < len; i++) {
		unsigned long long y = edge[x][i];
		if(y != fa[x]) {
			change(y);
		}
	}
}

int main() {
	cin >> n;
	for(unsigned long long i = 1; i < n; i++) {
		unsigned long long u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	for(unsigned long long i = 1; i <= n; i++) {
		cin >> a[i];
		sum[i] = a[i];
	}
	fa[1] = 0;
	build(1, 0);
	ans[1] = su;
	change(1);
	minn = min(minn, ans[1]);
	cout << minn;
}
```

---

## 作者：wwwwwza (赞：0)

[相似的题](https://www.luogu.com.cn/problem/CF1092F)。

换根 DP 和 DFN 序上线段树。

先处理出节点 $1$ 的条件，将其他节点与节点 $1$ 的距离和系数 $c_i$ 放入线段树。

发现在 DFN 序上一个节点的子树的编号是相连的，加上换根 DP 的思想，就可以用线段树维护每一个节点的代价。

代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=998244353;
const int inf=0x3f3f3f3f;
int n,x,y,c[N],dfn[N],id[N],idx=0,siz[N],dep[N];
int ans;
vector<int>g[N];
struct node{
	int num;//代价
	int tag;//lazy标记
	int x;//系数
}tree[N<<2];
void dfs(int u,int fa){
	dfn[u]=++idx;siz[u]=1;
	id[dfn[u]]=u;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
void pushup(int rt){
	tree[rt].num=tree[rt*2].num+tree[rt*2+1].num;
	tree[rt].x=tree[rt*2].x+tree[rt*2+1].x;
}
void pushdown(int rt){
	if(tree[rt].tag){
		tree[rt*2].tag+=tree[rt].tag;
		tree[rt*2+1].tag+=tree[rt].tag;
		tree[rt*2].num+=tree[rt*2].x*tree[rt].tag;
		tree[rt*2+1].num+=tree[rt*2+1].x*tree[rt].tag;
		tree[rt].tag=0;
	}
}
void build(int rt,int l,int r){
	if(l==r){
		tree[rt].num=dep[id[l]]*c[id[l]];
		tree[rt].x=c[id[l]];
		return;
	}
	int mid=l+r>>1;
	build(rt*2,l,mid);
	build(rt*2+1,mid+1,r);
	pushup(rt);
}
void update(int rt,int l,int r,int x,int y,int d){
	if(x<=l&&r<=y){
		tree[rt].tag+=d;
		tree[rt].num+=d*tree[rt].x;
		return;
	}
	pushdown(rt);
	int mid=l+r>>1;
	if(mid>=x)update(rt*2,l,mid,x,y,d);
	if(mid<y)update(rt*2+1,mid+1,r,x,y,d);
	pushup(rt);
}
void dfs1(int u,int fa){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		update(1,1,n,dfn[v],dfn[v]+siz[v]-1,-2);
		update(1,1,n,1,n,1);
		ans=min(ans,tree[1].num);
		dfs1(v,u);
		update(1,1,n,dfn[v],dfn[v]+siz[v]-1,2);
		update(1,1,n,1,n,-1);
	}
}
signed main(){
	cin >>n;
	for(int i=1;i<n;i++){
		cin >>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		cin >>c[i];
	}
	dfs(1,0);
	build(1,1,n);
	ans=tree[1].num;
	dfs1(1,0);
	cout <<ans;
	return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目分析

这是一道典型的换根 DP。因为此题要求距离之和的最小值，所以是一道换根 DP。我们先来推导一下换根 DP 的状态转移方程。如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/5cwfu4i8.png)

假设根节点为 $1$。当从结点 $1$ 转移到结点 $2$ 时，以 $2$ 为根的子树中的所有结点到目标结点的距离都会少 $1$，而其他结点到目标结点的距离就会多 $1$，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/111485z4.png)

所以，每次向下转移会少掉以目标结点为根的子树的 $C$ 之和，会多去其他结点的 $C$ 之和。这样，状态转移方程就很明显了。设 $f_i$ 表示题目中的 $f(i)$，$x$ 表示结点 $i$ 的一个子结点，$sum_i$ 表示以 $i$ 为根的子树中的 $C$ 之和，$root$ 表示树的根结点，那么 $f_x=f_i-sum_x+sum_{root}-sum_x$。

接下来的问题就变成了如何求出 $f_{root}$。设 $x$ 表示结点 $i$ 的子结点，$dp_i$ 表示 $\sum (C_x \times d(x,i))$，那么 $dp_i=\sum (dp_x+sum_x)$。显然，$f_{root}=dp_{root}$。所以，这个问题就被我们解决了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=1e5;
int n;
ll a[maxn+5],f[maxn+5],sum[maxn+5],dp[maxn+5];
vector<int>node[maxn+5];

void dfs1(int x,int fa){
	sum[x]=a[x];
	for(int nxt:node[x]){
		if(nxt==fa){
			continue;
		}
		dfs1(nxt,x);
		sum[x]+=sum[nxt],dp[x]+=dp[nxt]+sum[nxt];
	}
}

void dfs2(int x,int fa){
	for(int nxt:node[x]){
		if(nxt==fa){
			continue;
		}
		f[nxt]=f[x]-sum[nxt]+sum[1]-sum[nxt];
		dfs2(nxt,x);
	}
}

void init(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		node[x].push_back(y);
		node[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
}

void solve(){
	dfs1(1,0);
	f[1]=dp[1];
	dfs2(1,0);
	ll ans=1e19;
	for(int i=1;i<=n;i++){
		ans=min(ans,f[i]);
	}
	printf("%lld",ans);
}

int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：yshpdyt (赞：0)

## 题意

有 $n$ 个顶点的树，有点权为 $c_i$，$d(x,y)$ 是两点路径之间的边数，$f(x)=\sum\limits_{i=1}^n c_i\times d(i,x)$ ，求最小的 $f(x)$。
## Sol 
换根 dp 版题。

首先很容易求出根的答案，就是：
$$f_{root}=\sum\limits_{i=1}^n c_i\times dep_i$$

其中根节点深度为 $0$。

然后考虑换根，假设 $y$ 是 $x$ 的儿子，$y$ 子树内的点到 $y$ 的距离是到 $x$ 的距离减一，$x$ 子树内且非 $y$ 子树内的点到 $y$ 的距离是到 $x$ 距离 $+1$。

从对答案的影响来看，就是减去 $y$  子树内 $c_i$ 的和，加上 $y$ 子树外 $c_i$ 的和。预处理 $siz$ 数组为：

$$siz_x=c_x+\sum\limits_{y\in son_x}siz_y$$

 那么显然有转移方程：
 $$f_y=f_{x}-siz_y+(siz_{root}-siz_y),y\in son_x$$
 
 最后的答案便是：
 $$res=\min\limits_{i=1}^n f_i$$ 
 
 时间复杂度 $O(n)$。
 
 ## Code
 ```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=3e18;
const double eps=1e-6;
ll n;
vector<ll>v[N];
ll c[N],siz[N];
ll dep[N],ans=inf,f[N];
void dfs1(ll x,ll fa,ll d){
    dep[x]=d;
    siz[x]=c[x];
    for(auto y:v[x]){
        if(y==fa)continue;
        dfs1(y,x,d+1);
        siz[x]+=siz[y];
    }
}
void dfs2(ll x,ll fa){
    ans=min(ans,f[x]);
    for(auto y:v[x]){
        if(y==fa)continue;
        f[y]=f[x]-siz[y]+(siz[1]-siz[y]);
        dfs2(y,x);
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n;
    for(int i=1;i<n;i++){
        ll x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1;i<=n;i++)cin>>c[i];
    dfs1(1,0,0);
    for(int i=1;i<=n;i++)f[1]+=dep[i]*c[i];
    dfs2(1,0);
    cout<<ans;
    return 0;
}
```

---

## 作者：vanyou (赞：0)

## 题目大意

有一颗 $N$ 个点的树，每个点有点权，定义$\displaystyle\ f(x)=\sum_{i=1}^{N}(C_i\times d(x,i))$。其中，$x$ 为树上任意一点，$C_i$ 代表点权，$d(x,i)$ 代表两个点路径经过边的条数。求 $f(x)$ 最小值。

## 思路

考虑换根 dp。先暴力求解出 $x=1$，的情况，再用这个答案推出其它点的答案。

思考 $1$ 的子节点答案变化可以发现，子节点的子树上的点答案贡献都会少一次，而不是子节点子树上的点答案贡献都会多一次，所以只需要预处理出以 $1$ 为根的树每个点及子树上点权和，再跑一次 dfs 就可以了。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100010],s[100010],ans;//s[i] 表示以1为根i点的子树权值和
vector<int> g[100010];

void pre(int u,int fa){
	for(auto i:g[u]){
		if(i==fa) continue;
		pre(i,u);
		s[u]+=s[i];//处理子树权值和
	}
	ans+=s[u];//统计x=1的情况
	s[u]+=a[u];
}

void dfs(int u,int fa,int sum){
	sum+=s[1]-s[u]*2;//换根
	ans=min(ans,sum);//取最小值
	for(auto i:g[u]){
		if(i==fa) continue;
		dfs(i,u,sum);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++) cin>>a[i];
	pre(1,0);
	for(auto i:g[1]) dfs(i,1,ans);//推其他点的答案
	cout<<ans;
	return 0;
}
```

---

## 作者：梦应归于何处 (赞：0)

### 题目大意

给你一棵有 $N$ 个顶点的树。顶点编号为 $1$ 至 $N$，第 $i$ 条边连接顶点 $A_i$ 和 $B_i$。

我们还给出了一个长度为 $N$ 的正整数序列 $C = (C_1, C_2, \dots ,C_N)$。设顶点 $a$ 和 $b$ 之间的边数为 $d(a, b)$ ，而 $x = 1, 2, \dots, N$ 的边数为 $\displaystyle f(x) = \sum_{i=1}^{N} (C_i \times d(x, i))$。求 $\displaystyle \min_{1 \leq v \leq N}^{f(v)}$。

### 思路

我们考虑在树上从根节点开始然后每次往他的子树移动这个 $x$。

然后我们发现这个子树里面的 $C$ 都少了一个，子树外的 $C$ 都多了一个，所以我们可以每次移动 $O(1)$ 计算。

### 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp make_pair
#define pll pair<ll,ll>
#define prq priority_queue
using namespace std;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			f = -1;
		}
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
const ll N = 1e5 + 5;
vector<ll> g[N];
ll c[N];
ll ans = 0;
ll totc[N], tot;
inline void init(ll x, ll dep, ll fa) {
	ans += c[x] * dep;
	totc[x] = c[x];
	for (auto v : g[x]) {
		if (v == fa) {
			continue;
		}
		init(v, dep + 1, x);
		totc[x] += totc[v];
	}
}
inline void dfs(ll x, ll fa, ll cnt) {
	ans = min(ans, cnt);
	for (auto v : g[x]) {
		if (v == fa) {
			continue;
		}
		dfs(v, x, cnt - totc[v] + tot - totc[v]);
	}
}
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n = read();
	for (int i = 1; i < n; i++) {
		ll u = read(), v = read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		c[i] = read();
		tot += c[i];
	}
	init(1, 0, 0);
	dfs(1, 0, ans);
	cout<<ans;
	return 0;
}
~~~

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

换根板子。

首先随便找一个根，并记 $s_i$ 表示 $i$ 的子树的权值之和。

接下来考虑一个点从 $u$ 移到其儿子 $v$ 的总权值变化过程。 

容易发现，$v$ 与 $u$ 相比，到 $v$ 的整棵子树内所有点的距离都 $-1$，而其余所有点的距离都 $+1$。

因此权值 $S\gets S-s_v+(s_{all}-s_v)$。

从 $v$ 走回 $u$ 是一样的，只需要修改加减号即可。

```cpp
ll c[100005],s[100005];
int n;
vector<int>v[100005];
ll cur,ans;
void dfs1(int now,int fa,int d){
	s[now]=c[now];
	cur+=d*c[now];
	for(auto i:v[now])if(i^fa)dfs1(i,now,d+1),s[now]+=s[i];
}
void dfs2(int now,int fa){
	ans=min(ans,cur);
	for(auto i:v[now])if(i^fa){
		cur=cur-s[i]+(s[1]-s[i]);
		dfs2(i,now);
		cur=cur+s[i]-(s[1]-s[i]);
	}
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n;
	for(int i=1,x,y;i<n;i++)cin>>x>>y,v[x].push_back(y),v[y].push_back(x);
	for(int i=1;i<=n;i++)cin>>c[i];
	dfs1(1,1,0);//先预处理出 s_i 以及最初的 S
	ans=cur;
	dfs2(1,1);
	cout<<ans<<"\n";
}
```

---

