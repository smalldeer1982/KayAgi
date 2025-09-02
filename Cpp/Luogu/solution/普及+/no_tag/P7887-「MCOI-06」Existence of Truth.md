# 「MCOI-06」Existence of Truth

## 题目描述

可能存在一个非负整数数序列 $a_1,a_2,\dots,a_n$ 使得 $0\le a_i<10^9+7$。

给定 $x_1,x_2,\dots,x_n$，$y_1,y_2,\dots,y_n$，$z_1,z_2,\dots,z_n$，已知对于 $1\le i\le n$ 满足：

$$x_i\left(\sum_{j=1}^ia_j\right)+y_i\left(\sum_{j=i}^na_j\right)\equiv z_i\pmod{10^9+7}$$

求 $a_1,a_2,\dots,a_n$。

## 说明/提示

#### 数据规模与约定

**本题采用捆绑测试。**

 - Subtask 1（10 pts）：$n=1$。
 - Subtask 2（19 pts）：$\sum n\le100$。
 - Subtask 3（19 pts）：$x_i=y_i=1$。
 - Subtask 4（22 pts）：保证有**唯一解。**
 - Subtask 5（30 pts）：无特殊限制。

对于所有数据：

 - $1\le n,\sum n\le 2\times10^5$；
 - $1\le x_i,y_i<10^9+7$；
 - $0\le z_i<10^9+7$。

## 样例 #1

### 输入

```
2
3
3 1 9
2 2 16
1 3 15
6
3 6 246
5 7 283
2 7 179
4 6 214
8 7 337
3 5 151```

### 输出

```
1
1 2 3
1
8 8 0 6 7 8```

# 题解

## 作者：一只书虫仔 (赞：9)

#### Description

> 求序列 $a_1,a_2,\dots,a_n$ 使得对于所有 $i=1,2,\dots,n$ 有：
>
>$$x_i\left(\sum_{j=1}^ia_i\right)+y_i\left(\sum_{j=i}^na_i\right)\equiv z_i\pmod{10^9+7}$$

#### Solution

~~誊抄官方题解~~ 我们直接不考虑 $\bmod 10^9+7$，因此以下运算在模 $10^9+7$ 意义下进行。

考虑 $a_i$ 的前缀和 $S_i$，则题目中的要求可以表示为（$i \in (1,n]$）：

$$\begin{aligned}x_iS_i+y_i(S_n-S_{i-1})&=z_i\\x_iS_i+y_iS_n-y_iS_{i-1}&=z_i\\x_iS_i-y_iS_{i-1}&=z_i-y_iS_n\end{aligned}$$

对于 $i=1$ 即为：

$$\begin{aligned}x_1a_1+y_1S_n&=z_1\\S_n&=\frac{z_1-x_1a_1}{y_1}\end{aligned}$$

代入 $i \in (1,n]$ 的情况则有：

$$\begin{aligned}x_iS_i-y_iS_{i-1}&=z_i-y_i\frac{z_1-x_1a_1}{y_1}\\S_i&=\frac{z_i+y_i\left(S_{i-1}-\frac{z_1-x_1a_1}{y_1}\right)}{x_i}\end{aligned}$$

不难得知，所有 $S_i$ 都可以表示为 $A_ia_1+B_i$（因为 $S_1=a_1$），我们考虑求出 $A_i$ 与 $B_i$：

$$\begin{aligned}S_i&=\frac{z_i+y_i(A_{i-1}a_1+B_{i-1}-\frac{z_1-x_1a_1}{y_1})}{x_i}\\S_i&=\frac{y_i}{x_i}A_{i-1}a_1+\frac{z_i}{x_i}+\frac{y_i}{x_i}B_{i-1}-\frac{z_1y_i}{y_1x_i}+\frac{x_1y_i}{y_1x_i}a_1\\S_i&=\frac{y_i}{x_i}\left(A_{i-1}+\frac{x_1}{y_1}\right)a_1+\frac{z_i}{x_i}+\frac{y_i}{x_i}\left(B_{i-1}-\frac{z_1}{y_1}\right)\end{aligned}$$

因此：

