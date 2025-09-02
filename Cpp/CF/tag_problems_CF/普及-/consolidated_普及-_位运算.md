---
title: "AND Sorting"
layout: "post"
diff: 普及-
pid: CF1682B
tag: ['贪心', '位运算']
---

# AND Sorting

## 题目描述

You are given a permutation $ p $ of integers from $ 0 $ to $ n-1 $ (each of them occurs exactly once). Initially, the permutation is not sorted (that is, $ p_i>p_{i+1} $ for at least one $ 1 \le i \le n - 1 $ ).

The permutation is called $ X $ -sortable for some non-negative integer $ X $ if it is possible to sort the permutation by performing the operation below some finite number of times:

- Choose two indices $ i $ and $ j $ $ (1 \le i \lt j \le n) $ such that $ p_i \& p_j = X $ .
- Swap $ p_i $ and $ p_j $ .

Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Find the maximum value of $ X $ such that $ p $ is $ X $ -sortable. It can be shown that there always exists some value of $ X $ such that $ p $ is $ X $ -sortable.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \le t \le 10^4) $ — the number of test cases. Description of test cases follows.

The first line of each test case contains a single integer $ n $ $ (2 \le n \le 2 \cdot 10^5) $ — the length of the permutation.

The second line of each test case contains $ n $ integers $ p_1, p_2, ..., p_n $ ( $ 0 \le p_i \le n-1 $ , all $ p_i $ are distinct) — the elements of $ p $ . It is guaranteed that $ p $ is not sorted.

It is guaranteed that the sum of $ n $ over all cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output a single integer — the maximum value of $ X $ such that $ p $ is $ X $ -sortable.

## 说明/提示

In the first test case, the only $ X $ for which the permutation is $ X $ -sortable are $ X = 0 $ and $ X = 2 $ , maximum of which is $ 2 $ .

Sorting using $ X = 0 $ :

- Swap $ p_1 $ and $ p_4 $ , $ p = [2, 1, 3, 0] $ .
- Swap $ p_3 $ and $ p_4 $ , $ p = [2, 1, 0, 3] $ .
- Swap $ p_1 $ and $ p_3 $ , $ p = [0, 1, 2, 3] $ .

Sorting using $ X = 2 $ :

- Swap $ p_3 $ and $ p_4 $ , $ p = [0, 1, 2, 3] $ .

In the second test case, we must swap $ p_1 $ and $ p_2 $ which is possible only with $ X = 0 $ .

## 样例 #1

### 输入

```
4
4
0 1 3 2
2
1 0
7
0 1 2 3 5 6 4
5
0 3 2 1 4
```

### 输出

```
2
0
4
1
```



---

---
title: "Cirno's Perfect Bitmasks Classroom"
layout: "post"
diff: 普及-
pid: CF1688A
tag: ['位运算']
---

# Cirno's Perfect Bitmasks Classroom

## 题目描述

> 就算是很简单的问题，她一定也答不上来。——《东方求闻史纪》   

琪露诺的完美位运算教室开始了！    
琪露诺给了她的学生一个正整数 $x$，作为作业题，她的学生需要找到一个满足以下两个条件的，最小的正整数 $y$。
- $x \operatorname{and} y>0$     
- $x \operatorname{xor} y>0$ 

这里的 $\operatorname{and}$ 和 $\operatorname{xor}$ 都是位运算。      
她的学生米斯蒂娅对这个问题束手无策，请你来帮帮她。

## 输入格式

第一行输入一个正整数 $t(1 \leq t \leq 10^3)$，表示输入数据组数。    
对于每一组数据，输入一个正整数 $x$。

## 输出格式

对于每一组数据，输出符合题目要求的 $y$。

## 样例 #1

### 输入

```
7
1
2
5
9
16
114514
1000000
```

### 输出

```
3
3
1
1
17
2
64
```



---

---
title: "Patchouli's Magical Talisman"
layout: "post"
diff: 普及-
pid: CF1688B
tag: ['贪心', '位运算']
---

# Patchouli's Magical Talisman

## 题目描述

> 她擅长多种魔法，而且致力于开发新魔法。——《东方求闻史纪》

帕秋莉正在制作一个魔法护身符。她现在有 $n$ 个魔法令牌，令牌上的魔力值可以用正整数数列 $a_1,a_2,\dots,a_n$ 来表示。     
帕秋莉可以对她的魔法令牌进行如下两种操作。

