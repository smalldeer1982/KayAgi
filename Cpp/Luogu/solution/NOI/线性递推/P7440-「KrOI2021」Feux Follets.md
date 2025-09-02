# 「KrOI2021」Feux Follets

## 题目背景

Note：$\sigma(5307)=7440$，且在所有满足 $\sigma(x)=7440$ 的 $x$ 中这是唯一一个模 10 余 7 的数。

## 题目描述

设 $\text{cyc}_\pi$ 将长为 $n$ 的排列 $\pi$ 当成置换时所能分解成的循环个数。给定两个整数 $n,k$ 和一个 $k-1$ 次多项式，对 $1\leq m\leq n$ 求：

$$
\sum\limits_{\pi}F(\text{cyc}_{\pi})
$$

其中 $\pi$ 是长度为 $m$ 且不存在位置 $i$ 使得 $\pi_i=i$ 的排列。

## 说明/提示

### 数据范围

对于 $100\%$ 的数据，$1\leq n,k\leq 10^5$。

## 样例 #1

### 输入

```
3 2
0 1```

### 输出

```
0 1 2```

## 样例 #2

### 输入

```
6 4
11 43 27 7```

### 输出

```
0 88 176 1311 7332 53070```

## 样例 #3

### 输入

```
6 4
9 72 22 7```

### 输出

```
0 110 220 1551 8580 60990```

# 题解

## 作者：Karry5307 (赞：20)

### 题意

设 $\text{cyc}_\pi$ 将长为 $n$ 的排列 $\pi$ 当成置换时所能分解成的循环个数。给定两个整数 $n,k$ 和一个 $k-1$ 次多项式，对 $1\leq m\leq n$ 求：

$$
\sum\limits_{\pi}F(\text{cyc}_{\pi})
$$

其中 $\pi$ 是长度为 $m$ 且不存在位置 $i$ 使得 $\pi_i=i$ 的排列。

$\texttt{Data Range:}1\leq n,k\leq 10^5$。

### 题解

转置原理。

本篇题解同时适用于 P7438 P7439 和 P7440。

首先将给出的多项式转成牛顿级数，即 $F(x)=\sum\limits_{i}f_i\dbinom{x}{i}$，然后考虑对每一个 $\dbinom{x}{i}$ 单独计算，即

$$\sum\limits_{\pi}\dbinom{\text{cyc}_\pi}{i}$$

也即对所有错排求环数选 $i$ 个的答案。

对于错排而言其 EGF 为 $e^{-x-\ln(1-x)}$，而一元的生成函数不足以表达出环数这个信息，所以再加一个元区分一下，即 $e^{(1+y)(-x-\ln(1-x))}$。

其中 $1+y$ 表示的是如果选这个环则贡献为 $y$，否则贡献为 $1$，如果不熟悉组合符号化的读者可以使用 DP 得到结果，这里简单讲一下。

设 $f_{i,j}$ 表示长度为 $i$ 的排列选 $j$ 个环的答案，考虑枚举 $n$ 所在的环的长度，则有

$$f_{i,j}=\sum\limits_{k\geq 2}\binom{n-1}{k-1}(k-1)!(f_{i-k,j}+f_{i-k,j-1})$$

同样可以得到上面的式子。

考虑对 GF 求偏导，则有

$$\frac{\partial}{\partial x}F(x,y)=\frac{x(1+y)}{1-x}F(x,y)$$

$$[x^n]\frac{\partial}{\partial x}F(x,y)=[x^n]\frac{x(1+y)}{1-x}F(x,y)$$

$$(n+1)[x^{n+1}]F(x,y)=[x^n]\frac{y}{1-x}F(x,y)+[x^n]\frac{1}{1-x}F(x,y)$$

$$(n+1)[x^{n+1}y^m]F(x,y)=[x^ny^{m-1}]\frac{1}{1-x}F(x,y)+[x^ny^m]\frac{1}{1-x}F(x,y)$$

$$(n+1)[x^{n+1}y^m]F(x,y)=\sum_{i}[x^iy^{m-1}]F(x,y)+[x^iy^m]F(x,y)$$

递推系数即可，复杂度 $O(nk)$，可以通过 P7438。

---

现在考虑 $k=10^5$ 求一项，这个时候由于是 $1+y$ 不好处理，考虑先求 $[x^n]e^{y(-x-\ln(1-x))}$。

