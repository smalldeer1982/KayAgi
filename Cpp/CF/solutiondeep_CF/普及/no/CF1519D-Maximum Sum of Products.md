# 题目信息

# Maximum Sum of Products

## 题目描述

You are given two integer arrays $ a $ and $ b $ of length $ n $ .

You can reverse at most one subarray (continuous subsegment) of the array $ a $ .

Your task is to reverse such a subarray that the sum $ \sum\limits_{i=1}^n a_i \cdot b_i $ is maximized.

## 说明/提示

In the first example, you can reverse the subarray $ [4, 5] $ . Then $ a = [2, 3, 2, 3, 1] $ and $ 2 \cdot 1 + 3 \cdot 3 + 2 \cdot 2 + 3 \cdot 4 + 1 \cdot 2 = 29 $ .

In the second example, you don't need to use the reverse operation. $ 13 \cdot 2 + 37 \cdot 4 = 174 $ .

In the third example, you can reverse the subarray $ [3, 5] $ . Then $ a = [1, 8, 3, 6, 7, 6] $ and $ 1 \cdot 5 + 8 \cdot 9 + 3 \cdot 6 + 6 \cdot 8 + 7 \cdot 8 + 6 \cdot 6 = 235 $ .

## 样例 #1

### 输入

```
5
2 3 2 1 3
1 3 2 4 2```

### 输出

```
29```

## 样例 #2

### 输入

```
2
13 37
2 4```

### 输出

```
174```

## 样例 #3

### 输入

```
6
1 8 7 6 3 6
5 9 6 8 8 6```

### 输出

```
235```

# AI分析结果

### 题目内容重写（中文）

给定两个长度为 $n$ 的整数数组 $a$ 和 $b$。你可以翻转数组 $a$ 中的至多一个子数组（连续子段）。你的任务是翻转这样一个子数组，使得 $\sum\limits_{i=1}^n a_i \cdot b_i$ 的值最大。

### 算法分类
动态规划

### 题解分析与结论

本题的核心是通过翻转数组 $a$ 的一个子数组，使得 $a$ 和 $b$ 对应元素的乘积和最大。由于翻转操作只影响一个子数组，因此可以通过枚举所有可能的子数组来找到最优解。然而，直接枚举所有子数组的时间复杂度为 $O(n^3)$，无法通过 $n \leq 5000$ 的数据范围。

大多数题解通过动态规划或中心扩展法将时间复杂度优化到 $O(n^2)$。具体思路是：

1. **中心扩展法**：枚举每个可能的中心点（单个元素或两个相邻元素），然后向左右扩展，计算翻转后的贡献。这种方法的核心是每次扩展时，只需要计算新增的两个元素的贡献，而不需要重新计算整个子数组的贡献。
  
2. **动态规划**：使用 $dp_{i,j}$ 表示翻转 $[i,j]$ 区间后的贡献，通过状态转移方程 $dp_{i,j} = dp_{i+1,j-1} + a_i \times b_j + a_j \times b_i - a_i \times b_i - a_j \times b_j$ 来优化计算。

### 高星题解推荐

#### 题解1：水沝淼㵘（4星）
- **关键亮点**：通过中心扩展法优化了时间复杂度，代码清晰且易于理解。
- **核心代码**：
  ```cpp
  for(int i=1;i<=n;i++){
      long long tmp1=0;
      for(int j=i,k=i;j>=1&&k<=n;j--,k++){
          tmp1+=(a[j]-a[k])*(b[k]-b[j]);
          tmp=maxn(tmp,tmp1);
      }
  }
  ```
- **个人心得**：作者提到最小区间有两种情况（单个元素和相邻两个元素），通过分别处理这两种情况，确保了所有可能的翻转区间都被枚举到。

#### 题解2：RedreamMer（4星）
- **关键亮点**：通过前缀和和后缀和优化了翻转区间的贡献计算，代码简洁且高效。
- **核心代码**：
  ```cpp
  rep(i, 1, 2 * a) {
      int tmp = 0;
      rep(j, 1, min(i, 2 * a - i + 1)) {
          int l = i - j + 1, r = i + j - 1;
          tmp += s1[l] * s2[r] + s1[r] * s2[l];
          if (l == r) tmp -= s1[l] * s2[r];
          ans = max(ans, tmp + L[l - 1] + R[r + 1]);
      }
  }
  ```
- **个人心得**：作者提到反转中心可能为下标是 $\frac{i+(i+1)}{2}$，通过添加 $0$ 位来处理这种情况，类似于 Manacher 算法。

#### 题解3：_shining（4星）
- **关键亮点**：通过动态规划的状态转移方程优化了翻转区间的贡献计算，代码结构清晰。
- **核心代码**：
  ```cpp
  for(int i=1;i<=n;i++){//长度为奇数的区间
      int l = i, r = i; 
      ll t = res;
      while(l >= 1 && r <= n){ 
          ans = max(ans, t);
          l--, r++;//向外扩展 
          if(l < 1 || r > n) break;//超出区间就退出 
          t += a[l] * b[r] + a[r] * b[l] - a[l] * b[l] - a[r] * b[r];//计算贡献 
      }
  }
  ```
- **个人心得**：作者提到对于对称轴，可能长度为奇数或偶数，因此需要分类讨论，确保所有情况都被覆盖。

### 最优关键思路与技巧

1. **中心扩展法**：通过枚举中心点并向左右扩展，优化了翻转区间的贡献计算，避免了重复计算。
2. **动态规划**：通过状态转移方程 $dp_{i,j} = dp_{i+1,j-1} + a_i \times b_j + a_j \times b_i - a_i \times b_i - a_j \times b_j$，将时间复杂度优化到 $O(n^2)$。
3. **前缀和与后缀和**：通过预处理前缀和和后缀和，快速计算翻转区间的贡献，进一步优化了时间复杂度。

### 可拓展之处

1. **类似题目**：可以扩展到多个翻转区间的情况，或者翻转操作有次数限制的情况。
2. **其他优化**：可以考虑使用滑动窗口或其他数据结构进一步优化时间复杂度。

### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：36.50秒