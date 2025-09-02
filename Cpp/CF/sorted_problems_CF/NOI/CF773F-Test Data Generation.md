---
title: "Test Data Generation"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF773F
tag: []
---

# Test Data Generation

## 题目描述

Test data generation is not an easy task! Often, generating big random test cases is not enough to ensure thorough testing of solutions for correctness.

For example, consider a problem from an old Codeforces round. Its input format looks roughly as follows:

The first line contains a single integer $ n $ ( $ 1<=n<=max_{n} $ ) — the size of the set. The second line contains $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=max_{a} $ ) — the elements of the set in increasing order.

If you don't pay attention to the problem solution, it looks fairly easy to generate a good test case for this problem. Let $ n=max_{n} $ , take random distinct $ a_{i} $ from 1 to $ max_{a} $ , sort them... Soon you understand that it's not that easy.

Here is the actual problem solution. Let $ g $ be the greatest common divisor of $ a_{1},a_{2},...,a_{n} $ . Let $ x=a_{n}/g-n $ . Then the correct solution outputs "Alice" if $ x $ is odd, and "Bob" if $ x $ is even.

Consider two wrong solutions to this problem which differ from the correct one only in the formula for calculating $ x $ .

The first wrong solution calculates $ x $ as $ x=a_{n}/g $ (without subtracting $ n $ ).

The second wrong solution calculates $ x $ as $ x=a_{n}-n $ (without dividing by $ g $ ).

A test case is interesting if it makes both wrong solutions output an incorrect answer.

Given $ max_{n} $ , $ max_{a} $ and $ q $ , find the number of interesting test cases satisfying the constraints, and output it modulo $ q $ .

## 输入格式

The only line contains three integers $ max_{n} $ , $ max_{a} $ and $ q $ ( $ 1<=max_{n}<=30000 $ ; $ max_{n}<=max_{a}<=10^{9} $ ; $ 10^{4}<=q<=10^{5}+129 $ ).

## 输出格式

Output a single integer — the number of test cases which satisfy the constraints and make both wrong solutions output an incorrect answer, modulo $ q $ .

## 说明/提示

In the first example, interesting test cases look as follows:

`<br></br>1              1              1              3<br></br>2              4              6              2 4 6<br></br>`

## 样例 #1

### 输入

```
3 6 100000

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6 21 100129

```

### 输出

```
154

```

## 样例 #3

### 输入

```
58 787788 50216

```

### 输出

```
46009

```

