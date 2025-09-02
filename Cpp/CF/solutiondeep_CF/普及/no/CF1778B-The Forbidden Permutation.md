# 题目信息

# The Forbidden Permutation

## 题目描述

You are given a permutation $ p $ of length $ n $ , an array of $ m $ distinct integers $ a_1, a_2, \ldots, a_m $ ( $ 1 \le a_i \le n $ ), and an integer $ d $ .

Let $ \mathrm{pos}(x) $ be the index of $ x $ in the permutation $ p $ . The array $ a $ is not good if

- $ \mathrm{pos}(a_{i}) < \mathrm{pos}(a_{i + 1}) \le \mathrm{pos}(a_{i}) + d $ for all $ 1 \le i < m $ .

For example, with the permutation $ p = [4, 2, 1, 3, 6, 5] $ and $ d = 2 $ :

- $ a = [2, 3, 6] $ is a not good array.
- $ a = [2, 6, 5] $ is good because $ \mathrm{pos}(a_1) = 2 $ , $ \mathrm{pos}(a_2) = 5 $ , so the condition $ \mathrm{pos}(a_2) \le \mathrm{pos}(a_1) + d $ is not satisfied.
- $ a = [1, 6, 3] $ is good because $ \mathrm{pos}(a_2) = 5 $ , $ \mathrm{pos}(a_3) = 4 $ , so the condition $ \mathrm{pos}(a_2) < \mathrm{pos}(a_3) $ is not satisfied.

In one move, you can swap two adjacent elements of the permutation $ p $ . What is the minimum number of moves needed such that the array $ a $ becomes good? It can be shown that there always exists a sequence of moves so that the array $ a $ becomes good.

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but there is $ 4 $ in the array).

## 说明/提示

In the first case, $ pos(a_1)=1 $ , $ pos(a_2)=3 $ . To make the array good, one way is to swap $ p_3 $ and $ p_4 $ . After that, the array $ a $ will be good because the condition $ \mathrm{pos}(a_2) \le \mathrm{pos}(a_1) + d $ won't be satisfied.

In the second case, $ pos(a_1)=1 $ , $ pos(a_2)=4 $ . The $ 3 $ moves could be:

1. Swap $ p_3 $ and $ p_4 $ .
2. Swap $ p_2 $ and $ p_3 $ .
3. Swap $ p_1 $ and $ p_2 $ .

 After these moves, the permutation $ p $ will be $ [2,5,4,3,1] $ . The array $ a $ will be good because the condition $ \mathrm{pos}(a_1) < \mathrm{pos}(a_2) $ won't be satisfied. It can be shown that you can't make the array $ a $ good with fewer moves.In the third case, $ pos(a_1)=1 $ , $ pos(a_2)=3 $ , $ pos(a_3)=5 $ . The $ 2 $ moves can be:

1. Swap $ p_4 $ and $ p_5 $ .
2. Swap $ p_3 $ and $ p_4 $ .

 After these moves, the permutation $ p $ will be $ [3,4,2,1,5] $ . The array $ a $ will be good because the condition $ \mathrm{pos}(a_2) < \mathrm{pos}(a_3) $ won't be satisfied. It can be shown that you can't make the array $ a $ good with fewer moves.In the fourth case, $ pos(a_1)=2 $ , $ pos(a_2)=1 $ . The array $ a $ is already good.

In the fifth case, $ pos(a_1)=2 $ , $ pos(a_2)=5 $ . The $ 2 $ moves are:

1. Swap $ p_1 $ and $ p_2 $ .
2. Swap $ p_5 $ and $ p_6 $ .

## 样例 #1

### 输入

```
5
4 2 2
1 2 3 4
1 3
5 2 4
5 4 3 2 1
5 2
5 3 3
3 4 1 5 2
3 1 2
2 2 1
1 2
2 1
6 2 4
1 2 3 4 5 6
2 5```

### 输出

```
1
3
2
0
2```

# AI分析结果

### 题目翻译

#### 被禁止的排列

**题目描述**

给定一个长度为 $n$ 的排列 $p$，一个由 $m$ 个不同整数组成的数组 $a_1, a_2, \ldots, a_m$（$1 \le a_i \le n$），以及一个整数 $d$。

定义 $\mathrm{pos}(x)$ 为 $x$ 在排列 $p$ 中的索引。如果数组 $a$ 满足以下条件，则称其为“不好”的数组：

- 对于所有 $1 \le i < m$，有 $\mathrm{pos}(a_{i}) < \mathrm{pos}(a_{i + 1}) \le \mathrm{pos}(a_{i}) + d$。

例如，给定排列 $p = [4, 2, 1, 3, 6, 5]$ 和 $d = 2$：

- $a = [2, 3, 6]$ 是一个“不好”的数组。
- $a = [2, 6, 5]$ 是“好”的，因为 $\mathrm{pos}(a_1) = 2$，$\mathrm{pos}(a_2) = 5$，条件 $\mathrm{pos}(a_2) \le \mathrm{pos}(a_1) + d$ 不满足。
- $a = [1, 6, 3]$ 是“好”的，因为 $\mathrm{pos}(a_2) = 5$，$\mathrm{pos}(a_3) = 4$，条件 $\mathrm{pos}(a_2) < \mathrm{pos}(a_3)$ 不满足。

