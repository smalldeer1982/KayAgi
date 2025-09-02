---
title: "Vasya and Magic Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF1042E
tag: ['前缀和', '期望', '逆元']
---

# Vasya and Magic Matrix

## 题目描述

Vasya has got a magic matrix $ a $ of size $ n \times m $ . The rows of the matrix are numbered from $ 1 $ to $ n $ from top to bottom, the columns are numbered from $ 1 $ to $ m $ from left to right. Let $ a_{ij} $ be the element in the intersection of the $ i $ -th row and the $ j $ -th column.

Vasya has also got a chip. Initially, the chip is in the intersection of the $ r $ -th row and the $ c $ -th column (that is, in the element $ a_{rc} $ ). Vasya performs the following process as long as possible: among all elements of the matrix having their value less than the value of the element with the chip in it, Vasya randomly and equiprobably chooses one element and moves his chip to this element.

After moving the chip, he adds to his score the square of the Euclidean distance between these elements (that is, between the element in which the chip is now and the element the chip was moved from). The process ends when there are no elements having their values less than the value of the element with the chip in it.

Euclidean distance between matrix elements with coordinates $ (i_1, j_1) $ and $ (i_2, j_2) $ is equal to $ \sqrt{(i_1-i_2)^2 + (j_1-j_2)^2} $ .

Calculate the expected value of the Vasya's final score.

It can be shown that the answer can be represented as $ \frac{P}{Q} $ , where $ P $ and $ Q $ are coprime integer numbers, and $ Q \not\equiv 0~(mod ~ 998244353) $ . Print the value $ P \cdot Q^{-1} $ modulo $ 998244353 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ $ (1 \le n, m \le 1\,000) $ — the number of rows and the number of columns in the matrix $ a $ .

The following $ n $ lines contain description of the matrix $ a $ . The $ i $ -th line contains $ m $ integers $ a_{i1}, a_{i2}, \dots, a_{im} ~ (0 \le a_{ij} \le 10^9) $ .

The following line contains two integers $ r $ and $ c $ $ (1 \le r \le n, 1 \le c \le m) $ — the index of row and the index of column where the chip is now.

## 输出格式

Print the expected value of Vasya's final score in the format described in the problem statement.

## 说明/提示

In the first example, Vasya will move his chip exactly once. The expected value of the final score is equal to $ \frac{1^2 + 2^2+ 1^2}{3} = 2 $ .

## 样例 #1

### 输入

```
1 4
1 1 2 1
1 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 3
1 5 7
2 3 1
1 2

```

### 输出

```
665496238

```



---

---
title: "Shaass and Lights"
layout: "post"
diff: 提高+/省选-
pid: CF294C
tag: ['数学', '组合数学', '逆元']
---

# Shaass and Lights

## 题目描述

There are $ n $ lights aligned in a row. These lights are numbered $ 1 $ to $ n $ from left to right. Initially some of the lights are switched on. Shaass wants to switch all the lights on. At each step he can switch a light on (this light should be switched off at that moment) if there's at least one adjacent light which is already switched on.

He knows the initial state of lights and he's wondering how many different ways there exist to switch all the lights on. Please find the required number of ways modulo $ 1000000007 (10^{9}+7) $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ where $ n $ is the number of lights in the sequence and $ m $ is the number of lights which are initially switched on, $ (1<=n<=1000,1<=m<=n) $ . The second line contains $ m $ distinct integers, each between $ 1 $ to $ n $ inclusive, denoting the indices of lights which are initially switched on.

## 输出格式

In the only line of the output print the number of different possible ways to switch on all the lights modulo $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
3 1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 2
1 4

```

### 输出

```
2

```

## 样例 #3

### 输入

```
11 2
4 8

```

### 输出

```
6720

```



---

---
title: "Iahub and Permutations"
layout: "post"
diff: 提高+/省选-
pid: CF340E
tag: ['动态规划 DP', '容斥原理', '逆元']
---

# Iahub and Permutations

## 题目描述

Iahub is so happy about inventing bubble sort graphs that he's staying all day long at the office and writing permutations. Iahubina is angry that she is no more important for Iahub. When Iahub goes away, Iahubina comes to his office and sabotage his research work.

The girl finds an important permutation for the research. The permutation contains $ n $ distinct integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ $ (1<=a_{i}<=n) $ . She replaces some of permutation elements with -1 value as a revenge.

When Iahub finds out his important permutation is broken, he tries to recover it. The only thing he remembers about the permutation is it didn't have any fixed point. A fixed point for a permutation is an element $ a_{k} $ which has value equal to $ k $ $ (a_{k}=k) $ . Your job is to proof to Iahub that trying to recover it is not a good idea. Output the number of permutations which could be originally Iahub's important permutation, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=2000 $ ). On the second line, there are $ n $ integers, representing Iahub's important permutation after Iahubina replaces some values with -1.

It's guaranteed that there are no fixed points in the given permutation. Also, the given sequence contains at least two numbers -1 and each positive number occurs in the sequence at most once. It's guaranteed that there is at least one suitable permutation.

## 输出格式

Output a single integer, the number of ways Iahub could recover his permutation, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

For the first test example there are two permutations with no fixed points are \[2, 5, 4, 3, 1\] and \[5, 1, 4, 3, 2\]. Any other permutation would have at least one fixed point.

## 样例 #1

### 输入

```
5
-1 -1 4 3 -1

```

### 输出

```
2

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

