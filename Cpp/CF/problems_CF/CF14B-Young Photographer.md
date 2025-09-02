---
title: "Young Photographer"
layout: "post"
diff: 普及-
pid: CF14B
tag: []
---

# Young Photographer

## 题目描述

Among other things, Bob is keen on photography. Especially he likes to take pictures of sportsmen. That was the reason why he placed himself in position $ x_{0} $ of a long straight racetrack and got ready to take pictures. But the problem was that not all the runners passed him. The total amount of sportsmen, training at that racetrack, equals $ n $ . And each of them regularly runs distances within a particular segment of the racetrack, which is the same for each sportsman. For example, the first sportsman runs from position $ a_{1} $ to position $ b_{1} $ , the second — from $ a_{2} $ to $ b_{2} $

What is the minimum distance that Bob should move to have a chance to take pictures of each sportsman? Bob can take a picture of a sportsman, if he stands within the segment that this sportsman covers on the racetrack.

## 输入格式

The first line of the input file contains integers $ n $ and $ x_{0} $ ( $ 1<=n<=100 $ ; $ 0<=x_{0}<=1000 $ ). The following $ n $ lines contain pairs of integers $ a_{i},b_{i} $ ( $ 0<=a_{i},b_{i}<=1000 $ ; $ a_{i}≠b_{i} $ ).

## 输出格式

Output the required minimum distance in the same units as the positions on the racetrack. If there is no such a position, output -1.

## 样例 #1

### 输入

```
3 3
0 7
14 2
4 6

```

### 输出

```
1

```

