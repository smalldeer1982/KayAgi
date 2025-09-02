---
title: "[ABC066B] ss"
layout: "post"
diff: 入门
pid: AT_abc066_b
tag: []
---

# [ABC066B] ss

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc066/tasks/abc066_b

同じ文字列を $ 2 $ つ並べてできる文字列のことを偶文字列と呼ぶことにします。 例えば、 `xyzxyz` や `aaaaaa` は偶文字列ですが、`ababab` や `xyzxy` は偶文字列ではありません。

アルファベットの小文字からなる偶文字列 $ S $ が与えられます。 $ S $ の末尾の文字を $ 1 $ 文字以上消して作れる偶文字列のうち、最も長い偶文字列の長さを求めて下さい。 与えられる入力では、条件を満たす $ 1 $ 文字以上の文字列が存在することが保証されています。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えとなる文字列の長さを出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ |S|\ \leq\ 200 $
- $ S $ は小文字のアルファベットのみからなる偶文字列である。
- $ S $ に対して、条件を満たす $ 1 $ 文字以上の文字列が存在する。

### Sample Explanation 1

`abaababaab` は偶文字列ですが、 $ 1 $ 文字も消していないので条件を満たしません。 `abaababaa` は偶文字列ではありません。 `abaababa` は偶文字列ではありません。 `abaabab` は偶文字列ではありません。 `abaaba` は偶文字列です。よって、答えは `abaaba` の長さである $ 6 $ です。

### Sample Explanation 2

`xxx` は偶文字列ではありません。 `xx` は偶文字列です。

### Sample Explanation 3

条件を満たす文字列は `abcabc` なので、答えは $ 6 $ です。

### Sample Explanation 4

条件を満たす文字列は `akasakaakasaka` なので、答えは $ 14 $ です。

## 样例 #1

### 输入

```
abaababaab
```

### 输出

```
6
```

## 样例 #2

### 输入

```
xxxx
```

### 输出

```
2
```

## 样例 #3

### 输入

```
abcabcabcabc
```

### 输出

```
6
```

## 样例 #4

### 输入

```
akasakaakasakasakaakas
```

### 输出

```
14
```

