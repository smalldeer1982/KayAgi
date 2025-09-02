# Connecting Cities

## 题目描述

有 $n$ 个点排成一行，在第 $i,j$ 个点之间连边的代价为 $|i-j| \times D+A_i+A_j$，求将它们连成一棵树的最小代价。

$1 \leq n \leq 2\times 10^5$，$1 \leq D,A_i \leq 10^9$

## 样例 #1

### 输入

```
3 1
1 100 1```

### 输出

```
106```

## 样例 #2

### 输入

```
3 1000
1 100 1```

### 输出

```
2202```

## 样例 #3

### 输入

```
6 14
25 171 7 1 17 162```

### 输出

```
497```

## 样例 #4

### 输入

```
12 5
43 94 27 3 69 99 56 25 8 15 46 8```

### 输出

```
658```

# 题解

## 作者：chenxia25 (赞：11)

洛谷的AtC接口貌似坏掉了，水不了这道紫题了，但是题解还是可以水的（大雾

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4569) & [AtC题目页面传送门](https://atcoder.jp/contests/keyence2019/tasks/keyence2019_e)

>有$n$个点，第$i$个点的权值为$a_i$。给定常数$d$，在点$i,j$之间连边的代价是$|i-j|d+a_i+a_j$。求将它们连成一棵树的最小代价。

>$n\in\left[1,10^5\right]$。

首先不难发现，原题相当于，求完全图的MST的权，其中点$i,j$之间的边权为$|i-j|d+a_i+a_j$。如果直接Kruskal的话，建图就要爆炸，边数是$\mathrm O\!\left(n^2\right)$的。考虑用某些MST的奇技淫巧。

我们的目的是，尽可能删掉一些边，留下尽量少的边，使得MST的权不变。

注意到这样一条经典的性质：MST不可能包含一个环上所有的最大边。证明很简单：反证法。若包含，则随意去掉一个环上的最大边$(x,y)$，此时整棵树断成两部分，$x,y$在不同的部分。由于是个环，那么环上一定有一条反向的不包含 $(x,y)$的$x\to y$路径，连接两个部分，这条路径上显然有连接两部分的另一条边，选上它得到另一棵生成树。这条边边权严格小于$(x,y)$的权，所以原树不可能是MST。得证。

不妨研究一些环，看能不能用这个性质删边。从最简单的三元环入手。

首先，$i<j$间边权可变形为$a_i-id+a_j+jd$。令$A_i=a_i-id,B_i=a_i+id$，那么就是$A_i+B_j$。对于三元环$(i,j,k)$，

1. 当$i<j<k$时，$(i,j)$非严格最大当且仅当$B_j\geq B_k,A_i+B_j\geq A_j+B_k$。注意到$B_j\geq B_k,A_i\geq A_j$显然是它的充分条件，我们完全可以只用这个，正确性健在；
1. 当$i<k<j$时，$(i,j)$非严格最大当且仅当$B_j\geq B_k,A_i\geq A_k$；
1. 当$k<i<j$时，$(i,j)$非严格最大当且仅当$A_i+B_j\geq A_k+B_i,A_i\geq A_k$。同$1$，充分条件是$B_j\geq B_i,A_i\geq A_k$。

把$1,2$放一起研究，可以得出共同点：$B_j\geq B_k,A_i\geq A_{\text{位置在第2的点}}$。那么我们想，对于一堆在$i$右边的、$A$值$\leq A_i$的点，我们一定可以把它们连向$i$的边互相毙，毙的只剩一个，即那个$B$值最小的。

这看起来很成立，但是似乎仅在严格的时候成立，因为根据上述性质，只有最大边唯一的时候，才可以肆无忌惮地毙掉最大边，否则一般情况下需要保证其他最大边建在。不过在这里的特殊情况，即使非严格也是成立的。证明：若不存在任意一个MST使得它包含任意一条被毙掉的边则已，否则选择一个：设留下来的点是$x$。对于任意一个被毙掉的还在MST里的边$(i,y)$，若$(x,y)$不在MST里即可直接换成$(x,y)$，否则$(i,x)$一定不在（因为生成树里不可能有环），但是不能直接换成$(i,x)$，因为它是唯一的，而有那么多被毙掉的边等着换呢。如此，只要证满足$(i,y),(x,y)$都在MST里的被毙掉的边$(i,y)$最多只有一个。这是显然的，因为若有两个$y_0,y_1$，则$(i,x,y_0,y_1)$构成四元环。得证。

同理，一堆在$i$左边的、$B$值$\leq B_i$的点，我们也可以留下$A$值最小的，其他都毙掉。

不过这样，两个毙法一综合，问题又出现了。。有的点对$(i,j)(i<j)$，它们之间的边可能会被考虑两次（$j$左边和$i$右边），这样就可能是即被删掉，又被留下来的状态。这里有一个巧妙的处理方法：观察$A_i\geq A_j$，展开得$a_i-id\geq a_j-jd$，注意到因为$i<j$，所以$-id>-jd$，那么充分条件就是$a_i\geq a_j$。同理，$B_j\geq B_i$的充分条件是$a_j\geq a_i$。在$a$值互不相同的时候，两者恰好只能选一个，也就是说完全图里每条边恰好被考虑了一遍，就不存在问题了。如果$a$值有相同的呢？只需要再加第二个关键字：位置，这样就一定能比出大小了。

如此，每个点两侧最多各有一条边留下来，边数复杂度$\mathrm O(n)$。再用BIT xjb随便维护一下建图，然后Kruskal，时间复杂度$\mathrm O(n\log n)$。

代码也没啥需要说的：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define X first
#define Y second
#define pb push_back
const int inf=0x3f3f3f3f3f3f3f3f;
int lowbit(int x){return x&-x;}
const int N=200000;
int n,d;
int a[N+1];
pair<int,int> p[N+1];
struct bitree{
	pair<int,int> mn[N+1];
	void init(){
		for(int i=1;i<=n;i++)mn[i]=mp(inf,0);
	}
	void chkmn(int x,pair<int,int> v){
		while(x<=n)mn[x]=min(mn[x],v),x+=lowbit(x);
	}
	int Mn(int x){
		pair<int,int> res(inf,0);
		while(x)res=min(res,mn[x]),x-=lowbit(x);
		return res.Y;
	}
}bit,bit_r;
vector<pair<int,int> > eg;
struct ufset{//并查集 
	int fa[N+1];
	void init(){memset(fa,0,sizeof(fa));}
	int root(int x){return fa[x]?fa[x]=root(fa[x]):x;}
	bool mrg(int x,int y){
		x=root(x);y=root(y);
		if(x==y)return false;
		return fa[x]=y,true;
	}
}ufs;
int cst(pair<int,int> x){//边权 
	if(x.X>x.Y)swap(x.X,x.Y);
	return a[x.X]+a[x.Y]+(x.Y-x.X)*d;
}
bool cmp(pair<int,int> x,pair<int,int> y){
	return cst(x)<cst(y);
}
int kruskal(){//Kruskal 
	sort(eg.begin(),eg.end(),cmp);
	int ans=0;
//	for(int i=0;i<eg.size();i++)printf("%lld %lld\n",eg[i].X,eg[i].Y);
	for(int i=0;i<eg.size();i++)ans+=ufs.mrg(eg[i].X,eg[i].Y)*cst(eg[i]);
	return ans;
}
signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++)scanf("%lld",a+i),p[i]=mp(a[i],i);
	sort(p+1,p+n+1);
	bit.init();bit_r.init();
	for(int i=1;i<=n;i++){//BIT建图 
		int mn1=bit.Mn(p[i].Y-1),mn2=bit_r.Mn(n-p[i].Y);
		if(mn1)eg.pb(mp(p[i].Y,mn1));
		if(mn2)eg.pb(mp(p[i].Y,mn2));
		bit.chkmn(p[i].Y,mp(p[i].X-p[i].Y*d,p[i].Y));bit_r.chkmn(n-p[i].Y+1,mp(p[i].X+p[i].Y*d,p[i].Y));
	} 
	cout<<kruskal();
	return 0;
}
```

官方题解还给出了另一种分治的方法。就是说，把边分成在左半边内、在右半边内、横跨两半边三类，处理横跨两半边的，另外两种递归下去。考虑如何处理。我们选择左半边$A$值最小的点$x$连所有右半边的点，选择右半边$B$值最小的点$y$连所有左半边的点，这样一来其他所有的横跨两半边的边$(x',y')$都被毙掉了，因为$(x,y),(x,y'),(x',y)$都在，$(x',y')$成了环中最大的边。至于严格非严格的问题，xjb再证一下即可。这是在四元环上作文章的。边数复杂度$\mathrm O(n\log n)$，时间复杂度$\mathrm O\!\left(n\log^2n\right)$。

代码没写。应该很好写？

综上所述，下次遇到这样的人类智慧题我还是做不出来。

---

## 作者：lemondinosaur (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/AT4569)

---
考虑如何去掉这个绝对值，

换句话说，如何减少边数并且能建出 MST。

在求解偏序问题时，往往会分而治之，

这样原来 $O(n^2)$ 的做法就能够被优化。

考虑将所有点对半折开，

左半部分和右半部分的建边分治处理，

只考虑横跨两部分的建边，

若左半部分的点为 $j$，右半部分的点为 $i$

边权就可以转换成：

$$
(A_i+i\times d)+(A_j-j\times d)
$$

既然 $i$ 和 $j$ 独立出来，那么只需要选出

右半部分 $\min\{A_i+i\times d\}$ 所对应的 $i$，

左半部分 $\min\{A_j-j\times d\}$ 所对应的 $j$，

将 $j$ 与右半部分所有点连边，$i$ 同理。

那么这样就只有 $O(n\log n)$ 条边，

用 Kruskal 跑最小生成树就可以做到 $O(n\log^2n)$。

---
# Code
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define rr register
using namespace std;
const int N=200011; typedef long long lll;
struct node{int x,y; lll w;}e[N<<5];
lll a[N],b[N],D,ans; int n,f[N],m;
inline signed iut(){
	rr int ans=0; rr char c=getchar();
	while (!isdigit(c)) c=getchar();
	while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans; 
}
bool cmp(node x,node y){return x.w<y.w;}
inline signed getf(int u){return f[u]==u?u:f[u]=getf(f[u]);}
inline void dfs(int l,int r){
    if (l==r) return;
    rr int mid=(l+r)>>1,t0=l,t1=r;
    for (rr int i=l;i<=mid;++i)
        if (a[t0]>a[i]) t0=i;
    for (rr int i=r;i>mid;--i)
        if (b[t1]>b[i]) t1=i;
    for (rr int i=l;i<=mid;++i)
	    e[++m]=(node){i,t1,a[i]+b[t1]};
    for (rr int i=r;i>mid;--i)
	    e[++m]=(node){t0,i,a[t0]+b[i]};
    dfs(l,mid),dfs(mid+1,r);
}
signed main(){
	n=iut(),D=iut();
	for (rr int i=1;i<=n;++i){
		rr int x=iut(); f[i]=i;
		a[i]=x-i*D,b[i]=x+i*D;
	}
	dfs(1,n),sort(e+1,e+1+m,cmp);
	for (rr int i=1;i<=m;++i){
		rr int fa=getf(e[i].x),fb=getf(e[i].y);
		if (fa!=fb) f[fa]=fb,ans+=e[i].w;
	}
	return !printf("%lld",ans);
}
```

