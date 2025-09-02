# Grid Coloring

## 题目描述

There is a $ n\times m $ grid with each cell initially white. You have to color all the cells one-by-one. After you color a cell, all the colored cells furthest from it receive a penalty. Find a coloring order, where no cell has more than $ 3 $ penalties.

Note that $ n $ and $ m $ are both odd.

The distance metric used is the [chessboard distance](https://en.wikipedia.org/wiki/Chebyshev_distance) while we decide ties between cells with [Manhattan distance](https://en.wikipedia.org/wiki/Taxicab_geometry#Formal_definition). Formally, a cell $ (x_2, y_2) $ is further away than $ (x_3, y_3) $ from a cell $ (x_1, y_1) $ if one of the following holds:

- $ \max\big(\lvert x_1 - x_2 \rvert, \lvert y_1 - y_2 \rvert\big)>\max\big(\lvert x_1 - x_3 \rvert, \lvert y_1 - y_3 \rvert\big) $
- $ \max\big(\lvert x_1 - x_2 \rvert, \lvert y_1 - y_2 \rvert\big)=\max\big(\lvert x_1 - x_3 \rvert, \lvert y_1 - y_3 \rvert\big) $ and $ \lvert x_1 - x_2 \rvert + \lvert y_1 - y_2 \rvert>\lvert x_1 - x_3 \rvert + \lvert y_1 - y_3 \rvert $

It can be proven that at least one solution always exists.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118E/0999d880eddd8a91b5091ba07c8decca3603697f.png) Example showing penalty changes after coloring the center of a $ 5 \times 5 $ grid. The numbers indicate the penalty of the cells.

## 说明/提示

In the first test case, the grid can be colored as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118E/218c1c0d1bb1b99ba12b524b28250a50bd75964e.png) The numbers indicate the penalty of the cells.

## 样例 #1

### 输入

```
3
3 3
1 1
1 5```

### 输出

```
2 1
2 3
2 2
1 1
3 2
3 3
3 1
1 3
1 2

1 1

1 2
1 4
1 5
1 1
1 3```

# 题解

## 作者：3a51_ (赞：2)

手搓几组数据不难凭直觉发现，越靠近边缘的位置越有可能被当作 "furthest point" 导致贡献超过 $3$。所以一个很 naive 的想法就是从中间开始往外边涂色。

考虑递推关系，从 $(n-2)\times (n-2)$ 推出 $n\times n$ 的情况。常规版本只要求贡献不超过 $3$，构造起来并不算难。对于新加入的左边和右边，从中间点 $(i,l)$ 和 $(i,r)$ 开始，按照 $(i-k,l)$，$(i+k,r)$，$(i+k,l)$，$(i-k,r)$ 的顺序直到角落即可。上下边同理。

最后从 $\min(n,m)\times \min(n,m)$ 推到 $n\times m$ 也是简单的。延续从中间到两边的思路，只不过只用涂一组对边即可。

考虑证明方案的合法性。对于每一次递推，除了 $(i,l)$ 的贡献会给到原来的 $(n-2)\times (n-2)$ 的正方形以外，其他的贡献会全部落在新加入的点上面，且每个点都不超过 $2$。也就是说，由于所有新加入的点的贡献均 $\leq 2$，再下一次递推的时候一定不会超过 $3$。而且考虑到只有纵向的初始点和横向的初始点的贡献为 $2$，延续这个思路的话，如果写的好完全可以做到 $\max\text{penalty}\leq 2$。

给个 $n=7,m=9$ 的例子，方便理解（数字表示涂色顺序）：
```
60 46 42 38 36 40 44 49 63 
56 32 22 18 16 20 25 35 59 
52 28 12 06 04 09 15 31 55 
50 26 10 02 01 03 11 27 51 
54 30 14 08 05 07 13 29 53 
58 34 24 21 17 19 23 33 57 
62 48 45 41 37 39 43 47 61
```

赛时提交记录：[submission](https://codeforces.com/contest/2118/submission/324116670)

---

