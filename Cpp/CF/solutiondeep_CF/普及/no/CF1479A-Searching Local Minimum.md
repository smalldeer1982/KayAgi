# 题目信息

# Searching Local Minimum

## 题目描述

This is an interactive problem.

Homer likes arrays a lot and he wants to play a game with you.

Homer has hidden from you a permutation $ a_1, a_2, \dots, a_n $ of integers $ 1 $ to $ n $ . You are asked to find any index $ k $ ( $ 1 \leq k \leq n $ ) which is a local minimum.

For an array $ a_1, a_2, \dots, a_n $ , an index $ i $ ( $ 1 \leq i \leq n $ ) is said to be a local minimum if $ a_i < \min\{a_{i-1},a_{i+1}\} $ , where $ a_0 = a_{n+1} = +\infty $ . An array is said to be a permutation of integers $ 1 $ to $ n $ , if it contains all integers from $ 1 $ to $ n $ exactly once.

Initially, you are only given the value of $ n $ without any other information about this permutation.

At each interactive step, you are allowed to choose any $ i $ ( $ 1 \leq i \leq n $ ) and make a query with it. As a response, you will be given the value of $ a_i $ .

You are asked to find any index $ k $ which is a local minimum after at most $ 100 $ queries.

## 说明/提示

In the example, the first line contains an integer $ 5 $ indicating that the length of the array is $ n = 5 $ .

The example makes five "?" queries, after which we conclude that the array is $ a = [3,2,1,4,5] $ and $ k = 3 $ is local minimum.

## 样例 #1

### 输入

```
5
3
2
1
4
5```

### 输出

```
? 1
? 2
? 3
? 4
? 5
! 3```

# AI分析结果

【题目翻译】
# 寻找局部最小值

## 题目描述

这是一个交互题。

Homer 非常喜欢数组，他想和你玩一个游戏。

Homer 隐藏了一个长度为 $n$ 的排列 $a_1, a_2, \dots, a_n$，其中包含整数 $1$ 到 $n$。你需要找到任意一个索引 $k$（$1 \leq k \leq n$），使得 $k$ 是一个局部最小值。

对于一个数组 $a_1, a_2, \dots, a_n$，索引 $i$（$1 \leq i \leq n$）被称为局部最小值，如果 $a_i < \min\{a_{i-1},a_{i+1}\}$，其中 $a_0 = a_{n+1} = +\infty$。一个数组被称为 $1$ 到 $n$ 的排列，如果它包含从 $1$ 到 $n$ 的所有整数且每个整数恰好出现一次。

最初，你只知道 $n$ 的值，而不知道这个排列的其他信息。

在每个交互步骤中，你可以选择任意 $i$（$1 \leq i \leq n$）并进行查询。作为响应，你将得到 $a_i$ 的值。

你需要在最多 $100$ 次查询后找到一个局部最小值 $k$。

## 说明/提示

在示例中，第一行包含一个整数 $5$，表示数组的长度为 $n = 5$。

示例进行了五次 "?" 查询，之后我们得出结论：数组为 $a = [3,2,1,4,5]$，且 $k = 3$ 是局部最小值。

## 样例 #1

### 输入

```
5
3
2
1
4
5```

### 输出

```
? 1
? 2
? 3
? 4
? 5
! 3```

【算法分类】二分

【题解分析与结论】

该题的核心思路是通过二分法逐步缩小搜索范围，最终找到局部最小值。由于题目允许最多100次查询，而二分法的时间复杂度为 $O(\log n)$，因此该方法在时间上是可行的。各题解的主要区别在于二分的具体实现方式和边界处理。

【评分较高的题解】

1. **作者：Cutest_Junior (赞：10)**
   - **星级：5星**
   - **关键亮点**：通过证明“正确区间”的存在性，确保了二分法的正确性。代码简洁，逻辑清晰，且通过记忆化查询结果减少了不必要的查询次数。
   - **代码核心思想**：每次二分时，查询中间位置和其相邻位置的值，根据比较结果更新搜索区间。
   ```cpp
   while (l < r) {
       int mid = (l + r) >> 1;
       if (arr[mid] == 0) {
           printf("? %d\n", mid);
           fflush(stdout);
           scanf("%d", &arr[mid]);
       }
       if (arr[mid + 1] == 0) {
           printf("? %d\n", mid + 1);
           fflush(stdout);
           scanf("%d", &arr[mid + 1]);
       }
       if (arr[mid] < arr[mid + 1]) {
           r = mid;
       } else {
           l = mid + 1;
       }
   }
   ```

2. **作者：Meickol (赞：0)**
   - **星级：4星**
   - **关键亮点**：通过贪心策略，每次将二分边界更新为较小的位置，确保最终找到的局部最小值是谷底点。代码简洁，逻辑清晰。
   - **代码核心思想**：每次二分时，比较中间位置和其相邻位置的值，更新搜索区间。
   ```cpp
   while (l < r) {
       int mid = (l + r) >> 1;
       if (query(mid) < query(mid + 1)) r = mid;
       else l = mid + 1;
   }
   ```

3. **作者：lightup37 (赞：0)**
   - **星级：4星**
   - **关键亮点**：通过二分法逐步缩小搜索范围，确保在每次查询后都能将搜索区间减半。代码简洁，逻辑清晰。
   - **代码核心思想**：每次二分时，查询中间位置和其相邻位置的值，根据比较结果更新搜索区间。
   ```cpp
   while (l < r) {
       int m = (l + r) >> 1;
       query(m); query(m + 1);
       if (query(m) < query(m + 1)) r = m;
       else l = m + 1;
   }
   ```

【最优关键思路与技巧】
- **二分法**：通过二分法逐步缩小搜索范围，确保在每次查询后都能将搜索区间减半，从而在最多 $O(\log n)$ 次查询内找到局部最小值。
- **记忆化查询**：通过记忆化查询结果，避免重复查询，减少查询次数。

【可拓展之处】
- 类似的问题可以扩展到多维数组中的局部最小值查找，或者在其他类型的函数中寻找极值。

【推荐题目】
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

【个人心得】
- **调试经历**：在处理边界条件时，需要特别注意数组的边界，避免查询到无效位置。
- **顿悟感想**：通过二分法逐步缩小搜索范围，能够有效减少查询次数，提高算法效率。

---
处理用时：35.00秒