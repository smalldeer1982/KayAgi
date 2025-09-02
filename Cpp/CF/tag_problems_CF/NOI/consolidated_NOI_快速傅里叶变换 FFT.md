---
title: "Problems for Codeforces"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1580F
tag: ['分治', '快速傅里叶变换 FFT']
---

# Problems for Codeforces

## 题目描述

XYMXYM 与 CQXYM 将为 Codeforces 准备 $n$ 个题目。第 $i$ 个题目的难度为整数 $a_i$ 且 $a_i\geq 0$。所有题目的难度必须满足 $a_i+a_{i+1}\lt m\,\space(1\leq i\lt n)$ 且 $a_1+a_n\lt m$，其中 $m$ 为一个固定整数。XYMXYM 想知道题目难度有多少种可能的方案，结果对 $998244353$ 取模。

两种题目难度的方案 $a$ 和 $b$ 是不同的当且仅当存在一个整数 $i,\space (1\leq i\leq n)$ 满足 $a_i\neq b_i$。

## 输入格式

一行包含两个整数 $n$ 和 $m$ $(2\leq n\leq 50\,000,1\leq m\leq 10^9)$。

## 输出格式

输出一个整数为方案数，对 $998244353$ 取模。

## 说明/提示

在第一个样例中，合法的方案为 $[0,0,0],[0,0,1],[0,1,0],[1,0,0]$，而 $[1,0,1]$ 不合法因为 $a_1+a_n\geq m$。

## 样例 #1

### 输入

```
3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 9
```

### 输出

```
8105
```

## 样例 #3

### 输入

```
21038 3942834
```

### 输出

```
338529212
```



---

---
title: "Mio and Lucky Array"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1704G
tag: ['快速傅里叶变换 FFT']
---

# Mio and Lucky Array

## 题目描述

Mio has an array $ a $ consisting of $ n $ integers, and an array $ b $ consisting of $ m $ integers.

Mio can do the following operation to $ a $ :

- Choose an integer $ i $ ( $ 1 \leq i \leq n $ ) that has not been chosen before, then add $ 1 $ to $ a_i $ , subtract $ 2 $ from $ a_{i+1} $ , add $ 3 $ to $ a_{i+2} $ an so on. Formally, the operation is to add $ (-1)^{j-i} \cdot (j-i+1)  $ to $ a_j $ for $ i \leq j \leq n $ .

Mio wants to transform $ a $ so that it will contain $ b $ as a subarray. Could you answer her question, and provide a sequence of operations to do so, if it is possible?

An array $ b $ is a subarray of an array $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains one integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the number of elements in $ a $ .

The second line of the test case contains $ n $ integers $ a_1, a_2, \cdots, a_n $ ( $ -10^5 \leq a_i \leq 10^5 $ ), where $ a_i $ is the $ i $ -th element of $ a $ .

The third line of the test case contains one integer $ m $ ( $ 2 \leq m \leq n $ ) — the number of elements in $ b $ .

The fourth line of the test case contains $ m $ integers $ b_1, b_2, \cdots, b_m $ ( $ -10^{12} \leq b_i \leq 10^{12} $ ), where $ b_i $ is the $ i $ -th element of $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

If it is impossible to transform $ a $ so that it contains $ b $ as a subarray, output $ -1 $ .

Otherwise, the first line of output should contain an integer $ k $ ( $ 0 \leq k \leq n $ ), the number of operations to be done.

The second line should contain $ k $ distinct integers, representing the operations done in order.

If there are multiple solutions, you can output any.

Notice that you do not need to minimize the number of operations.

## 说明/提示

In the first test case, the sequence $ a $ = $ [1,2,3,4,5] $ . One of the possible solutions is doing one operation at $ i = 1 $ (add $ 1 $ to $ a_1 $ , subtract $ 2 $ from $ a_2 $ , add $ 3 $ to $ a_3 $ , subtract $ 4 $ from $ a_4 $ , add $ 5 $ to $ a_5 $ ). Then array $ a $ is transformed to $ a $ = $ [2,0,6,0,10] $ , which contains $ b $ = $ [2, 0, 6, 0, 10] $ as a subarray.

In the second test case, the sequence $ a $ = $ [1,2,3,4,5] $ . One of the possible solutions is doing one operation at $ i = 4 $ (add $ 1 $ to $ a_4 $ , subtract $ 2 $ from $ a_5 $ ). Then array $ a $ is transformed to $ a $ = $ [1,2,3,5,3] $ , which contains $ b $ = $ [3,5,3] $ as a subarray.

In the third test case, the sequence $ a $ = $ [-3, 2, -3, -4, 4, 0, 1, -2] $ . One of the possible solutions is the following.

- Choose an integer $ i=8 $ to do the operation. Then array $ a $ is transformed to $ a $ = $ [-3, 2, -3, -4, 4, 0, 1, -1] $ .
- Choose an integer $ i=6 $ to do the operation. Then array $ a $ is transformed to $ a $ = $ [-3, 2, -3, -4, 4, 1, -1, 2] $ .
- Choose an integer $ i=4 $ to do the operation. Then array $ a $ is transformed to $ a $ = $ [-3, 2, -3, -3, 2, 4, -5, 7] $ .
- Choose an integer $ i=3 $ to do the operation. Then array $ a $ is transformed to $ a $ = $ [-3, 2, -2, -5, 5, 0, 0, 1] $ .
- Choose an integer $ i=1 $ to do the operation. Then array $ a $ is transformed to $ a $ = $ [-2, 0, 1, -9, 10, -6, 7, -7] $ .

The resulting $ a $ is $ [-2, 0, 1, -9, 10, -6, 7, -7] $ , which contains $ b $ = $ [10, -6, 7, -7] $ as a subarray.

In the fourth test case, it is impossible to transform $ a $ so that it contains $ b $ as a subarray.

In the fifth test case, it is impossible to transform $ a $ so that it contains $ b $ as a subarray.

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
5
2 0 6 0 10
5
1 2 3 4 5
3
3 5 3
8
-3 2 -3 -4 4 0 1 -2
4
10 -6 7 -7
5
1 2 3 4 5
4
1 10 1 1
5
0 0 0 0 0
2
10 12
```

### 输出

```
1
1 
1
4 
5
1 3 4 6 8 
-1
-1
```



---

---
title: "Transforming Sequence"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF623E
tag: ['快速傅里叶变换 FFT']
---

# Transforming Sequence

## 题目描述

Let's define the transformation $ P $ of a sequence of integers $ a_{1},a_{2},...,a_{n} $ as $ b_{1},b_{2},...,b_{n} $ , where $ b_{i}=a_{1} | a_{2} | ... | a_{i} $ for all $ i=1,2,...,n $ , where $ | $ is the bitwise OR operation.

Vasya consequently applies the transformation $ P $ to all sequences of length $ n $ consisting of integers from $ 1 $ to $ 2^{k}-1 $ inclusive. He wants to know how many of these sequences have such property that their transformation is a strictly increasing sequence. Help him to calculate this number modulo $ 10^{9}+7 $ .

## 输入格式

The only line of the input contains two integers $ n $ and $ k $ ( $ 1<=n<=10^{18},1<=k<=30000 $ ).

## 输出格式

Print a single integer — the answer to the problem modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2 3

```

### 输出

```
30

```

## 样例 #3

### 输入

```
3 3

```

### 输出

```
48

```



---

