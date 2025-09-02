# 【MX-X11-T5】「蓬莱人形 Round 1」俄罗斯方块

## 题目背景

原题链接：<https://oier.team/problems/X11F>。

---

「興味がないこと本気じゃないもの全部後回しで」

「知ってることは知らんぷり 私は終わってる」

「恥ずかしい過去知ってるやつらの記憶消させて」

「迷惑かけてごめんってば ねえ誰か助けて」

## 题目描述

给定一个长为 $n$ 的整数序列 $h_i$，再给定 $n$ 个二元组 $(a_i,b_i)$，和一个正整数 $k$。


对于每个位置 $p$，你可以进行如下操作之一：

- 激活位置 $p$，选择一个位置 $j$ 满足 $1\le j-p\le k$，然后令 $h_p \leftarrow h_p + a_p$、$h_j \leftarrow h_j - b_p$。**每个位置最多激活一次**。

- 不激活位置 $p$。

有 $q$ 次询问 $(l_i,r_i,x_i)$，表示在只能激活位置 $p\in[l_i,r_i]$，且对应的 $j\in [p+1,\min(p+k,r_i)]$ 的条件下，可以选择多个位置激活，问此时是否存在一种激活方式使得 $\max_{t=l_i}^{r_i}h_t\le x_i$。

询问之间互相独立，即每次询问开始时序列 $h$ 被恢复到原始状态，每个位置均未选择操作方式。

## 说明/提示

**【样例解释 #1】**

对于询问 $(2,3,1)$，可以激活位置 $2$，令 $h_2 \leftarrow h_2 + a_2$、$h_3 \leftarrow h_3 - b_2$，最后的 $h$ 的区间 $[2,3]$ 为 $1,-6$，最大值为 $1$，符合要求。

对于询问 $(1,3,1)$，可以证明没有合法的操作方案。

**【数据范围】**

**本题使用子任务捆绑**。

对于所有测试数据，$1 \le T \le 3$，$1 \le n \le 2 \times 10^4$，$1\le q \le 10^5$，$0\le h_i,a_i,b_i,x_i \le 10^6$，$1\le l_i \le r_i \le n$，$1\le k \le 5$。

|子任务编号|$n\le$|$q \le$|$k \le$|$T \le$|特殊性质|分值|时限|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$10$|$10$|$5$|$3$|无|$5$|1 s|
|$2$|$1000$|$1000$|$5$|$1$|无|$10$|1 s|
|$3$|$2\times 10^4$|$10^5$|$5$|$3$|A|$10$|4 s|
|$4$|$10^4$|$10^4$|$3$|$1$|B|$5$|1 s|
|$5$|$10^4$|$10^4$|$3$|$1$|无|$10$|1 s|
|$6$|$2\times 10^4$|$2\times 10^4$|$4$|$1$|B|$5$|1 s|
|$7$|$2\times 10^4$|$2\times 10^4$|$4$|$1$|无|$10$|1 s|
|$8$|$2\times 10^4$|$4\times 10^4$|$4$|$2$|B|$5$|1 s|
|$9$|$2\times 10^4$|$4\times 10^4$|$4$|$2$|无|$10$|1 s|
|$10$|$2\times 10^4$|$10^5$|$5$|$3$|无|$30$|4 s|

- 特殊性质 A：$\forall 1 \le i \le q,l_i=1,r_i = n$。
- 特殊性质 B：$\forall 1 \le i,j \le q,x_i = x_j$。

**【提示】**

请注意本题特别的时间限制。

## 样例 #1

### 输入

```
0 1
3 2 1
2 0 2
4 1 1
0 8 0
2 3 1
1 3 1```

### 输出

```
Yes
No```

## 样例 #2

### 输入

```
0 2
7 7 3
4 1 2 2 3 2 2
4 1 4 0 3 2 1
3 3 4 1 3 3 0
5 5 4
3 4 5
1 4 3
2 5 0
1 2 3
1 4 5
1 3 4
7 7 3
5 2 1 5 2 5 2
4 2 1 4 3 1 2
1 5 3 4 1 5 1
6 7 5
1 4 5
2 4 5
5 7 5
1 2 5
3 4 5
2 6 5```

### 输出

```
Yes
Yes
No
No
No
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
```

# 题解

## 作者：Engulf (赞：2)

:::warning[写在前面]{open}

本题解十分详细。按照正常思考顺序编写，可以跳转到自己卡壳的地方开始阅读。

**只有绿色折叠框的代码 6 能够通过本题。**
:::

### subtask 1

暴力，枚举每个位置激活与否，若激活，激活了后面的哪个。

$\Theta(qk^n)$。

:::info[代码 1]
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using pii = pair<int, int>;
 
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
 
const int N = 2e4 + 5;
 
int n, q, k;
int h[N], a[N], b[N];
int backup[N];
 
int dfs(int u, int l, int r, int x) {
    if (u > r) {
        return *max_element(h + l, h + 1 + r) <= x;
    }
 
    if (dfs(u + 1, l, r, x)) return true;
 
    for (int j = u + 1; j <= min(u + k, r); j++) {
        h[u] += a[u];
        h[j] -= b[u];
        if (dfs(u + 1, l, r, x)) return true;
        h[u] -= a[u];
        h[j] += b[u];
    }
 
    return false;
}
 
void subtask1() {
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
 
        for (int i = l; i <= r; i++) h[i] = backup[i];
 
        cout << (dfs(l, l, r, x) ? "Yes\n" : "No\n");
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, tt;
    cin >> c >> tt;
    while (tt--) {
        cin >> n >> q >> k;
        for (int i = 1; i <= n; i++) cin >> h[i], backup[i] = h[i];
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
 
        subtask1();
    }
    return 0;
}
```
:::

代码 1 期望获得 $5$ 分，实际获得 $5$ 分。

### subtask 2 & 3

$k\le 5$，考虑状压 dp。

设 $f_{i, S}$ 表示：处理至点 $i$，往前 $k$ 个点（**包括点** $i$）的状态为 $S$，此时前 $i$ 个数的最大值 的最小值。

其中 $S$ 是一个二进制数，$S$ 的第 $t(0\le t <k)$ 位为 $1$ 表示点 $i - t$ **已激活**，**但还没有往后贡献**（对应题目中就是，激活了点 $p$，但还没往后选择点 $j$）。

转移的时候，枚举 $S$ 的子集 $T$，让 $T$ 中的点贡献给 $i + 1$，即让 $h_{i + 1}$ 减去 $T$ 中点的 $b$。

而点 $i + 1$ 有激活与不激活两种选项，分别写出转移：
- 不激活点 $i + 1$：
  $$f_{i + 1, (S \oplus T) \ll 1} = \min\left(f_{i + 1, (S \oplus T) \ll 1}, \max\left(f_{i, S}, h_{i + 1} - \sum\limits_{x \in T}b_x\right)\right)$$
- 激活点 $i + 1$：
  $$f_{i + 1, (S \oplus T) \ll 1 | 1} = \min\left(f_{i + 1, (S \oplus T) \ll 1 | 1}, \max\left(f_{i, S}, h_{i + 1} + a_{i + 1} - \sum\limits_{x \in T} b_x\right)\right)$$

其中 $S \oplus T$ 表示去掉了子集 $T$（贡献给了 $i + 1$），或上 $1$ 表示激活点 $i + 1$，因为只处理到 $i + 1$，肯定是无法往后贡献的。

边界条件：$f_{l, 0} = h_l,f_{l, 1} = h_l + a_l$。其他状态初始设置为 $+\infty$。

若 $f_{r, 0} \le x$（所有激活了的点都贡献了出去），答案为 `Yes`，否则为 `No`。

$\Theta(qn3^k)$。

:::info[代码 2]
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using pii = pair<int, int>;
 
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
 
const int N = 2e4 + 5;
const int inf = 0x3f3f3f3f;
 
int n, q, k;
int h[N], a[N], b[N];
 
int f[N][32];
 
void chkmin(int &x, int y) {x = min(x, y);}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc, tt;
    cin >> tc >> tt;
    while (tt--) {
        cin >> n >> q >> k;
        for (int i = 1; i <= n; i++) cin >> h[i];
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
 
        while (q--) {
            int l, r, x;
            cin >> l >> r >> x;
 
            for (int i = l; i <= r; i++)
                for (int j = 0; j < (1 << k); j++)
                    f[i][j] = inf;
            f[l][0] = h[l], f[l][1] = h[l] + a[l];
            for (int i = l; i < r; i++) {
                for (int j = 0; j < (1 << min(k, i - l + 1)); j++) {
                    chkmin(f[i + 1][j << 1 & 31], max(f[i][j], h[i + 1]));
                    chkmin(f[i + 1][(j << 1 | 1) & 31], max(f[i][j], h[i + 1] + a[i + 1]));
                    for (int s = j; s; s = (s - 1) & j) {
                        int d = 0;
                        for (int t = 0; t < min(k, i - l + 1); t++)
                            if (s >> t & 1) if (i - t >= l)
                                d += b[i - t];
                        chkmin(f[i + 1][(j ^ s) << 1 & 31], max(f[i][j], h[i + 1] - d));
                        chkmin(f[i + 1][((j ^ s) << 1 | 1) & 31], max(f[i][j], h[i + 1] + a[i + 1] - d));
                    }
                }
            }
 
            cout << (f[r][0] <= x ? "Yes\n" : "No\n");
        }
    }
    return 0;
}
```
:::

