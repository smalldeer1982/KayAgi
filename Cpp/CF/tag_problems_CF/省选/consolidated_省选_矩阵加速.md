---
title: "Lunar New Year and a Recursive Sequence"
layout: "post"
diff: 省选/NOI-
pid: CF1106F
tag: ['数学', '矩阵加速']
---

# Lunar New Year and a Recursive Sequence

## 题目描述

Lunar New Year is approaching, and Bob received a gift from his friend recently — a recursive sequence! He loves this sequence very much and wants to play with it.

Let $ f_1, f_2, \ldots, f_i, \ldots $ be an infinite sequence of positive integers. Bob knows that for $ i > k $ , $ f_i $ can be obtained by the following recursive equation:

 $ $$$f_i = \left(f_{i - 1} ^ {b_1} \cdot f_{i - 2} ^ {b_2} \cdot \cdots \cdot f_{i - k} ^ {b_k}\right) \bmod p, $ $ </p><p>which in short is</p><p> $ $ f_i = \left(\prod_{j = 1}^{k} f_{i - j}^{b_j}\right) \bmod p, $ $ </p><p>where  $ p = 998\\,244\\,353 $  (a widely-used prime),  $ b\_1, b\_2, \\ldots, b\_k $  are known integer constants, and  $ x \\bmod y $  denotes the remainder of  $ x $  divided by  $ y $ .</p><p>Bob lost the values of  $ f\_1, f\_2, \\ldots, f\_k $ , which is extremely troublesome – these are the basis of the sequence! Luckily, Bob remembers the first  $ k - 1 $  elements of the sequence:  $ f\_1 = f\_2 = \\ldots = f\_{k - 1} = 1 $  and the  $ n $ -th element:  $ f\_n = m $ . Please find any possible value of  $ f\_k$$$. If no solution exists, just tell Bob that it is impossible to recover his favorite sequence, regardless of Bob's sadness.

## 输入格式

The first line contains a positive integer $ k $ ( $ 1 \leq k \leq 100 $ ), denoting the length of the sequence $ b_1, b_2, \ldots, b_k $ .

The second line contains $ k $ positive integers $ b_1, b_2, \ldots, b_k $ ( $ 1 \leq b_i < p $ ).

The third line contains two positive integers $ n $ and $ m $ ( $ k < n \leq 10^9 $ , $ 1 \leq m < p $ ), which implies $ f_n = m $ .

## 输出格式

Output a possible value of $ f_k $ , where $ f_k $ is a positive integer satisfying $ 1 \leq f_k < p $ . If there are multiple answers, print any of them. If no such $ f_k $ makes $ f_n = m $ , output $ -1 $ instead.

It is easy to show that if there are some possible values of $ f_k $ , there must be at least one satisfying $ 1 \leq f_k < p $ .

## 说明/提示

In the first sample, we have $ f_4 = f_3^2 \cdot f_2^3 \cdot f_1^5 $ . Therefore, applying $ f_3 = 4 $ , we have $ f_4 = 16 $ . Note that there can be multiple answers.

In the third sample, applying $ f_7 = 1 $ makes $ f_{23333} = 1 $ .

In the fourth sample, no such $ f_1 $ makes $ f_{88888} = 66666 $ . Therefore, we output $ -1 $ instead.

## 样例 #1

### 输入

```
3
2 3 5
4 16

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5
4 7 1 5 6
7 14187219

```

### 输出

```
6

```

## 样例 #3

### 输入

```
8
2 3 5 6 1 7 9 10
23333 1

```

### 输出

```
1

```

## 样例 #4

### 输入

```
1
2
88888 66666

```

### 输出

```
-1

```

## 样例 #5

### 输入

```
3
998244352 998244352 998244352
4 2

```

### 输出

```
-1

```

## 样例 #6

### 输入

```
10
283 463 213 777 346 201 463 283 102 999
2333333 6263423

```

### 输出

```
382480067

```



---

---
title: "Trails (Hard)"
layout: "post"
diff: 省选/NOI-
pid: CF1970E3
tag: ['动态规划 DP', '矩阵加速']
---

# Trails (Hard)

## 题目描述

Harry Potter is hiking in the Alps surrounding Lake Geneva. In this area there are $ m $ cabins, numbered 1 to $ m $ . Each cabin is connected, with one or more trails, to a central meeting point next to the lake. Each trail is either short or long. Cabin $ i $ is connected with $ s_i $ short trails and $ l_i $ long trails to the lake.

Each day, Harry walks a trail from the cabin where he currently is to Lake Geneva, and then from there he walks a trail to any of the $ m $ cabins (including the one he started in). However, as he has to finish the hike in a day, at least one of the two trails has to be short.

How many possible combinations of trails can Harry take if he starts in cabin 1 and walks for $ n $ days?

Give the answer modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains the integers $ m $ and $ n $ .

The second line contains $ m $ integers, $ s_1, \dots, s_m $ , where $ s_i $ is the number of short trails between cabin $ i $ and Lake Geneva.

The third and last line contains $ m $ integers, $ l_1, \dots, l_m $ , where $ l_i $ is the number of long trails between cabin $ i $ and Lake Geneva.

We have the following constraints:

 $ 0 \le s_i, l_i \le 10^3 $ .

 $ 1 \le m \le 10^5 $ .

 $ 1 \le n \le 10^9 $ .

## 输出格式

The number of possible combinations of trails, modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
3 2
1 0 1
0 1 1
```

### 输出

```
18
```



---

---
title: "Jeff and Brackets"
layout: "post"
diff: 省选/NOI-
pid: CF351C
tag: ['动态规划 DP', '矩阵加速']
---

# Jeff and Brackets

## 题目描述

Jeff loves regular bracket sequences.

Today Jeff is going to take a piece of paper and write out the regular bracket sequence, consisting of $ nm $ brackets. Let's number all brackets of this sequence from $ 0 $ to $ nm $ - $ 1 $ from left to right. Jeff knows that he is going to spend $ a_{i\ mod\ n} $ liters of ink on the $ i $ -th bracket of the sequence if he paints it opened and $ b_{i\ mod\ n} $ liters if he paints it closed.

You've got sequences $ a $ , $ b $ and numbers $ n $ , $ m $ . What minimum amount of ink will Jeff need to paint a regular bracket sequence of length $ nm $ ?

Operation $ x\ mod\ y $ means taking the remainder after dividing number $ x $ by number $ y $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=20; 1<=m<=10^{7}; $ $ m $ is even). The next line contains $ n $ integers: $ a_{0} $ , $ a_{1} $ , $ ... $ , $ a_{n-1} $ $ (1<=a_{i}<=10) $ . The next line contains $ n $ integers: $ b_{0} $ , $ b_{1} $ , $ ... $ , $ b_{n-1} $ $ (1<=b_{i}<=10) $ . The numbers are separated by spaces.

## 输出格式

In a single line print the answer to the problem — the minimum required amount of ink in liters.

## 说明/提示

In the first test the optimal sequence is: $ ()()()()()() $ , the required number of ink liters is $ 12 $ .

## 样例 #1

### 输入

```
2 6
1 2
2 1

```

### 输出

```
12

```

## 样例 #2

### 输入

```
1 10000000
2
3

```

### 输出

```
25000000

```



---

