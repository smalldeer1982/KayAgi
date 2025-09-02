# Mex Tree

## 题目描述

You are given a tree with $ n $ nodes. For each node, you either color it in $ 0 $ or $ 1 $ .

The value of a path $ (u,v) $ is equal to the MEX $ ^\dagger $ of the colors of the nodes from the shortest path between $ u $ and $ v $ .

The value of a coloring is equal to the sum of values of all paths $ (u,v) $ such that $ 1 \leq u \leq v \leq n $ .

What is the maximum possible value of any coloring of the tree?

 $ ^{\dagger} $ The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ , and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first sample, we will color vertex $ 2 $ in $ 1 $ and vertices $ 1,3 $ in $ 0 $ . After this, we consider all paths:

- $ (1,1) $ with value $ 1 $
- $ (1,2) $ with value $ 2 $
- $ (1,3) $ with value $ 2 $
- $ (2,2) $ with value $ 0 $
- $ (2,3) $ with value $ 2 $
- $ (3,3) $ with value $ 1 $

We notice the sum of values is $ 8 $ which is the maximum possible.

## 样例 #1

### 输入

```
4
3
1 2
2 3
4
1 2
1 3
1 4
10
1 2
1 3
3 4
3 5
1 6
5 7
2 8
6 9
6 10
1```

### 输出

```
8
15
96
1```

# 题解

## 作者：honglan0301 (赞：20)

## 题目分析

首先注意到 $\text{mex}$ 只有三种情况，于是我们先想到贪心的思路，即让 $\text{mex}=2$ 的情况尽可能多，这显然可以通过交替染色的方式实现，做到 $n(n+1)-n-\sum [p_i=1]$。

但是这样贪并不总是最优的，比如造一个在一条边两段挂分别挂很多条边的树，此时最优解是把中间两个点都染成 $1$，其余点染成 $0$。

然后可以换个角度从反面想，发现当且仅当一条路径只经过一种颜色的点时其 $\text{mex}$ 才不为 $2$，这启发我们对于每种颜色的连通块分别考虑。初始情况 $ans=n(n+1)$，每个大小为 $i$、颜色为 $j\in \{0,1\}$ 的连通块会让答案减小 $\frac{i(i+1)(j+1)}{2}$。

那么考虑 $\text{dp}$，注意到每个连通块的大小不会太大（交替染色使得答案只减小至多 $2n$，而一个大小为 $i$ 的连通块会让答案减小 $O(i^2)$，故 $i<O(\sqrt n)$），于是设 $f_{i,j,k}$ 表示点 $i$ 的子树中，$i$ 所在的连通块大小为 $j$，颜色为 $k$ 时答案最小要减少多少。合并子树时有显然的转移：

