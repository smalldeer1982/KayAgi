---
title: "Opposites Attract"
layout: "post"
diff: 入门
pid: CF131B
tag: []
---

# Opposites Attract

## 题目描述

Everybody knows that opposites attract. That is the key principle of the "Perfect Matching" dating agency. The "Perfect Matching" matchmakers have classified each registered customer by his interests and assigned to the $ i $ -th client number $ t_{i} $ ( $ -10<=t_{i}<=10 $ ). Of course, one number can be assigned to any number of customers.

"Perfect Matching" wants to advertise its services and publish the number of opposite couples, that is, the couples who have opposite values of $ t $ . Each couple consists of exactly two clients. The customer can be included in a couple an arbitrary number of times. Help the agency and write the program that will find the sought number by the given sequence $ t_{1},t_{2},...,t_{n} $ . For example, if $ t=(1,-1,1,-1) $ , then any two elements $ t_{i} $ and $ t_{j} $ form a couple if $ i $ and $ j $ have different parity. Consequently, in this case the sought number equals 4.

Of course, a client can't form a couple with him/herself.

## 输入格式

The first line of the input data contains an integer $ n $ ( $ 1<=n<=10^{5} $ ) which represents the number of registered clients of the "Couple Matching". The second line contains a sequence of integers $ t_{1},t_{2},...,t_{n} $ ( $ -10<=t_{i}<=10 $ ), $ t_{i} $ — is the parameter of the $ i $ -th customer that has been assigned to the customer by the result of the analysis of his interests.

## 输出格式

Print the number of couples of customs with opposite $ t $ . The opposite number for $ x $ is number $ -x $ ( $ 0 $ is opposite to itself). Couples that only differ in the clients' order are considered the same.

Note that the answer to the problem can be large enough, so you must use the 64-bit integer type for calculations. Please, do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I64d specificator.

## 说明/提示

In the first sample the couples of opposite clients are: (1,2), (1,5) и (3,4).

In the second sample any couple of clients is opposite.

## 样例 #1

### 输入

```
5
-3 3 0 0 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
0 0 0

```

### 输出

```
3

```

