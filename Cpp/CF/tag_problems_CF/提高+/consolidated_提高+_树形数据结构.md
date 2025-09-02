---
title: "Paths on the Tree"
layout: "post"
diff: 提高+/省选-
pid: CF1746D
tag: ['动态规划 DP', '贪心', '树形数据结构']
---

# Paths on the Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a score array $ s_1, s_2, \ldots, s_n $ .

A multiset of $ k $ simple paths is called valid if the following two conditions are both true.

- Each path starts from $ 1 $ .
- Let $ c_i $ be the number of paths covering vertex $ i $ . For each pair of vertices $ (u,v) $ ( $ 2\le u,v\le n $ ) that have the same parent, $ |c_u-c_v|\le 1 $ holds.

 The value of the path multiset is defined as $ \sum\limits_{i=1}^n c_i s_i $ .It can be shown that it is always possible to find at least one valid multiset. Find the maximum value among all valid multisets.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two space-separated integers $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) and $ k $ ( $ 1 \le k \le 10^9 $ ) — the size of the tree and the required number of paths.

The second line contains $ n - 1 $ space-separated integers $ p_2,p_3,\ldots,p_n $ ( $ 1\le p_i\le n $ ), where $ p_i $ is the parent of the $ i $ -th vertex. It is guaranteed that this value describe a valid tree with root $ 1 $ .

The third line contains $ n $ space-separated integers $ s_1,s_2,\ldots,s_n $ ( $ 0 \le s_i \le 10^4 $ ) — the scores of the vertices.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10 ^ 5 $ .

## 输出格式

For each test case, print a single integer — the maximum value of a path multiset.

## 说明/提示

In the first test case, one of optimal solutions is four paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , $ 1 \to 4 $ , here $ c=[4,2,2,2,2] $ . The value equals to $ 4\cdot 6+ 2\cdot 2+2\cdot 1+2\cdot 5+2\cdot 7=54 $ .

In the second test case, one of optimal solution is three paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , here $ c=[3,2,2,1,2] $ . The value equals to $ 3\cdot 6+ 2\cdot 6+2\cdot 1+1\cdot 4+2\cdot 10=56 $ .

## 样例 #1

### 输入

```
2
5 4
1 2 1 3
6 2 1 5 7
5 3
1 2 1 3
6 6 1 4 10
```

### 输出

```
54
56
```



---

---
title: "Hossam and (sub-)palindromic tree"
layout: "post"
diff: 提高+/省选-
pid: CF1771D
tag: ['树形数据结构', '区间 DP']
---

# Hossam and (sub-)palindromic tree

## 题目描述

Hossam has an unweighted tree $ G $ with letters in vertices.

Hossam defines $ s(v, \, u) $ as a string that is obtained by writing down all the letters on the unique simple path from the vertex $ v $ to the vertex $ u $ in the tree $ G $ .

A string $ a $ is a subsequence of a string $ s $ if $ a $ can be obtained from $ s $ by deletion of several (possibly, zero) letters. For example, "dores", "cf", and "for" are subsequences of "codeforces", while "decor" and "fork" are not.

A palindrome is a string that reads the same from left to right and from right to left. For example, "abacaba" is a palindrome, but "abac" is not.

Hossam defines a sub-palindrome of a string $ s $ as a subsequence of $ s $ , that is a palindrome. For example, "k", "abba" and "abhba" are sub-palindromes of the string "abhbka", but "abka" and "cat" are not.

Hossam defines a maximal sub-palindrome of a string $ s $ as a sub-palindrome of $ s $ , which has the maximal length among all sub-palindromes of $ s $ . For example, "abhbka" has only one maximal sub-palindrome — "abhba". But it may also be that the string has several maximum sub-palindromes: the string "abcd" has $ 4 $ maximum sub-palindromes.

Help Hossam find the length of the longest maximal sub-palindrome among all $ s(v, \, u) $ in the tree $ G $ .

Note that the sub-palindrome is a subsequence, not a substring.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 200 $ ) — the number of test cases.

