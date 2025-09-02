# Scarlet loves WenHuaKe

## 题目背景

Scarlet上大学了，在此之前，她加强了一道高考模拟题QAQ

## 题目描述

Scarlet尝试在 $n$ 行 $m$ 列的中国象棋棋盘上放置 $2\times n$ 个炮，使得它们互不攻击。

大家都知道 Scarlet 沉迷搞事，她想问你有多少个方案。

## 说明/提示

对于 $20\%$ 的数据，$n,m\leq5$；

对于另 $25\%$ 的数据，$n,m\leq2000$；

对于另 $20\%$ 的数据，$n=m$；

对于剩下的 $35\%$ 的数据，$m-n\leq10$；

对于 $100\%$ 的数据，有 $1\leq n\leq m\leq100000$。

## 样例 #1

### 输入

```
4 4```

### 输出

```
90```

# 题解

## 作者：ez_zjt (赞：12)

似乎见到的做法都是多项式$\ln \exp$的（

然而通过一些简单容斥可以轻易做到只用一次卷积，也并不需要对二分图结构进行奇怪讨论（

显然每行都有两枚石子。考虑枚举有两枚石子的列数，设其中$k$列有两枚石子，则有$2(n-k)$列有一枚石子，$m-2n+k$列为空。此时问题可以转化为二分图模型，左边有$n$个点，每个点度数为$2$，右边有$k$个点度数为$2$，$2(n-k)$个点度数为$1$，我们需要统计这个图的合法匹配数量（每个点恰好连出对应度数的边，且两个点之间最多连一条边）。

考虑将所有度数为$2$的点拆成两个度数为$1$的点，此时左右各有$2n$个点。如果直接在这$4n$个点之间连边，可能会出现重边的情况（设左边点$a$与点$b$原本同属于一个点，右边点$c$与点$d$原本同属于一个点，如果$(a,c),(b,d)$或$(a,d),(b,c)$连边，则对应原图中的重边情况）。可以用容斥去掉这一类情况，枚举重边的数量$i$，则总的匹配数量为：

$$S_k=\frac 1{2^{n+k}}\sum_i(-1)^i\binom ni\binom kii!2^i(2(n-i))!$$

这里的$2^i$是因为每一条重边在拆点后的新图中有两种连法，最后除以$2^{n+k}$是因为每一组拆出来的点交换顺序并不影响对应到原图中的连边方案。注意到$S_k$右边的和式只跟$\binom ki$有关，因此可以卷积计算，复杂度$O(n\log n)$。总答案为：

$$Ans=\sum_k\binom mk\binom {m-k}{2(n-k)}S_k$$

---

## 作者：zj余能 (赞：12)

