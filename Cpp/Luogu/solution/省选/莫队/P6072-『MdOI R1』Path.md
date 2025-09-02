# 『MdOI R1』Path

## 题目描述

给定一棵 $n$ 个点的无根树，边有边权。

令 $V(x,y),E(x,y)$ 分别表示树上 $x,y$ 之间的简单路径上的所有点的集合和所有边的集合，特别地，当 $x=y$ 时，$V(x,y) = \{x\}$，$E(x,y) = \varnothing$。

再令边集 $E$ 的权值 $f(E)$ 为 $E$ 中所有边的权值的 **异或和**，当 $E = \varnothing$ 时，$f(E) = 0$。

现在，要你求出
$$
\max_{1\le x,y,u,v \le n,V(x,y)\cap V(u,v) = \varnothing}(f(E(x,y)) + f(E(u,v)))
$$
通俗的讲，你要选择两条简单路径，满足没有重合的点，且边权异或和之和最大。

## 说明/提示

【样例 1 解释】

样例中的树如图所示，选择标红色和蓝色的两条路径，满足没有重合的点，且边权异或和之和最大，为 $(7\oplus 1\oplus 8)+(5\oplus 2)=21$（其中 $\oplus$ 表示异或运算）。

![](https://cdn.luogu.com.cn/upload/image_hosting/jen9sxcf.png)

【样例 2 解释】

样例中的树如图所示，为一条链的形状，选择标红色和蓝色的两条路径，蓝色路径退化成了一个点，使异或和之和达到最大值 $2+0=2$。注意红色路径并不能延申到 $3$，否则蓝色路径将无法存在。

![](https://cdn.luogu.com.cn/upload/image_hosting/1xzo1lh2.png)

---

【数据范围】

**本题采用捆绑测试。**

| 子任务编号 |    $n\leq$     |  特殊性质   | 分值 | 时限 |
| :--------: | :------------: | :---------: | :--: | :--: |
|     1      |      $50$      |     无      |  12  |  1s  |
|     2      | $2\times 10^3$ |     无      |  28  |  2s  |
|     3      | $2\times 10^4$ | $y = x + 1$ |  20  |  3s  |
|     4      | $3\times 10^4$ |     无      |  40  | 3.5s |

对于 $100\%$ 的数据，$2\leq n\leq 3\times 10^4$，$1\leq x,y\leq n$，$0\leq w\leq 10^9$。

## 样例 #1

### 输入

```
9
1 2 1
1 3 7
2 4 8
3 5 3
4 6 3
3 7 3
7 8 5
7 9 2
```

### 输出

```
21
```

## 样例 #2

### 输入

```
3
1 2 2
2 3 1
```

### 输出

```
2
```

# 题解

## 作者：CTime_Pup_314 (赞：25)

补充一下这道题的 $O(n\log n\log\max w)$ 的做法，我们以 $1$ 为根，定义 $a_x$ 为从 $x$ 到 $1$ 边权的异或值，$in_x$ 和 $out_x$ 为 $x$ 子树内部和外部选择 $u$ 和 $v$ 中 $a_u\oplus a_v$ 的最大值，那么最后答案显然为 $\max_{x\ne1}\{in_x+out_x\}$。

对于求 $in_x$ 我们有很多做法，例如启发式合并，dsu on tree，或者可持久化 trie，需要 $O(n\log n\log\max w)$ 的时间。

对于求 $out_x$，我们不妨先找到任意两个点 $p$ 和 $q$，使得 $a_p\oplus a_q$ 最大，这时不以这个点对为最大值的只有 $p$ 到根上的所有点，和 $q$ 到根上的所有点。考虑我们只求树上一条链 $out_x$，加入我们按照顺序遍历 到 $x$，只需要将 $x$ 父亲的子树内除去 $x$ 子树部分加入 trie 即可。这一部分复杂度 $O(n\log \max w)$。

通过代码

```cpp
const int N = 3e4+5, L = 128, S = 1<<7; int SZ;
int n, maxl, p, q, ch[N*L][2], t[N*L], fa[N], tot, tg[N], bel[N], out[N], in[N], a[N], A, B, o[N], rk[N], ans; vector<int> v[N]; vector<pii> e[N]; 
int l2(int x) { return x == 0?-1:l2(x>>1)+1; }
void ins(int &o, int v)
{
    if(!o) o = ++tot; ++t[o];
	for(int i = maxl, x = o; ~i; --i)
	{
		bool d = v>>i&1; if(!ch[x][d]) ch[x][d] = ++tot;
		x = ch[x][d], ++t[x];
	}
}
void cls() { memset(t+1, 0, sizeof(int)*tot); }
int ask(int o, int v)
{
	int ret = 0; 
	for(int i = maxl, x = o; ~i; --i)
	{
		bool d = ~v>>i&1;
		if(t[ch[x][d]]) x = ch[x][d], ret |= 1ll<<i;
		else x = ch[x][d^1];
	}	
	return ret;
}
void mg(int x, int p, int z, int i, int &v)
{
    if(!x) return; if(!~i) return v = max(v, ask(o[p], z)), ins(o[p], z);
    mg(ch[x][0], p, z, i-1, v), mg(ch[x][1], p, z|1<<i, i-1, v);
}
void dfs(int x)
{
    static int _t; rk[++_t] = x, in[x] = 0; ins(o[x], a[x]);
    for(pii u:e[x]) 
    {
        int y = u.fi; if(y == fa[x]) continue;
        fa[y] = x, a[y] = a[x]^u.se, dfs(y); if(t[o[x]] < t[o[y]]) swap(o[x], o[y]);;
        mg(o[y], x, 0, maxl, in[x]), in[x] = max(in[x], in[y]);
    }
}
void sol(int p)
{
	cls(); for(int x = p; x; x = fa[x]) tg[x] = 1; int now = 0;
	for(int k = 1, i; k <= n; v[i].clear(), v[bel[i]].pb(a[i]), ++k) 
		if(tg[i = rk[k]]) bel[i] = i; else bel[i] = bel[fa[i]];
	for(int k = 1, i; k <= n; ++k) if(tg[i = rk[k]])
	{
		for(int w:v[fa[i]]) now = max(now, ask(o[0], w)), ins(o[0], w);
		out[i] = max(out[i], now), tg[i] = 0;
	}
}
int main()
{
	rd(n); for(int i = 1, x, y, z; i < n; ++i) 
        rd(x), rd(y), rd(z), maxl = max(maxl, l2(z)), e[x].pb(pii(y, z)), e[y].pb(pii(x, z));
    dfs(1), cls();
	for(int i = 1; i <= n; ++i) 
	{
		int v = ask(o[0], a[i]); ins(o[0], a[i]), out[i] = -1;
		if((A^B) < v) A = a[i], B = v^A, p = i;
	}
	for(int i = 1; i <= n; ++i) if(a[i] == B) q = i;
	sol(p), sol(q); for(int i = 1; i <= n; ++i) if(!~out[i]) out[i] = A^B;
    for(int i = 2; i <= n; ++i) ans = max(ans, in[i]+out[i]);
    print(ans);
	return 0;
}
```


---

## 作者：violin_wyl (赞：18)

## P6072 『MdOI R1』Path

#### 思路

这里写一个单 log 的做法。

这里受Ynoi的启发（别问哪道），我们考虑找到一个分割边使得分成的两棵树的路径边权异或和的和最大，因为异或的特殊性质（两个异或等于0），我们对一条简单路径差分，并记录每个点到根节点到异或和，这样即把边权问题变成点权问题，而询问一条路径就是  $\mathcal O(1)$ 的，这样时间复杂度变成  $\mathcal O (n^5)$。

然后我们找到任意一对全局的异或和最大的点对 $(X,Y)$，这部分可以用0-1Trie解决，那么只要分割边不在这条全局异或和最大的路径上，那么就一定有一棵子树完全包括这条路径，这样我们只需要枚举另一棵子树即可，这部分时间复杂度 $O(n^3)$。

接下来我们弱化一下问题，我们在断边之后的图实际上是求一棵子树内的异或最大值加一棵子树外的异或最大值，我们先考虑子树外的异或最大值。

我们考虑最开始找到的点对 $(X,Y)$ ，那么这个点对不在子树外当且仅当枚举的分割边在 $X \rightarrow RT$  的路径上或在 $Y \rightarrow RT$  的路径上 （$RT$ 即代表根），如果我们从根节点逐渐往下跳，那实际上在子树外的点是在**逐渐增加的**，也就是说原来在子树外的节点**一定一直在**子树外，原先加入0-1Trie的节点并不用删除，这样我们即可 $O(n \log w)$ 求出每条边子树外的最大异或和了。

至于子树内的异或最大值可以用带有双 $\log$ 的启发式合并（~~那我们上面写了半天的单log不就没用了？~~）,其实我们没有必要求出每条边对应的子树内的值，因为子树外的最大值已经固定了，我们只需要最大化子树内的值即可，那如果我们一棵子树内的节点越多也就意味着答案可能更大，所以我们考虑找到与链 $X\rightarrow Y$ 和链 $Lca(X,Y)\rightarrow RT$ 的所有相邻的子树的异或最大值即可，这些子树的交集一定为空，我们就把原先每个点都需要加入 $\log$ 次0-1Trie优化成只加入一次，处理子树内的时间复杂度优化为 $O(n \log w)$ （常数就看你写的丑不丑了）。

最后一种情况，即分割边在路径 $X\rightarrow Y$ 上，其中子树外的情况我们已经考虑完了，而子树内的则可以从下往上跳，那不难发现，子树内的节点个树仍然**单调递增**，我们分别从 $X$，$Y$ 各往上跳一次，即可求出整个图的子树外以及子树内的异或和的最大值了。

我们最后分析一波时间复杂度，总时间复杂度为 $\mathcal O(n \log w)$，而数据出到了 $3\times10^4$ 所以 $\log n$ 所带来的常数不明显（大概14多一点样子，实际上会小一些），而这种方法一个点进0-1Trie的次数仍然带来一个巨大的常数，不过仍然跑的飞快～

------

#### code

~~我认为这码风还是很可读的~~

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 3e4 + 10;
const int M = 1e6 + 10;
const int mods = 1e9 + 7;
const int INF = 0x3f3f3f3f;
inline int read ( )
{
    int x = 0, f = 1;
    char ch = getchar ( );
    while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
    while (ch >= '0' && ch <='9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int n, root = 1;
struct edge {
    int ver, nxt, val;
}e[N << 1];
int head[N], tot;
void add_edge (int u, int v, int w) { e[++tot] = (edge) {v, head[u], w}; head[u] = tot;}
int mx, x1, x2;
struct Trie {
    int ch[M][2], val[M], pos[M], cnt;
    void init ()
    {
        for (int i = 1; i <= cnt; i++) ch[i][0] = ch[i][1] = 0; // 注意这里不要直接memset
        cnt = 1;
    }
    void find (int x, int Pos)
    {
        int p = 1, res = 0;
        for (int i = 31; i >= 0; i--) { bool d = (x >> i) & 1; if (ch[p][d ^ 1]) p = ch[p][d ^ 1], res += (1 << i); else p = ch[p][d]; }
        if (mx < res) mx = res, x1 = pos[p], x2 = Pos;
    }
    void insert(int x, int Pos)
    {
        int p = 1;
        for(int i = 31; i >= 0; i--) { bool d = (x >> i) & 1; if(!ch[p][d]) ch[p][d] = ++cnt; p = ch[p][d]; }
        pos[p] = Pos, val[p] = x;
    }
}tree1, tree2;
int val[N], fa[N], son[N];
int f1[N], lca; // f1 数组即表示子树外的最大异或值
int ans, ans1;
void dfs1 (int u, int f, int x)
{
    fa[u] = f; val[u] = x;
    for (int i = head[u]; i; i = e[i].nxt)
        if (e[i].ver != f)
            dfs1 (e[i].ver, u, x ^ e[i].val);
}
void dfs2 (int u, int f)
{
    tree2.insert (val[u], u); tree2.find (val[u], u);
    for (int i = head[u]; i; i = e[i].nxt)
        if (e[i].ver != f)
            dfs2 (e[i].ver, u);
}
bool vis[N];
int getlca (int x, int y) // 就找一次所以没写倍增
{
    while (x) vis[x] = true, x = fa[x];
    while (!vis[y]) vis[y] = true, y = fa[y];
    return y;
}
void solve (int x) // 先处理子树外的最大异或值
{
    int now = x;
    while (now != root) son[fa[now]] = now, now = fa[now];
    now = root; mx = 0;
    while (now)
    {
        f1[now] = mx; tree2.insert (val[now], now); tree2.find (val[now], now);
        for (int i = head[now]; i; i = e[i].nxt)
            if (e[i].ver != son[now] && e[i].ver != fa[now]) dfs2 (e[i].ver, now);
        now = son[now];
    }
}
void solve2 (int x) // 路径 x -> y 在子树外
{
    int now = x;
    while (now)
    {
        for (int i = head[now]; i; i = e[i].nxt)
            if (!vis[e[i].ver] && e[i].ver != fa[now])
            {
                tree2.init (); mx = 0; // 注意这里清空的均摊复杂度是 O(n) 的
                dfs2 (e[i].ver, now);
                ans = max (ans, mx + ans1);
            }
        now = fa[now];
    }
}
void solve3 (int x) // 分割边在路径上
{
    int now = x; mx = 0;
    tree2.init ();
    while (now != lca)
    {
        tree2.insert (val[now], now); tree2.find (val[now], now);
        for (int i = head[now]; i; i = e[i].nxt)
            if (!vis[e[i].ver] && e[i].ver != fa[now]) dfs2 (e[i].ver, now);
        ans = max (ans, f1[now] + mx);
        now = fa[now];
    }
}
signed main()
{
    n = read ( );
    for (int i = 1, u, v, w; i < n; i++)
    {
        u = read ( ), v = read ( ), w = read ( );
        add_edge (u, v, w); add_edge (v, u, w);
    }
    dfs1 (1, 0, 0); mx = 0;
    tree1.cnt = 1;
    for (int i = 1; i <= n; i++) tree1.insert (val[i], i), tree1.find (val[i], i);
    for (int i = 1; i <= n; i++) f1[i] = mx;
    int x = x1, y = x2; ans1 = mx; lca = getlca (x, y);
    tree2.cnt = 1; solve (x); tree2.init (); solve (y);
    ans = max (ans, f1[lca] + (lca == root ? 0 : ans1));
  	// 路径 x -> y 在子树内，根据贪心直接找lca即可
  	// 注意需要把 lca 为根的情况特判掉
    solve2 (x); solve2 (y);
    solve3 (x); solve3 (y);
    printf ("%d\n", ans);
    return 0;
} // The Dark Emperor
```

---

## 作者：ix35 (赞：13)

## $\mathrm{[MdOI2020]\ T5\ Path}\ $ 题解

upd. 有 poly log 的做法，希望会的神仙写一写...

---

[原题链接](https://www.luogu.com.cn/problem/T115029)

------

#### 算法 $1$：（$Subtask\ 1$，枚举）

首先一次 DFS 计算出 $dist[i]$ 表示 $i$ 到 $1$ 的路径上所有边的权值异或和。则如果选择了 $a\to b,\ \ c\to d$ 两条路径，则要求的答案为 $\max (dist[a]\oplus dist[b]+dist[c]\oplus dist[d])$。

计算答案时，直接枚举选择的两条路径的四个端点 $a,b,c,d$，首先判断是否相交，若不相交再更新答案，判断相交的时候可以暴力跳，也可以用结论。

时间复杂度为 $O(n^5)$，可以解决 $n\leq 50$ 的部分分。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,ans,x,y,z,eg,hd[MAXN],ver[2*MAXN],nx[2*MAXN],edge[2*MAXN],vis[2][MAXN],dis[MAXN],f[MAXN];
void add_edge (int x,int y,int z) {
	ver[++eg]=y;
	nx[eg]=hd[x],edge[eg]=z;
	hd[x]=eg;
	return;
}
void dfs (int x,int fa) {
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dis[ver[i]]=dis[x]^edge[i],f[ver[i]]=x;
		dfs(ver[i],x);
	}
	return;
}
bool chk (int a,int b,int c,int d) {
	for (int i=1;i<=n;i++) {vis[0][i]=vis[1][i]=0;}
	int x=a,flg=0;
	while (x) {vis[0][x]=1;x=f[x];}
	x=b;
	while (x) {
		if (flg) {vis[0][x]=0;}
		if (vis[0][x]) {flg=1;}
		if (!flg) {vis[0][x]=1;}
		x=f[x];
	}
	x=c,flg=0;
	while (x) {vis[1][x]=1;x=f[x];}
	x=d;
	while (x) {
		if (flg) {vis[1][x]=0;}
		if (vis[1][x]) {flg=1;}
		if (!flg) {vis[1][x]=1;}
		x=f[x];
	}
	for (int i=1;i<=n;i++) {if (vis[0][i]&&vis[1][i]) {return 0;}}
	return 1;
}
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z),add_edge(y,x,z);
	}
	dfs(1,0);
	for (int i=1;i<=n;i++) {
		for (int j=i;j<=n;j++) {
			for (int k=1;k<=n;k++) {
				for (int l=k;l<=n;l++) {
					if ((dis[i]^dis[j])+(dis[k]^dis[l])<ans) {continue;}
					if (chk(i,j,k,l)) {
						ans=max(ans,(dis[i]^dis[j])+(dis[k]^dis[l]));
					}
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

------

#### 算法 $2$：（$Subtask\ 1,2$，结论+枚举）

设 $l=lca(a,b)$，那么如果 $c$ 在 $l$ 子树内，而 $d$ 在 $l$ 子树外，那么路径 $c\to d$ 一定经过点 $l$，所以一定与 $a\to b$相交；如果 $c,d$ 都在 $l$ 子树外，那么路径 $c\to d$ 一定与 $a\to b$ 不相交；最麻烦的是 $c,d$ 都在 $l$ 子树内，无法直接判断，但是这时换个角度也可以解决：

既然 $c,d$ 都在 $a\to b$ 的 $lca$ 子树内，那么我们可以反过来看 $a,b$ 与 $c\to d$ 的 $lca$ 的关系，设 $q=lca(c,d)$，判断 $a,b,q$ 的关系就可以判定相交关系了（此时如果再次出现 $a,b$ 都在 $q$ 子树内，那么显然是 $a\to b$，$c\to d$ 两条路径交于一点 $q$，$q$ 同时是两对点的 LCA）。

所以我们只要枚举 $l=lca(a,b)$，在 $l$ 子树内任取两点作为 $a,b$，在 $l$ 子树外任取两点作为 $c,d$，那么 $a,b,c,d$ 就是一对合法路径。所以我们可以减小枚举量，枚举 $l$ 后只要分别枚举两对点，显然令 $dist[a]\oplus dist[b]$ 和 $dist[c]\oplus dist[d]$ 分别取到最大值，相加以后即可取最大值。

直接枚举是 $O(n^3)$ 的，可以用 0-1 Trie 始终维护当前考虑过的所有数，每个数可以 $O(\log W)$ 完成插入和查询，于是优化了复杂度。

时间复杂度为 $O(n^2\log W)$，其中 $W=\max(w_i)$，可以解决 $n\leq 2\times 10^3$ 的部分分。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=60010,B=60;
int n,x,y,z,eg,cnt,tot=1,hd[MAXN],ver[2*MAXN],nx[2*MAXN],edge[2*MAXN];
int dfn[MAXN],ed[MAXN],siz[MAXN<<5],ch[MAXN<<5][2];
ll dist[MAXN],val[MAXN],ans;
void add_edge (int x,int y,int z) {
	ver[++eg]=y;
	nx[eg]=hd[x],edge[eg]=z;
	hd[x]=eg;
	return;
}
void ins (ll x) {
	int p=1;
	siz[1]++;
	for (int i=B;i>=0;i--) {
		int b=((x>>i)&1);
		if (!ch[p][b]) {ch[p][b]=++tot;}
		p=ch[p][b];
		siz[p]++;
	}
	return;
}
ll query (ll x) {
	int p=1;
	ll res=0;
	for (int i=B;i>=0;i--) {
		int b=((x>>i)&1);
		if (siz[ch[p][b^1]]) {
			p=ch[p][b^1],res|=(1ll<<i);
		} else {
			p=ch[p][b];
		}
	}
	return res;
}
void dfs (int x,int fa) {
	dfn[x]=ed[x]=++cnt;
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dist[ver[i]]=dist[x]^edge[i];
		dfs(ver[i],x);
		ed[x]=ed[ver[i]];
	}
	return;
}
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z),add_edge(y,x,z);
	}
	dfs(n,0);
	for (int i=1;i<=n;i++) {
		val[dfn[i]]=val[dfn[i]+n]=dist[i];
	}
	for (int i=2;i<=n;i++) {
		ll tmp1=0,tmp2=0;
		for (int j=1;j<=tot;j++) {ch[j][0]=ch[j][1]=siz[j]=0;}
		tot=1;
		for (int j=dfn[i];j<=ed[i];j++) {
			ins(val[j]);
			tmp1=max(tmp1,query(val[j]));
		}
		for (int j=1;j<=tot;j++) {ch[j][0]=ch[j][1]=siz[j]=0;}
		tot=1;
		for (int j=ed[i]+1;j<=dfn[i]+n-1;j++) {
			ins(val[j]);
			tmp2=max(tmp2,query(val[j]));
		}
		ans=max(ans,tmp1+tmp2);
	}
	printf("%lld\n",ans);
	return 0;
}
```

------

#### 算法 $3$：（$Subtask\ 3$，0-1 Trie，链式数据）

对于退化成链的树，可以理解为一个序列，我们需要从序列中选出两个不相邻区间（注意仅仅不相交是不够的，那样可能会导致端点重合），使得异或和之和最大。

这是一个经典问题，记 $s_i$ 为 $w_i$ 的前缀异或和，我们可以先顺序将所有 $s_i$ 加入一个 0-1 Trie，求出所有 $pre_i$ 表示 $[1,i]$ 中选择两个 $s_i$ 的最大异或和。同理倒序插入 0-1 Trie 可以求出 $suc_i$ 表示 $[i,n]$ 中选择两个 $s_i$ 的最大异或和。然后枚举分界点 $i$，求 $\max(pre_{i-1}+suc_{i+1})$ 即可。

时间复杂度为 $O(n\log W)$，其中 $W=\max(w_i)$，可以解决链式数据，结合算法 $2$ 可获得 $50\%$ 的分数。 

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=30010,B=30;
int n,tot=1,x,y,z,ans,s[MAXN],pre[MAXN],suf[MAXN],sz[MAXN<<5],ch[MAXN<<5][2];
void ins (int x,int v) {
	int p=1;
	sz[1]+=v;
	for (int i=B;i>=0;i--) {
		int tmp=((x>>i)&1);
		if (!ch[p][tmp]) {ch[p][tmp]=++tot;}
		p=ch[p][tmp];
		sz[p]+=v;
	}
	return;
}
int query (int x) {
	int p=1,res=0;
	for (int i=B;i>=0;i--) {
		int tmp=((x>>i)&1);
		if (sz[ch[p][tmp^1]]) {p=ch[p][tmp^1],res+=(1<<i);}
		else {p=ch[p][tmp];}
	}
	return res;
}
int main () {
	scanf("%d",&n);
	ins(0,1);
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		s[i]=s[i-1]^z;
		pre[i]=max(pre[i-1],query(s[i]));
		ins(s[i],1);
	}
	memset(sz,0,sizeof(sz));
	memset(ch,0,sizeof(ch));
	tot=1;
	ins(0,1);
	for (int i=n-1;i>=1;i--) {
		s[i]=s[i+1]^(s[i]^s[i-1]);
		suf[i]=max(suf[i+1],query(s[i]));
		ins(s[i],1);
	}
	for (int i=1;i<=n-1;i++) {ans=max(ans,pre[i-1]+suf[i+1]);}
	printf("%d\n",ans);
	return 0;
}
```

------

#### 算法 $4$：（$100\%$，回滚莫队+0-1 Trie）

~~观察数据范围为 $n\leq 2\times 10^4$，猜测出题人的内心，可能需要一个带根号复杂度的算法。~~

树上问题直接解决是不方便的，可以放到序列上考虑：

我们要从枚举的 $l$ 的子树内外各选出一对点，分别的异或和最大。如果我们将点按照 DFN 排成一个序列，那么 $l$ 的子树就是一个区间，设为 $[x_l,y_l]$，于是我们问题就变成了：

1. 从 $[x_l,y_l]$ 中选出一对数，异或和最大；
2. 从 $[1,x_l-1]\cup [y_l+1,n]$ 中选一对数，异或和最大。

两者互不干扰，可以看成两个任务来做。

这两个问题都有一个显著的特点，如果要加一个数，容易更新答案；但如果要删一个数，不容易更新答案。也就是说：以第一问为例，从 $[x,y]$ 的答案扩展 $[x,y+1]$ 是简单的，只需要求 $y+1$ 与所有 $[x,y]$ 内的数的异或最大值即可，可以用 0-1 Trie 解决；但是要从 $[x,y]$ 扩展到 $[x,y-1]$ 就很困难，不容易统计答案。

这类问题可以用回滚莫队来解决，还是以第一问为例：将所有询问 $[x_i,y_i]$ 按照 $x_i$ 的位置分块，每一块分别计算答案：

由于我们只会处理加数的操作，所以在莫队的扩展过程中希望只增不减，所以块内按照 $y_i$ 升序排序。用一个 Trie 维护当前块右端点 $R$ 到当前处理到的 $y_i$ 这一段的答案。遇到一个询问 $[x_i,y_i]$ 时，先将右端点推到 $y_i$，将遇到的数加到 Trie 中，然后先记录一个当前的答案 $ans$（即区间 $[R,y_i]$ 的最大异或和），然后将左端点从 $R$ 不断向左推到 $x_i$，同样将遇到的数加入 Trie，然后统计答案，这样一个询问就解决了，但是由于我们不能直接删除一个数，所以每做完一个询问，就要将左端点重新推回 $R$ 来实现撤销，这样当前区间答案依然是 $ans$，接下来可以更新。

第二问处理方法类似，只是这次我们容易从 $[x,y]$ 的答案推得 $[x,y-1]$ 的答案但很难推得 $[x,y+1]$ 的答案，所以同一块内按 $y_i$ 降序排序，Trie 维护当前块左端点 $L$ 至当前的 $y_i$ 的最大异或和，其他步骤类似。

设块长为 $S$，则总共有 $\frac{n}{S}$ 块，每一块内右端点有序，所以移动是 $O(n)$ 的；左端点只在同一块内移动，所以是$O(q\times S)$，其中 $q$ 为询问个数，在这里每个子树都问一次，所以有 $\sum q=n$。又因为每次移动需要加一个数到 Trie 中，时间复杂度是 $O(\log n)$，所以总的时间复杂度为 $O((n\frac{n}{S}+nS)\log n)$，取 $S=\sqrt n$ 时取到最优复杂度。

事实上，如果把 DFS 序复制两倍，那么第二个问题也变成了一个连续区间，但是这样做会降低效率，我不知道为什么。

最终时间复杂度是 $O(n\sqrt n\log W)$，其中 $W=\max(w_i)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=30010,B=30;
struct Query {
	int l,r,id,bl;
}q[MAXN];
int n,x,y,z,eg,cnt,res,sq,tot=1,w,l,r,mxor,fr,to,ans[MAXN],hd[MAXN],ver[2*MAXN],nx[2*MAXN],edge[2*MAXN];
int dfn[MAXN],ed[MAXN],ps[MAXN],dep[MAXN],val[MAXN],pref[MAXN],sz[MAXN<<5],edn[MAXN<<5],ch[MAXN<<5][2];
bool cmp1 (Query a,Query b) {return (a.bl==b.bl?a.r<b.r:a.bl<b.bl);}
bool cmp2 (Query a,Query b) {return (a.bl==b.bl?a.r>b.r:a.bl<b.bl);}
void add_edge (int x,int y,int z) {
	ver[++eg]=y;
	nx[eg]=hd[x],edge[eg]=z;
	hd[x]=eg;
	return;
}
void dfs (int x,int fa) {
	dfn[x]=ed[x]=++cnt;
	ps[cnt]=x,val[cnt]=dep[x];
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dep[ver[i]]=dep[x]^edge[i];
		dfs(ver[i],x);
		ed[x]=ed[ver[i]];
	}
	return;
}
void ins_pos (int x,int v,int pos) {
	int p=1;
	sz[1]+=v;
	for (int i=B;i>=0;i--) {
		int tmp=((x>>i)&1);
		if (!ch[p][tmp]) {ch[p][tmp]=++tot;}
		p=ch[p][tmp];
		sz[p]+=v;
	}
	edn[p]=pos;
	return;
}
int query_pos (int x) {
	int p=1,res=0;
	for (int i=B;i>=0;i--) {
		int tmp=((x>>i)&1);
		if (sz[ch[p][tmp^1]]) {p=ch[p][tmp^1];}
		else {p=ch[p][tmp];}
	}
	return edn[p];
}
void ins (int x,int v) {
	int p=1;
	sz[1]+=v;
	for (int i=B;i>=0;i--) {
		int tmp=((x>>i)&1);
		if (!ch[p][tmp]) {ch[p][tmp]=++tot;}
		p=ch[p][tmp];
		sz[p]+=v;
	}
	return;
}
int query (int x) {
	int p=1,res=0;
	for (int i=B;i>=0;i--) {
		int tmp=((x>>i)&1);
		if (sz[ch[p][tmp^1]]) {p=ch[p][tmp^1],res+=(1<<i);}
		else {p=ch[p][tmp];}
	}
	return res;
}
int main () {
	scanf("%d",&n);
	sq=pow(n,0.5);
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z),add_edge(y,x,z);
	}
	dfs(1,0);
	for (int i=1;i<=n;i++) {
		ins_pos(val[i],1,i);
		int tpos=query_pos(val[i]);
		int tmp=val[i]^val[tpos];
		pref[i]=max(pref[i-1],tmp);
		if (tmp>mxor) {mxor=tmp,l=tpos,r=i;}
	}
	for (int i=1;i<=n;i++) {q[i].l=dfn[i],q[i].r=ed[i],q[i].id=i,q[i].bl=(dfn[i]-1)/sq+1;}
	sort(q+1,q+n+1,cmp1);
	memset(sz,0,sizeof(sz));
	memset(ch,0,sizeof(ch));
	tot=1;
	w=r=0,l=1;
	for (int i=1;i<=n;i++) {
		if (q[i].bl!=q[i-1].bl) {
			while (l<q[i].bl*sq+1) {
				if (l<=r) {ins(val[l],-1);}
				l++;
			}
			while (r>q[i-1].bl*sq) {
				if (l<=r) {ins(val[r],-1);}
				r--;
			}
			w=0;
		}
		while (r<q[i].r) {
			r++;
			if (l<=r) {ins(val[r],1);w=max(w,query(val[r]));}
		}
		int tmp=w;
		while (l>q[i].l) {
			l--;
			if (l<=r) {ins(val[l],1);w=max(w,query(val[l]));}
		}
		ans[q[i].id]+=w;
		while (l<q[i].bl*sq+1) {
			if (l<=r) {ins(val[l],-1);}
			l++;
		}
		w=tmp;
	}
	sort(q+1,q+n+1,cmp2);
	memset(sz,0,sizeof(sz));
	memset(ch,0,sizeof(ch));
	tot=1;
	w=0,l=1,r=n;
	for (int i=1;i<=n;i++) {
		if (q[i].bl!=q[i-1].bl) {
			while (r<n) {
				r++;
				if (l<=r) {ins(val[r],-1);}
			}
			while (l<(q[i].bl-1)*sq+1) {
				if (l<=r) {ins(val[l],1);}
				l++;
			}
			w=pref[q[i-1].bl*sq];
		}
		if (l>fr&&r<to) {ans[q[i].id]+=mxor;continue;}
		while (r>q[i].r) {
			if (l<=r) {ins(val[r],1);w=max(w,query(val[r]));}
			r--;
		}
		int tmp=w;
		while (l<q[i].l) {
			if (l<=r) {ins(val[l],1);w=max(w,query(val[l]));}
			l++;
		}
		ans[q[i].id]+=w;
		while (l>(q[i].bl-1)*sq+1) {
			l--;
			if (l<=r) {ins(val[l],-1);}
		}
		w=tmp;
	}
	for (int i=2;i<=n;i++) {res=max(res,ans[i]);}
	printf("%d\n",res);
	return 0;
}
```



---

## 作者：5k_sync_closer (赞：11)

看来 P8511 的套路还不怎么推广。来点单 $\log$ 做法。

令 $a_i=f(E(1,i))$，则 $E(x,y)=a_x\oplus a_y$。

令 $s_i$ 为 $i$ 子树外 $a$ 的最大异或对，$t_i$ 为 $i$ 子树内 $a$ 的最大异或对。

转化一下问题，求 $\max\{s_i+t_i\}$。

求 $s_i$ 就是 [P8511](https://www.luogu.com.cn/problem/P8511)，[这里仅给出题解](https://www.luogu.com.cn/blog/388651/solution-p8511)。

考虑用相似的套路求 $t_i$，分类讨论 $i$ 的位置。

1. $i$ 为 $x$ 或 $y$ 的祖先。从 $x,y$ 爬到根，01 Trie 维护子树内点集，途中统计答案。
2. $\text{otherwise}$。此时 $x,y$ 都在 $i$ 子树外，即 $s_i$ 为定值 $a_x\oplus a_y$，且任意子树的 $t_i$ 不劣于其内部子树，所以只需统计满足条件的极大子树即可。

显然每个过程中每个点都只会被加一次，所以复杂度 $O(n\log n)$。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct E
{
    int v, w, t;
} e[60050];
struct T
{
    int c[2] = {0, 0}, k = 0, v;
} R[2000050];
int n, c, x, y, z, p, q, r = 1, P = 1, a[30050], s[30050], t[30050], f[30050], g[30050], h[30050];
void A(int u, int v, int w)
{
    e[++c] = {v, w, h[u]};
    h[u] = c;
}
void I(int i, int x)
{
    int p = r;
    ++R[r].k;
    for (int i = 30, o; i >= 0; --i)
        p = R[p].c[o = x >> i & 1] ? R[p].c[o] : R[p].c[o] = ++P, ++R[p].k;
    R[p].v = i;
}
int Q(int &i, int x)
{
    int p = r;
    for (int i = 30, o; i >= 0; --i)
        p = R[p].c[R[R[p].c[o = !(x >> i & 1)]].k ? o : !o];
    return x ^ a[i = R[p].v];
}
void D(int u, int k)
{
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
            f[v] = u, a[v] = a[u] ^ e[i].w, D(v, u);
}
void F1(int u, int k)
{
    I(u, a[u]);
    q = max(q, Q(z, a[u]));
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k && v != g[u])
            F1(v, u);
}
void F2(int u, int k)
{
    g[u] = 1;
    I(u, a[u]);
    q = max(q, Q(z, a[u]));
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k && !g[v])
            F2(v, u);
}
void G1(int x)
{
    q = 0;
    for (int i = 1; i <= n; ++i)
        g[i] = 0;
    for (int i = x; i != 1; i = f[i])
        g[f[i]] = i;
    for (int i = r = 1; i <= P; ++i)
        R[i].c[0] = R[i].c[1] = R[i].k = 0;
    for (int i = P = 1; i != x; i = g[i])
        s[i] = q, F1(i, f[i]);
    s[x] = q;
}
void G2(int x)
{
    q = 0;
    for (int i = 1; i <= n; ++i)
        g[i] = 0;
    for (int i = r = 1; i <= P; ++i)
        R[i].c[0] = R[i].c[1] = R[i].k = 0;
    for (int i = x; i; i = f[i])
        F2(i, f[i]), t[i] = q;
}
void S(int u, int k)
{
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
            if (g[v])
                S(v, u);
            else
            {
                q = 0;
                for (int i = r = 1; i <= P; ++i)
                    R[i].c[0] = R[i].c[1] = R[i].k = 0;
                P = 1;
                F1(v, u);
                t[v] = q;
            }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; ++i)
        scanf("%d%d%d", &u, &v, &w), A(u, v, w), A(v, u, w);
    D(1, 0);
    for (int i = 1; i <= n; ++i)
        I(i, a[i]);
    for (int i = 1; i <= n; ++i)
        if (q < (p = Q(z, a[i])))
            q = p, x = i, y = z;
    for (int i = 1; i <= n; ++i)
        s[i] = q;
    G1(x);
    G1(y);
    G2(x);
    G2(y);
    for (int i = 1; i <= n; ++i)
        g[i] = 0;
    for (int i = x; i; i = f[i])
        g[i] = 1;
    for (int i = y; i; i = f[i])
        g[i] = 1;
    S(1, 0);
    q = 0;
    for (int i = 2; i <= n; ++i)
        q = max(q, s[i] + t[i]);
    printf("%d", q);
    return 0;
}
```


---

## 作者：Sai0511 (赞：8)

QwQ 原定验题人来发个题解。~~因为我太菜跑路了所以验题人就变成Kubic了。~~   
一句话题意：选两条不相交的路径，使其边权的异或和的和最大。   
首先分析一下两条路径不相交的性质。   
设路径1的两个端点是$a,b$，它们的$\text{lca}$是$p$。路径2的两个端点是$c,d$，它们的$\text{lca}$是$q$。  
情况1：当$c$在子树$p$内部而$d$在子树$p$外部时，$c \rightarrow d$一定与$a \rightarrow b$相交。  
情况2：当$c$和$d$都在子树$p$外部时，$c \rightarrow d$一定不与$a \rightarrow b$相交。  
当$c,d$都在子树$p$内部时，我们可以反过来讨论$a \rightarrow b$与$q$的关系。    
情况3：当$a$在子树$q$内部而$b$在子树$q$外部时，同情况1。  
情况4：当$a$和$b$都在子树$q$外部时，同情况2。  
情况5：当$a$和$b$都在子树$q$内部时，$p$与$q$必交与一点，故这2条路径一定相交。   
所以如果2条路径不相交则**路径1一定在某一子树内，路径2一定在这个子树外**。   
接着40分做法就一目了然了：枚举一个点，然后枚举在这个子树内的点和这个子树外的点，使这两部分的异或和最大。可以用$01\text{trie}$做到$\mathcal{O}(n^2\log \{ \max w_i\})$。  
结合一下链的部分分可以获得$60$分的好成绩。   
**接下来才是这题的核心，从$60$分到正解的过度。**  
考虑把问题放在序列上，设$L(u)$表示子树$u$的开始$\text{dfs}$序，$R(u)$表示子树$u$的结束$\text{dfs}$序。  
则子树$u$对应的询问就是在$[L(u),R(u)]$选出2个异或和最大的数，在$[1,L(u)-1] \cup [R(u)+1,n]$中选出2个异或和最大的数。  
发现这2个区间并不连续，比较麻烦。**但是因为这2个区间的并相当于从整个序列中挖走了一段出来，所以把这个序列复制一遍加到末尾一定可以得到一个完整的连续的覆盖所有信息的区间。**  
到了这里其实这道题就结束了，我们相当于对于每个点创造出2个询问，这个点的答案就是这2个询问对应的区间的最大异或和之和。   
可以用回滚莫队+$\text{01trie}$做到$\mathcal{O}(n\sqrt{n}log \{ \max w_i \})$。    
代码：
```cpp
#include <bits/stdc++.h>

const int N = 6e4 + 10;
int n, m, i, j, k, tot, totq, p = 1, trie_tot = 1, SZ, Ans;
int dfn[N], siz[N], bel[N], dis[N];
int fir[N], we[N << 1], to[N << 1], nxt[N << 1]; 
int ch[N * 26][2], tag[N * 26], ans[N];
struct ques {
  int l, r, id;
  ques() { l = r = id = 0; }
  ques(int _l, int _r, int i) {
    l = _l, r = _r, id = i; 
  }
  inline friend bool operator < (ques a, ques b) {
    if (bel[a.l] == bel[b.l]) return a.r < b.r;
    else return bel[a.l] < bel[b.l];
  }
} q[N << 1];  
inline void adde(int u, int v, int w) {
  static int ce = 0;
  to[++ce] = v, we[ce] = w, nxt[ce] = fir[u], fir[u] = ce;
}
inline void insert(int a) {
  int u = 1;
  for (int i = 30; i >= 0; i--) {
    bool v = (a >> i) & 1;
    if (!ch[u][v]) ch[u][v] = ++trie_tot;
    u = ch[u][v];
    tag[u]++;
  }
}
inline int query(int a) {
  int u = 1, res = 0;
  for (int i = 30; i >= 0; i--) {
    bool v = (a >> i) & 1;
    if (tag[ch[u][v ^ 1]]) res |= 1 << i, u = ch[u][v ^ 1];
    else u = ch[u][v]; 
  }
  return res;
}
inline void del(int a) {
  int u = 1;
  for (int i = 30; i >= 0; i--) {
    bool v = (a >> i) & 1;
    u = ch[u][v];
    tag[u]--;
  }
}
void dfs(int u, int par, int w) {
  siz[u] = 1, dfn[u] = ++tot, dis[dfn[u]] = dis[dfn[par]] ^ w;
  for (int i = fir[u], v; i; i = nxt[i]) 
    if ((v = to[i]) != par) {
      int w = we[i];
      dfs(v, u, w);
      siz[u] += siz[v];
    }
}
inline int calc(int l, int r) {
  int res = 0;
  for (int i = l; i <= r; i++) res = std::max(res, query(dis[i])), insert(dis[i]); 
  for (int i = l; i <= r; i++) del(dis[i]);
  return res;
}
inline void solve(int x) {
  int br = std::min(x * SZ, n), l = br + 1, r = br;
  int _ans = 0;
  for (; bel[q[p].l] == x; p++) {
    int ql = q[p].l, qr = q[p].r;  
    if (bel[qr] == x) { ans[q[p].id] += calc(ql, qr); continue; } 
    while (r < qr) _ans = std::max(_ans, query(dis[++r])), insert(dis[r]);
    int rev = _ans;
    while (l > ql) _ans = std::max(_ans, query(dis[--l])), insert(dis[l]);  
    ans[q[p].id] += _ans;
    while (l <= br) del(dis[l++]); _ans = rev;
  }
  while (r > br) del(dis[r--]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1, u, v, w; i < n; i++) scanf("%d %d %d",&u, &v, &w), adde(u, v, w), adde(v, u, w); 
  dfs(1, 0, 0); 
  for (int i = 2; i <= n; i++) q[++totq] = ques(dfn[i], dfn[i] + siz[i] - 1, i), q[++totq] = ques(dfn[i] + siz[i], dfn[i] + n - 1, i);
  for (int i = 1; i <= n; i++) dis[i + n] = dis[i];
  n <<= 1; SZ = sqrt(n);
  for (int i = 1; i <= n; i++) bel[i] = (i - 1) / SZ + 1;
  std::sort(q + 1, q + totq + 1);
  for (int i = 1; i <= bel[n]; i++) solve(i);
  for (int i = 1; i <= n; i++) Ans = std::max(Ans, ans[i]);
  printf("%d\n", Ans);
  return 0;
}
```

---

## 作者：kernel_panic (赞：5)

## 思路

先做一遍树上前缀异或和，转化为选出四个点 $a, b, c, d$，使得 $V(a, b) \cap V(c, d) = \varnothing$，最大化 $(v_a \oplus v_b) + (v_c \oplus v_d)$．

为了满足第一个限制，我们可以枚举一个点 $u$，钦定 $a, b$ 在 $u$ 的子树内，$c, d$ 在 $u$ 的子树外，容易发现这覆盖了所有情况．然后两部分独立了，考虑分别求解．

子树内的部分可以采用 01-Trie + DSU on tree 简单解决，子树外的部分就是 [[Ynoi Easy Round 2021] TEST_68](https://www.luogu.com.cn/problem/P8511)．然后把两部分答案拼起来就行．

时间复杂度 $O(n \log n \log V)$，其中 $V$ 是值域．

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

#define int long long

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

using pii = std::pair<int, int>;

const int N = 3e4;
const int LOGV = 30;

int n; std::vector<pii> G[N + 5];

int fa[N + 5]; std::vector<int> g[N + 5];

int val[N + 5];
void dfs(int u, int f) {
	fa[u] = f;
	for (auto [v, w] : G[u]) {
		if (v == f) continue;
		val[v] = val[u] ^ w, dfs(v, u);
	}
}

int st[N + 5], stc[N + 5];

namespace trie {
	int ch[N * LOGV + 5][2], ed[N * LOGV + 5], alct;
	void ins(int x, int id) {
		int p = 0;
		for (int i = LOGV; i >= 0; i--) {
			int c = x >> i & 1;
			if (!ch[p][c]) ch[p][c] = ++alct;
			p = ch[p][c];
		}
		ed[p] = id;
	}
	pii que(int x) {
		int p = 0, res = 0;
		for (int i = LOGV; i >= 0; i--) {
			int c = x >> i & 1;
			if (ch[p][!c]) p = ch[p][!c], res |= 1 << i;
			else p = ch[p][c];
		}
		return {res, ed[p]};
	}
	void clear() {
		for (int i = 0; i <= alct; i++) ch[i][0] = ch[i][1] = ed[i] = 0;
		alct = 0;
	}
};

namespace paradise {
	int dfn[N + 5], rid[N + 5], cid;
	int siz[N + 5], hch[N + 5], chn[N + 5];
	void gethch(int u) {
		siz[u] = 1;
		for (int v : g[u]) {
			gethch(v), siz[u] += siz[v];
			if (siz[v] > siz[hch[u]]) hch[u] = v;
		}
	}
	void getchn(int u, int ct) {
		rid[dfn[u] = ++cid] = u;
		if (hch[u]) getchn(hch[u], ct);
		for (int v : g[u]) {
			if (v == hch[u]) continue;
			getchn(v, v);
		}
	}
	void dfs(int u, bool keep) {
		for (int v : g[u]) {
			if (v == hch[u]) continue;
			dfs(v, 0), st[u] = std::max(st[u], st[v]);
		}

		if (hch[u]) dfs(hch[u], 1), st[u] = std::max(st[u], st[hch[u]]);

		st[u] = std::max(st[u], trie::que(val[u]).first);
		trie::ins(val[u], u);
		for (int v : g[u]) {
			if (v == hch[u]) continue;
			for (int i = dfn[v]; i <= dfn[v] + siz[v] - 1; i++) {
				int w = rid[i];
				st[u] = std::max(st[u], trie::que(val[w]).first);
				trie::ins(val[w], w);
			}
		}
		if (!keep) trie::clear();
	}
	void solve() {
		gethch(1), getchn(1, 1);
		dfs(1, 0);
	}
};

namespace paradox {
	int cur;
	void ins_subtree(int u) {
		trie::ins(val[u], 0);
		cur = std::max(cur, trie::que(val[u]).first);
		for (int v : g[u]) ins_subtree(v);
	}
	void solve_chain(int u) {
		static int st[N + 5]; int tp = 0;
		while (u) st[++tp] = u, u = fa[u];
		for (int i = tp; i >= 1; i--) {
			int u = st[i];
			stc[u] = std::max(stc[u], cur);
			trie::ins(val[u], 0);
			cur = std::max(cur, trie::que(val[u]).first);
			for (int v : g[u]) {
				if (v == st[i - 1]) continue;
				ins_subtree(v);
			}
		}
	}
	void solve() {
		trie::ins(0, 0);
		for (int i = 1; i <= n; i++) trie::ins(val[i], i);
		int mx = -1, u = -1, v = -1;
		for (int i = 1; i <= n; i++) {
			auto [va, j] = trie::que(val[i]);
			if (va > mx) mx = va, u = i, v = j;
		}
		memset(stc, -1, sizeof(stc));
		trie::clear(), cur = 0, solve_chain(u);
		trie::clear(), cur = 0, solve_chain(v);
		for (int i = 1; i <= n; i++) if (stc[i] == -1) stc[i] = mx;
	}
};

signed main() {
	n = rd();
	for (int i = 2; i <= n; i++) {
		int u = rd(), v = rd(), w = rd();
		G[u].emplace_back(v, w), G[v].emplace_back(u, w);
	}
	dfs(1, 0); for (int i = 2; i <= n; i++) g[fa[i]].push_back(i);

	paradise::solve(), paradox::solve();
	int ans = 0;
	for (int i = 2; i <= n; i++) {
		ans = std::max(ans, st[i] + stc[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：_HL_ (赞：5)

单 $\log $ 楼上已经有人写了 但似乎跑的很慢 不太理解 我的单 $\log $ 跑的挺快 现在 ( 2022.2.11 ) 是最优解第一 写篇题解纪念一下 qwq

首先任选一个根路径差分 点权为点到根路径边权异或和

问题转化为分割一颗树变成一个子树和剩余部分 使这两部分各选最大异或点对 两部分最大异或点对之和为这种分割方案的答案

分割问题 很直观的一个想法是枚举分割点 也就相当于求全部子树和 rest 的最大异或点对 用 dsu 有双 $\log$ 解法

但是我们要求得是全局答案 这种方案需要求出每个点的答案 是将问题加强了的

考虑解决这类全局支配问题的方法 先找到全局最大点对 这两个点的路径外的点为分割点时显然有一部分最大值必为全局异或最大点对 而另一部分子树内的点是显然比不上子树的根的 给张图比较好理解

![](https://cdn.luogu.com.cn/upload/image_hosting/tz3nxe78.png)

红色点对为异或最大点对 注意 现在的点权是经过问题转化后的 

那么不难看出黄色的点为分割点显然是要劣于绿色的点为分割点

因此我们只需要处理红色路径四周的点为根的子树和红色路径上点为分割点

我们可以形象地称红色路径为树干

我们发现树干四周的点的子树是互不包含的 因此这里的点只需要 $O(1)$ 次操作 01trie 暴力插暴力清空即可

再考虑树干上的点

树干是弯的还有一个关键点为 lca 不太好处理 我们考虑换根 而换根没有改变树的路径 因此我们树上差分边权转点权的问题转化还是成立的

我们考虑以树干上一个点为根

![](https://cdn.luogu.com.cn/upload/image_hosting/j6zlpa8t.png)

仔细看这两张图其实是一样的树

问题转化为一条从上到下的链上求子树内异或最大点对加子树外异或最大点对的值

01trie 暴力插 每个点插 $O(1)$ 次

因此总共插 $O(n)$ 次 单次 $O(\log V)$

总复杂度时间空间都是 $O(n\log V)$

坑点是 01trie 空间要开够 我写的这个最后会多出一倍的点 01trie 压缩可以空间线性 我不会（

然后就没啥坑了 两发就过了 卡了几发常 

这题不开 O2 比开要快（

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
const int N=3e4+3;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c<='9'&&c>='0')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x;
}
struct node
{
	int to;
	int nxt;
	int w;
}e[N<<1];
int etot,h[N],w[N];
inline void e_add(int x,int y,int w)
{
	e[++etot].to=y;
	e[etot].nxt=h[x];
	e[etot].w=w;
	h[x]=etot;
}
void get_w(int x,int fa)
{
	for(int i=h[x];i;i=e[i].nxt)
	{
		if(e[i].to!=fa)
		{
			w[e[i].to]=w[x]^e[i].w;
			get_w(e[i].to,x);
		}
	}
}
int trie[N*60+1][2],id[N*60+1];
int maxv,maxn[2];
int tot;
inline void ins(int x,int idx)
{
	bool f[32];
	int p=0;
	for(int i=30;i>=0;i--)
	{
		if(x>=(1<<i))
		{
			x-=(1<<i);
			f[i]=1;
		}
		else
		f[i]=0;
		if(!trie[p][f[i]])trie[p][f[i]]=++tot;
		p=trie[p][f[i]];
	}
	id[p]=idx;
	p=0;
	int res=0;
	for(int i=30;i>=0;i--)
	{
		if(!trie[p][f[i]^1])p=trie[p][f[i]];
		else
		{
			p=trie[p][f[i]^1];
			res+=(1<<i);
		}
	}
	if(res>maxv)
	{
		maxv=res;
		maxn[0]=id[p];
		maxn[1]=idx;
	}
}
inline void get_max()
{
	for(int i=1;i<=n;i++)ins(w[i],i);
}
int fa[N];
void rebuild(int x)
{
	for(int i=h[x];i;i=e[i].nxt)
	{
		if(e[i].to!=fa[x])
		{
			fa[e[i].to]=x;
			rebuild(e[i].to);
		}
	}
}
inline void clear(int p)
{
	if(trie[p][0])
	{
		clear(trie[p][0]);
		trie[p][0]=0;
	}
	if(trie[p][1])
	{
		clear(trie[p][1]);
		trie[p][1]=0;
	}
}
int son[N];
int all_max,ans;
void dfs(int x)
{
	ins(w[x],x);
	for(int i=h[x];i;i=e[i].nxt)
	if(e[i].to!=fa[x])dfs(e[i].to);
}
int ans_t[N];
inline void lxl(int rt,int l_end)
{
	int x=l_end;
	while(x!=rt)
	{
		son[fa[x]]=x;
		x=fa[x];
	}
	while(x)
	{
		for(int i=h[x];i;i=e[i].nxt)
		{
			if(e[i].to!=fa[x]&&e[i].to!=son[x])
			{
				clear(0);
				maxv=-1;
				dfs(e[i].to);
				ans=max(ans,all_max+maxv);
			}
		}
		x=son[x];
	}
	clear(0);
	maxv=-1;
	x=rt;
	while(x)
	{
		ans_t[x]=maxv;
		for(int i=h[x];i;i=e[i].nxt)
		{
			if(e[i].to!=fa[x]&&e[i].to!=son[x])
			{
				dfs(e[i].to);
			}
		}
		ins(w[x],x);
		x=son[x];
	}
	clear(0);
	maxv=-1;
	x=l_end;
	while(x)
	{
		for(int i=h[x];i;i=e[i].nxt)
		{
			if(e[i].to!=fa[x]&&e[i].to!=son[x])
			{
				dfs(e[i].to);
			}
		}
		ins(w[x],x);
		ans_t[x]+=maxv;
		ans=max(ans,ans_t[x]);
		x=fa[x];
	}
}
int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read(),w=read();
		e_add(x,y,w);
		e_add(y,x,w);
	}
	maxv=-1;
	ans=-1;
	get_w(1,0);
	get_max();
	int uu1=maxn[0],uu2=maxn[1];
	all_max=maxv;
	rebuild(maxn[0]);
	lxl(uu1,uu2);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：yzxoi (赞：4)

[My Blog](https://yzxoi.top/archives/1913)

给定一棵 $n$ 个节点的无根树，从中选择两个不交路径，求边权异或和之和最大值。

$n\leq 3\times 10^4$。

## Sol

这里具体讲讲一只 $\log$ 的做法（在此感谢 [神仙lwy](https://www.luogu.com.cn/discuss/show/347250)）。

考虑这种题首先套路地枚举分界点 $x$，使两条路径一条在节点 $x$ 的子树内，另一条在子树外。

然后就很自然地想到了 $\mathcal O(n\log n\log w)$ 的 DSU+Trie 的做法处理子树内的部分，子树外的部分可以先利用 Trie 求出任意一对全局的异或和最大的点对 $(X,Y)$，那么显然所有不在 $X$ 到根和 $Y$ 到根的路径上的点的子树外的答案都是 $(X,Y)$ 间的异或和。考虑 $X$ 到根以及 $Y$ 到根的路径就直接从根节点出发，每次将点插入 Trie 中，维护出异或值最大即可，由于每个点只会被插一次，所以总复杂度为 $\mathcal O(n\log w)$。

然后考虑如何做到完全的一只 $\log$。还是先求出全局的异或和最大的 $(X,Y)$，然后把这条 $X$ 到 $Y$ 的链提取出来。

- 如果分界点不在这条链上，显然子树外的答案取这个链的答案最优，子树内的答案直接求解与这条链相邻的子树内的答案即可，显然如果子树内的最优答案必然包含在与这条链相邻的子树内，这样每个点只会被插一次。
- 如果分界点在这条链上，考虑先钦定 $X$ 为根，从 $Y$ 向上扫一遍，不断插入点，求出其异或和最大值即为当前点的子树内答案。类似的，钦定 $Y$ 为根，从 $X$ 向上扫一遍，不断插点，同样也能求出其子树外的答案。

由于每个点只会被插一次，所以这样的话总时间复杂度为 $\mathcal O(n\log w)$。

有一点点小细节，写的时候注意一下就好了。然后就跑的比两只 $\log$ 还慢。。。

```c++
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define CI Cn int&
#define gc getchar
#define D isdigit(c=gc())
#define pc(c) putchar((c))
using namespace std;
namespace Debug{
	Tp I void _debug(Cn char* f,Ty t){cerr<<f<<'='<<t<<endl;}
	Ts I void _debug(Cn char* f,Ty x,Ar... y){W(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	Tp ostream& operator<<(ostream& os,Cn vector<Ty>& V){os<<"[";for(Cn auto& vv:V) os<<vv<<",";os<<"]";return os;}
	#define gdb(...) _debug(#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
namespace FastIO{
	Tp I void read(Ty& x){char c;int f=1;x=0;W(!D) f=c^'-'?1:-1;W(x=(x<<3)+(x<<1)+(c&15),D);x*=f;}
	Ts I void read(Ty& x,Ar&... y){read(x),read(y...);}
	Tp I void write(Ty x){x<0&&(pc('-'),x=-x,0),x<10?(pc(x+'0'),0):(write(x/10),pc(x%10+'0'),0);}
	Tp I void writeln(Cn Ty& x){write(x),pc('\n');}
}using namespace FastIO;
Cn int N=3e4+10;
int n,fir[N],nxt[N<<1],son[N<<1],w[N<<1],tot,F[N],Mx=-1,idx,idy,vis[N],G[N],P[N],dfn[N],bk[N],cnt,sz[N],Ans,in[N],out[N];
I void Add(CI x,CI y,CI z){nxt[++tot]=fir[x],fir[x]=tot,son[tot]=y,w[tot]=z;}
#define to son[i]
I void DFS(CI x,CI fa){RI i;for(i=fir[x];i;i=nxt[i]) to^fa&&(F[to]=F[x]^w[i],DFS(to,x),0);}
#define PA pair<int,int>
#define MP make_pair
class Trie{
	private:
		int ch[N*31][2],id[N*31],cnt;
	public:
		I void C(){RI i;for(i=0;i<=cnt;i++) ch[i][0]=ch[i][1]=id[i]=0;cnt=0;}
		I void U(CI x,CI dd){RI i,u=0;for(i=30;~i;i--) ch[u][x>>i&1]?u=ch[u][x>>i&1]:u=ch[u][x>>i&1]=++cnt;id[u]=dd;}
		I PA Q(CI x){RI i,u=0,X=0;for(i=30;~i;i--) ch[u][x>>i&1^1]?u=ch[u][x>>i&1^1],X|=1<<i:u=ch[u][x>>i&1];return MP(X,id[u]);}
}T;//Trie 树维护异或和最大值
I void dfs(CI x,CI fa){RI i;for(P[x]=fa,bk[dfn[x]=++cnt]=x,sz[x]=1,i=fir[x];i;i=nxt[i]) to^fa&&(F[to]=F[x]^w[i],dfs(to,x),sz[x]+=sz[to],0);}
I void GT(CI x){RI i,j;PA t;for(i=fir[x];i;i=nxt[i]) if(!vis[to]){for(j=dfn[to];j<=dfn[to]+sz[to]-1;j++) t=T.Q(F[bk[j]]),Ans=max(Ans,Mx+t.first),T.U(F[bk[j]],bk[j]);T.C();}}//分界点不在链上，求与链相邻子树答案
I void FG(CI x){RI i,j;PA t;for(t=T.Q(F[x]),in[x]=max(in[x],t.first),T.U(F[x],x),i=fir[x];i;i=nxt[i]) if(!vis[to]) for(j=dfn[to];j<=dfn[to]+sz[to]-1;j++) t=T.Q(F[bk[j]]),in[x]=max(in[x],t.first),T.U(F[bk[j]],bk[j]);}//分界点在链上，求子树内答案
I void FO(CI x){RI i,j;PA t;for(t=T.Q(F[x]),out[x]=max(out[x],t.first),T.U(F[x],x),i=fir[x];i;i=nxt[i]) if(!vis[to]) for(j=dfn[to];j<=dfn[to]+sz[to]-1;j++) t=T.Q(F[bk[j]]),out[x]=max(out[x],t.first),T.U(F[bk[j]],bk[j]);}//分界点在链上，求子树外答案
int main(){
	RI i,x,y,z,lst;PA t;for(read(n),i=1;i<n;i++) read(x,y,z),Add(x,y,z),Add(y,x,z);for(DFS(1,0),i=1;i<=n;i++) t=T.Q(F[i]),Mx<t.first&&(Mx=t.first,idx=t.second,idy=i),T.U(F[i],i);//先求出全局异或和最大点对
	for(F[idx]=0,dfs(idx,0),vis[idx]=1,i=idy;i!=idx;i=P[i]) vis[i]=1;for(T.C(),GT(idx),i=idy;i!=idx;i=P[i]) GT(i);for(i=idy;i!=idx;i=P[i]) FG(i);FG(idx),T.C();//分界点不在链上
	for(F[idy]=cnt=0,dfs(idy,0),i=idx;i!=idy;i=P[i]) FO(i);FO(idy);for(lst=0,i=P[idx];i!=idy;i=P[i]) Ans=max(Ans,in[i]+lst),lst=max(lst,out[i]);//分界点在链上合并子树内子树外
	return Ans=max(Ans,in[idy]+lst),writeln(Ans),0;
}
```

---

## 作者：heaksicn (赞：3)

给出一个不使用回滚莫队的纯分块做法。

首先考虑枚举一个点对 $(x,y)$ 的 lca，记为 $L$，如果另一个点对 $(u,v)$ 都不在都不在 $l$ 的子树内，那么 $E(x,y)$ 和 $E(u,v)$ 一定不交。

那么题目就变成如何求在一棵子树内和外分别取出一对点，使得两个点的路径的异或和最大。

将树通过 dfn 序拍到一个序列上，$L$ 的子树就变成了一个区间 $[l_L,r_L]$。那么问题就变成了：

- 求出区间 $[l,r]$ 的两个点，他们的异或和最大。

- 求出区间 $[1,l-1] \cup [r+1,n]$ 的两个点，他们的异或和最大。

转换到这里，我们考虑分块。令每一块的块长为 $B$。

对于每一个块 $j$，将块内的点全部压进 0-1 trie 里面。再对于每个点 $i$，求出它与块内所有点匹配的最大异或和，记为 $g_{i,j}$。

在这个基础上，可以求出在块 $i$ 和块 $j$ 中分别取出一个点的最大异或和,记为 $f_{i,j}$。

这部分的复杂度为 $O(nB\log V)$，其中 $V$ 是值域。

以询问的前一部分为例：

- 对于两个散块中的点匹配的答案，同样可以将这些点压进 0-1 trie 里面求。时间复杂度为 $O(B\log V)$。

- 对于一个散块中的点和和整块中的点匹配的答案，可以将 $g$ 压进线段树里面求出。时间复杂度为 $O(B\log \frac{n}{B})$。

- 对于两个整块中的点匹配的答案，同样可以将 $f$ 放到线段树里面求出。时间复杂度为 $O(\frac{n}{B}\log \frac{n}{B})$。

询问的第二部分同理。

所以询问总的复杂度为 $O(n(B\log V+B\log \frac{n}{B}+\frac{n}{B}\log \frac{n}{B}))$。

取 $B=\sqrt n$ 即可通过本题。

### code

```
//Man always remember love because of romance only!
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
struct edge{
	int to,nxt,w;
}e[60001];
int head[30001],cnt;
void add(int u,int v,int w){
	cnt++;
	e[cnt].to=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int dfn[30001],tot,a[30001],mx[30001],dep[30001];
void dfs(int x,int fa){
	dfn[x]=++tot;
	a[dfn[x]]=dep[x];
	mx[x]=dfn[x];
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		dep[v]=dep[x]^e[i].w;
		dfs(v,x);
		mx[x]=max(mx[x],mx[v]);
	}
}
int n,B;
int id[30001];
int f[201][201],g[30001][201];
int tr[30001][2],nw;
int fl[30001];
void insert(int x){
	int now=0;
	for(int i=30;i>=0;i--){
//		cout<<now<<" ";
		int tp=((x>>i)&1);
		if(!tr[now][tp]) tr[now][tp]=++nw;
		now=tr[now][tp];
	}
	fl[now]=x;
//	cout<<now<<" "<<x<<endl;
//	puts("");
}
int query(int x){
	if(nw==0) return x;
	int now=0,res=0;
	for(int i=30;i>=0;i--){
//		cout<<now<<" ";
		int tp=((x>>i)&1);
		if(tr[now][tp^1]!=0){
			now=tr[now][tp^1];
		}else{
			now=tr[now][tp];
		}
	}
//	cout<<now<<" "<<fl[now]<<endl;
	return fl[now];
}
int trg[30001][801];
void pushup(int x,int id){
	trg[id][x]=max(trg[id][x<<1],trg[id][x<<1|1]);
}
void build(int x,int l,int r,int id){
	if(l==r){
		trg[id][x]=g[id][l];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid,id);
	build(x<<1|1,mid+1,r,id);
	pushup(x,id);
}
int query(int x,int l,int r,int nl,int nr,int id){
	if(nl>nr) return 0;
	if(nl<=l&&nr>=r) return trg[id][x];
	int res=0,mid=(l+r)/2;
	if(mid>=nl) res=max(res,query(x<<1,l,mid,nl,nr,id));
	if(mid<nr) res=max(res,query(x<<1|1,mid+1,r,nl,nr,id));
	return res;
}
int trf[201][801];
void pushup2(int x,int id){
	trf[id][x]=max(trf[id][x<<1],trf[id][x<<1|1]);
}
void build2(int x,int l,int r,int id){
	if(l==r){
		trf[id][x]=f[id][l];
		return;
	}
	int mid=(l+r)/2;
	build2(x<<1,l,mid,id);
	build2(x<<1|1,mid+1,r,id);
	pushup2(x,id);
}
int query2(int x,int l,int r,int nl,int nr,int id){
	if(nl>nr) return 0;
	if(nl<=l&&nr>=r) return trf[id][x];
	int res=0,mid=(l+r)/2;
	if(mid>=nl) res=max(res,query2(x<<1,l,mid,nl,nr,id));
	if(mid<nr) res=max(res,query2(x<<1|1,mid+1,r,nl,nr,id));
	return res;
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
//	cout<<"complete cin\n";
	B=sqrt(n);
	for(int i=1;i<=n;i++) id[i]=(i-1)/B+1;
//	for(int i=1;i<=n;i++) cout<<dfn[i]<<" ";
//	puts("");
//	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
//	cout<<endl;
//	for(int i=1;i<=n;i++) cout<<id[i]<<" ";
//	cout<<endl;
	for(int i=1;i<=id[n];i++){
//		cout<<"i="<<i<<endl;
		for(int j=0;j<=nw;j++) tr[j][0]=tr[j][1]=0,fl[j]=0; 
		nw=0;
//		cout<<"l="<<(i-1)*B+1<<",r="<<min(i*B,n)<<endl;
		for(int j=(i-1)*B+1;j<=min(i*B,n);j++) insert(a[j]);
		for(int j=1;j<=n;j++){
//			if(id[j]==i) continue;
			g[j][i]=a[j]^query(a[j]);
			f[id[j]][i]=max(f[id[j]][i],g[j][i]);
		}
	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=id[n];j++) cout<<g[i][j]<<" ";
//		puts("");
//	}
//	cout<<"complete init\n";
	for(int i=1;i<=n;i++) build(1,1,id[n],i);
	for(int i=1;i<=id[n];i++) build2(1,1,id[n],i);
//	cout<<"complete building segment-tree\n";
	int ans=0;
	for(int x=1;x<=n;x++){
		int l=dfn[x],r=mx[x];
//		cout<<"l="<<l<<",r="<<r<<endl;
		for(int j=0;j<=nw;j++) tr[j][0]=tr[j][1]=0; 
		nw=0;
		int res=0;
		if(id[l]==id[r]){
			for(int i=l;i<=r;i++){
				insert(a[i]);
				res=max(res,a[i]^query(a[i]));
			}
		}else{
			for(int i=l;i<=id[l]*B;i++){
				insert(a[i]);
				res=max(res,a[i]^query(a[i]));
			}
			for(int i=(id[r]-1)*B+1;i<=r;i++){
				insert(a[i]);
				res=max(res,a[i]^query(a[i]));
			}
			int nl=id[l]+1,nr=id[r]-1;
			for(int i=l;i<=id[l]*B;i++) res=max(res,query(1,1,id[n],nl,nr,i));
			for(int i=(id[r]-1)*B+1;i<=r;i++) res=max(res,query(1,1,id[n],nl,nr,i));
			for(int i=nl;i<=nr;i++) res=max(res,query2(1,1,id[n],i+1,nr,i));
		}
		int res2=0;
		r=dfn[x]-1,l=mx[x]+1;
		for(int j=0;j<=nw;j++) tr[j][0]=tr[j][1]=0,fl[j]=0; 
		nw=0;
		int nl=id[l]+1,nr=id[r]-1;
		if(r<=0&&l>n){
			res2=-2e9;
		}else if(r<=0&&l<=n){
			for(int i=l;i<=min(id[l]*B,n);i++){
				insert(a[i]);
				res2=max(res2,a[i]^query(a[i]));
			}
			for(int i=l;i<=min(id[l]*B,n);i++) res2=max(res2,query(1,1,id[n],nl,id[n],i));
			for(int i=nl;i<=id[n];i++) res2=max(res2,query2(1,1,id[n],nl,id[n],i));
		}else if(r>0&&l>n){
			for(int i=(id[r]-1)*B+1;i<=r;i++){
				insert(a[i]); 
				res2=max(res2,a[i]^query(a[i]));
			}
			for(int i=(id[r]-1)*B+1;i<=r;i++) res2=max(res2,query(1,1,id[n],1,nr,i));
			for(int i=1;i<=nr;i++) res2=max(res2,query2(1,1,id[n],1,nr,i));
		}else{
			for(int i=l;i<=min(id[l]*B,n);i++){
				insert(a[i]);
				res2=max(res2,a[i]^query(a[i]));
			}
			for(int i=(id[r]-1)*B+1;i<=r;i++){
				insert(a[i]); 
				res2=max(res2,a[i]^query(a[i]));
			}
			for(int i=l;i<=min(id[l]*B,n);i++) res2=max(res2,max(query(1,1,id[n],1,nr,i),query(1,1,id[n],nl,id[n],i)));
			for(int i=(id[r]-1)*B+1;i<=r;i++) res2=max(res2,max(query(1,1,id[n],1,nr,i),query(1,1,id[n],nl,id[n],i)));
			for(int i=1;i<=nr;i++) res2=max(res2,max(query2(1,1,id[n],nl,id[n],i),query2(1,1,id[n],1,nr,i)));
			for(int i=nl;i<=id[n];i++) res2=max(res2,max(query2(1,1,id[n],1,nr,i),query2(1,1,id[n],nl,id[n],i)));
		}	
//		cout<<res<<" "<<res2<<endl;
		ans=max(ans,res+res2);
	}
	write(ans);
	return 0;
}


```


---

## 作者：NATO (赞：2)

有人考场上睡了 1.5h 后秒了 T4，但 T3 连断边都没想到，怎么回事呢？

### 思路浅析：

考虑如何刻画两条路径点集不交。

考虑若这两条路径就算有两个点相邻，我仍然可以断开中间那条边分离这两条路径。

故我们可以用“断开任意一条边后形成的两颗树中各选一条路径”来刻画两条路径点集不交（怎么有人没想到呢？）。

那么暴力枚举断边后问题就变成了求两棵树最大异或路径之和，树上最大异或路径是典，使用 trie 树即可在 $O(n\log w)$ 的时间复杂度内解决。

但是枚举边后复杂度就爆了，考虑优化。

注意到这两棵树为某一颗子树+砍掉这颗子树后的剩余部分的形式。

对于任意一颗子树内的最大异或路径，考虑树上启发式合并+trie 树即可。

剩下的部分考虑这样一个 trick：

考虑原树上最大异或路径 $(u,v)$，若砍掉的子树根节点上方的边不在 $(u,1)$ 和 $(v,1)$ 路径上，则答案显然为 $(u,v)$，否则考虑按深度扫过 $(1,u)$ 和 $(1,v)$，不断加入扫过的点不在 $(1,u)$ 和 $(1,v)$ 的子树即可。

由于每个点只加入+查询一次，故时间复杂度 $O(n\log w)$。

发现树上启发式合并+trie 树是双 $\log$，很不牛，考虑优化。

考虑到如果砍掉的边若不在 $(u,v)$ 上，那么让砍掉的子树尽可能大是优的，那么只需要考虑与 $(u,v)$ 相邻的那些极大子树即可，注意到每个点只属于一个极大子树，所以这部分是 $O(n\log w)$ 的。

否则可以发现砍掉的子树和砍掉这颗子树后的剩余部分是本质相同的，套用上面的 trick，从 $u$ 到 $v$，从 $v$ 到 $u$ 各扫一遍，把相邻位置上从两个方向扫得的最大值加起来即可。

故总时间复杂度 $O(n\log w)$。

#### 参考代码：


```cpp
#include<bits/stdc++.h>
#define ll int
using namespace std;
const ll N=500000,DEP=29;
ll n;
struct ed
{
	ll v,next,w;
}edge[N*2+5];
ll head[N+5],cnt;
void add(ll u,ll v,ll w)
{
	edge[++cnt].v=v;edge[cnt].next=head[u];head[u]=cnt;edge[cnt].w=w;
	edge[++cnt].v=u;edge[cnt].next=head[v];head[v]=cnt;edge[cnt].w=w;
}
struct trie
{
	struct tree
	{
		ll son[2],uid;
	}tr[(DEP+3)*N+5];
	#define ls(id) tr[id].son[0]
	#define rs(id) tr[id].son[1]
	#define son(id,where) tr[id].son[where]
	#define uid(id) tr[id].uid
	ll rt,cot,qid;
	void clear()
	{
		for(ll i=1;i<=cot;++i)ls(i)=rs(i)=uid(i)=0;
		rt=cot=0;
	}
	void insert(ll &id,ll dep,ll val,ll uid)
	{
		if(!id)id=++cot;
		uid(id)=uid;
		if(dep==-1)return;
		insert(son(id,(val>>dep)&1),dep-1,val,uid);
	}
	ll query(ll id,ll dep,ll val)
	{
		if(dep==-1)
		{
			qid=uid(id);return 0;
		}
		ll to=(((val>>dep)&1)^1);
		if(son(id,to))return query(son(id,to),dep-1,val)+(1<<dep);
		return query(son(id,to^1),dep-1,val);
	}
}tr;
ll f[N+5],dis[N+5];
ll maxn;
void dfs(ll id,ll fa,ll ok=0)
{
	if(ok>=0)
	tr.insert(tr.rt,DEP,dis[id],id);
	if(ok>=-1)
	f[id]=fa;
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v,w=edge[i].w;
		if(v==fa)continue;
		dis[v]=(dis[id]^w);
		dfs(v,id,ok);
	}
	if(ok==1)maxn=max(maxn,tr.query(tr.rt,DEP,dis[id]));
}
bool vis[N+5];
ll ans,mv,pre[N+5],suf[N+5];
void dfs2(ll id,ll fa)
{
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		if(v==fa)continue;
		if(vis[v])dfs2(v,id);
		else
		{
			tr.clear();
			dis[v]=maxn=0;
			dfs(v,id,1);
			ans=max(ans,maxn+mv);
		}
	}
}
void dfs3(ll id,ll fa)
{
	tr.insert(tr.rt,DEP,dis[id],id);
	pre[id]=pre[fa];
	pre[id]=max(pre[id],tr.query(tr.rt,DEP,dis[id]));
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		if(vis[v])continue;
		maxn=0;dis[v]=(dis[id]^edge[i].w);
		dfs(v,id,1);
		pre[id]=max(pre[id],maxn);
	}
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		if(v==fa)continue;
		if(vis[v])dfs3(v,id);
	}
}
void dfs4(ll id,ll fa)
{
	tr.insert(tr.rt,DEP,dis[id],id);
	suf[id]=suf[fa];
	suf[id]=max(suf[id],tr.query(tr.rt,DEP,dis[id]));
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		if(vis[v])continue;
		maxn=0;dis[v]=(dis[id]^edge[i].w);
		dfs(v,id,1);
		suf[id]=max(suf[id],maxn);
	}
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		if(v==fa)continue;
		if(vis[v])dfs4(v,id);
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	ll u,v,w;
	for(ll i=1;i<n;++i)cin>>u>>v>>w,add(u,v,w);
	dfs(1,0);
	ll maxn=-1,x,y;
	for(ll i=1;i<=n;++i)
	{
		ll res=tr.query(tr.rt,DEP,dis[i]);
		if(res>maxn)maxn=res,x=i,y=tr.qid;
	}
	dis[x]=0;
	dfs(x,0,-1);
	ll now=y;
	vis[y]=1;
	while(f[now])now=f[now],vis[now]=1;
	mv=maxn;
	dfs2(x,0);
	dis[x]=0;
	tr.clear();
	dfs3(x,0);
	tr.clear();dis[y]=0;
	dfs(y,0,-2);
	dfs4(y,0);
	now=y;
	while(f[now])
	ans=max(ans,pre[f[now]]+suf[now]),now=f[now];
	cout<<ans;
}
```

---

## 作者：qnqfff (赞：1)

### 思路

以 $1$ 为根，将每个点的点权设为到根链边权的异或和，容易发现一定存在一个点使得一条路径在这个点子树内，另一条路劲在子树外，设 $in_i$ 表示 $i$ 子树内选两个点的异或最大和，$out_i$ 表示 $i$ 子树外选两个点的异或最大和，则答案为 $\max\limits_{i\neq1}{in_i+out_i}$。

考虑怎么求 $in$，容易发现是 dsu on tree 板子，每次保留重儿子信息即可。

考虑怎么求 $out$，先找出全局异或最大的两个点 $u,v$，将 $u$ 和 $v$ 到根链标记，则没被标记的点的答案就是全局异或最大和，现在只剩下两条链了，直接暴力遍历这两条链求答案即可。

求异或最大和可以使用 trie。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int T,typ,n,dis[500010];vector<array<int,2>>e[500010];
struct TRIE{
	int tr[10000010][2],val[10000010],cnt;
	void clear(){for(int i=0;i<=cnt;i++) tr[i][0]=tr[i][1]=val[i]=0;cnt=0;}
	void ins(int x,int id){int u=0;for(int i=31;~i;i--){if(!tr[u][x>>i&1]) tr[u][x>>i&1]=++cnt;u=tr[u][x>>i&1];}val[u]=id;}
	array<int,2>query(int x){int u=0,res=0;for(int i=31;~i;i--){if(tr[u][x>>i&1^1]) res+=1ll<<i,u=tr[u][x>>i&1^1];else u=tr[u][x>>i&1];}return {res,val[u]};}
}trie;
struct IN{
	int f[500010],siz[500010],son[500010],dfn[500010],tim,id[500010],res[500010];
	void solve(){
		function<void(int,int)>dfs=[&](int u,int fa){f[u]=fa;siz[u]=1;son[u]=0;for(auto v:e[u]) if(v[0]^fa){dfs(v[0],u);siz[u]+=siz[v[0]];if(siz[v[0]]>siz[son[u]]) son[u]=v[0];}};dfs(1,0);
		function<void(int,int)>_dfs=[&](int u,int tp){id[dfn[u]=++tim]=u;if(son[u]) _dfs(son[u],tp);for(auto v:e[u]) if(v[0]^f[u]&&v[0]^son[u]) _dfs(v[0],v[0]);};tim=0;_dfs(1,1);
		function<void(int,int)>dsu=[&](int u,int opt){
			res[u]=0;for(auto v:e[u]) if(v[0]^f[u]&&v[0]^son[u]){dsu(v[0],0);res[u]=max(res[u],res[v[0]]);}if(son[u]){dsu(son[u],1);res[u]=max(res[u],res[son[u]]);}trie.ins(dis[u],u);res[u]=max(res[u],trie.query(dis[u])[0]);
			for(auto v:e[u]) if(v[0]^f[u]&&v[0]^son[u]){for(int i=dfn[v[0]];i<=dfn[v[0]]+siz[v[0]]-1;i++){trie.ins(dis[id[i]],id[i]); res[u]=max(res[u],trie.query(dis[id[i]])[0]);}}if(!opt) trie.clear();
		};dsu(1,0);
	}
}in;
struct OUT{
	int res[500010],f[500010],dep[500010],flg[500010];
	void solve(){
		array<int,3>mx={0,0,0};
		function<void(int,int)>dfs=[&](int u,int fa){
			trie.ins(dis[u],u);auto tmp=trie.query(dis[u]);if(tmp[0]>mx[0]) mx={tmp[0],u,tmp[1]};f[u]=fa;dep[u]=dep[fa]+1;
			for(auto v:e[u]) if(v[0]^fa) dfs(v[0],u);
		};dfs(1,0);
		function<void(int,int)>init=[&](int u,int opt){
			if(!(flg[u]&opt)&&u^1){trie.ins(dis[u],u);auto tmp=trie.query(dis[u]);if(tmp[0]>mx[0]) mx={tmp[0],u,tmp[1]};}else return ;
			for(auto v:e[u]) if(v[0]^f[u]) init(v[0],opt);
		};function<void(int,int)>upd=[&](int u,int opt){
			res[u]=mx[0];trie.ins(dis[u],u);auto tmp=trie.query(dis[u]);if(tmp[0]>mx[0]) mx={tmp[0],u,tmp[1]};
			for(auto v:e[u]) if(v[0]^f[u]&&flg[v[0]]^opt) init(v[0],opt);for(auto v:e[u]) if(v[0]^f[u]&&flg[v[0]]==opt) upd(v[0],opt);
		};int old=mx[0];for(int i=1;i<=n;i++) flg[i]=0;int u=mx[1];while(u^1) flg[u]=1,u=f[u];trie.clear();mx={0,0,0};upd(1,1);
		u=mx[2];while(u^1) flg[u]=2,u=f[u];trie.clear();mx={0,0,0};upd(1,2);for(int i=2;i<=n;i++) if(!flg[i]) res[i]=old;
	}
}out;
void solve(){
	n=read();for(int i=1;i<=n;i++) e[i].clear();for(int i=1;i<n;i++){int u=read(),v=read(),w=read();e[u].push_back({v,w});e[v].push_back({u,w});}
	function<void(int,int)>dfs=[&](int u,int fa){for(auto v:e[u]) if(v[0]^fa) dis[v[0]]=dis[u]^v[1],dfs(v[0],u);};dfs(1,0);
	trie.clear();in.solve();trie.clear();out.solve();int ans=0;for(int i=2;i<=n;i++) ans=max(ans,in.res[i]+out.res[i]);cout<<ans<<'\n';
}
signed main(){
    typ=0;T=1;while(T--) solve();
    return 0;
}
```

