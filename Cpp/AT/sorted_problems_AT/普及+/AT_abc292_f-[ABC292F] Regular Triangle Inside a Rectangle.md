---
title: "[ABC292F] Regular Triangle Inside a Rectangle"
layout: "post"
diff: 普及+/提高
pid: AT_abc292_f
tag: []
---

# [ABC292F] Regular Triangle Inside a Rectangle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc292/tasks/abc292_f

縦の長さが $ A $、横の長さが $ B $ の長方形の内部に描ける正三角形の一辺の長さの最大値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $

## 输出格式

答えを出力せよ。  
 なお、真の値との絶対誤差または相対誤差が $ 10^{-9} $ 以下であれば正解として扱われる。

## 说明/提示

### 制約

- $ 1\ \leq\ A,B\ \leq\ 1000 $
- $ A,B $ は整数
 
### Sample Explanation 1

下図のように描くのが最適で、一辺の長さが $ \sqrt{6}\ -\ \sqrt{2} $ になります。 ![image](https://img.atcoder.jp/abc292/2cd44ddc3d8241e510a356be9533631f.png) なお、この出力例の値は $ \sqrt{6}-\ \sqrt{2} $ と厳密には一致しませんが、誤差が $ 10^{-9} $ 以下なので正解として扱われます。

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1.03527618041008295791
```

