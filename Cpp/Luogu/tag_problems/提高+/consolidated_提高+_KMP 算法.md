---
title: "[蓝桥杯 2024 国 A] 重复的串"
layout: "post"
diff: 提高+/省选-
pid: P10581
tag: ['2024', '矩阵加速', 'KMP 算法', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 A] 重复的串
## 题目描述

给定一个仅含小写字母的字符串 $S$，问有多少个长度为 $n$ 的仅含小写字母的字符串中恰好出现了两次 $S$。答案对 $998\ 244\ 353$ 取模。
## 输入格式

输入一行包含一个字符串 $S$ 和一个整数 $n$，用一个空格分隔。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
aba 6
```
### 样例输出 #1
```
53
```
### 样例输入 #2
```
aba 10
```
### 样例输出 #2
```
77907666
```
## 提示

对于 $40\%$ 的评测用例，$n \le 20$，$|S| \le 6$；  
另有 $10\%$ 的评测用例，$n\le 500$，$|S| \le 2$；  
对于 $70\%$ 的评测用例，$n\le 10^5$；  
对于所有评测用例，$1\le n\le 10^9$，$1 \le |S| \le 30$。


---

---
title: "BZOJ2372 music"
layout: "post"
diff: 提高+/省选-
pid: P10634
tag: ['字符串', 'O2优化', '哈希 hashing', 'KMP 算法']
---
# BZOJ2372 music
## 题目描述

最近 A、B 两国发生了一场战争。dick 作为 A 国的军事总指挥，最近非常头痛于己方的情报问题。因为 B 国最近雇佣了 Easy 这一位密码专家来给他们的所有通讯加密。

Easy 非常喜欢唱歌，于是他决定将所有的信号都变成旋律储存起来，比如说 $11556654433221$ 就可能是一段加过密的音符，我们用一个等长度的序列来表示它，就变成了 $1,1,5,5,6,6,\dots$。为了增加密码的保密性，他把加密的乐谱又调整了一下，把某些音调改变了，将原序列 $A$ 变成 $B$，有 $|A|=|B|$，且对于 $a_i=a_j$ 有 $b_i=b_j$，对于 $a_i<a_j$ 有 $b_i<b_j$，对于 $a_i>a_j$ 有 $b_i>b_j$。例如：`11221` 和 `55775` 就可能代表了同一段音符。

最近，dick 截获了一段信号，这段信号中可能包含了某些重要信息。根据以往的经验，dick 已经知道了某些旋律所代表的意义。于是 dick 想知道，对于一段已知的旋律，能不能判断它是否在这段截获的旋律中出现？如果出现了，能否找出它出现的次数及位置呢？

「任务」判断给定旋律在截获旋律中出现的次数及位置。
## 输入格式

第一行三个正整数 $n,m,s$，$n$ 是截获旋律的长度，$m$ 是已知旋律的长度，所有的旋律都是 $1\sim s(s\leq 25)$ 的正整数。

接下来 $n$ 行，每行一个整数描述截获的旋律 $A$；

接下来 $m$ 行，每行一个整数描述已知的旋律 $B$；
## 输出格式

第一行一个整数 $t$ 表示出现的次数。

然后 $t$ 行，按照从小到大给出出现时的起始位置 $p$，即：$A[p\dots p+m-1]$ 等价于 $B$。
## 样例

### 样例输入 #1
```
9 6 10
5
6
2
10
10
7
3
2
9
1
4
4
3
2
1
```
### 样例输出 #1
```
1
3
```
## 提示

对于所有数据，保证 $1\leq n \leq 10^5$，$1\leq m \leq 25000$。


---

---
title: "[NOI2014] 动物园"
layout: "post"
diff: 提高+/省选-
pid: P2375
tag: ['字符串', '递推', '2014', 'NOI', 'KMP 算法']
---
# [NOI2014] 动物园
## 题目描述

近日，园长发现动物园中好吃懒做的动物越来越多了。例如企鹅，只会卖萌向游客要吃的。为了整治动物园的不良风气，让动物们凭自己的真才实学向游客要吃的，园长决定开设算法班，让动物们学习算法。

某天，园长给动物们讲解 KMP 算法。

园长：“对于一个字符串 $S$，它的长度为 $L$。我们可以在 $O(L)$ 的时间内，求出一个名为 $\mathrm{next}$ 的数组。有谁预习了 $\mathrm{next}$ 数组的含义吗？”

熊猫：“对于字符串 $S$ 的前 $i$ 个字符构成的子串，既是它的后缀又是它的前缀的字符串中（它本身除外），最长的长度记作 $\mathrm{next}[i]$。”

园长：“非常好！那你能举个例子吗？”

熊猫：“例 $S$ 为 $\verb!abcababc!$，则 $\mathrm{next}[5]=2$。因为$S$的前$5$个字符为 $\verb!abcab!$，$\verb!ab!$ 既是它的后缀又是它的前缀，并且找不到一个更长的字符串满足这个性质。同理，还可得出 $\mathrm{next}[1] = \mathrm{next}[2] = \mathrm{next}[3] = 0$，$\mathrm{next}[4] = \mathrm{next}[6] = 1$，$\mathrm{next}[7] = 2$，$\mathrm{next}[8] = 3$。”

园长表扬了认真预习的熊猫同学。随后，他详细讲解了如何在 $O(L)$ 的时间内求出 $\mathrm{next}$ 数组。

下课前，园长提出了一个问题：“KMP 算法只能求出 $\mathrm{next}$ 数组。我现在希望求出一个更强大 $\mathrm{num}$ 数组一一对于字符串 $S$ 的前 $i$ 个字符构成的子串，既是它的后缀同时又是它的前缀，并且该后缀与该前缀不重叠，将这种字符串的数量记作 $\mathrm{num}[i]$。例如 $S$ 为 $\verb!aaaaa!$，则 $\mathrm{num}[4] = 2$。这是因为$S$的前 $4$ 个字符为 $\verb!aaaa!$，其中 $\verb!a!$ 和 $\verb!aa!$ 都满足性质‘既是后缀又是前缀’，同时保证这个后缀与这个前缀不重叠。而 $\verb!aaa!$ 虽然满足性质‘既是后缀又是前缀’，但遗憾的是这个后缀与这个前缀重叠了，所以不能计算在内。同理，$\mathrm{num}[1] = 0,\mathrm{num}[2] = \mathrm{num}[3] = 1,\mathrm{num}[5] = 2$。”

最后，园长给出了奖励条件，第一个做对的同学奖励巧克力一盒。听了这句话，睡了一节课的企鹅立刻就醒过来了！但企鹅并不会做这道题，于是向参观动物园的你寻求帮助。你能否帮助企鹅写一个程序求出$\mathrm{num}$数组呢？

特别地，为了避免大量的输出，你不需要输出 $\mathrm{num}[i]$ 分别是多少，你只需要输出所有 $(\mathrm{num}[i]+1)$ 的乘积，对 $10^9 + 7$ 取模的结果即可。

## 输入格式

第 $1$ 行仅包含一个正整数 $n$，表示测试数据的组数。  
随后 $n$ 行，每行描述一组测试数据。每组测试数据仅含有一个字符串 $S$，$S$ 的定义详见题目描述。数据保证 $S$ 中仅含小写字母。输入文件中不会包含多余的空行，行末不会存在多余的空格。

## 输出格式

包含 $n$ 行，每行描述一组测试数据的答案，答案的顺序应与输入数据的顺序保持一致。对于每组测试数据，仅需要输出一个整数，表示这组测试数据的答案对 $10^9+7$ 取模的结果。输出文件中不应包含多余的空行。

## 样例

### 样例输入 #1
```
3
aaaaa
ab
abcababc
```
### 样例输出 #1
```
36
1
32 
```
## 提示

测试点编号| 约定
-|-  
1| $n \le 5, L \le 50$  
2| $n \le 5, L \le 200$  
3| $n \le 5, L \le 200$  
4| $n \le 5, L \le 10,000$  
5| $n \le 5, L \le 10,000$  
6| $n \le 5, L \le 100,000$  
7| $n \le 5, L \le 200,000$   
8| $n \le 5, L \le 500,000$  
9| $n \le 5, L \le 1,000,000$  
10| $n \le 5, L \le 1,000,000$  



---

---
title: "[HNOI2008] GT考试"
layout: "post"
diff: 提高+/省选-
pid: P3193
tag: ['递推', '2008', '湖南', '矩阵乘法', 'KMP 算法']
---
# [HNOI2008] GT考试
## 题目描述

阿申准备报名参加 GT 考试，准考证号为 $N$ 位数$X_1,X_2…X_n\ (0\le X_i\le 9)$，他不希望准考证号上出现不吉利的数字。
他的不吉利数字$A_1,A_2,\cdots, A_m\ (0\le A_i\le 9)$ 有 $M$ 位，不出现是指 $X_1,X_2\cdots X_n$ 中没有一段恰好等于 $A_1,A_2,\cdots ,A_m$，$A_1$ 和 $X_1$ 可以为 $0$。
## 输入格式

第一行输入 $N,M,K$ 接下来一行输入 $M$ 位的数。
## 输出格式

阿申想知道不出现不吉利数字的号码有多少种，输出模 $K$ 取余的结果。
## 样例

### 样例输入 #1
```
4 3 100
111
```
### 样例输出 #1
```
81
```
## 提示

### 数据范围及约定

对于全部数据，$N\leq10^9$，$M\leq 20$，$K\leq10000$。


---

---
title: "[POI 2006] OKR-Periods of Words"
layout: "post"
diff: 提高+/省选-
pid: P3435
tag: ['2006', 'POI（波兰）', 'KMP 算法']
---
# [POI 2006] OKR-Periods of Words
## 题目描述

A string is a finite sequence of lower-case (non-capital) letters of the English alphabet. Particularly, it may be an empty sequence, i.e. a sequence of 0 letters. By A=BC we denotes that A is a string obtained by concatenation (joining by writing one immediately after another, i.e. without any space, etc.) of the strings B and C (in this order). A string P is a prefix of the string !, if there is a string B, that A=PB. In other words, prefixes of A are the initial fragments of A. In addition, if P!=A and P is not an empty string, we say, that P is a proper prefix of A.


A string Q is a period of Q, if Q is a proper prefix of A and A is a prefix (not necessarily a proper one) of the string QQ. For example, the strings abab and ababab are both periods of the string abababa. The maximum period of a string A is the longest of its periods or the empty string, if A doesn't have any period. For example, the maximum period of ababab is abab. The maximum period of abc is the empty string.

Task Write a programme that:

reads from the standard input the string's length and the string itself,calculates the sum of lengths of maximum periods of all its prefixes,writes the result to the standard output.



## 输入格式

In the first line of the standard input there is one integer $k$ ($1\le k\le 1\ 000\ 000$) - the length of the string. In the following line a sequence of exactly $k$ lower-case letters of the English alphabet is written - the string.

## 输出格式

In the first and only line of the standard output your programme should write an integer - the sum of lengths of maximum periods of all prefixes of the string given in the input.

## 样例

### 样例输入 #1
```
8
babababa
```
### 样例输出 #1
```
24
```
## 题目翻译

对于一个仅含小写字母的字符串 $a$，$p$ 为 $a$ 的前缀且 $p\ne a$，那么我们称 $p$ 为 $a$ 的 proper 前缀。

规定字符串 $Q$ 表示 $a$ 的周期，当且仅当 $Q$ 是 $a$ 的 proper 前缀且 $a$ 是 $Q+Q$ 的前缀。若这样的字符串不存在，则 $a$ 的周期为空串。

例如 `ab` 是 `abab` 的一个周期，因为 `ab` 是 `abab` 的 proper 前缀，且 `abab` 是 `ab+ab` 的前缀。

求给定字符串所有前缀的最大周期长度之和。


---

---
title: "【模板】失配树"
layout: "post"
diff: 提高+/省选-
pid: P5829
tag: ['字符串', '树形数据结构', 'KMP 算法']
---
# 【模板】失配树
## 题目描述

给定一个字符串 $s$，定义它的 **$k$ 前缀** $\mathit{pre}_k$ 为字符串 $s_{1\dots k}$，**$k$ 后缀** $\mathit{suf}_k$ 为字符串 $s_{|s|-k+1\dots |s|}$，其中 $1 \le k \le |s|$。

定义 $\bold{Border}(s)$ 为**对于 $i \in [1, |s|)$，满足 $\mathit{pre}_i = \mathit{suf}_i$** 的字符串 $\mathit{pre}_i$ 的集合。$\bold{Border}(s)$ 中的每个元素都称之为字符串 $s$ 的 $\operatorname{border}$。

有 $m$ 组询问，每组询问给定 $p,q$，求 $s$ 的 **$\boldsymbol{p}$ 前缀** 和 **$\boldsymbol{q}$ 前缀** 的 **最长公共 $\operatorname{border}$**  的长度。
## 输入格式

第一行一个字符串 $s$。

第二行一个整数 $m$。

接下来 $m$ 行，每行两个整数 $p,q$。
## 输出格式

对于每组询问，一行一个整数，表示答案。若不存在公共 $\operatorname{border}$，请输出 $0$。
## 样例

### 样例输入 #1
```
aaaabbabbaa
5
2 4
7 10
3 4
1 2
4 11

