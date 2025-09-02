# 题目信息

# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
4 5
```

## 样例 #2

### 输入

```
3
1 2 4
```

### 输出

```
1
4
```

# AI分析结果



---

**算法分类选择**  
贪心

**题解思路、算法要点与解决难点**  
题目要求选出若干数使它们的按位与结果能被最大的 2^v 整除，且选最多数。核心思路是贪心枚举可能的 v，从高到低检查是否可行。

### 题解对比分析
1. **题解1（Graphcity）**  
   - 核心思路：从高到低枚举 v，收集所有二进制第 v 位为 1 的数，计算它们的按位与。若结果能被 2^v 整除，则输出。
   - 问题：仅检查结果能否被 2^v 整除，未确保低 v 位全为 0，可能导致误判（如结果能被更高的 2^(v+1) 整除）。

2. **题解2（Rye_Catcher）**  
   - 核心思路：同样枚举 v，但检查按位与结果的低 v 位是否为 0。通过 `res & ((1 << v) - 1) == 0` 确保结果仅能被 2^v 整除，无法被更高次方整除。
   - 解决难点：确保结果的低 v 位全为 0，从而保证 v 的最大性。

**结论**  
题解2的贪心策略更严谨，通过严格检查低 v 位是否为 0，确保找到的 v 是最大可能值。

---

**题解评分**  
1. **题解2（Rye_Catcher）** ★★★★☆  
   - 思路清晰，通过检查低 v 位为 0 确保正确性。
   - 代码简洁，逻辑明确。
   
（题解1存在逻辑漏洞，未达4星）

---

**最优思路或技巧提炼**  
1. **高位贪心枚举**：从最高位开始枚举 v，优先保证高位的可行性。
2. **严格条件检查**：通过 `res & (2^v - 1) == 0` 确保结果的低 v 位全为 0。
3. **快速筛选候选数**：仅保留第 v 位为 1 的数，减少计算量。

---

**同类型题或类似算法套路**  
- **位运算贪心**：常见于需逐位确定最大/最小值的题目，如最大异或对（CF276D）。
- **枚举关键位**：如寻找子数组按位与的最大值（LeetCode 1310）。

---

**推荐题目**  
1. CF276D（贪心+位运算）  
2. LeetCode 898（子数组按位或的性质）  
3. CF484B（位运算优化最大值）

---

**可视化与算法演示**  
1. **动画设计**  
   - **像素风格网格**：将每个数的二进制位用网格表示，高亮当前枚举的位（如第 v 位）。
   - **颜色标记**：选中数用绿色，当前按位与结果用红色闪烁。
   - **步进控制**：可单步执行，展示如何筛选候选数及检查条件。
   - **音效提示**：找到可行解时播放成功音效，错误条件时播放警告音。

2. **复古游戏化**  
   - **8位像素风格**：用 16 色调色板渲染二进制网格。
   - **自动演示模式**：AI 自动从高位到低位枚举，动态筛选候选数并检查条件。

---

**代码核心实现**  
```cpp
// 题解2的核心代码
for (int v = 30; v >= 0; v--) {
    int mask = (1 << v) - 1;
    int res = -1;
    vector<int> candidates;
    for (int x : a) {
        if (x & (1 << v)) {
            candidates.push_back(x);
            res = (res == -1) ? x : res & x;
        }
    }
    if (res != -1 && (res & mask) == 0) {
        // 输出结果
    }
}
```

---
处理用时：337.25秒