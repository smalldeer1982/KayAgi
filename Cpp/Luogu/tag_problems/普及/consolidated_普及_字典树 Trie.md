---
title: "前缀统计"
layout: "post"
diff: 普及/提高-
pid: P10470
tag: ['字典树 Trie']
---
# 前缀统计
## 题目描述

给定 $N$ 个字符串 $S_1,S_2\cdots S_N$，接下来进行 $M$ 次询问，每次询问给定一个字符串 $T$，求 $S_1 \sim S_N$ 中有多少个字符串是 $T$ 的前缀。

输入字符串的总长度不超过 $10^6$，仅包含小写字母。
## 输入格式

第一行输入两个整数 $N，M$。

接下来 $N$ 行每行输入一个字符串 $S_i$。

接下来 $M$ 行每行一个字符串 $T$ 用以询问。
## 输出格式

对于每个询问，输出一个整数表示答案。

每个答案占一行。
## 样例

### 样例输入 #1
```
3 2
ab
bc
abc
abc
efg
```
### 样例输出 #1
```
2
0
```
## 提示

数据范围满足 $1 \le N,M \le 10^5$


---

---
title: "最大异或对 The XOR Largest Pair"
layout: "post"
diff: 普及/提高-
pid: P10471
tag: ['字典树 Trie']
---
# 最大异或对 The XOR Largest Pair
## 题目描述

给定 $N$ 个整数 $A_1.A_2, \cdots, A_N$ 中选出两个进行异或计算，得到的结果最大是多少？
## 输入格式

第一行一个整数 $N$，第二行 $N$ 个整数 $A_1.A_2, \cdots, A_N$。
## 输出格式

