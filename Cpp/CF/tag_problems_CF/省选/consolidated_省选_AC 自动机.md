---
title: "You Are Given Some Strings..."
layout: "post"
diff: 省选/NOI-
pid: CF1202E
tag: ['字符串', '动态规划 DP', 'AC 自动机']
---

# You Are Given Some Strings...

## 题目描述

You are given a string $ t $ and $ n $ strings $ s_1, s_2, \dots, s_n $ . All strings consist of lowercase Latin letters.

Let $ f(t, s) $ be the number of occurences of string $ s $ in string $ t $ . For example, $ f('\text{aaabacaa}', '\text{aa}') = 3 $ , and $ f('\text{ababa}', '\text{aba}') = 2 $ .

Calculate the value of $ \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} f(t, s_i + s_j) $ , where $ s + t $ is the concatenation of strings $ s $ and $ t $ . Note that if there are two pairs $ i_1 $ , $ j_1 $ and $ i_2 $ , $ j_2 $ such that $ s_{i_1} + s_{j_1} = s_{i_2} + s_{j_2} $ , you should include both $ f(t, s_{i_1} + s_{j_1}) $ and $ f(t, s_{i_2} + s_{j_2}) $ in answer.

## 输入格式

The first line contains string $ t $ ( $ 1 \le |t| \le 2 \cdot 10^5 $ ).

The second line contains integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

Each of next $ n $ lines contains string $ s_i $ ( $ 1 \le |s_i| \le 2 \cdot 10^5 $ ).

It is guaranteed that $ \sum\limits_{i=1}^{n} |s_i| \le 2 \cdot 10^5 $ . All strings consist of lowercase English letters.

## 输出格式

Print one integer — the value of $ \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} f(t, s_i + s_j) $ .

## 样例 #1

### 输入

```
aaabacaa
2
a
aa

```

### 输出

```
5

```

## 样例 #2

### 输入

```
aaabacaa
4
a
a
a
b

```

### 输出

```
33

```



---

---
title: "e-Government"
layout: "post"
diff: 省选/NOI-
pid: CF163E
tag: ['字符串', '线段树', 'AC 自动机']
---

# e-Government

## 题目描述

The best programmers of Embezzland compete to develop a part of the project called "e-Government" — the system of automated statistic collecting and press analysis.

We know that any of the $ k $ citizens can become a member of the Embezzland government. The citizens' surnames are $ a_{1},a_{2},...,a_{k} $ . All surnames are different. Initially all $ k $ citizens from this list are members of the government. The system should support the following options:

- Include citizen $ a_{i} $ to the government.
- Exclude citizen $ a_{i} $ from the government.
- Given a newspaper article text, calculate how politicized it is. To do this, for every active government member the system counts the number of times his surname occurs in the text as a substring. All occurrences are taken into consideration, including the intersecting ones. The degree of politicization of a text is defined as the sum of these values for all active government members.

Implement this system.

## 输入格式

The first line contains space-separated integers $ n $ and $ k $ ( $ 1<=n,k<=10^{5} $ ) — the number of queries to the system and the number of potential government members.

Next $ k $ lines contain the surnames $ a_{1},a_{2},...,a_{k} $ , one per line. All surnames are pairwise different.

Next $ n $ lines contain queries to the system, one per line. Each query consists of a character that determines an operation and the operation argument, written consecutively without a space.

Operation "include in the government" corresponds to the character "+", operation "exclude" corresponds to "-". An argument of those operations is an integer between $ 1 $ and $ k $ — the index of the citizen involved in the operation. Any citizen can be included and excluded from the government an arbitrary number of times in any order. Including in the government a citizen who is already there or excluding the citizen who isn't there changes nothing.

The operation "calculate politicization" corresponds to character "?". Its argument is a text.

All strings — surnames and texts — are non-empty sequences of lowercase Latin letters. The total length of all surnames doesn't exceed $ 10^{6} $ , the total length of all texts doesn't exceed $ 10^{6} $ .

## 输出格式

For any "calculate politicization" operation print on a separate line the degree of the politicization of the given text. Print nothing for other operations.

## 样例 #1

### 输入

```
7 3
a
aa
ab
?aaab
-2
?aaab
-3
?aaab
+2
?aabbaa

```

### 输出

```
6
4
3
6

```



---

---
title: "String Set Queries"
layout: "post"
diff: 省选/NOI-
pid: CF710F
tag: ['分治', '哈希 hashing', '分块', '字典树 Trie', 'AC 自动机', 'KMP 算法']
---

# String Set Queries

## 题目描述

You should process $ m $ queries over a set $ D $ of strings. Each query is one of three kinds:

1. Add a string $ s $ to the set $ D $ . It is guaranteed that the string $ s $ was not added before.
2. Delete a string $ s $ from the set $ D $ . It is guaranteed that the string $ s $ is in the set $ D $ .
3. For the given string $ s $ find the number of occurrences of the strings from the set $ D $ . If some string $ p $ from $ D $ has several occurrences in $ s $ you should count all of them.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query of the third type. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 输入格式

The first line contains integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of queries.

Each of the next $ m $ lines contains integer $ t $ ( $ 1<=t<=3 $ ) and nonempty string $ s $ — the kind of the query and the string to process. All strings consist of only lowercase English letters.

The sum of lengths of all strings in the input will not exceed $ 3·10^{5} $ .

## 输出格式

For each query of the third kind print the only integer $ c $ — the desired number of occurrences in the string $ s $ .

## 样例 #1

### 输入

```
5
1 abc
3 abcabc
2 abc
1 aba
3 abababc

```

### 输出

```
2
2

```

## 样例 #2

### 输入

```
10
1 abc
1 bcd
1 abcd
3 abcd
2 abcd
3 abcd
2 bcd
3 abcd
2 abc
3 abcd

```

### 输出

```
3
2
1
0

```



---

