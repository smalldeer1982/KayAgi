---
title: "[USACO03FALL] Milking Grid（数据加强版）"
layout: "post"
diff: 普及+/提高
pid: P10475
tag: ['USACO', '哈希 hashing', 'KMP 算法']
---
# [USACO03FALL] Milking Grid（数据加强版）
## 题目描述

Every morning when they are milked, the Farmer John's cows form a rectangular grid that is $R (1 \leq R \leq 10,000)$ rows by $C (1 \leq C \leq 75)$ columns. As we all know, Farmer John is quite the expert on cow behavior, and is currently writing a book about feeding behavior in cows. He notices that if each cow is labeled with an uppercase letter indicating its breed, the two-dimensional pattern formed by his cows during milking sometimes seems to be made from smaller repeating rectangular patterns.

Help FJ find the rectangular unit of smallest area that can be repetitively tiled to make up the entire milking grid. Note that the dimensions of the small rectangular unit do not necessarily need to divide evenly the dimensions of the entire milking grid, as indicated in the sample input below.
## 输入格式

- Line $1$: Two space-separated integers: $R$ and $C$

- Lines $2\dots R+1$: The grid that the cows form, with an uppercase letter denoting each cow's breed. Each of the $R$ input lines has $C$ characters with no space or other intervening character.
## 输出格式

- Line 1: The area of the smallest unit from which the grid is formed
## 样例

### 样例输入 #1
```
2 5 
ABABA 
ABABA

```
### 样例输出 #1
```
2
```
## 提示

The entire milking grid can be constructed from repetitions of the pattern `AB`.
## 题目翻译

**【题目描述】**

每天早上挤奶时，农夫约翰的奶牛们排成一个 $R (1 \leq R \leq 10,000)$ 行乘 $C (1 \leq C \leq 75)$ 列的矩形网格。众所周知，约翰农夫是一个相当擅长牛行为的专家，目前正在撰写一本关于奶牛饲养行为的书。他注意到，如果每头奶牛都标有一个表示其品种的大写字母，那么奶牛在挤奶时形成的二维图案有时似乎是由更小的重复矩形图案组成的。

帮助约翰农夫找到可以重复铺设以组成整个挤奶网格的最小面积的矩形单元。请注意，小矩形单元的尺寸不一定需要完全整除整个挤奶网格的尺寸，如下面的示例输入所示。

**【输入格式】**

- 第一行：两个用空格分隔的整数：$R$ 和 $C$
- 第 $2\dots R+1$ 行：奶牛形成的网格，每个奶牛的品种用大写字母表示。每个 $R$ 输入行有 $C$ 个字符，没有空格或其他间隔字符。

**【输出格式】**

第一行：形成网格的最小单位的面积

**【提示说明】**

整个挤奶网格可以由图案 AB 的重复构建。

翻译来自于：ChatGPT。


---

---
title: "[蓝桥杯 2025 国 Python A] 心意"
layout: "post"
diff: 普及+/提高
pid: P12877
tag: ['2025', 'KMP 算法', '差分', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 Python A] 心意
## 题目描述

小蓝有一个序列 $a$，同时他的朋友小乔有一个序列 $b$。

我们认为两个序列是和谐的，当且仅当存在某个数 $x$，使得对于所有的 $i$ 有 $a_i + x = b_i$。

现在小蓝可以让序列 $a$ 旋转，即通过一次参数为 $k$ 的旋转可以将序列 $a_1, a_2, \cdots, a_n$ 变为 $a_{1+k}, a_{2+k}, \cdots, a_n, a_1, a_2, \cdots, a_k$。

小蓝希望知道，是否存在这样的旋转操作，能够让序列 $a$ 和 $b$ 是和谐的。

输出共一行，一个自然数 $k$ 表示参数为 $k$ 的旋转操作能够让 $a, b$ 是和谐的，如果存在多个这样的 $k$，请输出最小的 $k$，如果不存在这样的 $k$，请输出 $-1$。
## 输入格式

输入的第一行包含一个正整数 $n$。

第二行包含 $n$ 个正整数 $a_1, a_2, \cdots, a_n$，相邻整数之间使用一个空格分隔。

第三行包含 $n$ 个正整数 $b_1, b_2, \cdots, b_n$，相邻整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个整数表示答案，如果不存在，请输出整数 $-1$。
## 样例

### 样例输入 #1
```
4
2 3 4 5
2 3 4 1
```
### 样例输出 #1
```
1
```
## 提示

**【样例说明】**