一个整数表示答案。
## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
3
```
## 提示

对于所有测试数据，$1 \le n \le 100000$，保证 $A_i$ 在 `int` 范围内。



---

---
title: "[EPXLQ2024 fall round] 风吹起了从前"
layout: "post"
diff: 普及/提高-
pid: P11412
tag: ['排序', '哈希 hashing', '字典树 Trie']
---
# [EPXLQ2024 fall round] 风吹起了从前
## 题目背景

对于过去，温昭雪有着断断续续的记忆。
## 题目描述

具体地，她有 $n$ 条记忆，每条记忆是一个长度不超过 $100$ 的字符串。第 $i$ 条记忆 $S_i$ 位于她心灵的 $r_i$ 深处，对她有 $v_i$ 的价值。

温昭雪正在试图恢复自己记忆中的美好，可记忆实在太多太复杂，她只能想到她记忆的一段前缀 $Q$ 和她能到达的最深位置 $d$。只有满足对应的 $Q$ 是 $S_i$ 的前缀且 $r_i \le d$ 的记忆才能被温昭雪回想到。

现在，温昭雪有 $m$ 次尝试。她想知道，对于每次尝试，她能获得的所有记忆价值之和是多少。
## 输入格式

输入第一行包含 $n,m$。

以下 $n$ 行，每行两个整数 $r_i,v_i$ 和一个字符串 $S_i$，空格分隔。

以下 $m$ 行，每行一个整数 $d$ 和一个字符串 $Q$，空格分隔。保证 $Q$ 至少是某一个 $S_i$ 的前缀，**但不保证一定存在一个记忆能被回想到**。
## 输出格式

输出 $m$ 行，每行表示对于每次尝试，她能获得的所有记忆价值之和是多少。
## 样例

### 样例输入 #1
```
5 6
5 6 abcab
7 10 abcba
4 3 abc
3 6 ade
2 4 cde
2 abc
4 abc
5 abc
6 a
7 c
8 ab
```
### 样例输出 #1
```
0
3
9
15
4
19
```
## 提示

### 提示

本题对前缀的定义为：对于字符串 $S,P$，若 $|P| \le |S|$ 且对所有 $1 \le i \le |P|$ 均有 $S_i=P_i$，则称 $P$ 是 $S$ 的前缀。

### 数据规模与约定

**本题采用捆绑测试。**

| $\text{Subtask}$ | $n \le$ | $ m\le$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $0$ | $100$ | $100$ | | $11$ |
| $1$ | $10^4$ | $10^5$ | $d = 10^9$ | $13$ |
| $2$ | $10^4$ | $10^5$ | 字符串长度不超过 $2$ | $9$ |
| $3$ | $10^4$ | $10^3$ | | $26$ |
| $4$ | $10^4$ | $10^5$ | | $41$ |

对于所有数据，保证 $1 \le |S_i|,|Q| \le100, 0 \le r_i,v_i,d \le 10^9$，所有字符串仅由小写字母组成。

请注意时间复杂度常数因子带来的影响。

请考虑使用较快的输入输出方式。


---

---
title: "[GCJ 2018 #1C] A Whole New Word"
layout: "post"
diff: 普及/提高-
pid: P13142
tag: ['2018', 'Special Judge', '字典树 Trie', 'Google Code Jam']
---
# [GCJ 2018 #1C] A Whole New Word
## 题目描述

Vincent and Desta are childhood friends. Today, Vincent is showing $N$ distinct $L$-letter words to Desta by using some letter tiles. Each tile contains one uppercase English alphabet letter, and one number between $1$ and $L$. A word consists of the letters spelled out by $L$ tiles with numbers from $1$ through $L$, in order. (Vincent's words are not necessarily real English words.)

For example, if Vincent has $N = 3$ words with $L = 4$, and the words are $\{\text{CAKE}, \text{TORN}, \text{SHOW}\}$, then Vincent must show the following to Desta:

![](https://cdn.luogu.com.cn/upload/image_hosting/ve1i8p4m.png)

Desta feels that creating words must be easy, and he wants to create a new word that obeys the rules above and is not one of Vincent's existing words. However, Desta does not have any tiles of his own, so he must use some of Vincent's tiles.

For instance, if Vincent has the words from the previous example, then Desta can make a new word such as $\text{CORN}$ or $\text{SAKE}$ or $\text{CHRE}$ (Desta's words are also not necessarily real English words). Each of the example is illustrated in the following image:

![](https://cdn.luogu.com.cn/upload/image_hosting/0rhou6na.png)

Note that the three rows in the image above are independent. Desta only needs to make one new word.

However, in the above example, Desta cannot make WAKE, for example, because there is no $\text W$ tile with a number $1$. Nor can he make coo, since it is not the right length.

Notice that it may be impossible for Desta to make a new word. For example, if Vincent has only one word, then Desta cannot make anything new. Or, if Vincent has the words $\{\text{AA}, \text{AB}, \text{BA}, \text{BB}\}$, then any word that Desta can form is already present.

Help Desta to choose a word that he can show to Vincent using only the tiles used by Vincent, or indicate that it is impossible to do so.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each begins with one line with two integers $N$ and $L$: the number of Vincent's words, and the length of each word. Then, $N$ more lines follow. The $i$-th of these lines contains a string of $L$ uppercase English letters representing the $i$-th of Vincent's words.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is a valid word to be chosen by Desta, or - (a single dash character of ASCII value 45) if there is no valid word to be chosen by Desta. If there is more than one valid word that Desta can make, you can output any of them.
## 样例

### 样例输入 #1
```
5
4 1
A
B
C
D
4 2
WW
AA
SS
DD
4 2
AA
AB
BA
BB
3 4
CAKE
TORN
SHOW
5 7
HELPIAM
TRAPPED
INSIDEA
CODEJAM
FACTORY
```
### 样例输出 #1
```
Case #1: -
Case #2: WA
Case #3: -
Case #4: CORN
Case #5: HOLIDAY
```
## 提示

**Sample Explanation**

Note that the last two sample cases would not appear in test set 1.

In Sample Case #1, the only words that can be constructed using the tiles used by Vincent are A, B, C, D. However, all of those words already appear in Vincent's list of words, so Desta is not allowed to choose them.

In Sample Case #2, there are $12$ possible new words that Desta can make, one of which is $\text{WA}$.

Sample Case #3 was explained in the problem description above; there is no new word that Desta can make.

Sample Case #4 was explained in the problem description above; other answers such as $\text{SAKF}$ are possible.

In Sample Case #5, other answers such as $\text{TRAPJAM}$ are possible.

**Limits**

- $1 \leqslant T \leqslant 100$.
- No two of Vincent's words are the same.

**Test set 1 (11 Pts, Visible)**

- $1 \leqslant N \leqslant 26^{2}$.
- $1 \leqslant L \leqslant 2$.

**Test set 2 (17 Pts, Hidden)**

- $1 \leqslant N \leqslant 2000$.
- $1 \leqslant L \leqslant 10$.


---

---
title: "魔族密码"
layout: "post"
diff: 普及/提高-
pid: P1481
tag: ['树形 DP', '哈希 hashing', '字典树 Trie', '差分']
---
# 魔族密码
## 题目背景

风之子刚走进他的考场，就……

花花：当当当当~~偶是魅力女皇——花花！！^^（华丽出场，礼炮，鲜花）

风之子：我呕……（杀死人的眼神）快说题目！否则……-\_-###
## 题目描述



花花：……咦~~好冷~~我们现在要解决的是魔族的密码问题（自我陶醉：搞不好魔族里面还会有人用密码给我和菜虫写情书咧，哦活活，当然是给我的比较多拉\*^\_^\*）。

魔族现在使用一种新型的密码系统。每一个密码都是一个给定的仅包含小写字母的英文单词表，每个单词至少包含 $1$ 个字母，至多 $75$ 个字母。如果在一个由一个词或多个词组成的表中，除了最后一个以外，每个单词都被其后的一个单词所包含，即前一个单词是后一个单词的前缀，则称词表为一个词链。例如下面单词组成了一个词链：

- $\verb!i!$；
- $\verb!int!$；
- $\verb!integer!$。

但下面的单词不组成词链：

- $\verb!integer!$；
- $\verb!intern!$。

现在你要做的就是在一个给定的单词表中取出一些词，组成最长的词链，就是包含单词数最多的词链。将它的单词数统计出来，就得到密码了。

风之子：密码就是最长词链所包括的单词数阿……

## 输入格式

这些文件的格式是，第一行为单词表中的单词数 $N$（$1 \le N \le 2000$），下面每一行有一个单词，按字典顺序排列，中间也没有重复的单词。
## 输出格式

输出共一行，一个整数，表示密码。
## 样例

### 样例输入 #1
```
5
i
int
integer
intern
internet

