# [ARC173F] Select and Split

## 题目描述

黑板上写有一个由正整数组成的集合。最初，黑板上写有集合 $S=\lbrace 1,2,\dots,A,A+1,A+2,\dots,A+B\rbrace$。

高桥君希望通过以下操作 $N-1$ 次，将黑板上的集合变为 $N$ 个：

- 从黑板上写着的整数集合中，选择一个集合 $S_0$，该集合中 $A$ 以下和 $A+1$ 及以上的元素各至少有一个。从 $S_0$ 中分别选出一个 $A$ 以下的元素 $a$ 和一个 $A+1$ 及以上的元素 $b$。将 $S_0$ 从黑板上擦去，任意选择两个满足以下条件的集合 $S_1,S_2$ 写到黑板上：
  - $S_1,S_2$ 的并集为 $S_0$，且两者没有公共元素；
  - $a\in S_1,\ b\in S_2$。

请计算所有可能的一系列操作的方案数，答案对 $998244353$ 取模。

注意，如果存在某个 $i\ (1\leq i\leq N-1)$，第 $i$ 次操作所选择的 $S_0,a,b,S_1,S_2$ 中有任意一个不同，则认为这两组操作方案是不同的。

## 说明/提示

### 限制条件

- $2\leq N\leq 2\times 10^5$
- $1\leq A,B\leq 2\times 10^5$
- $N\leq A+B$
- 所有输入均为整数

### 样例解释 1

一种操作方案如下：

- 选择 $S_0=\lbrace 1,2,3,4,5,6\rbrace$，$a=2,b=5$，分成 $S_1=\lbrace 1,2,3,6\rbrace,\ S_2=\lbrace 4,5\rbrace$。此时黑板上有 $\lbrace 1,2,3,6\rbrace,\lbrace 4,5\rbrace$ 两个集合。
- 选择 $S_0=\lbrace 1,2,3,6\rbrace$，$a=1,b=3$，分成 $S_1=\lbrace 1,2\rbrace,\ S_2=\lbrace 3,6\rbrace$。此时黑板上有 $\lbrace 1,2\rbrace,\lbrace 3,6\rbrace,\lbrace 4,5\rbrace$ 三个集合。

### 样例解释 2

