---
title: "Partial Virtual Trees"
layout: "post"
diff: 省选/NOI-
pid: CF1707D
tag: ['数学', '树形 DP', '容斥原理']
---

# Partial Virtual Trees

## 题目描述

Kawashiro Nitori is a girl who loves competitive programming. One day she found a rooted tree consisting of $ n $ vertices. The root is vertex $ 1 $ . As an advanced problem setter, she quickly thought of a problem.

Kawashiro Nitori has a vertex set $ U=\{1,2,\ldots,n\} $ . She's going to play a game with the tree and the set. In each operation, she will choose a vertex set $ T $ , where $ T $ is a partial virtual tree of $ U $ , and change $ U $ into $ T $ .

A vertex set $ S_1 $ is a partial virtual tree of a vertex set $ S_2 $ , if $ S_1 $ is a subset of $ S_2 $ , $ S_1 \neq S_2 $ , and for all pairs of vertices $ i $ and $ j $ in $ S_1 $ , $ \operatorname{LCA}(i,j) $ is in $ S_1 $ , where $ \operatorname{LCA}(x,y) $ denotes the [lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of vertices $ x $ and $ y $ on the tree. Note that a vertex set can have many different partial virtual trees.

Kawashiro Nitori wants to know for each possible $ k $ , if she performs the operation exactly $ k $ times, in how many ways she can make $ U=\{1\} $ in the end? Two ways are considered different if there exists an integer $ z $ ( $ 1 \le z \le k $ ) such that after $ z $ operations the sets $ U $ are different.

Since the answer could be very large, you need to find it modulo $ p $ . It's guaranteed that $ p $ is a prime number.

## 输入格式

The first line contains two integers $ n $ and $ p $ ( $ 2 \le n \le 2000 $ , $ 10^8 + 7 \le p \le 10^9+9 $ ). It's guaranteed that $ p $ is a prime number.

Each of the next $ n-1 $ lines contains two integers $ u_i $ , $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ ), representing an edge between $ u_i $ and $ v_i $ .

It is guaranteed that the given edges form a tree.

## 输出格式

The only line contains $ n-1 $ integers — the answer modulo $ p $ for $ k=1,2,\ldots,n-1 $ .

## 说明/提示

In the first test case, when $ k=1 $ , the only possible way is:

1. $ \{1,2,3,4\} \to \{1\} $ .

When $ k=2 $ , there are $ 6 $ possible ways:

1. $ \{1,2,3,4\} \to \{1,2\} \to \{1\} $ ;
2. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1\} $ ;
3. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1\} $ ;
4. $ \{1,2,3,4\} \to \{1,3\} \to \{1\} $ ;
5. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1\} $ ;
6. $ \{1,2,3,4\} \to \{1,4\} \to \{1\} $ .

When $ k=3 $ , there are $ 6 $ possible ways:

1. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1,2\} \to \{1\} $ ;
2. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1,3\} \to \{1\} $ ;
3. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1,2\} \to \{1\} $ ;
4. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1,4\} \to \{1\} $ ;
5. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1,3\} \to \{1\} $ ;
6. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1,4\} \to \{1\} $ .

## 样例 #1

### 输入

```
4 998244353
1 2
2 3
1 4
```

### 输出

```
1 6 6
```

## 样例 #2

### 输入

```
7 100000007
1 2
1 3
2 4
2 5
3 6
3 7
```

### 输出

```
1 47 340 854 880 320
```

## 样例 #3

### 输入

```
8 1000000007
1 2
2 3
3 4
4 5
5 6
6 7
7 8
```

### 输出

```
1 126 1806 8400 16800 15120 5040
```



---

---
title: "Illumination"
layout: "post"
diff: 省选/NOI-
pid: CF1728G
tag: ['动态规划 DP', '状态合并', '组合数学', '容斥原理', '快速沃尔什变换 FWT']
---

# Illumination

## 题目描述

Consider a segment $ [0, d] $ of the coordinate line. There are $ n $ lanterns and $ m $ points of interest in this segment.

For each lantern, you can choose its power — an integer between $ 0 $ and $ d $ (inclusive). A lantern with coordinate $ x $ illuminates the point of interest with coordinate $ y $ if $ |x - y| $ is less than or equal to the power of the lantern.

