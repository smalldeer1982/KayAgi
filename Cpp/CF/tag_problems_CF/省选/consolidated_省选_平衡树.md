---
title: "Top-Notch Insertions"
layout: "post"
diff: 省选/NOI-
pid: CF1558D
tag: ['线段树', '二分', '平衡树', '组合数学']
---

# Top-Notch Insertions

## 题目描述

Consider the insertion sort algorithm used to sort an integer sequence $ [a_1, a_2, \ldots, a_n] $ of length $ n $ in non-decreasing order.

For each $ i $ in order from $ 2 $ to $ n $ , do the following. If $ a_i \ge a_{i-1} $ , do nothing and move on to the next value of $ i $ . Otherwise, find the smallest $ j $ such that $ a_i < a_j $ , shift the elements on positions from $ j $ to $ i-1 $ by one position to the right, and write down the initial value of $ a_i $ to position $ j $ . In this case we'll say that we performed an insertion of an element from position $ i $ to position $ j $ .

It can be noticed that after processing any $ i $ , the prefix of the sequence $ [a_1, a_2, \ldots, a_i] $ is sorted in non-decreasing order, therefore, the algorithm indeed sorts any sequence.

For example, sorting $ [4, 5, 3, 1, 3] $ proceeds as follows:

- $ i = 2 $ : $ a_2 \ge a_1 $ , do nothing;
- $ i = 3 $ : $ j = 1 $ , insert from position $ 3 $ to position $ 1 $ : $ [3, 4, 5, 1, 3] $ ;
- $ i = 4 $ : $ j = 1 $ , insert from position $ 4 $ to position $ 1 $ : $ [1, 3, 4, 5, 3] $ ;
- $ i = 5 $ : $ j = 3 $ , insert from position $ 5 $ to position $ 3 $ : $ [1, 3, 3, 4, 5] $ .

You are given an integer $ n $ and a list of $ m $ integer pairs $ (x_i, y_i) $ . We are interested in sequences such that if you sort them using the above algorithm, exactly $ m $ insertions will be performed: first from position $ x_1 $ to position $ y_1 $ , then from position $ x_2 $ to position $ y_2 $ , ..., finally, from position $ x_m $ to position $ y_m $ .

How many sequences of length $ n $ consisting of (not necessarily distinct) integers between $ 1 $ and $ n $ , inclusive, satisfy the above condition? Print this number modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ 0 \le m < n $ ) — the length of the sequence and the number of insertions.

The $ i $ -th of the following $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 2 \le x_1 < x_2 < \ldots < x_m \le n $ ; $ 1 \le y_i < x_i $ ). These lines describe the sequence of insertions in chronological order.

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Note that there is no constraint on the sum of $ n $ of the same kind.

## 输出格式

For each test case, print the number of sequences of length $ n $ consisting of integers from $ 1 $ to $ n $ such that sorting them with the described algorithm produces the given sequence of insertions, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the algorithm performs no insertions — therefore, the initial sequence is already sorted in non-decreasing order. There are $ 10 $ such sequences: $ [1, 1, 1], [1, 1, 2], [1, 1, 3], [1, 2, 2], [1, 2, 3], [1, 3, 3], [2, 2, 2], [2, 2, 3], [2, 3, 3], [3, 3, 3] $ .

In the second test case, the only sequence satisfying the conditions is $ [3, 2, 1] $ .

In the third test case, $ [4, 5, 3, 1, 3] $ is one of the sought sequences.

## 样例 #1

### 输入

```
3
3 0
3 2
2 1
3 1
5 3
3 1
4 1
5 3
```

### 输出

```
10
1
21
```



---

---
title: "Two Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF213E
tag: ['线段树', '平衡树', '枚举', '哈希 hashing']
---

# Two Permutations

## 题目描述

Rubik is very keen on number permutations.

A permutation $ a $ with length $ n $ is a sequence, consisting of $ n $ different numbers from 1 to $ n $ . Element number $ i $ $ (1<=i<=n) $ of this permutation will be denoted as $ a_{i} $ .

Furik decided to make a present to Rubik and came up with a new problem on permutations. Furik tells Rubik two number permutations: permutation $ a $ with length $ n $ and permutation $ b $ with length $ m $ . Rubik must give an answer to the problem: how many distinct integers $ d $ exist, such that sequence $ c $ $ (c_{1}=a_{1}+d,c_{2}=a_{2}+d,...,c_{n}=a_{n}+d) $ of length $ n $ is a subsequence of $ b $ .

