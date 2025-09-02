# 「SiR-1」Lighthouse

## 题目描述

给定一棵 $n$ 个点的树，每个点有权值 $w_i$，初始为 $0$。初始得分 $s=0$。

进行 $m$ 次操作，每次操作选择一个点 $u$，给 $s$ 增加 $u$ 所在的同点权连通块的大小（即，假设只保留点权等于 $w_u$ 的点，和连接两个点权等于 $w_u$ 的点的边，对得分的贡献就是此时 $u$ 所在的连通块大小。注意这不会真的删去一部分树上的点和边），然后给 $w_u$ 增加 $1$。

请对所有 $n^m$ 种操作方式，求它们的得分 $s$ 之和，对 $10^9+7$ 取模。

## 说明/提示

对于所有数据，满足 $1\leq n\leq 1000$，$1\leq m\leq 10^5$，$1\leq u,v\leq n$，保证输入是一棵树。

- Subtask 0（5 pts）：$n,m\le 7$。
- Subtask 1（20 pts）：$n,m\le 10$。
- Subtask 2（15 pts）：$n,m\le 50$。
- Subtask 3（15 pts）：$n,m\le 100$。
- Subtask 4（15 pts）：$n\le 50$。
- Subtask 5（15 pts）：树是一条链。
- Subtask 6（15 pts）：无特殊限制。

本题同时开启子任务依赖。具体地：

+ 对于子任务 $i(i \in [1, 3])$，依赖于子任务 $0 \sim (i -  1)$；
+ 对于子任务 $4$，依赖于子任务 $0 \sim 2$；
+ 对于子任务 $6$，依赖于子任务 $0 \sim 5$。

## 样例 #1

### 输入

```
3 2
1 3
2 3```

### 输出

```
40```

# 题解

## 作者：E.Space (赞：17)

这里给一种不需要 dirty work 递推的方法。

求和可以改成求期望再乘方案数。

首先第一步是一样的，把连通块的贡献拆成操作的点对每个连通块里的点的贡献。记 $p(u,v,w)$ 表示操作 $u$ 之前 $u$ 的权值是 $w$ 且这一步操作时 $v$ 在那个连通块里的概率。那么答案就是

$$
\sum\limits_{u=1}^n \sum\limits_{v=1}^n \sum\limits_{w=0}^{m-1} p(u,v,w)
$$

容易发现，$p(u,v,w)$ 只和 $u$ 与 $v$ 的距离有关，所以设 $d$ 为 $u$ 到 $v$ 的路径上的点数（本题中我们把这个定义为两点间距离），答案可以改写成

$$
\sum\limits_{d=1}^n c_d \sum\limits_{w=0}^{m-1} p(d,w)
$$

其中 $c_d$ 表示路径上点数为 $d$ 的有向路径条数，$p(d,w)$ 表示一对距离为 $d$ 的点 $u,v$ 的 $p(u,v,w)$。

现在来求 $p(d,w)$。

考虑这样计算这个概率：先决定每一步操作是否在路径上，然后决定路径上的操作的位置。有贡献当且仅当路径上至少有 $dw+1$ 次操作，并且在路径上的前 $dw$ 次操作均等地分布在路径的 $d$ 个点上，并且第 $dw+1$ 次操作操作的是点 $u$。

可以发现，这三个条件中，只要满足了第一个条件，无论有多少次操作在路径上，满足后面两个条件的概率都是一样的。这个概率等于

$$
\frac{(dw)!}{(w!)^dd^{dw+1}}
$$

即前 $dw$ 次平均分配的方案数除以前 $dw$ 次的总方案数再乘以第 $dw+1$ 次操作位于 $u$ 的概率。

对于满足第一个条件的概率，可以考虑枚举有多少个操作在路径上。由于一次操作在路径上的概率是 $\frac{d}{n}$，所以这个概率就等于

$$
\sum\limits_{i=dw+1}^m{m\choose i}\frac{d^i(n-d)^{m-i}}{n^m}
$$

注意 $w$ 的取值范围是 $\left[0,\left\lfloor\frac{m-1}{d}\right\rfloor\right]$，否则就会有 $dw+1>m$。

结合上述几个部分，答案就等于

