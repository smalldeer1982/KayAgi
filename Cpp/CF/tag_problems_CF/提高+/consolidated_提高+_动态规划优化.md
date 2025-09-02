---
title: "Two Subarrays"
layout: "post"
diff: 提高+/省选-
pid: CF2042F
tag: ['动态规划 DP', '线段树', '矩阵运算', '动态规划优化']
---

# Two Subarrays

## 题目描述

给定两个长度为 $n$ 的整数数组 $a$ 和 $b$。

我们定义子数组 $[l, r]$ 的代价为 $a_l + a_{l + 1} + \cdots + a_r + b_l + b_r$。如果 $l = r$，那么代价计算为 $a_l + 2 \cdot b_l$。

你需要执行以下三种类型的查询：

- "1 $p$ $x$" — 把 $a_p$ 更新为 $x$；
- "2 $p$ $x$" — 把 $b_p$ 更新为 $x$；
- "3 $l$ $r$" — 在区间 $[l, r]$ 内找到两个不相交且非空的子数组，使它们的总代价最大，并输出这个总代价。

## 输入格式

第一行是一个整数 $n$，表示数组的长度（$2 \le n \le 2 \cdot 10^5$）。

第二行是 $n$ 个整数，分别表示数组 $a$ 的元素：$a_1, a_2, \dots, a_n$（每个 $a_i$ 满足 $-10^9 \le a_i \le 10^9$）。

第三行是 $n$ 个整数，分别表示数组 $b$ 的元素：$b_1, b_2, \dots, b_n$（每个 $b_i$ 满足 $-10^9 \le b_i \le 10^9$）。

第四行是一个整数 $q$，表示查询的数量（$1 \le q \le 2 \cdot 10^5$）。

接下来的 $q$ 行，每行一个查询，可能是以下三种之一：

- "1 $p$ $x$"：更新 $a$ 数组的第 $p$ 个元素为 $x$；
- "2 $p$ $x$"：更新 $b$ 数组的第 $p$ 个元素为 $x$；
- "3 $l$ $r$"：在区间 $[l, r]$ 找到两个不重叠且非空的子数组，使它们的总代价最大，并输出该代价。

可以保证至少存在一个第三种类型的查询。

## 输出格式

