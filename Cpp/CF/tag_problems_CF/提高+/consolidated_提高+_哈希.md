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
title: "Hyperregular Bracket Strings"
layout: "post"
diff: 提高+/省选-
pid: CF1830C
tag: ['哈希 hashing', '组合数学']
---

# Hyperregular Bracket Strings

## 题目描述

给定一个数 $n$ 和 $k$ 个区间 $\left[l_i,r_i\right]\in [1,n]$。

我们定义，对于一个长度为 $n$ 的，仅由 ```(``` 和 ```)``` 组成的合法括号序列，如果它的每一个区间 $\left[l_i,r_i\right]$ 内的子串都是合法括号序列，那么这个括号序列是**好的**。

求**好的**括号序列的数量，答案对 $998244353$ 取模。

## 输入格式

每个数据点第一行为一个数 $t\ (1\le t\le 10^5)$，表示数据组数。

每组数据第一行为两个数 $n,k\ (1\le n\le 3\cdot 10^5,1\le k\le3\cdot 10

## 输出格式

共 $t$ 行，第 $i$ 行表示第 $i$ 组数据的答案对 $998244353$ 取模后的结果

## 说明/提示

以样例的第四组数据为例，答案代表的 $4$ 个好的括号序列分别是：

```
 ((())(()))
 ((())()())
 ()()((()))
 ()()(()())
```

而 ```)(())(())(``` 不是答案之一，因为它不是一个合法的括号序列（最左端与最右端的括号未配对）

```(())((()))``` 也不是答案之一，因为它的 $[3,4]$ 表示的子串 ```))``` 不是一个合法的括号序列

```((()(())))``` 也不是答案之一，因为它的 $[6,9]$ 表示的子串 ```()))``` 不是一个合法的括号序列

## 样例 #1

### 输入

```
7
6 0
5 0
8 1
1 3
10 2
3 4
6 9
1000 3
100 701
200 801
300 901
28 5
1 12
3 20
11 14
4 9
18 19
4 3
1 4
1 4
1 4
```

### 输出

```
5
0
0
4
839415253
140
2
```



---

---
title: "XORificator"
layout: "post"
diff: 提高+/省选-
pid: CF1977D
tag: ['哈希 hashing']
---

# XORificator

## 题目描述

You are given a binary (consisting only of 0s and 1s) $ n \times m $ matrix. You are also given a XORificator, using which you can invert all the values in a chosen row (i.e. replace 0 with 1 and 1 with 0).

A column in the matrix is considered special if it contains exactly one 1. Your task is to find the maximum number of columns that can be made special at the same time, and the set of rows the XORificator should be used on to achieve that.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 3 \cdot 10^5 $ , $ n \cdot m \leq 3 \cdot 10^5 $ ).

Each of the following $ n $ lines of the test case contains a binary string of length $ m $ .

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output two lines.

In the first line, output the maximum number of special columns that is possible to get simultaneously.

In the second line, output a binary string of length $ n $ , where the $ i $ -th character is 0, if you don't use the XORificator on the $ i $ -th row, and 1, if you use the XORificator on the $ i $ -th row.

If there are multiple valid XORificator configurations that achieve the optimal answer, you can output any of them.

## 说明/提示

In the first test case, you can use the XORificator on the second row to make the columns $ 2 $ , $ 3 $ , and $ 4 $ special.

In the second test case, the only column is already special, so you don't need to use the XORificator.

## 样例 #1

### 输入

```
5
3 4
1010
0110
0100
1 1
1
1 1
0
2 5
00101
10110
3 3
101
111
000
```

### 输出

```
3
010
1
0
1
1
3
00
2
010
```



---

---
title: "Robin Hood Archery"
layout: "post"
diff: 提高+/省选-
pid: CF2014H
tag: ['莫队', '哈希 hashing']
---

# Robin Hood Archery

## 题目描述

在这种时候，射箭总是一天中的主要运动，因为诺丁汉郡的自耕农是整个快乐的英格兰最好的长弓手，但今年郡长犹豫了……



诺丁汉郡长组织了一场射箭比赛。这是最后一轮，罗宾汉对阵警长!

编号为$ 1 $ ～ $ n $的行中有$ n $个目标。当玩家射击目标$ i $时，他们的得分增加$ a_i $，目标$ i $被摧毁。游戏由回合组成，玩家轮流轮到谁。罗宾汉总是先开始游戏，然后是警长等等。游戏继续进行，直到所有目标被摧毁。两名球员都以得分$ 0 $开始。

在游戏结束时，得分最多的玩家获胜，而另一名玩家输了。如果双方得分相同，则为平局，没有人赢也没有人输。在每个回合中，玩家可以射击任何之前没有射击过的目标。两种游戏都是为了获得尽可能多的分数。

诺丁汉郡长怀疑他可能会输掉比赛!不能这样，你必须帮助警长。Sheriff将提出$ q $查询，每个查询指定$ l $和$ r $。这意味着游戏将只与目标$ l, l+1, \dots, r $一起玩，因为其他目标将在游戏开始前被Sheriff删除。

对于每个查询$ l $, $ r $，在只考虑目标$ l, l+1, \dots, r $的情况下，确定警长是否不会输掉比赛。

## 输入格式

输入的第一行包含一个整数$ t $ ($ 1 \le t \le 10^4 $)——测试用例的数量。

每个测试用例的第一行包含两个整数$ n $、$ q $ ($ 1 \le n,q \le 2\cdot10^5 $)——目标的数量和Sheriff将提出的查询的数量。

