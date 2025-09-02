# [AGC065D] Not Intersect

## 题目描述

在一个平面上画有一个圆周。圆周上有 $N$ 个不同的点，这些点按顺时针方向依次编号为 $1,2,\dots,N$。

在这 $N$ 个点中，任意两点之间可以连一条线段，共有 $\frac{N(N-1)}{2}$ 条不同的线段。现在从中选出 $M$ 条线段画出来。请计算有多少种选法，使得任意两条线段除了端点外不会相交。请将答案对 $10^9+7$ 取模后输出。

## 说明/提示

### 限制条件

- $1 \leq N \leq 10^7$
- $0 \leq M \leq \frac{N(N-1)}{2}$

### 样例解释 1

左侧和中间的例子满足条件。（注意，线段在端点处相交是允许的。）右侧的例子不满足条件，因为有两条边在端点以外的地方相交。除此之外，剩下的 $\binom{6}{2} - 1 = 14$ 种情况都满足条件。  
![](https://img.atcoder.jp/agc065/4854b47261fd9c54c2d25ee53c3e6be5.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2```

### 输出

```
14```

## 样例 #2

### 输入

```
6 3```

### 输出

```
295```

## 样例 #3

### 输入

```
2023 1217```

### 输出

```
10811951```

## 样例 #4

### 输入

```
1234321 2345432```

### 输出

```
789452255```

# 题解

## 作者：RedreamMer (赞：15)

神 $\texttt{z\color{red}ak}$ 教会我一个此题的十分方便的做法，发现题解区好像没有，我来记录一下。

  前置知识：Raney 引理

  > 对于一个整数序列 $a_i$，若所有数的和为 $1$，那么其所有 $n$ 个循环位移的序列恰好有一个满足，前缀和数组在任意处大于 $0$。

  关于这种序列的一个简单推论是，$n$ 个循环位移序列两两不同。

  对于 $n$ 个点的环，枚举多少条边连接相邻两个点，然后将其看成是一个凸多边形，问题转化成，一个大小为 $n$ 的凸多边形，将其任意划分成 $k \in [m + 1, m - n + 1]$ 个多边形的方案数。

  接着，一个划分可以映射成一个长度为 $n - 1 + k$ 的操作序列，即从 $2$ 枚举到 $n$，每次可以加入一个新点，也可以在任意时刻画一条划分边，删去栈顶若干个点，但是不能删成空。

  那么操作序列就是 $n$ 个 $+1$，以及 $k$ 个负数组成的序列，因为最后得到一个凸多边形，所以这个序列中所有值的总和应该是 $1$。

  套用 Raney 引理，我们避开了麻烦的计算合法序列的过程，任意一个序列的贡献就是 $\frac 1 {n - 1 + k}$，因此只需要计算序列个数即可，答案就是

  $$
  \sum_{i = 0} ^ {\min(n, m - 1)} \frac 1 {n - 1 + m - i} \binom n i \binom {n - 3} {m - i - 1} \binom {n - 1 + m - i} {m - i}
  $$

  注意需要特判一些边界情况。

---

## 作者：Fido_Puppy (赞：9)

第一步考虑断环成链，则原问题转化为：

有一条 $n$ 个点的链，点从左到右编号为 $1 \sim n$，要在 $m$ 对不同的点之间连边，满足两条边只在顶点处相交，求连边的方案数。

第二步考虑 dp，设 $f_{n, m}$ 表示 $n+1$ 个点的链，需要连 $m$ 条边，并且满足 $1$ 和 $n+1$ 之间不连边的方案数。

枚举从 $n+1$ 连出去最左的边（或者没有边与 $n+1$ 相连），那么有 $\displaystyle f_{n,m}=f_{n-1,m}+f_{n-1,m-1}+\sum_{x=1}^{n-1}\sum_{y=0}^{m-1} f_{x,y}\cdot f_{n-x,m-1-y}+\sum_{x=1}^{n-1}\sum_{y=0}^{m-2}f_{x,y}\cdot f_{n-x,m-2-y}$。

边界条件为 $f_{0,m}=0\ (m\ge0), f_{n,0}=1\ (n\ge1)$。

最终答案为 $f_{n-1,m}+f_{n-1,m-1}$，可以特判 $m=0$ 时答案为 $1$。

发现 $m$ 过大时没有满足条件的方案，而连边形成了一个类似树的结构，所以 $m$ 最大为 $O(n)$ 级别，时间复杂度 $O(n^4)$。

```cpp
const int N = 107, M = N * 2, md = 1e9 + 7;
int n, m, f[N][M];
int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m, --n;
	if (m > n + 1 + max(n - 2, 0)) return cout << 0, 0;
	if (!m) return cout << 1, 0;
	For(i, 1, n) {
		f[i][0] = 1;
		For(j, 1, m) {
			f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % md;
			For(x, 1, i - 1) For(y, 0, j - 1) f[i][j] = (1ll * f[i][j] + 1ll * f[x][y] * f[i - x][j - 1 - y]) % md;
			For(x, 1, i - 1) For(y, 0, j - 2) f[i][j] = (1ll * f[i][j] + 1ll * f[x][y] * f[i - x][j - 2 - y]) % md;
		}
	}
	cout << (f[n][m - 1] + f[n][m]) % md << '\n';
	return 0;
}
```

第三步考虑生成函数，设 $\displaystyle F = \sum_{n\ge 0}\sum_{m\ge 0} f_{x, y}x^n y^m$，那么只要知道 $[x^{n-1}y^m] F$ 与 $[x^{n-1}y^{m-1}]F$ 就能知道答案，下面考虑如何求出 $[x^n y^m] F$。

通过 dp 转移式列出方程：

$$F=Fx+Fxy+F^2y+F^2y^2+x$$

$$F^2y^2+F^2y+Fxy+Fx-F+x=0$$

$$F^2y^2+F^2y-F=-x(Fy+F+1)$$

$$\dfrac{F-F^2y^2-F^2y}{Fy+F+1}=x$$

设 $\displaystyle G=\frac{x-x^2y^2-x^2y}{xy+x+1}$，则 $F \circ G=x$。

然后拉格朗日反演：

$$\displaystyle [x^n]F=\frac{1}{n}[x^{n-1}]{\left(\frac{x}{G}\right)}^n$$

考虑计算 $\displaystyle [x^{n-1}]{\left(\frac{x}{G}\right)}^n$：

$$\displaystyle =[x^{n-1}]{\left(\frac{xy+x+1}{1-xy^2-xy}\right)}^n$$

$$\displaystyle =[x^{n-1}]{[(y+1)x+1]}^n\times {\left(\frac{1}{1-y(y+1)x}\right)}^n$$

$$\displaystyle =[x^{n-1}]\left(\sum_{z\ge 0} \binom{n}{z}{(y+1)}^z x^z\right)\times\left(\sum_{z\ge 0}\binom{n+z-1}{z} y^z{(y+1)}^z x^z\right)$$

$$\displaystyle =\sum_{z=0}^{n-1}\binom{n}{n-z-1}{(y+1)}^{n-z-1}\times\binom{n+z-1}{z}y^z{(y+1)}^z$$

$$\displaystyle =\sum_{z=0}^{n-1}\binom{n}{n-z-1}\binom{n+z-1}{z}{(y+1)}^{n-1}y^z$$

于是能求出 $[x^ny^m] F$：

$$\displaystyle =\frac{1}{n}[x^{n-1}y^m]{\left(\frac{x}{G}\right)}^n$$

$$\displaystyle =\frac{1}{n}\sum_{z=0}^{n-1}\binom{n}{n-z-1}\binom{n+z-1}{z}[y^{m-z}]{(y+1)}^{n-1}$$

$$\displaystyle =\frac{1}{n}\sum_{z=0}^{n-1}\binom{n}{n-z-1}\binom{n+z-1}{z}\binom{n-1}{m-z}$$

我们就在 $O(n)$ 的时间复杂度内求出了 $[x^ny^m]F$，也就能 $O(n)$ 求出答案。

```cpp
const int N = 2e7 + 7, md = 1e9 + 7;
void add(int &x, int y) {
  (x += y) >= md ? x -= md : 0;
}
int qpow(int x, int p) {
  int ans = 1;
  for (; p; p /= 2, x = 1ll * x * x % md) {
    if (p & 1) ans = 1ll * ans * x % md;
  }
  return ans;
}
int n, fac[N], ifac[N];
ll m;
int C(int m, ll n) {
  if (n > m) return 0;
  return 1ll * fac[m] * ifac[n] % md * ifac[m - n] % md;
}
int F(int n, ll m) {
  int sum = 0;
  For(z, 0, min(1ll * n - 1, m)) {
    add(sum, 1ll * C(n, n - z - 1) * C(n + z - 1, z) % md * C(n - 1, m - z) % md);
  }
  return 1ll * sum * qpow(n, md - 2) % md;
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  fac[0] = 1;
  For(i, 1, N - 1) fac[i] = 1ll * fac[i - 1] * i % md;
  ifac[N - 1] = qpow(fac[N - 1], md - 2);
  Rep(i, N - 1, 1) ifac[i - 1] = 1ll * ifac[i] * i % md;
  cin >> n >> m, --n;
  if (!m) { cout << 1; return 0; }
  int ans = F(n, m);
  add(ans, F(n, m - 1));
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：suomynonA (赞：7)

## 前言

搬运一个官方题解的组合意义做法，完全不需要生成函数。

## 题解

首先可以发现 $m$ 比较小，具体来说是有 $m \le 2n - 3$，因为最大的情况是先连接环上的 $n$ 条边，然后再对这个 $n$ 边形三角剖分，连接 $n - 2$ 条边。

试着写一下式子之后，（可能？）会发现允许边可重更好做，所以考虑求一个 $g_k$ 表示边可重的答案，最后再容斥回来，考虑怎么求 $g_k$。

我们可以将一条边的连接视为一个元素进出栈的过程，因为进出栈显然就不会发生交叉。连接多条边的点，就是进栈或出栈多次。具体来说，我们这样构建这张图：按顺序遍历 $1 \sim n$，对于一个点 $i$，先执行若干次出栈操作，每次都将 $i$ 与弹出的元素连边，然后再向栈中压入若干个 $i$。需要保证最后栈为空，且总共连接 $k$ 条边。可以发现，每一张边可重的合法图都与这个过程一一对应。

进一步转化，以进栈的数的个数为 $x$ 轴，出栈的数的个数为 $y$ 轴，把这个过程放到平面上，过程变为：每次先向 $y$ 轴正方向走若干步，再向 $x$ 轴正方向走若干步，需要保证过程中不越过直线 $y=x$，求 $(0, 0)$ 走到 $(k, k)$ 走 $n$ 次的方案数。首先显然有第一次的向上走和最后一次的向右走不会发生，所以可以改为先向右再向上，走 $n-1$ 次。

考虑每次走完之后的位置 $(a_i, b_i)$，发现上面的过程等价于求两个长度为 $n$ 的不降序列 $a$ 和 $b$，满足 $a_0 = b_0 = 0, a_{n - 1} = b_{n - 1} = k, a_i \ge b_i$。进一步发现，一个开头结尾确定的不降序列一一对应了一条从 $(0, 0)$ 到 $(k, n - 2)$ 的路径，所以相当于求路径对 $(P, Q)$ 的数量，满足 $Q$ 低于 $P$（可相交）。

上述问题可以直接解决。考虑每一步两条路径分别怎么走，记向右为 $1$ 向上为 $0$，则有四种走法：$(0, 0), (0, 1), (1, 0), (1, 1)$。第二三种的数量是一样的，所以枚举这个数量 $i$，则第一种走了 $n - 2 - i$ 次，第四种走了 $k - i$ 次。发现第一四种是不会影响 $P$ 和 $Q$ 之间的高度的，所以低于的关系可以表示为对于任意一个前缀，第二种的数量大于等于第三种的数量。这是卡特兰数经典问题。所以有（$H_i$ 为卡特兰数）

$$
\begin{aligned}
g_k &= \sum_{i = 0}^k \frac {H_i(n - 2 + k)!} {(n - 2 - i)!(k - i)!(2i)!}\\ &= \sum_{i = 0}^k \frac {(n - 2 + k)!} {(n - 2 - i)!(k - i)!i!(i + 1)!}\\ &= \frac {(n - 2 + k)!} {(n - 2)!(k + 1)!}\sum_{i = 0}^k \binom {n - 2} i \binom {k + 1} {k - i}\\
&= \frac {\binom {n - 1 + k} {n - 2}\binom {n - 1 + k} {n - 1}} {n - 1 + k}
\end{aligned}
$$


这样就可以 $O(m)$ 计算所有 $g_k$ 了。那怎么容斥出原问题的答案 $f$ 呢？

由于边是无标号的，所以枚举一个实际有效的边数，再乘上一个插板法的系数来对边分类，就可以由 $f$ 求 $g$，即 $g_k = \sum_{i = 0} ^ k \binom {k - 1} {i - 1} f_i$，二项式反演可得 $f_m = \sum_{i = 0} ^ {m - 1} (-1)^{m - 1 - i}\binom {m - 1} {i} g_{i + 1}$，$O(m)$ 计算即可。

注意需要特判 $n \le 2$ 以及 $m \ge 2n - 3$ 的情况。

代码没什么放的必要了。

---

## 作者：dspt (赞：2)

@RedreamMer 题解重制版。再次拜谢 ZAK 的做法。

&nbsp;
## Raney 引理
> 对于整数序列 $a_0,\dots,a_{n-1}$，如果 $\sum a=1$，那么 $a$ 的 $n$ 个循环移位的序列中恰好有一个满足：该序列的所有前缀和均为正整数。

证明：构造周期为 $n$，定义域为 $\Z$ 的函数 $f(x)$，满足 $f(x)=f(x-1)+a_{(x-1)\bmod n}$。

![](https://pic3.zhimg.com/v2-9f83d4d31229312c2e2e1228e0aad7b2_r.jpg)

偷了张图，这是序列 $a=\set{1,3,-4,1}$ 构造出的函数。

用直线 $y=\frac xn+b$ 从 $b=-\infin$ 处往上平移去切函数图像。图中切线为 $DH$。

> 此切线与 $f(x)$ 在一个周期中恰好切于一个整点。

这里认为周期是 $[x,x+T)$。容易说明切点是整点。设切点为 $(x_0,y_0)$。因为直线的斜率为 $\frac1n$，所以直线 $y=\frac xn+b$ 除了在 $x_0$ 处，在该周期内的其它函数值均不为整数，不可能与 $f(x)$ 相切。

从 $x_0$ 开始的循环移位就是我们要求的：序列的所有前缀和均为正整数的那个循环移位。

还要说明其它循环移位的序列均存在某个前缀和不是正整数。容易说明其它循环移位的序列在 $x_0$ 之前的前缀和 $\le0$。

引理证毕。

例题：[P6672 清华集训 2016 你的生命已如风中残烛](https://www.luogu.com.cn/problem/P6672)

---

我们还需要用到另一个引理：

> 对于整数序列 $a_0,\dots,a_{n-1}$，如果 $\sum a=1$，那么 $a$ 的 $n$ 个循环移位的序列均不相同。	

对于 $n=1$ 显然成立。对于 $n>1$，考虑反证法。如果有两个循环移位的序列相同，那么存在周期 $T<n$，使得 $a_i=a_{(i+T)\bmod n}$。

从 $i$ 开始在模 $n$ 意义下不停以步长为 $T$ 的步跳，跳到的点均和 $a_i$ 相等。容易说明等价类大小为 $\frac n{\gcd(T,n)}$，可以进一步得到 $\frac n{\gcd(T,n)}\mid\sum a$。

在 $n>1$ 时，$\frac n{\gcd(T,n)}$ 也大于 $1$。$\sum a=1$ 需要是某个大于 $1$ 的数的倍数，假设不成立。

引理证毕。

&nbsp;
## 构造双射

以下的讨论均对于 $n\ge3$。

把圆看成一个正 $n$ 边形。加的 $m$ 条边相当于在对正 $n$ 边形进行划分。

正 $n$ 边形上相邻的两点之间的边是否连接不会对划分的形态产生影响，不妨枚举有多少条这样的边。设有 $i$ 条，方案数为 $\binom ni$。现在问题变成了要连接 $m-i$ 条边，连接的边不能与原来正 $n$ 边形上的边重合，问可以得到多少本质不同的正 $n$ 边形划分。

破环为链。容易发现限制不会产生变化。

构造双射。假设有个栈，初始为空。我们要把 $j:2\to n$ 依次加入栈中。在任意时刻可以选择：

+ 把 $j$ 加入栈中
+ 此时栈顶为 $j$，选择一个正整数 $k$，弹出栈顶的 $k+1$ 个数。视为 $j$ 与当前栈顶连一条边。如果栈里没有点，那么就是 $j$ 和 $1$ 连边。连完边后再把 $j$ 放回去。

![](https://cdn.luogu.com.cn/upload/image_hosting/wmio8ry5.png)

如图，这样的图形可以用以下的流程描述。

|          操作           |        栈         |
| :---------------------: | :---------------: |
|       加入 $j=2$        |     $\set{2}$     |
|       加入 $j=3$        |    $\set{2,3}$    |
|       加入 $j=4$        |   $\set{2,3,4}$   |
| 取 $k=1$，连边 $4\to2$ |    $\set{2,4}$    |
| 取 $k=1$，连边 $4\to1$ |     $\set{4}$     |
|       加入 $j=5$        |    $\set{4,5}$    |
|       加入 $j=6$        |   $\set{4,5,6}$   |
|       加入 $j=7$        |  $\set{4,5,6,7}$  |
|       加入 $j=8$        | $\set{4,5,6,7,8}$ |
| 取 $k=2$，连边 $8\to5$ |   $\set{4,5,8}$   |

主播主播，有没有更加深刻的理解？有的，当然有的。

栈中的数和 $1$ 就是当前所有可以连边的点。每次连边的时候可供连边的点都会减少。这同时保证了不会连出相邻的边。

这个过程其实就是扫描边的右端点 $j$。把所有右端点为 $j$ 的边按左端点从右往左的顺序加入。

---

其实这样会存在一个问题。就是边 $n\to1$。这条边属于相邻的边，其实是不应该存在的。但是在上面的过程中，只要把最后一步改成 $k=4$，就会连出这样的边。

解决的方式是我们钦定必须有边 $n\to1$（但这条边实际上不存在）。这样做的好处在于：

+ 任意合法的图按照上述方式构造操作序列后，栈中剩余的数数量 $>1$，取 $k=$ 栈中剩余的数数量 $-1$ 就能把边 $n\to1$ 这条边加上。双射的性质没有变，同时解决了会连出 $n\to1$ 的情况。
+ 设加入点为 $+1$，连边为 $-k$，得到的操作序列和为 $1$（栈中最后只剩 $n$ 这一个数）。

&nbsp;
## 计算答案

特判掉 $n\le2$。对于 $n\ge3$，套用 Raney 引理计算答案。

假设我们有一个操作序列：序列中有 $n-1$ 个 $+1$，$m-i+1$ 个负数，这些数的和为 $1$。但是这个序列可能是不合法的。序列合法的条件是：栈中任意时刻都要有至少一个数，即序列的所有前缀和均为正整数。

根据 Raney 引理，这个序列的循环同构中恰好有一个是合法的。又通过前面的引理可以得到，这个序列所有的循环同构都不相同。这样就不会计重了！

容易发现根据当前的计算方式，可以得到 $m-i+1\le n-2$。因为 $i\le n$，所以只有 $m\le2n-3$ 时答案才不为 $0$。

令 $k=m-i+1$。只要统计合法操作序列数量即可，每个合法操作序列对答案的贡献是 $\frac1{n-1+k}$。有 $m-i+1$ 个负数，这些数的和为 $2-n$。先给每个数分配 $-1$，还剩 $n-2-k$ 个负单位可以分配。插个板得到 $\binom{n-2-1}{k-1}$。然后要把 $n-1$ 个 $+1$ 和 $k$ 个负数归并在一起。方案数为 $\binom{n-1+k}k$。

总答案：
$$
\sum_{i=0}^{\min(n,m)}\frac 1{n-1+k}\binom ni\binom{n-3}{k-1}\binom{n-1+k}k
$$
时间复杂度 $O(n)$。[代码](https://atcoder.jp/contests/agc065/submissions/63982678)。

---

## 作者：ExplodingKonjac (赞：1)

[**原题链接**](https://atcoder.jp/contests/agc065/tasks/agc065_d)

## 题目分析

我们改为解决这个的问题：有一个 $n$ 段的圆弧，$(1,n)$ 之间已经连了一条线段，要再连 $m$ 条不相交的线段，并且边与圆弧**不重**（也就是不能有 $(i,i+1)$ 的线段）。设这样的答案为 $f_{n,m}$。

那么原题答案显然是 $\displaystyle\sum_{i=0}^m f_{n-1,i}\binom{n}{m-i}$，也就是再加入一些与圆弧重的边。

我们考虑求 $f$ 的生成函数 $\displaystyle F(x,y)=\sum_{n,m}f_{n,m}x^ny^m$。

考虑边界上最靠外的若干条边，这些边可以看做是将圆弧分成若干段，而每个段内都是形式相同的子问题，如图：

![](https://pic.imgdb.cn/item/658054b5c458853aefa15bb6.png)

我们先假装把 $(1,n)$ 的边也计入 $m$，那么有方程：
$$
F=y\cdot \dfrac{F^2}{1-F}+x
$$
其中，那个分式相当于至少 $2$ 个 $F$ 相乘（因为我们不能只分一段），那个 $x$ 是边界 $f_{1,0}=1$。

这样解出来是一个二次方程，因此会有两个解，我们需要选择那个 $[x^0]F(x,y)=0$ 的解。

最后，我们要把假装加入的 $(1,n)$ 去除，即，除了 $x^1$ 之外所有 $x^i$ 系数都要除以一个 $y$：
$$
F\gets \frac{F-x}{y}+x
$$
经过艰苦卓绝的~~使用 Mathematica~~ 计算，可以得到最终的 $F$：
$$
F(x,y)=\frac{1-x+2xy^2-\sqrt{x^2-2x(2y+1)+1}}{2y(y+1)}
$$
然后我们就要计算答案啦。
$$
\begin{aligned}
	ans&=\sum_{i=0}^m [x^{n-1}y^i]F(x,y)\binom{n}{m-i} \\
	&=[x^{n-1} y^m] F(x,y)\cdot (y+1)^n \\
	&=[x^{n-1} y^m] \frac{1-x+2xy^2-\sqrt{x^2-2x(2y+1)+1}}{2y}\cdot (y+1)^{n-1} \\
	&=\frac{1}{2}[x^{n-1}y^{m+1}]\left(1-x+2xy^2-\sqrt{x^2-2x(2y+1)+1}\right)(y+1)^{n-1}
\end{aligned}
$$
我们发现，分母上的东西都被搞掉了，于是我们只需要展开分子。这里分子是两部分的乘积，我们尝试展开前半部分，这里显然只需要管那个根式：
$$
\begin{aligned}
	[x^ny^m] \sqrt{x^2-2x(2y+1)+1}&=[x^ny^m]\sqrt{(1-x)^2-4xy} \\
	&=[x^ny^m]\sum_{i=0}^{+\infty} \binom{1/2}{i}(-4xy)^i(1-x)^{1-2i} \\
	&=[x^n]\binom{1/2}{i}(-4x)^m(1-x)^{1-2m} \\
	&=\binom{1/2}{i}(-4)^m\cdot [x^{n-m}](1-x)^{1-2m} \\
	&=\binom{1/2}{i}\binom{1-2m}{n-m}4^m(-1)^n
\end{aligned}
$$
这里的两个组合数虽然看着十分鬼畜，但是都可以用 $\dbinom{n}{m}=\dfrac{n^{\underline{m}}}{m!}$ 来拆成下降幂算。至于负数的下降幂，可以每一项提出 $-1$ 之后转成正数的上升幂。注意到这里隐含了要求 $m\le n$，所以 $O(n)$ 预处理后整个式子都可以 $O(1)$ 记算。

回到上面的式子，既然左边可以 $O(1)$，右边是一个简单的组合数，那么就可以 $O(n)$ 计算出 $[x^{n-1}y^{m+1}]$ 的系数，那么整道题就做完啦 ヾ(≧∇≦*)ヾ。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/*
省略快读快输（qin,qout）和模意义整数类（Mint）
*/

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

constexpr int MOD=1e9+7;
constexpr int MAXN=2e7;
constexpr Mint INV2=((MOD+1)/2);

Mint fac[MAXN+5],inv[MAXN+5],f[MAXN+5],pw4[MAXN+5];
inline Mint binom(int r,int c)
{ return r<c?0:fac[r]*inv[c]*inv[r-c]; }
void prepare()
{
	fac[0]=1;
	for(int i=1;i<=MAXN;i++) fac[i]=fac[i-1]*i;
	inv[MAXN]=fac[MAXN].inv();
	for(int i=MAXN;i>=1;i--) inv[i-1]=inv[i]*i;
	pw4[0]=1,f[0]=1;
	for(int i=1;i<=MAXN;i++) pw4[i]=pw4[i-1]*4,f[i]=f[i-1]*(INV2-i+1);
	for(int i=1;i<=MAXN;i++) f[i]*=inv[i];
}

int n;
LL m;
inline Mint calc(int x,int y)
{
	if(!y) return 0;
	Mint res;
	res=f[y]*fac[x+y-2]*inv[2*y-2]*inv[x-y]*pw4[y];
	if(!(y&1)) res=-res;
	if(x==0 && y==0) res+=1;
	if(x==1 && y==0) res-=1;
	if(x==1 && y==2) res+=2;
	return res;
}

int main()
{
	prepare();
	qin>>n>>m;
	if(n==1) return qout<<int(m==0)<<'\n',0;
	if(m>2*n) return qout<<"0\n",0;
	Mint ans=0;
	for(int i=0;i<n && i<=m+1;i++)
		ans+=INV2*calc(n-1,i)*binom(n-1,m+1-i);
	qout<<ans()<<'\n';
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc065_d)

**题目大意**

> 求圆上 $n$ 个等分点连 $m$ 条不相交弦的方案数。
>
> 数据范围：$n\le 10^7$。

**思路分析**

首先 $m$ 最大值一定是三角剖分时取到，即 $m\le 2n-3$。

首先连接相邻点的弦无意义，只考虑连接非相邻点的弦。

从 $(1,n)$ 处断环为链，每条弦都唯一对应 $[1,n]$ 的子区间，只要这些区间两两包含或无交即可。

一种区间是否合法的检验方法是：从左往右扫描右端点 $r$，对于每个区间 $[l,r]$，不能存在 $x\le l\le y<r$ 的区间 $[x,y]$。

那么用栈维护所有合法的 $l$，每次加入 $[l,r]$ 就把 $l+1\sim r-1$ 中的元素都弹出即可。

具体来说：不把 $1$ 加入栈，且每次先加入 $r$，再弹出 $l+1\sim r-1$ 的元素，最后加入虚拟区间 $[1,n]$，这样一个序列合法当且仅当任何时候栈大小 $>0$，且最终栈大小 $=1$。

容易发现任何一种栈的大小的变化序列和一组连边方案双射。

设有 $k-1$ 条弦，则只要考虑有 $n-1$ 个 $+1$ 和 $k$ 个负数，和为 $1$ 且每个前缀和都 $>0$ 的序列个数。

这是经典的 Raney 定理：对于每个序列，其所有循环移位中恰有一个合法。

这是显然的，合法循环移位一定是所有取到前缀和最小值的点中下标最大的一个。

那么方案数先给所有负数插板分配权值，再求所有整数位置。

设 $i$ 为连接相邻点的弦个数，$k=m-i+1$，则答案为：
$$
\sum_i\dfrac{1}{n-1+k}\binom ni\binom{n-3}{k-1}\binom{n-1+k}{k}
$$
时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e7+5,MOD=1e9+7;
ll n,m,fac[MAXN],ifac[MAXN],inv[MAXN];
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
ll C(int x,int y) { return y<0||y>x?0:fac[x]*ifac[y]%MOD*ifac[x-y]%MOD; }
signed main() {
	inv[1]=1;
	for(int i=2;i<MAXN;++i) inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=fac[0]=1;i<MAXN;++i) fac[i]=fac[i-1]*i%MOD;
	ifac[MAXN-1]=ksm(fac[MAXN-1]);
	for(int i=MAXN-1;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	scanf("%lld%lld",&n,&m);
	if(m>max(0ll,2*n-3)) return puts("0"),0;
	if(n<=2) return puts("1"),0;
	ll s=0;
	for(int i=0;i<=n&&i<=m;++i) if(m-i<=n-3) {
		int k=m-i+1;
		s=(s+C(n,i)*C(n-3,k-1)%MOD*C(n-1+k,k)%MOD*inv[n-1+k])%MOD;
	}
	printf("%lld\n",s);
	return 0;
}
```

---

