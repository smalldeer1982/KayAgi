---
title: "[ABC071D] Coloring Dominoes"
layout: "post"
diff: 普及/提高-
pid: AT_arc081_b
tag: []
---

# [ABC071D] Coloring Dominoes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc071/tasks/arc081_b

$ 2\ \times\ N $ のマス目があります． すぬけ君は，このマス目に $ N $ 個のドミノを，重ならないように敷き詰めました． ここで，ドミノは，$ 1\ \times\ 2 $ または $ 2\ \times\ 1 $ のマス目を覆うことができます．

すぬけ君は，赤色，水色，緑色の $ 3 $ 色を使って，これらのドミノを塗ることにしました． このとき，辺で接しているドミノは異なる色で塗るようにします． ここで，必ずしも $ 3 $ 色すべてを使う必要はありません．

このような塗り方が何通りあるかを mod $ 1000000007 $ で求めてください．

ただし，ドミノの敷き詰め方は，文字列 $ S_1,\ S_2 $ を用いて，次のようにして与えられます．

- 各ドミノは，それぞれ異なる英小文字または英大文字で表される．
- $ S_i $ の $ j $ 文字目は，マス目の上から $ i $ 番目，左から $ j $ 番目のマスにどのドミノがあるかを表す．

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S_1 $ $ S_2 $

## 输出格式

ドミノを塗る方法の数を mod $ 1000000007 $ で出力せよ．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 52 $
- $ |S_1|\ =\ |S_2|\ =\ N $
- $ S_1,\ S_2 $ は英小文字または英大文字からなる
- $ S_1,\ S_2 $ は正しいドミノの敷き詰め方を表している

### Sample Explanation 1

次の $ 6 $ 通りあります． !\[\](https://atcoder.jp/img/arc081/899673bd23529f4fb5e41c6e7d5bc372.png)

### Sample Explanation 2

必ずしもすべての色を使わなくてもよいことに注意してください．

## 样例 #1

### 输入

```
3
aab
ccb
```

### 输出

```
6
```

## 样例 #2

### 输入

```
1
Z
Z
```

### 输出

```
3
```

## 样例 #3

### 输入

```
52
RvvttdWIyyPPQFFZZssffEEkkaSSDKqcibbeYrhAljCCGGJppHHn
RLLwwdWIxxNNQUUXXVVMMooBBaggDKqcimmeYrhAljOOTTJuuzzn
```

### 输出

```
958681902
```

