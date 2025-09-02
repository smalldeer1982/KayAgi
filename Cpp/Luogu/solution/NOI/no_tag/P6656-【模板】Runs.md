# 【模板】Runs

## 题目描述

定义一个字符串 $|S|$ 里的一个 run，指其内部一段两侧都不能扩展的**周期子串**，且周期至少完整出现两次。

严格地说，一个 run 是一个 三元组 $(i,j,p)$，满足 $p$ 是 $S[i..j]$ 的最小周期，$j-i+1 \ge 2p$，且满足如下两个条件：

+ 要么 $i=1$，要么 $S[i-1]\ne S[i-1+p]$；
+ 要么 $j=n$，要么 $S[j+1] \ne S[j+1-p]$。

给定字符串 $S$，求他的所有 runs。



## 说明/提示

对于 $60\%$ 的数据，$|S| \le 2 \times 10^5$。

对于 $100\%$ 的数据，$|S| \le 10^6$。


## 样例 #1

### 输入

```
aababaababb```

### 输出

```
7
1 2 1
1 10 5
2 6 2
4 9 3
6 7 1
7 10 2
10 11 1```

# 题解

## 作者：zghtyarecrenj (赞：96)

# 【模板】Runs 题解

By zghtyarecrenj

本文包括：Lyndon Words & Lyndon Array & Runs & Three Squares Lemma。

**禁止转载全文**，转载部分需要注明出处。

实在太长，已尽量删减（

哇，你古md排版是不是出了点问题

Lyndon tree 是一个非常有趣的东西，但是我现在还没有发现应用，所以先咕着。

前言：Lyndon 相关知识是大毒瘤。

## 0 Marks & Facts

1. 我们定义两个字符串 $a$ 和 $b$，如果 $a$ 的字典序 $<b$，则我们称 $a < b$。
2. 如果 $a$ 是 $b$ 的前缀且 $a \ne b$，则我们称 $a \sqsubset b$。
3. 如果 $a$ 是 $b$ 的前缀，则我们称 $a \sqsubseteq b$。
4. 如果 $a < b$ 且 $a$ 不是 $b$ 的前缀，则我们称 $a \triangleleft b$。即 $a \triangleleft b \Longleftrightarrow (a < b) \wedge (a \not\sqsubseteq b)$。Fact：如果 $a \triangleleft b$，则 ${au} < {bv}$。
5. ${abc}$ 表示拼接 $a, b, c$ 三个字符串。
6. $a^n$ 表示 $n$ 个 $a$ 拼接在一起。e.g. ${a^2b} = {aab}$
7. $\epsilon$ 表示空串。
8. 我们定义字符集为 $\Sigma$，组成的字符串为 $\Sigma^*$，$\Sigma^+ = \Sigma^* \setminus \{\epsilon\}$
9. $\operatorname{pref}(a)$ 表示所有 $a$ 的前缀的集合，$\operatorname{suf}(a)$ 表示所有 $a$ 的后缀的集合（包含 $a$ 和 $\epsilon$）
10. $\operatorname{pref}^+(a) = \operatorname{pref}(a) \setminus \{a,\epsilon\},\ \operatorname{suf}^+(a) = \operatorname{suf}^+(a) \setminus \{a, \epsilon\}$
11. 若无特殊定义，字符串 $s$ 是从 $0$ 开始。
12. $|s|$ 表示 $s$ 的长度，$s[i..j]$ 表示 $s$ 的一个子串，第一个字符的标号为 $i$，最后一个字符的标号为 $j$。
13. $\hat{w}=w\$ $，其中 $\$ $ 是一个比字符集里面任何数小的字符。

## 1 Lyndon Words

### 1.1 Definition

**Lyndon Word**：一个串是一个 **Lyndon Word** 当且仅当 $\forall a$ 的后缀 $b$，有 $a < b$。

还有一个定义：对于一个 $n$ 的串有 $n$ 个循环同构，则其中严格最小的那个是一个 Lyndon Word。

比如：$\text{ab}$ 是一个 Lyndon Word，但是 $\text{ba}$ 不是。

$\mathcal L$ 表示 Lyndon Word 的集合。

### 1.2 Chan-Fox-Lyndon Factorization

