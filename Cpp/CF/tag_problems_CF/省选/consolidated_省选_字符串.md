---
title: "AB-Strings"
layout: "post"
diff: 省选/NOI-
pid: CF1012D
tag: ['字符串', '前缀和']
---

# AB-Strings

## 题目描述

## 题面描述
给定两个只包含 $\texttt{a}$ 和 $\texttt{b}$ 的字符串，每次操作可以把两个字符串的任意前缀进行交换（前缀长度可以为 $0$），问最少多少次操作可以使的一个串只有 $\texttt{a}$，另一个串只有 $\texttt{b}$。

## 输入格式

两行，一行一个字符串，保证串长 $\leq 200000$。

保证两个串中有 $\texttt{a}$ 和 $\texttt{b}$。

## 输出格式

第一行一个整数 $n(0\leq n\leq 500000)$，表示答案。

后面 $n$ 行，一行两个整数，表示每次操作时被交换的两个串的前缀长度。

## 样例 #1

### 输入

```
bab
bb

```

### 输出

```
2
1 0
1 3

```

## 样例 #2

### 输入

```
bbbb
aaa

```

### 输出

```
0

```



---

---
title: "Bracket Substring"
layout: "post"
diff: 省选/NOI-
pid: CF1015F
tag: ['字符串', '递推', '枚举']
---

# Bracket Substring

## 题目描述

You are given a bracket sequence $ s $ (not necessarily a regular one). A bracket sequence is a string containing only characters '(' and ')'.

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Your problem is to calculate the number of regular bracket sequences of length $ 2n $ containing the given bracket sequence $ s $ as a substring (consecutive sequence of characters) modulo $ 10^9+7 $ ( $ 1000000007 $ ).

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 100 $ ) — the half-length of the resulting regular bracket sequences (the resulting sequences must have length equal to $ 2n $ ).

The second line of the input contains one string $ s $ ( $ 1 \le |s| \le 200 $ ) — the string $ s $ that should be a substring in each of the resulting regular bracket sequences ( $ |s| $ is the length of $ s $ ).

## 输出格式

Print only one integer — the number of regular bracket sequences containing the given bracket sequence $ s $ as a substring. Since this number can be huge, print it modulo $ 10^9+7 $ ( $ 1000000007 $ ).

## 说明/提示

All regular bracket sequences satisfying the conditions above for the first example:

- "(((()))())";
- "((()()))()";
- "((()))()()";
- "(()(()))()";
- "()((()))()".

All regular bracket sequences satisfying the conditions above for the second example:

- "((()))";
- "(()())";
- "(())()";
- "()(())".

And there is no regular bracket sequences of length $ 4 $ containing "(((" as a substring in the third example.

## 样例 #1

### 输入

```
5
()))()

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3
(()

```

### 输出

```
4

```

## 样例 #3

### 输入

```
2
(((

```

### 输出

```
0

```



---

---
title: "The Supersonic Rocket"
layout: "post"
diff: 省选/NOI-
pid: CF1017E
tag: ['字符串', '凸包', 'KMP 算法']
---

# The Supersonic Rocket

## 题目描述

After the war, the supersonic rocket became the most common public transportation.

Each supersonic rocket consists of two "engines". Each engine is a set of "power sources". The first engine has $ n $ power sources, and the second one has $ m $ power sources. A power source can be described as a point $ (x_i, y_i) $ on a 2-D plane. All points in each engine are different.

You can manipulate each engine separately. There are two operations that you can do with each engine. You can do each operation as many times as you want.

1. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i+a, y_i+b) $ , $ a $ and $ b $ can be any real numbers. In other words, all power sources will be shifted.
2. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i \cos \theta - y_i \sin \theta, x_i \sin \theta + y_i \cos \theta) $ , $ \theta $ can be any real number. In other words, all power sources will be rotated.

The engines work as follows: after the two engines are powered, their power sources are being combined (here power sources of different engines may coincide). If two power sources $ A(x_a, y_a) $ and $ B(x_b, y_b) $ exist, then for all real number $ k $ that $ 0 \lt k \lt 1 $ , a new power source will be created $ C_k(kx_a+(1-k)x_b,ky_a+(1-k)y_b) $ . Then, this procedure will be repeated again with all new and old power sources. After that, the "power field" from all power sources will be generated (can be considered as an infinite set of all power sources occurred).

A supersonic rocket is "safe" if and only if after you manipulate the engines, destroying any power source and then power the engine, the power field generated won't be changed (comparing to the situation where no power source erased). Two power fields are considered the same if and only if any power source in one field belongs to the other one as well.

Given a supersonic rocket, check whether it is safe or not.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 3 \le n, m \le 10^5 $ ) — the number of power sources in each engine.

Each of the next $ n $ lines contains two integers $ x_i $ and $ y_i $ ( $ 0\leq x_i, y_i\leq 10^8 $ ) — the coordinates of the $ i $ -th power source in the first engine.

Each of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 0\leq x_i, y_i\leq 10^8 $ ) — the coordinates of the $ i $ -th power source in the second engine.

It is guaranteed that there are no two or more power sources that are located in the same point in each engine.

## 输出格式

Print "YES" if the supersonic rocket is safe, otherwise "NO".

You can print each letter in an arbitrary case (upper or lower).

## 说明/提示

The first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/1f54366cb2efd6f1fd1d0617b722b5e3979dfd89.png)Those near pairs of blue and orange points actually coincide.First, manipulate the first engine: use the second operation with $ \theta = \pi $ (to rotate all power sources $ 180 $ degrees).

The power sources in the first engine become $ (0, 0) $ , $ (0, -2) $ , and $ (-2, 0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/d9732486b953667a46772450be0d244f2cb20626.png)Second, manipulate the second engine: use the first operation with $ a = b = -2 $ .

The power sources in the second engine become $ (-2, 0) $ , $ (0, 0) $ , $ (0, -2) $ , and $ (-1, -1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/f5d3a1ffc842f837240530d5f9c0ef57b3d408b7.png)You can examine that destroying any point, the power field formed by the two engines are always the solid triangle $ (0, 0) $ , $ (-2, 0) $ , $ (0, -2) $ .