在一次操作中，你可以交换排列 $p$ 中的两个相邻元素。问最少需要多少次操作才能使数组 $a$ 变为“好”的？可以证明，总存在一系列操作使得数组 $a$ 变为“好”的。

排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 出现了两次），$[1,3,4]$ 也不是排列（$n=3$，但数组中出现了 $4$）。

**说明/提示**

在第一个样例中，$pos(a_1)=1$，$pos(a_2)=3$。为了使数组 $a$ 变为“好”的，一种方法是将 $p_3$ 和 $p_4$ 交换。交换后，数组 $a$ 将变为“好”的，因为条件 $\mathrm{pos}(a_2) \le \mathrm{pos}(a_1) + d$ 不再满足。

在第二个样例中，$pos(a_1)=1$，$pos(a_2)=4$。可能的 $3$ 次操作如下：

1. 交换 $p_3$ 和 $p_4$。
2. 交换 $p_2$ 和 $p_3$。
3. 交换 $p_1$ 和 $p_2$。

操作后，排列 $p$ 将变为 $[2,5,4,3,1]$。数组 $a$ 将变为“好”的，因为条件 $\mathrm{pos}(a_1) < \mathrm{pos}(a_2)$ 不再满足。可以证明，无法用更少的操作使数组 $a$ 变为“好”的。

在第三个样例中，$pos(a_1)=1$，$pos(a_2)=3$，$pos(a_3)=5$。可能的 $2$ 次操作如下：

1. 交换 $p_4$ 和 $p_5$。
2. 交换 $p_3$ 和 $p_4$。

操作后，排列 $p$ 将变为 $[3,4,2,1,5]$。数组 $a$ 将变为“好”的，因为条件 $\mathrm{pos}(a_2) < \mathrm{pos}(a_3)$ 不再满足。可以证明，无法用更少的操作使数组 $a$ 变为“好”的。

在第四个样例中，$pos(a_1)=2$，$pos(a_2)=1$。数组 $a$ 已经是“好”的。

在第五个样例中，$pos(a_1)=2$，$pos(a_2)=5$。可能的 $2$ 次操作如下：

1. 交换 $p_1$ 和 $p_2$。
2. 交换 $p_5$ 和 $p_6$。

**样例 #1**

**输入**

```
5
4 2 2
1 2 3 4
1 3
5 2 4
5 4 3 2 1
5 2
5 3 3
3 4 1 5 2
3 1 2
2 2 1
1 2
2 1
6 2 4
1 2 3 4 5 6
2 5
```

**输出**

```
1
3
2
0
2
```

### 算法分类

贪心

### 题解分析与结论

本题的核心在于通过最少的交换操作使得给定的数组 $a$ 变为“好”的。题解中普遍采用了贪心策略，通过分析 $a$ 中相邻元素的相对位置关系，找到最少的交换次数。

#### 题解对比

1. **_acat_ 的题解**
   - **亮点**：详细分析了三种情况，并给出了两种可能的操作方式，代码实现简洁。
   - **评分**：4星
   - **关键代码**：
     ```cpp
     for(int i=1;i<m;i++){
         int dis=pos[a[i+1]]-pos[a[i]];
         if(pos[a[i+1]]<=pos[a[i]] || dis>d){
             ans=0;
             break;
         }
         ans=min(ans,dis);
         if((pos[a[i]]-1+n-pos[a[i+1]])>=d-dis+1){
             ans=min(ans,d-dis+1);
         }
     }
     ```

2. **atomic_int 的题解**
   - **亮点**：代码简洁，直接处理了两种情况，并考虑了边界条件。
   - **评分**：4星
   - **关键代码**：
     ```cpp
     for (int i = 1; i < m; i ++) {
         if (pos[a[i]] > pos[a[i + 1]] || pos[a[i + 1]] - d > pos[a[i]]) {
             cout << 0 << '\n';
             return ;
         }
         int res = min(pos[a[i + 1]] - pos[a[i]], (d + 1 < n ? d + 1 - pos[a[i + 1]] + pos[a[i]] : inf64));
         ans = min(ans, res);
     }
     ```

3. **zfx_VeXl6 的题解**
   - **亮点**：详细解释了两种操作方式，并给出了具体的操作次数计算。
   - **评分**：4星
   - **关键代码**：
     ```cpp
     for(int i=1;i<m;i++)
         if(pos[a[i]]<pos[a[i+1]]&&pos[a[i+1]]<=pos[a[i]]+d)
         {
             ans=min(ans,pos[a[i+1]]-pos[a[i]]);
             if(d<=n-2)
                 ans=min(ans,d-(pos[a[i+1]]-pos[a[i]]-1));
         }
     ```

### 最优思路总结

最优思路是通过贪心策略，分析 $a$ 中相邻元素的相对位置关系，找到最少的交换次数。具体来说，对于每一对相邻元素 $a_i$ 和 $a_{i+1}$，有两种可能的操作方式：

1. 将 $a_{i+1}$ 向左移动，使其位置小于 $a_i$ 的位置。
2. 将 $a_{i+1}$ 向右移动，使其位置大于 $a_i$ 的位置加上 $d$。

通过计算这两种操作的最小值，可以得到全局的最小交换次数。

### 可拓展之处

类似的问题可以扩展到其他需要调整元素相对位置的场景，例如在排序问题中，通过最少的交换次数使数组满足某种特定的顺序条件。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

---
处理用时：50.83秒