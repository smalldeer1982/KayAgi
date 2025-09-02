---
title: "Dispute"
layout: "post"
diff: 提高+/省选-
pid: CF242D
tag: []
---

# Dispute

## 题目描述

Valera has $ n $ counters numbered from $ 1 $ to $ n $ . Some of them are connected by wires, and each of the counters has a special button.

Initially, all the counters contain number $ 0 $ . When you press a button on a certain counter, the value it has increases by one. Also, the values recorded in all the counters, directly connected to it by a wire, increase by one.

Valera and Ignat started having a dispute, the dispute is as follows. Ignat thought of a sequence of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Valera should choose some set of distinct counters and press buttons on each of them exactly once (on other counters the buttons won't be pressed). If after that there is a counter with the number $ i $ , which has value $ a_{i} $ , then Valera loses the dispute, otherwise he wins the dispute.

Help Valera to determine on which counters he needs to press a button to win the dispute.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ $ (1<=n,m<=10^{5}) $ , that denote the number of counters Valera has and the number of pairs of counters connected by wires.

Each of the following $ m $ lines contains two space-separated integers $ u_{i} $ and $ v_{i} $ $ (1<=u_{i},v_{i}<=n,u_{i}≠v_{i}) $ , that mean that counters with numbers $ u_{i} $ and $ v_{i} $ are connected by a wire. It is guaranteed that each pair of connected counters occurs exactly once in the input.

The last line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (0<=a_{i}<=10^{5}) $ , where $ a_{i} $ is the value that Ignat choose for the $ i $ -th counter.

## 输出格式

If Valera can't win the dispute print in the first line -1.

Otherwise, print in the first line integer $ k $ $ (0<=k<=n) $ . In the second line print $ k $ distinct space-separated integers — the numbers of the counters, where Valera should push buttons to win the dispute, in arbitrary order.

If there exists multiple answers, you are allowed to print any of them.

## 样例 #1

### 输入

```
5 5
2 3
4 1
1 5
5 3
2 1
1 1 2 0 2

```

### 输出

```
2
1 2

```

## 样例 #2

### 输入

```
4 2
1 2
3 4
0 0 0 0

```

### 输出

```
3
1 3 4

```

