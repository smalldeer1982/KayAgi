# Drazil and Morning Exercise

## 题目描述

Drazil and Varda are the earthworm couple. They want to find a good place to bring up their children. They found a good ground containing nature hole. The hole contains many rooms, some pairs of rooms are connected by small tunnels such that earthworm can move between them.

Let's consider rooms and small tunnels as the vertices and edges in a graph. This graph is a tree. In the other words, any pair of vertices has an unique path between them.

Each room that is leaf in the graph is connected with a ground by a vertical tunnel. Here, leaf is a vertex that has only one outgoing edge in the graph.

Each room is large enough only to fit one earthworm living in it. Earthworm can't live in a tunnel.

Drazil and Varda have a plan to educate their children. They want all their children to do morning exercises immediately after getting up!

When the morning is coming, all earthworm children get up in the same time, then each of them chooses the farthest path to the ground for gathering with others (these children are lazy, so they all want to do exercises as late as possible).

Drazil and Varda want the difference between the time first earthworm child arrives outside and the time the last earthworm child arrives outside to be not larger than $ l $ (otherwise children will spread around the ground and it will be hard to keep them exercising together).

Also, The rooms that are occupied by their children should form a connected set. In the other words, for any two rooms that are occupied with earthworm children, all rooms that lie on the path between them should be occupied with earthworm children too.

How many children Drazil and Varda may have at most in order to satisfy all conditions above? Drazil and Varda want to know the answer for many different choices of $ l $ .

(Drazil and Varda don't live in the hole with their children)

## 说明/提示

For the first sample the hole looks like the following. Rooms 1 and 5 are leaves, so they contain a vertical tunnel connecting them to the ground. The lengths of farthest path from rooms $ 1–5 $ to the ground are $ 12,9,7,9,12 $ respectively.

If l = 1, we may only choose any single room.

If l = 2..4, we may choose rooms 2, 3, and 4 as the answer.

If l = 5, we may choose all rooms.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF516D/7e38d1221e5eee1b5e202db37a2fe92e264256df.png)

## 样例 #1

### 输入

```
5
1 2 3
2 3 4
4 5 3
3 4 2
5
1 2 3 4 5
```

### 输出

```
1
3
3
3
5
```

## 样例 #2

### 输入

```
12
5 9 3
2 1 7
11 7 2
6 5 5
2 5 3
6 7 2
1 4 4
8 5 7
1 3 8
11 12 3
10 8 2
10
13 14 14 13 13 4 6 7 2 1
```

### 输出

```
10
10
10
10
10
3
3
5
2
1
```

# 题解

## 作者：VenusM1nT (赞：13)

