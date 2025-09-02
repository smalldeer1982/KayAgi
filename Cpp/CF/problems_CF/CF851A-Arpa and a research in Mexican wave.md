---
title: "Arpa and a research in Mexican wave"
layout: "post"
diff: 入门
pid: CF851A
tag: []
---

# Arpa and a research in Mexican wave

## 题目描述

Arpa is researching the Mexican wave.

There are $ n $ spectators in the stadium, labeled from $ 1 $ to $ n $ . They start the Mexican wave at time $ 0 $ .

- At time $ 1 $ , the first spectator stands.
- At time $ 2 $ , the second spectator stands.
- $ ... $
- At time $ k $ , the $ k $ -th spectator stands.
- At time $ k+1 $ , the $ (k+1) $ -th spectator stands and the first spectator sits.
- At time $ k+2 $ , the $ (k+2) $ -th spectator stands and the second spectator sits.
- $ ... $
- At time $ n $ , the $ n $ -th spectator stands and the $ (n-k) $ -th spectator sits.
- At time $ n+1 $ , the $ (n+1-k) $ -th spectator sits.
- $ ... $
- At time $ n+k $ , the $ n $ -th spectator sits.

Arpa wants to know how many spectators are standing at time $ t $ .

## 输入格式

The first line contains three integers $ n $ , $ k $ , $ t $ ( $ 1<=n<=10^{9} $ , $ 1<=k<=n $ , $ 1<=t<n+k $ ).

## 输出格式

Print single integer: how many spectators are standing at time $ t $ .

## 说明/提示

In the following a sitting spectator is represented as -, a standing spectator is represented as ^.

- At $ t=0  $ ---------- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 0.
- At $ t=1  $ ^--------- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 1.
- At $ t=2  $ ^^-------- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 2.
- At $ t=3  $ ^^^------- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 3.
- At $ t=4  $ ^^^^------ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 4.
- At $ t=5  $ ^^^^^----- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 5.
- At $ t=6  $ -^^^^^---- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 5.
- At $ t=7  $ --^^^^^--- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 5.
- At $ t=8  $ ---^^^^^-- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 5.
- At $ t=9  $ ----^^^^^- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 5.
- At $ t=10 $ -----^^^^^ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 5.
- At $ t=11 $ ------^^^^ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 4.
- At $ t=12 $ -------^^^ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 3.
- At $ t=13 $ --------^^ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 2.
- At $ t=14 $ ---------^ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 1.
- At $ t=15 $ ---------- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF851A/36de14eb23d8ee46ce065565960590d715b12072.png) number of standing spectators = 0.

## 样例 #1

### 输入

```
10 5 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
10 5 7

```

### 输出

```
5

```

## 样例 #3

### 输入

```
10 5 12

```

### 输出

```
3

```

