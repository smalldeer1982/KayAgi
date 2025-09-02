# [Celeste-B] Say Goodbye

## 题目背景

> 你们居然挺过来了，真是令人难以置信，不是吗？

> 努力的过程还是挺有意思的。

> 这个嘛，

> 你又在等什么？

## 题目描述

Madeline 将收集到的草莓分给了朋友们

火红色的草莓和金黄色的草莓交错在一起，很受朋友们喜爱

朋友们为了感谢 Madeline ，一起收集了许多五颜六色的珠子，打算串成一条花花绿绿的项链送给 Madeline

经过朋友们的精心准备，现在桌子上摆着$n$个珠子，这些珠子一共有$k$种颜色。具体来说，第$i$种颜色的珠子有$a_i$个

看着桌子上晶莹剔透的珠子，现在朋友们却犯难了，因为他们不知道怎样将它们串在一起才最美丽

朋友们向你发出了请求，需要你帮忙求出本质不同的方案总数

朋友们分不清这些珠子的顺序，因此**两个珠子不同仅当它们的颜色不同**

这条项链必须是完整的，因此**所有珠子构成了一个连通块**

这条项链还不能太杂乱，因此所有珠子必须构成一棵**基环树**

在多次询问 Madeline 的朋友们之后，你发现这棵基环树的两个子树不同仅当**它们对应点的颜色不同或者这两棵子树不同构**。对于不同的子树是有先后顺序之分的

举例来说，下面的几种**部分**串法是互不相同的