首先想到 $\min f_i$ 肯定在直径上，于是以该点为根，得到一棵随深度增加 $f_i$ 递增的树。然后对点 $u$ 考虑，如果 $u\in S$，那么其祖先也可能 $\in S$，于是一路存下 $f_i$，向上二分找到刚好符合要求的祖先，用差分给这一段都 $+1$，取个最大值就是答案了。  
以最小的这个点为根还是比较难想的，不过想到了就比较好做了。
```cpp
#include<bits/stdc++.h>
#define N 100000
#define reg register
#define inl inline
#define int long long
#define inf 1e18
using namespace std;
int cnt,fst[N+5],nxt[N*2+5],to[N*2+5],w[N*2+5];
int n,Q,S,T,ans,root=1,dis[N+5],disa[N+5],disb[N+5],f[N+5];
vector <int> val,pos;
inl void AddEdge(reg int u,reg int v,reg int c)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
	w[cnt]=c;
}
void Dfs1(reg int u,reg int pre,reg int d[])
{
	for(reg int i=fst[u];i;i=nxt[i])
	{
		reg int v=to[i];
		if(v==pre) continue;
		d[v]=d[u]+w[i];
		Dfs1(v,u,d);
	}
}
void Dfs(reg int u,reg int pre,reg int x)
{
	val.push_back(dis[u]); pos.push_back(u);
	f[u]=1; f[pos[lower_bound(val.begin(),val.end(),dis[u]-x)-val.begin()-1]]--;
	for(reg int i=fst[u];i;i=nxt[i])
	{
		reg int v=to[i];
		if(v==pre) continue;
		Dfs(v,u,x);
		f[u]+=f[v];
	}
	ans=max(ans,f[u]);
	val.pop_back(); pos.pop_back();
}
signed main()
{
	scanf("%lld",&n);
	for(reg int i=1;i<n;i++)
	{
		reg int x,y,z;
		scanf("%lld %lld %lld",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	Dfs1(1,0,disa);
	for(reg int i=1;i<=n;i++) if(disa[i]>disa[S]) S=i;
	memset(disa,0,sizeof(disa));
	Dfs1(S,0,disa);
	for(reg int i=1;i<=n;i++) if(disa[i]>disa[T]) T=i;
	Dfs1(T,0,disb);
	for(reg int i=1;i<=n;i++)
	{
		dis[i]=max(disa[i],disb[i]);
		if(dis[i]<dis[root]) root=i;
	}
	val.push_back(-inf); pos.push_back(0);
	scanf("%lld",&Q);
	while(Q--)
	{
		reg int x;
		scanf("%lld",&x);
		ans=0;
		Dfs(root,0,x);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Kinandra (赞：7)

标签: 图论, 并查集

注意这个 $f$ 的定义是对于全局的, 而不是对于某个连通块, 这里搞错了就不是同一道题了(或许只有我搞错了吧).

#### Part 1

首先两遍 `dfs` 求出每个点的 $f$ . 任意选定一个点作为根, 第一遍 dfs 求出每个点到子树内最远的距离, 第二遍 dfs 用父亲更新儿子. 实现很简单, 不赘述, 可以看看代码.

#### Part 2

观察发现距离**某个点最远的点组成的点集**必然包含**每一条**直径的两个端点中至少一个. 所以显然以任意一条直径的中点作为树根, 每一个点的 $f$ 都不比其子树内的点的 $f$ 大.

根据这个单调性我们可以用尺取(也即 `two points `)来做了. 

``` cpp
#include <bits/stdc++.h>
using namespace std;
long long read();
void chmax(long long &x, long long y) { x < y ? x = y : x; }
int n, q;
struct E {
    int v, w;
};
vector<E> e[200005];
void add(int f, int t, int w) {
    e[f].push_back((E){t, w}), e[t].push_back((E){f, w});
}

long long f[200005], g[200005];

void update(int u, long long d) {
    chmax(g[u], d), (g[u] > f[u]) ? swap(g[u], f[u]) : void();
}

void dfs1(int u, int fa) {
    for (int i = 0, v; i < e[u].size(); ++i)
        if ((v = e[u][i].v) != fa) dfs1(v, u), update(u, f[v] + e[u][i].w);
}

int up[200005], p[200005];
bool cmp(int u, int v) { return f[u] == f[v] ? u < v : f[u] < f[v]; }
void dfs2(int u, int fa) {
    for (int i = 0, v; i < e[u].size(); ++i) {
        if ((v = e[u][i].v) == fa) continue;
        update(v, e[u][i].w + ((f[v] + e[u][i].w == f[u]) ? g[u] : f[u]));
        dfs2(v, u);
    }
    for (int i = 0, v; i < e[u].size(); ++i)
        cmp(u, v = e[u][i].v) ? up[v] = u : up[u] = v;
}

int fa[200005], w[200005];
int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }

void work(long long d) {
    int res = 0;
    for (int i = 1; i <= n; ++i) fa[i] = i, w[i] = 1;
    for (int i = n, j = n; i >= 1; --i) {
        while (f[p[j]] > f[p[i]] + d) --w[find(p[j--])];
        res = max(res, w[p[i]]), w[fa[p[i]] = up[p[i]]] += w[p[i]];
    }
    printf("%d\n", res);
}

int main() {
    n = read();
    for (int i = 1, u, v; i < n; ++i) u = read(), v = read(), add(u, v, read());
    dfs1(1, 0), dfs2(1, 0), q = read();
    for (int i = 1; i <= n; ++i) p[i] = i;
    sort(p + 1, p + 1 + n, cmp);
    while (q--) work(read());
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
long long read() {
    long long x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```







---

## 作者：xht (赞：4)

> [CF516D Drazil and Morning Exercise](https://codeforc.es/contest/516/problem/D)

## 题意

- 给定一棵 $n$ 个点的树，边有边权。
- 定义 $f_x = \max_{i=1}^n \text{dist}(x,i)$。
- $q$ 次询问最大的满足 $\max_{x \in s} f_x - \min_{x \in s} f_x \le l$ 的连通块 $s$ 包含的点数。
- $n \le 10^5$，$q \le 50$。

## 题解

先把 $f$ 线性求出来，然后由大到小双指针扫一遍，发现只会合并，因此并查集维护连通性即可，时间复杂度 $\mathcal O(n \log n + qn\alpha(n))$。

## 代码

```cpp
const int N = 1e5 + 7;
int n, q, fa[N], s[N], v[N], ans;
ll m, f[N][2], g[N];
pair< ll, int > p[N];
vector< pi > e[N];

void dfs1(int x, int fa) {
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i].fi;
		if (y == fa) continue;
		dfs1(y, x);
		ll z = f[y][0] + e[x][i].se;
		if (z > f[x][1]) f[x][1] = z;
		if (z > f[x][0]) swap(f[x][0], f[x][1]);
	}
}

