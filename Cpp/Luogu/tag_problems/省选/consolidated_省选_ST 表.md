---
title: "[COTS 2016] 建造费 Pristojba"
layout: "post"
diff: 省选/NOI-
pid: P11307
tag: ['2016', '线段树', '生成树', '生成树的另类算法', '特殊生成树', 'ST 表', 'COCI（克罗地亚）']
---
# [COTS 2016] 建造费 Pristojba
## 题目背景

译自 [Izborne Pripreme 2016 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2016/) D2T2。$\texttt{5s,0.5G}$。

## 题目描述


有一张 $n$ 个点的简单无向图 $G$。

给定数列 $p$，边 $(i,j)$（$i\neq j$）的边权为 $p_i+p_j$。

然而，不是所有 $i,j$ 间都有边连接。给定 $m$ 个三元组形如 $x,l,r$，表示「$\forall l\le y\le r$，$x,y$ 间有边连接」。

求出这张无向图的[最小生成树](https://www.luogu.com.cn/user/398152)的边权和。

## 输入格式


第一行，两个正整数 $n,m$。

第二行，$n$ 个非负整数 $p_1,\cdots,p_n$。

接下来 $m$ 行，每行三个正整数 $x,l,r$。

**不保证三元组两两不同**，但保证 $x\not\in [l,r]$。

**输入数据保证有解。**
## 输出格式

输出一行一个整数，表示答案。

## 样例

### 样例输入 #1
```
4 4
2 4 1 0
1 2 3
1 3 4
3 1 1
4 1 2
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
6 8
3 5 8 2 9 4
3 1 2
6 3 3
3 1 1
6 2 2
2 3 6
3 1 2
3 2 2
4 1 1
```
### 样例输出 #2
```
46
```
### 样例输入 #3
```
12 10
9 2 7 5 5 9 3 6 5 7 8 8
6 3 3
9 1 1
6 10 11
1 3 11
5 6 12
3 5 5
12 3 7
6 1 4
4 6 6
10 4 6
```
### 样例输出 #3
```
126
```
## 提示



对于 $100\%$ 的数据，保证：
- $1\le n,m\le  10^5$；
- $0\le p_i\le 10^6$；
- $1\le x\le n$；
- $1\le l\le r\le n$，$x\not\in [l,r]$；
- 存在一组解。


| 子任务编号 | $n,m\le  $ |  得分 |  
| :--: | :--: | :--: | 
| $ 1 $    | $ 10^3$  |   $ 20 $   |  
| $ 2 $    | $ 10^5 $  | $ 80 $   |  



---

---
title: "无聊"
layout: "post"
diff: 省选/NOI-
pid: P11661
tag: ['莫队', 'O2优化', '分治', 'ST 表', '笛卡尔树', '根号分治']
---
# 无聊
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/f9kqwg7m.png)
## 题目描述

白很无聊呢，于是她给空出了道题。

给出 $n$ 个数的序列 $a,b$。

求 $b_l\equiv b_r\pmod {\displaystyle\max_{l\le i\le r}a_i}$ 的 $(l,r)$ 个数。
## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个整数表示 $a$ 序列。

第三行 $n$ 个整数表示 $b$ 序列。
## 输出格式

一个整数。
## 样例

### 样例输入 #1
```
10
5 5 7 8 6 7 2 1 7 2 
4 11 7 19 13 8 10 11 10 7 
```
### 样例输出 #1
```
15
```
## 提示

对于所有测试数据，保证：$1\le n,a_i,b_i\le 5\times10^5$。

| Subtask | $n\le$ | 限制 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $10^4$ | - | $5$ |
| $1$ | $10^5$ | $a_i\ge a_{i+1}$ | $15$ |
| $2$ | $10^5$ | - | $30$ |
| $3$ | $5\times10^5$ | - | $50$ |


---

---
title: "「TPOI-1D」谢谢您。"
layout: "post"
diff: 省选/NOI-
pid: P11750
tag: ['O2优化', '分块', 'ST 表']
---
# 「TPOI-1D」谢谢您。
## 题目背景

