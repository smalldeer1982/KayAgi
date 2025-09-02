---
title: "Satanic Panic"
layout: "post"
diff: 省选/NOI-
pid: CF1146H
tag: ['动态规划 DP', '计算几何', '区间 DP']
---

# Satanic Panic

## 题目描述

You are given a set of $ n $ points in a 2D plane. No three points are collinear.

A pentagram is a set of $ 5 $ points $ A,B,C,D,E $ that can be arranged as follows. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/f942ae06c7e29cb9bc6462315be09bb7d5b4c362.png) Note the length of the line segments don't matter, only that those particular intersections exist.

Count the number of ways to choose $ 5 $ points from the given set that form a pentagram.

## 输入格式

The first line contains an integer $ n $ ( $ 5 \leq n \leq 300 $ ) — the number of points.

Each of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ -10^6 \leq x_i,y_i \leq 10^6 $ ) — the coordinates of the $ i $ -th point. It is guaranteed that no three points are collinear.

## 输出格式

Print a single integer, the number of sets of $ 5 $ points that form a pentagram.

## 说明/提示

A picture of the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/ecb5db206846ce3b41c177fcaeaebe0ee2b1bb2a.png) A picture of the second sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/4f7f38f01a0904403461b302f8dc7d443ccc0e93.png) A picture of the third sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/d922b8e812b7b67b3a0bbbb474a47be87ee53781.png)

## 样例 #1

### 输入

```
5
0 0
0 2
2 0
2 2
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
0 0
4 0
0 4
4 4
2 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
10
841746 527518
595261 331297
-946901 129987
670374 -140388
-684770 309555
-302589 415564
-387435 613331
-624940 -95922
945847 -199224
24636 -565799

```

### 输出

```
85

```



---

---
title: "Replace on Segment"
layout: "post"
diff: 省选/NOI-
pid: CF1922F
tag: ['动态规划 DP', '区间 DP']
---

# Replace on Segment

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , where each element is an integer from $ 1 $ to $ x $ .

You can perform the following operation with it any number of times:

- choose three integers $ l $ , $ r $ and $ k $ such that $ 1 \le l \le r \le n $ , $ 1 \le k \le x $ and each element $ a_i $ such that $ l \le i \le r $ is different from $ k $ . Then, for each $ i \in [l, r] $ , replace $ a_i $ with $ k $ .

In other words, you choose a subsegment of the array and an integer from $ 1 $ to $ x $ which does not appear in that subsegment, and replace every element in the subsegment with that chosen integer.

Your goal is to make all elements in the array equal. What is the minimum number of operations that you have to perform?

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

Each test case consists of two lines:

- the first line contains two integers $ n $ and $ x $ ( $ 1 \le x \le n \le 100 $ );
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le x $ ).

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, print one integer — the minimum number of operations you have to perform.

## 样例 #1

### 输入

```
3
3 2
1 2 1
6 3
1 2 3 1 2 3
12 3
3 1 3 1 2 1 1 2 3 1 1 3
```

### 输出

```
1
2
2
```



---

---
title: "Interesting Problem (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1987F1
tag: ['区间 DP']
---

# Interesting Problem (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ n $ . You can make hacks only if both versions of the problem are solved.

You are given an array of integers $ a $ of length $ n $ .

In one operation, you will perform the following two-step process:

1. Choose an index $ i $ such that $ 1 \le i < |a| $ and $ a_i = i $ .
2. Remove $ a_i $ and $ a_{i+1} $ from the array and concatenate the remaining parts.

Find the maximum number of times that you can perform the operation above.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 100 $ .

## 输出格式

For each test case, output a single integer — the maximum number of times that you can perform the operation.

## 说明/提示

In the first test case, one possible optimal sequence of operations is $ [ 1, 5, \color{red}{3}, \color{red}{2}, 4 ] \rightarrow [\color{red}{1}, \color{red}{5}, 4] \rightarrow [4] $ .

In the third test case, one possible optimal sequence of operations is $ [1, \color{red}{2}, \color{red}{3}] \rightarrow [1] $ .

## 样例 #1

### 输入

```
6
5
1 5 3 2 4
8
2 1 3 4 5 6 7 8
3
1 2 3
4
1 2 4 4
5
4 4 1 3 5
1
1
```

### 输出

```
2
3
1
2
0
0
```



---

---
title: "Interesting Problem (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1987F2
tag: ['区间 DP']
---

# Interesting Problem (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ n $ . You can make hacks only if both versions of the problem are solved.

You are given an array of integers $ a $ of length $ n $ .

In one operation, you will perform the following two-step process:

1. Choose an index $ i $ such that $ 1 \le i < |a| $ and $ a_i = i $ .
2. Remove $ a_i $ and $ a_{i+1} $ from the array and concatenate the remaining parts.

Find the maximum number of times that you can perform the operation above.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 800 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 800 $ .

## 输出格式

For each test case, output a single integer — the maximum number of times that you can perform the operation.

## 说明/提示

In the first test case, one possible optimal sequence of operations is $ [ 1, 5, \color{red}{3}, \color{red}{2}, 4 ] \rightarrow [\color{red}{1}, \color{red}{5}, 4] \rightarrow [4] $ .

In the third test case, one possible optimal sequence of operations is $ [1, \color{red}{2}, \color{red}{3}] \rightarrow [1] $ .

## 样例 #1

### 输入

```
6
5
1 5 3 2 4
8
2 1 3 4 5 6 7 8
3
1 2 3
4
1 2 4 4
5
4 4 1 3 5
1
1
```

### 输出

```
2
3
1
2
0
0
```



---

---
title: "Speedbreaker Counting (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2018F1
tag: ['区间 DP', '容斥原理']
---

# Speedbreaker Counting (Easy Version)

## 题目描述

[DRG - Limbo](https://soundcloud.com/drg72711/limbo)

⠀



This is the easy version of the problem. In the three versions, the constraints on $ n $ and the time limit are different. You can make hacks only if all the versions of the problem are solved.

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

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 80 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ n $ , $ p $ ( $ 1 \le n \le 80 $ , $ 10^8 \leq p \leq 10^9 $ , $ p $ is prime) — the number of cities and the modulo.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 80 $ .

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