对于每一个第三种类型的查询，输出在区间 $[l, r]$ 内的两个不相交且非空子数组的最大可能总代价。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
3 -1 4 -3 2 4 0
0 6 1 0 -3 -2 -1
6
3 1 7
1 2 0
3 3 6
2 5 -3
1 3 2
3 1 5
```

### 输出

```
18
7
16
```

## 样例 #2

### 输入

```
10
2 -1 -3 -2 0 4 5 6 2 5
2 -4 -5 -1 6 2 5 -6 4 2
10
3 6 7
1 10 -2
3 5 7
3 2 8
2 1 -5
2 7 4
3 1 3
3 3 8
3 2 3
1 4 4
```

### 输出

```
23
28
28
-17
27
-22
```



---

---
title: "Ice Baby"
layout: "post"
diff: 提高+/省选-
pid: CF2121H
tag: ['动态规划 DP', '线段树', '动态规划优化', '标签504']
---

# Ice Baby

## 题目描述

The longest non-decreasing subsequence of an array of integers $ a_1, a_2, \ldots, a_n $ is the longest sequence of indices $ 1 \leq i_1 < i_2 < \ldots < i_k \leq n $ such that $ a_{i_1} \leq a_{i_2} \leq \ldots \leq a_{i_k} $ . The length of the sequence is defined as the number of elements in the sequence. For example, the length of the longest non-decreasing subsequence of the array $ a = [3, 1, 4, 1, 2] $ is $ 3 $ .

You are given two arrays of integers $ l_1, l_2, \ldots, l_n $ and $ r_1, r_2, \ldots, r_n $ . For each $ 1 \le k \le n $ , solve the following problem:

- Consider all arrays of integers $ a $ of length $ k $ , such that for each $ 1 \leq i \leq k $ , it holds that $ l_i \leq a_i \leq r_i $ . Find the maximum length of the longest non-decreasing subsequence among all such arrays.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the arrays $ l $ and $ r $ .

The next $ n $ lines of each test case contain two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i \leq r_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers: for each $ k $ from $ 1 $ to $ n $ , output the maximum length of the longest non-decreasing subsequence among all suitable arrays.

## 说明/提示

In the first test case, the only possible array is $ a = [1] $ . The length of the longest non-decreasing subsequence of this array is $ 1 $ .

In the second test case, for $ k = 2 $ , no matter how we choose the values of $ a_1 $ and $ a_2 $ , the condition $ a_1 > a_2 $ will always hold. Therefore, the answer for $ k = 2 $ will be $ 1 $ .

In the third test case, for $ k = 4 $ , we can choose the array $ a = [5, 3, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 3 $ .

In the fourth test case, for $ k = 8 $ , we can choose the array $ a = [7, 5, 3, 5, 3, 3, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 5 $ .

In the fifth test case, for $ k = 5 $ , we can choose the array $ a = [2, 8, 5, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 3 $ .

## 样例 #1

### 输入

```
6
1
1 1
2
3 4
1 2
4
4 5
3 4
1 3
3 3
8
6 8
4 6
3 5
5 5
3 4
1 3
2 4
3 3
5
1 2
6 8
4 5
2 3
3 3
11
35 120
66 229
41 266
98 164
55 153
125 174
139 237
30 72
138 212
109 123
174 196
```

### 输出

```
1 
1 1 
1 2 2 3 
1 2 2 3 3 3 4 5 
1 2 2 2 3 
1 2 3 4 5 6 7 7 8 8 9
```



---

---
title: "Darth Vader and Tree"
layout: "post"
diff: 提高+/省选-
pid: CF514E
tag: ['动态规划 DP', '动态规划优化', '矩阵加速']
---

# Darth Vader and Tree

## 题目描述

When Darth Vader gets bored, he sits down on the sofa, closes his eyes and thinks of an infinite rooted tree where each node has exactly $ n $ sons, at that for each node, the distance between it an its $ i $ -th left child equals to $ d_{i} $ . The Sith Lord loves counting the number of nodes in the tree that are at a distance at most $ x $ from the root. The distance is the sum of the lengths of edges on the path between nodes.

But he has got used to this activity and even grew bored of it. 'Why does he do that, then?' — you may ask. It's just that he feels superior knowing that only he can solve this problem.

Do you want to challenge Darth Vader himself? Count the required number of nodes. As the answer can be rather large, find it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains two space-separated integers $ n $ and $ x $ ( $ 1<=n<=10^{5},0<=x<=10^{9} $ ) — the number of children of each node and the distance from the root within the range of which you need to count the nodes.

The next line contains $ n $ space-separated integers $ d_{i} $ ( $ 1<=d_{i}<=100 $ ) — the length of the edge that connects each node with its $ i $ -th child.

## 输出格式

Print a single number — the number of vertexes in the tree at distance from the root equal to at most $ x $ .

## 说明/提示

Pictures to the sample (the yellow color marks the nodes the distance to which is at most three)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514E/dfa75ce6cc0df1087a16e02cadbd273a08641d03.png)

## 样例 #1

### 输入

```
3 3
1 2 3

```

### 输出

```
8

```



---

---
title: "The Bakery"
layout: "post"
diff: 提高+/省选-
pid: CF833B
tag: ['动态规划 DP', '线段树', '枚举', '动态规划优化']
---

# The Bakery

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833B/f46eccace96d929fa4c99a2b4ae6e89027b73fa1.png)Some time ago Slastyona the Sweetmaid decided to open her own bakery! She bought required ingredients and a wonder-oven which can bake several types of cakes, and opened the bakery.

Soon the expenses started to overcome the income, so Slastyona decided to study the sweets market. She learned it's profitable to pack cakes in boxes, and that the more distinct cake types a box contains (let's denote this number as the value of the box), the higher price it has.

She needs to change the production technology! The problem is that the oven chooses the cake types on its own and Slastyona can't affect it. However, she knows the types and order of $ n $ cakes the oven is going to bake today. Slastyona has to pack exactly $ k $ boxes with cakes today, and she has to put in each box several (at least one) cakes the oven produced one right after another (in other words, she has to put in a box a continuous segment of cakes).

Slastyona wants to maximize the total value of all boxes with cakes. Help her determine this maximum possible total value.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=35000 $ , $ 1<=k<=min(n,50) $ ) – the number of cakes and the number of boxes, respectively.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ ) – the types of cakes in the order the oven bakes them.

## 输出格式

Print the only integer – the maximum total value of all boxes with cakes.

## 说明/提示

In the first example Slastyona has only one box. She has to put all cakes in it, so that there are two types of cakes in the box, so the value is equal to $ 2 $ .

In the second example it is profitable to put the first two cakes in the first box, and all the rest in the second. There are two distinct types in the first box, and three in the second box then, so the total value is $ 5 $ .

## 样例 #1

### 输入

```
4 1
1 2 2 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7 2
1 3 3 1 4 4 4

```

### 输出

```
5

```

## 样例 #3

### 输入

```
8 3
7 7 8 7 7 8 1 7

```

### 输出

```
6

```



---

