---
title: "Numbers"
layout: "post"
diff: 普及-
pid: CF13A
tag: ['模拟', '最大公约数 gcd', '进制']
---

# Numbers

## 题目描述

Little Petya likes numbers a lot. He found that number 123 in base 16 consists of two digits: the first is 7 and the second is 11. So the sum of digits of 123 in base 16 is equal to 18.

Now he wonders what is an average value of sum of digits of the number $ A $ written in all bases from $ 2 $ to $ A-1 $ .

Note that all computations should be done in base 10. You should find the result as an irreducible fraction, written in base 10.

## 输入格式

Input contains one integer number $ A $ ( $ 3<=A<=1000 $ ).

## 输出格式

Output should contain required average value in format «X/Y», where X is the numerator and Y is the denominator.

## 说明/提示

In the first sample number 5 written in all bases from 2 to 4 looks so: 101, 12, 11. Sums of digits are 2, 3 and 2, respectively.

## 样例 #1

### 输入

```
5

```

### 输出

```
7/3

```

## 样例 #2

### 输入

```
3

```

### 输出

```
2/1

```



---

---
title: "GCD Problem"
layout: "post"
diff: 普及-
pid: CF1617B
tag: ['数论', '最大公约数 gcd']
---

# GCD Problem

## 题目描述

Given a positive integer $ n $ . Find three distinct positive integers $ a $ , $ b $ , $ c $ such that $ a + b + c = n $ and $ \operatorname{gcd}(a, b) = c $ , where $ \operatorname{gcd}(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. Description of the test cases follows.

The first and only line of each test case contains a single integer $ n $ ( $ 10 \le n \le 10^9 $ ).

## 输出格式

For each test case, output three distinct positive integers $ a $ , $ b $ , $ c $ satisfying the requirements. If there are multiple solutions, you can print any. We can show that an answer always exists.

## 说明/提示

In the first test case, $ 6 + 9 + 3 = 18 $ and $ \operatorname{gcd}(6, 9) = 3 $ .

In the second test case, $ 21 + 39 + 3 = 63 $ and $ \operatorname{gcd}(21, 39) = 3 $ .

In the third test case, $ 29 + 43 + 1 = 73 $ and $ \operatorname{gcd}(29, 43) = 1 $ .

## 样例 #1

### 输入

```
6
18
63
73
91
438
122690412
```

### 输出

```
6 9 3
21 39 3
29 43 1
49 35 7
146 219 73
28622 122661788 2
```



---

---
title: "GCD Partition"
layout: "post"
diff: 普及-
pid: CF1780B
tag: ['最大公约数 gcd', '前缀和']
---

# GCD Partition

## 题目描述

While at Kira's house, Josuke saw a piece of paper on the table with a task written on it.

The task sounded as follows. There is an array $ a $ of length $ n $ . On this array, do the following:

- select an integer $ k > 1 $ ;
- split the array into $ k $ subsegments $ ^\dagger $ ;
- calculate the sum in each of $ k $ subsegments and write these sums to another array $ b $ (where the sum of the subsegment $ (l, r) $ is $ {\sum_{j = l}^{r}a_j} $ );
- the final score of such a split will be $ \gcd(b_1, b_2, \ldots, b_k)^\ddagger $ .

The task is to find such a partition that the score is maximum possible. Josuke is interested in this task but is not strong in computer science. Help him to find the maximum possible score.

 $ ^\dagger $ A division of an array into $ k $ subsegments is $ k $ pairs of numbers $ (l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k) $ such that $ l_i \le r_i $ and for every $ 1 \le j \le k - 1 $ $ l_{j + 1} = r_j + 1 $ , also $ l_1 = 1 $ and $ r_k = n $ . These pairs represent the subsegments.

 $ ^\ddagger $ $ \gcd(b_1, b_2, \ldots, b_k) $ stands for the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the array $ b $ .

## 输入格式

The first line contains a single number $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

For each test case, the first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, a_3, \ldots, a_n $ ( $ 1 \le a_i \le 10^9  $ ) — the array $ a $ itself.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case print a single integer — the maximum score for the optimal partition.

## 说明/提示

In the first test case, you can choose $ k = 2 $ and split the array into subsegments $ (1, 2) $ and $ (3, 4) $ .

Then the score of such a partition will be equal to $ \gcd(a_1 + a_2, a_3 + a_4) = \gcd(2 + 2, 1 + 3) = \gcd(4, 4) = 4 $ .

In the fourth test case, you can choose $ k = 3 $ and split the array into subsegments $ (1, 2), (3, 5), (6, 6) $ .

The split score is $ \gcd(1 + 2, 1 + 1 + 1, 3) = 3 $ .

## 样例 #1

### 输入

```
6
4
2 2 1 3
2
1 2
3
1 4 5
6
1 2 1 1 1 3
10
12 30 37 88 12 78 89 17 2 12
6
7 7 7 7 7 7
```

### 输出

```
4
1
5
3
1
21
```



---

---
title: "Two Divisors"
layout: "post"
diff: 普及-
pid: CF1916B
tag: ['最大公约数 gcd']
---

# Two Divisors

## 题目描述

A certain number $ 1 \le x \le 10^9 $ is chosen. You are given two integers $ a $ and $ b $ , which are the two largest divisors of the number $ x $ . At the same time, the condition $ 1 \le a < b < x $ is satisfied.

For the given numbers $ a $ , $ b $ , you need to find the value of $ x $ .

 $ ^{\dagger} $ The number $ y $ is a divisor of the number $ x $ if there is an integer $ k $ such that $ x = y \cdot k $ .

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follows the description of the test cases.

The only line of each test cases contains two integers $ a $ , $ b $ ( $ 1 \le a < b \le 10^9 $ ).

It is guaranteed that $ a $ , $ b $ are the two largest divisors for some number $ 1 \le x \le 10^9 $ .

## 输出格式

For each test case, output the number $ x $ , such that $ a $ and $ b $ are the two largest divisors of the number $ x $ .

If there are several answers, print any of them.

## 说明/提示

For the first test case, all divisors less than $ 6 $ are equal to $ [1, 2, 3] $ , among them the two largest will be $ 2 $ and $ 3 $ .

For the third test case, all divisors less than $ 33 $ are equal to $ [1, 3, 11] $ , among them the two largest will be $ 3 $ and $ 11 $ .

For the fifth test case, all divisors less than $ 20 $ are equal to $ [1, 2, 4, 5, 10] $ , among them the two largest will be $ 5 $ and $ 10 $ .

For the sixth test case, all divisors less than $ 12 $ are equal to $ [1, 2, 3, 4, 6] $ , among them the two largest will be $ 4 $ and $ 6 $ .

## 样例 #1

### 输入

```
8
2 3
1 2
3 11
1 5
5 10
4 6
3 9
250000000 500000000
```

### 输出

```
6
4
33
25
20
12
27
1000000000
```



---