$$
\sum\limits_{d=1}^n c_d \sum\limits_{w=0}^{\left\lfloor\frac{m-1}{d}\right\rfloor}\frac{(dw)!}{(w!)^dd^{dw+1}}\sum\limits_{i=dw+1}^m{m\choose i}\frac{d^i(n-d)^{m-i}}{n^m}
$$

乘上最初为了算期望除掉的方案数 $n^m$，就是

$$
\sum\limits_{d=1}^n c_d \sum\limits_{w=0}^{\left\lfloor\frac{m-1}{d}\right\rfloor}\frac{(dw)!}{(w!)^dd^{dw+1}}\sum\limits_{i=dw+1}^m{m\choose i}d^i(n-d)^{m-i}
$$

然后就可以直接算了。

组合数和阶乘、阶乘逆元可以直接 $O(m)$ 预处理。

$d^i$ 和 $(n-d)^{m-i}$ 可以对每个 $d$ 的值 $O(m)$ 预处理，这里总复杂度是 $O(nm)$。

这样最后一个和号就可以由其右边的东西对 $i$ 做一个后缀和得到。

前两个和号的枚举是 $O(m\log n)$ 的，而计算中间那个分式的分母的逆元的时间复杂度是 $O(\log M)$ 的，其中 $M$ 为模数。

所以总复杂度是 $O(n^2+m(n+\log n\log M))$。在本题的数据范围下和标算相当。

---

## 作者：Sol1 (赞：6)

定义一次操作 $(u,j)$ 为在 $u$ 的点权为 $j$ 时给 $u$ 的点权 +1。现在可以分别考虑计算每一个操作的贡献。

那么可以枚举操作 $(u,j)$，然后对于一个点 $v$，其能够对 $(u,j)$ 的贡献产生贡献当且仅当树以 $u$ 为根，执行该操作时 $u\rightarrow v$ 的路径上所有点权均为 $j$。那么枚举这一操作何时执行，然后 $v$ 到根这条链上的所有点必须在这一操作之前占据 $j$ 个位置，剩下的位置从剩余的点里面瞎选操作就可以了。该操作执行后从所有点里面瞎选点操作就可以了。得到下式：

$$\text{Ans}=\sum_{u=1}^n\sum_{v=1}^n\sum_{j=0}^{m-1}\sum_{i=0}^{m-1}\dfrac{(dj)!}{(j!)^d}\cdot\dbinom{i}{dj}(n-d)^{i-dj}n^{m-i-1}$$

其中 $d$ 是 $u\rightarrow v$ 路径上点的数量。

提一提公因式：

$$\text{Ans}=n^{m-1}\sum_{u=1}^n\sum_{v=1}^n\sum_{j=0}^{m-1}\dfrac{(dj)!}{(j!)^d(n-d)^{dj}}\sum_{i=0}^{m-1}\cdot\dbinom{i}{dj}\left(\dfrac{n-d}{n}\right)^i$$

考虑提前对于所有 $d$ ，预处理出路径上点数为 $d$ 的点对数，记为 $C_d$。

$$\text{Ans}=n^{m-1}\sum_{d=1}^nC_d\sum_{j=0}^{m-1}\dfrac{(dj)!}{(j!)^d(n-d)^{dj}}\sum_{i=0}^{m-1}\cdot\dbinom{i}{dj}\left(\dfrac{n-d}{n}\right)^i$$

然后需要快速计算：

$$f_{a,b}=\sum_{i=0}^{m-1}\dbinom{i}{a}\left(\dfrac{n-b}{n}\right)^i$$

套路组合数加法递推：

$$f_{a,b}=\sum_{i=0}^{m-1}\dbinom{i-1}{a-1}\left(\dfrac{n-b}{n}\right)^i+\sum_{i=0}^{m-1}\dbinom{i-1}{a}\left(\dfrac{n-b}{n}\right)^i$$

$$f_{a,b}=\sum_{i=0}^{m-2}\dbinom{i}{a-1}\left(\dfrac{n-b}{n}\right)^{i+1}+\sum_{i=0}^{m-2}\dbinom{i}{a}\left(\dfrac{n-b}{n}\right)^{i+1}$$

$$f_{a,b}=\dfrac{n-b}{n}\left[f_{a-1,b}-\dbinom{m-1}{a-1}\left(\dfrac{n-b}{n}\right)^{m-1}\right]+\dfrac{n-b}{n}\left[f_{a,b}-\dbinom{m-1}{a}\left(\dfrac{n-b}{n}\right)^{m-1}\right]$$

