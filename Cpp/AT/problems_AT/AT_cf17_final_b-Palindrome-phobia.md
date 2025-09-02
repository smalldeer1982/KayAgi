---
title: "Palindrome-phobia"
layout: "post"
diff: 普及/提高-
pid: AT_cf17_final_b
tag: []
---

# Palindrome-phobia

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf17-final/tasks/cf17_final_b

すぬけ君は `a`、`b`、`c` の $ 3 $ 種類の文字のみからなる文字列 $ S $ を持っています。

回文恐怖症のすぬけ君は $ S $ の文字を自由に並び替えて、$ 2 $ 文字以上の回文を部分文字列として含まないようにしようと思いました。 これが可能かどうかを判定して下さい。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

可能な場合は `YES`、不可能な場合は `NO` を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 10^5 $
- $ S $ は `a`、`b`、`c` 以外の文字を含まない。

### Sample Explanation 1

このままだと `aba` という回文を含みますが、例えば `acba` のように並び替えると $ 2 $ 文字以上の回文を含まなくなります。

## 样例 #1

### 输入

```
abac
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
aba
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
babacccabab
```

### 输出

```
YES
```