[博客链接](https://www.cnblogs.com/Dance-Of-Faith/p/10216658.html)

一道好题，第一次用生成函数做题。感谢赛珂狼教我这个做法。
这个做法是和$m-n$无关的，可以把那个$\le10$的限制去掉。。。

首先我们显然可以把题目中的限制转化成一个二分图的模型：左边有$n$个点，右边有$m$个点，如果在棋盘$(i,j)$这个点上放了炮，那么我们把左边第$i$个点向右边第$j$个点连边，那么最终这个图上左边每个点的度数都是$2$，右边每个点的度数都小于等于$2$。求合法图的个数。
可以发现，这个二分图是由一些环和一些链组成的，每一条链都是属于右边的点数比属于左边的点数多一（我们把属于右边的单独的一个点也算作一条链）。并且这样链的条数恰好为$m-n$。
对于每条链或者每一个环，一旦分配给它的点固定后，其内部的方案数就和外部无关了，只和该链（环）的大小有关。
我们先计算有关于链的部分。

我们定义函数$g_n$表示左边有$n-1$个点，右边有$n$个点的一条链内部排列的方案数。那就有：
$$g = <0, 1, 1, 6, \dots, \frac{n!(n-1)!}{2}>$$
简述上述式子的由来，左边$n-1$个点有排列$(n-1)!$，右边$n$个点有排列$n!$，乘起来之后左右对称要除以$2$。我们构造一个生成函数把$g$挂上去，表示有一条链的情况：
$$G(x) = \sum_{n} g_n \frac{x^n}{n!(n-1)!}$$
如果有两条链我们就把它自己卷一下，并且用$g^{(2)}$来表示新得到的数列：
$$G^2(x) = \sum_{n} \left( \sum_{i = 0}^{n} \binom{n}{i} \binom{n - 2}{i - 1} g_i g_{n - i} \right) \frac{x^n}{n!(n-2)!}$$
$$G^2(x) =\sum_{n} g^{(2)}_n \frac{x^n}{n!(n-2)!}$$
注意到这个生成函数的形式和$G(x)$相比有些许变动，即在$x^n$下的系数有改动，这是因为在两条链的时候右边的点数会比左边的点数多二，而不是一。于是更一般的，如果有$k$条链，就可以写成以下形式：
$$G^k(x) = \sum_{n} g^{(k)}_n \frac{x^n}{n!(n-k)!}$$
其中数列$g^{(m-n)}$就是我们想要的有恰好$m-n$条链的时候的方案数。但是细心的读者可以发现这里有一个小问题，就是我们在做卷积的过程中，我们每卷一次就会增加一条链，这相当于枚举了新加入的链的位置，于是在每一个合法的情况中，这$m-n$条链的加入顺序不同会被算成不同的方案，于是最终我们需要的应该是数列$\frac{g^{(m-n)}}{(m-n)!}$。
理解这一点很重要，我们在计算环的时候同样需要用到这一点，请大家自行揣摩。
我们知道了$G(x)$，于是我们只要求出$G^{m-n}(x)$就行了，直接快速幂可以$O(mlog^2m)$，如果比较厉害写$O(mlogm)$的多项式快速幂也是可以的。

接下来我们算环的部分。
我们定义函数$f_n$表示左右边都有$n$个点的环内部排列的方案数，那就有：
$$f = <0, 0, 1, 6, \dots ,\frac{(n!)^2}{2n}>$$
简单说明上述式子的由来，左右边分别有圆排列$(n-1)!$，合并起来有$n$中方案，同时镜像对称要除以$2$。同时，这里有特殊情况$f_1=0$，因为你不能有一个两个点的环。这里有读者会发现，我们定义了$f_0 = 0$，这是因为我们接下来做卷积时必须保证每次选择环的大小时不能用一个空环（也就是会导致实际环的个数会少一）。
同样我们构造了一个生成函数，表示一个环的情况：
$$F(x) = \sum_{n} f_n \frac{x^n}{(n!)^2}$$
与链同理，如果我们用了$k$个环，就有：
$$F^k(x) = \sum_{n} f^{(k)}_n \frac{x^n}{(n!)^2}$$
与链同理，每一种用了$k$个环的合法情况会被重复计算到$k!$次，我们要除掉它，同时我们需要枚举我们用的环的个数$k$，于是我们需要的是：
$$H(x) = \sum_{k} \frac{F^k(x)}{k!} = e^{F(x)}$$

虽然我不会多项式$exp$，但是这里的形式比较简单我们可以手推。
我们需要先求出$F(x)$的一个比较简单的形式。根据$f$我们可以写出：
$$F(x) = -\frac{x}{2} + \frac{1}{2} \sum_n \frac{x^n}{n} = -\frac{x}{2} - \frac{1}{2} ln(1 - x)$$

于是有：

$$H(x) = \sum_n h_n \frac{x^n}{(n!)^2} = e^{F(x)} = e^{-\frac{1}{2} x} e^{-\frac{1}{2} ln(1-x)} = e^{-\frac{1}{2}x} (1-x)^{-\frac{1}{2}}$$

前半部分用$e$直接展开：

$$e^{-\frac{1}{2}x} = \sum_n (-\frac{1}{2})^n \frac{x^n}{n!}$$

后半部分用广义二项式展开：

$$(1-x)^{-\frac{1}{2}} = \sum_n \frac{(-\frac{1}{2})^{\underline{n}}}{n!} (-1)^n x^n$$

把这两个卷起来就得到了$H(x)$。

最后我们需要把链和环拼起来，这一步做卷积或手动展开都可以了。
总复杂度是$O(mlogmlog(m-n))$，或者$O(mlogm)$。于是就和$m-n$无关了。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> Poly;

const int N = (int)1e5 + 5;
const int MOD = 998244353;
const int _IV2 = (MOD - 1) / 2;

int n, m;

namespace {
  int fac[N], ifac[N];
  int Add(int a, int b) { return (a += b) >= MOD? a - MOD : a; }
  int Sub(int a, int b) { return (a -= b) < 0? a + MOD : a; }
  int Mul(int a, int b) { return (long long)a * b % MOD; }
  int Pow(int a, int b) {
    int r = 1;
    for (; b; b >>= 1, a = Mul(a, a)) if (b & 1) r = Mul(r, a);
    return r;
  }
  void Math_Init() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = Mul(fac[i - 1], i);
    ifac[N - 1] = Pow(fac[N - 1], MOD - 2);
    for (int i = N - 2; ~i; --i) ifac[i] = Mul(ifac[i + 1], i + 1);
  }
}