- 融合：帕秋莉可以选择两块令牌并且将它们移除，并且创造出一块新的令牌，其魔力值为这两块令牌的魔力值的和。
- 降低：帕秋莉可以选择一个魔力值为一个偶数 $x$ 的令牌，将其移除，创造出一块新的令牌，其魔力值变为 $\dfrac{x}{2}$。

由于当魔力值为奇数的时候这些令牌的工作效率会达到最高，所以请你帮助帕秋莉，告诉她把这些令牌的魔力值都变成奇数，所需的最小次数是多少。

## 输入格式

第一行输入一个正整数 $t(1 \leq t \leq 10^3)$，表示输入数据组数。         
对于每组数据，第一行输入一个正整数 $n(1 \leq n \leq 2\times 10^5)$，表示魔法令牌的个数。   
第二行输入 $n$ 个正整数 $a_i(1 \leq a_i \leq 10^9)$，表示魔法令牌上的魔力值。    
数据保证，对于每组数据，$\sum n \leq 2 \times 10^5$。

## 输出格式

对于每一组数据，输出一个正整数，表示把这些令牌的魔力值都变成奇数，所需的最小次数是多少。可以证明一定存在一种方式。

## 样例 #1

### 输入

```
4
2
1 9
3
1 1 2
3
2 4 8
3
1049600 33792 1280
```

### 输出

```
0
1
3
10
```



---

---
title: "NIT orz!"
layout: "post"
diff: 普及-
pid: CF1696A
tag: ['贪心', '位运算']
---

# NIT orz!

## 题目描述

NIT, the cleaver, is new in town! Thousands of people line up to orz him. To keep his orzers entertained, NIT decided to let them solve the following problem related to $ \operatorname{or} z $ . Can you solve this problem too?

You are given a 1-indexed array of $ n $ integers, $ a $ , and an integer $ z $ . You can do the following operation any number (possibly zero) of times:

- Select a positive integer $ i $ such that $ 1\le i\le n $ . Then, simutaneously set $ a_i $ to $ (a_i\operatorname{or} z) $ and set $ z $ to $ (a_i\operatorname{and} z) $ . In other words, let $ x $ and $ y $ respectively be the current values of $ a_i $ and $ z $ . Then set $ a_i $ to $ (x\operatorname{or}y) $ and set $ z $ to $ (x\operatorname{and}y) $ .

