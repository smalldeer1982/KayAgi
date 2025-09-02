---
title: "Umka and a Long Flight"
layout: "post"
diff: 普及+/提高
pid: CF1811D
tag: []
---

# Umka and a Long Flight

## 题目描述

The girl Umka loves to travel and participate in math olympiads. One day she was flying by plane to the next olympiad and out of boredom explored a huge checkered sheet of paper.

Denote the $ n $ -th Fibonacci number as $ F_n = \begin{cases} 1, & n = 0; \\ 1, & n = 1; \\ F_{n-2} + F_{n-1}, & n \ge 2. \end{cases} $

A checkered rectangle with a height of $ F_n $ and a width of $ F_{n+1} $ is called a Fibonacci rectangle of order $ n $ .

Umka has a Fibonacci rectangle of order $ n $ . Someone colored a cell in it at the intersection of the row $ x $ and the column $ y $ .

It is necessary to cut this rectangle exactly into $ n+1 $ squares in such way that

- the painted cell was in a square with a side of $ 1 $ ;
- there was at most one pair of squares with equal sides;
- the side of each square was equal to a Fibonacci number.

Will Umka be able to cut this rectangle in that way?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — number of test cases.

For each test case the integers $ n $ , $ x $ , $ y $ are given ( $ 1 \le n \le 44 $ , $ 1 \le x \le F_n $ , $ 1 \le y \le F_{n+1} $ ) — the order of the Fibonacci rectangle and the coordinates of the colored cell.

## 输出格式

For each test case, print "YES" if the answer is positive, and "NO" otherwise.

You can print "YES" and "NO" in any case (for example, the strings "yEs", "yes" and "Yes" will be recognized as a positive answer).

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811D/e5f4a8a6969129eb7406262bfa57aeda28c2a7af.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811D/f9a9f5019cb436c08d516ca2337b43e44d86aeca.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811D/b75cbdcea405d71b913c844c613b79782c601576.png) The first, third and fourth test cases.

## 样例 #1

### 输入

```
12
1 1 1
2 1 2
3 1 4
3 3 2
4 4 6
4 3 3
5 6 5
5 4 12
5 2 12
4 2 1
1 1 2
44 758465880 1277583853
```

### 输出

```
YES
NO
YES
YES
YES
NO
YES
NO
NO
YES
YES
NO
```

