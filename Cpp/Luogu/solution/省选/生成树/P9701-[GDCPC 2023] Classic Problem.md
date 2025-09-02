# [GDCPC 2023] Classic Problem

## 题目描述

给定一张 $n$ 个点的无向完全图与 $m$ 个三元组 $P_1, P_2, \cdots, P_m$，其中 $P_i = (u_i, v_i, w_i)$。保证 $1 \leq u_i < v_i \leq n$，且对于任意两个编号不同的三元组 $P_i$ 和 $P_j$，有 $(u_i, v_i) \ne (u_j, v_j)$。

对于图中的任意两个节点 $x$ 与 $y$（$1 \leq x < y \leq n$），定义它们之间的无向边的边权如下：

- 如果存在一个三元组 $P_i$ 满足 $u_i = x$ 且 $v_i = y$，那么边权为 $w_i$。
- 否则，边权为 $|x - y|$。

求这张图的最小生成树的边权之和。

## 样例 #1

### 输入

```
3
5 3
1 2 5
2 3 4
1 5 0
5 0
5 4
1 2 1000000000
1 3 1000000000
1 4 1000000000
1 5 1000000000```

### 输出

```
4
4
1000000003```

# 题解

## 作者：EuphoricStar (赞：6)

对于一个点 $x$，若 $\exists i, u_i = x \lor v_i = x$，则称 $x$ 为**特殊点**，否则为**一般点**。

首先发现，对于极长的一段 $[l, r]$ 满足 $l \sim r$ 均为一般点，那么可以连边 $(l, l + 1), (l + 1, l + 2), \ldots, (r - 1, r)$，然后把 $[l, r]$ 缩成一个**连续点**。因为这些点通过别的点与外界连通显然不优。

对于一个特殊点 $x$，我们把它变成区间为 $[x, x]$ 的连续点。然后把所有连续点按区间左端点排序后重编号。

然后现在相当于我们有至多 $4m + 1$ 个点的完全图，有一些给定边，若对于之间不存在给定边的点对 $u, v\ (u < v)$，它们之间的边权是 $l_v - r_u$。求这个完全图的最小生成树。

考虑 Boruvka 算法，其流程是每轮对每个连通块找到一条连向另一连通块的最短边，然后合并两端点。

考虑模拟流程。我们首先考虑给定边，然后考虑其他边。前者是容易的。至于后者，我们希望找到 $u$ 左右侧最接近 $u$ 且和 $u$ 不在同一连通块且和 $u$ 之间没有给定边的点 $v$。于是我们每次先处理出 $pre_u$ 和 $nxt_u$ 表示 $u$ 左侧（或右侧）最接近 $u$ 且和 $u$ 不在同一连通块的点，然后枚举 $u$，暴力找 $v$，以左侧为例，就是若 $u, v$ 之间存在给定边就 $v \gets v - 1$，否则 $v \gets pre_v$。因为边数是 $O(m)$ 的，所以这部分复杂度是对的。

若使用 `set` 存给定边，时间复杂度为 $O(m \log^2 m)$。

