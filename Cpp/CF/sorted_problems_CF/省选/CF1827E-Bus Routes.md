---
title: "Bus Routes"
layout: "post"
diff: 省选/NOI-
pid: CF1827E
tag: []
---

# Bus Routes

## 题目描述

There is a country consisting of $ n $ cities and $ n - 1 $ bidirectional roads connecting them such that we can travel between any two cities using these roads. In other words, these cities and roads form a tree.

There are $ m $ bus routes connecting the cities together. A bus route between city $ x $ and city $ y $ allows you to travel between any two cities in the simple path between $ x $ and $ y $ with this route.

Determine if for every pair of cities $ u $ and $ v $ , you can travel from $ u $ to $ v $ using at most two bus routes.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \le n \le 5 \cdot 10^5, 0 \le m \le 5 \cdot 10^5 $ ) — the number of cities and the number of bus routes.

Then $ n - 1 $ lines follow. Each line contains two integers $ u $ and $ v $ denoting a road connecting city $ u $ and city $ v $ ( $ 1 \le u, v \le n, u \neq v $ ). It is guaranteed that these cities and roads form a tree.

Then $ m $ lines follow. Each line contains two integers $ x $ and $ y $ denoting a bus route between city $ x $ and city $ y $ ( $ 1 \le x, y \le n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ and the sum of $ m $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if you can travel between any pair of cities using at most two bus routes.

Otherwise, output "NO". In the next line, output two cities $ x $ and $ y $ ( $ 1 \le x, y \le n $ ) such that it is impossible to reach city $ y $ from city $ x $ using at most two bus routes.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

Here are the graphs of test case $ 1 $ , $ 2 $ , and $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827E/636b5045dbd1d95c74fcfe21de52ce3103ecff1f.png) Sample 1  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827E/5e6bc53eeaf1c05a72aa8adb625cb08699ecaf80.png) Sample 2  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827E/a888d70cad2c6923d39db1e4ae24fc5352ba8193.png) Sample 4

## 样例 #1

### 输入

```
4
5 2
1 2
2 3
3 4
2 5
1 4
5 2
5 1
1 2
2 3
3 4
2 5
1 5
2 0
1 2
6 3
1 2
2 3
3 4
4 5
5 6
1 3
2 5
4 6
```

### 输出

```
YES
NO
1 3
NO
1 2
NO
1 6
```

