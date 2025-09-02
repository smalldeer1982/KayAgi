---
title: "Bear and Friendship Condition"
layout: "post"
diff: 普及/提高-
pid: CF771A
tag: []
---

# Bear and Friendship Condition

## 题目描述

Bear Limak examines a social network. Its main functionality is that two members can become friends (then they can talk with each other and share funny pictures).

There are $ n $ members, numbered $ 1 $ through $ n $ . $ m $ pairs of members are friends. Of course, a member can't be a friend with themselves.

Let A-B denote that members A and B are friends. Limak thinks that a network is reasonable if and only if the following condition is satisfied: For every three distinct members (X, Y, Z), if X-Y and Y-Z then also X-Z.

For example: if Alan and Bob are friends, and Bob and Ciri are friends, then Alan and Ciri should be friends as well.

Can you help Limak and check if the network is reasonable? Print "YES" or "NO" accordingly, without the quotes.

## 输入格式

The first line of the input contain two integers $ n $ and $ m $ ( $ 3<=n<=150000 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF771A/8f065d6ccf5ce6e7ee658f598aa517f9541bc089.png)) — the number of members and the number of pairs of members that are friends.

The $ i $ -th of the next $ m $ lines contains two distinct integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n,a_{i}≠b_{i} $ ). Members $ a_{i} $ and $ b_{i} $ are friends with each other. No pair of members will appear more than once in the input.

## 输出格式

If the given network is reasonable, print "YES" in a single line (without the quotes). Otherwise, print "NO" in a single line (without the quotes).

## 说明/提示

The drawings below show the situation in the first sample (on the left) and in the second sample (on the right). Each edge represents two members that are friends. The answer is "NO" in the second sample because members $ (2,3) $ are friends and members $ (3,4) $ are friends, while members $ (2,4) $ are not.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF771A/452e04bb457330535035b94604ffb28f5fa05d56.png)

## 样例 #1

### 输入

```
4 3
1 3
3 4
1 4

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4 4
3 1
2 3
3 4
1 2

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
10 4
4 3
5 10
8 9
1 2

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
3 2
1 2
2 3

```

### 输出

```
NO

```

