---
title: "Pursuit For Artifacts"
layout: "post"
diff: 提高+/省选-
pid: CF652E
tag: []
---

# Pursuit For Artifacts

## 题目描述

Johnny is playing a well-known computer game. The game are in some country, where the player can freely travel, pass quests and gain an experience.

In that country there are $ n $ islands and $ m $ bridges between them, so you can travel from any island to any other. In the middle of some bridges are lying ancient powerful artifacts. Johnny is not interested in artifacts, but he can get some money by selling some artifact.

At the start Johnny is in the island $ a $ and the artifact-dealer is in the island $ b $ (possibly they are on the same island). Johnny wants to find some artifact, come to the dealer and sell it. The only difficulty is that bridges are too old and destroying right after passing over them. Johnnie's character can't swim, fly and teleport, so the problem became too difficult.

Note that Johnny can't pass the half of the bridge, collect the artifact and return to the same island.

Determine if Johnny can find some artifact and sell it.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=3·10^{5} $ , $ 0<=m<=3·10^{5} $ ) — the number of islands and bridges in the game.

Each of the next $ m $ lines contains the description of the bridge — three integers $ x_{i} $ , $ y_{i} $ , $ z_{i} $ ( $ 1<=x_{i},y_{i}<=n $ , $ x_{i}≠y_{i} $ , $ 0<=z_{i}<=1 $ ), where $ x_{i} $ and $ y_{i} $ are the islands connected by the $ i $ -th bridge, $ z_{i} $ equals to one if that bridge contains an artifact and to zero otherwise. There are no more than one bridge between any pair of islands. It is guaranteed that it's possible to travel between any pair of islands.

The last line contains two integers $ a $ and $ b $ ( $ 1<=a,b<=n $ ) — the islands where are Johnny and the artifact-dealer respectively.

## 输出格式

If Johnny can find some artifact and sell it print the only word "YES" (without quotes). Otherwise print the word "NO" (without quotes).

## 样例 #1

### 输入

```
6 7
1 2 0
2 3 0
3 1 0
3 4 1
4 5 0
5 6 0
6 4 0
1 6

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
5 4
1 2 0
2 3 0
3 4 0
2 5 1
1 4

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5 6
1 2 0
2 3 0
3 1 0
3 4 0
4 5 1
5 3 0
1 2

```

### 输出

```
YES

```

