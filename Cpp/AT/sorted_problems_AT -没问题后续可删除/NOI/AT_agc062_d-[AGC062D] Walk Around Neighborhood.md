---
title: "[AGC062D] Walk Around Neighborhood"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_agc062_d
tag: ['动态规划 DP', '背包 DP', '折半搜索 meet in the middle', '标签465']
---

# [AGC062D] Walk Around Neighborhood

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc062/tasks/agc062_d

二次元平面の原点 $ (0,0) $ にメモ帳を持った高橋君がいます。メモ帳には $ N $ 個の**偶数** $ D_i\ (1\leq\ i\ \leq\ N) $ が書かれています。

これから高橋君は二次元平面上で以下の行動を $ N $ 回行います。

- メモ帳に書かれている偶数を $ 1 $ つ選んで消す。選んだ偶数を $ d $ としたとき、マンハッタン距離でちょうど $ d $ だけ離れた点へ移動する。より正確には、現在高橋君がいる点の座標を $ (x,y) $ としたとき、$ |x-x'|+|y-y'|=d $ を満たす点 $ (x',y') $ へ移動する。
 
$ N $ 回の行動を行った後、高橋君は原点 $ (0,0) $ に戻っていなければなりません。

そのように $ N $ 回の行動を行うことができるか判定してください。可能な場合、$ i $ 回目の行動を終えた後高橋君がいる座標を $ (x_i,y_i) $ としたときの $ \displaystyle\ \max_{1\leq\ i\ \leq\ N}(|x_i|+|y_i|) $ の最小値を求めてください（この値は整数になることが証明できます）。

## 输入格式

入力は以下の形式で標準入力から与えられます。

> $ N $ $ D_1 $ $ D_2 $ $ \dots $ $ D_N $

## 输出格式

上記のように $ N $ 回の行動を行うことが不可能な場合、`-1` を出力してください。可能な場合、$ \displaystyle\ \max_{1\leq\ i\ \leq\ N}(|x_i|+|y_i|) $ の最小値を整数で出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ D_i\ \leq\ 2\ \times\ 10^5 $
- $ D_i\ (1\leq\ i\ \leq\ N) $ は偶数
- 入力される値はすべて整数
 
### Sample Explanation 1

高橋君が $ 1 $ 回目から $ 3 $ 回目の行動でそれぞれ $ 2,6,4 $ をメモ帳から消し、 $ (0,0)\rightarrow\ (0,2)\ \rightarrow\ (-4,0)\ \rightarrow\ (0,0) $ と移動すると $ \displaystyle\ \max_{1\leq\ i\ \leq\ N}(|x_i|+|y_i|) $ は $ 4 $ になり、これが最小です。

### Sample Explanation 2

高橋君が $ 1 $ 回目から $ 5 $ 回目の行動でそれぞれ $ 2,2,6,2,2 $ をメモ帳から消し、 $ (0,0)\rightarrow\ (\frac{1}{2},\frac{3}{2})\rightarrow\ (0,3)\ \rightarrow\ (0,-3)\ \rightarrow\ (-\frac{1}{2},-\frac{3}{2})\ \rightarrow\ (0,0) $ と移動すると $ \displaystyle\ \max_{1\leq\ i\ \leq\ N}(|x_i|+|y_i|) $ は $ 3 $ になり、これが最小です。 高橋君は格子点以外にも移動できます。

### Sample Explanation 3

高橋君は上記のように $ N $ 回行動した後、原点に戻ることはできません。

## 样例 #1

### 输入

```
3
2 4 6
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
2 2 2 2 6
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2
2 200000
```

### 输出

```
-1
```

