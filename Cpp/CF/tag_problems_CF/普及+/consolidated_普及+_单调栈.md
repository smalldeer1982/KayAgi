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

