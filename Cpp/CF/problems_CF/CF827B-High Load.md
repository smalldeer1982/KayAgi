---
title: "High Load"
layout: "post"
diff: 普及+/提高
pid: CF827B
tag: []
---

# High Load

## 题目描述

Arkady needs your help again! This time he decided to build his own high-speed Internet exchange point. It should consist of $ n $ nodes connected with minimum possible number of wires into one network (a wire directly connects two nodes). Exactly $ k $ of the nodes should be exit-nodes, that means that each of them should be connected to exactly one other node of the network, while all other nodes should be connected to at least two nodes in order to increase the system stability.

Arkady wants to make the system as fast as possible, so he wants to minimize the maximum distance between two exit-nodes. The distance between two nodes is the number of wires a package needs to go through between those two nodes.

Help Arkady to find such a way to build the network that the distance between the two most distant exit-nodes is as small as possible.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 3<=n<=2·10^{5} $ , $ 2<=k<=n-1 $ ) — the total number of nodes and the number of exit-nodes.

Note that it is always possible to build at least one network with $ n $ nodes and $ k $ exit-nodes within the given constraints.

## 输出格式

In the first line print the minimum possible distance between the two most distant exit-nodes. In each of the next $ n-1 $ lines print two integers: the ids of the nodes connected by a wire. The description of each wire should be printed exactly once. You can print wires and wires' ends in arbitrary order. The nodes should be numbered from $ 1 $ to $ n $ . Exit-nodes can have any ids.

If there are multiple answers, print any of them.

## 说明/提示

In the first example the only network is shown on the left picture.

In the second example one of optimal networks is shown on the right picture.

Exit-nodes are highlighted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF827B/0a307dfc178cc97ead8d05d1f345ab6df68055f9.png)

## 样例 #1

### 输入

```
3 2

```

### 输出

```
2
1 2
2 3

```

## 样例 #2

### 输入

```
5 3

```

### 输出

```
3
1 2
2 3
3 4
3 5

```

