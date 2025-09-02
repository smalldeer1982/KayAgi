---
title: "Kuriyama Mirai's Stones"
layout: "post"
diff: 普及/提高-
pid: CF433B
tag: []
---

# Kuriyama Mirai's Stones

## 题目描述

Kuriyama Mirai has killed many monsters and got many (namely $ n $ ) stones. She numbers the stones from $ 1 $ to $ n $ . The cost of the $ i $ -th stone is $ v_{i} $ . Kuriyama Mirai wants to know something about these stones so she will ask you two kinds of questions:

1. She will tell you two numbers, $ l $ and $ r (1<=l<=r<=n) $ , and you should tell her ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF433B/a68d6654cf2b25883008b776a62307a377b6be58.png).
2. Let $ u_{i} $ be the cost of the $ i $ -th cheapest stone (the cost that will be on the $ i $ -th place if we arrange all the stone costs in non-decreasing order). This time she will tell you two numbers, $ l $ and $ r (1<=l<=r<=n) $ , and you should tell her ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF433B/81f5c65268118775753c7eebcdd998c0bae9a99d.png).

For every question you should give the correct answer, or Kuriyama Mirai will say "fuyukai desu" and then become unhappy.

## 输入格式

The first line contains an integer $ n (1<=n<=10^{5}) $ . The second line contains $ n $ integers: $ v_{1},v_{2},...,v_{n} (1<=v_{i}<=10^{9}) $ — costs of the stones.

The third line contains an integer $ m (1<=m<=10^{5}) $ — the number of Kuriyama Mirai's questions. Then follow $ m $ lines, each line contains three integers $ type $ , $ l $ and $ r (1<=l<=r<=n; 1<=type<=2) $ , describing a question. If $ type $ equal to $ 1 $ , then you should output the answer for the first question, else you should output the answer for the second one.

## 输出格式

Print $ m $ lines. Each line must contain an integer — the answer to Kuriyama Mirai's question. Print the answers to the questions in the order of input.

## 说明/提示

Please note that the answers to the questions may overflow 32-bit integer type.

## 样例 #1

### 输入

```
6
6 4 2 7 2 7
3
2 3 6
1 3 4
1 1 6

```

### 输出

```
24
9
28

```

## 样例 #2

### 输入

```
4
5 5 2 3
10
1 2 4
2 1 4
1 1 1
2 1 4
2 1 2
1 1 1
1 3 3
1 1 3
1 4 4
1 2 2

```

### 输出

```
10
15
5
15
5
5
2
12
3
5

```

