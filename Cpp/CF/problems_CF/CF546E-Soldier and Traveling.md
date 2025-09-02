---
title: "Soldier and Traveling"
layout: "post"
diff: 省选/NOI-
pid: CF546E
tag: []
---

# Soldier and Traveling

## 题目描述

In the country there are $ n $ cities and $ m $ bidirectional roads between them. Each city has an army. Army of the $ i $ -th city consists of $ a_{i} $ soldiers. Now soldiers roam. After roaming each soldier has to either stay in his city or to go to the one of neighboring cities by at moving along at most one road.

Check if is it possible that after roaming there will be exactly $ b_{i} $ soldiers in the $ i $ -th city.

## 输入格式

First line of input consists of two integers $ n $ and $ m $ ( $ 1<=n<=100 $ , $ 0<=m<=200 $ ).

Next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=100 $ ).

Next line contains $ n $ integers $ b_{1},b_{2},...,b_{n} $ ( $ 0<=b_{i}<=100 $ ).

Then $ m $ lines follow, each of them consists of two integers $ p $ and $ q $ ( $ 1<=p,q<=n $ , $ p≠q $ ) denoting that there is an undirected road between cities $ p $ and $ q $ .

It is guaranteed that there is at most one road between each pair of cities.

## 输出格式

If the conditions can not be met output single word "NO".

Otherwise output word "YES" and then $ n $ lines, each of them consisting of $ n $ integers. Number in the $ i $ -th line in the $ j $ -th column should denote how many soldiers should road from city $ i $ to city $ j $ (if $ i≠j $ ) or how many soldiers should stay in city $ i $ (if $ i=j $ ).

If there are several possible answers you may output any of them.

## 样例 #1

### 输入

```
4 4
1 2 6 3
3 5 3 1
1 2
2 3
3 4
4 2

```

### 输出

```
YES
1 0 0 0 
2 0 0 0 
0 5 1 0 
0 0 2 1 

```

## 样例 #2

### 输入

```
2 0
1 2
2 1

```

### 输出

```
NO
```

