---
title: "Animal Observation (easy version)"
layout: "post"
diff: 提高+/省选-
pid: CF1304F1
tag: []
---

# Animal Observation (easy version)

## 题目描述

The only difference between easy and hard versions is the constraint on $ k $ .

Gildong loves observing animals, so he bought two cameras to take videos of wild animals in a forest. The color of one camera is red, and the other one's color is blue.

Gildong is going to take videos for $ n $ days, starting from day $ 1 $ to day $ n $ . The forest can be divided into $ m $ areas, numbered from $ 1 $ to $ m $ . He'll use the cameras in the following way:

- On every odd day ( $ 1 $ -st, $ 3 $ -rd, $ 5 $ -th, ...), bring the red camera to the forest and record a video for $ 2 $ days.
- On every even day ( $ 2 $ -nd, $ 4 $ -th, $ 6 $ -th, ...), bring the blue camera to the forest and record a video for $ 2 $ days.
- If he starts recording on the $ n $ -th day with one of the cameras, the camera records for only one day.

Each camera can observe $ k $ consecutive areas of the forest. For example, if $ m=5 $ and $ k=3 $ , he can put a camera to observe one of these three ranges of areas for two days: $ [1,3] $ , $ [2,4] $ , and $ [3,5] $ .

Gildong got information about how many animals will be seen in each area each day. Since he would like to observe as many animals as possible, he wants you to find the best way to place the two cameras for $ n $ days. Note that if the two cameras are observing the same area on the same day, the animals observed in that area are counted only once.

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ k $ ( $ 1 \le n \le 50 $ , $ 1 \le m \le 2 \cdot 10^4 $ , $ 1 \le k \le min(m,20) $ ) – the number of days Gildong is going to record, the number of areas of the forest, and the range of the cameras, respectively.

Next $ n $ lines contain $ m $ integers each. The $ j $ -th integer in the $ i+1 $ -st line is the number of animals that can be seen on the $ i $ -th day in the $ j $ -th area. Each number of animals is between $ 0 $ and $ 1000 $ , inclusive.

## 输出格式

Print one integer – the maximum number of animals that can be observed.

## 说明/提示

The optimal way to observe animals in the four examples are as follows:

Example 1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F1/d3d7ccf6369074c42d9cb3c6953ef69b03850081.png)Example 2:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F1/cb62ca568d7dec1d0d903ae38c9fff43fc945cf2.png)Example 3:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F1/3e18878b2213816dafe01bd460999dff35151fc8.png)Example 4:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F1/dc814ca536d6cd407d5a49988e0923d5d85a8629.png)

## 样例 #1

### 输入

```
4 5 2
0 2 1 1 0
0 0 3 1 2
1 0 4 3 1
3 3 0 0 4
```

### 输出

```
25
```

## 样例 #2

### 输入

```
3 3 1
1 2 3
4 5 6
7 8 9
```

### 输出

```
31
```

## 样例 #3

### 输入

```
3 3 2
1 2 3
4 5 6
7 8 9
```

### 输出

```
44
```

## 样例 #4

### 输入

```
3 3 3
1 2 3
4 5 6
7 8 9
```

### 输出

```
45
```