Here $ \operatorname{or} $ and $ \operatorname{and} $ denote the [bitwise operations OR and AND](https://en.wikipedia.org/wiki/Bitwise_operation) respectively.

Find the maximum possible value of the maximum value in $ a $ after any number (possibly zero) of operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 100 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ z $ ( $ 1\le n\le 2000 $ , $ 0\le z<2^{30} $ ).

The second line of each test case contains $ n $ integers $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 0\le a_i<2^{30} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, print one integer — the answer to the problem.

## 说明/提示

In the first test case of the sample, one optimal sequence of operations is:

- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (3\operatorname{or}3)=3 $ and $ z $ becomes $ (3\operatorname{and}3)=3 $ .
- Do the operation with $ i=2 $ . Now $ a_2 $ becomes $ (4\operatorname{or}3)=7 $ and $ z $ becomes $ (4\operatorname{and}3)=0 $ .
- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (3\operatorname{or}0)=3 $ and $ z $ becomes $ (3\operatorname{and}0)=0 $ .

After these operations, the sequence $ a $ becomes $ [3,7] $ , and the maximum value in it is $ 7 $ . We can prove that the maximum value in $ a $ can never exceed $ 7 $ , so the answer is $ 7 $ .

In the fourth test case of the sample, one optimal sequence of operations is:

- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (7\operatorname{or}7)=7 $ and $ z $ becomes $ (7\operatorname{and}7)=7 $ .
- Do the operation with $ i=3 $ . Now $ a_3 $ becomes $ (30\operatorname{or}7)=31 $ and $ z $ becomes $ (30\operatorname{and}7)=6 $ .
- Do the operation with $ i=5 $ . Now $ a_5 $ becomes $ (27\operatorname{or}6)=31 $ and $ z $ becomes $ (27\operatorname{and}6)=2 $ .

## 样例 #1

### 输入

```
5
2 3
3 4
5 5
0 2 4 6 8
1 9
10
5 7
7 15 30 29 27
3 39548743
10293834 10284344 13635445
```

### 输出

```
7
13
11
31
48234367
```



---

---
title: "XOR Sequences"
layout: "post"
diff: 普及-
pid: CF1979B
tag: ['位运算']
---

# XOR Sequences

## 题目描述

You are given two distinct non-negative integers $ x $ and $ y $ . Consider two infinite sequences $ a_1, a_2, a_3, \ldots $ and $ b_1, b_2, b_3, \ldots $ , where

- $ a_n = n \oplus x $ ;
- $ b_n = n \oplus y $ .

Here, $ x \oplus y $ denotes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operation of integers $ x $ and $ y $ .

For example, with $ x = 6 $ , the first $ 8 $ elements of sequence $ a $ will look as follows: $ [7, 4, 5, 2, 3, 0, 1, 14, \ldots] $ . Note that the indices of elements start with $ 1 $ .

Your task is to find the length of the longest common subsegment $ ^\dagger $ of sequences $ a $ and $ b $ . In other words, find the maximum integer $ m $ such that $ a_i = b_j, a_{i + 1} = b_{j + 1}, \ldots, a_{i + m - 1} = b_{j + m - 1} $ for some $ i, j \ge 1 $ .

 $ ^\dagger $ A subsegment of sequence $ p $ is a sequence $ p_l,p_{l+1},\ldots,p_r $ , where $ 1 \le l \le r $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The only line of each test case contains two integers $ x $ and $ y $ ( $ 0 \le x, y \le 10^9, x \neq y $ ) — the parameters of the sequences.

## 输出格式

For each test case, output a single integer — the length of the longest common subsegment.

## 说明/提示

In the first test case, the first $ 7 $ elements of sequences $ a $ and $ b $ are as follows:

 $ a = [1, 2, 3, 4, 5, 6, 7,\ldots] $

 $ b = [0, 3, 2, 5, 4, 7, 6,\ldots] $

It can be shown that there isn't a positive integer $ k $ such that the sequence $ [k, k + 1] $ occurs in $ b $ as a subsegment. So the answer is $ 1 $ .

In the third test case, the first $ 20 $ elements of sequences $ a $ and $ b $ are as follows:

 $ a = [56, 59, 58, 61, 60, 63, 62, 49, 48, 51, 50, 53, 52, 55, 54, \textbf{41, 40, 43, 42}, 45, \ldots] $

 $ b = [36, 39, 38, 33, 32, 35, 34, 45, 44, 47, 46, \textbf{41, 40, 43, 42}, 53, 52, 55, 54, 49, \ldots] $

It can be shown that one of the longest common subsegments is the subsegment $ [41, 40, 43, 42] $ with a length of $ 4 $ .

## 样例 #1

### 输入

```
4
0 1
12 4
57 37
316560849 14570961
```

### 输出

```
1
8
4
33554432
```



---

---
title: "AND Reconstruction"
layout: "post"
diff: 普及-
pid: CF1991B
tag: ['贪心', '位运算']
---

# AND Reconstruction

## 题目描述

给定一个由 $ n - 1 $ 个整数组成的数组 $ b $。

一个数组 $ a $ 被称为是“好的”当且仅当对于 $ 1 \le i \le n-1 $，都有 $ b_i = a_i \, \& \, a_{i + 1} $ 其中$ \& $ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。

你的任务是构造一个“好的”数组，或输出 `-1` 表示不存在“好的”数组。

## 输入格式

有多组数据。第一行是一个整数 $ t $ ( $ 1 \le t \le 10^4 $ )，表示数据组数。

每组数据的第一行有一个正整数 $ n $ ( $ 2 \le n \le 10^5 $ )，表示数组 $ a $ 的长度

第二行有 $ n - 1 $ 个整数， $ b_1, b_2, \ldots, b_{n - 1} $ ( $ 0 \le b_i < 2^{30} $ )，表示 $ b $ 数组。

保证所有数据中 $ n $ 的和不超过 $ 10^5 $。

## 输出格式

对于每组数据，若不存在“好的”数组输出 `-1`。

否则输出 $ n $ 个用空格分隔的整数 $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i < 2^{30} $ ) 表示一个“好的”数组。

若有多种方案，输出任意一种都可。

## 说明/提示

对于第一组样例，$ b = [1] $。一个可能的"好的"数组是 $ a=[5, 3] $。因为 $ a_1 \, \& \, a_2 = 5 \, \& \, 3 = 1 = b_1 $。

