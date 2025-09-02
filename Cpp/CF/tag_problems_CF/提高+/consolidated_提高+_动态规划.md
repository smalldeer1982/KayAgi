---
title: "Magic Gems"
layout: "post"
diff: 提高+/省选-
pid: CF1117D
tag: ['动态规划 DP', '矩阵加速']
---

# Magic Gems

## 题目描述

xht37 有很多魔法宝石。每颗魔法宝石可以分解成 $ m $ 颗普通宝石，魔法宝石和普通宝石都占据 $ 1 $ 体积的空间，但普通宝石不能再被分解。

xht37 想要使一些魔法宝石分解，使得所有宝石占据的空间**恰好**为 $ n $ 单位体积。显然，一个魔法宝石分解后会占据 $ m $ 体积空间，不分解的魔法宝石仍占据 $ 1 $ 体积空间。

现在 xht37 想要求出有多少种分解方案，可以让最后得到的宝石**恰好**占据 $ n $ 单位体积。两种分解方案不同当且仅当分解的魔法宝石数量不同，或者是所用的宝石的编号不同。

xht37 当然知道怎么做，但是他想考考你。

## 输入格式

输入包含两个数字 $ n,m (1 \le N \le 10^{18},2 \le M \le 100)$ 。

## 输出格式

输出能使宝石占据恰好 $ n $ 体积的方案数。因为方案数实在太大了，请输出方案数 $ \mod 10^9+7 $ 后的结果。

### 样例解释

该样例中一颗魔法宝石可以分解得到两颗普通宝石，我们的目标是拿到 $ 4 $ 颗宝石。

让我们用 $ 1 $ 代表魔法宝石，$ 0 $ 代表普通宝石。

则存在如下几种方案：

* $ 1111 $ ：没有宝石被分解。
* $ 0011 $ ：第一颗宝石分解。
* $ 1001 $ ：第二颗宝石分解。
* $ 1100 $ ：第三颗宝石分解。
* $ 0000 $ ：第一颗和第二颗宝石分解。

因此答案为 $ 5 $ 。

## 样例 #1

### 输入

```
4 2

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
3

```



---

---
title: "Clear the String"
layout: "post"
diff: 提高+/省选-
pid: CF1132F
tag: ['动态规划 DP', '区间 DP']
---

# Clear the String

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase Latin letters. You may apply some operations to this string: in one operation you can delete some contiguous substring of this string, if all letters in the substring you delete are equal. For example, after deleting substring bbbb from string abbbbaccdd we get the string aaccdd.

Calculate the minimum number of operations to delete the whole string $ s $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 500 $ ) — the length of string $ s $ .

The second line contains the string $ s $ ( $ |s| = n $ ) consisting of lowercase Latin letters.

## 输出格式

Output a single integer — the minimal number of operation to delete string $ s $ .

## 样例 #1

### 输入

```
5
abaca

```

### 输出

```
3

```

## 样例 #2

### 输入

```
8
abcddcba

```

### 输出

```
4

```



---

---
title: "Three Religions"
layout: "post"
diff: 提高+/省选-
pid: CF1149B
tag: ['动态规划 DP', '有限状态自动机']
---

# Three Religions

## 题目描述

During the archaeological research in the Middle East you found the traces of three ancient religions: First religion, Second religion and Third religion. You compiled the information on the evolution of each of these beliefs, and you now wonder if the followers of each religion could coexist in peace.

The Word of Universe is a long word containing the lowercase English characters only. At each moment of time, each of the religion beliefs could be described by a word consisting of lowercase English characters.

The three religions can coexist in peace if their descriptions form disjoint subsequences of the Word of Universe. More formally, one can paint some of the characters of the Word of Universe in three colors: $ 1 $ , $ 2 $ , $ 3 $ , so that each character is painted in at most one color, and the description of the $ i $ -th religion can be constructed from the Word of Universe by removing all characters that aren't painted in color $ i $ .

The religions however evolve. In the beginning, each religion description is empty. Every once in a while, either a character is appended to the end of the description of a single religion, or the last character is dropped from the description. After each change, determine if the religions could coexist in peace.

## 输入格式

The first line of the input contains two integers $ n, q $ ( $ 1 \leq n \leq 100\,000 $ , $ 1 \leq q \leq 1000 $ ) — the length of the Word of Universe and the number of religion evolutions, respectively. The following line contains the Word of Universe — a string of length $ n $ consisting of lowercase English characters.

Each of the following line describes a single evolution and is in one of the following formats:

- + $ i $ $ c $ ( $ i \in \{1, 2, 3\} $ , $ c \in \{\mathtt{a}, \mathtt{b}, \dots, \mathtt{z}\} $ : append the character $ c $ to the end of $ i $ -th religion description.
- - $ i $ ( $ i \in \{1, 2, 3\} $ ) – remove the last character from the $ i $ -th religion description. You can assume that the pattern is non-empty.

You can assume that no religion will have description longer than $ 250 $ characters.

## 输出格式

Write $ q $ lines. The $ i $ -th of them should be YES if the religions could coexist in peace after the $ i $ -th evolution, or NO otherwise.

You can print each character in any case (either upper or lower).

## 说明/提示

In the first example, after the 6th evolution the religion descriptions are: ad, bc, and ab. The following figure shows how these descriptions form three disjoint subsequences of the Word of Universe:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1149B/d2161037f06cd41962d7459e510bbcc1eef61be4.png)

## 样例 #1

### 输入

```
6 8
abdabc
+ 1 a
+ 1 d
+ 2 b
+ 2 c
+ 3 a
+ 3 b
+ 1 c
- 2

```

### 输出

```
YES
YES
YES
YES
YES
YES
NO
YES

```

## 样例 #2

### 输入

```
6 8
abbaab
+ 1 a
+ 2 a
+ 3 a
+ 1 b
+ 2 b
+ 3 b
- 1
+ 2 z

```

### 输出

```
YES
YES
YES
YES
YES
NO
YES
NO

```



---

---
title: "Linear Kingdom Races"
layout: "post"
diff: 提高+/省选-
pid: CF115E
tag: ['动态规划 DP', '线段树', '枚举']
---

# Linear Kingdom Races

## 题目描述

你是一个赛车比赛的组织者，想在线性王国中安排一些比赛。

线性王国有 $n$ 条连续的从左到右的道路。道路从左到右依次编号为从 $1$ 到 $n$，因此道路按照升序排列。在这些道路上可能会有几场比赛，每一场比赛都将使用这些道路的某个连续的子序列。而且，如果某场比赛举行了，你将获得一定数额的金钱。没有比赛在时间上重叠，所以每一段道路可以在多个比赛中使用。

不幸的是，**所有道路**的状况都不佳，需要修理。每条路都有与之相关的维修费用，你需要支付这笔费用来修理道路。只有在某场比赛中需要使用的所有道路**都进行了修复**，才能进行比赛。你的任务是修复道路并使你的利润最大化。你的利润被定义为你从比赛中获得的总金额减去你花在修理道路上的钱。**请注意，您可以决定不修任何道路，并获得利润 $0$。**

输出你能获得的最大利润。

## 输入格式

第一行包括两个整数 $n,m$（$1 \leq n,m \leq 2\cdot 10^5$），分别表示道路的数量和比赛的数量。

接下来 $n$ 行，每行一个整数，表示这条道路修复需要的代价。

再接下来 $m$ 行，每行包括三个整数 $l_b,u_b,p$（$1 \leq l_b,u_b \leq n,1 \leq p \leq 10^9$），表示第 $b$ 场比赛需要使用道路 $[l_b,u_b]$，你会获得收益 $p$。

## 输出格式

输出一个整数，表示你能获得的最大利润。

## 说明/提示

在第一个样例中，最优解是修复 $1, 2, 3, 7$。你将会在第 $1, 2, 4$ 三场比赛中获得 $15$ 的收益。道路修理费用是 $11$，因此你的利润是 $4$。

## 样例 #1

### 输入

```
7 4
3
2
3
2
1
2
3
1 2 5
2 3 5
3 5 3
7 7 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2 1
0
3
1 2 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 1
10
10
10
1 3 10

```

### 输出

```
0

```



---

---
title: "A Simple Task"
layout: "post"
diff: 提高+/省选-
pid: CF11D
tag: ['动态规划 DP', '枚举', '状态合并']
---

# A Simple Task

## 题目描述

Given a simple graph, output the number of simple cycles in it. A simple cycle is a cycle with no repeated vertices or edges.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1<=n<=19 $ , $ 0<=m $ ) – respectively the number of vertices and edges of the graph. Each of the subsequent $ m $ lines contains two integers $ a $ and $ b $ , ( $ 1<=a,b<=n $ , $ a≠b $ ) indicating that vertices $ a $ and $ b $ are connected by an undirected edge. There is no more than one edge connecting any pair of vertices.

## 输出格式

Output the number of cycles in the given graph.

## 说明/提示

The example graph is a clique and contains four cycles of length 3 and three cycles of length 4.

## 样例 #1

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4

```

### 输出

```
7

```



---

---
title: "Yet Another Substring Reverse"
layout: "post"
diff: 提高+/省选-
pid: CF1234F
tag: ['动态规划 DP', '状态合并']
---

# Yet Another Substring Reverse

## 题目描述

You are given a string $ s $ consisting only of first $ 20 $ lowercase Latin letters ('a', 'b', ..., 't').

Recall that the substring $ s[l; r] $ of the string $ s $ is the string $ s_l s_{l + 1} \dots s_r $ . For example, the substrings of "codeforces" are "code", "force", "f", "for", but not "coder" and "top".

You can perform the following operation no more than once: choose some substring $ s[l; r] $ and reverse it (i.e. the string $ s_l s_{l + 1} \dots s_r $ becomes $ s_r s_{r - 1} \dots s_l $ ).

Your goal is to maximize the length of the maximum substring of $ s $ consisting of distinct (i.e. unique) characters.

The string consists of distinct characters if no character in this string appears more than once. For example, strings "abcde", "arctg" and "minecraft" consist of distinct characters but strings "codeforces", "abacaba" do not consist of distinct characters.

## 输入格式

The only line of the input contains one string $ s $ consisting of no more than $ 10^6 $ characters 'a', 'b', ..., 't' (first $ 20 $ lowercase Latin letters).

## 输出格式

Print one integer — the maximum possible length of the maximum substring of $ s $ consisting of distinct characters after reversing no more than one its substring.

## 样例 #1

### 输入

```
abacaba

```

### 输出

```
3

```

## 样例 #2

### 输入

```
abcdecdf

```

### 输出

```
6

```

## 样例 #3

### 输入

```
aabbcc

```

### 输出

```
3

```

## 样例 #4

### 输入

```
abcdeefc

```

### 输出

```
6

```



---

---
title: "Beautiful Mirrors"
layout: "post"
diff: 提高+/省选-
pid: CF1265E
tag: ['动态规划 DP', '期望']
---

# Beautiful Mirrors

## 题目描述

Creatnx has $ n $ mirrors, numbered from $ 1 $ to $ n $ . Every day, Creatnx asks exactly one mirror "Am I beautiful?". The $ i $ -th mirror will tell Creatnx that he is beautiful with probability $ \frac{p_i}{100} $ for all $ 1 \le i \le n $ .

Creatnx asks the mirrors one by one, starting from the $ 1 $ -st mirror. Every day, if he asks $ i $ -th mirror, there are two possibilities:

- The $ i $ -th mirror tells Creatnx that he is beautiful. In this case, if $ i = n $ Creatnx will stop and become happy, otherwise he will continue asking the $ i+1 $ -th mirror next day;
- In the other case, Creatnx will feel upset. The next day, Creatnx will start asking from the $ 1 $ -st mirror again.

You need to calculate [the expected number](https://en.wikipedia.org/wiki/Expected_value) of days until Creatnx becomes happy.

This number should be found by modulo $ 998244353 $ . Formally, let $ M = 998244353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1\le n\le 2\cdot 10^5 $ ) — the number of mirrors.

The second line contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \leq p_i \leq 100 $ ).

## 输出格式

Print the answer modulo $ 998244353 $ in a single line.

## 说明/提示

In the first test, there is only one mirror and it tells, that Creatnx is beautiful with probability $ \frac{1}{2} $ . So, the expected number of days until Creatnx becomes happy is $ 2 $ .

## 样例 #1

### 输入

```
1
50

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
10 20 50

```

### 输出

```
112

```



---

---
title: "AND Segments"
layout: "post"
diff: 提高+/省选-
pid: CF1327F
tag: ['动态规划 DP', '差分']
---

# AND Segments

## 题目描述

你有三个整数 $n, k, m$ 以及 $m$ 个限制 $(l_1, r_1, x_1), (l_2, r_2, x_2), \ldots, (l_m, r_m, x_m)$。

计算满足下列条件的，长度为 $n$ 的序列 $a$ 的个数：

- 对于每个 $1 \le i \le n$，$0 \le a_i \lt 2 ^ k$。
- 对于每个 $1 \le i \le m$，数字的按位与 $a[l_i] \text{ and } a_[l_i + 1] \text{ and } \ldots \text{ and } a[r_i] = x_i$。

两个序列 $a, b$ 被认为是不同的，当且仅当存在一个位置 $i$ 满足 $a_i \neq b_i$。

由于答案可能过大，请输出其对 $998\ 244\ 353$ 取模的结果。

## 输入格式

第一行输入三个整数 $n, k, m ~(1 \le n \le 5 \cdot 10 ^ 5; 1 \le k \le 30; 0 \le m \le 5 \cdot 10 ^ 5)~$，分别表示数组 $a$ 的长度，$a$ 中元素的值域，以及限制的个数。

接下来 $m$ 行，每行描述一个限制 $l_i, r_i, x_i ~ (1 \le l_i \le r_i \le n; 0 \le x_i \lt 2 ^ k)$，分别表示限制的线段区间以及按位与值。

## 输出格式

输出一行一个整数，表示满足条件的序列 $a$ 的个数，对 $998\ 244\ 353$ 取模的结果。

## 说明/提示

你可以在 [这里](https://en.wikipedia.org/wiki/Bitwise_operation#AND) 获得有关按位与的信息。

在一个样例中，合法的序列 $a$ 有：$[3, 3, 7, 6]$，$[3, 7, 7, 6]$ 以及 $[7, 3, 7, 6]$。

## 样例 #1

### 输入

```
4 3 2
1 3 3
3 4 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 2 3
1 3 2
2 5 0
3 3 3
```

### 输出

```
33
```



---

---
title: "String and Operations"
layout: "post"
diff: 提高+/省选-
pid: CF1455F
tag: ['动态规划 DP']
---

# String and Operations

## 题目描述

You are given a string $ s $ consisting of $ n $ characters. These characters are among the first $ k $ lowercase letters of the Latin alphabet. You have to perform $ n $ operations with the string.

During the $ i $ -th operation, you take the character that initially occupied the $ i $ -th position, and perform one of the following actions with it:

- swap it with the previous character in the string (if it exists). This operation is represented as L;
- swap it with the next character in the string (if it exists). This operation is represented as R;
- cyclically change it to the previous character in the alphabet (b becomes a, c becomes b, and so on; a becomes the $ k $ -th letter of the Latin alphabet). This operation is represented as D;
- cyclically change it to the next character in the alphabet (a becomes b, b becomes c, and so on; the $ k $ -th letter of the Latin alphabet becomes a). This operation is represented as U;
- do nothing. This operation is represented as 0.

For example, suppose the initial string is test, $ k = 20 $ , and the sequence of operations is URLD. Then the string is transformed as follows:

1. the first operation is U, so we change the underlined letter in test to the next one in the first $ 20 $ Latin letters, which is a. The string is now aest;
2. the second operation is R, so we swap the underlined letter with the next one in the string aest. The string is now aset;
3. the third operation is L, so we swap the underlined letter with the previous one in the string aset (note that this is now the $ 2 $ -nd character of the string, but it was initially the $ 3 $ -rd one, so the $ 3 $ -rd operation is performed to it). The resulting string is saet;
4. the fourth operation is D, so we change the underlined letter in saet to the previous one in the first $ 20 $ Latin letters, which is s. The string is now saes.

The result of performing the sequence of operations is saes.

Given the string $ s $ and the value of $ k $ , find the lexicographically smallest string that can be obtained after applying a sequence of operations to $ s $ .

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of two lines. The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 500 $ ; $ 2 \le k \le 26 $ ).

The second line contains a string $ s $ consisting of $ n $ characters. Each character is one of the $ k $ first letters of the Latin alphabet (in lower case).

## 输出格式

For each test case, print one line containing the lexicographically smallest string that can be obtained from $ s $ using one sequence of operations.

## 样例 #1

### 输入

```
6
4 2
bbab
7 5
cceddda
6 5
ecdaed
7 4
dcdbdaa
8 3
ccabbaca
5 7
eabba
```

### 输出

```
aaaa
baccacd
aabdac
aabacad
aaaaaaaa
abadb
```



---

---
title: "Phoenix and Computers"
layout: "post"
diff: 提高+/省选-
pid: CF1515E
tag: ['动态规划 DP', '区间 DP', '生成函数']
---

# Phoenix and Computers

## 题目描述

There are $ n $ computers in a row, all originally off, and Phoenix wants to turn all of them on. He will manually turn on computers one at a time. At any point, if computer $ i-1 $ and computer $ i+1 $ are both on, computer $ i $ $ (2 \le i \le n-1) $ will turn on automatically if it is not already on. Note that Phoenix cannot manually turn on a computer that already turned on automatically.

If we only consider the sequence of computers that Phoenix turns on manually, how many ways can he turn on all the computers? Two sequences are distinct if either the set of computers turned on manually is distinct, or the order of computers turned on manually is distinct. Since this number may be large, please print it modulo $ M $ .

## 输入格式

The first line contains two integers $ n $ and $ M $ ( $ 3 \le n \le 400 $ ; $ 10^8 \le M \le 10^9 $ ) — the number of computers and the modulo. It is guaranteed that $ M $ is prime.

## 输出格式

Print one integer — the number of ways to turn on the computers modulo $ M $ .

## 说明/提示

In the first example, these are the $ 6 $ orders in which Phoenix can turn on all computers:

- $ [1,3] $ . Turn on computer $ 1 $ , then $ 3 $ . Note that computer $ 2 $ turns on automatically after computer $ 3 $ is turned on manually, but we only consider the sequence of computers that are turned on manually.
- $ [3,1] $ . Turn on computer $ 3 $ , then $ 1 $ .
- $ [1,2,3] $ . Turn on computer $ 1 $ , $ 2 $ , then $ 3 $ .
- $ [2,1,3] $
- $ [2,3,1] $
- $ [3,2,1] $

## 样例 #1

### 输入

```
3 100000007
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 100000007
```

### 输出

```
20
```

## 样例 #3

### 输入

```
400 234567899
```

### 输出

```
20914007
```



---

---
title: "Korney Korneevich and XOR (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1582F2
tag: ['动态规划 DP']
---

# Korney Korneevich and XOR (hard version)

## 题目描述

给一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$ ，寻找在 $a$ 的所有递增子序列（可以为空）的异或和中出现的数。

## 输入格式

第一行一个正整数 $n$ 表示序列长度。

第二行 $n$ 个整数表示序列 $a$ 。

## 输出格式

从小到大输出在 $a$ 的所有子序列（可以为空）的异或和中出现的数。

## 说明/提示

$1\le n\le10^6,0\le a_i\le5000$ 。
### 样例解释
对于第一个样例：
- 子序列 $\{\}$ 的异或和为 $0$ 。
- 子序列 $\{2\}$ 的异或和为 $2$ 。
- 子序列 $\{4\}$ 的异或和为 $4$ 。
- 子序列 $\{2,4\}$ 的异或和为 $6$ 。

其他子序列的异或和与上述其中一个子序列的异或和相等。

## 样例 #1

### 输入

```
4
4 2 2 4
```

### 输出

```
4
0 2 4 6
```

## 样例 #2

### 输入

```
8
1 0 1 7 12 5 3 2
```

### 输出

```
12
0 1 2 3 4 5 6 7 10 11 12 13
```



---

---
title: "Non-equal Neighbours"
layout: "post"
diff: 提高+/省选-
pid: CF1585F
tag: ['动态规划 DP', '单调队列', '容斥原理']
---

# Non-equal Neighbours

## 题目描述

You are given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ . Your task is to calculate the number of arrays of $ n $ positive integers $ b_1, b_2, \ldots, b_n $ such that:

- $ 1 \le b_i \le a_i $ for every $ i $ ( $ 1 \le i \le n $ ), and
- $ b_i \neq b_{i+1} $ for every $ i $ ( $ 1 \le i \le n - 1 $ ).

The number of such arrays can be very large, so print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

Print the answer modulo $ 998\,244\,353 $ in a single line.

## 说明/提示

In the first test case possible arrays are $ [1, 2, 1] $ and $ [2, 1, 2] $ .

In the second test case possible arrays are $ [1, 2] $ , $ [1, 3] $ , $ [2, 1] $ and $ [2, 3] $ .

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
2 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
0
```



---

---
title: "Not Escaping"
layout: "post"
diff: 提高+/省选-
pid: CF1627E
tag: ['动态规划 DP']
---

# Not Escaping

## 题目描述

Major Ram is being chased by his arch enemy Raghav. Ram must reach the top of the building to escape via helicopter. The building, however, is on fire. Ram must choose the optimal path to reach the top of the building to lose the minimum amount of health.

The building consists of $ n $ floors, each with $ m $ rooms each. Let $ (i, j) $ represent the $ j $ -th room on the $ i $ -th floor. Additionally, there are $ k $ ladders installed. The $ i $ -th ladder allows Ram to travel from $ (a_i, b_i) $ to $ (c_i, d_i) $ , but not in the other direction. Ram also gains $ h_i $ health points if he uses the ladder $ i $ . It is guaranteed $ a_i < c_i $ for all ladders.

If Ram is on the $ i $ -th floor, he can move either left or right. Travelling across floors, however, is treacherous. If Ram travels from $ (i, j) $ to $ (i, k) $ , he loses $ |j-k| \cdot x_i $ health points.

Ram enters the building at $ (1, 1) $ while his helicopter is waiting at $ (n, m) $ . What is the minimum amount of health Ram loses if he takes the most optimal path? Note this answer may be negative (in which case he gains health). Output "NO ESCAPE" if no matter what path Ram takes, he cannot escape the clutches of Raghav.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627E/deebf4ace32c90c729995f8cfd0fc9e081fe2525.png)

## 输入格式

The first line of input contains $ t $ ( $ 1 \leq t \leq 5 \cdot 10^4 $ ) — the number of test cases.

The first line of each test case consists of $ 3 $ integers $ n, m, k $ ( $ 2 \leq n, m \leq 10^5 $ ; $ 1 \leq k \leq 10^5 $ ) — the number of floors, the number of rooms on each floor and the number of ladders respectively.

The second line of a test case consists of $ n $ integers $ x_1, x_2, \dots, x_n $ ( $ 1 \leq x_i \leq 10^6 $ ).

The next $ k $ lines describe the ladders. Ladder $ i $ is denoted by $ a_i, b_i, c_i, d_i, h_i $ ( $ 1 \leq a_i < c_i \leq n $ ; $ 1 \leq b_i, d_i \leq m $ ; $ 1 \leq h_i \leq 10^6 $ ) — the rooms it connects and the health points gained from using it.

It is guaranteed $ a_i < c_i $ for all ladders and there is at most one ladder between any 2 rooms in the building.

The sum of $ n $ , the sum of $ m $ , and the sum of $ k $ over all test cases do not exceed $ 10^5 $ .

## 输出格式

Output the minimum health Ram loses on the optimal path from $ (1, 1) $ to $ (n, m) $ . If Ram cannot escape the clutches of Raghav regardless of the path he takes, output "NO ESCAPE" (all uppercase, without quotes).

## 说明/提示

The figure for the first test case is in the statement. There are only $ 2 $ possible paths to $ (n, m) $ :

- Ram travels to $ (1, 3) $ , takes the ladder to $ (3, 3) $ , travels to $ (3, 2) $ , takes the ladder to $ (5, 1) $ , travels to $ (5, 3) $ where he finally escapes via helicopter. The health lost would be $ $$$ \begin{align*} &\mathrel{\phantom{=}} x_1 \cdot |1-3| - h_1 + x_3 \cdot |3-2| - h_3 + x_5 \cdot |1-3| \\ &= 5 \cdot 2 - 4 + 8 \cdot 1 - 6 + 4 \cdot 2 \\ &= 16. \end{align*}  $ $  </li><li> Ram travels to  $ (1, 3) $ , takes the ladder to  $ (3, 3) $ , travels to  $ (3, 1) $ , takes the ladder to  $ (5, 2) $ , travels to  $ (5, 3) $  where he finally escapes via helicopter. The health lost would be  $ $  \begin{align*} &\mathrel{\phantom{=}} x_1 \cdot |1-3| - h_1 + x_3 \cdot |3-1| - h_2 + a_5 \cdot |2-3| \\ &= 5 \cdot 2 - 4 + 8 \cdot 2 - 5 + 4 \cdot 1 \\ &= 21. \end{align*}  $ $  </li></ul> Therefore, the minimum health lost would be  $ 16 $ .<p>In the second test case, there is no path to  $ (n, m) $ .</p><p>In the third case case, Ram travels to  $ (1, 3) $  and takes the only ladder to  $ (5, 3) $ . He loses  $ 5 \\cdot 2 $  health points and gains  $ h\_1 = 100 $  health points. Therefore the total loss is  $ 10-100=-90$$$ (negative implies he gains health after the path).

## 样例 #1

### 输入

```
4
5 3 3
5 17 8 1 4
1 3 3 3 4
3 1 5 2 5
3 2 5 1 6
6 3 3
5 17 8 1 4 2
1 3 3 3 4
3 1 5 2 5
3 2 5 1 6
5 3 1
5 17 8 1 4
1 3 5 3 100
5 5 5
3 2 3 7 5
3 5 4 2 1
2 2 5 4 5
4 4 5 2 3
1 2 4 2 2
3 3 5 2 4
```

### 输出

```
16
NO ESCAPE
-90
27
```



---

---
title: "Compatible Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF165E
tag: ['动态规划 DP', '枚举', '进制']
---

# Compatible Numbers

## 题目描述

Two integers $ x $ and $ y $ are compatible, if the result of their bitwise "AND" equals zero, that is, $ a $ $ & $ $ b=0 $ . For example, numbers $ 90 $ $ (1011010_{2}) $ and $ 36 $ $ (100100_{2}) $ are compatible, as $ 1011010_{2} $ $ & $ $ 100100_{2}=0_{2} $ , and numbers $ 3 $ $ (11_{2}) $ and $ 6 $ $ (110_{2}) $ are not compatible, as $ 11_{2} $ $ & $ $ 110_{2}=10_{2} $ .

You are given an array of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to find the following for each array element: is this element compatible with some other element from the given array? If the answer to this question is positive, then you also should find any suitable element.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ) — the number of elements in the given array. The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=4·10^{6} $ ) — the elements of the given array. The numbers in the array can coincide.

## 输出格式

Print $ n $ integers $ ans_{i} $ . If $ a_{i} $ isn't compatible with any other element of the given array $ a_{1},a_{2},...,a_{n} $ , then $ ans_{i} $ should be equal to -1. Otherwise $ ans_{i} $ is any such number, that $ a_{i} $ $ & $ $ ans_{i}=0 $ , and also $ ans_{i} $ occurs in the array $ a_{1},a_{2},...,a_{n} $ .

## 样例 #1

### 输入

```
2
90 36

```

### 输出

```
36 90
```

## 样例 #2

### 输入

```
4
3 6 3 6

```

### 输出

```
-1 -1 -1 -1
```

## 样例 #3

### 输入

```
5
10 6 9 8 2

```

### 输出

```
-1 8 2 2 8
```



---

---
title: "Optimal Partition"
layout: "post"
diff: 提高+/省选-
pid: CF1667B
tag: ['动态规划 DP', '树状数组']
---

# Optimal Partition

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You should divide $ a $ into continuous non-empty subarrays (there are $ 2^{n-1} $ ways to do that).

Let $ s=a_l+a_{l+1}+\ldots+a_r $ . The value of a subarray $ a_l, a_{l+1}, \ldots, a_r $ is:

- $ (r-l+1) $ if $ s>0 $ ,
- $ 0 $ if $ s=0 $ ,
- $ -(r-l+1) $ if $ s<0 $ .

 What is the maximum sum of values you can get with a partition?

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 5 \cdot 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ -10^9 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case print a single integer — the maximum sum of values you can get with an optimal parition.

## 说明/提示

Test case $ 1 $ : one optimal partition is $ [1, 2] $ , $ [-3] $ . $ 1+2>0 $ so the value of $ [1, 2] $ is $ 2 $ . $ -3<0 $ , so the value of $ [-3] $ is $ -1 $ . $ 2+(-1)=1 $ .

Test case $ 2 $ : the optimal partition is $ [0, -2, 3] $ , $ [-4] $ , and the sum of values is $ 3+(-1)=2 $ .

## 样例 #1

### 输入

```
5
3
1 2 -3
4
0 -2 3 -4
5
-1 -2 3 -1 -1
6
-1 2 -3 4 -5 6
7
1 -1 -1 1 -1 -1 1
```

### 输出

```
1
2
1
6
-1
```



---

---
title: "Sorting Pancakes"
layout: "post"
diff: 提高+/省选-
pid: CF1675G
tag: ['动态规划 DP']
---

# Sorting Pancakes

## 题目描述

### 题意简述

有 $n$ 个箱子和 $m$ 个小球，初始时第 $i$ 个箱子有 $a_i$ 个小球。每次操作可以将**一个**小球移到相邻的箱子里。求要使得最终数组 $a_i\ge a_{i+1}$ 的最小操作次数。

## 输入格式

第一行两个正整数 $n,m$。

第二行 $n$ 个非负整数 $a_i$。数据保证 $\sum a_i=m$。

## 输出格式

输出一行一个非负整数，表示答案。

### 数据规模

$1\le n,m\le 250$

## 样例 #1

### 输入

```
6 19
5 3 2 3 3 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 6
3 2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 6
2 1 3
```

### 输出

```
1
```

## 样例 #4

### 输入

```
6 19
3 4 3 3 5 1
```

### 输出

```
3
```

## 样例 #5

### 输入

```
10 1
0 0 0 0 0 0 0 0 0 1
```

### 输出

```
9
```



---

---
title: "Text Editor"
layout: "post"
diff: 提高+/省选-
pid: CF1701E
tag: ['动态规划 DP']
---

# Text Editor

## 题目描述

You wanted to write a text $ t $ consisting of $ m $ lowercase Latin letters. But instead, you have written a text $ s $ consisting of $ n $ lowercase Latin letters, and now you want to fix it by obtaining the text $ t $ from the text $ s $ .

Initially, the cursor of your text editor is at the end of the text $ s $ (after its last character). In one move, you can do one of the following actions:

- press the "left" button, so the cursor is moved to the left by one position (or does nothing if it is pointing at the beginning of the text, i. e. before its first character);
- press the "right" button, so the cursor is moved to the right by one position (or does nothing if it is pointing at the end of the text, i. e. after its last character);
- press the "home" button, so the cursor is moved to the beginning of the text (before the first character of the text);
- press the "end" button, so the cursor is moved to the end of the text (after the last character of the text);
- press the "backspace" button, so the character before the cursor is removed from the text (if there is no such character, nothing happens).

