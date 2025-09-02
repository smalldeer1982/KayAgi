---
title: "One Occurrence"
layout: "post"
diff: 提高+/省选-
pid: CF1000F
tag: ['莫队', '线段树']
---

# One Occurrence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and $ q $ queries to it. $ i $ -th query is denoted by two integers $ l_i $ and $ r_i $ . For each query, you have to find any integer that occurs exactly once in the subarray of $ a $ from index $ l_i $ to index $ r_i $ (a subarray is a contiguous subsegment of an array). For example, if $ a = [1, 1, 2, 3, 2, 4] $ , then for query $ (l_i = 2, r_i = 6) $ the subarray we are interested in is $ [1, 2, 3, 2, 4] $ , and possible answers are $ 1 $ , $ 3 $ and $ 4 $ ; for query $ (l_i = 1, r_i = 2) $ the subarray we are interested in is $ [1, 1] $ , and there is no such element that occurs exactly once.

Can you answer all of the queries?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 5 \cdot 10^5 $ ).

The third line contains one integer $ q $ ( $ 1 \le q \le 5 \cdot 10^5 $ ).

Then $ q $ lines follow, $ i $ -th line containing two integers $ l_i $ and $ r_i $ representing $ i $ -th query ( $ 1 \le l_i \le r_i \le n $ ).

## 输出格式

Answer the queries as follows:

If there is no integer such that it occurs in the subarray from index $ l_i $ to index $ r_i $ exactly once, print $ 0 $ . Otherwise print any such integer.

## 样例 #1

### 输入

```
6
1 1 2 3 2 4
2
2 6
1 2

```

### 输出

```
4
0

```



---

---
title: "Robin Hood Archery"
layout: "post"
diff: 提高+/省选-
pid: CF2014H
tag: ['莫队', '哈希 hashing']
---

# Robin Hood Archery

## 题目描述

在这种时候，射箭总是一天中的主要运动，因为诺丁汉郡的自耕农是整个快乐的英格兰最好的长弓手，但今年郡长犹豫了……



诺丁汉郡长组织了一场射箭比赛。这是最后一轮，罗宾汉对阵警长!

编号为$ 1 $ ～ $ n $的行中有$ n $个目标。当玩家射击目标$ i $时，他们的得分增加$ a_i $，目标$ i $被摧毁。游戏由回合组成，玩家轮流轮到谁。罗宾汉总是先开始游戏，然后是警长等等。游戏继续进行，直到所有目标被摧毁。两名球员都以得分$ 0 $开始。

在游戏结束时，得分最多的玩家获胜，而另一名玩家输了。如果双方得分相同，则为平局，没有人赢也没有人输。在每个回合中，玩家可以射击任何之前没有射击过的目标。两种游戏都是为了获得尽可能多的分数。

诺丁汉郡长怀疑他可能会输掉比赛!不能这样，你必须帮助警长。Sheriff将提出$ q $查询，每个查询指定$ l $和$ r $。这意味着游戏将只与目标$ l, l+1, \dots, r $一起玩，因为其他目标将在游戏开始前被Sheriff删除。

对于每个查询$ l $, $ r $，在只考虑目标$ l, l+1, \dots, r $的情况下，确定警长是否不会输掉比赛。

## 输入格式

输入的第一行包含一个整数$ t $ ($ 1 \le t \le 10^4 $)——测试用例的数量。

每个测试用例的第一行包含两个整数$ n $、$ q $ ($ 1 \le n,q \le 2\cdot10^5 $)——目标的数量和Sheriff将提出的查询的数量。

每个测试用例的第二行包含$ n $整数$ a_1, a_2, \ldots, a_n $ ($ 1 \le a_i \le 10^6 $)—达到每个目标的点。

然后$ q $行，每一行有两个整数$ l $和$ r $ ($ 1 \le l \le r \le n $)——每个查询要考虑的目标范围。

可以保证所有测试用例中$ n $和$ q $的总和不超过$ 2 \cdot 10^5 $。

## 输出格式

对于每个查询，如果警长在只考虑目标$ l, l+1, \dots, r $时没有输掉比赛，则输出“YES”，否则输出“NO”。

