---
title: "Department of Redundancy Department"
layout: "post"
diff: 难度0
pid: UVA219
tag: []
---

# Department of Redundancy Department

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=155

[PDF](https://uva.onlinejudge.org/external/2/p219.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA219/3d6459b1e8bd47eb09d6653f3bc70892d6cc7bcf.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA219/52ea9935f70c958e187c26260c862b1cb33124c5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA219/c9417ca74628d56bf5e5143dd2d7dcc6196cce3d.png)

## 样例 #1

### 输入

```
3
A-&gt;BD
BD-&gt;C
A-&gt;C
6
P-&gt;RST
VRT-&gt;SQP
PS-&gt;T
Q-&gt;TR
QS-&gt;P
SR-&gt;V
5
A-&gt;B
A-&gt;C
B-&gt;D
C-&gt;D
A-&gt;D
3
A-&gt;B
B-&gt;C
A-&gt;D
0
```

### 输出

```
Set number 1
FD 3 is redundant using FDs: 1 2
Set number 2
FD 3 is redundant using FDs: 1
FD 5 is redundant using FDs: 4 6 2
Set number 3
FD 5 is redundant using FDs: 1 3
--OR--
FD 5 is redundant using FDs: 2 4
Set number 4
No redundant FDs.
```