namespace PO {
  int rev[(int)1e6 + 5];
  void Dft(Poly &a, int le) {
    for (int i = 0; i < le; ++i)
      if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int i = 1; i < le; i <<= 1) {
      int wn = Pow(3, (MOD - 1) / (i << 1));
      for (int j = 0; j < le; j += i << 1) {
        int w = 1, x, y;
        for (int k = 0; k < i; ++k, w = Mul(w, wn)) {
          x = a[j + k];
          y = Mul(a[j + k + i], w);
          a[j + k] = Add(x, y);
          a[j + k + i] = Sub(x, y);
        }
      }
    }
  }
  void Idft(Poly &a, int le) {
    reverse(a.begin() + 1, a.end());
    Dft(a, le);
    int iv = Pow(le, MOD - 2);
    for (int i = 0; i < le; ++i) a[i] = ::Mul(a[i], iv);
  }
  Poly Mul(Poly a, Poly b, int lim) {
    int n = a.size(), m = b.size(), l;
    for (l = 1; l < n + m - 1; l <<= 1);
    for (int i = 0; i < l; ++i)
      rev[i] = (rev[i >> 1] >> 1) | (i & 1? l >> 1 : 0);
    a.resize(l), Dft(a, l);
    b.resize(l), Dft(b, l);
    for (int i = 0; i < l; ++i) a[i] = ::Mul(a[i], b[i]);
    Idft(a, l), a.resize(lim);
    return a;
  }
  Poly Pow(Poly a, int b, int lim) {
    Poly r(lim);
    for (r[0] = 1; b; b >>= 1) {
      if (b & 1) r = Mul(r, a, lim);
      a = Mul(a, a, lim);
    }
    return r;
  }
}

int main() {
  Math_Init();
  scanf("%d%d", &n, &m);
  
  Poly F0(m + 1), F1(m + 1), fm(m + 1);
  for (int i = 0, dw = 1; i <= m; ++i) {
    F0[i] = Mul(dw, ifac[i]);
    if (i & 1) F0[i] = Sub(0, F0[i]);
    dw = Mul(dw, Sub(_IV2, i));
  }
  for (int i = 0, pw = 1; i <= m; ++i) {
    F1[i] = Mul(pw, ifac[i]);
    pw = Mul(pw, _IV2);
  }
  Poly expF = PO::Mul(F0, F1, m + 1);
  for (int i = 0; i <= m; ++i) {
    fm[i] = Mul(expF[i], Mul(fac[i], fac[i]));
  }

  Poly G(m + 1), gk(m + 1);
  G[1] = 1;
  for (int i = 2; i <= m; ++i) {
    G[i] = (MOD + 1) / 2;
  }
  G = PO::Pow(G, m - n, m + 1);
  for (int i = m - n; i <= m; ++i) {
    gk[i] = Mul(Mul(G[i], Mul(fac[i], fac[i - m + n])), ifac[m - n]);
  }

  int ans = 0;
  for (int i = 0; i <= n; ++i) {
    int ch1 = Mul(fac[m], Mul(ifac[i], ifac[m - i]));
    int ch2 = Mul(fac[n], Mul(ifac[i], ifac[n - i]));
    ans = Add(ans, Mul(Mul(fm[i], gk[m - i]), Mul(ch1, ch2)));
  }
  printf("%d\n", ans);
  return 0;
}

