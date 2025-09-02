# Calculating

## 题目描述

若 $x$ 分解质因数结果为 $x=p_1^{k_1}p_2^{k_2}\cdots p_n^{k_n}$，令$f(x)=(k_1+1)(k_2+1)\cdots (k_n+1)$，求 $\sum_{i=l}^rf(i)$ 对 $998\,244\,353$ 取模的结果。

## 说明/提示

#### 数据规模与约定

| 测试点编号 | $l$ | $r$ | $r-l$ |
| :----------: | :----------: | :----------: | :----------: |
| $1\sim 3$ | $1\le l\le 10$ | $1\le r\le 10$ | $r-l=0$ |
| $4\sim 7$ | $1\le l\le 50$ | $1\le r\le 50$ |$r-l=0$ |
| $8\sim 10$ | $1\le l\le 100$ | $1\le r\le 100$ |$r-l<50$ |
| $11\sim 16$ | $1\le l\le 500$ | $1\le r\le 500$ | 无特殊限制 |
| $17\sim 25$ | $1\le l \le 10^3$ | $1\le r \le 10^3$ | 无特殊限制 |
| $26\sim 30$ | $1\le l \le 5\times 10^3$ | $1\le r \le 5\times 10^3$ | $r-l<100$ |
| $31\sim 40$ | $1\le l \le 10^4$ | $1\le r \le 10^4$ |无特殊限制  |
| $41\sim 60$ | $1\le l \le 10^7$ | $1\le r \le 10^7$ | 无特殊限制 |
| $61\sim 70$ | $1\le l \le 10^9$ | $1\le r \le 10^9$ | 无特殊限制 |
| $71\sim 90$ | $1\le l \le 10^{12}$ | $1\le r \le 10^{12}$ | 无特殊限制 |
| $91\sim 95$ | $1\le l \le 10^{13}$ | $1\le r \le 10^{13}$ | 无特殊限制 |
| $96\sim 97$ | $1\le l \le 2\times 10^{13}$ | $1\le r \le 2\times 10^{13}$ | $r-l<10^{13}$ |
| $98\sim 99$ | $1\le l \le 10^{13}$ | $1\le r \le 10^{14}$ | $r-l>9\times 10^{13}$ |
| $100$ | $1\le l \le 10^{14}$ | $1\le r \le 1.6\times 10^{14}$ | $r-l>10^{14}$ |

## 样例 #1

### 输入

```
2 4```

### 输出

```
7```

# 题解

## 作者：KesdiaelKen (赞：48)

看到$\sum^r_{i=l}f(i)$，我们应该容易想到将它转化成$\sum^r_{i=1}f(i)-\sum^{l-1}_{i=1}f(i)$（容斥基本操作）。但是这个东西怎么求呢？

下面，我们引出两个定理和一个算法。

## 1.因数个数定理

设$n=p_1^{a_1}*p_2^{a_2}*...*p_m^{a_m}$，其中$p_1,p_2,...,p_m$均为互不相等的质数（$n$的质因数），则$n$的因数个数为$\prod_{i=1}^m{(a_i+1)}$。

**证明：**

设$n$的一个约数为$k$，则$k$必能表示为$p_1^{b_1}*p_2^{b_2}*...*p_m^{b_m}$，其中$\left\{{b_1,b_2,...,b_m} \right\}\in N$。则$b_i$的取值总共有$a_i+1$种。所以k的取值总共有$$\prod_{i=1}^m{(a_i+1)}$$
$$\mathcal{Q.E.D}$$

## 2.（我也不知道它叫什么名字）

设$f(x)$表示$x$的约数个数，求$\sum^n_{i=1}f(x)$。

**解：**

对于$f(x)$我们可以进行适当的转换得到一个与之相等的式子：$$\sum^n_{i=1}[i|x]$$

再对其进行转换：

$$\sum^n_{i=1}\sum^{\lfloor\frac{n}{i}\rfloor}_{j=1}[i*j==x]$$

看起来是更加复杂了。我们再将它带到原式中：

$$\sum^n_{i=1}f(x)=\sum^n_{x=1}\sum^n_{i=1}\sum^{\lfloor\frac{n}{i}\rfloor}_{j=1}[i*j==x]=\sum^n_{i=1}\sum^{\lfloor\frac{n}{i}\rfloor}_{j=1}=\sum^n_{i=1}\lfloor\frac{n}{i}\rfloor$$

