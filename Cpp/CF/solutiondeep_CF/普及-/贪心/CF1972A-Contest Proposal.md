# 题目信息

# Contest Proposal

## 题目描述

A contest contains $ n $ problems and the difficulty of the $ i $ -th problem is expected to be at most $ b_i $ . There are already $ n $ problem proposals and the difficulty of the $ i $ -th problem is $ a_i $ . Initially, both $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ are sorted in non-decreasing order.

Some of the problems may be more difficult than expected, so the writers must propose more problems. When a new problem with difficulty $ w $ is proposed, the most difficult problem will be deleted from the contest, and the problems will be sorted in a way that the difficulties are non-decreasing.

In other words, in each operation, you choose an integer $ w $ , insert it into the array $ a $ , sort array $ a $ in non-decreasing order, and remove the last element from it.

Find the minimum number of new problems to make $ a_i\le b_i $ for all $ i $ .

## 说明/提示

In the first test case:

- Propose a problem with difficulty $ w=800 $ and $ a $ becomes $ [800,1000,1400,2000,2000,2200] $ .
- Propose a problem with difficulty $ w=1800 $ and $ a $ becomes $ [800,1000,1400,1800,2000,2000] $ .

It can be proved that it's impossible to reach the goal by proposing fewer new problems.

In the second test case:

- Propose a problem with difficulty $ w=1 $ and $ a $ becomes $ [1,4,5,6,7,8] $ .
- Propose a problem with difficulty $ w=2 $ and $ a $ becomes $ [1,2,4,5,6,7] $ .
- Propose a problem with difficulty $ w=3 $ and $ a $ becomes $ [1,2,3,4,5,6] $ .

It can be proved that it's impossible to reach the goal by proposing fewer new problems.

## 样例 #1

### 输入

```
2
6
1000 1400 2000 2000 2200 2700
800 1200 1500 1800 2200 3000
6
4 5 6 7 8 9
1 2 3 4 5 6```

### 输出

```
2
3```

# AI分析结果



### 题目内容

#### 比赛提案

##### 题目描述

一场比赛包含 $n$ 个题目，第 $i$ 题的预期难度至多为 $b_i$。已有 $n$ 个提案，第 $i$ 题的难度为 $a_i$。初始时，$a_1, a_2, \ldots, a_n$ 和 $b_1, b_2, \ldots, b_n$ 均为非递减排序。

某些题目可能比预期更难，因此需要提出新题。每次提案新增难度为 $w$ 的题目后，插入 $a$ 数组并排序，删除最大的元素。求使所有 $a_i \le b_i$ 所需的最少新增题目数。

##### 样例

输入样例 1：
```
2
6
1000 1400 2000 2000 2200 2700
800 1200 1500 1800 2200 3000
6
4 5 6 7 8 9
1 2 3 4 5 6
```
输出样例 1：
```
2
3
```

---

### 题解分析与结论

#### 核心思路：贪心双指针法
1. **排序匹配**：利用题目中 $a$ 和 $b$ 已排序的性质，采用双指针法从前往后匹配。
2. **贪心策略**：尽可能多地保留原 $a$ 中的元素，使其满足 $a[i] \le b[j]$。若当前元素不满足，则移动 $b$ 的指针寻找更大的值。
3. **计算插入次数**：未匹配成功的 $a$ 元素数量即为需插入的次数，即 $n - \text{匹配数}$。

#### 解决难点
- **保留最大匹配数**：通过双指针贪心匹配，确保保留的原 $a$ 元素数量最大化。
- **插入元素的巧妙处理**：插入的小元素填充前部，保证最终排序后前部元素自动满足 $b$ 的条件。

#### 最优代码实现
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];
        
        int i = 0, j = 0;
        while (i < n && j < n) {
            if (a[i] <= b[j]) {
                i++;
                j++;
            } else {
                j++;
            }
        }
        cout << n - i << endl;
    }
    return 0;
}
```

#### 关键技巧
- **双指针贪心**：时间复杂度 $O(n)$，高效匹配。
- **无需显式插入操作**：直接通过匹配数推导插入次数，避免复杂模拟。

---

### 相似题目推荐
1. **P1090 合并果子**（贪心，优先队列）
2. **P1106 删数问题**（贪心选择保留数字）
3. **P1803 凌乱的yyy / 线段覆盖**（活动选择贪心）

---
处理用时：306.83秒