---
title: "Drazil and His Happy Friends"
layout: "post"
diff: 普及+/提高
pid: CF515B
tag: []
---

# Drazil and His Happy Friends

## 题目描述

Drazil has many friends. Some of them are happy and some of them are unhappy. Drazil wants to make all his friends become happy. So he invented the following plan.

There are $ n $ boys and $ m $ girls among his friends. Let's number them from $ 0 $ to $ n-1 $ and $ 0 $ to $ m-1 $ separately. In $ i $ -th day, Drazil invites ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515B/0da6b9a3d02abb66f05faf59011ade551446e858.png)-th boy and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515B/b11adea5506a14de900c875f929fb5324c4eb93f.png)-th girl to have dinner together (as Drazil is programmer, $ i $ starts from $ 0 $ ). If one of those two people is happy, the other one will also become happy. Otherwise, those two people remain in their states. Once a person becomes happy (or if he/she was happy originally), he stays happy forever.

Drazil wants to know whether he can use this plan to make all his friends become happy at some moment.

## 输入格式

The first line contains two integer $ n $ and $ m $ ( $ 1<=n,m<=100 $ ).

The second line contains integer $ b $ ( $ 0<=b<=n $ ), denoting the number of happy boys among friends of Drazil, and then follow $ b $ distinct integers $ x_{1},x_{2},...,x_{b} $ ( $ 0<=x_{i}&lt;n $ ), denoting the list of indices of happy boys.

The third line conatins integer $ g $ ( $ 0<=g<=m $ ), denoting the number of happy girls among friends of Drazil, and then follow $ g $ distinct integers $ y_{1},y_{2},...\ ,y_{g} $ ( $ 0<=y_{j}&lt;m $ ), denoting the list of indices of happy girls.

It is guaranteed that there is at least one person that is unhappy among his friends.

## 输出格式

If Drazil can make all his friends become happy by this plan, print "Yes". Otherwise, print "No".

## 说明/提示

By ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515B/bc360a33d2d53f2f08a31e2a137952fc77466359.png) we define the remainder of integer division of $ i $ by $ k $ .

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
Yes

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
No

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
Yes

```

