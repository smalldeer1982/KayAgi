---
title: "[AGC037E] Reversing and Concatenating"
layout: "post"
diff: 省选/NOI-
pid: AT_agc037_e
tag: ['贪心']
---

# [AGC037E] Reversing and Concatenating

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc037/tasks/agc037_e

高橋君は英小文字からなる長さ $ N $ の文字列 $ S $ を持っています。 高橋君は $ S $ に対して以下の操作を $ K $ 回行うことにしました。

- $ S $ を反転した文字列を $ T $ として、$ S $ と $ T $ をこの順に連結して得られる文字列を $ U $ とする。
- ある $ U $ の連続する長さ $ N $ の部分文字列を $ S' $ として、$ S $ を $ S' $ で置き換える。

最終的な $ S $ として考えられる文字列の内、辞書順で最小のものを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $ $ S $

## 输出格式

最終的な $ S $ として考えられる文字列の内、辞書順で最小のものを出力せよ。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 5000 $
- $ 1\ ≦\ K\ ≦\ 10^9 $
- $ |S|=N $
- $ S $ は英小文字からなる

### Sample Explanation 1

$ S= $`bacba`のとき、$ T= $`abcab`, $ U= $`bacbaabcab`であるので $ S'= $`aabca`とするのが最適です。

## 样例 #1

### 输入

```
5 1
bacba
```

### 输出

```
aabca
```

## 样例 #2

### 输入

```
10 2
bbaabbbaab
```

### 输出

```
aaaabbaabb
```

