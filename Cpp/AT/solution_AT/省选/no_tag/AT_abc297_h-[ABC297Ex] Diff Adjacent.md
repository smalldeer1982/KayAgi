# [ABC297Ex] Diff Adjacent

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc297/tasks/abc297_h

正整数列のうち、全ての隣接している $ 2 $ 項が異なるものを**素晴らしい整数列**と定めます。

要素の総和が $ N $ の素晴らしい整数列全てに対する長さの総和を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- 入力はすべて整数
 
### Sample Explanation 1

要素の総和が $ 4 $ の素晴らしい整数列は、$ (4),(1,3),(3,1),(1,2,1) $ の $ 4 $ 個です。なので、答えはこれらの長さの総和の $ 1+2+2+3=8 $ です。 $ (2,2) $ や $ (1,1,2) $ は総和が $ 4 $ ですが、両方 $ 1 $ 項目と $ 2 $ 項目が等しいため条件を満たしません。

## 样例 #1

### 输入

```
4```

### 输出

```
8```

## 样例 #2

### 输入

```
297```

### 输出

```
475867236```

## 样例 #3

### 输入

```
123456```

### 输出

```
771773807```

# 题解

## 作者：UltiMadow (赞：6)

一个暴力的推法（

首先有一个显然的 dp：记 $f_{i,j}$ 表示和为 $i$，最后一个选的数是 $j$ 的所有序列长度和，$g_{i,j}$ 表示和为 $i$，最后一个选的数是 $j$ 的序列个数。

那么有转移：$f_{i,j}=\sum f_{i-j,k}+g_{i-j,k},g_{i,j}=\sum g_{i-j,k}$，答案即为 $\sum f_{n,i}$。

首先考虑快速计算 $g$，记 $G_j(x)=\sum g_{i,j}x^i,S(x)=1+\sum G_j(x)$。

那么根据转移式有 $G_j(x)=x^j\sum_{k\not=j} G_k(x)=x^j(S(x)-G_j(x))$，移项可得 $G_j(x)=\frac{x^j}{1+x^j}S(x)$。

考虑把所有 $j=1\dots n$ 的式子加起来，可得 $S(x)=1+S(x)\sum\frac{x^i}{1+x^i}\Leftrightarrow S(x)=\frac 1{1-\sum\frac {x^i}{1+x^i}}$。

由于 $\frac{x^i}{1+x^i}=-\sum (-x^i)^j$，所以可以用 $\mathcal O(n\ln n)$ 的时间暴力处理出 $1-\sum\frac{x^i}{1+x^i}$，之后多项式求逆即可求出 $S(x)$。

接下来考虑计算 $f$，记 $F_j(x)=\sum f_{i,j}x^i,T(x)=\sum F_j(x)$。

同样根据转移式有 $F_j(x)=x^j\sum_{k\not=j}(F_k(x)+G_k(x))=x^j(S(x)+T(x)-F_j(x)-G_j(x))$，移项可得 $F_j(x)=\frac{x^j}{1+x^j}(S(x)+T(x)-G_j(x))$。

把 $G_j(x)=\frac{x^j}{1+x^j}S(x)$ 带入上式，有 $F_j(x)=\frac{x^j}{1+x^j}(\frac1{1+x^j}S(x)+T(x))$。

把所有 $j=1\dots n$ 的式子加起来，可得 $T(x)=T(x)\sum\frac{x^i}{1+x^i}+S(x)\sum\frac{x^i}{(1+x^i)^2}$，化简可得 $T(x)=S^2(x)\sum\frac{x^i}{(1+x^i)^2}$。

记 $z=x^i$，则 $\frac{x^i}{(1+x^i)^2}=z(\sum(-z)^i)^2$，于是可以先预处理出 $(\sum(-z)^i)^2$ 之后就可以用 $\mathcal O(n\ln n)$ 的时间暴力处理出 $\sum\frac{x^i}{(1+x^i)^2}$ 了。

这样我们就可以直接卷积得到 $T(x)$，最后答案即为 $[x^n]T(x)$。

时间复杂度 $\mathcal O(n\log n)$。

---

## 作者：zyc070419 (赞：2)

# [ABC297EX] Diff Adjacent 题解

