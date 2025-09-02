---
title: "【MX-X1-T4】「KDOI-05」简单的字符串问题"
layout: "post"
diff: 省选/NOI-
pid: P10716
tag: ['字符串', '倍增', '树上启发式合并', 'O2优化', 'KMP 算法', '梦熊比赛']
---
# 【MX-X1-T4】「KDOI-05」简单的字符串问题
## 题目背景

原题链接：<https://oier.team/problems/X1D>。
## 题目描述

你有一个字符串 $S$。$q$ 个询问，每次给出 $(i,k)$，求有多少个非空字符串 $A$，使得存在可空字符串 $B_1,B_2,\dots,B_{k-1}$ 满足：

$$S[1,i]=AB_1AB_2A\dots AB_{k-1}A$$

其中 $S[1,i]$ 表示 $S$ 的长度为 $i$ 的前缀。
## 输入格式

第一行一个正整数 $n$ 表示 $S$ 的长度。

接下来一个长度为 $n$ 且仅包含小写字母的字符串表示 $S$。

接下来一行一个正整数表示 $q$。

接下来 $q$ 行，每行两个正整数表示一个询问的 $i,k$。
## 输出格式

输出 $q$ 行，每行一个非负整数表示答案。
## 样例

### 样例输入 #1
```
10
aabaacaaaa
5
5 3
5 2
6 1
10 4
10 5
```
### 样例输出 #1
```
1
2
1
2
1
```
### 样例输入 #2
```
10
bababababa
10
6 1
6 2
6 3
6 4
6 5
10 2
10 3
9 4
5 5
4 2
```
### 样例输出 #2
```
1
1
1
0
0
2
1
1
0
1

```
## 提示

**【样例解释 \#1】**

对于第一次询问 $(5,3)$，可以取 $A=\texttt{a}$，$B_1=\varepsilon$，$B_2=\texttt{ba}$，其中 $\varepsilon$ 表示空串。可以证明有且仅有一个合法的 $A$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | 分值 | $n,q\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|
| $1$ | $5$ | $500$ | 无 |
| $2$ | $10$ | $5000$ | 无 |
| $3$ | $10$ | $2\times10^5$ | $S$ 中字符从 $\tt a,b$ 中随机生成 |
| $4$ | $20$ | $2\times10^5$ | 每个询问的 $k$ 相同 |
| $5$ | $20$ | $5\times10^4$ | 无 |
| $6$ | $35$ | $2\times10^5$ | 无 |

对于 $100\%$ 的数据：$1\leq k\leq i\leq n\leq 2\times 10^5$，$1\leq q\leq 2\times 10^5$，$s$ 仅包含小写字母。


---

---
title: "【MX-S6-T3】「KDOI-11」简单的字符串问题 2"
layout: "post"
diff: 省选/NOI-
pid: P11291
tag: ['字符串', '贪心', '倍增', 'Special Judge', 'O2优化', '哈希 hashing', '前缀和', 'KMP 算法', '梦熊比赛']
---
# 【MX-S6-T3】「KDOI-11」简单的字符串问题 2
## 题目背景

原题链接：<https://oier.team/problems/S6C>。
## 题目描述

给定 $n$ 个字符串 $S_1, \ldots, S_n$ 以及一个字符串 $T$。

对于一个字符串 $R$，定义 $|R|$ 表示 $R$ 的长度、$R_{[l,r]}$ 表示 $R$ 的第 $l\sim r$ 个字符组成的字符串。字符串 $R'$ 是字符串 $R$ 的前缀当且仅当存在 $1\leq p\leq |R|$ 且 $p$ 为整数使得 $R'=R_{[1,p]}$。

定义一个字符串 $R$ 是**好的**当且仅当它是某个 $S_i$ 的前缀**或** $R$ **为空**。

对于若干字符串 $R_1,R_2,\dots,R_k$，定义 $R_1+R_2+\dots+R_k$ 为 $R_1,R_2,\dots,R_k$ 顺次拼接得到的字符串。

定义一个三元组 $(l,r,k)$（$l,r,k$ 均为整数）是好的当且仅当 $1\leq l\leq r\leq|T|$，$1\leq k\leq K$ 且存在 $k$ 个**好的**字符串 $R_1,R_2,\dots,R_k$ 使得 $R_1+R_2+\dots+R_k=T_{[l,r]}$。

