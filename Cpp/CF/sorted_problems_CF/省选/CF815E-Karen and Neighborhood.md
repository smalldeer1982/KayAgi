---
title: "Karen and Neighborhood"
layout: "post"
diff: 省选/NOI-
pid: CF815E
tag: []
---

# Karen and Neighborhood

## 题目描述

It's been long after the events of the previous problems, and Karen has now moved on from student life and is looking to relocate to a new neighborhood.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815E/8bd2a5609d0d80a04305caa2f81f70648ac35159.png)The neighborhood consists of $ n $ houses in a straight line, labelled $ 1 $ to $ n $ from left to right, all an equal distance apart.

Everyone in this neighborhood loves peace and quiet. Because of this, whenever a new person moves into the neighborhood, he or she always chooses the house whose minimum distance to any occupied house is maximized. If there are multiple houses with the maximum possible minimum distance, he or she chooses the leftmost one.

Note that the first person to arrive always moves into house $ 1 $ .

Karen is the $ k $ -th person to enter this neighborhood. If everyone, including herself, follows this rule, which house will she move into?

## 输入格式

The first and only line of input contains two integers, $ n $ and $ k $ ( $ 1<=k<=n<=10^{18} $ ), describing the number of houses in the neighborhood, and that Karen was the $ k $ -th person to move in, respectively.

## 输出格式

Output a single integer on a line by itself, the label of the house Karen will move into.

## 说明/提示

In the first test case, there are $ 6 $ houses in the neighborhood, and Karen is the fourth person to move in:

1. The first person moves into house $ 1 $ .
2. The second person moves into house $ 6 $ .
3. The third person moves into house $ 3 $ .
4. The fourth person moves into house $ 2 $ .

In the second test case, there are $ 39 $ houses in the neighborhood, and Karen is the third person to move in:

1. The first person moves into house $ 1 $ .
2. The second person moves into house $ 39 $ .
3. The third person moves into house $ 20 $ .

## 样例 #1

### 输入

```
6 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
39 3

```

### 输出

```
20

```

