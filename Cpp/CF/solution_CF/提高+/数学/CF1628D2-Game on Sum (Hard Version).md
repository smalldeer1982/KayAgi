# Game on Sum (Hard Version)

## 题目描述

This is the hard version of the problem. The difference is the constraints on $ n $ , $ m $ and $ t $ . You can make hacks only if all versions of the problem are solved.

Alice and Bob are given the numbers $ n $ , $ m $ and $ k $ , and play a game as follows:

The game has a score that Alice tries to maximize, and Bob tries to minimize. The score is initially $ 0 $ . The game consists of $ n $ turns. Each turn, Alice picks a real number from $ 0 $ to $ k $ (inclusive) which Bob either adds to or subtracts from the score of the game. But throughout the game, Bob has to choose to add at least $ m $ out of the $ n $ turns.

Bob gets to know which number Alice picked before deciding whether to add or subtract the number from the score, and Alice gets to know whether Bob added or subtracted the number for the previous turn before picking the number for the current turn (except on the first turn since there was no previous turn).

If Alice and Bob play optimally, what will the final score of the game be?

## 说明/提示

In the first test case, the entire game has $ 3 $ turns, and since $ m = 3 $ , Bob has to add in each of them. Therefore Alice should pick the biggest number she can, which is $ k = 2 $ , every turn.

In the third test case, Alice has a strategy to guarantee a score of $ \frac{75}{8} \equiv 375000012 \pmod{10^9 + 7} $ .

In the fourth test case, Alice has a strategy to guarantee a score of $ \frac{45}{2} \equiv 500000026 \pmod{10^9 + 7} $ .

## 样例 #1

### 输入

```
7
3 3 2
2 1 10
6 3 10
6 4 10
100 1 1
4 4 0
69 4 20```

### 输出

```
6
5
375000012
500000026
958557139
0
49735962```

# 题解

## 作者：Alex_Wei (赞：16)

对于 Easy version，$n,m \leq 2\times 10 ^ 3$。由于我们 **只关心游戏进行的轮数以及 Bob 使用 `add` 的次数**，考虑设计 DP：设 $f_{i, j}$ 表示经过 $i$ 轮后 Bob 用了 $j$ 次 `add`，Alice 所能达到的最大分数，但是不方便转移，因为两人绝顶聪明使得当前决策 **仅** 基于接下来的决策。

综上，可以发现一般博弈论的 DP 题都是 **从后往前** DP，即从确定的终止状态向初始状态 DP，因为 **绝顶聪明** 这一条件使得双方都能预测到他们当前的行为对后续局面的影响，可以说只有 **后效性** 而没有 **前效性**：若 $i, j$ 确定，则两人之前的决策对当前决策无影响。

因此，设 $f_{i, j}$ 表示游戏还剩 $i$ 轮，Bob 还需使用 $j$ 次 `add` 时，Alice 还能获得的最大分数（另一种理解方法是当 $n = i, m = j$ 时的答案）。转移即考虑 Alice 选择的数 $x\in [0, k]$ 以及 Bob 选择加还是减（外层取 $\min$），有 $f_{i, j} = \min(f_{i - 1, j - 1} + x, f_{i - 1, j} - x)$。由于 Alice 需要让分值最大，所以当 $x = \dfrac {f_{i - 1, j - 1} - f_{i - 1, j}} 2$ 时，$f_{i, j}$ 取到最大值 $\dfrac{f_{i - 1, j - 1} + f_{i - 1, j}}2$，这就是转移方程。

