---
title: "[NOI2016] 优秀的拆分"
layout: "post"
diff: 省选/NOI-
pid: P1117
tag: ['字符串', '2016', 'NOI', 'O2优化', '枚举', '后缀数组 SA']
---
# [NOI2016] 优秀的拆分
## 题目描述

如果一个字符串可以被拆分为 $\text{AABB}$ 的形式，其中 $\text{A}$ 和 $\text{B}$ 是任意**非空**字符串，则我们称该字符串的这种拆分是优秀的。  
例如，对于字符串 $ \texttt{aabaabaa} $ ，如果令 $\text{A}=\texttt{aab}$，$\text{B}=\texttt{a}$，我们就找到了这个字符串拆分成 $\text{AABB}$ 的一种方式。

一个字符串可能没有优秀的拆分，也可能存在不止一种优秀的拆分。  
比如我们令 $\text{A}=\texttt{a}$，$\text{B}=\texttt{baa}$，也可以用 $\text{AABB}$ 表示出上述字符串；但是，字符串 $\texttt{abaabaa}$ 就没有优秀的拆分。

现在给出一个长度为 $n$ 的字符串 $S$，我们需要求出，在它所有子串的所有拆分方式中，优秀拆分的总个数。这里的子串是指字符串中连续的一段。

以下事项需要注意：

1. 出现在不同位置的相同子串，我们认为是不同的子串，它们的优秀拆分均会被记入答案。
2. 在一个拆分中，允许出现 $\text{A}=\text{B}$。例如 $\texttt{cccc}$ 存在拆分 $\text{A}=\text{B}=\texttt{c}$。
3. 字符串本身也是它的一个子串。
## 输入格式

每个输入文件包含多组数据。

输入文件的第一行只有一个整数 $T$，表示数据的组数。

接下来 $T$ 行，每行包含一个仅由英文小写字母构成的字符串 $S$，意义如题所述。
## 输出格式

输出 $T$ 行，每行包含一个整数，表示字符串 $S$ 所有子串的所有拆分中，总共有多少个是优秀的拆分。
## 样例

### 样例输入 #1
```
4
aabbbb
cccccc
aabaabaabaa
bbaabaababaaba

```
### 样例输出 #1
```
3
5
4
7

```
## 提示

### 样例解释

我们用 $S[i, j]$ 表示字符串 $S$ 第 $i$ 个字符到第 $j$ 个字符的子串（从 $1$ 开始计数）。

第一组数据中，共有三个子串存在优秀的拆分：  
$S[1,4]=\texttt{aabb}$，优秀的拆分为 $\text{A}=\texttt{a}$，$\text{B}=\texttt{b}$；  
$S[3,6]=\texttt{bbbb}$，优秀的拆分为 $\text{A}=\texttt{b}$，$\text{B}=\texttt{b}$；  
$S[1,6]=\texttt{aabbbb}$，优秀的拆分为 $\text{A}=\texttt{a}$，$\text{B}=\texttt{bb}$。  
而剩下的子串不存在优秀的拆分，所以第一组数据的答案是 $3$。

第二组数据中，有两类，总共四个子串存在优秀的拆分：  
对于子串 $S[1,4]=S[2,5]=S[3,6]=\texttt{cccc}$，它们优秀的拆分相同，均为 $\text{A}=\texttt{c}$，$\text{B}=\texttt{c}$，但由于这些子串位置不同，因此要计算三次；  
对于子串 $S[1,6]=\texttt{cccccc}$，它优秀的拆分有两种：$\text{A}=\texttt{c}$，$\text{B}=\texttt{cc}$ 和 $\text{A}=\texttt{cc}$，$\text{B}=\texttt{c}$，它们是相同子串的不同拆分，也都要计入答案。  
所以第二组数据的答案是 $3+2=5$。

第三组数据中，$S[1,8]$ 和 $S[4,11]$ 各有两种优秀的拆分，其中 $S[1,8]$ 是问题描述中的例子，所以答案是 $2+2=4$。

第四组数据中，$S[1,4]$，$S[6,11]$，$S[7,12]$，$S[2,11]$，$S[1,8]$ 各有一种优秀的拆分，$S[3,14]$ 有两种优秀的拆分，所以答案是 $5+2=7$。

### 数据范围

对于全部的测试点，保证 $1 \leq T \leq 10$。以下对数据的限制均是对于单组输入数据而言的，也就是说同一个测试点下的 $T$ 组数据均满足限制条件。

我们假定 $n$ 为字符串 $S$ 的长度，每个测试点的详细数据范围见下表：

| 测试点编号   | $n \leq$  | 特殊性质           |
| ------------ | --------- | ------------------ |
| $1 \sim 2$   | $300$     | $S$ 中所有字符相同 |
| $3 \sim 4$   | $2\,000$  | $S$ 中所有字符相同 |
| $5 \sim 6$   | $10$      |                    |
| $7 \sim 8$   | $20$      |                    |
| $9 \sim 10$  | $30$      |                    |
| $11 \sim 12$ | $50$      |                    |
| $13 \sim 14$ | $100$     |                    |
| $15$         | $200$     |                    |
| $16$         | $300$     |                    |
| $17$         | $500$     |                    |
| $18$         | $1\,000$  |                    |
| $19$         | $2\,000$  |                    |
| $20$         | $30\,000$ |                    |


---

---
title: "[COTS 2016] 删除 Brisanje"
layout: "post"
diff: 省选/NOI-
pid: P11305
tag: ['2016', '二分', '哈希 hashing', '后缀数组 SA', 'COCI（克罗地亚）']
---
# [COTS 2016] 删除 Brisanje
## 题目背景


译自 [Izborne Pripreme 2016 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2016/) D1T2。$\texttt{4s,0.5G}$。


为了卡掉理论复杂度较劣的解法，在 Subtask 0 添加了 Hack 数据（#35~#39，感谢 @Hoks 和 @N_z_），同时将时限改为 1.5s。欢迎对数据的加强。

## 题目描述


给定字符串 $s$。

定义 $s(l,r)$ 为 $s$ 第 $l\sim r$ 个字符组成的字符串。

定义 $t(l,r)$ 为 $s$ 删除第 $l\sim r$ 个字符后得到的字符串。

找到最长的区间 $[l,r]$，使得 $s(l,r)$ 在 $t(l,r)$ 中作为子串出现。

## 输入格式

一行一个字符串 $s$。

## 输出格式

输出一个整数，表示最长可能的区间长度。  

## 样例

