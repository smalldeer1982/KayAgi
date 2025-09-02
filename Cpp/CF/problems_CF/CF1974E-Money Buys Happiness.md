---
title: "Money Buys Happiness"
layout: "post"
diff: 普及/提高-
pid: CF1974E
tag: ['动态规划 DP']
---

# Money Buys Happiness

## 题目描述

Being a physicist, Charlie likes to plan his life in simple and precise terms.

For the next $ m $ months, starting with no money, Charlie will work hard and earn $ x $ pounds per month. For the $ i $ -th month $ (1 \le i \le m) $ , there'll be a single opportunity of paying cost $ c_i $ pounds to obtain happiness $ h_i $ .

Borrowing is not allowed. Money earned in the $ i $ -th month can only be spent in a later $ j $ -th month ( $ j>i $ ).

Since physicists don't code, help Charlie find the maximum obtainable sum of happiness.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case contains two integers, $ m $ and $ x $ ( $ 1 \le m \le 50 $ , $ 1 \le x \le 10^8 $ ) — the total number of months and the monthly salary.

The $ i $ -th of the following $ m $ lines contains two integers, $ c_i $ and $ h_i $ ( $ 0 \le c_i \le 10^8 $ , $ 1 \le h_i \le 10^3 $ ) — the cost and happiness on offer for the $ i $ -th month. Note that some happiness may be free ( $ c_i=0 $ for some $ i $ 's).

It is guaranteed that the sum of $ \sum_i h_i $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print a single integer, the maximum sum of happiness Charlie could obtain.

## 说明/提示

In the first test case, Charlie only gets paid at the end of the month, so is unable to afford anything.

In the second test case, Charlie obtains the free happiness in the first month.

In the third test case, it's optimal for Charlie to buy happiness in the second month. Even with money left at the end, Charlie could not go back in time to obtain the happiness on offer in the first month.

## 样例 #1

### 输入

```
7
1 10
1 5
2 80
0 10
200 100
3 100
70 100
100 200
150 150
5 8
3 1
5 3
3 4
1 5
5 3
2 5
1 5
2 1
5 3
2 5
2 4
4 1
5 1
3 4
5 2
2 1
1 2
3 5
3 2
3 2
```

### 输出

```
0
10
200
15
1
9
9
```