请你求出好的三元组的数量，并对于每个 $i$ 求出有多少好的三元组 $(l,r,k)$ 满足 $l\leq i\leq r$。如果你只能求出两者中其一，也可以获得部分分数，见【**输出格式**】。
## 输入格式

第一行，三个非负整数 $id,n,K$，其中 $id$ 表示测试点编号（所有样例满足 $id=0$），$n$ 表示字符串数量，$K$ 表示对好的三元组的限制。

接下来 $n$ 行，每行一个字符串 $S_i$。

接下来一行，一个字符串 $T$。
## 输出格式

第一行，一个非负整数，表示好的三元组的数量。

第二行，$\lvert T\rvert$ 个非负整数，第 $i$ 个表示满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量。

本题使用**自定义校验器**进行评分，对于每个测试点：

* 如果你的程序正确地求出了好的三元组的数量并正确地对于每个 $1\leq i\leq |T|$ 求出了满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量，你可以获得该测试点 $100\%$ 的分数。
* 如果你的程序未能正确地求出了好的三元组的数量但正确地对于每个 $1\leq i\leq |T|$ 求出了满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量，你可以获得该测试点 $80\%$ 的分数。
* 如果你的程序正确地求出了好的三元组的数量但未能正确地对于每个 $1\leq i\leq |T|$ 求出了满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量，你可以获得该测试点 $60\%$ 的分数。
* 否则，你不能获得该测试点的任何分数。

注意，即使你希望获得某测试点 $80\%$ 或 $60\%$ 的分数，你也需要在第一行输出一个数并在第二行输出 $\lvert T\rvert$ 个数。
## 样例

### 样例输入 #1
```
0 1 2
ab
abaab
```
### 样例输出 #1
```
13
5 3 5 6 3
```
### 样例输入 #2
```
0 3 2
abc
ac
b
bacabcab
```
### 样例输出 #2
```
27
4 9 6 11 10 5 6 5
```
### 样例输入 #3
```
0 10 10
wooogpgpoo
owpwgwwp
ooogpgpooo
gppwppgwoo
wooogpgpoo
wowooogpgp
gwwp
ggggogwgpp
wowooogpgp
pgpoooowpw
pgwgwggggggogwgppwppgwooggoogwowooogpgpoooowpwgwwp
```
### 样例输出 #3
```
7698
183 390 577 792 990 1213 1422 1651 1780 1889 1984 2099 2235 2355 2491 2458 2435 2426 2439 2466 2478 2498 2503 2489 2481 2477 2477 2483 2491 2527 2532 2559 2571 2540 2489 2433 2372 2276 2163 2041 1932 1803 1662 1491 1308 1111 900 702 486 252
```
## 提示

**【样例解释 #1】**

符合要求的 $(l,r,k)$ 有以下 $13$ 组：

* $(1,1,1)$；
* $(1,1,2)$；
* $(1,2,1)$；
* $(1,2,2)$；
* $(1,3,2)$；
* $(3,3,1)$；
* $(3,3,2)$；
* $(3,4,2)$；
* $(3,5,2)$；
* $(4,4,1)$；
* $(4,4,2)$；
* $(4,5,1)$；
* $(4,5,2)$。

**【样例 #4】**

见附件中的 `string/string4.in` 与 `string/string4.ans`。

该组样例满足测试点 $1\sim3$ 的约束条件。

**【样例 #5】**

见附件中的 `string/string5.in` 与 `string/string5.ans`。

该组样例满足测试点 $4\sim6$ 的约束条件。

**【样例 #6】**

见附件中的 `string/string6.in` 与 `string/string6.ans`。

该组样例满足测试点 $7\sim10$ 的约束条件。

**【样例 #7】**

见附件中的 `string/string7.in` 与 `string/string7.ans`。

该组样例满足测试点 $13\sim14$ 和测试点 $16\sim17$ 的约束条件。

**【样例 #8】**

见附件中的 `string/string8.in` 与 `string/string8.ans`。

该组样例满足测试点 $18\sim20$ 的约束条件。

**【数据范围】**

对于所有测试数据，保证：$1\leq n\leq10$，$1\leq |S_i|\leq5\times10^4$，$1\leq |T|,K\leq5\times10^5$，字符串仅包含小写英文字母 $\texttt{a}\sim\texttt{z}$。

