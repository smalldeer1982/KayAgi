# Star MST

## 题目描述

In this problem, we will consider complete undirected graphs consisting of $ n $ vertices with weighted edges. The weight of each edge is an integer from $ 1 $ to $ k $ .

An undirected graph is considered beautiful if the sum of weights of all edges incident to vertex $ 1 $ is equal to the weight of MST in the graph. MST is the minimum spanning tree — a tree consisting of $ n-1 $ edges of the graph, which connects all $ n $ vertices and has the minimum sum of weights among all such trees; the weight of MST is the sum of weights of all edges in it.

Calculate the number of complete beautiful graphs having exactly $ n $ vertices and the weights of edges from $ 1 $ to $ k $ . Since the answer might be large, print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3 2```

### 输出

```
5```

## 样例 #2

### 输入

```
4 4```

### 输出

```
571```

## 样例 #3

### 输入

```
6 9```

### 输出

```
310640163```

## 样例 #4

### 输入

```
42 13```

### 输出

```
136246935```

# 题解

## 作者：蒟蒻君HJT (赞：29)


更好的阅读体验：

https://www.cnblogs.com/hokarikanae/articles/16045118.html

第一次打 codeforces 自己做出 E 题，还是个 dp ，所以来写人生第一发题解。

## 一、题意：

有一个 $n$ 个点的无向完全图，边权 $e\in[1,k]$ ，已知该图的最小生成树的权值与所有与1号点相连的边的边权和相同，求有多少种构图方式，答案对   $998244353$ 取模，$n,k \leq 250$ 。

## 二、分析：

考虑一棵以 $1$ 号点为根的菊花图（ $1$ 号点度数为 $n-1$ ），根据题意，显然这是其中一棵最小生成树，设它的权值为 $t$ 。那么如果要满足**不存在更小的生成树**，有什么条件呢？

考虑两个点 $u$ ，$v$（ $u,v\neq1$ ），设 $u$ 到 $v$ 的无向边权值为 $x$ ，而 $1$ 到 $u$ 的边权值为 $y$ 。那么在以 $1$ 号点为根的菊花图中，如果去掉 $1$ 到 $u$ 的边，并加上 $u$ 到 $v$ 的边，也可以得到一棵生成树，而这颗生成树的权值为 $t-y+x$ 。根据题意 $t-y+x\geq t$ ，得出：$y\leq x$ 。**也就是说，除 $1$ 号点外任意点 $u$ 连出去的边的权值都必须 $\geq$ 边 $(u,1)$ 的权值，换句话说，离 $u$ 最近（可以是之一）的点必须是 $1$ 号点，容易发现这是充要条件。**

## 三、解题方法：

根据上面的分析，可以发现：

决定无向完全图的形态的是什么？ $\frac{n(n-1)}{2}$ 条边的边权；

限制边权的条件是什么？两端点 $u$ ，$v$ 到 $1$ 号点的距离；

除此之外，一条边的边权是否受到其他边的限制？不受到。

再结合本题较小的数据范围，一个简单的 dp 思路就呼之欲出了：

设 $dp_{i,j}$ 表示已经在图中加入了 $i$ 个点，这些点到 $1$ 号点的距离最大值为 $j$ **（且必须存在这个最大值）** 时，有多少种不同的构图方案。在这里，我们需要考虑选取点的不同方案，因此这 $i$ 个点的编号可以是任意的（当然 $1$ 号点必须包括在内），未必是 $1,2,3\cdots i$ 。

初始状态：$dp_{1,0}=1$ ，$dp_{1,i}=0$ $(i\in [1,k])$ 。这是因为只有 $1$ 号点时，我们什么都做不了，一条边也没有，边权最大值当然是 $0$ 了。

答案： $\sum _{i=1}^{k}dp_{n,i}$ 。

重点在于如何转移。笔者赛时在这里也卡了一会儿，因此会讲得细致一些。

对于 $i\geq2$ ，考虑一个状态 $dp_{i,j}$ ，我们枚举到 $1$ 距离为 $j$ 的点有多少个，在代码中笔者枚举的是到 $1$ 距离小于 $j$ 的点有多少个，即转移点在哪里。我们设到 $1$ 距离小于 $j$ 的点有 $t$ 个，那么应当转移到当前状态的是 $dp_{t,x},x\in[0,j-1]$ ，即可以转移过来的状态数为 $\sum_{x=0}^{j-1}dp_{t,x}$ 。转移的时候，我们先在剩余的 $n-t$ 个点中选择 $i-t$ 个点进行新加入，这个选择的方案数是 $C_{n-t}^{i-t}$ ；选好之后，我们还要连边，注意到所有点到 $1$ 号点的边在转移过程中都已经确定下来了，我们需要枚举的是新加入的这些点到除了 $1$ 号点之外的点的边。

这里有一个很关键的地方：对于还未加入的 $n-i$ 个点，已加入的点与它们相连的边会受到更加严格的限制，因为它们到 $1$ 号点的距离 $>j$ ，于是已加入的点与它们相连的边的边权也必须 $>j$ ，那么这些边我们就应该在加入剩下的 $n-i$ 个点的时候再分别考虑，到时候只需要考虑那个大于 $j$ 的某个限制就可以了，因为这一定是更严格的限制（其实这里就反映了一个动态规划的重要思想：消去后效性）。

回到 $dp_{i,j}$ 的转移过程来，当我们加入这 $i-t$ 个点时，应该只考虑这些点之间的连边以及这些点到前 $t$ 个点（除了 $1$ 号点）之间的连边。所有的这些边的限制均为边权 $\geq j$ ，因此，连边的总方案数为： $(k-j+1)^{(i+t-3)(i-t)/2}$  ，指数 $(i+t-3)(i-t)/2$ 就是这一次连边的总数，建议可以画一下图手玩一下，很容易明白的。

综上所述，转移方程为：

$dp_{i,j}=\sum_{t=1}^{i-1}(\sum_{x=0}^{j-1}dp_{t,x})$  $\cdot C_{n-t}^{i-t}$  $ \cdot (k-j+1)^{(i+t-3)(i-t)/2}$ ，其中 $i\in[2,n]$ , $j\in[1,k]$ 。

注意到 $\sum_{x=0}^{j-1}dp_{t,x}$ 可以用前缀和优化，组合数的系数不太大，可以直接递推预处理，幂次 $(k-j+1)^{(i+t-3)(i-t)/2}$ 可以用预处理分块快速幂（光速幂）优化，得到 $O(kn)$ 的空间复杂度和 $O(kn^2)$ 的时间复杂度；笔者比较懒，而且 codeforces 的机子比较快，可以接受 $O(kn^2 \log n)$ 的复杂度，因此直接在转移的过程中用了快速幂。

时间复杂度： $O(kn^2 \log n)$ ，空间复杂度： $O(kn)$ 。

## 四、代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long p=998244353,inv=499122177;
long long n,k,dp[255][255],C[255][255],sum[255][255];
long long qpow(long long x,long long y){
	long long r=1;
	while(y){
		if(y&1) r=r*x%p;
		x=x*x%p,y>>=1;
	}
	return r;
}//快速幂
int main(){
	scanf("%lld%lld",&n,&k);
	dp[1][0]=1;
	for(long long i=0;i<=k;++i) sum[1][i]=1;//初始化dp值
	for(long long i=0;i<=n;++i) C[i][0]=1;
	for(long long i=1;i<=n;++i){
		for(long long j=1;j<=i;++j){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
		}
	}//预处理组合数
	for(long long i=2;i<=n;++i){
		for(long long j=1;j<=k;++j){
			for(long long t=1;t<=i-1;++t){
				dp[i][j]=(dp[i][j]+
           C[n-t][i-t]*sum[t][j-1]%p*qpow(k-j+1,(i-2+t-1)*(i-t)/2)%p)%p;//状态转移方程
			}
			sum[i][j]=(sum[i][j-1]+dp[i][j])%p;//前缀和优化
		}
	}
	long long ans=0;
	for(long long i=1;i<=k;++i) ans=(ans+dp[n][i])%p;
	printf("%lld\n",ans);
	return 0;
}//切掉E了，拜拜！
```