又称 Lyndon Decomposition。

我们定义 $\operatorname{CFL}(s)$ 是一个对于 $s$ 串的划分，即划分成了 ${w_1w_2\cdots w_k} = s$，使得所有 $w_i$ 是 Lyndon Word，并且 $w_1 \ge w_2 \ge \cdots \ge w_n$。

比如：串 $\text{bbababaabaaabaaaab}$ 的 Lyndon 分解是 $\color{blue}\text{b}\color{red}\text{b}\color{blue}\text{ab}\color{red}\text{ab}\color{blue}\text{aab}\color{red}\text{aaab}\color{blue}\text{aaaab}$。

#### Theory 1.2.1 Lyndon Concatanation

这是一个很显然的结论。

> 如果 $a, b \in \mathcal L$，且 $a < b$，则 $ {ab} \in \mathcal L$。

由于 $a < b$，我们有 ${ab} < b$。接下来我们分两种情况讨论。

1) 当 $a \not \sqsubseteq b$ 时：根据 $a < b$，我们有 $a \triangleleft b$。所以 ${ab} \triangleleft b \implies {ab} < b$。

2) 当 $a \sqsubseteq b$ 时：令 $b={ac}$，则 ${ab} = {a^2c}$。因为 $b \in \mathcal L$，所以 ${ab} < b \implies {a^2c} < {ac} \implies {ac} < c$，所以 $b < c$。

所以，$\forall d \in \operatorname{suf}^+(b), \ {ab} < b < d \implies \forall c \in \operatorname{suf}^+(a),\ a \triangleleft e \implies {ab} \triangleleft {eb}$。$\blacksquare$

#### Theory 1.2.2 Existence of CFL

这个结论和 **[Theory 1.2.3] Uniqueness of CFL** 是两个很有趣的结论。

> 对于任意的串 $s$，$\operatorname{CFL}(s)$ 一定存在。

构造法。我们考虑，单个的字母一定是 Lyndon Word。

根据 **[Theory 1.2.1 Lyndon Concatanation]**，我们可以把字典序小的两个 Lyndon Word 并起来，所以我们把所有的字典序单增的序列都并起来，剩下的就是一个合法的 CFL。$\blacksquare$

#### Theory 1.2.3 Uniqueness of CFL

> 对于任意的串 $s$，$\operatorname{CFL}(s)$ 一定唯一。

反证法，假设有两种方案。我们考虑第一个不同的位置的情况，可以很容易地得到矛盾，和 CFL 的定义矛盾。$\blacksquare$

然后我们就得到了 **CFL 存在且唯一**。由此有两个推论：

#### Theory 1.2.4 Lyndon Suffixes and Lyndon Prefixes

> $w_1$ 是最长的 Lyndon 前缀且 $w_k$ 是最长的 Lyndon 后缀。

反证法。因为如果 $w_1$ 不是最长，那么还能再拼，产生了两个合法的 CFL，和 **[Theory 1.2.3 Uniqueness of CFL]** 矛盾。所以 $w_1$ 是最长的 Lyndon 前缀。

$w_k$ 同理。$\blacksquare$

#### Theory 1.2.5 Theory of Minsuf

> 一个字符串 $s$ 的最小后缀是 $w_k$。

首先，我们有这样的一个 CFL：

