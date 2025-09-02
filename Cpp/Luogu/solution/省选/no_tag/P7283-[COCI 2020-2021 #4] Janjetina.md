# [COCI 2020/2021 #4] Janjetina

## 题目背景

疫情封禁期间，克罗地亚的所有餐厅均被关闭。

Malnar 先生为此十分伤感。但他不久发现并没有必要感到如此伤心，因此他决定将在封禁结束后周游克罗地亚，并在最好的餐厅中享用最美味的羊肉。

## 题目描述

Malnar 先生将访问 $n$ 个城市，分别用整数 $1$ 到 $n$ 表示。同时，他经过调研发现，有 $n-1$ 条连接其中两个城市的双向路。

每条路上均有一家提供羊肉的餐厅，同时给定每个餐厅可以订购的最大羊肉的重量。

他将选择两个城市 $x$ 和 $y$，并以最短路径（指经过的最少的路）从 $x$ 到达 $y$。他将且仅将在一家餐厅停留，且这家餐厅为可提供羊肉重量最多的一家（如果有多家这样的餐厅，他将会选择任意一家），并将订购的羊肉全部吃光。

如果通过一种长度为 $l$ 的路径可以吃到 $w$ 千克的羊肉，且 $w-l \ge k$，那么 Malnar 先生就称之为**满意的**。一种路径的长度等同于其经过路的条数。

求有多少个有序数对 $(x,y)$，使得从 $x$ 到 $y$ 的最短路径是满意的。

## 说明/提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/orifach0.png)

满足题意的有序数对有 $(1,3),(3,1),(1,5),(5,1),(3,5),(5,3),(4,5),(5,4)$。

#### 数据规模与约定

**本题采用捆绑评测。**

| Subtask | 分值 | 数据范围及约定 |
| :----------: | :----------: | :----------: |
| $1$ | $15$ | $1 \le n \le 1000$ |
| $2$ | $35$ | 城市 $i$ 和 $i+1$ （$1 \le i \le n-1$）直接相连（即最短距离为 $1$） |
| $2$ | $60$ | 无 |

对于 $100\%$ 的数据，$1 \le n,k,w \le 10^5$，$1 \le x,y \le n,x \neq y$。

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2020-2021](https://hsin.hr/coci/) [CONTEST #4](https://hsin.hr/coci/contest4_tasks.pdf)  _T4 Janjetina_。**

## 样例 #1

### 输入

```
3 1
1 2 3
1 3 2```

### 输出

```
6```

## 样例 #2

### 输入

```
4 1
1 2 1
2 3 2
3 4 3```

### 输出

```
6```

## 样例 #3

### 输入

```
5 2
1 2 2
1 3 3
3 4 2
3 5 4```

### 输出

```
8```

# 题解

## 作者：钰瑾_恋涵 (赞：6)

[题目链接](https://www.luogu.com.cn/problem/P7283)

### 题目大意:

给定一棵树，求满足路径最大值减路径长度大于等于 $k$ 的点对 $(u,v)$ 的数量。


### 分析:

求树上满足条件的点对数量，很容易想到点分治可以做。

设当前根为 $root$，$g[x]$ 表示 $x$ 到 $root$ 之间的最大值，$d[x]$ 表示 $x$ 到 $root$ 的距离。

在 $root$ 为根的子树中点对 $(u, v)$ 合法当且仅当 $\max (g[u],g[y])-d[u]-d[v] \geq k$ 且 $u$，$v$ 不属于 $root$ 的同一直接儿子下。

max 很不好处理，所以我们可以将它拆开成两个部分。

$$\begin{cases}
g[u]-d[u]-d[v]\geq k,& g[u]\geq g[v]\\
g[v]-d[u]-d[v]\geq k,& g[u]\leq g[v]
\end{cases}$$

移项后:

$$\begin{cases}
g[u]-d[u]-k\geq d[v],& g[u]\geq g[v]\\
-d[u]-k\geq d[v]-g[v],& g[u]\leq g[v]
\end{cases}$$

这两个部分显然可以用两个树状数组维护，至于如何确定是哪个贡献，直接对子树节点按 $g$ 排序即可。**注意此处需要取等**。

然后我们就发现会算重，因为 $root$ 同一直接儿子内部可能导致不合法的贡献，直接减去就完了。。。

### 时间复杂度分析:

经典点分治，每次找重心处理，只有 $\log n$ 层，每次计算答案，对但前子树扫描一遍预处理，$O(siz(x))$，排序加树状数组 $O(siz(x)\log(siz(x)))$，去重时同样是遍历一遍当前子树复杂度相同。子树总和大小为 $n$，所以最后时间复杂度为 $O(n\log^2n)$。

### 代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
i64 read() {
	i64 x(0), f(0); char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}
int __stk[128], __len;
void put(i64 x) {
	if (x < 0) putchar('-'), x = -x;
	do { __stk[++__len] = x % 10, x /= 10; } while (x);
	while (__len) putchar(__stk[__len--] ^ 48);
}
const int N = 1e5 + 10, inf = 1e9;
int n, k;
i64 ans;
namespace DFZ {
    int head[N], cur;
    struct edge {
        int to, nxt, w;
    } e[N << 1];
    void link(int u, int v) {
		int w = read();
        e[++cur] = (edge) {v, head[u], w}, head[u] = cur;
        e[++cur] = (edge) {u, head[v], w}, head[v] = cur;
    }
    int root, siz[N], maxp[N];
    bool vis[N];
    void get_root(int u, int fa, int total) {
        maxp[u] = 0, siz[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            if (e[i].to == fa || vis[e[i].to]) continue;
            get_root(e[i].to, u, total);
            siz[u] += siz[e[i].to], maxp[u] = max(maxp[u], siz[e[i].to]);
        }
        maxp[u] = max(maxp[u], total - siz[u]);
        if (maxp[u] < maxp[root]) root = u;
    }
	int g[N], d[N], o[N], cnt;
	bool cmp(int x, int y) { return g[x] < g[y]; }
	struct BIT {
		int t[2000000];
		void add(int x, int y) { for (x += 1000000; x <= 2000000; x += x & -x) t[x] += y; }
		int ask(int x) { int res = 0; for (x += 1000000; x; x -= x & -x) res += t[x]; return res; }
	}t1, t2;
	void prepare(int u, int fa) {
		for (int i = head[u]; i; i = e[i].nxt) 
			if (!vis[e[i].to] && e[i].to != fa) 
				g[e[i].to] = max(g[u], e[i].w), d[e[i].to] = d[u] + 1, prepare(e[i].to, u);
	}
	void dfs(int u, int fa) {
		o[++cnt] = u;
		for (int i = head[u]; i; i = e[i].nxt) 
			if (!vis[e[i].to] && e[i].to != fa) dfs(e[i].to, u);
	}
    void calc(int u) {
        g[u] = 0, d[u] = 0, prepare(u, 0);
		cnt = 0, dfs(u, 0), sort(o + 1, o + cnt + 1, cmp);
		for (int i = 1; i <= cnt; ++i) ans += t1.ask(g[o[i]] - d[o[i]] - k), t1.add(d[o[i]], 1);
		for (int i = cnt; i >= 1; --i) ans += t2.ask(-d[o[i]] - k), t2.add(d[o[i]] - g[o[i]], 1);
		for (int i = 1; i <= cnt; ++i) t1.add(d[o[i]], -1), t2.add(d[o[i]] - g[o[i]], -1);
		for (int i = head[u]; i; i = e[i].nxt) {
			if (vis[e[i].to]) continue;
			cnt = 0, dfs(e[i].to, u), sort(o + 1, o + cnt + 1, cmp);
			for (int j = 1; j <= cnt; ++j) ans -= t1.ask(g[o[j]] - d[o[j]] - k), t1.add(d[o[j]], 1);
			for (int j = cnt; j >= 1; --j) ans -= t2.ask(-d[o[j]] - k), t2.add(d[o[j]] - g[o[j]], 1);
			for (int j = 1; j <= cnt; ++j) t1.add(d[o[j]], -1), t2.add(d[o[j]] - g[o[j]], -1);
		}
    }
    void divide(int u) {
        calc(u), get_root(u, 0, 0), vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            if (vis[e[i].to]) continue;
            root = 0, get_root(e[i].to, 0, siz[e[i].to]);
            divide(root);
        }
    }
}

signed main() {
	n = read(), k = read(); 
	for (int i = 1; i < n; ++i) DFZ::link(read(), read());
	DFZ::maxp[0] = n, DFZ::get_root(1, 0, n);
	DFZ::divide(DFZ::root), put(ans), putchar('\n');
	return 0;
}
```



---

## 作者：szhqwq (赞：2)

## $\tt{Solution}$

可以使用点分治套树状数组解决问题。

对于一条长度为 $l$ 的链，其价值 $w$ 为所经过的边的权值的**最大值**，题目要求满足条件 $w - l \geq k$ 的链的条数，相当于是 $w - l - k \geq 0$。首先将存下来的链根据 $w$ 从小到大排序，我们去考虑有多少条链能够与之合并，相当于去查找此前的链中满足 $l' \le w - l - k$ 的个数，可以使用树状数组维护。

这样就是一个二维偏序问题，第一维 $w$ 排序处理，第二维在树状数组中查找满足条件的链的个数。

注意处理同一个子树里计算重复的情况，需要单独在统计一个子树内的链时减去。

题目要求**有序数对** $(x,y)$ 的个数，最后答案乘 $2$ 即可。

```cpp
#include <bits/stdc++.h>

#define int long long
#define ll long long
#define ull unsigned long long
#define rep(i,l,r) for (int i = (int)(l); i <= (int)(r); ++ i )
#define rep1(i,l,r) for (int i = (int)(l); i >= (int)(r); -- i )
#define il inline
#define fst first
#define snd second
#define ptc putchar
#define Yes ptc('Y'),ptc('e'),ptc('s'),puts("")
#define No ptc('N'),ptc('o'),puts("")
#define YES ptc('Y'),ptc('E'),ptc('S'),puts("")
#define NO ptc('N'),ptc('O'),puts("")
#define pb emplace_back
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define debug() puts("------------------")

using namespace std;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
namespace szhqwq {
    template<class T> il void read(T &x) {
        x = 0; T f = 1; char ch = getchar();
        while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
        while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
        x *= f;
    }
    template<class T,class... Args> il void read(T &x,Args &...x_) { read(x); read(x_...); }
    template<class T> il void print(T x) {
        if (x < 0) ptc('-'), x = -x; 
        if (x > 9) print(x / 10); ptc(x % 10 + '0');
    }
    template<class T,class T_> il void write(T x,T_ ch) { print(x); ptc(ch); }
    template<class T,class T_> il void chmax(T &x,T_ y) { x = max(x,y); }
    template<class T,class T_> il void chmin(T &x,T_ y) { x = min(x,y); }
    template<class T,class T_,class T__> il T qmi(T a,T_ b,T__ p) {
        T res = 1; while (b) {
            if (b & 1) res = res * a % p;
            a = a * a % p; b >>= 1;
        } return res;
    }
    template<class T> il int getinv(T x,T p) { return qmi(x,p - 2,p); }
} using namespace szhqwq;
const int N = 2e5 + 10,inf = 1e9,mod = 998244353;
const ll inff = 1e18;
int n,k,rt,sum;
int h[N],e[N],ne[N],w[N],idx;
PII dd[N]; int cnt;
int mx[N],siz[N],dist[N]; 
bool vis[N]; int res;
PII aa[N]; int cc;
struct BIT {
    int tr[N];
    il int lowbit(int x) { return x & -x; }

    il void add(int x,int k) {
        for (; x <= 100000; x += lowbit(x)) tr[x] += k;
    }

    il int ask(int x) {
        if (x < 0) x = 0;
        int res = 0;
        for (; x; x -= lowbit(x)) res += tr[x];
        return res;
    }
} bit;

il void add(int a,int b,int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++;
}

il void calcsiz(int u,int fa) {
    siz[u] = 1;
    mx[u] = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa || vis[j]) continue;
        calcsiz(j,u);
        chmax(mx[u],siz[j]);
        siz[u] += siz[j];
    }
    chmax(mx[u],sum - siz[u]);
    if (mx[u] < mx[rt]) rt = u;
}

