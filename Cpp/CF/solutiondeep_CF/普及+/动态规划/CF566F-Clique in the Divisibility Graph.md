# 题目信息

# Clique in the Divisibility Graph

## 题目描述

As you must know, the maximum clique problem in an arbitrary graph is $ NP $ -hard. Nevertheless, for some graphs of specific kinds it can be solved effectively.

Just in case, let us remind you that a clique in a non-directed graph is a subset of the vertices of a graph, such that any two vertices of this subset are connected by an edge. In particular, an empty set of vertexes and a set consisting of a single vertex, are cliques.

Let's define a divisibility graph for a set of positive integers $ A={a_{1},a_{2},...,a_{n}} $ as follows. The vertices of the given graph are numbers from set $ A $ , and two numbers $ a_{i} $ and $ a_{j} $ ( $ i≠j $ ) are connected by an edge if and only if either $ a_{i} $ is divisible by $ a_{j} $ , or $ a_{j} $ is divisible by $ a_{i} $ .

You are given a set of non-negative integers $ A $ . Determine the size of a maximum clique in a divisibility graph for set $ A $ .

## 说明/提示

In the first sample test a clique of size 3 is, for example, a subset of vertexes $ {3,6,18} $ . A clique of a larger size doesn't exist in this graph.

## 样例 #1

### 输入

```
8
3 4 6 8 10 18 21 24
```

### 输出

```
3
```

# AI分析结果

### 题目内容重写
# 可除性图中的团

## 题目描述

众所周知，在任意图中求解最大团问题是 $NP$ 难问题。然而，对于某些特定类型的图，它可以被有效解决。

为了确保理解，我们提醒你，无向图中的团是指图的一个顶点子集，使得该子集中的任意两个顶点之间都有一条边相连。特别地，空集和仅包含一个顶点的集合也是团。

对于一个正整数集合 $A={a_{1},a_{2},...,a_{n}}$，我们定义其可除性图如下：图的顶点是集合 $A$ 中的数，两个数 $a_{i}$ 和 $a_{j}$（$i≠j$）之间有一条边，当且仅当 $a_{i}$ 能被 $a_{j}$ 整除，或者 $a_{j}$ 能被 $a_{i}$ 整除。

给定一个非负整数集合 $A$，求其可除性图中的最大团的大小。

## 说明/提示

在第一个样例中，大小为 3 的团是顶点子集 $ {3,6,18} $。该图中不存在更大的团。

## 样例 #1

### 输入

```
8
3 4 6 8 10 18 21 24
```

### 输出

```
3
```

### 题解分析与结论

#### 综合分析与结论
本题的核心是通过动态规划（DP）来解决最大团问题。所有题解都采用了类似的思路：利用数的可除性关系，通过 DP 来更新每个数的最大团大小。具体来说，每个数的最大团大小由其所有因数的最大团大小决定，然后通过更新其倍数的最大团大小来传递信息。

#### 最优关键思路或技巧
1. **动态规划**：定义 $dp[i]$ 为以数字 $i$ 结尾的最大团大小，通过更新其倍数的 $dp$ 值来传递信息。
2. **调和级数优化**：通过调和级数的性质，将复杂度优化到 $O(n \log n)$，避免了 $O(n^2)$ 的复杂度。
3. **预处理与排序**：通过预处理和排序，减少重复计算，提高效率。

#### 可拓展之处
1. **类似问题**：类似的可除性关系可以应用于其他图论问题，如最大独立集、最小路径覆盖等。
2. **算法套路**：这种通过数的倍数关系进行 DP 更新的方法，可以推广到其他需要处理数的倍数关系的题目中。

#### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)

### 高星题解展示

#### 题解1：作者：cenxinyang12 (赞：7)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，利用调和级数优化复杂度。
- **核心代码**：
```cpp
cin>>x;f[x]++;
for(i=2;i*x<=1000000;i++)
    f[i*x]=max(f[i*x],f[x]);
ma=max(ma,f[x]);
```
- **个人心得**：通过调和级数优化，避免了 $O(n^2)$ 的复杂度，大大提高了效率。

#### 题解2：作者：slzx2021zjx (赞：5)
- **星级**：4星
- **关键亮点**：代码简洁，思路明确，利用 DP 更新倍数的最大团大小。
- **核心代码**：
```cpp
dp[x]++;
for(int j=2;j*x<=maxn;j++){
    dp[j*x]=max(dp[j*x],dp[x]);
}
Max=max(Max,dp[x]);
```
- **个人心得**：通过 DP 更新倍数的最大团大小，避免了重复计算，提高了效率。

#### 题解3：作者：Up_Xu (赞：4)
- **星级**：4星
- **关键亮点**：利用筛选法优化 DP 更新，代码清晰。
- **核心代码**：
```cpp
dp[x]++;
while(j+x<=Max){
    j+=x;
    if(f[j]==1)
        dp[j]=max(dp[j],dp[x]);
}
sum=max(dp[x],sum);
```
- **个人心得**：通过筛选法优化 DP 更新，减少了不必要的计算，提高了效率。

---
处理用时：32.61秒