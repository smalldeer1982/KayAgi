---
title: "[AGC019B] Reverse and Compare"
layout: "post"
diff: 普及/提高-
pid: AT_agc019_b
tag: []
---

# [AGC019B] Reverse and Compare

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc019/tasks/agc019_b

英小文字からなる文字列 $ A\ =\ A_1\ A_2\ ...\ A_n $ があります。

あなたは $ 1\ \leq\ i\ \leq\ j\ \leq\ n $ であるような任意の二つの添字 $ i,\ j $ を選び、$ A $ のうち部分文字列 $ A_i\ A_{i+1}\ ...\ A_j $ を反転することができます。

この操作は一回まで行うことができます。

これによって得られる文字列は何通りあるでしょうか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $

## 输出格式

$ A $ のうち任意の部分文字列を一回まで反転することによって、何通りの文字列が得られるか出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ |A|\ \leq\ 200,000 $
- $ A $ は英小文字からなる。

### Sample Explanation 1

得られる文字列は `aatt`（何もしない）、`atat`（$ A[2..3] $ を反転）、`atta`（$ A[2..4] $ を反転）、`ttaa`（$ A[1..4] $ を反転）、`taat`（$ A[1..3] $ を反転）です。

### Sample Explanation 2

どの部分文字列を反転しても、結果は `xxxxxxxxxx` です。

## 样例 #1

### 输入

```
aatt
```

### 输出

```
5
```

## 样例 #2

### 输入

```
xxxxxxxxxx
```

### 输出

```
1
```

## 样例 #3

### 输入

```
abracadabra
```

### 输出

```
44
```

