# 「MCOI-06」Lost Desire

## 题目背景

頰滴る　紅い涙

不安定な視界の中

差し出した手を取れたら

あぁ…そんな世界を夢みた

-------

哭いて…

激しく  燃やした 黒い感情 

届かぬ この手に

Cry 闇の中で

最果てから 光へ手を翳して

揺らいだ想いさえも 闇の奥底へ堕ちてく

[网易云本曲试听链接](https://music.163.com/song?id=1809745288&userid=1399272307)

## 题目描述

设正整数 $n, m$ 互质，$k$ 为整数，定义函数 $F(n, m, k)$ 为小于 $\displaystyle m+n$ 的正整数集合 $\{1, 2, \cdots, m + n - 1\}$ 中，所有满足 $\displaystyle\sum_{x \in S} x \equiv k \pmod n$ 的 $m$ 元子集 $S$ 的个数。

现给定正整数 $N, M, K$，求所有 $F(i,j,x)$ 之积，使得 $1\le i\le N$，$1\le j\le M$，$1\le x\le K$，并且 $i$ 与 $j$ 互质。

由于结果很大，所以你只需要求出结果对特定素数 $p$ 取模的值。

**同时请注意实现程序时常数因子带来的影响。**

## 说明/提示

本题采用捆绑测试，分 $5$ 个 Subtask 。

+ 对于 Subtask 1 ~~(Tutorial)~~：
  + $T=1$
  + $1\leq N,M,K\leq 6$
  + $p=10^9+7$。
+ 对于 Subtask 2 ~~(PST 4.0)~~：
  + $T=1$
  + $1\leq N,M,K\leq200$
  + $p=10^9+7$。
+ 对于 Subtask 3 ~~(PRS 7.5)~~：
  + $T=100$
  + $1\leq N,M,K\leq 1000$
  + $p=10^9+7$。
+ 对于 Subtask 4 ~~(FTR 9.8)~~：
  + $T=10^3$
  + $1 \leq N,M,K\le 10^5$
  + $10^9\le p\le2\times10^9$。
+ 对于 Subtask 5 ~~(BYD 11.0)~~：
  + $T=9999$
  + $1 \leq N,M,K\le 5\times10^5$
  + $10^9\le p\le2\times10^9$。

Subtask $1\sim5$ 的分值分别为 $5,7,11,17,60$ 。

特别的，假设您在一个测试点中前 $x$ 个询问正确，则您得该测试点的分值的 $\left\lfloor100\times\sqrt\dfrac{x}{T}\right\rfloor\%$ 分。您在任何一个 Subtask 的得分则为对应 Subtask 中所有测试点得分的最小值。

特别的，**TLE 一律不得分。**（无需补满未在时间范围内解决的测试点的答案，会导致奇怪的错误。）

**再次提醒注意实现程序时常数因子带来的影响。**

---

Idea: Powerless Std&Data: w33z （Data was corrected on 2021.10.05）

Sub4 added by Prean, Sub 5 by w33z.

This problem was added on 2021.10.01. Thanks for their help.

2021.10.01 - 2021.12.07 : 68 days 1st kill (Leasier).

2021.10.01 - 2022.01.21 : 113 days 2nd kill (wkywkywky).

2021.10.01 - 2022.02.26 : 149 days 3rd kill (NaNH2).

## 样例 #1

### 输入

```
3 1926195307
2 3 3
3 3 3
5 6 1```

### 输出

```
8
64
363031200```

# 题解

## 作者：Prean (赞：11)

[前置芝士](https://www.luogu.com.cn/paste/2jowtv8m)的光速幂技巧。

本题解不是正解，和正解唯一的差别在于对幂的处理。

我们能够发现有：
$$ F(n,m,k)=\frac 1 n \binom {n+m-1} m $$
证明见[这里](https://www.luogu.com.cn/paste/mvhuutmb)。

然后我们开始推柿子：
$$ \prod_{i=1}^n\prod_{j=1}^m\prod_{x=0}^k(\frac 1 i \binom {i+j-1} j )^{[\gcd(i,j)=1]} $$
$$ (\prod_{i=1}^n\prod_{j=1}^m(\frac {(i+j-1)!} {i!j!})^{[\gcd(i,j)=1]})^{k+1} $$
此时我们可以把答案拆成两部分：
$$ \prod_{i=1}^n\prod_{j=1}^m((i+j-1)!)^{[\gcd(i,j)=1]} $$
$$ \prod_{i=1}^n\prod_{j=1}^m(i!j!)^{[\gcd(i,j)=1]} $$

## 1

$$ \prod_{i=1}^n\prod_{j=1}^m((i+j-1)!)^{\sum_{d|i,d|j}\mu(d)} $$
$$ \prod_{d=1}^n\prod_{i=1}^{\lfloor \frac n d \rfloor}\prod_{j=1}^{\lfloor \frac m d \rfloor} (di+dj-1)!^{\mu(d)} $$
$$ \prod_{d=1}^n\prod_{i=1}^{\lfloor \frac n d \rfloor}\prod_{j=1}^{\lfloor \frac m d \rfloor} \frac {(d(i+j))!^{\mu(d)}} {(d(i+j))^{\mu(d)}} $$

## 1.1

$$ \prod_{d=1}^n\prod_{i=1}^{\lfloor \frac n d \rfloor}\prod_{j=1}^{\lfloor \frac m d \rfloor} {(d(i+j))!^{\mu(d)}} $$
真正的毒瘤。
$$ \prod_{d=1}^n\prod_{k=1}^{{\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor}}(dk)!^{num_{{\lfloor \frac n d \rfloor},{\lfloor \frac m d \rfloor}}[k]\mu(d)} $$
$$ \prod_{d=1}^n\prod_{k=1}^{\lfloor \frac n d \rfloor}(dk)!^{(k-1)\mu(d)} \times\prod_{k={\lfloor \frac n d \rfloor}+1}^{{\lfloor \frac m d \rfloor}} (dk)!^{{\lfloor \frac n d \rfloor}\mu(d)} \times \prod_{k={\lfloor \frac m d \rfloor}+1}^{{\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor}} (dk)!^{({\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor}-k+1)\mu(d)} $$

## 1.1.1

$$ \prod_{d=1}^n\prod_{k=1}^{\lfloor \frac n d \rfloor} (dk)!^{(k-1)\mu(d)} $$
$$ \prod_{d=1}^nd!^{\sum_{k|d} k \mu(\frac d k)} \div \prod_{d=1}^n d!^{\sum_{k|d}\mu(\frac d k)} $$
$$ \prod_{d=1}^nd!^{\varphi(d)} $$

有趣的一点是，这玩意儿和 $ \prod_{d=1}^n\prod_{k=1}^{\lfloor \frac n d \rfloor} (dk)!^{k\mu(d)} $ 是一个东西。以及这玩意儿和后面的 $ 1.1.3.1 $ 是一样的，所以可以不用推。。。

## 1.1.2

$$ \prod_{d=1}^n\prod_{k={\lfloor \frac n d \rfloor}+1}^{\lfloor \frac m d \rfloor} (dk)^{{\lfloor \frac n d \rfloor}\mu(d)} $$
$$ \prod_{d=1}^n\prod_{k=1}^{\lfloor \frac m d \rfloor} (dk)^{{\lfloor \frac n d \rfloor}\mu(d)} \div \prod_{k=1}^{\lfloor \frac n d \rfloor} (dk)!^{{\lfloor \frac n d \rfloor}\mu(d)} $$
右边：
$$ \prod_{d=1}^n\prod_{k=1}^{\lfloor \frac n d \rfloor} (dk)!^{\mu(d){\lfloor \frac n d \rfloor}} $$
$$ \prod_{d=1}^n(\prod_{k=1}^{\lfloor \frac n d \rfloor} (dk)!^{\mu(d)})^{\lfloor \frac n d \rfloor} $$
设：
$$ f_1(d,n)=\prod_{k=1}^n(dk)!^{\mu(d)} $$
可以发现：
$$ f_1(d,n)=f_1(d,n-1) \times (dn)!^{\mu(d)} $$
$ (dn)!^{mu(d)} $ 用光速幂搞定，（这里的 $ dn $ 一定不大于数据范围）就可以 $ O(n \log n) $ 递推 $ f_1 $ 了。

这一部分最终能够推得：
$$ \prod_{d=1}^n f_1(d,{\lfloor \frac n d \rfloor})^{\lfloor \frac n d \rfloor} $$
对 $ f_1 $ 在第二维度上做前缀积即可整除分块带走。

左边的和右边的是一样的，就不再论述了。

## 1.1.3

$$ \prod_{d=1}^n\prod_{k={\lfloor \frac m d \rfloor}+1}^{{\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor}} (dk)!^{({\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor}-k+1)\mu(d)} $$
它 是 毒 瘤

首先拆一下：
$$ \prod_{d=1}^n((\prod_{k=1}^{{\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor}} (dk)!^{({\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor})\mu(d)} \div \prod_{k=1}^{\lfloor \frac m d \rfloor} (dk)!^{({\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor})\mu(d)}) $$

$$  \div (\prod_{k=1}^{{\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor}} (dk)!^{k\mu(d)} \div \prod_{k=1}^{\lfloor \frac m d \rfloor} (dk)!^{k\mu(d)}) $$

$$ \times (\prod_{k=1}^{{\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor}} (dk)!^{\mu(d)} \div \prod_{k=1}^{\lfloor \frac m d \rfloor} (dk)!^{\mu(d)})) $$
后面四个好像容易一些，先搞后面四个。

## 1.1.3.1

$$ \prod_{d=1}^n\prod_{k=1}^{\lfloor \frac m d \rfloor}(dk)!^{k\mu(d)} $$
设：
$$ f_2(d,n)=\prod_{k=1}^n(dk)!^{k\mu(d)} $$
明显有：
$$ f_2(d,n)=f_2(d,n-1) \times (dn)!^{n\mu(d)} $$
和 $ f_1 $ 一样即可以 $ O(n\log n) $ 处理这玩意儿。

## 1.1.3.2

$$ \prod_{d=1}^n\prod_{k=1}^{\lfloor \frac m d \rfloor} (dk)!^{\mu(d)} $$
你发现这玩意儿就是 $ f_1 $，所以可以直接草了。

## 1.1.3.3

$$ \prod_{d=1}^n\prod_{k=1}^{\lfloor \frac m d \rfloor} (dk)!^{({\lfloor \frac n d \rfloor}+{\lfloor \frac m d \rfloor})\mu(d)} $$

这玩意儿好像就只是 $ f_1 $ 加上了一个幂？用一个光速幂就可以带走了。

## 1.2

$$ \prod_{d=1}^n\prod_{i=1}^{\lfloor \frac n d \rfloor}\prod_{j=1}^{\lfloor \frac m d \rfloor} {(d(i+j))^{\mu(d)}} $$

这一部分几乎和 $ 1.1 $ 是相同的，所以不再论述，将 $ (dk)! $ 换成 $ (dk) $ 即可。

## 2

$$ \prod_{i=1}^n\prod_{j=1}^m(i!j!)^{\sum_{d|i,d|j} \mu(d)} $$
其实这一部分明显比前面简单得多，以至于我前面刚写完就以为整个题解写完了（
$$ \prod_{d=1}^n\prod_{i=1}^{\lfloor \frac n d \rfloor}\prod_{i=1}^{\lfloor \frac m d \rfloor}(di)!^{\mu(d)}(dj)!^{\mu(d)} $$
$$ \prod_{d=1}^n(\prod_{i=1}^{\lfloor \frac n d \rfloor}(di)!^{\mu(d){\lfloor \frac m d \rfloor}} \times \prod_{i=1}^{\lfloor \frac m d \rfloor}(dj)!^{\mu(d){\lfloor \frac n d \rfloor}}) $$
$$ \prod_{d=1}^n(\prod_{i=1}^{\lfloor \frac n d \rfloor} (di)!^{\mu(d)})^{\lfloor \frac m d \rfloor} \times (\prod_{d=1}^n \prod_{j=1}^{\lfloor \frac m d \rfloor} (dj)!^{\mu(d)})^{\lfloor \frac n d \rfloor} $$

我们发现这玩意儿就是 $ f_3 $，直接光速幂即可。

虽然复杂度是 $ O(n^{\frac 5 4}\log n+T\sqrt n) $ 的，但是常数巨大。。。

以及，光速幂空间过大，所以可能需要 $ \rm vector $ 来实现，以及离线卡常。

来想想需要对哪些东西预处理光速幂

$ f_1 $和 $ 1.2 $ 中的 “$ f_1 $”。长度分别为 $ O(n\log n) $ 和 $ O(n\log n) $。

对二者同时光速幂。注意光速幂离线后一共有 $ O(n\log n) $ 个底数，对其分块后可以卡进 cache，对上面的二者同步预处理光速幂即可。

---

## 作者：飞雨烟雁 (赞：7)

本题解旨在提供一种简洁的推导方法，~~减少各位的脑细胞的损耗~~。

------------

在此题解中，我们约定：

$$F^ * (x)=\prod_{i=1}^xF(i)$$

$$F^ {* * } (x)=\prod_{i=1}^xF^*(i)$$

即 $F^ * (x)$ 相当于对 $F(x)$ 做一次前缀积，$F^{* * }(x)$ 就是对 $F(x)$ 做两次前缀积。

那么我们就有 **定理** $1$：

$$
\prod_{i=1}^n\prod_{j=1}^mF(i+j)=\prod_{i=1}^n\dfrac{F^* (i+m)}{F^* (i)}=\dfrac{F^{* * }(n + m)}{F^{* * }(n)F^{* * }(m)}
$$

同样地，在 $\sum$ 中也有类似结论。

------------

注：以下推导省略向下取整符号 $\lfloor\rfloor$。

接下来开始推式子，假设 $n\le m$，先看分子部分：

$$
\begin{aligned}
\prod_{i=1}^n\prod_{j=1}^m(i+j-1)!^{[i\perp j]}=\prod_{d=1}^n\prod_{i=1}^{n/d}\prod_{j=1}^{m/d}[d(i+j)-1]!^{\mu(d)}
\end{aligned}
$$

设 $F_d(x)=(dx-1)!^{\mu(d)}$，那么由定理 $1$ 得：

$$
\begin{aligned}\prod_{d=1}^n\prod_{i=1}^{n/d}\prod_{j=1}^{m/d}[d(i+j)-1]!^{\mu(d)}=\prod_{d=1}^n\dfrac{F^{* * }_ d (\frac nd+\frac md)}{F^{* * }_ d(\frac nd)F^{* * }_ d(\frac md)}
\end{aligned}
$$

这样分子就算推完了，接下来是分母：

$$\prod_{i=1}^n\prod_{j=1}^m(i!j!)^{[i\perp j]}=\prod_{d=1}^n\prod_{i=1}^{n/d}\prod_{j=1}^{m/d}[(di)!(dj)!]^{\mu(d)}$$

记 $G_d(x)=(dx)!^{\mu(d)}$，则：

$$\prod_{d=1}^n\prod_{i=1}^{n/d}\prod_{j=1}^{m/d}[(di)!(dj)!]^{\mu(d)}=\prod_{d=1}^nG_d^* (\frac nd)^{\frac md}G_d^ * (\frac md)^{\frac nd}$$

把分子分母结合起来，就可以得到：

$$\prod_{d=1}^n\dfrac{F^{* * }_ d (\frac nd+\frac md)}{F^{* * }_ d(\frac nd)F^{* * }_ d(\frac md)G_d^* (\frac nd)^{\frac md}G_d^ * (\frac md)^{\frac nd}}$$

为了能够整除分块，我们设：

$$H_d(x)=\prod_{i=1}^dF_i^{* * }(x)$$
$$L_d(x)=\prod_{i=1}^dG_i^* (x)$$

那么对于整除分块中的区间 $[l,r]$，其计算式就是：

$$\dfrac{H_ r(\frac nl+\frac ml)H_ {l-1}(\frac nl)H_ {l-1}(\frac ml)L_{l-1} (\frac nl)^{\frac ml}L_{l-1}(\frac ml)^{\frac nl}}{H_ {l-1}(\frac nl+\frac ml)H_ r(\frac nl)H_ r(\frac ml)L_r (\frac nl)^{\frac ml}L_r (\frac ml)^{\frac nl}}$$

------------

那么我们只需计算出所有需要的 $H_d(x),L_d(x)$，再加上整除分块，就能在 $O(n\ln n+T\sqrt n\log n)$ 的时间复杂度内完成计算。

如果再加上 Index Calculus 或其他求离散对数的算法，那就可以通过此题了。

以下给出一个只能过前四个 Subtask 的代码，仅供参考 or 对拍：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;

int Read(){
    int res = 0; char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') res = res * 10 + (c ^ 48), c = getchar();
    return res;
}
void Write(int x){ if(x > 9) Write(x / 10); putchar(48 ^ (x % 10));}

const int Mx = 1e6 + 1, Nx = 13970040;
int Mod;

int FastPow(ll a, int b){
	int res = 1;
	while(b){
		if(b & 1) res = res * a % Mod;
		b >>= 1, a = a * a % Mod;
	}
	return res;
}

bool Vis[Mx];
int Prime[78500], tot, Miu[Mx];
int Frac[Mx], Infs[Mx];
int St[Mx];
int MF[Nx], MG[Nx];
void TestifyInit(){
	Miu[1] = Frac[0] = Frac[1] = 1;
	for(int i = 2; i < Mx; ++i){
		if(!Vis[i]) Prime[++tot] = i, Miu[i] = -1;
		for(int j = 1; j <= tot && Prime[j] * i < Mx; ++j){
			Vis[i * Prime[j]] = 1;
			if(i % Prime[j] == 0) break;
			Miu[i * Prime[j]] = -Miu[i];
		}
		Frac[i] = 1ll * Frac[i - 1] * i % Mod;
	}
	St[1] = -1, Infs[Mx - 1] = FastPow(Frac[Mx - 1], Mod - 2);
	for(int i = 1; i < Mx - 1; ++i) St[i + 1] = St[i] + (Mx - 1) / i;
	for(int i = Mx - 1; i; --i) Infs[i - 1] = 1ll * Infs[i] * i % Mod;
	for(int d = 1; d < Mx; ++d){
		int lim = St[d] + (Mx - 1) / d;
		if(Miu[d] & 2){
			MF[St[d] + 1] = Infs[d], MG[St[d] + 1] = Infs[d - 1];
			for(int x = St[d] + 2, t = d; x <= lim; ++x){
				MF[x] = 1ll * Infs[t += d] * MF[x - 1] % Mod;
				MG[x] = 1ll * Infs[t - 1] * MG[x - 1] % Mod;
			}
			for(int x = St[d] + 2; x <= lim; ++x) MG[x] = 1ll * MG[x] * MG[x - 1] % Mod;
		}
		else if(Miu[d]){
			MF[St[d] + 1] = Frac[d], MG[St[d] + 1] = Frac[d - 1];
			for(int x = St[d] + 2, t = d; x <= lim; ++x){
				MF[x] = 1ll * Frac[t += d] * MF[x - 1] % Mod;
				MG[x] = 1ll * Frac[t - 1] * MG[x - 1] % Mod;
			}
			for(int x = St[d] + 2; x <= lim; ++x) MG[x] = 1ll * MG[x] * MG[x - 1] % Mod;
		}
		else for(int x = St[d] + 1; x <= lim; ++x) MF[x] = MG[x] = 1;
	}
	for(int d = 2; d < Mx; ++d){
		int lim = St[d] + (Mx - 1) / d;
		for(int x = St[d] + 1, y = St[d - 1] + 1; x <= lim; ++x, ++y)
			MF[x] = 1ll * MF[x] * MF[y] % Mod, MG[x] = 1ll * MG[x] * MG[y] % Mod;
	}
}

int main(){
	int T = Read(); Mod = Read();
	TestifyInit();
	while(T--){
		int n = Read(), m = Read(), k = Read();
		if(n > m) swap(n, m);
		int A = MG[n + m - 1];
		int B = 1ll * MG[n - 1] * MG[m - 1] % Mod * FastPow(MF[n - 1], m) % Mod * FastPow(MF[m - 1], n) % Mod; // Ans = A / B
		for(int l = 2, r; l <= n; l = r + 1){
			int N = n / l, M = m / l;
			r = min(n / N, m / M);
			A = 1ll * A * MG[St[r] + N + M] % Mod
					* MG[St[l - 1] + N] % Mod
					* MG[St[l - 1] + M] % Mod
					* FastPow(MF[St[l - 1] + N], M) % Mod
					* FastPow(MF[St[l - 1] + M], N) % Mod;
			B = 1ll * B * MG[St[l - 1] + N + M] % Mod
					* MG[St[r] + N] % Mod
					* MG[St[r] + M] % Mod
					* FastPow(MF[St[r] + N], M) % Mod
					* FastPow(MF[St[r] + M], N) % Mod;
		}
		printf("%d\n", FastPow(1ll * A * FastPow(B, Mod - 2) % Mod, k));
	}
	return 0;
}
```

---

## 作者：wkywkywky (赞：5)

感觉这题推导挺 trivial，所以决定只讲下一种绕开光速幂和 Index Calculus 算法的做法。

下记 $a$ 在模 $p$ 意义下的离散对数为 $\log_g{a}$，其中 $g$ 为 $p$ 的一个原根。

不加证明的给出两个显然的引理。

-  Lemma 1: $\log_g{ab}\equiv(\log_g{a}+\log_g{b})\pmod{\varphi(p)}$

-  Lemma 2: $x(\left\lfloor\dfrac{p}{x}\right\rfloor+1)\equiv x-(p\bmod{x})\pmod{p}$

根据引理 1,2 当 $x>\sqrt{p}$ 时有：

$$\log_g{x}\equiv\log_{g}{(x-(p\bmod{x}))}-\log_g{(\left\lfloor\dfrac{p}{x}\right\rfloor+1)}\pmod{\varphi(p)}$$

所以当 $x>\sqrt{p}$ 时可以 $O(1)$ 递推求出 $\log_{g}x$ 的值。

由 Lemma 1 知 $\log_g{x}$ 为完全加性函数，故只要求出素数点处值。

综上，只需求所有小于 $\sqrt{p}$ 的素数的原根。

考虑 BSGS 算法本质，用 $O(B)$ 预处理，每次询问 $O(\frac{p}{B})$ 的复杂度。

平衡下复杂度：

令 $B=\frac{p}{B}\frac{\sqrt{p}}{\ln{p}}$，解得 $B=\frac{p^\frac{3}{4}}{\sqrt{\ln{p}}}$。

求前 $n$ 个数的离散对数总复杂度为 $O(\frac{p^\frac{3}{4}}{\sqrt{\ln{p}}}+n)$。

应出题人不放代码，本人不保证这篇题解做法能稳定通过，读者应自行卡常（

---

## 作者：Leasier (赞：5)

前置芝士：[莫比乌斯反演](https://oi-wiki.org/math/number-theory/mobius/)、[Index Calculus 算法](https://www.luogu.com.cn/blog/Leasier/Index-Calculus)

**Warning：本题极为卡常。~~常数跟我一样巨大的人慎入。~~**

首先考虑 $F$ 函数。打表可得：$F(n, m, k) = \frac{C_{n + m - 1}^{m}}{n} = \frac{(n + m - 1)!}{n! m!}$。

~~放一份出题人的证明：https://www.luogu.com.cn/paste/mvhuutmb。~~

令 $F'(n, m) = F(n, m, k)$，有：

原式 $= (\displaystyle\prod_{i = 1}^N \prod_{j = 1}^M F'(i, j)^{[\gcd(i, j) = 1]})^K$

$ = (\displaystyle\prod_{i = 1}^N \prod_{j = 1}^M (\frac{(i + j - 1)!}{i!j!})^{[\gcd(i, j) = 1]})^K$

考虑将分子和分母分开处理。

1. 计算 $\displaystyle\prod_{i = 1}^N \prod_{j = 1}^M ((i + j - 1)!)^{[\gcd(i, j) = 1]}$

原式 $= \displaystyle\prod_{i = 1}^N \prod_{j = 1}^M ((i + j - 1)!)^{\displaystyle\sum_{d \mid \gcd(i, j)} \mu(d)}$

$ = \displaystyle\prod_{d = 1}^{\min(N, M)} (\prod_{d \mid i}^N \prod_{d \mid j}^M (i + j - 1)!)^{\mu(d)}$

$ = \displaystyle\prod_{d = 1}^{\min(N, M)} (\prod_{i = 1}^{\lfloor \frac{N}{d} \rfloor} \prod_{j = 1}^{\lfloor \frac{M}{d} \rfloor} (d(i + j) - 1)!)^{\mu(d)}$

$ = \displaystyle\prod_{d = 1}^{\min(N, M)} (\prod_{q = 1}^{\lfloor \frac{N}{d} \rfloor + \lfloor \frac{M}{d} \rfloor} (dq - 1)!^{\displaystyle\sum_{i = 1}^{\lfloor \frac{N}{d} \rfloor} \sum_{j = 1}^{\lfloor \frac{M}{d} \rfloor} [i + j = q]})^{\mu(d)}$

$ = \displaystyle\prod_{d = 1}^{\min(N, M)} ((\prod_{q = 1}^{\lfloor \frac{\min(N, M)}{d} \rfloor} ((dq - 1)!)^{q - 1}) (\prod_{q = \lfloor \frac{\min(N, M)}{d} \rfloor + 1}^{\lfloor \frac{\max(N, M)}{d} \rfloor} (dq - 1)!)^{\lfloor \frac{\min(N, M)}{d} \rfloor} (\prod_{q = \lfloor \frac{\max(N, M)}{d} \rfloor + 1}^{\lfloor \frac{N}{d}                        \rfloor + \lfloor \frac{M}{d} \rfloor} ((dq - 1)!)^{\lfloor \frac{N}{d} \rfloor + \lfloor \frac{M}{d} \rfloor - q + 1}))^{\mu(d)}$

将阶乘拆开（即 $(i - 1)! = \frac{i!}{i}$）并预处理 $f_{n, m} = \displaystyle\prod_{i = 1}^n (im)!$ 和 $g_{n, m} = \displaystyle\prod_{i = 1}^n ((im)!)^i$ 以及 $f'_{n, m} = \displaystyle\prod_{i = 1}^n f_{n, i}^{\mu(i)}$ 和 $g'_{n, m} = \displaystyle\prod_{i = 1}^n g_{n, i}^{\mu(i)}$ 以数论分块即可。

由于本题卡时间，建议用上你所能想到的一切卡常方式并用暴力处理一部分数论分块中 $l, r$ 较小的部分。

由于本题卡时间和空间，建议手写内存池并使用离线使得 $f, f'$ 和 $g, g'$ 能使用同一个数组进行转移。

2. 计算 $\displaystyle\prod_{i = 1}^N \prod_{j = 1}^M (i!j!)^{[\gcd(i, j) = 1]}$

原式 $= \displaystyle\prod_{i = 1}^N \prod_{j = 1}^M (i!j!)^{\displaystyle\sum_{d \mid \gcd(i, j)} \mu(d)}$

$ = \displaystyle\prod_{d = 1}^{\min(N, M)} (\prod_{d \mid i}^N \prod_{d \mid j}^M (i!j!))^{\mu(d)}$

$ = \displaystyle\prod_{d = 1}^{\min(N, M)} (\prod_{i = 1}^{\lfloor \frac{N}{d} \rfloor} \prod_{j = 1}^{\lfloor \frac{M}{d} \rfloor} (id)!(jd)!)^{\mu(d)}$

$ = \displaystyle\prod_{d = 1}^{\min(N, M)} ((\prod_{i = 1}^{\lfloor \frac{N}{d} \rfloor} (id!))^{\lfloor \frac{M}{d} \rfloor} (\prod_{i = 1}^{\lfloor \frac{M}{d} \rfloor} (id!))^{\lfloor \frac{N}{d} \rfloor})^{\mu(d)}$

3. 实现上的问题

容易发现，如果不使用光速幂，这样做的时间复杂度为 $O(T \sqrt{\min(n, m)} (\log n + \log m) + N \log N \ln N)$，而且乘法和取模常数极大。即使使用光速幂，时间复杂度也只会降到 $O(TM \sqrt{\min(n, m)} + M N^{1 + \frac{1}{2^{M - 1}}} \ln N)$，而且常数将会变得更大。

发现 $p$ 为质数，于是直接上 Index Calculus 算法求出前缀离散对数，将乘法变为加法即可。

~~你还需要有极大的耐心。~~

时间复杂度为 $O(T \sqrt{\min(n, m)} + \sqrt{p} + \alpha \beta^{\beta} (\frac{M}{\ln M})^2 + \alpha(\frac{M}{\ln M})^3 \log p + \frac{\alpha^{\alpha} NM}{\ln N \ln M} + N \ln N)$。

Update：为防止贺题，代码就不放了，而且我也不能保证我的代码随时可以 AC（

---

## 作者：cforrest (赞：0)

提供另一种推式子的方法。

如同其他题解解释的那样，求出原根 $g$ 后，问题转化为计算离散对数

$$
K\sum_{m=1}^M\sum_{n=1}^N[m\perp n]\log_g\dfrac{(m+n-1)!}{m!n!}.
$$

为简化记号，下令

$$
N_d = \lfloor N/d\rfloor,~M_d=\lfloor M/d\rfloor.
$$

首先，处理分子：(不妨设 $N\le M$)

$$
\begin{aligned}
F_1(M,N)
&= \sum_{m=1}^M\sum_{n=1}^N[m\perp n]\log_g(m+n-1)!\\
&= \sum_d\mu(d)\sum_{m=1}^{M_d}\sum_{n=1}^{N_d}\log_g((m+n)d-1)!\\
&= \sum_d\mu(d)\Bigg(\sum_{s=2}^{N_d}(s-1)+\sum_{N_d+1}^{M_d}{N_d}+\sum_{M_d+1}^{M_d+N_d}(M_d+N_d+1-s)\Bigg)\log_g(sd-1)!.
\end{aligned}
$$

最后一步就是取 $s=m+n$，然后计算每个 $s$ 分别对应的数对 $(m,n)$ 的数目。再令

$$
\begin{aligned}
G_0(S,d) &= \sum_{s=1}^S\log_g(sd-1)!,\\
G_1(S,d) &= \sum_{s=1}^S(s-1)\log_g(sd-1)!,
\end{aligned}
$$

就有

$$
\begin{aligned}
F_1(M,N)
&= \sum_d\mu(d)\Bigg(G_1(N_d,d)+N_d(G_0(M_d,d)-G_0(N_d,d)) \\
&\quad\quad\quad\quad\quad+(M_d+N_d)(G_0(M_d+N_d,d)-G_0(M_d,d))\\
&\quad\quad\quad\quad\quad-(G_1(M_d+N_d,d)-G_1(M_d,d))\Bigg) \\
&=\sum_d\mu(d)\left((M_d+N_d)G_0(M_d+N_d,d)-M_dG_0(M_d,d)-N_dG_0(N_d,d)\right) \\
&\quad+\sum_d\mu(d)\left(G_1(M_d,d)+G_1(N_d,d)-G_1(M_d+N_d,d)\right).
\end{aligned}
$$

所以只需要预处理 $G_0(S,d)$ 和 $G_1(S,d)$，然后计算 $S$ 固定时它们与 $\mu(d)$ 的乘积对 $d$ 的前缀和就可以做数论分块了。

然后，处理分母：

$$
\begin{aligned}
F_2(M,N)&=\sum_{m=1}^M\sum_{n=1}^N[m\perp n](\log_g m!+\log_g n!)\\
&=\sum_d\mu(d)\left(N_d\sum_{s=1}^{M_d}\log_g(sd)!+M_d\sum_{s=1}^{N_d}\log_g(sd)!\right).
\end{aligned}
$$

为避免预处理更多的二维数列，注意到

$$
\sum_{s=1}^{M_d}\log(sd)! = G_0(M_d,d)+\log_g M_d!+M_d\log_g d.
$$

因而，只需要额外再处理 $\mu(d)$ 和 $\mu(d)\log_g d$ 的前缀和即可。

整理下，就有：

$$
\begin{aligned}
&\sum_d\mu(d)(M_d+N_d)\big(G_0(M_d+N_d,d)-G_0(M_d,d)-G_0(N_d,d)\big)\\
&\quad+\sum_d\mu(d)\big(G_1(M_d+N_d,d)-G_1(M_d,d)-G_1(N_d,d)\big)\\
&\quad+\sum_d\mu(d)\big(M_d\log_gN_d!+N_d\log_gM_d!\big)\\
&\quad+\sum_d\mu(d)2M_dN_d\log_gd.
\end{aligned}
$$

虽然形式看起来很整洁，但是跑得并没有更快。仍需要竭尽所能地卡常。

---

