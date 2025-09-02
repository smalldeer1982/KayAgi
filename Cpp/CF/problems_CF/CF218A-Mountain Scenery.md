---
title: "Mountain Scenery"
layout: "post"
diff: 普及-
pid: CF218A
tag: []
---

# Mountain Scenery

## 题目描述

Little Bolek has found a picture with $ n $ mountain peaks painted on it. The $ n $ painted peaks are represented by a non-closed polyline, consisting of $ 2n $ segments. The segments go through $ 2n+1 $ points with coordinates $ (1,y_{1}) $ , $ (2,y_{2}) $ , $ ... $ , $ (2n+1,y_{2n+1}) $ , with the $ i $ -th segment connecting the point $ (i,y_{i}) $ and the point $ (i+1,y_{i+1}) $ . For any even $ i $ $ (2<=i<=2n) $ the following condition holds: $ y_{i-1}&lt;y_{i} $ and $ y_{i}&gt;y_{i+1} $ .

We shall call a vertex of a polyline with an even $ x $ coordinate a mountain peak.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF218A/96f9e39adc23f097d41530b53dba00529f48c7bd.png) The figure to the left shows the initial picture, the figure to the right shows what the picture looks like after Bolek's actions. The affected peaks are marked red, $ k $ = 2. Bolek fancied a little mischief. He chose exactly $ k $ mountain peaks, rubbed out the segments that went through those peaks and increased each peak's height by one (that is, he increased the $ y $ coordinate of the corresponding points). Then he painted the missing segments to get a new picture of mountain peaks. Let us denote the points through which the new polyline passes on Bolek's new picture as $ (1,r_{1}) $ , $ (2,r_{2}) $ , $ ... $ , $ (2n+1,r_{2n+1}) $ .

Given Bolek's final picture, restore the initial one.

## 输入格式

The first line contains two space-separated integers $ n $ and $ k $ $ (1<=k<=n<=100) $ . The next line contains $ 2n+1 $ space-separated integers $ r_{1},r_{2},...,r_{2n+1} $ $ (0<=r_{i}<=100) $ — the $ y $ coordinates of the polyline vertices on Bolek's picture.

It is guaranteed that we can obtain the given picture after performing the described actions on some picture of mountain peaks.

## 输出格式

Print $ 2n+1 $ integers $ y_{1},y_{2},...,y_{2n+1} $ — the $ y $ coordinates of the vertices of the polyline on the initial picture. If there are multiple answers, output any one of them.

## 样例 #1

### 输入

```
3 2
0 5 3 5 1 5 2

```

### 输出

```
0 5 3 4 1 4 2 

```

## 样例 #2

### 输入

```
1 1
0 2 0

```

### 输出

```
0 1 0 

```

