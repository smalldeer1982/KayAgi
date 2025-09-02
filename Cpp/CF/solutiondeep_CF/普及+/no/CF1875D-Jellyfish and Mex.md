# 题目信息

# Jellyfish and Mex

## 题目描述

You are given an array of $ n $ nonnegative integers $ a_1, a_2, \dots, a_n $ .

Let $ m $ be a variable that is initialized to $ 0 $ , Jellyfish will perform the following operation $ n $ times:

- select an index $ i $ ( $ 1 \leq i \leq |a| $ ) and delete $ a_i $ from $ a $ .
- add $ \operatorname{MEX}(a)^{\dagger} $ to $ m $ .

Now Jellyfish wants to know the minimum possible final value of $ m $ if he performs all the operations optimally.

 $ ^{\dagger} $ The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ , and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, we delete elements from $ a $ in the following order: $ [5,2,\color{red}{1},0,3,0,4,0] \to [5,2,0,3,\color{red}{0},4,0] \to [5,2,\color{red}{0},3,4,0] \to [5,2,3,4,\color{red}{0}] \to [5,2,\color{red}{3},4] \to [\color{red}{5},2,4] \to [\color{red}{2},4] \to [\color{red}{4}] \to [~] $ . The value of $ m $ will be $ 1+1+1+0+0+0+0+0=3 $ .

## 样例 #1

### 输入

```
4
8
5 2 1 0 3 0 4 0
2
1 2
5
1 0 2 114514 0
8
0 1 2 0 1 2 0 3```

### 输出

```
3
0
2
7```

# AI分析结果

### 题目内容
# Jellyfish and Mex

## 题目描述

给定一个包含 $n$ 个非负整数的数组 $a_1, a_2, \dots, a_n$。

初始时，变量 $m$ 为 $0$，Jellyfish 将执行以下操作 $n$ 次：

- 选择一个下标 $i$（$1 \leq i \leq |a|$），并从 $a$ 中删除 $a_i$。
- 将 $\operatorname{MEX}(a)^{\dagger}$ 加到 $m$ 上。

现在，Jellyfish 想知道如果他以最优方式执行所有操作，$m$ 的最小可能值是多少。

$^{\dagger}$ $\operatorname{MEX}(a)$ 是数组 $a$ 中未出现的最小非负整数。例如：

- $\operatorname{MEX}([2,2,1])$ 是 $0$，因为 $0$ 不在数组中。
- $\operatorname{MEX}([3,1,0,1])$ 是 $2$，因为 $0$ 和 $1$ 在数组中，但 $2$ 不在。
- $\operatorname{MEX}([0,3,1,2])$ 是 $4$，因为 $0$、$1$、$2$ 和 $3$ 都在数组中，但 $4$ 不在。

## 说明/提示

在第一个测试用例中，我们按以下顺序从 $a$ 中删除元素：$[5,2,\color{red}{1},0,3,0,4,0] \to [5,2,0,3,\color{red}{0},4,0] \to [5,2,\color{red}{0},3,4,0] \to [5,2,3,4,\color{red}{0}] \to [5,2,\color{red}{3},4] \to [\color{red}{5},2,4] \to [\color{red}{2},4] \to [\color{red}{4}] \to [~]$。$m$ 的值为 $1+1+1+0+0+0+0+0=3$。

## 样例 #1

### 输入

```
4
8
5 2 1 0 3 0 4 0
2
1 2
5
1 0 2 114514 0
8
0 1 2 0 1 2 0 3```

### 输出

```
3
0
2
7```

### 算法分类
动态规划

### 题解分析与结论
该题的核心在于通过动态规划来优化删除顺序，使得最终的 $m$ 值最小。大多数题解都采用了类似的思路：首先计算数组的 $\operatorname{MEX}$，然后通过动态规划来计算删除每个数的最小代价。关键点在于如何定义状态转移方程，以及如何优化计算过程。

### 所选高星题解
1. **作者：weitianyi (赞：12)**  
   - **星级：4.5**  
   - **关键亮点：** 通过动态规划从大到小枚举，优化了状态转移方程，代码简洁且易于理解。  
   - **核心代码：**
     ```cpp
     for (int i = mex; i >= 1; i--) {
         for (int j = 0; j < i; j++) {
             dp[j] = min(dp[j], dp[i] + (cnt[j] - 1) * i + j);
         }
     }
     ```

2. **作者：MarSer020 (赞：11)**  
   - **星级：4.5**  
   - **关键亮点：** 通过栈优化了动态规划的状态转移，减少了不必要的计算，时间复杂度得到了优化。  
   - **核心代码：**
     ```cpp
     for (int i = n - 1; i >= 1; i--) {
         for (int j = i + 1; j <= n; j++) {
             dp[i] = min(dp[i], dp[j] + (cnt[a[i]] - 1) * a[j] + a[i]);
         }
     }
     ```

3. **作者：Lucky_Cloud (赞：7)**  
   - **星级：4**  
   - **关键亮点：** 通过简单的动态规划思路，清晰地解释了状态转移方程，代码实现较为直观。  
   - **核心代码：**
     ```cpp
     for (int i = p; i >= 0; i--) {
         for (int j = i - 1; j >= 0; j--) {
             f[j] = min(f[i] + (c[j] - 1) * i + j, f[j]);
         }
     }
     ```

### 最优关键思路
1. **动态规划状态定义：** 定义 $dp_i$ 表示删除所有小于等于 $i$ 的数的最小代价。
2. **状态转移方程：** $dp_j = \min(dp_j, dp_i + (cnt_j - 1) \times i + j)$，其中 $cnt_j$ 是 $j$ 的出现次数。
3. **优化策略：** 通过从大到小枚举 $i$，减少重复计算，或使用栈优化状态转移。

### 可拓展之处
该题的动态规划思路可以应用于类似的优化问题，如最小化某些操作的总代价。类似的问题可以参考以下题目：
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)

### 个人心得
- **调试经历：** 在实现动态规划时，确保状态转移方程的正确性非常重要，尤其是在处理边界条件时。
- **踩坑教训：** 未正确处理 $\operatorname{MEX}$ 的计算可能导致整个算法的失败。
- **顿悟感想：** 通过从大到小枚举 $i$，可以避免重复计算，显著提高算法效率。

---
处理用时：47.86秒