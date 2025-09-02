---
title: "[AGC027E] ABBreviate"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_agc027_e
tag: []
---

# [AGC027E] ABBreviate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc027/tasks/agc027_e

`a` と `b` のみからなる文字列 $ s $ があります。 すぬけ君は、次の $ 2 $ 種類の操作を任意の順序で任意の回数だけ行えます。

- $ s $ 中の部分文字列 `aa` を一箇所選び、`b` へ置き換える。
- $ s $ 中の部分文字列 `bb` を一箇所選び、`a` へ置き換える。

$ 0 $ 回以上の操作の後、$ s $ は何通りありうるでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ s $

## 输出格式

操作後の $ s $ は何通りありうるか？ $ 10^9\ +\ 7 $ で割った余りを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ |s|\ \leq\ 10^5 $
- $ s $ は `a` と `b` のみからなる。

### Sample Explanation 1

次の $ 6 $ 通りです。 - `aaaa` - `aab` - `aba` - `baa` - `bb` - `a`

### Sample Explanation 2

次の $ 5 $ 通りです。 - `aabb` - `aaa` - `bbb` - `ab` - `ba`

### Sample Explanation 3

すぬけ君は一度も操作を行えません。

## 样例 #1

### 输入

```
aaaa
```

### 输出

```
6
```

## 样例 #2

### 输入

```
aabb
```

### 输出

```
5
```

## 样例 #3

### 输入

```
ababababa
```

### 输出

```
1
```

## 样例 #4

### 输入

```
babbabaaba
```

### 输出

```
35
```

