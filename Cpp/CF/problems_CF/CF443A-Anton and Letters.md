---
title: "Anton and Letters"
layout: "post"
diff: 入门
pid: CF443A
tag: []
---

# Anton and Letters

## 题目描述

Recently, Anton has found a set. The set consists of small English letters. Anton carefully wrote out all the letters from the set in one line, separated by a comma. He also added an opening curved bracket at the beginning of the line and a closing curved bracket at the end of the line.

Unfortunately, from time to time Anton would forget writing some letter and write it again. He asks you to count the total number of distinct letters in his set.

## 输入格式

The first and the single line contains the set of letters. The length of the line doesn't exceed 1000. It is guaranteed that the line starts from an opening curved bracket and ends with a closing curved bracket. Between them, small English letters are listed, separated by a comma. Each comma is followed by a space.

## 输出格式

Print a single number — the number of distinct letters in Anton's set.

## 样例 #1

### 输入

```
{a, b, c}

```

### 输出

```
3

```

## 样例 #2

### 输入

```
{b, a, b, a}

```

### 输出

```
2

```

## 样例 #3

### 输入

```
{}

```

### 输出

```
0

```