### 样例输入 #1
```
abcxyzabc

```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
bbcdbcbbcbadadda
```
### 样例输出 #2
```
5
```
## 提示


#### 样例解释

不难注意到 $\texttt{bbcdbcb\underline{bcbad}adda} \to \texttt{bbcd\underline{bcbad}da}$。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le |s| \le 10^5$；
- $s$ 中只有小写字母。


| 子任务编号 | $\vert s\vert \in $ | 得分 |  
| :--: | :--: | :--: | 
| $ 1 $    | $ [1,400] $    |   $ 16 $   |  
| $ 2 $    | $ (400,5000] $   |  $ 24 $   |  
| $ 3 $    | $ (5000,10^5]$ | $ 60 $   |  




---

---
title: "[KOI 2021 Round 2] 公共括号子串字典序"
layout: "post"
diff: 省选/NOI-
pid: P12727
tag: ['2021', '后缀数组 SA', 'KOI（韩国）']
---
# [KOI 2021 Round 2] 公共括号子串字典序
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

给定两个只由左括号 `(` 与右括号 `)` 构成的字符串 $A$ 和 $B$，以及一个自然数 $K$。

我们定义集合 $S(A, B)$ 表示：所有既是字符串 $A$ 的子串、又是字符串 $B$ 的子串，并且是一个**合法括号序列**的不同字符串所组成的集合。

你的任务是判断 $S(A, B)$ 的大小是否不少于 $K$。如果不小于，则输出 $S(A, B)$ 中**按字典序排列后的第 $K$ 个字符串**；否则，输出 $-1$。

你需要在一个输入数据中处理 $T$ 个测试用例。

### 合法括号序列的定义

一个合法括号序列定义如下：

- 单个括号对构成的字符串 `()` 是合法括号序列。
- 若 $X$ 是合法括号序列，则 $(X)$ 也是合法括号序列。
- 若 $X$ 和 $Y$ 都是合法括号序列，则将它们连接而成的 $XY$ 也是合法括号序列。
- 所有合法括号序列都只能通过上述三条规则构造。

例如：`((()(())))` 和 `(())()()` 是合法括号序列，而 `(()` 和 `)((()()` 都不是。

### 子串的定义

给定长度为 $l$ 的字符串 $s$ 和两个整数 $i, j$，其中 $1 \leq i \leq j \leq l$，则 $s[i..j]$ 表示从 $s$ 的第 $i$ 个字符到第 $j$ 个字符组成的子字符串。

例如若 $s = \texttt{()(()()}$，则 $s[1..5] = \texttt{(()(}$，$s[1..7] = \texttt{()(()()}$，因此 `(()(` 和 `()(()()` 都是 $s$ 的子串。但 `)()(` 不是该字符串的子串。

### 字典序的定义

给定两个字符串 $s_1[1..l_1]$ 和 $s_2[1..l_2]$，我们说 $s_1$ 在字典序上早于 $s_2$，当且仅当满足以下任一条件：

- $s_1$ 是 $s_2$ 的前缀，且 $l_1 < l_2$
- 存在最小的 $i$ 满足 $s_1[i] \ne s_2[i]$ 且 $s_1[i] < s_2[i]$

在本题中，左括号 `'('` 比右括号 `')'` 更小，即 `'(' < ')'`。这与 C++、Java 和 Python 中的字符串比较方式一致。
## 输入格式

第一行包含一个整数 $T$，表示测试用例的个数。

接下来的 $T$ 行中，每行描述一个测试用例，包含字符串 $A$、字符串 $B$ 和整数 $K$，它们之间用一个空格隔开。

## 输出格式

对于每个测试用例，按输入顺序依次输出一行：

- 若 $|S(A, B)| < K$，输出 $-1$
- 否则，输出 $S(A, B)$ 中字典序第 $K$ 小的字符串
## 样例

### 样例输入 #1
```
3
()((())) (()((())))() 3
))(()(((( )())))))( 1
())) )))))(()) 4
```
### 样例输出 #1
```
()
()
-1
```
## 提示

**约束条件**

设 $\sum |A|$ 表示一个输入数据中所有测试用例的字符串 $A$ 的总长度之和，$\sum |B|$ 类似。

- $1 \leq T \leq 500\,000$
- 每个字符串 $A$ 和 $B$ 均由 `'('` 和 `')'` 组成，且长度均不少于 1
- $1 \leq K \leq 10^{18}$
- $\sum |A| \leq 500\,000$
- $\sum |B| \leq 500\,000$

**子任务**

1. （4 分）$\sum |A| \leq 100$，$\sum |B| \leq 100$
2. （11 分）$\sum |A| \leq 1\,000$，$\sum |B| \leq 1\,000$
3. （16 分）$\sum |A| \leq 10\,000$，$\sum |B| \leq 10\,000$，且 $A = B$，$K = 1$
4. （25 分）$\sum |A| \leq 10\,000$，$\sum |B| \leq 10\,000$
5. （10 分）$A = B$，$K = 1$
6. （12 分）$A = B$
7. （9 分）$K = 1$
8. （13 分）无额外约束条件


---

---
title: "[KOI 2021 Round 2] 最长公共括号子串"
layout: "post"
diff: 省选/NOI-
pid: P12729
tag: ['2021', '后缀数组 SA', 'KOI（韩国）']
---
# [KOI 2021 Round 2] 最长公共括号子串
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

给定两个仅由左括号 `(` 和右括号 `)` 组成的字符串 $A$ 和 $B$。

我们定义 $S(A, B)$ 为以下所有字符串的集合：

- 是 $A$ 的子串；
- 是 $B$ 的子串；
- 并且是一个**合法括号序列**；
- 集合中元素互不相同。

请你判断 $S(A, B)$ 是否为空集。如果不是，请计算出 $S(A, B)$ 中最长字符串的长度。

你需要解决一个输入中给出的 $T$ 个测试用例。

### 合法括号序列的定义

合法括号序列的定义如下：

- 单独的一对括号 `()` 是合法括号序列；
- 若 $X$ 是合法括号序列，则用括号将其包围后的 $(X)$ 也是合法括号序列；
- 若 $X$ 和 $Y$ 都是合法括号序列，则其连接后的 $XY$ 也是合法括号序列；
- 所有合法括号序列都只能通过以上三种规则构造。

例如：`((()(())))` 和 `(())()()` 是合法括号序列，而 `(()` 和 `)((()()` 都不是合法括号序列。

### 子串的定义

给定一个长度为 $l$ 的字符串 $s$，以及满足 $1 \leq i \leq j \leq l$ 的两个整数 $i$ 和 $j$，则 $s[i..j]$ 表示从第 $i$ 个字符开始到第 $j$ 个字符为止的连续子串。

例如若 $s = \texttt{()(()()}$，则 $s[3..5] = \texttt{(()}$，$s[4..7] = \texttt{()()}$，因此 `(()` 和 `()()` 都是该字符串的子串。但 `)()(` 不是其子串。
## 输入格式

第一行包含一个整数 $T$，表示测试用例数量。

接下来 $T$ 行，每行由两个字符串 $A$ 和 $B$ 组成，中间以一个空格隔开，表示一个测试用例。

## 输出格式

对于每个测试用例，按顺序输出一行：

- 若 $S(A, B)$ 是空集，输出 $0$
- 否则，输出 $S(A, B)$ 中最长字符串的长度
## 样例

### 样例输入 #1
```
3
()((())) (()((())))()
))(()(((( )())))))(
())) )))))(())
```
### 样例输出 #1
```
8
2
2
```
## 提示

**约束条件**

设 $\sum |A|$ 表示输入中所有测试用例的字符串 $A$ 的总长度之和，$\sum |B|$ 定义相同。

- $1 \leq T \leq 500\,000$
- 每个字符串 $A$ 和 $B$ 均由 `'('` 和 `')'` 构成，长度均不少于 1
- $\sum |A| \leq 500\,000$
- $\sum |B| \leq 500\,000$

**子任务**

1. （5 分）$\sum |A| \leq 100$，$\sum |B| \leq 100$
2. （13 分）$\sum |A| \leq 1\,000$，$\sum |B| \leq 1\,000$
3. （23 分）$\sum |A| \leq 10\,000$，$\sum |B| \leq 10\,000$
4. （17 分）所有测试用例中均满足 $A = B$
5. （42 分）无额外约束条件


---

---
title: "[GCJ Farewell Round #4] Genetic Sequences"
layout: "post"
diff: 省选/NOI-
pid: P12962
tag: ['2023', '后缀自动机 SAM', 'ST 表', '后缀数组 SA', 'Google Code Jam']
---
# [GCJ Farewell Round #4] Genetic Sequences
## 题目描述

Margaret researches genetic sequences. She is analysing two sequences $\mathbf{A}$ and $\mathbf{B}$ from a new kind of life that does not use the typical four letter genetic alphabet. The code for the genetic sequences conveniently requires 26 letters represented by the uppercase English letters 'A' through 'Z'.

Margaret wants to compare the sequences $\mathbf{A}$ and $\mathbf{B}$. The best way to do this is to do a series of sequence analysis tests. Each test involves taking a prefix from $\mathbf{A}$ containing only the first $\mathbf{P}$ letters from $\mathbf{A}$, which is called the $\mathbf{A}$-prefix. Each test also involves taking a suffix from $\mathbf{B}$ containing only the last $\mathbf{S}$ letters from $\mathbf{B}$, which is called the $\mathbf{B}$-suffix. Margaret then needs to compare the $\mathbf{A}$-prefix to the $\mathbf{B}$-suffix. A substring is a subsequence of contiguous letters. A substring from the $\mathbf{A}$-prefix matches the $\mathbf{B}$-suffix if the $\mathbf{B}$-suffix starts with that substring. That is, the substring is a prefix of the $\mathbf{B}$-suffix. The result of a test is the length of the longest substring from the $\mathbf{A}$-prefix that matches the $\mathbf{B}$-suffix.

Margaret needs some software to determine the outcome of a batch of $\mathbf{Q}$ sequence analysis tests. Note that each test is independent. Margaret has many copies of $\mathbf{A}$ and $\mathbf{B}$ and a new one is used for each test.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case begins with a line containing two strings and an integer, $\mathbf{A}$, $\mathbf{B}$, and $\mathbf{Q}$ respectively. Each test case ends with $\mathbf{Q}$ lines, the $i$-th of which contains two integers $\mathbf{P}_i$ and $\mathbf{S}_i$, which are the prefix and suffix sizes for the $i$-th sequence analysis test.

## 输出格式

For each test case, output one line containing Case #$x$: $y_1$ $y_2$ $\ldots$ $y_{\mathbf{Q}}$, where $x$ is the test case number (starting from 1) and $y_i$ is the answer to the $i$-th query in the input.
## 样例

### 样例输入 #1
```
3
ABCABAC CABABA 3
3 6
7 6
6 5
BANANA HABANA 2
5 4
5 5
ABC ABD 1
2 1
```
### 样例输出 #1
```
Case #1: 1 4 3
Case #2: 4 1
Case #3: 0
```
## 提示

**Sample Explanation**

In Sample Case #1, there are 3 tests. The prefix $\mathbf{A B C}$ from $\mathbf{A}$ and the complete suffix $\mathbf{C A B A B A}$ from $\mathbf{B}$ are compared in the first test. The answer is 1, since $\mathbf{c}$ is the longest substring that is contained in $\mathbf{A B C}$ and is a prefix of $\mathbf{C A B A B A}$. In the second test, $\mathbf{A B C A B A C}$ is tested against $\mathbf{C A B A B A}$ and the longest match is $\mathbf{C A B A}$. In the third test, $\mathbf{A B C A B A}$ is tested against $\mathbf{A B A B A}$ and the longest match is $\mathbf{A B A}$.

In Sample Case #2, there are 2 tests. In the first, $\mathbf{B A N A N}$ is tested against $\mathbf{B A N A}$, and the longest match is $\mathbf{B A N A}$. In the second, $\mathbf{B A N A N}$ is tested against $\mathbf{A B A N A}$, and the longest match is $\mathbf{A}$.

In Sample Case #3, there is one test. In it, $\mathbf{A B}$ is tested against $\mathbf{d}$. Since there is no match the answer is 0.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{P}_{i} \leq$ the length of $\mathbf{A}$.
- $1 \leq \mathbf{S}_{i} \leq$ the length of $\mathbf{B}$.

**Test Set 1 (5 Pts, Visible Verdict)**

- $1 \leq$ the length of $\mathbf{A} \leq 3000$.
- $1 \leq$ the length of $\mathbf{B} \leq 3000$.
- $1 \leq \mathbf{Q} \leq 3000$.

**Test Set 2 (17 Pts, Hidden Verdict)**

- $1 \leq$ the length of $\mathbf{A} \leq 10^{5}$.
- $1 \leq$ the length of $\mathbf{B} \leq 10^{5}$.
- The sum of the lengths of $\mathbf{A}$ over all test cases is $\leq 5 \times 10^{5}$
- The sum of the lengths of $\mathbf{B}$ over all test cases is $\leq 5 \times 10^{5}$
- $1 \leq \mathbf{Q} \leq 10^{5}$.


---

---
title: "[CERC 2021] Repetitions"
layout: "post"
diff: 省选/NOI-
pid: P13772
tag: ['2021', '后缀数组 SA', 'ICPC', 'Z 函数', 'CERC']
---
# [CERC 2021] Repetitions
## 题目描述

Bob is an aspiring avant-garde writer. He disdains the use of spaces, punctuation, capital letters and the like; hence, his stories are nothing but long strings of lowercase letters of the English alphabet. Critics have also noted that his style is marked by a certain fondness for repetitions, in the sense that it sometimes happens that two instances of the same substring appear in his story twice in a row, without any other intervening characters.

Bob has submitted his latest masterpiece, a string which happens to be $n$ characters long, to $q$ different literary magazines in the hopes that at least one of them might be willing to publish it. The response was more favourable than he had dared to hope. The editors of all $q$ magazines have expressed willingness to publish some part (i.e. a substring) of his story, but on the condition that he identify the longest repetition (i.e. a shorter substring appearing twice in a row) within that part of the story. The editors intend to remove that part to prevent the story from being too boring. Now Bob needs your help to answer these queries from the editors.

Write a program that, given a string of $n$ letters, $s[1]s[2] \ldots s[n]$, answers $q$ queries of the form "given $a_i$ and $b_i$, how long is the longest string $t$ for which $tt$ appears as a substring of $s[a_i]s[a_i + 1] \ldots s[b_i - 1]s[b_i]$, and where does the leftmost such occurrence begin?"

## 输入格式

The first line contains two integers, $n$ and $q$. The second line contains the string $s$, which is $n$ characters long; all these characters are lowercase letters of the English alphabet. The remaining $q$ lines describe the queries; the $i$-th of these lines contains the integers $a_i$ and $b_i$, separated by a space.

## 输出格式

Output $q$ lines; the $i$-th of these lines must contain two space-separated integers $\ell_i$ and $c_i$. $\ell_i$ should be the length of the longest string $t$ for which $tt$ appears as a substring in $s[a_i]s[a_i + 1] \ldots s[b_i - 1]s[b_i]$, and $c_i$ should be the index at which the leftmost repetition of this length begins, i.e. the smallest integer such that $a_i \leq c_i$, $c_i + 2\ell_i - 1 \leq b_i$ and $s[c_i] \ldots s[c_i + \ell_i - 1] = s[c_i + \ell_i] \ldots s[c_i + 2\ell_i - 1]$. (If $\ell_i = 0$, then $c_i = a_i$ by definition.)
## 样例

### 样例输入 #1
```
10 4
cabaabaaca
4 8
1 9
5 9
8 10
```
### 样例输出 #1
```
1 4
3 2
1 7
0 8

