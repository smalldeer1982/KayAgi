---
title: "[ABC359G] Sum of Tree Distance"
layout: "post"
diff: 提高+/省选-
pid: AT_abc359_g
tag: ['虚树', '根号分治']
---

# [ABC359G] Sum of Tree Distance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc359/tasks/abc359_g

$ N $ 頂点の木が与えられます。 $ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を双方向に結んでいます。

また、整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。

ここで $ f(i,j) $ を以下で定義します。

- $ A_i=A_j $ のとき、$ f(i,j) $ は頂点 $ i $ から頂点 $ j $ に移動する場合に通る辺数の最小値とする。$ A_i\neq\ A_j $ のとき $ f(i,j)=0 $ とする。
 
次の式の値を求めてください。

$ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ f(i,j) $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ u_1 $ $ v_1 $ $ \vdots $ $ u_{N-1} $ $ v_{N-1} $ $ A_1 $ $ A_2 $ $ \ldots $ $ A_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ u_i,v_i\ \leq\ N $
- $ 1\leq\ A_i\leq\ N $
- 入力されるグラフは木
- 入力される数値は全て整数
 
### Sample Explanation 1

$ f(1,4)=2,f(2,3)=2 $ となります。また、それ以外の $ i,j\ (1\leq\ i\ <\ j\leq\ N) $ について $ f(i,j)=0 $ なので、答えは $ 2+2=4 $ です。

## 样例 #1

### 输入

```
4

3 4

4 2

1 2

2 1 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8

8 6

3 8

1 4

7 8

4 5

3 4

8 2

1 2 2 2 3 1 1 3
```

### 输出

```
19
```



---

