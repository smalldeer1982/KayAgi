# [ABC240G] Teleporting Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc240/tasks/abc240_g

高橋君は無限に広がる三次元グリッドのマス $ (0,\ 0,\ 0) $ にいます。

高橋君は瞬間移動によってマスからマスへ移動する能力を持っています。 マス $ (x,\ y,\ z) $ にいるとき、瞬間移動を $ 1 $ 回行うと $ (x+1,\ y,\ z),\ (x-1,\ y,\ z),\ (x,\ y+1,\ z),\ (x,\ y-1,\ z),\ (x,\ y,\ z+1),\ (x,\ y,\ z-1) $ のいずれかのマスに移動します。（マス $ (x,\ y,\ z) $ にとどまることは出来ないことに注意してください。）

ちょうど $ N $ 回の瞬間移動を行った後にマス $ (X,\ Y,\ Z) $ にいるような高橋君の移動経路が何通りあるかを求めてください。

すなわち、整数の $ 3 $ つ組を $ N+1 $ 個並べた列 $ \big(\ (x_0,\ y_0,\ z_0),\ (x_1,\ y_1,\ z_1),\ (x_2,\ y_2,\ z_2),\ \ldots,\ (x_N,\ y_N,\ z_N)\big) $ であって、下記の $ 3 $ つの条件をすべて満たすものの個数を求めてください。

- $ (x_0,\ y_0,\ z_0)\ =\ (0,\ 0,\ 0) $
- $ (x_N,\ y_N,\ z_N)\ =\ (X,\ Y,\ Z) $
- $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ |x_i-x_{i-1}|\ +\ |y_i-y_{i-1}|\ +\ |z_i-z_{i-1}|\ =\ 1 $

ただし、答えは非常に大きくなることがあるので、答えを $ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^7 $
- $ -10^7\ \leq\ X,\ Y,\ Z\ \leq\ 10^7 $
- $ N,\ X,\ Y,\ Z $ は整数

### Sample Explanation 1

ちょうど $ 3 $ 回の瞬間移動を行った後にマス $ (2,\ 0,\ -1) $ にいるような高橋君の移動経路は、下記の $ 3 $ 通り存在します。 - $ (0,\ 0,\ 0)\ \rightarrow\ (1,\ 0,\ 0)\ \rightarrow\ (2,\ 0,\ 0)\ \rightarrow(2,\ 0,\ -1) $ - $ (0,\ 0,\ 0)\ \rightarrow\ (1,\ 0,\ 0)\ \rightarrow\ (1,\ 0,\ -1)\ \rightarrow(2,\ 0,\ -1) $ - $ (0,\ 0,\ 0)\ \rightarrow\ (0,\ 0,\ -1)\ \rightarrow\ (1,\ 0,\ -1)\ \rightarrow(2,\ 0,\ -1) $

### Sample Explanation 2

ちょうど $ N $ 回の瞬間移動を行わなければならないことと、瞬間移動の際には移動せずにその場にとどまることは出来ないことに注意してください。

### Sample Explanation 3

答えを $ 998244353 $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
3 2 0 -1```

### 输出

```
3```

## 样例 #2

### 输入

```
1 0 0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
314 15 92 65```

### 输出

```
106580952```

# 题解

## 作者：zhaoyp (赞：12)

[ABC240G](https://atcoder.jp/contests/abc240/tasks/abc240_g)

$\text{Difficulty : 2462}$。

在三维空间内走 $n$ 步，从 $(0,0,0)$ 走到 $(x,y,z)$，每一步只能从当前整点移动到三维空间内相邻的整点，求走法数量，对大质数取模。

判断掉非法情况，假定 $x,y,z \ge 0$。

先考虑在二维平面内 $n$ 步走到 $(x,y)$ 该怎么做。

变化一下坐标轴为 $(x+y,x-y)$，发现四种走法 $(+1,0),(-1,0),(0,+1),(0,-1)$ 转化后的变化量分别为 $(+1,+1),(+1,-1),(-1,+1),(-1,-1)$ 两维相互独立。于是我们只需要分别求 $n$ 步走 $x - y$ 与 $x + y$ 的方案数然后相乘即可。

扩展到三维上，可以尝试枚举在 $x$ 方向上走的步数 $a$，走到 $x$ 的方案数为 $\dbinom{n}{a}\dbinom{a}{\frac{a+x}{2}}$，含义为从 $n$ 次操作中选出 $a$ 次在 $x$ 轴上移动，这 $a$ 次中又有 $\frac{a+x}{2}$ 次是向正方向的。再与 $n - a$ 步走 $z - y$ 与 $z + y$ 的方案数相乘即可。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e7 + 5;
const int mod = 998244353;
long long n,x,y,a,b,c,m,ans,fac[maxn],inv[maxn];
long long qpow(long long a,long long b){long long ans=1;while(b){if(b&1)ans=ans*a%mod;a=a*a%mod,b>>=1;}return ans;}
inline long long calc(long long n,long long m){return (m > n) ? 0 : fac[n] * inv[m] % mod * inv[n - m] % mod;}
inline long long solve(long long n,long long m){return (n >= m&&(n - m) % 2 == 0) ? calc(n,(n + m) / 2) : 0 ;}
void input()
{
	cin >> n >> a >> b >> c;
	a = abs(a),b = abs(b),c = abs(c);
	m = n - (a + b + c);
}
void prefix()
{
	fac[0] = 1;
	for(int i = 1;i <= n;i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = qpow(fac[n],mod - 2);
	for(int i = n - 1;i >= 0;i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
}
int main()
{
	input();
	prefix();
	if(m < 0||m % 2)
	{
		puts("0");return 0 ;
	}
	for(int i = a;i <= n - b - c;i++)
		ans = (ans + calc(n,i) * solve(i,a) % mod * solve(n - i,b + c) % mod * solve(n - i,abs(b - c)) % mod) % mod;
	cout << ans;
	return 0;
}
```

