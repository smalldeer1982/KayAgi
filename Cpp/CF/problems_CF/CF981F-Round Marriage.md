---
title: "Round Marriage"
layout: "post"
diff: 省选/NOI-
pid: CF981F
tag: ['二分', '枚举', '构造']
---

# Round Marriage

## 题目描述

It's marriage season in Ringland!

Ringland has a form of a circle's boundary of length $ L $ . There are $ n $ bridegrooms and $ n $ brides, and bridegrooms decided to marry brides.

Of course, each bridegroom should choose exactly one bride, and each bride should be chosen by exactly one bridegroom.

All objects in Ringland are located on the boundary of the circle, including the capital, bridegrooms' castles and brides' palaces. The castle of the $ i $ -th bridegroom is located at the distance $ a_i $ from the capital in clockwise direction, and the palace of the $ i $ -th bride is located at the distance $ b_i $ from the capital in clockwise direction.

Let's define the inconvenience of a marriage the maximum distance that some bride should walk along the circle from her palace to her bridegroom's castle in the shortest direction (in clockwise or counter-clockwise direction).

Help the bridegrooms of Ringland to choose brides in such a way that the inconvenience of the marriage is the smallest possible.

## 输入格式

The first line contains two integers $ n $ and $ L $ ( $ 1 \leq n \leq 2 \cdot 10^{5} $ , $ 1 \leq L \leq 10^{9} $ ) — the number of bridegrooms and brides and the length of Ringland.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < L $ ) — the distances from the capital to the castles of bridegrooms in clockwise direction.

The next line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \leq b_i < L $ ) — the distances from the capital to the palaces of brides in clockwise direction.

## 输出格式

In the only line print the smallest possible inconvenience of the wedding, where the inconvenience is the largest distance traveled by a bride.

## 说明/提示

In the first example the first bridegroom should marry the second bride, the second bridegroom should marry the first bride. This way, the second bride should walk the distance of $ 1 $ , and the first bride should also walk the same distance. Thus, the inconvenience is equal to $ 1 $ .

In the second example let $ p_i $ be the bride the $ i $ -th bridegroom will marry. One of optimal $ p $ is the following: $ (6,8,1,4,5,10,3,2,7,9) $ .

## 样例 #1

### 输入

```
2 4
0 1
2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 100
3 14 15 92 65 35 89 79 32 38
2 71 82 81 82 84 5 90 45 23

```

### 输出

```
27

```

