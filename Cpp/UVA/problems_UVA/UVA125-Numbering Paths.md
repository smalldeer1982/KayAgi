---
title: "Numbering Paths"
layout: "post"
diff: 普及+/提高
pid: UVA125
tag: []
---

# Numbering Paths

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=61

[PDF](https://uva.onlinejudge.org/external/1/p125.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA125/2c01b1b3863b0e262ebdab9e49d0d869d64c657f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA125/1407cfa4ba0be873f9fa90f207289053a0315d27.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA125/021959b0ec72154c8b191fe9fe01107113a492d7.png)

## 样例 #1

### 输入

```
7 
0 1 0 2 0 4 2 4 
2 3 3 1 4 3

5
0 2 0 1 1 5 2 5 2 1

9
0 1 0 2 0 3 0 4 1 4 
2 1 2 0 3 0 3 1
```

### 输出

```
matrix for city 0
0 4 1 3 2
0 0 0 0 0
0 2 0 2 1
0 1 0 0 0
0 1 0 1 0
matrix for city 1
0 2 1 0 0 3
0 0 0 0 0 1
0 1 0 0 0 2
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
matrix for city 2
-1 -1 -1 -1 -1
0 0 0 0 1
-1 -1 -1 -1 -1
-1 -1 -1 -1 -1
0 0 0 0 0
```

