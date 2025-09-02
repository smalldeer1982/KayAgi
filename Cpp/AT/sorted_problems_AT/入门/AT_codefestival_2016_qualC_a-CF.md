---
title: "CF"
layout: "post"
diff: 入门
pid: AT_codefestival_2016_qualC_a
tag: ['模拟', '字符串', '栈']
---

# CF

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-qualc/tasks/codefestival_2016_qualC_a

このコンテストの名前は`CODEFESTIVAL`で、いくつかの文字を消すと`CF`という文字列にすることが出来ます。

好奇心旺盛な高橋君は、他の文字列に対してもこのように`CF`を得られるか気になりました。

英大文字アルファベットからなる文字列$ s $が与えられるので、$ s $からいくつかの文字を消して`CF`という文字列にすることが出来るか判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ s $

## 输出格式

$ s $からいくつかの文字を消して`CF`という文字列にすることが出来るなら`Yes`を、そうでないなら`No`を出力せよ。

## 说明/提示

### 制約

- $ 2≦|s|≦100 $
- $ s $は英大文字(`A`-`Z`)のみからなる文字列である

### Sample Explanation 1

1文字目の`C`と5文字目の`F`を残して消すことで`CF`が得られます。

### Sample Explanation 2

`FC`なら得ることが出来ますが、文字の順番を変えることは出来ないので、この場合は`CF`を作ることが出来ません。

### Sample Explanation 3

一文字も消さないこともありえます。

### Sample Explanation 4

1文字目を消すことで得られます。

## 样例 #1

### 输入

```
CODEFESTIVAL
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
FESTIVALCODE
```

### 输出

```
No
```

## 样例 #3

### 输入

```
CF
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
FCF
```

### 输出

```
Yes
```

