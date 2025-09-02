---
title: "[ABC089C] March"
layout: "post"
diff: 普及-
pid: AT_abc089_c
tag: []
---

# [ABC089C] March

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc089/tasks/abc089_c

$ N $ 人の人がいて、$ i $ 番目の人の名前は $ S_i $ です。

この中から、以下の条件を満たすように $ 3 $ 人を選びたいです。

- 全ての人の名前が `M`,`A`,`R`,`C`,`H` のどれかから始まっている
- 同じ文字から始まる名前を持つ人が複数いない

これらの条件を満たすように $ 3 $ 人を選ぶ方法が何通りあるか、求めてください。ただし、選ぶ順番は考えません。

答えが $ 32 $ bit整数型に収まらない場合に注意してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S_1 $ $ : $ $ S_N $

## 输出格式

与えられた条件を満たすように $ 3 $ 人を選ぶ方法が $ x $ 通りのとき、$ x $ を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ S_i $ は英大文字からなる
- $ 1\ \leq\ |S_i|\ \leq\ 10 $
- $ S_i\ \neq\ S_j\ (i\ \neq\ j) $

### Sample Explanation 1

次のような名前の $ 3 $ 人を選ぶと良いです。 - `MASHIKE`,`RUMOI`,`HABORO` - `MASHIKE`,`RUMOI`,`HOROKANAI` よって、$ 2 $ 通りとなります。

### Sample Explanation 2

与えられた条件を満たすように $ 3 $ 人を選ぶ方法が存在しない場合に注意してください。

## 样例 #1

### 输入

```
5
MASHIKE
RUMOI
OBIRA
HABORO
HOROKANAI
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
ZZ
ZZZ
Z
ZZZZZZZZZZ
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
CHOKUDAI
RNG
MAKOTO
AOKI
RINGO
```

### 输出

```
7
```

