# 题目信息

# Beaver's Calculator 1.0

## 题目描述

The Smart Beaver from ABBYY has once again surprised us! He has developed a new calculating device, which he called the "Beaver's Calculator $ 1.0 $ ". It is very peculiar and it is planned to be used in a variety of scientific problems.

To test it, the Smart Beaver invited $ n $ scientists, numbered from $ 1 $ to $ n $ . The $ i $ -th scientist brought $ k_{i} $ calculating problems for the device developed by the Smart Beaver from ABBYY. The problems of the $ i $ -th scientist are numbered from $ 1 $ to $ k_{i} $ , and they must be calculated sequentially in the described order, since calculating each problem heavily depends on the results of calculating of the previous ones.

Each problem of each of the $ n $ scientists is described by one integer $ a_{i,j} $ , where $ i $ ( $ 1<=i<=n $ ) is the number of the scientist, $ j $ ( $ 1<=j<=k_{i} $ ) is the number of the problem, and $ a_{i,j} $ is the number of resource units the calculating device needs to solve this problem.

The calculating device that is developed by the Smart Beaver is pretty unusual. It solves problems sequentially, one after another. After some problem is solved and before the next one is considered, the calculating device allocates or frees resources.

The most expensive operation for the calculating device is freeing resources, which works much slower than allocating them. It is therefore desirable that each next problem for the calculating device requires no less resources than the previous one.

You are given the information about the problems the scientists offered for the testing. You need to arrange these problems in such an order that the number of adjacent "bad" pairs of problems in this list is minimum possible. We will call two consecutive problems in this list a "bad pair" if the problem that is performed first requires more resources than the one that goes after it. Do not forget that the problems of the same scientist must be solved in a fixed order.

## 说明/提示

In the first sample $ n=2 $ , $ k_{1}=2 $ , $ a_{1,1}=1 $ , $ a_{1,2}=2 $ , $ k_{2}=2 $ , $ a_{2,1}=3 $ , $ a_{2,2}=4 $ . We've got two scientists, each of them has two calculating problems. The problems of the first scientist require $ 1 $ and $ 2 $ resource units, the problems of the second one require $ 3 $ and $ 4 $ resource units. Let's list all possible variants of the calculating order (each problem is characterized only by the number of resource units it requires): $ (1,2,3,4) $ , $ (1,3,2,4) $ , $ (3,1,2,4) $ , $ (1,3,4,2) $ , $ (3,4,1,2) $ , $ (3,1,4,2) $ .

Sequence of problems $ (1,3,2,4) $ has one "bad" pair ( $ 3 $ and $ 2 $ ), $ (3,1,4,2) $ has two "bad" pairs ( $ 3 $ and $ 1 $ , $ 4 $ and $ 2 $ ), and $ (1,2,3,4) $ has no "bad" pairs.

## 样例 #1

### 输入

```
2
2 1 1 1 10
2 3 1 1 10
```

### 输出

```
0
1 1
2 1
3 2
4 2
```

## 样例 #2

### 输入

```
2
3 10 2 3 1000
3 100 1 999 1000
```

### 输出

```
2
10 1
23 1
49 1
100 2
99 2
98 2
```

# AI分析结果

### 题目内容
# 海狸计算器1.0

## 题目描述
来自ABBYY的聪明海狸又一次惊艳到了我们！他开发了一种新的计算设备，称之为“海狸计算器 1.0”。这个设备非常独特，计划用于各种科学问题。

为了测试它，聪明海狸邀请了n位科学家，编号从1到n。第i位科学家带来了$k_{i}$个由来自ABBYY的聪明海狸开发的设备要计算的问题。第i位科学家的问题编号从1到$k_{i}$，并且必须按照描述的顺序依次计算，因为计算每个问题在很大程度上依赖于前一个问题的计算结果。

n位科学家中每位科学家的每个问题都由一个整数$a_{i,j}$描述，其中i（$1 \leq i \leq n$）是科学家的编号，j（$1 \leq j \leq k_{i}$）是问题的编号，$a_{i,j}$是计算设备解决这个问题所需的资源单元数量。

聪明海狸开发的计算设备非常不寻常。它依次解决问题，一个接一个。在某个问题解决后，下一个问题考虑之前，计算设备分配或释放资源。

对于计算设备来说，最昂贵的操作是释放资源，这比分配资源要慢得多。因此，希望计算设备的每个后续问题所需的资源不少于前一个问题。

给定科学家提供用于测试的问题信息。你需要以这样一种顺序排列这些问题，使得此列表中相邻的“坏”问题对的数量尽可能少。如果在此列表中，先执行的问题比后执行的问题需要更多的资源，我们将这两个连续的问题称为“坏对”。不要忘记，同一科学家的问题必须按照固定顺序解决。

## 说明/提示
在第一个样例中，$n = 2$，$k_{1} = 2$，$a_{1,1} = 1$，$a_{1,2} = 2$，$k_{2} = 2$，$a_{2,1} = 3$，$a_{2,2} = 4$。我们有两位科学家，每位都有两个计算问题。第一位科学家的问题需要1和2个资源单元，第二位科学家的问题需要3和4个资源单元。让我们列出所有可能的计算顺序（每个问题仅由其所需的资源单元数量来表征）：$(1,2,3,4)$，$(1,3,2,4)$，$(3,1,2,4)$，$(1,3,4,2)$，$(3,4,1,2)$，$(3,1,4,2)$。

问题序列$(1,3,2,4)$有一个“坏”对（3和2），$(3,1,4,2)$有两个“坏”对（3和1，4和2），而$(1,2,3,4)$没有“坏”对。

## 样例 #1
### 输入
```
2
2 1 1 1 10
2 3 1 1 10
```
### 输出
```
0
1 1
2 1
3 2
4 2
```

## 样例 #2
### 输入
```
2
3 10 2 3 1000
3 100 1 999 1000
```
### 输出
```
2
10 1
23 1
49 1
100 2
99 2
98 2
```

### 算法分类
贪心

### 题解综合分析与结论
两题解核心思路均基于贪心策略。_Weslie_ 将序列分成不下降子段，利用优先队列维护，通过取反元素值放入pair简化操作；Confringo 证明答案为取走单独一个序列需要连续子段最小值的最大值，通过暴力计算实现，根据数据范围不同选择不同保存方式。两题解思路清晰，_Weslie_ 代码实现更直接，Confringo 对思路证明阐述详细。但两题解代码可读性一般，均未对算法进行深度优化，整体质量均未达到4星。

### 通用建议与扩展思路
通用建议：优化代码结构，提高可读性，如增加注释、合理命名变量等。对于大规模数据，可考虑进一步优化算法，如尝试更高效的数据结构或优化计算过程。
扩展思路：此类问题可拓展到多序列合并优化场景，如多个有序序列合并时，如何通过贪心策略最小化某些代价。类似算法套路可关注序列合并中的贪心选择，以及如何确定最优解的上下界。

### 推荐洛谷题目
1. P1094 [纪念品分组](https://www.luogu.com.cn/problem/P1094)
2. P1223 排队接水
3. P1199 [三国游戏](https://www.luogu.com.cn/problem/P1199) 

---
处理用时：41.73秒