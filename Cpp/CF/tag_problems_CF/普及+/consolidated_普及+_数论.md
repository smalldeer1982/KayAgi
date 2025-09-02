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
title: "LCM Sum (easy version)"
layout: "post"
diff: 普及+/提高
pid: CF1712E1
tag: ['数论']
---

# LCM Sum (easy version)

## 题目描述

给你两个正整数 $l$ 和 $r$。

计算不同的整数三元组 $(i,j,k)$ 的数量，使得 $l\leq i<j<k\leq r$ 且 $\operatorname{lcm}(i,j,k)\ge i+j+k$。

$\operatorname{lcm}(i,j,k)$ 表示整数 $i,j,k$ 的最小公倍数 $(LCM)$ 。

## 输入格式

**本题单测试点内有多组测试数据。**

第一行包含一个整数 $t(1\leq t\leq 5)$，表示测试组数。

对于每组数据：

每行两个正整数 $l$ 和 $r(1\leq l \leq r \leq 2\times 10^5,l+2 \leq r)$。

## 输出格式

对于每组数据，输出一行一个整数表示答案。

### 输入输出样例

**输入 #1**
```
5
1 4
3 5
8 86
68 86
6 86868
```

**输出 #1**
```
3
1
78975
969
109229059713337
```

### 样例解释

在第一个测试用例中，有 $3$ 个合适的三元组：

- $(1,2,3)$，

- $(1,3,4)$，

- $(2,3,4)$。

在第二个测试用例中，有 $1$ 个合适的三元组：

- $(3,4,5)$。

## 样例 #1

### 输入

```
5
1 4
3 5
8 86
68 86
6 86868
```

### 输出