A way to choose the power values for all lanterns is considered valid if every point of interest is illuminated by at least one lantern.

You have to process $ q $ queries. Each query is represented by one integer $ f_i $ . To answer the $ i $ -th query, you have to:

- add a lantern on coordinate $ f_i $ ;
- calculate the number of valid ways to assign power values to all lanterns, and print it modulo $ 998244353 $ ;
- remove the lantern you just added.

## 输入格式

The first line contains three integers $ d $ , $ n $ and $ m $ ( $ 4 \le d \le 3 \cdot 10^5 $ ; $ 1 \le n \le 2 \cdot 10^5 $ ; $ 1 \le m \le 16 $ ) — the size of the segment, the number of lanterns and the number of points of interest, respectively.

The second line contains $ n $ integers $ l_1, l_2, \dots, l_n $ ( $ 1 \le l_i \le d - 1 $ ), where $ l_i $ is the coordinate of the $ i $ -th lantern.

The third line contains $ m $ integers $ p_1, p_2, \dots, p_m $ ( $ 1 \le p_i \le d - 1 $ ), where $ p_i $ is the coordinate of the $ i $ -th point of interest.

The fourth line contains one integer $ q $ ( $ 1 \le q \le 5 \cdot 10^5 $ ) — the number of queries.

The fifth line contains $ q $ integers $ f_1, f_2, \dots, f_q $ ( $ 1 \le f_i \le d - 1 $ ), where $ f_i $ is the integer representing the $ i $ -th query.

Additional constraint on the input: during the processing of each query, no coordinate contains more than one object (i. e. there cannot be two or more lanterns with the same coordinate, two or more points of interest with the same coordinate, or a lantern and a point of interest with the same coordinate).

## 输出格式

For each query, print one integer — the answer to it, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
6 1 1
4
3
3
2 1 5
```

### 输出

```
48
47
47
```

## 样例 #2

### 输入

```
6 1 2
4
2 5
2
1 3
```

### 输出

```
44
46
```

## 样例 #3

### 输入

```
20 1 2
11
15 7
1
8
```

### 输出

```
413
```

## 样例 #4

### 输入

```
20 3 5
5 7 18
1 6 3 10 19
5
4 17 15 8 9
```

### 输出

```
190431
187503
188085
189903
189708
```



---

---
title: "List Generation"
layout: "post"
diff: 省选/NOI-
pid: CF1747E
tag: ['递推', '组合数学', '容斥原理']
---

# List Generation

## 题目描述

For given integers $ n $ and $ m $ , let's call a pair of arrays $ a $ and $ b $ of integers good, if they satisfy the following conditions:

- $ a $ and $ b $ have the same length, let their length be $ k $ .
- $ k \ge 2 $ and $ a_1 = 0, a_k = n, b_1 = 0, b_k = m $ .
- For each $ 1 < i \le k $ the following holds: $ a_i \geq a_{i - 1} $ , $ b_i \geq b_{i - 1} $ , and $ a_i + b_i \neq a_{i - 1} + b_{i - 1} $ .

Find the sum of $ |a| $ over all good pairs of arrays $ (a,b) $ . Since the answer can be very large, output it modulo $ 10^9 + 7 $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t (1 \leq t \leq 10^4) $ — the number of test cases. The description of the test cases follows.

The only line of each test case contains two integers $ n $ and $ m $ $ (1 \leq n, m \leq 5 \cdot 10^6) $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^6 $ and the sum of $ m $ over all test cases does not exceed $ 5 \cdot 10^6 $ .

## 输出格式

For each test case, output a single integer — the sum of $ |a| $ over all good pairs of arrays $ (a,b) $ modulo $ 10^9 + 7 $ .

## 说明/提示

In the first testcase, the good pairs of arrays are

- $ ([0, 1], [0, 1]) $ , length = $ 2 $ .
- $ ([0, 1, 1], [0, 0, 1]) $ , length = $ 3 $ .
- $ ([0, 0, 1], [0, 1, 1]) $ , length = $ 3 $ .

Hence the sum of the lengths would be $ {2 + 3 + 3} = 8 $ .

## 样例 #1

### 输入

```
4
1 1
1 2
2 2
100 100
```

### 输出

```
8
26
101
886336572
```



---

---
title: "Count Voting"
layout: "post"
diff: 省选/NOI-
pid: CF1799G
tag: ['动态规划 DP', '组合数学', '容斥原理']
---

# Count Voting

## 题目描述

There are $ n $ people that will participate in voting. Each person has exactly one vote.

 $ i $ -th person has a team $ t_i $ ( $ 1 \leq t_i \leq n $ ) where $ t_i = t_j $ means $ i $ , $ j $ are in the same team. By the rules each person should vote for the person from the different team. Note that it automatically means that each person can't vote for himself.

Each person knows the number of votes $ c_i $ he wants to get. How many possible votings exists, such that each person will get the desired number of votes? Due to this number can be big, find it by modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 200 $ ) — the number of people.

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 0 \leq c_i \leq n $ ) — desired number of votes. It is guaranteed, that $ \sum\limits_{i=1}^{n} c_i = n $ .

The third line contains $ n $ integers $ t_1, t_2, \ldots, t_n $ ( $ 1 \leq t_i \leq n $ ) — team numbers.

## 输出格式

Print a single integer — the number of possible votings by modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test there are two possible votings: $ (2, 3, 1) $ , $ (3, 1, 2) $ .

In the third test there are five possible votings: $ (3, 3, 2, 2, 1) $ , $ (2, 3, 2, 3, 1) $ , $ (3, 3, 1, 2, 2) $ , $ (3, 1, 2, 3, 2) $ , $ (2, 3, 1, 3, 2) $ .

## 样例 #1

### 输入

```
3
1 1 1
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 0 1 0 2
1 2 3 4 5
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5
1 2 2 0 0
3 5 4 3 4
```

### 输出

```
5
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