In the second sample, no matter how you manipulate the engines, there always exists a power source in the second engine that power field will shrink if you destroy it.

## 样例 #1

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
1 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
0 0

```

### 输出

```
NO

```



---

---
title: "Side Transmutations"
layout: "post"
diff: 省选/NOI-
pid: CF1065E
tag: ['字符串']
---

# Side Transmutations

## 题目描述

考虑一个字符集合$A$（$A$中元素互不相同）和一个长度为$n$的字符串$S$，其中$S$中的字符都属于集合$A$。



给你一个包含 $m$ 个整数的序列 $b$  ($b_1<b_2<\dots<b_m$)。你可以对字符串 $S$ 作以下的操作：



1.选择一个合法的 $i$ ,并且令 $k=b_i$ ;



2.取出 $S$ 中前 $k$ 个字符 $Pr_k$ ;



3.取出 $S$ 中后 $k$ 个字符$Su_k$ ;



4.将 $S$ 中前 $k$ 个字符替换成翻转后的 $Su_k$ ;



5.将 $S$ 中后 $k$ 个字符替换成翻转后的 $Pr_k$ ;



举个例子，我们令 $S=$ "abcdefghi"，$k=2$ 。这时$Pr_2=$ "ab"，$Su_2=$ "hi"，翻转后有 $Pr_2=$ "ba"，$Su_2=$ "ih"，那么最终得到的字符串 $S$ 就是 "ihcdefgba"。



这个操作可以被执行许多次（可能是零次），任何一个 $i$ 也可以被使用多次。



我们将字符串 $S$ 和 $T$ 称为相等的字符串，当且仅当存在一个操作序列，将字符串 $S$ 变成 $T$。对于上面的例子来说，"abcdefghi" 和 "ihcdefgba" 是相等的。注意到 $S$ 和它自己也是相等的。

你的任务很简单，数出互不相同的字符串的个数。

最终的答案可能会非常大，因此你只需要输出答案 $mod$ $998244353$ 的结果。

## 输入格式

第一行包括三个整数 $n$，$m$ 和 $|A|$（$2 \leq n \leq 10^9$，$1 \leq m \leq min(\frac{n}{2},2 * 10^5)$，$1\leq |A|\leq 10^9$），分别是字符串的长度，序列 $b$ 的大小，以及字符集 $A$ 的大小。

第二行包括 $m$ 个整数： $b_1,b_2,\dots,b_m$。

## 输出格式

输出一个整数，即答案 $mod$ $998244353$ 的结果。

## 样例 #1

### 输入

```
3 1 2
1

```

### 输出

```
6

```

## 样例 #2

### 输入

```
9 2 26
2 3

```

### 输出

```
150352234

```

## 样例 #3

### 输入

```
12 3 1
2 5 6

```

### 输出

```
1

```



---

---
title: "Yet Another LCP Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1073G
tag: ['字符串', '图论', '后缀自动机 SAM', '虚树', '后缀数组 SA', '后缀树']
---

# Yet Another LCP Problem

## 题目描述

Let $ \text{LCP}(s, t) $ be the length of the longest common prefix of strings $ s $ and $ t $ . Also let $ s[x \dots y] $ be the substring of $ s $ from index $ x $ to index $ y $ (inclusive). For example, if $ s =  $ "abcde", then $ s[1 \dots 3] = $ "abc", $ s[2 \dots 5] = $ "bcde".

You are given a string $ s $ of length $ n $ and $ q $ queries. Each query is a pair of integer sets $ a_1, a_2, \dots, a_k $ and $ b_1, b_2, \dots, b_l $ . Calculate $ \sum\limits_{i = 1}^{i = k} \sum\limits_{j = 1}^{j = l}{\text{LCP}(s[a_i \dots n], s[b_j \dots n])} $ for each query.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the length of string $ s $ and the number of queries, respectively.

The second line contains a string $ s $ consisting of lowercase Latin letters ( $ |s| = n $ ).

Next $ 3q $ lines contains descriptions of queries — three lines per query. The first line of each query contains two integers $ k_i $ and $ l_i $ ( $ 1 \le k_i, l_i \le n $ ) — sizes of sets $ a $ and $ b $ respectively.

The second line of each query contains $ k_i $ integers $ a_1, a_2, \dots a_{k_i} $ ( $ 1 \le a_1 < a_2 < \dots < a_{k_i} \le n $ ) — set $ a $ .

The third line of each query contains $ l_i $ integers $ b_1, b_2, \dots b_{l_i} $ ( $ 1 \le b_1 < b_2 < \dots < b_{l_i} \le n $ ) — set $ b $ .

It is guaranteed that $ \sum\limits_{i = 1}^{i = q}{k_i} \le 2 \cdot 10^5 $ and $ \sum\limits_{i = 1}^{i = q}{l_i} \le 2 \cdot 10^5 $ .

## 输出格式

Print $ q $ integers — answers for the queries in the same order queries are given in the input.

## 说明/提示

Description of queries:

1. In the first query $ s[1 \dots 7] = \text{abacaba} $ and $ s[2 \dots 7] = \text{bacaba} $ are considered. The answer for the query is $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{bacaba}) + \text{LCP}(\text{bacaba}, \text{abacaba}) + \text{LCP}(\text{bacaba}, \text{bacaba}) = 7 + 0 + 0 + 6 = 13 $ .
2. In the second query $ s[1 \dots 7] = \text{abacaba} $ , $ s[2 \dots 7] = \text{bacaba} $ , $ s[3 \dots 7] = \text{acaba} $ and $ s[7 \dots 7] = \text{a} $ are considered. The answer for the query is $ \text{LCP}(\text{abacaba}, \text{a}) + \text{LCP}(\text{bacaba}, \text{a}) + \text{LCP}(\text{acaba}, \text{a}) = 1 + 0 + 1 = 2 $ .
3. In the third query $ s[1 \dots 7] = \text{abacaba} $ are compared with all suffixes. The answer is the sum of non-zero values: $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{acaba}) + \text{LCP}(\text{abacaba}, \text{aba}) + \text{LCP}(\text{abacaba}, \text{a}) = 7 + 1 + 3 + 1 = 12 $ .
4. In the fourth query $ s[1 \dots 7] = \text{abacaba} $ and $ s[5 \dots 7] = \text{aba} $ are considered. The answer for the query is $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{aba}) + \text{LCP}(\text{aba}, \text{abacaba}) + \text{LCP}(\text{aba}, \text{aba}) = 7 + 3 + 3 + 3 = 16 $ .

## 样例 #1

### 输入

```
7 4
abacaba
2 2
1 2
1 2
3 1
1 2 3
7
1 7
1
1 2 3 4 5 6 7
2 2
1 5
1 5