```
3
1
78975
969
109229059713337
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
title: "Divisibility Test"
layout: "post"
diff: 普及+/提高
pid: CF1912D
tag: ['数论', '进制']
---

# Divisibility Test

## 题目描述

Daisy has recently learned divisibility rules for integers and she is fascinated by them. One of the tests she learned is a divisibility test by 3. You can find a sum of all digits of a decimal number and check if the resulting sum is divisible by 3. Moreover, the resulting sum of digits is congruent modulo 3 to the original number — the remainder modulo 3 is preserved. For example, $ 75 \equiv 7 + 5 \pmod 3 $ . Daisy is specifically interested in such remainder preserving divisibility tests.

There are more examples like that that she learned for decimal integers (integers base 10):

- To test divisibility modulo 11, find an alternating sum of digits. Counting digits from the last (least significant) digit, add digits on odd positions (the last, 3rd to the last, etc) and subtract digits on even positions (2nd to the last, 4th to the last, etc) to get the sum that is congruent modulo 11 to the original number. For example, $ 123 \equiv 1 - 2 + 3 \pmod {11} $ .
- To test divisibility modulo 4, keep the last two digits. Their value is congruent modulo 4 to the original number. For example, $ 876543 \equiv 43 \pmod 4 $ .
- To test divisibility modulo 7, find an alternating sum of groups of three digits. For example, $ 4389328 \equiv 4 - 389 + 328 \pmod 7 $ .

Similar tests can be found in other bases. For example, to test divisibility modulo 5 for octal numbers (base 8), find an alternating sum of groups of two digits. For example, $ 1234_8 \equiv -12_8 + 34_8 \pmod 5 $ .

Daisy wants to find such rules for a given base $ b $ . She is interested in three kinds of divisibility rules:

- Kind 1 — take the last $ k $ digits of an integer in base $ b $ .
- Kind 2 — take a sum of groups of $ k $ digits of an integer in base $ b $ .
- Kind 3 — take an alternating sum of groups of $ k $ digits of an integer in base $ b $ .

It is not always possible to find such a divisibility rule. For example, in base 10 there is no such test for divisibility modulo 6, even though different approaches to testing divisibility by 6 exist.

Given base $ b $ and modulo $ n $ , Daisy wants to know the smallest group size $ k $ for which such a divisibility test exits.

## 输入格式

There are several tests in the input. The first line of the input contains an integer $ t $ — the number of tests. The next $ t $ lines describe the tests.

Each test consists of a line with two integers $ b $ and $ n $ — the base and the modulo ( $ b, n \ge 2 $ ). The sum of all $ b $ values in the input does not exceed $ 10^6 $ , and the sum of all $ n $ values in the input does not exceed $ 10^6 $ .

## 输出格式

Write $ t $ lines — a line for each test in the input. On a line for a test write a single integer $ 0 $ if the divisibility test for a given $ b $ and $ n $ does not exist. Otherwise, write two integers $ a $ and $ k $ , where $ a $ is the kind of the divisibility test (1, 2, or 3) and $ k $ is the number of digits in a group for the test, such that $ k $ is the lowest among all possible divisiblity tests for the given $ b $ and $ n $ .

## 样例 #1

### 输入

```
6
10 3
10 11
10 4
10 7
8 5
10 6
```

### 输出

```
2 1
3 1
1 2
3 3
3 2
0
```



---

---
title: "GCD on a grid"
layout: "post"
diff: 普及+/提高
pid: CF1955G
tag: ['动态规划 DP', '搜索', '数论']
---

# GCD on a grid

## 题目描述

Not long ago, Egor learned about the Euclidean algorithm for finding the greatest common divisor of two numbers. The greatest common divisor of two numbers $ a $ and $ b $ is the largest number that divides both $ a $ and $ b $ without leaving a remainder. With this knowledge, Egor can solve a problem that he once couldn't.

Vasily has a grid with $ n $ rows and $ m $ columns, and the integer $ {a_i}_j $ is located at the intersection of the $ i $ -th row and the $ j $ -th column. Egor wants to go from the top left corner (at the intersection of the first row and the first column) to the bottom right corner (at the intersection of the last row and the last column) and find the greatest common divisor of all the numbers along the path. He is only allowed to move down and to the right. Egor has written down several paths and obtained different GCD values. He became interested in finding the maximum possible GCD.

Unfortunately, Egor is tired of calculating GCDs, so he asks for your help in finding the maximum GCD of the integers along the path from the top left corner to the bottom right corner of the grid.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le {10}^{4} $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 100 $ ) — the number of rows and columns of the grid.

Then, there are $ n $ lines, where the $ i $ -th line contains $ m $ integers $ (1 \le a_{i,j} \le {10}^{6} $ ) — the integers written in the $ i $ -th row and the $ j $ -th column of the grid.

It is guaranteed that the sum of $ n \cdot m $ does not exceed $ 2 \cdot {10}^{5} $ over all test cases.

## 输出格式

For each test case, output the maximum possible GCD along the path from the top left cell to the bottom right cell in a separate line.

## 样例 #1

### 输入

```
3
2 3
30 20 30
15 25 40
3 3
12 4 9
3 12 2
8 3 12
2 4
2 4 6 8
1 3 6 9
```

### 输出

```
10
3
1
```



---

---
title: "Nikita and LCM"
layout: "post"
diff: 普及+/提高
pid: CF1977C
tag: ['动态规划 DP', '数论']
---

# Nikita and LCM

## 题目描述

Nikita is a student passionate about number theory and algorithms. He faces an interesting problem related to an array of numbers.

Suppose Nikita has an array of integers $ a $ of length $ n $ . He will call a subsequence $ ^\dagger $ of the array special if its [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) is not contained in $ a $ . The LCM of an empty subsequence is equal to $ 0 $ .

Nikita wonders: what is the length of the longest special subsequence of $ a $ ? Help him answer this question!

 $ ^\dagger $ A sequence $ b $ is a subsequence of $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements, without changing the order of the remaining elements. For example, $ [5,2,3] $ is a subsequence of $ [1,5,7,8,2,4,3] $ .

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 2000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, output a single integer — the length of the longest special subsequence of $ a $ .

## 说明/提示

In the first test case, the LCM of any non-empty subsequence is contained in $ a $ , so the answer is $ 0 $ .

In the second test case, we can take the subsequence $ [3, 2, 10, 1] $ , its LCM is equal to $ 30 $ , which is not contained in $ a $ .

In the third test case, we can take the subsequence $ [2, 3, 6, 100\,003] $ , its LCM is equal to $ 600\,018 $ , which is not contained in $ a $ .

## 样例 #1

### 输入

```
6
5
1 2 4 8 16
6
3 2 10 20 60 1
7
2 3 4 6 12 100003 1200036
9
2 42 7 3 6 7 7 1 6
8
4 99 57 179 10203 2 11 40812
1
1
```

### 输出

```
0
4
4
5
8
0
```



---

---
title: "Beauty of the mountains"
layout: "post"
diff: 普及+/提高
pid: CF1982D
tag: ['数论', '前缀和']
---

# Beauty of the mountains

## 题目描述

Nikita loves mountains and has finally decided to visit the Berlyand mountain range! The range was so beautiful that Nikita decided to capture it on a map. The map is a table of $ n $ rows and $ m $ columns, with each cell containing a non-negative integer representing the height of the mountain.

He also noticed that mountains come in two types:

- With snowy caps.
- Without snowy caps.

Nikita is a very pragmatic person. He wants the sum of the heights of the mountains with snowy caps to be equal to the sum of the heights of the mountains without them. He has arranged with the mayor of Berlyand, Polikarp Polikarpovich, to allow him to transform the landscape.

Nikita can perform transformations on submatrices of size $ k \times k $ as follows: he can add an integer constant $ c $ to the heights of the mountains within this area, but the type of the mountain remains unchanged. Nikita can choose the constant $ c $ independently for each transformation. Note that $ c $ can be negative.

Before making the transformations, Nikita asks you to find out if it is possible to achieve equality of the sums, or if it is impossible. It doesn't matter at what cost, even if the mountains turn into canyons and have negative heights.

If only one type of mountain is represented on the map, then the sum of the heights of the other type of mountain is considered to be zero.

## 输入格式

Each test consists of several test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. This is followed by a description of test cases.

The first line of each test case contains three integers $ n, m, k $ ( $ 1 \le n, m \le 500, 1 \le k \le min(n, m) $ ).

The next $ n $ lines of each test case contain $ m $ integers $ a_{i j} $ ( $ 0 \le a_{i j} \le 10^{9} $ ) — the initial heights of the mountains.

The next $ n $ binary strings of length $ m $ for each test case determine the type of mountain, ' $ 0 $ ' — with snowy caps, ' $ 1 $ ' — without them.

It is guaranteed that the sum of $ n \cdot m $ for all test cases does not exceed $ 250\,000 $ .

## 输出格式

For each test case, output "YES" without quotes if it is possible to equalize the sums of the mountain heights, otherwise output "NO" without quotes. You can output each letter in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

The mountain array from the first test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/c2cad4d039daa4458ac8328be539df0f39115b35.png)Initially, the sum of the heights of the mountains with snowy caps is $ 11 + 3 + 4 + 3 + 0 + 1 + 15 = 37 $ , and without them is $ 7 + 2 = 9 $ .

To equalize these sums, we can perform two transformations:

First transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/26401332927c782774104130bd94cec3d8dea8ef.png)Note that the constant $ c $ can be negative.

After the first transformation, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/8985a2e394a22468e2807bb57386a8c62bc3f888.png)Second transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/83de4303ed287bb4d20cf33c8ab2494ed765c011.png)As a result, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/1dfddde2b777b3b24d753c3d41d8fe42319ee24e.png)The sum of the heights of the mountains with snowy caps is $ 17 + 9 + 9 - 16 - 20 - 19 + 15 = -5 $ , and without them is $ 7 - 12 = -5 $ , thus the answer is YES.

## 样例 #1

### 输入

```
8
3 3 2
7 11 3
4 2 3
0 1 15
100
010
000
4 4 3
123 413 24 233
123 42 0 216
22 1 1 53
427 763 22 6
0101
1111
1010
0101
3 3 2
2 1 1
1 1 2
1 5 4
010
101
010
3 3 2
2 1 1
1 1 2
1 5 3
010
101
010
3 4 3
46 49 50 1
19 30 23 12
30 25 1 46
1000
0100
0010
5 4 4
39 30 0 17
22 42 30 13
10 44 46 35
12 19 9 39
21 0 45 40
1000
1111
0011
0111
1100
2 2 2
3 4
6 7
00
00
2 2 2
0 0
2 0
01
00
```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
YES
```



