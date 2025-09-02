# 题目信息

# 木

## 题目描述

[problemUrl]: https://atcoder.jp/contests/indeednow-qualb/tasks/indeednow_2015_qualc_3

木とは、頂点とそれを結ぶ辺からなる構造「グラフ」の $ 1 $ 種で、頂点の数を $ N $ 個とすると、辺は $ N-1 $ 本あり、どの頂点も他の全ての頂点に辺で間接・直接的につながっています。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_indeednow_2015_qualc_3/db302ed5e6211ee095f87c2aa4b931b136442faf.png)

この問題では、頂点は $ N $ 個あり、$ 1 $ から $ N $ まで番号付けられています。

木が与えられたとき、以下の操作で作られる数列のうち、辞書順で最小のものを出力してください。

1. 頂点1を選ぶ。
2. 今まで選ばれた頂点と辺で結ばれている頂点のうち、まだ選ばれていない頂点を1つ選ぶ、という操作を選ばれていない頂点が無くなるまで繰り返す。
3. 頂点の番号を選ばれた順に並べた数列を作る。

ただし、長さ $ N $ の列 $ A=\{a_1,a_2,\ ...,a_N\} $ と $ B=\{b_1,b_2,\ ...,b_N\} $ に対し、辞書順で $ A $ が $ B $ より小さいとは、

- $ i\ で\ a_i $=$ b_i $
- $ i\ =\ k $ で $ a_i $b\_i

となるような $ k(1≦k≦N) $ が存在するということです。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 50 $ 点分のテストケースにおいて、 $ 1\ ≦\ N\ ≦\ 3,000 $ を満たす。

### Sample Explanation 1

問題文中の図の木です。 まず、初めに頂点 $ 1 $ を選びます。 !\[\](http://indeednow-qualb.contest.atcoder.jp/img/other/indeednow-qualb/C\_sample2.png) 次に、頂点 $ 3 $ を選びます。頂点 $ 2 $ は今まで選んだ頂点(この場合、頂点 $ 1 $ のみ)と辺で結ばれていないので、選ぶことができないことに注意してください。 !\[\](http://indeednow-qualb.contest.atcoder.jp/img/other/indeednow-qualb/C\_sample3.png) 次に、頂点 $ 2 $ を選びます。 !\[\](http://indeednow-qualb.contest.atcoder.jp/img/other/indeednow-qualb/C\_sample4.png) 次に、頂点 $ 4 $ を選びます。 !\[\](http://indeednow-qualb.contest.atcoder.jp/img/other/indeednow-qualb/C\_sample5.png) 頂点の番号を選んだ順に並べると、$ 1 $ $ 3 $ $ 2 $ $ 4 $ となります。この列より辞書順で小さい選び方は存在しません。

## 样例 #1

### 输入

```
4

1 3

1 4

2 3```

### 输出

```
1 3 2 4```

## 样例 #2

### 输入

```
6

1 2

2 3

2 6

6 4

1 5```

### 输出

```
1 2 3 5 6 4```

## 样例 #3

### 输入

```
7

1 5

5 2

5 3

5 7

5 6

6 4```

### 输出

```
1 5 2 3 6 4 7```

# AI分析结果



---
处理用时：161.10秒