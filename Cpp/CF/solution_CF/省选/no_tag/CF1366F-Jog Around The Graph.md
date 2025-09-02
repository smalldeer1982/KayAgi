# Jog Around The Graph

## 题目描述

You are given a simple weighted connected undirected graph, consisting of $ n $ vertices and $ m $ edges.

A path in the graph of length $ k $ is a sequence of $ k+1 $ vertices $ v_1, v_2, \dots, v_{k+1} $ such that for each $ i $ $ (1 \le i \le k) $ the edge $ (v_i, v_{i+1}) $ is present in the graph. A path from some vertex $ v $ also has vertex $ v_1=v $ . Note that edges and vertices are allowed to be included in the path multiple times.

The weight of the path is the total weight of edges in it.

For each $ i $ from $ 1 $ to $ q $ consider a path from vertex $ 1 $ of length $ i $ of the maximum weight. What is the sum of weights of these $ q $ paths?

Answer can be quite large, so print it modulo $ 10^9+7 $ .

## 说明/提示

Here is the graph for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1366F/982d98828c2c04ce07da51dfc61efa355738e144.png)Some maximum weight paths are:

- length $ 1 $ : edges $ (1, 7) $ — weight $ 3 $ ;
- length $ 2 $ : edges $ (1, 2), (2, 3) $ — weight $ 1+10=11 $ ;
- length $ 3 $ : edges $ (1, 5), (5, 6), (6, 4) $ — weight $ 2+7+15=24 $ ;
- length $ 4 $ : edges $ (1, 5), (5, 6), (6, 4), (6, 4) $ — weight $ 2+7+15+15=39 $ ;
- $ \dots $

So the answer is the sum of $ 25 $ terms: $ 3+11+24+39+\dots $

In the second example the maximum weight paths have weights $ 4 $ , $ 8 $ , $ 12 $ , $ 16 $ and $ 20 $ .

## 样例 #1

### 输入

```
7 8 25
1 2 1
2 3 10
3 4 2
1 5 2
5 6 7
6 4 15
5 3 1
1 7 3```

### 输出

```
4361```

## 样例 #2

### 输入

```
2 1 5
1 2 4```

### 输出

```
60```

## 样例 #3

### 输入

```
15 15 23
13 10 12
11 14 12
2 15 5
4 10 8
10 2 4
10 7 5
3 10 1
5 6 11
1 13 8
9 15 4
4 2 9
11 15 1
11 12 14
10 8 12
3 6 11```

### 输出

```
3250```

## 样例 #4

### 输入

```
5 10 10000000
2 4 798
1 5 824
5 2 558
4 1 288
3 4 1890
3 1 134
2 3 1485
4 5 284
3 5 1025
1 2 649```

### 输出

```
768500592```

# 题解

## 作者：q1uple (赞：3)

题意非常的清楚喵。

如果 $T$ 比较小的话，我们有一个 dp 喵。

设 $ dp_{i,j}$ 为在第 $i$ 个点，经过 $j$ 条边的最大长度喵。

我们有方程

$$
dp_{v,j} = \max ( dp_{u,j-1} ) 
$$

其中 $u$ 到 $v$ 有一条连边。

然后注意到走了 $m$ 次后一定是在一个最长的边来回走，所以我们枚举终点边，然后此时构成了一个形似 $y=kx+b$ 的函数，$b$ 是走到边上点的 dp 值，$k$ 显然是边权，$x$ 就是时间喵。

接下来就是找这 $n$ 条直线，他在那个范围最优，直接暴力枚举就可以了，然后因为是等差数列，我们直接求和即可喵。

