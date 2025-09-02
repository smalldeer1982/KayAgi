# 题目信息

# Jellyfish and Game

## 题目描述

Jellyfish has $ n $ green apples with values $ a_1, a_2, \dots, a_n $ and Gellyfish has $ m $ green apples with values $ b_1,b_2,\ldots,b_m $ .

They will play a game with $ k $ rounds. For $ i=1,2,\ldots,k $ in this order, they will perform the following actions:

- If $ i $ is odd, Jellyfish can choose to swap one of her apples with one of Gellyfish's apples or do nothing.
- If $ i $ is even, Gellyfish can choose to swap one of his apples with one of Jellyfish's apples or do nothing.

Both players want to maximize the sum of the values of their apples.

Since you are one of the smartest people in the world, Jellyfish wants you to tell her the final sum of the value of her apples after all $ k $ rounds of the game. Assume that both Jellyfish and Gellyfish play optimally to maximize the sum of values of their apples.

## 说明/提示

In the first test case, Jellyfish will swap the apple of value $ 1 $ and $ 4 $ .

In the second test case, both players will swap the two apples $ 10,000 $ times.

In the fourth test case, Jellyfish will do nothing.

## 样例 #1

### 输入

```
4
2 2 1
1 2
3 4
1 1 10000
1
2
4 5 11037
1 1 4 5
1 9 1 9 8
1 1 1
2
1```

### 输出

```
6
1
19
2```

# AI分析结果

【题目内容】
# 水母和游戏

## 题目描述

水母有 $ n $ 个绿苹果，价值分别为 $ a_1, a_2, \dots, a_n $，而海蜇有 $ m $ 个绿苹果，价值分别为 $ b_1, b_2, \dots, b_m $。

他们将进行 $ k $ 轮游戏。在第 $ i=1,2,\ldots,k $ 轮中，按顺序执行以下操作：

- 如果 $ i $ 是奇数，水母可以选择用自己的一个苹果与海蜇的一个苹果交换，或者不进行任何操作。
- 如果 $ i $ 是偶数，海蜇可以选择用自己的一个苹果与水母的一个苹果交换，或者不进行任何操作。

双方都希望最大化自己苹果的价值总和。

由于你是世界上最聪明的人之一，水母希望你告诉她，在所有 $ k $ 轮游戏结束后，她手中苹果的价值总和。假设双方都采取最优策略来最大化自己苹果的价值总和。

## 说明/提示

在第一个测试用例中，水母将交换价值为 $ 1 $ 和 $ 4 $ 的苹果。

在第二个测试用例中，双方将交换两个苹果 $ 10,000 $ 次。

在第四个测试用例中，水母将不进行任何操作。

## 样例 #1

### 输入

```
4
2 2 1
1 2
3 4
1 1 10000
1
2
4 5 11037
1 1 4 5
1 9 1 9 8
1 1 1
2
1```

### 输出

```
6
1
19
2```

【算法分类】
贪心

【分析与结论】
本题的核心在于模拟双方在每一轮中的最优交换策略。由于双方都希望最大化自己苹果的价值总和，因此在每一轮中，当前操作的一方会选择对自己最有利的交换策略。

由于题目中涉及到多轮交换，且每一轮的策略依赖于前一轮的结果，因此直接模拟每一轮的交换过程可能会导致时间复杂度过高。为了优化，我们可以通过分析发现，经过一定轮数后，双方的交换策略会趋于稳定，即不再进行交换。因此，我们可以通过判断 $ k $ 的奇偶性来简化计算。

【通用建议与扩展思路】
1. **贪心策略**：在每一轮中，当前操作的一方会选择对自己最有利的交换策略。这种策略可以通过排序双方的苹果价值来实现。
2. **优化轮数**：由于经过一定轮数后，交换策略会趋于稳定，因此可以通过判断 $ k $ 的奇偶性来简化计算，避免不必要的模拟。
3. **边界情况**：需要注意 $ k=0 $ 或 $ k=1 $ 的特殊情况，确保程序在这些情况下也能正确运行。

【推荐题目】
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：18.48秒