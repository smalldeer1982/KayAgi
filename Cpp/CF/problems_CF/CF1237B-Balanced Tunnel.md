---
title: "Balanced Tunnel"
layout: "post"
diff: 普及/提高-
pid: CF1237B
tag: []
---

# Balanced Tunnel

## 题目描述

Consider a tunnel on a one-way road. During a particular day, $ n $ cars numbered from $ 1 $ to $ n $ entered and exited the tunnel exactly once. All the cars passed through the tunnel at constant speeds.

A traffic enforcement camera is mounted at the tunnel entrance. Another traffic enforcement camera is mounted at the tunnel exit. Perfectly balanced.

Thanks to the cameras, the order in which the cars entered and exited the tunnel is known. No two cars entered or exited at the same time.

Traffic regulations prohibit overtaking inside the tunnel. If car $ i $ overtakes any other car $ j $ inside the tunnel, car $ i $ must be fined. However, each car can be fined at most once.

Formally, let's say that car $ i $ definitely overtook car $ j $ if car $ i $ entered the tunnel later than car $ j $ and exited the tunnel earlier than car $ j $ . Then, car $ i $ must be fined if and only if it definitely overtook at least one other car.

Find the number of cars that must be fined.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^5 $ ), denoting the number of cars.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ), denoting the ids of cars in order of entering the tunnel. All $ a_i $ are pairwise distinct.

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le n $ ), denoting the ids of cars in order of exiting the tunnel. All $ b_i $ are pairwise distinct.

## 输出格式

Output the number of cars to be fined.

## 说明/提示

The first example is depicted below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237B/7d2f6b4d3eea560d8fb835871b9aa0fd74a81766.png)

Car $ 2 $ definitely overtook car $ 5 $ , while car $ 4 $ definitely overtook cars $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ . Cars $ 2 $ and $ 4 $ must be fined.

In the second example car $ 5 $ was definitely overtaken by all other cars.

In the third example no car must be fined.

## 样例 #1

### 输入

```
5
3 5 2 1 4
4 3 2 5 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7
5 2 3 6 7 1 4
2 3 6 7 1 4 5

```

### 输出

```
6

```

## 样例 #3

### 输入

```
2
1 2
1 2

```

### 输出

```
0

```

