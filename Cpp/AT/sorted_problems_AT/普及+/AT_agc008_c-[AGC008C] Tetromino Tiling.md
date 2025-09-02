---
title: "[AGC008C] Tetromino Tiling"
layout: "post"
diff: 普及+/提高
pid: AT_agc008_c
tag: ['贪心']
---

# [AGC008C] Tetromino Tiling

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc008/tasks/agc008_c

正方形のマスを $ 4 $ 個繋げた形をテトロミノといいます。 次の $ 7 $ 種類のテトロミノを順に I, O, T, J, L, S, Z 型と呼ぶことにします。

 ![a60bcb8e9e8f22e3af51049eda063392.png](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc008_c/41da26817a0aa4921d5f3228c5ba880f4ed240c0.png)

すぬけ君は I, O, T, J, L, S, Z 型のテトロミノをそれぞれ $ a_I $, $ a_O $, $ a_T $, $ a_J $, $ a_L $, $ a_S $, $ a_Z $ 個ずつ持っています。 すぬけ君はこれらのテトロミノのうち $ K $ 個を組み合わせ、縦 $ 2 $ マス、横 $ 2K $ マスの長方形を作ろうとしています。 このとき、すぬけ君は次のルールに従います。

- 各テトロミノを置くとき、回転はできるが、反転はできない。
- 長方形の各マスにはちょうど $ 1 $ 個のテトロミノが置かれているようにする。
- 長方形の外部にテトロミノが置かれていないようにする。

すぬけ君はできるだけ大きい長方形を作ろうとしています。 $ K $ の最大値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ a_I $ $ a_O $ $ a_T $ $ a_J $ $ a_L $ $ a_S $ $ a_Z $

## 输出格式

$ K $ の最大値を出力せよ。 長方形を作ることができない場合、`0` を出力せよ。

## 说明/提示

### 制約

- $ 0\ <\ =a_I,a_O,a_T,a_J,a_L,a_S,a_Z\ <\ =10^9 $
- $ a_I+a_O+a_T+a_J+a_L+a_S+a_Z\ >\ =1 $

### Sample Explanation 1

たとえば、図のように組み合わせればよいです。 !\[45515ed2a1dd5e41c5e4ca1f39323d8e.png\](https://atcoder.jp/img/agc008/45515ed2a1dd5e41c5e4ca1f39323d8e.png)

### Sample Explanation 2

長方形を作ることができません。

## 样例 #1

### 输入

```
2 1 1 0 0 0 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
0 0 10 0 0 0 0
```

### 输出

```
0
```

