# [ICPC 2022 Jinan R] DFS Order 2

## 题目描述

P有一棵树，根节点是$1$，总共有$n$个节点，从$1$到$n$编号。

他想从根节点开始进行深度优先搜索。他想知道对于每个节点$v$，在深度优先搜索中，它出现在第$j$个位置的方式有多少种。深度优先搜索的顺序是在搜索过程中访问节点的顺序。节点出现在第$j（1 \le j \le n $）个位置表示它在访问了$j - 1$个其他节点之后才被访问。因为节点的子节点可以以任意顺序访问，所以有多种可能的深度优先搜索顺序。

P想知道对于每个节点$v$，有多少种不同的深度优先搜索顺序，使得$v$出现在第$j$个位置。对于每个$v$和$j（i \le v,j \le n）$，计算答案。答案可能很大，所以输出时要取模$998244353$。以下是深度优先搜索的伪代码，用于处理树。在调用$main()$函数后， dfs_order将会包含深度优先搜索的顺序。



------------
#### 算法 $1$ 深度优先搜索的实现
```
1. 过程 DFS(节点 x)

2.	将x添加到dfs_order的末尾

3.	对于x的每个子节点y do               ·子节点可以以任意顺序遍历。

4.		DFS(y)

5.	结束循环

6. 结束过程

7. 过程 MAIN()

8.	将dfs_order设为全局变量

9.	dfs_order ← 空列表

10.	DFS(1)

11. 结束过程
```
------------

## 样例 #1

### 输入

```
5
1 2
1 3
3 4
3 5```

### 输出

```
4 0 0 0 0
0 2 0 0 2
0 2 2 0 0
0 0 1 2 1
0 0 1 2 1```

# 题解

## 作者：9981day (赞：9)

# P9669 [ICPC2022 Jinan R] DFS Order 2 题解

## 简要题意

给定一棵 $n$ 个节点的树，根节点是 $1$。

从根节点开始深度优先搜索这一棵树，dfs 序是在搜索过程中访问节点的顺序。

对于每一个节点 $v$，你要给出有多少种不同的 dfs 序，使得 $v$ 出现在第 $j$ 个位置。

答案对 $998244353$ 取模。

## 解法说明

首先我们考虑一下总共有多少种 dfs 序。

记 $h[x]$ 为只考虑 $x$ 的子树内的节点所形成的 dfs 序的方案数。

假设 $x$ 有 $m$ 个儿子，那么他选第一个儿子的时候有 $m$ 种选法，第二个儿子有 $m - 1$ 种选法，同理第 $i$ 个儿子有 $m - i + 1$ 种选法，那么他儿子的选法总共有 $m!$ 种。

然后再乘上他每个儿子的只考虑子树内节点形成 dfs 序的方案数。

我们可以得到 $h[x] = jc[m]\times\prod\limits_{v \in e[x].v} h[v]$。

其中 $jc[i]$ 表示 $i$ 的阶乘，$e[x].v$ 表示 $x$ 的儿子节点。

设 $f[j][k]$ 表示在 $x$ 的儿子中选了 $j$ 个儿子，$s$ 和为 $k$ 的方案数。

其中 $s[x]$ 表示 $x$ 的子树中的总节点数。

$f[j][k]$ 可以通过背包的方式来求出。

每一个 $j \in [1,m],k \in [s[v],n] $ 由 $f[j - 1][k - s[v]],v \in e[x].v$ 转移而来。

因为我们把表示 $x$ 的那一维滚掉了，所以我们需要逆序来算上面的 $f[j][k]$。

然后我们假设我们现在已经处理到 $x$ 的儿子 $v$ 这个节点。

设 $g[k]$ 表示当前儿子节点 $v$ 排在 $x$ 后面 $k$ 个位置的方案数，$hx$ 为该节点除去儿子 $v$ 的方案以及去掉选 $m$ 个儿子的排列的方案。

我们知道 $f[j][k]$ 是 $x$ 的儿子中的总方案数，为了求出 $v$ 节点排在父亲后的方案,我们需要求出除去 $v$ 的方案数。

可以通过回退背包的做法，把 $v$ 的贡献减掉。

对于每个状态 $f[j][k]$ 我们把 $f[j - 1][k - s[v]]$ 的贡献给减掉，上面加入贡献我们是逆序做的，这里需要正序来减。

总的方案每一次计算新的 $v$ 都要使用，所以在这次的关于 $v$ 的计算完成后，要把这里减掉的贡献重新加回去。

对于选择的节点数量 $k \in [1,s[x]]$ 可以由不同的儿子节点的选择方式组成，那么 $g[x]$ 可以从 $f[j][k]$ 转移过来。

对于已选的 $j$ 个儿子，有 $j!$ 种选择，剩下的 $m - j - 1$ 个儿子，有 $(m - j - 1)!$ 种选择。

然后再乘上 $hx$ 就可以得到 $g[x]$。

这里的 $hx = \frac{h[x]}{h[v] \times m!}$ 是去除 $v$ 的子树中，$x$ 的子树中，其他节点的方案数。

现在我们求出了儿子节点排在父亲节点后 $k$ 个位置的方案数了，那么我们便可以推出他在整棵树中 dfs 序的情况了。

设 $dp[x][k]$ 表示 $x$ 在总的 dfs 序中排在位置 $k$ 的方案数（不计 $x$ 子树内部节点方案数）。

每个儿子节点的位置都可以从他父亲的位置往后推出来，即 $dp[v][j + k] = \sum\limits_{j\in[1,n],k\in[1,s[x]]} dp[x][j] \times g[k]$。

然后 $dp[i][j] \times h[i]$ 即为题目要求的最终的方案数。

我们对于每一个节点 $x$ 都要求一个 $f[j][k]$，每个 $f[j][k]$ 都需要遍历 $x$ 的儿子数以及所有的叶子节点数，这里的复杂度是 $O(n^3)$ 的。

同理其他几个状态的转移复杂度和这个也是同级的，所以总复杂度为 $O(n^3)$。

原本对于每个 $x$ 的每个 $v$ 单独求解除去 $v$ 的方案应该是 $O(n^4)$ 的复杂度，这里使用了回滚背包，优化成了 $O(n^3)$。

## 具体实现

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int read()
{
	int s = 0,f = 1; char x = getchar();
	while(x < '0' || '9' < x) f = (x == '-') ? -1 : 1 , x = getchar();
	while('0' <= x && x <= '9') s = s * 10 + x - '0' , x = getchar();
	return s * f;
}

const int N = 510;
const int mo = 998244353;

int n;
int s[N],ft[N];
int h[N],son[N];
int f[N][N];
int ans[N][N],dp[N][N];
int iv[N],fc[N];

vector <int> e[N];

int fpow(int x,int nn)
{
	int res = 1;
	while(nn)
	{
		if (nn & 1) res = (res * x) % mo;
		x = (x * x) % mo;
		nn >>= 1;
	}
	return res;
}

int inv(int x)//求逆元
{
	if (x <= n) return (iv[x] * fc[x - 1]) % mo;
	return fpow(x,mo - 2);
}

void dfs(int x,int fa)
{
	ft[x] = fa;
	s[x] = 1;
	h[x] = 1;
	for (int i = 0,v;i < e[x].size();i ++)
	{
		v = e[x][i];
		if (v == fa) continue;
		son[x] ++;
		dfs(v,x);
		h[x] = (h[x] * h[v]) % mo;//在x的子树内的方案数
		s[x] += s[v];
	}
	h[x] = (h[x] * fc[son[x]]) % mo;
	return;
}

void dfs1(int x)
{
	int m = son[x];
	vector<vector<int> > f(m + 1,vector<int>(s[x] + 1,0));
	f[0][0] = 1;//不选儿子一种方案
	for (int i = 0,v;i < e[x].size();i ++)
	{
		v = e[x][i];
		if (v == ft[x]) continue;
		for (int j = m;j >= 1;j --)
		{
			for (int k = s[x];k >= s[v];k --)
			{
				f[j][k] = (f[j][k] + f[j - 1][k - s[v]]) % mo;//选v这个儿子
			}
		}
	}
	
	for (int i = 0,v;i < e[x].size();i ++)
	{
		v = e[x][i];
		if (v == ft[x]) continue;
		
		int hx = (h[x] * inv(h[v]) % mo * iv[m]) % mo;//去掉儿子中v的方案数以及去掉 选m个儿子的排列的方案

		for (int j = 1;j <= m;j ++)
			for (int k = s[v];k <= s[x];k ++)
				f[j][k] = ((f[j][k] - f[j - 1][k - s[v]]) % mo + mo) % mo;//去掉儿子v的方案数
		
		vector <int> g(n + 1,0);//g[k]表示在x后k个位置的方案数
		
		for (int j = 0;j < m;j ++)
			for (int k = 0;k < s[x];k ++)
				g[k + 1] = (g[k + 1] + f[j][k] * hx % mo * fc[j] % mo * fc[m - j - 1]) % mo;

		for (int j = 1;j <= n;j ++)
			for (int k = 1;k <= s[x];k ++)
				dp[v][j + k] = (dp[v][j + k] + dp[x][j] * g[k]) % mo;
		
		for (int j = m;j >= 1;j --)
			for (int k = s[x];k >= s[v];k --)
				f[j][k] = (f[j][k] + f[j - 1][k - s[v]]) % mo;
		
		dfs1(v);
	}
	return;
}

