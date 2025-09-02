---
title: "[ABC391A] Lucky Direction"
layout: "post"
diff: 入门
pid: AT_abc391_a
tag: ['字符串（入门）']
---

# [ABC391A] Lucky Direction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc391/tasks/abc391_a

$ 8 $ 種類の方角（北、東、西、南、北東、北西、南東、南西）のいずれかを表す文字列 $ D $ が与えられます。方角とそれを表す文字列は以下のように対応しています。

- 北：`N`
- 東：`E`
- 西：`W`
- 南：`S`
- 北東：`NE`
- 北西：`NW`
- 南東：`SE`
- 南西：`SW`
 
$ D $ が表す方角の反対の方角を表す文字列を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ D $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ D $ は `N`, `E`, `W`, `S`, `NE`, `NW`, `SE`, `SW` のいずれか
 
### Sample Explanation 1

北の反対の方角である南を表す `S` を出力してください。

### Sample Explanation 2

南東の反対の方角である北西を表す `NW` を出力してください。

## 样例 #1

### 输入

```
N
```

### 输出

```
S
```

## 样例 #2

### 输入

```
SE
```

### 输出

```
NW
```

