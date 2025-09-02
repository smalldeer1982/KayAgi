---
title: "Sheep"
layout: "post"
diff: 省选/NOI-
pid: CF309E
tag: ['贪心', '二分']
---

# Sheep

## 题目描述

Information technologies are developing and are increasingly penetrating into all spheres of human activity. Incredible as it is, the most modern technology are used in farming!

A large farm has a meadow with grazing sheep. Overall there are $ n $ sheep and each of them contains a unique number from 1 to $ n $ — because the sheep need to be distinguished and you need to remember information about each one, and they are so much alike! The meadow consists of infinite number of regions numbered from 1 to infinity. It's known that sheep $ i $ likes regions from $ l_{i} $ to $ r_{i} $ .

There are two shepherds taking care of the sheep: First and Second. First wakes up early in the morning and leads the sheep graze on the lawn. Second comes in the evening and collects all the sheep.

One morning, First woke up a little later than usual, and had no time to lead the sheep graze on the lawn. So he tied together every two sheep if there is a region they both like. First thought that it would be better — Second would have less work in the evening, because sheep won't scatter too much, being tied to each other!

In the evening Second came on the lawn, gathered the sheep and tried to line them up in a row. But try as he might, the sheep wouldn't line up as Second want! Second had neither the strength nor the ability to untie the sheep so he left them as they are, but with one condition: he wanted to line up the sheep so that the maximum distance between two tied sheep was as small as possible. The distance between the sheep is the number of sheep in the ranks that are between these two.

Help Second find the right arrangement.

## 输入格式

The first input line contains one integer $ n $ ( $ 1<=n<=2000 $ ). Each of the following $ n $ lines contains two integers $ l_{i} $ and $ r_{i} $ $ (1<=l_{i},r_{i}<=10^{9}; l_{i}<=r_{i}) $ .

## 输出格式

In the single output line print $ n $ space-separated numbers — the sought arrangement of the sheep. The $ i $ -th value in the line must represent the number of the sheep that took the $ i $ -th place from left in the optimal arrangement line.

If there are multiple optimal arrangements, print any of them.

## 样例 #1

### 输入

```
3
1 3
5 7
2 4

```

### 输出

```
1 3 2
```

## 样例 #2

### 输入

```
5
1 5
2 4
3 6
1 7
2 6

```

### 输出

```
2 1 3 5 4
```

## 样例 #3

### 输入

```
4
1 3
4 6
5 7
2 3

```

### 输出

```
1 4 2 3
```

