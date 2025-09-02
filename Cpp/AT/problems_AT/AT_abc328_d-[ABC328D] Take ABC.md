---
title: "[ABC328D] Take ABC"
layout: "post"
diff: 普及-
pid: AT_abc328_d
tag: ['栈']
---

# [ABC328D] Take ABC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc328/tasks/abc328_d

`A` , `B` , `C` の $ 3 $ 種類の文字のみからなる文字列 $ S $ が与えられます。

$ S $ が連続な部分文字列として文字列 `ABC` を含む限り、下記の操作を繰り返します。

> $ S $ に連続な部分文字列として含まれる文字列 `ABC` のうち、$ S $ の中で最も左にあるものを、$ S $ から削除する。

上記の手順を行った後の、最終的な $ S $ を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ S $ は `A` , `B` , `C` のみからなる長さ $ 1 $ 以上 $ 2\times\ 10^5 $ 以下の文字列
 
### Sample Explanation 1

与えられた文字列 $ S\ = $ `BAABCBCCABCAC` に対して、下記の通りに操作が行われます。 - $ 1 $ 回目の操作で、$ S\ = $ `BAABCBCCABCAC` の $ 3 $ 文字目から $ 5 $ 文字目の `ABC` が削除され、その結果 $ S\ = $ `BABCCABCAC` となります。 - $ 2 $ 回目の操作で、$ S\ = $ `BABCCABCAC` の $ 2 $ 文字目から $ 4 $ 文字目の `ABC` が削除され、その結果 $ S\ = $ `BCABCAC` となります。 - $ 3 $ 回目の操作で、$ S\ = $ `BCABCAC` の $ 3 $ 文字目から $ 5 $ 文字目の `ABC` が削除され、その結果 $ S\ = $ `BCAC` となります。 よって、最終的な $ S $ は `BCAC` です。

### Sample Explanation 2

この入力例では、最終的な $ S $ は空文字列です。

## 样例 #1

### 输入

```
BAABCBCCABCAC
```

### 输出

```
BCAC
```

## 样例 #2

### 输入

```
ABCABC
```

### 输出

```

```

## 样例 #3

### 输入

```
AAABCABCABCAABCABCBBBAABCBCCCAAABCBCBCC
```

### 输出

```
AAABBBCCC
```