---

---
title: ""a" String Problem"
layout: "post"
diff: 普及+/提高
pid: CF1984D
tag: ['数论', '哈希 hashing']
---

# "a" String Problem

## 题目描述

You are given a string $ s $ consisting of lowercase Latin characters. Count the number of nonempty strings $ t \neq $ " $ \texttt{a} $ " such that it is possible to partition $ ^{\dagger} $ $ s $ into some substrings satisfying the following conditions:

- each substring either equals $ t $ or " $ \texttt{a} $ ", and
- at least one substring equals $ t $ .

 $ ^{\dagger} $ A partition of a string $ s $ is an ordered sequence of some $ k $ strings $ t_1, t_2, \ldots, t_k $ (called substrings) such that $ t_1 + t_2 + \ldots + t_k = s $ , where $ + $ represents the concatenation operation.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The only line of each test case contains a string $ s $ consisting of lowercase Latin characters ( $ 2 \leq |s| \leq 2 \cdot 10^5 $ ).

The sum of $ |s| $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of nonempty strings $ t \neq $ " $ \texttt{a} $ " that satisfy all constraints.

## 说明/提示

In the first test case, $ t $ can be " $ \texttt{aa} $ ", " $ \texttt{aaa} $ ", " $ \texttt{aaaa} $ ", or the full string.

In the second test case, $ t $ can be " $ \texttt{b} $ ", " $ \texttt{bab} $ ", " $ \texttt{ba} $ ", or the full string.

In the third test case, the only such $ t $ is the full string.

## 样例 #1

### 输入

