# Two Subarrays

## 题目描述

给定两个长度为 $n$ 的整数数组 $a$ 和 $b$。

我们定义子数组 $[l, r]$ 的代价为 $a_l + a_{l + 1} + \cdots + a_r + b_l + b_r$。如果 $l = r$，那么代价计算为 $a_l + 2 \cdot b_l$。

你需要执行以下三种类型的查询：

- "1 $p$ $x$" — 把 $a_p$ 更新为 $x$；
- "2 $p$ $x$" — 把 $b_p$ 更新为 $x$；
- "3 $l$ $r$" — 在区间 $[l, r]$ 内找到两个不相交且非空的子数组，使它们的总代价最大，并输出这个总代价。

## 样例 #1

### 输入

```
7
3 -1 4 -3 2 4 0
0 6 1 0 -3 -2 -1
6
3 1 7
1 2 0
3 3 6
2 5 -3
1 3 2
3 1 5```

### 输出

```
18
7
16```

## 样例 #2

### 输入

```
10
2 -1 -3 -2 0 4 5 6 2 5
2 -4 -5 -1 6 2 5 -6 4 2
10
3 6 7
1 10 -2
3 5 7
3 2 8
2 1 -5
2 7 4
3 1 3
3 3 8
3 2 3
1 4 4```

### 输出

```
23
28
28
-17
27
-22```

# 题解

## 作者：XiaoXia_uwu (赞：9)

线段树优化 DP 可做，我们考虑如下状态设计：

- $f[0]$：当前未选任何数。
- $f[1]$：进行第一组的选数。
- $f[2]$：已经选完了第一组。
- $f[3]$：已经选完了第一组，进行第二组的选数。
- $f[4]$：两组都选完了。

那么转移设计也是显而易见的：
- $f[0] = f'[0]$

