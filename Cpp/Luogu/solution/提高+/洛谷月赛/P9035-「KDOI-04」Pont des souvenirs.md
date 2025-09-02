# 「KDOI-04」Pont des souvenirs

## 题目背景

虽然这是一个 C，但是

![](https://cdn.luogu.com.cn/upload/image_hosting/dzj8va56.png)

## 题目描述

给定正整数 $n,k$，求有多少个长度为 $n$ 的正整数序列 $a$ 满足：

* $0<a_1\le a_2\le a_3\le\cdots\le a_n\le k$；
* $\forall\ i\not=j$，$a_i+a_j\le k+1$。

答案对 $10^9+7$ 取模。

## 说明/提示

**【样例解释】**

对于第 $1$ 组测试数据，所有满足要求的序列为 $(1,1)$ 和 $(1,2)$。

对于第 $2$ 组测试数据，所有满足要求的序列为 $(1)$，$(2)$ 和 $(3)$。

**【数据范围】**

对于 $100\%$ 的数据，保证 $1\le T\le2\times10^5$，$1\le n,k\le10^7$。

**本题开启捆绑测试。**

|子任务编号|分值|$T\le$|$n\le$|$k$|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$8$|$5$|$5$|$\le5$|
|$2$|$3$|$10^5$|$10^7$|$=1$|
|$3$|$3$|$10^5$|$10^7$|$=2$|
|$4$|$8$|$10^5$|$10^7$|$=3$|
|$5$|$16$|$10$|$200$|$\le200$|
|$6$|$16$|$10$|$3000$|$\le3000$|
|$7$|$8$|$10^4$|$10^7$|$\le5$|
|$8$|$8$|$100$|$10^7$|$\le10^5$|
|$9$|$30$|$2\times10^5$|$10^7$|$\le10^7$|


## 样例 #1

### 输入

```
5
2 2
1 3
4 5
4030 218
1145 1419
```

### 输出

```
2
3
20
571656908
172735629
```

# 题解

## 作者：Polaris_Australis_ (赞：15)

### 做法 1

暴力枚举，复杂度 $O(k^n)$。

### 做法 2

容易发现，$k=1$ 时答案为 $1$，$k=2$ 时答案为 $2$，$k=3$ 时答案为 $n+2$。

### 做法 3

设 $dp_{i,j}$ 表示到 $i$ 位置为止最大数为 $j$ 的方案数，$dp_{i,j}=\sum\limits_{l=1}^{j}dp_{i-1,l}$，复杂度 $O(n\times k^2)$，前缀和优化即可 $O(n\times k)$，最后一位上界为 $k$，其余位上界为 $\lfloor\frac{k+1}{2}\rfloor$。

### 做法 4

根据上边的 dp 式矩阵乘法，复杂度 $O(k^3\log_2n)$。

### 做法 5

设 $a_0=1$，对于 $1\le i\le n$，$b_i=a_i-a_{i-1}$。枚举 $a_n$ 的值，分为两种情况：

1. $a_n\le\lfloor\frac{k+1}{2}\rfloor$，则不需要考虑题目中第二条限制，所以只需要求满足 $(\sum\limits_{i=1}^{n}b_i)=a_n-1$ 的方案数即可，即可重组合数 $H_{n}^{a_n-1}=\binom{n+a_n-2}{a_n-1}$。
2. $a_n>\lfloor\frac{k+1}{2}\rfloor$，此时要考虑第二条限制，即 $a_{n-1}\le k+1-a_n$，容易发现，这一条件等价于最后一位为 $k+1-a_n$ 的方案数，于是转化为第一种情况。

即：

$$
ans=\sum\limits_{i=1}^{\lceil\frac{k}{2}\rceil}\binom{n+i-2}{i-1}+\sum\limits_{i=1}^{\lfloor\frac{k}{2}\rfloor}\binom{n+i-2}{i-1}
$$

复杂度 $O(k)$。

### 做法 6

首先有一个组合数求和结论：

$$\sum\limits_{i=l}^{r}\binom{i}{k}=\binom{r+1}{k+1}-\binom{l}{k+1}$$

证明的话直接移项，然后一直根据递推式合并即可。

之后利用这个结论去推式子：

$$
\begin{aligned}
ans&=
\sum\limits_{i=1}^{\lceil\frac{k}{2}\rceil}\binom{n+i-2}{i-1}+\sum\limits_{i=1}^{\lfloor\frac{k}{2}\rfloor}\binom{n+i-2}{i-1}\\
&=\sum\limits_{i=1}^{\lceil\frac{k}{2}\rceil}\binom{n+i-2}{n-1}+\sum\limits_{i=1}^{\lfloor\frac{k}{2}\rfloor}\binom{n+i-2}{n-1}\\
&=\binom{n+\lceil\frac{k}{2}\rceil-1}{n}+\binom{n+\lfloor\frac{k}{2}\rfloor-1}{n}
\end{aligned}
$$

总复杂度 $O(\max(n+\lceil\frac{k}{2}\rceil)+T)$。

---

## 作者：hcywoi (赞：8)

- SubTask $1\sim 7$
	- $0<a_1\le a_2<\cdots\le a_n\le k$ 方案数的求法。
   		- 考虑每个数选得个数（因为确定每个数选得个数后即可知原序列）。
      - 令 $x_i$ 表示 $i$ 在序列中出现的个数。
      - $\displaystyle\sum_{i=1}^{k}x_i=n(x_i\ge 0)$。
      - 再令 $y_i$ 为 $x_i+1$。
      - $\displaystyle\sum_{i=1}^{k}y_i=n+k(y_i\ge 1)$。
      - 这是隔板法的经典柿子。
      - 即有 $n+k$ 个小球，然后把它进行分组，每组内小球的个数即为 $y_i$。
      - 就等价于在 $n+k-1$ 个空隙中放入 $k-1$ 个隔板的方案数，$\dbinom{n+k-1}{k-1}$。  
   - 再考虑加上 $\forall i\neq j, a_i+a_j\le k+1$。
   		- 满足这个条件，即要满足 $a_{n-1}+a_n\le k+1$。
      - 我们暴力枚举 $a_n$。
      - 则 $0<a_1\le a_2\le\cdots\le a_{n-1}\le\min\{a_n, k+1-a_n\}$。
      - $\displaystyle\sum_{i=1}^{k}\dbinom{n-1+\min\{i, k+1-i\}-1}{\min\{i,k+1-i\}-1}$。
- Subtask $8$
	- 前置芝士
   	   - $\dbinom{n}{m}=\dbinom{n}{n-m}$；
      - $\displaystyle\sum_{i=0}^{m}\dbinom{i}{n}=\dbinom{m+1}{n+1}$。
   - 我们考虑 $\min\{i, k+1-i\}$ 的取值范围。
   		- 我们令 $q=k+1$。
      - 则变成了 $\min\{i, q-i\}$ 的取值范围。
      - 即 $1\sim \left\lceil\frac{q}{2}\right\rceil$ 和 $1\sim \left\lfloor\frac{q}{2}\right\rfloor$。
	- 柿子就变成了 $\displaystyle\sum_{i=1}^{\left\lfloor\frac{k+1}{2}\right\rfloor}\dbinom{n+i-2}{i-1}+\displaystyle\sum_{i=1}^{\left\lceil\frac{k+1}{2}\right\rceil}\dbinom{n+i-2}{i-1}$。
   - 我们枚举 $i-1$，柿子就变成了  $\displaystyle\sum_{i=0}^{\left\lfloor\frac{k+1}{2}\right\rfloor-1}\dbinom{n+i-1}{i}+\displaystyle\sum_{i=0}^{\left\lceil\frac{k+1}{2}\right\rceil-1}\dbinom{n+i-1}{i}$。
   - 根据 $\dbinom{n}{m}=\dbinom{n}{n-m}$，柿子就变成了 $\displaystyle\sum_{i=0}^{\left\lfloor\frac{k+1}{2}\right\rfloor-1}\dbinom{n+i-1}{n}+\displaystyle\sum_{i=0}^{\left\lceil\frac{k+1}{2}\right\rceil-1}\dbinom{n+i-1}{n}$。
   - 根据 $\displaystyle\sum_{i=0}^{m}\dbinom{i}{n}=\dbinom{m+1}{n+1}$，柿子就变成了 $\dbinom{n+\left\lfloor\frac{k+1}{2}\right\rfloor}{n}+\dbinom{n+\left\lceil\frac{k+1}{2}\right\rceil}{n}$。
   - **组合数要用 $\mathcal O(n)$ 的预处理求**，具体见[【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)。
   - 时间复杂度：$\mathcal O(n)$，瓶颈在预处理。

---

预处理代码：

```cpp
	fact[0] = inv[0] = 1;
	for (int i = 1; i < N; i ++ ) {
		fact[i] = fact[i - 1] * (LL)i % mod;
	}

	inv[N - 1] = qmi(fact[N - 1], mod - 2);
	for (int i = N - 2; i >= 1; i -- ) {
		inv[i] = inv[i + 1] * (i + 1ll) % mod;
	}
```

---

## 作者：kbtyyds (赞：6)

# P9035 题解

建议在[博客](https://www.luogu.com.cn/blog/453059/solution--p9035)里食用：

[题目链接](https://www.luogu.com.cn/problem/P9035)

---

## 题目描述

给定正整数 $n,k$，求有多少个长度为 $n$ 的正整数序列 $a$ 满足：

* $0<a_1\le a_2\le a_3\le\cdots\le a_n\le k$；
* $\forall\ i\not=j$，$a_i+a_j\le k+1$。

答案对 $10^9+7$ 取模。

---

## 前置知识

组合数，推式子。

----

## 简要分析

我们看第二个约束，再结合第一个大小关系的约束，不难得到数列只需满足约束一以及满足 $a_{n-1}+a_n\le k+1$ 即可。

可以考虑枚举 $a_{n-1}$ ，分别计算出 $\{a_1,a_2,\cdots,a_{n-2}\}$ 这一段的数量以及 $a_n$ 的数量，最后乘一下再加起来即可。

同时也要注意 $a_{n-1}$ 的范围。由 $0<a_{n-1}\le a_n\le k$ 及 $a_{n-1}+a_n\le k+1$ 易得 $0<a_{n-1}\le\lfloor\frac k 2\rfloor$。

接着是 $a_n$ 的数量。当 $a_{n-1}=i$ 时，可得 $a_n\in[i,k+1-i]$，所以它的数量为 $(k-2i+2)$。

只需再考虑前半段即可。

---

## 深度思考

对于 $\{a_1,a_2,\cdots,a_{n-2}\}$ 的数量，我们拎出来化作这样一个问题：

> 给定 $n,m$，求长度为 $n$ 的整数序列 $\{a\}$ 的数量，使得 $0<a_1\le a_2\le\cdots\le a_{n-1}\le a_n\le m$。

对于这个问题，考虑 dp。记 $f[i][j]$ 为 $0\le a_1\le a_2\le\cdots\le a_{i-1}\le a_i=j$ 的方案数，容易得到转移方程：

$$f[i][j]=\sum_{k=1}^j f[i-1][k]$$

其中，边界条件为 $f[i][1]=1,f[1][j]=1$。

答案为 $\sum\limits_{j=1}^m f[n][j]=f[n+1][m]$。

再对方程进行研究：

$$\begin{aligned}f[i][j]=&\sum_{k=1}^j f[i-1][k]\\=&\left(\sum_{k=1}^{j-1}f[i-1][k]\right)+f[i-1][j]\\=&f[i][j-1]+f[i-1][j]\end{aligned}$$

得到了它的直接递推式，现在我们考虑它的通项公式。

可以证明，它的通项公式为 $f[i][j]={\rm C}_{i+j-2}^{i-1}$。可以用数学归纳法[证明](https://www.luogu.com.cn/paste/3yn5oana)。

于是我们得出结论：若记答案为 $\rm ans$，那么：

$${\rm ans}=\sum_{i=1}^{\lfloor\frac{k+1}2\rfloor}(k-2i+2)f[n-1][i]=\sum_{i=1}^{\lfloor\frac{k+1}2\rfloor}(k-2i+2){\rm C}_{n+i-3}^{n-2}$$

若组合数的求解为 $\mathcal O(1)$，那么该算法单次复杂度为 $\mathcal O(k)$，可以有 $\rm 70pts$。

---

## 推式子

我们给出两个将要用到的恒等式：

$$\boxed{\sum_{k=0}^n{\rm C}_{k}^m={\rm C}_{n+1}^{m+1}}$$

$$\boxed{n{\rm C}_ {n-1}^{m-1}=m{\rm C}_n^m}$$

证明过程在文末参考资料。

~~为了让文章详略得当，~~ 直接给出推式子的简单过程以及结果，详细讲解见[云剪切板](https://www.luogu.com.cn/paste/wf19ccqa)。

$$\begin{aligned} {\rm ans}=&\sum_{i=1}^{\lfloor\frac{k+1}2\rfloor}(k-2i+2){\rm C}_{n+i-3}^{n-2}\\=&\sum_{i=0}^{\lfloor\frac{k+1}2\rfloor-1}(k-2i){\rm C}_{n+i-2}^{n-2}\\=&\sum_{i=0}^{\lfloor\frac{k+1}2\rfloor-1}\Big[(k+2n-2){\rm C}_{n+i-2}^{n-2}-2(n+i-1){\rm C}_{n+i-2}^{n-2}\Big]\\=&\left[(k+2n-2)\sum_{i=0}^{\lfloor\frac{k+1}2\rfloor-1}{\rm C}_{n-2+i}^i\right]-2\sum_{i=0}^{\lfloor\frac{k+1}2\rfloor-1}(n+i-1){\rm C}_{(n+i-1)-1}^{(n-1)-1}\\=&(k+2n-2){\rm C}_{n+\lfloor\frac{k+1}2\rfloor-2}^{\lfloor\frac{k+1}2\rfloor-1}-2\sum_{i=0}^{\lfloor\frac{k+1}2\rfloor-1}(n-1){\rm C}_{n+i-1}^{n-1}\\=&(k+2n-2){\rm C}_{n+\lfloor\frac{k+1}2\rfloor-2}^{n-1}-2(n-1)\sum_{i=0}^{\lfloor\frac{k+1}2\rfloor-1}{\rm C}_{n-1+i}^i\\=&(k+2n-2){\rm C}_{n+\lfloor\frac{k+1}2\rfloor-2}^{n-1}-2(n-1){\rm C}_{n+\lfloor\frac{k+1}2\rfloor-1}^n\end{aligned}$$

得到了这个式子后，我们就能单次 $\mathcal O(1)$ 求解啦。

当然，不要忘了 $\mathcal O(1)$ 组合数的实现需要线性处理出阶乘及其逆元。

总时间复杂度 $\mathcal O(\max\{n+\lfloor\frac {k+1} 2\rfloor\}+\log p+T)$，空间复杂度 $\mathcal O(\max\{n+\lfloor\frac {k+1} 2\rfloor\})$，可以通过本题。

注意：当 $n=1$ 时要特判一下，答案显然为 $k$ 而不是长长的式子。

---

### 代码

[戳我](https://www.luogu.com.cn/paste/e2v5oq4g)qwq。

---

### 参考资料

[洛谷日报\#401](https://www.luogu.com.cn/blog/i-am-zhiyangfan/er-xiang-shi-ji-shuo)。

### 特别鸣谢

感谢在[求助帖](https://www.luogu.com.cn/discuss/568753)中帮忙的大佬们！！！

---

---

## 作者：ydzr00000 (赞：4)

题面很简洁，这里不做多说。

## 70pts 做法

首先考虑到 $a_{n-1}$ 和 $a_n$ 两项是整个数列 $a$ 中的最大的两项，所以若 $a_{n-1}+a_n$ 不超过 $k+1$，则数列中任意两项之和肯定不超过 $k+1$。

考虑当 $a_{n-1}=x$ 时，首先可以计算出 $a_n$ 的取值范围：

- 因为 $a_{n-1}\leq a_n$，故 $a_n\geq x$。

- 因为 $a_{n-1}+a_n\leq k+1$，则 $a_n\leq k+1-x$。

所以 $x\leq a_n\leq k+1-x$，取值数量为 $k+2-2x$，当 $x > k+1-x$ 时取值数量为 $0$。

考虑第一个约束，因为：

$$1\leq a_1\leq a_2\leq ...\leq a_{n-2}\leq a_{n-1}$$

将不等式的每一个部分加上下标，为了方便，下式的表达式所加的下标从 $0$ 开始：

$$1\leq a_1+0 < a_2+1< ...< a_{n-2}+n-3 < x+n-2$$

所以 $a_{n-2}+n-3\leq x+n-3$。

具体证明本蒟蒻不太会，建议查询相关资料。

于是我们可以得到 $a$ 数列的前 $n-2$ 项就是在 $[1,x+n-3]$ 范围中选择 $n-2$ 个数，方案数为 ${x+n-3\choose n-2}$。

于是对于 $a_{n-1}=x$，方案数为 ${x+n-3\choose n-2}\times \max(k+2-2x,0)$。

累加所有的可能，答案为：

$$ \overset{k+1}{\underset{i=1}{\sum}} {i+n-3\choose n-2}\times \max(k+2-2i,0) $$

## 100pts 做法

我们只需要化简如上求和式子即可，本蒟蒻不会等号对齐，故观感可能较差。

首先 $\max(k+2-2i,0)$ 很难化简，于是我们需要求出 $i$ 的上界，解不等式可得 $\lfloor { \frac{k+1}{2} } \rfloor$，为了之后化简的方便，以下用 $m+1$ 代替该数字。

$$ \overset{k+1}{\underset{i=1}{\sum}} {i+n-3\choose n-2}\times \max(k+2-2i,0) $$

化为：

$$\overset{m+1}{\underset{i=1}{\sum}}{i+n-3\choose n-2}\times (k-2i)$$

运用乘法分配律得：

$$k\times \overset{m}{\underset{i=0}{\sum}} {i+n-2\choose n-2} - 2\times \overset{m}{\underset{i=0}{\sum}} {i+n-2\choose n-2}\times i$$

由组合数公式，得：

$$k\times {m+n-1\choose n-1} - 2\times \overset{m}{\underset{i=0}{\sum}} {i+n-2\choose n-2}\times i$$

由于 $\times 0$ 无意义，故省去，得：

$$k\times {m+n-1\choose n-1} - 2\times \overset{m}{\underset{i=1}{\sum}} {i+n-2\choose n-2}\times i$$

变换形式，得：

$$k\times {m+n-1\choose n-1} - 2\times \overset{m}{\underset{i=1}{\sum}} \overset{i}{\underset{j=1}{\sum}}  {i+n-2\choose n-2}$$

调换求和顺序，得：

$$k\times {m+n-1\choose n-1} - 2\times \overset{m}{\underset{j=1}{\sum}} \overset{m}{\underset{i=j}{\sum}}  {i+n-2\choose n-2}$$

将第二个求和换成两式相减，得：

$$k\times {m+n-1\choose n-1} - 2\times \overset{m}{\underset{j=1}{\sum}} (\overset{m}{\underset{i=0}{\sum}} {i+n-2\choose n-2} - \overset{j-1}{\underset{i=0}{\sum}} {i+n-2\choose n-2})$$

运用组合数公式，得：

$$k\times {m+n-1\choose n-1} - 2\times \overset{m}{\underset{j=1}{\sum}} ({m+n-1\choose n-1} - {j-1+n-1\choose n-1})$$

拆除一个括号，方便化简，得：

$$k\times {m+n-1\choose n-1} - 2\times \overset{m}{\underset{j=1}{\sum}} {m+n-1\choose n-1} + 2\times \overset{m}{\underset{j=1}{\sum}} {j-1+n-1\choose n-1}$$

化简第一个求和，得：

$$k\times {m+n-1\choose n-1} - 2m\times  {m+n-1\choose n-1} + 2\times \overset{m}{\underset{j=1}{\sum}} {j-1+n-1\choose n-1}$$


降低求和范围，得：

$$(k-2m)\times  {m+n-1\choose n-1} + 2\times \overset{m-1}{\underset{j=0}{\sum}} {j+n-1\choose n-1}$$

运用组合数公式，得：

$$(k-2m)\times  {m+n-1\choose n-1} + 2\times {m+n-1\choose n}$$

至此，我们就化简完毕，可以预处理阶乘及其逆元，求组合数时 $\mathcal{O}(1)$ 求解，记得取余。



---

## 作者：Y_ATM_K (赞：3)

[题面](https://www.luogu.com.cn/problem/P9035)

## 分析

对于第二个限制，可以转化为两个限制：

1. $a_{n-1} \le \big\lceil \frac{k}{2} \big\rceil $

2. $ a_{n-1} \le a_n \le k+1-a_{n-1} $

因为 $ 2 \big\lceil \frac{k}{2} \big\rceil + 1> k + 1$，所以前 $n-1$ 个数都要小于等于 $\big\lceil \frac{k}{2} \big\rceil$。

又因为 $ 2\big\lceil \frac{k}{2} \big\rceil \le k + 1 $，所以只需要 $a$ 单调不减且 $a_{n-1} \le \big\lceil \frac{k}{2} \big\rceil$，就是合法的前 $n-1$ 个数。

考虑如何计算前 $n-1$ 个的合法方案数。

把 $a_i$ 转化为 $(i,a_i)$ 这样的点，我们要求的实际上是从 $(1,1)$ 走到 $ (n,\big\lceil \frac{k}{2} \big\rceil) $，一次只能往上或右走一格的方案数。

这个问题的答案可以用组合数表示为 $\dbinom{n - 1 + \lceil \frac{k}{2} \rceil - 1}{n-1}$.

显然对于 $i \in [1,\lceil \frac{k}{2} \rceil]$ 从 $(1,1)$ 走到 $(n-1,i)$ 的方案数之和等于走到 $(n,\big\lceil \frac{k}{2} \big\rceil) $ 的方案数。就得到了
$$\forall x>0,y \ge 0, \sum_{i=1}^{x}{\binom{y+x-1}{y}} = \binom{y+x}{y+1}$$

然后考虑加上第 $n$ 个数怎么做。

因为 $a_{n-1} \le k + 1 -a_{n-1}$，所以 $a_n$ 的取值方案数为 $k - 2 a_{n-1} + 2$，也就是对于每个 $(n-1,i)$ 有 $k - 2 i + 2$ 种走法走到终点。

那么原问题答案为
$$\begin{aligned}
& \sum_{i=1}^{\lceil \frac{k}{2} \rceil}{\binom{n-3+i}{n-2}} \cdot (k - 2i + 2) \\
= & (k+2) \cdot \sum_{i=1}^{\lceil \frac{k}{2} \rceil}{\binom{n-3+i}{n-2}} - 2\sum_{i=1}^{\lceil \frac{k}{2} \rceil}{\binom{n-3+i}{n-2} \cdot i} \\
= & (k+2) \cdot \binom{n-2+\lceil \frac{k}{2} \rceil}{n-1} - 2\sum_{i=1}^{\lceil \frac{k}{2} \rceil}{\binom{n-3+i}{n-2} \cdot i}
\end{aligned}$$

把 $i$ 乘上组合数的项进行转化
$$\begin{aligned}
& -\sum_{i=1}^{\lceil \frac{k}{2} \rceil}{\binom{n-3+i}{n-2} \cdot i} \\
= & \sum_{i=1}^{\lceil \frac{k}{2} \rceil}{\binom{n-3+i}{n-2} \cdot \big(\big\lceil \frac{k}{2} \big\rceil - i + 1 \big)} - \sum_{i=1}^{\lceil \frac{k}{2} \rceil}{\binom{n-3+i}{n-2} \cdot \big( \big\lceil \frac{k}{2} \big\rceil + 1 \big)}\\
= & \sum_{i=1}^{\lceil \frac{k}{2} \rceil}{\binom{n-2+i}{n-1}} - \big( \big\lceil \frac{k}{2} \big\rceil + 1 \big) \cdot \binom{n - 2 + \lceil \frac{k}{2} \rceil}{n-1}\\
= & \binom{n-1+\lceil \frac{k}{2} \rceil}{n} - \big( \big\lceil \frac{k}{2} \big\rceil + 1 \big) \cdot \binom{n - 2 + \lceil \frac{k}{2} \rceil}{n-1}\\
\end{aligned}$$

最终结果是
$$ 2\binom{n + \lceil \frac{k}{2} \rceil - 1}{n} + \big(k - 2\big\lceil \frac{k}{2} \big\rceil \big) \cdot \binom{n + \lceil \frac{k}{2} \rceil - 1}{n-1}$$

$O(n)$ 预处理阶乘和阶乘的逆元就可以 $O(1)$ 查询。

## 代码
```cpp
#include <bits/stdc++.h>
#define N 15000000
using namespace std;
const int mod=1e9+7;
int power(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1) ans=1ll*ans*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ans;
}
int T,n,K,jie[N+10],inv[N+10];
long long C(int n,int m) {
	return 1ll*jie[n]*inv[m]%mod*inv[n-m]%mod;
}
int main() {
	jie[0]=inv[0]=1;
	for(int i=1;i<=N;++i) jie[i]=1ll*jie[i-1]*i%mod;
	inv[N]=power(jie[N],mod-2);
	for(int i=N-1;i;--i) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&K);int k=(K+1)/2;
		printf("%lld\n",(2*C(n+k-1,n)+C(n-2+k,n-1)*(K-2*k)%mod+mod)%mod);
	}
	return 0;
}
```

---

## 作者：Demeanor_Roy (赞：2)

- [原题链接](https://www.luogu.com.cn/problem/P9035)


------------

依稀记得这场通过翻**具体数学**找式子的方法场切了 T3。时隔半年却发现当时的难题已变得套路而简单。

显然第二个条件很诈骗，结合第一个条件其实就是 $a_{n-1}+a_n \leq k+1$。这启发我们第二个条件对 $a$ 序列限制很小。

不妨考虑暴力 dp，$f_{i,j}$ 表示 $a_i=j$ 的方案数，转移就是前缀和刷一遍。显然这种形式的转移可以通过组合数快速表示 dp 值，即 $f_{i,j}={{i+j-2}\choose{i-1}}$。

枚举 $a_{n-1}$，可得答案为：

$$Ans=\sum_{2x \leq k+1}f_{n-1,x}(k-2x)$$

通过简单化简后，上述式子一部分可通过**上指标求和**转化为组合式，一部分配凑一下系数，用**吸收恒等式**同理转化。

于是预处理组合数，每组询问 $O(1)$ 回答即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=1.5e7+10,mod=1e9+7;
int T,n,k,m,fct[N],inv[N],finv[N];
inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}
inline void init()
{
	fct[0]=inv[0]=finv[0]=fct[1]=inv[1]=finv[1]=1;
	for(int i=2;i<N;i++)
	{
		fct[i]=(LL)fct[i-1]*i%mod;
		inv[i]=(mod-(LL)mod/i*inv[mod%i]%mod)%mod;
		finv[i]=(LL)finv[i-1]*inv[i]%mod;
	}
}
inline int C(int x,int y)
{
	return x<y?0:(LL)fct[x]*finv[y]%mod*finv[x-y]%mod;
}
inline void solve()
{
	n=read(),k=read(),m=(k+1)>>1;
	if(n==1) return printf("%d\n",k),void();
	printf("%d\n",(C(n+m-1,n)*2%mod-C(n+m-2,n-1)*(k&1)+mod)%mod);
}
int main()
{  
	init();
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：1)

前言：这个shaber赛时草稿纸上赫然写着 $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}$ 然后觉得很熟悉却不会做。

### Subtask 1

随便暴力随便过，就不讲了。

期望得分 $8$。

### Subtask 2

$k=1$ 的时候容易发现只能是 $1,1,1,\dots,1$，就一种情况，答案为 $1$。

期望得分 $3$。

### Subtask 3

$k=2$ 的时候由于要求任意两个数和 $\leq 3$，所以容易发现不能有超过一个 $2$。因此要么是 $1,1,\dots,1$，要么是 $1,1,\dots,1,2$，一共两种情况。

期望得分 $3$。

### Subtask 4

$k=3$ 的时候要求任意两个数和 $\leq 4$，所以不能有超过一个 $3$ 并且有 $3$ 的时候不能有 $2$。

所以一定是 $1,1,\dots,1,2,2,\dots,2$ 或者 $1,1,\dots,1,3$ 这两种形式。

容易发现第一种可以枚举 $1$ 和 $2$ 的分界点，共 $n+1$ 种可能，第二种 $1$ 种可能，所以答案是 $n+2$。

期望得分 $8$。

### Subtask 5

考虑一个朴素的 dp：$dp_{i,j}$ 表示前 $i$ 个数，第 $i$ 个大小为 $j$，此时的方案数。显然有：

$$dp_{i,j}=\sum\limits_{p=1}^{\min\{j,k-j+1\}}dp_{i-1,p}$$

答案就是 $\sum_{p=1}^{k}dp_{n,p}$。

复杂度 $O(Tnk^2)$，期望 $24$ 分。

### Subtask 6&7

容易发现我们可以维护一个 $S_{i,j}=\sum_{p=1}^{j} dp_{i,j}$。于是转移变成了：

$$\begin{cases}dp_{i,j}=S_{i-1,\min\{j,k-j+1\}}\\S_{i,j}=S_{i,j-1}+dp_{i,j}\end{cases}$$

复杂度降为 $O(Tnk)$，期望还是 $24$ 分/hanx。

上面那个显然可以滚动数组，空间变成 $O(k)$。

注意到每次算一遍 dp 值太麻烦了，因此我们考虑离线下来扫一遍解决问题。

观察到我们是对 $k$ 个位置进行了 $n$ 次 dp，所以我们按照 $n$ 排序，每次 dp 到 $\max k$，然后双指针处理答案。

容易发现排序复杂度是 $O(T\log T)$ 的，dp 复杂度是 $O(\max n \cdot \max k)$ 的，所以总复杂度 $O(T \log T+\max n \cdot \max k)$，期望 $62$ 分。

### Subtask 8&9

打一个表出来发现那个 dp 其实是一个对称的 $k$ 阶等差数列。因此有转移：

$$dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}$$

我们~~艰难的~~发现这不就是个组合数嘛！$dp_{i,j}=\binom{i+j-1}{j-1}$。（没写反吧，我不太熟用这个。）

所以每次的答案可以表示为 $dp_{n,\lceil k/2\rceil}+dp_{n,\lfloor k/2\rfloor}$，也就可以轻松用组合数求出来了。

求组合数不会有人不会 $O(n)-O(1)$ 做法吧，具体就是求一个阶乘 $fr$ 数组，费马求出 $n!$ 逆元，然后倒着求其他数的逆元 $inv_i$，最后求一个逆元阶乘 $rf$。于是有：

$$\dbinom{n}{m}=\dfrac{n!}{m!(n-m)!}=\dfrac{fr_n}{rf_m \cdot rf_{n-m}}$$

显然单次可以 $O(1)$ 查询。

因此本题解决，复杂度为 $O(n+k+T)$。

好题。

---

## 作者：李34 (赞：1)

[P9035 「KDOI-04」Pont des souvenirs](https://www.luogu.com.cn/problem/P9035)

### 题意

给定正整数 $n,k$，求有多少个长度为 $n$ 的正整数序列 $a$ 满足：

* $0<a_1\le a_2\le a_3\le\cdots\le a_n\le k$；
* $\forall\ i\not=j$，$a_i+a_j\le k+1$。

### 题解

首先发现第二个条件实际上不是很强，因为 $\{a\}$ 是单调不降的，所以只需满足 $a_{n-1} + a_{n} \leq k$ 就好了。

而第一个条件很像一个组合数能算的东西。那么我们不妨定义 $f(x,y)$ 表示满足 $0<a_1\le a_2\le a_3\le\cdots\le a_x\le y$ 的数列个数。由于第二个条件只作用于最后两个数，我们不妨枚举 $a_n$。当 $a_n=x$ 时，有 $a_{n-1}\leq k+1-x$ 和 $a_{n-1}\leq x$ 同时成立，那么答案为：

$$\sum_{x=1}^{k} f(n-1,\min\{x,k-x+1\})$$

观察式子发现，函数的第二维是先递增再递减的。我们不妨把它拆开。当 $k$ 为奇数时：

$$\sum_{x=1}^{\frac{k+1}{2}} f(n-1,x)\ \ \ +\sum_{x=1}^{\frac{k-1}{2}} f(n-1,x)$$

当 $k$ 为偶数时：

$$2\cdot\sum_{x=1}^{\frac{k}{2}} f(n-1,x)$$

接下来考虑如何求得 $f(x,y)$。

首先有一个非常明显的递推式：我们依然枚举最后一位，那么前面 $x-1$ 位是随便选的，就得出了：

$$f(x,y) = \sum_{i=1}^{y} f(x-1,i)$$

这个式子看起来一点用都没有，但实际上它可以优化之前我们得出的答案式子。答案就变为了，$k$ 为奇数时：

$$f(n,\frac{k+1}{2})+f(n,\frac{k-1}{2})$$

$k$ 为偶数时：

$$2\cdot f(n, \frac{k}{2})$$

这下看起来简洁多了。由于第一个条件十分简洁，我们不妨考虑用组合数直接求出 $f(x,y)$。

由于数列是单调不下降的，前面的数的选择会影响到后面的数的选择。这很不方便。于是我们采取一个常见的套路：把问题转化为一开始有 $x$ 个 $1$，有 $y-1$ 次 $+1$ 的机会（原先已经有 $1$ 了），每次可以选择一个数，让这个数和后面所有数都 $+1$。然而特殊地，我们可以不用完所有机会，于是把浪费掉的 $+1$ 机会定义为给 $x+1$ 个数 $+1$。（同样的，我们也可以借助差分的思想，把原数列差分后转化为给 $y-1$ 个差分数组里的数 $+1$。）

无论如何，现在我们将问题转化为了插板法的模型：把 $+1$ 看作板，数看作球，那么就转化为了在 $x+1$ 个空隙中插入 $y-1$ 块板，可以在同一空隙插入多块板。那么我们不妨再增加 $y-2$ 个空隙，那么就成了 $x+y-1$ 个空隙插入 $y-1$ 块板，答案是 $C_{x+y-1}^{y-1}$。（如果你交换板和球，也将得到同样的答案）

或者说更加直观一点，我们把 $+1$ 也看成是数，那么就是合并一个有 $x$ 个元素的数组和有 $y-1$ 个元素的数组，每个数组中的元素相同（$1$ 和 $+1$），两个数组之间的元素不相同。很显然，最后得到的数组有 $x+y-1$ 个元素，其中要选 $x$ 个 $1$（或者选 $y-1$ 个 $+1$ ），答案是 $C_{x+y-1}^{y-1}$。

我们也可以通过变形 $f(x,y)$ 的递推式，得出 $f(x,y) = f(x-1,y) + f(x,y-1)$，和组合数的递推式进行对比得出通式。

多种方法殊途同归，最后我们得出 $f(x,y) = C_{x+y-1}^{y-1}$。可以 $O(n)$ 预处理 $O(1)$ 回答。

参考代码

```cpp
#include<bits/stdc++.h>
#define gc getchar
#define pc putchar
#define F(i,x,y) for(int i=x;i<=y;++i)
#define R(i,x,y) for(int i=x;i>=y;--i)
typedef long long LL;
inline int read(){
	int x=0;char ch=gc();bool p=1;
	while (!isdigit(ch)) ch=='-'?p=0:0,ch=gc();
	while ( isdigit(ch)) x=(x<<1)+(x<<3)+(ch^'0'),ch=gc();
	return p?x:-x;
}
const int N=2e7,MOD=1e9+7;
int n,k,jc[N+1],nc[N+1];
inline int fpow(int a,int b){
	int s=1;
	while (b){
		if (b&1) s=(LL)s*a%MOD;
		a=(LL)a*a%MOD,b>>=1;
	}
	return s;
}
inline void INIT(){
	jc[0]=1;
	F(i,1,N) jc[i]=(LL)jc[i-1]*i%MOD;
	nc[N]=fpow(jc[N],MOD-2);
	R(i,N,1) nc[i-1]=(LL)nc[i]*i%MOD;
}
inline int C(int x,int y){
	return (LL)jc[x]*nc[y]%MOD*nc[x-y]%MOD;
}
inline int f(int x,int y){
	return C(x+y-1,y-1);
}
signed main(){
	int T=read();
	INIT();
	while (T--){
		n=read(),k=read();
		if (k&1){
			int p=(k+1)/2;
			printf("%d\n",(f(n,p)+f(n,p-1))%MOD);
		}else{
			int p=(k+1)/2;
			printf("%d\n",(f(n,p)+f(n,p))%MOD);
		}
	}
	return 0;
}
```

---

## 作者：Gapple (赞：0)

设 $S = a_{n - 1} + a_n$，则根据题意有 $S \le k + 1$。又因为 $a_{n - 1} \le a_n$，所以 $a_{n - 1} \le \lfloor S / 2 \rfloor$。

我们枚举 $S, a_{n - 1}$，则每一种前 $n - 2$ 项的方案都对应一种直角坐标系上 $(0, 1) \to (n - 2, a_{n - 1})$ 的路径。这样的路径共有 $\dbinom{n + a_{n - 1} - 3}{n - 2}$ 种。

则答案为：

$$
\begin{aligned}
    \sum \limits_{S = 2}^{k + 1} \sum \limits_{a_{n - 1} = 1}^{\left \lfloor S / 2 \right \rfloor} \dbinom{n - 3 + a_{n - 1}}{n - 2}
    &= \sum \limits_{S = 2}^{k + 1} \dbinom{n - 2 + \lfloor S / 2 \rfloor}{n - 1} \\
    &= \sum \limits_{i = 1}^{\lceil k / 2 \rceil} \dbinom{n - 2 + i}{n - 1} + \sum \limits_{i = 1}^{\lfloor k / 2 \rfloor} \dbinom{n - 2 + i}{n - 1} \\
    &= \dbinom{n - 1 + \lceil k / 2 \rceil}{n} + \dbinom{n - 1 + \lfloor k / 2 \rfloor}{n}
\end{aligned}
$$

时间复杂度：$O(1)$ 计算答案，$O(n + k)$ 预处理。

空间复杂度：$O(n + k)$ 存逆元。

```cpp
#include <iostream>

using namespace std;
using i64 = long long;

constexpr int MOD = 1e9 + 7, V = 2e7;

int fact[V + 1], ifact[V + 1], inv[V + 1];

inline int add(int a, int b) { return (a + b) % MOD; }
inline int mul(int a, int b) { return i64(a) * b % MOD; }
inline int comb(int n, int k) { return mul(fact[n], mul(ifact[k], ifact[n - k])); }

void init()
{
    inv[1] = fact[1] = ifact[1] = fact[0] = ifact[0] = 1;

    for (int i = 2; i <= V; ++i) {
        inv[i] = mul(MOD - MOD / i, inv[MOD % i]);
        fact[i] = mul(fact[i - 1], i);
        ifact[i] = mul(ifact[i - 1], inv[i]);
    }
}

void solve_test()
{
    int n, k;
    cin >> n >> k;
    cout << add(comb(n - 1 + ((k + 1) >> 1), n), comb(n - 1 + (k >> 1), n)) << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;

    init();

    while (t-- > 0)
        solve_test();

    return 0;
}
```

---

## 作者：AK_400 (赞：0)

### 70pts做法

枚举最后一个填什么，变为 $[1,mx]$ 之间有多少个长度为 $n-1$ 的不降数列，其中 $mx$ 表示 $a_{n-1}$ 可以取到的最大值，即 $\min(a_n,k+1-a_n)$。

注意到这个问题可以转化成一个单位正方形构成的矩形，问如果只能向右和向上移动，从左下角到右上角有几种走法。

具体地，假设我们在 $(x,y)$ 向右走了一步到 $(x+1,y)$，表示在第 $x$ 个数填 $y$。

根据上述定义，我们要求的就是一个 $n$ 列，$mx$ 行的矩形的答案。考虑总共走 $n+mx-2$ 步，其中 $n-1$ 步往右，也就是 $C_{n+mx-2}^{n-1}$。

于是答案为
$$\sum_{i=1}^k C_{n+\min(i,k+1-i)-2}^{n-1}$$

### 100pts做法

注意到

$$\min(i,k+1-i)=\begin{cases}
  i & i\le\lfloor\frac{k+1}{2}\rfloor \\
  k+1-i & i>\lfloor\frac{k+1}{2}\rfloor
\end{cases}$$

变为

$$\sum_{i=1}^{\lfloor\frac{k+1}{2}\rfloor} C_{n+i-2}^{n-1}+\sum_{i=\lfloor\frac{k+1}{2}\rfloor+1}^{k} C_{n+k+1-i-2}^{n-1}$$

即

$$\sum_{i=n-1}^{n+\lfloor\frac{k+1}{2}\rfloor-2} C_{i}^{n-1}+\sum_{i=n-1}^{n+k-\lfloor\frac{k+1}{2}\rfloor-2} C_{i}^{n-1}$$

考虑朱世杰恒等式，即

$$\sum_{i=m}^nC_i^a=C_{n+1}^{a+1}-C_m^{a+1}$$

那么上式可以 $O(1)$ 求。

复杂度：预处理阶乘 $O(n)$，单次查询复杂度 $O(1)$。总复杂度 $O(n+T)$。

code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void read(int &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read(a),read(b),read(c)
#define read4(a,b,c,d) read(a),read(b),read(c),read(d)
#define read5(a,b,c,d,e) read(a),read(b),read(c),read(d),read(e)
#define read6(a,b,c,d,e,f) read(a),read(b),read(c),read(d),read(e),read(f)
const int mod=1e9+7;
int fact[30000005];
int inv[30000005];
int qp(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
void init(){
    fact[0]=1;
    for(int i=1;i<=15000000;i++)fact[i]=fact[i-1]*i%mod;
    inv[15000000]=qp(fact[15000000],mod-2);
    for(int i=14999999;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int k){
    return fact[n]*inv[k]%mod*inv[n-k]%mod;
}
int qu(int m,int n,int a){
    return (C(n+1,a+1)-C(m,a+1)+mod)%mod;
}
void slv(){
    int n,k;
    read2(n,k);
    cout<<(qu(n-1,n+(k+1)/2-2,n-1)+qu(n-1,n+k-(k+1)/2-2,n-1))%mod<<endl;
}
signed main(){
    init();
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：A2_Zenith (赞：0)

注意到 $\forall i \ne j,a_i+a_j \leq k+1 \Longleftrightarrow a_{n-1} + a_n \le k+1$。

考虑枚举 $0 \leq a_{n-1}+a_n=S \leq k+1$，$x = a_{n-1} \leq a_n = S-x$。

答案是 

$$
\begin{aligned}
&\sum\limits_{S=0}^{k+1}\sum\limits_{x=0}^{\lfloor\frac{S}{2}\rfloor}\dbinom{x+(n-2)-1}{n-2}\\
=& \sum\limits_{S=0}^{k+1}\dbinom{\lfloor\frac{S}{2}\rfloor+n-2}{n-1}\\
=& \sum\limits_{i=0}^{\lfloor\frac{k+1}{2}\rfloor}\dbinom{i+n-2}{n-1} +  \sum\limits_{i=0}^{\lfloor\frac{k}{2}\rfloor}\dbinom{i+n-2}{n-1}\\
=& \dbinom{n+\lceil\frac{k}{2}\rceil-1}{n} +  \dbinom{n+\lfloor\frac{k}{2}\rfloor-1}{n}\\
\end{aligned}
$$

其中的第二行变到第三行的原因是：考虑 $f(x) = \lfloor\frac{x}{2}\rfloor$ 在 $x=0,1 \cdots k+1$ 的取值，一定形如 $0,0,1,1 \cdots \lfloor\frac{k+1}{2}\rfloor$。你显然可以分成两组：$0,1,2 \cdots \lfloor\frac{k}{2}\rfloor$ 与 $0,1,2 \cdots \lfloor\frac{k+1}{2}\rfloor$。更严谨的证明的话，可以对 $k$ 的奇偶性讨论。

然后就是上指标求和的恒等式，这个是为我们所熟知的。

那这题就做完了，复杂度 $\mathcal{O(k+n) - O(1)}$。

这个不用贴代码吧（？

---