| 测试点编号 | $n\leq$ | $\lvert S_i\rvert\leq$ |  $\lvert T\rvert\leq$ | $K\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|:--:|
| $1\sim3$ | $10$ | $50$ | $50$ | $50$ | 无 |
| $4\sim6$ | $10$ | $100$ | $300$ | $300$ | 无 |
| $7\sim10$ | $10$ | $1000$ | $5000$ | $5000$ | 无 |
| $11\sim12$ | $10$ | $5\times10^4$ | $5\times10^5$ | $1$ | 无 |
| $13\sim14$ | $10$ | $5\times10^4$ | $5\times10^5$ | $10$ | 无 |
| $15$ | $10$ | $5\times10^4$ | $5\times10^5$ | $5\times10^5$ | 所有字符均为 $\texttt{a}$ |
| $16\sim17$ | $10$ | $5\times10^4$ | $5\times10^5$ | $5\times10^5$ | 所有字符在 $\{\texttt{a},\texttt{b}\}$ 中独立均匀随机生成 |
| $18\sim20$ | $10$ | $5\times10^4$ | $5\times10^5$ | $5\times10^5$ | 无 |


---

---
title: "[GCJ 2021 #1C] Double or NOTing"
layout: "post"
diff: 省选/NOI-
pid: P13034
tag: ['图论', '2021', 'KMP 算法', 'Google Code Jam']
---
# [GCJ 2021 #1C] Double or NOTing
## 题目描述

You are given a starting non-negative integer $\textbf{S}$ and an ending non-negative integer $\textbf{E}$. Both $\textbf{S}$ and $\textbf{E}$ are given by their binary representation (that is, they are given written in base 2). Your goal is to transform $\textbf{S}$ into $\textbf{E}$. The following two operations are available to you:

- Double your current value.
- Take the bitwise NOT of your current value. The binary representation of your current value is taken without unnecessary leading zeroes, and any unnecessary leading zeroes produced by the operation are dropped. (The only necessary leading zero is the one in the representation of 0).

For example, by using the double operation, 6 becomes 12, 0 becomes 0, and 10 becomes 20. By using the NOT operation, 0 becomes 1, 1 becomes 0, $3 = 11_2$ becomes 0, $14 = 1110_2$ becomes 1, $10 = 1010_2$ becomes $5 = 101_2$, and $5 = 101_2$ becomes $2 = 10_2$. ($X_2$ means the integer whose binary representation is $X$).

You can use these operations as many times as you want in any order. For example, you can transform $\textbf{S} = 10001_2$ to $\textbf{E} = 111_2$ using the NOT operation first, then using the double operation twice, and then another NOT operation:

$$10001_2 \xrightarrow{\text{NOT}} 1110_2 \xrightarrow{\times2} 11100_2 \xrightarrow{\times2} 111000_2 \xrightarrow{\text{NOT}} 111_2.$$

Determine the smallest number of operations needed to complete the transformation, or say it is impossible to do so.

## 输入格式

The first line of the input gives the number of test cases, $\textbf{T}$. $\textbf{T}$ test cases follow. Each consists of a single line containing two strings $\textbf{S}$ and $\textbf{E}$, the binary representations of the starting and ending integers, respectively.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is IMPOSSIBLE if there is no way to transform $\textbf{S}$ into $\textbf{E}$ using the two operations. Otherwise, $y$ is the smallest number of operations needed to transform $\textbf{S}$ into $\textbf{E}$.
## 样例

### 样例输入 #1
```
6
10001 111
1011 111
1010 1011
0 1
0 101
1101011 1101011
```
### 样例输出 #1
```
Case #1: 4
Case #2: 3
Case #3: 2
Case #4: 1
Case #5: IMPOSSIBLE
Case #6: 0
```
## 提示

**Sample Explanation**

Sample Case #1 is the example shown in the main part of the statement.

These are possible optimal ways of solving Sample Cases #2, #3, and #4, respectively:

$$1011_2 \xrightarrow{\text{NOT}} 100_2 \xrightarrow{\times2} 1000_2 \xrightarrow{\text{NOT}} 111_2,$$

$$1010_2 \xrightarrow{\times2} 10100_2 \xrightarrow{\text{NOT}} 1011_2,$$ 

and

$$0_2 \xrightarrow{\text{NOT}} 1_2.$$

In Sample Case #5, it is not possible to get from $0_2$ to $101_2$ with any sequence of operations.

In Sample Case #6, we do not need to perform any operations because $\textbf{S} = \textbf{E}$.

**Limits**