signed main()
{
	n = read();
	
	fc[0] = 1;
	for (int i = 1;i <= n + 1;i ++) fc[i] = (fc[i - 1] * i) % mo;
	iv[n + 1] = fpow(fc[n + 1],mo - 2);
	for (int i = n;i >= 0;i --) iv[i] = (iv[i + 1] * (i + 1)) % mo;//求阶乘逆元
	
	for (int i = 1,u,v;i < n;i ++)
	{
		u = read() , v = read();
		e[u].push_back(v) , e[v].push_back(u);
	}
	
	dfs(1,0);
	
	dp[1][1] = 1;
	
	dfs1(1);
	
	for (int i = 1;i <= n;i ++)
	{
		for (int j = 1;j <= n;j ++)
		{
			ans[i][j] = (dp[i][j] * h[i]) % mo;
			cout << ans[i][j] << ' ';
		}
		puts("");
	}
	return 0;
}
```

## 后话

这篇题解主要是参考了 [2022 International Collegiate Programming Contest, Jinan Site C. DFS Order 2(树形dp+回滚背包)](https://blog.csdn.net/Code92007/article/details/133590804) 和 [2022 ICPC 济南站 C (回退背包)](https://zhuanlan.zhihu.com/p/587399484) 还有 [P9669 [ICPC2022 Jinan R] DFS Order 2](https://www.cnblogs.com/Livingston/p/17785680.html) 三位大佬的题解。

---

## 作者：Thunder_S (赞：8)

## Solution

先考虑怎么求总方案数。设 $t_x$ 表示以 $x$ 为根节点的子树的总方案数。有 $t_x=son_x!\times \prod\limits_{y\in son} t_{y}$（$son_x$ 表示 $x$ 的儿子数）。

设 $ans_{x,i}$ 表示点 $i$ 在 $\text{dfs}$ 序中的位置为 $i$ 的答案（不考虑 $x$ 子树内部的顺序）。因为 $\text{dfs}$ 是从 $x$ 走到 $x$ 的儿子 $y$，所以转移也考虑从 $x$ 转移到 $y$。枚举 $y$ 和 $x$ 的 $\text{dfs}$ 序差几，有 $ans_{y,j}=\sum ans_{x,i}\times g_{j-i}$，其中 $g_{j-i}$ 表示在 $\text{dfs}$ 序中 $y$ 与 $x$ 差 $j-i$ 的方案数。

考虑 $g$ 的转移。枚举当前节点 $y$ 前有多少个点 $i$，它们的大小的和是 $j$。设 $f_{i,j}$ 表示在 $x$ 的儿子中选了 $i$ 个，大小为 $j$ 的方案数。$f$ 可以用背包来维护。那么 $g_{j+1}=\sum f_{i,j}\times j!\times (son_x-1-j)!\times \frac{t_x}{t_y\times son_x!}$。其中，$j!$ 和 $(son_x-1-j)!$ 分别表示 $y$ 前和 $y$ 后的兄弟节点的排列顺序，$\frac{t_x}{t_y\times son_x!}$ 表示 $x$ 的儿子中，除了 $y$ 的子树内部方案数的积。因为 $ans$ 定义的时候就要求不能考虑 $y$ 子树内部的方案数，因此要除去 $y$ 的子树带来的贡献。

那么最后答案为 $ans_{x,i}\times t_x$。

但是，求 $f$ 的过程是 $\mathcal O(n^4)$ 的。因此考虑写回滚背包，就是先求出所有儿子带来的贡献，再减去目标儿子节点带来的贡献即可。优化至 $\mathcal O(n^3)$。

## Code
```cpp
#include<cstdio>
#include<cstring>
#define N 505
#define mod 998244353
#define ll long long
using namespace std;
int n,tot,son[N],siz[N];
ll jc[N],ans[N][N],f[N][N],g[N],t[N];
struct node {int to,next,head;}a[N<<1];
void add(int x,int y)
{
    a[++tot].to=y;a[tot].next=a[x].head;a[x].head=tot;
    a[++tot].to=x;a[tot].next=a[y].head;a[y].head=tot;
}
ll ksm(ll x,ll y)
{
    ll res=1;
    while (y)
    {
        if (y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
void gett(int x,int fa)
{
    ll res=1;
    siz[x]=1;t[x]=1;
    for (int i=a[x].head;i;i=a[i].next)
    {
        int y=a[i].to;
        if (y==fa) continue;
        gett(y,x);
        son[x]++;siz[x]+=siz[y];
        t[x]=t[x]*t[y]%mod;
    }
    t[x]=t[x]*jc[son[x]]%mod;
}
void dfs(int x,int fa)
{
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for (int i=a[x].head;i;i=a[i].next)
    {
        int y=a[i].to;
        if (y==fa) continue;
        for (int j=son[x];j;--j)
            for (int k=siz[y];k<=siz[x];++k)
                f[j][k]=(f[j][k]+f[j-1][k-siz[y]])%mod;
    }
    for (int i=a[x].head;i;i=a[i].next)
    {
        int y=a[i].to;
        ll base=t[x]*ksm(t[y],mod-2)%mod*ksm(jc[son[x]],mod-2)%mod;
        if (y==fa) continue;
        for (int j=1;j<=son[x];++j)
            for (int k=siz[y];k<=siz[x];++k)
                f[j][k]=(f[j][k]-f[j-1][k-siz[y]]+mod)%mod;
        memset(g,0,sizeof(g));
        for (int j=0;j<son[x];++j)
            for (int k=0;k<siz[x];++k)
                g[k+1]=(g[k+1]+f[j][k]*jc[j]%mod*jc[son[x]-1-j]%mod*base%mod)%mod;
        for (int j=1;j<=n;++j)
            for (int k=j+1;k<=n;++k)
                ans[y][k]=(ans[y][k]+ans[x][j]*g[k-j]%mod)%mod;
        for (int j=son[x];j;--j)
            for (int k=siz[y];k<=siz[x];++k)
                f[j][k]=(f[j][k]+f[j-1][k-siz[y]])%mod;
    }
    for (int i=a[x].head;i;i=a[i].next)
    {
        int y=a[i].to;
        if (y==fa) continue;
        dfs(y,x);
    }
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    jc[0]=1;
    for (int i=1;i<=n;++i)
        jc[i]=jc[i-1]*(ll)i%mod;
    gett(1,0);
    ans[1][1]=1;
    dfs(1,0);
    for (int i=1;i<=n;++i)
    {
        for (int j=1;j<=n;++j)
            printf("%lld ",ans[i][j]*t[i]%mod);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：To_our_starry_sea (赞：5)

萌萌树上 dp 题，不过细节有点多，~~还要注意常数~~。
## Part 1 思路
看到这一类计数题，我们可以很直接的想到设 $dp_{i,j}$ 为节点 $i$ 的 dfs 序为 $j$ 的方案数。但如果这样设计，容易发现很难从一个节点转移到其子结点。因此我们规定 $dp_{i,j}$ 为节点 $i$ 在不考虑其子树内部的情况下 dfs 序为 $j$ 的方案数，则最终的答案矩阵 $ans_{i,j} = dp_{i,j} \times w_i$，其中 $w_i$ 表示遍历 $i$ 的子树的方案数。

较为简单的，设 $size_u$ 表示 $u$ 的子结点个数，则 $w_u = size_u! \times \prod_{v \in son(u)} w_v$。注意前面的系数来源于遍历子结点顺序不同。

接下来，我们发现从父节点 $u$ 向子结点 $v$ 转移需要一个权值矩阵 $g_{i,j}$。表示**在不考虑先后顺序**的前提下从 $u$ 开始遍历再到开始遍历 $v$ 所在的子树且中间恰好经过了 $i$ 个不同的 $u$ 的子结点所在的子树与 $j$ 个不同的节点。换句话说，就是从 $u$ 的子结点中选出 $i$ 个不为 $v$ 的点，其子树大小的和为 $j$ 的方案数。这个明显可以用类似背包的方法做。那么从 $u$ 到 $v$ 经过节点数量为 $x$ 的方案数为 $now_x = \sum_{i = 1}^{size_u - 1} g_{i,x} \times (i - 1)! \times (size_u - i - 1)! \times \frac{w_u}{w_v \times size_u!}$，$(i - 1)!$ 与 $(size_u - i - 1)!$ 的系数来源前后两部分的顺序任意，而 $\frac{w_u}{w_v \times size_u!}$ 则来源于考虑 $v$ 的兄弟节点内部顺序的贡献。同时注意特判 $now_0$ 的情况。

最后我们发现，$dp_{v, i} = \sum_{j = 1}^{i - 1}dp_{u, j} \times now_{i - j - 1}$。但此时由于对每个节点都需要计算一次 $g$ 与 $now$，这使得时间复杂度为 $O(n^4)$，这是无法接受的。因此需要提前计算对于每一个节点 $u$ 所有的子结点所贡献的 $g$ 与 $now$，然后再消去每一个节点的贡献。~~我是不会告诉你我一开始是不知道这叫回滚背包的。~~ 最后就是 $O(n^3)$ 的了。

## Part 2 代码
注意数组要及时清空，转移系数要预处理同时取模可以优化。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 505;
const ll MOD = 998244353;
int n, cnt = 0, head[MAXN];
int f[MAXN][MAXN][MAXN], dp[MAXN][MAXN];
ll sum[MAXN], w[MAXN], S[MAXN], jc[MAXN], ans[MAXN][MAXN], now[MAXN];
struct edge {
	int to, next;
} e[MAXN << 1];
inline void add(int u, int v) {
	cnt++;
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}
inline ll qmi(ll a, ll b) {
	ll res = a, ans = 1;
	while (b) {
		if (b & 1) ans = ans * res % MOD;
		res = res * res % MOD;
		b >>= 1;
	}
	return ans;
}
inline void dfs(int u, int pre) {
	sum[u] = 1, w[u] = 1;
	for (int i = head[u]; i; i = e[i].next) {
		 int v = e[i].to;
		 if (v == pre) continue;
		 S[u]++;
		 dfs(v, u);
		 w[u] = w[u] * w[v] % MOD, sum[u] += sum[v];
	}
	w[u] = w[u] * jc[S[u]] % MOD;
}
inline void dfs1(int u, int pre) {
	f[u][0][0] = 1;
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (v == pre) continue;
		for (int j = S[u]; j >= 1; j--) {
			for (int k = sum[u]; k >= sum[v]; k--) f[u][j][k] = ((f[u][j][k] + f[u][j - 1][k - sum[v]]) >= MOD ? (f[u][j][k] + f[u][j - 1][k - sum[v]]) - MOD : (f[u][j][k] + f[u][j - 1][k - sum[v]]));
		}
        dfs1(v, u);
	}
}
inline void dfs2(int u, int pre) {
	f[u][0][0] = 1;
	if (u == 1) ans[1][1] = 1;
	else if (u != 1) {
		
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) dp[i][j] = 0;
		}
		dp[1][sum[u]] = (f[pre][1][sum[u]] - 1 + MOD) % MOD;
		for (int i = 1; i <= S[pre]; i++) {
			for (int j = 0; j <= sum[pre]; j++) {
				if (i == 1 && j == sum[u]) continue;
				else if ((i < S[pre] && j < sum[u]) ) dp[i][j] = f[pre][i][j];
				else dp[i][j] = (f[pre][i][j] - dp[i - 1][j - sum[u]] < 0 ? f[pre][i][j] - dp[i - 1][j - sum[u]] + MOD : f[pre][i][j] - dp[i - 1][j - sum[u]]);
			}
		}
		
		for (int j = 0; j < n; j++) now[j] = 0;
		now[0] = jc[S[pre] - 1] * w[pre] % MOD * qmi(w[u], MOD - 2) % MOD * qmi(jc[S[pre]], MOD - 2) % MOD;
		ll xs = w[pre] % MOD * qmi(w[u], MOD - 2) % MOD * qmi(jc[S[pre]], MOD - 2) % MOD;
		for (int i = 1; i < S[pre]; i++) {
			for (int j = 1; j <= sum[pre]; j++) now[j] = (now[j] + dp[i][j] * jc[i] % MOD * jc[S[pre] - i - 1] % MOD * xs % MOD) % MOD;
		}
		
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) ans[u][j] = (ans[u][j] + ans[pre][i] * now[j - i - 1] % MOD) % MOD;
		}
	}
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (v == pre) continue;
		for (int j = S[u]; j >= 1; j--) {
			for (int k = sum[u]; k >= sum[v]; k--) f[u][j][k] = ((f[u][j][k] + f[u][j - 1][k - sum[v]]) >= MOD ? (f[u][j][k] + f[u][j - 1][k - sum[v]]) - MOD : (f[u][j][k] + f[u][j - 1][k - sum[v]]));
		}
		//dfs2(v, u);
	}
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (v == pre) continue;
		dfs2(v, u);
	}
}
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
inline ll R() {
	ll x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main() {
    n = read();
    for (int i = 1; i <= n - 1; i++) {
		int u = read(), v = read();
		add(u, v), add(v, u);
	}
	jc[0] = 1;
	for (ll i = 1; i <= n; i++) jc[i] = jc[i - 1] * i % MOD;
	dfs(1, 0);
	//dfs1(1, 0);
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) printf("%lld ", ans[i][j] * w[i] % MOD);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：4)

