---
title: "Generate a String"
layout: "post"
diff: 普及+/提高
pid: CF710E
tag: []
---

# Generate a String

## 题目描述

zscoder wants to generate an input file for some programming competition problem.

His input is a string consisting of $ n $ letters 'a'. He is too lazy to write a generator so he will manually generate the input in a text editor.

Initially, the text editor is empty. It takes him $ x $ seconds to insert or delete a letter 'a' from the text file and $ y $ seconds to copy the contents of the entire text file, and duplicate it.

zscoder wants to find the minimum amount of time needed for him to create the input file of exactly $ n $ letters 'a'. Help him to determine the amount of time needed to generate the input.

## 输入格式

The only line contains three integers $ n $ , $ x $ and $ y $ ( $ 1<=n<=10^{7} $ , $ 1<=x,y<=10^{9} $ ) — the number of letters 'a' in the input file and the parameters from the problem statement.

## 输出格式

Print the only integer $ t $ — the minimum amount of time needed to generate the input file.

## 样例 #1

### 输入

```
8 1 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
8 1 10

```

### 输出

```
8

```