小蓝可以让序列 $a$ 旋转得到 $3 \ 4 \ 5 \ 2$，根据和谐序列的定义，令 $x = -1$，那么此时 $a, b$ 就是和谐的。

**【评测用例规模与约定】**

对于 $50\%$ 的评测用例，$n \leq 3000$；

对于 $80\%$ 的评测用例，对于任意 $i \neq j$ 有 $a_i \neq a_j$；

对于所有评测用例，$1 \leq n \leq 5 \times 10^5$，$1 \leq a_i, b_i \leq 10^9$。


---

---
title: "[GCJ 2015 #1C] Typewriter Monkey"
layout: "post"
diff: 普及+/提高
pid: P13222
tag: ['动态规划 DP', '2015', 'Special Judge', '期望', 'KMP 算法', 'Google Code Jam']
---
# [GCJ 2015 #1C] Typewriter Monkey
## 题目描述

Your publishing house has decided to use monkeys randomly typing at keyboards to write great works of literature. You are the supervisor for one monkey with a keyboard containing $K$ keys, each of which is labeled with an uppercase English letter. (There may be multiple keys displaying the same letter.) The monkey will start with an empty string and repeat the following $S$ times: choose a key from its keyboard uniformly at random and press it, adding a copy of that key's letter to the right end of the string. The final resulting string will have length $S$.

You have a *target word* of length $L$ that you are hoping the monkey will type. (The target word will not necessarily be a real English word.) This target word may even appear multiple times in what the monkey types. (Overlapping instances count too -- for example, if "ABA" is the target word and the monkey types "ABABA", that contains two instances of the target.)

You plan to pay the monkey one banana for each instance of the target word that it types. When you go to inspect the monkey's work, you will bring along the minimum number of bananas that you need to ensure that you will always have enough bananas to pay the monkey, no matter what it has typed. Then, you will pay the monkey one banana for each instance of the target word that it actually typed. You will keep the remaining bananas that you brought with you.

What is the expected number of bananas that you will get to keep?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each consists of three lines. The first contains three space-separated positive integers: $K$, $L$, and $S$. The second contains a string of $K$ uppercase English letters representing the monkey's keyboard. The third contains a string of $L$ uppercase English letters representing the target word.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $y$ is the expected number of bananas you will get to keep after paying the monkey.

$y$ will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer.
## 样例

### 样例输入 #1
```
5
7 6 6
BANANAS
MONKEY
2 3 4
AA
AAA
2 1 2
AB
B
6 2 2
GOOGLE
GO
26 11 100
ABCDEFGHIJKLMNOPQRSTUVWXYZ
ROSENCRANTZ
```
### 样例输出 #1
```
Case #1: 0.0
Case #2: 0.0
Case #3: 1.0
Case #4: 0.8888889
Case #5: 9.0
```
## 提示

**Sample Explanation**

Note that Case #5 is not within the limits for the Small dataset.

In Case #1, the monkey has no chance of typing the target word "MONKEY" even once (because his keyboard lacks most of the letters in "MONKEY"), so you do not bring any bananas along when you visit, and of course you do not pay any. Poor monkey!

In Case #2, the monkey is guaranteed to type "AAAA", which has two overlapping instances of the target word "AAA". You will bring two bananas and then pay both.

In Case #3, the monkey will produce the following outputs with equal probability (1/4 each): "AA", "AB", "BA", "BB". These have 0, 1, 1, and 2 instances of the target word, respectively. You must bring 2 bananas to be ready for the "BB" case, but you will on average pay $(0 + 1 + 1 + 2) / 4 = 1$.

In Case #4, the monkey has a $1/3$ chance of typing a "G" first and a $1/3$ chance of typing an "O" second, for a $1/9$ chance of typing "GO". You will bring one banana and give it up $1/9$ of the time.

In Case #5, the monkey could in theory type "ROSENCRANTZ" up to nine times, but the chances of this happening even once are so small that they are negligible compared to the acceptable margin of error for answers.

**Limits**

$1 \leq T \leq 100$.

**Small dataset(11 Pts)**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq K \leq 7$.
- $1 \leq L \leq S \leq 7$.

**Large dataset**

- Time limit: ~~480~~ 10 seconds.
- $1 \leq K \leq 100$.
- $1 \leq L \leq S \leq 100$.


---

---
title: "「CZOI-R6」Border"
layout: "post"
diff: 普及+/提高
pid: P13790
tag: ['倍增', '二分', 'O2优化', '哈希 hashing', 'KMP 算法']
---
# 「CZOI-R6」Border
## 题目描述