```
 

这里简单讲一下为什么有$\sum_{n=1} \frac{x^n}{n} = -ln(1-x)$。

根据定义有：$ln'(x) = \frac{1}{x}$

根据导数的复合：$(ln(1-x))' = ln'(1-x)(1-x)' = \frac{-1}{1-x} = -\sum_n x^n$

对两边积分：$ln(1-x) = -\sum_{n=1} \frac{x^n}{n}$

---

## 作者：NaCly_Fish (赞：9)

原题是不限制炮数，这里给生成函数增加一元以计量炮数，大概算是扩展吧。（而且要求原题只需令计量炮数的元为 $1$ 即可）
****
沿着 yhx 奆佬的思路，我们直接设要求摆恰好 $k$ 个炮的情况。此题中 $k=2n$ 的情况较为简单，这里我们考虑更普遍的情况。

首先来复读一下组合推导，一样是用二分图建模，转化为计数：左边 $n$ 个点，右边 $m$ 个点，连恰好 $k$ 条边，图中只有链与环的有标号二分图。

1. 还是先来考虑环，记 $n!m![x^ny^mz^k] R$ 为对环的计数。由于环上连接的点必须是二分图上左右交替，点数应当相同。又由于是环排列，总数要除以 $2n$，得到
$$R=\sum_{n=2}^\infty \frac{(n!)^2}{2n}\times \frac{x^ny^nz^{2n}}{(n!)^2}$$
$$=\frac 12\sum_{n=2}^\infty \frac{(xyz^2)^n}{n}=-\frac 12(\ln(1-xyz^2)+xyz^2)$$


2. 对于有偶数个点的链，两边包含的点数也是相同的，仿照刚才的思路直接列出
$$C_e=\sum_{n=1}^\infty  (n!)^2 \times \frac{x^ny^nz^{{2n-1}}}{(n!)^2}=\frac{xyz}{1-xyz^2}$$
3. 有奇数个点的链的首尾都在一侧节点上，还按照刚才的做法得到左边 $n$ 个，右边 $n+1$ 个点的链会有 $n!(n+1)!$ 个 —— 但链是不分正反的，首尾相同时无法区分，所以对 $n\geq 1$ 时要除 $2$。

$$C_o=x+y+\frac 12\sum_{n=1}^\infty n!(n+1)!z^{2n} \frac{x^ny^{n+1}+x^{n+1}y^n}{n!(n+1)!}$$
$$=(x+y)\frac{2-xyz^2}{2-2xyz^2}$$

然后答案的生成函数就是 $\exp(R+C_e+C_o)$。这个三元生成函数看着就让人头大，以下内容基本口胡，如有错误请毫不留情地指出。

****
根据某个技巧的扩展，$\exp R$ 的系数都是形如 $x^iy^iz^{2i}$ 的，我们只需要把 $\exp(C_e+C_o)$ 中形如 $x^{n-i}y^{m-i}z^{k-2i}$ 的系数提出来即可。  
设 $d_1=m-n$，$d_2=2n-k$，要提的系数可改写为 $x^iy^{i+d_1}z^{2i-d_2}$。将 $\exp(C_e+C_o)$ 展开得到
$$\sum_{i=0}^\infty \frac{1}{(1-xyz^2)^ii!}\sum_{j=0}^i \binom ij (xyz)^{i-j} (x+y)^j(2-xyz^2)^j2^{-j}$$
注意到「乘只含 $xyz^2$ 的项」这个操作，并不改变其中的项「是否属于我们要提取的」这一性质。  

令 $j=2t+d_1$，则从 $(x+y)^j$ 中即可提取出 $x^ty^{t+d_1}$ 的项，是我们要的一部分；$(xyz)^{i-j}$ 中提供的 $x^{i-j}y^{i-j}$ 项也不影响 $y,x$ 指数差为 $d_1$，故只需保证 $x$ 指数的二倍减去 $z$ 的指数为 $d_2$，也就是 $2(t+i-j)-(i-j)=d_2$，化简得 $i=d_2+d_1$。  

于是把我们要提取的系数拿出来，就组成了下式。为方便表示，记 $c=d_1+d_2$。
$$\frac{1}{(1-xyz^2)^cc!}\sum_{t\geq0} \binom c{2t+d_1}\binom{2t+d_1}{t}x^ty^{t+d_1}(xyz)^{c-2t-d_1}(1-xyz^2/2)^{2t+d_1}$$
看起来还是很复杂，但做换元 $u=xyz^2$ 就能化简为
$$\frac{x^{d_2}y^cz^{d_2}}{(1-u)^cc!}\sum_{t\geq 0} \binom{c}{2t+d_1} \binom{2t+d_1}{t}u^{-t}(1-u/2)^{2t+d_1}$$
这个 $u$ 的负指数看起来很诡异，但把它扔到 mma 里算出来确实是对的，，现在可以设
$$F(u) = \frac{(1-u/2)^{d_1}}{(1-u)^c}\sum_{t\geq 0 } \binom{c}{2t+d_1} \binom{2t+d_1}{t} u^{-t}(1-u+u^2/4)^{t}$$
前面这个分式显然微分有限，先考虑后面：
$$G(u) = \sum_{t\geq 0 } \binom{c}{2t+d_1} \binom{2t+d_1}{t} (u^{-1}-1+u/4)^{t}$$
这是一个超几何级数和一个有理分式的复合，$G(u)$ 就是微分有限的，于是 $F(u)$ 是微分有限的。

现在倒回来看 $\exp R$，有
$$\mathcal R(u)=\exp R = \frac{\text e^{-u/2}}{\sqrt{1-u}}$$
显然 $\mathcal R(u)$ 也是微分有限的，最终答案也微分有限，可以做到 $\Theta(n)$ 或 $\Theta(\sqrt n \log n)$。

ps：我知道你想要什么。最终答案为
$$n!m^{\underline{k-n}}[u^{k-n}] \left( \frac{\text e^{-u/2}(1-u/2)^{d_1}}{(1-u)^{c+1/2}} \sum_{t\geq 0} \binom{c}{2t+d_1}\binom{2t+d_1}{t}(u^{-1}-1+u/4)^t\right)$$
![](https://cdn.luogu.com.cn/upload/image_hosting/4w8auizl.png)
****
其实整篇题解都只是依葫芦画瓢，最后再膜一发奆佬 yhx。



---

## 作者：H_W_Y (赞：7)

> 好题，牛牛的一个套路。 —— <font color = black>$\textsf H$</font><font color = red>$\textsf {anghang}$</font>

给一种组合数学做法。



首先，容易发现每行恰好有两个棋子，而每列最多有两个棋子，那么答案就是把 $n$ 种棋子，每种两个，放入 $m$ 个无序二元组的方案数，每组元素不同，可以留空。

但是留空又是非常不好处理的，所以我们再进行转化，变成将 $m$ 种棋子，每种两个，放入 $n$ 个无序二元组且每组元素不相同的方案数（不一定要放完）。

我们记它为 $f(n,m)$，这就是我们想要求的答案。



**无序** 和 **二元组元素不相同** 的这两个限制都是不太好处理的，所以我们考虑把这两个东西去掉，

设 $g(n,m)$ 表示把 $m$ 种颜色的球，每种两个，放入 $2 \times n$ 个格子里面的方案数（格子有序），不一定要放完。

于是我们来枚举多少种颜色是放了两个的，多少种颜色只放了一个或者没有放，于是有
$$
g(n,m) = (2n)! \sum_{i=0}^{\min(m-n,n)} \frac {\binom m {n-i} \binom {m-n+i} {2i}} {2^{n-i}}
$$
上面的式子枚举了 $n-i$ 种颜色的球放了两个，所以有 $\binom {m} {n-i}$ 种选法，而剩下的 $m-n+i$ 种球放了一种或者根本没有放，而剩下的格子数量是 $2i$ 种，所以贡献是 $\binom {m-n+i} {2i}$。

在这里我们放球的方法是让前 $2n-2i$ 个格子放 $n-i$ 种颜色的球，每种两个，后面的 $2i$ 放其他颜色，而由于格子有序，所以要乘上 $(2n)!$。

由于前面相同颜色的球之间的交换是没有贡献的，所以我们需要除以 $2^{n-i}$。



同时，我们发现 $g(n,m)$ 也是可以用 $f(n,m)$ 表示出来的，具体来说，我们去枚举有多少个二元组的元素是相同的，还需要注意有序二元组和无序二元组的转化，也就是
$$
g(n,m) = \sum_{i=0}^{n} \binom n i A_{m}^{i} 2^{n-i} f(n-i,m-i)
$$
其中 $2^{n-i}$ 是让 $f(n-i,m-i)$ 中的二元组有序，而 $A_m^i$ 是给选出来的 $i$ 个相同二元组的球的颜色定序。

进行一些化简，我们得到
$$
\begin{aligned}
g(n,m) = & \sum_{i=0}^n \binom n i \frac {m!} {(m-i)!} 2^{n-i} f(n-i,m-i)
\\
\frac {g(n,m)} {m!} = & \sum_{i=0}^n \binom n i \frac {2^{n-i} f(n-i,m-i)} {(m-i)!}
\end{aligned}
$$
发现这里面的 $g$ 和 $f$ 所用到的 $n,m$ 之差是相同的，所以我们考虑换元，设
$$
\begin{aligned}
G(i) = & \frac {g(i,i-n+m)} {(i-n+m)!}
\\
F(i) = & \frac {2^i f(i,i-n+m)} {(i-n+m)!}
\end{aligned}
$$
于是原式就变成
$$
\begin{aligned}
G(n) = & \sum_{i=0}^n \binom n i F(n-i)
\\
= & \sum_{i=0}^n \binom n i F(i)
\end{aligned}
$$
这个形式就是一个标标准准的 **二项式反演** 的形式，那么我们想求的 $F(i)$ 就是
$$
\begin{aligned}
F(n) = & \sum_{i=0}^n \binom n i (-1)^{n-i} G(i) 
\\
= & \sum_{i=0}^n \binom n i (-1)^i G(n-i)
\end{aligned}
$$
那么
$$
\begin{aligned}
\frac {2^n f(n,m)} {m!} = & \sum_{i=0}^n (-1)^i \binom n i \frac {g(n-i,m-i)} {(m-i)!}
\\
f(n,m) = & \frac {m!} {2^n} \sum_{i=0}^n (-1)^i \binom n i \frac {g(n-i,m-i)} {(m-i)!}
\end{aligned}
$$
每次求 $g$ 的时间复杂度是 $\mathcal O(\min(m-n,n))$，所以总时间复杂度 $\mathcal O(\min (m-n,n) n)$。



```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5,H=998244353;
int n,m,fac[N],ifac[N],two[N],inv2;

