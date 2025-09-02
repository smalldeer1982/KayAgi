---
title: "Lucky Array"
layout: "post"
diff: 省选/NOI-
pid: CF121E
tag: ['树状数组', '枚举', '进制']
---

# Lucky Array

## 题目描述

Petya 喜欢幸运数，幸运数只包含 $4$ 和 $7$ 这两个数字。例如 $47$，$744$，$4$ 都是幸运数字，但 $5,16,467$ 不是。

Petya 有一个 $N$ 个数的数组，他想给这个数组执行 $M$ 个操作，可以分为两种操作：

1. `add l r d` 把第 $l$ 到第 $r$ 个数都加上 $d$；
2. `count l r` 统计第 $l$ 到第 $r$ 个数有多少个幸运数字。

保证所有数操作前后都不超过 $10^4$。

请你编一个程序来执行这些操作。

$1\leq N,M\leq 10^5$，$1\leq l\leq r\leq N$，$1\leq d \leq 10^4$。

## 输入格式

第一行，两个数 $N$ 和 $M$；

第二行，$N$ 个数，表示原数组；

## 输出格式

对于每个询问幸运数个数的问题，输出答案，每个占一行。

_输入输出样例在下面_

## 说明/提示

对于第一个样例：

1. 执行了 `add 1 3 2` 操作之后变成：$[4, 5, 6]$；
2. 执行了 `add 2 3 3` 操作之后变成：$[4, 8, 9]$。

对于第二个样例：

1. 执行了 `add 1 4 3` 之后变成：$[7,7,7,7]$；
2. 执行了 `add 2 3 40` 之后变成：$[7,47,47,7]$。

## 样例 #1

### 输入

```
3 6
2 3 4
count 1 3
count 1 2
add 1 3 2
count 1 3
add 2 3 3
count 1 3

```

### 输出

```
1
0
1
1

```

## 样例 #2

### 输入

```
4 5
4 4 4 4
count 1 4
add 1 4 3
count 1 4
add 2 3 40
count 1 4

```

### 输出

```
4
4
4

```



---

---
title: "Rotatable Number"
layout: "post"
diff: 省选/NOI-
pid: CF303D
tag: ['素数判断,质数,筛法', '进制']
---

# Rotatable Number

## 题目描述

Bike is a smart boy who loves math very much. He invented a number called "Rotatable Number" inspired by $ 142857 $ .

As you can see, $ 142857 $ is a magic number because any of its rotatings can be got by multiplying that number by $ 1,2,...,6 $ (numbers from one to number's length). Rotating a number means putting its last several digit into first. For example, by rotating number $ 12345 $ you can obtain any numbers: $ 12345,51234,45123,34512,23451 $ . It's worth mentioning that leading-zeroes are allowed. So both $ 4500123 $ and $ 0123450 $ can be obtained by rotating $ 0012345 $ . You can see why $ 142857 $ satisfies the condition. All of the $ 6 $ equations are under base $ 10 $ .

- $ 142857·1=142857 $ ;
- $ 142857·2=285714 $ ;
- $ 142857·3=428571 $ ;
- $ 142857·4=571428 $ ;
- $ 142857·5=714285 $ ;
- $ 142857·6=857142 $ .

Now, Bike has a problem. He extends "Rotatable Number" under any base $ b $ . As is mentioned above, $ 142857 $ is a "Rotatable Number" under base $ 10 $ . Another example is $ 0011 $ under base 2. All of the $ 4 $ equations are under base $ 2 $ .

- $ 0011·1=0011 $ ;
- $ 0011·10=0110 $ ;
- $ 0011·11=1001 $ ;
- $ 0011·100=1100 $ .

So, he wants to find the largest $ b $ $ (1&lt;b&lt;x) $ so that there is a positive "Rotatable Number" (leading-zeroes allowed) of length $ n $ under base $ b $ .

Note that any time you multiply a rotatable number by numbers from 1 to its length you should get a rotating of that number.

## 输入格式

The only line contains two space-separated integers $ n,x $ $ (1<=n<=5·10^{6},2<=x<=10^{9}) $ .

## 输出格式

Print a single integer — the largest $ b $ you found. If no such $ b $ exists, print -1 instead.

## 样例 #1

### 输入

```
6 11

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 8

```

### 输出

```
-1

```



---

---
title: "Axis Walking"
layout: "post"
diff: 省选/NOI-
pid: CF327E
tag: ['状态合并', '进制', '前缀和']
---

# Axis Walking

## 题目描述

Iahub wants to meet his girlfriend Iahubina. They both live in $ Ox $ axis (the horizontal axis). Iahub lives at point 0 and Iahubina at point $ d $ .

Iahub has $ n $ positive integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . The sum of those numbers is $ d $ . Suppose $ p_{1} $ , $ p_{2} $ , ..., $ p_{n} $ is a permutation of $ {1,2,...,n} $ . Then, let $ b_{1}=a_{p1} $ , $ b_{2}=a_{p2} $ and so on. The array b is called a "route". There are $ n! $ different routes, one for each permutation $ p $ .

Iahub's travel schedule is: he walks $ b_{1} $ steps on $ Ox $ axis, then he makes a break in point $ b_{1} $ . Then, he walks $ b_{2} $ more steps on $ Ox $ axis and makes a break in point $ b_{1}+b_{2} $ . Similarly, at $ j $ -th $ (1<=j<=n) $ time he walks $ b_{j} $ more steps on $ Ox $ axis and makes a break in point $ b_{1}+b_{2}+...+b_{j} $ .

Iahub is very superstitious and has $ k $ integers which give him bad luck. He calls a route "good" if he never makes a break in a point corresponding to one of those $ k $ numbers. For his own curiosity, answer how many good routes he can make, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=24 $ ). The following line contains $ n $ integers: $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