代码 2 期望获得 $25$ 分，实际获得 $15$ 分（这份代码没有特殊处理特殊性质 A，A 的话只要跑一遍全局的 dp 就行）。

### subtask 4 ~ 7

如何加速区间询问？

观察转移方程：

$$f_{i + 1, (S \oplus T) \ll 1} = \min\left(f_{i + 1, (S \oplus T) \ll 1}, \max\left(f_{i, S}, h_{i + 1} - \sum\limits_{x \in T}b_x\right)\right)$$

  $$f_{i + 1, (S \oplus T) \ll 1 | 1} = \min\left(f_{i + 1, (S \oplus T) \ll 1 | 1}, \max\left(f_{i, S}, h_{i + 1} + a_{i + 1} - \sum\limits_{x \in T} b_x\right)\right)$$

可以发现它们的形式都类似这样：

$$f_{i + 1, U} = \min\left(f_{i + 1, U}, \max\left(f_{i, S}, v\right)\right)$$

由于 $\min$ 运算对 $\max$ 运算有分配律（反过来也成立哦），上式可以矩阵乘法加速，定义转移矩阵 $A_{S, U} = v$，那么 $f_{i + 1} = f_i \times A$。

进一步发现，每个 $i$ 对应的转移矩阵 $A$ 是一样的，问题转化成了求静态的区间矩阵乘积，使用线段树维护。

注意询问的时候，查到线段树上对应的某个区间的矩阵乘积，直接用答案向量 $f$ 去乘它，不要把一堆这些矩阵乘在一次，不然时间复杂度会多乘上一个 $2^k$。

$\Theta(n8^k + q4^k\log n)$。

:::info[代码 3]
```
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e4 + 5;
const int inf = 0x3f3f3f3f;

int n, q, k;
int h[N], a[N], b[N];

// int f[N][32];

void chkmin(int &x, int y) {x = min(x, y);}

using Matrix = vector<vector<int>>;

Matrix I() {Matrix I(1 << k, vector<int>(1 << k, inf)); for (int i = 0; i < I.size(); i++) I[i][i] = -inf; return I;}

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c(1 << k, vector<int>(1 << k, inf));

    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b[0].size(); j++)
            for (int k = 0; k < b.size(); k++)
                c[i][j] = min(c[i][j], max(a[i][k], b[k][j]));

    return c;
}

Matrix tr[N << 2];

void build(int p, int l, int r) {
    if (l == r) {
        tr[p].assign(1 << k, vector<int>(1 << k, inf));
        for (int j = 0; j < (1 << k); j++) {
            chkmin(tr[p][j][j << 1 & (1 << k) - 1], h[l + 1]);
            chkmin(tr[p][j][(j << 1 | 1) & (1 << k) - 1], h[l + 1] + a[l + 1]);
            for (int s = j; s; s = (s - 1) & j) {
                int d = 0;
                bool valid = true;
                for (int t = 0; t < k; t++)
                    if (s >> t & 1) {
                        if (l - t < 1) {
                            valid = false;
                            break;
                        }
                        d += b[l - t];
                    }
                if (!valid) continue;
                chkmin(tr[p][j][(j ^ s) << 1 & (1 << k) - 1], h[l + 1] - d);
                chkmin(tr[p][j][((j ^ s) << 1 | 1) & (1 << k) - 1], h[l + 1] + a[l + 1] - d);
            }
        }
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    tr[p] = tr[p << 1] * tr[p << 1 | 1];
}

void query(int p, int l, int r, int L, int R, Matrix &f) {
    if (L > R || r < L || l > R) return;
    if (L <= l && r <= R) {f = f * tr[p]; return;}
    int mid = l + r >> 1;
    query(p << 1, l, mid, L, R, f);
    query(p << 1 | 1, mid + 1, r, L, R, f);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc, tt;
    cin >> tc >> tt;
    while (tt--) {
        cin >> n >> q >> k;
        for (int i = 1; i <= n; i++) cin >> h[i];
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        build(1, 1, n - 1);

        while (q--) {
            int l, r, x;
            cin >> l >> r >> x;

            Matrix f(1, vector<int>(1 << k, inf));
            f[0][0] = h[l], f[0][1] = h[l] + a[l];

            // auto A = query(1, 1, n, l, r - 1);

            query(1, 1, n - 1, l, r - 1, f);

            cout << (f[0][0] <= x ? "Yes\n" : "No\n");
        }
    }
    return 0;
}
```
:::

代码 3 期望得分 $70$ 分，实际得分 $55$ 分（常数太大）。

### subtask 8

观察特殊性质 B：所有 $x$ 均相等。

实际上我们只关心每个数相对 $x$ 的大小关系，不妨令 $\le x$ 的数为 $0$，$>x$ 的数为 $1$，把 $2^k \times 2^k$ 的矩阵改成 $2^k$ 个 `bitset`，每个 `bitset` $2^k$ 位。其他同上。

用 `bitset` 加速矩阵乘法，具体地，原本的矩阵乘法形如

$$c_{i, j} = \min_{k}\max(a_{i, k}, b_{k, j})$$

改成 $0/1$ 后可以用位运算

$$c_{i, j} = \text{and}_k(a_{i, k} \ \text{or} \ b_{k, j})$$

$j$ 这一维可以省略了，仅需枚举 $i$ 和 $k$。
- 若 $a_{i, k} = 1$，后面 $\max(a_{i, k}, b_{k, j})$，也就是 $a_{i, k}\ \text{or} \ b_{k, j}$ 一定为 $1$，前面对 $1$ 取 $\min$ 显然不会影响 $c_{i, j}$。
- 若 $a_{i, k} = 0$，它不会影响 $\max$，可以直接拿掉，
  $$c_{i, j} = \text{and}_k b_{k, j}$$

  既然用了 `bitset`，就直接 $c_i = c_i \ \text{and} \  b_i$ 即可，复杂度除以 $w$。

$\Theta\left(\dfrac{n8^k + q4^k \log n}{w}\right)$。

:::info[代码 4]
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using pii = pair<int, int>;
 
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
 
const int N = 2e4 + 5;
const ll inf = (1ll << 32) - 1;
 
int n, q, k, x;
int h[N], a[N], b[N];
 
// int f[N][32];
 
using Matrix = vector<bitset<32>>;
 
ostream& operator<<(ostream &os, const Matrix &b) {
    for (int i = 0; i < b.size(); i++) {
        os << b[i];
        if (i != b.size() - 1)
            os << "\n";
    }
    return os;
}
 
Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c(32, bitset<32>(inf));
 
    for (int i = 0; i < a.size(); i++)
        for (int k = 0; k < b.size(); k++)
            if (!a[i][k])
                c[i] &= b[k];
 
    // for (int i = 0; i < a.size(); i++)
    //     for (int j = 0; j < b[0].size(); j++)
    //         for (int k = 0; k < b.size(); k++)
    //             c[i][j] = c[i][j] & (a[i][k] | b[k][j]);
 
    return c;
}
 
Matrix tr[N << 2];
 
