---
title: "Colorful Points"
layout: "post"
diff: 提高+/省选-
pid: CF909D
tag: []
---

# Colorful Points

## 题目描述

You are given a set of points on a straight line. Each point has a color assigned to it. For point $ a $ , its neighbors are the points which don't have any other points between them and $ a $ . Each point has at most two neighbors - one from the left and one from the right.

You perform a sequence of operations on this set of points. In one operation, you delete all points which have a neighbor point of a different color than the point itself. Points are deleted simultaneously, i.e. first you decide which points have to be deleted and then delete them. After that you can perform the next operation etc. If an operation would not delete any points, you can't perform it.

How many operations will you need to perform until the next operation does not have any points to delete?

## 输入格式

Input contains a single string of lowercase English letters 'a'-'z'. The letters give the points' colors in the order in which they are arranged on the line: the first letter gives the color of the leftmost point, the second gives the color of the second point from the left etc.

The number of the points is between 1 and $ 10^{6} $ .

## 输出格式

Output one line containing an integer - the number of operations which can be performed on the given set of points until there are no more points to delete.

## 说明/提示

In the first test case, the first operation will delete two middle points and leave points "ab", which will be deleted with the second operation. There will be no points left to apply the third operation to.

In the second test case, the first operation will delete the four points in the middle, leaving points "aa". None of them have neighbors of other colors, so the second operation can't be applied.

## 样例 #1

### 输入

```
aabb

```

### 输出

```
2

```

## 样例 #2

### 输入

```
aabcaa

```

### 输出

```
1

```

