# 彼岸 | To See the Next Part of the Dream

## 题目背景

「“看见梦境的下一个部分”…？」

“是啊… ‘尽管身体已是成年人，但内心却依旧是那个不切实际的小孩，依旧是那个相信自己有着无尽可能的小孩——即使是在认清了现实和理想的鸿沟后，还仍是如此。年少时那个成为摇滚巨星的梦，如今已显得分外不可及，只能在一次次前行中看见梦的下一个部分’… 不觉得作者和我很像吗？”

“曾经年少的自己对一切的未知都怀揣着好奇与欣喜，但如今仿佛只是在如同抓住救命稻草一般抓住自己背离现实的梦想，然后在生活的洋流中逐渐看见梦的下一个部分… 明知自己的失败，却仍在仿佛为了看见什么、达成什么一样向上登攀，这样一来，和作者所描述的‘active loser’也没什么两样吧…”

「所以，你所期望看见的、期望达成的，究竟是什么呢？」

“…”

“现在的我，已经不知道了。”

> 나의 어리고 멍청했던 날들은 사라져줬으면
>
> 如果那些年少无知的日子消失掉就好了
>
> 나의 소중한 인연들 이제는 추억속으로만
>
> 珍贵的感情 现在仅仅存在于在记忆中
>
> 만약 이 세상이 전부 누군가의 또다른 꿈이었다면
>
> 如果这个世界 只是别人的梦
>
> 언젠가 깨어나게 될때 나는 지금과는 달라져있을까
>
> 某天醒来时 我会变得不一样吗

## 题目描述

「那么，你相信宿命吗？」

“那种东西，顶多只是什么励志故事里的抒情工具吧。”

「是吗… 那么要玩玩塔罗牌吗？」

“谁会对那种事情感兴趣…”

「真是的，你要再一副对什么事情都漠不关心的态度我要生气了…！」

“好好好… 所以呢？塔罗牌呢？”

「这个嘛… 嘿嘿，自己想象咯～」

“什么毛病…”

「现在有 $n$ 叠塔罗牌放在桌上，每一叠都有 $2^n$ 张，从桌面向上分别是 $1$ 号、$2$ 号… $n$ 号。现在作为宿命的管理者的我们——要洗一遍这些塔罗牌！」

“怎么… 中二病开始传染了吗…”

「那么，洗牌的过程是，将牌均匀地分成两半，下面一半和上面一半分别放在左右手；接着，右手从底部放下一张牌，左手从底部放下一张牌，右手又从底部放下一张牌… 这样交错重复，于是一次洗牌就完成了！」

“例如 $n=2$ 时，假设原来的牌从下往上看是 $[1,2,3,4]$，洗一次牌后就会变成 $[3,1,4,2]$——是这样吗？”

「是的！然后对于这 $n$ 叠初始时都按顺序从下到上摆放的塔罗牌，我会不操作第一叠牌，然后洗一次第二叠牌，洗两次第三叠牌… 洗 $n-1$ 次第 $n$ 叠牌。接下来，我会把这 $n$ 叠牌都从下到上地发给 $2^n$ 个人——也就是说第一个人会拿到每叠牌的第一张，第二个人会拿到每叠牌的第二张… 每一个人都恰好会拿到 $n$ 张牌。」

「现在，定义一个人拿到和自己号码相同的牌的张数为这个人的幸运值。你能算出这 $n$ 个人幸运值的总和是多少吗？」

“嗯… 撇开你粗制滥造的题面不谈，这个题目还是很有趣的。”

「适可而止啊喂！」

“… 我想了想，好像还挺简单的。不妨让我们记 $n=k$ 的时候的幸运值总和为 $f(k)$。现在你需要对 $l\le k\le r$ 的 $f(k)$ 求和，你看怎么样？”

「… 不是很会了…」

### 简要题意

对于长度为 $2k$ 的序列 $a$，定义函数 $S_q(a)$，其中

$$
S_q(a)=
\begin{cases}
a,&q=0\\
[a_{k+1},a_1,a_{k+2},a_2,\dots,a_{2k},a_k],&q=1\\
S_{q-1}(S_1(a)),&\text{otherwise.}
\end{cases}
$$

现在给定正整数 $l,r$，求 $\sum_{k=l}^r f(k)$，其中

$$
f(n)=\sum_{q=0}^{n-1}\sum_{k=1}^{2^n}\left[S_q([1,2,3,\dots,2^n])_k=k\right]
$$

## 说明/提示

### 样例解释

以样例一中计算 $f(2)$ 为例。最初有 $2$ 叠牌，从下到上的牌都是 $[1,2,3,4]$。然后现在对第一叠牌不操作，第二叠牌洗一次，于是第二叠牌从下到上变成了 $[3,1,4,2]$。现在把两叠牌发给 $4$ 个人。第一个人拿到 $[1,3]$，第二个人拿到 $[2,1]$，第三个人拿到 $[3,4]$，第四个人拿到 $[4,2]$。发现每个人的幸运值都为 $1$（都恰好拿到了一张和自己号码相同的牌），于是幸运值总和就是 $4$，继而 $f(2)=4$。

### 数据范围

对于全部数据，有 $1\le l\le r\le 10^{10}$。

Subtask 1（10 pts）：保证 $l=r$ 且 $r\le 12$。

Subtask 2（35 pts）：保证 $l=r$。

Subtask 3（15 pts）：保证 $1\le l\le r\le 10^6$。

Subtask 4（40 pts）：无特殊限制。

## 样例 #1

### 输入

```
2 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 4```

### 输出

```
26```

## 样例 #3

### 输入

```
10 20```

### 输出

```
2096384```

# 题解

## 作者：Mivik (赞：6)

## Subtask 1

给暴力分是中华民族的优秀传统美德。

## Subtask 2

我们注意到这个子任务给了很多分，暗示着出题人认为会了求单点就差不多会做了（嗯嗯）。

