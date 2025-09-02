# On Changing Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is a vertex number $ 1 $ .

Initially all vertices contain number $ 0 $ . Then come $ q $ queries, each query has one of the two types:

- The format of the query: $ 1 $ $ v $ $ x $ $ k $ . In response to the query, you need to add to the number at vertex $ v $ number $ x $ ; to the numbers at the descendants of vertex $ v $ at distance $ 1 $ , add $ x-k $ ; and so on, to the numbers written in the descendants of vertex $ v $ at distance $ i $ , you need to add $ x-(i·k) $ . The distance between two vertices is the number of edges in the shortest path between these vertices.
- The format of the query: $ 2 $ $ v $ . In reply to the query you should print the number written in vertex $ v $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

Process the queries given in the input.

## 说明/提示

You can read about a rooted tree here: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 样例 #1

### 输入

```
3
1 1
3
1 1 2 1
2 1
2 2
```

### 输出

```
2
1
```

# 题解

## 作者：nekko (赞：8)

~~这不是套路题么……为什么是紫牌啊……~~

设$dep_u$表示$u$的深度

如果对于$u$为根的子树执行操作$2$，既对于每一个子树中的节点$v$，那么新增加的值为

$$x-dis_{u,v}k=x-(dep_v-dep_u)k=(-dep_vk)+(x-dep_uk)$$

对于后边的那一项相当于一个子树整体加一个常数，树状数组维护一下就行了

对于前面那项，发现$dep_v$是关于$v$的固有属性，换句话说，$\sum -dep_vk_i=-dep_v\sum k_i$，也就是说直接维护子树的$k$之和就行了

于是写俩树状数组就可以做了

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10, mod = 1e9 + 7;

int n, l[N], r[N];
vector<int> g[N];

struct BIT {
	ll sum[N];
	void addsig(int x, ll y) {
		for( ; x <= n ; x += x & -x)
			(sum[x] += y) %= mod;
	}
	void add(int l, int r, ll s) {
		addsig(l, s), addsig(r + 1, -s);
	}
	ll ask(int x) {
		ll r = 0;
		for( ; x ; x -= x & -x)
			(r += sum[x]) %= mod;
		return r;
	}
} a, b;

int dep[N];
void dfs(int u) {
	static int tot = 0;
	l[u] = ++ tot;
	for(int v: g[u])
		dep[v] = dep[u] + 1, dfs(v);
	r[u] = tot;
}

int main() {
	scanf("%d", &n);
	for(int i = 2, fa ; i <= n ; ++ i)
		scanf("%d", &fa), g[fa].push_back(i);
	dfs(1);
	int q; scanf("%d", &q);
	for(int i = 1, op, v, x, k ; i <= q ; ++ i) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d%d%d", &v, &x, &k);
			a.add(l[v], r[v], k % mod);
			b.add(l[v], r[v], (x + 1ll * dep[v] * k % mod) % mod);
		} else {
			scanf("%d", &v);
			ll qa = a.ask(l[v]);
			ll qb = b.ask(l[v]);
			ll ans = (1ll * -dep[v] * qa % mod + qb) % mod;
			ans = (ans % mod + mod) % mod;
			printf("%lld\n", ans);
		}
	}
}
```

---

## 作者：N2MENT (赞：5)

#### CF396C题解

[原题链接](https://www.luogu.com.cn/problem/CF396C)


#### 思路：

由于子树里不同深度的节点权值不同，所以用线段树直接维护的难度比较高。但容易注意到：进行加操作时，相邻深度之间增加权值的差是 **一样** 的，而且询问操作居然 **只有单点查询** ，非常容易想到一个常用的技巧： **差分** 。

------------


定义 $f(x)$ 为 $x$ 和 $root$ 路径上的所有节点的权值和，$v$ 为树中的节点，$u$ 为 $v$ 子树中的节点（$u$ 与 $v$ 不同）。


#### 修改操作：


我们令每个节点记录它与它父亲的差，$v$ 原本的值等于 $f(v)$。进行修改操作时，给 $v$ 的权值加 $x$，此时 $f(v)$ 增加了 $x$，同时 $f(u)$ 也增加了 $x$。再让所有的 $u$ 减去 $k$，$f(u)$ 的值全部都减去 $dis(u,v)\cdot k$，这样所有的值都按照题意进行了改变。我们使用线段树维护信息，一次单点修改 $v$ 加 $x$，一次区间修改 $u$ 减 $k$，复杂度为 $O(\log_2n)$
 
```cpp
void Update(ll v, ll x, ll k) {
    sgt.Update(1, 1, n, id[v], id[v] + siz[v] - 1, -k);//给整个子树-k
    sgt.Update(1, 1, n, id[v], id[v], k + x);//加回v原有的k同时加上x
    return;
}
```


#### 查询操作：

这是最容易的部分，只需要求 $f(v)$ 即可。直接向上暴力跳，均摊的复杂度似乎还可以接受，但假如毒瘤出题人让树变成一根链，复杂度便会退化到 $O(n\log_2n)$。改用树链剖分维护，复杂度 $O(\log_2^2n)$。

```cpp
ll Query(ll x) {
    ll res = 0;
    while (top[x] != 1) {
        res = (res + sgt.Query(1, 1, n, id[top[x]], id[x]) + mod) % mod;
        x = fa[top[x]];
    }
    res = (res + sgt.Query(1, 1, n, 1, id[x]) + mod) % mod;
    return res;
}
```



------------

以下是 AC 代码，复杂度介于 $O(q\log_2n)$ 到 $O(q\log_2^2n)$ 之间。测试点最长用了 $1.6s$（为什么常数这么大），但是还是可以 AC。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lc (k << 1)
#define rc (k << 1 | 1)
const ll mod = 1000000007;
const ll maxn = 3e5 + 10;
//建线段树维护差分的和
class SegTree {
public:
    ll tr[maxn << 2];
    ll lazy[maxn << 2];
    SegTree() {
        memset(tr, 0, sizeof(tr));
        memset(lazy, 0, sizeof(lazy));
    }
    void TagUpdate(ll k, ll l, ll r) {
        ll mid = (l + r) >> 1;
        tr[lc] = (tr[lc] + lazy[k] * ((mid - l + 1 + mod) % mod) + mod) % mod;
        tr[rc] = (tr[rc] + lazy[k] * ((r - mid + mod) % mod) + mod) % mod;
        lazy[lc] += lazy[k];
        lazy[rc] += lazy[k];
        lazy[k] = 0;
        return;
    }
    void FatherUpdate(ll k) {
        tr[k] = tr[lc] + tr[rc];
        return;
    }
    void Update(ll k, ll l, ll r, ll L, ll R, ll val) {
        if (L <= l && r <= R) {
            tr[k] = (tr[k] + (r - l + 1) * val + mod) % mod;
            lazy[k] = (lazy[k] + val + mod) % mod;
            return;
        }
        TagUpdate(k, l, r);
        ll mid = (l + r) >> 1;
        if (L <= mid)
            Update(lc, l, mid, L, R, val);
        if (R > mid)
            Update(rc, mid + 1, r, L, R, val);
        FatherUpdate(k);
        return;
    }
    ll Query(ll k, ll l, ll r, ll L, ll R) {
        if (L <= l && r <= R) {
            return tr[k];
        }
        TagUpdate(k, l, r);
        ll mid = (l + r) >> 1, res = 0;
        if (L <= mid)
            res = (res + Query(lc, l, mid, L, R) + mod) % mod;
        if (R > mid)
            res = (res + Query(rc, mid + 1, r, L, R) + mod) % mod;
        return res;
    }
} sgt;
vector<ll> G[maxn];
ll n, q;
ll top[maxn], dep[maxn], siz[maxn], son[maxn], fa[maxn], id[maxn], re[maxn], cnt;
//树剖
void Dfs1(ll u, ll f) {
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    fa[u] = f;
    for (auto v : G[u]) {
        if (v == f)
            continue;
        Dfs1(v, u);
        siz[u] += siz[v];
        if (!son[u] || siz[v] > siz[son[u]])
            son[u] = v;
    }
    return;
}
void Dfs2(ll u, ll tp) {
    top[u] = tp;
    id[u] = ++cnt;
    re[cnt] = u;
    if (son[u])
        Dfs2(son[u], tp);
    for (auto v : G[u]) {
        if (v == fa[u] || v == son[u])
            continue;
        Dfs2(v, v);
    }
    return;
}
void Update(ll v, ll x, ll k) {
    sgt.Update(1, 1, n, id[v], id[v] + siz[v] - 1, -k);
    sgt.Update(1, 1, n, id[v], id[v], k + x);
    return;
}
ll Query(ll x) {
    ll res = 0;
    while (top[x] != 1) {
        res = (res + sgt.Query(1, 1, n, id[top[x]], id[x]) + mod) % mod;
        x = fa[top[x]];
    }
    res = (res + sgt.Query(1, 1, n, 1, id[x]) + mod) % mod;
    return res;
}
void Init() {
    scanf("%lld", &n);
    for (ll i = 2; i <= n; i++) {
        ll f;
        scanf("%lld", &f);
        G[i].push_back(f);
        G[f].push_back(i);
    }
    Dfs1(1, 1);
    Dfs2(1, 1);
    scanf("%lld", &q);
    return;
}
void Solve() {
    for (ll i = 1; i <= q; i++) {
        ll v, x, k, opt;
        scanf("%lld", &opt);
        if (opt == 1) {
            scanf("%lld%lld%lld", &v, &x, &k);
            Update(v, x, k);
        } else {
            scanf("%lld", &v);
            ll ans = Query(v);
            while (ans < 0) ans += mod;
            printf("%lld\n", ans);
        }
    }
    return;
}
int main() {
    // freopen("data.in", "r", stdin);
    // freopen("ans.out", "w", stdout);
    Init();
    Solve();
    return 0;
}
```

