# [AGC064E] Cross Sum Construction

## 题目描述

给定一个正整数 $N$ 和两个长度为 $N$ 的整数序列 $A=(a_1,\ldots,a_N),\ B=(b_1,\ldots,b_N)$。  
另外，定义多重集合 $X$，其包含 $N^2$ 个值 $(a_i+b_j)\ (1\leq i,j\leq N)$。

对于每个元素都在 $[-10^{18},\ 10^{18}]$ 范围内的 $N\times N$ 整数矩阵 $M$，定义其分数如下：

- 设 $S$ 为一个多重集合，包含 $N^2$ 个值，分别为“$M$ 的第 $i$ 行或第 $j$ 列中属于的 $2N-1$ 个元素的总和”$(1\leq i,j\leq N)$。此时，分数为对所有整数 $z$，$\min($$X$ 中 $z$ 的出现次数, $S$ 中 $z$ 的出现次数$)$ 的总和。

请你对于每个测试用例，求出一个能使分数最大的矩阵 $M$。

$T$ 组测试数据，请分别解决上述问题。

## 说明/提示

### 限制条件

- $1\leq T\leq 2.5\times 10^5$
- $1\leq N\leq 500$
- $-10^9\leq a_i,b_i\leq 10^9$
- 所有测试用例中 $N^2$ 的总和不超过 $2.5\times 10^5$
- 输入均为整数

### 样例说明 1

