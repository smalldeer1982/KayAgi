---
title: "Mike and Shortcuts"
layout: "post"
diff: 普及+/提高
pid: CF689B
tag: []
---

# Mike and Shortcuts

## 题目描述

Recently, Mike was very busy with studying for exams and contests. Now he is going to chill a bit by doing some sight seeing in the city.

City consists of $ n $ intersections numbered from $ 1 $ to $ n $ . Mike starts walking from his house located at the intersection number $ 1 $ and goes along some sequence of intersections. Walking from intersection number $ i $ to intersection $ j $ requires $ |i-j| $ units of energy. The total energy spent by Mike to visit a sequence of intersections $ p_{1}=1,p_{2},...,p_{k} $ is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689B/cc97750fb7205e858b8008fe7ee7f7055a90a20f.png) units of energy.

Of course, walking would be boring if there were no shortcuts. A shortcut is a special path that allows Mike walking from one intersection to another requiring only $ 1 $ unit of energy. There are exactly $ n $ shortcuts in Mike's city, the $ i^{th} $ of them allows walking from intersection $ i $ to intersection $ a_{i} $ ( $ i<=a_{i}<=a_{i+1} $ ) (but not in the opposite direction), thus there is exactly one shortcut starting at each intersection. Formally, if Mike chooses a sequence $ p_{1}=1,p_{2},...,p_{k} $ then for each $ 1<=i&lt;k $ satisfying $ p_{i+1}=a_{pi} $ and $ a_{pi}≠p_{i} $ Mike will spend only $ 1 $ unit of energy instead of $ |p_{i}-p_{i+1}| $ walking from the intersection $ p_{i} $ to intersection $ p_{i+1} $ . For example, if Mike chooses a sequence $ p_{1}=1,p_{2}=a_{p1},p_{3}=a_{p2},...,p_{k}=a_{pk-1} $ , he spends exactly $ k-1 $ units of total energy walking around them.

Before going on his adventure, Mike asks you to find the minimum amount of energy required to reach each of the intersections from his home. Formally, for each $ 1<=i<=n $ Mike is interested in finding minimum possible total energy of some sequence $ p_{1}=1,p_{2},...,p_{k}=i $ .

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=200000) $ — the number of Mike's city intersection.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (i<=a_{i}<=n $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689B/ad326ba540ee1b16339ba396d883cf47c32893d3.png), describing shortcuts of Mike's city, allowing to walk from intersection $ i $ to intersection $ a_{i} $ using only $ 1 $ unit of energy. Please note that the shortcuts don't allow walking in opposite directions (from $ a_{i} $ to $ i $ ).

## 输出格式

In the only line print $ n $ integers $ m_{1},m_{2},...,m_{n} $ , where $ m_{i} $ denotes the least amount of total energy required to walk from intersection $ 1 $ to intersection $ i $ .

## 说明/提示

In the first sample case desired sequences are:

 $ 1:1 $ ; $ m_{1}=0 $ ;

 $ 2:1,2 $ ; $ m_{2}=1 $ ;

 $ 3:1,3 $ ; $ m_{3}=|3-1|=2 $ .

In the second sample case the sequence for any intersection $ 1&lt;i $ is always $ 1,i $ and $ m_{i}=|1-i| $ .

In the third sample case — consider the following intersection sequences:

 $ 1:1 $ ; $ m_{1}=0 $ ;

 $ 2:1,2 $ ; $ m_{2}=|2-1|=1 $ ;

 $ 3:1,4,3 $ ; $ m_{3}=1+|4-3|=2 $ ;

 $ 4:1,4 $ ; $ m_{4}=1 $ ;

 $ 5:1,4,5 $ ; $ m_{5}=1+|4-5|=2 $ ;

 $ 6:1,4,6 $ ; $ m_{6}=1+|4-6|=3 $ ;

 $ 7:1,4,5,7 $ ; $ m_{7}=1+|4-5|+1=3 $ .

## 样例 #1

### 输入

```
3
2 2 3

```

### 输出

```
0 1 2 

```

## 样例 #2

### 输入

```
5
1 2 3 4 5

```

### 输出

```
0 1 2 3 4 

```

## 样例 #3

### 输入

```
7
4 4 4 4 7 7 7

```

### 输出

```
0 1 2 1 2 3 3 

```