```

### 输出

```
13
2
12
16

```



---

---
title: "Crime Management"
layout: "post"
diff: 省选/NOI-
pid: CF107D
tag: ['字符串', '深度优先搜索 DFS', '概率论']
---

# Crime Management

## 题目描述

Zeyad 想要在埃及犯下 $n$ 起罪行，并且不受惩罚。罪行有几种类型。例如，贿赂是一种罪行，但如果重复两次，它就不被视为犯罪。因此，贿赂在重复偶数次时不被视为犯罪。超速也是一种罪行，但如果其重复的次数是 5 的倍数，它也不被视为犯罪。

更具体地说，已知有 $c$ 条关于罪行重复的条件。每个条件描述了罪行的类型 $t_{i}$ 及其重复的次数限制 $m_{i}$ 。如果 Zeyad 犯下的罪行 $t_{i}$ 的次数是 $m_{i}$ 的倍数，则 Zeyad 不会因为该罪行而受到惩罚。如果某种罪行出现多次，满足其中任意一个条件即可不受惩罚。当然，如果某罪行的次数为零，Zeyad 对该罪行无罪。

现在，Zeyad 想知道有多少种方式可以精确犯下 $n$ 起罪行且不受惩罚。

罪行的顺序是重要的。更正式地说，犯下 $n$ 起罪行的两种方式（序列 $w1$ 和 $w2$ ）如果对所有 $1 \leq i \leq n$ ，$w1_{i} = w2_{i}$ ，那么它们是相同的方式。

## 输入格式

第一行包含两个整数 $n$ 和 $c$ ($0 \leq n \leq 10^{18}, 0 \leq c \leq 1000$) —— Zeyad 想要犯下的罪行数量和他知道的条件数量。

接下来是 $c$ 条条件的定义。有 $26$ 种类型的罪行。每个罪行的定义由罪行类型（一个大写拉丁字母）和其重复次数的限制组成。

每个罪行的重复次数限制是一个正整数，并且所有限制的乘积不超过 $123$ 。输入中可能有重复的条件。

若某罪行的重复次数限制为 $1$ ，无论犯多少次都不会受到惩罚。法律的严格性由其非强制性来弥补。

显然，如果某罪行未在条件集中列出，那么 Zeyad 不会考虑它，因为犯下它不可避免地会受到惩罚。

请不要在 C++ 中使用 %lld 格式符来读写 64 位整数，建议使用 cin 流（你也可以使用 %I64d 格式符）。

## 输出格式

输出精确犯下 $n$ 起罪行且不受惩罚的不同方式数量，结果对 $12345$ 取模。

## 说明/提示

在第一个测试用例中，16 种方式是：AAAAA，AAABB，AABAB，AABBA，ABAAB，ABABA，ABBAA，BAAAB，BAABA，BABAA，BBAAA，ABBBB，BABBB，BBABB，BBBAB，BBBBA。

## 样例 #1

### 输入

```
5 2
A 1
B 2

```

### 输出

```
16

```

## 样例 #2

### 输入

```
6 3
A 1
B 2
C 3

```

### 输出

```
113

```

## 样例 #3

### 输入

```
8 3
A 2
A 3
B 2

```

### 输出

```
128

```



---

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
title: "Balance"
layout: "post"
diff: 省选/NOI-
pid: CF17C
tag: ['字符串', '枚举', '概率论']
---

# Balance

## 题目描述

1. 选择两个相邻字符，将第一个字符替换成第二个。 
2. 选择两个相邻字符，将第二个字符替换成第一个。 这样，通过任意多次的操作，可以得到许多不同的串，为了追求字符的平衡， 我们要求a,b,c三种字符在字符串中出现的次数两两之差都不能大于1。

你的任 务是，统计给定字符串通过任意多次的操作，能够得到的不同的平衡串的个数。

## 输入格式

输入文件包含2行。 第一行包含1个正整数n，表示字符串长度。 第二行包含1个长度为n的字符串。

## 输出格式

输出共1行，包含1个正整数，表示能够得到的平衡串的数量。由于答案可 能很大，因此输出时要对51123987取模。

## 样例 #1

### 输入

```
4
abca

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4
abbc

```

### 输出

```
3

```

## 样例 #3

### 输入

```
2
ab

```

### 输出

```
1

```



---

---
title: "Palisection"
layout: "post"
diff: 省选/NOI-
pid: CF17E
tag: ['字符串', '前缀和', '差分']
---

# Palisection

## 题目描述

给定一个长度为n的小写字母串。问你有多少对相交的回文子 串（包含也算相交） 。

## 输入格式

第一行是字符串长度n(1<=n<=2*10^6)，第二行字符串

## 输出格式

相交的回文子串个数%51123987

Translated by liyifeng

## 样例 #1

### 输入

```
4
babb

```

### 输出

```
6

```

## 样例 #2

### 输入

```
2
aa

```

### 输出

```
2