- $1 \leq \textbf{T} \leq 100$.
- Each character of $\textbf{S}$ is either 0 or 1.
- The first digit of $\textbf{S}$ can be 0 only if the length of $\textbf{S}$ is 1.
- Each character of $\textbf{E}$ is either 0 or 1.
- The first digit of $\textbf{E}$ can be 0 only if the length of $\textbf{E}$ is 1.

**Test Set 1 (14 Pts, Visible Verdict)**

- $1 \leq \text{the length of } \textbf{S} \leq 8$.
- $1 \leq \text{the length of } \textbf{E} \leq 8$.

**Test Set 2 (26 Pts, Hidden Verdict)**

- $1 \leq \text{the length of } \textbf{S} \leq 100$.
- $1 \leq \text{the length of } \textbf{E} \leq 100$.


---

---
title: "[GDCPC 2024] 腊肠披萨"
layout: "post"
diff: 省选/NOI-
pid: P13352
tag: ['2024', '广东', '容斥原理', 'AC 自动机', 'KMP 算法', 'XCPC']
---
# [GDCPC 2024] 腊肠披萨
## 题目背景

数据、标程、题解等资源的获取：<https://gitlink.org.cn/thusaa/gdcpc2024>
## 题目描述

宇宙北大街上新开了一家披萨店。这家披萨店主打使用腊肠的披萨，被顾客亲切地称为“腊肠披萨店”。这种中西合璧的做法听上去很离经叛道，但是品尝过腊肠披萨的顾客都对其称赞有加，吸引了众多食客蜂拥而至。

除了配料极具特色，腊肠披萨店的 Wi-Fi 密码也是它的流量密码。菜单上写着：“本店的 Wi-Fi 密码是

$$
\sum_{i=1}^L \sum_{j=1}^L C^{\left|LCPS\left(s_i, s_j\right)\right|} \bmod{P},
$$

其中 $LCPS\left(s_i, s_j\right)$ 表示 $s_i$ 和 $s_j$ 的最长公共前后缀，即最长的同时是 $s_i$ 前缀和 $s_j$ 后缀的字符串（可能为空，也可能为整个串）；每天的 $s_1,\cdots,s_L$ 都不一样，服务员会在点餐后提供用于当天的 Wi-Fi 密码的字符串。每天将会从前 100 名连上 Wi-Fi 的顾客中随机抽取一位免单。”

你计划下周和朋友一起来这家店聚餐，因此你想设计一个算法，快速求出这家店的 Wi-Fi 密码。
## 输入格式

输入的第一行包含三个正整数 $L, C, P$，表示字符串的数量、底数及模数。保证 $1\le L\le 3\times 10^6$，$2\le C<P<2^{30}$。

接下来 $L$ 行，每行输入一个仅由小写字符构成的字符串 $s_i$。保证 $1\le \left|s_i\right| \le 3\times 10^6$，$\sum_{i=1}^L \left|s_i\right| \le 3\times 10^6$。

## 输出格式

输出一个非负整数，表示腊肠披萨店的 Wi-Fi 密码。
## 样例

### 样例输入 #1
```
4 2 378323747
shop
pizza
piazza
pizzala
```
### 样例输出 #1
```
286
```
### 样例输入 #2
```
9 99 998244353
asap
peace
piece
pizza
sapiens
dazzling
andromeda
sakurasaku
kokorosaku
```
### 样例输出 #2
```
161369438
```
## 提示

### 样例 1 解释

对于 $1\le i,j\le 4, i\ne j$，

- $LCPS($ `pizza` $,$ `shop` $ )=LCPS($ `piazza` $,$ `shop` $)=LCPS($ `pizzala` $,$ `shop` $)=$ `p`；
- $LCPS($ `pizzala` $,$ `pizza` $)=$ `pizza`；
- 其余的 $LCPS\left(s_i, s_j\right)=\varepsilon$。

因此对应的 Wi-Fi 密码为

$$
2^4 + 2^0 + 2^0 + 2^0 + 2^1 + 2^5 + 2^0 + 2^0 + 2^1 + 2^0 + 2^6 + 2^0 + 2^1 + 2^5 + 2^0 + 2^7 = 286.
$$

腊肠披萨店在制作披萨时使用了绝密配方。在没有专业人士指导的情况下，请不要轻易模仿。


---

---
title: "[CERC 2022] Insertions"
layout: "post"
diff: 省选/NOI-
pid: P13812
tag: ['树状数组', '2022', 'KMP 算法', 'ICPC', 'CERC']
---
# [CERC 2022] Insertions
## 题目描述

