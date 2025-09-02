# [ARC041C] ウサギ跳び

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc041/tasks/arc041_c

$ L $ 個のマスが横一列に並んでいる。 マスの上には $ N $ 匹のウサギがいる。 $ i $ ($ 1≦i≦N $) 番目のウサギは、左から $ x_i $ 番目のマスにいる。 ただし、$ 1≦x_1\ <\ x_2\ <\ ..\ <\ x_N≦L $ を満たす。 また、ウサギはそれぞれ左向きまたは右向きである。

それぞれのウサギは、自分の $ 1 $ つ前にマスが存在し、そこに他のウサギがいなければ、ジャンプして自分の $ 1 $ つ前のマスへ移動できる。

ウサギがジャンプする順番を自由に選べるとき、ジャンプの総回数の最大値を求めよ。

## 说明/提示

### Sample Explanation 1

図のようにジャンプすればよい。 !\[\](https://arc041.contest.atcoder.jp/img/arc/041/qawsedrftgyhujikolp/rabbit\_1.png)

### Sample Explanation 2

図のようにジャンプすればよい。 !\[\](https://arc041.contest.atcoder.jp/img/arc/041/qawsedrftgyhujikolp/rabbit\_2.png)

### Sample Explanation 3

どのウサギもジャンプできない。

## 样例 #1

### 输入

```
1 5
1 R```

### 输出

```
4```

## 样例 #2

### 输入

```
4 5
1 R
3 L
4 L
5 L```

### 输出

```
3```

## 样例 #3

### 输入

```
4 10
1 L
5 R
6 L
10 R```

### 输出

```
0```