```
### 样例输出 #1
```
1
1
2
0
2

```
### 样例输入 #2
```
zzaaccaazzccaacczz
3
2 18
10 18
3 5

```
### 样例输出 #2
```
1
2
0

```
## 提示

样例 $2$ 说明：

对于第一个询问，$2$ 前缀和 $18$ 前缀分别是 ``zz`` 和 ``zzaaccaazzccaacczz``，由于 ``zz`` 只有一个 $\operatorname{border}$，即 ``z``，故最长公共 $\operatorname{border}$ 长度为 $1$。

---

对于 $16\%$ 的数据，$s$ 中的字符全部相等。

对于 $100\%$ 的数据，$1\leq p,q \le |s|\leq 10^6$，$1 \leq m \leq 10^5$，$s_i \in [\texttt{a}, \texttt{z}]$。


---

---
title: "回文匹配"
layout: "post"
diff: 提高+/省选-
pid: P6216
tag: ['前缀和', 'KMP 算法', 'Manacher 算法']
---
# 回文匹配
## 题目描述

对于一对字符串 $(s_1,s_2)$，若 $s_1$ 的长度为奇数的子串 $(l,r)$ 满足 $(l,r)$ 是回文的，那么 $s_1$ 的“分数”会增加 $s_2$ 在 $(l,r)$ 中出现的次数。

现在给出一对 $(s_1,s_2)$，请计算出 $s_1$ 的“分数”。

答案对 $2 ^ {32}$ 取模。
## 输入格式

第一行两个整数，$n,m$，表示 $s_1$ 的长度和 $s_2$ 的长度。

第二行两个字符串，$s_1,s_2$。
## 输出格式

一行一个整数，表示 $s_1$ 的分数。
## 样例

### 样例输入 #1
```
10 2
ccbccbbcbb bc
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
20 2
cbcaacabcbacbbabacca ba