---

## 作者：xiezheyuan (赞：9)

## 简要题意

求有多少个有标号 $n$ 个点的无向连通图（每条边的边权位于区间 $[1,m]$，注意原题面中 $m$ 为 $k$），使得以 $1$ 为花心的菊花图是这个无向图的一个最小生成树。

答案对 $998,244,353$ 取模。

$2\leq n\leq 250,1\leq m\leq 250$。

## 思路

提供一个无需组合数和题意转换的做法。

首先我们需要考虑怎样的树是一个图的最小生成树。假如对于树上每一对不相邻的点 $(x,y)$，原图上的边 $(x,y)$ 的边权比树上路径 $(x,y)$ 的每一条边的边权都要大，那么这就是一个最小生成树。考虑根据这个性质设计 dp 状态。

不妨考虑将原图除了 $1$ 的点重新标号，使得对于 $x<y$，有 $w(1,x)\leq w(1,y)$，其中 $w(a,b)$ 表示完全图上 $(a,b)$ 的权。这样我们就为 dp 钦定了一个合理的顺序。

设 $f(i,j)$ 表示考虑到第 $i$ 个点，$w(1,i)=j$ 的方案数，则不难列出（看起来正确的）转移方程：

$$
f(i,j)=(m-j+1)^{i-1}\cdot \sum_{k=1}^{j-1}f(i-1,k)
$$

