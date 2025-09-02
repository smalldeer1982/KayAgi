---
title: "Coupons and Discounts"
layout: "post"
diff: 普及/提高-
pid: CF731B
tag: []
---

# Coupons and Discounts

## 题目描述

The programming competition season has already started and it's time to train for ICPC. Sereja coaches his teams for a number of year and he knows that to get ready for the training session it's not enough to prepare only problems and editorial. As the training sessions lasts for several hours, teams become hungry. Thus, Sereja orders a number of pizzas so they can eat right after the end of the competition.

Teams plan to train for $ n $ times during $ n $ consecutive days. During the training session Sereja orders exactly one pizza for each team that is present this day. He already knows that there will be $ a_{i} $ teams on the $ i $ -th day.

There are two types of discounts in Sereja's favourite pizzeria. The first discount works if one buys two pizzas at one day, while the second is a coupon that allows to buy one pizza during two consecutive days (two pizzas in total).

As Sereja orders really a lot of pizza at this place, he is the golden client and can use the unlimited number of discounts and coupons of any type at any days.

Sereja wants to order exactly $ a_{i} $ pizzas on the $ i $ -th day while using only discounts and coupons. Note, that he will never buy more pizzas than he need for this particular day. Help him determine, whether he can buy the proper amount of pizzas each day if he is allowed to use only coupons and discounts. Note, that it's also prohibited to have any active coupons after the end of the day $ n $ .

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the number of training sessions.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 0<=a_{i}<=10000 $ ) — the number of teams that will be present on each of the days.

## 输出格式

If there is a way to order pizzas using only coupons and discounts and do not buy any extra pizzas on any of the days, then print "YES" (without quotes) in the only line of output. Otherwise, print "NO" (without quotes).

## 说明/提示

In the first sample, Sereja can use one coupon to buy one pizza on the first and the second days, one coupon to buy pizza on the second and the third days and one discount to buy pizzas on the fourth days. This is the only way to order pizzas for this sample.

In the second sample, Sereja can't use neither the coupon nor the discount without ordering an extra pizza. Note, that it's possible that there will be no teams attending the training sessions on some days.

## 样例 #1

### 输入

```
4
1 2 1 2

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3
1 0 1

```

### 输出

```
NO

```