---
title: "Shohag Loves Counting (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2039F1
tag: ['动态规划 DP', '数论', '莫比乌斯反演', '容斥原理']
---

# Shohag Loves Counting (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions of this problem are the constraints on $ t $ , $ m $ , and the sum of $ m $ . You can only make hacks if both versions of the problem are solved.

For an integer array $ a $ of length $ n $ , define $ f(k) $ as the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the maximum values of all subarrays $ ^{\text{∗}} $ of length $ k $ . For example, if the array is $ [2, 1, 4, 6, 2] $ , then $ f(3) = \operatorname{gcd}(\operatorname{max}([2, 1, 4]), \operatorname{max}([1, 4, 6]), \operatorname{max}([4, 6, 2])) = \operatorname{gcd}(4, 6, 6) = 2 $ .

An array is good if $ f(i) \neq f(j) $ is satisfied over all pairs $ 1 \le i \lt j \le n $ .

Shohag has an integer $ m $ . Help him count the number, modulo $ 998\,244\,353 $ , of non-empty good arrays of arbitrary length such that each element of the array is an integer from $ 1 $ to $ m $ .

 $ ^{\text{∗}} $ An array $ d $ is a subarray of an array $ c $ if $ d $ can be obtained from $ c $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains an integer $ m $ ( $ 1 \le m \le 10^5 $ ).

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output an integer — the number of valid arrays modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the valid arrays are $ [1] $ , $ [1, 2] $ , $ [2] $ , and $ [2, 1] $ .

In the second test case, there are a total of $ 29 $ valid arrays. In particular, the array $ [2, 1, 4] $ with length $ n = 3 $ is valid because all elements are from $ 1 $ to $ m = 5 $ and $ f(1) $ , $ f(2) $ and $ f(n = 3) $ all are distinct:

- $ f(1) = \operatorname{gcd}(\operatorname{max}([2]), \operatorname{max}([1]), \operatorname{max}([4])) = \operatorname{gcd}(2, 1, 4) = 1. $
- $ f(2) = \operatorname{gcd}(\operatorname{max}([2, 1]), \operatorname{max}([1, 4])) = \operatorname{gcd}(2, 4) = 2. $
- $ f(3) = \operatorname{gcd}(\operatorname{max}([2, 1, 4])) = \operatorname{gcd}(4) = 4. $

## 样例 #1

### 输入

```
3
2
5
9
```

### 输出

```
4
29
165
```



---

---
title: "Kevin and Matrices"
layout: "post"
diff: 省选/NOI-
pid: CF2048G
tag: ['二项式定理', '容斥原理']
---

