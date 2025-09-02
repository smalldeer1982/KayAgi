---
title: "STARSBC - Star"
layout: "post"
diff: 难度0
pid: SP25158
tag: []
---

# STARSBC - Star

## 题目描述

Fernando won a compass for his birthday, and now his favorite hobby is drawing stars: ﬁrst, he marks **N** points on a circumference, dividing it into **N** equal arcs; then, he connects each point to the _k-th_ next point, until returning to the ﬁrst point.  
  
 Depending on the value of _k_, Fernando may or may not reach all points marked on the circumference; when that happens, the star is called complete. For example, when **N** = 8, the possible stars are shown in the ﬁgure below. Stars (a) and (c) are complete, while stars (b) and (d) are not.

![Stars for N=8 and k in {1-4}](https://cdn.luogu.com.cn/upload/vjudge_pic/SP25158/1c87a031cb5d728512d67c9e5c7626fa6db689ea.png)

Depending on the value of **N**, it may be possible to draw many diﬀerent stars; Fernando asked you to write a program that, given **N**, determines the number of complete stars he can draw.

## 输入格式

The input contains several test cases. Each test case contains a single line, containing a single integer **N** (3 N < 2 $ ^{31} $ ), indicating the number of arcs in which the circumference was divided.

## 输出格式

For each test case, your program must print a single line containing a single integer, indicating the number of complete stars that can be drawn.

## 样例 #1

### 输入

```
3\n4\n5\n18\n36\n360\n2147483647
```

### 输出

```
1\n1\n2\n3\n6\n48\n1073741823
\n
```