![1566976736844.png](https://cdn.luogu.com.cn/upload/image_hosting/diwl819r.png)

朋友们的时间很紧迫，因此如果两种项链能够通过**旋转基环**得到同样的结果，那么这两种项链本质上是相同的



## 说明/提示

基环树：一个有$n$个点$n$条边的联通图，**没有自环**。容易看出这样的图是一个环上连出了一些树

基环：基环树中的环

对于 $ 5\% $ 的数据，$ n \leq 8 $

对于另 $ 10\% $ 的数据，$ k = 1 , n \leq 10^3 $

对于前 $ 30\% $ 的数据，$ n \leq 10^3 $

对于另 $ 20\% $ 的数据，$ k = 1 , n \leq 5 \times 10^4 $

对于前 $ 80\% $ 的数据，$ n \leq 5 \times 10^4 $

对于 $ 100\% $ 的数据，$ a_i > 0 , \sum a_i = n , n \leq 2 \times 10^5 , k \leq n $


第二个样例解释：

有如下$15$种情况：

![1567002672190.png](https://cdn.luogu.com.cn/upload/image_hosting/80ph1r8a.png)




## 样例 #1

### 输入

```
3 3
1 1 1```

### 输出

```
8```

## 样例 #2

### 输入

```
4 2
1 3```

### 输出

```
15```

# 题解

## 作者：小粉兔 (赞：11)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/11525881.html](https://www.cnblogs.com/PinkRabbit/p/11525881.html)。

### 题意简述：

有 $n$ 个点，染 $m$ 种颜色，第 $i$ 种颜色染恰好 $cnt_i$ 个节点，满足 $cnt_1+cnt_2+\cdots+cnt_m=n$。

求这 $n$ 个点组成的**本质不同**的**无标号**+**有序**（子树有序）基环（环长至少为 $2$）树个数。

两棵基环树本质相同当且仅当通过环的旋转（不能翻转）后能使得它们完全相同。

### 题解：

首先考虑只染一种颜色的 $n$ 个点（$n\ge1$）的无标号有根有序树个数计数。  
考虑这棵树的括号序，发现其括号序是长度为 $n$ 的合法括号串，但是必须满足最外层括号（根节点）只有一对。  
即 $n$ 个点的有根有序树个数为 $n-1$ 对括号组成的合法括号串，即第 $n-1$ 个卡特兰数。  
令 $n$ 个点的有根有序树个数为 $t_n$，令其 OGF 为 $\displaystyle T=\sum_{i=1}^{+\infty}t_ix^i$，即 $T=xC$，其中 $C$ 为卡特兰数的 OGF。

再考虑染色的问题，不难发现只要有序，则染色和树形态是相互独立的。  
即只要乘上一个多重组合数 $\displaystyle\binom{n}{cnt_1,cnt_2,\ldots,cnt_m}$ 即可。

----

回到原问题，枚举环长 $k$，使用 Burnside 引理统计等价类个数。环的旋转置换的统计方法是常见的，即枚举因数 $d$，等价于循环 $d$ 格的置换个数为 $\varphi\!\left(\dfrac{k}{d}\right)$。则有：

$$\begin{aligned}\mathbf{Ans}&=\sum_{k=2}^{n}\dfrac{1}{k}\sum_{d|k}\varphi\!\left(\dfrac{k}{d}\right)\!\cdot f(d)\end{aligned}$$

其中 $f(d)$ 表示循环 $d$ 格时的不动点个数。

循环 $d$ 格时，存在 $d$ 个长度为 $\dfrac{k}{d}$ 的循环，循环内的每个元素都代表一棵外向树。为了方便进一步的展开，交换 $d$ 与 $\dfrac{k}{d}$ 的意义，枚举 $d$ 为循环长度，而 $\dfrac{k}{d}$ 为循环个数。此时每个循环内的树形态相互独立，而且染色和树形态相互独立，但每个循环的树形态必须相同，且染色也必须相同，也就是说有 $\dfrac{k}{d}$ 棵树，且总点数为 $\dfrac{n}{d}$，并且需要满足每种颜色的个数是 $d$ 的倍数，即 $\left.d\:\middle|\:\gcd\limits_{i=1}^{m}cnt_i\right.$。则公式变为：

$$\begin{aligned}\mathbf{Ans}&=\sum_{k=2}^{n}\dfrac{1}{k}\sum_{d|k}\varphi(d)\cdot f\!\left(\dfrac{k}{d}\right)\!\\&=\sum_{k=2}^{n}\dfrac{1}{k}\sum_{d|k}\varphi(d)\cdot\!\left\{\!\left[d\:\middle|\:\gcd\limits_{i=1}^{m}cnt_i\right]\!\cdot\!\left[x^{n/d}\right]\!T^{k/d}\cdot\binom{n/d}{cnt_1/d,cnt_2/d,\ldots,cnt_m/d}\right\}\!\end{aligned}$$

此时有两条路可走，其一是留下生成函数 $T$ 的形式不变，其二是考虑使用卡特兰数的性质。

先使用第一种做法，考虑交换求和顺序并改变求和指标 $k$ 为 $kd$：

$$\begin{aligned}\mathbf{Ans}&=\sum_{k=2}^{n}\dfrac{1}{k}\sum_{d|k}\varphi(d)\cdot\!\left\{\!\left[d\:\middle|\:\gcd_{i=1}^{m}cnt_i\right]\!\cdot\!\left[x^{n/d}\right]\!T^{k/d}\cdot\binom{n/d}{cnt_1/d,cnt_2/d,\ldots,cnt_m/d}\right\}\!\\&=-t_n\binom{n}{cnt_{1\ldots m}}+\sum_{d\mid\gcd_{i=1}^{m}cnt_i}\varphi(d)\cdot\binom{n/d}{cnt_{1\ldots m}/d}\cdot\!\left[x^{n/d}\right]\!\sum_{k=1}^{n/d}\frac{T^k}{kd}\\&=-t_n\binom{n}{cnt_{1\ldots m}}+\sum_{d\mid\gcd_{i=1}^{m}cnt_i}\frac{\varphi(d)}{d}\cdot\binom{n/d}{cnt_{1\ldots m}/d}\cdot\!\left[x^{n/d}\right]\!\sum_{k=1}^{+\infty}\frac{T^k}{k}\\&=-t_n\binom{n}{cnt_{1\ldots m}}+\sum_{d\mid\gcd_{i=1}^{m}cnt_i}\frac{\varphi(d)}{d}\cdot\binom{n/d}{cnt_{1\ldots m}/d}\cdot\!\left[x^{n/d}\right]\!(-\ln(1-T))\end{aligned}$$

第二行的第一项是因为后面统计了 $d=k=1$ 的情况，但是实际不需要，所以要减掉。  
最后一行利用了 $\ln$ 在 $1$ 处展开的的泰勒级数：$\displaystyle\ln(1-x)=-\sum_{i=1}^{+\infty}\frac{x^i}{i}$。  
先使用多项式对数函数计算出 $-\ln(1-T)$，按照此式直接计算即可。时间复杂度 $\mathcal{O}(n\log n+\sigma_0(n)\cdot m)$。

----

第二种做法是考虑卡特兰数和自身的 $m$ 次卷积的第 $n$ 项的通项。

有公式 $\displaystyle[x^n]C^m=\binom{2n+m-1}{n}-\binom{2n+m-1}{n-1}$，将此式代入可得：

$$\begin{aligned}\mathbf{Ans}&=\sum_{k=2}^{n}\dfrac{1}{k}\sum_{d|k}\varphi(d)\cdot\!\left\{\!\left[d\:\middle|\:\gcd\limits_{i=1}^{m}cnt_i\right]\!\cdot\!\left[x^{n/d}\right]\!T^{k/d}\cdot\binom{n/d}{cnt_1/d,cnt_2/d,\ldots,cnt_m/d}\right\}\!\\&=\sum_{k=2}^{n}\dfrac{1}{k}\sum_{d|k}\varphi(d)\cdot\!\left\{\!\left[d\:\middle|\:\gcd\limits_{i=1}^{m}cnt_i\right]\!\cdot\!\left(\binom{2n/d-k/d-1}{2n/d-2k/d}-\binom{2n/d-k/d-1}{2n/d-2k/d-1}\right)\!\cdot\binom{n/d}{cnt_{1\ldots m}/d}\right\}\!\\&=-t_n\binom{n}{cnt_{1\ldots m}}+\sum_{d\mid\gcd_{i=1}^{m}cnt_i}\frac{\varphi(d)}{d}\cdot\binom{n/d}{cnt_{1\ldots m}/d}\sum_{k=1}^{n/d}\frac{1}{k}\!\left(\binom{2n/d-k-1}{2n/d-2k}-\binom{2n/d-k-1}{2n/d-2k-1}\right)\!\end{aligned}$$

直接计算即可，复杂度 $\mathcal{O}(\sigma_0(n)(n+m))$。

---

