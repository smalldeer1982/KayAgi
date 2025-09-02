---
title: "[GDKOI2023 提高组] 矩阵"
layout: "post"
diff: 提高+/省选-
pid: P10102
tag: ['2023', '广东', '随机化']
---
# [GDKOI2023 提高组] 矩阵
## 题目描述

多次给定三个 $n \times n$ 的矩阵 $A, B, C$，你需要判断 $A \times  B$ 在模 $998244353$ 意义下是否等于 $C$。
其中 $×$ 为矩阵乘法，$C_{i,j} = \sum_{k=1}^{n}A_{i,k}B_{k,j}$。

本题读入量较大，建议使用快速读入。
## 输入格式

第 $1$ 行输入一个正整数 $T$，表示数据组数。

接下来包含 $T$ 组数据，每组数据第一行为一个正整数 $n$，表示矩阵大小。

接下来 $n$ 行，每行 $n$ 个整数，表示矩阵 $A$。

接下来 $n$ 行，每行 $n$ 个整数，表示矩阵 $B$。

接下来 $n$ 行，每行 $n$ 个整数，表示矩阵 $C$。
## 输出格式

输出 $T$ 行 Yes 或 No，表示 $A \times  B$ 在模 $998244353$ 意义下是否等于 $C$。
## 样例

### 样例输入 #1
```
3
1
2
3
6
2
1 2
3 4
5 6
7 8
19 22
43 51
2
1111111 2222222
3333333 4444444
5555555 6666666
7777777 8888888
39625305 256038638
772687616 944903942
```
### 样例输出 #1
```
Yes
No
Yes
```
## 提示

对于 20% 的数据，满足 $\sum n ≤ 300$。

对于另外 20% 的数据，满足 $A_{i,j} \ne 0$ 的位置不超过 $n$ 个。

对于 100% 的数据，满足 $1 ≤ T, n ≤ 3000,\sum n ≤ 3000, 0 ≤ A_{i,j} , B_{i,j} , C_{i,j} < 998244353$。


---

---
title: "「SFMOI Round I」Strange Train Game"
layout: "post"
diff: 提高+/省选-
pid: P11146
tag: ['贪心', '并查集', '洛谷原创', 'O2优化', '图论建模', '线性基', '随机化', '洛谷月赛']
---
# 「SFMOI Round I」Strange Train Game
## 题目背景

