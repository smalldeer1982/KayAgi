# [EPXLQ2024 fall round] 如今走过这世间

## 题目背景

温昭雪开始了上传视频，成为大 uploader 之路。

这天，她所在的视频平台上线了一个激励计划。

## 题目描述

温昭雪有 $n$ 个视频要发布，每个视频可以是 $t$ 个分类中的一种。初始时温昭雪有 $k$ 分。每当她发布一个类型为 $j$ 的视频，设她上一个发布的视频类型为 $i$，则她的分数会在发布这个视频后立刻乘上 $d_{i,j}$（如果是第 $1$ 个视频，分数不会变化）。**然后**，设当前有 $x$ 分，则会得 $b_j\times x$ 的收益。

温昭雪是个有点随意的人，所以她每次会**等概率随机选择**一个视频的类型（除了第一个视频的类型固定为 $v$）。现在她想知道在这样发视频的情况下，她能获得总收益的期望。

## 说明/提示

### 样例解释

显然，所有以 $v$ 开头的发布视频的序列具有相同的概率出现。

当发布第 $2$ 个视频时，分数与获得收益的可能性如下表：

| 视频类型 | 发布后分数 | 总收益 |
| :-: | :-: | :-: |
| $1$ | $100$ | $500+500=1000$ |
| $2$ | $90$ | $500+900=1400$ |
| $3$ | $80$ | $500+1200=1700$ |

令 $F$ 表示发布第 $3$ 个视频前的分数，$P$ 表示发布第 $3$ 个视频前的收益，则：

- 发布第 $3$ 个视频后的分数为：


| 第 $3$ 个视频类型（行）/ 第 $2$ 个视频类型（列） | $1$（$F=100$） | $2$（$F=90$） | $3$（$F=80$） |
| :-: | :-: | :-: | :-: |
| $1$ | $100$ | $63$ | $48$ |
| $2$ | $90$ | $90$ | $88$ |
| $3$ | $80$ | $72$ | $80$ |

- 发布第 $3$ 个视频后能获得的最终收益为：


| 第 $3$ 个视频类型（行）/ 第 $2$ 个视频类型（列） | $1$（$P = 1000$） | $2$（$P=1400$） | $3$（$P=1700$） |
| :-: | :-: | :-: | :-: |
| $1$ | $1000 + 500$ | $1400+315$ | $1700+240$ |
| $2$ | $1000 + 900$ | $1400+900$ | $1700+880$ |
| $3$ | $1000 + 1200$ | $1400+1080$ | $1700+1200$ |

因此，总收益期望为 ${19515 \over 9}={6505 \over 3} \approx 2168.333333$。在本样例所示数据范围下，`decimal` 和 `inverse` 输出均可用，两种答案均正确。

### 数据规模与约定

**本题采用捆绑测试。**

| $\text{Subtask}$ | $n \le$ | $t \le $ | 特殊性质 | 是否可使用 `decimal` | 分值 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $0$ | $8$ | $8$ | | 是 | $9$ |
| $1$ | $18$ | $200$ | | 是 | $6$ |
| $2$ | $10^9$ | $1$ | | 否 | $4$ |
| $3$ | $100$ | $200$ | | 是 | $7$ |
| $4$ | $100$ | $200$ | A | 是 | $10$ |
| $5$ | $10^9$ | $200$ | B | 是 | $6$ |
| $6$ | $10^9$ | $100$ | | 否 | $12$ |
| $7$ | $10^4$ | $200$ | | 否 | $11$ |
| $8$ | $10^9$ | $200$ | | 否 | $35$ |

特殊性质 A：$d_{i,j} \in \{0,0.5,1\}$。

特殊性质 B：$d_{i,j}=1$。

对于所有数据，保证 $1 \le n \le 10^9, 1 \le t \le 200, 0 \le d \le 2$。

## 样例 #1

### 输入

```
3 3 100 1 0
5 10 15
100 90 80
70 100 80
60 110 100```

### 输出

```
decimal 2168.333333```

## 样例 #2

### 输入

```
3 3 100 1 0
5 10 15
100 90 80
70 100 80
60 110 100```

### 输出

```
inverse 332750286```

# 题解

## 作者：Alphas (赞：3)

如何达成以最优解倒数第一通过此题？~~官解竟然认为该做法只能获得 48 分？~~

考虑维护一个 $2\times 2$ 的矩阵:

$$\begin{bmatrix}
 x & y\\
 0 & 0
\end{bmatrix}$$

其中 $x_i$ 表示当前最后一个的类型是 $i$ 的期望收益，$y_i$ 表示当前最后一个的类型是 $i$ 的期望分数。那么我们上一个类型是 $i$，转移到下一个视频类型为 $j$ 的矩阵的贡献是：

$$\begin{bmatrix}
(x_i+b_j\cdot d_{i,j}\cdot y_i)\frac 1n & y_i\cdot d_{i,j}\cdot \frac 1n \\
 0 & 0
\end{bmatrix}$$

那么转移矩阵是：

$$\begin{bmatrix}
 \frac 1n & 0 \\
 \frac{b_{i,j}\cdot d_j}{n} & \frac{d_{i,j}}{n}
