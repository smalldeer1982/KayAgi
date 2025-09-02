# Diameter Cuts

## 题目描述

You are given an integer $ k $ and an undirected tree, consisting of $ n $ vertices.

The length of a simple path (a path in which each vertex appears at most once) between some pair of vertices is the number of edges in this path. A diameter of a tree is the maximum length of a simple path between all pairs of vertices of this tree.

You are about to remove a set of edges from the tree. The tree splits into multiple smaller trees when the edges are removed. The set of edges is valid if all the resulting trees have diameter less than or equal to $ k $ .

Two sets of edges are different if there is an edge such that it appears in only one of the sets.

Count the number of valid sets of edges modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example the diameter of the given tree is already less than or equal to $ k $ . Thus, you can choose any set of edges to remove and the resulting trees will have diameter less than or equal to $ k $ . There are $ 2^3 $ sets, including the empty one.

In the second example you have to remove the only edge. Otherwise, the diameter will be $ 1 $ , which is greater than $ 0 $ .

Here are the trees for the third and the fourth examples:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1499F/79b28352721e574665f54dbdbe68df4e7a2b22d3.png)

## 样例 #1

### 输入

```
4 3
1 2
1 3
1 4```

### 输出

```
8```

## 样例 #2

### 输入

```
2 0
1 2```

### 输出

```
1```

## 样例 #3

### 输入

```
6 2
1 6
2 4
2 6
3 6
5 6```

### 输出

```
25```

## 样例 #4

### 输入

```
6 3
1 2
1 5
2 3
3 4
5 6```

### 输出

```
29```

# 题解

## 作者：wz20201136 (赞：6)

### 题意

给定一个 $n$ 的节点的树和一个值 $k$，求删去若干条边使得剩下的每个连通块的直径大小均 $\leq k$ 的方案数。

### 题解

考虑动态规划：

$dp_{u,i}$ 表示以 $u$ 为根，$u$ 所在连通块深度为 $i$ 的方案数。

转移时，枚举子树 $v$，分三种情况讨论：

- 删去边 $(u,v)$，则 $dp_{u,i}=dp_{u,i}\times\sum_{j=0}^{k}{dp_{v,j}}$。
- 保留边 $(u,v)$，且 $u$ 所在连通块最深的节点不在 $v$ 的子树内。则 $dp_{u,i}=dp_{u,i}\times\sum_{j=0}^{\min(k-i-1,i-1)}{dp_{v,j}}$。
- 保留边 $(u,v)$，且 $u$ 所在连通块最深的节点在 $v$ 的子树内。则 $dp_{u,i}=dp_{v,i-1}\times\sum_{j=0}^{\min(k-i,i-1)}{dp_{u,j}}$。