Your task is to calculate the minimum number of moves required to obtain the text $ t $ from the text $ s $ using the given set of actions, or determine it is impossible to obtain the text $ t $ from the text $ s $ .

You have to answer $ T $ independent test cases.

## 输入格式

The first line of the input contains one integer $ T $ ( $ 1 \le T \le 5000 $ ) — the number of test cases. Then $ T $ test cases follow.

The first line of the test case contains two integers $ n $ and $ m $ ( $ 1 \le m \le n \le 5000 $ ) — the length of $ s $ and the length of $ t $ , respectively.

The second line of the test case contains the string $ s $ consisting of $ n $ lowercase Latin letters.

The third line of the test case contains the string $ t $ consisting of $ m $ lowercase Latin letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ ( $ \sum n \le 5000 $ ).

## 输出格式

For each test case, print one integer — the minimum number of moves required to obtain the text $ t $ from the text $ s $ using the given set of actions, or -1 if it is impossible to obtain the text $ t $ from the text $ s $ in the given test case.

## 样例 #1

### 输入

```
6
9 4
aaaaaaaaa
aaaa
7 3
abacaba
aaa
5 4
aabcd
abcd
4 2
abba
bb
6 4
baraka
baka
8 7
question
problem
```

### 输出

```
5
6
3
4
4
-1
```



---

---
title: "Burenka and Traditions (easy version)"
layout: "post"
diff: 提高+/省选-
pid: CF1718A1
tag: ['动态规划 DP', '贪心']
---

# Burenka and Traditions (easy version)

## 题目描述

This is the easy version of this problem. The difference between easy and hard versions is only the constraints on $ a_i $ and on $ n $ . You can make hacks only if both versions of the problem are solved.

Burenka is the crown princess of Buryatia, and soon she will become the $ n $ -th queen of the country. There is an ancient tradition in Buryatia — before the coronation, the ruler must show their strength to the inhabitants. To determine the strength of the $ n $ -th ruler, the inhabitants of the country give them an array of $ a $ of exactly $ n $ numbers, after which the ruler must turn all the elements of the array into zeros in the shortest time. The ruler can do the following two-step operation any number of times:

- select two indices $ l $ and $ r $ , so that $ 1 \le l \le r \le n $ and a non-negative integer $ x $ , then
- for all $ l \leq i \leq r $ assign $ a_i := a_i \oplus x $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). It takes $ \left\lceil \frac{r-l+1}{2} \right\rceil $ seconds to do this operation, where $ \lceil y \rceil $ denotes $ y $ rounded up to the nearest integer.

Help Burenka calculate how much time she will need.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the size of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 5000 $ ) — elements of the array.

It is guaranteed that the sum of $ n $ in all tests does not exceed $ 5000 $ .

## 输出格式

For each test case, output a single number — the minimum time that Burenka will need.

## 说明/提示

In the first test case, Burenka can choose segment $ l = 1 $ , $ r = 4 $ , and $ x=5 $ . so it will fill the array with zeros in $ 2 $ seconds.

In the second test case, Burenka first selects segment $ l = 1 $ , $ r = 2 $ , and $ x = 1 $ , after which $ a = [0, 2, 2] $ , and then the segment $ l = 2 $ , $ r = 3 $ , and $ x=2 $ , which fills the array with zeros. In total, Burenka will spend $ 2 $ seconds.

## 样例 #1

### 输入

```
7
4
5 5 5 5
3
1 3 2
2
0 0
3
2 5 7
6
1 2 3 3 2 1
10
27 27 34 32 2 31 23 56 52 4
5
1822 1799 57 23 55
```

### 输出

```
2
2
0
2
4
7
4
```



---

---
title: "Burenka and Traditions (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1718A2
tag: ['动态规划 DP', '贪心']
---

# Burenka and Traditions (hard version)

## 题目描述

This is the hard version of this problem. The difference between easy and hard versions is only the constraints on $ a_i $ and on $ n $ . You can make hacks only if both versions of the problem are solved.

Burenka is the crown princess of Buryatia, and soon she will become the $ n $ -th queen of the country. There is an ancient tradition in Buryatia — before the coronation, the ruler must show their strength to the inhabitants. To determine the strength of the $ n $ -th ruler, the inhabitants of the country give them an array of $ a $ of exactly $ n $ numbers, after which the ruler must turn all the elements of the array into zeros in the shortest time. The ruler can do the following two-step operation any number of times:

- select two indices $ l $ and $ r $ , so that $ 1 \le l \le r \le n $ and a non-negative integer $ x $ , then
- for all $ l \leq i \leq r $ assign $ a_i := a_i \oplus x $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). It takes $ \left\lceil \frac{r-l+1}{2} \right\rceil $ seconds to do this operation, where $ \lceil y \rceil $ denotes $ y $ rounded up to the nearest integer.

Help Burenka calculate how much time she will need.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 500) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (1 \le n \le 10^5) $ - the size of the array

The second line of each test case contains $ n $ integers $ a_1, a_2, \cdots , a_n $ $ (0 \le a_i < 2^{30}) $ — elements of the array.

It is guaranteed that the sum of $ n $ in all tests does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single number — the minimum time that Burenka will need.

## 说明/提示

In the first test case, Burenka can choose segment $ l = 1 $ , $ r = 4 $ , and $ x=5 $ . so it will fill the array with zeros in $ 2 $ seconds.

In the second test case, Burenka first selects segment $ l = 1 $ , $ r = 2 $ , and $ x = 1 $ , after which $ a = [0, 2, 2] $ , and then the segment $ l = 2 $ , $ r = 3 $ , and $ x=2 $ , which fills the array with zeros. In total, Burenka will spend $ 2 $ seconds.

## 样例 #1

### 输入

```
7
4
5 5 5 5
3
1 3 2
2
0 0
3
2 5 7
6
1 2 3 3 2 1
10
27 27 34 32 2 31 23 56 52 4
5
1822 1799 57 23 55
```

### 输出

```
2
2
0
2
4
7
4
```



---

---
title: "Intersection and Union"
layout: "post"
diff: 提高+/省选-
pid: CF1743F
tag: ['动态规划 DP', '数学', '线段树']
---

# Intersection and Union

## 题目描述

You are given $ n $ segments on the coordinate axis. The $ i $ -th segment is $ [l_i, r_i] $ . Let's denote the set of all integer points belonging to the $ i $ -th segment as $ S_i $ .

Let $ A \cup B $ be the union of two sets $ A $ and $ B $ , $ A \cap B $ be the intersection of two sets $ A $ and $ B $ , and $ A \oplus B $ be the symmetric difference of $ A $ and $ B $ (a set which contains all elements of $ A $ and all elements of $ B $ , except for the ones that belong to both sets).

Let $ [\mathbin{op}_1, \mathbin{op}_2, \dots, \mathbin{op}_{n-1}] $ be an array where each element is either $ \cup $ , $ \oplus $ , or $ \cap $ . Over all $ 3^{n-1} $ ways to choose this array, calculate the sum of the following values:

 $ $$$|(((S_1\ \mathbin{op}_1\ S_2)\ \mathbin{op}_2\ S_3)\ \mathbin{op}_3\ S_4)\ \dots\ \mathbin{op}_{n-1}\ S_n| $ $ </p><p>In this expression,  $ |S| $  denotes the size of the set  $ S$$$.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 3 \cdot 10^5 $ ).

Then, $ n $ lines follow. The $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 0 \le l_i \le r_i \le 3 \cdot 10^5 $ ).

## 输出格式

Print one integer — the sum of $ |(((S_1\ \mathbin{op}_1\ S_2)\ \mathbin{op}_2\ S_3)\ \mathbin{op}_3\ S_4)\ \dots\ \mathbin{op}_{n-1}\ S_n| $ over all possible ways to choose $ [\mathbin{op}_1, \mathbin{op}_2, \dots, \mathbin{op}_{n-1}] $ . Since the answer can be huge, print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
3 5
4 8
2 2
1 9
```

### 输出

```
162
```

## 样例 #2

### 输入

```
4
1 9
3 5
4 8
2 2
```

### 输出

```
102
```



---

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
title: "Yet Another Array Counting Problem"
layout: "post"
diff: 提高+/省选-
pid: CF1748E
tag: ['动态规划 DP', '树形 DP', '笛卡尔树']
---

# Yet Another Array Counting Problem

## 题目描述

对于长度为 $n$ 的序列 $x$，定义其在子段 $[l;r]$ 的“最左端最大值位置”为最小的满足 $l\leq i\leq r$ 且 $x_i=\max_{j=l}^rx_j$ 的整数 $i$。  
给定整数 $n,m$ 和长度为 $n$ 的序列 $a$，你需要求出满足下列要求的序列 $b$ 的数量：

- 序列 $b$ 长度为 $n$，且对任意整数 $i(1\leq i\leq n)$ 都有 $1\leq b_i\leq m$ 成立。
- 对任意整数 $l,r(1\leq l\leq r\leq n)$，总有 $a,b$ 在子段 $[l;r]$ 的“最左端最大值位置”相同。

答案对 $10^9+7$ 取模。  
每个测试点包含多组数据。

## 输入格式

第一行输入一个整数 $t(1\leq t\leq10^3)$ 表示数据组数，接下来对于每组数据：  
第一行输入两个整数 $n,m(2\leq n,m\leq2\times10^5;\sum n\times m\leq10^6)$。  
接下来输入一行 $n$ 个整数表示序列 $a(1\leq a_i\leq m)$。

## 输出格式

对于每组数据：  
输出满足要求的序列 $b$ 的数量对 $10^9+7$ 取模后的值。

### 样例解释

- 对于第一组数据：
	- 下面是所有 $8$ 个满足要求的序列 $b$：  
    $[1,2,1],[1,2,2],[1,3,1],[1,3,2],[1,3,3],[2,3,1],[2,3,2],[2,3,3]$。
- 对于第二组数据：
	- 下面是所有 $5$ 个满足要求的序列 $b$：  
    $[1,1,1,1],[2,1,1,1],[2,2,1,1],[2,2,2,1],[2,2,2,2]$。

## 样例 #1

### 输入

```
4
3 3
1 3 2
4 2
2 2 2 2
6 9
6 9 6 9 6 9
9 100
10 40 20 20 100 60 80 60 60
```

### 输出

```
8
5
11880
351025663
```



---

---
title: "Wish I Knew How to Sort"
layout: "post"
diff: 提高+/省选-
pid: CF1753C
tag: ['动态规划 DP', '组合数学', '概率论']
---

# Wish I Knew How to Sort

## 题目描述

You are given a binary array $ a $ (all elements of the array are $ 0 $ or $ 1 $ ) of length $ n $ . You wish to sort this array, but unfortunately, your algorithms teacher forgot to teach you sorting algorithms. You perform the following operations until $ a $ is sorted:

1. Choose two random indices $ i $ and $ j $ such that $ i < j $ . Indices are chosen equally probable among all pairs of indices $ (i, j) $ such that $ 1 \le i < j \le n $ .
2. If $ a_i > a_j $ , then swap elements $ a_i $ and $ a_j $ .

What is the [expected number](https://en.wikipedia.org/wiki/Expected_value) of such operations you will perform before the array becomes sorted?

It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{998\,244\,353} $ . Output the integer equal to $ p \cdot q^{-1} \bmod 998\,244\,353 $ . In other words, output such an integer $ x $ that $ 0 \le x < 998\,244\,353 $ and $ x \cdot q \equiv p \pmod{998\,244\,353} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 200\,000 $ ) — the number of elements in the binary array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ a_i \in \{0, 1\} $ ) — elements of the array.

It's guaranteed that sum of $ n $ over all test cases does not exceed $ 200\,000 $ .

## 输出格式

For each test case print one integer — the value $ p \cdot q^{-1} \bmod 998\,244\,353 $ .

## 说明/提示

Consider the first test case. If the pair of indices $ (2, 3) $ will be chosen, these elements will be swapped and array will become sorted. Otherwise, if one of pairs $ (1, 2) $ or $ (1, 3) $ will be selected, nothing will happen. So, the probability that the array will become sorted after one operation is $ \frac{1}{3} $ , the probability that the array will become sorted after two operations is $ \frac{2}{3} \cdot \frac{1}{3} $ , the probability that the array will become sorted after three operations is $ \frac{2}{3} \cdot \frac{2}{3} \cdot \frac{1}{3} $ and so on. The expected number of operations is $ \sum \limits_{i=1}^{\infty} \left(\frac{2}{3} \right)^{i - 1} \cdot \frac{1}{3} \cdot i = 3 $ .

In the second test case the array is already sorted so the expected number of operations is zero.

In the third test case the expected number of operations equals to $ \frac{75}{4} $ so the answer is $ 75 \cdot 4^{-1} \equiv 249\,561\,107 \pmod {998\,244\,353} $ .

## 样例 #1

### 输入

```
3
3
0 1 0
5
0 0 1 1 1
6
1 1 1 0 0 1
```

### 输出

```
3
0
249561107
```



---

---
title: "Decomposition"
layout: "post"
diff: 提高+/省选-
pid: CF1766E
tag: ['动态规划 DP', '前缀和']
---

# Decomposition

## 题目描述

For a sequence of integers $ [x_1, x_2, \dots, x_k] $ , let's define its decomposition as follows:

Process the sequence from the first element to the last one, maintaining the list of its subsequences. When you process the element $ x_i $ , append it to the end of the first subsequence in the list such that the bitwise AND of its last element and $ x_i $ is greater than $ 0 $ . If there is no such subsequence in the list, create a new subsequence with only one element $ x_i $ and append it to the end of the list of subsequences.

For example, let's analyze the decomposition of the sequence $ [1, 3, 2, 0, 1, 3, 2, 1] $ :

- processing element $ 1 $ , the list of subsequences is empty. There is no subsequence to append $ 1 $ to, so we create a new subsequence $ [1] $ ;
- processing element $ 3 $ , the list of subsequences is $ [[1]] $ . Since the bitwise AND of $ 3 $ and $ 1 $ is $ 1 $ , the element is appended to the first subsequence;
- processing element $ 2 $ , the list of subsequences is $ [[1, 3]] $ . Since the bitwise AND of $ 2 $ and $ 3 $ is $ 2 $ , the element is appended to the first subsequence;
- processing element $ 0 $ , the list of subsequences is $ [[1, 3, 2]] $ . There is no subsequence to append $ 0 $ to, so we create a new subsequence $ [0] $ ;
- processing element $ 1 $ , the list of subsequences is $ [[1, 3, 2], [0]] $ . There is no subsequence to append $ 1 $ to, so we create a new subsequence $ [1] $ ;
- processing element $ 3 $ , the list of subsequences is $ [[1, 3, 2], [0], [1]] $ . Since the bitwise AND of $ 3 $ and $ 2 $ is $ 2 $ , the element is appended to the first subsequence;
- processing element $ 2 $ , the list of subsequences is $ [[1, 3, 2, 3], [0], [1]] $ . Since the bitwise AND of $ 2 $ and $ 3 $ is $ 2 $ , the element is appended to the first subsequence;
- processing element $ 1 $ , the list of subsequences is $ [[1, 3, 2, 3, 2], [0], [1]] $ . The element $ 1 $ cannot be appended to any of the first two subsequences, but can be appended to the third one.

The resulting list of subsequences is $ [[1, 3, 2, 3, 2], [0], [1, 1]] $ .

Let $ f([x_1, x_2, \dots, x_k]) $ be the number of subsequences the sequence $ [x_1, x_2, \dots, x_k] $ is decomposed into.

Now, for the problem itself.

You are given a sequence $ [a_1, a_2, \dots, a_n] $ , where each element is an integer from $ 0 $ to $ 3 $ . Let $ a[i..j] $ be the sequence $ [a_i, a_{i+1}, \dots, a_j] $ . You have to calculate $ \sum \limits_{i=1}^n \sum \limits_{j=i}^n f(a[i..j]) $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 3 $ ).

## 输出格式

Print one integer, which should be equal to $ \sum \limits_{i=1}^n \sum \limits_{j=i}^n f(a[i..j]) $ .

## 样例 #1

### 输入

```
8
1 3 2 0 1 3 2 1
```

### 输出

```
71
```

## 样例 #2

### 输入

```
5
0 0 0 0 0
```

### 输出

```
35
```



---

---
title: "Count Binary Strings"
layout: "post"
diff: 提高+/省选-
pid: CF1767C
tag: ['动态规划 DP']
---

# Count Binary Strings

## 题目描述

You are given an integer $ n $ . You have to calculate the number of binary (consisting of characters 0 and/or 1) strings $ s $ meeting the following constraints.

For every pair of integers $ (i, j) $ such that $ 1 \le i \le j \le n $ , an integer $ a_{i,j} $ is given. It imposes the following constraint on the string $ s_i s_{i+1} s_{i+2} \dots s_j $ :

- if $ a_{i,j} = 1 $ , all characters in $ s_i s_{i+1} s_{i+2} \dots s_j $ should be the same;
- if $ a_{i,j} = 2 $ , there should be at least two different characters in $ s_i s_{i+1} s_{i+2} \dots s_j $ ;
- if $ a_{i,j} = 0 $ , there are no additional constraints on the string $ s_i s_{i+1} s_{i+2} \dots s_j $ .

Count the number of binary strings $ s $ of length $ n $ meeting the aforementioned constraints. Since the answer can be large, print it modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ).

Then $ n $ lines follow. The $ i $ -th of them contains $ n-i+1 $ integers $ a_{i,i}, a_{i,i+1}, a_{i,i+2}, \dots, a_{i,n} $ ( $ 0 \le a_{i,j} \le 2 $ ).

## 输出格式

Print one integer — the number of strings meeting the constraints, taken modulo $ 998244353 $ .

## 说明/提示

In the first example, the strings meeting the constraints are 001, 010, 011, 100, 101, 110.

In the second example, the strings meeting the constraints are 001, 110.

## 样例 #1

### 输入

```
3
1 0 2
1 0
1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
1 1 2
1 0
1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
1 2 1
1 0
1
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3
2 0 2
0 1
1
```

### 输出

```
0
```



---

---
title: "Hossam and a Letter"
layout: "post"
diff: 提高+/省选-
pid: CF1771E
tag: ['动态规划 DP', '枚举', '双指针 two-pointer']
---

# Hossam and a Letter

## 题目描述

Hossam bought a new piece of ground with length $ n $ and width $ m $ , he divided it into an $ n \cdot m $ grid, each cell being of size $ 1\times1 $ .

Since Hossam's name starts with the letter 'H', he decided to draw the capital letter 'H' by building walls of size $ 1\times1 $ on some squares of the ground. Each square $ 1\times1 $ on the ground is assigned a quality degree: perfect, medium, or bad.

The process of building walls to form up letter 'H' has the following constraints:

- The letter must consist of one horizontal and two vertical lines.
- The vertical lines must not be in the same or neighboring columns.
- The vertical lines must start in the same row and end in the same row (and thus have the same length).
- The horizontal line should connect the vertical lines, but must not cross them.
- The horizontal line can be in any row between the vertical lines (not only in the middle), except the top and the bottom one. (With the horizontal line in the top row the letter looks like 'n', and in the bottom row like 'U'.)
- It is forbidden to build walls in cells of bad quality.
- You can use at most one square of medium quality.
- You can use any number of squares of perfect quality.

Find the maximum number of walls that can be used to draw the letter 'H'.

Check the note for more clarification.

## 输入格式

The first line of the input contains two integer numbers $ n $ , $ m $ ( $ 1 \le n, m \le 400 $ ).

The next $ n $ lines of the input contain $ m $ characters each, describing the grid. The character '.' stands for a perfect square, the character 'm' stands for a medium square, and the character '\#' stands for a bad square.

## 输出格式

Print a single integer — the maximum number of walls that form a capital letter 'H'.

If it is not possible to draw any letter 'H', print $ 0 $ .

## 说明/提示

In the first test case, we can't build the letter 'H'.

For the second test case, the figure below represents the grid and some of the valid letters 'H'. Perfect, medium, and bad squares are represented with white, yellow, and black colors respectively.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771E/7ab52d112de710667f4c7cf4e814613751fe43eb.png)

## 样例 #1

### 输入

```
2 3
#m.
.#.
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7 8
...#.m..
..m...m.
.#..#.m#
...m..m.
m.......
..#.m.mm
......m.
```

### 输出

```
16
```



---

---
title: "Two Chess Pieces"
layout: "post"
diff: 提高+/省选-
pid: CF1774E
tag: ['动态规划 DP', '树形 DP']
---

# Two Chess Pieces

## 题目描述

# Two Chess Pieces


Cirno\_9baka 有一棵包含 $n$ 个节点的树。他愿意把它与你分享，这意味着你可以对它进行一些操作。  

最初，树的 $1$ 号节点上有两个棋子。对每个操作，您可以选择任意一个棋子，并将其移动到相邻节点。你需要确保两个棋子之间的距离不会超过 $d$。

给你两个序列，分别表示两个棋子需要经过的节点（可以以**任何顺序**经过）。最终，它们必须回到根节点。作为一个好奇的男孩，Cirno\_9baka 想知道最少操作次数。

## 输入格式

第一行包含两个整数 $n$ 和 $d$（$2\le d\le n\le 2\cdot 10^5$）。
以下 $n-1$ 行的第 $i$ 行包含两个整数 $ u_i, v_i $ $ (1 \le u_i, v_i \le n) $，表示节点 $ u_i, v_i $ 之间的边。
保证这些边形成一棵树。
下一行包含一个整数 $m_1$（$1\le m_1\le n$）和 $m_1$ 个整数 $a_1，a_2，\ldots，a_{m_1}$（$1\le a_i\le n$，所有$a_i$都是不同的）- 第一个棋子需要经过的节点序列。
第二行包含一个整数$m_2$（$1\le m_2\le n$）和 $m_2$ 个整数 $b_1，b_2，\ldots，b_{m_2}$（$1\le b_i\le n$，所有$b_i$都是不同的）-第二棋子需要经过的节点序列。

## 输出格式

输出一个整数 - 最小操作次数。

## 样例 #1

### 输入

```
4 2
1 2
1 3
2 4
1 3
1 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 2
1 2
2 3
3 4
4 1 2 3 4
1 1
```

### 输出

```
8
```



---

---
title: "Representative Sampling"
layout: "post"
diff: 提高+/省选-
pid: CF178F3
tag: ['动态规划 DP', '字典树 Trie']
---

# Representative Sampling

## 题目描述

The Smart Beaver from ABBYY has a long history of cooperating with the "Institute of Cytology and Genetics". Recently, the Institute staff challenged the Beaver with a new problem. The problem is as follows.

There is a collection of $ n $ proteins (not necessarily distinct). Each protein is a string consisting of lowercase Latin letters. The problem that the scientists offered to the Beaver is to select a subcollection of size $ k $ from the initial collection of proteins so that the representativity of the selected subset of proteins is maximum possible.

The Smart Beaver from ABBYY did some research and came to the conclusion that the representativity of a collection of proteins can be evaluated by a single number, which is simply calculated. Let's suppose we have a collection $ {a_{1},...,a_{k}} $ consisting of $ k $ strings describing proteins. The representativity of this collection is the following value:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178F3/c7b3873e6751582bb5e2ad2c1deb58138ab9c543.png)where $ f(x,y) $ is the length of the longest common prefix of strings $ x $ and $ y $ ; for example, $ f( $ "abc", "abd" $ )=2 $ , and $ f( $ "ab", "bcd" $ )=0 $ .

Thus, the representativity of collection of proteins $ { $ "abc", "abd", "abe" $ } $ equals $ 6 $ , and the representativity of collection $ { $ "aaa", "ba", "ba" $ } $ equals $ 2 $ .

Having discovered that, the Smart Beaver from ABBYY asked the Cup contestants to write a program that selects, from the given collection of proteins, a subcollection of size $ k $ which has the largest possible value of representativity. Help him to solve this problem!

## 输入格式

The first input line contains two integers $ n $ and $ k $ ( $ 1<=k<=n $ ), separated by a single space. The following $ n $ lines contain the descriptions of proteins, one per line. Each protein is a non-empty string of no more than $ 500 $ characters consisting of only lowercase Latin letters (a $ ... $ z). Some of the strings may be equal.

The input limitations for getting 20 points are:

- $ 1<=n<=20 $

The input limitations for getting 50 points are:

- $ 1<=n<=100 $

The input limitations for getting 100 points are:

- $ 1<=n<=2000 $

## 输出格式

Print a single number denoting the largest possible value of representativity that a subcollection of size $ k $ of the given collection of proteins can have.

## 样例 #1

### 输入

```
3 2
aba
bzd
abq

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 3
eee
rrr
ttt
qqq

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4 3
aaa
abba
abbc
abbd

```

### 输出

```
9