```



---

---
title: "Palindromic Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1913F
tag: ['字符串', '枚举']
---

# Palindromic Problem

## 题目描述

You are given a string $ s $ of length $ n $ , consisting of lowercase Latin letters.

You are allowed to replace at most one character in the string with an arbitrary lowercase Latin letter.

Print the lexicographically minimal string that can be obtained from the original string and contains the maximum number of palindromes as substrings. Note that if a palindrome appears more than once as a substring, it is counted the same number of times it appears.

The string $ a $ is lexicographically smaller than the string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ are different, the string $ a $ contains a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \leq n \leq 3 \cdot 10^5 $ ) — the number of characters in the string.

The second line contains the string $ s $ itself, consisting of exactly $ n $ lowercase Latin letters.

## 输出格式

In the first line, print one integer — the maximum number of palindromic substrings that can be obtained using the operation described in the statement at most once.

In the second line, print the string that can be obtained from $ s $ and has the maximum possible number of palindromic substrings. If there are multiple answers, print the lexicographically smallest one.

## 样例 #1

### 输入

```
5
aabaa
```

### 输出

```
15
aaaaa
```

## 样例 #2

### 输入

```
5
aaaaa
```

### 输出

```
15
aaaaa
```

## 样例 #3

### 输入

```
4
awoo
```

### 输出

```
7
aooo
```



---

---
title: "The Next Good String"
layout: "post"
diff: 省选/NOI-
pid: CF196D
tag: ['字符串', '枚举', '哈希 hashing']
---

# The Next Good String

## 题目描述

In problems on strings one often has to find a string with some particular properties. The problem authors were reluctant to waste time on thinking of a name for some string so they called it good. A string is good if it doesn't have palindrome substrings longer than or equal to $ d $ .

You are given string $ s $ , consisting only of lowercase English letters. Find a good string $ t $ with length $ |s| $ , consisting of lowercase English letters, which is lexicographically larger than $ s $ . Of all such strings string $ t $ must be lexicographically minimum.

We will call a non-empty string $ s[a ... b]=s_{a}s_{a+1}...\ s_{b} $ $ (1<=a<=b<=|s|) $ a substring of string $ s=s_{1}s_{2}...\ s_{|s|} $ .

A non-empty string $ s=s_{1}s_{2}...\ s_{n} $ is called a palindrome if for all $ i $ from $ 1 $ to $ n $ the following fulfills: $ s_{i}=s_{n-i+1} $ . In other words, palindrome read the same in both directions.

String $ x=x_{1}x_{2}...\ x_{|x|} $ is lexicographically larger than string $ y=y_{1}y_{2}...\ y_{|y|} $ , if either $ |x|&gt;|y| $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{|y|}=y_{|y|} $ , or there exists such number $ r $ $ (r&lt;|x|,r&lt;|y|) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&gt;y_{r+1} $ . Characters in such strings are compared like their ASCII codes.

## 输入格式

The first line contains integer $ d $ ( $ 1<=d<=|s| $ ).

The second line contains a non-empty string $ s $ , its length is no more than $ 4·10^{5} $ characters. The string consists of lowercase English letters.

## 输出格式

Print the good string that lexicographically follows $ s $ , has the same length and consists of only lowercase English letters. If such string does not exist, print "Impossible" (without the quotes).

## 样例 #1

### 输入

```
3
aaaaaaa

```

### 输出

```
aabbcaa

```

## 样例 #2

### 输入

```
3
zzyzzzz

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
4
abbabbbabbb

```

### 输出

```
abbbcaaabab

```



---

---
title: "Alien DNA"
layout: "post"
diff: 省选/NOI-
pid: CF217E
tag: ['字符串', '并查集', '递归']
---

# Alien DNA

## 题目描述

Professor Bajtocy is conducting experiments on alien DNA. He has discovered that it is subject to repetitive mutations — each mutation happens in the same way: some continuous subsequence of the alien DNA becomes active, copies itself, the copy gets mangled and inserts itself right after the original subsequence. The mangled copy of the activated continuous subsequence is formed by first joining all the elements at the even positions in that subsequence, and then joining all the elements at the odd ones at the end. That is, if the activated subsequence consists of 11 elements and represented as $ s_{1}s_{2}...\ s_{11} $ , its mangled copy is $ s_{2}s_{4}s_{6}s_{8}s_{10}s_{1}s_{3}s_{5}s_{7}s_{9}s_{11} $ .

For example, if the original sequence was "ACTGG" and the mutation happened on the segment $ [2,4] $ (that is the activated subsequence is "CTG"), the mutated DNA is: "ACTGTCGG". The mangled copy of the activated subsequence is marked with bold font.

Professor Bajtocy has written down the original DNA sequence and the mutations that sequentially happened to it, and he now asks you to recover the first $ k $ elements of the DNA sequence after all the mutations.

## 输入格式

The first line of input contains the original DNA sequence, consisting only of letters "A", "C", "T" and "G" and not exceeding $ 3·10^{6} $ in length.

The second line contains a single integer $ k $ ( $ 1<=k<=3·10^{6} $ ).

The third line contains a single integer $ n $ ( $ 0<=n<=5000 $ ) — the number of mutations. The next $ n $ lines describe the mutations in chronological order — each mutation is described by two numbers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=10^{9} $ ), meaning that the continuous subsequence $ [l_{i},r_{i}] $ has become active and cloned itself, joining itself with the mangled copy.

It is guaranteed that the input data is correct, that is, no mutation acts on non-existing elements of the DNA sequence, and the resulting DNA sequence has at least $ k $ elements.

Assume that the DNA elements are indexed starting from 1 and that the notation $ [l,r] $ meaning the continuous subsequence of DNA sequence that consists of $ r-l+1 $ elements starting at the $ l $ -th DNA sequence element and ending at the $ r $ -th DNA sequence element.

## 输出格式

Output a single line, containing the first $ k $ letters of the mutated DNA sequence.

## 说明/提示

In the second example, after the first mutation the sequence is "ACCAGTACGT". After the second mutation it's "ACCAGTACCGACATCGT".

## 样例 #1

### 输入

```
GAGA
4
0

```

### 输出

```
GAGA

```

## 样例 #2

### 输入

```
ACGTACGT
16
2
1 2
2 8

