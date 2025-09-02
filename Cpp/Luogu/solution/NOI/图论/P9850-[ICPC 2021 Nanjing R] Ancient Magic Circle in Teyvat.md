# [ICPC 2021 Nanjing R] Ancient Magic Circle in Teyvat

## 题目描述

占星师 Mona Megistus 最近在 Teyvat 发现了一个古老的魔法阵。

![](https://cdn.luogu.com.cn/upload/image_hosting/gohzab6t.png)

这个魔法阵看起来像一个有 $n$ 个顶点的完全图，其中 $m$ 条边被染成红色，其他边被染成蓝色。注意，完全图是一个简单的无向图，其中每一对不同的顶点之间都由一条唯一的边连接。

Mona 意识到，如果她选择四个不同的顶点，使得这四个顶点之间的六条边颜色相同，她将从魔法阵中获得一个“钥匙”。如果颜色是红色，她将获得一个“红色钥匙”；如果颜色是蓝色，她将获得一个“蓝色钥匙”。

根据 Mona 阅读的古书中写的信息，古老魔法阵的魔力是她可以从魔法阵中获得的“红色钥匙”和“蓝色钥匙”数量的绝对差。

Mona 非常需要你的帮助，因为计算魔法阵的魔力实在是一项艰巨的工作。

## 说明/提示

对于示例情况，古老魔法阵中只有一个“红色钥匙” $(1,2,3,4)$，而有四个“蓝色钥匙” $(1,5,6,7)$、$(2,5,6,7)$、$(3,5,6,7)$ 和 $(4,5,6,7)$，因此魔法阵的魔力是 $|1-4|=3$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
3
```

# 题解

## 作者：Arghariza (赞：6)

考虑容斥掉蓝色完全子图。令 $f_i(0\le i\le 6)$ 为硬点有 $i$ 条红边的方案数（即有 $j$ 条红边的子图贡献为 $\dbinom{j}{i}$），$g_i$ 为恰有 $i$ 条红边的方案数。

$$f_i=\sum\limits_{j=i}\dbinom{j}{i}g_j\iff g_i=\sum\limits_{j=i}\dbinom{j}{i}(-1)^{j-i}f_j$$

考虑我们要求 $|g_0-g_6|=|f_0-f_1+f_2-f_3+f_4-f_5|$。

然后画图发现每种情况都是可以算的，分类讨论即可：

- $f_0$：即 $\dbinom{n}{4}$。
- $f_1$：$m\dbinom{n-2}{2}$。
- $f_2$：$(n-3)\sum\limits_{i}\dbinom{d_i}{2}+\dbinom{m}{2}-\sum\limits_{i}\dbinom{d_i}{2}$，$d_i$ 为 $i$ 的度数。
- $f_3$：$(n-3)c_3+\sum\limits_{i}\dbinom{d_i}{3}+\sum\limits_{(u,v)\in E}(d_u-1)(d_v-1)-3c_3$，$c_3$ 为三元环个数。
- $f_4$：$\sum\limits_{i}ct_i(d_i-2)+c_4$，$ct_i$ 为以 $i$ 为顶点的三元环数，$c_4$ 为四元环数。
- $f_5$：$\sum\limits_{(u,v)\in E}\dbinom{cnt_{u,v}}{2}$，$cnt_{u,v}$ 为包含 $(u,v)$ 边的三元环数。

复杂度 $O(m\sqrt m)$，瓶颈在三元环/四元环计数。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

const int N = 1e5 + 100;
const int M = 2e5 + 200;

int n, m, l3, c3, c4;
int op[10], d[N], ct[N], cte[M], vs[N];
vector<pi> g[N], h[N];

void solve() {
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) 
        cin >> u >> v, g[u].eb(v, i), g[v].eb(u, i), d[u]++, d[v]++;
    for (int u = 1; u <= n; u++) {
        for (pi p : g[u]) {
            int v = p.fi, w = p.se;
            if (d[u] > d[v] || (d[u] == d[v] && u > v)) h[u].eb(v, w);
        }
    }
    for (int u = 1; u <= n; u++) {
        for (pi p : h[u]) {
            int v = p.fi;
            for (pi q : g[v]) {
                int w = q.fi;
                if (d[u] < d[w] || (d[u] == d[w] && u <= w)) continue;
                c4 += (ct[w]++);
            }
        }
        for (pi p : h[u]) 
            for (pi q : g[p.fi]) ct[q.fi] = 0;
    }
    for (int u = 1; u <= n; u++) {
        for (pi p : h[u]) vs[p.fi] = p.se;
        for (pi p : h[u]) {
            int v = p.fi, i = p.se;
            for (pi q : h[v]) {
                int w = q.fi, j = q.se;
                if (!vs[w]) continue;
                c3++, ct[u]++, ct[v]++, ct[w]++;
                cte[i]++, cte[j]++, cte[vs[w]]++;
            }
        }
        for (pi p : h[u]) vs[p.fi] = 0;
    }
    for (int i = 1; i <= n; i++)
        l3 += d[i] * (d[i] - 1) / 2;
    op[0] = (__int128)n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4;
    op[1] = m * (n - 2) * (n - 3) / 2;
    op[2] = (n - 3) * l3 + m * (m - 1) / 2 - l3;
    op[3] = (n - 3) * c3;
    for (int i = 1; i <= n; i++) op[3] += d[i] * (d[i] - 1) * (d[i] - 2) / 6;
    for (int i = 1; i <= n; i++) {
        for (pi p : g[i]) {
            int j = p.fi;
            if (i < j) op[3] += (d[i] - 1) * (d[j] - 1);
        }
    }
    op[3] -= 3 * c3;
    op[4] = c4;
    for (int i = 1; i <= n; i++) op[4] += ct[i] * (d[i] - 2);
    for (int i = 1; i <= n; i++) {
        for (pi p : g[i]) {
            int j = p.fi;
            if (i < j) op[5] += cte[p.se] * (cte[p.se] - 1) / 2;
        }
    }
    cout << abs(op[0] - op[1] + op[2] - op[3] + op[4] - op[5]) << '\n';
}

bool Med;
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：JustPureH2O (赞：4)

[更好的阅读体验](https://justpureh2o.cn/articles/9850)

题目地址：[P9850](https://www.luogu.com.cn/problem/P9850)

> 给定一个 $n$ 个点的完全图，有 $m$ 条边是红色的，其余边是蓝色的，求出边均为蓝色的大小为 $4$ 的完全子图个数与边均为红色的大小为 $4$ 的完全子图个数的差。
> 
> 对所有数据满足，${4\le n\le 10^5}$，${0\le m\le \min(\frac{n(n-1)}{2},2\times 10^5)}$

注意到 $n$ 的量级是 ${10^5}$ 的，因此不能直接建完全图，考虑把蓝色图用红色图表示出来。假设存在 $f_i$ 个有 $i$ 条边的红色子图，那么对于一张存在 $j$ 条红色边的图，就能有 $\binom{j}{i}$ 种选择方法；此时再令 $g_i$ 表示大小为 ${4}$ 且存在 $i$ 条红色边的完全子图个数，因此有下式：

$$
f_i=\sum\limits_{j=i}\binom{j}{i}g_j
$$

对上面的式子使用二项式反演得：

$$
g_i=\sum\limits_{j=i}\binom{j}{i}(-1)^{j-i}f_j
$$

那么求蓝色完全子图和红色完全子图的差就可以用 $|g_0-g_6|=|\sum\limits_{i=0}^5(-1)^if_i|=|f_0-f_1+f_2-f_3+f_4-f_5|$ 得到，接下来对每个 $f_i$ 进行分类讨论：

1. $i=0$ 时，即没有选定的红色边。此时随便选择四个点组成图，即 $f_0=\binom{n}{4}$。
2. $i=1$ 时，需选定一条红色边。选边方案数是 $\binom{m}{1}$，此时确定下两个端点，那么在剩下的 $n-2$ 个点里选择两个点，即 $f_1=\binom{m}{1}\binom{n-2}{2}$。
3. $i=2$ 时，分两类考虑：
   
   * 两条线有公共端点：首先枚举这个公共点，再枚举两条以该点为端点的线段，最后选剩下的那个点。此时方案数为 $(n-3)\sum\limits_{u=1}^n\binom{d_u}{2}$，其中 $d_u$ 为原无向图中点 $u$ 的度数。
   * 两条线无公共端点：正难则反，将原图中任意选两条边的方案数减去两条线有公共端点的方案数即得两条线无公共端点的方案数。也就是 $\binom{m}{2}-\sum\limits_{u=1}^n\binom{d_u}{2}$。
   * 两情况求和得：$f_2=\binom{m}{2}+(n-4)\sum\limits_{u=1}^{n}\binom{d_u}{2}$。
4. $i=3$ 时，继续分类讨论：
   
   * 三条边组成一个三元环，再枚举剩下的一个点，结果为 $(n-3)C_3$。
   * 三条边共用一个顶点，枚举这个顶点，选择直连边中的三条即可涵盖四个点，即 $\sum\limits_{u=1}^n\binom{n}{3}$。
   * 三条边形成链状结构。选择一条边，该边的两个端点分别支出去一条边，刚好覆盖满四个点。注意把成环情况舍去，同一个三元环会算三次，最终需减去 ${3}C_3$。结果为：$-3C_3+\sum\limits_{(u,v)\in E}(d_u-1)(d_v-1)$。
   * 综上，$f_3=(n-6)C_3+\sum\limits_{(u,v)\in E}(d_u-1)(d_v-1)$。
5. $i=4$ 时，分两类讨论：
   
   * 四条边组成一个四元环，四个点恰好均被覆盖，无需多余枚举，结果为 $C_4$。
   * 三元环的某个顶点支出去一条边，枚举这个端点。结果为 $\sum\limits_{u=1}^ns_u(d_u-2)$，其中 $s_u$ 为经过点 $u$ 的不同三元环个数。
   * 综上，$f_4=C_4+\sum\limits_{u=1}^ns_u(d_u-2)$。
6. $i=5$ 时，只有一种情况，那就是两个三元环共用一条边。此时只需枚举这个公共边即可，即 $f_5=\sum\limits_{i\in\mathbb C_3}\binom{t_i}{2}$，其中 $\mathbb C_3$ 表示求解三元环时完成定向的边集，$t_i$ 表示覆盖到边 $i$ 的不同三元环个数。

最后套公式计算即可，注意加上绝对值，建图用前向星会超时。

```cpp
#include <bits/stdc++.h>

#define N 100010
#define M 200010
using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

vector<PII> E[N];
vector<int> G[N];
int u[N << 1], v[N << 1];
ll deg[N << 1];
ll cnt[N << 1];
ll containerP[N], containerE[M]; // 分别为公式中的 s 和 t
int tmp[N], id[N];
ll n, m;

ll countTripling() {
    // 三元环计数
    ll ret = 0;
    for (int i = 1; i <= n; i++) {
        for (auto j: E[i]) id[j.first] = j.second;
        for (auto j: E[i]) {
            int k = j.first;
            for (auto l: E[k]) {
                int w = l.first;
                if (id[w]) {
                    // 维护当前的三元环经过哪些点和哪些边
                    containerP[i]++;
                    containerP[k]++;
                    containerP[w]++;
                    containerE[j.second]++;
                    containerE[l.second]++;
                    containerE[id[w]]++;
                    ret++;
                }
            }
        }
        for (auto j: E[i]) id[j.first] = 0;
    }
    return ret;
}

ll countQuadrant() {
    // 四元环计数
    for (int i = 1; i <= m; i++) {
        // 为边定向，求三元环时也要用到这张图
        // 规定度数小的指向度数大的，度数相同则让编号小的指向编号大的
        if ((deg[u[i]] == deg[v[i]] && u[i] > v[i]) || deg[u[i]] > deg[v[i]]) swap(u[i], v[i]);
        E[u[i]].emplace_back(v[i], i);
    }
    ll ret = 0;
    int hh = 0;
    for (int i = 1; i <= n; i++) {
        for (int j: G[i]) {
            for (auto k: E[j]) {
                int w = k.first;
                if (deg[i] < deg[w] || (deg[i] == deg[w] && i < w)) {
                    ret += cnt[w];
                    if (!cnt[w]) tmp[hh++] = w;
                    cnt[w]++;
                }
            }
        }
        for (int j = 0; j < hh; j++) cnt[tmp[j]] = 0;
        hh = 0;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
        deg[u[i]]++;
        deg[v[i]]++;
        G[u[i]].push_back(v[i]);
        G[v[i]].push_back(u[i]);
    }
    ll quad = countQuadrant();
    ll trip = countTripling();
    ll f0, f1, f2 = 0, f3 = 0, f4 = 0, f5 = 0;
    for (int i = 1; i <= n; i++) {
        f2 += deg[i] * (deg[i] - 1) / 2 * (n - 4);
        f3 += deg[i] * (deg[i] - 1) * (deg[i] - 2) / 6;
        f4 += containerP[i] * (deg[i] - 2);
        for (auto j: E[i]) {
            int k = j.first;
            f3 += (deg[i] - 1) * (deg[k] - 1);
        }
    }
    for (int i = 1; i <= m; i++) {
        f5 += containerE[i] * (containerE[i] - 1) / 2;
    }
    f0 = (__int128) n * (n - 1) * (n - 2) * (n - 3) / 24; // 注意连乘爆 long long
    f1 = m * (n - 2) * (n - 3) / 2;
    f2 += m * (m - 1) / 2;
    f3 += trip * (n - 6);
    f4 += quad;
    cout << abs(f0 - f1 + f2 - f3 + f4 - f5);
    return 0;
}
```

$\texttt{The End}$

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P9850)

**题目大意**

> 给定 $n$ 个点 $m$ 条边的无向图，求 $K_4$ 子图个数与四元独立集子图个数之差。
>
> 数据范围：$n\le 10^5,m\le 2\times 10^5$。

**思路分析**

考虑二项式反演，设 $f_i$ 表示钦定 $i$ 条边的四元子图数量，答案就是 $|f_0-f_1+f_2-f_3+f_4-f_5|$。

对 $f_0\sim f_5$ 分别计算：

- $f_0$：任选四个点都满足：$\dfrac{n(n-1)(n-2)(n-3)}{24}$。
- $f_1$：任选一条边并另选两个点：$m\times \dfrac{n(n-1)}2$。
- $f_2$：分讨选的两条边的形态：

  - 如果有公共顶点，那么枚举顶点并选剩下的一个点： $(n-3)\sum_u\dfrac{d_u(d_u-1)}2$，其中 $d_u$ 表示度数。
  - 如果没有公共顶点，任选两条边，容斥掉有公共顶点的情况：$\dfrac{m(m-1)}2-\sum_u\dfrac{d_u(d_u-1)}2$。
- $f_3$：分讨选的三条边的形态：
  - 如果三条边有公共顶点，枚举顶点：$\sum_u\dfrac{d_u(d_u-1)(d_u-2)}6$。
  - 如果是三元环，答案就是图中三元环个数 $c_3$ 乘以 $(n-3)$。
  - 如果是链，枚举中间的一条边，但我们要求另外两条边的另一个端点不重合，如果重合了就形成了三元环，且一个三元环被算三次：$\sum_{(u,v)\in E}(d_u-1)(d_v-1)-3c_3$。

- $f_4$：分讨选的四条边的形态：
  - 如果是四元环，答案就是图中四元环个数 $c_4$。
  - 如果是三元环外挂一条边，枚举外挂边的节点，答案就是：$\sum c_u(d_u-2)$，其中 $c_u$ 表示覆盖 $u$ 的三元环个数。

- $f_5$：此时只能是两个三元环公用一条边：$\sum_e \dfrac{c_e(c_e-1)}2$，其中 $c_e$ 表示过 $e$ 这条边的三元环个数。

容易发现 $c_3,c_4,c_u,c_e$ 都是好求的。

时间复杂度 $\mathcal O(m\sqrt m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
const int MAXN=1e5+5;
struct Edge { int v,id; };
vector <Edge> G[MAXN],E[MAXN];
int n,m,deg[MAXN],f[MAXN];
ll c3=0,c4=0,cv[MAXN],ce[MAXN*2];
bool cmp(int x,int y) { return deg[x]<deg[y]||(deg[x]==deg[y]&&x<y); }
ll f0,f1,f2,f3,f4,f5;
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i) {
		scanf("%d%d",&u,&v),G[u].push_back({v,i}),G[v].push_back({u,i});
		++deg[u],++deg[v];
	}
	for(int u=1;u<=n;++u) for(auto e:G[u]) if(cmp(u,e.v)) E[u].push_back(e);
	for(int u=1;u<=n;++u) {
		for(auto i:G[u]) for(auto j:E[i.v]) if(cmp(u,j.v)) c4+=f[j.v]++;
		for(auto i:G[u]) for(auto j:E[i.v]) f[j.v]=0;
	}
	for(int u=1;u<=n;++u) {
		for(auto i:E[u]) f[i.v]=i.id;
		for(auto i:E[u]) for(auto j:E[i.v]) if(f[j.v]) {
			++c3,++cv[u],++cv[i.v],++cv[j.v];
			++ce[i.id],++ce[j.id],++ce[f[j.v]];
		}
		for(auto i:E[u]) f[i.v]=0;
	}
	f0=(__int128)n*(n-1)*(n-2)*(n-3)/24;
	f1=1ll*m*(n-2)*(n-3)/2;
	f2=1ll*m*(m-1)/2;
	for(int i=1;i<=n;++i) f2+=1ll*deg[i]*(deg[i]-1)/2*(n-3-1);
	f3=c3*(n-3-3);
	for(int u=1;u<=n;++u) f3+=1ll*deg[u]*(deg[u]-1)*(deg[u]-2)/6;
	for(int u=1;u<=n;++u) for(auto e:E[u]) f3+=1ll*(deg[u]-1)*(deg[e.v]-1);
	f4=c4;
	for(int u=1;u<=n;++u) f4+=(deg[u]-2)*cv[u];
	for(int i=1;i<=m;++i) f5+=ce[i]*(ce[i]-1)/2;
	ll ans=f0-f1+f2-f3+f4-f5;
	printf("%lld\n",ans<0?-ans:ans);
	return 0;
}
```

---

## 作者：PosVII (赞：2)

**前言**

------------

偶不，居然不是第一个写题解的。

分讨，容斥，三/四元环计数。

**思路**

------------

直接求完全子图计数是困难的，考虑容斥。

设 $f_{i}$ 表示图中边数为 $i$ 的四元子图数量（点有序，不一定要取这四个点之间所有的边）。

那么蓝色四元完全子图的数量为 $f_{0}-f_{1}+f_{2}-f_{3}+f_{4}-f_{5}+f_{6}$，红色四元完全子图的数量为 $f_{6}$，作差得 $ans=f_{0}-f_{1}+f_{2}-f_{3}+f_{4}-f_{5}$。

可以对于不同的子图形状进行分类讨论，总共有 $10$ 种情况，分别是各种菊花以及三\四元环计数和它们的变形。

![](https://cdn.luogu.com.cn/upload/image_hosting/n59uqjdw.png)

除了情况⑥和情况⑧都是平凡的，所以不讨论。

对于情况⑥，可以视为三元环再加一条额外的出边。

对于情况⑧，可以视为两个共边的三元环。

记得求绝对值！

**code**

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename G> inline void read(G&x) {x=0;G f=1;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') {x=x*10+(ch^48);ch=getchar();}x*=f;}
const int MAXN=2e5+5;
#define int long long
int n,m,ans,vis[MAXN],num[MAXN],tot,cnt[MAXN],deg[MAXN];
vector<pair<int,int> > G[MAXN];
vector<int> E[MAXN];
int u[MAXN],v[MAXN];
signed main() {
	read(n),read(m);
	ans=1ull*n*(n-1)*(n-2)/6*(n-3)/4;//0
	ans-=m*(n-2)*(n-3)/2;//1
	for(int i=1;i<=m;++i) {
		read(u[i]),read(v[i]);
		E[u[i]].emplace_back(v[i]);
		E[v[i]].emplace_back(u[i]);
		if(u[i]>v[i]) swap(u[i],v[i]);
		ans+=i-deg[u[i]]-deg[v[i]]-1;//2
		ans+=(deg[u[i]]+deg[v[i]])*(n-3);//3
		ans-=(deg[u[i]]*(deg[u[i]]-1)+deg[v[i]]*(deg[v[i]]-1))/2;//5
		++deg[u[i]],++deg[v[i]];
	}
	for(int i=1;i<=m;++i) {
		ans-=(deg[u[i]]-1)*(deg[v[i]]-1);//4
		if(deg[u[i]]<deg[v[i]]) swap(u[i],v[i]);
		G[u[i]].emplace_back(make_pair(v[i],++tot)); 
	}
	for(int i=1;i<=n;++i) {
		for(auto p1:G[i]) {
			int j=p1.first;
			for(auto k:E[j]) {
				if(deg[i]<deg[k]||(deg[i]==deg[k]&&i>=k)) continue; 
				ans+=cnt[k]++;//7
			}
		}
		for(auto p1:G[i]) {
			int j=p1.first;
			for(auto k:E[j]) {
				cnt[k]=0;
			}
		}
	}
	for(int i=1;i<=n;++i) {
		for(auto pii:G[i]) vis[pii.first]=pii.second;
		for(auto p1:G[i]) {
			int j=p1.first,jj=p1.second;
			for(auto p2:G[j]) {
				int k=p2.first,kk=p2.second;
				if(vis[k]) {
					ans-=(n-3);//9
					ans+=3;//4
					ans+=(deg[i]+deg[j]+deg[k]-6);//6
					ans-=num[jj]++;//8
					ans-=num[kk]++;//8
					ans-=num[vis[k]]++;//8
				}
			}
		}
		for(auto pii:G[i]) vis[pii.first]=0;
	}
	printf("%lld",labs(ans));
	return 0; 
}
```

---