附赠造数据机一个

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 10
#define Q 100
int main() {
    freopen("data.in", "w", stdout);
    srand(time(NULL));
    int n = N, q = Q;
    printf("%d\n", n);
    for (int i = 2; i <= n; i++) {
        int f = rand() % (i - 1) + 1;
        printf("%d ", f);
    }
    printf("\n%d\n", q);
    for (int i = 1; i <= q; i++) {
        int opt = rand() % 2 + 1;
        printf("%d ", opt);
        if (opt == 1) {
            printf("%d %d %d\n", rand() % n + 1, rand() % 100, rand() % 100);
        } else {
            printf("%d\n", rand() % n + 1);
        }
    }
}
```

---

## 作者：pzc2004 (赞：5)

[题目传送门](https://www.luogu.org/problem/CF396C)

~~没有树链剖分的题解？那我写一个~~

大致思路：把每次的修改分为两部分，一部分是给v节点和它的子树上的所有节点加上一个x，另一部分是给v节点和它的所有子树上的节点减去一个$k*(dep_u-dep_v)$（u表示当前节点，dep表示深度），然后我们发现可以开两颗线段树，每次操作就将第二颗线段树上的v节点和它的所有子树上的节点都加上一个$x+k*dep_v$，再将第一颗线段树上的v节点和它的所有子树上的节点都加上一个k，最后查询时就输出该节点的第二颗线段树上的节点的值减去第一颗线段树上的节点的值乘上该节点的深度即可，具体实现看代码，~~然而直到最后我才发现其实不需要写树链剖分。~~

代码（~~也就144行~~）：
```
#include<bits/stdc++.h>
using namespace std;
const long long P=1000000007; 
const long long N=300001;
long long n,m,head[N],dep[N],fa[N],top[N],son[N],size[N],id[N],cnt1,cnt2,a1,a2,a3;
struct sb1
{
	long long a,b;
}e[N<<1];
struct sb2
{
	long long s,la;
}tre[N<<2],tre2[N<<2];//tre同题目描述中的第一棵线段树，tre2同描述中的第二棵线段树
void add(long long a,long long b)//链式前向星存边
{
	e[++cnt1]=sb1{head[a],b};
	head[a]=cnt1;
}
void dfs1(long long x,long long y)//树链剖分模板
{
	dep[x]=dep[y]+1;
	fa[x]=y;
	size[x]=1;
	long long k=-1;
	for(long long i=head[x];i;i=e[i].a)
	{
		if(e[i].b!=y)
		{
			dfs1(e[i].b,x);
			size[x]+=size[e[i].b];
			if(size[e[i].b]>k)
			{
				k=size[e[i].b];
				son[x]=e[i].b;
			}
		}
	}
}
void dfs2(long long x,long long y)
{
	id[x]=++cnt2;
	top[x]=y;
	if(!son[x])return;
	dfs2(son[x],y);
	for(long long i=head[x];i;i=e[i].a)
	{
		if(e[i].b!=fa[x] && e[i].b!=son[x])dfs2(e[i].b,e[i].b);
	}
}
void pushdown(long long p,long long l,long long r)//线段树模板
{
	if(tre[p].la==0)return;
	long long mid=(l+r)>>1;
	tre[p<<1].s=(tre[p<<1].s+tre[p].la*(mid-l+1))%P;
	tre[p<<1|1].s=(tre[p<<1|1].s+tre[p].la*(r-mid))%P;
	tre[p<<1].la=(tre[p<<1].la+tre[p].la)%P;
	tre[p<<1|1].la=(tre[p<<1|1].la+tre[p].la)%P;
	tre[p].la=0;
}
void add(long long p,long long l,long long r)
{
	if(l>=a1 && r<=a2){tre[p].s=(tre[p].s+(r-l+1)*a3%P)%P;tre[p].la+=a3;return;}
	pushdown(p,l,r);
	long long mid=(l+r)>>1;
	if(mid>=a1)add(p<<1,l,mid); 
	if(mid<a2)add(p<<1|1,mid+1,r);
	tre[p].s=(tre[p<<1].s+tre[p<<1|1].s)%P;
}
long long query(long long p,long long l,long long r)
{
	if(l>=a1 && r<=a2)return tre[p].s;
	pushdown(p,l,r);
	long long mid=(l+r)>>1,ans=0;
	if(mid>=a1)ans=(ans+query(p<<1,l,mid))%P; 
	if(mid<a2)ans=(ans+query(p<<1|1,mid+1,r))%P;
	return ans; 
}
void pushdown2(long long p,long long l,long long r)
{
	if(tre2[p].la==0)return;
	long long mid=(l+r)>>1;
	tre2[p<<1].s=(tre2[p<<1].s+tre2[p].la*(mid-l+1))%P;
	tre2[p<<1|1].s=(tre2[p<<1|1].s+tre2[p].la*(r-mid))%P;
	tre2[p<<1].la=(tre2[p<<1].la+tre2[p].la)%P;
	tre2[p<<1|1].la=(tre2[p<<1|1].la+tre2[p].la)%P;
	tre2[p].la=0;
}
void add2(long long p,long long l,long long r)
{
	if(l>=a1 && r<=a2){tre2[p].s=(tre2[p].s+(r-l+1)*a3%P)%P;tre2[p].la+=a3;return;}
	pushdown2(p,l,r);
	long long mid=(l+r)>>1;
	if(mid>=a1)add2(p<<1,l,mid); 
	if(mid<a2)add2(p<<1|1,mid+1,r);
	tre2[p].s=(tre2[p<<1].s+tre2[p<<1|1].s)%P;
}
long long query2(long long p,long long l,long long r)
{
	if(l>=a1 && r<=a2)return tre2[p].s;
	pushdown2(p,l,r);
	long long mid=(l+r)>>1,ans=0;
	if(mid>=a1)ans=(ans+query2(p<<1,l,mid))%P; 
	if(mid<a2)ans=(ans+query2(p<<1|1,mid+1,r))%P;
	return ans; 
}
signed main()
{
	scanf("%lld",&n);
	for(long long i=2;i<=n;i++)
	{
		long long b;
		scanf("%lld",&b);
		add(i,b);
		add(b,i);
	}
	dfs1(1,0);
	dfs2(1,1);
	scanf("%lld",&m);
	while(m--)
	{
		long long k;
		scanf("%lld",&k);
		if(k==1)
		{
			long long a,b,c;
			scanf("%lld%lld%lld",&a,&b,&c);
			a1=id[a],a2=id[a]+size[a]-1,a3=b+c*dep[a];//操作
			add2(1,1,n+1);
			a1=id[a],a2=id[a]+size[a]-1,a3=-c;//操作
			add(1,1,n+1);
		}
		else
		{
			long long a,ans=0;
			scanf("%lld",&a);
			a1=id[a],a2=id[a];//计算答案
			ans+=query2(1,1,n+1);
			a1=id[a],a2=id[a];
			ans+=query(1,1,n+1)*dep[a];
			ans%=P;
			printf("%lld\n",(ans+P)%P);//防止出现负数
		}
	}
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：Pengzt (赞：3)

[cnblogs](https://www.cnblogs.com/Pengzt/p/17931672.html)

[CF396C](https://www.luogu.com.cn/problem/CF396C)

考虑将贡献表示出来：$\forall v\in \text{subtree}_u$，$v$ 会加上 $x - (dep_v - dep_u)k$，然后发现这个东西可以维护整棵子树，即把 $x,dep_u\times k$ 和 $dep_v\times k$ 分开计算，然后 $dep_v$ 可以最后再管，就变为子树加，单点和了。用树状数组维护 dfs 序即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
#define L(i, j, k) for(int i = (j); i <= (k); ++i)
#define R(i, j, k) for(int i = (j); i >= (k); --i)
#define ll long long
#define eb emplace_back
const int mod = 1e9 + 7;
int n, m;
int dn, dfn[300010], sz[300010], dep[300010];
vector<int> e[300010];
struct BIT {
	int v[300010];
	void add(int x, int y) {
		for(; x <= n; x += x & -x) v[x] = (v[x] + y) % mod;
	}
	int ask(int x) {
		int res = 0;
		for(; x; x -= x & -x) res = (res + v[x]) % mod;
		return res;
	}
	void upd(int l, int r, int v) { add(l, v), add(r + 1, -v); };
} t1, t2;
void dfs(int x) {
	dfn[x] = ++dn, sz[x] = 1;
	for(int y : e[x]) dep[y] = dep[x] + 1, dfs(y), sz[x] += sz[y];
}
int main(){
	ios :: sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	L(i, 2, n) {
		int x; cin >> x;
		e[x].eb(i);
	}
	dfs(1);
	cin >> m;
	L(_, 1, m) {
		int opt, v; cin >> opt >> v;
		if(opt == 1) {
			int x, k; cin >> x >> k;
			int l = dfn[v], r = dfn[v] + sz[v] - 1;
			t1.upd(l, r, k), t2.upd(l, r, (dep[v] * 1ll * k + x) % mod);
		} else {
			cout << (t2.ask(dfn[v]) - t1.ask(dfn[v]) * 1ll * dep[v] % mod + 2 * mod) % mod << "\n";
		}
	}
	cerr << TIME << "ms\n";
	return 0;
}
```

接下来的部分没有代码。

这个方法可以扩展到全局操作。

对深度操作在根的时候是很方便的，考虑转化到根，这里可以采用对边赋值然后求树上前缀和的方法，但这里不需要对其兄弟产生贡献，所以没有必要转换到根。

具体地，令 $u$ 为当前节点，给 $u$ 子树内的边都减去 $k$，然后给 $(u,fa_u)$ 这条边的权值加上 $x$ 即可。所以这里需要树链剖分，且需支持区间加，区间和。

---

## 作者：xuzz (赞：3)

树上问题一般用**树链剖分**,但是这题不涉及链上操作，所以只需要```dfs序```。设子树根节点为 $u$，节点个数为 $size_u$， $u$ 的dfs序为 $dfn_u$,改变子树只需改变 $(dfn_u,dfn_u+size_u-1)$ 的节点，区间修改单点查询可以用线段树或树状数组，~~奈何本人太菜，不会树状数组~~下面来介绍线段树的做法。

题目的修改操作难以用单一懒标记维护，且无法合并，所以可以将操作拆分成加上 $x+deep_u \times k$ 和减 $deep_v \times k$，标记 $x+deep_u \times k$ 和 $k$，查询时将前一个标记减去后一个标记乘 $deep_v$，这样就可以合并标记，用线段树维护。

最后附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define N 300010
using namespace std;
void read(int &o) {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	o=x*f;
	return;
}
int n,id[N],m,size[N],deep[N],fa[N];
vector<int> a[N];
struct obj {
	int l,r,lan1,lan2;
} tree[N<<4];
int cnt=0;
void dfs(int x) {
	id[x]=++cnt;
	deep[cnt]=deep[id[fa[x]]]+1;
	size[x]=1;
	for(int i=0; i<a[x].size(); i++) {
		dfs(a[x][i]);
		size[x]+=size[a[x][i]];
	}
	return;
}
void build(int u,int l,int r) {
	tree[u].l=l,tree[u].r=r;
	if(l>=r) return;
	int mid=(l+r)>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
}
void pushdown(int u) {
	tree[u<<1].lan1=(tree[u<<1].lan1+tree[u].lan1)%mod;
	tree[u<<1].lan2=(tree[u<<1].lan2+tree[u].lan2)%mod;
	tree[u<<1|1].lan1=(tree[u<<1|1].lan1+tree[u].lan1)%mod;
	tree[u<<1|1].lan2=(tree[u<<1|1].lan2+tree[u].lan2)%mod;
	tree[u].lan1=0;
	tree[u].lan2=0;
	return;
}
void update(int u,int l,int r,int x,int k) {
	if(tree[u].l>=l&&r>=tree[u].r) {
		tree[u].lan1+=x;
		tree[u].lan1%=mod;
		tree[u].lan2+=k;
		tree[u].lan2%=mod;
		return;
	}
	int mid=(tree[u].l+tree[u].r)>>1;
	if(l<=mid) update(u<<1,l,r,x,k);
	if(r>mid) update(u<<1|1,l,r,x,k);
	return;
}
int querry(int u,int x) {
	if(tree[u].l>=tree[u].r) {
		return (tree[u].lan1-tree[u].lan2*deep[tree[u].l]+mod)%mod;
	}
	pushdown(u);
	int mid=(tree[u].l+tree[u].r)>>1;
	if(x<=mid) return querry(u<<1,x);
	else return querry(u<<1|1,x);
}
signed main() {
	read(n);
	for(int i=2; i<=n; i++) {
		int x;
		read(x);
		fa[i]=x;
		a[x].push_back(i);
	}
	dfs(1);
	build(1,1,n);
	read(m);
	while(m--) {
		int opt;
		read(opt);
		if(opt==1) {
			int x,v,k;
			read(v),read(x),read(k);
			x=(x+deep[id[v]]*k)%mod;
			update(1,id[v],id[v]+size[v]-1,x,k);
		} else {
			int x;
			read(x);
			printf("%lld\n",(querry(1,id[x])%mod+mod)%mod); 
		}
	}
	return 0;
}
```


---

## 作者：shadowice1984 (赞：2)

~~普通树据结构题，树状数组随便搞搞就行了~~

_____________________

一句话题意：给定一棵以1为根的树,初始时每个点的点权全部是0,支持两种操作

操作1，给节点$u$加上$x$,对于$u$子树中所有节点，如果它和$u$的距离为$i$那么这个点被加上$x-ik$,$x$和$k$均为输入的参数

操作2:询问节点u的点权

_______________________

## 本题题解

发现询问异常的简单，所以我们考虑贡献

考虑在一个时刻t，我们询问了节点$v$的点权

那么什么样的修改会对这个询问产生贡献呢？

第一这个修改发生的时刻$t'$必须小于$t$

第二就是这个修改的$u$必须在这个点到1的路径上，否则显然影响不到这个点

那么此时v的点权又是多少呢?

应该是

$$\sum_{i}x_{i}-dis(u_{i},v)k_{i}$$

简单的把dis拆一下

$$\sum_{i}x_{i}-(dep_{v}-dep_{u_{i}})k_{i}$$

然后简单的拆一下Σ

$$(\sum_{i}x_{i}+dep_{u_{i}}k_{i})-(dep_{v}\sum_{i}k_{i})$$

换句话说要我们查询的东西是所有满足以下条件修改的$x+dep_{u}k$的和以及$k$的和

1.这个修改的$t$小于我们询问的$t$

2.这个修改的点$u$在$1-v$的路径上


那么第二个条件相当的好解决，我们在树上dfs,将u压栈的时候就将和u有关的修改都插入某数据结构里，将u弹栈的时候就将和u有关的修改全部从数据结构中删除，这样的话当我们dfs到v的时候数据结构中留下的修改就全部在1~v的路径上了

还剩下第一个限制条件，发现只是一个修改的t小于询问t的关系，这个东西就相当的好解决了,我们将询问离线用一个树状数组维护一下，到时候查两发前缀和就行了

具体点来讲就是开两个树状数组，当我们插入一个询问的时候·在这个询问的$t$的位置单点加上$x+dep_{u}k$，在另一个树状数组上单点加$k$,删除的时候就换成减法就可以了

回答一个询问的时候在树状数组上查两发前缀和然后套个式子减一下就可以了~

上代码~

```C
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;const int N=3*1e5+10;typedef long long ll;const ll mod=1e9+7;
int n;int m;
struct data{ll x;ll k;int t;};vector <data> ve[N];vector <int> qr[N];
struct treearray//树状数组 
{
    ll ta[N];
    inline void c(int x,ll t){for(;x<=m;x+=x&(-x))(ta[x]+=t)%=mod;}
    inline ll q(int x){ll r=0;for(;x;x-=x&(-x))(r+=ta[x])%=mod;return r;}
}ta1,ta2;int v[N];int x[N];int ct;int al[N];ll ans[N];
inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
inline void dfs(int u,int dep)//dfs 
{
    for(vector <data>::iterator it=ve[u].begin();it!=ve[u].end();++it)//插入 
        ta1.c(it->t,(it->x+dep*it->k)%mod),ta2.c(it->t,it->k);
    for(vector <int>::iterator it=qr[u].begin();it!=qr[u].end();++it)//回答 
        ans[*it]=(ta1.q(*it)+mod-ta2.q(*it)*dep%mod)%mod;
    for(int i=al[u];i;i=x[i])dfs(v[i],dep+1);//dfs 
    for(vector <data>::iterator it=ve[u].begin();it!=ve[u].end();++it)//删除 
        ta1.c(it->t,mod-(it->x+dep*it->k)%mod),ta2.c(it->t,mod-it->k);
}
int main()
{
    scanf("%d",&n);for(int i=2,f;i<=n;i++)scanf("%d",&f),add(f,i);scanf("%d",&m);
    for(int i=1;i<=m;i++)ans[i]=-1;
    for(int i=1,t,u,x,k;i<=m;i++)//离线 
    {
        scanf("%d%d",&t,&u);
        if(t==1)scanf("%d%d",&x,&k),ve[u].push_back((data){x,k,i});
        else qr[u].push_back(i);
    }dfs(1,0);//输出答案 
    for(int i=1;i<=m;i++)if(ans[i]!=-1)printf("%I64d\n",ans[i]);return 0;//拜拜程序~ 
}


```





---

## 作者：Milthm (赞：1)

这个操作它每次给 $u$ 的子树中的节点 $v$ 增加 $x-dis_{u,v}k$（其中 $dis_{u,v}$ 表示 $u$ 到 $v$ 的距离）。设 $dep_u$ 表示 $u$ 的深度，我们可以推一下式子：

$x-dis_{u,v}k=x-k(dep_v-dep_u)=x-dep_vk+dep_uk=(x+dep_uk)-dep_vk$。

你会发现前面这个 $x+dep_uk$ 和 $v$ 一点关系也没有，于是我们就想到可以分两个部分维护。

前面这个 $x+dep_uk$ 很好维护，每次直接给子树加上这个值就可以了。

后面这个 $-dep_vk$ 也很好维护，$dep_v$ 是固定的，你只需要维护 $k$ 之和，到时候乘上 $-dep_v$ 就行。

然后观察你需要做的操作，子树加，单点查。又因为子树加可以通过 dfs 序转化为区间加，所以这就是一个差分加树状数组的板子，因为你维护了两个部分，所以要两个树状数组。

时间复杂度 $O(q \log n)$。

### AC code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 300005 
const int mod=1e9+7;
using namespace std;
int n,m,cnt,L[N],R[N],dep[N];
vector<int>e[N];
int read(){
	char c=getchar();int ans=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))ans=ans*10+c-'0',c=getchar();
	return ans;
} 
void dfs(int u,int fa){
	L[u]=++cnt;dep[u]=dep[fa]+1;
	for(int i=0;i<e[u].size();++i){
		int v=e[u][i];dfs(v,u);
	}
	R[u]=cnt;
}
struct BIT{
	int c[N]; 
	void add(int x,int k){
		while(x<=n){
			c[x]=(c[x]+k)%mod;x+=x&-x;
		}
	}
	void upd(int l,int r,int k){
		add(l,k);add(r+1,-k);
	}
	int ask(int x){
		int ans=0;
		while(x){
			ans=(ans+c[x])%mod;x-=x&-x;
		}
		return ans;
	}
}a,b;
signed main(){
	n=read();
	for(int i=2;i<=n;++i){
		int u=read();e[u].push_back(i);
	}
	dfs(1,0);
	m=read();
	while(m--){
		int op,v,x,k;
		op=read();v=read();
		if(op==1){
			x=read();k=read();
			a.upd(L[v],R[v],(x+dep[v]*k)%mod);
			b.upd(L[v],R[v],k%mod);
		}
		else printf("%lld\n",((a.ask(L[v])-b.ask(L[v])*dep[v]%mod)%mod+mod)%mod);
	}
	return 0;
}

```


---

## 作者：Double_Light (赞：1)

### CF396C On Changing Tree 题解

考虑使用树状数组来维护。

先用链式前向星来建图（或 `vector`），然后将这棵树转化为可以用树状数组维护的数列。显然对于每一个修改操作，都会修改以当前节点为根的子树。如果让这一棵子树所有节点在数列中的下标连续，那么很容易用差分转化为单点修改。

一颗树的每棵子树转化为一段连续区间。显然可以用 `dfs` 序来遍历。同时可以求出以 $x$ 号节点为根的子树映射到数列中区间左右端点的下标。

随后考虑使用两个树状数组，一个维护层数乘上 $k$ 然后加 $x$，即子树对应区间的区间修改。但是由于维护层数乘 $k$ 则多加上了所以是多加上了 $v$ 节点的深度与 $k$ 的积这么多（因为 $v$ 号节点本应该不乘上 $k$，而在第一个树状数组中，乘上了 $dep_v$ 个 $k$），于是第二个树状数组在对应区域加上 $k$，查询时乘上 $v$ 节点的深度就是第一个树状数组多加的部分，减掉即可。

代码：

```cpp
#include<iostream>
#include<map>
#include<cmath>
#define int long long
using namespace std;
int n,m,a[300005],d[300005],cnt;
int num,head[300005];
int opt,p,q,u,v,s;
int l[300005],r[300005];
const int mod=1e9+7;
map<int,int>ma,ma2;
struct edge{
	int u,v,nxt;
}e[600005];
void add(int u,int v){//链式前向星建图
	e[++num]={u,v,head[u]};
	head[u]=num;
}
int read(){//加快读，否则常数大可能就会 TLE
	char c=getchar();int ans=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))ans=ans*10+c-'0',c=getchar();
	return ans;
} 
struct tree{
	int c[300005];
	int lowbit(int x){
		return x&-x;
	}
	void update(int x,int v){//单点修改
		while(x<=n){
			c[x]+=v;
			c[x]%=mod;
			x+=lowbit(x);
		}
	}
	int query(int x){//单点查询
		int now=x,ans=0;
		while(now){
			ans+=c[now]%mod;
			ans%=mod;
			now-=lowbit(now);
		}
		return ans;
	}
}tr1,tr2; //上文提到的两个树状数组