三种情况分别前缀和优化即可，时间复杂度 $O(n^2)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5005,mod=998244353;
int dp[MAXN][MAXN],n,k,x,y,sum[MAXN],f[MAXN];
vector<int> E[MAXN];
void dfs(int u,int fa)
{
	dp[u][0]=1;
	for(int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if(v==fa) continue;
		dfs(v,u);
		memset(sum,0,sizeof(sum));
		memset(f,0,sizeof(f));
		for(int j=0;j<=k;j++)
			f[j]=dp[u][j]*dp[v][k+1]%mod;
		sum[0]=dp[v][0];
		for(int j=1;j<=k;j++)
			sum[j]=(sum[j-1]+dp[v][j])%mod;
		for(int j=0;j<k;j++)
			f[j]=(f[j]+dp[u][j]*sum[min(j-1,k-j-1)])%mod;
		sum[0]=dp[u][0];
		for(int j=1;j<=k;j++)
			sum[j]=(sum[j-1]+dp[u][j])%mod;
		for(int j=1;j<=k;j++)
			f[j]=(f[j]+dp[v][j-1]*sum[min(k-j,j-1)])%mod;
		for(int j=0;j<=k;j++) dp[u][j]=f[j];
	}
	for(int i=0;i<=k;i++) dp[u][k+1]=(dp[u][k+1]+dp[u][i])%mod;
}
signed main()
{
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		cin>>x>>y;
		E[x].push_back(y),E[y].push_back(x);
	}
	dfs(1,0);
	cout<<dp[1][k+1];
	return 0;
}
```

---

## 作者：jifbt (赞：3)

提供一个比较笨的 DP 方法。

记 $f_{u,i}$ 表示从 $u$ 的父亲走到 $u$ 再一直向下走，途中只能走未被割的边，所形成的最长路径的边数，称为 $u$ 的深度。（$u$ 到父亲的边被割掉时，不能形成路径，故 $i=0$。)

我们来处理 $f_{u,i+1}$ 的转移。考虑把子结点排成一列，其中深度最大的结点为 $v$（有多个则选最右边的），则左边的结点深度 $\le i$，右边的 $<i$。由题意得其余结点的深度不超过 $m-i$。记 $p(v)$ 为子结点 $v$ 排成一列的编号，则转移方程为
$$\begin{aligned}
f_{u,i+1}&=\sum_{v\in son(u)}\prod_{v'\in son(u),v'\ne v}\sum_{i'=1}^{\min(i-[p(v')<p(v)],m-i)}f_{v,i'},\\
f_{u,0}&=\sum_{i=0}^{m}f_{u,i+1}.
\end{aligned}$$

接下来考虑优化。首先可以对 $i$ 求前缀和，优化最后一个求和号。
$$s_{u,i}=\sum_{i'=0}^{i}f_{u,i}.$$

然后把子节点的 $s$ 做前后缀积，优化掉求积号。
$$\begin{aligned}
pre_{v,i}=\prod_{v'\in son(u),p(v')<v}s_{v',i},\\
suf_{v,i}=\prod_{v'\in son(u),p(v')>v}s_{v',i}.
\end{aligned}$$

最后的转移方程为
$$
f_{u,i+1}=\sum_{v\in son(u)}pre_{v,\min(i,m-i)}\cdot suf_{v,\min(i-1,m-i)}.
$$

需要特判叶子。

以 $1$ 为根进行 dfs，答案为 $f_{1,0}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> void rd(T &x) {
    x = 0;
    int f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - 48;
        c = getchar();
    }
    x *= f;
}
template <typename T, typename... T2> void rd(T &x, T2 &...y) {
    rd(x), rd(y...);
}

typedef long long ll;
const int mod = 998244353;

const int N = 5010, M = N;
int n, m;
vector<int> e[N];

int f[N][M], sum[N][M], pre[M];

void dfs(int u, int fa) {
    if (e[u].size() == !!fa) {
        f[u][0] = sum[u][0] = f[u][1] = 1;
        fill(sum[u] + 1, sum[u] + m + 2, 2);
        return;
    }
    for (int v : e[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
    for (int t = 0; t <= 1; ++t) {
        fill(pre, pre + m + 1, 1);
        bool fl = false;
        for (int v : e[u]) {
            if (v == fa) continue;
            if (t && fl) f[v][0] = 0;
            for (int i = t; i <= m; ++i) {
                f[v][i] = f[v][i] * (ll)pre[min(i - t, m - i)] % mod;
            }
            for (int i = 0; i <= m; ++i)
                pre[i] = pre[i] * (ll)sum[v][i] % mod;
            fl = true;
        }
        reverse(e[u].begin(), e[u].end());
    }
    for (int i = 0; i <= m; ++i) {
        for (int v : e[u]) {
            if (v == fa) continue;
            (f[u][i + 1] += f[v][i]) %= mod;
        }
        (f[u][0] += f[u][i + 1]) %= mod;
    }
    sum[u][0] = f[u][0];
    for (int i = 0; i <= m; ++i) {
        (sum[u][i + 1] = sum[u][i] + f[u][i + 1]) %= mod;
    }
}

int main() {
    rd(n, m);
    for (int i = 1; i < n; ++i) {
        int u, v;
        rd(u, v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);
    printf("%d", sum[1][0]);
}
```

---

## 作者：E1_de5truct0r (赞：3)

小清新树形 dp。

## 思路

我一开始想的是求出所有超过 $k$ 的链，在链上做文章。但是发现不太好做就弃掉了。

后来发现，一个点 $i$ 的子树内，可以分成它的儿子中处理长度 $\geq k$ 的链的情况，以及跨过 $u$ 这个点的情况。那么就可以递归的进行求解。