# Kevin and Matrices

## 题目描述

Kevin has been transported to Sacred Heart Hospital, which contains all the $  n \times m  $ matrices with integer values in the range $  [1,v]  $ .

Now, Kevin wants to befriend some matrices, but he is willing to befriend a matrix $  a  $ if and only if the following condition is satisfied:

$$ \min_{1\le i\le n}\left(\max_{1\le j\le m}a_{i,j}\right)\le\max_{1\le j\le m}\left(\min_{1\le i\le n}a_{i,j}\right).$$
 
Please count how many matrices in Sacred Heart Hospital can be friends with Kevin.

Since Kevin is very friendly, there could be many matrices that meet this condition. Therefore, you only need to output the result modulo  
$998\,244\,353$.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $  t  $ ( $  1 \le t \le 8\cdot 10^3  $ ).

The only line of each test case contains three integers $ n $ , $ m $ , $ v $ ( $  1 \le n, v, n \cdot v \leq 10^6 $ , $ 1 \le m \le 10^9  $ ).

It is guaranteed that the sum of $  n \cdot v  $ over all test cases doesn't exceed $  10^6  $ .

## 输出格式

For each test case, output one integer — the number of matrices that can be friends with Kevin modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, besides the matrices $  a=\begin{bmatrix}1&2\\2&1\end{bmatrix}  $ and $  a=\begin{bmatrix}2&1\\1&2\end{bmatrix}  $ , which do not satisfy the condition, the remaining $  2^{2 \cdot 2} - 2 = 14  $ matrices can all be friends with Kevin.

## 样例 #1

### 输入

```
3
2 2 2
2 3 4
11 45 14
```

### 输出

```
14
2824
883799966
```



---

---
title: "Positions in Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF285E
tag: ['动态规划 DP', '容斥原理']
---

# Positions in Permutations

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

We'll call position $ i $ ( $ 1<=i<=n $ ) in permutation $ p_{1},p_{2},...,p_{n} $ good, if $ |p[i]-i|=1 $ . Count the number of permutations of size $ n $ with exactly $ k $ good positions. Print the answer modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The single line contains two space-separated integers $ n $ and $ k $ ( $ 1<=n<=1000,0<=k<=n $ ).

## 输出格式

Print the number of permutations of length $ n $ with exactly $ k $ good positions modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The only permutation of size 1 has 0 good positions.

Permutation $ (1,2) $ has 0 good positions, and permutation $ (2,1) $ has 2 positions.

Permutations of size 3:

1. $ (1,2,3) $ — 0 positions
2. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/0be2e55cf7a19e2daea8429a422511a827d2e236.png) — 2 positions
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/581bad7452cc25f3e2dca31dac99a205bf6361ef.png) — 2 positions
4. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/aad15ec07c7621cca60c3be370547e4457323e38.png) — 2 positions
5. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/b2a9b87daae026f62e110bd34347625817635c68.png) — 2 positions
6. $ (3,2,1) $ — 0 positions

## 样例 #1

### 输入

```
1 0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 2

```

### 输出

```
4

```

## 样例 #4

### 输入

```
4 1

```

### 输出

```
6

```

## 样例 #5

### 输入

```
7 4

```

### 输出

```
328

```



---

---
title: "Mystic Carvings"
layout: "post"
diff: 省选/NOI-
pid: CF297E
tag: ['线段树', '树状数组', '容斥原理']
---

# Mystic Carvings

## 题目描述

The polar bears have discovered a gigantic circular piece of floating ice with some mystic carvings on it. There are $ n $ lines carved on the ice. Each line connects two points on the boundary of the ice (we call these points endpoints). The endpoints are numbered $ 1,2,...,2n $ counter-clockwise along the circumference. No two lines share an endpoint.

Now a group of 6 polar bears (Alice, Bob, Carol, Dave, Eve, Frank) are going to build caves on the endpoints. Each polar bear would build a cave and live in it. No two polar bears can build a cave on the same endpoints. Alice and Bob is a pair of superstitious lovers. They believe the lines are carved by aliens (or humans, which are pretty much the same thing to polar bears), and have certain spiritual power. Therefore they want to build their caves on two endpoints which are connected by a line. The same for Carol and Dave, Eve and Frank.