[submission](https://codeforces.com/contest/1366/submission/301313226)

喵喵喵。

---

## 作者：tzc_wk (赞：3)

这道题还蛮有意思的，比赛最后几分钟肝出来了，却因为爆 int 一直 WA 8，赛后 2min 把它 A 掉了……

首先注意到图中每个简单路径的长度都 $\le m$，因此当 $k$ 比较大（$>m$）组成的路径肯定不是简单路径，故不难猜出当 $k$ 比较大时最优方案是先走到某条边 $e$ 的一个端点处，然后在这条边上来回走动，在这种情况下每过一秒经过的长度 $\Delta l$ 都等于这条边的边权 $w$，因此这条边经过的路径长度可以写成一个与时间 $t$ 有关的一次函数 $y=wt+b(t\ge t_0)$，其中 $t_0$ 为到达这条边的时间。

受到这个思想的启发，我们可以先暴力 $dp$ 求出当 $k\le m$ 时以每个点结束的最短路径，这部分的贡献我们特殊处理一下，特判掉。对于 $k>m$ 的部分我们就暴力枚举是哪条边，以及到达这条边的时间 $t_0$，这样有 $n^2$ 条直线（或者准确来说，是一条射线），求出它们的凸壳即可，复杂度 $n^2\log n$ 可以通过。当然这里也有一个非常 trival 的优化，不难发现同一条边，对于不同的 $t_0$，它们表示的直线的斜率是相同的，我们只需保留截距最大的那条即可。这样建凸包的时间可以降到 $n\log n$，总复杂度 $nm+n\log n$。

```cpp
const int MAXN=2e3;
const double EPS=1e-7;
const int MOD=1e9+7;
const int INV2=5e8+4;
int n,m,q,dp[MAXN+5][MAXN+5];ll mx[MAXN+5];
struct edge{int u,v,w;} e[MAXN+5];
vector<pii> g[MAXN+5];
struct line{
	int k,b;
	bool operator <(const line &rhs){
		if(k!=rhs.k) return k<rhs.k;
		return b<rhs.b;
	}
} l[MAXN+5];
double inter(line a,line b){return 1.0*(a.b-b.b)/(b.k-a.k);}
int stk[MAXN+5],tp=0;
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
		g[e[i].u].pb(mp(e[i].v,e[i].w));
		g[e[i].v].pb(mp(e[i].u,e[i].w));
	} memset(dp,192,sizeof(dp));dp[0][1]=0;
	for(int i=0;i<m;i++) for(int j=1;j<=n;j++){
		for(pii p:g[j]) chkmax(dp[i+1][p.fi],dp[i][j]+p.se);
	} int ans=0;memset(mx,192,sizeof(mx));
	for(int i=1;i<=m;i++){
		int mxs=0;
		for(int j=1;j<=n;j++) chkmax(mxs,dp[i][j]);
		ans=(0ll+ans+mxs)%MOD;
		for(int j=1;j<=m;j++){
			chkmax(mx[j],dp[i][e[j].u]-1ll*e[j].w*i);
			chkmax(mx[j],dp[i][e[j].v]-1ll*e[j].w*i);
		}
	} int p=0;
	for(int j=1;j<=m;j++) if(mx[j]>-0x3f3f3f3f) l[++p].k=e[j].w,l[p].b=mx[j];
	sort(l+1,l+p+1);
	for(int i=1;i<=p;i++){
		if(l[i+1].k==l[i].k) continue;
		while(tp>1){
			double it1=inter(l[stk[tp]],l[stk[tp-1]]);
			double it2=inter(l[stk[tp]],l[i]);
			if(it2>it1) break;tp--;
		} stk[++tp]=i;
	}
	for(int i=1;i<=tp;i++){
		double lft=((i==1)?m:inter(l[stk[i]],l[stk[i-1]]));
		double rit=((i==tp)?q:inter(l[stk[i]],l[stk[i+1]]));
		int L=(int)ceil(lft+EPS),R=floor(rit);
		chkmax(L,m+1);chkmin(R,q);
		if(L>R) continue;
//		printf("%d %d\n",L,R);
//		printf("%d %d\n",l[stk[i]].k,l[stk[i]].b);
		int tl=(l[stk[i]].b+1ll*L*l[stk[i]].k)%MOD;
		int tr=(l[stk[i]].b+1ll*R*l[stk[i]].k)%MOD;
		ans=(ans+1ll*(tl+tr)*(R-L+1)%MOD*INV2)%MOD;
	} printf("%d\n",ans);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

首先容易观察到最优方案一定是走若干步到某个位置，然后对着某个边来回跳。

考虑先算出 $n-1$ 步到每个位置 $i$ 的最长路。对于小于等于 $n-1$ 步的答案，计算的时候带着统计即可。

然后，我们可以发现绕着每个边来回跳的贡献可以写成 $k_ix+b_i$ 的形式。于是，我们只需要对于每条边计算 $k_ix+b_i>k_jx+b_j$ 或 $k_ix+b_i=k_jx+b_j$ 且 $i<j$ 的符合要求的 $x$ 的区间 $[l,r]$，用小学学的的等差数列求和公式计算即可。

总复杂度 $O((n+m)^2)$。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int dp[2005][2005];
int k[2005],b[2005],u[2005],v[2005],w[2005];
vector<pair<int,int>> vc[2005];
//k1x+b1>k2x+b2
//(k1-k2)x>b2-b1
//x>(b2-b1)/(k1-k2)
//k1x+b1>k2x+b2
//b1-b2>(k2-k1)x
//x<(b1-b2)/(k2-k1)
signed main(){
	int n,m,q,ans=0; cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>w[i];
		vc[u[i]].push_back(make_pair(v[i],w[i]));
		vc[v[i]].push_back(make_pair(u[i],w[i]));
	}
	memset(dp,-1,sizeof(dp)); dp[0][1]=0;
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=n;j++){
			if(dp[i-1][j]==-1) continue;
			for(auto v:vc[j]){
				dp[i][v.first]=max(dp[i][v.first],dp[i-1][j]+v.second);
			}
		}
		int maxv=0; for(int j=1;j<=n;j++) maxv=max(maxv,dp[i][j]);
		(ans+=maxv)%=mod;
	}
	q-=(n-1);
	for(int i=1;i<=m;i++){
		k[i]=w[i],b[i]=max(dp[n-1][v[i]],dp[n-1][u[i]]);
	}
	for(int i=1;i<=m;i++){
		int L=1,R=q;
		for(int j=1;j<=m;j++){
			if(i!=j){
				if(k[i]>k[j]) L=max(L,(b[j]-b[i])/(k[i]-k[j])+1);
				else if(k[i]<k[j]) R=min(R,(b[i]-b[j])/(k[j]-k[i]));
				else{
					if(b[i]>b[j]||((b[i]==b[j])&&(i<j))){
						continue;
					}
					L=q+1;
				}
			}
		}
		if(L<=R){
			(ans+=b[i]*(R-L+1)%mod+(L+R)*(R-L+1)/2%mod*k[i])%=mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：MatrixGroup (赞：0)

## 题意

给定一个无向连通带正边权图，定义 $f(i)$ 为从 $1$ 开始走 $i$ 条边最大的边权和，求 $\sum\limits_{i=1}^qf(i)$。

$|V|,|E|\le2\times10^3,q\le10^9$。

## 题解

不难发现，经过至少 $m$ 条边后，一定是在某一条边权为 $w$ 边上来回打转，而且之前的边一定使得 $\sum w-w_i$ 最小。证明显然。

因此，在经过至少 $m$ 条边后，一定有 $f(x)=\max\limits_{i=1}^ma_ix+b_i$，其中 $a_i,b_i$ 为常数。我们可以 $O(m^2)$ 地对于每个 $i,j$ 求出 $a_ix+b_i>(\ge)a_jx+b_j$ 的范围，对于每个 $i$ 求交集即为其为最大值的区间，等差数列求和即可。

注意有可能相等，因此采用如果 $a_ix+b_i=a_jx+b_j$ 则比较 $i,j$ 的方法避免算重。

---

