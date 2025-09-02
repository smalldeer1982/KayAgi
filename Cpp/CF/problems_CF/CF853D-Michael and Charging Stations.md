---
title: "Michael and Charging Stations"
layout: "post"
diff: 普及+/提高
pid: CF853D
tag: []
---

# Michael and Charging Stations

## 题目描述

Michael has just bought a new electric car for moving across city. Michael does not like to overwork, so each day he drives to only one of two his jobs.

Michael's day starts from charging his electric car for getting to the work and back. He spends $ 1000 $ burles on charge if he goes to the first job, and $ 2000 $ burles if he goes to the second job.

On a charging station he uses there is a loyalty program that involves bonus cards. Bonus card may have some non-negative amount of bonus burles. Each time customer is going to buy something for the price of $ x $ burles, he is allowed to pay an amount of $ y $ ( $ 0<=y<=x $ ) burles that does not exceed the bonus card balance with bonus burles. In this case he pays $ x-y $ burles with cash, and the balance on the bonus card is decreased by $ y $ bonus burles.

If customer pays whole price with cash (i.e., $ y=0 $ ) then 10% of price is returned back to the bonus card. This means that bonus card balance increases by ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF853D/b63fc695c9b8ab1ed954e5b28e2ca9818fa92a5c.png) bonus burles. Initially the bonus card balance is equal to 0 bonus burles.

Michael has planned next $ n $ days and he knows how much does the charge cost on each of those days. Help Michael determine the minimum amount of burles in cash he has to spend with optimal use of bonus card. Assume that Michael is able to cover any part of the price with cash in any day. It is not necessary to spend all bonus burles at the end of the given period.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=300000 $ ), the number of days Michael has planned.

Next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ a_{i}=1000 $ or $ a_{i}=2000 $ ) with $ a_{i} $ denoting the charging cost at the day $ i $ .

## 输出格式

Output the minimum amount of burles Michael has to spend.

## 说明/提示

In the first sample case the most optimal way for Michael is to pay for the first two days spending 3000 burles and get 300 bonus burles as return. After that he is able to pay only 700 burles for the third days, covering the rest of the price with bonus burles.

In the second sample case the most optimal way for Michael is to pay the whole price for the first five days, getting 1000 bonus burles as return and being able to use them on the last day without paying anything in cash.

## 样例 #1

### 输入

```
3
1000 2000 1000

```

### 输出

```
3700

```

## 样例 #2

### 输入

```
6
2000 2000 2000 2000 2000 1000

```

### 输出

```
10000

```

