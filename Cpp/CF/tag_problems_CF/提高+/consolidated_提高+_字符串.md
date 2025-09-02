---
title: "Space Isaac"
layout: "post"
diff: 提高+/省选-
pid: CF1045B
tag: ['字符串', '枚举', '位运算']
---

# Space Isaac

## 题目描述

Everybody seems to think that the Martians are green, but it turns out they are metallic pink and fat. Ajs has two bags of distinct nonnegative integers. The bags are disjoint, and the union of the sets of numbers in the bags is $ \{0,1,…,M-1\} $ , for some positive integer $ M $ . Ajs draws a number from the first bag and a number from the second bag, and then sums them modulo $ M $ .

What are the residues modulo $ M $ that Ajs cannot obtain with this action?

## 输入格式

The first line contains two positive integer $ N $ ( $ 1 \leq N \leq 200\,000 $ ) and $ M $ ( $ N+1 \leq M \leq 10^{9} $ ), denoting the number of the elements in the first bag and the modulus, respectively.

The second line contains $ N $ nonnegative integers $ a_1,a_2,\ldots,a_N $ ( $ 0 \leq a_1<a_2< \ldots< a_N<M $ ), the contents of the first bag.

## 输出格式

In the first line, output the cardinality $ K $ of the set of residues modulo $ M $ which Ajs cannot obtain.

In the second line of the output, print $ K $ space-separated integers greater or equal than zero and less than $ M $ , which represent the residues Ajs cannot obtain. The outputs should be sorted in increasing order of magnitude. If $ K $ =0, do not output the second line.

## 说明/提示

In the first sample, the first bag and the second bag contain $ \{3,4\} $ and $ \{0,1,2\} $ , respectively. Ajs can obtain every residue modulo $ 5 $ except the residue $ 2 $ : $  4+1 \equiv 0, \, 4+2 \equiv 1, \, 3+0 \equiv 3, \, 3+1 \equiv 4  $ modulo $ 5 $ . One can check that there is no choice of elements from the first and the second bag which sum to $ 2 $ modulo $ 5 $ .

In the second sample, the contents of the first bag are $ \{5,25,125,625\} $ , while the second bag contains all other nonnegative integers with at most $ 9 $ decimal digits. Every residue modulo $ 1\,000\,000\,000 $ can be obtained as a sum of an element in the first bag and an element in the second bag.

## 样例 #1

### 输入

```
2 5
3 4

```

### 输出

```
1
2

```

## 样例 #2

### 输入

```
4 1000000000
5 25 125 625

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2 4
1 3

```

### 输出

```
2
0 2

```



---

---
title: "Check Transcription"
layout: "post"
diff: 提高+/省选-
pid: CF1056E
tag: ['字符串', '哈希 hashing']
---

# Check Transcription

## 题目描述

One of Arkady's friends works at a huge radio telescope. A few decades ago the telescope has sent a signal $ s $ towards a faraway galaxy. Recently they've received a response $ t $ which they believe to be a response from aliens! The scientists now want to check if the signal $ t $ is similar to $ s $ .

The original signal $ s $ was a sequence of zeros and ones (everyone knows that binary code is the universe-wide language). The returned signal $ t $ , however, does not look as easy as $ s $ , but the scientists don't give up! They represented $ t $ as a sequence of English letters and say that $ t $ is similar to $ s $ if you can replace all zeros in $ s $ with some string $ r_0 $ and all ones in $ s $ with some other string $ r_1 $ and obtain $ t $ . The strings $ r_0 $ and $ r_1 $ must be different and non-empty.

Please help Arkady's friend and find the number of possible replacements for zeros and ones (the number of pairs of strings $ r_0 $ and $ r_1 $ ) that transform $ s $ to $ t $ .

## 输入格式

The first line contains a string $ s $ ( $ 2 \le |s| \le 10^5 $ ) consisting of zeros and ones — the original signal.

