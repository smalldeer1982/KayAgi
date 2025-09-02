---
title: "The Door Problem"
layout: "post"
diff: 提高+/省选-
pid: CF776D
tag: []
---

# The Door Problem

## 题目描述

Moriarty has trapped $ n $ people in $ n $ distinct rooms in a hotel. Some rooms are locked, others are unlocked. But, there is a condition that the people in the hotel can only escape when all the doors are unlocked at the same time. There are $ m $ switches. Each switch control doors of some rooms, but each door is controlled by exactly two switches.

You are given the initial configuration of the doors. Toggling any switch, that is, turning it ON when it is OFF, or turning it OFF when it is ON, toggles the condition of the doors that this switch controls. Say, we toggled switch $ 1 $ , which was connected to room $ 1 $ , $ 2 $ and $ 3 $ which were respectively locked, unlocked and unlocked. Then, after toggling the switch, they become unlocked, locked and locked.

You need to tell Sherlock, if there exists a way to unlock all doors at the same time.

## 输入格式

First line of input contains two integers $ n $ and $ m $ ( $ 2<=n<=10^{5} $ , $ 2<=m<=10^{5} $ ) — the number of rooms and the number of switches.

Next line contains $ n $ space-separated integers $ r_{1},r_{2},...,r_{n} $ ( $ 0<=r_{i}<=1 $ ) which tell the status of room doors. The $ i $ -th room is locked if $ r_{i}=0 $ , otherwise it is unlocked.

The $ i $ -th of next $ m $ lines contains an integer $ x_{i} $ ( $ 0<=x_{i}<=n $ ) followed by $ x_{i} $ distinct integers separated by space, denoting the number of rooms controlled by the $ i $ -th switch followed by the room numbers that this switch controls. It is guaranteed that the room numbers are in the range from $ 1 $ to $ n $ . It is guaranteed that each door is controlled by exactly two switches.

## 输出格式

Output "YES" without quotes, if it is possible to open all doors at the same time, otherwise output "NO" without quotes.

## 说明/提示

In the second example input, the initial statuses of the doors are $ [1,0,1] $ ( $ 0 $ means locked, $ 1 $ — unlocked).

After toggling switch $ 3 $ , we get $ [0,0,0] $ that means all doors are locked.

Then, after toggling switch $ 1 $ , we get $ [1,1,1] $ that means all doors are unlocked.

It can be seen that for the first and for the third example inputs it is not possible to make all doors unlocked.

## 样例 #1

### 输入

```
3 3
1 0 1
2 1 3
2 1 2
2 2 3

```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3 3
1 0 1
3 1 2 3
1 2
2 1 3

```

### 输出

```
YES
```

## 样例 #3

### 输入

```
3 3
1 0 1
3 1 2 3
2 1 2
1 3

```

### 输出

```
NO
```

