---
title: "Free Market"
layout: "post"
diff: 省选/NOI-
pid: CF364B
tag: ['贪心']
---

# Free Market

## 题目描述

John Doe has recently found a "Free Market" in his city — that is the place where you can exchange some of your possessions for other things for free.

John knows that his city has $ n $ items in total (each item is unique). You can bring any number of items to the market and exchange them for any other one. Note that each item is one of a kind and that means that you cannot exchange set $ {a,b} $ for set $ {v,a} $ . However, you can always exchange set $ x $ for any set $ y $ , unless there is item $ p $ , such that $ p $ occurs in $ x $ and $ p $ occurs in $ y $ .

For each item, John knows its value $ c_{i} $ . John's sense of justice doesn't let him exchange a set of items $ x $ for a set of items $ y $ , if $ s(x)+d&lt;s(y) $ ( $ s(x) $ is the total price of items in the set $ x $ ).

During one day John can exchange only one set of items for something else. Initially, he has no items. John wants to get a set of items with the maximum total price. Find the cost of such set and the minimum number of days John can get it in.

## 输入格式

The first line contains two space-separated integers $ n $ , $ d $ ( $ 1<=n<=50 $ , $ 1<=d<=10^{4} $ ) — the number of items on the market and John's sense of justice value, correspondingly. The second line contains $ n $ space-separated integers $ c_{i} $ ( $ 1<=c_{i}<=10^{4} $ ).

## 输出格式

Print two space-separated integers: the maximum possible price in the set of items John can get and the minimum number of days needed to get such set.

## 说明/提示

In the first sample John can act like this:

- Take the first item ( $ 1-0<=2 $ ).
- Exchange the first item for the second one ( $ 3-1<=2 $ ).
- Take the first item ( $ 1-0<=2 $ ).

## 样例 #1

### 输入

```
3 2
1 3 10

```

### 输出

```
4 3

```

## 样例 #2

### 输入

```
3 5
1 2 3

```

### 输出

```
6 2

```

## 样例 #3

### 输入

```
10 10000
10000 9999 1 10000 10000 10000 1 2 3 4

```

### 输出

```
50010 6

```

