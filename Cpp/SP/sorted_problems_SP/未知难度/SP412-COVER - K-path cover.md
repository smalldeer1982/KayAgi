---
title: "COVER - K-path cover"
layout: "post"
diff: 难度0
pid: SP412
tag: []
---

# COVER - K-path cover

## 输入格式

 First line of input contains number of test cases c (1<=c<=20). Each test case begins with k, number of vertices n and number of edges m (1<=k<=100, 1<=n<=10000, 0<=m<=1000000). Next n lines contain costs of the vertices, each of them is an integer from \[-100000,100000\]. Then m lines describing edges follow, each of them containing exactly two numbers representing its start and end vertices. Vertices are numbered from 1 to n.

## 输出格式

 For each test case output cost of the cheapest k-path cover. When given graph has no k-path cover output NONE.

## 样例 #1

### 输入

```
1
4 6 9
5
4
6
10
2
3
1 2
1 4
2 4
3 2
4 3
5 4
6 3
5 6
6 5
```

### 输出

```
33
```

