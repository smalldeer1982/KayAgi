# 「Daily OI Round 3」Xor Graph

## 题目背景

在黎明来临之前，总要有人照亮黑暗。

## 题目描述

Xs_siqi 给了你 $2^n$ 个点，$x$ 到 $y$ 有**有向**边当且仅当 $x\operatorname{xor} y=2^k,k \in [0,n)$，且 $x>y$。其中，$\operatorname{xor}$ 表示按位异或，$k$ 为整数。令 $f_{x,y}$ 为 $x$ 点到 $y$ 点的不同路径数，求： 

$$\sum_{i=1}^{2^n}\sum_{j=1}^{2^n}f_{i,j}(i\neq j)$$

答案对 $998244353$ 取模。

## 说明/提示

#### 【样例解释 #1】

对于样例的第一组，$3$ 向 $1,2$ 连边，这样 $3$ 到 $1$ 是一个方案，$3$ 到 $2$ 是一个方案，一共有 $2$ 个方案。

#### 【数据范围】

对于全部数据保证：$1 \le t \le 10^6$，$1 \le n \le 10^7$。

## 样例 #1

### 输入

```
4
2
3
50
999998```

### 输出

```
2
15
599192517
81627972```

# 题解

## 作者：max0810 (赞：12)

我们首先观察到，对于 popcount 相同的数，它们的答案是一样的。设一个数的二进制中有 $n$ 个 $1$，那这个数下一步就可以走到 $n$ 个不同的 popcount 为 $n-1$ 的数。

由于终点是不固定的，那么以一个 popcount 为 $n$ 的数为起点的路径一共有 $n+n(n-1)+n(n-1)(n-2)+\ldots+n(n-1)\times\ldots\times 2$ 条（$0$ 不能当作终点），也就是 $\sum_{i=1}^{n-1}\frac{n!}{i!}$。

所以我们可以枚举 popcount 是多少：

$$
\begin{aligned}
\sum_{i=1}^{2^n}\sum_{j=1}^{2^n}f_{i,j} &= \sum_{i=1}^n \binom n i\sum_{j=1}^{i-1}\frac{i!}{j!} \\ 
&= \sum_{i=1}^n \frac{n!}{i!(n-i)!}\sum_{j=1}^{i-1}\frac{i!}{j!} \\ 
&= \sum_{i=1}^n \frac{n!}{(n-i)!}\sum_{j=1}^{i-1}\frac 1 {j!}
\end{aligned}
$$
令 $f(n) = \sum_{i=1}^n \frac 1 {i!}$，然后我们改变枚举方式，用 $n-i$ 来代替 $i$：
$$
\sum_{i=1}^n \frac{n!}{(n-i)!}\sum_{j=1}^{i-1}\frac 1 {j!} = \sum_{i=0}^{n-1} \frac{n!}{i!}\times f(n-i-1)
$$
然后我们考虑怎么优化时间复杂度，这里可以用递推的方式。具体地，我们令 $ans_n$ 表示 $n$ 的答案，则：
$$
\begin{aligned}
ans_{n+1}-ans_n &= \frac{(n+1)!}{n!}\times f(n+1-n-1)+\sum_{i=0}^{n-1}(\frac{(n+1)!}{i!}\times f(n-i)-\frac{n!}{i!}\times f(n-i-1)) \\ 
&= \sum_{i=0}^{n-1}\frac{(n+1)!\times f(n-i)-n!\times f(n-i-1)}{i!} \\ 
&= \sum_{i=0}^{n-1}\frac{(n+1)!\times(\frac 1 {(n-i)!}+f(n-i-1))-n!\times f(n-i-1)}{i!} \\ 
&= \sum_{i=0}^{n-1}\frac{((n+1)!-n!)\times f(n-i-1)}{i!}+\sum_{i=0}^{n-1}\frac{(n+1)!}{(n-i)!i!} \\ 
&= \sum_{i=0}^{n-1}\frac{n\times n!\times f(n-i-1)}{i!}+\sum_{i=0}^{n-1}(n+1)\binom{n}{i} \\ 
&= n\times ans_{n}+(n+1)(2^n-1) \\ 
ans_{n+1} &= (n+1)ans_n+(n+1)(2^n-1) = (n+1)(ans_n+2^n-1)
\end{aligned}
$$
所以递推公式就是：
$$
ans_n = n(ans_{n-1}+2^{n-1}-1)
$$
代码：

```cpp
int main()
{
    int t = rd();
    for(int i = 1;i < N;i++,p = p*2%mod)
        f[i] = i*(f[i-1]+p-1)%mod;
    while(t--)printf("%lld\n",f[rd()]);
    return 0;
}
```

---

## 作者：eastcloud (赞：7)

为啥都是复杂推式子，其实这个题有比较简单的做法。

考虑一条合法的从 $x$ 到 $y$ 的路径肯定是 $y$ 在二进制下是 $x$ 的子集，$x$ 每次丢掉一个子集比 $y$ 多出来的二进制位前进，就有： 

$$f(x,y)=\text{popcount}( x  \oplus  y )!$$

你发现其实贡献种数只有 $n-1$ 种，枚举贡献，然后我们就确定这个多出来的二进制位的数量，接着枚举重合的二进制位（非空）就能得到答案为:

$$ \sum_{i=1}^{n-1} {n\choose i} i!(2^{n-i}-1) $$

把阶乘塞进去就是：

$$ \sum_{i=1}^{n-1} n^{\underline m} (2^{n-i}-1) $$

这个显然可以把括号拆开然后递推，递推式子非常显然，于是做完了。

```cpp
int main(){
	ll T=read();f[2]=2;g[2]=4;
	for(ll w=4,i=3;i<N;i++,w=(w*2)%mod){
		f[i]=(f[i-1]*i+i)%mod;
		g[i]=(g[i-1]*i+w*i)%mod;
	}
	while(T--){ll n=read();write((g[n]-f[n]+mod)%mod);putchar('\n');}
	return 0;
}
```


---

## 作者：xs_siqi (赞：3)


以下讨论的时候，都钦定一个点到他自己也是一个方案（最后直接减去 $2^n$ 即可）。

首先暴力复杂度是 $O(2^{2n})$ 的。

