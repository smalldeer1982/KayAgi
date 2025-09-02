---
title: "Drazil and His Happy Friends"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF516E
tag: []
---

# Drazil and His Happy Friends

## 题目描述

Drazil has many friends. Some of them are happy and some of them are unhappy. Drazil wants to make all his friends become happy. So he invented the following plan.

There are $ n $ boys and $ m $ girls among his friends. Let's number them from $ 0 $ to $ n-1 $ and $ 0 $ to $ m-1 $ separately. In $ i $ -th day, Drazil invites $i\bmod n$ -th boy and $i\bmod m$ -th girl to have dinner together (as Drazil is programmer, $ i $ starts from $ 0 $ ). If one of those two people is happy, the other one will also become happy. Otherwise, those two people remain in their states. Once a person becomes happy (or if it is happy originally), he stays happy forever.

Drazil wants to know on which day all his friends become happy or to determine if they won't become all happy at all.

## 输入格式

The first line contains two integer $ n $ and $ m $ ( $ 1\leq n,m\leq 10^{9} $ ).

The second line contains integer $ b $ ( $ 0\leq b\leq \min(n,10^{5}) $ ), denoting the number of happy boys among friends of Drazil, and then follow $ b $ distinct integers $ x_{1},x_{2},\cdots ,x_{b} $ ( $ 0\leq x_{i} < n $ ), denoting the list of indices of happy boys.

The third line conatins integer $ g $ ( $ 0\leq g\leq \min(m,10^{5}) $ ), denoting the number of happy girls among friends of Drazil, and then follow $ g $ distinct integers $ y_{1},y_{2},\cdots,y_{g} $ ( $ 0\leq y_{j} < m $ ), denoting the list of indices of happy girls.

It is guaranteed that there is at least one person that is unhappy among his friends.

## 输出格式

Print the number of the first day that all friends of Drazil become happy. If this day won't come at all, you print -1.

## 说明/提示

By ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF516E/bc360a33d2d53f2f08a31e2a137952fc77466359.png) we define the remainder of integer division of $ i $ by $ k $ .

In first sample case:

- On the 0-th day, Drazil invites 0-th boy and 0-th girl. Because 0-th girl is happy at the beginning, 0-th boy become happy at this day.
- On the 1-st day, Drazil invites 1-st boy and 1-st girl. They are both unhappy, so nothing changes at this day.
- On the 2-nd day, Drazil invites 0-th boy and 2-nd girl. Because 0-th boy is already happy he makes 2-nd girl become happy at this day.
- On the 3-rd day, Drazil invites 1-st boy and 0-th girl. 0-th girl is happy, so she makes 1-st boy happy.
- On the 4-th day, Drazil invites 0-th boy and 1-st girl. 0-th boy is happy, so he makes the 1-st girl happy. So, all friends become happy at this moment.

## 样例 #1

### 输入

```
2 3
0
1 0

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2 4
1 0
1 2

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
2 3
1 0
1 1

```

### 输出

```
2

```

## 样例 #4

### 输入

```
99999 100000
2 514 415
2 50216 61205

```

### 输出

```
4970100515

```

