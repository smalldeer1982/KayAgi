---
title: "Distributing Parts"
layout: "post"
diff: 提高+/省选-
pid: CF496E
tag: []
---

# Distributing Parts

## 题目描述

You are an assistant director in a new musical play. The play consists of $ n $ musical parts, each part must be performed by exactly one actor. After the casting the director chose $ m $ actors who can take part in the play. Your task is to assign the parts to actors. However, there are several limitations.

First, each actor has a certain voice range and there are some parts that he cannot sing. Formally, there are two integers for each actor, $ c_{i} $ and $ d_{i} $ ( $ c_{i}<=d_{i} $ ) — the pitch of the lowest and the highest note that the actor can sing. There also are two integers for each part — $ a_{j} $ and $ b_{j} $ ( $ a_{j}<=b_{j} $ ) — the pitch of the lowest and the highest notes that are present in the part. The $ i $ -th actor can perform the $ j $ -th part if and only if $ c_{i}<=a_{j}<=b_{j}<=d_{i} $ , i.e. each note of the part is in the actor's voice range.

According to the contract, the $ i $ -th actor can perform at most $ k_{i} $ parts. Besides, you are allowed not to give any part to some actors (then they take part in crowd scenes).

The rehearsal starts in two hours and you need to do the assignment quickly!

## 输入格式

The first line contains a single integer $n$ — the number of parts in the play ( $1\le n \le 10^5$ )  

Next $n$  lines contain two space-separated integers each, $a_j$ and $b_j$ — the range of notes for the $j$-th part $( 1\le a_j \le b_j \le 10^9 )$  
 
The next line contains a single integer $m$—the number of actors $( 1\le m \le 10^5 )$  

Next $m$ lines contain three space-separated integers each $c_i,d_i$ and $k_i$，— the range of the $i$-th actor and the number of parts that he can perform ( $1\le c_i \le d_i \le 10^9$,$1\le k_i \le 10^9$ )

## 输出格式

If there is an assignment that meets all the criteria aboce, print a single word "YES" (without the quotes) in the first line.

In the next line print $ n $ space-separated integers. The $ i $ -th integer should be the number of the actor who should perform the $ i $ -th part. If there are multiple correct assignments, print any of them.

If there is no correct assignment, print a single word "NO" (without the quotes).

## 样例 #1

### 输入

```
3
1 3
2 4
3 5
2
1 4 2
2 5 1

```

### 输出

```
YES
1 1 2

```

## 样例 #2

### 输入

```
3
1 3
2 4
3 5
2
1 3 2
2 5 1

```

### 输出

```
NO

```