```
8
aaaaa
baba
cabacb
aaabaaa
bitset
ab
abbaaaabbb
yearnineteeneightyfour
```

### 输出

```
4
4
1
16
1
2
3
1
```



---

---
title: "Beautiful Array"
layout: "post"
diff: 普及+/提高
pid: CF1986E
tag: ['数论']
---

# Beautiful Array

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ and an integer $ k $ . You need to make it beautiful with the least amount of operations.

Before applying operations, you can shuffle the array elements as you like. For one operation, you can do the following:

- Choose an index $ 1 \leq i \leq n $ ,
- Make $ a_i = a_i + k $ .

The array $ b_1, b_2, \ldots, b_n $ is beautiful if $ b_i = b_{n - i + 1} $ for all $ 1 \leq i \leq n $ .

Find the minimum number of operations needed to make the array beautiful, or report that it is impossible.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of sets of input data. Then follows their description.

The first line of each set of input data contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 10^5 $ , $ 1 \leq k \leq 10^9 $ ) — the size of the array $ a $ and the number $ k $ from the problem statement.

The second line of each set of input data contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all sets of input data does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each set of input data, output the minimum number of operations needed to make the array beautiful, or $ -1 $ if it is impossible.

## 说明/提示

In the first set of input data, the array is already beautiful.

In the second set of input data, you can shuffle the array before the operations and perform the operation with index $ i = 1 $ for $ 83966524 $ times.

In the third set of input data, you can shuffle the array $ a $ and make it equal to $ [2, 3, 1] $ . Then apply the operation with index $ i = 3 $ to get the array $ [2, 3, 2] $ , which is beautiful.

In the eighth set of input data, there is no set of operations and no way to shuffle the elements to make the array beautiful.

In the ninth set of input data, the array is already beautiful.

## 样例 #1

### 输入

```
11
1 1000000000
1
2 1
624323799 708290323
3 1
3 2 1
4 1
7 1 5 3
5 1
11 2 15 7 10
7 1
1 8 2 16 8 16 31
13 1
2 1 1 3 3 11 12 22 45 777 777 1500 74
10 2
1 2 1 2 1 2 1 2 1 2
11 2
1 2 1 2 1 2 1 2 1 2 1
13 3
2 3 9 14 17 10 22 20 18 30 1 4 28
5 1
2 3 5 3 5
```

### 输出

```
0
83966524
1
4
6
1
48
-1
0
14
0
```



---

---
title: "Prime XOR Coloring"
layout: "post"
diff: 普及+/提高
pid: CF1991D
tag: ['数论', '位运算', 'Ad-hoc']
---

# Prime XOR Coloring

## 题目描述

You are given an undirected graph with $ n $ vertices, numbered from $ 1 $ to $ n $ . There is an edge between vertices $ u $ and $ v $ if and only if $ u \oplus v $ is a [prime number](https://en.wikipedia.org/wiki/Prime_number), where $ \oplus $ denotes the [bitwise XOR operator](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Color all vertices of the graph using the minimum number of colors, such that no two vertices directly connected by an edge have the same color.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of test cases follows.

The only line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the graph.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two lines.

The first line should contain a single integer $ k $ ( $ 1 \le k \le n $ ) — the minimum number of colors required.

The second line should contain $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le k $ ) — the color of each vertex.

If there are multiple solutions, output any of them.

## 说明/提示

In the first test case, the minimum number of colors is $ 1 $ , because there is only one vertex.

In the second test case, the minimum number of colors is $ 2 $ , because there is an edge connecting $ 1 $ and $ 2 $ ( $ 1 \oplus 2 = 3 $ , which is a prime number).

In the third test case, the minimum number of colors is still $ 2 $ , because $ 2 $ and $ 3 $ can be colored the same since there is no edge between $ 2 $ and $ 3 $ ( $ 2 \oplus 3 = 1 $ , which is not a prime number).

In the fourth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the fifth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the sixth test case, it can be shown that the minimum number of colors is $ 4 $ .

## 样例 #1

### 输入

```
6
1
2
3
4
5
6
```

### 输出

```
1
1
2
1 2
2
1 2 2
3
1 2 2 3
3
1 2 2 3 3
4
1 2 2 3 3 4
```



---

---
title: "Valuable Cards"
layout: "post"
diff: 普及+/提高
pid: CF1992F
tag: ['贪心', '数论']
---

# Valuable Cards

## 题目描述

In his favorite cafe Kmes once again wanted to try the herring under a fur coat. Previously, it would not have been difficult for him to do this, but the cafe recently introduced a new purchasing policy.

Now, in order to make a purchase, Kmes needs to solve the following problem: $ n $ cards with prices for different positions are laid out in front of him, on the $ i $ -th card there is an integer $ a_i $ , among these prices there is no whole positive integer $ x $ .

