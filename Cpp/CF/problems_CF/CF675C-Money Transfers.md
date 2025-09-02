---
title: "Money Transfers"
layout: "post"
diff: 提高+/省选-
pid: CF675C
tag: []
---

# Money Transfers

## 题目描述

There are $ n $ banks in the city where Vasya lives, they are located in a circle, such that any two banks are neighbouring if their indices differ by no more than $ 1 $ . Also, bank $ 1 $ and bank $ n $ are neighbours if $ n&gt;1 $ . No bank is a neighbour of itself.

Vasya has an account in each bank. Its balance may be negative, meaning Vasya owes some money to this bank.

There is only one type of operations available: transfer some amount of money from any bank to account in any neighbouring bank. There are no restrictions on the size of the sum being transferred or balance requirements to perform this operation.

Vasya doesn't like to deal with large numbers, so he asks you to determine the minimum number of operations required to change the balance of each bank account to zero. It's guaranteed, that this is possible to achieve, that is, the total balance of Vasya in all banks is equal to zero.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of banks.

The second line contains $ n $ integers $ a_{i} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ), the $ i $ -th of them is equal to the initial balance of the account in the $ i $ -th bank. It's guaranteed that the sum of all $ a_{i} $ is equal to $ 0 $ .

## 输出格式

Print the minimum number of operations required to change balance in each bank to zero.

## 说明/提示

In the first sample, Vasya may transfer $ 5 $ from the first bank to the third.

In the second sample, Vasya may first transfer $ 1 $ from the third bank to the second, and then $ 1 $ from the second to the first.

In the third sample, the following sequence provides the optimal answer:

1. transfer $ 1 $ from the first bank to the second bank;
2. transfer $ 3 $ from the second bank to the third;
3. transfer $ 6 $ from the third bank to the fourth.

## 样例 #1

### 输入

```
3
5 0 -5

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4
-1 0 1 0

```

### 输出

```
2

```

## 样例 #3

### 输入

```
4
1 2 3 -6

```

### 输出

```
3

```

