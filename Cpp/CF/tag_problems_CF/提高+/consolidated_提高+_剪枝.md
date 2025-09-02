---
title: "Tree Master"
layout: "post"
diff: 提高+/省选-
pid: CF1806E
tag: ['剪枝', '分块', '根号分治']
---

# Tree Master

## 题目描述

You are given a tree with $ n $ weighted vertices labeled from $ 1 $ to $ n $ rooted at vertex $ 1 $ . The parent of vertex $ i $ is $ p_i $ and the weight of vertex $ i $ is $ a_i $ . For convenience, define $ p_1=0 $ .

For two vertices $ x $ and $ y $ of the same depth $ ^\dagger $ , define $ f(x,y) $ as follows:

- Initialize $ \mathrm{ans}=0 $ .
- While both $ x $ and $ y $ are not $ 0 $ : 
  - $ \mathrm{ans}\leftarrow \mathrm{ans}+a_x\cdot a_y $ ;
  - $ x\leftarrow p_x $ ;
  - $ y\leftarrow p_y $ .
- $ f(x,y) $ is the value of $ \mathrm{ans} $ .

You will process $ q $ queries. In the $ i $ -th query, you are given two integers $ x_i $ and $ y_i $ and you need to calculate $ f(x_i,y_i) $ .

 $ ^\dagger $ The depth of vertex $ v $ is the number of edges on the unique simple path from the root of the tree to vertex $ v $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \le n \le 10^5 $ ; $ 1 \le q \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ ).

The third line contains $ n-1 $ integers $ p_2, \ldots, p_n $ ( $ 1 \le p_i < i $ ).

Each of the next $ q $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1\le x_i,y_i\le n $ ). It is guaranteed that $ x_i $ and $ y_i $ are of the same depth.

## 输出格式

Output $ q $ lines, the $ i $ -th line contains a single integer, the value of $ f(x_i,y_i) $ .

## 说明/提示

Consider the first example:

In the first query, the answer is $ a_4\cdot a_5+a_3\cdot a_3+a_2\cdot a_2+a_1\cdot a_1=3+4+25+1=33 $ .

In the second query, the answer is $ a_6\cdot a_6+a_2\cdot a_2+a_1\cdot a_1=1+25+1=27 $ .

## 样例 #1

### 输入

```
6 2
1 5 2 3 1 1
1 2 3 3 2
4 5
6 6
```

### 输出

```
33
27
```

## 样例 #2

### 输入

```
14 8
3 2 5 3 1 4 2 2 2 5 5 5 2 4
1 2 3 1 1 4 7 3 3 1 5 3 8
4 4
4 10
13 10
3 12
13 9
3 12
9 10
11 5
```

### 输出

```
47
53
48
36
42
36
48
14
```



---

---
title: "Number With The Given Amount Of Divisors"
layout: "post"
diff: 提高+/省选-
pid: CF27E
tag: ['剪枝', '素数判断,质数,筛法']
---

# Number With The Given Amount Of Divisors

## 题目描述

Given the number $ n $ , find the smallest positive integer which has exactly $ n $ divisors. It is guaranteed that for the given $ n $ the answer will not exceed $ 10^{18} $ .

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=1000 $ ).

## 输出格式

Output the smallest positive integer with exactly $ n $ divisors.

## 样例 #1

### 输入

```
4

```

### 输出

```
6

```

## 样例 #2

### 输入

```
6

```

### 输出

```
12

```



---

---
title: "Anya and Cubes"
layout: "post"
diff: 提高+/省选-
pid: CF525E
tag: ['搜索', '枚举', '剪枝', '折半搜索 meet in the middle']
---

# Anya and Cubes

## 题目描述

Anya loves to fold and stick. Today she decided to do just that.

Anya has $ n $ cubes lying in a line and numbered from $ 1 $ to $ n $ from left to right, with natural numbers written on them. She also has $ k $ stickers with exclamation marks. We know that the number of stickers does not exceed the number of cubes.

Anya can stick an exclamation mark on the cube and get the factorial of the number written on the cube. For example, if a cube reads $ 5 $, then after the sticking it reads $ 5! $, which equals $ 120 $.

You need to help Anya count how many ways there are to choose some of the cubes and stick on some of the chosen cubes at most $ k $ exclamation marks so that the sum of the numbers written on the chosen cubes after the sticking becomes equal to $ S $. Anya can stick at most one exclamation mark on each cube. Can you do it?

Two ways are considered the same if they have the same set of chosen cubes and the same set of cubes with exclamation marks.

## 输入格式

The first line of the input contains three space-separated integers $ n $, $ k $ and $ S\ (1\le n\le25,\ 0\le k\le n,\ 1\le S\le10^{16})$ — the number of cubes and the number of stickers that Anya has, and the sum that she needs to get.

