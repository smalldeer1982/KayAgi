---
title: "Field Division (easy version)"
layout: "post"
diff: 普及+/提高
pid: CF1980F1
tag: ['单调栈']
---

# Field Division (easy version)

## 题目描述

This is an easy version of the problem; it differs from the hard version only by the question. The easy version only needs you to print whether some values are non-zero or not. The hard version needs you to print the exact values.

Alice and Bob are dividing the field. The field is a rectangle of size $ n \times m $ ( $ 2 \le n, m \le 10^9 $ ), the rows are numbered from $ 1 $ to $ n $ from top to bottom, and the columns are numbered from $ 1 $ to $ m $ from left to right. The cell at the intersection of row $ r $ and column $ c $ is denoted as ( $ r, c $ ).

Bob has $ k $ ( $ 2 \le k \le 2 \cdot 10^5 $ ) fountains, all of them are located in different cells of the field. Alice is responsible for dividing the field, but she must meet several conditions:

- To divide the field, Alice will start her path in any free (without a fountain) cell on the left or top side of the field and will move, each time moving to the adjacent cell down or right. Her path will end on the right or bottom side of the field.
- Alice's path will divide the field into two parts — one part will belong to Alice (this part includes the cells of her path), the other part — to Bob.
- Alice will own the part that includes the cell ( $ n, 1 $ ).
- Bob will own the part that includes the cell ( $ 1, m $ ).

Alice wants to divide the field in such a way as to get as many cells as possible.

Bob wants to keep ownership of all the fountains, but he can give one of them to Alice. First, output the integer $ \alpha $ — the maximum possible size of Alice's plot, if Bob does not give her any fountain (i.e., all fountains will remain on Bob's plot). Then output $ k $ non-negative integers $ a_1, a_2, \dots, a_k $ , where:

- $ a_i=0 $ , if after Bob gives Alice the $ i $ -th fountain, the maximum possible size of Alice's plot does not increase (i.e., remains equal to $ \alpha $ );
- $ a_i=1 $ , if after Bob gives Alice the $ i $ -th fountain, the maximum possible size of Alice's plot increases (i.e., becomes greater than $ \alpha $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 2 \le n, m \le 10^9 $ , $ 2 \le k \le 2 \cdot 10^5 $ ) — the field sizes and the number of fountains, respectively.

Then follow $ k $ lines, each containing two numbers $ r_i $ and $ c_i $ ( $ 1 \le r_i \le n $ , $ 1 \le c_i \le m $ ) — the coordinates of the cell with the $ i $ -th fountain. It is guaranteed that all cells are distinct and none of them is ( $ n, 1 $ ).

It is guaranteed that the sum of $ k $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, first output $ \alpha $ — the maximum size of the plot that can belong to Alice if Bob does not give her any of the fountains. Then output $ k $ non-negative integers $ a_1, a_2, \dots, a_k $ , where:

- $ a_i=0 $ , if after Bob gives Alice the $ i $ -th fountain, the maximum possible size of Alice's plot does not increase compared to the case when all $ k $ fountains belong to Bob;
- $ a_i=1 $ , if after Bob gives Alice the $ i $ -th fountain, the maximum possible size of Alice's plot increases compared to the case when all $ k $ fountains belong to Bob.

If you output any other positive number instead of $ 1 $ that fits into a 64-bit signed integer type, it will also be recognized as $ 1 $ . Thus, a solution to the hard version of this problem will also pass the tests for the easy version.

## 说明/提示

Below are the images for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1980F1/50ede57a92b2f87fd310741ab01efa95ca5a8eab.png) The indices of the fountains are labeled in green. The cells belonging to Alice are marked in blue.Note that if Bob gives Alice fountain $ 1 $ or fountain $ 3 $ , then that fountain cannot be on Alice's plot.

## 样例 #1

### 输入

```
5
2 2 3
1 1
1 2
2 2
5 5 4
1 2
2 2
3 4
4 3
2 5 9
1 2
1 5
1 1
2 2
2 4
2 5
1 4
2 3
1 3
6 4 4
6 2
1 3
1 4
1 2
3 4 5
2 1
3 2
1 4
1 3
2 4
```

### 输出

```
1
1 0 1 
11
0 1 0 1 
1
0 0 1 1 0 0 0 0 0 
6
1 0 0 0 
1
1 1 0 0 0
```