We are given three strings, $s$, $t$ and $p$. We will denote the length of a string by vertical bars, thus $|s|$ is the length of $s$ and so on. If we insert $t$ into $s$ at position $k$, where $0 \leq k \leq |s|$, the result is a new string consisting of the first $k$ characters of $s$, followed by the entirety of $t$, and finally followed by the remaining $|s| - k$ characters of $s$. We would like to select $k$ so that the resulting new string will contain the largest possible number of occurrences of $p$ as a substring.

Thus, for example, inserting $t = \text{aba}$ into $s = \text{ab}$ at position $k = 0$ results in the string $\text{abaab}$; at $k = 1$, in the string $\text{aabab}$; and at $k = 2$, in the string $\text{ababa}$. If we are interested in occurrences of $p = \text{aba}$, then the best position to insert $t$ into $s$ is $k = 2$, where we get two occurrences: $\text{ababa}$ and $\text{ababa}$ (as this example shows, occurrences of $p$ are allowed to overlap). If, on the other hand, we were interested in occurrences of $p = \text{aa}$, then the best choices of $k$ would be $k = 0$ and $k = 1$, which result in one occurrence of $p$, whereas $k = 2$ results in 0 occurrences of $p$.

## 输入格式

The first line contains the string $s$, the second line the string $t$, and the third line the string $p$.
## 输出格式

Output one line containing the following four integers, separated by spaces:

1. The maximum number of occurrences of $p$ we can get after inserting $t$ into $s$ at position $k$, if we choose the position $k$ wisely.
2. The number of different $k$'s (from the range $0, 1, \ldots, |s|$) where this maximum number of occurrences of $p$ is attained.
3. The minimum value of $k$ where the maximum number of occurrences of $p$ is attained.
4. The maximum value of $k$ where the maximum number of occurrences of $p$ is attained.
## 样例

### 样例输入 #1
```
ab
aba
aba
```
### 样例输出 #1
```
2 1 2 2
```
### 样例输入 #2
```
abaab
aba
ababa
```
### 样例输出 #2
```
1 3 1 5
```
### 样例输入 #3
```
eeoeo
eoe
eeo
```
### 样例输出 #3
```
2 3 1 4
```
## 提示

### Comment

The first of these three examples is the one discussed earlier in the problem statement

### Input limits

- $1 \leq |s| \leq 10^5$
- $1 \leq |t| \leq 10^5$
- $1 \leq |p| \leq 10^5$
- All the strings consist only of lowercase letters of the English alphabet.


---

---
title: "Mivik 的标题"
layout: "post"
diff: 省选/NOI-
pid: P1393
tag: ['字符串', '数学', 'KMP 算法', '快速数论变换 NTT']
---
# Mivik 的标题
## 题目背景

Mivik 现在已经写好了他的书，他现在准备给这本书起个书名去投稿。
## 题目描述

由于 Mivik 写书是乱敲键盘敲出来的，他准备对书名干同样的事情。Mivik 的键盘上有 $m$ 个不同的按键，对应着 $m$ 个不同的字符。Mivik 决定在这个键盘上**等概率**随机敲 $n$ 次敲出标题。但出于某些原因，Mivik 希望书名中要包含有一个人的名字 $S$。于是 Mivik 来问你，他随机敲出的标题有多大的概率包含有这个名字。

同样的，Mivik 并不喜欢奇形怪状的小数，所以你只需要输出这个概率对 $998244353$ 取模后的值。
## 输入格式

第一行三个整数 $n$、$m$、$|S|$，其中 $|S|$ 代表这个名字的长度。

第二行给出 $|S|$ 个整数 $a_i$，代表这个名字。
## 输出格式

一行一个整数，代表概率对 $998244353$ 取模后的值。
## 样例

### 样例输入 #1
```
3 2 2
1 1
```
### 样例输出 #1
```
623902721
```
### 样例输入 #2
```
6 3 4
1 2 3 2
```
### 样例输出 #2
```
480636170
```
## 提示

### 样例解释

样例一：为方便描述，我们定义键盘上两个按键为 `a` 和 `b`。那么长度为 3 的所有字符串共有 `aaa`、`aab`、`aba`、`abb`、`baa`、`bab`、`bba`、`bbb` 这 8 个，其中包含有指定名字 `aa` 的共有 `aaa`、`aab`、`baa` 这三个，则概率为 $\frac{3}{8}$，取模后得到 623902721。

### 数据范围

