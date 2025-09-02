---
title: "[ARC058F] 文字列大好きいろはちゃん"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_arc058_d
tag: []
---

# [ARC058F] 文字列大好きいろはちゃん

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc058/tasks/arc058_d

いろはちゃんは $ N $ 個の文字列 $ s_1,\ s_2,\ ...,\ s_N $ を持っています。

いろはちゃんは、この中からいくつか文字列を選びます。そして添字の昇順で選んだ文字列を繋げ、長さ $ K $ の文字列を作ります。

作れる長さ $ K $ の文字列のうち、もっとも辞書順で小さいものを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $ $ s_1 $ $ s_2 $ : $ s_N $

## 输出格式

作れる長さ $ K $ の文字列のうち、もっとも辞書順で小さいものを出力せよ。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 2000 $
- $ 1\ ≦\ K\ ≦\ 10^4 $
- $ 1\ ≦\ |s_i|\ ≦\ K $
- $ |s_1|\ +\ |s_2|\ +\ ...\ +\ |s_N|\ ≦\ 10^6 $
- 各 $ i $ について, $ s_i $ は全て半角英小文字のみから成る文字列である。
- 長さ $ K $ の文字列を作る方法が存在することが保証される。

### Sample Explanation 1

`at` と `codar` を選択します。

### Sample Explanation 2

`codar` と `at` を選択します。

### Sample Explanation 3

`namida` と `zzzzzzz` を選択します。

## 样例 #1

### 输入

```
3 7
at
coder
codar
```

### 输出

```
atcodar
```

## 样例 #2

### 输入

```
3 7
coder
codar
at
```

### 输出

```
codarat
```

## 样例 #3

### 输入

```
4 13
kyuri
namida
zzzzzzz
aaaaaa
```

### 输出

```
namidazzzzzzz
```