---

## 作者：Milthm (赞：1)

感谢 [Syx](https://www.luogu.com.cn/user/852144) 帮助我调题！

____

这题比较复杂，需要对异或、01-trie 和树的性质有较深的理解。

首先这个两条不相交路径一定不好做，所以转换一下，我们发现一定存在一个点，使得这两条路径一个在子树内，一个在子树外。

然后我们就把问题拆成了两个问题，分别处理之后合并就行了。

发现边权还是不好做，可以再转化一步，由异或的性质我们知道，一个数异或两遍是会变成 $0$ 的，所以一条路径 $(x,y)$ 的异或和就是 $(1,x)$ 异或上 $(1,y)$，于是我们把边权转化成了点权。

现在可以分类讨论了，在子树内的情况就是求子树内两点的最大异或和，我们发现我们可以很容易通过 01-trie 算出这个最大异或和，但是每次都要重新算一遍的话，复杂度肯定是会爆炸的。

解决方法是每次不重新算，把子树内的信息合并，也就是将子树的所有 01-trie 进行启发式合并，这样就可以快速得到根节点的信息。

至于在子树外的情况，和 [P8511 [Ynoi Easy Round 2021] TEST_68](https://www.luogu.com.cn/problem/P8511) 是完全一样的。我们发现如果求出了一条全局的最长异或路径，那么所有不包含这条路径的子树都可以用这个答案，而只有根节点到这两个点的两条链不符合这条要求。

所以对两条链再进行 dfs，从两个点往上递归，每次在递归之后向下计算答案，因为只有两条链所以时间复杂度是对的。

总时间复杂度 $O(n \log n \log V)$，$V$ 是值域，瓶颈在于启发式合并。


```cpp
#include<bits/stdc++.h>
#define N 30005
using namespace std;
int n,num,h[N],val[N],syx[N],srx[N];
int rr[N],vis[N],f[N],dep[N],siz[N],son[N];
int top[N],idx,w[N],dfn[N];
struct edge{
	int u,v,w,nxt;
}e[N*2];
void add(int u,int v,int w){
	e[++num]={u,v,w,h[u]};h[u]=num;
}
struct trie{
	int a[N<<6][2],cnt=1;
	int id[N<<6],mx=0,p=0,q=0,qwq=0;
	void clear(){
		for(int i=0;i<=cnt;++i)a[i][0]=a[i][1]=id[i]=0;cnt=1;p=q=mx=qwq=0;
	}
	void insert(int x){
		int u=1;
		for(int i=31;i>=0;--i){
			int ch=(val[x]>>i)&1;
			if(!a[u][ch])a[u][ch]=++cnt;
			u=a[u][ch];
		}
		id[u]=x;
	}
	void query(int x){
		int u=1,ans=0;
		for(int i=31;i>=0;--i){
			int ch=(val[x]>>i)&1;
			if(a[u][!ch])u=a[u][!ch],ans|=(1ll<<i);
			else u=a[u][ch];
		}
		qwq=ans;
		if(ans>mx){
			mx=ans;p=x,q=id[u];
		}
	}
}A;
void dfs1(int u,int fa){
	f[u]=fa;
	A.insert(u);A.query(u);
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==f[u]||v==fa)continue;
		val[v]=val[u]^e[i].w;
		dfs1(v,u);
	}
}
void dfs2(int u,int lst){
	if(!u)return;
	dfs2(f[u],u);
	rr[u]=A.mx;vis[u]=1;
	A.insert(u);A.query(u);
	if(u==lst)return;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=lst&&v!=f[u])dfs1(v,u);
	}
}
void solve1(){
	dfs1(1,0);
	int p=A.p,q=A.q;
	int maxn=A.mx;
	A.clear();dfs2(p,p);
	A.clear();dfs2(q,q);
	for(int i=1;i<=n;++i)syx[i]=(vis[i]?rr[i]:maxn);
	A.clear();
}
void dfs3(int u){
	dep[u]=dep[f[u]]+1;siz[u]=1;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==f[u])continue;
		dfs3(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs4(int u,int t){
	dfn[u]=++idx;w[idx]=u;
	if(!son[u])return;
	dfs4(son[u],t);
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==f[u]||v==son[u])continue;
		dfs4(v,v);
	}
}
void dfs5(int u,int cl){
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==f[u]||v==son[u])continue;
		dfs5(v,0);
		srx[u]=max(srx[u],srx[v]);
	}
	if(son[u])dfs5(son[u],1),srx[u]=max(srx[u],srx[son[u]]);
	A.query(u);srx[u]=max(srx[u],A.qwq);
	A.insert(u);
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==f[u]||v==son[u])continue;
		for(int j=dfn[v];j<=dfn[v]+siz[v]-1;++j){
			int vv=w[j];A.query(vv);
			srx[u]=max(srx[u],A.qwq);A.insert(vv);
		}
	}
	if(!cl)A.clear();
}
void solve2(){
	dfs3(1);dfs4(1,1);dfs5(1,0);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;++i){
		int u,v,w;cin>>u>>v>>w;
		add(u,v,w);add(v,u,w);
	}
	solve1();solve2();
	int ans=0;
	for(int i=2;i<=n;++i)ans=max(ans,syx[i]+srx[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

两个问题拼接的大杂烩，有点恶心。

考虑要求选出的两条路径不交，那么这两条路径是独立的，也就是说，选出的任意两个满足不交的合法的路径，肯定会出现对于某个节点而言，一条路径在它子树内，另一条在子树外。

来想想为什么是对的，对于某个在子树内的路径 $(a,b)$，如果还有一个路径也在子树内，由于他们不交的缘故，所以存在一个点为 $lca(a,b)$ 与 $lca(c,d)$ 中深度较大的满足条件。

那么我们就可以考虑枚举一个 $u$，钦定 $(a,b)$ 为在子树外的路径，$(c,d)$ 在子树内的路径。

于是原问题被拆分成了两个子问题，分别来做最后拼接即可。

我们发现，一条 $(x,y)$ 的路径的边权异或和可以被拆分成 $(x,1) \oplus (y,1)$，于是边权化为点权，每次求的即为 $a_x \oplus a_y$。$a_i$ 表示 $(i,1)$ 路径上的边权异或和。

对于在子树外的答案，我们考虑先忽略强制要求子树外这个条件，直接上 01 Trie 得出最大的答案，我们记答案为 $(x,y)$，则只有 $(x,1)$ 和 $(y,1)$ 的路径上无法使用这个答案，对于这么多分别按深度大小重做一遍 01 Trie 即可。

这么一部分其实就是 [P8511 [Ynoi Easy Round 2021] TEST_68](https://www.luogu.com.cn/problem/P8511)。

那么对于在子树内的答案，我们先求出每个节点在重链剖分下的重儿子，然后 dsu on tree 维护这么一个重儿子就好了。

子树外部分 $O(n \log V)$，子树内部分 $O(n \log n \log V)$，$V$ 是值域。

写的很长，将就看看。

```cpp
const int N = 3e4 + 19;
int n, fa[N], a[N], qwq[N], awa[N];
vector<pii> g[N];
namespace solve_out {
	int t[N << 5][2], id[N << 5], tot = 1, o[67], in[N], stk[N], top, now, ans[N];
	void insert(int x, int W) {
		int u = 1;
		int len = 31;
		for (int i = 0; i < 32; ++i) o[i] = 0;
		while (x) {
			o[len--] = x % 2;
			x >>= 1;
		}
		for (int i = 0; i < 32; ++i) {
			if (!t[u][o[i]]) t[u][o[i]] = ++tot;
			u = t[u][o[i]];
		}
		id[u] = W;
	}
	pii getmax(int x) {
		int u = 1, len = 31;
		for (int i = 0; i < 32; ++i) o[i] = 0;
		while (x) {
			o[len--] = x % 2;
			x >>= 1;
		}
		int ans = 0;
		for (int i = 0; i < 32; ++i) {
			ans *= 2;
			if (t[u][o[i] ^ 1]) ans += o[i] ^ 1, u = t[u][o[i] ^ 1];
			else ans += o[i], u = t[u][o[i]];
		}
		return {ans, id[u]};
	}
	void jump(int x) {
		while (x) {
			// test(x);
			in[x] = 1;
			stk[++top] = x;
			x = fa[x];
		}
	}
	void clear() {
		tot = 1;
		for (int i = 0; i < (N << 5); ++i) t[i][0] = t[i][1] = id[i] = 0;
	}
	void dfs(int u, int fa, int no) {
		insert(a[u], u);
		smax(now, getmax(a[u]).F ^ a[u]);
		for (auto [i,j] : g[u]) {
			if (i == fa || i == no) continue;
			dfs(i, u, no);
		}
	}
	void solve() {
		pii use; int mx = -1;
		for (int i = 1; i <= n; ++i) {
			insert(a[i], i);
			pii U = getmax(a[i]);
			if (mx < (a[i] ^ U.F)) {
				mx = a[i] ^ U.F;
				use = {i, U.S};
			}
		}
		clear();
		jump(use.F);
		now = -1;
		for (int i = top; i; --i) {
			ans[stk[i]] = now;
			smax(now, a[stk[i]] ^ getmax(a[stk[i]]).F);
			if (i ^ 1)dfs(stk[i], stk[i+1], stk[i-1]);
		} top = 0;
		clear();
		jump(use.S);
		now = -1; stk[top+1]=0;
		for (int i = top; i; --i) {
			ans[stk[i]] = now;
			smax(now, a[stk[i]] ^ getmax(a[stk[i]]).F);
			if (i ^ 1)dfs(stk[i], stk[i+1], stk[i-1]);
		} ans[1] = 0;
		for (int i = 1; i <= n; ++i) qwq[i] = (in[i] ? ans[i] : mx);
	}
};
namespace solve_in {
	int o[36], t[N << 5][2], tot = 1;
	void insert(int x) {
		int u = 1, len = 31;
		for (int i = 0; i < 32; ++i) o[i] = 0;
		while (x) {
			o[len--] = x % 2;
			x >>= 1;
		}
		for (int i = 0; i < 32; ++i) {
			if (!t[u][o[i]]) t[u][o[i]] = ++tot;
			u = t[u][o[i]];
		}
	}
	int getmax(int x) {
		int u = 1, len = 31;
		for (int i = 0; i < 32; ++i) o[i] = 0;
		while (x) {
			o[len--] = x % 2;
			x >>= 1;
		}
		int ans = 0;
		for (int i = 0; i < 32; ++i) {
			ans *= 2;
			if (t[u][o[i] ^ 1]) ans += o[i] ^ 1, u = t[u][o[i] ^ 1];
			else ans += o[i], u = t[u][o[i]];
		} return ans;
	}
	void clear() {
		for (int i = 0; i <= tot; ++i) t[i][0] = t[i][1] = 0;
		tot = 1;
	}
	int cnt, now[N], top[N], dep[N], siz[N], son[N], dfn[N];
	void dfs(int u, int f) {
		fa[u] = f; dep[u] = dep[f] + 1;
		siz[u] = 1;
		for (auto [i, j] : g[u]) {
			if (i == f) continue;
			dfs(i, u);
			siz[u] += siz[i];
			if (siz[i] > siz[son[u]]) son[u] = i;
		}
	}
	void dfs2(int u, int f) {
		top[u] = f;
		dfn[u] = ++cnt;
		now[cnt] = u;
		if (son[u]) dfs2(son[u], f);
		for (auto [i, j] : g[u]) if (i ^ fa[u] && i ^ son[u]) dfs2(i, i);
	}
	void getval(int u, bool k = 0) {
		for (auto [i,j] : g[u]) {
			if (i == son[u] || i == fa[u]) continue;
			getval(i);
			smax(awa[u], awa[i]); 
		}
		if (son[u]) getval(son[u], 1), smax(awa[u], awa[son[u]]);
		smax(awa[u], getmax(a[u]) ^ a[u]);
		insert(a[u]);
		for (auto [i,j] : g[u]) {
			if (i == son[u] || i == fa[u]) continue;
			for (int s = dfn[i]; s <= dfn[i] + siz[i] - 1; ++s) {
				int v = now[s];
				smax(awa[u], getmax(a[v]) ^ a[v]);
				insert(a[v]);
			}
		}
		if (!k) clear();
	}
	void solve() {
		dfs(1, 0), dfs2(1, 1);
		getval(1);
	}
};
void geta(int u, int val, int f = 0) {
	fa[u] = f;
	a[u] = val;
	for (auto [i,j]:g[u]) {
		if (i ^ f) {
			geta(i, val ^ j, u);
		}
	}
}
signed main() {
	read(n);
	for (int i = 1, u, v, w; i < n; ++i) {
		read(u, v, w);
		g[u].eb(v, w), g[v].eb(u, w);
	}
	geta(1,0);
	solve_out::solve();
	solve_in::solve();
	int A = 0;
	for (int i = 2; i <= n; ++i) smax(A, qwq[i] + awa[i]);
	write(A);
	return 0;
}
```

---

## 作者：creation_hy (赞：1)

显然不相交可以转化为子树内、外各选一条，前缀和后转化为两点的异或和，然后考虑分别怎么计算。

子树内 01Trie + 启发式合并就好了，先计算轻儿子，不在 Trie 上打标记，然后计算重儿子打标记，然后计算轻儿子打标记并计算前面子树对该子树的贡献，最后加入当前点。

子树外，考虑求出异或和最大的点对 $(x,y)$，那么对于不在 $1$ 到 $x$ 的链或 $1$ 到 $y$ 的链的根来说，该点对在子树外，答案即为最大值。剩下两条链的答案就很好求了，从 $1$ 往下 dfs，每次把该点父亲的其他儿子加入 01Trie 即可。

时间复杂度 $O(n\log n\log w)$

代码（启发式合并改标记换成 dfs 序可能好写一点）：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 6e4 + 5;
const int M = N << 5;
int n, head[N], to[N], nxt[N], val[N], fa[N], etot;
int vis[N], a[N], in[N], out[N];
inline void link(int u, int v, int w)
{
    to[etot] = v;
    val[etot] = w;
    nxt[etot] = head[u];
    head[u] = etot++;
}
struct Trie
{
    int t[M][2], id[M], sz[M], tot;
    inline void clear()
    {
        memset(t, 0, sizeof(t)), memset(sz, 0, sizeof(sz)), tot = 0;
    }
    inline void insert(int x, int pos, int w)
    {
        int p = 0;
        for (int i = 29; ~i; i--)
        {
            int c = x >> i & 1;
            if (!t[p][c])
                t[p][c] = ++tot;
            sz[p = t[p][c]] += w;
        }
        id[p] = pos;
    }
    inline pair<int, int> query(int x)
    {
        int p = 0, res = 0;
        for (int i = 29; ~i; i--)
        {
            int c = x >> i & 1;
            if (sz[t[p][c ^ 1]])
                p = t[p][c ^ 1], res |= 1 << i;
            else
                p = t[p][c];
        }
        return {res, id[p]};
    }
} tr;
inline void init(int x)
{
    for (int i = head[x]; ~i; i = nxt[i])
        if (to[i] != fa[x])
            fa[to[i]] = x, a[to[i]] = a[x] ^ val[i], init(to[i]);
}
namespace calc_in
{
    int sz[N], son[N];
    inline void dfs1(int x)
    {
        sz[x] = 1;
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] != fa[x])
            {
                dfs1(to[i]), sz[x] += sz[to[i]];
                if (sz[to[i]] > sz[son[x]])
                    son[x] = to[i];
            }
    }
    inline void solve(int x, int &ans)
    {
        ans = max(ans, tr.query(a[x]).first);
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] != fa[x])
                solve(to[i], ans);
    }
    inline void dye(int x)
    {
        tr.insert(a[x], x, 1);
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] != fa[x])
                dye(to[i]);
    }
    inline void undo(int x)
    {
        tr.insert(a[x], x, -1);
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] != fa[x])
                undo(to[i]);
    }
    inline void dfs2(int x)
    {
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] != fa[x] && to[i] != son[x])
                dfs2(to[i]), undo(to[i]), in[x] = max(in[x], in[to[i]]);
        if (son[x])
            dfs2(son[x]), in[x] = in[son[x]];
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] != fa[x] && to[i] != son[x])
                solve(to[i], in[x]), dye(to[i]);
        in[x] = max(in[x], tr.query(a[x]).first), tr.insert(a[x], x, 1);
    }
    inline void main()
    {
        tr.clear();
        dfs1(1), dfs2(1);
    }
}
namespace calc_out
{
    inline void dye(int x, int &ans)
    {
        ans = max(ans, tr.query(a[x]).first), tr.insert(a[x], x, 1);
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] != fa[x])
                dye(to[i], ans);
    }
    inline void dfs(int x)
    {
        out[x] = max(out[fa[x]], tr.query(a[fa[x]]).first), tr.insert(a[fa[x]], fa[x], 1);
        for (int i = head[fa[x]]; ~i; i = nxt[i])
            if (!vis[to[i]] && to[i] != fa[fa[x]])
                dye(to[i], out[x]);
        for (int i = head[x]; ~i; i = nxt[i])
            if (vis[to[i]] && to[i] != fa[x])
                dfs(to[i]);
    }
    inline void solve(int x)
    {
        tr.clear();
        memset(vis, 0, sizeof(vis));
        for (int p = x; p > 1; p = fa[p])
            vis[p] = 1;
        for (int i = head[1]; ~i; i = nxt[i])
            if (vis[to[i]])
                dfs(to[i]);
    }
    inline void main()
    {
        tr.clear();
        memset(out, -1, sizeof(out));
        int mx = 0, p1, p2;
        for (int i = 1; i <= n; i++)
        {
            auto t = tr.query(a[i]);
            if (t.first >= mx)
                mx = t.first, p1 = t.second, p2 = i;
            tr.insert(a[i], i, 1);
        }
        out[1] = 0, solve(p1), solve(p2);
        for (int i = 1; i <= n; i++)
            if (out[i] == -1)
                out[i] = mx;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof(head));
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, link(u, v, w), link(v, u, w);
    init(1), calc_in::main(), calc_out::main();
    int ans = 0;
    for (int i = 2; i <= n; i++)
        ans = max(ans, in[i] + out[i]);
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Tyyyyyy (赞：1)

# P6072

综合好题。考察了问题转化+01trie+树上回滚莫队。

### 题目分析

首先，我们提出一个结论：对于两条合法的路线，一定可以找到一个点 $u$，使得一条路径在以点 $u$ 为根的子树内，另一条在其子树外。

自己画图理解一下，上述结论不难证明。

于是，若我们将树用 dfs 序转为一个序列，设以点 $i$ 为根的子树对应的序列区间为 $[st_i,ed_i]$，则对于一个确定的点 $u$，我们可以知道两条路径的两个端点分别在 $[st_u,ed_u]$ 和 $[1,st_u)\cup(ed_u,n]$。

路径上的异或和显然可以转化为根到两节点路径的异或和互相异或的值。设根到点 $u$ 路径上的异或和为 $f_u$。

显然，子树内和子树外的问题是互不关联的。即我们只需要在子树内和子树外分别找到两个点 $u,v$，使得 $f_u \oplus f_v$ 最大即可。

发现上面的 $[1,st_u)\cup(ed_u,n]$ 其实可以转化。只要我们将序列复制一遍，这就是一个完整的区间。

于是，现在的问题就变为了：有 $n$ 个数 $f_1,f_2,\dots,f_n$，$2\times n$ 个询问，每次询问一段区间 $[l,r]$ 内的数中的 $\displaystyle\max_{x,y\in[l,r]}f_x\oplus f_y$。

考虑用莫队来维护区间，01trie 来寻找最大异或值。发现这样维护容易进行增加操作，而删除操作难以快速完成。于是用只增不删的回滚莫队+01trie 即可解决。

时间复杂度为 $O(n\sqrt{n}\log n)$。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e4+10;
int n,m,unit,tot,h[N],ans[N<<1];
struct edge
{
	int v,w,nxt;
}e[N<<1];
void add(int u,int v,int w)
{
	e[++tot]=(edge){v,w,h[u]};
	h[u]=tot;
}
int val[N],st[N],ed[N],id[N<<1],cnt;
void dfs(int u,int fa)
{
	id[st[u]=++cnt]=u;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		val[v]=val[u]^e[i].w;
		dfs(v,u);
	}
	ed[u]=cnt;
}
struct zero_one_trie
{
	int son[N<<5][2],siz[N<<5],sz;
	void insert(int a)
	{
		int cur=0;
		for(int i=30;i>=0;i--)
		{
			int u=a>>i&1;
			if(!son[cur][u])son[cur][u]=++sz;
			siz[cur=son[cur][u]]++;
		} 
	}
	void erase(int a)
	{
		int cur=0;
		for(int i=30;i>=0;i--)
		{
			int u=a>>i&1;
			siz[cur=son[cur][u]]--;
		} 
	}
	int query(int a)
	{
		int cur=0,res=0;
		for(int i=30;i>=0;i--)
		{
			int u=a>>i&1;
			if(son[cur][!u]&&siz[son[cur][!u]])cur=son[cur][!u],res=(res<<1)+!u;
			else cur=son[cur][u],res=(res<<1)+u;
		}
		return res^a;
	}
}trie,spe;
int L[N<<1],R[N<<1],pos[N<<1];
int res,Ans;
struct query
{
	int l,r,id;
	bool operator < (query b) const
	{
		if(pos[l]!=pos[b.l])return l<b.l;
		return r<b.r;
	} 
}q[N<<1];
int main()
{
	scanf("%d",&n);
	for(int i=1,x,y,w;i<n;i++)
		scanf("%d%d%d",&x,&y,&w),add(x,y,w),add(y,x,w);
	dfs(1,0);
	for(int i=2;i<=n;i++)
		q[++m]=(query){st[i],ed[i],m},q[++m]=(query){ed[i]+1,n+st[i]-1,m};
	for(int i=1;i<=n;i++)id[i+n]=id[i];
	n<<=1;
	int sz=n/(unit=max(1,(int)(n/sqrt(m))));
	for(int i=1;i<=sz;i++)L[i]=R[i-1]+1,R[i]=L[i]+unit-1;
	if(R[sz]<n)sz++,L[sz]=R[sz-1]+1,R[sz]=n;
	for(int i=1;i<=n;i++)pos[i]=(i-1)/unit+1;
	sort(q+1,q+m+1);
	for(int i=1,now=1,l,r;i<=sz;i++)
	{
		memset(trie.son,0,sizeof(trie.son));
		memset(trie.siz,0,sizeof(trie.siz));
		trie.sz=res=0,r=R[i];
		while(pos[q[now].l]==i)
		{
			if(q[now].r-q[now].l<=unit)
			{
				for(int i=q[now].l;i<=q[now].r;i++)
				{
					ans[q[now].id]=max(ans[q[now].id],spe.query(val[id[i]]));
					spe.insert(val[id[i]]);
				}
				for(int i=q[now].l;i<=q[now].r;i++)spe.erase(val[id[i]]);
			}
			else
			{
				l=R[i]+1;
				while(r<q[now].r)
					r++,res=max(res,trie.query(val[id[r]])),trie.insert(val[id[r]]);
				int tmp=res;
				while(l>q[now].l)
					l--,res=max(res,trie.query(val[id[l]])),trie.insert(val[id[l]]);
				ans[q[now].id]=res;
				res=tmp;
				while(l<R[i]+1)trie.erase(val[id[l]]),l++;
			}
			now++;
		}
	}
	for(int i=1;i<=m;i+=2)Ans=max(Ans,ans[i]+ans[i+1]);
	printf("%d",Ans);
	return 0;
}
```

---

## 作者：tzc_wk (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/P6072)

又是 ix35 神仙出的题，先以 mol 为敬 %%%

首先预处理出根节点到每个点路径上权值的异或和 $dis_i$，那么两点 $a,b$ 路径上权值的异或和显然为 $dis_a\oplus dis_b$。

我们考虑探究 $a,b$ 与 $c,d$ 间的路径不相交意味着什么。记 $l=lca(a,b)$，显然 $c,d$ 不能一个在 $l$ 子树内，一个在 $l$ 子树外，否则它们间的路径就会经过 $l$ 了。那么分两种情况，$c,d$ 全在 $l$ 子树外，和 $c,d$ 全在 $l$ 子树内。$c,d$ 全在子树外的情况显然好搞定，只要 $c,d$ 都在 $l$ 的子树外，那么 $a,b$ 与 $c,d$ 之间的路径就肯定不会相交。比较麻烦的是 $c,d$ 全在 $l$ 子树内的情况，记 $l'=lca(c,d)$，显然 $l'\neq l$，而 $c,d$ 都在 $l$ 子树内，故 $l'$ 也在 $l$ 子树内，如果我们交换 $(a,b)$ 和 $(c,d)$，那么可得 $c,d$ 的 lca 在 $a,b$ 的 lca $l'$ 的子树外，故第二种情况可以规约到第一种情况。所以我们只用考虑第一种情况就行了。

考虑枚举 $a,b$ 的 lca $l$，如果我们按照 DFS 序将原树展开成一个序列，那么相当于在 $[dfn_l,dfn_l+sz_l-1]$ 和 $[1,dfn_l-1]\cup[dfn_l+sz_l,n]$ 中分别选择两个数 $a,b$ 和 $c,d$ 使得 $dis_a\oplus dis_b+dis_c\oplus dis_d$ 最大。那么我们只用让它们分别最大即可。而如果我们令 $dfn_i=dfn_{i-n}(i>n)$，那么后面那个区间并又可写成 $[dfn_l+sz_l,dfn_l+n-1]$。于是现在题目转化为：给定一个序列 $a$，要求在 $[l,r]$ 中选择两个数 $a_i,a_j$，$a_i\oplus a_j$ 的最大值。首先可以肯定的是这东西没法用 DS 直接维护，而本题 3e4 的数据范围也在疯狂暗示本题的根号算法。故考虑莫队，建立一个 01-trie，插入某个数 $x$ 的时候就按照套路将其插入 01-trie，而本题的答案以取 $\max$ 出现的，不支持删除。故使用回滚莫队，扫到右端点的时候记录一个 $tmp$ 保存答案，解决一个询问之后就用临时保存的值还原答案即可。

时间复杂度 $n\sqrt{n}\log w$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=3e4;
const int SQRT=245;
const int LOG_N=30;
const int MAXP=1e6;
int n,hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],cst[MAXN*2+5],ec=0;
void adde(int u,int v,int w){to[++ec]=v;cst[ec]=w;nxt[ec]=hd[u];hd[u]=ec;}
int dis[MAXN+5],dfn[MAXN+5],ed[MAXN+5],id[MAXN+5],tim=0;
void dfs(int x,int f){
	dfn[x]=++tim;id[tim]=x;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e],z=cst[e];if(y==f) continue;
		dis[y]=dis[x]^z;dfs(y,x);
	} ed[x]=tim;
}
int blk_sz,blk_cnt,L[SQRT+5],R[SQRT+5],bel[MAXN*2+5];
int w[MAXN*2+5];
struct query{
	int l,r,id;
	bool operator <(const query &rhs){
		if(bel[l]!=bel[rhs.l]) return l<rhs.l;
		return r<rhs.r;
	}
} q[MAXN*2+5];
int ch[MAXP+5][2],siz[MAXP+5],ncnt=0;
void insert(int x,int v){
	int cur=0;
	for(int i=LOG_N;~i;i--){
		int d=x>>i&1;
		if(!ch[cur][d]) ch[cur][d]=++ncnt;
		cur=ch[cur][d];siz[cur]+=v;
	}
}
int query(int v){
	int x=0,cur=0;
	for(int i=LOG_N;~i;i--){
		int d=v>>i&1;
		if(siz[ch[cur][d^1]]) x|=1<<i,cur=ch[cur][d^1];
		else cur=ch[cur][d];
	} return x;
}
int ans=0,res[MAXN+5];
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		adde(u,v,w);adde(v,u,w);
	} dfs(1,0);
	for(int i=1;i<=n;i++) w[i]=dis[id[i]];
	for(int i=n+1;i<=n*2;i++) w[i]=w[i-n];