考虑两个点有边，当且仅当 $y$ 是 $x$ 的子集。那么我们可以枚举每一个 $i$ 的 $1$ 的个数，然后枚举它的子集个数。

首先我们发现比如说枚举到的这个数有 $t$ 个 $1$，那么它的包含了 $1$ 个 $1$ 的个数为 $C_t^1$（这个不证了），然后对于每一个只有一个 $1$ 的点，它到达的方案数必然是 $(t-1)!$（因为你可以考虑每一次减少一个 $1$ 之后就会有且仅有 $1$ 个数不包含这一位的 $1$ 了）。

综上，式子变成了：

$$\sum_{i=1}^{2^n}\sum_{j=1}^{\operatorname{popcount(i)}}C_{\operatorname{popcount(i)}}^j(\operatorname{popcount(i)}-j)!$$

复杂度 $O(n2^n)$。

然后我们可以继续考虑下去，主要是优化第一个 $\sum_{i=1}^{2^n}$。

我们先考虑优化 $\sum_{i=1}^{2^n-1}$

注意到对于每次 $n+1$，那么原来为一个 $1$ 的就会变成两个 $1$（因为最高位加了个 $1$）。

所以不难发现，对于一个 $1$ 的随 $n$ 增加公差为 $1$ 增加，对于两个 $1$ 的随公差为 $1,2,3,4,\cdots$ 增加，以此类推。

这个东西有一个经典式子叫做 $C_{j+l-1}^{l-1}$。直接套就行。

而且考虑到此时的东西是 $n$，那么每行刚好往前差一项。

然后式子变成了：

$$\sum_{i=1}^{n}C_n^i\sum_{j=1}^i C_i^j (i-j)!$$

预处理组合数，复杂度 $O((\sum n)^2)$。

这个式子还可以继续优化。

考虑组合意义，所以下面两个式子是一样的：

$$\sum_{i=1}^{n}C_n^i\sum_{j=1}^i C_i^j (i-j)!$$

$$\sum_{i=1}^{n}C_n^i\sum_{j=1}^i \dfrac{i!}{j!(i-j)!} (i-j)!$$

刚好消掉了，发现了吧，式子变成：

$$\sum_{i=1}^{n}C_n^i\sum_{j=1}^i \dfrac{i!}{j!} $$

不妨令 $f_i=\sum_{j=1}^i \dfrac{i!}{j!}$，那么显然会有：

$$f_i=i\times f_{i-1}+1$$

式子变成：

$$\sum_{i=1}^{n}C_n^i f_i$$

然后我们刚刚考虑的一直都是 $2^n-1$，我们发现对于 $2^n$ 这个点它只有一个 $1$，只能走到它自己，所以方案直接加一即可。

也即式子变成：

$$\sum_{i=1}^{n}C_n^i f_i+1$$

预处理组合数，同时处理该式子和 $f$ 函数，时间复杂度为 $O(\sum n)$。

---

好！标程被验题人爆了。现在有一个 $O(\max n)$ 做法。原来做法是  $O(\sum n)$。

做法式子貌似是：

$$f_i=i(2^{i-1}-1+f_{i-1})$$

不过他是找规律找出来这个做法。明明我 OEIS 过根本找不到，哎，这可能就是人工 OEIS 吧。

这个做法式子是不基于 $n$，比标程更优。

我们知道：$f_n=\sum\limits_{i=2}^n(C_n^i\sum\limits_{j=1}^{i-1}A_i^j)$。

$\begin{aligned}
\therefore f_n&=\sum\limits_{i=2}^n(\dfrac{n!}{i!(n-i)!}\sum\limits_{j=1}^{i-1}\dfrac{i!}{(i-j)!})\\
&=\sum\limits_{i=2}^n(\dfrac{n!}{(n-i)!}\sum\limits_{j=1}^{i-1}\dfrac{1}{(i-j)!})\\
&=n!\sum\limits_{i=2}^n\sum\limits_{j=1}^{i-1}\dfrac{1}{(n-i)!(i-j)!}\\
&=n!\sum\limits_{1\le j<i\le n}\dfrac{1}{(n-i)!(i-j)!}
\end{aligned}$

令 $i_0=n-j,j_0=n-i$：

$\begin{aligned}
\therefore f_n&=n!\sum\limits_{1\le n-i_0<n-j_0\le n}\dfrac{1}{(n-(n-j_0))!((n-j_0)-(n-i_0)))!}\\
&=n!\sum\limits_{0\le j_0<i_0\le n-1}\dfrac{1}{j_0!(i_0-j_0)!}\\
&=n!\sum\limits_{i_0=1}^{n-1}\sum\limits_{j_0=0}^{i_0-1}\dfrac{1}{j_0!(i_0-j_0)!}\\
&=n!\sum\limits_{i_0=1}^{n-1}\dfrac{1}{i_0!}\sum\limits_{j_0=0}^{i_0-1}\dfrac{i_0!}{j_0!(i_0-j_0)!}\\
&=n!\sum\limits_{i_0=1}^{n-1}\dfrac{1}{i_0!}\sum\limits_{j_0=0}^{i_0-1}C_{i_0}^{j_0}\\
&=n!\sum\limits_{i_0=1}^{n-1}\dfrac{2^{i_0}-1}{i_0!}。
\end{aligned}$

于是，我们有：

$$f_n=n!\sum\limits_{i=1}^{n-1}\dfrac{2^i-1}{i!}$$ 

又由 $f_n=n!\sum\limits_{i=1}^{n-1}\dfrac{2^i-1}{i!}$，$f_{n-1}=(n-1)!\sum\limits_{i=1}^{n-2}\dfrac{2^i-1}{i!}$

$\begin{aligned}
\therefore f_n-nf_{n-1}&=n!\dfrac{2^{n-1}-1}{(n-1)!}\\
&=n(2^{n-1}-1)。
\end{aligned}$

$\therefore f_n=n(2^{n-1}-1+f_{n-1})$，证毕。

---

## 作者：Coffins (赞：2)

好玩的推柿子题！！！

