---
title: "Don't Try to Count"
layout: "post"
diff: 入门
pid: CF1881A
tag: []
---

# Don't Try to Count

## 题目描述

给定一个长度为 $n$ 的字符串 $x$，长度为 $m$ 的字符串 $s$，你可以进行下列操作：

- 将 字符串 $x$ 复制到字符串 $x$末尾。
例：`aba` $->$ `abaaba` $->$ `abaabaabaaba`。

询问最少进行多少次操作字符串 $s$ 为字符串 $x$ 的子串。

## 输入格式

输入的第一行包含一个整数 $t$，表示 $t$ 组数据。

每组数据第一行，包含两个数字 $n$ 和 $m$，分别表示字符串 $x$ 和 $s$ 的长度。

每组数据的第二行包含长度为 $n$ 的字符串 $x$。

每组数据的第三行包含长度为 $m$ 的字符串 $s$。

## 输出格式

对于每组数据，输出一个数字，表示字符串$s$作为子串 出现在 $x$ 中的最小操作数。如果不可能，则输出 $-1$。

## 样例 #1

### 输入

```
12
1 5
a
aaaaa
5 5
eforc
force
2 5
ab
ababa
3 5
aba
ababa
4 3
babb
bbb
5 1
aaaaa
a
4 2
aabb
ba
2 8
bk
kbkbkbkb
12 2
fjdgmujlcont
tf
2 2
aa
aa
3 5
abb
babba
1 19
m
mmmmmmmmmmmmmmmmmmm
```

### 输出

```
3
1
2
-1
1
0
1
3
1
0
2
5
```