The third line contains integer $ k $ ( $ 0<=k<=2 $ ). The fourth line contains $ k $ positive integers, representing the numbers that give Iahub bad luck. Each of these numbers does not exceed $ 10^{9} $ .

## 输出格式

Output a single integer — the answer of Iahub's dilemma modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first case consider six possible orderings:

- \[2, 3, 5\]. Iahub will stop at position 2, 5 and 10. Among them, 5 is bad luck for him.
- \[2, 5, 3\]. Iahub will stop at position 2, 7 and 10. Among them, 7 is bad luck for him.
- \[3, 2, 5\]. He will stop at the unlucky 5.
- \[3, 5, 2\]. This is a valid ordering.
- \[5, 2, 3\]. He got unlucky twice (5 and 7).
- \[5, 3, 2\]. Iahub would reject, as it sends him to position 5.

In the second case, note that it is possible that two different ways have the identical set of stopping. In fact, all six possible ways have the same stops: \[2, 4, 6\], so there's no bad luck for Iahub.

## 样例 #1

### 输入

```
3
2 3 5
2
5 7

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
2 2 2
2
1 3

```

### 输出

```
6

```



---

---
title: "Devu and Flowers"
layout: "post"
diff: 省选/NOI-
pid: CF451E
tag: ['状态合并', '进制', '容斥原理']
---

# Devu and Flowers

## 题目描述

Devu wants to decorate his garden with flowers. He has purchased $ n $ boxes, where the $ i $ -th box contains $ f_{i} $ flowers. All flowers in a single box are of the same color (hence they are indistinguishable). Also, no two boxes have flowers of the same color.

Now Devu wants to select exactly $ s $ flowers from the boxes to decorate his garden. Devu would like to know, in how many different ways can he select the flowers from each box? Since this number may be very large, he asks you to find the number modulo $ (10^{9}+7) $ .

Devu considers two ways different if there is at least one box from which different number of flowers are selected in these two ways.

## 输入格式

The first line of input contains two space-separated integers $ n $ and $ s $ ( $ 1<=n<=20 $ , $ 0<=s<=10^{14} $ ).

The second line contains $ n $ space-separated integers $ f_{1},f_{2},...\ f_{n} $ ( $ 0<=f_{i}<=10^{12} $ ).

## 输出格式

Output a single integer — the number of ways in which Devu can select the flowers modulo $ (10^{9}+7) $ .

## 说明/提示

Sample 1. There are two ways of selecting $ 3 $ flowers: $ {1,2} $ and $ {0,3} $ .

Sample 2. There is only one way of selecting $ 4 $ flowers: $ {2,2} $ .

Sample 3. There are three ways of selecting $ 5 $ flowers: $ {1,2,2} $ , $ {0,3,2} $ , and $ {1,3,1} $ .

## 样例 #1

### 输入

```
2 3
1 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 4
2 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 5
1 3 2

```

### 输出

```
3

```



---

---
title: "Xor-matic Number of the Graph"
layout: "post"
diff: 省选/NOI-
pid: CF724G
tag: ['进制', '概率论', '线性基']
---

# Xor-matic Number of the Graph

## 题目描述

给你一个无向图，有n个顶点和m条边，每条边上都有一个非负权值。

我们称一个三元组  $(u,v,s)$ 是有趣的，当且仅当对于 $1 \le u < v \le n$ 且有一条从 $u$ 到 $v$ 的路径(可以经过相同的点和边多次)，其路径上的权值异或和为  $s$。对于一条路径，如果一条边经过了多次，则计算异或和时也应计算多次。不难证明，这样的三元组是有限的。

计算所有有趣的三元组中 $s$ 的和对于 $10^9+7$ 的模数

## 输入格式