The first line of each test case has one integer number $ n $ ( $ 1 \le n \le 2 \cdot 10^3 $ ) — the number of vertices in the graph.

The second line contains a string $ s $ of length $ n $ , the $ i $ -th symbol of which denotes the letter on the vertex $ i $ . It is guaranteed that all characters in this string are lowercase English letters.

The next $ n - 1 $ lines describe the edges of the tree. Each edge is given by two integers $ v $ and $ u $ ( $ 1 \le v, \, u \le n $ , $ v \neq u $ ). These two numbers mean that there is an edge $ (v, \, u) $ in the tree. It is guaranteed that the given edges form a tree.

It is guaranteed that sum of all $ n $ doesn't exceed $ 2 \cdot 10^3 $ .

## 输出格式

For each test case output one integer — the length of the longest maximal sub-palindrome among all $ s(v, \, u) $ .

## 说明/提示

In the first example the maximal subpalindromes are "aaa" with letters in vertices $ 1, \, 3, \, 5 $ , or "aca" with letters in vertices $ 1, \, 4, \, 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771D/2a7d49fbfdc47b629dbea5a5d05163d26e820257.png) The tree from the first example.In the second example there is only one maximal palindrome "bacab" with letters in vertices $ 4, \, 2, \, 1, \, 5, \, 9 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771D/1a3ef86962248c5a486bd8acba156707a2fa8aec.png) The tree from the second example.

## 样例 #1

### 输入

```
2
5
abaca
1 2
1 3
3 4
4 5
9
caabadedb
1 2
2 3
2 4
1 5
5 6
5 7
5 8
8 9
```

### 输出

```
3
5
```



---

---
title: "Balanced Unshuffle (Hard)"
layout: "post"
diff: 提高+/省选-
pid: CF1970A3
tag: ['树形数据结构']
---

# Balanced Unshuffle (Hard)

## 题目描述

The only difference with the medium version is the maximum length of the input.

A parentheses sequence is a string consisting of characters "(" and ")", for example "(()((".

A balanced parentheses sequence is a parentheses sequence which can become a valid mathematical expression after inserting numbers and operations into it, for example "(()(()))".

The balance of a parentheses sequence is defined as the number of opening parentheses "(" minus the number of closing parentheses ")". For example, the balance of the sequence "(()((" is 3.

A balanced parentheses sequence can also be defined as a parentheses sequence with balance 0 such that each of its prefixes has a non-negative balance.

We define the balanced shuffle operation that takes a parentheses sequence and returns a parentheses sequence as follows: first, for every character of the input sequence, we compute the balance of the prefix of the sequence before that character and write those down in a table together with the positions of the characters in the input sequence, for example:

Prefix balance01212321Position12345678Character(()(()))Then, we sort the columns of this table in increasing order of prefix balance, breaking ties in decreasing order of position. In the above example, we get:

Prefix balance01112223Position18427536Character()(()())The last row of this table forms another parentheses sequence, in this case "()(()())". This sequence is called the result of applying the balanced shuffle operation to the input sequence, or in short just the balanced shuffle of the input sequence.

Surprisingly, it turns out that the balanced shuffle of any balanced parentheses sequence is always another balanced parentheses sequence (we will omit the proof for brevity). Even more surprisingly, the balanced shuffles of two different balanced parentheses sequences are always different, therefore the balanced shuffle operation is a bijection on the set of balanced parentheses sequences of any given length (we will omit this proof, too).

You are given a balanced parentheses sequence. Find its preimage: the balanced parentheses sequence the balanced shuffle of which is equal to the given sequence.

## 输入格式

The only line of input contains a string $ s $ consisting only of characters "(" and ")". This string is guaranteed to be a non-empty balanced parentheses sequence with its length not exceeding $ 500\,000 $ .

## 输出格式

Print the balanced parentheses sequence $ t $ such that the balanced shuffle of $ t $ is equal to $ s $ . It is guaranteed that the answer always exists and is unique.

## 样例 #1

### 输入

```
()(()())
```

### 输出

```
(()(()))
```



---

