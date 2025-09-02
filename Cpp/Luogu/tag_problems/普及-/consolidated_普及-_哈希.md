---
title: "[常州市赛 2020] 重点单词"
layout: "post"
diff: 普及-
pid: B4200
tag: ['模拟', '字符串', '2020', '江苏', '哈希 hashing', '科创活动', '小学活动']
---
# [常州市赛 2020] 重点单词
## 题目背景

搬运自 <http://czoj.com.cn/p/448>。数据为民间数据。
## 题目描述

回家后，小 $\text{X}$ 望着自己打瞌睡时写的英语笔记陷入了迷茫。由于太困了，他会时不时地把一个字母多写几次：比如可能把 $\texttt{she}$ 写成 $\texttt{shhe}$，也可能写成 $\texttt{ssshee}$。  
但他依稀记得这堂课只讲了一个重点单词。为了找到这个单词，他想先把每个单词中连续重复的字母压缩起来：把 $\texttt{coool}$ 压缩为 $\texttt{col}$，把 $\texttt{aabbaa}$ 压缩为 $\texttt{aba}$。接下来找到压缩后出现次数最多的单词，这样就能找到重点单词了。  
由于工作量太大，小 $\text{X}$ 希望你帮助他找到重点单词。他向你保证压缩后的单词出现次数最多的一定唯一。
## 输入格式

第一行一个整数 $n$ 表示笔记上共写了 $n$ 个单词。  
接下来 $n$ 行，每行一个字符串，表示一个单词。  
## 输出格式

输出数据只有一行，包含一个字符串，表示压缩后出现次数最多的单词。
## 样例

### 样例输入 #1
```
3
qaaqqq
qwwwwq
qqqqaq
```
### 样例输出 #1
```
qaq
```
## 提示

### 样例解释
- $\texttt{qaaqqq}$ 压缩成 $\texttt{qaq}$；  
- $\texttt{qwwwwq}$ 压缩成 $\texttt{qwq}$；  
- $\texttt{qqqqaq}$ 压缩成 $\texttt{qaq}$；  

$\texttt{qaq}$ 出现了两次，$\texttt{qwq}$ 出现了一次，所以 $\texttt{qaq}$ 出现次数最多。  
### 数据范围
本题共有 $10$ 个测试点。  
对于全部数据：$1\le n\le 10^4$，$1\le $ 单词长度 $\le50$。 
|测试点编号|$n$|单词长度|
|:-:|:-:|:-:|
|$1$|$=1$|$=1$|
|$2\sim3$|$\le 10^4$|$=1$|
|$4\sim6$|$=1$|$\le 50$|
|$7\sim8$|$\le 10$|$\le 50$|
|$9\sim10$|$\le 10^4$|$\le 50$|  



---

---
title: "A-B 数对"
layout: "post"
diff: 普及-
pid: P1102
tag: ['模拟', '数学', '二分', '排序', '哈希 hashing', '双指针 two-pointer']
---
# A-B 数对
## 题目背景

出题是一件痛苦的事情！

相同的题目看多了也会有审美疲劳，于是我舍弃了大家所熟悉的 A+B Problem，改用 A-B 了哈哈！
## 题目描述

给出一串正整数数列以及一个正整数 $C$，要求计算出所有满足 $A - B = C$ 的数对的个数（不同位置的数字一样的数对算不同的数对）。
## 输入格式

输入共两行。

第一行，两个正整数 $N,C$。

第二行，$N$ 个正整数，作为要求处理的那串数。
## 输出格式

一行，表示该串正整数中包含的满足 $A - B = C$ 的数对的个数。
## 样例

### 样例输入 #1
```
4 1
1 1 2 3

```
### 样例输出 #1
```
3
```
## 提示

对于 $75\%$ 的数据，$1 \leq N \leq 2000$。

对于 $100\%$ 的数据，$1 \leq N \leq 2 \times 10^5$，$0 \leq a_i <2^{30}$，$1 \leq C < 2^{30}$。

2017/4/29 新添数据两组


---

---
title: "[蓝桥杯 2025 国 Python A] 倒排索引"
layout: "post"
diff: 普及-
pid: P12871
tag: ['字符串', '2025', '哈希 hashing', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 Python A] 倒排索引
## 题目描述

