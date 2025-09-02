---
title: "Count Paths"
layout: "post"
diff: 提高+/省选-
pid: CF1923E
tag: ['点分治', '递归']
---

# Count Paths

## 题目描述

You are given a tree, consisting of $ n $ vertices, numbered from $ 1 $ to $ n $ . Every vertex is colored in some color, denoted by an integer from $ 1 $ to $ n $ .

A simple path of the tree is called beautiful if:

- it consists of at least $ 2 $ vertices;
- the first and the last vertices of the path have the same color;
- no other vertex on the path has the same color as the first vertex.

Count the number of the beautiful simple paths of the tree. Note that paths are considered undirected (i. e. the path from $ x $ to $ y $ is the same as the path from $ y $ to $ x $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le n $ ) — the color of each vertex.

The $ i $ -th of the next $ n - 1 $ lines contains two integers $ v_i $ and $ u_i $ ( $ 1 \le v_i, u_i \le n $ ; $ v_i \neq u_i $ ) — the $ i $ -th edge of the tree.

The given edges form a valid tree. The sum of $ n $ over all testcases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print a single integer — the number of the beautiful simple paths of the tree.

## 样例 #1

### 输入

```
4
3
1 2 1
1 2
2 3
5
2 1 2 1 2
1 2
1 3
3 4
4 5
5
1 2 3 4 5
1 2
1 3
3 4
4 5
4
2 2 2 2
3 1
3 2
3 4
```

### 输出

```
1
3
0
3
```



---

---
title: "Painting Fence"
layout: "post"
diff: 提高+/省选-
pid: CF448C
tag: ['贪心', '递归', '分治']
---

# Painting Fence

## 题目描述

Bizon the Champion isn't just attentive, he also is very hardworking.

Bizon the Champion decided to paint his old fence his favorite color, orange. The fence is represented as $ n $ vertical planks, put in a row. Adjacent planks have no gap between them. The planks are numbered from the left to the right starting from one, the $ i $ -th plank has the width of $ 1 $ meter and the height of $ a_{i} $ meters.

Bizon the Champion bought a brush in the shop, the brush's width is $ 1 $ meter. He can make vertical and horizontal strokes with the brush. During a stroke the brush's full surface must touch the fence at all the time (see the samples for the better understanding). What minimum number of strokes should Bizon the Champion do to fully paint the fence? Note that you are allowed to paint the same area of the fence multiple times.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=5000) $ — the number of fence planks. The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the minimum number of strokes needed to paint the whole fence.

## 说明/提示

In the first sample you need to paint the fence in three strokes with the brush: the first stroke goes on height 1 horizontally along all the planks. The second stroke goes on height 2 horizontally and paints the first and second planks and the third stroke (it can be horizontal and vertical) finishes painting the fourth plank.

In the second sample you can paint the fence with two strokes, either two horizontal or two vertical strokes.

In the third sample there is only one plank that can be painted using a single vertical stroke.

## 样例 #1

### 输入

```
5
2 2 1 2 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2
2 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
1
5

```

### 输出

```
1

```



---

---
title: "SUM and REPLACE"
layout: "post"
diff: 提高+/省选-
pid: CF920F
tag: ['线段树', '递归', '分块']
---

# SUM and REPLACE

## 题目描述

Let $ D(x) $ be the number of positive divisors of a positive integer $ x $ . For example, $ D(2)=2 $ ( $ 2 $ is divisible by $ 1 $ and $ 2 $ ), $ D(6)=4 $ ( $ 6 $ is divisible by $ 1 $ , $ 2 $ , $ 3 $ and $ 6 $ ).

You are given an array $ a $ of $ n $ integers. You have to process two types of queries:

1. REPLACE $ l $ $ r $ — for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/8c67e39bbb4a436ecb9bbf84b28c1b332f05ca94.png) replace $ a_{i} $ with $ D(a_{i}) $ ;
2. SUM $ l $ $ r $ — calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/1deabb69ce88e0c9a5b8e5232e5782460ccfe87b.png).

Print the answer for each SUM query.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=3·10^{5} $ ) — the number of elements in the array and the number of queries to process, respectively.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the array.

Then $ m $ lines follow, each containing $ 3 $ integers $ t_{i} $ , $ l_{i} $ , $ r_{i} $ denoting $ i $ -th query. If $ t_{i}=1 $ , then $ i $ -th query is REPLACE $ l_{i} $ $ r_{i} $ , otherwise it's SUM $ l_{i} $ $ r_{i} $ ( $ 1<=t_{i}<=2 $ , $ 1<=l_{i}<=r_{i}<=n $ ).

There is at least one SUM query.

## 输出格式

For each SUM query print the answer to it.

## 样例 #1

### 输入

```
7 6
6 4 1 10 3 2 4
2 1 7
2 4 5
1 3 5
2 4 4
1 5 7
2 1 7

```

### 输出

```
30
13
4
22

```



---

---
title: "XOR-pyramid"
layout: "post"
diff: 提高+/省选-
pid: CF983B
tag: ['动态规划 DP', '递推', '递归']
---

# XOR-pyramid

## 题目描述

For an array $ b $ of length $ m $ we define the function $ f $ as

 $  f(b) = \begin{cases} b[1] & \quad \text{if } m = 1 \\ f(b[1] \oplus b[2],b[2] \oplus b[3],\dots,b[m-1] \oplus b[m]) & \quad \text{otherwise,} \end{cases}  $ where $ \oplus $ is [bitwise exclusive OR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

For example, $ f(1,2,4,8)=f(1\oplus2,2\oplus4,4\oplus8)=f(3,6,12)=f(3\oplus6,6\oplus12)=f(5,10)=f(5\oplus10)=f(15)=15 $

You are given an array $ a $ and a few queries. Each query is represented as two integers $ l $ and $ r $ . The answer is the maximum value of $ f $ on all continuous subsegments of the array $ a_l, a_{l+1}, \ldots, a_r $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the length of $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2^{30}-1 $ ) — the elements of the array.

The third line contains a single integer $ q $ ( $ 1 \le q \le 100\,000 $ ) — the number of queries.

Each of the next $ q $ lines contains a query represented as two integers $ l $ , $ r $ ( $ 1 \le l \le r \le n $ ).

## 输出格式

Print $ q $ lines — the answers for the queries.

## 说明/提示

In first sample in both queries the maximum value of the function is reached on the subsegment that is equal to the whole segment.

In second sample, optimal segment for first query are $ [3,6] $ , for second query — $ [2,5] $ , for third — $ [3,4] $ , for fourth — $ [1,2] $ .

## 样例 #1

### 输入

```
3
8 4 1
2
2 3
1 2

```

### 输出

```
5
12

```

## 样例 #2

### 输入

```
6
1 2 4 8 16 32
4
1 6
2 5
3 4
1 2

```

### 输出

```
60
30
12
3

```



---

