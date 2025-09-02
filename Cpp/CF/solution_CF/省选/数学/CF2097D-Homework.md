# Homework

## 题目描述

有些老师在"天狼星"教育中心工作的同时还在大学学习。这种情况下，出差并不能免除他们完成作业的义务，因此他们直接在飞机上做作业。Artem 就是这样一位老师，他在大学被布置了以下作业。

对于任意长度为偶数 $m$ 的字符串 $a$，他可以执行以下操作。Artem 将字符串 $a$ 分成两个长度相等的部分 $x$ 和 $y$，然后执行以下三种操作之一：

- 对于每个 $i \in \left\{ 1, 2, \ldots, \frac{m}{2}\right\}$，令 $x_i = (x_i + y_i) \bmod 2$；
- 对于每个 $i \in \left\{ 1, 2, \ldots, \frac{m}{2}\right\}$，令 $y_i = (x_i + y_i) \bmod 2$；
- 对字符串 $x$ 和 $y$ 分别执行任意次数的上述操作（递归应用），注意此时 $x$ 和 $y$ 的长度必须为偶数。

操作完成后，字符串 $a$ 将被替换为按原顺序连接的 $x$ 和 $y$。不幸的是，Artem 在飞机上睡着了，所以你需要替他完成作业。Artem 有两个长度为 $n$ 的二进制字符串 $s$ 和 $t$，每个字符串都由 $n$ 个字符 0 或 1 组成。请判断是否可以通过任意次数的操作使字符串 $s$ 等于字符串 $t$。

## 说明/提示

在第一个测试用例中，字符串 00001001 可以通过两次操作转换为 10101001。操作序列如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2097D/168d2d9e52ff66afe40aa42de1043dc65663a285.png)

在第二个测试用例中，字符串 00000000 无法转换为除自身外的任何其他字符串，因为在任何操作中都无法产生非零元素。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
8
00001001
10101001
8
00000000
00001001
6
010110
100010```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：Mr_罗 (赞：5)

设 $n=mk$ ，其中 $2\nmid m$ ，$k$ 是 $2$ 的幂。

由于每次将长度为偶数的串劈开，那么分到最后整下一个个长度为 $m$ 的小段必须当成一个整体来看。

下面说明几个命题：

**命题一** 如果可以将一个数异或到另一个数上去，那么可以实现交换操作。

形式化语言：对于一个二元组 $(x,y)$ ，如果可以执行下列两个操作：

- $(x,y)\to(x,x\oplus y)$
- $(x,y)\to(x\oplus y,y)$

那么可以 $(x,y)\to(y,x)$ 。

> **证明** $(x,y)\to(x,x\oplus y)\to(y,x\oplus y)\to(y,x)$
>
> $\square$

**命题二** 对于任意一个长度为 $2^k(k>0)$ 的序列，总可以将第 $i(i<2^{k-1})$ 个元素异或到第 $i+2^{k-1}$ 个元素上去。

> **证明** 考虑归纳法，假设所有比当前小的 $k'$ 都可行。边界是 $k=1$ ，从 $k=2$ 开始考虑。
>
> 首先说明可以把第 $0$ 个元素异或到第 $2^{k-1}$ 个元素上去：
>
> $$\begin{pmatrix}x_0\\x_1\\\vdots\\x_{t-1}\\y_0\\y_1\\\vdots\\y_{t-1}\end{pmatrix}\to\begin{pmatrix}x_0\oplus x_1\\x_0\\\vdots\\x_{t-1}\\y_0\\y_1\\\vdots\\y_{t-1}\end{pmatrix}\to\begin{pmatrix}x_0\oplus x_1\\x_0\\\vdots\\x_{t-1}\\y_0\oplus x_0\oplus x_1\\y_1\oplus x_0\\\vdots\\y_{t-1}\oplus x_{t-1}\end{pmatrix}\to\begin{pmatrix}x_0\oplus x_1\\x_0\\\vdots\\x_{t-1}\\y_0\oplus y_1\oplus x_1\\y_1\oplus x_0\\\vdots\\y_{t-1}\oplus x_{t-1}\end{pmatrix}\to\begin{pmatrix}x_0\oplus x_1\\x_0\\\vdots\\x_{t-1}\\y_0\oplus y_1\oplus x_0\\y_1\\\vdots\\y_{t-1}\end{pmatrix}\to\begin{pmatrix}x_0\\x_1\\\vdots\\x_{t-1}\\y_0\oplus x_0\\y_1\\\vdots\\y_{t-1}\end{pmatrix}$$
>
> 对于 $i\not=0$ 的情况，可以先把第 $i$ 个元素和第 $0$ 个交换一下，另一半同理，操作完再交换回来。由归纳假设及命题一可知交换操作是可行的。
>
> $\square$

**命题三** 我们可以任意将一个元素异或到另一个元素上去。

> **证明** 首先把两个元素之间的间隔拆成若干 $2$ 的幂，由命题二可知中间的每一步都能走过去，于是 $(x_0,x_1,\cdots,x_{t-1},x_t)\to(x_1,x_0,\cdots,x_{t-1},x_t)\to(x_1,x_2,\cdots,x_0,x_t)\to(x_1,x_2,\cdots,x_0,x_0\oplus x_t)\to(x_1,x_0,\cdots,x_{t-1},x_0\oplus x_t)\to(x_0,x_1,\cdots,x_{t-1},x_0\oplus x_t)$ 即可。
>
> $\square$

于是我们可以直接对两个 $m\times k$ 的矩阵做高消，由于相似矩阵（能够通过线性变换变得相同的两个矩阵）高消之后结果相同，因此只要判这两个矩阵的高消之后的结果是否相同即可。

```cpp
int n, m;
char s[N], t[N];

void mslv() {
    rd(n, s, t);
    m = n >> __builtin_ctz(n), n /= m;
    vector<vi> a(n, vi(m)), b(n, vi(m));
    req(i, 0, n * m) a[i / m][i % m] = s[i] - '0', b[i / m][i % m] = t[i] - '0';
    int p = 0;
    req(i, 0, m) {
        int q = p;
        while (q < n && !a[q][i]) q++;
        if (q >= n) continue;
        if (p != q) swap(a[p], a[q]);
        req(j, 0, n) if (j != p && a[j][i]) req(k, i, m) a[j][k] ^= a[p][k];
        p++;
    } p = 0;
    req(i, 0, m) {
        int q = p;
        while (q < n && !b[q][i]) q++;
        if (q >= n) continue;
        if (p != q) swap(b[p], b[q]);
        req(j, 0, n) if (j != p && b[j][i]) req(k, i, m) b[j][k] ^= b[p][k];
        p++;
    }
    req(i, 0, n) req(j, 0, m) if (a[i][j] != b[i][j]) return prs("No");
    prs("Yes");
}
```

---

