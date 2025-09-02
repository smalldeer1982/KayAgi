---
title: "Identifying Concurrent Events"
layout: "post"
diff: 难度0
pid: UVA334
tag: []
---

# Identifying Concurrent Events

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=270

[PDF](https://uva.onlinejudge.org/external/3/p334.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA334/d3a2a163b237d8f161fb0222bd5d2789025c9003.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA334/3734d200897b54463485573c360b3c7134b30834.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA334/0c728b3d45cf21287f65b755ff5b67d57755aa2f.png)

## 样例 #1

### 输入

```
2
2 e1 e2
2 e3 e4
1
e3 e1
3
3 one two three
2 four five
3 six seven eight
2
one four
five six
1
3 x y zee
0
2
2 alpha beta
1 gamma
1
gamma beta
0
```

### 输出

```
Case 1, 2 concurrent events:
(e1,e4) (e2,e4)
Case 2, 10 concurrent events:
(two,four) (two,five)
Case 3, no concurrent events.
Case 4, 1 concurrent events:
(alpha,gamma)
```

