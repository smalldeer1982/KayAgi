---
title: "ALT"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF786E
tag: []
---

# ALT

## 题目描述

ALT is a planet in a galaxy called "Encore". Humans rule this planet but for some reason there's no dog in their planet, so the people there are sad and depressed. Rick and Morty are universal philanthropists and they want to make people in ALT happy.

ALT has $ n $ cities numbered from $ 1 $ to $ n $ and $ n-1 $ bidirectional roads numbered from $ 1 $ to $ n-1 $ . One can go from any city to any other city using these roads.

There are two types of people in ALT:

1. Guardians. A guardian lives in a house alongside a road and guards the road.
2. Citizens. A citizen lives in a house inside a city and works in an office in another city.

Every person on ALT is either a guardian or a citizen and there's exactly one guardian alongside each road.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786E/98823384a51131ca904b345eb24e1dfd63229a39.png)Rick and Morty talked to all the people in ALT, and here's what they got:

- There are $ m $ citizens living in ALT.
- Citizen number $ i $ lives in city number $ x_{i} $ and works in city number $ y_{i} $ .
- Every day each citizen will go through all roads along the shortest path from his home to his work.
- A citizen will be happy if and only if either he himself has a puppy himself or all of guardians along his path to his work has a puppy (he sees the guardian's puppy in each road and will be happy).
- A guardian is always happy.

You need to tell Rick and Morty the minimum number of puppies they need in order to make all people in ALT happy, and also provide an optimal way to distribute these puppies.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 2<=n<=2×10^{4} $ , $ 1<=m<=10^{4} $ ) — number of cities and number of citizens respectively.

The next $ n-1 $ lines contain the roads, $ i $ -th line contains endpoint of $ i $ -th edge, $ v $ and $ u $ ( $ 1<=v,u<=n $ , $ v≠u $ ).

The next $ m $ lines contain the information about citizens. $ i $ -th line contains two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=n $ , $ x_{i}≠y_{i} $ ).

## 输出格式

In the first line of input print a single integer $ k $ , the total number of puppies they need ( $ 1<=k<=n $ ).

In the second line print an integer $ q $ , the number of puppies to give to citizens, followed by $ q $ distinct integers $ a_{1},a_{2},...,a_{q} $ , index of citizens to give puppy to ( $ 0<=q<=min(m,k) $ , $ 1<=a_{i}<=m $ ).

In the third line print an integer $ e $ , the number of puppies to give to guardians, followed by $ e $ distinct integers $ b_{1},b_{2},...,b_{e} $ , index of road of guardians to give puppy to ( $ 0<=e<=min(n-1,k) $ , $ 1<=b_{i}<=n-1 $ ).

Sum of $ q $ and $ e $ should be equal to $ k $ .

## 说明/提示

Map of ALT in the first sample testcase (numbers written on a road is its index):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786E/7a9e6fa1daa23b80f01b793c79a6a9d57b816dca.png)Map of ALT in the second sample testcase (numbers written on a road is its index):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786E/4dd536a81d1bc8f835994567a99f1287412e7178.png)

## 样例 #1

### 输入

```
4 5
2 4
3 4
1 4
2 4
2 1
2 4
1 2
2 3

```

### 输出

```
3
1 5 
2 3 1 

```

## 样例 #2

### 输入

```
4 7
3 4
1 4
2 1
4 2
4 2
2 4
1 4
2 1
3 1
4 2

```

### 输出

```
3
1 6 
2 2 3 

```

