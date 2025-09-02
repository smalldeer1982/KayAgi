---
title: "Galaxy Generator"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2062H
tag: []
---

# Galaxy Generator

## 题目描述

In a two-dimensional universe, a star can be represented by a point $ (x,y) $ on a two-dimensional plane. Two stars are directly connected if and only if their $ x $ or $ y $ coordinates are the same, and there are no other stars on the line segment between them. Define a galaxy as a connected component composed of stars connected directly or indirectly (through other stars).

For a set of stars, its value is defined as the minimum number of galaxies that can be obtained after performing the following operation for any (possibly, zero) times: in each operation, you can select a point $ (x,y) $ without stars. If a star can be directly connected to at least $ 3 $ stars after creating it here, then you create a star here.

You are given a $ n\times n $ matrix $ a $ consisting of $ 0 $ and $ 1 $ describing a set $ S $ of stars. There is a star at $ (x,y) $ if and only if $ a_{x,y}=1 $ . Calculate the sum, modulo $ 10^9 + 7 $ , of the values of all non-empty subsets of $ S $ .

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

For each test case, the first line contains a single integer $ n $ ( $ 1 \leq n \leq 14 $ ) — the size of matrix $ a $ .

Then $ n $ lines follow; the $ i $ -th line contains a string $ a_i $ of length $ n $ — the $ i $ -th row of matrix $ a $ .

It is guaranteed that the sum of $ 2^n $ over all test cases does not exceed $ 2^{14} $ .

## 输出格式

For each test case, output the sum, modulo $ 10^9 + 7 $ , of the values of all non-empty subsets of $ S $ .

## 说明/提示

In the first test case, $ S $ is empty. $ S $ has no non-empty subsets. So the answer is $ 0 $ .

In the second test case, $ S = \{(1,2),(2,1)\} $ . $ S $ has $ 3 $ non-empty subsets.

- $ \{(1,2)\} $ and $ \{(2,1)\} $ — there is only one star in the set, forming $ 1 $ galaxy.
- $ \{(1,2),(2,1)\} $ — two stars in the set are not connected, forming $ 2 $ galaxies.

So the answer is $ 1+1+2=4 $ .

In the third test case, $ S = \{(1,2),(3,1),(3,3)\} $ . $ S $ has $ 7 $ non-empty subsets.

- $ \{(1,2)\} $ , $ \{(3,1)\} $ , and $ \{(3,3)\} $ — there is only one star in the set, forming $ 1 $ galaxy.
- $ \{(1,2),(3,1)\} $ and $ \{(1,2),(3,3)\} $ — two stars in the set are not connected, forming $ 2 $ galaxies.
- $ \{(3,1),(3,3)\} $ — two stars in the set are connected, forming $ 1 $ galaxy.
- $ \{(1,2),(3,1),(3,3)\} $ — initially, star $ (1,2) $ is not in the galaxy formed by $ (3,1) $ and $ (3,3) $ . You can make an operation creating a star at $ (3,2) $ connecting to these three stars, forming $ 1 $ galaxy.

So the answer is $ 1+1+1+2+2+1+1=9 $ .

## 样例 #1

### 输入

```
8
1
0
2
01
10
3
010
000
101
4
0110
1001
1001
0110
11
11111110111
10000010010
10111010011
10111010011
10111010001
10000010000
11111110101
00000000111
11011010011
10010101100
11101010100
11
11011111110
10010000010
00010111010
10010111010
01010111010
11010000010
01011111110
11000000000
01010000010
01000111100
00000001010
11
11010101001
11001010100
00000000110
11111110010
10000010010
10111010110
10111010111
10111010010
10000010110
11111110100
00000000000
3
111
100
111
```

### 输出

```
0
4
9
355
593092633
438667113
922743932
155
```

