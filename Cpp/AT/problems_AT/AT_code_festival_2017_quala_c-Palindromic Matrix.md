---
title: "Palindromic Matrix"
layout: "post"
diff: 普及+/提高
pid: AT_code_festival_2017_quala_c
tag: []
---

# Palindromic Matrix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2017-quala/tasks/code_festival_2017_quala_c

縦 $ H $ 行、横 $ W $ 列の行列 $ A $ があります。 上から $ i $ 行目、左から $ j $ 列目の要素を $ a_{ij} $ とします。 各 $ a_{ij} $ は英小文字です。

すぬけ君は、$ A $ の要素を自由に並べ替え、縦 $ H $ 行、横 $ W $ 列の行列 $ A' $ を作ろうとしています。 このとき、次の条件が成り立つようにします。

- $ A' $ のどの行およびどの列もそれぞれ回文になっている。

条件を満たす $ A' $ が存在するか判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ H $ $ W $ $ a_{11} $$ a_{12} $$ ... $$ a_{1W} $ $ : $ $ a_{H1} $$ a_{H2} $$ ... $$ a_{HW} $

## 输出格式

条件を満たす $ A' $ が存在するならば `Yes` を、存在しないならば `No` を出力せよ。

## 说明/提示

### 注釈

回文とは、前後を反転しても変わらない文字列のことです。 例えば、`a`, `aa`, `abba`, `abcba` は回文ですが、`ab`, `abab`, `abcda` は回文ではありません。

### 制約

- $ 1\ <\ =\ H,\ W\ <\ =\ 100 $
- $ a_{ij} $ は英小文字である。

### Sample Explanation 1

例えば、次の $ A' $ は条件を満たします。 ``` abba acca abba ```

### Sample Explanation 2

どのように $ A $ の要素を並べ替えても、条件を満たす $ A' $ を作れません。

### Sample Explanation 3

例えば、次の $ A' $ は条件を満たします。 ``` t e w e t ```

## 样例 #1

### 输入

```
3 4
aabb
aabb
aacc
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 2
aa
bb
```

### 输出

```
No
```

## 样例 #3

### 输入

```
5 1
t
w
e
e
t
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
2 5
abxba
abyba
```

### 输出

```
No
```

## 样例 #5

### 输入

```
1 1
z
```

### 输出

```
Yes
```

