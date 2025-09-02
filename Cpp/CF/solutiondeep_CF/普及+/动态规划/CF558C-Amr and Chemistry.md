# 题目信息

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 5 6
```

### 输出

```
5```

# AI分析结果

### 题目翻译

Amr 喜欢化学，尤其是做实验。他正在准备一个新的有趣实验。

Amr 有 $n$ 种不同的化学物质。每种化学物质 $i$ 的初始体积为 $a_{i}$ 升。为了这个实验，Amr 需要将所有化学物质混合在一起，但首先所有化学物质的体积必须相等。因此，他的任务是使所有化学物质的体积相等。

为此，Amr 可以进行两种操作：

- 选择某个化学物质 $i$ 并将其当前体积加倍，新的体积为 $2a_{i}$。
- 选择某个化学物质 $i$ 并将其体积除以二（整数除法），新的体积为 $\lfloor \frac{a_{i}}{2} \rfloor$。

假设每种化学物质都装在一个无限体积的容器中。现在 Amr 想知道，使所有化学物质体积相等所需的最少操作次数是多少？

### 说明/提示

在第一个样例中，最优解是将第二个化学物质的体积除以二，并将第三个化学物质的体积乘以二，使所有体积都变为 $4$。

在第二个样例中，最优解是将第一个化学物质的体积除以二，并将第二个和第三个化学物质的体积除以二两次，使所有体积都变为 $1$。

### 样例 #1

#### 输入

```
3
4 8 2
```

#### 输出

```
2
```

### 样例 #2

#### 输入

```
3
3 5 6
```

#### 输出

```
5
```

---

### 题解分析与结论

该题的核心思路是将每个化学物质的体积通过乘2或除2操作转化为相同的目标体积，并计算所需的最少操作次数。多个题解都采用了将问题转化为树形结构或二进制表示的方法，通过遍历或动态规划来求解最优解。

#### 最优关键思路与技巧

1. **树形结构建模**：将每个化学物质的体积通过乘2和除2操作转化为树形结构，节点表示可能的体积，边表示操作。通过遍历树结构，找到所有化学物质都能到达的公共节点，并计算最小操作次数。
2. **二进制表示与位运算**：将体积的乘2和除2操作转化为二进制位运算，通过位操作来快速计算每个化学物质到达目标体积所需的操作次数。
3. **换根动态规划**：通过动态规划的方法，从根节点开始计算每个节点的操作次数，并通过换根操作来优化计算过程。

#### 可拓展之处

该题的思路可以拓展到其他需要通过操作将多个元素转化为相同状态的题目，如通过加减操作使数组元素相等，或通过位操作使二进制数相等。

#### 推荐题目

1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---

### 所选高星题解

#### 题解1：IkunTeddy (4星)

**关键亮点**：
- 使用01-Trie树结构建模，通过树形结构计算操作次数。
- 通过换根动态规划优化计算过程。

**核心代码**：
```cpp
void dfs(int u){
    ans=min(ans,dp[u]);
    for(int i=0;i<1;i++){
        int v=tree[u].son[i];
        if(!v)continue;
        dp[v]=dp[u]+n-2*tree[v].cnt;
        dfs(v);
    }
}
```
**核心思想**：通过DFS遍历树结构，计算每个节点的操作次数，并通过换根动态规划优化计算过程。

#### 题解2：KokiNiwa (4星)

**关键亮点**：
- 将问题转化为完全二叉树结构，通过换根动态规划计算最小操作次数。
- 通过位运算快速计算每个化学物质到达目标体积所需的操作次数。

**核心代码**：
```cpp
void dfs(int now){
    if(now>maxVal) return;
    int lson=now<<1,rson=now<<1|1;
    dfs(lson),dfs(rson);
    sze[now]=mark[now];
    if(lson<=maxVal)sze[now]+=sze[lson];
    if(rson<=maxVal)sze[now]+=sze[rson];
}
```
**核心思想**：通过DFS遍历完全二叉树结构，计算每个节点的操作次数，并通过换根动态规划优化计算过程。

#### 题解3：Marsrayd (4星)

**关键亮点**：
- 使用经典二叉树结构建模，通过换根动态规划计算最小操作次数。
- 通过位运算快速计算每个化学物质到达目标体积所需的操作次数。

**核心代码**：
```cpp
void dfs1(int now){
    if(now>mx)return;
    dfs1(now<<1),dfs1(now<<1|1);
    sz[now]+=sz[now<<1]+sz[now<<1|1];
}
```
**核心思想**：通过DFS遍历二叉树结构，计算每个节点的操作次数，并通过换根动态规划优化计算过程。

---

### 个人心得总结

- **调试经历**：在实现树形结构时，需要注意节点的父子关系以及操作次数的正确计算，避免重复计算或遗漏。
- **踩坑教训**：在换根动态规划中，需要注意子节点与父节点之间的关系，确保每次换根后的操作次数计算正确。
- **顿悟感想**：通过将问题转化为树形结构或二进制表示，可以大大简化问题的复杂度，并利用已有的算法框架快速求解。

---
处理用时：41.95秒