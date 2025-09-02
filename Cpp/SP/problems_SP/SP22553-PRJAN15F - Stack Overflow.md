---
title: "PRJAN15F - Stack Overflow"
layout: "post"
diff: 难度0
pid: SP22553
tag: []
---

# PRJAN15F - Stack Overflow

## 题目描述

初始有 $n$ 个空栈。有 $q$ 个操作：

1. `push i x`：把 $x$ 放进第 $i$ 个栈。
2. `pop i`：弹出第 $i$ 个栈的栈顶。如果第 $i$ 个栈已经空，那么忽略这个操作。
3. `put i j`：把第 $j$ 个栈放在第 $i$ 个栈上（不改变顺序）。
4. `top i`：输出第 $i$ 个栈的栈顶。

## 输入格式

第一行 $t$：表示有 $t$ 组数据。

接下来有 $t$ 组数据：

- 每组数据的第一行是 $n$ 和 $q$。

## 输出格式

每组数据的第一行是该组数据的编号。

以下为对于每个4操作的回答。

## 样例输入

```
1
3 18
push 1 1
push 2 2
push 3 3
push 3 4
top 1
top 2
top 3
put 1 3
pop 2
top 1
top 2
top 3
pop 1
top 1
pop 1
top 1
pop 1
top 1

```

## 样例输出

```
Case 1:
1
2
4
4
Empty!
Empty!
3
1
Empty!
```

## 说明/提示

$1\leq n\leq 10^4$。
$1\leq q\leq 5\times10^4$。

###### **翻译者 [90693](/user/90693)**。