\end{bmatrix}$$

于是我们很自然的将每个 $i\rightarrow j$ 的 $2\times 2$ 的小转移矩阵放到新加入一个位置时的 $t\times t$ 的大转移矩阵的 $i$ 行 $j$ 列的位置上，转移直接做矩阵乘法就行，需要手写 $2\times 2$ 矩阵的加、乘。注意特判 $n=1$。

时间复杂度 $\Theta(t^3\log n)$。$2\times 2$ 矩阵自带 8 倍常数。

于是官解认为这就过不了了，实测也只有 48 分。[记录](https://www.luogu.com.cn/record/194707249)

但是真的是这样的吗？我们认为计算过程的极大开销在于取模，考虑能否减少一些这样的操作，并发现可以轻松做到这一点，相信不少习惯好的人本来就是这么写的。

我们首先将 $2\times 2$ 矩阵的乘法中的三层 for 删了，因为只有 4 个位置，所以直接把式子手写上去就行，这样，我们不但省去了 `i++` 这样自增操作的运算次数，还将取模次数减半了，因为原来为了不溢出我们是 `res.d[i][k] = (res.d[i][k] + d[i][j] * rhs.d[j][k]) % mod` 对于每个 $(i, k)$ 执行了两遍，现在 `res.d[i][k] = (d[i][0] * rhs.d[0][k] + d[i][1] * rhs.d[1][k]) % mod` 对于每个 $(i, k)$ 执行了一遍。

乘法操作常数减半，成功获得 65 分。[记录](https://www.luogu.com.cn/record/194709441)

然后就简单优化一下加法就行了，我们把 `res.d[i][j] = (d[i][j] + rhs.d[i][j]) % mod` 变成直接相加后 `if (res.d[i][j] >= mod) res.d[i][j] -= mod`，于是又扔掉了很多的取模操作。

于是获得了 100 分。记得加 inline，虽然我也不知道为什么加了以后快了 0.2s。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 201;
const int mod = 998244353;

ll ans, invn, inv100, b[MAXN];
int m, n, K, id, sid;

struct matrix2 {
    ll d00, d01, d10, d11;
    matrix2() {
        d00 = d01 = d10 = d11 = 0;
    }
    matrix2 operator * (const matrix2 &rhs) const {
        matrix2 res;
        res.d00 = (d00 * rhs.d00 + d01 * rhs.d10) % mod;
        res.d01 = (d00 * rhs.d01 + d01 * rhs.d11) % mod;
        res.d10 = (d10 * rhs.d00 + d11 * rhs.d10) % mod;
        res.d11 = (d10 * rhs.d01 + d11 * rhs.d11) % mod;
        return res;
    }
    matrix2 operator + (const matrix2 &rhs) const {
        matrix2 res;
        res.d00 = d00 + rhs.d00;
        if (res.d00 >= mod) 
            res.d00 -= mod;
        res.d01 = d01 + rhs.d01;
        if (res.d01 >= mod) 
            res.d01 -= mod;
        res.d10 = d10 + rhs.d10;
        if (res.d10 >= mod) 
            res.d10 -= mod;
        res.d11 = d11 + rhs.d11;
        if (res.d11 >= mod) 
            res.d11 -= mod;
        return res;
    }
} one;

struct matrixn {
    matrix2 d[MAXN][MAXN];
    matrixn operator * (const matrixn &rhs) const {
        matrixn res;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) 
                    res.d[i][k] = res.d[i][k] + d[i][j] * rhs.d[j][k];
        return res;
    }
} One, zy, st;

inline ll fpow(ll x, ll y) {
    int t = 1;
    while (y) {
        if (y & 1) 
            t = t * x % mod;
        x = x * x % mod;
        y /= 2;
    }
    return t;
}

inline matrixn fpowm(ll y) {
    matrixn t = One;
    while (y) {
        if (y & 1) 
            t = t * zy;
        zy = zy * zy;
        y /= 2;
    }
    return t;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> m >> n >> K >> id >> sid, id --;
    one.d00 = one.d11 = 1;
    for (int i = 0; i < n; i++) 
        One.d[i][i] = one;
    invn = fpow(n, mod - 2), inv100 = fpow(100, mod - 2);
    for (int i = 0; i < n; i++) 
        cin >> b[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            ll x;
            cin >> x, x = x * inv100 % mod;
            matrix2 tmp;
            tmp.d00 = invn;
            tmp.d10 = x * b[j] % mod * invn % mod;
            tmp.d11 = x * invn % mod;
            zy.d[i][j] = tmp;
        }
    matrix2 tmp;
    tmp.d00 = K * b[id] % mod, tmp.d01 = K;
    st.d[0][id] = tmp;
    if (m == 1) {
        cout << "inverse " << tmp.d00 << '\n';
        return 0;
    }
    st = st * fpowm(m - 1);
    for (int i = 0; i < n; i++) 
        ans = (ans + st.d[0][i].d00) % mod;
    cout << "inverse " << ans << '\n';
    return 0;
}
```

---