$$\dfrac{b}{n}f_{a,b}=\dfrac{n-b}{n}f_{a-1,b}-\dbinom{m-1}{a-1}\left(\dfrac{n-b}{n}\right)^{m}-\dbinom{m-1}{a}\left(\dfrac{n-b}{n}\right)^{m}$$

$$f_{a,b}=\dfrac{n-b}{b}f_{a-1,b}-\dfrac{n}{b}\dbinom{m-1}{a-1}\left(\dfrac{n-b}{n}\right)^{m}-\dfrac{n}{b}\dbinom{m-1}{a}\left(\dfrac{n-b}{n}\right)^{m}$$

$$f_{a,b}=\dfrac{n-b}{b}f_{a-1,b}-\dfrac{n}{b}\dbinom{m}{a}\left(\dfrac{n-b}{n}\right)^{m}$$

这样这个东西就可以递推了。既然 $b$ 只有 $O(n)$ 种，我们就可以在枚举到一个 $d$ 的时候递推一遍，然后剩下的暴力算可以做到 $O(nm+m\ln m)$，足以通过。

可以通过点分治和分块多点求值做到 $O(n\log^2n+m\log^3m+m\sqrt m\log m)$，然而由于常数原因没啥用。

---

## 作者：EnofTaiPeople (赞：3)

不知道这道题难点在哪里，但确实有思考价值。

设 $F(u,v)$ 表示所有操作方式中，某一次对 $u$ 操作，此时 $u,v$ 连通的情况总和。

不难发现，答案就是 $\sum\limits_{u=1}^n\sum\limits_{v=1}^nF(u,v)$。

在 $F(u,v)$ 的过程中，$u,v$ 路径上的点本质相同，路径外的点也本质相同。

于是，$F(u,v)$ 只与 $u,v$ 之间的路径长度有关，我们可以暴力求出路径长度为 $l$ 的 $(u,v)$ 点对有多少个，记为 $ct_l$，而路径长度为 $l$ 的 $F(u,v)$ 均相等，记为 $G_l$，于是答案为 $\sum\limits_{l=1}^nct_lG_l$

考虑求出 $G_l$，先枚举连通时相等的 $w$，再枚举连通之后的对 $u$ 的操作是第 $k$ 次。

第 $k$ 次之后的操作点没有限制，而之前的路径外点只有 $n-l$ 个，路径上点每一个只能**恰好**出现 $w$ 次。

于是 $G_l=\sum\limits_{wl<m}\dfrac{(wl)!}{(w!)^l}\sum\limits_{k=wl+1}^m\dbinom{k-1}{wl}(n-l)^{k-wl-1}n^{m-k}$ 这个式子不方便计算，直接算时间复杂度为 $O(m^2\ln n)$。

如果你想用三模 NTT 也可以，但我没研究过，可能可以多得一些分。

然后我们需要还一种计数方式，具体地，改为总共有 $k$ 次操作在路径上，这样可以规避二项式中的 $wl$，事实上，这 $k$ 次操作一定是前 $wl$ 次按规律排布，第 $wl+1$ 次是对 $u$ 操作，而后面的没有限制，于是让计算更简便。

此时有 $G_l=\sum\limits_{wl<m}\dfrac{(wl)!}{(w!)^l}\sum\limits_{k=wl+1}^m\dbinom m kl^{k-wl-1}(n-l)^{m-k}$，我们希望后面的和式中不含 $wl$，于是将 $l^{m-wl-1}$ 前提。

于是 $G_l=\sum\limits_{wl<m}\dfrac{(wl)!}{(w!)^l}l^{m-wl-1}\sum\limits_{k=wl+1}^m\dbinom m k(\dfrac{n-l}l)^{m-k}$，然后后面的和式可以前缀和处理。

总时间复杂度 $O(nm+m\ln n)$，可以通过。

---

## 作者：dead_X (赞：1)

考虑一对点 $(x,y)$ 的贡献。

那只能是先弄一堆操作加加加，加到链上全一样了，然后对着 $x$ 加一下就能给 $y$ 贡献。

发现这里只和 $x$ 到 $y$ 的距离有关，假设距离为 $t$，那么问题就转化为了有一个序列 $a$，每次可以给某个数 $+1$ 或者啥都不加，然后如果 $z$ 次操作后序列全相等就有 $n^{m-z-1}$ 的贡献。

