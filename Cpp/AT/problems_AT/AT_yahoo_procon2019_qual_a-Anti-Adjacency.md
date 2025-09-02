---
title: "Anti-Adjacency"
layout: "post"
diff: 入门
pid: AT_yahoo_procon2019_qual_a
tag: []
---

# Anti-Adjacency

## 题目描述

[problemUrl]: https://atcoder.jp/contests/yahoo-procon2019-qual/tasks/yahoo_procon2019_qual_a

$ 1 $ 以上 $ N $ 以下の異なる整数を、差が $ 1 $ の整数をともに選ばないように $ K $ 個選ぶことができるか判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $

## 输出格式

整数を $ K $ 個選ぶことができるなら `YES` を、そうでないなら `NO` を出力せよ。

## 说明/提示

### 制約

- $ 1\leq\ N,K\leq\ 100 $
- $ N,K $ は整数である

### Sample Explanation 1

$ 1,3 $ を選べばよいです。

## 样例 #1

### 输入

```
3 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
31 10
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
10 90
```

### 输出

```
NO
```