首先这个 $2^n$ 很废物看着很难受，然后还有这个 $i\not =j$，也很蠢，于是转化一下题意，我们来求一个：
$$\zeta_n=\sum\limits_{i=1}^{2^n-1}\sum\limits_{i=1}^{2^n-1}f_{i,j}$$
考虑最终的答案与 $\zeta$ 的差距就在于对于多了自己到自己的路径，于是最终答案就是 $\zeta_n-2^n+1$,于是考虑 $O(n)$ 预处理 $O(1)$ 查询 $\zeta_n$。

首先考虑求一个 $h_i=\sum\limits_{j=1}^if_{i,j}$，观察到每走一条边就是去掉 $i$ 二进制下的一个 $1$，于是可以知道 $h_i$ 只与 $\operatorname{popcount(i)}$ 有关，于是再设一个 $s_i$ 表示 $\operatorname{popcount(val)}=i$ 时的答案。

考虑一条路径就是选出若干个 $1$，然后进行一个排列，于是根据组合意义有 $s_i=\sum\limits_{j=1}^{i}\dfrac{i!}{j!}$

然后就有 $\zeta_n=\sum\limits_{i=1}^n\binom{n}{i}s_i$

然后就到了喜闻乐见的推柿子环节啦！！！

$$\begin{aligned}\dfrac{\zeta_n}{n!}
&=\sum\limits_{i=1}^n\dfrac{1}{i!(n-i)!}\sum\limits_{j=1}^i\dfrac{i!}{j!}\\
&=\sum\limits_{i=1}^n\dfrac{1}{(n-i)!}\sum\limits_{j=1}^i\dfrac{1}{j!}\\
&=\sum\limits_{i=1}^n\dfrac{1}{i!}\sum\limits_{j=1}^{n-i}\dfrac{1}{j!}\\
&=\sum\limits_{i=1}^{n-1}\dfrac{1}{i!}(\sum\limits_{j=1}^{n-1-i}\dfrac{1}{j!}+\dfrac{1}{(n-i)!})+\dfrac{1}{0!n!}\\
&=\dfrac{\zeta_{n-1}}{(n-1)!}+\sum\limits_{i=1}^{n}\dfrac{1}{i!(n-i)!}
\end{aligned}$$

于是就有：
$$\begin{aligned}\zeta_n
&=n\zeta_{n-1}+\sum\limits_{i=1}^n\dfrac{n!}{i!(n-i)!}\\
&=n\zeta_{n-1}+\sum\limits_{i=1}^n\binom{n}{i}\\
&=n\zeta_{n-1}+2^n-1
\end{aligned}$$

然后就可以 $O(n)$ 预处理 $O(1)$ 查询了！！！

由于柿子给出后，代码难度为 0，所以不贴了。

---

## 作者：zqiaor (赞：2)

在下文中记 $c_i$ 为 $i$ 在二进制表示下 $1$ 的个数。

**首先需要知道在 $1$ 到 $2^n-1$ 中有 $C_n^i$ 个 $x$ 满足 $c_x=i$**

然后考虑分步推式子。

设 $h_{i,j} (i>j)$ 为 $i\rightarrow j$ 的方案数，则 $h_{i,j}=(i\&j==j)\times (c_i-c_j)!$，表示将 $c_i-c_j$ 个 $1$ 变为 $0$ 不同操作序列数。

设 $g_{i}=\sum_{j=1}^{i-1}h_{i,j}$，观察 $h_{i,j}$ 的表达式及意义可知 $g_i$ 只与 $c_{i}$ 有关，所以：

$g_i=g_{2^{c_i}-1}=\sum_{j=1}^{2^{c_i}-2}(c_i-c_j)!=\sum_{c_j=1}^{c_i-1}C_{c_i}^{c_j}(c_i-c_j)!=c_i!\sum_{c_j=1}^{c_i-1}\frac{1}{c_j!}$

设 $f_n=\sum_{i=1}^{2^n-1}g_i$ （显然 $2^n$ 这个点是没有用的），由于 $g_i$ 只与 $c_i$ 有关，用同样的方法可以推得：

$f_n=\sum_{i=1}^{2^n-1}g_i=n!\sum_{c_i=1}^{n}\frac{1}{(n-c_i)!}\sum_{c_j=1}^{c_i-1}\frac{1}{c_j!}=n!\sum_{i=0}^{n-2}\frac{1}{i!}\sum_{j=1}^{n-i-1}\frac{1}{j!}$ 

（最后面这个式子中的 $i=n-c_i$，然后其中 $c_i=1$ 时贡献为 $0$，直接删了）

发现 $\frac{f_n}{n!}-\frac{f_{n-1}}{(n-1)!}=\sum_{i=0}^{n-2}\frac{1}{i!(n-i-1)!}=\frac{1}{(n-1)!}\sum_{i=0}^{n-2}C_{n-1}^{i}=\frac{2^{n-1}-1}{(n-1)!}$，

即 $f_n=n(f_{n-1}+2^{n-1}-1)$，可以 $O(n)$ 预处理出所有答案。

---

## 作者：modfish_ (赞：1)

非常好题目，使我怒砸桌子。

赛时式子推完了，就是没推出怎么递推。所以写个 $O(tn)$ 华丽趋势。
## 思路
题目明显表示，若 $x$ 到 $y$ 有边，则 $x$ 在二进制表示中有且仅有一位不同。结合 $x>y$，则 $x$ 包含所有 $y$ 拥有的二进制位 $1$，且多出来一位 $1$。

换言之，从 $x$ 走到下一个点，本质上是将其二进制位上的一个 $1$ 变成 $0$。

令 $num_x$ 表示 $x$ 的二进制表示中 $1$ 的个数，则 $x$ 至多能走出 $num_x-1$ 步，且第 $i$ 步有 $num_x-i+1$ 种选择。

这启示我们：若 $num_a=num_b$，则以 $a$ 为起点和以 $b$ 为起点的路径数是一样的。

那么，对于 $num_x=k$ 的数，共有多少条以它为起点的路径呢？

若路径长度为 $i$，则我们需要将该数二进制表示中的 $i$ 个 $1$ 变成 $0$，且顺序随意，容易知道有 $\frac{k!}{(k-i)!}$ 条路径。

对于最多 $n$ 位的二进制数，共有 $\binom{n}{k}$。

所以，令 $f_n$ 表示 $n$ 位时的答案，则：

