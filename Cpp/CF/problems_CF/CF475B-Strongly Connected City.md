---
title: "Strongly Connected City"
layout: "post"
diff: 普及/提高-
pid: CF475B
tag: []
---

# Strongly Connected City

## 题目描述

Imagine a city with $ n $ horizontal streets crossing $ m $ vertical streets, forming an $ (n-1)×(m-1) $ grid. In order to increase the traffic flow, mayor of the city has decided to make each street one way. This means in each horizontal street, the traffic moves only from west to east or only from east to west. Also, traffic moves only from north to south or only from south to north in each vertical street. It is possible to enter a horizontal street from a vertical street, or vice versa, at their intersection.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475B/7015745b6e36cd9d1741bb00e67e81a4ab310705.png)The mayor has received some street direction patterns. Your task is to check whether it is possible to reach any junction from any other junction in the proposed street direction pattern.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ , ( $ 2<=n,m<=20 $ ), denoting the number of horizontal streets and the number of vertical streets.

The second line contains a string of length $ n $ , made of characters '<' and '>', denoting direction of each horizontal street. If the $ i $ -th character is equal to '<', the street is directed from east to west otherwise, the street is directed from west to east. Streets are listed in order from north to south.

The third line contains a string of length $ m $ , made of characters '^' and 'v', denoting direction of each vertical street. If the $ i $ -th character is equal to '^', the street is directed from south to north, otherwise the street is directed from north to south. Streets are listed in order from west to east.

## 输出格式

If the given pattern meets the mayor's criteria, print a single line containing "YES", otherwise print a single line containing "NO".

## 说明/提示

The figure above shows street directions in the second sample test case.

## 样例 #1

### 输入

```
3 3
><>
v^v
```

### 输出

```
NO

```

## 样例 #2

### 输入

```
4 6
<><>
v^v^v^
```

### 输出

```
YES

```