The distance between two caves X and Y is defined as one plus minimum number of other caves one need to pass through in order to travel from X to Y along the boundary of the ice (endpoints without caves are not counted).

To ensure fairness, the distances between the three pairs of lovers have to be the same (that is, the distance between Alice and Bob, the distance between Carol and Dave, and the distance between Eve and Frank are the same).

The figures below show two different configurations, where the dots on the circle are the endpoints. The configuration on the left is not valid. Although each pair of lovers (A and B, C and D, E and F) is connected a line, the distance requirement is not satisfied. The distance between A and B is 2 (one can go from A to B in the clockwise direction passing through F). The distance between E and F is also 2. However, the distance between C and D is 1 (one can go from C to D in the counter-clockwise direction without passing through any other caves). The configuration on the right is valid. All three pairs have the same distance 1.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297E/d4294009e1edf87a8acd5f07b8b6190c53a3334c.png)Count the number of ways to build the caves under the requirements. Two configurations are considered the same if the same set of 6 endpoints are used.

## 输入格式

The first line contains integer $ n $ ( $ 3<=n<=10^{5} $ ) — the number of lines.

Each of the following $ n $ lines contains two integers $ a_{i},b_{i} $ ( $ 1<=a_{i},b_{i}<=2n $ ), which means that there is a line carved on the ice connecting the $ a_{i} $ –th and $ b_{i} $ –th endpoint.

It's guaranteed that each endpoints touches exactly one line.

## 输出格式

Print the number of ways to build the caves.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

The second sample corresponds to the figure in the problem statement.

## 样例 #1

### 输入

```
4
5 4
1 2
6 7
8 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
8
1 7
2 4
3 9
5 11
6 8
10 16
13 15
14 12

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
title: "Dead Ends"
layout: "post"
diff: 省选/NOI-
pid: CF53E
tag: ['动态规划 DP', '状态合并', '容斥原理']
---

# Dead Ends

## 题目描述

Bertown的生活变得困难了起来。这个城市有太多的道路，而且政府花费了太多来维护这些道路。这里有$n$个节点和$m$条双向道路，且两两节点之间可以通过道路相互到达。现在市长想要关闭一些道路，使最后总共有$n-1$条道路留下，并且所以节点之间仍然联通。另外，市长很关心终点，也就是只有一条道路可以到达的点的数量。终点不能太多也不能太少。在讨论过这个问题之后，市长和他的助手们觉得在应该关闭的道路关闭后，应该总共有恰好$k$个终点。你的任务是求出满足以下三个条件的方案数：

1.有恰好$n-1$条道路保留下来；

2.整张道路图仍然联通；

3.最后有恰好$k$个终点在道路图上。

如果有一条道路在第一种方案中被关闭而在第二种方案中没有被关闭，那么我们认为这两种方案不同。

## 输入格式

第一行有三个整数$n$，$m$和$k$（$3\leq n\leq10 , n-1\leq m\leq \frac {n(n-1)} {2} , 2\leq k\leq n-1$），依次代表了节点、道路和终点的数量。随后$m$行，每行包含两个不同的整数$v_1$和$v_2$（$1\leq v_1 , v_2\leq n , v_1 \not= v_2$），代表一条道路连接的两个节点。每一对节点之间最多有一条道路。节点被编号为1到$n$。保证初始的图联通。

## 输出格式

一个整数：满足条件的方案数。

## 样例 #1

### 输入

```
3 3 2
1 2
2 3
1 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 6 2
1 2
2 3
3 4
4 1
1 3
2 4

```

### 输出

```
12

```

## 样例 #3

### 输入

```
4 6 3
1 2
2 3
3 4
4 1
1 3
2 4

```

### 输出

```
4

