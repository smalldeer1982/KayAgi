# 题目信息

# Bessie and MEX

## 题目描述

[MOOO! - Doja Cat](https://soundcloud.com/amalaofficial/mooo)

⠀



Farmer John has a permutation $ p_1, p_2, \ldots, p_n $ , where every integer from $ 0 $ to $ n-1 $ occurs exactly once. He gives Bessie an array $ a $ of length $ n $ and challenges her to construct $ p $ based on $ a $ .

The array $ a $ is constructed so that $ a_i $ = $ \texttt{MEX}(p_1, p_2, \ldots, p_i) - p_i $ , where the $ \texttt{MEX} $ of an array is the minimum non-negative integer that does not appear in that array. For example, $ \texttt{MEX}(1, 2, 3) = 0 $ and $ \texttt{MEX}(3, 1, 0) = 2 $ .

Help Bessie construct any valid permutation $ p $ that satisfies $ a $ . The input is given in such a way that at least one valid $ p $ exists. If there are multiple possible $ p $ , it is enough to print one of them.

## 说明/提示

In the first case, $ p = [0, 1, 4, 2, 3] $ is one possible output.

 $ a $ will then be calculated as $ a_1 = \texttt{MEX}(0) - 0 = 1 $ , $ a_2 = \texttt{MEX}(0, 1) - 1 = 1 $ , $ a_3 = \texttt{MEX}(0, 1, 4) - 4 = -2 $ , $ a_4 = \texttt{MEX}(0, 1, 4, 2) - 2 = 1 $ , $ a_5 = \texttt{MEX}(0, 1, 4, 2, 3) - 3 = 2 $ .

So, as required, $ a $ will be $ [1, 1, -2, 1, 2] $ .

## 样例 #1

### 输入

```
3
5
1 1 -2 1 2
5
1 1 1 1 1
3
-2 1 2```

### 输出

```
0 1 4 2 3 
0 1 2 3 4 
2 0 1```

# AI分析结果

### 题目内容重写

#### 题目描述

Farmer John 有一个排列 $ p_1, p_2, \ldots, p_n $，其中每个从 $ 0 $ 到 $ n-1 $ 的整数恰好出现一次。他给 Bessie 一个长度为 $ n $ 的数组 $ a $，并挑战她根据 $ a $ 构造出 $ p $。

数组 $ a $ 的构造方式是 $ a_i = \texttt{MEX}(p_1, p_2, \ldots, p_i) - p_i $，其中 $\texttt{MEX}$ 是一个数组中未出现的最小非负整数。例如，$\texttt{MEX}(1, 2, 3) = 0$，$\texttt{MEX}(3, 1, 0) = 2$。

帮助 Bessie 构造出任意一个满足 $ a $ 的有效排列 $ p $。输入保证至少存在一个有效的 $ p $。如果有多个可能的 $ p $，只需输出其中一个即可。

#### 说明/提示

在第一个样例中，$ p = [0, 1, 4, 2, 3] $ 是一个可能的输出。

$ a $ 的计算方式为 $ a_1 = \texttt{MEX}(0) - 0 = 1 $，$ a_2 = \texttt{MEX}(0, 1) - 1 = 1 $，$ a_3 = \texttt{MEX}(0, 1, 4) - 4 = -2 $，$ a_4 = \texttt{MEX}(0, 1, 4, 2) - 2 = 1 $，$ a_5 = \texttt{MEX}(0, 1, 4, 2, 3) - 3 = 2 $。

因此，$ a $ 为 $ [1, 1, -2, 1, 2] $。

#### 样例 #1

##### 输入

```
3
5
1 1 -2 1 2
5
1 1 1 1 1
3
-2 1 2
```

##### 输出

```
0 1 4 2 3 
0 1 2 3 4 
2 0 1
```

### 题解分析与结论

#### 综合分析

该题的核心是通过给定的数组 $ a $ 构造出满足条件的排列 $ p $。由于 $ p $ 是一个排列，且 $ a_i = \texttt{MEX}(p_1, p_2, \ldots, p_i) - p_i $，因此可以从后往前推导 $ p $ 的值。具体来说，$ p_n = n - a_n $，然后依次向前推导 $ p_{n-1}, p_{n-2}, \ldots, p_1 $。

#### 最优思路与技巧

1. **从后往前推导**：由于 $ p $ 是一个排列，且 $\texttt{MEX}(p_1, p_2, \ldots, p_n) = n$，因此可以从后往前推导 $ p $ 的值，逐步确定每个 $ p_i $。
2. **维护 $\texttt{MEX}$ 值**：在推导过程中，维护当前的 $\texttt{MEX}$ 值，并根据 $ a_i $ 的值更新 $ p_i $ 和 $\texttt{MEX}$。
3. **时间复杂度优化**：通过从后往前推导，可以将时间复杂度优化到 $ O(n) $，避免了复杂的计算。

#### 推荐题解

1. **作者：luobotianle (5星)**
   - **关键亮点**：思路清晰，代码简洁，直接从后往前推导 $ p $ 的值，时间复杂度为 $ O(n) $。
   - **代码片段**：
     ```cpp
     int mex = n;
     for(int i = n; i >= 1; i--){
         p[i] = mex - a[i];
         mex = min(mex, p[i]);
     }
     ```

2. **作者：Zhuluoan (4星)**
   - **关键亮点**：详细分析了从后往前推导的思路，并解释了 $\texttt{MEX}$ 的维护方式，代码实现清晰。
   - **代码片段**：
     ```cpp
     mex = n;
     for(int i = n; i >= 1; i--){
         p[i] = mex - a[i];
         mex = min(p[i], mex);
     }
     ```

3. **作者：hyman00 (4星)**
   - **关键亮点**：提供了两种解题思路，一种是从后往前推导，另一种是从前往后推导，并讨论了可能的扩展情况。
   - **代码片段**：
     ```cpp
     int mex = n;
     for(int i = n; i >= 1; i--){
         p[i] = mex - a[i];
         mex = min(mex, p[i]);
     }
     ```

#### 扩展思路

该题的解题思路可以推广到类似的排列构造问题，特别是涉及到 $\texttt{MEX}$ 的题目。通过从后往前推导，可以有效降低问题的复杂度，并保证构造的排列满足给定的条件。

#### 推荐题目

1. [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

#### 个人心得

在解题过程中，从后往前推导的思路是一个常见的技巧，特别是在涉及到排列和 $\texttt{MEX}$ 的问题中。通过维护当前的 $\texttt{MEX}$ 值，可以有效地构造出满足条件的排列。此外，代码的实现过程中，需要注意边界条件的处理，以确保程序的正确性。

---
处理用时：48.69秒