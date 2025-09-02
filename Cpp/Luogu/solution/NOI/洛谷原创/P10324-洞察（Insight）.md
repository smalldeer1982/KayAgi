# 洞察（Insight）

## 题目背景

看待万物毫无偏见的新视角 —— 洞察。

****
「洞察之光」凯伊·雅思·德·布拉德，是减法盗贼，也是背负黑暗命运的混沌骑士。

凯伊的右手内隐藏着混沌之剑，为了使其发挥出足够的力量又不至于失控，需要满足特定的内部结构。她想知道有多少种符合条件的结构，为了方便你的计算，她把问题转化为如下形式：

## 题目描述

赛时更新：题面中的笔误已修改为：相邻点对颜色**互不相同**。
****
在一个**无向连通图** $G$ 中，有黑色和白色的点各 $n$ 个，红色的点 $1$ 个。  
所有点都有标号，图中有 $2n$ 条边，且所有相邻点对（也就是有边直接相连的点对）的颜色也互不相同。

对于 $\text{type}$ 等于 $0$ 或 $1$，分别在不同条件下计算符合条件的图 $G$ 有多少个：

- $\text{type}=0$：无附加条件。  
- $\text{type}=1$：对于每个**不包含**红色点的极大连通子图，都要对**恰好一个**点做特殊标记（每个标记也都是不同的）。

答案对 $998244353$ 取模。

## 说明/提示

【样例 $1$ 解释】  
此时 $\text{type}=1$，所有 $5$ 种合法的图包括：

1. $R-W'-B$
2. $R-W-B'$
3. $R-B'-W$
4. $R-B-W'$
5. $B'-R-W'$

由于 $n=1$，可以仅用 $B$ 和 $W$ 来区分白点和黑点，$R$ 表示红点。中间的横杠表示连边，$B'$ 和 $W'$ 分别表示有标记的白点和黑点。

注意，由于第 $5$ 个图中，单个的 $B$ 和 $W$ 就是不包含 $R$ 的极大连通子图，必须各有一个标记在这唯一的位置上。

【样例 $2,3$ 解释】

见附件图片，其中展示了 $\text{type}=0$ 时全部的 $45$ 种可能的图 $G$。

对于 $\text{type}=1$ 的情况，只需要对每个图的基础上做标记，就可以数出答案为 $149$。

【样例 $4,5$ 解释】

取模前的答案分别为 $116758263583336861101$ 和 $4159784334433940020473603987503242886367209494283213841$。

【数据范围】

**本题采用捆绑测试。**

Subtask 1（8 pts）：$n \le4$；     
Subtask 2（10 pts）：$n \le 10^3$，$\text{type}=0$；  
Subtask 3（11 pts）：$\text{type}=0$；  
Subtask 4（13 pts）：$n \le 100$，$\text{type}=1$；     
Subtask 5（14 pts）：$n \le 10^3$，$\text{type}=1$；  
Subtask 6（21 pts）：$n\le 10^5$，$\text{type}=1$；  
Subtask 7（23 pts）：$\text{type}=1$。

对于全部的数据，$1\le n \le 10^7$，$\text{type}\in \{ 0,1\}$。

