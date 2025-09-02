---
title: "Second-Price Auction"
layout: "post"
diff: 入门
pid: CF386A
tag: ['排序']
---

# Second-Price Auction

## 题目描述

In this problem we consider a special type of an auction, which is called the second-price auction. As in regular auction $ n $ bidders place a bid which is price a bidder ready to pay. The auction is closed, that is, each bidder secretly informs the organizer of the auction price he is willing to pay. After that, the auction winner is the participant who offered the highest price. However, he pay not the price he offers, but the highest price among the offers of other participants (hence the name: the second-price auction).

Write a program that reads prices offered by bidders and finds the winner and the price he will pay. Consider that all of the offered prices are different.

## 输入格式

The first line of the input contains $ n $ ( $ 2<=n<=1000 $ ) — number of bidders. The second line contains $ n $ distinct integer numbers $ p_{1},p_{2},...\ p_{n} $ , separated by single spaces ( $ 1<=p_{i}<=10000 $ ), where $ p_{i} $ stands for the price offered by the $ i $ -th bidder.

## 输出格式

The single output line should contain two integers: index of the winner and the price he will pay. Indices are 1-based.

## 样例 #1

### 输入

```
2
5 7

```

### 输出

```
2 5

```

## 样例 #2

### 输入

```
3
10 2 8

```

### 输出

```
1 8

```

## 样例 #3

### 输入

```
6
3 8 2 9 4 14

```

### 输出

```
6 9

```