对于第二组样例，$ b = [2, 0] $。一个可能的"好的"数组是 $ a=[3, 2, 1] $。因为 $ a_1 \, \& \, a_2 = 3 \, \& \, 2 = 2 = b_1 $ and $ a_2 \, \& \, a_3 = 2 \, \& \, 1 = 0 = b_2 $。

对于第三组样例，$ b = [1, 2, 3] $。可以证明不存在"好的"数组，所以输出 `-1`。

对于第四组样例，$ b = [3, 5, 4, 2] $。一个可能的"好的"数组是 $ a=[3, 7, 5, 6, 3] $。

## 样例 #1

### 输入

```
4
2
1
3
2 0
4
1 2 3
5
3 5 4 2
```

### 输出

```
5 3
3 2 1
-1
3 7 5 6 3
```



---

---
title: "Shohag Loves XOR (Easy Version)"
layout: "post"
diff: 普及-
pid: CF2039C1
tag: ['数学', '枚举', '位运算']
---

# Shohag Loves XOR (Easy Version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ \mathbf{x \neq y} $ and $ x \oplus y $ is a divisor $ ^{\text{∗}} $ of either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ b $ is a divisor of the number $ a $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains two space-separated integers $ x $ and $ m $ ( $ 1 \le x \le 10^6 $ , $ 1 \le m \le 10^{18} $ ).

It is guaranteed that the sum of $ x $ over all test cases does not exceed $ 10^7 $ .

## 输出格式

For each test case, print a single integer — the number of suitable $ y $ .

## 说明/提示

In the first test case, for $ x = 6 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 9 $ , and they are $ 4 $ , $ 5 $ , and $ 7 $ .

- $ y = 4 $ is valid because $ x \oplus y = 6 \oplus 4 = 2 $ and $ 2 $ is a divisor of both $ x = 6 $ and $ y = 4 $ .
- $ y = 5 $ is valid because $ x \oplus y = 6 \oplus 5 = 3 $ and $ 3 $ is a divisor of $ x = 6 $ .
- $ y = 7 $ is valid because $ x \oplus y = 6 \oplus 7 = 1 $ and $ 1 $ is a divisor of both $ x = 6 $ and $ y = 7 $ .

In the second test case, for $ x = 5 $ , there are $ 2 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 7 $ , and they are $ 4 $ and $ 6 $ .

- $ y = 4 $ is valid because $ x \oplus y = 5 \oplus 4 = 1 $ and $ 1 $ is a divisor of both $ x = 5 $ and $ y = 4 $ .
- $ y = 6 $ is valid because $ x \oplus y = 5 \oplus 6 = 3 $ and $ 3 $ is a divisor of $ y = 6 $ .

## 样例 #1

### 输入

```
5
6 9
5 7
2 3
6 4
4 1
```

### 输出

```
3
2
1
1
0
```



---

---
title: "Binary Matrix"
layout: "post"
diff: 普及-
pid: CF2082A
tag: ['贪心', '位运算']
---

# Binary Matrix

## 题目描述

如果一个矩阵的所有元素都是 $0$ 或 $1$，则称其为二进制矩阵。

当二进制矩阵 $A$ 满足以下两个条件时，Ecrade 称其为好矩阵：
- 矩阵 $A$ 每一行的所有数的[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)结果等于 $0$。
- 矩阵 $A$ 每一列的所有数的[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)结果等于 $0$。

Ecrade 有一个大小为 $n \cdot m$ 的二进制矩阵。他想知道将这个矩阵变为好矩阵所需修改元素的最小数量。

这个问题似乎有些困难，请你帮助他！

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 400$）。接下来描述每个测试用例：

每个测试用例的第一行包含两个整数 $n, m$（$1 \le n, m \le 100$）。

接下来是 $n$ 行，每行包含恰好 $m$ 个由 $0$ 和 $1$ 组成的字符，描述 Ecrade 的矩阵。

保证所有测试用例的 $n \cdot m$ 之和不超过 $5 \cdot 10^4$。

## 输出格式

对于每个测试用例，输出一个整数，表示需要修改元素的最小数量。

## 说明/提示

第一个测试用例中，需要修改 2 个元素得到以下矩阵：
$$\begin{pmatrix}1&1&0\\1&0&1\\0&1&1\end{pmatrix}$$