il void calcdist(int u,int fa,int nowdis) {
    dd[++ cnt] = {dist[u],nowdis};
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa || vis[j]) continue;
        dist[j] = max(dist[u],w[i]);
        calcdist(j,u,nowdis + 1);
    }
}

il void calcans(int u) {
    cc = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (vis[j]) continue;
        cnt = 0; dist[j] = w[i]; calcdist(j,u,1);
        sort(dd + 1,dd + cnt + 1);
        rep(i,1,cnt) {
            res -= bit.ask(dd[i].fst - dd[i].snd - k);
            bit.add(dd[i].snd,1);
        }
        rep(i,1,cnt) bit.add(dd[i].snd,-1),aa[++ cc] = dd[i];
    }
    sort(aa + 1,aa + cc + 1);
    rep(i,1,cc) {
        res += bit.ask(aa[i].fst - aa[i].snd - k);
        bit.add(aa[i].snd,1);   
    }
    rep(i,1,cc) {
        if (aa[i].fst - aa[i].snd >= k) ++ res;
        bit.add(aa[i].snd,-1);
    }
}

il void dfz(int u) {
    vis[u] = 1;
    calcans(u);
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (vis[j]) continue;
        mx[0] = inff;
        rt = 0; sum = siz[j];
        calcsiz(j,0);
        dfz(rt);
    }
}