void dfs(int x,int deep,int fa){
	d[x]=deep;
	ma[x]=++cnt;ma2[cnt]=x;
	l[x]=cnt;//l[x]表示以x号节点为根的子树映射到数列中区间左端点的下标
	for(int i=head[x];i;i=e[i].nxt){
		if(e[i].v==fa)continue;
		dfs(e[i].v,deep+1,x);
	}
	r[x]=cnt;//r[x]就是右端点的下标
}
signed main(){
	n=read();
	for(int i=2;i<=n;i++){
		u=read();
		add(i,u);add(u,i);
	}
	m=read();
	dfs(1,1,0);
	while(m--){
		opt=read();
		if(opt==1){
			p=read();q=read();s=read();
			tr1.update(l[p],(q+d[p]*s)%mod);//差分
			tr1.update(r[p]+1,-(q+d[p]*s)%mod);
			tr2.update(l[p],s%mod);
			tr2.update(r[p]+1,-s%mod);
		}
		if(opt==2){
			p=read();
			printf("%lld\n",((tr1.query(l[p])-tr2.query(l[p])*d[p]%mod)%mod+mod)%mod);//少取模会爆long long
		}
	}
	return 0;
}
```


---

## 作者：decoqwq (赞：1)

树剖题8.jpg(反正一眼是这个思路

考虑修改操作，深度越大要增加的值越少，每增加1深度增加的值减少 $k$ ，考虑差分，在修改的点 $v$ 处加上值 $x$，之后在它的子树中所有除了它的点全部加上 $-k$，查询的时候因为要满足“增加1深度就减少 $k$”这个条件，那么显然就是查询 $1-x$ 的链上的数字和，所以树链剖分维护子树加链查询即可

时间复杂度 $\Theta(q\log ^2n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
vector<int> vc[300010];
int fa[300010],in[300010],out[300010],siz[300010];
int top[300010],son[300010],dep[300010];
int sum[1200010],addv[1200010],n,q,cnt;
void dfs1(int u)
{
	siz[u]=1;
	for(auto v:vc[u])
	{
		dep[v]=dep[u]+1;
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
		{
			son[u]=v;
		}
	}
}
void dfs2(int u,int tp)
{
	top[u]=tp;
	in[u]=++cnt;
	if(son[u])
	{
		dfs2(son[u],tp);
	}
	for(auto v:vc[u])
	{
		if(v==son[u])
		{
			continue;
		}
		dfs2(v,v);
	}
	out[u]=cnt;
}
void pushdown(int o,int lf,int rg)
{
	if(addv[o])
	{
		addv[o<<1]+=addv[o];
		addv[o<<1]%=mod;
		addv[o<<1|1]+=addv[o];
		addv[o<<1|1]%=mod;
		int mid=(lf+rg)>>1;
		sum[o<<1]=(sum[o<<1]+addv[o]*(mid-lf+1)%mod)%mod;
		sum[o<<1|1]=(sum[o<<1|1]+addv[o]*(rg-mid)%mod)%mod;
		addv[o]=0;
	}
}
void modify(int o,int lf,int rg,int l,int r,int x)
{
	if(l<=lf&&rg<=r)
	{
		sum[o]+=(rg-lf+1)*x;
		addv[o]+=x;
		return ;
	}
	int mid=(lf+rg)>>1;
	pushdown(o,lf,rg);
	if(l<=mid)
	{
		modify(o<<1,lf,mid,l,r,x);
	}
	if(mid<r)
	{
		modify(o<<1|1,mid+1,rg,l,r,x);
	}
	sum[o]=sum[o<<1]+sum[o<<1|1];
}
int query(int o,int lf,int rg,int l,int r)
{
	if(l<=lf&&rg<=r)
	{
		return sum[o];
	}
	pushdown(o,lf,rg);
	int ans=0,mid=(lf+rg)>>1;
	if(l<=mid)
	{
		ans=(ans+query(o<<1,lf,mid,l,r))%mod;
	}
	if(mid<r)
	{
		ans=(ans+query(o<<1|1,mid+1,rg,l,r))%mod;
	}
	return ans;
}
int qpath(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
		{
			swap(x,y);
		}
		ans=(ans+query(1,1,n,in[top[x]],in[x])+mod)%mod;
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])
	{
		swap(x,y);
	}
	ans=(ans%mod+query(1,1,n,in[y],in[x])%mod+mod)%mod;
	return (ans+mod)%mod;
}
signed main()
{
	cin>>n;
	for(int i=2;i<=n;i++)
	{
		scanf("%lld",&fa[i]);
		vc[fa[i]].push_back(i);
	}
	dfs1(1);
	dfs2(1,1); 
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int opt,x,y,z;
		scanf("%lld%lld",&opt,&x);
		if(opt==1)
		{
			scanf("%lld%lld",&y,&z);
			modify(1,1,n,in[x],in[x],y);
			modify(1,1,n,in[x]+1,out[x],-z);
		}
		else
		{
			cout<<qpath(1,x)<<"\n";
		}
	}
}
```

