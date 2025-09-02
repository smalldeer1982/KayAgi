---
title: "[AGC036E] ABC String"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_agc036_e
tag: ['构造']
---

# [AGC036E] ABC String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc036/tasks/agc036_e

`A`,`B`,`C` からなる文字列 $ S $ が与えられます。

$ S $ の連続とは限らない部分列 $ x $ であって、次の条件をすべて満たすもののうち、最長のものを $ 1 $ つ求めてください。 なお、$ S $ の部分列とは、$ S $ から $ 0 $ 個以上の文字を削除して得られる文字列を意味します。

- $ x $ に含まれる `A`,`B`,`C` それぞれの個数は全て等しい。
- $ x $ の中で同じ文字は隣り合わない。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

条件を満たす最長の部分列を $ 1 $ つ出力せよ。 解が複数ある場合は、どれを出力しても正解とみなされる。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 10^6 $
- $ S $ は `A`,`B`,`C` からなる。

### Sample Explanation 1

$ S $ の部分列として、`ACBCAB` を考えると、これは条件を満たしており、またこれが最長です。 また、`ABCBCA` も条件を満たす最長の部分列です。 `ABCBCAB`, `ABBCCA` なども $ S $ の部分列ですが、これらは条件を満たしません。

### Sample Explanation 4

条件を満たす部分列が空文字列のみのこともあります。

## 样例 #1

### 输入

```
ABBCBCAB
```

### 输出

```
ACBCAB
```

## 样例 #2

### 输入

```
ABABABABACACACAC
```

### 输出

```
BABCAC
```

## 样例 #3

### 输入

```
ABCABACBCBABABACBCBCBCBCBCAB
```

### 输出

```
ACABACABABACBCBCBCBCA
```

## 样例 #4

### 输入

```
AAA
```

### 输出

```

```

