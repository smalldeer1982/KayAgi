# 题目信息

# Boot Camp

## 题目描述

Berland State University (BSU) is conducting a programming boot camp. The boot camp will last for $ n $ days, and the BSU lecturers are planning to give some number of lectures during these days.

Some days of the boot camp are already planned as excursion days, and no lectures should be held during these days. To make sure the participants don't get too tired of learning to program, the number of lectures for each day should not exceed $ k_1 $ , and the number of lectures for each pair of consecutive days should not exceed $ k_2 $ .

Can you calculate the maximum number of lectures that can be conducted during the boot camp? Formally, find the maximum integer $ m $ such that it is possible to choose $ n $ non-negative integers $ c_1 $ , $ c_2 $ , ..., $ c_n $ (where $ c_i $ is the number of lectures held during day $ i $ ) so that:

- $ c_1 + c_2 + \dots + c_n = m $ ;
- for each excursion day $ d $ , $ c_d = 0 $ ;
- for each day $ i $ , $ c_i \le k_1 $ ;
- for each pair of consecutive days $ (i, i + 1) $ , $ c_i + c_{i + 1} \le k_2 $ .

Note that there might be some non-excursion days without lectures (i. e., it is possible that $ c_i = 0 $ even if $ i $ is not an excursion day).

## 样例 #1

### 输入

```
4
4 5 7
1011
4 4 10
0101
5 3 4
11011
6 4 6
011101```

### 输出

```
12
8
8
14```

# AI分析结果

### 题目内容重写

# 编程训练营

## 题目描述

Berland州立大学（BSU）正在举办一个编程训练营。训练营将持续$n$天，BSU的讲师们计划在这些天里安排一些讲座。

训练营的某些天已经被安排为游览日，这些天不应该安排讲座。为了确保参与者不会因为学习编程而感到过于疲惫，每天安排的讲座数量不应超过$k_1$，并且连续两天的讲座数量之和不应超过$k_2$。

你能计算出在训练营期间最多可以安排多少场讲座吗？形式上，找出最大的整数$m$，使得可以选择$n$个非负整数$c_1, c_2, \dots, c_n$（其中$c_i$表示第$i$天安排的讲座数量），满足以下条件：

- $c_1 + c_2 + \dots + c_n = m$；
- 对于每个游览日$d$，$c_d = 0$；
- 对于每一天$i$，$c_i \le k_1$；
- 对于每一对连续的天$(i, i + 1)$，$c_i + c_{i + 1} \le k_2$。

注意，可能会有一些非游览日没有安排讲座（即，即使$i$不是游览日，$c_i$也可能为0）。

## 样例 #1

### 输入

```
4
4 5 7
1011
4 4 10
0101
5 3 4
11011
6 4 6
011101
```

### 输出

```
12
8
8
14
```

### 算法分类
动态规划

### 综合分析与结论
该题的核心在于如何在满足每日讲座数量不超过$k_1$且连续两天讲座数量之和不超过$k_2$的条件下，最大化总讲座数量。由于游览日的讲座数量必须为0，且非游览日的讲座数量可以灵活调整，因此可以采用动态规划的方法来解决。

### 通用建议与扩展思路
1. **动态规划**：通过定义状态$dp[i][j]$表示第$i$天安排$j$场讲座时的最大总讲座数量，然后根据前一天的讲座数量进行状态转移。
2. **边界条件**：注意游览日的讲座数量必须为0，且非游览日的讲座数量不能超过$k_1$。
3. **优化**：可以通过滚动数组优化空间复杂度，减少内存使用。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

### 关键代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k1, k2;
    string s;
    cin >> n >> k1 >> k2 >> s;
    
    vector<vector<int>> dp(n + 1, vector<int>(k1 + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        if (s[i - 1] == '1') {
            for (int j = 0; j <= k1; ++j) {
                for (int k = 0; k <= k1; ++k) {
                    if (j + k <= k2) {
                        dp[i][j] = max(dp[i][j], dp[i - 1][k] + j);
                    }
                }
            }
        } else {
            dp[i][0] = dp[i - 1][0];
        }
    }
    
    int max_lectures = 0;
    for (int j = 0; j <= k1; ++j) {
        max_lectures = max(max_lectures, dp[n][j]);
    }
    
    cout << max_lectures << endl;
    return 0;
}
```

### 核心实现思想
1. **状态定义**：$dp[i][j]$表示第$i$天安排$j$场讲座时的最大总讲座数量。
2. **状态转移**：对于非游览日，遍历前一天可能的讲座数量$k$，确保$j + k \leq k_2$，并更新$dp[i][j]$。
3. **边界处理**：对于游览日，直接继承前一天的讲座数量。
4. **结果计算**：最终结果取$dp[n][j]$的最大值。

通过这种方法，可以有效地计算出在满足所有约束条件下的最大讲座数量。

---
处理用时：30.20秒