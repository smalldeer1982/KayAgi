---
title: "New Year Domino"
layout: "post"
diff: 省选/NOI-
pid: CF500E
tag: []
---

# New Year Domino

## 题目描述

Celebrating the new year, many people post videos of falling dominoes; Here's a list of them: https://www.youtube.com/results?search\_query=New+Years+Dominos

User ainta, who lives in a 2D world, is going to post a video as well.

There are $ n $ dominoes on a 2D Cartesian plane. $ i $ -th domino ( $ 1<=i<=n $ ) can be represented as a line segment which is parallel to the $ y $ -axis and whose length is $ l_{i} $ . The lower point of the domino is on the $ x $ -axis. Let's denote the $ x $ -coordinate of the $ i $ -th domino as $ p_{i} $ . Dominoes are placed one after another, so $ p_{1}&lt;p_{2}&lt;...&lt;p_{n-1}&lt;p_{n} $ holds.

User ainta wants to take a video of falling dominoes. To make dominoes fall, he can push a single domino to the right. Then, the domino will fall down drawing a circle-shaped orbit until the line segment totally overlaps with the x-axis.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/1cd8bce76e7268e84c7286ca2b5288f25521c70b.png)Also, if the $ s $ -th domino touches the $ t $ -th domino while falling down, the $ t $ -th domino will also fall down towards the right, following the same procedure above. Domino $ s $ touches domino $ t $ if and only if the segment representing $ s $ and $ t $ intersects.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/3f86ba9201ab03c6c9c4c879a8ca9ea2e8677f8f.png)See the picture above. If he pushes the leftmost domino to the right, it falls down, touching dominoes (A), (B) and (C). As a result, dominoes (A), (B), (C) will also fall towards the right. However, domino (D) won't be affected by pushing the leftmost domino, but eventually it will fall because it is touched by domino (C) for the first time.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/73c30bfd9b8a146d5c8d1eb8ad442e5fc6ef6a23.png)The picture above is an example of falling dominoes. Each red circle denotes a touch of two dominoes.

User ainta has $ q $ plans of posting the video. $ j $ -th of them starts with pushing the $ x_{j} $ -th domino, and lasts until the $ y_{j} $ -th domino falls. But sometimes, it could be impossible to achieve such plan, so he has to lengthen some dominoes. It costs one dollar to increase the length of a single domino by $ 1 $ . User ainta wants to know, for each plan, the minimum cost needed to achieve it. Plans are processed independently, i. e. if domino's length is increased in some plan, it doesn't affect its length in other plans. Set of dominos that will fall except $ x_{j} $ -th domino and $ y_{j} $ -th domino doesn't matter, but the initial push should be on domino $ x_{j} $ .

## 输入格式

The first line contains an integer $ n $ ( $ 2<=n<=2×10^{5} $ )— the number of dominoes.

Next $ n $ lines describe the dominoes. The $ i $ -th line ( $ 1<=i<=n $ ) contains two space-separated integers $ p_{i} $ , $ l_{i} $ ( $ 1<=p_{i},l_{i}<=10^{9} $ )— the $ x $ -coordinate and the length of the $ i $ -th domino. It is guaranteed that $ p_{1}&lt;p_{2}&lt;...&lt;p_{n-1}&lt;p_{n} $ .

The next line contains an integer $ q $ ( $ 1<=q<=2×10^{5} $ ) — the number of plans.

Next $ q $ lines describe the plans. The $ j $ -th line ( $ 1<=j<=q $ ) contains two space-separated integers $ x_{j} $ , $ y_{j} $ ( $ 1<=x_{j}&lt;y_{j}<=n $ ). It means the $ j $ -th plan is, to push the $ x_{j} $ -th domino, and shoot a video until the $ y_{j} $ -th domino falls.

## 输出格式

For each plan, print a line containing the minimum cost needed to achieve it. If no cost is needed, print 0.

## 说明/提示

Consider the example. The dominoes are set like the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/69189c949bbf1e3980e2fd50301d969359a4096f.png)Let's take a look at the 4th plan. To make the 6th domino fall by pushing the 2nd domino, the length of the 3rd domino (whose x-coordinate is 4) should be increased by 1, and the 5th domino (whose x-coordinate is 9) should be increased by 1 (other option is to increase 4th domino instead of 5th also by 1). Then, the dominoes will fall like in the picture below. Each cross denotes a touch between two dominoes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/6a17a43a3d05b4fceb521113b22deae344f88b4a.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/a58f494f30ab4662cf64a0b15656a9dc77793371.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/b71e767b3c7cf778590e571800dc614fef82da50.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/c0207539620df6be43ff32b6c6c47fe615cfd5fd.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF500E/8f6e8505e7e0c11feeece111e6108210f04cb5d4.png)

## 样例 #1

### 输入

```
6
1 5
3 3
4 4
9 2
10 1
12 1
4
1 2
2 4
2 5
2 6

```

### 输出

```
0
1
1
2

```

