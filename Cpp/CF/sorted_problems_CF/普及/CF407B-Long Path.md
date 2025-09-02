---
title: "Long Path"
layout: "post"
diff: 普及/提高-
pid: CF407B
tag: []
---

# Long Path

## 题目描述

One day, little Vasya found himself in a maze consisting of $ (n+1) $ rooms, numbered from $ 1 $ to $ (n+1) $ . Initially, Vasya is at the first room and to get out of the maze, he needs to get to the $ (n+1) $ -th one.

The maze is organized as follows. Each room of the maze has two one-way portals. Let's consider room number $ i $ $ (1<=i<=n) $ , someone can use the first portal to move from it to room number $ (i+1) $ , also someone can use the second portal to move from it to room number $ p_{i} $ , where $ 1<=p_{i}<=i $ .

In order not to get lost, Vasya decided to act as follows.

- Each time Vasya enters some room, he paints a cross on its ceiling. Initially, Vasya paints a cross at the ceiling of room $ 1 $ .
- Let's assume that Vasya is in room $ i $ and has already painted a cross on its ceiling. Then, if the ceiling now contains an odd number of crosses, Vasya uses the second portal (it leads to room $ p_{i} $ ), otherwise Vasya uses the first portal.

Help Vasya determine the number of times he needs to use portals to get to room $ (n+1) $ in the end.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{3} $ ) — the number of rooms. The second line contains $ n $ integers $ p_{i} $ ( $ 1<=p_{i}<=i $ ). Each $ p_{i} $ denotes the number of the room, that someone can reach, if he will use the second portal in the $ i $ -th room.

## 输出格式

Print a single number — the number of portal moves the boy needs to go out of the maze. As the number can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
2
1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4
1 1 2 3

```

### 输出

```
20

```

## 样例 #3

### 输入

```
5
1 1 1 1 1

```

### 输出

```
62

```

