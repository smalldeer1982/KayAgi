# 题目信息

# Increase Subarray Sums

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , consisting of $ n $ integers. You are also given an integer value $ x $ .

Let $ f(k) $ be the maximum sum of a contiguous subarray of $ a $ after applying the following operation: add $ x $ to the elements on exactly $ k $ distinct positions. An empty subarray should also be considered, it has sum $ 0 $ .

Note that the subarray doesn't have to include all of the increased elements.

Calculate the maximum value of $ f(k) $ for all $ k $ from $ 0 $ to $ n $ independently.

## 说明/提示

In the first testcase, it doesn't matter which elements you add $ x $ to. The subarray with the maximum sum will always be the entire array. If you increase $ k $ elements by $ x $ , $ k \cdot x $ will be added to the sum.

In the second testcase:

- For $ k = 0 $ , the empty subarray is the best option.
- For $ k = 1 $ , it's optimal to increase the element at position $ 3 $ . The best sum becomes $ -1 + 5 = 4 $ for a subarray $ [3, 3] $ .
- For $ k = 2 $ , it's optimal to increase the element at position $ 3 $ and any other element. The best sum is still $ 4 $ for a subarray $ [3, 3] $ .
- For $ k = 3 $ , you have to increase all elements. The best sum becomes $ (-2 + 5) + (-7 + 5) + (-1 + 5) = 5 $ for a subarray $ [1, 3] $ .

## 样例 #1

### 输入

```
3
4 2
4 1 3 2
3 5
-2 -7 -1
10 2
-6 -1 -2 4 -6 -1 -4 4 -5 -4```

### 输出

```
10 12 14 16 18
0 4 4 5
4 6 6 7 7 7 7 8 8 8 8```

# AI分析结果

### 题目内容重写
# 增加子数组和

## 题目描述

给定一个由 $n$ 个整数组成的数组 $a_1, a_2, \dots, a_n$，以及一个整数 $x$。

定义 $f(k)$ 为在应用以下操作后，数组 $a$ 中连续子数组的最大和：将 $x$ 加到恰好 $k$ 个不同的位置上。空子数组也应被考虑，其和为 $0$。

注意，子数组不必包含所有被增加的元素。

请分别计算 $f(k)$ 对于所有 $k$ 从 $0$ 到 $n$ 的最大值。

## 说明/提示

在第一个测试用例中，无论你将 $x$ 加到哪些元素上，最大和的子数组始终是整个数组。如果你将 $k$ 个元素增加 $x$，则总和将增加 $k \cdot x$。

在第二个测试用例中：

- 对于 $k = 0$，空子数组是最佳选择。
- 对于 $k = 1$，最优选择是将位置 $3$ 的元素增加 $x$。最佳和变为 $ -1 + 5 = 4 $，对应的子数组为 $[3, 3]$。
- 对于 $k = 2$，最优选择是将位置 $3$ 的元素和任意其他元素增加 $x$。最佳和仍为 $4$，对应的子数组为 $[3, 3]$。
- 对于 $k = 3$，你必须将所有元素增加 $x$。最佳和变为 $ (-2 + 5) + (-7 + 5) + (-1 + 5) = 5 $，对应的子数组为 $[1, 3]$。

## 样例 #1

### 输入

```
3
4 2
4 1 3 2
3 5
-2 -7 -1
10 2
-6 -1 -2 4 -6 -1 -4 4 -5 -4
```

### 输出

```
10 12 14 16 18
0 4 4 5
4 6 6 7 7 7 7 8 8 8 8
```

### 算法分类
动态规划

### 题解分析与结论
该题的核心思路是通过动态规划预处理出不同长度的最大子数组和，然后根据给定的 $k$ 值，计算在增加 $k$ 个 $x$ 后的最大子数组和。难点在于如何高效地计算不同长度的最大子数组和，并在增加 $k$ 个 $x$ 后快速得到结果。

### 所选高分题解
#### 题解1：信息向阳花木 (5星)
**关键亮点**：
- 使用前缀和优化动态规划，计算不同长度的最大子数组和。
- 通过后缀最大值处理，确保在增加 $k$ 个 $x$ 后能够快速得到最大子数组和。
- 代码清晰，逻辑严谨，优化程度高。

**核心代码**：
```cpp
for(int i=1;i<=n;i++)
    for(int j=i;j<=n;j++)
        f[j-i+1]=max(f[j-i+1],s[j]-s[i-1]);
for(int i=n-1;i>=0;i--) f[i]=max(f[i],f[i+1]);
for (int k=0;k<=n;k++){
    f[k]=max(f[k-1],f[k]+k*x);
    cout<<f[k]<<" ";
}
```
**核心实现思想**：
- 首先通过前缀和计算不同长度的最大子数组和。
- 然后通过后缀最大值处理，确保在增加 $k$ 个 $x$ 后能够快速得到最大子数组和。
- 最后根据 $k$ 值，计算并输出结果。

#### 题解2：清烛 (4星)
**关键亮点**：
- 提供了两种解法，一种是基于经典的最大子段和 DP，另一种是基于贪心的解法。
- 代码实现清晰，逻辑严谨，适合不同场景的需求。

**核心代码**：
```cpp
for(int i=1;i<=n;i++) {
    f[i][0] = max(f[i - 1][0] + a[i], a[i]);
    for(int j=1;j<=i;j++) {
        f[i][j] = max(f[i - 1][j] + a[i], a[i], f[i - 1][j - 1] + a[i] + x, a[i] + x);
    }
    for(int j=0;j<=i;j++) chkmax(ans[j], f[i][j]);
}
```
**核心实现思想**：
- 通过动态规划，计算在增加 $k$ 个 $x$ 后的最大子数组和。
- 使用经典的最大子段和 DP 思路，确保在增加 $k$ 个 $x$ 后能够快速得到最大子数组和。

### 最优关键思路或技巧
- 使用前缀和优化动态规划，计算不同长度的最大子数组和。
- 通过后缀最大值处理，确保在增加 $k$ 个 $x$ 后能够快速得到最大子数组和。
- 结合贪心思想，确保在增加 $k$ 个 $x$ 后能够快速得到最大子数组和。

### 可拓展之处
- 类似的问题可以通过动态规划和贪心思想结合来解决，尤其是在需要处理不同长度的子数组和时。
- 可以拓展到更复杂的场景，如多维数组或更复杂的操作。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)

### 个人心得摘录
- **信息向阳花木**：通过前缀和和后缀最大值的处理，确保在增加 $k$ 个 $x$ 后能够快速得到最大子数组和，代码实现清晰，逻辑严谨。
- **清烛**：提供了两种解法，一种是基于经典的最大子段和 DP，另一种是基于贪心的解法，适合不同场景的需求，代码实现清晰，逻辑严谨。

---
处理用时：40.50秒