# [SWERC 2023] Nicest view

## 题目描述

:::align{center}

![](https://espresso.codeforces.com/93613cfd23ca0223b6f9aa573bf5381a7646cd95.png)

:::

Paris is so crowded with tourists during the Olympic games! You want to escape the city and go on a hike on a linear trail path, going from left to right. Every kilometre on that trail, including at start and end, is a milestone, on which is written the stone's altitude. The slope between two consecutive stones is constant, and no two stones have the same altitude.


Planning to come back with your friends, you try to identify the point of the hike at which you had the nicest view. The beauty of a point of view is defined as the distance (measured in kilometres) between your position and the leftmost position that you can see on your hike and that is at the same altitude as you are. If such a previous position fails to exist, it means that you can see the city and its smog, and the beauty of that view is zero.


You have listed the altitudes of the milestones. What is the maximal beauty on your hike?

## 样例 #1

### 输入

```
7
0 5 3 1 4 8 2```

### 输出

```
13/4```

## 样例 #2

### 输入

```
5
3 5 8 7 1```

### 输出

```
0```