The second line contains a string $ t $ ( $ 1 \le |t| \le 10^6 $ ) consisting of lowercase English letters only — the received signal.

It is guaranteed, that the string $ s $ contains at least one '0' and at least one '1'.

## 输出格式

Print a single integer — the number of pairs of strings $ r_0 $ and $ r_1 $ that transform $ s $ to $ t $ .

In case there are no such pairs, print $ 0 $ .

## 说明/提示

In the first example, the possible pairs $ (r_0, r_1) $ are as follows:

- "a", "aaaaa"
- "aa", "aaaa"
- "aaaa", "aa"
- "aaaaa", "a"

The pair "aaa", "aaa" is not allowed, since $ r_0 $ and $ r_1 $ must be different.

In the second example, the following pairs are possible:

- "ko", "kokotlin"
- "koko", "tlin"

## 样例 #1

### 输入

```
01
aaaaaa

```

### 输出

```
4

```

## 样例 #2

### 输入

```
001
kokokokotlin

```

### 输出

```
2

```



---

---
title: "A, B, AB and BA"
layout: "post"
diff: 提高+/省选-
pid: CF2069E
tag: ['字符串', '贪心']
---

# A, B, AB and BA

## 题目描述

给定一个由字符 A 和 B 组成的字符串 $s$。

你的任务是将它分割成长度为 $1$ 或 $2$ 的块，使得：
- "A" 类型的块数量不超过 $a$；
- "B" 类型的块数量不超过 $b$；
- "AB" 类型的块数量不超过 $ab$；
- "BA" 类型的块数量不超过 $ba$；

其中 "AA" 和 "BB" 类型的块是被禁止的。原始字符串 $s$ 的每个字符必须恰好属于一个块。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。接下来输入 $t$ 个独立测试用例。

每个测试用例的第一行包含一个仅由字符 A 和/或 B 组成的字符串 $s$（$1 \le |s| \le 5 \cdot 10^5$）。

每个测试用例的第二行包含四个整数 $a$、$b$、$ab$ 和 $ba$（$0 \le a, b, ab, ba \le 5 \cdot 10^5$）——分别表示允许的 "A"、"B"、"AB" 和 "BA" 类型块的最大数量。

保证所有测试用例的 $s$ 总长度不超过 $5 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果能够分割字符串 $s$ 则输出 YES，否则输出 NO。

## 说明/提示

第三个测试用例中，所有可能的分割方式为：A|B|A、AB|A 或 A|BA。所有这些方式都至少包含一个 "A"。

第四个测试用例中，一种可能的分割方式是：A|B|B|A|B|A|A|B。

第五个测试用例中，一种可能的分割方式是：A|BA|B|BA|AB|BA|AB。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
A
0 0 10 10
B
0 1 0 0
ABA
0 0 1 1
ABBABAAB
5 5 0 0
ABABBAABBAAB
1 1 2 3
ABBBBAB
0 3 2 0
BAABBA
1 3 2 0
```

### 输出

```
NO
YES
NO
YES
YES
YES
NO
```



---

---
title: "Cowboys"
layout: "post"
diff: 提高+/省选-
pid: CF212C
tag: ['字符串', '枚举']
---

# Cowboys

## 题目描述

问题描述
 
　　n个牛仔站立于一个环中，并且每个牛仔都用左轮手枪指着他旁边的人！每个牛仔指着他顺时针或者逆时针方向上的相邻的人。正如很多西部片那样，在这一刻，绳命是入刺的不可惜……对峙的场景每秒都在变化。每秒钟牛仔们都会分析局势，当一对相邻的牛仔发现他们正在互指的时候，就会转过身。一秒内每对这样的牛仔都会转身。所有的转身都同时在一瞬间发生。我们用字母来表示牛仔所指的方向。“A”表示顺时针方向，“B”表示逆时针方向。如此，一个仅含“A”“B”的字符串便用来表示这个由牛仔构成的环。这是由第一个指着顺时针方向的牛仔做出的记录。例如，牛仔环“ABBBABBBA”在一秒后会变成“BABBBABBA”；而牛仔环“BABBA”会变成“ABABB”。 这幅图说明了“BABBA”怎么变成“ABABB” 一秒过去了，现在用字符串s来表示牛仔们的排列。你的任务是求出一秒前有多少种可能的排列。如果某个排列中一个牛仔指向顺时针，而在另一个排列中他指向逆时针，那么这两个排列就是不同的。

## 输入格式

　　输入数据包括一个字符串s，它只含有“A”和“B”。

## 输出格式

　　输出你求出来的一秒前的可能排列数。
  
数据规模和约定

　　s的长度为3到100（包含3和100）

由 @落叶知秋声 提供翻译

## 样例 #1

### 输入

```
BABBBABBA

