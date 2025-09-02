---
title: "Adventurers"
layout: "post"
diff: 提高+/省选-
pid: CF2046C
tag: ['线段树', '二分', '树状数组', '扫描线']
---

# Adventurers

## 题目描述

Once, four Roman merchants met in a Roman mansion to discuss their trading plans. They faced the following problem: they traded the same type of goods, and if they traded in the same city, they would inevitably incur losses. They decided to divide up the cities between them where they would trade.

The map of Rome can be represented in this problem as a plane with certain points marked — the cities of the Roman Empire.

The merchants decided to choose a certain dividing point $ (x_0, y_0) $ . Then, in a city with coordinates $ (x_i, y_i) $ ,

- the first merchant sells goods if $ x_0 \le x_i $ and $ y_0 \le y_i $ ;
- the second merchant sells goods if $ x_0 > x_i $ and $ y_0 \le y_i $ ;
- the third merchant sells goods if $ x_0 \le x_i $ and $ y_0 > y_i $ ;
- the fourth merchant sells goods if $ x_0 > x_i $ and $ y_0 > y_i $ .

The merchants want to choose $ (x_0, y_0) $ in such a way as to maximize the smallest number of cities that any of them gets (i. e., as fair as possible). Please find such a point for them.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 4 \le n \le 10^5 $ ) — the number of cities on the map.

Each of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ -10^9 \le x_i, y_i \le 10^9 $ ) — the coordinates of the cities.

Note that some points may coincide. This is because some cities may be so close that they cannot be distinguished on the map at the given scale.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, in the first line, print a single integer $ k $ ( $ 0 \le k \le \frac{n}{4} $ ) — the maximum possible number of cities that each merchant can get at a minimum.

In the second line, print two integers $ x_0 $ and $ y_0 $ ( $ |x_0|, |y_0| \le 10^9 $ ) — the coordinates of the dividing point. If there are multiple suitable points, print any of them.

## 样例 #1

### 输入

```
4
4
1 1
1 2
2 1
2 2
4
0 0
0 0
0 0
0 0
8
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
-2 1
-1 2
7
1 1
1 2
1 3
1 4
2 1
3 1
4 1
```

### 输出

```
1
2 2
0
0 0
2
1 0
0
0 0
```

