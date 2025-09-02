---
title: "Commentator problem"
layout: "post"
diff: 提高+/省选-
pid: CF2C
tag: ['模拟', '搜索', '模拟退火']
---

# Commentator problem

## 题目描述

The Olympic Games in Bercouver are in full swing now. Here everyone has their own objectives: sportsmen compete for medals, and sport commentators compete for more convenient positions to give a running commentary. Today the main sport events take place at three round stadiums, and the commentator's objective is to choose the best point of observation, that is to say the point from where all the three stadiums can be observed. As all the sport competitions are of the same importance, the stadiums should be observed at the same angle. If the number of points meeting the conditions is more than one, the point with the maximum angle of observation is prefered.

Would you, please, help the famous Berland commentator G. Berniev to find the best point of observation. It should be noted, that the stadiums do not hide each other, the commentator can easily see one stadium through the other.

## 输入格式

The input data consists of three lines, each of them describes the position of one stadium. The lines have the format $ x,y,r $ , where ( $ x,y $ ) are the coordinates of the stadium's center ( $ -10^{3}<=x,y<=10^{3} $ ), and $ r $ ( $ 1<=r<=10^{3} $ ) is its radius. All the numbers in the input data are integer, stadiums do not have common points, and their centers are not on the same line.

## 输出格式

Print the coordinates of the required point with five digits after the decimal point. If there is no answer meeting the conditions, the program shouldn't print anything. The output data should be left blank.

## 样例 #1

### 输入

```
0 0 10
60 0 10
30 30 10

```

### 输出

```
30.00000 0.00000

```