那直接枚举一下 $t,z,a_1$ 就是 $O(m^2\log m)$ 的了，考虑优化。

$$
\begin{aligned}
&\sum_D\sum_{ij\leq D}a_j(n-j)^{D-ij}n^{m-D-1}\frac{D!}{(D-ij)!(i!)^j}\\
=&\sum_D\sum_{ij\leq D}a_j\left(\frac{n-j}{n}\right)^{D-ij}n^{m-1-ij}\frac{D!}{(D-ij)!(i!)^j}\\
\end{aligned}
$$

考虑快速计算和 $D$ 有关的项。

$$
\begin{aligned}
F(a,b,m)&=\sum_{x\leq m}\left(\frac{n-a}{n}\right)^x\binom{x}{b}\\
&=\sum_{x\leq m}\left(\frac{n-a}{n}\right)^x\left(\binom{x-1}{b-1}+\binom{x-1}{b}\right)\\
&=\frac{n-a}{n}\sum_{x\leq m}\left(\frac{n-a}{n}\right)^{x-1}\binom{x-1}{b-1}
+\frac{n-a}{n}\sum_{x\leq m}\left(\frac{n-a}{n}\right)^{x-1}\binom{x-1}{b}\\\\
&=\frac{n-a}{n}(F(a,b-1,m-1)+F(a,b,m-1))\\
nF(a,b,m)&=(n-a)\left(F(a,b-1,m)-\left(\frac{n-a}{n}\right)^m\binom{m}{b-1}
+F(a,b,m)-\left(\frac{n-a}{n}\right)^m\binom{m}{b}\right)\\
aF(a,b,m)&=(n-a)\left(F(a,b-1,m)
-\left(\frac{n-a}{n}\right)^m\binom{m+1}{b}\right)\\
\end{aligned}
$$

反正一通 Dirty Work 我们肯定可以通过 $F(a,b-1,m)$ 算出 $F(a,b,m)$，所以这题 $O(n^2+nm)$。已经够多 Dirty Work 了，别再端上来了。

---

## 作者：irris (赞：1)

定义一次操作 $(u,j)$ 为在 $u$ 的点权为 $j$ 时给 $u$ 的点权 $+1$，枚举操作 $(u,j)$ 和其在第 $i$ 次操作时执行，容易发现点 $v$ 能够对 $(u,j)$ 的贡献产生贡献，当且仅当执行该操作时 $u \sim v$ 的路径上所有点权均为 $j$。更具体地：

+ $v$ 到 $u$ 链上的所有点必须在操作之前占据 $j$ 个位置，剩下的位置 **从剩余的点里** 随便操作即可（这里一定要注意加粗字）；
+ 该操作执行后 **从所有点里** 随便操作即可。

于是我们得到了同样的式子：

$$\sum_{u=1}^n\sum_{v=1}^n\sum_{j=0}^{m-1}\sum_{i=0}^{m-1}\dfrac{(dj)!}{(j!)^d}\cdot\dbinom{i}{dj}(n-d)^{i-dj}n^{m-i-1}$$

其中：$d$ 是 $u\rightarrow v$ 路径上**点的**数量（注意不是边的数量）。

解释一下式子：

+ $\dfrac{(dj)!}{(j!)^d}$ 对于这 $dj$ 次操作确定顺序；
+ $\dbinom{i}{dj}$ 确定这 $dj$ 次操作的位置；
+ $(n-d)^{i-dj}$ 对这次操作之前从剩余的点里选择；
+ $n^{m-i-1}$ 对这次操作之后从任意点里选择。

由于 $dj \leq m$，这样的点对数只有 $\mathcal O(m\log m)$ 种。我们只需要快速计算后面这个形式的式子：
		
$$f_{a,b}=\sum_{i=0}^{m-1}\dbinom{i}{a}\left(\dfrac{n-b}{n}\right)^i$$
		
套路地，进行组合数加法递推：
		
$$f_{a,b}=\sum_{i=0}^{m-1}\dbinom{i-1}{a-1}\left(\dfrac{n-b}{n}\right)^i+\sum_{i=0}^{m-1}\dbinom{i-1}{a}\left(\dfrac{n-b}{n}\right)^i$$
		
化一下变量的范围：
		