//	for(int i=1;i<=n*2;i++) printf("%d\n",w[i]);
	blk_sz=(int)sqrt(2*n);blk_cnt=(2*n-1)/blk_sz+1;
	for(int i=1;i<=blk_cnt;i++){
		L[i]=(i-1)*blk_sz+1;
		R[i]=min(i*blk_sz,2*n);
		for(int j=L[i];j<=R[i];j++) bel[j]=i;
	}
	for(int i=2;i<=n;i++){
		q[i-1].l=dfn[i];q[i-1].r=ed[i];q[i-1].id=i;
		q[i+n-2].l=ed[i]+1;q[i+n-2].r=dfn[i]+n-1;q[i+n-2].id=i;
//		printf("%d %d %d\n",dfn[i],ed[i],i);
//		printf("%d %d %d\n",ed[i]+1,dfn[i]+n-1,i); 
	} sort(q+1,q+(n<<1)-1);int cl=1,cr=0;
//	for(int i=1;i<=(n<<1)-2;i++) printf("%d %d %d\n",q[i].l,q[i].r,q[i].id);
	for(int i=1;i<=(n<<1)-2;i++){
		if(i==1||bel[q[i].l]!=bel[q[i-1].l]){
			cl=R[bel[q[i].l]]+1;cr=cl-1;
			memset(siz,0,sizeof(siz));memset(ch,0,sizeof(ch));
			ncnt=0;ans=0;
		}
		if(bel[q[i].l]==bel[q[i].r]){
			int mx=-0x3f3f3f3f;
			for(int j=q[i].l;j<=q[i].r;j++) insert(w[j],1);
			for(int j=q[i].l;j<=q[i].r;j++) mx=max(mx,query(w[j]));
			for(int j=q[i].l;j<=q[i].r;j++) insert(w[j],-1);
			res[q[i].id]+=mx;continue;
		}
		while(cr<q[i].r) insert(w[++cr],1),ans=max(ans,query(w[cr]));
		int tmp=ans;
		while(cl>q[i].l) insert(w[--cl],1),ans=max(ans,query(w[cl]));
		res[q[i].id]+=ans;
		while(cl<R[bel[q[i].l]]+1) insert(w[cl++],-1);
		ans=tmp;
	} int mx=0;
	for(int i=1;i<=n;i++) chkmax(mx,res[i]);
	printf("%d\n",mx);
	return 0;
}
```



---

## 作者：南阳刘子骥 (赞：1)

题目要求我们从一棵树中选出两条互不相交的简单路径，使得其边权异或和之和最大。

首先我们可以将不好维护的边权异或和转化为路径两端点到根的这两条路径上的边权异或和。

然后就是考虑如何不重不漏地找到这两条路径。  
可以想到边分治，用当前的分治中心来分开两条路径。但是两条路径的其中一条可能会穿过上层的分治中心，导致维护困难，可以pass掉。

可以想到对于每一个点，分别求出子树内的最大路径和子树外的最大路径，发现可行。

维护子树外的最大路径可以参考[P8511](https://www.luogu.com.cn/problem/P8511)这道Ynoi，提供了一种 $O(n \log v)$ 的、利用支配性质的做法，其中 $v$ 是值域。

对于子树内的做法，我们也可以利用支配的性质。  
我们首先找到异或和最大的两个点 $x$ 和 $y$，考虑 $a_x \oplus a_y$ 对答案的贡献。

- 对于 $x$ 和 $y$ 都在子树内的，子树内答案就是 $a_x \oplus a_y$。这一条适用于从 $\operatorname{lca}(x,y)$ 向上到根的这一条路径上的点。
- 对于 $x$ 和 $y$ 都不在子树内的，子树外答案就是 $a_x \oplus a_y$，子树内答案就需要单独计算并取较大值即可。其中我们可以利用贪心策略，对于一棵子树，我们只需要计算其根的子树内答案即可。这一条适用于所有不在 $x$ 到根或 $y$ 到根路径上的子树。
- 对于 $x$ 和 $y$ 两者中只有一个在子树中的，我们也需要单独计算其子树内答案。这一条适用于 $x$ 到 $\operatorname{lca}(x,y)$ 再到 $y$ 这两条路径上的点。

分析一下时间复杂度：

首先子树外的答案是 $O(n \log v)$ 的。  
其次，子树内的答案的三部分我们分别分析：
- 第一部分直接统计 $O(n)$；
- 第二部分，我们只对于每一棵极大子树的根节点统计答案，那么这棵子树内的每一个节点只会被插入一次，总共就只会插入 $O(n)$ 级别的节点，复杂度 $O(n \log v)$；
- 第三部分，我们可以对于两条路径分别从下往上统计答案，此时我们只需要插入操作即可统计，总共也只会插入 $O(n)$ 级别的节点，复杂度 $O(n \log v)$。
所以总复杂度是 $O(n \log v)$。

代码如下：
``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 30010, M = N << 1;
struct Trie
{
    struct Node
    {
        int s[2];
        int end;
    };
    Node tr[N * 30];
    int idx;
    void clear()
    {
        for(int i = 0; i <= idx; i++)
            tr[i].s[0] = tr[i].s[1] = tr[i].end = 0;
        idx = 0;
    }
    void insert(int x, int id)
    {
        int p = 0;
        for(int i = 29; i >= 0; i--)
        {
            int c = (x >> i) & 1;
            if(!tr[p].s[c])tr[p].s[c] = ++idx;
            p = tr[p].s[c];
        }
        tr[p].end = id;
    }
    int query(int x)
    {
        int p = 0;
        for(int i = 29; i >= 0; i--)
        {
            int c = (x >> i) & 1;
            if(tr[p].s[c ^ 1])p = tr[p].s[c ^ 1];
            else if(tr[p].s[c])p = tr[p].s[c];
            else return 0;
        }
        return tr[p].end;
    }
};

int n;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
int a[N], ans[N];
Trie tr;
int l1, l2; int maxn;
int dep[N], fa[N], deg[N];
bool tag[N];
void dfs1(int p, int fa, int v)
{
    dep[p] = dep[fa] + 1, ::fa[p] = fa, a[p] = v;
    for(int i = h[p]; ~i; i = ne[i])
    {
        if(e[i] == fa)continue;
        dfs1(e[i], p, v ^ w[i]);
    }
}
int lca(int p, int q)
{
    if(dep[p] < dep[q])swap(p, q);
    tag[p] = tag[q] = true;
    while(dep[p] > dep[q])p = fa[p], tag[p] = true;
    if(p == q)return p;
    while(p != q)p = fa[p], q = fa[q], tag[p] = tag[q] = true;
    return p;
}
int sta[N], tt;
bool vis[N];
void dfs2(int p, int fa)
{
    tr.insert(a[p], p);
    int q = tr.query(a[p]);
    if((a[p] ^ a[q]) > maxn)maxn = a[p] ^ a[q];
    for(int i = h[p]; ~i; i = ne[i])
    {
        if(e[i] == fa || vis[e[i]])continue;
        dfs2(e[i], p);
    }
}
void solve(int p, int q)
{
    if(p == q)return;
    if(dep[p] < dep[q])swap(p, q);
    tt = 0;
    while(p != q)sta[++tt] = p, vis[p] = true, p = fa[p];
    tr.clear(), maxn = 0;
    dfs2(1, 0);
    for(int i = tt; i; i--)
    {
        ans[sta[i]] = maxn;
        dfs2(sta[i], fa[sta[i]]);
        vis[sta[i]] = false;
    }
}
int res = 0;
int main()
{
    memset(h, -1, sizeof(h));
    scanf("%d", &n);
    bool flag = true;
    for(int i = 1; i < n; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w), add(v, u, w);
        deg[u]++, deg[v]++;
        if(deg[u] > 2 || deg[v] > 2)flag = false;
    }
    dfs1(1, 0, 0);
    tr.clear(), maxn = 0;
    for(int i = 1; i <= n; i++)
    {
        tr.insert(a[i], i);
        int j = tr.query(a[i]);
        if((a[i] ^ a[j]) > maxn)l1 = j, l2 = i, maxn = a[i] ^ a[j];
    }
    //求子树外的答案
    int g = lca(l1, l2);
    for(int i = g; i >= 1; i = fa[i])tag[i] = true;
    for(int i = 2; i <= n; i++)
        if(!tag[i])ans[i] = maxn;
    solve(1, l1), solve(g, l2);
    //一条链且x到y是整条链的特殊情况
    if(flag && deg[l1] == 1 && deg[l2] == 1)
    {
        tr.clear(), maxn = 0;
        if(deg[l2] < deg[l1])swap(l1, l2);
        for(int i = l2; i != l1; i = fa[i])
        {
            tr.insert(a[i], i);
            int j = tr.query(a[i]);
            if((a[i] ^ a[j]) > maxn)maxn = a[i] ^ a[j];
            res = max(res, ans[i] + maxn);
        }
        printf("%d\n", res);
        return 0;
    }
    //x与y均在子树内的点
    for(int i = g; i >= 1; i = fa[i])
        res = max(res, ans[i] + (a[l1] ^ a[l2]));
    //x与y均在子树外的点
    queue<int>q;
    for(int i = l1; i != g; i = fa[i])
    {
        for(int j = h[i]; ~j; j = ne[j])
            if(!tag[e[j]])q.push(e[j]);
    }
    for(int i = l2; i != g; i = fa[i])
    {
        for(int j = h[i]; ~j; j = ne[j])
            if(!tag[e[j]])q.push(e[j]);
    }
    for(int i = h[g]; ~i; i = ne[i])
        if(!tag[e[i]])q.push(e[i]);
    for(int i = 1; i <= n; i++)vis[i] = false;
    while(!q.empty())
    {
        tr.clear(), maxn = 0;
        dfs2(q.front(), fa[q.front()]);
        res = max(res, maxn + (a[l1] ^ a[l2]));
        q.pop();
    }
    res = max(res, maxn + (a[l1] ^ a[l2]));
    //x到y路径上的点
    tr.clear(), maxn = 0;
    for(int i = 1; i <= n; i++)vis[i] = false;
    for(int i = l1; i != fa[g]; i = fa[i])
    {
        dfs2(i, fa[i]);
        vis[i] = true;
        res = max(res, maxn + ans[i]);
    }
    tr.clear(), maxn = 0;
    for(int i = 1; i <= n; i++)vis[i] = false;
    for(int i = l2; i != fa[g]; i = fa[i])
    {
        dfs2(i, fa[i]);
        vis[i] = true;
        res = max(res, maxn + ans[i]);
    }

    printf("%d\n", res);
    return 0;
}
```