在信息检索系统中，倒排索引是一种常用的数据结构，用于快速查找包含特定词语的文档集合。为了增强搜索的灵活性，我们引入了 N-Gram 分词算法，参数 $[\min, \max]$，表示分别按照长度 $\min$、$\min+1$、$\cdots$、$\max$ 对单词进行滑动窗口截取。例如对于 $[3, 5]$ 的 N-Gram，会将单词 $\tt{lanqb}$ 分割为 $[\tt{lan, anq, nqb, lanq, anqb, lanqb}]$ 的索引序列，如果文档长度小于 $\min$，那么索引序列只包含文档本身。

给定 $n$ 个文档，对于第 $i$ 个文档 $d_i$，利用上述的 N-Gram 算法为其生成一组索引序列 $L_i$。对于查询词 $q$，也对其应用 N-Gram 为其生成一个索引序列 $P$，如果序列 $P$ 中的某个单词出现在序列 $L_i$ 中，那么就认为查询词和文档 $d_i$ 匹配成功。

请统计查询词 $q$ 能与多少个文档匹配成功。
## 输入格式

输入的第一行包含三个正整数 $n$，$\min$，$\max$，相邻整数之间使用一个空格分隔。

接下来 $n$ 行，每行包含一个字符串，其中第 $i$ 行的字符串表示文档 $d_i$。

