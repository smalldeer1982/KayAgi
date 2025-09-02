---
title: "Making Shapes"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1290F
tag: ['数位 DP']
---

# Making Shapes

## 题目描述

You are given $ n $ pairwise non-collinear two-dimensional vectors. You can make shapes in the two-dimensional plane with these vectors in the following fashion:

1. Start at the origin $ (0, 0) $ .
2. Choose a vector and add the segment of the vector to the current point. For example, if your current point is at $ (x, y) $ and you choose the vector $ (u, v) $ , draw a segment from your current point to the point at $ (x + u, y + v) $ and set your current point to $ (x + u, y + v) $ .
3. Repeat step 2 until you reach the origin again.

You can reuse a vector as many times as you want.

Count the number of different, non-degenerate (with an area greater than $ 0 $ ) and convex shapes made from applying the steps, and the vectors building the shape are in counter-clockwise fashion, such that the shape can be contained within a $ m \times m $ square. Since this number can be too large, you should calculate it by modulo $ 998244353 $ .

Two shapes are considered the same if there exists some parallel translation of the first shape to another.

A shape can be contained within a $ m \times m $ square if there exists some parallel translation of this shape so that every point $ (u, v) $ inside or on the border of the shape satisfies $ 0 \leq u, v \leq m $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ — the number of vectors and the size of the square ( $ 1 \leq n \leq 5 $ , $ 1 \leq m \leq 10^9 $ ).

Each of the next $ n $ lines contains two integers $ x_i $ and $ y_i $ — the $ x $ -coordinate and $ y $ -coordinate of the $ i $ -th vector ( $ |x_i|, |y_i| \leq 4 $ , $ (x_i, y_i) \neq (0, 0) $ ).

It is guaranteed, that no two vectors are parallel, so for any two indices $ i $ and $ j $ such that $ 1 \leq i < j \leq n $ , there is no real value $ k $ such that $ x_i \cdot k = x_j $ and $ y_i \cdot k = y_j $ .

## 输出格式

Output a single integer — the number of satisfiable shapes by modulo $ 998244353 $ .

## 说明/提示

The shapes for the first sample are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290F/1435a49a0854cf885bd0a880b2bd4ec616aaecf0.png)The only shape for the second sample is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290F/c198c6d97ae318f4efbc29b95f2307d41e83d32d.png)The only shape for the fourth sample is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290F/5612d8b3b2e07c811bb5d8b4ac9e1b97873da5e3.png)

## 样例 #1

### 输入

```
3 3
-1 0
1 1
0 -1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3
-1 0
2 2
0 -1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 1776966
-1 0
3 3
0 -2
```

### 输出

```
296161
```

## 样例 #4

### 输入

```
4 15
-4 -4
-1 1
-1 -4
4 3
```

### 输出

```
1
```

## 样例 #5

### 输入

```
5 10
3 -4
4 -3
1 -3
2 -3
-3 -4
```

### 输出

```
0
```

## 样例 #6

### 输入

```
5 1000000000
-2 4
2 -3
0 -4
2 4
-1 -3
```

### 输出

```
9248783
```



---

---
title: "Bit Game (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2027E2
tag: ['博弈论', '数位 DP', 'SG 函数']
---

# Bit Game (Hard Version)

## 题目描述

This is the hard version of this problem. The only difference is that you need to output the number of choices of games where Bob wins in this version, where the number of stones in each pile are not fixed. You must solve both versions to be able to hack.

Alice and Bob are playing a familiar game where they take turns removing stones from $ n $ piles. Initially, there are $ x_i $ stones in the $ i $ -th pile, and it has an associated value $ a_i $ . A player can take $ d $ stones away from the $ i $ -th pile if and only if both of the following conditions are met:

- $ 1 \le d \le a_i $ , and
- $ x \, \& \, d = d $ , where $ x $ is the current number of stones in the $ i $ -th pile and $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

The player who cannot make a move loses, and Alice goes first.

You're given the $ a_i $ values of each pile, but the number of stones in the $ i $ -th pile has not been determined yet. For the $ i $ -th pile, $ x_i $ can be any integer between $ 1 $ and $ b_i $ , inclusive. That is, you can choose an array $ x_1, x_2, \ldots, x_n $ such that the condition $ 1 \le x_i \le b_i $ is satisfied for all piles.

Your task is to count the number of games where Bob wins if both players play optimally. Two games are considered different if the number of stones in any pile is different, i.e., the arrays of $ x $ differ in at least one position.

Since the answer can be very large, please output the result modulo $ 10^9 + 7 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains $ n $ ( $ 1 \le n \le 10^4 $ ) — the number of piles.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i < 2^{30} $ ).

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i < 2^{30} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^4 $ .

## 输出格式

Output a single integer, the number of games where Bob wins, modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, no matter which values of $ x_2 $ and $ x_3 $ we choose, the second and third piles will always be chosen exactly once before no more stones can be taken from them. If $ x_1 = 2 $ , then no stones can be taken from it, so Bob will make the last move. If $ x_1 = 1 $ or $ x_1 = 3 $ , then exactly one move can be made on that pile, so Alice will make the last move. So Bob wins when $ x = [2, 1, 1] $ or $ x = [2, 1, 2] $ or $ x = [2, 2, 1] $ or $ x = [2, 2, 2] $ .

In the second test case, Bob wins when $ x_1 = 14 $ or $ x_1 = 30 $ by removing $ 14 - k $ stones, where $ k $ is the number of stones Alice removes on her turn. Bob also wins when $ x_1 = 16 $ or $ x_1 = 32 $ since Alice does not have any moves to begin with.

## 样例 #1

### 输入

```
7
3
1 2 3
3 2 2
1
13
45
5
5 4 7 8 6
4 4 5 5 5
4
6 4 8 8
12 13 14 12
3
92856133 46637598 12345678
29384774 73775896 87654321
2
65 12
110 31
4
677810235 275091182 428565855 720629731
74522416 889934149 3394714 230851724
```

### 输出

```
4
4
0
6552
722019507
541
665443265
```



---

