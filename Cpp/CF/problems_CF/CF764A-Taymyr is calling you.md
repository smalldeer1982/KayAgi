---
title: "Taymyr is calling you"
layout: "post"
diff: 入门
pid: CF764A
tag: []
---

# Taymyr is calling you

## 题目描述

Comrade Dujikov is busy choosing artists for Timofey's birthday and is recieving calls from Taymyr from Ilia-alpinist.

Ilia-alpinist calls every $ n $ minutes, i.e. in minutes $ n $ , $ 2n $ , $ 3n $ and so on. Artists come to the comrade every $ m $ minutes, i.e. in minutes $ m $ , $ 2m $ , $ 3m $ and so on. The day is $ z $ minutes long, i.e. the day consists of minutes $ 1,2,...,z $ . How many artists should be killed so that there are no artists in the room when Ilia calls? Consider that a call and a talk with an artist take exactly one minute.

## 输入格式

The only string contains three integers — $ n $ , $ m $ and $ z $ ( $ 1<=n,m,z<=10^{4} $ ).

## 输出格式

Print single integer — the minimum number of artists that should be killed so that there are no artists in the room when Ilia calls.

## 说明/提示

Taymyr is a place in the north of Russia.

In the first test the artists come each minute, as well as the calls, so we need to kill all of them.

In the second test we need to kill artists which come on the second and the fourth minutes.

In the third test — only the artist which comes on the sixth minute.

## 样例 #1

### 输入

```
1 1 10

```

### 输出

```
10

```

## 样例 #2

### 输入

```
1 2 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
2 3 9

```

### 输出

```
1

```

