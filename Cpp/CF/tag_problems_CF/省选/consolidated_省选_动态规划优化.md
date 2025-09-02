---
title: "Lanterns"
layout: "post"
diff: 省选/NOI-
pid: CF1476F
tag: ['动态规划优化']
---

# Lanterns

## 题目描述

有 $n$ 个灯笼拍成一排，第 $i$ 个灯笼具有 $p_i$ 的亮度。每个灯笼要么朝向左，照亮左边编号为 $[i - p_i,i - 1]$ 的灯笼，要么朝向右，照亮右边编号为 $[i + 1, i + p_i]$ 的灯笼。

寻找一种方案，为所有的灯笼确定朝向，使得每一个灯笼被至少一个其他灯笼照亮。

## 输入格式

第一行一个正整数表示数据组数 $t$。

每组数据包含两行。第一行为一个正整数 $n$，表示灯笼的个数。

第二行 $n$ 个整数 $p_i$，表示各个灯笼的亮度。

## 输出格式

对于每组数据，如果存在方案，在第一行输出字符串 $\texttt{YES}$，并在下一行给出一个长度为 $n$ 的仅由 $\texttt L$ 和 $\texttt R$ 组成的字符串，描述灯笼的方向。多解输出任意解。无解输出 $\texttt{NO}$。

## 说明/提示

$1\le t \le 1\times 10^4$。对于每组数据，有 $2\le n\le 3\times 10^5,0\le p_i\le n$。同一个测试点内保证 $\sum n\le 3\times 10^5$。

## 样例 #1

### 输入

```
4
8
0 0 3 1 1 1 1 2
2
1 1
2
2 2
2
0 1
```

### 输出

```
YES
RRLLLLRL
YES
RL
YES
RL
NO
```



---

---
title: "Serious Business"
layout: "post"
diff: 省选/NOI-
pid: CF1648D
tag: ['动态规划 DP', '线段树', '动态规划优化']
---

# Serious Business

## 题目描述

Dima is taking part in a show organized by his friend Peter. In this show Dima is required to cross a $ 3 \times n $ rectangular field. Rows are numbered from $ 1 $ to $ 3 $ and columns are numbered from $ 1 $ to $ n $ .

The cell in the intersection of the $ i $ -th row and the $ j $ -th column of the field contains an integer $ a_{i,j} $ . Initially Dima's score equals zero, and whenever Dima reaches a cell in the row $ i $ and the column $ j $ , his score changes by $ a_{i,j} $ . Note that the score can become negative.

Initially all cells in the first and the third row are marked as available, and all cells in the second row are marked as unavailable. However, Peter offered Dima some help: there are $ q $ special offers in the show, the $ i $ -th special offer allows Dima to mark cells in the second row between $ l_i $ and $ r_i $ as available, though Dima's score reduces by $ k_i $ whenever he accepts a special offer. Dima is allowed to use as many special offers as he wants, and might mark the same cell as available multiple times.

Dima starts his journey in the cell $ (1, 1) $ and would like to reach the cell $ (3, n) $ . He can move either down to the next row or right to the next column (meaning he could increase the current row or column by 1), thus making $ n + 1 $ moves in total, out of which exactly $ n - 1 $ would be horizontal and $ 2 $ would be vertical.

Peter promised Dima to pay him based on his final score, so the sum of all numbers of all visited cells minus the cost of all special offers used. Please help Dima to maximize his final score.

## 输入格式

The first input line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 500\,000 $ ) — the number of columns in the field and the number of special offers.

The next three lines describe the field, $ i $ -th of them contains $ n $ integers $ a_{i1} $ , $ a_{i2} $ , ..., $ a_{in} $ ( $ -10^9 \le a_{ij} \le 10^9) $ — the values in the $ i $ -th row.

The next $ q $ lines describe special offers: the $ i $ -th offer is described by 3 integers $ l_i $ , $ r_i $ and $ k_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1\leq k_i\leq 10^9 $ ) — the segment that becomes unblocked and the cost of this special offer.

## 输出格式

Output one integer — the maximum final score Dima can achieve.

## 说明/提示

In the first example, it is optimal to use Peter's second offer of $ 4 $ rubles and go through the cells $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ , $ (3, 3) $ , $ (3, 4) $ , earning $ 1 + 0 + 2 + 9 + 4 + 1 - 4 = 13 $ rubles in total.

In the second example, it is optimal to use Peter's second and third offers of $ 2 $ and $ 3 $ rubles, respectively, and go through the cells $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (3, 4) $ , $ (3, 5) $ , earning $ -20 + 1 + 3 + 3 + 6 + 6 + 2 - 2 - 3= -4 $ rubles.

## 样例 #1

### 输入

```
4 3
1 0 2 -1
-3 1 9 2
3 2 4 1
1 2 5
2 3 4
1 4 14
```

### 输出

```
13
```

## 样例 #2

### 输入