Kmes is asked to divide these cards into the minimum number of bad segments (so that each card belongs to exactly one segment). A segment is considered bad if it is impossible to select a subset of cards with a product equal to $ x $ . All segments, in which Kmes will divide the cards, must be bad.

Formally, the segment $ (l, r) $ is bad if there are no indices $ i_1 < i_2 < \ldots < i_k $ such that $ l \le i_1, i_k \le r $ , and $ a_{i_1} \cdot a_{i_2} \ldots \cdot a_{i_k} = x $ .

Help Kmes determine the minimum number of bad segments in order to enjoy his favorite dish.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

The first line of each set of input data gives you $ 2 $ integers $ n $ and $ x $ ( $ 1 \le n \le 10^5, 2 \le x \le 10^5 $ ) — the number of cards and the integer, respectively.

The second line of each set of input data contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 2 \cdot 10^5, a_i \neq x $ ) — the prices on the cards.

It is guaranteed that the sum of $ n $ over all sets of test data does not exceed $ 10^5 $ .

## 输出格式

For each set of input data, output the minimum number of bad segments.

## 样例 #1

### 输入

```
8
6 4
2 3 6 2 1 2
9 100000
50000 25000 12500 6250 3125 2 4 8 16
5 2
1 1 1 1 1
8 6
4 3 4 3 4 3 4 3
7 12
6 11 1 3 11 10 2
10 5
2 4 4 2 4 4 4 3 1 1
7 8
4 6 5 1 2 4 1
8 27
3 9 17 26 2 20 9 3
```

### 输出

```
3
2
1
1
2
1
3
3
```



---

---
title: "Funny Game"
layout: "post"
diff: 普及+/提高
pid: CF1994D
tag: ['数论', '鸽笼原理']
---

# Funny Game

## 题目描述

Vanya has a graph with $ n $ vertices (numbered from $ 1 $ to $ n $ ) and an array $ a $ of $ n $ integers; initially, there are no edges in the graph. Vanya got bored, and to have fun, he decided to perform $ n - 1 $ operations.

Operation number $ x $ (operations are numbered in order starting from $ 1 $ ) is as follows:

- Choose $ 2 $ different numbers $ 1 \leq u,v \leq n $ , such that $ |a_u - a_v| $ is divisible by $ x $ .
- Add an undirected edge between vertices $ u $ and $ v $ to the graph.

Help Vanya get a connected $ ^{\text{∗}} $ graph using the $ n - 1 $ operations, or determine that it is impossible.

 $ ^{\text{∗}} $ A graph is called connected if it is possible to reach any vertex from any other by moving along the edges.

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{3} $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains the number $ n $ ( $ 1 \leq n \leq 2000 $ ) — the number of vertices in the graph.

The second line of each test case contains $ n $ numbers $ a_1, a_2, \cdots a_n $ ( $ 1 \leq a_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, if there is no solution, then output "No" (without quotes).

Otherwise, output "Yes" (without quotes), and then output $ n - 1 $ lines, where in the $ i $ -th line, output the numbers $ u $ and $ v $ that need to be chosen for operation $ i $ .

You can output each letter in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

Let's consider the second test case.

- First operation $ (x = 1) $ : we can connect vertices $ 4 $ and $ 1 $ , since $ |a_4 - a_1| = |13 - 99| = |-86| = 86 $ , and $ 86 $ is divisible by $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1994D/f454bbc6f9e0e97455a35659663326d5f1b7732f.png)- Second operation $ (x = 2) $ : we can connect vertices $ 2 $ and $ 1 $ , since $ |a_2 - a_1| = |7 - 99| = |-92| = 92 $ , and $ 92 $ is divisible by $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1994D/9f40b6b2ea3eceff5de09b1a367a88713eeb53f7.png)- Third operation $ (x = 3) $ : we can connect vertices $ 3 $ and $ 2 $ , since $ |a_3 - a_2| = |1 - 7| = |-6| = 6 $ , and $ 6 $ is divisible by $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1994D/f0db9ab0c3e7fd24f5ff083e0932405157cd111f.png) From the picture, it can be seen that a connected graph is obtained.

## 样例 #1

### 输入

```
8
2
1 4
4
99 7 1 13
5
10 2 31 44 73
5
87 6 81 44 32
5
62 35 33 79 16
5
6 51 31 69 42
5
52 63 25 21 5
12
33 40 3 11 31 43 37 8 50 5 12 22
```

### 输出

