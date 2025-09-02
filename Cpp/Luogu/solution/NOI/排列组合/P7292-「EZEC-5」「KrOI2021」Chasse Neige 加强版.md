# 「EZEC-5」「KrOI2021」Chasse Neige 加强版

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/kben34ml.png)

『我喜欢雪。』

『之前虽然讨厌寒冷，现在却是最喜欢了。』

![](https://cdn.luogu.com.cn/upload/image_hosting/sbuj1tnc.png)

## 题目描述

**本题与原题的区别是 $r$ 的范围扩大了，应该能卡掉 $O(n\log^2n)$ 的分治 FFT 做法，如果有分治 FFT 能过请联系我。同时，如果你的做法是 $O(n\log n)$ 的话，请注意常数优化。**

Rikka 给了你 $T$ 组询问，每组询问给定两个正整数 $n,k$，你需要告诉 Rikka 有多少个长度为 $n$ 的排列 $\pi$ 满足如下条件：

- $\pi_1<\pi_2$

- $\pi_{n-1}>\pi_{n}$

- 恰好存在 $k$ 个位置 $i(2\leq i\leq n-1)$ 满足 $\pi_{i-1}<\pi_{i}$ 且 $\pi_{i}>\pi_{i+1}$。

答案对 $998244353$ 取模。

## 说明/提示

### 样例解释 1

对于第一组询问，$n=3,k=1$，$(1,3,2)$ 和 $(2,3,1)$ 均满足条件，答案为 $2$。

对于第二组询问，满足条件的排列为：

$$(1,3,2,5,4),(1,4,2,5,3),(1,4,3,5,2),(1,5,2,4,3),(1,5,3,4,2)\\(2,3,1,5,4),(2,4,1,5,3),(2,4,3,5,1),(2,5,1,4,3),(2,5,3,4,1)\\(3,4,1,5,2),(3,4,2,5,1),(3,5,1,4,2),(3,5,2,4,1),(4,5,1,3,2),(4,5,2,3,1)$$

共 $16$ 个，所以答案为 $16$。

### 数据范围

对于 $100\%$ 的数据，$1\leq T\leq 2\times 10^5,3\leq n\leq r\leq 10^6,\max(1,\lfloor\frac{n-1}{2}\rfloor-10)\leq k\leq \lfloor\frac{n-1}{2}\rfloor$。

## 样例 #1

### 输入

```
2 10
3 1
5 2```

### 输出

```
2
16```

# 题解

## 作者：w33z8kqrqk8zzzx33 (赞：29)

良心出题人的良心题 /qq

~~官方题解怎么基本上跳过转移讲解啊~~

排列计数通常有两个 DP 方法：

 1. 按照顺序构造 DP，但是这里无法应用（存不了最后元素的值）
 2. 插入极值构造 DP

考虑维护第一值与第二值的关系，以及次后值与最后值关系。

 1. 令 $a_{n\ k}$ 为长度为 $n$ 的排列 $(\pi_1,\pi_2,\dots,\pi_n)$ 个数，使得存在恰好 $k$ 个巅峰并且 $\pi_1<\pi_2,\pi_{n-1}>\pi_n$。
 2. 令 $b_{n\ k}$ 为长度为 $n$ 的排列 $(\pi_1,\pi_2,\dots,\pi_n)$ 个数，使得存在恰好 $k$ 个巅峰并且 $\pi_1<\pi_2,\pi_{n-1}<\pi_n$。
 3. 令 $c_{n\ k}$ 为长度为 $n$ 的排列 $(\pi_1,\pi_2,\dots,\pi_n)$ 个数，使得存在恰好 $k$ 个巅峰并且 $\pi_1>\pi_2,\pi_{n-1}>\pi_n$。
 4. 令 $d_{n\ k}$ 为长度为 $n$ 的排列 $(\pi_1,\pi_2,\dots,\pi_n)$ 个数，使得存在恰好 $k$ 个巅峰并且 $\pi_1>\pi_2,\pi_{n-1}<\pi_n$。

则：

 1. $b_{n\ k}$ 与 $c_{n\ k}$ 具有一一对应：$(\pi_1,\pi_2,\dots,\pi_n)\Leftrightarrow(\pi_n,\pi_{n-1},...,\pi_1)$。
 2. $a_{n\ k}$ 与 $d_{n\ k-1}$ 具有一一对应：$(\pi_1,\pi_2,\dots,\pi_n)\Leftrightarrow(n+1-\pi_1,n+1-\pi_2,\dots,n+1-\pi_n)$。这是因为每一个巅峰（除了最后一个）都有恰好一个紧接下来的逆巅峰，每一个逆巅峰都有恰好一个紧接下来的巅峰。

于是我们只需要往 $a_{n\ k},b_{n\ k}$ 转移。

以下格式为 $\text{旧排列类型}\rightarrow\text{新排列类型}$。注意旧排列最后元素为 $\pi_{n-1}$。考虑转移，我们转移时插入 $n$ 使巅峰变换更简介：

 1. $a_{n-1\ k}\rightarrow a_{n\ k}$ 有 $2k$ 方案；不会产生新巅峰当且仅当插入在紧挨着一个旧巅峰，覆盖了旧巅峰。
 2. $a_{n-1\ k-1}\rightarrow a_{n\ k}$ 有 $n-1-1-2(k-1)=n-2k$ 方案；需要插入在旧排列 **里面** 并且不能挨着一个巅峰，这样会新构造一个巅峰。
 3. $b_{n-1\ k-1}\rightarrow a_{n\ k}$ 有 $1$ 方案；插入在旧排列 $\pi_{n-2}$ 和 $\pi_{n-1}$ 之间会产生恰好一个巅峰。
 4. $c_{n-1\ k-1}\rightarrow a_{n\ k}$ 有 $1$ 方案；插入在旧排列 $\pi_1$ 和 $\pi_2$ 之间会产生恰好一个巅峰。
 5. $b_{n-1\ k}\rightarrow b_{n\ k}$ 有 $2k+1$ 方案；与 $1$ 转移同理，也可以插入在旧排列 $\pi_{n-1}$ 后面。
 6. $b_{n-1\ k-1}\rightarrow b_{n\ k}$ 有 $n-1-1-2(k-1)-1=n-2k-1$ 方案；基本和 $2$ 同理，但是需要减 $1$ 因为不能在旧 $\pi_{n-2},\pi_{n-1}$ 之间插入。
 7. $a_{n-1\ k}\rightarrow b_{n\ k}$ 有 $1$ 方案；插入在旧排列 $\pi_{n-1}$ 后面。
 8. $d_{n-1\ k-1}\rightarrow b_{n\ k}$ 有 $1$ 方案；插入在旧排列 $\pi_1$ 和 $\pi_2$ 之间，同时会产生一个新巅峰。

于是有递推

$$\begin{cases}a_{n\ k}=2ka_{n-1\ k}+(n-2k)a_{n-1\ k-1}+b_{n-1\ k-1}+c_{n-1\ k-1}\\b_{n\ k}=(2k+1)b_{n-1\ k}+(n-2k-1)b_{n-1\ k-1}+a_{n-1\ k}+d_{n-1\ k-1}\end{cases}$$

采用以上一一对应：

$$\begin{cases}a_{n\ k}=2ka_{n-1\ k}+(n-2k)a_{n-1\ k-1}+2b_{n-1\ k-1}\\b_{n\ k}=(2k+1)b_{n-1\ k}+(n-2k-1)b_{n-1\ k-1}+2a_{n-1\ k}\end{cases}$$

不 感 觉 很 类 似 吗 ？

定 $f_{n\ k}$，其中 $f_{n\ 2k}=a_{n\ k}$，$f_{n\ 2k+1}=b_{n\ k}$，则 $a_{n\ k}$ 在 $f$ 里“上一个”元素是 $b_{n\ k-1}$，$b_{n\ k}$ 在 $f$ 里“上一个”元素是 $a_{n\ k}$。

于是有

$$f_{n\ k}=kf_{n-1\ k}+(n-k)f_{n-1\ k-2}+2f_{n-1\ k-1}$$

考虑 $f_{n\ n-1}$ 代表什么；替换回去得到 $f_{2n\ 2n-1}=f_{2n\ 2(n-1)+1}=b_{2n\ n-1}$；$f_{2n+1\ 2n}=a_{2n+1\ n}$。

套会原始，得到 $f_{2n\ 2n-1}=b_{2n\ n-1}$ 为满足相邻比较是 `<><><...><` 的排列，$f_{2n+1\ 2n}=a_{2n+1\ n}$ 位满足 `<><><...><>` 的排列。

这些是 ”Alternating permuation numbers“，由 Andre 定理，这数列由指数生成函数 $[\frac{x^n}{n!}](\tan(x)+\sec(x))$ 给出。于是

$$f_{n\ n-1}=n![x^n](\tan(x)+\sec(x))$$

考虑定义 $f'_{n\ d}=f_{n\ n-d}$，则：

$$f'_{n\ d}=(n-d)f_{n-1\ k}+df_{n-1\ k-2}+2f_{n-1\ k-1}$$
$$f'_{n\ d}=(n-d)f'_{n-1\ d-1}+df'_{n-1\ d+1}+2f'_{n-1\ d}$$
$$\begin{cases}f'_{n\ 1}=n![x^n](\tan(x)+\sec(x))\\f'_{n-1\ d+1}=\frac{f'_{n\ d}-(n-d)f'_{n-1\ d-1}-2f'_{n-1\ d}}{d}\end{cases}$$

问题想求 $a_{n\ k}=f_{n\ 2k}=f'_{n\ n-2k}$，递推即可。

最优解 /qq

---

## 作者：Karry5307 (赞：29)

### 题意

$T$ 组询问，求有多少个长度为 $n$ 的排列 $\pi$ 满足如下条件：

- $\pi_1<\pi_2$

- $\pi_{n-1}>\pi_{n}$

- 恰好存在 $k$ 个位置 $i(2\le i\le n-1)$ 满足 $\pi_{i-1}<\pi_{i}$ 且 $\pi_{i}>\pi_{i+1}$。

答案对 $998244353$ 取模。

$\texttt{Data Range:}1\leq T\leq 2\times 10^5,3\leq n\leq r\leq 10^6,\max(1,\lfloor\frac{n-1}{2}\rfloor-10)\leq k\leq \lfloor\frac{n-1}{2}\rfloor$

### 前言

[题目名来源请右转这里](https://www.bilibili.com/video/BV1hE411Q7Ti)

Rikka 可爱！

### 题解

首先考虑暴力 DP。由于我们只需要关心极大值有多少个，只需要看有多少个极长单调子段。讨论一下第一个和最后一个位置所处子段的单调性就可以设四个东西来：

- 设 $f_{n,k}$ 表示长度为 $n$ 并满足 $\pi_1<\pi_2,\pi_{n-1}>\pi_n$ 且有 $k$ 个极大值的排列个数。

- 设 $g_{n,k}$ 表示长度为 $n$ 并满足 $\pi_1>\pi_2,\pi_{n-1}>\pi_n$ 且有 $k$ 个极大值的排列个数。

- 设 $g^{\prime}_{n,k}$ 表示长度为 $n$ 并满足 $\pi_1<\pi_2,\pi_{n-1}<\pi_n$ 且有 $k$ 个极大值的排列个数。

- 设 $h_{n,k}$ 表示长度为 $n$ 并满足 $\pi_1>\pi_2,\pi_{n-1}<\pi_n$ 且有 $k$ 个极大值的排列个数。

这里排列的第一个和最后一个位置并不算极大值，下面的图中，左上表示 $f_{n,k}$，右上表示 $g_{n,k}$，左下表示 $g^{\prime}_{n,k}$，右下表示 $h_{n,k}$，红圈圈出来的表示计入的极大值，必须要恰有 $k$ 个，一个极长单调子段中只标出了首尾元素。

![](https://cdn.luogu.com.cn/upload/image_hosting/3m0b5pjn.png)

同时有两个性质：如果 $(\pi_1,\cdots,\pi_n)$ 是被计入 $g$ 的，那么 $(\pi_n,\cdots,\pi_{1})$ 则会被计入 $g^{\prime}$，也即 $g_{n,k}=g^{\prime}_{n,k}$。如果 $(\pi_1,\cdots,\pi_n)$ 是被计入 $h$ 的，那么 $(n-\pi_1+1,\cdots,n-\pi_n+1)$ 则会被计入 $f$，但是要多统计一个极大值，也即 $h_{n,k}=f_{n,k+1}$。

这样只需要对 $f_{n,k}$ 和 $g_{n,k}$ 进行 DP。考虑将 $n$ 插到长度为 $n-1$ 的排列中。注意到插到极大值两边不会造成 $k$ 的增加，别的地方均可以造成极大值的增加（这也是为什么首尾不计入极大值的原因），于是可以列出如下式子：

$$\begin{cases}f_{i,j}=2jf_{i-1,j}+(i-2j)f_{i-1,j-1}+g_{i-1,j-1}+g^{\prime}_{i-1,j-1}\\g_{i,j}=2jg_{i-1,j}+(i-2j-1)g_{i-1,j-1}+g_{i-1,j}+f_{i-1,j}+h_{i-1,j-1}\end{cases}$$

第一个式子中右边分别表示插在极大值两侧，不插在极大值两侧，插在满足 $g$ 的排列的前两个位置之间，满足 $g^{\prime}$ 的后两个位置之间。第二个式子中右边分别表示插在极大值两侧，不插在极大值两侧，插在满足 $g$ 的排列的最左边，满足 $f$ 的最左边以及满足 $h$ 的前两个位置之间。

但是根据之前的两个性质可以简化一下这个式子：

$$\begin{cases}f_{i,j}=2jf_{i-1,j}+(i-2j)f_{i-1,j-1}+2g_{i-1,j-1}\\g_{i,j}=(2j+1)g_{i-1,j}+(i-2j-1)g_{i-1,j-1}+2f_{i-1,j}\end{cases}$$

注意到这两个式子长得很像，所以可以合并成一个。设 $f^{\prime}_{i,2j}=f_{i,j},f^{\prime}_{i,2j+1}=g_{i,j}$，那么很明显可以合并成这样：

$$f^{\prime}_{i,j}=jf^{\prime}_{i-1,j}+(i-j)f^{\prime}_{i-1,j-2}+2f^{\prime}_{i-1,j-1}$$

$O(n^2)$ DP 即可拿到 32pts。

注意数据范围有一个 $\max(1,\lfloor\frac{n-1}{2}\rfloor-10)\leq k\leq \lfloor\frac{n-1}{2}\rfloor$，相当于是只需要你回答靠近对角线位置的值，所以看看能不能快速求出对角线上的值。

这里存在另外一个 DP。设 $f_n$ 表示长度为 $n$ 的排列中每个数交错并且 $\pi_1<\pi_2,\pi_{n-1}>\pi_n$ 的排列个数，$g_n$ 表示长度为 $i$ 的排列中每个数交错并且 $\pi_1>\pi_2,\pi_{n-1}>\pi_{n}$ 的排列个数，枚举 $n$ 放在哪里可以得到以下式子：

$$\begin{cases}f_{n}=\sum\limits_{i\text{ is odd}}\binom{n-1}{i}f_{i}f_{n-1-i}\\g_n=\sum\limits_{i\text{ is even}}\binom{n-1}{i}g_{i}f_{n-1-i}\end{cases}$$

到这一步可以 $O(n\log^2n+n(n-2k))$ 分治 FFT，然而这个做法不优秀，本题无法通过。

钦定 $f_n$ 在 $n$ 为偶数的时候，$g_n$ 在 $n$ 为奇数的时候为 $0$，设 $F(x),G(x)$ 为 $f,g$ 的 EGF，则有

$$F^{\prime}(x)=F^2(x)+1,G^{\prime}(x)=F(x)G(x)$$

考虑解这个微分方程，鉴于讲评时的反响，这里给出具体解法。

$$
\def\rd{\ \mathrm{d}}
\frac{\rd F(x)}{\rd x}=F^2(x)+1\\\ \\
\frac{1}{F^2(x)+1}\rd F(x)=\rd x\\\ \\
\int \frac{1}{F^2(x)+1}\rd F(x)=\int\rd x\\\ \\
\tan^{-1}F(x)=x+C\\\ \\
F(x)=\tan (x+C)
$$

可以自行检验 $C=0$，即 $F(x)=\tan x$，以及

$$
\def\rd{\ \mathrm{d}}
\frac{\rd G(x)}{\rd x}=G(x)\tan x\\\ \\
\frac{1}{G(x)}\rd G(x)=\tan x\rd x\\\ \\
\int \frac{1}{G(x)}\rd G(x)=\int \tan x\rd x\\\ \\
\ln\vert G(x)\vert=\ln\vert\sec x\vert+C\\\ \\
\vert G(x)\vert=C\vert\sec x\vert
$$

可以自行检验 $C=1$ 且绝对值取正，所以 $G(x)=\sec x$。

于是，$f^{\prime}_{n,n}=[x^n](\tan x+\sec x)$，多项式求逆即可，然后再递推回来得到所有的 $f^{\prime}$，时间复杂度 $O(n\log n+n(n-2k))$，本题可能需要一些常数优化。

代码就不放了，实在需要代码的找我。

彩蛋：

![](https://cdn.luogu.com.cn/upload/image_hosting/gp621hfo.png)


![](https://cdn.luogu.com.cn/upload/image_hosting/hphuouv9.png)

---