声明：本文并不是标算的 $O\left(n^3\right)$ 做法题解，而是 $O\left(n^2\sqrt n\right)$ 的 Bonus 的题解。请确保你已经会了标算的三方做法再来看这篇题解，三方做法的细节将不予描述，可以参考代码 https://www.luogu.com.cn/paste/fjk0rzr5

不妨先分析复杂度瓶颈。

* $g$：转移时只涉及到儿子，而我们知道 $u=fa(v)$ 的 $(u,v)$ 对只有 $n-1$ 个，所以是 $O\left(n\right)$ 的。
* $f'$：我们发现链长为 $1$ 的菊花图就是复杂度上界，无论怎么卡转移的状态的上下界，复杂度都是 $O\left(n^3\right)$ 的。
* $f$：分析同 $f'$，也是 $O\left(n^3\right)$。
* $h$：这个也是 $O\left(n^3\right)$ 的，因为复杂度大致就是一个 $\sum siz_u(n-siz_u)$。

我们发现一个性质，在对于节点 $u$，用它的状态求 $v\in son(u)$ 的状态时，如果两个儿子 $v_1,v_2$ 满足 $siz_{v_1}=siz_{v_2}$，那么它们对应的 $f,h$ 都应该是相同的。所以我们考虑将子树 $siz$ 相同的儿子放在一起处理，可以直接看作同一个，然后由于 $\sum siz_v\le n$，实际上不同的 $siz_v$ 只有至多 $\sqrt n$ 种。这时候我们就变成了一个只有 $\sqrt n$ 种物品的多重背包，如果能在 $O\left(n^2\sqrt n\right)$ 内求得 $f'$，那么 $g,h$ 都是好求的了，因为只要考虑 $\sqrt n$ 个儿子。

$f'$ 实际上是一个需要记录物品数量的背包，我们考虑对 $f'$ 也是用类似于退背包的技巧，直接同时求 $f'$ 和 $f$，那么当我们选物品 $j$ 时，从 $f_{j}$ 来转移，就能保证不会选超过 $cnt_j$ 个 $j$ 物品。这样的话 $f',f,h$ 的复杂度就都变为了 $O\left(n^2\sqrt n\right)$。

