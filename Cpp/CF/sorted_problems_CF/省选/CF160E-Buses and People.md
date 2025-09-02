---
title: "Buses and People"
layout: "post"
diff: 省选/NOI-
pid: CF160E
tag: []
---

# Buses and People

## 题目描述

The main Bertown street is represented by a straight line. There are $ 10^{9} $ bus stops located on the line. The stops are numbered with integers from $ 1 $ to $ 10^{9} $ in the order in which they follow on the road. The city has $ n $ buses. Every day the $ i $ -th bus drives from stop number $ s_{i} $ to stop number $ f_{i} $ ( $ s_{i}< f_{i} $ ), it stops on all intermediate stops and returns only at night. The bus starts driving at time $ t_{i} $ and drives so fast that it finishes driving also at time $ t_{i} $ . The time $ t_{i} $ is different for all buses. The buses have infinite capacity.

Bertown has $ m $ citizens. Today the $ i $ -th person should get from stop number $ l_{i} $ to stop number $ r_{i} $ ( $ l_{i}< r_{i} $ ); the $ i $ -th citizen comes to his initial stop ( $ l_{i} $ ) at time $ b_{i} $ . Each person, on the one hand, wants to get to the destination point as quickly as possible, and on the other hand, definitely does not want to change the buses as he rides. More formally: the $ i $ -th person chooses bus $ j $ , with minimum time $ t_{j} $ , such that $ s_{j} \leq l_{i} $ , $ r_{i}\leq f_{j} $ and $ b_{i} \leq t_{j} $ .

Your task is to determine for each citizen whether he can ride to the destination point today and if he can, find the number of the bus on which the citizen will ride.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n,m \leq 10^{5} $ ) — the number of buses and the number of people.

Then $ n $ lines follow, each of them contains three integers: $ s_{i} $ , $ f_{i} $ , $ t_{i} $ ( $ 1 \leq s_{i},f_{i},t_{i} \leq 10^{9},s_{i}<f_{i} $ ) — the description of the buses. It is guaranteed that all $ t_{i} $ -s are different.

Then $ m $ lines follow, each of them contains three integers: $ l_{i} $ , $ r_{i} $ , $ b_{i} $ ( $ 1 \leq l_{i},r_{i},b_{i} \leq 10^{9},l_{i}<r_{i} $ ) — the Bertown citizens' description. Some $ b_{i} $ -s could coincide.

## 输出格式

In the first line print $ m $ space-separated integers: the $ i $ -th number should be equal either to -1, if the person number $ i $ can't get to the destination point, or to the number of the bus that will ride the person number $ i $ . The buses are numbered with integers from $ 1 $ to $ n $ in the input order.

## 样例 #1

### 输入

```
4 3
1 10 10
5 6 2
6 7 3
5 7 4
5 7 1
1 2 1
1 10 11

```

### 输出

```
4 1 -1

```

## 样例 #2

### 输入

```
1 1
1 1000000000 1000000000
1 1000000000 1000000000

```

### 输出

```
1

```

