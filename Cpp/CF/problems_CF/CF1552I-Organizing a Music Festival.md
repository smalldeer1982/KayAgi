---
title: "Organizing a Music Festival"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1552I
tag: []
---

# Organizing a Music Festival

## 题目描述

You are the organizer of the famous "Zurich Music Festival". There will be $ n $ singers who will perform at the festival, identified by the integers $ 1 $ , $ 2 $ , $ \dots $ , $ n $ . You must choose in which order they are going to perform on stage.

You have $ m $ friends and each of them has a set of favourite singers. More precisely, for each $ 1\le i\le m $ , the $ i $ -th friend likes singers $ s_{i,1}, \, s_{i, 2}, \, \dots, \,s_{i, q_i} $ .

A friend of yours is happy if the singers he likes perform consecutively (in an arbitrary order). An ordering of the singers is valid if it makes all your friends happy.

Compute the number of valid orderings modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1\le n,\,m\le 100 $ ) — the number of singers and the number of friends correspondingly.

The $ i $ -th of the next $ m $ lines contains the integer $ q_i $ ( $ 1\le q_i\le n $ ) — the number of favorite singers of the $ i $ -th friend – followed by the $ q_i $ integers $ s_{i,1}, \, s_{i, 2}, \, \dots, \,s_{i, q_i} $ ( $ 1\le s_{i,1}<s_{i,2}<\cdots<s_{i,q_i}\le n $ ) — the indexes of his favorite singers.

## 输出格式

Print the number of valid orderings of the singers modulo $ 998\,244\,353 $ .

## 说明/提示

Explanation of the first sample: There are $ 3 $ singers and only $ 1 $ friend. The friend likes the two singers $ 1 $ and $ 3 $ . Thus, the $ 4 $ valid orderings are:

- 1 3 2
- 2 1 3
- 2 3 1
- 3 1 2

Explanation of the second sample: There are $ 5 $ singers and $ 5 $ friends. One can show that no ordering is valid.

Explanation of the third sample: There are $ 100 $ singers and only $ 1 $ friend. The friend likes only singer $ 50 $ , hence all the $ 100! $ possible orderings are valid.

Explanation of the fourth sample: There are $ 5 $ singers and only $ 1 $ friend. The friend likes all the singers, hence all the $ 5!=120 $ possible orderings are valid.

## 样例 #1

### 输入

```
3 1
2 1 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 5
2 1 2
2 2 3
2 3 4
2 4 5
2 1 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
100 1
1 50
```

### 输出

```
35305197
```

## 样例 #4

### 输入

```
5 1
5 1 2 3 4 5
```

### 输出

```
120
```

## 样例 #5

### 输入

```
2 5
1 2
1 2
1 2
1 1
1 1
```

### 输出

```
2
```

## 样例 #6

### 输入

```
11 4
5 4 5 7 9 11
2 2 10
2 9 11
7 1 2 3 5 8 10 11
```

### 输出

```
384
```

