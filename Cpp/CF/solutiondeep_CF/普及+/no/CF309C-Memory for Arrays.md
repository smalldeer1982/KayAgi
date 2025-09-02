# 题目信息

# Memory for Arrays

## 题目描述

You get to work and turn on the computer. You start coding and give little thought to the RAM role in the whole process. In this problem your task is to solve one of the problems you encounter in your computer routine.

We'll consider the RAM as a sequence of cells that can contain data. Some cells already contain some data, some are empty. The empty cells form the so-called memory clusters. Thus, a memory cluster is a sequence of some consecutive empty memory cells.

You have exactly $ n $ memory clusters, the $ i $ -th cluster consists of $ a_{i} $ cells. You need to find memory for $ m $ arrays in your program. The $ j $ -th array takes $ 2^{b_{j}} $ consecutive memory cells. There possibly isn't enough memory for all $ m $ arrays, so your task is to determine what maximum number of arrays can be located in the available memory clusters. Of course, the arrays cannot be divided between the memory clusters. Also, no cell can belong to two arrays.

## 说明/提示

In the first example you are given memory clusters with sizes 8, 4, 3, 2, 2 and arrays with sizes 8, 4, 4. There are few ways to obtain an answer equals 2: you can locate array with size 8 to the cluster with size 8, and one of the arrays with size 4 to the cluster with size 4. Another way is to locate two arrays with size 4 to the one cluster with size 8.

In the second example you are given 10 memory clusters with size 1 and 6 arrays with size 1. You can choose any 6 clusters and locate all given arrays to them.

## 样例 #1

### 输入

```
5 3
8 4 3 2 2
3 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 6
1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0
```

### 输出

```
6
```

# AI分析结果

### 题目内容
# 数组的内存分配

## 题目描述
你开始工作并打开电脑。你开始编码，很少思考随机存取存储器（RAM）在整个过程中的作用。在这个问题中，你的任务是解决你在日常计算机操作中遇到的问题之一。

我们将把 RAM 看作是一系列可以存储数据的单元。一些单元已经包含了一些数据，一些是空的。空单元形成了所谓的内存簇。因此，一个内存簇是一些连续的空内存单元序列。

你恰好有 $n$ 个内存簇，第 $i$ 个簇由 $a_{i}$ 个单元组成。你需要在你的程序中为 $m$ 个数组找到内存空间。第 $j$ 个数组需要 $2^{b_{j}}$ 个连续的内存单元。可能没有足够的内存来存放所有 $m$ 个数组，所以你的任务是确定在可用的内存簇中最多可以存放多少个数组。当然，数组不能在内存簇之间分割。此外，任何一个单元都不能属于两个数组。

## 说明/提示
在第一个例子中，你得到的内存簇大小为 8、4、3、2、2，数组大小为 8、4、4。有几种方法可以得到答案为 2：你可以将大小为 8 的数组放入大小为 8 的簇中，将大小为 4 的数组之一放入大小为 4 的簇中。另一种方法是将两个大小为 4 的数组放入大小为 8 的一个簇中。

在第二个例子中，你得到 10 个大小为 1 的内存簇和 6 个大小为 1 的数组。你可以选择任意 6 个簇并将所有给定的数组放入其中。

## 样例 #1
### 输入
```
5 3
8 4 3 2 2
3 2 2
```
### 输出
```
2
```

## 样例 #2
### 输入
```
10 6
1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0
```
### 输出
```
6
```

### 算法分类
贪心

### 综合分析与结论
目前仅一题解，该题解使用反悔贪心算法解决问题。思路是将问题类比为有 $n$ 个容量为 $a_i$ 的背包和 $m$ 个体积为 $2^{b_i}$ 的物品，求能装入物品的最大数量。从大到小考虑物品，若有足够空间的背包则放入，否则若已放入更大物品，就用当前物品替代最大的一个。难点在于证明该贪心策略的正确性，题解通过假设存在更优方案并推出矛盾来完成证明。

### 所选的题解
 - **星级**：4 星
 - **关键亮点**：采用反悔贪心算法，并严谨证明了算法的正确性。
 - **个人心得**：无

### 重点代码及核心实现思想
题解未提供代码。核心实现思想为：先对背包容量数组 $a$ 和物品体积数组 $2^{b}$ 进行处理，从大到小遍历物品体积数组，对于每个物品体积，在背包容量数组中寻找能容纳它的最小背包容量，若找到则将该背包标记为已用，物品计数加一；若找不到且已存在放入背包的物品，则用当前物品替换已放入的最大物品（前提是当前物品小于已放入的最大物品）。通过这种反悔贪心策略实现对问题的求解。 

---
处理用时：29.76秒