```
### 样例输出 #1
```
4

```


---

---
title: "于是他错误的点名开始了"
layout: "post"
diff: 普及/提高-
pid: P2580
tag: ['字符串', '搜索', '字典树 Trie']
---
# 于是他错误的点名开始了
## 题目背景

XS中学化学竞赛组教练是一个酷爱炉石的人。

他会一边搓炉石一边点名以至于有一天他连续点到了某个同学两次，然后正好被路过的校长发现了然后就是一顿欧拉欧拉欧拉（详情请见已结束比赛 CON900）。
## 题目描述

这之后校长任命你为特派探员，每天记录他的点名。校长会提供化学竞赛学生的人数和名单，而你需要告诉校长他有没有点错名。（为什么不直接不让他玩炉石。）
## 输入格式

第一行一个整数 $n$，表示班上人数。

接下来 $n$ 行，每行一个字符串表示其名字（互不相同，且只含小写字母，长度不超过 $50$）。

第 $n+2$ 行一个整数 $m$，表示教练报的名字个数。

接下来 $m$ 行，每行一个字符串表示教练报的名字（只含小写字母，且长度不超过 $50$）。
## 输出格式

对于每个教练报的名字，输出一行。

如果该名字正确且是第一次出现，输出 `OK`，如果该名字错误，输出 `WRONG`，如果该名字正确但不是第一次出现，输出 `REPEAT`。
## 样例

### 样例输入 #1
```
5  
a
b
c
ad
acd
3
a
a
e

```
### 样例输出 #1
```
OK
REPEAT
WRONG

