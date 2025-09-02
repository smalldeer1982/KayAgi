---
title: "COWCAR - Cow Cars"
layout: "post"
diff: 普及-
pid: SP2714
tag: ['贪心', '队列']
---

# COWCAR - Cow Cars

## 题目描述

N (1 ≤ N ≤ 50,000) cows conveniently numbered 1, ..., N are driving in separate cars along a highway in Cowtopia. Cow i can drive in any of M different high lanes (1 ≤ M ≤ N) and can travel at a maximum speed of S $ _{i} $ (1 ≤ S $ _{i} $ ≤ 1,000,000) km/hour.

After their other bad driving experience, the cows hate collisions and take extraordinary measures to avoid them. On this highway, cow i reduces its speed by D (0 ≤ D ≤ 5,000) km/hour for each cow in front of it on the highway (though never below 0 km/hour). Thus, if there are K cows in front of cow i, the cow will travel at a speed of max(S $ _{i} $ - D\*K, 0). While a cow might actually travel faster than a cow directly in front of it, the cows are spaced far enough apart so crashes will not occur once cows slow down as described.

Cowtopia has a minimum speed law which requires everyone on the highway to travel at a a minimum speed of L (1 ≤ L ≤ 1,000,000) km/hour, so sometimes some of the cows will be unable to take the highway if they follow the rules above. Write a program that will find the maximum number of cows that can drive on the highway while obeying the minimum speed limit law.

## 输入格式

The first line contains the four integers N, M, D, and L. For the next N lines, line i+1 contains the integer S $ _{i} $ .

## 输出格式

Print a single integer denoting the maximum number of cows that can take the highway.

## 样例 #1

### 输入

```
3 1 1 5

5

7

5
```

### 输出

```
2
```



---