```



---

---
title: "Hot Start Up (easy version)"
layout: "post"
diff: 提高+/省选-
pid: CF1799D1
tag: ['动态规划 DP']
---

# Hot Start Up (easy version)

## 题目描述

This is an easy version of the problem. The constraints of $ t $ , $ n $ , $ k $ are the only difference between versions.

You have a device with two CPUs. You also have $ k $ programs, numbered $ 1 $ through $ k $ , that you can run on the CPUs.

The $ i $ -th program ( $ 1 \le i \le k $ ) takes $ cold_i $ seconds to run on some CPU. However, if the last program we ran on this CPU was also program $ i $ , it only takes $ hot_i $ seconds ( $ hot_i \le cold_i $ ). Note that this only applies if we run program $ i $ multiple times consecutively — if we run program $ i $ , then some different program, then program $ i $ again, it will take $ cold_i $ seconds the second time.

You are given a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of integers from $ 1 $ to $ k $ . You need to use your device to run programs $ a_1, a_2, \ldots, a_n $ in sequence. For all $ 2 \le i \le n $ , you cannot start running program $ a_i $ until program $ a_{i - 1} $ has completed.

Find the minimum amount of time needed to run all programs $ a_1, a_2, \ldots, a_n $ in sequence.

## 输入格式

Input consists of multiple test cases. The first line contains a single integer $ t $ , the number of test cases ( $ 1 \le t \le 5000 $ ).

The first line of each test case contains $ n $ and $ k $ ( $ 1 \le n, k \le 5000 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le k $ ).

The third line of each test case contains $ k $ integers $ cold_1, cold_2, \ldots, cold_k $ ( $ 1 \le cold_i \le 10^9 $ ).

The fourth line of each test case contains $ k $ integers $ hot_1, hot_2, \ldots, hot_k $ ( $ 1 \le hot_i \le cold_i $ ).

It is guaranteed the sum of $ n $ and the sum of $ k $ over all test cases do not exceed $ 5000 $ .

## 输出格式

For each test case, print the minimum time needed to run all programs in the given order.

## 说明/提示

In the first test case, we can do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 3 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 2 $ seconds to run.
- Run program $ a_3 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 3 + 2 + 1 = 6 $ seconds to run them all. We can show this is optimal.

In the second test case, we can use do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 5 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 3 $ seconds to run.
- Run program $ a_3 = 1 $ on CPU $ 1 $ . The last program run on this CPU was also program $ 1 $ , so it takes $ hot_1 = 2 $ seconds to run.
- Run program $ a_4 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 5 + 3 + 2 + 1 = 11 $ seconds. We can show this is optimal.

## 样例 #1

### 输入

```
9
3 2
1 2 2
3 2
2 1
4 2
1 2 1 2
5 3
2 1
4 3
1 2 3 1
100 100 100
1 1 1
5 2
2 1 2 1 1
65 45
54 7
5 3
1 3 2 1 2
2 2 2
1 1 1
5 1
1 1 1 1 1
1000000000
999999999
5 6
1 6 1 4 1
3 6 4 1 4 5
1 1 1 1 4 1
1 3
3
4 5 6
1 2 3
8 3
3 3 3 1 2 3 2 1
10 10 8
10 10 5
```

### 输出

```
6
11
301
225
8
4999999996
11
6
63
```



---

---
title: "Hot Start Up (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1799D2
tag: ['动态规划 DP', '线段树']
---

# Hot Start Up (hard version)

## 题目描述

This is a hard version of the problem. The constraints of $ t $ , $ n $ , $ k $ are the only difference between versions.

You have a device with two CPUs. You also have $ k $ programs, numbered $ 1 $ through $ k $ , that you can run on the CPUs.

The $ i $ -th program ( $ 1 \le i \le k $ ) takes $ cold_i $ seconds to run on some CPU. However, if the last program we ran on this CPU was also program $ i $ , it only takes $ hot_i $ seconds ( $ hot_i \le cold_i $ ). Note that this only applies if we run program $ i $ multiple times consecutively — if we run program $ i $ , then some different program, then program $ i $ again, it will take $ cold_i $ seconds the second time.

You are given a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of integers from $ 1 $ to $ k $ . You need to use your device to run programs $ a_1, a_2, \ldots, a_n $ in sequence. For all $ 2 \le i \le n $ , you cannot start running program $ a_i $ until program $ a_{i - 1} $ has completed.

Find the minimum amount of time needed to run all programs $ a_1, a_2, \ldots, a_n $ in sequence.

## 输入格式

Input consists of multiple test cases. The first line contains a single integer $ t $ , the number of test cases ( $ 1 \le t \le 10^5 $ ).

The first line of each test case contains $ n $ and $ k $ ( $ 1 \le n, k \le 3 \cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le k $ ).

The third line of each test case contains $ k $ integers $ cold_1, cold_2, \ldots, cold_k $ ( $ 1 \le cold_i \le 10^9 $ ).

The fourth line of each test case contains $ k $ integers $ hot_1, hot_2, \ldots, hot_k $ ( $ 1 \le hot_i \le cold_i $ ).

It is guaranteed the sum of $ n $ and the sum of $ k $ over all test cases do not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print the minimum time needed to run all programs in the given order.

## 说明/提示

In the first test case, we can do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 3 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 2 $ seconds to run.
- Run program $ a_3 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 3 + 2 + 1 = 6 $ seconds to run them all. We can show this is optimal.

In the second test case, we can use do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 5 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 3 $ seconds to run.
- Run program $ a_3 = 1 $ on CPU $ 1 $ . The last program run on this CPU was also program $ 1 $ , so it takes $ hot_1 = 2 $ seconds to run.
- Run program $ a_4 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 5 + 3 + 2 + 1 = 11 $ seconds. We can show this is optimal.

## 样例 #1

### 输入

```
9
3 2
1 2 2
3 2
2 1
4 2
1 2 1 2
5 3
2 1
4 3
1 2 3 1
100 100 100
1 1 1
5 2
2 1 2 1 1
65 45
54 7
5 3
1 3 2 1 2
2 2 2
1 1 1
5 1
1 1 1 1 1
1000000000
999999999
5 6
1 6 1 4 1
3 6 4 1 4 5
1 1 1 1 4 1
1 3
3
4 5 6
1 2 3
8 3
3 3 3 1 2 3 2 1
10 10 8
10 10 5
```

### 输出

```
6
11
301
225
8
4999999996
11
6
63
```



---

---
title: "Music Festival"
layout: "post"
diff: 提高+/省选-
pid: CF1801C
tag: ['动态规划 DP', '树状数组']
---

# Music Festival

## 题目描述

The boy Vitya loves to listen to music very much. He knows that $ n $ albums are due to be released this Friday, $ i $ -th of which contains $ k_i $ tracks. Of course, Vitya has already listened to all the tracks, and knows that in the $ i $ -th album, the coolness of the $ j $ -th track is equal to $ a_{i,j} $ .Vitya has a friend Masha, whom he really wants to invite to the festival, where his favorite bands perform. However, in order for a friend to agree, she must first evaluate the released novelties. Vitya knows that if Masha listens to a track that was cooler than all the previous ones, she will get 1 unit of impression. Unfortunately, albums can only be listened to in their entirety, without changing the songs in them in places.

Help Vitya find such an order of albums so that Masha's impression turns out to be as much as possible, and she definitely went to the festival with him.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer t ( $ 1 \le t \le 200\,000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 200\,000 $ ) — number of albums.

The album descriptions follow. Each album description consists of two lines:

The first line contains a single integer $ k_i $ ( $ 1 \le k_i \le 200\,000 $ ) — the number of tracks in the $ i $ th album.

The following line contains $ k_i $ integers $ a_{i, 1},\ a_{i, 2},\ a_{i, 3},\ \ldots,\ a_{i, k_i} $ ( $ 1 \le a_{i,j} \le 200\,000 $ ) — the coolness of the tracks in the $ i $ album.

Denote for $ \sum k_i $ the sum of all $ k_i $ . It is guaranteed that $ \sum k_i \le 200\,000 $ .

## 输出格式

For each test case print the singular number — the maximum impression that Masha can get.

## 说明/提示

In the first test example, the optimal order is listening to the 4th, 2nd, 3rd and 1st albums.

In this case, Masha will listen to the tracks in the following order: 1; 7; 8, 6; 4, 9, 4, 6, 8 and will receive 4 units of impression.

In the second test example, you must first listen to the 1st, then the 4th, and in any order the 2nd and 3rd. In this case, Masha will get the maximum impression, and for every song in the 1st and 4th albums and nothing for the 2nd and 3rd.

## 样例 #1

### 输入

```
2
4
5
4 9 4 6 8
1
7
2
8 6
1
1
4
2
3 4
2
1 8
2
2 8
2
7 9
```

### 输出

```
4
4
```



---

---
title: "The way home"
layout: "post"
diff: 提高+/省选-
pid: CF1801D
tag: ['动态规划 DP']
---

# The way home

## 题目描述

The famous magician Borya Budini traveled through the country $ X $ , which consists of $ n $ cities. However, an accident happened, and he was robbed in the city number $ 1 $ . Now Budini will have a hard way home to the city number $ n $ .He's going to get there by plane. In total, there are $ m $ flights in the country, $ i $ -th flies from city $ a_i $ to city $ b_i $ and costs $ s_i $ coins. Note that the $ i $ -th flight is one-way, so it can't be used to get from city $ b_i $ to city $ a_i $ . To use it, Borya must be in the city $ a_i $ and have at least $ s_i $ coins (which he will spend on the flight).

After the robbery, he has only $ p $ coins left, but he does not despair! Being in the city $ i $ , he can organize performances every day, each performance will bring him $ w_i $ coins.

Help the magician find out if he will be able to get home, and what is the minimum number of performances he will have to organize.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 80 $ ) – the number of test cases. The description of test cases follows.

The first line contains three integers $ n $ , $ m $ and $ p $ ( $ 2 \le n \le 800 $ , $ 1 \le m \le 3000 $ , $ 0 \le p \le 10^9 $ ) — the number of cities, the number of flights and the initial amount of coins.

The second line contains $ n $ integers $ w_1, w_2, \ldots, w_n $ $ (1 \le w_i \le 10^9) $ — profit from representations.

The following $ m $ lines each contain three integers $ a_i $ , $ b_i $ and $ s_i $ ( $ 1 \le a_i, b_i \le n $ , $ 1 \le s_i \le 10^9 $ ) — the starting and ending city, and the cost of $ i $ -th flight.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 800 $ and the sum of $ m $ over all test cases does not exceed $ 10000 $ .

## 输出格式

For each test case print a single integer — the minimum number of performances Borya will have to organize to get home, or $ -1 $ if it is impossible to do this.

## 说明/提示

In the first example, it is optimal for Borya to make $ 4 $ performances in the first city, having as a result $ 2 + 7 \cdot 4 = 30 $ coins, and then walk along the route $ 1-3-2-4 $ , spending $ 6+8+11=25 $ coins. In the second example, it is optimal for Borya to make $ 15 $ performances in the first city, fly to $ 3 $ city, make $ 9 $ performances there, and then go to $ 4 $ city.

## 样例 #1

### 输入

```
4
4 4 2
7 4 3 1
1 2 21
3 2 6
1 3 8
2 4 11
4 4 10
1 2 10 1
1 2 20
2 4 30
1 3 25
3 4 89
4 4 7
5 1 6 2
1 2 5
2 3 10
3 4 50
3 4 70
4 1 2
1 1 1 1
1 3 2
```

### 输出

```
4
24
10
-1
```



---

---
title: "DSU Master"
layout: "post"
diff: 提高+/省选-
pid: CF1806D
tag: ['动态规划 DP']
---

# DSU Master

## 题目描述

You are given an integer $ n $ and an array $ a $ of length $ n-1 $ whose elements are either $ 0 $ or $ 1 $ .

Let us define the value of a permutation $ ^\dagger $ $ p $ of length $ m-1 $ ( $ m \leq n $ ) by the following process.

Let $ G $ be a graph of $ m $ vertices labeled from $ 1 $ to $ m $ that does not contain any edges. For each $ i $ from $ 1 $ to $ m-1 $ , perform the following operations:

- define $ u $ and $ v $ as the (unique) vertices in the weakly connected components $ ^\ddagger $ containing vertices $ p_i $ and $ p_i+1 $ respectively with only incoming edges $ ^{\dagger\dagger} $ ;
- in graph $ G $ , add a directed edge from vertex $ v $ to $ u $ if $ a_{p_i}=0 $ , otherwise add a directed edge from vertex $ u $ to $ v $ (if $ a_{p_i}=1 $ ).

 Note that after each step, it can be proven that each weakly connected component of $ G $ has a unique vertex with only incoming edges.Then, the value of $ p $ is the number of incoming edges of vertex $ 1 $ of $ G $ .

For each $ k $ from $ 1 $ to $ n-1 $ , find the sum of values of all $ k! $ permutations of length $ k $ . Since this value can be big, you are only required to compute this value under modulo $ 998\,244\,353 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1806D/27fd1ea1a5a6a85d7d3f7a744475a00230fb82dd.png) Operations when $ n=3 $ , $ a=[0,1] $ and $ p=[1,2] $  $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^\ddagger $ The weakly connected components of a directed graph is the same as the components of the undirected version of the graph. Formally, for directed graph $ G $ , define a graph $ H $ where for all edges $ a \to b $ in $ G $ , you add an undirected edge $ a \leftrightarrow b $ in $ H $ . Then the weakly connected components of $ G $ are the components of $ H $ .

 $ ^{\dagger\dagger} $ Note that a vertex that has no edges is considered to have only incoming edges.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2\le n\le 5 \cdot 10^5 $ ).

The second line of each test case contains $ n-1 $ integers $ a_1, a_2, \ldots, a_{n-1} $ ( $ a_i $ is $ 0 $ or $ 1 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n-1 $ integers in a line, the $ i $ -th integer should represent the answer when $ k=i $ , under modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first test case.

When $ k=1 $ , there is only $ 1 $ permutation $ p $ .

- When $ p=[1] $ , we will add a single edge from vertex $ 2 $ to $ 1 $ . Vertex $ 1 $ will have $ 1 $ incoming edge. So the value of $ [1] $ is $ 1 $ .

Therefore when $ k=1 $ , the answer is $ 1 $ .

When $ k=2 $ , there are $ 2 $ permutations $ p $ .

- When $ p=[1,2] $ , we will add an edge from vertex $ 2 $ to $ 1 $ and an edge from $ 3 $ to $ 1 $ . Vertex $ 1 $ will have $ 2 $ incoming edges. So the value of $ [1,2] $ is $ 2 $ .
- When $ p=[2,1] $ , we will add an edge from vertex $ 3 $ to $ 2 $ and an edge from $ 2 $ to $ 1 $ . Vertex $ 1 $ will have $ 1 $ incoming edge. So the value of $ [2,1] $ is $ 1 $ .

Therefore when $ k=2 $ , the answer is $ 2+1=3 $ .

## 样例 #1

### 输入

```
2
3
0 0
9
0 1 0 0 0 1 0 0
```

### 输出

```
1 3 
1 2 7 31 167 1002 7314 60612
```



---

---
title: "Trees and Segments"
layout: "post"
diff: 提高+/省选-
pid: CF1858D
tag: ['动态规划 DP', '双指针 two-pointer']
---

# Trees and Segments

## 题目描述

# 树木与区间


夏季信息学学校的教师们决定在一排中种植 $ n $ 棵树，而且决定只种植橡树和冷杉树。为此，他们制定了一个计划，可以用长度为 $ n $ 的二进制字符串 $ s $ 表示。如果 $ s_i = 0 $，则第 $ i $ 棵树应该是橡树，如果 $ s_i = 1 $，则第 $ i $ 棵树应该是冷杉树。

树木种植的日子就是明天，后天一个督察将来到学校。督察非常喜欢大自然，他将根据以下方式评估这一排树的美丽程度：

- 首先，他将计算 $ l_0 $，作为该计划 $ s $ 中连续的橡树的最大数目（计划 $ s $ 中由零构成的最大子串）。如果树行中没有橡树，则 $ l_0 = 0 $。
- 然后，他将计算 $ l_1 $，作为该计划 $ s $ 中连续的冷杉树的最大数目（计划 $ s $ 中由一构成的最大子串）。如果树行中没有冷杉树，则 $ l_1 = 0 $。
- 最后，他将计算树行的美丽程度为 $ a \cdot l_0 + l_1 $，其中 $ a $ 是督察最喜欢的数。

教师们知道参数 $ a $ 的值，但出于安全原因，他们不能告诉你。他们只告诉你 $ a $ 是从 $ 1 $ 到 $ n $ 的整数。

由于树木尚未种植，教师们决定在不超过 $ k $ 棵树上更改树的类型（即在计划中从 $ 0 $ 更改为 $ 1 $ 或从 $ 1 $ 更改为 $ 0 $），以便根据督察的计算来最大化树行的美丽程度。

对于从 $ 1 $ 到 $ n $ 的每个整数 $ j $ 独立回答以下问题：

- 如果督察最喜欢的数为 $ j $，则在不超过 $ k $ 次更改的情况下，教师们可以通过更改树的类型来实现树行的最大美丽程度是多少？

## 输入格式

第一行包含一个整数 $ t $（$ 1 \le t \le 1000 $） — 测试用例的数量。

每个测试用例由一行组成，包含两个整数 $ n $ 和 $ k $（$ 1 \le n \le 3000 $，$ 0 \le k \le n $） — 行中树木的数量以及最大更改次数。

第二行包含长度为 $ n $ 的字符串 $ s $，由零和一组成 — 计划的描述。

保证所有测试用例中的所有 $ n $ 值的总和不超过 $ 3000 $。

## 输出格式

对于每个测试用例，输出 $ n $ 个整数，其中第 $ j $ 个整数（$ 1 \le j \le n $）是在使用 $ a = j $ 计算美丽程度后，教师们在不超过 $ k $ 次更改的情况下可以实现的树行的最大美丽程度。

## 样例 #1

### 样例输入 #1

```
5
3 0
111
4 1
0110
5 0
10000
6 2
101101
7 1
0001101
```

### 样例输出 #1

```
3 3 3 
4 5 7 9 
5 9 13 17 21 
6 9 13 17 21 25 
7 10 13 17 21 25 29
```

## 说明/提示

在第一个测试用例中，不允许进行任何更改，因此始终满足 $ l_0 = 0 $ 和 $ l_1 = 3 $。因此，不管 $ a $ 的值如何，树行的美丽程度都将是 $ 3 $。

在第二个测试用例中，对于 $ a \in \{1, 2\} $，教师们可以将计划 $ s $ 更改为 $ 0111 $（通过更改 $ s_4 $），对于 $ a \in \{3, 4\} $，他们可以将计划 $ s $ 更改为 $ 0010 $（通过更改 $ s_2 $）。在这种情况下，每个 $ a $ 的树行的美丽程度计算如下：

- 对于 $ a = 1 $：$ l_0 = 1 $，$ l_1 = 3 $。树行的美丽程度为 $ 1\cdot 1 + 3 = 4 $。
- 对于 $ a = 2 $：$ l_0 = 1 $，$ l_1 = 3 $。树行的美丽程度为 $ 2\cdot 1 + 3 = 5 $。
- 对于 $ a = 3 $：$ l_0 = 2 $，$ l_1 = 1 $。树行的美丽程度为 $ 3\cdot 2 + 1 = 7 $。
- 对于 $ a = 4 $：$ l_0 = 2 $，$ l_1 = 1 $。树行的美丽程度为 $ 4\cdot 2 + 1 = 9 $。

可以证明，上述更改对于所有 $ a $ 从 $ 1 $ 到 $ 4 $ 都是最优的。

## 样例 #1

### 输入

```
5
3 0
111
4 1
0110
5 0
10000
6 2
101101
7 1
0001101
```

### 输出

```
3 3 3 
4 5 7 9 
5 9 13 17 21 
6 9 13 17 21 25 
7 10 13 17 21 25 29
```



---

---
title: "Twin Friends"
layout: "post"
diff: 提高+/省选-
pid: CF1906H
tag: ['动态规划 DP', '组合数学']
---

# Twin Friends

## 题目描述

You meet two new friends who are twins. The name of the elder twin is $ A $ , which consists of $ N $ characters. While the name of the younger twin is $ B $ , which consists of $ M $ characters. It is known that $ N \leq M $ .

You want to call each of them with a nickname. For the elder twin, you want to pick any permutation of $ A $ as the nickname. For the younger twin, you want to remove exactly $ M - N $ characters from any permutation of $ B $ . Denote the nicknames of the elder twin and the younger twin as $ A' $ and $ B' $ , respectively.

You want the nicknames to satisfy the following requirement. For each $ i $ that satisfies $ 1 \leq i \leq N $ , $ B'_i $ must be equal to either $ A'_i $ or the next letter that follows alphabetically after $ A'_i $ (if such a next letter exists).

Determine the number of different pairs of nicknames $ (A', B') $ that satisfy the requirement. Two pairs of nicknames are considered different if at least one of the nicknames are different. As the result might be large, find the answer modulo $ 998\,244\,353 $ .

## 输入格式

The first line consists of two integers $ N $ $ M $ ( $ 1 \leq N \leq M \leq 200\,000 $ ).

The second line consists of a string $ A $ of length $ N $ .

The third line consists of a string $ B $ of length $ M $ .

All strings consist of only upper-case letters.

## 输出格式

Output a single integer representing number of different pairs $ (A', B') $ that satisfy the requirement, modulo $ 998\,244\,353 $ .

## 说明/提示

Explanation for the sample input/output #1

The $ 9 $ pairs are:

- (AAM, AAN),
- (AAM, ABN),
- (AAM, BAN),
- (AMA, ANA),
- (AMA, ANB),
- (AMA, BNA),
- (MAA, NAA),
- (MAA, NAB), and
- (MAA, NBA).

Explanation for the sample input/output #2

The $ 120 $ pairs are the pairs where $ A' $ is a permutation of BINUS and $ B' = A' $ .

## 样例 #1

### 输入

```
3 4
AMA
ANAB
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5 8
BINUS
BINANUSA
```

### 输出

```
120
```

## 样例 #3

### 输入

```
15 30
BINUSUNIVERSITY
BINANUSANTARAUNIVERSITYJAKARTA
```

### 输出

```
151362308
```

## 样例 #4

### 输入

```
4 4
UDIN
ASEP
```

### 输出

```
0
```



---

---
title: "Count BFS Graph"
layout: "post"
diff: 提高+/省选-
pid: CF1906J
tag: ['动态规划 DP', '组合数学']
---

# Count BFS Graph

## 题目描述

You are currently researching a graph traversal algorithm called the Breadth First Search (BFS). Suppose you have an input graph of $ N $ nodes (numbered from $ 1 $ to $ N $ ). The graph is represented by an adjacency matrix $ M $ , for which node $ u $ can traverse to node $ v $ if $ M_{u, v} $ is $ 1 $ , otherwise it is $ 0 $ . Your algorithm will output the order the nodes are visited in the BFS. The pseudocode of the algorithm is presented as follows.

```
<pre class="verbatim"><br></br>    BFS(M[1..N][1..N]):<br></br>        let A be an empty array<br></br>        let Q be an empty queue<br></br><br></br>        append 1 to A<br></br>        push 1 to Q<br></br><br></br>        while Q is not empty:<br></br>            pop the front element of Q into u<br></br>            for v = 1 to N:<br></br>                if M[u][v] == 1 and v is not in A:<br></br>                    append v to A<br></br>                    push v to Q<br></br><br></br>        return A<br></br>
```

During your research, you are interested in the following problem. Given an array $ A $ such that $ A $ is a permutation of $ 1 $ to $ N $ and $ A_1 = 1 $ . How many simple undirected graph with $ N $ nodes and adjacency matrix $ M $ such that $ \text{BFS}(M) = A $ ? Since the answer can be very large, calculate the answer modulo $ 998\,244\,353 $ .

A simple graph has no self-loop ( $ M_{i, i} = 0 $ for $ 1 \leq i \leq N $ ) and there is at most one edge that connects a pair of nodes. In an undirected graph, if node $ u $ is adjacent to node $ v $ , then node $ v $ is also adjacent to node $ u $ ; formally, $ M_{u, v} = M_{v, u} $ for $ 1 \leq u < v \leq N $ .

Two graphs are considered different if there is an edge that exists in one graph but not the other. In other words, two graphs are considered different if their adjacency matrices are different.

## 输入格式

The first line consists of an integer $ N $ ( $ 2 \leq N \leq 5000 $ ).

The second line consists of $ N $ integers $ A_i $ . The array $ A $ is a permutation of $ 1 $ to $ N $ and $ A_1 = 1 $ .

## 输出格式

Output an integer representing the number of simple undirected graphs with $ N $ nodes and adjacency matrix $ M $ such that $ \text{BFS}(M) = A $ . Since the answer can be very large, output the answer modulo $ 998\,244\,353 $ .

## 说明/提示

Explanation for the sample input/output #1

The following illustration shows all graphs that satisfy the requirements.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906J/96f1bd6a81238405d96653e941a6d0d3b2152525.png)Explanation for the sample input/output #2

The only graph that satisfies the requirements is a graph with two edges: one that connects nodes $ 1 $ and $ 3 $ , and another one that connects nodes $ 3 $ and $ 2 $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 3 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
1 3 2 4 5
```

### 输出

```
17
```

## 样例 #4

### 输入

```
11
1 2 3 4 5 6 7 8 9 10 11
```

### 输出

```
379394847
```



---

---
title: "Array Collapse"
layout: "post"
diff: 提高+/省选-
pid: CF1913D
tag: ['动态规划 DP']
---

# Array Collapse

## 题目描述

You are given an array $ [p_1, p_2, \dots, p_n] $ , where all elements are distinct.

You can perform several (possibly zero) operations with it. In one operation, you can choose a contiguous subsegment of $ p $ and remove all elements from that subsegment, except for the minimum element on that subsegment. For example, if $ p = [3, 1, 4, 7, 5, 2, 6] $ and you choose the subsegment from the $ 3 $ -rd element to the $ 6 $ -th element, the resulting array is $ [3, 1, 2, 6] $ .

An array $ a $ is called reachable if it can be obtained from $ p $ using several (maybe zero) aforementioned operations. Calculate the number of reachable arrays, and print it modulo $ 998244353 $ .

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of two lines. The first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ). The second line contains $ n $ distinct integers $ p_1, p_2, \dots, p_n $ ( $ 1 \le p_i \le 10^9 $ ).

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the number of reachable arrays, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
2
2 1
4
2 4 1 3
5
10 2 6 3 4
```

### 输出

```
2
6
12
```



---

---
title: "Counting Binary Strings"
layout: "post"
diff: 提高+/省选-
pid: CF1920E
tag: ['动态规划 DP']
---

# Counting Binary Strings

## 题目描述

Patrick calls a substring $ ^\dagger $ of a binary string $ ^\ddagger $ good if this substring contains exactly one 1.

Help Patrick count the number of binary strings $ s $ such that $ s $ contains exactly $ n $ good substrings and has no good substring of length strictly greater than $ k $ . Note that substrings are differentiated by their location in the string, so if $ s = $ 1010 you should count both occurrences of 10.

 $ ^\dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

 $ ^\ddagger $ A binary string is a string that only contains the characters 0 and 1.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2500 $ ) — the number of test cases. The description of the test cases follows.

The only line of each test case contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 2500 $ , $ 1 \leq k \leq n $ ) — the number of required good substrings and the maximum allowed length of a good substring.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2500 $ .

## 输出格式

For each test case, output a single integer — the number of binary strings $ s $ such that $ s $ contains exactly $ n $ good substrings and has no good substring of length strictly greater than $ k $ . Since this integer can be too large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the only suitable binary string is 1. String 01 is not suitable because it contains a substring 01 with length $ 2 > 1 $ .

In the second test case, suitable binary strings are 011, 110 and 111.

In the third test case, suitable binary strings are 101, 0110, 0111, 1110, and 1111.

## 样例 #1

### 输入

```
6
1 1
3 2
4 2
5 4
6 2
2450 2391
```

### 输出

```
1
3
5
12
9
259280854
```



---

---
title: "Paint Charges"
layout: "post"
diff: 提高+/省选-
pid: CF1927G
tag: ['动态规划 DP']
---

# Paint Charges

## 题目描述

A horizontal grid strip of $ n $ cells is given. In the $ i $ -th cell, there is a paint charge of size $ a_i $ . This charge can be:

- either used to the left — then all cells to the left at a distance less than $ a_i $ (from $ \max(i - a_i + 1, 1) $ to $ i $ inclusive) will be painted,
- or used to the right — then all cells to the right at a distance less than $ a_i $ (from $ i $ to $ \min(i + a_i - 1, n) $ inclusive) will be painted,
- or not used at all.

Note that a charge can be used no more than once (that is, it cannot be used simultaneously to the left and to the right). It is allowed for a cell to be painted more than once.

What is the minimum number of times a charge needs to be used to paint all the cells of the strip?

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases in the test. This is followed by descriptions of $ t $ test cases.

Each test case is specified by two lines. The first one contains an integer $ n $ ( $ 1 \le n \le 100 $ ) — the number of cells in the strip. The second line contains $ n $ positive integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ), where $ a_i $ is the size of the paint charge in the $ i $ -th cell from the left of the strip.

It is guaranteed that the sum of the values of $ n $ in the test does not exceed $ 1000 $ .

## 输出格式

For each test case, output the minimum number of times the charges need to be used to paint all the cells of the strip.

## 说明/提示

In the third test case of the example, it is sufficient to use the charge from the $ 1 $ -st cell to the right, then it will cover both cells $ 1 $ and $ 2 $ .

In the ninth test case of the example, you need to:

- use the charge from the $ 3 $ -rd cell to the left, covering cells from the $ 1 $ -st to the $ 3 $ -rd;
- use the charge from the $ 5 $ -th cell to the left, covering cells from the $ 4 $ -th to the $ 5 $ -th;
- use the charge from the $ 7 $ -th cell to the left, covering cells from the $ 6 $ -th to the $ 7 $ -th.

In the eleventh test case of the example, you need to:

- use the charge from the $ 5 $ -th cell to the right, covering cells from the $ 5 $ -th to the $ 10 $ -th;
- use the charge from the $ 7 $ -th cell to the left, covering cells from the $ 1 $ -st to the $ 7 $ -th.

## 样例 #1

### 输入

```
13
1
1
2
1 1
2
2 1
2
1 2
2
2 2
3
1 1 1
3
3 1 2
3
1 3 1
7
1 2 3 1 2 4 2
7
2 1 1 1 2 3 1
10
2 2 5 1 6 1 8 2 8 2
6
2 1 2 1 1 2
6
1 1 4 1 3 2
```

### 输出

```
1
2
1
1
1
3
1
2
3
4
2
3
3
```



---

---
title: "Modular Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF1928E
tag: ['动态规划 DP', '贪心']
---

# Modular Sequence

## 题目描述

You are given two integers $ x $ and $ y $ . A sequence $ a $ of length $ n $ is called modular if $ a_1=x $ , and for all $ 1 < i \le n $ the value of $ a_{i} $ is either $ a_{i-1} + y $ or $ a_{i-1} \bmod y $ . Here $ x \bmod y $ denotes the remainder from dividing $ x $ by $ y $ .

Determine if there exists a modular sequence of length $ n $ with the sum of its elements equal to $ S $ , and if it exists, find any such sequence.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ). The description of the test cases follows.

The first and only line of each test case contains four integers $ n $ , $ x $ , $ y $ , and $ s $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le x \le 2 \cdot 10^5 $ , $ 1 \le y \le 2 \cdot 10^5 $ , $ 0 \le s \le 2 \cdot 10^5 $ ) — the length of the sequence, the parameters $ x $ and $ y $ , and the required sum of the sequence elements.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ , and also the sum of $ s $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if the desired sequence exists, output "Yes" on the first line (without quotes). Then, on the second line, output $ n $ integers $ a_1, a_2, \ldots, a_n $ separated by a space — the elements of the sequence $ a $ . If there are multiple suitable sequences, output any of them.

If the sequence does not exist, output "No" on a single line.

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 说明/提示

In the first example, the sequence $ [8, 11, 2, 5, 2] $ satisfies the conditions. Thus, $ a_1 = 8 = x $ , $ a_2 = 11 = a_1 + 3 $ , $ a_3 = 2 = a_2 \bmod 3 $ , $ a_4 = 5 = a_3 + 3 $ , $ a_5 = 2 = a_4 \bmod 3 $ .

In the second example, the first element of the sequence should be equal to $ 5 $ , so the sequence $ [2, 2, 2] $ is not suitable.

## 样例 #1

### 输入

```
3
5 8 3 28
3 5 3 6
9 1 5 79
```

### 输出

```
YES
8 11 2 2 5 
NO
NO
```



---

---
title: "Sum over all Substrings (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1930D2
tag: ['动态规划 DP']
---

# Sum over all Substrings (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

For a binary $ ^\dagger $ pattern $ p $ and a binary string $ q $ , both of length $ m $ , $ q $ is called $ p $ -good if for every $ i $ ( $ 1 \leq i \leq m $ ), there exist indices $ l $ and $ r $ such that:

- $ 1 \leq l \leq i \leq r \leq m $ , and
- $ p_i $ is a mode $ ^\ddagger $ of the string $ q_l q_{l+1} \ldots q_{r} $ .

For a pattern $ p $ , let $ f(p) $ be the minimum possible number of $ \mathtt{1} $ s in a $ p $ -good binary string (of the same length as the pattern).

You are given a binary string $ s $ of size $ n $ . Find $ $$$\sum_{i=1}^{n} \sum_{j=i}^{n} f(s_i s_{i+1} \ldots s_j). $ $  In other words, you need to sum the values of  $ f $  over all  $ \\frac{n(n+1)}{2} $  substrings of  $ s $ .</p><p> $ ^\\dagger $  A binary <span class="tex-font-style-it">pattern</span> is a string that only consists of characters  $ \\mathtt{0} $  and  $ \\mathtt{1} $ .</p><p> $ ^\\ddagger $  Character  $ c $  is a mode of string  $ t $  of length  $ m $  if the number of occurrences of  $ c $  in  $ t $  is at least  $ \\lceil \\frac{m}{2} \\rceil $ . For example,  $ \\mathtt{0} $  is a mode of  $ \\mathtt{010} $ ,  $ \\mathtt{1} $  is not a mode of  $ \\mathtt{010} $ , and both  $ \\mathtt{0} $  and  $ \\mathtt{1} $  are modes of  $ \\mathtt{011010}$$$.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the length of the binary string $ s $ .

The second line of each test case contains a binary string $ s $ of length $ n $ consisting of only characters $ \mathtt{0} $ and $ \mathtt{1} $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output the sum of values of $ f $ over all substrings of $ s $ .

## 说明/提示

In the first test case, the only $ \mathtt{1} $ -good string is $ \mathtt{1} $ . Thus, $ f(\mathtt{1})=1 $ .

In the second test case, $ f(\mathtt{10})=1 $ because $ \mathtt{01} $ is $ \mathtt{10} $ -good, and $ \mathtt{00} $ is not $ \mathtt{10} $ -good. Thus, the answer is $ f(\mathtt{1})+f(\mathtt{10})+f(\mathtt{0}) = 1 + 1 + 0 = 2 $ .

In the third test case, $ f $ equals to $ 0 $ for all $ 1 \leq i \leq j \leq 5 $ . Thus, the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
1
1
2
10
5
00000
20
11110110000000111111
```

### 输出

```
1
2
0
346
```



---

---
title: "Learning to Paint"
layout: "post"
diff: 提高+/省选-
pid: CF1942D
tag: ['动态规划 DP', '堆']
---

# Learning to Paint

## 题目描述

[Pristine Beat - Touhou](https://soundcloud.com/jackaltroy/sets/primordial-beat-pristine-beat)

⠀



Elsie is learning how to paint. She has a canvas of $ n $ cells numbered from $ 1 $ to $ n $ and can paint any (potentially empty) subset of cells.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942D/3277b406102b440ccbe0c485777db99ec89618eb.png)Elsie has a 2D array $ a $ which she will use to evaluate paintings. Let the maximal contiguous intervals of painted cells in a painting be $ [l_1,r_1],[l_2,r_2],\ldots,[l_x,r_x] $ . The beauty of the painting is the sum of $ a_{l_i,r_i} $ over all $ 1 \le i \le x $ . In the image above, the maximal contiguous intervals of painted cells are $ [2,4],[6,6],[8,9] $ and the beauty of the painting is $ a_{2,4}+a_{6,6}+a_{8,9} $ .

There are $ 2^n $ ways to paint the strip. Help Elsie find the $ k $ largest possible values of the beauty of a painting she can obtain, among all these ways. Note that these $ k $ values do not necessarily have to be distinct. It is guaranteed that there are at least $ k $ different ways to paint the canvas.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

The first line of each test case contains $ 2 $ integers $ n $ and $ k $ ( $ 1 \leq n \leq 10^3 $ , $ 1 \leq k \leq \min(2^n, 5 \cdot 10^3) $ ) — the number of cells and the number of largest values of the beauty of a painting you must find.

The next $ n $ lines of each test case describe $ a $ where the $ i $ -th of which contains $ n-i+1 $ integers $ a_{i,i},a_{i,i+1},\ldots,a_{i,n} $ ( $ -10^6 \leq a_{i,j} \leq 10^6 $ ).

It is guaranteed the sum of $ n $ over all test cases does not exceed $ 10^3 $ and the sum of $ k $ over all test cases does not exceed $ 5 \cdot 10^3 $ .