对于全部数据，有 $1\le |S|\le 10^5$，$|S|\le n\le |S|+10^5$，$1\le m\le 10^8$。

Subtask 1 (5 pts)：满足 $m=1$。

Subtask 2 (20 pts)：满足 $1\le n, m\le 250$。

Subtask 3 (30 pts)：满足 $1\le n, m\le 5000$。

Subtask 3 (45 pts)：无特殊限制。


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
title: "[POI 2005] SZA-Template"
layout: "post"
diff: 省选/NOI-
pid: P3426
tag: ['树形数据结构', '2005', '平衡树', 'POI（波兰）', 'KMP 算法']
---
# [POI 2005] SZA-Template
## 题目描述

你打算在纸上印一串字母。

为了完成这项工作，你决定刻一个印章。印章每使用一次，就会将印章上的**所有**字母印到纸上。

同一个位置的相同字符可以印多次。例如：用 `aba` 这个印章可以完成印制 `ababa` 的工作（中间的 `a` 被印了两次）。但是，因为印上去的东西不能被抹掉，在同一位置上印不同字符是不允许的。例如：用 `aba` 这个印章不可以完成印制 `abcba` 的工作。

因为刻印章是一个不太容易的工作，你希望印章的字符串长度尽可能小。
## 输入格式

输入一个长度不超过 $5 \times 10^5$ 的非空字符串（只包含小写字母），代表要在纸上印的字符。
## 输出格式

输出一个整数，代表印章上字符串长度的最小值。
## 样例

### 样例输入 #1
```
ababbababbabababbabababbababbaba
```
### 样例输出 #1
```
8
```
## 提示

印章为 `ababbaba`。

印制过程如下：

```plain
ababbababbabababbabababbababbaba
ababbaba
     ababbaba
            ababbaba
                   ababbaba
                        ababbaba
```


---

---
title: "[POI 2007] OSI-Axes of Symmetry"
layout: "post"
diff: 省选/NOI-
pid: P3454
tag: ['字符串', '计算几何', '2007', 'POI（波兰）', 'KMP 算法']
---
# [POI 2007] OSI-Axes of Symmetry
## 题目描述

Little Johnny - a well-respected young mathematician - has a younger sister, Justina. Johnny likes hissister very much and he gladly helps her with her homework, but, like most scientific minds, he does mindsolving the same problems again. Unfortunately, Justina is a very diligent pupil, and so she asks Johnny toreview her assignments many times, for sake of certainty. One sunny Friday, just before the famous LongMay Weekend1 the math teacher gave many exercises consisting in finding the axes of symmetry of variousgeometric figures. Justina is most likely to spend considerable amount of time solving these tasks. LittleJohnny had arranged himself a trip to the seaside long time before, nevertheless he feels obliged to help hislittle sister. Soon, he has found a solution - it would be best to write a programme that wouldease checking Justina's solutions. Since Johnny is a mathematician, not a computer scientist, and you are hisbest friend, it falls to you to write it.

## Task

Write a programme that:

- reads the descriptions of the polygons from the standard input,

- determines the number of axes of symmetry for each one of them,

- writes the result to the standard output.


给定一个多边形，求对称轴数量。

## 输入格式

In the first line of the input there is one integer $t$ ($1 \le t \le 10$) - it is the number of polygons, for which the number of axes of symmetry is to be determined. Next, $t$ descriptions of the polygons follow. The first line of each description contains one integer $n$ ($3 \le n \le 100\ 000$) denoting the number of vertices of the polygon. In each of the following $n$ lines there are two integers $x$ and $y$ ($-100\ 000\ 000 \le x, y \le 100\ 000\ 000$) representing the coordinates of subsequent vertices of the polygon. The polygons need not be convex, but they have no self-intersections - any two sides have at most one common point - their common endpoint, if they actually share it. Furthermore, no pair of consecutive sides is parallel.

## 输出格式

Your programme should output exactly $t$ lines, with the $k$'th line containing a sole integer $n_k$ - the number of axes of symmetry of the $k$'th polygon.

## 样例

### 样例输入 #1
```
2
12
1 -1
2 -1
2 1
1 1
1 2
-1 2
-1 1
-2 1
-2 -1
-1 -1
-1 -2
1 -2
6
-1 1
-2 0
-1 -1
1 -1
2 0
1 1
```
### 样例输出 #1
```
4
2
```
## 题目翻译

### 题目描述