```

### 输出

```
ACCAGTACCGACATCG

```



---

---
title: "Colorful Stones"
layout: "post"
diff: 省选/NOI-
pid: CF264D
tag: ['字符串', '前缀和']
---

# Colorful Stones

## 题目描述

There are two sequences of colorful stones. The color of each stone is one of red, green, or blue. You are given two strings $ s $ and $ t $ . The $ i $ -th (1-based) character of $ s $ represents the color of the $ i $ -th stone of the first sequence. Similarly, the $ i $ -th (1-based) character of $ t $ represents the color of the $ i $ -th stone of the second sequence. If the character is "R", "G", or "B", the color of the corresponding stone is red, green, or blue, respectively.

Initially Squirrel Liss is standing on the first stone of the first sequence and Cat Vasya is standing on the first stone of the second sequence. You can perform the following instructions zero or more times.

Each instruction is one of the three types: "RED", "GREEN", or "BLUE". After an instruction $ c $ , the animals standing on stones whose colors are $ c $ will move one stone forward. For example, if you perform an instruction «RED», the animals standing on red stones will move one stone forward. You are not allowed to perform instructions that lead some animals out of the sequences. In other words, if some animals are standing on the last stones, you can't perform the instructions of the colors of those stones.

A pair of positions (position of Liss, position of Vasya) is called a state. A state is called reachable if the state is reachable by performing instructions zero or more times from the initial state (1, 1). Calculate the number of distinct reachable states.

## 输入格式

The input contains two lines. The first line contains the string $ s $ ( $ 1<=|s|<=10^{6} $ ). The second line contains the string $ t $ ( $ 1<=|t|<=10^{6} $ ). The characters of each string will be one of "R", "G", or "B".

## 输出格式

Print the number of distinct reachable states in a single line.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first example, there are five reachable states: (1, 1), (2, 2), (2, 3), (3, 2), and (3, 3). For example, the state (3, 3) is reachable because if you perform instructions "RED", "GREEN", and "BLUE" in this order from the initial state, the state will be (3, 3). The following picture shows how the instructions work in this case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF264D/ff8e8d184349ca742f85291d5c556a28aebdf7a7.png)

## 样例 #1

### 输入

```
RBR
RGG

```

### 输出

```
5

```

## 样例 #2

### 输入

```
RGBB
BRRBRR

```

### 输出

```
19

```

## 样例 #3

### 输入

```
RRRRRRRRRR
RRRRRRRR

```

### 输出

```
8

```



---

---
title: "Game with Strings"
layout: "post"
diff: 省选/NOI-
pid: CF482C
tag: ['字符串', '状态合并', '期望']
---

# Game with Strings

## 题目描述

你和你的朋友玩一个游戏，游戏规则如下。

你的朋友创造出了 $n$ 个长度均为 $m$ 的不相同的字符串，然后他随机地选择其中一个。他选择这些字符串的概率是相等的，也就是说，他选择 $n$ 个字符串中的每一个的概率是 $\frac{1}{n}$。你想猜猜你的朋友选择了哪个字符串。

为了猜到你的朋友选择了哪个字符串，你可以问他问题，形式如下：字符串中第 $pos$ 个字符是什么？当这些问题的答案能够唯一确定一个字符串时，我们认为这个字符串被猜到了。在字符串被猜到后，你将停止提问。

你没有特殊的策略，所以你每次可能会等概率的问任何一个你从没猜过的位置。求猜到你的朋友选的字符串所需次数的期望。

## 输入格式

第一行包括一个数字 $n$（$1 \le n \le 50$）。接下来 $n$ 行，每行一个字符串，表示你朋友创造出的字符串。除此之外，所有字符的长度是相同的，在 $1\sim 20$ 之间。

## 输出格式

输出期望值，要求误差在 $10^{-9}$ 以内。

## 样例 #1

### 输入

```
2
aab
aac

```

### 输出

```
2.000000000000000

```

## 样例 #2

### 输入

```
3
aaA
aBa
Caa

```

### 输出

```
1.666666666666667

```

## 样例 #3

### 输入

```
3
aca
vac
wqq

```

### 输出

```
1.000000000000000

```



---

---
title: "Strange Sorting"
layout: "post"
diff: 省选/NOI-
pid: CF484C
tag: ['字符串', '递推', '排序']
---

# Strange Sorting

## 题目描述

How many specific orders do you know? Ascending order, descending order, order of ascending length, order of ascending polar angle... Let's have a look at another specific order:  $ d $ -sorting. This sorting is applied to the strings of length at least $ d $ , where $ d $ is some positive integer. The characters of the string are sorted in following manner: first come all the 0-th characters of the initial string, then the 1-st ones, then the 2-nd ones and so on, in the end go all the $ (d-1) $ -th characters of the initial string. By the $ i $ -th characters we mean all the character whose positions are exactly $ i $ modulo $ d $ . If two characters stand on the positions with the same remainder of integer division by $ d $ , their relative order after the sorting shouldn't be changed. The string is zero-indexed. For example, for string 'qwerty':

Its 1-sorting is the string 'qwerty' (all characters stand on 0 positions),

Its 2-sorting is the string 'qetwry' (characters 'q', 'e' and 't' stand on 0 positions and characters 'w', 'r' and 'y' are on 1 positions),

Its 3-sorting is the string 'qrwtey' (characters 'q' and 'r' stand on 0 positions, characters 'w' and 't' stand on 1 positions and characters 'e' and 'y' stand on 2 positions),

Its 4-sorting is the string 'qtwyer',

Its 5-sorting is the string 'qywert'.

You are given string $ S $ of length $ n $ and $ m $ shuffling operations of this string. Each shuffling operation accepts two integer arguments $ k $ and $ d $ and transforms string $ S $ as follows. For each $ i $ from $ 0 $ to $ n-k $ in the increasing order we apply the operation of $ d $ -sorting to the substring $ S\[i..i+k-1\] $ . Here $ S\[a..b\] $ represents a substring that consists of characters on positions from $ a $ to $ b $ inclusive.

After each shuffling operation you need to print string $ S $ .

## 输入格式

The first line of the input contains a non-empty string $ S $ of length $ n $ , consisting of lowercase and uppercase English letters and digits from 0 to 9.

The second line of the input contains integer $ m $ – the number of shuffling operations ( $ 1<=m·n<=10^{6} $ ).

Following $ m $ lines contain the descriptions of the operations consisting of two integers $ k $ and $ d $ ( $ 1<=d<=k<=n $ ).

## 输出格式

After each operation print the current state of string $ S $ .

## 说明/提示

Here is detailed explanation of the sample. The first modification is executed with arguments $ k=4 $ , $ d=2 $ . That means that you need to apply 2-sorting for each substring of length 4 one by one moving from the left to the right. The string will transform in the following manner:

qwerty $ → $ qewrty $ → $ qerwty $ → $ qertwy

Thus, string $ S $ equals 'qertwy' at the end of first query.

The second modification is executed with arguments $ k=6 $ , $ d=3 $ . As a result of this operation the whole string $ S $ is replaced by its 3-sorting:

qertwy $ → $ qtewry

The third modification is executed with arguments $ k=5 $ , $ d=2 $ .

qtewry $ → $ qertwy $ → $ qetyrw

## 样例 #1

### 输入

```
qwerty
3
4 2
6 3
5 2