---

## 作者：Rorschachindark (赞：1)

# On Changing Tree
[题目传送门](https://www.luogu.com.cn/problem/CF396C)
## 思路1:树状数组
我们考虑对于点$v$算出它的值那么就是:

$$\sum_{t=1}^{i-1} (x_t-dis[u_t,v]\times k_t)$$

$$=\sum_{t=1}^{i-1} (x_t-(deep[v]-deep[u_t])\times k_t)$$

$$=\sum_{t=1}^{i-1} (x_t+deep[u_t]\times k_t)-deep[v]\times \sum_{t=1}^{i-1} k_t$$

但是我们发现这个东西需要满足$u_t$在$1\to v$的路径上，怎么办呢？很简单，我们可以利用$dfs$的特性解决即可，然后这个东西直接用两个树状数组维护即可。

因为一个操作会加入删除各一次，所以总时间复杂度为$\Theta(m\log m+n)$。
## $\text {Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define mod 1000000007
#define int long long
#define MAXN 300005

int n,m;

struct edge
{
	int v,nxt;
}e[MAXN];

int top = 1;
int head[MAXN];

void Add_Edge (int u,int v)
{
	e[++ top] = edge {v,head[u]};
	head[u] = top; 
}

class Bit_tree
{
	private:
		int bit[MAXN];
		int lowbit (int x){return x & (-x);}
	public:
		void update (int pos,int x){for (Int i = pos;i <= m;i += lowbit (i)) (bit[i] += x) %= mod;}
		int query (int pos){int ans = 0;for (Int i = pos;i;i -= lowbit (i)) (ans += bit[i]) %= mod;return ans;}
}Tree1,Tree2;

struct Node
{
	int x,k,Index;//x,k,时间 
};

vector <int> Que[MAXN];
vector <Node> Ins[MAXN];

int Ans[MAXN];

void dfs (int u,int dep)
{
	for (vector <Node>::iterator it = Ins[u].begin();it != Ins[u].end();++ it)
		Tree1.update (it -> Index,(it -> x + dep * it -> k % mod) % mod),
		Tree2.update (it -> Index,it -> k % mod);
	for (vector <int>::iterator it = Que[u].begin();it != Que[u].end();++ it)
		Ans[*it] = (Tree1.query (*it) + mod - dep * Tree2.query (*it) % mod) % mod;
	for (Int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].v;
		dfs (v,dep + 1);
	}
	for (vector <Node>::iterator it = Ins[u].begin();it != Ins[u].end();++ it)
		Tree1.update (it -> Index,mod - (it -> x + dep * it -> k % mod) % mod),
		Tree2.update (it -> Index,mod - it -> k % mod);
}