Johnny 是一位非常年轻的数学家，但他此刻正在为他妹妹的数学作业烦恼。

这个周末，他的妹妹需要完成一项作业，计算各种几何图形的对称轴数量。因为 Johnny 这个周末想要去海边旅行，所以他希望他的妹妹能尽快完成这项作业。

于是他找到了擅长编程的你，你一定能帮助他完成这项任务的！

### 输入格式

输入包含多组数据。

第一行包含一个整数 $t$，代表数据的组数。

对于每组数据，第一行一个整数 $n$，代表多边形的顶点数。

接下来 $n$ 行，每行两个整数 $x_i,y_i$，代表每个顶点的坐标。

输入中的第 $i$ 个顶点会与第 $i+1$ 个顶点连一条边。特别地，输入中的第 $n$ 个顶点会与第一个顶点连一条边。

输入给出的多边形**不保证**是凸多边形，但是保证任意两条边只会在端点处相交，且任意两条相邻的边不共线。

### 输出格式

对于每组数据，输出一行一个整数，即多边形对称轴的数量。

### 数据范围

$1 \leq t \leq 10$，$3 \leq n \leq 10^5$，$-10^8 \leq x_i,y_i \leq 10^8$。


---

---
title: "[POI 2012] PRE-Prefixuffix"
layout: "post"
diff: 省选/NOI-
pid: P3546
tag: ['字符串', '2012', 'POI（波兰）', '哈希 hashing', '线性递推', 'KMP 算法']
---
# [POI 2012] PRE-Prefixuffix
## 题目描述

We consider strings consisting of lowercase letters of the English alphabet in this problem.

An initial fragment of a given string is called its prefix.

A final (terminal) fragment of a given string is called its suffix.

In particular, the empty string is both a prefix and a suffix of any string.

Two strings are cyclically equivalent if one of them can be obtained from another by    moving its certain suffix from the end of the string to its beginning.

For example, the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.1.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.2.png) are cyclically equivalent, whereas the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.3.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.4.png) are not.

In particular, every string is cyclically equivalent to itself.

A string ![](http://main.edu.pl/images/OI19/pre-en-tex.5.png) consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.6.png) letters is given.

We are looking for its prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.7.png) and suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.8.png) of equal length such that:

