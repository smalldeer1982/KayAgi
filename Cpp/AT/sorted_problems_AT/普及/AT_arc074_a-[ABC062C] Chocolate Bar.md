---
title: "[ABC062C] Chocolate Bar"
layout: "post"
diff: 普及/提高-
pid: AT_arc074_a
tag: []
---

# [ABC062C] Chocolate Bar

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc062/tasks/arc074_a

縦 $ H $ ブロック、横 $ W $ ブロックの板チョコがあります。 すぬけ君は、この板チョコをちょうど $ 3 $ つのピースに分割しようとしています。 ただし、各ピースはブロックの境目に沿った長方形でなければなりません。

すぬけ君は、$ 3 $ つのピースの面積 (ブロック数) をできるだけ均等にしようとしています。 具体的には、$ 3 $ つのピースの面積の最大値を $ S_{max} $、最小値を $ S_{min} $ としたとき、$ S_{max}\ -\ S_{min} $ を最小化しようとしています。 $ S_{max}\ -\ S_{min} $ の最小値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ H $ $ W $

## 输出格式

$ S_{max}\ -\ S_{min} $ の最小値を出力せよ。

## 说明/提示

### 制約

- $ 2\ <\ =\ H,\ W\ <\ =\ 10^5 $

### Sample Explanation 1

次図のように分割すると、$ S_{max}\ -\ S_{min}\ =\ 5\ -\ 5\ =\ 0 $ となります。 !\[2a9b2ef47b750c0b7ba3e865d4fb4203.png\](https://atcoder.jp/img/arc074/2a9b2ef47b750c0b7ba3e865d4fb4203.png)

### Sample Explanation 2

次図のように分割すると、$ S_{max}\ -\ S_{min}\ =\ 8\ -\ 6\ =\ 2 $ となります。 !\[a42aae7aaaadc4640ac5cdf88684d913.png\](https://atcoder.jp/img/arc074/a42aae7aaaadc4640ac5cdf88684d913.png)

### Sample Explanation 3

次図のように分割すると、$ S_{max}\ -\ S_{min}\ =\ 10\ -\ 6\ =\ 4 $ となります。 !\[eb0ad0cb3185b7ae418e21c472ff7f26.png\](https://atcoder.jp/img/arc074/eb0ad0cb3185b7ae418e21c472ff7f26.png)

## 样例 #1

### 输入

```
3 5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 5
```

### 输出

```
4
```

## 样例 #4

### 输入

```
100000 2
```

### 输出

```
1
```

## 样例 #5

### 输入

```
100000 100000
```

### 输出

```
50000
```