每个测试用例的第二行包含$ n $整数$ a_1, a_2, \ldots, a_n $ ($ 1 \le a_i \le 10^6 $)—达到每个目标的点。

然后$ q $行，每一行有两个整数$ l $和$ r $ ($ 1 \le l \le r \le n $)——每个查询要考虑的目标范围。

可以保证所有测试用例中$ n $和$ q $的总和不超过$ 2 \cdot 10^5 $。

## 输出格式

对于每个查询，如果警长在只考虑目标$ l, l+1, \dots, r $时没有输掉比赛，则输出“YES”，否则输出“NO”。

您可以在任何情况下输出答案(大小写不敏感)。例如，字符串“yEs”、“yEs”、“yEs”和“yEs”将被识别为“YES”。

## 样例 #1

### 输入

```
2
3 3
1 2 2
1 2
1 3
2 3
5 3
2 1 2 1 1
1 2
1 3
4 5
```

### 输出

```
NO
NO
YES
NO
NO
YES
```



---

---
title: "C+K+S"
layout: "post"
diff: 提高+/省选-
pid: CF2023C
tag: ['图论', '哈希 hashing']
---

# C+K+S

## 题目描述

# 题面
给您两个强连接 $^{1}$ 有向图，每个图都有恰好 $n$ 个顶点，但可能有不同数量的边。仔细观察后，您发现了一个重要特征--这两个图中任何一个循环的长度都能被 $k$ 整除。

每个 $2n$ 顶点都属于两种类型中的一种：传入或传出。每个顶点的类型都是已知的。

您需要确定是否有可能在源图之间绘制恰好 $n$ 条有向边，从而满足以下四个条件：

- 任何添加的边的两端都位于不同的图中。
- 从每个传出顶点，正好有一条新增边产生。
- 在每个进入的顶点中，正好有一条添加边进入。
- 在生成的图中，任何循环的长度都能被 $k$ 整除。

$^{1}$强连接图是指从每个顶点到其他顶点都有一条路径的图。

## 输入格式

**输入**

每个测试由多个测试用例组成。第一行包含一个整数 $t$ ( $1 \le t \le 10^4$ )--测试用例数。测试用例说明如下。

每个测试用例的第一行包含两个整数 $n$ 和 $k$ （ $2 \le k \le n \le 2 \cdot 10^5$ ）--每个图形的顶点数和每个循环的长度可整除的值。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ( $a_i \in \{0, 1\}$ )。如果 $a_i = 0$ ，则第一个图形的顶点 $i$ 进入。如果是 $a_i = 1$ ，那么第一个图形的顶点 $i$ 是传出的。

每个测试用例的第三行包含一个整数 $m_1$ ( $1 \le m_1 \le 5 \cdot 10^5$ ) - 第一个图中的边数。

接下来的 $m_1$ 行包含对第一个图的边的描述。其中 $i$ 行包含两个整数 $v_i$ 和 $u_i$ （ $1 \le v_i, u_i \le n$ ）--第一个图形中从顶点 $v_i$ 到顶点 $u_i$ 的一条边。

接下来以同样的格式描述第二个图形。

下一行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$ ( $b_i \in \{0, 1\}$ )。如果是 $b_i = 0$ ，那么第二个图形的顶点 $i$ 是进入的。如果是 $b_i = 1$ ，那么第二个图形的顶点 $i$ 是传出的。

下一行包含一个整数 $m_2$ ( $1 \le m_2 \le 5 \cdot 10^5$ )--第二个图形中的边数。

接下来的 $m_2$ 行包含对第二个图的边的描述。其中 $i$ 行包含两个整数 $v_i$ 和 $u_i$ （ $1 \le v_i, u_i \le n$ ）--第二个图中从顶点 $v_i$ 到顶点 $u_i$ 的一条边。

可以保证这两个图都是强连接的，并且所有循环的长度都能被 $k$ 整除。

保证所有测试案例中 $n$ 的总和不超过 $2 \cdot 10^5$ 。保证所有测试用例中 $m_1$ 与 $m_2$ 之和不超过 $5 \cdot 10^5$ 。

## 输出格式

**输出**

对于每个测试用例，如果可以绘制 $n$ 条新边且满足所有条件，则输出 "YES"（不带引号），否则输出 "NO"（不带引号）。

您可以输出任何情况下的答案（例如，字符串 "yEs"、"yes"、"Yes "和 "YES "将被视为肯定答案）。

# 样例解释
**注**

在第一个测试用例中，从第一个图到第二个图的边可以绘制为 $(1, 3)$ 和 $(4, 2)$ （这对边中的第一个数字是第一个图中的顶点编号，这对边中的第二个数字是第二个图中的顶点编号），从第二个图到第一个图的边可以绘制为 $(1, 2)$ 和 $(4, 3)$ （这对边中的第一个数字是第二个图中的顶点编号，这对边中的第二个数字是第一个图中的顶点编号）。

在第二个测试案例中，共有 $4$ 个进入顶点和 $2$ 个离开顶点，因此无法绘制 $3$ 条边。

## 样例 #1

### 输入

```
3
4 2
1 0 0 1
4
1 2
2 3
3 4
4 1
1 0 0 1
4
1 3
3 2
2 4
4 1
3 3
0 0 0
3
1 2
2 3
3 1
1 1 0
3
1 2
2 3
3 1
4 2
1 1 1 1
4
1 2
2 3
3 4
4 1
0 0 0 0
6
1 2
2 1
1 3
3 1
1 4
4 1
```

### 输出

```
YES
NO
YES
```



---

