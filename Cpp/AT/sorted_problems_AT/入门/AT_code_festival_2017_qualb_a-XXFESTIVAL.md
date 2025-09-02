---
title: "XXFESTIVAL"
layout: "post"
diff: 入门
pid: AT_code_festival_2017_qualb_a
tag: []
---

# XXFESTIVAL

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_a

りんごさんは、とある祭りに参加しようとしています。

その祭りの名称が `FESTIVAL` で終わる文字列 $ S $ として入力に与えられるので、りんごさんが何の祭りに参加しようしているのかを出力して下さい。

ただし、$ s $ の祭りの名称は $ s $ の末尾に `FESTIVAL` を $ 1 $ つだけ追加した文字列であるとします。 例えば `CODEFESTIVAL` は `CODE` の祭りです。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

りんごさんが何の祭りに参加しようしているのかを出力せよ。

## 说明/提示

### 制約

- $ 9\ \leq\ |S|\ \leq\ 50 $
- $ S $ は大文字アルファベットのみからなる
- $ S $ は `FESTIVAL` で終わる

### Sample Explanation 1

問題文中の例の通りです。

### Sample Explanation 2

`CODEFESTIVAL` の末尾に `FESTIVAL` を追加した文字列であるので、これは `CODEFESTIVAL` の祭りとなります。

## 样例 #1

### 输入

```
CODEFESTIVAL
```

### 输出

```
CODE
```

## 样例 #2

### 输入

```
CODEFESTIVALFESTIVAL
```

### 输出

```
CODEFESTIVAL
```

## 样例 #3

### 输入

```
YAKINIKUFESTIVAL
```

### 输出

```
YAKINIKU
```

