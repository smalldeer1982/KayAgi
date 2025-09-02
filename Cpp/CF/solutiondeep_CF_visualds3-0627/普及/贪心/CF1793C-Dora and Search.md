# 题目信息

# Dora and Search

## 题目描述

As you know, the girl Dora is always looking for something. This time she was given a permutation, and she wants to find such a subsegment of it that none of the elements at its ends is either the minimum or the maximum of the entire subsegment. More formally, you are asked to find the numbers $ l $ and $ r $ $ (1 \leq l \leq r \leq n) $ such that $ a_l \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_l \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ and $ a_r \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_r \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

Help Dora find such a subsegment, or tell her that such a subsegment does not exist.

## 说明/提示

In the first and fourth test cases, it can be shown that there are no desired subsegments.

In the second test case, the subsegment $ [1, 4] $ satisfies all the conditions, because $ \max(a_1, a_2, a_3, a_4) = 4, \min(a_1, a_2, a_3, a_4) = 1 $ , as we see, all the conditions are met.

In the third test case, the subsegment $ [2, 6] $ also satisfies all the conditions described.

## 样例 #1

### 输入

```
4
3
1 2 3
4
2 1 4 3
7
1 3 2 4 6 5 7
6
2 3 6 5 4 1```

### 输出

```
-1
1 4
2 6
-1```

# AI分析结果



### 综合分析与结论

**题目核心**：在排列中寻找一个子段，使得两端点均不是该子段的极值。  
**核心难点**：如何高效判断并排除非法端点，找到合法区间。  
**贪心策略**：  
- 双指针法，初始区间为整个数组。维护当前区间的 `min` 和 `max`。  
- 若当前端点（左或右）等于 `min` 或 `max`，则移动该指针，并更新极值（`min++` 或 `max--`）。  
- 正确性基于排列的连续性，排除的端点不可能成为任何更大区间的合法端点。  

**可视化设计**：  
- **动画方案**：用双色方块表示数组，红色标记当前左右指针，绿色为合法区间。  
- **极值跟踪**：显示当前 `min` 和 `max`，当指针移动时高亮变化。  
- **复古风格**：8-bit 像素动画，移动指针时播放电子音效，找到解时播放胜利音效。  

---

### 题解评分 (≥4星)

1. **TernaryTree（★★★★★）**  
   - **亮点**：代码简洁，双指针逻辑清晰，时间复杂度 O(n)。  
   - **代码**：直接维护极值变量，无需额外数据结构。  

2. **hswfwkj_（★★★★☆）**  
   - **亮点**：详细思路解释，强调极值单调性，代码与逻辑高度对应。  
   - **个人心得**：指出“区间极值单调变化”是核心观察点。  

3. **aeiouaoeiu（★★★★☆）**  
   - **亮点**：结合 ST 表处理极值，思路直观，适合非排列情况。  
   - **优化**：代码中显式处理四种缩进情况，逻辑明确。  

---

### 最优思路与代码

**核心代码（TernaryTree 版本）**  
```cpp
int l = 1, r = n, mn = 1, mx = n;
while (l <= r) {
    if (a[l] == mn)      ++l, ++mn;
    else if (a[l] == mx) ++l, --mx;
    else if (a[r] == mn) --r, ++mn;
    else if (a[r] == mx) --r, --mx;
    else break;
}
if (l > r) cout << -1;
else cout << l << " " << r;
```

**思想**：  
- 初始化极值为排列的全局极值（1 和 n）。  
- 每次排除端点中的极值，并更新极值为下一个可能值。  
- 最终未被排除的区间即为合法解。  

---

### 同类型题目与套路

**通用解法**：  
- **双指针**：处理区间问题，利用单调性逐步缩小范围。  
- **贪心选择**：每次排除不可能的解，保留潜在最优解。  

**推荐题目**：  
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)（单调队列）  
2. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)（双指针求最小覆盖）  
3. [P1712 区间](https://www.luogu.com.cn/problem/P1712)（区间覆盖与极值）  

---

### 可视化与游戏化设计

**动画方案**：  
1. **像素网格**：数组元素显示为 8-bit 方块，左右指针用箭头标记。  
2. **极值高亮**：当前 `min` 和 `max` 用闪烁边框表示。  
3. **音效反馈**：  
   - 移动指针：短促“哔”声。  
   - 找到解：欢快音效。  
   - 无解：低沉音效。  

**交互功能**：  
- **自动演示**：AI 模拟双指针移动，速度可调。  
- **关卡积分**：每正确排除一个端点得 10 分，连击奖励。  

**代码片段（JS 动画）**  
```javascript
function animate() {
    if (l > r) playSound('fail');
    else {
        highlight(l, 'red');
        highlight(r, 'blue');
        checkExtremes();
    }
}
```

---

### 个人心得摘录

- **hswfwkj_**：“极值的单调性是关键，每次排除的端点不可能再参与合法解。”  
- **TernaryTree**：“双指针缩进时，极值的更新直接利用排列特性，无需遍历。”  
- **调试教训**：初始未考虑两端同时为极值的情况，需同时移动两指针。  

---

**总结**：本题通过双指针与极值维护的贪心策略高效求解，结合排列特性实现 O(n) 复杂度。可视化可强化对极值变化和指针移动的理解。

---
处理用时：94.76秒