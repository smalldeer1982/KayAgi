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

### 题目内容重写（中文）

#### 最大和

**题目描述**

给定一个包含 $n$ 个整数的数组 $a$。

你需要进行 $k$ 次操作。每次操作，你可以选择数组中的一个连续子数组（可以为空），并在数组中的任意位置插入这个子数组的和。

你的任务是找到进行 $k$ 次操作后数组可能的最大和。

由于这个数可能很大，输出答案时需要对 $10^9+7$ 取模。

**提示**

在第一个测试用例中，最优策略是选择空子数组两次，并将空子数组的和（零）插入到数组中的任意位置，最终得到的数组和为 $(-4) + (-7) + 0 + 0 = -11$，取模 $10^9 + 7$ 后为 $999\,999\,996$。

在第二个测试用例中，最优策略是选择整个数组的和三次，并将其插入到数组中的任意位置，最终得到的数组和为 $2 + 2 + 8 + 12 + 24 + 48 = 96$。

在第四个测试用例中，最优策略是选择数组的前三个数（即 $4, -2, 8$）的和，并将其插入到数组的开头，最终得到的数组和为 $10 + 4 + (-2) + 8 + (-12) + 9 = 17$。

在第七个测试用例中，最优策略是选择空子数组，最终得到的数组和与原数组和相同，取模后为 $42$。

### 题解分析与结论

本题的核心在于通过贪心策略最大化数组和。具体思路是每次操作选择当前数组的最大子段和，并将其插入到最大子段中，使得下一次操作的最大子段和翻倍。通过这种策略，最终数组和可以表示为原数组和加上最大子段和的 $2^k - 1$ 倍。

#### 关键思路与技巧

1. **贪心策略**：每次操作选择最大子段和，并将其插入到最大子段中，使得下一次操作的最大子段和翻倍。
2. **快速幂优化**：计算 $2^k$ 时使用快速幂算法，避免直接计算大数。
3. **取模处理**：由于结果可能为负数，取模时需要先加上模数再取模，确保结果为非负数。

#### 推荐题解

1. **作者：KazamaRuri (5星)**
   - **亮点**：思路清晰，代码简洁，使用了快速幂优化，处理了负数取模的问题。
   - **核心代码**：
     ```cpp
     ll qp(ll x, int y) {
         ll mul = 1;
         while (y) {
             if (y & 1) mul = mul * x % mod;
             x = x * x % mod;
             y >>= 1;
         }
         return mul;
     }
     ```
   - **个人心得**：通过贪心策略和快速幂优化，成功将时间复杂度降低到 $O(n + \log k)$。

2. **作者：oyoham (5星)**
   - **亮点**：代码结构清晰，快速幂优化，处理了负数取模的问题。
   - **核心代码**：
     ```cpp
     int fp(int a, int b, int p = mod) {
         int base = a;
         int ans = 1;
         while (b) {
             if (b & 1) ans = ans * base % p;
             base = base * base % p;
             b >>= 1;
         }
         return ans;
     }
     ```
   - **个人心得**：通过观察题目，发现每次操作的最大子段和翻倍，直接使用等比数列求和公式优化。

3. **作者：cute_overmind (4星)**
   - **亮点**：贪心策略明确，快速幂优化，处理了负数取模的问题。
   - **核心代码**：
     ```cpp
     int qp(int a, int b, int p) {
         int sum = 1;
         while (b) {
             if (b & 1) sum = sum * a % p;
             b >>= 1;
             a = a * a % p;
         }
         return sum;
     }
     ```
   - **个人心得**：通过贪心策略和快速幂优化，成功将时间复杂度降低到 $O(n + \log k)$。

### 推荐题目

1. **P1115 最大子段和**：考察最大子段和的经典题目。
2. **P1226 快速幂**：练习快速幂算法的题目。
3. **P1045 大数取模**：练习大数取模的题目。

### 个人心得总结

- **调试经历**：在处理负数取模时，容易忽略先加模数再取模的步骤，导致结果错误。
- **顿悟感想**：通过贪心策略和快速幂优化，成功将时间复杂度降低到 $O(n + \log k)$，避免了直接模拟的高时间复杂度。

---
处理用时：32.76秒