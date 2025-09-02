---
title: "Student's Camp"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF708E
tag: ['动态规划 DP', '排列组合']
---

# Student's Camp

## 题目描述

Alex studied well and won the trip to student camp Alushta, located on the seashore.

Unfortunately, it's the period of the strong winds now and there is a chance the camp will be destroyed! Camp building can be represented as the rectangle of $ n+2 $ concrete blocks height and $ m $ blocks width.

Every day there is a breeze blowing from the sea. Each block, except for the blocks of the upper and lower levers, such that there is no block to the left of it is destroyed with the probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/422afcf1e06a5628bae49992f52449e3f10a781f.png). Similarly, each night the breeze blows in the direction to the sea. Thus, each block (again, except for the blocks of the upper and lower levers) such that there is no block to the right of it is destroyed with the same probability $ p $ . Note, that blocks of the upper and lower level are indestructible, so there are only $ n·m $ blocks that can be destroyed.

The period of the strong winds will last for $ k $ days and $ k $ nights. If during this period the building will split in at least two connected components, it will collapse and Alex will have to find another place to spend summer.

Find the probability that Alex won't have to look for other opportunities and will be able to spend the summer in this camp.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=1500 $ ) that define the size of the destructible part of building.

The second line of the input contains two integers $ a $ and $ b $ ( $ 1<=a<=b<=10^{9} $ ) that define the probability $ p $ . It's guaranteed that integers $ a $ and $ b $ are coprime.

The third line contains a single integer $ k $ ( $ 0<=k<=100000 $ ) — the number of days and nights strong wind will blow for.

## 输出格式

Consider the answer as an irreducible fraction is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/80a3a0e00c79b470772b3be90efd3e0d2e457bd7.png). Print one integer equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/554b30b982e35fb63eb76dd412a37e11659c08f3.png). It's guaranteed that within the given constraints ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/7e61bb4a29a39d49b7ec2c70e2cceae658d627bd.png).

## 说明/提示

In the first sample, each of the four blocks is destroyed with the probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/fda96725ccc697b767e5edbf0d5cfb5ba17d9aa2.png). There are $ 7 $ scenarios that result in building not collapsing, and the probability we are looking for is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/dda8ba13f4feb6c7325a04d07cb771a7084c4ba2.png), so you should print ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/823f9bb4d7539823cd6e4037b4f9a35cb2e52f03.png)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/2ecb6c84ea76dfa6c7235391533a743f1c25b7f8.png)

## 样例 #1

### 输入

```
2 2
1 2
1

```

### 输出

```
937500007

```

## 样例 #2

### 输入

```
5 1
3 10
1

```

### 输出

```
95964640

```

## 样例 #3

### 输入

```
3 3
1 10
5

```

### 输出

```
927188454

```



---

