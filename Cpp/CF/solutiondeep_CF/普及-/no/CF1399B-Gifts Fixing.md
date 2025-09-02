# 题目信息

# Gifts Fixing

## 题目描述

You have $ n $ gifts and you want to give all of them to children. Of course, you don't want to offend anyone, so all gifts should be equal between each other. The $ i $ -th gift consists of $ a_i $ candies and $ b_i $ oranges.

During one move, you can choose some gift $ 1 \le i \le n $ and do one of the following operations:

- eat exactly one candy from this gift (decrease $ a_i $ by one);
- eat exactly one orange from this gift (decrease $ b_i $ by one);
- eat exactly one candy and exactly one orange from this gift (decrease both $ a_i $ and $ b_i $ by one).

Of course, you can not eat a candy or orange if it's not present in the gift (so neither $ a_i $ nor $ b_i $ can become less than zero).

As said above, all gifts should be equal. This means that after some sequence of moves the following two conditions should be satisfied: $ a_1 = a_2 = \dots = a_n $ and $ b_1 = b_2 = \dots       = b_n $ (and $ a_i $ equals $ b_i $ is not necessary).

Your task is to find the minimum number of moves required to equalize all the given gifts.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, we can perform the following sequence of moves:

- choose the first gift and eat one orange from it, so $ a         = [3, 5, 6] $ and $ b = [2, 2, 3] $ ;
- choose the second gift and eat one candy from it, so $ a =         [3, 4, 6] $ and $ b = [2, 2, 3] $ ;
- choose the second gift and eat one candy from it, so $ a =         [3, 3, 6] $ and $ b = [2, 2, 3] $ ;
- choose the third gift and eat one candy and one orange from it, so $ a = [3, 3, 5] $ and $ b = [2, 2, 2] $ ;
- choose the third gift and eat one candy from it, so $ a =         [3, 3, 4] $ and $ b = [2, 2, 2] $ ;
- choose the third gift and eat one candy from it, so $ a =         [3, 3, 3] $ and $ b = [2, 2, 2] $ .

## 样例 #1

### 输入

```
5
3
3 5 6
3 2 3
5
1 2 3 4 5
5 4 3 2 1
3
1 1 1
2 2 2
6
1 1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1 1
3
10 12 8
7 5 4```

### 输出

```
6
16
0
4999999995
7```

# AI分析结果

### 题目内容
#### Gifts Fixing
1. **题目描述**：你有$n$个礼物，想把它们全部送给孩子们。为避免冒犯他人，所有礼物应保持一致。第$i$个礼物包含$a_i$颗糖果和$b_i$个橙子。
在一次操作中，你可以选择某个礼物$1 \leq i \leq n$，并执行以下操作之一：
    - 从该礼物中吃掉恰好一颗糖果（将$a_i$减一）；
    - 从该礼物中吃掉恰好一个橙子（将$b_i$减一）；
    - 从该礼物中吃掉恰好一颗糖果和恰好一个橙子（将$a_i$和$b_i$都减一）。
当然，如果礼物中没有糖果或橙子，则不能吃（所以$a_i$和$b_i$都不能小于零）。
如前所述，所有礼物应保持一致。这意味着在经过一系列操作后，应满足以下两个条件：$a_1 = a_2 = \cdots = a_n$且$b_1 = b_2 = \cdots = b_n$（$a_i$等于$b_i$并非必要条件）。
你的任务是找出使所有给定礼物一致所需的最少操作次数。
你需要回答$t$个独立的测试用例。
2. **说明/提示**：在示例的第一个测试用例中，我们可以执行以下一系列操作：
    - 选择第一个礼物并从其中吃掉一个橙子，此时$a = [3, 5, 6]$，$b = [2, 2, 3]$；
    - 选择第二个礼物并从其中吃掉一颗糖果，此时$a = [3, 4, 6]$，$b = [2, 2, 3]$；
    - 选择第二个礼物并从其中吃掉一颗糖果，此时$a = [3, 3, 6]$，$b = [2, 2, 3]$；
    - 选择第三个礼物并从其中吃掉一颗糖果和一个橙子，此时$a = [3, 3, 5]$，$b = [2, 2, 2]$；
    - 选择第三个礼物并从其中吃掉一颗糖果，此时$a = [3, 3, 4]$，$b = [2, 2, 2]$；
    - 选择第三个礼物并从其中吃掉一颗糖果，此时$a = [3, 3, 3]$，$b = [2, 2, 2]$。
3. **样例 #1**
    - **输入**：
```
5
3
3 5 6
3 2 3
5
1 2 3 4 5
5 4 3 2 1
3
1 1 1
2 2 2
6
1 1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1 1
3
10 12 8
7 5 4
```
    - **输出**：
```
6
16
0
4999999995
7
```
### 算法分类
贪心
### 题解综合分析与结论
所有题解的核心思路均为贪心策略，即要使操作次数最少，应将数组$a$中的所有元素变为数组$a$的最小值，将数组$b$中的所有元素变为数组$b$的最小值。对于每个礼物，计算$a_i$与数组$a$最小值的差值$x$，$b_i$与数组$b$最小值的差值$y$，操作次数为$\max(x, y)$，最后将所有礼物的操作次数累加得到总操作次数。各题解在思路表述、代码实现细节（如变量命名、输入输出方式、是否使用宏定义等）上略有不同，但本质算法相同，整体质量较为接近，均未展现出特别突出的优化或独特的技巧，因此所有题解均未达到4星。
### 通用建议与扩展思路
通用建议：在解决此类问题时，要善于分析操作的性质和目标状态，通过贪心策略找到最优解。代码实现时注意变量类型的选择，本题答案可能超出int范围，需使用long long类型。
扩展思路：类似题目可能会改变操作类型、操作限制或目标状态，例如改变操作规则，允许增加元素；或者改变目标状态，要求$a_i$和$b_i$最终相等。解决这类扩展问题时，需重新分析问题性质，调整贪心策略。
### 洛谷相似题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略解决合并物品的最小代价问题，与本题贪心选择操作方式以达到最小操作次数类似。
2. [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：运用贪心思想在游戏规则下选择最优策略，锻炼贪心算法的应用能力。
3. [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过贪心排序解决双属性任务安排的最优解问题，与本题对两个数组进行分析处理有相似之处。 

---
处理用时：42.85秒