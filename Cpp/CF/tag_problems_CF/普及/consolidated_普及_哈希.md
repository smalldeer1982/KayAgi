---
title: "Beautiful Triple Pairs"
layout: "post"
diff: 普及/提高-
pid: CF1974C
tag: ['哈希 hashing', '容斥原理']
---

# Beautiful Triple Pairs

## 题目描述

Polycarp was given an array $ a $ of $ n $ integers. He really likes triples of numbers, so for each $ j $ ( $ 1 \le j \le n - 2 $ ) he wrote down a triple of elements $ [a_j, a_{j + 1}, a_{j + 2}] $ .

Polycarp considers a pair of triples $ b $ and $ c $ beautiful if they differ in exactly one position, that is, one of the following conditions is satisfied:

- $ b_1 \ne c_1 $ and $ b_2 = c_2 $ and $ b_3 = c_3 $ ;
- $ b_1 = c_1 $ and $ b_2 \ne c_2 $ and $ b_3 = c_3 $ ;
- $ b_1 = c_1 $ and $ b_2 = c_2 $ and $ b_3 \ne c_3 $ .

Find the number of beautiful pairs of triples among the written triples $ [a_j, a_{j + 1}, a_{j + 2}] $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 3 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — the elements of the array.

It is guaranteed that the sum of the values of $ n $ for all test cases in the test does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of beautiful pairs of triples among the pairs of the form $ [a_j, a_{j + 1}, a_{j + 2}] $ .

Note that the answer may not fit into 32-bit data types.

## 说明/提示

In the first example, $ a = [3, 2, 2, 2, 3] $ , Polycarp will write the following triples:

1. $ [3, 2, 2] $ ;
2. $ [2, 2, 2] $ ;
3. $ [2, 2, 3] $ .

 The beautiful pairs are triple $ 1 $ with triple $ 2 $ and triple $ 2 $ with triple $ 3 $ .In the third example, $ a = [1, 2, 3, 2, 2, 3, 4, 2] $ , Polycarp will write the following triples:

1. $ [1, 2, 3] $ ;
2. $ [2, 3, 2] $ ;
3. $ [3, 2, 2] $ ;
4. $ [2, 2, 3] $ ;
5. $ [2, 3, 4] $ ;
6. $ [3, 4, 2] $ ;

 The beautiful pairs are triple $ 1 $ with triple $ 4 $ , triple $ 2 $ with triple $ 5 $ , and triple $ 3 $ with triple $ 6 $ .

## 样例 #1

### 输入

```
8
5
3 2 2 2 3
5
1 2 1 2 1
8
1 2 3 2 2 3 4 2
4
2 1 1 1
8
2 1 1 2 1 1 1 1
7
2 1 1 1 1 1 1
6
2 1 1 1 1 1
5
2 1 1 1 1
```

### 输出

```
2
0
3
1
8
4
3
2
```



---

---
title: "Message Transmission Error (hard version)"
layout: "post"
diff: 普及/提高-
pid: CF2010C2
tag: ['字符串', '哈希 hashing', 'KMP 算法']
---

# Message Transmission Error (hard version)

## 题目描述

这是一个难度较高的问题。它与简单版的区别仅在于约束条件不同。

在伯兰州立大学，服务器之间的本地网络并非总是运行无误。当连续传输两条相同的信息时，可能会发生错误，导致两条信息合并为一条。在这种合并中，第一条信息的结尾与第二条信息的开头重合。当然，合并只能发生在相同字符处。合并的长度必须是一个小于信息文本长度的正数。

例如，当连续传送两条信息```abrakadabra```时，可能会出现所述类型的错误、导致出现类似```abrakadabrakadabra```或```abrakadabrakadabra```的信息(前者在一个字符处发生合并，后者在四个字符处发生合并)。

给定接收到的报文 ```t``` ，判断这是否可能是本地网络运行中出现所述类型错误的结果，如果是，请确定可能的值 ```s``` 。

两个报文完全重叠的情况不应视为错误。例如，如果收到的报文是```abcd```，则应认为其中没有错误。同样，简单地在一条信息后附加另一条信息也不是错误的标志。例如，如果收到的信息是 ```abcabc```，也应认为其中没有错误。

## 输入格式

一个非空字符串 ```t``` ，该字符串由拉丁字母的小写字母组成。字符串 ```t``` 的长度不超过 ```4×10⁵``` 个字符。

## 输出格式

如果信息 ```t``` 不能包含错误，则在单行输出中输出 ```NO``` (不带引号)。
否则，在第一行输出```YES```(不带引号)，在下一行输出字符串``` s ```(可能导致错误的信息)。如果有多个可能的答案，可以输出任意一个。

## 样例 #1

### 输入

```
abrakadabrabrakadabra
```

### 输出

```
YES
abrakadabra
```

## 样例 #2

### 输入

```
acacacaca
```

### 输出

```
YES
acacaca
```

## 样例 #3

### 输入

```
abcabc
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
abababab
```

### 输出

```
YES
ababab
```

## 样例 #5

### 输入

```
tatbt
```

### 输出

```
NO
```



---

