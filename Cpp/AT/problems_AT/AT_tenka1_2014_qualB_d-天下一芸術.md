---
title: "天下一芸術"
layout: "post"
diff: 省选/NOI-
pid: AT_tenka1_2014_qualB_d
tag: []
---

# 天下一芸術

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2014-qualb/tasks/tenka1_2014_qualB_d



## 输入格式

> $ N $ $ A_1 $ $ A_2 $ : $ A_N $ $ H $ $ W $ $ B_{1,1} $ $ B_{1,2} $ ... $ B_{1,W} $ $ B_{2,1} $ $ B_{2,2} $ ... $ B_{2,W} $ : $ B_{H,1} $ $ B_{H,2} $ ... $ B_{H,W} $

- 1行目では、使用できるペンキの数を表す整数 $ N $ ($ 1\ \leq{}\ N\ \leq{}\ 17 $) が与えられる。
- 2行目から $ N $ 行では、各ペンキの濃さを表す整数 $ A_i $ ($ 0\ \leq{}\ A_i\ \leq{}\ 255 $) が与えられる。
- $ N+2 $ 行目では、設計図の高さを表す整数 $ H $ ($ 1\ \leq{}\ H\ \leq{}\ 200 $) と、設計図の幅を表す整数 $ W $ ($ 1\ \leq{}\ W\ \leq{}\ 200 $) が与えられる。
- $ N+3 $ 行目から $ H $ 行は設計図の情報が与えられる。そのうちの $ y $ ($ 1\ \leq{}\ y\ \leq{}\ H $) 行目には、各マスの番号がスペース区切りで $ W $ 個与えられる。$ y $ 行目の左側から $ x $ ($ 1\ \leq{}\ x\ \leq{}\ W $)番目に、設計図の上から $ y $ マス、左から $ x $ マスの位置のマス目の番号、整数 $ B_{y,x} $ ($ 0\ \leq{}\ B_{y,x}\ \leq{}\ N\ -\ 1 $) が与えられる。

## 输出格式

与えられたペンキで設計図どおりに塗ることが可能なら1、不可能なら0を1行で出力せよ。出力の末尾には改行をいれること。

## 说明/提示

### 部分点

- $ 1\ \leq{}\ N\ \leq{}\ 5 $ かつ $ 1\ \leq{}\ H,\ W\ \leq{}\ 5 $のすべてのテストケースに正解した場合、部分点として35点を与える
- $ 1\ \leq{}\ N\ \leq{}\ 9 $ のすべてのテストケースに正解した場合、部分点としてさらに40点を与える

### Sample Explanation 1

\### 出力例1 ```

```
<pre class="prettyprint linenums">1
```

与えられたペンキを上から順にA, B, C, D, Eとすると以下の順番で塗りわけることが可能です。

 ```
BBB
BBB
```

 ```
BBB
AAA
```

 ```
BCB
AAA
```

 ```
BCB
ADA
```

今回の塗り方ではEは使用しませんでした。<h3>Sample Explanation 2</h3><p>### 出力例2

 ```
</p><pre class="prettyprint linenums">0
```

与えられたペンキで塗ることはできません。<h3>Sample Explanation 3</h3><p>### 出力例3

 ```
</p><pre class="prettyprint linenums">0
```

与えられたペンキで塗ることはできません。<h3>Sample Explanation 4</h3><p>### 出力例4

 ```
</p><pre class="prettyprint linenums">1
```

与えられたペンキを上から順にA, B, C, D, Eとすると以下の順番で塗りわけることが可能です。

 ```
A A # # #
A A # # #
A A # # #
A A # # #
A A # # #
```

 ```
A A B B #
A A B B #
A A B B #
A A B B #
A A B B #
```

 ```
A A B B E
A A B B E
A A B B E
A A B B E
A A B B E
```

 ```
A D D D E
A D D D E
A D D D E
A A B B E
A A B B E
```

 ```
A D D D E
A D D C C
A D D C C
A A B C C
A A B B E
```
```

## 样例 #1

### 输入

```
5
4
0
4
10
4
2 3
3 1 3
0 2 0
```

### 输出

```
None
```

## 样例 #2

### 输入

```
5
4
0
4
10
4
2 4
3 1 2 3
0 1 2 0
```

### 输出

```
None
```

## 样例 #3

### 输入

```
2
1
2
2 2
0 1
1 0
```

### 输出

```
None
```

## 样例 #4

### 输入

```
5
1
1
66
30
1
5 5
3 4 4 4 2
3 4 4 0 0
3 4 4 0 0
3 3 1 0 0
3 3 1 1 2
```

### 输出

```
None
```