---

## 作者：int08 (赞：0)

## 前言
我能在得了痴呆症的情况下通过这道题目吗？

# Solution
由于两条链不交，总是能找到一条边使得两条链在这条边的两侧，枚举这条边。

然后简单做一个树上差分，现在题目变为：

给一棵树，点带权，对每个 $i\in[1,n]$，求出 $i$ 子树内选两点的异或最大值和 $i$ 子树外选两点的异或最大值。

首先一个集合求选两数异或最大值显然用 `0-1 Trie` 来做支持一个一个加入并动态维护答案，所以对于前者，显然可以使用 dsu on tree 的技巧配合 `0-1 Trie` 做到 $O(n\log n\log w)$。

子树外咋办啊？似乎这个最大值不太支持删除的动态维护。

考虑上 [P7124](https://www.luogu.com.cn/problem/P7124)（子树补集不删除莫队）的 Trick，就可以也在 $O(n\log n\log w)$ 时间内解决。

不过重剖然后哈夫曼树长作不可写状，故使用[那道题第一篇题解](https://www.luogu.com.cn/article/061zkdcu)分治做法，前面的子树内也改用分治解决。

最终复杂度 $O(n\log n\log w)$。
## AC Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mx=(1<<30)-1;
#define N 514514
#define vep vector<pair<int,int> >
int rt,ls[N*61],rs[N*61],val[N*61],cnt;
#define mid (l+r>>1)
#define ca rt,0,mx
void change(int &o,int l,int r,int x,int v)
{
	if(!o) o=++cnt;
	val[o]+=v;
	if(l==r) return;
	if(x<=mid) change(ls[o],l,mid,x,v);
	if(x>mid) change(rs[o],mid+1,r,x,v);
}
int ask(int o,int l,int r,int x)
{
	if(!val[o]) return 0;
	if(l==r) return l^x;
	int b=(r-l+1)/2;
	if((x&b)&&val[ls[o]]||!(x&b)&&!val[rs[o]]) return ask(ls[o],l,mid,x);
	else return ask(rs[o],mid+1,r,x);
}
vector<pair<int,int> > ed[N];
int va[N],sz[N],dfn[N],df,nfd[N];
int n,i,T;
vep q1,q2;
void dfs(int u,int fa)
{
	sz[u]=1;
	dfn[u]=++df;nfd[df]=u;
	for(auto x:ed[u]) if(x.first!=fa)
	{
		int v=x.first,w=x.second;
		va[v]=va[u]^w;
		dfs(v,u);
		sz[u]+=sz[v]; 
	}
	q1.push_back({dfn[u],dfn[u]+sz[u]-1});q2.push_back({dfn[u],dfn[u]+sz[u]-1});
}
int ans1[N],ans2[N],ans;
#undef mid
void solve1(vep q,int l,int r)
{
	if(!q.size()) return;
	if(l==r)
	{
		ans1[nfd[l]]=ans;
		return;
	}
	int mid=(l+r)>>1;
	vep lq,rq;
	lq.clear(),rq.clear();
	int lp=l-1,rp=r+1;
	int anb=ans;
	for(auto x:q)
	{
		if(x.first>mid) rq.push_back(x);
		else if(x.second<=mid) lq.push_back(x);
		else
		{
			while(lp<x.first-1) change(ca,va[nfd[++lp]],1),ans=max(ans,ask(ca,va[nfd[lp]]));
			while(rp>x.second+1) change(ca,va[nfd[--rp]],1),ans=max(ans,ask(ca,va[nfd[rp]]));
			ans1[nfd[lp+1]]=ans;
		}
	}
	while(lp>=l) change(ca,va[nfd[lp--]],-1);
	while(rp<=r) change(ca,va[nfd[rp++]],-1);
	ans=anb;
	while(lp<mid) change(ca,va[nfd[++lp]],1),ans=max(ans,ask(ca,va[nfd[lp]]));
	solve1(rq,mid+1,r);
	while(lp>=l) change(ca,va[nfd[lp--]],-1);
	ans=anb;
	while(rp>mid+1) change(ca,va[nfd[--rp]],1),ans=max(ans,ask(ca,va[nfd[rp]]));
	solve1(lq,l,mid);
	while(rp<=r) change(ca,va[nfd[rp++]],-1);
	ans=anb;
	lq.clear(),rq.clear(),q.clear();
}
void solve2(vep q,int l,int r)
{
	if(!q.size()) return;
	if(l==r)
	{
		ans2[nfd[l]]=ans=0;
		return;
	}
	int mid=(l+r)>>1;
	vep lq,rq;
	lq.clear(),rq.clear();
	int lp=mid+1,rp=mid,ans=0;
	for(auto x:q)
	{
		if(x.first>mid) rq.push_back(x);
		else if(x.second<=mid) lq.push_back(x);
		else
		{
			while(rp<x.second) change(ca,va[nfd[++rp]],1),ans=max(ans,ask(ca,va[nfd[rp]]));
			while(lp>x.first) change(ca,va[nfd[--lp]],1),ans=max(ans,ask(ca,va[nfd[lp]]));
			ans2[nfd[lp]]=ans;
		}
	}
	while(lp<=mid) change(ca,va[nfd[lp++]],-1);
	while(rp>mid) change(ca,va[nfd[rp--]],-1);
	ans=0;
	solve2(rq,mid+1,r);
	solve2(lq,l,mid);
	lq.clear(),rq.clear(),q.clear();
}
int op;
int main()
{
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	T=1;
	while(T--)
	{
		cin>>n;
		for(i=1;i<n;i++)
		{
			int u,v,w;
			cin>>u>>v>>w;
			ed[u].push_back({v,w}),ed[v].push_back({u,w}); 
		}
		dfs(1,0);
		sort(q1.begin(),q1.end());
		sort(q2.begin(),q2.end());reverse(q2.begin(),q2.end());
		solve1(q1,1,n);
		solve2(q2,1,n);
		int ann=0;
		for(i=2;i<=n;i++) ann=max(ann,ans1[i]+ans2[i]);
		cout<<ann<<endl;
		for(i=0;i<=n;i++) ans1[i]=ans2[i]=ans=va[i]=sz[i]=dfn[i]=df=nfd[i]=0,ed[i].clear();
		q1.clear(),q2.clear();
		for(i=0;i<=cnt;i++) ls[i]=rs[i]=val[i]=0;cnt=rt=0;
	}
}
```
# The End.

---

## 作者：Raisen_zx (赞：0)

这是一份 $O(n\log n \log W)$ 的做法的奇怪实现，纯靠 0/1Trie 合并与 dsu on tree。

定 1 号点为根，对于两条不交路径，我们可以化成一个点子树内的路径和子树外的路径。

对于子树内的我们考虑 dsu on tree，每次背包式的合并。

对于子树外部的，我们考虑找一条异或值最大的路径 $(x,y)$，此时只有 $(1,x)$ 与 $(1,y)$ 的点不会把这条路径加入答案，对这些点打上标记， 深搜时对于有标记的儿子计算答案。

然后我们惊奇地发现：只有一个点会有两个打标记的儿子（其实废话），除了这个点要复制一棵 0/1Trie 对两个儿子分讨以外，其他的点只需要把除了打标记的儿子以外的子树加入后下传到仅有的一个儿子那里，所以可持久化直接就不需要了。

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#define ls(p) tr[(p)].son[0]
#define rs(p) tr[(p)].son[1]
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
using namespace std;
typedef long long ll;
char buf[1<<20],*p1=buf,*p2=buf;
template<typename type>
inline void read(type &x)
{
    x=0;bool flag=0;char ch=gc();
    while(!isdigit(ch)) flag=ch=='-',ch=gc();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=gc();
    flag?x=-x:0;
}
const int MAXN=3e4+100;
int n,head[MAXN],rt[MAXN],son[MAXN],siz[MAXN],fa[MAXN],idx,cnte,dfn[MAXN],pdfn;
ll pre[MAXN],in[MAXN],out[MAXN];
int dfnx[MAXN],tmpo,x,y,stk[10],tail;
ll ans;
struct Edge
{
    int to,nxt;
	ll val;
}e[MAXN<<1];
struct Trie
{
    int son[2],ed;
}tr[MAXN*80];
bool vis[MAXN];
inline void link(int u,int v,ll w)
{
    e[++cnte]={v,head[u],w};
    head[u]=cnte;
}
void dfs1(int u,int fth)
{
    fa[u]=fth,siz[u]=1;
    for(int i=head[u],v;i;i=e[i].nxt)
    {
        v=e[i].to;
        if(v==fth) continue;
        pre[v]=pre[u]^e[i].val;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
        
    }
}
inline void insert(int p,ll v)
{
    int tmp=p;
    p=rt[p];
    for(ll i=32;i>=0;--i)
    {
        ll d=(v>>i)&1;
        if(!tr[p].son[d]) tr[p].son[d]=++idx;
        p=tr[p].son[d];
    }
    tr[p].ed=tmp;
}
inline ll find(int p,ll v)
{
    ll res=0;
    for(ll i=32ll;i>=0ll;--i)
    {
        int d=(v>>i)&1ll;
        if(tr[p].son[d^1]) d^=1;
        p=tr[p].son[d];
        res|=(1ll*d)<<i;
    }
    return v^res;
}
inline int find_id(int p,ll v)
{
    for(ll i=32;i>=0;--i)
    {
        int d=(v>>i)&1;
        if(tr[p].son[d^1]) d^=1;
        p=tr[p].son[d];
    }
    return tr[p].ed;
}
int merge(int u,int v)
{
    if(!u||!v) return u|v;
    ls(u)=merge(ls(u),ls(v));
    rs(u)=merge(rs(u),rs(v));
    return u;
}
void calc(int u)
{
    dfnx[++pdfn]=u;
    dfn[u]=pdfn;
    if(son[u]) calc(son[u]);
    for(int i=head[u],v;i;i=e[i].nxt)
    {
        v=e[i].to;
        if(v!=son[u]&&v!=fa[u]) calc(v);
    }
}
void dfs2(int u)
{
    rt[u]=++idx;
    insert(u,pre[u]);
    if(son[u])
    {
        dfs2(son[u]);
        in[u]=max(in[son[u]],find(rt[son[u]],pre[u]));
        rt[u]=merge(rt[u],rt[son[u]]);
    }
    for(int i=head[u],v;i;i=e[i].nxt)
    {
        v=e[i].to;
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v);
        in[u]=max(in[u],in[v]);
        for(int j=dfn[v];j<=dfn[v]+siz[v]-1;++j)
        {
            int k=dfnx[j];
            in[u]=max(in[u],find(rt[u],pre[k]));
        }
        rt[u]=merge(rt[u],rt[v]);
    }
}
inline void bj(int u)
{
    while(u) vis[u]=1,u=fa[u];
}
void copy(int x,int &y)
{
    y=++idx;
    if(ls(x)) copy(ls(x),ls(y));
    if(rs(y)) copy(rs(x),rs(y));
}
void solve(int u)
{
    tail=0;
    if(!vis[u]) return;
    ll tmp=out[u];
    if(u!=1)
    {
        tmp=max(tmp,find(rt[u],pre[u]));
    }
    insert(u,pre[u]);
    for(int i=head[u],v;i;i=e[i].nxt)
    {
        v=e[i].to;
        if(v==fa[u]) continue;
        else if(vis[v])
        {
            stk[++tail]=v;
        }
        else{
            for(int j=dfn[v],k;j<=dfn[v]+siz[v]-1;++j)
            {
                k=dfnx[j];
                tmp=max(tmp,find(rt[u],pre[k]));
            }
            rt[u]=merge(rt[u],rt[v]);
        }
    }
    if(tail==1)
    {
        rt[stk[1]]=rt[u];
        out[stk[1]]=tmp;
        solve(stk[1]);
    }
    if(tail==2)
    {
        int tmp1=rt[stk[1]],tmp2=rt[stk[2]];
        out[stk[1]]=tmp,out[stk[2]]=tmp;
        for(int i=1;i<=2;++i)
        {
            int t=stk[3-i];
            for(int j=dfn[t],k;j<=dfn[t]+siz[t]-1;++j)
            {
                k=dfnx[j];
                out[stk[i]]=max(out[stk[i]],find(rt[u],pre[k]));
            }
        }
        rt[stk[1]]=rt[u];
        copy(rt[stk[1]],rt[stk[2]]);
        rt[stk[1]]=merge(rt[stk[1]],tmp2);
        rt[stk[2]]=merge(rt[stk[2]],tmp1);
        solve(stk[1]);
        solve(stk[2]);
    }
}
int main()
{
    read(n);
    for(int i=1,a,b,w;i<n;++i)
    {
        read(a),read(b),read(w);
        link(a,b,w),link(b,a,w);
    }
    dfs1(1,0);
    calc(1);
    dfs2(1);
    for(int i=1;i<=n;++i)
    {
        int tmp=find(rt[1],pre[i]);
        if(tmp>tmpo) tmpo=tmp,x=i,y=find_id(rt[1],pre[i]);
    }
    bj(x),bj(y);
    for(int i=2;i<=n;++i) if(!vis[i]) out[i]=tmpo;
    rt[1]=++idx;
    solve(1);
    for(int i=2;i<=n;++i) ans=max(ans,in[i]+out[i]);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

[传送门](https://www.luogu.com.cn/problem/P6072)。

题目大意：求两条不相交路径的最大异或和。

首先，路径 $(u,v)$ 的异或和就相当于其到根亦或之和的前缀数组 $a$ 亦或之和，即 $a_u \oplus  a_v$。

把两条路径拆开，一条在子树内，一条在子树外。

令 $d_x= \max\limits_{u,v \in sub(x)} a_u \oplus a_v,g_x= \max\limits_{u,v \notin sub(x)} a_u \oplus a_v$

题目等价于求 $\max\limits_{i=1}^{n} (d_i+g_i)$。

首先，考虑求 $d_i$。

先不考虑子树外的限制，可以先求出全局最大的 $a_u \oplus a_v$，把点对 $(u,v)$ 记录下来。

容易发现，除了在 $(1,u)$ 或者 $(1,v)$ 路径上的点，$d_i$ 答案都是一样的为 $a_u \oplus a_v$。

所以只用对这两个点到根的路径上节点求 $d_i$。

分开考虑，从 $1$ 节点到 $v$ 节点 dfs 时，先遍历一个点所有除了包含路径的子树，把所有点插入 01Trie，最后再遍历包含路径的那棵子树。

这样就可以求出来每个点的 $d_i$。

code：
```cpp
inline void dfs(int x){
	T.ins(rt,a[x],31);tmp=max(tmp,T.qry(rt,a[x],31));
	for(int y:ed[x]) if(y!=fa[x]) dfs(y);
}
inline void solve1(int x,int son){
	if(x==0) return;f[x]=1;
	solve1(fa[x],x);d[x]=tmp;
	T.ins(rt,a[x],31);tmp=max(tmp,T.qry(rt,a[x],31));
	for(int y:ed[x]){
		if(y==son||y==fa[x]) continue;
		dfs(y);
	}
}
```

接着考虑求 $g_i$。

直观的，可以直接 dsu on tree，但是有两只 $\log$。

还是参考刚刚的过程，首先 $(1,v)$ 和 $(1,u)$ 的路径上的 $g_i$ 可以用刚刚的过程求出来。

至于其他的点，由于 $d_i$ 相同，只需要求出每个极大的不包含路径上的点子树根的 $g_i$ 就行。

我人傻，求出来所有符合要求的根后按子树大小从大到小排序跑 dfs 写的比较长。

时间空间均为 $O(n \log V)$。

code：
```cpp
#include <bits/stdc++.h>
//#define int long long
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define drep(i, x, y) for(int i = x; i >= y; --i)
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pb push_back
#define pii pair<int,int>
#define mp(x, y) make_pair(x, y)
#define fi first
#define se second
#define ld lower_bound
#define ud upper_bound
#define mem(s) memset(s,0,sizeof(s))
#define ui unsigned
#define N 30005
#define ull unsigned long long
#define ll int
using namespace std;
int rt;
struct Trie{
	int cnt=0,ch[N*66][2];
	inline int newnode(){cnt++;ch[cnt][0]=ch[cnt][1]=0;return cnt;}
	inline void ins(int &p,ll x,int dep){
		if(!p) p=newnode();
		if(dep==-1) return;
		ins(ch[p][(x>>dep)&1],x,dep-1);
	}
	inline ll qry(int p,ll x,int dep){
		if(!p||dep==-1) return 0;
		bool f=(x>>dep)&1;
		if(ch[p][f^1]) return qry(ch[p][f^1],x,dep-1)+(1ll<<dep);
		return qry(ch[p][f],x,dep-1);
	}
	void clear(){rt=cnt=0;}
}T;
int n,fa[N],siz[N];
ll mx,x,y,z,tmp,res,d[N],g[N],a[N],f[N];
vector<int> ed[N];
vector<pii> G[N];
inline void dfs(int x){
	T.ins(rt,a[x],31);tmp=max(tmp,T.qry(rt,a[x],31));
	for(int y:ed[x]) if(y!=fa[x]) dfs(y);
}
inline void solve1(int x,int son){
	if(x==0) return;f[x]=1;
	solve1(fa[x],x);d[x]=tmp;
	T.ins(rt,a[x],31);tmp=max(tmp,T.qry(rt,a[x],31));
	for(int y:ed[x]){
		if(y==son||y==fa[x]) continue;
		dfs(y);
	}
}
inline void solve2(int x,int son){
	if(x==0) return;
	T.ins(rt,a[x],31);
	tmp=max(tmp,T.qry(rt,a[x],31));
	for(int y:ed[x]){
		if(y==son||y==fa[x]) continue;
		dfs(y);
	}
	g[x]=tmp;solve2(fa[x],x);
}
vector<int> S;
inline void dfs2(int x){
	siz[x]=1;
	for(int y:ed[x]){
		if(y==fa[x]) continue;
		dfs2(y),f[x]|=f[y];siz[x]+=siz[y];
	}
	if(!f[x]) S.pb(x); 
}
inline void dfs3(int x){
	if(f[x]) return;
	f[x]=1;
	for(int y:ed[x]){
		if(y!=fa[x]) dfs3(y),g[x]=max(g[x],g[y]);
	}
	T.ins(rt,a[x],31);
	g[x]=max(g[x],T.qry(rt,a[x],31));
}
inline void init(int x,int f){
	fa[x]=f;
	for(pii s:G[x]){
		int y=s.fi,z=s.se;
		if(y==f) continue;
		a[y]=a[x]^z;
		init(y,x);
	}
}
inline bool cmp(int x,int y){
	return (siz[x])>(siz[y]);
}
void calc(){
	dfs2(1);
	sort(S.begin(),S.end(),cmp);
	mem(f);
	for(int x:S) T.clear(),dfs3(x);
}
signed main(){
	IOS;
	cin>>n;
	rep(i,1,n-1) cin>>x>>y>>z,ed[x].pb(y),ed[y].pb(x),G[x].pb(mp(y,z)),G[y].pb(mp(x,z));
	x=y=z=0;
	init(1,0);
	memset(d,-1,sizeof(d));
	rep(i,1,n) T.ins(rt,a[i],31);
	rep(i,1,n){
		ll s=T.qry(rt,a[i],31);
		if(s>mx) mx=s,x=a[i],y=mx^a[i];
	}
	int px=0,py=0;
	rep(i,1,n){
		if(a[i]==x) px=i;
		if(a[i]==y) py=i;
	}
	T.clear();tmp=0;solve1(px,0);
	T.clear();tmp=0;solve1(py,0);
	T.clear();tmp=0;solve2(px,0);
	T.clear();tmp=0;solve2(py,0);
	T.clear();calc();
	rep(i,1,n) if(d[i]<0) d[i]=mx;
	g[1]=0;for(int y:ed[1]) g[1]=max(g[1],g[y]);
	ll ans=0;
	rep(i,1,n) ans=max(ans,d[i]+g[i]);
	cout<<ans;
}
```

---

## 作者：St_john (赞：0)

通俗的讲，你要选择两条简单路径，满足没有重合的点，且边权异或和之和最大。 

如果只有1条，01Trie板子。  

现在有两条，可以以节点 $x$ 为分界线，求 $x$ 的子树外的最大路径的权值 $in_x$ 和 $x$ 的子树内的最大路径的权值 $out_x$ ，相加即可。   

思路就很清晰了。

先处理子树内。暴力扫一遍 $O(n^2 \log { \max{W}})$ 。  
考虑~~玄学~~算法，树上启发式合并，达到 $O(n\log{n} \log{ \max{W}})$ 。  
具体实现就是建 $n$ 棵01Trie，记录一下每个节点有多少个数插入了。合并时，枚举小的的每一种情况，将小的向大的合并。  

再处理子树外的情况。  
选出两个点 $A$ 和 $B$ ,使得 $A$ 到 $B$ 的路径的权值 $mx$ 最大。  
此时，只有不在 $A$ 和 $B$ 到根节点的链上的点 $x$ 的 $out_x=mx$。  
再观察，发现从根节点到 $A$ 和 $B$ 的路径上的点的子树的大小是递减的，即子树外的大小是递增的。  
这时，可以从根节点向下遍历到 $A$ 或 $B$ ，设当前的点为 $x$  ， $son_x$ 为 $x$ 在链上的儿子,对所有不在链上的儿子进行DFS，将到根的路径权值插入01Trie，算出当前的 $mx=out_{son_x}$。



```cpp
#include<cstdio>
#define Re register int 
#define _for(i,a,b) for(register int i=(a);i<=(b);++i)
#define __for(i,a,b) for(register int i=(a);i>=(b);--i)
#define il inline
#define pc putchar
using namespace std;
typedef long long ll;
const int N=3e4+10,M=1e6+10,inf=2147483647;
il int re(){
    int x=0;
    bool f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')
        f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return f?-x:x;
}
void pr(ll x){
	if(x<0) pc('-'),x=-x;
	if(x>9) pr(x/10);
	pc(x%10|48);
}
int n,r[N],cnt;
struct Edge{
	int t,n,w;
}edge[N<<1];
il void add_edge(int u,int v,int w){
	edge[++cnt]={v,r[u],w};r[u]=cnt;
	edge[++cnt]={u,r[v],w};r[v]=cnt;
}
int fa[N],in[N],out[N];
int ch[N*128][2];
int t[N];
void insert(int &p,int v){
	if(!p) p=++cnt;
	int pp=p;
	__for(i,30,0){
		int q=v>>i&1;
		if(!ch[pp][q]) ch[pp][q]=++cnt;
		pp=ch[pp][q];
	}
}
int ask(int p,int v){
	int ans=0;
	__for(i,30,0){
		int q=v>>i&1;
		if(ch[p][!q]) p=ch[p][!q],ans|=1<<i;
		else p=ch[p][q];
	}
	return ans;
}
int root[N];
il int max(int a,int b){
	return a>b?a:b;
}
void merge(int x,int y,int z,int i,int &v){
	if(!x) return ;
	if(!(~i)){
		v=max(v,ask(root[y],z));
		++t[y];
		insert(root[y],z);
		return ;
	}
	merge(ch[x][0],y,z,i-1,v);
	merge(ch[x][1],y,z|1<<i,i-1,v);
}
int d[N];
il void swap(int &x,int &y){
	x^=y^=x^=y;
}
void dfs1(int x){
	++t[x];
	insert(root[x],d[x]);
	for(Re i=r[x],y;i&&(y=edge[i].t);i=edge[i].n)
		if(y!=fa[x]){
			d[y]=d[x]^edge[i].w;
			fa[y]=x;
			dfs1(y);
			if(t[x]<t[y]) swap(root[x],root[y]),swap(t[x],t[y]);
			merge(root[y],x,0,30,in[x]);
			if(in[x]<in[y]) in[x]=in[y];
		}
}
int mx,A,B;
struct Trie{
	int ch[M][2],pos[M];
	void clear(){
		_for(i,1,cnt) ch[i][0]=ch[i][1]=0;
		cnt=1;
	}
	void find(int x,int y){
		int p=1,ans=0;
		__for(i,30,0){
			int q=x>>i&1;
			if(ch[p][!q]) p=ch[p][!q],ans|=1<<i;
			else p=ch[p][q];
		}
		if(ans>mx) mx=ans,A=pos[p],B=y;
	}
	void insert(int x,int y){
		int p=1;
		__for(i,30,0){
			int q=x>>i&1;
			if(!ch[p][q]) ch[p][q]=++cnt;
			p=ch[p][q];
		}
		pos[p]=y;
	}
}tr;
int son[N];
void dfs2(int x){
	tr.insert(d[x],x);
	tr.find(d[x],x);
	for(Re i=r[x],y;i&&(y=edge[i].t);i=edge[i].n)
		if(y!=fa[x])
			dfs2(y);
}
void solve(int x){
	while(x!=1)
		son[fa[x]]=x,x=fa[x];
	mx=0;
	tr.clear();
	while(x){
		out[x]=mx;
		tr.insert(d[x],x);
		tr.find(d[x],x);
		for(Re i=r[x],y;i&&(y=edge[i].t);i=edge[i].n)
			if(y!=fa[x]&&y!=son[x])
				dfs2(y);
		x=son[x];
	}
}
bool vis[N];
int lca(int x,int y){
	while(x!=1) vis[x]=1,x=fa[x];
	while(y!=1)
		if(vis[y])
			return y;
		else y=fa[y];
	return 1;
}
signed main(){
	n=re();
	_for(i,2,n){
		int x=re(),y=re(),z=re();
		add_edge(x,y,z);
	}
	cnt=0;
	dfs1(1);
	cnt=1;
	_for(i,1,n)
		tr.insert(d[i],i),tr.find(d[i],i);
	_for(i,1,n) out[i]=mx;
	int aa=A,bb=B;
	solve(aa);
	solve(bb);
	ll ans=0;
	if(lca(aa,bb)!=1) ans=in[1];
	
	_for(i,2,n)
		if(ans<in[i]+out[i])
			ans=in[i]+out[i];
	pr(ans);
	return 0;
}
```


---