```cpp
// Problem: P9701 [GDCPC2023] Classic Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9701
// Memory Limit: 1 MB
// Time Limit: 8000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 500100;

ll n, m, lsh[maxn], tot, fa[maxn], pre[maxn], nxt[maxn];
pii f[maxn];
set<ll> S[maxn];

struct E {
	ll u, v, d;
	E(ll a = 0, ll b = 0, ll c = 0) : u(a), v(b), d(c) {}
} Es[maxn], G[maxn];

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

inline bool merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		fa[x] = y;
		return 1;
	} else {
		return 0;
	}
}

struct node {
	ll l, r, f;
	node(ll a = 0, ll b = 0, ll c = 0) : l(a), r(b), f(c) {}
} a[maxn];

inline bool operator < (const node &a, const node &b) {
	return a.l < b.l;
}

void solve() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= m * 5; ++i) {
		S[i].clear();
	}
	tot = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%lld%lld%lld", &Es[i].u, &Es[i].v, &Es[i].d);
		lsh[++tot] = Es[i].u;
		lsh[++tot] = Es[i].v;
	}
	sort(lsh + 1, lsh + tot + 1);
	tot = unique(lsh + 1, lsh + tot + 1) - lsh - 1;
	lsh[0] = 0;
	lsh[tot + 1] = n + 1;
	ll K = tot, ans = 0;
	for (int i = 1; i <= tot; ++i) {
		a[i] = node(lsh[i], lsh[i], 1);
	}
	for (int i = 0; i <= tot; ++i) {
		if (lsh[i] + 1 != lsh[i + 1]) {
			a[++K] = node(lsh[i] + 1, lsh[i + 1] - 1, 0);
			ans += lsh[i + 1] - lsh[i] - 2;
		}
	}
	sort(a + 1, a + K + 1);
	int tt = 0;
	map<pii, ll> mp;
	for (int i = 1; i <= m; ++i) {
		ll u = Es[i].u, v = Es[i].v, d = Es[i].d;
		u = lower_bound(a + 1, a + K + 1, node(u, u, 0)) - a;
		v = lower_bound(a + 1, a + K + 1, node(v, v, 0)) - a;
		if (u > v) {
			swap(u, v);
		}
		G[++tt] = E(u, v, d);
		S[u].insert(v);
		S[v].insert(u);
		mp[mkp(u, v)] = mp[mkp(v, u)] = d;
	}
	for (int i = 1; i <= K; ++i) {
		fa[i] = i;
	}
	while (1) {
		bool flag = 1;
		for (int i = 1; i <= K; ++i) {
			if (find(i) != find(1)) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			break;
		}
		for (int i = 1; i <= K; ++i) {
			f[i] = mkp(1e18, -1);
		}
		for (int u = 1; u <= K; ++u) {
			for (int v : S[u]) {
				if (find(u) == find(v)) {
					continue;
				}
				ll d = mp[mkp(u, v)];
				f[find(u)] = min(f[find(u)], mkp(d, 1LL * find(v)));
			}
		}
		for (int i = 1, j = 1; i <= K; i = (++j)) {
			while (j < K && find(j + 1) == find(i)) {
				++j;
			}
			for (int u = i; u <= j; ++u) {
				pre[u] = i - 1;
				nxt[u] = j + 1;
			}
		}
		for (int u = 1; u <= K; ++u) {
			int v = u;
			while (v >= 1 && (S[u].find(v) != S[u].end() || find(v) == find(u))) {
				if (find(v) == find(u)) {
					v = pre[v];
				} else {
					--v;
				}
			}
			if (v) {
				f[find(u)] = min(f[find(u)], mkp(a[u].l - a[v].r, 1LL * find(v)));
			}
			v = u;
			while (v <= K && (S[u].find(v) != S[u].end() || find(v) == find(u))) {
				if (find(v) == find(u)) {
					v = nxt[v];
				} else {
					++v;
				}
			}
			if (v <= K) {
				f[find(u)] = min(f[find(u)], mkp(a[v].l - a[u].r, 1LL * find(v)));
			}
		}
		for (int i = 1; i <= K; ++i) {
			if (fa[i] == i && merge(i, f[i].scd)) {
				ans += f[i].fst;
			}
		}
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```


---

## 作者：Albert_van (赞：5)

Boruvka 蓝莓算法模板题。

首先图的规模太大，考虑压缩一些点或状态。$m$ 条指定边只涉及 $2m$ 个结点，称它们为关键点，那么相邻关键点 $l$ 与 $r$ 间所有点的连边没有限制。于是在整个图的 MST 中，必然有一条长 $r-l-2$ 的链贯穿 $[l+1,r-1]$ 间所有非关键点。

>  要证明，考虑利用 MST 的性质：$x$ 到 $y$ 在树上路径最大值，等于原图路径最大值的最小值。这里对 $x,y\in(l,r)$ 有 $x$ 到 $y$ 路径最大值为 $1$。因为 $x$ 和 $y$ 连向外界的边权不会小于 $1$，所以连成链必然不劣。

于是先令答案加上 $r-l-2$，然后将 $[l+1,r-1]$ 串起来视作一个结点，与关键点一起加入图中。这样点数就降到了 $\mathcal O(m)$ 级别。

