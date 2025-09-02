---
title: "Letter Picking"
layout: "post"
diff: 普及+/提高
pid: CF1728D
tag: ['动态规划 DP', '贪心', '区间 DP']
---

# Letter Picking

## 题目描述

Alice and Bob are playing a game. Initially, they are given a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string is even. Each player also has a string of their own, initially empty.

Alice starts, then they alternate moves. In one move, a player takes either the first or the last letter of the string $ s $ , removes it from $ s $ and prepends (adds to the beginning) it to their own string.

The game ends when the string $ s $ becomes empty. The winner is the player with a lexicographically smaller string. If the players' strings are equal, then it's a draw.

A string $ a $ is lexicographically smaller than a string $ b $ if there exists such position $ i $ that $ a_j = b_j $ for all $ j < i $ and $ a_i < b_i $ .

What is the result of the game if both players play optimally (e. g. both players try to win; if they can't, then try to draw)?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of testcases.

Each testcase consists of a single line — a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string $ s $ is even.

The total length of the strings over all testcases doesn't exceed $ 2000 $ .

## 输出格式

For each testcase, print the result of the game if both players play optimally. If Alice wins, print "Alice". If Bob wins, print "Bob". If it's a draw, print "Draw".

## 说明/提示

One of the possible games Alice and Bob can play in the first testcase:

1. Alice picks the first letter in $ s $ : $ s= $ "orces", $ a= $ "f", $ b= $ "";
2. Bob picks the last letter in $ s $ : $ s= $ "orce", $ a= $ "f", $ b= $ "s";
3. Alice picks the last letter in $ s $ : $ s= $ "orc", $ a= $ "ef", $ b= $ "s";
4. Bob picks the first letter in $ s $ : $ s= $ "rc", $ a= $ "ef", $ b= $ "os";
5. Alice picks the last letter in $ s $ : $ s= $ "r", $ a= $ "cef", $ b= $ "os";
6. Bob picks the remaining letter in $ s $ : $ s= $ "", $ a= $ "cef", $ b= $ "ros".

Alice wins because "cef" &lt; "ros". Neither of the players follows any strategy in this particular example game, so it doesn't show that Alice wins if both play optimally.

## 样例 #1

### 输入

```
2
forces
abba
```

### 输出

```
Alice
Draw
```



---

---
title: "Minimizing the Sum"
layout: "post"
diff: 普及+/提高
pid: CF1969C
tag: ['动态规划 DP', '区间 DP']
---

# Minimizing the Sum

## 题目描述

You are given an integer array $ a $ of length $ n $ .

You can perform the following operation: choose an element of the array and replace it with any of its neighbor's value.

For example, if $ a=[3, 1, 2] $ , you can get one of the arrays $ [3, 3, 2] $ , $ [3, 2, 2] $ and $ [1, 1, 2] $ using one operation, but not $ [2, 1, 2 $ \] or $ [3, 4, 2] $ .

Your task is to calculate the minimum possible total sum of the array if you can perform the aforementioned operation at most $ k $ times.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 3 \cdot 10^5 $ ; $ 0 \le k \le 10 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

Additional constraint on the input: the sum of $ n $ over all test cases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum possible total sum of the array if you can perform the aforementioned operation at most $ k $ times.

## 说明/提示

In the first example, one of the possible sequences of operations is the following: $ [3, 1, 2] \rightarrow [1, 1, 2 $ \].

In the second example, you do not need to apply the operation.

In the third example, one of the possible sequences of operations is the following: $ [2, 2, 1, 3] \rightarrow [2, 1, 1, 3] \rightarrow [2, 1, 1, 1] $ .

In the fourth example, one of the possible sequences of operations is the following: $ [4, 1, 2, 2, 4, 3] \rightarrow [1, 1, 2, 2, 4, 3] \rightarrow [1, 1, 1, 2, 4, 3] \rightarrow [1, 1, 1, 2, 2, 3] $ .

## 样例 #1

### 输入

```
4
3 1
3 1 2
1 3
5
4 2
2 2 1 3
6 3
4 1 2 2 4 3
```

### 输出

```
4
5
5
10
```



---

---
title: "Queries for Number of Palindromes"
layout: "post"
diff: 普及+/提高
pid: CF245H
tag: ['字符串', '动态规划 DP', '区间 DP', '前缀和']
---

# Queries for Number of Palindromes

## 题目描述

给你一个字符串s由小写字母组成，有q组询问，每组询问给你两个数，l和r，问在字符串区间l到r的字串中，包含多少回文串。

## 输入格式

第1行，给出s，s的长度小于5000
第2行给出q(1<=q<=10^6)
第2至2+q行 给出每组询问的l和r

## 输出格式

输出每组询问所问的数量。

## 样例 #1

### 输入

```
caaaba
5
1 1
1 4
2 3
4 6
4 5

```

### 输出

```
1
7
3
4
2

```



---

