---
title: "Object Identification"
layout: "post"
diff: 难度0
pid: CF2066A
tag: []
---

# Object Identification

## 题目描述

This is an interactive problem.

You are given an array $ x_1, \ldots, x_n $ of integers from $ 1 $ to $ n $ . The jury also has a fixed but hidden array $ y_1, \ldots, y_n $ of integers from $ 1 $ to $ n $ . The elements of array $ y $ are unknown to you. Additionally, it is known that for all $ i $ , $ x_i \neq y_i $ , and all pairs $ (x_i, y_i) $ are distinct.

The jury has secretly thought of one of two objects, and you need to determine which one it is:

- Object A: A directed graph with $ n $ vertices numbered from $ 1 $ to $ n $ , and with $ n $ edges of the form $ x_i \to y_i $ .
- Object B: $ n $ points on a coordinate plane. The $ i $ -th point has coordinates $ (x_i, y_i) $ .

To guess which object the jury has thought of, you can make queries. In one query, you must specify two numbers $ i, j $ $ (1 \leq i, j \leq n, i \neq j) $ . In response, you receive one number:

- If the jury has thought of Object A, you receive the length of the shortest path (in edges) from vertex $ i $ to vertex $ j $ in the graph, or $ 0 $ if there is no path.
- If the jury has thought of Object B, you receive the Manhattan distance between points $ i $ and $ j $ , that is $ |x_i -x_j| + |y_i - y_j| $ .

You have $ 2 $ queries to determine which of the objects the jury has thought of.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

## 输出格式

The interaction begins with reading $ n $ ( $ 3 \leq n \leq 2 \cdot 10^5 $ ) — the length of the arrays $ x $ and $ y $ at the start of each test case.

Next, read $ n $ integers: $ x_1, x_2, \ldots, x_n $ ( $ 1 \leq x_i \leq n $ ) — the elements of array $ x $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

The array $ y_1, y_2, \ldots, y_n $ is fixed for each test case. In other words, the interactor is not adaptive.

It is guaranteed that $ x_i \neq y_i $ for all $ 1 \leq i \leq n $ , and all pairs $ (x_i, y_i) $ are distinct.

To make a query, output "? $ i $ $ j $ " (without quotes, $ 1 \le i, j \le n, i \neq j $ ). Then you must read the response to the query, which is a non-negative integer.

To give an answer, output "! A" if Object A is hidden or "! B" if Object B is hidden (without quotes). Note that printing the answer does not count as one of the $ 2 $ queries.

After printing each query do not forget to output the end of line and flush $ ^{\text{∗}} $ the output. Otherwise, you will get Idleness limit exceeded verdict. If, at any interaction step, you read $ -1 $ instead of valid data, your solution must exit immediately. This means that your solution will reveive Wrong answer because of an invalid query or any other mistake. Failing to exit can result in an arbitrary verdict because your solution will continue to read from a closed stream. Note that if the query is correct, the response will never be $ -1 $ .

Hacks

The first line must contain an integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case must contain an integer $ n $ ( $ 3 \le n \le 2 \cdot 10^5 $ ) — the length of the hidden array.

The second line of each test case must contain $ n $ integers — $ x_1, x_2, \ldots, x_n $ ( $ 1 \le x_i \le n $ ).

The third line of each test case must contain $ n $ integers — $ y_1, y_2, \ldots, y_n $ ( $ 1 \le y_i \le n $ ).

It must be ensured that $ x_i \neq y_i $ for all $ 1 \le i \le n $ , and all pairs $ (x_i, y_i) $ must be distinct.

The fourth line must contain one character: A or B, indicating which of the objects you want to hide.

The sum of $ n $ across all test cases must not exceed $ 2 \cdot 10^5 $ .

 $ ^{\text{∗}} $ To flush, use:

- fflush(stdout) or cout.flush() in C++;
- sys.stdout.flush() in Python;
- see the documentation for other languages.

## 说明/提示

In the first test case, $ x = [2,2,3] $ , $ y = [1,3,1] $ and Object A is guessed.

In the second test case, $ x = [5,1,4,2,3] $ , $ y = [3,3,2,4,1] $ and Object B is guessed.

## 样例 #1

### 输入

```
2
3
2 2 3

1

0

5
5 1 4 2 3

4

4
```

### 输出

```
? 2 3

? 1 2

! A

? 1 5

? 5 1

! B
```

