---
title: "Fence Divercity"
layout: "post"
diff: 省选/NOI-
pid: CF659G
tag: []
---

# Fence Divercity

## 题目描述

Long ago, Vasily built a good fence at his country house. Vasily calls a fence good, if it is a series of $ n $ consecutively fastened vertical boards of centimeter width, the height of each in centimeters is a positive integer. The house owner remembers that the height of the $ i $ -th board to the left is $ h_{i} $ .

Today Vasily decided to change the design of the fence he had built, by cutting his top connected part so that the fence remained good. The cut part should consist of only the upper parts of the boards, while the adjacent parts must be interconnected (share a non-zero length before cutting out of the fence).

You, as Vasily's curious neighbor, will count the number of possible ways to cut exactly one part as is described above. Two ways to cut a part are called distinct, if for the remaining fences there is such $ i $ , that the height of the $ i $ -th boards vary.

As Vasily's fence can be very high and long, get the remainder after dividing the required number of ways by $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=1000000 $ ) — the number of boards in Vasily's fence.

The second line contains $ n $ space-separated numbers $ h_{1},h_{2},...,h_{n} $ ( $ 1<=h_{i}<=10^{9} $ ), where $ h_{i} $ equals the height of the $ i $ -th board to the left.

## 输出格式

Print the remainder after dividing $ r $ by $ 1000000007 $ , where $ r $ is the number of ways to cut exactly one connected part so that the part consisted of the upper parts of the boards and the remaining fence was good.

## 说明/提示

From the fence from the first example it is impossible to cut exactly one piece so as the remaining fence was good.

All the possible variants of the resulting fence from the second sample look as follows (the grey shows the cut out part):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF659G/a2b3bf8825e8935004832f4f03b0b46a19d70316.png)

## 样例 #1

### 输入

```
2
1 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3
3 4 2

```

### 输出

```
13

```