```



---

---
title: "List Of Integers"
layout: "post"
diff: 省选/NOI-
pid: CF920G
tag: ['二分', '枚举', '容斥原理']
---

# List Of Integers

## 题目描述

Let's denote as $ L(x,p) $ an infinite sequence of integers $ y $ such that $ gcd(p,y)=1 $ and $ y>x $ (where $ gcd $ is the greatest common divisor of two integer numbers), sorted in ascending order. The elements of $ L(x,p) $ are $ 1 $ -indexed; for example, $ 9 $ , $ 13 $ and $ 15 $ are the first, the second and the third elements of $ L(7,22) $ , respectively.

You have to process $ t $ queries. Each query is denoted by three integers $ x $ , $ p $ and $ k $ , and the answer to this query is $ k $ -th element of $ L(x,p) $ .

## 输入格式

The first line contains one integer $ t $ ( $ 1<=t<=30000 $ ) — the number of queries to process.

Then $ t $ lines follow. $ i $ -th line contains three integers $ x $ , $ p $ and $ k $ for $ i $ -th query ( $ 1<=x,p,k<=10^{6} $ ).

## 输出格式

Print $ t $ integers, where $ i $ -th integer is the answer to $ i $ -th query.

## 样例 #1

### 输入

```
3
7 22 1
7 22 2
7 22 3

```

### 输出

```
9
13
15

```

## 样例 #2

### 输入

```
5
42 42 42
43 43 43
44 44 44
45 45 45
46 46 46

```

### 输出

```
187
87
139
128
141

```



---

---
title: "Team Players"
layout: "post"
diff: 省选/NOI-
pid: CF985G
tag: ['图论', '容斥原理']
---

# Team Players

## 题目描述

### 题目大意

有 $n$ 个点和 $m$ 条边，点编号依次为 $0,1,\cdots, n-1$。

如果一个点的三元组 $(i,j,k)~(i<j<k)$ 两两**没有边**相连，那么它的贡献为 $A\times i+B\times j+C\times k$。

求出所有三元组的贡献和，答案对 $2^{64}$ 取模。

## 输入格式

第一行两个整数 $n, m$（$3 \le n \le 2\times 10 ^ 5, 0\le m \le 2\times 10 ^ 5$）。

接下来一行三个小于等于 $10 ^ 6$ 的正整数 $A, B, C$。

接下来 $m$ 行，每行两个整数 $u, v$ 表示 $u, v$ 间有一条边。

## 输出格式

一行一个整数表示答案。

## 样例 #1

### 输入

```
4 0
2 3 4

```

### 输出

```
64

```

## 样例 #2

### 输入

```
4 1
2 3 4
1 0

```

### 输出

```
38

```

## 样例 #3

### 输入

```
6 4
1 5 3
0 3
3 5
5 4
4 3

```

### 输出

```
164

```



---

---
title: "GCD Counting"
layout: "post"
diff: 省选/NOI-
pid: CF990G
tag: ['点分治', '容斥原理']
---

# GCD Counting

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

Let's denote the function $ g(x, y) $ as the greatest common divisor of the numbers written on the vertices belonging to the simple path from vertex $ x $ to vertex $ y $ (including these two vertices).

For every integer from $ 1 $ to $ 2 \cdot 10^5 $ you have to count the number of pairs $ (x, y) $ $ (1 \le x \le y \le n) $ such that $ g(x, y) $ is equal to this number.

## 输入格式

The first line contains one integer $ n $ — the number of vertices $ (1 \le n \le 2 \cdot 10^5) $ .

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ $ (1 \le a_i \le 2 \cdot 10^5) $ — the numbers written on vertices.

Then $ n - 1 $ lines follow, each containing two integers $ x $ and $ y $ $ (1 \le x, y \le n, x \ne y) $ denoting an edge connecting vertex $ x $ with vertex $ y $ . It is guaranteed that these edges form a tree.

## 输出格式

For every integer $ i $ from $ 1 $ to $ 2 \cdot 10^5 $ do the following: if there is no pair $ (x, y) $ such that $ x \le y $ and $ g(x, y) = i $ , don't output anything. Otherwise output two integers: $ i $ and the number of aforementioned pairs. You have to consider the values of $ i $ in ascending order.

See the examples for better understanding.

## 样例 #1

### 输入

```
3
1 2 3
1 2
2 3

```

### 输出

```
1 4
2 1
3 1

```

## 样例 #2

### 输入

```
6
1 2 4 8 16 32
1 6
6 3
3 4
4 2
6 5

```

### 输出

```
1 6
2 5
4 6
8 1
16 2
32 1

```

## 样例 #3

### 输入

```
4
9 16 144 6
1 3
2 3
4 3

```

### 输出

```
1 1
2 1
3 1
6 2
9 2
16 2
144 1

```



---