il void solve() {
    //------------code------------
    memset(h,-1,sizeof h);
    read(n,k);
    rep(i,1,n - 1) {
        int a,b,c; read(a,b,c);
        add(a,b,c); add(b,a,c);
    }
    vis[0] = 1; mx[0] = n; rt = 0; sum = n;
    calcsiz(1,0);
    dfz(rt);
    write(res << 1ll,'\n');
    return ;
}

il void init() {
    return ;
}

signed main() {
    // init();
    int _ = 1;
    // read(_);
    while (_ -- ) solve();
    return 0;
}
```

---

## 作者：harmis_yz (赞：2)

## 分析

考虑点分治。

将每条路径从重心断开分成两条子路径。若 $(x,y)$ 合法，则有：$\max(\max(v_{1,1},v_{1,2},\dots,v_{1,k1}),\max(v_{2,1},v_{2,2},\dots,v_{2,k2}))-(k1+k2) \ge k$。将所有子路径按照路径边权最大值从小到大排序就有：$\max(v_{2,1},v_{2,2},\dots,v_{2,k2})-(k1+k2) \ge k$。

这个时候我们去枚举子路径，就相当于在求其前面的路径长度 $k1 \le \max(v_{2,1},v_{2,2},\dots,v_{2,k2})-k2- k $ 的数量。这个直接树状数组就行了，复杂度是 $O(n \log^2 n)$ 的。

注：记得减去在同一棵子树中的两条子路径的情况和加上单独一条合法子路径的情况。

## 代码

```cpp
const int N=2e5+10;
int n,k;
int ne[N],e[N],h[N],w[N],idx;
int max_p[N],siz[N];
int root,Siz;
bool vis[N];
int ans;
vector<pii> v1,v2;
int tr[N];