$$f_{a,b}=\sum_{i=0}^{m-2}\dbinom{i}{a-1}\left(\dfrac{n-b}{n}\right)^{i+1} +\sum_{i=0}^{m-2}\dbinom{i}{a}\left(\dfrac{n-b}{n}\right)^{i+1}$$

对照新式（第二行）和原式（第一行）：
		
$$ \begin{aligned}
f_{a,b}&=\sum_{i=0}^{m-1}\dbinom{i}{a}\left(\dfrac{n-b}{n}\right)^i \\
f_{a,b}&=\sum_{i=0}^{m-2}\dbinom{i}{a-1}\left(\dfrac{n-b}{n}\right)^{i+1} +\sum_{i=0}^{m-2}\dbinom{i}{a}\left(\dfrac{n-b}{n}\right)^{i+1} 
\end{aligned} $$

不难得出：
		
$$ \begin{aligned}
f_{a,b} =& \dfrac{n-b}{n}\left[f_{a-1,b}-\dbinom{m-1}{a-1}\left(\dfrac{n-b}{n}\right)^{m-1}\right] + \\
& \dfrac{n-b}{n}\left[f_{a,b}-\dbinom{m-1}{a}\left(\dfrac{n-b}{n}\right)^{m-1}\right]
\end{aligned} $$

整理一下，然后就是 dirty work 了。
		
$$\dfrac{b}{n}f_{a,b}=\dfrac{n-b}{n}f_{a-1,b}-\dbinom{m-1}{a-1}\left(\dfrac{n-b}{n}\right)^{m}-\dbinom{m-1}{a}\left(\dfrac{n-b}{n}\right)^{m}$$
		
$$f_{a,b}=\dfrac{n-b}{b}f_{a-1,b}-\dfrac{n}{b}\dbinom{m-1}{a-1}\left(\dfrac{n-b}{n}\right)^{m}-\dfrac{n}{b}\dbinom{m-1}{a}\left(\dfrac{n-b}{n}\right)^{m}$$
		
$$f_{a,b}=\dfrac{n-b}{b}f_{a-1,b}-\dfrac{n}{b}\dbinom{m}{a}\left(\dfrac{n-b}{n}\right)^{m}$$

到这里这个东西对于 $a$ 就可以递推了。回顾原始的式子是：
		
$$n^{m-1}\sum_{d=1}^nC_d\sum_{j=0}^{m-1}\dfrac{(dj)!}{(j!)^d(n-d)^{dj}}f_{dj, d}$$
		
暴力递推即可 $\mathcal O(nm + m\log m)$。

---

## 作者：Yanami_Anna (赞：1)

猛。

很有意思。

首先我们设 $F(u,v)$ 表示 $u$ 和 $v$ 连通的时候，$u$ 往上蹦一下的情况数量。

显而易见，答案是 $\sum_{i=1}^n\sum_{j=1}^nF(i,j)$。

然后你发现，如果一条路长度相同，那么他并没有什么不一样的，因为道路内的没有实际差异，道路外的我不在乎，也没有实际差异。

所以你决定枚举长度 $l$，假设 $G_l$ 为所有长度为 $l$ 的路径的 $F$，假设 $cnt_l$ 表示长度为 $l$ 的路径数量，那么现在答案是 $\sum_{l=1}^{n}cnt_lG_l$。

$cnt_l$ 我们很方便计算，考虑 $G_l$ 怎么计算。

先枚举 $w$ 表示第 $w$ 层的时候路径端点开始蹦。

然后你发现总共要在路径中做 $wl$ 次操作，每个点恰好做 $w$ 次。

这个不难，首先打标签全排列，然后再去标签。

然后假设是第 $k$ 次操作拿下的。

那就是，$k-1$ 次操作中安排 $wl$ 次操作，然后剩下 $k-1-wl$ 次操作，可以选择路径外的所有点。

剩下 $m-k$ 次操作，可以选择所有点因为目的已经达到了后面什么样子不在乎了。

式子就长这样：
$$
G_l=\sum_{wl<m}\frac{(wl)!}{(w!)^l}\sum_{k=wl+1}^{m}C_{k-1}^{wl}(n-l)^{k-1-wl}n^{m-k}
$$
然后你发现直接嗯算就是 $m^2\ln n$ 的，非常的愚蠢，我们需要来优化他。

