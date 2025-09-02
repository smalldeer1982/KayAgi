---
title: "Credit Card"
layout: "post"
diff: 普及+/提高
pid: CF893D
tag: []
---

# Credit Card

## 题目描述

Recenlty Luba got a credit card and started to use it. Let's consider $ n $ consecutive days Luba uses the card.

She starts with $ 0 $ money on her account.

In the evening of $ i $ -th day a transaction $ a_{i} $ occurs. If $ a_{i}&gt;0 $ , then $ a_{i} $ bourles are deposited to Luba's account. If $ a_{i}&lt;0 $ , then $ a_{i} $ bourles are withdrawn. And if $ a_{i}=0 $ , then the amount of money on Luba's account is checked.

In the morning of any of $ n $ days Luba can go to the bank and deposit any positive integer amount of burles to her account. But there is a limitation: the amount of money on the account can never exceed $ d $ .

It can happen that the amount of money goes greater than $ d $ by some transaction in the evening. In this case answer will be «-1».

Luba must not exceed this limit, and also she wants that every day her account is checked (the days when $ a_{i}=0 $ ) the amount of money on her account is non-negative. It takes a lot of time to go to the bank, so Luba wants to know the minimum number of days she needs to deposit some money to her account (if it is possible to meet all the requirements). Help her!

## 输入格式

The first line contains two integers $ n $ , $ d $ ( $ 1<=n<=10^{5} $ , $ 1<=d<=10^{9} $ ) —the number of days and the money limitation.

The second line contains $ n $ integer numbers $ a_{1},a_{2},...\ a_{n} $ ( $ -10^{4}<=a_{i}<=10^{4} $ ), where $ a_{i} $ represents the transaction in $ i $ -th day.

## 输出格式

Print -1 if Luba cannot deposit the money to her account in such a way that the requirements are met. Otherwise print the minimum number of days Luba has to deposit money.

## 样例 #1

### 输入

```
5 10
-1 5 0 -5 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3 4
-10 0 20

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
5 10
-5 0 10 -11 0

```

### 输出

```
2

```