$$f_n=\sum_{k=1}^n\binom{n}{k}\sum_{i=1}^{k-1}\frac{k!}{(k-i)!}$$

展开：

$$f_n=\sum_{k=1}^n\frac{n!}{k!(n-k)!}\sum_{i=1}^{k-1}\frac{k!}{(k-i)!}$$

化简：

$$f_n=n!(\sum_{k=1}^n\frac{1}{(n-k)!}\sum_{i=1}^{k-1}\frac{1}{(k-i)!})$$

因为 $1\leq t\leq 10^6$，所以要 $O(1)$ 或 $O(\log n)$ 求解，故尝试递推。

不难发现：

$$f_{n+1}-(n+1)f_n=(n+1)! (\sum_{k=1}^{n+1}\frac{1}{(n-k+1)!}\sum_{i=1}^{k-1}\frac{1}{(k-i)!})-(n+1)!(\sum_{k=1}^n\frac{1}{(n-k)!}\sum_{i=1}^{k-1}\frac{1}{(k-i)!})$$

读者们可以自行化简一下，总之最后会变成：

$$f_{n+1}-(n+1)f_n=(n+1)!\sum_{i=1}^n\frac{1}{i!(n-i)!}$$

进行一些转换：

$$f_{n+1}-(n+1)f_n=(n+1)\sum_{i=1}^n\frac{n!}{i!(n-i)!}$$

结合组合数公式：

$$f_{n+1}-(n+1)f_n=(n+1)\sum_{i=1}^n\binom{n}{i}$$

由二项式定理：

$$f_{n+1}-(n+1)f_n=(n+1)(2^n-1)$$

最后：

$$f_{n+1}=(n+1)(f_n+2^n-1)$$

上式是可以线性处理的。这样我们就可以 $O(n+k)$ 完成了。

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 1e7 + 5, mod = 998244353;

ll fact[maxn], pow2[maxn], f[maxn];

int main(){
	fact[0] = pow2[0] = 1;
	f[1] = 0;
	for(int i = 1; i <= 1e7; i ++){
		fact[i] = (fact[i - 1] * i) % mod;
		pow2[i] = (pow2[i - 1] << 1) % mod;
		if(i > 1) f[i] = i * ((f[i - 1] + pow2[i - 1] - 1) % mod) % mod;
	}
	int T;
	scanf("%d", &T);
	while(T --){
		int n;
		scanf("%d", &n);
		printf("%lld\n", f[n]);
	}
	return 0;
}
```
好耶！！

## 后记
考场上只推到

$$f_n=n!(\sum_{k=1}^n\frac{1}{(n-k)!}\sum_{i=1}^{k-1}\frac{1}{(k-i)!})$$

所以寄了，结果当天晚上可能脑子想了一个晚上，第二天早上就想出来了……

---

## 作者：Demeanor_Roy (赞：1)

- [原题链接](https://www.luogu.com.cn/problem/P10128)

------------

图上走一步的本质是把自己二进制位上某一位 $1$ 变成 $0$。

据此可列出答案式子：

$$\sum_{i=1}^{n}{n \choose i}\sum_{j=1}^{i-1}{{i \choose j}(i-j)!}$$

$$=\sum_{i=1}^{n}{n \choose i}\sum_{j=1}^{i-1}{{i \choose j}j!}$$

其中化简这一步即令 $j \rightarrow i-j$。

这样不好化简，不妨更改枚举顺序，先枚举 $j$，则答案为：

$$\sum_{j=1}^{n-1}{n \choose j}j!(2^{n-j}-1)$$

$$=\sum_{j=1}^{n-1}\dfrac{n!}{(n-j)!}(2^{n-j}-1)$$

$$=\sum_{j=1}^{n-1}\dfrac{n!}{j!}(2^j-1)$$

$$=n!\sum_{j=1}^{n-1}\dfrac{(2^j-1)}{j!}$$

化简至此即可递推出 $1 \sim n$ 的答案。

---

## 作者：teylnol_evteyl (赞：1)

假设加入 $0$ 号点，并且不需要 $i\neq j$。

容易发现，$\operatorname{popcnt}$ 相同的点为起点的贡献是一样的，且 $\operatorname{popcnt}$ 是 $i$ 个贡献即在 $i$ 个 $1$ 中选出若干位进行排列，则

$$
\begin{aligned}
Ans_i&=\sum_{i=0}^n C_n^i\sum_{j=0}^i\dfrac{i!}{j!}
\\
&=\sum_{i=0}^n \dfrac{n!}{i!(n-i)!}\sum_{j=0}^i\dfrac{i!}{j!}\\
&=n!\sum_{i=0}^n \dfrac{1}{(n-i)!}\sum_{j=0}^i\dfrac{1}{j!}\\
&=n!\sum_{i=0,j=0}^{i+j\leq n}\dfrac{1}{i!j!}\\
&=n!\sum_{i=0}^n\sum_{j=0}^i\dfrac{1}{j!(i-j)!}\\
&=n!\sum_{i=0}^n\dfrac{\sum_{j=0}^iC_i^j}{i!}\\
&=n!\sum_{i=0}^n\dfrac{2^i}{i!}
\end{aligned}
$$

以 $0$ 为终点的贡献：

$$
\sum_{i=0}^nC_{n,i}i!=n!\sum\dfrac{1}{i!}
$$

$i=j$ 的贡献：

$$
2^n-1
$$

所以总的答案为：

$$
\left(n!\sum_{i=0}^n\dfrac{2^i-1}{i!}\right)-2^n+1
$$

---

## 作者：wcyQwQ (赞：1)

容易得到在图上走一条边的实质是将 $x$ 的一个 $1$ 变成 $0$，所以如果 $x$ 能走到 $y$，那么 $y$ 一定是 $x$ 的子集，方案数即为 $\text{popcount}(x \oplus y)!$。
所以答案即为

$$
\sum_{i = 1}^n i! \sum_{x, y} [y \subset x, \text{popcount}(x \oplus y) = i]
$$

然后我们考虑枚举 $\text{popcount}(x) = j$，那么这样的 $x$ 共有 $\binom{n}{j}$ 个，此时我们要求 $\text{popcount}(y) =j - i$，这样的 $y$ 共有 $\binom{j}{j - i} = \binom{j}{i}$ 个。

然后我们即可得到答案为

$$
\begin{aligned}
&\sum_{i = 1}^ni!\sum_{j = i +1}^n \binom{n}{j}\binom{j}{i} \\
&= \sum_{i = 1}^ni!\sum_{j = i + 1}^n\binom{n}{i}\binom{n - i}{j - i}\\
&=\sum_{i = 1}^n \dfrac{n!}{(n - i)!}\sum_{j = 1}^{n - i}\binom{n - i}{j}\\
&=n!\sum_{i = 0}^{n - 1}\dfrac{2^i - 1}{i!} 
\end{aligned}
$$

线性处理阶乘逆元即可做到 $O(n + T)$。

---

## 作者：orange_new (赞：0)

首先，观察到如果 $x \operatorname{xor} y = 2^k,k \in [1,n)$，那么 $x$ 和 $y$ 的二进制位上有且仅有一位不同。

其次，还要保证 $x > y$，那么只有当 $y$ 是将 $x$ 的某二进制位 $1$ 变为 $0$ 时，才可以使两个性质都成立。

考虑求 $\displaystyle\sum_{i=1}^{2^n}\sum_{j=1,j \neq i}^{2^n}f(i,j)$，如果枚举点对，那么复杂度一定超，于是我们枚举每种长度的线段的个数，动态考虑该问题，每走一步，就将二进制位上的某个 $1$ 变为 $0$，直到二进制位上只有一个 $1$ 为止。

就可以发现，从一个数出发存在长度为 $n$ 的路径，当且仅当这个数二进制位上 $1$ 的个数大于 $n$。

现在有 $2^n$ 个点，因此每个数都可以表示成一个 $n$ 位二进制数，可以先枚举这个数的二进制位上有多少个 $1$，再钦定哪几个位上是 $1$，最后确定删几个 $1$ 以及删 $1$ 的顺序。

现在，答案就变成了求 $\displaystyle\sum_{i=2}^n \binom ni \sum_{j=1}^{i-1} i^{\underline{j}}$

~~无脑~~大力推式子：原式 

$\begin{aligned} &= \displaystyle\sum_{i=2}^n \sum_{j=1}^{i-1} \binom ni i^{\underline{j}} \\&= \sum_{i=2}^n \sum_{j=1}^{i-1} \binom ni \binom ij j! \\&=  \sum_{i=2}^n \sum_{j=1}^{i-1} \binom nj \binom{n - j}{i - j} j! \\&=  \sum_{j=1}^{n - 1} \sum_{i=j+1}^{n} \binom nj \binom{n - j}{i - j} j! \\&= \sum_{j=1}^{n - 1} \binom nj j! \sum_{i=j+1}^{n} \binom{n - j}{i - j}\\ &= \sum_{j=1}^{n - 1} \binom nj j! (2^{n-j}-1) \end{aligned}$

已经 $O(n)$ 不能再优化了，但这道题的数据十分~~可爱~~极限，导致我们只能递推预处理qwq。

将括号拆开，得：$\displaystyle\sum_{j=1}^{n - 1} \binom nj j! 2^{n-j} - \sum_{j=1}^{n - 1} \binom nj j!$

现在两边都可以预处理，那这道题就做完了。

代码（其实不长）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e7 + 9, mod = 998244353;
int ans1[N], ans2[N], mi;
int t;
signed main(){
	ans1[1] = ans2[1] = 0;
	ans1[2] = 2, ans2[2] = 4;
	mi = 4;
	for(int i = 3; i <= 1e7; i++){
		ans1[i] = (ans1[i - 1] * i + i) % mod;//减号左边递推 
		ans2[i] = (ans2[i - 1] * i + i * mi) % mod;//减号右边递推 
		mi = mi * 2 % mod;
	}
	scanf("%d",&t);
	while(t--){
		int x;
		scanf("%d",&x);
		printf("%lld\n",(ans2[x] - ans1[x] + mod) % mod);
	}
	return 0;
} 
```