如果第一次操作选择 $a=1,b=2$，分成 $S_1=\lbrace 1\rbrace,S_2=\lbrace 2,3,4\rbrace$，则后续无法完成 $N-1$ 次操作。像这样未能完成 $N-1$ 次操作的方案不计入答案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2 4```

### 输出

```
1728```

## 样例 #2

### 输入

```
4 1 3```

### 输出

```
6```

## 样例 #3

### 输入

```
5 6 6```

### 输出

```
84486693```

## 样例 #4

### 输入

```
173173 173173 173173```

### 输出

```
446948086```

# 题解

## 作者：Kevin090228 (赞：5)

# ARC173F - Select and Split

设最终得到的 $n$ 个集合为 $S_1,S_2,\cdots, S_n$，考虑计数达到该最终状态的操作序列个数。事实上 $S_i$ 具体包含的元素不重要，设其包含了 $a_i$ 个前半区元素和 $b_i$ 个后半区元素。

$n-1$ 次操作对应了用 $n-1$ 条边将这 $n$ 个集合连起来。对于一次合并，设其对应了边 $(u,v)$，则该合并钦定 $a,b$ 对应的贡献是 $a_ub_v+a_vb_u$。合并之后的集合再次连边的贡献可以用分配率拆到每个点上，问题变成了求这张图的生成树个数，最后再乘 $(n-1)!$，其中点 $(u,v)$ 之间有 $a_ub_v+a_vb_u$ 条无向边。

同时，确定了 $a_i,b_i$ 之后我们还要计算最终 $S_i$ 的选择方案，容易想到用二元指数型生成函数处理这个贡献。只需要想办法把生成树个数的贡献拆出来即可。

$$
L(G)=D-E=\text{diagonal}\{Ab+Ba\}-ab^T-ba^T
$$

其中，$A=\sum_{i=1}^n a_i,B=\sum_{i=1}^n b_i$，即为题目中给定的 $A,B$。$\text{diagonal}$ 表示将这个向量排列在矩阵的对角线上。生成树个数是 $L(G)$ 的任意一个主子式的值，不妨选择去掉第一行第一列的主子式 $L_1(G)$。

注意到 $\text{rank}(ab^T)=\text{rank}(ba^T)=1$，那么可以将式子拆开：

$$
\det L_1(G)=\prod_{i=2}^{n}(Ab_i+Ba_i)\left(1+\sum_{i=2}^{n}\frac{-2a_ib_i}{Ab_i+Ba_i}+\sum_{2\leq i<j\leq n}\frac{2a_ia_jb_ib_j}{(Ab_i+Ba_i)(Ab_j+Ba_j)}+\sum_{2\leq i<j\leq n}\frac{-a_i^2b_j^2-b_i^2a_j^2}{(Ab_i+Ba_i)(Ab_j+Ba_j)}\right)
$$

分别写出四部分的形式幂级数。

第一部分：

$$
F_1(x,y)=\sum_{a,b\geq 0}\frac{x^ay^b}{a!b!}(Ab+Ba)=Ae^xye^{y}+Be^yxe^x\\W_1=\left[\frac{x^{A}y^B}{A!B!}\right]e^{x+y}F_1^{n-1}(x,y)=\left[\frac{x^{A}y^B}{A!B!}\right]e^{n(x+y)}(Ay+Bx)^{n-1}
$$

这里利用了：$\lang1,1,1,\cdots\rang=e^x,\lang0,1,2,3,\cdots\rang=xe^x$。

第二部分：

$$
F_2(x,y)=\sum_{a,b\geq 0}\frac{x^ay^b}{a!b!}(-2ab)=-2xye^{x+y} \\ W_2=\left[\frac{x^{A}y^B}{A!B!}\right]\binom{n-1}{1}e^{x+y}F_1^{n-2}(x,y)F_2(x,y)=\left[\frac{x^{A}y^B}{A!B!}\right]-2(n-1)e^{n(x+y)}xy(Ay+Bx)^{n-2}
$$

这里 $\binom{n-1}1$ 的系数来源于选择和式中的 $i$。

第三部分：

$$
W_3=\left[\frac{x^{A}y^B}{A!B!}\right]\frac{1}{2}\binom{n-1}{2}e^{x+y}F_1^{n-3}(x,y)F_2^2(x,y)=\left[\frac{x^{A}y^B}{A!B!}\right](n-1)(n-2)e^{n(x+y)}x^2y^2(Ay+Bx)^{n-3}
$$

第四部分：

$$
F_{3}(x,y)=\sum_{a,b\geq0}\frac{x^ay^b}{a!b!}a^2=x(x+1)e^{x+y},F_{4}(x,y)=\sum_{a,b\geq 0}\frac{x^ay^b}{a!b!}b^2=y(y+1)e^{x+y}\\ W_4=-\left[\frac{x^{A}y^B}{A!B!}\right]\binom{n}{2}2!e^{x+y}F_1^{n-3}(x,y)F_{3}(x,y)F_4(x,y)=-\left[\frac{x^{A}y^B}{A!B!}\right](n-1)(n-2)xy(x+1)(y+1)e^{n(x+y)}(Ay+Bx)^{n-3}
$$

这里利用了：$\lang0,1,4,9,\cdots\rang=x(x+1)e^x$。

确定选择树边的方案有 $(n-1)!$ 种方式，但是最终的 $S_1,S_2,\cdots ,S_n$ 应该是无序的，所以还要除掉 $n!$，最终答案为：

$$
\frac{1}{n}(W_1+W_2+W_3+W_4)
$$

对于 $W_1,W_2,W_3,W_4$ 的求值，可将其转化为求 $e^{n(x+y)}(Ay+Bx)^{k}$ 的 $x^py^q$ 项系数，暴力展开 $(Ay+Bx)^k$ 之后用组合数求 $e^{n(x+y)}$ 的单处系数是简单的。时间复杂度 $O(n)$。

---

## 作者：strapplE (赞：2)

### 长文警告！！发现笔者哪里写错了请直接提出，可以来 D 笔者！

趣题。似乎想清楚了还好，不算特别困难。讲一下题解做法。

把操作倒过来，实际上每次选择 $(S_0,a,b,S_1,S_2)$ 就是在目前的极大连通分支中选择两个，并选择其中的两个点 $a,b$，进行合并，形成 $S_0$。而 $a,b$ 要满足 $a\leq A,b\gt A$。那么就相当于我们把 $a$ 和 $b$ 之间连一条边。

容易发现，如果你知道了你要连哪些边，那么选边连接的顺序是不会影响的，所以可以直接最后乘上一个 $(n-1)!$。考虑 $n=A+B-1$ 的情况，答案就是一个左部点有 $A$ 个，右部点有 $B$ 个的完全二分图的生成树数量。

而 $n<A+B-1$ 时，你其实最开始就有 $n$ 个连通分支（或者就是集合），设第 $i$ 个集合有 $a_i$ 个左部点和 $b_i$ 个右部点。则我们选择第 $i$ 个集合和第 $j$ 个集合合并的方案数就是 $a_ib_j+a_jb_i$。方案数就是这 $n$ 个点构成的图的生成树个数。

当然，$a_i$ 和 $b_i$ 不是固定的，由于这些集合之间没有顺序，所以选择的方案数就是：

$$\dfrac{1}{n!}\binom{A}{a_1,a_2,\dots,a_n}\binom{B}{b_1,b_2,\dots,b_n}=\dfrac{A!B!}{n!}\prod\limits_{i=1}^{n}\dfrac{1}{a_i!b_i!}$$

当然，还有行列式的部分。由于自环不影响，所以可不妨认为 $i$ 与自己有 $a_ib_i+a_ib_i$ 条边，所以由矩阵树定理，得到的矩阵 $M$ 的第 $i$ 行 $j$ 列的值 $m_{i,j}$ 形如：

$$[i=j](a_iB+b_iA)-(a_ib_j+a_jb_i)$$

所以，乘上最开始的 $(n-1)!$，然后矩阵树定理去除掉第 $1$ 行 $1$ 列，答案就是：

$$\dfrac{A!B!}{n}\cdot \sum\limits_{\sum a_i=A,\sum b_i=B}(\prod\limits_{i=1}^{n}\dfrac{1}{a_i!b_i!})\cdot\det(\operatorname{diag}(a_2B+b_2A,\dots,a_nB+b_nA)-a^\text{T}b-b^\text{T}a)$$

其中 $\operatorname{diag}(c_1,c_2,\dots,c_n)$ 为 $c_i$ 从左上到右下对应构成的对角阵，$a$ 为列向量 $(a_2,a_3,\dots,a_n)$，$b$ 同理。

接下来考虑这个行列式怎么求。由降阶公式（Schur 补定理），即对角阵 $D$（本题中为那个 $\operatorname{diag}(...)$）加减一个秩为 $r$ 的矩阵的行列式（本题中为 $ba^\text{T}+ab^\text{T}$），可以转成一个 $r\times r$ 的矩阵的行列式。也就是说：

$$
\begin{vmatrix}
D-ba^\text{T}-ab^\text{T} & 0 & 0\\
a^\text{T} & 1 & 0\\
b^\text{T} & 0 & 1
\end{vmatrix}=
\begin{vmatrix}
D & b & a\\
a^\text{T} & 1 & 0\\
b^\text{T} & 0 & 1
\end{vmatrix}=
\begin{vmatrix}
D & b & a\\
0 & 1-a^\text{T}D^{-1}b & -a^\text{T}D^{-1}a\\
0 & -b^\text{T}D^{-1}b & 1-b^\text{T}D^{-1}a
\end{vmatrix}
$$

这里提一嘴笔者关于降阶公式的一些看法：降阶公式是一个求行列式非常非常有用的东西（新领军也考过好几次），不过 OI 中经常只能看见降阶成 $1\times 1$ 的例子，实际上 $2\times 2$ 的也很有用，一个很好的例题就是[本题](https://atcoder.jp/contests/arc173/tasks/arc173_f)。

因为 $D^\text{T}=D$，所以那个右下角的矩阵实际就等于：

$$(1-a^\text{T}D^{-1}b)^2-(a^\text{T}D^{-1}a)(b^\text{T}D^{-1}b)=1-2\sum(\dfrac{a_ib_i}{a_iB+b_iA})+\sum(\dfrac{a_ib_ia_jb_j}{(a_iB+b_iA)(a_jB+b_jA)})-\sum(\dfrac{a_i^2b_j^2}{(a_iB+b_iA)(a_jB+b_jA)})$$

二次的部分展开式实际可以消掉 $i=j$ 的值。再乘上 $D$ 本身的行列式，因此，本题的答案就等于：

$$\dfrac{A!B!}{n}\cdot\sum\limits_{\sum a_i=A,\sum b_i=B}\dfrac{1}{a_1!b_1!}(\prod\limits_{i=2}^{n}(\dfrac{a_iB+b_iA}{a_i!b_i!}))\cdot(1-2\sum\limits_{i=2}^{n}(\dfrac{a_ib_i}{a_iB+b_iA})+\sum\limits_{2\leq i\neq j\leq n}(\dfrac{a_ib_ia_jb_j}{(a_iB+b_iA)(a_jB+b_jA)})-\sum\limits_{2\leq i\neq j\leq n}(\dfrac{a_i^2b_j^2}{(a_iB+b_iA)(a_jB+b_jA)}))$$

接下来，就要邀请 GF 登场了！

一个平凡的引理：

$P(n_1,n_2,\dots,n_k)$ 是一个关于 $n_1,\dots,n_k$ 的多项式，把它表示成下降幂多项式后的系数构成的多项式（即，关于每个参数先表示成下降幂多项式，再把系数乘起来构成一些小多项式，再同类项合并）为 $Q(n_1,n_2,\dots,n_k)$，则：

$$\sum\limits_{n_1,n_2,\dots,n_k\geq 0}\dfrac{P(n_1,n_2,\dots,n_k)}{n_1!n_2!\dots n_k!}{x_1}^{n_1}{x_2}^{n_2}\dots{x_k}^{n_k}=Q(x_1,x_2,\dots,x_k)e^{x_1+x_2+\dots+x_k}$$

我们把求和式展开，之后就全都是乘积，所以 GF 是好求的。

设 $x$ 和 $y$ 是两个变量，$n$ 和 $m$ 是它们对应的次数，则由引理知：

$\dfrac{1}{n!m!}$ 的 OGF 是 $e^{x+y}$；$\dfrac{Bn+Am}{n!m!}$ 的 OGF 是 $(Bx+Ay)e^{x+y}$；$\dfrac{nm}{n!m!}$ 的 OGF 是 $xye^{x+y}$；$\dfrac{n^2m^2}{n!m!}$ 的 OGF 是 $(x^2+x)(y^2+y)e^{x+y}$。

然后通过对称性和简单的计算，可以得到答案为：

$$\dfrac{A!B!}{n}[x^Ay^B](e^{n(x+y)}\cdot ((Bx+Ay)^{n-1}-2(n-1)xy(Bx+Ay)^{n-2}-(n-1)(n-2)(x^2y+xy^2+xy)(Bx+Ay)^{n-3}))$$

这相当于我们只需求出 $[x^ay^b]((Bx+Ay)^{m}e^{n(x+y)})$ 状物，枚举左边选择的次数得到一个系数，右边会对应有一个系数，加起来就可以了。

时间复杂度是 $\Theta((A+B)\log(A+B))$，也可以通过预处理做到 $\Theta(A+B)$。

放个本人的代码地址：[here](https://atcoder.jp/contests/arc173/submissions/51147441)。

---

## 作者：WrongAnswer_90 (赞：0)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18391786)

### [[ARC173F] Select and Split](https://www.luogu.com.cn/problem/AT_arc173_f)

~~在 Kevin 题解的基础上解释了一下~~。分裂这个过程感觉很不自然，考虑倒过来做合并。

经过简单的观察，可以发现一个集合的属性只和在 $[1,A]$ 内的元素个数和 $[A+1,A+B]$ 内的元素个数有关，分别设其为 $a_i,b_i$。

合并两个点的方案数是 $a_ib_j+a_jb_i$。合并两个集合 $S,T$ 的方案数可以看成从 $S,T$ 两个集合内各自任选一个点合并，拆到每个点的贡献上，即：

$$
\sum_{i\in S}a_i\sum_{j\in T}b_j=\sum_{i\in S}\sum_{j\in T}a_ib_j
$$

所以可以建图，$i,j$ 之间连 $a_ib_j+a_jb_i$ 条边，这样这个图的生成树个数就是合并的方案数。操作顺序的影响是平凡的，可以最后乘一个 $(n-1)!$ 解决。

因为数字是有标号，而有标号问题可以想到用二元指数型生成函数解决。所以现在只需要把有了 $a_i,b_i$ 之后，合并的方案数比较简单的表示出来。根据矩阵树定理，设 $L_{i,j}=[i=j](Ab_j+Ba_i),X_{i,j}=a_ib_j,Y_{i,j}=a_ib_j$，其中 $i,j>1$，则 $\det(L-X-Y)$ 即为答案。可以发现这个矩阵的形式比较简单（好像是对角矩阵加上若干个秩为 $1$ 的矩阵都可以这么做？），考虑降阶公式（太神奇了！），新设一个矩阵：

$$
\begin{vmatrix}
 
 L-X-Y & 0 & 0\\
 b & 1 & 0\\
 a & 0 & 1
\end{vmatrix}
$$

其中 $L-X-Y$ 是矩阵，$a,b$ 是行向量，第一排的两个 $0$ 都是空的列向量。容易发现该矩阵的行列式和 $G$ 相同。可以把 $a,b$ 都对应位相减到 $L-X-Y$ 上，于是有：

$$
\begin{vmatrix}
 L-X-Y & 0 & 0\\
 b & 1 & 0\\
 a & 0 & 1
\end{vmatrix}
=
\begin{vmatrix}
 L & a^T & b^T\\
 b & 1 & 0\\
 a & 0 & 1
\end{vmatrix}
$$

其中 $a^T,b^T$ 是列向量。因为 $L$ 是对角矩阵，所以可以直接消元：

$$
\begin{vmatrix}
 L & a^T & b^T\\
 b & 1 & 0\\
 a & 0 & 1
\end{vmatrix}
=
\begin{vmatrix}
 L & a^T & b^T\\
 0 & 1-\sum \frac{a_ib_i}{a_iB+b_iA} & -\sum \frac {b_i^2}{a_iB+b_iA}\\
 0 & -\sum \frac{a_i^2}{a_iB+b_iA} & 1-\sum \frac{a_ib_i}{a_iB+b_iA}
\end{vmatrix}
$$

然后分类讨论一下，就可以得到行列式为：

$$
\prod_i v_i(1-2\sum_{i}\frac{a_ib_i}{v_i}+\sum_{i,j}\frac{a_ia_jb_ib_j}{v_iv_j}-\sum_{i,j}\frac{a_i^2b_j^2}{v_iv_j})
$$

其中 $v_i=a_iB+b_iA$。其实后面的部分就相对比较平凡了。写出四个部分的指数型生成函数：

$$
\begin{aligned}
F_1(x,y)&=\sum_{i,j\geq 0}\frac{x^iy^j}{i!j!}(Aj+Bi)\\&=Ae^xye^y+Bxe^xe^y\\&=e^{x+y}(Ay+Bx)\\
W_1&=[x^Ay^B]e^xe^yF_1^{n-1}(x,y)\\
&=[x^Ay^B]e^{n(x+y)}(Ay+Bx)^{n-1}
\end{aligned}
$$

因为 $xe^x=\sum_{i\geq 1}i\frac{x^i}{i!}$。第二个式子中乘 $e^{x+y}$ 是因为需要统计第一个集合（计算行列式时删掉了）的贡献。

$$
\begin{aligned}
F_2(x,y)&=\sum_{i,j\geq 0}\frac{x^iy^j}{i!j!}ij=xye^{x+y}\\
W_2&=-2(n-1)[x^Ay^B]e^{x+y}F_2(x,y)F_1^{n-2}(x,y)\\&=-2(n-1)[x^Ay^B]e^{n(x+y)}xy(Ay+Bx)^{n-2}
\end{aligned}
$$

$n-1$ 是因为选一个做 $a_ib_i$ 的贡献，其余的做 $Ab_i+Ba_i$ 的贡献。

对于第三第四部分，可以发现如果 $i=j$ 则两部分的贡献抵消了，所以可以删去的 $i=j$（其实只是为了简单一点）。

$$
\begin{aligned}
W_3&=(n-1)^{\underline2}[x^Ay^B]e^{x+y}F_2^2(x,y)F_1^{n-3}(x,y)\\&=(n-1)^{\underline2}[x^Ay^B]e^{n(x+y)}x^2y^2(Ay+Bx)^{n-3}
\end{aligned}
$$

因为 $i,j$ 和 $j,i$ 都要贡献，所以是 $(n-1)^{\underline2}$ 而不是 $\binom{n-1}{2}$。

$$
\begin{aligned}
F_3(x,y)&=\sum_{i,j\geq 0}\frac{x^iy^j}{i!j!}i^2=e^y\sum_{i\geq 0}\frac{x^i}{i!}(i^{\underline 2}+i^{\underline 1})\\
&=e^y(x^2e^x+xe^x)=x(x+1)e^{x+y}\\
F_4(x,y)&=y(y+1)e^{x+y}\\
W_4&=-(n-1)^{\underline2}[x^Ay^B]e^{x+y}F_3(x,y)F_4(x,y)F_1^{n-3}(x,y)\\
&=-(n-1)^{\underline2}[x^Ay^B](Ay+Bx)^{n-3}xy(x+1)(y+1)e^{n(x+y)}\\
\end{aligned}
$$

使用了 $x^te^x=\sum_{i\geq t}i^{\underline t}\frac{x^i}{i!}$。最终答案即为 $\frac{(n-1)!}{n!}A!B!(W_1+W_2+W_3+W_4)$，$(n-1)!$ 是确定操作顺序，$n!$ 是消除集合之间的顺序。可以用组合数把除了 $e^{n(x+y)}$ 以外的部分展开然后 $\mathcal O(n)$ 算。

```cpp
int n,A,B,W1,W2,W3,W4,fr[600010],inv[600010],f[600010],pwa[600010],pwb[600010],pwn[600010];
inline int C(int n,int m){return m<0||m>n?0:Cmul(fr[n],inv[m],inv[n-m]);}
inline void mian()
{
	read(n,A,B),fr[0]=inv[0]=pwa[0]=pwb[0]=pwn[0]=1;
	for(int i=1;i<=600000;++i)
	{
		fr[i]=Cmul(fr[i-1],i),pwa[i]=Cmul(pwa[i-1],A);
		pwb[i]=Cmul(pwb[i-1],B),pwn[i]=Cmul(pwn[i-1],n);
	}
	inv[600000]=power(fr[600000],MOD-2);
	for(int i=599999;i>0;--i)inv[i]=Cmul(inv[i+1],i+1);
	for(int i=0;i<=n-1&&i<=A;++i)if(n-1-i<=B)
	Madd(W1,Cmul(pwn[A-i],pwn[B-(n-1-i)],inv[A-i],inv[B-(n-1-i)],C(n-1,i),pwb[i],pwa[n-1-i]));
	for(int i=0;i<=n-2&&i+1<=A;++i)if(n-2-i+1<=B)
	Madd(W2,Cmul(pwn[A-1-i],pwn[B-1-(n-2-i)],inv[A-1-i],inv[B-1-(n-2-i)],C(n-2,i),pwb[i],pwa[n-2-i]));
	Mmul(W2,2,n-1);
	for(int i=0;i<=n-3&&i+2<=A;++i)if(n-3-i+2<=B)
	Madd(W3,Cmul(pwn[A-2-i],pwn[B-2-(n-3-i)],inv[A-2-i],inv[B-2-(n-3-i)],C(n-3,i),pwb[i],pwa[n-3-i]));
	Mmul(W3,n-2,n-1);
	for(int i=0;i<=n-3&&i+1<=A;++i)if(n-3-i+1<=B)
	for(int j=0;j<2&&j+i+1<=A;++j)for(int k=0;k<2&&k+n-3-i+1<=B;++k)
	Madd(W4,Cmul(pwn[A-1-j-i],pwn[B-1-k-(n-3-i)],inv[A-1-j-i],inv[B-1-k-(n-3-i)],C(n-3,i),pwb[i],pwa[n-3-i]));
	Mmul(W4,n-2,n-1);
	write(Cmul(power(n,MOD-2),fr[A],fr[B],Cdel(Cadd(W1,W3),Cadd(W2,W4))));
}
```

---

