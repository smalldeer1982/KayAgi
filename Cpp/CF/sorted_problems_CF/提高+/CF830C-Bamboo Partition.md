---
title: "Bamboo Partition"
layout: "post"
diff: 提高+/省选-
pid: CF830C
tag: []
---

# Bamboo Partition

## 题目描述

Vladimir wants to modernize partitions in his office. To make the office more comfortable he decided to remove a partition and plant several bamboos in a row. He thinks it would be nice if there are $ n $ bamboos in a row, and the $ i $ -th from the left is $ a_{i} $ meters high.

Vladimir has just planted $ n $ bamboos in a row, each of which has height $ 0 $ meters right now, but they grow $ 1 $ meter each day. In order to make the partition nice Vladimir can cut each bamboo once at any height (no greater that the height of the bamboo), and then the bamboo will stop growing.

Vladimir wants to check the bamboos each $ d $ days (i.e. $ d $ days after he planted, then after $ 2d $ days and so on), and cut the bamboos that reached the required height. Vladimir wants the total length of bamboo parts he will cut off to be no greater than $ k $ meters.

What is the maximum value $ d $ he can choose so that he can achieve what he wants without cutting off more than $ k $ meters of bamboo?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 1<=k<=10^{11} $ ) — the number of bamboos and the maximum total length of cut parts, in meters.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the required heights of bamboos, in meters.

## 输出格式

Print a single integer — the maximum value of $ d $ such that Vladimir can reach his goal.

## 说明/提示

In the first example Vladimir can check bamboos each $ 3 $ days. Then he will cut the first and the second bamboos after $ 3 $ days, and the third bamboo after $ 6 $ days. The total length of cut parts is $ 2+0+1=3 $ meters.

## 样例 #1

### 输入

```
3 4
1 3 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 40
10 30 50

```

### 输出

```
32

```

