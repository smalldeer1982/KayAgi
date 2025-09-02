---
title: "Sqrt Inequality"
layout: "post"
diff: 入门
pid: AT_panasonic2020_c
tag: []
---

# Sqrt Inequality

## 题目描述

[problemUrl]: https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_c

$ \sqrt{a}\ +\ \sqrt{b}\ <\ \sqrt{c} $ ですか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ a\ b\ c $

## 输出格式

$ \sqrt{a}\ +\ \sqrt{b}\ <\ \sqrt{c} $ ならば `Yes`、そうでないならば `No` と出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ a,\ b,\ c\ \leq\ 10^9 $
- 入力は全て整数である。

### Sample Explanation 1

$ \sqrt{2}\ +\ \sqrt{3}\ <\ \sqrt{9} $ ではありません。

### Sample Explanation 2

$ \sqrt{2}\ +\ \sqrt{3}\ <\ \sqrt{10} $ です。

## 样例 #1

### 输入

```
2 3 9
```

### 输出

```
No
```

## 样例 #2

### 输入

```
2 3 10
```

### 输出

```
Yes
```

