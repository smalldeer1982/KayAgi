---
title: "X-Magic Pair"
layout: "post"
diff: 普及+/提高
pid: CF1612D
tag: ['数论', '最大公约数 gcd']
---

# X-Magic Pair

## 题目描述

You are given a pair of integers $ (a, b) $ and an integer $ x $ .

You can change the pair in two different ways:

- set (assign) $ a := |a - b| $ ;
- set (assign) $ b := |a - b| $ ,

 where $ |a - b| $ is the absolute difference between $ a $ and $ b $ .The pair $ (a, b) $ is called $ x $ -magic if $ x $ is obtainable either as $ a $ or as $ b $ using only the given operations (i.e. the pair $ (a, b) $ is $ x $ -magic if $ a = x $ or $ b = x $ after some number of operations applied). You can apply the operations any number of times (even zero).

Your task is to find out if the pair $ (a, b) $ is $ x $ -magic or not.

You have to answer $ t $ independent test cases.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The next $ t $ lines describe test cases.

The only line of the test case contains three integers $ a $ , $ b $ and $ x $ ( $ 1 \le a, b, x \le 10^{18} $ ).

## 输出格式

For the $ i $ -th test case, print YES if the corresponding pair $ (a, b) $ is $ x $ -magic and NO otherwise.

## 样例 #1

### 输入

```
8
6 9 3
15 38 7
18 8 8
30 30 30
40 50 90
24 28 20
365 216 52
537037812705867558 338887693834423551 3199921013340
```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES
```



---

---
title: "GCD Guess"
layout: "post"
diff: 普及+/提高
pid: CF1665D
tag: ['最大公约数 gcd', '中国剩余定理 CRT']
---

# GCD Guess

## 题目描述

This is an interactive problem.

There is a positive integer $ 1 \le x \le 10^9 $ that you have to guess.

In one query you can choose two positive integers $ a \neq b $ . As an answer to this query you will get $ \gcd(x + a, x + b) $ , where $ \gcd(n, m) $ is the [greatest common divisor](<https://en.wikipedia.org/wiki/Greatest common divisor>) of the numbers $ n $ and $ m $ .

To guess one hidden number $ x $ you are allowed to make no more than $ 30 $ queries.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) denoting the number of test cases.

The integer $ x $ that you have to guess satisfies the constraints: ( $ 1 \le x \le 10^9 $ ).

## 输出格式

The hidden number $ x $ is fixed before the start of the interaction and does not depend on your queries.

To guess each $ x $ you can make no more than $ 30 $ queries in the following way:

- "? a b" ( $ 1 \le a, b \le 2 \cdot 10^9 $ , $ a \neq b $ ).

For this query you will get $ \gcd(x + a, x + b) $ .

When you know $ x $ , print a single line in the following format.

- "! x" ( $ 1 \le x \le 10^9 $ ).

After that continue to solve the next test case.

If you ask more than $ 30 $ queries for one $ x $ or make an invalid query, the interactor will terminate immediately and your program will receive verdict Wrong Answer.

After printing each query do not forget to output end of line and flush the output buffer. Otherwise, you will get the Idleness limit exceeded verdict. To do flush use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- Read documentation for other languages.

Hacks

To use hacks, use the following format of tests:

The first line should contain a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first and only line of each test case should contain a single integer $ x $ ( $ 1 \le x \le 10^9 $ ) denoting the integer $ x $ that should be guessed.

## 说明/提示

The first hidden number is $ 4 $ , that's why the answers for the queries are:

"? 1 2" — $ \gcd(4 + 1, 4 + 2) = \gcd(5, 6) = 1 $ .

"? 12 4" — $ \gcd(4 + 12, 4 + 4) = \gcd(16, 8) = 8 $ .

The second hidden number is $ 10^9 $ , that's why the answer for the query is:

"? 2000000000 1999999999" — $ \gcd(3 \cdot 10^9, 3 \cdot 10^9 - 1) = 1 $ .

These queries are made only for understanding the interaction and are not enough for finding the true $ x $ .

## 样例 #1

### 输入

```
2

1

8


1
```

### 输出

```
? 1 2

? 12 4

! 4
? 2000000000 1999999999