---

## 作者：沉石鱼惊旋 (赞：3)

# 题目翻译

点 $i,j$ 连边的代价是 $|i-j|\times d+a_i+a_j$，问最小生成树边权之和。

$1\leq n\leq 2\times 10^5$，$1\leq d,a_i\leq 10^9$。

# 题目思路

典。

$\mathcal O(n^2)$ 条边很多情况都可以直接上 Boruvka。

Boruvka 大致流程是维护联通块，每一轮把联通块之间最短的边连起来。每次联通块个数至少减半，一共进行 $\mathcal O(\log n)$ 轮。

那么考虑如何快速求出这些联通块间最短的边。

首先绝对值可以拆开，$w(i,j)=\begin{cases}(a_i+i\times d)+(a_j - j\times d)&i\lt j\\(a_i-i\times d)+(a_j + j\times d)&i\gt j\end{cases}$。

不妨设 $b_i=a_i-i\times d,c_i=a_i+i\times d$。

考虑枚举每个联通块之内的点，以及这个点 $i$ 属于 $i\leq j$ 还是 $i\gt j$。如果是 $i\lt j$ 的情况，相当于在 $[i+1,n]$ 找到最小的 $c_j$。$i\gt j$ 同理。

但是这样可能会导致连到同一个联通块的边，那么我们就把联通块内的点的相关的值全部设成 $+\infty$。

使用线段树维护单点修改，区间查询可以做到 $\mathcal O(n\log^2 n)$。Boruvka 和并查集带一只 $\log$，线段树带一只 $\log$。并查集这里需要按大小启发式合并（因为要维护联通块内的所有点）。

# 完整代码

