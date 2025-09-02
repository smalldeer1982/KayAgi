---
title: "Case of Computer Network"
layout: "post"
diff: 省选/NOI-
pid: CF555E
tag: []
---

# Case of Computer Network

## 题目描述

Andrewid the Android is a galaxy-known detective. Now he is preparing a defense against a possible attack by hackers on a major computer network.

In this network are $ n $ vertices, some pairs of vertices are connected by $ m $ undirected channels. It is planned to transfer $ q $ important messages via this network, the $ i $ -th of which must be sent from vertex $ s_{i} $ to vertex $ d_{i} $ via one or more channels, perhaps through some intermediate vertices.

To protect against attacks a special algorithm was developed. Unfortunately it can be applied only to the network containing directed channels. Therefore, as new channels can't be created, it was decided for each of the existing undirected channels to enable them to transmit data only in one of the two directions.

Your task is to determine whether it is possible so to choose the direction for each channel so that each of the $ q $ messages could be successfully transmitted.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n,m,q<=2·10^{5} $ ) — the number of nodes, channels and important messages.

Next $ m $ lines contain two integers each, $ v_{i} $ and $ u_{i} $ ( $ 1<=v_{i},u_{i}<=n $ , $ v_{i}≠u_{i} $ ), that means that between nodes $ v_{i} $ and $ u_{i} $ is a channel. Between a pair of nodes can exist more than one channel.

Next $ q $ lines contain two integers $ s_{i} $ and $ d_{i} $ ( $ 1<=s_{i},d_{i}<=n $ , $ s_{i}≠d_{i} $ ) — the numbers of the nodes of the source and destination of the corresponding message.

It is not guaranteed that in it initially possible to transmit all the messages.

## 输出格式

If a solution exists, print on a single line "Yes" (without the quotes). Otherwise, print "No" (without the quotes).

## 说明/提示

In the first sample test you can assign directions, for example, as follows: $ 1→2 $ , $ 1→3 $ , $ 3→2 $ , $ 4→3 $ . Then the path for for the first message will be $ 1→3 $ , and for the second one — $ 4→3→2 $ .

In the third sample test you can assign directions, for example, as follows: $ 1→2 $ , $ 2→1 $ , $ 2→3 $ . Then the path for the first message will be $ 1→2→3 $ , and for the second one — $ 2→1 $ .

## 样例 #1

### 输入

```
4 4 2
1 2
1 3
2 3
3 4
1 3
4 2

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
3 2 2
1 2
3 2
1 3
2 1

```

### 输出

```
No

```

## 样例 #3

### 输入

```
3 3 2
1 2
1 2
3 2
1 3
2 1

```

### 输出

```
Yes

```

