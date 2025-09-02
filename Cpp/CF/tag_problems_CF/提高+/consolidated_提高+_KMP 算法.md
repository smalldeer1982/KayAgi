---
title: "Prefix Function Queries"
layout: "post"
diff: 提高+/省选-
pid: CF1721E
tag: ['KMP 算法', '有限状态自动机']
---

# Prefix Function Queries

## 题目描述

You are given a string $ s $ , consisting of lowercase Latin letters.

You are asked $ q $ queries about it: given another string $ t $ , consisting of lowercase Latin letters, perform the following steps:

1. concatenate $ s $ and $ t $ ;
2. calculate the prefix function of the resulting string $ s+t $ ;
3. print the values of the prefix function on positions $ |s|+1, |s|+2, \dots, |s|+|t| $ ( $ |s| $ and $ |t| $ denote the lengths of strings $ s $ and $ t $ , respectively);
4. revert the string back to $ s $ .

The prefix function of a string $ a $ is a sequence $ p_1, p_2, \dots, p_{|a|} $ , where $ p_i $ is the maximum value of $ k $ such that $ k < i $ and $ a[1..k]=a[i-k+1..i] $ ( $ a[l..r] $ denotes a contiguous substring of a string $ a $ from a position $ l $ to a position $ r $ , inclusive). In other words, it's the longest proper prefix of the string $ a[1..i] $ that is equal to its suffix of the same length.

## 输入格式

The first line contains a non-empty string $ s $ ( $ 1 \le |s| \le 10^6 $ ), consisting of lowercase Latin letters.

The second line contains a single integer $ q $ ( $ 1 \le q \le 10^5 $ ) — the number of queries.

Each of the next $ q $ lines contains a query: a non-empty string $ t $ ( $ 1 \le |t| \le 10 $ ), consisting of lowercase Latin letters.

## 输出格式

For each query, print the values of the prefix function of a string $ s+t $ on positions $ |s|+1, |s|+2, \dots, |s|+|t| $ .

## 样例 #1

### 输入

```
aba
6
caba
aba
bababa
aaaa
b
forces
```

### 输出

```
0 1 2 3 
1 2 3 
2 3 4 5 6 7 
1 1 1 1 
2 
0 0 0 0 0 0
```

## 样例 #2

### 输入

```
aacba
4
aaca
cbbb
aab
ccaca
```

### 输出

```
2 2 3 1 
0 0 0 0 
2 2 0 
0 0 1 0 1
```



---

---
title: "Test"
layout: "post"
diff: 提高+/省选-
pid: CF25E
tag: ['字符串', '枚举', 'KMP 算法']
---

# Test

## 题目描述

Sometimes it is hard to prepare tests for programming problems. Now Bob is preparing tests to new problem about strings — input data to his problem is one string. Bob has 3 wrong solutions to this problem. The first gives the wrong answer if the input data contains the substring $ s_{1} $ , the second enters an infinite loop if the input data contains the substring $ s_{2} $ , and the third requires too much memory if the input data contains the substring $ s_{3} $ . Bob wants these solutions to fail single test. What is the minimal length of test, which couldn't be passed by all three Bob's solutions?

## 输入格式

There are exactly 3 lines in the input data. The $ i $ -th line contains string $ s_{i} $ . All the strings are non-empty, consists of lowercase Latin letters, the length of each string doesn't exceed $ 10^{5} $ .

## 输出格式

Output one number — what is minimal length of the string, containing $ s_{1} $ , $ s_{2} $ and $ s_{3} $ as substrings.

## 样例 #1

### 输入

```
ab
bc
cd

```

### 输出

```
4

```

## 样例 #2

### 输入

```
abacaba
abaaba
x

```

### 输出

```
11

```



---

---
title: "Lucky Common Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF346B
tag: ['字符串', '动态规划 DP', '枚举', 'KMP 算法']
---

# Lucky Common Subsequence

## 题目描述

In mathematics, a subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements. For example, the sequence BDF is a subsequence of ABCDEF. A substring of a string is a continuous subsequence of the string. For example, BCD is a substring of ABCDEF.

You are given two strings $ s_{1} $ , $ s_{2} $ and another string called $ virus $ . Your task is to find the longest common subsequence of $ s_{1} $ and $ s_{2} $ , such that it doesn't contain $ virus $ as a substring.

## 输入格式

The input contains three strings in three separate lines: $ s_{1} $ , $ s_{2} $ and $ virus $ ( $ 1<=|s_{1}|,|s_{2}|,|virus|<=100 $ ). Each string consists only of uppercase English letters.

## 输出格式

Output the longest common subsequence of $ s_{1} $ and $ s_{2} $ without $ virus $ as a substring. If there are multiple answers, any of them will be accepted.

If there is no valid common subsequence, output 0.

## 样例 #1

### 输入

```
AJKEQSLOBSROFGZ
OVGURWZLWVLUXTH
OZ

```

### 输出

```
ORZ

```

## 样例 #2

### 输入

```
AA
A
A

```

### 输出

```
0

```



---