![Pic1](https://zght.gitee.io/pic/pics/Pic1.jpg)

首先，我们记 $w_n$ 的起始位置为 $pos$，则显然

![这个位置是不可能的](https://zght.gitee.io/pic/pics/Pic2.jpg)

如图，最小后缀的其实位置不可能 $>pos$，因为根据 Lyndon Word 的定义，$w_n$ 的每个后缀都大于他自身。

接下来我们考虑最小后缀在另一个位置的情况，即他在另一个 $w_i$ 之中

![这个位置也是不行的](https://zght.gitee.io/pic/pics/Pic3.jpg)

根据 $w_i \ge w_{i+1}\ge \cdots \ge w_n$，而 $w_i$ 的一个后缀 $> w_i$，所以这个后缀大于 $w_n$。

所以唯一可能的最小后缀就是 $w_n$。

简单来说，假设最小后缀是 ${xw_{i+1}w_{i+2}\cdots w_{k}}$ 而不是 $w_k$ 且 $|x| < |w_i|$。我们有 ${x w_{i + 1} \dots w_k} \geq x > w_i \ge w_k$，矛盾。$\blacksquare$

### 1.3 Duval's Algorithm

就是求出 CFL 的算法啦~

我们有一个非常优美的算法

有一个言简意赅、一看就懂的描述

> $ {uav} \in \mathcal{L}$，$u,v,h \in \Sigma^*$，$a<b\in\Sigma$，$k\ge1$
>
> 1. ${(uav)^k ub} \in \mathcal{L}$
> 2. $\operatorname{CFL}({(ubv)^k uah}) = {(ubv)^k} \operatorname{CFL}({uah})$
> 3. $\operatorname{CFL}({(uv)^k u}) = {(uv)^k} \operatorname{CFL}(u)$

换成代码实现就是：

我们需要维护两个部分：$ubv$ 和 $u$。

简单来说，就是如果可以拼到当前的串的末尾就拼上去，否则就是一个新的 Lyndon Word。（如果碰到一个比当前的小的东西，则我们更新 $ubv$，否则我们就更新 $u$）。

如果还是不太懂可以移步 oi-wiki，那里写的比较详细。

模拟即可，显然空间复杂度 $\mathcal O(1)$。接下来证明一下时间复杂度。

接下来证明一下复杂度为什么是对的。

最优情况为一个分解走到底，$\mathcal O(n)$。

最坏情况为不停地在重新找，由于至多回退 $n$ 次，每次回退的距离不超过前进的距离，所以是 $\mathcal O(n)$。

## 2 Significant Suffixes

这里不太用到，需要的去 [ZJOI2017 字符串 题解](https://www.luogu.com.cn/blog/orz-you-all/solution-p5211) 看吧。

## 3 Lyndon Array

### 3.1 Definition

我们有一个字符串 $s$，则

**Lyndon Array**：$\mathcal L[i] = \max \{j : s_i \cdots s_{j-1} \in L\}$，其中 $L$ 表示 Lyndon 串的集合。在 $\prec_l$ 意义下的 $\mathcal L$ 记为 $\mathcal L_l$。

这有啥子用？别急，先看性质。

### 3.2 Non Intersecting Substrings

#### Theory 3.2.1 Non Intersecting Lyndon Substrings

> 最长的 Lyndon 子串是无交集的，即 $i < j < \mathcal L[i]$，我们有 $\mathcal L[j] \le \mathcal L[i]$。

我们假设存在 $i,j$ 使得 $\mathcal L[i] < \mathcal L[j]$。

我们假设 $u = s_i \cdots s_{j-1}$，$v = s_j \cdots s_{\mathcal L[i] - 1}$，$w = s_{\mathcal L[i]} \cdots s_{\mathcal L[j] - 1}$，且 $u,v,w$ 满足 ${uv}, {vw} \in L$。

对于所有的 $s \in \operatorname{suf}^+({uvw})$，且满足 $|s| \le |v| + |w|$，有 $s \triangleleft {vw} \sqsupseteq v \triangleleft {uv}$。$\implies {uvw} \triangleleft s$。

对于所有的 $s \in \operatorname{suf}^+({uvw})$，且满足 $|s| > |v| + |w|$，有 ${svw} \sqsupseteq {sv} \triangleleft {uv}$。$\implies {uvw} \triangleleft {svw}$。

所以 ${uvw} \in L$，矛盾。$\blacksquare$

### 3.3 Suffix & Lyndon Arrays

我们设 $\operatorname{suf}(i) = s_i \cdots s_{n-1}$，即一个后缀。

而我们有 $s_i \cdots s_{\mathcal L[i] - 1} \triangleleft s_j \cdots s_{\mathcal L[i] - 1}$。

$\implies \operatorname{suf}(i) \triangleleft \operatorname{suf}(j)\quad(i<j<\mathcal L[i])$

于是我们设
$$
\operatorname{NSV}(i) = \min\{\{j > i : \neg(\operatorname{suf}(i) \triangleleft \operatorname{suf}(j))\} \cup \{n\}\}
$$

显然 $\mathcal L[i] \le \operatorname {NSV}(i)$。

我们还有 $\neg(\operatorname{suf}(i) \triangleleft \operatorname{suf}(j)) \Longleftrightarrow \operatorname{suf}(j) \sqsubseteq \operatorname{suf}(i) \vee \operatorname{suf}(j) \triangleleft \operatorname{suf}(i) \Longleftrightarrow \operatorname{rank}(i) > \operatorname{rank}(j)$。

#### Theory 3.3.1 NSV Theory

有了上述定义，证这个是不是非常简单呢 XD

> $\mathcal L[i] = \operatorname{NSV}(i)$

原命题可以很方便地转化为 $s_i \cdots s_{\operatorname{NSV}(i) - 1} \in L$。

分类讨论：

1. 如果 $\operatorname{NSV}(i) = n$，$s_i \cdots s_{\operatorname{NSV}(i) - 1} = \operatorname{suf}(i)$ 

2. 否则的话我们肯定有一些 $j$ 使得 $\operatorname{suf}(i) \triangleleft \operatorname{suf}(j)$。

   然后我们继续来讨论：

   i) 如果 $s_1 \cdot s_{\operatorname{NSV}(i) - 1} \triangleleft s_{j} \cdots s_{\operatorname{NSV}(i) - 1}$，易证。

   ii) 反之，结合 $\operatorname{suf}(i + (\operatorname{NSV}(i) - j) - 1) \triangleright \operatorname{suf}(i)>\operatorname{suf}(\operatorname{NSV}(i))$，易证矛盾。（你看不出来？明显与 $\operatorname{suf}(i) \triangleright \operatorname{suf}(j)$ 矛盾）。$\blacksquare$

## 4 Runs

### 4.1 Definition

这个东西的英文名是 runs，他的中文名是顶天立地串……（好中二啊）

我们有一个串，runs 是他的一些子串，满足：

$p = \operatorname{per}(s_i\cdots s_{j-1})\le \dfrac {j-i}2$，$s_{i-1} \ne s_{i-1}+p$，$s_{j-p}=s_{j}$

更好理解的定义：

定义一个字符串 $|S|$ 里的一个 run，指其内部一段两侧都不能扩展的**周期子串**，且周期至少完整出现两次。

严格地说，一个 run 是一个 三元组 $(i,j,p)$，满足 $p$ 是 $S[i..j]$ 的最小周期，$j-i+1 \ge 2p$，且满足如下两个条件：

+ 要么 $i=1$，要么 $S[i-1]\ne S[i-1+p]$；
+ 要么 $j=n$，要么 $S[j+1] \ne S[j+1-p]$。

例如：$S = \text{aababaababb}$ 之中有 7 个 runs：$S[1..2] = \text a^2$，$S[1..10] = (\text{aabab})^2$，$S[2..6] = (\text{ab})^{2.5}$，$S[4..9] = (\text{aba})^2$，$S[6..7] = \text a^2$，$S[7..10] = (\text{ab})^2$，$S[10..11] = \text b^2$。

（实际上是 LOJ #173 的题面，题目是我造的，这一段是 EtoainWu 的文字）

定义 $Runs(w)$ 表示字符串 $w$ 的所有 runs 的集合。

$\rho(n)$ 表示了在一个长为 $n$ 的字符串之中至多有多少组 runs，而 $\sigma(n)$ 表示了在一个长为 $n$ 的字符串之中所有 runs 的幂之和的最大值。

**Lyndon Root**：令 $r=(i,j,p)$ 是一个run，则他的 Lyndon Root 是一个 $s[i..j]$ 的长度为 $p$ 的 Lyndon 子串。

每一个 run 都有一个 Lyndon root。

### 4.2 Linear Runs

#### Theory 4.2.1 Linear Runs Theory

我们假设 $\prec^0$ 表示 $<$，而 $\prec^1$ 表示 $<^R$。（此处的 $^R$ 表示 reverse，给 $\prec$ 标号是为了方便）

$\prec^0$ 和 $\prec^1$ 的对应的 Lyndon Array 是 $\mathcal L^0$ 和 $\mathcal L^1$.

> $\rho(n) \le 2n$

原命题可以转化为

> 对于每个 runs，我们有存在 $i$ 和 $t$ 使得 $s[i..\mathcal L^t[i] - 1]$ 是 Lyndon root。

我们令 $w$ 是 Lyndon root，$w=s[k..s-1]$。

分类讨论：

1. 如果 $j=|S|$，

   我们可以把 $s[k .. |S| - 1]$ 表示成 ${w^pw'} \ (p \in N, w' \in \operatorname{pref}(w))$。

   因为 $\operatorname{CFL}({w^pw'}) = {w^p\operatorname{CFL}(w')}$，所以 $w$ 是从 $k$ 开始的最长 Lyndon 前缀。

2. 如果 $j<|S|$，

   我们可以把 $w$ 表示成 ${uab}$，其中 $a \ne b$。

   所以我们可以把 $s_k \cdots s_{|S| - 1}$ 表示成为 ${(uav)^pub}$。

   我们不妨假设 $b \prec^t a$、

   因为我们有 $\operatorname{CFL}^t({(uav)^pubh}) = (uav)^p\operatorname{CFL}^t({ubh})$，所以 ${uav}$ 是 $\prec^t$ 下的最长 Lyndon 前缀。$\blacksquare$

#### Theory 4.2.2 The "Runs" Theory

> $\rho(n)<n,\sigma(n)\leq3n-3$

~~几乎从 WC2019 课件搬运的证明~~

定义 $Beg(I)$ 表示 $I$ 中所有区间的起始端点的集合。

##### Lemma A

> 对于一个串的 Lyndon Array $\mathcal L^0[i]$ 和 $\mathcal L^1[i]$，总有 $\mathcal L^{l}[i] = [i..i], \mathcal L^{1-l}[i] = [i..j] (j\ne i)$，其中 $l\in \{0,1\}$。

令 $k=\max\{k'\ |\hat{w}_{k'}\ne \hat{w}_i,k'>i\}$。

由 **[Theory 1.2.1 Lyndon Concatanation]** 可得：

+ 若 $\hat w_k < \hat w_i$，则 $\mathcal L^0[i]=[i..i]$，且 $\mathcal L^1[i]=[i..j]\ (j\geq k>i)$。
+ 若 $\hat w_k > \hat w_i$，则 $\mathcal L^1[i]=[i..i]$，且 $\mathcal L^0[i]=[i..j]\ (j\geq k>i)$。$\blacksquare$

##### Lemma B

> 若 $r=(i,j,p)$ 为一个run，则对于 $\hat{w}[j+1]\prec_l \hat{w}[j+1-p]$ 的 $l$，$\forall r$ 的 $\prec_l$ 意义下的 Lyndon Root $\hat w[i_{\lambda}..j_{\lambda}]$ 都与 $\mathcal L^l(i_{\lambda})$相等。

$\because \hat{w}[j+1]\ne\hat{w}[j+1-p]$，令 $l\in\{0,1\}$ 满足 $\hat{w}[j+1]\prec_l\hat{w}[j+1-p]$。

令 $\lambda=[i_{\lambda}...j_{\lambda}]$ 为 $r$ 的 $\prec_l$ 意义下的一个 Lyndon Root，由 **[Theory 1.2.1 Lyndon Concatanation]**，$[i_{\lambda}...j_{\lambda}]=\mathcal L^l(i_{\lambda})$。$\blacksquare$

对于一个run $r=(i,j,p)$，令 $B_r=\{\lambda=[i_{\lambda}...j_{\lambda}]|\lambda$ 为 $r$ 的 $\prec_l$ 意义下的一个 Lyndon Root 且 $i_{\lambda}\ne i\}$。即 $B_r$ 表示所有 $r$ 的关于 $\prec_l$ 的 Lyndon Root 构成的集合，但要除去开头位置 $i$ 处开始的 Lyndon Root。有 $|Beg(B_r)|=|B_r|\geq \lfloor e_r-1\rfloor\geq 1$，其中 $e_r$ 为 $r$ 的指数。

##### Lemma C

> 两个不同的 run $r,r'$，$Beg(B_r)\cap Beg(B_{r'})$ 为空。

