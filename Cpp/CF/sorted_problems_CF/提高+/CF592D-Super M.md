---
title: "Super M"
layout: "post"
diff: 提高+/省选-
pid: CF592D
tag: []
---

# Super M

## 题目描述

Ari the monster is not an ordinary monster. She is the hidden identity of Super M, the Byteforces’ superhero. Byteforces is a country that consists of $ n $ cities, connected by $ n-1 $ bidirectional roads. Every road connects exactly two distinct cities, and the whole road system is designed in a way that one is able to go from any city to any other city using only the given roads. There are $ m $ cities being attacked by humans. So Ari... we meant Super M have to immediately go to each of the cities being attacked to scare those bad humans. Super M can pass from one city to another only using the given roads. Moreover, passing through one road takes her exactly one kron - the time unit used in Byteforces.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592D/56ad621cd6030e31dd330e89c0a8c84a229488d5.png)However, Super M is not on Byteforces now - she is attending a training camp located in a nearby country Codeforces. Fortunately, there is a special device in Codeforces that allows her to instantly teleport from Codeforces to any city of Byteforces. The way back is too long, so for the purpose of this problem teleportation is used exactly once.

You are to help Super M, by calculating the city in which she should teleport at the beginning in order to end her job in the minimum time (measured in krons). Also, provide her with this time so she can plan her way back to Codeforces.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=m<=n<=123456 $ ) - the number of cities in Byteforces, and the number of cities being attacked respectively.

Then follow $ n-1 $ lines, describing the road system. Each line contains two city numbers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) - the ends of the road $ i $ .

The last line contains $ m $ distinct integers - numbers of cities being attacked. These numbers are given in no particular order.

## 输出格式

First print the number of the city Super M should teleport to. If there are many possible optimal answers, print the one with the lowest city number.

Then print the minimum possible time needed to scare all humans in cities being attacked, measured in Krons.

Note that the correct answer is always unique.

## 说明/提示

In the first sample, there are two possibilities to finish the Super M's job in $ 3 $ krons. They are:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592D/1e0931f0ee430eed74c20346afbbffa12e1171b1.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592D/3d215bf3b44e51bded5f8987ac4bd264a82b6423.png).

However, you should choose the first one as it starts in the city with the lower number.

## 样例 #1

### 输入

```
7 2
1 2
1 3
1 4
3 5
3 6
3 7
2 7

```

### 输出

```
2
3

```

## 样例 #2

### 输入

```
6 4
1 2
2 3
2 4
4 5
4 6
2 4 5 6

```

### 输出

```
2
4

```