考虑更新 $u$ 的答案，需要哪些 $v$ 的值。显然，我们要记录从 $u$ 往下的两条链，用这个链更新答案。因此想到了 $dp$ 状态：

$dp_{i,j}$ 表示从 $i$ 开始，向下长度为 $j$ 的链的方案数。

我们每次枚举它的儿子 $v$，以及从 $v$ 向下的长度更新答案。假设我们有一个 $dp$ 值就是 $dp_{v,k}$，则我们对于 $dp_{u,j}$ 有两种决策：

1. $u \rightarrow v$ 这条边断开，则 $dp_{u,j} = dp_{u,j}+dp_{u,j} \times dp_{v,k}$。但是观察到，这个更新会影响到当前的 $dp$，这个是错误的，所以我们要用单独的数组记录，即 $tmp_{j}=tmp_{j}+dp_{u,j} \times dp_{u,k}$，最后再把 $tmp_j \rightarrow dp_{u,j}$。

2. 这条边不断开，则需要满足 $j+k+1 \leq k$。那么转移为：$tmp_{\max(i,j+1)}=tmp_{\max(i,j+1)}+dp_{u,j} \times dp_{v,k}$。

因此我们对于每一个 $u,v$ 枚举 $j,k$ 进行转移即可。

初始值也比较显然，$dp_{u,0}=1$。

## 代码

```cpp
#include <iostream>
#include <vector>
#define ios ios::sync_with_stdio
using namespace std;
const int mod=998244353,MAXN=5005;
inline int Mod(const int &x){return x>=mod?x-mod:x;}
inline int qmax(const int &x,const int &y){
	return x>y?x:y;
}

int n,K;
vector<int> E[MAXN];
int dep[MAXN],mxd[MAXN];
int dp[MAXN][MAXN],tmp[MAXN];
void dfs(int u,int fa){
	dep[u]=mxd[u]=dep[fa]+1;
	dp[u][0]=1;
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa) continue;
		dfs(v,u);
		int N=mxd[u]-dep[u],M=mxd[v]-dep[u];
		for(int j=0;j<=max(N,M);j++) tmp[j]=0;
		for(int j=0;j<=N;j++){
			for(int k=0;k<=M;k++){
//				cout<<K<<endl;
				tmp[j]=Mod(tmp[j]+1ll*dp[u][j]*dp[v][k]%mod);
				if(j+k+1<=K) tmp[qmax(j,k+1)]=Mod(tmp[qmax(j,k+1)]+1ll*dp[u][j]*dp[v][k]%mod);
			}
		}
		mxd[u]=qmax(mxd[u],mxd[v]);
		for(int j=0;j<=max(N,M);j++) dp[u][j]=tmp[j];
//		for(int j=0;j<=K;j++) cout<<dp[u][j]<<" ";
//		cout<<endl<<"------------------\n";
	}
//	cout<<u<<endl;
//	for(int j=0;j<=K;j++) cout<<dp[u][j]<<" ";
//	cout<<endl<<"------------------\n";
}
void solve(){
	cin>>n>>K;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<=K;j++)
			dp[i][j]=(j==0);
	int ans=0; dfs(1,0);
	for(int i=0;i<=K;i++) ans=Mod(ans+dp[1][i]);
	cout<<ans<<endl;
}
int main(){
	ios(0);
	solve();
	return 0;
}
```

---

## 作者：lory1608 (赞：3)

## CF1499F题解

这场EDU的F怎么这么简单啊。

由于直径这个东西可以DP，我们整个计数过程也可以考虑DP，设 $dp_{u,i}$ 表示在 $u$ 的子树内选择的一条最长的直达 $u$ 的链的长度为 $i$ 的方案数，转移如下：

- $dp_{u,i}=dp_{u,i}\times \sum\limits_{j\leq k} dp_{v,j}$ 表示割掉这条边。
- $dp_{u,max(i,j+1)}=dp_{u,i}\times dp_{v,j}(i+j+1\leq k)$ 表示不割掉这条边，并且长度要合法。

