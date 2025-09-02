---
title: "Supermarket"
layout: "post"
diff: 入门
pid: CF919A
tag: ['数学', '贪心', '排序']
---

# Supermarket

## 题目描述

We often go to supermarkets to buy some fruits or vegetables, and on the tag there prints the price for a kilo. But in some supermarkets, when asked how much the items are, the clerk will say that $ a $ yuan for $ b $ kilos (You don't need to care about what "yuan" is), the same as $ a/b $ yuan for a kilo.

Now imagine you'd like to buy $ m $ kilos of apples. You've asked $ n $ supermarkets and got the prices. Find the minimum cost for those apples.

You can assume that there are enough apples in all supermarkets.

## 输入格式

The first line contains two positive integers $ n $ and $ m $ ( $ 1<=n<=5000 $ , $ 1<=m<=100 $ ), denoting that there are $ n $ supermarkets and you want to buy $ m $ kilos of apples.

The following $ n $ lines describe the information of the supermarkets. Each line contains two positive integers $ a,b $ ( $ 1<=a,b<=100 $ ), denoting that in this supermarket, you are supposed to pay $ a $ yuan for $ b $ kilos of apples.

## 输出格式

The only line, denoting the minimum cost for $ m $ kilos of apples. Please make sure that the absolute or relative error between your answer and the correct answer won't exceed $ 10^{-6} $ .

Formally, let your answer be $ x $ , and the jury's answer be $ y $ . Your answer is considered correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919A/9c418c1ac059184ac2ec8107da47a63db7a44091.png).

## 说明/提示

In the first sample, you are supposed to buy $ 5 $ kilos of apples in supermarket $ 3 $ . The cost is $ 5/3 $ yuan.

In the second sample, you are supposed to buy $ 1 $ kilo of apples in supermarket $ 2 $ . The cost is $ 98/99 $ yuan.

## 样例 #1

### 输入

```
3 5
1 2
3 4
1 3

```

### 输出

```
1.66666667

```

## 样例 #2

### 输入

```
2 1
99 100
98 99

```

### 输出

```
0.98989899

```

