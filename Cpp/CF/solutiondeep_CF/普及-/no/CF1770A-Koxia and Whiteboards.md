# 题目信息

# Koxia and Whiteboards

## 题目描述

Kiyora has $ n $ whiteboards numbered from $ 1 $ to $ n $ . Initially, the $ i $ -th whiteboard has the integer $ a_i $ written on it.

Koxia performs $ m $ operations. The $ j $ -th operation is to choose one of the whiteboards and change the integer written on it to $ b_j $ .

Find the maximum possible sum of integers written on the whiteboards after performing all $ m $ operations.

## 说明/提示

In the first test case, Koxia can perform the operations as follows:

1. Choose the $ 1 $ -st whiteboard and rewrite the integer written on it to $ b_1=4 $ .
2. Choose the $ 2 $ -nd whiteboard and rewrite to $ b_2=5 $ .

After performing all operations, the numbers on the three whiteboards are $ 4 $ , $ 5 $ and $ 3 $ respectively, and their sum is $ 12 $ . It can be proven that this is the maximum possible sum achievable.

In the second test case, Koxia can perform the operations as follows:

1. Choose the $ 2 $ -nd whiteboard and rewrite to $ b_1=3 $ .
2. Choose the $ 1 $ -st whiteboard and rewrite to $ b_2=4 $ .
3. Choose the $ 2 $ -nd whiteboard and rewrite to $ b_3=5 $ .

The sum is $ 4 + 5 = 9 $ . It can be proven that this is the maximum possible sum achievable.

## 样例 #1

### 输入

```
4
3 2
1 2 3
4 5
2 3
1 2
3 4 5
1 1
100
1
5 3
1 1 1 1 1
1000000000 1000000000 1000000000```

### 输出

```
12
9
1
3000000002```

# AI分析结果

### 题目内容
# 科夏与白板

## 题目描述
科夏有 $n$ 块编号从 $1$ 到 $n$ 的白板。最初，第 $i$ 块白板上写有整数 $a_i$ 。

科夏进行 $m$ 次操作。第 $j$ 次操作是选择其中一块白板，并将上面写的整数改为 $b_j$ 。

求进行完所有 $m$ 次操作后，白板上整数的最大可能和。

## 说明/提示
在第一个测试用例中，科夏可以按如下方式进行操作：
1. 选择第 $1$ 块白板，并将上面写的整数重写为 $b_1 = 4$ 。
2. 选择第 $2$ 块白板，并重写为 $b_2 = 5$ 。

进行完所有操作后，三块白板上的数字分别为 $4$、$5$ 和 $3$ ，它们的和为 $12$ 。可以证明这是可达到的最大可能和。

在第二个测试用例中，科夏可以按如下方式进行操作：
1. 选择第 $2$ 块白板，并重写为 $b_1 = 3$ 。
2. 选择第 $1$ 块白板，并重写为 $b_2 = 4$ 。
3. 选择第 $2$ 块白板，并重写为 $b_3 = 5$ 。

总和为 $4 + 5 = 9$ 。可以证明这是可达到的最大可能和。

## 样例 #1
### 输入
```
4
3 2
1 2 3
4 5
2 3
1 2
3 4 5
1 1
100
1
5 3
1 1 1 1 1
1000000000 1000000000 1000000000
```
### 输出
```
12
9
1
3000000002
```

### 算法分类
贪心

### 综合分析与结论
题目要求通过 $m$ 次操作，将白板上的数字替换为给定的 $b_j$ ，以获取最大的数字总和。核心思路是每次操作时都选择当前白板上最小的数字进行替换，这样能保证总和最大，属于贪心策略。由于暂无题解，以下给出通用建议与扩展思路。
通用建议：实现时可以先将白板上初始的数字 $a_i$ 存储起来，对每次操作的 $b_j$ 进行处理，每次从当前白板数字集合中找出最小值并替换为 $b_j$ ，最后计算总和。
扩展思路：同类型题可能会增加白板或操作的限制条件，比如限制只能对特定编号的白板操作，或者操作有先后顺序要求等。类似算法套路在涉及资源分配、最值求解等场景下都可能用到贪心策略，例如在一些任务调度问题中，每次选择耗时最短的任务先执行以最大化效率等。

### 洛谷推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序实现贪心策略，求解最大收益问题。
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：运用贪心思想来确定游戏中的最优选择。
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：利用贪心算法对纪念品进行分组以满足特定条件。 

---
处理用时：22.25秒