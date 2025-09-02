# 题目信息

# Paprika and Permutation

## 题目描述

Paprika loves permutations. She has an array $ a_1, a_2, \dots, a_n $ . She wants to make the array a permutation of integers $ 1 $ to $ n $ .

In order to achieve this goal, she can perform operations on the array. In each operation she can choose two integers $ i $ ( $ 1 \le i \le n $ ) and $ x $ ( $ x > 0 $ ), then perform $ a_i := a_i \bmod x $ (that is, replace $ a_i $ by the remainder of $ a_i $ divided by $ x $ ). In different operations, the chosen $ i $ and $ x $ can be different.

Determine the minimum number of operations needed to make the array a permutation of integers $ 1 $ to $ n $ . If it is impossible, output $ -1 $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

For the first test, the only possible sequence of operations which minimizes the number of operations is:

- Choose $ i=2 $ , $ x=5 $ . Perform $ a_2 := a_2 \bmod 5 = 2 $ .

For the second test, it is impossible to obtain a permutation of integers from $ 1 $ to $ n $ .

## 样例 #1

### 输入

```
4
2
1 7
3
1 5 4
4
12345678 87654321 20211218 23571113
9
1 2 3 4 18 19 5 6 7```

### 输出

```
1
-1
4
2```

# AI分析结果



### 综合分析与结论

**题目核心**：通过取模操作将数组转换为1~n的排列，求最小操作次数。关键在于贪心策略的设计，确保每个元素能通过取模变为所需目标数。

**贪心策略核心**：
1. **处理重复与超出范围的元素**：将原数组中无法直接作为排列的元素（重复或超过n）收集为`extra`数组。
2. **目标数匹配**：将缺失的1~n元素收集为`target`数组，排序后与`extra`数组一一匹配，验证每个`extra[i] > 2 * target[i]`。

**难点**：
- **重复元素处理**：需确保每个目标数仅被使用一次。
- **数学条件验证**：必须满足模后结果的范围约束（即`extra[i] > 2 * target[i]`）。

**可视化设计**：
- **复古像素风格**：用8位像素方块表示数组元素，绿色表示已匹配元素，红色表示需操作的元素。
- **动态匹配展示**：逐步连接`extra`与`target`元素，若条件满足则高亮绿色并播放成功音效，否则红色警告。
- **交互控制**：支持暂停、步进、自动播放，显示当前匹配条件和剩余操作次数。

---

### 题解评分（≥4星）

1. **RevolutionBP（4星）**  
   - **亮点**：正确处理重复元素，双指针扫描优化匹配过程，代码结构清晰。
2. **Fu_Da_Ying（4星）**  
   - **亮点**：简洁的条件判断（`j >= (a[i]+1)/2`），高效处理`vis`数组标记。
3. **lzy120406（4星）**  
   - **亮点**：明确分离`extra`与`target`数组，排序后贪心匹配，代码可读性高。

---

### 最优思路提炼

1. **排序预处理**：将原数组排序以简化后续处理。
2. **分离有效元素**：标记已存在的1~n元素，收集需处理的`extra`和缺失的`target`数组。
3. **贪心匹配验证**：升序排列`extra`和`target`，检查每个`extra[i] > 2 * target[i]`，若全部满足则操作数为`extra`长度，否则无解。

**关键代码片段**：
```cpp
// 分离需处理元素与目标数
vector<int> extra, target;
for (int i = 1; i <= n; i++) {
    if (a[i] <= n && !used[a[i]]) used[a[i]] = true;
    else extra.push_back(a[i]);
}
for (int i = 1; i <= n; i++)
    if (!used[i]) target.push_back(i);

// 贪心验证
sort(extra.begin(), extra.end());
sort(target.begin(), target.end());
for (int i = 0; i < extra.size(); i++) {
    if (extra[i] <= 2 * target[i]) return -1;
}
return extra.size();
```

---

### 类似题目推荐

1. **P1969 积木大赛**：贪心调整高度差，类似逐步满足条件。
2. **P1223 排队接水**：贪心排序最小化等待时间。
3. **P1090 合并果子**：优先队列贪心选择最小代价。

---

### 可视化算法演示

**步骤动态展示**：
1. **初始状态**：原数组排序后分为有效（绿色）和需处理（红色）部分。
2. **匹配过程**：逐个将红色方块（`extra`）与下方蓝色方块（`target`）连线，条件满足则变绿，计数器+1。
3. **失败终止**：若某步条件不满足，播放警告音效，标记红色终止线。

**复古游戏化设计**：
- **像素绘制**：Canvas绘制元素和连线，8-bit音效增强沉浸感。
- **自动模式**：AI自动执行匹配，速度可调，展示贪心决策过程。
- **积分系统**：每成功匹配得10分，连续成功触发连击加分。

---

### 个人心得摘录

- **重复元素陷阱**：未去重直接匹配会导致同一元素多次使用，需严格标记已使用的位置。
- **排序必要性**：升序排列确保小的目标数优先匹配，避免大数浪费在小目标上。
- **数学约束验证**：理解模运算后的最大可能值（即`a > 2b`）是解题突破口。

---
处理用时：107.16秒