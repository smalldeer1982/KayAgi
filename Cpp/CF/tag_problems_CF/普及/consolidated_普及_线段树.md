---
title: "Iva & Pav"
layout: "post"
diff: 普及/提高-
pid: CF1878E
tag: ['线段树', '二分', 'ST 表']
---

# Iva & Pav

## 题目描述

Iva and Pav are a famous Serbian competitive programming couple. In Serbia, they call Pav "papuca" and that's why he will make all of Iva's wishes come true.

Iva gave Pav an array $ a $ of $ n $ elements.

Let's define $ f(l, r) = a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r $ (here $ \& $ denotes the [bitwise AND operation](http://tiny.cc/bitwise_and)).

Note that $ f(l, r) $ is not defined when $ l>r $ .

Iva also gave Pav $ q $ queries.

Each query consists of 2 numbers, $ k $ and $ l $ , and she wants Pav to find the largest index $ r $ ( $ l \le r \le n $ ), such that $ f(l, r) \ge k $ .

Pav wants to solve this problem fast because he doesn't want to upset Iva. He needs your help.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of array $ a $ .

The third line of each test case contains a single integer $ q $ ( $ 1 \le q \le 10^5 $ ) — the number of queries Iva gave Pav.

The next $ q $ lines of each test case contains two numbers, $ l $ and $ k $ ( $ 1 \le l \le n $ , $ 1 \le k \le 10^9 $ ) — the left bound for the subsegment, and the integer $ k $ described in statement.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Also, it is guaranteed that the sum of $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query output maximal index $ r $ ( $ l \le r \le n $ ) such that $ a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r \ \ge \ k $ .

If such $ r $ doesn't exist, output $ -1 $ .

## 说明/提示

In the first test case $ n=5 $ , and the array $ a = [15, 14, 17, 42, 34] $

The first query asks for the biggest index $ r $ such that the $ f(1, r) \ge 7 $ .

 $ f(1,1) = 15, \ f(1, 2) = 14, \ f(1,3)=0 \ f(1, 4)=0 \ f(1, 5)=0 $ , so $ r=2 $ is the answer.

The second query asks for $ f(2, r) \ge 15 $ . Since such $ r $ doesn't exist, the answer is $ -1 $ .

The third query asks for $ f(4, r) \ge 5 $ . $ f(4, 4) = 42, \ f(4, 5) = 34 $ , so $ r=5 $ is the answer.

In the second test case $ n=5 $ , and the array $ a= [7, 5, 3, 1, 7] $ .

For the first query, $ f(1, r) \ge 7 $ .

 $ f(1, 1)=7, \ f(1, 2)=5, \ f(1, 3) = 1, \ f(1,4) = 1, \ f(1, 5)=1 $ , so the answer to this query is $ 1 $ .

For the second query, $ f(5, r) \ge 7 $ .

 $ f(5, 5) = 7 $ , so the answer is $ 5 $ .

For the third query, $ f(2, r) \ge 3 $ .

 $ f(2, 2) = 5, \ f(2, 3) = 1, \ f(2, 4) = 1, \ f(2, 5) = 1 $ , so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
5
15 14 17 42 34
3
1 7
2 15
4 5
5
7 5 3 1 7
4
1 7
5 7
2 3
2 2
7
19 20 15 12 21 7 11
4
1 15
4 4
7 12
5 7
```

### 输出

```
2 -1 5 
1 5 2 2 
2 6 -1 5
```



---

---
title: "Pasha and String"
layout: "post"
diff: 普及/提高-
pid: CF525B
tag: ['字符串', '线段树']
---

# Pasha and String

## 题目描述

Pasha got a very beautiful string $ s $ for his birthday, the string consists of lowercase Latin letters. The letters in the string are numbered from 1 to $ |s| $ from left to right, where $ |s| $ is the length of the given string.

Pasha didn't like his present very much so he decided to change it. After his birthday Pasha spent $ m $ days performing the following transformations on his string — each day he chose integer $ a_{i} $ and reversed a piece of string (a segment) from position $ a_{i} $ to position $ |s|-a_{i}+1 $ . It is guaranteed that $ 2·a_{i}<=|s| $ .

You face the following task: determine what Pasha's string will look like after $ m $ days.

## 输入格式

The first line of the input contains Pasha's string $ s $ of length from $ 2 $ to $ 2·10^{5} $ characters, consisting of lowercase Latin letters.

The second line contains a single integer $ m $ ( $ 1<=m<=10^{5} $ ) — the number of days when Pasha changed his string.

The third line contains $ m $ space-separated elements $ a_{i} $ ( $ 1<=a_{i} $ ; $ 2·a_{i}<=|s| $ ) — the position from which Pasha started transforming the string on the $ i $ -th day.

## 输出格式

In the first line of the output print what Pasha's string $ s $ will look like after $ m $ days.

## 样例 #1

### 输入

```
abcdef
1
2

