# 题目信息

# Guess the Maximum

## 题目描述

Alice 和 Bob 想出了一个相当奇怪的游戏。他们有一个由整数 $a_1,a_2,\cdots,a_n$ 组成的数列。Alice 会选择一个确定的整数 $k$ 并告诉 Bob，接着：
* Bob 会选择两个整数 $i,j(1\leq i<j\leq n)$，然后在 $a_i,a_{i+1},\cdots,a_j$ 中得出最大的整数；
* 如果得出的整数**严格大于** $k$，那么 Alice 获胜，否则 Bob 获胜。

请帮助 Alice 找到整数 $k$ 的最大值，使得她一定能够获胜。

## 说明/提示

$1\leq i<j\leq n\leq5\times10^4,\sum n\leq5\times10^4,1\leq a_i\leq10^9$。

## 样例 #1

### 输入

```
6
4
2 4 1 7
5
1 2 3 4 5
2
1 1
3
37 8 16
5
10 10 10 10 9
10
3 12 9 5 2 3 2 9 8 2```

### 输出

```
3
1
0
15
9
2```

# AI分析结果



# Guess the Maximum

## 题目描述

Alice 和 Bob 想出了一个奇怪的游戏。他们有一个整数序列 $a_1,a_2,\cdots,a_n$。Alice 选定一个整数 $k$ 并告诉 Bob，接着：
* Bob 选择两个整数 $i,j$（$1\leq i<j\leq n$），在子数组 $a_i,a_{i+1},\cdots,a_j$ 中取最大值；
* 若该最大值**严格大于** $k$，Alice 胜，否则 Bob 胜。

求 Alice 能选的最大 $k$ 使得她必赢。

## 说明/提示

$1\leq n\leq5\times10^4$，$\sum n\leq5\times10^4$，$1\leq a_i\leq10^9$。

---

**关键思路**  
所有长度≥2的子数组的最大值的最小值等于相邻元素对的最大值的最小值。因此，遍历所有相邻元素，计算每对的最大值，取最小值减一即为答案。

**算法要点**  
1. 遍历数组，比较每对相邻元素。
2. 记录这些对的最大值中的最小值。
3. 最终结果为该最小值减一。

**解决难点**  
通过观察发现，任何长度≥2的子数组的最大值至少包含一个相邻元素对的最大值。因此只需考虑相邻元素对的最大值的最小值，无需处理所有子数组，将时间复杂度从 $O(n^2)$ 优化至 $O(n)$。

**核心代码**  
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        int min_max = INT_MAX;
        for (int i = 0; i < n-1; ++i) {
            min_max = min(min_max, max(a[i], a[i+1]));
        }
        cout << min_max - 1 << endl;
    }
    return 0;
}
```

**相似题目**  
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)  
2. [P1440 求区间最小值](https://www.luogu.com.cn/problem/P1440)  
3. [P2216 理想的正方形](https://www.luogu.com.cn/problem/P2216)

---
处理用时：206.55秒