il void add(int x,int y){
	while(x<N) tr[x]+=y,x+=x&(-x);
}
il int query(int x){
	int sum=0;
	while(x) sum+=tr[x],x-=x&(-x);
	return sum;
}
il bool cmp(pii a,pii b){
	return a.x<b.x;
}
il void add(int a,int b,int c){
	ne[++idx]=h[a],e[idx]=b,w[idx]=c,h[a]=idx;
	ne[++idx]=h[b],e[idx]=a,w[idx]=c,h[b]=idx;
}
il void dfs(int now,int fa,int dis,int Max){
	v2.push_back({Max,dis});
	if(Max-dis>=k) ++ans;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa||vis[j]) continue;
		dfs(j,now,dis+1,max(Max,w[i]));
	}
	return ;
}
il void calc(int now){
	v1.clear();
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(vis[j]) continue;
		v2.clear(),dfs(j,now,1,w[i]);
		sort(v2.begin(),v2.end(),cmp);
		for(auto x:v2){
			int dt=x.x-x.y-k;
			if(dt>=1){
				int sum=query(dt);
				ans-=sum;
			}
			add(x.y,1);
		}
		for(auto x:v2)
			add(x.y,-1),
			v1.push_back(x);
	}
	sort(v1.begin(),v1.end(),cmp);
	for(auto x:v1){
		int dt=x.x-x.y-k;
		if(dt>=1){
			int sum=query(dt);
			ans+=sum;
		}
		add(x.y,1);
	}
	for(auto x:v2) add(x.y,-1);
	return ;
}
il void find(int now,int fa){
	siz[now]=1,max_p[now]=0;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa||vis[j]) continue;
		find(j,now),siz[now]+=siz[j];
		max_p[now]=max(max_p[now],siz[j]);	
	}
	max_p[now]=max(max_p[now],Siz-siz[now]);
	if(max_p[root]>max_p[now]) root=now;
	return ;
}
il void work(int now){
	vis[now]=1,calc(now);
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(vis[j]) continue;
		Siz=siz[j],root=0,find(j,0);
		work(root);
	}
	return ;
}