考虑拉格朗日反演，设 $\dfrac{G^2(x)}{2}=-x-\ln(1-x)$，其复合逆为 $H(x)$，则 $F(x,y)$ 实质上是 $G(x)$ 与 $e^{\frac{x^2y}{2}}$ 的复合，则根据拓展拉格朗日反演有

$$[x^n]e^\frac{G^2(x)y}{2}=\frac{1}{n}[x^{n-1}]xye^{\frac{x^2y}{2}}\left(\frac{x}{H(x)}\right)^n$$

注意到

$$xye^{\frac{x^2y}{2}}=\sum\limits_{i}\frac{x^{2i+1}y^{i+1}}{2^ii!}$$

所以有

$$\frac{1}{n}[x^{n-1}y^m]xye^{\frac{x^2y}{2}}\left(\frac{x}{H(x)}\right)^n=\frac{1}{n2^{m-1}(m-1)!}[x^{n-2m}]\left(\frac{x}{H(x)}\right)^n$$

如果知道复合逆的话可以直接算，现在考虑求 $H(x)$。由于 $G(x)$ 有简单的封闭形式可以牛迭，即

$$\frac{G^2(x)}{2}=-x-\ln(1-x)$$

那么有

$$\frac{x^2}{2}=-H(x)-\ln(1-H(x))$$

即

$$2H(x)+2\ln(1-H(x))+x^2=0$$

直接牛迭即可，注意中间有可能会对一个没有常数项的多项式求逆，这里分子分母同时除以 $x$ 即可，同时 $H(x)$ 的初值为 $x$，而且由于除法的原因次数会不对，多迭代一次即可，可以通过 P7439。

alpha1022 和 cmd_block 的牛迭式子与这个有所不同，感兴趣的读者可以看看。

---

现在考虑 P7440，也就是本题。设 $G(x,y)=e^{(1+y)(-x-\ln(1-x))}$，目标变成了计算

$$\sum\limits_{i}f_i[y^i]G(x,y)$$

考虑转置原理，变成求

$$\sum\limits_{i}f_i[x^i]G(x,y)$$

对 $G(x,y)$ 求偏导则有

$$\frac{\partial}{\partial x}G(x,y)=\frac{x(1+y)}{1-x}G(x,y)$$

设 $F_i=[x^i]G(x,y)$ 则有

$$F_i=\frac{i-1}{i}F_{i-1}+\frac{y+1}{i}F_{i-2}$$

用矩阵表示一下则有

$$\begin{pmatrix}F_i&F_{i-1}\end{pmatrix}=\begin{pmatrix}F_{i-1}&F_{i-2}\end{pmatrix}\begin{pmatrix}\dfrac{i-1}{i}&1\\\dfrac{y+1}{i}&0\end{pmatrix}$$

设

$$\begin{pmatrix}F_i&F_{i-1}\end{pmatrix}=\begin{pmatrix}F_{i-1}&F_{i-2}\end{pmatrix}A_i$$

则实际上的就是

$$\sum\limits_{i}\begin{pmatrix}f_i&0\end{pmatrix}\prod_{j=1}^{i}A_j$$

右边的矩阵乘积可以使用分治 FFT，然后算这个也可以分治算，时间复杂度 $O(n\log^2n+k\log^2k)$。

---

## 作者：warzone (赞：14)