```

### 输出

```
2

```

## 样例 #2

### 输入

```
ABABB

```

### 输出

```
2

```

## 样例 #3

### 输入

```
ABABAB

```

### 输出

```
4

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

---
title: "Least Cost Bracket Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF3D
tag: ['字符串', '优先队列', '队列']
---

# Least Cost Bracket Sequence

## 题目描述

This is yet another problem on regular bracket sequences.

A bracket sequence is called regular, if by inserting "+" and "1" into it we get a correct mathematical expression. For example, sequences "(())()", "()" and "(()(()))" are regular, while ")(", "(()" and "(()))(" are not. You have a pattern of a bracket sequence that consists of characters "(", ")" and "?". You have to replace each character "?" with a bracket so, that you get a regular bracket sequence.

For each character "?" the cost of its replacement with "(" and ")" is given. Among all the possible variants your should choose the cheapest.

## 输入格式

The first line contains a non-empty pattern of even length, consisting of characters "(", ")" and "?". Its length doesn't exceed $ 5·10^{4} $ . Then there follow $ m $ lines, where $ m $ is the number of characters "?" in the pattern. Each line contains two integer numbers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=10^{6} $ ), where $ a_{i} $ is the cost of replacing the $ i $ -th character "?" with an opening bracket, and $ b_{i} $ — with a closing one.

## 输出格式

Print the cost of the optimal regular bracket sequence in the first line, and the required sequence in the second.

Print -1, if there is no answer. If the answer is not unique, print any of them.

## 样例 #1

### 输入

```
(??)
1 2
2 8

```

### 输出

```
4
()()

```



---

---
title: "Restoring Increasing Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF490E
tag: ['字符串', '枚举', '构造']
---

# Restoring Increasing Sequence

## 题目描述

Peter wrote on the board a strictly increasing sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Then Vasil replaced some digits in the numbers of this sequence by question marks. Thus, each question mark corresponds to exactly one lost digit.

Restore the the original sequence knowing digits remaining on the board.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the length of the sequence. Next $ n $ lines contain one element of the sequence each. Each element consists only of digits and question marks. No element starts from digit 0. Each element has length from 1 to 8 characters, inclusive.

## 输出格式

If the answer exists, print in the first line "YES" (without the quotes). Next $ n $ lines must contain the sequence of positive integers — a possible variant of Peter's sequence. The found sequence must be strictly increasing, it must be transformed from the given one by replacing each question mark by a single digit. All numbers on the resulting sequence must be written without leading zeroes. If there are multiple solutions, print any of them.

If there is no answer, print a single line "NO" (without the quotes).

## 样例 #1

### 输入

```
3
?
18
1?

```

### 输出

```
YES
1
18
19

```

## 样例 #2

### 输入

```
2
??
?

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
12224
12??5
12226
?0000
?00000

```

### 输出

```
YES
12224
12225
12226
20000
100000

```



---

---
title: "Obsessive String"
layout: "post"
diff: 提高+/省选-
pid: CF494B
tag: ['字符串', '递推', '前缀和']
---

# Obsessive String

## 题目描述

