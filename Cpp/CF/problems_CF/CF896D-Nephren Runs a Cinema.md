---
title: "Nephren Runs a Cinema"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF896D
tag: []
---

# Nephren Runs a Cinema

## 题目描述

Lakhesh loves to make movies, so Nephren helps her run a cinema. We may call it No. 68 Cinema.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF896D/c4ab5c88eb89d5d2f9a45a0cad227d56ef890e10.png)

However, one day, the No. 68 Cinema runs out of changes (they don't have 50-yuan notes currently), but Nephren still wants to start their business. (Assume that yuan is a kind of currency in Regulu Ere.)

There are three types of customers: some of them bring exactly a 50-yuan note; some of them bring a 100-yuan note and Nephren needs to give a 50-yuan note back to him/her; some of them bring VIP cards so that they don't need to pay for the ticket.

Now $ n $ customers are waiting outside in queue. Nephren wants to know how many possible queues are there that they are able to run smoothly (i.e. every customer can receive his/her change), and that the number of 50-yuan notes they have after selling tickets to all these customers is between $ l $ and $ r $ , inclusive. Two queues are considered different if there exists a customer whose type is different in two queues. As the number can be large, please output the answer modulo $ p $ .

## 输入格式

One line containing four integers $ n $ ( $ 1<=n<=10^{5}) $ , $ p $ ( $ 1<=p<=2·10^{9}) $ , $ l $ and $ r $ ( $ 0<=l<=r<=n $ ).

## 输出格式

One line indicating the answer modulo $ p $ .

## 说明/提示

We use A, B and C to indicate customers with 50-yuan notes, customers with 100-yuan notes and customers with VIP cards respectively.

For the first sample, the different possible queues that there are $ 2 $ 50-yuan notes left are AAAB, AABA, ABAA, AACC, ACAC, ACCA, CAAC, CACA and CCAA, and the different possible queues that there are $ 3 $ 50-yuan notes left are AAAC, AACA, ACAA and CAAA. So there are $ 13 $ different queues satisfying the first sample. Similarly, there are $ 35 $ different queues satisfying the second sample.

## 样例 #1

### 输入

```
4 97 2 3

```

### 输出

```
13

```

## 样例 #2

### 输入

```
4 100 0 4

```

### 输出

```
35

```