## 输出格式

For each test case, output $ k $ integers in one line: the $ i $ -th of them must represent the $ i $ -th largest value of the beauty of a painting Elsie can obtain.

## 说明/提示

In the first test case, Elsie can either paint the only cell or not paint it. If she paints the only cell, the beauty of the painting is $ -5 $ . If she chooses not to paint it, the beauty of the painting is $ 0 $ . Thus, the largest beauty she can obtain is $ 0 $ and the second largest beauty she can obtain is $ -5 $ .

Below is an illustration of the third test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942D/3d3d08bddad77d78ec4518a724cf3c2c6ce9ab10.png)

## 样例 #1

### 输入

```
4
1 2
-5
2 4
2 -3
-1
3 8
2 4 3
1 3
5
6 20
0 -6 -3 0 -6 -2
-7 -5 -2 -3 -4
7 0 -9 -4
2 -1 1
1 -2
-6
```

### 输出

```
0 -5 
2 0 -1 -3 
7 5 4 3 3 2 1 0 
8 8 7 7 5 5 2 2 1 1 1 1 1 1 0 0 0 0 0 -1
```



---

---
title: "The Most Reckless Defense"
layout: "post"
diff: 提高+/省选-
pid: CF1955H
tag: ['动态规划 DP', '状态合并']
---

# The Most Reckless Defense

## 题目描述

You are playing a very popular Tower Defense game called "Runnerfield 2". In this game, the player sets up defensive towers that attack enemies moving from a certain starting point to the player's base.

You are given a grid of size $ n \times m $ , on which $ k $ towers are already placed and a path is laid out through which enemies will move. The cell at the intersection of the $ x $ -th row and the $ y $ -th column is denoted as $ (x, y) $ .

Each second, a tower deals $ p_i $ units of damage to all enemies within its range. For example, if an enemy is located at cell $ (x, y) $ and a tower is at $ (x_i, y_i) $ with a range of $ r $ , then the enemy will take damage of $ p_i $ if $ (x - x_i) ^ 2 + (y - y_i) ^ 2 \le r ^ 2 $ .

Enemies move from cell $ (1, 1) $ to cell $ (n, m) $ , visiting each cell of the path exactly once. An enemy instantly moves to an adjacent cell horizontally or vertically, but before doing so, it spends one second in the current cell. If its health becomes zero or less during this second, the enemy can no longer move. The player loses if an enemy reaches cell $ (n, m) $ and can make one more move.

By default, all towers have a zero range, but the player can set a tower's range to an integer $ r $ ( $ r > 0 $ ), in which case the health of all enemies will increase by $ 3^r $ . However, each $ r $ can only be used for at most one tower.

Suppose an enemy has a base health of $ h $ units. If the tower ranges are $ 2 $ , $ 4 $ , and $ 5 $ , then the enemy's health at the start of the path will be $ h + 3 ^ 2 + 3 ^ 4 + 3 ^ 5 = h + 9 + 81 + 243 = h + 333 $ . The choice of ranges is made once before the appearance of enemies and cannot be changed after the game starts.

Find the maximum amount of base health $ h $ for which it is possible to set the ranges so that the player does not lose when an enemy with health $ h $ passes through (without considering the additions for tower ranges).

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 2 \le n, m \le 50, 1 \le k < n \cdot m $ ) — the dimensions of the field and the number of towers on it.

The next $ n $ lines each contain $ m $ characters — the description of each row of the field, where the character "." denotes an empty cell, and the character "#" denotes a path cell that the enemies will pass through.

Then follow $ k $ lines — the description of the towers. Each line of description contains three integers $ x_i $ , $ y_i $ , and $ p_i $ ( $ 1 \le x_i \le n, 1 \le y_i \le m, 1 \le p_i \le 500 $ ) — the coordinates of the tower and its attack parameter. All coordinates correspond to empty cells on the game field, and all pairs $ (x_i, y_i) $ are pairwise distinct.

It is guaranteed that the sum of $ n \cdot m $ does not exceed $ 2500 $ for all test cases.

## 输出格式

For each test case, output the maximum amount of base health $ h $ on a separate line, for which it is possible to set the ranges so that the player does not lose when an enemy with health $ h $ passes through (without considering the additions for tower ranges).

If it is impossible to choose ranges even for an enemy with $ 1 $ unit of base health, output "0".

## 说明/提示

In the first example, there is no point in increasing the tower range, as it will not be able to deal enough damage to the monster even with $ 1 $ unit of health.

In the second example, the tower has a range of $ 1 $ , and it deals damage to the monster in cells $ (1, 1) $ and $ (2, 2) $ .

In the third example, the tower has a range of $ 2 $ , and it deals damage to the monster in all path cells. If the enemy's base health is $ 1491 $ , then after the addition for the tower range, its health will be $ 1491 + 3 ^ 2 = 1500 $ , which exactly equals the damage the tower will deal to it in three seconds.

In the fourth example, the tower at $ (1, 2) $ has a range of $ 1 $ , and the tower at $ (3, 1) $ has a range of $ 2 $ .

## 样例 #1

### 输入

```
6
2 2 1
#.
##
1 2 1
2 2 1
#.
##
1 2 2
2 2 1
#.
##
1 2 500
3 3 2
#..
##.
.##
1 2 4
3 1 3
3 5 2
#.###
#.#.#
###.#
2 2 2
2 4 2
5 5 4
#....
#....
#....
#....
#####
3 2 142
4 5 9
2 5 79
1 3 50
```

### 输出

```
0
1
1491
11
8
1797
```



---

---
title: "Nene and the Mex Operator"
layout: "post"
diff: 提高+/省选-
pid: CF1956D
tag: ['动态规划 DP', '构造']
---

# Nene and the Mex Operator

## 题目描述

Nene gave you an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ .

You can perform the following operation no more than $ 5\cdot 10^5 $ times (possibly zero):

- Choose two integers $ l $ and $ r $ such that $ 1 \le l \le r \le n $ , compute $ x $ as $ \operatorname{MEX}(\{a_l, a_{l+1}, \ldots, a_r\}) $ , and simultaneously set $ a_l:=x, a_{l+1}:=x, \ldots, a_r:=x $ .

Here, $ \operatorname{MEX} $ of a set of integers $ \{c_1, c_2, \ldots, c_k\} $ is defined as the smallest non-negative integer $ m $ which does not occur in the set $ c $ .

Your goal is to maximize the sum of the elements of the array $ a $ . Find the maximum sum and construct a sequence of operations that achieves this sum. Note that you don't need to minimize the number of operations in this sequence, you only should use no more than $ 5\cdot 10^5 $ operations in your solution.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 18 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 0\leq a_i \leq 10^7 $ ) — the array $ a $ .

## 输出格式

In the first line, output two integers $ s $ and $ m $ ( $ 0\le m\le 5\cdot 10^5 $ ) — the maximum sum of elements of the array $ a $ and the number of operations in your solution.

In the $ i $ -th of the following $ m $ lines, output two integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ), representing the parameters of the $ i $ -th operation.

It can be shown that the maximum sum of elements of the array $ a $ can always be obtained in no more than $ 5 \cdot 10^5 $ operations.

## 说明/提示

In the first example, after the operation with $ l=1 $ and $ r=2 $ the array $ a $ becomes equal to $ [2,2] $ . It can be shown that it is impossible to achieve a larger sum of the elements of $ a $ , so the answer is $ 4 $ .

In the second example, the initial sum of elements is $ 13 $ which can be shown to be the largest.

In the third example, the array $ a $ changes as follows:

- after the first operation ( $ l=3 $ , $ r=3 $ ), the array $ a $ becomes equal to $ [1,100,0,1] $ ;
- after the second operation ( $ l=3 $ , $ r=4 $ ), the array $ a $ becomes equal to $ [1,100,2,2] $ .

It can be shown that it is impossible to achieve a larger sum of the elements of $ a $ , so the answer is $ 105 $ .

## 样例 #1

### 输入

```
2
0 1
```

### 输出

```
4 1
1 2
```

## 样例 #2

### 输入

```
3
1 3 9
```

### 输出

```
13 0
```

## 样例 #3

### 输入

```
4
1 100 2 1
```

### 输出

```
105 2
3 3
3 4
```

## 样例 #4

### 输入

```
1
0
```

### 输出

```
1 1
1 1
```



---

---
title: "Reconstruction"
layout: "post"
diff: 提高+/省选-
pid: CF1984F
tag: ['动态规划 DP', '枚举']
---

# Reconstruction

## 题目描述

There is a hidden array $ a_1, a_2, \ldots, a_n $ of length $ n $ whose elements are integers between $ -m $ and $ m $ , inclusive.

You are given an array $ b_1, b_2, \ldots, b_n $ of length $ n $ and a string $ s $ of length $ n $ consisting of the characters $ \texttt{P} $ , $ \texttt{S} $ , and $ \texttt{?} $ .

For each $ i $ from $ 1 $ to $ n $ inclusive, we must have:

- If $ s_i = \texttt{P} $ , $ b_i $ is the sum of $ a_1 $ through $ a_i $ .
- If $ s_i = \texttt{S} $ , $ b_i $ is the sum of $ a_i $ through $ a_n $ .

Output the number of ways to replace all $ \texttt{?} $ in $ s $ with either $ \texttt{P} $ or $ \texttt{S} $ such that there exists an array $ a_1, a_2, \ldots, a_n $ with elements not exceeding $ m $ by absolute value satisfying the constraints given by the array $ b_1, b_2, \ldots, b_n $ and the string $ s $ .

Since the answer may be large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 2 \cdot 10^3 $ , $ 2 \leq m \leq 10^{9} $ ) — the length of the hidden array $ a_1, a_2, \ldots, a_n $ and the maximum absolute value of an element $ a_i $ .

The second line of each test case contains a string $ s $ of length $ n $ consisting of characters $ \texttt{P} $ , $ \texttt{S} $ , and $ \texttt{?} $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ |b_i| \leq m \cdot n $ ).

The sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^3 $ .

## 输出格式

For each test case, output a single integer — the number of ways to replace all $ \texttt{?} $ in $ s $ with either $ \texttt{P} $ or $ \texttt{S} $ that result in the existence of a valid array $ a_1, a_2, \ldots, a_n $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, we can see that the following array satisfies all constraints, thus the answer is $ 1 $ :

1. $ \texttt{P} $ — $ {[\color{red}{\textbf{1}},3,4,2]} $ : sum of $ 1 $ .
2. $ \texttt{S} $ — $ {[1,\color{red}{\textbf{3},4,2}]} $ : sum of $ 9 $ .
3. $ \texttt{P} $ — $ {[\color{red}{1,3,\textbf{4}},2]} $ : sum of $ 8 $ .
4. $ \texttt{P} $ — $ {[\color{red}{1,3,4,\textbf{2}}]} $ : sum of $ 10 $ .

In the second test case, it can be shown that no array $ a $ with all $ |a_i| \leq m = 10^9 $ satisfies all constraints.

## 样例 #1

### 输入

```
6
4 10
PSPP
1 9 8 10
4 1000000000
????
1 1 1 4000000000
8 1000000000
?P?SSP?P
-857095623 -1424391899 -851974476 673437144 471253851 -543483033 364945701 -178537332
4 7
PPSS
4 2 1 3
9 20
?????????
1 2 3 4 5 6 7 8 9
3 1000000000
P??
-145463248 -974068460 -1287458396
```

### 输出

```
1
0
2
1
14
1
```



---

---
title: "Distance to Different"
layout: "post"
diff: 提高+/省选-
pid: CF1989E
tag: ['动态规划 DP']
---

# Distance to Different

## 题目描述

Consider an array $ a $ of $ n $ integers, where every element is from $ 1 $ to $ k $ , and every integer from $ 1 $ to $ k $ appears at least once.

Let the array $ b $ be constructed as follows: for the $ i $ -th element of $ a $ , $ b_i $ is the distance to the closest element in $ a $ which is not equal to $ a_i $ . In other words, $ b_i = \min \limits_{j \in [1, n], a_j \ne a_i} |i - j| $ .

For example, if $ a = [1, 1, 2, 3, 3, 3, 3, 1] $ , then $ b = [2, 1, 1, 1, 2, 2, 1, 1] $ .

Calculate the number of different arrays $ b $ you can obtain if you consider all possible arrays $ a $ , and print it modulo $ 998244353 $ .

## 输入格式

The only line of the input contains two integers $ n $ and $ k $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ 2 \le k \le \min(n, 10) $ ).

## 输出格式

Print one integer — the number of different arrays $ b $ you can obtain, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6 2
```

### 输出

```
20
```

## 样例 #4

### 输入

```
6 5
```

### 输出

```
3
```

## 样例 #5

### 输入

```
133 7
```

### 输出

```
336975971
```



---

---
title: "Med-imize"
layout: "post"
diff: 提高+/省选-
pid: CF1993D
tag: ['动态规划 DP', '二分']
---

# Med-imize

## 题目描述

Given two positive integers $ n $ and $ k $ , and another array $ a $ of $ n $ integers.

In one operation, you can select any subarray of size $ k $ of $ a $ , then remove it from the array without changing the order of other elements. More formally, let $ (l, r) $ be an operation on subarray $ a_l, a_{l+1}, \ldots, a_r $ such that $ r-l+1=k $ , then performing this operation means replacing $ a $ with $ [a_1, \ldots, a_{l-1}, a_{r+1}, \ldots, a_n] $ .

For example, if $ a=[1,2,3,4,5] $ and we perform operation $ (3,5) $ on this array, it will become $ a=[1,2] $ . Moreover, operation $ (2, 4) $ results in $ a=[1,5] $ , and operation $ (1,3) $ results in $ a=[4,5] $ .

You have to repeat the operation while the length of $ a $ is greater than $ k $ (which means $ |a| \gt k $ ). What is the largest possible median $ ^\dagger $ of all remaining elements of the array $ a $ after the process?

 $ ^\dagger $ The median of an array of length $ n $ is the element whose index is $ \left \lfloor (n+1)/2 \right \rfloor $ after we sort the elements in non-decreasing order. For example: $ median([2,1,5,4,3]) = 3 $ , $ median([5]) = 5 $ , and $ median([6,8,2,4]) = 4 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 5 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the largest median possible after performing the operations.

## 说明/提示

In the first test case, you can select a subarray $ (l, r) $ which can be either $ (1, 3) $ or $ (2, 4) $ . Thus, two obtainable final arrays are $ [3] $ and $ [2] $ . The former one has the larger median ( $ 3 > 2 $ ) so the answer is $ 3 $ .

In the second test case, three obtainable final arrays are $ [6, 4] $ , $ [3, 4] $ , and $ [3, 2] $ . Their medians are $ 4 $ , $ 3 $ , and $ 2 $ respectively. The answer is $ 4 $ .

In the third test case, only one element is left in the final array and it can be any element of the initial array. The largest one among them is $ 9 $ , so the answer is $ 9 $ .

## 样例 #1

### 输入

```
5
4 3
3 9 9 2
5 3
3 2 5 6 4
7 1
5 9 2 6 5 4 6
8 2
7 1 2 6 8 3 4 5
4 5
3 4 5 6
```

### 输出

```
3
4
9
6
4
```



---

---
title: "Minecraft"
layout: "post"
diff: 提高+/省选-
pid: CF1994G
tag: ['动态规划 DP']
---

# Minecraft

## 题目描述

### 题意翻译


在赢得一场紧张的 Bed Wars 起床战争游戏后, Masha 和 Olya 想放松一下, Masha 给了 Olya 一个长度为 $n$ 的数组 $a$ 和一个数字 $s$ 。现在请帮助Olya找到一个非负整数 $x$ ，使得 $ \displaystyle\sum_{i=1}^{n} a_i \oplus x = s \ $ ($ \oplus $表示异或运算)。但是这个任务对他们来说似乎太简单了，所以他们决定把数字变大并以长度为$ k $的二进制形式表示。

## 输入格式

每个测试都由多个测试用例组成。第一行包含一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) 表示测试用例的数量。
 
 每个测试用例的第一行包含两个整数 $ n $ 和 $ k $ ( $ 1 \le n, k, n \cdot k \le 2 \cdot 10^6 $ ) , $ n $ 为数组 $ a $ 的长度，$ k $ 为所有数字二进制形式的长度。
 
 第二行包含一个长度为 $ k $ 并由 $ 0 $ 和 $ 1 $ 组成的字符串，表示数字 $ s $ 的二进制形式，从最高位开始。
 
 接下来 $ n $ 行每行还包含长度为 $ k $ 并由 $ 0 $ 和 $ 1 $ 组成的字符串，表示数字 $ a_i $ 的二进制形式，从最高位开始。
 
 保证所有测试用例的 $ n \cdot k $ 之和不超过 $ 2⋅10^6 $。

## 输出格式

‭‌‭‏⁫‮⁯⁨⁣⁨⁩‬‍‌⁥‬⁤⁮⁫⁫⁤‍⁦⁦⁭‪⁮⁨⁯‍‮⁥⁪⁩⁮⁨‎​⁮⁦⁮‌⁩⁪‬⁮⁬‭ 
对于每个测试用例，输出一行长度为 $ k $ 的字符串，该字符串由 $ 0 $ 和 $ 1 $ 组成， 表示任意一个合适的数字 $ x $ ( $ x \ge 0 $ ) 的二进制形式, 从最高位开始。 如果不存在合适的 $ x $ 则输出 $ −1 $ 。


### 样例解释

 在第一个测试用例中, $ s = 11, a = [14, 6, 12, 15] $ , 如果 $ x = 14 $ , 则 $ \displaystyle\sum_{i=1}^{n} a_i \oplus x = (14 \oplus 14) + (6 \oplus 14) + (12 \oplus 14) + (15 \oplus 14) = 0 + 8 + 2 + 1 = 11 = s $ .

在第二个测试用例中, $ s = 41, a = [191, 158] $ , 如果 $ x = 154 $ , 则 $ \displaystyle\sum_{i=1}^{n} a_i \oplus x = (191 \oplus 154) + (158 \oplus 154) = 37 + 4 = 41 = s $ .

## 样例 #1

### 输入

```
4
4 5
01011
01110
00110
01100
01111
2 8
00101001
10111111
10011110
5 4
0101
0010
0000
0000
0010
0011
6 5
00011
10110
11001
01010
11100
10011
10000
```

### 输出

```
01110
10011010
0010
-1
```



---

---
title: "Checkout Assistant"
layout: "post"
diff: 提高+/省选-
pid: CF19B
tag: ['动态规划 DP', '背包 DP']
---

# Checkout Assistant

## 题目描述

Bob 来到一家现购自运商店，将 $n$ 件商品放入了他的手推车，然后到收银台付款。每件商品由它的价格 $c_i$ 和收银员扫描它的时间 $t_i$ 秒定义。

当收银员正在扫描某件商品时，Bob 可以从他的手推车中偷走某些其它商品。Bob 需要恰好 $1$ 秒来偷走一件商品。Bob 需要付给收银员的最少钱数是多少？请记住，收银员扫描商品的顺序由 Bob 决定。

## 输入格式

输入第一行包含数 $n$（$1 \le n \le 2000$）。接下来 $n$ 行每行每件商品由一对数 $t_i$，$c_i$（$0 \le t_i \le 2000$，$1 \le c_i \le 10^9$）描述。如果 $t_i$ 是 $0$，那么当收银员扫描商品 $i$ 时，Bob 不能偷任何东西。

## 输出格式

输出一个数字—— Bob 需要支付的最小金额是多少。

## 样例 #1

### 输入

```
4
2 10
0 20
1 5
1 3

```

### 输出

```
8

```

## 样例 #2

### 输入

```
3
0 1
0 10
0 100

```

### 输出

```
111

```



---

---
title: "Cosmic Rays"
layout: "post"
diff: 提高+/省选-
pid: CF2002E
tag: ['动态规划 DP', '单调栈']
---

# Cosmic Rays

## 题目描述

Given an array of integers $ s_1, s_2, \ldots, s_l $ , every second, cosmic rays will cause all $ s_i $ such that $ i=1 $ or $ s_i\neq s_{i-1} $ to be deleted simultaneously, and the remaining parts will be concatenated together in order to form the new array $ s_1, s_2, \ldots, s_{l'} $ .

Define the strength of an array as the number of seconds it takes to become empty.

You are given an array of integers compressed in the form of $ n $ pairs that describe the array left to right. Each pair $ (a_i,b_i) $ represents $ a_i $ copies of $ b_i $ , i.e. $ \underbrace{b_i,b_i,\cdots,b_i}_{a_i\textrm{ times}} $ .

For each $ i=1,2,\dots,n $ , please find the strength of the sequence described by the first $ i $ pairs.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\le t\le10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le3\cdot10^5 $ ) — the length of sequence $ a $ .

The next $ n $ lines contain two integers each $ a_i $ , $ b_i $ ( $ 1\le a_i\le10^9,0\le b_i\le n $ ) — the pairs which describe the sequence.

It is guaranteed that the sum of all $ n $ does not exceed $ 3\cdot10^5 $ .

It is guaranteed that for all $ 1\le i<n $ , $ b_i\neq b_{i+1} $ holds.

## 输出格式

For each test case, print one line containing $ n $ integers — the answer for each prefix of pairs.

## 说明/提示

In the first test case, for the prefix of length $ 4 $ , the changes will be $ [0,0,1,0,0,0,1,1,1,1,1]\rightarrow[0,0,0,1,1,1,1]\rightarrow[0,0,1,1,1]\rightarrow[0,1,1]\rightarrow[1]\rightarrow[] $ , so the array becomes empty after $ 5 $ seconds.

In the second test case, for the prefix of length $ 4 $ , the changes will be $ [6,6,6,6,3,6,6,6,6,0,0,0,0]\rightarrow[6,6,6,6,6,6,0,0,0]\rightarrow[6,6,6,6,6,0,0]\rightarrow[6,6,6,6,0]\rightarrow[6,6,6]\rightarrow[6,6]\rightarrow[6]\rightarrow[] $ , so the array becomes empty after $ 7 $ seconds.

## 样例 #1

### 输入

```
4
4
2 0
1 1
3 0
5 1
6
4 6
1 3
4 6
4 0
7 6
6 3
7
9 0
7 1
5 0
7 1
9 0
1 1
2 0
10
10 7
4 9
2 2
7 9
2 8
8 5
11 7
15 5
12 7
4 0
```

### 输出

```
2 2 4 5 
4 4 7 7 10 10 
9 9 9 9 9 9 10 
10 10 10 10 10 10 12 15 15 15
```



---

---
title: "Turtle and Inversions (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2003E1
tag: ['动态规划 DP']
---

# Turtle and Inversions (Easy Version)

## 题目描述

这是题目的简化版本。这两种题目的区别在于对于 $m$ 的限制及在简化版本中，满足 $r_i < l_{i + 1}$ 对于每个 $i$ 从 $1$ 到 $m-1$。只有当两个版本的问题都被解决后，才可以进行 hack。

海龟给了你 $m$ 个区间 $[l_1, r_1], [l_2, r_2], \ldots, [l_m, r_m]$。他认为一个排列 $p$ 是有趣的，如果对于每个区间存在一个整数 $k_i$ 满足 $l_i \le k_i < r_i$，那么对于每个从 $1$ 到 $m$ 的整数 $i$，可以计算出 $a_i = \max\limits_{j = l_i}^{k_i} p_j$ 和 $b_i = \min\limits_{j = k_i + 1}^{r_i} p_j$，使得以下条件成立：

$$
\max\limits_{i = 1}^m a_i < \min\limits_{i = 1}^m b_i
$$

海龟希望你计算出长度为 $n$ 的所有有趣排列中能获得的最大逆序对数量，或者告诉他是否没有这样的有趣排列。

排列 $p$ 的逆序对是指任意两个整数对 $(i, j)$（$1 \le i < j \le n$）且满足 $p_i > p_j$。

## 输入格式

每组数据包含多个测试用例。第一行是测试用例的数量 $t$（$1 \le t \le 10^3$）。每个测试用例的描述如下。

对于每个测试用例，第一行有两个整数 $n, m$（$2 \le n \le 5 \cdot 10^3, 0 \le m \le \frac{n}{2}$），分别表示排列的长度和区间的数量。

接下来的 $m$ 行，每行包含两个整数 $l_i, r_i$（$1 \le l_i < r_i \le n$），表示第 $i$ 个区间。

注意：本版本输入确保 $r_i < l_{i + 1}$ 对于每个从 $1$ 到 $m-1$ 的 $i$。

所有测试用例中 $n$ 的总和不超过 $5 \cdot 10^3$。

## 输出格式

对于每个测试用例，如果没有有趣的排列，输出 $-1$。否则，输出一个整数，表示最大逆序对的数量。

## 说明/提示

在第三个测试用例中，最大逆序对数量的有趣排列是 $[5, 2, 4, 3, 1]$。

在第四个测试用例中，最大逆序对数量的有趣排列是 $[4, 8, 7, 6, 3, 2, 1, 5]$。这时可以设定 $[k_1, k_2] = [1, 7]$。

在第五个测试用例中，最大逆序对数量的有趣排列是 $[4, 7, 6, 3, 2, 1, 5]$。

在第六个测试用例中，最大逆序对数量的有趣排列是 $[4, 7, 3, 6, 2, 5, 1]$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
2 0
2 1
1 2
5 1
2 4
8 2
1 4
6 8
7 2
1 3
4 7
7 3
1 2
3 4
5 6
```

### 输出

```
1
0
8
21
15
15
```



---

---
title: "Turtle and Inversions (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2003E2
tag: ['动态规划 DP']
---

# Turtle and Inversions (Hard Version)

## 题目描述

这是一个问题的困难版本。这个困难版本与简单版本在 $m$ 的限制条件上有所不同，而且在简单版本中，对于每一个 $i$（从 $1$ 到 $m-1$），都有 $r_i < l_{i+1}$ 的条件。只有当两个版本的问题都解决后，你才可以进行 hack。

有 $m$ 个区间 $[l_1, r_1], [l_2, r_2], \ldots, [l_m, r_m]$，海龟认为一个排列 $p$ 是有趣的，如果对每个区间 $l_i \le k_i < r_i$，存在一个整数 $k_i$，并且对于每个 $i$ 从 $1$ 到 $m$，满足以下条件：

设 $a_i = \max\limits_{j = l_i}^{k_i} p_j$，$b_i = \min\limits_{j = k_i + 1}^{r_i} p_j$，需满足：

$$
\max\limits_{i = 1}^m a_i < \min\limits_{i = 1}^m b_i
$$

海龟希望你找出长度为 $n$ 的所有可能的有趣排列中，逆序对数量的最大值。如果没有这样一个有趣的排列，则返回 $-1$。

排列 $p$ 中的逆序对是指满足 $p_i > p_j$ 的整数对 $(i, j)$，其中 $1 \le i < j \le n$。

## 输入格式

输入数据包含多个测试用例。第一行给出测试用例数量 $t$（$1 \le t \le 10^3$）。接下来是每个测试用例的详细描述。

每个测试用例第一行包含两个整数 $n$ 和 $m$（$2 \le n \le 5 \cdot 10^3$, $0 \le m \le 5 \cdot 10^3$），分别表示排列的长度和区间的数量。

接下来的 $m$ 行每行两个整数 $l_i, r_i$（$1 \le l_i < r_i \le n$），表示第 $i$ 个区间。需要注意的是，可能会有相同的区间（即存在不同的 $i, j$ 使得 $l_i = l_j$ 且 $r_i = r_j$）。

保证所有测试用例中 $n$ 的总和不超过 $5 \cdot 10^3$，$m$ 的总和不超过 $5 \cdot 10^3$。

## 输出格式