```
### 样例输出 #2
```
4

```
## 提示

**【样例解释】**

   对于样例一：

   子串 $(1,5)$ 中 $s_2$ 出现了一次，子串 $(2,4)$ 中 $s_2$ 出现了一次。

   子串 $(7,9)$ 中 $s_2$ 出现了一次，子串 $(6,10)$ 中 $s_2$ 出现了一次。

--------------------------------------

**【数据范围】**

**本题采用捆绑测试。**

- 对于 $100\%$ 的数据：$1 \le n,m \le 3 \times 10 ^ 6$，字符串中的字符都是小写字母。

- **详细的数据范围：**

  | Subtask 编号 |     $n,m \le$     | 分值 |
  | :----------: | :---------------: | :--: |
  |     $1$      |       $100$       | $15$ |
  |     $2$      |     $10 ^ 3$      | $15$ |
  |     $3$      | $5 \times 10 ^ 3$ | $20$ |
  |     $4$      | $4 \times 10 ^ 5$ | $30$ |
  |     $5$      | $3 \times 10 ^ 6$ | $20$ |


---

---
title: "[Cnoi2021] 符文破译"
layout: "post"
diff: 提高+/省选-
pid: P8112
tag: ['字符串', '贪心', '2021', 'O2优化', 'KMP 算法']
---
# [Cnoi2021] 符文破译
## 题目背景

Cirno 想要解读一本古老的魔法书。
## 题目描述

为了保护魔法书中记载的禁忌的魔法，撰写者将符咒的魔法词缀不加空格地连接在一起，形成一个符文串，记作 $\texttt{S}$。

而构成符文串的所有魔法词缀都被记载在更远古的先知所编写的魔法辞典中，记作 $\texttt{T}$。具体地，$\texttt{T}$ 的所有非空前缀均是一个合法的魔法词缀。

简洁是魔法书撰写的第一要务，所以使用的魔法词缀应该尽可能少。所以在破译魔法书时，将 $\texttt{S}$ 分解成的魔法词缀数越少，破译正确的可能性就越高。

Cirno 想知道，这本魔法书最少的魔法词缀划分段数是多少。

特别地，如果不存在一种合法的划分方案，则表明这本魔法书是假的。Cirno 将得到一个字符串 `Fake`。
## 输入格式

第一行，两个整数，表示 $|\texttt{T}|$，$|\texttt{S}|$。

第二行，一个字符串 $\texttt{T}$。

第三行，一个字符串 $\texttt{S}$。
## 输出格式

一行，一个整数或一个字符串 `Fake`，表示答案。
## 样例

### 样例输入 #1
```
3 5
aba
abaab
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 5
aba
ababa
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
3 5
aba
abbaa
```
### 样例输出 #3
```
Fake
```
## 提示

**数据范围与约定**

对于 $100\%$ 的数据，保证 $1\le |\texttt{S}|,|\texttt{T}|\le 10^7$，$\texttt{S}_x,\texttt{T}_x \in [\texttt{a},\texttt{z}]$。

**子任务**

Subtask1（$10$ points）：$\texttt{T}_x=\texttt{a}$。

Subtask2（$20$ points）：$|\texttt{S}|\le1000$。

Subtask3（$30$ points）：$|\texttt{S}|\le 10^6$。

Subtask4（$40$ points）：无特殊限制。


---

---
title: "串串题"
layout: "post"
diff: 提高+/省选-
pid: P9149
tag: ['字符串', '数学', '洛谷原创', 'O2优化', '组合数学', 'KMP 算法', '洛谷月赛']
---
# 串串题
## 题目描述

给定长度分别为 $n,m$ 的整数序列 $A,B$ 和常数 $W,d$，序列从 $1$ 开始标号，保证 $A_i,B_i \in [1,W]$。

容易发现，我们有 $\binom{W}{d}$ 种方案选择 $[1,W]$ 中的 $d$ 个互不相同的整数。

对于每一种选择的方案，我们删去 $A$ 中出现的对应的 $d$ 种整数，令此时序列 $B$ 在序列 $A$ 中的出现次数为这次选择方案的权值。

你需要求所有的选择方案的权值和，对 ${10}^9+7$ 取模。

若对题意有疑问，请阅读样例及样例解释。

注：$\binom{a}{b}$ 表示组合数，含义为在 $a$ 个物品中**无序**地选择出 $b$ 个物品的方案数。

**请注意：我们并不会删除序列 $\bm{B}$ 中出现的对应整数。**
## 输入格式

**本题有多组数据。**

第一行，一个正整数 $T$，表示数据组数。对于每组数据：

第一行，四个正整数 $n, m, W, d$，保证 $d \le W$。

第二行，$n$ 个正整数 $A_1, A_2, \ldots, A_n$，表示序列 $A$。

第三行，$m$ 个正整数 $B_1, B_2, \ldots, B_m$，表示序列 $B$。
## 输出格式

对于每组数据，输出一个整数表示答案对 ${10}^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
2
4 2 3 1
1 1 2 1
1 1
8 3 4 1
1 2 3 1 2 3 1 2
1 2 1

```
### 样例输出 #1
```
3
2

```
## 提示