```
## 提示

### Comment

The four queries in the above example refer to the substrings $\textbf{\underline{a}abaa}$, $\textbf{c\underline{aba}abaac}$, $\textbf{ab\underline{a}ac}$, and $\textbf{aca}$; the part shown in bold is the substring referred to by the result of that query (a substring of length $\ell_i$, beginning at index $c_i$). In the last query there is no repetition, so $\ell_4 = 0$.

### Input limits

* $1 \leq n \leq 10^6$
* $1 \leq q \leq 100$
* $1 \leq a_i \leq b_i \leq n$ for each $i = 1, 2, \ldots, q$


---

---
title: "[CERC 2023] Labelled Paths"
layout: "post"
diff: 省选/NOI-
pid: P13856
tag: ['2023', 'Special Judge', '后缀数组 SA', 'ICPC', 'CERC']
---
# [CERC 2023] Labelled Paths
## 题目描述

We are given a directed acyclic graph with $n$ vertices and $m$ edges. Each edge has a label (a string of lowercase letters; possibly even an empty string). We can now extend the concept of labels from edges to paths by defining the label of a path as the concatenation of the labels of the edges that constitute this path (in the same order in which they appear in the path). The smallest path from a start vertex $s$ to a destination vertex $t$ is the path (from $s$ to $t$) whose label is lexicographically smallest (i.e. the earliest in lexicographical order) amongst all the paths from $s$ to $t$. Write a program that, for a given $s$, outputs the smallest paths from $s$ to $t$ for all vertices $t$ of the graph.

## 输入格式

The first line contains four space-separated integers: $n$ (the number of vertices), $m$ (the number of edges), $d$ (the length of the string $A$, on which see below) and $s$ (the number of the start vertex). The vertices are numbered by integers from $1$ to $n$.

The second line contains a string $A$, which is exactly $d$ characters long; all these characters are lowercase letters of the English alphabet. All the edge labels in our graph are substrings of the string $A$.

The remaining $m$ lines describe the edges of the graph. The $i$-th of these lines describes the $i$-th edge and contains four space-separated integers: $u_i$ (the start vertex of this edge), $v_i$ (the end vertex of this edge), $p_i$ and $\ell_i$. The last two of these integers indicate that the label of this edge is the substring of $A$ that begins with the $p_i$-th character of $A$ and is $\ell_i$ characters long. For this purpose we consider the characters of $A$ to be indexed by integers from $1$ to $d$.
## 输出格式

Output $n$ lines, where the $t$-th line (for $t = 1, \dots, n$) describes the smallest path from $s$ to $t$. If there is no path from $s$ to $t$, the line should contain only the integer $0$ and nothing else. Otherwise the line should start with the number of vertices on the path (including vertices $s$ and $t$), followed by the list of those vertices, separated by spaces. If there are several possible solutions, you may output any of them.
## 样例

### 样例输入 #1
```
5 7 6 3
abcbca
3 2 1 1
2 1 5 1
2 5 4 2
3 1 1 2
3 4 3 2
1 4 6 1
5 4 5 2
```
### 样例输出 #1
```
2 3 1
2 3 2
1 3
3 3 1 4
3 3 2 5
```
## 提示

### Comment

In this example, the edge $3 \rightarrow 1$ has the label ab; the edge $1 \rightarrow 4$ has the label a; the smallest path from $3$ to $4$ is $3 \rightarrow 1 \rightarrow 4$, whose label is aba.

### Input limits

- $1 \leq s \leq n \leq 600$
- $1 \leq m \leq 2000$
- $1 \leq d \leq 10^6$
- $1 \leq u_i \leq n$, $1 \leq v_i \leq n$, $u_i \neq v_i$ (for all $i = 1, \dots, m$)
- $1 \leq p_i$, $0 \leq \ell_i$, $p_i + \ell_i - 1 \leq d$ (for all $i = 1, \dots, m$)
- The graph is acyclic and has no parallel edges (i.e. from $i \neq j$ it follows that $u_i \neq u_j$ and/or $v_i \neq v_j$).



---

---
title: "[NOI2015] 品酒大会"
layout: "post"
diff: 省选/NOI-
pid: P2178
tag: ['2015', '并查集', 'NOI', '后缀数组 SA']
---
# [NOI2015] 品酒大会
## 题目描述

一年一度的“幻影阁夏日品酒大会”隆重开幕了。大会包含品尝和趣味挑战 两个环节，分别向优胜者颁发“首席品酒家”和“首席猎手”两个奖项，吸引了众多品酒师参加。


在大会的晚餐上，调酒师 Rainbow 调制了 $n$ 杯鸡尾酒。这 $n$ 杯鸡尾酒排成一行，其中第 $n$ 杯酒 ($1 ≤ i ≤ n$) 被贴上了一个标签 $s_i$ ，每个标签都是 $26$ 个小写 英文字母之一。设 $str(l, r)$ 表示第 $l$ 杯酒到第 $r$ 杯酒的 $r - l + 1$ 个标签顺次连接构成的字符串。若 $str(p, p_0) = str(q, q_0)$，其中 $1 ≤ p ≤ p_0 ≤ n$, $1 ≤ q ≤ q_0 ≤ n$, $p ≠ q$，$p_0-p+1 = q_0 - q + 1 = r$ ，则称第 $p$ 杯酒与第 $q$ 杯酒是“ $r$ 相似” 的。当然两杯“ $r$ 相似”($r > 1$)的酒同时也是“ $1$ 相似”、“ $2$ 相似”、……、“ $(r - 1)$ 相似”的。特别地，对于任意的 $1 ≤ p ,q ≤ n,p  ≠  q$，第 $p$ 杯酒和第 $q$ 杯酒都 是“ $0$ 相似”的。


在品尝环节上，品酒师 Freda 轻松地评定了每一杯酒的美味度，凭借其专业的水准和经验成功夺取了“首席品酒家”的称号，其中第 $i$ 杯酒 ($1 ≤ i ≤ n$) 的 美味度为 $a_i$ 。现在 Rainbow 公布了挑战环节的问题：本次大会调制的鸡尾酒有一个特点，如果把第 $p$ 杯酒与第 $q$ 杯酒调兑在一起，将得到一杯美味度为 $a_p\times a_q$ 的 酒。现在请各位品酒师分别对于 $r = 0,1,2,⋯,n-1$ ，统计出有多少种方法可以 选出 $2$ 杯“ $r$ 相似”的酒，并回答选择 $2$ 杯“$r$ 相似”的酒调兑可以得到的美味度的最大值。

## 输入格式

第 $1$ 行包含 $1$ 个正整数 $n$ ，表示鸡尾酒的杯数。

第 $2$ 行包含一个长度为 $n$ 的字符串 $S$，其中第 $i$ 个字符表示第 $i$ 杯酒的标签。

第 $3$ 行包含 $n$ 个整数，相邻整数之间用单个空格隔开，其中第 $i$ 个整数表示第 $i$ 杯酒的美味度 $a_i$ 。

## 输出格式

包括 $n$ 行。

第 $i$ 行输出 $2$ 个整数，中间用单个空格隔开。第 $1$ 个整 数表示选出两杯“ $(i - 1)$ 相似”的酒的方案数，第 2 个整数表示选出两杯 “ $(i - 1)$ 相似”的酒调兑可以得到的最大美味度。若不存在两杯“ $(i - 1)$ 相似” 的酒，这两个数均为 $0$ 。

## 样例

### 样例输入 #1
```
10
ponoiiipoi
2 1 4 7 4 8 3 6 4 7
```
### 样例输出 #1
```
45 56
10 56
3 32
0 0
0 0
0 0
0 0
0 0
0 0
0 0
```
### 样例输入 #2
```
12
abaabaabaaba
1 -2 3 -4 5 -6 7 -8 9 -10 11 -12