! 1000000000
```



---

---
title: "Lucky Chains"
layout: "post"
diff: 普及+/提高
pid: CF1766D
tag: ['最大公约数 gcd']
---

# Lucky Chains

## 题目描述

Let's name a pair of positive integers $ (x, y) $ lucky if the greatest common divisor of them is equal to $ 1 $ ( $ \gcd(x, y) = 1 $ ).

Let's define a chain induced by $ (x, y) $ as a sequence of pairs $ (x, y) $ , $ (x + 1, y + 1) $ , $ (x + 2, y + 2) $ , $ \dots $ , $ (x + k, y + k) $ for some integer $ k \ge 0 $ . The length of the chain is the number of pairs it consists of, or $ (k + 1) $ .

Let's name such chain lucky if all pairs in the chain are lucky.

You are given $ n $ pairs $ (x_i, y_i) $ . Calculate for each pair the length of the longest lucky chain induced by this pair. Note that if $ (x_i, y_i) $ is not lucky itself, the chain will have the length $ 0 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of pairs.

Next $ n $ lines contains $ n $ pairs — one per line. The $ i $ -th line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i < y_i \le 10^7 $ ) — the corresponding pair.

## 输出格式

Print $ n $ integers, where the $ i $ -th integer is the length of the longest lucky chain induced by $ (x_i, y_i) $ or $ -1 $ if the chain can be infinitely long.

## 说明/提示

In the first test case, $ \gcd(5, 15) = 5 > 1 $ , so it's already not lucky, so the length of the lucky chain is $ 0 $ .

In the second test case, $ \gcd(13 + 1, 37 + 1) = \gcd(14, 38) = 2 $ . So, the lucky chain consists of the single pair $ (13, 37) $ .

## 样例 #1

### 输入

```
4
5 15
13 37
8 9
10009 20000
```

### 输出

```
0
1
-1
79
```



---

---
title: "Vasilije Loves Number Theory"
layout: "post"
diff: 普及+/提高
pid: CF1878F
tag: ['数论', '最大公约数 gcd']
---

# Vasilije Loves Number Theory

## 题目描述

Vasilije is a smart student and his discrete mathematics teacher Sonja taught him number theory very well.

He gave Ognjen a positive integer $ n $ .

Denote $ d(n) $ as the number of positive integer divisors of $ n $ , and denote $ gcd(a, b) $ as the largest integer $ g $ such that $ a $ is divisible by $ g $ and $ b $ is divisible by $ g $ .

After that, he gave Ognjen $ q $ queries, and there are $ 2 $ types of queries.

- $ 1 $ , $ x $ — set $ n $ to $ n \cdot x $ , and then answer the following question: does there exist a positive integer $ a $ such that $ gcd(a, n) = 1 $ , and $ d(n \cdot a) = n $ ?
- $ 2 $ — reset $ n $ to its initial value (before any queries).

Note that $ n $ does not get back to its initial value after the type 1 query.

Since Ognjen is afraid of number theory, Vasilije promised him that after each query, $ d(n) \le 10^9 $ , however, even with that constraint, he still needs your help with this problem.

## 输入格式

The first line contains a positive integer $ t $ , ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains $ 2 $ integers, $ n $ and $ q $ ( $ 1 \le n \le 10^{6} $ , $ 1\le q \le 1000 $ ) — the number $ n $ and the number of queries.

The following $ q $ lines contain an integer $ k $ ( $ 1 \le k \le 2 $ ), if $ k=1 $ then there is another integer in this line $ x $ ( $ 1 \le x \le 10^6 $ ) — the description of the queries.

It is guaranteed that, for the given input, $ d(n) $ does not exceed $ 10^9 $ at any point.

It is guaranteed that the sum of $ q $ over all test cases doesn't exceed $ 10^3 $ .

## 输出格式

For each type 1 query, you should output "YES" if there exist such positive integer $ a $ that $ gcd(a, n) = 1 $ and $ d(n \cdot a)=n $ , and "NO" if he can't.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

In the first test case, we initially have $ n=1 $ .

After the first query: $ n=1 $ , $ d(n)=1 $ , so by taking $ a = 1 $ , $ d(n \cdot a) = n $ , and the answer to this query is "YES".

After the second query: $ n=2 $ , $ d(n)=2 $ , we can, again, take $ a = 1 $ , $ d(n \cdot a) = n $ , and the answer to this query is "YES".

After the third query $ n=1 $ , and this is a type $ 2 $ query so we don't answer it.

After the fourth query: $ n=8 $ , and by taking $ a=3 $ , $ d(n \cdot a) = d(24) = 8 = n $ , so the answer is "YES".

After the fifth query: $ n=72 $ , now we can take $ a=637 $ to get $ n \cdot a = 45864 $ , and $ d(n \cdot a) = 72 = n $ , so the answer is "YES".

In the second test case, we initially have $ n=20 $ .

After the first query: $ n=60 $ , and the answer is "YES".

After the second query: $ n=20 $ , this is a type $ 2 $ query, so we don't answer it.

After the third query: $ n=140 $ , and it can be proven that no matter which positive integer $ a $ we take, $ d(n \cdot a) $ will never be equal to $ n $ , so the answer to this query is "NO".

After the fourth query: $ n=1680 $ . It can be proven that there exists a positive integer $ a $ , such that $ d(n \cdot a) = n $ , so the answer is "YES".

## 样例 #1

### 输入

```
7
1 5
1 1
1 2
2
1 8
1 9
20 4
1 3
2
1 7
1 12
16 10
1 6
1 6
1 10
1 9
1 1
1 9
1 7
1 3
1 2
1 10
9 1
1 3
8 1
1 2
8 3
1 5
1 8
1 10
11 5
1 8
1 2
1 1
1 3
1 1
```

### 输出

```
YES
YES
YES
YES

