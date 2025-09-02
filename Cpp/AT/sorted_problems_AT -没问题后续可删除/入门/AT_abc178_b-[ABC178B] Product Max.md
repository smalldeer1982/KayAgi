---
title: "[ABC178B] Product Max"
layout: "post"
diff: 入门
pid: AT_abc178_b
tag: []
---

# [ABC178B] Product Max

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc178/tasks/abc178_b

整数 $ a,b,c,d $ が与えられます。 $ a\ \leq\ x\ \leq\ b,\ c\leq\ y\ \leq\ d $ を満たす整数 $ x,y $ について、$ x\ \times\ y $ の最大値はいくつですか。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ a $ $ b $ $ c $ $ d $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ -10^9\ \leq\ a\ \leq\ b\ \leq\ 10^9 $
- $ -10^9\ \leq\ c\ \leq\ d\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ x=1,y=1 $ のとき $ x\ \times\ y=1 $、$ x=2,y=1 $ のとき $ x\ \times\ y=2 $ であるため、答えは $ 2 $ です。

### Sample Explanation 2

答えが負になることもあります。

## 样例 #1

### 输入

```
1 2 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 5 -4 -2
```

### 输出

```
-6
```

## 样例 #3

### 输入

```
-1000000000 0 -1000000000 0
```

### 输出

```
1000000000000000000
```