void dfs2(int x, int fa) {
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i].fi;
		if (y == fa) continue;
		int z = e[x][i].se;
		g[y] = max(g[x], f[y][0] + z == f[x][0] ? f[x][1] : f[x][0]) + z;
		dfs2(y, x);
	} 
}

int get(int x) {
	return x == fa[x] ? x : (fa[x] = get(fa[x]));
}

inline void merge(int x, int y) {
	if (x == y) return;
	if (s[x] > s[y]) swap(x, y);
	fa[x] = y, s[y] += s[x];
	ans = max(ans, s[y]);
}

int main() {
	rd(n);
	for (int i = 1, x, y, z; i < n; i++)
		rd(x), rd(y), rd(z), e[x].pb(mp(y, z)), e[y].pb(mp(x, z));
	dfs1(1, 0);
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) p[i] = mp(max(f[i][0], g[i]), i);
	sort(p + 1, p + n + 1);
	reverse(p + 1, p + n + 1);
	rd(q);
	while (q--) {
		rd(m), ans = 1;
		for (int i = 1; i <= n; i++) fa[i] = i, s[i] = 1, v[i] = 0;
		for (int l = 1, r = 0; l <= n; l++) {
			while (r < n && p[l].fi - p[r+1].fi <= m) {
				int x = p[++r].se;
				v[x] = 1;
				for (ui i = 0; i < e[x].size(); i++) {
					int y = e[x][i].fi;
					if (v[y]) merge(get(x), get(y));
				}
			}
			--s[get(p[l].se)], v[get(p[l].se)] = 0;
		}
		print(ans);
	}
	return 0;
}
```

---

## 作者：s_r_f (赞：3)

安利$:$ [杂题选做](https://www.luogu.com.cn/blog/s-r-f/liu-yue-qi-yue-za-ti-xuan-zuo)

---

不难发现权值分布组成了一棵以$f_x$最小的$x$为根的树$,$其中父亲的权值一定$\leq$儿子的权值$.$

那么直接$two-pointers,$然后用并查集维护当前的答案就可以做到 $O(nα(n))$处理一组询问 $.$

$two-pointers$的细节大概是$,$考虑$l,r$的移动$,$ 不难发现$r$变小是不会影响联通情况的$,$所以就从大往小扫$.$

复杂度 $O(qnα(n)).$

代码 $:$

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
template <typename T> void read(T &x){
	x = 0; int f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - '0'; ch = getchar();}
	x *= f;
}
inline void write(int x){if (x > 9) write(x/10); putchar(x%10+'0'); }

const int N = 100050;
int To[N<<1],Ne[N<<1],Dis[N<<1],He[N],_;
inline void add(int x,int y,int w){
	++_; To[_] = y,Ne[_] = He[x],Dis[_] = w,He[x] = _;
	++_; To[_] = x,Ne[_] = He[y],Dis[_] = w,He[y] = _;
}
int n; LL a[N]; int p[N],fa[N],dpt[N]; vector<int>ch[N];
inline bool cmp(int x,int y){ return (a[x] != a[y]) ? (a[x] > a[y]) : (dpt[x] > dpt[y]); }

struct DS{
	int cnt[N],ans,fa[N],size[N];
	inline void init(){ memset(cnt,0,(n+1)<<2),ans = 0; for (int i = 1; i <= n; ++i) fa[i] = i,size[i] = 1,++cnt[1]; }
	inline int Find(int x){ return x == fa[x] ? x : (fa[x] = Find(fa[x])); }
	inline void Merge(int x,int y){
		x = Find(x),y = Find(y); if (x == y) return;
		if (size[x] > size[y]) swap(x,y);
		--cnt[size[x]],--cnt[size[y]]; size[y] += size[x]; ++cnt[size[y]];
		ans = max(ans,size[y]);
		fa[x] = y;
	}
	inline void Dec(int x){
		x = Find(x); --cnt[size[x]];
		if (size[x] == ans && !cnt[size[x]]) --ans;
		--size[x]; ++cnt[size[x]];
	}
	inline int Ans(){ return ans; }
}T;

namespace subtask1{
	LL dis[N];
	inline void dfs(int x,int f){ if (f == -1) dis[x] = 0; for (int y,p = He[x]; p ; p = Ne[p]) if ((y=To[p])^f) dis[y] = dis[x] + Dis[p],dfs(y,x); }
	inline void solve(){
		int i,mx,x,y;
		dfs(1,-1); for (mx = 1,i = 2; i <= n; ++i) if (dis[i] > dis[mx]) mx = i;
		x = mx,dfs(x,-1); for (mx = 1,i = 2; i <= n; ++i) if (dis[i] > dis[mx]) mx = i; y = mx;
		for (i = 1; i <= n; ++i) a[i] = dis[i];
		dfs(y,-1); for (i = 1; i <= n; ++i) a[i] = max(a[i],dis[i]);
	}
}

inline void dfs(int x){
	dpt[x] = dpt[fa[x]]+1;
	for (int y,p = He[x]; p ; p = Ne[p]) if ((y=To[p])^fa[x]) fa[y] = x,dfs(y),ch[x].push_back(y);
}

inline int solve(LL d){
	int ans = 1,l,r,x,i;
	T.init();
	for (l = r = 1; l <= n; ++l){
		while (r < n && a[p[l]]-a[p[r+1]] <= d){
			++r; x = p[r];
			for (i = 0; i < ch[x].size(); ++i) T.Merge(x,ch[x][i]);
		}
		ans = max(ans,T.Ans());
		T.Dec(p[l]);
	}
	return ans;
}

int main(){
	int i,x,y,z,Rt;
	read(n);
	for (i = 1; i < n; ++i) read(x),read(y),read(z),add(x,y,z);
	subtask1::solve();
	for (Rt = 1,i = 2; i <= n; ++i) if (a[i] < a[Rt]) Rt = i;
	dfs(Rt);
	for (i = 1; i <= n; ++i) p[i] = i;
	sort(p+1,p+n+1,cmp);
	int q; LL v;
	read(q); while (q--) read(v),write(solve(v)),putchar('\n');
	return 0;
}
```