完成了转换。

## 3.整除分块

它的主要功能，就是将一个形如$\sum^n_{i=1}\lfloor\frac{n}{i}\rfloor$（当然不是只能在这个式子上应用，但它的确是最经常应用到整除分块的式子，没有之一）的式子的求值时间复杂度从$O(n)$降到$O(\sqrt n)$。

整除分块能实现基于这样一个事实：$\lfloor\frac{n}{i}\rfloor$的取值总共不会超过$2\sqrt n$种。为什么呢，我们来**证明**一下：

**当$i<=\sqrt n$时：**

我们需要证明：$\lfloor\frac{n}{i}\rfloor\not=\lfloor\frac{n}{i+1}\rfloor$

我们设$n\div i=k...s$，那么就有$n=i*k+s$。根据除法的性质，$s<i$，而又因为$i<=\sqrt n$，所以$k>=\sqrt n>=i$，所以$s<k$。

如果$\lfloor\frac{n}{i}\rfloor=\lfloor\frac{n}{i+1}\rfloor$，那么$n$就可以表示为$(i+1)*k+p$（$p>=0$），即$n=i*k+s+(k+p-s)=n+(k+p-s)$。而我们又知道$k-s>0,p>=0$。所以$k+p-s>0$，即等式两边矛盾。所以由反证法我们就得到了$\lfloor\frac{n}{i}\rfloor\not=\lfloor\frac{n}{i+1}\rfloor$。因此，在此情况下$\lfloor\frac{n}{i}\rfloor$的取值个数就等于$i$的取值数，即$\sqrt n$种。

**当$i>\sqrt n$时：**

这个不用怎么说了吧……$\lfloor\frac{n}{i}\rfloor_{max}$都已经是小于$\sqrt n$的了，总取值数当然不超过$\sqrt n$啊。

所以，两类加起来就是$2\sqrt n$种了。$$\mathcal{Q.E.D}$$

既然证玩了这个结论，我们就可以考虑这样一个思路：因为$\lfloor\frac{n}{i}\rfloor$的取值数为$\sqrt n$（那个$2$是常数，可以忽略），那么只要求出它取每一种值时$i$的最大值和最小值是多少，最终求和的时候用前缀和预处理算一下每一段的值是多少，加起来就可以了。

**那么接下来，我们又需要证明一个结论了：**

如果已知正整数$p,n$（$n>=p$），则使$\lfloor\frac{n}{i}\rfloor=\lfloor\frac{n}{p}\rfloor$的最大整数$i$的值就是$i_{max}=\lfloor\frac{n}{\frac{n}{p}}\rfloor$。

**证明：**

我们同样分类讨论一下。

**当$p<=\sqrt n$时：**

我们设$n\div p=k...s$，那么就有$n=p*k+s$。根据除法的性质，$s<p$，而又因为$p<=\sqrt n$，所以$k>=\sqrt n>=p$，所以$s<k$。而$\lfloor\frac{n}{p}\rfloor$的值就是$k$。

那么，就会有$\lfloor\frac{n}{\frac{n}{p}}\rfloor=\lfloor\frac{n}{k}\rfloor$。在此基础上，让我们再证明一个结论：$\lfloor\frac{n}{k}\rfloor=p$。我们令$n\div k=(p+t)...w$，则$n=p*k+t*k+w$。又因为$n=p*k+s$而，所以$n=p*k+t*k+w=n+(t*k+w-s)$，所以$t*k+w-s=0$。因为$k>w$且$k>=\sqrt n$，所以我们可以得出：$w,s\in[0,\sqrt n)$。所以：$(w-s)\in(-\sqrt n,\sqrt n)$。又因为$k>=\sqrt n$，所以$t$必须为$0$。所以$\lfloor\frac{n}{k}\rfloor=p$就证完了。而又由我们上面证的结论：$\lfloor\frac{n}{i}\rfloor$的取值总共不会超过$2\sqrt n$种可以知道当$p<=\sqrt n$的时候，所有$\lfloor\frac{n}{p}\rfloor$的值都不相同，即$p=i_{max}$。所以$i_{max}=\lfloor\frac{n}{\frac{n}{p}}\rfloor$，得证了。