第一行包括两个整数  $n,m,(n\in [1,10^5],m\in[0,2*10^5]$  ——图中点数与边数

接下来的  $m$  行每行包括3个整数  $u_i,v_i,t_i(u_i,v_i\in [1,n],t_i\in [0,10^{18}],u_i\not = v_i)$  ——边的两端点序号与边的权值

图中无自环与重边

## 输出格式

输出一个整数，即题目中的答案对于  $10^9+7$  的mod值

感谢@Dimitry_L 提供的翻译

## 样例 #1

### 输入

```
4 4
1 2 1
1 3 2
2 3 3
3 4 1

```

### 输出

```
12

```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 2
3 4 4
4 1 8

```

### 输出

```
90

```

## 样例 #3

### 输入

```
8 6
1 2 2
2 3 1
2 4 4
4 5 5
4 6 3
7 8 5

```

### 输出

```
62

```



---

---
title: "PolandBall and Gifts"
layout: "post"
diff: 省选/NOI-
pid: CF755F
tag: ['贪心', '背包 DP', '进制']
---

# PolandBall and Gifts

## 题目描述

It's Christmas time! PolandBall and his friends will be giving themselves gifts. There are $ n $ Balls overall. Each Ball has someone for whom he should bring a present according to some permutation $ p $ , $ p_{i}≠i $ for all $ i $ .

Unfortunately, Balls are quite clumsy. We know earlier that exactly $ k $ of them will forget to bring their gift. A Ball number $ i $ will get his present if the following two constraints will hold:

1. Ball number $ i $ will bring the present he should give.
2. Ball $ x $ such that $ p_{x}=i $ will bring his present.

What is minimum and maximum possible number of kids who will not get their present if exactly $ k $ Balls will forget theirs?

## 输入格式

The first line of input contains two integers $ n $ and $ k $ ( $ 2<=n<=10^{6} $ , $ 0<=k<=n $ ), representing the number of Balls and the number of Balls who will forget to bring their presents.

The second line contains the permutation $ p $ of integers from $ 1 $ to $ n $ , where $ p_{i} $ is the index of Ball who should get a gift from the $ i $ -th Ball. For all $ i $ , $ p_{i}≠i $ holds.

## 输出格式

You should output two values — minimum and maximum possible number of Balls who will not get their presents, in that order.

## 说明/提示

In the first sample, if the third and the first balls will forget to bring their presents, they will be th only balls not getting a present. Thus the minimum answer is $ 2 $ . However, if the first ans the second balls will forget to bring their presents, then only the fifth ball will get a present. So, the maximum answer is $ 4 $ .

## 样例 #1

### 输入

```
5 2
3 4 1 5 2

```

### 输出

```
2 4
```

## 样例 #2

### 输入

```
10 1
2 3 4 5 6 7 8 9 10 1

```

### 输出

```
2 2
```



---

---
title: "Xor-MST"
layout: "post"
diff: 省选/NOI-
pid: CF888G
tag: ['深度优先搜索 DFS', '生成树', '进制']
---

# Xor-MST

## 题目描述

You are given a complete undirected graph with $ n $ vertices. A number $ a_{i} $ is assigned to each vertex, and the weight of an edge between vertices $ i $ and $ j $ is equal to $ a_{i}xora_{j} $ .

Calculate the weight of the minimum spanning tree in this graph.

## 输入格式

The first line contains $ n $ ( $ 1<=n<=200000 $ ) — the number of vertices in the graph.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 0<=a_{i}<2^{30} $ ) — the numbers assigned to the vertices.

## 输出格式

Print one number — the weight of the minimum spanning tree in the graph.

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4
1 2 3 4

```

### 输出

```
8

```



---

---
title: "Substrings in a String"
layout: "post"
diff: 省选/NOI-
pid: CF914F
tag: ['进制', 'KMP 算法']
---

# Substrings in a String

## 题目描述

Given a string $ s $ , process $ q $ queries, each having one of the following forms:

- $ 1ic $ — Change the $ i $ -th character in the string to $ c $ .
- $ 2lry $ — Consider the substring of $ s $ starting at position $ l $ and ending at position $ r $ . Output the number of times $ y $ occurs as a substring in it.

## 输入格式

The first line of the input contains the string $ s $ ( $ 1<=|s|<=10^{5} $ ) of lowercase English letters.

The second line contains an integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of queries to process.

The next $ q $ lines describe the queries and may have one of the following forms:

- $ 1ic $ ( $ 1<=i<=|s| $ )
- $ 2lry $ ( $ 1<=l<=r<=|s| $ )

 $ c $ is a lowercase English letter and $ y $ is a non-empty string consisting of only lowercase English letters.

The sum of $ |y| $ over all queries of second type is at most $ 10^{5} $ .

It is guaranteed that there is at least one query of second type.

All strings are $ 1 $ -indexed.

 $ |s| $ is the length of the string $ s $ .

## 输出格式

For each query of type $ 2 $ , output the required answer in a separate line.

## 说明/提示

Consider the first sample case. Initially, the string aba occurs $ 3 $ times in the range $ [1,7] $ . Note that two occurrences may overlap.

After the update, the string becomes ababcbaba and now aba occurs only once in the range $ [1,7] $ .

## 样例 #1

### 输入

```
ababababa
3
2 1 7 aba
1 5 c
2 1 7 aba

```

### 输出

```
3
1

```

## 样例 #2

### 输入

```
abcdcbc
5
2 1 7 bc
1 4 b
2 4 7 bc
1 2 a
2 1 4 aa

```

### 输出

```
2
2
1

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

