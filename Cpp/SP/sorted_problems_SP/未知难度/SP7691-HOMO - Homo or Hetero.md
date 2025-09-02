---
title: "HOMO - Homo or Hetero"
layout: "post"
diff: 难度0
pid: SP7691
tag: []
---

# HOMO - Homo or Hetero

## 题目描述

考虑一个具有两个操作的数列：
1. insert number — 在数列末尾加入一个数字。
2. delete number — 将数列的第一个数字删除。如果数列里没有这个数字，那么不会发生变化。

例如：把数字4加入数列 [1, 2, 1] 的结果是 [1, 2, 1, 4] 。如果我们将数列里的1删除，我们会得到 [2, 1, 4] 。但是如果我们删除数列 [1, 2, 1, 4] 中的3，数列将不会有变化。

当数列含有至少两个相同的数字时，这个数列被称为 homogeneous ，当数列含有至少两个不同的数字时，这个数列被称为 heterogeneous 。例如：数列 [2, 2] 是 homogeneous 的，数列 [2, 1, 4] 是 heterogeneous 的，数列 [1, 2, 1, 4] 两个都是，空数列两个都不是。

编写一个程序，处理在列表中的插入和删除并且在每次操作后输出目前序列是 homogeneous 的还是 heterogeneous 的。（数列最初是空的）

## 输入格式

输入的第一行是一个数字 n ，代表了操作的数量。

接下来的 n 行每行包含一个操作，操作包含一个词“insert” 或“delete” 接着是一个数字 k —操作参数。

## 输出格式

对于每个操作输出一行，包含一个描述当前数列状态的单词：
- “both”— 这个数列既是 homogeneous 的也是 heterogeneous 的。
- “homo”— 这个数列是 homogeneous 的但不是 heterogeneous 的。
- “hetero”— 这个数列是 heterogeneous 的但不是 homogeneous 的。
- “neither”— 这个数列既不是 homogeneous 的也不是 heterogeneous 的。

## 样例 #1

### 输入

```
11
insert 1
insert 2
insert 1
insert 4
delete 1
delete 3
delete 2
delete 1
insert 4
delete 4
delete 4
```

### 输出

```
neither
hetero
both
both
hetero
hetero
hetero
neither
homo
neither
neither
```