---

## 作者：dsidsi (赞：2)

# 「Codeforces516D」Drazil and Morning Exercise

## Description

给出一棵 $n$ 个点的树，给出 $n-1$ 条 $x$ 和 $y$ 之间的边。

每条边有一个长度$v$，询问$q$次，每次询问给出一个$L$，请选择一个符合要求的最大联通块，要求该联通块中所有点到树上离它最远的点的距离的最大值与最小值之差小于等于$L$，输出联通块的最大大小。

$n \leq 100000, q \leq 50$

## Solution

$q \leq 50$，显然没啥用。

设$d(i)$表示$i$到树上离它最远的点的距离。显然这个直接预处理。

~~然后枚举从大到小枚举最小的$d$值$t$，维护满足$d \leq t+lim$点形成的联通块大小，lct即可~~

上面那个方法太难写了（而且不太能过），考虑挖掘一些别的性质，可以发现树上离一个点最远的点只会是直径的两端点，那么如果以直径的中点为根（可以发现这是$d$最小的点），可以发现每个点子树里的$d$值都不小于子树根的$d$值。

有了这个性质就很好做了，从大到小枚举最小的$d$值$x$，对于$d$值超过$d+lim$的点直接删掉，因为它的子树肯定已经被删掉了，所以不会影响连通性。所以可以用并查集维护。时间复杂度$O(n+nq\alpha(n))$

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

