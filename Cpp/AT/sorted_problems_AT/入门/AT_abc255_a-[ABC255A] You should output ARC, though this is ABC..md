---
title: "[ABC255A] You should output ARC, though this is ABC."
layout: "post"
diff: 入门
pid: AT_abc255_a
tag: []
---

# [ABC255A] You should output ARC, though this is ABC.

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc255/tasks/abc255_a

整数 $ R,C $ と $ 2 $ 行 $ 2 $ 列からなる行列 $ A $ が与えられるので、 $ A_{R,C} $ を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ R $ $ C $ $ A_{1,1} $ $ A_{1,2} $ $ A_{2,1} $ $ A_{2,2} $

## 输出格式

答えを整数として出力せよ。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ R,C\ \le\ 2 $
- $ 0\ \le\ A_{i,j}\ \le\ 100 $

### Sample Explanation 1

$ A_{1,2}=0 $ です。

### Sample Explanation 2

$ A_{2,2}=4 $ です。

### Sample Explanation 3

$ A_{2,1}=70 $ です。

## 样例 #1

### 输入

```
1 2
1 0
0 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 2
1 2
3 4
```

### 输出

```
4
```

## 样例 #3

### 输入

```
2 1
90 80
70 60
```

### 输出

```
70
```

