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

# 题解

## 作者：cpchenpi (赞：4)

题意简述：

有 $n$ 个容量为 $a_i$ 的背包，$m$ 个体积为 $2^{b_i}$ 的物品。

把物品装入背包，求装入物品个数之和的最大值。

首先给出我的做法：反悔贪心。

从大到小考虑物品，若有剩余空间足够的背包，就将物品放入其中。否则，若已经放入过一个更大的物品，就用当前物品替代最大的一个。

这个做法乍一看漏洞百出，实际上可以证明正确性。首先，易知一定存在一种最优方案选择的是最小的一些物品，而显然我们的做法最终选择的也一定是一些最小的物品，因此只要证明选择的数量相同。

假设物品 $y$ 没有选，而实际上可以选。首先它一定被选择过，因为我们的做法中，有放得下的背包的物品都会被选到；那么它一定被 $x$ 反悔替代了。我们只要证明，在此时，不可能存在一种方案让 $x$ 和 $y$ 同时被选中，即可证明不可能存在更优的一种方案。

需要反悔，说明当前所有背包的空闲空间都小于 $x$。而当前已经选择的所有物品均大于等于 $x$，且由于是 $2$ 的次幂，体积是 $x$ 的整数倍。若存在一种重排方案，使一个背包能腾出不小于 $x$ 的空间，则至少有一个背包的剩余空间减小了。然而由于物品的体积是 $x$ 的整数倍，减小只能以 $x$ 为单位减小；但所有背包的空间剩余空间都小于 $x$，并不存在这样一个背包。证毕。

---

