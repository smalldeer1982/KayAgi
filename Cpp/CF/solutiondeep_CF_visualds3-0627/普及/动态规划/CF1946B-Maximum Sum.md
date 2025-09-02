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



# 题目中文翻译

## 题目描述

你有一个包含 $n$ 个整数的数组 $a$。

你需要对数组执行恰好 $k$次操作。每次操作中，你可以选择数组的一个连续子数组（可以是空数组），并将这个子数组的和插入到数组的任意位置。

你的任务是找出在执行这 $k$ 次操作后，数组可能的最大和。

由于这个数可能非常大，请将答案对 $10^9 + 7$ 取模后输出。

提示：一个数 $x$ 对 $p$ 取模的余数是指满足 $x = p \cdot q + y$ 的最小非负整数 $y$。

## 说明/提示

样例说明略（保持原样）

---

# 算法分类选择
**线性DP**

---

# 综合分析与结论

## 题解思路与核心难点
1. **最大子段和计算**：使用线性DP计算原数组最大子段和（Kadane算法）
2. **贪心策略**：每次操作插入当前最大子段和，使其在后续操作中指数增长
3. **快速幂优化**：计算 $2^k$ 的快速幂来避免重复乘法
4. **负数处理**：当最大子段和为负时，操作无效（插入空子数组和为0）

## 关键状态转移方程
```python
dp[i] = max(dp[i-1] + a[i], a[i])
max_subarray = max(dp[1..n])
```
可视化设计思路：
- 用像素风格网格展示数组和DP数组，每个单元格显示数值
- 当 `dp[i]` 更新时，用闪光特效高亮变化位置
- 红色高亮表示当前最大子段和的扩展，黄色表示新起点

## 复古游戏化动画设计
1. **8位像素风格**：
   - 16色调色板（经典FC红黄蓝绿）
   - DP数组用绿色方块表示，最大子段和用闪烁红框标记
2. **音效触发**：
   - 状态更新："哔"声（8位方波音效）
   - 找到新最大值：上升音阶
   - 插入操作："叮当"金属声
3. **自动演示模式**：
   - AI自动执行Kadane算法，用箭头指示当前比较的 `dp[i-1]+a[i]` 与 `a[i]`
   - 操作次数计数器以像素数字显示剩余操作次数

---

# 题解清单（≥4星）

## 1. KazamaRuri（5星）
**关键亮点**：
- 清晰推导等比数列求和公式
- 代码正确处理负数取模
- 快速幂实现高效计算
```cpp
ans = (1ll*ans%mod*qp(2,k)%mod + ... )
```

## 2. oyoham（4.5星）
**亮点**：
- 独立推导等比数列公式
- 使用动态规划数组维护子段和
- 代码包含详细注释

## 3. cute_overmind（4星）
**特色**：
- 明确处理最大子段和为负的情况
- 代码结构简洁易读
```cpp
if(maxi < 0) maxi = 0;
```

---

# 核心代码实现

## Kadane算法与快速幂（Python伪代码）
```python
MOD = 10**9+7

def max_sum(n, k, a):
    max_sub = curr = 0
    total = sum(a)
    for x in a:
        curr = max(curr + x, x)
        max_sub = max(max_sub, curr)
    
    if max_sub < 0: 
        return (total % MOD + MOD) % MOD
    
    power = pow(2, k, MOD)
    res = (total + max_sub * (power - 1)) % MOD
    return (res + MOD) % MOD
```

---

# 同类型题目推荐
1. P1115 最大子段和（Kadane算法基础）
2. P3398 仓鼠找sugar（树形DP与路径处理）
3. P4381 岛屿（环形最大子段和）

---

# 可视化设计要点

## Canvas动画核心逻辑
```javascript
// 初始化8位风格画布
ctx.fillStyle = "#00FF00"; // FC经典绿色
drawGrid(dpArray); 

// Kadane算法动画帧
function animateStep(i) {
  highlightCell(i, "yellow"); // 当前元素
  showComparison(dp[i-1]+a[i], a[i]); // 弹出比较窗口
  playSound("bleep"); 
  updateDPCell(i); // 更新网格颜色
}
```

## 音效触发规则
- 状态转移：`WebAudio` 播放 500Hz 方波（持续0.1s）
- 新最大值：三连上升音阶（600Hz→800Hz→1000Hz）
- 错误操作：低频噪音（200Hz 锯齿波）

---

# 个人心得摘录
"在第七个测试用例卡了2小时，终于明白当最大子段和为负时必须取0，这与等比数列的前提条件密切相关。调试时要特别注意边界情况！" —— 题解作者Bc2_ChickenDreamer

---

# 算法演示 URL（示例）
`https://code-visualizer.com/demo-cf1946b` （伪链接，示意用）

---
处理用时：82.46秒