```
5 4
-20 -10 -11 -10 1
1 3 3 6 3
14 -20 3 6 2
1 5 13
1 2 2
3 5 3
2 3 1
```

### 输出

```
-4
```



---

---
title: "Speedbreaker Counting (Medium Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2018F2
tag: ['区间 DP', '动态规划优化', '容斥原理']
---

# Speedbreaker Counting (Medium Version)

## 题目描述

[DRG - Limbo](https://soundcloud.com/drg72711/limbo)

⠀



This is the medium version of the problem. In the three versions, the constraints on $ n $ and the time limit are different. You can make hacks only if all the versions of the problem are solved.

This is the statement of Problem D1B:

- There are $ n $ cities in a row, numbered $ 1, 2, \ldots, n $ left to right.
  - At time $ 1 $ , you conquer exactly one city, called the starting city.
  - At time $ 2, 3, \ldots, n $ , you can choose a city adjacent to the ones conquered so far and conquer it.
  
  You win if, for each $ i $ , you conquer city $ i $ at a time no later than $ a_i $ . A winning strategy may or may not exist, also depending on the starting city. How many starting cities allow you to win?

For each $ 0 \leq k \leq n $ , count the number of arrays of positive integers $ a_1, a_2, \ldots, a_n $ such that

- $ 1 \leq a_i \leq n $ for each $ 1 \leq i \leq n $ ;
- the answer to Problem D1B is $ k $ .

The answer can be very large, so you have to calculate it modulo a given prime $ p $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ n $ , $ p $ ( $ 1 \le n \le 500 $ , $ 10^8 \leq p \leq 10^9 $ , $ p $ is prime) — the number of cities and the modulo.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output $ n+1 $ integers: the $ i $ -th integer should be the number of arrays that satisfy the conditions for $ k = i-1 $ .

## 说明/提示

In the first test case,

- arrays with $ 1 $ good starting city: $ [1] $ .

In the second test case,

- arrays with $ 0 $ good starting cities: $ [1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2] $ , $ [2, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2] $ .

In the third test case,

- arrays with $ 0 $ good starting cities: $ [1, 1, 1] $ , $ [1, 1, 2] $ , $ [1, 1, 3] $ , $ [1, 2, 1] $ , $ [1, 2, 2] $ , $ [1, 3, 1] $ , $ [1, 3, 2] $ , $ [2, 1, 1] $ , $ [2, 1, 2] $ , $ [2, 2, 1] $ , $ [2, 2, 2] $ , $ [2, 3, 1] $ , $ [2, 3, 2] $ , $ [3, 1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2, 3] $ , $ [1, 3, 3] $ , $ [2, 1, 3] $ , $ [3, 1, 2] $ , $ [3, 1, 3] $ , $ [3, 2, 1] $ , $ [3, 3, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2, 3] $ , $ [2, 3, 3] $ , $ [3, 2, 2] $ , $ [3, 3, 2] $ ;
- arrays with $ 3 $ good starting cities: $ [3, 2, 3] $ , $ [3, 3, 3] $ .

## 样例 #1

### 输入

```
11
1 998244353
2 998244353
3 998244353
4 998244353
5 998244353
6 998244353
7 998244353
8 998244353
9 998244353
10 102275857
10 999662017
```

### 输出

```
0 1 
1 2 1 
14 7 4 2 
183 34 19 16 4 
2624 209 112 120 48 12 
42605 1546 793 992 468 216 36 
785910 13327 6556 9190 4672 2880 864 144 
16382863 130922 61939 94992 50100 36960 14256 4608 576 
382823936 1441729 657784 1086596 583344 488700 216000 96480 23040 2880 
20300780 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400 
944100756 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400
```



---

---
title: "Speedbreaker Counting (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2018F3
tag: ['区间 DP', '动态规划优化', '容斥原理']
---

# Speedbreaker Counting (Hard Version)

## 题目描述

[DRG - Limbo](https://soundcloud.com/drg72711/limbo)

⠀



This is the hard version of the problem. In the three versions, the constraints on $ n $ and the time limit are different. You can make hacks only if all the versions of the problem are solved.

This is the statement of Problem D1B:

- There are $ n $ cities in a row, numbered $ 1, 2, \ldots, n $ left to right.
  - At time $ 1 $ , you conquer exactly one city, called the starting city.
  - At time $ 2, 3, \ldots, n $ , you can choose a city adjacent to the ones conquered so far and conquer it.
  
  You win if, for each $ i $ , you conquer city $ i $ at a time no later than $ a_i $ . A winning strategy may or may not exist, also depending on the starting city. How many starting cities allow you to win?

For each $ 0 \leq k \leq n $ , count the number of arrays of positive integers $ a_1, a_2, \ldots, a_n $ such that

- $ 1 \leq a_i \leq n $ for each $ 1 \leq i \leq n $ ;
- the answer to Problem D1B is $ k $ .

The answer can be very large, so you have to calculate it modulo a given prime $ p $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 3000 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ n $ , $ p $ ( $ 1 \le n \le 3000 $ , $ 10^8 \leq p \leq 10^9 $ , $ p $ is prime) — the number of cities and the modulo.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3000 $ .

## 输出格式

For each test case, output $ n+1 $ integers: the $ i $ -th integer should be the number of arrays that satisfy the conditions for $ k = i-1 $ .

## 说明/提示

In the first test case,

- arrays with $ 1 $ good starting city: $ [1] $ .

In the second test case,

- arrays with $ 0 $ good starting cities: $ [1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2] $ , $ [2, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2] $ .

In the third test case,

- arrays with $ 0 $ good starting cities: $ [1, 1, 1] $ , $ [1, 1, 2] $ , $ [1, 1, 3] $ , $ [1, 2, 1] $ , $ [1, 2, 2] $ , $ [1, 3, 1] $ , $ [1, 3, 2] $ , $ [2, 1, 1] $ , $ [2, 1, 2] $ , $ [2, 2, 1] $ , $ [2, 2, 2] $ , $ [2, 3, 1] $ , $ [2, 3, 2] $ , $ [3, 1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2, 3] $ , $ [1, 3, 3] $ , $ [2, 1, 3] $ , $ [3, 1, 2] $ , $ [3, 1, 3] $ , $ [3, 2, 1] $ , $ [3, 3, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2, 3] $ , $ [2, 3, 3] $ , $ [3, 2, 2] $ , $ [3, 3, 2] $ ;
- arrays with $ 3 $ good starting cities: $ [3, 2, 3] $ , $ [3, 3, 3] $ .

## 样例 #1

### 输入

```
11
1 998244353
2 998244353
3 998244353
4 998244353
5 998244353
6 998244353
7 998244353
8 998244353
9 998244353
10 102275857
10 999662017
```

### 输出

```
0 1 
1 2 1 
14 7 4 2 
183 34 19 16 4 
2624 209 112 120 48 12 
42605 1546 793 992 468 216 36 
785910 13327 6556 9190 4672 2880 864 144 
16382863 130922 61939 94992 50100 36960 14256 4608 576 
382823936 1441729 657784 1086596 583344 488700 216000 96480 23040 2880 
20300780 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400 
944100756 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400
```



---

---
title: "Divide OR Conquer"
layout: "post"
diff: 省选/NOI-
pid: CF2038D
tag: ['动态规划 DP', '树状数组', '动态规划优化']
---

# Divide OR Conquer

## 题目描述

You are given an array $ [a_1, a_2, \ldots a_n] $ consisting of integers between $ 0 $ and $ 10^9 $ . You have to split this array into several segments (possibly one) in such a way that each element belongs to exactly one segment.

Let the first segment be the array $ [a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}] $ , the second segment be $ [a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}] $ , ..., the last segment be $ [a_{l_k}, a_{l_k+ 1}, \ldots, a_{r_k}] $ . Since every element should belong to exactly one array, $ l_1 = 1 $ , $ r_k = n $ , and $ r_i + 1 = l_{i+1} $ for each $ i $ from $ 1 $ to $ k-1 $ . The split should meet the following condition: $ f([a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}]) \le f([a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}]) \le \dots \le f([a_{l_k}, a_{l_k+1}, \ldots, a_{r_k}]) $ , where $ f(a) $ is the bitwise OR of all elements of the array $ a $ .

