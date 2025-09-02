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
**差分数组**

---

## 题解思路与算法要点

### 核心思路
**将每个工作区间转换为对起始点的贡献区间，使用差分数组高效统计每个起始点对应的重叠工作数。**

1. **区间转换**  
   对于每个工作区间 `[l, r]`，其影响的起始点范围是 `[max(1, l-d+1), r]`。这是因为起始点 `day` 的访问区间 `[day, day+d-1]` 必须与 `[l, r]` 有交集。通过差分数组在此范围内 `+1`，最后前缀和统计每个起始点的重叠数。

2. **差分优化**  
   差分数组 `cover` 在 `max(1, l-d+1)` 处 `+1`，`r+1` 处 `-1`。前缀和后，`cover[day]` 即为起始点 `day` 的重叠工作数。

3. **遍历求解**  
   遍历所有可能的起始点 `day`（范围 `1` 到 `n-d+1`），记录最大和最小的重叠数对应的起始点。

### 解决难点
- **正确转换区间**：需确保起始点的访问区间与工作区间的交集条件，数学推导是关键。
- **高效统计**：差分数组将区间操作优化为 `O(1)`，总时间复杂度 `O(n + k)`，适用于大范围数据。

---

## 题解评分（≥4星）

1. **作者：cly312（4星）**  
   - **亮点**：代码简洁，差分数组实现高效，逻辑清晰。
   - **代码**：正确处理区间转换，前缀和统计后遍历求解。

2. **作者：Temp113（4星）**  
   - **亮点**：与cly312思路一致，变量命名更规范，代码可读性略优。

3. **作者：doumingze（4星）**  
   - **亮点**：双指针滑动窗口维护当前覆盖数，时间复杂度同样优秀，实现新颖。

---

## 最优思路与技巧提炼

### 关键技巧
1. **差分数组的区间操作**  
   将区间 `[L, R]` 的贡献转化为差分数组的 `L` 处 `+1` 和 `R+1` 处 `-1`，前缀和快速统计每个位置的总贡献。

2. **数学条件转换**  
   确定起始点 `day` 的访问区间与工作区间交集的数学条件，转换为起始点的有效范围。

3. **滑动窗口维护（双指针）**  
   维护窗口 `[L, R]`，动态更新当前覆盖数，避免重复计算。

---

## 同类型题与算法套路

### 类似问题
- **区间覆盖统计**：如统计每个位置被多少区间覆盖，或求覆盖数的最大/最小值。
- **滑动窗口最值**：窗口固定或可变长度，动态维护窗口内属性。

### 通用解法
- **差分数组**：适用于区间批量加减操作。
- **前缀和/后缀和**：预处理后快速查询区间属性。
- **双指针**：滑动窗口维护当前状态，减少重复计算。

---

## 推荐题目
1. **P2184**：统计农田的覆盖数（差分数组经典应用）。
2. **P3406**：海底高铁（差分数组优化区间修改）。
3. **P1719**：最大加权矩形（二维前缀和）。

---

## 个人心得摘录
- **调试关键**：验证区间转换的正确性，尤其是边界条件（如 `l-d+1` 可能小于1）。
- **优化经验**：差分数组在处理区间问题时，比线段树等数据结构更高效。

---

## 可视化算法设计

### 核心流程
1. **差分数组构建**  
   - 高亮当前处理的区间 `[l, r]`，在对应位置更新差分数组。
   - 显示差分数组的 `+1` 和 `-1` 操作。

2. **前缀和计算**  
   - 逐步计算前缀和，显示每个起始点的覆盖数变化。

3. **遍历求解**  
   - 动态标记当前最大/最小值及其位置，更新结果。

### 复古像素风格
- **颜色方案**：8位色（绿、红、蓝分别表示操作、当前值、结果）。
- **音效**：  
  - 差分操作时播放“滴”声。
  - 找到最大/最小值时播放“成功”音效。
- **动画**：Canvas绘制网格，差分操作时对应位置闪烁，前缀和逐格填充。

### 交互设计
- **步进控制**：允许单步执行差分操作、前缀和、遍历。
- **自动演示**：按预设速度自动播放，展示完整流程。
- **对比模式**：并行显示差分数组与双指针法的执行过程。

---

## 代码实现（核心逻辑）

```cpp
// 差分数组解法（cly312）
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t;
    while (t--) {
        int n, d, k; cin >> n >> d >> k;
        vector<int> cover(n + 2, 0); // 差分数组
        for (int i = 0; i < k; ++i) {
            int l, r; cin >> l >> r;
            int start = max(1, l - d + 1);
            cover[start]++;
            cover[r + 1]--;
        }
        // 前缀和计算覆盖数
        for (int i = 1; i <= n; ++i) cover[i] += cover[i - 1];
        // 遍历找最大和最小
        int bday = 1, mday = 1, maxn = -1, minn = INT_MAX;
        for (int day = 1; day <= n - d + 1; ++day) {
            if (cover[day] > maxn) { maxn = cover[day]; bday = day; }
            if (cover[day] < minn) { minn = cover[day]; mday = day; }
        }
        cout << bday << ' ' << mday << '\n';
    }
    return 0;
}
```

---
处理用时：114.53秒