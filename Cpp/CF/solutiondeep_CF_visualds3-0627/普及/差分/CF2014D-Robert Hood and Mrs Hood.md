# 题目信息

# Robert Hood and Mrs Hood

## 题目描述

Impress thy brother, yet fret not thy mother.



Robin's brother and mother are visiting, and Robin gets to choose the start day for each visitor.

All days are numbered from $ 1 $ to $ n $ . Visitors stay for $ d $ continuous days, all of those $ d $ days must be between day $ 1 $ and $ n $ inclusive.

Robin has a total of $ k $ risky 'jobs' planned. The $ i $ -th job takes place between days $ l_i $ and $ r_i $ inclusive, for $ 1 \le i \le k $ . If a job takes place on any of the $ d $ days, the visit overlaps with this job (the length of overlap is unimportant).

Robin wants his brother's visit to overlap with the maximum number of distinct jobs, and his mother's the minimum.

Find suitable start days for the visits of Robin's brother and mother. If there are multiple suitable days, choose the earliest one.

## 说明/提示

In the first test case, the only job fills all $ 2 $ days, both should visit on day $ 1 $ .

In the second test case, day $ 2 $ overlaps with $ 2 $ jobs and day $ 1 $ overlaps with only $ 1 $ .

In the third test case, Robert visits for days $ [1,2] $ , Mrs. Hood visits for days $ [4,5] $ .

## 样例 #1

### 输入

```
6
2 1 1
1 2
4 1 2
1 2
2 4
7 2 3
1 2
1 3
6 7
5 1 2
1 2
3 5
9 2 1
2 8
9 2 4
7 9
4 8
1 3
2 3```

### 输出

```
1 1
2 1
1 4
1 1
1 1
3 4```

# AI分析结果



## 算法分类
差分数组/前缀和

---

## 综合分析与结论

### 核心思路与难点
题目要求在固定长度的窗口内，分别找到与最多/最少任务重叠的起始天。关键难点在于如何高效统计每个可能起始天对应的任务重叠数。各题解主要采用以下方法：

1. **差分数组法**：将每个任务的影响范围映射到起始天的区间上，通过差分数组快速统计覆盖次数。例如，任务区间 `[l_i, r_i]` 对应的起始天范围为 `max(1, l_i-d+1)` 到 `r_i`，通过差分标记后求前缀和即可得到每个起始天的覆盖数。
2. **滑动窗口+Set**：维护当前窗口内的任务右端点，动态调整窗口内的任务数，时间复杂度为 `O(n log n)`。
3. **左右端点统计法**：预处理左右端点前缀和，通过总任务数减去不相交的任务数，直接计算覆盖数。

### 最优思路
**差分数组法**是最优解，理由如下：
- **时间复杂度**：`O(n + k)`，优于其他方法。
- **实现简洁**：仅需差分数组和前缀和，无需复杂数据结构。
- **边界处理清晰**：通过 `max` 和 `min` 确保起始天范围有效。

### 可视化设计
1. **差分构建**：以时间轴展示每个任务如何影响起始天区间，用颜色标记差分加减操作。
2. **前缀和计算**：逐步累加差分数组，动态显示每个起始天的覆盖数。
3. **极值遍历**：光标遍历每个起始天，高亮当前最大/最小值，记录最终结果。

---

## 题解清单（评分≥4星）

1. **cly312（4星）**
   - **亮点**：代码简洁，正确应用差分数组和前缀和，边界处理严谨。
   - **关键代码**：
     ```cpp
     cover[max(1,l-d+1)]++;  // 差分加
     cover[r+1]--;           // 差分减
     for (遍历前缀和) { ... }  // 计算覆盖数
     ```

2. **Temp113（4星）**
   - **亮点**：逻辑与cly312一致，变量命名更清晰。
   - **关键代码**：
     ```cpp
     a[max_(1, l-d+1)]++;    // 差分加
     a[r+1]--;               // 差分减
     ```

3. **sad_lin（4星）**
   - **亮点**：代码与上述一致，注释更详细。
   - **关键代码**：
     ```cpp
     a[max(1ll,l-d+1)]++;    // 差分加
     a[r+1]--;               // 差分减
     ```

---

## 核心代码实现（差分法）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t;
    while (t--) {
        int n, d, k; cin >> n >> d >> k;
        vector<int> cover(n + 2, 0);
        for (int i = 0; i < k; ++i) {
            int l, r; cin >> l >> r;
            cover[max(1, l - d + 1)]++;
            cover[r + 1]--;
        }
        for (int i = 1; i <= n; ++i) cover[i] += cover[i - 1];
        int max_day = 1, min_day = 1;
        for (int i = 1; i <= n - d + 1; ++i) {
            if (cover[i] > cover[max_day]) max_day = i;
            if (cover[i] < cover[min_day]) min_day = i;
        }
        cout << max_day << ' ' << min_day << '\n';
    }
    return 0;
}
```

---

## 同类型题目
1. **P3406 海底高铁**：区间覆盖统计，差分法经典应用。
2. **P2184 贪婪大陆**：查询区间内不同任务数，需结合前缀和与差分。
3. **P3667 区间**：滑动窗口或差分处理极值问题。

---

## 个人心得摘录
- **边界处理**：`max(1, l-d+1)` 避免负数，`r+1` 防止溢出。
- **遍历范围**：起始天仅需遍历 `1` 到 `n-d+1`，避免无效计算。

---

## 可视化与复古动画设计
1. **像素风格时间轴**：用8位色块表示天数，任务区间为红色块，窗口为绿色框。
2. **差分标记动画**：任务影响起始天时，对应区间闪烁黄色，显示差分加减。
3. **前缀和累加**：逐步填充颜色，覆盖数越高颜色越深。
4. **音效设计**：
   - **差分操作**：短促“滴”声。
   - **找到极值**：上扬音效。
5. **自动演示**：按帧步进，展示差分构建、前缀和、极值遍历全过程。

---
处理用时：201.63秒