Sequence $ a $ is a subsequence of sequence $ b $ , if there are such indices $ i_{1},i_{2},...,i_{n} $ $ (1<=i_{1}&lt;i_{2}&lt;...&lt;i_{n}<=m) $ , that $ a_{1}=b_{i1} $ , $ a_{2}=b_{i2} $ , $ ... $ , $ a_{n}=b_{in} $ , where $ n $ is the length of sequence $ a $ , and $ m $ is the length of sequence $ b $ .

You are given permutations $ a $ and $ b $ , help Rubik solve the given problem.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=m<=200000) $ — the sizes of the given permutations. The second line contains $ n $ distinct integers — permutation $ a $ , the third line contains $ m $ distinct integers — permutation $ b $ . Numbers on the lines are separated by spaces.

## 输出格式

On a single line print the answer to the problem.

## 样例 #1

### 输入

```
1 1
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1 2
1
2 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 3
2 3 1
1 2 3

```

### 输出

```
0

```



---

---
title: "Polycarp's Masterpiece"
layout: "post"
diff: 省选/NOI-
pid: CF589C
tag: ['字符串', '平衡树', '可持久化']
---

# Polycarp's Masterpiece

## 题目描述

Inspired by success of Joanne Rowling and her fantasy series of Harry Potter, Polycarp decided to create his own masterpiece. He has already picked a name for his future bestseller — string $ s $ .

Polycarp faced a number of difficulties while he was working on the main story of his book so he decided to become Malevich in a literature and create his own "Black Square".

Chapters of his masterpiece were written by Polycarp in $ n $ days. He started from writing down the string $ s $ . Every day (during the following $ n $ days) he did the following procedure: on the $ i $ -th day he added to the right of current text $ t $ its $ k_{i} $ -th circular shift. It means that every day content of his masterpiece doubled in size.

Circular shift of a string $ r $ is defined as a string resulted after movement of the last character of $ r $ to the first position in the string. As an example: circular shift of «masterpiece» is «emasterpiec». The $ i $ -th circular shift of a string $ r $ is defined as a string resulted after applying $ i $ subsequent circular shifts of the string $ r $ (e.g., the third circular shift of «masterpiece» is «ecemasterpi»).

After $ n $ days of tedious work Polycarp managed to write a very long text deserving the efforts made. However, text of his masterpiece was so long that it was nearly impossible to do any analysis of its content.

Help Polycarp to answer $ m $ requests about his masterpiece: for the $ j $ -th request you will need to find how many times a letter $ c_{j} $ is contained in a substring of his masterpiece starting from position $ l_{j} $ and ending at $ r_{j} $ inclusively.

## 输入格式

The first line contains a name of the masterpiece — string $ s $ . The string $ s $ contains only lowercase latin letters and its length is between 1 and 100 inclusively.

The second line contains a pair of integer numbers $ n $ and $ m $ $ (1<=n<=10^{5},1<=m<=10^{5}) $ — a number of days Polycarp worked on his masterpiece and a number of requests you need to answer for the text respectively.

The next line consists of $ n $ integer numbers $ k_{i} $ $ (0<=k_{i}<=100) $ — circular shifts used during $ n $ days of work.

Following $ m $ lines contains two integer numbers $ l_{j},r_{j} $ and a lowercase latin letter $ c_{j} $ each — requests description. For each request you need to count number of times letter $ c_{j} $ is contained in a substring of the masterpiece from position $ l_{j} $ to $ r_{j} $ inclusively. Positions are numerated starting from $ 1 $ . It is guaranteed that $ 1<=l_{j}<=r_{j}<=10^{18} $ and both $ l_{j} $ and $ r_{j} $ do not exceed length of the masterpiece.

## 输出格式

Output should contain $ m $ lines, where the $ j $ -th line contains the answer on the $ j $ -th request.

## 样例 #1

### 输入

```
masterpiece
1 3
3
1 22 m
9 14 e
8 15 p

```

### 输出

```
2
4
0

```

## 样例 #2

### 输入

```
polycarp
1 2
0
2 15 p
1 16 p

```

### 输出

```
2
4

```



---

---
title: "T-Shirts"
layout: "post"
diff: 省选/NOI-
pid: CF702F
tag: ['平衡树']
---

# T-Shirts

## 题目描述

The big consignment of t-shirts goes on sale in the shop before the beginning of the spring. In all $ n $ types of t-shirts go on sale. The t-shirt of the $ i $ -th type has two integer parameters — $ c_{i} $ and $ q_{i} $ , where $ c_{i} $ — is the price of the $ i $ -th type t-shirt, $ q_{i} $ — is the quality of the $ i $ -th type t-shirt. It should be assumed that the unlimited number of t-shirts of each type goes on sale in the shop, but in general the quality is not concerned with the price.