```
### 样例输出 #2
```
66 120
34 120
15 55
12 40
9 27
7 16
5 7
3 -4
2 -4
1 -4
0 0
0 0
```
## 提示

【样例说明 1】

用二元组 $(p, q)$ 表示第 $p$ 杯酒与第 $q$ 杯酒。

$0$ 相似：所有 $45$ 对二元组都是 $0$ 相似的，美味度最大的是 $8 × 7 = 56 $。

$1$ 相似： $(1,8) (2,4) (2,9) (4,9) (5,6) (5,7) (5,10) (6,7) (6,10) (7,10) $，最大的 $8 × 7 = 56$ 。

$2$ 相似： $(1,8) (4,9) (5,6)$ ，最大的 $4 × 8 = 32$ 。

没有 $3,4,5, ⋯ ,9$ 相似的两杯酒，故均输出 $0$ 。



 ![](https://cdn.luogu.com.cn/upload/pic/1508.png) 

【时限1s，内存512M】



---

---
title: "[SCOI2012] 喵星球上的点名"
layout: "post"
diff: 省选/NOI-
pid: P2336
tag: ['2012', '四川', '莫队', '各省省选', 'AC 自动机', '后缀数组 SA']
---
# [SCOI2012] 喵星球上的点名
## 题目描述

a180285 幸运地被选做了地球到喵星球的留学生。他发现喵星人在上课前的点名现象非常有趣。

假设课堂上有 $n$ 个喵星人，每个喵星人的名字由**姓**和**名**构成。喵星球上的老师会选择 $m$ 个串来点名，每次读出一个串的时候，如果这个串是一个喵星人的姓或名的**子串**，那么这个喵星人就必须答到。

然而，由于喵星人的字码如此古怪，以至于不能用 ASCII 码来表示。为了方便描述，a180285 决定用数串来表示喵星人的名字。



现在你能帮助 a180285 统计每次点名的时候有多少喵星人答到，以及 $m$ 次点名结束后每个喵星人答到多少次吗？

## 输入格式

首先定义喵星球上的字符串给定方法：

先给出一个正整数 $l$，表示字符串的长度，接下来 $l$ 个整数，第 $i$ 个整数 $a_i$ 表示字符串的第 $i$ 个字符。

输入的第一行有两个整数，分别表示喵星人的个数 $n$ 个点名次数 $m$。  
接下来 $n$ 行，每行两个喵星球上的字符串，按照定义的方法给出，依次表示第 $i$ 只喵的姓和名。  
接下来 $m$ 行，每行一个喵星球上的字符串，表示一个老师点名的串。
## 输出格式

对于每个老师点名的串，输出一行一个整数表示有多少只喵答到。  
然后在最后一行输出 $n$ 个用空格隔开的整数，第 $i$ 个整数表示第 $i$ 个喵星人被点到的次数。

## 样例

### 样例输入 #1
```
2 3
6 8 25 0 24 14 8 6 18 0 10 20 24 0
7 14 17 8 7 0 17 0 5 8 25 0 24 0
4 8 25 0 24
4 7 0 17 0
4 17 0 8 25

```
### 样例输出 #1
```
2
1
0
1 2
```
## 提示

#### 样例 1 解释

事实上样例给出的数据如果翻译成地球上的语言可以这样来看

```plain
2 3
izayoi sakuya
orihara izaya
izay
hara
raiz
```

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n, m \le 10^3$，喵星人的名字总长不超过 $4\times10^3$，点名串的总长不超过 $2\times10^3$。
- 对于$100\%$ 的数据，保证 $1 \leq n\le 5 \times 10^4$，$1 \leq m \le 10^5$，喵星人的名字总长和点名串的总长分别不超过 $10^5$，保证喵星人的字符串中作为字符存在的数不超过 $10^4$ 。


---

---
title: "[SDOI2008] Sandy 的卡片"
layout: "post"
diff: 省选/NOI-
pid: P2463
tag: ['2008', '各省省选', '山东', 'KMP 算法', '后缀数组 SA']
---
# [SDOI2008] Sandy 的卡片
## 题目描述

Sandy 和 Sue 都热衷于收集干脆面中的卡片。

然而，Sue 收集卡片是因为卡片上漂亮的人物形象，而 Sandy 则是为了积攒卡片兑换超炫的人物模型。

每一张卡片都由一些数字进行标记，第 $i$ 张卡片的序列长度为 $M_i$，要想兑换人物模型，首先必须要集够 $N$ 张卡片，对于这 $N$ 张卡片，如果他们都有一个相同的子串长度为 $k$，则可以兑换一个等级为 $k$ 的人物模型。相同的定义为：两个子串长度相同且一个串的全部元素加上一个数就会变成另一个串。

Sandy 的卡片数远远小于要求的 $N$，于是 Sue 决定在 Sandy 的生日将自己的卡片送给 Sandy，在 Sue 的帮助下，Sandy 终于集够了 $N$ 张卡片，但是，Sandy 并不清楚他可以兑换到哪个等级的人物模型，现在，请你帮助 Sandy 和 Sue，看看他们最高能够得到哪个等级的人物模型。
## 输入格式

第一行为一个数 $N$，表示可以兑换人物模型最少需要的卡片数，即 Sandy 现在有的卡片数。

第 $i+1$ 行到第 $i+N$ 行每行第一个数为第 $i$ 张卡片序列的长度 $M_i$，之后 $j+1$ 到 $j+1+M_i$ 个数，用空格分隔，分别表示序列中的第 $j$ 个数。
## 输出格式

一个数 $k$，表示可以获得的最高等级。
## 样例

### 样例输入 #1
```
2
2 1 2
3 4 5 9

```
### 样例输出 #1
```
2
```
## 提示

$30\%$ 的数据保证 $n\le50$

$100\%$ 的数据保证 $n\le1000,M\le1000,2\le M_i\le101$

update：题面上数据范围 $M_i$ 和 $M$ 的范围其实是一个东西… 真实数据范围: $40\le n\le1000,2\le M_i\le101$,字符串中的每个数字的大小范围为 $[0,1864]$。



---

---
title: "[HAOI2016] 找相同字符"
layout: "post"
diff: 省选/NOI-
pid: P3181
tag: ['字符串', '2016', '河南', '后缀数组 SA']
---
# [HAOI2016] 找相同字符
## 题目描述

给定两个字符串，求出在两个字符串中各取出一个子串使得这两个子串相同的方案数。两个方案不同当且仅当这两个子串中有一个位置不同。

## 输入格式

两行，两个字符串 $s_1,s_2$，长度分别为 $n_1,n_2$。

## 输出格式

输出一个整数表示答案。

## 样例

### 样例输入 #1
```
aabb
bbaa
```
### 样例输出 #1
```
10
```
## 提示

$1\le n_1,n_2\le 2\times 10^5$，字符串中只有小写字母。


---

---
title: "[APIO2014] 回文串"
layout: "post"
diff: 省选/NOI-
pid: P3649
tag: ['字符串', '2014', 'APIO', '后缀自动机 SAM', '后缀数组 SA', '回文自动机 PAM']
---
# [APIO2014] 回文串
## 题目描述

给你一个由小写拉丁字母组成的字符串 $s$。我们定义 $s$ 的一个子串的存在值为这个子串在 $s$ 中出现的次数乘以这个子串的长度。

对于给你的这个字符串 $s$，求所有回文子串中的最大存在值。

## 输入格式

一行，一个由小写拉丁字母（a~z）组成的非空字符串 $s$。

## 输出格式

输出一个整数，表示所有回文子串中的最大存在值。

## 样例

### 样例输入 #1
```
abacaba

```
### 样例输出 #1
```
7

