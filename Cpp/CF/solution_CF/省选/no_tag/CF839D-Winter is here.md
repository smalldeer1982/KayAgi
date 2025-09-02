# Winter is here

## 题目描述

Winter is here at the North and the White Walkers are close. John Snow has an army consisting of $ n $ soldiers. While the rest of the world is fighting for the Iron Throne, he is going to get ready for the attack of the White Walkers.

He has created a method to know how strong his army is. Let the $ i $ -th soldier’s strength be $ a_{i} $ . For some $ k $ he calls $ i_{1},i_{2},...,i_{k} $ a clan if $ i_{1}&lt;i_{2}&lt;i_{3}&lt;...&lt;i_{k} $ and $ gcd(a_{i1},a_{i2},...,a_{ik})&gt;1 $ . He calls the strength of that clan $ k·gcd(a_{i1},a_{i2},...,a_{ik}) $ . Then he defines the strength of his army by the sum of strengths of all possible clans.

Your task is to find the strength of his army. As the number may be very large, you have to print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

Greatest common divisor (gcd) of a sequence of integers is the maximum possible integer so that each element of the sequence is divisible by it.

## 说明/提示

In the first sample the clans are $ {1},{2},{1,2} $ so the answer will be $ 1·3+1·3+2·3=12 $

## 样例 #1

### 输入

```
3
3 3 1
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4
2 3 4 6
```

### 输出

```
39
```

# 题解

## 作者：Karnage (赞：17)

# [CF839D Winter is here](http://codeforces.com/contest/839/problem/D)

题意：给定一个序列，定义一个长度为$k$，最大公约数为$gcd \left( gcd \ge 2 \right)$的子序列的权值为$k * gcd$。

对于所有的$k$，求出权值和对$10^9+7$取模后的结果。

## Solution

对于每个长度分别求贡献好像并不很可行，那就考虑枚举$gcd$，然后求贡献。

设$cnt \left[ i \right]$为原序列中$i$出现的次数，$dp \left[ i \right]$为$gcd$为$i$的子序列总长。

发现此时$dp\left[ i \right]$仍不好求，我们可以倒着枚举$i$，先求出所有$i$的倍数$($包括$i )$的子序列长度和，之后再减去多算的部分$($不包括$i)$即可。

那么，假设我们此时已经求出了$i$的倍数个数$cur$，如何求出其$dp$值$($长度和$)$呢？

考虑每个长度$len \left( 1 \le len \le cur \right)$，~~显然~~答案为：


$$ \sum ^{cur} _ {i = 1} \binom {cur} {i} * i = \sum ^{cur} _{i = 1} \frac {cur!*i} {i! \left( cur-  i \right)!} = cur * \sum ^{cur} _{i = 1} \frac {\left( cur - 1 \right)!} {\left( i - 1 \right)! \left( cur - i \right)!} $$
即为
$$ cur * \sum ^{cur - 1} _{i = 0} \binom {cur - 1} {i} $$
也就是
$$cur * 2 ^{cur - 1} $$

这题做完了。

## Code

```cpp
#include <cstdio>
#include <algorithm>

const int N = 1e6 + 5, Mod = 1e9 + 7;
int n, cnt[N], fac[N], dp[N], ans;

int main() {
    scanf("%d", &n);
    for (int i = fac[0] = 1; i <= n; ++i) fac[i] = 2LL * fac[i - 1] % Mod;
    for (int i = 1, x; i <= n; ++i)
        scanf("%d", &x), ++cnt[x];
    for (int i = N - 1; i > 1; --i) {
        int cur = 0;
        for (int j = i; j < N; j += i) cur += cnt[j];
        if (!cur) continue;
        dp[i] = 1LL * fac[cur - 1] * cur % Mod;
        for (int j = i + i; j < N; j += i) dp[i] = (dp[i] - dp[j] + Mod) % Mod;
        ans = (ans + 1LL * dp[i] * i % Mod) % Mod;
    }
    printf("%d\n", ans);
    return 0;
}
```





---

## 作者：Meteorshower_Y (赞：16)

# 食用说明

1. 本篇题解写的较为详细,涉及 "基础" 知识 和 推理性式子较多