---

---
title: "Longest Max Min Subsequence"
layout: "post"
diff: 普及+/提高
pid: CF2001D
tag: ['线段树', '栈']
---

# Longest Max Min Subsequence

## 题目描述

You are given an integer sequence $ a_1, a_2, \ldots, a_n $ . Let $ S $ be the set of all possible non-empty subsequences of $ a $ without duplicate elements. Your goal is to find the longest sequence in $ S $ . If there are multiple of them, find the one that minimizes lexicographical order after multiplying terms at odd positions by $ -1 $ .

For example, given $ a = [3, 2, 3, 1] $ , $ S = \{[1], [2], [3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 3, 1], [3, 2, 1]\} $ . Then $ [2, 3, 1] $ and $ [3, 2, 1] $ would be the longest, and $ [3, 2, 1] $ would be the answer since $ [-3, 2, -1] $ is lexicographically smaller than $ [-2, 3, -1] $ .

A sequence $ c $ is a subsequence of a sequence $ d $ if $ c $ can be obtained from $ d $ by the deletion of several (possibly, zero or all) elements.

A sequence $ c $ is lexicographically smaller than a sequence $ d $ if and only if one of the following holds:

- $ c $ is a prefix of $ d $ , but $ c \ne d $ ;
- in the first position where $ c $ and $ d $ differ, the sequence $ c $ has a smaller element than the corresponding element in $ d $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^4 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the length of $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the sequence $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output the answer in the following format:

Output an integer $ m $ in the first line — the length of $ b $ .

Then output $ m $ integers $ b_1, b_2, \ldots, b_m $ in the second line — the sequence $ b $ .

## 说明/提示

In the first example, $ S = \{[1], [2], [3], [1, 3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 1, 3], [3, 2, 1]\} $ . Among them, $ [2, 1, 3] $ and $ [3, 2, 1] $ are the longest and $ [-3, 2, -1] $ is lexicographical smaller than $ [-2, 1, -3] $ , so $ [3, 2, 1] $ is the answer.

In the second example, $ S = \{[1]\} $ , so $ [1] $ is the answer.

## 样例 #1

### 输入

```
4
4
3 2 1 3
4
1 1 1 1
9
3 2 1 3 2 1 3 2 1
1
1
```

### 输出

```
3
3 2 1
1
1
3
3 1 2
1
1
```

## 样例 #2

### 输入

```
10
2
1 2
10
5 2 1 7 9 7 2 5 5 2
2
1 2
10
2 2 8 7 7 9 8 1 9 6
9
9 1 7 5 8 5 6 4 1
3
3 3 3
6
1 6 4 4 6 5
6
3 4 4 5 3 3
10
4 1 4 5 4 5 10 1 5 1
7
1 2 1 3 2 4 6
```

### 输出

```
2
1 2
5
5 1 9 7 2
2
1 2
6
2 7 9 8 1 6
7
9 1 7 5 8 6 4
1
3
4
1 4 6 5
3
4 5 3
4
5 4 10 1
5
2 1 3 4 6
```



---

---
title: "Milky Days"
layout: "post"
diff: 普及+/提高
pid: CF2014G
tag: ['栈']
---

# Milky Days

## 题目描述

### 题目背景
小约翰爱喝牛奶。

他的日记有 $n$ 条记录，表明他在第 $d_i$ 天获得了 $a_i$ 品脱鲜牛奶。牛奶的新鲜度会随着时间的推移而下降，最多可以饮用 $k$ 天。换句话说，在第 $d_i$ 天获得的鲜牛奶在第 $d_i$ 天和第 $d_i+k-1$ 天（含）之间可以饮用。

小约翰每天最多喝 $m$ 品脱牛奶，并且会尽量多喝。如果牛奶少于 $m$ 品脱，他会喝完所有牛奶，但不会感到满足；如果牛奶至少有 $m$ 品脱，他会喝下 $m$ 品脱并感到满足，称这是牛奶满足日。

小约翰总是先喝最新鲜的可饮用牛奶。

请求出小约翰的牛奶满意日的数量。

 _**本题有多组测试数据。**_

## 输入格式

第一行输入一个整数 $T$（$1\leq T \leq 10^4$），表示测试数据总数。

此后每组测试数据，第一行为三个整数 $n, m, k$（$1\leq n,m,k \leq 10^5$）。含义如题目背景所示。