int read ()
{
	int x = 0;char c = getchar();int f = 1;
	while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}
	while (c >= '0' && c <= '9'){x = (x << 3) + (x << 1) + c - '0';c = getchar();}
	return x * f;
}

void write (int x)
{
	if (x < 0){x = -x;putchar ('-');}
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
}

signed main()
{
	n = read ();
	for (Int i = 2;i <= n;++ i)
	{
		int fa = read ();
		Add_Edge (fa,i);
	}
	m = read ();
	for (Int i = 1,x,k;i <= m;++ i)
	{
		Ans[i] = -1;
		int type = read (),u = read ();
		if (type == 1) x = read (),k = read (),Ins[u].push_back(Node {x,k,i});
		else Que[u].push_back (i);
	}
	dfs (1,1);
	for (Int i = 1;i <= m;++ i) if (Ans[i] != -1) write (Ans[i]),putchar ('\n');
	return 0;
}
```
## 思路2:线段树
其实很套路，我们发现这个东西是给子树内加上一个等差数列（不是很严谨，大家意会一下），跟[这道题](https://www.luogu.com.cn/problem/P4243)有些相似。

于是就十分套路了。我们直接用线段树维护一个差分数组，每次操作就相当于给$u$节点加上$x$,给子树内其他节点加上$-k$。

查询操作就相当于询问$1\to u$的路径和。

时间复杂度为$\Theta(m\log ^2n+n)$。
## $\text {Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define mod 1000000007
#define int long long
#define MAXN 300005

int n,m;

struct edge
{
	int v,nxt;
}e[MAXN];

int toop = 1;
int head[MAXN];

void Add_Edge (int u,int v)
{
	e[++ toop] = edge {v,head[u]};
	head[u] = toop;
}

int Index;
int par[MAXN],dep[MAXN],son[MAXN],top[MAXN],dfn[MAXN],size[MAXN];

void dfs1 (int u,int fa)
{
	par[u] = fa,size[u] = 1,dep[u] = dep[fa] + 1;
	for (Int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].v;
		dfs1 (v,u);
		size[u] += size[v];
		if (size[v] > size[son[u]]) son[u] = v;
	}
}

void dfs2 (int u,int Top)
{
	top[u] = Top;
	dfn[u] = ++ Index;
	if (son[u]) dfs2 (son[u],Top);
	for (Int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].v;
		if (v == son[u]) continue;
		dfs2 (v,v);
	}
}

struct node
{
	int l,r,sum,lazy;
}tree[MAXN << 2];

void Pushup (int i)
{
	tree[i].sum = tree[i << 1].sum + tree[i << 1 | 1].sum;
}

void Pushdown (int i)
{
	if (!tree[i].lazy) return ;
	(tree[i << 1].sum += (tree[i << 1].r - tree[i << 1].l + 1) * tree[i].lazy % mod) %= mod;
	(tree[i << 1 | 1].sum += (tree[i << 1 | 1].r - tree[i << 1 | 1].l + 1) * tree[i].lazy % mod) %= mod;
	(tree[i << 1].lazy += tree[i].lazy) %= mod,(tree[i << 1 | 1].lazy += tree[i].lazy) %= mod;
	tree[i].lazy = 0;
}

void build (int i,int l,int r)
{
	tree[i].l = l,tree[i].r = r;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	build (i << 1,l,mid);
	build (i << 1 | 1,mid + 1,r); 
}

void update (int i,int l,int r,int val)
{
	if (tree[i].l > r || l > tree[i].r) return ;
	if (tree[i].l >= l && tree[i].r <= r) return (tree[i].sum += val * (tree[i].r - tree[i].l + 1)) %= mod,(tree[i].lazy += val) %= mod,void ();
	Pushdown (i);
	update (i << 1,l,r,val);
	update (i << 1 | 1,l,r,val);
	Pushup (i);
}

int query (int i,int l,int r)
{
	if (tree[i].l > r || l > tree[i].r) return 0;
	if (tree[i].l >= l && tree[i].r <= r) return tree[i].sum;
	Pushdown (i);
	return (query (i << 1,l,r) + query (i << 1 | 1,l,r)) % mod;
}

int Tree_query (int u,int v)
{
	int Ans = 0;
	while (top[u] ^ top[v])
	{
		if (dep[top[u]] < dep[top[v]]) swap (u,v);
		Ans = (Ans + query (1,dfn[top[u]],dfn[u]));
		u = par[top[u]];
	}
	if (dep[u] > dep[v]) swap (u,v);
	Ans = (Ans + query (1,dfn[u],dfn[v])) % mod;
	return (Ans % mod + mod) % mod;
}

int read ()
{
	int x = 0;char c = getchar();int f = 1;
	while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}
	while (c >= '0' && c <= '9'){x = (x << 3) + (x << 1) + c - '0';c = getchar();}
	return x * f;
}

void write (int x)
{
	if (x < 0){x = -x;putchar ('-');}
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
}

signed main()
{
	n = read ();
	for (Int i = 2;i <= n;++ i)
	{
		int fa = read ();
		Add_Edge (fa,i);
	}
	dfs1 (1,0);
	dfs2 (1,1);
	build (1,1,n);
	m = read ();
	for (Int i = 1;i <= m;++ i)
	{
		int type = read (),u = read (),x,k;
		if (type == 1) x = read (),k = read (),update (1,dfn[u],dfn[u],x),update (1,dfn[u] + 1,dfn[u] + size[u] - 1,mod - k);
		else write (Tree_query (1,u)),putchar ('\n'); 
	}
	return 0;
}
```
## 后记
可以来体会一下离线和在线的时间差距:

![](https://cdn.luogu.com.cn/upload/image_hosting/zkspurtm.png)

---

## 作者：lbmzxhb (赞：0)

[题目链接](/problem/CF396C)  
树剖模板，但有一点思维难度  
感觉不至于紫题，降不降无所谓~~毕竟多一道紫题有啥不好的~~

# 思路：

一眼差分。  
对于操作一，就是将点 $v$ 增加 $x$，而对其子树节点减去 $k$，  
而对于操作二，求的就是点 $v$ 到根节点所有权值的和，  
用普通树剖模板改一改就能过了。

# Code:

代码应该算较为易懂的吧（

```cpp
#include <iostream>
#define int long long
#define lx (x<<1)
#define rx (x<<1|1) 
using namespace std;
const int N(3e5 + 5), p(1e9 + 7);
int n, q, tre[N << 2], laz[N << 2];
//以下树剖模板
void pushup(int x) {tre[x] = tre[lx] + tre[rx];}
void pushdown(int x, int l, int r) {
	int mid((l + r) >> 1);
	if (laz[x]) {
		(laz[lx] += laz[x]) %= p; (laz[rx] += laz[x]) %= p;
		(tre[lx] += laz[x] * (mid - l + 1)) %= p; (tre[rx] += laz[x] * (r - mid)) %= p;
		laz[x] = 0;
	}
} 
void radd(int L, int R, int v, int x = 1, int l = 1, int r = n) {
	if (L > R) swap(L, R);//L可能比R大
	if (L <= l && r <= R) {(laz[x] += v) %= p, (tre[x] += v * (r - l + 1)) %= p; return;}
	int mid((l + r) >> 1); pushdown(x, l, r);
	if (L <= mid) radd(L, R, v, lx, l, mid);
	if (mid < R) radd(L, R, v, rx, mid + 1, r);
	pushup(x);
}
int rget(int L, int R, int x = 1, int l = 1, int r = n) {
	if (L > R) swap(L, R);//和radd()的一样特判
	if (L <= l && r <= R) return tre[x];
	int mid((l + r) >> 1), res(0); pushdown(x, l, r);
	if (L <= mid) res += rget(L, R, lx, l, mid);
	if (mid < R) res += rget(L, R, rx, mid + 1, r);
	pushup(x); return res;
}
int fa[N], son[N], dep[N], sz[N], dfn[N], top[N], tid;
int e[N << 1], ne[N << 1], to[N << 1], eid;
void add(int x, int y) {to[++eid] = y; ne[eid] = e[x]; e[x] = eid;}
void dfs1(int u, int f) {
	sz[u] = 1;
	for (int i = e[u], v = to[e[u]]; i; v = to[i = ne[i]]) if (v != f) {
		fa[v] = u; dep[v] = dep[u] + 1; dfs1(v, u); sz[u] += sz[v];
		if (sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tp) {
	top[u] = tp; dfn[u] = ++tid;
	if (!son[u]) return; dfs2(son[u], tp);
	for (int i = e[u], v = to[e[u]]; i; v = to[i = ne[i]]) if (v != fa[u] && v != son[u]) dfs2(v, v);
}
inline int upd(int x) {return (x % p + p) % p;}//能处理负数的取模
void tadd(int x, int v) {//给以x为根的所有子节点减去-v
  if (sz[x] > 1) radd(dfn[x] + 1, dfn[x] + sz[x] - 1, -v);//x大小=1时没有除x以外的子节点，要特判
}
int tget(int x, int y) {//求x--y链上的权值和
	int res(0);
	while (top[x] != top[y]) res += rget(dfn[x], dfn[top[x]]), x = fa[top[x]];
	return upd(res + rget(dfn[x], dfn[y]));
}
//以上树剖模板
signed main() {
	cin.tie(0),cout.tie(0)->sync_with_stdio(0); //不加快读过不了
	cin >> n;
	for (int i = 2, v; i <= n; i++) cin >> v, add(v, i), add(i, v);
	dfs1(1, -1); dfs2(1, 1);
	cin >> q;
	while (q--) {
		int op, v, x, k;
		cin >> op >> v; if (op == 1) cin >> x >> k;
		if (op == 1) radd(dfn[v], dfn[v], x), tadd(v, k);
		else cout << tget(v, 1) << '\n';
	}
}
```

[cf提交记录](https://codeforces.com/contest/396/submission/253143911)  
[洛谷提交记录](/record/152594552)  
~~点个赞再走罢~~

---

## 作者：gdf_yhm (赞：0)

[CF396C](https://www.luogu.com.cn/problem/CF396C)

### 思路

对于一个点维护 $b_i=a_i-a_{fa_i}$。对于操作一，等价于 $b_u$ 加 $x$，$u$ 的子树不含 $u$ 的每个点和父亲的差都减 $k$。对于操作二，等价于从根到 $u$ 路径上的 $b_x$ 的和。同 [P3178](https://www.luogu.com.cn/problem/P3178)，子树加，路径查，树剖加线段树。

### code

```cpp
int n,q;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int fa[maxn],siz[maxn],son[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1;dep[u]=dep[fa[u]]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],idx,tp[maxn];
void dfs1(int u,int lst){
	dfn[u]=++idx;tp[u]=lst;
	if(!son[u])return ;
	dfs1(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs1(v,v);
	}
}
int tree[maxn<<2],tag[maxn<<2];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
void push(int nd,int l,int r){
	if(tag[nd]){
		(tree[ls]+=1ll*(mid-l+1)*tag[nd]%mod)%=mod;(tag[ls]+=tag[nd])%=mod;
		(tree[rs]+=1ll*(r-mid)*tag[nd]%mod)%=mod;(tag[rs]+=tag[nd])%=mod;
		tag[nd]=0;
	}
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		(tree[nd]+=1ll*(r-l+1)*w%mod)%=mod;(tag[nd]+=w)%=mod;
		return ;
	}
	push(nd,l,r);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=(tree[ls]+tree[rs])%mod;
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	push(nd,l,r);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return (query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr))%mod;
}
int que(int u){
	int res=0;
	while(u){
		(res+=query(1,1,n,dfn[tp[u]],dfn[u]))%=mod;
		u=fa[tp[u]];
	}
	return res;
}
void work(){
	n=read();
	for(int i=2;i<=n;i++){int p=read();add(p,i);}
	dfs(1),dfs1(1,1); 
	q=read();
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),x=read(),k=read();
			updata(1,1,n,dfn[u]+1,dfn[u]+siz[u]-1,mod-k);
			updata(1,1,n,dfn[u],dfn[u],x);
		}
		else{
			int u=read();
			printf("%d\n",que(u));
		}
	}
}
```

---

## 作者：CRTL_xzh2009 (赞：0)

采用线段树或树状数组可解决此题。

众所周知：树的 DFS 序，会将同一子树的结点，排列在一起成为一个连续的区间。

那么 $v$ 子树上的结点增加值 $x-(d_{i}-d_{v}) \times k$，其实就是在 DFS 序上的区间修改，困难的是每个结点增加的值不一样。

考虑对 $i$ 点增加的值 $x-(d_{i}-d_{v}) \times k$ 变形为 $x+d_{v} \times k-d_{i} \times k$。减号左边 $x+d_{v} \times k$ 这一部分每个结点增加的值都是一样的；减号右边 $d_{i} \times k$，不同的结点深度不同，那我们就只累加 $k$ 就好了，由于输出时是单点查询，所有针对查询的结点在乘上 $d_{i}$ 即可。

好了，我需要两个线段树 $t_{1}$ 和 $t_{2}$，维护区间加，单点查询。

$t_{1}$ 中维护区间加 $x+d_{v} \times k$，$t_{2}$ 中维护区间加 $k$。

查询时用 $t_{1}$ 查询的结果减去 $t_{2}$ 查询的结果乘 $d_{i}$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300005
#define LL long long
#define mod 1000000007
#define LS u<<1
#define RS u<<1|1
int h[N],ecnt;
struct Edge
{
int v,p;
}e[N];
void AddEdge(int u,int v)
{
	e[++ecnt].p=h[u]; 
	h[u]=ecnt;
	e[ecnt].v=v;
}
int clk,L[N],R[N],d[N];
void DFS(int u,int dep)
{
	d[u]=dep; L[u]=++clk;
	for(int i=h[u];i;i=e[i].p)
		DFS(e[i].v,dep+1);
	R[u]=clk;
}
struct Tree
{
	int lz[N<<2];
	void PushDown(int u,int l,int r)
	{
		if(l==r || !lz[u])
		    return;
		lz[LS]=(lz[LS]+lz[u])%mod;
		lz[RS]=(lz[RS]+lz[u])%mod;
		lz[u]=0;
	}
	void UpDate(int L,int R,int x,int u,int l,int r)
	{
		if(L<=l && r<=R)
		{
			lz[u]=(lz[u]+x)%mod;
			return;
		}
		PushDown(u,l,r);
		int m=l+r>>1;
		if(L<=m)
		    UpDate(L,R,x,LS,l,m);
		if(m<R) 
		    UpDate(L,R,x,RS,m+1,r);
	}
	int Query(int L,int u,int l,int r)
	{
		if(l==r)
		    return lz[u];
		PushDown(u,l,r);
		int m=l+r>>1;
		if(L<=m)
		    return Query(L,LS,l,m);
		else 
		    return Query(L,RS,m+1,r);
	}
}t1,t2;
int n;
int main()
{
	scanf("%d",&n);
	for(int i=2,f;i<=n;++i)
	{
		scanf("%d",&f);
		AddEdge(f,i);
	}
	DFS(1,1);
	int q; 
	scanf("%d",&q);
	while(q--)
	{
		int op,v,x,k;
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d",&v,&x,&k);
			t1.UpDate(L[v],R[v],(x+1ll*d[v]*k)%mod,1,1,n);
			t2.UpDate(L[v],R[v],k,1,1,n);
		}
		else
		{
			scanf("%d",&v);
			LL ans=t1.Query(L[v],1,1,n);
			ans=(ans-1LL*d[v]*t2.Query(L[v],1,1,n));
			ans=(ans%mod+mod)%mod;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：Strelitzia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF396C)

---

没有什么思维难度的方法，一个线段树，没有树剖。

由于是对 $\mathrm{v}$ 的子树，所以深度都比 $\mathrm{v}$ 大。

维护区间深度，区间长度，啊，这的 $k$ 是线段树下标。

一个区间的修改，就是 $dep_v \times len_k \times K - sum_k \times x$。

然后三个 $\operatorname{tag}$ 维护 $k,x,dep_v\times x$ 就是了。 

```cpp
#include <map>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

char buf[1 << 23],*p1 = buf,*p2 = buf,obuf[1 << 23],*O = obuf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++)
#define putchar(x) *O ++ = x

template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
int read() {
	int x = 0, f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	return x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

template<typename T>T Abs(T x) {return x < 0 ? -x : x;}
template<typename T>T Min(T x,T y) {return x < y ? x : y;}
template<typename T>T Max(T x,T y) {return x > y ? x : y;}
template<typename T>void Swap(T &x,T &y) {T z = x;x = y;y = z;}

const int N = 3e5 + 5;
const int MOD = 1e9 + 7;

int nxt[N],ver[N],head[N],tot;
void addEdge(int u,int v) {nxt[++ tot] = head[u];ver[tot] = v;head[u] = tot;}

int n,m,tim;
int dfn[N],dep[N],sz[N],s[N];
int t[N << 2],tag[N << 2],lazy[N << 2],lazytag[N << 2],sum[N << 2],len[N << 2];

void dfs(int u,int pre) {
	sz[u] = 1;
	dfn[u] = ++ tim;
	dep[u] = dep[pre] + 1;
	s[tim] = s[tim - 1] + dep[u];
	for (int e = head[u] ; e ; e = nxt[e]) {
		int v = ver[e];
		if (v == pre) continue;
		dfs(v,u);
		sz[u] += sz[v];
	}
}

void build(int l,int r,int k) {
	sum[k] = s[r] - s[l - 1];
	len[k] = r - l + 1;
	if (l == r) {
		t[k] = lazytag[k] = lazy[k] = tag[k] = 0;
		return;
	}
	int mid = l + r >> 1;
	build(l,mid,k << 1);
	build(mid + 1,r,k << 1 | 1);
}

void pushdown(int k) {
	tag[k << 1] = (tag[k << 1] + tag[k]) % MOD;
	tag[k << 1 | 1] = (tag[k << 1 | 1] + tag[k]) % MOD;
	lazy[k << 1] = (lazy[k << 1] + lazy[k]) % MOD;
	lazy[k << 1 | 1] = (lazy[k << 1 | 1] + lazy[k]) % MOD;
	lazytag[k << 1] = (lazytag[k << 1] + lazytag[k]) % MOD;
	lazytag[k << 1 | 1] = (lazytag[k << 1 | 1] + lazytag[k]) % MOD;
	t[k << 1] = (t[k << 1] - 1ll * sum[k << 1] * lazy[k] + 1ll * len[k << 1] * tag[k] + 1ll * len[k << 1] * lazytag[k]) % MOD;
	t[k << 1 | 1] = (t[k << 1 | 1] - 1ll * sum[k << 1 | 1] * lazy[k] + 1ll * len[k << 1 | 1] * tag[k] + 1ll * len[k << 1 | 1] * lazytag[k]) % MOD;
	tag[k] = lazytag[k] = lazy[k] = 0;
}

void update(int l,int r,int L,int R,int k,int d,int z,int y) {
	if (L <= l && r <= R) {
		t[k] = (t[k] - (sum[k] - 1ll * d * len[k]) % MOD * z % MOD + 1ll * len[k] * y) % MOD;
		tag[k] = (tag[k] + 1ll * d * z % MOD) % MOD;
		lazy[k] = (lazy[k] + z) % MOD;
		lazytag[k] = (lazytag[k] + y) % MOD;
		return;
	}
	pushdown(k);
	int mid = l + r >> 1;
	if (L <= mid) update(l,mid,L,R,k << 1,d,z,y);
	if (R >  mid) update(mid + 1,r,L,R,k << 1 | 1,d,z,y);
	t[k] = (t[k << 1] + t[k << 1 | 1]) % MOD;
}

int query(int l,int r,int x,int k) {
	if (l == r) return t[k];
	pushdown(k);
	int mid = l + r >> 1;
	if (x <= mid) return query(l,mid,x,k << 1);
	if (x >  mid) return query(mid + 1,r,x,k << 1 | 1);
}

int main () {
	read(n);
	for (int i = 2 ; i <= n ; ++ i)
		addEdge(read(),i);
	dfs(1,0);
	read(m);
	build(1,n,1);
	int op,v,x,k;
	for (int i = 1 ; i <= m ; ++ i) {
		read(op);
		if (op == 1) {
			read(v);read(x);read(k);
			update(1,n,dfn[v],dfn[v] + sz[v] - 1,1,dep[v],k,x);
		}
		else {
			read(v);
			print((query(1,n,dfn[v],1) % MOD + MOD) % MOD),putchar('\n');
		}
	}
	fwrite(obuf,O - obuf,1,stdout);
	return 0;
}
```

---

## 作者：Cylete (赞：0)

要求支持修改子树和查询权值

无脑上树剖

对于每次修改操作

我们令$newval = val + deep[x] * k$

其中$x$为节点，$val$为加的权值，$k$就是题意中的$k$

遇到一个节点$y$，我们就把他的权值加上$newval - k * deep[y]$

这样转换后线段树支持加操作就容易维护了

```cpp
#define int long long
#define next kkksc03
#define mid ((l+r)>>1)
#define lson (o<<1)
#define rson (o<<1|1)
#define R register
#define PP pair<int, int>
#define mp(x, y) make_pair(x, y)

#define size dedede//cf

const int P = 1e9 + 7;
const int N = 3e5 + 10;

int n, m;

int cut, head[N], ver[N << 1], next[N << 1];
inline void add(int x, int y)
{
	ver[++cut] = y; next[cut] = head[x]; head[x] = cut;
}

int deep[N], f[N], size[N], son[N], id[N], tot, dede[N];
inline void dfs1(int x, int fa)
{
	deep[x] = deep[fa] + 1;
	f[x] = fa;
	size[x] = 1;
	for(R int i = head[x]; i; i = next[i])
	{
		int y = ver[i];
		if(y == fa) continue;
		dfs1(y, x);
		size[x] += size[y];
		if(size[y] > size[son[x]]) son[x] = y;
	}
}

inline void dfs2(int x, int mtop)
{
	id[x] = ++tot;
	dede[tot] = x;
	if(!son[x]) return;
	dfs2(son[x], mtop);
	for(R int i = head[x]; i; i = next[i])
	{
		int y = ver[i];
		if(y == son[x] || y == f[x]) continue;
		dfs2(y, y);
	}
}

PP tree[N << 2];
int ans[N];

inline void pushdown(int o, int l1, int r1, int l2, int r2)
{
	if(tree[o].first == 0 && tree[o].second == 0) return;
	if(l1 == r1) ans[l1] = ((ans[l1] + tree[o].first - tree[o].second * deep[dede[l1]]) % P + P) % P;
	else tree[lson].first = ((tree[lson].first + tree[o].first) % P + P) % P, tree[lson].second = ((tree[lson].second + tree[o].second) % P + P) % P;
	if(l2 == r2) ans[l2] = ((ans[l2] + tree[o].first - tree[o].second * deep[dede[l2]]) % P + P) % P;
	else tree[rson].first = ((tree[rson].first + tree[o].first) % P + P) % P, tree[rson].second = ((tree[rson].second + tree[o].second) % P + P) % P;
	tree[o].first = 0;
	tree[o].second = 0;
}

inline void update(int o, int l, int r, int ql, int qr, PP val)
{
	if(ql <= l && r <= qr)
	{
		if(l == r) ans[l] = ((ans[l] + val.first - deep[dede[l]] * val.second) % P + P) % P;
		else tree[o].first = ((tree[o].first + val.first) % P + P) % P, tree[o].second = ((tree[o].second + val.second) % P + P) % P;
		return;
	}
	pushdown(o, l, mid, mid + 1, r);
	if(ql <= mid) update(lson, l, mid, ql, qr, val);
	if(qr > mid) update(rson, mid + 1, r, ql, qr, val);
}

inline int query(int o, int l, int r, int pos)
{
	if(l == r) return ans[l];
	pushdown(o, l, mid, mid + 1, r);
	if(pos <= mid) return query(lson, l, mid, pos);
	else return query(rson, mid + 1, r, pos);
}

signed main()
{
	into();
	read(n);
	for(R int i = 2, x; i <= n; i++) read(x), add(x, i), add(i, x);
	dfs1(1, 0);
	dfs2(1, 1);
	read(m);
	while(m--)
	{
		R int opt, x, value, k;
		read(opt); read(x);
		if(opt == 1)
		{
			read(value); read(k);
			update(1, 1, n, id[x], id[x] + size[x] - 1, mp((value + deep[x] * k) % P, k));
		}
		else writeln(query(1, 1, n, id[x]));
	}
	return 0;
}
```

---

## 作者：bztMinamoto (赞：0)

打广告->[这里](https://www.cnblogs.com/bztMinamoto/p/9456692.html)

话说真没想到这题竟然这么简单……死活都想不出来……

先dfs预处理出每一个节点的dfs序，以及子树代表的区间$ls$和$rs$，以及每一个点的深度$dep$

假设先$add(ls[v],x+dep[v]*k),add(rs[v]+1,-x-dep[v]*k)$，然后用树状数组维护前缀和，树状数组设为$c1$

可以发现，$v$这个点多加去了$dep[v]*k$，要减掉。同理可得，$v$的所有子树都要减掉$dep[j]*k$（$j$为$v$的子节点）

可以证明以上这么乱搞之后每一个点的值都加上了正确的数

乱证：$j$节点经过这一操作后加上了$dep[v]*k-dep[j]*k=k*(dep[j]-dep[v])=k*dis[v,j]$

然后证明每一个节点都加上了正确的数值

那么只要再开一个树状数组维护前缀$k$就可以了

查询的答案就是$sum(ls[v],c1)-sum(ls[v],c2)*dep[v]$
```
//minamoto
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(ll x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=300005,mod=1e9+7;
int ver[N],head[N],Next[N],dep[N];
int ls[N],rs[N];
ll c[2][N];
int n,tot,q,cnt;
inline void add(int x,ll val,int k){
    for(int i=x;i<=n;i+=i&(-i))
    (c[k][i]+=val)%=mod;
}
inline ll sum(int x){
    ll a=0,b=0;
    for(int i=ls[x];i;i-=i&(-i)){
        a+=c[0][i],b+=c[1][i];
    }
    return ((a-b*dep[x])%mod+mod)%mod;
}
void dfs(int u,int fa){
    ls[u]=++cnt;
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=Next[i]) dfs(ver[i],u);
    rs[u]=cnt;
}
int main(){
    //freopen("testdata.in","r",stdin);
    n=read();
    for(int i=2;i<=n;++i){
        int fa=read();
        ver[++tot]=i,Next[tot]=head[fa],head[fa]=tot;
    }
    dfs(1,0);
    q=read();
    while(q--){
        int opt=read(),v=read();
        if(opt&2) print(sum(v));
        else{
            ll x=read(),k=read();
            add(ls[v],x+dep[v]*k,0);
            add(rs[v]+1,-x-dep[v]*k,0);
            add(ls[v],k,1);
            add(rs[v]+1,-k,1);
        }
    }
    Ot();
    return 0;
}
```

---

