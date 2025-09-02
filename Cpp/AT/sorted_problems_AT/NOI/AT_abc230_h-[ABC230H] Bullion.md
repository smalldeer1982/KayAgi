---
title: "[ABC230H] Bullion"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_abc230_h
tag: []
---

# [ABC230H] Bullion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc230/tasks/abc230_h

クレーンゲームの大会で優勝した高橋君は金塊詰め放題の権利を得ました。  
 会場には $ w_1\ \lbrack\mathrm{kg}\rbrack,\ w_2\ \lbrack\mathrm{kg}\rbrack,\ \dots,\ w_K\ \lbrack\mathrm{kg}\rbrack $ の重さの金塊、および金塊を詰める $ 1\ \lbrack\mathrm{kg}\rbrack $ の袋が無尽蔵にあります。

高橋君は $ 1 $ 個の空でない袋を持ち帰ることができます。  
 袋には $ 0 $ 個以上の空でない袋と $ 0 $ 個以上の金塊を入れることができます。

耐荷重量 $ W\ \lbrack\mathrm{kg}\rbrack $ のトラックを手配した高橋君は、 $ w\ =\ 2,\ 3,\ \dots,\ W $ について持ち帰る袋の総重量が $ w\ \lbrack\mathrm{kg}\rbrack $ である詰め方としてあり得る状態の数が気になりました。  
 $ w\ =\ 2,\ 3,\ \dots,\ W $ について状態数を $ 998244353 $ で割ったあまりを求めてください。ただし、

- $ 2 $ つの金塊が同じであるとは、金塊の重さが同じであることをいいます。
- $ 2 $ つの袋が同じ状態であるとは、袋に入っている袋および金塊からなる多重集合が一致することをいいます。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ W $ $ K $ $ w_1 $ $ w_2 $ $ \dots $ $ w_K $

## 输出格式

答えを $ W\ -\ 1 $ 行出力せよ。  
 $ i $ 行目には $ w\ =\ i\ +\ 1 $ のときの答えを出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ W\ \leq\ 2.5\ \times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ W $
- $ 1\ \leq\ w_i\ \leq\ W $ $ (1\ \leq\ i\ \leq\ K) $
- $ i\ \neq\ j\ \to\ w_i\ \neq\ w_j $ $ (1\ \leq\ i,j\ \leq\ K) $
- 入力はすべて整数である。

### Sample Explanation 1

$ w\ =\ 2,\ 3,\ 4 $ において袋の状態としてあり得るものを列挙したのが下の図になります。 (丸い線が袋を表しています。) !\[image\](https://img.atcoder.jp/ghi/5e1a4298e8b0992c767932915c7e93f4.png)

## 样例 #1

### 输入

```
4 1
1
```

### 输出

```
1
2
4
```

## 样例 #2

### 输入

```
10 10
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
1
3
7
18
45
121
325
904
2546
```