int adc(int a,int b){return a+b>=H?a+b-H:a+b;}
int dec(int a,int b){return a<b?a-b+H:a-b;}
int mul(int a,int b){return 1ll*a*b%H;}
void add(int &a,int b){a=adc(a,b);}
void del(int &a,int b){a=dec(a,b);}

int qpow(int a,int b=H-2){
  int res=1;
  while(b){if(b&1) res=mul(res,a);a=mul(a,a),b>>=1;}
  return res;
}

void init(){
  fac[0]=two[0]=1;inv2=qpow(2);
  for(int i=1;i<N;i++) fac[i]=mul(i,fac[i-1]),two[i]=mul(inv2,two[i-1]);
  ifac[N-1]=qpow(fac[N-1]);
  for(int i=N-1;i>=1;i--) ifac[i-1]=mul(i,ifac[i]);
}

int binom(int n,int m){
  if(m<0||n<m) return 0;
  return mul(fac[n],mul(ifac[m],ifac[n-m]));
}

int g(int n,int m){
  int res=0;
  for(int i=0;i<=min(m-n,n);i++) add(res,mul(mul(binom(m,n-i),binom(m-n+i,2*i)),two[n-i]));
  return mul(res,fac[2*n]);
}

int f(int n,int m){
  int res=0;
  for(int i=0;i<=n;i++){
	if(i&1) del(res,mul(binom(n,i),mul(g(n-i,m-i),ifac[m-i])));
	else add(res,mul(binom(n,i),mul(g(n-i,m-i),ifac[m-i])));
  }
  return mul(mul(fac[m],two[n]),res);
}