> もしも もう一度 あなたに会えるなら
>
> 如果 能够再次与您相遇
>
> たった一言伝えたい ありがとう ありがとう
>
> 我只想告诉您一句话 谢谢您 谢谢您
>
> —— KOKIA「[ありがとう…](https://www.bilibili.com/video/BV12W421X7MQ/)」 
## 题目描述

Misaka Mikoto 给你一个长度为 $n$ 的序列 $[a_1, \dots, a_n]$ 和 $m$ 个区间 $[l_1,r_1], \dots, [l_m,r_m]$。

Misaka Mikoto 有 $q$ 次询问 $L, R, k$，对于每一次询问，请你求出：

$$\max_{i=L}^R \sum_{j=l_i}^{r_i} [a_j = k]$$
## 输入格式

第一行包含三个正整数 $n, m, q$。

接下来一行，$n$ 个正整数 $a_1, \ldots, a_n$。

接下来 $m$ 行，第 $i$ 行包含两个正整数 $l_i, r_i$。

接下来 $q$ 行，每行有三个正整数 $L, R, k$，依次表示每次询问。
## 输出格式

输出共 $q$ 行。第 $i$ 行一个整数，表示第 $i$ 次询问的答案。
## 样例

### 样例输入 #1
```
1 1 1
1
1 1
1 1 1

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
10 6 8
1 1 2 1 3 2 1 3 2 3
1 5
2 7
3 6
4 5
7 10
5 9
1 3 3
2 4 1
5 6 1
2 2 2
4 6 3
2 5 2
1 3 1
3 5 4

```
### 样例输出 #2
```
1
3
1
2
2
2
3
0

```
### 样例输入 #3
```
15 15 15
11 14 1 5 5 5 5 4 10 2 5 1 4 5 4
10 14
2 7
7 12
6 10
4 5
5 11
3 15
3 7
3 8
1 6
8 11
14 14
5 8
8 12
4 5
8 15 2
12 13 5
8 12 5
7 12 11
7 12 10
2 11 11
10 10 10
5 13 11
11 14 11
2 4 4
13 14 1
4 8 11
7 12 5
3 5 11
10 15 11

```
### 样例输出 #3
```
1
3
4
1
1
1
0
1
0
1
1
0
6
0
1

```
### 样例输入 #4
```
20 20 20
12 1 20 1 1 11 11 1 11 12 11 17 12 1 11 12 20 12 17 17
4 7
6 7
10 20
17 19
2 4
6 6
17 19
10 12
14 15
12 13
7 19
8 16
8 11
4 6
16 18
3 8
16 20
4 5
7 10
6 19
6 8 20
2 6 12
1 3 17
4 5 12
13 14 12
2 8 11
7 11 12
3 4 20
12 15 20
19 19 1
4 4 1
1 8 1
7 15 20
2 8 17
8 16 12
4 12 1
12 17 1
4 9 11
2 7 1
1 15 17

```
### 样例输出 #4
```
1
4
3
1
1
2
4
1
1
1
0
2
1
3
4
2
3
1
2
3

```
## 提示

**本题采用捆绑测试。**

- Subtask 1（5 分）：$n,m,q\le 500$。
- Subtask 2（5 分）：$n,m,q\le 5000$。
- Subtask 3（5 分）：序列 $a$ 中至多有 $100$ 种元素。
- Subtask 4（5 分）：序列 $a$ 中每种元素至多出现 $10$ 次。
- Subtask 5（20 分）：$n,m,q\le 5\times 10^4$。
- Subtask 6（20 分）：$n,m,q\le 10^5$。
- Subtask 7（40 分）：无特殊限制。

对于 $100\%$ 数据，$1\le n,m,q\le 2\times 10^5$，$1\le a_i,k\le n$，$1\le l_i\le r_i\le n$，$1\le L\le R\le m$。


---

---
title: "[NAC 2025] Humans vs AI"
layout: "post"
diff: 省选/NOI-
pid: P12624
tag: ['线段树', '树状数组', '2025', '分治', 'ST 表', 'ICPC', 'NAC']
---
# [NAC 2025] Humans vs AI
## 题目描述

In the world of rising AI, James is scared of losing his job. So, when his boss asks him to evaluate a new AI model to see how well it performs compared to humans, he wants to make it look as bad as possible.

To test the AI, James conducts a sequence of $N$ trials where a human and an AI are
given the same task and then scored based on their performance on the task. 
He is then going to send the results of some non-empty contiguous subsequence of these trials to his boss and quietly delete the rest.

Let $a_i$ and $h_i$ be the performance of the AI and human on trial $i$, respectively. James's boss evaluates the AI on a sequence of trials by calculating two total scores: one for the humans, and one for the AI. Both scores are initially $0$. For each trial $i$ where $h_i \geq a_i$, the boss awards the humans $h_i-a_i$ points. For each trial where $h_i < a_i$, the AI earns $a_i-h_i$ points.
If the humans' total score is greater than or equal to the AI's total score times some constant $k$ (to account for humans needing food, water, and a desk), James's boss declares that the humans outperform the AI.

James plans to send his chosen subsequence of test results through email to his boss. There is, however, one complication: since AI is already all-knowing and all-pervasive, it intercepts this email and may swap the value of $h_i$ and $a_i$ for one trial $i$ of its choice. (It doesn't want to swap more than one trial result---James might notice!)

Count how many non-empty contiguous subsequences of trial results James could send his boss with the guarantee that humans will be declared to outperform the AI, even if the AI swaps the result of up to one trial.
## 输入格式

The first line of input contains two space-separate integers: $N$ ($1 \leq N \leq 2 \cdot 10^5$), the total number of trials James conducted, and $k$ ($1 \leq k \leq 100$), the multiplier James's boss will apply to the AI's total score to determine whether humans outperform AI.

The second line contains $N$ space-separated integers $h_1, h_2, \ldots, h_N$ ($0 \leq h_i \leq 10^6$), the performance of the humans on each of the $N$ trials.

The third line contains $N$ space-separated integers $a_1, a_2, \ldots, a_N$ ($0 \leq a_i \leq 10^6$), the performance of the AI on the $N$ trials.
## 输出格式

Print the number of non-empty contiguous trial subsequences for which James's boss would declare that humans outperform AI, even if the AI swaps the result of up to one trial.
## 样例

### 样例输入 #1
```
10 2
3 5 7 6 8 6 4 5 2 6
2 4 6 5 4 3 3 6 3 4
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
7 1
4 3 2 1 7 6 5
4 2 3 1 7 6 5
```
### 样例输出 #2
```
11
```


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
title: "[NOI2010] 超级钢琴"
layout: "post"
diff: 省选/NOI-
pid: P2048
tag: ['贪心', '2010', '堆', 'NOI', 'O2优化', '前缀和', 'ST 表']
---
# [NOI2010] 超级钢琴
## 题目描述

小 Z 是一个小有名气的钢琴家，最近 C 博士送给了小 Z 一架超级钢琴，小 Z 希望能够用这架钢琴创作出世界上最美妙的音乐。

这架超级钢琴可以弹奏出 $n$ 个音符，编号为 $1$ 至 $n$。第 $i$ 个音符的美妙度为 $A_i$，其中 $A_i$ 可正可负。

一个“超级和弦”由若干个编号连续的音符组成，包含的音符个数不少于 $L$ 且不多于 $R$。我们定义超级和弦的美妙度为其包含的所有音符的美妙度之和。两个超级和弦被认为是相同的，当且仅当这两个超级和弦所包含的音符集合是相同的。

小 Z 决定创作一首由 $k$ 个超级和弦组成的乐曲，为了使得乐曲更加动听，小 Z 要求该乐曲由 $k$ 个不同的超级和弦组成。我们定义一首乐曲的美妙度为其所包含的所有超级和弦的美妙度之和。小 Z 想知道他能够创作出来的乐曲美妙度最大值是多少。
## 输入格式

输入第一行包含四个正整数 $n, k, L, R$。其中 $n$ 为音符的个数，$k$ 为乐曲所包含的超级和弦个数，$L$ 和 $R$ 分别是超级和弦所包含音符个数的下限和上限。

接下来 $n$ 行，每行包含一个整数 $A_i$，表示按编号从小到大每个音符的美妙度。
## 输出格式

输出只有一个整数，表示乐曲美妙度的最大值。

## 样例

### 样例输入 #1
```
4 3 2 3
3
2
-6
8
```
### 样例输出 #1
```
11
```
## 提示

### 样例解释

共有 $5$ 种不同的超级和弦：

1. 音符 $1 \sim 2$，美妙度为 $3+2=5$；
2. 音符 $2 \sim 3$，美妙度为 $2+(-6)=-4$；
3. 音符 $3 \sim 4$，美妙度为 $(-6)+8=2$；
4. 音符 $1 \sim 3$，美妙度为 $3+2+(-6)=-1$；
5. 音符 $2 \sim 4$，美妙度为 $2+(-6)+8=4$。

最优方案为：乐曲由和弦 $1,3,5$ 组成，美妙度为 $5+2+4=11$。

 ![](https://cdn.luogu.com.cn/upload/pic/2609.png) 

所有数据满足：$-1000 \leq A_i \leq 1000$，$1 \leq L \leq R \leq n$ 且保证一定存在满足要求的乐曲。



---

---
title: "[HNOI2016] 序列"
layout: "post"
diff: 省选/NOI-
pid: P3246
tag: ['2016', '各省省选', '湖南', '前缀和', '栈', 'ST 表']
---
# [HNOI2016] 序列
## 题目描述

给定长度为 $ n $ 的序列：$ a_1, a_2, \cdots , a_n $，记为 $ a[1 \colon n] $。类似地，$ a[l \colon r] $（$ 1 \leq l \leq r \leq N$）是指序列：$ a_{l}, a_{l+1}, \cdots ,a_{r-1}, a_r$。若 $1\leq l \leq s \leq t \leq r \leq n$，则称 $ a[s \colon t] $ 是 $ a[l \colon r] $ 的子序列。

现在有 $ q $ 个询问，每个询问给定两个数 $ l $ 和 $ r $，$ 1 \leq l \leq r \leq n $，求 $ a[l \colon r] $ 的不同子序列的最小值之和。例如，给定序列
 $ 5, 2, 4, 1, 3 $，询问给定的两个数为 $ 1 $ 和 $ 3 $，那么 $ a[1 \colon 3] $ 有 $ 6 $ 个子序列 $a[1 \colon 1], a[2 \colon 2], a[3 \colon 3], a[1 \colon 2],a[2 \colon 3], a[1 \colon 3] $，这 $6 $ 个子序列的最小值之和为 $5+2+4+2+2+2=17$。
## 输入格式

输入文件的第一行包含两个整数 $ n $ 和 $ q $，分别代表序列长度和询问数。

接下来一行，包含 $ n $ 个整数，以空格隔开，第 $ i $ 个整数为 $ a_i $，即序列第 $i$ 个元素的值。

接下来 $ q $ 行，每行包含两个整数 $ l $ 和 $ r $，代表一次询问。
## 输出格式

对于每次询问，输出一行，代表询问的答案。

## 样例

### 样例输入 #1
```
5 5
5 2 4 1 3
1 5
1 3
2 4
3 5
2 5
```
### 样例输出 #1
```
28 
17 
11 
11 
17
```
## 提示

对于 $100\%$ 的数据，$ 1 \leq n,q \leq 100000$，$|a_i| \leq 10^9$。


---

---
title: "[SCOI2016] 萌萌哒"
layout: "post"
diff: 省选/NOI-
pid: P3295
tag: ['2016', '四川', '并查集', '枚举', 'ST 表']
---
# [SCOI2016] 萌萌哒
## 题目描述

一个长度为 $n$ 的大数，用 $S_1S_2S_3 \cdots S_n$表示，其中 $S_i$ 表示数的第 $i$ 位, $S_1$ 是数的最高位。告诉你一些限制条件，每个条件表示为四个数，$l_1,r_1,l_2,r_2$，即两个长度相同的区间，表示子串 $S_{l_1}S_{l_1+1}S_{l_1+2} \cdots S_{r_1}$ 与 $S_{l_2}S_{l_2+1}S_{l_2+2} \cdots S_{r_2}$ 完全相同。

比如 $n=6$ 时，某限制条件 $l_1=1,r_1=3,l_2=4,r_2=6$ ，那么 $123123$，$351351$ 均满足条件，但是 $12012$，$131141$ 不满足条件，前者数的长度不为 $6$ ，后者第二位与第五位不同。问满足以上所有条件的数有多少个。
## 输入格式

第一行两个数 $n$ 和 $m$，分别表示大数的长度，以及限制条件的个数。

接下来 $m$ 行，对于第 $i$ 行,有 $4$ 个数 $l_{i_1},r_{i_1},{l_{i_2}},r_{i_2}$，分别表示该限制条件对应的两个区间。

$1\le n\le 10^5$，$1\le m\le 10^5$，$1\le l_{i_1},r_{i_1},{l_{i_2}},r_{i_2}\le n$ ；并且保证 $ r_{i_1}-l_{i_1}=r_{i_2}-l_{i_2}$ 。

## 输出格式

一个数，表示满足所有条件且长度为 $n$ 的大数的个数，答案可能很大，因此输出答案模 $ 10^9+7 $ 的结果即可。

## 样例

### 样例输入 #1
```
4 2
1 2 3 4
3 3 3 3
```
### 样例输出 #1
```
90
```


---

---
title: "[ZJOI2018] 胖"
layout: "post"
diff: 省选/NOI-
pid: P4501
tag: ['2018', '线段树', '二分', '各省省选', '浙江', 'ST 表']
---
# [ZJOI2018] 胖
## 题目背景

Cedyks 是九条可怜的好朋友（可能这场比赛公开以后就不是了），也是这题的主人公。
## 题目描述

Cedyks 是一个富有的男孩子。他住在著名的 The Place（宫殿）中。

Cedyks 是一个努力的男孩子。他每天都做着不一样的题来锻炼他的 The Salt（灵魂）。

这天，他打算在他的宫殿外围修筑一道城墙，城墙上有 $n$ 座瞭望塔。你可以把城墙看做一条线段，瞭望塔是线段上的 $n$ 个点，其中 $1$ 和 $n$ 分别为城墙的两个端点。其中第 $i$ 座瞭望塔和第 $i + 1$ 座瞭望塔的距离为 $w_i$，他们之间的道路是双向的。

城墙很快就修建好了，现在 Cedyks 开始计划修筑他的宫殿到城墙的道路。因为这题的题目名称，Cedyks 打算用他的宫殿到每一个瞭望塔的最短道路之和来衡量一个修建计划。

现在 Cedyks 手上有 $m$ 个设计方案，第 $k$ 个设计方案会在宫殿和瞭望塔之间修建 $T_k$ 条双向道路，第 $i$ 条道路连接着瞭望塔 $a_i$，长度为 $l_i$。

计算到每一个瞭望塔的最短路之和是一个繁重的工程，本来 Cedyks 想用广为流传的 SPFA 算法来求解，但是因为他的 butter（缓冲区）实在是太小了，他只能转而用原始的贝尔福特曼算法来计算，算法的流程大概如下：

1. 定义宫殿是 $0$ 号点，第 $i$ 个瞭望塔是 $i$ 号点，双向边 $(u_i, v_i, l_i)$ 为一条连接 $u_i$ 和 $v_i$ 的双向道路。令 $d$ 为距离数组，最开始 $d_0 = 0, d_i = 10^{18}(i ∈ [1, n])$。
2. 令辅助数组 $c = d$。依次对于每一条边 $(u_i, v_i,w_i)$ 进行增广，$c_{u_i} = \min(c_{u_i} , d_{v_i} + w_i)$，$c_{v_i} = \min(c_{v_i} , d_{u_i} + w_i)$。
3. 令 $t$ 为 $c$ 和 $d$ 中不一样的位置个数，即令 $S = \{i|c_i≠d_i\}$，则 $t = |S|$。若 $t = 0$，说明 $d$ 就是最终的最短路，算法结束。否则令 $d = c$，回到第二步。

因为需要计算的设计方案实在是太多了，所以 Cedyks 雇佣了一些人来帮他进行计算。为了避免这些人用捏造出来的数据偷懒，他定义一个设计方案的校验值为在这个方案上运行贝尔福特曼算法每一次进入第三步 $t$ 的和。他会让好几个雇佣来的人计算同样的设计方案，并比对每一个人给出的校验值。

你是 Cedyks 雇佣来的苦力之一，聪明的你发现在这个情形下计算最短路的长度的和是一件非常简单的事情。但是寄人篱下不得不低头，你不得不再计算出每一个方案的校验值来交差。
## 输入格式

第一行输入两个整数 $n,m$，表示瞭望塔个数和设计方案个数。

接下来一行 $n - 1$ 个数 $w_i$，表示瞭望塔 $i$ 和 $i + 1$ 之间道路的长度。

接下来 $m$ 行，每行描述一个设计方案。第一个整数 $K$ 表示设计方案中的道路数量，接下来 $K$ 个数对 $(a_i, l_i)$ 为一条宫殿到瞭望塔的边。
## 输出格式

对于每一个设计方案，输出一行一个整数表示校验值。
## 样例

### 样例输入 #1
```
5 5
2 3 1 4
1 2 2
2 1 1 4 10
3 1 1 3 1 5 1
3 1 10 2 100 5 1
5 1 1 2 1 3 1 4 1 5 1
```
### 样例输出 #1
```
5
8
5
8
5
```
## 提示

### 样例解释

对于第一个设计方案，每一个阶段 $d$ 的变化为：

- $[0,10^{18},10^{18},10^{18},10^{18},10^{18}] \rightarrow [0,10^{18},2,10^{18},10^{18},10^{18}] \rightarrow$ $[0,4,2,5,10^{18},10^{18}] \rightarrow [0,4,2,5,6,10^{18}] \rightarrow [0,4,2,5,6,10]$。

因此校验值为 $1+2+1+1=5$。

对于第二个设计方案，每一个阶段 $d$ 的变化为：

- $[0,10^{18},10^{18},10^{18},10^{18},10^{18}] \rightarrow [0,1,10^{18},10^{18},10,10^{18}] \rightarrow$ $[0,1,3,11,10,14] \rightarrow [0,1,3,6,10,14] \rightarrow [0,1,3,6,7,14] \rightarrow [0,1,3,6,7,11]$。

因此校验值为 $2+3+1+1+1=8$。

对于第三个设计方案，每一个阶段 $d$ 的变化为：

- $[0,10^{18},10^{18},10^{18},10^{18},10^{18}] \rightarrow [0,1,10^{18},1,10^{18},1] \rightarrow [0,1,3,1,2,1]$。

因此校验值为 $3+1+1=5$。

对于第四个设计方案，每一个阶段 $d$ 的变化为：

- $[0,10^{18},10^{18},10^{18},10^{18},10^{18}] \rightarrow [0,10,100,10^{18},10^{18},1] \rightarrow$ $[0,10,12,103,5,1] \rightarrow [0,10,12,6,5,1] \rightarrow [0,10,9,5,1]$。

因此校验值为 $3+3+1+1=8$。

对于第五个设计方案，每一个阶段 $d$ 的变化为：

- $[0,10^{18},10^{18},10^{18},10^{18},10^{18}] \rightarrow [0,1,1,1,1,1]$

因此校验值为 $5$。

### 数据范围

测试点|$n$|$m$|$K$|其他约定
-|-|-|-|-
1,2|$\le 1000$|$\le 1000$|$\le 100$|无
3,4|$\le 2 \times 10^5$|$\le 2 \times 10^5$|$\le 100$|无
5,6|$\le 2 \times 10^5$|$\le 2 \times 10^5$|$\le 2 \times 10^5$|$1 \le w_i,l_i \le 50$
7,8,9,10|$\le 2 \times 10^5$|$\le 2 \times 10^5$|$\le 2 \times 10^5$|无


对于 $100\%$ 的数据，保证每个设计方案 $a_i$ 两两不同且 $1\le a_i\le n$。  
对于 $100\%$ 的数据，保证 $1\le w_i,l_i\le 10^9,1\le\sum K\le 2\times 10^5$。

感谢 @Xeonacid 提供题面


---

---
title: "【XR-1】逛森林"
layout: "post"
diff: 省选/NOI-
pid: P5344
tag: ['倍增', '洛谷原创', 'O2优化', '最短路', '最近公共祖先 LCA', 'ST 表']
---
# 【XR-1】逛森林
## 题目背景

NaCly_Fish 和 PinkRabbit 是好朋友。

有一天她去森林里游玩，回去跟 PinkRabbit 说：“我发现好多棵会动的树耶！”

PinkRabbit 动了动一只兔耳朵：“这有什么好稀奇的，我用一只兔耳朵就能维护每棵树的形态。”

NaCly_Fish 不服：“不止这样，我还看到有一些传送门，能从一条树枝跳到另一条树枝上呢！”

PinkRabbit 动了动另一只兔耳朵：“这有什么好稀奇的，我用两只兔耳朵就能统计每个传送门的信息。”

![](https://cdn.luogu.com.cn/upload/pic/57782.png)

于是 NaCly_Fish 很郁闷，她向你求助，请帮帮她吧。

什么？你不愿意帮？

那她就不给你这题的分了。
## 题目描述

给你 $n$ 个节点的森林，初始没有边。

有 $m$ 个操作，分为两种：

$1\ u_1\ v_1\ u_2\ v_2\ w$：表示构建一个单向传送门，从 $u_1 \rightarrow v_1$ 简单路径上的所有节点，可以花费 $w$ 的代价，到达 $u_2 \rightarrow v_2$ 简单路径上的所有节点。若 $u_1$ 到 $v_1$ 或 $u_2$ 到 $v_2$ 不连通(由 $2$ 操作产生的边不连通)，则忽略此次操作。

$2\ u\ v\ w$：表示将 $u$ 和 $v$ 节点间连一条花费为 $w$ 的无向边，若 $u$ 和 $v$ 之间已连通(由 $2$ 操作产生的边连通)则忽略此次操作。

经过这 $m$ 次操作后，请你求出从 $s$ 节点出发，到每个节点的最小花费。
## 输入格式

第一行三个正整数 $n, m, s$，分别表示树的节点数、操作数、和起始节点。

接下来 $m$ 行，每行若干个正整数，表示一次操作。
## 输出格式

输出一行 $n$ 个整数，第 $i$ 个整数表示从 $s$ 节点出发，到 $i$ 节点的最小花费。特别地，若不能到达$i$节点，则输出 `-1`。
## 样例

### 样例输入 #1
```
9 11 5
2 2 1 2
2 3 1 5
2 4 2 10
2 5 3 9
2 6 5 3
2 7 6 6
2 8 7 2
2 9 4 2
1 1 1 4 9 2
1 8 5 1 6 1
1 3 6 9 6 1
```
### 样例输出 #1
```
1 1 1 1 0 1 7 9 1
```
## 提示

【样例说明】

这是样例中给出的树（严格来讲，这棵树也是一条链）：

![](https://cdn.luogu.com.cn/upload/image_hosting/g1kmzdbv.png)

有三个传送门，其中两个是这样的：

- 从 $1$ 号点可以花费 $2$ 的代价到达 $4 \rightarrow 9$ 简单路径上的所有节点（即 $4, 9$ 号点）。
- 从 $8 \rightarrow 5$ 简单路径上的所有节点（即 $8, 7, 6, 5$ 号点）可以花费 $1$ 的代价到达 $1 \rightarrow 6$ 简单路径上的所有节点（即 $1, 3, 5, 6$ 号点）。

容易看出从 $5$ 号节点出发，到达其它节点的最小花费分别为：$1, 1, 1, 1, 0, 1, 7, 9, 1$。

【数据规模与约定】

对于第 $1, 2$ 个测试点，$1 \le n \le 100$，$1 \le m \le 300$。

对于第 $3, 4$ 个测试点，$1 \le n \le 1000$，$1 \le m \le 3000$。

对于 $100\%$ 的数据，$1\le n \le 50000$，$1\le m \le 10^6$，$1\le u,v \le n$，$1\le w \le 100$。

对于第 $1$ ~ $10$ 个测试点，每个 $5$ 分。

对于第 $11, 12$ 个测试点，每个 $25$ 分。


---

---
title: "「ACOI2020」惊吓路径"
layout: "post"
diff: 省选/NOI-
pid: P6038
tag: ['2020', '线段树', '倍增', '二分', 'O2优化', 'ST 表']
---
# 「ACOI2020」惊吓路径
## 题目背景

![T6](https://s2.ax1x.com/2020/01/12/lopZpq.png)

3 年 E 班的同学们赢得了去南方的冲绳小岛的机会，在渚打败了鹰冈之后，他们受杀老师的邀请参加“试胆大会”。

试胆大会在一个黑漆漆的洞窟里面进行。赤羽 業（Akabane Karma）现在和奧田 愛美站在洞窟的门口。突然，業想到了一个事情。。。
## 题目描述

杀老师告诉过他们，洞窟可以近似地看成 $n$ 个点的外向树，因为地形原因，所以一个点到另一个点的边是有方向的，且边的方向都是同向的。这棵树的树根为入度为 $0$ 的点。每个点都有一个惊吓值，给出每个点的惊吓值 $a_i$。

杀老师告诉他们，这个洞穴有很多惊吓路径。如果两个节点 $u,v$ 构成的路径是一条惊吓路径的话，满足以下条件：

- $v$ 一定在 $u$ 的子树中。

- $u, v$ 这条路径上的所有的点的惊吓值的或值 $\geq k$。

走过一条惊吓路径就会收到杀老师的惊喜大礼。杀老师已经提前准备好了惊喜大礼，但是業当然已经知道杀老师有一些下流的意图，更别说惊喜大礼的数量可能不够！杀老师已经承诺有多少条惊吓路径就有多少个惊喜大礼。業已经通过一些神奇的途径知道了杀老师准备的惊喜大礼的个数，现在他想知道有多少条惊吓路径，也就是杀老师最少需要准备惊喜大礼的个数。如果不够，他就会揭穿杀老师的意图。现在業当然想赚，好好捉弄一下杀老师。所以他~~作弊~~提前得到了杀老师的地图，想问这个图里面有多少条惊吓路径？
## 输入格式

第一行两个整数 $n,k$。

第二行 $n$ 个整数，表示每个点的惊吓值。

接下来 $n-1$ 行，每行有两个整数 $u,v$ 表示节点 $u,v$ 之间有一条有向边，节点 $u$ 可以到达节点 $v$，**节点 $v$ 不可以到达节点 $u$**。




## 输出格式

一行一个整数，表示这个洞穴的惊吓路径条数。
## 样例

### 样例输入 #1
```
5 10
5 9 6 4 2
3 1
3 4
1 2
1 5

```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
7 5
6 7 4 5 7 8 9
1 2
2 3
2 4
1 5
5 6
5 7

```
### 样例输出 #2
```
16
```
### 样例输入 #3
```
8 5
4 3 2 5 6 7 6 2
1 2
1 5
2 3
2 4
5 6
5 7
6 8

```
### 样例输出 #3
```
16
```
## 提示

#### 样例解释 #1

![](https://cdn.luogu.com.cn/upload/image_hosting/lqu4ejku.png)

只有两条路径满足条件：

1. $3\to 1\to 2$，这条路径的所有点的惊吓值的或值是 $6\operatorname{or}5\operatorname{or}9=15$。

2. $1 \to 2$，这条路径的所有点的惊吓值的或值是 $5\operatorname{or}9=13$。

------------
#### 数据范围 
**本题采用捆绑测试**。

- Subtask 1（10 points）：$n \leq 5 \times 10^3$，$k \leq 10^5$。    
- Subtask 2（30 points）：对于任意一条边，$v=u+1$，$n \leq 10^6$，$k,a_i \leq 10^9$。     
- Subtask 3（20 points）：$n \leq 10^5$，$k,a_i \leq 10^9$。    
- Subtask 4（40 points）：$n \leq 5 \times 10^5$，$k,a_i \leq 10^9$。

对于 $100\%$ 的数据，$1 \leq n \leq 10^6$，$1 \leq k,a_i \leq 10^9$。

------------
#### 提示
**第四个子任务中的测试点空间 256MB，其余子任务中的测试点空间 128MB。**


---

---
title: "[JRKSJ R2] 你的名字。"
layout: "post"
diff: 省选/NOI-
pid: P7811
tag: ['2021', '洛谷原创', 'O2优化', '分治', '分块', 'ST 表']
---
# [JRKSJ R2] 你的名字。
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/73iq08qk.png)
## 题目描述

给你一个长为 $n$ 的序列 $a$，有 $m$ 次查询，每次查询区间 $[l,r]$ 模 $k$ 意义下的最小值。
## 输入格式

第一行两个整数 $n,m$。

第二行 $n$ 个整数表示 $a$。

下面 $m$ 行，每行三个整数 $l,r,k$ 表示一次询问。
## 输出格式

对于每个查询操作，每行输出一个答案。
## 样例

### 样例输入 #1
```
10 10
15 14 14 4 8 10 18 14 10 9 
2 10 8
2 4 7
3 9 6
1 7 5
3 4 6
6 6 12
4 8 20
1 6 18
7 8 8
2 6 6
```
### 样例输出 #1
```
0
0
0
0
2
10
4
4
2
2
```
### 样例输入 #2
```
5 5
77 24 80 90 92 
2 3 84
4 5 37
1 1 4
3 5 85
1 4 46
```
### 样例输出 #2
```
24
16
1
5
24
```
## 提示

Idea：mcyl35，Solution：mcyl35，Code：mcyl35，Data：cyffff&mcyl35

本题采用捆绑测试。

| $\text{Subtask}$ | $n,m\le$ | $k,a_i\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $\text{1}$ | $10^4$ | $10^5$ | 无 | $3$ | $1$ |
| $\text{2}$ | $10^5$ | $300$ | 无 | $6$ | $1$ |
| $\text{3}$ | $10^5$ | $10^5$ | $k\ge 10^3$ | $10$ | $1\to2$ |
| $\text{4}$ | $10^5$ | $10^5$ | 无 | $19$ |$2\to4$ |
| $\text{5}$ | $3\times10^5$ | $10^5$ | 数据随机 | $14$ |$1$ |
| $\text{6}$ | $3\times10^5$ | $10^5$ | $k\ge 10^3$ | $2$ |$2\to3$ |
| $\text{7}$ | $3\times10^5$ | $10^5$ | 无 | $46$ |$2\to5$ |

对于 $100\%$ 的数据，$1\le n,m\le3\times10^5$，$1\le a_i,k\le 10^5$。

前 $6$ 个 $\text{Subtask}$ 的空间限制为 $256\text{MB}$，第 $7$ 个 $\text{Subtask}$ 的空间限制为 $128\text{MB}$。


---

---
title: "[POI 2020/2021 R3] Kolekcjoner Bajtemonów 2"
layout: "post"
diff: 省选/NOI-
pid: P9401
tag: ['数学', '2020', 'POI（波兰）', 'ST 表']
---
# [POI 2020/2021 R3] Kolekcjoner Bajtemonów 2
## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Kolekcjoner Bajtemonów 2](https://szkopul.edu.pl/problemset/problem/yI8VISW680r7ktJAPvA5QPkl/statement/)。

试机题。
## 题目描述

给你 $n$ 个数对，你要进行 $n$ 次二选一，这样你就有了 $n$ 个数，最大化这 $n$ 个数的 $\gcd$。
## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行，每行两个整数，$a_i,b_i$。
## 输出格式

一行一个数：最大的 $\gcd$。
## 样例

### 样例输入 #1
```
4
5 7
10 15
13 20
7 5

```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
2
18900 22050
14700 17640

```
### 样例输出 #2
```
7350
```
### 样例输入 #3
```
见附件
```
### 样例输出 #3
```
2
```
## 提示

对于所有数据，$1\leq n\leq 10^6$，$1\leq a_i\leq 5\times 10^5$，$1\leq b_i<2^{63}$。

对于 $42pts$ 的数据，$n\leq 5000$。


---

---
title: "[CERC2019] Be Geeks!"
layout: "post"
diff: 省选/NOI-
pid: P9607
tag: ['2019', '线段树', '倍增', 'ST 表', 'ICPC', '笛卡尔树', '单调栈']
---
# [CERC2019] Be Geeks!
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Be Geeks!](https://contest.felk.cvut.cz/19cerc/solved/begeeks.pdf)」**
## 题目描述

音乐乐队 Be Geeks! 的名字并非偶然，因为所有成员都是真正的数学怪才。除此之外，他们喜欢研究数列的各种性质。下面是他们感兴趣的一个例子：
- 设 $A$ 是一个非空正整数序列，$A=(a_1, a_2, \dots, a_N)$。
- $G(i, j)=\gcd (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $M(i, j)=\max (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $P(i, j)=G(i, j)\times M(i, j)$，其中 $1\le i\le j\le N$。
- $F(A)=\sum P(i, j)[1\le i\le j\le N]$。

给出一个序列 $A$，你需要求出 $F(A)\bmod 1\,000\,000\,007$ 的值。
## 输入格式

第一行包含一个整数 $N\ (1\le N\le 2\times 10^5)$，代表序列 $A$ 的长度。

第二行包含 $N$ 个整数 $a_1, a_2, \dots, a_N\ (1\le a_i\le 10^9)$，代表序列 $A$。
## 输出格式

输出一个整数，代表 $F(A)\bmod 1\,000\,000\,007$ 的值。
## 样例

### 样例输入 #1
```
4
1 2 3 4

```
### 样例输出 #1
```
50

```
### 样例输入 #2
```
5
2 4 6 12 3

```
### 样例输出 #2
```
457

```


---