CF 上的标程。

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); ++i) 
#define R(i, j, k) for(int i = (j); i >= (k); --i) 
#define ll long long 
#define vi vector < int > 
#define sz(a) ((int) (a).size()) 
#define me(a, x) memset(a, x, sizeof(a)) 
using namespace std;
const int N = 507, FF = sqrt(N * 2) + 5, mod = 998244353; 
int qpow(int x, int y = mod - 2) {
	int res = 1;
	for(; y; x = (ll) x * x % mod, y >>= 1) if(y & 1) res = (ll) res * x % mod;
	return res;
}
int n, fa[N], fac[N], ifac[N], inv[N];
void inif(int n) {
	fac[0] = ifac[0] = inv[1] = 1;
	L(i, 2, n) inv[i] = (ll) inv[mod % i] * (mod - mod / i) % mod;
	L(i, 1, n) fac[i] = (ll) fac[i - 1] * i % mod, ifac[i] = (ll) ifac[i - 1] * inv[i] % mod;
}

vi e[N];
int siz[N], prd[N], ivprd[N]; 
void init(int x) {
	siz[x] = 1;
	int deg = 0;
	prd[x] = 1, ivprd[x] = 1;
	for(const int &v : e[x]) if(v != fa[x]) 
		fa[v] = x, init(v), siz[x] += siz[v], prd[x] = (ll) prd[x] * prd[v] % mod, ++deg, 
		ivprd[x] = (ll) ivprd[x] * ivprd[v] % mod;
	prd[x] = (ll) prd[x] * fac[deg] % mod;
	ivprd[x] = (ll) ivprd[x] * ifac[deg] % mod;
}

int dp[N][N], ns[N][N], kk[N];
int pm[N][N], rH[N];

int F[N]; 
int G[FF][N], H[FF][N];
int v[N], arc[N], tot;

void dfs(int x, int all) {
	vi _G;
	for(const int &v : e[x]) if(v != fa[x]) _G.emplace_back(v);
	
	int cnt = sz(_G);
	
	for(auto u : _G) 
		all = (ll) all * prd[u] % mod;
	L(i, 1, n) 
		ns[x][i] = (ll) dp[x][i] * all % mod * fac[sz(_G)] % mod;
	
	map < int, vi > mp;
	L(p, 0, cnt - 1) 
		mp[siz[_G[p]]].emplace_back(_G[p]);
	
	L(i, 0, cnt - 1) kk[i] = (ll) fac[i] * fac[cnt - i - 1] % mod;
	kk[cnt] = kk[cnt + 1] = 0;
	
	tot = 0;
	int sums = 0;
	for(auto U : mp) 
		sums += U.first * sz(U.second), ++tot, v[tot] = U.first, arc[tot] = sz(U.second);
	
	me(F, 0);
	L(p, 1, tot) me(H[p], 0), me(G[p], 0);
	F[0] = 1;
	L(i, 1, tot) G[i][0] = 1, (H[i][0] += kk[0]) %= mod; 
	
	L(i, 1, cnt) {
		R(j, sums, 0) {
			F[j] = 0; 
			L(p, 1, tot) 
				if(j >= v[p] && G[p][j - v[p]]) 
					(F[j] += (ll) arc[p] * G[p][j - v[p]] % mod) %= mod;
			F[j] = (ll) F[j] * inv[i] % mod;
			L(p, 1, tot) {
				G[p][j] = F[j];
				if(j >= v[p] && G[p][j - v[p]]) 
					(G[p][j] += mod - G[p][j - v[p]]) %= mod;
				(H[p][j] += (ll) G[p][j] * kk[i] % mod) %= mod;
			}
		}
	}
	
	L(p, 1, tot) {
		vi vc = mp[v[p]];
		
		me(rH, 0);
		L(i, 0, sums) if(H[p][i]) {
			L(k, 0, n) if(dp[x][k]) {
				(rH[k + i + 1] += (ll) dp[x][k] * H[p][i] % mod) %= mod;
			}
		}
		
		for(auto u : vc) 
			L(i, 0, n) 
				dp[u][i] = rH[i];
	}
	
	for(const int &v : _G) 
		dfs(v, (ll) all * ivprd[v] % mod);
}