YES
NO
YES

YES
NO
YES
YES
YES
NO
YES
NO
YES
YES

NO

NO

YES
NO
NO

YES
NO
NO
NO
NO
```



---

---
title: "Split Plus K"
layout: "post"
diff: 普及+/提高
pid: CF1909D
tag: ['最大公约数 gcd']
---

# Split Plus K

## 题目描述

[eliteLAQ - Desert Ruins](https://soundcloud.com/lux-gg-198448038/desert-ruins)

⠀



There are $ n $ positive integers $ a_1, a_2, \dots, a_n $ on a blackboard. You are also given a positive integer $ k $ . You can perform the following operation some (possibly $ 0 $ ) times:

- choose a number $ x $ on the blackboard;
- erase one occurrence of $ x $ ;
- write two positive integers $ y $ , $ z $ such that $ y+z = x+k $ on the blackboard.

Is it possible to make all the numbers on the blackboard equal? If yes, what is the minimum number of operations you need?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \leq k \leq 10^{12} $ ) — the number of integers initially on the blackboard and the constant $ k $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^{12} $ ) — the initial state of the blackboard.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing an integer: the minimum number of operations you need to make all the numbers on the blackboard equal, or $ -1 $ if it is impossible.

## 说明/提示

In the first test case, $ k = 1 $ . You can make all the numbers on the blackboard equal to $ 2 $ with the following operations:

- Erase $ x = 4 $ and write $ (y, z) = (2, 3) $ . Note that $ y+z=x+k $ . The blackboard now contains the multiset $ \{3, 2, 3\} $ .
- Erase $ x = 3 $ and write $ (y, z) = (2, 2) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{2, 2, 2, 3\} $ .
- Erase $ x = 3 $ and write $ (y, z) = (2, 2) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{2, 2, 2, 2, 2\} $ .

This makes all the numbers equal in $ 3 $ operations. It can be shown that you cannot make all the numbers equal in less than $ 3 $ operations.

In the second test case, $ k = 3 $ . You can make all the numbers on the blackboard equal to $ 7 $ with the following operation:

- Erase $ x = 11 $ and write $ (y, z) = (7, 7) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{7, 7, 7\} $ .

In the third test case, $ k = 10 $ . You can make all the numbers on the blackboard equal to $ 40 $ with the following operations:

- Erase $ x = 100 $ and write $ (y, z) = (70, 40) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{70, 40, 40, 100\} $ .
- Erase $ x = 70 $ and write $ (y, z) = (40, 40) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{40, 40, 40, 40, 100\} $ .
- Erase $ x = 100 $ and write $ (y, z) = (40, 70) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{40, 40, 40, 40, 40, 70\} $ .
- Erase $ x = 70 $ and write $ (y, z) = (40, 40) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{40, 40, 40, 40, 40, 40, 40\} $ .

In the fourth and in the fifth test case, you can show that it is impossible to make all the numbers on the blackboard equal.

## 样例 #1

### 输入

```
9
2 1
3 4
2 3
7 11
3 10
100 40 100
2 1
1 2
2 2
1 2
1 327869541
327869541
5 26250314066
439986238782 581370817372 409476934981 287439719777 737637983182
5 616753575719
321037808624 222034505841 214063039282 441536506916 464097941819
5 431813672576
393004301966 405902283416 900951084746 672201172466 518769038906
```

### 输出

```
3
1
4
-1
-1
0
3119
28999960732
-1
```



---

---
title: "Small Operations"
layout: "post"
diff: 普及+/提高
pid: CF2114F
tag: ['动态规划 DP', '搜索', '数学', '记忆化搜索', '最大公约数 gcd']
---

# Small Operations

## 题目描述

给你两个正整数 $x,k$。进行以下两种变换之一称为一次操作：
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $x\cdot a$；
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $\frac{x}{a}$，要求操作完后 $x$ 值是整数。

你需要找出使 $x$ 变为给定正整数 $y$ 的最小操作次数，或判断无解。

## 输入格式

第一行，一个正整数 $t\ (1 \le t \le {10}^4)$，表示测试数据组数。

对于每组测试数据，一行三个正整数 $x,y,k\ (1 \le x,y,k \le {10}^6)$。

保证所有测试数据中 $x$ 的总和与 $y$ 的总和均不超过 ${10}^8$。

## 输出格式

对于每组测试数据，如果无解输出 $-1$，否则输出使 $x$ 变为 $y$ 的最小操作次数。

## 说明/提示

对于第一组测试数据，我们可以选择 $a=2$，将 $x$ 除以 $2$，然后选择 $a=3$，将 $x$ 乘上 $3$，此时 $x$ 将变为 $6$，等于 $y$。

对于第二组测试数据，可以证明其不可能。

对于第七组测试数据，我们可以分别选择 $a=7,9,10,10,12,13$，连续做 $6$ 次乘法。可以证明没有比这更少的操作次数了。

## 样例 #1

### 输入

```
8
4 6 3
4 5 3
4 6 2
10 45 3
780 23 42
11 270 23
1 982800 13
1 6 2
```

### 输出

```
2
-1
-1
3
3
3
6
-1
```



---

---
title: "Good Sequences"
layout: "post"
diff: 普及+/提高
pid: CF264B
tag: ['动态规划 DP', '枚举', '最大公约数 gcd']
---

# Good Sequences

## 题目描述

Squirrel Liss is interested in sequences. She also has preferences of integers. She thinks $ n $ integers $ a_{1},a_{2},...,a_{n} $ are good.

Now she is interested in good sequences. A sequence $ x_{1},x_{2},...,x_{k} $ is called good if it satisfies the following three conditions:

- The sequence is strictly increasing, i.e. $ x_{i}&lt;x_{i+1} $ for each $ i $ $ (1<=i<=k-1) $ .
- No two adjacent elements are coprime, i.e. $ gcd(x_{i},x_{i+1})&gt;1 $ for each $ i $ $ (1<=i<=k-1) $ (where $ gcd(p,q) $ denotes the greatest common divisor of the integers $ p $ and $ q $ ).
- All elements of the sequence are good integers.

Find the length of the longest good sequence.

## 输入格式

The input consists of two lines. The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of good integers. The second line contains a single-space separated list of good integers $ a_{1},a_{2},...,a_{n} $ in strictly increasing order ( $ 1<=a_{i}<=10^{5}; a_{i}&lt;a_{i+1} $ ).

## 输出格式

Print a single integer — the length of the longest good sequence.

## 说明/提示

In the first example, the following sequences are examples of good sequences: \[2; 4; 6; 9\], \[2; 4; 6\], \[3; 9\], \[6\]. The length of the longest good sequence is 4.

## 样例 #1

### 输入

```
5
2 3 4 6 9

