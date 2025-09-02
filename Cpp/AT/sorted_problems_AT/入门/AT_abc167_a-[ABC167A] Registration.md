---
title: "[ABC167A] Registration"
layout: "post"
diff: 入门
pid: AT_abc167_a
tag: []
---

# [ABC167A] Registration

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc167/tasks/abc167_a

高橋君はとあるWebサービスに会員登録しようとしています。

まずIDを $ S $ として登録しようとしました。しかし、このIDは既に他のユーザーによって使用されていました。

そこで、高橋君は $ S $ の末尾に $ 1 $ 文字追加した文字列をIDとして登録することを考えました。

高橋君は新しくIDを $ T $ として登録しようとしています。これが前述の条件を満たすか判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $ $ T $

## 输出格式

$ T $ が問の条件を満たすならば `Yes` と、そうでないならば `No` と出力せよ。

## 说明/提示

### 制約

- $ S $, $ T $ は英小文字列
- $ 1\ \leq\ |S|\ \leq\ 10 $
- $ |T|\ =\ |S|\ +\ 1 $

### Sample Explanation 1

`chokudaiz` は `chokudai` の末尾に `z` を追加して得られる文字列です。

### Sample Explanation 2

`snekee` は `snuke` の末尾に英小文字を $ 1 $ 文字追加して得られる文字列ではありません。

## 样例 #1

### 输入

```
chokudai
chokudaiz
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
snuke
snekee
```

### 输出

```
No
```

## 样例 #3

### 输入

```
a
aa
```

### 输出

```
Yes
```