```

### 输出

```
qertwy
qtewry
qetyrw

```



---

---
title: "Kefa and Watch"
layout: "post"
diff: 省选/NOI-
pid: CF580E
tag: ['字符串', '线段树', '哈希 hashing']
---

# Kefa and Watch

## 题目描述

One day Kefa the parrot was walking down the street as he was on the way home from the restaurant when he saw something glittering by the road. As he came nearer he understood that it was a watch. He decided to take it to the pawnbroker to earn some money.

The pawnbroker said that each watch contains a serial number represented by a string of digits from $ 0 $ to $ 9 $ , and the more quality checks this number passes, the higher is the value of the watch. The check is defined by three positive integers $ l $ , $ r $ and $ d $ . The watches pass a check if a substring of the serial number from $ l $ to $ r $ has period $ d $ . Sometimes the pawnbroker gets distracted and Kefa changes in some substring of the serial number all digits to $ c $ in order to increase profit from the watch.

The seller has a lot of things to do to begin with and with Kefa messing about, he gave you a task: to write a program that determines the value of the watch.

Let us remind you that number $ x $ is called a period of string $ s $ ( $ 1<=x<=|s| $ ), if $ s_{i}=s_{i+x} $ for all $ i $ from 1 to $ |s|-x $ .

## 输入格式

The first line of the input contains three positive integers $ n $ , $ m $ and $ k $ ( $ 1<=n<=10^{5} $ , $ 1<=m+k<=10^{5} $ ) — the length of the serial number, the number of change made by Kefa and the number of quality checks.

The second line contains a serial number consisting of $ n $ digits.

Then $ m+k $ lines follow, containing either checks or changes.

The changes are given as 1 $ l $ $ r $ $ c $ ( $ 1<=l<=r<=n $ , $ 0<=c<=9 $ ). That means that Kefa changed all the digits from the $ l $ -th to the $ r $ -th to be $ c $ .

The checks are given as 2 $ l $ $ r $ $ d $ ( $ 1<=l<=r<=n $ , $ 1<=d<=r-l+1 $ ).

## 输出格式

For each check on a single line print "YES" if the watch passed it, otherwise print "NO".

## 说明/提示

In the first sample test two checks will be made. In the first one substring "12" is checked on whether or not it has period 1, so the answer is "NO". In the second one substring "88", is checked on whether or not it has period 1, and it has this period, so the answer is "YES".

In the second statement test three checks will be made. The first check processes substring "3493", which doesn't have period 2. Before the second check the string looks as "334334", so the answer to it is "YES". And finally, the third check processes substring "8334", which does not have period 1.

## 样例 #1

### 输入

```
3 1 2
112
2 2 3 1
1 1 3 8
2 1 2 1

```

### 输出

```
NO
YES

```

## 样例 #2

### 输入

```
6 2 3
334934
2 2 5 2
1 4 4 3
2 1 6 3
1 2 3 8
2 3 6 1

```

### 输出

```
NO
YES
NO

```



---

---
title: "Polycarp's Masterpiece"
layout: "post"
diff: 省选/NOI-
pid: CF589C
tag: ['字符串', '平衡树', '可持久化']
---

# Polycarp's Masterpiece

## 题目描述

Inspired by success of Joanne Rowling and her fantasy series of Harry Potter, Polycarp decided to create his own masterpiece. He has already picked a name for his future bestseller — string $ s $ .

Polycarp faced a number of difficulties while he was working on the main story of his book so he decided to become Malevich in a literature and create his own "Black Square".

Chapters of his masterpiece were written by Polycarp in $ n $ days. He started from writing down the string $ s $ . Every day (during the following $ n $ days) he did the following procedure: on the $ i $ -th day he added to the right of current text $ t $ its $ k_{i} $ -th circular shift. It means that every day content of his masterpiece doubled in size.

Circular shift of a string $ r $ is defined as a string resulted after movement of the last character of $ r $ to the first position in the string. As an example: circular shift of «masterpiece» is «emasterpiec». The $ i $ -th circular shift of a string $ r $ is defined as a string resulted after applying $ i $ subsequent circular shifts of the string $ r $ (e.g., the third circular shift of «masterpiece» is «ecemasterpi»).

After $ n $ days of tedious work Polycarp managed to write a very long text deserving the efforts made. However, text of his masterpiece was so long that it was nearly impossible to do any analysis of its content.

Help Polycarp to answer $ m $ requests about his masterpiece: for the $ j $ -th request you will need to find how many times a letter $ c_{j} $ is contained in a substring of his masterpiece starting from position $ l_{j} $ and ending at $ r_{j} $ inclusively.

## 输入格式

The first line contains a name of the masterpiece — string $ s $ . The string $ s $ contains only lowercase latin letters and its length is between 1 and 100 inclusively.

The second line contains a pair of integer numbers $ n $ and $ m $ $ (1<=n<=10^{5},1<=m<=10^{5}) $ — a number of days Polycarp worked on his masterpiece and a number of requests you need to answer for the text respectively.

The next line consists of $ n $ integer numbers $ k_{i} $ $ (0<=k_{i}<=100) $ — circular shifts used during $ n $ days of work.

Following $ m $ lines contains two integer numbers $ l_{j},r_{j} $ and a lowercase latin letter $ c_{j} $ each — requests description. For each request you need to count number of times letter $ c_{j} $ is contained in a substring of the masterpiece from position $ l_{j} $ to $ r_{j} $ inclusively. Positions are numerated starting from $ 1 $ . It is guaranteed that $ 1<=l_{j}<=r_{j}<=10^{18} $ and both $ l_{j} $ and $ r_{j} $ do not exceed length of the masterpiece.

## 输出格式

Output should contain $ m $ lines, where the $ j $ -th line contains the answer on the $ j $ -th request.

## 样例 #1

### 输入

```
masterpiece
1 3
3
1 22 m
9 14 e
8 15 p