前置芝士：[转置原理](https://www.luogu.com.cn/blog/wangrx/tellegen-s--principle)  
# 题意

设 $\text{cyc}_\pi$ 为将长为 $n$ 的排列 $\pi$ 当成置换时所能分解成的循环置换个数。  
给定两个整数 $n,k$ 和一个 $k-1$ 次多项式，对 $1\leq m\leq n$ 求：

$$\sum\limits_{\pi}F(\text{cyc}_{\pi})$$

其中 $\pi$ 是长度为 $m$ 且不存在位置 $i$ 使得 $\pi_i=i$ 的排列。

$\texttt{Data Range:}1\leq n,k\leq 10^5$

如果你不知道置换是啥，请看：  
[oi-wiki 置换群](https://oi-wiki.org/math/permutation-group/)  
链接里没提到的东西（怕听不懂）：
- （映射的定义）函数是映射的一种。
- $\dbinom{a_1,a_2}{a_{p_1},a_{p_2}}$ 与 $\dbinom{a_2,a_1}{a_{p_2},a_{p_1}}$ 是同一种置换。  
  （只要上下对应就可以了，顺序无所谓）

# 题解

首先考虑 $\text{exp}$ 的组合意义：

> 若 $f_n$ 表示对 $n$ 个不同的元素作某种计数，$f(x)=\displaystyle\sum_{k=0}^\infty f_kx^k$，  
 则 $\text{OGF}(e^{\text{EGF}f})$ 表示将 $n$ 种不同元素划分为任意个无标号集合，  
 每个集合内的元素分别作该种计数的方案数。  
证明：已知 $e^{f(x)}=\displaystyle\sum_k\frac{f^k(x)}{k!}$，由卷积和指数生成函数的定义可知  
> $$[x^n]\text{OGF}(e^{\text{EGF} f})=\sum_{k}\frac{1}{k!}\sum_{\sum_{i=1}^ka_i=n}\binom{n}{a_1,a_2,\cdots a_k}\prod_{i=1}^kf_{a_i}$$
> - $\displaystyle\sum_{i=1}^ka_i=n$ 表示总共有 $n$ 个元素。
> - $\dbinom{n}{a_1,a_2,\cdots a_k}$ 表示划分为 $k$ 个集合。
> - $\dfrac{1^{}}{k!}$ 表示去掉标号。  
> $\displaystyle\prod_{i=1}^kf_{a_i}$ 表示每个集合内分别作该种计数。  
> 证毕。


长度为 $n$ 的排列当成置换，可划分为任意个循环置换。  
由于 长度为 $k$ 的排列数 为 $k!$，对应的指数生成函数为 $\dfrac{1}{1-x}$，  
可得 长度为 $k$ 的循环置换数 对应的指数生成函数为 $\ln \dfrac{1}{1-x}=-\ln(1-x)$。  

由于错排要求没有 长度为 $1$ 的循环置换，  
因此 长度为 $k$ 的错排数 对应的指数生成函数为 $e^{-\ln(1-x)-x}$

这个过程没有计算错排中循环置换的数目，考虑从中选若干个：  
$\text{EGF}_x$ 表示以 $x$ 为主元的指数生成函数（$\text{OGF}_x$ 同理），则
$$[x^n]\text{OGF}_x(e^{y\text{EGF}_xf})=\sum_{k}\frac{1}{k!}\sum_{\sum_{i=1}^ka_i=n}\binom{n}{a_1,a_2,\cdots a_k}\prod_{i=1}^kf_{a_i}y$$
$$=\sum_{k}\frac{1}{k!}\sum_{\sum_{i=1}^ka_i=n}\binom{n}{a_1,a_2,\cdots a_k}(\prod_{i=1}^kf_{a_i})y^k$$
因此设 $g(x,y)=e^{y(-\ln(1-x)-x)}$，  
则 $[x^ny^k](\text{OGF}_x g)$ 就是长度为 $n$ 的，可分解为 $k$ 个循环置换的错排数。

----------------------------------
设答案序列为 $ans$，则显然
$$ans_m=\sum_{k=0}^mF(k)[x^my^k](\text{OGF}_x g)
$$
$\qquad\qquad\qquad\displaystyle\frac{ans_m}{m!}=\sum_{k=0}^nF(k)[x^my^k]g(x,y)$（$k>m$ 时，$[x^my^k]g(x,y)=0$）

多点求值求出 $v_k=F(k)$ 。

右边的部分可以看作矩阵乘向量，设 $G_{m,k}=[x^my^k]g(x,y)$，  
则 $\dfrac{ans_m}{m!}=\displaystyle\sum_{k=0}^n G_{m,k}v_k=(G\vec{v})_m$。

因此这是个线性算法，且是个方阵。考虑转置原理：  
### 1. 找出如何计算 $G^T\vec{v}$
$(G^T\vec{v})_m=\displaystyle\sum_{k=0}^n G_{k,m}v_k=\sum_{k=0}^nv_k[x^ky^m]g(x,y)$ 。  
   设 $g(x,y)=\displaystyle\sum_kg_k(y)x^k,$  
$f(y)=\displaystyle\sum_{m=0}^n(G^T\vec{v})_my^m=\sum_{k=0}^nv_k[x^k]g(x,y)=\sum_{k=0}^nv_kg_k(y)$。    
  为找到 $g_k(y)$ 之间的关系，$g(x,y)$ 对 $x$ 求偏导得  
  $$\dfrac{\partial g(x,y)}{\partial x}=g(x,y)y(\dfrac{1}{1-x}-1)$$  
  已知 $[x^{k-1}]\dfrac{\partial g(x,y)}{\partial x}=kg_{k}(y),[x^k]g(x,y)y=g_k(y)y$，则  

$$kg_k(y)=\sum_{i=1}^{k-1}g_{k-1-i}(y)y=\sum_{i=0}^{k-2}g_i(y)y$$

可以用矩阵快速幂来优化 $g_k(y)$ 的计算，  
设 $\vec{u}_k=\begin{pmatrix}g_k(y)&\displaystyle\sum_{i=0}^{k-1}g_i(y)\end{pmatrix}=\vec{u}_{k-1}W_k$，
则 
$$
\vec{u}_0=\begin{pmatrix}
g_0(y)&\displaystyle\sum_{i=0}^{-1}g_i(y)
\end{pmatrix}=\begin{pmatrix}
g(0,y)&0
\end{pmatrix}=\begin{pmatrix}
1&0
\end{pmatrix}$$
$$
W_k=\begin{bmatrix}
0&1\\\dfrac{y}{k}&1
\end{bmatrix},
\vec{u}_k=\vec{u}_0W_1\cdots W_k
$$
将 $\vec{u}_0$ 补全为单位矩阵 $W_0=I=\begin{bmatrix}1&0\\0&1\end{bmatrix}$，

于是 $\begin{bmatrix}f(y)&\cdots\\\cdots&\cdots\end{bmatrix}=\displaystyle\sum_{k=0}^n v_k\begin{bmatrix}\underline{\vec{u}_k}\\\cdots\end{bmatrix}=\sum_{k=0}^nv_kW_0W_1\cdots W_k$

最终可分治 FFT 解决这个问题：  
设 $B_{l,r}=W_lW_{l+1}\cdots W_r,A_{l,r}=\displaystyle\sum_{k=l}^r v_kB_{l,k}$。

设 $l\le mid<r$，则

$$B_{l,r}=B_{l,mid}B_{mid+1,r}$$
$$A_{l,r}=A_{l,mid}+B_{l,mid}A_{mid+1,r}$$

$B_{l,l}=W_l,A_{l,l}=v_lW_l$，计算 $\vec{u_0}A_{0,n}$ 即可。

### 2.将 $G^T\vec{a}$ 化为线性算法的标准形式
设 $A_{l,r}=\begin{bmatrix}\vec{a}_{l,r,0}&\vec{a}_{l,r,1}\\\vec{a}_{l,r,2}&\vec{a}_{l,r,3}\end{bmatrix},B_{l,r}=\begin{bmatrix}\vec{b}_{l,r,0}&\vec{b}_{l,r,1}\\\vec{b}_{l,r,2}&\vec{b}_{l,r,3}\end{bmatrix}$，则过程为

- 自下而上初始化常量（$\times$ 为多项式乘法）：
  - $\vec{b}_{l,l,0}=\dbinom{0}{0},\vec{b}_{l,l,2}=\begin{pmatrix}0\\\dfrac{1}{l}\end{pmatrix},\vec{b}_{l,l,1}=\vec{b}_{l,l,3}=\dbinom{1}{0}$
  - $\vec{b}_{l,r,0}=\vec{b}_{l,mid,0}\times\vec{b}_{mid+1,r,0}+\vec{b}_{l,mid,1}\times\vec{b}_{mid+1,r,2}$  
    $\vec{b}_{l,r,1}=\vec{b}_{l,mid,0}\times\vec{b}_{mid+1,r,1}+\vec{b}_{l,mid,1}\times\vec{b}_{mid+1,r,3}$  
    $\vec{b}_{l,r,2}=\vec{b}_{l,mid,2}\times\vec{b}_{mid+1,r,0}+\vec{b}_{l,mid,3}\times\vec{b}_{mid+1,r,2}$  
    $\vec{b}_{l,r,3}=\vec{b}_{l,mid,2}\times\vec{b}_{mid+1,r,1}+\vec{b}_{l,mid,3}\times\vec{b}_{mid+1,r,3}$
- 初始化向量为 $\begin{pmatrix}\underline{\vec{v}}\\\vec{0}\end{pmatrix},\vec{0}$ 为初始化的内存。
- 赋值（实际为累加）： 
  - $(\vec{a}_{l,l,2})_1\leftarrow(\vec{a}_{l,l,2})_1+\dfrac{1}{l}\times v_l$
  - $(\vec{a}_{l,l,1})_0\leftarrow(\vec{a}_{l,l,1})_0+v_l$
  - $(\vec{a}_{l,l,3})_0\leftarrow(\vec{a}_{l,l,3})_0+v_l$
- 自下而上分治：
  - $\vec{a}_{l,r,0}\leftarrow\vec{a}_{l,r,0}+\vec{a}_{l,mid,0}$（这里只有低位对应位置相加）  
    $\vec{a}_{l,r,0}\leftarrow\vec{a}_{l,r,0}+\vec{b}_{l,mid,0}\times\vec{a}_{mid+1,r,0}$  
    $\vec{a}_{l,r,0}\leftarrow\vec{a}_{l,r,0}+\vec{b}_{l,mid,1}\times\vec{a}_{mid+1,r,2}$
  - $\vec{a}_{l,r,1}\leftarrow\vec{a}_{l,r,1}+\vec{a}_{l,mid,1}$  
    $\vec{a}_{l,r,1}\leftarrow\vec{a}_{l,r,1}+\vec{b}_{l,mid,0}\times\vec{a}_{mid+1,r,1}$  
    $\vec{a}_{l,r,1}\leftarrow\vec{a}_{l,r,1}+\vec{b}_{l,mid,1}\times\vec{a}_{mid+1,r,3}$ 
  - $\vec{a}_{l,r,2}\leftarrow\vec{a}_{l,r,2}+\vec{a}_{l,mid,2}$  
    $\vec{a}_{l,r,2}\leftarrow\vec{a}_{l,r,2}+\vec{b}_{l,mid,2}\times\vec{a}_{mid+1,r,0}$  
    $\vec{a}_{l,r,2}\leftarrow\vec{a}_{l,r,2}+\vec{b}_{l,mid,3}\times\vec{a}_{mid+1,r,2}$ 
  - $\vec{a}_{l,r,3}\leftarrow\vec{a}_{l,r,3}+\vec{a}_{l,mid,3}$  
    $\vec{a}_{l,r,3}\leftarrow\vec{a}_{l,r,3}+\vec{b}_{l,mid,2}\times\vec{a}_{mid+1,r,1}$  
    $\vec{a}_{l,r,3}\leftarrow\vec{a}_{l,r,3}+\vec{b}_{l,mid,3}\times\vec{a}_{mid+1,r,3}$

- 最后赋值（实际为交换）：$\vec{v}\leftrightarrow\vec{a}_{0,n,0}$ 。
- 将辅助变量清零。

### 3. ~~一板一眼地~~转置算法

- 自下而上初始化常量。
- 初始化向量为 $\begin{pmatrix}\underline{\vec{v}}\\\vec{0}\end{pmatrix},\vec{0}$ 为初始化的内存。
- 将辅助变量清零。
- 赋值（实际为交换）： $\vec{a}_{0,n,0}\leftrightarrow\vec{v}$ 。
- 自上而下分治：（$\times^T$ 为转置卷积）
  - $\vec{a}_{mid+1,r,3}\leftarrow\vec{a}_{mid+1,r,3}+\vec{b}_{l,mid,3}\times^T\vec{a}_{l,r,3}$  
    $\vec{a}_{mid+1,r,1}\leftarrow\vec{a}_{mid+1,r,1}+\vec{b}_{l,mid,2}\times^T\vec{a}_{l,r,3}$  
    $\vec{a}_{l,mid,3}\leftarrow\vec{a}_{l,mid,3}+\vec{a}_{l,r,3}$（超出 $\vec{a}_{l,mid,3}$ 长度的部分不要，以下同理）  
  - $\vec{a}_{mid+1,r,2}\leftarrow\vec{a}_{mid+1,r,2}+\vec{b}_{l,mid,3}\times^T\vec{a}_{l,r,2}$  
    $\vec{a}_{mid+1,r,0}\leftarrow\vec{a}_{mid+1,r,0}+\vec{b}_{l,mid,2}\times^T\vec{a}_{l,r,2}$   
    $\vec{a}_{l,mid,1}\leftarrow\vec{a}_{l,mid,1}+\vec{a}_{l,r,2}$  

  -  $\vec{a}_{mid+1,r,3}\leftarrow\vec{a}_{mid+1,r,3}+\vec{b}_{l,mid,1}\times^T\vec{a}_{l,r,1}$  
    $\vec{a}_{mid+1,r,1}\leftarrow\vec{a}_{mid+1,r,1}+\vec{b}_{l,mid,0}\times^T\vec{a}_{l,r,1}$  
     $\vec{a}_{l,mid,1}\leftarrow\vec{a}_{l,mid,1}+\vec{a}_{l,r,1}$   
    
  - $\vec{a}_{mid+1,r,2}\leftarrow\vec{a}_{mid+1,r,2}+\vec{b}_{l,mid,1}\times^T\vec{a}_{l,r,0}$  
    $\vec{a}_{mid+1,r,0}\leftarrow\vec{a}_{mid+1,r,0}+\vec{b}_{l,mid,0}\times^T\vec{a}_{l,r,0}$  
    $\vec{a}_{l,mid,0}\leftarrow\vec{a}_{l,mid,0}+\vec{a}_{l,r,0}$  
- 最后赋值（实际为累加）：
  - $v_l\leftarrow v_l+(\vec{a}_{l,l,3})_0$
  - $v_l\leftarrow v_l+(\vec{a}_{l,l,1})_0$
  - $v_l\leftarrow v_l+\dfrac{1}{l}\times (\vec{a}_{l,l,2})_1$

中间这步实际上等价于：
- $A_{l,mid}\leftarrow A_{l,r}$
- $A_{mid+1,r}\leftarrow B^T_{l,mid}\times^TA_{l,r}$  


显然代码会很丑，就不放了。

# 后记
写了这道题后，对转置原理和生成函数的理解加深了很多。

比如 exp 的组合意义，多元生成函数的技巧、矩阵优化多项式运算等，都是在这道题中学习得到的。

感谢 @GuidingStar 的指导。 

---

## 作者：Aleph1022 (赞：13)

重构一下题解。

考虑先进行多点求值，问题转化为对给定的数列 $F_k$ 和 $1 \le m \le n$，计算
$$
\sum\limits_{|\pi|=m} F_{\mathrm{cyc}_{\pi}}
$$

我们自然考察计算
$$
\sum\limits_k F_k \sum\limits_{|\pi|=m} [\mathrm{cyc}_{\pi}=k]
$$

考虑
$$
\sum\limits_{1 \le |\pi| \le n} z^{|\pi|} t^{\mathrm{cyc}_{\pi}}
$$

根据 Symbolic Methods，显然其即
$$
G(z,t) = \mathrm e^{t(-\ln(1-z)-z)}
$$

考虑实际上我们需要计算
$$
\sum\limits_k F_k [t^k] G(z,t)
$$

首先考虑其转置
$$
\sum\limits_k F_k [z^k] G(z,t)
$$

注意 $G$ 满足微分方程
$$
\frac{\partial G(z,t)}{\partial z} = \frac{zt}{1-z} G(z,t)
$$

令 $G_k = [z^k]G(z,t)$，则其满足
$$
G_k = \frac1k\left[(k-1)G_{k-1}+tG_{k-2}\right]
$$

其转移容易用矩阵描述。那么对原问题的转置的计算方式无非就是考虑分治，同时维护区间内的矩阵连乘积和区间内的矩阵贡献和即可。  
而对于原问题，我们应用**转置原理**将分治过程逐步改写即可。

---

## 作者：Lyrella (赞：1)

# 前言

本篇题解摘自本人的[博客](https://www.cnblogs.com/Lyrella/p/18880723)，里面有 P7438 一直到此题的题解。在此不复述题意。



# 题解

现在要对每个 $n$ 求：
$$
\sum_iF(i)[x^ny^i]e^{y(-\ln(1-x)-x)}
$$
设 $G(x,y)=e^{y(-\ln(1-x)-x)}$。此时考虑转置原理，其实我们要求：
$$
\sum_iF(i)[x^i]G(x,y)
$$
我们现在就需要找 $G$ 的递推式，所以对其求偏导：
$$
{\partial\over\partial x}G(x,y)={x(1+y)\over1-x}G(x,y)
$$
设 $G_i(y)=[x^i]G(x,y)$，现在就可以写出递推式：
$$
G_i={i-1\over i}G_{i-1}+{y\over i}G_{i-2}
$$
且 $G_0=1$。我们可以把递推式写成矩阵的形式：
$$
\begin{bmatrix}
G_i&G_{i-1}
\end{bmatrix}
=
\begin{bmatrix}
G_{i-1}&G_{i-2}
\end{bmatrix}
\begin{bmatrix}
{i-1\over i}&1\\{y\over i}&0
\end{bmatrix}
$$
设转移矩阵
$$
A_i
=
\begin{bmatrix}
{i-1\over i}&1\\{y\over i}&0
\end{bmatrix}
$$
答案就是：
$$
\sum_i\begin{bmatrix}
F(i)&0
\end{bmatrix}\prod_{j=1}^iA_j
$$
对于后面的矩阵乘法我们用分治 FFT 计算，外面的这个东西也可以分治，时间复杂度 $O(n\log^2n+k\log^2k)$。

---