对于每个测试用例，如果不存在有趣的排列，输出单一整数 $-1$；否则，输出最大可能逆序对的数量。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
8
2 0
2 1
1 2
5 1
2 4
8 3
1 4
2 5
7 8
7 2
1 4
4 7
7 3
1 2
1 7
3 7
7 4
1 3
4 7
1 3
4 7
7 3
1 2
3 4
5 6
```

### 输出

```
1
0
8
18
-1
-1
15
15
```



---

---
title: "Subtangle Game (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2005E2
tag: ['动态规划 DP']
---

# Subtangle Game (Hard Version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are the constraints on all the variables. You can make hacks only if both versions of the problem are solved.

Tsovak and Narek are playing a game. They have an array $ a $ and a matrix $ b $ of integers with $ n $ rows and $ m $ columns, numbered from $ 1 $ . The cell in the $ i $ -th row and the $ j $ -th column is $ (i, j) $ .

They are looking for the elements of $ a $ in turns; Tsovak starts first. Each time a player looks for a cell in the matrix containing the current element of $ a $ (Tsovak looks for the first, then Narek looks for the second, etc.). Let's say a player has chosen the cell $ (r, c) $ . The next player has to choose his cell in the submatrix starting at $ (r + 1, c + 1) $ and ending in $ (n, m) $ (the submatrix can be empty if $ r=n $ or $ c=m $ ). If a player cannot find such a cell (or the remaining submatrix is empty) or the array ends (the previous player has chosen the last element), then he loses.

Your task is to determine the winner if the players play optimally.

Note: since the input is large, you may need to optimize input/output for this problem.

For example, in C++, it is enough to use the following lines at the start of the main() function:

```
<pre class="lstlisting">```
int main() {<br></br>    ios_base::sync_with_stdio(false);<br></br>    cin.tie(NULL); cout.tie(NULL);<br></br>}<br></br>
```
```

## 输入格式

The first line of the input contains $ t $ ( $ 1 \le t \le 1500 $ ) – the number of test cases.

The first line of each test case contains three integers $ l $ , $ n $ , and $ m $ ( $ 1 \le l, n, m \le 1500 $ ) – the size of the array and the sizes of the matrix.

The second line contains $ l $ integers $ a_1, a_2, a_3, \ldots a_l $ ( $ 1 \le a_i \le n \cdot m $ ) – the elements of the array $ a $ .

The $ i $ -th of the last $ n $ lines contains $ m $ integers $ b_{i,1}, b_{i,2}, b_{i,3}, \ldots b_{i,m} $ ( $ 1 \le b_{i,j} \le n \cdot m $ ) – representing the $ i $ -th row of the matrix.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 3 \cdot 10^6 $ .

It is guaranteed that the sum of $ l $ over all test cases does not exceed $ 1500 $ .

## 输出格式

You should output $ t $ lines, the $ i $ -th of them containing a character representing the answer of the $ i $ -th test case: "T" if Tsovak wins or "N", otherwise (without quotes).

## 说明/提示

In the first example, Tsovak starts by looking for $ 1 $ . There is only one occurrence of $ 1 $ at $ (1,1) $ , so he chooses it. Then Narek needs to look for $ 2 $ in the submatrix of $ (2, 2) $ , which consists of just the last two elements: $ 6 $ and $ 2 $ . He chooses $ 2 $ , and then Tsovak loses since the array has ended.

In the second example, Tsovak needs to choose $ 1 $ . There is a $ 1 $ at the cell $ (n,m) $ , so he chooses that cell. Then, since the submatrix of $ (n + 1, m + 1) $ is empty, Narek cannot find $ 2 $ , so he loses.

## 样例 #1

### 输入

```
3
2 2 3
1 2
1 3 6
4 6 2
2 2 4
1 2
1 1 3 2
4 2 5 1
2 4 2
1 2
3 4
5 6
7 8
8 8
```

### 输出

```
N
T
N
```



---

---
title: "Max Plus Min Plus Size"
layout: "post"
diff: 提高+/省选-
pid: CF2018D
tag: ['动态规划 DP', '线段树', '并查集']
---

# Max Plus Min Plus Size

## 题目描述

[EnV - 尘龙酒馆](https://soundcloud.com/envyofficial/env-the-dusty-dragon-tavern)

----------------
给定一个由正整数组成的数组 $a_1, a_2, \ldots, a_n$ 。

你可以将数组中的一些元素涂成红色，但不能有两个相邻的红色元素（即对于 $1 \leq i \leq n-1$ 来说， $a_i$ 和 $a_{i+1}$ 中至少有一个元素不能是红色的）。

您的得分是红色元素的最大值加上红色元素的最小值，再加上红色元素的数量。请找出您能得到的最高分。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 10^4$ )。对每个测试用例输入如下：

每个测试用例的第一行都包含一个整数 $n$ ( $1 \le n \le 2 \cdot 10^5$ ) ，表示数组的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ( $1 \le a_i \le 10^9$ ) 表示给定的数组。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每个测试用例，输出一个整数：根据题意将某些元素染成红色后可能得到的最大分数。

**样例解释**

在第一个测试用例中，可以对数组着色如下： $[\color{red}{5}\color{black}, 4, \color{red}{5} \color{black}]$ .您的得分是 $\max([5, 5]) + \min([5, 5]) + \text{size}([5, 5]) = 5+5+2 = 12$ 。这是你能得到的最高分。

在第二个测试案例中，您可以对数组着色如下： $[4, \color{red}{5},\color{black} 4]$ .您的得分是 $\max([5]) + \min([5]) + \text{size}([5]) = 5+5+1 = 11$ 。这是你能得到的最高分。

在第三个测试案例中，您可以对数组着色如下： $[\color{red}{3}\color{black}, 3, \color{red}{3} \color{black},3, \color{red}{4}\color{black}, 1, 2, \color{red}{3}, \color{black}5, \color{red}{4} \color{black}]$ .您的得分是 $\max([3, 3, 4, 3, 4]) + \min([3, 3, 4, 3, 4]) + \text{size}([3, 3, 4, 3, 4]) = 4+3+5 = 12$ 。这是你能得到的最高分。

## 样例 #1

### 输入

```
4
3
5 4 5
3
4 5 4
10
3 3 3 3 4 1 2 3 5 4
10
17 89 92 42 29 41 92 14 70 45
```

### 输出

```
12
11
12
186
```



---

---
title: "Digital Village (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2021E1
tag: ['动态规划 DP']
---

# Digital Village (Easy Version)

## 题目描述

**这是问题的简单版本。在三个版本中，$n$ 和 $m$ 的约束条件不同。只有所有版本的问题都解决了，你才能进行 hack。**

Pak Chanek 正在为 Khuntien 村设置互联网连接。这个村庄可以表示为一个连通的简单图，其中有 $n$ 栋房屋和 $m$ 条互联网电缆，每条电缆连接房屋 $u_i$ 和房屋 $v_i$，并且具有延迟 $w_i$。

有 $p$ 栋房屋需要互联网。Pak Chanek 最多可以在 $k$ 栋房屋中安装服务器。需要互联网的房屋将连接到其中一个服务器。但是，由于每条电缆都有其延迟，对于需要互联网的房屋 $s_i$，其经历的延迟将是该房屋与其连接的服务器之间电缆的**最大**延迟。

对于每个 $k = 1,2,\ldots,n$，帮助 Pak Chanek 确定所有需要互联网的房屋所能达到的最小**总**延迟。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 400$ )。对每个测试用例说明如下：

每个测试用例的第一行包含三个整数 $n$ , $m$ , $p$ ( $2 \le n \le 400$ ; $n-1 \le m \le 400$ ; $1 \le p \le n$ )，表示房屋数量、电缆数量和需要网络的房屋数量。

每个测试用例的第二行包含 $p$ 个整数 $s_1, s_2, \ldots, s_p$ ( $1 \le s_i \le n$ )，表示需要上网的房屋。保证 $s$ 中的所有元素都是不同的。

每个测试用例下 $m$ 行每行包含三个整数 $u_i$、$v_i$ 和 $w_i$（$1 \le u_i , v_i \le n$ ; $1 \le w_i \le 10^9$）表示一条连接房屋 $u_i$ 和房屋 $v_i$ 的网线，延迟为 $w_i$。保证给定的边构成一个连通的简单图。

保证 $n^3$ 和 $m^3$ 之和不超过 $10^8$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数：对**每个**$k = 1,2,\ldots,n$，计算所有需要上网的房屋所能达到的最小总延迟。

**样例解释**

第一个测试用例中，$k=3$ 的一个的最佳解决方案是在顶点 $2$ 、 $6$ 和 $8$ 安装服务器，并获得以下延迟：

- $\text{latency}(2) = 0$
- $\text{latency}(5) = \max(3, 5) = 5$
- $\text{latency}(6) = 0$
- $\text{latency}(8) = 0$
- $\text{latency}(9) = \max(2, 4) = 4$

因此总延迟为 $0+5+0+0+4=9$ 。

## 样例 #1

### 输入

```
2
9 8 5
2 5 6 8 9
1 2 1
1 3 2
3 4 10
4 5 3
4 6 5
1 7 10
7 8 4
7 9 2
3 3 2
3 1
1 2 1
2 3 3
1 3 2
```

### 输出

```
34 19 9 4 0 0 0 0 0
2 0 0
```



---

---
title: "Digital Village (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2021E2
tag: ['动态规划 DP', 'Kruskal 重构树']
---

# Digital Village (Hard Version)

## 题目描述

**这是问题的困难版本。在三个版本中，$n$ 和 $m$ 的约束条件不同。只有所有版本的问题都解决了，你才能进行 hack。**

Pak Chanek 正在为 Khuntien 村设置互联网连接。这个村庄可以表示为一个连通的简单图，其中有 $n$ 栋房屋和 $m$ 条互联网电缆，每条电缆连接房屋 $u_i$ 和房屋 $v_i$，并且具有延迟 $w_i$。

有 $p$ 栋房屋需要互联网。Pak Chanek 最多可以在 $k$ 栋房屋中安装服务器。需要互联网的房屋将连接到其中一个服务器。但是，由于每条电缆都有其延迟，对于需要互联网的房屋 $s_i$，其经历的延迟将是该房屋与其连接的服务器之间电缆的**最大**延迟。

对于每个 $k = 1,2,\ldots,n$，帮助 Pak Chanek 确定所有需要互联网的房屋所能达到的最小**总**延迟。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 2000$ )。对每个测试用例说明如下：

每个测试用例的第一行包含三个整数 $n$ , $m$ , $p$ ( $2 \le n \le 5000$ ; $n-1 \le m \le 5000$ ; $1 \le p \le n$ )，表示房屋数量、电缆数量和需要网络的房屋数量。

每个测试用例的第二行包含 $p$ 个整数 $s_1, s_2, \ldots, s_p$ ( $1 \le s_i \le n$ )，表示需要上网的房屋。保证 $s$ 中的所有元素都是不同的。

每个测试用例下 $m$ 行每行包含三个整数 $u_i$、$v_i$ 和 $w_i$（$1 \le u_i , v_i \le n$ ; $1 \le w_i \le 10^9$）表示一条连接房屋 $u_i$ 和房屋 $v_i$ 的网线，延迟为 $w_i$。保证给定的边构成一个连通的简单图。

保证 $n$ 和 $m$ 之和不超过 $5000$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数：对**每个**$k = 1,2,\ldots,n$，计算所有需要上网的房屋所能达到的最小总延迟。

**样例解释**

第一个测试用例中，$k=3$ 的一个的最佳解决方案是在顶点 $2$ 、 $6$ 和 $8$ 安装服务器，并获得以下延迟：

- $\text{latency}(2) = 0$
- $\text{latency}(5) = \max(3, 5) = 5$
- $\text{latency}(6) = 0$
- $\text{latency}(8) = 0$
- $\text{latency}(9) = \max(2, 4) = 4$

因此总延迟为 $0+5+0+0+4=9$ 。

## 样例 #1

### 输入

```
2
9 8 5
2 5 6 8 9
1 2 1
1 3 2
3 4 10
4 5 3
4 6 5
1 7 10
7 8 4
7 9 2
3 3 2
3 1
1 2 1
2 3 3
1 3 2
```

### 输出

```
34 19 9 4 0 0 0 0 0
2 0 0
```



---

---
title: "Card Game"
layout: "post"
diff: 提高+/省选-
pid: CF2025E
tag: ['动态规划 DP', 'Catalan 数']
---

# Card Game

## 题目描述

在伯兰最受欢迎的卡牌游戏中，使用的是一个 $ n \times m $ 的卡牌组。每张卡牌都有两个参数：花色和等级。游戏中的花色编号从 $ 1 $ 到 $ n $，等级编号从 $ 1 $ 到 $ m $。每种花色和等级的组合中恰好有一张卡牌。

一张花色为 $ a $、等级为 $ b $ 的卡牌可以打败一张花色为 $ c $、等级为 $ d $ 的卡牌的条件有两个：
- $ a = 1 $ ， $ c \ne 1 $ （花色为 $ 1 $ 的卡牌可以打败任何其他花色的卡牌）；
- $ a = c $ ， $ b > d $ （同一花色的卡牌可以打败等级较低的卡牌）。

两名玩家进行游戏。在游戏开始之前，他们各自获得正好一半的牌组。第一名玩家获胜的条件是，对于第二名玩家的每一张卡牌，他都能选择一张可以打败它的卡牌，并且没有卡牌被选择两次（即存在一组匹配，第一名玩家的卡牌与第二名玩家的卡牌相匹配，每对中的第一名玩家的卡牌打败第二名玩家的卡牌）。否则，第二名玩家获胜。

你的任务是计算出将卡牌分配的方式，以便第一名玩家获胜的方式数量。两种方式被认为是不同的，如果存在一张卡牌在一种方式中属于第一名玩家，而在另一种方式中属于第二名玩家。结果可能非常大，因此请输出结果对 $ 998244353 $ 取模。

## 输入格式

输入的第一行包含两个整数 $ n $ 和 $ m $ （ $ 1 \le n, m \le 500 $ ）。

输入数据保证 $ m $ 是偶数。

## 输出格式

输出将卡牌分配的方式数量，使得第一名玩家获胜，结果对 $ 998244353 $ 取模 。

## 样例 #1

### 输入

```
1 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 6
```

### 输出

```
1690
```

## 样例 #4

### 输入

```
5 4
```

### 输出

```
568
```

## 样例 #5

### 输入

```
500 500
```

### 输出

```
84693741
```



---

---
title: "The Endspeaker (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2027D2
tag: ['动态规划 DP', '线段树']
---

# The Endspeaker (Hard Version)

## 题目描述

这是这道题目的困难版本。与简单版本的区别在于，你还需要输出达到最优解的操作序列数量。你需要解决这两种版本才能进行 hack。

现在给定一个数组 $ a $，长度为 $ n $，以及一个数组 $ b $，长度为 $ m $（保证 $ b_i > b_{i+1} $ 对所有 $ 1 \le i < m $ 成立）。初始时，$ k $ 的值为 $ 1 $。你的目标是通过执行以下两种操作之一反复将数组 $ a $ 变为空：

- 类型 $ 1 $ 操作 — 在 $ k < m $ 且数组 $ a $ 不为空时，你可以将 $ k $ 的值加 $ 1 $。这种操作不需要花费任何代价。
- 类型 $ 2 $ 操作 — 你可以移除数组 $ a $ 的一个非空前缀，使得这个前缀的和不大于 $ b_k $。这种操作的代价为 $ m - k $。

你需要让将数组 $ a $ 变为空的总操作代价最小化。如果无法通过任何操作序列达到这一目标，请输出 $ -1 $。否则，输出最小总操作代价以及产生命中该代价的操作序列数量，对 $ 10^9 + 7 $ 取模。

若两个操作序列在任一步骤中选择了不同种类的操作，或移除前缀的大小不同，则它们视为不同。

## 输入格式

每个测试用例包含多个测试，第一行为测试用例数量 $ t $（$ 1 \le t \le 1000 $）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $ n $ 和 $ m $（$ 1 \le n, m \le 3 \cdot 10^5 $，且 $ 1 \le n \cdot m \le 3 \cdot 10^5 $）。

每个测试用例的第二行包含长度为 $ n $ 的整数数组 $ a $，其中每个 $ a_i $ 满足 $ 1 \le a_i \le 10^9 $。

每个测试用例的第三行包含长度为 $ m $ 的整数数组 $ b $，$ 1 \le b_i \le 10^9 $，并且满足 $ b_i > b_{i+1} $ 对所有 $ 1 \le i < m $。

保证所有测试用例的总 $ n \cdot m $ 不超过 $ 3 \cdot 10^5 $。

## 输出格式

对于每个测试用例，如果可以使数组 $ a $ 变为空，则输出两个整数：最小的操作总费用，以及达到该最小费用的操作序列数量，结果对 $ 10^9 + 7 $ 取模。

如果没有可能的操作序列能使数组 $ a $ 变为空，则输出单个整数 $ -1 $。

## 说明/提示

以下为一个测试用例的示例，其中最优操作序列的总费用为 $ 1 $，共有 $ 3 $ 种：

- 所有这 $ 3 $ 种序列都以类型 $ 2 $ 的操作开头，移除前缀 $ [9] $，使得 $ a = [3, 4, 3] $，产生代价 $ 1 $。然后执行类型 $ 1 $ 操作，把 $ k $ 提升一位，此后所有操作均无代价。
- 一种序列依次移除前缀 $ [3, 4] $ 和 $ [3] $。
- 另一种序列依次移除前缀 $ [3] $ 和 $ [4, 3] $。
- 还有一种序列依次移除前缀 $ [3] $，再移除 $ [4] $，最后移除 $ [3] $。

在第二个测试用例中，由于 $ a_1 > b_1 $，无法移除任何前缀，因此无论如何都无法使数组 $ a $ 变为空。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1
```

### 输出

```
1 3
-1
2 11
10 42
4 1
```



---

---
title: "Alice's Adventures in Addition"
layout: "post"
diff: 提高+/省选-
pid: CF2028F
tag: ['动态规划 DP', '标签465']
---

# Alice's Adventures in Addition

## 题目描述

**注意不寻常的空间限制。**

柴郡猫给爱丽丝出了一个题：给定 $n$ 个整数 $a_1,a_2,\dots,a_n$ 和一个整数 $m$，能否在以下等式的 $\circ $ 中放入 $+$ 和 $\times$ 使得等式成立：

$$
a_1 \circ a_2 \circ \cdots \circ a_n = m
$$

我们遵循通常的运算顺序：$\times$ 在 $+$ 之前进行。

虽然爱丽丝的象棋下得很好，但她的数学却不好。请帮帮她，让她找到离开仙境的方法！

## 输入格式

每个测试点内有多组数据，第一行一个整数 $t$，表示数据组数。

接下来 $t$ 组数据，对于每组数据：

## 输出格式

对于每组数据，输出一行一个 `YES` 或 `NO` 表示答案，大小写均可。

## 说明/提示

$1\le t\le 10^4$，$1\le n\le \sum n\le 2\times 10^5$，$1\le m\le 10^4$，$0\le a_i\le 10^4$。

## 样例 #1

### 输入

```
6
5 4
2 1 1 1 2
5 5
2 1 1 1 2
5 6
2 1 1 1 2
5 7
2 1 1 1 2
5 8
2 1 1 1 2
5 6
2 0 2 2 3
```

### 输出

```
YES
YES
YES
YES
NO
YES
```



---

---
title: "MEXimize the Score"
layout: "post"
diff: 提高+/省选-
pid: CF2030E
tag: ['动态规划 DP', '组合数学', '排列组合']
---

# MEXimize the Score

## 题目描述

Suppose we partition the elements of an array $ b $ into any number $ k $ of non-empty multisets $ S_1, S_2, \ldots, S_k $ , where $ k $ is an arbitrary positive integer. Define the score of $ b $ as the maximum value of $ \operatorname{MEX}(S_1) $ $ ^{\text{∗}} $ $  + \operatorname{MEX}(S_2) + \ldots + \operatorname{MEX}(S_k) $ over all possible partitions of $ b $ for any integer $ k $ .

Envy is given an array $ a $ of size $ n $ . Since he knows that calculating the score of $ a $ is too easy for you, he instead asks you to calculate the sum of scores of all $ 2^n - 1 $ non-empty subsequences of $ a $ . $ ^{\text{†}} $ Since this answer may be large, please output it modulo $ 998\,244\,353 $ .

 $ ^{\text{∗}} $ $ \operatorname{MEX} $ of a collection of integers $ c_1, c_2, \ldots, c_k $ is defined as the smallest non-negative integer $ x $ that does not occur in the collection $ c $ . For example, $ \operatorname{MEX}([0,1,2,2]) = 3 $ and $ \operatorname{MEX}([1,2,2]) = 0 $

 $ ^{\text{†}} $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deleting several (possibly, zero or all) elements.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the answer, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, we must consider seven subsequences:

- $ [0] $ : The score is $ 1 $ .
- $ [0] $ : The score is $ 1 $ .
- $ [1] $ : The score is $ 0 $ .
- $ [0,0] $ : The score is $ 2 $ .
- $ [0,1] $ : The score is $ 2 $ .
- $ [0,1] $ : The score is $ 2 $ .
- $ [0,0,1] $ : The score is $ 3 $ .

 The answer for the first testcase is $ 1+1+2+2+2+3=11 $ .In the last testcase, all subsequences have a score of $ 0 $ .

## 样例 #1

### 输入

```
4
3
0 0 1
4
0 0 1 1
5
0 0 1 2 2
4
1 1 1 1
```

### 输出

```
11
26
53
0
```



---

---
title: "Sakurako and Chefir"
layout: "post"
diff: 提高+/省选-
pid: CF2033G
tag: ['动态规划 DP', '倍增']
---

# Sakurako and Chefir

## 题目描述

Given a tree with $ n $ vertices rooted at vertex $ 1 $ . While walking through it with her cat Chefir, Sakurako got distracted, and Chefir ran away.

To help Sakurako, Kosuke recorded his $ q $ guesses. In the $ i $ -th guess, he assumes that Chefir got lost at vertex $ v_i $ and had $ k_i $ stamina.

Also, for each guess, Kosuke assumes that Chefir could move along the edges an arbitrary number of times:

- from vertex $ a $ to vertex $ b $ , if $ a $ is an ancestor $ ^{\text{∗}} $ of $ b $ , the stamina will not change;
- from vertex $ a $ to vertex $ b $ , if $ a $ is not an ancestor of $ b $ , then Chefir's stamina decreases by $ 1 $ .

If Chefir's stamina is $ 0 $ , he cannot make a move of the second type.

For each assumption, your task is to find the distance to the farthest vertex that Chefir could reach from vertex $ v_i $ , having $ k_i $ stamina.

 $ ^{\text{∗}} $ Vertex $ a $ is an ancestor of vertex $ b $ if the shortest path from $ b $ to the root passes through $ a $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

Each test case is described as follows:

- The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.
- The next $ n-1 $ lines contain the edges of the tree. It is guaranteed that the given edges form a tree.
- The next line consists of a single integer $ q $ $ (1\le q\le 2 \cdot 10^5) $ , which denotes the number of guesses made by Kosuke.
- The next $ q $ lines describe the guesses made by Kosuke, with two integers $ v_i $ , $ k_i $ $ (1\le v_i \le n, 0 \le k_i\le n) $ .

It is guaranteed that the sum of $ n $ and the sum of $ q $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case and for each guess, output the maximum distance to the farthest vertex that Chefir could reach from the starting point $ v_i $ having $ k_i $ stamina.

## 说明/提示

In the first example:

- In the first query, you can go from vertex $ 5 $ to vertex $ 3 $ (after which your stamina will decrease by $ 1 $ and become $ 0 $ ), and then you can go to vertex $ 4 $ ;
- In the second query, from vertex $ 3 $ with $ 1 $ stamina, you can only reach vertices $ 2 $ , $ 3 $ , $ 4 $ , and $ 5 $ ;
- In the third query, from vertex $ 2 $ with $ 0 $ stamina, you can only reach vertices $ 2 $ , $ 3 $ , $ 4 $ , and $ 5 $ ;

## 样例 #1

### 输入

```
3
5
1 2
2 3
3 4
3 5
3
5 1
3 1
2 0
9
8 1
1 7
1 4
7 3
4 9
3 2
1 5
3 6
7
6 0
2 3
6 2
8 2
2 4
9 2
6 3
6
2 1
2 5
2 4
5 6
4 3
3
3 1
1 3
6 5
```

### 输出

```
2 1 2 
0 5 2 4 5 5 5 
1 3 4
```



---

---
title: "Khayyam's Royal Decree (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2034F1
tag: ['动态规划 DP', '容斥原理']
---

# Khayyam's Royal Decree (Easy Version)

## 题目描述

这是本题的简单版本。两个版本的唯一区别在于 $k$ 和 $\sum k$ 的限制。

Khayyam 有一个**宝箱**，**宝箱**里初始有 $n$ 个红宝石和 $m$ 个蓝宝石。一个红宝石的价值为 $2$，一个蓝宝石的价值为 $1$。他还有一个**背包**，初始为空。另外，他还有 $k$ 张卷轴，第 $i$ 张卷轴上有数对 $(r_i,b_i)$。

Khayyam 将进行一个游戏，游戏共 $n+m$ 轮，每轮流程如下：

1. Khayyam 从**宝箱**中等概率随机拿出一个宝石。
2. 他将这个宝石放入**背包**中。
3. 若存在一张卷轴 $i$，使得**宝箱**中恰有 $r_i$ 个红宝石和 $b_i$ 个蓝宝石，将所有**背包**里的宝石的价值翻倍。

一个宝石的价值可以被多次翻倍。

求游戏结束时 Khayyam **背包**里宝石的价值总和的期望值，对 $998244353$ 取模。

## 输入格式

多测，第一行一个整数 $T$ 表示数据组数。

每组数据的第一行三个整数 $n,m,k$。

接下来 $k$ 行，每行两个整数 $r_i,b_i$。

保证 $1\le T\le 500$，$1\le n,m,\sum n,\sum m\le 2\times 10^5$，$1\le k,\sum k\le 500$。

保证 $0\le r_i\le n$，$0\le b_i\le m$，$1\le r_i+b_i\le n+m-1$，且 $(r_i,b_i)$ 两两不同。

## 输出格式

一行一个整数，表示答案对 $998244353$ 取模的值。

### 样例解释

对于第一组数据，最终背包里总会有 $3$ 个红宝石和 $4$ 个蓝宝石，不会有卷轴被触发。因此背包里宝石的总价值总是 $2\times 3+1\times 4=10$。

对于第二组数据：

+ 有 $\dfrac{1}{2}$ 概率，Khayyam 先拿出红宝石再拿出蓝宝石，不会有卷轴被触发，总价值为 $3$；
+ 有 $\dfrac{1}{2}$ 概率，Khayyam 先拿出蓝宝石再拿出红宝石，卷轴 $1$ 会被触发，蓝宝石的价值翻倍，总价值为 $4$。

因此总价值的期望是 $\dfrac{1}{2}\times 3+\dfrac{1}{2}\times 4=\dfrac{7}{2}\equiv 499122180\pmod {998244353}$。

## 样例 #1

### 输入

```
5
3 4 0
1 1 1
1 0
3 3 2
1 1
2 2
3 3 2
2 1
1 2
10 4 5
1 0
8 0
6 4
0 2
7 4
```

### 输出

```
10
499122180
798595498
149736666
414854846
```



---

---
title: "Monster"
layout: "post"
diff: 提高+/省选-
pid: CF2035E
tag: ['动态规划 DP', '模拟退火', '根号分治']
---

# Monster

## 题目描述

Man, this Genshin boss is so hard. Good thing they have a top-up of $ 6 $ coins for only $  \$4.99 $ . I should be careful and spend no more than I need to, lest my mom catches me...



You are fighting a monster with $ z $ health using a weapon with $ d $ damage. Initially, $ d=0 $ . You can perform the following operations.

- Increase $ d $ — the damage of your weapon by $ 1 $ , costing $ x $ coins.
- Attack the monster, dealing $ d $ damage and costing $ y $ coins.

You cannot perform the first operation for more than $ k $ times in a row.

Find the minimum number of coins needed to defeat the monster by dealing at least $ z $ damage.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 100 $ ) — the number of test cases.

The only line of each test case contains 4 integers $ x $ , $ y $ , $ z $ , and $ k $ ( $ 1\leq x, y, z, k\leq 10^8 $ ) — the first operation's cost, the second operation's cost, the monster's health, and the limitation on the first operation.

## 输出格式

For each test case, output the minimum number of coins needed to defeat the monster.

## 说明/提示

In the first test case, $ x = 2 $ , $ y = 3 $ , $ z = 5 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 12 $ coins:

- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.

You deal a total of $ 3 + 3 = 6 $ damage, defeating the monster who has $ 5 $ health. The total number of coins you use is $ 2 + 2 + 2 + 3 + 3 = 12 $ coins.

In the second test case, $ x = 10 $ , $ y = 20 $ , $ z = 40 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 190 $ coins:

- Increase damage by $ 5 $ , costing $ 5\cdot x $ = $ 50 $ coins.
- Attack the monster once, dealing $ 5 $ damage, costing $ 20 $ coins.
- Increase damage by $ 2 $ , costing $ 2\cdot x $ = $ 20 $ coins.
- Attack the monster $ 5 $ times, dealing $ 5\cdot 7 = 35 $ damage, costing $ 5\cdot y $ = $ 100 $ coins.

You deal a total of $ 5 + 35 = 40 $ damage, defeating the monster who has exactly $ 40 $ health. The total number of coins you use is $ 50 + 20 + 20 + 100 = 190 $ coins.

## 样例 #1

### 输入

```
4
2 3 5 5
10 20 40 5
1 60 100 10
60 1 100 10
```

### 输出

```
12
190
280
160
```



---

---
title: "Grid Walk"
layout: "post"
diff: 提高+/省选-
pid: CF2038K
tag: ['动态规划 DP', '数论']
---

# Grid Walk

## 题目描述

### 题意翻译
给定一个 $n\times n$ 的矩阵和两个正整数 $a$ 和 $b$，第 $i$ 行第 $j$ 列的权值 $c_{i,j}=\gcd(i,a)+\gcd(j,b)$，一开始你在点 $(1,1)$，你可以向右或者向下走，一直走到点 $(n,n)$。

你需要规划一条路径，使得从点 $(1,1)$ 走到点 $(n,n)$ 所经过的点的权值和 $\sum c_{i,j}$ 最小，输出这个最小值。

## 输入格式

一行输入三个正整数 $n,a,b$。（$2\le n \le 10^6$；$1\le a,b \le 10^6$）

## 输出格式

输出一个整数表示所求答案。

翻译人：[gcx12012](https://www.luogu.com.cn/user/494601)

## 样例 #1

### 输入

```
4 2 4
```

### 输出

```
21
```

## 样例 #2

### 输入

```
10 210 420
```

### 输出

```
125
```



---

---
title: "Shohag Loves Inversions"
layout: "post"
diff: 提高+/省选-
pid: CF2039E
tag: ['动态规划 DP']
---

# Shohag Loves Inversions

## 题目描述

# Shohag Loves Inversions


给你一个数列，初始数列为 $ a = [0, 1] $ ，现在重复进行以下操作若干次:
- 将当前数组中逆序对个数k插入当前数组中任意一个位置，包括开头或者结尾。

举个例子, 如果 $ a = [4, 6, 2, 4] $ , 则逆序对个数是 $ k = 3 $ . 所以可以通过操作，得到以下数组: $ [\textbf{3}, 4, 6, 2, 4] $ , $ [4, \textbf{3}, 6, 2, 4] $ , $ [4, 6, \textbf{3}, 2, 4] $ , $ [4, 6, 2, \textbf{3}, 4] $ , 和$ [4, 6, 2, 4, \textbf{3}] $ 。

给一个整数 $ n $，求通过操作可以得到多少种长度为$ n $的不同数列，方案数对对 $ 998\,244\,353 $ 取模。

逆序对的对数就是有多少个二元组，满足  $ i < j $ 并且 $ a_i > a_j $ 。

## 输入格式

第一行给出一个整数$ t $ ( $ 1 \le t \le 10^4 $ )，表示有多少组数据。

每行给出一个整数 $ n $ ( $ 2 \le n \le 10^6 $ )

可以保证n的和在所有测试用例中不超过$ 10^6 $ 。

## 输出格式

对于每一个测试点, 输出一个整数 — 对 $ 998\,244\,353 $ 取模。

## 样例 #1

### 样例输入 #1

```
4
4
2
7
69
```

### 样例输出 #1

```
5
1
682
325188814
```

## 说明/提示

对于第一个样例, 以下$ 5 $种数列可以通过操作得到  
- $ [0, 1] \rightarrow [0, \textbf{0}, 1] \rightarrow [0, 0, 1, \textbf{0}] $ ,
- $ [0, 1] \rightarrow [0, \textbf{0}, 1] \rightarrow [0, 0, \textbf{0}, 1] $ ,
- $ [0, 1] \rightarrow [0, 1, \textbf{0}] \rightarrow [0, 1, 0, \textbf{1}] $ ,
- $ [0, 1] \rightarrow [0, 1, \textbf{0}] \rightarrow [0, 1, \textbf{1}, 0] $ ,
- $ [0, 1] \rightarrow [0, 1, \textbf{0}] \rightarrow [\textbf{1}, 0, 1, 0] $ .

## 样例 #1

### 输入

```
4
4
2
7
69
```

### 输出

```
5
1
682
325188814
```



---

---
title: "Sheet Music"
layout: "post"
diff: 提高+/省选-
pid: CF2041H
tag: ['动态规划 DP']
---

# Sheet Music

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041H/b6dd52e9533263fc8e6069a510bb15c19ed436d6.png) Image generated by ChatGPT 4o.Alice likes singing. As a singing enthusiast, Alice has listened to countless songs and has tried singing them many times. However, occasionally, some songs make Alice feel bored. After some research, Alice believes that this is because even though the songs she chose are all different, due to her instinctive preference, they all turn out to be musically similar to one another.

To thoroughly analyze this, Alice decided to study the sheet music of the songs. For convenience, Alice represented a song of length $ n $ as an integer sequence $ a_1, a_2, \ldots, a_n $ , where $ a_i $ is the pitch of the $ i $ -th note. Then she defined the musical equivalence between songs. Two songs $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ of length $ n $ are musically equivalent if for all $ 1\leq i<n $ , both $ a_i, a_{i+1} $ and $ b_{i}, b_{i+1} $ have the same pitch relationship. More specifically, $ a_i, a_{i+1} $ and $ b_i, b_{i+1} $ have the same pitch relationship if either