[AT submission 59342851](https://atcoder.jp/contests/keyence2019/submissions/59342851)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <typename T>
void chkmn(T &x, T y) { x = min(x, y); }
typedef long long ll;
const ll inf = 1e18;
int n;
ll d;
ll a[200020];
ll b[200020];
ll c[200020];
int fa[200020];
int sz[200020];
vector<int> vec[200020];
array<ll, 2> p[200020];
int F(int u) { return fa[u] ^ u ? fa[u] = F(fa[u]) : u; }
void U(int u, int v)
{
    u = F(u), v = F(v);
    if (u == v)
        return;
    if (sz[u] > sz[v])
        swap(u, v);
    fa[u] = v;
    sz[v] += sz[u];
    sz[u] = 0;
    for (int i : vec[u])
        vec[v].push_back(i);
    vec[u].clear();
}
struct SegTree
{
    struct node
    {
        array<ll, 2> mn;
    } t[200020 << 2];
#define ls id << 1
#define rs id << 1 | 1
    void push_up(int id) { t[id].mn = min(t[ls].mn, t[rs].mn); }
    void build(ll *a, int id = 1, int l = 1, int r = n)
    {
        if (l == r)
            return t[id].mn = {a[l], l}, void();
        int mid = l + r >> 1;
        build(a, ls, l, mid);
        build(a, rs, mid + 1, r);
        push_up(id);
    }
    void update(ll p, ll k, int id = 1, int l = 1, int r = n)
    {
        if (r < p || l > p)
            return;
        if (p <= l && r <= p)
            return t[id].mn[0] = k, void();
        int mid = l + r >> 1;
        update(p, k, ls, l, mid);
        update(p, k, rs, mid + 1, r);
        push_up(id);
    }
    array<ll, 2> query(int ql, int qr, int id = 1, int l = 1, int r = n)
    {
        if (r < ql || l > qr)
            return {inf, 0};
        if (ql <= l && r <= qr)
            return t[id].mn;
        int mid = l + r >> 1;
        return min(query(ql, qr, ls, l, mid), query(ql, qr, rs, mid + 1, r));
    }
} T1, T2;
int main()
{
    read(n, d);
    for (int i = 1; i <= n; i++)
        read(a[i]);
    for (int i = 1; i <= n; i++)
    {
        b[i] = a[i] - d * i;
        c[i] = a[i] + d * i;
    }
    T1.build(b);
    T2.build(c);
    for (int i = 1; i <= n; i++)
        fa[i] = i, sz[i] = 1, vec[i].push_back(i);
    int cnt = n;
    ll ans = 0;
    while (cnt > 1)
    {
        for (int i = 1; i <= n; i++)
        {
            if (F(i) != i)
                continue;
            p[i] = {inf, 0};
            for (int j : vec[i])
            {
                T1.update(j, inf);
                T2.update(j, inf);
            }
            for (int j : vec[i])
            {
                if (j > 1)
                {
                    auto [w, k] = T1.query(1, j - 1);
                    chkmn(p[i], {w + c[j], k});
                }
                if (j < n)
                {
                    auto [w, k] = T2.query(j + 1, n);
                    chkmn(p[i], {w + b[j], k});
                }
            }
            for (int j : vec[i])
            {
                T1.update(j, b[j]);
                T2.update(j, c[j]);
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (F(i) == i && F(p[i][1]) != F(i))
                U(p[i][1], i), ans += p[i][0], cnt--;
        }
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：_NTT_ (赞：3)

## 题意
给定 $n$ 个点的点权 $a$，点 $i$ 和 点 $j$ 之间边的权值为 $\lvert i-j\rvert\times D+a_i+a_j$，求这个图的最小生成树。  

## 分析
有一种叫做 `Boruvka` 的最小生成树算法，流程大致是这样的：对于每个连通块每次找到连出去的最短的边，然后合并这条边连接的两个连通块直到全局联通，一开始每个点单独构成一个连通块。  
于是问题转化成如何求一个点连出去的最短边，考虑分类讨论，假设求距离 $i$ 点最近的点 $j$。
$$
w_{i,j}=
\begin{cases}
	(a_j - jD) + (iD+a_i)&\text{if } j<i \\
	(a_j + jD) + (-iD+a_i)&\text{if } j>i \\
\end{cases}
$$

注意到前面一个括号只跟 $j$ 有关，后面只跟 $i$ 有关，于是只需要维护 $a_j + jD$ 和 $a_j - jD$ 的最小值。  
然后问题就变得简单了，维护两个线段树分别对应两个情况，然后每个连通块存一个 `vector`，然后把连通块所有元素在线段树上的值都改成 $\infty$，再对于每一个元素查询即可，最后再把连通块所有元素改回来。

## 细节
因为这个做法复杂度是 $O(\alpha(n)n\log^2 n)$ 并且线段树的 $4$ 倍常数乘上修改查询的 $6$ 倍常数，需要非常卡常才可通过。

注意一些细节：
- 并查集按秩合并应当按大小合并，方便维护 `vector` 的启发式合并。
- `find` 函数用循环写。
- 两个函数的值开个数组存下来，避免重复计算。
- 线段树维护的是最小值的下标，方便合并。
- 不要 `define int long long`。

最后发现实际上也跑的挺快的，都在一秒内跑过了。

## 代码
```cpp
typedef long long ll;

const int N = 2e5 + 10, M = N << 2, INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int n, d, a[N], fa[N], siz[N], to[N];
ll res, b[N], c[N];
vector<int> v[N];
pair<ll, int> mn[N];

il int find(int x) {
	while(x != fa[x]) x = fa[x] = fa[fa[x]];
	return x;
}
il void merge(int x, int y) {
	x = find(x); y = find(y);
	if(siz[x] > siz[y]) swap(x, y);
	fa[x] = y; siz[y] += siz[x];
	for(int i : v[x]) v[y].eb(i);
}

#define mid (l + r >> 1)
#define lc (k << 1)
#define rc (k << 1 | 1)

struct smt {
	ll a[N];
	int mn[M];
	il void update(int k, int l, int r, int p, ll x) {
		if(l == r) return (void)(mn[k] = l, a[l] = x);
		if(p <= mid) update(lc, l, mid, p, x);
		else update(rc, mid + 1, r, p, x);
		if(a[mn[lc]] < a[mn[rc]]) mn[k] = mn[lc];
		else mn[k] = mn[rc];
	}
	il int query(int k, int l, int r, int L, int R) {
		if(l >= L && r <= R) return mn[k];
		int res = 0, x;
		if(L <= mid) res = query(lc, l, mid, L, R);
		if(R > mid) {
			x = query(rc, mid + 1, r, L, R);
			if(!res || a[x] < a[res]) res = x;
		}
		return res;
	}
} t1, t2; 

signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> d;
	rep(i, 1, n) {
		cin >> a[i];
		v[i].eb(i);
		siz[i] = 1;
		fa[i] = i;
		t1.update(1, 1, n, i, b[i] = a[i] - (ll)i*d);
		t2.update(1, 1, n, i, c[i] = a[i] + (ll)i*d);
	}
	
	int s = n;
	while(s > 1) {
		rep(i, 1, n) {
			if(i != fa[i]) continue;
			mn[i] = {INFLL, 0};
			for(auto x : v[i]) t1.update(1, 1, n, x, INFLL), t2.update(1, 1, n, x, INFLL);
			for(auto x : v[i]) {
				if(x > 1) {
					int y = t1.query(1, 1, n, 1, x - 1);
					ll w = t1.a[y] + c[x];
					if(mn[i].fir > w) mn[i] = {w, y};
				}
				if(x < n) {
					int y = t2.query(1, 1, n, x + 1, n);
					ll w = t2.a[y] + b[x];
					if(mn[i].fir > w) mn[i] = {w, y};
				}
			}
			for(auto x : v[i]) t1.update(1, 1, n, x, b[x]), t2.update(1, 1, n, x, c[x]);
		}

		rep(i, 1, n) if(i == find(i) && find(i) != find(mn[i].sec)) merge(i, mn[i].sec), res += mn[i].fir, --s;
	}
	
	cout << res << '\n';
	
    return 0;
}
```


---

## 作者：do_it_tomorrow (赞：2)

Boruvka 大法好！！！

注意到完全图而且边数有 $n^2$，直接考虑 Boruvka 处理这样的问题。

Boruvka 的思想比较简单，可以通过下面的步骤求解最小生成树：

1. 遍历所有的节点，对于每一个节点选择和它相连的最小的边。
2. 把选择的边两侧的点合并到一起，继续操作 $1$ 直到只有一个点。

最后选择的边形成的生成树就是 MST，因为每一次进行操作 $1$ 都会让连通块的数量除以 $2$，所以合并的次数是 $O(\log n)$ 的。

回到这个题目，容易发现绝对值找最小值非常难处理，考虑将其展开得到：

$$w(i,j)=\left\{\begin{matrix}
(Di+A_i)+(-Dj+A_j)  & i\ge j \\
(-Di+A_i)+(Dj+A_j)  & \text{Otherwise.}
\end{matrix}\right.$$

考虑开 $2$ 棵线段树分别维护 $Di+A_i$ 和 $-D_i+A_i$，分别叫它们 $t1$ 和 $t2$。

考虑节点 $i$，把 $i$ 这个连通块中所有的点在 $t1$ 和 $t2$ 上都改成 $+\infty$，接着对于小于 $i$ 的在 $t1$ 上查询其他的在 $t2$ 上查询。

以连通块为单位进行查找，整个连通块都跑完了之后再改回来，时间复杂度为 $O(n\log ^2 n)$。

[Submission #61342119 - KEYENCE Programming Contest 2019](https://atcoder.jp/contests/keyence2019/submissions/61342119)

---

## 作者：冷却心 (赞：0)

大家好，我写线段树套 Brovuka 被卡常，所以有了这一发单 $\log$ Brovuka 题解。

写 Brovuka 的 sol 的几乎都套了数据结构，这么没树脂。

先把朴素的线段树做法讲了。

首先 Brovuka 算法的过程就是每轮对每个连通块找一条向外的最短边连上去，这是最优的，会发现这个每一轮连通块个数至少减半，所以只有 $O(\log n)$ 轮，再乘上一个找最短边的复杂度就做完了。

这个边权 $w_{ij}=D|i-j|+A_i+A_j$ 带了绝对值感觉很难受，先拆了：

$$w_{ij}=\left\{\begin{aligned}Di+A_i-Dj+A_j,\quad &i>j,\\ -Di+A_i+Dj+A_j,\quad &i<j.\end{aligned}\right.$$

然后我们每一轮对每个结点找一个最短的且终点不和他在同一个连通块的边即可。这个可以用线段树维护 $j\in[1,i-1]$ 这个区间的 $(-D_j+A_j)_{\min}$ 以及 $j\in[i+1,n]$ 这个区间的 $(D_j+A_j)_{\min}$，但是我们要求 $j$ 和 $i$ 不在同一个连通块，于是我们维护一个最小值，以及和最小值不在同一个连通块的最小值，然后根据情况选择前者还是后者即可。最后对每个连通块中的点连出去的边选择一条最小的连接，然后就做完了。时间复杂度 $O(n\log^2n)$，因为套了一只线段树，这里不计并查集的复杂度。

然后我就被卡常了。人傻常熟大。

我们发现我们维护的东西是一个前后缀，于是 $O(n)$ 正反各扫一遍就做完了。时间复杂度 $O(n\log n)$，同样不计并查集复杂度。

[https://atcoder.jp/contests/keyence2019/submissions/62981126](https://atcoder.jp/contests/keyence2019/submissions/62981126)。

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_keyence2019_e)

# 前置知识

[Boruvka 算法](https://oi-wiki.org/graph/mst/#boruvka-%E7%AE%97%E6%B3%95)

# 解法

考虑 Boruvka 算法。

拆掉绝对值后得到 $a_{i}+id,a_{i}-id,a_{j}+id,a_{j}-id$ 四个式子。

``vector`` 启发式合并辅助线段树查询的常数过大，无法通过。上述做法的常数在于一条边会被计算两次，考虑优化。

不妨直接钦定向前连、向后连的贡献，顺次扫的过程中是容易维护的。做法正确性由最优解一定包含与其中可以保证。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll a[200010],b[200010],c[200010],f[200010];
pair<ll,ll>g[200010];
multiset<pair<ll,ll> >s;
struct DSU
{
	ll fa[200010];
	void init(ll n)
	{
		for(ll i=1;i<=n;i++)
		{
			fa[i]=i;
		}
	}
	ll find(ll x)
	{
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
	void merge(ll x,ll y)
	{
		x=find(x);
		y=find(y);
		if(x!=y)
		{
			fa[x]=y;
		}
	}
}D;
ll boruvka(ll n)
{
	D.init(n);
	ll ans=0,flag=1,x;
	while(flag==1)
	{
		flag=0;
		fill(g+1,g+1+n,make_pair(0,0x3f3f3f3f3f3f3f3f));
		s.clear();
		for(ll i=1;i<=n;i++)
		{
			f[i]=0x3f3f3f3f3f3f3f3f;
			s.insert(make_pair(f[i],i));
		}
		for(ll i=1;i<=n;i++)
		{
			x=D.find(i);
			s.erase(make_pair(f[x],x));
			if(s.empty()==0&&s.begin()->first+c[i]<g[x].second)
			{
				g[x].first=s.begin()->second;
				g[x].second=s.begin()->first+c[i];
			}
			f[x]=min(f[x],b[i]);
			s.insert(make_pair(f[x],x));
		}
		s.clear();
		for(ll i=1;i<=n;i++)
		{
			f[i]=0x3f3f3f3f3f3f3f3f;
			s.insert(make_pair(f[i],i));
		}
		for(ll i=n;i>=1;i--)
		{
			x=D.find(i);
			s.erase(make_pair(f[x],x));
			if(s.empty()==0&&s.begin()->first+b[i]<g[x].second)
			{
				g[x].first=s.begin()->second;
				g[x].second=s.begin()->first+b[i];
			}
			f[x]=min(f[x],c[i]);
			s.insert(make_pair(f[x],x));
		}
		for(ll i=1;i<=n;i++)
		{
			x=D.find(i);
			if(g[x].first!=0&&D.find(x)!=D.find(g[x].first))
			{
				D.merge(x,g[x].first);
				ans+=g[x].second;
				flag=1;
			}
		}
	}
	return ans;
}
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	ll n,d,i;
	cin>>n>>d;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=a[i]-i*d;
		c[i]=a[i]+i*d;
	}
	cout<<boruvka(n)<<endl;
	return 0;
}
```

---

## 作者：__vector__ (赞：0)

似乎没有题解提到枚举二进制位这个 trick，就发一篇题解。  

由于边的信息可以通过点的信息表示出来，并且边很多，无法直接存储，考虑使用 Boruvka 算法。 

考虑每一轮加边该如何处理。  

考虑将加边前的图中每个节点所在的连通块编号视为这个点的**类别**。  

考虑正常算法流程，对于每个连通块，都需要找到其他连通块中最优的点，使得本连通块与之建的边权是最小的。

显然，本轮需要加入的边所连接的两个点的类别肯定是不同的。  

考虑朴素做法，正着扫一遍再反着扫一遍，扫描的过程中必然需要记录每个类别的最优点是哪个。    

这样的话，有 $O(\log V)$ 级别的加边轮数，每次扫描复杂度 $O(n^2)$，炸了。  

考虑简化上述过程。上述过程的本质在于任意两个不同类别的点都需要 chk 一次。  

考虑这样一个 trick：枚举每个二进制位，仅对类别编号在这一位不同的点对进行处理。  

这样的话，每次处理过程只需要 $O(n)$ 扫一遍（不是  $O(n^2)$ 是因为这里从 $n$ 种类别变成了两种类别，即这一位是 $0$ 还是 $1$）。  

复杂度变为 $O(n \log n \log V )$  。  

```cpp 
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define REP(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mkpr make_pair
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
template <class T>
void ckmx(T &a, T b) { a = max(a, b); }
template <class T>
void ckmn(T &a, T b) { a = min(a, b); }
template <class T>
T gcd(T a, T b) { return !b ? a : gcd(b, a % b); }
template <class T>
T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define gc getchar()
#define eb emplace_back
#define pc putchar
#define ep empty()
#define fi first
#define se second
#define pln pc('\n');
template <class T>
void wrint(T x)
{
    if (x < 0)
    {
        x = -x;
        pc('-');
    }
    if (x >= 10)
    {
        wrint(x / 10);
    }
    pc(x % 10 ^ 48);
}
template <class T>
void wrintln(T x)
{
    wrint(x);
    pln
}
template <class T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char ch = gc;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc;
    }
    while (isdigit(ch))
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = gc;
    }
    x *= f;
}
const int maxn = 2e5 + 5;
int n;
ll d, a[maxn];
struct MS
{
    int fa[maxn];
    int get(int x) { return (fa[x] == x ? x : fa[x] = get(fa[x])); }
    void ms(int a, int b)
    {
        if (get(a) != get(b))
        {
            fa[get(a)] = get(b);
        }
    }
    void init() { FOR(i, 1, n)
                  fa[i] = i; }
} ms;
ll mn[maxn];
int mnid[maxn];
bool at(int s, int i) { return (s & (1 << i)); }
void solve(int id_of_test)
{
    read(n);
    read(d);
    FOR(i, 1, n) { read(a[i]); }
    ms.init();
    ll ans = 0;
    while (1)
    {
        memset(mn, 0x7f, sizeof mn);
        memset(mnid, 0, sizeof mnid);
        bool flg = 0;
        FOR(bit, 0, 17)
        {
            {
                ll _mn = mn[0];
                int _mnid = 0;
                FOR(i, 1, n)
                {
                    _mn += d;
                    if (at(ms.get(i), bit))
                    {
                        if (_mn + a[i] < mn[ms.get(i)])
                        {
                            mnid[ms.get(i)] = _mnid;
                            mn[ms.get(i)] = _mn + a[i];
                        }
                    }
                    if (!at(ms.get(i), bit))
                    {
                        if (_mn > a[i])
                        {
                            _mn = a[i];
                            _mnid = i;
                        }
                    }
                }
                _mn = mn[0];
                _mnid = 0;
                REP(i, n, 1)
                {
                    _mn += d;
                    if (at(ms.get(i), bit))
                    {
                        if (_mn + a[i] < mn[ms.get(i)])
                        {
                            mn[ms.get(i)] = _mn + a[i];
                            mnid[ms.get(i)] = _mnid;
                        }
                    }
                    if (!at(ms.get(i), bit))
                    {
                        if (_mn > a[i])
                        {
                            _mn = a[i];
                            _mnid = i;
                        }
                    }
                }
            }
            {
                ll _mn = mn[0];
                int _mnid = 0;
                FOR(i, 1, n)
                {
                    _mn += d;
                    if (!at(ms.get(i), bit))
                    {
                        if (_mn + a[i] < mn[ms.get(i)])
                        {
                            mnid[ms.get(i)] = _mnid;
                            mn[ms.get(i)] = _mn + a[i];
                        }
                    }
                    if (at(ms.get(i), bit))
                    {
                        if (_mn > a[i])
                        {
                            _mn = a[i];
                            _mnid = i;
                        }
                    }
                }
                _mn = mn[0];
                _mnid = 0;
                REP(i, n, 1)
                {
                    _mn += d;
                    if (!at(ms.get(i), bit))
                    {
                        if (_mn + a[i] < mn[ms.get(i)])
                        {
                            mn[ms.get(i)] = _mn + a[i];
                            mnid[ms.get(i)] = _mnid;
                        }
                    }
                    if (at(ms.get(i), bit))
                    {
                        if (_mn > a[i])
                        {
                            _mn = a[i];
                            _mnid = i;
                        }
                    }
                }
            }
        }
        FOR(i, 1, n)
        {
            if (mnid[i])
            {
                if (ms.get(i) == ms.get(mnid[i]))
                    continue;
                ms.ms(i, mnid[i]);
                flg = 1;
                ans += mn[i];
            }
        }
        if (!flg)
        {
            break;
        }
    }
    printf("%lld\n", ans);
}
int main()
{
    int T;
    T = 1;
    FOR(_, 1, T) { solve(_); }
    return 0;
}
```

---

## 作者：win114514 (赞：0)

B 算法萌萌题。

### 题解

看到完全图求最小生成树，必然是要考虑一下 B 算法能不能做的。

发现这个题的联通块最小值是可以维护的。

我们发现。

假如我们钦定 $i$ 往前面连。

那么前面的最小权值必然是一个固定的值。

我们一定会连到 $\min (a_j-j\times D)$ 上。

由于不能连到自己在的联通块上。

所以我们可以维护每一个联通块的最小值。

只需要从前往后扫一遍，用 set 维护即可。

往后面连是同理的。

使用并查集维护联通性即可。

时间复杂度：$O(n\log^2 n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, D, ans;
int a[200010], f[200010];
int v[200010], s[200010];
int fa[200010];

inline int gf(int x) {
  return (fa[x] == x ? x : fa[x] = gf(fa[x]));
}
inline bool chk() {
  for (int i = 1; i <= n; i++) {
    if (gf(i) != gf(1)) return 1;
  }
  return 0;
}

signed main() {
  cin >> n >> D;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], fa[i] = i;
  }
  while (chk()) {
    multiset<pair<int, int>> q;
    for (int i = 1; i <= n; i++) s[i] = 0, v[i] = 1e18;
    for (int i = 1; i <= n; i++) f[i] = 1e18;
    q.clear();
    for (int i = 1; i <= n; i++) {
      int x = gf(i);
      if (f[x] < 1e18) q.erase(q.find({f[x], x}));
      if (q.empty() == 0) {
        if (v[x] > q.begin()->first + a[i] + i * D) {
          v[x] = q.begin()->first + a[i] + i * D;
          s[x] = q.begin()->second;
        }
      }
      if (f[x] > a[i] - i * D) {
        f[x] = a[i] - i * D;
      }
      q.insert({f[x], x});
    }
    for (int i = 1; i <= n; i++) f[i] = 1e18;
    q.clear();
    for (int i = n; i >= 1; i--) {
      int x = gf(i);
      if (f[x] < 1e18) q.erase(q.find({f[x], x}));
      if (q.empty() == 0) {
        if (v[x] > q.begin()->first + a[i] - i * D) {
          v[x] = q.begin()->first + a[i] - i * D;
          s[x] = q.begin()->second;
        }
      }
      if (f[x] > a[i] + i * D) {
        f[x] = a[i] + i * D;
      }
      q.insert({f[x], x});
    }
    vector<int> r;
    for (int i = 1; i <= n; i++)
      if (s[i]) {
        int x = gf(i), y = gf(s[i]);
        if (x != y) fa[x] = y, ans += v[i];
      }
  }
  cout << ans << "\n";
}
```

---

## 作者：六楼溜刘 (赞：0)

## 题意

- 给你一张 $n$ 个点的完全图，其中边 $(u,v)$ 的边权是 $A_u+A_v+|u-v|\cdot D$。
- 求这张图的最小生成树。

## 题解

这道题现有的题解讲的做法不是删一些边用 Kruskal 求最小生成树就是直接用 Boruvka 在原来的完全图上求最小生成树，但这道题其实还有 Prim 的做法，我觉得这个做法非常自然，而且我在完全没卡常的情况下跑到了洛谷最优解第三位。

设已经连好的点的集合为 $S$，其余的为 $T$。那么只要能快速从从 $S$ 和 $T$ 里面分别找出两个点 $u,v$ 使得它们间边权最小就能做 Prim。

由于有绝对值，考虑拆绝对值，那么分两种情况讨论：

$$
\begin{cases}
(A_u-uD)+(A_v+vD)   &u<v\\
(A_u+uD)+(A_v-vD)  &u \ge v
\end{cases}
$$

那么可以直接用线段树维护，合并的时候分 $u$ 左 $v$ 右，$v$ 左 $u$ 右，两个都在左边和两个都在右边四种情况考虑。那么我们对于每个点维护 **上面式子中四个括号分别的最小值和答案** 五个值即可解决问题，但是由于我们要维护加入集合 $S$ 的操作，所以还要维护答案具体是由哪个 $v$ 得到的，因此我们还要额外维护**两个和 $v$ 有关的括号具体是由哪个 $v$ 得到的，答案是由哪个 $v$ 得到的**。

由于是单调修改整体查询，使用 zkw 线段树十分好写。

初始化线段树 $O(n\log n)$，每次修改是 $O(\log n)$ 的，故总复杂度为 $O(n \log n)$。

### code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(i64 i=(s);i<=(e);i++)
#define fordown(i,s,e) for(i64 i=(s);i>=(e);i--)
using namespace std;
using i64=long long;
#define gc getchar()
inline i64 read(){
    i64 x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const i64 N=1<<18,inf=1e18;//注意这道题 N 的范围是 2e5
i64 n,a[N],d;
struct SegmentTree{
	struct Node{
		i64 uadd,usub,vadd,va,vsub,vs,ans,vans;
//ans 就是答案，va,vs,vans 是三个需要维护的 v，剩下的是那四个式子的值。
//add 是加，sub 是减（subtract）
		Node(i64 _uadd=inf,i64 _usub=inf,i64 _vadd=inf,i64 _va=0,i64 _vsub=inf,i64 _vs=0,i64 _ans=inf,i64 _vans=0){
			uadd=_uadd;usub=_usub;vadd=_vadd;va=_va;vsub=_vsub;vs=_vs;ans=_ans;vans=_vans;
//注意初值设为多少
		}
	}tree[(N<<1)+10];
	void PushUp(i64 id){//合并（有亿点复杂）
		tree[id].uadd=min(tree[id<<1].uadd,tree[id<<1|1].uadd);
		tree[id].usub=min(tree[id<<1].usub,tree[id<<1|1].usub);
		tree[id].vadd=min(tree[id<<1].vadd,tree[id<<1|1].vadd);
		tree[id].vsub=min(tree[id<<1].vsub,tree[id<<1|1].vsub);
		tree[id].va=tree[id<<1].vadd<tree[id<<1|1].vadd?tree[id<<1].va:tree[id<<1|1].va;
		tree[id].vs=tree[id<<1].vsub<tree[id<<1|1].vsub?tree[id<<1].vs:tree[id<<1|1].vs;
		tree[id].ans=min(tree[id<<1].ans,tree[id<<1|1].ans);
		if(tree[id<<1].usub!=inf&&tree[id<<1|1].vadd!=inf){
			tree[id].ans=min(tree[id].ans,tree[id<<1].usub+tree[id<<1|1].vadd);
		}
		if(tree[id<<1].vsub!=inf&&tree[id<<1|1].uadd!=inf){
			tree[id].ans=min(tree[id].ans,tree[id<<1].vsub+tree[id<<1|1].uadd);
		}
		if(tree[id].ans==tree[id<<1].ans){
			tree[id].vans=tree[id<<1].vans;
		}else if(tree[id].ans==tree[id<<1|1].ans){
			tree[id].vans=tree[id<<1|1].vans;
		}else if(tree[id].ans==tree[id<<1].usub+tree[id<<1|1].vadd){
			tree[id].vans=tree[id<<1|1].va;
		}else{
			tree[id].vans=tree[id<<1].vs;
		}
	}
	void Build(){//这就是 zkw 线段树带给我的自信
		tree[N+1]=Node(a[1]+d,a[1]-d,inf,0,inf,0,inf,0);
		forup(i,2,n){tree[N+i]=Node(inf,inf,a[i]+d*i,i,a[i]-d*i,i,inf,0);}
		fordown(i,N,1){PushUp(i);}
	}
	void Update(i64 L){//把 L 加入集合 S
		tree[N+L]=Node(a[L]+d*L,a[L]-d*L,inf,0,inf,0,inf,0);
		for(int i=(L+N)>>1;i;i>>=1){PushUp(i);}
	}
}mt;
signed main(){
	n=read();d=read();
	forup(i,1,n){
		a[i]=read();
	}
	mt.Build();
	i64 res=0;
	forup(i,1,n-1){
		res+=mt.tree[1].ans;
		mt.Update(mt.tree[1].vans);//每次查询后把 v 加入 S 集合
	}
	printf("%lld",res);
}
```

---

## 作者：daitouzero (赞：0)

## 题意

给定一张 $n$ 个点的完全图，$(i,j)$ 间点的边权是 $|i-j|\times D+a_{i}+a_{j}$。

求这个图的最小生成树。

## Solve

对于这种在边数爆炸的图上让你求最小生成树的题，很冷门的 Boruvka 算法可以发挥其神奇的作用。

Boruvka 算法考虑维护当前的连通块（刚开始时每个点都是一个连通块），然后对于每一个连通块，求其连到其他连通块的最小边。

然后向最小生成树中加入这些找到的边，重复两个操作直到整出生成树为止。

虽然每次找边的复杂度是 $O(m)$ 的，但是很容易发现连通块的数量每次合并完都会少一半，所以一共只会合并 $O(\log n)$ 次。

总复杂度的就是 $O(n\log n)$ 的。

这个算法的优势就在于它只需要 $\log$ 次合并，而且此算法可把问题转化为找连通块最小出边。

知道了这个算法后，本题基本就可以当个板子题做。

因为边权的式子比较坑，带了个绝对值，所以不妨开两发线段树，一发存 $A_{i}-i$，一发存 $A_{i}+i$。

这样每轮找边就是 $n\log n$ 的，故总复杂度为 $O(n\log^2n)$，只要常数不是特别巨大即可通过。

>注意：给一个连通块找出边的时候记得把这个连通块内的点在线段树上改成极大值！（找完后还得改回来！）

## Code

~~不仅粪得不行还拥有巨大常数的屑代码~~

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<string>
#include<algorithm>
#include<bitset>
#include<map>
#include<set>
#include<functional>
#include<queue>
typedef long long ll;
typedef unsigned long long ull;
const int N=2e5+5;
const ll inf=1e16;
template<typename T>
inline void scan(T& x)
{
	x=0;
	T dp=0;
	char type=getchar();
	while(type<'0') dp|=(type=='-'),type=getchar();
	while(type>='0') 
	{
		x=(x<<1)+(x<<3)+(type&15);
		type=getchar();
	}
	x=dp?-x:x;
}
template<typename T,typename ... args>
inline void scan(T& x, args& ... tmp)
{
	scan(x);
	scan(tmp...);
	return ;
}
template<typename T>
inline void print(T x)
{
	if (x<0) putchar('-'),x=-x;
	if (!x) return ;
	print(x/10);
	putchar(x%10+'0');
}
int n;
struct SegmentTree
{
	struct Node
	{
		ll MMn;
        int Mp;
	}tree[N<<2];
	inline void pushup(int k)
	{
		if (tree[k<<1].MMn<tree[k<<1|1].MMn)
		{
			tree[k].MMn=tree[k<<1].MMn;
			tree[k].Mp=tree[k<<1].Mp;
		}
		else 
		{
			tree[k].MMn=tree[k<<1|1].MMn;
			tree[k].Mp=tree[k<<1|1].Mp;
		}
	}
	void build(std::function<ll(int)>f,int k=1,int l=1,int r=n)
	{
		if (l==r)
		{
			tree[k].MMn=f(l);
			tree[k].Mp=l;
			return ;
		}
		int mid=(l+r)/2;
		build(f,k<<1,l,mid);
		build(f,k<<1|1,mid+1,r);
		pushup(k);
	}
	void change(int pos,ll cag,int k=1,int l=1,int r=n)
	{
		if (l==r)
		{
			tree[k].MMn=cag;
			return ;
		}
		int mid=(l+r)/2;
		if (pos<=mid) change(pos,cag,k<<1,l,mid);
		else change(pos,cag,k<<1|1,mid+1,r);
		pushup(k);
	}
	std::pair<ll,int >query(int L,int R,int k=1,int l=1,int r=n)
	{
		if (L<=l&&r<=R) return std::pair<ll ,int >(tree[k].MMn,tree[k].Mp);
		int mid=(l+r)/2;
		std::pair<ll ,int >res(inf,-1);
		if (L<=mid) res=std::min(res,query(L,R,k<<1,l,mid));
		if (mid+1<=R) res=std::min(res,query(L,R,k<<1|1,mid+1,r));
		return res;
	}
}pre,suf;

int D,val[N];
inline ll F(int x)
{
	return (ll)-x*D+val[x];
}
inline ll G(int x)
{
	return (ll)x*D+val[x];
}
int tree[N],Size[N],last[N],Next[N];

/*DSU*/
inline int Find(int x)
{
	while (x!=tree[x])
		x=tree[x]=tree[tree[x]];
    return x;
}
inline bool Merge(int x,int y)
{
	x=Find(x),y=Find(y);
	if (x==y) return false;
	if (Size[x]>Size[y]) std::swap(x,y);
	Size[y]+=Size[y];
	tree[x]=y;
	return true;
}
int main()
{
	scan(n,D);
	for (int i=1;i<=n;i++)
		scan(val[i]);
	
	pre.build(F),suf.build(G);
	for (int i=1;i<=n;i++)
		tree[i]=i,Size[i]=1;
	
	ll ans=0;
	int tot=0;
	while (1)
	{
        if (tot==n-1) break;
		for (int i=1;i<=n;i++) last[i]=Next[i]=0;

		/*扣连通块*/
		for (int i=1;i<=n;i++)
		{
			Next[i]=last[Find(i)];
			last[Find(i)]=i;
		}

		std::vector<std::pair<int ,int > >edge;
		for (int i=1;i<=n;i++)
		{
			if (i!=Find(i)) continue;
			for (int pos=last[i];pos;pos=Next[pos])
				pre.change(pos,inf),suf.change(pos,inf);
			
			ll MMn=inf,sum;
			int x,y;
			for (int pos=last[i];pos;pos=Next[pos])
			{
				if (pos!=n)
				{
					std::pair<ll ,int >R=suf.query(pos+1,n);
					sum=R.first+F(pos);
					if (R.second!=-1&&sum<MMn)
					{
						MMn=sum;
						x=pos;
						y=R.second;
					}
				}
				if (pos!=1)
				{
					std::pair<ll ,int >L=pre.query(1,pos-1);
					sum=L.first+G(pos);
					if (L.second!=-1&&sum<MMn)
					{
						MMn=sum;
						x=pos;
						y=L.second;
					}
				}
			}
			if (MMn!=inf) edge.push_back(std::pair<int ,int >(x,y));

			for (int pos=last[i];pos;pos=Next[pos])
				pre.change(pos,F(pos)),suf.change(pos,G(pos));
		}
		
		for (auto [x,y]:edge)
		{
			int fx=Find(x),fy=Find(y);
			if (fx==fy) continue;
			/*启发式合并*/
			if (Size[fx]>Size[fy]) std::swap(fx,fy);
			ans+=(ll)D*std::abs(x-y)+val[x]+val[y];
			Size[fy]+=Size[fy];
			tree[fx]=fy;
			tot++;
		}
	}
	print(ans);
	return 0;
}
```

---

## 作者：ademik (赞：0)

#### 分析 ：

首先有一个不得不做的转化，将 $|i - j| \times D + a_i + a_j$ 看成 $\min((a_i + i \times D) + (a_j - j \times D) , (a_i - i \times D) + (a_j + j \times D))$。

这样的话我们可以通过维护 $a_i + i \times D$ 和 $a_i - i \times D$ 来得到我们要求的式子的结果，反正比 带个绝对值的式子好维护。

然后由于我们实际上要求一棵最小生成树，那么可以从 kruskal 和 Prim 两种常见的最小生成树算法考虑。

对于 kruskal 而言，如果直接暴力建图的话会有 $n ^ 2$ 条边。考虑到有一些边是一定不会被 kruskal 算法选择的，那么可以考虑优化建图。这里我的建图方式来自于 [lemondinosaur](https://www.luogu.com.cn/blog/sugar-free-mint/solution-at4569)。

我们可以考虑分治，由于我们每次将序列分成两块，两块间有明显的左右关系，我们令 左块中元素的编号为 $i$，右块中元素的编号为 $j$，那么 两者间边的权值为 $a_i - i \times D + a_j + j \times D$。
我们可以在 左块中 找到 最小 的 $a_i - i \times D$，将该点与 右块中的所有的点连边。在 右块中 找到 最小 的 $a_i + i \times D$，将该点与左块中 的所有点连边，相当于在两个块中找到最优点来 代替 两个块所有元素互相连边。

由于我们要找的是最小的 边 使得两个块联通，所以这种方式一定能将 kruskal 所需的最小边加入原图中，即可以保证答案的正确性。最后跑一边 kruskal 即可。总建边数为 $n \times \log n$，总时间复杂度为 $O(n \log^2n)$。

#### Code (kruskal):

```cpp
using namespace std;
typedef long long i64;
const int N = 2 * 1e5 + 50;
int n, fa[N], edge_sum;
int _find(int x) {return fa[x] == x ? x : fa[x] = _find(fa[x]);}
i64 a[N], b[N], ans, D;
struct edge {
    i64 u, v, w;
    bool operator <(const edge &tmp) const {
        return w < tmp.w;
    }
} e[N << 5];
void dfs(int x, int y)
{
    if(x == y) return;
    int mid = (x + y) >> 1;
    int ll = x, rr = y;
// 找到左块中 a_i - i * D 的最小值， 右块中 a_i + i * D 的最小值。
    for(int i = x; i <= mid; i ++) {
        if(a[ll] > a[i]) ll = i;
    }
    for(int i = mid + 1; i <= y; i ++) {
        if(b[rr] > b[i]) rr = i;
    }
// 连边， 保证一定将两块间的最小边包含在内
    for(int i = x; i <= mid; i ++) {
        e[++ edge_sum] = (edge){i, rr, a[i] + b[rr]};
    }
    for(int i = mid + 1; i <= y; i ++) {
        e[++ edge_sum] = (edge){ll, i, a[ll] + b[i]};
    }
    dfs(x, mid); dfs(mid + 1, y); return;
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >>n >>D;
    for(int i = 1, x; i <= n; i ++) {
        cin >>x; fa[i] = i;
        a[i] = x - i * D; 
        b[i] = x + i * D;
    }
    dfs(1, n); sort(e + 1, e + 1 + edge_sum);
    for(int i = 1; i <= edge_sum; i ++) {
        int u = _find(e[i].u), v = _find(e[i].v);
        if(u != v) {
            fa[v] = u; ans += e[i].w;
        }
    }
    cout <<ans <<endl;
    return 0;
} 
```


对于 Prim 而言，我们考虑它的暴力流程，发现实际上我们需要维护的是**最小的边权** 和 最小边权是由 **哪个 未被连接的点** 和 已连接的点组成的。

线段树维护的思路来自于 [200815147](https://blog.csdn.net/baidu_36797646/article/details/86482424?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522159833064319195264512590%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=159833064319195264512590&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v3~pc_rank_v2-2-86482424.first_rank_ecpm_v3_pc_rank_v2&utm_term=Connecting%20Cities&spm=1018.2118.3001.4187)
。 我们还是将所求式子的绝对值拆开，通过线段树来维护边权的最小值，再记录一个标记，表示组成最小边的 点的标号。那么现在的问题是 Prim 要求
我们选择的两个点，一个位于 已经被选择的点集中，另一个位于 还没有被选择的点集中。 

我们考虑利用两类数组来区分 这两种点，当一个点被选中时，将其对应的一类数组清空，另一类数组赋值。每次计算两个点间的距离时，只用这两种数组交错而形成的边，这样线段树维护的边权始终是 未被选择的点 和 已被选择的点间的距离。总时间复杂度为 $O(n \log n)$。

#### Code(Prim) :
 
```cpp
# define mid ((l + r) >> 1)
# define lson (rt << 1)
# define rson (rt << 1 | 1)
using namespace std;
typedef long long i64;
const int N = 2 * 1e5 + 50;
const i64 Inf = 0x3f3f3f3f3f3f3f3f;
i64 n, D, a[N];
struct node {
    i64 val, id;
    node() {}
    node(i64 val, i64 id) : val(val), id(id) {}
    bool operator <(const node &tmp) const {
        return val < tmp.val;
    }
} ;
struct SEG {
    int pos;
    node p[5];
} tr[N << 2];

// p[0] 表示 未被选择的点的 a_i - i * D 的最小值;
// p[1] 表示 未被选择的点的 a_i + i * D 的最小值；
// p[2] 表示 已被选择的点的 a_i - i * D 的最小值;
// p[3] 表示 已被选择的点的 a_i + i * D 的最小值；
// p[4] 表示 未被选择的点集 和 已被选择的点集 间边权的最大值；
// pos 表示 当 p[4] 最小时， 我们选择的 未被选择的点。
void push_up(int rt)
{
    for(int i = 0; i <= 4; i ++) {
        if(tr[lson].p[i] < tr[rson].p[i]) {
            tr[rt].p[i] = tr[lson].p[i];
            if(i == 4) tr[rt].pos = tr[lson].pos;
        }
        else {
            tr[rt].p[i] = tr[rson].p[i];
            if(i == 4) tr[rt].pos = tr[rson].pos;
        }
    }

    if(tr[lson].p[2].val != Inf && tr[rson].p[1].val != Inf) {
        i64 now = tr[lson].p[2].val + tr[rson].p[1].val;
        if(now < tr[rt].p[4].val) {
            tr[rt].p[4] = node(now, tr[lson].p[2].id);
            tr[rt].pos = tr[rson].p[1].id;
        }
    }
    if(tr[lson].p[0].val != Inf && tr[rson].p[3].val != Inf) {
        i64 now = tr[lson].p[0].val + tr[rson].p[3].val;
        if(now < tr[rt].p[4].val) {
            tr[rt].p[4] = node(now, tr[rson].p[3].id);
            tr[rt].pos = tr[lson].p[0].id;
        }
    }
}
void Build(int l, int r, int rt)
{
    for(int i = 0; i <= 4; i ++) tr[rt].p[i] = node(Inf, 0);
    if(l == r) {
        if(l != 1) { // 将 1 作为第一个已被选择的点
            tr[rt].p[2] = tr[rt].p[3] = tr[rt].p[4] = node(Inf, 0);
            tr[rt].p[0] = node(a[l] - 1ll * l * D, l);
            tr[rt].p[1] = node(a[l] + 1ll * l * D, l);
        }
        else {
            tr[rt].p[0] = tr[rt].p[1] = tr[rt].p[4] = node(Inf, 0);
            tr[rt].p[2] = node(a[l] - 1ll * l * D, l);
            tr[rt].p[3] = node(a[l] + 1ll * l * D, l);
        }
        return;
    }
    Build(l, mid, lson); Build(mid + 1, r, rson);
    push_up(rt); return;
}
void change(int pos, int l, int r, int rt) // 将一个点 由未被选择的点转化为 已被选择的点。
{
    for(int i = 0; i <= 4; i ++) tr[rt].p[i] = node(Inf, 0);
    if(l == r) {
        tr[rt].p[0] = tr[rt].p[1] = tr[rt].p[4] = node(Inf, 0);
        tr[rt].p[2] = node(a[l] - 1ll * l * D, l);
        tr[rt].p[3] = node(a[l] + 1ll * l * D, l);
        return;
    } 
    if(pos <= mid) change(pos, l, mid, lson);
    else change(pos, mid + 1, r, rson);
    push_up(rt); return;
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >>n >>D;
    for(int i = 1; i <= n; i ++) cin >>a[i];
    Build(1, n, 1);
    int m = n - 1; i64 ans = 0;
    while(m --) {
        ans += tr[1].p[4].val;
        change(tr[1].pos, 1, n, 1);
    }
    cout <<ans <<endl;
    return 0;
}
```

似乎这道题还有 模拟 Boruvka 算法的，[这里](https://www.cnblogs.com/cnyzz/p/16144616.html)，用 树状数组解题。

总的来说，这道题还是比较好的，每一种 最小生成树 的算法都可以解题，而每种解题方式都 有共同点，也有各自的特色。





---

