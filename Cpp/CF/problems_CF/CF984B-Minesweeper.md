---
title: "Minesweeper"
layout: "post"
diff: 普及-
pid: CF984B
tag: []
---

# Minesweeper

## 题目描述

One day Alex decided to remember childhood when computers were not too powerful and lots of people played only default games. Alex enjoyed playing Minesweeper that time. He imagined that he saved world from bombs planted by terrorists, but he rarely won.

Alex has grown up since then, so he easily wins the most difficult levels. This quickly bored him, and he thought: what if the computer gave him invalid fields in the childhood and Alex could not win because of it?

He needs your help to check it.

A Minesweeper field is a rectangle $ n \times m $ , where each cell is either empty, or contains a digit from $ 1 $ to $ 8 $ , or a bomb. The field is valid if for each cell:

- if there is a digit $ k $ in the cell, then exactly $ k $ neighboring cells have bombs.
- if the cell is empty, then all neighboring cells have no bombs.

Two cells are neighbors if they have a common side or a corner (i. e. a cell has at most $ 8 $ neighboring cells).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 100 $ ) — the sizes of the field.

The next $ n $ lines contain the description of the field. Each line contains $ m $ characters, each of them is "." (if this cell is empty), "\*" (if there is bomb in this cell), or a digit from $ 1 $ to $ 8 $ , inclusive.

## 输出格式

Print "YES", if the field is valid and "NO" otherwise.

You can choose the case (lower or upper) for each letter arbitrarily.

## 说明/提示

In the second example the answer is "NO" because, if the positions of the bombs are preserved, the first line of the field should be \*2\*1.

You can read more about Minesweeper in <a>Wikipedia's article</a>.

## 样例 #1

### 输入

```
3 3
111
1*1
111

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 4
*.*.
1211

```

### 输出

```
NO
```

