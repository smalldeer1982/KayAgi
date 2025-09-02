---
title: "[ARC180A] ABA and BAB"
layout: "post"
diff: 普及/提高-
pid: AT_arc180_a
tag: ['数学', '排列组合']
---

# [ARC180A] ABA and BAB

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc180/tasks/arc180_a

`A`, `B` からなる長さ $ N $ の文字列 $ S $ が与えられます．

あなたは以下の $ 2 $ 種類の操作を好きな順序で $ 0 $ 回以上繰り返すことができます．

- $ S $ の中で `ABA` となっている (連続した) 部分を選び，それを `A` で置き換える．
- $ S $ の中で `BAB` となっている (連続した) 部分を選び，それを `B` で置き換える．
 
操作後の $ S $ としてあり得る文字列の個数を $ 10^9+7 $ で割ったあまりを求めてください．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ N $ $ S $

## 输出格式

答えを出力せよ．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 250000 $
- $ S $ は `A`, `B` からなる長さ $ N $ の文字列
 
### Sample Explanation 1

操作後の $ S $ としてあり得るのは以下の $ 2 $ 種類の文字列です． - `ABAB`: $ 0 $ 回の操作を行うことでこの文字列を得ることができます． - `AB`: $ S= $`ABAB` の $ 1 $ 文字目から $ 3 $ 文字目までが `ABA` となっています．これを `A` で置き換えると $ S= $`AB` となります． なお，$ S= $`ABAB` の $ 2 $ 文字目から $ 4 $ 文字目までが `BAB` となっているので，これを `B` に置き換える操作も可能です． ただし，その結果得られる `AB` は重複して数えないことに注意してください．

### Sample Explanation 2

操作を $ 1 $ 度も行うことができません．

### Sample Explanation 4

$ 10^9+7 $ で割ったあまりを求めるのを忘れないようにしてください．

## 样例 #1

### 输入

```
4
ABAB
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1
A
```

### 输出

```
1
```

## 样例 #3

### 输入

```
17
BBABABAABABAAAABA
```

### 输出

```
18
```

## 样例 #4

### 输入

```
100
ABAABAABABBABAABAABAABABBABBABBABBABBABBABBABBABBABBABBABBABBABBABAABABAABABBABBABABBABAABAABAABAABA
```

### 输出

```
415919090
```