题目中限制条件看起来很像容斥，所以可以考虑一下如何容斥算答案。

考虑容斥有至少有 $i$ 个相邻的数相等。但是如果这样容斥的话只能算出好序列的个数，而无法算出答案，所以首先假设如果我们可以求出方案数如何得到答案。我们记 $g_i$ 表示元素和为 $i$ 的好序列个数。

可以考虑一个值 $v$ 在多少个好序列中出现了。那么答案就是：
$$
\sum_{i=1}^{n}\sum_{j=0}^{n-i}h_{j,i}\times h_{n-i-j,i}
$$
其中 $h_{p,q}$ 表示元素和为 $p$ 并且第一个序列元素不为 $q$ 的方案数。上面这个式子表示：枚举当前元素大小 $i$，枚举当前元素之前的元素和大小 $j$，然后首尾方案数相乘再相加就是答案。先考虑 $h_{p,q}$ 怎么算，可以容斥（或者说是归纳一下），过程如下：
$$
\begin{aligned}
h_{p,q}=&g_{p}-h_{p-q,q}\\\\
=&\sum_{i\ge 0,i\times q\le p}(-1)^{i}\times g_{p-i\times q,q}
\end{aligned}
$$
然后答案就可以化简成：
$$
\begin{aligned}
&\sum_{i=1}^{n}\sum_{j=0}^{n-i}\sum_{s\ge 0,s\times i\le j}\sum_{t\ge 0,t\times i\le n-i-j}(-1)^{s+t}\times g_{j-s\times i}\times g_{n-i-j-t\times i}\\\\
=&\sum_{i=1}^{n}\sum_{s\ge 0,t\ge 0,(s+t+1)\times i\le n}(-1)^{s+t}\sum_{j=s\times i}^{n-i}g_{j-s\times i}\times g_{n-i-j-t\times i}\\\\
=&\sum_{i=1}^{n}\sum_{s\ge 0,t\ge 0,(s+t+1)\times i\le n}(-1)^{s+t}\sum_{j=0}^{n-(s+t+1)\times i}g_{j}\times g_{n-(s+t+1)\times i-j}\\\\
=&\sum_{i=1}^{n}\sum_{j\ge 1,i\times j\le n}(-1)^{j-1}f_{n-i\times j}
\end{aligned}
$$
其中 $f_{m}=\sum_{i=0}^{m}g_{i}\times g_{m-i}$，可以 $\mathcal{O}(n\log n)$ 的复杂度内求出 $\{f_n\}$ 数组，然后调和级数计算上面的答案，所以现在只要快速求出 $\{g_n\}$ 即可。

运用上面说的容斥，则答案为 $\sum_{i=0}^{n-1}(-1)^iv_i$，其中 $v_i$ 表示至少有 $i$ 个相邻元素相等的方案数。我们可以按照 **没有要求必须相等的两个相邻的数之间** 分段，使得每一段内的元素都相等，然后就可以生成函数。构造生成函数：
$$
F(x)=\sum_{i=1}^{n}x^i\sum_{j\mid i}(-1)^{j-1}
$$
其中 $[x^i]F(x)$ 表示段内元素和为 $i$ 的方案数。因为元素和为 $i$ 的一段可以分成 $j$ 个元素的条件是 $j\mid i$，分成 $j$ 个元素的容斥系数为 $(-1)^{j-1}$，所以构造出上面的生成函数，那么有 $k$ 个段的答案就是 $[x^n]F^k(x)$，所以答案就是 $[x^n]\sum_{k\ge 1}F^k(x)=[x^n]G(x)$。求一下可以发现 $G(x)=\dfrac{1}{1-F(x)}$。多项式求逆就行了，复杂度 $\mathcal{O}(n\log n)$。