接下来一行包含一个字符串，表示查询词 $q$。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
3 3 4
angel
ac
angle
lang
```
### 样例输出 #1
```
2
```
## 提示

**【样例说明】**

文档分词结果如下：

- $\tt{angel}$：$[\tt{ang, nge, gel, ange, ngel}]$
- $\tt{ac}$：$[\tt{ac}]$
- $\tt{angle}$：$[\tt{ang, ngl, gle, angl, ngle}]$

查询词分词结果如下：

- $\tt{lang}$：$[\tt{lan, ang, lang}]$

$\tt{angel}$ 和 $\tt{angle}$ 的分词中都包含 $\tt{ang}$，所以答案为 $2$。

**【评测用例规模与约定】**

设 $|s|$ 表示字符串 $s$ 的长度。

对于 50% 的评测用例，$1 \leq n \leq 100$；

对于所有评测用例，$1 \leq n \leq 10^3$，$1 \leq \min \leq \max \leq 20$，$1 \leq |d_i|, |q| \leq 20$，$d_i$ 和 $q$ 都只包含小写英文字母。


---

---
title: "[GCJ Farewell Round #1] Colliding Encoding"
layout: "post"
diff: 普及-
pid: P12946
tag: ['字符串', '2023', '哈希 hashing', 'Google Code Jam']
---
# [GCJ Farewell Round #1] Colliding Encoding
## 题目描述

Alan just had his first cryptography class in school today. He decided to apply what he learned and come up with his own cipher. He will map each English letter from `A` to `Z` to a decimal digit $0$ through $9$. He will then try to encode each word to a string consisting of decimal digits by replacing each letter in the word with its mapped digit.

In his excitement, Alan failed to notice that there are $26$ letters in the English alphabet and only $10$ decimal digits. As a result, there might be collisions, that is, pairs of different words whose encoding is the same.

Given a list of $N$ words that Alan wants to encode and the mapping that he uses, can you find out if there would be any collisions between words on the list?
## 输入格式

The first line of the input gives the number of test cases, T. T test cases follow.

The first line of each test case contains 26 decimal digits (integers between 0 and 9, inclusive) $D_A$, $D_B$, …, $D_Z$, representing the mapping that Alan uses. A letter $\alpha$ is mapped to digit $D_\alpha$.

The second line of each test case contains N, the number of words Alan will encode.

The $i$-th of the last N lines contains a string $S_i$, representing the $i$-th word Alan will encode.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is either `YES`, if there is at least one pair of different words from the list whose encoding coincides, and NO otherwise.
## 样例

### 样例输入 #1
```
2
0 1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
4
ABC
BC
BCD
CDE
0 1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
3
CDE
DEF
EFG
```
### 样例输出 #1
```
Case #1: NO
Case #2: YES
```
## 提示

**Sample Explanation**

In Sample Case #1, the mapping for A is 0, for B is 1, for C is 2, for D is 3, and for E is 3. With this mapping, ABC is encoded as 012, BC is encoded as 12, BCD as 123, and CDE as 233. Since all of these encodings are distinct, there are no collisions.

In Sample Case #2, the mapping for C is 2, for D is 3, for E is 3, for F is 3, and for G is 3. With this mapping, CDE is encoded as 233, DEF as 333, and EFG as 333. Since the encoding for DEF and EFG is the same, there is a collision.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $0 \leq \mathbf{D}_{\alpha} \leq 9$, for all $\alpha$.
- $1 \leq$ the length of $\mathbf{S}_{i} \leq 10$, for all $i$.
- Each character of $\mathbf{S}_{i}$ is an uppercase English letter A through Z, for all $i$.
- $\mathbf{S}_{i} \neq \mathbf{S}_{j}$, for all $i \neq j$.

**Test Set 1 (4Pts, Visible Verdict)**

- $1 \leq \mathbf{N} \leq 100$.

**Test Set 2 (10Pts, Visible Verdict)**

- $1 \leq \mathbf{N} \leq 6 \times 10^{4}$.


---

---
title: "[USACO09OCT] Barn Echoes G"
layout: "post"
diff: 普及-
pid: P2957
tag: ['字符串', '2009', 'USACO', '哈希 hashing', '前缀和']
---
# [USACO09OCT] Barn Echoes G
## 题目描述

The cows enjoy mooing at the barn because their moos echo back, although sometimes not completely. Bessie, ever the excellent

secretary, has been recording the exact wording of the moo as it goes out and returns. She is curious as to just how much overlap there is.

Given two lines of input (letters from the set a..z, total length in the range 1..80), each of which has the wording of a moo on it, determine the greatest number of characters of overlap between one string and the other. A string is an overlap between two other strings if it is a prefix of one string and a suffix of the other string.

By way of example, consider two moos:

```
moyooyoxyzooo
yzoooqyasdfljkamo
```
The last part of the first string overlaps 'yzooo' with the first part of the second string. The last part of the second string

overlaps 'mo' with the first part of the first string. The largest overlap is 'yzooo' whose length is 5.

POINTS: 50

奶牛们非常享受在牛栏中哞叫，因为她们可以听到她们哞声的回音。虽然有时候并不能完全听到完整的回音。Bessie 曾经是一个出色的秘书，所以她精确地纪录了所有的哞叫声及其回声。她很好奇到底两个声音的重复部份有多长。

输入两个字符串（长度为 $1$ 到 $80$ 个字母），表示两个哞叫声。你要确定最长的重复部份的长度。两个字符串的重复部份指的是同时是一个字符串的前缀和另一个字符串的后缀的字符串。

我们通过一个例子来理解题目。考虑下面的两个哞声：

```
moyooyoxyzooo
yzoooqyasdfljkamo
```

第一个串的最后的部份 `yzooo` 跟第二个串的第一部份重复。第二个串的最后的部份 `mo` 跟第一个串的第一部份重复。所以 `yzooo` 跟 `mo` 都是这 $2$ 个串的重复部份。其中，`yzooo` 比较长，所以最长的重复部份的长度就是 $5$。

## 输入格式

\* Lines 1..2: Each line has the text of a moo or its echo

## 输出格式

\* Line 1: A single line with a single integer that is the length of the longest overlap between the front of one string and end of the other.

## 样例

### 样例输入 #1
```
abcxxxxabcxabcd 
abcdxabcxxxxabcx 

```
### 样例输出 #1
```
11 

