---
title: "Ring road"
layout: "post"
diff: 普及/提高-
pid: CF24A
tag: []
---

# Ring road

## 题目描述

Nowadays the one-way traffic is introduced all over the world in order to improve driving safety and reduce traffic jams. The government of Berland decided to keep up with new trends. Formerly all $ n $ cities of Berland were connected by $ n $ two-way roads in the ring, i. e. each city was connected directly to exactly two other cities, and from each city it was possible to get to any other city. Government of Berland introduced one-way traffic on all $ n $ roads, but it soon became clear that it's impossible to get from some of the cities to some others. Now for each road is known in which direction the traffic is directed at it, and the cost of redirecting the traffic. What is the smallest amount of money the government should spend on the redirecting of roads so that from every city you can get to any other?

## 输入格式

The first line contains integer $ n $ ( $ 3<=n<=100 $ ) — amount of cities (and roads) in Berland. Next $ n $ lines contain description of roads. Each road is described by three integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n,a_{i}≠b_{i},1<=c_{i}<=100 $ ) — road is directed from city $ a_{i} $ to city $ b_{i} $ , redirecting the traffic costs $ c_{i} $ .

## 输出格式

Output single integer — the smallest amount of money the government should spend on the redirecting of roads so that from every city you can get to any other.

## 样例 #1

### 输入

```
3
1 3 1
1 2 1
3 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
1 3 1
1 2 5
3 2 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
6
1 5 4
5 3 8
2 4 15
1 6 16
2 3 23
4 6 42

```

### 输出

```
39

```

## 样例 #4

### 输入

```
4
1 2 9
2 3 8
3 4 7
4 1 5

```

### 输出

```
0

```

