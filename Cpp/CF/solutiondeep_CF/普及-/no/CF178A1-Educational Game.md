# 题目信息

# Educational Game

## 题目描述

The Smart Beaver from ABBYY began to develop a new educational game for children. The rules of the game are fairly simple and are described below.

The playing field is a sequence of $ n $ non-negative integers $ a_{i} $ numbered from $ 1 $ to $ n $ . The goal of the game is to make numbers $ a_{1},a_{2},...,a_{k} $ (i.e. some prefix of the sequence) equal to zero for some fixed $ k $ $ (k<n) $ , and this should be done in the smallest possible number of moves.

One move is choosing an integer $ i $ ( $ 1<=i<=n $ ) such that $ a_{i}>0 $ and an integer $ t $ $ (t>=0) $ such that $ i+2^{t}<=n $ . After the values of $ i $ and $ t $ have been selected, the value of $ a_{i} $ is decreased by $ 1 $ , and the value of $ a_{i+2^{t}} $ is increased by $ 1 $ . For example, let $ n=4 $ and $ a=(1,0,1,2) $ , then it is possible to make move $ i=3 $ , $ t=0 $ and get $ a=(1,0,0,3) $ or to make move $ i=1 $ , $ t=1 $ and get $ a=(0,0,2,2) $ (the only possible other move is $ i=1 $ , $ t=0 $ ).

You are given $ n $ and the initial sequence $ a_{i} $ . The task is to calculate the minimum number of moves needed to make the first $ k $ elements of the original sequence equal to zero for each possible $ k $ $ (1<=k<n) $ .

## 样例 #1

### 输入

```
4
1 0 1 2
```

### 输出

```
1
1
3
```

## 样例 #2

### 输入

```
8
1 2 3 4 5 6 7 8
```

### 输出

```
1
3
6
10
16
24
40
```

# AI分析结果

### 题目内容
# 教育游戏

## 题目描述
来自 ABBYY 的聪明海狸开始为孩子们开发一款新的教育游戏。游戏规则相当简单，如下所述。

游戏场地是一个由 $n$ 个非负整数 $a_{i}$ 组成的序列，编号从 $1$ 到 $n$ 。游戏的目标是使数字 $a_{1},a_{2},...,a_{k}$ （即序列的某个前缀）对于某个固定的 $k$ （$k < n$）等于零，并且应该以尽可能少的移动次数完成。

一次移动是选择一个整数 $i$ （$1 \leq i \leq n$），使得 $a_{i} > 0$ ，以及一个整数 $t$ （$t \geq 0$），使得 $i + 2^{t} \leq n$ 。在选择了 $i$ 和 $t$ 的值之后，$a_{i}$ 的值减 $1$ ，$a_{i + 2^{t}}$ 的值加 $1$ 。例如，设 $n = 4$ 且 $a = (1, 0, 1, 2)$ ，那么可以进行移动 $i = 3$ ，$t = 0$ ，得到 $a = (1, 0, 0, 3)$ ，或者进行移动 $i = 1$ ，$t = 1$ ，得到 $a = (0, 0, 2, 2)$ （唯一可能的其他移动是 $i = 1$ ，$t = 0$ ）。

给定 $n$ 和初始序列 $a_{i}$ 。任务是计算对于每个可能的 $k$ （$1 \leq k < n$），使原始序列的前 $k$ 个元素等于零所需的最小移动次数。

## 样例 #1
### 输入
```
4
1 0 1 2
```
### 输出
```
1
1
3
```

## 样例 #2
### 输入
```
8
1 2 3 4 5 6 7 8
```
### 输出
```
1
3
6
10
16
24
40
```

### 算法分类
枚举

### 题解综合分析与结论
这些题解思路基本一致，均采用暴力枚举的方法。算法要点在于通过枚举每个数要移动到的位置，利用二进制思想计算移动的代价，即通过将移动距离转换为二进制后统计其中 $1$ 的个数来确定最小移动次数。解决难点在于理解为何统计二进制中 $1$ 的个数就是最小移动次数，因为每次移动相当于把剩余距离的第 $t$ 位减一。所有题解均采用 $\mathcal{O}(n^3\log n)$ 的暴力枚举算法，在数据范围较小时可通过，但未做优化，整体质量不高，均未达到 4 星。

### 通用建议与扩展思路
对于此类题目，在暴力枚举的基础上，可以考虑优化。例如，尝试预处理一些数据，减少重复计算。或者思考是否存在更优的算法，如动态规划等，来降低时间复杂度。同类型题可关注涉及序列操作及最小操作次数的题目，类似算法套路可从如何利用数据结构优化枚举过程，或者挖掘题目隐藏的性质以减少枚举量等方面思考。

### 推荐洛谷题目
1. [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)
2. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)
3. [P1219 [USACO1.5]八皇后 Checker Challenge](https://www.luogu.com.cn/problem/P1219)

---
处理用时：31.49秒