# [ARC086E] Smuggling Marbles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc086/tasks/arc086_c

すぬけ君は $ N+1 $ 頂点の根付き木を持っています。 この木の頂点には $ 0 $ から $ N $ までの番号がついており、頂点 $ 0 $ はこの木の根です。 頂点 $ i(1\ \leq\ i\ \leq\ N) $ の親は頂点 $ p_i $ です。

すぬけ君はこの木の他に、空の箱とビー玉を使って遊んでいます。 この遊びはいくつかの頂点にビー玉をそれぞれ $ 1 $ つ置いたのち、以下の手順で進行します。

1. 頂点 $ 0 $ にビー玉が置かれているならば、そのビー玉を箱に移す。
2. 全てのビー玉を現在の頂点から親の頂点に(同時に)移す。
3. $ 2 $ つ以上のビー玉が置かれている頂点それぞれについて、その頂点に置かれているビー玉を全て取り除く。
4. ビー玉が置かれている頂点が存在するならば手順 1 へ、そうでなければ遊びを終了する。

ビー玉の置き方は $ 2^{N+1} $ 通りあります。 これらそれぞれの場合について **遊びが終了したときに箱に入っているビー玉** の数を求め、その和を $ {\rm\ mod}\ 1,000,000,007 $ で求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ <\ 2\ \times\ 10^{5} $
- $ 0\ \leq\ p_i\ <\ i $

### 部分点

- $ 400 $ 点分のデータセットでは $ N\ <\ 2000 $ が成立する

### Sample Explanation 1

頂点 $ 1 $ と頂点 $ 2 $ のどちらにもビー玉を置いたとき、手順 $ 2 $ により頂点 $ 0 $ に複数のビー玉が置かれてしまいます。このとき、これらのビー玉は取り除かれるため箱に移動されることはありません。

### Sample Explanation 3

答えを $ {\ \rm\ mod}\ 1,000,000,007 $ で求めてください。

## 样例 #1

### 输入

```
2
0 0```

### 输出

```
8```

## 样例 #2

### 输入

```
5
0 1 1 0 4```

### 输出

```
96```

## 样例 #3

### 输入

```
31
0 1 0 2 4 0 4 1 6 4 3 9 7 3 7 2 15 6 12 10 12 16 5 3 20 1 25 20 23 24 23```

### 输出

```
730395550```

# 题解

## 作者：ZillionX (赞：7)

# Description

给定一棵 $n+1$ 个点的树，其中 $0$ 为根，每个点上有 $0$ 或 $1$ 个石子，进行若干次如下操作直至整棵树没有石子：

- 把 $0$ 上面的石子从树上拿走放入口袋

- 把每个点上的石子移到其父亲上

- 对于每个点，若其石子数 $\ge 2$，则移除该点所有石子（不放入口袋）

对于所有 $2^{n+1}$ 种放置石子的方案，求最终口袋中石子数的和为多少。

$n \le 2 \times 10^5$，时限 3s。

# Solution

题解区做法怎么都是 $\mathcal O(n \log n)$ 的，这里提供一个严格线性的做法。

------------

容易发现若已经确定石子放置方式，则只有同深度的石子会撞到同一个点上。因此同深度的石子最多只能收到一个。

因此我们可以记 $f_{u,d}$ 表示在 $u$ 子树中深度为 $d$ 的点移到点 $u$ 后，使 $u$ 点石子数为 $1$ 的概率。（如果这里记方案数而不是概率的话，下面的式子中的 $1$ 要变成子树总方案数，我们就要维护更麻烦的乘法标记）

有转移

$$f_{u,d}=\sum_{v_1 \in {\rm son}_u} f_{v_1,d} \prod_{v_1 \neq v_2} (1-f_{v_2,d})$$

然后边界显然是 $f_{u,d_u}=\frac{1}{2}$（这里的 $d_u$ 为 $u$ 点深度）。