给定两个字符串 $s$ 和 $t$。定义一种合法的截取方案为，在字符串 $s$ 中截取若干（大于 $0$）个互不相交的子串，满足 $t$ 是每个这些子串的子串。

请你输出总方案数模 $10^9 + 7$ 的值。

## 输入格式

输入共两行。第一行一个字符串 $s$，第二行一个字符串 $t$。

## 输出格式

输出共一行，一个非负整数表示答案。

## 说明/提示

保证 $1 \leq |s|, |t| \leq 10^5$，字符串中只包含小写拉丁字母。

## 样例 #1

### 输入

```
ababa
aba

```

### 输出

```
5

```

## 样例 #2

### 输入

```
welcometoroundtwohundredandeightytwo
d

```

### 输出

```
274201

```

## 样例 #3

### 输入

```
ddd
d

```

### 输出

```
12

```



---

---
title: "Watto and Mechanism"
layout: "post"
diff: 提高+/省选-
pid: CF514C
tag: ['字符串', '字典树 Trie']
---

# Watto and Mechanism

## 题目描述

Watto, the owner of a spare parts store, has recently got an order for the mechanism that can process strings in a certain way. Initially the memory of the mechanism is filled with $ n $ strings. Then the mechanism should be able to process queries of the following type: "Given string $ s $ , determine if the memory of the mechanism contains string $ t $ that consists of the same number of characters as $ s $ and differs from $ s $ in exactly one position".

Watto has already compiled the mechanism, all that's left is to write a program for it and check it on the data consisting of $ n $ initial lines and $ m $ queries. He decided to entrust this job to you.

## 输入格式

The first line contains two non-negative numbers $ n $ and $ m $ ( $ 0<=n<=3·10^{5} $ , $ 0<=m<=3·10^{5} $ ) — the number of the initial strings and the number of queries, respectively.

Next follow $ n $ non-empty strings that are uploaded to the memory of the mechanism.

Next follow $ m $ non-empty strings that are the queries to the mechanism.

The total length of lines in the input doesn't exceed $ 6·10^{5} $ . Each line consists only of letters 'a', 'b', 'c'.

## 输出格式

For each query print on a single line "YES" (without the quotes), if the memory of the mechanism contains the required string, otherwise print "NO" (without the quotes).

## 样例 #1

### 输入

```
2 3
aaaaa
acacaca
aabaa
ccacacc
caaac

```

### 输出

```
YES
NO
NO

```



---

---
title: "A Simple Task"
layout: "post"
diff: 提高+/省选-
pid: CF558E
tag: ['字符串', '线段树', '排序']
---

# A Simple Task

## 题目描述

This task is very simple. Given a string $ S $ of length $ n $ and $ q $ queries each query is on the format $ i $ $ j $ $ k $ which means sort the substring consisting of the characters from $ i $ to $ j $ in non-decreasing order if $ k=1 $ or in non-increasing order if $ k=0 $ .

Output the final string after applying the queries.

## 输入格式

The first line will contain two integers $ n,q $ ( $ 1<=n<=10^{5} $ , $ 0<=q<=50000 $ ), the length of the string and the number of queries respectively.

Next line contains a string $ S $ itself. It contains only lowercase English letters.

Next $ q $ lines will contain three integers each $ i,j,k $ ( $ 1<=i<=j<=n $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/7c3e064c95015e1bd5569e78df83991726b5fb24.png)).

## 输出格式

Output one line, the string $ S $ after applying the queries.

## 说明/提示

First sample test explanation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/39812d297b72578842edac4711612bcaf8f08f55.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/6cf00260e704a305c81e1f57b87405efa2610fa7.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/8d72452272093b12cc5f5081cf07220bba9298d5.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/51ddb7e0620c1f3452d956f281c3537d11d07fb3.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/47cfdfe8b8cb10e651ce3dbdd53d8f068aca3e79.png)

## 样例 #1

### 输入

```
10 5
abacdabcda
7 10 0
5 8 1
1 4 0
3 6 0
7 10 1

```

### 输出

