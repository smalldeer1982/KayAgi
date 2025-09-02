# 题目信息

# New Year and Rating

## 题目描述

Every Codeforces user has rating, described with one integer, possibly negative or zero. Users are divided into two divisions. The first division is for users with rating $ 1900 $ or higher. Those with rating $ 1899 $ or lower belong to the second division. In every contest, according to one's performance, his or her rating changes by some value, possibly negative or zero.

Limak competed in $ n $ contests in the year 2016. He remembers that in the $ i $ -th contest he competed in the division $ d_{i} $ (i.e. he belonged to this division just before the start of this contest) and his rating changed by $ c_{i} $ just after the contest. Note that negative $ c_{i} $ denotes the loss of rating.

What is the maximum possible rating Limak can have right now, after all $ n $ contests? If his rating may be arbitrarily big, print "Infinity". If there is no scenario matching the given information, print "Impossible".

## 说明/提示

In the first sample, the following scenario matches all information Limak remembers and has maximum possible final rating:

- Limak has rating $ 1901 $ and belongs to the division $ 1 $ in the first contest. His rating decreases by $ 7 $ .
- With rating $ 1894 $ Limak is in the division $ 2 $ . His rating increases by $ 5 $ .
- Limak has rating $ 1899 $ and is still in the division $ 2 $ . In the last contest of the year he gets $ +8 $ and ends the year with rating $ 1907 $ .

In the second sample, it's impossible that Limak is in the division $ 1 $ , his rating increases by $ 57 $ and after that Limak is in the division $ 2 $ in the second contest.

## 样例 #1

### 输入

```
3
-7 1
5 2
8 2
```

### 输出

```
1907
```

## 样例 #2

### 输入

```
2
57 1
22 2
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
1
-5 1
```

### 输出

```
Infinity
```

## 样例 #4

### 输入

```
4
27 2
13 1
-50 1
8 2
```

### 输出

```
1897
```

# AI分析结果



**算法分类**: 贪心 / 区间约束

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
题目要求找到初始评分，使得经过所有比赛后评分最大。关键在于将每场比赛的条件转换为对初始评分的约束：
- 比赛i前若为Div.1 (`d_i=1`)，初始评分需满足 `x + sum_prev_i ≥ 1900` → `x ≥ 1900 - sum_prev_i`。
- 比赛i前若为Div.2 (`d_i=2`)，初始评分需满足 `x + sum_prev_i ≤ 1899` → `x ≤ 1899 - sum_prev_i`。

通过维护初始评分的上下界（`lower`和`upper`），遍历所有比赛条件，更新上下界：
- `lower`取所有Div.1条件的最大值。
- `upper`取所有Div.2条件的最小值。

最终若 `lower > upper`，无解；若 `upper`未更新（仍为无穷大），输出Infinity；否则最大评分为 `upper + 总变化值`。

#### **解决难点**
1. **前缀和计算**：需要正确计算每场比赛前的累积变化值（`sum_prev_i`）。
2. **边界处理**：初始时上下界为无穷大，需逐步约束。
3. **特殊情况处理**：如无Div.2条件时可能输出Infinity。

---

### **题解评分 (≥4星)**

1. **frankchenfu (★★★★★)**
   - **思路清晰**：直接维护上下界，逻辑简洁。
   - **代码高效**：时间复杂度O(n)，空间O(1)。
   - **正确性保证**：正确处理所有约束条件。

2. **caibet (★★★★☆)**
   - **前缀和优化**：明确转化为前缀和问题。
   - **代码可读性**：使用前缀和数组便于理解。
   - **略微冗余**：前缀和数组存储可优化为变量。

3. **Loi_Anina (★★★☆☆)**
   - **直观模拟**：动态维护当前评分范围。
   - **潜在错误**：在复杂约束下可能出错。
   - **代码可读性**：注释详细但逻辑复杂。

---

### **最优思路提炼**
1. **区间约束法**：将每场比赛的条件转换为初始评分的上下界，通过求交集确定可行区间。
2. **前缀和优化**：动态计算每场比赛前的累积变化，避免重复计算。

---

### **同类型题与算法套路**
- **区间交集问题**：如调度任务的时间窗约束（如LeetCode 986）。
- **贪心约束**：如分配资源时的最大最小值限制（如CF 489B）。

---

### **推荐题目**
1. **CF 489B** - BerSU Ball：贪心匹配问题。
2. **LeetCode 986** - Interval List Intersections：区间交集。
3. **洛谷 P1056** - 排座椅：贪心选择最优分割。

---

### **代码实现（核心逻辑）**
```cpp
#include <iostream>
using namespace std;

const int INF = 0x7fffffff;

int main() {
    int n, c, d;
    int sum_prev = 0, lower = -INF, upper = INF;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> c >> d;
        if (d == 1) {
            lower = max(lower, 1900 - sum_prev);
        } else {
            upper = min(upper, 1899 - sum_prev);
        }
        sum_prev += c;
    }
    if (lower > upper) {
        cout << "Impossible";
    } else if (upper == INF) {
        cout << "Infinity";
    } else {
        cout << upper + sum_prev;
    }
    return 0;
}
```

---

### **可视化与算法演示**
1. **动画设计**：
   - **初始状态**：显示初始评分区间为[-∞, ∞]。
   - **步进更新**：每场比赛后，高亮新约束并更新区间。
   - **颜色标记**：红色表示上界，蓝色表示下界，绿色为可行区。
2. **复古风格**：
   - **8-bit像素**：用方格表示区间变化，音效提示越界。
   - **自动演示**：按比赛顺序自动收缩区间，失败时播放低沉音效。

---

### **总结**
通过区间约束法，将问题转化为维护初始评分的上下界，高效且直观。关键点在于正确转换比赛条件为数学约束，并动态更新区间范围。

---
处理用时：334.33秒