![](http://main.edu.pl/images/OI19/pre-en-tex.9.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.10.png) are cyclically equivalent,                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.11.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.12.png) does not exceed ![](http://main.edu.pl/images/OI19/pre-en-tex.13.png)        (i.e., the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.14.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.15.png) do not overlap in ![](http://main.edu.pl/images/OI19/pre-en-tex.16.png)), and                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.17.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.18.png) is maximized.

对于两个串 $S_1, S_2$，如果能够将 $S_1$ 的一个后缀移动到开头后变成 $S_2$，就称 $S_1$ 和 $S_2$ 循环相同。例如串 ababba 和串 abbaab 是循环相同的。

给出一个长度为 $n$ 的串 $S$，求满足下面条件的最大的 $L(L\leq \frac n 2)$：$S$ 的 $L$ 前缀和 $S$ 的 $L$ 后缀是循环相同的。
## 输入格式

The first line of the standard input contains a single integer ![](http://main.edu.pl/images/OI19/pre-en-tex.19.png)      (![](http://main.edu.pl/images/OI19/pre-en-tex.20.png)) denoting the length of the string ![](http://main.edu.pl/images/OI19/pre-en-tex.21.png).

The second line of input contains the string ![](http://main.edu.pl/images/OI19/pre-en-tex.22.png) itself, consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.23.png) lowercase letters of the English alphabet.

In tests worth 30% of the points the condition ![](http://main.edu.pl/images/OI19/pre-en-tex.24.png) holds in addition.

In tests worth 50% of the points the condition ![](http://main.edu.pl/images/OI19/pre-en-tex.25.png) holds in addition.

## 输出格式

Your program should print a single integer in the first and only line of the standard output,      namely the common length of the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.26.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.27.png) that we are looking for.

## 样例

### 样例输入 #1
```
15
ababbabababbaab
```
### 样例输出 #1
```
6
```
## 提示

数据范围：

- 对于 $30\%$ 的数据，保证 $n\le 500$；
- 对于 $50\%$ 的数据，保证 $n\le 5000$；
- 对于 $100\%$ 数据，保证 $1\le n\le 10^6$。


---

---
title: "残缺的字符串"
layout: "post"
diff: 省选/NOI-
pid: P4173
tag: ['字符串', '数学', 'KMP 算法', '快速傅里叶变换 FFT']
---
# 残缺的字符串
## 题目描述

很久很久以前，在你刚刚学习字符串匹配的时候，有两个仅包含小写字母的字符串 $A$ 和 $B$，其中 $A$ 串长度为 $m$，$B$ 串长度为 $n$。可当你现在再次碰到这两个串时，这两个串已经老化了，每个串都有不同程度的残缺。

你想对这两个串重新进行匹配，其中 $A$ 为模板串，那么现在问题来了，请回答，对于 $B$ 的每一个位置 $i$，从这个位置开始连续 $m$ 个字符形成的子串是否可能与 $A$ 串完全匹配？
## 输入格式

第一行包含两个正整数 $m,n$，分别表示 $A$ 串和 $B$ 串的长度。

第二行为一个长度为 $m$ 的字符串 $A$。

第三行为一个长度为 $n$ 的字符串 $B$。

两个串均仅由小写字母和 $\texttt *$ 组成，其中 $\texttt *$ 表示相应位置已经残缺。
## 输出格式

第一行包含一个整数 $k$，表示 $B$ 串中可以完全匹配 $A$ 串的位置个数。

若 $k>0$，则第二行输出 $k$ 个正整数，从小到大依次输出每个可以匹配的开头位置（下标从 $1$ 开始）。
## 样例

### 样例输入 #1
```
3 7
a*b
aebr*ob
```
### 样例输出 #1
```
2
1 5
```
## 提示

$100\%$ 的数据满足 $1 \le m \le n \le 3 \times 10^5$。


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
title: "[EC Final 2022] Binary String"
layout: "post"
diff: 省选/NOI-
pid: P9717
tag: ['2022', 'O2优化', 'KMP 算法', 'ICPC']
---
# [EC Final 2022] Binary String
## 题目描述

You are given a binary string $a_0a_1a_2\dots a_{n-1}$ arranged on a cycle. Each second, you will change every $01$ to $10$ simultaneously. In other words, if $a_i = 0$ and $a_{(i+1) \bmod n} = 1$, you swap $a_i$ and $a_{(i+1)\bmod n}$. For example, we will change $\texttt{100101110}$ to $\texttt{001010111}$.

You need to answer how many different strings will occur in infinite seconds, modulo $998244353$.

Note: Two strings $a_0a_1\dots a_{n-1}$ and $b_0b_1\dots b_{n-1}$ are different if there exists an integer $i\in \{0,1,\ldots, n-1\}$ such that $a_i\neq b_i$. Thus, the cyclic shifts of a string may be different from the original string.
## 输入格式

The first line contains an integer $T$ $(1\leq T\leq 10^6)$ $-$ the number of test cases.

For each test case, the first line contains a binary string $a_0 a_1 \dots a_{n-1}$ $(a_i \in \{0, 1\})$.

It is guaranteed that the sum of lengths of strings over all test cases does not exceed $10^7$.
## 输出格式

For each test case, output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
3
1
001001
0001111
```
### 样例输出 #1
```
1
3
9
```
## 题目翻译

**【题目描述】**

给定一个排列在环上的二进制字符串 $a_0a_1a_2\dots a_{n-1}$。每一秒钟，你会同时将每个 $01$ 变为 $10$。换句话说，如果 $a_i = 0$ 且 $a_{(i+1) \bmod n} = 1$，则交换 $a_i$ 和 $a_{(i+1)\bmod n}$。例如，我们将 $\texttt{100101110}$ 变为 $\texttt{001010111}$。

你需要回答在无限秒内会出现多少种不同的字符串，取模 $998244353$。

注意：如果存在整数 $i\in \{0,1,\ldots, n-1\}$ 使得 $a_i\neq b_i$，则两个字符串 $a_0a_1\dots a_{n-1}$ 和 $b_0b_1\dots b_{n-1}$ 是不同的。因此，字符串的循环移位可能与原始字符串不同。

**【输入格式】**

第一行包含一个整数 $T$ $(1\leq T\leq 10^6)$ $-$ 测试用例的数量。

对于每个测试用例，第一行包含一个二进制字符串 $a_0 a_1 \dots a_{n-1}$ $(a_i \in \{0, 1\})$。

保证所有测试用例中字符串长度的总和不超过 $10^7$。

**【输出格式】**

对于每个测试用例，输出一行一个整数，表示答案。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

