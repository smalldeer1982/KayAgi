---
title: "Anya and 1100"
layout: "post"
diff: 普及-
pid: CF2036C
tag: ['模拟']
---

# Anya and 1100

## 题目描述

While rummaging through things in a distant drawer, Anya found a beautiful string $ s $ consisting only of zeros and ones.

Now she wants to make it even more beautiful by performing $ q $ operations on it.

Each operation is described by two integers $ i $ ( $ 1 \le i \le |s| $ ) and $ v $ ( $ v \in \{0, 1\} $ ) and means that the $ i $ -th character of the string is assigned the value $ v $ (that is, the assignment $ s_i = v $ is performed).

But Anya loves the number $ 1100 $ , so after each query, she asks you to tell her whether the substring "1100" is present in her string (i.e. there exist such $ 1 \le i \le |s| - 3 $ that $ s_{i}s_{i + 1}s_{i + 2}s_{i + 3} = \texttt{1100} $ ).

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of the test case contains the string $ s $ ( $ 1 \leq |s| \leq 2 \cdot 10^5 $ ), consisting only of the characters "0" and "1". Here $ |s| $ denotes the length of the string $ s $ .

The next line contains an integer $ q $ ( $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the number of queries.

The following $ q $ lines contain two integers $ i $ ( $ 1 \leq i \leq |s| $ ) and $ v $ ( $ v \in \{0, 1\} $ ), describing the query.

It is guaranteed that the sum of $ |s| $ across all test cases does not exceed $ 2 \cdot 10^5 $ . It is also guaranteed that the sum of $ q $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output "YES", if "1100" is present in Anya's string; otherwise, output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 输入

```
4
100
4
1 1
2 0
2 0
3 1
1100000
3
6 1
7 1
4 1
111010
4
1 1
5 0
4 1
5 0
0100
4
3 1
1 1
2 0
2 1
```

### 输出

```
NO
NO
NO
NO
YES
YES
NO
NO
YES
YES
YES
NO
NO
NO
NO
```