保留题目中 1 开始的下标机制，我们发现洗一次牌本质上就是进行一次

$$
k\rightarrow 2k\pmod{2^n+1}
$$

的置换（记为 $P$）。而题目中的 $f(n)$ 实际上就是在对 $P^0,P^1,P^2,\dots,P^{n-1}$ 这些置换的不动点个数求和。

不妨先来研究一下这个置换的环。首先有个显然的观察：环长最大是 $2n$。因为对于任何整数 $t$（$1\le t\le\left(2^n+1\right)$），我们有

$$
\begin{aligned}
&2^{2n}t\\
=&\left(2^{2n}-1\right)t+t\\
=&\left(2^n-1\right)\left(2^n+1\right)t+t\\
=&t\pmod{2^n+1}
\end{aligned}
$$

我们想要求出长度为 $k$ 的环有多少个，可直接切入似乎会没有什么思路。我们考虑计算所在环长度为 $k$ 的约数的数的个数 $B_k$，然后就可以莫比乌斯反演得到所在环长度为 $k$ 的数的个数 $A_k$。

我们发现，对于一个数 $t$，它在一个长度为 $k$ 的约数的环内，当且仅当

$$
\begin{aligned}
2^kt&\equiv t\pmod{2^n+1}\\
\left(2^k-1\right)t&\equiv 0\pmod{2^n+1}
\end{aligned}
$$

即

$$
\begin{aligned}
(2^n+1)&\mid \left((2^k-1)t\right)\\
\frac{2^n+1}{\left(2^n+1,2^k-1\right)}&\mid t
\end{aligned}
$$

$\left(2^n+1,2^k-1\right)$？这不难让我们想起一个定理：

> 定理一：对于 $n,m,a\in\Z^+$，有
>
$$
\left(a^n-1,a^m-1\right)=a^{(n,m)}-1
$$

