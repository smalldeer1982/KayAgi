---
title: "All Possible Digits"
layout: "post"
diff: 普及+/提高
pid: CF1759F
tag: []
---

# All Possible Digits

## 题目描述

A positive number $ x $ of length $ n $ in base $ p $ ( $ 2 \le p \le 10^9 $ ) is written on the blackboard. The number $ x $ is given as a sequence $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < p $ ) — the digits of $ x $ in order from left to right (most significant to least significant).

Dmitry is very fond of all the digits of this number system, so he wants to see each of them at least once.

In one operation, he can:

- take any number $ x $ written on the board, increase it by $ 1 $ , and write the new value $ x + 1 $ on the board.

For example, $ p=5 $ and $ x=234_5 $ .

- Initially, the board contains the digits $ 2 $ , $ 3 $ and $ 4 $ ;
- Dmitry increases the number $ 234_5 $ by $ 1 $ and writes down the number $ 240_5 $ . On the board there are digits $ 0, 2, 3, 4 $ ;
- Dmitry increases the number $ 240_5 $ by $ 1 $ and writes down the number $ 241_5 $ . Now the board contains all the digits from $ 0 $ to $ 4 $ .

Your task is to determine the minimum number of operations required to make all the digits from $ 0 $ to $ p-1 $ appear on the board at least once.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^3 $ ) — the number of test cases. The descriptions of the input test cases follow.

The first line of description of each test case contains two integers $ n $ ( $ 1 \le n \le 100 $ ) and $ p $ ( $ 2 \le p \le 10^9 $ ) — the length of the number and the base of the number system.

The second line of the description of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < p $ ) — digits of $ x $ in number system with base $ p $

It is guaranteed that the number $ x $ does not contain leading zeros (that is, $ a_1>0 $ ).

## 输出格式

For each test case print a single integer — the minimum number of operations required for Dmitry to get all the digits on the board from $ 0 $ to $ p-1 $ .

It can be shown that this always requires a finite number of operations.

## 样例 #1

### 输入

```
11
2 3
1 2
4 2
1 1 1 1
6 6
1 2 3 4 5 0
5 2
1 0 1 0 1
3 10
1 2 3
5 1000
4 1 3 2 5
3 5
2 3 4
4 4
3 2 3 0
1 3
2
5 5
1 2 2 2 4
3 4
1 0 1
```

### 输出

```
1
1
0
0
7
995
2
1
1
1
2
```

