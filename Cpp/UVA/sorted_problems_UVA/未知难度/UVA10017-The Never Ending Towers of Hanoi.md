---
title: "The Never Ending Towers of Hanoi"
layout: "post"
diff: 难度0
pid: UVA10017
tag: []
---

# The Never Ending Towers of Hanoi

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=958

[PDF](https://uva.onlinejudge.org/external/100/p10017.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10017/c13ae044f4da91403c962c87039381b103785b52.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10017/358abeaf7f6673b3eba156cde5a203bcd0bb04f3.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10017/3c2796aef934ae78286f82ef29c032a0f93d90ed.png)

## 样例 #1

### 输入

```
64 2
8 45
0 0
```

### 输出

```
Problem #1
A=&gt; 64 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41
40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15
14 13 12 11 10 9 8 7 6 5 4 3 2 1
B=&gt;
C=&gt;
A=&gt; 64 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41
40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15
14 13 12 11 10 9 8 7 6 5 4 3 2
B=&gt; 1
C=&gt;
A=&gt; 64 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41
40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15
14 13 12 11 10 9 8 7 6 5 4 3
B=&gt; 1
C=&gt; 2
Problem #2
A=&gt; 8 7 6 5 4 3 2 1
B=&gt;
C=&gt;
A=&gt; 8 7 6 5 4 3 2
B=&gt; 1
C=&gt;
A=&gt; 8 7 6 5 4 3
B=&gt; 1
C=&gt; 2
A=&gt; 8 7 6 5 4 3
B=&gt;
C=&gt; 2 1
A=&gt; 8 7 6 5 4
B=&gt; 3
C=&gt; 2 1
A=&gt; 8 7 6 5 4 1
B=&gt; 3
C=&gt; 2
A=&gt; 8 7 6 5 4 1
B=&gt; 3 2
C=&gt;
A=&gt; 8 7 6 5 4
B=&gt; 3 2 1
C=&gt;
A=&gt; 8 7 6 5
B=&gt; 3 2 1
C=&gt; 4
A=&gt; 8 7 6 5
B=&gt; 3 2
C=&gt; 4 1
A=&gt; 8 7 6 5 2
B=&gt; 3
C=&gt; 4 1
A=&gt; 8 7 6 5 2 1
B=&gt; 3
C=&gt; 4
A=&gt; 8 7 6 5 2 1
B=&gt;
C=&gt; 4 3
A=&gt; 8 7 6 5 2
B=&gt; 1
C=&gt; 4 3
A=&gt; 8 7 6 5
B=&gt; 1
C=&gt; 4 3 2
A=&gt; 8 7 6 5
B=&gt;
C=&gt; 4 3 2 1
A=&gt; 8 7 6
B=&gt; 5
C=&gt; 4 3 2 1
A=&gt; 8 7 6 1
B=&gt; 5
C=&gt; 4 3 2
A=&gt; 8 7 6 1
B=&gt; 5 2
C=&gt; 4 3
A=&gt; 8 7 6
B=&gt; 5 2 1
C=&gt; 4 3
A=&gt; 8 7 6 3
B=&gt; 5 2 1
C=&gt; 4
A=&gt; 8 7 6 3
B=&gt; 5 2
C=&gt; 4 1
A=&gt; 8 7 6 3 2
B=&gt; 5
C=&gt; 4 1
A=&gt; 8 7 6 3 2 1
B=&gt; 5
C=&gt; 4
A=&gt; 8 7 6 3 2 1
B=&gt; 5 4
C=&gt;
A=&gt; 8 7 6 3 2
B=&gt; 5 4 1
C=&gt;
A=&gt; 8 7 6 3
B=&gt; 5 4 1
C=&gt; 2
A=&gt; 8 7 6 3
B=&gt; 5 4
C=&gt; 2 1
A=&gt; 8 7 6
B=&gt; 5 4 3
C=&gt; 2 1
A=&gt; 8 7 6 1
B=&gt; 5 4 3
C=&gt; 2
A=&gt; 8 7 6 1
B=&gt; 5 4 3 2
C=&gt;
A=&gt; 8 7 6
B=&gt; 5 4 3 2 1
C=&gt;
A=&gt; 8 7
B=&gt; 5 4 3 2 1
C=&gt; 6
A=&gt; 8 7
B=&gt; 5 4 3 2
C=&gt; 6 1
A=&gt; 8 7 2
B=&gt; 5 4 3
C=&gt; 6 1
A=&gt; 8 7 2 1
B=&gt; 5 4 3
C=&gt; 6
A=&gt; 8 7 2 1
B=&gt; 5 4
C=&gt; 6 3
A=&gt; 8 7 2
B=&gt; 5 4 1
C=&gt; 6 3
A=&gt; 8 7
B=&gt; 5 4 1
C=&gt; 6 3 2
A=&gt; 8 7
B=&gt; 5 4
C=&gt; 6 3 2 1
A=&gt; 8 7 4
B=&gt; 5
C=&gt; 6 3 2 1
A=&gt; 8 7 4 1
B=&gt; 5
C=&gt; 6 3 2
A=&gt; 8 7 4 1
B=&gt; 5 2
C=&gt; 6 3
A=&gt; 8 7 4
B=&gt; 5 2 1
C=&gt; 6 3
A=&gt; 8 7 4 3
B=&gt; 5 2 1
C=&gt; 6
A=&gt; 8 7 4 3
B=&gt; 5 2
C=&gt; 6 1
```