```

### 输出

```
aedcbf

```

## 样例 #2

### 输入

```
vwxyz
2
2 2

```

### 输出

```
vwxyz

```

## 样例 #3

### 输入

```
abcdef
3
1 2 3

```

### 输出

```
fbdcea

```



---

---
title: "Circular RMQ"
layout: "post"
diff: 普及/提高-
pid: CF52C
tag: ['线段树']
---

# Circular RMQ

## 题目描述

You are given circular array $ a_{0},a_{1},...,a_{n-1} $ . There are two types of operations with it:

- $ inc(lf,rg,v) $ — this operation increases each element on the segment $ [lf,rg] $ (inclusively) by $ v $ ;
- $ rmq(lf,rg) $ — this operation returns minimal value on the segment $ [lf,rg] $ (inclusively).

Assume segments to be circular, so if $ n=5 $ and $ lf=3,rg=1 $ , it means the index sequence: $ 3,4,0,1 $ .

Write program to process given sequence of operations.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=200000 $ ). The next line contains initial state of the array: $ a_{0},a_{1},...,a_{n-1} $ ( $ -10^{6}<=a_{i}<=10^{6} $ ), $ a_{i} $ are integer. The third line contains integer $ m $ ( $ 0<=m<=200000 $ ), $ m $ — the number of operartons. Next $ m $ lines contain one operation each. If line contains two integer $ lf,rg $ ( $ 0<=lf,rg<=n-1 $ ) it means $ rmq $ operation, it contains three integers $ lf,rg,v $ ( $ 0<=lf,rg<=n-1;-10^{6}<=v<=10^{6} $ ) — $ inc $ operation.

## 输出格式

For each $ rmq $ operation write result for it. Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cout (also you may use %I64d).

## 样例 #1

### 输入

```
4
1 2 3 4
4
3 0
3 0 -1
0 1
2 1

```

### 输出

```
1
0
0

```



---

---
title: "Bear and Blocks"
layout: "post"
diff: 普及/提高-
pid: CF573B
tag: ['递推', '线段树', '线性递推']
---

# Bear and Blocks

## 题目描述

Limak is a little bear who loves to play. Today he is playing by destroying block towers. He built $ n $ towers in a row. The $ i $ -th tower is made of $ h_{i} $ identical blocks. For clarification see picture for the first sample.

Limak will repeat the following operation till everything is destroyed.

Block is called internal if it has all four neighbors, i.e. it has each side (top, left, down and right) adjacent to other block or to the floor. Otherwise, block is boundary. In one operation Limak destroys all boundary blocks. His paws are very fast and he destroys all those blocks at the same time.

Limak is ready to start. You task is to count how many operations will it take him to destroy all towers.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=10^{5} $ ).

The second line contains $ n $ space-separated integers $ h_{1},h_{2},...,h_{n} $ ( $ 1<=h_{i}<=10^{9}) $ — sizes of towers.

## 输出格式

Print the number of operations needed to destroy all towers.

## 说明/提示

The picture below shows all three operations for the first sample test. Each time boundary blocks are marked with red color.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573B/256df13c1ef1192f2e98a72ff5ba9bb98f4ceade.png) After first operation there are four blocks left and only one remains after second operation. This last block is destroyed in third operation.

## 样例 #1

### 输入

```
6
2 1 4 6 2 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
3 3 3 1 3 3 3

```

### 输出

```
2

```



---

---
title: "Destroying Array"
layout: "post"
diff: 普及/提高-
pid: CF722C
tag: ['线段树', '并查集']
---

# Destroying Array

## 题目描述

给你一个由 $n$ 个非负整数组成的数列 $a_1$，$a_2$，$\cdots$，$a_n$。

你将要一个一个摧毁这个数列中的数。并且，现在给你一个由 $1$ 到 $n$ 组成的序列来告诉你每个数被摧毁的时间顺序。

每当一个元素被摧毁时，你需要找到这个当前数列中的未被摧毁的数组成的和最大的连续子序列，另外，如果当前剩余的序列是空的的话，最大和就是 $0$。

## 输入格式

第一行包含一个整数 $n (1\le n\le 100000)$ , 代表数列的长度。

第二行包含 $n$ 个整数 $a_1$，$a_2$，$\cdots$，$a_n$ $(0\le a_i\le 10^9)$。

第三行包含一个由 $1$ 到 $n$ 的整数组成的序列，代表数被摧毁的顺序。

## 输出格式

输出有 $n$ 行，第 $i$ 行包含一个整数 —— 在第 $i$ 个操作已经执行完之后，数列中连续的最大和。

## 说明/提示

第一个样例：

1.第三个数被删除了，现在的数列是 1 3 x 5 ，5由一个数5组成。

2.第四个数被删除了，现在的数列是 1 3 x x ，4由两个数1和3组成。

3.第一个数被删除了，现在的数列是 x 3 x x ，3由一个数3组成。

4.最后一个剩下的数被删除了，现在的数列中没有东西啦，所以答案是0呢！


感谢 @FangHaosb 提供的翻译

## 样例 #1

### 输入

```
4
1 3 2 5
3 4 1 2