```
cbcaaaabdd
```

## 样例 #2

### 输入

```
10 1
agjucbvdfk
1 10 1

```

### 输出

```
abcdfgjkuv
```



---

---
title: "Zuma"
layout: "post"
diff: 提高+/省选-
pid: CF607B
tag: ['字符串', '搜索', '记忆化搜索', '区间 DP']
---

# Zuma

## 题目描述

$\texttt{Genos}$ 最近在他的手机上下载了祖玛游戏。在祖玛游戏里，存在 $n$ 个一行的宝石，第 $i$ 个宝石的颜色是 $C_i$。这个游戏的目标是尽快的消灭一行中所有的宝石。

在一秒钟，$\texttt{Genos}$ 能很快的挑选出这些有颜色的宝石中的一个回文的、连续的子串，并将这个子串移除。每当一个子串被删除后，剩余的宝石将连接在一起，形成一个新的行列。

你的任务是：求出把整个宝石串都移除的最短时间。

## 输入格式

第一行包含一个整数 $n(1 \le n \le 500)$，表示宝石串的长度。第二行包含 $n$ 个被空格分开的整数，第 $i(1 \le i \le n)$ 个表示这行中第 $i$ 个珠子的颜色。

## 输出格式

输出一个整数，把这行珠子移除的最短时间。

## 说明/提示

在第一个例子中，$\texttt{Genos}$ 可以在一秒钟就把这行珠子全部移走。在第二个例子中，$\texttt{Genos}$ 一次只能移走一个珠子，所以移走三个珠子花费他三秒。在第三个例子中，为了达到 $2$ 秒的最快时间，先移除回文串 $\texttt{4 4}$,再移除回文串 $\texttt{1 2 3 2 1}$。

感谢 @Administrator2004 提供的翻译

## 样例 #1

### 输入

```
3
1 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
1 2 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
7
1 4 4 2 3 2 1

```

### 输出

```
2

```



---

---
title: "Innokenty and a Football League"
layout: "post"
diff: 提高+/省选-
pid: CF780D
tag: ['字符串', '贪心', '构造']
---

# Innokenty and a Football League

## 题目描述

Innokenty is a president of a new football league in Byteland. The first task he should do is to assign short names to all clubs to be shown on TV next to the score. Of course, the short names should be distinct, and Innokenty wants that all short names consist of three letters.

Each club's full name consist of two words: the team's name and the hometown's name, for example, "DINAMO BYTECITY". Innokenty doesn't want to assign strange short names, so he wants to choose such short names for each club that:

1. the short name is the same as three first letters of the team's name, for example, for the mentioned club it is "DIN",
2. or, the first two letters of the short name should be the same as the first two letters of the team's name, while the third letter is the same as the first letter in the hometown's name. For the mentioned club it is "DIB".

Apart from this, there is a rule that if for some club $ x $ the second option of short name is chosen, then there should be no club, for which the first option is chosen which is the same as the first option for the club $ x $ . For example, if the above mentioned club has short name "DIB", then no club for which the first option is chosen can have short name equal to "DIN". However, it is possible that some club have short name "DIN", where "DI" are the first two letters of the team's name, and "N" is the first letter of hometown's name. Of course, no two teams can have the same short name.

Help Innokenty to choose a short name for each of the teams. If this is impossible, report that. If there are multiple answer, any of them will suit Innokenty. If for some team the two options of short name are equal, then Innokenty will formally think that only one of these options is chosen.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of clubs in the league.

Each of the next $ n $ lines contains two words — the team's name and the hometown's name for some club. Both team's name and hometown's name consist of uppercase English letters and have length at least $ 3 $ and at most $ 20 $ .

## 输出格式

It it is not possible to choose short names and satisfy all constraints, print a single line "NO".

Otherwise, in the first line print "YES". Then print $ n $ lines, in each line print the chosen short name for the corresponding club. Print the clubs in the same order as they appeared in input.

If there are multiple answers, print any of them.