```
## 提示

'abcxxxxabcx' is a prefix of the first string and a suffix of the second string.



---

---
title: "【模板】字符串哈希"
layout: "post"
diff: 普及-
pid: P3370
tag: ['哈希 hashing']
---
# 【模板】字符串哈希
## 题目描述

如题，给定 $N$ 个字符串（第 $i$ 个字符串长度为 $M_i$，字符串内包含数字、大小写字母，大小写敏感），请求出 $N$ 个字符串中共有多少个不同的字符串。


**友情提醒：如果真的想好好练习哈希的话，请自觉。**

## 输入格式

第一行包含一个整数 $N$，为字符串的个数。

接下来 $N$ 行每行包含一个字符串，为所提供的字符串。

## 输出格式

输出包含一行，包含一个整数，为不同的字符串个数。

## 样例

### 样例输入 #1
```
5
abc
aaaa
abc
abcc
12345
```
### 样例输出 #1
```
4
```
## 提示

对于 $30\%$ 的数据：$N\leq 10$，$M_i≈6$，$Mmax\leq 15$。

对于 $70\%$ 的数据：$N\leq 1000$，$M_i≈100$，$Mmax\leq 150$。

对于 $100\%$ 的数据：$N\leq 10000$，$M_i≈1000$，$Mmax\leq 1500$。


样例说明：

样例中第一个字符串(abc)和第三个字符串(abc)是一样的，所以所提供字符串的集合为{aaaa,abc,abcc,12345}，故共计4个不同的字符串。


Tip：
感兴趣的话，你们可以先看一看以下三题：

BZOJ3097：http://www.lydsy.com/JudgeOnline/problem.php?id=3097

BZOJ3098：http://www.lydsy.com/JudgeOnline/problem.php?id=3098

BZOJ3099：http://www.lydsy.com/JudgeOnline/problem.php?id=3099

如果你仔细研究过了（或者至少仔细看过AC人数的话），我想你一定会明白字符串哈希的正确姿势的^\_^



---

---
title: "[TJOI2010] 阅读理解"
layout: "post"
diff: 普及-
pid: P3879
tag: ['字符串', '2010', '各省省选', '哈希 hashing', '字典树 Trie', '天津']
---
# [TJOI2010] 阅读理解
## 题目描述

英语老师留了 $N$ 篇阅读理解作业，但是每篇英文短文都有很多生词需要查字典，为了节约时间，现在要做个统计，算一算某些生词都在哪几篇短文中出现过。
## 输入格式

第一行为整数 $N$ ，表示短文篇数，其中每篇短文只含空格和小写字母。

按下来的 $N$ 行，每行描述一篇短文。每行的开头是一个整数 $L$ ，表示这篇短文由 $L$ 个单词组成。接下来是 $L$ 个单词，单词之间用一个空格分隔。

然后为一个整数 $M$ ，表示要做几次询问。后面有 $M$ 行，每行表示一个要统计的生词。

## 输出格式

对于每个生词输出一行，统计其在哪几篇短文中出现过，并按从小到大输出短文的序号，序号不应有重复，序号之间用一个空格隔开（注意第一个序号的前面和最后一个序号的后面不应有空格）。如果该单词一直没出现过，则输出一个空行。

## 样例

### 样例输入 #1
```
3
9 you are a good boy ha ha o yeah
13 o my god you like bleach naruto one piece and so do i
11 but i do not think you will get all the points
5
you
i
o
all
naruto

```
### 样例输出 #1
```
1 2 3
2 3
1 2
3
2

```
## 提示

对于 $30\%$ 的数据， $1\le M\le 10^3$ 。

对于 $100\%$ 的数据，$1\le M\le 10^4$，$1\le N\le 10^3$ 。

每篇短文长度（含相邻单词之间的空格）$\le 5\times 10^3$ 字符，每个单词长度 $\le 20$ 字符。

每个测试点时限 $2$ 秒。

感谢@钟梓俊添加的一组数据。


---

---
title: "[JLOI2011] 不重复数字"
layout: "post"
diff: 普及-
pid: P4305
tag: ['2011', '各省省选', '吉林', 'O2优化', '排序', '哈希 hashing']
---
# [JLOI2011] 不重复数字
## 题目描述

给定 $n$ 个数，要求把其中重复的去掉，只保留第一次出现的数。
## 输入格式

**本题有多组数据。**

第一行一个整数 $T$，表示数据组数。

对于每组数据：

第一行一个整数 $n$。

第二行 $n$ 个数，表示给定的数。
## 输出格式

对于每组数据，输出一行，为去重后剩下的数，两个数之间用一个空格隔开。
## 样例

### 样例输入 #1
```
2
11
1 2 18 3 3 19 2 3 6 5 4
6
1 2 3 4 5 6

```
### 样例输出 #1
```
1 2 18 3 19 6 5 4
1 2 3 4 5 6