```
### 样例输入 #2
```
www
```
### 样例输出 #2
```
4
```
## 提示

【样例解释1】

用 $\lvert s \rvert$ 表示字符串 $s$ 的长度。

一个字符串 $s_1 s_2 \dots s_{\lvert s \rvert}$ 的子串是一个非空字符串 $s_i s_{i+1} \dots s_j$，其中 $1 \leq i \leq j \leq \lvert s \rvert$。每个字符串都是自己的子串。

一个字符串被称作回文串当且仅当这个字符串从左往右读和从右往左读都是相同的。

这个样例中，有 $7$ 个回文子串 a，b，c，aba，aca，bacab，abacaba。他们的存在值分别为 $4, 2, 1, 6, 3, 5, 7$。

所以回文子串中最大的存在值为 $7$。



第一个子任务共 8 分，满足 $1 \leq \lvert s \rvert \leq 100$。

第二个子任务共 15 分，满足 $1 \leq \lvert s \rvert \leq 1000$。

第三个子任务共 24 分，满足 $1 \leq \lvert s \rvert \leq 10000$。

第四个子任务共 26 分，满足 $1 \leq \lvert s \rvert \leq 100000$。

第五个子任务共 27 分，满足 $1 \leq \lvert s \rvert \leq 300000$。



---

---
title: "[TJOI2017] DNA"
layout: "post"
diff: 省选/NOI-
pid: P3763
tag: ['2017', '各省省选', '后缀数组 SA', '快速傅里叶变换 FFT', '天津']
---
# [TJOI2017] DNA
## 题目描述

加里敦大学的生物研究所，发现了决定人喜不喜欢吃藕的基因序列 $S$,有这个序列的碱基序列就会表现出喜欢吃藕的性状，但是研究人员发现对碱基序列 $S$，任意修改其中不超过 $3$ 个碱基，依然能够表现出吃藕的性状。现在研究人员想知道这个基因在 DNA 链 $S_0$ 上的位置。所以你需要统计在一个表现出吃藕性状的人的 DNA 序列 $S_0$ 上，有多少个连续子串可能是该基因，即有多少个 $S_0$ 的连续子串修改小于等于三个字母能够变成 $S$。

## 输入格式

第一行有一个整数 $T$，表示有几组数据。

每组数据第一行一个长度不超过 $10^5$ 的碱基序列 $S_0$。

每组数据第二行一个长度不超过 $10^5$ 的吃藕基因序列 $S$。

## 输出格式

共 $T$ 行，第 $i$ 行表示第 $i$ 组数据中，在 $S_0$中有多少个与 $S$ 等长的连续子串可能是表现吃藕性状的碱基序列。

## 样例

### 样例输入 #1
```
1
ATCGCCCTA
CTTCA
```
### 样例输出 #1
```
2
```
## 提示

对于 $20\%$ 的数据，$S_0,S$ 的长度不超过 $10^4$。

对于 $100\%$ 的数据，$S_0,S$ 的长度不超过 $10^5$，$0\lt T\leq 10$。

注：DNA 碱基序列只有 ATCG 四种字符。


---

---
title: "【模板】后缀自动机（SAM）"
layout: "post"
diff: 省选/NOI-
pid: P3804
tag: ['字符串', '后缀自动机 SAM', 'O2优化', '后缀数组 SA']
---
# 【模板】后缀自动机（SAM）
## 题目描述

给定一个只包含小写字母的字符串 $S$。

请你求出 $S$ 的所有出现次数不为 $1$ 的子串的出现次数乘上该子串长度的最大值。

## 输入格式

一行一个仅包含小写字母的字符串 $S$。
## 输出格式

一个整数，为所求答案。
## 样例

### 样例输入 #1
```
abab
```
### 样例输出 #1
```
4
```
## 提示

对于 $10 \%$ 的数据，$\lvert S \rvert \le 1000$。  
对于 $100\% $的数据，$1 \le \lvert S \rvert \le {10}^6$。

- 2023.7.30：添加一组 hack 数据。


---

---
title: "【模板】后缀排序"
layout: "post"
diff: 省选/NOI-
pid: P3809
tag: ['字符串', 'O2优化', '排序', '后缀数组 SA']
---
# 【模板】后缀排序
## 题目背景

这是一道模板题。

## 题目描述

读入一个长度为 $ n $ 的由大小写英文字母或数字组成的字符串，请把这个字符串的所有非空后缀按字典序（用 ASCII 数值比较）从小到大排序，然后按顺序输出后缀的第一个字符在原串中的位置。位置编号为 $ 1 $ 到 $ n $。

## 输入格式

一行一个长度为 $ n $ 的仅包含大小写英文字母或数字的字符串。

## 输出格式

一行，共 $n$ 个整数，表示答案。

## 样例

### 样例输入 #1
```
ababa
```
### 样例输出 #1
```
5 3 1 4 2
```
## 提示

$1\le n \le 10^6$。



---

---
title: "[TJOI2015] 弦论"
layout: "post"
diff: 省选/NOI-
pid: P3975
tag: ['2015', '各省省选', '后缀自动机 SAM', '枚举', '后缀数组 SA', '天津']
---
# [TJOI2015] 弦论
## 题目描述

为了提高智商，ZJY 开始学习弦论。这一天，她在《String theory》中看到了这样一道问题：对于一个给定的长度为 $n$ 的字符串，求出它的第 $k$ 小子串是什么。你能帮帮她吗?

## 输入格式

第一行是一个仅由小写英文字母构成的字符串 $s$。

第二行为两个整数 $t$ 和 $k$，$t$ 为 $0$ 则表示不同位置的相同子串算作一个，$t$ 为 $1$ 则表示不同位置的相同子串算作多个。$k$ 的意义见题目描述。

## 输出格式

输出数据仅有一行,该行有一个字符串，为第 $k$ 小的子串。若子串数目不足 $k$ 个，则输出 $-1$。

## 样例

### 样例输入 #1
```
aabc
0 3
```
### 样例输出 #1
```
aab
```
### 样例输入 #2
```
aabc
1 3
```
### 样例输出 #2
```
aa
```
### 样例输入 #3
```
aabc
1 11
```
### 样例输出 #3
```
-1
```
## 提示

### 数据范围

对于 $10\%$ 的数据，$n\leq 1000$。

对于 $50\%$ 的数据，$t = 0$。

对于 $100\%$ 的数据，$1\leq n \leq 5 \times 10^5$，$0\leq t \leq 1$，$1\leq k \leq 10^9$。



---

---
title: "[JSOI2007] 字符加密"
layout: "post"
diff: 省选/NOI-
pid: P4051
tag: ['字符串', '2007', '各省省选', '江苏', '后缀数组 SA']
---
# [JSOI2007] 字符加密
## 题目描述

喜欢钻研问题的JS 同学，最近又迷上了对加密方法的思考。一天，他突然想出了一种他认为是终极的加密办法：把需要加密的信息排成一圈，显然，它们有很多种不同的读法。

例如‘JSOI07’，可以读作：  JSOI07 SOI07J OI07JS I07JSO 07JSOI 7JSOI0 把它们按照字符串的大小排序： 07JSOI 7JSOI0 I07JSO JSOI07 OI07JS SOI07J 读出最后一列字符：I0O7SJ，就是加密后的字符串（其实这个加密手段实在很容易破解，鉴于这是突然想出来的，那就^^）。 但是，如果想加密的字符串实在太长，你能写一个程序完成这个任务吗？

## 输入格式

输入文件包含一行，欲加密的字符串。注意字符串的内容不一定是字母、数字，也可以是符号等。

## 输出格式

输出一行，为加密后的字符串。

## 样例

### 样例输入 #1
```
JSOI07
```
### 样例输出 #1
```
I0O7SJ
```
## 提示

对于40%的数据字符串的长度不超过10000。

对于100%的数据字符串的长度不超过100000。



---

---
title: "[SDOI2016] 生成魔咒"
layout: "post"
diff: 省选/NOI-
pid: P4070
tag: ['字符串', '2016', '各省省选', '平衡树', '山东', '后缀自动机 SAM', '后缀数组 SA']
---
# [SDOI2016] 生成魔咒
## 题目描述

魔咒串由许多魔咒字符组成，魔咒字符可以用数字表示。例如可以将魔咒字符 $1,2$ 拼凑起来形成一个魔咒串 $[1,2]$。

一个魔咒串 $S$ 的非空字串被称为魔咒串 $S$ 的生成魔咒。

例如 $S=[1,2,1]$ 时，它的生成魔咒有 $[1],[2],[1,2],[2,1],[1,2,1]$ 五种。$S=[1,1,1]$ 时，它的生成魔咒有 $[1],[1,1],[1,1,1]$ 三种，最初 S 为空串。  

共进行 $n$ 次操作，每次操作是在 $S$ 的结尾加入一个魔咒字符。每次操作后都需要求出，当前的魔咒串 $S$ 共有多少种生成魔咒。

## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个数，第 $i$ 个数表示第 $i$ 次操作加入的魔咒字符 $x_i$。

## 输出格式

输出 $n$ 行，每行一个数。  
第 $i$ 行的数表示第 $i$ 次操作后 $S$ 的生成魔咒数量。

## 样例

### 样例输入 #1
```
7
1 2 3 3 3 1 2
```
### 样例输出 #1
```
1
3
6
9
12
17
22
```
## 提示

#### 数据规模与约定   
对于 $10\%$ 的数据，保证 $1 \le n \le 10$；  
对于 $30\%$ 的数据，保证 $1 \le n \le 100$；  
对于 $60\%$ 的数据，保证 $1 \le n \le 10^3$；   
对于 $100\%$ 的数据，保证 $1 \le n \le 10^5$，$1 \leq x_i \leq 10^9$。



---

---
title: "[USACO17DEC] Standing Out from the Herd P"
layout: "post"
diff: 省选/NOI-
pid: P4081
tag: ['字符串', '2017', 'USACO', '后缀自动机 SAM', '后缀数组 SA']
---
# [USACO17DEC] Standing Out from the Herd P
## 题目描述

Just like humans, cows often appreciate feeling they are unique in some way. Since Farmer John's cows all come from the same breed and look quite similar, they want to measure uniqueness in their names.

Each cow's name has some number of substrings. For example, "amy" has substrings {a, m, y, am, my, amy}, and "tommy" would have the following substrings: {t, o, m, y, to, om, mm, my, tom, omm, mmy, tomm, ommy, tommy}.

A cow name has a "uniqueness factor" which is the number of substrings of that name not shared with any other cow. For example, If amy was in a herd by herself, her uniqueness factor would be 6. If tommy was in a herd by himself, his uniqueness factor would be 14. If they were in a herd together, however, amy's uniqueness factor would be 3 and tommy's would be 11.

Given a herd of cows, please determine each cow's uniqueness factor.
## 输入格式

The first line of input will contain $N$ ($1 \le N \le 10^5$). The following $N$ lines will each contain the name of a cow in the herd. Each name will contain only lowercase characters a-z. The total length of all names will not exceed $10^5$.

## 输出格式

Output $N$ numbers, one per line, describing the uniqueness factor of each cow.

## 样例

### 样例输入 #1
```
3
amy
tommy
bessie
```
### 样例输出 #1
```
3
11
19
```
## 题目翻译

### 题目描述

就像人类一样，奶牛也常常希望在某些方面感到自己与众不同。由于 Farmer John 的奶牛都来自同一品种且外观非常相似，它们希望通过名字来衡量独特性。

每头奶牛的名字都有一些子字符串。例如，"amy" 的子字符串为 {a, m, y, am, my, amy}，而 "tommy" 的子字符串为 {t, o, m, y, to, om, mm, my, tom, omm, mmy, tomm, ommy, tommy}。

一头奶牛的名字有一个“独特性因子”，即该名字中不与任何其他奶牛共享的子字符串的数量。例如，如果 amy 独自在一个牛群中，她的独特性因子为 6。如果 tommy 独自在一个牛群中，他的独特性因子为 14。然而，如果它们在一个牛群中，amy 的独特性因子为 3，而 tommy 的独特性因子为 11。

给定一个牛群，请计算每头奶牛的独特性因子。

### 输入格式

输入的第一行包含 $N$（$1 \le N \le 10^5$）。接下来的 $N$ 行每行包含牛群中一头奶牛的名字。每个名字仅包含小写字母 a-z。所有名字的总长度不超过 $10^5$。

### 输出格式

输出 $N$ 个数字，每行一个，表示每头奶牛的独特性因子。


---

---
title: "[HEOI2015] 最短不公共子串"
layout: "post"
diff: 省选/NOI-
pid: P4112
tag: ['2015', '各省省选', '河北', '后缀自动机 SAM', 'O2优化', '广度优先搜索 BFS', '后缀数组 SA']
---
# [HEOI2015] 最短不公共子串
## 题目描述

在虐各种最长公共子串、子序列的题虐的不耐烦了之后，你决定反其道而行之。

下面给出一些定义：

- 一个串的“子串”指的是它的连续的一段，例如 `bcd` 是 `abcdef` 的子串，但 `bde` 不是。
- 一个串的“子序列”指的是它的可以不连续的一段，例如 `bde` 是 `abcdef` 的子串，但 `bdd` 不是。

下面，给两个小写字母串 $a, b$，请你计算：

1. $a$ 的一个最短的子串，它不是 $b$ 的子串。
2. $a$ 的一个最短的子串，它不是 $b$ 的子序列。
3. $a$ 的一个最短的子序列，它不是 $b$ 的子串。
4. $a$ 的一个最短的子序列，它不是 $b$ 的子序列。

## 输入格式

有两行，每行一个小写字母组成的字符串，分别代表 $a$ 和 $b$。

## 输出格式

输出 $4$ 行，每行一个整数，依次表示以上 $4$ 个问题的答案的长度。如果没有符合要求的答案，输出 $-1$。

## 样例

### 样例输入 #1
```
aabbcc
abcabc
```
### 样例输出 #1
```
2
4
2
4
```
### 样例输入 #2
```
aabbcc
aabbcc
```
### 样例输出 #2
```
-1
-1
2
-1
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $a$ 和 $b$ 的长度都不超过 $20$。
- 对于 $50\%$ 的数据，保证 $a$ 和 $b$ 的长度都不超过 $500$。
- 对于 $100\%$ 的数据，保证 $a$ 和 $b$ 的长度都不超过 $2000$。



