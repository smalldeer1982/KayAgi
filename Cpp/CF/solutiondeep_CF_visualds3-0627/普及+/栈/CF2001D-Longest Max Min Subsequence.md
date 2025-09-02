# 题目信息

# Longest Max Min Subsequence

## 题目描述

You are given an integer sequence $ a_1, a_2, \ldots, a_n $ . Let $ S $ be the set of all possible non-empty subsequences of $ a $ without duplicate elements. Your goal is to find the longest sequence in $ S $ . If there are multiple of them, find the one that minimizes lexicographical order after multiplying terms at odd positions by $ -1 $ .

For example, given $ a = [3, 2, 3, 1] $ , $ S = \{[1], [2], [3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 3, 1], [3, 2, 1]\} $ . Then $ [2, 3, 1] $ and $ [3, 2, 1] $ would be the longest, and $ [3, 2, 1] $ would be the answer since $ [-3, 2, -1] $ is lexicographically smaller than $ [-2, 3, -1] $ .

A sequence $ c $ is a subsequence of a sequence $ d $ if $ c $ can be obtained from $ d $ by the deletion of several (possibly, zero or all) elements.

A sequence $ c $ is lexicographically smaller than a sequence $ d $ if and only if one of the following holds:

- $ c $ is a prefix of $ d $ , but $ c \ne d $ ;
- in the first position where $ c $ and $ d $ differ, the sequence $ c $ has a smaller element than the corresponding element in $ d $ .

## 说明/提示

In the first example, $ S = \{[1], [2], [3], [1, 3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 1, 3], [3, 2, 1]\} $ . Among them, $ [2, 1, 3] $ and $ [3, 2, 1] $ are the longest and $ [-3, 2, -1] $ is lexicographical smaller than $ [-2, 1, -3] $ , so $ [3, 2, 1] $ is the answer.

In the second example, $ S = \{[1]\} $ , so $ [1] $ is the answer.

## 样例 #1

### 输入

```
4
4
3 2 1 3
4
1 1 1 1
9
3 2 1 3 2 1 3 2 1
1
1```

### 输出

```
3
3 2 1
1
1
3
3 1 2
1
1```

## 样例 #2

### 输入

```
10
2
1 2
10
5 2 1 7 9 7 2 5 5 2
2
1 2
10
2 2 8 7 7 9 8 1 9 6
9
9 1 7 5 8 5 6 4 1
3
3 3 3
6
1 6 4 4 6 5
6
3 4 4 5 3 3
10
4 1 4 5 4 5 10 1 5 1
7
1 2 1 3 2 4 6```

### 输出

```
2
1 2
5
5 1 9 7 2
2
1 2
6
2 7 9 8 1 6
7
9 1 7 5 8 6 4
1
3
4
1 4 6 5
3
4 5 3
4
5 4 10 1
5
2 1 3 4 6```

# AI分析结果



## 算法分类
贪心 + 单调栈

---

## 题解分析与结论

### 核心思路与难点
**核心目标**：构造最长不重复子序列，且奇位取反后字典序最小  
**等价转换**：奇位尽可能大，偶位尽可能小  
**关键步骤**：  
1. 预处理每个元素的最后出现位置（last数组）
2. 维护单调栈，奇偶位交替采用不同单调性
3. 动态调整栈结构，确保后续有足够元素构成最长序列

**解决难点**：  
1. **双重单调性切换**：奇数位要求递减，偶数位要求递增，需交替维护两种单调性
2. **元素可用性判断**：使用vis数组标记已选元素，结合last数组判断能否弹出栈顶
3. **跨层替换**：允许连续弹出两个元素（如栈顶两个元素不符合交替单调性时）

---

## 最优题解评分（≥4星）

### 1. chenmingeng（★★★★★）  
**亮点**：  
- 线性时间复杂度，空间效率极佳  
- 双循环处理单层/双层弹出，巧妙处理交替单调性  
- 代码简洁，仅用数组模拟栈结构

### 2. wujingfey（★★★★☆）  
**亮点**：  
- 详细注释解释交替单调性切换逻辑  
- 通过实例说明跨层替换的必要性  
- 完整包含预处理、栈维护、边界处理全流程

### 3. Z1qqurat（★★★★☆）  
**亮点**：  
- 使用线段树维护区间极值  
- set维护可行区间右端点，保证剩余元素充足  
- 提供两种数据结构组合方案

---

## 核心算法代码实现
```cpp
vector<int> last(n), vis(n), stk(n);
int top = -1;
for (int i = 0; i < n; ++i) {
    if (vis[a[i]]) continue;
    // 弹出单元素（处理当前奇偶位的单调性）
    while (top >= 0 && 
        (top%2 ? a[stk[top]] > a[i] : a[stk[top]] < a[i]) && 
        last[a[stk[top]]] > i) {
        vis[a[stk[top--]]] = 0;
    }
    // 弹出双元素（处理交替单调性冲突）
    while (top >= 1 && 
        (top%2 ? a[stk[top-1]] < a[i] : a[stk[top-1]] > a[i]) &&
        last[a[stk[top-1]]] > i && last[a[stk[top]]] > i) {
        vis[a[stk[top--]]] = 0;
        vis[a[stk[top--]]] = 0;
    }
    stk[++top] = i;
    vis[a[i]] = 1;
}
```

---

## 可视化设计

### 动画方案
**数据结构**：  
- 主栈（波浪形红蓝交替显示奇偶位）  
- 最后出现位置标记（黄色高亮）  
- 当前遍历元素（绿色闪烁）

**操作演示**：  
1. **元素入栈**：绿色元素进入栈，若违反单调性触发弹出  
2. **单层弹出**：红色警告特效标记被弹出元素  
3. **双层弹出**：紫色特效标记连续弹出的两个元素  
4. **奇偶切换**：栈层切换时红蓝背景色交替变化

### 复古像素风格
- **栈结构**：8-bit方块堆叠，奇位深红，偶位深蓝  
- **元素值**：16x16像素数字显示  
- **音效**：  
  - 入栈：NES风格"coin"音效  
  - 弹出：8-bit"explosion"音效  
  - 奇偶切换：经典《超级玛丽》管道穿梭音效

---

## 相似题目推荐
1. P2866 [USACO06NOV] Bad Hair Day（单调栈经典）
2. P1901 发射站（双单调性处理）
3. P3503 [POI2010] KLO-Blocks（极值贪心+栈优化）

---

## 思维拓展
**通用套路**：  
当遇到交替单调性要求时，可通过维护两种规则栈，结合后续元素充足性判断（如last数组）实现贪心选择。此类问题常伴随元素唯一性约束，需用哈希表辅助判重。

---
处理用时：56.77秒