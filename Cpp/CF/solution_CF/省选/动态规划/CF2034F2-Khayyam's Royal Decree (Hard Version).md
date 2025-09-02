# Khayyam's Royal Decree (Hard Version)

## 题目描述

这是本题的困难版本。两个版本的唯一区别在于 $k$ 和 $\sum k$ 的限制。

Khayyam 有一个**宝箱**，**宝箱**里初始有 $n$ 个红宝石和 $m$ 个蓝宝石。一个红宝石的价值为 $2$，一个蓝宝石的价值为 $1$。他还有一个**背包**，初始为空。另外，他还有 $k$ 张卷轴，第 $i$ 张卷轴上有数对 $(r_i,b_i)$。

Khayyam 将进行一个游戏，游戏共 $n+m$ 轮，每轮流程如下：

1. Khayyam 从**宝箱**中等概率随机拿出一个宝石。
2. 他将这个宝石放入**背包**中。
3. 若存在一张卷轴 $i$，使得**宝箱**中恰有 $r_i$ 个红宝石和 $b_i$ 个蓝宝石，将所有**背包**里的宝石的价值翻倍。

一个宝石的价值可以被多次翻倍。

求游戏结束时 Khayyam **背包**里宝石的价值总和的期望值，对 $998244353$ 取模。

## 样例 #1

### 输入

```
5
3 4 0
1 1 1
1 0
3 3 2
1 1
2 2
3 3 2
2 1
1 2
10 4 5
1 0
8 0
6 4
0 2
7 4```

### 输出

```
10
499122180
798595498
149736666
414854846```

# 题解

## 作者：Tx_Lcy (赞：6)

## 思路

首先有很简单的 $\Theta(k^3)$ 容斥做法，但是这个做法非常不优美，没有利用好每次将权值 $\times 2$ 的性质，因此考虑利用一下这个性质。

我先把 $(r_i,b_i)$ 变成了 $(n-r_i,m-b_i)$，这样变换后的 $(r_i,b_i)$ 的意义就变成了当前选了 $r_i$ 个红宝石，$b_i$ 个蓝宝石。我们称现在的 $(r_i,b_i)$ 为关键点。

考虑组合意义，我们假设一个方案经过了 $k$ 个关键点 $p_1,p_2,\dots,p_k$，$p_0$ 是起点，$p_{k+1}$ 是终点，则该方案的权值是 $\sum (2(r_{p_{i}}-r_{p_{i-1}})+(b_{p_{i}}-b_{p_{i-1}})) \times 2^{k+1-i}$。

然后化简一下，变成：$\sum_{i=1}^k (2 \times r_{p_i}+b_{p_i}) \times (2^{k+1-i}-2^{k-i})+(2 \times r_{p_{k+1}}+b_{p_k+1})=\sum_{i=1}^k (2 \times r_{p_i}+b_{p_i}) \times 2^{k-i}+(2 \times r_{p_{k+1}}+b_{p_k+1})$，我们发现 $2^{k-i}$ 的组合意义就是在 $[i+1,k]$ 中任选一个标记点集合的方案数。

然后把贡献拆开来，对于 $(2 \times r_{p_{k+1}}+b_{p_k+1})$ 我们直接计算一下从 $(0,0)$ 走到 $(n,m)$ 的方案数即可，对于剩下的，相当于选一个 $i$，然后选择一个标记点集合 $S$，然后计算一下从 $(0,0)$ 开始经过 $i$ 和所有标记点最后到达 $(n,m)$ 的方案数乘上 $(2 \times r_i+b_i)$。