```
YES
2 1
YES
4 1
2 1
3 2
YES
5 1
4 1
3 1
2 1
YES
4 1
3 1
2 1
5 4
YES
3 1
5 1
2 1
4 2
YES
4 1
5 1
2 1
3 2
YES
2 1
5 2
3 1
4 3
YES
9 1
12 9
11 1
10 1
6 1
7 6
2 1
8 2
5 2
3 1
4 1
```



---

---
title: "Sakurako's Task"
layout: "post"
diff: 普及+/提高
pid: CF2008G
tag: ['数论', '构造']
---

# Sakurako's Task

## 题目描述

Sakurako has prepared a task for you:

She gives you an array of $ n $ integers and allows you to choose $ i $ and $ j $ such that $ i \neq j $ and $ a_i \ge a_j $ , and then assign $ a_i = a_i - a_j $ or $ a_i = a_i + a_j $ . You can perform this operation any number of times for any $ i $ and $ j $ , as long as they satisfy the conditions.

Sakurako asks you what is the maximum possible value of $ mex_k $ $ ^{\text{∗}} $ of the array after any number of operations.

 $ ^{\text{∗}} $ $ mex_k $ is the $ k $ -th non-negative integer that is absent in the array. For example, $ mex_1(\{1,2,3 \})=0 $ , since $ 0 $ is the first element that is not in the array, and $ mex_2(\{0,2,4 \})=3 $ , since $ 3 $ is the second element that is not in the array.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1\le n\le 2\cdot 10^5,1\le k\le 10^9 $ ) — the number of elements in the array and the value $ k $ for $ mex_k $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots,a_n $ ( $ 1\le a_i\le 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the maximum $ mex_k $ that can be achieved through the operations.

## 样例 #1

### 输入

```
6
1 3
3
2 10
1 1
3 1
1 2 3
3 2
1 2 4
4 5
2 2 2 16
4 5
2 2 2 3
```

### 输出

```
2
11
3
4
8
8
```



---

---
title: "Natlan Exploring"
layout: "post"
diff: 普及+/提高
pid: CF2037G
tag: ['动态规划 DP', '数论', '莫比乌斯反演', '容斥原理']
---

# Natlan Exploring

## 题目描述

You are exploring the stunning region of Natlan! This region consists of $ n $ cities, and each city is rated with an attractiveness $ a_i $ . A directed edge exists from City $ i $ to City $ j $ if and only if $ i < j $ and $ \gcd(a_i,a_j)\neq 1 $ , where $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Starting from City $ 1 $ , your task is to determine the total number of distinct paths you can take to reach City $ n $ , modulo $ 998\,244\,353 $ . Two paths are different if and only if the set of cities visited is different.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the number of cities.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 2 \leq a_i \leq 10^6 $ ) — the attractiveness of each city.

## 输出格式

Output the total number of distinct paths you can take to reach City $ n $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the five paths are the following:

- City $ 1\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 3\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 4\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 4\rightarrow $ City $ 5 $

In the second example, the two paths are the following:

- City $ 1\rightarrow $ City $ 3\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 3\rightarrow $ City $ 5 $

## 样例 #1

### 输入

```
5
2 6 3 4 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
4 196 2662 2197 121
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
3 6 8 9 11 12 20
```

### 输出

```
7
```

## 样例 #4

### 输入

```
2
2 3
```

### 输出

```
0
```



---

---
title: "Shohag Loves XOR (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF2039C2
tag: ['数学', '数论', '枚举', '位运算']
---

# Shohag Loves XOR (Hard Version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ x \oplus y $ is divisible $ ^{\text{∗}} $ by either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ a $ is divisible by the number $ b $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains two space-separated integers $ x $ and $ m $ ( $ 1 \le x \le 10^6 $ , $ 1 \le m \le 10^{18} $ ).

It is guaranteed that the sum of $ x $ over all test cases does not exceed $ 10^7 $ .

## 输出格式

For each test case, print a single integer — the number of suitable $ y $ .

## 说明/提示

In the first test case, for $ x = 7 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 10 $ , and they are $ 1 $ , $ 7 $ , and $ 9 $ .

- $ y = 1 $ is valid because $ x \oplus y = 7 \oplus 1 = 6 $ and $ 6 $ is divisible by $ y = 1 $ .
- $ y = 7 $ is valid because $ x \oplus y = 7 \oplus 7 = 0 $ and $ 0 $ is divisible by both $ x = 7 $ and $ y = 7 $ .
- $ y = 9 $ is valid because $ x \oplus y = 7 \oplus 9 = 14 $ and $ 14 $ is divisible by $ x = 7 $ .

## 样例 #1

### 输入

```
5
7 10
2 3
6 4
1 6
4 1
```

### 输出

```
3
2
2
6
1
```



---

