---
title: "Lexicographical disorder"
layout: "post"
diff: 省选/NOI-
pid: AT_codefestival_2016_qualB_e
tag: []
---

# Lexicographical disorder

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-qualb/tasks/codefestival_2016_qualB_e

英小文字のみからなる文字列が$ N $個あります。$ i $番目の文字列は$ S_i $です。すべての文字列は相異なります。

次の$ Q $個のクエリに答えてください。$ i $番目のクエリは、以下のような形式です。

クエリ: 整数$ k_i $と、{'a','b',...,'z'}の並び替えである文字列$ p_{i,1}p_{i,2}...p_{i,26} $が与えられる。文字の順序が$ p_{i,1}\ のとき、文字列S_{k_i} $は$ N $個の文字列たちの中で辞書順で何番目か出力せよ。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S_1 $ : $ S_N $ $ Q $ $ k_1 $ $ p_{1,1}p_{1,2}...p_{1,26} $ : $ k_Q $ $ p_{Q,1}p_{Q,2}...p_{Q,26} $

## 输出格式

$ Q $行出力せよ。

$ i $行目には、$ i $番目のクエリに対し、文字列$ S_{k_i} $は$ N $個の文字列たちの中で辞書順で何番目かを表す整数を出力せよ。

## 说明/提示

### 制約

- $ 1\ ≦\ N,Q\ ≦\ 100000 $
- $ 1\ ≦\ |\ S_i\ |\ (1\ ≦\ i\ ≦\ N) $
- $ S_i\ (1\ ≦\ i\ ≦\ N) $は英小文字のみからなる。
- $ |\ S_i\ | $たちの合計は$ 400000 $以下。
- $ S_i $たちはすべて相異なる。
- $ 1\ ≦\ k_i\ ≦\ N(1\ ≦\ i\ ≦\ Q) $
- すべての$ 1\ ≦\ i\ ≦\ Q $に対し、$ p_{i,1}p_{i,2}...p_{i,26} $は"abcd...z"の並び替えである。

### Sample Explanation 1

文字の順序が"a" 1,3,5番目のクエリにはそれぞれ$ 1,5,2 $と答えます。 また、文字の順序が"b" 2,4番目のクエリにはそれぞれ$ 2,4 $と答えます。

## 样例 #1

### 输入

```
5
aa
abbaa
abbba
aaab
aaaaaba
5
1 abcdefghijklmnopqrstuvwxyz
2 bacdefghijklmnopqrstuvwxyz
3 abcdefghijklmnopqrstuvwxyz
4 bacdefghijklmnopqrstuvwxyz
5 abcdefghijklmnopqrstuvwxyz
```

### 输出

```
1
2
5
4
2
```

## 样例 #2

### 输入

```
8
abrakatabra
abadaba
abracadabra
atcoder
grand
contest
ababa
a
6
3 abcdefghijklmnopqrstuvwxyz
6 qwertyuiopasdfghjklzxcvbnm
8 poiuytrewqlkjhgfdsamnbvcxz
2 qazwsxedcrfvtgbyhnujmikolp
1 plokmijnuhbygvtfcrdxeszwaq
4 mnbvcxzasdfghjklpoiuytrewq
```

### 输出

```
4
8
2
3
4
7
```

