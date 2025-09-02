---
title: "Choosing Balls"
layout: "post"
diff: 提高+/省选-
pid: CF264C
tag: []
---

# Choosing Balls

## 题目描述

There are $ n $ balls. They are arranged in a row. Each ball has a color (for convenience an integer) and an integer value. The color of the $ i $ -th ball is $ c_{i} $ and the value of the $ i $ -th ball is $ v_{i} $ .

Squirrel Liss chooses some balls and makes a new sequence without changing the relative order of the balls. She wants to maximize the value of this sequence.

The value of the sequence is defined as the sum of following values for each ball (where $ a $ and $ b $ are given constants):

- If the ball is not in the beginning of the sequence and the color of the ball is same as previous ball's color, add (the value of the ball) $ × $ $ a $ .
- Otherwise, add (the value of the ball) $ × $ $ b $ .

You are given $ q $ queries. Each query contains two integers $ a_{i} $ and $ b_{i} $ . For each query find the maximal value of the sequence she can make when $ a=a_{i} $ and $ b=b_{i} $ .

Note that the new sequence can be empty, and the value of an empty sequence is defined as zero.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1<=n<=10^{5}; 1<=q<=500 $ ). The second line contains $ n $ integers: $ v_{1},v_{2},...,v_{n} $ ( $ |v_{i}|<=10^{5} $ ). The third line contains $ n $ integers: $ c_{1},c_{2},...,c_{n} $ ( $ 1<=c_{i}<=n $ ).

The following $ q $ lines contain the values of the constants $ a $ and $ b $ for queries. The $ i $ -th of these lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ |a_{i}|,|b_{i}|<=10^{5} $ ).

In each line integers are separated by single spaces.

## 输出格式

For each query, output a line containing an integer — the answer to the query. The $ i $ -th line contains the answer to the $ i $ -th query in the input order.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first example, to achieve the maximal value:

- In the first query, you should select 1st, 3rd, and 4th ball.
- In the second query, you should select 3rd, 4th, 5th and 6th ball.
- In the third query, you should select 2nd and 4th ball.

Note that there may be other ways to achieve the maximal value.

## 样例 #1

### 输入

```
6 3
1 -2 3 4 0 -1
1 2 1 2 1 1
5 1
-2 1
1 0

```

### 输出

```
20
9
4

```

## 样例 #2

### 输入

```
4 1
-3 6 -1 2
1 2 3 1
1 -1

```

### 输出

```
5

```

