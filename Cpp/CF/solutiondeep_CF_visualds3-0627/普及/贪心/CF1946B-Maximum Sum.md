# 题目信息

# Maximum Sum

## 题目描述

You have an array $ a $ of $ n $ integers.

You perform exactly $ k $ operations on it. In one operation, you select any contiguous subarray of the array $ a $ (possibly empty) and insert the sum of this subarray anywhere in the array.

Your task is to find the maximum possible sum of the array after $ k $ such operations.

As this number can be very large, output the answer modulo $ 10^9 + 7 $ .

Reminder: the remainder of a number $ x $ modulo $ p $ is the smallest non-negative $ y $ such that there exists an integer $ q $ and $ x = p \cdot q + y $ .

## 说明/提示

In the first test case, it is advantageous to take an empty subarray of the array twice and insert the sum of the empty subarray (zero) anywhere, then the sum of the resulting array will be $ (-4) + (-7) + 0 + 0 = -11 $ , modulo $ 10^9 + 7 $ this is $ 999\,999\,996 $ .

In the second test case, it is advantageous to take the sum of the entire array three times and place it anywhere in the array, then one of the possible sequences of actions: \[ $ 2, 2, 8 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24, 48 $ \], the sum of the final array is $ 2 + 2 + 8 + 12 + 24 + 48 = 96 $ .

In the fourth test case, it is advantageous to take a subarray of the array consisting of the first three numbers (i.e. consisting of the numbers $ 4, -2 $ and $ 8 $ ) and insert its sum at the beginning of the array, thereby obtaining the array \[ $ 10, 4, -2, 8, -12, 9 $ \], the sum of this array is $ 17 $ .

In the seventh test case, it will always be advantageous for us to take an empty subarray of the array. In this case, the sum of the resulting array will not differ from the sum of the original. The answer will be the sum of the original array, taken modulo — $ 42 $ , because $ (-6 \cdot (10^9 + 7) + 42 = -6\,000\,000\,000) $ .

## 样例 #1

### 输入

```
12
2 2
-4 -7
3 3
2 2 8
1 7
7
5 1
4 -2 8 -12 9
7 4
8 14 -9 6 0 -1 3
7 100
5 3 -8 12 -5 -9 3
6 1000
-1000000000 -1000000000 -1000000000 -1000000000 -1000000000 -1000000000
2 1
1000000000 8
5 4
0 0 0 0 0
6 10
48973 757292 58277 -38574 27475 999984
7 1
-1000 1000 -1000 1000 -1000 1000 -1000
10 10050
408293874 -3498597 7374783 295774930 -48574034 26623784 498754833 -294875830 283045804 85938045```

### 输出

```
999999996
96
896
17
351
716455332
42
2
0
897909241
0
416571966```

# AI分析结果



### 【综合分析与结论】

该问题的核心在于贪心策略：每次操作插入当前数组的最大子段和，并将其插入到原最大子段中，使得后续每次的最大子段和翻倍。若最大子段和为负，则插入空子数组的和（0），总和不变。关键步骤如下：

1. **计算最大子段和**：使用Kadane算法动态规划求解。
2. **处理负数情况**：若最大子段和为负，设为0。
3. **等比数列求和**：通过快速幂计算 \(2^k \mod (10^9+7)\)，总增加值为 \(mx \times (2^k - 1)\)。
4. **模运算处理**：确保每一步结果非负。

**贪心选择策略的可视化设计**：
- **动画步骤**：展示初始数组、计算最大子段和、插入位置、翻倍过程。
- **颜色标记**：高亮当前最大子段，插入元素以不同颜色显示。
- **交互控制**：允许调整速度，单步执行观察翻倍过程。

### 【题解清单 (≥4星)】

1. **oyoham（5星）**  
   - **关键亮点**：显式处理最大子段和为负的情况，代码简洁高效，快速幂优化。
   - **代码片段**：
     ```cpp
     if (maxi < 0) maxi = 0;
     int fn = (((fp(2, k) * maxi % mod) + sum - maxi) % mod + mod) % mod;
     ```

2. **cute_overmind（5星）**  
   - **关键亮点**：直接置最大子段和为0，逻辑清晰，代码简洁。
   - **代码片段**：
     ```cpp
     mx = max(0, mx);
     sum = ((sum % mod) + (qp(2, k, mod) - 1) * (mx % mod) % mod) % mod;
     ```

3. **DFbd（4星）**  
   - **关键亮点**：预处理2的幂次，优化计算，代码可读性高。
   - **代码片段**：
     ```cpp
     s[0] = 1;
     for (int i = 1; i <= 200000; i++) s[i] = s[i-1] * 2 % mod;
     ```

### 【最优思路与技巧提炼】

1. **贪心选择依据**：每次插入当前最大子段和并翻倍，确保后续操作收益最大化。
2. **负数处理**：若最大子段和为负，插入0（空子数组），避免总和减少。
3. **快速幂优化**：快速计算 \(2^k \mod (10^9+7)\)，时间复杂度 \(O(\log k)\)。
4. **模运算技巧**：每一步加减后立即取模，避免溢出。

### 【同类型题与算法套路】

- **常见贪心场景**：区间调度、最小生成树（Kruskal）、Huffman编码。
- **典型问题**：
  - **最大子段和**（洛谷P1115）：动态规划或贪心。
  - **活动选择问题**：每次选最早结束的活动。
  - **跳跃游戏**：贪心选择最大跳跃范围。

### 【推荐题目】

1. **洛谷P1115**：基础最大子段和。
2. **洛谷P1090**：合并果子（贪心+堆）。
3. **洛谷P1223**：排队接水（贪心排序）。

### 【个人心得摘录】

- **调试教训**：未处理最大子段和为负时直接计算会导致错误，需显式置零。
- **模运算坑点**：负数的模运算需先加模数再取模，确保结果非负。
- **顿悟点**：翻倍插入的贪心策略可通过等比数列简化计算。

### 【可视化与算法演示】

- **动画设计**：
  - **像素风格**：用8-bit色块表示数组元素，插入元素高亮显示。
  - **动态翻倍**：展示每次插入后最大子段和的增长（如12 → 24 → 48）。
  - **音效提示**：插入操作时播放8-bit音效，背景音乐循环。
- **交互功能**：
  - **步进控制**：暂停/继续/单步执行。
  - **速度调节**：调整动画速度，观察贪心过程。
  - **自动模式**：AI自动执行，模拟贪心决策。

```javascript
// 示例：Canvas绘制贪心过程（伪代码）
function drawAnimation() {
    ctx.clearRect(0, 0, width, height);
    // 绘制原数组
    drawArray(originalArray, 0, 'blue');
    // 高亮当前最大子段
    highlightSubarray(maxSubarray, 'yellow');
    // 绘制插入元素
    drawInsertedElement(sum, position, 'red');
}
```

**复古游戏化设计**：  
- **积分系统**：每正确插入一次得10分，连击加倍。  
- **关卡模式**：逐步增加数组长度和k值，提升难度。  
- **音效设计**：使用Web Audio API播放8-bit音效，增强沉浸感。

---
处理用时：272.51秒