```
## 提示

对于 $30\%$ 的数据，$n \le 100$，给出的数 $\in [0, 100]$。

对于 $60\%$ 的数据，$n \le 10^4$，给出的数 $\in [0, 10^4]$。

对于 $100\%$ 的数据，$1 \le T\le 50$，$1 \le n \le 5 \times 10^4$，给出的数在 $32$ 位有符号整数范围内。


---

---
title: "[NWRRC 2015] Hash Code Hacker"
layout: "post"
diff: 普及-
pid: P7055
tag: ['字符串', '2015', 'Special Judge', '哈希 hashing', '构造', 'ICPC']
---
# [NWRRC 2015] Hash Code Hacker
## 题目描述



According to Java standard library documentation, the hash code of String is computed as

$s[0] \times 31 ^ {n -1} + s[1] \times 31 ^ {n -2} + \cdots + s[n -1]$

Here $s[i]$ is the i-th character of the string, $n$ is the length of the string, and $^$ indicates exponentiation. Computation uses signed $32-bit$ integers in two's complement form.

Heather is going to hack the servers of Not Entirely Evil Recording Company $(NEERC).$ To perform an attack she needs $k$ distinct query strings that have equal hash codes. Unfortunately, NEERC servers accept query string containing lower- and uppercase English letters only.

Heather hired you to write a program that generates such query strings for her.


## 输入格式



The single line of the input file contains integer $k$ -- the number of required query strings to generate $(2 \le k \le 1000)$ .


## 输出格式



Output $k$ lines. Each line should contain a single query string. Each query string should be non-empty and its length should not exceed $1000$ characters. Query string should contain only lower- and uppercase English letters. All query strings should be distinct and should have equal hash codes.


## 样例

### 样例输入 #1
```
4

```
### 样例输出 #1
```
edHs
mENAGeS
fEHs
edIT

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

根据$Java$的标准库文件，字符串的哈希代码是这么计算的：

$$s[0]×31 ^{(n−1)}+s[1]×31^{(n−2)}+⋯+s[n−1]$$

在这里，s[i]指的是字符串中的第i位，n是字符串的长度。

这个计算过程用的是有符号的$32$位整数的二进制补码形式。

有一个人叫作 阖锕仄 $(Heather)$。他想要$hack$掉“不全是恶魔录音公司”$(NEERC)$。为了进行

一次攻击，阖锕仄需要$k$个有相同哈希代码的不同的询问字符串。不幸的是，$NEERC$的服务器

只接受只包含大小写字母的字符串。

阖锕仄请你帮忙写一个程序，以生成他需要的询问字符串。

-------

输入一个正整数$k$,代表需要的字符串的数量。

-------

输出有$k$行，每行的询问字符串都不应该为空，并且每行的字符串的长度应该小于等于1000个字符。

询问字符串的具体要求请看上文。

-------

时间限制：$2s$    

空间限制：$256MB$

翻译提供：@Trexmao


---

---
title: "[COCI 2009/2010 #2] KUTEVI"
layout: "post"
diff: 普及-
pid: P7774
tag: ['模拟', '动态规划 DP', '2009', '枚举', '哈希 hashing', 'COCI（克罗地亚）']
---
# [COCI 2009/2010 #2] KUTEVI
## 题目背景

本题为[$\texttt{COCI 2009-2010}\ 2^\texttt{nd}\ \texttt{round}\ \text{T3 KUTEVI}$](https://hsin.hr/coci/archive/2009_2010/contest2_tasks.pdf)。

分值按原题设置，满分 $70$。
## 题目描述

给定 $N$ 个角（第 $i$ 个角记作 $a_i$），作为初始角，另给定 $M$ 个角（第 $i$ 个角记作 $b_i$），作为目标角。

请求出对于每个 $b_i$，它是否能被若干个 $a_i$ 之间的加、减运算得到。

注意同一个 $a_i$ 可以用多次，也可以不用。
## 输入格式

第一行两个正整数 $N,M$。

第二行 $N$ 个正整数，第 $i$ 个数为 $a_i$。

第三行 $M$ 个正整数，第 $i$ 个数为 $b_i$。
## 输出格式

共 $M$ 行，在第 $i$ 行，如果 $b_i$ 能被若干个 $a_i$ 之间的加、减运算得到，输出`YES`，否则输出`NO`。
## 样例

### 样例输入 #1
```
2 1
30 70
40
```
### 样例输出 #1
```
YES
```
### 样例输入 #2
```
1 1
100
60
```
### 样例输出 #2
```
YES
```
### 样例输入 #3
```
3 2
10 20 30
5 70
```
### 样例输出 #3
```
NO
YES
```
## 提示

### 样例解释

样例 $1$ 解释：

$70^\circ-30^\circ=40^\circ$。

样例 $2$ 解释：

$15\times100^\circ=1500^\circ=60^\circ$。

### 数据范围与约定

$1\leq N,M\leq10$，$0<a_i,b_i< 360$。


---

