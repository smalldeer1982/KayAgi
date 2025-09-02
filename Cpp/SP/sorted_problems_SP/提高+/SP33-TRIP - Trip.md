---
title: "TRIP - Trip"
layout: "post"
diff: 提高+/省选-
pid: SP33
tag: ['字符串', '递归', '枚举']
---

# TRIP - Trip

## 题目描述

Alice and Bob want to go on holiday. Each of them has drawn up a list of cities to be visited in turn. A list may contain a city more than once. As they want to travel together, they have to agree upon a common route. No one wants to change the order of the cities on his list or add other cities. Therefore they have no choice but to remove some cities from the list. Of course the common route is to involve as much sight-seeing in cities as possible. There are exactly 26 cities in the region. Therefore they are encoded on the lists as lower case letters from 'a' to 'z'.

## 输入格式

The first line of input contains a number T <= 10 that indicates the number of test cases to follow. Each test case consists of two lines; the first line is the list of Alice, the second line is the list of Bob. Each list consists of 1 to 80 lower case letters.

## 输出格式

The output for each test case should contain all different trips exactly once that meet the conditions described above. There is at least one such trip, but never more than 1000 different ones. You should order the trips in lexicographic order. Print one blank line between the output of different test cases.

## 样例 #1

### 输入

```
1
abcabcaa
acbacba
```

### 输出

```
ababa
abaca
abcba
acaba
acaca
acbaa
acbca
```

