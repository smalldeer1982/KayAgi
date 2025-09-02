# Game on Sum (Easy Version)

## 题目描述

This is the easy version of the problem. The difference is the constraints on $ n $ , $ m $ and $ t $ . You can make hacks only if all versions of the problem are solved.

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

## 作者：Alex_Wei (赞：24)

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

## 作者：DaiRuiChen007 (赞：11)

# CF1628D1 - Game on Sum (Easy Version) 题解

upd 2022.01.28，修复了几处笔误，感谢 @wzy2021 大佬的指正

## 题目大意

[题目链接](https://codeforces.com/problemset/problem/1628/D1)

Alice 和 Bob 正在玩一个游戏，游戏分为 $n$ 个回合，Alice 和 Bob 要轮流对一个数 $x$ 进行操作，已知这个数初始值是 $0$。

具体每个回合的行动规则如下：

1. Alice 选择一个在区间 $[0,k]$ 之间的实数 $t$。
2. Bob 可以选择让 $x$ 变成 $x+t$ 或者 $x-t$，但是 Bob 在 $n$ 个回合之内至少选择 $m$ 次让 $x$ 变成 $x+t$。

Alice想让最终的 $x$ 最大，Bob 想让最终的 $x$ 最小。

已知双方均采用最优策略，求最终的 $x$ 值（对 $10^9+7$ 取模）

数据范围保证：$1\le m\le n\le 2000,k\le10^9+7$。

## 思路分析

约定：用 $t_i$ 表示第 $i$ 轮的 $t$ 值。

从特殊到一般，首先考虑比较简单的情况：$n=2,m=1$。

对于第一轮的情况，如果 Alice 选择的 $t_1$ 比较小那么 Bob 的最优策略是加上 $t_1$，反之则是减去 $t_1$。

- 对于第一种情况，Bob 第二轮一定会减去 $t_2$，所以 Alice 一定会选 $0$，最终结果是 $t_1$。
- 对于第二种情况，Bob 第二轮只能会加上 $t_2$，所以 Alice 一定会选 $k$，最终结果是 $k-t_1$。

所以对于这种情况，Bob 的最优策略的结果应该是 $\min(t_1,k-t_1)$。

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

这样的时间复杂度是 $\Theta(nm)$ 预处理 $\Theta(1)$ 查询的，可以通过本题。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2001,MOD=1e9+7,INV=5e8+4;
//INV(5e8+4)是2在模1e9+7意义下的乘法逆元，在此意义下*INV就等价于/2 
int dp[MAXN][MAXN],n,m,k;
inline void solve() {
	scanf("%lld%lld%lld",&n,&m,&k);
	printf("%lld\n",dp[n][m]*k%MOD); //输出时把答案都*k 
	return ;
}
signed main() {
	for(register int i=1;i<MAXN;++i) {
		dp[i][0]=0;
		dp[i][i]=i%MOD; //dp的边界条件
	} 
	for(register int i=2;i<MAXN;++i) {
		for(register int j=1;j<i;++j) {
			dp[i][j]=(dp[i-1][j-1]+dp[i-1][j])%MOD*INV%MOD; //按式子进行状态转移 
		}
	}
	int T;
	scanf("%lld",&T);
	while(T--) solve(); //多组数据
	return 0;
}
```



---

## 作者：Vsinger_洛天依 (赞：9)

# [Game on Sum(Easy Version)](https://www.luogu.com.cn/problem/CF1628D1)

逆天[冲刺 NOIP2024 题单](https://www.luogu.com.cn/training/484173)可做题之一。

首先看到题目是一个想让最后结果较大，一个想让最后结果较小，两者均选择最优策略，所以可以考虑 $\text{dp}$，经典套路了。

然后设 $f_{i,j}$ 为用掉 $i$ 轮且使用了 $j$ 次加法后的对应的 $x$ 的值，可以知道 $f_{n,m}$ 为最后的结果。

然后对于 Bob（他想要让最后结果较小）的转移方程就很明显了。

$$f_{i,j}=\min(f_{i-1,j}-t,f_{i-1,j-1}+t)$$

这里 $f_{i-1,j}$ 表示上一次不使用加法，$f_{i-1,j-1}$表示上一次使用加法（似乎很明显吧）。

而 Alice 希望这个结果最大，因此我们可知其会让 $f_{i-1,j}-t=f_{i-1,j-1}+t$（很明显是因为这里要取 $\min$）。

那么用最基本的等式的基本性质可以解一下上面那个式子去求出 $t$ 的值。

$$f_{i-1,j}-t-(f_{i-1,j-1}+t)=0$$

$$2\times t=f_{i-1,j}-f_{i-1,j-1}$$

$$t=\frac{f_{i-1,j}-f_{i-1,j-1}}{2}$$

我们解出 $t$ 的之后可以带回原本的转移方程来求出对应的 $f_{i,j}$ 了。

$$f_{i,j}=f_{i-1,j-1}+\frac{f_{i-1,j}-f_{i-1,j-1}}{2}$$

$$f_{i,j}=\frac{f_{i-1,j}+f_{i-1,j-1}}{2}$$

边界值 $f_{i,0}=0,f_{i,i}=i\times k$，然后直接大力 $\text{dp}$ 即可。

这是朴素代码，复杂度是 $\text O(Tnm)$ 无法通过此题。

```cpp
namespace solve{
	inline int read(){
		int s=0,w=1;char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
		while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
		return s*w;
	}
    inline void write(const int x){
        if(x>=10) write(x/10);
        putchar(x%10+'0');
    }
    inline void print(const int x,string s){
        if(x<0) putchar('-');
        write(x<0?-x:x);
        int len=s.size();
        for_(i,0,len-1) putchar(s[i]);        
    }
    int f[2000][2000];
	inline void In(){
        const int mod=1e9+7,inv=5e8+4;
        int T=read();
        while(T--){
            int n=read(),m=read(),k=read();
            for_(i,1,n){
                f[i][i]=i*k%mod;
            }
            for_(i,2,n){
                for_(j,1,i-1){
                    f[i][j]=(f[i-1][j]+f[i-1][j-1])%mod*inv%mod;
                }
            }
            print(f[n][m],"\n");
        }
	}
}
```

那咋办呢？完全可以 $\text O(nm)$ 预处理一遍，然后 $\text O(1)$ 去查询。

但是这样就有个问题，原本我们是让 $f_{i,i}=i\times k$，而现在我们需要让 $f_{i,i}=i$，在查询 $f_{n,m}$ 的时候乘上 $k$。

复杂度 $\text{O}(nm)$ 可以通过此题。

```cpp
int f[3000][3000];
inline void In(){
    const int mod=1e9+7,inv=5e8+4;
    for_(i,1,2005){
        f[i][i]=i;
    }
    for_(i,2,2005){
        for_(j,1,i-1){
            f[i][j]=(f[i-1][j]+f[i-1][j-1])%mod*inv%mod;
        }
    }
    int T=read();
    while(T--){
        int n=read(),m=read(),k=read();
        print(f[n][m]*k%mod,"\n");
    }
}
```

---

## 作者：KingPowers (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1628D1)

一方让一个值尽可能大，另一方让一个值尽可能小，这类问题我们经常会考虑 dp。

注意到 Alice 和 Bob 都是绝顶聪明的，因此他们的决策只和后续的结果有关，因此反着 dp：设 $f[i][j]$ 表示还剩下 $i$ 轮，Bob 还要使用 $j$ 次加法最后的 $x$ 值，设这次 Alice 给出的值为 $t$，转移考虑 Bob 这一次用不用加法：

$$
f[i][j]=\min(f[i-1][j]-t,f[i-1][j-1]+t)
$$

而 Alice 给出的 $t$ 值会使得 $\min(f[i-1][j]-t,f[i-1][j-1]+t)$ 最大，不难发现令它们相等的时候可以取最大值，解得

$$
t=\frac{f[i-1][j]-f[i-1][j-1]}{2}
$$

回代可得

$$
f[i][j]=\frac{f[i-1][j]+f[i-1][j-1]}{2}
$$

边界值令 $f[i][i]=i$，直接暴力预处理，每次询问输出 $f[n][m]\times k$ 即可。

时间复杂度：$O(nm+T)$。

```cpp
const int mod=1e9+7;
const int inv2=(mod+1)>>1;
const int inf=1e9;
int n,m,k,f[2005][2005];
void init(int n){
	For(i,1,n) f[i][i]=i;
	For(i,2,n) For(j,1,i-1)
		f[i][j]=(f[i-1][j-1]+f[i-1][j])%mod*inv2%mod;
}
void Main(){
	cin>>n>>m>>k;
	cout<<f[n][m]*k%mod<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	init(2000);
	int T=1;cin>>T;
	while(T--) Main();
	return 0;
}
```

---

## 作者：naroto2022 (赞：2)

# CF1628D1 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1628D1)

### 题意

初始时，有一个数 $ans=0$。

有两个人，第一个人要在 $[0,k]$ 选出一个实数 $t$。

第二个人可以选择让 $ans$ 加 $t$ 或减 $t$。

总共有 $n$ 轮，第二个人至少要操作 $m$ 次，且两个人都会使用最优策略。

### 思路

容易发现，$k$ 在题目中没啥大用，于是我们就假设 $k=1$，这时候设最后的 $ans$ 就为 $dp[n][m]$。

开始考虑 $dp$ 的转移方程，可以容易得到。

$\begin{aligned} dp[i][j]=\max_{t=0/1}\{\min(dp[i-1]j-1]+t,dp[i-1][j]-t)\} \end{aligned}$。

里面的是第二个人是否选择操作，外面的是第一个人要的最优的操作。

于是，由于 $t$ 只可能为 $0$ 或 $1$，所以就可以进行分类讨论。

1. 若 $dp[i-1][j]-dp[i-1][j-1]\leqslant 2$，则 $dp[i][j]=\frac{dp[i-1][j-1]+dp[i-1][j]}{2}$。
2. 若 $dp[i-1][j]-dp[i-1][j-1]>2$，则 $dp[i][j]=dp[i-1][j-1]+1$。

接下来我们发现对于一个 $dp[n][m]$，有 $dp[n][m+1]-dp[n][m]\leqslant 2$，证明如下。

证明：$\begin{aligned} dp[n][m+1]-dp[n][m]&=\frac{dp[n-1][m]+d[n-1][m+1]}{2}-\frac{dp[n-1][m-1]+dp[n-1][m]}{2}  \\&=\frac{dp[n-1][m+1]-dp[n-1][m-1]}{2}\\&=\frac{dp[n-1][m+1]-dp[n-1][m]}{2}+\frac{dp[n-1][m]-dp[n-1][m-1]}{2}\\&\leqslant\frac{2}{2}+\frac{2}{2}\\&=2 \end{aligned}$

即 $dp[n][m+1]-dp[n][m]\leqslant 2$。

所以，$dp[i][j]$ 只能为 $\frac{dp[i-1][j-1]+dp[i-1][j]}{2}$。

观察到，除去分数线，就是一个杨辉三角，但是，显然，这样会 TLE（困难版），所以考虑线性统计 $ans$。

可以考虑 $dp[i][i]$ 对 $dp[n][m]$ 的影响，除去分数线，会发现其实就是从 $(i,i)$ 开始只能向下或向右下前进到 $(n,m)$ 的方案数，但是由于 $dp[i+1][i+1]$ 是边界值，所以必能经过 $(i+1,i+1)$，那么就相当于从 $(i,i+1)$ 出发到 $(n,m)$ 的方案数，于是，就为 $C^{m-i}_{n-i-1}$。

当然，这里就有人问了，为什么呢？

首先，这是一个杨辉三角形（除去分数线）没错吧？于是通过数学归纳法可以证明杨辉三角形第 $n$ 行的第 $m$ 个为 $C^{m}_{n}(m\geqslant 2)$。

证明：已知，杨辉三角的第一行为 $1$，第二行为 $1,1$，两行均满足猜想。

接下来，对于第 $n$ 行（$n>2$），第 $m$ 个数（$m\geqslant2$）为 $\begin{aligned}C^{m-1}_{n-1}+C^{m}_{n-1}&=\frac{(n-1)\times(n-2)\times\cdots\times(n-m+1)}{(m-1)!}+\frac{(n-1)\times(n-2)\times\cdots\times(n-m)}{m!}\\&=\frac{(n-1)\times(n-2)\times\cdots\times(n-r+r)}{m!}\\&=\frac{(n-1)\times(n-2)\times\cdots\times(n-m)}{m!}\\&=C^{m}_{n}\end{aligned}$

证毕。

接下来，再加上分数线，就可以得到 $\begin{aligned}dp[n][m]=\sum^{m}_{i=1}\frac{i\times C^{m-i}_{n-i-1}}{2^{n-i}}\end{aligned}$。

于是就有 $\begin{aligned}ans=k\times\sum^{m}_{i=1}\frac{i\times C^{m-i}_{n-i-1}}{2^{n-i}}\end{aligned}$。

预处理即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int INV=5e8+4,mod=1e9+7,MN=1e6+1;
//INV是2在模mod意义下的乘法逆元，在此意义下*INV就等价于/2 
long long fac[MN],inv[MN],T,n,m,k,ans;
//fac[i]表示i!的值，inv[i]表示fac[i]在模1e9+7意义下的乘法逆元 
long long ksm(long long a, long long b) {
	long long res=1;
	while(b) {
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b=b>>1;
	}
	return res;
}
long long C(long long m, long long n) {
	if(n==m||n==0) return 1; 
	return fac[m]*inv[n]%mod*inv[m-n]%mod; 
}
int main(){
	fac[0]=1;
	for(long long i=1; i<MN; i++){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=ksm(fac[i],mod-2);
	}
	scanf("%lld %lld %lld",&n,&m,&k); 
	if(n==m) printf("%lld\n",n*k%mod);
	else{
		for(long long i=1; i<=m; i++) ans=(ans+ksm(INV,n-i)*i%mod*C(n-i-1,m-i)%mod)%mod;
		printf("%lld\n",ans*k%mod);	
	}
	return 0;
}
```

---

## 作者：dbxxx (赞：2)

[可以在我的博客中查看本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf1628d1.html)

个人认为博弈论的板子题。

首先 $k$ 就是个障眼法。当 $k$ 变化的时候，Alice 选择的数也按比例变化，这样操作后的 $x$ 也总会按比例变化（$x$ 初值为 $0$），仍然可以最优。因此只需要计算 Alice 在 $[0, 1]$ 之间选数最后答案乘 $k$ 即可。

然后又是一个障眼法：Bob 肯定会选择恰好 $m$ 次让 $x \gets x + t$，多选显然在 Bob 的角度上更劣。

博弈论经典倒序 dp，这是因为每个人都聪明绝顶，可以根据接下来的局势判断当前局势做什么更优（而跟之前的局势无关）。

设 $f(i, j)$ 为游戏还剩 $i$ 轮，Bob 还能做 $j$ 次加法时 $x$ 的值。

接着倒着思考，先思考 Bob 再思考 Alice，因为 Alice 的决策取决于 Bob。

设这一轮 Alice 选择的是 $t$。如果 Bob 选择的是加法，答案是 $f(i - 1, j - 1) + t$；如果 Bob 选择的是减法，答案是 $f(i - 1, j) - t$。

Bob 为了让 $x$ 尽可能小，会选择两种方案中更小的那种，也就是 $\min(f(i - 1, j - 1) + t, f(i - 1, j) - t)$。那么 Bob 就思考完成了。

当然聪明绝顶~~秃头~~的 Alice 也思考到了 Bob 的思考。那么她的目标就是让 $x = \min(f(i - 1, j - 1) + t, f(i - 1, j) - t)$ 最大。

推导可得当且仅当 $t = \dfrac{f(i - 1, j) - f(i - 1, j - 1)}{2}$ 时，$x$ 有最大值 $\dfrac{f(i - 1, j - 1) + f(i - 1, j)}{2}$。

得到转移方程：$f(i, j) = \dfrac{f(i - 1, j - 1) + f(i - 1, j)}{2}$。

边界：$f(i, 0) = 0$，$f(i, i) = i$。前面那种 Alice 每次只能选 $0$，不然 Bob 就能把他减成负数；后面那种就是 Alice 欺负 Bob，每次都选 $1$，反正 Bob 不能减。

多组询问，先预处理然后 $\mathcal{O}(1)$ 回答即可。

时间复杂度 $\mathcal{O}(nm + q)$。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-10-17 02:13:13 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-10-17 02:20:25
 */
#include <bits/stdc++.h>
#define int long long

inline int read() {
    int x = 0;
    bool flag = true;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            flag = false;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return x;
    return ~(x - 1);
}

const int mod = (int)1e9 + 7, in2 = (int)5e8 + 4;
const int maxn = 2005, maxm = 2005;

int f[maxn][maxm];

signed main() {
    for (int i = 1; i <= 2000; ++i)
        f[i][i] = i;
    
    for (int i = 2; i <= 2000; ++i)
        for (int j = 1; j < i; ++j)
            f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % mod * in2 % mod;
    
    int q = read();
    while (q--) {
        int n = read(), m = read(), k = read();
        printf("%lld\n", f[n][m] * k % mod);
    }
    return 0;
}
```

如果觉得本篇题解写得好，不要忘记点赞，谢谢！

---

## 作者：lcfollower (赞：1)

模拟赛第三题，没做出来，学长讲解后有感，来发篇题解巩固一下。

从 $1\le m\le n\le 2000$ 很容易想到总体时间复杂度是 $\mathcal O(nm)$。

然后看着很像 dp，于是设 $f_{i,j}$ 表示前 $i$ 轮 Bob 用了 $j$ 次加法后的答案，询问结果即为 $f_{n ,m}$。

但是我们注意到 Alice 和 Bob 都非常聪明，他们会思考后面的结果然后做出决定，于是反着 dp，设 $f_{i,j}$ 表示还剩 $i$ 轮且 Bob 还可以用 $j$ 次加法的答案。

- 首先 $f_{i,0} = 0$，此时 Bob 一直执行减法，而 Alice 总是选择一个非负数，因此选出的 $t>0$ 则明显不优。所以 Alice 一直选择 $t = 0$ 为最优解。

- 还有一种特殊情况，$f_{i,i} = ik$，此时 Bob 不得不都执行加法，Alice 可以一直选择 $t = k$ 为最优解。

处理完边界条件后考虑转移。

明显有 $f_{i ,j} = \max\limits_{t\land \mathbb{R}\land t\in [0 ,k]}\{\min \{f_{i - 1 ,j - 1} + t ,f_{i - 1 ,j} - t\}\}$，前者表示这次选择加法，后者表示这次选择减法。由于 Bob 想要这次答案尽可能小，所以两者取最小值。由于 Alice 想要这次答案尽可能大，所以外面套上取最大值。

Alice 为了让里面最大，所以一定会让 $f_{i - 1 ,j - 1} + t = f_{i - 1 ,j} - t$，改变一下 $2t = f_{i - 1 ,j} - f_{i - 1 ,j - 1}$，$t = \frac{f_{i - 1 ,j} - f_{i - 1 ,j - 1}}{2}$。

带进去 $f_{i ,j} = f_{i - 1 ,j - 1} + \frac{f_{i - 1 ,j} - f_{i - 1 ,j - 1}}{2}$ = $\frac{f_{i - 1 ,j - 1} + f_{i - 1 ,j}}{2}$。

最后答案是 $f_{n ,m}$。

由于是在模 $10^9 + 7$ 意义下，所以需要求得 $\frac{1}{2}$ 在模 $10^9 + 7$ 意义下的逆元。

时间复杂度为 $\mathcal O(Tnm)$，会 TLE（$1\le T\le 10^3$）。

回顾一下 $f_{i ,i} = ik$，此时把 $f_{i ,i} = i$，把它带入一下转移方程：$f_{i ,j} = \frac{f_{i - 1 ,j - 1}k + f_{i - 1 ,j}k}{2} = \frac{\left(f_{i - 1 ,j - 1} + f_{i - 1 ,j}\right)k}{2}$，这里一开始从 $f_{2 ,1}$ 转移，有用的为 $\frac{f_{1 ,1}k}{2}$，然后一直转移，会发现此时答案是**原来的（$f$）** $\frac{f_{i ,j}}{k}$，因此现在答案为 $f_{n ,m}k$。

于是 $\mathcal O(nm)$ 预处理一下然后 $\mathcal O(1)$ 输出，时间复杂度为 $\mathcal O(T + nm)$。

```cpp
# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)
# define dn(i ,x ,y) for (int i = x ; i >= y ; i --)
# define inf 1e14

using namespace std;

inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writesp (int x){write (x) ,putchar (' ');}
inline void writeln (int x){write (x) ,putchar ('\n');}

const int N = 2005 ,MOD = 1e9 + 7;
int f[N][N] ,n ,m ,k ,inv2;

inline int qpow (int a ,int b){
  int res = 1;
  while (b){
    if (b & 1) res = res * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  } return res;
} inline void init (){

  /* 由于 f 是全局数组，所以不用赋 f[i][0] = 0。 */
  up (i ,1 ,2000) f[i][i] = i;//边界。

  up (i ,2 ,2000)
    up (j ,1 ,i - 1)
      f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % MOD * inv2 % MOD;//转移。
    
} inline void solve (){
  n = read () ,m = read () ,k = read ();

  writeln (f[n][m] * k % MOD);

} signed main (){

  inv2 = qpow (2 ,MOD - 2);//费马小定理求逆元。
  
//  writeln (inv2);
      
  init ();
  
  int T = read ();

  while (T --) solve () ;
  return 0 ;
}
```

---

## 作者：hzoi_Shadow (赞：1)

[题目传送门 (Easy Version)](https://www.luogu.com.cn/problem/CF1628D1) | [题目传送门 (Hard Version)](https://www.luogu.com.cn/problem/CF1628D2)

# 前置知识

[博弈论](https://oi-wiki.org/math/game-theory/intro/)

# 解法

## [CF1628D1 Game on Sum (Easy Version)](https://www.luogu.com.cn/problem/CF1628D1)

设 $x_{i}$ 表示第 $i$ 轮时 ``Alice`` 选择的数。

设 $f_{i,j}$ 表示已经进行了 $i$ 轮，且使用了 $j$ 次加法时的最大得分，状态转移方程为 $f_{i,j}= \max \{ \min(f_{i-1,j}-x_{i},f_{i-1,j-1}+x_{i}) \}=\frac{f_{i-1,j}+f_{i-1,j-1}}{2}$，边界为 $\begin{cases} f_{i,0 \sim \infty}=0 & i=0 \\ f_{i,0}=0, f_{i,i}=i \times k & i \ne 0 \end{cases}$。
  - 由于 ``Bob`` 想让结果尽可能小，所以有 $f_{i,j}= \min(f_{i-1,j}-x_{i},f_{i-1,j-1}+x_{i})$。
  - 由于 ``Alice`` 想让结果尽可能大，所以会让 $\min(f_{i-1,j}-x_{i},f_{i-1,j-1}+x_{i})$ 取到最大值，即 $f_{i-1,j}-x_{i}=f_{i-1,j-1}+x_{i}$ 时，解得 $x_{i}= \frac{f_{i-1,j}-f_{i-1,j-1}}{2}$，代入原式有 $f_{i,j}=\frac{f_{i-1,j}+f_{i-1,j-1}}{2}$。

由于 ``Bob`` 想让结果尽可能小，所以至多使用 $m$ 次加法，故最终 $f_{n,m}$ 即为所求。

另外，由于求解 $f_{n,m}$ 的过程中只有加法和 $\times \frac{1}{2}$ 运算，故可以将 $k$ 缩小至 $1$ 进行预处理 $f_{n,m}$，询问时再扩大到 $k$，即 $f_{n,m} \times k$。
        
        
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll p=1000000007;
ll f[2010][2010];
ll qpow(ll a,ll b,ll p)
{
    ll ans=1;
    while(b>0)
    {
        if(b&1)
        {
            ans=ans*a%p;
        }
        b>>=1;
        a=a*a%p;
    }
    return ans;
}
int main()
{
    ll t,n,m,k,i,j;
    cin>>t;
    for(i=1;i<=2000;i++)
    {
        f[i][0]=0;
        f[i][i]=i;
        for(j=1;j<=i-1;j++)
        {
            f[i][j]=((f[i-1][j]+f[i-1][j-1])%p)*qpow(2,p-2,p)%p;
        }
    }
    for(i=1;i<=t;i++)
    {
        cin>>n>>m>>k;
        cout<<f[n][m]*k%p<<endl;
    }
    return 0;
}
```

## [CF1628D2 Game on Sum (Hard Version)](https://www.luogu.com.cn/problem/CF1628D2)

观察到 $f$ 的转移过程比较像杨辉三角的转移过程。

当 $n=m$ 时，有 $f_{n,m}=m \times k$ 即为所求。

当 $n \ne m$ 时，
  - 考虑计算 $f_{i,i}$ 对 $f_{n,m}$ 产生的贡献。
    - 从 $f_{i,i}$ 到 $f_{n,m}$ 一共进行了 $n-i$ 次 $\times \frac{1}{2}$ 操作。
    - 由 $f_{i,j}$ 会向 $f_{i+1,j}$ 和 $f_{i+1,j+1}$ 进行转移，故等价于 $(i,j)$ 一次可以走到 $(i+1,j)$ 或 $(i+1,j+1)$，求不经过形如 $(x,x)$ 的点时从 $(i,i)$ 走到 $(n,m)$ 的方案数，即从 $(i+1,i)$ 走到 $(n,m)$ 的方案数 $\dbinom{n-(i+1)}{m-i}$。
  - 故 $\sum\limits_{i=1}^{m}\frac{i \times k \times \binom{n-(i+1)}{m-i}}{2^{n-i}}$ 即为所求。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll p=1000000007;
ll jc[2000010],inv[2000010],jc_inv[2000010],a[2000010];
ll qpow(ll a,ll b,ll p)
{
    ll ans=1;
    while(b>0)
    {
        if(b&1)
        {
            ans=ans*a%p;
        }
        b>>=1;
        a=a*a%p;
    }
    return ans;
}
ll C(ll n,ll m,ll p)
{
    return (n>=m&&n>=0&&m>=0)?(jc[n]*jc_inv[m]%p)*jc_inv[n-m]%p:0;
}
int main()
{
    ll t,n,m,k,ans=0,i,j;
    cin>>t;
    jc[0]=jc_inv[0]=1;
    for(i=1;i<=1000000;i++)
    {
        a[i]=i;
        jc[i]=jc[i-1]*a[i]%p;
    }
    for(i=1000001;i<=2000000;i++)
    {
        a[i]=qpow(2,i-1000000-1,p);
        jc[i]=jc[i-1]*a[i]%p;
    }
    jc_inv[2000000]=qpow(jc[2000000],p-2,p);
    for(i=2000000-1;i>=1;i--)
    {
        jc_inv[i]=jc_inv[i+1]*a[i+1]%p;
    }
    for(i=1;i<=2000000;i++)
    {
        inv[i]=jc_inv[i]*jc[i-1]%p;
    }
    for(i=1;i<=t;i++)
    {
        cin>>n>>m>>k;
        ans=0;
        if(n==m)
        {
            cout<<m*k%p<<endl;
        }
        else
        {
            for(j=1;j<=m;j++)
            {
                ans=(ans+((j*k%p)*C(n-(j+1),m-j,p)%p)*inv[1000000+1+n-j]%p)%p;
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

[Hard Version 解法](https://www.luogu.com.cn/blog/101868/solution-cf1628d2)

### Analysis

首先显然 Bob 最终会恰好选 `+` 共 $m$ 次。

我们设 $f(n,m)$ 表示 $n$ 轮游戏中 Bob 选 `+` 共 $m$ 次最终的 score（初始 score 为 $0$）。

假设 Alice 第一轮选择 $x$，那么聪明绝顶~~秃头~~的 Bob 就会选择 `+` 和 `-` 中使得最终 score 最小的那个，即最终 score 成为 $\min\{f(n-1,m-1)+x,f(n-1,m)-x\}$，Alice 当然会选择让这个数最大，即 $x=\dfrac{f(n-1,m)-f(n-1,m-1)}{2}$。

即转移为：

$$f(n,m)=\dfrac{f(n-1,m-1)+f(n-1,m)}{2}$$

边界：

$$\begin{aligned}
f(n,n)&=nk
\\f(n,0)&=0
\end{aligned}$$

Dp 就好了。

时间 $O(nm)$。

### Code

自己动手试一试吧！

---

## 作者：npqenqpve (赞：1)

### 思路：

发现 $k$ 是最没有用的变量，因为等价于在 $[0,1]$  中选一个实数的答案扩大 $k$ 倍，因为策略总是相同的。

先手玩 $n=1$ 的答案，发现当 $m=0$ 时 Alice  一定会选 $0$，$m=1$ 时 Alice  会蹬鼻子上脸选 $1$，因为他怎么选 Bob 都得加上去。

设 $f_{i,j}$ 表示 $n=i,m=j$ 时的答案，那么 $f_{i,0}=0$，$f_{i,i}=i$。

手玩 $n=2,m=1$ 时发现不是那么显然，假设 Alice 给出了 $p$ 这个实数，那么 Bob 可以选择加或不加，也就是 $f_{2,1}=\min(f_{1,0}+p,f_{1,1}-p)$，当然 Alice 是**足够聪明**的，自然会让 $\min(f_{1,0}+p,f_{1,1}-p)$ 尽量大，也就是使得 $f_{1,0}+p=f_{1,1}-p$，即取 $p=\frac{f_{1,1}-f_{1,0}}{2}$，带入 $p$ 得到 $f_{2,1}=\frac{f_{1,1}+f_{1,0}}{2}$。

因此得到一般情况下 $f_{i,j}=\frac{f_{i-1,j-1}+f_{i-1,j}}{2}$。

考虑到最后是在模 $10^9+7$ 意义下的分数，直接求 $2$ 的逆元乘起来即可，当然也可以模拟分数。

### 代码：

```cpp
int t,n,m,k;
signed main()
{
	int inv=ksm(2,mod-2)%mod;//求 2 的逆元
	for(int i=1;i<=2000;i++) dp[i][i]=i,dp[i][0]=0;
	for(int i=1;i<=2000;i++)
	{
		for(int j=1;j<=2000;j++)
		{
			if(!dp[i][j])
			{
				dp[i][j]=((dp[i-1][j-1]+dp[i-1][j])%mod*inv%mod)%mod;
			}
		}
	}
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k;
		cout<<(dp[n][m]*k)%mod<<"\n";
	}
	system("pause > null");
}
```





---

## 作者：STA_Morlin (赞：0)

[题目 in CF](https://codeforces.com/problemset/problem/1628/D1)。

Alice 镇楼：

![](https://cdn.luogu.com.cn/upload/image_hosting/vo8c543o.png)

[博客食用效果更佳](https://www.cnblogs.com/stamorlin/p/18565627/CF1628D1)

## 题目大意

> Alice 和 Bob 又在玩游戏。
> 
> 该种游戏共分为 $n$ 轮，每轮中，先有一个数 $x = 0$，Alice 将选择 $t \isin [0, t_{max}]$，而 B 将会选择将 $x$ 增加或减少 $t$。在全部 $n$ 轮中，B 应至少有 $m$ 次选择减少操作。
> 
> Alice 希望结果最大，而 B 希望结果最小，并且他们都会做出最优决策。
> 
> 求问最终 $x$ 的值。

## 思路简析

~~感觉这个很博弈论。~~

每步最优操作，要推 dp 的样子还是比较显然的吧？

这里只有 $n, m$ 是给定变量，所以显然以其为状态。

考虑 $f_{i, j}$ 的一个值即进行了 $i$ 轮时，已经进行 $j$ 次增加操作时的 $x$ 值。

边界为 $f_{i, 0} = 0, f_{i, i} = i \times k$（当 $j = 0$ 时，Alice 必选 $0$，当 $j = i$ 时，Alice 必选 $k$）。

由于是 B 进行操作，那么他必然是取小，易得转移方程：

$f_{i, j} = \min{f_{i-1, j}-t, f_{i-1, j-1}+t}$

$Range : i_{1\rightarrow n}, j_{1\rightarrow \min{i-1, m}}$

考虑 Alice 要尽量大，那么就不能让 B 选出最小的，所以她会使 $f_{i-1, j}-t = f_{i-1, j-1}+t$，整理得 $t = \frac{f_{i-1, j}-f_{i-1, j-1}}{2}$，那么 $f_{i, j} = f_{i-1, j-1}+t = \frac{f_{i-1, j}+f_{i-1, j-1}}{2}$。

最终结果是 $f_{n, m}$。

然后我们写完了就会发现这是显然不对的，因为样例里有分数，而 $f_{i, j}$ 显然无法存入分数。

这个怎么办？一开始我还想分开存分子和分母，于是突击乘法逆元，然后你看定义：

> 如果一个线性同余方程 $ax \equiv 1 \pmod b$ ，则 $x$ 称为 $a \bmod b$ 的逆元，记作 $a^{-1}$ 。

那我们正好就是要把这个数乘上 $2^{-1}$ 的。所以要找到 $2x \equiv 1 \pmod {10^9+7}$，得 $x = 5\times10^8+4$，所以把每个 $f_{i, j}$ 都乘上 $5\times10^8+4$ 即可（相当于除以 $2$）。

（$2147482647 \div (5\times10^8+4) \approx 4$，所以在代码里这里要乘上 `1LL`。）

但是你考虑这样的话时间复杂度是 $O(T\cdot n\cdot m)$ 即 $4\times 10^9$ 的。

怎么办怎么办，但是你仔细看一眼这里除了 $k$ 真有啥是必要的吗？显然对于这个 dp $n$ 和 $m$ 只是一个范围，那么我们只要把范围推够了即可。那么我们可以预先钦定一个 $k = 1$，然后对于每一问进行对 $k$ 的一个乘，即是答案（这样的话上面转移方程的范围 $i$ 应是到 $n_{max}$ ，$j$ 也可以去掉 $m$ 了，这很好。）。

## _Code：_
```cpp
int T, n, m, k, li, lj;
int f[man][man];
int main () {
    files("test");
    scanf("%d", &T);
    for (int i = 1; i <= 2e3; ++ i) {
        f[i][i] = i;
        for (int j = 1; j < i; ++ j) 
            f[i][j] = 1LL*(f[i-1][j]+f[i-1][j-1])*inv%mop;
        }
    while (T --) {
        scanf("%d%d%d", &n, &m, &k);
        printf("%lld\n", 1LL*f[n][m]*k%mop);
    } return 0;
}
```

---

## 作者：gan1234 (赞：0)

令 $f_{i,j}$ 表示第 $i$ 轮回合，用了 $j$ 次加法操作。

我们从后往前转移。

首先对于 $j=m-n+i$ 的情况，Bob 不得不选择加法，所以 Alice 可以往大了去选数，因此转移为：

$$f_{i,m-n+i}=f_{i+1,m-n+i+1}+k$$

对于其它情况，Bob 会选择两种策略中最终更小的一种策略，因此转移是：

$$f_{i,j}=\min(f_{i+1,j}-t,f_{i+1,j+1}+t)$$

考虑 Alice 会要尽可能的大，所以 Alice 会让选择一个 $t$ 较小的那个使得较小的那个更大而，这时候 $f_{i+1,j}-t=f_{i+1,j+1}+t$，所以我们有转移：

$$f_{i,j}=\frac{f_{i+1,j}+f_{i+1,j+1}}{2}$$

直接做复杂度 $O(nm)$。可以过 easy。

考虑优化。

我们观察一下转移，发现我们可以画出一个矩阵，第一行的元素分别为：$k,3k,5k,...$ 也就是 $(2i+1)k$。而往下每一行每一列的元素都是上面两个元素和除以二。

我们尝试用生成函数去描述这个东西。

令 $F_i(x)$ 表示第 $i$ 行的生成函数。第一行是：

$$F_1(x)=\sum (2i+1)kx^i$$

转移就是：

$$F_{i}(x)=\frac{F_{i-1}(x)+xF_{i-1}(x)}{2}$$

这个东西和组合数是一样的形式，只不过下面多除了一个二。所以我们有：

$$F_n(x)=\frac{\sum^{n-1}_{i=0}\binom{n-1}ikx^iF_1(x)}{2^{n-1}}$$

而答案就是 $[x^{m-1}]F_n(x)$，也就是：

$$\frac{\sum^{\min(n-1,m-1)}_{i=0}\binom{n-1}i(2m-2i-1)k}{2^{n-1}}$$

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;

int ksm(int x,int k){
	int res=1,t=x;
	while(k){
		if(k&1)res=(res*t)%mod;
		t=(t*t)%mod;k>>=1;
	}
	return res;
}

int n,m,k;

int jc[1000005],inv[1000005];

int C(int x,int y){
	if(x<y)return 0;
	return jc[x]*inv[y]%mod*inv[x-y]%mod;
}

void work(){
	cin>>n>>m>>k;
	int sum=0;
	for(int i=0;min(n,m)>i;i++){
		sum+=C(n-1,i)*(2*(m-i-1)+1)%mod;
		sum%=mod;
	}
	sum=(sum*ksm(ksm(2,n-1),mod-2)%mod*k)%mod;
	cout<<sum<<endl;
}

signed main(){
	int N=1000000; 
	jc[0]=1;
	for(int i=1;N>=i;i++)jc[i]=jc[i-1]*i%mod;
	inv[N]=ksm(jc[N],mod-2);
	for(int i=N-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	int _T;
	cin>>_T;
	while(_T--)work();
	return 0;
}
```

---

## 作者：tder (赞：0)

观察到可能影响最终答案的有且仅有：

- 游戏进行的轮数；
- Bob 选择加减的次数。

不妨用 $f_{i,j}$ 表示进行了 $n-i$ 轮，还剩 $i$ 轮，Bob 选择了 $m-j$ 次 $x\gets x+t$，即还需选择 $j$ 次加法时的最优答案。

显然地，有 $f_{n,i}=0$。而又对于 $f_{i,0}$ Bob 无需再选择加法，为了使 $x$ 尽可能小，选择减法显然更优，而 Alice 为了使 $x$ 尽可能大，因此应选择 $t=0$，故此 $f_{i,0}=f_{i+1,0}=\cdots =f_{n,0}=0$。再考虑 $f_{i,i}$ 的情况，此时 Bob 在剩下的轮次里都必须选择加法，而 Alice 希望 $x$ 尽可能大，应选择最大的 $t=k$，此时最优，故 $x$ 最大变为 $i\times k$，因此 $f_{i,i}=i\times k$。

接下来考虑一般转移，这里比较简单，可以选择选或不选，即 $f_{i,j}=\min(f_{i-1,j-1}+x,f_{i-1,j}-x)$。此时两者一大一小，$x$ 越大前者越大，而后者越小，因此我们希望两者的较小值最大，应让两者尽可能接近，即 $f_{i-1,j-1}+x=f_{i-1,j}-x$，解得 $x=\dfrac{f_{i-1,j}-f_{i-1,j-1}}2$，此时 $f_{i,j}=\dfrac{f_{i-1,j}+f_{i-1,j-1}}2$。注意答案最终需要输出 $x\bmod(10^9+7)$ 的值，因此这里不妨乘上 $2$ 的逆元，如果不会建议先学习 [P5656](https://www.luogu.com.cn/problem/P5656)。最终答案即为 $f_{n,m}$。

经过上述推导我们已经可以解决 Easy Version 了，时间复杂度 $O(n\times m)$，只需考虑优化即可。

初始状态中的 $f_{n,i}$ 与 $f_{i,0}$ 均为 $0$，显然无法对最终答案作出贡献，因此只需考虑每个 $f_{i,i}=i\times k$ 的贡献。在转移到 $f_{n,m}$ 的过程中，其会依次转移到：

$$
\begin{aligned}
f_{i,i}\to f_{i+1,i}&\to f_{i+2,i}\to\cdots\to f_{n-(m-i),i}\to f_{n-(m-i)+1,i+1}\to\cdots\to f_{n,m} \\
&\to f_{i+2,i+1}\to\cdots\to f_{i+1+(m-i),m}\to f_{i+2+(m-i),m+1}\to\cdots f_{n,m} \\
&\to\cdots
\end{aligned}
$$

我们观察到 $f_{i,i}$ 无法转移给 $f_{i+1,i+1}$，而只能转移到 $f_{i+1,i}$，因此忽略第一次转移，那么不难发现上述转移次数均为 $n-i+1$，方案数即为 $\dbinom{n-i-1}{m-i}$，这是因为我们需要在 $n-i-1$ 次转移中选择 $m-i$ 次转移到 $f_{i,j}\to f_{i+1,j+1}$ 以确保最终能走到 $f_{n,m}$。注意到转移时还需要除以二，因此答案为：

$$
\sum_{i=1}^m\left(f_{i,i}\times\frac{\binom{n-i-1}{m-i}}{2^{n-i}}\right)
$$

时间复杂度 $O(m)$。

---

## 作者：TernaryTree (赞：0)

和 @Etinorally duel 到这题，慢了 19 条 CF 提交，被薄纱了/ll。

---

首先把至少选 $m$ 次 $+t$ 转换为至多选 $n-m$ 次 $-t$。然后考虑朴素 dp。设 $f_{i,j}$ 表示还剩 $i$ 轮，能用 $j$ 次 $-t$ 的答案。有：

$$f_{i,j}=\max_{t\in [0,k]}\min(f_{i-1,j-1}-t,f_{i-1,j}+t)$$

边界为 $f_{0,j}=0$，$f_{i,0}=ik$。

然后注意到转移里面两个关于 $t$ 的一次柿子取 $\min$ 是一个先增后减的凸壳形式，其中当柿子取到最大值时，$t=\dfrac{f_{i-1,j-1}-f_{i-1,j}}{2}$，可以通过归纳法证明 $t\in[0,k]$。然后代入得到转移的简单形式：

$$f_{i,j}=\dfrac{f_{i-1,j}+f_{i-1,j-1}}{2}$$

答案就是 $f_{n,n-m}$。这里复杂度 $\Theta(n^2)$。

欸这东西，我给第 $i$ 行都乘上 $2^i$，然后不就是组合数杨辉三角吗？就是边界不一样啊？考虑直接扔到边界上去算贡献。现在令 $g_{i,j}=2^i\cdot f_{i,j}$，然后注意到通过反复展开递推公式能使 $g_{i,j}$ 能被拆成若干个 $a_i\cdot g_{i,0}$ 的和，$a_i$ 表示此项系数。手摸发现

$$a_i=\binom{n-i-1}{m-i}$$

所以答案即为

$$\dfrac{k}{2^n}\sum_{i=0}^m\binom{n-i-1}{m-i}\cdot i\cdot 2^i$$

预处理阶乘，$2$ 的幂次及逆元即可做到线性复杂度。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int inv2 = 5e8 + 4;

int T, n, m, k;
int fac[maxn], inv[maxn];
int pw[maxn], ipw[maxn];

int power(int a, int b) {
	int t = 1;
	while (b) {
		if (b & 1) t = t * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return t;
}

int C(int n, int m) {
	if (n < 0 || m < 0 || m > n) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

signed main() {
	fac[0] = pw[0] = ipw[0] = 1;
	for (int i = 1; i < maxn; i++) {
		fac[i] = fac[i - 1] * i % mod;
		pw[i] = pw[i - 1] * 2 % mod;
		ipw[i] = ipw[i - 1] * inv2 % mod;
	} 
	inv[maxn - 1] = power(fac[maxn - 1], mod - 2);
	for (int i = maxn - 2; ~i; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
	cin >> T;
	while (T--) {
		cin >> n >> m >> k;
		if (n == m) {
			cout << n * k % mod << endl;
			continue;
		}
		int ans = 0;
		for (int i = 0; i <= m; i++) ans = (ans + C(n - i - 1, m - i) * i % mod * pw[i] % mod) % mod;
		cout << ans * k % mod * ipw[n] % mod << endl;
	}
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

#### 题意
$t$ 组数据，给定 $n, m, k$ ， Alice 每次给出一个 $[0,k]$ 的实数 $x$ ，Bob选择将分数 $+x$ 或 $-x$ ，Bob 要使最终分数最小，Alice 要使最终分数最大。Bob 至少进行 $m$ 次 $+x$ 。  
$1 \leq m \leq n, 0 \leq k \leq 10^9+7$ 。  
easy version: $1 \leq n, \sum n \leq 2000$ 。  
#### 题解
令 $f(x,y)$ 表示剩下 $x$ 个数，至少进行 $y$ 次加法操作的 Alice 控分的最大值。
边界条件 $f(x, 0) = 0, f(x, x) = kx$ 。  
考虑取第 $x$ 轮数的情况，Alice选择了值 $z$ ，Bob 有两种决策： $f(x - 1, y - 1) + z, f(x - 1, y) - z$ 。注意这里因为对于固定的Alice的选择序列，Bob可以任意采用 $y$ 的使用决策序列。  
然后 Bob 必然取 $\min(f(x - 1, y - 1) + z, f(x - 1, y) - z)$ 。  
注意两者的和是固定的，所以对于Alice的决策  $z$ 有 $\max_z \min(f(x - 1, y - 1) + z, f(x - 1, y) - z) = \frac{f(x - 1, y - 1) + f(x - 1, y)}{2}$ 。Alice采取了最优的 $z$ ，迫使 Bob 取到最大值。  
所以转移方程 $f(x, y) = \frac{f(x - 1, y - 1) + f(x - 1, y)}{2}$ 。  
这是 easy version 的部分。  

hard version 看[这里](https://www.luogu.com.cn/blog/FrigidPigeon/solution-cf1628d2)

---

## 作者：Iam1789 (赞：0)

设 $dp_{i,j}$ 表示进行 $i$ 轮游戏，`Bob` 使用 $j$ 次加法后的最终答案。

不难发现，`Bob` 为了最小化自己的答案，一定只会进行 $m$ 次加法，所以答案就是 $dp_{n,m}$。

考虑第 $1$ 轮，设 `Alice` 给出的数为 $k$，则有转移 $dp_{i,j}=min(dp_{i-1,j}-k,dp_{i-1,j-1}+k)$。

接着考虑 $k$ 会是多少。`Alice` 想要取得最大值。发现 $(y=dp_{i-1,j}-k)$ 是一个关于 $k$ 的减函数而 $(y=dp_{i-1,j-1}+k)$ 是一个关于 $k$ 的增函数。易得当且仅当 $dp_{i-1,j}-k=dp_{i-1,j-1}+k$ 时 $dp_{i,j}$ 取得最大，解得 $k=\frac{dp_{i-1,j}-dp_{i-1,j-1}}{2}$ 带入得 $dp_{i,j}=\frac{dp_{i-1,j}+dp_{i-1,j-1}}{2}$。

暴力 `dp` 即可。

---

