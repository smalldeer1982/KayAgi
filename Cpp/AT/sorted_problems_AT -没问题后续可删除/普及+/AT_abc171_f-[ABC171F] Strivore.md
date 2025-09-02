---
title: "[ABC171F] Strivore"
layout: "post"
diff: 普及+/提高
pid: AT_abc171_f
tag: []
---

# [ABC171F] Strivore

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc171/tasks/abc171_f

「好きな英小文字 $ 1 $ 文字を好きな位置に挿入する」という操作を文字列 $ S $ にちょうど $ K $ 回繰り返してできる文字列は何通りあるでしょう？

答えは非常に大きくなる可能性があるので、$ (10^9+7) $ で割ったあまりを出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ K $ $ S $

## 输出格式

条件を満たす文字列の個数を $ (10^9+7) $ で割ったあまりを出力せよ。

## 说明/提示

### 制約

- $ K $ は $ 1 $ 以上 $ 10^6 $ 以下の整数
- $ S $ は英小文字からなる長さ $ 1 $ 以上 $ 10^6 $ 以下の文字列

### Sample Explanation 1

たとえば、`proofend`、`moonwolf`、`onionpuf` などが条件を満たします。 それに対し、`oofsix`、`oofelevennn`、`voxafolt`、`fooooooo` などは条件を満たしません。

## 样例 #1

### 输入

```
5
oof
```

### 输出

```
575111451
```

## 样例 #2

### 输入

```
37564
whydidyoudesertme
```

### 输出

```
318008117
```