首先就是那个低能组合数，我们必须把他拿下来，但是很明显拿不下来，那我们就考虑整 $k$ 次操作在路径上。
$$
G_l=\sum_{wl<m}\frac{(wl)!}{(w!)^l}\sum_{k=wl+1}^{m}C_{m}^{k}(l)^{k-1-wl}(n-l)^{m-k}
$$
这个式子非常好看，但是还不够，我们容不得 $w$ 在后面出现！

所以我们把他变成了这个样子。
$$
G_l=\sum_{wl<m}\frac{(wl)!}{(w!)^l}l^{-wl}\sum_{k=wl+1}^{m}C_{m}^{k}(l)^{k-1}(n-l)^{m-k}
$$
很好，后面没有 $w$ 了，这意味着后面的式子只与 $k$ 和 $l$ 有关了。

但是还不够，写一下就会发现难写，所以我们再化一下。
$$
G_l=\sum_{wl<m}\frac{(wl)!}{(w!)^l}l^{-wl}\sum_{k=wl+1}^{m}C_{m}^{k}(l)^{(k-m)+(m-1)}(n-l)^{m-k}
$$

$$
G_l=\sum_{wl<m}\frac{(wl)!}{(w!)^l}l^{-wl}\sum_{k=wl+1}^{m}C_{m}^{k}(l)^{(m-1)}(\frac{n-l}{l})^{m-k}
$$

$$
G_l=\sum_{wl<m}\frac{(wl)!}{(w!)^l}l^{m-wl-1}\sum_{k=wl+1}^{m}C_{m}^{k}(\frac{n-l}{l})^{m-k}
$$

​	
那我们直接对于每一个 $l$ 预处理一遍这些式子，然后后缀和，就可以直接求了。

天才的想法！

时间复杂度 $O(nm+m\ln n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int P=1000000007;
const int MAXN=200005;
int n,m;
vector<int> ljb[1500];
int Cnt[1500];
int father[1500][11];
int dep[1500];
int Jc[MAXN];
int InvJc[MAXN];
int Pre[MAXN];
int Suf[MAXN];
int ans;
int Co[MAXN];
int power(int x,int y=P-2){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    if(y&1)return tmp*tmp%P*x%P;
    else return tmp*tmp%P;
}
void dfs(int cur,int fa){
    dep[cur]=dep[fa]+1;
    father[cur][0]=fa;
    for(int i=1;i<11;i++){
        father[cur][i]=father[father[cur][i-1]][i-1];
    }
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        dfs(v,cur);
    }
    return;
}
int LCA(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=10;i>=0;i--){
        if(dep[father[x][i]]>=dep[y]){
            x=father[x][i];
        }
    }
    if(x==y)return x;
    for(int i=10;i>=0;i--){
        if(father[x][i]^father[y][i]){
            x=father[x][i];
            y=father[y][i];
        }
    }
    return father[x][0];
}
int dis(int x,int y){
    int lca=LCA(x,y);
    return dep[x]+dep[y]-dep[lca]-dep[father[lca][0]];
}
int C(int n,int m){
    return Jc[n]*InvJc[m]%P*InvJc[n-m]%P;
}
signed main(){
    scanf("%lld%lld",&n,&m);
    Jc[0]=1;
    InvJc[0]=1;
    for(int i=1;i<=200000;i++){
        Jc[i]=Jc[i-1]*i%P;
        InvJc[i]=power(Jc[i]);
    }
    for(int i=0;i<=m;i++){
        Co[i]=C(m,i);
    }
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        ljb[u].push_back(v);
        ljb[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int fw=dis(i,j);
            if(fw<1||fw>n){
                return j;
            }
            assert(fw>=1&&fw<=n);
            Cnt[fw]++;
        }
    }
    for(int l=1;l<=n;l++){
        int Fuck=(n-l)*power(l)%P;
        int D=1;
        for(int i=m;i>=0;i--){
            Suf[i]=(Suf[i+1]+C(m,i)*D%P)%P;
            D=D*Fuck%P;
        }
        int S=0;
        for(int w=0;w*l<m;w++){
            int dinner=(Suf[w*l+1])*Jc[w*l]%P*(power(InvJc[w],l))%P*power(l,m-w*l-1)%P;
            S=(S+dinner)%P;
        }
        ans=(ans+S*Cnt[l]%P)%P;
    }
    printf("%lld",ans%P);
    return 0;
}
```

---