对这个新的完全图，使用蓝莓算法求 MST，每轮需对每个点求出离开连通块的最小边。对于指定的关键点间连边，逐个用边权更新两端点即可。考虑剩下边权为两点距离的连边。

初始每个点独立组成连通块时，可以从点 $i$ 出发暴力向前/后跳（$p\gets p\mp 1$），找到离 $i$ 最近的 $p$ 满足 $i$ 与 $p$ 间没有指定边。这个过程显然花费 $\mathcal O(m)$。

在一个连通块有多个点时，$p$ 必须同时满足 $p$ 与 $i$ 不在同一块内，复杂度无法保证。进行优化，记录 $\operatorname{pre}_p$ 表示 $p$ 之前第一个不在 $p$ 的连通块内的点，$\operatorname{nxt}_p$ 同理。那么遇到 $p$ 与 $i$ 在同一块内时，令 $p\gets \operatorname{pre}_p/\operatorname{nxt}_p$ 即可。每次这样的操作后，要么 $p$ 合法并结束，要么进行一次 $p\gets p\mp 1$ 的操作，所以这里的花费也是 $\mathcal O(m)$。

于是每一轮 $\mathcal O(m)$，总复杂度 $\mathcal O(m\log m)$。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>

using namespace std;

const int N=514114;

namespace U{
	int anc[N];
	void set(int n){for(int i=1;i<=n;++i) anc[i]=i;}
	int fnd(int x){return anc[x]==x?x:anc[x]=fnd(anc[x]);}
	void mrg(int x,int y){anc[fnd(x)]=fnd(y);}
}using namespace U;

struct point{int p,id;}pt[N];

struct ed{
	int v,w;
	bool operator<(const ed t)const{return v<t.v;}
};
vector<ed> vc[N];

bool ex(int x,int y){
	auto p=lower_bound(vc[x].begin(),vc[x].end(),(ed){y,0});
	return p!=vc[x].end()&&p->v==y;
}

struct edg{int x,y,w;}e[N];

void upe(edg &k,edg n){if(n.w<k.w) k=n;}

map<int,int> pos;

int u[N],v[N],we[N],l[N],r[N],pre[N],nxt[N];