第 $1$ 个测试用例中，$X=\{-5\},\ S=\{-5\}$，分数为 $1$。  
第 $2$ 个测试用例中，$X=\{8,-11,7,-12\},\ S=\{7,8,-11,-10\}$，分数为 $3$。  
第 $3$ 个测试用例中，$X=\{21,22,23,24,25,26,27,28,29\},\ S=\{28,21,26,23,25,27,24,29,22\}$，分数为 $9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1
5
-10
2
0 -1
8 -11
3
20 23 26
1 2 3```

### 输出

```
-5
8 9
-10 -9
2 9 4
7 5 3
6 1 8```

# 题解

## 作者：Y204335 (赞：1)

# \[AGC064E] Cross Sum Construction

## 题目大意

给定 $n$ 和长度为 $n$ 的序列 $A,B$，令可重集 $X=\left\{a+b| a\in A,b\in B\right\}$，要求构造 $n\times n$ 的矩阵 $M$，令可重集 $S=\left\{\sum_{i=1}^{n}M_{x,i}+\sum_{i=1}^{n}M_{i,y}-M_{x,y}|1\le x,y\le n\right\}$，使得 $\sum_{i}\min\left(sum_{i\in X},sum_{i\in S}\right)$ 最大（注意 $sum_{i\in X}$ 指 $i$ 在 $X$ 中出现的次数）。

## 题目分析

由于 $i$ 的贡献最大就是 $i$ 在 $X$ 中出现的次数，所以要让 $X$ 中的元素尽可能在 $S$ 中出现。令 $s_{x,y}=\sum_{i=1}^{n}M_{x,i}+\sum_{i=1}^{n}M_{i,y}-M_{x,y}$（也就是 $M$ 中这一行一列的元素之和），考虑如何通过 $s_{i,j}$ 反推 $M_{i,j}$。

首先，由于 $M$ 中的每个数字都会被 $2n-1$ 个 $s$ 算上，所以 $M$ 中所有元素之和 $sum=\frac{\sum_{i=1}^{n}\sum_{j=1}^{n}s_{i,j}}{2n-1}$，由于 $sum$ 一定为整数，所以如果要使 $S$ 与 $X$ 一致，$\sum_{i\in X}i\times sum_{i\in X}$ 一定要是 $2n-1$ 的倍数，先考虑满足倍数关系的情况（不满足倍数关系可以通过改变其中一个 $s$ 来处理）。

令 $r_x=\sum_{i=1}^{n}s_{i,x},c_x=\sum_{i=1}^{n}s_{x,i}$，则：

$$\begin{aligned}M_{i,j}&=\frac{r_i+c_j-\left(n-1\right)\times s_{i,j}-2\times\frac{sum}{2n-1}}{n-1}\\&=\frac{\left(r_i+c_j\right)\left(2n-1\right)-2sum}{\left(n-1\right)\left(2n-1\right)}-s_{i,j}\end{aligned}$$

所以 $\left(r_i+c_j\right)\left(2n-1\right)-2sum$ 需要是 $n-1$ 的倍数。

- 若 $\forall 1\le i,j\le n,\left(r_i+c_j\right)\left(2n-1\right)\equiv 2sum\pmod{n-1}$ 则：

$$\begin{aligned}\left(r_i+c_j\right)\left(2n-1\right)&\equiv 2sum\pmod{n-1}\\\left(r_i+c_j\right)\left(2n-1\right)&\equiv\left(r_x+c_y\right)\left(2n-1\right)\pmod{n-1}\\r_i+c_j&\equiv r_x+c_y\pmod{n-1}\\r_i&\equiv r_x\pmod{n-1}\\c_j&\equiv c_y\pmod{n-1}\end{aligned}$$

- 若 $\forall 1\le i,j\le n,r_i\equiv r_j,c_i\equiv c_j\pmod{n-1}$，则：

$$\begin{aligned}\left(r_i+c_j\right)\left(2n-1\right)&\equiv \left(r_i+c_j\right)\times n\pmod{n-1}\\&\equiv n\times r_i+n\times c_j\pmod{n-1}\\&\equiv\sum_{i=1}^{n}r_i+\sum_{i=1}^{n}c_i\pmod{n-1}\\&\equiv 2sum\pmod{n-1}\end{aligned}$$

所以 $\forall 1\le i,j\le n,\left(r_i+c_j\right)\left(2n-1\right)\equiv 2sum\pmod{n-1}$ 与 $\forall 1\le i,j\le n,r_i\equiv r_j,c_i\equiv c_j\pmod{n-1}$ 互为充要条件。

考虑如何使得 $\forall 1\le i,j\le n,r_i\equiv r_j,c_i\equiv c_j\pmod{n-1}$，可以通过构造下标使得 $\forall 1\le i\le n,r_i=\sum_{i=1}^{n}A_i+B_i,c_i=\sum_{i=1}^{n}A_i+B_i$，按照 $n$ 的奇偶性分开考虑，注意以下下标从 $0$ 开始（$0\dots n-1$），默认模 $n$。

1. 当 $n\bmod 2=1$ 时，可以借助溢出转变下标奇偶性来处理，令 $s_{i,j}=A_{-i+j}+B_{-2i+j}$，此时 $r_x=c_x=\sum_{i=1}^{n}A_i+B_i$。

2. 当 $n\bmod 2=0$ 时，设 $s_{i,j}=A_l+B_k$，先考虑 $k$，当 $i,j$ 改变时，$k$ 需要不重不漏，可以构造出 $k=\begin{cases}-i+j&-i+j\ne 0\text{ 且}-i+j\ne\frac{n}{2}\\\frac{n\times\left(i\bmod2\right)}{2}&-i+j=0\text{ 或}-i+j=\frac{n}{2}\end{cases}$，再考虑 $l$，可以发现直接通过 $i,j$ 算出 $l$ 是困难的，可以反过来，从 $l$ 反推 $i,j$，分别从 $0\sim n-1$ 枚举 $l$ 和 $x$，令 $\left(i,j\right)=\begin{cases}\left(2\times\left\lfloor\frac{l}{2}\right\rfloor+\frac{n\times\left(l\bmod2\right)}{2}+x,2\times\left\lfloor\frac{l}{2}\right\rfloor+2x\right)&x=0\sim\frac{n}{2}-1\\\left(2\times\left\lfloor\frac{l}{2}\right\rfloor+\frac{n\times\left(l\bmod2\right)}{2}+x,2\times\left\lfloor\frac{l}{2}\right\rfloor+2x+1\right)&x=\frac{n}{2}\sim n-1\end{cases}$，此时 $r_x=c_x=\sum_{i=1}^{n}A_i+B_i$（具体证明可以看[官方题解](https://atcoder.jp/contests/agc064/editorial/6983)）。

这样就解决了 $\left(\sum_{i\in X}i\times sum_{i\in X}\right)\bmod 2n-1=0$ 时的构造，当 $\left(\sum_{i\in X}i\times sum_{i\in X}\right)\bmod 2n-1\ne 0$ 时，可以通过不断给某个 $s_{i,j}$ 加上 $n-1$（这是为了在构造完后进行变化仍能满足 $\forall 1\le x\le n,r_i\equiv r_x,c_j\equiv c_x\pmod{n-1}$）来进行处理。

时间复杂度 $O(n^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 510;
int t, n;
ll s[N][N], sum, r[N], c[N], cnt[N], a[N], b[N];
void solve()
{
    cin >> n;
    sum = 0;
    for (int i = 0; i < n; i++) {
        r[i] = c[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    if (n == 1) {
        cout << a[0] + b[0] << '\n';
        return;
    }
    if (n % 2) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                s[i][j] = a[(n + j - i) % n] + b[(2 * n - 2 * i + j) % n];
            }
        }
    } else {
        for (int i = 0; i < n - 1; i++) {
            cnt[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            if (cnt[(n - 1 + a[i] % (n - 1)) % (n - 1)] != -1) {
                swap(a[cnt[(n - 1 + a[i] % (n - 1)) % (n - 1)]], a[0]);
                swap(a[i], a[n / 2]);
                break;
            }
            cnt[(n - 1 + a[i] % (n - 1)) % (n - 1)] = i;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j || (n + j - i) % n == n / 2) {
                    s[i][j] = a[(i % 2) * n / 2];
                } else {
                    s[i][j] = a[(n + j - i) % n];
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x = (2 * (i / 2) + (i % 2) * n / 2 + j) % n, y = (2 * (i / 2) + 2 * j + (j >= n / 2)) % n;
                s[x][y] += b[i];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += s[i][j];
        }
    }
    while (sum % (2 * n - 1)) {
        s[0][0] += n - 1;
        sum += n - 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            r[i] += s[i][j];
            c[j] += s[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ((r[i] + c[j]) - 2 * sum / (2 * n - 1)) / (n - 1) - s[i][j] << ' ';
        }
        cout << '\n';
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

---