---

---
title: "[AHOI2013] 差异"
layout: "post"
diff: 省选/NOI-
pid: P4248
tag: ['2013', '各省省选', '安徽', '后缀自动机 SAM', '后缀数组 SA', '后缀树']
---
# [AHOI2013] 差异
## 题目描述

给定一个长度为 $n$ 的字符串 $S$，令 $T_i$ 表示它从第 $i$ 个字符开始的后缀。求

$$\displaystyle \sum_{1\leqslant i<j\leqslant n}\operatorname{len}(T_i)+\operatorname{len}(T_j)-2\times\operatorname{lcp}(T_i,T_j)$$

其中，$\text{len}(a)$ 表示字符串 $a$ 的长度，$\text{lcp}(a,b)$ 表示字符串 $a$ 和字符串 $b$ 的最长公共前缀。
## 输入格式

一行，一个字符串 $S$。
## 输出格式

一行，一个整数，表示所求值。
## 样例

### 样例输入 #1
```
cacao
```
### 样例输出 #1
```
54
```
## 提示

#### 数据规模与约定

- 对于 $100\%$ 的数据，保证 $2\le n\le 500000$，且 $S$ 中均为小写字母。


---

---
title: "Annihilate"
layout: "post"
diff: 省选/NOI-
pid: P5028
tag: ['字符串', '后缀数组 SA']
---
# Annihilate
## 题目背景

前情提要：小正方形与黑暗之主展开了大战，最后小正方形击败了黑暗之主，成功从黑暗之主的手上夺下最后一个三角。

三角旋转着，净化着，正当三角即将净化完成时，黑暗之主突然到来，阻断了三角形的净化，吸收了三角的能量。

可是，因为三角的能量太过巨大，导致黑暗之主发生了变异，现在的黑暗之主一次次复制，最终成为了一条蜈蚣……

现在，小正方形还能阻止黑暗之主毁灭世界吗？
## 题目描述

黑暗之主的蜈蚣几乎可以毁灭一切，因此小正方形陷入了苦战……

小正方形现在需要减弱黑暗之主的攻击。

一个黑暗之主的攻击可以用一个仅有小写字母的字符串表示。

现在黑暗之主向小正方形发动了若干攻击，对于两个攻击，小正方形能选出它们最长的公共**子串**，并把这一段消除。

现在小正方形想要知道，对于**任意两个**黑暗之主的攻击，它们的最长公共子串长度是多少，你能帮帮它吗？
## 输入格式

第一行为一个整数 $n$，表示字符串数目。

接下来 $n$ 行，一行一个字符串，保证所有字符串长度之和 <= 1000000


## 输出格式

输出共有 $n$ 行，每行 $n - 1$个正整数

第一行第一个正整数表示第1个串与第2个串的最长公共子串

第二个正整数表示第1个串与第3个串的最长公共子串

……

第二行第一个正整数表示第2个串与第1个串的最长公共子串

以此类推。
## 样例

### 样例输入 #1
```
3
abb
bcc
aba
```
### 样例输出 #1
```
1 2
1 1
2 1
```
## 提示

对于 $30\%$ 的数据，$n <= 5$，每个字符串长度 $<= 500$

对于 $100\%$ 的数据，$2 <= n <= 50$，字符串长度之和 $ <= 1000000$

**注意：本题内存限制仅为 64 MB,请尽量使用内存运用优秀的方法。**

另外，对于占 60 Pts 的测试点，您每通过一个点即可获得 10 Pts

对于剩下的测试点，您只有全部通过才能获得 40 Pts.

**对于所有数据点，不保证数据为随机生成。**


---

---
title: "[JSOI2012] 玄武密码"
layout: "post"
diff: 省选/NOI-
pid: P5231
tag: ['字符串', '2012', '各省省选', '江苏', '后缀自动机 SAM', 'O2优化', 'AC 自动机', '后缀数组 SA']
---
# [JSOI2012] 玄武密码
## 题目背景

在美丽的玄武湖畔，鸡鸣寺边，鸡笼山前，有一块富饶而秀美的土地，人们唤作进香河。相传一日，一缕紫气从天而至，只一瞬间便消失在了进香河中。老人们说，这是玄武神灵将天书藏匿在此。 

很多年后，人们终于在进香河地区发现了带有玄武密码的文字。更加神奇的是，这份带有玄武密码的文字，与玄武湖南岸台城的结构有微妙的关联。于是，漫长的破译工作开始了。
## 题目描述

 经过分析，我们可以用东南西北四个方向来描述台城城砖的摆放，不妨用一个长度为 $n$ 的序列 $s$ 来描述，序列中的元素分别是 `E`，`S`，`W`，`N`，代表了东南西北四向，我们称之为母串。而神秘的玄武密码是由四象的图案描述而成的 $m$ 段文字。这里的四象，分别是东之青龙，西之白虎，南之朱雀，北之玄武，对东南西北四向相对应。 

现在，考古工作者遇到了一个难题。对于每一段文字 $t$，求出其最长的前缀 $p$，满足 $p$ 是 $s$ 的子串。
## 输入格式

第一行有两个整数，分别表示母串的长度 $n$ 和文字段的个数 $m$。

第二行有一个长度为 $n$ 的字符串，表示母串 $s$。

接下来 $m$ 行，每行一个字符串，表示一段带有玄武密码的文字 $t$。
## 输出格式

对于每段文字，输出一行一个整数，表示最长的 $p$ 的长度。
## 样例

