# 题目信息

# [POI 2011] TEM-Temperature

## 题目描述

The Byteotian Institute of Meteorology (BIM) measures the air temperature  daily.

The measurement is done automatically, and its result immediately printed.

Unfortunately, the ink in the printer has long dried out...

The employees of BIM however realised the fact only recently, when the    Byteotian Organisation for Meteorology (BOM) requested access to that data.

An eager intern by the name of Byteasar saved the day, as he systematically    noted down the temperatures reported by two domestic alcohol thermometers    placed on the north and south outside wall of the BIM building.

It was established decades ago by various BIM employees that the temperature    reported by the thermometer on the south wall of the building is never lower    than the actual temperature, while that reported by the thermometer on the    north wall of the building is never higher than the actual temperature.

Thus even though the exact temperatures for each day remain somewhat of    a mystery, the range they were in is known at least.

Fortunately for everyone involved (except Byteasar and you, perhaps),    BOM does not require exact temperatures. They only want to know the longest    period in which the temperature was not dropping (i.e. on each successive    day it was no smaller than on the day before).

In fact, the veteran head of BIM knows very well that BOM would like this    period as long as possible.

To whitewash the negligence he insists that Byteasar determines, based on    his valuable notes, the longest period in which the temperature    could have been not dropping.

Now this is a task that Byteasar did not quite expect on his BIM internship,    and he honestly has no idea how to tackle it.

He asks you for help in writing a program that determines the longest such    period.

某国进行了连续 $ n $ ( $ 1 \le n \le 1,000,000 $）天的温度测量，测量存在误差，测量结果是第 $i$ 天温度在 $[l_i,r_i]$ 范围内。

求最长的连续的一段，满足该段内可能温度不降。


## 样例 #1

### 输入

```
6
6 10
1 5
4 8
2 5
6 8
3 5```

### 输出

```
4```

# AI分析结果



---

**算法分类**: 单调队列

---

### 算法要点与解决难点

#### 核心思路
1. **单调队列维护左端点**：  
   每个元素表示一段连续区间，保存该段的最低温度最大值和起始天数。队列按最低温度单调递减排列，保证队头是当前可能的最优左端点。
2. **关键操作**：  
   - **弹出队头**：当新天的最高温度 `<` 队头的最低温度时，无法形成合法区间，弹出队头。
   - **合并队尾**：从队尾弹出所有最低温度 `<` 当前天最低温度的天，合并其起始天数，保证队列单调性。

#### 解决难点
1. **区间起点的动态维护**：  
   合并被弹出的队尾元素的起始天数，确保连续区间的正确性（如 `Lonely_NewYear` 题解中的 `tmp` 变量）。
2. **时间复杂度优化**：  
   单调队列的 `O(n)` 复杂度确保处理 `1e6` 数据的高效性。

---

### 题解评分（≥4星）
| 题解作者       | 评分 | 亮点                                                                 |
|----------------|------|----------------------------------------------------------------------|
| Lonely_NewYear | ★★★★★ | 详细推导队列维护逻辑，通过 `tmp` 变量修正区间起点，代码简洁高效。     |
| chenxinyang2006 | ★★★★☆ | 双指针结合 ST 表预处理，思路清晰，但复杂度略高。                      |
| zhendelan      | ★★★★☆ | 结构体队列维护区间最大值，代码可读性强，适合理解单调队列本质。        |

---

### 最优思路提炼
1. **队列元素结构**：  
   每个队列元素保存 `(l, r, id)`，其中 `l` 为当前段的最低温度最大值，`id` 为段起始天数。
2. **合并逻辑**：  
   当新天的最低温度高于队尾元素的 `l` 时，合并队尾的起始天数，更新 `l` 为当前天的 `l`。
3. **动态计算区间长度**：  
   每次弹出队头后，用 `当前天数 - 队头起始天数 + 1` 更新答案。

---

### 核心代码实现
```cpp
struct node { int l, r, id; };
deque<node> q;
int ans = 1;

for (int i = 1; i <= n; i++) {
    int l, r; scanf("%d%d", &l, &r);
    // 弹出队头无效元素
    while (!q.empty() && q.front().l > r) q.pop_front();
    // 更新答案
    if (!q.empty()) ans = max(ans, i - q.front().id + 1);
    // 合并队尾并插入新元素
    int tmp = i;
    while (!q.empty() && q.back().l < l) {
        tmp = q.back().id;
        q.pop_back();
    }
    q.push_back({l, r, tmp});
}
```

---

### 可视化设计
1. **动画流程**：  
   - **初始状态**：队列为空，当前天数为 `1`。  
   - **弹出队头**：红色高亮被弹出的元素，显示 `r_i < q.front().l` 的逻辑。  
   - **合并队尾**：蓝色闪烁被合并的元素，显示 `tmp` 的更新过程。  
   - **插入新元素**：绿色显示新入队的 `(l, r, tmp)`，并更新区间长度。  

2. **复古像素风格**：  
   - **颜色方案**：队列元素用 8-bit 调色板（深蓝、浅蓝、红色表示操作）。  
   - **音效**：弹出元素时播放“哔”声，插入时播放“嘟”声，背景音乐为循环 8-bit 旋律。  

3. **交互功能**：  
   - **步进控制**：支持暂停/继续，拖动进度条观察队列变化。  
   - **积分系统**：每次成功扩展区间时得分 +10，连击时额外奖励。  

---

### 类似题目推荐
1. **P1886 滑动窗口**（单调队列模板）  
2. **P2216 [HAOI2007] 理想的正方形**（二维单调队列）  
3. **P1714 切蛋糕**（前缀和+单调队列优化）  

---

**个人心得**：  
调试中发现若不维护合并后的起始天数（如 `tmp`），会导致区间起点错误。例如样例中合并后需将起始天数回退到被合并段的最早天数，而非当前天。这一细节是算法正确性的关键。

---
处理用时：84.78秒