其中 $(m-j+1)^{i-1}$ 表示需要满足 $\forall k\lt i, w(k,i)\geq j$。

然后你发现这样是不行的，原因是最后统计答案不方便，最后统计答案的时候，我们要把无标号转换为有标号，这时候直接乘 $(n-1)!$ 是不对的，举个最简单的例子，假如所有 $w(1,i)$ 都相等，这是一种方案，而不是 $(n-1)!$ 种。

你发现罪魁祸首是 $w(1,i)$ 的连续段，考虑将这玩意也设到状态里。

设 $f(i,j,k)$ 表示考虑到第 $i$ 个点，$w(1,i)=j$，之前有 $k-1$ 个 $t$，使得 $w(1,t)=j$ 的方案数。

则先考虑转移 $f(i,j,1)$：

$$
f(i,j,1)=(m-j+1)^{i-1}\cdot \sum_{s=1}^{j-1}\sum_{t=1}^{i-1} \frac{f(i-1,s,t)}{t!}
$$

然后考虑转移 $f(i,j,k)$，其中 $k\geq 2$：

$$
f(i,j,k)=(m-j+1)^{i-1}\cdot f(i-1,j,k-1)
$$

最后答案就是：

$$
(n-1)!\cdot \sum_{s=1}^{m}\sum_{t=1}^{n-1}\frac{f(n-1,s,t)}{t!}
$$

时间复杂度为 $O(n^4\log n)$，无法通过本题，考虑优化。

不妨转换状态，设 $F(i,j,k)=f(i,j,k)\div k!$，你发现转移突然就变得规整了许多：

$$
F(i,j,k)=\begin{cases}
\sum_{s=1}^{j-1}\sum_{t=1}^{i-1}F(s,t)& k=1\\
\frac{1}{k}F(i-1,j,k-1)& \text{otherwise}
\end{cases}
$$

考虑如何优化转移，记：

$$
G(i,j)=\sum_{s=1}^{j}\sum_{t=1}^{i}F(i,s,t)
$$

$G$ 可以在转移的时候计算，那么转移方程就变成了：

$$
F(i,j,k)=\begin{cases}
G(i-1,j-1)& k=1\\
\frac{1}{k}F(i-1,j,k-1)& \text{otherwise}
\end{cases}
$$

答案就是：

$$
(n-1)!\cdot \sum_{s=1}^{m}\sum_{t=1}^{n-1}F(n-1,s,t)
$$

时间复杂度 $O(n^3\log n)$，精细的实现可以做到 $O(n^3)$。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

const int N = 255, mod = 998244353;
int n, m, f[N][N][N], g[N][N], fact[N], inv[N];

int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