The second line contains $ n $ positive integers $ a_{i}\ ( 1\le a_{i}\le10^{9}) $ — the numbers, written on the cubes. The cubes in the input are described in the order from left to right, starting from the first one.

Multiple cubes can contain the same numbers.

## 输出格式

Output the number of ways to choose some number of cubes and stick exclamation marks on some of them so that the sum of the numbers became equal to the given number $ S $ .

## 说明/提示

In the first sample the only way is to choose both cubes and stick an exclamation mark on each of them.

In the second sample the only way is to choose both cubes but don't stick an exclamation mark on any of them.

In the third sample it is possible to choose any of the cubes in three ways, and also we may choose to stick or not to stick the exclamation mark on it. So, the total number of ways is six.

## 样例 #1

### 输入

```
2 2 30
4 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 2 7
4 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1 1
1 1 1

```

### 输出

```
6

```



---

---
title: "Fibonacci-ish"
layout: "post"
diff: 提高+/省选-
pid: CF633D
tag: ['枚举', '剪枝', '概率论']
---

# Fibonacci-ish

## 题目描述

Yash has recently learnt about the Fibonacci sequence and is very excited about it. He calls a sequence Fibonacci-ish if

1. the sequence consists of at least two elements
2. $ f_{0} $ and $ f_{1} $ are arbitrary
3. $ f_{n+2}=f_{n+1}+f_{n} $ for all $ n>=0 $ .

You are given some sequence of integers $ a_{1},a_{2},...,a_{n} $ . Your task is rearrange elements of this sequence in such a way that its longest possible prefix is Fibonacci-ish sequence.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=1000 $ ) — the length of the sequence $ a_{i} $ .

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ |a_{i}|<=10^{9} $ ).

## 输出格式

Print the length of the longest possible Fibonacci-ish prefix of the given sequence after rearrangement.

## 说明/提示

In the first sample, if we rearrange elements of the sequence as $ -1 $ , $ 2 $ , $ 1 $ , the whole sequence $ a_{i} $ would be Fibonacci-ish.

In the second sample, the optimal way to rearrange elements is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/d3ff4ea2c12e52c9ca4c15e14139f2b01f478bed.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/67db7509088e9e5340d450cc0af986d1466ce169.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/7be78903e0b1130fefbb3533b84d31cf4efaa940.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/0d98505f3f5d3d9cd5c06747ea4bb30d03a8d1e8.png), $ 28 $ .

## 样例 #1

### 输入

```
3
1 2 -1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
28 35 7 14 21

```

### 输出

```
4

```



---

---
title: "Vladik and cards"
layout: "post"
diff: 提高+/省选-
pid: CF743E
tag: ['枚举', '剪枝', '状态合并', '向量']
---

# Vladik and cards

## 题目描述

Vladik was bored on his way home and decided to play the following game. He took $ n $ cards and put them in a row in front of himself. Every card has a positive integer number not exceeding $ 8 $ written on it. He decided to find the longest subsequence of cards which satisfies the following conditions:

- the number of occurrences of each number from $ 1 $ to $ 8 $ in the subsequence doesn't differ by more then $ 1 $ from the number of occurrences of any other number. Formally, if there are $ c_{k} $ cards with number $ k $ on them in the subsequence, than for all pairs of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743E/0c6cc5f621659ae2ddf5ab0dac10dd28e326ec14.png) the condition $ |c_{i}-c_{j}|<=1 $ must hold.
- if there is at least one card with number $ x $ on it in the subsequence, then all cards with number $ x $ in this subsequence must form a continuous segment in it (but not necessarily a continuous segment in the original sequence). For example, the subsequence $ [1,1,2,2] $ satisfies this condition while the subsequence $ [1,2,2,1] $ doesn't. Note that $ [1,1,2,2] $ doesn't satisfy the first condition.

Please help Vladik to find the length of the longest subsequence that satisfies both conditions.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of cards in Vladik's sequence.

The second line contains the sequence of $ n $ positive integers not exceeding $ 8 $ — the description of Vladik's sequence.

## 输出格式

Print single integer — the length of the longest subsequence of Vladik's sequence that satisfies both conditions.

## 说明/提示

In the first sample all the numbers written on the cards are equal, so you can't take more than one card, otherwise you'll violate the first condition.

## 样例 #1

### 输入

```
3
1 1 1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
8
8 7 6 5 4 3 2 1

```

### 输出

```
8
```

## 样例 #3

### 输入

```
24
1 8 1 2 8 2 3 8 3 4 8 4 5 8 5 6 8 6 7 8 7 8 8 8

```

### 输出

```
17
```



---

