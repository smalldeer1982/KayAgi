# 题目信息

# Little Elephant and Sorting

## 题目描述

The Little Elephant loves sortings.

He has an array $ a $ consisting of $ n $ integers. Let's number the array elements from 1 to $ n $ , then the $ i $ -th element will be denoted as $ a_{i} $ . The Little Elephant can make one move to choose an arbitrary pair of integers $ l $ and $ r $ $ (1<=l<=r<=n) $ and increase $ a_{i} $ by $ 1 $ for all $ i $ such that $ l<=i<=r $ .

Help the Little Elephant find the minimum number of moves he needs to convert array $ a $ to an arbitrary array sorted in the non-decreasing order. Array $ a $ , consisting of $ n $ elements, is sorted in the non-decreasing order if for any $ i $ $ (1<=i&lt;n) $ $ a_{i}<=a_{i+1} $ holds.

## 说明/提示

In the first sample the array is already sorted in the non-decreasing order, so the answer is $ 0 $ .

In the second sample you need to perform two operations: first increase numbers from second to third (after that the array will be: \[3, 3, 2\]), and second increase only the last element (the array will be: \[3, 3, 3\]).

In the third sample you should make at least 6 steps. The possible sequence of the operations is: (2; 3), (2; 3), (2; 3), (3; 3), (3; 3), (3; 3). After that the array converts to \[7, 7, 7, 47\].

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3
3 2 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
7 4 1 47
```

### 输出

```
6
```

# AI分析结果

### 题目内容
# 小象与排序

## 题目描述
小象喜欢排序。
它有一个由 $n$ 个整数组成的数组 $a$ 。让我们将数组元素从1到 $n$ 编号，那么第 $i$ 个元素将表示为 $a_{i}$ 。小象可以进行一次移动，选择任意一对整数 $l$ 和 $r$ （$1 \leq l \leq r \leq n$），并对所有满足 $l \leq i \leq r$ 的 $i$ ，将 $a_{i}$ 增加1。
帮助小象找到将数组 $a$ 转换为任意非降序排列数组所需的最小移动次数。由 $n$ 个元素组成的数组 $a$ 按非降序排列是指对于任意 $i$ （$1 \leq i \lt n$），都有 $a_{i} \leq a_{i + 1}$ 成立。

## 说明/提示
在第一个样例中，数组已经按非降序排列，所以答案是 $0$ 。
在第二个样例中，你需要执行两次操作：首先将第二个到第三个数字增加（之后数组将变为：\[3, 3, 2\]），然后仅增加最后一个元素（数组将变为：\[3, 3, 3\]）。
在第三个样例中，你至少应该进行6步。可能的操作序列是：(2; 3), (2; 3), (2; 3), (3; 3), (3; 3), (3; 3) 。之后数组转换为 \[7, 7, 7, 47\] 。

## 样例 #1
### 输入
```
3
1 2 3
```
### 输出
```
0
```

## 样例 #2
### 输入
```
3
3 2 1
```
### 输出
```
2
```

## 样例 #3
### 输入
```
4
7 4 1 47
```
### 输出
```
6
```

### 算法分类
贪心

### 综合分析与结论
所有题解思路基本一致，均是通过遍历数组，当发现前一个数大于后一个数时，将两数差值累加到结果中，以此得到使数组变为非降序所需的最少操作次数。其核心在于利用“同增同减差不变原理”，每次遇到不符合非降序的情况，仅考虑当前相邻两项的差值，不影响后续元素间差值关系，是一种贪心策略。各题解都强调要开`long long`类型防止数据溢出。在代码实现上，整体逻辑简单清晰，差异不大。

### 通用建议与扩展思路
对于此类贪心算法题目，关键在于理解问题本质，找到局部最优策略并证明其能导致全局最优解。可拓展到类似的数组操作求最优解问题，如改变操作规则或数组条件，进一步锻炼贪心策略应用能力。

### 洛谷相似题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
- [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)

### 个人心得摘录与总结
多数题解提到“不开`long long`见祖宗”，强调在处理数据时要注意数据范围，防止因类型选择不当导致错误。 

---
处理用时：23.78秒