给定一个仅包含小写字母的字符串 $s$（下标从 $1$ 开始），你可以将 **不超过 $\boldsymbol{1}$ 个位置** 修改为任意小写字母，使得最大化其最长 border 长度。你只需输出这个最大化的长度即可。

字符串 $b$ 是字符串 $a$ 的 border，当且仅当 $\lvert b\rvert < \lvert a\rvert$，且 $b$ 既是 $a$ 的前缀又是 $a$ 的后缀。
## 输入格式

第一行输入 $1$ 个字符串，表示 $s$。
## 输出格式

第一行输出 $1$ 个整数，表示答案。
## 样例

### 样例输入 #1
```
abaa
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
qwqqaq
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
iakioi
```
### 样例输出 #3
```
1
```
### 样例输入 #4
```
ababaaab

```
### 样例输出 #4
```
6

```
### 样例输入 #5
```
r
```
### 样例输出 #5
```
0

```
### 样例输入 #6
```
onion

```
### 样例输出 #6
```
2

```
## 提示

**【数据范围】**

**本题采用捆绑测试。**

- Subtask #1（$10\ \text{pts}$）：$|s|\le 20$。
- Subtask #2（$20\ \text{pts}$）：$s_i\in\{\texttt a,\texttt b\}$。
- Subtask #3（$30\ \text{pts}$）：$|s|\le 1000$。
- Subtask #4（$40\ \text{pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le |s|\le 10^6$，$s$ 仅包含小写字母。


---

---
title: "[USACO2.3] 最长前缀 Longest Prefix"
layout: "post"
diff: 普及+/提高
pid: P1470
tag: ['字符串', '动态规划 DP', 'USACO', 'KMP 算法']
---
# [USACO2.3] 最长前缀 Longest Prefix
## 题目描述

在生物学中，一些生物的结构是用包含其要素的大写字母序列来表示的。生物学家对于把长的序列分解成较短的序列（即元素）很感兴趣。

如果一个集合 $P$ 中的元素可以串起来（元素可以重复使用）组成一个序列 $s$ ，那么我们认为序列 $s$ 可以分解为 $P$ 中的元素。元素不一定要全部出现（如下例中 `BBC` 就没有出现）。举个例子，序列 `ABABACABAAB` 可以分解为下面集合中的元素：`{A,AB,BA,CA,BBC}`

序列 $s$ 的前面 $k$ 个字符称作 $s$ 中长度为 $k$ 的前缀。设计一个程序，输入一个元素集合以及一个大写字母序列  ，设 $s'$ 是序列 $s$ 的最长前缀，使其可以分解为给出的集合 $P$ 中的元素，求 $s'$ 的长度 $k$。

## 输入格式

输入数据的开头包括若干个元素组成的集合 $P$，用连续的以空格分开的字符串表示。字母全部是大写，数据可能不止一行。元素集合结束的标志是一个只包含一个 `.` 的行，集合中的元素没有重复。  

接着是大写字母序列 $s$ ，长度为，用一行或者多行的字符串来表示，每行不超过 $76$ 个字符。换行符并不是序列 $s$ 的一部分。

## 输出格式

只有一行，输出一个整数，表示 S 符合条件的前缀的最大长度。

## 样例

### 样例输入 #1
```
A AB BA CA BBC
.
ABABACABAABC

```
### 样例输出 #1
```
11

```
## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le \text{card}(P) \le 200$，$1\le |S| \le 2\times 10^5$，$P$ 中的元素长度均不超过 $10$。

翻译来自NOCOW

USACO 2.3



---

---
title: "【模板】KMP"
layout: "post"
diff: 普及+/提高
pid: P3375
tag: ['字符串', 'O2优化', 'KMP 算法']
---
# 【模板】KMP
## 题目描述

给出两个字符串 $s_1$ 和 $s_2$，若 $s_1$ 的区间 $[l, r]$ 子串与 $s_2$ 完全相同，则称 $s_2$ 在 $s_1$ 中出现了，其出现位置为 $l$。  
现在请你求出 $s_2$ 在 $s_1$ 中所有出现的位置。

定义一个字符串 $s$ 的 border 为 $s$ 的一个**非 $s$ 本身**的子串 $t$，满足 $t$ 既是 $s$ 的前缀，又是 $s$ 的后缀。  
对于 $s_2$，你还需要求出对于其每个前缀 $s'$ 的最长 border $t'$ 的长度。
## 输入格式

第一行为一个字符串，即为 $s_1$。  
第二行为一个字符串，即为 $s_2$。

## 输出格式