接下来 $n$ 行，每行输入两个整数 $d_i, a_i$（$1\leq d_i,a_i \leq 10^6$），表示牛奶的购买日期和购买的品脱数，从小到大排序，每个数据的值都不相同。

**保证所有样例的 $n$ 之和不超过 $2 \cdot 10^5$。**

## 输出格式

对于每组测试数据，每行输出一个整数表示该数据中小约翰的牛奶满意日的数量。

## 样例 #1

### 输入

```
6
1 1 3
1 5
2 3 3
1 5
2 7
4 5 2
1 9
2 6
4 9
5 6
5 2 4
4 7
5 3
7 1
11 2
12 1
4 1 3
5 10
9 4
14 8
15 3
5 5 5
8 9
10 7
16 10
21 5
28 9
```

### 输出

```
3
3
4
5
10
6
```



---

---
title: "Yet Another Real Number Problem"
layout: "post"
diff: 普及+/提高
pid: CF2035D
tag: ['贪心', '单调栈']
---

# Yet Another Real Number Problem

## 题目描述

# 又一个实数问题


Three r there are's in strawberry.

（“strawberry”中有三个“r”）


给定一个长度为 $m$ 的数组 $b$ 。你可以进行以下操作任意次（可能为零次）：

- 选择两个不同的下标 $i$ 和 $j$ ，其中 $\bf{1\le i<j\le m}$ 且 $b_i$ 是偶数，将 $b_i$ 除以 $2$ ，并将 $b_j$ 乘以 $2$ 。

你的任务是通过任意次数的操作来最大化数组的和。因为结果可能会非常大，你需要输出该和对 $10^9+7$ 取模的结果。

由于这个问题太简单了，所以现在你被给定了一个长度为 $n$ 的数组 $a$，需要针对数组 $a$ 的每个前缀来求解该问题。

换句话说，记经过任意次数操作后 $ b $ 的最大和为 $f(b)$ ，你需要分别输出 $f([a_1])$ , $f([a_1,a_2])$ , $\ldots$ , $f([a_1,a_2,\ldots,a_n])$ 对 $10^9+7$ 取模的结果。

## 输入格式

第一行包含一个整数 $t$ ( $1\le t\le 10^4$ ) — 测试用例数。

每个测试用例的第一行包含一个整数 $n$ ( $1\le n\le 2\cdot 10^5$ ) — $a$ 的长度。

第二行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$ ( $1\le a_i\le 10^9$ ) — 数组 $a$ 的初始值。

保证所有测试用例中 $n$ 的总和不超过 $2\cdot 10^5$ 。

## 输出格式

针对每个测试用例，输出 $n$ 个整数，表示每个前缀的答案，结果对 $10^9+7$ 取模。

## 样例 #1

### 样例输入 #1

```
3
10
1 2 3 4 5 6 7 8 9 10
11
1 6 9 4 7 4 4 10 3 2 3
4
527792568 502211460 850237282 374773208
```

### 样例输出 #1

```
1 3 8 13 46 59 126 149 1174 1311 
1 7 22 26 70 74 150 1303 1306 1308 1568 
527792568 83665723 399119771 773892979 
```

## 说明/提示

对于第一个测试用例中的每个前缀数组，操作后可能是：

- $[1]$ 和为 $1$ 
- $[1,2]$ 和为 $3$ 
- $[1,1,6]$ 和为 $8$ 
- $[1,1,3,8]$ 和为 $13$ 
- $[1,1,3,1,40]$ 和为 $46$ 
- $[1,1,3,1,5,48]$ 和为 $59$ 
- $[1,1,3,1,5,3,112]$ 和为 $126$ 
- $[1,1,3,1,5,3,7,128]$ 和为 $149$ 
- $[1,1,3,1,5,3,7,1,1152]$ 和为 $1174$
- $[1,1,3,1,5,3,7,1,9,1280]$ 和为 $ 1311 $​

## 样例 #1

### 输入

```
3
10
1 2 3 4 5 6 7 8 9 10
11
1 6 9 4 7 4 4 10 3 2 3
4
527792568 502211460 850237282 374773208
```

### 输出

```
1 3 8 13 46 59 126 149 1174 1311 
1 7 22 26 70 74 150 1303 1306 1308 1568 
527792568 83665723 399119771 773892979
```



---

