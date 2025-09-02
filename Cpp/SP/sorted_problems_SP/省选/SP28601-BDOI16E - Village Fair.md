---
title: "BDOI16E - Village Fair"
layout: "post"
diff: 省选/NOI-
pid: SP28601
tag: []
---

# BDOI16E - Village Fair

## 题目描述

 <a name="page1"></a> **Village Fair**

There are N houses in a village far away from here. They are numbered from 1 to N. For this problem lets assume, the houses each can accommodate infinite amount of people. **From each house there is a** **directed path to exactly one other house**. One of the houses is a grand house. There is a fair going on currently in the grand house. From this house there is no exit, and everybody can enjoy the festival here. Initially there is a little kid in each of the houses of the village. Each kid has some non-negative amount of joy(they are all pretty excited about the fair). It is guaranteed that there is exactly one simple way from each house to the grand house.

Every kid from their house starts their journey to the grand house. When they go from a house to some other house, their joy changes by some positive or negative amount. This change depends on the path.

Now, for each houses, you have to count the number of distinct joy values that will come to this house at some point of time. Note that if two or more persons with the same joy value will be counted only once. See the sample explanation for details.

**Input:**

You are given an integer N in the first line. The next line will contain N integers, the initial joy value of the kids in the houses. The next line also contains N integers, where the kth integer is the id of the house where the kids can go to from the kth house or 0 if it is the grand house. The fourth line will contain N integers, the amount of change of joy that will occur if one person goes through the path from starting at kth house or 0 if it is the grand house.

**Output:**

Print N lines, each containing the number of distinct joy values that will come to this house at some point of time.

 Input

  Output

  5

7 3 2 5 1

0 1 1 3 3

0 4 1 0 4

  3

1

2

1

1

 **Explanation of Sample:**

Initially each house will contain the kids with joy { 7, 3, 2, 5, 1 }. The first kid always stays in the grand house. The second kid will go to the grand house with joy 7. The 3 $ ^{rd} $  kid will go to the grand house with joy 3. The fourth kid will go to 3 $ ^{rd} $  house with joy 5 and from there he will make it to grand house with 6 joy. Same goes for 5 $ ^{th} $  person.

So the first house will see { 7, 7, 3, 6, 6}. The second house will see {3}. The third house will see {2, 5, 5} The fourth house will see { 5 } and the fifth house will see { 1 }.

So the number of distinct joy values of each house is { 3, 1, 2, 1, 1}.

<a name="_GoBack"></a>Limits: Easy(1 <= N <= 1000), Hard(1 <= N <= 100000).

  
**Problem Setter: Nafis Sadique**