## 说明/提示

In the first sample Innokenty can choose first option for both clubs.

In the second example it is not possible to choose short names, because it is not possible that one club has first option, and the other has second option if the first options are equal for both clubs.

In the third example Innokenty can choose the second options for the first two clubs, and the first option for the third club.

In the fourth example note that it is possible that the chosen short name for some club $ x $ is the same as the first option of another club $ y $ if the first options of $ x $ and $ y $ are different.

## 样例 #1

### 输入

```
2
DINAMO BYTECITY
FOOTBALL MOSCOW

```

### 输出

```
YES
DIN
FOO

```

## 样例 #2

### 输入

```
2
DINAMO BYTECITY
DINAMO BITECITY

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
3
PLAYFOOTBALL MOSCOW
PLAYVOLLEYBALL SPB
GOGO TECHNOCUP

```

### 输出

```
YES
PLM
PLS
GOG

```

## 样例 #4

### 输入

```
3
ABC DEF
ABC EFG
ABD OOO

```

### 输出

```
YES
ABD
ABE
ABO

```



---

---
title: "Robot Vacuum Cleaner"
layout: "post"
diff: 提高+/省选-
pid: CF922D
tag: ['字符串', '排序', '概率论']
---

# Robot Vacuum Cleaner

## 题目描述

Pushok the dog has been chasing Imp for a few hours already.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/829d42ff73514382387680ad82853edceea77a87.png)Fortunately, Imp knows that Pushok is afraid of a robot vacuum cleaner.

While moving, the robot generates a string $ t $ consisting of letters 's' and 'h', that produces a lot of noise. We define noise of string $ t $ as the number of occurrences of string "sh" as a subsequence in it, in other words, the number of such pairs $ (i,j) $ , that $ i<j $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/f1a56c1d084d739e6652be99271753eea487f10e.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/1c020fe0ca945d3f2fc54f71a604c6ab2188fcee.png).

The robot is off at the moment. Imp knows that it has a sequence of strings $ t_{i} $ in its memory, and he can arbitrary change their order. When the robot is started, it generates the string $ t $ as a concatenation of these strings in the given order. The noise of the resulting string equals the noise of this concatenation.

Help Imp to find the maximum noise he can achieve by changing the order of the strings.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of strings in robot's memory.

Next $ n $ lines contain the strings $ t_{1},t_{2},...,t_{n} $ , one per line. It is guaranteed that the strings are non-empty, contain only English letters 's' and 'h' and their total length does not exceed $ 10^{5} $ .

## 输出格式

Print a single integer — the maxumum possible noise Imp can achieve by changing the order of the strings.

## 说明/提示

The optimal concatenation in the first sample is $ ssshhshhhs $ .

## 样例 #1

### 输入

```
4
ssh
hs
s
hhhs

```

### 输出

```
18

```

## 样例 #2

### 输入

```
2
h
s

```

### 输出

```
1

```



---

---
title: "Largest Beautiful Number"
layout: "post"
diff: 提高+/省选-
pid: CF946E
tag: ['字符串', '枚举', '构造']
---

# Largest Beautiful Number

## 题目描述

如果一个正整数在十进制表示法下，不含前导零，有偶数个数字，并且对于它的所有数字来说，有一种排列方式使得这些数字组成一个回文数，那么这个数就是“美丽数”。例如4242是一个美丽数，因为它含有4个数字，这4个数字可以组成一个回文数2442。

给定一个正整数s，求严格小于s的最大美丽数。

## 输入格式

第1行，1个整数t，表示数据组数。

下面t行，每行1个十进制数s。

## 输出格式

对于每个s，输出严格小于s的最大美丽数。

数据保证有解。

## 说明/提示

t <= 10^5 
 

s的长度<= 2*10^5 

感谢@刷题永动机 提供的翻译

## 样例 #1

### 输入

```
4
89
88
1000
28923845

```

### 输出

```
88
77
99
28923839

```



---