```
## 提示

- 对于 $40\%$ 的数据，$n\le 1000$，$m\le 2000$。
- 对于 $70\%$ 的数据，$n\le 10^4$，$m\le 2\times 10^4$。
- 对于 $100\%$ 的数据，$n\le 10^4$，$m≤10^5$。

---

$\text{upd 2022.7.30}$：新增加一组 Hack 数据。


---

---
title: "会议座位"
layout: "post"
diff: 普及/提高-
pid: P5149
tag: ['排序', '字典树 Trie']
---
# 会议座位
## 题目背景

话说校长最近很喜欢召开全校教职工大会，让老师们强行听他装逼

## 题目描述

现在校长在校园网上公布了一份座位表，$n$ 位老师从左到右依次排成一行。老师们都对这个座位很满意。

然而到了开会时，校长不小心把座位表打乱了，老师们很不满。老师们并不在意自己的位置变了多少，但如果有一对老师 $a$ 和 $b$，他们原来的座位是 $a$ 在 $b$ 左边，现在变成了 $a$ 在 $b$ 右边，那么这一对老师便会贡献一单位不满值。

校长想知道这些老师的总不满值是多少。
## 输入格式

第一行一个正整数 $n$，为 $n$ 位老师。

第二行有 $n$ 个字符串，每个字符串代表老师的名字（大小写敏感）。这一行代表原来的座位表。

第三行有 $n$ 个字符串，代表打乱后的座位表。
## 输出格式

一行，一个正整数，表示老师们的总不满值。
## 样例

### 样例输入 #1
```
3
Stan Kyle Kenny
Kyle Stan Kenny
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
5
A B C D E
B A D E C
```
### 样例输出 #2
```
3
```
## 提示

对于 $30\%$ 的数据，$1\le n \le 10^3$。

对于 $100\%$ 的数据，$1\le n \le 10^5$，每位老师名字长度不超过 $5$，只有大小写字母并且互不相同。注意名字对大小写敏感。


---

---
title: "【模板】字典树"
layout: "post"
diff: 普及/提高-
pid: P8306
tag: ['字符串', 'O2优化', '字典树 Trie']
---
# 【模板】字典树
## 题目描述

给定 $n$ 个模式串 $s_1, s_2, \dots, s_n$ 和 $q$ 次询问，每次询问给定一个文本串 $t_i$，请回答 $s_1 \sim s_n$ 中有多少个字符串 $s_j$ 满足 $t_i$ 是 $s_j$ 的**前缀**。

一个字符串 $t$ 是 $s$ 的前缀当且仅当从 $s$ 的末尾删去若干个（可以为 0 个）连续的字符后与 $t$ 相同。

输入的字符串大小敏感。例如，字符串 `Fusu` 和字符串 `fusu` 不同。
## 输入格式

**本题单测试点内有多组测试数据**。  

输入的第一行是一个整数，表示数据组数 $T$。

对于每组数据，格式如下：  
第一行是两个整数，分别表示模式串的个数 $n$ 和询问的个数 $q$。  
接下来 $n$ 行，每行一个字符串，表示一个模式串。  
接下来 $q$ 行，每行一个字符串，表示一次询问。
## 输出格式

按照输入的顺序依次输出各测试数据的答案。  
对于每次询问，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
3 3
fusufusu
fusu
anguei
fusu
anguei
kkksc
5 2
fusu
Fusu
AFakeFusu
afakefusu
fusuisnotfake
Fusu
fusu
1 1
998244353
9
```
### 样例输出 #1
```
2
1
0
1
2
1
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $1 \leq T, n, q\leq 10^5$，且输入字符串的总长度不超过 $3 \times 10^6$。输入的字符串只含大小写字母和数字，且不含空串。

### 说明
std 的 IO 使用的是关闭同步后的 cin/cout，本题不卡常。


---

---
title: "[蓝桥杯 2020 国 B] 游园安排"
layout: "post"
diff: 普及/提高-
pid: P8736
tag: ['动态规划 DP', '2020', '字典树 Trie', '蓝桥杯国赛']
---
# [蓝桥杯 2020 国 B] 游园安排
## 题目描述

$\mathrm{L}$ 星球游乐园非常有趣，吸引着各个星球的游客前来游玩。小蓝是 $\mathrm{L}$ 星球 游乐园的管理员。

为了更好的管理游乐园，游乐园要求所有的游客提前预约，小蓝能看到系统上所有预约游客的名字。每个游客的名字由一个大写英文字母开始，后面跟 $0$ 个或多个小写英文字母。游客可能重名。

小蓝特别喜欢递增的事物。今天，他决定在所有预约的游客中，选择一部分游客在上午游玩，其他的游客都在下午游玩，在上午游玩的游客要求按照预约的顺序排列后，名字是单调递增的，即排在前面的名字严格小于排在后面的名字。

一个名字 $A$ 小于另一个名字 $B$ 是指：存在一个整数 $i$，使得 $A$ 的前 $i$ 个字母与 $B$ 的前 $i$ 个字母相同，且 $A$ 的第 $i+1$ 个字母小于 $B$ 的第 $i+1$ 个字母。(如果 $A$ 不存在第 $i+1$ 个字母且 $B$ 存在第 $i+1$ 个字母, 也视为 $A$ 的第 $i+1$ 个字母小于 $B$ 的第 $i+1$ 个字母)

作为小蓝的助手，你要按照小蓝的想法安排游客，同时你又希望上午有尽量多的游客游玩，请告诉小蓝让哪些游客上午游玩。如果方案有多种，请输出上午游玩的第一个游客名字最小的方案。如果此时还有多种方案，请输出第一个游客名字最小的前提下第二个游客名字最小的方案。如果仍然有多种，依此类推选择第三个、第四个……游客名字最小的方案。

## 输入格式

输入包含一个字符串，按预约的顺序给出所有游客的名字，相邻的游客名字之间没有字符分隔。
## 输出格式

按预约顺序输出上午游玩的游客名单，中间不加任何分隔字符。 
## 样例

### 样例输入 #1
```
WoAiLanQiaobei
```
### 样例输出 #1
```
AiLanQiaobei
```
## 提示

对于 $20 \%$ 的评测数据, 输入的总长度不超过 $20$ 个字母。

对于 $50 \%$ 的评测数据, 输入的总长度不超过 $300$ 个字母。

对于 $70 \%$ 的评测数据, 输入的总长度不超过 $10000$ 个字母。

对于所有评测数据, 每个名字的长度不超过 $10$ 个字母, 输入的总长度不超过 $10^6$ 个字母。 

蓝桥杯 2020 年国赛 B 组 G 题。


---