- $ a_i < a_{i + 1} $ and $ b_i < b_{i + 1} $ ,
- $ a_i = a_{i + 1} $ and $ b_i = b_{i + 1} $ , or
- $ a_i > a_{i + 1} $ and $ b_i > b_{i + 1} $ .

 For example, $ 1, 2, 3, 3, 2 $ and $ 5, 9, 13, 13, 1 $ are musically equivalent, while $ 1, 2, 3, 2, 1 $ and $ 1, 2, 2, 2, 1 $ are not. Having practiced consistently for a long time, Alice is able to sing any note in the range of $ [1, k] $ . She wants to know how many different songs of length $ n $ within her range there are, if we treat musically equivalent songs as the same one. Can you help her calculate the number?

Since the answer might be large, print the answer modulo $ 998244353 $ .

## 输入格式

The only line contains two integers $ n, k $ .

- $ 1\leq n\leq 10^6 $
- $ 1\leq k \leq 10^9 $

## 输出格式

Output the number of different songs modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3 2
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
67
```



---

---
title: "Two Subarrays"
layout: "post"
diff: 提高+/省选-
pid: CF2042F
tag: ['动态规划 DP', '线段树', '矩阵运算', '动态规划优化']
---

# Two Subarrays

## 题目描述

给定两个长度为 $n$ 的整数数组 $a$ 和 $b$。

我们定义子数组 $[l, r]$ 的代价为 $a_l + a_{l + 1} + \cdots + a_r + b_l + b_r$。如果 $l = r$，那么代价计算为 $a_l + 2 \cdot b_l$。

你需要执行以下三种类型的查询：

- "1 $p$ $x$" — 把 $a_p$ 更新为 $x$；
- "2 $p$ $x$" — 把 $b_p$ 更新为 $x$；
- "3 $l$ $r$" — 在区间 $[l, r]$ 内找到两个不相交且非空的子数组，使它们的总代价最大，并输出这个总代价。

## 输入格式

第一行是一个整数 $n$，表示数组的长度（$2 \le n \le 2 \cdot 10^5$）。

第二行是 $n$ 个整数，分别表示数组 $a$ 的元素：$a_1, a_2, \dots, a_n$（每个 $a_i$ 满足 $-10^9 \le a_i \le 10^9$）。

第三行是 $n$ 个整数，分别表示数组 $b$ 的元素：$b_1, b_2, \dots, b_n$（每个 $b_i$ 满足 $-10^9 \le b_i \le 10^9$）。

第四行是一个整数 $q$，表示查询的数量（$1 \le q \le 2 \cdot 10^5$）。

接下来的 $q$ 行，每行一个查询，可能是以下三种之一：

- "1 $p$ $x$"：更新 $a$ 数组的第 $p$ 个元素为 $x$；
- "2 $p$ $x$"：更新 $b$ 数组的第 $p$ 个元素为 $x$；
- "3 $l$ $r$"：在区间 $[l, r]$ 找到两个不重叠且非空的子数组，使它们的总代价最大，并输出该代价。

可以保证至少存在一个第三种类型的查询。

## 输出格式

对于每一个第三种类型的查询，输出在区间 $[l, r]$ 内的两个不相交且非空子数组的最大可能总代价。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
3 -1 4 -3 2 4 0
0 6 1 0 -3 -2 -1
6
3 1 7
1 2 0
3 3 6
2 5 -3
1 3 2
3 1 5
```

### 输出

```
18
7
16
```

## 样例 #2

### 输入

```
10
2 -1 -3 -2 0 4 5 6 2 5
2 -4 -5 -1 6 2 5 -6 4 2
10
3 6 7
1 10 -2
3 5 7
3 2 8
2 1 -5
2 7 4
3 1 3
3 3 8
3 2 3
1 4 4
```

### 输出

```
23
28
28
-17
27
-22
```



---

---
title: "Nim"
layout: "post"
diff: 提高+/省选-
pid: CF2043F
tag: ['动态规划 DP', '博弈论', '鸽笼原理']
---

# Nim

## 题目描述

重温一下「Nim」游戏的规则。游戏开始时有 $ n $ 堆石子，第 $ i $ 堆中有若干石子。两名玩家轮流行动：选择一个不为空的石子堆，从中取走至少一个石子。不能进行操作的玩家将输掉游戏。

现有一个包含 $ n $ 个整数的数组 $ a $。Artem 和 Ruslan 打算在数组的部分区间上进行 Nim 游戏。每个游戏回合由一个区间 $ (l_i, r_i) $ 确定，其中 $ a_{l_i}, a_{l_i+1}, \dots, a_{r_i} $ 是各个石子堆的大小。

在每轮游戏开始前，Ruslan 可以选择从该区间中移除任意数量的堆，但至少要留下一个堆，因此最多可移除 $ (r_i - l_i) $ 堆。他可以选择不移除任何堆。移除后，游戏将在留下的堆上进行。

每个回合相互独立：某一回合的变动不会影响原始数组或其他回合。

Ruslan 的目标是移除尽可能多的石子堆，以确保始终是先手的 Artem 输掉游戏。

对于每个回合：

1. 确定 Ruslan 可以移除的最大石子堆数量；
2. 计算达到最大移除数量的方法数，并输出其对 $ 998\,244\,353 $ 取模的结果。

若两种移除方法在某个索引 $ i $ 上存在区别，即一种方法移除了该索引对应的堆而另一种没有，则视为两种不同的方法。若 Ruslan 无法确保 Artem 输掉某回合，则输出 -1。

## 输入格式

第一行包含两个整数 $ n $ 和 $ q $（$ 1 \le n, q \le 10^5 $），分别表示数组的大小和需要计算结果的区间数。

第二行是 $ n $ 个整数 $ a_1, a_2, \dots, a_n $（$ 0 \le a_i \le 50 $），表示初始数组中的元素。

接下来的 $ q $ 行中，每行包含两个整数 $ l_i, r_i $（$ 1 \le l_i \le r_i \le n $），定义第 $ i $ 个回合中要进行操作的区间。

## 输出格式

对于每个回合：

- 如果 Ruslan 能赢，输出两个整数——可以移除的最大堆数及其对应的移除方案数量（对 $ 998\,244\,353 $ 取模）；
- 否则输出 -1。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
9 5
0 1 2 1 3 4 5 6 0
1 5
2 5
3 5
4 5
1 9
```

### 输出

```
4 1
2 1
0 1
-1
8 2
```



---

---
title: "Missing Separators"
layout: "post"
diff: 提高+/省选-
pid: CF2045H
tag: ['动态规划 DP']
---

# Missing Separators

## 题目描述

你有一个字典，其中的单词均已按照字母顺序排好，并且每个单词都是独特的，由大写英文字母构成。

现在你想打印这个字典，但不幸的是，打印系统出现了故障，所有单词都相连在一起打印，没有任何间隔符。因此，你得到一个字符串 $S$，它是字典中所有单词按顺序连接构成的。

你的任务是从字符串 $S$ 中将原来的字典单词分离出来。注意，分离出来的单词也必须是唯一的，并且按字母顺序排列。你需要尽可能多地复原字典中的单词数量。如果存在多个分离方案能够达到单词数量的最大值，你可以选择任意一种方案。

## 输入格式

输入为一行，包含字符串 $S$（长度范围为 $1 \leq |S| \leq 5000$）。字符串 $S$ 只由大写字母组成。

## 输出格式

首先输出一个整数，表示最多可以复原的单词数量，记作 $n$。

接下来输出 $n$ 行，每行表示一个单词。输出的单词需互不相同，并按字母顺序排列。按排列顺序连接这些单词后应完全等于输入字符串 $S$。

如果有多个方案可以实现最大单词数量，输出任意一种方案即可。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
ABACUS
```

### 输出

```
4
A
BA
C
US
```

## 样例 #2

### 输入

```
AAAAAA
```

### 输出

```
3
A
AA
AAA
```

## 样例 #3

### 输入

```
EDCBA
```

### 输出

```
1
EDCBA
```



---

---
title: "Kevin and Math Class"
layout: "post"
diff: 提高+/省选-
pid: CF2048F
tag: ['动态规划 DP', '树形 DP', '笛卡尔树']
---

# Kevin and Math Class

## 题目描述

Kevin 是来自 Eversleeping Town 的一名学生，他正在参加一门数学课，老师正在给他出一些除法练习题。

在黑板上，有两行正整数，每行包含 $n$ 个数字。第一行是 $a_1, a_2, \ldots, a_n$，第二行是 $b_1, b_2, \ldots, b_n$。

对于每个除法练习题，Kevin 可以选择任何一个区间 $[l, r]$，并在 $b_l, b_{l+1}, \ldots, b_r$ 中找到最小的值 $x$。然后他将修改 $l \leq i \leq r$ 范围内的每个 $a_i$，使得每个 $a_i$ 被 $x$ 除后的结果向上取整。

更正式地，他选择两个整数 $1 \leq l \leq r \leq n$，设 $x = \min_{l \leq i \leq r} b_i$，然后将所有 $l \leq i \leq r$ 范围内的 $a_i$ 修改为 $ \lceil \frac{a_i}{x} \rceil$。

Kevin 只有当所有 $a_i$ 都变为 1 时，才能离开教室回家。他非常渴望回家，想知道实现这一目标所需的最小除法练习次数。

## 输入格式

每个测试案例包含多个测试用例。第一行是测试用例的数量 $t$（$1 \le t \le 10^4$）。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$），表示数列 $a$ 和 $b$ 的长度。

接下来的一行是 $n$ 个整数 $a_1, a_2, \ldots, a_n$，表示黑板上的第一行数字。

接下来的一行是 $n$ 个整数 $b_1, b_2, \ldots, b_n$，表示黑板上的第二行数字。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— 达成目标所需的最小除法练习次数。

## 说明/提示

对于第一个测试用例:  
$[{\color{red}{5,4}}, 2] \xrightarrow[\min(b_1, b_2) = 3] {\text{操作区间}[1, 2]} [{\color{red}{2, 2, 2}}] \xrightarrow[\min(b_1, b_2, b_3) = 2]{\text{操作区间}[1, 3]} [1, 1, 1]$

对于第二个测试用例:  
$[{\color{red}{3, 6, 1}}, 3, 2] \xrightarrow[\min(b_1, b_2, b_3) = 3]{\text{操作区间}[1, 3]} [1, {\color{red}{2, 1, 3}}, 2] \xrightarrow[\min(b_2, b_3, b_4) = 2]{\text{操作区间}[2, 4]} [1, 1, 1, {\color{red}{2, 2}}] \xrightarrow[\min(b_4, b_5) = 2]{\text{操作区间}[4, 5]} [1, 1, 1, 1, 1]$

translation from [Yorg](https://www.luogu.com.cn/user/617130)

## 样例 #1

### 输入

```
3
3
5 4 2
6 3 2
5
3 6 1 3 2
3 5 3 2 2
6
8 3 3 7 5 8
3 2 3 4 2 3
```

### 输出

```
2
3
3
```



---

---
title: "Earnest Matrix Complement"
layout: "post"
diff: 提高+/省选-
pid: CF2053F
tag: ['动态规划 DP', '线段树']
---

# Earnest Matrix Complement

## 题目描述

3, 2, 1, ... 我们是 —— RiOI 团队！

—— Felix & All, [特别感谢 3](https://www.luogu.com.cn/problem/T351681)

- Peter: 好消息，我的题目 T311013 已获批！
- $ \delta $: 幸好我的电脑没电，不然我可能参加了 wyrqwq 的比赛并得到负分。
- Felix: \[点赞\] 关于一首被删除歌曲的题目陈述！
- Aquawave: 我该为我的化学课感到悲伤吗？
- E.Space: 啊？
- Trine: 面包。
- Iris: 为什么总是我来测试题目？

时光荏苒，未来我们也许会重逢。回顾过去，每个人都在追寻自己向往的生活。

Aquawave 有一个大小为 $ n \times m $ 的矩阵 $ A $，其中的元素只允许是 $ [1, k] $ 区间内的整数。矩阵中的一些位置已被填上整数，其余位置用 $ -1 $ 表示，代表尚未填充。

你的任务是将矩阵 $ A $ 填满所有空白位置，接着定义 $ c_{u,i} $ 为第 $ i $ 行中数字 $ u $ 出现的次数。Aquawave 将矩阵的美丽定义为：

$$ \sum_{u=1}^k \sum_{i=1}^{n-1} c_{u,i} \cdot c_{u,i+1}. $$

请找出在最佳填充方案下的矩阵 $ A $ 的最大美丽值。

## 输入格式

输入第一行为一个整数 $ t $（$ 1 \leq t \leq 2 \cdot 10^4 $），表示测试用例的数量。以下为每个测试用例的详细描述。

每个测试用例第一行包含三个整数 $ n $、$ m $ 和 $ k $（$ 2 \leq n \leq 2 \cdot 10^5 $，$ 2 \leq m \leq 2 \cdot 10^5 $，$ n \cdot m \leq 6 \cdot 10^5 $，$ 1 \leq k \leq n \cdot m $），分别代表矩阵 $ A $ 的行数、列数以及矩阵中整数的范围。

接下来的 $ n $ 行，每行包含 $ m $ 个整数 $ A_{i,1}, A_{i,2}, \ldots, A_{i,m} $（$ 1 \leq A_{i,j} \leq k $ 或 $ A_{i,j} = -1 $），表示矩阵 $ A $ 中的各个元素。

保证所有测试用例中 $ n \cdot m $ 的总和不超过 $ 6 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一个整数，表示最大可能的美丽值。

## 说明/提示

在第一个测试用例中，矩阵 $ A $ 已经确定，其美丽值为：

$$ \sum_{u=1}^k \sum_{i=1}^{n-1} c_{u,i} \cdot c_{u,i+1} = c_{1,1} \cdot c_{1,2} + c_{1,2} \cdot c_{1,3} + c_{2,1} \cdot c_{2,2} + c_{2,2} \cdot c_{2,3} + c_{3,1} \cdot c_{3,2} + c_{3,2} \cdot c_{3,3} = 1 \cdot 1 + 1 \cdot 1 + 2 \cdot 0 + 0 \cdot 1 + 0 \cdot 2 + 2 \cdot 1 = 4。$$

在第二个测试用例中，可以这样填充矩阵：

$$ \begin{bmatrix} 2 & 3 & 3 \\ 2 & 2 & 3 \end{bmatrix}, $$

得到的美丽值为 $ 4 $。这可以被证明是最大的可能值。

在第三个测试用例中，以下为一种可能的最优填充方案：

$$ \begin{bmatrix} 1 & 1 & 1 \\ 1 & 2 & 1 \\ 1 & 1 & 4 \end{bmatrix}. $$

在第四个测试用例中，下面是一种可能的最优配置：

$$ \begin{bmatrix} 1 & 3 & 2 & 3 \\ 1 & 3 & 2 & 1 \\ 3 & 1 & 5 & 1 \end{bmatrix}. $$

在第五个测试用例中，以下是一种可能的最优填充：

$$ \begin{bmatrix} 5 & 5 & 2 \\ 1 & 8 & 5 \\ 7 & 5 & 6 \\ 7 & 7 & 4 \\ 4 & 4 & 4 \end{bmatrix}. $$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
9
3 3 3
1 2 2
3 1 3
3 2 1
2 3 3
-1 3 3
2 2 -1
3 3 6
-1 -1 1
1 2 -1
-1 -1 4
3 4 5
1 3 2 3
-1 -1 2 -1
3 1 5 1
5 3 8
5 -1 2
1 8 -1
-1 5 6
7 7 -1
4 4 4
6 6 5
-1 -1 5 -1 -1 -1
-1 -1 -1 -1 2 -1
-1 1 3 3 -1 -1
-1 1 -1 -1 -1 4
4 2 -1 -1 -1 4
-1 -1 1 2 -1 -1
6 6 4
-1 -1 -1 -1 1 -1
3 -1 2 2 4 -1
3 1 2 2 -1 -1
3 3 3 3 -1 2
-1 3 3 -1 1 3
3 -1 2 2 3 -1
5 5 3
1 1 3 -1 1
2 2 -1 -1 3
-1 -1 -1 2 -1
3 -1 -1 -1 2
-1 1 2 3 -1
6 2 7
-1 7
-1 6
7 -1
-1 -1
-1 -1
2 2
```

### 输出

```
4
4
10
10
8
102
93
58
13
```



---

---
title: "Bro Thinks He's Him"
layout: "post"
diff: 提高+/省选-
pid: CF2065H
tag: ['动态规划 DP', '线段树', '树状数组', '矩阵加速', '前缀和']
---

# Bro Thinks He's Him

## 题目描述

Skibidus 自认为是"天选之人"！他通过解决这个难题证明了这一点。你也能证明自己吗？

给定一个二进制字符串 $^{\text{∗}}$ $t$，定义 $f(t)$ 为将 $t$ 分割成由相同字符组成的连续子串的最小数量。例如，$f(\texttt{00110001}) = 4$，因为 $t$ 可以被分割为 $\texttt{[00][11][000][1]}$，每个括号内的子串均由相同字符组成。

Skibidus 给你一个二进制字符串 $s$ 和 $q$ 次查询。每次查询会翻转字符串中的一个字符（即 $\texttt{0}$ 变为 $\texttt{1}$，$\texttt{1}$ 变为 $\texttt{0}$），且修改会保留到后续查询。每次查询后，你需要输出所有非空子序列 $^{\text{†}}$ $b$ 的 $f(b)$ 之和模 $998\,244\,353$ 的结果。

 $^{\text{∗}}$ 二进制字符串仅包含字符 $\texttt{0}$ 和 $\texttt{1}$。

 $^{\text{†}}$ 字符串的子序列是指通过删除原字符串中若干（可能为零）个字符得到的新字符串。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例数量。

每个测试用例的第一行包含一个二进制字符串 $s$（$1 \leq |s| \leq 2 \cdot 10^5$）。

每个测试用例的第二行包含一个整数 $q$（$1 \leq q \leq 2 \cdot 10^5$）——查询次数。

每个测试用例的第三行包含 $q$ 个整数 $v_1, v_2, \ldots, v_q$（$1 \leq v_i \leq |s|$），表示第 $i$ 次查询翻转 $s_{v_i}$ 处的字符。

保证所有测试用例的 $|s|$ 之和与 $q$ 之和均不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在一行中输出 $q$ 个整数——每次查询后的答案模 $998\,244\,353$。

## 说明/提示

第一个测试用例在第一次查询后，$s$ 变为 $\texttt{001}$。计算所有子序列的 $f$ 值：
- $f(s_1) = f(\texttt{0}) = 1$
- $f(s_2) = f(\texttt{0}) = 1$
- $f(s_3) = f(\texttt{1}) = 1$
- $f(s_1 s_2) = f(\texttt{00}) = 1$
- $f(s_1 s_3) = f(\texttt{01}) = 2$
- $f(s_2 s_3) = f(\texttt{01}) = 2$
- $f(s_1 s_2 s_3) = f(\texttt{001}) = 2$

这些值的总和为 $10$，模 $998\,244\,353$ 后结果为 $10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
101
2
1 3
10110
3
1 2 3
101110101
5
7 2 4 4 1
```

### 输出

```
10 7 
61 59 67 
1495 1169 1417 1169 1396
```



---

---
title: "Bitwise Slides"
layout: "post"
diff: 提高+/省选-
pid: CF2066C
tag: ['动态规划 DP', '离散化', '位运算']
---

# Bitwise Slides

## 题目描述

给定一个数组 $a_1, a_2, \ldots, a_n$，以及三个初始值为零的变量 $P, Q, R$。

你需要按从 $1$ 到 $n$ 的顺序依次处理所有数字 $a_1, a_2, \ldots, a_n$。当处理当前元素 $a_i$ 时，你必须从以下三个操作中任选一个执行：
1. $P := P \oplus a_i$
2. $Q := Q \oplus a_i$
3. $R := R \oplus a_i$

其中 $\oplus$ 表示按位异或操作。

执行操作时必须遵守核心规则：每次操作后，三个数 $P, Q, R$ 必须满足两两不互异。

所有 $n$ 个操作共有 $3^n$ 种可能的执行方式。求其中不违反核心规则的方式数量。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。随后为各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——数组 $a$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$）——数组 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出不违反核心规则的操作方式数量对 $10^9 + 7$ 取模后的结果。

## 说明/提示

第一个测试用例中，存在 3 种合法操作序列：PPP、QQQ、RRR。

第二个测试用例中，存在 9 种合法操作序列：PPPP、PPPQ、PPPR、QQQP、QQQQ、QQQR、RRRP、RRRQ、RRRR。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3
1 7 9
4
179 1 1 179
5
1 2 3 3 2
12
8 2 5 3 9 1 8 12 9 9 9 4
1
1000000000
```

### 输出

```
3
9
39
123
3
```



---

---
title: "Club of Young Aircraft Builders (easy version)"
layout: "post"
diff: 提高+/省选-
pid: CF2066D1
tag: ['动态规划 DP', '组合数学']
---

# Club of Young Aircraft Builders (easy version)

## 题目描述

这是该问题的简单版本。各版本间的区别在于此版本中所有 $a_i = 0$。只有当您解决了该问题的所有版本时才能进行 hack。

有一栋 $n$ 层的建筑物，楼层从下到上编号为 $1$ 至 $n$。每层恰好住着一位居民。

今天全体居民有一个重要目标：共同发射至少 $c$ 架纸飞机。居民们将依次发射飞机。当第 $i$ 层的居民发射一架飞机时，从第 $1$ 层到第 $i$ 层的所有居民都能看到它降落到地面的过程。

如果从第 $i$ 层居民的视角看，已有至少 $c$ 架飞机被发射，则该居民自己不会再发射更多飞机。已知到当天结束时，从每位居民的视角看至少发射了 $c$ 架飞机，且总共发射了 $m$ 架飞机。

您仔细记录了这次快闪活动，记录了每位发射飞机的居民所在楼层。遗憾的是，关于具体是谁发射了某些飞机的信息已经丢失。请找出填补空缺信息使其可信的方案数。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

在此版本的问题中，所有信息均已丢失，整个数组全由空缺构成。

也可能您的记录存在错误，导致无法恢复任何有效信息。此时答案视为 $0$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。随后为各测试用例的描述。

每个测试用例的第一行包含三个整数 $n, c, m$（$1 \le n \le 100$，$1 \le c \le 100$，$c \le m \le n \cdot c$）——建筑物的层数、所需最小飞机数、实际发射的飞机数。

每个测试用例的第二行包含 $m$ 个整数 $a_1, a_2, \ldots, a_m$（$0 \le a_i \le n$）——$a_i$ 表示发射第 $i$ 架飞机的居民所在楼层；$a_i = 0$ 表示空缺。

在此版本的问题中，保证所有 $a_i = 0$。

保证所有测试用例的 $m$ 值之和不超过 $10^4$。

## 输出格式

对于每个测试用例，输出用 $1$ 至 $n$ 填补空缺信息使其可信的方案数对 $10^9 + 7$ 取模后的结果。


## 说明/提示

第一个测试样例中，所有六种可能的填补方案如下：
1. $[1, 1, 3, 3]$
2. $[1, 2, 3, 3]$
3. $[1, 3, 2, 3]$
4. $[2, 1, 3, 3]$
5. $[2, 2, 3, 3]$
6. $[3, 1, 2, 3]$

注意数组 $[2, 3, 1, 3]$ 不是有效方案，因为第三架飞机不可能由第 $1$ 层的居民发射——从他们的视角看，当时已有 $c = 2$ 架飞机被发射。

同样地，数组 $[1, 1, 2, 3]$ 也不是有效方案，因为从第 $3$ 层居民的视角看，仅发射了 $1$ 架飞机，而 $c = 2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
3 2 4
0 0 0 0
5 5 7
0 0 0 0 0 0 0
```

### 输出

```
6
190
```



---

---
title: "Key of Like (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2089C1
tag: ['动态规划 DP', '概率论']
---

# Key of Like (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本之间的区别在于，在这个版本中保证 $$$k = 0$$$。只有当你解决了该问题的所有版本时才能进行 hack。

玩具盒如同装满童年欢愉的冰箱。像脆弱、挣扎、希望……当这样的沉睡者被重新唤醒时，会有什么样的惊喜等待？

M 从母亲那里收到了这个玩具盒作为生日礼物。一位珠宝设计师必定会不遗余力地装饰这件无价杰作：用精美造型的宝石点缀出星空般的天穹。此外，$$$l$$$ 把独特的锁守护着可爱女儿的微型宇宙：一枚花朵造型的发夹、一支磨损的羽毛笔、一个 M 字母形状的气球……每件物品都封存着珍贵的瞬间。

几天前，M 在整理卧室时重新发现了玩具盒，以及一个专为它设计的钥匙环。钥匙环上挂着 $$$(l + k)$$$ 把钥匙，其中 $$$l$$$ 把钥匙能对应地打开 $$$l$$$ 把锁中的一把，而另外 $$$k$$$ 把钥匙只是用于防止暴力破解的仿制品。为了提醒对应关系，M 的母亲为每把钥匙镶嵌了不同类型的宝石。然而，流逝的时光已让 M 的记忆逐渐模糊。

"……所以只能拜托大家了。"M 说着将钥匙环放在桌上。

K 拿起钥匙仔细端详。"这些钥匙的外观无法提供有用信息。恐怕我们必须逐一尝试。"

虽然大家都愿意帮助 M，但没有人有头绪。观察着众人的反应，T 提议："我们来玩个游戏吧。大家轮流尝试钥匙，最终打开最多锁的人最厉害。"

包括 M 在内的 $$$n$$$ 名成员将按固定顺序轮流尝试解锁，直到所有 $$$l$$$ 把锁都被打开。每轮操作中，当前成员只会选择一把钥匙并在恰好一把锁上进行测试。为了尽快打开玩具盒，每位成员都会选择能最大化成功匹配概率的钥匙与锁组合。若存在多个这样的组合，成员会以相等概率随机选择其中之一。显然，若某把锁已与某把钥匙匹配成功，则该锁和钥匙都不会在后续尝试中被再次选择。

假设在最开始时，任意钥匙能打开任意锁的概率均相等。若每个人始终基于所有历史尝试选择最优的钥匙与锁组合，每位成员成功匹配的期望次数分别是多少？

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数 $$$t$$$（$$$1 \le t \le 100$$$）。接下来是每个测试用例的描述。

输入仅一行包含三个整数 $$$n$$$、$$$l$$$、$$$k$$$（$$$1 \leq n \leq 100$$$，$$$1 \leq l \leq 5000$$$，$$$k = 0$$$）——参与游戏的成员数、锁的数量和仿制钥匙的数量。

保证所有测试用例的 $$$l$$$ 之和不超过 $$$5000$$$。

## 输出格式

对于每个测试用例，输出一行包含 $$$n$$$ 个整数 $$$e_1, \ldots, e_n$$$，其中 $$$e_i$$$ 表示第 $$$i$$$ 位成员的期望成功匹配次数，结果对 $$$10^9 + 7$$$ 取模。

形式化地，令 $$$M = 10^9 + 7$$$。可以证明精确答案可以表示为不可约分数 $$$\frac{p}{q}$$$，其中 $$$p$$$ 和 $$$q$$$ 为整数且 $$$q \not \equiv 0 \pmod{M}$$$。输出整数 $$$p \cdot q^{-1} \bmod M$$$。换句话说，输出满足 $$$0 \le x < M$$$ 且 $$$e_i \cdot q \equiv p \pmod{M}$$$ 的整数 $$$e_i$$$。

## 说明/提示

对于第一个测试用例，只有 $$$1$$$ 把锁，因此第一位成员必定用唯一的钥匙打开唯一的锁。

对于第二个测试用例，恰好有 $$$2$$$ 把锁和 $$$2$$$ 把钥匙，每把钥匙对应一把锁。在缺乏额外信息时，第一位成员会以相等概率随机选择钥匙与锁的组合，成功概率为 $$$1/2$$$。

- 若第一位成员成功，第二位成员将用另一把钥匙打开另一把锁。
- 若第一位成员失败，则她选择的钥匙能打开另一把锁，而另一把钥匙必定对应她选择的锁。这一信息将使得第二位和第三位成员都能打开一把锁。

综上，期望成功次数为：

$$ 
\begin{split}
e_1 &= \frac{1}{2} \times 1 + \frac{1}{2} \times 0 = \frac{1}{2} \equiv 500,000,004 \pmod{10^9+7}, \\
e_2 &= \frac{1}{2} \times 1 + \frac{1}{2} \times 1 = 1, \\
e_3 &= \frac{1}{2} \times 0 + \frac{1}{2} \times 1 = \frac{1}{2} \equiv 500,000,004 \pmod{10^9+7}.
\end{split}
$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3 1 0
3 2 0
2 5 0
9 104 0
```

### 输出

```
1 0 0
500000004 1 500000004
200000004 800000008
869203933 991076635 39374313 496894434 9358446 51822059 979588764 523836809 38844739
```



---

---
title: "Gleb and Boating"
layout: "post"
diff: 提高+/省选-
pid: CF2091G
tag: ['动态规划 DP', '广度优先搜索 BFS', '标签465']
---

# Gleb and Boating

## 题目描述

程序员 Gleb 经常访问 IT Campus "NEIMARK" 参加编程训练。

Gleb 不仅是程序员，还是一位著名的划船运动员，因此他选择通过划皮划艇沿河流完成部分通勤路程。假设 Gleb 从点 $0$ 出发，必须到达点 $s$（即沿直线划行 $s$ 米）。为增加挑战性，Gleb 决定不离开线段 $[0, s]$。皮划艇的尺寸可忽略不计。

Gleb 是实力强劲的程序员！初始时他的力量为 $k$。Gleb 的力量直接影响皮划艇的运动：若当前力量为 $x$，则每次划桨可使皮划艇沿当前方向移动 $x$ 米。Gleb 可以调头并继续向相反方向移动，但此操作十分困难，每次调头后力量会减少 $1$。力量永远不会变为 $0$ —— 若当前力量为 $1$，则即使调头后仍保持 $1$。此外，Gleb 不能连续两次调头 —— 每次调头后必须至少移动一次才能再次调头。同理，Gleb 不能在出发后立即调头 —— 必须先进行一次划桨。

Gleb 希望在从点 $0$ 到达点 $s$ 的过程中不离开线段 $[0, s]$ 并尽可能保留最多力量。请帮助他 —— 给定 $s$ 和初始力量 $k$，确定到达点 $s$ 时可能保留的最大力量。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$ ($1 \leq t \leq 100$)。接下来是测试用例描述。

每个测试用例单独一行，包含两个整数 $s$ 和 $k$ ($1 \leq s \leq 10^9$，$1 \leq k \leq 1000$，$k \leq s$)。

保证所有测试用例的 $k$ 之和不超过 $2000$。

## 输出格式

对于每个测试用例，输出 Gleb 在旅程结束时可能保留的最大力量。


## 说明/提示

第一个样例中 Gleb 的一种可能移动方式：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091G/776d3b954c1b6c71e54b3d9667d6f17ccd68b4e7.png)  

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
9 6
10 7
24 2
123456 777
6 4
99 6
10 4
99 4
```

### 输出

```
4
1
2
775
1
4
2
2
```



---

---
title: "Cycling (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2107F1
tag: ['动态规划 DP', '贪心']
---

# Cycling (Easy Version)

## 题目描述

> 这是此问题的简单版本，和其他版本的区别是此版本中 $n\le 5000$，且你不需要对每个前缀都求解。

Leo 骑车去见他的女朋友。在 Leo 的前面有 $n$ 名骑手，从前往后排在第 $i$ 名的骑手的灵活度为 $a_i$。

Leo 将要加速超过前面的所有骑手，他可以执行以下两种操作：
- 当他在骑手 $i$ 后面，骑手 $i+1$ 前面（或 $i=n$）时，付出 $a_i$ 的代价超过骑手 $i$，之后他将在骑手 $i$ 前面，骑手 $i-1$ 后面（如果 $i>1$）；
- 使用他的超级力量交换 $a_i$ 和 $a_j$，代价为 $\vert i-j\vert$。

请你找出超过所有 $n$ 名骑手的最小代价。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 1000)$，表示数据组数。

对于每组数据，第一行一个整数 $n(1\le n\le 5000)$。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le 10^9)$。