int main()
{
	int T;scanf("%d",&T);while(T--){
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=m;++i){
			scanf("%d%d%d",u+i,v+i,we+i);if(u[i]<v[i]) swap(u[i],v[i]);
			pt[i*2-1]=(point){u[i],i};pt[i*2]=(point){v[i],0};
		}
		sort(pt+1,pt+(m<<1|1),[](point x,point y){return x.p<y.p;});
		long long ans=0;int c=0;
		for(int i=1;i<=m<<1;++i){
			int pl=pt[i-1].p,pr=pt[i].p;
			if(pr>pl+1) ans+=pr-pl-2,++c,l[c]=pl+1,r[c]=pr-1;
			if(pr>pl) ++c,l[c]=r[c]=pr;
			pos[pr]=c;int x=pt[i].id;
			if(x) vc[c].push_back((ed){pos[v[x]],we[x]}),vc[pos[v[x]]].push_back((ed){c,we[x]});
		}
		if(pt[m<<1].p<n) ++c,l[c]=pt[m<<1].p+1,r[c]=n,ans+=n-l[c];
		set(n=c);for(int i=1;i<=n;++i) sort(vc[i].begin(),vc[i].end());
		nxt[n+1]=anc[n+1]=0;int kc=n;while(kc>1){
			for(int i=1;i<=n;++i) if(fnd(i)==i) e[i].w=1e9+7;
			for(int i=1;i<=n;++i) pre[i]=fnd(i)==fnd(i-1)?pre[i-1]:i-1;
			for(int i=n;i;--i) nxt[i]=fnd(i)==fnd(i+1)?nxt[i+1]:i+1;
			for(int i=1;i<=n;++i){
				int p=i,a=fnd(i);
				while(fnd(p)==a||ex(i,p)) p=fnd(p)==a?pre[p]:p-1;
				if(p) upe(e[a],(edg){i,p,l[i]-r[p]});
				p=i;while(fnd(p)==a||ex(i,p)) p=fnd(p)==a?nxt[p]:p+1;
				if(p<=n) upe(e[a],(edg){i,p,l[p]-r[i]});
			}
			for(int i=1;i<=n;++i) for(auto[v,w]:vc[i]) if(fnd(i)!=fnd(v))
				upe(e[fnd(i)],(edg){i,v,w});
			for(int i=1;i<=n;++i) if(fnd(i)==i&&fnd(e[i].x)!=fnd(e[i].y))
				U::mrg(e[i].x,e[i].y),ans+=e[i].w,--kc;
		}
		printf("%lld\n",ans);
		for(int i=1;i<=n;++i) vc[i].clear();
	}
}
```



---

## 作者：rui_er (赞：3)

题如其名，确实挺经典的。

我们称边权在输入中给定的边为特殊边，其它边为平凡边。称特殊边涉及到的点为特殊点，其它点为平凡点。

显然，对于连续的若干平凡点 $[l,r]$，他们内部的最优连边方式就是连成一条链，花费 $r-l$ 的代价。我们先把这样的代价加到答案中，然后将极长连续平凡点缩成一个点，称为区间点。

我们可以按照编号从小到大的顺序为区间点和特殊点重新标号。问题转化为给定一个由区间点和特殊点构成的 $O(m)$ 点的完全图，求它的最小生成树。

有特殊性质的点数特别多的稠密图的最小生成树问题一般考虑使用 Boruvka 算法进行求解。对于图 $G=(V,E)$ 求最小生成树，Boruvka 算法的思路是：每一轮找到每个连通块向外连的边权最小的边，在这轮结束后把所有最小边连上，直到整个图连通为止。显然，每一轮过后连通块数至少减半，因此轮数为 $O(\log|V|)$，复杂度为 $O(|E|\log|V|)$。我们可以利用图的特殊性质，加速找到最小边的过程，使得复杂度降至 $O(|V|\log|V|)$。

在每一轮开始时，预处理 $pre(u),suc(u)$ 表示节点 $u$ 前面/后面最近的不在同一连通块的点。对于区间点，它的最小边一定是它与 $pre(u)$ 或 $suc(u)$ 之间的。对于特殊点，首先判一遍所有跨连通块的特殊边，然后分别找到前面/后面最近的既不在同一连通块又没有特殊边相连的点，看看哪个更小即可。可以证明，每轮的时间复杂度为 $O(|V|)$，总复杂度为 $O(|V|\log|V|)$。由于重建的图的点数 $|V|=O(m)$，总复杂度为 $O(m\log m)$。

```cpp
// Problem: T368344 [GDCPC2023] L-Classic Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T368344?contestId=135929
// Memory Limit: 1 MB
// Time Limit: 8000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(ll x = (y); x <= (z); ++x)
#define per(x, y, z) for(ll x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
    uniform_int_distribution<ll> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 5e5 + 5, inf = 0x1f1f1f1f1f1f1f1fll;

ll T, n, m, U[N], V[N], W[N], buc[N], tot, cntV, val[N], pos[N], pre[N], suc[N], vis[N];
map<ll, ll> id;

struct Vertex {
    ll l, r;
    bool special;
    vector<tuple<ll, ll>> e;
}vtx[N];

