# 题目信息

# Array Rearrangment

## 题目描述

You are given two arrays $ a $ and $ b $ , each consisting of $ n $ positive integers, and an integer $ x $ . Please determine if one can rearrange the elements of $ b $ so that $ a_i + b_i \leq x $ holds for each $ i $ ( $ 1 \le i \le n $ ).

## 说明/提示

In the first test case, one can rearrange $ b $ so it'll look like $ [1, 2, 1] $ . In this case, $ 1 + 1 \leq 4 $ ; $ 2 + 2 \leq 4 $ ; $ 3 + 1 \leq 4 $ .

In the second test case, one can set $ b $ to $ [5, 2] $ , then $ 1 + 5 \leq 6 $ ; $ 4 + 2 \leq 6 $ .

In the third test case, no matter how one shuffles array $ b $ , $ a_4 + b_4 = 4 + b_4 > 4 $ .

In the fourth test case, there is only one rearrangement of array $ b $ and it doesn't satisfy the condition since $ 5 + 5 > 5 $ .

## 样例 #1

### 输入

```
4
3 4
1 2 3
1 1 2

2 6
1 4
2 5

4 4
1 2 3 4
1 2 3 4

1 5
5
5```

### 输出

```
Yes
Yes
No
No```

# AI分析结果

### 题目内容
# 数组重排

## 题目描述
给定两个数组 $a$ 和 $b$，每个数组都由 $n$ 个正整数组成，以及一个整数 $x$。请判断是否可以重新排列 $b$ 的元素，使得对于每个 $i$（$1 \leq i \leq n$），都有 $a_i + b_i \leq x$ 成立。

## 说明/提示
在第一个测试用例中，可以将 $b$ 重新排列为 $[1, 2, 1]$。在这种情况下，$1 + 1 \leq 4$；$2 + 2 \leq 4$；$3 + 1 \leq 4$。

在第二个测试用例中，可以将 $b$ 设置为 $[5, 2]$，然后 $1 + 5 \leq 6$；$4 + 2 \leq 6$。

在第三个测试用例中，无论如何打乱数组 $b$，$a_4 + b_4 = 4 + b_4 > 4$。

在第四个测试用例中，数组 $b$ 只有一种重排方式，并且不满足条件，因为 $5 + 5 > 5$。

## 样例 #1
### 输入
```
4
3 4
1 2 3
1 1 2

2 6
1 4
2 5

4 4
1 2 3 4
1 2 3 4

1 5
5
5
```
### 输出
```
Yes
Yes
No
No
```
### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，即通过合理地配对数组 $a$ 和 $b$ 的元素，使得 $a_i + b_i$ 的值尽可能小，从而判断是否满足 $a_i + b_i \leq x$。
- **思路**：大部分题解都提到将数组 $a$ 和 $b$ 进行排序（部分题解利用数组已非降序的条件），然后将 $a$ 中的最小值与 $b$ 中的最大值配对，$a$ 中的次小值与 $b$ 中的次大值配对，以此类推。这样能保证配对后的和尽可能小，若这样配对都存在和大于 $x$ 的情况，则说明无法满足条件。
- **算法要点**：对数组进行排序（若题目未给定数组有序），然后遍历配对的元素，检查是否所有的和都小于等于 $x$。
- **解决难点**：主要难点在于贪心策略的证明，即为什么这样的配对方式能使所有 $a_i + b_i$ 的最大值最小。部分题解通过假设不同的配对方式，比较和的大小来证明。

### 通用建议与扩展思路
对于这类贪心问题，关键在于理解贪心策略的正确性并能清晰地证明。在实现时，注意数组的排序方式和遍历逻辑。相似的题目套路通常围绕如何通过合理的元素配对或选择，以满足特定的条件。可以进一步拓展到更复杂的数组操作或条件判断问题，例如考虑多个数组之间的关系，或者在配对时加入更多的限制条件。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859) 

---
处理用时：29.54秒