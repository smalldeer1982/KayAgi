---
title: "Karen and Supermarket"
layout: "post"
diff: 提高+/省选-
pid: CF815C
tag: ['动态规划 DP', '枚举']
---

# Karen and Supermarket

## 题目描述

On the way home, Karen decided to stop by the supermarket to buy some groceries.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815C/155b4f0d440b0d3ff60763603980cf23ed9ae97d.png)She needs to buy a lot of goods, but since she is a student her budget is still quite limited. In fact, she can only spend up to $ b $ dollars.

The supermarket sells $ n $ goods. The $ i $ -th good can be bought for $ c_{i} $ dollars. Of course, each good can only be bought once.

Lately, the supermarket has been trying to increase its business. Karen, being a loyal customer, was given $ n $ coupons. If Karen purchases the $ i $ -th good, she can use the $ i $ -th coupon to decrease its price by $ d_{i} $ . Of course, a coupon cannot be used without buying the corresponding good.

There is, however, a constraint with the coupons. For all $ i>=2 $ , in order to use the $ i $ -th coupon, Karen must also use the $ x_{i} $ -th coupon (which may mean using even more coupons to satisfy the requirement for that coupon).

Karen wants to know the following. What is the maximum number of goods she can buy, without exceeding her budget $ b $ ?

## 输入格式

The first line of input contains two integers $ n $ and $ b $ ( $ 1<=n<=5000 $ , $ 1<=b<=10^{9} $ ), the number of goods in the store and the amount of money Karen has, respectively.

The next $ n $ lines describe the items. Specifically:

- The $ i $ -th line among these starts with two integers, $ c_{i} $ and $ d_{i} $ ( $ 1<=d_{i}<c_{i}<=10^{9} $ ), the price of the $ i $ -th good and the discount when using the coupon for the $ i $ -th good, respectively.
- If $ i>=2 $ , this is followed by another integer, $ x_{i} $ ( $ 1<=x_{i}<i $ ), denoting that the $ x_{i} $ -th coupon must also be used before this coupon can be used.

## 输出格式

Output a single integer on a line by itself, the number of different goods Karen can buy, without exceeding her budget.

## 说明/提示

In the first test case, Karen can purchase the following $ 4 $ items:

- Use the first coupon to buy the first item for $ 10-9=1 $ dollar.
- Use the third coupon to buy the third item for $ 12-2=10 $ dollars.
- Use the fourth coupon to buy the fourth item for $ 20-18=2 $ dollars.
- Buy the sixth item for $ 2 $ dollars.

The total cost of these goods is $ 15 $ , which falls within her budget. Note, for example, that she cannot use the coupon on the sixth item, because then she should have also used the fifth coupon to buy the fifth item, which she did not do here.

In the second test case, Karen has enough money to use all the coupons and purchase everything.

## 样例 #1

### 输入

```
6 16
10 9
10 5 1
12 2 1
20 18 3
10 2 3
2 1 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 10
3 1
3 1 1
3 1 2
3 1 3
3 1 4

```

### 输出

```
5

```