struct Dsu {
    ll fa[N];
    void init(ll x) {rep(i, 1, x) fa[i] = i;}
    bool isroot(ll x) {return x == fa[x];}
    ll find(ll x) {return isroot(x) ? x : fa[x] = find(fa[x]);}
    bool same(ll x, ll y) {return find(x) == find(y);}
    bool merge(ll x, ll y) {
        if(same(x, y)) return false;
        x = find(x); y = find(y);
        fa[x] = y;
        return true;
    }
}dsu;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(cin >> T; T; --T) {
        cin >> n >> m;
        rep(i, 1, m) {
            cin >> U[i] >> V[i] >> W[i];
            buc[++tot] = U[i];
            buc[++tot] = V[i];
        }
        sort(buc + 1, buc + 1 + tot);
        tot = unique(buc + 1, buc + 1 + tot) - buc - 1;
        ll lst = 0;
        rep(i, 1, tot) {
            // segment
            if(buc[i] - lst + 1 >= 3) {
                ++cntV;
                vtx[cntV].l = lst + 1;
                vtx[cntV].r = buc[i] - 1;
                vtx[cntV].special = false;
            }
            // special
            ++cntV;
            vtx[cntV].l = vtx[cntV].r = buc[i];
            vtx[cntV].special = true;
            id[buc[i]] = cntV;
            lst = buc[i];
        }
        // segment
        if(n - lst + 1 >= 2) {
            ++cntV;
            vtx[cntV].l = lst + 1;
            vtx[cntV].r = n;
            vtx[cntV].special = false;
        }
        rep(i, 1, m) {
            vtx[id[U[i]]].e.emplace_back(id[V[i]], W[i]);
            vtx[id[V[i]]].e.emplace_back(id[U[i]], W[i]);
        }
        ll edges = 0, ans = 0;
        rep(u, 1, cntV) ans += vtx[u].r - vtx[u].l;
        dsu.init(cntV);
        while(edges < cntV - 1) { // MST - Boruvka algorithm
            rep(u, 1, cntV) {
                if(dsu.isroot(u)) {
                    val[u] = inf;
                    pos[u] = -1;
                }
            }
            rep(u, 1, cntV) {
                if(vtx[u].special) {
                    for(auto [v, w] : vtx[u].e) {
                        if(!dsu.same(u, v) && w < val[dsu.find(u)]) {
                            val[dsu.find(u)] = w;
                            pos[dsu.find(u)] = dsu.find(v);
                        }
                    }
                }
            }
            pre[1] = 0;
            rep(i, 2, cntV) pre[i] = dsu.same(i - 1, i) ? pre[i - 1] : i - 1;
            suc[cntV] = cntV + 1;
            per(i, cntV - 1, 1) suc[i] = dsu.same(i, i + 1) ? suc[i + 1] : i + 1;
            rep(u, 1, cntV) {
                if(vtx[u].special) for(auto [v, w] : vtx[u].e) vis[v] = 1;
                for(ll v = u; v >= 1; ) {
                    if(dsu.same(v, u)) v = pre[v];
                    else if(vis[v]) --v;
                    else {
                        if(vtx[u].l - vtx[v].r < val[dsu.find(u)]) {
                            val[dsu.find(u)] = vtx[u].l - vtx[v].r;
                            pos[dsu.find(u)] = dsu.find(v);
                        }
                        break;
                    }
                }
                for(ll v = u; v <= cntV; ) {
                    if(dsu.same(u, v)) v = suc[v];
                    else if(vis[v]) ++v;
                    else {
                        if(vtx[v].l - vtx[u].r < val[dsu.find(u)]) {
                            val[dsu.find(u)] = vtx[v].l - vtx[u].r;
                            pos[dsu.find(u)] = dsu.find(v);
                        }
                        break;
                    }
                }
                if(vtx[u].special) for(auto [v, w] : vtx[u].e) vis[v] = 0;
            }
            rep(u, 1, cntV) {
                if(dsu.isroot(u) && pos[u] != -1 && dsu.isroot(pos[u])) {
                    ++edges;
                    ans += val[dsu.find(u)];
                    dsu.merge(u, pos[u]);
                }
            }
        }
        cout << ans << endl;
        rep(i, 1, tot) buc[i] = id[i] = 0;
        rep(i, 1, cntV) {
            vis[i] = vtx[i].l = vtx[i].r = 0;
            vtx[i].special = false;
            vtx[i].e.clear();
        }
        tot = cntV = 0;
    }
    return 0;
}
```

---

## 作者：IdnadRev (赞：2)

我们先将值域离散成至多 $4m+1$ 段，每一段要么没有边相连，要么是一个单点。由于第一类一定内部使用长为 $1$ 的边相连，因此开始时我们仅有 $4m+1$ 个连通块。

使用 Boruvka，每一轮需要找到每一连通块的最小出边，我们分两类边讨论：

- 最小修改过的出边：暴力枚举相连的边，检查是否连接不同连通块。
- 最小未修改的出边：分在这一段前/后讨论，由于对称性不妨只考虑前者。我们暴力向前枚举不同连通块的段（可以记录前面第一个与其不同连通块的段来帮助枚举，具体可见 std），并判断是否有边相连，若有则继续往前枚举，由于边数总和是 $O(m)$，无效的枚举数量也是 $O(m)$ 级别。

于是经过 $O(\log m)$ 轮后我们能得到最小生成树，复杂度 $O(m\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=400005;
int n,m,T,nums,tot,stp;
long long ans;
int num[maxn],xx[maxn],yy[maxn],zz[maxn],typ[maxn],dsu[maxn],rec[maxn],mn[maxn],id[maxn],ll[maxn],rr[maxn],vis[maxn],pre[maxn],suf[maxn];
vector<int>v[maxn];
int find(int x){
	return dsu[x]==x? x:dsu[x]=find(dsu[x]);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m),nums=tot=ans=0;
		for(int i=1;i<=m;i++)
			scanf("%d%d%d",&xx[i],&yy[i],&zz[i]),num[++nums]=xx[i],num[++nums]=yy[i];
		sort(num+1,num+1+nums),nums=unique(num+1,num+1+nums)-num-1;
		int lst=0;
		for(int i=1;i<=nums;i++){
			if(num[i]>lst+1)
				tot++,ll[tot]=lst+1,rr[tot]=num[i]-1,typ[tot]=0;
			tot++,ll[tot]=num[i],rr[tot]=num[i],typ[tot]=i,id[i]=tot;
			lst=num[i];
		}
		for(int i=1;i<=m;i++){
			xx[i]=lower_bound(num+1,num+1+nums,xx[i])-num;
			yy[i]=lower_bound(num+1,num+1+nums,yy[i])-num;
			v[xx[i]].emplace_back(i),v[yy[i]].emplace_back(i);
		}
		if(lst+1<=n)
			tot++,ll[tot]=lst+1,rr[tot]=n,typ[tot]=0;
		for(int i=1;i<=tot;i++)
			ans+=rr[i]-ll[i],dsu[i]=i;
		int cnt=0;
		while(cnt<tot-1){
			for(int i=1;i<=tot;i++)
				if(dsu[i]==i)
					mn[i]=2e9,rec[i]=-1;
			for(int i=1;i<=tot;i++)
				if(typ[i]){
					int x=typ[i];
					for(int j=0;j<v[x].size();j++){
						int k=v[x][j],y=id[xx[k]+yy[k]-x];
						if(find(y)!=find(i)&&mn[find(i)]>zz[k])
							mn[find(i)]=zz[k],rec[find(i)]=find(y);
					}
				}
			pre[1]=0;
			for(int i=2;i<=tot;i++){
				if(find(i-1)==find(i))
					pre[i]=pre[i-1];
				else pre[i]=i-1;
			}
			suf[tot]=tot+1;
			for(int i=tot-1;i>=1;i--){
				if(find(i+1)==find(i))
					suf[i]=suf[i+1];
				else suf[i]=i+1;
			}
			for(int i=1;i<=tot;i++){
				stp++;
				if(typ[i]){
					int x=typ[i];
					for(int j=0;j<v[x].size();j++){
						int k=v[x][j];
						vis[id[xx[k]+yy[k]-x]]=stp;
					}
				}
				int j=i;
				while(j){
					if(find(j)==find(i))
						j=pre[j];
					else if(vis[j]==stp)
						j--;
					else{
						int c=ll[i]-rr[j];
						if(mn[find(i)]>c)
							mn[find(i)]=c,rec[find(i)]=find(j);
						break;
					}
				}
				j=i;
				while(j<=tot){
					if(find(j)==find(i))
						j=suf[j];
					else if(vis[j]==stp)
						j++;
					else{
						int c=ll[j]-rr[i];
						if(mn[find(i)]>c)
							mn[find(i)]=c,rec[find(i)]=find(j);
						break;
					}
				}
			}
			for(int i=1;i<=tot;i++)
				if(dsu[i]==i&&rec[i]!=-1&&i!=find(rec[i]))
					cnt++,ans+=mn[i],dsu[i]=find(rec[i]);
		}
		printf("%lld\n",ans);
		for(int i=1;i<=tot;i++)
			v[i].clear();
	}
	return 0;
}
```

---