$$\left \{
\begin{aligned}
& f_{u,i,0}=\min (f_{u,i,0}+\min_{j}\{f_{v,j,1}\},\min_{j}\{f_{u,j,0}+f_{v,i-j,0}+i^2-ij\})\\
& f_{u,i,1}=\min (f_{u,i,1}+\min_{j}\{f_{v,j,0}\},\min_{j}\{f_{u,j,1}+f_{v,i-j,1}+2(i^2-ij)\})\\
\end{aligned}
\right.
$$

于是做完了，下面补充一些应该是前置知识的东西。考虑时间复杂度，如上的树上背包根据 $size$ 合并是 $O(\max u\times \max i)=O(n\sqrt n)$ 的。证明可考虑以下几种情况： 

1. 当 $size_u>\sqrt n,size_v>\sqrt n$ 时：这样的合并至多进行 $O(\frac{n}{\sqrt n})=O(\sqrt n)$ 次，故时间复杂度 $O(n\sqrt n)$。

2. 当 $size_u<\sqrt n,size_v<\sqrt n$ 时：这等价于在每个 $size<\sqrt n$ 的子树上做无限制的背包，容易发现找出每个 $size<\sqrt n$ 的极大子树后时间复杂度就是 $O(\sum size^2)\leq O(\max size\times \sum size)=O(n\sqrt n)$。

3. 当 $size_u<\sqrt n,size_v>\sqrt n$ 时：注意到每个点至多有一个祖先 $u$ 会进行这样的合并，且每个点 $u$ 至多进行一次，故时间复杂度 $O(\sum size_u\times \sqrt n)=O(n\sqrt n)$。

4. 当 $size_u>\sqrt n,size_v<\sqrt n$ 时：注意到每个点至多有一个祖先 $v$ 会进行这样的合并，且每个 $v$ 本来就只会合并一次，故时间复杂度 $O(\sum size_v\times \sqrt n)=O(n\sqrt n)$。

再考虑空间复杂度，直接开满显然是 $O(n\sqrt n)$ 的，会寄掉，于是考虑动态地开（且用完就清空释放内存），此时合并到 $i$ 时只需保存从根到 $i$ 的 $\text{dp}$ 数组，并且背包大小取决于链外的节点个数（因为这条链上的 $size$ 还没有上传），故空间 $O(n)$，可以通过本题。

感觉还不错，启发性在于对 $\text{mex}$ 的贪心转化和优化 $\text{dp}$ 的过程。

## 代码

```cpp
/*
  author: PEKKA_l  
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define pb push_back
#define B 785ll
#define INF 100000000000
#define int long long

int t,n,u,v,sz[200005],g[2][805];
vector <int> e[200005],dp[200005][2];

void dfs(int x,int fat)
{
	sz[x]=1; dp[x][0].pb(INF); dp[x][1].pb(INF); dp[x][0].pb(1); dp[x][1].pb(2);
	for(auto i:e[x])
	{
		if(i==fat) continue; dfs(i,x);
		int min0=INF,min1=INF;
		for(int j=1;j<=min(B,sz[i]);j++) min0=min(min0,dp[i][0][j]),min1=min(min1,dp[i][1][j]);
		for(int j=1;j<=min(B,sz[x]);j++) g[0][j]=dp[x][0][j],g[1][j]=dp[x][1][j],dp[x][0][j]=dp[x][1][j]=INF;
		for(int j=min(B,sz[x])+1;j<=min(B,sz[x]+sz[i]);j++) dp[x][0].pb(INF),dp[x][1].pb(INF);
		for(int j=1;j<=min(B,sz[x]+sz[i]);j++)
		{
			for(int k=max(1ll,j-min(B,sz[x]));k<=min(j-1,min(B,sz[i]));k++)
			{
				dp[x][0][j]=min(dp[x][0][j],dp[i][0][k]+g[0][j-k]+j*k-k*k);
				dp[x][1][j]=min(dp[x][1][j],dp[i][1][k]+g[1][j-k]+2*j*k-2*k*k);
			}
		}
		for(int j=1;j<=min(B,sz[x]);j++)
		{
			dp[x][0][j]=min(dp[x][0][j],g[0][j]+min1); dp[x][1][j]=min(dp[x][1][j],g[1][j]+min0);
		}
		sz[x]+=sz[i]; dp[i][0].clear(); dp[i][0].shrink_to_fit(); dp[i][1].clear(); dp[i][1].shrink_to_fit();//
	}
}

signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n; for(int i=1;i<=n;i++) e[i].clear(),dp[i][0].clear(),dp[i][1].clear();
		for(int i=1;i<=n-1;i++) {cin>>u>>v; e[u].pb(v); e[v].pb(u);} dfs(1,1);
		int nans=INF; for(int i=1;i<=min(B,sz[1]);i++) nans=min(nans,min(dp[1][0][i],dp[1][1][i]));
		cout<<n*(n+1)-nans<<endl;//
	}
}
```


---

## 作者：pikiuk (赞：6)

显然，一条路径 $\operatorname{mex}$ 的取值有且仅有 $\{0,1,2\}$ 三种，我们希望他尽可能的是 $2$。

观察性质，注意到如果一条路径始终是单色的，那么他的贡献才不是 $2$，这个条件非常的苛刻，启发我们逆向思考：不妨假设所有路径的贡献都是 $2$，去统计最少损失的贡献量。

进一步的，从“路径上所有点同色”这一性质出发，不难发现仅有极大同色连通块之间的点对会折损贡献，且具体的折损量和颜色以及连通块大小正相关，无疑，可以动态规划解决。

我们记 $f(u,x,0/1)$ 表示对于以 $u$ 为根的子树，$u$ 的颜色是 $0/1$，$u$ 所在的极大同色连通块的大小是 $x$ 时的最小折损，朴素树上背包是 $\mathcal{O}(n^2)$ 的。

事实上，我们不难猜测，$x$ 的大小不会很大，否则我们将其拆开可能更优，但是，$x$ 是否有一个更具体，明晰的上界呢，事实上是有的。

我们考虑这么一个构造，对于整棵树，我们以二分图的方式对其染色，那么有且仅有形如 $u\to u$ 的路径的权值不是 $2$，总的折损量级不会超过 $\mathcal{O}(n)$，而大小为 $x$ 的极大同色连通块的折损已经达到了 $\mathcal{O}(x^2)$。不难发现，我们关心的 $x$ 只有 $\mathcal{O}(\sqrt n)$ 级别的，做树上背包即可。

```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7, M = 507, inf = 0x3f3f3f3f;
int n, m, siz[N], Bu, Bv, B, T; vector <int> e[N], f[N][2], g[2];
void chkmin (int &x, int y) {x = (x > y) ? y : x;}
void dfs (int u, int fa) {
	siz[u] = 1; g[0].clear (); g[1].clear ();
	for (int i = 0; i < 2; i ++) f[u][i].resize (2);
	f[u][0][0] = f[u][1][0] = inf;
	f[u][1][1] = 2; f[u][0][1] = 1;
	for (auto v : e[u]) {
		if (v == fa) continue;
		dfs (v, u); 
		B = min ((int) sqrt (siz[u] + siz[v] - 1) + 1, M - 7); 
		Bu = min ((int) sqrt (siz[u] - 1) + 1, M - 7); 
		Bv = min((int) sqrt (siz[v] - 1) + 1, M - 7);
		g[0].resize (B + 7); g[1].resize (B + 7);
		for (auto &i : g[0]) i = inf;
		for (auto &i : g[1]) i = inf;
		for (int i = 1; i <= Bu; i ++) {
			for (int j = 1; j <= Bv; j ++) {
				if (i + j < B) {
					chkmin (g[0][i + j], f[u][0][i] + f[v][0][j] + i * j); // 0 + 0
					chkmin (g[1][i + j], f[u][1][i] + f[v][1][j] + 2 * i * j); // 1 + 1
					assert (g[1][i + j]);
				}
				chkmin (g[0][i], f[u][0][i] + f[v][1][j]); // 0 + 1
				chkmin (g[1][i], f[u][1][i] + f[v][0][j]); // 1 + 0
				assert (g[1][i]);
			}
		} f[u][0] = g[0]; f[u][1] = g[1]; siz[u] += siz[v];
		vector<int> ().swap (f[v][0]); vector<int> ().swap (f[v][1]);
	}
}
void solve () {
	cin >> n; 
	for (int i = 1; i <= n; i ++) e[i].clear (), siz[i] = 0;
	for (int i = 1, u, v; i < n; i ++) {
		cin >> u >> v; 
		e[u].push_back (v); 
		e[v].push_back (u);
	} dfs (1, 0); int ans = inf;
	for (auto i : f[1][0]) chkmin (ans, i);
	for (auto i : f[1][1]) chkmin (ans, i);
	cout << 1ll * n * (n + 1) - ans << "\n";
}
signed main () {
	cin >> T; while (T --) solve ();
}
```

---

## 作者：Hisaishi_Kanade (赞：5)

由 $\text{mex}$ 的定义可以知道，这棵树的 $\text{mex}$ 只可能是 $0,1,2$。

我们似乎可以 $0,1$ 交错的染，这样的答案是 $n(n+1)-2\sum[col_i=0]-\sum[col_i=1]$，但是这样的话树的形状奇怪一些估计就是错的。

对于 $x\to y$ 的一条路径，当全部是 $0$ 的时候 $\text{mex}=1$；全部是 $1$ 的时候 $\text{mex}=0$；否则 $\text{mex}=2$。这启发我们可以按照颜色分割成一个一个连通块，称为零块和一块，这样我们将路径分成两类，一类是跨块的，一类是不跨块的。当作为零块的时候，这之中所有的路径就是 $\text{mex}=1$ 的；当作为一块的时候，这之中所有的路径就是 $\text{mex}=0$ 的。跨块的路径必然又有 $0$ 又有 $1$，那么这条路径必然经过 $0,1$，$\text{mex}=2$。

答案肯定不超过 $n(n+1)$，每个连通块相当于减去一小部分价值。我们直接来大力 dp。设 $f(i,j,k)$ 表示子树 $i$，构造出大小为 $j$ 颜色为 $k$ 的连通块，最小的损耗。

考虑 $x$ 为根的一颗子树和根节点不染一个色，$f(i,j,0)=\min\{f(x,j^{\prime},1)\}$ 和 $f(i,j,1)=\min\{f(x,j^{\prime},0)\}$。

那么接下来考虑成为一个连通块，如何从 $f(i,p,k)$ 和 $f(x,q,k)$ 转移出 $f(i,p+q,k)$。我们发现实际上减去的价值是 $p$ 个和 $q$ 个这 $p\times q$ 条路径产生的，当 $k=0$ 时，每条路径产生 $1$ 的损耗，$k=1$ 时产生 $2$ 的损耗。

即 $f(i,p+q,k)=\min\{f(i,p,k)+f(x,q,k)+\omega\}$。当 $k=1$ 时 $\omega=2pq$；$k=0$ 时，$\omega=pq$。

这样 dp 就会了，但是复杂度是 $n^2$ 的跑不动。

直觉告诉我们连通块一定不会很大，太大应该不会更优。实际上确实是这样。

还记得最开始交错染色吗，当 $0,1$ 染得个数相同时就能取到，这样减去的量级是 $\dfrac 3 2n$，如果你某个连通块减去的价值甚至比这个多，那还不如直接贪。

所以就会有 $\omega\le\dfrac 3 2 n$，也就是 $p=q$ 时 $p,q$ 在 $\dfrac {\sqrt {6n}} 2$ 这样，算了一下大概在 $500$ 左右，直接就跑 $500$ 可以了。

注意到空间开不下，考虑到这个儿子只有父亲求解会用到，所以当求解完就把儿子的数组释放了。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
using namespace std;
using ll=long long;
const ll N=2e5+5,inf=1ll<<40;
const int M=500;
int siz[N];
vector<int> e[N];
vector<ll> f[N][2];
inline void dp(int id,int fa)
{
    int i,j;
    int lu,lv;
    siz[id]=1;
    vector<ll> g[2];
    f[id][0].resize(2);
    f[id][1].resize(2);
    f[id][0][0]=f[id][1][0]=inf;
    f[id][0][1]=1,f[id][1][1]=2;
    for(int nxt:e[id])
    {
        if(nxt==fa)
            continue;
        else
            dp(nxt,id);
        vector<ll>p(min(siz[id]+siz[nxt],M)+1,inf);
		g[0]=p;g[1]=p;
	    lu=min(siz[id],M);lv=min(siz[nxt],M);
        rep(i,1,lu)
        {
            rep(j,1,lv)
            {
                if(i+j<M)
                {
                    g[0][i+j]=min(g[0][i+j],f[id][0][i]+f[nxt][0][j]+i*j);
                    g[1][i+j]=min(g[1][i+j],f[id][1][i]+f[nxt][1][j]+2*i*j);
                }
                g[0][i]=min(g[0][i],f[id][0][i]+f[nxt][1][j]);
                g[1][i]=min(g[1][i],f[id][1][i]+f[nxt][0][j]);
            }
        }
        f[id][0]=g[0];
        f[id][1]=g[1];
        vector<ll>().swap(f[nxt][0]);
        vector<ll>().swap(f[nxt][1]);
        siz[id]+=siz[nxt];
    }
}
inline void solve()
{
    int n,i,u,v;
    scanf("%d",&n);
    rep(i,1,n)
    {
        e[i].clear();
        siz[i]=0;
    }
    rep(i,2,n)
    {
        scanf("%d %d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dp(1,0);
    ll ans=inf;
    for(auto nxt:f[1][0])ans=min(ans,nxt);
    for(auto nxt:f[1][1])ans=min(ans,nxt);
    printf("%lld\n",1ll*n*(n+1)-ans);
}
int main()
{int t;scanf("%d",&t);
    while(t--)solve();
    return 0;
}
```


---

## 作者：zhongpeilin (赞：3)

## 题目大意：
你现在要将一颗树染色 `01`，一条路径的权值为这条路径的 MEX，问树的路径权值最大为多少？
## 解题思路：
首先我们读完题后不难想到一个假做法，就是 `01` 交替的染色，但是我们通过认真思考后发现这个是有 hack，就是类似一条边两端很多个分叉，然后最优策略是这条边的两点涂 `1`，其他为 `0`。  
为什么 `01` 不优？因为对于一个 `01` 间隔的染色，每个 `1` 都没有贡献，也就是有可能比最优策略少 $O(n)$ 级别，然后对于一个 `0` 的连通块，少的贡献是 $O(n^2)$ 级别的，所以有个结论，所有全为 `01` 的连通块大小不超过 $\sqrt{n}$。  
而答案就是拿总路径数 $\times 2 - $ 所有 `1` 的连通块的大小的平方 $\times 2 - $ 所有 `0` 连通块的大小的平方。  
那么我们自然地设 $dp_{i, j, k}$ 表示 $i$ 的子树中，包含 $i$ 的连通块的大小，以及这个连通块内所有点的颜色，满足这个条件的要减去的最少之和。  
$$dp'_{i, j + j', 0} = 	dp_{i, j, 0} + dp_{son, j', 0} + j \times k$$
$$dp'_{i, j, 0} = 	dp_{i, j, 0} + dp_{son, j', 1}$$
$$dp'_{i, j + j', 1} = 	dp_{i, j, 1} + dp_{son, j', 1} + j \times k \times 2$$
$$dp'_{i, j, 1} = 	dp_{i, j, 1} + dp_{son, j', 0}$$
注意这题卡空间，所以 dp 要拿动态数组及时清空。  
时间复杂度：$O(n \times \sqrt{n})$。
## CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 0x3f3f3f3f3f3f3f3f;
int t, n, sz[200005];
vector<int> g[200005], dp[200005][2];

void dfs(int x, int fa){
	sz[x] = 1;
	dp[x][0].push_back(INF); dp[x][1].push_back(INF);
	dp[x][0].push_back(1); dp[x][1].push_back(2);
	
	vector<int> tmp[2];
	for(int i = 0; i < g[x].size(); i++){
		int y = g[x][i];
		if(y == fa) continue;
		dfs(y, x);
		
		tmp[0].clear(); tmp[1].clear();
		tmp[0].resize(ceil(sqrt(sz[x] + sz[y])) + 2, INF);
		tmp[1].resize(ceil(sqrt(sz[x] + sz[y])) + 2, INF);
		
		for(int j = ceil(sqrt(sz[x])); j >= 1; j--){
			for(int k = ceil(sqrt(sz[y])); k >= 1; k--){
				if(j + k > ceil(sqrt(sz[x] + sz[y]))) continue;
				tmp[0][j + k] = min(tmp[0][j + k], dp[x][0][j] + dp[y][0][k] + j * k);
				tmp[1][j + k] = min(tmp[1][j + k], dp[x][1][j] + dp[y][1][k] + j * k * 2);
				
				tmp[0][j] = min(tmp[0][j], dp[x][0][j] + dp[y][1][k]);
				tmp[1][j] = min(tmp[1][j], dp[x][1][j] + dp[y][0][k]);
			}
		}
		dp[x][0] = tmp[0]; dp[x][1] = tmp[1];
		
		vector<int>().swap(dp[y][0]); vector<int>().swap(dp[y][1]);
		sz[x] += sz[y];
	}
}
void solve(){
	cin >> n;
	for(int i = 1; i <= n; i++) g[i].clear();
	for(int i = 1; i < n; i++){
		int x, y;
		scanf("%lld%lld", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1, 0);
	int ans = INF;
	for(auto it : dp[1][0]) ans = min(ans, it);
	for(auto it : dp[1][1]) ans = min(ans, it);
	printf("%lld\n", n * (n + 1) - ans);
	
	vector<int>().swap(dp[1][0]);
	vector<int>().swap(dp[1][1]);
}
signed main(){
	scanf("%lld", &t);
	while(t--) solve();
	return 0;
}
```


---

## 作者：Drifty (赞：2)

### Preface

好题，尽量把这题讲的清楚一点。

### Solution

首先有一个贪心，即二分图交替染色，是错的，但很有启发意义。以下是 Hack：

![](https://cdn.luogu.com.cn/upload/image_hosting/tue7fxiq.png)

显然 $1,2$ 点填 $1$ 更优秀，这不符合贪心的思路。

先不管这个做法，我们考虑一个 $\mathcal{O}(n^2)$ 的 DP。正着算贡献太困难了，我们不妨直接算负贡献。你会发现只有同颜色的连通块内会产生负的贡献，我们实际上需要计算的是就是这些贡献之和。

那状态就很明显了，我们设 $f_{u, i, 0/1}$ 代表以节点 $u$ 为根的子树中，当前 $u$ 连着大小为 $i$ 的联通块是的最小负贡献。然后随便转移一下：

$$
f'_{u, i + j, x} = \min_{j\le \mathrm{siz}_v} \left \{ f_{v, j, x} + f_{u, i, x} + i\times j\times (x + 1) \right \}
$$

$$
f'_{u, i, x} = \min_{j\le \mathrm{siz}_v} \left \{ f_{v, j, 1 - x} + f_{u, i, x}\right \}
$$

注意这里的转移是不断加入 $v$ 的过程中转移的。

然后我们魔法的注意到贪心对于所有两个点以上的路径都是 $2$ 的贡献，再加上会有超过一半的点是 $0$，那么答案大致在 $0.5n(n - 1) \times 2 + 0.5n$ 也就是 $n^2 - 0.5n$ 的级别。而完美的答案应该是 $n(n + 1)$。

减一减得到 $1.5n$。然后每个连通块都会产生 $\mathrm{siz}^2$ 左右的负贡献，因此比贪心更优秀的决策一定在 $\sum \mathrm{siz}^2 \le 1.5n$ 的情形下产生，这意味着连通块的大小不会超过 $\sqrt{1.5n}$。实际上可能更小。

因此枚举 $j$ 的时候只要到 $\sqrt{\mathrm{siz}_v}$ 就可以了。时间复杂度为小常数 $O(n\sqrt{n})$。

注意这题卡空间，开 vector 存状态，用完记得释放。

### Code

```cpp
void dfs (int u, int fa) {
	array <vector <int>, 2> g{};
	siz[u] = 1;
	f[u][0] = {(int)1e9, 1};
	f[u][1] = {(int)1e9, 2};

	for (auto v : e(u)) {
		if (v == fa) continue;
		dfs (v, u);
		
		int su = sqrt(siz[u]), sv = sqrt(siz[v]), 
			ss = sqrt(siz[u] + siz[v]) + 1;
		
		g[0].clear();
		g[1].clear();

		g[0].resize(ss + 1, 1e9);
		g[1].resize(ss + 1, 1e9);

		for (int i = su; i; i --) for (int j = sv; j; j --) {
            g[0][i] = min(g[0][i], f[u][0][i] + f[v][1][j]);
			g[1][i] = min(g[1][i], f[u][1][i] + f[v][0][j]);
			if (i + j > ss) continue;
			g[0][i + j] = min(g[0][i + j], f[u][0][i] + f[v][0][j] + i * j);
			g[1][i + j] = min(g[1][i + j], f[u][1][i] + f[v][1][j] + i * j * 2);
		}
		
		f[u][0] = g[0]; f[u][1] = g[1];
		f[v][0] = f[v][1] = vector <int> ();
		siz[u] += siz[v];
	}
}
```

---

## 作者：_JF_ (赞：2)

[Link](https://www.luogu.com.cn/problem/CF1830D)

梳理思路。

尽可能讲的清晰些。

首先考虑贪心交替染色，但是不正确的，反例就是一个端点左右各一车子点，这样以这个端点为中转站，一边全部填 $0$，另一边全部填 $1$ 更优秀。

稍微观察题目就能发现，题目能取到的 $\operatorname{mex}$ 仅在 $[0,2]$ 中，并且一条路径上如果只有一种颜色，那就只能取到 $[0,1]$ 了。

所以我们不妨从 $1$ 种颜色入手，消去限制。而这样的话我们需要反过来搞，不妨考虑如果当前我们所有路径答案都是 $2$，然后使得取到 $[0,1]$ 的和最小，就能保证答案最大。也就是理想的总贡献减去最小负贡献。

在树上，考虑只有一种颜色（单一的，对于点的限制）的影响，就可以把他转换成这个颜色所在的连通块，而对于一个连通块他对答案的贡献，在这里我们是容易计算的，假设当前连通块大小为 $x$，颜色是 $y$，那贡献就是 $\frac{x\times(x-1) \times (y+1)}{2}+x\times(y+1)$。

所以，我们把连通块设到状态里面，设 $dp_{i,j,0/1}$ 以 $i$ 为根的子树，连通块大小为 $j$，连通块颜色为 $0/1$，所能产生的最小贡献。

转移的话，直接根据所设状态含义转移就好了：

$$dp_{i,j,0}=\min\{dp_{i,j,0},dp_{i,j,0}+dp_{v,k,1},dp_{i,j-k,0}+dp_{v,k,0}-(j-k)\times k \}$$

$$dp_{i,j,1}=\min\{dp_{i,j,1},dp_{i,j,1}+dp_{v,k,0},dp_{i,j-k,1}+dp_{v,k,1}-2\times (j-k)\times k \}$$

这样做的话时间复杂度是 $O(n^2)$ 的，但是注意到这样的连通块大小不会太大，一个连通块的贡献大概算下来是 $x^2$ 的，所以连通块最大不能超过 $\sqrt n$。

注意卡空间，用完儿子的转移后立刻释放掉，时间复杂度为 $O(n\sqrt n)$。

参考了第一篇题解的实现，这题不能通过倒序的方式实现背包，以后还是尽量使用记录答案的正序吧。

最大的启示是在正难则反的考虑以及对连通块的一个考虑。

逆天题，很新的一种技巧，自己是一步都想不到。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N =2e5+5;
const int lst=785ll;
vector<int> dp[N][2],g[N];
int n,t,siz[N],G[2][805];
void dfs(int u,int fath){
	siz[u]=1;
	dp[u][1].push_back(1e9),dp[u][0].push_back(1e9);
	dp[u][1].push_back(2),dp[u][0].push_back(1);
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fath)	continue;
		dfs(v,u);
		int Min=1e9,Min1=1e9;
		for(int j=1;j<=min(lst,siz[u]);j++)	G[0][j]=dp[u][0][j],G[1][j]=dp[u][1][j],dp[u][0][j]=dp[u][1][j]=1e9;
		for(int j=1;j<=min(lst,siz[v]);j++)	Min=min(Min,dp[v][0][j]),Min1=min(Min1,dp[v][1][j]);
		for(int j=min(lst,siz[u])+1;j<=min(lst,siz[u]+siz[v]);j++)	dp[u][0].push_back(1e9),dp[u][1].push_back(1e9);
		for(int j=min(lst,siz[u]+siz[v]);j>=1;j--)
			for(int k=max(1ll*1,j-min(lst,siz[u]));k<=min(j-1,min(lst,siz[v]));k++){
				dp[u][0][j]=min(dp[u][0][j],G[0][j-k]+dp[v][0][k]+(j-k)*k);
				dp[u][1][j]=min(dp[u][1][j],G[1][j-k]+dp[v][1][k]+2*(j-k)*k);
			}
		for(int j=1;j<=min(lst,siz[u]);j++)
			dp[u][0][j]=min(dp[u][0][j],G[0][j]+Min1),dp[u][1][j]=min(dp[u][1][j],G[1][j]+Min);
		dp[v][0].clear(),dp[v][1].clear(), dp[v][0].shrink_to_fit(); dp[v][1].shrink_to_fit();;
		siz[u]+=siz[v];
	}
}
signed main()
{
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1,u,v;i<n;i++)	cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
		dfs(1,0);
		int ans=1e9;
		for(int i=1;i<=min(siz[1],lst);i++)
			ans=min(ans,min(dp[1][0][i],dp[1][1][i]));
		cout<<n*(n-1)+2*n-ans<<endl;
		dp[1][0].clear(),dp[1][1].clear();
		for(int i=1;i<=n;i++)	g[i].clear();
		for(int i=1;i<=n;i++)	siz[i]=0;
	}
	return 0;
}
// dp_u,0/1,j , block j ,now use 0/1 
```


---

## 作者：EuphoricStar (赞：2)

考虑答案的下界。

对整棵树进行二分图染色，我们得到答案是 $n \times (n + 1) - O(n)$ 级别的。但是二分图染色不一定是最优的。

考虑计算 $O(n)$ 的损失。发现在极大同色连通块内的点对才会造成损失，并且因为损失是 $O(n)$ 的，所以极大同色连通块大小是 $O(\sqrt{n})$ 的。

考虑 dp，设 $f_{u,0/1,i}$ 为包含 $u$ 的极大颜色为 $0/1$ 的连通块大小是 $i$ 的最少损失。转移就按照直接树形背包合并就行。注意我们在 $v \to u$ 且 $u,v$ 颜色不同时计算 $v$ 的连通块的贡献。

本题卡空间，因此需要对于每个 $f_{u,0/1,i}$ 开大小为 $\min(sz_u, \sqrt{n})$ 的 vector，并且合并完立刻销毁。

[code](https://codeforces.com/contest/1830/submission/207715342)

---

## 作者：orz_z (赞：2)



观察到贡献不为 $2$ 的点对形成多个连通块，于是考虑树上背包。

记 $f_{u,i,c}$ 表示点 $u$ 的子树内，点 $u$ 所在的连通块大小为 $i$（这个连通块满足其上所有点对贡献不为 $2$，即所有点点权相等），点 $u$ 的颜色为 $c$，$u$ 子树的最大答案。

分析复杂度可知为 $\mathcal O(n^2)$。

考虑一种贪心，对树进行二分图染色，答案可达 $n(n+1)-\mathcal O(n)$。

注意到对于一个大小为 $k$ 的连通块，会使答案减少 $\mathcal O(k^2)$。

故在一个最优性方案中，连通块大小不超过 $\mathcal O(\sqrt{n})$。

复杂度优化为 $\mathcal O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> pii;
typedef vector<int> vi;
#define F(i, a, b) for(int i = a; i <= (b); ++i)
#define F2(i, a, b) for(int i = a; i < (b); ++i)
#define dF(i, a, b) for(int i = a; i >= (b); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define Debug debug("Passing [%s] in LINS %d\n", __FUNCTION__, __LINE__)
#define pb push_back
#define fi first
#define se second
#define Mry debug("%.3lf MB\n", (&Mbe - &Med) / 1048576.0)
#define Try cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
typedef long long ll;
//namespace Fread {const int SIZE = 1 << 17; char buf[SIZE], *S, *T; inline char getchar() {if (S == T) {T = (S = buf) + fread(buf, 1, SIZE, stdin); if (S == T) return '\n';} return *S++;}}
//namespace Fwrite {const int SIZE = 1 << 17; char buf[SIZE], *S = buf, *T = buf + SIZE; inline void flush() {fwrite(buf, 1, S - buf, stdout), S = buf;} inline void putchar(char c) {*S++ = c;if (S == T) flush();} struct NTR {~NTR() {flush();}} ztr;}
//#ifdef ONLINE_JUDGE
//#define getchar Fread::getchar
//#define putchar Fwrite::putchar
//#endif
inline int ri() {
	int x = 0;
	bool t = 0;
	char c = getchar();
	while (c < '0' || c > '9') t |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return t ? -x : x;
}
inline void wi(int x) {
	if (x < 0) {
		putchar('-'), x = -x;
	}
	if (x > 9) wi(x / 10);
	putchar(x % 10 + 48);
}
inline void wi(int x, char s) {
	wi(x), putchar(s);
}
bool Mbe;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const int _ = 2e5 + 5, Sq = sqrt(_) + 5;
int n, m, tmp[Sq + 5], sz[_];
vector<int> f[_][2];
vector<int> d[_];
void dfs(int u, int fa) {
	int sq;
	f[u][0].resize(5), f[u][1].resize(5);
	f[u][0][1] = 1, f[u][1][1] = 0;
	sz[u] = 1;
	for(int v : d[u]) if(v != fa) {
		dfs(v, u);
		int K = min(Sq, sz[v]);
		sq = min(Sq, sz[u]);
		int Sqq = min(Sq, sz[u] + sz[v]);
		F(i, 1, Sqq) tmp[i] = 0;
		F(i, 1, sq) {
			F(j, 1, K) tmp[i] = max(tmp[i], f[u][0][i] + f[v][1][j] + 2 * sz[u] * sz[v]);
			F(j, 1, min(K, Sqq - i)) tmp[i + j] = max(tmp[i + j], f[u][0][i] + f[v][0][j] - i * j + 2 * (sz[u] * sz[v]));
		}
		f[u][0].resize(Sqq + 5);
		F(i, 1, Sqq) f[u][0][i] = tmp[i];
		F(i, 1, Sqq) tmp[i] = 0;
		F(i, 1, sq) {
			F(j, 1, K) tmp[i] = max(tmp[i], f[u][1][i] + f[v][0][j] + 2 * sz[u] * sz[v]);
			F(j, 1, min(K, Sqq - i)) tmp[i + j] = max(tmp[i + j], f[u][1][i] + f[v][1][j] + 2 * (sz[u] * sz[v] - i * j));
		}
		f[u][1].resize(Sqq + 5);
		F(i, 1, Sqq) f[u][1][i] = tmp[i];
		sz[u] += sz[v];
		f[v][0].clear(), f[v][0].shrink_to_fit();
		f[v][1].clear(), f[v][1].shrink_to_fit();
	}
}
void solve() {
	n = ri();
	F(i, 1, n) d[i].clear(), d[i].shrink_to_fit();
	F(i, 1, n - 1) {
		int u = ri(), v = ri();
		d[u].pb(v), d[v].pb(u);
	}
	F(i, 0, n + 2) f[i][0].clear(), f[i][0].shrink_to_fit(), f[i][1].clear(), f[i][1].shrink_to_fit();
	dfs(1, 0);
	int ans = 0;
	F(i, 1, min(Sq, sz[1])) ans = max(ans, max(f[1][0][i], f[1][1][i]));
	cout << ans << '\n';
}

bool Med;
signed main() {
//	freopen("1.txt", "r", stdin);
	// Mry;
//	cout << Sq;
	int T = ri();
	while(T--) 
		solve();
	Try;
}
```





---

## 作者：hfjh (赞：2)

# CF1830D Mex Tree 题解
## 题意

给定一棵 $n$ 个结点的树，点有点权，点权为 0 或 1。你需要给一种指定点权的方案，使得每一条路径的点权 $\operatorname{mex}$ 之和最大。

## 题解

考虑最优解是大多路径都是 2，少部分是 1 或者 0。

那么我们记录距离所有路径都是 2 的情况缺失多少，我们要让缺失值最小。

设 $f_{u, 0/1,i}$ 表示以 $u$ 为根的子树，$u$ 是 $0/1$，$u$ 子树和 $u$ 值相同的联通块大小为 $i$。

$f$ 初始值就是 $f_{u,0,1} = 1,f_{u,1,1} = 2$。

> 本身到本身有贡献。

转移方程就是：

$$
f_{u,0,j} = \min(f_{u,0,j} + \min_{k=1}^{siz[v]}f_{v,1,k}, 
\min_{k = 1}^{siz[v]}(f_{u,0,j - k} + f_{v,0,k}+(j-k)\times k)\\

f_{u,1,j} = \min(f_{u,1,j} + \min_{k=1}^{siz[v]}f_{v,0,k}, 
\min_{k = 1}^{siz[v]}(f_{u,1,j - k} + f_{v,1,k}+2\times(j-k)\times k)
$$

这样是 $O(n^2)$ 的，我们怎么优化呢？

### 优化

我们考虑设每个子树大小为 $siz$，最优情况联通块大小不超过 $\sqrt {2n}$。

因为我们可以发现一种比较优秀的情况是黑白染色，这时候缺失值最多为 $2n$。

当联通块大小为 $x$ 时，缺失值最少是 $x^2$，当联通块大小 $\ge \sqrt {2n}$ 时候一定不够优秀。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = 300;
const int inf = 1e9; 
char _begin;
int t, n, x, y, tot = 0, w;
int head[N], siz[N];
int B, Bu, Bv; 
int ans = inf;
vector<int> f[N][2], g[2];
struct node{
	int next, to, w;	
}edge[2 * N];
char _end;
void add(int x, int y, int w){
	++tot;
	edge[tot].next = head[x];
	edge[tot].to = y;
	edge[tot].w = w;
	head[x] = tot;
}
void input(){
	cin>>n;
	for(int i = 1; i < n; ++i){
		cin>> x >> y;
		add(x, y, i);
		add(y, x, i);
	}
}
void dfs(int x, int fa){
	siz[x] = 1;
	f[x][0].resize(2); f[x][1].resize(2);
	f[x][0][0] = f[x][1][0] = inf;
	f[x][0][1] = 1; f[x][1][1] = 2;
	for(int i = head[x]; i; i = edge[i].next){
		int y = edge[i].to;
		if(y == fa) continue;
		dfs(y, x);
		
		B = min ((int) sqrt (siz[x] + siz[y] - 1) + 1, M - 7); 
		Bu = min ((int) sqrt (siz[x] - 1) + 1, M - 7); 
		Bv = min((int) sqrt (siz[y] - 1) + 1, M - 7);
		
		g[0].resize (B + 7); g[1].resize (B + 7);
		
		for (auto &i : g[0]) i = inf;
		for (auto &i : g[1]) i = inf;
		int mi0 = inf, mi1 = inf;
		for(int k = 1; k <= Bv; ++k){
			mi0 = min(mi0, f[y][0][k]);
			mi1 = min(mi1, f[y][1][k]);
		}
		for(int j = 1; j <= B; ++j){
			for(int k = 1; k <= min(j - 1, Bv); ++k){
				g[0][j] = min(g[0][j], f[x][0][j - k] + f[y][0][k] + (j - k) * k);
				g[1][j] = min(g[1][j], f[x][1][j - k] + f[y][1][k] + 2 * (j - k) * k);
			}	
			g[0][j] = min(g[0][j], f[x][0][j] + mi1);
			g[1][j] = min(g[1][j], f[x][1][j] + mi0);
			
		}
		siz[x] += siz[y];
		f[x][0] = g[0], f[x][1] = g[1];
		vector<int> ().swap(f[y][0]);
		vector<int> ().swap(f[y][1]);
	}
}
void output(){
	ans = inf;
	for(int i : f[1][0]) ans = min(ans, i);
	for(int i : f[1][1]) ans = min(ans, i);
	cout<<1ll * n * (n + 1) - ans<<'\n';
}
void qk(){
	tot = 0;
	for(int i = 1; i <= n; ++i) head[i] = 0;
}
int main(){
	cerr<<(&_begin - &_end) / 1024 / 1024<<'\n';
	cin>>t;
	qk();
	while(t--){
		input();
		dfs(1, 0);
		output();
		qk();
	}
} 
```

---

## 作者：Purslane (赞：0)

# Solution

简单 `*2800`。发现路径的 $\rm mex$ 只有 $0/1/2$ 三种情况。

具体的，将相邻的、值相同的点缩点。不同连通块之间的路径 $\rm mex$ 必定是 $2$；$0$ 连通块内部路径的 $\rm mex$ 是 $1$，$1$ 连通块内部路径的 $\rm mex$ 是 $0$。

这样容易设计一个 $O(n^2)$ 的树形 $\rm DP$，但是没啥用。下面用黑色表示 $1$，白色表示 $0$。

直接黑白染色，可以做到 $n(n-1) + c$，其中 $c$ 是白色点的数量，大于 $\frac{n-1}{2}$。而显然答案具有上界 $n(n-1)+n$，记为 $u$。

如果有一个大小为 $s$ 的连通块，会在 $u$ 基础上至少损失 $\frac{s(s-1)}{2}$。所以 $s(s-1) \le n$，有 $s \le \sqrt n + 1$。

这样背包就是 $O(n^{1.5})$ 的了。树形背包可以通过即使释放做到 $O(n)$ 空间。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int T,n,lim,tmp[MAXN];
vector<int> dp[MAXN][2],G[MAXN];
void dfs(int u,int f) {
	dp[u][0].push_back(-0x3f3f3f3f3f3f3f3f),dp[u][1].push_back(-0x3f3f3f3f3f3f3f3f);
	dp[u][0].push_back(0),dp[u][1].push_back(0);
	for(auto v:G[u]) if(v!=f) {
		dfs(v,u);
		int s=min(lim,(int)(dp[u][0].size()+dp[v][0].size()-2));
		ffor(i,0,s) tmp[i]=-0x3f3f3f3f3f3f3f3f;
		ffor(i,0,dp[u][0].size()-1) ffor(j,0,dp[v][0].size()-1) if(i+j<=s) tmp[i+j]=max(tmp[i+j],dp[u][0][i]+dp[v][0][j]);
		dp[u][0].clear();
		ffor(i,0,s) dp[u][0].push_back(tmp[i]);
		ffor(i,0,s) tmp[i]=-0x3f3f3f3f3f3f3f3f;
		ffor(i,0,dp[u][1].size()-1) ffor(j,0,dp[v][0].size()-1) if(i+j<=s) tmp[i+j]=max(tmp[i+j],dp[u][1][i]+dp[v][1][j]);
		dp[u][1].clear();
		ffor(i,0,s) dp[u][1].push_back(tmp[i]);
		vector<int> ().swap(dp[v][0]);
		vector<int> ().swap(dp[v][1]);
	}
	ffor(i,1,dp[u][0].size()-1) dp[u][1][0]=max(dp[u][1][0],dp[u][0][i]+i*(n-i)+i*(i+1)/2);
	ffor(i,1,dp[u][1].size()-1) dp[u][0][0]=max(dp[u][0][0],dp[u][1][i]+i*(n-i));
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n,lim=sqrt(n)+2;
		ffor(i,1,n) G[i].clear(),dp[i][0].clear(),dp[i][1].clear();
		ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
		dfs(1,0);
		cout<<max(dp[1][0][0],dp[1][1][0])<<'\n';
	}
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

一眼望去是一道构造题，所以我们先想有没有上界。

令 $f(x, y)$ 表示 $x$ 到 $y$ 路径的 $\operatorname{mex}$。最好的情况是让任何 $x \neq y$ 都有 $f(x, y) = 2$，且对于任何 $x$ 都有 $f(x, x) = 1$。但是只要出现一个权值为 $1$ 的点，这个上界就取不到。

接着想尽量接近上界的染色方法。很快我们便发现，容易构造一组方案（比如交替染色等等）使得其权值与上界相差不远 （$O(n)$ 级别以内）。受其启发，我们可以反过来思考，假定所有 $f(x, y)$ 都是 $2$，再算出减去的最小贡献就是答案了。

定义 $f_{pos, c, num}$ 表示考虑 $pos$ 的子树，且 $pos$ 的权值是 $c$，其所在的同权值连通块有 $num$ 个节点。由于交替染色与答案的差已经在 $O(n)$ 级别了，因此 $num$ 这一维不会很大，最多 $O(\sqrt{n})$ 级别。实际上，取 $300$ 就能通过了。

这里存在一个树形背包空间优化技巧：用动态数组存 DP 数组，用完就清空。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

bool ST;

const int N = 200010;
int T, n, m = 300, siz[N]; vector < int > tr[N], f[N][2];
inline int calc(int opt, int n)
{
	if(opt == 0) return n * (n + 1) / 2;
	else return n * (n + 1);
}
inline void update(int &now, int ex) {now = min(now, ex);}
inline void clear(int p)
{
	f[p][0].clear(), f[p][0].shrink_to_fit();
	f[p][1].clear(), f[p][1].shrink_to_fit();
}
int tmp[2][301];
inline void treedp(int now, int prt)
{
	siz[now] = 1;
	f[now][0].push_back(0); f[now][0].push_back(0);
	f[now][1].push_back(0); f[now][1].push_back(0);
	for(int to : tr[now])
	{
		if(to == prt) continue;
		treedp(to, now);
		for(int i = 0; i <= 1; ++i)
			for(int j = 0; j <= m; ++j)
				tmp[i][j] = 1e9;
		for(int op_n = 0; op_n <= 1; ++op_n)
		{
			for(int num_n = 1; num_n <= min(m, siz[now]); ++num_n)
			{
				for(int op_t = 0; op_t <= 1; ++op_t)
				{
					for(int num_t = 1; num_t <= min(m, siz[to]); ++num_t)
					{
						if(op_n == op_t && num_n + num_t > m) continue;
						update(tmp[op_n][num_n + (op_n == op_t) * num_t], f[now][op_n][num_n] + f[to][op_t][num_t] + (op_n != op_t) * calc(op_t, num_t));
					}
				}
			}
		}
		for(int i = siz[now] + 1; i <= min(m, siz[now] + siz[to]); ++i)
			f[now][0].push_back(0), f[now][1].push_back(0);
		siz[now] += siz[to]; clear(to);
		for(int i = 0; i <= 1; ++i)
			for(int j = 0; j <= min(siz[now], m); ++j)
				f[now][i][j] = tmp[i][j];
	}
}
inline void sol()
{
	for(int i = 1; i <= n; ++i) tr[i].clear(), clear(i);
	cin >> n;
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		tr[x].push_back(y);
		tr[y].push_back(x);
	}
	treedp(1, 0);
	int res = 1e9;
	for(int i = 0; i <= 1; ++i)
		for(int j = 1; j <= min(siz[1], m); ++j)
			res = min(res, f[1][i][j] + calc(i, j));
	cout << 2ll * n * (n + 1) / 2 - res << '\n';
}

bool ED;

int main()
{
	cerr << (&ED - &ST) / 1024.0 / 1024.0 << '\n';
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--) sol();
	return 0;
}
/*

*/
```

---

## 作者：SnowTrace (赞：0)

好题。

首先对题目进行分析，我们考虑什么情况下 mex 不是 $2$。

注意到 mex 不是 $2$ ，当且仅当路径的两个端点都在一个同色的连通块内。启示我们对连通块进行处理，也就是使用树形背包。$dp_{i,j,0/1}$ 表示考虑把以 $i$ 为根的子树染完了，$i$ 所在的连通块里面全是 $0$ 或全是 $1$ ，且这个连通块大小是 $j$ 时的答案。

直接做复杂度是 $O(n^2)$ 的，考虑优化。

注意到，对树做二分图染色 ，可以得到的答案大概是 $n(n+1)-1.5n$。

而我们知道，如果有一个大小为 $k$ 的同色连通块，则答案肯定小于等于 $n(n+1)-k(k+1)/2$，也就是说，如果存在同色连通块使得，$k\geq \sqrt n$，那么这个情况一定不是最优的。

从而我们把 dp 的第二维降到了 $O(\sqrt n)$ 的级别。

时间复杂度 $O(n\sqrt n)$，可以通过。

空间有点大，需要用 vector 卡一卡才能过。

----

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M = 500;
vector<int>dp[200005][2];
//代码中 dp 数组记录的是损失了多少。
int n;vector<int>p[200005];
int sz[200005];
int mn[200005][2];
//统计贡献的方式是在连通块的最深处统计
void dfs(int now,int fa){
	sz[now]= 1;
	for(int i =0 ;i<p[now].size();i++){
		if(p[now][i] ==fa)continue;
		dfs(p[now][i],now);sz[now]+=sz[p[now][i]];
	}dp[now][0].resize(min(M,sz[now])+5,100000000),dp[now][1].resize(min(M,sz[now])+5,100000000);
	//根节点选1，带来两倍的损失。
	dp[now][1][1] = 0;dp[now][0][1] = 0;int sum = 1;
	for(int x:p[now]){
		if(x == fa)continue;
		for(int j = min(M,sum+sz[x]);j>=1;j--){
			dp[now][1][j] = dp[now][1][j]+mn[x][0];
			dp[now][0][j] = dp[now][0][j]+mn[x][1];
			for(int k = max(1,j-sum);k<=sz[x];k++){
				if(k>j)break;
				dp[now][1][j] = min(dp[now][1][j],dp[now][1][j-k]+dp[x][1][k]);
				dp[now][0][j] = min(dp[now][0][j],dp[now][0][j-k]+dp[x][0][k]);
			}
		}sum+=sz[x];
		dp[x][0].clear(),dp[x][1].clear();
		dp[x][0].shrink_to_fit();dp[x][1].shrink_to_fit();
		//释放空间，注意 clear 函数单独用不能释放空间。
	}mn[now][0] = mn[now][1] = 100000000;
	for(int i =0;i<=min(M,sz[now]);i++){
		mn[now][0] = min(mn[now][0],dp[now][0][i]+i*(i+1)/2);
		mn[now][1] = min(mn[now][1],dp[now][1][i]+i*(i+1));
	}
	//根节点选0，带来1倍的损失。
}
void solve(){
	cin >> n;
	for(int i = 1;i<=n;i++)dp[i][0].clear(),dp[i][1].clear(),p[i].clear();
	for(int i = 1;i<n;i++){
		int a,b;cin >> a >> b;
		p[a].push_back(b),p[b].push_back(a);
	}dfs(1,1);
	long long mn = 1000000000;
	for(int i = 1;i<=min(M,sz[1]);i++){
		mn = min(mn,1ll*dp[1][0][i]+i*(i+1)/2);
		mn = min(mn,1ll*dp[1][1][i]+i*(i+1));
	}cout << 1ll*n*(n+1)-mn << endl;
}
signed main(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;cin >> t;
	while(t--){
		solve();
	}
	return 0;
}/*
真牛。
首先，必须得想到，这个东西的计算相当于考虑同色连通块
从而可以写出 O(n^2) 的树形背包。
然后继续思考，优化这个背包的过程。
注意到对树二分图染色，答案大概是 n*(n+1)-1.5n
也就是说连通块大小的平方的和小于等于 O(n)
复杂度降为 O(n^1.5)，卡空间，用vector实现




*/
```

---

## 作者：intel_core (赞：0)

朴素的想法是令 $f_{i,j,0/1}$ 表示考虑完 $i$ 的子树，与 $i$ 同一个颜色块里的点有 $j$ 个，然后在每个颜色块最上端的顶点计算贡献即可。

这样明显是 $O(n^2)$ 的，考虑优化。

注意到对于原树黑白染色，答案可以做到 $n^2-O(n)$，而又因为一个大小为 $j$ 的连通块对答案的负贡献是 $j^2$ 量级的，所以 $j$ 这一维只需开到 $O(\sqrt{n})$ 即可。

这样相当于做了一个大小至多为 $O(\sqrt{n})$ 的背包，因此复杂度 $O(n\sqrt{n})$。

卡空间，很烦。

---

## 作者：happybob (赞：0)

如果我们将树进行二分图染色，然后黑点染 $1$，白色点染 $0$，发现答案大概是 $O(n^2)$ 量级的并且不会比 $n^2$ 小多少。

发现两个点的路径 $\operatorname{mex}$ 如果不是 $2$，那么这两个点必然在同色连通块中。考虑 DP，$f_{u,i,0/1}$ 表示以 $u$ 为根，$u$ 所在同色连通块点数为 $i$，$u$ 颜色为 $0/1$ 时的答案。转移类似树上背包。直接做是 $O(n^2)$ 的。

注意到如果一个同色连通块大小比较大，那么还不如二分图染色，故 $i$ 取到 $O(\sqrt{n})$ 量级即可。复杂度 $O(n\sqrt{n})$。

---

