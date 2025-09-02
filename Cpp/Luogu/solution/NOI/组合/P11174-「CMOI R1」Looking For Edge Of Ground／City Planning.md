# 「CMOI R1」Looking For Edge Of Ground／City Planning

## 题目背景

![](bilibili:BV1np4y19753)

[如何对 $n$ 个点的简单有标号无向连通图计数？](https://www.luogu.com.cn/problem/P4841)$\small\color{white}/42^{\text{nd}}\text{Problem by ArCu}.$

有一个显然错误的做法：枚举一棵树，然后在上面加边。

你需要求每张图被统计的次数的平方和。

## 题目描述

给定正整数 $n$。

一开始，$\text{ClBe}$ 会选定一棵 $n$ 个点的有标号无向无根树，将树上的边染成白色。然后他会在这棵树上加任意多条边，且满足：

* 新加的边是黑色的无向边；
* 加完边后的图忽略边的颜色后是一张简单图。

接下来 $\text{ClBe}$ 会将所有可能得到的结果放到一个集合 $S$ 中。

显然这种统计连通图个数的方法会把一个图算很多遍，所以 $\text{ClBe}$ 定义 $f(G)$：$S$ 中有 $f(G)$ 个图在忽略边的颜色后和 $G$ 相同（两个图 $A,B$ 相同指对于任意一条边 $(u,v)$，$(u,v)\in A\iff(u,v)\in B$）。

（$\sum_G$ 代表对所有可能的图 $G$ 求和。）显然

$$\sum_{G}f(G)=n^{n-2}2^\binom{n-1}2$$

所以你需要求

$$\sum_{G}f(G)^2$$

答案对 $998244353$ 取模。很可惜因为一些原因模数**不能**取 $1004535809$。

## 说明/提示

$\text{Sample Explanation}:$

集合 $S$ 中包含以下 $6$ 张图（边权为 $0$ 代表白边，为 $1$ 代表黑边，点的编号为 $1A$ 代表这是图 $A$ 的 $1$ 号点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/neuo34c3.png)

$3$ 个点的连通图有 $4$ 种：

