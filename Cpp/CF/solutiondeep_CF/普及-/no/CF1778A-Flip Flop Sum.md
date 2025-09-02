# 题目信息

# Flip Flop Sum

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ . The integers are either $ 1 $ or $ -1 $ . You have to perform the following operation exactly once on the array $ a $ :

- Choose an index $ i $ ( $ 1 \leq i < n $ ) and flip the signs of $ a_i $ and $ a_{i+1} $ . Here, flipping the sign means $ -1 $ will be $ 1 $ and $ 1 $ will be $ -1 $ .

What is the maximum possible value of $ a_1 + a_2 + \ldots + a_n $ after applying the above operation?

## 说明/提示

In the first case, we can choose index $ 4 $ and flip the signs of $ a_4 $ and $ a_5 $ . After this operation, the sum will be $ -1+1+1+1+1 = 3 $ . We can't make the sum larger than this.

In the third case, the only option is to choose the index $ 1 $ .

## 样例 #1

### 输入

```
4
5
-1 1 1 -1 -1
5
1 1 -1 -1 -1
2
1 1
4
1 -1 -1 1```

### 输出

```
3
3
-2
4```

# AI分析结果

### 题目内容
# 翻转求和

## 题目描述
给定一个包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ 的数组。这些整数要么是 $1$ 要么是 $ - 1$ 。你必须对数组 $a$ 恰好执行以下操作一次：
- 选择一个索引 $i$（$1 \leq i < n$），并翻转 $a_i$ 和 $a_{i + 1}$ 的符号。这里，翻转符号意味着 $ - 1$ 变为 $1$，$1$ 变为 $ - 1$ 。

在应用上述操作后，$a_1 + a_2 + \ldots + a_n$ 的最大可能值是多少？

## 说明/提示
在第一种情况下，我们可以选择索引 $4$ 并翻转 $a_4$ 和 $a_5$ 的符号。在此操作之后，和将是 $ - 1+1+1+1+1 = 3$ 。我们无法使和大于此值。

在第三种情况下，唯一的选择是选择索引 $1$ 。

## 样例 #1
### 输入
```
4
5
-1 1 1 -1 -1
5
1 1 -1 -1 -1
2
1 1
4
1 -1 -1 1
```
### 输出
```
3
3
-2
4
```

### 算法分类
贪心

### 综合分析与结论
由于暂无题解，现提供通用思路：对于该问题，核心在于通过一次特定的符号翻转操作来最大化数组元素和。可以遍历所有可能的翻转位置 $i$（$1 \leq i < n$），每次翻转后计算新的数组和，记录下最大的和值。这种贪心策略是基于每次尝试局部最优的翻转选择，期望得到全局最优解。

### 扩展思路
同类型题目通常围绕对数组元素的特定操作，通过有限次数的操作来优化某个目标值。类似算法套路可以先尝试暴力枚举所有可能操作情况，再看是否能通过贪心策略优化，减少计算量。

### 洛谷相似题目推荐
1. P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)：同样是通过一定操作优化目标值，考察贪心思想。
2. P1199 [三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及对数据的操作及最优策略选择，与本题思路类似。
3. P1223 [排队接水](https://www.luogu.com.cn/problem/P1223)：也是利用贪心策略解决排队操作以优化时间总和的问题。 

---
处理用时：19.94秒