```

### 输出

```
5
4
3
0

```

## 样例 #2

### 输入

```
5
1 2 3 4 5
4 2 3 5 1

```

### 输出

```
6
5
5
1
0

```

## 样例 #3

### 输入

```
8
5 5 4 4 6 6 5 5
5 2 8 7 1 3 4 6

```

### 输出

```
18
16
11
8
8
6
6
0

```



---

---
title: "Planning"
layout: "post"
diff: 普及/提高-
pid: CF853A
tag: ['贪心', '线段树', '排序']
---

# Planning

## 题目描述

Helen在大都会机场工作，她的任务是安排每天的航班起飞时刻。今天一共有n架飞机将要起飞，第i架飞机将在第i分钟起飞。

大都会机场是大都会最重要的交通枢纽，因此想要原封不动地按照起飞时刻表的时刻起飞是很困难的。今天的情况也是如此：由于技术原因，在今天一开始的k分钟内飞机不允许起飞，因此必须创建一个新的起飞时刻表。

所有的航班必须在第(k+1)分钟到第(k+n)分钟内(包括两端)起飞，而且每分钟仅能有一架飞机起飞。然而，航班起飞的先后顺序可以与最初的时刻表排好的顺序不同，重排的时刻表只有一个限制：飞机不能比它在初始时刻表中起飞的时刻还要早的时刻起飞(即：第i架飞机必须在第i分钟后或第i分钟时起飞)。

Helen知道第i架飞机起飞时刻每延误一分钟机场所需支付的额外花费ci是多少。帮助她找到额外花费最小的方案。

## 输入格式

输入数据的第一行包括两个整数n和k(1<=k<=n<=300000)。

第二行包括n个整数c1，c2，...，cn(1<=ci<=10^7).

## 输出格式

输出数据的第一行包括一个整数，表示最小额外花费。

第二行包括n个整数t1，t2，...，tn(k+1<=ti<=k+n)，ti表示第i架家航班起飞的时刻。如果同时存在多种方案，输出任意一种。

## 说明/提示

在样例中，如果Helen仅把每架飞机的起飞时刻都推迟2分钟，那么总额外花费是38。
但是，对于最佳结果来说，总额外花费为20。

感谢@radish布団  提供的翻译

## 样例 #1

### 输入

```
5 2
4 2 1 10 2

```

### 输出

```
20
3 6 7 4 5 

```



---

---
title: "A Twisty Movement"
layout: "post"
diff: 普及/提高-
pid: CF933A
tag: ['动态规划 DP', '线段树', '枚举', '前缀和']
---

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=2000) $ , denoting the length of the original sequence.

The second line contains $ n $ space-separated integers, describing the original sequence $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=2,i=1,2,...,n) $ .

## 输出格式

Print a single integer, which means the maximum possible length of the longest non-decreasing subsequence of the new sequence.

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1

```

### 输出

```
9

```



---

---
title: "Three displays"
layout: "post"
diff: 普及/提高-
pid: CF987C
tag: ['动态规划 DP', '线段树', '枚举']
---

# Three displays

## 题目描述

### 形式化题面

给定一个有两个性质 $s_i$ 和 $c_i$ 的数组，要求在其中选出三个数，满足：

 - $i<j<k$.
 - $s_i<s_j<s_k$.
 - $c_i+c_j+c_k$ 最小.

## 输入格式

第一行一个整数 $n$ 表示数组长度.

接下来一行 $n$ 个整数，表示 $s_i$.

接下来一行 $n$ 个整数，表示 $c_i$.

## 输出格式

一行一个整数，表示最小的 $c_i+c_j+c_k$

翻译 @[zymooll](/user/289296)

## 样例 #1

### 输入

```
5
2 4 5 4 10
40 30 20 10 40

```

### 输出

```
90

```

## 样例 #2

### 输入

```
3
100 101 100
2 4 5

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
10 13 11 14 15 12 13 13 18 13

```

### 输出

```
33

```



---

