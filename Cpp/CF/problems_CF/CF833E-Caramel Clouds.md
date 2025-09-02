---
title: "Caramel Clouds"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF833E
tag: []
---

# Caramel Clouds

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833E/db40d025825b9026548b6b558f5519ab6e034eec.png)
 
 It is well-known that the best decoration for a flower bed in Sweetland are vanilla muffins. Seedlings of this plant need sun to grow up. Slastyona has $ m $ seedlings, and the $ j $ -th seedling needs at least $ k_{j} $ minutes of sunlight to grow up.

Most of the time it's sunny in Sweetland, but sometimes some caramel clouds come, the $ i $ -th of which will appear at time moment (minute) $ l_{i} $ and disappear at time moment $ r_{i} $ . Of course, the clouds make shadows, and the seedlings can't grow when there is at least one cloud veiling the sun.

Slastyona wants to grow up her muffins as fast as possible. She has exactly $ C $ candies, which is the main currency in Sweetland.

One can dispel any cloud by paying $ c_{i} $ candies. However, in order to comply with Sweetland's Department of Meteorology regulations, one can't dispel more than two clouds.

Slastyona hasn't decided yet which of the $ m $ seedlings will be planted at the princess' garden, so she needs your help. For each seedling determine the earliest moment it can grow up if Slastyona won't break the law and won't spend more candies than she has. Note that each of the seedlings is considered independently.

The seedlings start to grow at time moment $ 0 $ .

## 输入格式

The first line contains two integers $ n $ and $ C $ $ (0<=n<=3·10^{5},0<=C<=10^{9}) $ – the number of caramel clouds and the number of candies Slastyona has.

The next $ n $ lines contain three integers each: $ l_{i},r_{i},c_{i} $ $ (0<=l_{i},r_{i}<=10^{9},0<=c_{i}<=10^{9}) $ , describing one caramel cloud.

The next line contains single integer $ m $ ( $ 1<=m<=3·10^{5}) $ – the number of seedlings. Each of the seedlings is described with one integer $ k_{j} $ $ (1<=k_{j}<=10^{9}) $ – the required number of sunny minutes.

## 输出格式

For each seedling print one integer – the minimum minute Slastyona can grow it up.

## 说明/提示

Consider the first example. For each $ k $ it is optimal to dispel clouds $ 1 $ and $ 3 $ . Then the remaining cloud will give shadow on time segment $ [1..6] $ . So, intervals $ [0..1] $ and $ [6..inf) $ are sunny.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833E/1b1598777f9deeee0ae38fd2a6c94fc4108cc67e.png)In the second example for $ k=1 $ it is not necessary to dispel anything, and for $ k=5 $ the best strategy is to dispel clouds $ 2 $ and $ 3 $ . This adds an additional sunny segment $ [4..8] $ , which together with $ [0..1] $ allows to grow up the muffin at the eight minute.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833E/af2fb1c509883914ea43c944e79abe6c41c5f097.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833E/a2ce6a5cf5c5c248407a66179aa4b0fa365f0d80.png)If the third example the two seedlings are completely different. For the first one it is necessary to dispel cloud $ 1 $ and obtain a sunny segment $ [0..10] $ . However, the same strategy gives answer $ 180 $ for the second seedling. Instead, we can dispel cloud $ 2 $ , to make segments $ [0..3] $ and $ [7..inf) $ sunny, and this allows up to shorten the time to $ 104 $ .

## 样例 #1

### 输入

```
3 5
1 7 1
1 6 2
1 7 1
3
7
2
5

```

### 输出

```
12
7
10

```

## 样例 #2

### 输入

```
3 15
1 4 17
2 8 6
4 8 9
2
5
1

```

### 输出

```
8
1

```

## 样例 #3

### 输入

```
2 10
3 7 9
10 90 10
2
10
100

```

### 输出

```
10
104

```

