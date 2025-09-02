---
title: "Signboard"
layout: "post"
diff: 入门
pid: AT_codefestival_2016_qualB_a
tag: ['字符串']
---

# Signboard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-qualb/tasks/codefestival_2016_qualB_a

CODE FESTIVAL 2016が開催されます。開催にあたって、高橋君はCODE FESTIVAL 2016の看板を作ることにしました。

看板には`CODEFESTIVAL2016`と書きたかったのですが、高橋君は間違えて異なる文字列$ S $を書いてしまいました。幸い、書いた文字列の長さは間違っていませんでした。

そこで高橋君は、ある文字を別の文字に書き換えるという操作を最小の回数行って、この文字列を`CODEFESTIVAL2016`に書き換えることにしました。

書き換えの回数の最小値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

書き換えの回数の最小値を表す整数を出力せよ。

## 说明/提示

### 制約

- $ S $の長さは$ 16 $である。
- $ S $ は英大文字、英小文字、数字からなる。

### Sample Explanation 1

$ 2 $文字目の`0`を`O`に、$ 14 $文字目の`O`を`0`に書き換える必要があります。

## 样例 #1

### 输入

```
C0DEFESTIVAL2O16
```

### 输出

```
2
```

## 样例 #2

### 输入

```
FESTIVAL2016CODE
```

### 输出

```
16
```