int main(){
  /*2024.5.25 H_W_Y P4831 Scarlet loves WenHuaKe 二项式反演*/
  init();
  scanf("%d%d",&n,&m);
  printf("%d\n",f(n,m));
  return 0;
}
```

---

## 作者：ZillionX (赞：3)

# Description

给定 $n,m$，询问在 $n \times m$ 的中国象棋棋盘上放置 $2\times n$ 个炮使得它们互不攻击的方案数。

$n,m \times 10^5$，时限 1s。

# Solution

一道没人做的神仙题。

可以发现每行都恰好有 $2$ 个炮，每列至多有 $2$ 个炮。考虑枚举有 $2$ 个炮的列数，设其为 $i$ 个，那么有 $2n-2i$ 列有 $1$ 个炮，$m-2n+i$ 列无棋子。

注意到这种棋盘题的一贯套路是转化为二分图模型，左边的点表示行，右边的表示列，那么左边有 $n$ 个点，右边有 $2n-i$ 个点。左边的点度数都为 $2$，右边有 $i$ 个点度数为 $2$，$2n-2i$ 个点度数为 $1$，方案数就是图的合法匹配数量。

这么搞不好算，考虑拆点，将度数为 $2$ 的点拆成两个，但是直接算可能会有重复（被拆出来的两组点间连边，即原图中重边），那么考虑容斥。

设 $f(i)$ 表示有 $i$ 列有两个炮的方案数，有

$$f(i)=\frac{1}{2^{n+i}} \sum_{j=0}^i (-1)^j\dbinom{i}{j} \dbinom{n}{j} j! 2^j  (2n-2j)!$$

对于每个拆出来的点都会给答案两次贡献，所以乘上 $\dfrac{1}{2^{n+i}}$。而重复的 $j$ 个点与右边共有 $2^j j!$ 种组合方式，剩余点的匹配数有 $(2n-2j)!$ 种。

可以发现是卷积的形式，那么 NTT 即可。

最终答案为 $m$ 列中选 $i$ 列放两个炮，$2n-2i$ 个列放一个炮，即

$$\sum_{i=0}^n \dbinom{m}{i} \dbinom{m-i}{2n-2i} f(i)$$

# Code

```cpp
typedef long long LL;