不难发现这个 DP 和子树最大深度有关，因此可以使用长链剖分优化 DP，每条长链只会被合并一次，时空复杂度 $\mathcal O(n)$。

因为常数很小，跑到了目前的最优解。

# Code

```cpp
const int N=2e5+5,mo=1e9+7,iv2=(mo+1)/2;
int n,ans,le[N],d[N],s[N],ls[N],o[N],*f[N],*pf=o,sm[N];
vector<int> g[N];
void dfs1(int u) {
	s[u]=1;
	for (int v:g[u]) {
		d[v]=d[u]+1;
		dfs1(v);
		s[u]+=s[v];
		le[u]=max(le[u],le[v]+1);
		if (le[v]>le[ls[u]]) ls[u]=v;
	}
}
void dfs2(int u) {
	f[u][d[u]]=iv2;
	if (!ls[u]) return;
	f[ls[u]]=f[u];
	dfs2(ls[u]);
	int mxd=0;
	for (int v:g[u])
		if (v!=ls[u]) {
			f[v]=pf-d[v],pf+=le[v]+1,dfs2(v);
			mxd=max(mxd,le[v]);
		}
	for (int i=d[u]+1;i<=d[u]+mxd+1;i++) sm[i]=(1+(mo-f[u][i]))%mo;
	for (int v:g[u])
		if (v!=ls[u]) {
			for (int k=d[v];k<=d[v]+le[v];k++) {
				f[u][k]=(1ll*sm[k]*f[v][k]%mo+1ll*f[u][k]*(1+(mo-f[v][k]))%mo)%mo;
				sm[k]=1ll*sm[k]*(1+(mo-f[v][k]))%mo;
			}
		}
}
int main() {
	scanf("%d",&n);
	for (int i=2;i<=n+1;i++) {
		int x;
		scanf("%d",&x),x++;
		g[x].pb(i);
	}
	le[0]=-1;
	dfs1(1);
	f[1]=pf,pf+=le[1]+1,dfs2(1);
	for (int i=0;i<=le[1];i++) ans=(ans+f[1][i])%mo;
	for (int i=1;i<=n+1;i++) ans=1ll*ans*2%mo;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：NOI_Winner (赞：4)

知识点：树形 DP，长链剖分。

先考虑 $N \lt 2000$ 的部分分。可以考虑用树形 DP 求解，设 $dp_{i,j}$ 表示以 $i$ 为根的子树内从上往下第 $j$ 层（从 $0$ 开始编号）的所有石子移到 $i$ 时 $i$ 上存在石子的方案数，也就是经过 $j$ 轮操作后 $i$ 上存在石子的方案数。若 $i$ 是叶节点，则 $dp_{i,0}=1,dp_{i,j}=0(j \gt 0)$。否则，设以 $i$ 为根的子树大小为 $sz_i$，$son_i$ 为 $i$ 的儿子集合，则有转移方程：
$$
dp_{i,0}=2^{sz_i-1} \\
dp_{i,j}=2 \times \sum_{u \in son_i}dp_{u,j-1}\prod_{v \in son_i且v \ne u}(2^{sz_v}-dp_{v,j-1}) (j \gt 0)
$$
我们先求出 $val=\prod_{u \in son_i}(2^{sz_u}-dp_{u,j-1})$，则：
$$
dp_{i,j}=2 \times \sum_{u \in son_i}\frac{dp_{u,j-1} \times val}{2^{sz_u}-dp_{u,j-1}}
$$
最终答案即为 $\sum_{i=0}^{i\le N}dp_{0,i}$。

如果 $N \lt 200000$，不难发现上述动态规划过程是基于树的深度的，可以考虑长链剖分优化，实现较为复杂，需要使用乘法标记维护，具体请见代码。

参考代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int maxn = 200000, mod = 1000000007;
int head[maxn + 5], vert[maxn + 5], nxt[maxn + 5], tot;
int f[maxn + 5], sz[maxn + 5], val[maxn + 5], dep[maxn + 5], tg[maxn + 5];
int son[maxn + 5], *dp[maxn + 5], *tag[maxn + 5], c[maxn + 5], s[maxn + 5];
int n, cur;

inline void add(int x, int y)       // 加边 
{
	vert[++tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}

inline int qp(int x, int y)        // 快速幂 
{
	int ans = 1;
	for (; y; y >>= 1)
	{
		if (y & 1)
			ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
	}
	return ans;
}

void dfs1(int x)         //  预处理子树大小和重儿子 
{
	sz[x] = 1;
	for (int i = head[x]; i; i = nxt[i])
	{
		int y = vert[i];
		dfs1(y); sz[x] += sz[y];
		if (dep[y] + 1 > dep[x])
		{
			dep[x] = dep[y] + 1;
			son[x] = y;
		}
	}
}

void dfs2(int x)           // 分配dp和tag数组 
{
	dp[x] = f + ++cur; tag[x] = tg + cur;
	if (son[x])
		dfs2(son[x]);
	for (int i = head[x]; i; i = nxt[i])
		if (vert[i] != son[x])
			dfs2(vert[i]);
}

void dfs3(int x)         // 树形dp 
{
	if (1 == sz[x])
	{
		dp[x][0] = 1;
		return;
	}
	
	for (int i = head[x]; i; i = nxt[i])
		dfs3(vert[i]);
	
	int cnt =  0;
	for (int i = head[x]; i; i = nxt[i])
		if (vert[i] != son[x])
			c[++cnt] = vert[i];
	sort(c + 1, c + cnt + 1, [](int x, int y) { return dep[x] > dep[y]; });
	
	if (0 == cnt)
	{
		dp[x][0] = val[sz[x] - 1];
		tag[x][1] = 2ll * tag[x][1] % mod;
		return;
	}
	
	for (int i = 1; i <= cnt; i++)
		for (int d = 0; d <= dep[c[i]]; d++)
			if (tag[c[i]][d] > 1)
			{
				dp[c[i]][d] = 1ll * dp[c[i]][d] * tag[c[i]][d] % mod;
				if (d < dep[c[i]])
					tag[c[i]][d + 1] = 1ll * tag[c[i]][d + 1] * tag[c[i]][d] % mod;
				tag[c[i]][d] = 1;
			}
	
	s[cnt + 1] = 1;
	for (int i = cnt; i >= 1; i--)
		s[i] = 1ll * s[i + 1] * val[sz[c[i]]] % mod;
	
	dp[x][0] = val[sz[x] - 1];
	for (int d = 1; d <= dep[c[1]] + 1; d++)
	{
		if (tag[x][d] > 1)
		{
			dp[x][d] = 1ll * dp[x][d] * tag[x][d] % mod;
			if (d < dep[x])
				tag[x][d + 1] = 1ll * tag[x][d + 1] * tag[x][d] % mod;
			tag[x][d] = 1;
		}
		
		int cur = (val[sz[son[x]]] - dp[x][d]) % mod, i;
		for (i = 1; i <= cnt && d <= dep[c[i]] + 1; i++)
			cur = 1ll * (val[sz[c[i]]] - dp[c[i]][d - 1]) % mod * cur % mod;
		if (i <= cnt)
			cur = 1ll * cur * s[i] % mod;
		dp[x][d] = 1ll * cur * qp((val[sz[son[x]]] - dp[x][d]) % mod, mod - 2) % mod * dp[x][d] % mod;
		for (i = 1; i <= cnt && d <= dep[c[i]] + 1; i++)
			dp[x][d] = (dp[x][d] + 1ll * cur * qp((val[sz[c[i]]] - dp[c[i]][d - 1]) % mod, mod - 2) % mod * dp[c[i]][d - 1] % mod) % mod;
		dp[x][d] = 2ll * dp[x][d] % mod;
	}
	if (dep[c[1]] + 1 < dep[x])
		tag[x][dep[c[1]] + 2] = 2ll * tag[x][dep[c[1]] + 2] % mod * s[1] % mod;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int f; cin >> f;
		add(f, i);
	}
	val[0] = 1;
	for (int i = 1; i <= n + 1; i++)       // 预处理2的幂 
		val[i] = 2ll * val[i - 1] % mod;
	
	dfs1(0); dfs2(0);
	for (int i = 1; i <= n + 1; i++)
		tg[i] = 1;
	dfs3(0);
		
	int ans = 0;
	for (int i = 0; i <= dep[0]; i++)     // 统计答案 
	{
		if (tag[0][i] > 1)
		{
			dp[0][i] = 1ll * dp[0][i] * tag[0][i] % mod;
			if (i < dep[0])
				tag[0][i + 1] = 1ll * tag[0][i + 1] * tag[0][i] % mod;
			tag[0][i] = 1;
		}
		ans = (ans + dp[0][i]) % mod;
	}
	cout << (ans + mod) % mod << endl;
	
	return 0;
}
```