首先输出若干行，每行一个整数，**按从小到大的顺序**输出 $s_2$ 在 $s_1$ 中出现的位置。  
最后一行输出 $|s_2|$ 个整数，第 $i$ 个整数表示 $s_2$ 的长度为 $i$ 的前缀的最长 border 长度。
## 样例

### 样例输入 #1
```
ABABABC
ABA

```
### 样例输出 #1
```
1
3
0 0 1 

```
## 提示

### 样例 1 解释

 ![](https://cdn.luogu.com.cn/upload/pic/2257.png)。
 
对于 $s_2$ 长度为 $3$ 的前缀 `ABA`，字符串 `A` 既是其后缀也是其前缀，且是最长的，因此最长 border 长度为 $1$。


### 数据规模与约定

**本题采用多测试点捆绑测试，共有 3 个子任务**。

- Subtask 1（30 points）：$|s_1| \leq 15$，$|s_2| \leq 5$。
- Subtask 2（40 points）：$|s_1| \leq 10^4$，$|s_2| \leq 10^2$。
- Subtask 3（30 points）：无特殊约定。

对于全部的测试点，保证 $1 \leq |s_1|,|s_2| \leq 10^6$，$s_1, s_2$ 中均只含大写英文字母。


---

---
title: "[BalticOI 2009] Radio Transmission 无线传输"
layout: "post"
diff: 普及+/提高
pid: P4391
tag: ['字符串', '2009', '前缀和', 'KMP 算法', 'BalticOI（波罗的海）']
---
# [BalticOI 2009] Radio Transmission 无线传输
## 题目描述

给你一个字符串 $s_1$，它是由某个字符串 $s_2$ 不断自我连接形成的（保证至少重复 $2$ 次）。但是字符串 $s_2$ 是不确定的，现在只想知道它的最短长度是多少。
## 输入格式

第一行一个整数 $L$，表示给出字符串的长度。 

第二行给出字符串 $s_1$ 的一个子串，全由小写字母组成。  
## 输出格式

仅一行，表示 $s_2$ 的最短长度。
## 样例

### 样例输入 #1
```
8
cabcabca
```
### 样例输出 #1
```
3
```
## 提示

#### 样例输入输出 1 解释
对于样例，我们可以利用 $\texttt{abc}$ 不断自我连接得到 $\texttt{abcabcabcabc}$，读入的 $\texttt{cabcabca}$，是它的子串。

#### 规模与约定
对于全部的测试点，保证 $1\le L \le 10^6$。


---

---
title: "[CERC2019] ABB"
layout: "post"
diff: 普及+/提高
pid: P9606
tag: ['字符串', '2019', '哈希 hashing', 'KMP 算法', 'Manacher 算法', 'ICPC']
---
# [CERC2019] ABB
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[ABB](https://contest.felk.cvut.cz/19cerc/solved/abb.pdf)」**
## 题目描述

Fernando 受雇于滑铁卢大学，负责完成该大学不久前开始的一个开发项目。在校园外，该大学希望为重要的外国游客和合作者建造具有代表性的平房街。

目前，这条街只建了一部分，它从湖岸开始，一直延伸到森林尽头。Fernando 的任务是通过在森林尽头建造更多的平房来完成这条街。所有现有的平房都坐落在街道的一侧，新的平房应该建在同一侧。这些平房有各种各样的类型，漆成各种各样的颜色。

在 Fernando 看来，整条街的布局有点混乱。他担心增加新平房后，它会看起来更加混乱。所以他想通过为新平房选择合适的颜色来增加一些排列顺序。当项目完成时，平房的整个颜色序列将是对称的，也就是说，从街道的两端观察时，颜色序列是相同的。

在其他问题中，Fernando 想知道，在满足平房颜色限制的情况下，他最少需要用来建造和适当染色才能完成项目的新平房数量。

### 简要题意

求使给定小写字母字符串成为回文串需在字符串末尾加入字母的最少数量。
## 输入格式

第一行包含一个整数 $N\ (1\le N\le 4\times 10^5)$，代表街道上现有平房的数量。

第二行包含一个由 $N$ 个小写字母（从 `a` 到 `z`）组成的字符串，代表从湖岸开始的街道现有的平房颜色顺序，其中不同的字母表示不同的颜色。
## 输出格式

输出一个整数，代表满足 Fernando 要求的新平房的最少数量。
## 样例

### 样例输入 #1
```
3
abb

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
12
recakjenecep

```
### 样例输出 #2
```
11

```
### 样例输入 #3
```
15
murderforajarof

```
### 样例输出 #3
```
6

```


---