**【样例解释】**

在样例的第一组数据中：

1. 如果我们选择删去 $A$ 中的字符 $1$，$A$ 将变为 $\{2\}$，此时 $B$ 在 $A$ 中的出现次数为 $0$。
1. 如果我们选择删去 $A$ 中的字符 $2$，$A$ 将变为 $\{1,1,1\}$，此时 $B$ 在 $A$ 中的出现次数为 $2$。
1. 如果我们选择删去 $A$ 中的字符 $3$，$A$ 将变为 $\{1,1,2,1\}$，此时 $B$ 在 $A$ 中的出现次数为 $1$。

因此，第一组数据的答案为 $0+2+1=3$。

**再次提醒：我们并不会删除序列 $\bm{B}$ 中出现的对应整数。**

---

**【数据范围】**

对于 $100\%$ 的数据，$1 \le n,m,W \le {10}^6$，$1 \le d, A_i, B_j \le W$，$1 \le T \le 5$。

**本题采用捆绑测试且开启子任务依赖！**

| 子任务 | $n \le$ | $m \le$ | $W \le$ | 特殊性质 | 分数 | 依赖 |
| - | - | - | - | - | - | - |
| 1 | $10$ | $10$ | $5$ | | $10$ | \ |
| 2 | $1000$ | $1000$ | $5$ | | $20$ | 子任务 1 |
| 3 |  | | | A | $15$ | \ |
| 4 |  | | | B | $25$ | \ |
| 5 | | | | | $30$ | 子任务 1、2、3、4 |

特殊性质 A：保证 $d=1$。

特殊性质 B：令 $c$ 表示仅在序列 $A$ 中出现，而不在序列 $B$ 中出现的数字总数。保证 $c \le 5$。


---

