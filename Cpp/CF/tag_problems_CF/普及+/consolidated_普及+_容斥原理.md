---
title: "Count GCD"
layout: "post"
diff: 普及+/提高
pid: CF1750D
tag: ['数学', '枚举', '容斥原理']
---

# Count GCD

## 题目描述

You are given two integers $ n $ and $ m $ and an array $ a $ of $ n $ integers. For each $ 1 \le i \le n $ it holds that $ 1 \le a_i \le m $ .

Your task is to count the number of different arrays $ b $ of length $ n $ such that:

- $ 1 \le b_i \le m $ for each $ 1 \le i \le n $ , and
- $ \gcd(b_1,b_2,b_3,...,b_i) = a_i $ for each $ 1 \le i \le n $ .

Here $ \gcd(a_1,a_2,\dots,a_i) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ a_1,a_2,\ldots,a_i $ .

Since this number can be too large, print it modulo $ 998\,244\,353 $ .

## 输入格式

Each test consist of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le 10^9 $ ) — the length of the array $ a $ and the maximum possible value of the element.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le m $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ across all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the number of different arrays satisfying the conditions above. Since this number can be large, print it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the possible arrays $ b $ are:

- $ [4,2,1] $ ;
- $ [4,2,3] $ ;
- $ [4,2,5] $ .

In the second test case, the only array satisfying the demands is $ [1,1] $ .

In the third test case, it can be proven no such array exists.

## 样例 #1

### 输入

```
5
3 5
4 2 1
2 1
1 1
5 50
2 3 5 2 3
4 1000000000
60 30 1 1
2 1000000000
1000000000 2
```

### 输出

```
3
1
0
595458194
200000000
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

