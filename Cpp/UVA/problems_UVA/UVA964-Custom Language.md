---
title: "Custom Language"
layout: "post"
diff: 难度0
pid: UVA964
tag: []
---

# Custom Language

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=905

[PDF](https://uva.onlinejudge.org/external/9/p964.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA964/018d998a23f8b73c9fab0b695d3e9653b3bb828a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA964/eabf9ab76458fa41d9e76e3caefbb73ae1e8d556.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA964/b5ccedc8717b57fd7d337ad023152573813eea5d.png)

## 样例 #1

### 输入

```
READ
POP num
PUSH 2
POP x
PUSH num
PUSH 2
SUB
JUMPPOS 31
PUSH num
PUSH x
SUB
DUP
JUMPZERO 28
JUMPPOS 28
PUSH x
PUSH num
DIV
PUSH x
MUL
PUSH num
SUB
JUMPZERO 31
PUSH x
PUSH 1
ADD
POP x
JUMP 9
PUSH 1
WRITE
JUMP 33
PUSH 0
WRITE
#
7
#
PUSH undefined
WRITE
#
#
```

### 输出

```
1
#
ABORTED
#
```

