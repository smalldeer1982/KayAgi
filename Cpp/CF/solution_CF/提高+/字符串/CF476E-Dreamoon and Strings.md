# Dreamoon and Strings

## 题目描述

Dreamoon 有一个字符串 $s$ 和一个模式串 $p$，他会先从 $s$ 中删除恰好 $x$ 个字符来产生一个新的字符串 $s'$。然后他会计算 $occ(s',p)$，即从 $s'$ 中能找到的等于 $p$ 的不相交的子串数量的最大值。他想让 $occ(s',p)$ 的值尽可能大。

更形式地说，让我们用 $ans(x)$ 表示所有可以从 $s$ 中删去恰好 $x$ 个字符得到的 $s'$ 中 $occ(s',p)$ 的最大值。Dreamoon 想要知道对于所有的 $x$ $(0 \leq x \leq |s|)$，$ans(x)$ 的值。

## 样例 #1

### 输入

```
aaaaa
aa
```

### 输出

```
2 2 1 1 0 0
```

## 样例 #2

### 输入

```
axbaxxb
ab
```

### 输出

```
0 1 1 2 1 1 0 0
```

# 题解

## 作者：SunnyYuan (赞：1)

## 思路

假设原串为 $s$，匹配的串为 $p$。

我们设 $last_i$ 表示从 $[last_i, i]$ 这一段区间里面能够选择出一个子序列等于 $p$ 的最大值，那我们想要让这一段区间匹配上 $p$，就需要删除 $i - last_i + 1 - \operatorname{len}(p)$ 个元素。

这个 $last_i$ 可以使用 $O(n^2)$ 求出来。

然后我们考虑使用动态规划，设 $f_{i, j}$ 表示考虑到了第 $i$ 个元素，且删除了 $j$ 个元素可以匹配 $p$ 的最大个数。

首先，我们可以不删除任何数字，直接从 $i - 1$ 推过来，即可以选择删除一个元素 $i$，也可以选择不删元素 $i$：

$$f_{i, j} = \max\{f_{i - 1, j}, f_{i - 1, j - 1}\}$$

其次，我们可以完整地匹配一个串，匹配数量 $+1$：

$$f_{i, j} = \max\{f_{i, j}, f_{last_i - 1, j - (i - last_i + 1 - \operatorname{len}(p))} + 1\}$$

最终的答案就是删除 $cnt$ 个，可以获得最大子串数量是 $f_{n, cnt}$ 个。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Dreamoon and Strings
| Contest: Luogu
| URL:     https://www.luogu.com.cn/problem/CF476E
| When:    2023-10-04 16:24:24
| 
| Memory:  250 MB
| Time:    1000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 2010, INF = 0x3f3f3f3f;

char s[N], p[N];
int last[N];
int f[N][N];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s + 1 >> p + 1;
    n = strlen(s + 1), m = strlen(p + 1);
    for (int i = 1; i <= n; i++) {		// 计算 last 数组
        int j = i, x = 0;
        for (x = m; x >= 1; x--) {
            while (j >= 1 && p[x] != s[j]) j--;
            if (j < 1) break;
            j--;
        }
        if (!x) last_i = j + 1;
        else last_i = INF;
    }
    memset(f, -0x3f, sizeof(f));		// 动态规划
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            f[i][j] = f[i - 1][j];
            if (j) f[i][j] = max(f[i][j], f[i - 1][j - 1]);
            if (last_i != INF && (j - (i - last_i + 1 - m)) >= 0) f[i][j] = max(f[i][j], f[last_i - 1][j - (i - last_i + 1 - m)] + 1);
        }
    }
    for (int i = 0; i <= n; i++) cout << f[n][i] << ' ';
    return 0;
}

```

---

