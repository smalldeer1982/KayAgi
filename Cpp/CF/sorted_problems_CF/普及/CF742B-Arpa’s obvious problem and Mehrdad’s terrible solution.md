---
title: "Arpa’s obvious problem and Mehrdad’s terrible solution"
layout: "post"
diff: 普及/提高-
pid: CF742B
tag: []
---

# Arpa’s obvious problem and Mehrdad’s terrible solution

## 题目描述

There are some beautiful girls in Arpa’s land as mentioned before.

Once Arpa came up with an obvious problem:

Given an array and a number $ x $ , count the number of pairs of indices $ i,j $ ( $ 1<=i&lt;j<=n $ ) such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/80e8812f6abd24888e930488b3c56b15fb2a49a1.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/4298d47c0191af3c0a3103f431751061bc7e2362.png) is bitwise xor operation (see notes for explanation).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/7cd1b5aedffc45f296d333e099a050047eae38ee.png)Immediately, Mehrdad discovered a terrible solution that nobody trusted. Now Arpa needs your help to implement the solution to that problem.

## 输入格式

First line contains two integers $ n $ and $ x $ ( $ 1<=n<=10^{5},0<=x<=10^{5} $ ) — the number of elements in the array and the integer $ x $ .

Second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{5} $ ) — the elements of the array.

## 输出格式

Print a single integer: the answer to the problem.

## 说明/提示

In the first sample there is only one pair of $ i=1 $ and $ j=2 $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/c63bc815847bae57aeba51b11f6ec2211cbd1efa.png) so the answer is $ 1 $ .

In the second sample the only two pairs are $ i=3 $ , $ j=4 $ (since ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/360a9ab048a3005f1d532cfb7c78e96ffd10455b.png)) and $ i=1 $ , $ j=5 $ (since ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/e00da54f194d914d5a9270c780a44af611f46740.png)).

A bitwise xor takes two bit integers of equal length and performs the logical xor operation on each pair of corresponding bits. The result in each position is $ 1 $ if only the first bit is $ 1 $ or only the second bit is $ 1 $ , but will be $ 0 $ if both are $ 0 $ or both are $ 1 $ . You can read more about bitwise xor operation here: [https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 样例 #1

### 输入

```
2 3
1 2

```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 1
5 1 2 3 4 1

```

### 输出

```
2
```