### 样例输入 #1
```
7 3
SNNSSNS
NNSS
NNN
WSEE

```
### 样例输出 #1
```
4
2
0
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 100$，$m \leq 50$。
- 对于 $40\%$ 的数据，保证 $n \leq 2 \times 10^4$，$m \leq 2 \times 10^3$。
- 对于 $70\%$ 的数据，保证 $n \leq 10^6$，$m \leq 2 \times 10^4$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^7$，$1 \leq m \leq 10^5$，$1 \leq |t| \leq 100$，$s, t$ 中均只含字母 `E` `S` `W` `N`。


---

---
title: "【XR-1】柯南家族"
layout: "post"
diff: 省选/NOI-
pid: P5346
tag: ['倍增', '离散化', 'O2优化', '可持久化线段树', '可持久化', '后缀数组 SA']
---
# 【XR-1】柯南家族
## 题目背景

xht37 最近沉迷于名侦探柯南。

在某集中，小兰又在怀疑柯南的真实身份了。为了让小兰不再怀疑，柯南编造出自己的家族背景来应对小兰的询问。
## 题目描述

这个家族一开始只有一个人，后来不断有人有了孩子，直到现在，这个家族有 $n$ 个人，第 $n$ 个人正是柯南。易知这个家族构成了一个 $n$ 个点的树形结构。

柯南为了使自己编造的家庭背景更加真实，他给家族中的每个人赋予了一个**智商值**。但是，一个人的**聪明程度**不仅仅只与他的**智商值**有关，还可能与他**祖先的聪明程度**及他**出生的时代**有关。

具体来说，在这个家族中，A 比 B 聪明**当且仅当** A 和 B 满足下面三种情况中的某一种：

1. A 的智商值比 B 的智商值高；
2. A 的智商值与 B 的智商值一样且 A 和 B 有不同的父亲，A 的父亲比 B 的父亲聪明；
3. A 的智商值与 B 的智商值一样且 A 和 B 的父亲是同一个人或某一个人没有父亲，A 比 B 后出生。

有一个很显然的结论是，这个家族中不会有两个人一样聪明。

柯南需要回答小兰的 $q$ 个询问。为了方便说明，假设第 $i$ 个出生的人编号为 $i$。

每个询问是下面三种情况中的某一种：

1. `1 x`：询问编号为 $x$ 的人在整个家族中聪明程度排第几。
2. `2 x k`：询问编号为 $x$ 的人及其祖先中第 $k$ 聪明的人的编号。
3. `3 x k`：询问编号为 $x$ 的人及其后代中第 $k$ 聪明的人的编号。

柯南还有许多案子要办，他不想在回答小兰的问题上浪费时间，他希望你能编程帮他回答小兰的所有询问。
## 输入格式

第 $1$ 行包含两个数 $n, q$，分别表示人数和询问次数。

第 $2$ 行包含 $n-1$ 个数 $f_{2 \dots n}$，其中 $f_i$ 表示 $i$ 的父亲。

第 $3$ 行包含 $n$ 个数 $a_{1 \dots n}$，其中 $a_i$ 表示 $i$ 的智商值。

接下来 $q$ 行每行两个或三个数表示一个合法询问，其中第一个数表示询问种类，后面一个或两个数为询问参数。
## 输出格式

输出 $q$ 行，每行一个数表示询问的答案。
## 样例

### 样例输入 #1
```
5 11
1 1 3 2
1 2 2 1 1
1 1
1 2
1 3
1 4
1 5
2 4 1
2 5 3
3 1 1
3 1 2
3 1 3
3 1 4
```
### 样例输出 #1
```
5
2
1
3
4
3
1
3
2
4
5
```
## 提示

【样例说明】

形成的树如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/eie1mrxb.png)

首先比较编号为 $2,3$ 的两个人，由于** $3$ 号的智商值与 $2$ 号的智商值一样且他们的父亲是同一个人，$3$ 号比 $2$ 号后出生**满足第 $3$ 种情况，因此 $3$ 号比 $2$ 号聪明。

再比较编号为 $4,5$ 的两个人，由于** $4$ 号的智商值与 $5$ 号的智商值一样且他们有不同的父亲，$4$ 号的父亲 $3$ 号比 $5$ 号的父亲 $2$ 号聪明**满足第 $2$ 种情况，因此 $4$ 号比 $5$ 号聪明。

再比较编号为 $1,5$ 的两个人，由于** $5$ 号的智商值与 $1$ 号的智商值一样且 $1$ 号没有父亲，$5$ 号比 $1$ 号后出生**满足第 $3$ 种情况，因此 $5$ 号比 $1$ 号聪明。

再根据第 $1$ 种情况比较编号为 $2,4$ 的两个人，可对 $5$ 人的聪明程度排序：$3 > 2 > 4 > 5 > 1$。

【数据规模与约定】

一共 $10$ 个测试点。

对于前 $20\%$ 的数据，$1 \le n, q \le 10 ^ 3$，每个测试点 $7$ 分，时限 1s。

对于另 $20\%$ 的数据，保证一个人最多只有一个儿子，每个测试点 $9$ 分，时限 4s。

对于另 $20\%$ 的数据，$1 \le n, q \le 10 ^ 5$，每个测试点 $9$ 分，时限 1.5s。

对于另 $20\%$ 的数据，保证只有第一种询问，每个测试点 $12$ 分，时限 1.5s。

对于 $100\%$ 的数据，$1 \le n, q \le 5 \times 10 ^ 5$，$1 \le a_i \le 10 ^ 9$，每个测试点 $13$ 分，时限 2.5s。


---

---
title: "树上后缀排序"
layout: "post"
diff: 省选/NOI-
pid: P5353
tag: ['字符串', '倍增', 'O2优化', '后缀数组 SA']
---
# 树上后缀排序
## 题目描述

给定一棵以 $1$ 为根包含 $n$ 个节点的树，保证对于 $2 \sim n$ 的每个节点，其父亲的编号均小于自己的编号。

每个节点上有一个的字符，一个节点所代表的字符串定义为从当前节点一直到根节点的简单路径上经过的所有字符连起来形成的字符串。

请你给这些字符串按照字典序排序。

特别地，如果两个节点所代表的字符串完全相同，它们的大小由它们父亲排名的大小决定，即谁的父亲排名大谁就更大；如果仍相同，则由它们编号的大小决定，即谁的编号大谁就更大。
## 输入格式

第一行包含一个正整数 $n$。

第二行包含 $n-1$ 个数 $f_{2 \dots n}$，其中 $f_i$ 表示 $i$ 的父亲。

第三行为一个包含 $n$ 个**小写字母**的字符串 $s$，其中 $s_i$ 表示编号为 $i$ 的节点上的字符。
## 输出格式

输出一行 $n$ 个正整数，第 $i$ 个正整数表示代表**排名第 $i$ 的字符串**的节点编号。
## 样例

### 样例输入 #1
```
5
1 1 3 2
abbaa
```
### 样例输出 #1
```
1 5 4 2 3
```
## 提示

对于 $20\%$ 的数据，$n \le 10 ^ 3$。

对于 $50\%$ 的数据，$n \le 10 ^ 5$。

对于 $100\%$ 的数据，$1 \le n \le 5 \times 10 ^ 5$。


---

---
title: "[JSOI2015] 串分割"
layout: "post"
diff: 省选/NOI-
pid: P6095
tag: ['2015', '二分', '各省省选', '江苏', '后缀数组 SA']
---
# [JSOI2015] 串分割
## 题目背景

JYY 每天都会在地铁上度过很长的时间。

为了打发时间，JYY 随手写下了一个很长的环形的数字字符串，并且陷入了沉思。
## 题目描述

JYY 写下了一个长度为 $N$ 的，仅包含 `1`，`2`，……，`9` 这 $9$ 种不同字符的环形字符串 $S$。JYY 希望把 $S$ 进行 $K$ 次切割，并分成 $K$ 个非空的子串。对于每一个子串，由于其仅包含数字，我们可以将其看成一个十进制数——因此
经过 $K$ 次切割，JYY 可以得到 $K$ 个不同的十进制数。JYY 希望他得到的这 $K$ 个数中，最大的那一个尽量小。
## 输入格式

第一行包含两个整数 $N$ 和 $K$。

第二行包含一个长度为 $N$ 的字符串 $S$。
## 输出格式

输出一行包含一个正整数，表示最佳分割方案中，JYY 所得到的那 $K$ 个数中，最大的那一个。


## 样例

### 样例输入 #1
```
4 2
4321
```
### 样例输出 #1
```
32
```
## 提示

对于 $100\%$ 的数据，$3\leq N\leq 2\times 10^5$，$2\leq K\leq N$。


---

---
title: "[SNOI2020] 字符串"
layout: "post"
diff: 省选/NOI-
pid: P6793
tag: ['字符串', '2020', '各省省选', '后缀自动机 SAM', '树形 DP', '后缀数组 SA']
---
# [SNOI2020] 字符串
## 题目描述

有两个长度为 $n$ 的由小写字母组成的字符串 $a,b$，取出他们所有长为 $k$ 的子串（各有 $n-k+1$ 个），这些子串分别组成集合 $A,B$。现在要修改 $A$ 中的串，使得 $A$ 和 $B$ 完全相同。可以任意次选择修改 $A$ 中一个串的一段后缀，花费为这段后缀的长度。总花费为每次修改花费之和，求总花费的最小值。
## 输入格式

第一行两个整数 $n,k$ 表示字符串长度和子串长度；   
第二行一个小写字母字符串 $a$；   
第三行一个小写字母字符串 $b$。
## 输出格式

输出一行一个整数表示总花费的最小值。
## 样例

### 样例输入 #1
```
5 3
aabaa
ababa
```
### 样例输出 #1
```
3
```
## 提示

#### 样例说明

对于样例 $1$，所有子串为：$A = \{aab,aba,baa\}, B = \{aba, bab, aba\}$。可以看出有一对 $aba$ 是相同的，另外要把 $aab$ 改成 $aba$（花费 $2$），$baa$ 改成 $bab$（花费 $1$），总花费为 $3$。

#### 数据规模与约定

对于所有数据，$1\le k\le n\le 1.5\times 10^5$。

- 对于 $10\%$ 的数据，$n \le 11$；
- 对于另外 $20\%$ 的数据，$n \le 200$；
- 对于另外 $20\%$ 的数据，$n \le 2000$；
- 对于另外 $10\%$ 的数据，字符串的每一位在小写字母中均匀随机；
- 对于余下 $40\%$ 的数据，无特殊限制。


---

---
title: "SvT"
layout: "post"
diff: 省选/NOI-
pid: P7409
tag: ['字符串', '图论', '后缀自动机 SAM', '虚树', '后缀数组 SA', '后缀树']
---
# SvT
## 题目背景

（我并不想告诉你题目名字是什么鬼）
## 题目描述

有一个长度为  $n$ 的仅包含小写字母的字符串  $S$，下标范围为  $[1,n]$。

现在有若干组询问,对于每一个询问,我们给出若干个后缀（以其在  $S$ 中出现的起始位置来表示），求这些后缀两两之间的 LCP（最长公共前缀）的长度之和。一对后缀之间的 LCP 长度仅统计一遍。



## 输入格式

第一行两个正整数  $n,m$，分别表示  $S$ 的长度以及询问的次数。

接下来一行有一个字符串  $S$。

接下来有  $m$ 组询问，对于每一组询问，均按照以下格式在一行内给出：

首先是一个整数  $t$，表示共有多少个后缀。接下来  $t$ 个整数分别表示  $t$ 个后缀在字符串  $S$ 中的出现位置。
## 输出格式

对于每一组询问，输出一行一个整数，表示该组询问的答案。由于答案可能很大，仅需要输出这个答案对于 $\text{23333333333333333}$ （一个巨大的质数）取模的余数。
## 样例

### 样例输入 #1
```
7 3
popoqqq
1 4
2 3 5
4 1 2 5 6
```
### 样例输出 #1
```
0
0
2
```
## 提示

样例解释:

对于询问一，只有一个后缀 `oqqq`，因此答案为 $0$。

对于询问二，有两个后缀`poqqq`以及`qqq`，两个后缀之间的 LCP 为 $0$，因此答案为 $0$。

对于询问三，有四个后缀 `popoqqq` , `opoqqq` , `qqq` , `qq`，其中只有 `qqq`，`qq` 两个后缀之间的LCP不为 $0$，且长度为 $2$，因此答案为 $2$。

对于 $100\%$ 的测试数据，有 $|S|\le 5\times 10^5$，且 $\sum t\le3\times10^6$。

特别注意:由于另一世界线的某些参数发生了变化，对于一组询问，即使一个后缀出现了多次，也仅算一次。

题目来源：bzoj 3879


---

---
title: "[CERC2018] The ABCD Murderer"
layout: "post"
diff: 省选/NOI-
pid: P7456
tag: ['字符串', '2018', '哈希 hashing', 'AC 自动机', 'KMP 算法', '后缀数组 SA', 'ICPC']
---
# [CERC2018] The ABCD Murderer
## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [The ABCD Murderer](https://contest.felk.cvut.cz/18cerc/solved/abcd.pdf)**

Oscar 特别喜欢看犯罪电影。他钦佩那些罪犯，因为他们富有创造力。他也想展示他的创造力。但很可惜的是，他没什么经验，也想不出来什么原创伎俩。所以他想从已有的招数中寻找灵感。他一直喜欢看罪犯从报纸上剪下字母，然后用这些字母拼勒索信的桥段。然而 Oscar 根本不想抄袭，所以他自己想了一个这种方法的变体。他觉得把字母一个一个拼成文本既无聊又费时间。所以他决定通过剪下一整个单词的方式拼出自己的勒索信。

Oscar 买来一些主流报纸，这样他几乎就有了无限的单词库。他可以多次剪出任意特定的单词。然而，他还是被报纸中出现的的单词集限制。问题是一些单词根本没在报纸中出现。为了让这项工作更简单，他决定去除勒索信中所有的标点符号和空格并且忽略字母的大小写。他同时允许剪出的单词互相重叠，只需要重叠部分相同。现在 Oscar 想知道他至少要剪下多少次单词才能拼成他想要的勒索信。
## 输入格式

第一行包含一个整数 $L$，表示在报纸中发现的单词数；

下一行包含勒索信的内容 $s$。保证内容非空并且只包含小写英文字母。

接下来 $L$ 行，每行包含一个在报纸中出现的单词 $a_i$，保证只出现小写英文字母。这些单词中没有空串，也没有比勒索信长的单词。所有报纸中单词在输入中出现至少一次。
## 输出格式

输出 Oscar 最少要从报纸中剪下多少次单词才能组成勒索信、如果不能组成，输出 $-1$ 。每个单词都要被记实际从报纸剪下那么多次。
## 样例

### 样例输入 #1
```
3
aaaaa
a
aa
aaa
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5
abecedadabra
abec
ab
ceda
dad
ra
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
9
icpcontesticpc
international
collegiate
programming
contest
central
europe
regional
contest
icpc
```
### 样例输出 #3
```
3
```
## 提示

$1≤L,|s|,∑|a_i|≤3×10^5$


---

---
title: "「CGOI-1」大师选徒"
layout: "post"
diff: 省选/NOI-
pid: P7769
tag: ['O2优化', '后缀数组 SA']
---
# 「CGOI-1」大师选徒
## 题目背景

最近有好多人来丑国学习 bc。bc 大师 ac 和 mc 要从所有学生选出一些来传授 bc 技艺。

###### 2021.8.29：添加了一组 hack
## 题目描述

有 $n$ 个学生站成一排，每个学生有一个丑值 $a_i$。现在 ac 和 mc 要**各自**从学生中选取**连续**的一段传授 bc。

由于 ac 和 mc 关系很♂好，所以两人选出的学生必须人数相同，并且**对应位置**上的学生丑值之和均为 $s$。

（比方说，如果 ac 选第 $1$、$2$、$3$ 号学生，mc 选 $3$、$4$、$5$ 号学生，必须满足 $a_1+a_3=a_2+a_4=a_3+a_5=s$）

但 ac 并不知道 mc 所选的学生以及 $s$ 是多少，所以他会给出若干个询问。对于每个询问，你需要回答对于特定的 $s$ 以及 mc 选出的一段学生，ac 是否可以选出另一段学生满足上述要求。

**简化版题意：**

给出 $n$ 及 $n$ 个整数 $a_1,\,a_2,\,\dots,\,a_n$；

$q$ 次询问，每次给出 $s,l,r$，问是否存在 $b$，满足 $\forall k \in [0, r-l]$，$a_{l+k}+a_{b+k}=s$。
## 输入格式

第一行输入两个整数 $n,\,q$，分别表示学生的人数与询问的个数。

第二行输入 $n$ 个整数，第 $i$ 个数 $a_i$ 表示第 $i$ 个学生的丑值。

接下来 $q$ 行，每行输入三个整数 $s,\,l,\,r$，分别表示丑值之和，mc 所选的第一个学生的下标和最后一个学生的下标。
## 输出格式

对于每一个询问，如果可以选出符合条件的学生，输出 `Yes`，否则输出 `No`。每个输出占一行。
## 样例

### 样例输入 #1
```
6 4
1 1 3 4 2 1
4 3 3
1 2 2
5 4 6
2 1 2
```
### 样例输出 #1
```
Yes
No
Yes
Yes
```
### 样例输入 #2
```
6 4
4 2 2 2 2 1
6 1 1
5 5 6
4 3 5
5 2 2
```
### 样例输出 #2
```
Yes
No
Yes
No
```
## 提示

#### 样例说明：

对于样例 1：

第一个询问，mc 选择的是第三个学生，ac 可以选择第一个学生。

第二个询问，mc 选择的第二个学生丑值为 $1$，而总和也为 $1$，但不存在丑值为 $0$ 的学生，故不能满足条件。

第三个询问，mc 选择的是第四个到第六个，那么 ac 选择第二个到第四个，对应位置的学生丑值之和 $a_2+a_4=a_3+a_5=a_4+a_6=5$，满足条件。

第四个询问，mc 选择第一个和第二个，那么 ac 也选择第一个和第二个，满足条件。

---

#### 数据范围：

**本题采用捆绑测试。**

对于全部数据，有 $1\le n,\,q\le 4\times10^5$，$1\le a_i \le n$，$1\le s\le 2n$，$1\le l\le r\le n$。
* Subtask 0（10 points）：$n,\,q\le 500$。
* Subtask 1（20 points）：$n,\,q\le 8\times10^3$。
* Subtask 2（20 points）：保证所有 $s$ 相同。
* Subtask 3（50 points）：无特殊限制。


---

---
title: "[ICPC 2021 Macao R] LCS Spanning Tree"
layout: "post"
diff: 省选/NOI-
pid: P9664
tag: ['2021', '后缀自动机 SAM', 'O2优化', '生成树', '后缀数组 SA', '后缀树', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] LCS Spanning Tree
## 题目描述

Given a complete undirected graph of $n$ vertices and $n$ strings $s_1, s_2, \cdots, s_n$, the weight of edge connecting vertices $i$ and $j$ is equal to the length of the longest common substring (LCS) between $s_i$ and $s_j$. Compute the maximum total weight of any spanning tree on this graph.

A substring of a string can be obtained by removing some (possibly zero) characters from the beginning and/or the end of that string. For example, ``maca``, ``aca`` and ``cau`` are all substrings of ``macau``, while ``acu`` is not.
## 输入格式

There is only one test case in each test file.

The first line of the input contains one integer $n$ ($1 \leq n \leq 2 \times 10^6$) indicating the number of vertices and strings.

For the following $n$ lines, the $i$-th line contains one string $s_i$ ($1 \le |s_i| \le 2 \times 10^6$) consisting only of lowercase English letters.

It's guaranteed that the sum of lengths of all strings will not exceed $2 \times 10^6$.
## 输出格式

Output one line containing one integer indicating the answer.
## 样例

### 样例输入 #1
```
4
icpc
macau
regional
contest
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3
ababa
babab
aba
```
### 样例输出 #2
```
7
```
## 题目翻译

**【题目描述】**

给定一个有 $n$ 个顶点的完全无向图和 $n$ 个字符串 $s_1, s_2, \cdots, s_n$，连接顶点 $i$ 和 $j$ 的边的权重等于字符串 $s_i$ 和 $s_j$ 的最长公共子串（LCS）的长度。计算此图上任意生成树的最大总权重。

一个字符串的子串可以通过从该字符串的开头和/或结尾删除一些（可能为零）字符来获得。例如，“maca”、“aca” 和“cau”都是“macau”的子串，而“acu”不是。

**【输入格式】**

每个测试文件中包含一个测试用例。

输入的第一行包含一个整数 $n$ ($1 \leq n \leq 2 \times 10^6$)，表示顶点和字符串的数量。

接下来的 $n$ 行，第 $i$ 行包含一个字符串 $s_i$ ($1 \le |s_i| \le 2 \times 10^6$)，由小写英文字母组成。

保证所有字符串的长度之和不超过 $2 \times 10^6$。

**【输出格式】**

输出一行，包含一个整数，表示答案。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

