---
title: "Changing a String"
layout: "post"
diff: 普及/提高-
pid: CF56D
tag: []
---

# Changing a String

## 题目描述

这里有一个由大写字母构成的字符串 $s$，我们把他的长度表示为 $|s|$。在一次操作中，我们可以做这几种事情：

- 插入一个字符——我们可以在 $pos$ 位置上插入一个大写字母 $ch$（$1\le pos\le |s|+1$），此时字符串的 $pos$ 位置变成 $ch$ 字符，并且，其余字符将依次后移，字符串长度也要增加 $1$。
- 删除一个字符——将 $pos$ 位置上的字符删除，同样，其余字符移动，并且字符串长度减少 $1$。
- 替换一个字符——将 $pos$ 位置上的字符替换为大写字母 $ch$（$1\le pos\le |s|$），字符串长度不改变。

你的任务就是计算字符串 $s$ 通过上面的操作变到字符串 $t$ 最少花的步数，并且输出操作过程。

## 输入格式

第一行是字符串 $s$，第二行是字符串 $t$，两个字符串都只有大写字母，并且长度在 $[1, 1000]$ 间。

## 输出格式

第一行为最少移动次数 $k$，接下来 $k$ 行，按“操作名称 $pos$ $ch$”的格式输出。

## 样例 #1

### 输入

```
ABA
ABBBA

```

### 输出

```
2
INSERT 3 B
INSERT 4 B

```

## 样例 #2

### 输入

```
ACCEPTED
WRONGANSWER

```

### 输出

```
10
REPLACE 1 W
REPLACE 2 R
REPLACE 3 O
REPLACE 4 N
REPLACE 5 G
REPLACE 6 A
INSERT 7 N
INSERT 8 S
INSERT 9 W
REPLACE 11 R

```