**当$p>\sqrt n$时：**

我们设$n\div p=k...s$，那么就有$n=p*k+s$。根据除法的性质，$s<p$。而$\lfloor\frac{n}{p}\rfloor$的值就是$k$。

那么，就会有$\lfloor\frac{n}{\frac{n}{p}}\rfloor=\lfloor\frac{n}{k}\rfloor$。而我们现在要证明的，就是$\lfloor\frac{n}{k}\rfloor=i_{max}$。看上去很难证，但是我们注意到$i_{max}$必须符合且只需要符合的两个条件：$\lfloor\frac{n}{i_{max}}\rfloor=\lfloor\frac{n}{p}\rfloor=k,\lfloor\frac{n}{i_{max}+1}\rfloor\not=\lfloor\frac{n}{p}\rfloor=k$。那么，如果我们需要证明$\lfloor\frac{n}{k}\rfloor=i_{max}$，那么就只需要说明$\lfloor\frac{n}{\lfloor\frac{n}{k}\rfloor}\rfloor=\lfloor\frac{n}{p}\rfloor=k\space\space and\space\space\lfloor\frac{n}{\lfloor\frac{n}{k}\rfloor+1}\rfloor\not=\lfloor\frac{n}{p}\rfloor=k$。看到$\lfloor\frac{n}{\lfloor\frac{n}{k}\rfloor}\rfloor=k$你想到了什么？

聪明的读者一定已经想到了，因为这个$k<\sqrt n$（讲了这么多这个不可能不会自行理解吧），所以这个结论在上面讨论$p<=\sqrt n$的时候已经证过了。所以，得证啦！

$$\mathcal{Q.E.D}$$

综合上面两个结论，我们便可以得出整除分块的思路了：

1. 令$i=1$

2. 对于当前的$i$求得$i_{max}$，设为$j$

3. 通过前缀和或公式（例如等差数列公式）求得函数（$\sum_{i=1}^nf(i)$中的$f(i)$）的自变量从$i$一直到$j$的函数值的总和，并且加进$sum$

4. 我们已知$\lfloor\frac{n}{j}\rfloor\not=\lfloor\frac{n}{j+1}\rfloor$，所以我们让$i=j+1$。如果现在的$i$仍然小于$n$，则跳转第$2$步，否则结束

最终得到的$sum$就是答案了。

综合上面的三项内容，思路就很明显了，相信各位如果仔细看了的话，一定已经完全明白这道题该怎么做了。

代码：

```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	long long left,right;
	scanf("%lld%lld",&left,&right);
	long long sum1=0,sum2=0;
	for(long long zuo=1,you;zuo<=right;zuo=you+1)
	{
		you=right/(right/zuo);
		sum1=(sum1+(right/zuo)%998244353*((you-zuo+1)%998244353)%998244353)%998244353;
	}
	for(long long zuo=1,you;zuo<=left-1;zuo=you+1)
	{
		you=(left-1)/((left-1)/zuo);
		sum2=(sum2+((left-1)/zuo)%998244353*((you-zuo+1)%998244353)%998244353)%998244353;
	}
	printf("%lld\n",((sum1-sum2)%998244353+998244353)%998244353);//熟练运用取余操作的一些技巧
	return 0;
}
```

---

## 作者：Snakes (赞：21)

#### 算法一


我会推公式！


将$f$分解质因数得到$f=p_1^{k_1}p_2^{k_2}..p_j^{a_j}$，则题目实际上要求：


$$ans=\sum_{f=l}^r\prod_{i=1}^j p_i^{a_i+1}$$


记$f$因数个数为$d(f)$，则由排列组合可得：


$$\prod_{i=1}^j p_i^{a_i+1}=d(f)$$


则原式化为：


$$ans=\sum_{f=l}^rd(f)$$


暴力统计答案。时间复杂度$O(r^2)$，期望得分$40$。


#### 算法二


我会拆询问！


实际上，我们有：


$$ans=\sum_{i=1}^rd(i)-\sum_{j=1}^{l-1}d(j)$$