---
title: "Shohag Loves GCD"
layout: "post"
diff: 普及+/提高
pid: CF2039D
tag: ['贪心', '数论', '素数判断,质数,筛法', '构造', '标签475']
---

# Shohag Loves GCD

## 题目描述

Shohag 拥有一个整数 $n$ 和一个包含 $m$ 个不同整数的集合 $S$。请帮助他找到字典序最大*的整数数组 $a_1, a_2, \ldots, a_n$，使得对于每个 $1 \le i \le n$ 有 $a_i \in S$ ，并且满足对所有 $1 \le i < j \le n$ 有 $a_{\gcd(i, j)} \neq \gcd(a_i, a_j)$†，或者说明不存在这样的数组。

*一个数组 $a$ 如果在第一个不同的位置上比数组 $b$ 有更大的元素，则称其为字典序大于数组 $b$（假设两个数组长度相同）。

†$\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的[最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

## 输入格式

第一行包含一个整数 $t$ ($1 \le t \le 10^4$) — 测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$ ($1 \le m \le n \le 10^5$)。

每个测试用例的第二行包含 $m$ 个按递增顺序排列的不同整数，表示集合 $S$ 的元素 ($1 \le x \le n$ 对于每个 $x \in S$)。

保证所有测试用例中 $n$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果无解则输出 $-1$，否则输出 $n$ 个整数 —— 满足条件的字典序最大的整数数组。

## 说明/提示

在第一个测试用例中，数组中的每个元素都属于给定的集合 $S = \{3, 4, 6\}$，并且数组的所有索引对都满足必要的条件。特别是对于对 $(2, 3)$，有 $a_{\gcd(2, 3)} = a_1 = 6$ 而 $\gcd(a_2, a_3) = \gcd(4, 4) = 4$，因此它们不相等。尽管存在其他满足条件的数组，但这个是其中字典序最大的。

在第三个测试用例中，由于我们只能使用数组 $a = [2, 2]$，但对于该数组，对于对 $(1, 2)$，有 $a_{\gcd(1, 2)} = a_1 = 2$ 而 $\gcd(a_1, a_2) = \gcd(2, 2) = 2$，因此它们相等，这是不允许的！所以没有解决方案。

## 样例 #1

### 输入

```
3
6 3
3 4 6
1 1
1
2 1
2
```

### 输出

```
6 4 4 3 4 3 
1 
-1
```



---

---
title: "Problem about GCD"
layout: "post"
diff: 普及+/提高
pid: CF2043D
tag: ['数论']
---

# Problem about GCD

## 题目描述

给出三个整数 $l,r,G$，要求找到一个数对 $A,B$ 满足 $l\le A\le B\le r$ 且 $\gcd (A,B) = G$，并且满足 $\left\vert A-B \right\vert$ 最大。

如果有多组解，选择 $A$ 的值最小的一个。

## 输入格式

第一行一个整数 $T$，表示测试点数量。

## 输出格式

$T$ 行，每行两个数 $A,B$ 表示该测试点的答案。

## 说明/提示

$1\le t\le 10^3$

$1\le l\le r\le 10^{18}$

$1\le G\le 10^{18}$

## 样例 #1

### 输入

```
4
4 8 2
4 8 3
4 8 4
5 7 6
```

### 输出

```
4 6
-1 -1
4 8
6 6
```



---

---
title: "Tree Destruction"
layout: "post"
diff: 普及+/提高
pid: CF2050G
tag: ['数论']
---

# Tree Destruction

## 题目描述

给定一棵有 $n$ 个顶点的树。你可以一次选择两个顶点 $a$ 和 $b$，然后删除从 $a$ 到 $b$ 路径上的所有顶点，包括顶点本身。如果选择 $a=b$，则只会移除一个顶点。


你的任务是找到从树中移除路径后可以形成的连接组件的最大数量。


树是一个没有环的连通图。


连通组件是一组顶点的集合，其中任何顶点都有一条沿边缘的路径到达集合中的任何其他顶点（不可能到达不属于该集合的顶点）。

## 输入格式

输入的第一行包含一个整数 $t（1≤t≤10^4）$，用于表示测试用例的数量。


每个测试用例的第一行包含一个整数 $n（2≤n≤2\times 10^5）$，用于表示树的大小。


接下来的 $n−1$ 行包含两个整数 $u$ 和 $v（1≤u,v≤n, u≠v）$，用于表示由一条边连接的顶点。可以保证这些边形成一棵树。


保证所有测试用例的 $n$ 之和不超过 $2\times 10^5$。

## 输出格式

对于每个测试用例，输出一个整数，用于表示使用所描述的操作可以实现的连接组件的最大数量。$\\$
——By hyacinth_lpy.

## 样例 #1

### 输入

```
6
2
1 2
5
1 2
2 3
3 4
3 5
4
1 2
2 3
3 4
5
2 1
3 1
4 1
5 4
6
2 1
3 1
4 1
5 3
6 3
6
2 1
3 2
4 2
5 3
6 4
```

### 输出

```
1
3
2
3
4
3
```



---

---
title: "Skibidus and Capping"
layout: "post"
diff: 普及+/提高
pid: CF2065G
tag: ['数论', '素数判断,质数,筛法']
---

# Skibidus and Capping

## 题目描述

Skibidus 被 Amog 外星人绑架了！Skibidus 试图以言辞自辩脱身，但 Amog 外星人不相信他。为了证明自己不是在撒谎(capping)，Amog 外星人要求他解决以下问题：

一个整数 $x$ 如果可以写成 $p \cdot q$ 的形式（$p$ 和 $q$ 均为质数，可以相同），则称其为半质数。例如，$9$ 是半质数，因为它可以写成 $3 \cdot 3$，而 $3$ 是质数。

Skibidus 得到了一个包含 $n$ 个整数的数组 $a$。他需要统计所有满足 $i \leq j$ 且 $\operatorname{lcm}(a_i, a_j)$ $ ^{\text{∗}} $ 为半质数的索引对 $(i, j)$ 的数量。

$ ^{\text{∗}} $ 给定两个整数 $x$ 和 $y$，$\operatorname{lcm}(x, y)$ 表示 $x$ 与 $y$ 的 [最小公倍数](https://zh.wikipedia.org/wiki/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B8)。

## 输入格式

第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$)，表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$ ($2 \leq n \leq 2 \cdot 10^5$)。

接下来一行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ($2 \leq a_i \leq n$)。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行一个整数，表示满足条件的有序索引对 $(i, j)$ 的数量。

## 说明/提示

在第一个测试用例中，满足条件的 $5$ 个索引对分别为 $(1, 3)$、$(1, 4)$、$(2, 3)$、$(2, 4)$ 和 $(4, 4)$。

## 样例 #1

### 输入

```
3
4
2 2 3 4
6
2 2 3 4 5 6
9
2 2 4 5 7 8 9 3 5
```

### 输出

```
5
12
18
```



---

---
title: "Prime Swaps"
layout: "post"
diff: 普及+/提高
pid: CF432C
tag: ['数论']
---

# Prime Swaps

## 题目描述

You have an array $ a[1],a[2],...,a[n] $ , containing distinct integers from $ 1 $ to $ n $ . Your task is to sort this array in increasing order with the following operation (you may need to apply it multiple times):

- choose two indexes, $ i $ and $ j $ ( $ 1<=i&lt;j<=n $ ; $ (j-i+1) $ is a prime number);
- swap the elements on positions $ i $ and $ j $ ; in other words, you are allowed to apply the following sequence of assignments: $ tmp=a[i],a[i]=a[j],a[j]=tmp $ ( $ tmp $ is a temporary variable).

You do not need to minimize the number of used operations. However, you need to make sure that there are at most $ 5n $ operations.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ . The next line contains $ n $ distinct integers $ a[1],a[2],...,a[n] $ $ (1<=a[i]<=n) $ .

## 输出格式

In the first line, print integer $ k $ $ (0<=k<=5n) $ — the number of used operations. Next, print the operations. Each operation must be printed as " $ i $ $ j $ " ( $ 1<=i&lt;j<=n $ ; $ (j-i+1) $ is a prime).

If there are multiple answers, you can print any of them.

## 样例 #1

### 输入

```
3
3 2 1

```

### 输出

```
1
1 3

```

## 样例 #2

### 输入

```
2
1 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4
4 2 3 1

```

### 输出

```
3
2 4
1 2
2 4

```



---

---
title: "Om Nom and Candies"
layout: "post"
diff: 普及+/提高
pid: CF526C
tag: ['数学', '数论']
---

# Om Nom and Candies

## 题目描述

桌子上有无限多的红糖果与蓝糖果，每个红糖果重 $ W_{r} $ 克，而每个蓝糖果重 $ W_{b} $ 克。吃一颗红糖果可以获得 $ H_{r} $ 的快乐值，吃一颗蓝糖果可以获得 $ H_{b} $ 的快乐值。

在只能吃 $ C $ 克糖果的前提下，请求出能获得的最大快乐值。

## 输入格式

五个整数：$ C,H_{r},H_{b},W_{r},W_{b} $（$1 \leq C,H_{r},H_{b},W_{r},W_{b}  \leq 10^9$）

## 输出格式

出输出一个整数：能达到的最大快乐值。

## 样例 #1

### 输入

```
10 3 5 2 3

```

### 输出

```
16

```



---