然后就能直接 DP 了，时间复杂度 $\Theta(n+m+k^2)$。

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
#define add(x,y) (x=((x+y>=mod)?(x+y-mod):(x+y)))
int const N=1e6+10,M=5e3+10,mod=998244353;
int n,m,k,fac[N],inv[N],r[M],b[M],dp[M],id[M];
inline int qpow(int a,int b){int res=1;while (b){if (b&1) res*=a,res%=mod;a*=a,a%=mod,b>>=1;}return res;}
inline int C(int n,int m){if (n<m || m<0) return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
inline void solve(){
	cin>>n>>m>>k;
	rep(i,1,k) cin>>r[i]>>b[i],r[i]=n-r[i],b[i]=m-b[i],id[i]=i;
	sort(id+1,id+k+1,[](int x,int y){return (r[x]==r[y])?(b[x]<b[y]):(r[x]<r[y]);});
	int div=qpow(C(n+m,m),mod-2),ans=C(n+m,m)*(n*2+m)%mod;
	rep(g,1,k){
		int i=id[g];
		dp[i]=C(r[i]+b[i],r[i])*(r[i]*2+b[i])%mod;
		rep(j,1,k) if (j!=i && r[j]<=r[i] && b[j]<=b[i])
			add(dp[i],C(r[i]-r[j]+b[i]-b[j],r[i]-r[j])*dp[j]%mod)%mod;
		add(ans,C(n-r[i]+m-b[i],n-r[i])*dp[i]%mod);
	}
	cout<<ans*div%mod<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	fac[0]=1;
	rep(i,1,N-1) fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	per(i,N-2,0) inv[i]=inv[i+1]*(i+1)%mod;
	int t=1;
	cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

感觉这题的转化非常神奇，场上怎么过了那么多，是我太菜了……

Easy Version 的容斥做法对 Hard Version 没有任何帮助。

容易将问题转化成，有一个 $n \times m$ 的网格图，给定 $k$ 个关键点 $(x_i, y_i)$，每次可以以一定的概率往上或往右走，往上走得分 $+ 1$，往右走得分 $+ 2$，每走到一个关键点得分 $\times 2$，求最终期望得分。

首先可以发现每条路径的概率相同，所以先求出总数再除路径数就是答案。考虑拆贡献。对于一条**恰好**经过了 $k$ 个关键点 $p_1, p_2, \ldots, p_k$ 的路径（认为 $(0, 0)$ 和 $(n, m)$ 也是关键点），$p_{i - 1} \to p_i$ 这一段贡献为 $2^{k - i} \times (2(r_{p_i} - r_{p_{i - 1}}) + b_{p_i} - b_{p_{i - 1}})$。考虑对于每个 $j \ge i$，将答案累加 $2^{k - j - 1} \times (2r_{p_j} + b_{p_j})$，最后的期望再加上 $2n + m$（这么做是因为我们把 $2^{k - i}$ 拆成了 $2^{k - i - 1} + 2^{k - i - 2} + \ldots + 2^0 + 1$）。

考虑 $2^{k - j - 1}$ 相当于 $p_j, p_{j + 1}, \ldots, p_{k - 1}$ 的子集数量，于是 $2^{k - j - 1}$ 可以看作是选一个点 $p_j$ 和若干个点 $s_1, s_2, \ldots, s_t$，表示路径依次经过了 $p_j, s_1, s_2, \ldots, s_t$（不要求恰好）。于是直接把所有点按字典序排序后 DP，设 $f_i$ 为先选若干个之后的点，然后钦定路径经过了点 $i$ 和那些点的方案数。有转移 $f_i = \sum\limits_{j = i + 1}^{k + 1} f_j \binom{x_j - x_i + y_j - y_i}{x_j - x_i}$。答案就是 $\sum\limits_{i = 1}^k f_i \times \binom{x_i + y_i}{x_i} \times (2x_i + y_i)$。

时间复杂度 $O(n + m + k^2)$。

[code](https://codeforces.com/problemset/submission/2034/294201528)

---

## 作者：Autre (赞：1)

首先对题意做如下转化：

将 ruby 记作 A，sapphire 记作 B，于是整个过程可以记作由 $n$ 个 A 和 $m$ 个 B 构成的序列；并且通过观察到这样的序列中以 A 开头和以 B 开头的序列数量之比恰好为 $n:m$，可以归纳得到所有合法的表示序列所代表的过程的概率相等。

转化题意为在网格图上有 $k$ 个关键点，横向边权值为 $1$，纵向边权值为 $2$；一条合法路径从 $(0,0)$ 出发，每次向右或向下走直到 $(n,m)$，设该路径中某条边**之前**经过的**关键点**数为 $c$，该边的贡献为 $2^c$ 乘边权，该路径的权值为路径上所有边贡献之和。要求所有合法路径的权值和。

考虑将 $2^c$ 拆贡献，注意到这是该边之前经过的关键点集合的子集数量。所以我们定义一个**方案**为一个条路径和其上的一个**关键点集合**，我们使一条路径上的某条边只在所有**只选了该边之前的关键点**的**方案**中被计边权的贡献即可，于是一个**方案**的权值就应为路径上**方案内最后一个关键点**到终点上所有边的边权和（若关键点集为空则为整个路径上的边权和）。

这样我们通过自选关键点，规避掉了直接 DP 中“两个关键点间不经过其它关键点的路径条数”的问题。

```C++
#include<iostream>
#include<cstring>

const int N = 2e5, K = 5e3, P = 998244353;
int cas, n, m, k, sm, x[K], y[K], f[K], fc[N*2+1], ifc[N*2+1];
long long inline calc(int x, int y) { return 1ll*fc[x+y]*ifc[x]%P*ifc[y]%P; }
int dfs(int i) {
	if (~f[i]) return f[i];
	f[i] = calc(x[i], y[i]);
	for (int j=0; j<k; j++)
		if (x[j] <= x[i] && y[j] <= y[i] && i != j)
			f[i] = (f[i]+dfs(j)*calc(x[i]-x[j], y[i]-y[j]))%P;
	return f[i];
}
int main() {
	*fc = ifc[N*2] = 1;
	for (int i=1; i<=N*2; i++) fc[i] = 1ll*fc[i-1]*i%P;
	for (int a=fc[N*2], b=P-2; b; b>>=1, a=1ll*a*a%P)
		if (b&1) ifc[N*2] = 1ll*ifc[N*2]*a%P;
	for (int i=N*2; i; i--) ifc[i-1] = 1ll*ifc[i]*i%P;
	for (std::cin >> cas; cas--; std::cout << sm << '\n') {
		std::cin >> n >> m >> k, memset(f, -1, k*4), sm = 0;
		for (int i=0; i<k; i++) std::cin >> x[i] >> y[i];
		for (int i=0; i<k; i++) sm = (sm+dfs(i)*
			(2ll*(n-x[i])+m-y[i])%P*calc(n-x[i], m-y[i]))%P;
		sm = (1ll*sm*ifc[n+m]%P*fc[n]%P*fc[m]+2*n+m)%P;
	}
}
```

---