- $f[1] = \max(f'[0] + a[i] + b[i], f'[1] + a[i])$
- $f[2] = \max(f'[0] + a[i] + 2b[i], f'[1] + a[i] + b[i], f'[2])$
- $f[3] = \max(f'[2] + a[i] + b[i], f'[3] + a[i])$
- $f[4] = \max(f'[2] + a[i] + 2b[i], f'[3] + a[i] + b[i], f'[4])$

转移矩阵设计如下：

$$ \left[
    \begin{array}{ccccc}
        0 & a_i+b_i & a_i+2b_i & -\infin & -\infin \\
        -\infin & a_i & a_i+b_i & -\infin & -\infin \\
        -\infin & -\infin & 0 & a_i+b_i & a_i+2b_i \\
        -\infin & -\infin & -\infin & a_i & a_i+b_i \\
        -\infin & -\infin & -\infin & -\infin & 0 \\
    \end{array}
\right] $$

最后的答案就是 $(\prod_{i=l}^{r} A_i)[0][4]$。

对于操作一和操作二，我们直接在线段树上修改对应位置的转移矩阵就行；对于操作三，我们直接进行线段树区间查询即可。

时间复杂度：$O(k^3n\log n+k^3q\log n)$。

[参考代码](https://www.luogu.com.cn/paste/xw7jwc0k)

---

## 作者：Starrykiller (赞：8)

显然的线段树。考虑如何合并信息，分类讨论一下发现只有几种情况：
- 两个区间都在左侧/右侧。这个是好处理的。
- 一个区间在左侧，另一个在右侧。这个也是好处理的。
- 左侧有一个完整的区间，另外一个区间横跨左右。
- 右侧有一个完整的区间，另外一个区间横跨左右。

发现只需要记录一个横跨的最大值方便拼接就可以了。于是，考虑维护以下信息：

- $\mathrm{answer}$：区间内答案（即，两个不交子区间的最大权值和）。
- $\mathrm{mx}$：区间内的最大权值（即，子区间的最大权值和）。
- $\mathrm{pre1}$：已经有了一个区间 $[l,r]$，剩下一个右边开口的区间 $[l',R]$。
- $\mathrm{suf1}$：已经有了一个区间 $[l,r]$，剩下一个左边开口的区间 $[L,r']$。
- $\mathrm{pre}$：一个右边开口的区间 $[l',R]$。
- $\mathrm{suf}$：一个左边开口的区间 $[L,r']$。 
- $\mathrm{mid}$：一个向左边开口的区间 $[L,r']$ 和一个向右边开口的区间 $[l',R]$。
- $\mathrm{suma}$：区间内的 $\sum a_i$。


然后直接转移即可。[代码](https://codeforces.com/contest/2042/submission/294607542)。时间复杂度 $\Theta((n+m)\log n)$。

---

## 作者：xiezheyuan (赞：3)

不是，都除夕了，CF 还卡我常数，没有武德！

## 简要题意

给定两个长度为 $n$ 的序列 $a,b$，有 $m$ 次操作，支持：

- `1 p v` 令 $a_p\gets v$。
- `2 p v` 令 $b_p\gets v$。
- `3 l r` 定义一个区间 $[x,y]$ 的收益为 $b_x+b_y+\sum_{i=x}^{y}a_i$，你需要在 $[l,r]$ 中选出两个不交的非空区间，使得这两个区间的收益之和最大，输出这个最大收益和。

$1\leq n,m\leq 2\times 10^5$。

## 思路

先来思考一下这个问题：

> 给定一个长度为 $n$ 的序列 $a$，你需要选出两个不交的非空区间，使得这两个区间的收益之和最大，输出这个最大收益和。$1\leq n\leq 10^6$。

我们称左边的区间为 $A$ 区间，右边的区间为 $B$ 区间，那么实际上对于每一个位置，可以看成进行决策（划分到 $A$ 区间或 $B$ 区间，或者不划分），因此可以考虑 dp。

设 $f(i,x)$ 表示考虑到第 $i$ 个位置的收益和，其中：

- $x=1$ 表示在 $i$ 及 $i$ 之前不存在区间的端点。
- $x=2$ 表示在 $i$ 及 $i$ 之前存在 $A$ 区间的左端点。
- $x=3$ 表示在 $i$ 及 $i$ 之前存在 $A$ 区间的右端点。
- $x=4$ 表示在 $i$ 及 $i$ 之前存在 $B$ 区间的左端点。
- $x=5$ 表示在 $i$ 及 $i$ 之前存在 $B$ 区间的右端点。

转移的话直接一步一步写就好了：

- $f(i,1)=f(i-1,1)$。
- $f(i,2)=\max(f(i-1,1)+a_i+b_i, f(i-2)+a_i)$，表示 $i$ 是否为 $A$ 的左端点。
- $f(i,3)=\max(f(i-1,2)+a_i+b_i,f(i-1,1)+a_i+2b_i,f(i-1,3))$ 分别表示 $i$ 仅为 $A$ 的右端点、同时为 $A$ 的左右端点、不为 $A$ 的任何端点。
- $f(i,4)=\max(f(i-1,3)+a_i+b_i,f(i-1,4)+a_i)$，表示 $i$ 是否为 $B$ 的左端点。
- $f(i,5)=\max(f(i-1,4)+a_i+b_i,f(i-1,3)+a_i+2b_i,f(i-1,5))$ 分别表示 $i$ 仅为 $B$ 的右端点、同时为 $B$ 的左右端点、不为 $B$ 的任何端点。

边界 $f(0,1)=0,f(0,2)=f(0,3)=f(0,4)=f(0,5)=-\infty$，这样就可以做到 $O(n)$ 了。

回到原问题，有了前面的铺垫，我们很容易看出可以使用动态 dp。

具体地，根据上面的转移方程，可以使用 $(\max,+)$ 矩阵乘法，写出下面的转移矩阵：

$$
P(i-1)
\begin{bmatrix}
0  & a_i+b_i & a_i+2b_i &  & \\
  & a_i & a_i+b_i &  & \\
  &  & 0 & a_i+b_i & a_i+2b_i\\
  &  &  & a_i & a_i+b_i\\
  &  &  &  & 0
\end{bmatrix}
=
P(i)
$$

其中 $P(i)=\begin{bmatrix}f(i,1) & f(i,2) & f(i,3) & f(i,4) & f(i,5)\end{bmatrix}$ 表示状态向量。

于是按照动态 dp 的基本套路，写一个单点修改区间查询矩阵乘积的线段树即可，时间复杂度 $O(m\log n)$。可能需要卡常，一种实用的卡常方法是先对矩阵乘法循环展开，然后观察到有些位置恒为 $0$ 或 $-\infty$，可以用这个方法减少一点运算。

## 代码

```cpp
#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

const int N = 2e5 + 5;
using i64 = long long;

int n, m, a[N], b[N];

struct matrix{
    int n, m;
    i64 a[5][5];
    matrix(){
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++) a[i][j] = -1e18;
        }
    }
    i64* operator[](int p){ return a[p]; }
};

matrix operator*(matrix a, matrix b){
    matrix c; c.n = a.n, c.m = b.m;
    c[0][0] = 0;
    c[0][1] = max({b[0][1], a[0][1] + b[1][1]});
    c[0][2] = max({b[0][2], a[0][1] + b[1][2], a[0][2]});
    c[0][3] = max({b[0][3], a[0][1] + b[1][3], a[0][2] + b[2][3], a[0][3] + b[3][3]});
    c[0][4] = max({b[0][4], a[0][1] + b[1][4], a[0][2] + b[2][4], a[0][3] + b[3][4], a[0][4]});
    c[1][1] = a[1][1] + b[1][1];
    c[1][2] = max({a[1][1] + b[1][2], a[1][2]});
    c[1][3] = max({a[1][1] + b[1][3], a[1][2] + b[2][3], a[1][3] + b[3][3]});
    c[1][4] = max({a[1][1] + b[1][4], a[1][2] + b[2][4], a[1][3] + b[3][4], a[1][4]});
    c[2][2] = 0;
    c[2][3] = max({b[2][3], a[2][3] + b[3][3]});
    c[2][4] = max({b[2][4], a[2][3] + b[3][4], a[2][4]});
    c[3][3] = a[3][3] + b[3][3];
    c[3][4] = max({a[3][3] + b[3][4], a[3][4]});
    c[4][4] = 0;
    return c;
}

matrix pack(int i){
    matrix res; res.n = res.m = 5;
    res[0][0] = res[2][2] = res[4][4] = 0;
    res[0][1] = res[1][2] = res[2][3] = res[3][4] = a[i] + b[i];
    res[0][2] = res[2][4] = a[i] + 2ll * b[i];
    res[1][1] = res[3][3] = a[i];
    return res;
}

matrix t[N << 2];

void build(int i, int l, int r){
    if(l == r) return t[i] = pack(l), void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    t[i] = t[ls] * t[rs];
}

void update(int p, int i, int l, int r){
    if(l == r) return t[i] = pack(p), void();
    int mid = (l + r) >> 1;
    if(p <= mid) update(p, ls, l, mid);
    else update(p, rs, mid + 1, r);
    t[i] = t[ls] * t[rs];
}

matrix query(int ql, int qr, int i, int l, int r){
    if(ql <= l && r <= qr) return t[i];
    int mid = (l + r) >> 1;
    if(ql <= mid && qr > mid) return query(ql, qr, ls, l, mid) * query(ql, qr, rs, mid + 1, r);
    if(ql <= mid) return query(ql, qr, ls, l, mid);
    return query(ql, qr, rs, mid + 1, r);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    build(1, 1, n);
    cin >> m;
    while(m--){
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1) a[x] = y, update(x, 1, 1, n);
        if(op == 2) b[x] = y, update(x, 1, 1, n);
        if(op == 3){
            matrix ret = query(x, y, 1, 1, n);
            matrix tmp; tmp.n = 1, tmp.m = 5;
            tmp[0][0] = 0;
            ret = tmp * ret;
            cout << ret[0][4] << '\n';
        }
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：postpone (赞：0)

> 思路来自 jls 的赛时做法，可能算比较“板”。

本题的核心难点有两个：

1. 如何去维护区间中最大子段？
1. 如何保证两个区间不相交？

先看第一个，如果 $b$ 数组全是 $0$，那就是板子题，维护前缀后缀以及答案。带上 $b$ 一起考虑，我们可以想象，此时要维护一个没有“开口”的子段。

||l|l+1|...|r-1|r|
|:-:|:-:|:-:|:-:|:-:|:-:|
|a|$\green{\blacksquare}$|$\green{\blacksquare}$|$\green{\blacksquare}$|$\green{\blacksquare}$|$\green{\blacksquare}$|
|b|$\red{\blacksquare}$||||$\red{\blacksquare}$|

如上表所示，我们要维护这个东西。那么有开口是什么样子呢？看下表。

||l|l+1|...|r|...|
|:-:|:-:|:-:|:-:|:-:|:-:|
|a|$\green{\blacksquare}$|$\green{\blacksquare}$|$\green{\blacksquare}$|$\green{\blacksquare}$|$\green{\blacksquare}$|
|b|$\red{\blacksquare}$|||||

这肯定就不符合要求，我们形象地称为“向右开口”，向左开口同理，就是左边没闭上。

如果只需要维护一个没有开口的子段，我们不妨让前缀和后缀分别表示**向左开口**和**向右开口**的子段，而合并时，左区间的后缀与右区间的前缀，就能合并成为没有开口的子段了，例如下表的中间那段。

||L.l|...|...|L.r|R.l|...|...|R.r|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|a|$\green{\blacksquare}$||$\green{\blacksquare}$|$\green{\blacksquare}$|$\green{\blacksquare}$||$\green{\blacksquare}$|$\green{\blacksquare}$|
|b|$\red{\blacksquare}$||$\red{\blacksquare}$||$\red{\blacksquare}$||$\red{\blacksquare}$|

那要怎么实现呢？我们只需要在初始化上动点手脚就行了。

```cpp
constexpr i64 inf = 1e18;

struct Info {
    i64 ans = -inf;
    i64 l = -inf;
    i64 r = -inf;
    i64 sum = 0;

    Info() {}
    Info(i64 a, i64 b) {
        sum = a;
        l = a + b;
        r = a + b;
        ans = a + 2 * b; // 表示只选自己，两个闭口都是自己
    }
};
// 合并与板子完全一样
Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.l = Max(a.l, b.l + a.sum); // 开口肯定朝左
    c.r = Max(a.r + b.sum, b.r); // 开口肯定朝右
    c.ans = Max(a.ans, b.ans, a.r + b.l); //肯定没有开口
    return c;
}
```

到目前为止，我们解决了第一个问题，现在我们来看第二个：怎么同时维护两个不相交的区间呢？情况略显复杂，我们先想想在两个区间合并时，答案可能会来自哪里。

1. 都严格位于同一个区间内。
2. 分别严格位于不同区间内（一个左，一个右）。
3. 一个严格在一子区间中，另一个是跨区间的。

第 1 条和第 2 条都很简单，但第 3 条很麻烦，对此我们需要以下信息：

- $\text{sum}$：区间和。
- $\text{l}_1$：向左开口的前缀。
- $\text{r}_1$：向右开口的后缀。
- $\text{mid}$：两个**不相交**的子段，一个向左开口，一个向右开口。
- $\text{l}_2$：两个不相交的子段，一个没有开口，一个是向左开口。
- $\text{r}_2$：两个不相交的子段，一个没有开口，一个向右开口。
- $\text{ans}_1$：一个没有开口的子段。
- $\text{ans}_2$：两个没有开口的子段。

用 $\text{l}_1$ 和 $\text{r}_1$ 来更新 $\text{ans}_1$ 和 $\text{mid}$；用 $\text{mid}$ 来更新 $\text{l}_2$ 和 $\text{r}_2$；最后再一起更新 $\text{ans}_2$，这样一定是正确的。

若不理解，可以像上文的表格一样，画一下推一下。

具体合并如代码所示。之所以说这个思路比较“板”，因为确实没有太多推导的成分，理解并记住就行了。总复杂度 $O((n+m)\log n)$

```cpp
constexpr i64 inf = 1e18;

struct Info {
    i64 ans1 = -inf;
    i64 ans2 = -inf;

    i64 l1 = -inf;
    i64 l2 = -inf;

    i64 r1 = -inf;
    i64 r2 = -inf;

    i64 sum = 0;
    i64 mid = -inf;

    Info() {}
    Info(i64 a, i64 b) {
        ans1 = a + 2 * b;
        l1 = a + b;
        r1 = a + b;
        sum = a;
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;

    c.ans1 = Max(a.ans1, b.l1 + a.r1, b.ans1);
    c.ans2 = Max(a.ans2, b.l1 + a.r2, b.ans1 + a.ans1, b.l2 + a.r1, b.ans2);

    c.l1 = Max(a.l1, b.l1 + a.sum);
    c.l2 = Max(a.l2, b.l1 + a.mid, b.ans1 + a.l1, b.l2 + a.sum);

    c.r1 = Max(a.r1 + b.sum, b.r1);
    c.r2 = Max(a.r2 + b.sum, a.ans1 + b.r1, a.r1 + b.mid, b.r2);

    c.sum = b.sum + a.sum;
    c.mid = Max(a.mid + b.sum, b.r1 + a.l1, b.mid + a.sum);

    return c;
}
```

[完整代码](https://codeforces.com/contest/2042/submission/309133099)

---

## 作者：wfc284 (赞：0)

一个很显然的线段树。

我们仿照 [P4513](https://www.luogu.com.cn/problem/P4513) 求区间最大子段和的思路，可以用线段树维护区间前缀、后缀以及最终答案相关的一堆东西，是可做的，但是细节很多，容易亖。常数 $10$ 左右，吊打 DDP 做法。

再说一下被吊打的 DDP：（参考这位[大佬](https://www.luogu.com.cn/user/1061285)的题解）  
![](https://cdn.luogu.com.cn/upload/image_hosting/z70q8eex.png)

我们观察这幅图（红色为点权，紫色为边权），区间的答案就是从 $(l,1)$ 走到 $(r,5)$ 的最长路。这可以用 DP 求解。  

这个有点小问题，本列的状态会由本列的转移，有点丑。  
我们改进一下图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/48nvnx83.png)

不难发现，这样是和原图等价的。  

设 $f_{i,j}$ 为起点 $(l, 1)$ 到 $(i,j)$ 的最长路。那么 $f_l = [0, a_l+b_l, a_l+2b_l, -\infty, -\infty]$。  
转移有：
$$
\begin{aligned}
f_{i,1} & = f_{i-1,1} \\
f_{i, 2} & = \max(f_{i-1, 1} + a_i + b_i, f_{i-1, 2} + a_i) \\
f_{i, 3} & = \max(f_{i-1, 1} + a_i + 2b_i, f_{i-1, 2} + a_i + b_i, f_{i-1, 3}) \\
f_{i, 4} & = \max(f_{i-1, 3} + a_i + b_i, f_{i-1, 4} + a_i) \\
f_{i, 5} & = \max(f_{i-1, 3} + a_i + 2b_i, f_{i-1, 4} + a_i + b_i, f_{i-1, 5})
\end{aligned}
$$

写成矩阵的形式就是：
$$
\begin{bmatrix}
f_{i-1, 1} & f_{i-1, 2}  & f_{i-1, 3}  & f_{i-1, 4} & f_{i-1, 5} \\
\end{bmatrix}
\begin{bmatrix}
0  & a_i+b_i & a_i+2b_i & -\infty & -\infty \\
-\infty  & a_i & a_i+b_i & -\infty & -\infty\\
-\infty  & -\infty & 0 & a_i+b_i & a_i+2b_i \\
-\infty  & -\infty & -\infty & a_i & a_i+b_i \\
-\infty  & -\infty & -\infty & -\infty 0 &
\end{bmatrix}
=
\begin{bmatrix}
f_{i, 1} & f_{i, 2}  & f_{i, 3}  & f_{i, 4} & f_{i, 5} \\
\end{bmatrix}
$$
其中矩阵乘法重定义为 $+,\max$。

记转移矩阵为 $A_i$。单点修改 $A_i$，区间查询答案就是 $ ([0, a_l+b_l, a_l+2b_l, -\infty, -\infty] \times \prod_{i=l+1}^{r}A_i)_5 $。发现这个东西恰好是 $(\prod_{i=l}^{r}A_i)_{1,5}$。

时间复杂度 $O(k^3(n+q)\log n)$，其中 $k$ 为矩阵大小，为 $5$。

---