保证单个测试点中 $\sum n\le 5000$。

## 输出格式

对于每组数据，输出一行一个整数，表示答案。

## 说明/提示

**样例解释**

第一组数据中，一组操作如下所示：
- 交换 $a_2$ 和 $a_3$，之后 $a=(1,4,2)$，代价为 $1$；
- 超过第 $3$ 名骑手，代价为 $2$；
- 交换 $a_1$ 和 $a_2$，$a=(4,1,2)$，代价为 $1$；
- 超过第 $2$ 名骑手，代价为 $1$；
- 交换 $a_1$ 和 $a_2$，$a=(1,4,2)$，代价为 $1$；
- 超过第 $1$ 名骑手，代价为 $1$。

总代价为 $7$。可以证明这是最小的代价。

第二组数据中如果一直执行“超过”操作，花费为 $4$。可以证明这是最小的代价。

By chenxi2009

## 样例 #1

### 输入

```
4
3
1 2 4
4
1 1 1 1
2
1 2
4
4 1 3 2
```

### 输出

```
7
4
3
8
```



---

---
title: "Binary String Wowee"
layout: "post"
diff: 提高+/省选-
pid: CF2109E
tag: ['动态规划 DP']
---

# Binary String Wowee

## 题目描述

Mouf 觉得主题太无聊了，所以他决定这道题不使用任何主题。

给定一个长度为 $n$ 的二进制$^{\text{∗}}$字符串 $s$。你需要精确执行 $k$ 次以下操作：
- 选择一个下标 $i$（$1 \le i \le n$）满足 $s_i = \mathtt{0}$；
- 然后翻转$^{\text{†}}$所有 $s_j$（$1 \le j \le i$）。

你需要计算执行所有 $k$ 次操作的可能方式数量。

由于答案可能非常大，请输出其对 $998\,244\,353$ 取模的结果。

如果在任何步骤中选择的下标不同，则认为两个操作序列是不同的。

$^{\text{∗}}$ 二进制字符串是指仅由字符 $\mathtt{0}$ 和 $\mathtt{1}$ 组成的字符串。

$^{\text{†}}$ 翻转二进制字符是指将其从 $\mathtt{0}$ 变为 $\mathtt{1}$ 或反之。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 100$）。接下来是测试用例描述。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \le k \le n \le 500$）——分别表示二进制字符串 $s$ 的长度和需要执行操作的次数。

第二行包含一个长度为 $n$ 的二进制字符串 $s$，仅由字符 $\mathtt{0}$ 和 $\mathtt{1}$ 组成。

保证所有测试用例的 $n$ 之和不超过 $500$。

## 输出格式

对于每个测试用例，输出一个整数——表示精确执行 $k$ 次操作的可能方式数量，对 $998\,244\,353$ 取模的结果。


## 说明/提示

**第一个测试用例解释：**
所有可能的操作序列如下：
1. $\mathtt{\color{red}{0}10} \xrightarrow{i = 1} \mathtt{110}$
2. $\mathtt{\color{red}{010}} \xrightarrow{i = 3} \mathtt{101}$

**第二个测试用例解释：**
所有可能的操作序列如下：
1. $\mathtt{\color{red}{0}00} \xrightarrow{i = 1} \mathtt{\color{red}{1}00} \xrightarrow{i = 2} \mathtt{010}$
2. $\mathtt{\color{red}{0}00} \xrightarrow{i = 1} \mathtt{\color{red}{1}00} \xrightarrow{i = 3} \mathtt{011}$
3. $\mathtt{\color{red}{00}0} \xrightarrow{i = 2} \mathtt{\color{red}{11}0} \xrightarrow{i = 3} \mathtt{001}$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3 1
010
3 2
000
5 4
01001
8 8
11001100
20 20
10010110101101010110
```

### 输出

```
2
3
10
27286
915530405
```



---

---
title: "Tree Colorings"
layout: "post"
diff: 提高+/省选-
pid: CF2112E
tag: ['动态规划 DP', '数学']
---

# Tree Colorings

## 题目描述

考虑一棵有根树，每个结点可以被染成蓝色、绿色或黄色。一个染色方案是美丽的，当且仅当：
- 根节点被染成绿色；
- 所有的**蓝色和绿色**结点构成一个点集，点集中的点两两之间的路径上都没有黄色结点；
- 所有的**黄色和绿色**结点构成一个点集，点集中的点两两之间的路径上都没有蓝色结点。

给你一个整数 $m$，问一棵**恰有** $m$ 种美丽的染色方案的有根树最少有多少个结点？

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 10^5)$ 表示数据组数。

对于每组数据，一行一个整数 $m(1\le m\le 5\times 10^5)$。

## 输出格式

对于每组数据，输出一个整数表示答案。特别地，如果不存在一棵恰有 $m$ 种美丽的染色方案的有根树，在这一行输出 $-1$。

## 说明/提示

**样例解释**

我们用 $g$ 表示绿色，用 $b$ 表示蓝色，用 $y$ 表示黄色。

对于第一组数据，考虑一个只有一个结点的树。它有一种美丽的染色方案：根节点为绿色。

对于第二组数据，考虑一个有两个结点的树，根为结点 $1$，它有三种美丽的染色方案：$[g,g],[g,b],[g,y]$。

对于第三组数据，考虑一个有三个结点的链，根为结点 $1$，结点 $2$ 和结点 $1$ 与结点 $3$ 相连，它有五种美丽的染色方案：$[g,g,g],[g,g,b],[g,g,y],[g,b,b],[g,y,y]$。

对于第五组数据，考虑一个有三个结点的树，根为结点 $1$，另外两个结点和它相连，它有九种美丽的染色方案：$[g,g,g],[g,g,b],[g,g,y],[g,b,g],[g,b,b],[g,b,y],[g,y,g],[g,y,b],[g,y,y]$。

## 样例 #1

### 输入

```
5
1
3
5
7
9
```

### 输出

```
1
2
3
4
3
```



---

---
title: "Ice Baby"
layout: "post"
diff: 提高+/省选-
pid: CF2121H
tag: ['动态规划 DP', '线段树', '动态规划优化', '标签504']
---

# Ice Baby

## 题目描述

The longest non-decreasing subsequence of an array of integers $ a_1, a_2, \ldots, a_n $ is the longest sequence of indices $ 1 \leq i_1 < i_2 < \ldots < i_k \leq n $ such that $ a_{i_1} \leq a_{i_2} \leq \ldots \leq a_{i_k} $ . The length of the sequence is defined as the number of elements in the sequence. For example, the length of the longest non-decreasing subsequence of the array $ a = [3, 1, 4, 1, 2] $ is $ 3 $ .

You are given two arrays of integers $ l_1, l_2, \ldots, l_n $ and $ r_1, r_2, \ldots, r_n $ . For each $ 1 \le k \le n $ , solve the following problem:

- Consider all arrays of integers $ a $ of length $ k $ , such that for each $ 1 \leq i \leq k $ , it holds that $ l_i \leq a_i \leq r_i $ . Find the maximum length of the longest non-decreasing subsequence among all such arrays.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the arrays $ l $ and $ r $ .

The next $ n $ lines of each test case contain two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i \leq r_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers: for each $ k $ from $ 1 $ to $ n $ , output the maximum length of the longest non-decreasing subsequence among all suitable arrays.

## 说明/提示

In the first test case, the only possible array is $ a = [1] $ . The length of the longest non-decreasing subsequence of this array is $ 1 $ .

In the second test case, for $ k = 2 $ , no matter how we choose the values of $ a_1 $ and $ a_2 $ , the condition $ a_1 > a_2 $ will always hold. Therefore, the answer for $ k = 2 $ will be $ 1 $ .

In the third test case, for $ k = 4 $ , we can choose the array $ a = [5, 3, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 3 $ .

In the fourth test case, for $ k = 8 $ , we can choose the array $ a = [7, 5, 3, 5, 3, 3, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 5 $ .

In the fifth test case, for $ k = 5 $ , we can choose the array $ a = [2, 8, 5, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 3 $ .

## 样例 #1

### 输入

```
6
1
1 1
2
3 4
1 2
4
4 5
3 4
1 3
3 3
8
6 8
4 6
3 5
5 5
3 4
1 3
2 4
3 3
5
1 2
6 8
4 5
2 3
3 3
11
35 120
66 229
41 266
98 164
55 153
125 174
139 237
30 72
138 212
109 123
174 196
```

### 输出

```
1 
1 1 
1 2 2 3 
1 2 2 3 3 3 4 5 
1 2 2 2 3 
1 2 3 4 5 6 7 7 8 8 9
```



---

---
title: "Table"
layout: "post"
diff: 提高+/省选-
pid: CF232B
tag: ['动态规划 DP', '组合数学']
---

# Table

## 题目描述

John Doe has an $ n×m $ table. John Doe can paint points in some table cells, not more than one point in one table cell. John Doe wants to use such operations to make each square subtable of size $ n×n $ have exactly $ k $ points.

John Doe wondered, how many distinct ways to fill the table with points are there, provided that the condition must hold. As this number can be rather large, John Doe asks to find its remainder after dividing by $ 1000000007 $ $ (10^{9}+7) $ .

You should assume that John always paints a point exactly in the center of some cell. Two ways to fill a table are considered distinct, if there exists a table cell, that has a point in one way and doesn't have it in the other.

## 输入格式

A single line contains space-separated integers $ n $ , $ m $ , $ k $ ( $ 1<=n<=100; n<=m<=10^{18}; 0<=k<=n^{2} $ ) — the number of rows of the table, the number of columns of the table and the number of points each square must contain.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 输出格式

In a single line print a single integer — the remainder from dividing the described number of ways by $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

Let's consider the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF232B/8876a3223960f71627c5d6c6a4c6ddb988dcaef6.png) The gray area belongs to both $ 5×5 $ squares. So, if it has one point, then there shouldn't be points in any other place. If one of the white areas has a point, then the other one also must have a point. Thus, there are about $ 20 $ variants, where the point lies in the gray area and $ 25 $ variants, where each of the white areas contains a point. Overall there are $ 45 $ variants.

## 样例 #1

### 输入

```
5 6 1

```

### 输出

```
45
```



---

---
title: "Anagram"
layout: "post"
diff: 提高+/省选-
pid: CF254C
tag: ['字符串', '动态规划 DP']
---

# Anagram

## 题目描述

String $ x $ is an anagram of string $ y $ , if we can rearrange the letters in string $ x $ and get exact string $ y $ . For example, strings "DOG" and "GOD" are anagrams, so are strings "BABA" and "AABB", but strings "ABBAC" and "CAABA" are not.

You are given two strings $ s $ and $ t $ of the same length, consisting of uppercase English letters. You need to get the anagram of string $ t $ from string $ s $ . You are permitted to perform the replacing operation: every operation is replacing some character from the string $ s $ by any other character. Get the anagram of string $ t $ in the least number of replacing operations. If you can get multiple anagrams of string $ t $ in the least number of operations, get the lexicographically minimal one.

The lexicographic order of strings is the familiar to us "dictionary" order. Formally, the string $ p $ of length $ n $ is lexicographically smaller than string $ q $ of the same length, if $ p_{1}=q_{1} $ , $ p_{2}=q_{2} $ , ..., $ p_{k-1}=q_{k-1} $ , $ p_{k}&lt;q_{k} $ for some $ k $ ( $ 1<=k<=n $ ). Here characters in the strings are numbered from 1. The characters of the strings are compared in the alphabetic order.

## 输入格式

The input consists of two lines. The first line contains string $ s $ , the second line contains string $ t $ . The strings have the same length (from $ 1 $ to $ 10^{5} $ characters) and consist of uppercase English letters.

## 输出格式

In the first line print $ z $ — the minimum number of replacement operations, needed to get an anagram of string $ t $ from string $ s $ . In the second line print the lexicographically minimum anagram that could be obtained in $ z $ operations.

## 说明/提示

The second sample has eight anagrams of string $ t $ , that can be obtained from string $ s $ by replacing exactly two letters: "ADBADC", "ADDABC", "CDAABD", "CDBAAD", "CDBADA", "CDDABA", "DDAABC", "DDBAAC". These anagrams are listed in the lexicographical order. The lexicographically minimum anagram is "ADBADC".

## 样例 #1

### 输入

```
ABA
CBA

```

### 输出

```
1
ABC

```

## 样例 #2

### 输入

```
CDBABC
ADCABD

```

### 输出

```
2
ADBADC

```



---

---
title: "Yaroslav and Two Strings"
layout: "post"
diff: 提高+/省选-
pid: CF296B
tag: ['动态规划 DP', '容斥原理']
---

# Yaroslav and Two Strings

## 题目描述

Yaroslav thinks that two strings $ s $ and $ w $ , consisting of digits and having length $ n $ are non-comparable if there are two numbers, $ i $ and $ j $ $ (1<=i,j<=n) $ , such that $ s_{i}&gt;w_{i} $ and $ s_{j}&lt;w_{j} $ . Here sign $ s_{i} $ represents the $ i $ -th digit of string $ s $ , similarly, $ w_{j} $ represents the $ j $ -th digit of string $ w $ .

A string's template is a string that consists of digits and question marks ("?").

Yaroslav has two string templates, each of them has length $ n $ . Yaroslav wants to count the number of ways to replace all question marks by some integers in both templates, so as to make the resulting strings incomparable. Note that the obtained strings can contain leading zeroes and that distinct question marks can be replaced by distinct or the same integers.

Help Yaroslav, calculate the remainder after dividing the described number of ways by $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ — the length of both templates. The second line contains the first template — a string that consists of digits and characters "?". The string's length equals $ n $ . The third line contains the second template in the same format.

## 输出格式

In a single line print the remainder after dividing the answer to the problem by number $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

The first test contains no question marks and both strings are incomparable, so the answer is $ 1 $ .

The second test has no question marks, but the given strings are comparable, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
2
90
09

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
11
55

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5
?????
?????

```

### 输出

```
993531194

```



---

---
title: "Book of Evil"
layout: "post"
diff: 提高+/省选-
pid: CF337D
tag: ['动态规划 DP', '图论']
---

# Book of Evil

## 题目描述

Paladin Manao caught the trail of the ancient Book of Evil in a swampy area. This area contains $ n $ settlements numbered from 1 to $ n $ . Moving through the swamp is very difficult, so people tramped exactly $ n-1 $ paths. Each of these paths connects some pair of settlements and is bidirectional. Moreover, it is possible to reach any settlement from any other one by traversing one or several paths.

The distance between two settlements is the minimum number of paths that have to be crossed to get from one settlement to the other one. Manao knows that the Book of Evil has got a damage range $ d $ . This means that if the Book of Evil is located in some settlement, its damage (for example, emergence of ghosts and werewolves) affects other settlements at distance $ d $ or less from the settlement where the Book resides.

Manao has heard of $ m $ settlements affected by the Book of Evil. Their numbers are $ p_{1},p_{2},...,p_{m} $ . Note that the Book may be affecting other settlements as well, but this has not been detected yet. Manao wants to determine which settlements may contain the Book. Help him with this difficult task.

## 输入格式

The first line contains three space-separated integers $ n $ , $ m $ and $ d $ ( $ 1<=m<=n<=100000; 0<=d<=n-1 $ ). The second line contains $ m $ distinct space-separated integers $ p_{1},p_{2},...,p_{m} $ ( $ 1<=p_{i}<=n $ ). Then $ n-1 $ lines follow, each line describes a path made in the area. A path is described by a pair of space-separated integers $ a_{i} $ and $ b_{i} $ representing the ends of this path.

## 输出格式

Print a single number — the number of settlements that may contain the Book of Evil. It is possible that Manao received some controversial information and there is no settlement that may contain the Book. In such case, print 0.

## 说明/提示

Sample 1. The damage range of the Book of Evil equals 3 and its effects have been noticed in settlements 1 and 2. Thus, it can be in settlements 3, 4 or 5.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337D/bb5982168a46056c0b6c7bf34dd6accd73b10df3.png)

## 样例 #1

### 输入

```
6 2 3
1 2
1 5
2 3
3 4
4 5
5 6

```

### 输出

```
3

```



---

---
title: "Iahub and Permutations"
layout: "post"
diff: 提高+/省选-
pid: CF340E
tag: ['动态规划 DP', '容斥原理', '逆元']
---

# Iahub and Permutations

## 题目描述

Iahub is so happy about inventing bubble sort graphs that he's staying all day long at the office and writing permutations. Iahubina is angry that she is no more important for Iahub. When Iahub goes away, Iahubina comes to his office and sabotage his research work.

The girl finds an important permutation for the research. The permutation contains $ n $ distinct integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ $ (1<=a_{i}<=n) $ . She replaces some of permutation elements with -1 value as a revenge.

When Iahub finds out his important permutation is broken, he tries to recover it. The only thing he remembers about the permutation is it didn't have any fixed point. A fixed point for a permutation is an element $ a_{k} $ which has value equal to $ k $ $ (a_{k}=k) $ . Your job is to proof to Iahub that trying to recover it is not a good idea. Output the number of permutations which could be originally Iahub's important permutation, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=2000 $ ). On the second line, there are $ n $ integers, representing Iahub's important permutation after Iahubina replaces some values with -1.

It's guaranteed that there are no fixed points in the given permutation. Also, the given sequence contains at least two numbers -1 and each positive number occurs in the sequence at most once. It's guaranteed that there is at least one suitable permutation.

## 输出格式

Output a single integer, the number of ways Iahub could recover his permutation, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

For the first test example there are two permutations with no fixed points are \[2, 5, 4, 3, 1\] and \[5, 1, 4, 3, 2\]. Any other permutation would have at least one fixed point.

## 样例 #1

### 输入

```
5
-1 -1 4 3 -1

```

### 输出

```
2

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

---
title: "Robot Control"
layout: "post"
diff: 提高+/省选-
pid: CF346D
tag: ['动态规划 DP', '最短路']
---

# Robot Control

## 题目描述

The boss of the Company of Robot is a cruel man. His motto is "Move forward Or Die!". And that is exactly what his company's product do. Look at the behavior of the company's robot when it is walking in the directed graph. This behavior has been called "Three Laws of Robotics":

- Law 1. The Robot will destroy itself when it visits a vertex of the graph which it has already visited.
- Law 2. The Robot will destroy itself when it has no way to go (that is when it reaches a vertex whose out-degree is zero).
- Law 3. The Robot will move randomly when it has multiple ways to move (that is when it reach a vertex whose out-degree is more than one). Of course, the robot can move only along the directed edges of the graph.

Can you imagine a robot behaving like that? That's why they are sold at a very low price, just for those who are short of money, including mzry1992, of course. mzry1992 has such a robot, and she wants to move it from vertex $ s $ to vertex $ t $ in a directed graph safely without self-destruction. Luckily, she can send her robot special orders at each vertex. A special order shows the robot which way to move, if it has multiple ways to move (to prevent random moving of the robot according to Law 3). When the robot reaches vertex $ t $ , mzry1992 takes it off the graph immediately. So you can see that, as long as there exists a path from $ s $ to $ t $ , she can always find a way to reach the goal (whatever the vertex $ t $ has the outdegree of zero or not).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF346D/70cbc1b898581d5fe7e403c459e5024fa4aa2e72.png) Sample 2 However, sending orders is expensive, so your task is to find the minimum number of orders mzry1992 needs to send in the worst case. Please note that mzry1992 can give orders to the robot while it is walking on the graph. Look at the first sample to clarify that part of the problem.

## 输入格式

The first line contains two integers $ n $ ( $ 1<=n<=10^{6} $ ) — the number of vertices of the graph, and $ m $ ( $ 1<=m<=10^{6} $ ) — the number of edges. Then $ m $ lines follow, each with two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ; $ v_{i}≠u_{i} $ ), these integers denote that there is a directed edge from vertex $ u_{i} $ to vertex $ v_{i} $ . The last line contains two integers $ s $ and $ t $ ( $ 1<=s,t<=n $ ).

It is guaranteed that there are no multiple edges and self-loops.

## 输出格式

If there is a way to reach a goal, print the required minimum number of orders in the worst case. Otherwise, print -1.

## 说明/提示

Consider the first test sample. Initially the robot is on vertex 1. So, on the first step the robot can go to vertex 2 or 3. No matter what vertex the robot chooses, mzry1992 must give an order to the robot. This order is to go to vertex 4. If mzry1992 doesn't give an order to the robot at vertex 2 or 3, the robot can choose the "bad" outgoing edge (return to vertex 1) according Law 3. So, the answer is one.

## 样例 #1

### 输入

```
4 6
1 2
2 1
1 3
3 1
2 4
3 4
1 4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 5
1 2
2 1
1 3
2 4
3 4
1 4

```

### 输出

```
1

```



---

---
title: "Levko and Array"
layout: "post"
diff: 提高+/省选-
pid: CF360B
tag: ['动态规划 DP', '二分']
---

# Levko and Array

## 题目描述

Levko has an array that consists of integers: $ a_{1},a_{2},...\ ,a_{n} $ . But he doesn’t like this array at all.

Levko thinks that the beauty of the array $ a $ directly depends on value $ c(a) $ , which can be calculated by the formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF360B/bc46a8f9d72cc21bf5d1738220033f31da7db825.png) The less value $ c(a) $ is, the more beautiful the array is.It’s time to change the world and Levko is going to change his array for the better. To be exact, Levko wants to change the values of at most $ k $ array elements (it is allowed to replace the values by any integers). Of course, the changes should make the array as beautiful as possible.

Help Levko and calculate what minimum number $ c(a) $ he can reach.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=2000 $ ). The second line contains space-separated integers $ a_{1},a_{2},...\ ,a_{n} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ).

## 输出格式

A single number — the minimum value of $ c(a) $ Levko can get.

## 说明/提示

In the first sample Levko can change the second and fourth elements and get array: $ 4 $ , $ 4 $ , $ 4 $ , $ 4 $ , $ 4 $ .

In the third sample he can get array: $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ .

## 样例 #1

### 输入

```
5 2
4 7 4 7 4

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3 1
-100 0 100

```

### 输出

```
100

```

## 样例 #3

### 输入

```
6 3
1 2 3 7 8 9

```

### 输出

```
1

```



---

---
title: "Sereja and Intervals"
layout: "post"
diff: 提高+/省选-
pid: CF367E
tag: ['动态规划 DP']
---

# Sereja and Intervals

## 题目描述

Sereja is interested in intervals of numbers, so he has prepared a problem about intervals for you. An interval of numbers is a pair of integers $ [l,r] $ $ (1<=l<=r<=m) $ . Interval $ [l_{1},r_{1}] $ belongs to interval $ [l_{2},r_{2}] $ if the following condition is met: $ l_{2}<=l_{1}<=r_{1}<=r_{2} $ .

Sereja wants to write out a sequence of $ n $ intervals $ [l_{1},r_{1}] $ , $ [l_{2},r_{2}] $ , $ ... $ , $ [l_{n},r_{n}] $ on a piece of paper. At that, no interval in the sequence can belong to some other interval of the sequence. Also, Sereja loves number $ x $ very much and he wants some (at least one) interval in the sequence to have $ l_{i}=x $ . Sereja wonders, how many distinct ways to write such intervals are there?

Help Sereja and find the required number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ .

Two ways are considered distinct if there is such $ j $ $ (1<=j<=n) $ , that the $ j $ -th intervals in two corresponding sequences are not equal.

## 输入格式

The first line contains integers $ n $ , $ m $ , $ x $ $ (1<=n·m<=100000,1<=x<=m) $ — the number of segments in the sequence, the constraints on the numbers in segments and Sereja's favourite number.

## 输出格式

In a single line print the answer modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In third example next sequences will be correct: $ {[1,1],[3,3]} $ , $ {[1,2],[3,3]} $ , $ {[2,2],[3,3]} $ , $ {[3,3],[1,1]} $ , $ {[3,3],[2,2]} $ , $ {[3,3],[1,2]} $ .

## 样例 #1

### 输入

```
1 1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 5 1

```

### 输出

```
240

```

## 样例 #3

### 输入

```
2 3 3

```

### 输出

```
6

```



---

---
title: "Valera and Fools"
layout: "post"
diff: 提高+/省选-
pid: CF369D
tag: ['动态规划 DP', '广度优先搜索 BFS']
---

# Valera and Fools

## 题目描述

One fine morning, $ n $ fools lined up in a row. After that, they numbered each other with numbers from $ 1 $ to $ n $ , inclusive. Each fool got a unique number. The fools decided not to change their numbers before the end of the fun.

Every fool has exactly $ k $ bullets and a pistol. In addition, the fool number $ i $ has probability of $ p_{i} $ (in percent) that he kills the fool he shoots at.

The fools decided to have several rounds of the fun. Each round of the fun looks like this: each currently living fool shoots at another living fool with the smallest number (a fool is not stupid enough to shoot at himself). All shots of the round are perfomed at one time (simultaneously). If there is exactly one living fool, he does not shoot.

Let's define a situation as the set of numbers of all the living fools at the some time. We say that a situation is possible if for some integer number $ j $ ( $ 0<=j<=k $ ) there is a nonzero probability that after $ j $ rounds of the fun this situation will occur.

Valera knows numbers $ p_{1},p_{2},...,p_{n} $ and $ k $ . Help Valera determine the number of distinct possible situations.

## 输入格式

The first line contains two integers $ n,k $ ( $ 1<=n,k<=3000 $ ) — the initial number of fools and the number of bullets for each fool.

The second line contains $ n $ integers $ p_{1},p_{2},...,p_{n} $ ( $ 0<=p_{i}<=100 $ ) — the given probabilities (in percent).

## 输出格式

Print a single number — the answer to the problem.

## 说明/提示

In the first sample, any situation is possible, except for situation $ {1,2} $ .

In the second sample there is exactly one fool, so he does not make shots.

In the third sample the possible situations are $ {1,2} $ (after zero rounds) and the "empty" situation $ {} $ (after one round).

In the fourth sample, the only possible situation is $ {1,2,3} $ .

## 样例 #1

### 输入

```
3 3
50 50 50

```

### 输出

```
7

```

## 样例 #2

### 输入

```
1 1
100

```

### 输出

```
1

```

## 样例 #3

### 输入

```
2 1
100 100

```

### 输出

```
2

```

## 样例 #4

### 输入

```
3 3
0 0 0

```

### 输出

```
1

```



---

---
title: "Roman and Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF401D
tag: ['动态规划 DP', '枚举', '状态合并', '进制', '构造']
---

# Roman and Numbers

## 题目描述

Roman is a young mathematician, very famous in Uzhland. Unfortunately, Sereja doesn't think so. To make Sereja change his mind, Roman is ready to solve any mathematical problem. After some thought, Sereja asked Roma to find, how many numbers are close to number $ n $ , modulo $ m $ .

Number $ x $ is considered close to number $ n $ modulo $ m $ , if:

- it can be obtained by rearranging the digits of number $ n $ ,
- it doesn't have any leading zeroes,
- the remainder after dividing number $ x $ by $ m $ equals 0.

Roman is a good mathematician, but the number of such numbers is too huge for him. So he asks you to help him.

## 输入格式

The first line contains two integers: $ n $ $ (1<=n&lt;10^{18}) $ and $ m $ $ (1<=m<=100) $ .

## 输出格式

In a single line print a single integer — the number of numbers close to number $ n $ modulo $ m $ .

## 说明/提示

In the first sample the required numbers are: 104, 140, 410.

In the second sample the required number is 232.

## 样例 #1

### 输入

```
104 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
223 4

```

### 输出

```
1

```

## 样例 #3

### 输入

```
7067678 8

```

### 输出

```
47

```



---

---
title: "2048"
layout: "post"
diff: 提高+/省选-
pid: CF413D
tag: ['动态规划 DP', '状态合并']
---

# 2048

## 题目描述

The programmers from the R2 company love playing 2048. One day, they decided to invent their own simplified version of this game — $ 2^{k} $ on a stripe.

Imagine an infinite in one direction stripe, consisting of unit squares (the side of each square is equal to the height of the stripe). Each square can either be empty or contain some number.

Initially, all squares are empty. Then at infinity one of the unit squares number 2 or 4 appears. Then the player presses a button once, and the appeared number begins to move towards the beginning of the stripe. Let's assume that some number $ x $ moves to the beginning of the stripe, then it will stop if:

1. it either gets in the first square of the stripe;
2. or it is in the square that is preceded by a square with number $ y $ $ (y≠x) $ . But if number $ x $ at some point of time gets to the square with the same number then both numbers add to each other and result in $ 2x $ . The new number $ 2x $ continues moving to the beginning of the stripe by the same rules.

After the final stop of the number moving process, the infinity gets a new number 2 or 4 and the process repeats. Read the notes to the test samples to better understand the moving strategy.

I guess you've understood that the game progress fully depends on the order in which numbers 2 and 4 appear. Let's look at some sequence of numbers 2 and 4 in the game. We assume that the sequence is winning if it results in at least one square getting the number greater or equal than $ 2^{k} $ .

The goal of the game is to make up a winning sequence of $ n $ numbers. But not everything is so simple, some numbers in the sequence are identified beforehand. You are given a sequence consisting of numbers 0, 2, 4. Count how many ways there are to replace each 0 of the sequence with 2 or 4 to get a winning sequence.

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (1<=n<=2000; 3<=k<=11) $ . The next line contains sequence of $ n $ integers, each of them is either 0, or 2, or 4.

## 输出格式

Print a single integer — the number of ways to replace zeroes by numbers 2 or 4 to get a winning sequence. As this number can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

Consider the first example. The beginning of the strip will look as follows:

2 $ → $ 4 $ → $ 8 $ → $ 8 2 $ → $ 8 4 $ → $ 8 4 2 $ → $ 16.

To better understand the game, you can see the original game on http://gabrielecirulli.github.io/2048/. Please note that the game that is described on the strip is slightly different from the original game (when the two numbers add up in the original game, they do not keep moving). Be careful, the game is addictive, there isn't much time for the contest!

## 样例 #1

### 输入

```
7 4
2 2 4 2 2 2 2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1 3
0

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2 3
0 4

```

### 输出

```
1

```

## 样例 #4

### 输入

```
5 4
2 0 0 4 4

```

### 输出

```
2

