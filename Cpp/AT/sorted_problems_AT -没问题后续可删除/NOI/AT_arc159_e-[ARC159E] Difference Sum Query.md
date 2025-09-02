---
title: "[ARC159E] Difference Sum Query"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_arc159_e
tag: ['二分', '虚树']
---

# [ARC159E] Difference Sum Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc159/tasks/arc159_e

正整数 $ N $ と $ M $ 個の正整数の組 $ (a_0,b_0),\ldots,(a_{M-1},b_{M-1}) $ が与えられます( $ a_i,b_i $ は添え字が $ 0 $ から始まることに気を付けてください)。

また、以下のような非負整数列 $ X=(x_1,\ldots,x_N) $ があります。

- $ x_i $ は以下の手順で定まる。
  1. $ l=1,r=N,t=0 $ とする。
  2. $ m=\left\ \lfloor\ \dfrac{a_{t\ \bmod\ M}\ \times\ l\ +\ b_{t\ \bmod\ M}\ \times\ r}{a_{t\ \bmod\ M}\ +b_{t\ \bmod\ M}}\ \right\ \rfloor $ とする( $ \lfloor\ x\ \rfloor $ は $ x $ を超えない最大の整数)。$ m=i $ ならば $ x_i=t $ として手順を終了する。
  3. $ l\ \leq\ i\ \lt\ m $ ならば $ r=m-1 $、そうでなければ $ l=m+1 $ とする。 $ t $ の値を $ 1 $ 増やし、2へ戻る。
 
$ i=1,2,\ldots,Q $ に対し、$ \sum_{j=c_i}^{d_i-1}\ |x_j\ -\ x_{j+1}| $ の値を求めてください。  
 なお、本問の制約の下、答えが $ 10^{18} $ 以下であることが示せます。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ a_0 $ $ b_0 $ $ \vdots $ $ a_{M-1} $ $ b_{M-1} $ $ Q $ $ c_1 $ $ d_1 $ $ \vdots $ $ c_Q $ $ d_Q $

## 输出格式

$ Q $ 行出力せよ。$ x $ 行目には、$ i=x $ に対する問題の答えを出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^{15} $
- $ 1\ \leq\ M\ \leq\ 100 $
- $ 1\ \leq\ a_i,b_i\ \leq\ 1000 $
- $ \max\ \left\ (\dfrac{a_i}{b_i},\dfrac{b_i}{a_i}\right\ )\ \leq\ 2 $
- $ 1\ \leq\ Q\ \leq\ 10^4 $
- $ 1\ \leq\ c_i\ \lt\ d_i\ \leq\ N $
- 入力はすべて整数
 
### Sample Explanation 1

$ X=(1,2,0,1,2) $ です。例えば、$ x_1 $ は以下の手順で定まります。 - $ l=1,r=5(=N),t=0 $ とする。 - $ m=3(=\left\ \lfloor\ \dfrac{1\ \times\ 1\ +\ 1\ \times\ 5}{1+1}\ \right\ \rfloor) $ とする。 - $ l\ \leq\ 1\ \lt\ m $ なので $ r=2(=m-1) $ とする。$ t $ の値を $ 1 $ 増やして $ 1 $ とする。 - $ m=1(=\ \left\ \lfloor\ \dfrac{1\ \times\ 1\ +\ 1\ \times\ 2}{1+1}\ \right\ \rfloor\ ) $ とする。$ m=1 $ なので $ x_1=1(=t) $ として手順を終了する。 $ (c_i,d_i) $ への答えは、例えば $ (c_1,d_1) $ の場合、$ \sum_{j=c_i}^{d_i-1}\ |x_j\ -\ x_{j+1}|\ =\ |x_1-x_2|\ =\ 1 $ となります。

## 样例 #1

### 输入

```
5 1
1 1
3
1 2
2 4
3 5
```

### 输出

```
1
3
2
```

## 样例 #2

### 输入

```
1000000000000000 2
15 9
9 15
3
100 10000
5000 385723875
150 17095708
```

### 输出

```
19792
771437738
34191100
```

