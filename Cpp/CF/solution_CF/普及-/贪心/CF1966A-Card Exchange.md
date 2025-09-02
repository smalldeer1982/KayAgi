# Card Exchange

## 题目描述

You have a hand of $ n $ cards, where each card has a number written on it, and a fixed integer $ k $ . You can perform the following operation any number of times:

- Choose any $ k $ cards from your hand that all have the same number.
- Exchange these cards for $ k-1 $ cards, each of which can have any number you choose (including the number written on the cards you just exchanged).

Here is one possible sequence of operations for the first example case, which has $ k=3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1966A/25cf30b9964a74e1022f2c7cdd313093587901b5.png)What is the minimum number of cards you can have in your hand at the end of this process?

## 说明/提示

The first example case corresponds to the picture above. The sequence of operations displayed there is optimal, so the answer is $ 2 $ .

In the second example case, no operations can be performed, so the answer is $ 1 $ .

In the fourth example case, you can repeatedly select $ 4 $ cards numbered with $ 1 $ and replace them with $ 3 $ cards numbered with $ 1 $ , until there are $ 3 $ cards left.

## 样例 #1

### 输入

```
7
5 3
4 1 1 4 4
1 10
7
7 2
4 2 1 100 5 2 3
10 4
1 1 1 1 1 1 1 1 1 1
5 2
3 8 1 48 7
6 2
10 20 30 10 20 40
6 3
10 20 30 10 20 40```

### 输出

```
2
1
1
3
5
1
6```