$$\begin{aligned}A_i&=\frac{y_i}{x_i}\left(A_{i-1}+\frac{x_1}{y_1}\right)\\B_i&=\frac{z_i}{x_i}+\frac{y_i}{x_i}\left(B_{i-1}-\frac{z_1}{y_1}\right)\end{aligned}$$

求出 $S_n$ 后代入 $S_n=\frac{z_1-x_1a_1}{y_1}$ 就可以得到 $a_1$ 了。

对 $a_1$ 进行一些判断：

- 如果 $a_1=\frac 0 0$，则任意 $a_1$ 都满足，解数为 $10^9+7$；
- 如果 $a_1=\frac x 0\ (x \ne 0)$，则没有 $a_1$ 满足，解数为 $0$；
- 其他情况都有解。

---

## 作者：TonyYin (赞：9)

提供一种从**高斯消元**来考虑的做法。

更好的阅读体验：[TonyYin - Blog](https://www.tonyyin.top/2021/10/luogu-p7887/)

## 题目来源

[【LGR-093】洛谷 10 月月赛 I & MCOI R6 Div.1](https://www.luogu.com.cn/contest/52020) A题

[【LGR-093】洛谷 10 月月赛 I & MCOI R6 Div.2](https://www.luogu.com.cn/contest/52021) C题

## 题意

可能存在一个非负整数数序列 $a_1,a_2,\dots,a_n$ 使得 $0\leq a_i < 10^9+7$。

给定 $x_1,x_2,\cdots,x_n$，$y_1,y_2,\cdots,y_n$，$z_1,z_2,\cdots,z_n$，已知对于 $1\le i\le n$ 满足：
$$
x_i\left(\sum_{j=1}^ia_j\right)+y_i\left(\sum_{j=i}^na_j\right)\equiv z_i\pmod{10^9+7}
$$
先求满足条件的解的个数。若只有一组解，求出 $a_1,a_2,\dots,a_n$。

有多测。

> 对于 $10\%$ 的数据，$n=1$，
>
> 对于另外 $19\%$ 的数据，$n\leq 100$，
>
> 对于另外 $19\%$ 的数据，$x_i=y_i=1$，
>
> 对于另外 $22\%$ 的数据，保证有唯一解。
>
> 对于 $100\%$ 的数据，$1\leq n\leq 2\times 10^5$，$1\leq x_i, y_i\leq 10^9+7$，$0\leq z_i\leq 10^9+7$.

## $\rm{Subtask}$ $1$

对于 $10\%$ 的数据，$n=1$.

按照题意写出关于 $a_1$ 的方程：
$$
x_1a_1+y_1a_1\equiv z_1 \pmod{10^9+7}
$$
即：
$$
(x_1+y_1)a_1\equiv z_1\pmod{10^9+7}
$$
注意到此时 $a_1$ **不一定有唯一解**，需要分类讨论。

**一、** 当 $x_1+y_1=0$ 且 $z_1\neq 0$ 时，方程无解。

**二、** 当 $x_1+y_1=0$ 且 $z_1=0$ 时，$a_1$ 可以在 $[0, 10^9+7)$ 上任取，共有 $10^9+7$ 组解。

**三、** 对于其他情况均有唯一解：
$$
a_1=\frac{z_1}{x_1+y_1}\pmod{10^9+7}
$$
用乘法逆元处理即可。

```cpp
if(n == 1) cout << 1 << endl << z[1] * inv((x[1] + y[1]) % mod) % mod << endl;
```

这里如果只考虑情况三，也可以拿到这 $10$ 分。

但由于题目有多组测试数据，如果后续在代码中保留对 $n=1$ 的特判，不分类讨论会被卡掉。

然后还查不出来）

## $\rm{Subtask}$ $3$

对于另外 $19 \%$ 的数据，$x_i=y_i=1$.

**为了方便表示，后面涉及的所有运算都在 $\bmod 10^9+7$ 意义下进行。**

把 $n$ 个方程列出：
$$
\left \{
\begin{array}{l}
x_1(a_1)+y_1(a_1+a_2+\cdots+a_n)=z_1\\
x_2(a_1+a_2)+y_2(a_2+\cdots+a_n)=z_2\\
x_3(a_1+\cdots+a_3)+y_3(a_3+\cdots+a_n)=z_3\\
\cdots\\
x_n(a_1+a_2+\cdots+a_n)+y_n(a_n)=z_n\\
\end{array}
\right.
$$

若 $x_i=y_i=1$，那么：

$$
\left\{
\begin{array}{l}
(a_1+a_2+\cdots+a_n)+a_1=z_1 &(1)\\
(a_1+a_2+\cdots+a_n)+a_2=z_2 &(2)\\
(a_1+a_2+\cdots+a_n)+a_3=z_3 &(3)\\
\cdots&\cdots\\
(a_1+a_2+\cdots+a_n)+a_n=z_n &(n)\\
\end{array}
\right.
$$


容易想到把 $n$ 个方程相加，
$$
(n+1)(a_1+a_2+\cdots+a_n)=z_1+z_2+\cdots+z_n
$$
把 $n+1$ 除过去就能得到 $a_1+a_2+\cdots+a_n$ 的值，再代入 $(1)\cdots(n)$ 式即可求出答案。

同样的，需要分类讨论一下解的情况。但对于这部分数据，不讨论也能通过。

```cpp
if(subtask3) {
    int sumz = 0;
    for(int i = 1; i <= n; i++) (sumz += z[i]) %= mod;
    int sum = sumz * inv(n + 1) % mod;
    cout << 1 << endl;
    for(int i = 1; i <= n; i++) {
        cout << (((z[i] - sum) % mod) + mod) % mod << " ";
    } cout << endl;
}
```

## $\rm{Subtask}$ $2$

对于另外 $19\%$ 的数据，$n\leq 100$。
$$
\left\{
\begin{array}{l}
x_1(a_1)+y_1(a_1+a_2+\cdots+a_n)=z_1\\
x_2(a_1+a_2)+y_2(a_2+\cdots+a_n)=z_2\\
x_3(a_1+\cdots+a_3)+y_3(a_3+\cdots+a_n)=z_3\\
\cdots\\
x_n(a_1+a_2+\cdots+a_n)+y_n(a_n)=z_n\\
\end{array}
\right.
$$
对于这个方程组，我们可以把每个方程进行整理，转化为这样的形式：
$$
\left\{
\begin{array}{l}
c_{1,1}a_1+c_{1,2}a_2+\cdots+c_{1,n}a_n=z_1\\
c_{2,1}a_1+c_{2,2}a_2+\cdots+c_{2,n}a_n=z_2\\
\cdots\\
c_{n,1}a_1+c_{n,2}a_2+\cdots+c_{n,n}a_n=z_n
\end{array}
\right.
$$
也就是把每个方程中，未知数的系数求出来。

之后使用[**高斯消元**](https://www.tonyyin.top/2021/09/gauss-elimination/)直接解方程。

过程中，若存在自由元，则为解的个数为 $10^9+7$，不管有几个自由元都是。不知道为什么。

> 若方程组通过化简可以得到 $0\cdot x=0$，那么 $x$ 的取值任意，称 $x$ 为自由元。

时间复杂度 $\mathcal{O}(n^3)$.

## $\rm{Subtask}$ $4$

对于另外 $22\%$ 的数据，保证有唯一解。

题目中的方程显然不同于随机生成的方程，要找到一些可以利用的特性。

**有可能**可以发现，方程与区间和密切相关，于是考虑前缀和。

设 $s_i=\sum_{j=1}^ja_j$，则方程组通项为：
$$
x_i\cdot s_i+y_i(s_n-s_{j-1})=z_i\quad (i)
$$
也就是：
$$
-y_i\cdot s_{j-1} + x_i\cdot s_i+y_i\cdot s_n=z_i\quad (i)
$$
这种形式下，每个方程涉及的未知数更少，更容易处理。

考虑系数矩阵的形态：
$$
\begin{matrix}
&&\textcolor{gray}{1} &\textcolor{gray}{2} &\textcolor{gray}{3} &\textcolor{gray}{4} &\textcolor{gray}{5} &\textcolor{gray}{6}\\\\
\textcolor{gray}{1} &&x &  &  &  &  &x \\
\textcolor{gray}{2} &&x &x &  &  &  &x \\
\textcolor{gray}{3} &&  &x &x &  &  &x \\
\textcolor{gray}{4} &&  &  &x &x &  &x \\
\textcolor{gray}{5} &&  &  &  &x &x &x \\
\textcolor{gray}{6} &&  &  &  &  &x &x \\
\end{matrix}
$$
$x$ 表示系数不为 $0$。

这样第 $1$ 行只需要消第 $2$ 行，第 $2$ 行消第 $3$ 行，以此类推，最后的矩阵形如：
$$
\begin{matrix}
&&\textcolor{gray}{1} &\textcolor{gray}{2} &\textcolor{gray}{3} &\textcolor{gray}{4} &\textcolor{gray}{5} &\textcolor{gray}{6}\\\\
\textcolor{gray}{1} &&x &  &  &  &  &x \\
\textcolor{gray}{2} &&0 &x &  &  &  &x \\
\textcolor{gray}{3} &&  &0 &x &  &  &x \\
\textcolor{gray}{4} &&  &  &0 &x &  &x \\
\textcolor{gray}{5} &&  &  &  &0 &x &x \\
\textcolor{gray}{6} &&  &  &  &  &0 &x \\
\end{matrix}
$$
于是 $a_n$ 可求，分别代入第 $1\sim n-1$ 个方程即可求解。

这样的时间复杂度是 $\mathcal{O}(n\log n)$，$\log n$ 来自求逆元。

对于空间，每行只有 $3$ 个系数需要存，不用开矩阵，也是 $\mathcal{O}(n)$ 的。

## $\rm{Subtask}$ $5$

对于 $100\%$ 的数据，$1\leq n\leq 2\times 10^5$，$1\leq x_i, y_i\leq 10^9+7$，$0\leq z_i\leq 10^9+7$.

上面的时空复杂度已经可以通过此题，只需要多加一个判断解的个数。

判断的方法在 $\rm{Subtask}$ $1$ 中提到过了，但**需要另外注意**：

存在一个自由元，其值可以任取，不代表方程组有无穷组解。**只要有一个变量是无解的，则方程组无解。**

## 代码

删去了 `read()` 和头文件。

```cpp
#define int long long
const int MAXN = 2e5 + 10, mod = 1e9 + 7;
inline int power(int x, int k) {
	int ret = 1;
	while(k) {
		if(k & 1) ret = ret * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ret;
}
inline int inv(int x) {return power(x, mod - 2);}
int T, n;
int x[MAXN], y[MAXN], z[MAXN];
int a[MAXN], b[MAXN], c[MAXN];
int s[MAXN];
signed main() {
	T = read();
	while(T--) {
		n = read();
		for(int i = 1; i <= n; i++) {
			x[i] = read(); y[i] = read(); z[i] = read();
		}
		//对每个x,y,z，x[i]s[i] - y[i]s[i-1] + y[i]s[n] = z[i]
		for(int i = 1; i < n; i++) {//高斯消元解前缀和
			a[i] = mod - y[i]; b[i] = x[i]; c[i] = y[i];
		} a[n] = mod - y[n]; c[n] = (x[n] + y[n]) % mod;
		for(int i = 1; i < n; i++) {//用第i行消掉第i+1行的第i列
			int k = a[i + 1] * inv(b[i]) % mod;
			(a[i + 1] -= k * b[i] % mod) %= mod;
			(c[i + 1] -= k * c[i] % mod) %= mod;
			(z[i + 1] -= k * z[i] % mod) %= mod;
		}
		int roots = 1;
		if(c[n] == 0 && z[n] != 0) {
            putchar('0'); putchar('\n');
            continue;
        }
		else if(c[n] == 0 && z[n] == 0) roots = mod;
		else s[n] = z[n] * inv(c[n]) % mod;
		for(int i = 1; i <= n - 1; i++) {
			int right = (z[i] - c[i] * s[n] % mod) % mod;
			if(b[i] == 0 && right != 0) {roots = 0; break;}
			else if(b[i] == 0 && right == 0) roots += mod;
			else s[i] = ((z[i] - c[i] * s[n] % mod) * inv(b[i]) % mod + mod) % mod;
		}
		if(roots != 1) {printf("%lld\n", roots); continue;}
		else {putchar('1'); putchar('\n');}
		for(int i = 1; i <= n; i++) 
            printf("%lld ", ((s[i] - s[i - 1]) % mod + mod) % mod);
        putchar('\n');
	}
	return 0;
}
```



---

## 作者：Remake_ (赞：2)

好题啊qwq

首先将所有 $y_i$ 变为 $1$，相应的 $x_i'=\frac{x_i}{y_i}$，$z_i'=\frac{z_i}{y_i}$ 。

然后所有式子变成了这样：

$$x_i '(\sum_{j=1}^ia_j)+\sum_{j=i}^na_j\equiv z_i'$$

然后关键的来了，我们把相邻两个式子差分一下看看我们会得到什么：

$$x_i '(\sum_{j=1}^ia_j)-x_{i+1}'(\sum_{j=1}^{i+1}a_j)+\sum_{j=i}^na_j-\sum_{j=i+1}^na_j\equiv z_i'-z_{i+1}'$$

化简一下得：

$$(x_i'-x_{i+1}')(\sum_{j=1}^ia_j)-x_{i+1}'a_{i+1}+a_i\equiv z_i'-z_{i+1}'$$

看起来还是没有什么用啊TAT

别着急，我们看看特殊情况，即 $i=1$ 时的情况可化成：

$$(x_1'-x_2'+1)a_1-x_2'a_2\equiv z_1'-z_2'$$

把 $a_1$ 当做一个常量，上面这个东西就可以看做是一个一元一次方程了，解得：

$$a_2=\frac{x_1'-x_2'+1}{x_2'}a_1+\frac{z_2'-z_1'}{x_2'}$$

观察到我们把 $a_2$ 表示为了 $ka_1+b$ 的形式！

接下来我们使用递推的思想，就是再继续通过 $i=2$ 的式子把 $a_3$ 表示成 $ka_1+b$ 的形式，通过 $i=3$ 的式子把 $a_4$ 表示成 $ka_1+b$ 的形式，以此类推，通过 $i=m$ 的式子把 $a_{m+1}$ 表示成 $ka_1+b$ 的形式 . . . . . .

怎么做呢？由于我们是递推的，所以我们在看 $i=m$ 的情况时，我们已经把 $j\in[1,m]$ 的所有 $a_j$ 均表示成了 $ka_1+b$ 的形式，那么我们再观察一下原式：

$$(x_i'-x_{i+1}')(\sum_{j=1}^ia_j)-x_{i+1}'a_{i+1}+a_i\equiv z_i'-z_{i+1}'$$

其中的 $\sum\limits_{j=1}^ia_j$ 以及 $a_i$ 项已经在先前全被我们表示为 $ka_1+b$ 的形式了，那么原式又可以变成这样：

$$(x_i'-x_{i+1}')(k_1a_1+b_1)-x_{i+1}'a_{i+1}+k_2a_1+b_2\equiv z_i'-z_{i+1}'$$

又是一个一元一次方程，又是只有 $a_1$ 和 $a_{i+1}$ 两个未知量

还是把 $a_1$ 看做常量，解一下方程就行了

就这样我们把每一个 $a_i$ 都表示为了 $ka_1+b$ 的形式

将他们全部带入到 $i=1$ 的情况中，注意此时代入进去的就是差分前的原式了，化简一下可以得到形如 $Aa_1\equiv B$ 的形式，分类讨论：

$1.$ 如果 $A\ne0$，可以解得 $a_1$，其他数便也顺理成章的解出来了，直接输出解数为 $1$ 然后输出所有 $a_i$ 就行了

$2.$ 如果 $A=0$ 且 $B\ne0$，此时该一元一次方程无解，输出解数为 $0$ 即可

$3.$ 如果 $A=0$ 且 $B=0$，此时 $a_1$ 取啥值都行，但是我们观察到 $0\leq a_i<10^9+7$ ，故而直接输出 $10^9+7$ 即可



---