考虑如何求$\sum_{i=1}^rd(i)$，对于$[1,r]$的整数$k$，$k$作为因数在$[1,r]$中出现了$\left\lfloor \frac rk \right\rfloor$次，显然对答案的贡献为$\left\lfloor \frac rk \right\rfloor$。


则：

$$ans=\sum_{i=1}^r\left\lfloor \frac ri \right\rfloor-\sum_{j=1}^{l-1}\left\lfloor \frac {l-1}j \right\rfloor$$


枚举$k$，统计答案。时间复杂度$O(2r)$，期望得分$60$到$70$之间。


#### 算法三


我会分块！


注意到$\left\lfloor \frac rk \right\rfloor$最多有$2\sqrt r$种取值，我们对其分类统计答案即可。做法类似没有莫比乌斯函数的莫比乌斯反演。


时间复杂度$O(4\sqrt r)$，可通过全部测试点。


**PS:**至于为什么会有$100$个测试点……这是个好问题。


---

## 作者：学委 (赞：18)

Dalao `KesdiaelKen` 的题解的简化证明版 QwQ。

> 看到$\sum^r_{i=l}f(i)$，我们应该容易想到将它转化成$\sum^r_{i=1}f(i)-\sum^{l-1}_{i=1}f(i)$（容斥基本操作）。但是这个东西怎么求呢？

> 下面，我们引出两个定理和一个算法。

## １.因数个数定理

* 若 $x$ 分解质因数结果为 $x = p_1^{k_1}p_2^{k_2} \cdots p_n^{k_n}$，则 **$x$ 的因数个数 $ = (k_1+1)(k_2+1)\cdots(k_n+1)$**。

**证明：**

* $x$ 的一个因数，肯定是这样的：**它**拥有的质因子，$x$ 都有，而且**它**的这个质因子的数目不能比 $x$ 的多。

* $x$ 的因数就是 $x$ 的众多质因子组合出来的。即，$x$ 的因数 $ = p_1^{t_1}p_2^{t_2} \cdots p_n^{t_n}$、其中每个 $t_i$ 的可以取 $[0, k_i]$。所以因数个数有 $(k_1+1)(k_2+1)\cdots(k_n+1)$ 个。

由此可见，题目求的即是区间内每个数的因数个数的和。

## 2.（我也也不知道它叫什么名字）

设 $f(x)$ 表示 $x$ 的因数个数，计算 $\sum^n_{i=1}f(i)$。

**解：**