您可以在任何情况下输出答案(大小写不敏感)。例如，字符串“yEs”、“yEs”、“yEs”和“yEs”将被识别为“YES”。

## 样例 #1

### 输入

```
2
3 3
1 2 2
1 2
1 3
2 3
5 3
2 1 2 1 1
1 2
1 3
4 5
```

### 输出

```
NO
NO
YES
NO
NO
YES
```



---

---
title: "XOR and Favorite Number"
layout: "post"
diff: 提高+/省选-
pid: CF617E
tag: ['莫队']
---

# XOR and Favorite Number

## 题目描述

Bob has a favorite number $ k $ and $ a_{i} $ of length $ n $ . Now he asks you to answer $ m $ queries. Each query is given by a pair $ l_{i} $ and $ r_{i} $ and asks you to count the number of pairs of integers $ i $ and $ j $ , such that $ l<=i<=j<=r $ and the xor of the numbers $ a_{i},a_{i+1},...,a_{j} $ is equal to $ k $ .

## 输入格式

The first line of the input contains integers $ n $ , $ m $ and $ k $ ( $ 1<=n,m<=100000 $ , $ 0<=k<=1000000 $ ) — the length of the array, the number of queries and Bob's favorite number respectively.

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=1000000 $ ) — Bob's array.

Then $ m $ lines follow. The $ i $ -th line contains integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) — the parameters of the $ i $ -th query.

## 输出格式

Print $ m $ lines, answer the queries in the order they appear in the input.

## 说明/提示

In the first sample the suitable pairs of $ i $ and $ j $ for the first query are: ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 3 $ ), ( $ 3 $ , $ 6 $ ), ( $ 5 $ , $ 6 $ ), ( $ 6 $ , $ 6 $ ). Not a single of these pairs is suitable for the second query.

In the second sample xor equals $ 1 $ for all subarrays of an odd length.

## 样例 #1

### 输入

```
6 2 3
1 2 1 1 0 3
1 6
3 5

```

### 输出

```
7
0

```

## 样例 #2

### 输入

```
5 3 1
1 1 1 1 1
1 5
2 4
1 3

```

### 输出

```
9
4
4

```



---

---
title: "Powerful array"
layout: "post"
diff: 提高+/省选-
pid: CF86D
tag: ['莫队', '枚举']
---

# Powerful array

## 题目描述

An array of positive integers $ a_{1},a_{2},...,a_{n} $ is given. Let us consider its arbitrary subarray $ a_{l},a_{l+1}...,a_{r} $ , where $ 1<=l<=r<=n $ . For every positive integer $ s $ denote by $ K_{s} $ the number of occurrences of $ s $ into the subarray. We call the power of the subarray the sum of products $ K_{s}·K_{s}·s $ for every positive integer $ s $ . The sum contains only finite number of nonzero summands as the number of different values in the array is indeed finite.

You should calculate the power of $ t $ given subarrays.

## 输入格式

First line contains two integers $ n $ and $ t $ ( $ 1<=n,t<=200000 $ ) — the array length and the number of queries correspondingly.

Second line contains $ n $ positive integers $ a_{i} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the array.

Next $ t $ lines contain two positive integers $ l $ , $ r $ ( $ 1<=l<=r<=n $ ) each — the indices of the left and the right ends of the corresponding subarray.

## 输出格式

Output $ t $ lines, the $ i $ -th line of the output should contain single positive integer — the power of the $ i $ -th query subarray.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preferred to use cout stream (also you may use %I64d).

## 说明/提示

Consider the following array (see the second sample) and its \[2, 7\] subarray (elements of the subarray are colored):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF86D/5e3c36b108711f9f95c3c3519472e9f583328f8b.png) Then $ K_{1}=3 $ , $ K_{2}=2 $ , $ K_{3}=1 $ , so the power is equal to $ 3^{2}·1+2^{2}·2+1^{2}·3=20 $ .

## 样例 #1

### 输入

```
3 2
1 2 1
1 2
1 3

```

### 输出

```
3
6

```

## 样例 #2

### 输入

```
8 3
1 1 2 2 1 3 1 1
2 7
1 6
2 7

```

### 输出

```
20
20
20

```



---