---

## 作者：__O_v_O__ (赞：0)

首先，我们观察到：$x$ 到 $y$ 有有向边，需要 $x\operatorname{xor} y=2^k$，也就是 $x$ 和 $y$ 的二进制有且仅有一位不同。而 $x>y$，所以 $y$ 就是把 $x$ 二进制某一个为 $1$ 的位变为 $0$。

所以，题中条件就相当于：一个数可以把它二进制的某一个为 $1$ 的位变为 $0$。

有了这个，我们来看 $f_{i,j}$。因为我们要把 $x$ 变为 $y$，所以需要将 $x$ 二进制的每一位变为 $y$ 的每一位。

如果 $x$ 的某一位为 $0$，而 $y$ 的这一位为 $1$，则必然不能变换，$f_{i,j}=0$。否则，$x$ 和 $y$ 有 $\operatorname{popcount}(x\oplus y)$ 位不同，而这些位可以以任意顺序操作，所以 $f_{x,y}=\operatorname{popcount}(x\oplus y)!$。

我们发现，直接计算这个的和还是会超时。

考虑一个常见的套路，改为枚举 $\operatorname{popcount}(x\oplus y)$，再计算它的贡献。

当 $\operatorname{popcount}(x\oplus y)=i$ 时，$x$ 和 $y$ 有 $i$ 位不同，这 $i$ 位共有 $\binom{n}{i}$ 种选法。对于剩余的 $n-i$ 位，每一位都可以取 $0$ 或 $1$，但是因为 $x,y>0$，所以不能全取 $1$，共有 $2^{n-i}-1$ 种选法。

所以，此时的贡献为 $\binom{n}{i}(2^{n-i}-1)$，所求的答案变为 $\sum\limits_{i=1}^{n-1}\binom{n}{i}(2^{n-i}-1)i!$。

把 $i!$ 乘进 $\binom{n}{i}$，得到：$\sum\limits_{i=1}^{n-1}(2^{n-i}-1)n^{\underline{i}}$。

拆成 $\sum\limits_{i=1}^{n-1}2^{n-i}n^{\underline{i}}$ 和 $\sum\limits_{i=1}^{n-1}n^{\underline{i}}$ 两部分分别计算，设两部分分别为 $f_i$ 和 $g_i$。

