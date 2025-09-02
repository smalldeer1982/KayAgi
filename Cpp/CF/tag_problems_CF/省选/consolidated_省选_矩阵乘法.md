---
title: "Let Me Teach You a Lesson (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1995E2
tag: ['线段树', '矩阵乘法']
---

# Let Me Teach You a Lesson (Hard Version)

## 题目描述

This is the hard version of a problem. The only difference between an easy and a hard version is the constraints on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

Arthur is giving a lesson to his famous $ 2 n $ knights. Like any other students, they're sitting at the desks in pairs, but out of habit in a circle. The knight $ 2 i - 1 $ is sitting at the desk with the knight $ 2 i $ .

Each knight has intelligence, which can be measured by an integer. Let's denote the intelligence of the $ i $ -th knight as $ a_i $ . Arthur wants the maximal difference in total intelligence over all pairs of desks to be as small as possible. More formally, he wants to minimize $ \max\limits_{1 \le i \le n} (a_{2 i - 1} + a_{2 i}) - \min\limits_{1 \le i \le n} (a_{2 i - 1} + a_{2 i}) $ .

However, the Code of Chivalry only allows swapping the opposite knights in the circle, i.e., Arthur can simultaneously perform $ a_i := a_{i + n} $ , $ a_{i + n} := a_i $ for any $ 1 \le i \le n $ . Arthur can make any number of such swaps. What is the best result he can achieve?

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10\,000 $ ) — the number of test cases. It is followed by descriptions of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100\,000 $ ) — the number of desks.

The second line consists of $ 2n $ integers $ a_1, a_2, \ldots, a_{2 n} $ ( $ 1 \le a_i \le 10^9 $ ) — the intelligence values of the knights.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 100\,000 $ .

## 输出格式

For each test case, output a single line containing one integer — the minimal difference Arthur can achieve.

## 说明/提示

In the first test case, Arthur can swap the second and the fourth knights. Then the total intelligence at both desks will be $ 10 $ .

In the third test case, Arthur can make $ 0 $ operations, which will result in the total intelligence of $ 11 $ at each of the desks.

In the fourth test case, Arthur can swap knights with indices $ 2 $ and $ 5 $ and achieve the difference of $ 2 $ . It can be proven that he cannot improve his result any further.

## 样例 #1

### 输入

```
5
2
6 6 4 4
1
10 17
3
1 10 1 10 1 10
3
3 3 4 5 5 4
5
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
0
0
0
2
4
```



---

---
title: "Sasha and Array"
layout: "post"
diff: 省选/NOI-
pid: CF718C
tag: ['线段树', '斐波那契数列', '矩阵乘法']
---

# Sasha and Array

## 题目描述

Sasha has an array of integers $ a_{1},a_{2},...,a_{n} $ . You have to perform $ m $ queries. There might be queries of two types:

1. 1 l r x — increase all integers on the segment from $ l $ to $ r $ by values $ x $ ;
2. 2 l r — find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF718C/9868345ffca37ba44cd594bdeb805f21011d5d1d.png), where $ f(x) $ is the $ x $ -th Fibonacci number. As this number may be large, you only have to find it modulo $ 10^{9}+7 $ .

In this problem we define Fibonacci numbers as follows: $ f(1)=1 $ , $ f(2)=1 $ , $ f(x)=f(x-1)+f(x-2) $ for all $ x>2 $ .

Sasha is a very talented boy and he managed to perform all queries in five seconds. Will you be able to write the program that performs as well as Sasha?

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n<=100000 $ , $ 1<=m<=100000 $ ) — the number of elements in the array and the number of queries respectively.

The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

Then follow $ m $ lines with queries descriptions. Each of them contains integers $ tp_{i} $ , $ l_{i} $ , $ r_{i} $ and may be $ x_{i} $ ( $ 1<=tp_{i}<=2 $ , $ 1<=l_{i}<=r_{i}<=n $ , $ 1<=x_{i}<=10^{9} $ ). Here $ tp_{i}=1 $ corresponds to the queries of the first type and $ tp_{i} $ corresponds to the queries of the second type.

It's guaranteed that the input will contains at least one query of the second type.

## 输出格式

For each query of the second type print the answer modulo $ 10^{9}+7 $ .

## 说明/提示

Initially, array $ a $ is equal to $ 1 $ , $ 1 $ , $ 2 $ , $ 1 $ , $ 1 $ .

The answer for the first query of the second type is $ f(1)+f(1)+f(2)+f(1)+f(1)=1+1+1+1+1=5 $ .

After the query 1 2 4 2 array $ a $ is equal to $ 1 $ , $ 3 $ , $ 4 $ , $ 3 $ , $ 1 $ .