综上，复杂度为 $\mathcal{O}(n\log n)​$，代码在 [这里](https://atcoder.jp/contests/abc297/submissions/51220664)。

---

## 作者：APJifengc (赞：2)

~~据说现在发题解秒过，那我来水篇题解~~

题目一眼看上去就很生成函数。先不管长度总和，先考虑求方案数。这个限制看起来就很容斥，我们钦定多少对数相等，其它任意填。那么答案的生成函数就是：

$$F(x) = \frac{1}{1 - G(x)}, G(x) = \sum_{i=1}^{\infty} \frac{x^i}{1 + x^i}$$

上述式子就是将钦定相等的连续段合起来计算，容斥系数为 $(-1)^{j - 1}$。

考虑长度。求 $\sum i f_i$ 很自然能想到多项式求导，那么我们引入第二个元 $y$ 为序列长度，那么上式子改写为：

$$F(x, y) = \frac{1}{1 - G(x, y)}, G(x, y) = \sum_{i=1}^{\infty} \frac{x^iy}{1 + x^iy}$$

对 $y$ 求导，可得：

$$\frac{\partial}{\partial y}F(x, y) = \frac{\frac{\partial}{\partial y} (G(x, y) - 1)}{(1-G(x, y))^2}, \frac{\partial}{\partial y} G(x, y) = \sum_{i=1}^{\infty} \frac{x^i}{(1 + x^iy)^2}$$

我们不关心 $y$，所以直接带入 $y=1$，那么最后我们要求的答案 $H(x)$ 就是：

$$H(x) = \frac{\displaystyle \sum_{i=1}^{\infty} \frac{x^{i}}{(1+x^i)^2}}{\left(1-\displaystyle \sum_{i=1}^{\infty} \frac{x^i}{1+x^i}\right)^2}$$

分子分母都可以暴力拆开计算（调和级数，共 $O(n \log n)$ 项），于是再加上多项式求逆就做完了。

```cpp
int main() {
    scanf("%d", &n);
    f.set(n), g.set(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; i * j <= n; j++) {
            f[i * j] = (f[i * j] + ((j & 1) ? 1ll : P - 1ll) * j) % P;
            g[i * j] = (g[i * j] + ((j & 1) ? 1ll : P - 1ll)) % P;
        }
    }
    h = f * ((g * (-1) + 1) * (g * (-1) + 1)).inv(n + 1);
    printf("%d\n", h[n]);
    return 0;
}
```

---

## 作者：zhouyuhang (赞：1)

二元 GF 小练习。

考虑容斥，钦定一些位置相等，这样序列就被划分成若干连续段，要求连续段内相等。

注意到题目要求和为 $n$ 的序列的长度之和，那我们考虑二元 GF，$x$ 表示和，$y$ 表示长度。这样一个长为 $i$ 填的数字为 $j$ 的连续段的 GF 就是 $(-1) ^ {i - 1} x ^ {ij} y ^ i$，其中 $(-1) ^ {i - 1}$ 为其容斥系数。则 $F(x, y) = \operatorname{SEQ} \left( \sum_{i, j \ge 1} (-1) ^ {i - 1}x ^ {ij} y ^ i \right)$ 即为答案关于和与长度的二元 GF。

现在来看看题目要求的东西，也就是 $\sum _ {i} i[x ^ n y ^ i]F(x, y)$。注意到这一形式很接近 $F(x, y)$ 对 $y$ 求导的形式，又由于我们只关心长度之和，因此上式的实质就是将 $y = 1$ 代入 $ \frac {\partial} {\partial y} F(x, y)$ 后 $x^ n$ 的系数。

那我们从 $F(x, y)$ 的定义出发计算：记 $G(x, y) = \sum_{i, j \ge 1} (-1) ^ {i - 1}x ^ {ij} y ^ i$，$F(x, y) = \frac {1} {1 - G(x, y)}$，则 $\frac {\partial} {\partial y}F(x, y) = \dfrac {\frac {\partial} {\partial y} G(x, y)} {(1 - G(x, y)) ^ 2}$，代入 $y = 1$ 求逆计算即可。复杂度 $O(n\log n)$。

核心代码很简单（变量名与上文有出入，不影响理解）：

```cpp
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	Prework();
	
	int n;
	cin >> n;
	
	Poly F(n + 1), G(n + 1); F[0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; j += i) {
			if (i & 1) F[j] = sub(F[j], 1), G[j] = add(G[j], i);
			else F[j] = add(F[j], 1), G[j] = sub(G[j], i);
		}
	}
	
	F = Inv(F, n + 1);
	G = G * F;
	G.resize(n + 1);
	G = G * F;
	
	cout << G[n] << endl;

	return 0;
}
```

---