---

## 作者：tanyulin (赞：7)

### [ABC240G Teleporting Takahashi](https://www.luogu.com.cn/problem/AT_abc240_g)
~~组合意义天地灭，代数推导保平安。~~  
根据对称性，从 $(0,0,0)$ 走到 $(x,y,z)$ 的方案数等于走到 $(|x|,|y|,|z|)$ 的方案数，下文假设 $x,y,z>0$。  
最小步数显然是 $x+y+z$，每一步都是将某一维加 1，如果我们在某一维添上一个减 1 的操作，为了让这一维达到最终目标，应添加一个加 1 的操作，因此增加的步数一定是 2 的倍数，这就是判无解的条件。  
由于每多一个减 1 就一定多一个加 1，因此我们可以通过总步数算出一共走了多少次 -1，记为 $cnt=\frac{n-(x+y+z)}{2}$。  
于是我们枚举第一维用了多少次 -1，以及第 2 维用了多少 -1，可以得到如下~~长相十分恐怖~~的式子：
$$
\begin{aligned}
ans=\sum_{i=0}^{cnt}{{n}\choose{x+i}}{{n-(x+i)}\choose{i}}\sum_{j=0}^{cnt-i}{{n-(x+2i)}\choose{y+j}}{{n-(x+2i)-(y+j)}\choose{j}}
{{n-(x+2i)-(y+2j)}\choose{z+cnt-i-j}}
\end{aligned}
$$
尝试化简后面那坨式子，暴力拆开组合数：
$$
\begin{aligned}
W &=\sum_{j=0}^{cnt-i}{{n-(x+2i)}\choose{y+j}}{{n-(x-2i)-(y+j)}\choose{j}}{{n-(x-2i)-(y+2j)}\choose{z+cnt-i-j}}\\
&=\sum_{j=0}^{cnt-i}\frac{(n-(x+2i))!}{(y+j)!j!(z+cnt-i-j)!(cnt-i-j)!}\\
&=(n-(x+2i))!\sum_{j=0}^{cnt-i}\frac{1}{(y+j)!j!(z+cnt-i-j)!(cnt-i-j)!}\\
\end{aligned}
$$
把后面凑成新的二项式系数：
$$
\begin{aligned}
W&=\frac{(n-(x+2i))!}{(cnt+y-i)!(cnt+z-i)!}\sum_{j=0}^{cnt-i}\frac{(cnt+y-i)!}{(y+j)!(cnt-i-j)!}\frac{(cnt+z-i)!}{j!(z+cnt-i-j)!}\\
&=\frac{(n-(x+2i))!}{(cnt+y-i)!(cnt+z-i)!}\sum_{j=0}^{cnt-i}{{cnt+y-i}\choose{y+j}}{{cnt+z-i}\choose{z+cnt-i-j}}\\
&=\frac{(n-(x+2i))!}{(cnt+y-i)!(cnt+z-i)!}{{2cnt+y+z-2i}\choose{cnt+y+z-i}}
\end{aligned}
$$
其中最后一步用到了范德蒙德卷积公式。  
于是枚举 i 就能做到 $\mathcal{O}(n)$ 计算。  
[code](https://atcoder.jp/contests/abc240/submissions/39058389)

---

## 作者：Empty_Dream (赞：4)

## 分析

类似[这题](https://www.luogu.com.cn/problem/AT_abc221_g)，有个套路，把平面旋转 $45\degree$。

这题是三维的，显然不好做，那么可以先枚举第一维，就转化成二维平面中是否能从 $(0,0)$ 走到 $(y,z)$。

按照这题的思路，直接旋转一下，就变化成了 $(0,0)$ 走到 $(y-z,y+z)$，每一步也变成了 $(1,-1)$ 或 $(1,1)$ 或 $(-1,-1)$ 或 $(-1,1)$，可以进行单独操作了，证明过程参考[这题的题解](https://www.luogu.com.cn/article/zpnd6f71)。

之后的步骤还可以优化一下，先考虑一个问题，如果走了 $a$ 步 $+1$，$b$ 步 $-1$，总共走了 $k$ 步，目的地是 $x$，可以得到一个方程组：
$$
\begin{cases}
a-b=x\\
a+b=k
\end{cases}
$$
简单学过小学数学的就知道，$a=\frac{x+k}{2},b=\frac{x-k}{2}$，而最终方案就是 $C_k^a=C_k^b$。拓展到这题上面，最终目的地是 $(y-z,y+z)$，都是走 $k$ 步，那么最终方案就是到 $y-z$ 的方案数乘上到 $y+z$ 的方案数，也就是：
$$
C_k^{\frac{k+y-z}{2}} \times C_{k}^\frac{k+y+z}{2}
$$
不过这里还需要特判一下能否到达，以及分子部分能不能被 $2$ 整除。

对于第一维的判断，也是枚举走多少个正的，也可以得到走多少个负的；设走了 $a$ 步 $+1$，$b$ 步 $-1$，那么最终方案数就是 $C_n^a\times C_{n-a}^b$，当然 $a+b\le n$。

最终答案就是三维的方案数乘起来。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
const int N = 1e7;
int n, x, y, z, ans;
int fac[N + 5], inv[N + 5];

int ksm(int a, int b){
	int res = 1;
	while (b){
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

int C(int x, int y){
	return fac[x] * inv[x - y] % mod * inv[y] % mod;
}

int solve(int k, int kx, int ky){
	int a = abs(kx - ky), b = abs(kx + ky);
	if (k + a & 1 || k + b & 1 || k < a || k < b) return 0;
	return C(k, k + a >> 1) * C(k, k + b >> 1) % mod;//方程组求解加上组合数
}

signed main(){
	cin >> n >> x >> y >> z;
	x = abs(x), y = abs(y), z = abs(z);
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;//预处理阶乘
	inv[N] = ksm(fac[N], mod - 2);
	for (int i = N - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1ll) % mod;//预处理逆元
	for (int i = 0, j = x; i + j <= n; i++, j++){//i走负的，j走正的
		ans = (ans + C(n, i) * C(n - i, j) % mod * solve(n - i - j, y, z) % mod) % mod;//乘法原理统计答案
	}
	cout << ans;
	return 0;
}
```

---

## 作者：云浅知处 (赞：4)

当 $N<|X|+|Y|+|Z|$ 时无解。

否则，考虑先算出将 $a$ 步分配到一个长为 $b$ 的维度上，发现方案数是
$$
\binom{a}{\frac{a+b}{2}}
$$
不妨考虑两维的情况
$$
\begin{aligned}
F(N)&=\sum_{x=0}^N\binom{N}{x}\binom{x}{\frac{x+X}{2}}\binom{N-x}{\frac{N+Y-x}{2}}\\
&=\sum_{x=0}^N\dfrac{N!}{(\frac{x+X}{2})!(\frac{x-X}{2})!(\frac{N+Y-x}{2})!(\frac{N-Y-x}{2})!}\\
&=\dfrac{N!}{(\frac{N-X-Y}{2})!(\frac{N+X+Y}{2})!}\sum_{x=0}^N\dfrac{(N-X-Y)!(N+X+Y)!}{(\frac{x+X}{2})!(\frac{x-X}{2})!(\frac{N+Y-x}{2})!(\frac{N-Y-x}{2})!}\\
&=\dfrac{N!}{(\frac{N-X-Y}{2})!(\frac{N+X+Y}{2})!}\sum_{x=0}^N\binom{\frac{N-X-Y}{2}}{\frac{x-X}{2}}\binom{\frac{N+X+Y}{2}}{\frac{N+Y-x}{2}}\\
&=\binom{N}{\frac{N+X+Y}{2}}\binom{N}{\frac{N+X-Y}{2}}
\end{aligned}
$$
那么答案就是
$$
\sum_{z=0}^NF(N-z)\binom{N}{z}\binom{z}{\frac{z+Z}{2}}
$$
做完了。

> 写个 EGF：
> $$f_X(x)=\sum_{n\ge 0}\dfrac{1}{(2n+X)!}\binom{2n+X}{n}x^{2n+X}$$
> 我草了，这个东西的封闭形式是 $I_X(2x)$，其中 $I_{\alpha}$ 是[第一类修正贝塞尔函数](https://en.wikipedia.org/wiki/Bessel_function#Modified_Bessel_functions)，好高深！

---

## 作者：Ishy (赞：3)

# ABC240G Teleporting Takahashi

[洛谷：ABC240G Teleporting Takahashi](https://www.luogu.com.cn/problem/AT_abc240_g) 

[Atcoder：ABC240G Teleporting Takahashi](https://atcoder.jp/contests/abc240/tasks/abc240_g) 

## Problem

在一个空间直角坐标系中移动，每步可以沿着坐标轴正/负方向移动一个单位的长度。

给定 $N,X,Y,Z$，求：

恰好 $N$ 步，从点 $(0,0,0)$ 走到点 $(X,Y,Z)$ 的方案数。

答案对 $998244353$ 取模。$N,X,Y,Z \le 10^7$。

## Solution

先把答案为 $0$ 判掉。

记 $w = \frac{n - x - y - z}{2}$。

答案为：
$$
\sum\limits_{a_1 + a_2 + a_3 = w}\binom{x + 2a_1}{a_1}\binom{y + 2a_2}{a_2}\binom{z + 2a_3}{a_3}\binom{n}{x + 2a_1}\binom{n - x - 2a_1}{y + 2a_2}
$$
然后化简。**拆开消项以组成新的二项式系数**。
$$
\begin{aligned}
ans &= \sum\limits_{a_1 + a_2 + a_3 = w}\binom{x + 2a_1}{a_1}\binom{y + 2a_2}{a_2}\binom{z + 2a_3}{a_3}\binom{n}{x + 2a_1}\binom{n - x - 2a_1}{y + 2a_2} \\
&= \sum\limits_{a_1 + a_2 = 0}^{w}\binom{x + 2a_1}{a_1}\binom{y + 2a_2}{a_2}\binom{z + 2(w - a_1 - a_2)}{w - a_1 - a_2}\binom{n}{x + 2a_1}\binom{n - x - 2a_1}{y + 2a_2} \\
&= \sum\limits_{S = 0}^{w}\sum\limits_{a_1 = 0}^{S}\binom{x + 2a_1}{a_1}\binom{y + 2S - 2a_1}{S - a_1}\binom{z + 2w - 2S}{w - S}\binom{n}{x + 2a_1}\binom{n - x - 2a_1}{y + 2S - 2a_1} \\
&= \sum\limits_{S = 0}^{w}\binom{z + 2w - 2S}{w - S}\sum\limits_{a_1 = 0}^{S}\binom{x + 2a_1}{a_1}\binom{y + 2S - 2a_1}{S - a_1}\binom{n}{x + 2a_1}\binom{n - x - 2a_1}{y + 2S - 2a_1} \\
\end{aligned}
$$
 记 $W = \sum\limits_{a_1 = 0}^{S}\binom{x + 2a_1}{a_1}\binom{y + 2S - 2a_1}{S - a_1}\binom{n}{x + 2a_1}\binom{n - x - 2a_1}{y + 2S - 2a_1}$。
$$
\begin{aligned}
W &= \sum\limits_{a_1 = 0}^{S}\binom{x + 2a_1}{a_1}\binom{y + 2S - 2a_1}{S - a_1}\binom{n}{x + 2a_1}\binom{n - x - 2a_1}{y + 2S - 2a_1} \\
&= \sum\limits_{a_1 = 0}^{S} \frac{(x + 2a_1)!}{a_1!(x + a_1)!}\frac{(y + 2S - 2a_1)!}{(S - a_1)!(y + S - a_1)!}\frac{n!}{(x + 2a_1)!(n - x - 2a_1)!}\frac{(n - x - 2a_1)!}{(y + 2S - 2a_1)!(n - x - y - 2S)!} \\
&= \sum\limits_{a_1 = 0}^{S}\frac{n!}{a_1!(x + a_1)!(S - a_1)!(y + S - a_1)!(n - x - y - 2S)!} \\
&= n! \times \frac{1}{S!} \times \frac{1}{(x + y + S)!} \times \frac{1}{(n - x - y - 2S)!} \sum\limits_{a_1 = 0}^{S} \frac{S!}{a_1!(S - a_1)!}\frac{(x + y + S)!}{(x + a_1)!(y + S - a_1)!}  \\
&= \frac{n!}{S!(x + y + S)!(n - x - y - 2S)!}\sum\limits_{a_1 = 0}^{S}\binom{S}{a_1}\binom{x + y + S}{y + S - a_1}  \\
&= \frac{n!}{S!(x + y + S)!(n - x - y - 2S)!} \binom{x + y + 2S}{y + S}
\end{aligned}
$$
于是可以枚举 $S$。

[code ABC240G Teleporting Takahashi](https://atcoder.jp/contests/abc240/submissions/39058686) 

---

## 作者：Expert_Dream (赞：2)

这道题很像[这一道题](https://www.luogu.com.cn/problem/AT_abc221_g)。

我在这题写了题解，比较详细，[这里](https://www.luogu.com.cn/article/c9tpu7g9)。

难度黑题，关键就是一个点非常巧妙，非常难想到。将整一个图旋转一下，这样就可以独立两个维度，因此，再加上一些处理，可以背包。

但这道题稍有点不同。

这道题变成了立体空间，三维！那我们该如何处理呢？

我们可以直接枚举其中一个维度，变成二维上走到 $(y,z)$ 的方案了。

根据那个黑题的思想，我们可以将图旋转，相当于走到 $(y-z,y+z)$。两个维度也独立，可以分别操作。

我们再引出一个式子。

如果 $a$ 次 $-1$，$b$ 次 $+1$。

当你走了 $s$ 步，最终想要走到 $t$。

那么可以的出这两个式子：

$a-b=t$ 和 $a+b=s$。

因此我们可以算出 $a=\dfrac{s+t}{2}$，$b=\dfrac{s-t}{2}$。

那么我们把他应用到这道题上面，这一道题的要求就是最终要到达  $(y-z,y+z)$，设他要走 $k$ 步。

所以它的方案数可以用组合数学来表示，用到的是乘法原理。

${k\choose{\frac{k+y-z}{2}}} \times  {k\choose {\frac{k+y+z}{2}}}$

我们还需要判断一下如果不是 $2$ 的因数的话，那么是不合法的。

因此，最后的方案数就直接乘法原理即可。

~~某位小朋友只会用 lucas 求组合数，被 T 飞了，于是用了逆元预处理。~~

[link](https://atcoder.jp/contests/abc240/submissions/52483333)。

---

## 作者：Purslane (赞：2)

# Solution

用组合意义推导式子总是令人惊叹的。

## Subtask 1

考虑二维问题。用 $n$ 步走到 $(x,y)$。保证 $x$ 和 $y$ 都是自然数。

考虑我们用 $a$ 步让 $x+1$，$b$ 步让 $y+1$。那么要用 $a-x$ 步让 $x-1$，$b-y$ 步让 $y-1$。也就是 $2a+2b-x-y=n$，得出 $a+b=\frac{n+x+y}{2}$。

下面的过程中，如果组合数没有意义，默认为 $0$。令 $k=\frac{n+x+y}{2}$。

那么答案为 

$$\sum_{a=0}^{k} C_n^aC_{n-a}^{k-a}C_{n-k}^{a-x}$$

数学不好，不会推导。但是实际上是在 $n$ 个数里面选出长度为 $a$，$k-a$，$a-x$ 的三段。你可以先选出长度为 $k$ 的一段，然后从中选 $a$，在外面选 $a-x$。也就是

$$C_n^k\sum_{a=0}^k C_k^a C_{n-k}^{a-x}$$

有组合计数基础的人都知道，后面可以把 $C_k^a$ 换为 $C_k^{k-a}$。

$$C_n^k \sum_{a=0}^k C_k^{k-a} C_{n-k}^{a-x}$$

再抽象出一个问题，你有 $n$ 个数，你从中选 $k-x$ 个 。但是你把这 $n$ 个数分成了前 $k$ 个和后面的一些，分别枚举这 $k-x$ 个数有多少个在左右两边，也就是 $C_n^{k-x}$。

答案为

$$C_n^kC_n^{k-x}$$

## Subtask 2

直接枚举第三维分了多少步，可以算出多少个 $+1$ 多少个 $-1$。然后进行简单的组合计数，这个不是重点。复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e7+10,MOD=998244353;
int n,x,y,z,fuc[MAXN],inv[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {if(p&1) ans=ans*base%MOD;base=base*base%MOD,p>>=1;}
	return ans;
}
int C(int u,int d) {return fuc[d]*inv[u]%MOD*inv[d-u]%MOD;}
int solve(int n,int x,int y) {
	if((n+x+y)&1) return 0;
	if(n<x+y) return 0;
	int k=(n+x+y)/2;
	return C(k,n)*C(k-x,n)%MOD;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>x>>y>>z;
	x=abs(x),y=abs(y),z=abs(z);
	if(x+y+z>n||(n-x-y-z)&1) return cout<<0,0;
	fuc[0]=1; ffor(i,1,n+n+n) fuc[i]=fuc[i-1]*i%MOD;
	inv[n+n+n]=qpow(fuc[n+n+n],MOD-2);
	roff(i,n+n+n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	int ans=0;
	ffor(i,z,n) if((z-i)%2==0) {
		int mul=solve(n-i,x,y);
		int zz=(i+z)/2;
		mul*=C(zz,i),mul%=MOD;
		mul*=C(i,n),mul%=MOD;
		ans+=mul,ans%=MOD;	
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：liangbowen (赞：1)

[blog](https://www.cnblogs.com/liangbowen/p/18145579)。很典的 trick！记录一下。

关键技巧：走相邻点很难处理，通过改变坐标轴意义，将维度分开考虑。

下面是 ABC211G 与 ABC240G 的题解，先看完 ABC221G 后 ABC240G 就比较好做了捏。

## ABC221G

两维混在一起，每一步决策需要考虑两维，非常麻烦。

考虑将 $(x,y)$ 转为 $(x+y,x-y)$，那么每一步操作有如下变化。

+ 上：$(x,y+d_i)\to(x+d_i,y-d_i)$。
+ 下：$(x,y-d_i)\to(x-d_i,y+d_i)$。
+ 右：$(x+d_i,y)\to(x+d_i,y+d_i)$。
+ 左：$(x-d_i,y)\to(x-d_i,y-d_i)$。

发现两维被拆开了，等价于，解决两次下面的问题。

> 钦定 $o_i\in{-1,1}$，使得 $\sum\limits_{i=1}^no_i\times d_i=T$。

对等式左侧提出一倍的 $\sum\limits_{i=1}^nd_i$ 并移项，等价于解决：

> 钦定 $o_i\in{0,1}$，使得 $\sum\limits_{i=1}^no_i\times d_i=\dfrac{T-\sum d_i}2$。

即 01 背包问题，直接做即可。时空都有点小爆，bitset 优化即可通过。

[code](https://atcoder.jp/contests/abc221/submissions/52500236)，时间复杂度 $O(\dfrac{n\times\sum |d_i|}\omega)$。

## ABC240G

也就是将上面那个转化思路，上升到三维去计数。

不会三维怎么办？枚举走 $i$ 步到达 $Z$ 点，贡献为 $\Large\binom ni$ 乘以「$i$ 步走到 $Z$ 方案数」。

剩下就是用 $N-i$ 步 $(0,0)\to(X,Y)$。

与 ABC221G 一样，转成 $(0,0)\to(X+Y,X-Y)$，两维分开考虑，贡献即「$n-i$ 步走到 $X+Y$ 方案数」乘以「$n-i$ 步走到 $X-Y$ 方案数」。

> **Little problem**：如何计算「$t$ 步走到 $p$ 的方案数」？
> 必定是走 $\dfrac{t+p}2$ 步正向的，$\dfrac{t-p}2$ 步反向的，方案即 $\large\binom{t}{\frac{t-p}2}$。
> $\dfrac{t-p}2\notin\mathbb{N}$ 则方案数为 $0$。

于是枚举 $i$ 即可。

[code](https://atcoder.jp/contests/abc240/submissions/52500439)，时间复杂度 $O(n)$。

---

## 作者：complete_binary_tree (赞：0)

题意：从 $(0,0,0)$ 走到 $(X,Y,Z)$ 走 $N$ 步的方案数。

首先发现 $X,Y,Z$ 的正负与答案是无关的，所以 $X \leftarrow |X|,Y \leftarrow |Y|,Z \leftarrow |Z|$，都是正数比较好做。

考虑无解情况。$N - X - Y - Z$ 是奇数或者 $X + Y + Z < N$ 无解。

有解情况，考虑在 $x$ 轴上走 $a$ 步，$y$ 轴上走 $b$ 步，那么在 $z$ 轴上只能走 $N - a - b$ 步。

考虑在 $x$ 轴上走 $a$ 步的方案数。此时必须向前走 $\displaystyle \frac{a + X}{2}$ 步，再往回走 $\displaystyle \frac{a - X}{2}$ 步，但是可以任意排序，所以答案是 $\displaystyle C_{a}^{\frac{a + X}{2}}$。

同理其他两个也能算出，最后合并时乘上组合数即可。所以答案是：

$$\sum_{a=X}^{N-Y-Z}\sum_{b=Y}^{N-X-Z} C_{a}^{\frac{a + X}{2}} \cdot C_{b}^{\frac{b + Y}{2}} \cdot C_{N-a-b}^{\frac{N-a-b+Z}{2}} \cdot C_{N}^a \cdot C_{N-a}^b$$

但是如果这样枚举的话复杂度是 $O(n^2)$ 的，会 T 飞，所以考虑优化。

发现把前两维变成切比雪夫距离 $(x+y,x-y,z)$ 有一个很好的性质：一个变动的时候另一个也会变动，而且四种情况刚好覆盖两个 $+1,-1$，所以可以直接合并枚举：

枚举 $a$，那么前两维走 $a$ 步变为 $X+Y$ 和 $X - Y$，第三维走 $N-a$ 步变为 $Z$。那么答案是：

$$\sum_{a=X+Y}^{N-Z} C_{a}^{\frac{a+X+Y}{2}} \cdot C_{a}^{\frac{a+X-Y}{2}} \cdot C_{N-a}^{\frac{N-a+Z}{2}} \cdot C_N^a$$

这样就可以 $O(N)$ 递推了。（实际上如果是 $k$ 维用切比雪夫也可以做到 $O(N2^{k-2})$ 的复杂度）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int n, x, y, z, jc[10000007], ny[10000007];
long long ans = 0;

int ksm ( int a, int b ) {
    long long x = a, ans = 1;
    while ( b ) {
        if ( b & 1 ) ans = ans * x % mod;
        x = x * x % mod, b >>= 1;
    }
    return ans;
}

int C ( int n, int m ) { return 1ll * jc[n] * ny[m] % mod * ny[n - m] % mod; }

int main() {
    ios::sync_with_stdio( 0 ), cin.tie( 0 ), cout.tie( 0 );
    cin >> n >> x >> y >> z;
    x = abs ( x ), y = abs ( y ), z = abs ( z );
    if ( n < x + y + z || ( ( n - x - y - z ) & 1 ) ) {
        cout << 0;
        return 0;
    }
    jc[0] = 1;
    for ( int i = 1; i <= 1e7; ++i ) jc[i] = 1ll * jc[i - 1] * i % mod;
    ny[10000000] = ksm ( jc[10000000], mod - 2 );
    for ( int i = 9999999; ~i; --i ) ny[i] = 1ll * ny[i + 1] * ( i + 1 ) % mod;
    //cout << ny[1] << endl;
    for ( int k = x + y; k <= n - z; ++k ) {
        if ( ( k + x + y ) & 1 ) continue;
        ( ans += 1ll * C ( k, ( k + x + y ) / 2 ) * C ( k, ( k + x - y ) / 2 ) % mod * C ( n - k, ( n - k + z ) / 2 ) % mod * C ( n, k ) % mod ) %= mod;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：HomuraAkemi (赞：0)

直接大力代数推导。


$$
\begin{aligned}
&[x^ay^bz^c] \left(x+x^{-1}+y+y^{-1}+z+z^{-1}\right)^n \\
=&[x^ay^bz^c] \left((x+y)(1+1/xy)+(z+z^{-1})\right)^n \\
=& [x^ay^bz^c] \sum_{0\le i\le n} {n\choose i}(x+y)^i(1+1/xy)^i (z+z^{-1})^{n-i} \\
=& [x^ay^bz^c] \sum_{0\le i\le n} {n\choose i} \left[\sum_{0\le p\le i} {i\choose p}x^py^{i-p}\sum_{0\le q\le i}{i\choose q} (xy)^{-q}\right]\left[\sum_{0\le r\le n-i} {n-i\choose r} z^{n-i-2r}\right] \\
\end{aligned}
$$

枚举 $i$，我们要求 $p-q=a,i-p-q=b$，两个方程两个未知数不难解出 $p,q$；同理，$n-i-2r=c$，不难解出 $r$，从而本题直接得解。时间复杂度线性。

SpadeA261 姐姐好可爱！亲亲 Madoka 酱！

---

## 作者：Svemit (赞：0)

[cnblog](https://www.cnblogs.com/Svemit/p/18393466)

# [abc240 g](https://www.luogu.com.cn/problem/AT_abc240_g)

只考虑 $0 \leq X, Y, Z$ 的情况，显然小于 0 时的路径可以与大于 0 的一一对应。

考虑我们三个方向的增量分别需要 $X, Y, Z$，剩下的步数显然是通过走一步该方向又走回来这样子消耗。

记 $m = \frac{N - X - Y - Z}{2}$。如果 $N - X - Y - Z$ 是奇数或者 $N < X + Y +Z$ 就无解。

枚举三个方向分别多走了几步。

假设我们在 $X$ 方向多走了 $i$ 步，那么需要用 $i$ 步再走回来。

$$\sum_{i = 0}^{m} \sum_{j = 0}^{m - i} \binom {N}{X + i} \binom {N - X - i}{i} \binom{N - X - 2 \times i}{Y + j} \binom{N - x - 2 \times i - Y - j}{j}\binom{N - x - 2 * i - Y - 2 * j}{Z + m - i - j}\binom{N - x - i - Y - j - Z - m}{m - i - j}$$

发现这是个多重集组合数，可以给它变成 

$$\sum_{i = 0}^{m} \sum_{j = 0}^{m - i} \frac{N!}{(x + i)!i!(Y + j)!j!(Z + m - i - j)!(m - i - j)!}$$

把与 $j$ 无关的提出来

$$\sum_{i = 0}^{m} \frac{N!}{(x + i)!i!}\sum_{j = 0}^{m - i} \frac{1}{(Y + j)!j!(Z + m - i - j)!(m - i - j)!}$$

希望后面那一坨带 $j$ 的式子优美一点，发现 $Y + j + m - i - j = Y + m - i, Z + m - i - j + j = Z + m - i$，给他重新凑一下组合系数

$$\sum_{i = 0}^{m} \frac{N!}{(x + i)!i!(Y + m - i)!(Z + m - i)!}\sum_{j = 0}^{m - i} \frac{(Y + m - i)!}{(Y + j)!(m - i - j)!} \frac{(Z + m - i)!}{(Z + m - i - j)!j!}$$

$$= \sum_{i = 0}^{m} \frac{N!}{(x + i)!i!(Y + m - i)!(Z + m - i)!}\sum_{j = 0}^{m - i} \binom {Y + m - i}{Y + j} \binom{Z + m - i}{Z + m - i - j}$$

对后面那个式子使用范德蒙德卷积

$$\sum_{i = 0}^{m} \frac{N!}{(x + i)!i!(Y + m - i)!(Z + m - i)!}\binom{Y + Z + 2 \times m - 2 \times i}{Y + Z + m - i}$$

时间复杂度 $O(N)$。

---

## 作者：newwzl (赞：0)

## 思路
首先显然可以看出 $X$，$Y$，$Z$ 都求绝对值答案不变，后面假定三个值都为非负数。

然后可以看出 $N$ 与 $(X+Y+Z)$ 奇偶性不同或者 $N<X+Y+Z$ 时无解，直接输出 $0$。

接下来直接拿组合数求解。我们求一个 $f_i$ 表示只走 $X$ 和 $Y$ 轴并用 $X+Y+2\times i$ 步到 $(X,Y)$ 的走法。通过枚举在 $X$ 轴上走错的步数 $j$ 得到:

$$f_i=\sum_{j=0}^{i}C_{X+Y+2\times i}^{X+i-j,i-j,Y+j,j}$$

注：这里 $C_N^{a,b,c,d\dots}$ 表示 $N$ 中取 $a$ 个，再从剩下的中取 $b$ 个，以此类推。

$\text{ans} =\sum_{i=0}^{\frac{N-X-Y-Z}{2}}f_i\times C_{N-X-Y-2\times i}^{\frac{N-X-Y-Z-2\times i}{2}}\times C_{N}^{N-X-Y-2\times i}$

但是此时时间是 $O(N^2)$ 的，显然过不去，所以我们要优化式子。

我们观察原式：

$$\sum_{j=0}^{i}C^{X+i-j,i-j,Y+j,j}_{X+Y+2\times i}$$

发现好像 $X+i-j$ 与 $Y+j$ 一组， $i-j$ 与 $j$ 一组，每组相加都可以消除需要枚举的 $j$。原式可以化为：

$$\sum_{j=0}^{i}C^{X+i-j,Y+j}_{X+Y+2\times i}\times C_i^j$$

然后拆开得到：

$$\sum_{j=0}^{i}C_{X+Y+2\times i}^{X+Y+i}\times C_{X+Y+i}^{X+i-j}\times C_i^j$$

发现左边与 $j$ 无关，于是原式变为：

$$C_{X+Y+2\times i}^{X+Y+i}\times\sum_{j=0}^{i} C_{X+Y+i}^{X+i-j}\times C_i^j$$

关注求和右侧的式子，可以理解为第一组有 $X+Y+i$ 块石头，第二组有 $i$ 块石头，现在要从第二组中拿出 $j$ 块石头，从第一组中拿出 $X+i-j$ 块石头。因为一共要拿 $X+i$ 块石头，并且两组一共有 $X+Y+2\times i$ 块石头，显然有 $C_{X+Y+2\times i}^{X+i}$ 种拿法。原式化为下式：

$$C_{X+Y+2\times i}^{X+Y+i}\times C_{X+Y+2\times i}^{X+i}$$

显然 $O(1)$ 可解，那么时间复杂度就变成 $O(N)$ 的了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e7+10,mod=998244353;
inline int power(const int &a,int b){
	int ret=1,num=a%mod;
	while(b){
		if(b&1)ret=ret*num%mod;
		num=num*num%mod;
		b>>=1;
	}
	return ret;
}
int fac[N]={1},inv[N];
int C(int down,int up){
	if(up<0||up>down)return 0;
	return fac[down]*inv[up]%mod*inv[down-up]%mod;
}
int n,x,y,z;
int f[N];
signed main(){
	for(int i=1;i<=1e7;i++){fac[i]=fac[i-1]*i%mod;}
	inv[10000000]=power(fac[10000000],mod-2);
	for(int i=10000000-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	cin>>n>>x>>y>>z;
	x=abs(x);y=abs(y);z=abs(z);
	if(((n-x-y-z)&1)||(n<x+y+z)){cout<<0;return 0;}
	for(int i=0;i<=n&&x+y+2*i<=n-z;i++)f[i]=C(x+y+2*i,x+y+i)*C(x+y+2*i,x+i)%mod;
	int ans=0;
	for(int i=0;i<=(n-x-y-z)/2;i++){
		ans=(ans+f[i]*C(n-x-y-2*i,(n-x-y-z-2*i)/2)%mod*C(n,n-x-y-2*i)%mod)%mod;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：0)

## 题目大意

给定一个坐标 $(x,y,z)$。

每一步可以沿（前后左右上下）进行移动。

求从原点 $(0,0,0)$ 走到这个坐标恰好 $n$ 步的方案数。

## 思路

对于 $(x,y,z)$ 的答案，我们不妨求 $(\left|x\right|,\left |y\right|,\left|z\right|)$。

显然这两个问题答案一致。

下面都已经假定 $x,y,z \ge 0$。

对于 $n < x+y+z$，那么直接没有方案，显然我们最少也得走 $x+y+z$ 步。

那么我们如何计算剩余的情况呢？

我们先思考如何构造方案使得走 $n$ 步。

对于一个维度，我们一定是先走一步再往回退来消耗步数，这是我们发现一次只能消耗偶数步数，那么我们就能得到一个性质：$n$ 与 $x+y+z$ 的奇偶性一致，否则也是没有方案。

我们需回退$k=\frac{n-(x+y+z)}{2}$ 步。

那么我们枚举每个维度回退多少步，就得到了方案数。

注：前方高能预警。

$$\sum^{k}_{i=0}\binom n{x+i}\binom {n-(x+i)} i\sum_{j=0}^{k-i}\binom{n-(x+2i)}{y+j}\binom{n-(n+2i)-(y+j)}j\binom{n-(x+2i)-(y+2j)}{z+k-i-j}$$

我们先算后面~~那坨艺术~~吧！

$$\begin{aligned}&\sum_{j=0}^{k-i}\binom{n-(x+2i)}{y+j}\binom{n-(n+2i)-(y+j)}j\binom{n-(x+2i)-(y+2j)}{z+k-i-j}
\\&=\sum_{j=0}^{k-i} \frac{(n-(x+2i))!}{(y+j)!j!(z+k-i-j)!(n-x-y-z-k-i-j)!} 
\\&\because n-x-y-z=2k
\\&=\sum_{j=0}^{k-i} \frac{(n-(x+2i))!}{(y+j)!j!(z+k-i-j)!(k-i-j)!}
\\&=\sum_{j=0}^{k-i} \frac{(n-(x+2i))!}{(y+j)!j!(z+k-i-j)!(k-i-j)!}
\\
\\&\text{考虑组成新的组合数}
\\
\\&=\sum_{j=0}^{k-i} \frac{(k+y-i)!(z+k-i)!}{(y+j)!j!(z+k-i-j)!(k-i-j)!} \times \frac{(n-(x+2i))!}{(k+y-i)!(z+k-i)!}
\\&=\frac{(n-(x+2i))!}{(k+y-i)!(z+k-i)!}\sum_{j=0}^{k-i} \binom{k+y-i}{y+j}\binom{z+k-i}{z+k-i-j}
\\
\\&\text{使用蒙德范德卷积}
\\
\\&=\frac{(n-(x+2i))!}{(k+y-i)!(z+k-i)!}\binom{z+y+2k-2i}{z+y+k-i}
\end{aligned}$$

$$ \text{原式}= \sum^{k}_{i=0} \binom {n}{x+i} \binom {n-(x+i)}{i}\binom{z+y+2k-2i}{z+y+k-i}\frac{(n-(x+2i))!}{(k+y-i)!(z+k-i)!}$$

我们预处理阶乘和逆元，然后就可以 $O(n)$ 解决了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=3e7+5;
const long long mod=998244353;
int x,y,z,n;
long long inv[N],fac[N];
long long C(long long n,long long m){
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
	cin>>n>>x>>y>>z;
	x=abs(x);
	y=abs(y);
	z=abs(z);
	if((n&1)!=((x+y+z)&1)){
		cout<<"0"<<endl;
		return 0;
	}
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=3e7;i++){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	}
	for(int i=2;i<=3e7;i++)inv[i]=inv[i-1]*inv[i]%mod;
	long long ans=0,k=(n-x-y-z)/2;
	for(int i=0;i<=k;i++){
		ans=(ans+C(n,x+i)*C(n-x-i,i)%mod*fac[n-x-2*i]%mod*inv[k+y-i]%mod*inv[k+z-i]%mod*C(2*k+y+z-2*i,k+y+z-i)%mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：pokefunc (赞：0)

题意：求在三维空间内从原点出发走 $n$ 步抵达 $(x,y,z)$ 的方案数。每步只能沿一个维度的一个方向走单位长度。

$n,x,y,z \le 5 \times 10^7$。

容易发现坐标可以直接取绝对值而不影响答案。

$n<x+y+z$ 或 $n-x-y-z$ 为奇数时显然无解。

考虑 $n \ge x+y+z$ 时我们如何消耗掉多出的步数，显然是任选一个方向走一步再退回来。

设 $w=\frac{n-x-y-z}2$，那么每一维都需要枚举它要向反方向走多少步，得到

$$
\sum_{i=0}^{w}\dbinom{n}{x+2i} \dbinom{x+2i}{i}\sum_{j=0}^{w-i} \dbinom{n-x-2i}{y+2j} \dbinom{y+2j}{j}\dbinom{n-x-2i-y-2j}{z+2w-2i-2j}\dbinom{z+2w-2i-2j}{w-i-j}
$$

~~真是吓人呢~~

拆一下后面部分拆成阶乘：

$$
\begin{aligned}
&\sum_{j=0}^{w-i} \dbinom{n-x-2i}{y+2j} \dbinom{y+2j}{j}\dbinom{n-x-2i-y-2j}{z+2w-2i-2j}\dbinom{z+2w-2i-2j}{w-i-j}\\
&=\sum_{j=0}^{w-i} \frac{(n-x-2i)!}{j!(y+j)!(w-i-j)!(z+w-i-j)!}
\end{aligned}
$$

提出与 $j$ 无关的项然后开始重组：

$$
\begin{aligned}
&(n-x-2i)!\sum_{j=0}^{w-i} \frac{1}{j!(y+j)!(w-i-j)!(z+w-i-j)!}
\\
&= \frac{(n-x-2i)!}{(z+w-i)!(w-i+y)!}\sum_{j=0}^{w-i}\frac{(z+w-i)!}{j!(z+w-i-j)!}\frac{(w-i+y)!}{(y+j)!(w-i-j)!} \\
&= \frac{(n-x-2i)!}{(z+w-i)!(w-i+y)!}\sum_{j=0}^{w-i}\dbinom{w+z-i}{j}\dbinom{w-i+y}{w-i-j}
\end{aligned}
$$

观察后面的部分，可以发现就是一个下指标卷积，最终得到

$$
\frac{(n-x-2i)!}{(z+w-i)!(w-i+y)!}\dbinom{2w-2i+y+z}{w-i}
$$

直接计算即可。时间复杂度线性。

码丑勿喷。

```cpp
#include<bits/stdc++.h>
using std::vector;
#define int long long
typedef vector<int> vi;
typedef long long ll;
const int Mod=998244353;
template<typename Tp=int>inline Tp read(){Tp x(0);int op(0);char ch=getchar();while(ch<'0'||ch>'9')op|=(ch==45),ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();return op?-x:x;}

inline int ksm(int x,int y){
	int ans=1;
	for(;y;y>>=1,x=x*x%Mod)if(y&1)ans=ans*x%Mod;
	return ans;
}

signed main(){
	int n=read(),x=abs(read()),y=abs(read()),z=abs(read());
	if(n<x+y+z||(n-x-y-z)%2!=0)return puts("0"),0;
	int w=(n-x-y-z)/2;
	vi fac(n+1),inv(n+1);
	fac[0]=fac[1]=1;
	for(int i=2;i<=n;++i)fac[i]=fac[i-1]*i%Mod;
	inv[n]=ksm(fac[n],Mod-2);
	for(int i=n-1;~i;--i)inv[i]=inv[i+1]*(i+1)%Mod;
	auto C=[fac,inv](int x,int y){return x>=0&&y>=0&&x>=y?fac[x]*inv[y]%Mod*inv[x-y]%Mod:0;};
	int ans=0;
	for(int i=0;i<=w;++i){
		int W=fac[n-x-2*i]*inv[z+w-i]%Mod*inv[w-i+y]%Mod*C(2*w-2*i+y+z,w-i)%Mod;
		(ans+=W*C(n,x+2*i)%Mod*C(x+2*i,i)%Mod)%=Mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