void build(int p, int l, int r) {
    if (l == r) {
        tr[p].assign(32, bitset<32>(inf));
        for (int j = 0; j < (1 << k); j++) {
            tr[p][j][j << 1 & 31] = (h[l + 1] > x);
            tr[p][j][(j << 1 | 1) & 31] = (h[l + 1] + a[l + 1] > x);
            for (int s = j; s; s = (s - 1) & j) {
                int d = 0;
                bool valid = true;
                for (int t = 0; t < k; t++)
                    if (s >> t & 1) {
                        if (l - t < 1) {
                            valid = false;
                            break;
                        }
                        d += b[l - t];
                    }
                if (!valid) continue;
 
                tr[p][j][(j ^ s) << 1 & 31] = tr[p][j][(j ^ s) << 1 & 31] & (h[l + 1] - d > x);
                tr[p][j][((j ^ s) << 1 | 1) & 31] = tr[p][j][((j ^ s) << 1 | 1) & 31] & (h[l + 1] + a[l + 1] - d > x);
            }
        }
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    tr[p] = tr[p << 1] * tr[p << 1 | 1];
}
 
void query(int p, int l, int r, int L, int R, Matrix &f) {
    if (L > R || r < L || l > R) return;
    if (L <= l && r <= R) {f = f * tr[p]; return;}
    int mid = l + r >> 1;
    query(p << 1, l, mid, L, R, f);
    query(p << 1 | 1, mid + 1, r, L, R, f);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc, tt;
    cin >> tc >> tt;
    while (tt--) {
        cin >> n >> q >> k;
        for (int i = 1; i <= n; i++) cin >> h[i];
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
 
        int l, r;
        cin >> l >> r >> x;
 
        build(1, 1, n - 1);
 
        while (q--) {
            Matrix f(32, bitset<32>(inf));
            f[0][0] = (h[l] > x), f[0][1] = (h[l] + a[l] > x);
 
            query(1, 1, n - 1, l, r - 1, f);
 
            cout << (!f[0][0] ? "Yes\n" : "No\n");
 
            if (q) cin >> l >> r >> x;
        }
    }
    return 0;
}

```
:::

代码 4 期望得分 $15$ 分，实际得分 $10$ 分（常数太大）。

### subtask 9 & 10

考虑推广特殊性质 B。将询问离线，将所有询问和 $A_{S, U} = v$ 这样的修改，按照 $x$（对于修改，则是 $v$）从小到大排序，优先修改后查询。

初始时从小到大遍历询问和修改，如果是询问，正常查询即可。

如果是修改，发现修改仅仅是将线段树某个叶子节点的矩阵的第 $S$ 行 $U$ 列置 $0$，如果 pushup 的时候直接左儿子矩阵乘右儿子矩阵，复杂度爆炸。

我们只考虑哪些位置要重新更新。叶子节点直接更改。

接下来，令左儿子的矩阵是 $a$，右儿子的矩阵是 $b$，该节点的矩阵是 $c$。

$$c_{i, j} = \min_k\max(a_{i, k}, b_{k, j})$$

$$c_{i, j} = \text{and}_k(a_{i, k} \ \text{or} \ b_{k, j})$$

依次往上看，先看叶子节点的父亲 $u$，发现儿子在左子树还是右子树的情况不同，分类讨论：
- 若修改来自 $u$ 的左儿子，不妨假设修改是把 $a_{i, k}$ 置 $0$。
   - 若 $b_{k, j} = 1$，$a_{i, k} \ \text{or} \ b_{k, j}$ 一定为 $1$，不会影响前面的 $\text{and}$。
   - 也就是只有 $b_{k, j} = 0$ 的位置可能会影响 $c_{i, j}$，只要找 $b_k$ 所有 $0$ 的位置，把 $c_{i, j}$ 置 $0$ 即可。
- 若修改来自 $u$ 的右儿子，不妨假设修改是把 $b_{k, j}$ 置 $0$。
   - 若 $a_{i, k} = 1$，$a_{i, k} \ \text{or} \ b_{k, j}$ 一定为 $1$，不会影响前面的 $\text{and}$。
   - 也就是只有 $a_{i, k} = 0$ 的位置会影响 $c_{i, j}$，只要找所有第 $k$ 位是 $0$ 的 $a_{i}$，把 $c_{i, j}$ 置 $0$ 即可。

对于左儿子，我们知道 libstdc++ 为 bitset 提供了方便的 `_Find_first()` 和 `_Find_next(pos)` 成员函数，但这是找 $1$ 的，把 $b_k$ 取反找 $1$ 就等价于找 $0$ 了。

对于右儿子，发现跨了 `bitset`，有点棘手？记录转置矩阵 $A^T_{j, i} = A_{i, j}$，修改是同步的，只有在这一步，要找所有第 $k$ 位是 $0$ 的 $a_i$，只需要找 $a^T_{k}$ 所有的 $0$ 即可，同上取反找 $1$ 即可。

注意，一个 $c_{i, j}$ 被置 $0$ 后就不会再变回 $1$，要保证每次找的 $1$ 一共只被找 $1$ 次，可以使用一些位运算技巧。

:::info[技巧]
因为是实现细节，所以放在了折叠框里。

左右儿子情况类似，不妨只讨论左儿子。

我们要找到所有位置 $j$，使得取反后的 $b_{k, j} = 0$，且这个位置没被我们找过，这意味着 $c_{i, j}=1$。我们的处理把 $b$ 取反得到 $b'$，现在要找 $b_{k, j} = 1$ 且 $c_{i, j} = 1$ 的位置，直接令 $b_k \leftarrow b_k \ \text{and} \ c_i$ 即可。

右儿子就是把 $b_k$ 换成了 $a^T_k$。
:::

发现现在 $c_{i, j}$ 又有若干个置 $0$ 的修改，用 vector 存下这些修改，在父亲处继续修改即可。

每个点我们保证了只有一次 $1$ 变成 $0$，一共有 $\Theta(n4^k)$ 个这样的操作。复杂度可接受。

$\Theta\left(\dfrac{n8^k + q4^k \log n}{w}\right)$。

:::info[代码 5]
```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e4 + 5, M = 1e5 + 5;
const unsigned inf = ~0;

int n, m, k;
int h[N], a[N], b[N];

using Matrix = vector<bitset<32>>;

int ans[M];

struct Query {
    int l, r, x, id;
    int typ;
    Query(int l, int r, int x, int id, int typ) : l(l), r(r), x(x), id(id), typ(typ) {}
    bool operator<(const Query &b) const {return x != b.x ? x < b.x : typ < b.typ;}
};
vector<Query> q;

ostream& operator<<(ostream &os, const Matrix &b) {
    for (int i = 0; i < b.size(); i++) {
        os << b[i];
        if (i != b.size() - 1)
            os << "\n";
    }
    return os;
}

bitset<32> operator*(const bitset<32> &a, const Matrix &b) {
    bitset<32> c(inf);

    for (int k = 0; k < b.size(); k++)
        if (!a[k])
            c &= b[k];

    return c;
}

// Matrix operator*(const Matrix &a, const Matrix &b) {
//     Matrix c(32, bitset<32>(inf));

//     for (int i = 0; i < a.size(); i++)
//         for (int k = 0; k < b.size(); k++)
//             if (!a[i][k])
//                 c[i] &= b[k];

//     return c;
// }

Matrix tr[N << 2], tr2[N << 2];
vector<pii> add[N << 2];

void build(int p, int l, int r) {
    tr[p].assign(32, bitset<32>(inf));
    tr2[p].assign(32, bitset<32>(inf));
    if (l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void modify(int p, int l, int r, int x, int s, int t) {
    if (l == r) {
        tr[p][s][t] = 0;
        tr2[p][t][s] = 0;
        add[p].emplace_back(s, t);
        return;
    }
    int mid = l + r >> 1;

    if (x <= mid) {
        modify(p << 1, l, mid, x, s, t);
        for (auto [s, t]: add[p << 1]) {
            auto rev = ~tr[p << 1 | 1][t];
            rev &= tr[p][s];
            for (int k = rev._Find_first(); k < 32; k = rev._Find_next(k)) {
                tr[p][s][k] = tr2[p][k][s] = 0;
                add[p].emplace_back(s, k);
            }
        }
        add[p << 1].clear();
        add[p << 1].shrink_to_fit();
    } else {
        modify(p << 1 | 1, mid + 1, r, x, s, t);
        for (auto [s, t]: add[p << 1 | 1]) {
            auto rev = ~tr2[p << 1][s];
            rev &= tr2[p][t];
            for (int i = rev._Find_first(); i < 32; i = rev._Find_next(i)) {
                tr[p][i][t] = tr2[p][t][i] = 0;
                add[p].emplace_back(i, t);
            }
        }
        add[p << 1 | 1].clear();
        add[p << 1 | 1].shrink_to_fit();
    }

    // if (corp != tr[p]) {
    //     debug("Let's check out the mergement of matrix %d\n", p);

    //     debug("the modify comes from %s, and s = %d, t = %d\n", lef ? "left" : "right", s, t);

    //     cerr << "left matrix: \n" << tr[p << 1] << "\n";
    //     cerr << "right matrix: \n" << tr[p << 1 | 1] << "\n";

    //     cerr << "correct matrix " << p << ":\n" << corp << "\n";
    //     cerr << "present matrix " << p << ": \n" << tr[p] << "\n\n";
    // }
}

void query(int p, int l, int r, int L, int R, bitset<32> &f) {
    if (L > R || r < L || l > R) return;
    if (L <= l && r <= R) {f = f * tr[p]; return;}
    int mid = l + r >> 1;
    query(p << 1, l, mid, L, R, f);
    query(p << 1 | 1, mid + 1, r, L, R, f);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc, tt;
    cin >> tc >> tt;
    while (tt--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) cin >> h[i];
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        q.clear();

        for (int i = 1, l, r, x; i <= m; i++) {
            cin >> l >> r >> x;
            q.emplace_back(l, r, x, i, 1);
        }

        for (int i = 1; i < n; i++)
            for (int j = 0; j < (1 << k); j++) {
                q.emplace_back(j, j << 1 & 31, h[i + 1], i, 0);
                q.emplace_back(j, (j << 1 | 1) & 31, h[i + 1] + a[i + 1], i, 0);
                for (int s = j; s; s = (s - 1) & j) {
                    int d = 0;
                    bool valid = true;
                    for (int t = 0; t < k; t++)
                        if (s >> t & 1) {
                            if (i - t < 1) {
                                valid = false;
                                break;
                            }
                            d += b[i - t];
                        }
                    if (!valid) continue;
                    q.emplace_back(j, (j ^ s) << 1 & 31, h[i + 1] - d, i, 0);
                    q.emplace_back(j, ((j ^ s) << 1 | 1) & 31, h[i + 1] + a[i + 1] - d, i, 0);
                }
            }

        build(1, 1, n - 1);

        sort(q.begin(), q.end());

        for (auto [l, r, x, id, typ]: q) {
            if (typ) {
                // Matrix f(32, bitset<32>(inf));
                // f[0][0] = h[l] > x, f[0][1] = h[l] + a[l] > x;
                bitset<32> f(inf);
                f[0] = h[l] > x, f[1] = h[l] + a[l] > x;
                query(1, 1, n - 1, l, r - 1, f);
                ans[id] = !f[0];
            } else {
                modify(1, 1, n - 1, id, l, r);
            }
        }

        for (int i = 1; i <= m; i++)
            cout << (ans[i] ? "Yes\n" : "No\n");
    }
    return 0;
}
```
:::

代码 5 期望得分 $100$，实际得分 $5$。

### 卡常

:::warning{open}
本题卡常严重。
:::

这部分更多算是我的一些碎碎念，感觉偏离了题解本身教授题目做法的宗旨，所以我放在了折叠框里。

如果你觉得阅读完上面的题解后，认为自己能够写出复杂度正确且常数较小的优秀做法，你可以不用打开折叠框。但如果你认为自己可能会被卡常，可以阅读一下，了解一些注意事项。

:::info[卡常]

从代码 3 开始就埋下伏笔了。

代码 5 的复杂度正确，但因为常数巨大只能获得 $5$ 分。仔细分析不难发现，代码 5 的常数巨大主要由两方面导致：

#### 实现本身的不够优。

##### 排序
排序是很难被注意到的一点。

我们将所有的询问和修改放在了一起，可以发现，极端情况下询问和修改的总数是 $Q = q + 2n3^k = 9.82 \times 10^6$，直接排序乘上 $20$ 多的 $\log$，不优。
  
降低排序的复杂度就考虑计数排序，$x_i$ 的值域上限是 $h + a \le 10^6 + 10^6 = 2\times 10^6$，下限是 $0$ 减去 $k$ 个最大的 $b$ 就是 $-5\times 10^6$。值域大小 $7 \times 10^6$，可以接受。

计数排序的时间复杂度是 $\Theta(Q)$，$Q$ 是询问和修改的总数。

##### 构造转移矩阵

如果你看了我的代码 5 的实现，会发现那是我直接在 dp 的基础上改的。

```cpp
q.emplace_back(j, (j ^ s) << 1 & 31, h[i + 1] - d, i, 0);
q.emplace_back(j, ((j ^ s) << 1 | 1) & 31, h[i + 1] + a[i + 1] - d, i, 0);
```

我直接把所有的修改拿出来排序。但修改有很多是打在了同一个位置的，因为一个 $j$ 对应了最多 $32$ 个状态，这里跟 dp 的时候不一样，dp 的时候没有什么 $\Theta\left(\dfrac{q4^k\log n}{w}\right)$ 的修改，只有 $\Theta(1)$ 的取 $\min$。这是非常严重的失误，显然只有最小的 $x$ 有用。$1$ 改成 $0$ 后不会再修改。这可以显著减少修改。

上面这两个是导致常数巨大的主要原因。但还是在一些数据上跑得慢，剩下的就是常规的卡常技巧。

#### 常规卡常

我做了包括但不限于下面的常规卡常：
- 快读快写；
- 少用 vector；
- 修改的时候，记录一下序列的第 $i$ 个对应线段树哪个节点，直接从底往上修改，就不用再递归去找叶子，没有修改直接退出；
- 全局 `bitset`。
:::

:::success[代码 6]
```
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

namespace fastio{ // from MiniLong
    #ifdef ONLINE_JUDGE
    char ibuf[1 << 20],*p1 = ibuf, *p2 = ibuf;
    #define get() p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++
    #else
    #define get() getchar()
    #endif
    template<typename T> inline void read(T &t){
        T x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T, typename ... Args> void write(T t, Args... args){
        write(t), putchar(' '), write(args...);
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
    template<typename T> void writes(T t){
        write(t), putchar(' ');
    }
    #undef get
};
using namespace fastio;

const int N = 2e4 + 5, M = 1e5 + 5, Q = 5e6;
const unsigned inf = ~0;

int n, m, k;
int h[N], a[N], b[N];

int ans[M];

struct Query {
    int l, r, x, id;
    int typ;
    Query() {}
    Query(int l, int r, int x, int id, int typ) : l(l), r(r), x(x), id(id), typ(typ) {}
    bool operator<(const Query &b) const {return x != b.x ? x < b.x : typ < b.typ;}
} q[M + N * 486], qq[M + N * 486];

bitset<32> tr[N << 2][32], tr2[N << 2][32];
vector<pii> add[N << 2];
int reff[N];

void build(int p, int l, int r) {
    for (int i = 0; i < 32; i++) {
        tr[p][i].set();
        tr2[p][i].set();
    }
    if (l == r) return reff[l] = p, void();
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void modify(int x, int s, int t) {
    int p = reff[x];
    if (!tr[p][s][t]) return;

    tr[p][s][t] = tr2[p][t][s] = 0;
    add[p].emplace_back(s, t);
    p >>= 1;

    while (p) {
        if (add[p << 1].empty() && add[p << 1 | 1].empty()) break;
        for (auto [s, t]: add[p << 1]) {
            auto rev = ~tr[p << 1 | 1][t] & tr[p][s];
            for (int i = rev._Find_first(); i < (1 << k); i = rev._Find_next(i)) {
                tr[p][s][i] = tr2[p][i][s] = 0;
                add[p].emplace_back(s, i);
            }
        }
        add[p << 1].clear();

        for (auto [s, t]: add[p << 1 | 1]) {
            auto rev = ~tr2[p << 1][s] & tr2[p][t];
            for (int i = rev._Find_first(); i < (1 << k); i = rev._Find_next(i)) {
                tr[p][i][t] = tr2[p][t][i] = 0;
                add[p].emplace_back(i, t);
            }
        }
        add[p << 1 | 1].clear();

        p >>= 1;
    }
}
bitset<32> f, c;
void query(int p, int l, int r, int L, int R) {
    if (L > R || r < L || l > R) return;
    if (L <= l && r <= R) {
        c.set();
        for (int i = 0; i < (1 << k); i++)
            if (!f[i])
                c &= tr[p][i];
        f = c;
        return;
    }
    int mid = l + r >> 1;
    query(p << 1, l, mid, L, R);
    query(p << 1 | 1, mid + 1, r, L, R);
}

int cnt[7000005];

int g[32];

int main() {
    int tc, tt;
    read(tc, tt);
    int maxx = 0;
    while (tt--) {
        read(n, m, k);
        for (int i = 1; i <= n; i++) read(h[i]);
        for (int i = 1; i <= n; i++) read(a[i]);
        for (int i = 1; i <= n; i++) read(b[i]);

        for (int i = 1; i <= maxx; i++) cnt[i] = 0;

        int lenq = 0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < (1 << k); j++) {
                for (int t = 0; t < 32; t++)
                    g[t] = 2e9;
                for (int s = j; ; s = (s - 1) & j) {
                    int d = 0;
                    bool valid = true;
                    for (int t = 0; t < k; t++)
                        if (s >> t & 1) {
                            if (i - t < 1) {
                                valid = false;
                                break;
                            }
                            d += b[i - t];
                        }
                    if (!valid) continue;
                    g[(j ^ s) << 1 & 31] = min(g[(j ^ s) << 1 & 31], h[i + 1] - d);
                    g[((j ^ s) << 1 | 1) & 31] = min(g[((j ^ s) << 1 | 1) & 31], h[i + 1] + a[i + 1] - d);
                    // q[++lenq] = {j, (j ^ s) << 1 & 31, h[i + 1] - d, i, 0}, maxx = max(maxx, h[i + 1] - d + Q);
                    // debug("[%d][%d] = %d\n", j, (j ^ s) << 1 & 31, h[i + 1] - d);
                    // q[++lenq] = {j, ((j ^ s) << 1 | 1) & 31, h[i + 1] + a[i + 1] - d, i, 0}, maxx = max(maxx, h[i + 1] + a[i + 1] - d + Q);
                    // debug("[%d][%d] = %d\n", j, ((j ^ s) << 1 | 1) & 31, h[i + 1] + a[i + 1] - d);
                    if (!s) break;
                }
                for (int t = 0; t < (1 << k); t++) {
                    if (g[t] == 2e9) continue;
                    q[++lenq] = {j, t, g[t], i, 0};
                    maxx = max(maxx, g[t] + Q);
                }
            }

        for (int i = 1, l, r, x; i <= m; i++) {
            read(l, r, x);
            maxx = max(maxx, x + Q);
            q[++lenq] = {l, r, x, i, 1};
        }

        build(1, 1, n - 1);

        for (int i = 1; i <= lenq; i++)
            cnt[q[i].x + Q]++;

        for (int i = 1; i <= maxx; i++)
            cnt[i] += cnt[i - 1];

        for (int i = lenq; i >= 1; i--)
            qq[cnt[q[i].x + Q]--] = q[i];

        for (int i = 1; i <= lenq; i++) {
            int l = qq[i].l, r = qq[i].r, x = qq[i].x, id = qq[i].id, typ = qq[i].typ;
            if (typ) {
                // Matrix f(32, bitset<32>(inf));
                // f[0][0] = h[l] > x, f[0][1] = h[l] + a[l] > x;
                f.set();
                f[0] = h[l] > x, f[1] = h[l] + a[l] > x;
                query(1, 1, n - 1, l, r - 1);
                ans[id] = !f[0];
            } else {
                modify(id, l, r);
            }
        }

        for (int i = 1; i <= m; i++)
            puts(ans[i] ? "Yes" : "No");
    }
    return 0;
}
```
:::

代码 6 期望得分 $100$，实际得分 $100$。

代码 6 和正常编写的代码 5 相比重构太多，可读性比较差。

### 后记 & 闲话

:::info[后记 & 闲话]
#### 为什么我要写这么详细的题解？

我个人是理解能力比较一般的人，每次看到模拟赛后贴出来的两三行题解，都得仔细研读，乃至去网上搜索更加详细的题解。这让我的改题十分痛苦，因为不能准确捕捉到写题解的人的意思。

我没有权利要求其他选手写出详细的题解，毕竟题解是选手花自己的时间分享自己的心得，而不是老师教导学生。但我想写详细的题解，真正能帮别人的学会这道题的题解，而不仅是自己的做题心得，而且详细的题解也能让我更好地梳理自己的思路，对题目有更深的认识。

#### 居然每个部分都有代码？

这几个部分大致和出题人题解一样，我就是按着这几个部分一个部分一份代码写过来的。这也是正常、合理、科学的思考链条，按部就班有利于更好把握题目。

#### 吐槽

这题花了我很多时间，毕竟每个部分我都去实现。但卡常花了我尤其久，有一天半左右了。总共提交了九十多发。卡常是真的恶心。题很好，就是卡常太恶心。

#### 致谢

本题的出题人 @[MiniLong](https://www.luogu.com.cn/user/573341) 给予了我很多帮助，是一位实力强大且思路清晰的选手。非常感谢。

#### 闲话

洛谷更新的这个折叠框我非常喜欢。

这篇题解花了我很多时间，虽然这题是冷门题，看到的人也不多，但希望我的题解帮到了你。

这是我写过最久最长最详细的题解，27k+ 字。
:::

---

## 作者：toolazy (赞：1)

### 题意

本文段截取自个人小记。

> [**P12151 【MX-X11-T5】「蓬莱人形 Round 1」俄罗斯方块**](https://www.luogu.com.cn/problem/P12151)
>
> 给定一个长度为 $n$ 的序列，其中每个元素由 $(h_i,a_i,b_i)$  三元组组成，再给出一个整数 $k$。
>
> 你可以进行若干次操作，每次操作选择一个下标 $i$，然后让 $h_i$ 增加 $a_i$，并选定一个 $j\in[i+1,i+k]$，让 $h_j$ 减少 $b_i$，每个下标只能操作一次。
>
> 给出若干次询问 $(l_i,r_i,x_i)$，回答能否只操作 $[l_i,r_i]$ 间的下标，使得区间内所有 $a_i\le x$，回答 `Yes` 或 `No`。
>
> 极限数据：$3$ 次多测，$1\le k\le 5$，值域 $10^6$，$n\le2\times10^4,q\le10^5$，时限 $4\ \rm s$。

本文分三段，详细介绍此题思考历程，主打清新与自然顺畅。

### Phase A. 动态规划部分

> 操作本身的意义就是——让稍小的 $i$ 吃亏，受到 $+a_i$ 变得稍劣，从而赚取优化 $j\in[i+1,i+k]$ 的机会，使之 $-b_i$ 变得更优，达到一个『劫富济贫』的效果（谔谔你语文怎么能这么差...
>
> 由于 $k$ 很小，所以考虑状态压缩。**先来做全局询问**，我们设状态 $f(i,S)$ 表示最小化前缀 $[1,i]$ 内的 $\max h_j$，用 $S$ 来记录 $[i-k+1,i]$ 各元素的操作情况。每个元素的操作情况具体分三种：
>
> 1. 其没有被操作过（指 **没有** 给自己加入 $+a_j$ 的增量，更不可能分配 $-b_j$ 的增量给别人）。
> 2. 其已经确定被操作过，加入了 $+a_j$ 的增量，并且 $-b_j$ 的增量也 **已经分配** 到 $[1,i]$ 中的某个位置。
> 3. 其已经确定被操作过，加入了 $+a_j$ 的增量，但 $-b_j$ 的增量还 **没有确定（要）分配** 到 $[i+1,n]$ 中的哪个位置。
>
> 我们把 1, 2. 两情况统称为 **确定态**，3. 称为 **未定态**，因为前者不对 $[i+1,n]$ 的下标产生后续的影响。
>
> 将未定态的 $i$ 记录到 $S$ 中，确定态不加入集合，进行动态规划。每次枚举 $S$ 的子集 $T$，令之贡献到 $h_{i+1}$，进行后续转移：
> $$
> \begin{array}{}
> \max\Bigg\{f(i,S),h_{i+1}-\displaystyle\sum_{j\in T}b_j\Bigg\}&\rarr&{\rm chk}\displaystyle\min_{T\subset S}\Big\{f(i+1,S/T)\Big\}\\
> \max\Bigg\{f(i,S),h_{i+1}-\displaystyle\sum_{j\in T}b_j+a_{i+1}\Bigg\}&\rarr&{\rm chk}\displaystyle\min_{T\subset S}\Big\{f(i+1,S/T\cup\{i+1\})\Big\}
> \end{array}
> $$
> 为了符合题面，我们要求，如果 $S$ 里面包含了 $i-k+1$，那么 $T$ 必须也选上 $i-k+1$，否则不进行转移。子集枚举有 $O(3^k)$，单询问暴力，则时间复杂度可以做到 $O(nq3^k)$，可以通过 $15\rm\ pts$ 的小数据和性质 A 的 $10\rm\ pts$。

### Phase B. 线段树套矩乘

> 考虑 **上升到区间询问**。首先要发现 $\min$ 对 $\max$ 满足分配律：
> $$
> \max\Big\{\min\{x,y\},z\Big\}=\min\Big\{\max\{x,z\},\max\{y,z\}\Big\}\\
> $$
> 好吧，二元运算符前置，波兰表达式确实看着很不自然，但我很确定我没有写错（？）。也许我应该这么写：
> $$
> (x\min y)\max z=(x\max z)\min(y\max z)\\
> $$
> 于是考虑矩阵乘法。我们定义答案（行）向量恰有 $2^k$ 维，对应每一个 $S$，初始化全部为 $+\infty$（单位矩阵）。
>
> 为了构造转移矩阵，我们反写转移方程：
> $$
> f(i,S)=\min_{S\cap T=\varnothing}\begin{Bmatrix}\begin{array}{l}\max\Bigg\{f(i-1,S\cup T),h_{i}-\displaystyle\sum_{j\in T}b_j\Bigg\}&(i\notin S)\\\max\Bigg\{f(i-1,S/\{i\}\cup T),h_{i}+a_{i}-\displaystyle\sum_{j\in T}b_j\Bigg\}&(i\in S)\end{array}\end{Bmatrix}
> $$
> 我们直接枚举所有集合 $S,T$，判断是否满足 $S\cap T\neq\varnothing$，然后再要求 $i-k\notin S$，若满足，则：
> $$
> M_{S/\{i\}\cup T,S}=\begin{cases}
> h_i-\displaystyle\sum_{j\in T}b_j&(i\notin S)\\
> h_i+a_i-\displaystyle\sum_{j\in T}b_j&(i\in S)
> \end{cases}
> $$
> 其它不满足情况的下标，直接 $M_{i,j}=+\infty$，最后线段树处理。
>
> > 或者改成 `int/bitset` 的形式，左边为小端，位权小，右边为大端，位权大，枚举所有 $s,t\in[0,2^k)$：
> >
> > $$
> > M_{(2s+t)\&(2^k-1),s}=\begin{cases}
> > +\infty&\big((2s)\&(t)\neq 0\big)\\
> > h_i-\displaystyle\sum_{2^j\in t} b_{i-k+j}&(2^{k-1}\notin s)\\
> > h_i+a_i-\displaystyle\sum_{2^j\in t}b_{i-k+j}&(2^{k-1}\in S)
> > \end{cases}
> > $$
> > 左侧越界时则 $a_j=+\infty,b_j=-\infty$，参考下面一模一样的代码：
> >
> > ```c++
> > memset(mt, 0x3f, sizeof mt); // int mt[32][32];
> > for (int s = 0; s <= S; s ++) for (int t = 0; t <= S; t ++) {
> >     if ((s << 1) & t) { continue; } int v = h[nl]; // 计算这个位置的值，丢到队列里面根据值排序
> >     if (s & (1 << (k - 1))) v += a[nl];
> >     for (int tt = t; tt; tt &= tt - 1) {
> >         int j = log2(lowbit(tt)); int pos = nl - k + j;
> >         if (pos <= 0) { v = 0x3f3f3f3f; break; } v -= b[pos];
> >     } mt[s][t] = v;
> > }
> > ```
>
> 发现 `pushup` 要矩阵乘法，所以预处理其实是 $O(n8^k)$ 的。
>
> 询问直接用向量乘矩阵 $O(4^k)$，不要 `merge` 变成矩阵乘矩阵 $O(8^k)$ 了。
>
> 总时间复杂度可以做到 $O(n8^k+q4^k\lg n)$，期望 $50\sim 70\rm\ pts$，卡常也是分数的一部分。

### Phase C. 询问离线 & `bitset` 优化

> 部分分 $x_i$ 全部相同启发我们使用 `bitset` 优化。对于矩阵元素，若其 $>x_i$ 则直接改写成 $1$ 即可，$\le x_i$ 的则改写为 $0$，意义显然正确，这样矩阵乘法就可以多上一个 `bitset` 了，取 $\min$ 等价于 `bitset.all()`，取 $\max$ 等价于求或。
>
> 倘若我们对 $x_i$ 扫描一下，从小到大依次处理询问，每一次把若干（叶子节点上的）矩阵的若干元素从 $1$ 改成 $0$，并由此对整棵线段树进行更新，不断 `pushup`。
>
> 我们将这些点取出来，根据它们从 $1$ 变 $0$ 的时刻进行排序，然后继续扫描，适时加入，分析一波时间复杂度。
>
> 初始扫描权值极小，矩阵里面全都是 $1$（$+\infty$），每次从 $1$ 改 $0$，向上继续 `pushup` 也只能从 $1$ 变 $0$。
>
> 欸，这矩阵大小 $O(4^k)$ 的，线段树节点又只有 $O(n)$ 个，所以可以翻转的总比特数其实只有 $O(n4^k)$。
>
> 我们考虑让每一次翻转至多贡献 $O\Big(\dfrac{2^k}w\Big)$ 的时间复杂度，然后发现这很唐... 假如我们翻转了左儿子的 $(i,j)$，那么右儿子能与之配对的下标肯定都是 $(j,0\sim 2^k-1)$，这里用 `bitset` 求一个 $\rm NOT$（`~`）可以了；
>
> 然后它贡献出来的下标也对应父亲的 $(i,0\sim 2^k-1)$，为了保证时间复杂度，我们不能让本就为 $0$ 的位置重新贡献时间复杂度，所以我们再把刚才就求到的 `bitset` 再 $\rm AND$（`&`）上父亲，最后一路数 `lowbit` 抠出来就好了。
>
> 右儿子也类似，btw，这个矩阵不仅要记录每一行的 `bitset`，还要记录每一列的 `bitset`。时间复杂度 $O\Big(\dfrac{n 8^k+q4^k\lg n}{w}\Big)$，不卡常，时限宽松（至少笔者没有卡常，但跑得也 [不算太优](https://www.luogu.com.cn/record/230976824) /xk），可以通过所有数据。

### Phase Z. 实现参考

受限于编译器确定的静态模板，`bitset` （也许）需要手动的更灵活更亲切的实现，反正我是手写了。

你会骂我说我的代码写的很不工程，无所谓，OI $\neq$ 开发。展示代码参考实现细节，略压行勿喷（（（：

```c++
#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

//#define NDEBUG
#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define ave(l, r) (((l) + (r)) >> 1)
#define fa(x) ((x) >> 1)

const int MAXN = 2e4 + 5;
const int MAXQ = 1e5 + 5;
const int MAXK = 5, MAXS = 32;

int n, q, k, T, S; unsigned U;

struct bitset { // 一般般的实现，里面相当一部分方法其实根本没有用（
	
	unsigned int_v; // 能用 ui 就别用 ll, 2 ** 5 == 32 正好够用
	
	explicit bitset(unsigned v = 0) : int_v(v & U) {}
	explicit bitset(bool flg) : int_v(flg * U) {}
	
	inline bool operator [] (int x) const { return int_v & (1u << x); }
	inline bitset operator & (bitset k) const { return bitset(int_v & k.int_v); }
	inline bitset operator &= (bitset k) { return bitset(int_v &= k.int_v); }
	inline bitset operator | (bitset k) const { return bitset(int_v | k.int_v); }
	inline bitset operator |= (bitset k) { return bitset(int_v |= k.int_v); }
	inline bitset operator ^ (bitset k) const { return bitset(int_v ^ k.int_v); }
	inline bitset operator ^= (bitset k) { return bitset(int_v ^= k.int_v); }
	inline bitset operator << (int x) const { return bitset((int_v << x) & U); }
	inline bitset operator <<= (int x) { return bitset(int_v = ((int_v << x) & U)); }
	inline bitset operator >> (int x) const { return bitset(int_v >> x); }
	inline bitset operator >>= (int x) { return bitset(int_v >>= x); }
	
	inline bitset operator ~ () const { return bitset(~int_v); }
	inline bitset operator ++ () { return bitset(++ int_v); }
	inline bitset operator ++ (int) { return bitset(int_v ++); }
	
	inline void reset() { int_v = 0; }
	inline void set() { int_v = U; }
	inline void reset(int k) { int_v &= U ^ (1u << k); }
	inline void set(int k) { int_v |= (1u << k); }
	inline void flip() { int_v ^= U; }
	inline void flip(int k) { int_v ^= (1u << k); }
	inline void write(bool v) { int_v = v * U; }
	inline void write(int k, bool v) { if (v) set(k); else reset(k); }
	
	inline bool any() const { return int_v; }
	inline operator bool () const { return int_v; }
	inline operator unsigned () const { return int_v; }
	inline bool none() const { return int_v == 0; }
	inline bool notall() const { return int_v < U; }
	inline bool all() const { return int_v == U; }
	
	inline int back() const { assert(any()); return int_v & -int_v; } // lowbit
	inline void pop_back() { assert(any()); int_v &= int_v - 1; } // 去掉一个 lowbit
	
//	inline void print() const { for (int i = 0; i <= S; i ++) cout << (*this)[i]; }
	
};

int h[MAXN], a[MAXN], b[MAXN], lg[65537]; bool ans[MAXQ];
struct QUERYS { int l, r, x, i; } qry[MAXQ];
struct FLIPS { int nd, x, y, v; }; vector<FLIPS> wait;

inline int lg2(unsigned x) { return x <= 65536 ? lg[x] : 16 + lg[x >> 16]; } // 手写 lg2，实测你直接 __builtin_log2 或者 __lg 也没啥差距

struct matrix {
	
	bitset r[MAXS], c[MAXS];
	
	inline void set() { for (int i = 0; i <= S; i ++) r[i].set(), c[i].set(); }
	inline void set(int x, int y) { r[x].set(y); c[y].set(x); }
	inline void reset() { for (int i = 0; i <= S; i ++) r[i].reset(), c[i].reset(); }
	inline void reset(int x, int y) { r[x].reset(y); c[y].reset(x); }
	inline void flip() { for (int i = 0; i <= S; i ++) r[i].flip(), c[i].flip(); }
	inline void flip(int x, int y) { r[x].flip(y); c[y].flip(x); }
	inline void write(bool v) { if (v) set(); else reset(); }
	inline void write(int x, int y, int v) { r[x].write(y, v); c[y].write(x, v); }
	
//	inline void print() const { for (int i = 0; i <= S; i ++) r[i].print(), cout << endl; }
	
} sgt[MAXN << 2];

//void printSGT(int nl = 1, int nr = n, int x = 1) {
//	cout << "[" << nl << ", " << nr << "]:\n"; sgt[x].print();
//	if (nl == nr) { return; } int mid = ave(nl, nr);
//	printSGT(nl, mid, ls(x)); printSGT(mid + 1, nr, rs(x));
//}

void buildSGT(int nl = 1, int nr = n, int x = 1) {
	sgt[x].set(); if (nl == nr) {
		for (int s = 0; s <= S; s ++)
			for (int t = 0; t <= S; t ++) {
				if ((s << 1) & t) { continue; } int v = h[nl]; // 计算这个位置的值，丢到队列里面根据值排序
				if (s & (1 << (k - 1))) v += a[nl];
				for (int tt = t; tt; tt &= tt - 1) {
					int j = lg[tt & -tt]; int pos = nl - k + j;
					if (pos <= 0) { v = 0x3f3f3f3f; break; } v -= b[pos];
				} if (v >= 0x3f3f3f3f) continue;
				wait.push_back({x, ((s << 1) | t) & S, s, v});
			} return;
	} int mid = ave(nl, nr);
	buildSGT(nl, mid, ls(x));
	buildSGT(mid + 1, nr, rs(x));
}

bitset gloRESULT, __tmp;

void querySGT(int l, int r, int nl = 1, int nr = n, int x = 1) {
	if (nr < l || r < nl) return;
	if (l <= nl && nr <= r) {
		for (int i = 0; i <= S; i ++)
			__tmp.write(i, (gloRESULT | sgt[x].c[i]).all()); // 用向量乘，不要用矩阵直接 merge 上来
		gloRESULT = __tmp; return;
	} int mid = ave(nl, nr);
	querySGT(l, r, nl, mid, ls(x));
	querySGT(l, r, mid + 1, nr, rs(x));
}

void flipSGT(int r, int c, int x) { // 这里实现需要注意，稍微写拉了就 gg 了
	sgt[x].flip(r, c); if (x == 1) return;
	if (~x & 1) { bitset res = sgt[fa(x)].r[r] & ~sgt[x + 1].r[c]; // 只找有意义的位置，用 lowbit 一位一位抠出来
		for (; res.any(); res.pop_back()) flipSGT(r, lg2(res.back()), fa(x));
	} else { bitset res = sgt[fa(x)].c[c] & ~sgt[x - 1].c[r];
		for (; res.any(); res.pop_back()) flipSGT(lg2(res.back()), c, fa(x));
	}
//	sgt[x].flip(r, c);
//	while (x = fa(x)) {
//		for (int i = 0; i <= S; i ++)
//			for (int j = 0; j <= S; j ++)
//				sgt[x].write(i, j, (sgt[ls(x)].r[i] | sgt[rs(x)].c[j]).all());
//	}
}

int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	for (int i = 2; i <= 65536; i ++) lg[i] = 1 + lg[i >> 1];
	for (cin >> T >> T; T --; ) {
		cin >> n >> q >> k; S = (1 << k) - 1;
		U = (unsigned)((1ll << (1 << k)) - 1);
		for (int i = 1; i <= n; i ++) cin >> h[i];
		for (int i = 1; i <= n; i ++) cin >> a[i];
		for (int i = 1; i <= n; i ++) cin >> b[i];
		wait.clear(); buildSGT(); __tmp.reset();
		for (int i = 1; i <= q; i ++) {
			int l, r, x; cin >> l >> r >> x; qry[i] = {l, r, x, i};
		} sort(qry + 1, qry + 1 + q, [] (QUERYS a, QUERYS b) { return a.x < b.x; }); // 听说有人被卡常，实在不行就把 sort 换计排吧
		sort(wait.begin(), wait.end(), [] (FLIPS a, FLIPS b) { return a.v < b.v; });
		auto ptr = wait.begin(); for (int i = 1; i <= q; i ++) {
			QUERYS qq = qry[i]; while (ptr != wait.end() && ptr -> v <= qq.x) {
				flipSGT(ptr -> x, ptr -> y, ptr -> nd); ptr ++;
			} gloRESULT.set(); gloRESULT.reset(0);
			querySGT(qq.l, qq.r); ans[qq.i] = gloRESULT[0];
		} for (int i = 1; i <= q; i ++) cout << (ans[i] ? "No" : "Yes") << '\n';
	} return 0;
}
```

由于 $\ne+\infty$ 的点值实际上和子集枚举相关，所以 `wait.size()` 是 $O(n3^k)$ 的，实际复杂度上界也许会更紧。

[这里](https://www.luogu.com.cn/record/231000345) 还有一份 deekpsee 帮我卡常的代码（主要就是把 `struct bitset` 直接换成 `unsigned int` 和把 `sort(wait)` 换成了手写的计数排序），确实快了不少。

### 闲言

非常感谢 MiniLong 学长愿意分享这么一道好题，虽然我和 TA 不熟（这就是你不 at 他的原因？），而且这题我订正了将近三周（（（（谔谔谔谔谔 我对不住学长更对不住林总啊啊啊

非常感谢 murder_drones 学长愿意和我一起探讨这道题目，TA 以光速秒掉了这题的 Phase A & B 并和我深入探讨 Phase C 的实现。没有 TA 我可能这辈子也写不出来 P12151，因为我看不懂别人的题解（（（

哎呦我本来有一大堆话想要说的，突然哽喉咙不好意思说了，哈哈人怎么能这样好笑（我想要说的前人们都 [CUT]

这题从 7.25 见面到 8.14 晚终于战胜，真的是好题，你们都过来给我做（其实是因为中途摆烂、写一半不会了不写了、终于写完结果挂了不会调于是咕咕，遂至今

哎呦卧槽我好颓废啊，哎呦卧槽 AI 太好用了你们知道吗

---

## 作者：godmoo (赞：1)

[Link](https://www.luogu.com.cn/problem/P12151) & [Cnblogs](https://www.cnblogs.com/godmoo/p/19005878).

模拟赛题。感谢 @[MiniLong](https://www.luogu.com.cn/user/573341) 学长和 @[carefree_Zhuang](https://www.luogu.com.cn/user/432566)。

$k\le 5$，会影响到 $h_i$ 的仅有它前 $k$ 个位置，考虑状压。设 $dp_{i,S}$ 表示对第 $i$ 个位置，前 $k$ 个位置中还未选定 $j$ 的位置集合为 $S$ 时，$\max h$ 的最小值，转移时枚举 $S$ 的子集 $T$ 贡献到 $dp_{i+1,f(S,T,op)}$（$op$ 表示是否激活 $i$）。对于每个询问的左端点分别 dp 即可。

给出方程：

$$dp_{i+1,f(S,T,op)}=\min\{\max(dp_{i,S}, g(h_i, T,op))\}$$

发现这很矩乘。使用矩阵刻画转移，由于需要区间询问，把矩阵搬到线段树上做。直接合并转移矩阵复杂度太高，考虑用初始向量乘矩阵，单次询问可以做到 $\mathcal{O}(4^k\log n)$，总复杂度 $\mathcal{O}(n8^k+q4^k\log n)$。

考虑特殊性质 B：所有 $x$ 相等。此时我们只关心 dp 值与 $x$ 的大小关系，又 dp 值的合并只有 $\min,\max$ 运算，于是将原矩阵换成 0/1 矩阵，表示矩阵上每个值是否 $\le x$，使用 `std::bitset` 存储，并用位运算刻画 $\min,\max$，复杂度 $\mathcal{O}(\frac{n8^k+q4^k\log n}{\omega})$。

受此启发，我们将询问按 $x$ 升序排序。当 $x=-\infin$ 时矩阵全为 $0$，我们仅需找出每个位置从 $0$ 变成 $1$ 的时间点，并在这个时间点的询问前加入线段树。

对于叶子节点，直接 dp 算出；对于非叶子节点，直接矩乘 `pushup` 复杂度爆炸，我们单独考察变化的位置对其父亲 $u$ 的贡献：

不妨钦定变化的位置在 $u$ 的左儿子 $l$，新增加的转移为 $f\rightarrow g$，则对于 $u$，新增加的转移必然是先在左儿子中 $f\rightarrow g$ ，再通过右儿子 $r$ 的某个转移 $g\rightarrow h$，形成一个新的转移 $f\rightarrow h$。右儿子情况类似。

维护出新增加的转移并在矩阵上修改，一路向上更新即可。时间复杂度？叶子节点的 dp 是 $\mathcal{O}(n3^k)$ 的；全树仅 $\mathcal{O}(n4^k)$ 个不同转移，对于一个转移，处理出它所在节点父亲新增的转移的复杂度为 $\mathcal{O}(\frac{2^k}{\omega})$；询问复杂度不变。总时间复杂度为 $\mathcal{O}(n3^k+\frac{n8^k+q4^k\log n}{\omega})$。


::::success[Code]
```cpp
// godmoo's code
// P12151
#include <bits/stdc++.h>

using namespace std;

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define mkp make_pair
#define lbd lower_bound
#define ubd upper_bound
#define IMX INT_MAX
#define LMX LLONG_MAX
#define mathmod(a) (((a) % MOD + MOD) % MOD)
#define mem(a, b) memset(a, b, sizeof(a))
#define cpy(a, b) memcpy(a, b, sizeof(b))
#define ckmx(a, b) (a = max(a, b))
#define ckmn(a, b) (a = min(a, b))
#define all(a) a.begin(), a.end()

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

const int N = 2e4 + 5;
const int M = 1e5 + 5;
const int V = 1e6 + 5, INF = 1e6;
const int ST = (1 << 5);

int c, T, n, m, k, st, h[N], a[N], b[N], ans[M]; ll sb[N][ST];

struct Task{
    int pos, f, g;  // (pos - 1, f) -> (pos, g)
    Task() = default;
    Task(int pos, int f, int g): pos(pos), f(f), g(g){}
};
vector<Task> X[V];

struct Query{
    int l, r, id;
    Query() = default;
    Query(int l, int r, int id): l(l), r(r), id(id){}
};
vector<Query> Q[V];

typedef bitset<ST> Vector;
Vector operator -(const Vector& U, const Vector& V){ return (U | V) ^ V; } // 差集

struct Matrix{
    Vector mat[ST];
    Vector row(int i) const{ return mat[i]; }
    auto get(int i, int j){ return mat[i][j]; }
    void clear(){ for(int i = 0; i < st; i++) mat[i].reset(); }
};
Vector operator*(const Vector& V, const Matrix& M){
    Vector R;
    for(int i = 0; i < st; i++) if(V[i]) R |= M.row(i);
    return R;
}

namespace SegTree{
    int lf[N];
    Matrix pre[N << 2], nxt[N << 2];
    vector<pii> task[N << 2];

    void build(int u = 1, int l = 1, int r = n){
        if(l == r) return lf[l] = u, void();
        int m = l + r >> 1;
        build(u << 1, l, m), build(u << 1 | 1, m + 1, r);
    }

    Vector res;
    void _query(int u, int l, int r, int ql, int qr){
        if(ql <= l && r <= qr) return res = res * nxt[u], void();
        int m = l + r >> 1;
        if(ql <= m) _query(u << 1, l, m, ql, qr);
        if(qr > m) _query(u << 1 | 1, m + 1, r, ql, qr);
    }
    bool query(int l, int r){
        return res.reset(), res.set(0), _query(1, 1, n, l, r), res[0];
    }

    Vector tmp;
    void _upd(int u){
        for(auto [f, g] : task[u << 1]){
            tmp = nxt[u << 1 | 1].row(g) - nxt[u].row(f);
            for(int i = tmp._Find_first(); i < st; i = tmp._Find_next(i))
                nxt[u].get(f, i) = pre[u].get(i, f) = 1, task[u].eb(f, i);
        }
        task[u << 1].resize(0);
        for(auto [f, g] : task[u << 1 | 1]){
            tmp = pre[u << 1].row(f) - pre[u].row(g);
            for(int i = tmp._Find_first(); i < st; i = tmp._Find_next(i))
                pre[u].get(g, i) = nxt[u].get(i, g) = 1, task[u].eb(i, g);
        }
        task[u << 1 | 1].resize(0);
    }
    void upd(int u, int f, int g){
        if(nxt[u = lf[u]].get(f, g)) return;
        nxt[u].get(f, g) = pre[u].get(g, f) = 1, task[u].eb(f, g);
        u >>= 1; 
        while(u){
            if(task[u << 1].empty() && task[u << 1 | 1].empty()) return;
            _upd(u), u >>= 1;
        }
    }

    void clear(int u = 1, int l = 1, int r = n){
        if(l > r) return;
        nxt[u].clear(), pre[u].clear(), task[u].resize(0);
        if(l == r) return;
        int m = l + r >> 1;
        clear(u << 1, l, m), clear(u << 1 | 1, m + 1, r);
    }
} using namespace SegTree;

void init(){
    for(int i = 1; i <= n; i++) for(int S = 0; S < st; S++) sb[i][S] = 0;
    for(int x = 0; x <= INF; x++) X[x].resize(0), Q[x].resize(0);
    clear();
}

void solve(){
    init();

    cin >> n >> m >> k, st = (1 << k);
    for(int i = 1; i <= n; i++) cin >> h[i];
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    for(int i = 1; i <= n; i++){
        for(int S = 0; S < st; S++) for(int j = 0; j < k; j++)
            if((S >> j & 1) && i - j - 1 > 0) sb[i][S] += b[i - j - 1];
        for(int S = 0; S < st; S++) for(int T = S; ; T = (T - 1) & S){
            ll x = h[i] - sb[i][T];
            if(x <= INF) X[max(x, 0ll)].eb(i, S, ((S ^ T) << 1) & (st - 1));
            if((x += a[i]) <= INF) X[max(x, 0ll)].eb(i, S, ((S ^ T) << 1) & (st - 1) | 1);
            if(!T) break;
        }
    }

    for(int i = 1, l, r, x; i <= m; i++) cin >> l >> r >> x, Q[x].eb(l, r, i);

    build();
    for(int x = 0; x <= INF; x++){ // T_max = 3
        for(auto [pos, f, g] : X[x]) upd(pos, f, g);
        for(auto [l, r, id] : Q[x]) ans[id] = query(l, r);
    }

    for(int i = 1; i <= m; i++) cout << (ans[i] ? "Yes\n" : "No\n");
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    for(cin >> c >> T; T; T--) solve();
    cout << flush;
    return 0;
}
```
::::

---

## 作者：dream10 (赞：1)

## Hint

1. 如何利用 $k$ 很小的性质？ 考虑状压 dp。
2. 对于询问的区间，如何快速进行 dp？使用矩阵乘法，区间数据结构。
3. 然而复杂度仍然很大，如果询问的所有 $x$ 都相同，有什么优化的技巧？使用位运算。

## Solution

对于这个问题，有一个朴素的 dp，设 $f(i,j)$ 表示处理了前 $i$ 个位置，$[i-k,i-1]$ 这个区间点被激活的情况，这些点的最大值的最小值。转移就枚举自己的子集，取所有转移可能的最小值。

然后发现这个东西其实可以用矩阵乘法刻画，对于一个区间，如果 dp 进去的状态是 $S$ 出来的状态是 $T$，那么可以算出这个区间处理之后的最大值的最小值，可以使用线段树加上 $(\min,\max)$ 操作的矩阵乘法维护。（注意，这里是把 $\min$ 当成加法，把 $\max$ 当成乘法，因为 $\max$ 有对 $\min$ 的分配律。）对于询问就向量乘矩阵。

此时分析复杂度为 $O(n8^k+q\log n4^k)$。

被特殊性质 B 启发，如果 $x$ 只有一种，我们就可以轻松使用位运算优化了。

如何推广呢？我们利用单调性，把询问进行升序排序，那么对于这些矩阵来说只有 0 变成 1，好处理了很多。接着就要找到 0 变成 1 的时间。首先，对于叶子，可以直接算出 dp 值，然后在合适的时候加入。但是对于非叶子，就不好算了，如果还是进行矩阵乘法，非常的劣。我们只从左右儿子被更新的部分进行矩阵乘法的过程。发现最多只有 $O(n4^k)$ 次翻转，每次进行到父亲的处理都会翻转一次，复杂度均摊。

继续分析复杂度，需要对叶子节点的值进行加入，这里大概有 $O(n4^k)$ 个值，使用计数排序和之前提到的均摊的父亲从左右儿子更新的部分转移，使用压位可以快速找到需要翻转的位，总复杂度可以做到 $O(n \log n + n4^k)$。然后处理叶子节点的 dp 值要 $O(n 3^k)$，询问是 $O(\frac{q\log n4^k}{w})$。

总共复杂度 $O(n4^k+\frac{q\log n4^k}{w})=O(\frac{n8^k}{w}+\frac{q\log n4^k}{w})$。

这题卡常数，记得使用 `__builtin_ctz`，快读快写，自底向上加剪枝，静态全局 `vector`进行优化。

```
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void read(T &a){
    #define gc getchar()
    char c;a=0;int f=1;
    while(!isdigit(c=gc))if(c=='-')f=-1;
    do a=a*10+c-'0';
    while(isdigit(c=gc));
    a*=f;
}
template<typename T>
void write(T a){
    if(a<0)putchar('-'),a=-a;
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
char GC(){
    char c=getchar();
    while(c<=32)c=getchar();
    return c;
}
template<typename T>
void chmin(T &x,T y){if(x>y)x=y;}
template<typename T>
void chmax(T &x,T y){if(x<y)x=y;}
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> PII;
typedef pair<ll,int> PLI;
typedef __int128 lll;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
int ccc=0;
namespace GENSOKYO{
int n,q,K;
const int MAXN=20010,INF=10000000,KK=1<<5;
int c[MAXN],a[MAXN],b[MAXN],d[MAXN][KK];
int popc[KK];
int leaf[MAXN];
bool ans[100010];
struct Q{
    int l,r,id;
    Q(){}
    Q(int l,int r,int id):l(l),r(r),id(id){}
};
vector<Q> qs[1000010];
struct P{
    int pos,y,z;
    P(){}
    P(int pos,int y,int z):pos(pos),y(y),z(z){}
};
vector<P> ps[1000010];
struct Mat{
    ui a[KK],b[KK];
    void clear(){
        for(int i=0;i<1<<K;++i)a[i]=b[i]=0;
    }
};
struct Vec{
    ui a;
    void clear(){
        a=0;
    }
};
Vec operator*(const Vec &A,const Mat &B){
    Vec C;C.clear();
    for(int j=0;j<1<<K;++j)
        if(A.a&B.b[j])
            C.a|=1<<j;
    return C;
}
Mat tr[MAXN<<2];
void build(int x,int L,int R){
    tr[x].clear();
    if(L==R){
        for(int i=0;i<1<<K;++i){
            for(int j=i;;j=(j-1)&i){
                int val=c[L]-d[L][j];
                if(val<=1000000)
                    ps[max(0,val)].emplace_back(P(L,i,((i^j)<<1)&((1<<K)-1)));
                if(val+a[L]<=1000000)
                    ps[max(0,val+a[L])].push_back(P(L,i,((i^j)<<1|1)&((1<<K)-1)));
                if(!j)break;
            }
        }
        leaf[L]=x;
    }else{
        int mid=L+R>>1;
        build(x<<1,L,mid);
        build(x<<1|1,mid+1,R);
    }
}
Vec res;
void upd(int pos,int y,int z){
    static vector<pair<int,int>> tmp1,tmp2;
    int x=leaf[pos],fx;
    tr[x].a[y]|=1<<z;
    tr[x].b[z]|=1<<y;
    tmp1.assign({{y,z}});
    while(x!=1){
        fx=x>>1;
        if(~x&1){
            if(!tmp1.size())return;
            tmp2.clear();
            for(auto &_i:tmp1){
                int i=_i.first,j=_i.second;
                ui mask=~tr[fx].a[i]&tr[x^1].a[j];
                while(mask){
                    int pos=__builtin_ctz(mask);
                    mask^=1<<pos;
                    tr[fx].a[i]|=1<<pos;
                    tr[fx].b[pos]|=1<<i;
                    tmp2.emplace_back(i,pos);
                }
            }
            tmp1.swap(tmp2);
        }else{
            if(!tmp1.size())return;
            tmp2.clear();
            for(auto &_i:tmp1){
                int i=_i.first,j=_i.second;
                ui mask=~tr[fx].b[j]&tr[x^1].b[i];
                while(mask){
                    int pos=__builtin_ctz(mask);
                    mask^=1<<pos;
                    tr[fx].a[pos]|=1<<j;
                    tr[fx].b[j]|=1<<pos;
                    tmp2.emplace_back(pos,j);
                }
            }
            tmp1.swap(tmp2);
        }
        if(!tmp1.size())break;
        x>>=1;
    }
}
void qry(int x,int L,int R,int l,int r){
    if(l<=L&&R<=r){
        res=res*tr[x];
    }else{
        int mid=L+R>>1;
        if(l<=mid)qry(x<<1,L,mid,l,r);
        if(r>mid)qry(x<<1|1,mid+1,R,l,r);
    }
}
void main(){
    for(int i=0;i<KK;++i)popc[i]=__builtin_popcount(i);
    cin>>n>>q>>K;
    for(int i=1;i<=n;++i)read(c[i]);
    for(int i=1;i<=n;++i)read(a[i]);
    for(int i=1;i<=n;++i)read(b[i]);
    for(int i=1;i<=n;++i){
        for(int j=0;j<1<<K;++j){
            d[i][j]=0;
            for(int o=0;o<K;++o)
                if((j>>o&1)&&i-1-o>=1)
                    d[i][j]+=b[i-1-o];
        }
    }
    for(int i=0;i<=1000000;++i)ps[i].clear(),qs[i].clear();
    build(1,1,n);
    for(int i=1,l,r,x;i<=q;++i){
        read(l),read(r),read(x);
        qs[x].emplace_back(Q(l,r,i));
    }
    for(int i=0;i<=1000000;++i){
        for(auto &j:ps[i]){
            upd(j.pos,j.y,j.z);
        }
        for(auto &j:qs[i]){
            res.a=1;
            qry(1,1,n,j.l,j.r);
            ans[j.id]=!!res.a;
        }
    }
    for(int i=1;i<=q;++i)
        puts(ans[i]?"Yes":"No");
}
}
signed main(){
    int T=1;cin>>T>>T;
    while(T--)GENSOKYO::main();
    cerr<<(double)clock()/CLOCKS_PER_SEC<<endl;
    return 0;
}
```

蓬莱人形好题！我非常喜欢。

感谢 Liuxizai 给我提供了特殊性质 B 推广的思路。

---