```

### 输出

```
2
4
0

```

## 样例 #2

### 输入

```
polycarp
1 2
0
2 15 p
1 16 p

```

### 输出

```
2
4

```



---

---
title: "Bear and Square Grid"
layout: "post"
diff: 省选/NOI-
pid: CF679C
tag: ['字符串', '搜索', '连通块']
---

# Bear and Square Grid

## 题目描述

You have a grid with $ n $ rows and $ n $ columns. Each cell is either empty (denoted by '.') or blocked (denoted by 'X').

Two empty cells are directly connected if they share a side. Two cells $ (r_{1},c_{1}) $ (located in the row $ r_{1} $ and column $ c_{1} $ ) and $ (r_{2},c_{2}) $ are connected if there exists a sequence of empty cells that starts with $ (r_{1},c_{1}) $ , finishes with $ (r_{2},c_{2}) $ , and any two consecutive cells in this sequence are directly connected. A connected component is a set of empty cells such that any two cells in the component are connected, and there is no cell in this set that is connected to some cell not in this set.

Your friend Limak is a big grizzly bear. He is able to destroy any obstacles in some range. More precisely, you can choose a square of size $ k×k $ in the grid and Limak will transform all blocked cells there to empty ones. However, you can ask Limak to help only once.

The chosen square must be completely inside the grid. It's possible that Limak won't change anything because all cells are empty anyway.

You like big connected components. After Limak helps you, what is the maximum possible size of the biggest connected component in the grid?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=500 $ ) — the size of the grid and Limak's range, respectively.

Each of the next $ n $ lines contains a string with $ n $ characters, denoting the $ i $ -th row of the grid. Each character is '.' or 'X', denoting an empty cell or a blocked one, respectively.

## 输出格式

Print the maximum possible size (the number of cells) of the biggest connected component, after using Limak's help.

## 说明/提示

In the first sample, you can choose a square of size $ 2×2 $ . It's optimal to choose a square in the red frame on the left drawing below. Then, you will get a connected component with $ 10 $ cells, marked blue in the right drawing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679C/73f9f2e0fd56d2fb7f7f3062a32953f02d9af103.png)

## 样例 #1

### 输入

```
5 2
..XXX
XX.XX
X.XXX
X...X
XXXX.

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 3
.....
.XXX.
.XXX.
.XXX.
.....

```

### 输出

```
25

```



---

---
title: "Dasha and cyclic table"
layout: "post"
diff: 省选/NOI-
pid: CF754E
tag: ['字符串']
---

# Dasha and cyclic table

## 题目描述

Dasha is fond of challenging puzzles: Rubik's Cube $ 3×3×3 $ , $ 4×4×4 $ , $ 5×5×5 $ and so on. This time she has a cyclic table of size $ n×m $ , and each cell of the table contains a lowercase English letter. Each cell has coordinates $ (i,j) $ ( $ 0<=i&lt;n $ , $ 0<=j&lt;m $ ). The table is cyclic means that to the right of cell $ (i,j) $ there is the cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF754E/a5d005af310d530b73654f2e5c374c68f16d2ee4.png), and to the down there is the cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF754E/1a381522c9ac4a424562398196989e9e4585022e.png).

Dasha has a pattern as well. A pattern is a non-cyclic table of size $ r×c $ . Each cell is either a lowercase English letter or a question mark. Each cell has coordinates $ (i,j) $ ( $ 0<=i&lt;r $ , $ 0<=j&lt;c $ ).

The goal of the puzzle is to find all the appearance positions of the pattern in the cyclic table.

We say that the cell $ (i,j) $ of cyclic table is an appearance position, if for every pair $ (x,y) $ such that $ 0<=x&lt;r $ and $ 0<=y&lt;c $ one of the following conditions holds:

- There is a question mark in the cell $ (x,y) $ of the pattern, or
- The cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF754E/54ce001d702da711f4c8fe98e24e25993cb660d2.png) of the cyclic table equals to the cell $ (x,y) $ of the pattern.

Dasha solved this puzzle in no time, as well as all the others she ever tried. Can you solve it?.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=400 $ ) — the cyclic table sizes.

Each of the next $ n $ lines contains a string of $ m $ lowercase English characters — the description of the cyclic table.

The next line contains two integers $ r $ and $ c $ ( $ 1<=r,c<=400 $ ) — the sizes of the pattern.

Each of the next $ r $ lines contains a string of $ c $ lowercase English letter and/or characters '?' — the description of the pattern.

## 输出格式

Print $ n $ lines. Each of the $ n $ lines should contain $ m $ characters. Each of the characters should equal '0' or '1'.

The $ j $ -th character of the $ i $ -th ( $ 0 $ -indexed) line should be equal to '1', in case the cell $ (i,j) $ is an appearance position, otherwise it should be equal to '0'.

## 样例 #1

### 输入

```
5 7
qcezchs
hhedywq
wikywqy
qckrqzt
bqexcxz
3 2
??
yw
?q

