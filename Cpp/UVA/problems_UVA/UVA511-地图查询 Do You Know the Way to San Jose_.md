---
title: "地图查询 Do You Know the Way to San Jose?"
layout: "post"
diff: 普及+/提高
pid: UVA511
tag: []
---

# 地图查询 Do You Know the Way to San Jose?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=452

[PDF](https://uva.onlinejudge.org/external/5/p511.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA511/26e6330848064fd4751b76d2e2695dde09b88405.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA511/845b00d15b05066583111c7057b9e7a8acad2aee.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA511/f7fd5e5203f6bfd1fec53f1a6fbcdbda6d01c7ea.png)

## 样例 #1

### 输入

```
MAPS
BayArea -6.0 12.0 -11.0 5.0
SantaClara 4.0 9.0 -3.5 2.5
SanJoseRegion -3.0 10.0 11.0 3.0
CenterCoast -5.0 11.0 1.0 -8.0
SanMateo -5.5 4.0 -12.5 9.0
NCalif -13.0 -7.0 13.0 15.0
LOCATIONS
Monterey -4.0 2.0
SanJose -1.0 7.5
Fresno 7.0 0.1
SanFrancisco -10.0 8.6
SantaCruz -4.0 2.0
SanDiego 13.8 -19.3
REQUESTS
SanJose 3
SanFrancisco 2
Fresno 2
Stockton 1
SanDiego 2
SanJose 4
SantaCruz 3
END
```

### 输出

```
SanJose at detail level 3 using SanJoseRegion
SanFrancisco at detail level 2 using BayArea
Fresno at detail level 2 no map at that detail level; using NCalif
Stockton at detail level 1 unknown location
SanDiego at detail level 2 no map contains that location
SanJose at detail level 4 using SantaClara
SantaCruz at detail level 3 no map at that detail level; using CenterCoast
```

