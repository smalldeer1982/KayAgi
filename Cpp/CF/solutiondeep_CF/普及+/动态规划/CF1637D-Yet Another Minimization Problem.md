# 题目信息

# Yet Another Minimization Problem

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ .

You can perform the following operation any number of times (possibly zero): select an index $ i $ ( $ 1 \leq i \leq n $ ) and swap $ a_i $ and $ b_i $ .

Let's define the cost of the array $ a $ as $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (a_i + a_j)^2 $ . Similarly, the cost of the array $ b $ is $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (b_i + b_j)^2 $ .

Your task is to minimize the total cost of two arrays.

## 说明/提示

In the second test case, in one of the optimal answers after all operations $ a = [2, 6, 4, 6] $ , $ b = [3, 7, 6, 1] $ .

The cost of the array $ a $ equals to $ (2 + 6)^2 + (2 + 4)^2 + (2 + 6)^2 + (6 + 4)^2 + (6 + 6)^2 + (4 + 6)^2 = 508 $ .

The cost of the array $ b $ equals to $ (3 + 7)^2 + (3 + 6)^2 + (3 + 1)^2 + (7 + 6)^2 + (7 + 1)^2 + (6 + 1)^2 = 479 $ .

The total cost of two arrays equals to $ 508 + 479 = 987 $ .

## 样例 #1

### 输入

```
3
1
3
6
4
3 6 6 6
2 7 4 1
4
6 7 2 4
2 5 3 5```

### 输出

```
0
987
914```

# AI分析结果

### 题目重写

#### 题目描述

给定两个长度为 $n$ 的数组 $a$ 和 $b$。

你可以进行任意次数的操作（包括零次）：选择一个下标 $i$（$1 \leq i \leq n$），并交换 $a_i$ 和 $b_i$。

定义数组 $a$ 的代价为 $\sum_{i=1}^{n} \sum_{j=i + 1}^{n} (a_i + a_j)^2$。类似地，数组 $b$ 的代价为 $\sum_{i=1}^{n} \sum_{j=i + 1}^{n} (b_i + b_j)^2$。

你的任务是最小化两个数组的总代价。

#### 说明/提示

在第二个测试用例中，其中一个最优解是操作后 $a = [2, 6, 4, 6]$，$b = [3, 7, 6, 1]$。

数组 $a$ 的代价为 $(2 + 6)^2 + (2 + 4)^2 + (2 + 6)^2 + (6 + 4)^2 + (6 + 6)^2 + (4 + 6)^2 = 508$。

数组 $b$ 的代价为 $(3 + 7)^2 + (3 + 6)^2 + (3 + 1)^2 + (7 + 6)^2 + (7 + 1)^2 + (6 + 1)^2 = 479$。

两个数组的总代价为 $508 + 479 = 987$。

#### 样例 #1

##### 输入

```
3
1
3
6
4
3 6 6 6
2 7 4 1
4
6 7 2 4
2 5 3 5
```

##### 输出

```
0
987
914
```

### 题解分析与结论

#### 综合分析

本题的核心在于通过交换操作最小化两个数组的总代价。代价的计算公式涉及到数组元素的平方和与元素之间的乘积。通过数学推导，可以将代价公式简化为固定部分和可变部分，从而将问题转化为如何通过交换操作最小化可变部分。

大多数题解都采用了动态规划（DP）的思路，通过状态转移方程来求解最小代价。部分题解还使用了模拟退火等启发式算法，但在时间复杂度上不如DP高效。

#### 最优关键思路

1. **数学推导**：通过展开代价公式，将其拆分为固定部分和可变部分。固定部分与数组元素的平方和有关，交换操作不会影响这部分的值；可变部分与数组元素的前缀和有关，交换操作会影响这部分的值。

2. **动态规划**：设 $dp[i][j]$ 表示前 $i$ 个元素中，$a$ 数组的前缀和为 $j$ 时的最小代价。通过状态转移方程，考虑是否交换当前元素，更新 $dp$ 数组。

3. **优化空间**：由于 $a$ 和 $b$ 的前缀和之和是固定的，可以通过一维 DP 数组来优化空间复杂度。

#### 推荐题解

1. **作者：include_BM (赞：16)**  
   **星级：5星**  
   **关键亮点**：通过数学推导将问题转化为DP问题，状态转移方程清晰，代码实现简洁高效。  
   **核心代码**：
   ```cpp
   for(int i=1; i<=n; i++){
       for(int j=0; j<=sum[i-1]; j++){
           if(j >= a[i]) dp[i][j] = min(dp[i][j], dp[i-1][j-a[i]] + a[i]*(j-a[i]) + b[i]*(sum[i-1]-j+a[i]));
           if(j >= b[i]) dp[i][j] = min(dp[i][j], dp[i-1][j-b[i]] + b[i]*(j-b[i]) + a[i]*(sum[i-1]-j+b[i]));
       }
   }
   ```

2. **作者：ckain (赞：6)**  
   **星级：4星**  
   **关键亮点**：通过数学推导简化问题，DP状态转移方程清晰，代码实现较为简洁。  
   **核心代码**：
   ```cpp
   for(int i=1; i<=n; i++){
       for(int j=0; j<=Max; j++){
           if(j-a[i]>=0 && sa[i]+sb[i]-j-b[i]>=0)
               dp[i][j] = min(dp[i][j], dp[i-1][j-a[i]] + (j-a[i])*a[i] + (sa[i]+sb[i]-j-b[i])*b[i]);
           if(j-b[i]>=0 && sa[i]+sb[i]-j-a[i]>=0)
               dp[i][j] = min(dp[i][j], dp[i-1][j-b[i]] + (j-b[i])*b[i] + (sa[i]+sb[i]-j-a[i])*a[i]);
       }
   }
   ```

3. **作者：Jairon314 (赞：1)**  
   **星级：4星**  
   **关键亮点**：通过数学推导简化问题，DP状态转移方程清晰，代码实现较为简洁。  
   **核心代码**：
   ```cpp
   for(int i=1; i<=n; i++){
       for(int j=0; j<=pre[i-1]; j++){
           chmin(dp[i][j+a[i]], dp[i-1][j] + (j)*a[i] + (pre[i-1]-j)*b[i]);
           chmin(dp[i][j+b[i]], dp[i-1][j] + (j)*b[i] + (pre[i-1]-j)*a[i]);
       }
   }
   ```

### 推荐题目

1. **P1048 采药**  
   题目链接：[https://www.luogu.com.cn/problem/P1048](https://www.luogu.com.cn/problem/P1048)  
   考察知识点：动态规划

2. **P1060 开心的金明**  
   题目链接：[https://www.luogu.com.cn/problem/P1060](https://www.luogu.com.cn/problem/P1060)  
   考察知识点：动态规划

3. **P1164 小A点菜**  
   题目链接：[https://www.luogu.com.cn/problem/P1164](https://www.luogu.com.cn/problem/P1164)  
   考察知识点：动态规划

---
处理用时：59.12秒