Calculate the number of ways to split the array, and print it modulo $ 998\,244\,353 $ . Two ways are considered different if the sequences $ [l_1, r_1, l_2, r_2, \ldots, l_k, r_k] $ denoting the splits are different.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10 ^9 $ ) — the elements of the given array.

## 输出格式

Print one integer — the number of ways to split the array, taken modulo $ 998\,244\,353 $ .

## 说明/提示

In the first two examples, every way to split the array is valid.

In the third example, there are three valid ways to split the array:

- $ k = 3 $ ; $ l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 2, l_3 = 3, r_3 = 3 $ ; the resulting arrays are $ [3] $ , $ [4] $ , $ [6] $ , and $ 3 \le 4 \le 6 $ ;
- $ k = 2 $ ; $ l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 3 $ ; the resulting arrays are $ [3] $ and $ [4, 6] $ , and $ 3 \le 6 $ ;
- $ k = 1 $ ; $ l_1 = 1, r_1 = 3 $ ; there will be only one array: $ [3, 4, 6] $ .

If you split the array into two arrays $ [3, 4] $ and $ [6] $ , the bitwise OR of the first array is $ 7 $ , and the bitwise OR of the second array is $ 6 $ ; $ 7 > 6 $ , so this way to split the array is invalid.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1000 1000 1000 1000 1000
```

### 输出

```
16
```

## 样例 #3

### 输入

```
3
3 4 6
```

### 输出

```
3
```



---

