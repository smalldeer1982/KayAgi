---
title: "[AGC062A] Right Side Character"
layout: "post"
diff: 普及/提高-
pid: AT_agc062_a
tag: ['贪心', '分类讨论']
---

# [AGC062A] Right Side Character

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc062/tasks/agc062_a

`A`,`B` のみからなる長さ $ n\ (2\leq\ n) $ の文字列 $ T=T_1T_2\dots\ T_n $ に対し、長さ $ n-1 $ の文字列 $ f(T) $ を以下のように定めます。

- $ T_i={} $`A` が成り立つ $ i\ (1\leq\ i\ \leq\ n-1) $ 全体を $ a_1\ <\ a_2\ <\ \dots\ <\ a_{m} $ とし、 $ T_i={} $`B` が成り立つ $ i\ (1\leq\ i\ \leq\ n-1) $ 全体を $ b_1\ <\ b_2\ <\ \dots\ <\ b_k $ とする。このとき、 $ f(T)=T_{a_1+1}T_{a_2+1}\dots\ T_{a_m+1}T_{b_1+1}T_{b_2+1}\dots\ T_{b_k+1} $ と定める。
 
例えば文字列 $ T={} $`ABBABA` について、$ T_i={} $`A` が成り立つ $ i\ (1\leq\ i\ \leq\ 5) $ 全体は $ i=1,4 $ , $ T_i={} $`B` が成り立つ $ i\ (1\leq\ i\ \leq\ 5) $ 全体は $ i=2,3,5 $ であるため、$ f(T) $ は $ T_{1+1}T_{4+1}T_{2+1}T_{3+1}T_{5+1}={} $`BBBAA` になります。

`A`,`B` のみからなる長さ $ N $ の文字列 $ S $ が与えられます。

$ S $ を $ f(S) $ で置き換えることを $ N-1 $ 回行った後の $ S $ を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられます。

> $ T $ $ \mathrm{case}_1 $ $ \vdots $ $ \mathrm{case}_T $

各ケースは以下の形式で与えられます。

> $ N $ $ S $

## 输出格式

$ T $ 行出力してください。$ i $ 行目には $ i $ 番目のテストケースに対する答えを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 10^5 $
- $ 2\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ S $ は `A`,`B` のみからなる長さ $ N $ の文字列
- 入力される数値はすべて整数
- $ 1 $ つの入力に含まれるテストケースについて、 $ N $ の総和は $ 3\ \times\ 10^5 $ 以下
 
### Sample Explanation 1

$ 1 $ つ目のテストケースについて、$ S $ は `AB`$ {}\rightarrow\ {} $`B` と変化します。 $ 2 $ つ目のテストケースについて、$ S $ は `AAA`$ {}\ \rightarrow\ {} $`AA`$ {}\ \rightarrow\ {} $`A` と変化します。 $ 3 $ つ目のテストケースについて、$ S $ は `ABAB`$ {}\rightarrow\ {} $`BBA`$ {}\ \rightarrow\ {} $`BA`$ {}\ \rightarrow\ {} $`A` と変化します。

## 样例 #1

### 输入

```
3
2
AB
3
AAA
4
ABAB
```

### 输出

```
B
A
A
```