[English statement](https://www.luogu.com.cn/problem/T512993). **You must submit your code at the Chinese version of the statement.**

SFM 团队又断网了，于是玩起了 Mini Metro，结果发现游戏更新了，列车要自己组装，于是有了这题。


## 题目描述

**提示**：我们在题目描述的最后提供了一份简要的、形式化描述的题面。

SFM 号列车由 $n$ 节车厢组成，编号为 $1\sim n$。每节车厢有一个舒适度 $a_i\in \{0,1\}$，$0$ 代表不舒适，$1$ 代表舒适。管理组想要让舒适的车厢的编号尽量小，也就是说，让 $a$ 的字典序最大。

为此，管理组运来了一辆 $n$ 节车厢的备用车，舒适度表示为 $b_i\in \{0,1\}$。共有 $m$ 个可进行的操作，第 $i$ 个操作的操作参数为 $l_i,r_i$，表示 $\forall l_i\le k\le r_i$，交换 $a_k,b_k$。

可以**从小到大依次**决定是否执行每个操作，但是一共有 $2^m$ 种方案，于是，管理组找来了你，帮忙选出一种最优的方案，最大化 $a$ 的字典序。只需要输出最终得到的 $a$ 即可。

**形式化地**：给定长度为 $n$ 的 $01$ 串 $a,b$，给定 $2m$ 个正整数 $l_i,r_i$。对于 $i=1,2,\cdots,m$，**依次**执行以下操作：
- 选择是否执行第 $i$ 次操作。
    - 如果执行，则对于 $k=l_i,l_{i}+1,\cdots,r_i$，交换 $a_k,b_k$。

最大化 $a$ 的字典序并输出最终的结果。

## 输入格式

第一行，两个正整数 $n,m$，表示字符串的长度和操作次数。

第二行，一个长度为 $n$ 的 $01$ 串 $a$。

第三行，一个长度为 $n$ 的 $01$ 串 $b$。

接下来 $m$ 行，每行两个正整数 $l_i,r_i$，描述第 $i$ 个操作。

## 输出格式

输出一行长度为 $n$ 的 $01$ 串，表示最优操作后的 $a$。

## 样例

### 样例输入 #1
```
10 5
0101011001
0101001110
5 10
2 6
1 10
6 6
3 4
```
### 样例输出 #1
```
0101011110
```
## 提示

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$1\le n,m\le 20$；
- Subtask 2（30 pts）：$l_i$ 互不相同，$a_i \ne b_i$；
- Subtask 3（30 pts）：$1 \le n ,m \le 10^3$；
- Subtask 4（20 pts）：无限制；

对于 $100\%$ 的数据，保证：
- $1\le n,m\le 2\times 10^5$；
- $1\le l_i\le r_i\le n$。


---

---
title: "「KDOI-10」反回文串"
layout: "post"
diff: 提高+/省选-
pid: P11190
tag: ['字符串', '贪心', '2024', '洛谷原创', 'Special Judge', 'O2优化', '随机化', '构造', '洛谷月赛']
---
# 「KDOI-10」反回文串
## 题目背景

[English Statement](https://www.luogu.com.cn/problem/T519008). You must submit your code at the Chinese version of the statement.

**本场比赛所有题目从标准输入读入数据，输出到标准输出。**
## 题目描述

我们称一个长度为 $m$ 的字符串 $r$ 是回文的，当且仅当 $r_i=r_{m+1-i}$ 对所有 $1\le i\le m$ 均成立。

给定一个长度为 $n$ 的字符串 $s$，你需要把 $s$ 分成若干个非空子序列，使得每一个子序列都**不是**回文的，并最大化划分成的子序列数。

形式化地说，你需要给出一组序列 $(a_1,a_2,\ldots,a_k)$，满足：

- 对于任意 $1\le i\le k$，记 $l_i$ 为 $a_i$ 的长度，则 $l_i\ge 1$，且 $1\le a_{i,1}<a_{i,2}<\cdots<a_{i,l_i}\le n$；
- 对于任意 $1\le i\le n$，恰好存在一个二元组 $(p,q)$，使得 $a_{p,q}=i$；
- 对于任意 $1\le i\le k$，记字符串 $t=s_{a_{i,1}}s_{a_{i,2}}\ldots s_{a_{i,l_i}}$，则 $t$ 不是回文的。

在此基础上，你需要最大化 $k$ 的值；或者判断不存在一种合法的方案。

特别地，如果 $k$ 的值不是最大的，你也可能获得一定的部分分。

## 输入格式

从标准输入读入数据。

**本题有多组测试数据。** 

输入的第一行包含一个正整数 $c$，表示测试点编号。$c=0$ 表示该测试点为样例。

第二行包含一个正整数 $q$，表示测试数据组数。

对于每组测试数据：

- 第一行包含一个正整数 $n$，表示字符串 $s$ 的长度；
- 第二行包含一个长度为 $n$ 的字符串 $s$。保证 $s$ 中仅包含小写英文字母。
## 输出格式

输出到标准输出。

对于每组测试数据：

- 如果不存在一种合法的方案，输出一行一个字符串 `Shuiniao`；
- 否则，你需要：
  - 在第一行输出一个字符串 `Huoyu`；
  - 第二行输出一个正整数 $k$ $(1\le k\le n)$，表示你划分成的子序列个数；
  - 接下来 $k$ 行，对于第 $i$ 行 $(1\le i\le k)$：
    - 首先输出一个正整数 $l_i$ $(1\le l_i\le n)$，表示第 $i$ 个子序列的长度；
    - 接下来输出 $l_i$ 个正整数 $a_{i,1},a_{i,2},\ldots, a_{i,l_i}$ $(1\le a_{i,j}\le n)$，表示第 $i$ 个子序列。

请注意，你的输出需要满足题目描述中所有的限制，否则，你将会得到 $0$ 分。
## 样例

### 样例输入 #1
```
0
4
4
kdoi
7
ccccccc
7
sszcdjr
7
abacaca
```
### 样例输出 #1
```
Huoyu
2
2 1 2
2 3 4
Shuiniao
Huoyu
3
3 1 2 3
2 4 5
2 6 7
Huoyu
3
2 1 4
3 2 3 5
2 6 7

```
## 提示

**【样例 1 解释】**

对于第一组测试数据，显然输出构成一个合法的子序列划分，并且

- 对于第一个子序列，$t=\tt{kd}$ 不是回文的；
- 对于第二个子序列，$t=\tt{oi}$ 不是回文的。

故这是一组合法的输出。可以证明，对于这组测试数据，$2$ 是 $k$ 的最大可能值。

对于第二组数据，它的任意一个子序列都是回文的， 故显然不存在合法的划分方案。

**【样例 2】**

见选手目录下的 `anti/anti2.in` 与 `anti/anti2.ans`。

这个样例共有 $10$ 组数据，均满足 $n=1\,000$。其中第 $1\sim 3$ 组数据满足特殊性质 A，第 $4\sim 6$ 组数据满足特殊性质 B。

***

**【评分方式】**

本题共有 $20$ 个测试点，每个测试点满分 $5$ 分。

本题采用自定义校验器（special judge）评测。每组测试数据可能有多组解，你只需要给出**任意**一组。

在每个测试点中，你的得分是在所有测试数据上得分的最小值。对于每组测试数据：

- 如果你错误地判断了是否有解或者给出了一组不合法的序列，你将会获得 $0$ 分；
- 如果你正确判断了是否有解，并在有解时给出了一组合法的序列：
  - 如果 $k$ 的值不是最大的，你将会获得 $2$ 分；
  - 如果 $k$ 的值是最大的，你将会获得 $5$ 分。
  
***

**【数据范围】**

对于全部的测试数据，保证：

- $1\le q\le 10$；
- $1\le n\le 10^5$；
- $s$ 中仅包含小写英文字母。

|测试点|$n\le$|特殊性质|
|:--:|:--:|:--:|
|$1,2$|$5$|无|
|$3\sim 5$|$18$|无|
|$6\sim 8$|$1\,000$|B|
|$9\sim 11$|$1\,000$|无|
|$12\sim 14$|$10^5$|A|
|$15\sim 17$|$10^5$|B|
|$18\sim 20$|$10^5$|无|

- 特殊性质 A：保证 $n$ 是偶数，且 $s$ 中每个字符的出现次数都不超过 $\frac{n}{2}$；
- 特殊性质 B：保证 $s$ 中仅有 `a` 和 `b`。

***

**【如何使用校验器】**

为了方便选手测试，在附件的 `anti` 目录下我们下发了 `checker.cpp` 文件作为样例校验器，选手可以编译该程序，并使用它校验自己的输出文件的结果是否**合法**。但请注意它与最终评测时所使用的校验器并不完全一致。你也不需要关心其代码的具体内容。

编译命令为：

```sh
g++ -o checker -std=c++14 -O2 checker.cpp
```

`checker` 的使用方式为：

```sh
checker <input-file> <output-file>
```

其中，参数 ` <input-file>` 与 `<output-file>` 依次表示输入文件与你的输出文件。

若你的输出中的数字大小范围不合法，则校验器会给出相应提示并立即退出。否则，校验器输出以下内容：

- 在第 $i$ 行 $(1\le i\le q)$ 中，输出第 $i$ 组测试数据的详细提示信息；
- 在第 $(q+1)$ 行，输出这个测试点的总结信息。

例如，对于样例 1 的输入与输出，校验器将会向屏幕打印如下内容：

```plain
Test case 1: OK. Participant's answer is YES (Huoyu), and k=2.
Test case 2: OK. Participant's answer is NO (Shuiniao).
Test case 3: OK. Participant's answer is YES (Huoyu), and k=3.
Test case 4: OK. Participant's answer is YES (Huoyu), and k=3.
ok 4 / 4 test cases passed. (4 test cases)
```

若将输出改为如下：

```plain
Huoyu
2
2 1 2
2 3 4
Huoyu
1
7 1 2 3 4 5 6 7
Huoyu
3
3 1 2 3
2 4 5
2 6 7
Huoyu
3
2 1 4
3 2 3 5
2 6 7
```

则会向屏幕打印如下内容：

```plain
Test case 1: OK. Participant's answer is YES (Huoyu), and k=2.
Test case 2: Wrong answer. The string t obtained in the subsequence a[1] is palindrome.
Test case 3: OK. Participant's answer is YES (Huoyu), and k=3.
Test case 4: OK. Participant's answer is YES (Huoyu), and k=3.
wrong answer 3 / 4 test cases passed.
```

**请注意：** 样例校验器只会检查你的输出是否合法，而**不会**：

- 检查有解性是否判断正确；
- 检查 $k$ 是否被最大化。

例如，将样例 1 的输出改为如下：

```plain
Shuiniao
Shuiniao
Shuiniao
Shuiniao
```

此时，样例校验器仍会返回 `ok` 的检查结果。



---

---
title: "[NERC 2022] Amazing Trick"
layout: "post"
diff: 提高+/省选-
pid: P12790
tag: ['模拟', '图论', '2022', 'Special Judge', '置换', '随机化', '构造', 'ICPC', 'Ad-hoc', 'NERC/NEERC']
---
# [NERC 2022] Amazing Trick
## 题目描述

Alice is a magician and she creates a new trick. She has $n$ cards with different numbers from $1$ to $n$ written on them. First, she asks an audience member to shuffle the deck and put cards in a row. Let's say the $i$-th card from the left has the number $a_i$ on it. 

Then Alice picks two permutations $p$ and $q$. There is a restriction on $p$ and $q$ --- $\textbf{permutations can't have fixed points}$. Which means $\forall i: p_i \ne i\ and\ q_i \ne i$.

After permutations are chosen, Alice shuffles the cards according to them. Now the $i$-th card from the left is the card $a[p[q[i]]$. The trick is considered successful if $i$-th card from the left has the number $i$ on it after the shuffles.

Help Alice pick the permutations $p$ and $q$ or say it is not possible for the specific starting permutation $a$. 
## 输入格式

The first line of the input contains the number of tests $t$ ($1 \leq t \leq 10^5$). 

Each test is described in two lines. The first line contains one integer $n$ --- the number of cards ($1 \leq n \leq 10^5$). The second line contains $n$ integers $a_i$ --- the initial permutation of the cards ($1 \leq a_i \leq n$; $\forall i \neq j: a_i \neq a_j$). 

It is guaranteed that the sum of $n$ over all tests does not exceed $10^5$.
## 输出格式

Print the answer for each test case in the same order the cases appear in the input.

For each test case, print $\tt{Impossible}$ in a single line, if no solution exists.

Otherwise, print $\tt{Possible}$ in the first line, and in the following two lines print permutations $p$ and $q$.
## 样例

### 样例输入 #1
```
4
2
2 1
3
1 2 3
4
2 1 4 3
5
5 1 4 2 3
```
### 样例输出 #1
```
Impossible
Possible
3 1 2
2 3 1
Possible
3 4 2 1
3 4 2 1
Possible
4 1 2 5 3
3 1 4 5 2
```


---

---
title: "[GCJ 2016 #3] Forest University"
layout: "post"
diff: 提高+/省选-
pid: P13203
tag: ['图论', '2016', 'Special Judge', '图论建模', '概率论', '随机化', 'Google Code Jam']
---
# [GCJ 2016 #3] Forest University
## 题目描述

The Forest University offers its students $\mathbf{N}$ courses, which must all be taken to obtain the degree. The courses can only be taken one at a time - you must complete a course before starting another. Each course is either basic, which means one can take it without any prior knowledge, or advanced, in which case exactly one other course is its prerequisite.

A student must take the prerequisite for a course before taking the course, although they do not need to be taken immediately one after the other. A course might be the prerequisite for multiple other courses. There are no prerequisite cycles. Any sequence of the $\mathbf{N}$ courses that meets the rules for prerequisites is valid for obtaining the degree.

When you graduate, the university commemorates the sequence of courses you have taken by printing an abbreviated version of it on your graduation hat. More precisely, this abbreviated version is a string consisting of the first letter of the name of each course you have taken, in the order you have taken them. For example, if you have taken a Coding course and a Jamming course, in that order, your graduation hat will say `CJ`. It is considered trendy to have certain cool words as a substring of the string on one's graduation hat.

Consider all possible valid sequences in which the courses can be taken. For each cool word, you need to find the fraction of those sequences that have the cool word as a substring (at least once) of the string on the corresponding graduation hat. Note that we're interested in the fraction of possible course sequences, not the fraction of possible different graduation hat strings. (Since multiple courses may start with the same letter, there may be fewer possible strings than course sequences.)

Somewhat unusually for Code Jam, we are only looking for an approximate answer to this problem; pay careful attention to the output format.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of five lines, in this order, which contain the following:

1. the number $\mathbf{N}$ of courses.
2. $\mathbf{N}$ integers; the i-th of these integers gives the number of the prerequisite course for the i-th course, or 0 if the i-th course is basic. The courses are numbered from 1 to $\mathbf{N}$.
3. $\mathbf{N}$ uppercase English letters (without whitespace in between), with the i-th character giving the first letter of the i-th course's name.
4. the number $\mathbf{M}$ of cool words.
5. $\mathbf{M}$ cool words, each of which consists only of uppercase English letters.
## 输出格式

For each test case, output one line containing Case #x: $y_{1}$ $y_{2}$ $\ldots$ $y_{\mathbf{M}}$, where $\mathrm{x}$ is the test case number (starting from 1) and $y_{\mathrm{i}}$ is the fraction of valid course sequences that will have the i-th cool word as a substring of the string on the graduation hat.

$y_{\mathrm{i}}$ will be considered correct if it is within an absolute error of 0.03 of the correct answer. See the FAQ for an explanation of what that means, and what formats of real numbers we accept.
## 样例

### 样例输入 #1
```
2
2
0 1
CJ
4
CJ C D JC
3
0 1 0
BAA
3
AA AAB ABA
```
### 样例输出 #1
```
Case #1: 1.0 1.0 0.0 0.0
Case #2: 0.67 0.0 0.33
```
## 提示

**Sample Explanation**

The sample output displays one set of acceptable answers to the sample cases. Other answers are possible within the allowed precision.

In sample case #1, course 1 (C) is a basic course that is a prerequisite for the advanced course 2 (J). The only way to complete the courses is to take course 1 and then course 2. This creates the string CJ. So the cool words CJ, C, D, and JC are present as substrings in 1, 1, 0, and 0 out of 1 possible cases, respectively.

In sample case #2, the basic course 1 (B) is a prerequisite for the advanced course 2 (A), and course 3 (A) is another basic course. There are three possible ways of completing the courses:

1. take course 1, then course 2, then course 3 (string: BAA)
2. take course 1, then course 3, then course 2 (string: BAA)
3. take course 3, then course 1, then course 2 (string: ABA)

The cool words AA, AAB, and ABA are present as substrings in 2, 0, and 1 out of 3 possible cases, respectively.

**Limits**

**Small dataset (25 Pts, Test Set 1 - Visible)**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $1 \leqslant \mathbf{N} \leqslant 100$.
- $1 \leqslant \mathbf{M} \leqslant 5$.
- The length of each cool word is between 1 and 20.
- Each cool word consists of uppercase English letters only.
- There are no cycles formed by the prerequisites.


---

---
title: "[USACO05FEB] Jersey Politics G"
layout: "post"
diff: 提高+/省选-
pid: P1675
tag: ['2005', 'USACO', 'Special Judge', '随机化']
---
# [USACO05FEB] Jersey Politics G
## 题目描述

在 Wisconsin（地名），有 $3 \times k$ 个城市，依次标号为 $1, 2, \cdots, 3 \times k$，每个城市共有 $1000$ 头奶牛。Jersey（人名）在这些城市中各占有 $w _ 1, w _ 2, \cdots, w _ {3 \times k}$（$0 \leq w _ i \leq 1000$）头奶牛。

你需要将这些城市平分为 $3$ 组。显然，此时每组城市中总共有 $1000 \times k$ 头奶牛。

你需要保证，在至少两组城市中，Jersey 占有的奶牛总数**严格大于** $1000 \times k$ 的一半。

求一种可行的分配方案。


## 输入格式

第一行一个整数 $k$。

然后 $3\times k$ 行，一行一个整数 $w_i$。
## 输出格式

输出有三组，第 $i$ 组输出 $k$ 行，表示第 $i$ 个区域的城市编号。
## 样例

### 样例输入 #1
```
2
510
500
500
670
400
310
```
### 样例输出 #1
```
1
2
3
6
5
4
```
## 提示

可能会有多组解，输出任意一组即可。

$1\le k\le 60$。


---

---
title: "外太空旅行"
layout: "post"
diff: 提高+/省选-
pid: P4212
tag: ['模拟', '枚举', '随机化', '状压 DP']
---
# 外太空旅行
## 题目描述

在人类的触角伸向银河系的边缘之际，普通人上太空旅行已经变得稀松平常了。某理科试验班有 $n$ 个人，现在班主任要从中选出尽量多的人去参加一次太空旅行活动。
可是 $n$ 名同学并不是和平相处的。有的人，比如小 A 和小 B 整天狼狈为奸，是好朋友；但还有的人，比如（政治敏感）和（政治敏感）就水火不相容。这 $n$ 名同学，由于是理科生，都非常的理性，所以“朋友的朋友就是朋友”和“敌人的朋友就是敌人”这两句话对这些同学无效。换句话说，有可能小 A 和小 B 是朋友，小 B 和小 C 是朋友，但是小 A 和小 C 两人势如水火。  
任意两个人之间要不就是敌人，要不就是朋友。  
因为在太空船上发生人员斗殴事件是很恶劣也很危险的，因此选出来参加旅行活动的同学必须互相之间都是朋友。你的任务就是确定最多可以选多少人参加旅行。
## 输入格式

第一行一个整数 $n(1 \le n \le 50)$。所有的同学按照 $1 \sim n$ 编号。  
接下来若干行，每行两个用空格隔开的整数 $a, b(1 \le a,b \le n)$，表示 $a$ 和 $b$ 是朋友。
注意：如果一个数对 $(x,y)$（或者 $(y,x)$）没有在文件中出现，那么编号为 $x$ 和 $y$ 的两个同学就是敌人。
## 输出格式

一个数，即最多可以选多少人参加活动。
## 样例

### 样例输入 #1
```
4
1 2
2 3
3 1
1 4
```
### 样例输出 #1
```
3
```


---

---
title: "[USACO18OPEN] Multiplayer Moo S"
layout: "post"
diff: 提高+/省选-
pid: P4380
tag: ['2018', 'USACO', '并查集', '枚举', '随机化']
---
# [USACO18OPEN] Multiplayer Moo S
## 题目描述

奶牛们提出了一款创新性的新游戏，令人惊讶的是她们给这款游戏取了个最没创意的名字：“Moo”。  
Moo 游戏在一个由 $N \times N$ 个正方形格子组成的棋盘上进行。一头奶牛可以通过大叫一声“哞！”然后把她的数字编号写在这个格子里来占有这个格子。

在游戏结束时，每个格子中都包含一个数。此时，如果一头奶牛创建了一个由连通的格子组成的领域，且该领域的大小不小于其他所有领域，那么这头奶牛就获胜。一个“领域”被定义为一些具有相同数字编号的格子，其中每个格子都直接与另一个同一领域中的格子通过上、下、左或右相邻（对角线不计）。

由于以单牛形式进行游戏有点无聊，奶牛们也对双牛组队进行游戏感兴趣。同一队的两头奶牛可以创建一个领域，但现在领域中的格子可以属于队伍中的任一头奶牛。

给定游戏棋盘的最终状态，请帮助奶牛们计算：  
1. 任何单头奶牛占有的最大领域包含的格子数量。  
2. 任何两头奶牛组成的队伍占有的最大领域包含的格子数量。  

注意，两头奶牛占有的领域必须同时包含队伍中两头奶牛的编号，不能仅仅包含一头。
## 输入格式

输入的第一行包含 $N$（$1 \leq N \leq 250$）。接下来的 $N$ 行，每行包含 $N$ 个整数（每个整数在 $0 \ldots 10^6$ 之间），描述棋盘的最终状态。棋盘中至少出现两种不同的数字。
## 输出格式

输出的第一行描述任何单头奶牛占有的最大领域大小，第二行描述任何两头奶牛的队伍占有的最大领域大小。
## 样例

### 样例输入 #1
```
4
2 3 9 3
4 9 9 1
9 9 1 7
2 1 1 9
```
### 样例输出 #1
```
5
10

```
## 提示

在这个例子中，单头奶牛占有的最大领域是由五个 $9$ 组成的。如果编号为 $1$ 和 $9$ 的奶牛组队，她们可以形成一个大小为 $10$ 的领域。

供题：Brian Dean


---

