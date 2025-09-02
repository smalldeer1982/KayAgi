---
title: "Listening to Music"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF543E
tag: []
---

# Listening to Music

## 题目描述

Please note that the memory limit differs from the standard.

You really love to listen to music. During the each of next $ s $ days you will listen to exactly $ m $ songs from the playlist that consists of exactly $ n $ songs. Let's number the songs from the playlist with numbers from $ 1 $ to $ n $ , inclusive. The quality of song number $ i $ is $ a_{i} $ .

On the $ i $ -th day you choose some integer $ v $ ( $ l_{i}<=v<=r_{i} $ ) and listen to songs number $ v,v+1,...,v+m-1 $ . On the $ i $ -th day listening to one song with quality less than $ q_{i} $ increases your displeasure by exactly one.

Determine what minimum displeasure you can get on each of the $ s $ next days.

## 输入格式

The first line contains two positive integers $ n $ , $ m $ ( $ 1<=m<=n<=2·10^{5} $ ). The second line contains $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}&lt;2^{30} $ ) — the description of songs from the playlist.

The next line contains a single number $ s $ ( $ 1<=s<=2·10^{5} $ ) — the number of days that you consider.

The next $ s $ lines contain three integers each $ l_{i},r_{i},x_{i} $ ( $ 1<=l_{i}<=r_{i}<=n-m+1 $ ; $ 0<=x_{i}&lt;2^{30} $ ) — the description of the parameters for the $ i $ -th day. In order to calculate value $ q_{i} $ , you need to use formula: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF543E/1bb5dced0895ed7046b88afe786c4973f192f501.png), where $ ans_{i} $ is the answer to the problem for day $ i $ . Assume that $ ans_{0}=0 $ .

## 输出格式

Print exactly $ s $ integers $ ans_{1},ans_{2},...,ans_{s} $ , where $ ans_{i} $ is the minimum displeasure that you can get on day $ i $ .

## 样例 #1

### 输入

```
5 3
1 2 1 2 3
5
1 1 2
1 3 2
1 3 3
1 3 5
1 3 1

```

### 输出

```
2
0
2
3
1

```