```

### 输出

```
0000100
0001001
0000000
0000000
0000000

```

## 样例 #2

### 输入

```
10 10
fwtoayylhw
yyaryyjawr
ywrdzwhscy
hnsyyxiphn
bnjwzyyjvo
kkjgseenwn
gvmiflpcsy
lxvkwrobwu
wyybbcocyy
yysijsvqry
2 2
??
yy

```

### 输出

```
1000100000
0000000001
0001000000
0000010000
0000000000
0000000000
0000000000
0100000010
1000000001
0000010000

```

## 样例 #3

### 输入

```
8 6
ibrgxl
xqdcsg
okbcgi
tvpetc
xgxxig
igghzo
lmlaza
gpswzv
1 4
gx??

```

### 输出

```
000100
000001
000000
000000
010001
000000
000000
000000

```



---

---
title: "Rusty String"
layout: "post"
diff: 省选/NOI-
pid: CF827E
tag: ['字符串', '枚举', '构造']
---

# Rusty String

## 题目描述

Grigory loves strings. Recently he found a metal strip on a loft. The strip had length $ n $ and consisted of letters "V" and "K". Unfortunately, rust has eaten some of the letters so that it's now impossible to understand which letter was written.

Grigory couldn't understand for a long time what these letters remind him of, so he became interested in the following question: if we put a letter "V" or "K" on each unreadable position, which values can the period of the resulting string be equal to?

A period of a string is such an integer $ d $ from $ 1 $ to the length of the string that if we put the string shifted by $ d $ positions to the right on itself, then all overlapping letters coincide. For example, $ 3 $ and $ 5 $ are periods of "VKKVK".

## 输入格式

There are several (at least one) test cases in the input. The first line contains single integer — the number of test cases.

There is an empty line before each test case. Each test case is described in two lines: the first line contains single integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the length of the string, the second line contains the string of length $ n $ , consisting of letters "V", "K" and characters "?". The latter means the letter on its position is unreadable.

It is guaranteed that the sum of lengths among all test cases doesn't exceed $ 5·10^{5} $ .

For hacks you can only use tests with one test case.

## 输出格式

For each test case print two lines. In the first line print the number of possible periods after we replace each unreadable letter with "V" or "K". In the next line print all these values in increasing order.

## 说明/提示

In the first test case from example we can obtain, for example, "VKKVK", which has periods $ 3 $ and $ 5 $ .

In the second test case we can obtain "VVVVVV" which has all periods from $ 1 $ to $ 6 $ .

In the third test case string "KVKV" has periods $ 2 $ and $ 4 $ , and string "KVKK" has periods $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
3
 
5
V??VK
 
6
??????
 
4
?VK?

```

### 输出

```
2
3 5
6
1 2 3 4 5 6
3
2 3 4

```



---

---
title: "Anti-Palindromize"
layout: "post"
diff: 省选/NOI-
pid: CF884F
tag: ['字符串', '网络流']
---

# Anti-Palindromize

## 题目描述

对于一个字串 $a$，若其长度 $m$ 为偶数，且对于 $\forall i \in[1,m]$，有 $a_i \neq a_{m-i+1}$，则将其称为反回文串。

Ivan 有一个由 $n$ 个小写拉丁字母构成的字串 $s$，且 $n$ 为偶数。他想用 $s$ 的一些排列构成一些反回文串 $t$。同时他称 $i$ 的美丽值为 $b_i$，且字串 $t$ 的美丽值 $Ans=\sum_{i=1}^{len(s)} b_i[s_i=t_i]$。

请帮 Ivan 确定 $Ans$ 的最大值。

## 输入格式

第一行一个偶数 $n\ (2 \leq n \leq 100)$，表示字串 $s$ 中的字符数量。

第二行一个只含小写字母的字串 $s$，题目保证存在 $s$ 的一个排列 $t$，使得 $\forall i \in [1,n],t_i \neq t_{n-i+1}$。

第三行为数组 $b\ (1\leq b_i \leq 100)$。

## 输出格式

一个整数，$Ans$ 的最大值。

## 样例 #1

### 输入

```
8
abacabac
1 1 1 1 1 1 1 1

```

### 输出

```
8

```

## 样例 #2

### 输入

```
8
abaccaba
1 2 3 4 5 6 7 8

```

### 输出

```
26

```

## 样例 #3

### 输入

```
8
abacabca
1 2 3 4 4 3 2 1

```

### 输出

```
17

```



---

---
title: "Short Code"
layout: "post"
diff: 省选/NOI-
pid: CF965E
tag: ['字符串', '贪心', '递归']
---

# Short Code

## 题目描述

Arkady's code contains $ n $ variables. Each variable has a unique name consisting of lowercase English letters only. One day Arkady decided to shorten his code.

He wants to replace each variable name with its non-empty prefix so that these new names are still unique (however, a new name of some variable can coincide with some old name of another or same variable). Among such possibilities he wants to find the way with the smallest possible total length of the new names.

A string $ a $ is a prefix of a string $ b $ if you can delete some (possibly none) characters from the end of $ b $ and obtain $ a $ .

Please find this minimum possible total length of new names.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of variables.

The next $ n $ lines contain variable names, one per line. Each name is non-empty and contains only lowercase English letters. The total length of these strings is not greater than $ 10^5 $ . The variable names are distinct.

## 输出格式

Print a single integer — the minimum possible total length of new variable names.

## 说明/提示

In the first example one of the best options is to shorten the names in the given order as "cod", "co", "c".

In the second example we can shorten the last name to "aac" and the first name to "a" without changing the other names.

## 样例 #1

### 输入

```
3
codeforces
codehorses
code

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
abba
abb
ab
aa
aacada

```

### 输出

```
11

```

## 样例 #3

### 输入

```
3
telegram
digital
resistance

```

### 输出

```
3

```



---

