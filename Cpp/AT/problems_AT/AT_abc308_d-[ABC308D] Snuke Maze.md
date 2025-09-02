---
title: "[ABC308D] Snuke Maze"
layout: "post"
diff: 普及/提高-
pid: AT_abc308_d
tag: []
---

# [ABC308D] Snuke Maze

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc308/tasks/abc308_d

$ H $ 行 $ W $ 列のグリッドがあります。 以下、上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ と表記します。 グリッドの各マスには英小文字が書かれており、$ (i,j) $ に書かれた文字は与えられる文字列 $ S_i $ の $ j $ 文字目と一致します。

すぬけくんは、辺で隣接するマスに移動することを繰り返して $ (1,1) $ から $ (H,W) $ まで移動しようと思っています。 訪れるマス （最初の $ (1,1) $ と 最後の $ (H,W) $ を含む）に書かれた文字が、 訪れる順に `s` $ \rightarrow $ `n` $ \rightarrow $ `u` $ \rightarrow $ `k` $ \rightarrow $ `e` $ \rightarrow $ `s` $ \rightarrow $ `n` $ \rightarrow\ \dots $ となるような経路が存在するか判定してください。 なお、$ 2 $ つのマス $ (i_1,j_1),(i_2,j_2) $ は $ |i_1-i_2|+|j_1-j_2|\ =\ 1 $ を満たすとき、またそのときに限り「辺で隣接する」といいます。

より厳密には、マスの列 $ ((i_1,j_1),(i_2,j_2),\dots,(i_k,j_k)) $ であって以下の条件を全て満たすものが存在するか判定してください。

- $ (i_1,j_1)\ =\ (1,1),(i_k,j_k)\ =\ (H,W) $
- すべての $ t\ (1\ \leq\ t\ <\ k) $ について、$ (i_t,j_t) $ と $ (i_{t+1},j_{t+1}) $ は辺で隣接する
- すべての $ t\ (1\ \leq\ t\ \leq\ k) $ について、$ (i_t,j_t) $ に書かれた文字は `snuke` の $ ((t-1)\ \bmod\ 5)\ +\ 1 $ 文字目と一致する

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ H $ $ W $ $ S_1 $ $ S_2 $ $ \vdots $ $ S_H $

## 输出格式

問題文中の条件を満たす経路が存在するならば `Yes` を、存在しないならば `No` を出力せよ。

## 说明/提示

### 制約

- $ 2\leq\ H,W\ \leq\ 500 $
- $ H,W $ は整数
- $ S_i $ は英小文字からなる長さ $ W $ の文字列
 
### Sample Explanation 1

$ (1,1)\ \rightarrow\ (1,2)\ \rightarrow\ (2,2)\ \rightarrow\ (2,3) $ という経路は、訪れたマスに書かれた文字が訪れた順に `s` $ \rightarrow $ `n` $ \rightarrow $ `u` $ \rightarrow $ `k` となるため条件を満たします。

## 样例 #1

### 输入

```
2 3
sns
euk
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 2
ab
cd
```

### 输出

```
No
```

## 样例 #3

### 输入

```
5 7
skunsek
nukesnu
ukeseku
nsnnesn
uekukku
```

### 输出

```
Yes
```