[**我这辈子都拿不到普及一等了**](https://www.luogu.org/problemnew/show/P1403)

别从每个 $i$ 的角度去考虑；直接从**每个约数在整个计算过程中的的出现次数（贡献次数）** 考虑。

* $1$ 这个因数作为**每个数**的因数，会在每个 $f(i)$ 中出现。它给答案贡献了 $n$。

* $2$ 作为**每个 $2k$** 的因数，会在每个 $f(2k)$ 中出现。它给答案贡献了 $\lfloor \frac{n}{2} \rfloor$。

* $3$ 作为**每个 $3k$** 的因数，会在每个 $f(3k)$ 中出现。它给答案贡献了 $\lfloor \frac{n}{3} \rfloor$。

* $\cdots$

* $n$ 只能作为 $n$ 的因数，为答案贡献了 $\lfloor \frac{n}{n} \rfloor$。 

这样从各个因数的参与情况考虑，可以得出最终答案就是 $\sum_{i=1}^n \lfloor \frac{n}{i} \rfloor$。

## 3.整除分块

这个方法可以比较快地求 $\sum_{i=1}^n \lfloor \frac{n}{i} \rfloor$。

试试暴力求解上面这个式子。

```cpp
for (int i = 1; i <= n; i++)
	sum += n / i;
```

~~*不难*~~ 发现，过程中很多 $\lfloor \frac{n}{i} \rfloor$ 重复了，而且 $i$ 越大，重复就严重。比如 $n = 900000$：从 $\lfloor \frac{900000}{i = 300001} \rfloor$ 到 $\lfloor \frac{900000}{i = 450000} \rfloor$，其实每个都是 $2$，暴力算太浪费时间了。

$\lfloor \frac{n}{i} \rfloor$ 在 $i$ 的递增过程中呈块状分布。一共有多少块呢？即，$\lfloor \frac{n}{i} \rfloor$ 有几种取值呢？其实很少，不超过 $\sqrt{2n}$ 种。

* 从 $i = 1$ 递增到 $i = \sqrt{n}$，过程中一共 $\sqrt{n}$ 个 $i$，所以 $\lfloor \frac{n}{i} \rfloor$ 最多就 $\sqrt{n}$ 种结果。

* 然而，当 $i = \sqrt{n}$ 时，已经导致 $\lfloor \frac{n}{i} \rfloor = \sqrt{n}$；然后 $i$ 继续递增，**但是 $\lfloor \frac{n}{i} \rfloor$ 只可能不断减小，**最小到 $1$，这个过程中 $\lfloor \frac{n}{i} \rfloor$ 最多也就 $\sqrt{n}$ 种结果。

所以“块”的个数是很少的。**要是知道每一块有多宽就好了。**

**下面开始模拟，可跳过阅读。注意，这里把 $\lfloor \frac{n}{i} \rfloor$ 称为 $p$。**

观察 $n = 15$：

```cpp
i =   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
p =  15  7  5  3  3  2  2  1  1  1  1  1  1  1  1
```

**从左往右思考。**（暴力就是从左往右枚举 $i$ 的）

* $i = 1$，此时 $p = 15$；我们期待找到 **$p = 15$ 的最右端（即找到 $p = 15$ 的一大块）**。但是下一项 $p$ 就变成了 $7$，不是同一块内的。

	（其本质原因是，$p = 15$ 的右边界是 $i = \lfloor \frac{15}{p} \rfloor = 1$，别急，待会你就会理解这个本质原因）

* $i = 2, p = 7$；我们期待找到 $p = 7$ 的最右端。但是很失望，下一项 $p$ 就变成了 $4$，不是同一块内的。

	（其本质原因是，$p = 7$ 的右边界是 $i = \lfloor \frac{15}{p} \rfloor = 2$）
* $\cdots$

* 现在 $i = 4, p = 3$；我们期待找到 $p = 3$ 的最右端。怎么找最右端？

	那就是找到一个 **$i_{max}$，满足 $\lfloor \frac{15}{i} \rfloor = 3$**。
    
    等下。观察一下，思考一下。
    
    ...
    
    **整数除法刚刚好能做到！**
    
    答案即 $i_{max} = \lfloor \frac{15}{3} \rfloor = 5$。（不过，这还没有体现向下取整的优势）
    
* 也许 $p = 2$ 时更有利于思考。现在 $i = 6, p = 2$。想找到 $p = 2$ 的最右端，即找到 **$i_{max}$** 满足 $\lfloor \frac{15}{i} \rfloor = 2$。

	如果没有“整数”这一限制，那么 $i = 15 \div 2 = 7.5$；加上“整数”限制呢？$i$ 向下取整就是最大整数。
    
    $i_{max} = \lfloor \frac{15}{2} \rfloor = 7$。
    
* $\cdots$

模拟结束。
    
如果已知正整数 $k,n$ ($n>=k$），设 $p = \lfloor \frac{n}{k} \rfloor$，则使 $\lfloor\frac{n}{i}\rfloor= p$ 的最大整数 $i$ 的值就是 $i_{max}=\lfloor \frac{n}{p} \rfloor$。

**证明：**

由向下取整的定义可得。

```cpp
int SumF(int n) {
  int sum = 0;
  for (int l = 1, r = 1; l <= n; l = r + 1/*来到下一块*/) {
    int p = n / l;//当前取值
    r = n / p;//这个取值块的右端点
    sum += p * (r - l + 1);
  }
  return sum;
}
```

## 整理一下

题目要求 $\sum^r_{i=l}f(i)$，其中 $f(i)$ 就是 $i$ 的因数个数。

$\sum^r_{i=l}f(i) = \sum^r_{i=1}f(i)-\sum^{l-1}_{i=1}f(i)$，因此我们要学会求 $\sum^n_{i=1}f(i)$。

简单推导得 $\sum^n_{i=1}f(i) = \sum_{i=1}^n \lfloor \frac{n}{i} \rfloor$。右边这个能 $O\sqrt{n}$ 求出。

```cpp
#include <cstdio>

const long long MOD = (119 << 23) + 1;

long long SumF(long long n) {
  long long sum = 0;
  for (long long l = 1, r = 1; l <= n; l = r + 1) {
    long long p = n / l % MOD;
    r = n / p;
    sum += p * ((r - l + 1) % MOD), sum %= MOD;
  }
  return sum;
}
int main() {
  long long l, r;
  scanf("%lld %lld", &l, &r);
  printf("%lld\n", (SumF(r) - SumF(l - 1) + MOD) % MOD);
  return 0;
}
```

---

## 作者：jpwang (赞：18)

水水水～～

我们知道$f(x)$实际上在求x的约数个数，令$s(x)=\sum_{i=1}^{x}f(i)$那么
$$ans=s(r)-s(l-1)$$
然后推s
$$s(x)=\sum_{i=1}^{x}\sum_{d|i}1=\sum_{d=1}^{n}\lfloor\frac{n}{d}\rfloor$$
然后下取整根号求，然后就A了


---

## 作者：kikuss (赞：9)

# Solution
如果你做过一些莫比乌斯反演的题,那么这道题可以说就是一个[整除分块](https://www.cnblogs.com/real-l/p/9630810.html)的模板

首先我们需要知道一个定理:**约数个数定理**
设$f(x)$为$x$的约数个数
$$n=\prod_{i=1}^k{p_i^{a_i}}\to f(n)=\prod_{i=1}^m{(a_i+1)}$$
上述式子中,$p_i$为质数
证明:
>由约数定义可知$p1^{a1}$的约数有:$p1^0, p1^1, p1^2......p1^a1$ ，共$(a1+1)$个;同理$p2^{a2}$的[约数](https://baike.baidu.com/item/%E7%BA%A6%E6%95%B0/8417882)有$(a2+1)$个......$pk^{ak}$的约数有$(ak+1)$个。根据乘法原理答案就是上述式子

考虑一下题目所求,
$$Ans=\sum_{i=l}^{r}f(i)$$
转换一下变成
$$Ans=\sum_{i=1}^rf(i)-\sum_{i=1}^{l-1}f(i)$$
对于$f(n)$,我们可以认为
$$f(n)=\sum_{d|n}1$$
令$Ans1=\sum_{i=1}^rf(i)$,由此推出
$$Ans1=\sum_{i=1}^r\sum_{d|i}1$$
更换枚举项,改为枚举i的因子
$$Ans1=\sum_{d=1}^r\lfloor\frac{r}{d}\rfloor$$
同理求出$Ans2$,然后用一下整除分块$O(\sqrt n)$预处理就可以了,不会的看一下我上面放的链接

欢迎踩博客[real_l](https://www.cnblogs.com/real-l/p/9651008.html)
# Code
```cpp
#include<bits/stdc++.h>
#define rg register
#define il inline
#define Min(a,b) (a)<(b)?(a):(b)
#define Max(a,b) (a)>(b)?(a):(b)
#define lol long long
using namespace std;

const lol mod=998244353;

void in(lol &ans) {
	ans=0; lol f=1; char i=getchar();
	while(i<'0' || i>'9') {if(i=='-') f=-1; i=getchar();}
	while(i>='0' && i<='9') ans=(ans<<1)+(ans<<3)+i-'0',i=getchar();
	ans*=f;
}

int main()
{
    lol ans1=0,ans2=0; lol n,m; in(n),in(m),n--;
    for(rg lol l=1,r,len;l<=n;l=r+1) {
        r=n/(n/l),len=r-l+1;
        ans1=(1ll*(ans1%mod+len%mod*(n/l)%mod)%mod)%mod;
    }
    for(rg lol l=1,r,len;l<=m;l=r+1) {
        r=m/(m/l),len=r-l+1;
        ans2=(1ll*(ans2%mod+len%mod*(m/l)%mod)%mod)%mod;
    }
    printf("%lld\n",(ans2-ans1+mod)%mod);//注意这里,最后答案一定要(ans+mod)%mod,不然可能会出现负数
    return 0;
}
```

---

## 作者：LightningUZ (赞：7)

 块状链表块状数组分块，数论数学，期望，概率论,统计，素数判断质数筛法，莫比乌斯反演什么的我一个小学生看不懂啦~
 
首先要看懂这个f函数。根据小学奥数的“因数个数定理”~~不难看出~~f(x)就是求x的因数个数的。

这题给定的l,r，就是求l~r之间所有数因数个数之和。然后可以先求出1~r的因数个数和，1~(l-1)的因数个数和，最后相减。

如何求1~n的因数个数和？见代码。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std; 
const ll mod=998244353;
ll cnt(ll n)
{
	ll sum=0;
    ll t=(ll)sqrt((double)n);
    //sqrt(n)
    for(ll i=1;i<=t;i++)
    {
    	sum+=(n/i)%mod;
	}
    sum*=2;//对称性,最后*2就好了 
    sum=sum-t*t;//记得这里一定要减去多算的 
    sum=(sum%mod+mod)%mod;//注意负数 
    return sum;
}
int main() 
{
    ll l,r;
    scanf("%lld%lld",&l,&r);
    ll ans=cnt(r)-cnt(l-1);
    ans=(ans%mod+mod)%mod;//这边也要注意负数 
	printf("%lld\n",ans);
	return 0; 
}
```

---

## 作者：陈雪森 (赞：4)

**这题是求区间内每个数的因子个数和。**

一想到求区间内的什么什么什么的，就考虑前缀和，发现本题可以用前缀和来求解。用1~r的每个数的因子个数和减去1~l-1的每个数的因子个数和。即为所求答案。

接下来考虑如何快速求出1~l-1的每个数的因子个数和。假设上界为n。
那么1~n中因子i的个数为（n/i）个。
```cpp
for(int i=1;i<=n;i++) ans=(ans+n/i)%mod;
```
由于n的范围过大，就算是O(n)便历一遍。显然也会超时。


接下来考虑用整除分块将O(n)的复杂度降到O(sqrt(n))。
假设当n=11时，i=6,7,8,9,10,11时n/i都等于1；所以我们可以分成一块一块来做。
```cpp
for(ll i=1,j;i<=x;i=j+1){
		j=x/(x/i);
		ans=(ans%mod+1ll*(x/i)*(j-i+1)%mod)%mod;
}
```
数学基础不太哈，或不会整处分块的可以看[数论总结] (https://www.cnblogs.com/yexinqwq/p/10392167.html)




```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define mod 998244353
#define ll long long
ll l,r;
ll work(ll x){
	ll ans=0;
	for(ll i=1,j;i<=x;i=j+1){
		j=x/(x/i);
		ans=(ans%mod+1ll*(x/i)*(j-i+1)%mod)%mod;
	}
	return ans;
}
int main(){
	scanf("%lld%lld",&l,&r);
	printf("%lld\n",(work(r)%mod-work(l-1)%mod+mod)%mod);
	return 0;
}
```


---

## 作者：Wolfycz (赞：2)

首先显然有$\sum\limits_{i=l}^rf(i)=\sum\limits_{i=1}^rf(i)-\sum\limits_{i=1}^{l-1}f(i)$，于是问题转化为了如何求$\sum\limits_{i=1}^nf(i)$，即$\sum\limits_{i=1}^n\sum\limits_{d|i}1$，调整枚举顺序有$\sum\limits_{d=1}^n\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}1$，即$\sum\limits_{d=1}^n\lfloor\dfrac{n}{d}\rfloor$，由于$n$很大，所以我们使用整除分块即可

```cpp
/*program from Wolfycz*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
inline char gc(){
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int frd(){
	int x=0,f=1; char ch=gc();
	for (;ch<'0'||ch>'9';ch=gc())	if (ch=='-')	f=-1;
	for (;ch>='0'&&ch<='9';ch=gc())	x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
inline int read(){
	int x=0,f=1; char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar())	if (ch=='-')	f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar())	x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
inline void print(int x){
	if (x<0)	putchar('-'),x=-x;
	if (x>9)	print(x/10);
	putchar(x%10+'0');
}
const int p=998244353;
int solve(ll n){
	int res=0;
	for (ll i=1,pos;i<=n;i=pos+1){
		pos=n/(n/i); int len=(pos-i+1)%p;
		res=(res+1ll*len*(n/i)%p)%p;
	}
	return res;
}
int main(){
	ll l,r;
	scanf("%lld%lld",&l,&r);
	printf("%d\n",(solve(r)-solve(l-1)+p)%p);
	return 0;
}
```



---

