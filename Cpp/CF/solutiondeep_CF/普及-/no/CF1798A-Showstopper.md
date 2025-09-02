# 题目信息

# Showstopper

## 题目描述

You are given two arrays $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ .

In one operation, you can choose any integer $ i $ from $ 1 $ to $ n $ and swap the numbers $ a_i $ and $ b_i $ .

Determine whether, after using any (possibly zero) number of operations, the following two conditions can be satisfied simultaneously:

- $ a_n = \max(a_1, a_2, \ldots, a_n) $ ,
- $ b_n = \max(b_1, b_2, \ldots, b_n) $ .

Here $ \max(c_1, c_2, \ldots, c_k) $ denotes the maximum number among $ c_1, c_2, \ldots, c_k $ . For example, $ \max(3, 5, 4) = 5 $ , $ \max(1, 7, 7) = 7 $ , $ \max(6, 2) = 6 $ .

## 说明/提示

In the first test case, you can swap the numbers $ a_3 $ and $ b_3 $ , after which the array $ a $ becomes equal to $ [7, 9, 9] $ , and the array $ b $ becomes equal to $ [7, 6, 7] $ , and both conditions are met.

In the second test case, it can be proved that it is impossible to satisfy both conditions.

In the third test case, you can swap the numbers $ a_1 $ and $ b_1 $ , after which the array $ a $ becomes equal to $ [99, 99] $ , and the array $ b $ becomes equal to $ [100, 100] $ , and both conditions are satisfied.

In fifth test case, you can swap $ a_7 $ and $ b_7 $ , $ a_8 $ and $ b_8 $ , $ a_9 $ and $ b_9 $ , after which the array $ a $ becomes equal to $ [1, 2, 3, 4, 5, 6, 6, 6, 6] $ , and the array $ b $ becomes equal to $ [9, 9, 9, 9, 9, 9, 7, 8, 9] $ , and both conditions are satisfied.

## 样例 #1

### 输入

```
7
3
7 9 7
7 6 9
4
10 10 15 15
10 16 15 15
2
100 99
99 100
1
1
1
9
1 2 3 4 5 6 7 8 9
9 9 9 9 9 9 6 6 6
7
1 1 2 2 1 1 2
1 2 1 2 1 2 1
2
30 4
5 30```

### 输出

```
Yes
No
Yes
Yes
Yes
No
No```

# AI分析结果

### 题目内容
# 引人注目的事物

## 题目描述
给定两个数组 $a_1, a_2, \ldots, a_n$ 和 $b_1, b_2, \ldots, b_n$ 。
在一次操作中，你可以从 $1$ 到 $n$ 中选择任意整数 $i$ ，并交换数字 $a_i$ 和 $b_i$ 。
判断在经过任意（可能为零）次操作后，以下两个条件是否能同时满足：
 - $a_n = \max(a_1, a_2, \ldots, a_n)$ ，
 - $b_n = \max(b_1, b_2, \ldots, b_n)$ 。
这里 $\max(c_1, c_2, \ldots, c_k)$ 表示 $c_1, c_2, \ldots, c_k$ 中的最大数。例如，$\max(3, 5, 4) = 5$ ，$\max(1, 7, 7) = 7$ ，$\max(6, 2) = 6$ 。

## 说明/提示
在第一个测试用例中，你可以交换 $a_3$ 和 $b_3$ ，之后数组 $a$ 变为 $[7, 9, 9]$ ，数组 $b$ 变为 $[7, 6, 7]$ ，两个条件都满足。
在第二个测试用例中，可以证明无法同时满足这两个条件。
在第三个测试用例中，你可以交换 $a_1$ 和 $b_1$ ，之后数组 $a$ 变为 $[99, 99]$ ，数组 $b$ 变为 $[100, 100]$ ，两个条件都满足。
在第五个测试用例中，你可以交换 $a_7$ 和 $b_7$ ，$a_8$ 和 $b_8$ ，$a_9$ 和 $b_9$ ，之后数组 $a$ 变为 $[1, 2, 3, 4, 5, 6, 6, 6, 6]$ ，数组 $b$ 变为 $[9, 9, 9, 9, 9, 9, 7, 8, 9]$ ，两个条件都满足。

## 样例 #1
### 输入
```
7
3
7 9 7
7 6 9
4
10 10 15 15
10 16 15 15
2
100 99
99 100
1
1
1
9
1 2 3 4 5 6 7 8 9
9 9 9 9 9 9 6 6 6
7
1 1 2 2 1 1 2
1 2 1 2 1 2 1
2
30 4
5 30
```
### 输出
```
Yes
No
Yes
Yes
Yes
No
No
```
• 算法分类：数学
• 综合分析与结论：由于暂无题解，无法进行题解间的对比分析。通用思路可以考虑通过分析数组元素之间的大小关系来判断是否能满足两个条件。难点在于如何高效地判断经过交换操作后能否达成目标状态。
• 通用建议与扩展思路：可以尝试遍历数组，记录每个数组中的最大值及其位置，分析交换操作对最终状态的影响。对于同类型题目，通常是围绕数组元素操作及条件判断，类似套路是通过分析元素大小关系和操作规则来寻找解题方法。
• 洛谷相似题目推荐：
  - P1085 [NOIP2004 普及组] 不高兴的津津，涉及对数据的分析判断。
  - P1909 买铅笔，通过对不同方案的计算与比较来求解。
  - P1425 小鱼的游泳时间，对时间数据进行分析和计算。 

---
处理用时：22.80秒