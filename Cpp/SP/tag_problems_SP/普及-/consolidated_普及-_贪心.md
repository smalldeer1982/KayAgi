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

---
title: "MDOLLS - Nested Dolls"
layout: "post"
diff: 普及-
pid: SP3943
tag: ['贪心', '二分', '排序']
---

# MDOLLS - Nested Dolls

## 题目描述

[English](/problems/MDOLLS/en/) [Vietnamese](/problems/MDOLLS/vn/) ```

Dilworth is the world's most prominent collector of Russian nested dolls:
he literally has thousands of them! You know, the wooden hollow dolls of 
different sizes of which the smallest doll is contained in the second smallest,
and this doll is in turn contained in the next one and so forth. One day he
wonders if there is another way of nesting them so he will end up with
fewer nested dolls? After all, that would make his collection even 
more magnificent! He unpacks each nested doll and measures the width 
and height of each contained doll. A doll with width w1 and height h1 will
fit in another doll of width w2 and height h= if and only if w1 < w2 and 
h1 < h2. Can you help him calculate the smallest number of nested dolls 
possible to assemble from his massive list of measurements? 
```

## 输入格式

```

On the first line of input is a single positive integer 1 ≤ t ≤ 20 specifying
the number of test cases to follow. Each test case begins with a positive 
integer 1 ≤ m ≤ 20000 on a line of itself telling the number of dolls 
in the test case. Next follow 2m positive integers w1, h1,w2, h2, ... ,wm, 
hm, where wi is the width and hi is the height of doll number i. 
1 ≤ wi, hi ≤ 10000 for all i.

SAMPLE INPUT
4
3
20 30 40 50 30 40
4
20 30 10 10 30 20 40 50
3
10 30 20 20 30 10
4
10 10 20 30 40 50 39 51
```

## 输出格式

```
 
For each test case there should be one line of output containing the minimum
number of nested dolls possible.

SAMPLE OUTPUT
1
2
3
2
```



---

