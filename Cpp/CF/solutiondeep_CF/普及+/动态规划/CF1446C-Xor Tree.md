# 题目信息

# Xor Tree

## 题目描述

For a given sequence of distinct non-negative integers $ (b_1, b_2, \dots, b_k) $ we determine if it is good in the following way:

- Consider a graph on $ k $ nodes, with numbers from $ b_1 $ to $ b_k $ written on them.
- For every $ i $ from $ 1 $ to $ k $ : find such $ j $ ( $ 1 \le j \le k $ , $ j\neq i $ ), for which $ (b_i \oplus b_j) $ is the smallest among all such $ j $ , where $ \oplus $ denotes the operation of bitwise XOR ([https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)). Next, draw an undirected edge between vertices with numbers $ b_i $ and $ b_j $ in this graph.
- We say that the sequence is good if and only if the resulting graph forms a tree (is connected and doesn't have any simple cycles).

It is possible that for some numbers $ b_i $ and $ b_j $ , you will try to add the edge between them twice. Nevertheless, you will add this edge only once.

You can find an example below (the picture corresponding to the first test case).

Sequence $ (0, 1, 5, 2, 6) $ is not good as we cannot reach $ 1 $ from $ 5 $ .

However, sequence $ (0, 1, 5, 2) $ is good.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1446C/787661480e10ca394e5bb0097a1db13aac775e6e.png)You are given a sequence $ (a_1, a_2, \dots, a_n) $ of distinct non-negative integers. You would like to remove some of the elements (possibly none) to make the remaining sequence good. What is the minimum possible number of removals required to achieve this goal?

It can be shown that for any sequence, we can remove some number of elements, leaving at least $ 2 $ , so that the remaining sequence is good.

## 说明/提示

Note that numbers which you remove don't impact the procedure of telling whether the resulting sequence is good.

It is possible that for some numbers $ b_i $ and $ b_j $ , you will try to add the edge between them twice. Nevertheless, you will add this edge only once.

## 样例 #1

### 输入

```
5
0 1 5 2 6```

### 输出

```
1```

## 样例 #2

### 输入

```
7
6 9 8 7 3 5 2```

### 输出

```
2```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个由互不相同的非负整数组成的序列 $(a_1, a_2, \dots, a_n)$，我们希望通过删除一些元素（可能不删除任何元素）来使剩下的序列成为“好序列”。一个序列被称为“好序列”当且仅当根据以下规则构建的图是一棵树：

1. 构建一个图，图中的节点对应序列中的元素。
2. 对于每个元素 $a_i$，找到一个元素 $a_j$（$j \neq i$），使得 $a_i \oplus a_j$ 是所有可能的 $a_j$ 中最小的，并在 $a_i$ 和 $a_j$ 之间画一条无向边。
3. 如果图是连通的且没有简单环，则称该序列为“好序列”。

目标是找到需要删除的最少元素数量，使得剩下的序列成为“好序列”。

#### 样例 #1

##### 输入

```
5
0 1 5 2 6
```

##### 输出

```
1
```

#### 样例 #2

##### 输入

```
7
6 9 8 7 3 5 2
```

##### 输出

```
2
```

### 题解综合分析与结论

本题的核心在于如何通过删除最少的元素，使得剩下的序列在构建的图中形成一棵树。多个题解都采用了**字典树（Trie）**来解决问题，利用字典树的性质来高效地找到最小异或对，并通过递归或动态规划来计算需要删除的元素数量。

### 精选题解

#### 题解1：BlankAo (赞：140)

**星级：5星**

**关键亮点：**
- 使用了字典树来存储和处理序列中的元素。
- 通过递归的方式计算每个子树的最大保留数，最终得到需要删除的元素数量。
- 思路清晰，代码简洁，时间复杂度为 $O(n \log n)$。

**核心代码：**
```cpp
int GetMaxPoint(int p) {
    if(!ch[p][0]&&!ch[p][1]) return 1;
    if(!ch[p][0]) return GetMaxPoint(ch[p][1]);
    if(!ch[p][1]) return GetMaxPoint(ch[p][0]);
    return max(GetMaxPoint(ch[p][0]),GetMaxPoint(ch[p][1]))+1;
}
```
**核心思想：**
- 递归计算每个子树的最大保留数，如果当前节点有两个子节点，则取两个子树的最大保留数加1。

#### 题解2：tommymio (赞：40)

**星级：4星**

**关键亮点：**
- 同样使用了字典树，通过递归计算每个子树的最大保留数。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
inline int GetMaxPoint(int p) {
    if(!ch[p][0]&&!ch[p][1]) return 1;
    if(!ch[p][0]) return GetMaxPoint(ch[p][1]);
    if(!ch[p][1]) return GetMaxPoint(ch[p][0]);
    return max(GetMaxPoint(ch[p][0]),GetMaxPoint(ch[p][1]))+1;
}
```
**核心思想：**
- 递归计算每个子树的最大保留数，如果当前节点有两个子节点，则取两个子树的最大保留数加1。

#### 题解3：Marsrayd (赞：10)

**星级：4星**

**关键亮点：**
- 使用了字典树，并通过动态规划的方式计算需要删除的元素数量。
- 详细解释了为什么需要删除某些元素来保证图的连通性。

**核心代码：**
```cpp
long long dp(int p) {
    if(!tr[p].son[0]&&!tr[p].son[1]) return 1;
    if(!tr[p].son[0]&&tr[p].son[1]) return dp(tr[p].son[1]);
    if(tr[p].son[0]&&!tr[p].son[1]) return dp(tr[p].son[0]);
    return std::max(dp(tr[p].son[0]),dp(tr[p].son[1]))+1;
}
```
**核心思想：**
- 递归计算每个子树的最大保留数，如果当前节点有两个子节点，则取两个子树的最大保留数加1。

### 最优关键思路或技巧

1. **字典树的应用**：利用字典树来高效地找到最小异或对，并通过递归或动态规划来计算需要删除的元素数量。
2. **递归与动态规划**：通过递归或动态规划的方式计算每个子树的最大保留数，最终得到需要删除的元素数量。

### 可拓展之处

- 类似的问题可以通过字典树来解决，例如寻找数组中异或值最大的对。
- 字典树在处理与二进制相关的问题时非常有效，可以扩展到其他与二进制相关的题目。

### 推荐题目

1. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)
2. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3373 【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)

### 个人心得摘录

- **BlankAo**：通过字典树的性质，递归计算每个子树的最大保留数，最终得到需要删除的元素数量。思路清晰，代码简洁。
- **tommymio**：同样使用了字典树，通过递归计算每个子树的最大保留数。代码结构清晰，易于理解。
- **Marsrayd**：详细解释了为什么需要删除某些元素来保证图的连通性，并通过动态规划的方式计算需要删除的元素数量。

---
处理用时：48.18秒