The answer for the second query of the second type is $ f(3)+f(4)+f(3)=2+3+2=7 $ .

The answer for the third query of the second type is $ f(1)+f(3)+f(4)+f(3)+f(1)=1+2+3+2+1=9 $ .

## 样例 #1

### 输入

```
5 4
1 1 2 1 1
2 1 5
1 2 4 2
2 2 4
2 1 5

```

### 输出

```
5
7
9

```



---

---
title: "A Trance of Nightfall"
layout: "post"
diff: 省选/NOI-
pid: CF989E
tag: ['进制', '矩阵乘法', '构造']
---

# A Trance of Nightfall

## 题目描述

 The cool breeze blows gently, the flowing water ripples steadily."Flowing and passing like this, the water isn't gone ultimately; Waxing and waning like that, the moon doesn't shrink or grow eventually."

"Everything is transient in a way and perennial in another."

Kanno doesn't seem to make much sense out of Mino's isolated words, but maybe it's time that they enjoy the gentle breeze and the night sky — the inexhaustible gifts from nature.

Gazing into the sky of stars, Kanno indulges in a night's tranquil dreams.





There is a set $ S $ of $ n $ points on a coordinate plane.

Kanno starts from a point $ P $ that can be chosen on the plane. $ P $ is not added to $ S $ if it doesn't belong to $ S $ . Then the following sequence of operations (altogether called a move) is repeated several times, in the given order:

1. Choose a line $ l $ such that it passes through at least two elements in $ S $ and passes through Kanno's current position. If there are multiple such lines, one is chosen equiprobably.
2. Move to one of the points that belong to $ S $ and lie on $ l $ . The destination is chosen equiprobably among all possible ones, including Kanno's current position (if it does belong to $ S $ ).

There are $ q $ queries each consisting of two integers $ (t_i, m_i) $ . For each query, you're to help Kanno maximize the probability of the stopping position being the $ t_i $ -th element in $ S $ after $ m_i $ moves with a proper selection of $ P $ , and output this maximum probability. Note that according to rule 1, $ P $ should belong to at least one line that passes through at least two points from $ S $ .

## 输入格式

The first line contains a positive integer $ n $ ( $ 2 \leq n \leq 200 $ ) — the number of points in $ S $ .

The $ i $ -th of the following $ n $ lines contains two space-separated integers $ x_i $ and $ y_i $ ( $ -10^4 \leq x_i, y_i \leq 10^4 $ ) — the coordinates of the $ i $ -th point in $ S $ . The input guarantees that for all $ 1 \leq i \lt j \leq n $ , $ (x_i, y_i) \neq (x_j, y_j) $ holds.

The next line contains a positive integer $ q $ ( $ 1 \leq q \leq 200 $ ) — the number of queries.

Each of the following $ q $ lines contains two space-separated integers $ t $ and $ m $ ( $ 1 \leq t_i \leq n $ , $ 1 \leq m_i \leq 10^4 $ ) — the index of the target point and the number of moves, respectively.

## 输出格式

Output $ q $ lines each containing a decimal number — the $ i $ -th among them denotes the maximum probability of staying on the $ t_i $ -th point after $ m_i $ steps, with a proper choice of starting position $ P $ .

Your answer will be considered correct if each number in your output differs from the corresponding one in jury's answer by at most $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is considered correct if $ |a - b| \le 10^{-6} $ .

## 说明/提示

The points in $ S $ and possible candidates for line $ l $ are depicted in the following figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF989E/9dc6a2e53d51df32abc295e2febe0114d0e3d73f.png)For the first query, when $ P = (-1, -3) $ , $ l $ is uniquely determined to be $ 3x = y $ , and thus Kanno will move to $ (0, 0) $ with a probability of $ \frac 1 2 $ .

For the third query, when $ P = (2, 2) $ , $ l $ is chosen equiprobably between $ x + y = 4 $ and $ x = y $ . Kanno will then move to the other four points with a probability of $ \frac 1 2 \cdot \frac 1 3 = \frac 1 6 $ each, or stay at $ (2, 2) $ with a probability of $ \frac 1 3 $ .

## 样例 #1

### 输入

```
5
0 0
1 3
2 2
3 1
4 4
10
1 1
2 1
3 1
4 1
5 1
3 2
3 3
3 4
3 5
3 6

```

### 输出

```
0.50000000000000000000
0.50000000000000000000
0.33333333333333331483
0.50000000000000000000
0.50000000000000000000
0.18518518518518517491
0.15226337448559670862
0.14494741655235482414
0.14332164812274550414
0.14296036624949901017

```



---