const int N=4e5+5;
const LL mod=998244353;

int n,m;
LL Ans,tr[N],f[N],g[N],fac[N],inv[N],ifac[N];

LL Qpow(LL x,LL y) {
	LL Mul=1;
	while (y) {
		if (y&1) Mul=Mul*x%mod;
		x=x*x%mod,y>>=1;
	}
	return Mul;
}

const LL inv_g=Qpow(3,mod-2);

void MkTr(int n) {
	for (int i=0;i<n;i++)
		if (i&1) tr[i]=(tr[i>>1]>>1)|(n>>1);
		else tr[i]=tr[i>>1]>>1;
}

void NTT(LL *f,int n,bool u) {
	MkTr(n);
	for (int i=0;i<n;i++)
		if (i<tr[i]) swap(f[i],f[tr[i]]);
	for (int i=2;i<=n;i<<=1) {
		int l=i>>1;
		LL p;
		if (u) p=Qpow(3,(mod-1)/i);
		else p=Qpow(inv_g,(mod-1)/i);
		for (int j=0;j<n;j+=i) {
			LL buf=1;
			for (int k=j;k<j+l;k++) {
				LL gt=buf*f[k+l]%mod;
				f[k+l]=((f[k]-gt)%mod+mod)%mod;
				f[k]=(f[k]+gt)%mod;
				buf=buf*p%mod;
			}
		}
	}
	if (!u) {
		LL inv_n=Qpow(n,mod-2);
		for (int i=0;i<n;i++) f[i]=f[i]*inv_n%mod;
	}
}

void Mul(int m,LL *f,LL *g) {
	int n=1;
	while (n<(m<<1)) n<<=1;
	static LL t[N];
	memcpy(t,g,n<<3);
	NTT(f,n,1),NTT(t,n,1);
	for (int i=0;i<n;i++) f[i]=f[i]*t[i]%mod;
	NTT(f,n,0);
	memset(f+m,0,(n-m)<<3),memset(t,0,n<<3);
}