关于这个定理的一个（甚至更通用的证明）可以看 [这里](https://math.stackexchange.com/questions/7473/prove-that-gcdan-1-am-1-a-gcdn-m-1)。

可是上面的是 $\left(2^n+1,2^k-1\right)$，看起来似乎没什么联系啊？

我们不妨改写为

$$
\left(2^n+1,2^k-1\right)=\left(\frac{2^{2n}-1}{2^n-1},2^k-1\right)
$$

然后我们知道

> 定理二：对于 $p,q,k\in\Z^+,(p,q)=1$，有
>
$$
(k,p)=\frac{(k,pq)}{(k,q)}
$$

这个挺显然的。由于 $(2^n-1,2^n+1)=(2^n-1,2)=1$，于是就有

$$
\begin{aligned}
&\left(2^n+1,2^k-1\right)\\
=&\left(\frac{2^{2n}-1}{2^n-1},2^k-1\right)\\
=&\frac{\left(2^{2n}-1,2^k-1\right)}{\left(2^n-1,2^k-1\right)}\\
=&\frac{2^{(2n,k)}-1}{2^{(n,k)}-1}
\end{aligned}
$$

我们分两种情况讨论：

### $\frac k{(n,k)}$ 为奇数

也就是说 $(k,2n)=(k,n)$，那么

$$
\begin{aligned} \left(2^{2n}-1,2^k-1\right)=\left(2^n-1,2^k-1\right)&=2^{(n,k)}-1\\
\left(2^n+1,2^k-1\right)&=1
\end{aligned}
$$

条件转化为

$$
\left(2^n+1\right)\mid t
$$

由于 $1\le t\le 2^n$，显然有 $B_k=0$。

### $\frac k{(n,k)}$ 为偶数

那么 $(k,2n)=2(k,n)$，则有

$$
\begin{aligned}
\left(2^{2n}-1,2^k-1\right)&=2^{2(n,k)}-1\\
\left(2^n-1,2^k-1\right)&=2^{(n,k)}-1\\
\left(2^n+1,2^k-1\right)&=2^{(n,k)}+1
\end{aligned}
$$

条件转化为

$$
\frac{2^n+1}{2^{(n,k)}+1}\mid t
$$

由于 $1\le t\le 2^n$，则 $B_k=2^{(n,k)}$。

---

总结一下

$$
B_k=
\begin{cases}
2^{(n,k)},&2\mid\frac k{(n,k)}\\
0,&\text{otherwise.}
\end{cases}
$$

记 $n=2^qp$（$p$ 为奇数），那么

$$
2\mid\frac k{(n,k)}\iff 2^{q+1}\mid k
$$

套用反演可得

$$
A_k=\sum_{d|k}\mu(d)B_{k/d}
$$

我们考虑到原题要求的 $P^0,P^1,P^2,\dots,P^{n-1}$ 的不动点个数之和似乎并不是非常的 canonical：最长的环有 $2n$ 长怎么只求前 $n$ 个？我们不妨先求出 $P^0,P^1,P^2,\dots,P^{2n-1}$ 的不动点个数之和，记之为 $g(n)$。

首先我们观察到环长必须得是 $(2n)$ 的约数。由于一个长度为 $w$ 的环对 $f(n)$ 的贡献为 $\left(\frac{2n}w\right)$，对 $g(n)$ 的贡献为 

$$
\left\lfloor\frac nw\right\rfloor=\frac12\left(1+\frac{2n}w\right)
$$

于是就有 $f(n)=\frac12\left(g(n)+2^n\right)$。我们只需要求出 $g(n)$ 即可。

整理式子之前现有一个小定理：

> 定理三：
>
$$
\sum_{k=1}^n\mu(k)\left\lfloor\frac nk\right\rfloor=1
$$

证明：

$$
\begin{aligned}
&\sum_{k=1}^n\mu(k)\left\lfloor\frac nk\right\rfloor\\
=&\sum_{k=1}^n\mu(k)\sum_{k|d,d\le n}1\\
=&\sum_{d=1}^n\sum_{k|d}\mu(k)\\
=&\sum_{d=1}^n\left[d=1\right]\\
=&1
\end{aligned}
$$

于是开始整理式子：

$$
\begin{aligned}
g(n)&=\sum_{k=1}^{2n}\left\lfloor\frac{2n}k\right\rfloor\sum_{d|k}\mu(d)B_{k/d}\\
&=\sum_{k=1}^p\left\lfloor\frac pk\right\rfloor\sum_{d|2Qk}\mu(d)B_{2Qk/d}\\
&=\sum_{k=1}^p\left\lfloor\frac pk\right\rfloor\sum_{d|k}\mu\left(\frac kd\right)2^{Q(d,p)}\\
&=\sum_{g|p}2^{Qg}\sum_{k=1}^{\frac pg}\left\lfloor\frac p{kg}\right\rfloor\sum_{d|k}\mu\left(\frac kd\right)\sum_{t|d,t|\frac pg}\mu(t)\\
&=\sum_{g|p}2^{Qg}\sum_{t|\frac pg}\mu(t)\sum_{d=1}^{\frac p{gt}}\sum_{k=1}^{\left\lfloor\frac p{gtd}\right\rfloor}\left\lfloor\frac p{kgtd}\right\rfloor\mu(k)\\
&=\sum_{g|p}2^{Qg}\sum_{t|\frac pg}\mu(t)\sum_{d=1}^{\frac p{gt}}1\\
&=\sum_{g|p}2^{Qg}\sum_{t|\frac pg}\mu(t)\frac p{gt}\\
&=\sum_{g|p}2^{Qg}\phi\left(\frac pg\right)\\
&=\sum_{g|p}2^{n/g}\phi(g)\\
&=\sum_{g|n,g\text{ is odd}}2^{n/g}\phi(g)
\end{aligned}
$$

嗯，于是我们拿到了 45 分。

## Subtask 3

我们考虑求 $g(n)$ 的前缀和 $G(n)$，再随便操作下就能求到 $f(n)$ 的前缀和 $F(n)$ 了。

$$
\begin{aligned}
G(N)&=\sum_{n=1}^N\sum_{g|n,g\text{ is odd}}2^{n/g}\phi(g)\\
&=\sum_{d=1}2^d\sum_{g=1}^{\left\lfloor\frac Nd\right\rfloor}\left[g\text{ is odd}\right]\phi(g)
\end{aligned}
$$

我们记

$$
S(n)=\sum_{k=1}^n\left[k\text{ is odd}\right]\phi(k)
$$

那么 $G(N)=\sum_{d=1}2^dS\left(\left\lfloor\frac Nd\right\rfloor\right)$。预处理好 $10^6$ 之内的 $S(n)$，我们就可以愉快地计算啦～

## Subtask 4

我们来观察这个 $S(n)$。首先我们注意到

$$
\phi(2n)=
\begin{cases}
\phi(n),&n\text{ is odd}\\
2\phi(n),&\text{otherwise.}
\end{cases}
$$

那么我们设 $H(n)=\sum_{k=1}^n\phi(k)$，则有

$$
\begin{aligned}
S(n)&=\sum_{k=1}^n\left[k\text{ is odd}\right]\phi(k)\\
&=H(n)-\sum_{k=1}^n\left[k\text{ is even}\right]\phi(k)\\
&=H(n)-\sum_{k=1}^{\left\lfloor\frac n2\right\rfloor}\left[k\text{ is even}\right]\phi(2k)-\sum_{k=1}^{\left\lfloor\frac n2\right\rfloor}\left[k\text{ is odd}\right]\phi(2k)\\
&=H(n)-2\sum_{k=1}^{\left\lfloor\frac n2\right\rfloor}\left[k\text{ is even}\right]\phi(k)-\sum_{k=1}^{\left\lfloor\frac n2\right\rfloor}\left[k\text{ is odd}\right]\phi(k)\\
&=H(n)-2\left(H\left(\left\lfloor\frac n2\right\rfloor\right)-S\left(\left\lfloor\frac n2\right\rfloor\right)\right)-S\left(\left\lfloor\frac n2\right\rfloor\right)\\
&=H(n)-2H\left(\left\lfloor\frac n2\right\rfloor\right)+S\left(\left\lfloor\frac n2\right\rfloor\right)\\
&=H(n)-2H\left(\left\lfloor\frac n2\right\rfloor\right)+H\left(\left\lfloor\frac n2\right\rfloor\right)-2H\left(\left\lfloor\frac n4\right\rfloor\right)+\cdots\\
&=H(n)-H\left(\left\lfloor\frac n2\right\rfloor\right)-H\left(\left\lfloor\frac n4\right\rfloor\right)-H\left(\left\lfloor\frac n8\right\rfloor\right)-\cdots
\end{aligned}
$$

那么用杜教筛计算 $H(n)$ 即可。这样的话，计算单个 $S(n)$ 会需要计算 $\log n$ 次 $H(n)$，加之我们需要算 $\sqrt N$ 个不同位置的 $S(n)$，看似时间复杂度爆表，实则不然。

记 $D(n)=\left\{n,\left\lfloor\frac n2\right\rfloor,\left\lfloor\frac n3\right\rfloor,\left\lfloor\frac n4\right\rfloor,\cdots\right\}$（不要给我以初中老师的口吻说集合不可重… 自动去重，啊，自动去重），那么我们知道杜教筛在计算 $H(n)$ 时实际上是对 $D(n)$ 中的所有数都计算了一遍 $H(n)$ 并存入了缓存。我们注意到，由于我们求的 $G(N)=\sum_{d=1}2^dS\left(\left\lfloor\frac Nd\right\rfloor\right)$，也就是说我们要求的 $S(x)$ 是满足 $x\in D(N)$ 的，而根据：

> 定理四：$\left\lfloor\frac{\left\lfloor\frac np\right\rfloor}q\right\rfloor=\left\lfloor\frac n{pq}\right\rfloor$

我们知道我们在求 $S(x)$ 时，需要求的 $H(x),H\left(\left\lfloor\frac x2\right\rfloor\right),H\left(\left\lfloor\frac x3\right\rfloor\right),\dots$ 这些东西实际上也是在 $D(N)$ 中，也就是被计算并缓存过的。因此总的时间复杂度依旧等同于做一次杜教筛的复杂度（当然是计算 $H(n)$ 的部分，其它地方不一定，但不会影响总复杂度），也就是 $O(N^{2/3})$（如果预处理前 $N^{2/3}$ 个 $H(n)$ 的话）。

[ametus.h](https://pastebin.com/U0qK4eJb) / [dream.cpp](https://pastebin.com/z0uv8W3G)

---

## 作者：VinstaG173 (赞：6)

有趣的数学题（

首先 $S_q$ 是 $S_1$ 的 $q$ 次迭代，而将所有数减去 $1$ 后表示成 $n$ 位二进制数，$S_1$ 操作相当于将末位取反后移到首位。因此我们容易想到它的等价形式：将整个数取反拼在原数前面形成 $2n$ 位 01 串，每次循环右移 $1$ 位后取末 $n$ 位即可。

由于循环移位时前 $n$ 位和末 $n$ 位始终互为取反，因此 $(S_q)_ k=k$ 时整个 $2n$ 位 01 串和初始时完全相同。因此此 $2n$ 位 01 串以 $q$ 为周期。

取 $k$ 对应的 01 串的最小正周期 $t$，则显然 $t \mid 2n$，且当且仅当 $q$ 为 $t$ 的倍数时有 $(S_q)_ k=k$。而由于 $k$ 移 $n$ 位后为其取反，显然与 $k$ 不同，因此 $t \nmid n$。故 $\dfrac{2n}{t}$ 为奇数，设其为 $s$。

我们考虑求使得 $t=2n$ 的 $k$ 的数量 $g(n)$，则可以对 $n$ 位数 $k$ 按 $t$ 的值分类，$t<2n$ 者均可以对应一个 $\dfrac{t}{2}=\dfrac{n}{s}$ 位数 $k'$。因此有式子：

$$\sum_{s \mid n,2 \nmid s}g\left(\dfrac{n}{s}\right)=2^n.$$

~~接下来我们考虑推式子。~~ 推什么式子，手算几项扔 [oeis](http://oeis.org/A045663) 就行了。

我们得到了一个 formula:

$$g(n)=\sum_{d \mid n,2 \nmid d}\mu(d)2^{\frac{n}{d}}.$$

事实上看到这个式子我们会发现它很容易推导，是一个显然的莫比乌斯反演的形式，容易用和推导莫比乌斯反演公式类似的方法得到

$$\begin{aligned}
\sum_{d \mid n,2 \nmid d}\mu(d)2^{\frac{n}{d}}&=\sum_{d \mid n,2 \nmid d}\mu(d)\sum_{s\mid\frac{n}{d},2 \nmid s}g\left(\dfrac{n}{ds}\right)\\
&=\sum_{S \mid n,2 \nmid S}g\left(\dfrac{n}{S}\right)\sum_{d|S}\mu(d)=g(n).
\end{aligned}$$

其中第二行用 $S$ 代替了第一行中的 $ds$，由于 $S$ 是奇数，因此 $d \mid S$ 即蕴含了 $2 \nmid d$。接着我们考虑转化题目中所给出的式子。

$$\begin{aligned}
f(n)&=\sum_{q=0}^{n-1}\sum_{k=1}^{2^n}[S_q([1,2,3,\dots,2^n])_ k=k]\\
&=\sum_{s \mid n,2 \nmid s}\dfrac{s+1}{2}g\left(\dfrac{n}{s}\right)\\
&=\dfrac{1}{2}\sum_{s \mid n,2 \nmid s}(s+1)\sum_{d \mid \frac{n}{s},2 \nmid d}\mu(d)2^{\frac{n}{ds}}\\
&=\dfrac{1}{2}\sum_{S \mid n,2 \nmid s}2^{\frac{n}{S}}\sum_{s \mid S}(s+1)\mu\left(\dfrac{S}{s}\right)\\
&=\dfrac{1}{2}\sum_{S \mid n,2 \nmid s}2^{\frac{n}{S}}(\varphi(S)+[S=1]),
\end{aligned}$$

因此

$$\begin{aligned}
Ans=\sum_{n=l}^{r}f(n)&=\dfrac{1}{2}\sum_{n=l}^{r}\sum_{S \mid n,2 \nmid S}2^{\frac{n}{S}}(\varphi(S)+[S=1])\\
&=\dfrac{1}{2}\sum_{2 \nmid S}(\varphi(S)+[S=1])\sum_{n=l}^{r}[S \mid n]2^{\frac{n}{S}}\\
&=\dfrac{1}{2}\sum_{2 \nmid S}(\varphi(S)+[S=1])\sum_{n=\left\lceil\frac{l}{S}\right\rceil}^{\left\lfloor\frac{r}{S}\right\rfloor}2^n.
\end{aligned}$$

我们记

$$\begin{aligned}
G(n)&=\dfrac{1}{2}\sum_{2 \nmid S}(\varphi(S)+[S=1])\sum_{i=1}^{\left\lfloor\frac{n}{S}\right\rfloor}2^i\\
&=2^n-1+\sum_{d}2^{d-1}\sum_{1 \le S \le \left\lfloor\frac{n}{d}\right\rfloor,2 \nmid S}\varphi(S).
\end{aligned}$$

则 $Ans=G(r)-G(l-1)$。记

$$F(n)=\sum_{1 \le S \le n,2 \nmid S}\varphi(S),$$

则可以用杜教筛加倍增计算。总复杂度在[出题人神 Mivik 的题解](https://mivik.blog.luogu.org/mivik-round-4-solution-dream)里分析得为 $O(n^{\frac{2}{3}})$（感觉这一部分非常神仙），我就不做赘述了。

~~然而退役选手陆续犯了忘删调试，忘开 ll，计算爆 ll 等多种 sb 错误期间甚至认为复杂度假了，大家引以为戒（~~

Code:
```cpp
#include<cctype>
#include<cstdio>
#include<cstring>
#define rg register
#define ll unsigned long long
const int ntf=998244353;
const int inv2=499122177;
const int N=1e7;int pr[N+7],cnt;
int mp[N+7];ll Sphi[N+7];
inline void init(){
	Sphi[1]=1;for(rg int i=2;i<=N;++i){
		if(!mp[i])mp[i]=i,Sphi[i]=i-1,pr[++cnt]=i;
		for(rg int j=1,k=i<<1;j<=cnt&&k<=N;++j,k=i*pr[j]){
			mp[k]=pr[j];if(mp[i]==pr[j]){
				Sphi[k]=Sphi[i]*pr[j];break;
			}Sphi[k]=Sphi[i]*(pr[j]-1);
		}Sphi[i]=(Sphi[i]+Sphi[i-1])%ntf;
	}
}ll sphi[1007],mxn;
inline ll GetSphi(ll n){
	if(n<=N)return Sphi[n];
	if(~sphi[mxn/n])return sphi[mxn/n];
	ll res=n%ntf*(n+1)%ntf*inv2%ntf;
	for(rg ll i=2,j;i<=n;i=j+1){j=n/(n/i);
		res=(res-(j-i+1)*GetSphi(n/i)%ntf+ntf)%ntf;
	}return sphi[mxn/n]=res;
}inline ll GetF(ll n){
	if(!n)return 0;
	ll res=GetSphi(n);
	for(rg ll i=n>>1;i;i>>=1){
		res=(res-GetSphi(i)+ntf)%ntf;
	}return res;
}inline ll qpw(ll v){
	ll r=1,x=2;v%=(ntf-1);while(v){
		(v&1)&&(r=r*x%ntf);x=x*x%ntf,v>>=1;
	}return r;
}inline ll solve(ll n){ll res=0,ls=1,nw;
	mxn=n,memset(sphi,-1,sizeof(sphi));
	for(rg ll i=1,j;i<=n;i=j+1,ls=nw){
		j=n/(n/i);res=(res+GetF(n/i)*\
		((nw=qpw(j))-ls+ntf)%ntf)%ntf;
	}return res;
}ll l,r,ans;int main(){init();
	scanf(" %llu %llu",&l,&r),--l;
	ans=(solve(r)-solve(l)+qpw(r)-qpw(l)+ntf+ntf)%ntf;
	return 0&printf("%llu\n",ans);
}
```

---

## 作者：Daniel13265 (赞：4)

给个无脑推式子做法。

---

> 设长 $2^n$ 的排列的 in-shuffle 的置换为 $\sigma_n$，求
> $$\sum_{n=l}^{r}\sum_{i=0}^{n-1}\operatorname{fix}\left(\sigma_n^i\right).$$
>
> 其中 $\operatorname{fix}(\sigma)$ 表示排列 $\sigma$ 的不动点数目。$l\le r\le10^{10}$。

分别对 $N=r$ 和 $N=l-1$ 求
$$\sum_{n=1}^{N}\sum_{i=0}^{n-1}\operatorname{fix}\left(\sigma_n^i\right).$$
作差后得到答案。

注意到 $\sigma_n(t)=2t\bmod\left(2^n+1\right)$，于是
$$
\begin{aligned}
\sum_{n=1}^{N}\sum_{i=0}^{n-1}\operatorname{fix}\left(\sigma_n^i\right)&=\sum_{n=1}^{N}\sum_{i=0}^{n-1}\sum_{t=1}^{2^n}\left[2^it\equiv t\pmod{2^n+1}\right]\\
&=\sum_{n=1}^{N}\sum_{i=0}^{n-1}\sum_{t=1}^{2^n}\left[\left(2^i-1\right)t\equiv 0\pmod{2^n+1}\right]\\
&=\sum_{n=1}^{N}\sum_{i=0}^{n-1}\sum_{t=1}^{2^n}\left[t\mid\frac{2^n+1}{\left(2^n+1,2^i-1\right)}\right]\\
&=\sum_{n=1}^{N}\sum_{i=0}^{n-1}\left\lfloor\frac{2^n\left(2^n+1,2^i-1\right)}{2^n+1}\right\rfloor\\
&=\sum_{n=1}^{N}\left(2^n+\sum_{i=1}^{n-1}\left\lfloor\frac{2^n\left(2^n+1,2^i-1\right)}{2^n+1}\right\rfloor\right)\\
&=\sum_{n=1}^{N}\left(2^n+\sum_{i=1}^{n-1}\left(\left(2^n+1,2^i-1\right)-1\right)\right)\\
&=\sum_{n=1}^{N}\left(2^n+\sum_{i=1}^{n-1}\left(\left(2^n+1,2^n-2^{n-i}\right)-1\right)\right)\\
&=\sum_{n=1}^{N}\left(2^n+\sum_{i=1}^{n-1}\left(\left(2^n+1,2^{n-i}+1\right)-1\right)\right)\\
&=\sum_{n=1}^{N}\left(2^n+\sum_{i=1}^{n-1}\left(\left(2^n+1,2^i+1\right)-1\right)\right)\\
&=\sum_{i=1}^{N}\sum_{j=1}^i\left(\left(2^i+1,2^j+1\right)-1\right)\\
&=\sum_{i=1}^{N}\sum_{j=1}^i2^{(i,j)}\left[2\nmid\frac{ij}{(i,j)^2}\right]\\
&=\sum_{d=1}^N2^d\sum_{k=1}^{\lfloor N/d\rfloor}\mu(k)\sum_{i=1}^{\lfloor N/dk\rfloor}\sum_{j=1}^i\left[2\nmid ijk^2\right]\\
&=\sum_{d=1}^N2^d\sum_{k=1}^{\lfloor N/d\rfloor}\mu(k)[2\nmid k]f\left(\left\lfloor\frac{N}{dk}\right\rfloor\right)\\
&=\sum_{d=1}^N2^dg\left(\left\lfloor\frac{N}{d}\right\rfloor\right).
\end{aligned}
$$

其中

$$
\begin{gathered}
g(n)=\sum_{k=1}^n\mu(k)[2\nmid k]f\left(\left\lfloor\frac nk\right\rfloor\right),\\
f(n)=\sum_{i=1}^{n}\sum_{j=1}^i\left[2\nmid ij\right]=\frac{\lfloor(n+1)/2\rfloor\lfloor(n+3)/2\rfloor}2.
\end{gathered}
$$

上述推导用到

>  **定理**：$\forall i,j\in\mathbb N^+$ 有
>
>  $$\left(2^i+1,2^j+1\right)=1+2^{(i,j)}\left[2\nmid\frac{ij}{(i,j)^2}\right].$$

其证明在文章末尾。

整除分块计算最终答案。对于 $g$ 的计算可以设阈值 $T$，对 $n\le T$ 预处理 $g(n)$，$n>T$ 时整除分块。小范围的计算直接无脑狄利克雷差分，时间复杂度 $O(T\log\log T)$；大范围的计算需要用到 $\mu(k)[2\nmid k]$ 的块筛，无脑杜教筛：
$$
\sum_{k|n}\mu(k)[2\nmid k]=[n\text{ is a power of }2].
$$

时间复杂度
$$
O\left(T\log\log T+\sum_{d=1}^{\lfloor N/T\rfloor}\sqrt{\frac Nd}\right)=O\left(T\log\log T+\frac{N}{\sqrt T}\right).
$$

取 $T=\sqrt[3]{\left(N/\log\log N\right)^2}$ 有最优时间复杂度 $O\left(\sqrt[3]{N^2\log\log N}\right)$。有了这个阈值后可以对杜教筛的阈值稍作修改做到空间复杂度 $O\left(\sqrt[3]{\left(N/\log\log N\right)^2}\right)$。

---

时间复杂度应该能进一步降到 $O\left(N^{2/3}\right)$，但脑子被僵尸吃了，所以只会无脑做法。

---

>  **定理证明**：欲求 $\left(2^i+1,2^j+1\right)$。若 $i=j$，则值为 $2^i+1$。否则不妨假设 $i>j$。则
>  $$\begin{aligned}\left(2^i+1,2^j+1\right)&=\left(\left(2^i+1\right)-2^{i-j}\left(2^j+1\right),2^j+1\right)\\&=\left(1-2^{i-j},2^j+1\right)\\&=\left(2^{i-j}-1,2^j+1\right).\end{aligned}$$
>
>  欲求 $\left(2^i+1,2^j-1\right)$。若 $i=j$，则值为 $1$。若 $i>j$，则
>  $$\begin{aligned}\left(2^i+1,2^j+1\right)&=\left(\left(2^i+1\right)-2^{i-j}\left(2^j-1\right),2^j-1\right)\\&=\left(2^{i-j}+1,2^j-1\right).\end{aligned}$$
>  若 $i<j$，则
>  $$\begin{aligned}\left(2^i+1,2^j-1\right)&=\left(2^i+1,\left(2^j-1\right)-2^{j-i}\left(2^i+1\right)\right)\\&=\left(2^i+1,-1-2^{j-i}\right)\\&=\left(2^i+1,2^{j-i}+1\right).\end{aligned}$$
>
>  容易发现这个过程在指数上是欧几里得算法。于是求 $\left(2^i+1,2^j+1\right)$ 最终一定会递归到 $2^{(i,j)}+1$ 与 $2^{(i,j)}\pm1$ 时停止，故该值一定是 $2^{(i,j)}+1$ 或 $1$。
>
>  确定值到底是多少只需要执行上述过程求 $\left(2^{(i,j)}+1,2^i+1\right)$ 与 $\left(2^{(i,j)}+1,2^j+1\right)$ 即可。不难发现
>  $$\left(2^{(i,j)}+1,2^i+1\right)=2^{(i,j)}+1\iff2\nmid\frac{i}{(i,j)}.$$
>
>  因此
>  $$\left(2^i+1,2^j+1\right)=2^{(i,j)}+1\iff2\nmid\frac{i}{(i,j)},2\nmid\frac{i}{(i,j)}.$$
>
>  从而定理得证。

---

## 作者：whiteqwq (赞：2)

[P8151 彼岸 | To See the Next Part of the Dream](https://www.luogu.com.cn/problem/P8151) 解题报告：

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/15888171.html)

**下文称奇数集合为 $\mathbb{O}$。**


## 题意

对于一个长度为 $2^n$ 的排列 $1,2,\cdots,2^n$，令置换 $P$ 为 $x\mapsto 2x\pmod{2^n+1}$，令 $f(n)$ 为 $P^0,P^1,\cdots,P^{n-1}$ 的不动点数量之和，求 $f$ 的前缀和。

$1\leqslant n\leqslant 10^{10}$

## 分析

思路曲折复杂，需要一定的熟练度与技巧的题。

将置换拆成若干个环，可以发现点 $x$ 在长度为 $l$ 约数的环内当且仅当 $(2^l-1)x\equiv0\pmod{2^n+1}$，也就是：

$$\frac{2^n+1}{\gcd(2^n+1,2^l-1)}\mid x$$

然后联想到经典结论 $\gcd(x^a-1,x^b-1)=x^{\gcd(a,b)}-1$，于是考虑向其转化：

$$\gcd(2^n+1,2^l-1)=\gcd(\frac{2^{2n}-1}{2^n-1},2^l-1)=\frac{2^{\gcd(2n,l)}-1}{2^{\gcd(n,l)}-1}$$

令 $t_l$ 为长度为 $l$ 的约数的环数量（显然 $l$ 是 $2n$ 的因数，因为 $2^{2n}l=(2^n+1)(2^n-1)l+l\equiv l\pmod{2^n+1}$），那么：

若 $\gcd(2n,l)=\gcd(n,l)$，那么 $2^n+1\mid x$，此时 $t_l=0$。

否则，$\gcd(2n,l)=2\gcd(n,l)$，那么 $\dfrac{2^n+1}{2^{\gcd(n,l)}-1}\mid x$，那么 $t_l=2^{\gcd(n,l)}$。

也就是说 $t_l=\begin{cases}0&\gcd(2n,l)=\gcd(n,l)\\2^{\gcd(n,l)}&\text{otherwise}\end{cases}$

令 $p$ 为 $n$ 分解质因数有多少个 $2$，那么 $t_l$ 非零当且仅当 $2^{p+1}\mid l$。

由于环长是 $2n$ 的约数而不是 $n$ 的约数，走 $n$ 步之后每个环都一定走了一半（原因是造成贡献的环长的二幂次至少是 $2^{p+1}$，走 $2n$ 步走完的完整环数量为奇数），那么我们就可以令 $g(n)$ 为 $P^0,P^1,\cdots,P^{2n-1}$ 的不动点数量，那么有 $f(n)=\sum\frac{g(n)+2^n}{2}$。

我们将上面的”为 $l$ 约数“莫反，并设 $n=2^ab$：

下面要用到的一个式子：$\sum_{k=1}^n\mu(k)\lfloor\frac{n}{k}\rfloor=\sum_{d=1}^n\sum_{k\mid d}\mu(k)=1$。

$$g(n)=\sum_{k=1}^{b}\lfloor\frac{2n}{k}\rfloor\sum_{d\mid k\times 2^{a+1}}2^{\gcd(d,b)2^a}\mu(\frac{k}{d})\\=\sum_{p\mid b}2^{2^ap}\sum_{k=1}^{\frac{b}{p}}\lfloor\frac{b}{pk}\rfloor\sum_{d\mid k}\mu(\frac{k}{d})\sum_{z\mid d,z\mid\frac{b}{p}}\mu(z)\\=\sum_{p\mid b}2^{2^ap}\sum_{z\mid\frac{b}{p}}\mu(z)\sum_{d=1}^{\frac{b}{pz}}\sum_{k=1}^{\lfloor\frac{b}{pzd}\rfloor}\mu(k)\lfloor\frac{b}{pzdk}\rfloor\\=\sum_{p\mid b}2^{2^ap}\sum_{z\mid\frac{b}{p}}\mu(z)\sum_{d=1}^{\frac{b}{pz}}1=\sum_{p\mid b}2^{2^ap}\sum_{z\mid\frac{b}{p}}\mu(z)\frac{b}{pz}\\=\sum_{p\mid b}2^{2^ap}\varphi(\frac{b}{p})=\sum_{p\mid n,p\in\mathbb{O}}2^{\frac{n}{p}}\varphi(p)$$

继续推：

$$\sum_{i=1}^ng(i)=\sum_{i=1}^n\sum_{p\mid n,p\in\mathbb{O}}2^{\frac{n}{p}}\varphi(p)\\=\sum_{d=1}^n2^d\sum_{1\leqslant p\leqslant \lfloor\frac{n}{d}\rfloor,p\in\mathbb{O}}\varphi(p)$$

记 $h(n)=\sum_{i=1}^n[i\in\mathbb{O}]\varphi(i),p(n)=\sum_{i=1}^n\varphi(i)$，那么有：

$$g(i)=\sum_{d=1}^n 2^dh(\lfloor\frac{n}{d}\rfloor)\\h(n)=p(n)-\sum_{i=1}^n[i\notin\mathbb{O}]\varphi(i)=p(n)-\sum_{i=1}^{\lfloor\frac{n}{2}\rfloor}[i\in\mathbb{O}]\varphi(2i)-\sum_{i=1}^{\lfloor\frac{n}{2}\rfloor}[i\notin\mathbb{O}]\varphi(2i)\\=p(n)-\sum_{i=1}^{\lfloor\frac{n}{2}\rfloor}[i\in\mathbb{O}]\varphi(i)-2\sum_{i=1}^{\lfloor\frac{n}{2}\rfloor}[i\notin\mathbb{O}]\varphi(i)\\=p(n)-h(\lfloor\frac{n}{2}\rfloor)-2(p(\lfloor\frac{n}{2}\rfloor)-h(\lfloor\frac{n}{2}\rfloor))=p(n)-2p(\lfloor\frac{n}{2}\rfloor)+h(\lfloor\frac{n}{2}\rfloor)$$

归纳可以证明 $h(n)=p(n)-\sum_{i=1}^{\lfloor\log_2 n\rfloor}p(\lfloor\frac{n}{2^i}\rfloor)$。

由于杜教筛是块筛（即其可以筛出 $x=\lfloor\frac{n}{1}\rfloor,\lfloor\frac{n}{2}\rfloor,\cdots,\lfloor\frac{n}{n}\rfloor$ 时函数前缀和的值），所以我们进行一次杜教筛，然后暴力算就好了。

复杂度 $O(n^{\frac{2}{3}}+\sqrt n\log n)$。

## 代码

写的时候偷懒用了 map，实现的也不太精细，不过还是勉强过了。

```
#include<stdio.h>
#include<map>
using namespace std;
const int maxn=5000005,mod=998244353,inv2=(mod+1)/2;
long long L,R;
int ps;
int c[maxn],p[maxn],phi[maxn],sum[maxn];
map<long long,int>mp;
int ksm(int a,long long b){
	int res=1;
	while(b){
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
void sieve(int n){
	c[1]=phi[1]=sum[1]=1;
	for(int i=2;i<=n;i++){
		if(c[i]==0)
			p[++ps]=i,phi[i]=i-1;
		for(int j=1;j<=ps&&i*p[j]<=n;j++){
			c[i*p[j]]=1;
			if(i%p[j]==0){
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
		sum[i]=(sum[i-1]+phi[i])%mod;
	}
}
int calcp(long long n){
	if(n<=5000000)
		return sum[n];
	if(mp.count(n))
		return mp[n];
	int res=1ll*(n%mod)*(n%mod+1)%mod*inv2%mod;
	long long l=2,r;
	while(l<=n)
		r=n/(n/l),res=(res-1ll*(r-l+1)%mod*calcp(n/l)%mod+mod)%mod,l=r+1;
	return mp[n]=res;
}
int calch(long long n){
	int res=calcp(n);
	n>>=1;
	while(n)
		res=(res-calcp(n)+mod)%mod,n>>=1;
	return res;
}
int calcf(long long n){
	long long l=1,r;
	int res=0,lst=0;
	while(l<=n){
		r=n/(n/l);
		int now=(ksm(2,r+1)-2+mod)%mod;
		res=(res+1ll*(now-lst+mod)*calch(n/l))%mod;
		lst=now;
		l=r+1;
	}
	return 1ll*(0ll+res+ksm(2,n+1)-2+mod)*inv2%mod;
}
int main(){
	sieve(5000000);
	scanf("%lld%lld",&L,&R);
	printf("%d\n",(calcf(R)-calcf(L-1)+mod)%mod);
	return 0;
}
```

---

## 作者：zhouyuhang (赞：0)

曾经令我望而生畏的题目。

首先褪去老套的洗牌变换的外壳，即注意到 $\forall x \in [1, 2 ^ n]$，$x$ 在 $S_q(a)$ 中的下标是其在 $a$ 中的下标模 $2 ^ n + 1$ 意义下的 $2$ 倍。那么题意就变为：

$$
f(n) = \sum _ {q = 0} ^ {n - 1} \sum _ {i = 1} ^ {2 ^ n} [2 ^ q i \equiv i \pmod {2 ^ n + 1}] 
$$

求 $\sum _ {i = l} ^ r f(i)$。

我们直接开始推式子：

$$
\begin {aligned}
& f(n) \\
& = \sum _ {q = 0} ^ {n - 1} \sum _ {i = 1} ^ {2 ^ n} [2 ^ q i \equiv i \pmod {2 ^ n + 1}] \\
& = \sum _ {q = 0} ^ {n - 1} \sum _ {i = 1} ^ {2 ^ n} [2 ^ n + 1 \mid (2 ^ q - 1) i] \\
& = \sum _ {q = 0} ^ {n - 1} \sum _ {i = 1} ^ {2 ^ n}
\left[ \left. \frac {2 ^ n + 1} {(2 ^ n + 1, 2 ^ q - 1)} \right | i  \right] \\
& = \sum _ {q = 0} ^ {n - 1} ((2 ^ n + 1, 2 ^ q - 1) - 1)
\end {aligned}
$$

现在，有一个看上去很棘手的东西出现了，也就是形如 $(2 ^ x + 1, 2 ^ y - 1)$ 的形式。在这里，我们不过多展开如何计算它，因为很容易将其写成在指数上辗转相减的形式。经过一定的分类讨论，当 $x > y$ 时，有如下事实：

$$
(2 ^ x + 1, 2 ^ y - 1) = 
\left \{
\begin{array}{ll}
1, & v_2(x) \ge v_2(y) \\
2 ^ {(x, y)} + 1, & \text{otherwise}
\end {array}
\right.
$$

其中 $v_2(n)$ 为 $n$ 标准分解中质因子 $2$ 的次数（$v_2(0)$ 可以视作无穷大）。

那么重写 $f(n)$，就有：

$$
\begin {aligned}
& f(n) \\
& = \sum _ {q = 0} ^ {n - 1} [v_2(q) > v_2(n)] 2 ^ {(q, n)} \\
& = 2 ^ n + \sum _ {d \mid n} 2 ^ d \sum _ {i = 1} ^ {n / d} \left[ \left( i, \frac {n} {d} \right) = 1 \land 2 \mid i \right]
\end {aligned}
$$

我们把内层嵌套的和式单独拿出来，设其为 $g(n) = \sum _ {i = 1} ^ n \left[ \left( i, n \right) = 1 \land 2 \mid i \right]$。显然当 $2 \mid n \lor n = 1$ 时 $g(n) = 0$；否则可以考虑将 $i$ 与 $n - i$ 配对，可以得到 $g(n) = \frac {1} {2} \varphi(n)$。一些无关紧要常数可以放到最后再算，于是可以再次将问题简化为：

$$
f'(n) = \sum _ {d \mid n} 2 ^ d g' \left( \frac {n} {d} \right)
$$

其中 $g'(n)$ 是只在奇数处有值的 $\varphi(n)$，显然其也是积性函数。

我们现在要求 $f'$ 的前缀和，也就是：

$$
\begin {aligned}
& S _ {f'}(n) \\
& = \sum _ {i = 1} ^ n f'(i) \\
& = \sum _ {d = 1} ^ n 2 ^ d S _ {g'} \left( \left\lfloor \frac {n} {d} \right\rfloor \right)
\end {aligned}
$$

那我们只需求出 $g'$ 的块筛即可。首先杜教筛求出 $\varphi$ 的块筛，然后枚举包含 $2$ 的次数容斥一下：

$$
S _ {g'}(n) = S _ {\varphi}(n) - \sum _ {i = 1} S _ {g'} \left( \left\lfloor \frac {n} {2 ^ i} \right\rfloor \right) \varphi(2 ^ i)
$$

这样结合预处理就做到了 $O(n ^ {2 / 3})$。

有人惊异于最终复杂度与普通杜教筛相同，但其实这是由块筛的定义以及 $\left\lfloor \frac {n} {pq} \right\rfloor = \left\lfloor \frac {\left\lfloor \frac {n} {p} \right\rfloor} {q} \right\rfloor$ 简单推出的。

代码很简单。

---

