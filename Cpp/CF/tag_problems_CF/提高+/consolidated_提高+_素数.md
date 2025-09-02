---
title: "Enlarge GCD"
layout: "post"
diff: 提高+/省选-
pid: CF1034A
tag: ['枚举', '素数判断,质数,筛法', '概率论']
---

# Enlarge GCD

## 题目描述

Mr. F has $ n $ positive integers, $ a_1, a_2, \ldots, a_n $ .

He thinks the greatest common divisor of these integers is too small. So he wants to enlarge it by removing some of the integers.

But this problem is too simple for him, so he does not want to do it by himself. If you help him, he will give you some scores in reward.

Your task is to calculate the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \leq n \leq 3 \cdot 10^5 $ ) — the number of integers Mr. F has.

The second line contains $ n $ integers, $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 1.5 \cdot 10^7 $ ).

## 输出格式

Print an integer — the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

You should not remove all of the integers.

If there is no solution, print «-1» (without quotes).

## 说明/提示

In the first example, the greatest common divisor is $ 1 $ in the beginning. You can remove $ 1 $ so that the greatest common divisor is enlarged to $ 2 $ . The answer is $ 1 $ .

In the second example, the greatest common divisor is $ 3 $ in the beginning. You can remove $ 6 $ and $ 9 $ so that the greatest common divisor is enlarged to $ 15 $ . There is no solution which removes only one integer. So the answer is $ 2 $ .

In the third example, there is no solution to enlarge the greatest common divisor. So the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
1 2 4

```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
6 9 15 30

```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
1 1 1

