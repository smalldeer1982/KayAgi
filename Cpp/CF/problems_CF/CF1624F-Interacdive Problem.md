---
title: "Interacdive Problem"
layout: "post"
diff: 普及+/提高
pid: CF1624F
tag: []
---

# Interacdive Problem

## 题目描述

This problem is interactive.

We decided to play a game with you and guess the number $ x $ ( $ 1 \le x < n $ ), where you know the number $ n $ .

You can make queries like this:

- + c: this command assigns $ x = x + c $ ( $ 1 \le c < n $ ) and then returns you the value $ \lfloor\frac{x}{n}\rfloor $ ( $ x $ divide by $ n $ and round down).

You win if you guess the current number with no more than $ 10 $ queries.

## 输出格式

The interaction begins by reading an integer $ n $ ( $ 2 < n \le 1000 $ ), which is written in the input data on its own line.

Then you can make no more than $ 10 $ queries. To make a query, print on a separate line:

- + c: this command will assign $ x = x + c $ ( $ 1 \le c < n $ ) and then print $ \lfloor\frac{x}{n}\rfloor $ (divide $ x $ by $ n $ and round down) on a separate line.

Print the answer, like the queries, on a separate line. The answer doesn't count in number of queries. To output it, use the following format:

- ! x: the current value of $ x $ .

After that, your program should exit.

You have to use a flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout), in Java — System.out.flush(), in Pascal — flush(output) and in Python — sys.stdout.flush().

Note that the interactor is not responsive.

To make a hack, use the following format: a single line must contain two numbers $ x $ and $ n $ , separated by a space.

## 说明/提示

In the first sample initially $ x = 2 $ . After the first query $ x = 3 $ , $ \lfloor\frac{x}{n}\rfloor = 1 $ .

In the second sample also initially $ x = 2 $ . After the first query $ x = 3 $ , $ \lfloor\frac{x}{n}\rfloor = 0 $ . After the second query $ x = 4 $ , $ \lfloor\frac{x}{n}\rfloor = 0 $ . After the third query $ x=5 $ , $ \lfloor\frac{x}{n}\rfloor = 1 $ .

## 样例 #1

### 输入

```
3

1
```

### 输出

```
+ 1

! 3
```

## 样例 #2

### 输入

```
5

0

0

1
```

### 输出

```
+ 1

+ 1

+ 1

! 5
```

## 样例 #3

### 输入

```
10

0

0

1

2
```

### 输出

```
+ 2

+ 2

+ 3

+ 8

! 20
```