il void solve(){
	n=rd,k=rd;
	for(re int i=1,a,b,c;i<n;++i)
		a=rd,b=rd,c=rd,
		add(a,b,c);
	vis[0]=1,max_p[0]=n,root=0,Siz=n,find(1,0);
	work(root),printf("%lld\n",ans*2);
	return ;
}
```

---

## 作者：yqr123YQR (赞：0)

### 分析
点分治板板。

其他都是板板，只考虑子树信息合并的部分。

设将已经求出的，子树内每点 $i$ 至当前分治重心 $rt$ 的路径信息记录在 `dist` 中。

因为最大值不好处理，故将 `dist` 按题面的 $w$ 递增排序，扫一遍，最大值即为当前路径的 $w$。此时考虑 $l$ 的限制，易知贡献为此前 $l'\leqslant w-k-l$ 的路径数量，以树状数组维护。

上面的方法会算重，同理减去各儿子子树内的贡献即可。
### 代码
```cpp
//......
std::vector<edge> g[maxn];
struct BIT {/*......*/}bit;//树状数组
void devide(int k)
{
	// printf("%d\n", k);
	del[k] = true;
	int lastcnt = 0;
	for(edge i : g[k])
	{
		int to = i.to;
		if(del[to]) continue;
		calcdist(to, -1, i.value, 1);
		std::sort(dist + lastcnt + 1, dist + cnt + 1);
		for(int j = lastcnt + 1; j <= cnt; j++)//减去子树内部的贡献
		{
			ans -= bit.query(dist[j].value - m - dist[j].to);
			bit.modify(dist[j].to, 1);
		}
		for(int j = lastcnt + 1; j <= cnt; j++) bit.modify(dist[j].to, -1);
		lastcnt = cnt;
	}
	std::sort(dist + 1, dist + 1 + cnt);
	for(int i = 1; i <= cnt; i++)//加上整体的贡献
	{
		if(dist[i].value - dist[i].to >= m) ans++;//考虑单条路径合法的情况
		ans += bit.query(dist[i].value - m - dist[i].to);
		bit.modify(dist[i].to, 1);
	}
	for(int i = 1; i <= cnt; i++) bit.modify(dist[i].to, -1);
	cnt = 0;
	for(edge i : g[k])
	{
		int to = i.to;
		if(del[to]) continue;
		rtmx = nown = sz[to];
		calcsize(to, -1, 1);
		calcsize(rt, -1, 0);
		devide(rt);
	}
}
int main()
{
	//init......
	printf("%lld\n", ans << 1);//因为为有序数对，故需 ×2
	return 0;
}
```

---

