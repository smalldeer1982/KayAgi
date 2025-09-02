# [IOI 2015] sorting

## 题目描述

Aizhan 有一个由 $N$ 个互不相同的整数组成的序列 $S[0],S[1],\cdots,S[N-1]$，其中 $S[i]$ 取值范围是 $[0,N-1]$。Aizhan 试图通过交换某些元素对的方法将这个序列按照升序排序。Aizhan 的朋友 Ermek 也想交换某些元素对， Ermek 的交换未必有助于 Aizhan 的排序。

Ermek 和 Aizhan 打算通过若干轮次来修改这个序列。在每一轮，Ermek 首先做一次交换，然后 Aizhan 做另一次交换。更确切地说，做交换的人选择两个有效的下标并交换这两个下标的元素。请注意这两个下标可能相同。如果它们相等，则对这个元素自身做交换，并不改变这个序列。

Aizhan 知道 Ermek 并不关心对序列 
$S$ 排序的事情。Aizhan还知道 Ermek 将会选择哪些下标。Ermek 打算参加 $M$ 轮交换，将这些轮次从 $0$ 到 $M-1$ 编号。对于 $0$ 到 $M-1$ 之间的每个 $i$，Ermek 在第 $i$ 轮将选择下标 $X[i]$ 和 $Y[i]$ 的元素进行交换。

Aizhan 要对序列 $S$ 按升序进行排序。在每一轮之前，如果 Aizhan 看到当前的序列已经按升序排列，她将结束这个排序过程。给定初始序列 $S$ 以及 Ermek 要选择的下标，请你找出一个交换的序列，使得 Aizhan 能完成对序列 $S$ 的排序。此外，在有些子任务中，你还要找出尽可能短的交换序列来完成排序任务。题目保证通过 $M$ 或更少的轮次能够将序列 $S$ 排好序。

请注意如果 Aizhan 发现在 Ermek 的交换之后，序列 $S$ 已经排好序，则 Aizhan 可以选择交换两个相同下标（例如 $0$ 和 $0$）的元素。这样，序列 $S$ 在这一轮次之后也完成排序，于是也达到了 Aizhan 的目标。另外，如果初始序列 $S$ 就已经排好序，那么所需的最少排序轮数就是 $0$。

## 说明/提示

对于 $100\%$ 的数据，$1 \le N\le 2 \times 10^5$，$1 \le M \le 6 \times 10^5$。要求 $R$ 取最小值。

## 样例 #1

### 输入

```
5
4 3 2 1 0
6
0 1
1 2
2 3
3 4
0 1
1 2
```

### 输出

```
3
0 4
1 3
3 4```

## 样例 #2

### 输入

```
5
3 0 4 2 1
5
1 1
4 0
2 3
1 4
0 4
```

### 输出

```
3
1 4
4 2
2 2```

# 题解

## 作者：Kinandra (赞：9)

标签: 构造

#### Part 1

设 `E` 的一次操作为 $E$ , `A` 的一次操作为 $A$ , 那么最终的操作序列应该为 $E_1A_1E_2A_2E_3A_3E_4A_4\cdots$ .

发现一组 $AE$ 操作必定可以转化为一组 $EA'$ , 意思是存在一个 `E` 先操作一步, `A` 再操作一步**的效果**与 `A` 先操作一步, `E` 再操作一步**的效果**相同, 并且对于确定的 $E$ , $A$ 和 $A'$ 是一一对应的.

于是我们不妨把所有 $A$ 移动到 $E$ 的后面, 构造一个这样的操作序列 $E_1E_2E_3E_4\cdots A'_1A'_2A'_3A'_4\cdots$ , 并通过这个序列还原出原序列.

#### Part 2

$E_1E_2E_3E_4\cdots A'_1A'_2A'_3A'_4\cdots$ 很容易构造, 我们只需要二分答案, 然后让 `E` 先把操作走完, 求一下此时使排列有序的操作次数( $n-\text{置换环个数}$ ) 并随便构造一下 $A'$ 序列即可.

考虑从 $A'$ 如何还原为 $A$ , 对于已知的 $A, E,$ 考虑使 $AE=EA'$ 的 $A'$ , 有如下几种情况:

- $A=(a,b),E=(c,d)$ , 则 $A'=(a,b)$ .
- $A=(a,b),E=(a,c)$ , 则 $A'=(b,c)$ .
- $A=(a,b),E=(a,b)$ , 则 $A'=(a,b)$ .

不难发现: $A'$ 还原到 $A$ , 如果 $A'$ 与 $E$ 中有相同的位置, 那么就把这个位置变成 $E$ 中的另一个位置. 

#### Part 3

暴力还原原操作序列是 $\mathcal O(n^2)$ 的(一个 $A'$ 需要与 $\mathcal O(n)$ 个 $E$ 交换), 不能承受, 考虑优化. 

发现 $A'$ 与 $E=(a,b)$ 交换等价于把 $a$ 映射到 $b$ , $b$ 映射到 $a$ , 并且这个映射是可以合并的. 于是的到这样一个算法: 从后向前扫 $E$ 序列, 边维护当前 $E$ 后缀对应的映射, 边计算出插在当前 $E$ 前面的 $A$ (详见代码). 这个部分的复杂度是 $\mathcal O(n)$ . 

时间复杂度 $\mathcal O(n\log n)$ .

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();

int n, flg, a[200005];
int m, x[200005], y[200005];

int b[200005];
bool vis[200005];
void get(int t) {
    for (int i = 0; i < n; ++i) b[i] = a[i];
    for (int i = 1; i <= t; ++i) swap(b[x[i]], b[y[i]]);
}
bool check(int x) {
    get(x), memset(vis, 0, n);
    int res = n;
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            --res;
            for (int j = i; !vis[j]; j = b[j]) vis[j] = 1;
        }
    }
    return res <= x;
}

vector<int> res;
void solve(int x) {
    get(x), memset(vis, 0, n);
    for (int i = 0; i < n; ++i)
        if (!vis[i] && b[i] != i)
            for (int j = i; !vis[b[j]]; j = b[j]) vis[j] = 1, res.push_back(j);

    while (res.size() < x) res.push_back(n);
}
int p[200005], fp[200005], rx[200005], ry[200005];
int main() {
    n = read();
    for (int i = 0; i < n; ++i)
        a[i] = read(), flg |= (a[i] != (p[i] = fp[i] = i));
    if (!flg) return puts("0"), 0;
    m = min(read(), n - 1);
    for (int i = 1; i <= m; ++i)
        x[i] = read(), y[i] = read(), x[i] > y[i] ? swap(x[i], y[i]) : void();
    int l = 1, r = m - 1, rs = r + 1, mid;
    while (l <= r) check(mid = l + r >> 1) ? r = (rs = mid) - 1 : l = mid + 1;
    printf("%d\n", rs), solve(rs);
    for (int i = 0; i < rs; ++i) {
        res[i] < n ? rx[i] = p[res[i]], ry[i] = p[b[res[i]]] : 0;
        swap(p[fp[x[rs - i]]], p[fp[y[rs - i]]]);
        swap(fp[x[rs - i]], fp[y[rs - i]]);
    }
    for (int i = 1; i <= rs; ++i) printf("%d %d\n", rx[rs - i], ry[rs - i]);
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```



---

