---
title: "Dima and Horses"
layout: "post"
diff: 提高+/省选-
pid: CF272E
tag: []
---

# Dima and Horses

## 题目描述

Dima came to the horse land. There are $ n $ horses living in the land. Each horse in the horse land has several enemies (enmity is a symmetric relationship). The horse land isn't very hostile, so the number of enemies of each horse is at most 3.

Right now the horse land is going through an election campaign. So the horses trusted Dima to split them into two parts. At that the horses want the following condition to hold: a horse shouldn't have more than one enemy in its party.

Help Dima split the horses into parties. Note that one of the parties can turn out to be empty.

## 输入格式

The first line contains two integers $ n,m $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF272E/dac9c4b7533b005d45a40124a615b184d0f4824d.png) — the number of horses in the horse land and the number of enemy pairs.

Next $ m $ lines define the enemy pairs. The $ i $ -th line contains integers $ a_{i},b_{i} $ $ (1<=a_{i},b_{i}<=n; a_{i}≠b_{i}) $ , which mean that horse $ a_{i} $ is the enemy of horse $ b_{i} $ .

Consider the horses indexed in some way from 1 to $ n $ . It is guaranteed that each horse has at most three enemies. No pair of enemies occurs more than once in the input.

## 输出格式

Print a line, consisting of $ n $ characters: the $ i $ -th character of the line must equal "0", if the horse number $ i $ needs to go to the first party, otherwise this character should equal "1".

If there isn't a way to divide the horses as required, print -1.

## 样例 #1

### 输入

```
3 3
1 2
3 2
3 1

```

### 输出

```
100

```

## 样例 #2

### 输入

```
2 1
2 1

```

### 输出

```
00

```

## 样例 #3

### 输入

```
10 6
1 2
1 3
1 4
2 3
2 4
3 4

```

### 输出

```
0110000000

```