容易得到递推式：$f_i=f_{i-1}\times i+2^{i-1}\times i$ 和 $g_i=g_{i-1}\times i+i$。

这样，我们就成功解决了这道题。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int p=998244353;
int t,n,f[10000001],g[10000001],pw[10000001];
signed main(){
	ios::sync_with_stdio(0);
	cin>>t,pw[0]=1;
	for(int i=1;i<=10000000;i++)
		pw[i]=pw[i-1]*2%p;
	f[2]=4,g[2]=2;
	for(int i=3;i<=10000000;i++){
		g[i]=(g[i-1]*i%p+i)%p;
		f[i]=(f[i-1]*i%p+i*pw[i-1]%p)%p;
	}
	for(int i=1;i<=t;i++){
		cin>>n;
		cout<<(f[n]-g[n]+p)%p<<'\n';
	}
	return 0;
}
```

---

## 作者：vegetable_king (赞：0)

[可能更好的阅读体验](https://yjh965.github.io/post/daily-oi-round-3-xor-graph-ti-jie/)

显然如果 $x$ 能到达 $y$ 一定有 $y \subseteq x$，则我们只需要关心 $x - y$ 的值 $z$。

然后对于一个 $z$，方案数显然是 $\operatorname{popc}(z)!$，因为每次走一条边相当于把 $z$ 中的某一位 $1 \to 0$。

现在只需要计算对于一个 $z$，可以得到这个 $z$ 的 $(x, y)$ 对的数量，显然是 $2^{n - \operatorname{popc}(z)}$，因为对于某一位，如果 $x, y$ 在这一位上相同，可以都填 $0 / 1$。

于是我们考虑枚举 $\operatorname{popc}(z)$，则对应的 $z$ 就有 $\binom n{\operatorname{popc}(z)}$ 种。整合一下得到式子：
$$
ans(n) = \sum_{k = 0}^n \binom nk k! 2^{n - k}
$$
可以 $O(n)$ 单次计算。把二项式展开可以得到：
$$
\begin{aligned}
ans(n) &= \sum_{k = 0}^n \frac{n!}{(n - k)!k!} k!2^{n - k}\\
&= \sum_{k = 0}^n \frac{n!}{(n - k)!} 2^{n - k}\\
&= n! \sum_{k = 0}^n \frac{2^{n - k}}{(n - k)!} \\
&= n! \sum_{k = 0}^n \frac{2^k}{k!}\\
\end{aligned}
$$
预处理前缀和即可，可以做到 $O(n + T)$。

去掉 $x = y$ 以及 $y = 0$ 的贡献是简单的，这里不再赘述。

---

## 作者：TianTian2008 (赞：0)

容易发现，存在一条边 $x\rightarrow y$ 当且仅当 $y\in x,\text{ppc}(x)=\text{ppc}(y)+1$。所以走过一条边可以看作选择 $x$ 二进制下的一位 $1$ 丢掉。

考虑如何计算 $f_{x,y}(y\in x)$，其必然恰好经过 $\text{ppc}(x-y)$ 条边，每次丢掉 $x-y$ 二进制下的一个 $1$，显然 $f_{x,y}=\text{ppc}(x-y)!$。

化简要求的式子

$\begin{aligned}
&\sum_{i=1}^{2^n}\sum_{j=1}^{2^n}f_{i,j}(i\neq j)
\\=&\sum\limits_{x=1}^n\binom nx\sum\limits_{y=1}^{x-1}\binom xy(x-y)!
\end{aligned}$

$\binom nx$ 是 $\text{ppc}(i)=x$ 的 $i$ 的个数，$\binom xy$ 是 $\text{ppc}(j)=y,j\in i$ 的 $j$ 的个数

$\begin{aligned}
=&\sum\limits_{x=1}^n\frac{n!}{x!(n-x)!}\sum\limits_{y=1}^{x-1}\frac{x!}{y!(x-y)!}(x-y)!
\\=&n!\sum\limits_{x=1}^n\frac1{(n-x)!}\sum\limits_{y=1}^{x-1}\frac1{y!}
\end{aligned}$

因为有多次询问，所以需要预处理到能 $O(1)$ 查询。现在这个形式还不能预处理，但是化简化不动了。取个巧，转成生成函数。为了防止枚举变量 $x$ 和生成函数的 $x$ 搞混，以下的枚举变量改为 $i$

$\begin{aligned}
=&n!\sum\limits_{i=1}^n([x^{n-i}]e^x)([x^{i-1}]\frac{e^x}{1-x})
\\=&n!\sum\limits_{i=1}^n[x^{i-1}]\frac{e^{2x}}{1-x}
\\=&n!\sum\limits_{i=1}^n\sum\limits_{j=0}^{i-1}\frac{2^j}{j!}
\end{aligned}$

现在的形式就可以预处理了。

```cpp
#include <iostream>
#include <cstdio>
#define mod 998244353
using namespace std;
typedef long long ll;
ll t,n,fac[10000001],f[10000001];
ll ksm(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
void init(ll n) {
	ll cur=1;
	for(int i=1;i<=n;++i) cur=cur*i%mod;
	cur=ksm(cur,mod-2);
	for(int i=n;i>=0;--i) {
		fac[i]=cur;
		cur=cur*i%mod;
	}
	ll pw=1,s1=0,s2=0;
	for(int i=0;i<=n;++i) {
		s1=(s1+pw*fac[i])%mod;
		s2=(s2+fac[i])%mod;
		pw=pw*2%mod;
		f[i]=s1-s2;
	}
	fac[0]=1;
	for(int i=1;i<=n;++i) fac[i]=fac[i-1]*i%mod;
}
int main() {
	init(10000000);
	scanf("%lld",&t);
	while(t--) {
		scanf("%lld",&n);
		printf("%lld\n",(f[n-1]*fac[n]%mod+mod)%mod);
	}
	return 0;
}
```

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/P10128)

## 题意

给定 $2^n$ 个点，编号为 $1\sim 2^n$，两个点 $x,y$ 之间有一条有向边当且仅当 $y\ \text{or}\ x=x,y\ \text{xor}\ x=2^k(k\in[0,n))$。令 $f_{x,y}$ 为 $x$ 点到 $y$ 点的不同路径数，求： 

$$\sum_{i=1}^{2^n}\sum_{j=1}^{2^n}f_{i,j}(i\neq j)$$

答案对 $998244353$ 取模。

## 分析

把编号的二进制表示看成集合，那么对于一条边 $x\rightarrow y$，$y$ 是 $x$ 仅少了一个元素的子集。

显然点 $2^n$ 是没用的，因为没有点 $0$。对于任意 $y\ \text{or}\ x=x$，从 $x$ 走到 $y$ 相当于去掉 $\operatorname{popcount}(y\ \text{xor}\ x)$ 个元素，有 $f(x,y)=\operatorname{popcount}(y\ \text{xor}\ x)!$ 种路径，其他情况 $f(x,y)=0$。

但这样计算仍然是 $O(2^{2n})$ 的，考虑换个计算方式，把路径数相同的点对拿出来算，有

$$\sum_{i=1}^{2^n}\sum_{j=1}^{2^n}f_{i,j}(i\neq j)$$
$$=\sum_{y\ \text{or}\ x=x}\operatorname{popcount}(y\ \text{xor}\ x)!$$
$$=\sum_{i=1}^ni!\sum [\operatorname{popcount}(y\ \text{xor}\ x)=i]$$

$\sum [\operatorname{popcount}(y\ \text{xor}\ x)=i]$ 相当于 $y$ 与 $x$ 有 $i$ 位不同的方案数，选出他们不同的位有 $C_n^i$ 种方案，相同的位有 $2^{n-i}-1$ 种方案（$y$ 不能为 $0$），所以：

$$\sum_{i=1}^ni!\sum [\operatorname{popcount}(y\ \text{xor}\ x)=i]$$
$$=\sum_{i=1}^ni!C_n^i(2^{n-i}-1)$$
$$=\sum_{i=1}^n\frac{n!}{(n-i)!}(2^{n-i}-1)$$
$$=n!\sum_{i=0}^{n-1}\frac{2^i-1}{i!}$$

后面那个和式显然是可以预处理前缀和的，于是这道题就解决了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch))
	{if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e7+10;
const ll mod=998244353;
int n;
int fac[N],inv[N],m2[N],sum[N];
ll qmi(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;b>>=1;
	}
	return ans;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	fac[0]=inv[0]=m2[0]=1;
	for(int i=1;i<=N-2;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[N-2]=qmi(fac[N-2],mod-2);
	for(int i=N-3;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(int i=1;i<=N-2;i++)m2[i]=m2[i-1]*2%mod;
	sum[0]=0;
	for(int i=1;i<=N-2;i++){
		sum[i]=(sum[i-1]+1ll*(m2[i]-1+mod)%mod*inv[i]%mod)%mod;
	}
	int T=read();
	while(T--){
		n=read();
		write(1ll*sum[n-1]*fac[n]%mod);
		puts("");
	}
	return 0;
}
```


---

## 作者：masonpop (赞：0)

这里给出我的赛时做法。

首先注意到，$x\oplus y=2^k,x>y$ 中的 $y$ 可以直接由 $x$ 生成，即将 $x$ 二进制表示中的某个 $1$ 变成 $0$。

枚举 $x$ 中 $1$ 的个数以及 $y$ 中 $1$ 的个数，并统计方案数，可以得到答案为

$F_n=\sum\limits_{i=1}^nC_n^i\sum\limits_{j=1}^{i-1}C_i^j(i-j)!$

利用 $C_n^m=\dfrac{n!}{m!(n-m)!}$ 展开组合数，得到：

$F_n=n!\sum\limits_{i=1}^n\dfrac{1}{(n-i)!}\sum\limits_{j=1}^{i-1}\dfrac{1}{j!}$

定义 $G_n=F_n/n!$ 并对上式交换求和，得到：

$G_n=\sum\limits_{j=1}^{n-1}\dfrac{1}{j!}\sum\limits_{i=0}^{n-1-j}\dfrac{1}{i!}$

到这里可以用前缀和做到单次 $O(n)$ 了。为了做到多测，需要找到 $G_n$ 的递推关系。

注意到 

$G_{n+1}=G_n+\sum\limits_{j=1}^n\dfrac{1}{j!(n-j)!}$

后面那个式子很像组合数的展开形式，将其变回组合数，得到

$G_{n+1}=G_n+\dfrac{\sum\limits_{j=1}^nC_n^j}{n!}$

上面那个式子的结论是熟知的，于是得到

$G_{n+1}=G_n+\dfrac{2^n-1}{n!}$

$O(n)$ 预处理 $O(1)$ 查询即可。[代码](https://www.luogu.com.cn/paste/m7bbv4z6)。

---

## 作者：Richard_Whr (赞：0)

展现一个推式子新手的全部思维过程，纪念第一道自己推出式子的题目。

题意：

有 $2^n$ 个点，$x$ 到 $y$ 有**有向**边当且仅当 $x\operatorname{xor} y=2^k,k \in [0,n)$，且 $x>y$。

其中，$\operatorname{xor}$ 表示按位异或，$k$ 为整数。令 $f_{x,y}$ 为 $x$ 点到 $y$ 点的不同路径数，

求： 

$$\sum_{i=1}^{2^n}\sum_{j=1}^{2^n}f_{i,j}(i\neq j)$$

答案对 $998244353$ 取模。

多测

$1 \le T \le 10^6$，$1 \le n \le 10^7$。

首先我们先从边入手，找到一些性质。

发现两个点 $a,b$ 存在边，就等价于：

- $a$ 的二进制表示与 $b$ 就差一位

- 不一样的一位上，$a$ 为 $1$，$b$ 为 $0$.

那么现在可以转化题意了：一条路径等价于：从一个点开始，不断将其二进制表示中的某位 $1$ 变为 $0$。

到这里就会发现，哦只要二进制表示中 $1$ 的个数一样，这两个点其实是等价的，可以一起处理。

现在假设当前这个点有 $x$ 个 $1$。

- 这样的数有 $C_{n}^{x}$ 个；

- 对于那些比这个数多 $i$ 个 $1$ 的数：

	- 这样的数有 $C_{n-x}^{i}$ 个；
    
   - 这 $i$ 个 $1$，可以以任意顺序剔除掉，每一种顺序都对应一种走法，因此贡献为 $i!$ 
   
将其形式化的总结：

$$Ans=\sum_{x=1}^{n-1}\sum_{i=1}^{n-x}C_{n}^{x} \times C_{n-x}^{i} \times n!$$

整理上下约分，可得：

$$Ans=\sum_{x=1}^{n-1}\sum_{i=1}^{n-x}\frac{n!}{x! \times (n-x-i)!}$$

发现 $n!,x!$ 都与 $i$ 无关，直接提出来。

$$Ans=\sum_{x=1}^{n-1}\frac{n
!}{x!}\sum_{i=1}^{n-x}\frac{1}{(n-x-i)!}$$
    
发现后面这个东东其实是个前缀和，自己带一下数就发现了

令 $fac[n]=n!,ifac[n]=n!^{-1}$，注意都是模意义下的，其实就是阶乘和阶乘逆元。

再次整理：

$$Ans=\sum_{x=1}^{n-1}fac[n]\times ifac[x]\sum_{i=0}^{n-1-x}ifac[i]$$

容易发现进行前缀和，可以有：
$$S[n]=\sum_{i=0}^{n}ifac[i]$$

$$Ans=\sum_{x=1}^{n-1}fac[n]\times ifac[x]\times s[n-1-x]$$

将前面的常量阶乘提出来，就有：

$$Ans=fac[n]\times \sum_{x=1}^{n-1} ifac[x]\times s[n-1-x]$$

至此，我们已经将复杂度从平方级别优化到了线性，但是还不够，需要对数甚至常数级别，因此我们继续观察这个式子。

线性的很适合递推，我们尝试进一步优化。

为了方便啊，我们只需要研究后面那坨东西：

令：

$$f(n)=\sum_{i=1}^{n} ifac[i]\times s[n-i]$$

那么：

$$Ans=fac[n] \times f(n-1)$$

刚刚学了函数的周期性质，递推也一样，往下写一项往往可以发现问题：

$$f(n-1)=\sum_{i=1}^{n-1} ifac[i]\times s[n-1-i]$$

这个函数其实差别并不大，我们将 $f(n)$ 用 $f(n-1)$ 来进行表示：

$$f(n)=(\sum_{i=1}^{n-1} ifac[i]\times (s[n-1-i]+ifac[n-i]))+ifac[n]\times s[0]$$

$$f(n)=(\sum_{i=1}^{n-1} ifac[i]\times s[n-1-i])+(\sum_{i=1}^{n-1}ifac[i]\times ifac[n-i])+ifac[n]\times s[0]$$

$$f(n)=f(n-1)+(\sum_{i=1}^{n-1}ifac[i]\times ifac[n-i])+ifac[n]\times s[0]$$

诶呀，到这里呀，发现又出了一个新东西，就是中间那部分，那就不妨再搞一个函数：

令：

$$g(n)=\sum_{i=1}^{n-1}ifac[i]\times ifac[n-i]$$

那么：

$$f(n)=f(n-1)+g(n)+ifac[n]\times s[0]$$

最自然的思路是和上面的方法一样，我们往下写一项：

$$g(n-1)=\sum_{i=1}^{n-2}ifac[i]\times ifac[n-1-i]$$

继续将 $g(n)$ 用 $g(n-1)$ 表示：

$$g(n)=\sum_{i=1}^{n-2} ifac[i] \times ifac[n-1-i] \times \frac{1}{n-i}+ …$$

可是当你写到这里的时候，你就意识到了问题并不是那么简单，因为这拆出来变成乘法了，不能分出去了。

这时候，将东西写为最原始，最直观的式子，往往更有利于思考：

$$g(n)=\sum_{i=1}^{n-1}\frac{1}{i!\times (n-i)!}$$

如果你熟练地记住了组合公式：

$$C_{n}^{m}=\frac{n!}{m!\times(n-m)!}$$

你就会反映出来可以这样变换：


$$g(n)=\sum_{i=1}^{n-1}\frac{C_{n}^{i}}{n!}$$

将 $n!$ 提出来：

$$g(n)= ifac[n] \times \sum_{i=1}^{n-1}C_{n}^{i}$$

如果你熟练地记住了二项式定理，或者学过了求集合地子集个数：

$$(a+b)^n=\sum_{i=0}^{n} C_{n}^{i} \times a^i \times b^{n-i}$$

你就可以发现这东西可以化简为：

$$g(n)= ifac[n] \times (2^n-C_{n}^{0}-C_{n}^{n})$$

$$g(n)= ifac[n] \times (2^n-2)$$

ok，至此，$g$ 函数已经可以递推求出。

有了 $g$ 函数，$f$ 也可以线性推出。

我们还需要一些辅助工具，不过这都是老生常谈的了：

- 阶乘；

- 阶乘逆元（注意需要线性递推）；

- $2$ 的 $n$ 次幂；

最后附上我写了将近 2h 的代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5,mod=998244353;
int fac[N],ifac[N];
int mi[N];
int s[N],ss[N];
int f[N],g[N];
int n;

int qmi(int a,int k)
{
	int res=1;
	while(k)
	{
		if(k&1) res=res*a%mod;
		k>>=1;
		a=a*a%mod;
	} 
	return res;
}

void init()
{
	fac[0]=ifac[0]=1;
	for(int i=1;i<=N-1;i++) fac[i]=fac[i-1]*i%mod;
	ifac[N-1]=qmi(fac[N-1],mod-2);
	for(int i=N-2;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
    mi[0]=1;
    for(int i=1;i<=N-1;i++) mi[i]=mi[i-1]*2%mod;
	s[0]=ifac[0];
	for(int i=1;i<=N-1;i++) s[i]=(s[i-1]+ifac[i])%mod;
	for(int i=1;i<=N-1;i++) g[i]=ifac[i]*(mi[i]-2+mod)%mod;
	for(int i=1;i<=N-1;i++) f[i]=((f[i-1]+g[i])%mod+ifac[i]*s[0]%mod)%mod;
}
int T;
 
signed main()
{	
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);

	init();
	
	cin>>T;
	while(T--)
	{
		cin>>n;
		cout<<fac[n]*f[n-1]%mod<<"\n";
	}
	
	return 0;
}
```



 
 
 
 

---

