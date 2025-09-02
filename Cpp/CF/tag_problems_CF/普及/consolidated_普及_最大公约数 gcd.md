---
title: "Non-Coprime Partition"
layout: "post"
diff: 普及/提高-
pid: CF1038B
tag: ['最大公约数 gcd']
---

# Non-Coprime Partition

## 题目描述

### 题目大意：
给定一个整数$n$，要求把$1$到$n$分别放入两个序列$s1,s2$，使得$\gcd(sum(s1),sum(s2))>1$

## 输入格式

一个整数$n$

一个整数$n$

## 输出格式

如果不能构成符合条件的序列，输出"No"，否则输出"Yes"，并在下两行输出$s1,s2$

```
### 题目大意：
给定一个整数$n$，要求把$1$到$n$分别放入两个序列$s1,s2$，使得$\gcd(sum(s1),sum(s2))>1$

如果不能构成符合条件的序列，输出"No"，否则输出"Yes"，并在下两行输出$s1,s2$

```

## 样例 #1

### 输入

```
1

```

### 输出

```
No
```

## 样例 #2

### 输入

```
3

```

### 输出

```
Yes
1 2
2 1 3 

```



---

---
title: "Partitioning the Array"
layout: "post"
diff: 普及/提高-
pid: CF1920C
tag: ['枚举', '最大公约数 gcd']
---

# Partitioning the Array

## 题目描述

Allen has an array $ a_1, a_2,\ldots,a_n $ . For every positive integer $ k $ that is a divisor of $ n $ , Allen does the following:

- He partitions the array into $ \frac{n}{k} $ disjoint subarrays of length $ k $ . In other words, he partitions the array into the following subarrays: $ $$$[a_1,a_2,\ldots,a_k],[a_{k+1}, a_{k+2},\ldots,a_{2k}],\ldots,[a_{n-k+1},a_{n-k+2},\ldots,a_{n}] $ $  </li><li> Allen earns one point if there exists some positive integer  $ m $  ( $ m \\geq 2 $ ) such that if he replaces every element in the array with its remainder when divided by  $ m$$$, then all subarrays will be identical.

Help Allen find the number of points he will earn.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2,\ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of points Allen will earn.

## 说明/提示

In the first test case, $ k=2 $ earns a point since Allen can pick $ m = 2 $ and both subarrays will be equal to $ [1, 0] $ . $ k=4 $ also earns a point, since no matter what $ m $ Allen chooses, there will be only one subarray and thus all subarrays are equal.

In the second test case, Allen earns $ 1 $ point for $ k=3 $ , where his choice for $ m $ does not matter.

## 样例 #1

### 输入

```
8
4
1 2 1 4
3
1 2 3
5
1 1 1 1 1
6
1 3 1 1 3 1
6
6 2 6 2 2 2
6
2 6 3 6 6 6
10
1 7 5 1 4 3 1 3 1 4
1
1
```

### 输出

```
2
1
2
4
4
1
2
1
```



---

---
title: "Modified GCD"
layout: "post"
diff: 普及/提高-
pid: CF75C
tag: ['数学', '枚举', '最大公约数 gcd']
---

# Modified GCD

## 题目描述

Well, here is another math class task. In mathematics, GCD is the greatest common divisor, and it's an easy task to calculate the GCD between two positive integers.

A common divisor for two positive numbers is a number which both numbers are divisible by.

But your teacher wants to give you a harder task, in this task you have to find the greatest common divisor $ d $ between two integers $ a $ and $ b $ that is in a given range from $ low $ to $ high $ (inclusive), i.e. $ low<=d<=high $ . It is possible that there is no common divisor in the given range.

You will be given the two integers $ a $ and $ b $ , then $ n $ queries. Each query is a range from $ low $ to $ high $ and you have to answer each query.

## 输入格式

The first line contains two integers $ a $ and $ b $ , the two integers as described above ( $ 1<=a,b<=10^{9} $ ). The second line contains one integer $ n $ , the number of queries ( $ 1<=n<=10^{4} $ ). Then $ n $ lines follow, each line contains one query consisting of two integers, $ low $ and $ high $ ( $ 1<=low<=high<=10^{9} $ ).

## 输出格式

Print $ n $ lines. The $ i $ -th of them should contain the result of the $ i $ -th query in the input. If there is no common divisor in the given range for any query, you should print -1 as a result for this query.

## 样例 #1

### 输入

```
9 27
3
1 5
10 11
9 11

```

### 输出

```
3
-1
9

```



---

---
title: "Finite or not?"
layout: "post"
diff: 普及/提高-
pid: CF983A
tag: ['数学', '最大公约数 gcd', '进制']
---

# Finite or not?

## 题目描述

有 $n$ 组数据，每一组数据读入一个分数的分子 $p$、分母 $q$ 和进制 $b$（分子、分母均以十进制读入）求在 $b$ 进制下 $\frac{p}{q}$ 是否为有限小数。如果是，输出 `Finite`，否则输出 `Infinite`

## 输入格式

第一行输入 $n$

接下来 $n$ 行输入 $p$, $q$ 和 $b$。

## 输出格式

对于每一组数据，输出 `Finite` 或 `Infinite`

1 <= n <= 10^5, 1 <= b, p, q <= 10^18

由 @Medoric 提供翻译

## 样例 #1

### 输入

```
2
6 12 10
4 3 10

```

### 输出

```
Finite
Infinite

```

## 样例 #2

### 输入

```
4
1 1 2
9 36 2
4 12 3
3 5 4

```

### 输出

```
Finite
Finite
Finite
Infinite

```



---