然后每次只循环到子树大小就可以 $O(n^2)$ 做了。

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define PII pair<int,int>
#define ll long long
#define pb push_back
#define PLL pair<ll,ll>
#define fi first
#define se second
#define sz(x) (int)(x.size())
#define rd (rand()<<16^rand())
#define db double
#define gc (_p1==_p2&&(_p2=(_p1=_buf)+fread(_buf,1,100000,stdin),_p1==_p2)?EOF:*_p1++)
using namespace std;
char _buf[100000],*_p1=_buf,*_p2=_buf;
inline int gi()
{
	int x=0,f=1;
	char ch=gc;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=gc;
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=gc;
	}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=5005,mod=998244353;
int dp[maxn][maxn];
vector<int>e[maxn];
int n,k,siz[maxn],dep[maxn],tmp[maxn],maxdep[maxn];
inline void init()
{

}
inline void input()
{
	n=gi(),k=gi();
	FOR(i,1,n-1)
	{
		int u=gi(),v=gi();
		e[u].pb(v),e[v].pb(u);	
	}
}
inline void dfs(int u,int fa)
{
	siz[u]=1;maxdep[u]=dep[u];
	dp[u][0]=1;
	for(auto v:e[u])
	{
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
		int kk=maxdep[u]-dep[u];
		FOR(i,0,max(maxdep[u],maxdep[v])-dep[u])tmp[i]=0;
		FOR(i,0,kk)
		{
			FOR(j,0,maxdep[v]-dep[u])
			{
				tmp[i]=(tmp[i]+1ll*dp[u][i]*dp[v][j]%mod)%mod;
				if(i+j+1>k)continue;
				tmp[max(i,j+1)]=(tmp[max(i,j+1)]+1ll*dp[u][i]*dp[v][j]%mod)%mod;
			}
		}
		maxdep[u]=max(maxdep[u],maxdep[v]);
		FOR(i,0,maxdep[u]-dep[u])dp[u][i]=tmp[i];
		siz[u]+=siz[v];
	}
}
inline void solve()
{
	dfs(1,0);
	int ans=0;
	FOR(i,0,k)ans=(ans+dp[1][i])%mod;
	printf("%d\n",ans);
}
int main()
{
	int T=1;
	while(T--)
	{
		init();
		input();
		solve();
	}
	return 0;
}
/*
3 1
1 2
2 3
3 4
*/
```



---

## 作者：一只绝帆 (赞：1)

限制竟然可以不用放在状态里！

我觉得这道题最难理解的地方是状态设计，一不小心就想把直径设进状态里，但那没法转移。

然后想用两条链拼成那个状态，但转念一想 $x$ 向下的最长链并不一定是所在子树的最长链，万一这个子树的最长链已经超过 $k$ 了呢？

遂看题解。

------------

（以上废话，不用管，以下原题中的 $k$ 用 $K$ 表示。）

限制不一定要把值显式设出来，也可以放进转移中处理（即当作状态的“条件”）。

设 $f_{x,j}$ 表示 $x$ 所在连通块与 $x$ 相连的最长路径长度为 $j$，**且此时合法**的方案数。

转移的时候，将子树合并进来，注意要关注合法这个条件。

原来合法，现在不合法的充要条件是你新加了一条边，这条边将原来的最长路径增长到了 $K$，而只有原来从根往下的路径会受上方是否断边的影响。

这是断边，不会导致任何不合法：

$$f'_{x,j}\gets \sum_{fa_v=x} \sum_{k\le K}f_{x,j}f_{v,k}$$

这是不断边，需要保证这一时刻形成的（可能的）最长路径，也就是在 $x$ 处拼起来的这条路径的长度 $\le K$：

$$\begin{aligned}f'_{x,j}&\gets \sum_{fa_v=x} \sum_{k+1\le j}f_{x,j}f_{v,k}[j+k+1\le K]\\f'_{x,k+1}&\gets\sum_{fa_v=x}\sum_{k+1>j}f_{x,j}f_{v,k}[j+k+1\le K] \end{aligned}$$

初始 $f_{x,1}=1$。

接下来优化。

长链剖分优化的 dp 通常是有一维状态是高度，且一般父亲可以从儿子继承（可能是子树合并的第一次合并）或只做很小的改动。

注意这个高度维必须转移枚举的是自己子树的最大高度，而不是 $n$，否则无法优化。

每次合并的时候先直接继承长儿子的数组（用指针向前移一位），然后将短儿子暴力合并，合并时枚举到短儿子高度。

（注意这并不是树上启发式合并那种的暴力递归下去，我们仍然只遍历儿子。）

时间复杂度 $O(nm^2)\to O(nm)$，证明就是每条长链只会在链顶处被枚举一遍该长链的深度，还要同时枚举 $x$ 的深度，所以是 $O(n)\times O(m)=O(nm)$。

注意写法，要给每条长链分配一块数组，其中每个点都有自己的指针数组。

若每个点的数组大小是严格小于 $d_x$ 的，那么按照 `dfn` 序分配即可，否则如果是 $d_x+O(1)$ 之类的那就需要精细实现。

注意枚举时下标 $[0,h_x-1]$，多了会越界，可以在指针上 $-1$ 来实现下标变换，当然本题的直径是边数不是点数，所以仍然从 $0$ 开始。

放到本题来看我们发现不断边的转移可以保留长儿子数组不变，断边转移把第一个位置修改为儿子数组 $[0,K]$ 这些位置的和，所以要多开一个前缀和数组。

Code：
```cpp
// Problem: CF1499F Diameter Cuts
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1499F
// Memory Limit: 250 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
#define G(i,x) for(int i(start[x]);i;i=Next[i])
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define f(i,a,b) for(int i=a;i<b;i++)
using namespace std;typedef long long ll;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<21];
int read() {
	int s=0,w=0;char ch=gc();
	while(ch<'0'||ch>'9') w|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=gc();
	return w?-s:s;
} const int N=5e3+5,M=N<<1,p=998244353;
int n,K,v[M],Next[M],start[N],cnt;
int dep[N],h[N],fa[N],son[N],tot,dfn[N],dfx[N];
ll *f[N],_f[N],*sum[N],_sum[N],ans,tmp[N];
void add(int x,int y) {v[++cnt]=y;Next[cnt]=start[x];start[x]=cnt;}
void Add(int x,int y) {add(x,y);add(y,x);}
void d(int x) {
	dep[x]=dep[fa[x]]+1;h[x]=1;
	G(i,x) if(v[i]^fa[x]) {
		fa[v[i]]=x;d(v[i]);
		h[x]=max(h[x],h[v[i]]+1);
		h[v[i]]>h[son[x]]&&(son[x]=v[i]);
	}
}
void d2(int x) {
	dfx[dfn[x]=++tot]=x;f[x]=_f+dfn[x];sum[x]=_sum+dfn[x];
	if(son[x]) d2(son[x]);
	G(i,x) if(v[i]^fa[x]&&v[i]^son[x]) d2(v[i]);
}
void dp(int x) {
	G(i,x) if(v[i]^fa[x]) dp(v[i]);
	if(!son[x]) f[x][0]=1;
	else if(h[son[x]]-1>=K) f[x][0]=sum[son[x]][K];
	else f[x][0]=sum[son[x]][h[son[x]]-1];
	G(i,x) if(v[i]^fa[x]&&v[i]^son[x]) {
		f(j,0,h[x]) f(k,0,h[v[i]]) if(j+k+1<=K) 
			tmp[max(j,k+1)]=(tmp[max(j,k+1)]+f[x][j]*f[v[i]][k]%p)%p;
		f(j,0,h[x]) f(k,0,h[v[i]]) if(j<=K&&k<=K) 
			tmp[j]=(tmp[j]+f[x][j]*f[v[i]][k]%p)%p;
		f(j,0,h[x]) f[x][j]=tmp[j],tmp[j]=0;
	} sum[x][0]=f[x][0];f(j,1,h[x]) sum[x][j]=(sum[x][j-1]+f[x][j])%p;
}
int main() {
	n=read();K=read();
	F(i,2,n) Add(read(),read());
	d(1);d2(1);dp(1);F(i,0,min(h[1]-1,K)) ans=(ans+f[1][i])%p;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Felix72 (赞：1)

设置二维状态，表示当前节点和从该节点出发的最长路径。

考虑用类似树上背包的东西做。每次用子树更新：如果当前路径保留，那么判断合法性之后直接乘即可，具体判断方法是看当前最长路径加上子树的最长路径是否大于限制（也就是算直径）；如果不保留，那么子树的状态完全无影响，于是乘上总合法方案数。

直接在原数组上弄是不行的，因为每个子树贡献只有一次机会。我们可以像背包一样倒着来，或者另外开一个数组专门算新贡献。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5010, mod = 998244353;
long long n, k, h[N], cnt, cal[N], add[N], ans, sig[N], js;
long long f[N][N];
struct edge {int to, next;} e[N * 2];
inline void Add(int x, int y)
{e[++cnt].to = y, e[cnt].next = h[x], h[x] = cnt;}
inline void treedp(int now, int prt)
{
	f[now][0] = 1;
	cal[now] = 0;
	for(int i = h[now]; i; i = e[i].next)
	{
		int to = e[i].to;
		if(to == prt) continue;
		treedp(to, now);
		memset(add, 0, sizeof(add));
		//add是计算当前贡献的数组，避免一个子树多次贡献 
		for(int j = 0; j <= min(cal[now], k); ++j)
			add[j] = (add[j] + f[now][j] * sig[to] - f[now][j]) % mod;
		//删除的话直接乘子树状态数 
		for(int j = 0; j <= cal[now]; ++j)
		{
			if(j > k) break;
			for(int l = 0; l <= cal[to]; ++l)
			{
				if(j + l >= k) break; //保留则先判断合法 
				add[max(j, l + 1)] = (add[max(j, l + 1)] + f[now][j] * f[to][l]) % mod;
			}
		}
		cal[now] = max(cal[now], cal[to] + 1);
		for(int j = 0; j <= cal[now]; ++j)
			f[now][j] = (f[now][j] + add[j]) % mod; //更新贡献 
	}
	for(int i = 0; i <= min(cal[now], k); ++i)
		sig[now] += f[now][i], sig[now] %= mod; //记录当前子树总合法方案数 
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		Add(x, y), Add(y, x);
	}
	treedp(1, 0);
	for(int i = 0; i <= k; ++i) ans = (ans + f[1][i]) % mod;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：1)