inline int gi()
{
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	int sum = 0;
	while('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

inline ll gl()
{
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	ll sum = 0;
	while('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

const int maxn = 100005;

int n, ans;

struct edge
{
	int to, next, w;
} e[maxn * 2];
int h[maxn], tot, rt, fa[maxn], p[maxn], siz[maxn], vis[maxn];
ll dis[maxn], d[maxn];

inline void add(int w, int u, int v)
{
	e[++tot] = (edge) {v, h[u], w}; h[u] = tot;
	e[++tot] = (edge) {u, h[v], w}; h[v] = tot;
}												

void dfs(int u, int fa)
{
	d[u] = max(d[u], dis[u]);
	if (dis[u] > dis[rt]) rt = u;
	for (int i = h[u], v; v = e[i].to, i; i = e[i].next)
		if (v != fa) dis[v] = dis[u] + e[i].w, dfs(v, u);
}

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	x = find(x); y = find(y);
	if (x == y) return ;
	if (siz[y] > siz[x]) swap(x, y);
	siz[x] += siz[y]; ans = max(ans, siz[x]); fa[y] = x;
}

int main()
{
	n = gi(); ++n; --n;
	for (int i = 1; i < n; ++i) add(gi(), gi(), gi());
	
	dfs(1, 0);
	int tmp = rt; dis[rt] = 0; rt = 0;
	dfs(tmp, 0);
	dis[rt] = 0; dfs(rt, 0);

	for (int i = 1; i <= n; ++i) p[i] = i;
	sort(p + 1, p + n + 1, [](const int &a, const int &b) {return d[a] < d[b];});
	int q = gi();
	ll lim;
	while (q--) {
		lim = gl();
		for (int i = 1; i <= n; ++i) fa[i] = i, siz[i] = 1, vis[i] = 0;

		ans = 1;
		for (int k = n, j = n; k >= 1; --k) {
			while (d[p[j]] > d[p[k]] + lim) {
				--siz[find(p[j])];
				--j;
			}
			vis[p[k]] = 1;
			for (int i = h[p[k]], v; v = e[i].to, i; i = e[i].next)
				if (vis[v]) merge(p[k], v);
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
```

---

## 作者：RQ。。。 (赞：1)

# T1 CF516D Drazil and Morning Exercise

- 给定一棵 n 个点的树，边有边权。
- 定义 $f_x = \max_{i=1}^n \text{dist}(x,i)$。
- q 次询问最大的满足 $\max_{x \in s} f_x - \min_{x \in s} f_x \le l$ 的连通块 s 包含的点数。
- $n <= 10^5，q <= 50$。

**solution**

首先，两边dfs求出对于每个点的 $f_x$ ，然后考虑以直径的中点作为根，那么在这个新的树里面，父亲的$f$ 就会$ \le $ 儿子的$f$ ，满足一种单调性，于是用类似双指针的东西维护一遍即可。

 ```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
#define int long long
inline int read()
{
	register int x = 0 , f = 0; register char c = getchar();
	while(c < '0' || c > '9') f |= c == '-' , c = getchar();
	while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48) , c = getchar();
	return f ? -x : x;
}
int n;
int fa[N] , up[N] , f[N] , g[N] , p[N] , siz[N];
struct node { int v , c; node(int v = 0 , int c = 0) : v(v) , c(c) {} };
vector< node > G[N];

void dfs1(int x , int Fa)
{
	int tmp;
	for(auto w : G[x]) if(w.v != Fa)
	{
		dfs1(w.v , x);
		tmp = f[w.v] + w.c;
		if(tmp > f[x]) g[x] = f[x] , f[x] = tmp;
		else if(tmp > g[x]) g[x] = tmp;
	}
}

inline bool cmp(const int &A , const int &B) { return f[A] == f[B] ? A < B : f[A] < f[B]; }

void dfs2(int x , int Fa)
{
	int tmp;
	for(auto w : G[x]) if(w.v != Fa)
	{
		tmp = w.c + ((f[w.v] + w.c == f[x]) ? g[x] : f[x]);
		if(tmp > f[w.v]) g[w.v] = f[w.v] , f[w.v] = tmp;
		else if(tmp > g[w.v]) g[w.v] = tmp;
		dfs2(w.v , x);
	}
	for(auto w : G[x]) if(cmp(x , w.v)) up[w.v] = x; else up[x] = w.v;
}

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void solve(int d)
{
	for(int i = 1 ; i <= n ; ++i) fa[i] = i , siz[i] = 1;
	int ans = 0;
	for(int i = n , j = n ; i >= 1 ; --i)
	{
		while(f[p[j]] > f[p[i]] + d) --siz[find(p[j--])];
		ans = max(ans , siz[p[i]]); siz[fa[p[i]] = up[p[i]]] += siz[p[i]];
	}
	cout << ans << '\n';
}

signed main()
{
	n = read(); int u , v , c;
	for(int i = 1 ; i < n ; ++i)
		u = read() , v = read() , c = read() , G[u].push_back(node(v , c)) , G[v].push_back(node(u , c));
	dfs1(1 , 0); dfs2(1 , 0);
	for(int i = 1 ; i <= n ; ++i) p[i] = i;
	sort(p + 1 , p + 1 + n , cmp);
	int Q = read(); while(Q--)  solve(read());
	return 0;
}
 ```



---

## 作者：Fading (赞：0)

这种题第一步一定是先求出$f$数组，我用了换根 dp，当然直接 lca 也可以，不过正常实现起来会很慢。

然后$q$很小，直接双指针+LCT，没了。吗？

众所周知，LCT 的常数大得和$\log^2n$差不多，所以这绝对会被卡，想都不用想，更何况它给了一个$f$？所以事情并不简单，我们老老实实去挖掘性质。

接下来有经验的选手可以一眼看出（我想了$10$分钟...），一个点的$f$值一定是在直径$2$个端点处取到的。

然后看看直径以外的点，发现离直径越远，$f$值越大。

再看看直径上的点。显然树的中心（$f$值最小的点）一定在直径上，然后离中心越远，$f$值越大。

以上都可以用反证法证明，这里不再赘述。

于是我们惊奇地发现如果以中心为根节点，这个树就成了一个小根堆。

接下来枚举连通块根节点。正好根节点就是子树最小值，因此我们可以贪心地找到所有可行的点，显然这是一个连通块。

然后这题就切了。

关于找到可行的点，我选择了堆+启发式合并。这看起来是$O(qn\log^2_2n)$，实际上每个点最多只会被删除一次，加上启发式合并的继承，这是$O(qn\log_2n)$的，而且常数跑不满。可惜我用了 priority_queue，慢的一批。。。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int dep[202020],n,head[202020],tot,rt;
struct edge{
	int to,nxt;ll dis;
}g[404040];
inline void made(int from,int to,ll dis){
	g[++tot].to=to;g[tot].dis=dis;g[tot].nxt=head[from];head[from]=tot;
}
ll dp[202020],fadis[202020],F[202020];
int id[202020],tid[202020];
void dfs1(int u,int fa){
	dp[u]=0;tid[u]=id[u]=0;
	for (int i=head[u];i;i=g[i].nxt){
		int v=g[i].to;
		if (v==fa) continue;
		fadis[v]=g[i].dis;
		dfs1(v,u);
		if (dp[u]<=dp[v]+g[i].dis){
			tid[u]=id[u];id[u]=v;dp[u]=dp[v]+g[i].dis;
		}else if (dp[tid[u]]+fadis[tid[u]]<=dp[v]+g[i].dis) tid[u]=v;
	}
}
void dfs2(int u,int fa,ll LAS){
	F[u]=max(dp[u],LAS);
	for (int i=head[u];i;i=g[i].nxt){
		int v=g[i].to;
		if (v==fa) continue;
		if (v==id[u]) dfs2(v,u,max(LAS,dp[tid[u]]+fadis[tid[u]])+g[i].dis);
		else dfs2(v,u,max(LAS,dp[u])+g[i].dis);
	}
}
int ANS,now,tcnt,tpos[202020];
priority_queue<ll> dl[202020];
void dfs3(int u,int faa,ll L){
	tpos[u]=++tcnt;
	for (int i=head[u];i;i=g[i].nxt){
		int v=g[i].to;
		if (v==faa) continue;
		dfs3(v,u,L);
		if (dl[tpos[u]].size()<dl[tpos[v]].size()) swap(tpos[u],tpos[v]);
		while (!dl[tpos[v]].empty()){
			dl[tpos[u]].push(dl[tpos[v]].top());
			dl[tpos[v]].pop();
		}
	}
	dl[tpos[u]].push(F[u]);
	while (F[u]+L<dl[tpos[u]].top()) dl[tpos[u]].pop();
	ANS=max(ANS,(int)dl[tpos[u]].size());
}
signed main(){
	n=read();
	for (int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		made(x,y,z);made(y,x,z);
	}
	dfs1(1,0);dfs2(1,0,0);
	F[0]=1e18;
	for (int i=1;i<=n;i++){
		if (F[rt]>F[i]) rt=i;
	}
	int Q=read();
	while (Q--){
		tcnt=ANS=0;
		while (!dl[tpos[rt]].empty()) dl[tpos[rt]].pop();
		dfs3(rt,0,read());
		printf("%d\n",ANS);
	}
	return 0;
}


```


---

## 作者：MikukuOvO (赞：0)

首先我们通过预处理可以求出每一个点的$f$。

考虑到能更新一个点的$f$的点一定会是一条直径的两个端点，因此我们找出直径后两遍$dfs$来求$f$数组即可。

继续挖掘性质，发现这个$f$值是具有单调性的，换而言之，如果我们钦定直径的中点作为根节点，那么每颗子树的$f$都具有小根堆的性质。

这样我们考虑从大到小枚举连通块中最小的$f$，$twopointer$做一下就可以了，统计连通块大小用并查集维护即可。

考虑这样做为什么是对的呢，根据小根堆性质，如果一个点被删除了，那么它的子树中所有点都会被删除，因此我们就保证了联通的单调性，删除直接在并查集的$siz$减一即可。

---

## 作者：yzc2005 (赞：0)

# 一、题意
见[题目链接](https://www.luogu.com.cn/problem/CF516D)

# 二、题解
首先，求出树的直径的两个端点，线性的算出 $f$。
接着，我们发现 $f$ 最小的 $u$ 一定是直径的中点。
又发现，以直径中点为根，$\forall{u_{\in tree(root)}, v_{\in subtree(u)}},f(v) >= f(u)$。~~（什么神仙结论qwq~~
于是将结点按 $f$ 从大到小排序，直接 $two-pointers$ + 并查集维护即可，因为被删除的点一定是叶子节点。

# 三、代码
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register
#define fu(i, a, b) for(rg int i = (a), I = (b) + 1; i < I; ++i)
#define fd(i, a, b) for(rg int i = (a), I = (b) - 1; i > i; --i)
#define go(u) for(rg int o = head[u], v = to[o], w = val[o]; o; o = nxt[o], v = to[o], w = val[o])
template <class T> inline void read(T &x) {
	x = 0; char ch = getchar();
	while(ch < 48 || ch > 57) ch = getchar();
	while(ch >= 48 && ch <= 57) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
}
template <class T> inline void ckmax(T &a, T b) {a = max(a, b);}
template <class T> inline void ckmin(T &a, T b) {a = min(a, b);}

const int N = 1e5 + 5;
int n, q, cnt, head[N], to[N << 1], nxt[N << 1], val[N << 1], rt, id[N], mp[N], fa[N], siz[N];
ll f[N], d[N], qd;

inline void add(int u, int v, int w) {
	to[++cnt] = v, val[cnt] = w;
	nxt[cnt] = head[u], head[u] = cnt;
}  

void dfs1(int u, int fa) {
	go(u) 
		if(v != fa) {
			f[v] = f[u] + w;
			dfs1(v, u); 
		}
}

void dfs2(int u, int fa) {
	go(u) 
		if(v != fa) {
			d[v] = d[u] + w;
			dfs2(v, u);
		}
}

void dfs(int u, int fa) {
	ckmax(d[u], f[u]);
	go(u)
		if(v != fa) {
			f[v] = f[u] + w;
			dfs(v, u);
		}
}

int get(int x) {
	return x == fa[x] ? x : fa[x] = get(fa[x]);
}

inline void merge(int u, int v) {
	if(u == v) return;
	if(siz[u] > siz[v]) swap(u, v);
	siz[v] += siz[u], fa[u] = v;
} 

inline bool cmp(const int &a, const int &b) {return d[a] > d[b];}

int main() {
	read(n);
	for(int i = 1, u, v, w; i < n; ++i) {
		read(u), read(v), read(w);
		add(u, v, w), add(v, u, w);
	}
	dfs1(1, 0); fu(i, 1, n) if(f[rt] < f[i]) rt = i; dfs2(rt, 0); 
	rt = 0; fu(i, 1, n) if(d[rt] < d[i]) rt = i; f[rt] = 0; dfs(rt, 0);
	fu(i, 1, n) id[i] = i; sort(id + 1, id + n + 1, cmp);
	fu(i, 1, n) mp[id[i]] = i;
	read(q); while(q--) {
		read(qd); int ans = 1;
		fu(i, 1, n) fa[i] = i, siz[i] = 1;
		for(rg int i = 1, l = 1; i <= n; ++i) {
			while(d[id[l]] - qd > d[id[i]]) --siz[get(id[l++])];
			go(id[i]) if(l <= mp[v] && mp[v] <= i) merge(get(id[i]), get(v));
			ckmax(ans, siz[get(id[i])]);
		}
		printf("%d\n", ans);
	}
	return 0;
} 
```

# 四、总结
**树的直径的性质！！**


---

## 作者：asuldb (赞：0)

[题目](https://www.luogu.org/problem/CF516D)

首先我们知道，在树上距离一个点最远的点一定是直径的两个端点之一

首先两遍$\rm dfs$把直径求出来，定义$d(u)$表示点$u$距离其最远点的距离，有了直径我们就能求出$d$数组了

当然可以树形$\rm dp$，设$f_{x,i,j}$表示在$x$子树内部选择一个最大值为$i$最小值为$j$的最大联通块是多少，显然这样的复杂度奇高无比

考虑把求出的直径来好好利用一下

首先感性的发现一下，设$x$为直径中点，那么$d(x)$肯定是最小的点权，又发现我们钦定$x$为根，那么一个点的点权肯定比其子树内部的点都要小

那么我们就钦定$x$为根，之后枚举一个联通块的最高点$i$，也就是点权的最小值

由于深度越大点权越大，于是我们就把这个子树内部所有点权不超过$d(i)+L$的点都选上，这显然构成一个联通块

于是问题转化成了求一个子树内部有多少个点的点权小于某个给定值，不难发现这是主席树裸题

说的好，于是我选择$\rm dsu\ on\ tree$，复杂度$O(nq\log n+n\log^2n)$，莫名其妙跑得比并查集老哥们快

代码

```cpp
#include<bits/stdc++.h>
#define re register
#define LL long long
#define lb(x) ((x)&(-x))
#define max(a,b) ((a)>(b)?(a):(b))
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
const int maxn=1e5+5;
struct E{int v,nxt,w;}e[maxn<<1];
int n,m,num,Rt,rt,sz,S;
int head[maxn],sum[maxn],son[maxn],pos[maxn],dep[maxn],d[maxn],Ans[55];
LL pre[maxn],mx[maxn],q[55],c[maxn];
inline void add(int x,int y,int w) {
	e[++num].v=y;e[num].nxt=head[x];head[x]=num;e[num].w=w;
}
inline int find(LL x) {
	int l=1,r=sz,now=0;
	while(l<=r) {
		int mid=l+r>>1;
		if(c[mid]<=x) now=mid,l=mid+1;else r=mid-1;
	}
	return now;
}
void dfs(int x,int fa) {
	for(re int i=head[x];i;i=e[i].nxt) {
		if(e[i].v==fa) continue;
		pre[e[i].v]=pre[x]+e[i].w;
		dfs(e[i].v,x);
	}
}
void dfs1(int x) {
	sum[x]=1;
	for(re int i=head[x];i;i=e[i].nxt) {
		if(dep[e[i].v]) continue;
		dep[e[i].v]=dep[x]+1;dfs1(e[i].v);sum[x]+=sum[e[i].v];
		if(sum[e[i].v]>sum[son[x]]) son[x]=e[i].v;
	}
}
inline void add(int x,int v) {
	for(re int i=x;i<=sz;i+=lb(i)) d[i]+=v;
}
inline int ask(int x) {
	int now=0;
	for(re int i=x;i;i-=lb(i)) now+=d[i];
	return now;
}
void calc(int x,int o) {
	add(pos[x],o);
	for(re int i=head[x];i;i=e[i].nxt)
	if(dep[e[i].v]>dep[x]&&S!=e[i].v) calc(e[i].v,o);
}
void dsu(int x,int k) {
	for(re int i=head[x];i;i=e[i].nxt) 
	if(dep[e[i].v]>dep[x]&&son[x]!=e[i].v) dsu(e[i].v,0);
	if(son[x]) dsu(son[x],1);
	S=son[x],calc(x,1),S=0;
	for(re int i=1;i<=m;i++) {
		int g=ask(find(mx[x]+q[i]));
		Ans[i]=max(Ans[i],g);
	}
	if(!k) calc(x,-1);
}
int main() {
	n=read();
	for(re int x,y,w,i=1;i<n;++i)
		x=read(),y=read(),w=read(),add(x,y,w),add(y,x,w);
	m=read();for(re int i=1;i<=m;i++) scanf("%lld",&q[i]);
	dfs(1,0);rt=1;
	for(re int i=2;i<=n;i++) if(pre[i]>pre[rt]) rt=i;
	pre[rt]=0;dfs(rt,0);Rt=1;
	for(re int i=1;i<=n;i++) mx[i]=pre[i];
	for(re int i=2;i<=n;i++) if(pre[i]>pre[Rt]) Rt=i;
	pre[Rt]=0;dfs(Rt,0);
	for(re int i=1;i<=n;i++) mx[i]=max(mx[i],pre[i]);
	rt=1;for(re int i=2;i<=n;i++) if(mx[i]<mx[rt]) rt=i;
	dep[rt]=1;dfs1(rt);
	for(re int i=1;i<=n;i++) c[i]=mx[i];
	std::sort(c+1,c+n+1);sz=std::unique(c+1,c+n+1)-c-1;
	for(re int i=1;i<=n;i++) pos[i]=find(mx[i]);
	dsu(rt,1);for(re int i=1;i<=m;i++) printf("%d\n",Ans[i]);
	return 0;
}

```


---