2. 此篇为 $O ( n\,\ln\,n )$ 的 **莫比乌斯反演** 做法,时间我做到了 $\;\large9.06 s$ [评测记录](https://www.luogu.com.cn/record/70925790)

3. 若关于其他同做法题解的没有解释的 $K[cnt]$ 会有详细的说明,若为理解 $K[cnt]$ 的求法而来,建议直达 "式子推导" 的 第四步

4. 本题解较长,为节省时间可以选择性食用 

5. 若有错误的地方,欢迎通过私信,留言等方式指正 

6. 祝您用餐愉快

# 题目大意
[题目传送门](https://www.luogu.com.cn/problem/CF839D)  
给定一个长度为 $n$ 的序列, 选取其中的长度为 $k$ 的一段子序列, 若其 $\gcd$ 大于 $1$ , 其权值为 $k\times \gcd$ , 求所有满足条件的子序列的权值和
# 前置知识
1. $C^m_n = C^{m-1}_{n-1} + C^{m}_{n-1}$

2. $\sum^{n}_{i=0} C^i_n= 2^n$

3. $[\gcd(x,y)=1] = \sum_{d|\gcd(x,y)}\mu(d)$

证明过程 :

PS : 若已经 " 透彻 " 则可跳过

Part.1
$$
\small

\begin{aligned}
&\quad\quad C^{m-1}_{n-1}+C^{m}_{n-1}\\

&=\frac{(n-1)!}{(m-1)!(n-m)!}+\frac{(n-1)!}{m!(n-m-1)!}\\

&=\frac{(n-1)!}{\frac{m!}{m}(n-m)!}+\frac{(n-1)!}{m!\frac{(n-m)!}{n-m}}\\

&=\frac{m(n-1)!+(n-m)(n-1)!}{m!(n-m)!}\\

&=\frac{n!}{m!(n-m)!}\\

&=C^m_n\\
\end{aligned}
$$


Part.2
$$
\small

\begin{aligned}
&\quad \sum^{n}_{i=0} C^i_n=\sum^n_{i=0}C^{i-1}_{n-1}+\sum^n_{i=0}C^i_{n-1}\\

&=\sum^{n-1}_{i=0}C^{i}_{n-1}+\sum^{n-1}_{i=0}C^i_{n-1}\\

&=2 \times \sum^{n-1}_{i=0}C^{i}_{n-1}\\
\end{aligned}
$$

令 $f(x)=\sum^{x}_{i=0} C^i_x$  
则 $f(x)=2 \times f(x-1)$  
$\because f(0)=1$  
$\therefore f(x)=2^x $

Part.3
$\mu$函数有个性质 :
$$
\small
\sum_{d|n}\mu(d)=[n=1]
$$
所以就~~显而易见~~了

# 式子推导

**注意事项**  :

**此下的 " 原式 $ = $ " 为方便写为 "    $\Rightarrow$ "**  
**此下的 " 原式 $ = $ " 为方便写为 "  $\Rightarrow$ "**  
**此下的 " 原式 $ = $ " 为方便写为 "  $\Rightarrow$ "**  
~~(重要的事情说三遍)~~

1. 根据题意我们能列出的式子如下:

$$
\sum^{Maxa}_{d=2}d\sum^{n}_{k=1}k\sum_{s_1,s_2...s_k}[\gcd(a_{s_1},a_{s_2}...a_{s_k})=d]
$$
其中 $d$ 枚举的是子序列的 $\gcd$ ,  
 $Maxa$ 是序列中 $a_i$ 的最大值,  
 $k$ 是序列长度,   
而 $s_1,s_2...s_k$ 是选出的 $k$ 个数的下标


$$
\Rightarrow
\sum^{Maxa}_{d=2}d\sum^{n}_{k=1}k\sum_{s_1,s_2...s_k}[\gcd(\frac{a_{s_1}}{d},a_{s_2}...a_{s_k})=1]
$$

2. 我们再把 $\mu$ 函数带进去

$$
\Rightarrow
\sum^{Maxa}_{d=2}d\sum^{n}_{k=1}k\sum_{s_1,s_2...s_k}\sum_{p|\gcd(\frac{a_{s_1}}{d},\frac{a_{s_2}}{d}...\frac{a_{s_k}}{d})}\mu(p)
$$

$$
\Rightarrow
\sum^{Maxa}_{d=2}d\sum^{n}_{k=1}k\sum_{s_1,s_2...s_k}\sum_{dp|\gcd(a_{s_1},a_{s_2}...a_{s_k})}\mu(p)
$$

$$
\Rightarrow
\sum^{Maxa}_{d=2}d\sum^{n}_{k=1}k\sum_{s_1,s_2...s_k}\sum_{p=1}^{\frac{Maxa}{d}}\mu(p)[dp|a_{s_1},dp|a_{s_2}...dp|a_{s_k}]
$$

3. 稍稍整理下式子

$$
\Rightarrow
\sum^{Maxa}_{d=2}d
\sum_{p=1}^{\frac{Maxa}{d}}\mu(p) 
\sum^{n}_{k=1}k\sum_{s_1,s_2...s_k}
[dp|a_{s_1},dp|a_{s_2}...dp|a_{s_k}]
$$

我们先单看这个式子 : 
$$
\small
\sum_{s_1,s_2...s_k}
[dp|a_{s_1},dp|a_{s_2}...dp|a_{s_k}]
$$
其意义可看为 : 在 $n$ 数中选出 $k$ 个数, 并使这 $k$ 个数都为 $dp$ 的倍数的 **组合** 方案数  
$\therefore$ 我们令序列 $a$ 中 $dp$ 的倍数有 $cnt[dp]$ 个 , 则有 ,
$$
\small
\sum_{s_1,s_2...s_k}
[dp|a_{s_1},dp|a_{s_2}...dp|a_{s_k}]
=
C^k_{cnt[dp]}
$$

$$
\therefore 
\Rightarrow
\sum^{Maxa}_{d=2}d
\sum_{p=1}^{\frac{Maxa}{d}}\mu(p) 
\sum^{cnt[dp]}_{k=1}k \, C^k_{cnt[dp]}
$$
注意此时枚举上界也要改为 $cnt[dp]$ ( $k\geqslant cnt[dp] $ 时无意义,它选不出来 QwQ )

4. 对式子及时间复杂度的进一步优化

我们令 :
$$
\small
K[cnt[dp]]=\sum^{cnt[dp]}_{k=1}k \, C^k_{cnt[dp]}
$$

那么 :
$$
\Rightarrow
\sum^{Maxa}_{d=2}d
\sum_{p=1}^{\frac{Maxa}{d}}\mu(p) \, K[cnt[dp]]
$$

也就是说,我们把 $K[\;]$ 数组 预处理出来就好了嘛  
关键是怎么把他 $O(n)$ 搞出来呢  

(1).式子理解 : 
$$
\small
\begin{aligned}
&K[n]=\sum^n_{k=1} k \times C^k_n\\

&\qquad =\sum^n_{k=1}k \times C^{k-1}_{n-1}+\sum^n_{k=1}k \times C^{k}_{n-1}\\

&\qquad =\sum^{n-1}_{k=0}(k+1) \times C^{k}_{n-1}+\sum^n_{k=1}k \times C^{k}_{n-1}\\
\end{aligned}
$$

$k=n$ 时 , $C^{n}_{n-1}$ 无意义, 舍去  
$k=0$ 时 , $0  \times  C^{0}_{n-1}= 0$, 加上 $0$ 对和式的求值并没有影响,会更好运算  
那我们接着上面的式子来算

$$
\small
\begin{aligned}
&\quad \sum^{n-1}_{k=0}(k+1)  \times  C^{k}_{n-1}+\sum^n_{k=1}k  \times  C^{k}_{n-1}\\

&=\sum^{n-1}_{k=0}(k+1)  \times  C^{k}_{n-1}+\sum^{n-1}_{k=0}k  \times  C^{k}_{n-1}\\

&=\sum^{n-1}_{k=0}(2k+1) \times  C^{k}_{n-1}\\

&=2 \times \sum^{n-1}_{k=0}k \times  C^{k}_{n-1}+\sum^{n-1}_{k=0}C^{k}_{n-1}\\

&=2 \times \sum^{n-1}_{k=1}k \times  C^{k}_{n-1}+\sum^{n-1}_{k=0}C^{k}_{n-1}\\

&=2 \times K[n-1] + 2^{n-1}\\
\end{aligned}
$$

(2).~~感性理解~~ : 
$$
\small
\begin{aligned}
&\quad K[n]\\
&=\sum^n_{k=1} k \times C^k_n\\

&=1 \times C^{1}_{n}+2 \times C^{2}_{n}+3 \times C^{3}_{n}+...+(n-1) \times C^{n-1}_{n}+n \times C^{n}_{n}\\

&=(C^{0}_{n-1}+C^{1}_{n-1})+(2 \times C^{1}_{n-1}+2 \times C^{2}_{n-1})+...+[(n-1) \times C^{n-2}_{n-1}+(n-1) \times C^{n-1}_{n-1}]+(n \times C^{n-1}_{n-1}+n \times C^{n}_{n-1})\\

&=1 \times C^0_{n-1}+3 \times C^1_{n-1}+5 \times C^2_{n-1}+...+(2n-1) \times C^{n-1}_{n-1}\\
\end{aligned}
$$

$ (C^n_{n-1} $ 无意义  , 给他 ~~扔了~~ )

$$
\small
\begin{aligned}
&=2 \times (C^1_{n-1}+2 \times C^2_{n-1}+...+(n-1) \times C^{n-1}_{n-1}\,)\,+\,(C^0_{n-1}+C^1_{n-1}+C^2_{n-1}+...+C^{n-1}_{n-1})\\

&=2 \times K[n-1]+2^n\\
\end{aligned}
$$

一个 $for$ 循环, 成功解决~  
两种理解 , 皆可食用

# Code

对于简化后的式子:
$$
\sum^{Maxa}_{d=2}d
\sum_{p=1}^{\frac{Maxa}{d}}\mu(p) \, K[cnt[dp]]
$$
只需 $O(n)$ 预处理出 $\mu[\,i\,]$ , $cnt[dp]$ , 和 $K[\,cnt[dp]\,] $ 就好,然后一个 $\Sigma$  一个 $for$ , 就是 $O(n\,\ln\,n)$ 的复杂度了

要想优化下常数的话,注意代码里的取模不要太多,  $long\,\,long$ 不要太过就好

下面...上代码 : 

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=200000;
const int MAXM=1000000;
const int mod=1e9+7;
int n,m,a[MAXN+10];
int p[MAXM+10],cnt,u[MAXM+10];
int CNT[MAXM+10];
long long ans,K[MAXM+10];
bool vis[MAXM+10];
inline void Get_Mu() //借欧拉筛求 u函数 
{
	u[1]=1;
	for(int i=2;i<=m;i+=1)
	{
		if(!vis[i]) p[++cnt]=i,u[i]=-1;
		for(int j=1;j<=cnt&&i*p[j]<=m;j+=1)
		{
			vis[i*p[j]]=1;
			if(i%p[j]==0)
			{
				u[i*p[j]]=0;
				break;
			}
			u[i*p[j]]=-u[i];
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i+=1)
	{
		scanf("%d",&a[i]);
		m=max(a[i],m);
		CNT[a[i]]+=1;
	}
	//预处理 u[] 
	Get_Mu();
	int M=m>>1;
	//预处理出 i 的倍数为 CNT[i] 个 
	for(int i=1;i<=M;i+=1)
		for(int j=i<<1;j<=m;j+=i)
			CNT[i]+=CNT[j]; 
	//预处理 K[] 数组 
	for(int i=1,t=1;i<=n;i+=1,t=(t*2ll)%mod)
		K[i]=(2*K[i-1]+t)%mod;
	//求和 取模 
	for(int i=2;i<=m;i+=1)
		for(int j=1;j<=m/i;j+=1)
			if(u[j]) ans=(ans+K[CNT[i*j]]*u[j]*i)%mod;
	printf("%lld",ans);
	return 0;
} 
```
## 结语
本篇题解到这里就结束啦~  
~~看到这里的同学应该都看到这里了吧~~  
感谢大家的支持~  
祝各位在OI的路上各有所成 , 前途似锦~  
 $\LARGE THE\quad END$ 

---

## 作者：Treaker (赞：12)

听说都是大家$O(n\ln n)$，我来一个$O(nloglogn)$的做法吧。

看到这个复杂度大家应该都想到了吧，用$Dirichlet$前缀和来算。

关于$Dirichlet$前缀和的东西，[可以去这里看](https://www.luogu.com.cn/blog/Treaker/dirichlet-qian-zhui-hu-ji-ta-zhan#)

设$f(i)$表示$\gcd=i$的子序列的总长度，$n$为$max\{a_i\}$

那么显然$ans=\displaystyle\sum_{i=2}^mi*f(i)$

但是$f(i)$不太好算，我们设$g(i)$为$\gcd$为$i$的倍数的子序列的总长度

那么$g(i)=\displaystyle\sum_{i|d}f(d)$

那么这个式子就是$Dirichlet$后缀和逆的形式。

我们现在只需要求出$g(i)$就行了。

我们考虑$g(i)$怎么快速算。

我们再设一个函数$s(i)$为$i$的倍数的数的个数。这个东西可以用$Dirichlet$后缀和来算。因为，我们设$c(i)$为$i$的出现次数。

$$s(i)=\displaystyle\sum_{i|d}c(d)$$

我们考虑$g(i)=\displaystyle\sum_{i=1}^{s(i)}{s(i)\choose i}*i$

这个东西我们可以根据组合数学那套理论来快速求了。具体就是分奇偶性来算。

然后这题就没了。

~~就不贴代码了~~

---

## 作者：5k_sync_closer (赞：8)

说两个做法。
# 共同思路
设 $f_i$ 为 $\gcd=i$ 的子序列长度和。$f_i$ 不太好算，设 $g_i$ 为 $i|\gcd$ 的子序列长度和，即 $g_x=\sum\limits_{x|i}f_i$。

考虑怎样求 $g_i$。设 $c_i$ 为 $i$ 的出现次数，$s_i$ 为 $i$ 的倍数的出现次数，即 $s_x=\sum\limits_{x|i}c_i$。

容易发现 $g_i$ 为在 $s_i$ 个数中选出的子序列长度和，$s_i$ 个数中，每个数被 $2^{s_i-1}$ 个子序列包含，则 $g_i=2^{s_i-1}s_i$。

最后根据 $g_i$ 推出 $f_i$ 即可。注意到复杂度瓶颈在于求 $f_i,s_i$。
# Sol. 1
考虑暴力求 $f_i,s_i$。复杂度是调和级数的，$O(n\log n)$ 可以过掉。
```cpp
#include <cstdio>
#include <algorithm>
#define M 1000000007
using namespace std;
int n, m, c[1000050];long long q, p[200050], f[1000050];
int main()
{
	scanf("%d", &n);for(int i = p[0] = 1, x;i <= n;++i)
	scanf("%d", &x), ++c[x], m = max(m, x), p[i] = (p[i - 1] << 1) % M;
	for(int i = m, s;i > 1;--i)
	{
		s = 0;for(int j = i;j <= m;j += i) s += c[j];if(s)
		{f[i] = s * p[s - 1] % M;for(int j = i << 1;j <= m;
		j += i) (f[i] += M - f[j]) %= M;(q += i * f[i]) %= M;}
	}
	return printf("%lld", q), 0;
}
```
# Sol. 2
注意到 $g_x=\sum\limits_{x|i}f_i,s_x=\sum\limits_{x|i}c_i$ 都是 Dirichlet 后缀和的形式，可以 $O(n\log\log n)$ 解决。
```cpp
#include <cstdio>
#include <algorithm>
#define M 1000000007
using namespace std;
int n, m, d, a[1000050], c[1000050];long long q, p[200050], f[1000050];bool b[1000050];
int main()
{
	scanf("%d", &n);for(int i = p[0] = 1, x;i <= n;++i)
	scanf("%d", &x), ++c[x], m = max(m, x), p[i] = (p[i - 1] << 1) % M;
	for(int i = 2;i <= m;++i) {if(!b[i]) a[++d] = i;
	for(int j = 1;i * a[j] <= m;++j) {b[i * a[j]] = 1;if(!(i % a[j])) break;}}
	for(int i = 1;i <= d;++i) for(int j = m / a[i];j > 1;--j) c[j] += c[j * a[i]];
	for(int i = m;i > 1;--i) if(c[i]) f[i] = c[i] * p[c[i] - 1] % M;
	for(int i = 1;i <= d;++i) for(int j = 2;j * a[i] <= m;++j) (f[j] += M - f[j * a[i]]) %= M;
	for(int i = 2;i <= m;++i) (q += i * f[i]) %= M;return printf("%lld", q), 0;
}
```


---

## 作者：RQ。。。 (赞：8)

虽然有位巨佬推出了$O(nloglog)$的做法，但是吧，作为蒟蒻，我还是想提出一个容易理解的$O(nln)$的做法
----

**强行推式子**
$$
\sum_{d = 2}^A\sum_{k=1}^n d \times k \sum_{s_1,s_2,s_3...,s_k}[gcd(a_{s_1},a_{s_2},,,a_{s_k}) = d]
$$
其中d是gcd，k是长度，A是最大的$a_i$
$$
\sum_{d = 2}^A\sum_{k=1}^n d \times k \sum_{s_1,s_2,s_3...,s_k}[gcd(\frac{a_{s_1}}{d},\frac{a_{s_2}}{d},,,\frac{a_{s_k}}{d}) = 1]
$$
然后莫比乌斯反演
$$
\sum_{d = 2}^A\sum_{k=1}^n d \times k \sum_{p=1}^{\frac{A}{d}}\mu(p)\sum_{s_1,s_2,s_3...,s_k}[d p | {a_{s_1}},d p | {a_{s_s}},d p | {a_{s_n}},]
$$
换一下顺序
$$
\sum_{d = 2}^Ad\sum_{p=1}^{\frac{A}{d}}\mu(p)\sum_{k=1}^n k \sum_{s_1,s_2,s_3...,s_k}[d p | {a_{s_1}},d p | {a_{s_s}},d p | {a_{s_n}},]
$$
记{a}中dp的倍数有cnt个，那么
$$
\sum_{d = 2}^Ad\sum_{p=1}^{\frac{A}{d}}\mu(p)\sum_{k=1}^{cnt} k C(cnt , k)
$$
然后把 $\sum_{k=1}^{cnt}kC(cnt,k)$ 预处理一下，记为K[cnt]
那么式子就变成了
$$
\sum_{d = 2}^Ad\sum_{p=1}^{\frac{A}{d}}\mu(p)K[cnt]
$$
线性筛筛一遍mu，然后就可以$O(nln)$求解
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
#define int long long
const int N = 1e6+10 , mod = 1000000007;
inline int read()
{
	register int x = 0; register char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48) , c = getchar();
	return x;
}
int n;
int a[N];
inline int Gcd(int a , int b) { return !b ? a : Gcd(b , a % b); }
inline int add(int a , int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a , int b) { return (LL)a * b % mod; }
inline int ksm(int a , int k) { int ans = 1; a %= mod; for( ; k ; k >>= 1 , a = mul(a , a)) if(k & 1) ans = mul(ans , a); return ans; }
namespace Work1
{
	int main()
	{
		int ans = 0 , res = 0 , k = 0;
		for(int i = 1 ; i < (1 << n) ; ++i)
		{
			res = k = 0;
			for(int j = 1 ; j <= n ; ++j) if((i >> (j - 1)) & 1) res = Gcd(res , a[j]) , k++;
			if(res > 1) ans = add(ans , mul(res , k));
		}
		cout << ans << '\n'; return 0;
	}
}

namespace Work2
{
	const int N = 1e6+10 , M = 1e6+10;
	int tot;
	int prime[M] , vis[M] , mu[M] , cnt[M] , K[N];
	void Init(int n , int m)
	{
		mu[1] = 1;
		for(int i = 2 ; i <= m ; ++i)
		{
			if(!vis[i]) prime[++tot] = i , mu[i] = -1;
			for(int j = 1 ; j <= tot && i * prime[j] <= m ; ++j)
			{
				vis[i * prime[j]] = 1;
				if(i % prime[j] == 0) { mu[i * prime[j]] = 0; break; }
				mu[i * prime[j]] = -mu[i];
			}
		}
		for(int i = 2 ; i <= m ; ++i)
			for(int j = i + i ; j <= m ; j += i)
				cnt[i] += cnt[j];
		K[1] = 1; int tmp = 2;
		for(int i = 2 ; i <= n ; ++i) K[i] = ((K[i-1] + K[i-1]) % mod + tmp) % mod , tmp = tmp * 2 % mod;
	}
	
	int main()
	{
		int mx = 0;
		for(int i = 1 ; i <= n ; ++i) cnt[a[i]]++ , mx = max(mx , a[i]);
		Init(1e6 , 1e6);
		for(int i = 0 ; i <= mx ; ++i) mu[i] = (mu[i] % mod + mod) % mod;
		int ans = 0;
		for(int d = 2 ; d <= mx ; ++d)
			for(int p = 1 ; p <= mx / d ; ++p)
				ans = (ans + (d * mu[p] % mod + mod) % mod * K[cnt[d * p]] % mod + mod) % mod , ans = (ans % mod + mod) % mod;
		cout << ans << '\n'; return 0;
	}
}

signed main()
{
	// freopen("a.in" , "r" , stdin); // freopen("rq.out" , "w" , stdout);
	n = read();
	for(int i = 1 ; i <= n ; ++i) a[i] = read();
	// if(n <= 20) Work1::main(); else 
	Work2::main();
	return 0;
}
/*
5
2 2 4 4 6
4
2 3 4 6
2 6 1 4 23 12 45 32
305 1072
*/
```
**记得开long long，**


---

## 作者：Weng_Weijie (赞：5)

下面默认$a_i$的最大值为$N$

$$f(x)=\sum_{S}x\cdot|S|[\gcd(S)=x]$$

答案就是$\displaystyle\sum_{i=2}^{N}f(i)$

直接求$f(x)$不好做

考虑求$g(x)=\displaystyle\sum_{S}|S|[x|\gcd(S)]$

$$=\sum_{L=1}^NL\cdot\binom {cnt_x}{L}=cnt_x2^{cnt_x-1}x$$

$$f(x)=x\sum_{i=1}^N\mu(i)cnt_{ix}2^{cnt_{ix}-1}$$

答案为 $$\sum_{i=2}^Ni\sum_{j=1}^N\mu(j)cnt_{ij}2^{cnt_{ij}-1}$$

$$\sum_{k=1}^Ncnt_k2^{cnt_k-1}\sum_{d\geq 2,d|k}d\mu(\frac kd)$$

$$\sum_{k=1}^Ncnt_k2^{cnt_k-1}(\varphi(k)-\mu(k))$$

```cpp
#include <cstdio>
const int R = 1E6;
const int mod = 1000000007;
using LL = long long;
int n, pow[R + 5];
bool sie[R + 5];
int phi[R + 5], miu[R + 5], pr[R / 10], pt, md[R + 5];
void up(int &x, int y) { if ((x += y) >= mod) x -= mod; }
void sieve() {
    phi[1] = miu[1] = 1;
    for (int i = 2; i <= R; i++) {
        if (!sie[i]) pr[++pt] = i, miu[i] = -1, md[i] = i, phi[i] = i - 1;
        for (int j = 1, t; j <= pt && (t = i * pr[j]) <= R; j++) {
            sie[t] = 1; md[t] = pr[j];
            if (i % pr[j] == 0) { phi[t] = phi[i] * pr[j]; miu[t] = 0; break; }
            phi[t] = phi[i] * (pr[j] - 1); up(miu[t] = 0, mod - miu[i]);
        }
    }
}
int cnt[R + 5];
int pdiv[100], pcnt[100], tot;
void dfs(int dep, int val) {
    if (dep > tot) return void(cnt[val]++);
    for (int i = 0; i <= pcnt[dep]; i++) dfs(dep + 1, val), val *= pdiv[dep];
}
int main() {
    sieve();
    std::scanf("%d", &n);
    pow[0] = 1; for (int i = 1; i <= n; i++) up(pow[i] = pow[i - 1], pow[i - 1]);
    for (int i = 1; i <= n; i++) {
        int x;
        std::scanf("%d", &x); tot = 0;
        while (x > 1) {
            int t = md[x], cnt = 0;
            while (x % t == 0) cnt++, x /= t;
            pdiv[++tot] = t, pcnt[tot] = cnt;
        }
        dfs(1, 1);
    }
    int ans = 0;
    for (int i = 1; i <= R; i++) if (cnt[i]) 
        up(ans, static_cast<LL> (cnt[i]) * pow[cnt[i] - 1] % mod * (phi[i] - miu[i] + mod) % mod);
    std::printf("%d\n", ans);
    return 0;
}
```

---

## 作者：zhikong (赞：2)

# CF839D Winter is here

问题相当于从 $a$ 中选 $k$ 个数求 $k \times \gcd(a_{i_1}, a_{i_2}, \cdots , a_{i_k})$ 的和。  

考虑 $dp_{i}$ 表示 $\gcd = i$ 的贡献。  

在不考虑算重的情况下，方案数为：  

$dp_i = \sum\limits_{j = 1}^{N_{i}} j {\binom{N_{i}}{j}} = n \times 2^{N_i-1}$  

其中 $N_i$ 表示 $a$ 中为 $i$ 的倍数的数的个数。  

考虑去重，设容斥系数为 $f_i$。  

初始 $f_i = i$。  

因为一个数只会在他的因数被算重。  

$\therefore f_i = f_i - \sum\limits_{j|i} f_j$  

那么最后的答案为：  

$ans=\sum\limits_{i = 1} ^ {\max} dp_i \times f_i$  

```cpp

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long pre[1000005],ans,tmp[1000005];
int a[200005],b[1000005],num;
int cnt,n,m;
void init(){
	pre[0]=1;
	for(int i=1;i<=1000000;i++){
		pre[i]=pre[i-1]*2ll%mod;
	}
}
int main(){
	init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[a[i]]++;
	}
	for(int i=2;i<=1000000;i++){
		tmp[i]=i;
	}
	for(int i=2;i<=1000000;i++){
		for(int j=i*2;j<=1000000;j+=i){
			tmp[j]-=tmp[i];
		}
	}
	for(int i=2;i<=1000000;i++){
		num=0;
		for(int j=i;j<=1000000;j+=i){
			num+=b[j];
		}
		ans+=pre[num-1]*1ll*num%mod*tmp[i]%mod;
		ans=(ans+mod)%mod;
	}
	printf("%lld",ans);
}

```


---

## 作者：Ginger_he (赞：1)

这题跟 
[CF803F Coprime Subsequences](https://www.luogu.com.cn/problem/CF803F) 有异曲同工之妙，考虑 $f_i$ 表示 $\gcd$ 为 $i$ 的序列长度和，$g_i$ 表示 $i\mid \gcd$ 的序列长度和，设 $cnt_i$ 表示值为 $i$ 的个数，先考虑如何求 $g_i$。

显然，我们可以先求出 $i$ 的倍数的个数，即

$$s_i=\sum_{i\mid x}cnt_x$$

那么可以按照长度来求出 $g_i$，即

$$g_i=\sum_{x=1}^{s_i}x\times\binom{s_i}{x}$$

展开并约分得到

$$g_i=\sum_{x=1}^{s_i}\dfrac{s_i!}{(x-1)!(s_i-x)!}$$

化简可得


$$g_i=s_i\sum_{x=1}^{s_i}\binom{s_i-1}{x-1}=s_i\times2^{s_i-1}$$

通过容斥可推出 $f_i$，即

$$f_i=g_i-\sum_{i\mid x}f_x$$

设 $m=\max\limits_{i=1}^na_i$，答案即为

$$\sum_{i=2}^mi\times f_i$$

时间复杂度 $\Theta(m\ln m)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
#define M 1000005
const ll p=1e9+7;
int n,m,a[N],cnt[M];
ll res,v[N],f[M],ans;
int main()
{
	scanf("%d",&n);
	v[0]=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		m=max(m,a[i]);
		cnt[a[i]]++;
		v[i]=v[i-1]*2%p;
	}
	for(int i=m;i>=2;i--)
	{
		res=0;
		for(int j=i;j<=m;j+=i)
			res+=cnt[j];
		f[i]=v[res-1]*res%p;
		for(int j=i*2;j<=m;j+=i)
			f[i]=((f[i]-f[j])%p+p)%p;
		ans=(ans+i*f[i]%p)%p;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：FjswYuzu (赞：0)

定义 $f(i)$ 为整个数列中为满足 $i \mid a_j$ 的 $j$ 的个数。这个东西如果对 $a$ 开一个桶，很显然可以在 $O(n \ln n)$ 的时间内处理。又定义 $g(i)$ 为 $\gcd$ 为 $i$ 的子序列个数，可以得到：

$$
g(i) = \sum_{j=0}^{f(i)} j \dbinom{f(i)}{j} - \sum_{j=2} g(ij)
$$

现在的问题是 $\sum_{j=0}^{f(i)} j \dbinom{f(i)}{j}$ 怎么算。虽然是个经典式子在这里再写一发。注意到：

$$
\sum_{j=0}^{f(i)} j \dbinom{f(i)}{j} =\sum_{j=0}^{f(i)} (f(i)-j) \dbinom{n}{n-j}
$$

两边相加，可以得到：

$$
n\sum_{j=0}^{f(i)} \dbinom{f(i)}{j}
$$

根据二项式定理显然原式值为 $n2^n$。注意要除以 $2$，所以 $\sum_{j=0}^{f(i)} j \dbinom{f(i)}{j} = n2^{n-1}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL QuickPow(LL x,LL p)
{
	if(x==0)	return 0;
	if(p<0)	return 0;
	LL ans=1,base=x;
	while(p)
	{
		if(p&1)	ans=ans*base%MOD;
		base=base*base%MOD;
		p>>=1;
	}
	return ans;
}
LL n,a[200005],st[1000005],up,f[1000005];
int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;++i)	scanf("%lld",&a[i]),++st[a[i]],up=max(up,a[i]);
	for(LL i=1;i<=up;++i)	for(LL j=i;j<=up;j+=i)	f[i]=(f[i]+st[j])%MOD;
	for(LL i=1;i<=up;++i)	f[i]=f[i]*QuickPow(2,f[i]-1)%MOD;
	for(LL i=up;i;--i)	for(LL j=2*i;j<=up;j+=i)	f[i]=(f[i]+MOD-f[j])%MOD;
	LL ans=0;
	for(LL i=2;i<=up;++i)	ans=(ans+f[i]*i%MOD)%MOD;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

以下记集合 $S$ 为原来的数列，$m =  \max\limits_{i=1}^n a_i$，$\gcd(T)$ 表示集合 $T$ 内所有元素的最大公约数，$[d | T]$ 表示 $d$ 能整除集合 $T$ 内的**所有元素**，$\dfrac{T}{d}$ 表示集合 $T$ 内每一个元素除以 $d$ 后得到的新集合。

按照题意，我们列出题目要求我们求的答案式，并套路化的变换：

$$\begin{aligned}ans & = \sum\limits_{T \in S}\gcd(T )\times |T| \times [\gcd(T)>1] \\ & = \sum\limits_{d=2}^md \times \sum \limits_{T \in S}[\gcd(T) = d] \times |T|\\ & = \sum\limits_{d=2}^md \times \sum \limits_{T \in S}[\gcd(\dfrac{T}{d}) = 1][d | T]\times |T| \\ & =\sum\limits_{d=2}^md \times \sum \limits_{T \in S}\varepsilon(\gcd(\dfrac{T}{d}))[d | T]\times |T|\\ & =\sum\limits_{d=2}^md \times \sum \limits_{T \in S}\sum \limits_{i=1}^m\mu(i)[d | T][i | \dfrac{T}{d}]\times |T| \end{aligned}$$

这里我们发现一个集合 $T$ 合法的必要条件是 $(i \times d) | T$。我们记 $c_i$ 表示集合 $S$ 中 $i$ 的倍数有几个，容易发现对于每一对 $(i,d)$ ，可以选的合法的元素共有 $c_{id}$ 个。我们知道对于一个有 $n$ 个元素的集合 $T$，其所有子集大小的和是 $2^{n-1} \times n$，因此对于数对 $(i,d)$ 对答案的贡献就是 $2^{c_{id}-1} \times c_{id} \times \mu(i)$。又发现当 $id > m$ 时贡献显然为 $0$，因此当 $id > m$ 时可以直接退出循环。因此上面的式子可以化为以下形式：

$$\sum_{d=2}^md\sum_{i=1}^{\lfloor \frac{m}{d} \rfloor} 2^{c_{id}-1} \times c_{id} \times \mu(i)$$

我们预处理筛出 $c_i$，然后枚举 $i,d$ 即可，时间复杂度预处理 $\Theta(n \log n)$ 枚举 $\Theta (n \ln n)$，可以通过本题。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6,mod = 1e9+7;
int n,a[maxn+5],c[maxn+5],mu[maxn+5],vis[maxn+5],f[maxn+5],ans,mx,d[maxn+5];
int lcm(int a,int b){return a * b / __gcd(a,b);}
signed main(){
	//freopen("gcd.in","r",stdin),freopen("gcd.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0);
	cin >> n;f[0] = 1;
	for(int i = 1;i <= n;i ++) cin >> a[i],c[a[i]] ++,mx = max(mx,a[i]);
	mu[1] = 1,vis[1] = 1;
	for(int i = 1;i <= maxn;i ++){
		if(!vis[i]) mu[i] = -1;f[i] = f[i-1] * 2 % mod;d[i] ++;
		for(int j = i*2;j <= maxn;j += i) c[i] = (c[i] + c[j]) % mod,vis[j] = (i != 1),mu[j] -= (mu[i]),d[j] ++;
		mu[i] = (mu[i]  + mod) % mod;
	}
	for(int i = 2;i <= mx;i ++){
		int tmp = 0;
		for(int j = 1;j*i <= mx;j ++){
			tmp = (tmp + f[c[i*j]-1] % mod * c[i*j] % mod * mu[j]) % mod;
		}
		ans = (ans + i * tmp) % mod;
	}
	cout << ans;
	return 0;
}
```



---