```



---

---
title: "Sereja and Sets"
layout: "post"
diff: 提高+/省选-
pid: CF425E
tag: ['动态规划 DP']
---

# Sereja and Sets

## 题目描述

对于一个有 $m$ 条线段的集合 $S$ 来说，定义函数 $f(S)$ 为你最多可以从这个集合中选择多少线段使得他们都不相交。端点重合也算相交。线段的右端点都小于等于 $n$。

对于给定的 $n,k$，求出有多少个满足条件的 $S$ 满足 $f(S)=k$。

## 输入格式

输入仅一行，$n,k$。$(1\le n\le 500,\ \ 0\le k\le 500)$。

## 输出格式

输出一行一个正整数，表示答案。对 $10^9+7$ 取模。

## 样例 #1

### 输入

```
3 1

```

### 输出

```
23

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
32

```

## 样例 #3

### 输入

```
2 0

```

### 输出

```
1

```

## 样例 #4

### 输入

```
2 2

```

### 输出

```
2

```



---

---
title: "Kindergarten"
layout: "post"
diff: 提高+/省选-
pid: CF484D
tag: ['动态规划 DP', '贪心']
---

# Kindergarten

## 题目描述

In a kindergarten, the children are being divided into groups. The teacher put the children in a line and associated each child with his or her integer charisma value. Each child should go to exactly one group. Each group should be a nonempty segment of consecutive children of a line. A group's sociability is the maximum difference of charisma of two children in the group (in particular, if the group consists of one child, its sociability equals a zero).

The teacher wants to divide the children into some number of groups in such way that the total sociability of the groups is maximum. Help him find this value.

## 输入格式

The first line contains integer $n$ — the number of children in the line ($1\le n\le 10^6$).

The second line contains $n$ integers $a_i$ — the charisma of the $i$-th child ($-10^9\le a_i\le 10^9$).

## 输出格式

Print the maximum possible total sociability of all groups.

## 说明/提示

In the first test sample one of the possible variants of an division is following: the first three children form a group with sociability 2, and the two remaining children form a group with sociability 1.

In the second test sample any division leads to the same result, the sociability will be equal to 0 in each group.

## 样例 #1

### 输入

```
5
1 2 3 1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
3 3 3

```

### 输出

```
0

```



---

---
title: "LIS of Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF486E
tag: ['动态规划 DP', '二分', '枚举']
---

# LIS of Sequence

## 题目描述

# 题意：
给你一个长度为n的序列a1,a2,...,an，你需要把这n个元素分成三类：1，2，3：

1:所有的最长上升子序列都不包含这个元素

2:有但非所有的最长上升子序列包含这个元素

3:所有的最长上升子序列都包含这个元素

## 输入格式

第一行包含一个正整数n，表示序列的长度。第二行包含n个正整数a1,a2,...,an，表示序列中的元素。

## 输出格式

一行，包含一个长度为n的、由1,2,3三种数字组成的字符串，第i个数字表示ai所属类别。

## 说明/提示

1≤n≤10^5

1≤ai≤10^5

## 样例 #1

### 输入

```
1
4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1 3 2 5

```

### 输出

```
3223

```

## 样例 #3

### 输入

```
4
1 5 2 3

```

### 输出

```
3133

```



---

---
title: "The Maths Lecture"
layout: "post"
diff: 提高+/省选-
pid: CF507D
tag: ['动态规划 DP', '数位 DP']
---

# The Maths Lecture

## 题目描述

Amr doesn't like Maths as he finds it really boring, so he usually sleeps in Maths lectures. But one day the teacher suspected that Amr is sleeping and asked him a question to make sure he wasn't.

First he gave Amr two positive integers $ n $ and $ k $ . Then he asked Amr, how many integer numbers $ x&gt;0 $ exist such that:

- Decimal representation of $ x $ (without leading zeroes) consists of exactly $ n $ digits;
- There exists some integer $ y&gt;0 $ such that: 
  - ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507D/a168a0f3214943d3090a4c18ee0075fe3a3849dd.png);
  - decimal representation of $ y $ is a suffix of decimal representation of $ x $ .

As the answer to this question may be pretty huge the teacher asked Amr to output only its remainder modulo a number $ m $ .

Can you help Amr escape this embarrassing situation?

## 输入格式

Input consists of three integers $ n,k,m $ ( $ 1<=n<=1000 $ , $ 1<=k<=100 $ , $ 1<=m<=10^{9} $ ).

## 输出格式

Print the required number modulo $ m $ .

## 说明/提示

A suffix of a string $ S $ is a non-empty string that can be obtained by removing some number (possibly, zero) of first characters from $ S $ .

## 样例 #1

### 输入

```
1 2 1000

```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 2 1000

```

### 输出

```
45
```

## 样例 #3

### 输入

```
5 3 1103

```

### 输出

```
590
```



---

---
title: "Progress Monitoring"
layout: "post"
diff: 提高+/省选-
pid: CF509F
tag: ['动态规划 DP', '深度优先搜索 DFS']
---

# Progress Monitoring

## 题目描述

### 题面翻译

编程老师$Dmitry Olegovich$（以下简称小$D$）准备在一次考试中出以下题目：
**以邻接矩阵的方式给定一颗树，求下面这段伪代码的输出结果**。

```
used[1 ... n] = {0, ..., 0};

procedure dfs(v):
    print v;
    used[v] = 1;
    for i = 1, 2, ..., n:
        if (a[v][i] == 1 and used[i] == 0):
            dfs(i);

dfs(1);
```

为了简化测试结果的检查过程 ~~（其实就是懒）~~ ，小 $D$ 决定创建一棵树 $T$ ，使得结果是他最喜欢的序列 $b$ 。不过，小 $D$ 不想为学生用相同的树作为输入（这意味着他们可能会作弊）。**所以小 $D$ 试图找出不同的树 $T$ 的数量，以便以 $T$ 作为输入运行上述伪代码的结果恰好是序列 $b$ ，答案对$10 ^9+7$取模**。

（两棵树“不同”的定义：它们的邻接矩阵不相同）

### 题面简述

见题面翻译中加粗部分。

## 输入格式

第一行一个整数 $n$，代表题目中序列 $b$ 的长度。

第二行 $n$ 个整数，表示序列 $b$（题目确保这是一个$1 \sim n$的排列，而且 $b_1=1$）。

## 输出格式

一行一个整数表示答案，意思如题面所述。

## 说明/提示

$1\le n \le 500$

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
1 3 2

```

### 输出

```
1

```



---

---
title: "Darth Vader and Tree"
layout: "post"
diff: 提高+/省选-
pid: CF514E
tag: ['动态规划 DP', '动态规划优化', '矩阵加速']
---

# Darth Vader and Tree

## 题目描述

When Darth Vader gets bored, he sits down on the sofa, closes his eyes and thinks of an infinite rooted tree where each node has exactly $ n $ sons, at that for each node, the distance between it an its $ i $ -th left child equals to $ d_{i} $ . The Sith Lord loves counting the number of nodes in the tree that are at a distance at most $ x $ from the root. The distance is the sum of the lengths of edges on the path between nodes.

But he has got used to this activity and even grew bored of it. 'Why does he do that, then?' — you may ask. It's just that he feels superior knowing that only he can solve this problem.

Do you want to challenge Darth Vader himself? Count the required number of nodes. As the answer can be rather large, find it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains two space-separated integers $ n $ and $ x $ ( $ 1<=n<=10^{5},0<=x<=10^{9} $ ) — the number of children of each node and the distance from the root within the range of which you need to count the nodes.

The next line contains $ n $ space-separated integers $ d_{i} $ ( $ 1<=d_{i}<=100 $ ) — the length of the edge that connects each node with its $ i $ -th child.

## 输出格式

Print a single number — the number of vertexes in the tree at distance from the root equal to at most $ x $ .

## 说明/提示

Pictures to the sample (the yellow color marks the nodes the distance to which is at most three)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514E/dfa75ce6cc0df1087a16e02cadbd273a08641d03.png)

## 样例 #1

### 输入

```
3 3
1 2 3

```

### 输出

```
8

```



---

---
title: "Gerald and Giant Chess"
layout: "post"
diff: 提高+/省选-
pid: CF559C
tag: ['动态规划 DP', '组合数学']
---

# Gerald and Giant Chess

## 题目描述

Giant chess is quite common in Geraldion. We will not delve into the rules of the game, we'll just say that the game takes place on an $ h×w $ field, and it is painted in two colors, but not like in chess. Almost all cells of the field are white and only some of them are black. Currently Gerald is finishing a game of giant chess against his friend Pollard. Gerald has almost won, and the only thing he needs to win is to bring the pawn from the upper left corner of the board, where it is now standing, to the lower right corner. Gerald is so confident of victory that he became interested, in how many ways can he win?

The pawn, which Gerald has got left can go in two ways: one cell down or one cell to the right. In addition, it can not go to the black cells, otherwise the Gerald still loses. There are no other pawns or pieces left on the field, so that, according to the rules of giant chess Gerald moves his pawn until the game is over, and Pollard is just watching this process.

## 输入格式

The first line of the input contains three integers: $ h,w,n $ — the sides of the board and the number of black cells ( $ 1<=h,w<=10^{5},1<=n<=2000 $ ).

Next $ n $ lines contain the description of black cells. The $ i $ -th of these lines contains numbers $ r_{i},c_{i} $ ( $ 1<=r_{i}<=h,1<=c_{i}<=w $ ) — the number of the row and column of the $ i $ -th cell.

It is guaranteed that the upper left and lower right cell are white and all cells in the description are distinct.

## 输出格式

Print a single line — the remainder of the number of ways to move Gerald's pawn from the upper left to the lower right corner modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
3 4 2
2 2
2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
100 100 3
15 16
16 15
99 88

```

### 输出

```
545732279

```



---

---
title: "Bindian Signalizing"
layout: "post"
diff: 提高+/省选-
pid: CF5E
tag: ['动态规划 DP', '递推', '栈']
---

# Bindian Signalizing

## 题目描述

**题面大意**

给定一个圆和圆弧上的 $n$ 座山，每座山上有一名看守员，若连接两名看守员的圆弧（注：圆弧有左右两条，任意一条满足即可）两条中没有比（这两个看守员所在的）两座山中任何一座更高的山，则这两名看守人彼此能看到各自的信号。现在给定 $n$ 座山的高度，求能够看到彼此信号的成对看守人的数量

## 输入格式

输入数据的第一行包含一个整数 $n$（$3\le n\le10^6$），表示该圆圈上的山丘数量。

第二行包含 $n$ 个数字整数表示山的高度（按顺时针顺序排列）。所有的高度介于 $1$ 和 $10^9$ 之间

## 输出格式

一个整数，表示答案

## 样例 #1

### 输入

```
5
1 2 4 5 3

```

### 输出

```
7

```



---

---
title: "Wet Shark and Blocks"
layout: "post"
diff: 提高+/省选-
pid: CF621E
tag: ['动态规划 DP', '矩阵乘法', '构造']
---

# Wet Shark and Blocks

## 题目描述

有 $b$ 个格子，每个格子有 $n$ 个数字，各个格子里面的数字都是相同的. 求从 $b$ 个格子中各取一个数字, 构成一个 $b$ 位数, 使得这个 $b$ 位数模 $x$ 为 $k$ 的方案数（同一格子内相同的数字算不同方案）.答案对 $1\times 10^9+7$ 取模.

## 输入格式

第一行有4个整数 $n,b,k,x$ ,其中 $2\leq n\leq 50000,1\leq b\leq 10^{9},0\leq k< x\leq 100,x\ge2$ 
第二行有 $n$ 个数, 为每个格子里面的数字(每个格子里面的数字都是相同的.)

## 输出格式

即从每个块中选择一个数构成一个大数, 使得其模x为k的方案数对 $1\times 10^9+7$ 取模.
注意:

样例二中没有一种方案使得模2为1
样例三中11,13,21,23,31,33满足模2余1.

感谢@aiyougege 提供的翻译

## 样例 #1

### 输入

```
12 1 5 10
3 5 6 7 8 9 5 1 1 1 1 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 2 1 2
6 2 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 2 1 2
3 1 2

```

### 输出

```
6

```



---

---
title: "Funny Game"
layout: "post"
diff: 提高+/省选-
pid: CF731E
tag: ['动态规划 DP', '博弈论']
---

# Funny Game

## 题目描述

Once upon a time Petya and Gena gathered after another programming competition and decided to play some game. As they consider most modern games to be boring, they always try to invent their own games. They have only stickers and markers, but that won't stop them.

The game they came up with has the following rules. Initially, there are $ n $ stickers on the wall arranged in a row. Each sticker has some number written on it. Now they alternate turn, Petya moves first.

One move happens as follows. Lets say there are $ m>=2 $ stickers on the wall. The player, who makes the current move, picks some integer $ k $ from $ 2 $ to $ m $ and takes $ k $ leftmost stickers (removes them from the wall). After that he makes the new sticker, puts it to the left end of the row, and writes on it the new integer, equal to the sum of all stickers he took on this move.

Game ends when there is only one sticker left on the wall. The score of the player is equal to the sum of integers written on all stickers he took during all his moves. The goal of each player is to maximize the difference between his score and the score of his opponent.

Given the integer $ n $ and the initial sequence of stickers on the wall, define the result of the game, i.e. the difference between the Petya's and Gena's score if both players play optimally.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 2<=n<=200000 $ ) — the number of stickers, initially located on the wall.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ -10000<=a_{i}<=10000 $ ) — the numbers on stickers in order from left to right.

## 输出格式

Print one integer — the difference between the Petya's score and Gena's score at the end of the game if both players play optimally.

## 说明/提示

In the first sample, the optimal move for Petya is to take all the stickers. As a result, his score will be equal to $ 14 $ and Gena's score will be equal to $ 0 $ .

In the second sample, the optimal sequence of moves is the following. On the first move Petya will take first three sticker and will put the new sticker with value $ -8 $ . On the second move Gena will take the remaining two stickers. The Petya's score is $ 1+(-7)+(-2)=-8 $ , Gena's score is $ (-8)+3=-5 $ , i.e. the score difference will be $ -3 $ .

## 样例 #1

### 输入

```
3
2 4 8

```

### 输出

```
14

```

## 样例 #2

### 输入

```
4
1 -7 -2 3

```

### 输出

```
-3

```



---

---
title: "Vladik and chat"
layout: "post"
diff: 提高+/省选-
pid: CF754C
tag: ['动态规划 DP', '搜索']
---

# Vladik and chat

## 题目描述

Recently Vladik discovered a new entertainment — coding bots for social networks. He would like to use machine learning in his bots so now he want to prepare some learning data for them.

At first, he need to download $ t $ chats. Vladik coded a script which should have downloaded the chats, however, something went wrong. In particular, some of the messages have no information of their sender. It is known that if a person sends several messages in a row, they all are merged into a single message. It means that there could not be two or more messages in a row with the same sender. Moreover, a sender never mention himself in his messages.

Vladik wants to recover senders of all the messages so that each two neighboring messages will have different senders and no sender will mention himself in his messages.

He has no idea of how to do this, and asks you for help. Help Vladik to recover senders in each of the chats!

## 输入格式

The first line contains single integer $ t $ ( $ 1<=t<=10 $ ) — the number of chats. The $ t $ chats follow. Each chat is given in the following format.

The first line of each chat description contains single integer $ n $ ( $ 1<=n<=100 $ ) — the number of users in the chat.

The next line contains $ n $ space-separated distinct usernames. Each username consists of lowercase and uppercase English letters and digits. The usernames can't start with a digit. Two usernames are different even if they differ only with letters' case. The length of username is positive and doesn't exceed $ 10 $ characters.

The next line contains single integer $ m $ ( $ 1<=m<=100 $ ) — the number of messages in the chat. The next $ m $ line contain the messages in the following formats, one per line:

- <username>:<text> — the format of a message with known sender. The username should appear in the list of usernames of the chat.
- <?>:<text> — the format of a message with unknown sender.

The text of a message can consist of lowercase and uppercase English letter, digits, characters '.' (dot), ',' (comma), '!' (exclamation mark), '?' (question mark) and ' ' (space). The text doesn't contain trailing spaces. The length of the text is positive and doesn't exceed $ 100 $ characters.

We say that a text mention a user if his username appears in the text as a word. In other words, the username appears in a such a position that the two characters before and after its appearance either do not exist or are not English letters or digits. For example, the text "Vasya, masha13 and Kate!" can mention users "Vasya", "masha13", "and" and "Kate", but not "masha".

It is guaranteed that in each chat no known sender mention himself in his messages and there are no two neighboring messages with the same known sender.

## 输出格式

Print the information about the $ t $ chats in the following format:

If it is not possible to recover senders, print single line "Impossible" for this chat. Otherwise print $ m $ messages in the following format:

<username>:<text>

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
1
2
Vladik netman
2
?: Hello, Vladik!
?: Hi

```

### 输出

```
netman: Hello, Vladik!
Vladik: Hi

```

## 样例 #2

### 输入

```
1
2
netman vladik
3
netman:how are you?
?:wrong message
vladik:im fine

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
2
3
netman vladik Fedosik
2
?: users are netman, vladik, Fedosik
vladik: something wrong with this chat
4
netman tigerrrrr banany2001 klinchuh
4
?: tigerrrrr, banany2001, klinchuh, my favourite team ever, are you ready?
klinchuh: yes, coach!
?: yes, netman
banany2001: yes of course.

```

### 输出

```
Impossible
netman: tigerrrrr, banany2001, klinchuh, my favourite team ever, are you ready?
klinchuh: yes, coach!
tigerrrrr: yes, netman
banany2001: yes of course.

```



---

---
title: "Karen and Supermarket"
layout: "post"
diff: 提高+/省选-
pid: CF815C
tag: ['动态规划 DP', '枚举']
---

# Karen and Supermarket

## 题目描述

On the way home, Karen decided to stop by the supermarket to buy some groceries.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815C/155b4f0d440b0d3ff60763603980cf23ed9ae97d.png)She needs to buy a lot of goods, but since she is a student her budget is still quite limited. In fact, she can only spend up to $ b $ dollars.

The supermarket sells $ n $ goods. The $ i $ -th good can be bought for $ c_{i} $ dollars. Of course, each good can only be bought once.

Lately, the supermarket has been trying to increase its business. Karen, being a loyal customer, was given $ n $ coupons. If Karen purchases the $ i $ -th good, she can use the $ i $ -th coupon to decrease its price by $ d_{i} $ . Of course, a coupon cannot be used without buying the corresponding good.

There is, however, a constraint with the coupons. For all $ i>=2 $ , in order to use the $ i $ -th coupon, Karen must also use the $ x_{i} $ -th coupon (which may mean using even more coupons to satisfy the requirement for that coupon).

Karen wants to know the following. What is the maximum number of goods she can buy, without exceeding her budget $ b $ ?

## 输入格式

The first line of input contains two integers $ n $ and $ b $ ( $ 1<=n<=5000 $ , $ 1<=b<=10^{9} $ ), the number of goods in the store and the amount of money Karen has, respectively.

The next $ n $ lines describe the items. Specifically:

- The $ i $ -th line among these starts with two integers, $ c_{i} $ and $ d_{i} $ ( $ 1<=d_{i}<c_{i}<=10^{9} $ ), the price of the $ i $ -th good and the discount when using the coupon for the $ i $ -th good, respectively.
- If $ i>=2 $ , this is followed by another integer, $ x_{i} $ ( $ 1<=x_{i}<i $ ), denoting that the $ x_{i} $ -th coupon must also be used before this coupon can be used.

## 输出格式

Output a single integer on a line by itself, the number of different goods Karen can buy, without exceeding her budget.

## 说明/提示

In the first test case, Karen can purchase the following $ 4 $ items:

- Use the first coupon to buy the first item for $ 10-9=1 $ dollar.
- Use the third coupon to buy the third item for $ 12-2=10 $ dollars.
- Use the fourth coupon to buy the fourth item for $ 20-18=2 $ dollars.
- Buy the sixth item for $ 2 $ dollars.

The total cost of these goods is $ 15 $ , which falls within her budget. Note, for example, that she cannot use the coupon on the sixth item, because then she should have also used the fifth coupon to buy the fifth item, which she did not do here.

In the second test case, Karen has enough money to use all the coupons and purchase everything.

## 样例 #1

### 输入

```
6 16
10 9
10 5 1
12 2 1
20 18 3
10 2 3
2 1 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 10
3 1
3 1 1
3 1 2
3 1 3
3 1 4

```

### 输出

```
5

```



---

---
title: "The Bakery"
layout: "post"
diff: 提高+/省选-
pid: CF833B
tag: ['动态规划 DP', '线段树', '枚举', '动态规划优化']
---

# The Bakery

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833B/f46eccace96d929fa4c99a2b4ae6e89027b73fa1.png)Some time ago Slastyona the Sweetmaid decided to open her own bakery! She bought required ingredients and a wonder-oven which can bake several types of cakes, and opened the bakery.

Soon the expenses started to overcome the income, so Slastyona decided to study the sweets market. She learned it's profitable to pack cakes in boxes, and that the more distinct cake types a box contains (let's denote this number as the value of the box), the higher price it has.

She needs to change the production technology! The problem is that the oven chooses the cake types on its own and Slastyona can't affect it. However, she knows the types and order of $ n $ cakes the oven is going to bake today. Slastyona has to pack exactly $ k $ boxes with cakes today, and she has to put in each box several (at least one) cakes the oven produced one right after another (in other words, she has to put in a box a continuous segment of cakes).

Slastyona wants to maximize the total value of all boxes with cakes. Help her determine this maximum possible total value.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=35000 $ , $ 1<=k<=min(n,50) $ ) – the number of cakes and the number of boxes, respectively.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ ) – the types of cakes in the order the oven bakes them.

## 输出格式

Print the only integer – the maximum total value of all boxes with cakes.

## 说明/提示

In the first example Slastyona has only one box. She has to put all cakes in it, so that there are two types of cakes in the box, so the value is equal to $ 2 $ .

In the second example it is profitable to put the first two cakes in the first box, and all the rest in the second. There are two distinct types in the first box, and three in the second box then, so the total value is $ 5 $ .

## 样例 #1

### 输入

```
4 1
1 2 2 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7 2
1 3 3 1 4 4 4

```

### 输出

```
5

```

## 样例 #3

### 输入

```
8 3
7 7 8 7 7 8 1 7

```

### 输出

```
6

```



---

---
title: "Looking for Order"
layout: "post"
diff: 提高+/省选-
pid: CF8C
tag: ['动态规划 DP', '枚举', '状态合并']
---

# Looking for Order

## 题目描述

Lena喜欢秩序井然的生活。一天，她要去上大学了。突然，她发现整个房间乱糟糟的——她的手提包里的物品都散落在了地上。她想把所有的物品都放回她的手提包。但是，这里有一点问题：她一次最多只能拿两个物品，她也不能移动她的手提包。并且，因为她爱整洁的习惯，如果她拿起了一个物品，她也不能将它放在其他地方，除非放回她的手提包。

Lena把她的房间划分为了一个平面直角坐标系。现在Lena给你她的手提包和每个散落的物品的坐标（当然，一开始的时候她就和手提包站在一个地方）。她从坐标 $(x1,y1)$  走到坐标 $(x2,y2)$  需要用 $(x1-x2)^2+(y1-y2)^2$  单位的时间。现在，Lena将告诉你她的房间的情况，请你为Lena找到一个拾起每个物品的顺序，使她拾起所有物品所需的总时间最小。当然，Lena最后需要返回她的手提包。

## 输入格式

输入文件的第一行为Lena的手提包的坐标 $x_s$  , $y_s$  。第二行为一个正整数 $n$  ，表示总的需要拾起的物品数。接下来的 $n$  行每行包括两个整数，表示每个物品的坐标。

## 输出格式

输出的第一行为一个正整数，表示Lena拾起所有物品所需的最小时间。

输出的第二行为Lena拾起每个物品的顺序。（每一个物品由它的编号代表，0表示手提包）她应该从手提包(0)出发，在手提包(0)结束。

如,0 1 2 0 3 0

表示她从手提包出发，先拾起1号物品，再拾起2号物品，然后返回手提包（并放下1和2），再拾起3号物品，最后返回手提包。

如果有多条允许的路径，输出任一条。

## 输入输出样例
略

感谢@星烁晶熠辉 提供的翻译

## 样例 #1

### 输入

```
0 0
2
1 1
-1 1

```

### 输出

```
8
0 1 2 0 

```

## 样例 #2

### 输入

```
1 1
3
4 3
3 4
0 0

```

### 输出

```
32
0 1 2 0 3 0 

```



---

---
title: "Birds"
layout: "post"
diff: 提高+/省选-
pid: CF922E
tag: ['动态规划 DP', '背包 DP']
---

# Birds

## 题目描述

Apart from plush toys, Imp is a huge fan of little yellow birds!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922E/3bbf7144a65fde520de46a3e8b677997bfb55fe8.png)To summon birds, Imp needs strong magic. There are $ n $ trees in a row on an alley in a park, there is a nest on each of the trees. In the $ i $ -th nest there are $ c_{i} $ birds; to summon one bird from this nest Imp needs to stay under this tree and it costs him $ cost_{i} $ points of mana. However, for each bird summoned, Imp increases his mana capacity by $ B $ points. Imp summons birds one by one, he can summon any number from $ 0 $ to $ c_{i} $ birds from the $ i $ -th nest.

Initially Imp stands under the first tree and has $ W $ points of mana, and his mana capacity equals $ W $ as well. He can only go forward, and each time he moves from a tree to the next one, he restores $ X $ points of mana (but it can't exceed his current mana capacity). Moving only forward, what is the maximum number of birds Imp can summon?

## 输入格式

The first line contains four integers $ n $ , $ W $ , $ B $ , $ X $ ( $ 1<=n<=10^{3},0<=W,B,X<=10^{9} $ ) — the number of trees, the initial points of mana, the number of points the mana capacity increases after a bird is summoned, and the number of points restored when Imp moves from a tree to the next one.

The second line contains $ n $ integers $ c_{1},c_{2},...,c_{n} $ ( $ 0<=c_{i}<=10^{4} $ ) — where $ c_{i} $ is the number of birds living in the $ i $ -th nest. It is guaranteed that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922E/b8ab3a37e0e8b12e9f9885a28b92f283792874ef.png).

The third line contains $ n $ integers $ cost_{1},cost_{2},...,cost_{n} $ ( $ 0<=cost_{i}<=10^{9} $ ), where $ cost_{i} $ is the mana cost to summon a bird from the $ i $ -th nest.

## 输出格式

Print a single integer — the maximum number of birds Imp can summon.

## 说明/提示

In the first sample base amount of Imp's mana is equal to $ 12 $ (with maximum capacity also equal to $ 12 $ ). After he summons two birds from the first nest, he loses $ 8 $ mana points, although his maximum capacity will not increase (since $ B=0 $ ). After this step his mana will be $ 4 $ of $ 12 $ ; during the move you will replenish $ 4 $ mana points, and hence own $ 8 $ mana out of $ 12 $ possible. Now it's optimal to take $ 4 $ birds from the second nest and spend $ 8 $ mana. The final answer will be — $ 6 $ .

In the second sample the base amount of mana is equal to $ 1000 $ . The right choice will be to simply pick all birds from the last nest. Note that Imp's mana doesn't restore while moving because it's initially full.

## 样例 #1

### 输入

```
2 12 0 4
3 4
4 2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 1000 10 35
1 2 4 5
1000 500 250 200

```

### 输出

```
5

```

## 样例 #3

### 输入

```
2 10 7 11
2 10
6 1

```

### 输出

```
11

```



---

---
title: "Cashback"
layout: "post"
diff: 提高+/省选-
pid: CF940E
tag: ['动态规划 DP', '单调队列', '队列']
---

# Cashback

## 题目描述

Since you are the best Wraith King, Nizhniy Magazin «Mir» at the centre of Vinnytsia is offering you a discount.

You are given an array $ a $ of length $ n $ and an integer $ c $ .

The value of some array $ b $ of length $ k $ is the sum of its elements except for the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF940E/7767e68a87566f0732f029bd691b100b0a741ae2.png) smallest. For example, the value of the array $ [3,1,6,5,2] $ with $ c=2 $ is $ 3+6+5=14 $ .

Among all possible partitions of $ a $ into contiguous subarrays output the smallest possible sum of the values of these subarrays.

## 输入格式

The first line contains integers $ n $ and $ c $ ( $ 1<=n,c<=100000 $ ).

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of $ a $ .

## 输出格式

Output a single integer — the smallest possible sum of values of these subarrays of some partition of $ a $ .

## 说明/提示

In the first example any partition yields 6 as the sum.

In the second example one of the optimal partitions is $ [1,1],[10,10,10,10,10,10,9,10,10,10] $ with the values 2 and 90 respectively.

In the third example one of the optimal partitions is $ [2,3],[6,4,5,7],[1] $ with the values 3, 13 and 1 respectively.

In the fourth example one of the optimal partitions is $ [1],[3,4,5,5,3,4],[1] $ with the values 1, 21 and 1 respectively.

## 样例 #1

### 输入

```
3 5
1 2 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
12 10
1 1 10 10 10 10 10 10 9 10 10 10

```

### 输出

```
92

```

## 样例 #3

### 输入

```
7 2
2 3 6 4 5 7 1

```

### 输出

```
17

```

## 样例 #4

### 输入

```
8 4
1 3 4 5 5 3 4 1

```

### 输出

```
23

```



---

---
title: "XOR-pyramid"
layout: "post"
diff: 提高+/省选-
pid: CF983B
tag: ['动态规划 DP', '递推', '递归']
---

# XOR-pyramid

## 题目描述

For an array $ b $ of length $ m $ we define the function $ f $ as

 $  f(b) = \begin{cases} b[1] & \quad \text{if } m = 1 \\ f(b[1] \oplus b[2],b[2] \oplus b[3],\dots,b[m-1] \oplus b[m]) & \quad \text{otherwise,} \end{cases}  $ where $ \oplus $ is [bitwise exclusive OR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

For example, $ f(1,2,4,8)=f(1\oplus2,2\oplus4,4\oplus8)=f(3,6,12)=f(3\oplus6,6\oplus12)=f(5,10)=f(5\oplus10)=f(15)=15 $

You are given an array $ a $ and a few queries. Each query is represented as two integers $ l $ and $ r $ . The answer is the maximum value of $ f $ on all continuous subsegments of the array $ a_l, a_{l+1}, \ldots, a_r $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the length of $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2^{30}-1 $ ) — the elements of the array.

The third line contains a single integer $ q $ ( $ 1 \le q \le 100\,000 $ ) — the number of queries.

Each of the next $ q $ lines contains a query represented as two integers $ l $ , $ r $ ( $ 1 \le l \le r \le n $ ).

## 输出格式

Print $ q $ lines — the answers for the queries.

## 说明/提示

In first sample in both queries the maximum value of the function is reached on the subsegment that is equal to the whole segment.

In second sample, optimal segment for first query are $ [3,6] $ , for second query — $ [2,5] $ , for third — $ [3,4] $ , for fourth — $ [1,2] $ .

## 样例 #1

### 输入

```
3
8 4 1
2
2 3
1 2

```

### 输出

```
5
12

```

## 样例 #2

### 输入

```
6
1 2 4 8 16 32
4
1 6
2 5
3 4
1 2

```

### 输出

```
60
30
12
3

```



---