---

## 作者：fade_away (赞：3)

# ARC086E - Smuggling Marbles
[安利博客](https://blog.csdn.net/xmr_pursue_dreams/article/details/111997371)
## Solution
感觉这题和[LG P3233 [HNOI2014]世界树](https://blog.csdn.net/xmr_pursue_dreams/article/details/111971930)几乎一模一样啊？！

大概就是对于每一个深度分别计算贡献，对该深度的点建出虚树，然后树形$dp$。

令$f_x$表示$x$子树中$2^{sz_x}$种方案中有多少可以让$x$是$1$，由此可知有$2^{sz_x}-f_x$种方案$x$为$0$，转移时相当于枚举其中一个子树为$1$，剩下的子树为$0$，这样才能保证$x$为$1$。

设$x$的虚树上的儿子分别为$v_1,v_2...v_k$，$f_x=2^t\sum_{i=1}^k(\prod_{j=1}^{i-1}f'_{v_j} *f_{v_i}*\prod_{j=k+1}^n f'_{v_j})$

其中$f'_v$表示$2^{sz_v}-f_v$，$t$表示在$x$原树的子树中但不在虚树上的点的个数。

这一部分求一个$f'_v$的前缀后缀积就能轻松线性时间内解决了。

时间复杂度$O(nlgn)$。

实现时依然建议把$1$放入虚树，不然最后还要乘一个$2^{sz}$的贡献。
## Code

```cpp

vector<int> e[MAXN],V[MAXN],E[MAXN];
int f[MAXN],g[MAXN],_g[MAXN],L[MAXN],R[MAXN],pw[MAXN],sz[MAXN],dep[MAXN],Log[MAXN],dfn[MAXN],stk[MAXN],fa[MAXN][20],DFN=0,top,n,mxd=0;
int upd(int x,int y) { return x+y>=mods?x+y-mods:x+y; }
int quick_pow(int x,int y)
{
	int ret=1;
	for (;y;y>>=1)
	{
		if (y&1) ret=1ll*ret*x%mods;
		x=1ll*x*x%mods;
	}
	return ret;
}
int getlca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=Log[dep[x]];i>=0;i--) 
		if (dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if (x==y) return x;
	for (int i=Log[dep[x]];i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int jump(int x,int d)
{
	for (int i=Log[dep[x]];i>=0;i--)
		if (dep[fa[x][i]]>=d) x=fa[x][i];
	return x;
}
void dfs1(int x)
{
	sz[x]=1,dfn[x]=++DFN,V[dep[x]].PB(x),upmax(mxd,dep[x]);
	for (int i=1;i<=Log[dep[x]];i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (auto v:e[x]) dep[v]=dep[x]+1,fa[v][0]=x,dfs1(v),sz[x]+=sz[v];
}
void add(int u,int v) { E[u].PB(v); }
void build(vector<int> V)
{
	stk[top=1]=1;
	for (auto v:V)
	{
		if (v==1) continue;
		int lca=getlca(stk[top],v);
		while (top>1&&dep[stk[top-1]]>dep[lca]) add(stk[top-1],stk[top]),top--;
		if (dep[stk[top]]>dep[lca]) add(lca,stk[top--]);
		if (stk[top]!=lca) stk[++top]=lca;
		stk[++top]=v; 
	}
	while (top>1) add(stk[top-1],stk[top]),top--;
}
void solve(int x)
{
	if (!E[x].size()) { f[x]=pw[sz[x]-1]; return; }
	for (auto v:E[x]) solve(v);
	int num=E[x].size(),cnt=sz[x];
	for (int i=0;i<num;i++)
	{
		int v=E[x][i],p=jump(v,dep[x]+1);
		cnt-=sz[v],g[i+1]=f[v],_g[i+1]=upd(pw[sz[v]],mods-g[i+1]);
	}
	L[0]=R[num+1]=1,f[x]=0;
	for (int i=1;i<=num;i++) L[i]=1ll*L[i-1]*_g[i]%mods;
	for (int i=num;i>=1;i--) R[i]=1ll*R[i+1]*_g[i]%mods;
	for (int i=1;i<=num;i++) f[x]=upd(f[x],1ll*L[i-1]*R[i+1]%mods*g[i]%mods);
	f[x]=1ll*f[x]*pw[cnt]%mods;
}
void clear(int x)
{
	for (auto v:E[x]) clear(v);
	f[x]=0,E[x].clear();
}
signed main()
{
	n=read()+1,Log[1]=0,pw[0]=1;
	for (int i=2;i<=n;i++) e[read()+1].PB(i),Log[i]=Log[i>>1]+1;
	for (int i=1;i<=n;i++) pw[i]=upd(pw[i-1],pw[i-1]);
	dep[0]=-1,dfs1(1);
	int ans=0;
	for (int i=0;i<=mxd;i++) build(V[i]),solve(1),ans=upd(ans,f[1]),clear(1);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：yazzkl (赞：3)


# 题意
有棵N个点的有根树 , 初始时其中一些点上有一个石子,每次同时将所有石子从所在的点移动到父亲上,根节点上的石子移动到篮子里.如果有一个点上的石子数大于1则移除所有石子,树上没有石子时结束 .求所有2N种初始局面经过操作后篮子里石子的总数量。

## 图论好题

# 分析

我们发现:每一层的点都是独立的

### ---->考虑**分开处理**

# 实现
分别将每一层的点建成虚树后**树形DP**即可，时间复杂度$O(n*log(n))$。 

可以用**长链剖分**做到O(n)。

# code
```
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> P;

const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;

int add(int x, int y) {
    x += y;
    if(x >= mod) x -= mod;
    return x;
}

int mul(int x, int y) {
    LL z = 1LL * x * y;
    return z - z / mod * mod;
}

int p[maxn];
vector<int> g[maxn], g2[maxn];
vector<int> fu[maxn];
int depth = 0, bn = 0, b[maxn << 1];
int f[maxn << 1], dfn[maxn], dis[maxn], fs[maxn];
LL ans[maxn];

void dfs(int u, int fa) {
    int tmp = ++depth;
    b[++bn] = tmp;
    f[tmp] = u;
    dfn[u] = bn;
    for (auto v : g[u]) {
        if (v == fa) continue;
        dis[v] = dis[u] + 1;
        dfs(v, u);
        b[++bn] = tmp;
    }
}

int st[maxn << 1][20];
int lg[maxn << 1];
void st_init() {
    for (int i = 2; i < maxn * 2; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = bn; i >= 1; --i) {
        st[i][0] = b[i];
        for (int j = 1; i + (1 << j) - 1 <= bn; ++j)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
}
int rmq(int l, int r) {
    int k = lg[r - l + 1];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}

int lca(int a, int b) {
    if(a == b) return a;
    if (dfn[a] > dfn[b]) swap(a, b);
    int k = rmq(dfn[a], dfn[b]);
    return f[k];
}

bool cmp(const int &i, const int &j) {
    return dfn[i] < dfn[j];
}

void build_tree(vector<int> &vec) {
    int sz = 0, k = vec.size();
    sort(vec.begin(), vec.end(), cmp);
    fs[sz] = 0;
    g2[0].clear();
    for (int i = 0; i < k; ++i) {
        int u = vec[i], ll = lca(u, fs[sz]);
        g2[u].clear();
        if (ll == fs[sz]) fs[++sz] = u;
        else {
            while (sz >= 1 && dis[fs[sz - 1]] >= dis[ll]) {
                g2[fs[sz - 1]].push_back(fs[sz]);
                sz--;
            }
            if (fs[sz] != ll) {
                g2[ll].clear();
                g2[ll].push_back(fs[sz--]);
                fs[++sz] = ll;
            }
            fs[++sz] = u;
        }
    }
    for (int i = 0; i < sz; ++i) g2[fs[i]].push_back(fs[i + 1]);
}

int dp[maxn][2];

void dfs2(int u) {
    int a,b,c;
    a = 1;
    b = c = 0;
    for(auto v:g2[u]) {
        dfs2(v);
        c = add(mul(c,add(dp[v][1],dp[v][0])),mul(b,dp[v][1]));
        b = add(mul(b,dp[v][0]),mul(a,dp[v][1]));
        a = mul(a,dp[v][0]);
    }
    if(g2[u].size() == 0) dp[u][0] = dp[u][1] = 1;
    else {
        dp[u][0] = add(a,c);
        dp[u][1] = b;
    }
}

int main() {
    int n, i, x, ans = 0;
    scanf("%d", &n);
    for(i = p[0] = 1; i < maxn; i++) p[i] = mul(p[i - 1], 2);
    for(i = 1; i <= n; i++) {
        scanf("%d", &x);
        g[x + 1].push_back(i + 1);
    }
    dis[1] = 1;
    dfs(1,0);
    st_init();
    for(i = 1;i <= n + 1; i++) fu[dis[i]].push_back(i);
    for(i = 1;i <= n + 1; i++) {
        if(fu[i].size()) {
            //cout<<i<<" = "<<fu[i].size()<<endl;
            build_tree(fu[i]);
            dfs2(0);
        //cout<<dp[0][1]<<endl;
            ans = add(ans,mul(dp[0][1],p[n + 1 - fu[i].size()]));
        }
    }
    printf("%d\n", ans);
    return 0;;
}

```
其实大方向是很容易找到的，代码实现可能有些问题。

调了老久了。

---

## 作者：white_carton (赞：2)

You can view the [English version](https://www.luogu.com.cn/paste/p3ot7hu4) of this solution.

---

非常美味，不可不品尝。

观察到笔者写下这篇题解时仅有一篇长剖题解，且使用的是指针写法，于是笔者提供一种 `vector` 写法。

---

考虑做到 $\mathcal{O}(n^2)$ 是容易的，设 $dp_{u,d}$ 表示深度为 $d$ 的点可以到 $u$ 的概率，有转移
$$
dp_{u,d}=\sum_{v_1\in son}dp_{v_1,d}\prod_{v_2\in son,v_2\ne v_1}\left(1-dp_{v_2,d}\right)
$$
即对于 $u$，第 $d$ 层的概率为第 $d$ 层**到某个儿子节点的概率**乘上**不到其他任何儿子节点的概率**之和。

对于每个节点做一遍这个东西就是 $\mathcal{O}(n^2)$。

---

考虑优化，发现一维下标为深度，考虑长链剖分。

这里使用 `vector` 写法，即倒着存储 $dp$ 数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
// #define max(a,b) (((a)>(b))?(a):(b))
#define ll long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define pii pair<int,int>
#define fir first
#define sec second
const int MAXN=200100;
const int mod=1e9+7,i2=(mod+1)/2;
int read(){
	int f=1,c=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch)){
		c=(c<<1)+(c<<3)+(ch^48);
		ch=getchar();
	}
	return c*f;
}
int n,fa[MAXN];
int modint(int x){
	if(x>mod){
		x-=mod;
	}
	if(x<0){
		x+=mod;
	}
	return x;
}
struct edge{
	int nxt,to;
}e[MAXN<<1];
int head[MAXN],cnt;
int power(ll a,int b){
	ll ans=1;
	while(b){
		if(b&1){
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void add(int u,int v){
	e[++cnt]={head[u],v};
	head[u]=cnt;
}
int dep[MAXN],maxn[MAXN],son[MAXN];
int len[MAXN];
ll sondp[MAXN];
vector<ll> dp[MAXN];
inline void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;
	maxn[u]=dep[u];
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(to==fa){
			continue;
		}
		dfs1(to,u);
		if(maxn[to]>maxn[son[u]]){
			maxn[u]=maxn[to];
			son[u]=to;
		}
	}
	len[u]=maxn[u]-dep[u];
}
int get(int u,int id){
	return len[u]-id;
}
inline void dfs2(int u,int tp){
	if(son[u]){
		dfs2(son[u],tp);
		swap(dp[u],dp[son[u]]);
	}
	dp[u].push_back(i2);
	if(!son[u]){
		return;
	}
	int mxd=0;
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(to==son[u]||to==fa[u]){
			continue;
		}
		dfs2(to,to);
		mxd=max(mxd,len[to]);
	}
	for(int i=1;i<=mxd+1;i++){
		sondp[i]=modint(1-dp[u][get(u,i)]);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(to==son[u]||to==fa[u]){
			continue;
		}
		for(int d=0;d<=len[to];d++){
			dp[u][get(u,d+1)]=modint(1ll*sondp[d+1]*dp[to][get(to,d)]%mod+1ll*dp[u][get(u,d+1)]*modint(1+mod-dp[to][get(to,d)])%mod);
			sondp[d+1]=1ll*sondp[d+1]*modint(1+-dp[to][get(to,d)])%mod;
		}//这里手模一下可以发现，sondp的实质是son的值乘上一个前缀儿子的值，而dp数组自身又不断的乘上后面的值，因此每个值都乘上了不包括自己的其他值。
	}
}
signed main(){
	cin.tie(nullptr)->ios::sync_with_stdio(false);
	n=read();
	n++;
	for(int i=2;i<=n;i++){
		fa[i]=read();
		fa[i]++;
		add(fa[i],i);
	}
	len[0]=-1;
	dfs1(1,0);
	dfs2(1,1);
	ll ans=0;
	for(int i=0;i<=len[1];i++){
		ans=(ans+dp[1][get(1,i)])%mod;
	}
	cout<<ans*power(2ll,n)%mod<<endl;
}
//吾日三省吾身
//输入多而不read()乎？
//1e18而不开longlong乎？
//多测不清乎？


```

---

撒花。

---

## 作者：simonG (赞：0)

首先发现所有的深度都是独立的，因为每个深度都是同时移动，不会出现干扰。

考虑处理每个深度的情况：设当前求是深度是 $d$ 的贡献。

我们有一个基本的 dp，是这样的，设 $f_{u,0/1}$ 表示在 $u$ 子树内全部深度是 $d$ 的节点石子移上来后，$u$ 节点有 $0/1$ 个石子的方案数。

如果计算 $f_{u,1}$，那么 $u$ 所有的儿子有且仅有一个儿子有一个石子。

枚举 $u$ 的儿子 $v$，设所有 $v$ 的 $f_{v,0}$ 的积是 $s$。

$f_{u,1}=\sum f_{v,1}\times \dfrac{s}{f_{v,0}}$

$f_{u,0}$ 就是该子树全部方案数减去 $f_{u,1}$。

最后，$f_{u,1}$ 对答案的贡献是 $2^{n-t}\times f_{u,1}$。因为这使得有 $2^{n-t}\times f_{u,1}$ 种情况石子都加上 $1$。

然而这样做，万一深度很大呢，复杂度是 $O(n^2)$ 的。

我们考虑每个深度建立一颗虚树再做 $dp$，方程是一样的，然而总的要做 dp 的点的数量是 $O(n)$ 的。

最后是建立虚树的复杂度为 $O(n\log n)$。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=2e5+10,mod=1e9+7;
int n,dep[N],Mxd,dfn[N],num,f[N][21];
vector<int> e[N];
vector<int> arr[N];
void dfs(int u,int fa) {
	f[u][0]=fa;
	for(int i=1; i<=20; i++) f[u][i]=f[f[u][i-1]][i-1];
	dfn[u]=++num;
	dep[u]=dep[fa]+1; Mxd=max(Mxd,dep[u]);
	arr[dep[u]].push_back(u);
	for(int v:e[u]) if(v!=fa) {
		dfs(v,u);
	}
}
int Lca(int u,int v) {
	if(dep[v]>dep[u]) swap(u,v);
	for(int i=20; i>=0; i--) 
		if(dep[f[u][i]]>=dep[v]) u=f[u][i];
	if(u==v) return u;
	for(int i=20; i>=0; i--)
		if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
int p[N],tot,A[N],tc;
bool cmp(int x,int y) {
	return dfn[x]<dfn[y];
}
vector<int> vt[N];
void buildvt() {
	p[++tot]=1;
	sort(p+1,p+1+tot,cmp);
	tc=0;
	for(int i=1; i<tot; i++) {
		A[++tc]=p[i]; A[++tc]=Lca(p[i],p[i+1]);
	} A[++tc]=p[tot];
	sort(A+1,A+1+tc,cmp);
	tc=unique(A+1,A+1+tc)-A-1;
	for(int i=1; i<tc; i++) {
		int lc=Lca(A[i],A[i+1]);
		vt[lc].push_back(A[i+1]);
	}
}
int dp[N][2],Ans;
int inv(int a) {
	int res=1,b=mod-2;
	for(; b; b>>=1) {
		if(b&1) res=1ll*res*a%mod;
		a=1ll*a*a%mod;
	}
	return res;
}
void solve(int u) {
	int son=0;
	for(int v:vt[u]) {
		solve(v); son++;
	}
	if(son==0) {
		dp[u][0]=dp[u][1]=1; return ;
	}
	int s=1,s2=1;
	for(int v:vt[u]) s2=1ll*s2*dp[v][0]%mod;
	for(int v:vt[u]) {
		dp[u][1]=(dp[u][1]+1ll*dp[v][1]*s2%mod*inv(dp[v][0]))%mod;
		s=1ll*s*(dp[v][1]+dp[v][0])%mod;
	}
	dp[u][0]=(s+mod-dp[u][1])%mod;
}
int pw[N];
int main() {
	scanf("%d",&n); n++;
	for(int i=2; i<=n; i++) {
		int u; scanf("%d",&u);
		u++; e[u].push_back(i);
	}
	dfs(1,1);
	pw[0]=1;
	for(int i=1; i<=n; i++) pw[i]=2ll*pw[i-1]%mod;
	for(int i=1; i<=Mxd; i++) {
		tot=0;
		for(int u:arr[i]) p[++tot]=u;
		buildvt();
		solve(1);
		Ans=(Ans+1ll*pw[n-arr[i].size()]*dp[1][1])%mod;
		for(int j=1; j<=tc; j++)
			dp[A[j]][0]=dp[A[j]][1]=0,vt[A[j]].clear();
	}
	printf("%d\n",Ans);
	return 0;
}
```

---