mt19937_64 orz;
int main() {
	ios :: sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
//	n = 500;
	inif(n + 1);
	L(i, 1, n - 1) {
		int u = i, v = i + 1;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	
	init(1);
	dp[1][1] = 1, dfs(1, 1);
	
	L(i, 1, n) {
		L(j, 1, n) 
			cout << ns[i][j] << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Egg_laying_master (赞：3)

## Description

P 哥有一棵树，根节点是 $1$，总共有 $n$ 个节点，从 $1$ 到 $n$ 编号。

他想从根节点开始进行深度优先搜索。他想知道对于每个节点 $v$，在深度优先搜索中，它出现在第 $j$ 个位置的方式有多少种。深度优先搜索的顺序是在搜索过程中访问节点的顺序。节点出现在第 $j\ (1 \leq j \le n)$ 个位置表示它在访问了 $j - 1$ 个其他节点之后才被访问。因为节点的子节点可以以任意顺序访问，所以有多种可能的深度优先搜索顺序。

P 哥想知道对于每个节点 $v$，有多少种不同的深度优先搜索顺序，使得 $v$ 出现在第 $j$ 个位置。对于每个 $v$ 和 $j\ (i \le v,j \le n)$ 计算答案。

答案可能很大，所以输出时要取模 $998244353$。

$1\leq n\leq 500$。

以下是深度优先搜索的伪代码，用于处理树。在调用 `main()` 函数后，`dfs_order` 将会包含深度优先搜索的顺序。

```
void dfs(u):
  dfs_order.push_back(u)
  for (auto v : son(u))
    dfs(v)

void main():
  dfs_order = {}
  dfs(1)
```

## Solution

考虑树形 DP。

设 $f_{i}$ 表示 $i$ 的子树任意排列的方案数，这个东西是很好求的，$g_{i,j}$ 表示走到了 $i$，并且 $i$ 当前在第 $j$ 个的方案数。

假设当前是从 $u\to v$，然后会发现这个 $g$ 的转移会受到 $u$ 子树以外的点的影响，这个是不好搞的。

容易发现只要把 $g_{i,j}$ 改成表示走到了 $i$，并且 $i$ 当前在第 $j$ 个的**概率**，那么这个时候就只要考虑 $u$ 子树里对 $v$ 的影响了。

设 $h_{i,j}$ 表示 $u$ 的子树里去掉 $v$，选 $i$ 个无序儿子使得他们的子树大小和为 $j$ 的方案数。容易发现 $h_{i,j}$ 可以先用考虑所有儿子的答案，然后利用 01 背包的可撤销性求得。

所以这里 $v$ 的编号比 $u$ 的编号大 $i+1$ 的概率就是 

$$\frac{\sum\limits_{j=0}^{cnt-1}{h_{j,i}\times j!\times (cnt-1-j)!}}{cnt!}$$

其中 $cnt$ 表示 $u$ 的儿子个数。

然后只要枚举 $u$ 的编号为 $k$ 的概率和 $v$ 比 $u$ 大 $i$ 的概率即可得到 $v$ 的编号为 $k+i$ 的概率。

最后只要把所有的概率乘 $f_1$ 就是答案。

时间复杂度：$O(n^3)$。

## Code

```cpp
#include <bits/stdc++.h>

// #define int int64_t

namespace Modular {
template<class T>
T qpow(T bs, T idx, T kMod) {
  bs %= kMod;
  int ret = 1;
  for (; idx; idx >>= 1, bs = 1ll * bs * bs % kMod)
    if (idx & 1)
      ret = 1ll * ret * bs % kMod;
  return ret;
}
int inv(int x, int kMod) {
  x %= kMod;
  if (!x) { std::cerr << "inv error\n"; return 0; }
  return qpow(x, kMod - 2, kMod);
}
template<class T, const T kMod>
T add(T x, T y) {
  if (x + y >= kMod) return x + y - kMod;
  else return x + y;
}

template<class T, const T kMod>
T minu(T x, T y) {
  if (x - y < 0) return x - y + kMod;
  else return x - y;
}

template<class T, const T kMod>
struct Mint {
  T x;

  Mint() { x = 0; }
  template<class _T> Mint(_T _x) { x = _x; }

  friend Mint operator +(Mint m1, Mint m2) { return Mint(Modular::add<T, kMod>(m1.x, m2.x)); }
  friend Mint operator -(Mint m1, Mint m2) { return Mint(Modular::minu<T, kMod>(m1.x, m2.x)); }
  friend Mint operator *(Mint m1, Mint m2) { return Mint(1ll * m1.x * m2.x % kMod); }
  friend Mint operator /(Mint m1, Mint m2) { return Mint(1ll * m1.x * inv(m2.x, kMod) % kMod); }
  Mint operator +=(Mint m2) { return x = Modular::add<T, kMod>(x, m2.x); }
  Mint operator -=(Mint m2) { return x = Modular::minu<T, kMod>(x, m2.x); }
  Mint operator *=(Mint m2) { return x = 1ll * x * m2.x % kMod; }
  Mint operator /=(Mint m2) { return x = 1ll * x * inv(m2.x, kMod) % kMod; }

  template<class _T> friend Mint operator +(Mint m1, _T m2) { return Mint(Modular::add<T, kMod>(m1.x, m2 % kMod)); }
  template<class _T> friend Mint operator -(Mint m1, _T m2) { return Mint(Modular::minu<T, kMod>(m1.x, m2 % kMod)); }
  template<class _T> friend Mint operator *(Mint m1, _T m2) { return Mint(1ll * m1.x * m2 % kMod); }
  template<class _T> friend Mint operator /(Mint m1, _T m2) { return Mint(1ll * m1.x * inv(m2, kMod) % kMod); }
  template<class _T> Mint operator +=(_T m2) { return x = Modular::add<T, kMod>(x, m2); }
  template<class _T> Mint operator -=(_T m2) { return x = Modular::minu<T, kMod>(x, m2); }
  template<class _T> Mint operator *=(_T m2) { return x = 1ll * x * m2 % kMod; }
  template<class _T> Mint operator /=(_T m2) { return x = 1ll * x * inv(m2, kMod) % kMod; }
  template<class _T> friend Mint operator +(_T m1, Mint m2) { return Mint(Modular::add<T, kMod>(m1 % kMod, m2.x)); }
  template<class _T> friend Mint operator -(_T m1, Mint m2) { return Mint(Modular::minu<T, kMod>(m1 % kMod, m2)); }
  template<class _T> friend Mint operator *(_T m1, Mint m2) { return Mint(1ll * m1 * m2.x % kMod); }
  template<class _T> friend Mint operator /(_T m1, Mint m2) { return Mint(1ll * m1 * inv(m2.x, kMod) % kMod); }
  friend Mint operator -(Mint &m1) { return Mint(m1.x == 0 ? (kMod - 1) : (m1.x - 1)); }
  friend Mint operator --(Mint &m1) { return m1 = Mint(m1.x == 0 ? (kMod - 1) : (m1.x - 1)); }
  friend Mint operator ++(Mint &m1) { return m1 = Mint(m1.x == (kMod - 1) ? 0 : (m1.x + 1)); }
  friend bool operator ==(Mint m1, Mint m2) { return m1.x == m2.x; }

  friend std::istream &operator >>(std::istream &is, Mint &m) {
    int x;
    is >> x;
    m = Mint(x);
    return is;
  }
  friend std::ostream &operator <<(std::ostream &os, Mint m) {
    os << m.x;
    return os;
  }
};
} // namespace Modular

using mint = Modular::Mint<int, 998244353>;

const int kMaxN = 505;

int n;
int sz[kMaxN];
std::vector<int> G[kMaxN];
mint f[kMaxN], g[kMaxN][kMaxN], fac[kMaxN], ifac[kMaxN]; // f[i] : i 的子树的方案数, g[i][j] : i 排在第 j 个的概率

mint C(int m, int n) {
  if (m < n || m < 0 || n < 0) return 0;
  return fac[m] * ifac[n] * ifac[m - n];
}

void dfs1(int u, int fa) {
  f[u] = sz[u] = 1;
  int ct = 0;
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    sz[u] += sz[v];
    f[u] *= f[v] * (++ct);
  }
}

void dfs2(int u, int fa) {
  static mint ff[kMaxN][kMaxN], tmp[kMaxN];
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= n; ++j)
      ff[i][j] = 0;
  ff[0][0] = 1;
  int now = 0, cnt = 0;
  mint mul = 1;
  for (auto v : G[u]) {
    if (v == fa) continue;
    mul *= f[v];
    ++cnt;
    for (int i = cnt; i; --i)
      for (int j = sz[v]; j <= n; ++j)
        ff[i][j] += ff[i - 1][j - sz[v]];
    now += sz[v];
  }
  for (auto v : G[u]) {
    if (v == fa) continue;
    for (int i = 0; i <= n; ++i)
      tmp[i] = 0;
    for (int i = 1; i <= cnt; ++i)
      for (int j = sz[v]; j <= n; ++j)
        ff[i][j] -= ff[i - 1][j - sz[v]];
    for (int i = 0; i <= cnt - 1; ++i) {
      for (int j = 0; j <= n; ++j) {
        tmp[j] += ff[i][j] * fac[i] * fac[cnt - 1 - i] * mul;
      }
    }
    for (int i = cnt; i; --i)
      for (int j = sz[v]; j <= n; ++j)
        ff[i][j] += ff[i - 1][j - sz[v]];
    mint val = 1 / f[u];
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= n - 1 - i; ++j)
        g[v][i + j + 1] += g[u][i] * tmp[j] * val;
  }
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs2(v, u);
  }
}

void dickdreamer() {
  std::cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    G[u].emplace_back(v), G[v].emplace_back(u);
  }
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i;
    ifac[i] = 1 / fac[i];
  }
  dfs1(1, 0);
  g[1][1] = 1;
  dfs2(1, 0);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j)
      std::cout << g[i][j] * f[1] << ' ';
    std::cout << '\n';
  }
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
  int T = 1;
  // std::cin >> T;
  while (T--) dickdreamer();
  // std::cerr << 1.0 * clock() / CLOCKS_PER_SEC << "s\n";
  return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：3)

谢邀，人在考场，转移写反，老师不给大样例，顺利爆炸。

考虑这样一个状态 $dp_{u,k}$ 表示点 $u$ 的 DFS 序为 $k$ 并且 **不考虑其子树内的 DFS 序** 的方案数。

有转移方程 $dp_{u,k} = \sum dp_{fa_u,k-l} \times w_l$。

其中 $w_l$ 表示是一个以子树大小为物品大小的计数背包，但是注意到求关于点 $v$ 的背包时需要把其自己的贡献减去，一个小小的问题是这么做是 $O(n^4)$ 的，过不去，怎么办？

不难发现我们其实只要先把所有物品拿进来做背包再分别把某个物品删除或者拿回来即可，回退背包可以胜任，复杂度是 $O(n^3)$ 的，可以通过。

注意预处理阶乘和逆元，记得取模。

```cpp
/*
dp[u][k] 点 u 是第 k 个被访问到的方案数
count[u] 遍历以 u 为根的整个子树的方案数 
*/ 
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int maxn = 510;
int qpow(int a,int b){
	if(b==0) return 1;
	if(b==1) return a%mod;
	int res=qpow(a,b/2);
	res=(res*res)%mod;
	if(b%2==1) res=(res*a)%mod;
	return res;
}
int dp[maxn][maxn],sz[maxn],Cnt[maxn],fac[maxn],inv[maxn],n,Sum[maxn];
vector<int> edge[maxn];
inline void dfs(int u,int fa){
	sz[u]=Cnt[u]=1;
	int val=1,sum=1;
	for(int v:edge[u]){
		if(v==fa) continue;
		val=(val*sum)%mod;
		sum++;
		dfs(v,u);
		Cnt[u]=(Cnt[u]*Cnt[v])%mod;
		sz[u]+=sz[v];
	}  
	Cnt[u]=(Cnt[u]*val)%mod;
}
int cnt[maxn][maxn];
inline void DP(int u,int fa){
	memset(cnt,0,sizeof(cnt));
	cnt[1][0]=fac[edge[u].size()-2];
	for(int son:edge[u]){
		if(son==fa) continue;
		for(int i=sz[u]-sz[son];i>=0;i--){
			for(int j=1;j<edge[u].size();j++){
				cnt[i+sz[son]][j]=(cnt[i+sz[son]][j]+((cnt[i][j-1]*inv[edge[u].size()-1-j]%mod)*j%mod))%mod;	
			}	
		}		
	}
	for(int v:edge[u]){
		if(v==fa) continue;
		memset(Sum,0,sizeof(Sum));
		int d=1;
		for(int son:edge[u]){
			if(son==v||son==fa) continue;
			d=(d*Cnt[son])%mod;
		}
		int son=v;
		for(int i=0;i<=sz[u]-sz[son];i++){
			for(int j=1;j<=edge[u].size()-1;j++){
				cnt[i+sz[son]][j]=(cnt[i+sz[son]][j]+mod-((cnt[i][j-1]*inv[edge[u].size()-1-j]%mod)*j%mod))%mod;	
			}	
		}	
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++) Sum[i]=(Sum[i]+cnt[i][j])%mod;
		}
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++){
				if(i+j<=n){
					dp[v][i+j]=(dp[v][i+j]+(dp[u][i]*Sum[j])%mod)%mod;
				}
			}
		}
		for(int i=0;i<=n;i++) dp[v][i]=(dp[v][i]*d)%mod;
		for(int i=sz[u]-sz[son];i>=0;i--){
			for(int j=1;j<edge[u].size();j++){
				cnt[i+sz[son]][j]=(cnt[i+sz[son]][j]+((cnt[i][j-1]*inv[edge[u].size()-1-j]%mod)*j%mod))%mod;	
			}	
		}	
	}
	for(int v:edge[u]){
		if(v!=fa) DP(v,u);
	}
	return ;
}
signed main(){
	//freopen("T3.in","r",stdin);
	//freopen("T3.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	fac[0]=1;
	for(int i=1;i<=n;i++) inv[i]=qpow(i,mod-2),fac[i]=(fac[i-1]*i)%mod;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	edge[1].push_back(0);
	dfs(1,0);
	dp[1][1]=1;
	DP(1,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<(dp[i][j]*Cnt[i])%mod<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
/*
5 
1 2 
1 3 
3 4 
3 5
*/
```


---

## 作者：phil071128 (赞：3)

打 ICPC2023 Jinan R 之前可能vp过这一场，但显然当时还不会这个题，今天模拟赛搬了此题很快秒了，记录一下。

首先，自底向上 DP 是很困难且不符合 DFN 实际意义的，我们考虑自上而下做。

总的个数（即 $ans_{1,1}$）是好求的，有转移方程：$h_{x}=\prod h_{y}\times son!$，其中 $son$ 是儿子个数。

那么有了初始边界即可向下递推，考虑由 $ans_{x,i}$ 转移到 $ans_{y,i+j}$。

相当于对每个儿子进行决策，我们需要记录以下两个信息：$y$ 是 $x$ 第几个遍历的子树，$y$ 前面遍历的子树 $siz$ 和是多少。分别记作 $s_1,s_2$。

记录前者是因为，转移系数是两个阶乘相乘的形式，记录后者则是考虑接下来在 dfs 序上的位置。更具体的：
$$
ans[x][i]\times \frac{s1!\times (son-s1-1)!}{son!}\to ans[y][i+s2]
$$
这一步可以轻松做到 $O(n^3)$，所以只需解决 $s_1$ 和 $s_2$。

我们将 $s_2$ 看作背包的容量，$s_1$ 看作背包的另一个维度，每个子树大小为物品体积，即可 $O(n^2)$ 对于每个 $x$ 求出答案。但是问题在于，在子树 $y$ 转移过程中，需要强制钦定 $y$ 不能选。

想到**退背包**，对于每个 $y$，再 $O(n^2)$ 的强制钦定不选即可。退背包有模板：[P4141 消失之物 - 洛谷 | 计算机科学教育新生态](https://www.luogu.com.cn/problem/P4141)，具体思想是：正序枚举背包大小，如果 $j< w_i$，那么一定不包含当前物品，$ans[j]=dp[j]$，否则，需要减去能转移到包含当前物品的个数，即 $ans[j]=dp[j]-ans[j-w[i]]$。


```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("gravekeeper.in","r",stdin);
	freopen("gravekeeper.out","w",stdout);
}
const int mod=998244353,N=510;
int dp[N][N],tmp[N],f[N][N],siz[N],fac[N];
int ans[N][N],n,h[N];
vector<int>s[N];
void calcsiz(int x,int fa) {
	siz[x]=1;
	h[x]=1;
	int tot=0;
	for(int y:s[x]) {
		if(y==fa) continue;
		calcsiz(y,x);
		tot++;
		h[x]=h[x]*h[y]%mod;
		siz[x]+=siz[y];
	}
	h[x]=h[x]*fac[tot]%mod;
} 
int ksm(int a,int b) {
	if(b==1) return a;
	int s=ksm(a,b/2);s=s*s%mod;
	if(b%2==1) s=s*a%mod;
	return s;
}
void dfs(int x,int fa) {
	vector<int>g;
	for(int y:s[x]) {
		if(y==fa) continue;
		g.push_back(y);
	}
	memset(dp,0,sizeof dp);
	dp[0][0]=1;//siz[x]=1
	for(int i=0;i<g.size();i++) {
		for(int j=n;j>=siz[g[i]];j--) 
		for(int k=1;k<=g.size();k++) {
			dp[j][k]=(dp[j][k]+dp[j-siz[g[i]]][k-1])%mod;
		}
	}
	memset(f,0,sizeof f);
	memset(tmp,0,sizeof tmp);
	int _inv=ksm(fac[g.size()],mod-2);
	for(int i=0;i<g.size();i++) {
		int y=g[i];
		f[0][0]=tmp[0]=1;
		int sum=0;
		for(int j=0;j<=siz[x];j++) {
			tmp[j]=0;
			for(int k=0;k<=g.size()-1;k++) {
				if(j<siz[y]) f[j][k]=dp[j][k];
				else f[j][k]=(dp[j][k]-f[j-siz[y]][k-1]+mod)%mod;
				tmp[j]+=(f[j][k]*fac[k]%mod*fac[g.size()-k-1]%mod);
				tmp[j]%=mod; 
			}
		}
		for(int j=0;j<=n;j++) {
			for(int k=1;k<=n&&k+j+1<=n;k++) {
				ans[y][k+j+1]=(ans[y][k+j+1]+ans[x][k]*tmp[j]%mod*_inv%mod)%mod;
			}
		}
	}
	for(int y:g) dfs(y,x);	
}
signed main(){
//	fil();
	n=read();
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<n;i++) {
		int u=read(),v=read();
		s[u].push_back(v);s[v].push_back(u);
	}
	calcsiz(1,0);
	ans[1][1]=h[1];
	dfs(1,0);
	for(int i=1;i<=n;i++) {
		int sum=0;
		for(int j=1;j<=n;j++) cout<<ans[i][j]<<' ';
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：_tobi_ (赞：3)

### [P9669 [ICPC2022 Jinan R] DFS Order 2](https://www.luogu.com.cn/problem/P9669)
一道计数题目，意思是给你一棵树，问每个节点出现在 DFS 序的每一位的不同 DFS 序的方案数。  
对于一个结点来说，DFS 序在它前面的部分的组成有：
1. 它的祖先；
2. 它祖先的一些兄弟子树；
3. 它的一些兄弟子树。

而后面的部分的组成有：
1. 它祖先的其他兄弟子树；
2. 它的其他兄弟子树；
3. 它的子树。

因为涉及到祖先，因此我们考虑从上到下进行 DP。考虑一个状态是 $dp[x, i]$ 意思是结点 $x$ 排在 DFS 序内第 $i$ 位的方案数。这个状态我们不考虑 $x$ 子树内顺序的不同，理由有三个：
1. 对于 $x$ 来说，在它子树所在的 DFS 序区间内，它永远是第一个，对 $x$ 的计算没有影响；
2. 我们以后还要转移到它的孩子结点，如果算上了我们就很难转移；
3. 最后计算答案的时候我们可以简单地再把它乘进去。

所以我们在这个状态中，只考虑上面六条中的五条。先考虑最简单的一个问题，如果我们计算出了 $dp[x, i]$，最后我们要乘上的子树内方案（记为 $g[x]$）怎么计算。记 $x$ 的儿子集合为 $S$，显然有：
$$g[x] = |S|! \times \prod\limits_{y \in S} g[y]$$

显然初值是 $dp[1, 1] = 1$。我们考虑如果已经计算了父亲 $x$ 的 $dp$ 值，如何转移到儿子 $y$。

我们首先枚举每个儿子分别计算，再枚举 $y$ 在 DFS 序的第 $i$ 位，$x$ 在 DFS 序的第 $j$ 位，那么我们需要让它的一部分兄弟的子树凑齐 $i - j - 1$ 这么多个位置，也就是做个背包。

我们记 $f[k, i]$ 是用 $k$ 个兄弟放在 $y$ 前面，它们的子树总共占了 $i$ 个位置的方案数。如果每个儿子都计算整个背包，那么复杂度是 $O(n^4)$，难以接受。有一个叫回退背包的技巧，我们先把所有 $x$ 的儿子做个背包，这部分是 $O(n^3)$，计算每个儿子的时候再用 $O(n^2)$ 的复杂度给退回去（怎么计算就怎么倒着退回去，这个技巧可以退任意一个物品，但是只适用于方案数类型的背包），总复杂度还是 $O(n^3)$。

那么我们就可以列出转移方程：
$$dp[y, i] = \sum\limits_{j < i} \sum\limits_{k < |S|} dp[x, j] \times f[k, i - j - 1] \times \frac{k! \times (|S| - 1 - k)! \times g[x]}{|S|! \times g[y]}$$

这一大坨是什么意思呢？前两个不用解释，来解释一下后面的分数：因为我们要计算进去它的兄弟、它兄弟子树内的不同排列，所以我们要有分子的式子，而 $g[x]$ 中 $|S|!$ 的部分显然被我们分子上的两个阶乘计算过了，所以要去掉；再根据状态定义，去掉 $y$ 子树内的方案数。  
我们在 DP 的过程中直接计算上面的一大坨，复杂度是 $O(n^4)$（枚举 $y$、$i$、$j$、$k$），主要瓶颈在于 $f[k, i - j - 1]$ 这个同时占了三项的式子，而它的第二维大小显然是 $O(n)$ 的，所以我们考虑预处理一下这个积的后两个部分。我们记如下式子：

$$w_{i} = \sum\limits_{k < |S|} f[k, i] \times \frac{k! \times (|S| - 1 - k)! \times g[x]}{|S|! \times g[y]}$$

对于每个儿子都要重新计算一遍 $w$，总复杂度也是 $O(n^3)$。
然后我们就可以 $O(n^3)$ 进行 DP 了。

顺便说一些实现上的细节，这题用 `vector` 存图可以很方便地获得 $|S|$，我们还需要预处理一个 $siz(x)$，作为背包的第二维的大小。我们预处理 $n$ 以内阶乘和阶乘逆元，计算 $g[x]$，再计算 $g[x]$ 的逆元就可以很方便地 $O(1)$ 算出来转移方程中的分数。

代码：
```cpp
using LL = long long;
istream &in = cin;
ostream &out = cout;
#define newl '\n'

const LL P = 998244353; const int N = 505;
vector<int> edge[N];
LL fac[N], invf[N], siz[N], g[N], invg[N], f[N][N], w[N], dp[N][N];
int n;

void dfs(int x, int fa){
    g[x] = fac[edge[x].size() - (fa != 0)];
    siz[x] = 1;
    for(int y : edge[x]){
        if(y == fa) continue;
        dfs(y, x);
        g[x] = g[x] * g[y] % P;
        siz[x] += siz[y];
    }
}

void solve(int x, int fa){
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    int sonNum = edge[x].size() - (fa != 0);
    for(int y : edge[x]){
        if(y == fa) continue;
        for(int i = sonNum; i; i--){
            for(int j = siz[x] - 1; j >= siz[y]; j--){
                f[i][j] = (f[i][j] + f[i - 1][j - siz[y]]) % P;
            }
        }
    }
    for(int y : edge[x]){
        if(y == fa) continue;
        for(int i = 1; i <= sonNum; i++){
            for(int j = siz[y]; j <= siz[x] - 1; j++){
                f[i][j] = ((f[i][j] - f[i - 1][j - siz[y]]) % P + P) % P;
            }
        }
        memset(w, 0, sizeof w);
        for(int i = 0; i <= siz[x]; i++){
            for(int j = 0; j < sonNum; j++){
                w[i] = (w[i] + f[j][i] * fac[j] % P * fac[(sonNum - 1 - j)] % P * g[x] % P * invf[sonNum] % P * invg[y] % P) % P;
            }
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j < i; j++){
                dp[y][i] = (dp[y][i] + dp[x][j] * w[i - j - 1] % P) % P;
            }
        }
        for(int i = sonNum; i; i--){
            for(int j = siz[x] - 1; j >= siz[y]; j--){
                f[i][j] = (f[i][j] + f[i - 1][j - siz[y]]) % P;
            }
        }
    }
    for(int y : edge[x]){
        if(y == fa) continue;
        solve(y, x);
    }
}

LL qpow(LL x, LL y){
    LL res = 1;  
    for(; y; y >>= 1){
        if(y & 1) res = res * x % P;
        x = x * x % P;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(0), in.tie(0), out.tie(0);
    in >> n;
    for(int i = 1; i < n; i++){
        int u, v;
        in >> u >> v;
        edge[u].push_back(v), edge[v].push_back(u);
    }
    fac[0] = 1;
    for(int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % P;
        invf[i] = qpow(fac[i], P - 2);
    }
    dfs(1, 0);
    for(int i = 1; i <= n; i++) invg[i] = qpow(g[i], P - 2);
    dp[1][1] = 1;
    solve(1, 0);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            out << dp[i][j] * g[i] % P << ' ';
        }
        out << newl;
    }
    return 0;
}
```

---

## 作者：junxis (赞：3)

### Preface
赛时写的，没调出来开摆了，感恩 @Xiaohuba。

### Analysis

我们记 $f(i,j,k)$ 表示 $i$ 的**兄弟**（不包括 $i$）中选了 $j$ 个，$sz$ 之和为 $k$ 的方案数。

从而计算出 $g(i,k)$ 表示 $i$ 的 dfs order 比其父亲大 $k$ 的方案数。

具体地，$g(i,k)=\sum\limits_{j}f(i,j,k-1)$。

接着，记 $ans(i,j)$ 为答案。

有 $ans(i,j) = \sigma(i)\sum\limits_{k<j}ans(p,j-k)\times g(i,k)$。

其中 $\sigma(i)$ 为 $i$ 子树内部排列的方案，$p$ 为 $i$ 的父亲。
　
 
你会发现不对。


因为在这个过程中，你给 $ans$ 乘了 $\sigma$，那么在计算他的儿子的时候儿子的排列已经算在那个 $\sigma$ 里了。

那么我们修改一下，求和号里的每一项除掉一个 $\sigma(i)\times (b - 1)!$。

其中 $b$ 为 $p$ 的孩子个数。

表示把内部排列钦定掉。

然后神奇地发现 $\sigma$ 可以约掉。

边界条件 $ans(1,1)=\sigma(1)$。

做完了？

还没有。

$f$ 如果直接树上背包，是 $O(n^4)$ 的。

我们考虑使用[这题](https://atcoder.jp/contests/abc321/tasks/abc321_f)的 trick，先求出所有儿子的背包，再在计算 $i$ 时撤销掉 $i$ 的贡献，就可以通过本题了。

时间复杂度 $O(n^3)$。

对不起，@Xiaohuba。

---

## 作者：AlicX (赞：2)

### Solution 

**提供一种不用回滚背包的做法。**

定义 $f_{u,j}$ 表示 $u$ 是 `dfs` 序中第 $j$ 个点，除了子树内的情况其他都考虑了的方案数。（~奇怪的定义~）

答案需要把子树内的贡献乘上，即 $ans_{i,j}=f_{i,j} \times g_i$，$g_i= pr_j \times \prod g_j(j \in son_u)$。也就是儿子数量的全排列方案乘上每个儿子的方案数。

考虑转移为：$f_{to,j}=f_{u,k}\times dp_{to,p,k} \times pr_p \times pr_{num-p-1} \times \frac{\prod g_{To}}{g_{to}} $，其中 $dp_{to,p,k}$ 表示在 $u$ 的子树中不选 $to$ 这个子树的情况下选择了 $p$ 个子树，大小为 $k$ 的方案数，然后这个式子显然可以优化到 $O(n^3)$，但是求 $dp_{to,p,k}$ 是 $O(n^4)$ 的。

不同于其他题解的回滚，不妨用一个小 trick 分治。假设当前的区间是 $[l,r]$，把 $[l,mid]$ 的儿子加入答案，继续分治 $[mid+1,r]$ 区间，然后清空数组，重新把 $[mid+1,r]$ 的儿子加入答案，分治 $[mid+1,r]$ 区间。不难想到当 $l=r$ 时，**整个区间只有 $l$ 这个儿子未加入答案了**，这样就完成了对 $dp_{to,p,k}$ 数组的求解。

时间复杂度 $O(n^3 \log n)$。 

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define il inline 
#define em emplace 
#define eb emplace_back 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=502; 
const int mod=998244353; 
int n; 
int g[N]; 
int pr[N]; 
int siz[N]; 
int dpf[N]; 
int f[N][N]; 
int h[N],idx=0; 
vector<int> fg[N][N]; 
int dp[N][N],lst[N][N][10]; 
struct Edge{ 
	int to,ne; 
}e[N<<1]; 
il int qmi(int x,int k){ 
	int res=1; 
	while(k){ 
		if(k&1) res=res*x%mod; 
		x=x*x%mod; k>>=1; 
	} return res; 
} 
il void add(int u,int v){ 
	e[idx].to=v,e[idx].ne=h[u],h[u]=idx++; 
} 
il void dfsp(int u,int fa){ 
	g[u]=siz[u]=1; int num=0; 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(to==fa) continue; 
		dfsp(to,u); siz[u]+=siz[to]; 
		g[u]=g[u]*g[to]%mod; num++; 
	} g[u]=g[u]*pr[num]%mod; 
} 
int a[N]; 
int num=0,sz=0,res; 
il void calc(int l,int r,int dep){ 
	if(l==r){ 
		for(int p=0;p<num;p++){ 
			fg[a[l]][p].resize(sz+1); 
			for(int k=0;k<=sz;k++) fg[a[l]][p][k]=dp[p][k]; 
		} return ; 
	} int mid=l+r>>1; 
	for(int p=0;p<=num;p++) for(int k=0;k<=sz;k++) lst[p][k][dep]=dp[p][k]; 
	for(int i=l;i<=mid;i++){ 
		for(int p=num-1;p>=1;p--){ 
			for(int k=sz;k>=siz[a[i]];k--){ 
				dp[p][k]=(dp[p][k]+dp[p-1][k-siz[a[i]]])%mod; 
			} 
		} 
	} calc(mid+1,r,dep+1); 
	for(int p=0;p<=num;p++) for(int k=0;k<=sz;k++) dp[p][k]=lst[p][k][dep]; 
	for(int i=mid+1;i<=r;i++){ 
		for(int p=num-1;p>=1;p--){ 
			for(int k=sz;k>=siz[a[i]];k--){ 
				dp[p][k]=(dp[p][k]+dp[p-1][k-siz[a[i]]])%mod; 
			} 
		} 
	} calc(l,mid,dep+1); 
} 
il void init(int u,int fa){ 
	num=0,sz=siz[u]; 
	for(int i=h[u];i!=-1;i=e[i].ne) if(e[i].to!=fa) a[++num]=e[i].to; 
	if(!num) return ; 
	for(int p=0;p<num;p++) for(int k=0;k<=sz;k++) dp[p][k]=0; 
	dp[0][0]=lst[0][0][0]=1,calc(1,num,0); 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(to==fa) continue; 
		init(to,u); 
	} 
} 
il void dfs(int u,int fa){ 
	num=0,sz=siz[u],res=1; 
	for(int i=h[u];i!=-1;i=e[i].ne) if(e[i].to!=fa) res=res*g[e[i].to]%mod,num++; 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to,inres=res*qmi(g[to],mod-2)%mod; 
		if(to==fa) continue; 
		memset(dpf,0,sizeof dpf); 
		for(int p=0;p<num;p++){ 
			for(int k=0;k<sz;k++){ 
				dpf[k]=(dpf[k]+fg[to][p][k]*pr[p]%mod*pr[num-p-1]%mod*inres%mod)%mod; 
			} 
		} for(int k=1;k<=n;k++){ 
			for(int j=k+1;j<=n;j++){ 
				f[to][j]=(f[to][j]+f[u][k]*dpf[j-k-1]%mod)%mod; 
			} 
		} 
	} for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(to==fa) continue; 
		dfs(to,u); 
	} 
} 
// f[to][j]=(f[to][j]+f[u][j-k-1]*fg[to][p][k]%mod*pr[p]%mod*pr[num-p-1]%mod*res%mod*inv[to]%mod)%mod; 
signed main(){ 
	memset(h,-1,sizeof h); 
	n=read(); f[1][1]=pr[0]=1;  
	for(int i=1,u,v;i<n;i++) u=read(),v=read(),add(u,v),add(v,u),pr[i]=pr[i-1]*i%mod; 
	dfsp(1,0),init(1,0),dfs(1,0); 
	for(int i=1;i<=n;i++){ 
		for(int j=1;j<=n;j++) printf("%lld ",f[i][j]*g[i]%mod); 
		puts(""); 
	} return 0; 
} 
```

---

## 作者：Chenyanxi0829 (赞：1)

设 $c_i$ 为 $i$ 的儿子个数。

根据 DFS 序的性质，DFS 到每个点 $x$ 的时候都有 $c_x!$ 种遍历儿子子树的顺序，且 $x$ 的儿子的答案可以从 $x$ 的答案转移过来，只需要把 $x$ 在每个位置的答案先除掉 $c_x!$ 再乘上这个儿子排在想要位置的方案数。

考虑 $x$ 对其儿子做一次 dp，设 $dp_{i,j,k}$ 表示前 $i$ 个儿子选了 $j$ 个且子树大小之和为 $k$ 的方案数，转移时直接看第 $i$ 个儿子选不选即可。计算答案时如果这个儿子排在 $x$ 后 $a$ 个位置，那么就需要排在其之前的儿子子树大小之和为 $a-1$，所以需要先做一次退背包，这样就知道了其它儿子中选了 $j$ 个且子树大小之和为 $k$ 的方案数，对于每种方案都有 $j!(c_x-1-j)!$ 种方案排列其它儿子。先统计出这个儿子 $y$ 排在 $x$ 后 $a$ 个位置的方案数 $s_a$，然后对于每个 $b$，$ans_{y,b}$ 加上 $\large{\frac{ans_{x,b-a}}{c_x!}}s_a$。由于所有点的儿子个数之和为 $n$，所以总复杂度为 $O(n^3)$。

## 代码
其他实现细节见代码。
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kMaxN = 550, mod = 998244353;

int n, g[kMaxN][kMaxN], G[kMaxN][kMaxN], a[kMaxN], z[kMaxN];
ll c[kMaxN], dp[kMaxN], ans[kMaxN][kMaxN], Y[kMaxN];
vector<int> e[kMaxN];

ll P(ll a, int b, ll ans = 1) {
  for (int i = 1; i <= b; i <<= 1, a = a * a % mod) {
    (i & b) && (ans = ans * a % mod);
  }
  return ans;
}

void dfs(int x, int f) {
  dp[x] = a[x] = 1;
  int s = 0;
  for (int i : e[x]) {
    if (i != f) {
      dfs(i, x), dp[x] = dp[x] * dp[i] % mod, a[x] += a[i];
    }
  }
  dp[x] = dp[x] * c[int(e[x].size()) - (f > 0)] % mod;
}

void DFS(int x, int f) {
  g[0][0] = 1;
  int t = 0, sum = 0;
  for (int i : e[x]) {
    if (i != f) {
      for (int j = t + 1; j; j--) {
        for (int k = sum + a[i]; k >= a[i]; k--) {
          g[j][k] = (g[j][k] + g[j - 1][k - a[i]]) % mod;
        }
      }
      t++, sum += a[i];
    }
  }
  for (int i : e[x]) {
    if (i != f) {
      for (int j = 0; j <= t; j++) {
        for (int k = 0; k <= sum; k++) {
          G[j][k] = g[j][k], z[k] = 0;
        }
      }
      for (int j = 1; j <= t; j++) {
        for (int k = a[i]; k <= sum; k++) {
          G[j][k] = (G[j][k] + mod - G[j - 1][k - a[i]]) % mod;
        }
      }
      for (int j = 0; j < t; j++) {
        for (int k = 0; k <= sum - a[i]; k++) {
          z[k] = (z[k] + c[j] * c[t - 1 - j] % mod * G[j][k]) % mod;
        }
      }
      for (int k = 0; k <= sum - a[i]; k++) {
        for (int j = 1 + k + 1; j <= n; j++) {
          ans[i][j] = (ans[i][j] + ans[x][j - 1 - k] * Y[int(e[x].size()) - (f > 0)] % mod * z[k]) % mod;
        }
      }
    }
  }
  for (int j = 0; j <= t; j++) {
    for (int k = 0; k <= sum; k++) {
      g[j][k] = 0;
    }
  }
  for (int i : e[x]) {
    if (i != f) {
      DFS(i, x);
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y, e[x].push_back(y), e[y].push_back(x);
  }
  c[0] = 1, Y[0] = 1;
  for (int i = 1; i <= n; i++) {
    c[i] = c[i - 1] * i % mod, Y[i] = P(c[i], mod - 2);
  }
  dfs(1, 0), ans[1][1] = dp[1], DFS(1, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << ans[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
```

---