第二个测试用例中，可以不修改任何元素直接得到以下矩阵：
$$\begin{pmatrix}0&0&0\\0&0&0\\0&0&0\end{pmatrix}$$

第三个测试用例中，需要修改 3 个元素得到以下矩阵：
$$\begin{pmatrix}1&0&1\\0&0&0\\1&0&1\end{pmatrix}$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
3 3
010
101
010
3 3
000
000
000
3 3
100
010
001
3 3
101
010
000
3 3
000
010
000
1 4
0101
4 1
0
1
0
1
```

### 输出

```
2
0
3
3
1
2
2
```



---

---
title: "Sum"
layout: "post"
diff: 普及-
pid: CF49B
tag: ['字符串', '进制', '位运算']
---

# Sum

## 题目描述

Vasya终于学会了进位制，但他经常忘记写算式的基数。有一次，他看到他的笔记本上写着a+b=？，但是没有写明基数。现在Vasya认为算式的基数为p。他知道算式在不同的基数下，会有不同的结果，甚至在有些基数下是没有意义的。算式78+87的值在十六进制下为FF，在十五进制下为110，十进制下为165，九进制下为176，更小的基数下就没有意义了。现在，Vasya想要知道算式结果的最大长度。
我们定义数字的长度为数字的字符个数，在不同的进制下，同一个数字有不同的数字长度。

## 输入格式

共一行，包含两个数a，b。

## 输出格式

共一行，输出算式的最大长度。

Translated by @handahao

## 样例 #1

### 输入

```
78 87

```

### 输出

```
3

```

## 样例 #2

### 输入

```
1 1

```

### 输出

```
2

```



---

---
title: "Nearest Minimums"
layout: "post"
diff: 普及-
pid: CF911A
tag: ['枚举', '排序', '位运算']
---

# Nearest Minimums

## 题目描述

You are given an array of $ n $ integer numbers $ a_{0},a_{1},...,a_{n-1} $ . Find the distance between two closest (nearest) minimums in it. It is guaranteed that in the array a minimum occurs at least two times.
找到一个长度为n的序列中，距离最短的最小值的距离。

## 输入格式

The first line contains positive integer $ n $ ( $ 2<=n<=10^{5} $ ) — size of the given array. The second line contains $ n $ integers $ a_{0},a_{1},...,a_{n-1} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of the array. It is guaranteed that in the array a minimum occurs at least two times.

## 输出格式

Print the only number — distance between two nearest minimums in the array.

## 样例 #1

### 输入

```
2
3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
5 6 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
9
2 1 3 5 4 1 2 3 1

```

### 输出

```
3

```



---

---
title: "New Year's Eve"
layout: "post"
diff: 普及-
pid: CF912B
tag: ['贪心', '进制', '位运算']
---

# New Year's Eve

## 题目描述

Since Grisha behaved well last year, at New Year's Eve he was visited by Ded Moroz who brought an enormous bag of gifts with him! The bag contains $ n $ sweet candies from the good ol' bakery, each labeled from $ 1 $ to $ n $ corresponding to its tastiness. No two candies have the same tastiness.

The choice of candies has a direct effect on Grisha's happiness. One can assume that he should take the tastiest ones — but no, the holiday magic turns things upside down. It is the xor-sum of tastinesses that matters, not the ordinary sum!

A xor-sum of a sequence of integers $ a_{1},a_{2},...,a_{m} $ is defined as the bitwise XOR of all its elements: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/475d3a054d8c211f23a68d652dd85385e5ab9fc9.png), here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the bitwise XOR operation; more about bitwise XOR can be found [here.](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

Ded Moroz warned Grisha he has more houses to visit, so Grisha can take no more than $ k $  candies from the bag. Help Grisha determine the largest xor-sum (largest xor-sum means maximum happiness!) he can obtain.

## 输入格式

The sole string contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=10^{18} $ ).

## 输出格式

Output one number — the largest possible xor-sum.

## 说明/提示

In the first sample case, one optimal answer is $ 1 $ , $ 2 $ and $ 4 $ , giving the xor-sum of $ 7 $ .

In the second sample case, one can, for example, take all six candies and obtain the xor-sum of $ 7 $ .

## 样例 #1

### 输入

```
4 3

```

### 输出

```
7

```

## 样例 #2

### 输入

```
6 6

```

### 输出

```
7

```



---

