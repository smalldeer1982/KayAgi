# 题目信息

# Almost All Multiples

## 题目描述

Given two integers $ n $ and $ x $ , a permutation $ ^{\dagger} $ $ p $ of length $ n $ is called funny if $ p_i $ is a multiple of $ i $ for all $ 1 \leq i \leq n - 1 $ , $ p_n = 1 $ , and $ p_1 = x $ .

Find the lexicographically minimal $ ^{\ddagger} $ funny permutation, or report that no such permutation exists.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of each of the integers from $ 1 $ to $ n $ exactly once.

 $ ^{\ddagger} $ Let $ a $ and $ b $ be permutations of length $ n $ . Then $ a $ is lexicographically smaller than $ b $ if in the first position $ i $ where $ a $ and $ b $ differ, $ a_i < b_i $ . A permutation is lexicographically minimal if it is lexicographically smaller than all other permutations.

## 说明/提示

In the first test case, the permutation $ [3,2,1] $ satisfies all the conditions: $ p_1=3 $ , $ p_3=1 $ , and:

- $ p_1=3 $ is a multiple of $ 1 $ .
- $ p_2=2 $ is a multiple of $ 2 $ .

In the second test case, the permutation $ [2,4,3,1] $ satisfies all the conditions: $ p_1=2 $ , $ p_4=1 $ , and:

- $ p_1=2 $ is a multiple of $ 1 $ .
- $ p_2=4 $ is a multiple of $ 2 $ .
- $ p_3=3 $ is a multiple of $ 3 $ .

We can show that these permutations are lexicographically minimal.

No such permutations exist in the third test case.

## 样例 #1

### 输入

```
3
3 3
4 2
5 4```

### 输出

```
3 2 1 
2 4 3 1 
-1```

# AI分析结果

### 题目内容重写

#### 题目描述

给定两个整数 $n$ 和 $x$，一个长度为 $n$ 的排列 $p$ 被称为“有趣的”如果满足以下条件：
- 对于所有 $1 \leq i \leq n - 1$，$p_i$ 是 $i$ 的倍数。
- $p_n = 1$。
- $p_1 = x$。

要求找到字典序最小的“有趣的”排列，或者报告不存在这样的排列。

#### 说明/提示

在第一个测试用例中，排列 $[3,2,1]$ 满足所有条件：$p_1=3$，$p_3=1$，并且：
- $p_1=3$ 是 $1$ 的倍数。
- $p_2=2$ 是 $2$ 的倍数。

在第二个测试用例中，排列 $[2,4,3,1]$ 满足所有条件：$p_1=2$，$p_4=1$，并且：
- $p_1=2$ 是 $1$ 的倍数。
- $p_2=4$ 是 $2$ 的倍数。
- $p_3=3$ 是 $3$ 的倍数。

可以证明这些排列是字典序最小的。

在第三个测试用例中，不存在这样的排列。

#### 样例 #1

##### 输入

```
3
3 3
4 2
5 4
```

##### 输出

```
3 2 1 
2 4 3 1 
-1
```

### 算法分类
构造

### 题解分析与结论

#### 综合分析

本题的核心在于构造一个满足特定条件的排列，并且要求字典序最小。主要难点在于如何合理地安排排列中的元素，使得每个元素都满足其位置的要求，并且最终排列的字典序最小。

#### 题解对比

1. **atomic_int (赞：8)**
   - **亮点**：通过交换元素来优化字典序，思路清晰，代码简洁。
   - **评分**：5星
   - **关键思路**：首先检查 $n$ 是否是 $x$ 的倍数，如果不是则无解。然后构造一个初始排列，通过交换元素来优化字典序。

2. **Alex_Wei (赞：4)**
   - **亮点**：通过连边的方式分析排列的环结构，提出了贪心枚举倍数的思路。
   - **评分**：4星
   - **关键思路**：分析排列的环结构，通过贪心枚举倍数来构造字典序最小的排列。

3. **wheneveright (赞：2)**
   - **亮点**：提出了贪心的优化方法，通过交换元素来优化字典序。
   - **评分**：4星
   - **关键思路**：首先构造一个初始排列，然后通过交换元素来优化字典序。

#### 最优关键思路

最优的思路是通过构造一个初始排列，然后通过交换元素来优化字典序。具体来说，首先检查 $n$ 是否是 $x$ 的倍数，如果不是则无解。然后构造一个初始排列，其中 $p_1 = x$，$p_x = n$，$p_n = 1$，其余位置 $p_i = i$。接着通过交换元素来优化字典序，具体来说，如果存在 $y$ 满足 $x \mid y$ 且 $y \mid n$，则交换 $p_x$ 和 $p_y$，并更新 $x$ 为 $y$。

#### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200005;

int T, n, x, a[maxn];

signed main () {
    ios :: sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    cin >> T;
    while (T--) {
        cin >> n >> x;
        if (n % x != 0) { puts ("-1"); continue ; }
        for (int i = 1; i <= n; i++) a[i] = i;
        a[1] = x; a[x] = n; a[n] = 1;
        for (int i = x + 1, las = x; i < n; i++)
            if (i % las == 0 && n % i == 0) { // 有更优的
                swap (a[las], a[i]);
                las = i;
            }
        for (int i = 1; i <= n; i++) printf ("%d ", a[i]);
        putchar (10);
    }
    return 0;
}
```

#### 可拓展之处

类似的问题可以通过构造初始解然后通过交换或调整来优化解的字典序。这类问题常见于排列构造和字典序优化问题中。

#### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

#### 个人心得

在调试过程中，发现初始构造的排列在某些情况下并不满足字典序最小的要求，因此需要通过交换元素来优化。这一过程需要仔细分析每个元素的位置和其倍数关系，确保交换后的排列仍然满足条件。

---
处理用时：36.14秒