【提示】  
对于这类题目，你或许会想从 [OEIS](https://oeis.org/) 上寻找答案。但我要提醒你的是，直接搜索答案数列不会找到任何结果。然而，对于小数据范围，仍然可以提前处理出答案数列。


## 样例 #1

### 输入

```
1 1```

### 输出

```
5```

## 样例 #2

### 输入

```
2 0```

### 输出

```
45```

## 样例 #3

### 输入

```
2 1```

### 输出

```
149```

## 样例 #4

### 输入

```
10 0```

### 输出

```
36011666```

## 样例 #5

### 输入

```
20 1```

### 输出

```
593465999```

## 样例 #6

### 输入

```
106 1```

### 输出

```
516553582```

# 题解

## 作者：Aleph1022 (赞：10)

首先要注意到我们只要数树。进一步，删掉红色的点和相邻的边之后只剩下一片森林。

设 $x, y$ 计量白点 / 黑点，$W(x, y), B(x, y)$ 分别表示以白点 / 黑点为根的树的二元 EGF，可以列出方程

$$
\begin{cases}
W(x, y) = x \mathrm e^{B(x, y)} \\
B(x, y) = y \mathrm e^{W(x, y)}
\end{cases}
$$

对于 $\mathrm{type}=0$，我们只需计算

$$
\left[\frac{x^ny^n}{n!n!}\right] \mathrm e^{W(x,y)+B(x,y)}
$$

施**多元 Lagrange 反演**，可得其

$$
\begin{aligned}
&=\left[\frac{x^ny^n}{n!n!}\right] \mathrm e^{(n+1)(x+y)}(1-xy) \\
&=(n+1)^{2n}-n^2(n+1)^{2n-2} \\
&=(2n+1)(n+1)^{2n-2}
\end{aligned}
$$

对于 $\mathrm{type}=1$，我们需要计算

$$
\left[\frac{x^ny^n}{n!n!}\right] \exp\left((x\partial_x+y\partial_y)(W+B)\right)
$$

不妨在方程两侧取 $\partial_x$，可得

$$
\begin{cases}
\partial_x W = \mathrm e^{B} + W \partial_x B\\
\partial_x B = B \partial_x W
\end{cases}
$$

即

$$
\begin{cases}
x\partial_x W = \frac W{1-WB} \\
x\partial_x B = \frac{WB}{1-WB}
\end{cases}
$$

$\partial_y$ 的结果同理。因此我们需要计算

$$
\left[\frac{x^ny^n}{n!n!}\right] \exp\left(\frac{W+B+2WB}{1-WB}\right)
$$

施多元 Lagrange 反演知其

$$
=\left[\frac{x^ny^n}{n!n!}\right] \exp\left(\frac{x+y+2xy}{1-xy}\right) \mathrm e^{n(x+y)}(1-xy)
$$

换元，令 $x\mapsto st^{-1}, y\mapsto t$，可得其

$$
\begin{aligned}
&= n!^2 [s^n t^0]\exp\left(\frac{st^{-1}+t+2s}{1-s}\right) \mathrm e^{n(st^{-1}+t)}(1-s) \\
&= n!^2 [s^n t^0] \exp\left(\frac{(1+n(1-s))(st^{-1}+t)}{1-s}\right) \mathrm e^{\frac{2s}{1-s}} (1-s) \\
&= n!^2 [s^n] (1-s) \mathrm e^{\frac{2s}{1-s}} \sum_{j\ge 0} \frac1{j!^2} \left(\frac{1+n(1-s)}{1-s}\right)^{2j} s^j \\
&= n!^2 [s^n] (1-s) \mathrm e^{\frac{2s}{1-s}} {}_0F_1\left(;1;\frac{s(1+n(1-s))^2}{(1-s)^2}\right)
\end{aligned}
$$

是 D-Finite 的。时间复杂度 $O(n)$ 或 $O(\sqrt n \log n)$。

---

## 作者：NaCly_Fish (赞：10)

首先来确认一下题意：整个图是一棵树，而树上只有一个红色点。那这个图就可以看作是若干「仅由黑白点构成的树」接在红点上构成的。那么接下来就数这样的黑白树就好。

考虑生成函数，用 $x$ 计量白点数，$y$ 计量黑点。设 $F$ 是以白点为根的树的 EGF，$G$ 则是以黑点为根的情况，则有生成函数方程：

$$\begin{cases} F = x \exp G \\G = y \exp F \end{cases}$$
那么对于 $\text{type}=0$ 的答案就很简单，是 $(n!)^2[x^ny^n]\exp(F+G)$。

$\text{type}=1$ 情况的说明有点绕，实际上就是把 $F+G$ 的 $x^iy^j$ 项系数乘上 $(i+j)$ 再做 $\exp$（因为有 $i+j$ 个点的树上选一个点标记的方案就是 $i+j$ 种），那么答案就是：
$$(n!)^2[x^ny^n]\exp \left( x\frac{\partial(F+G)}{\partial x}+y\frac{\partial(F+G)}{\partial y}\right)$$
下面我们对两种情况分别求解。

****

$\large \text{type}=0:$

有一种比较粗暴的做法，是直接写 $F=x \exp(y \exp F)$，然后对 $F$ 的 $x$ 这一维做 Lagrange 反演，即：

$$F^{\langle -1 \rangle}=\frac{x}{\exp(y \exp x)}$$

$$\begin{aligned}[x^ny^n]\exp(F+G)&=[x^ny^n]\exp(F+y \exp F)  \\ &=\frac 1n[x^{n-1}y^n]\exp(x+y\text e^x)(1+y\text e^x)\exp(n y \text e^x) \\ &= \frac 1n[x^{n-1}y^n] \text e^x\exp (y\text e^x)(1+y\text e^x)\exp(n y \text e^x)\end{aligned}$$
发现这个东西我们好像不会算，那就先求出
$$\begin{aligned}[y^n]x \exp(y x)(1+yx)\exp(nyx)&=x[y^n](1+yx)\exp((n+1)yx)  \\ &= x\left(\frac{(n+1)^nx^n}{n!}+\frac{(n+1)^{n-1}x^n}{(n-1)!}\right)\end{aligned}$$
然后就可以把  $x$ 再换回 $\text e^x$，这个东西就可以直接提取系数，答案就是 $(n+1)^{2n-1}+n(n+1)^{2n-2}$。

时间复杂度为 $\Theta(\log n)$。
****
$\large \text{type}=1:$

摆在面前的第一个难题，就是答案算式中 $\exp$ 里面那一大坨怎么处理。  
如果不做任何处理，可以跑 $\Theta(n^4)$ 的递推算 $\exp$；当然也可以用 FFT 优化二维卷积，时间复杂度 $\Theta(n^2 \log n)$。跑过 Subtask 4 是没有问题的。

如果要优化，可以尝试对原方程求偏导，就能得到如下结果：

$$\begin{aligned} \frac{\partial F}{\partial x}&=\frac Fx+F \frac{\partial G}{\partial x} \\ \frac{\partial F}{\partial x}&= \frac Fx+FG \frac{\partial F}{\partial x} \\ x\frac{\partial F}{\partial x} &= \frac{F}{1-FG}\end{aligned}$$
类似地也处理另外几个部分，就可以发现
$$x\frac{\partial(F+G)}{\partial x}+y\frac{\partial(F+G)}{\partial y}=\frac{F+G+2FG}{1-FG}$$
现在就方便一些了，不过这回又遇到了第二个难题：直接对一维使用 Lagrange 反演的话，会得到很奇怪的式子 —— 不能再像 $\text{type}=0$ 时那样简单地使用 $x \leftrightarrow \text e^x$ 的变换来处理了：
$$[x^ny^n]\exp\left(\frac{x+y\text e^x+2xy \text e^x}{1-x y\text e^x}\right)\exp(-y\text e^x)(1-xy \text e^x)\exp((n+1)y \text e^x)$$

太复杂了，这玩意看着就不想动它。那怎么办？一种方法是**多元 Lagrange 反演**，可以得到答案为

$$[x^ny^n]\exp\left( \frac{x+y+2xy}{1-xy}\right)\text e^{nx}\text e^{ny}\det \left ( \begin{matrix} 1 & -x \\ -y & 1\end{matrix} \right )$$

好吧，这个形式也不算简单。但是它有着不错的对称性，做换元 $u=x+y$，$v=xy$，设：

$$H=\exp\left( \frac{u+2v}{1-v}+nu\right)(1-v)$$
则除以 $n!^2$ 后的答案为
$$\sum_{a\geq 0}\sum_{b\geq 0}\left([u^av^b]H\right)\left([x^ny^n](x+y)^a(xy)^b \right)$$
（复合函数提取系数的方法）  

考虑 $[x^ny^n](x+y)^a(xy)^b=[(xy)^{n-b}](x+y)^a$ 只有在 $a=2(n-b)$ 时才非零，化简为：

$$\sum_{b=0}^n\binom{2(n-b)}{n-b}[u^{2(n-b)}v^b]H$$
然后把 $\exp$ 里面拆开：
$$\begin{aligned}H&=\exp\left( u\left( n +\frac{1}{1-v}\right)+\frac{2v}{1-v}\right)(1-v) \\ &= (1-v) \exp\left(u\left(n+ \frac{1}{1-v}\right)\right)\exp \left( \frac{2v}{1-v}\right)\end{aligned}$$
这样就可以很方便地提取其 $u^{2(n-b)}$ 系数，因为只有第一个 $\exp$ 中含有 $u$，这就直接得到

$$[u^{2(n-b)}]H=\frac{1-v}{(2n-2b)!}\exp \left( \frac{2v}{1-v}\right)\left( n+\frac{1}{1-v}\right)^{2(n-b)}$$
带回原式，答案就是
$$\begin{aligned}&[v^n]\sum_{b=0}^n\frac{v^{n-b}}{(n-b)!^2}(1-v)\exp \left( \frac{2v}{1-v}\right)\left( n+\frac{1}{1-v}\right)^{2(n-b)} \\ &=[v^n](1-v)\exp \left( \frac{2v}{1-v}\right)\sum_{b=0}^{\infty} \frac{v^b}{b!^2}\left( n+\frac{1}{1-v}\right)^{2b}\end{aligned}$$
要提取系数的这一大块是微分有限的。这是因为
$$A(x)=\sum_{i=0}^\infty \frac{x^i}{i!^2}$$
是微分有限的，而且
$$B(x)=x\left( n+\frac{1}{1-x}\right)^2$$
是代数的（甚至还是有理分式）。为了方便计算，可以单独整式递推出 $A(B(x))$ 的系数。

要找出整式递推式，比较方便的做法是直接算出前几项然后高斯消元。当然由于 $B(x)$ 比较简单，直接把递推式求出来也是可行的。

时间复杂度为 $\Theta(n)$ 或 $\Theta(\sqrt n \log n)$。

迷思：是否有更快的做法呢？

---

