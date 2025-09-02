---
title: "[ABC392A] Shuffled Equation"
layout: "post"
diff: 难度0
pid: AT_abc392_a
tag: []
---

# [ABC392A] Shuffled Equation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc392/tasks/abc392_a

整数列 $ A=(A_1,A_2,A_3) $ が与えられます。  
 $ A $ の要素を自由に並べ替えた列を $ B=(B_1,B_2,B_3) $ とします。  
 このとき、 $ B_1\ \times\ B_2\ =\ B_3 $ を満たすようにできるか判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A_1 $ $ A_2 $ $ A_3 $

## 输出格式

$ B_1\ \times\ B_2\ =\ B_3 $ を満たすようにできるなら `Yes` 、そうでないなら `No` と出力せよ。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ A_1,A_2,A_3\ \le\ 100 $
 
### Sample Explanation 1

$ A=(3,15,5) $ です。 $ B=(3,5,15) $ と並べ替えることで、 $ B_1\ \times\ B_2\ =\ B_3 $ を満たすようにできます。

### Sample Explanation 2

$ B $ をどのように定めても、 $ B_1\ \times\ B_2\ =\ B_3 $ を満たすようにはできません。

## 样例 #1

### 输入

```
3 15 5
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5 3 2
```

### 输出

```
No
```

## 样例 #3

### 输入

```
3 3 9
```

### 输出

```
Yes
```

