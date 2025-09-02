---
title: "[ABC320D] Relative Position"
layout: "post"
diff: 普及/提高-
pid: AT_abc320_d
tag: ['图遍历']
---

# [ABC320D] Relative Position

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc320/tasks/abc320_d

座標平面上に $ 1 $ から $ N $ の番号がついた $ N $ 人の人がいます。  
 人 $ 1 $ は原点にいます。

次の形式の情報が $ M $ 個与えられます。

- 人 $ A_i $ から見て、人 $ B_i $ は、$ x $ 軸正方向に $ X_i $、$ y $ 軸正方向に $ Y_i $ 離れた位置にいる
 
それぞれの人がいる座標を求めてください。一意に定まらないときはそのことを報告してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ A_1 $ $ B_1 $ $ X_1 $ $ Y_1 $ $ \vdots $ $ A_M $ $ B_M $ $ X_M $ $ Y_M $

## 输出格式

$ N $ 行出力せよ。  
 人 $ i $ のいる座標が一意に定まらないとき、$ i $ 行目には `undecidable` と出力せよ。  
 人 $ i $ のいる座標が $ (s_i,t_i) $ と一意に定まるとき、$ i $ 行目には $ s_i,t_i $ をこの順に空白区切りで出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,\ B_i\ \leq\ N $
- $ A_i\ \neq\ B_i $
- $ -10^9\ \leq\ X_i,Y_i\ \leq\ 10^9 $
- 入力は全て整数である
- 与えられる情報は矛盾しない
 
### Sample Explanation 1

$ 3 $ 人の位置関係は下図のようになっています。 !\[図\](https://img.atcoder.jp/abc320/787d69ac49af24e80723e88b4f954f44.png)

### Sample Explanation 2

$ 3 $ 人の位置関係は下図のようになっています。 !\[図\](https://img.atcoder.jp/abc320/5dde7e83dd268b5b5fc322ddcb44eb86.png)

### Sample Explanation 3

同じ情報が複数回与えられたり、同じ座標に複数の人がいることもあります。

## 样例 #1

### 输入

```
3 2
1 2 2 1
1 3 -1 -2
```

### 输出

```
0 0
2 1
-1 -2
```

## 样例 #2

### 输入

```
3 2
2 1 -2 -1
2 3 -3 -3
```

### 输出

```
0 0
2 1
-1 -2
```

## 样例 #3

### 输入

```
5 7
1 2 0 0
1 2 0 0
2 3 0 0
3 1 0 0
2 1 0 0
3 2 0 0
4 5 0 0
```

### 输出

```
0 0
0 0
0 0
undecidable
undecidable
```

