# 题目信息

# From Hero to Zero

## 题目描述

You are given an integer $ n $ and an integer $ k $ .

In one step you can do one of the following moves:

- decrease $ n $ by $ 1 $ ;
- divide $ n $ by $ k $ if $ n $ is divisible by $ k $ .

For example, if $ n = 27 $ and $ k = 3 $ you can do the following steps: $ 27 \rightarrow 26 \rightarrow 25 \rightarrow 24 \rightarrow 8 \rightarrow 7 \rightarrow 6 \rightarrow 2 \rightarrow 1 \rightarrow 0 $ .

You are asked to calculate the minimum number of steps to reach $ 0 $ from $ n $ .

## 说明/提示

Steps for the first test case are: $ 59 \rightarrow 58 \rightarrow 57 \rightarrow 19 \rightarrow 18 \rightarrow 6 \rightarrow 2 \rightarrow 1 \rightarrow 0 $ .

In the second test case you have to divide $ n $ by $ k $ $ 18 $ times and then decrease $ n $ by $ 1 $ .

## 样例 #1

### 输入

```
2
59 3
1000000000000000000 10
```

### 输出

```
8
19
```

# AI分析结果

### 题目内容
# 从英雄到零

## 题目描述
给定两个整数 $n$ 和 $k$ 。
在一步操作中，你可以执行以下操作之一：
- 将 $n$ 减 $1$；
- 如果 $n$ 能被 $k$ 整除，则将 $n$ 除以 $k$ 。
例如，如果 $n = 27$ 且 $k = 3$，你可以执行以下步骤：$27 \rightarrow 26 \rightarrow 25 \rightarrow 24 \rightarrow 8 \rightarrow 7 \rightarrow 6 \rightarrow 2 \rightarrow 1 \rightarrow 0$ 。
要求计算从 $n$ 到 $0$ 的最小步数。

## 说明/提示
第一个测试用例的步骤为：$59 \rightarrow 58 \rightarrow 57 \rightarrow 19 \rightarrow 18 \rightarrow 6 \rightarrow 2 \rightarrow 1 \rightarrow 0$ 。
在第二个测试用例中，你必须将 $n$ 除以 $k$ $18$ 次，然后将 $n$ 减 $1$ 。

## 样例 #1
### 输入
```
2
59 3
1000000000000000000 10
```
### 输出
```
8
19
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是基于贪心策略，即优先选择能使 $n$ 更快趋近于 $0$ 的操作。当 $n$ 能被 $k$ 整除时，选择除法操作；当 $n$ 不能被 $k$ 整除时，通过减去 $n \% k$ 使 $n$ 成为 $k$ 的倍数，从而快速减少 $n$ 的值。不同题解在实现细节上有所差异，如循环结构、代码风格等。

### 通用建议与扩展思路
对于此类贪心问题，关键在于准确把握问题中的最优子结构性质，确定贪心策略。可以进一步拓展到更复杂的操作组合和条件限制的题目中，例如操作的选择不仅取决于当前数字与除数的关系，还可能与之前的操作历史相关等。

### 洛谷相似题目
- P1094 [NOIP2007 普及组] 纪念品分组
- P1199 [NOIP2010 普及组] 三国游戏
- P1223 排队接水 

---
处理用时：18.62秒