```

### 输出

```
-1
```



---

---
title: "Kuzya and Homework"
layout: "post"
diff: 提高+/省选-
pid: CF1582G
tag: ['单调队列', '素数判断,质数,筛法']
---

# Kuzya and Homework

## 题目描述

Kuzya started going to school. He was given math homework in which he was given an array $ a $ of length $ n $ and an array of symbols $ b $ of length $ n $ , consisting of symbols '\*' and '/'.

Let's denote a path of calculations for a segment $ [l; r] $ ( $ 1 \le l \le r \le n $ ) in the following way:

- Let $ x=1 $ initially. For every $ i $ from $ l $ to $ r $ we will consequently do the following: if $ b_i= $ '\*', $ x=x*a_i $ , and if $ b_i= $ '/', then $ x=\frac{x}{a_i} $ . Let's call a path of calculations for the segment $ [l; r] $ a list of all $ x $ that we got during the calculations (the number of them is exactly $ r - l + 1 $ ).

For example, let $ a=[7, $ $ 12, $ $ 3, $ $ 5, $ $ 4, $ $ 10, $ $ 9] $ , $ b=[/, $ $ *, $ $ /, $ $ /, $ $ /, $ $ *, $ $ *] $ , $ l=2 $ , $ r=6 $ , then the path of calculations for that segment is $ [12, $ $ 4, $ $ 0.8, $ $ 0.2, $ $ 2] $ .

Let's call a segment $ [l;r] $ simple if the path of calculations for it contains only integer numbers.

Kuzya needs to find the number of simple segments $ [l;r] $ ( $ 1 \le l \le r \le n $ ). Since he obviously has no time and no interest to do the calculations for each option, he asked you to write a program to get to find that number!

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^6 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ).

The third line contains $ n $ symbols without spaces between them — the array $ b_1, b_2 \ldots b_n $ ( $ b_i= $ '/' or $ b_i= $ '\*' for every $ 1 \le i \le n $ ).

## 输出格式

Print a single integer — the number of simple segments $ [l;r] $ .

## 样例 #1

### 输入

```
3
1 2 3
*/*
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
6 4 10 1 2 15 1
*/*/*//
```

### 输出

```
8
```



---

---
title: "Madoka and The Best University"
layout: "post"
diff: 提高+/省选-
pid: CF1717E
tag: ['数论', '素数判断,质数,筛法']
---

# Madoka and The Best University

## 题目描述

Madoka wants to enter to "Novosibirsk State University", but in the entrance exam she came across a very difficult task:

Given an integer $ n $ , it is required to calculate $ \sum{\operatorname{lcm}(c, \gcd(a, b))} $ , for all triples of positive integers $ (a, b, c) $ , where $ a + b + c = n $ .

In this problem $ \gcd(x, y) $ denotes the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of $ x $ and $ y $ , and $ \operatorname{lcm}(x, y) $ denotes the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of $ x $ and $ y $ .

Solve this problem for Madoka and help her to enter to the best university!

## 输入格式

The first and the only line contains a single integer $ n $ ( $ 3 \le n \le 10^5 $ ).

## 输出格式

Print exactly one interger — $ \sum{\operatorname{lcm}(c, \gcd(a, b))} $ . Since the answer can be very large, then output it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, there is only one suitable triple $ (1, 1, 1) $ . So the answer is $ \operatorname{lcm}(1, \gcd(1, 1)) = \operatorname{lcm}(1, 1) = 1 $ .

In the second example, $ \operatorname{lcm}(1, \gcd(3, 1)) + \operatorname{lcm}(1, \gcd(2, 2)) + \operatorname{lcm}(1, \gcd(1, 3)) + \operatorname{lcm}(2, \gcd(2, 1)) + \operatorname{lcm}(2, \gcd(1, 2)) + \operatorname{lcm}(3, \gcd(1, 1)) = \operatorname{lcm}(1, 1) + \operatorname{lcm}(1, 2) + \operatorname{lcm}(1, 1) + \operatorname{lcm}(2, 1) + \operatorname{lcm}(2, 1) + \operatorname{lcm}(3, 1) = 1 + 2 + 1 + 2 + 2 + 3 = 11 $

## 样例 #1

### 输入

```
3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
```

### 输出

```
11
```

## 样例 #3

### 输入

```
69228
```

### 输出

```
778304278
```



---

---
title: "Divisors and Table"
layout: "post"
diff: 提高+/省选-
pid: CF1792E
tag: ['数论', '素数判断,质数,筛法', '构造']
---

# Divisors and Table

## 题目描述

给定一张 $n \times n$ 的表格和一个正整数 $m = m_1 \times m_2$，表格第 $i$ 行第 $j$ 列的数 $a_{i, j} = i \times j$。

现在需要你求出 $m$ 的每个因子 $d$ 是否在表格中出现，若出现，则求出其出现在表格中的最小行号。

## 输入格式

第一行一个整数 $t$，表示测试用例的组数。

## 输出格式

对于每组测试用例，设 $d_1, d_2, \dots, d_k$ 为升序排序下 $m$ 的所有因子，$a_1, a_2, \dots, a_k$ 为这些因子在表格中出现的最小行号，特殊地，若 $d_i$ 不在表格中出现，则 $a_i = 0$。

输出一行两个整数 $s, X$。其中 $s$ 表示 $m$ 的因子在表格中出现的个数，$X$ 表示答案序列的异或和，形式化地，$X = a_1 \oplus a_2 \oplus \dots \oplus a_k$。

## 样例 #1

### 输入

```
3
3 72 1
10 10 15
6 1 210
```

### 输出

```
6 2
10 0
8 5
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
title: "Prime Problem"
layout: "post"
diff: 提高+/省选-
pid: CF45G
tag: ['数学', '素数判断,质数,筛法', '构造']
---

# Prime Problem

## 题目描述

In Berland prime numbers are fashionable — the respectable citizens dwell only on the floors with numbers that are prime numbers. The numismatists value particularly high the coins with prime nominal values. All the prime days are announced holidays!

Yet even this is not enough to make the Berland people happy. On the main street of the capital stand $ n $ houses, numbered from 1 to $ n $ . The government decided to paint every house a color so that the sum of the numbers of the houses painted every color is a prime number.

However it turned out that not all the citizens approve of this decision — many of them protest because they don't want many colored houses on the capital's main street. That's why it is decided to use the minimal possible number of colors. The houses don't have to be painted consecutively, but every one of $ n $ houses should be painted some color. The one-colored houses should not stand consecutively, any way of painting is acceptable.

There are no more than 5 hours left before the start of painting, help the government find the way when the sum of house numbers for every color is a prime number and the number of used colors is minimal.

## 输入格式

The single input line contains an integer $ n $ ( $ 2<=n<=6000 $ ) — the number of houses on the main streets of the capital.

## 输出格式

Print the sequence of $ n $ numbers, where the $ i $ -th number stands for the number of color for house number $ i $ . Number the colors consecutively starting from 1. Any painting order is allowed. If there are several solutions to that problem, print any of them. If there's no such way of painting print the single number -1.

## 样例 #1

### 输入

```
8
```

### 输出

```
1 2 2 1 1 1 1 2
```



---

---
title: "Vasiliy's Multiset"
layout: "post"
diff: 提高+/省选-
pid: CF706D
tag: ['素数判断,质数,筛法', '进制', '字典树 Trie']
---

# Vasiliy's Multiset

## 题目描述

Author has gone out of the stories about Vasiliy, so here is just a formal task description.

You are given $ q $ queries and a multiset $ A $ , initially containing only integer $ 0 $ . There are three types of queries:

1. "+ x" — add integer $ x $ to multiset $ A $ .
2. "- x" — erase one occurrence of integer $ x $ from multiset $ A $ . It's guaranteed that at least one $ x $ is present in the multiset $ A $ before this query.
3. "? x" — you are given integer $ x $ and need to compute the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/728a3690d3a76b81fb1ccb07b4c04b8d10b1870d.png), i.e. the maximum value of bitwise exclusive OR (also know as XOR) of integer $ x $ and some integer $ y $ from the multiset $ A $ .

Multiset is a set, where equal elements are allowed.

## 输入格式

The first line of the input contains a single integer $ q $ ( $ 1<=q<=200000 $ ) — the number of queries Vasiliy has to perform.

Each of the following $ q $ lines of the input contains one of three characters '+', '-' or '?' and an integer $ x_{i} $ ( $ 1<=x_{i}<=10^{9} $ ). It's guaranteed that there is at least one query of the third type.

Note, that the integer $ 0 $ will always be present in the set $ A $ .

## 输出格式

For each query of the type '?' print one integer — the maximum value of bitwise exclusive OR (XOR) of integer $ x_{i} $ and some integer from the multiset $ A $ .

## 说明/提示

After first five operations multiset $ A $ contains integers $ 0 $ , $ 8 $ , $ 9 $ , $ 11 $ , $ 6 $ and $ 1 $ .

The answer for the sixth query is integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/4b442d72cf0f109da9eae35430cf9dc9dfa35fdf.png) — maximum among integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/c712973b7cb6a6b393c3b423fc78dda636ebb034.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e9b3f94b7acd1861f4b82fb60d691b2bd163374e.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/1bf5d0b4ff98720973629f7915ae529e790539ba.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/9023c8bab139f08429005ae47d2d497f5795be9b.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e21b15be88af70287d01c0b8f13ae0d351197a9c.png).

## 样例 #1

### 输入

```
10
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3
? 8
? 11

```

### 输出

```
11
10
14
13

```



---

---
title: "Congruence Equation"
layout: "post"
diff: 提高+/省选-
pid: CF919E
tag: ['素数判断,质数,筛法', '概率论', '逆元']
---

# Congruence Equation

## 题目描述

Given an integer $ x $ . Your task is to find out how many positive integers $ n $ ( $ 1<=n<=x $ ) satisfy

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919E/02717f82c41ef4ed609db5d967f659c9784212e1.png) where $ a,b,p $ are all known constants.

## 输入格式

The only line contains four integers $ a,b,p,x $ ( $ 2<=p<=10^{6}+3 $ , $ 1<=a,b<p $ , $ 1<=x<=10^{12} $ ). It is guaranteed that $ p $ is a prime.

## 输出格式

Print a single integer: the number of possible answers $ n $ .

## 说明/提示

In the first sample, we can see that $ n=2 $ and $ n=8 $ are possible answers.

## 样例 #1

### 输入

```
2 3 5 8

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 6 7 13

```

### 输出

```
1

```

## 样例 #3

### 输入

```
233 233 10007 1

```

### 输出

```
1

```



---

---
title: "Mahmoud and Ehab and another array construction task"
layout: "post"
diff: 提高+/省选-
pid: CF959D
tag: ['枚举', '素数判断,质数,筛法']
---

# Mahmoud and Ehab and another array construction task

## 题目描述

Mahmoud has an array $ a $ consisting of $ n $ integers. He asked Ehab to find another array $ b $ of the same length such that:

- $ b $ is lexicographically greater than or equal to $ a $ .
- $ b_{i}>=2 $ .
- $ b $ is pairwise coprime: for every $ 1<=i<j<=n $ , $ b_{i} $ and $ b_{j} $ are coprime, i. e. $ GCD(b_{i},b_{j})=1 $ , where $ GCD(w,z) $ is the greatest common divisor of $ w $ and $ z $ .

Ehab wants to choose a special array so he wants the lexicographically minimal array between all the variants. Can you find it?

An array $ x $ is lexicographically greater than an array $ y $ if there exists an index $ i $ such than $ x_{i}>y_{i} $ and $ x_{j}=y_{j} $ for all $ 1<=j<i $ . An array $ x $ is equal to an array $ y $ if $ x_{i}=y_{i} $ for all $ 1<=i<=n $ .

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=10^{5}) $ , the number of elements in $ a $ and $ b $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ $ (2<=a_{i}<=10^{5}) $ , the elements of $ a $ .

## 输出格式

Output $ n $ space-separated integers, the $ i $ -th of them representing $ b_{i} $ .

## 说明/提示

Note that in the second sample, the array is already pairwise coprime so we printed it.

## 样例 #1

### 输入

```
5
2 3 5 4 13

```

### 输出

```
2 3 5 7 11 
```

## 样例 #2

### 输入

```
3
10 3 7

```

### 输出

```
10 3 7 
```



---

---
title: "Perfect Groups"
layout: "post"
diff: 提高+/省选-
pid: CF980D
tag: ['数学', '素数判断,质数,筛法', '概率论']
---

# Perfect Groups

## 题目描述

SaMer has written the greatest test case of all time for one of his problems. For a given array of integers, the problem asks to find the minimum number of groups the array can be divided into, such that the product of any pair of integers in the same group is a perfect square.

Each integer must be in exactly one group. However, integers in a group do not necessarily have to be contiguous in the array.

SaMer wishes to create more cases from the test case he already has. His test case has an array $ A $ of $ n $ integers, and he needs to find the number of contiguous subarrays of $ A $ that have an answer to the problem equal to $ k $ for each integer $ k $ between $ 1 $ and $ n $ (inclusive).

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1 \leq n \leq 5000 $ ), the size of the array.

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , $ \dots $ , $ a_n $ ( $ -10^8 \leq a_i \leq 10^8 $ ), the values of the array.

## 输出格式

Output $ n $ space-separated integers, the $ k $ -th integer should be the number of contiguous subarrays of $ A $ that have an answer to the problem equal to $ k $ .

## 样例 #1

### 输入

```
2
5 5

```

### 输出

```
3 0

```

## 样例 #2

### 输入

```
5
5 -4 2 1 8

```

### 输出

```
5 5 3 2 0

```

## 样例 #3

### 输入

```
1
0

```

### 输出

```
1

```



---

