---
title: "Team Rocket Rises Again"
layout: "post"
diff: 省选/NOI-
pid: CF757F
tag: ['最短路']
---

# Team Rocket Rises Again

## 题目描述

It's the turn of the year, so Bash wants to send presents to his friends. There are $ n $ cities in the Himalayan region and they are connected by $ m $ bidirectional roads. Bash is living in city $ s $ . Bash has exactly one friend in each of the other cities. Since Bash wants to surprise his friends, he decides to send a Pikachu to each of them. Since there may be some cities which are not reachable from Bash's city, he only sends a Pikachu to those friends who live in a city reachable from his own city. He also wants to send it to them as soon as possible.

He finds out the minimum time for each of his Pikachus to reach its destination city. Since he is a perfectionist, he informs all his friends with the time their gift will reach them. A Pikachu travels at a speed of $ 1 $ meters per second. His friends were excited to hear this and would be unhappy if their presents got delayed. Unfortunately Team Rocket is on the loose and they came to know of Bash's plan. They want to maximize the number of friends who are unhappy with Bash.

They do this by destroying exactly one of the other $ n-1 $ cities. This implies that the friend residing in that city dies, so he is unhappy as well.

Note that if a city is destroyed, all the roads directly connected to the city are also destroyed and the Pikachu may be forced to take a longer alternate route.

Please also note that only friends that are waiting for a gift count as unhappy, even if they die.

Since Bash is already a legend, can you help Team Rocket this time and find out the maximum number of Bash's friends who can be made unhappy by destroying exactly one city.

## 输入格式

The first line contains three space separated integers $ n $ , $ m $ and $ s $ ( $ 2<=n<=2·10^{5} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757F/a96c653ce18839af52c685b3a4dac28dbdbbdc23.png), $ 1<=s<=n $ ) — the number of cities and the number of roads in the Himalayan region and the city Bash lives in.

Each of the next $ m $ lines contain three space-separated integers $ u $ , $ v $ and $ w $ ( $ 1<=u,v<=n $ , $ u≠v $ , $ 1<=w<=10^{9} $ ) denoting that there exists a road between city $ u $ and city $ v $ of length $ w $ meters.

It is guaranteed that no road connects a city to itself and there are no two roads that connect the same pair of cities.

## 输出格式

Print a single integer, the answer to the problem.

## 说明/提示

In the first sample, on destroying the city $ 2 $ , the length of shortest distance between pairs of cities $ (3,2) $ and $ (3,4) $ will change. Hence the answer is $ 2 $ .

## 样例 #1

### 输入

```
4 4 3
1 2 1
2 3 1
2 4 1
3 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7 11 2
1 2 5
1 3 5
2 4 2
2 5 2
3 6 3
3 7 3
4 6 2
3 4 2
6 7 3
4 5 7
4 7 7

```

### 输出

```
4

```

