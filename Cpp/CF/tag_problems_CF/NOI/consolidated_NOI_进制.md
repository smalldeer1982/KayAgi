---
title: "Fortnite"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1994H
tag: ['哈希 hashing', '进制', 'Ad-hoc']
---

# Fortnite

## 题目描述

This is an interactive problem!

Timofey is writing a competition called Capture the Flag (or CTF for short). He has one task left, which involves hacking a security system. The entire system is based on polynomial hashes $ ^{\text{∗}} $ .

Timofey can input a string consisting of lowercase Latin letters into the system, and the system will return its polynomial hash. To hack the system, Timofey needs to find the polynomial hash parameters ( $ p $ and $ m $ ) that the system uses.

Timofey doesn't have much time left, so he will only be able to make $ 3 $ queries. Help him solve the task.

 $ ^{\text{∗}} $ The polynomial hash of a string $ s $ , consisting of lowercase Latin letters of length $ n $ , based on $ p $ and modulo $ m $ is $ (\mathrm{ord}(s_1) \cdot p ^ 0 + \mathrm{ord}(s_2) \cdot p ^ 1 + \mathrm{ord}(s_3) \cdot p ^ 2 + \ldots + \mathrm{ord}(s_n) \cdot p ^ {n - 1}) \bmod m $ . Where $ s_i $ denotes the $ i $ -th character of the string $ s $ , $ \mathrm{ord}(\mathrm{chr}) $ denotes the ordinal number of the character $ \mathrm{chr} $ in the English alphabet, and $ x \bmod m $ is the remainder of $ x $ when divided by $ m $ .

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

It is guaranteed that the $ p $ and $ m $ used by the system satisfy the conditions: $ 26 < p \leq 50 $ and $ p + 1 < m \leq 2 \cdot 10^9 $ .

## 输出格式

To make a query to the system, output ? $ s $ , where $ s $ is a string of no more than $ 50 $ characters in length, the hash of which you want to know. In response to this query, you will receive the polynomial hash of the string $ s $ .

To output the answer, output ! $ p $ $ m $ , where $ p $ is the base of the hash, and $ m $ is the modulus. After that, immediately proceed to the next test case.

You have to make not more than $ 3 $ queries ?, otherwise you will get verdict Wrong Answer.

After outputting a query, do not forget to output a newline and flush the output buffer. Otherwise, you will receive the verdict Idleness limit exceeded. To flush the buffer, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see the documentation for other languages.

## 说明/提示

Answer for the first query is $ (ord(a) \cdot 31^0 + ord(a) \cdot 31^1) \mod 59 = (1 + 1 \cdot 31) \mod 59 = 32 $ .

Answer for the second query is $ (ord(y) \cdot 31^0 + ord(b) \cdot 31^1) \mod 59 = (25 + 2 \cdot 31) \mod 59 = 28 $ .

## 样例 #1

### 输入

```
1

32

28
```

### 输出

```
? aa

? yb

! 31 59
```



---

---
title: "Matvey's Birthday"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF718E
tag: ['枚举', '最短路', '进制']
---

# Matvey's Birthday

## 题目描述

Today is Matvey's birthday. He never knows what to ask as a present so friends gave him a string $ s $ of length $ n $ . This string consists of only first eight English letters: 'a', 'b', $ ... $ , 'h'.

First question that comes to mind is: who might ever need some string? Matvey is a special boy so he instantly found what to do with this string. He used it to build an undirected graph where vertices correspond to position in the string and there is an edge between distinct positions $ a $ and $ b $ ( $ 1<=a,b<=n $ ) if at least one of the following conditions hold:

1. $ a $ and $ b $ are neighbouring, i.e. $ |a-b|=1 $ .
2. Positions $ a $ and $ b $ contain equal characters, i.e. $ s_{a}=s_{b} $ .

Then Matvey decided to find the diameter of this graph. Diameter is a maximum distance (length of the shortest path) among all pairs of vertices. Also, Matvey wants to find the number of pairs of vertices such that the distance between them is equal to the diameter of the graph. As he is very cool and experienced programmer he managed to solve this problem very fast. Will you do the same?

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the length of the string.

The second line contains the string $ s $ itself. It's guaranteed that $ s $ consists of only first eight letters of English alphabet.

## 输出格式

Print two integers — the diameter of the graph and the number of pairs of positions with the distance equal to the diameter.

## 说明/提示

Consider the second sample.

The maximum distance is $ 2 $ . It's obtained for pairs $ (1,4) $ , $ (2,4) $ , $ (4,6) $ and $ (4,7) $ .

## 样例 #1

### 输入

```
3
abc

```

### 输出

```
2 1

```

## 样例 #2

### 输入

```
7
aaabaaa

```

### 输出

```
2 4

```



---

