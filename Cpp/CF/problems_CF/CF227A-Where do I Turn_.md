---
title: "Where do I Turn?"
layout: "post"
diff: 普及/提高-
pid: CF227A
tag: []
---

# Where do I Turn?

## 题目描述

Trouble came from the overseas lands: a three-headed dragon Gorynych arrived. The dragon settled at point $ C $ and began to terrorize the residents of the surrounding villages.

A brave hero decided to put an end to the dragon. He moved from point $ A $ to fight with Gorynych. The hero rode from point $ A $ along a straight road and met point $ B $ on his way. The hero knows that in this land for every pair of roads it is true that they are either parallel to each other, or lie on a straight line, or are perpendicular to each other. He also knows well that points $ B $ and $ C $ are connected by a road. So the hero must either turn 90 degrees to the left or continue riding straight ahead or turn 90 degrees to the right. But he forgot where the point $ C $ is located.

Fortunately, a Brave Falcon flew right by. It can see all three points from the sky. The hero asked him what way to go to get to the dragon's lair.

If you have not got it, you are the falcon. Help the hero and tell him how to get him to point $ C $ : turn left, go straight or turn right.

At this moment the hero is believed to stand at point $ B $ , turning his back to point $ A $ .

## 输入格式

The first input line contains two space-separated integers $ x_{a},y_{a} $ $ (|x_{a}|,|y_{a}|<=10^{9}) $ — the coordinates of point $ A $ . The second line contains the coordinates of point $ B $ in the same form, the third line contains the coordinates of point $ C $ .

It is guaranteed that all points are pairwise different. It is also guaranteed that either point $ B $ lies on segment $ AC $ , or angle $ ABC $ is right.

## 输出格式

Print a single line. If a hero must turn left, print "LEFT" (without the quotes); If he must go straight ahead, print "TOWARDS" (without the quotes); if he should turn right, print "RIGHT" (without the quotes).

## 说明/提示

The picture to the first sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF227A/e61b67213ead6cd60a9de674ba59a16f640ab902.png)The red color shows points A, B and C. The blue arrow shows the hero's direction. The green color shows the hero's trajectory.

The picture to the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF227A/009eb3489d47ef4ebc3672ec1f44c9cae16a8306.png)

## 样例 #1

### 输入

```
0 0
0 1
1 1

```

### 输出

```
RIGHT

```

## 样例 #2

### 输入

```
-1 -1
-3 -3
-4 -4

```

### 输出

```
TOWARDS

```

## 样例 #3

### 输入

```
-4 -6
-3 -7
-2 -6

```

### 输出

```
LEFT

```