int fastpow(int x, int y){
    int res = 1;
    while(y){
        if(y & 1) res = Mul(res, x);
        x = Mul(x, x);
        y >>= 1;
    }
    return res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    fact[0] = fact[1] = inv[0] = inv[1] = 1;
    for(int i=2;i<=n;i++){
        fact[i] = Mul(fact[i - 1], i);
        inv[i] = Mul(inv[mod % i], mod - mod / i);
    }
    for(int i=1;i<=m;i++) f[1][i][1] = 1, g[1][i] = i;
    for(int i=2;i<n;i++){
        for(int j=1;j<=m;j++){
            f[i][j][1] = g[i - 1][j - 1];
            f[i][j][1] = Mul(f[i][j][1], fastpow(m - j + 1, i - 1));
            g[i][j] = Add(g[i][j - 1], f[i][j][1]);
            for(int k=2;k<=i;k++){
                f[i][j][k] = Add(f[i][j][k], f[i - 1][j][k - 1]);
                f[i][j][k] = Mul(f[i][j][k], Mul(fastpow(m - j + 1, i - 1), inv[k]));
                g[i][j] = Add(g[i][j], f[i][j][k]);
            }
        }
    }
    int ans = 0;
    for(int j=1;j<=m;j++){
        for(int k=1;k<=(n - 1);k++) ans = Add(ans, f[n - 1][j][k]);
    }
    ans = Mul(ans, fact[n - 1]);
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Troubadour (赞：5)

这道题感觉找到思路的难度不是特别大，但是从思路引向正解这条道路可真是崎岖坎坷。

### 思路

首先我们固定 $1$ 号点，根据题意，这个图的 MST 是以 $1$ 为根的一个菊花图，记 $d(u,v)$ 为 $(u,v)$ 这条边的权值，则对于任意 $(u,v)(u\neq 1,v\neq 1)$，都存在 $d(u,v)\ge \max\left\{d(1,u),d(1,v)\right\}$。

简单证明一下，如果不是这样，当 $d(u,v)\le d(1,u)$，在 MST 上把 $(1,u)$，这条边换成 $(u,v)$ 会更优，那么我们最开始得到的这个菊花就不是 MST 了。

### 解法

我们考虑一个集合 $a=\left\{u|d(1,u)=x\right\}$，那么我们可以得到，首先 $a$ 集合内的点两两相连的边的权值一定都是 $\ge x$ 的；然后考虑合并答案，这个集合向所有满足 $d(1,v)<x$ 的 $v$ 点连边，这些边权也一定 $\ge x$。

所以，我们可以设 $f_{r,i}$ 表示已经考虑了 $r$ 个点，这些点中到 $1$ 号点边权最大值 $\le i$ 的方案数。每次枚举一个端点 $l$，这个大小在 $[l,r]$ 之间的集合内所有点到 $1$ 号点距离为 $i$，考虑这一段的选择方案、内部连边方案、向前面的点连边方案，则有如下转移：
$$
f_{r,i}=f_{r,i-1}+\sum_{1\le l\le r}\binom{n-l}{r-l+1}\times f_{l-1,i-1}\times(k-i+1)^{\frac{(r - l + 1)\times(r - l)}{2}}\times(k-i+1)^{(r - l + 1)\times(l - 1)}\bmod 998244353
$$

稍微解释一下：

$\binom{n-l}{r-l+1}$ 表示目前已经考虑过了 $l$ 个点，在剩下的 $n-l$ 个点中选取 $r-l+1$ 个的方案数。

$(k-i+1)^{\frac{(r - l + 1)\times(r - l)}{2}}$ 表示这个有 $r-l+1$ 个点的集合内部可以连 $\frac{(r - l + 1)\times(r - l)}{2}$ 条边，每一条边可以选择长度在 $[i,k]$ 以内的方案数。

$(k-i+1)^{(r - l + 1)\times(l - 1)}$ 表示这个有 $r-l+1$ 个点的集合向前面 $l-1$ 个点连 $(r - l + 1)\times(l - 1)$ 边，每一条边可以选择长度在 $[i,k]$ 以内的方案数。

乘起来即可。

需要注意的是，当 $i=1$ 时，$l$ 必须等于 $1$。

最后，$f_{n-1,m}$ 即为答案。

### Code（赛时代码）：
```cpp
/*
	Copyright (C) 2022  Troubadour_Ggmz

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include<bits/stdc++.h>
#define int long long
namespace GGMZ
{
	const int N = 255;
	const int mod = 998244353;
	int f[N][N], n, m, ans;
	int inv[N], fac[N], invfac[N];
	inline int binom(int n, int m)
	{
		return fac[n] * invfac[m] % mod*invfac[n - m] % mod;
	}
	inline int pow(int a, int b)
	{
		int res = 1;
		while (b)
		{
			if (b & 1)res = res * a%mod, b--;
			else a = a * a%mod, b >>= 1;
		}
		return res;
	}
	void work()
	{
		std::cin >> n >> m;
		fac[1] = fac[0] = inv[1] = inv[0] = invfac[1] = invfac[0] = 1;
		for (int i = 2;i <= 250;i++)
		{
			fac[i] = fac[i - 1] * i%mod;
			inv[i] = (mod - mod / i)*inv[mod%i] % mod;
			invfac[i] = invfac[i - 1] * inv[i] % mod;
		}
		for (int i = 0;i <= m;i++)
		{
			f[0][i] = 1;
		}
		for (int i = 1;i <= m;i++)
		{
			for (int j = 1;j < n;j++)
			{
				f[j][i] = f[j][i - 1];
			}
			for (int l = 1;l < (i == 1 ? 2 : n);l++)
			{
				for (int r = l;r < n;r++)
				{
					f[r][i] += f[l - 1][i - 1] * binom(n - l, r - l + 1) % mod*pow(m - i + 1, (r - l + 1)*(r - l) / 2) % mod*pow(m - i + 1, (r - l + 1)*(l - 1)) % mod;
					f[r][i] %= mod;
				}
			}
		}
		std::cout << f[n - 1][m];
	}
}
#undef int
int main()
{
	return GGMZ::work(), 0;
}
```


---

## 作者：AIskeleton (赞：5)

> [E. Star MST](https://codeforces.com/contest/1657/problem/E)
假设有一个 $n$ 个点的**无向连通图**，每条边的边权均在 $\left[1,k\right]$ 之间。
满足其 **最小生成树的边权和** 和 **与节点 1 相连的边的权值和** 相等，求方案数。

将题意转化一下： 
对于每条边 $x \rightarrow y(x \ne 1,y \ne 1)$，满足其边权大于 $1 \rightarrow x,1 \rightarrow y$ 的边权。

很明显用 DP。
假设 $f_{i,j}$ 表示给顶点 1 的 $j$ 条边分配了权值，且其中最大权值为 $i$ 时的方案数。

状态转移方程：
$$f_{i,k} = \sum \limits_{j<k} f_{i-1,j} \cdot C_{n-j-1,k-j} \cdot pow(K+1-i,j \cdot (k-j) + \dfrac{(k-j) \cdot (k-j-1)}{2})$$

其中 $C_{n-j-1,k-j}$ 是因为在 $n-j-1$ 条边中选出 $k-j$ 条边，将其权值修改为 $i$。

对于 $f_{i-1,j}$，选择了 $j$ 个点向点 1 连边，称之为点集 $A$，在转移时选择了另外 $k-j$ 条边，而 **点集 $A$ 连向点集 $B$ 的边** 和 **点集 $B$ 内部每两点之间的边** 的边权都应 $\ge i$，分别对应 $j\cdot(k-j)$ 和 $\dfrac{(k-j)\cdot(k-j-1)}{2}$，而因为边权应 $\ge i$，因此有 $K+1-i$ 种取值。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int R(){
    int x=0,f=0; char ch=getchar();
    while(!isdigit(ch)) f|=(ch==45),ch=getchar();
    while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return f?-x:x;
}const int N=601,mod=998244353;
int ksm(int x,int n){int s=1;while(n){if(n&1)s=(s*x)%mod;x=(x*x)%mod;n>>=1;}return s;}
int n,k,c[N][N],f[N][N];
signed main(){
    n=R()-1;k=R();f[k+1][0]=1;
    for(int i=0;i<=300;i++){
	c[i][i]=c[i][0]=1;
	for(int j=1;j<i;j++)
	    c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }for(int i=k;i;i--)
	for(int j=0;j<=n;j++)
	    for(int k=0;k+j<=n;k++)
		f[i][j+k]=(f[i][j+k]+f[i+1][j]*ksm(i,j*k+k*(k-1)/2)%mod*c[n-j][k])%mod;
    cout<<f[1][n]<<endl;return 0;
}
```


---

## 作者：I_am_Accepted (赞：4)

vp 自己写出来了，记录一下。

为方便，我们考虑将题面中的「最小生成树」改为「最大生成树」，显然这样方案数（即答案）是不变的。

由题可知，**以 $1$ 为中心的菊花图是这个完全图的最大生成树。** 进一步得到：
$$
\forall 2\le i,j\le n,w(i,j)\le\min(w(1,i),w(1,j))
$$
其中 $w(i,j)$ 表示两点间边权。

我们记
$$
A_i=w(1,i)\quad(2\le i\le n,1\le A_i\le k)
$$
则答案为
$$
\sum_{\{A\}}\prod_{2\le i<j\le n}\min(A_i,A_j)
$$
其中最外层的 $\sum$ 代表枚举共 $k^{n-1}$ 种序列 $\{A\}$。

发现这样好像不太好搞掉最外层的 $\sum$。

由于 $\{A\}$ 中的下标并没有顺序关系，我们只关心每种值的个数，所以我们把 $\{A\}$ 放入**桶**，记为 $B_1,B_2,\dots,B_k$（$B_i$ 表示 $\{A\}$ 中值为 $i$ 的元素数量）。

则答案改写为
$$
\sum_{B_1+\dots+B_k=n-1}\prod_{i=1}^k\binom{n-1-\sum_{j=i+1}^kB_j}{B_i}i^{B_i(B_i-1)/2+\sum_{j=i+1}^kB_j}
$$
（好好思考一下这个公式的具体含义）

这时候我们就可以 DP 了。

$dp(i,j)$ 表示我们已经计算好了 $B_i,B_{i+1},\dots,B_k$，且 $\sum_{x=i}^kB_x=j$ 的贡献。

根据上面答案的柿子，我们得到 $dp$ 的递推式
$$
dp(i,j)=\sum_{k=0}^j\binom{(n-1)-(j-k)}{k}dp(i+1,j-k)i^{k(k-1)/2+k(j-k)}
$$
$$
dp(k+1,0)=1
$$
答案就是
$$
dp(1,n-1)
$$
时间 $O(N^2K\log N)$。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ll long long
const ll mod=998244353;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define N 256
int n,K;
ll dp[N][N],f[N],ivf[N];
ll C(int x,int y){return f[x]*ivf[y]%mod*ivf[x-y]%mod;}
int main(){
	scanf("%d%d",&n,&K); 
	f[0]=1; For(i,1,n) f[i]=f[i-1]*i%mod;
	ivf[n]=pw(f[n],mod-2); Rof(i,n,1) ivf[i-1]=ivf[i]*i%mod;
	dp[K+1][0]=1;
	Rof(i,K,1)
		For(j,0,n-1)
			For(k,0,j)
				(dp[i][j]+=dp[i+1][j-k]*C(n-1-(j-k),k)%mod*pw(i,k*(k-1)/2+k*(j-k)))%=mod; 
	printf("%lld\n",dp[1][n-1]);
return 0;}
```

---

## 作者：GIFBMP (赞：1)

首先我们思考一下这幅图有什么性质。我们可以发现，$\forall 2\le x<y\le n$，若边 $1\rightarrow x$ 的权值为 $a$，边 $1\rightarrow y$ 的权值为 $b$，那么边 $x\rightarrow y$ 的权值必须大于等于 $\max(a,b)$。

于是我们可以想到 DP，设 $f_{i,j}$ 表示加入了 $i$ 个点（包括点 $1$），$1$ 号点到这些点的边权的最大值为 $j$ 时构图的方案数。那么有初值 $f_{1,0}=1$。

对于转移，我们可以枚举有多少个点，使得 $1$ 到这些点的边权**小于** $j$，那么 $1$ 到剩下的点的边权均等于 $j$。设这个点数为 $p$，那么加入剩下的点就有 $C_{n-p}^{i-p}$ 种方案。

接下来我们考虑新加入的边，可以得出它们的权值均要大于等于 $j$，因此每条边都有 $k-j+1$ 种取值。由于这些边要么是新加入的 $i-p$ 个点之间的两两连边，要么是这些点到前 $p-1$ 个点（不包括点 $1$）的连边，因此边的总数为 $\dfrac{(i-p)(i-p-1)}{2}+(i-p)(p-1)=\dfrac{(i+p-3)(i-p)}{2}$。

那么可以得出：

$$f_{i,j}=\sum_{p=1}^{i-1} C_{n-p}^{i-p}\times(k-j+1)^{\frac{(i+p-3)(i-p)}{2}}\sum_{l=0}^{j-1}f_{p,l}$$

对于后面的部分用前缀和优化即可。答案即为 $\sum_{i=1}^kf_{n,i}$。

时间复杂度 $\Theta(kn^2\log n)$。

Code:

```cpp
#include <cstdio>
using namespace std ;
typedef long long ll ;
const int MAXN = 510 , mod = 998244353 ;
int n , m ; 
ll c[MAXN][MAXN] , f[MAXN][MAXN] , s[MAXN][MAXN] , ans ;
ll qpow (ll x , ll p = mod - 2) {
	ll ret = 1 ;
	for (; p ; p >>= 1 , x = x * x % mod)
		if (p & 1) ret = ret * x % mod ;
	return ret ;
}
int main () {
	scanf ("%d%d" , &n , &m) ;
	for (int i = 0 ; i <= n ; i++) c[i][0] = 1 ;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= i ; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod ;
	f[1][0] = 1 ;
	for (int i = 0 ; i <= m ; i++) s[1][i] = 1 ;
	for (int i = 2 ; i <= n ; i++)
		for (int j = 1 ; j <= m ; j++) {
			for (int k = 1 ; k < i ; k++)
				f[i][j] = (f[i][j] + c[n - k][i - k] * s[k][j - 1] % mod * qpow (m - j + 1 , (ll)(i + k - 3) * (i - k) / 2) % mod) % mod ;
			s[i][j] = (s[i][j - 1] + f[i][j]) % mod ;
		}
	for (int i = 1 ; i <= m ; i++) ans = (ans + f[n][i]) % mod ;
	printf ("%lld\n" , ans) ;
	return 0 ;
}
```

---

## 作者：GaryH (赞：0)

## CF1657E 题解
~~`whk` 人回来混一个社贡分~~

首先注意到图是完全图，故若点 $1$ 的邻边权值和与图的 `MST` 的权值和相等，则点 $1$ 的邻边就是一棵 `MST`。

记这棵 `MST` 叫做 $T$，则考虑 $T$ 的性质：若有一条边 $w(u,v)$ 不在 $T$ 上，则必然有：

$u,v$ 在 $T$ 中的唯一路径上的每一条边 $w(x,y)$，都满足 $w(x,y)$ 权值不大于 $w(u,v)$ 的权值。

也就是说，若我们记 $C(T)$ 为：所有不在 $T$ 中的边的不同方案数，其中点 $1$ 的邻边形成的 `MST` 为 $T$，

那么最终答案就是 $\sum\limits_{T}C(T)$，而我们考虑用 `DP` 来解决这个计算。

考虑 $f(i,j)$ 代表，当 $1$ 号点已经连好了边权最小的 $i$ 条边，这些边里边权最大的边的权值是 $j$，

则此时边集 $S$ 中有多少种不同的合法边权方案，其中若边 $w(u,v)\in S$，当且仅当 $u,v$ 都和 $1$ 有边相连。

考虑转移，即枚举 $l$ 代表新连了 $l$ 条边，这些边都有一个端点是 $1$ 号点，且权值都是 $j+1$，

转移时乘上一些组合数和一些系数即可，这些都是细节，就不说了。

[代码](https://codeforces.com/contest/1657/submission/150565847)不难写，但要注意不能漏掉乘上的组合数，不然就会和我一样调`1.5h`。

---