~~难题一道！~~


------------
首先声明，本人实力有限，部分思路参考[大佬题解](https://blog.csdn.net/weixin_45755679/article/details/115435402)。

------------
看到这道题，我们注意到，题目要求的是能删掉 $k$ 条边的集合，使得任何一个子树的直径小于等于 $k$，所以我们**设计状态**：设 $dp[i][j]$ 表示以 $u$ 为根的子树，并且从 $j$ 开始的最长链为 $u$ 的方案数。在 dfs 的过程中，求出每个子树的最长链。然后，我们接着就要推状态转移方程了，由于我们知道**树形 dp 的特点是节点从深到浅（子树从小到大）的顺序作为 DP 的阶段**，所以，我们设 $num$ 数组为临时存放数组。但为什么要设置 $num$ 呢？因为每次都是新加了一个子树对 $dp$ 数组进行更新，即要用当前 $dp$ 数组**重新更新自己**，但是这样会导致可能用了更新过的 $dp$ 数组**再更新自己**，这样明显会出错，并且**我们可能需要用当前的，但是却被更新过了，这样就不好维护**，所以我们要重新开一个数组临时存一下。

接着就是推状态转移方程：

设当前的主链链长 $j$ 和子树的链长 $z$。

那么 $num[\max(j, z + 1)]  = num[\max(j, z + 1)] + dp[u][j] \times dp[v][z]$（这是因为子树 $v$ 与 $u$ 连接，转移的时候要判断 $j + z + 1 \le k$ ~~借鉴大佬原话~~）。

同时，如果子树不与 $u$ 相接，那么就不用进行判断，直接将值转移过来即可：$num[j] = dp[u][j] \times dp[v][z]$。

最终，存储答案：$dp[u][j] = num[j]$。

------------
## 警钟敲烂：
注意，这道题输入的是一棵树，所以在建边时**要建双向边**！！！

注意，这道题的直径可以小于**等于** $k$，所以在统计答案时循环**要从** $0$ **开始**！！！


------------
## 详细代码如下：

```c++

#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int mod = 998244353;
const int MAXN = 5e3 + 5;
const int inf = 0x3f3f3f3f;
struct node
{
    int to;
    int next;
} e[MAXN << 1];
int head[MAXN];
int dp[MAXN][MAXN];
int sum[MAXN];
int cnt;
int n, k;
void add(int u, int v)
{
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt++;
}
int dfs(int u, int f)
{
    int max_edge = 0;
    dp[u][0] = 1;
    for (int i = head[u]; i != -1; i = e[i].next)
    {
        int v = e[i].to;
        if (v == f)
        {
            continue;
        }
        int son = dfs(v, u);
        memset(sum, 0, sizeof(sum));
        for (int j = 0; j <= min(k, max_edge); j++)
        {
            for (int r = 0; r <= min(k, son); r++)
            {
                if (j + r + 1 <= k)
                {
                    sum[max(j, r + 1)] = (sum[max(j, r + 1)] + dp[u][j] * dp[v][r] % mod) % mod;
                }
                sum[j] = (sum[j] + dp[u][j] * dp[v][r] % mod) % mod;
            }
        }
        max_edge = max(max_edge, son + 1);
        for (int j = 0; j <= min(k, max_edge); j++)
        {
            dp[u][j] = sum[j];
        }
    }
    return max_edge;
}
signed main()
{
    memset(head, -1, sizeof(head));//这地方一定要根据你定义的head用法来初始化，别想我一开始傻傻的不初始化！！！
    n = read();
    k = read();
    for (int i = 1; i < n; i++)
    {
        int u, v;
        u = read();
        v = read();
        add(u, v);
        add(v, u);//记住，一定要建双向边，因为是树边
    }
    dfs(1, -1);
    int ans = 0;
    for (int i = 0; i <= k; i++)//这地方要从0开始，因为题目要求直径可以小于等于k，可以等于。
    {
        //cout << "dp[" << 1 << "][" << i << "]=" << dp[1][i] << endl;
        ans = (ans + dp[1][i]) % mod;
    }
    cout << ans;
    return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/120892823)

---

## 作者：happybob (赞：0)

简单题，不需要使用长链剖分。

考虑 $f_{u,i}$ 表示以 $u$ 为根的子树，一端点是 $u$ 时最长路径边数为 $i$ 的答案。

转移的时候类似树形背包，考虑之前的贡献 $x$，新的子树贡献 $y$，分两种情况，分别是断开子树或者不断开。对于断开，容易计算。不断开时需要满足 $x+y+1 \leq k$，贡献给 $dp_{u,\max\{x,y+1\}}$。注意树形背包的写法一定要按照子树大小做，否则复杂度会退化。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int N = 5005;
using ll = long long;
const ll MOD = 998244353;

int n, k;
vector<int> G[N];
int md[N];
ll f[N][N], g[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	auto dfs = [&](auto self, int u, int fa)->void
		{
			f[u][0] = 1ll;
			vector<pair<int, int>> vec;
			for (auto& j : G[u])
			{
				if (j != fa)
				{
					self(self, j, u);
					vec.emplace_back(make_pair(md[j], j));
				}
			}
			for (auto& [d, j] : vec)
			{
				for (int x = 0; x <= min(k, max(md[u], md[j] + 1)); x++) g[x] = 0;
				// 不删子树
				for (int x = 0; x <= md[j] && k - x > 0; x++) // 子树贡献 x
				{
					for (int y = 0; y < min(k - x, md[u] + 1); y++) // 之前贡献不超过k-x（x+y+1<=k)
					{
						int np = max(x + 1, y);
						g[np] = (g[np] + f[u][y] * f[j][x] % MOD) % MOD;
					}
				}
				ll s = 0ll;
				for (int x = 0; x <= min(md[j], k); x++) s = (s + f[j][x]) % MOD;
				md[u] = max(md[u], md[j] + 1);
				for (int x = 0; x <= min(k, md[u]); x++)
				{
					f[u][x] = (g[x] + f[u][x] * s % MOD) % MOD;
				}
			}
		};
	dfs(dfs, 1, 0);
	ll ans = 0ll;
	for (int i = 0; i <= k; i++) ans = (ans + f[1][i]) % MOD;
	cout << ans << "\n";
	return 0;
}
```

---