边界值：$f_{i, 0} = 0\ (0\leq i\leq n)$，以及 $f_{i, i} = i\times k\ (0\leq i\leq m)$，转移仅在 $1\leq j < i \leq n, j\leq m$ 之间进行。时间复杂度 $nm$，可以通过 Easy version。[代码](https://codeforces.com/contest/1628/submission/143660616)。

对于 Hard version，考虑每个 $f_{i, i}$ 对答案的贡献：从 $f_{i, i}\to f_{n, m}$，一共进行了 $n - i$ 次除以 $2$，同时，它被计算到的次数相当于 $(i + 1, i)$ 走到 $(n, m)$，每次向 $x + 1, y+ 1$ 或 $x + 1, y$，即右或右上方向走的路径数量。不是 $(i, i)$ 的原因是 $f_{i, i}$ 无法转移到 $f_{i + 1, i + 1}$，它是边界值，转移仅在 $j < i$ 时进行。在 $n - i - 1$ 步中选 $m - i$ 步进行纵坐标加 $1$，方案数为 $\dbinom{n - i - 1}{m - i}$。综上，答案为：
$$
k\sum_{i = 1} ^ m \dfrac{i\times \binom {n - i - 1}{m - i}}{2 ^ {n - i}}
$$
 注意特判 $n = m$ 的情况，时间复杂度线性。[代码](https://codeforces.com/contest/1628/submission/143665114)。

---

## 作者：周子衡 (赞：11)

可以发现 $k$ 实际上和整个博弈的结构关系不大。方便起见，不妨设 $F(n,m)$ 表示 $k=1$ 时最后的得分，那么答案即为 $k\times F(n,m)$。

考虑 $F(n,m)$ 的计算。一些边界条件：$F(n,0)=0$，$F(n,n)=n$（分别对应 Bob 可以选择全减、必须选择全加的情形）。转移的核心方程式：

$$
F(n,m)=\max_{0\leq d\leq 1}\{\min\{F(n-1,m-1)+d,F(n-1,m)-d\}\} (0 < m < n)
$$

其中外层的 $\max$ 表示 Alice 的决策，内层的 $\min$ 表示 Bob 的决策。

我们来进一步简化这个方程式。显见 $F(n-1,m-1)\leq F(n-1,m)$。简单讨论一下可以得到：若 $F(n-1,m) - F(n-1,m-1) \leq 2$ 那么 $F(n,m)=\dfrac{F(n-1,m-1)+F(n-1,m)}{2}$，否则 $F(n,m)=F(n-1,m-1)+1$。接下来我们将归纳地证明：对任意 $0\leq m < n$，$F(n,m+1)-F(n,m)\leq 2$。

--------------

**证明：** 对 $n$ 采取归纳法。$n=1$ 时必有 $m=0$，此时 $F(n,m+1)=1$，$F(n,m)=0$，符合题意。

考虑某个 $n\geq 2$，设命题对 $n-1$ 成立。此时对 $0 < m < n$ 有 $F(n,m)=\dfrac{F(n-1,m-1)+F(n-1,m)}{2}$。对 $0 < m < n-1$，我们有

$$
F(n,m+1)-F(n,m)=\dfrac{F(n-1,m+1)+F(n-1,m)}{2}-\dfrac{F(n-1,m)+F(n-1,m-1)}{2}
$$
$$
=\dfrac{F(n-1,m+1)-F(n-1,m-1)}{2}=\dfrac{F(n-1,m+1)-F(n-1,m)}{2}-\dfrac{F(n-1,m)-F(n-1,m-1)}{2}
$$
$$
\leq \dfrac{2}{2}+\dfrac{2}{2}=2
$$

接下来考虑 $m=0$ 或 $m=n-1$ 的边界情况。易得

$$
F(n,1)=\dfrac{1}{2^{n-1}}
$$

$$
F(n,n-1)=n-2+\dfrac{1}{2^{n-1}}
$$

证明也可归纳证得，此处不赘述。此时可以看出 $m=0$ 与 $m=n-1$ 的情形都是符合条件的，故证毕。

------------------

考虑答案的计算。可以形象地看成一个三角形数表：

![](https://cdn.luogu.com.cn/upload/image_hosting/5m8gfbeu.png)

其中左右两条边已经填好，中间每个数等于肩上两个数的平均值。那么考虑右边某个位置 $(i,i)$ 对 $F(n,m)$ 的贡献次数。每次贡献相当于一条从 $(i,i)$ 到达 $(n,m)$ 且不经过 $(i+1,i+1)$ 的路径（等价于从 $(i+1,i)$ 到 $(n,m)$ 的路径），而每次贡献时带来的值皆为 $\dfrac{i}{2^{n-i}}$。故得

$$
F(n,m)=\sum_{i}\binom{n-i-1}{m-i}\dfrac{i}{2^{n-i}}(0 < m < n)
$$

边界情况特殊处理即可。时间复杂度 $O(n)$。

```cpp
#include<cstdio>

using namespace std;

const long long MOD=1e9+7,INV2=(MOD+1)/2;
int add(int x,int y){return x+y>=MOD?x+y-MOD:x+y;}
int sub(int x,int y){return x>=y?x-y:x+MOD-y;}

long long fast_pow(long long b,long long p)
{
	long long ans=1;while(p){if(p&1)ans=ans*b%MOD;b=b*b%MOD;p>>=1;}
	return ans;
}
long long INV(long long x){return fast_pow(x,MOD-2);}


long long fac[3000000],invf[3000000];
void init_fac(int n)
{
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%MOD;
	invf[n]=INV(fac[n]);for(int i=n-1;i>=0;i--)invf[i]=invf[i+1]*(i+1)%MOD;
}
long long C(int n,int m)
{
	return fac[n]*invf[m]%MOD*invf[n-m]%MOD;
}
int main()
{
	int T=0;scanf("%d",&T);init_fac(1000000);
	while(T--)
	{
		int n=0,m=0;long long k=0;scanf("%d%d%lld",&n,&m,&k);
		long long ans=0;if(m==n)ans=n;else if(m==0)ans=0;
		else
		{
			for(int i=1;i<=m;i++)ans=add(ans,(long long)i*C(n-i-1,m-i)%MOD*fast_pow(INV2,n-i)%MOD);
		}
		printf("%lld\n",ans*k%MOD);
		
	}
}
```

---

## 作者：DaiRuiChen007 (赞：8)

# CF1628D2 - Game on Sum (Hard Version) 题解

upd 2022.01.28，修复了几处笔误，感谢 @wzy2021 大佬的指正

## 题目大意

[题目链接](https://codeforces.com/problemset/problem/1628/D2)

Alice 和 Bob 正在玩一个游戏，游戏分为 $n$ 个回合，Alice 和 Bob 要轮流对一个数 $x$ 进行操作，已知这个数初始值是 $0$。

具体每个回合的行动规则如下：

1. Alice 选择一个在区间 $[0,k]$ 之间的实数 $t$。
2. Bob 可以选择让 $x$ 变成 $x+t$ 或者 $x-t$，但是 Bob 在 $n$ 个回合之内至少选择 $m$ 次让 $x$ 变成 $x+t$。

Alice想让最终的 $x$ 最大，Bob 想让最终的 $x$ 最小。

已知双方均采用最优策略，求最终的 $x$ 值（对 $10^9+7$ 取模）。

数据范围保证：$1\le m\le n\le 10^6,k\le10^9+7$。

## 思路分析

约定：用$t_i$ 表示第 $i$ 轮的 $t$ 值。

从特殊到一般，首先考虑比较简单的情况：$n=2,m=1$。

对于第一轮的情况，如果 Alice 选择的 $t_1$ 比较小那么 Bob 的最优策略是加上 $t_1$，反之则是减去 $t_1$。

- 对于第一种情况，Bob 第二轮一定会减去 $t_2$，所以 Alice 一定会选 $0$，最终结果是 $t_1$。
- 对于第二种情况，Bob 第二轮只能会加上 $t_2$，所以 Alice 一定会选 $k$，最终结果是 $k-t_1$。

所以对于这种情况，Bob 的最优策略的结果应该是 $\max(t_1,k-t_1)$。

所以答案应该是一次函数图像 $y=x$ 和一次函数图像 $y=k-x$ 的交点，也就是 $\dfrac{k}{2}$。

接下来进行推广，考虑用 $dp[i][j]$ 表示 $n=i,m=j$ 时的答案。

不难的出 dp 的边界条件：
$$
\begin{cases}
dp[i][0]&=0\\
dp[i][i]&=i\times k
\end{cases}
$$
接下来考虑状态转移方程，对于每种情况 Bob 只可能选择加上或减去，所以对于 Alice 来说，最优的 $t_i$ 应该是使得 $\min(dp[i-1][j-1]+t_i,dp[i-1][j]-t_i)$ 最大的 $t_i$。

所以我们可以得出状态转移方程：
$$
dp[i][j]=\max_{x\in \mathbb{R}}^{0\le x\le k}\left\{\min(dp[i-1][j-1]+x,dp[i-1][j]-x)\right\}
$$
类似刚才的特殊情况，$dp[i][j]$ 的值应该是一次函数图像 $y=dp[i-1][j-1]+x$ 和一次函数图像 $y=dp[i-1][j]-x$ 的交点，也就是 $\dfrac{dp[i-1][j-1]+dp[i-1][j]}{2}$。

所以我们得到了最终的状态转移方程：
$$
dp[i][j]=
\begin{cases}
0 &j=0\\
i\times k &j=i\\
\dfrac{dp[i-1][j-1]+dp[i-1][j]}{2} &otherwise
\end{cases}
$$
由于存在多组数据，所以这样的算法时间复杂度是 $\Theta(nm)$ 每次询问的，会 TLE。

所以考虑一下优化，发现状态转移方程里和题目相关的只有 $k$，如果对于数组 $dp$ 里的每一个数都 $\div k$ 那么转移方程基本不变，只需要令 $dp[i][i]=i$ 即可，输出答案时把 $dp[n][m]\times k$ 即可。

这样的时间复杂度是 $\Theta(nm)$ 预处理 $\Theta(1)$ 查询的，还是会 TLE，继续考虑优化。

这种情况的优化只能从 DP 的状态转移方程入手。

首先排除 $\div2$ 的条件，可以观察到每个 $dp[i][j]$ 只能够表示成 $dp[k][k]$ 处转移而来。

画出网格图，发现整个 $dp$ 数组里值 $>0$ 的是一个下三角的形状，所以对答案有贡献的只有 $dp[1][1]\sim dp[m][m]$。

所以答案可以写成：
$$
ans
=k\sum_{i=1}^m{\dfrac{f(i)\times dp[i][i] }{2^{n-i}}}
=k\sum_{i=1}^m{i\times f(i) }
$$
其中 $f(i)$ 是一个关于 $n,m,i$ 的多项式，表示统计 $dp[i][i]$ 对 $dp[n][m]$ 的贡献。

手动模拟之后可以得到 $f(i)$ 等价于在每次只能向下或右下走一步的情况下，从 $(i,i)$ 到 $(n,m)$ 的方案总数。

所以 $f(i)=\operatorname{C}_{n-i-1}^{m-i}$。

然后再把 $\div2$ 的条件考虑进来，得到最终的 $f(i)=\dfrac{\operatorname{C}_{n-i-1}^{m-i}}{2^{n-i}}$。

所以最终的答案是 $ans=k\sum_{i=1}^m\dfrac{i\times\operatorname{C}_{n-i-1}^{m-i}}{2^{n-i}}$。

运用这个公式，可以将时间复杂度优化到 $\Theta(n)$ 预处理，$\Theta(m)$ 回答。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INV=5e8+4,MOD=1e9+7,MAXN=1e6+1;
//INV(5e8+4)是2在模1e9+7意义下的乘法逆元，在此意义下*INV就等价于/2 
int fac[MAXN],inv[MAXN];
//fac[i]表示i!模1e9+7的值，inv[i]表示fac[i]在模1e9+7意义下的乘法逆元 
inline int ksm(int a,int b) {
	//快速幂，表示a^b模1e9+7的值 
	int ans=1;
	while(b) {
		if(b&1) ans=ans*a%MOD;
		a=a*a%MOD;
		b=b>>1;
	}
	return ans;
}
inline int C(int m,int n) {
	if(n==m||n==0) return 1; //特判两种情况 
	return fac[m]*inv[n]%MOD*inv[m-n]%MOD; //用组合数的公式计算 
}
inline void solve() {
	int n,m,k,ans=0;
	scanf("%lld%lld%lld",&n,&m,&k); 
	if(n==m) {
		printf("%lld\n",n*k%MOD);
		return ;
	} else {
		for(register int i=1;i<=m;++i) {
			//按题解式子算 
			ans=(ans+ksm(INV,n-i)*i%MOD*C(n-i-1,m-i)%MOD)%MOD;
		}
		printf("%lld\n",ans*k%MOD);	//输出时把答案*k 
	}
	return ;
}
signed main() {
	fac[0]=1;
	for(register int i=1;i<MAXN;++i) {
		fac[i]=fac[i-1]*i%MOD;
		inv[i]=ksm(fac[i],MOD-2);
		//用费马小定理快速处理fac[i]的乘法逆元 
	}
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：I_am_Accepted (赞：4)

[Easy Version 解法](https://www.luogu.com.cn/blog/101868/solution-cf1628d1)

### Analysis

$m\le n\le 10^6$ 这意味着线性。

发现 Dp 的状态数就崩了……那么只能数学了。

我们考虑 $f(i,i)=ik\quad(1\le i\le m)$ 对 $f(n,m)$ 的贡献，累加起来就是答案。

发现 $f(x,y)$ 对 $f(x+1,y)$ 和 $f(x+1,y+1)$ 分别有 $\frac{1}{2}$ 倍的贡献（由 Dp 转移）（无意义和 $x=y$ 的状态不被贡献），所以 $f(i,i)$ 的贡献为以下图 $(i,i)\to(n,m)$ 的路径数量再乘上路径上“半衰”的 $2^{-(n-i)}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/t21w8ruv.png)

由组合计数可知，路径共 $\binom{n-i-1}{m-i}$ 条。

所以最终答案为：

$$\sum\limits_{i=1}^m\dfrac{ik}{2^{n-i}}\binom{n-i-1}{m-i}$$

时间 $O((n+m)+Tm)$，分别是 阶乘及其逆元的预处理 和 求和 的时间。

### Detail

$n=m$ 时要特判。

### Code

[Link](https://codeforces.com/contest/1628/submission/143969941)

---

## 作者：vectorwyx (赞：4)

这个模型和 [P7137](https://www.luogu.com.cn/problem/P7137) 简直一模一样，我也写了[题解](https://www.luogu.com.cn/blog/dream-of-Au/solution-p7137)，可以去康康。

令 $f_{i,j}$ 表示 $i$ 轮游戏，bob 需要选择 $j$ 次加，双方都采取最优策略时最终的分数。假设第一轮 Alice 选的实数为 $x$，如果 Bob 选择加上 $x$，最终局面为 $f_{i-1,j-1}+x$，否则为 $f_{i-1,j}-x$。由于 Bob 想要最小化分数，因此他会选择两者中更小的那个作为他的决策。换句话说，最终分数为 $\min(f_{i-1,j-1}+x,f_{i-1,j}-x)$，而显然当 $x=\frac{f_{i-1,j}-f_{i-1,j-1}}{2}$ 时 $\min(f_{i-1,j-1}+x,f_{i-1,j}-x)$ 最大，所以 Alice 在第一轮里一定会选 $\frac{f_{i-1,j}-f_{i-1,j-1}}{2}$。简化一下 dp 式即为：$f_{i,j}=\frac{f_{i-1,j-1}+f_{i-1,j}}{2}(0<j<i)$，特别地，由于 Alice 所选数必须在 $[0,k]$ 之间， 所以 $f_{i,0}=0,f_{i,i}=ik$。D1 就是直接递推。

分母是平凡的 $2^{i-1}$，系数也是平凡的 $k$，考虑剥去分母和系数，只关心分子。dp 式变为 $f_{i,0}=0,f_{i,j}=f_{i-1,j-1}+f_{i-1,j},f_{i,i}=2^{i-1}\times i$。看上去阳间多了，如果没有 $f_{i,0},f_{i,i}$ 的特殊 case 就是一个裸的杨辉三角。

考虑抹去这两个 case，找规律不难发现如果令 $f_{1,j}=0(j\le 0),f_{1,j}=2j-1(j>0)$ 那么 $f_{i,0},f_{i,i}$ 就可以用 $f_{i,j}=f_{i-1,j-1}+f_{i-1,j}$ 统一解释了。计算 $f_{n,m}$ 时考虑 $f_{0,i}$ 对于 $f_{n,m}$ 的贡献，这相当于在网格图上走，每次可以向右或右下走一步，问有多少种方案从 $(0,i)$ 走到 $(n,m)$ 这个点，直接组合数即可。时间复杂度 $O(Tm)$。

代码如下（码字不易，能给个赞再走吗QAQ）：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
#define int ll 
using namespace std;
inline int read(){int x=0,fh=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')fh=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=1e6+5,qlr=1e9+7;
int pw[N],inv[N],fac[N];

inline int ksm(int x,int y){
	int ans=1,t=x;
	while(y){
		if(y&1) ans=ans*t%qlr;
		t=t*t%qlr;
		y>>=1;
	}
	return ans;
}

int C(int n,int m){
	return fac[n]*inv[m]%qlr*inv[n-m]%qlr;
}

void solve(){
	int n=read(),m=read(),k=read(),ans=0;
	fo(i,1,m) ans=(ans+(2*i-1)*C(n-1,m-i))%qlr;
	cout<<ans*ksm(pw[n-1],qlr-2)%qlr*k%qlr<<'\n';
}

signed main(){
	int n=N-5;
	pw[0]=fac[0]=1;fo(i,1,n) pw[i]=(pw[i-1]<<1)%qlr,fac[i]=fac[i-1]*i%qlr;
	inv[n]=ksm(fac[n],qlr-2);go(i,n-1,0) inv[i]=(inv[i+1]*(i+1))%qlr;
	int T=read();
	while(T--) solve();
	return 0;
}
/*
-------------------------------------------------
*/

```


---

## 作者：Lates (赞：2)

设 $f[i][j]$ 表示进行了 $i$ 轮，$j$ 轮做加法最后的值。
	Alice 说的数是 $x$。

$f[i][j]$ 可以转移到 $f[i][j-1]+x,f[i-1][j-1]-x$

由于这个 Alice 采用最优策略，如果出现这两个转移一个大一个小，那么说明这个 Alice 不够聪明，Bob 选优的那个，Alice 就亏了。

所以 Alice 会让这两个玩意相等。

$x=\dfrac{f[i][j-1]-f[i-1][j-1]}{2}$

$f[i][j]=\dfrac{f[i][j-1]+f[i-1][j-1]}{2}$

同时乘 $2^i$，设 $g[i][j]= 2^i f[i][j]$

于是 $g[i][j]=g[i-1][j]+g[i-1][j-1]$

于是是类似一个杨辉三角的东西。

边界是 $g[i][0]=f[i][0]=0$， $g[i][i]=2^i\cdot i\cdot k$

注意到这里都是 $g[i][i]$ 对答案有贡献。

对于  $g[i][i]$ 对 $g[n][m]$ 的贡献次数是 点	$(i,i)$ 到 $(n,m)$ 的方案数。 每次可以向 下 或这 右下 走。

如果 $i=m$，只有一种方案，那就是一直向下走，
否则有 $\binom{n-i-1}{m-i}$ 种方法。因为这个时候向下只会走 $n-i-1$ 次。

![](https://cdn.luogu.com.cn/upload/image_hosting/jmt2f87h.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

比如从 $(1,1)$ 走到 $(4,2)$，只能往下走 第一维坐标之差减一次。

然后从 $(i,i)$ 走到 $(n,m)$ 的话，你会有 $m-i$ 的横坐标位移，这对应了走右下方，这也被 $n-i-1$ 个向下走的包含。所以就是数数数就是上面那个组合数。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
#define int long long 
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}

const int MAX=1e6+5,P=1e9+7;
/*
f[i][j]= ???{f[i-1][j]-x,f[i-1][j-1]+x} 
C[i][j]=C[i-1][j]+C[i-1][j-1]
(f[i-1][j]+f[i-1][j-1)/2=x ->

f[i][j]=(f[i-1][j]+f[i-1][j-1])/2
f[i][0]=0
f[i][i]=i*k

2^i f[i][j] = (f[i-1][j]+f[i-1][j-1]) 2^(i-1)
g[i][j]= 2^i * f[i][j]
g[i][j]=g[i-1][j]+g[i-1][j-1] 
g[i][0]= 0
g[i][i]=2^i * i * k

  0 1 2  3  4 j
0 0 - -  -  -
1 0 2 -  -  -
2 0 2 8  -  -
3 0 2 10 24 -
4 0 2 12 34 64
i
*/

int n,m,k,fac[MAX],inv[MAX],T,po[MAX];
inline int qpow(int x,int p){
	int ret=1;
	for(;p;p>>=1ll,x=1ll*x*x%P)if(p&1)ret=1ll*ret*x%P;
	return ret;
} 
inline int C(int n,int m){
	return 1ll*fac[n]*inv[m]%P*inv[n-m]%P;
}
signed main(){
	fac[0]=1;po[0]=1;inv[0]=1;
	for(register int i=1;i<=1e6;++i)
		fac[i]=1ll*fac[i-1]*i%P,po[i]=po[i-1]*2ll%P;
	inv[1000000]=qpow(fac[1000000],P-2);
	for(register int i=1e6-1;i>=1;--i)inv[i]=1ll*inv[i+1]*(i+1)%P;
//	printf("%lld %lld %lld\n",C(5,2),C(0,0),C(14,7));
	T=read();
	
	while(T--){
		n=read();m=read();k=read();
		int ans=0;
		for(register int i=1;i<m;++i){
			ans+=1ll*C(n-i-1,m-i)*i%P*po[i]%P;
			ans%=P;
		}
		ans+=1ll*m*po[m];ans%=P;
		ans=1ll*ans*qpow(po[n],P-2)%P;
		printf("%lld\n",ans*k%P);
	}

	return 0;
} 

```


---

## 作者：pengyule (赞：1)

博弈论 dp 好题。

**博弈论 dp 通常都是从终止态开始往前 dp。**   
首先还是找关键词——我们用什么刻画一个子游戏——Bob 还剩几个加法要做、游戏（还剩）的轮数。

设 $f(i,j)$ 表示还剩 $i$ 轮，Bob 还剩 $j$ 个加法要做，聪明的 Alice 在这一轮中能把自己引向的最大局面的值。

$$f(i,j)=\max_{x\in[0,k]}\{\min(f(i-1,j-1)+x,\min(f(i-1,j)-x\}$$

由于根据常识 $f(i-1,j)\ge f(i-1,j-1)$ 而两者都是定值，所以当且仅当 $x=\frac{f(i-1,j)-f(i-1,j-1)}2$ 时，$f(i,j)$ 取到最大值 $\frac{f(i-1,j)+f(i-1,j-1)}2$。

当 $i=j$ 时，只能够从 $f(i-1,j-1)$ 转移，并且不难发现 $f(i,i)=i\times k$。

这个 $O(nm)$ 的 dp 足以解决 Easy Version。

由于 dp 数组的每一个位置都可看作关于 dp 边界值的函数，所以我们考虑每一个 dp 边界值（$f(i,i)$）对于 $f(n,m)$ 的贡献。

$f(i,i)$ 第一步只能被 $f(i+1,i)$ 转移，从第二步开始就可以分别向 $f(i+1,j)$ 和 $f(i+1,j+1)$ 转移，那么到达 $f(n,m)$ 的过程可以看成 $(i+1,i)$ 横坐标 $+(n-i-1)$ 而纵坐标 $+(m-i)$ 得到，又因为总步数为 $(n-i-1)$，我们只需用 $n-i-1\choose m-i$；另一方面，每次都有 $\times \frac 12$ 的转移系数，因此 $f(i,i)=i\times k$ 对 $f(n,m)$ 的贡献为 $\frac {n-i-1\choose m-i}{2^{n-i}}$，最终式子为
$$f(n,m)=\sum_{i=1}^n\frac {n-i-1\choose m-i}{2^{n-i}}\cdot i\times k$$


```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	register char ch=getchar();register int x=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
const int N=1e6+5,mod=1e9+7,I2=(mod+1)/2;
int n,m,K,jc[N],ijc[N],miI2[N];
int C(int n,int m){return 1ll*jc[n]*ijc[m]%mod*ijc[n-m]%mod;}
void add(int &x,int y){(x+=y)>=mod&&(x-=mod);}
inline int qp(int a,int b){int c=1;for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)c=1ll*c*a%mod;return c;}
void solve(){
	n=read(),m=read(),K=read();
	jc[0]=ijc[0]=1;for(int i=1;i<=n;i++)jc[i]=1ll*jc[i-1]*i%mod;
	ijc[n]=qp(jc[n],mod-2);
	for(int i=n-1;i;i--)ijc[i]=1ll*ijc[i+1]*(i+1)%mod;
	miI2[0]=1;for(int i=1;i<=n;i++)miI2[i]=1ll*miI2[i-1]*I2%mod;
	if(n==m){cout<<1ll*n*K%mod<<'\n';return;}
	int ans=0;
	for(int i=1;i<=min(m,n-1);i++)add(ans,1ll*C(n-i-1,m-i)*miI2[n-i]%mod*i%mod*K%mod);
	cout<<ans<<'\n';
}
int main(){
	int T=read();
	while(T--)solve();
}
```

---

## 作者：Vistarin (赞：0)

由 Easy Version 可得，答案的递推式为：

$$a_{i,j} = \frac{1}{2}(a_{i-1,j}+a_{i-1,j-1}), a_{i,0}=ik, a_{0,j}=0$$

（为方便起见，令 $m := n-m$）

考虑固定 $i$ ，求数列关于 $j$ 的生成函数 $F_j(x)$。由题意：

$$F_0(x) = \sum_{i=0}^{\infty} a_{i,0} x^i = k\sum_{i=0}^{\infty} i  x^i  = \frac{kx}{(1 - x)^2}$$

对于 $j\ge 1$，设 $F_j(x) = \sum_{i=0}^{\infty} a_{i,j} x^i.$

则 $F_j(x) = \frac{1}{2} Σ_{i=1}^∞ (a_{i-1,j} + a_{i-1,j-1})x^i = \frac{1}{2} x \left(\sum_{i=0}^{\infty} a_{i,j} x^{i} + \sum_{i=0}^{\infty} a_{i,j-1} x^{i}  \right)$.

故 $F_j(x) = \frac{1}{2}x(F_j(x) + F_{j-1}(x))$，即 $F_j(x) = \frac{x}{2-x}F_{j-1}(x)$. 

解得 
$$F_j(x) = \frac{kx}{(1-x)^2}\cdot \left(\frac{x}{2-x}\right)^j = kx^{j+1} \cdot\frac{1}{(1-x)^2}\cdot \frac{1}{(2-x)^j}$$
	
考虑广义二项式定理推论：设 $r$ 是非负实数，则 $(1-rx)^{-n}=\sum^{\infty}_{k=0}\binom{n+k-1}{k}r^{k}x^{k}$.

我们有：

$$A(x)=\frac{1}{(1-x)^2}=(1-x)^{-2}=\sum^{\infty}_{i=0}\binom{2+i-1}{i}x^i=\sum^{\infty}_{i=0}(i+1)x^i$$

$$B(x)=\frac{1}{(2-x)^j}=\frac{2^{-j}}{\left( 1-\frac{1}{2}x \right)^j}=2^{-j}\sum^{\infty}_{i=0}\binom{j+i-1}{i}2^{-i}x^i$$
  
于是
$$F_j(x)=kx^{j+1}A(x)B(x)=k\cdot2^{−j}\sum_{n,m\ge 0}\binom{n+j-1}{j}(m+1)2^{-n}x^{j+1+n+m}$$

取出第 $i$ 项：令 $j+1+n+m=i$，将 $m$ 换元得

$$a_{i,j}=[x_{i}]F_j(x)=k\cdot 2^{−j}\sum_{n=0}^{i−j−1}\binom{n+j−1}{j−1}(i−j−n)2^{-n}$$

上式可以在 $O(m)$ 内计算完成。


```cpp
void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	m = n - m;	
	if (m == 0) {
		cout << n * k % mod << endl;
		return;
	}

	auto get_c = [&](int n, int m) {
		vector<int> c(n + 1);
		if (n < m) return c;
		c[m] = 1;
		for (int i = m + 1; i <= n; i++) {
			c[i] = c[i - 1] * i % mod * inv(i - m) % mod;
		}
		return c;
	};
	auto c = get_c(n, m - 1);

	int ans = 0;
	for (int i = 0; i <= n - m - 1; i++) {
		ans += c[i + m - 1] * inv(binpow(2, i)) * (n - m - i);
		ans %= mod;
	}
	ans = ans * k % mod * inv(binpow(2, m)) % mod;
	cout << ans << endl;
}
```

---

## 作者：cosf (赞：0)

## [CF1628D](https://codeforces.com/problemset/problem/1628/D2) [和的游戏](https://www.luogu.com.cn/problem/CF1628D2) 困难版

## 思路

在简单版中，$n, m \le 2000$，可以使用 $O(nm)$ 的算法，即 `dp`。

但是在本题中，原始的 `dp` 是过不了的。我们要稍微更改一下思路。

和 `dp` 一样，令 $d(n, m)$ 表示 $n$ 回，$m$ 回加的答案。容易发现，$d(n, m) = \min \{d(n - 1, m - 1) + x, d(n - 1, m) - x\}$，其中 $x$ 是选的数。为了使 $d(n, m)$ 大，后两者须相等，此时 $d(n, m) = \frac{d(n - 1, m - 1) + d(n - 1, m)}{2}$。

当 $d(n - 1, m - 1)$ 或 $d(n - 1, m)$ 不存在时，即边界上时，需要特殊处理：

1. 若 $m=0$，则 $d(n, m) = 0$。
2. 若 $n = m$，则 $d(n, m) = nk$。

容易发现，只要有了所有边界值，我们就可以算出结果了。我们只需要计算第 $2$ 种边界对答案的贡献就行了。每个 $d(i, j)$ 只会对 $d(i + 1, j), d(i + 1, j + 1)$ 有直接贡献，与杨辉三角的贡献方式是十分类似的，这种情况就可以利用组合数来求解。

对于 $d(i, i)$，它到 $d(n, m)$ 的不同方式有 $C(n - i - 1, m - i)$ 种（记得 $n-i$ 还要再减一），那么它对答案的贡献是 $ik\times\frac{C(n - i- 1, m - i)}{2^{n-i}}$。把所有 $i$ 从 $1$ 到 $m$ 的贡献加起来就是结果了。

这就可以 $O(n\log n)$ 求解了。

注意，若 $n = m$，不能用组合数（$n-i-1 \lt m-1$），需要特判（用公式）。

## 代码

```cpp
// 注：去掉了所有模。
ll n, m, k;
cin >> n >> m >> k;
if (n == m)
{
    cout << m * k << endl;
    continue;
}
ll res = 0;
for (int i = 1; i <= m; i++)
{
    res = (res + i * k * C(n - i - 1, m - i) * inv(pow(2LL, n - i)));
}
cout << res << endl;
```


---

## 作者：_ZSR_ (赞：0)

### [CF1628D2 Game on Sum (Hard Version) ](https://www.luogu.com.cn/problem/CF1628D2)

一开始没有什么好的思路，可以先从特殊的数据入手。如果 $m=0$，那么最后答案就是 $0$。如果 $m=n$，那么最后答案就是 $n*k$。这样的话我们就有一些边界的值了，然后可以考虑 $DP$。

我们令 $f_{i,j}$ 表示还剩 $i$ 轮，$Bob$ 还要进行 $j$ 次加操作的最终答案，那么状态转移方程就是 $f_{i,j}= \min (f_{i-1,j-1}+t,f_{i-1,j}-t)$，又由于两个人都绝顶聪明，那么当 $t = \frac {f_{i-1,j}-f_{i-1,j-1}} {2}$时，$f_{i,j}$ 取到最大值 $\frac {f_{i-1,j-1}+f_{i-1,j}} {2}$。

但是我们发现，如果这样转移的话时间复杂度是 $n^2$ 级别的，显然过不去，那么考虑优化。$f_{i,j}$ 其实就是 $\frac {f_{i-1,j-1}+f_{i-1,j}} {2}$，然后我们知道 $f_{i,i}$ 的值，思考每个 $f_{i,i}$ 对于答案的贡献。简单画个转移的图之后会发现，对于一个 $f_{i,j}$，它可以对 $f_{i+1,j},f_{i+1,j+1}$ 产生贡献，抽象成网格图就是一个点每次可以向下或者右下走一步。每走一步我们会发现，它的值都变成了原来的 $\frac 1 2$。一个点 $(i,i)$ 走到 $(n,m)$ 的路径数量就相当于 $(i+1,i)$ 走到 $(n,m)$ 的路径数量，因为 $f_{i,i}$ 无法更新 $f_{i+1,i+1}$。又因为每次都必须向下走一步，因此就是从 $n-(i+1)$ 步中选择 $m-i$ 步向右，方案数为 $C_{n-(i+1)}^{m-i}$。走每一条路径对于答案的贡献都是 $\frac {i \times k} {2^{n-i}}$。那么最终的答案就是 $k \times \sum_{i=1}^m C_{n-(i+1)}^{m-i} \times \frac i {2^{n-i}}$。

code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10,mod=1e9+7; 
int T,n,m,k;
int fac[N],inv[N];
inline int ksm(int a,int b) 
{
	int res=1;
	while (b) 
    {
		if (b&1) res=res*a%mod;
		a=a*a%mod;
		b=b>>1;
	}
	return res;
}
inline int C(int m,int n) 
{
	if (n==m||n==0) return 1;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
inline void pre_work()
{
    fac[0]=1;
	for(int i=1;i<N;++i) 
    {
		fac[i]=fac[i-1]*i%mod;
		inv[i]=ksm(fac[i],mod-2);
	}
}
signed main() 
{
#ifndef ONLINE_JUDGE
    freopen("zsr.in","r",stdin);
    freopen("zsr.out","w",stdout);
#endif
	pre_work();
	scanf("%lld",&T);
	while (T--)
    {
        int ans=0;
        scanf("%lld%lld%lld",&n,&m,&k); 
        if (n==m) printf("%lld\n",n*k%mod);
        else 
        {
            for(int i=1;i<=m;++i) ans=(ans+ksm(inv[2],n-i)*i%mod*C(n-i-1,m-i)%mod)%mod;
            printf("%lld\n",ans*k%mod);
        }
    }
	return 0;
}

```


---

## 作者：linyihdfj (赞：0)

## CF1628D2 Game on Sum (Hard Version)
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
显然可以考虑设 $dp[i][j]$ 表示前 $i$ 次操作 $Bob$ 选择了 $j$ 次加的最终的答案。
那么假设 $Alice$ 选择 $t$ 的话，转移方程就是：

$$
dp[i][j] = \min(dp[i-1][j] - t,dp[i-1][j-1] + t)
$$

可以发现我们睿智的 $Alice$ 一定会选择 $t = \dfrac{dp[i-1][j] + dp[i-1][j-1]}{2}$，可以证明如果比这个值大或者比这个值小都不是最优的。

$dp$ 初值就显然是 $dp[i][i] = i \times k,dp[i][0] = 0$。
我们考虑对于这个式子其实就相当于 $dp[i][j]$ 会对 $dp[i+1][j]$ 和 $dp[i+1][j+1]$ 产生 $\dfrac{dp[i][j]}{2}$ 的贡献，那么就考虑每一个 $dp[i][i]$ 对 $dp[n][m]$ 的贡献就好了，显然 $Bob$ 最多会选择 $m$ 次加。

我们考虑转化一下其实就是相当于从 $(i,i)$ 走到 $(n,m)$ 的方案数就是它的贡献次数，但是从 $(i,i)$ 走到 $(i+1,i+1)$ 是显然没有意义的，因为 $(i+1,i+1)$ 就是一个初值，所以就是可以理解为从 $(i+1,i)$ 走到 $(n,m)$ 的方案数，其实就是 $n - i - 1$ 步里选 $m-i$ 步向上，就是 $\binom{n-i-1}{m-i}$，但是我们每一步都会造成贡献除二，显然我们总共走了 $n-i$ 步，因为我们第一次走的也算一步，所以答案也要除以 $2^{n-i}$，所以最终就是：

$$
\sum_{i=1}^m \dfrac{i \times k \times \binom{n-i-1}{m-i}}{2^{n-i}}
$$

那么直接暴力算这个式子的值就好了。
但是需要特判 $n=m$ 的情况，因为我们把这个当作了初值，所以不会去处理。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6+5;
const int MOD = 1e9+7;
int fac[N],inv[N],pw[N];
int mod(int x){
	return x % MOD;
}
int power(int a,int b){
	int res = 1;
	while(b){
		if(b & 1)	res = mod(res * a);
		a = mod(a * a);
		b >>= 1;
	}
	return res;
}
void pre(int mx){
	fac[0] = 1;
	for(int i=1; i<=mx; i++)	fac[i] = mod(fac[i-1] * i);
	inv[mx] = power(fac[mx],MOD-2);
	for(int i=mx-1; i>=0; i--)	inv[i] = mod(inv[i+1] * (i + 1)); 
	int inv2 = power(2,MOD-2);
	pw[0] = 1;
	for(int i=1; i<=mx; i++)	pw[i] = mod(pw[i-1] * inv2);
}
int C(int n,int m){
	if(n < m)	return 0;
	return mod(mod(fac[n] * inv[m]) * inv[n - m]);
}
signed main(){
	pre(1000000);
	int t;
	scanf("%lld",&t);
	while(t--){
		int n,m,k;
		scanf("%lld%lld%lld",&n,&m,&k);
		int ans = 0;
		for(int i=1; i<=m; i++){
			ans = mod(ans + mod(mod(mod(k * i) * C(n-i-1,m-i)) * pw[n-i]));
		}
		if(n == m)	ans = mod(k * m);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：zcxxnqwq (赞：0)

令 $f[i][j]$ 表示前 $i$ 步里强制让 Bob 选择 $j$ 次加操作的结果，那么特殊情况就有：

- $j=0$，Alice 必定选 $0$，$f[i][j]=0$

- $j=i$，Alice 必定选 $k$，$f[i][j]=j\times k$

考虑一般情况：假设 Alice 选择了 $x$，那么Bob操作后结果即 $\min\{f[i-1][j-1]+x,f[i-1][j]-x\}$，那么 Alice 的最优策略必然是使 $f[i-1][j-1]+x=f[i-1][j]-x$，即 $f[i][j]=(f[i-1][j]+f[i-1][j-1])\div 2$。朴素 dp 的时间复杂度是 $O(nm)$。

考虑优化，观察 dp 式子，如果没有除以 $2$ 和乘 $k$ 的限制，那是不是就像极了杨辉三角。初始时三角形上只有 $i=j$ 的位置是有值的，值为 $i\times k$。最终要求的就是三角上 $(n,m)$ 位置的值。于是考虑快速统计 $(i,i)$ 对答案的贡献。

由于每次在三角上一定要往下走，可以选择是否向右走，那么 $(i,i)$ 走到 $(n,m)$ 就要走 $n-i$ 步，方案数就是 $C_{n-i}^{m-i}$ 吗？不是。如果第一步就往右下走，那么这时候的贡献是以 $(i+1,i+1)$ 为起点来计算的，于是只有 $n-i-1$ 步可以选择走右下，方案数 $C_{n-i-1}^{m-i}$，不要忘了每次贡献都要除以 $2$，一共除 $2^{n-i}$。

于是答案即 $ans=\sum\limits_{i=1}^m \dfrac{i\times k\times C_{n-i-1}^{m-i}}{2^{n-i}}$，预处理组合数即可 $O(n+m)$ 求解。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ff(i,s,e) for(int i=(s);i<=(e);++i)
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1e6+5,mod=1e9+7;
int n,m,k;
int jc[N],inv[N],inv2[N];
inline int ksm(int x,int y){
	int res=1;
	for(;y;y>>=1){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
	}
	return res;
}
inline int C(int n,int m){
	return 1ll*jc[n]*inv[m]%mod*inv[n-m]%mod;
}
inline void solve(){
	n=read(),m=read(),k=read();
	if(m==n) return printf("%d\n",1ll*k*m%mod),void();
	int ans=0;
	ff(i,1,m){
		int tmp=1ll*i*C(n-i-1,m-i)%mod*inv2[n-i]%mod;
		ans+=tmp;
		if(ans>=mod) ans-=mod;
	}
	printf("%d\n",1ll*ans*k%mod);
}
signed main(){
	int qwq=1e6;
	jc[0]=1;
	ff(i,1,qwq) jc[i]=1ll*jc[i-1]*i%mod;
	inv[qwq]=ksm(jc[qwq],mod-2);
	for(int i=qwq-1;i>=0;--i) inv[i]=1ll*inv[i+1]*(i+1)%mod; 
	inv2[1]=inv[2];
	ff(i,2,qwq) inv2[i]=1ll*inv2[i-1]*inv[2]%mod;
	int T=read();
	while(T--) solve();
	return 0;
}
```


---