反证，假设存在 $i\in Beg(B_r)\cap Beg(B_{r'})$，并且 $\lambda=[i...j_{\lambda}]\in B_r$，$\lambda'=[i...j_{\lambda'}]\in B_{r'}$。

令 $l\in\{0,1\}$ 满足 $\lambda=\mathcal L^l[i]$，由于 $\lambda\ne \lambda'$，有 $\lambda'=\mathcal L^{1-l}[i]$。

由 **Lemma A**，$\lambda$ 和 $\lambda'$ 中有且只有一个为 $[i..i]$。

不妨设 $\lambda=[i..i]$，那么 $j_{\lambda'}>i$。

由于 $w[i...j_{\lambda'}]$ 为一个 Lyndon Word，有 $w[i]\ne w[j_{\lambda'}]$。

由 $B_r$ 和 $B_{r'}$ 的定义，$r$ 和 $r'$ 的开始位置均小于 $i$，这意味着 $w[i-1]=w[i]$（由 $r$ 的周期性），并且 $w[i-1]=w[j_{\lambda'}]$（由 $r'$ 的周期性）。矛盾 $\blacksquare$

任意的一个 run $r$ 可以被赋予一个两两不交的非空位置集合 $Beg(B_r)$。并且，由于 $1\notin Beg(B_r)$ 对于任意的一个 $r$ 均成立，有 $\sum_{r\in Runs(w)}|B_r|=\sum_{r\in Runs(w)}|Beg(B_r)|\leq |w|-1$。

考虑字符串 $w$，由于对于任意 $r\in Runs(w)$，有 $|B_r|\geq1$，由 **Lemma C**，有 $|Runs(w)|\leq\sum_{r\in Runs(w)}|B_r|\leq |w|-1$。

考虑字符串 $w$，令 $e_r$ 表示 $r$ 的指数。由于对于任意 $r\in Runs(w)$，有 $|B_r|\geq \lfloor e_r-1\rfloor>e_r-2$，由 **Lemma C**，有 $\sum_{r\in Runs(w)}(e_r-2)<\sum_{r\in Runs(w)}\lfloor e_r-1\rfloor\leq\sum_{r\in Runs(w)}|B_r|\leq |w|-1$。因为 $|Runs(w)|\leq |w|-1$，可得 $\sum_{r\in Runs(w)}e_r\leq3n-3$。$\blacksquare$

### 4.3 Details about Implementation

现在，问题来了：我们怎么算 $\mathcal L^0$ 和 $\mathcal L^1$？

简要思路：

$$
\mathcal{L}^0[i] = \mathrm{NSV}(i) = \min\{\{j > i : \neg(\mathrm{suf}(i) \triangleleft \mathrm{suf}(j))\} \cup \{n\}\}
$$

类似的，

$$
\begin{aligned}\mathcal{L}^1[i] &= \mathrm{NSV}^R(i) \\&= \min\{\{j > i : \neg(\mathrm{suf}(i) \triangleleft^R \mathrm{suf}(j))\} \cup \{n\}\} \\&= \min\{\{j > i : \mathrm{suf}(i) \triangleleft \mathrm{suf}(j) \vee \mathrm{suf}(i) \sqsupseteq \mathrm{suf}(j))\} \cup \{n\}\}\end{aligned}
$$

在实现 Runs 之前，你需要会字符串哈希或者后缀数组或者其他后缀数据结构。

根据以上证明中的 **Lemma B**，每一个 runs 都会对应一个 Lyndon root，所以如果我们把 Lyndon Array 算出来了，就可以把每个 runs 对应的 Lyndon root 求出来。

所以我们考虑对于字符串的每个后缀都维护他的 CFL，方法是在头上插入一个新字符，然后判断是否合法。根据 **[Theory 1.2.1 Lyndon Concatanation]**，如果遇到一个 Lyndon word 大于下一个的情况，合并即可。可以保证正确性。

这里有一个实现上的细节，可能会好写一点。根据 **[Theory 1.2.4 Lyndon Suffixes and Lyndon Prefixes]**，$w_i$ 是 $w_iw_{i+1}\cdots w_k$ 的最小前缀，所以比较两个 Lyndon word 的字典序相当于比较两个后缀的大小，而这个是比做一个 lcp 要简单多的。

所以至此 Lyndon Array 已经求完了，具体实现细节可以看代码。

接下来我们只要使用 Lyndon Array 扩展出 runs 就可以了，具体的做法是求出 lcp，即如果当前的 Lyndon Array $\mathcal L[i] = (l..r)$，则我们 lcp 求出最长的 $s[l..l+l_1-1]=s[r+1..r+l_1], s[l-l_2..l-1]=s[r-l_2..r-1]$。

根据 runs 的定义，如果 $l_1 + l_2 \ge 2(l - r + 1)$，那么我们就找到了一个 run $(l-l_2, r+l_1-1, r-l+1)$。

如果我们使用 SAIS 和 $\mathcal O(n) - \mathcal O(1)$ 的 rmq 算法，我们就可以线性时间内求出所有的 runs。

比较优秀的 $\mathcal O(n) - \mathcal O(1)$ 的 rmq 方法：[叉姐的](https://zhuanlan.zhihu.com/p/86891529) 和 [hqztrue的](https://zhuanlan.zhihu.com/p/79423299)。

### Template

> [Luogu P6656](https://www.luogu.com.cn/problem/P6656) 

是我出的啦owo

求就好了，真真实实的板子题。

[Code](https://www.luogu.com.cn/paste/nqx6e5eh)

这篇文章可能以后还会更，加上 2-Period 问题什么的。

## 5 Three Squares Lemma

### 5.1 Definition

**Squares**: 能表示成 $x^2$ 的串。

**Primitive Squares**: 不能再拆的 Squares。如 $x^2+x$ 一定是一个 Primitive Square。

 ### 5.2 Three Squares Lemma

#### Theory 5.2.1 Three Squares Lemma

> 我们有 3 个 Primitive Squares，为 $u^2$，$v^2$ 和 $w^2$，满足 $|u|<|v|<|w|$。
>
> 则我们有 $|u| + |v| \le |w|$，并且 Primitive Squares 是数量是 poly log 级别的，即 $\mathcal O(n\log n)$。

唔，我不会证= =咕了咕了

Evguenia Kopylova, W.F. Smyth. The three squares lemma revisited. DOI: 10.1016/j.jda.2011.03.009

## 6 扯淡

我在出 LOJ #173 的时候，发现有一个非常强的暴力，就是暴力地去做 lcp 和 lcs。

后来我经过不懈努力使用 `aaaaa...ab` 这个串卡掉了他，但是其实考场上如果时间不够的话写这个暴力其实是非常优秀的，~~毕竟我见过的两个 runs 题都没有卡这个暴力~~。

---

## 作者：unputdownable (赞：26)

本文以文字说明为主，记号较少，可能存在一些非正式表述，请谅解。

前置知识：字符串哈希或后缀数组，~~脑子~~。

--------

记 $s_{i}$ 为字符串 $s$ 的第 $i$ 个字符（$1$ 下标），默认字符串的长度是 $n$。

记 $s_{l,r}$ 为从 $l$ 到 $r$ 的字符组成的子串。

称一个字符串的 $i$ 后缀为从第 $i$ 个字符开始的后缀，$i$ 前缀则是到第 $i$ 个字符终止的前缀。

如果没有讨论越界问题，默认 $s_0=s_{n+1}=-\inf$，即小于任意字符。

--------

首先，什么是 runs？

一个字符串 $s$ 中的一个 runs 是一个循环子串，例如 ``aabcabcabb`` 中 ``abcabcab`` 这个子串就是一个 runs。

一个 runs 必然存在最小周期，记最小周期长度为 $p$，对应子串是 $s_{l,r}$，则一个 runs 还要满足：

- 长度至少为 $2p$，即周期至少出现两遍；
- 不能向两侧扩展，即 $s_{r+1} \neq s_{r+1-p}$；对于左侧同理。

所以，对于串 ``aabcabcabb`` 而言，子串 ``abcab`` 和 ``abcabca`` 都不能算作 runs。

--------

接下来讨论如何去求所有 runs。

如果现在已经找到了某个 runs 的某个最小周期 $s_{i,j}$，那么可以通过对 $i$ 后缀和 $j+1$ 后缀求一次**最长公共前缀**来向右扩展，以及对 $i-1$ 前缀和 $j$ 前缀求**最长公共后缀**来向左扩展，最后检查是否满足 runs 的条件就能找到这个 runs。

![](https://cdn.luogu.com.cn/upload/image_hosting/uzk8o2m7.png)

任意一个在 runs 范围中且长度为 $p$ 的子串其实都能被称为 "周期"，下文直接称其为周期。

记上述操作为一次检查。要想找出所有 runs，只需要检查所有可能的周期即可。

--------

任何一个 runs 都有 $p$ 种周期，他们互为循环同构的串，仍然假设这个 runs 是 $s_{l,r}$。

从其中最小的串入手，假设这是 $s_{i,j}$（因为长度至少是 $2p$ 所以这样的串必然存在）。

这玩意其实可以叫最小表示法，一般的求法是重复原串两遍，取 $1\sim n$ 后缀中最小的后缀再截取 $n$ 前缀就行。

但是由于这是 runs，可以证明这还是一个 Lyndon Word，即所有后缀都比原串大，以下是简要证明：

> 首先说明对于任意非空串 $a,b$，$(a+b)^k+a$（$k \in \Z^+$） 一定不是一个最小表示法，考虑 $a+(a+b)^k$ 与 $(b+a)^k+a$ 这两个串就能推出矛盾。
>
> 反证法，不妨假设我们找到的串是 $r$ 有一个后缀 $s$ 比原串小。因为任何循环同构都大于等于 $r$，可以推出 $s$ 是 $r$ 的前缀，即 $s$ 是 $r$ 的一个 $\text{border}$。
>
> 首先 $|s|$ 不能是 $|r|$ 的因数，否则 $|r|$ 就不是最小周期；
>
> 若 $|s|<\frac{|r|}2$，则 $r$ 可以写成 $s+t+s$，必然不是最小表示法；
>
> 若 $|s|>\frac{|r|}2$, 记 $r=s+t$，则 $s$ 必然有周期 $t$，取 $t$ 长度为 $|s| \bmod |t|$ 的前缀为 $a$，记剩下的为 $b$，则 $s=(a+b)^k+a$，$r=(a+b)^{k+1}+a$，也必然不是最小表示法。

所以对于任意 $i+1 \leq k \leq j$，$k$ 后缀要大于 $i$ 后缀。

那么 $j+1$ 后缀是 $i$ 后面第一个可能比 $i$ 后缀小的后缀。

同时可以发现 $j+1$ 后缀与 $i$ 后缀的大小关系取决于 $s_{r+1}$ 与 $ s_{r+1-p}$ 的大小关系（就是之前取最长公共前缀的两个后缀）。

所以，通过找到**所有 $i$ 后缀后面第一个比他小的后缀**，并且检查对应区间，可以找出所有 $s_{r+1}<s_{r+1-p}$ 的 runs。

对于 $s_{r+1}<s_{r+1-p}$ 的 runs，从最大的周期（即反转字符大小关系下的最小，**注意此时空字符应当大于所有字符**）入手即可。即**找到所有 $i$ 后缀后面第一个比他大的后缀**，就可以找出所有这一类 runs。

不存在 $s_{r+1}=s_{r+1-p}$ 的情况，所以，通过检查至多 $2n$ 次，可以找出**所有** runs。

这也就是 runs 数量小于等于 $2n$ 的证明。

最后，如果这个 runs 包含 $k$ 个完整周期，那么最小/大周期也会出现至少 $k-1$ 次，所以记得去重。

----------------

讨论一些实现细节。

第一种实现是使用后缀排序。需要写正串和反串两遍 SA。通过写 SA-IS 加上四毛子可以做到线性求 runs。

第二种是直接字符串哈希，使用二分哈希/倍增哈希 $O(\log n)$ 求最长公共前后缀以及后缀比较。使用单调栈就只需要 $O(n)$ 次比较，总复杂度也是 $O(n\log n)$。

代码就不放了，~~哈希应该不至于不会写吧~~，记得去重。

后记：其实并不是初学 runs，纯粹是昨晚和同学口胡 runs 后几天心血来潮写了一篇。

---