void Init(int n) {
	fac[0]=inv[1]=ifac[0]=1;
	for (int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	for (int i=2;i<=n;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for (int i=1;i<=n;i++) ifac[i]=ifac[i-1]*inv[i]%mod;
}

LL C(int n,int m) {
	if (n<m) return 0;
	return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

int main() {
	scanf("%d%d",&n,&m);
	Init(max(n*2,m));
	for (int i=0;i<=n;i++) {
		if (i&1) f[i]=(mod-C(n,i)*Qpow(2,i)%mod*fac[n*2-i*2]%mod)%mod;
		else f[i]=C(n,i)*Qpow(2,i)%mod*fac[n*2-i*2]%mod;
		g[i]=ifac[i];
	}
	Mul(n+1,f,g);
	
	for (int i=0;i<=n;i++)
		Ans=(Ans+f[i]*fac[i]%mod*Qpow(2,(mod-2)*(n+i)%(mod-1))%mod*C(m,i)%mod*C(m-i,n*2-i*2)%mod)%mod;
	
	printf("%lld",Ans);
	
	return 0;
}
```


---

## 作者：liuenyin (赞：1)

提供一种可能更容易理解，不涉及太多式子的方法。

### 思路

由于摆放 $2n$ 个炮，因此每行一定是恰好两个炮的。假设我们已知前 $m-1$ 列的摆放方案数，考虑对第 $m$ 列的摆放情况做分类讨论。

首先，如果第 $m$ 列不摆放任何炮，那么 $n\times m$ 的方案数等价于 $n\times(m-1)$ 的方案数。

如果第 $m$ 列摆放了 $2$ 个炮，我们可以想到先枚举是哪两行放了（共 $\binom{n}{2}$ 种情况），然后讨论这两行的前一门炮的所在的列。若这两行的前一个炮在同一个列（共 $m-1$ 个可能的列），那么方案数等于将这两行两列去掉（即 $(n-2)\times (m-2)$ 的方案数）。若不相同，我们可以认为先合并这两列，等价于去掉这一行一列后，变为 $(n-1)\times (m-1)$ 的情况（同时根据这两列的顺序乘 $2$）。（可以参考下图，本人手绘有些简陋，请谅解）

![](https://cdn.luogu.com.cn/upload/image_hosting/nzf6p2zn.png)

最后考虑第 $m$ 列放了一个炮的情况。类似前面的情况，我们枚举炮在哪一行，以及这一行前一个炮在哪一列。去掉这一行这一列后，问题变为 $(n-1)\times (m-1)$ 的情况。但是，因为去掉的这一行在前面的那一列有一个炮，因此应该求解 $(n-1)\times (m-1)$，其中一列炮数目 $\leq 1$ 的方案数。这个 $\leq 1$ 的方案数相当于总方案数减去列炮数为 $2$ 的方案数（即上一段），按照上面的方法计算就好。

当我们要求 $n\times m$ 时，我们只需要知道 $(n-1)\times (m-1)$，$(n-2)\times (m-2)$，$n\times (m-1)$ 的方案，因为当 $n<m$ 时是无解的，所以总共的状态数是 $O(n(m-n))$ 的，时间复杂度也是这样的。我们可以递归求解，边界为 $n=0$，此时答案为 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5,M=998244353;
#define int ll
unordered_map<signed,int> g[N],h[N];
//h[i][j] i*j 放2个的方案数
int jc[N],inv[N];
int C(int x,int y){
    if(x<y||x<0||y<0)return 0;
    return ((jc[x]*inv[y])%M*inv[x-y])%M;
}
int qpow(int x,int p){
    int ret=1;
    while(p){
        if(p&1)ret=(ret*x)%M;
        x=(x*x)%M;
        p>>=1;
    }
    return ret;
}
int f(int x,int y){
    //x行y列的方案数
    if(x>y||x<0)return 0;if(x==0)return 1;  
    if(g[x][y])return g[x][y];
    g[x][y]=h[x][y]=0;  
    //放两个
    if(x>=2){
        g[x][y]=((C(x,2)*(y-1))%M*f(x-2,y-2))%M;//前一门炮所在列相同
        g[x][y]+=(C(x,2)*2*f(x-1,y-1))%M;//上一个不同
    }
    h[x][y]=g[x][y]=(g[x][y])%M;
    g[x][y]+=f(x,y-1);//一个都不放
    //放一个
    if(x>=1)g[x][y]+=(((f(x-1,y-1)-h[x-1][y-1])*x)%M*(y-1))%M;
    g[x][y]%=M;g[x][y]+=M;g[x][y]%=M;
    return g[x][y];
}
signed main(){
    jc[0]=1;
    for(int i=1;i<=1e5;i++)jc[i]=(jc[i-1]*i)%M;
    inv[100000]=qpow(jc[100000],M-2);
    for(int i=1e5-1;i>=0;i--)inv[i]=(inv[i+1]*(i+1))%M;
    int n,m;cin>>n>>m;
    cout<<f(n,m)<<endl;
    return 0;
}
```

---