![](https://cdn.luogu.com.cn/upload/image_hosting/q8kvdjgj.png)

忽略颜色后，

* 与 $G$ 相同的有 $B$；
* 与 $H$ 相同的有 $A$；
* 与 $I$ 相同的有 $C$；
* 与 $J$ 相同的有 $D,E,F$；

答案为 $f(G)^2+f(H)^2+f(I)^2+f(J)^2=1^2+1^2+1^2+3^2=12$。

$\text{Details of Subtasks}:$

本题采用捆绑测试。

| $\text{Subtask}$ | $n<$ | $\text{Score}$ |
| :----------: | :----------: | :----------: | 
| $1$ | $10$ | $5$ |
| $2$ | $500$ | $25$ |
| $3$ | $1500$ | $30$ |
| $4$ | $4500$ | $5$ |
| $5$ | $2^{16}$ | $5$ |
| $6$ | $2^{17}$ | $5$ |
| $7$ | $2^{20}$ | $20$ |
| $8$ | $2^{25}$ | $5$ |

## 样例 #1

### 输入

```
3```

### 输出

```
12```

## 样例 #2

### 输入

```
4```

### 输出

```
812```

## 样例 #3

### 输入

```
5```

### 输出

```
223440```

## 样例 #4

### 输入

```
107```

### 输出

```
404390093```

# 题解

## 作者：小粉兔 (赞：36)

可以发现，一张图 $G$ 的 $f(G)$ 值就是它的生成树个数，即有多少棵树 $T$ 满足 $T$ 是 $G$ 的子图。

在固定点集 $V = [n]$ 的记号下，我们用简单无向图的边集来指称这张图。上面的式子可以记为 $f(G) = \sum_T [T \subseteq G]$，这里 $\sum_T$ 表示对所有树求和。

对于答案，我们有

$$
\begin{aligned}
\mathrm{Ans} &= \sum_G f(G)^2 \\
&= \sum_G \Biggl( \sum_T [T \subseteq G] \Biggr)^2 \\
&= \sum_G \sum_{T_1} \sum_{T_2} [T_1 \subseteq G] [T_2 \subseteq G] \\
&= \sum_{T_1} \sum_{T_2} \sum_G [T_1 \subseteq G] [T_2 \subseteq G] \\
&= \sum_{T_1} \sum_{T_2} \sum_G [G \supseteq T_1 \cup T_2]
\end{aligned}
$$

我们考虑一下当 $T_1, T_2$ 固定时，满足上式的 $G$ 的结构。所有可能的边有 $\binom{n}{2}$ 条，而其中 $\lvert T_1 \cup T_2 \rvert$ 条是强制选的，剩下的都可以自由决策是否加入 $G$ 中。也就是说，如上 $G$ 的数量为 $2^{\binom n 2 - \lvert T_1 \cup T_2 \rvert}$。我们继续化简答案

$$
\begin{aligned}
\mathrm{Ans} &= \sum_{T_1} \sum_{T_2} \sum_G [G \supseteq T_1 \cup T_2] \\
&= \sum_{T_1} \sum_{T_2} 2^{\binom{n}{2} - \lvert T_1 \cup T_2 \rvert} \\
&= \sum_{T_1} \sum_{T_2} 2^{\binom{n}{2} - (\lvert T_1 \rvert + \lvert T_2 \rvert - \lvert T_1 \cap T_2 \rvert)} \\
&= \sum_{T_1} \sum_{T_2} 2^{\binom{n}{2} - (n - 1) - (n - 1) + \lvert T_1 \cap T_2 \rvert} \\
&= 2^{\binom{n}{2} - (n - 1) + 1} \sum_{T_1} \sum_{T_2} 2^{-(n - \lvert T_1 \cap T_2 \rvert)} \\
&= 2^{\binom{n - 1}{2} + 1} \sum_{T_1} \sum_{T_2} (1 / 2)^{n - \lvert T_1 \cap T_2 \rvert}
\end{aligned}
$$

其中，注意把 $T_1 \cup T_2$ 改为 $T_1 \cap T_2$ 时使用了容斥原理。这里的代数变形的目的再明显不过了：如果你对 [\[WC2019\] 数树](/problem/P5206) 有印象，指数上的 $n - \lvert T_1 \cap T_2 \rvert$ 应该对你而言很熟悉——这就是图 $T_1 \cap T_2$ 的连通块数，而这恰好就是 \[WC2019\] 数树 的 $\mathrm{op} = 2$ 的情况之所欲求，即 $y$ 的连通块数次方。这里 $y$ 取 $1 / 2$。

换句话说，设 \[WC2019\] 数树 中 $(n, y, \mathrm{op}) = (n, 1/2, 2)$ 的答案为 $\mathrm{Ans}'$，则本题答案为 $\mathrm{Ans} = 2^{\binom{n - 1}{2} + 1} \cdot \mathrm{Ans}'$。

主流的对 \[WC2019\] 数树 的解法调用了多项式 exp，直接在本题中进行实现可以[获得 75 分](/record/180334182)。

若不是在 2024 年 6 月，@[NaCly_Fish](/user/115864) 对于 \[WC2019\] 数树 的 $\mathrm{op} = 2$ 的情况给出了针对 $\displaystyle [x^n] \exp \Biggl( k \sum_{i \ge 1} \frac{i^i}{i!} x^i \Biggr)$（\[WC2019\] 数树 中需要处理的核心问题）使用 $\displaystyle T(x) = \sum_{i \ge 1} \frac{i^{i - 1}}{i!} x^i$ 满足的方程 $T(x) = x \mathrm{e}^{T(x)}$ 进行化简，然后再施以另类 Lagrange 反演，从而获得形如 $\displaystyle [x^n] \exp \biggl( \frac{a x}{1 - x} + b x \biggr)$ 形式的结果（而这显然是整式递推的），我们可能永远都无法发现 \[WC2019\] 数树 背后的整式递推性。

既然 \[WC2019\] 数树 的整式递推性确立了，本题的 $\mathcal O(n)$ 甚至 $\tilde{\mathcal O}(\sqrt{n})$ 做法也就迎刃而解。在此我援引 @NaCly_Fish 的文章 [\[WC2019\] 数树 op=2 线性做法题解 & 闲话](/article/mrz7ixcb) 以供参考（例如代数推导的细节、以及具体的整式递推式）。

AC 代码如下（就是 @NaCly_Fish 在 \[WC2019\] 数树 中的提交 [R161859081](/record/161859081) 删除了 $\mathrm{op} \ne 2$ 的部分，设置 $y = 1/2$，并在输出时对答案乘了个系数），时间复杂度为 $\mathcal O(n)$。

```cpp
// credit to NaCly_Fish.
// https://www.luogu.com/article/mrz7ixcb
// Code from <https://www.luogu.com.cn/record/161859081>

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<set>
#include<vector>
#define ll long long
#define p 998244353
#define N 67109000
using namespace std;

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

int inv[N],fac[N];

void init(int n){
    fac[0] = fac[1] = inv[1] = 1;
    for(int i=2;i<=n;++i){
        fac[i] = (ll)fac[i-1]*i%p;
        inv[i] = -(ll)(p/i)*inv[p%i]%p;
    }
}

int coef(int a,int b,int n){ // n! [x^n] exp(ax/(1-x) + bx)(1-x)
    static int f[N];
    f[0] = 1,f[1] = a+b,f[2] = (a + (ll)inv[2]*(a+b)%p*(a+b))%p;
    for(int i=2;i<n;++i) f[i+1] = ((a+b+2ll*i)*f[i] - (2ll*b+i-1)*f[i-1] + (ll)b*f[i-2])%p*inv[i+1]%p;
    return (ll)(f[n]-f[n-1])*fac[n]%p;
}

int solve2(int n,int y){
    int a = (ll)n*n%p*y%p*power(1-y,p-2)%p,b = n;
    int res = (ll)coef(a,b,n)*power(1-y,n)%p*power(n,p-5)%p;
    return (res+p)%p;
}

int n,y,op;

int main(){
    init(33555000);
    scanf("%d",&n);
    y=(p+1)/2;
    printf("%d",(int)((ll)solve2(n,y)*power(2,(int)(((ll)(n-1)*(n-2)/2+1)%(p-1)))%p));
    return 0;
}
```

我个人对出题人 @[Argon_Cube](/user/372983) [在明知 @NaCly_Fish 的文章的情况下，未确认本题的题意经过简单的处理后与 \[WC2019\] 数树 完全一致](/discuss/949820#:~:text=%E6%88%91%E7%9C%8B%E8%BF%87%E4%BA%86%E7%A5%9E%E9%B1%BC%E5%9C%A8%E6%9C%AC%E9%A2%98%E7%9A%84%E9%A2%98%E8%A7%A3%EF%BC%8C%E4%BD%86%E6%98%AF%E7%9C%8B%E5%88%B0%E8%83%BD%E7%94%A8%E8%BF%99%E4%B8%AA%20Trick%20%E4%BC%98%E5%8C%96%E8%87%AA%E5%B7%B1%E7%9A%84%E9%A2%98%E5%B0%B1%E8%B7%91%E4%BA%86%EF%BC%8C%E6%B2%A1%E6%9C%89%E4%BB%94%E7%BB%86%E7%9C%8B%E8%BF%87%E5%8E%9F%E9%A2%98%E9%9D%A2)的非专业精神表示批评，对 @NaCly_Fish 明知题意完全一致却以普及的目的未阻止本题的出现表示 ![](https://cdn.luogu.com.cn/upload/image_hosting/3wjw1hii.png)。

---

## 作者：Argon_Cube (赞：9)

Official Solution By Argon_Cube.

考虑所求式子的组合意义，就是从所有 $n$ 个点的树中选两个（可以重复），在两棵树上分别加边得到同一个图的方案数。 

那么我们枚举这两棵树，显然能够自由决定加不加的边只有在两棵树中都不出现的边（其它的边必须要加）。那么如果在两棵树中都出现的边（下文我们称这种边为紫边，只在第一棵树中出现的叫蓝边，只在第二棵树中出现的叫红边）有 $x$ 条，那么将它们分别加边得到同一个图的方案数为 $2^{\binom n2-(2n-2)+x}$。

现在我们发现如果将所有的紫边单独提出来，就会形成一个大小为 $n$ 的森林，设这个森林有 $m$ 个连通块，显然紫边就有 $n-m$ 条。

设选出两棵树使得紫边形成的森林恰好包含 $m$ 个连通块的方案数为 $g_m$ 则答案就是

$$2^{\binom n2-n+2}\sum_{i}2^{-i}g_i$$

现在问题就是，我们既没有办法在不求出每个 $g_i$ 的情况下直接算出整个和式，也没有办法直接求出每个 $g_i$，因为恰好这个限制非常烦人。那么就考虑算至多有 $m$ 个紫边连通块的方案数 $f_m$，我们钦定 $m$ 个连通块，每个紫边连通块内部是任意的无根树。连通块之间，我们需要算将大小为 $a_1,\cdots,a_m$ 的连通块连成树的方案数。这个方案数要平方，因为蓝边和红边各需要一种连边方式。

将一些连通块加边连通的方案计数就是 [CF156D Clues](https://www.luogu.com.cn/problem/CF156D)，结论是当 $m>1$ 时方案数为

$$n^{m-2}\prod_{i=1}^ma_i$$

注意 $m=1$ 时方案数为 $1$。注意到这是个很简单的形式，考虑用暴力方法计数：枚举每个连通块的大小，因为连通块之间没有顺序所以要除以 $m!$。显然 $f_1=n^{n-2}$，当 $m>1$ 时

$$
\begin{aligned}
f_m&=\frac{1}{m!}\sum_{\sum a=n,|a|=m,a_i>0}\binom{n}{a_1,\cdots,a_m}\prod_{i=1}^ma_i^{a_i-2}\left(n^{m-2}\prod_{i=1}^ma_i\right)^2\\
&=\frac{n^{2m-4}n!}{m!}\sum_{\sum a=n,|a|=m,a_i>0}\prod_{i=1}^m\frac{a_i^{a_i}}{a_i!}
\end{aligned}$$

到这里就比较显然了，设 $F(x)=\sum_{i>0}(i!)^{-1}i^ix^i$ 那么 $f_m=\frac{n^{2m-4}n!}{m!}[x^n]F^m$。对 $1\leq m\leq n$ 求出 $[x^n]F^m$ 用 Bostan-Mori 算法即可，详见[多项式复合逆](https://www.luogu.com.cn/article/t2cijmdo)。

但是我们现在要求的是 $g_m$，考虑容斥（二项式反演）：考虑得到 $g_i$ 在 $f_m$ 中被算了几次，对于每一种恰好有 $i$ 个紫连通块的方案，一共有 $n-i$ 条紫边，但在 $f_m$ 中只枚举了 $n-m$ 条紫边（多出来的紫边是红边和蓝边重合导致的），那么我们枚举在 $f_m$ 中实际枚举的是哪些紫边，就有：

$$f_m=\sum_i g_i\binom{n-i}{n-m}$$

这样基本就做完了，发现可以用卷积从 $g$ 算出 $f$ 那么同理用多项式求逆就能从 $f$ 算出 $g$。或者你可以用二项式反演：

$$g_{m}=\sum_i (-1)^{m-i}\binom{n-i}{n-m}f_{i}$$

直接做多项式乘法即可。无论怎样总复杂度都是 BM 的 $\mathrm O(n\log^2 n)$。

---

Inspired by [NaCly_Fish's Blog](https://www.luogu.com/article/mrz7ixcb).

发现 $F$ 的形式非常简洁特殊，是否有更快的方法求出 $[x^n]F^m$ 呢？

考虑有标号有根树的 EGF $T(x)=\sum_{i>0}i^{i-1}x^i(i!)^{-1}$，有 $T=x\exp T,F=xT'$。

注意到

$$T=x\exp T\implies T'=\exp T+xT'\exp T=x^{-1}T+T'T\implies F=\frac{T}{1-T}$$

并且显然 $T$ 有复合逆 $xe^{-x}$，得到 $F$ 的复合逆 $G=\dfrac{x}{x+1}\exp\dfrac{-x}{x+1}$。于是拉格朗日反演得

$$[x^n]F^m=\frac mn[x^{n-m}](1+x)^ne^{\frac{nx}{1+x}}=\frac mn[x^{n-m}]H(x)$$

$H$ 显然就是微分有限的，具体来说 $(1+x)^2H'=n(2+x)H$，提取系数递推即可不借助 Bostan-Mori 求出 $[x^n]F^m$。这样就只需要最后的一次卷积，时间复杂度 $\mathrm O(n\log n)$。

$g$ 很有可能也是 D-finite 的，但是这个猜想还未被证明。

然后就被 NaCly_Fish 爆标了。

可以发现 $g$ 我们很难推出来整式递推，那我们直接跳过这一步然后交换求和顺序：

$$
\begin{aligned}
&2^{\binom n2-n+2}\sum_{0<i\leq n}f_i\sum_{0\leq m\leq n}2^{-m} (-1)^{m-i}\binom{n-i}{n-m}\\
=&(-1)^n2^{\binom n2-2n+2}\sum_{0<i\leq n}(-1)^if_i\sum_{0\leq m\leq n}(-2)^{m} \binom{n-i}{m}\\
=&2^{\binom n2-2n+2}\sum_{0<i\leq n}f_i\\
\end{aligned}
$$

然后就 $\Omicron(n)$ 了。

$$
\begin{aligned}
&\sum_{0<i\leq n}f_i\\
=&n^{n-2}+(n-1)!n^{-4}\sum_{0\leq m\leq n}[x^{m}](xe^{n^2x}-x)[x^{n-m}]H(x)\\
=&n^{n-2}+(n-1)!n^{-4}[x^{n}]G(x)H(x)\\
\end{aligned}
$$

注意到 $G(x)=xe^{n^2x}-x$ 显然是 D-finite 的，所以 $GH$ 也是 D-finite 的，于是可以使用整式递推做到 $\Omicron(\sqrt n\log n)$。

---