As predicted, $ k $ customers will come to the shop within the next month, the $ j $ -th customer will get ready to spend up to $ b_{j} $ on buying t-shirts.

All customers have the same strategy. First of all, the customer wants to buy the maximum possible number of the highest quality t-shirts, then to buy the maximum possible number of the highest quality t-shirts from residuary t-shirts and so on. At the same time among several same quality t-shirts the customer will buy one that is cheaper. The customers don't like the same t-shirts, so each customer will not buy more than one t-shirt of one type.

Determine the number of t-shirts which each customer will buy, if they use the described strategy. All customers act independently from each other, and the purchase of one does not affect the purchase of another.

## 输入格式

The first line contains the positive integer $ n $ ( $ 1<=n<=2·10^{5} $ ) — the number of t-shirt types.

Each of the following $ n $ lines contains two integers $ c_{i} $ and $ q_{i} $ ( $ 1<=c_{i},q_{i}<=10^{9} $ ) — the price and the quality of the $ i $ -th type t-shirt.

The next line contains the positive integer $ k $ ( $ 1<=k<=2·10^{5} $ ) — the number of the customers.

The next line contains $ k $ positive integers $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{j}<=10^{9} $ ), where the $ j $ -th number is equal to the sum, which the $ j $ -th customer gets ready to spend on t-shirts.

## 输出格式

The first line of the input data should contain the sequence of $ k $ integers, where the $ i $ -th number should be equal to the number of t-shirts, which the $ i $ -th customer will buy.

## 说明/提示

In the first example the first customer will buy the t-shirt of the second type, then the t-shirt of the first type. He will spend 10 and will not be able to buy the t-shirt of the third type because it costs 4, and the customer will owe only 3. The second customer will buy all three t-shirts (at first, the t-shirt of the second type, then the t-shirt of the first type, and then the t-shirt of the third type). He will spend all money on it.

## 样例 #1

### 输入

```
3
7 5
3 5
4 3
2
13 14

```

### 输出

```
2 3 

```

## 样例 #2

### 输入

```
2
100 500
50 499
4
50 200 150 100

```

### 输出

```
1 2 2 1 

```



---

---
title: "Hitchhiking in the Baltic States"
layout: "post"
diff: 省选/NOI-
pid: CF809D
tag: ['动态规划 DP', '平衡树', '枚举']
---

# Hitchhiking in the Baltic States

## 题目描述

Leha and Noora decided to go on a trip in the Baltic States. As you know from the previous problem, Leha has lost his car on the parking of the restaurant. Unfortunately, requests to the watchman didn't helped hacker find the car, so friends decided to go hitchhiking.

In total, they intended to visit $ n $ towns. However it turned out that sights in $ i $ -th town are open for visitors only on days from $ l_{i} $ to $ r_{i} $ .

What to do? Leha proposed to choose for each town $ i $ a day, when they will visit this town, i.e any integer $ x_{i} $ in interval $ [l_{i},r_{i}] $ . After that Noora choses some subsequence of towns $ id_{1},id_{2},...,id_{k} $ , which friends are going to visit, that at first they are strictly increasing, i.e $ id_{i}<id_{i+1} $ is for all integers $ i $ from $ 1 $ to $ k-1 $ , but also the dates of the friends visits are strictly increasing, i.e $ x_{idi}<x_{idi+1} $ is true for all integers $ i $ from $ 1 $ to $ k-1 $ .

Please help Leha and Noora in choosing such $ x_{i} $ for each town $ i $ , and such subsequence of towns $ id_{1},id_{2},...,id_{k} $ , so that friends can visit maximal number of towns.

You may assume, that Leha and Noora can start the trip any day.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=3·10^{5} $ ) denoting the number of towns Leha and Noora intended to visit.

Each line $ i $ of the $ n $ subsequent lines contains two integers $ l_{i} $ , $ r_{i} $ $ (1<=l_{i}<=r_{i}<=10^{9}) $ , denoting that sights in $ i $ -th town are open for visitors on any day ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809D/67e7c15a830b4bf2b41222394fc99591b0cfcff8.png).

## 输出格式

Print a single integer denoting the maximal number of towns, that Leha and Noora can visit.

## 说明/提示

Consider the first example.

Let's take this plan: let's visit the sight in the second town on the first day, in the third town on the third day and in the fifth town on the fourth. That's would be the optimal answer.

## 样例 #1

### 输入

```
5
6 6
1 2
3 4
2 2
1 4

```

### 输出

```
3

```



---