```

### 输出

```
4

```

## 样例 #2

### 输入

```
9
1 2 3 5 6 7 8 9 10

```

### 输出

```
4

```



---

---
title: "Fox And Jumping"
layout: "post"
diff: 普及+/提高
pid: CF510D
tag: ['动态规划 DP', '枚举', '背包 DP', '最大公约数 gcd']
---

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=300 $ ), number of cards.

The second line contains $ n $ numbers $ l_{i} $ ( $ 1<=l_{i}<=10^{9} $ ), the jump lengths of cards.

The third line contains $ n $ numbers $ c_{i} $ ( $ 1<=c_{i}<=10^{5} $ ), the costs of cards.

## 输出格式

If it is impossible to buy some cards and become able to jump to any cell, output -1. Otherwise output the minimal cost of buying such set of cards.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10

```

### 输出

```
6

```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026

```

### 输出

```
7237

```



---

---
title: "Line"
layout: "post"
diff: 普及+/提高
pid: CF7C
tag: ['最大公约数 gcd', '扩展欧几里德算法', '逆元']
---

# Line

## 题目描述

A line on the plane is described by an equation $ Ax+By+C=0 $ . You are to find any point on this line, whose coordinates are integer numbers from $ -5·10^{18} $ to $ 5·10^{18} $ inclusive, or to find out that such points do not exist.

## 输入格式

The first line contains three integers $ A $ , $ B $ and $ C $ ( $ -2·10^{9}<=A,B,C<=2·10^{9} $ ) — corresponding coefficients of the line equation. It is guaranteed that $ A^{2}+B^{2}>0 $ .

## 输出格式

If the required point exists, output its coordinates, otherwise output -1.

## 样例 #1

### 输入

```
2 5 3

```

### 输出

```
6 -3

```



---

