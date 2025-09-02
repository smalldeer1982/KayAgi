---
title: "理性（Rationality）"
layout: "post"
diff: 省选/NOI-
pid: P10323
tag: ['数学', '洛谷原创', 'O2优化', '期望', '线性代数', '微积分', '洛谷比赛']
---
# 理性（Rationality）
## 题目背景

数学之善，统治宇宙的根本原理 —— 理性。
****
「理性之光」伊奥，是古代精灵图形术士。已经千岁的她总能不受感情的干扰，以理性做出最优的决策。   
## 题目描述

赛时更新：请注意，对于一组确定的 $v_1,\cdots,v_n$，都可以求出 $\text{RSS}$ 的最小值。**它是关于随机变量  $v_1,\cdots,v_n$ 的一个随机变量**，将其记为 $X$，则要求的是 $\mathbb E[X]$。   
笔误改正：残差平方和的英文为 $\text{RSS}$。
****
伊奥的思绪回到了千年前的一场大战中。

她记得那场战斗中有 $n$ 个敌人，第 $i$ 个敌人在距离她 $d_i$（$d_i$ 之间互不相同）的位置上。这些敌人都带有一个**正整数**标记 $v_i$，只要以**恰好** $v_i$ 的攻击力击中它就可以将其消灭。

她只要设定一个一次函数 $f(x)=ax+b$，就能在距离她 $d_i$ 的位置放出 $f(d_i)$ 的攻击力。好在她的队友会辅助她攻击，她只用考虑确定 $a,b$ 使得 $f(x)$ 的效果最优，即最小化 $\text{RSS}$（残差平方和）：
$$\text{RSS}=\sum_{i=1}^n(f(d_i)-v_i)^2$$
当然了，这只是她的回忆。她能清晰记得每个敌人到她的距离 $d_i$，而对于 $v_i$ 她只记得满足 $l_i\leq v_i \leq r_i$。

她想知道假设每个 $v_i$ 都对应在 $[l_i,r_i]$ 范围内**均匀随机**的情况下，「$\text{RSS}$ **的最小值」的期望**。   
可以证明答案总是有理数，你只需要告诉她答案对 $998244353$ 取模的结果即可。
## 输入格式

第一行一个正整数 $n$，表示敌人的个数。  
接下来 $n$ 行，每行三个正整数 $d_i,l_i,r_i$，分别表示第 $i$ 个敌人到伊奥的距离，其标记 $v_i$ 的下界和上界。

为了方便你的计算，伊奥保证 $d_i< d_{i+1}$（$1\leq i <n$），并且：

$$n\sum_{i=1}^nd_i^2 \not \equiv \left(\sum_{i=1}^nd_i \right)^2 \pmod{998244353}$$
**即确保答案在模 $998244353$ 意义下一定存在。**
## 输出格式

输出一行一个整数，表示所有情况下 $\text{RSS}$ 最小值的期望。
## 样例

### 样例输入 #1
```
3
1 4 4
3 7 7
5 10 10
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
5
1 4 4
2 5 5
3 7 7
4 8 8
9 8 8
```
### 样例输出 #2
```
488831003
```
### 样例输入 #3
```
5
1 1 4
2 2 5
3 3 7
4 2 8
9 3 8
```
### 样例输出 #3
```
884183796
```
### 样例输入 #4
```
10
123 1 10
234 11 14
345 10 20
456 6 6
567 20 30
678 84 90
789 1 3
8910 8 15
91011 123 129
101112 56 64
```
### 样例输出 #4
```
483360041
```
## 提示

【样例 $1$ 解释】

此样例中有 $l_i=r_i$，即情况已经确定，只需要求出此时最优的 $a,b$ 即可。容易发现 $(1,4),(3,7),(5,10)$ 这三组数据可以用一次函数完美拟合：即 $f(x)=\dfrac 32 x+\dfrac{5}{2}$，与每个点偏差都是 $0$，故 $\text{RSS}$ 最小值的期望，也就是答案为 $0$。

【样例 $2$ 解释】

这里同样有 $l_i=r_i$。$5$ 个敌人的数据 $(d_i,v_i)$ 分别为 $(1,4),(2,5),(3,7),(4,8),(9,8)$，可以证明取
$$a=\frac{87}{194} \ , \ b=\frac{911}{194}$$
是一组使得 $\text{RSS}$ 最小的解，代入计算得
$$\text{RSS}=\sum_{i=1}^n\left( \frac{87}{194}d_i+\frac{911}{194}-v_i\right)^2=\frac{1047}{194}$$
在模 $998244353$ 意义下答案为 $488831003$。

【数据范围】

**本题采用捆绑测试。**

Subtask 1（10 pts）：$n \leq 3$；  
Subtask 2（10 pts）：$l_i=r_i$；  
Subtask 3（15 pts）：$n\le500$，$r_i\leq 500$；  
Subtask 4（15 pts）：$n\le 5000$；  
Subtask 5（20 pts）：$n\le 10^5$；  
Subtask 6（30 pts）：无特殊限制。

对于全部的数据，$2\le n \le 5\times 10^5$，$1\leq l_i \leq r_i \leq 10^8$，$1\leq d_i \leq 10^8$， $d_i<d_{i+1}$（$1\leq i <n$），并且有：
$$n\sum_{i=1}^nd_i^2 \not \equiv \left(\sum_{i=1}^nd_i \right)^2 \pmod{998244353}$$

【提示】

题目中要求出「$\text{RSS}$ 的最小值」期望值。对于离散随机变量 $X$，假设其可以取值为 $a_1,a_2,\cdots,a_n$，对应概率为 $p_1,p_2,\cdots,p_n$（$p_1+\cdots+p_n=1$），则其期望值可以定义为：
$$\mathbb E[X]=\sum_{i=1}^np_i a_i$$
对于计算有理数取模的方法，请参考[模板题](https://www.luogu.com.cn/problem/P2613)。


---

---
title: "[HBCPC2024] Points on the Number Axis B"
layout: "post"
diff: 省选/NOI-
pid: P10868
tag: ['动态规划 DP', '数学', '2024', 'O2优化', '期望', 'XCPC', '湖北']
---
# [HBCPC2024] Points on the Number Axis B
## 题目描述

Bob is playing a single-player game on the number axis.

There are $n$ points on the number axis. Each time, the player selects two points. The two points will be removed, and their midpoint will be added. When there is only one point on the axis, the game ends. Formally, if the two chosen points is $x_i$ and $x_j$, then $\dfrac{x_i+x_j}{2}$ will be added after the operation.

In order to play this game happily, Bob will always select two adjacent points randomly. Initially, the $i$-th point and the $(i+1)$-th point are adjacent. When Bob added a new point, it inherits its left point's left adjacent point and its right point's right adjacent point.

Now Bob have a question: where is the expected position of the last point.

It can be proven that the answer can be expressed in the form $\dfrac{p}{q}$, you only need to output the value of $p\cdot q^{-1} \bmod 998\,244\,353$.
## 输入格式

The first line contains one integer $n$ ($1 \le n \le 10^6$).

The second line contains $n$ integers $x_i$ ($0 \le x_1 \le \dots \le x_n < 998\,244\,353$), describing the position of the $i$-th point.

Note that two points may be in the same position.
## 输出格式

Output one integer, the answer modulo $998\,244\,353$.
## 样例

### 样例输入 #1
```
3
1 2 4
```
### 样例输出 #1
```
623902723
```


---

---
title: "「KDOI-07」对树链剖分的爱"
layout: "post"
diff: 省选/NOI-
pid: P10879
tag: ['动态规划 DP', '数学', '图论', '2024', '洛谷原创', 'O2优化', '动态规划优化', '组合数学', '容斥原理', '期望']
---
# 「KDOI-07」对树链剖分的爱
## 题目背景

楼下说得对，但是 sszcdjr 在 NOI 2024 D2T2 用巧妙做法把我的暴力树剖爆掉了。

楼上说得对，但是树链剖分把我送上 10√ 了，所以我出了这道题以表示我对树链剖分的爱喵。
## 题目描述

给出一棵 $n$ 个节点以 $1$ 为根的有根树。对于第 $2\leq i\leq n$ 个节点，其父亲 $f_i$ 在 $[l_i,r_i]$ 中均匀随机。每个树的边有边权，初始为 $0$。

现在有 $m$ 次操作，第 $i$ 次操作表示将 $(u_i,v_i)$ 的路径上所有的边的权值统一加上 $w_i$。$m$ 次操作结束后，对于所有 $i=2\sim n$，求 $(i,f_i)$ 边上权值的期望，对 $998244353$ 取模。
## 输入格式

第一行一个正整数表示 $n$。

接下来 $n-1$ 行，其中第 $i$ 行两个正整数表示 $l_{i+1},r_{i+1}$。

接下来一行一个正整数表示 $m$。

接下来 $m$ 行，第 $i$ 行三个正整数表示 $u_i,v_i,w_i$。
## 输出格式

一行 $n-1$ 个正整数，其中第 $i$ 个表示边 $(i+1,f_{i+1})$ 边权的期望，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3
1 1
1 2
1
1 3 2
```
### 样例输出 #1
```
1 2
```
### 样例输入 #2
```
5
1 1
1 2
3 3
2 4
9
2 5 497855355
1 5 840823564
3 1 295265328
2 3 457999227
4 4 235621825
2 1 86836399
5 2 800390742
5 3 869167938
2 4 269250165
```
### 样例输出 #2
```
405260353 409046983 606499796 13504540
```
## 提示

### 样例解释 1

所有节点的父亲共有 $2$ 种可能的情况：

- $f_2=1,f_3=1$，此时 $(f_2,2),(f_3,3)$ 边上的权值分别是 $0,2$。

- $f_2=1,f_3=2$，此时 $(f_2,2),(f_3,3)$ 边上的权值分别是 $2,2$。

于是边 $(f_2,2)$ 边权的期望为 $\dfrac{0+2}{2}=1$，边 $(f_3,3)$ 边权的期望为 $\dfrac{2+2}{2}=2$。


---
### 数据规模与约定
**本题采用捆绑测试。**

| $\text{Subtask}$ | $n\leq$ | $m\leq$ | 分数 |
| :-----------: | :-----------: |  :-----------: | :-----------: |
| $1$ | $10$ | $10$ | $20$ |
| $2$ | $50$ | $50$ | $20$ |
| $3$ | $500$ | $500$ | $20$ |
| $4$ | $5000$ | $1$ | $20$ |
| $5$ | $5000$ | $5000$ | $20$|


对于所有数据，保证 $1\leq n,m\leq5000$，$1\leq l_i\leq r_i<i$，$1\leq u_i,v_i\leq n$，$1\leq w_i\leq 10^9$。


---

---
title: "[蓝桥杯 2024 国 Java A] 合并小球"
layout: "post"
diff: 省选/NOI-
pid: P12293
tag: ['动态规划 DP', '2024', '期望', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Java A] 合并小球
## 题目描述

给定 $n$ 个小球，其中第 $i$ 个小球位于数轴的 $x_i$ 处，小球上有数字 $y_i$。

每经过一秒，每个小球都有 $\frac{1}{2}$ 的概率向右移动一步。当任意小球到达位置 $T$ 时，小球会被立刻取走。

如果某一秒，有两个相邻的小球，左边的向右移动且右边的不动，那么两个小球会合并成一个，且合并后小球的数字为合并前的小球数字的乘积。

求所有小球都被取走时的数字之和的期望值，答案对 $998244353$ 取模。
## 输入格式

输入的第一行包含两个整数 $n, T$，用一个空格分隔。

接下来 $n$ 行，每行包含两个数 $x_i, y_i$，用一个空格分隔。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
3 5
2 1
3 1
4 1
```
### 样例输出 #1
```
406692146
```
## 提示

### 样例说明

$\frac{59}{27} \equiv 406692146 \pmod{998244353}$，其中 $\frac{1}{27} \equiv 480636170 \pmod{998244353}$。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$n \leq 5$，$T \leq 10$；
- 对于 $40\%$ 的评测用例，$n \leq 10$，$T \leq 20$；
- 对于所有评测用例，$1 \leq n < T \leq 100$，$1 \leq x_{i-1} < x_i < T$，$1 \leq y_i \leq 10^9$。


---

---
title: "[GCJ 2022 Qualification] Twisty Little Passages"
layout: "post"
diff: 省选/NOI-
pid: P12983
tag: ['2022', '交互题', 'Special Judge', '概率论', '期望', 'Google Code Jam']
---
# [GCJ 2022 Qualification] Twisty Little Passages
## 题目描述

You are investigating a cave. The cave has $\mathbf{N}$ rooms. There are underground passages that bidirectionally connect some pairs of rooms. Each room has at least one passage connected to it. No passage goes from a room to itself, and no two rooms are connected by more than one passage.

When in a room, you can identify what room you are in and see how many passages it connects to, but you cannot distinguish the passages. You want to estimate the number of passages that exist in the cave. You are allowed to do up to $\mathbf{K}$ operations. An operation is either:

* be magically teleported to a room of your choice, or
* walk through a random passage connected to the room you are in, taking you to the room at the other end of that passage.

When you decide to walk through a passage, you are unable to choose which one, because they are all alike. A passage is chosen for you uniformly at random.

You begin the investigation in an arbitrary room. Estimate the number of passages between rooms in the cave with at most $\mathbf{K}$ operations.

If $E$ is your estimate and $P$ is the actual number of passages, your solution is considered correct for a test case if and only if $P \cdot 2/3 \leq E \leq P \cdot 4/3$.

To pass a test set, your solution must be correct for at least 90% of the test cases in that set.

### Interactive Protocol

This is an interactive problem.

Initially, your program should read a single line containing an integer, $\mathbf{T}$, the number of test cases. Then, $\mathbf{T}$ test cases must be processed.

For each test case, your program must first read a line containing two integers $\mathbf{N}$ and $\mathbf{K}$: the number of rooms in the cave, and the maximum number of room operations you are allowed. Rooms are numbered between $1$ and $\mathbf{N}$. The cave is determined at the beginning of the test case – it won't be changed while you explore it. Then, your program must process up to $\mathbf{K} + 1$ exchanges.

The $i$-th exchange starts with you reading a line containing two integers $\mathbf{R}_i$ and $\mathbf{P}_i$, representing the number of the room you are currently in and the number of passages it connects to. Then, you must output a single line containing one of the following:

* A single uppercase $\mathbf{w}$: this means you want to walk through a random passage.
* A single uppercase $\mathbf{t}$ and an integer $S$: this means you want to teleport to room $S$.
* A single uppercase $\mathbf{e}$ and an integer $E$: this means you want to finish exploring and estimate that the cave contains $E$ passages.

After an estimation operation, the judge will immediately start the next test case if there is one, regardless of the correctness of your estimation. If there is no next test case, the judge will wait for you to finish without any further output.

If the judge receives an invalidly formatted line from your program at any moment, or if your $(\mathbf{K} + 1)$-th exchange for a test case is not an estimation operation, the judge will print a single number $-1$ and will not print any further output. If your program continues to wait for the judge after receiving a $-1$, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
1
5 3
4 1

5 2

4 1

1 3
```
### 样例输出 #1
```



T 5

W

T 1

E 5
```
## 提示

**Sample Explanation**

![](https://cdn.luogu.com.cn/upload/image_hosting/ve57bfoy.png)

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our interactive runner for that. For more information, read the instructions in comments in that file.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

**Test Set 1 (29 Pts, Visible Verdict)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{N} \leq 10^5$.
- $K = 8000$.
- Each room has at least one passage connected to it.


---

---
title: "[GCJ 2021 #1A] Hacked Exam"
layout: "post"
diff: 省选/NOI-
pid: P13028
tag: ['动态规划 DP', '2021', 'Special Judge', '组合数学', '期望', 'Google Code Jam']
---
# [GCJ 2021 #1A] Hacked Exam
## 题目描述

There is an exam with $\mathbf{Q}$ true or false questions. The correct answer to each question is either $\mathsf{T}$ or $\mathsf{F}$. Each student taking the exam selects either $\mathsf{T}$ or $\mathsf{F}$ for each question, and the student's score is the number of questions they answer correctly.

![](https://cdn.luogu.com.cn/upload/image_hosting/jwf5pdvs.png)

There are $\mathbf{N}$ students who have already taken this exam. For each of those students, you know the answers they gave to each question and their final score. Assuming that any sequence of answers that is consistent with all of those students' scores has the same probability of being the correct sequence of answers, you want to maximize your own expected score. Determine what that expected score is and how to answer the questions so that you achieve it.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. The first line of each test case contains two integers $\mathbf{N}$ and $\mathbf{Q}$: the number of students and the number of questions, respectively. Each of the next $\mathbf{N}$ lines contains a string $\mathbf{A}_i$ and an integer $\mathbf{S}_i$: the $i$-th student's answers and their score, respectively. The $j$-th character of $\mathbf{A}_i$ is either $\mathsf{T}$ or $\mathsf{F}$, representing the answer the $i$-th student gave to the $j$-th question.
## 输出格式

For each test case, output one line containing `Case #x: y z/w`, where $x$ is the test case number (starting from 1), $y$ is a string representing a sequence of answers that yields the maximum expected score (in the same format as the input), and $\frac{z}{w}$ is the maximum expected score as an irreducible fraction (that is, $w$ must be positive and of minimum possible value).
## 样例

### 样例输入 #1
```
4
1 3
FFT 3
1 3
FFT 2
2 6
FFTTTF 2
FTFTFT 4
2 2
FF 1
TT 1
```
### 样例输出 #1
```
Case #1: FFT 3/1
Case #2: FFT 2/1
Case #3: FTFFFT 4/1
Case #4: TF 1/1
```
### 样例输入 #2
```
1
3 120
FFTFFFTFFFTTTTTTTFTFFFFFFTTTFTFFFTFTFFTTFTFFTFFTTTFTFTFFTFTFTTFFFFTFTFFFFTTTFTTFTTTTFFFTTFFFFFTTFFTFFTFFTTTFFFFTTFFTFTTF 55
FFFTFFTTFFFFTFTFFTFFFTTTTTTFFFTTTFTTTTFFTFTTTFTTFFTTTFTFFFFTFFTTFFTTFTTFFTFTFFTFTTFTFTFFTTTFFTFTFTTFFTFTFTFTTFFTFFFTFTFT 62
FFFTFTTFFFFFTFTFTTTTTTFFTTFTFFFTFFTTTTTTFFFTTTFFFTTFTFFFFFFTFTTFFTFTTTFTTTTFTTFFFFTFFTTFTFFTTTTTTFTFFFFFTTFFTFTFTFFTTTTT 64
```
### 样例输出 #2
```
Case #1: FFFTFTTTFFFFTFTFFTFTTTTTTTFFFFTTTFTTTTFFTFTTTTTFFFTFTFTFFFFTFFTTFTFTFTTTTTFFTFFFFFFFFTTFTTTTTTFTTTTFFFFTFTFTTFTFFFFTTTFT 189154508532118369075350624633/2901503505434414233388602018
```
## 提示

**Sample Explanation**

In Sample Case #1, given that the score for $\mathsf{FFT}$ is 3, the sequence of correct answers must be $\mathsf{FFT}$.

In Sample Case #2, given that the score for $\mathsf{FFT}$ is 2, the sequence of correct answers is $\mathsf{FFF}$, $\mathsf{FTT}$, or $\mathsf{TFT}$, each with probability $\frac{1}{3}$. Your best strategy is to answer $\mathsf{FFT}$, to achieve the expected score of $\frac{1}{3} \times 2 + \frac{1}{3} \times 2 + \frac{1}{3} \times 2 = 2$.

In Sample Case #3, there are other answers that also achieve an expected score of 4, like $\mathsf{FTFTFT}$.

In Sample Case #4, one of the questions' answer is $\mathsf{T}$ and the other one is $\mathsf{F}$, but you do not know which is which. Answering $\mathsf{TF}$ or $\mathsf{FT}$ scores you 2 with probability $\frac{1}{2}$ and 0 with probability $\frac{1}{2}$, yielding an expected score of 1. Answering $\mathsf{FF}$ or $\mathsf{TT}$ guarantees a score of 1. Since any sequence of answers gives the same expected score, you can output any of them.

Sample 2 fits the limits of Test Set 3. It will not be run against your submitted solutions.

In the Sample Case for Test Set 3, you can get an expected score over 65, which is higher than the actual score of any of the other students. Notice that both the numerator and denominator of the expected score can be significantly larger than $2^{64}$ (the numerator in this case actually exceeds $2^{97}$).

**Limits**

- $1 \leq \mathbf{T} \leq 2021$.
- The length of $\mathbf{A}_{\mathbf{i}}=\mathbf{Q}$, for all $i$.
- Each character of $\mathbf{A}_{\mathbf{i}}$ is an uppercase $\mathsf{T}$ or an uppercase $\mathsf{F}$, for all $i$.
- $0 \leq \mathbf{S}_{\mathbf{i}} \leq \mathbf{Q}$, for all $i$.
- There exists at least one sequence of correct answers consistent with the input.

**Test Set 1 (8 Pts, Visible Verdict)**

- $1 \leq \mathbf{N} \leq 2$.
- $1 \leq \mathbf{Q} \leq 10$.

**Test Set 2 (6 Pts, Hidden Verdict)**

- $1 \leq \mathbf{N} \leq 2$.
- $1 \leq \mathbf{Q} \leq 40$.

**Test Set 3 (25 Pts, Hidden Verdict)**

- $1 \leq \mathbf{N} \leq 3$.
- $1 \leq \mathbf{Q} \leq 120$.


---

---
title: "[GCJ 2013 #3] Observation Wheel"
layout: "post"
diff: 省选/NOI-
pid: P13301
tag: ['动态规划 DP', '2013', 'Special Judge', '区间 DP', '概率论', '期望', 'Google Code Jam']
---
# [GCJ 2013 #3] Observation Wheel
## 题目描述

An observation wheel consists of $N$ passenger gondolas arranged in a circle, which is slowly rotating. Gondolas pass the entrance one by one, and when a gondola passes the entrance, a person may enter that gondola.

In this problem, the gondolas are so small that they can take just one person each, so if the gondola passing by the entrance is already occupied, the person waiting at the entrance will have to wait for the next one to arrive. If that gondola is also occupied, the person will have to wait for the next one after that, and so on, until a free gondola arrives. For simplicity, we will not consider people exiting the gondolas in this problem — let's assume that all people do is enter the gondolas, and then rotate with the wheel for an arbitrarily long time.

We want to make sure people are not disappointed because of long waiting times, and so we have introduced a flexible pricing scheme: when a person approaches the wheel, and the first gondola passing by the entrance is free, she pays $N$ dollars for the ride. If the first gondola is occupied and she has to wait for the second one, she pays $N-1$ dollars for the ride. If the first two gondolas are occupied and she has to wait for the third one, she pays $N-2$ dollars for the ride. Generally, if she has to wait for $K$ occupied gondolas to pass by, she pays $N-K$ dollars. In the worst case, when she has to wait for all but one gondola to pass, she will pay just 1 dollar.

Let's assume that people approach our wheel at random moments in time, so for each person approaching the wheel, the first gondola to pass the entrance is picked uniformly and independently. Let's also assume that nobody will come to the wheel while there's already at least one person waiting to enter, so that we don't have to deal with queueing. A person will always take the first free gondola that passes the entrance.

You are given the number of gondolas and which gondolas are already occupied. How much money are we going to make, on average, until all gondolas become occupied?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow. Each line describes one test case and contains only '.' (dot) or 'X' (capital letter X) characters. The number of characters in this line gives you $N$. The $i$-th character is 'X' when the $i$-th gondola is already occupied, and '.' when it's still free. The gondolas are numbered in the order they pass the entrance, so the 1st gondola is followed by the 2nd gondola, and so on, starting over from the beginning after the last gondola passes.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1) and $y$ is the average amount of money we will get, in dollars. Answers with absolute or relative error no larger than $10^{-9}$ will be accepted. See the FAQ for an explanation of what that means, and what formats of floating-point numbers we accept.
## 样例

### 样例输入 #1
```
5
.X.
X.X.
.XX.
X..XX.
.XX..X
```
### 样例输出 #1
```
Case #1: 4.66666666666667
Case #2: 6.00000000000000
Case #3: 5.75000000000000
Case #4: 13.4722222222222
Case #5: 13.5277777777778
```
## 提示

**Sample Explanation**

Here's how the first example works. There are nine possibilities, each with probability $1/9$:

The first person comes. If the next gondola to pass the entrance is:

* The 1st gondola, which is free, the first person enters it and pays 3 dollars. Then, some time later, the second person comes. If the next gondola to pass the entrance is:
    * The 1st gondola, which is occupied, and so is the 2nd gondola, the second person has to wait until the 3rd gondola, and thus she pays just 1 dollar before entering it. In total, we've earned 4 dollars.
    * The 2nd gondola, which is occupied, the second person has to skip it and enter the 3rd gondola and thus pays 2 dollars. In total, we've earned 5 dollars.
    * The 3rd gondola, which is free, so the second person pays 3 dollars. In total, we've earned 6 dollars.
* The 2nd gondola, which is occupied, the first person has to skip it and enter the 3rd gondola, paying 2 dollars. Then, some time later, the second person comes. If the next gondola to pass the entrance is:
    * The 1st gondola, which is free, the second person pays 3 dollars. In total, we've earned 5 dollars.
    * The 2nd gondola, which is occupied (as is the 3rd gondola), the second person has to wait until the 1st gondola, and thus she pays just 1 dollar before entering it. In total, we've earned 3 dollars.
    * The 3rd gondola, which is occupied, the second person has to skip it and enter the 1st gondola and thus pays 2 dollars. In total, we've earned 4 dollars.
* The 3rd gondola, which is free, the first person enters it and pays 3 dollars. Then, some time later, the second person comes. If the next gondola to pass the entrance is:
    * The 1st gondola, which is free, the second person pays 3 dollars. In total, we've earned 6 dollars.
    * The 2nd gondola, which is occupied (as is the 3rd gondola), the second person has to wait until the 1st gondola, and thus she pays just 1 dollar before entering it. In total, we've earned 4 dollars.
    * The 3rd gondola, which is occupied, the second person has to skip it and enter the 1st gondola and thus pays 2 dollars. In total, we've earned 5 dollars.

We have nine possibilities, earning 3 dollars in one of them, 4 dollars in three of them, 5 dollars in three of them, and 6 dollars in two of them. On average, we earn $(1\times 3+3\times 4+3\times 5+2\times 6)/9=42/9=4.6666666666\dots$ dollars.

**Limits**

- $1 \leq T \leq 50$. 

**Small dataset (8 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq N \leq 20$.

**Large dataset (23 Pts, Test set 2 - Hidden)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq N \leq 200$.


---

---
title: "「CZOI-R6」抽奖"
layout: "post"
diff: 省选/NOI-
pid: P13791
tag: ['数学', 'O2优化', '期望', '整除分块']
---
# 「CZOI-R6」抽奖
## 题目描述

公园里出现了一台抽奖机！根据小道消息，抽奖机在接下来的 $n$ 天的某一天晚上会撤走。抽奖机最终在每天晚上撤走的概率都相等。

你想在这 $n$ 天进行抽奖。初始时，你有一个中奖概率 $p = 0$。

每一天上午，你都会积攒运气，使得 $p$ 增加 $\frac{1}{n}$。

每一天下午，你都可以选择抽奖或不抽奖。若抽奖，设当前为第 $i$ 天，则你需要花费 $\frac{n}{n-i+1}$ 的代价，以 $p$ 的概率使得你的收益增加 $w$，且让 $p$ 重置为 $0$。$w$ 是一个固定的常量。

你制订了一个最优的策略以最大化你获得的收益减你付出的代价。你想知道假如你按照此策略，期望的收益减代价为多少。

**出于某种原因，你需要输出期望值乘 $\boldsymbol{n^2}$ 后对 $\boldsymbol{10^9 + 7}$ 取模的结果**。
## 输入格式

**本题有多组测试数据。**

第一行 $1$ 个整数 $T$，表示数据组数。

接下来 $T$ 行，每行 $2$ 个整数，依次为 $n, w$。
## 输出格式

输出 $T$ 行。每行输出 $1$ 个整数，表示期望值乘 $n^2$ 后对 $10^9 + 7$ 取模的结果。
## 样例

### 样例输入 #1
```
7
1 2
2 1
5 3
10 15
347 1562
724 15
283917 192034
```
### 样例输出 #1
```
1
0
2
400
87949316
1579768
172877821

```
## 提示

**【数据范围】**

**本题采用捆绑测试。**



| 子任务编号 |    $T \leq$    | $n \leq$ |    $w \leq$     | 分值 |
| :--------: | :------------: | :------: | :-------------: | :--: |
|    $1$     |      $5$       |   $20$   |      $50$       | $15$ |
|    $2$     |      $5$       |  $10^3$  | $3 \times 10^3$ | $15$ |
|    $3$     |      $20$      |  $10^6$  |     $10^6$      | $30$ |
|    $4$     | $5\times 10^3$ |  $10^6$  |     $10^6$      | $40$ |

对于 $100\%$ 的数据，$1\leq T\leq 5\times 10^3$，$1\leq n,w\leq10^6$。


---

---
title: "[NOI2012] 迷失游乐园"
layout: "post"
diff: 省选/NOI-
pid: P2081
tag: ['动态规划 DP', '图论', '递推', '2012', 'NOI', 'Special Judge', '期望', '基环树']
---
# [NOI2012] 迷失游乐园
## 题目描述

放假了，小 Z 觉得呆在家里特别无聊，于是决定一个人去游乐园玩。

进入游乐园后，小 Z 看了看游乐园的地图，发现可以将游乐园抽象成有 $n$ 个景点、$m$ 条道路的无向连通图，且该图中至多有一个环（即 $m$ 只可能等于 $n$ 或者 $n-1$）。

小 Z 现在所在的大门也正好是一个景点。小 Z 不知道什么好玩，于是他决定，从当前位置出发，每次随机去一个和当前景点有道路相连的景点，并且同一个景点不去两次（包括起始景点）。贪玩的小 Z 会一直游玩，直到当前景点的相邻景点都已经访问过为止。

小 Z 所有经过的景点按顺序构成一条非重复路径，他想知道这条路径的期望长度是多少？

小 Z 把游乐园的抽象地图画下来带回了家，可是忘了标哪个点是大门，他只好假设每个景点都可能是大门（即每个景点作为起始点的概率是一样的）。同时，他每次在选择下一个景点时会等概率地随机选择一个还没去过的相邻景点。

## 输入格式

第一行是两个整数 $n$ 和 $m$ ，分别表示景点数和道路数。

接下来 $m$ 行，每行三个整数 $X_i, Y_i, W_i$，分别表示第 $i$ 条路径的两个景点为 $X_i, Y_i$，路径长 $W_i$。所有景点的编号从 $1$ 至 $n$，两个景点之间至多只有一条道路。

## 输出格式

共一行，包含一个实数，即路径的期望长度，保留五位小数。

## 样例

### 样例输入 #1
```
4 3
1 2 3
2 3 1
3 4 4
```
### 样例输出 #1
```
6.00000000
```
## 提示

### 样例解释

样例数据中共有 $6$ 条不同的路径：

|路径|长度|概率|
|:-:|:-:|:-:| 
|$1\rightarrow 4$|$8$|$\frac{1}{4}$| 
|$2\rightarrow 1$|$3$|$\frac{1}{8}$| 
|$2\rightarrow 4$|$5$|$\frac{1}{8}$|
|$3\rightarrow 1$|$4$|$\frac{1}{8}$|
|$3\rightarrow 4$|$4$|$\frac{1}{8}$|
|$4\rightarrow 1$|$8$|$\frac{1}{4}$|

因此期望长度 $= \frac{8}{4} + \frac{3}{8} + \frac{5}{8} +\frac{4}{8} + \frac{4}{8} +\frac{8}{4} = 6.00$

### 评分方法

本题没有部分分，你程序的输出只有和标准答案的差距不超过 $0.01$ 时，才能获得该测试点的满分，否则不得分。


### 数据规模和约定

对于 $100\%$ 的数据，$1\leq W_i\leq 100$。

|测试点编号|$n$|$m$|备注| 
|:-:|:-:|:-:|:-:|
|$1$| $n=10$| $m = n-1$| 保证图是链状 |
|$2$| $n=100$|  $m = n-1$|只有节点 $1$ 的度数大于 $2$| 
|$3$| $n=1000$| $m = n-1$| / | 
|$4$| $n=10^5$| $m = n-1$| / | 
|$5$| $n=10^5$|  $m = n-1$| / | 
|$6$| $n=10$| $m = n$ | / | 
|$7$| $n=100$| $m = n$| 环中节点个数 $\leq 5$| 
|$8$| $n=1000$|$m = n$| 环中节点个数 $\leq 10$| 
|$9$| $n=10^5$ | $m = n$| 环中节点个数 $\leq 15$| 
|$10$| $n=10^5$|$m = n$| 环中节点个数 $\leq 20$| 



---

---
title: "[SCOI2008] 奖励关"
layout: "post"
diff: 省选/NOI-
pid: P2473
tag: ['2008', '四川', '各省省选', 'O2优化', '期望', '状压 DP']
---
# [SCOI2008] 奖励关
## 题目描述

你正在玩你最喜欢的电子游戏，并且刚刚进入一个奖励关。在这个奖励关里，系统将依次随机抛出 $k$ 次宝物，每次你都可以选择吃或者不吃（必须在抛出下一个宝物之前做出选择，且现在决定不吃的宝物以后也不能再吃）。

宝物一共有 $n$ 种，系统每次抛出这 $n$ 种宝物的概率都相同且相互独立。也就是说，即使前 $(k-1)$ 次系统都抛出宝物 $1$（这种情况是有可能出现的，尽管概率非常小），第 $k$ 次抛出各个宝物的概率依然均为 $\frac 1 n $。

获取第 $i$ 种宝物将得到 $p_i$ 分，但并不是每种宝物都是可以随意获取的。第 $i$ 种宝物有一个前提宝物集合 $s_i$。只有当 $s_i$ 中所有宝物都至少吃过一次，才能吃第 $i$ 种宝物（如果系统抛出了一个目前不能吃的宝物，相当于白白的损失了一次机会）。注意，$p_i$ 可以是负数，但如果它是很多高分宝物的前提，损失短期利益而吃掉这个负分宝物将获得更大的长期利益。

假设你采取最优策略，平均情况你一共能在奖励关得到多少分值？

## 输入格式

第一行为两个整数，分别表示抛出宝物的次数 $k$ 和宝物的种类数 $n$。

第 $2$ 到第 $(n + 1)$ 行，第 $(i + 1)$ 有若干个整数表示第 $i$ 个宝物的信息。每行首先有一个整数，表示第 $i$ 个宝物的分数 $p_i$。接下来若干个互不相同的整数，表示该宝物的各个前提宝物集合 $s_i$，每行的结尾是一个整数 $0$，表示该行结束。
## 输出格式

输出一行一个实数表示答案，保留六位小数。
## 样例

### 样例输入 #1
```
1 2
1 0
2 0

```
### 样例输出 #1
```
1.500000
```
### 样例输入 #2
```
6 6

12 2 3 4 5 0

15 5 0

-2 2 4 5 0

-11 2 5 0

5 0

1 2 4 5 0


```
### 样例输出 #2
```
10.023470
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq k \leq 100$，$1 \leq n \leq 15$，$-10^6 \leq p_i \leq 10^6$。


---

---
title: "[HNOI2011] XOR和路径"
layout: "post"
diff: 省选/NOI-
pid: P3211
tag: ['2011', '湖南', '期望', '高斯消元', '位运算']
---
# [HNOI2011] XOR和路径
## 题目描述

给定一个无向连通图，其节点编号为 $1$ 到 $N$，其边的权值为非负整数。试求出一条从 $1$ 号节点到 $N$ 号节点的路径，使得该路径上经过的边的权值的“XOR 和”最大。该路径可以重复经过某些节点或边，当一条边在路径中出现多次时，其权值在计算“XOR 和”时也要被重复计算相应多的次数。


直接求解上述问题比较困难，于是你决定使用非完美算法。具体来说，从 $1$ 号节点开始，以相等的概率，随机选择与当前节点相关联的某条边，并沿这条边走到下一个节点，重复这个过程，直到走到 $N$ 号节点为止，便得到一条从 $1$ 号节点到 $N$ 号节点的路径。显然得到每条这样的路径的概率是不同的并且每条这样的路径的“XOR 和”也不一样。现在请你求出该算法得到的路径的“XOR 和”的期望值。
## 输入格式

输入文件的第一行是用空格隔开的两个正整数 $N$ 和 $M$，分别表示该图的节点数和边数。紧接着的 $M$ 行，每行是用空格隔开的三个非负整数 $u,v$ 和 $w$。$(1\le u,v\le N$，$0\le w\le 10^9)$，表示该图的一条边 $(u,v)$，其权值为 $w$。输入的数据保证图连通。

## 输出格式

输出文件仅包含一个实数，表示上述算法得到的路径的“XOR 和”的期望值，要求保留三位小数。（建议使用精度较高的数据类型进行计算）

## 样例

### 样例输入 #1
```
2 2
1 1 2
1 2 3
```
### 样例输出 #1
```
2.333
```
## 提示

### 样例解释

有 $\dfrac{1}{2}$ 的概率直接从 $1$ 号节点走到 $2$ 号节点，该路径的“XOR和”为 $3$；有 $\dfrac{1}{4}$ 的概率从 $1$ 号节点走一次 $1$ 号节点的自环后走到 $2$ 号节点，该路径的“XOR和”为 $1$；有 $\dfrac{1}{8}$ 的概率从 $1$ 号节点走两次 $1$ 号节点的自环后走到 $2$ 号节点，该路径的“XOR和”为 $3$…依此类推，可知“XOR和”的期望值为：$\dfrac{3}{2}+\dfrac{1}{4}+\dfrac{3}{8}+\dfrac{1}{16}+\dfrac{3}{32}+\cdots=\dfrac{7}{3}$，约等于 $2.333$。

### 数据范围

- $30\%$ 的数据满足 $N\le 30$。  
- $100\%$ 的数据满足 $2\le N\le 100$，$M\le 10000$，但是图中可能有重边或自环。


---

---
title: "[HNOI2013] 游走"
layout: "post"
diff: 省选/NOI-
pid: P3232
tag: ['2013', '湖南', '期望', '高斯消元']
---
# [HNOI2013] 游走
## 题目描述

给定一个 $n$ 个点 $m$ 条边的无向连通图，顶点从 $1$ 编号到 $n$，边从 $1$ 编号到 $m$。 

小 Z 在该图上进行随机游走，初始时小 Z 在 $1$ 号顶点，每一步小 Z 以相等的概率随机选择当前顶点的某条边，沿着这条边走到下一个顶点，获得等于这条边的编号的分数。当小 Z 到达 $n$ 号顶点时游走结束，总分为所有获得的分数之和。 现在，请你对这 $m$ 条边进行编号，使得小 Z 获得的总分的期望值最小。
## 输入格式

第一行是两个整数，分别表示该图的顶点数 $n$ 和边数 $m$。

接下来 $m$ 行每行两个整数 $u,v$，表示顶点 $u$ 与顶点 $v$ 之间存在一条边。 
## 输出格式

输出一行一个实数表示答案，保留三位小数。
## 样例

### 样例输入 #1
```
3 3
2 3
1 2
1 3
```
### 样例输出 #1
```
3.333
```
## 提示

#### 样例输入输出 1 解释

边 $(1,2)$ 编号为 $1$，边 $(1,3)$ 编号 $2$，边 $(2,3)$ 编号为 $3$。

---

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n\leq 10$。
- 对于 $100\%$ 的数据，保证 $2\leq n \leq 500$， $1 \leq m \leq 125000$，$1 \leq u, v \leq n$，给出的图无重边和自环，且从 $1$ 出发可以到达所有的节点。


---

---
title: "[HNOI2015] 亚瑟王"
layout: "post"
diff: 省选/NOI-
pid: P3239
tag: ['动态规划 DP', '2015', '湖南', 'Special Judge', '期望']
---
# [HNOI2015] 亚瑟王
## 题目描述

小 K 不慎被 LL 邪教洗脑了，洗脑程度深到他甚至想要从亚瑟王邪教中脱坑。他决定，在脱坑之前，最后再来打一盘亚瑟王。既然是最后一战，就一定要打得漂亮。众所周知，亚瑟王是一个看脸的游戏，技能的发动都是看概率的。

作为一个非洲人，同时作为一个前 OIer，小 K 自然是希望最大化造成伤害的期望值。但他已经多年没写过代码，连 Spaly都敲不对了，因此，希望你能帮帮小 K，让他感受一下当欧洲人是怎样的体验。

本题中我们将考虑游戏的一个简化版模型。 玩家有一套卡牌，共 $n$ 张。游戏时，玩家将 $n$ 张卡牌排列成某种顺序，排列后将卡牌按从前往后依次编号为 $1 -  n$。本题中，顺序已经确定，即为输入的顺序。每张卡牌都有一个技能。第 $i$ 张卡牌的技能发动概率为 $p_i$，如果成功发动，则会对敌方造成 $d_i$ 点伤害。也只有通过发动技能，卡牌才能对敌方造成伤害。基于现实因素以及小 K 非洲血统的考虑，$p_i$ 不会为 $0$，也不会为 $1$，即 $0 < p_i < 1$。 一局游戏一共有 $r$ 轮。在每一轮中，系统将从第一张卡牌开始，按照顺序依次考虑每张卡牌。在一轮中，对于依次考虑的每一张卡牌：

1. 如果这张卡牌在这一局游戏中已经发动过技能，则

1.1. 如果这张卡牌不是最后一张，则跳过之（考虑下一张卡牌）； 否则（是最后一张），结束这一轮游戏。

2. 否则（这张卡牌在这一局游戏中没有发动过技能），设这张卡牌为第 $i$ 张

2.1. 将其以 $p_i$ 的概率发动技能。

2.2. 如果技能发动，则对敌方造成 $d_i$ 点伤害，并结束这一轮。

2.3. 如果这张卡牌已经是最后一张（即 $i$ 等于 $n$），则结束这一轮；否则，考虑下一张卡牌。

请帮助小 K 求出这一套卡牌在一局游戏中能造成的伤害的期望值。

## 输入格式

输入文件的第一行包含一个整数 $T$，代表测试数据组数。 

接下来一共 $T$ 组数据。 

每组数据的第一行包含两个用空格分开的整数 $n$ 和 $r$，分别代表卡牌的张数和游戏的轮数。

接下来 $n$ 行，每行包含一个实数和一个整数，由空格隔开，描述一张卡牌。第$i$ 行的两个数为 $p_i$ 和 $d_i$，分别代表第 $i$ 张卡牌技能发动的概率（实数）和技能发动造成的伤害（整数）。保证 $p_i$ 最多包含 $4$ 位小数，且为一个合法的概率。

## 输出格式

对于每组数据，输出一行，包含一个实数，为这套卡牌在这一局游戏中造成的伤害的期望值。对于每一行输出，只有当你的输出和标准答案的相对误差不超过 $10^{-8}$ 时——即 $\frac{|a-o|}{a} \leq 10^{-8}$ 时(其中 $a$ 是标准答案， $o$ 是输出)，你的输出才会被判为正确。建议输出 $10$ 位小数。

## 样例

### 样例输入 #1
```
1
3 2
0.5000 2
0.3000 3
0.9000 1
```
### 样例输出 #1
```
3.2660250000
```
## 提示

一共有 $13$ 种可能的情况：

1.  第一轮中，第 $1$ 张卡牌发动技能；第二轮中，第 $2$ 张卡牌发动技能；

概率为 $0.15$，伤害为 $5$。

2.  第一轮中，第 $1$ 张卡牌发动技能；第二轮中，第 $3$ 张卡牌发动技能；

概率为 $0.315$，伤害为 $3$。

3.  第一轮中，第 $1$ 张卡牌发动技能；第二轮不发动技能；

概率为 $0.035$，伤害为 $2$。

4.  第一轮中，第 $2$ 张卡牌发动技能；第二轮中，第 $1$ 张卡牌发动技能；

概率为 $0.075$，伤害为 $5$。

5.  第一轮中，第 $2$ 张卡牌发动技能；第二轮中，第 $3$ 张卡牌发动技能；

概率为 $0.0675$，伤害为 $4$。

6.  第一轮中，第 $2$ 张卡牌发动技能；第二轮不发动技能；

概率为 $0.0075$，伤害为 $3$。

7.  第一轮中，第 $3$ 张卡牌发动技能；第二轮中，第 $1$ 张卡牌发动技能；

概率为 $0.1575$，伤害为 $3$。

8.  第一轮中，第 $3$ 张卡牌发动技能；第二轮中，第 $2$ 张卡牌发动技能；

概率为 $0.04725$，伤害为 $4$。

9.  第一轮中，第 $3$ 张卡牌发动技能；第二轮不发动技能；

概率为 $0.11025$，伤害为 $1$。

10.  第一轮不发动技能；第二轮中，第 $1$ 张卡牌发动技能；

概率为 $0.0175$，伤害为 $2$。

11.  第一轮不发动技能；第二轮中，第 $2$ 张卡牌发动技能；

概率为 $0.00525$，伤害为 $3$。

12.  第一轮不发动技能；第二轮中，第 $3$ 张卡牌发动技能；

概率为 $0.011025$，伤害为 $1$。

13.  第一轮不发动技能；第二轮亦不发动技能；

概率为 $0.001225$，伤害为 $0$。

造成伤害的期望值为概率与对应伤害乘积之和，为 $3.266025$。


对于所有测试数据， $1 \leq T \leq 444， 1 \leq n \leq 220， 0 \leq r \leq 132， 0 < p_i < 1， 0 \leq d_i \leq 1000$。

除非备注中有特殊说明，数据中 $p_i$ 与 $d_i$ 均为随机生成。

请注意可能存在的实数精度问题，并采取适当措施。

本题使用 `special_judge`。


---

---
title: "[SDOI2014] 重建"
layout: "post"
diff: 省选/NOI-
pid: P3317
tag: ['2014', '矩阵树定理', '山东', 'Special Judge', '生成树', '期望']
---
# [SDOI2014] 重建
## 题目描述

T 国有 $N$ 个城市，用若干双向道路连接。一对城市之间至多存在一条道路。    

在一次洪水之后，一些道路受损无法通行。虽然已经有人开始调查道路的损毁情况，但直到现在几乎没有消息传回。    

幸运的是，此前 T 国政府调查过每条道路的强度，现在他们希望只利用这些信息估计灾情。具体地，给定每条道路在洪水后仍能通行的概率，请计算仍能通行的道路恰有 $N-1$ 条，且能联通所有城市的概率。

## 输入格式

输入的第一行包含整数 $N$。  

接下来 $N$ 行，每行 $N$ 个实数，第 $i+1$ 行，列的数 $G_{i,j}$ 表示城市 $i$ 与 $j$ 之间仍有道路联通的概率。    

输入保证 $G_{i,j}=G_{j,i}$，且 $G_{i,i}=0$。$G_{i, j}$ 至多包含两位小数。

## 输出格式

输出一个任意位数的实数表示答案。    

你的答案与标准答案相对误差不超过 $10^{-4}$ 即视为正确。

## 样例

### 样例输入 #1
```
3
0 0.5 0.5
0.5 0 0.5
0.5 0.5 0
```
### 样例输出 #1
```
0.375
```
## 提示

$1<N\leq 50$。

数据保证答案非零时，答案不小于 $10^{-4}$。



---

---
title: "仓鼠找sugar II"
layout: "post"
diff: 省选/NOI-
pid: P3412
tag: ['洛谷原创', '概率论', '期望', '洛谷月赛']
---
# 仓鼠找sugar II
## 题目描述

小仓鼠和他的基（mei）友（zi）sugar 住在地下洞穴中，每个节点的编号为 $1\sim n$ 间的一个整数。地下洞穴是一个树形结构（两个洞穴间距离为 $1$）。这一天小仓鼠打算从从他的卧室 $a$（**是任意的**）走到他的基友卧室 $b$（还**是任意的**）（注意，$a$ 有可能等于 $b$）。然而小仓鼠学 OI 学傻了，不知道怎么怎么样才能用最短的路程走到目的地，于是他只能随便乱走。当他在一个节点时，会等概率走到这个点的母亲或者所有孩子节点（例如这个节点有一个母亲节点和两个子节点，那么下一步走到这 $3$ 个节点的概率都是 $\dfrac{1}{3}$），一旦走到了他基友的卧室，就会停下。

现在小仓鼠希望知道，他走到目的地时，走的步数的期望。这个期望本来是一个有理数，但是为了避免误差，我们要求输出这个有理数对 $998,244,353$ 取模的结果。

形式化地说，可以证明答案可以被表示为既约分数 $\dfrac{y}{x}$，其中 $x\not\equiv 0\pmod {998,244,353}$。可以证明存在一个唯一的整数 $z$（$0\le z\lt 998,244,353$），使得 $xz=y$，你只需要输出 $z$ 的值。


小仓鼠那么弱，还要天天被 JOHNKRAM 大爷虐，请你快来救救他吧！
## 输入格式

第一行一个正整数 $n$，表示这棵树节点的个数。

接下来 $n-1$ 行，每行两个正整数 $u$ 和 $v$，表示节点 $u$ 到节点 $v$ 之间有一条边。
## 输出格式

一个整数，表示取模后的答案。
## 样例

### 样例输入 #1
```
3
1 2
1 3

```
### 样例输出 #1
```
110916041
```
## 提示

样例解释：期望的真实值为 $\dfrac {16}{9}$。

如果 $a$ 是叶子，$b$ 是根，此时期望 $\mathbb{E}_1=1$，有 $2$ 种情况。

如果 $a$ 是根，$b$ 是叶子，则 $\displaystyle \mathbb{E}_2=\frac{1}{2}+\frac{3}{4}+\frac{5}{8}+\cdots=3$。有 $2$ 种情况。

如果 $a,b$ 是不同的叶子，则 $\mathbb{E}_3=\mathbb{E}_2+1=4$。有 $2$ 种情况。

如果 $a=b$，则 $\mathbb{E}_4=0$。有 $3$ 种情况。

所以答案为 $\displaystyle \frac{2\times 1+2\times 3+2\times 4+3\times 0}{2+2+2+3}=\frac{16}{9}$。

由于 $110,916,041\times 9=998,244,369\equiv 16\pmod {998,244,353}$，所以输出 $110,916,041$。

对于 $30\%$ 的数据，$n\le 5$；

对于 $50\%$ 的数据，$n\le 5000$；

对于所有数据，$n\le 100000$。

$\text{Statement fixed by @Starrykiller.}$


---

---
title: "[六省联考 2017] 分手是祝愿"
layout: "post"
diff: 省选/NOI-
pid: P3750
tag: ['动态规划 DP', '递推', '2017', '各省省选', '枚举', '期望']
---
# [六省联考 2017] 分手是祝愿
## 题目描述

> Zeit und Raum trennen dich und mich.
时空将你我分开。

B 君在玩一个游戏，这个游戏由 $n$ 个灯和 $n$ 个开关组成，给定这 $n$ 个灯的初始状态，下标为从 $1$ 到 $n$ 的正整数。

每个灯有两个状态亮和灭，我们用 $1$ 来表示这个灯是亮的，用 $0$ 表示这个灯是灭的，游戏的目标是使所有灯都灭掉。

但是当操作第 $i$ 个开关时，所有编号为 $i$ 的约数（包括 $1$ 和 $i$）的灯的状态都会被改变，即从亮变成灭，或者是从灭变成亮。

B 君发现这个游戏很难，于是想到了这样的一个策略，每次等概率随机操作一个开关，直到所有灯都灭掉。

这个策略需要的操作次数很多，B 君想到这样的一个优化。如果当前局面，可以通过操作小于等于 $k$ 个开关使所有灯都灭掉，那么他将不再随机，直接选择操作次数最小的操作方法（这个策略显然小于等于 $k$ 步）操作这些开关。

B 君想知道按照这个策略（也就是先随机操作，最后小于等于 $k$ 步，使用操作次数最小的操作方法）的操作次数的期望。

这个期望可能很大，但是 B 君发现这个期望乘以 $n$ 的阶乘一定是整数，所以他只需要知道这个整数对 $100003$ 取模之后的结果。

## 输入格式

第一行两个整数 $n, k$。
接下来一行 $n$ 个整数，每个整数是 $0$ 或者 $1$，其中第 $i$ 个整数表示第 $i$ 个灯的初始情况。

## 输出格式

输出一行，为操作次数的期望乘以 $n$ 的阶乘对 $100003$ 取模之后的结果。

## 样例

### 样例输入 #1
```
4 0
0 0 1 1

```
### 样例输出 #1
```
512
```
### 样例输入 #2
```
5 0
1 0 1 1 1
```
### 样例输出 #2
```
5120
```
## 提示

对于 $0\%$ 的测试点，和样例一模一样；  
对于另外 $30\%$ 的测试点，$n \leq 10$；  
对于另外 $20\%$ 的测试点，$n \leq 100$；  
对于另外 $30\%$ 的测试点，$n \leq 1000$；  
对于 $100\%$ 的测试点，$1 \leq n \leq 100000, 0 \leq k \leq n$；  
对于以上每部分测试点，均有一半的数据满足 $k = n$。



---

---
title: "[SHOI2012] 随机树"
layout: "post"
diff: 省选/NOI-
pid: P3830
tag: ['动态规划 DP', '2012', '各省省选', '上海', '期望', '构造']
---
# [SHOI2012] 随机树
## 题目背景

SHOI2012 D1T3

## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/6555.png)

## 输入格式

输入仅有一行，包含两个正整数 q, n，分别表示问题编号以及叶结点的个数。

## 输出格式

输出仅有一行，包含一个实数 d，四舍五入精确到小数点后 6 位。如果 q = 1，则 d 表示叶结点平均深度的数学期望值；如果 q = 2，则 d 表示树深度的数学期望值。

## 样例

### 样例输入 #1
```
1 4
```
### 样例输出 #1
```
2.166667
```
### 样例输入 #2
```
2 4
```
### 样例输出 #2
```
2.666667
```
### 样例输入 #3
```
1 12
```
### 样例输出 #3
```
4.206421
```
### 样例输入 #4
```
2 12
```
### 样例输出 #4
```
5.916614
```
## 提示

 ![](https://cdn.luogu.com.cn/upload/pic/6556.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/6557.png) 

![](https://cdn.luogu.com.cn/upload/pic/6558.png)



---

---
title: "中学数学题"
layout: "post"
diff: 省选/NOI-
pid: P3922
tag: ['数学', '高精度', '洛谷原创', '期望']
---
# 中学数学题
## 题目背景

琪露诺：我知道了！答案是-1 0，因为幻想乡没有传送器！

露米娅：真拿你没办法。。算了，再来一道中学数学题吧

说着，露米娅写下了一个数列

$ 1 , 2 , 4 , 8 , 16 , 32 , 64 , 128 , \cdots , 2048 , 4096 , 8192 , 16384 , \cdots $

## 题目描述

露米娅：这个数列的通项公式是 $ x_n = 2^{n-1} $

那么你来求一下前 $ k+1 $ 项中有多少个第一位为4吧（比如4096）


输入经过“加密”

详细输入方式见【输入格式】

## 输入格式

一行两个正整数，$ t $ 和 $ k_0 $

若 $ t = 1 $ 说明实际的k就是 $ k_0 $

若 $ t = 0 $ 说明实际的k是 $ 10^{k_0} $

## 输出格式

一个整数 $ ans $ ，表示有多少个数第一位为 4

## 样例

### 样例输入 #1
```
1 3

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
0 1

```
### 样例输出 #2
```
1

```
### 样例输入 #3
```
1 10

```
### 样例输出 #3
```
1

```
## 提示

对于30%的数据， $ k_0 \leq 10^7, t = 1 $

对于70%的数据， $ k_0 \leq 10^9, t = 1 $

对于另外30%的数据， $ k_0 \leq 233 , t = 0 $

对于100%的数据，$ k_0 \geq 1 $



---

---
title: "[TJOI2015] 概率论"
layout: "post"
diff: 省选/NOI-
pid: P3978
tag: ['递推', '2015', '各省省选', 'Special Judge', 'Catalan 数', '生成函数', '期望', '天津']
---
# [TJOI2015] 概率论
## 题目描述

为了提高智商，ZJY 开始学习概率论。有一天，她想到了这样一个问题：对于一棵随机生成的 $n$ 个结点的有根二叉树（所有互相不同构的形态等概率出现），它的叶子节点数的期望是多少呢？

判断两棵树是否同构的伪代码如下：

$$
\def\arraystretch{1.2}
    \begin{array}{ll}
    \hline
    \textbf{算法 1}&\text{Check}(T1,T2) \\
    \hline
    1&\textbf{Require: }\text{ 两棵树的节点}T1,T2\\
    2&\qquad\textbf{if}\ \ T1=\text{null}\textbf{ or }T2=\text{null}\textbf{ then }\\
    3&\qquad\qquad\textbf{return}\ \ T1=\text{null}\textbf{ and }T2=\text{null}\\
    4&\qquad\textbf{else}\\
    5&\qquad\qquad\textbf{return}\ \text{Check}(T1\to\mathit{leftson},T2\to\mathit{leftson}) \\ 
    & \qquad\qquad\qquad \textbf{ and }\text{Check}(T1\to\mathit{rightson},T2\to\mathit{rightson})\\
    6&\qquad\textbf{endif}\\
    \hline
    \end{array} 
    $$


## 输入格式

输入一个正整数 $n$，表示有根树的结点数。

## 输出格式

输出这棵树期望的叶子节点数，要求误差小于 $10^{-9}$。

## 样例

### 样例输入 #1
```
1
```
### 样例输出 #1
```
1.000000000
```
### 样例输入 #2
```
3
```
### 样例输出 #2
```
1.200000000
```
## 提示

## 数据范围

对于 $30\%$ 的数据，$1 \le n \le 10$。

对于 $70\%$ 的数据，$1 \le n \le 100$。

对于 $100\%$ 的数据，$1 \le n \le 10^9$。


---

---
title: "树链剖分"
layout: "post"
diff: 省选/NOI-
pid: P3995
tag: ['Special Judge', 'O2优化', '树链剖分', '期望', '差分']
---
# 树链剖分
## 题目背景

树链剖分，计算机术语，指一种对树进行划分的算法，它先通过轻重边剖分将树分为多条链，保证每个点属于且只属于一条链，然后再通过数据结构（树状数组、SBT、SPLAY、线段树等）来维护每一条链。(摘自百度百科)

## 题目描述

大宁最近在研究树链剖分。他发现树链剖分的时间复杂度主要由轻重链的划分方式保证，最常见的剖分方式是按照子树大小剖分。如图（摘自百度百科），黑边为重链，长度任意，白边为轻链，长度全部为1。注意，下图 1-2, 1-3 为不同轻链。

 ![](https://cdn.luogu.com.cn/upload/pic/11502.png) 

其中对于每个节点，其在重链上的儿子叫做重儿子，且只有唯一一个，而叶子节点没有重儿子。例如对于图上 1 号点，重儿子是 4 号点。显然，对于不同剖分方式，同一组查询访问的链的数量不同。现在给定一棵根为 1 号节点的有根树和若干询问操作，每次询问访问从 $u$ 到 $v$ 上面的所有轻重链一次。例如在上图的剖分方式中，查询 3 到 8 一共访问了 3 条：轻链 1-3，重链 1-4，轻链 4-8；查询 3 到 11 一共访问了 3 条：轻链 1-3，轻链 1-2，重链 2-11。

大宁请你给出一种剖分方案，使所有询问操作总共访问的**轻重链总条数**最小，由于可能有许多合法方案，请任意输出一种，我们提供Special Judge检验你的方案的正确性。

设你的剖分方式的查询链数为 $x$，std 答案的查询数为 $x_0$，评分参数为 $a$ 。

你得到的分数是：

* $10$ 分  当 $x\leq x_0$ 。

* $8$ 分  当 $0<(x-x_0)\leq a$ 。

* $7$ 分  当 $a<(x-x0)\leq 2\times a$ 。

* $6$ 分  当 $2\times a<(x-x0)\leq 3\times a$ 。

* $1$ 分  输出了合法的方案。



$a=\lfloor\frac{q}{300}\rfloor$, $q$ 为询问总数。

我们提供了 `Div\_Checker.exe` 来检验你的答案。把它放到 `div.in` , `div.out` 同文件夹下运行，其中 `div.in` 是输入数据的文件形式, `div.out` 是你的程序在该输入下的输出。如果你的 `div.out` 答案合法，它会返回：

`Your answer is XXX.`

`XXX` 是你的剖分方式在该输入数据下的查询次数，否则返回：

`Wrong Outdata.`

**注意: 在正式提交的时候不能使用文件输入输出。**

## 输入格式

第一行有两个正整数 $n$ 和 $q$ ，表示该树的节点数 $n$ 和查询次数 $q$ 。

接下来 $n-1$ 行，各有两个正整数 $u$ ，$v$ ，表示 $u$ 和 $v$ 之间有一条边。

接下来 $q$ 行为 $q$ 个询问，为 $U$，$V$，表示有一次从 $U$ 到 $V$ 的询问。

## 输出格式

一共 $n$ 行，对于 $i$ 号节点，如果它不是叶子节点，那么输出它在你的剖分方案里的重儿子，否则输出 0。

## 样例

### 样例输入 #1
```
14 7
1 4
4 10
4 9
4 8
9 13
13 14
3 1
7 3
2 1
2 6
6 12
11 6
5 2
11 3
7 8
2 8
11 1
8 14
5 7
9 14

```
### 样例输出 #1
```
2
6
7
8
0
11
0
0
13
0
0
0
14
0

```
## 提示

样例即为上图，但图上的剖分方式对于此处的查询并非最优。

对于 $20\%$ 的数据，$n,q<=10$

对于 $60\%$ 的数据，$n,q<=1000$

对于 $100\%$ 的数据，$1<=n<=100000$,$1<=q<=200000$ ,保证给出的是一棵合法的树。

[Div\_Checker下载](https://pan.baidu.com/s/1c26OLf6)

如果对Checker的使用方式不太理解，请参照下面的图片

图中数据为样例。

 ![](https://cdn.luogu.com.cn/upload/pic/11563.png) 

一个合法方案的输出。

 ![](https://cdn.luogu.com.cn/upload/pic/11564.png) 

不合法方案的输出。

![](https://cdn.luogu.com.cn/upload/pic/11565.png)

---

$\text{upd 2022.8.26}$：新增加一组 Hack 数据。


---

---
title: "小 Y 和恐怖的奴隶主"
layout: "post"
diff: 省选/NOI-
pid: P4007
tag: ['2017', 'O2优化', '矩阵加速', '概率论', '期望', 'CTT（清华集训/北大集训）']
---
# 小 Y 和恐怖的奴隶主
## 题目背景

“A fight? Count me in!” 要打架了，算我一个。

“Everyone, get in here!” 所有人，都过来！

## 题目描述

小 Y 是一个喜欢玩游戏的 OIer。一天，她正在玩一款游戏，要打一个 Boss。

虽然这个 Boss 有 $10^{100}$ 点生命值，但它只带了一个随从——一个只有 $m$ 点生命值的“恐怖的奴隶主”。

这个“恐怖的奴隶主”有一个特殊的技能：每当它被扣减生命值但没有死亡（死亡即生命值 $\leq 0$），且 Boss 的随从数量小于上限 $k$，便会召唤一个新的具有 $m$ 点生命值的“恐怖的奴隶主”。

现在小 Y 可以进行 $n$ 次攻击，每次攻击时，会从 Boss 以及 Boss 的所有随从中的等概率随机选择一个，并扣减 $1$ 点生命值，她想知道进行 $n$ 次攻击后扣减 Boss 的生命值点数的期望。为了避免精度误差，你的答案需要对 $998244353$ 取模。
## 输入格式

输入第一行包含三个正整数 $T, m, k$，$T$ 表示询问组数，$m, k$ 的含义见题目描述。

接下来 $T$ 行，每行包含一个正整数 $n$，表示询问进行 $n$ 次攻击后扣减Boss的生命值点数的期望。
## 输出格式

输出共 $T$ 行，对于每个询问输出一行一个非负整数，表示该询问的答案对 $998244353$ 取模的结果。

可以证明，所求期望一定是一个有理数，设其为 $p / q$ $(\mathrm{gcd}(p,q) = 1)$，那么你输出的数 $x$ 要满足 $p \equiv qx \pmod{998244353}$。
## 样例

### 样例输入 #1
```
3 2 6
1
2
3
```
### 样例输出 #1
```
499122177
415935148
471393168
```
## 提示

【样例 $1$ 解释】

对于第一次询问，第一次攻击有 $\frac{1}{2}$ 的概率扣减 Boss 的生命值，有 $\frac{1}{2}$ 的概率扣减随从的生命值，所以答案为 $\frac{1}{2}$。$1 \equiv 2 \times 499122177 \pmod{998244353}$。

对于第二次询问，如果第一次攻击扣减了 Boss 的生命值，那么有 $\frac{1}{2}$ 的概率第二次攻击仍扣减 Boss 的生命值，有 $\frac{1}{2}$ 的概率第二次攻击扣减随从的生命值；如果第一次攻击扣减了随从的生命值，那么现在又新召唤了一个随从（“恐怖的奴隶主”），于是有 $\frac{1}{3}$ 的概率第二次攻击扣减 Boss 的生命值，有 $\frac{2}{3}$ 的概率第二次攻击扣减随从的生命值。所以答案为 $\frac{1}{2}\times\frac{1}{2}\times2+\frac{1}{2}\times\frac{1}{2}\times1+\frac{1}{2}\times\frac{1}{3}\times1+\frac{1}{2}\times\frac{2}{3}\times0 = \frac{11}{12}$。 $11 \equiv 12 \times 415935148\pmod{998244353}$。

【提示】

题目顺序可能与难度无关。

【子任务】

在所有测试点中，$1 \leq T \leq 1000, 1 \leq n \leq {10}^{18}, 1 \leq m \leq 3, 1 \leq k \leq 8$。

各个测试点的分值和数据范围如下：

![12058](https://cdn.luogu.com.cn/upload/pic/12058.png)


---

---
title: "连环病原体"
layout: "post"
diff: 省选/NOI-
pid: P4230
tag: ['深度优先搜索 DFS', '动态树 LCT', '期望', '差分']
---
# 连环病原体
## 题目背景

###（一）洞穴

顺着狭窄倾斜的溶洞向下走，这里，真有一番地心探险的感觉呢。

告诉你啊，地底有一片广阔的大世界，叫做旧地狱。

那里居住着被地面上的人厌恶的妖怪们。

虽然听着比较吓人，但实际上在地狱废弃后，一切都是井井有条的。

前方有一片开阔的空间啊，好像有人。

"地面上的来客吗,你好啊"

终于遇到地底的居民了。

眼前的两只妖怪是黑谷山女和琪斯美。

琪斯美呆在一个小桶里，悬挂在空中，和山女讨论着什么。

"哇，你们在讨论什么啊"

"嗯，有关病毒的问题，你们不懂的"

忘记说了，山女可以操纵疾病，所以谈论这样的话题自然也就很平常了。

不过好奇心很难抵挡啊，那就假装自己能帮上忙，然后接着问下去吧。

"好吧，你们要是能帮上忙的话就再好不过了"

"嗯，主要是，想知道病原体之间的相互作用，会对疾病产生什么影响呢。你看啊，把不同种的病原体看做点，相互作用看成连接这些点的线，如果产生了环，那么病毒的威力就会大幅加强，我把它叫做加强环。"

"病原体之间的相互作用也有很多种呢，我想研究的是，每种相互作用在产生加强环的过程中有多么重要。"

啊，听起来好复杂，不过如果帮了她的忙，地底的妖怪们大概会对我们友善一些吧。

而且，点，边，环？这些名词似乎见过呢，说不定我真的能帮上忙？

那么，继续详细地询问吧。

嗯，问出来的信息已经记录在这张纸上了。

## 题目描述

问题摘要:

有n 种病原体，它们之间会产生$m$种无方向性的影响，第$i$种影响发生在$u_i$,$v_i$ **两种**病原体之间。

我们把所有的**影响**按编号顺序排成一个序列，如果某一个区间包含有环，那么这个区间被称作加强区间。

求每种影响分别在多少个加强区间中出现过。

那么，到底怎样做才能高效的得出结果呢？

(后续剧情见本题题解，接下来请看T2)
## 输入格式

第一行一个数$m$
接下来$m$行每行两个数$u_i$,$v_i$，用空格分隔
## 输出格式

一行$m$个数字，第$i$个数字代表第$i$种影响在多少个加强区间内出现过，数字之间用空格分隔
## 样例

### 样例输入 #1
```
5
1 2
2 3
3 4
1 4
4 2

```
### 样例输出 #1
```
2 3 3 3 2
```
## 提示

###样例解释：

第一种影响在[1,4]和[1,5]两个加强区间内出现

第二种影响在[1,4]、[1,5]和[2,5]三个加强区间内出现

第三种影响在[1,5]、[1,4]和[2,5]三个加强区间内出现

第四种影响在[1,4]、[2,5]和[1,5]三个加强区间内出现

第五种影响在[2,5]和[1,5]两个加强区间内出现

注意：加强区间是由“影响”构成的，而不是由“病原体”构成的

$n\leqslant2m\leqslant400000$

测试点1~2总分10分，$m\leqslant5$

测试点3~6总分20分，$m\leqslant200$

测试点7~12总分30分，$m\leqslant5000$

测试点13~15总分15分，$m\leqslant50000$

测试点16~18总分15分，$m\leqslant50000$，捆绑测试

测试点19~22总分10分，$m\leqslant200000$，捆绑测试

by oscar


---

---
title: "[SHOI2014] 概率充电器"
layout: "post"
diff: 省选/NOI-
pid: P4284
tag: ['2014', '各省省选', '上海', '连通块', '条件概率', '期望', '高斯消元']
---
# [SHOI2014] 概率充电器
## 题目描述

著名的电子产品品牌 SHOI 刚刚发布了引领世界潮流的下一代电子产品——概率充电器：

“采用全新纳米级加工技术，实现元件与导线能否通电完全由真随机数决定！SHOI 概率充电器，您生活不可或缺的必需品！能充上电吗？现在就试试看吧！”

SHOI 概率充电器由 $n-1$ 条导线连通了 $n$ 个充电元件。进行充电时，每条导线是否可以导电以概率决定，每一个充电元件自身是否直接进行充电也由概率决定。随后电能可以从直接充电的元件经过通电的导线使得其他充电元件进行间接充电。

作为 SHOI 公司的忠实客户，你无法抑制自己购买 SHOI 产品的冲动。在排了一个星期的长队之后终于入手了最新型号的 SHOI 概率充电器。你迫不及待地将 SHOI 概率充电器插入电源——这时你突然想知道，进入充电状态的元件个数的期望是多少呢？
## 输入格式

第一行一个整数 $n$。概率充电器的充电元件个数。充电元件由 $1 \sim n$ 编号。

之后的 $n-1$ 行每行三个整数 $a, b, p$，描述了一根导线连接了编号为 $a$ 和 $b$ 的充电元件，通电概率为 $p\%$。

第 $n+2$ 行 $n$ 个整数 $q_i$。表示 $i$ 号元件直接充电的概率为 $q_i\%$。
## 输出格式

输出一行一个实数，为能进入充电状态的元件个数的期望，四舍五入到小数点后 6 位小数。
## 样例

### 样例输入 #1
```
3
1 2 50
1 3 50
50 0 0
```
### 样例输出 #1
```
1.000000
```
### 样例输入 #2
```
5
1 2 90
1 3 80
1 4 70
1 5 60
100 10 20 30 40
```
### 样例输出 #2
```
4.300000
```
## 提示

对于 $30\%$ 的数据，$n \leq 5 \times 10^3$。

对于 $100\%$ 的数据，$n \leq 5 \times 10^5$，$0 \leq p,q_i \leq 100$。


---

---
title: "随机漫游"
layout: "post"
diff: 省选/NOI-
pid: P4321
tag: ['动态规划 DP', '图论', 'O2优化', '期望', '高斯消元']
---
# 随机漫游
## 题目描述

H 国有 $N$ 个城市

在接下来的 $M$ 天，小 c 都会去找小 w，但是小 c 不知道小 w 的具体位置，所以小 c 决定每次随机找一条路走，直到遇到了小 w 为止

小 c 知道小 w 只有可能是在 $c_1, c_2.. c_n$ 这 $n$ 个城市中的一个，小 c 想知道在最坏情况下，小 c 遇到小 w 期望要经过多少条道路

H 国所有的边都是无向边，两个城市之间最多只有一条道路直接相连，没有一条道路连接相同的一个城市

任何时候，H 国不存在城市 $u$ 和城市 $v$ 满足从 $u$ 无法到达 $v$
## 输入格式

输入第 1 行一个正整数$N, E$，分别表示 H 国的城市数与边的数量

输入第 2 行至第 $E+1$ 行，每行两个正整数 $u, v$，分别表示城市 $u$ 到城市 $v$ 有一条道路

输入第 $E+2$ 行一个正整数 $M$

输入第 $E+3$ 行至第 $E+M+2$ 行每行 $n+2$ 个正整数，第一个正整数为 $n$，接下来 $n$ 个互不相同的正整数 $c_i$，最后一个正整数 $s$ 表示小 c 所在的城市
## 输出格式

输出共 $M$ 行，每行一个正整数 $r$ 表示答案

如果你计算出来的期望为 $\frac{q}{p}$，其中$p, q$互质，那么你输出的 $r$ 满足 $r\times p \equiv q(\mathrm{mod}\ 998244353)$，
且$0\leq r < 998244353$，可以证明这样的 $r$是唯一的
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
3
2 1 2 1		
3 1 2 3 1
1 3 1
```
### 样例输出 #1
```
1
4
4
```
## 提示

$H$ 国的道路构成一条链，所以最坏情况下就是小 w 在深度最大的点上(以小 c 所在的城市为根)

对于第一天，小 c 所在的城市为 1，深度最大的点为 2，城市 1 只能到达城市 2，期望经过 1 条道路到达

对于第二天，小 c 所在的城市为 1，深度最大的点为 3，计算的期望经过 4 条道路到达

第三天同第二天

最坏情况也就是说经过所有 $n$ 个可能的城市至少一遍

subtask1 : 10分，$N = 4, M = 12$

subtask2 : 15分，$N =10, M = 100000$

subtask3 : 15分，$N = 18, M = 1$

subtask4 : 10分，$N = 18, M = 99995$，图是一条链

subtask5 : 10分，$N = 18, M = 99996$，所有的 $s$ 都相同

subtask6 : 15分，$N = 18, M = 99997$，$E = N-1$

subtask7 : 15分，$N = 18, M = 99998$，所有的 $s$ 都相同

subtask8 : 10分，$N = 18, M = 99999$

对于所有数据 : $1\leq N\leq 18, 1\leq M\leq 100000, 1\leq E\leq \frac{N(N-1)}{2}$


---

---
title: "[JXOI2018] 排序问题"
layout: "post"
diff: 省选/NOI-
pid: P4561
tag: ['数学', '贪心', '2018', '各省省选', '期望']
---
# [JXOI2018] 排序问题
## 题目背景

九条可怜是一个热爱思考的女孩子。
## 题目描述



九条可怜最近正在研究各种排序的性质，她发现了一种很有趣的排序方法： Gobo sort ！

Gobo sort 的算法描述大致如下：

- 假设我们要对一个大小为 $n$ 的数列 $a$ 排序。
- 等概率随机生成一个大小为 $n$ 的排列 $p$ 。
- 构造一个大小为 $n$ 的数列 $b$ 满足 $b_i=a_{p_i}$ ，检查 $b$ 是否有序，如果 $b$ 已经有序了就结束算法，并返回 $b$ ，不然返回步骤 2。


显然这个算法的期望时间复杂度是 $O(n\times n!)$ 的，但是九条可怜惊奇的发现，利用量子的神奇性质，在量子系统中，可以把这个算法的时间复杂度优化到线性。

九条可怜对这个排序算法进行了进一步研究，她发现如果一个序列满足一些性质，那么 Gobo sort 会很快计算出正确的结果。为了量化这个速度，她定义 Gobo sort 的执行轮数是步骤 2 的执行次数。

于是她就想到了这么一个问题：

现在有一个长度为 $n$ 的序列 $x$ ，九条可怜会在这个序列后面加入 $m$ 个元素，每个元素是 $[l,r]$ 内的正整数。 她希望新的长度为 $n+m$ 的序列执行 Gobo sort 的期望执行轮数尽量的多。她希望得到这个最多的期望轮数。

九条可怜很聪明，她很快就算出了答案，她希望和你核对一下，由于这个期望轮数实在是太大了，于是她只要求你输出对 $998244353$ 取模的结果。
## 输入格式

第一行输入一个整数 $T$，表示数据组数。

接下来 $2 \times T$ 行描述了 $T$ 组数据。

每组数据分成两行，第 1 行有四个正整数 $n,m,l,r$ ，表示数列的长度和加入数字的个数和加入数字的范围。
第 2 行有 $n$ 个正整数，第 $i$ 个表示 $x_i$ 。
## 输出格式

输出 $T$ 个整数，表示答案。

## 样例

### 样例输入 #1
```
2
3 3 1 2
1 3 4
3 3 5 7
1 3 4
```
### 样例输出 #1
```
180
720

```
## 提示

###样例解释

对于第一组数据，我们可以添加 $\{1,2,2\}$ 到序列的最末尾，使得这个序列变成 `1 3 4 1 2 2` ，那么进行一轮的成功概率是 $\frac{1}{180}$ ，因此期望需要 $180$ 轮。

对于第二组数据，我们可以添加 $\{5,6,7\}$ 到序列的最末尾，使得这个序列变成 `1 3 4 5 6 7` ，那么进行一轮的成功概率是 $\frac{1}{720}$ ，因此期望需要 $720$ 轮。

### 数据范围

对于 30% 的数据， $T\leq 10 , n,m,l,r\leq 8$。  
对于 50% 的数据， $T\leq 300,n,m,l,r,a_i\leq 300$ 。  
对于 60% 的数据， $\sum{r-l+1}\leq 10^7$ 。  
对于 70% 的数据， $\sum{n} \leq 2\times 10^5$ 。  
对于 90% 的数据， $m\leq 2\times 10^5$。  
对于 100% 的数据， $T\leq 10^5,n\leq 2\times 10^5,m\leq 10^7,1\leq l\leq r\leq 10^9$ ， $1\leq a_i\leq 10^9,\sum{n}\leq 2\times 10^6$ 。


---

---
title: "[CTSC2018] 假面"
layout: "post"
diff: 省选/NOI-
pid: P4564
tag: ['数学', '2018', 'O2优化', '枚举', '期望', 'CTSC/CTS']
---
# [CTSC2018] 假面
## 题目背景


针针是绿绿的好朋友。
## 题目描述

针针喜欢玩一款叫做 DotA (**D**efense **o**f **t**he **A**lgorithm) 的游戏，在这个游戏中，针针会操纵自己的英雄与队友一起对抗另一支队伍。
针针在 DotA 中最喜欢使用的英雄叫做假面（Faceless），该英雄有 $2$ 个技能：

- 锁定：对一名指定的敌方单位使用，以 $p$ 的概率对该单位造成 $1$ 点伤害（使其减少 $1$ 点生命值）。
- 结界：在一片区域施放结界，让该区域内的所有其他单位无法动弹。
在游戏中，如果一个单位的生命值降至 $0$ 或 $0$ 以下，那么该单位就会死亡。

针针操纵假面的水平一般，因此他决定勤加练习。现在有 $n$ 个敌方单位（编号从 $1$ 至 $n$），编号为 $i$ 的敌方单位有 $h_i$ 点生命值。

针针已经安排好了练习的计划，他会按顺序施放 $Q$ 个技能：

- 对于锁定技能：针针会指定一个敌方单位 $id$ ，并对它施放。由于决定概率系数 $p$ 的因素很多，因此每次的 $p$ 都不一定相同。
特别地，如果该敌方单位已经死亡，那么该技能不会造成任何效果。
- 对于结界技能：针针会希望对 $k$ 个指定的敌方单位施放，但由于针针并不擅长施放该技能，因此他只能命中恰好 $1$ 个敌方单位。命中每个存活的敌方单位的概率是相等的（也就是说已经死亡的敌方单位不会有任何影响）。
特别地，如果这 $k$ 个敌方单位均已死亡，那么该技能同样不会命中任何敌方单位。

现在，围观针针进行练习的绿绿想知道：

1. 对于针针施放的每个结界技能，它命中各敌人的概率分别是多少。
2. 在针针的所有技能施放完毕后，所有敌方单位剩余生命值的期望分别是多少。

由于绿绿还要围观针针训练，所以请你帮他解决这两个问题。

为了防止精度误差，对于所有需要输出的数值，请输出其在模 $998244353$ 意义下的值。

由于结界为假面的终极技能，因此针针施放该技能的次数不会太多。具体请见”子任务“。
## 输入格式

第 $1$ 行为 $1$ 个正整数 $n$ ，表示敌方单位的数量。  
第 $2$ 行为 $n$ 个正整数 $m_1,\cdots , m_n$，依次表示各敌方单位的初始生命值。  
第 $3$ 行为 $1$ 个非负整数 $Q$ ，表示针针施放技能的数量。  
第 $4$ 行至第 $Q + 3$ 行，每行描述一个技能，第 $i + 3$ 行描述第 $i$ 个技能。

每行的开头为一个整数 $op$ ，表示该技能的种类。  
如果 $op = 0$ ，则表示锁定技能。并在此后跟随着 $3$ 个正整数 $id , u , v$ ，表示技能施放的目标为 $id$ ，技能命中的概率为 $p = \frac{u}{v}$ 。（保证 $1\le id \le n , 0 < u \le v < 998244353$ ）  
如果 $op = 1$ ，则表示结界技能。并在此后跟随着 $1$ 个正整数 $k$ 表示技能施放的目标数量，随后还有额外的 $k$ 个数 $id_1,\cdots,id_k$ 描述技能施放的所有目标。（保证所有 $1 \le id_i \le n$ 互不相同） 对于每一行，如果行内包含多个数，则用单个空格将它们隔开。
## 输出格式

输出包括 $C + 1$ 行（其中 $C$ 为结界技能的数量）：

前 $C$ 行依次对应每个结界技能，对于每行：

输出 $k$ 个数，第 $i$ 个数表示结界命中敌方单位 $id_i$ 的概率。   
第 $C + 1$ 行输出 $n$ 个数，第 $i$ 个数表示在所有技能施放完毕后，敌方单位 $i$ 剩余生命值的期望值。  

对于每一行，如果行内包含多个数，则用单个空格将它们隔开。

对于所有数值，请输出它们对 $998244353$ 取模的结果：即设答案化为最简分式后的形式为 $\frac{a}{b}$ ，其中 $a$ 和 $b$ 的互质。输出整数 $x$ 使得 $bx \equiv a\bmod 998244353$ 且 $0 \le x < 998244353$ 。（可以证明这样的整数 $x$ 是唯一的）

## 样例

### 样例输入 #1
```
3
1 2 3
6
0 2 1 1
1 1 2
0 2 1 1
0 3 1 1
1 1 2
1 3 1 2 3
```
### 样例输出 #1
```
1
0
499122177 0 499122177
1 0 2

```
### 样例输入 #2
```
3
1 1 1
4
0 2 1 2
1 2 1 2
0 3 2 3
1 3 1 2 3
```
### 样例输出 #2
```
249561089 748683265
804141285 887328314 305019108
1 499122177 332748118

```
## 提示

### 样例解释 1
针针按顺序施放如下技能：

1. 对敌方单位 $2$ 施放技能锁定：以 $1$ 的概率对其造成 $1$ 点伤害。此时 $2$ 号敌方单位必定剩余 $1$ 点生命值。
2. 对敌方单位 $2$ 施放技能结界：（由于 $2$ 号敌方单位尚存活，）必定命中 $2$ 号单位。
3. 对敌方单位 $2$ 施放技能锁定：以 $1$ 的概率对其造成 $1$ 点伤害。
4. 对敌方单位 $3$ 施放技能锁定：以 $1$ 的概率对其造成 $1$ 点伤害。此时三个敌方单位的生命值一定分别为 $1, 0 ,2$ ，敌方单位 $2$ 一定死亡。
5. 对敌方单位 $2$ 施放技能结界：（由于 $2$ 号敌方单位已死亡，）必定不命中任何单位。
6. 对敌方单位 $1, 2, 3$ 施放技能结界：命中敌方单位 $1, 3$ 的概率是相等的，即各 $\frac{1}{2}$ 。 最终，三个敌方单位的剩余生命值一定为 $1 , 0 , 2$ 。

### 样例解释 2
对于各结界技能的分析：

1. 第 $1$ 个结界（目标为敌方单位 $1,2$ ）：
- $2$ 号敌方单位存活的概率为 $\frac{1}{2}$ ， $1$ 号敌方单位必定存活。
- 如果 $2$ 号敌方单位存活，那么结界命中 $1 , 2$ 的概率相等，均为 $\frac{1}{2}$ ；如果 $2$ 号敌方单位死亡，那么结界必定命中 $1$ 号敌方单位。
- 因此：命中 $1$ 号敌方单位的概率为 $\frac{1}{2} \times 1 + \frac{1}{2} \times \frac{1}{2} = \frac{3}{4}$ ；命中 $2$ 号敌方单位的概率为 $\frac{1}{2} \times 0 + \frac{1}{2} \times \frac{1}{2} = \frac{1}{4}$ 。
2. 第 $2$ 个结界（目标为敌方单位 $1, 2, 3$ ）：
- 三个敌方单位存活的概率分别为 $1, \frac{1}{2} , \frac{1}{3}$ 。
- $1 , 2 , 3$ 同时存活的概率为 $\frac{1}{6}$ ；只有 $1, 2$ 存活的概率为 $\frac{1}{3}$ ；只有 $1 , 3$ 存活的概率为 $\frac{1}{6}$ ；只有 $1$ 存活的概率为 $\frac{1}{3}$ 。
- 因此：命中 $1$ 号敌方单位的概率为 $\frac{1}{6} \times \frac{1}{3} + (\frac{1}{3}+\frac{1}{6}) \times \frac{1}{2}+ \frac{1}{3} \times 1 = \frac{23}{36}$ ；命中 $2$ 号敌方单位的概率为 $\frac{1}{6} \times \frac{1}{3} + \frac{1}{3} \times \frac{1}{2} = \frac{2}{9}$ ；命中 $3$ 号敌方单位的概率为 $\frac{1}{6} \times \frac{1}{3} + \frac{1}{6} \times \frac{1}{2} = \frac{5}{36}$ 。 最终，三个敌方单位的剩余生命值的期望值为 $1 , \frac{1}{2} , \frac{1}{3}$ 。


### 数据范围

我们记 $C$ 为结界技能的数量。

测试点编号|n=|Q=|C=|u,v|其他限制
-|-|-|-|-|-
1|5|21|6|u<v|无
2|60|199992|500|u<v|所有 p 均相等
3|60|23|6|u<v|所有m_i =1
4|60|199994|500|u<v|无
5|60|199995|500|u<v|无
6|60|199996|0|u<v|无
7|60|199997|500|u=v|无
8|200|199998|1000|u<v|无
9|200|199999|1000|u<v|无
10|200|200000|1000|u<v|无

对于所有测试点，保证 $n \le 200 , Q \le 200000 , C \le 1000 , m_i \le 100$ 。

提示

Q 的个位可以帮助你快速确定测试点的编号。
测试点顺序可能与难度无关。

感谢 @和泉正宗 提供题面 


---

---
title: "[SHOI2011] 扫雷机器人"
layout: "post"
diff: 省选/NOI-
pid: P4637
tag: ['2011', '各省省选', '上海', 'Special Judge', '强连通分量', '期望']
---
# [SHOI2011] 扫雷机器人
## 题目描述

扫雷是陆军战场上一项重要的而危险的任务。为此， AL 军工厂专门研制了一种扫雷机器人。这种机器人是专门针对直线形雷阵设计的。所谓直线形雷阵，就是所有的地雷都埋在同一条直线上。例如图中黑点表示的雷阵就是直线形雷阵。

![0](https://cdn.luogu.com.cn/upload/pic/20066.png)

AL 军工厂生产的扫雷机器人的排雷方法只有一种，那就是安全引爆。每次，机器人在所有探测到的地雷中选择一颗引爆。被引爆的地雷会接连引爆不超过他的爆炸威力范围的其它地雷，这些被间接引爆的地雷还能引起进一步的连锁爆炸。例如图中，用一个圆的半径表示地雷的爆炸威力。如果引爆 $2$ 号雷， $1$ 、 $2$ 号雷都会爆炸；如果引爆 $3$ 号雷， $4$ 颗地雷全都会爆炸；而如果引爆 $4$ 号雷，那就只有它一颗爆炸。

虽然是机器人，但引爆也是危险的。所以，扫雷机器人的订购人希望机器人能在实战中采取引爆次数尽可能少的炸毁所有地雷的排雷方案。于是 AL 军工厂想就此方面对机器人进行测试。为了评估机器人的表现， AL 军工厂打算事先计算出：在一个直线形雷阵（即输入的雷阵）中，如果随机进行引爆，完成排雷工作所需要引爆次数的期望；并将这个值与机器人的实际排雷方案相比较，来评估他的表现。

所谓“随机进行引爆”是指，每次在所有没有被引爆的地雷中等概率的随机选择一个进行引爆。当这一次引爆引发的连环爆炸结束后，如果还有地雷没有被引爆，则重复上面的操作，直到所有地雷都被引爆为止。
## 输入格式

输入的第一行是一个正整数 $n$ ，表示地雷的个数。

接下去 $n$ 行，按照地雷的位置顺序，每行描述一颗地雷。其中，第 $i+1$ 行有两个整数 $x_i$ 和 $d_i$ ，分别是地雷的坐标和地雷的爆炸威力。也就是说，第 $i$ 号地雷的爆炸能直接进一步引爆第 $j$ 号地雷的条件是 $|x_i-x_j| \le d$ 。 输入保证： $|x_i| \le 10^8$ ， $1 \le d_i \le 10^8$ 。
## 输出格式

输出只有一行，包含一个实数，即为答案。四舍五入到小数点后四位。
## 样例

### 样例输入 #1
```
4
0 1
2 2
8 7
11 2
```
### 样例输出 #1
```
2.3333
```
### 样例输入 #2
```
3
-10 10
0 1
10 10
```
### 样例输出 #2
```
2.3333
```
### 样例输入 #3
```
2
1 10
2 100
```
### 样例输出 #3
```
1.0000

```
### 样例输入 #4
```
9
1 10
2 10
3 10
4 10
5 10
6 10
7 10
8 10
1000 2000
```
### 样例输出 #4
```
1.8889
```
## 提示

**提示**

本题的试题目录下有 $10$ 个额外的输入样例文件 ``robot20111.in~robot201110.in`` ，以及它们对应的输出样例文件 ``robot20111.out~robot201110.out`` 。这些数据符合本题中关于数据规模的全部约定，但它们不是最终的测试数据。

**[下载地址](https://pan.baidu.com/s/1Q5X52FMH38UYvmrEsVsEkA)**，密码：ypbv。

**评分方式**

在每个测试点，如果您的输出是 $YourAns$ ，而标准答案是 $StdAns$ ，那么：

-    当 $ |YourAns-StdAns| \le 0.0001$ 时，该测试点得 $10$ 分。

-    当 $0.01 \ge |YourAns-StdAns| > 0.0001$ 时，该测试点得 $6$ 分。

-    当 $0.5 \ge |YourAns-StdAns| > 0.01$ 时，该测试点得 $2$ 分。

-    否则得 $0$ 分。

**数据范围**

测试点 $1$：$n \le 20$。

测试点 $2$：$n \le 200$ ，且任意方案都保证引爆次数不超过 $20$。

测试点 $3$：$n \le 200$。

测试点 $4 \sim 5$：$n \le 4000$ ，且任意方案都保证引爆次数不超过 $20$。

测试点 $6 \sim 10$：$n \le 4000$。


---

---
title: "yyf hates choukapai"
layout: "post"
diff: 省选/NOI-
pid: P4852
tag: ['动态规划 DP', '2018', '单调队列', '洛谷原创', 'Special Judge', '前缀和', '期望', '队列']
---
# yyf hates choukapai
## 题目背景

非酋yyf总是抽不到自己想要的卡，因此还十分讨厌抽卡。但玩sif不可能不抽卡，于是他去请教了一下欧皇dew。dew告诉了他关于抽卡的秘密，然而yyf还是不知道如何让自己欧气尽量地大，于是他找到了你。
## 题目描述

dew告诉yyf，人在抽每张卡时欧气值都是固定的，第 $i$ 张卡的欧气值为 $a_i$ ，而在连抽时，欧气值等于第一张卡的欧气值。

“每次抽卡的欧气之和”指每次单抽的欧气之和加上每次连抽的欧气之和，一次连抽的欧气不加权，只计算一次

yyf想 $c$ 连抽（连续抽 $c$ 张卡） $n$ 次，单抽 $m$ 次，因为一直单抽太累，**yyf不想连续单抽超过 $d$ 次（可以连续单抽恰好 $d$ 次）**。共有 $c*n+m$ 张卡，抽卡的顺序不能改变，每张卡都必须且只能抽一次，只能改变哪几张卡连抽、哪几张卡单抽。那么yyf每次抽卡的欧气之和最多能达到多少，又如何实现呢？
## 输入格式

第 $1$ 行 $4$ 个正整数 $n\ m\ c\ d$

第 $2$ 行 $c*n+m$ 个正整数，其中第 $i$ 个正整数 $a_i$ 代表第 $i$ 张卡的欧气值
## 输出格式

第 $1$ 行一个正整数代表yyf每次抽卡的欧气之和的最大值

第 $2$ 行 $n$ 个正整数代表每次连抽的第一张卡的编号，如果有多种方案满足要求任意输出一种 （如果不会输出方案也请在第二行随意输出 $n$ 个整数，否则可能 $0$ 分）

方案请升序输出
## 样例

### 样例输入 #1
```
3 3 3 3
2 7 1 4 5 3 6 8 5 1 2 9
```
### 样例输出 #1
```
36
2 5 9
```
### 样例输入 #2
```
2 5 2 2
7 3 3 7 7 5 1 10 2
```
### 样例输出 #2
```
41
2 6 
```
## 提示

$20\%$的数据有$1 \le n \le 5$，$1 \le m \le 5$，$2 \le c \le 5$

$50\%$的数据有$1 \le n \le 40$，$1 \le m \le 200$，$2 \le c \le 20$

另有$20\%$的数据有$d=m$

$100\%$的数据有$1 \le n \le 40$，$1 \le m \le 80000$，$2 \le c \le 3000$，$1 \le a_i \le 10000$，$1 \le d \le m$，$d*(n+1) \ge m$

共 $10$ 个测试点，每个测试点答案错误 $0$ 分，答案正确方案错误 $6$ 分，答案正确方案正确 $10$ 分。

样例解释：输出的方案就是样例解释了QAQ

样例一：单抽 $1$ ，连抽 $2$~$4$，连抽 $5$~$7$，单抽 $8$，连抽 $9$~$11$，单抽 $12$，欧气值总和为 $2+7+5+8+5+9=36$

样例二：单抽 $1$ ，连抽 $2$~$3$，单抽 $4$，单抽 $5$，连抽 $6$~$7$，单抽 $8$，单抽 $9$，欧气值总和为 $7+3+7+7+5+10+2=41$

可以证明在满足条件的情况下上述两种方案是欧气值总和最大的


---

---
title: "yyf hates dagequ"
layout: "post"
diff: 省选/NOI-
pid: P4853
tag: ['动态规划 DP', '递推', '2018', '洛谷原创', 'Special Judge', '期望']
---
# yyf hates dagequ
## 题目背景

非酋yyf在dew的指点下抽到了不错的卡，但他还是太非了，对于随机触发的技能，他总是无法触发。yyf想知道自己究竟有多非，所以他请你来计算他的期望得分，与自己的得分来比较。

## 此题已放宽精度限制并显示错误答案和正确答案，请不要以此面向数据
## 题目描述

给你一些卡牌的技能，技能分为$2$种类型：
1. 加分，每连击$c$次有$p\%$的概率加$s$分
2. 改判，每连击$c$次有$p\%$的概率触发强判定效果，持续$t$个节奏图标（设连击数为$c$的倍数时为第$i$个节奏图标，则强判定效果在第$[i+1,i+t]$个节奏图标被触发）

这些技能在连击数为$c$的倍数且连击数不为$0$时有概率触发，多个技能可以同时触发

其中，加分技能有 $\mathrm{score}$ 个，改判技能有 $\mathrm{judge}$ 个

再给你$n$个节奏图标（yyf是按给出的顺序击打的）yyf击打的原始（相对于“强判定效果”修正后）结果，分为$2$，$1$，$0$三种

在“强判定效果”的持续期间内所有的击打结果$1$会视作击打结果$2$，击打结果$0$仍视作击打结果$0$，击打结果$2$仍视作击打结果$2$ 。下文中的“击打结果”若无说明均指修正后的击打结果。

“连击数”的定义为到目前为止连续的击打结果为$2$的次数（若这次的击打结果为$2$则这次击打也算入当前的连击数，否则当前的连击数为$0$）

多个“强判定效果”可以重叠，但持续时间不会叠加（设当前“强判定效果”剩余时间为 $t_1$，此时同时触发两个“强判定效果”，持续时间分别为 $t_2$ 和 $t_3$ ，则下一次击打时的“强判定效果”剩余时间为 $\max(t_1-1,t_2,t_3)$）。

一次击打的得分为这次的击打结果乘以当前的连击数加一。即：设当前的击打结果为 $x$ ，当前的连击数为 $\mathrm{combo}$ ，则这次击打的得分为 $\mathrm{x*(combo+1)}$

最终得分为每次（共$n$次）击打的得分之和加上加分技能的加分之和

请求出yyf这次打歌的期望得分
## 输入格式

第一行三个非负整数 $\mathrm{n\ score\ judge}$

下面的 $\mathrm{score}$ 行，每行三个正整数 $c\ p\ s$，代表一个加分技能

下面的 $\mathrm{judge}$ 行，每行三个正整数 $c\ p\ t$，代表一个改判技能

最后一行 $n$ 个整数，每个整数都∈$[0,2]$，第 $i$ 个整数代表第 $i$ 次击打的原始结果
## 输出格式

共一行一个实数代表yyf的期望得分，与答案的相对误差在 $10^{-5}$ 内算对
## 样例

### 样例输入 #1
```
4 1 1
3 70 3
2 20 1
2 2 1 1
```
### 样例输出 #1
```
13.82
```
### 样例输入 #2
```
5 0 2
2 60 1
2 10 2
2 2 1 1 1
```
### 样例输出 #2
```
19.084
```
### 样例输入 #3
```
5 0 0
2 1 0 2 2
```
### 样例输出 #3
```
15
```
## 提示

### 数据范围

对于全部的测试点，有：$5 \le n \le 1000$，$0 \le \mathrm{score} \le 1000$，$0 \le \mathrm{judge} \le 1000$，$1 \le c \le 5$，$1 \le p \le 99$，$1 \le s \le 10$，$1 \le t \le 5$。

| 测试点编号 | $n$ | $\mathrm{score}$ | $\mathrm{judge}$ | 特殊限制 | 测试点编号 | $n$ | $\mathrm{score}$ | $\mathrm{judge}$ | 特殊限制 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $1000$ | $\ \,0\ \,$ | $\ \,0\ \,$ | 所有 $a_i$ 均为 $2$ | $11$ | $1000$ | $\ \,0\ \,$ | $\ \,9\ \,$ | 无 |
| $2$ | $1000$ | $0$ | $0$ | 无 | $12$ | $1000$ | $2$ | $2$ | 无 |
| $3$ | $1000$ | $1$ | $0$ | 无 | $13$ | $1000$ | $3$ | $3$ | 无 |
| $4$ | $1000$ | $9$ | $0$ | 无 | $14$ | $1000$ | $3$ | $6$ | 无 |
| $5$ | $1000$ | $1000$ | $0$ | 无 | $15$ | $1000$ | $1$ | $8$ | 所有 $c$ 均为 $1$ |
| $6$ | $50$ | $1$ | $1$ | 无 | $16$ | $1000$ | $0$ | $9$ | 所有 $c$ 均为 $1$ |
| $7$ | $50$ | $2$ | $2$ | 无 | $17$ | $1000$ | $1000$ | $1000$ | 所有 $c$ 均为 $1$ |
| $8$ | $50$ | $4$ | $4$ | 无 | $18$ | $1000$ | $1000$ | $1000$ | 所有 $c$ 均为 $1$ |
| $9$ | $50$ | $0$ | $9$ | 无 | $19$ | $1000$ | $1000$ | $1000$ | 无 |
| $10$ | $50$ | $4$ | $5$ | 无 | $20$ | $1000$ | $1000$ | $1000$ | 无 |

### 样例1解释

![](https://cdn.luogu.com.cn/upload/image_hosting/lc16fxxt.png)

### 样例2解释

![](https://cdn.luogu.com.cn/upload/image_hosting/rd4khzu1.png)

### 样例3解释

第一次4分，第二次1分，第三次0分，第四次4分，第五次6分


---

---
title: "规划"
layout: "post"
diff: 省选/NOI-
pid: P4982
tag: ['动态规划 DP', 'O2优化', '期望', '构造']
---
# 规划
## 题目背景

经过长期的艰苦奋斗，${\rm TimeTraveller\ }$终于成功进入了理想的学校。
## 题目描述

作为吃货的${\rm \ TimeTraveller}$，入学的第一件事不是去报到，而是去食堂调查菜品。但是由于各种原因，本学期食堂的菜品很少，而且食堂制定了几天的菜谱，那么这个学期里，以后每天提供的菜品都会**按照菜谱轮流循环进行**。听到这件事，${\rm TimeTraveller\ }$的内心当然是崩溃的，但是他还是希望每天能吃的不那么重复，于是${\rm \  TimeTraveller\ }$决定只要**和前一天吃的菜不重复**就行了，但是身为吃货的${\rm \ TimeTraveller\ }$当然也不想饿肚子，所以**每天至少都要吃一道菜**。

${\rm TimeTraveller\ }$想要知道他有多少种合法的规划方案，但是他发现这实在是太多了，于是他来求助你，希望你能编写一个程序帮他计算。

## 输入格式

第一行三个正整数$n,m,k$，分别表示这个学期有$n$天，总共有$m$种菜品，学校制定了$k$天的菜谱（所有菜品从$1$到$m$编号，保证$n ≥ k$）。

接下来$k$行，每行第一个数$p$表示这一天学校准备了$p$道菜，紧接着有$p$个数，表示这一天的$p$道菜分别是哪几道（保证$p$不会超过$m$，且这$p$个数都是不重复的）。

## 输出格式

输出合法方案的数量，由于答案可能过大，你只需要输出答案对$1e9+7$取模后的值。
## 样例

### 样例输入 #1
```
3 3 2
2 1 3
2 2 3

```
### 样例输出 #1
```
11
```
### 样例输入 #2
```
10 7 3
5 1 2 3 4 5
3 1 3 7
4 1 2 6 7

```
### 样例输出 #2
```
730285459
```
## 提示

#### 样例$1$解释：

方案$1$：第一天吃$1,3$号菜品，第二天吃$2$号菜品，第三天吃$1,3$号菜品；

方案$2$：第一天吃$1,3$号菜品，第二天吃$2$号菜品，第三天吃$3$号菜品；

方案$3$：第一天吃$1,3$号菜品，第二天吃$2$号菜品，第三天吃$1$号菜品；

方案$4$：第一天吃$3$号菜品，第二天吃$2$号菜品，第三天吃$1,3$号菜品；

方案$5$：第一天吃$3$号菜品，第二天吃$2$号菜品，第三天吃$3$号菜品；

方案$6$：第一天吃$3$号菜品，第二天吃$2$号菜品，第三天吃$1$号菜品；

方案$7$：第一天吃$1$号菜品，第二天吃$2,3$号菜品，第三天吃$1$号菜品；

方案$8$：第一天吃$1$号菜品，第二天吃$3$号菜品，第三天吃$1$号菜品；

方案$9$：第一天吃$1$号菜品，第二天吃$2$号菜品，第三天吃$1,3$号菜品；

方案$10$：第一天吃$1$号菜品，第二天吃$2$号菜品，第三天吃$3$号菜品；

方案$11$：第一天吃$1$号菜品，第二天吃$2$号菜品，第三天吃$1$号菜品。

#### 数据范围：

- 对于$20\%$的数据，$n≤ 5,m≤ 7,k≤ 5$；

- 对于$45\%$的数据，$n≤ 50000,m≤ 7,k≤ 7$；

- 另有$10\%$的数据，$n≤ 10^7,m≤ 2,k= 1$；

- 对于$70\%$的数据，$n≤ 10^7,m≤ 7,k≤ 7$；

- 对于$100\%$的数据，$n≤ 10^7,m≤ 7,k≤ 300$。


---

---
title: "转换"
layout: "post"
diff: 省选/NOI-
pid: P4984
tag: ['进制', '期望']
---
# 转换
## 题目背景

$\rm hdxrie\ $最近在为新建的宇宙购物中心编写价格系统。
## 题目描述

购物中心汇聚了来自各个星球的商品，但是由于不同的星球采用的进制各不相同，导致商品价格计算起来比较困难，因此价格系统是必不可少的。

由于甲方所给的期限太短，$\rm hdxrie\ $便找到你来做他的助手，他只需要你帮忙编写一个进制转换的程序就行，其它的各个系统版块全部由他自己负责，你能在规定期限内写出转换程序吗？
## 输入格式

第一行一个数$n$，$n$表示有多少个物品的价格需要转换。

接下来$n$行，每行三个数字$a,l,r$和一个价格串$S$。

$a$表示这个价格串为$a$进制数（保证$a$不为$-1,0,1$），你需要把它转化为$l$到$r$的所有进制（请自动跳过输出为$-1,0,1$这些进制的情况）。

由于价格为实数，所以难免会出现小数，并且若一个小数为循环小数，我们会将小数的循环节使用 <,> 括起来。

如果不是循环小数则没有尖括号，如果没有小数部分则没有小数点，保证不会出现尖括号之间没有数字情况。

保证循环节以及循环节前面的小数部分都是最短的，例如$10$进制下的$0.123123\cdots$，那么所给的读入形式为$0.$<$123$>，保证不会出现类似于$0.1$<$231$>或$0.$<$123123$>这些情况。

对于正进制$a$，保证不会出现循环节为$a-1$的情况，例如$10$进制不会出现$0.$<$9$>这样的输入，但是负进制没有这样的要求。

为了方便转换，当用正进制表示负数的时候，规定在价格前加上负号，但是由于负进制既可表示正数也可表示负数，所以规定负进制前不允许出现负号。

规定任意进制的每一位不能为负，规定大于$9$的值按照大写字母从小到大编写。
## 输出格式

对于每一个需要转换的价格，在给定范围内按进制从小到大的顺序输出转换为该进制后的价格串（请自动跳过输出为$-1,0,1$这些进制的情况）。

对于输出格式你也应该严格按照上面输入格式的要求输出每一个价格串。
## 样例

### 样例输入 #1
```
2
10 2 4 72451
-3 -4 2 123456

```
### 样例输出 #1
```
10001101100000011
10200101101
101230003
2021
122000
10001001
-10000111
```
### 样例输入 #2
```
2
8 2 2 176336030760401.6
30 35 36 HQA9MBFD3SEC.<GAR85DJ2LO>

```
### 样例输出 #2
```
1111110011011110000011000111110000100000001.11
39SAWRJ5CPP7.<J36CPFVSM9>
2EMEUXKKZHA0.<JMWQ6>
```
### 样例输入 #3
```
1
-26 -6 -6 1PMMK.<L15>

```
### 样例输出 #3
```
1213400.<511>
```
## 提示

- 对于$5\%$的数据，保证没有小数部分，$1≤n≤20,2≤a≤36,2≤l≤r≤36$；

- 对于$15\%$的数据，保证没有小数部分，$1≤n≤100,2≤|a|≤36,-36≤l≤r≤36$；

- 另有$15\%$的数据，保证转换前和转换后都是有限小数，$1≤n≤550,2≤a≤36,2≤l≤r≤36$；

- 另有$20\%$的数据，$1≤n≤550,2≤a≤36,2≤l≤r≤36$；

- 对于$100\%$的数据，$1≤n≤550,2≤|a|≤36,-36≤l≤r≤36$；

保证所有数据中，价格的绝对值都不会超过$2^{63}-1$，且转换前和转换后的小数部分的字符串长度均不超过$\left\lfloor\log_{|a|}2^{62}\right\rfloor$（$a$表示进制，括号不计入长度）。


---

---
title: "[USACO18DEC] Balance Beam P"
layout: "post"
diff: 省选/NOI-
pid: P5155
tag: ['数学', '2018', 'USACO', '期望', '凸包']
---
# [USACO18DEC] Balance Beam P
## 题目描述

Bessie为了存钱给她的牛棚新建一间隔间，开始在当地的马戏团里表演，通过在平衡木上小心地来回走动来展示她卓越的平衡能力。

Bessie能够通过表演赚到的钱取决于她最终成功跳下平衡木的位置。平衡木上从左向右的位置记为 $ 0,1,\ldots,N+1 $ 。如果Bessie到达了位置 $ 0 $ 或是 $ N+1 $ ，她就会从平衡木的一端掉下去，遗憾地得不到报酬。

如果Bessie处在一个给定的位置 $ k $ ，她可以进行下面两项中的任意一项：

1. 投掷一枚硬币。如果背面朝上，她前往位置 $ k-1 $ ，如果正面朝上，她前往位置 $ k+1 $ （也就是说，每种可能性 $ 1/2 $ 的概率）。

2. 跳下平衡木，获得 $ f(k) $ 的报酬（ $ 0 \leq f(k) \leq 10^9 $ ）。

Bessie意识到她并不能保证结果能够得到某一特定数量的报酬，这是由于她的移动是由随机的掷硬币结果控制。然而，基于她的起始位置，她想要求出当她进行一系列最优的决定之后，她能够得到的期望报酬（“最优”指的是这些决定能够带来最高可能的期望报酬）。

例如，如果她的策略能够使她以 $ 1/2 $ 的概率获得 $ 10 $ 的报酬，$ 1/4 $ 的概率获得 $ 8 $ 的报酬，$ 1/4 $ 的概率获得 $ 0 $ 的报酬，那么她的期望报酬为加权平均值 $ 10 \times (1/2)+8 \times (1/4)+0 \times (1/4)=7 $ 。
## 输入格式

输入的第一行包含 $ N $ （ $ 2 \leq N \leq 10^5 $ ）。以下 $ N $ 行包含 $ f(1) \ldots f(N) $ 。
## 输出格式

输出 $ N $ 行。第 $ i $ 行输出 $ 10^5 $ 乘以Bessie从位置 $ i $ 开始使用最优策略能够获得的报酬的期望值，向下取整。
## 样例

### 样例输入 #1
```
2
1
3
```
### 样例输出 #1
```
150000
300000

```


---

---
title: "【XR-2】约定"
layout: "post"
diff: 省选/NOI-
pid: P5437
tag: ['数学', '生成树', '期望', '逆元']
---
# 【XR-2】约定
## 题目背景

>「小圆，不要走！这一分离，我们何时才能重逢？」
>
>「小焰，我们一定还会相见的！在那之前，我们只是短暂的离别啊......」
## 题目描述

只因为那一句约定，小焰开始了看不到尽头的等待。

约定在小焰心中幻化成了一张 $n$ 个点的图。一开始，这是一张完全图，其中点的编号从 $1$ 到 $n$，连接点 $i,j$ 的边的权值为 $(i+j)^k$。

然而等待的过程中，岁月也在逐渐消磨着她的信仰，因此图中的一些边被随机地删掉了。最终，图变成了一棵 $n$ 个点的树，永远地留在了小焰的心中。

很久很久以后，小焰的魔力耗尽，在痛苦与绝望之中濒临崩溃。而就在这时，小圆终于来找小焰了。为了拯救自己唯一的朋友，她必须知道这棵树边权和的期望值对 $998244353$ 取模的结果是多少。

你能帮小圆求出答案，让她完成那个约定吗？
## 输入格式

一行两个正整数 $n,k$。
## 输出格式

一行一个整数，表示答案对 $998244353$ 取模后的值。
## 样例

### 样例输入 #1
```
3 1

```
### 样例输出 #1
```
8

```
### 样例输入 #2
```
4 3

```
### 样例输出 #2
```
450

```
### 样例输入 #3
```
1926 817

```
### 样例输出 #3
```
984167516

```
## 提示

【样例 $1$ 说明】

这个完全图有 $3$ 个节点，$3$ 条边，形成了一个环。  
这些边的权分别为：$3,4,5$   
最后形成的树也有 $3$ 种可能，权值分别为：$7,8,9$  
期望值为 $8$。

【数据规模与约定】

**本题采用捆绑测试。**

Subtask 1（5 points）：$1 \le n \le 5$，$1\le k \le 10$。     
Subtask 2（11 points）：$k = 1$。  
Subtask 3（11 points）：$1 \le n,k \le 20000$。  
Subtask 4（13 points）：$1 \le n,k \le 10^5$。   
Subtask 5（23 points）：$1 \le k \le 10^5$。  
Subtask 6（37 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le n \le 998244352,1\le k \le 10^7$。
****
>「抱歉，让你久等了...... 你一直努力到了今天吧......」  
>
>「小圆......」
>
>「来，我们走吧。今后我们永不分离......」
>
>「是啊，我等这一刻——望眼欲穿。」


---

---
title: "【XR-2】约定 (加强版)"
layout: "post"
diff: 省选/NOI-
pid: P5442
tag: ['数学', 'O2优化', '期望', '逆元']
---
# 【XR-2】约定 (加强版)
## 题目背景

原题链接：[P5437](https://www.luogu.org/problemnew/show/P5437)

其实在比赛时就想放上这个加强版了qwq    
但是团队成员都强烈反对，于是就在赛后放上来啦
## 题目描述

有一个 $n$ 个点的完全图，编号从 $1$ 到 $n$。  
连接 $i$ 和 $j$ 节点的边，权值为 $(i+j)^k$。  
定义一棵树的权值为其所有边的权值和。  
从这个图的所有生成树中随机选择一个，求其权值的期望。  
需要将答案对 $998244353$ 取模。
## 输入格式

一行两个正整数 $n,k$。
## 输出格式

一行一个整数表示答案对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
3 1
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
4 3
```
### 样例输出 #2
```
450
```
### 样例输入 #3
```
1926 817
```
### 样例输出 #3
```
984167516
```
### 样例输入 #4
```
998244353 1
```
### 样例输出 #4
```
998244352
```
## 提示

### 数据范围：   
$1\le n \le 10^{10000}$  
$1\le k \le 10^7$



---

---
title: "[MtOI2019] 小铃的烦恼"
layout: "post"
diff: 省选/NOI-
pid: P5516
tag: ['动态规划 DP', '2019', '洛谷原创', 'O2优化', '期望']
---
# [MtOI2019] 小铃的烦恼
## 题目背景

在幻想乡中，本居 小铃(Motoori Kosuzu)不仅经常被人撞，还要整理铃奈庵的书籍，她有很多烦恼。
## 题目描述

小铃每天都会整理一次铃奈庵的书籍。这次桌子上有 $n$ 本魔法书，这些书一次排成一排，每本书有一个魔法属性和编号。

最开始这些书的魔法属性都是一样的，但是因为被人多次使用，魔法属性发生了变化，小铃想让所有书的魔法属性重新全部相同。

这次小铃找到了雾雨 魔理沙(Kirisame Marisa)帮忙整理书籍，每次魔理沙可以释放选定魔法，魔法会随机选择两本书 $a,b$ ( $a$ 不等于 $b$ )。

选定这两本书后，魔理沙会释放转移魔法，使得有 $p_{a,b}\ (p_{a,b}\in (0,1])$ 的概率，第 $b$ 本书的魔法属性变成第 $a$ 本书的魔法属性。也就是说有 $1-p_{a,b}$ 的概率，使得你**即使选定了 $a,b$ 两本书，但是魔法属性的转移不成功，意味着这次操作是无效的** 。

注意 $p_{a,b}$ 是对于**转移是否成功的概率**，和随机选择两本书的操作互不影响。

现在小铃想知道，求期望操作多少次，才能使所有的书魔法属性都一样？由于时间紧迫，小铃找到了你，希望你可以帮其解决这个问题，不然小铃就不会给你这题的分了。
## 输入格式

第一行一个字符串，第 $i$ 个字符表示第 $i$ 本书的魔法属性，注意每本书的魔法属性为 $A$ 到 $Z$ 的所有的大写字母中的任意一字母。(设字符串的长度为 $n$ ) 。

第二行到第 $n+1$ 行，每行 $n$ 个实数，第 $i$ 行的第 $j$ 个数表示 $p_{i,j}$ 。
## 输出格式

结果，精确到小数点后 $1$ 位。
## 样例

### 样例输入 #1
```
NACLYFISHAKIOI
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
```
### 样例输出 #1
```
164.9
```
### 样例输入 #2
```
DSGAY
1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0


```
### 样例输出 #2
```
16.0
```
## 提示

对于前 $10\%$ 的数据，$n\leq 10$，且最多有一种不同的魔法属性。

对于另外 $20\%$ 的数据，$n\leq10$，且最多有两种不同的魔法属性，并且其中一种的魔法属性的个数小于等于 $1$  。

对于 $100\%$ 的数据，$n\leq2\times 10^3$ 。

对于所有数据，满足 $\left(\sum\limits_{a=1}^{n}\sum\limits_{b=1}^{n}p_{a,b}\right) = n^2$ 。

### 题目来源

[迷途之家2019联赛](https://www.luogu.org/contest/20135)(MtOI2019) T3

出题人：Qiuly 



---

---
title: "[CmdOI2019] 黑白图"
layout: "post"
diff: 省选/NOI-
pid: P5575
tag: ['动态规划 DP', '期望']
---
# [CmdOI2019] 黑白图
## 题目背景

你看见了一张奇怪的图。
## 题目描述

有一张 $n$ 个点，$m$ 条边的简单无向连通图，点可以染上黑色或者白色。

这个图比较稀疏，具体来讲有两种情况。

- $m=n-1$ ，此时是一棵树。

- $m=n$ ，此时是一颗基环树。

我们定义一张黑白图的权值为：其黑色**连通块大小**的 $k$ 次方和。

现在图的形态已经确定，但是每个点上的颜色尚未确定，对于第 $i$ 个点。其有**百分之** $p_i$ 的可能是黑色，反之则是白色。

求图的期望权值对 $998244353$ 取模的结果。
## 输入格式

第一行包括三个正整数 $n,m,k$ ，意义如题面所述。

接下来一行 $n$ 个数依次表示 $p_{1\sim n}$。

后 $m$ 行，每行两个数 $f,t$ ，表示图的一条无向边 $f\leftrightarrow t$ 。
## 输出格式

输出一个整数，表示图的期望权值对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
5 4 3
50 50 50 50 50
1 2
2 3
2 4
2 5
```
### 样例输出 #1
```
19
```
### 样例输入 #2
```
6 5 2
20 30 40 50 60 70
1 2
2 3
2 4
2 5
4 6
```
### 样例输出 #2
```
397301258
```
### 样例输入 #3
```
10 10 2
39 76 71 86 36 38 36 44 63 37 
4 5
2 10
6 10
1 8
5 10
8 10
7 10
3 10
10 9
5 3
```
### 样例输出 #3
```
361859252
```
## 提示

| 数据点编号 | $n$ | 　$m$　 | 　$k$　 | 性质1 | 性质2 | 分数 |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| 1 | $16$ | $n-1$ | $5$ | $\sqrt{}$ | - | $5$ |
| 2 | $50$ | $n-1$ | $3$ | $\sqrt{}$ | $\sqrt{}$ | $5$ |
| 3 | $50$ | $n-1$ | $5$ | $\sqrt{}$ | - | $5$ |
| 4 | $500$ | $n-1$ | $1$ | - | - | $5$ |
| 5 | $2\times 10^5$ | $n-1$ | $3$ | $\sqrt{}$ | $\sqrt{}$ | $5$ |
| 6 | $2\times 10^5$ | $n-1$ | $2$ | - | $\sqrt{}$ | $5$ |
| 7 | $2\times 10^5$ | $n-1$ | $4$ | - | - | $10$ |
| 8 | $16$ | $n$ | $3$ | - | - | $10$ |
| 9 | $500$ | $n$ | $3$ | - | - | $10$ |
| 10 | $50000$ | $n$ | $2$ | - | - | $10$ |
| 11 | $2\times 10^5$ | $n$ | $4$ | $\sqrt{}$ | - | $10$ |
| 12 | $2\times 10^5$ | $n$ | $5$ | - | - | $10$ |
| 13 | $2\times 10^5$ | $n$ | $5$ | - | - | $10$ |

特殊性质 $1$ ：$p_i=50$。

特殊性质 $2$ ：图退化成一条链，其中 $i$ 向 $i+1$ 连边。


---

---
title: "[MtOI2019] 恶魔之树"
layout: "post"
diff: 省选/NOI-
pid: P5616
tag: ['动态规划 DP', '数学', '2019', '洛谷原创', 'O2优化', '期望', '洛谷月赛']
---
# [MtOI2019] 恶魔之树
## 题目背景

在 Kirito 和 Eugeo 还没有与 Alice 前往北之洞窟的时候，Eugeo 每天只能用龙骨斧砍恶魔之树——基家斯西达……

![](https://cdn.luogu.com.cn/upload/image_hosting/95swctde.png)

~~请忽略bilibili的水印~~
## 题目描述

Kirito 和 Eugeo 每天砍树觉得很无聊，于是开始比谁砍出好声音的次数多。渐渐地，他们发现这样也没有意思了，于是在这个基础上改了一点：

每个人去砍树前，会随机得到一个长度为 $n$ 的数列 $s_1, s_2, \dots, s_n$ 。最初每个人的得分都是 $1$，当第 $i$ 次砍出了一个好声音时，得分就变成了原来的得分与 $s_i$ 的最小公倍数，也就是常说的 ${\rm lcm}$。

现在 Kirito 已经得到了一个长度为 $n$ 的数列 $s_1, s_2, \ldots, s_n$ 。他想知道，如果每一次砍出好声音的概率是 $50\%$ 时他的期望得分。

由于 Kirito 不想看到小数，所以请你告诉 Kirito 答案乘 $2^n$ 对 $p$ 取模的值。
## 输入格式

共 $2$ 行。

第 $1$ 行包含 $2$ 个正整数 $n$ 和 $p$ ，代表数列的长度和给定的模数。**保证模数为质数**

第 $2$ 行包含 $n$ 个正整数，第 $i$ 个数代表 $s_i$。
## 输出格式

共 $1$ 行，包含 $1$ 个正整数，代表得分的期望值乘 $2^n$ 对 $p$ 取模的结果。

## 样例

### 样例输入 #1
```
3 998244353
1 2 3
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
10 998244353
1 2 3 4 5 6 7 8 9 10
```
### 样例输出 #2
```
516032
```
## 提示

#### 样例解释 1

一共有 $8$ 种情况：

- 没有出现好声音，得分为 $1$，概率为 $\frac{1}{8}$。

- 只有第一次出现了好声音，得分为 $1$，概率为 $\frac{1}{8}$。

- 只有第二次出现了好声音，得分为 $2$，概率为 $\frac{1}{8}$。

- 只有第三次出现了好声音，得分为 $3$，概率为 $\frac{1}{8}$。

- 只有第三次没有出现好声音，得分为 $\operatorname{lcm}(1, 2)=2$，概率为 $\frac{1}{8}$。

- 只有第二次没有出现好声音，得分为 $\operatorname{lcm}(1, 3)=3$，概率为 $\frac{1}{8}$。

- 只有第一次没有出现好声音，得分为 $\operatorname{lcm}(2, 3)=6$，概率为 $\frac{1}{8}$。

- 每一次都砍出了好声音，得分为 $\operatorname{lcm}(1, 2, 3)=6$，概率为 $\frac{1}{8}$。

所以期望值为 $\frac{1}{8}+\frac{1}{8}+\frac{2}{8}+\frac{3}{8}+\frac{2}{8}+\frac{3}{8}+\frac{6}{8}+\frac{6}{8}=3$

乘上 $2^3$ 得到答案为 $24$。

### 子任务

本题采用捆绑测试。

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^5$，$10^7 \leq p \leq 1.1 \times 10^9$且$p$为质数，$1\leq s_i\leq 300$。

本题共 $7$ 个子任务，各子任务的分值和限制如下：

子任务 $1$（$3$ 分）：$n=1$。

子任务 $2$（$7$ 分）：$n=18$。

子任务 $3$（$10$ 分）：$n=100$，$s$ 中不同的正整数不超过 $18$ 个。

子任务 $4$（$20$ 分）：$n=100$，不存在 $1\leq i \neq j \leq n$，使得 $s_i=s_j$。且保证数据随机。

子任务 $5$（$20$ 分）：$1\leq s_1, s_2, \ldots, s_n \leq 100$。

子任务 $6$（$20$ 分）：$1\leq n \leq 10^4$。

子任务 $7$（$20$ 分）：无特殊限制。

------

谨以此题庆祝刀剑10周年。~~好像晚了几个月...~~


### 题目来源

[MtOI2019 Extra Round](https://www.luogu.org/contest/22840) T4

出题人：CYJian 

验题人：suwAKow



---

---
title: "[CTSC2013] 没头脑和不高兴"
layout: "post"
diff: 省选/NOI-
pid: P5883
tag: ['2013', '线段树', 'Special Judge', '期望', 'CTSC/CTS']
---
# [CTSC2013] 没头脑和不高兴
## 题目描述

没头脑和不高兴是一对形影不离的好朋友，他们一起上学也一起玩耍。

这天，这对好朋友聚在一起玩纸牌游戏。他们所玩的纸牌总共有 $N$ 张，每一张上面都有一个 $1-N$ 的数字，任意两张纸牌上的数字都不相同。根据他们制定的游戏规则，在每局游戏的开始，所有的牌需要按照从 $1-N$ 的顺序排好。在开心地玩完了一局牌之后，他们发现牌的顺序被弄得乱七八糟，将它们排好序是一件挺麻烦的事情。

他们将凌乱的纸牌在桌面上排成一排，然后开始了排序工作。不高兴由于在上一局游戏中输了牌，非常不高兴。他只将其中**奇数位置**的牌排成了升序，然后把剩下的任务推给了没头脑。没头脑非常没头脑，他采取了一个有些笨的排序方式。每次，他找到两张相邻并且顺序不对的牌交换它们，直到整个序列被排好序为止。

乐于探究的你，想要研究在初始排列随机的情况下没头脑花在交换纸牌上的时间。假设没头脑每交换一对纸牌花费的时间为 $1$，你希望求出他排序时间的期望。此外，为了更好地分析这个问题，你还希望能够计算出所花时间的方差。更进一步地，如果**被不高兴排好序的位置发生了变化**，你是否还能求出没头脑用来排序时间的期望呢？
## 输入格式

- 输入文件共 $M+1$ 行。
- 第一行包含两个正整数 $N$,$M$。
- 接下来 $M$ 行，每行包含三个整数 $l$,$r$,$v$。其中 $1 \le l \le r \le n$，$v\in\{0,1\}$。若 $v=0$ 则表示不高兴不再对 $l$ 到 $r$ 之间的位置排序；反之若 $v=1$ 则表示被不高兴排序的位置将涵盖 $l$ 到 $r$。
## 输出格式

- 输出文件共 $M+2$ 行。每行输出一个形如 `p/q` 的有理数，其中 $\gcd(p,q)=1$，$q \ne 1$，$p,q \in Z$。
- 第一行输出在初始条件下没头脑排序时间的期望。
- 第二行输出在初始条件下没头脑排序时间的方差。
- 接下来 $M$ 行，每行分别输出在对不高兴排序的位置进行了前若干次修改之后没头脑排序时间的期望。
## 样例

### 样例输入 #1
```
3 3
2 3 0
2 2 1
1 3 1

```
### 样例输出 #1
```
2/3
2/9
3/2
1/1
0/1

```
## 提示

**样例说明**

在初始条件下，不高兴会将位置 $1$ 和 $3$ 的纸牌排好顺序。对于排列 $(1,2,3)$ 和 $(3,2,1)$，他将排列成 $(1,2,3)$，没头脑不需要操作；对于排列 $(1,3,2)$ 和 $(2,3,1)$，他将排列成 $(1,3,2)$ ，没头脑需要交换一次；对于排列 $(2,1,3)$ 和 $(3,1,2)$，他将排列成 $(2,1,3)$，没头脑需要交换一次。因此没头脑所花的时间期望为$\frac{0 \times 2+1 \times 2+1\times 2}{6}=\frac{2}{3}$；方差为 $\frac{ (0-\frac{2}{3})^2 \times 2 + (1-\frac{2}{3})^2 \times 2+(1-\frac{2}{3})^2 \times 2 }{6}=\frac{2}{9}$。

在进行了第一次修改之后，不高兴会只对位置 $1$ 排序，这和没有排序的效果一样；第二次修改之后，他会对位置 $1$,$2$ 排序；最后一次修改之后，他会对位置 $1$,$2$,$3$ 排序，这样没头脑完全不用参与排序工作。可据此求出对应情况下没头脑排序时间的期望。

**评分标准**
- 如果选手的前两行正确，其余行出现错误，可以得到 $40\%$ 的分数。
- 如果选手的前两行出现错误，其余行正确，可以得到 $50\%$ 的分数。
- 如果选手的所有行输出完全正确，可以得到 $100\%$ 的分数。
- 其余情况选手不得分。


**数据规模和约定**

| 测试点编号 | $N$ 的值 | $M$ 的值 |
| :----------: | :----------: | :----------: |
| $1$ | $4$ | $10$ |
| $2$ | $11$ | $100$ |
| $3$ | $100$ | $10^3$ |
| $4$ | $1001$ | $10^4$ |
| $5$ | $78590$ | $10^5$ |
| $6$ | $87933$ | $10^5$ |
| $7$ | $95000$ | $10^5$|
| $8$ | $99445$ | $10^5$ |
| $9$ | $99999$ | $10^5$ |
| $10$ | $100000$ |  $10^5$|



---

---
title: "[SDOI2012] 走迷宫"
layout: "post"
diff: 省选/NOI-
pid: P6030
tag: ['2012', '各省省选', '山东', '期望']
---
# [SDOI2012] 走迷宫
## 题目描述

Morenan 被困在了一个迷宫里。迷宫可以视为 $n$ 个点 $m$ 条边的有向图，其中 Morenan 处于起点 $s$，迷宫的终点设为 $t$。可惜的是，Morenan 非常的脑小，他只会从一个点出发随机沿着一条从该点出发的有向边，到达另一个点。这样，Morenan 走的步数可能很长，也可能是无限，更可能到不了终点。若到不了终点，则步数视为无穷大。但你必须想方设法求出 Morenan 所走步数的期望值。
## 输入格式

第一行四个整数，$n,m,s,t$。

接下来 $m$ 行，每行两个整数 $u, v$ ，表示有一条从 $u$ 到 $v$ 的边。
## 输出格式

一个浮点数，保留小数点后 $3$ 位，为步数的期望值。若期望值为无穷大，则输出`INF`。
## 样例

### 样例输入 #1
```
6 6 1 6
1 2
1 3
2 4
3 5
4 6
5 6
```
### 样例输出 #1
```
3.000
```
### 样例输入 #2
```
9 12 1 9
1 2
2 3
3 1
3 4
3 7
4 5
5 6
6 4
6 7
7 8
8 9
9 7
```
### 样例输出 #2
```
9.500
```
### 样例输入 #3
```
2 0 1 2
```
### 样例输出 #3
```
INF
```
## 提示

| 测试点 | $n\leq$ | $m\leq$ |
| :----------: | :----------: | :----------: |
| $1\sim 6$ | $10$ | $100$ |
| $7\sim 12$ | $200$ | $10^4$ |
| $13\sim 20$ | $10^4$ | $10^6$ |

另外，均匀分布着 $40\%$ 的数据，图中没有环，也没有自环。

对于 $100\%$ 的数据，$1\leq n\leq 10^4$，$0\leq m \leq 10^6$，**保证强连通分量的大小不超过** $\boldsymbol{100}$。


---

---
title: "Ryoku 爱学习"
layout: "post"
diff: 省选/NOI-
pid: P6036
tag: ['动态规划 DP', '2020', 'Special Judge', '期望']
---
# Ryoku 爱学习
## 题目背景

Ryoku 继承了 Riri 在学习方面的天赋，所以她非常热爱学习。但是，不管再怎么热爱学习，Ryoku 也会疲倦的。
## 题目描述

Ryoku 在第 $i$ 时刻会了解到有一个新知识 $i$，这个新知识的实际价值为 $w_i$，由于 Ryoku 爱学习，所以她不会选择不学习知识，但她只有 $p_i$ 的概率能成功掌握这个知识。

然而如果 Ryoku 同时掌握了太多知识，由于 Ryoku 内心的疲倦等因素，Ryoku 感受到的对知识的喜爱程度会改变，我们用一个数值 $R$ 来描述**喜爱程度**的大小。具体而言，设 $R=f(l,r)$ 代表 Ryoku **连续掌握**时刻 $l$ 至时刻 $r$ 的知识时对这些知识的喜爱程度的总和，有参数 $a, b$（$0 < a, b<1$），则有：

$$ f(l,r)=a^{b(r-l)}  \sum_{i=l}^r w_i$$

Ryoku 想要知道她期望能**掌握的每一段连续时刻的知识**的喜爱程度之和是多少（需要注意的是，这里所说的连续时刻的知识不能被一段更长的所包含）。你能帮帮她吗？

## 输入格式

输入包含三行。  
第一行包含一个整数 $n$，两个实数 $a,b$。  
第二行包含 $n$ 个整数，为 $w_i$。  
第三行包含 $n$ 个实数，为 $p_i$。
## 输出格式

输出包含一行一个正实数，为答案。
## 样例

### 样例输入 #1
```
3 0.5 0.5
2 3 3
0.5 0.5 0.5

```
### 样例输出 #1
```
3.097
```
### 样例输入 #2
```
6 0.8 0.2
1 1 4 5 1 4
0.9 0.6 0.7 0.7 0.6 0.8

```
### 样例输出 #2
```
10.521
```
## 提示

**【样例 1 说明】**

掌握知识 $1$、知识 $2$、知识 $3$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 2}(2+3+3)=4$。

掌握知识 $1$、知识 $2$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 1}(2+3)=\dfrac {5\sqrt2}2\approx 3.536$。

掌握知识 $1$、知识 $3$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 0}\times 2 +\left(\dfrac 12\right)^{\frac12\times 0}\times 3  = 5$。

掌握知识 $2$、知识 $3$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 1}(3+3)=3\sqrt 2\approx 4.243$。

只掌握知识 $1$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 0}\times 2  = 2$。

只掌握知识 $2$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 0}\times 3  = 3$。

只掌握宝物 $3$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 0}\times 3  = 3$。

什么都不掌握时，每一段连续掌握知识的喜爱程度之和为 $0$。

以上 $8$ 种情况出现的概率均为 $\dfrac 18$，所以答案约为：

$$(4+3.536+5+4.243+2+3+3+0)\times \dfrac 18\approx3.0973$$

---

**【数据规模与约定】**

对于 $20\%$ 的数据，$n \le 18$。  
对于另外 $15\%$ 的数据，$w_i = 1$。  
对于 $55\%$ 的数据，$n \le 10^3$。  
对于另外 $15\%$ 的数据，$w_i = 1$。  
对于另外 $15\%$ 的数据，$b_i \le 0.2$。  

此外，对于 $100\%$ 的数据，$0<n\le10^5$，$0<a,b,p_i<1$，$0<w_i\le10^3$。保证输入数据的精度不超过 $10^{-2}$。

**本题使用 Special Judge，如果某个测试点中你的答案与标准答案相差小于等于 $10^{-3}$，你就可以通过该测试点。**



---

---
title: "最优性剪枝"
layout: "post"
diff: 省选/NOI-
pid: P6048
tag: ['搜索', '数学', '2020', '线段树', '剪枝', '树链剖分', '期望']
---
# 最优性剪枝
## 题目背景

Nauuo 是一名出题人。

众所周知，某些出题人非常懒，导致[随便爆搜](https://www.luogu.com.cn/discuss/show/185420)加上一个[最优性剪枝](https://www.luogu.com.cn/discuss/show/184641)就能通过。Nauuo 决定把这些 naive 的暴力都卡掉。
## 题目描述

Nauuo 决定卡一个暴力搜索程序，为此她构建了一组数据。为了简化题目，你将得到这组数据产生的搜索树 $T$。$T$ 中包含 $n$ 个节点，依次编号为 $1 \sim n$，其中 $1$ 号点是 $T$ 的根节点。一个节点的深度是它到 $1$ 号点的简单路径上的节点个数。

这个程序的伪代码如下

```cpp
answer := inf

procedure dfs(node,depth)
	if (node is leaf) 
		answer := min(answer,depth)
		return
	if (depth < answer)
		for i in children of node
			dfs(i,depth+1)

dfs(1,1)
```

其中，`:=` 表示赋值运算。

翻译成人话就是说，这个暴力搜索程序将**深度优先**地遍历这棵搜索树，当访问到一个叶节点时，这个程序将用这个叶节点的深度更新答案。

同时，这个程序有一个最优性剪枝，也就是说，当这个程序访问到任意一个深度等于答案的节点时，它将不会再访问这个节点的子节点。

然而，可怜的 Nauuo 并不知道这个程序在某个节点时访问自己子节点的顺序，因此她认为每个节点访问子节点的顺序都是在所有可能的情况中等概率随机的，显然，一共有 $\prod d_i!$ 种情况，其中 $d_i$ 表示 $i$ 号节点的子节点数量。

现在她想知道这个程序访问到的节点数量的期望，以确定这个程序会不会被自己的数据卡掉。

为了避免浮点误差，答案对 $998244353$ 取模。保证答案能被表示为最简分数 $\frac{p}{q}$，你只需要输出一个 $x (0\leq x < 998244353)$ 使得 $qx \equiv p \pmod {998244353}$。
## 输入格式

第一行一个整数 $n$。

第二行 $n-1$ 个整数 $p_2, p_3 \cdots p_n$，其中 $p_i$ 表示 $i$ 号节点的父节点编号。
## 输出格式

一行一个整数，所求 $x$。
## 样例

### 样例输入 #1
```
4
1 1 3
```
### 样例输出 #1
```
499122180
```
### 样例输入 #2
```
3
1 2
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
13
1 1 1 3 5 4 2 3 7 4 4 6
```
### 样例输出 #3
```
776412285
```
## 提示

#### 样例解释

第一组样例的真实答案为 $\frac{7}{2}$。

一共只有两种情况，如果 $1$ 号节点先遍历 $3$ 号节点，则程序将访问到搜索树中所有节点。如果 $1$ 号节点先遍历 $2$ 号节点，则 $4$ 号节点不会被访问到。

第二组样例中，每个非叶节点的子节点都是唯一的，因此只有一种可能的情况，所有节点都必然被访问到。

第三组样例的真实答案为 $\frac{94}{9}$。

---

#### 数据范围

**「本题采用捆绑测试」**

对于所有测试点，保证 $1 \leq n \leq 3\times 10^5$，$1 \leq p_i < i$。

$\text{Subtask 1 (11 pts)}$ $n \leq 9$。

$\text{Subtask 2 (18 pts)}$ $n \leq 100$。

$\text{Subtask 3 (19 pts)}$ $n\leq 10^3$。

$\text{Subtask 4 (4 pts)}$ $p_i = i-1$。

$\text{Subtask 5 (8 pts)}$ $p_i =\lfloor \frac{i}{2} \rfloor$。

$\text{Subtask 6 (40 pts)}$ 无特殊限制。

---

#### 提示

如果你不知道怎么对分数取模，可以参考[这里](https://www.luogu.com.cn/problem/P3811)。




---

---
title: "[RC-02] 开门大吉"
layout: "post"
diff: 省选/NOI-
pid: P6054
tag: ['网络流', 'Special Judge', 'O2优化', '最小割', '期望']
---
# [RC-02] 开门大吉
## 题目描述

$n$ 位选手去参加节目“开门大吉”。共有 $m$ 套题，每套题包含 $p$ 个题目，第 $i$ 位选手答对第 $j$ 套题中第 $k$ 道的概率为 $f_{i,j,k}$。

若一位选手答对第 $i$ 题，会在已得到奖励的基础上，再得到 $c_i$ 元奖励。选手总是从第一道开始，按顺序答题的。

同时，为了防止过多的选手做同一套题，还有 $y$ 条形如“第 $i$ 位选手的套题编号必须至少比第 $j$ 位的大 $k$”的限制。

你需要给每一位选手分配一套题（不同选手可以相同），使得所有人的期望奖励和最小。
## 输入格式

输入包含多组数据。第一行是一个整数 $T$，为数据组数。

对于每组数据，第一行四个整数 $n,m,p,y$。

接下来一行 $p$ 个整数，第 $i$ 个为 $c_i$。 

接下来 $m$ 个 $n\times p$ 的矩阵，第 $j$ 个矩阵中第 $i$ 行第 $k$ 个实数为 $f_{i,j,k}$。

接下来 $y$ 行，每行三个整数 $i,j,k$（$1\le i,j\le n$，$-m<k<m$），描述一条限制。
## 输出格式

对于每组数据，输出一个实数，为答案。无解输出 `-1`。

本题有 Special Judge，答案误差在 $5\times 10^{-4}$ 以内都算对。

由于 SPJ 敏感，请在每组数据末尾都输出一个换行符，并不要再输出其它字符。
## 样例

### 样例输入 #1
```
4
3 2 4 0
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
3 2 4 1
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
2 3 1
3 2 4 1
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
1 2 1
3 2 4 2
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
1 2 1
2 3 1
```
### 样例输出 #1
```
15.1460
18.5340
18.7560
-1
```
## 提示

【样例解释】

这里只解释第二组数据。

一共只有两套题，而第二个人的套题编号大于第三个人，因此第二个人一定是选第二套，第三个人选第一套。

第二个人选第二套，期望支出：$0.2\times (1-0.5)\times 10+0.2\times 0.5 \times (1-0.3) \times 20+0.2\times 0.5 \times 0.3\times (1-0.6)  \times 30+0.2\times 0.5 \times 0.3\times 0.6  \times 50=3.66$。

其他人的计算方法类似。

【数据范围】

**本题捆绑测试。**

对于所有数据，$1\le n,m,p\le 80$，$0\le y\le 10^3$，$0\le f_{i,j,k} \le 1$，$0\le c_i\le 10^5$，$1 \le T\le 50$。保证每个测试点的输入数据大小小于 $10\text{MB}$。

Subtask 1（20 pts）：$n,m,p,y\le 7$；

Subtask 2（20 pts）：$T\le 6$，$y=0$；

Subtask 3（20 pts）：$n,m,p\le 30$，$y\le 200$；

Subtask 4（20 pts）：$T=1$；

Subtask 5（20 pts）：$T\le 5$。


---

---
title: "「StOI-1」小Z的旅行"
layout: "post"
diff: 省选/NOI-
pid: P6375
tag: ['线段树', '树状数组', '期望']
---
# 「StOI-1」小Z的旅行
## 题目描述

一块空地，有$n$座山，每座山有一个高度值$h$。小Z在最高的山上，要去最低的山。

他有如下移动方案：

$1.$ 移动到一座比当前山低的山；

$2.$ 移动到和当前山一样高的山（不可停留在当前山），对于每一高度只能执行一次该方案（即不可以连续 $3$ 次或以上到达同一高度的山）。

每次移动都会耗费体力值，耗费的体力值为两座山的水平距离（若从第 $i$ 座山移动到第 $j$ 座山，则耗费 |$i-j$| 点体力值）。

小Z**每次**若有多种方案移动，则会**等概率**选择任意一种，求耗费体力值的期望对 $998,244,353$ 取余后的结果。
## 输入格式

第一行一个正整数 $n$ ，表示山的个数。
接下来一行 $n$ 个正整数，表示每座山的高度。
## 输出格式

一个整数，表示最终答案对 $998,244,353$ 取余后的结果。
## 样例

### 样例输入 #1
```
4
1 3 3 7

```
### 样例输出 #1
```
332748121
```
### 样例输入 #2
```
3
1 3 2
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
10
1 2 2 2 4 3 2 6 5 9
```
### 样例输出 #3
```
384244861
```
## 提示

---

#### 样例1解释

取模前值为 $\frac{10}{3}$。

有如下方案（数字代表山的编号）：

1. $(4,1)$ 概率 $\frac{1}{3}$ ， 耗费体力值 $3$ ；

2. $(4,3,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $3$ ；

3. $(4,2,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $3$ ；

4. $(4,3,2,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $3$ ； 

5. $(4,2,3,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $5$ 。

---

#### 数据范围

对于 $50$% 的数据：$1 ≤ n ≤ 1000$，$1 ≤ h ≤ 10^{9}$；  
对于 $100$% 的数据：$1 ≤ n ≤ 500000$，$1 ≤ h ≤ 10^{9}$。

所有数据：最低和最高的山高度唯一。


---

---
title: "千年食谱颂"
layout: "post"
diff: 省选/NOI-
pid: P6395
tag: ['动态规划 DP', '数学', '2020', '组合数学', '期望']
---
# 千年食谱颂
## 题目背景

$$\texttt{事在人    命在天}$$
$$\texttt{亘古滔滔转眼间}$$
$$\texttt{唯席上}$$
$$\texttt{千年丰盛永不变}$$

&emsp;&emsp;“阿绫，今天是我的第 $15$ 个 $15$ 岁生日呀！”  
&emsp;&emsp;“哦……阿绫今天回不了家嗷。”  
&emsp;&emsp;早晨九点，迷迷糊糊睁开双眼的小灰毛悄悄用手戳了戳自己的身旁，却只感受到枕头的淡淡的温暖。  
&emsp;&emsp;“明明是人家的生日嘛，又要加班……”把手机扔在一边，叠好被子，走近床边，垂着手轻轻拨开窗帘，刺眼的阳光轻易地冲散了另一个人的温度。  
&emsp;&emsp;“好无聊啊！”  
&emsp;&emsp;就这样熬到了晚上，却发现冰箱已经空空如也。要不……去美食节转转？  
&emsp;&emsp;今天正好是魔都一年一度的美食节，本来以为阿绫会陪自己，天依可是做好了无比详细的攻略。但现在，阿绫不在，计划也随之落空。穿一身清凉的休闲装，带上钱包，天依还是决定，不能在食物上辜负自己！  
&emsp;&emsp;天依的手才刚刚搭上门把手，轻轻一拉，便猛然打开，竟被恋人拥入怀中……  
&emsp;&emsp;星光，灯火，美食，还有……天依小小的舌头轻轻舔着蓝莓味的甜筒，一边悄悄打量着身旁的恋人。修长的身段优雅从容地迈着步子，头顶标志性的红色呆毛就像那希望的烛光闪烁，漫天灯火，在那暗红色的明眸里缓缓流动……阿绫转过身，目光撞上那双碧绿的眼眸。  
&emsp;&emsp;“天依，天依。想什么呢？”   
&emsp;&emsp;看着恋人害羞地撇过脸，耳根子却不争气地红了起来，阿绫又动起了坏心思。她慢慢靠近恋人的脸庞，轻轻嘬了一口粉嫩的嘴唇。  
&emsp;&emsp;“干嘛啦阿绫，这里那么多人……”嘴上这么说着，天依却又不自觉地凑向阿绫。阿绫牵起恋人的手。“走，带你把这儿吃个遍！”
## 题目描述

美食节上一共有 $n$ 个店铺，初始 ( 第 $0$ 时刻 ) 时天依都没有品尝过。天依的 flag 是将它们尽数品尝。所以**从第一个时刻起**，天依会在每一个时刻**等概率地选取 $n$ 个店铺中的一个品尝**。不过，由于食客众多，许多店铺会出现食材短缺的情况而不得不中途撤场。**当一个店铺撤场后，会有一个新的 ( 以前从未出现的 ) 店铺立即进场**，我们称其为一次**撤场事件**。阿绫知道所有撤场事件会在**相邻两个时刻间**发生，且每个店铺在每个时刻间撤场的概率都是 $p$。   

天依凑过毛茸茸的脑袋问阿绫：“期望在第几个时刻，在场的 $n$ 个店铺都被我品尝过呢？”
## 输入格式

一行三个整数 $n,a,b$，表示有 $n$ 个店铺，撤场概率 $p=\dfrac{a}{b}$。
## 输出格式

一行一个整数，表示你的答案。

**由于答案可能是一个小数，为了避免损失精度，请输出答案对 $998244353$ 模意义下的值。**
## 样例

### 样例输入 #1
```
2 1 2
```
### 样例输出 #1
```
5
```
## 提示

#### 数据范围
对于不同的测试点，我们约定如下数据规模及其性质：

|             测试点编号              | $n \leq$ | 特殊性质 1 | 特殊性质 2 |
| :---------------------------------: | :------: | :--------: | :--------: |
|           $1 \sim 2$            |  $500$   | $\sqrt{}$  |     $\times$      |
|  $3 \sim 8$   |  $500$   |     $\times$      |     $\times$      |
|         $9 \sim 11$          |  $3000$  |     $\times$      | $\sqrt{}$  |
| $12 \sim 25$ |  $3000$  |     $\times$      |     $\times$      |

**特殊性质 1**：$a=0$。

**特殊性质 2**：$a=1,b=2$。

对于 $100 \%$ 的数据，$1 \le n \le 3000,0 \le a<b<998244353$。   

------------

#### 题目背景 ( 续 )
&emsp;&emsp;阿绫注视着丝毫不顾忌吃相的天依，又好气又好笑。但看着包里黑卡的钱少了一个又一个 $0$ ，脸色越来越沉……  
&emsp;&emsp;“喂，阴阳头，再送张卡来！”只好冲着哥哥发怒气的阿绫挂掉电话，又挂上了一副温柔的笑颜。  
&emsp;&emsp;“阿绫，阿绫你也尝尝吧。”天依可算想起了没怎么吃的阿绫。  
&emsp;&emsp;“不急，晚上回家，还有大餐等着我呢。”阿绫冲天依笑着，邪魅地笑着。  
&emsp;&emsp;“唔，所以大餐是什么呢？”天依想不明白，但总觉得有些不安。   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;“你还是老样子呢，天依。”


---

---
title: "[YsOI2020] 计划"
layout: "post"
diff: 省选/NOI-
pid: P6595
tag: ['数学', 'Special Judge', 'O2优化', '容斥原理', '期望']
---
# [YsOI2020] 计划
## 题目背景

相信大家已经知道了这样几个事实：  
- Ysuperman 是很有钱。

- Ysuperman 一直都很善于制定计划。

- Ysuperman 管理着一个幼儿园。

- Ysuperman 收藏了一些零食。

- 每一天，TA 可能会心血来潮地想要有计划地吃掉 TA 的零食。

## 题目描述

Ysuperman 现在有 $n$ 份零食，对**每份**零食而言，TA 每一天有 $P$ 的概率对 TA 的这份零食做出计划，TA 每做出一份计划后的 $T$ 天后，TA 将会将这一份零食给吃掉。需要特殊说明的是，如果在Ysuperman制定计划前已经对该份零食做出计划，则实际会按照**第一份计划的时间**将零食吃掉。

不幸的是，幼儿园内贪吃的小朋友会破坏这一计划。  幼儿园内有 $m$ 个小朋友，TA 们觊觎着 Ysuperman 的零食。对于**每份**零食，每天会有 $p_i$ 的概率被第 $i$ 个小朋友偷吃。如果这份零食在某位小朋友偷吃之前被吃掉了，那么相应地，这位小朋友就偷吃不了。**如果有一份零食在计划完成前被偷吃，那么，相关计划就无法实现了。**

现在 Ysuperman 要对 TA 的计划进行风险评估，TA 悬赏了 $114514pts$ ，这个项目在经过层层转包后来到了您的手上，现在已经算出了各概率在模意义下的值。经过各方协商，您如果解决了这个问题，您可以获得 $ 100pts $ 。您需要告诉 TA **Ysuperman 能期望吃掉多少份零食，以及 Ysuperman 的零食期望在多少天后被吃完** 。

**如果一份零食被某位小朋友吃掉了，那么这份零食就不属于Ysuperman了。**

需要注意的是，Ysuperman每天制定计划的时间在小朋友偷吃糖果**之前**。

Ysuperman 认为浮点数的精度误差太大，所以你只需要输出答案**对 $998244353$ 取模**的结果。
## 输入格式

第一行包括三个正整数 $n,m,T$ ，含义如题目所述。 

第二行包括一个正整数 $ P $ ，表示 $P$ 对 $998244353$ 取模后的结果。  

第三行包括 $m$ 个正整数 $p_1,p_2,\cdots,p_m$ ，分别表示 $p_i$ 对 $998244353$ 取模后的结果。
## 输出格式

一行，两个自然数。 分别表示 Ysuperman 能期望吃掉多少份零食，以及 Ysuperman 的零食期望在多少天后被吃完，您需要输出答案对 $998244353$ 取模后的结果。


## 样例

### 样例输入 #1
```
5 8 11
13482572 
299473306 598946612 898419918 199648871 499122177 798595483 99824436 1
```
### 样例输出 #1
```
0 1
```
### 样例输入 #2
```
3 5 0
1
1 1 1 1 1
```
### 样例输出 #2
```
3 1
```
### 样例输入 #3
```
2 2 0
499122177
499122177 499122177
```
### 样例输出 #3
```
855638018 507044752
```
### 样例输入 #4
```
11 4 514
1919810
1919810 1919810 1919810 1919810
```
### 样例输出 #4
```
550831570 75142974
```
### 样例输入 #5
```
100000 20 227
2020
2000 2001 2002 2003 2004 2005 2006 2007 2008 2009 2010 2011 2012 2013 2014 2015 2016 2017 2018 2019
```
### 样例输出 #5
```
808786679 861511854
```
## 提示

### 样例说明

#### 样例说明 $1$:

在取模前的其中一种可能情况为：
```cpp
5 8 11  
0.1  
0.1 0.2 0.3 0.4 0.5 0.6 0.7 1
```
该情况下，小朋友会在第一天中偷吃完所有的零食。

#### 样例说明 $2$:

在取模前的一种可能情况为：
```cpp
3 5 0  
1  
1 1 1 1 1
```

该情况下，Ysuperman 会在第一天计划并吃完所有的零食。

#### 样例说明 $3$:

在取模前的一种可能的情况为：

```cpp
2 2 0  
0.5  
0.5 0.5
```
在此情况下，答案为 $\dfrac{8}{7}$ 和 $\dfrac{80}{63}$。

由于解答过程较为复杂，所以请聪明的读者自行思考。


------------
### 数据范围

**如果您只答对了某个测试点两问中的任意一问，您可以获得这个测试点 $ 25\% $ 的分数。**

以下是致敬 $\text{NOI}$ 的部分分表格：
| 测试点编号 | $n$ | $m$ | $T$ | $P$ | 特殊性质 |
| :-----------: | -----------: | -----------: | -----------: | -----------: | :-----------: |
| 1 | $=1$ | $=1$ | $=0$ | 无其它约束 | 无 |
| 2 | $=1$ | $=10$ | $=1$ | $=1$ | $1$ |
| 3 | $=1$ | $\le100$ | $=227$ | $=1$ | $2$ |
| 4 | $\le 20$ | $\le 1000$ | $=4$ | 无其它约束 | 无 |
| 5 | $\le 100$ | $\le 1000$ | $=4$ | 无其它约束 | 无 |
| 6 | $\le 1000$ | $\le 1000$ | $=227$ | $=0$ | $1$ |
| 7 | $\le 100000$ | $\le 100000$ | $=233$ | $=1$ | $2$ |
| 8 | $\le1919820$ | $=114514$ | $=2333$ | $=0$ | $2$ |
| 9 | $\le1919820$ | $=114514$ | $=2333$ | $=0$ | $2$ |
| 10 | $=100000$ | $=100000$ | $=3$ | 无其它约束 | $2$ |
| 11 | $=114514$ | $=114514$ | $=3$ | 无其它约束 | 无 |
| 12 | $\le1919820$ | $=114514$ | $=0$ | 无其它约束 | $2$ |
| 13 | $\le 1919820$ | $=1$ | $\le 227$ | 无其它约束 | 无 |
| 14 | $\le 1919820$ | $\le114514$ | $\le 227$ | 无其它约束 | $2$ |
| 15 | $\le 1919820$ | $=1$ | $\le 500$ | $=1$ | 无 |
| 16 | $\le 1919820$ | $\le 114514$ | $\le 500$ | $=1$ | 无 |
| 17 | $\le 1919820$ | $\le 114514$ | $\le 500$ | $=1$ | 无 |
| 18 | $\le 1919820$ | $\le 114514$ | $=0$ | 无其它约束 | 无 |
| 19 | $\le 1919820$ | $\le 114514$ | $=0$ | 无其它约束 | 无 |
| 20 | $\le 100000$ | $\le 100000$ | $\le 500$ | 无其它约束 | $2$ |
| 21 | $\le 100000$ | $\le 100000$ | $\le 500$ | 无其它约束 | 无 |
| 22 | $\le 100000$ | $\le 100000$ | $\le 500$ | 无其它约束 | 无 |
| 23 | $\le 1919820$ | $\le 114514$ | $\le 2333$ | 无其它约束 | 无 |
| 24 | $\le 1919820$ | $\le 114514$ | $\le 2333$ | 无其它约束 | 无 |
| 25 | $\le 1919820$ | $\le 114514$ | $\le 2333$ | 无其它约束 | $2$ |

对于 $100\%$ 的数据，满足 $ 1\le n\le 1919820,1\le m \le 114514,0\le T \le 2333,0\le P< 998244353,1\le p_i<998244353$


特殊性质 $1$：存在一个 $i$ 使得$p_i=1$。

特殊性质 $2$：所有的 $p_i$ 都相等。


---

---
title: "[CCC 2020] Josh's Double Bacon Deluxe"
layout: "post"
diff: 省选/NOI-
pid: P6708
tag: ['动态规划 DP', '2020', 'Special Judge', 'CCC（加拿大）', '期望']
---
# [CCC 2020] Josh's Double Bacon Deluxe
## 题目背景

Josh 和 $N-1$ 个人去吃汉堡。
## 题目描述

这个汉堡店共有 $M$ 种汉堡。

第 $i$ 个人最喜欢吃的汉堡为第 $b_i$ 种汉堡。

这 $N$ 个人都会选他最喜欢吃的汉堡。

现在，这 $N$ 个人排队去取汉堡，不幸的是，第一个人忘记了他最喜欢的汉堡，于是他随便拿了一个汉堡。

接下来的 $N-2$ 个人会按如下规则拿汉堡：
- 如果有他最喜欢的汉堡，就直接拿走。
- 否则，他会随便拿一个。

您需要求出，**排在最后**的 Josh 拿到他最喜欢汉堡的概率。
## 输入格式

第一行为一个整数 $N$。

接下来 $N$ 行，一行一个整数 $b_i$。
## 输出格式

一行一个小数，表示**排在最后**的 Josh 拿到他最喜欢汉堡的概率。
## 样例

### 样例输入 #1
```
3
1 2 3

```
### 样例输出 #1
```
0.5
```
### 样例输入 #2
```
7
1 2 3 1 1 2 3
```
### 样例输出 #2
```
0.57142857
```
## 提示

#### 样例 1 解释
| 第一个人的选择 | 第二个人的选择 | Josh 的选择 | 概率 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $2$ | $3$ | $\frac{1}{3}$ |
| $2$ | $1$ | $3$ | $\frac{1}{3}\times \frac{1}{2}=\frac{1}{6}$ |
| $2$ | $3$ | $1$ | $\frac{1}{6}$ |
| $3$ | $2$ | $1$ | $\frac{1}{3}$ |

Josh 拿到他最喜欢汉堡的概率为 $\frac{1}{3}+\frac{1}{6}=\frac{1}{2}$。

#### SPJ 计分标准
设正确答案为 $C$，你的答案为 $P$，若 $\lvert P-C\rvert <10^{-6}$，则您得该测试点的满分，否则，您得零分。

#### 子任务
**本题采用捆绑测试，且本题的 Subtask 分数有微调。**
- Subtask 1（$27$ 分）：保证 $N\le 10^5$，$M\le 10^3$。
- Subtask 2（$33$ 分）：保证 $M\le 10^3$。
- Subtask 3（$40$ 分）：无特殊限制。

对于 $100\%$ 的数据，保证 $3\le N\le 10^6$，$1\le b_i\le M\le 5\times 10^5$。

#### 说明
本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/resources/past-contests?contest_category=29) [2020 Senior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/seniorEF.pdf) T5 Josh's Double Bacon Deluxe。


---

---
title: "[yLOI2020] 灼"
layout: "post"
diff: 省选/NOI-
pid: P7099
tag: ['数学', '2020', 'O2优化', '期望']
---
# [yLOI2020] 灼
## 题目背景

> 声嘶力竭，向悲泣的虚空祈祷至最后，  
> 神为何依然残酷冷漠。  
> 天国或地狱，也奢求你无垢眼眸，  
> 就让我，再次被你拯救。

——银临《灼》
## 题目描述

> 这里是 NS05，勒本星球已无生命反应，请求救援！普尔！——你听得到吗？我会一直在这里，等待你的归来。

扶苏被困在了勒本星球，灼闻羽驾驶着一架宇宙飞船正打算穿越虫洞到达勒本星球拯救扶苏。

在一条数轴上有 $n$ 个虫洞，第 $i$ 个虫洞的坐标为 $x_i$。进入这些虫洞的任意一个都可以直接到达勒本星球拯救扶苏。飞船到达数轴所在直线上后，会因为磁场的效应失去操控能力，飞船每秒会**等概率**向左或向右移动一个单位长度。

灼闻羽非常焦急，他给出了 $q$ 个飞船进入数轴所在直线的初始坐标，对于每个坐标，他想知道期望需要多少秒才能到达一个虫洞。

如果你计算出的期望是个分数，你需要求出这个分数对 $998244353$ 取模的答案。有关分数取模的定义你可以参考「提示」中的内容。

为了避免输出过大，你只需要输出四个整数，分别表示你所有回答（对 $998244353$ 取模之后，下同）的按位异或之和、你共有多少次回答的答案是奇数，你的所有答案中的最大值、你的所有答案中的最小值。
## 输入格式

第一行是一个整数，表示测试点所对应的编号 $T$。  
第二行有两个整数，分别表示虫洞的个数 $n$ 和初始坐标的个数 $q$。  
第三行有 $n$ 个整数，第 $i$ 个整数表示第 $i$ 个虫洞的坐标 $x_i$。  
接下来 $q$ 行，每行一个整数，表示一个飞船进入数轴所在直线的初始坐标 $y_j$。

**保证给出的 $y_j$ 以不降序排序**。
## 输出格式

输出四行，每行一个整数，依次表示你所有回答的按位异或之和、你共有多少次回答的答案是奇数，你的所有答案中的最大值、你的所有答案中的最小值。

## 样例

### 样例输入 #1
```
0
2 3
1 3
1
2
3

```
### 样例输出 #1
```
1
1
1
0
```
## 提示

### 样例 1 解释

数轴上 $1, 3$ 两点有虫洞。当飞船初始坐标为 $1$ 或 $3$ 时，可以直接进入虫洞，花费 $0s$；当初始坐标为 $2$ 时，有 $\frac 1 2$ 的概率向左一个单位，花费 $1s$ 进入虫洞，也有 $\frac 1 2$ 的概率向右一个单位，花费 $1s$ 进入虫洞，期望用时为 $\frac 1 2 \times (1 + 1) = 1$。

因此，三次询问的答案分别为 $0, 1, 0$。

### 数据规模与约定

本题共有 $10$ 个测试点，每个测试点 $10$ 分。

- 对于 $10\%$ 的数据，保证 $n = 1$。
- 对于 $20\%$ 的数据，保证对于任意一个虫洞，总存在另一个虫洞，使得他们之间的距离不超过 $2$。例如，样例中两个虫洞的距离为 $2$。
- 对于 $30\%$ 的数据，保证对于任意一个虫洞，总存在另一个虫洞，使得他们之间的距离不超过 $3$。
- 对于 $50\%$ 的数据，保证 $x_i,q \leq 100$。
- 对于 $70\%$ 的数据，保证 $x_i, q \leq 10^5$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$1 \leq q \leq 5 \times 10^6$，$1 \leq x_i, y_j \leq 10^9$，$y_j$ 不小于 $x_i$ 中的最小值，且 $y_j$ 不大于 $x_i$ 中的最大值，$y_j$ 按照不降序给出。

### 提示

- 如果你不知道什么是分数取模，可以参考如下的内容：

  对于一个形如 $\frac a b$ 的既约分数，其中 $b \lt 998244353$，它对 $998244353$ 取模后的值为 $a \times b^{998244351} \bmod {998244353}$ 。 
- 为了方便用脚造数据，数据**并不**保证 $x_i$ 互不相同。
- 请注意大量数据读入对程序效率造成的影响。
- 本题的特殊输出方式只是为了避免输出过大造成程序超时，与本题解法无关。
- 请注意，$T$ **不是**数据组数。
- 本题共有两个附加文件，见附加文件中的 zhuo.zip。	


---

---
title: "「C.E.L.U-01」门禁"
layout: "post"
diff: 省选/NOI-
pid: P7105
tag: ['Special Judge', '期望', '状压 DP']
---
# 「C.E.L.U-01」门禁
## 题目背景

abruce 有一次去机房去得**比较**早，然后……他在外面等了35分钟……于是，他想到这样一个问题：  
机房的大门锁着，有 $n$ 名学生都需要进来，进来必须要门禁卡。但有些学生会一同前往。一同前往的人中只要有一个人带了门禁卡就会免于被锁在外面的窘境。现在老师终于要发门禁卡了，可是究竟要发多少张呢？
## 题目描述

我们将题目背景中的问题简化。给出 $n$ 个点，以及任意两个点 $i,j$ 之间存在一条无向边的概率 $p_{i,j}$，求图中联通块个数的期望。
## 输入格式

第一行一个数 $n$。  
第二行到第 $n+1$ 行，每行 $n$ 个实数，代表 $p_{i,j}$。测试数据保证对任意 $1\le i \le n$，$p_{i,i}=0$，对任意 $1\le i,j \le n$，$p_{i,j}=p_{j,i}$，$0\le p_{i,j}\le1$ ，输入的实数小数点后位数不超过 $3$ 位。
## 输出格式

仅一行一个实数，表示连通块个数的期望。当你的答案与标准答案的**绝对**误差不超过 $10^{-4}$ 时算作正确。
## 样例

### 样例输入 #1
```
3
0 0.5 0.5
0.5 0 0.5
0.5 0.5 0
```
### 样例输出 #1
```
1.625000
```
### 样例输入 #2
```
4
0 0.129 0.58 0.37
0.129 0 0.22 0.134
0.58 0.22 0 0.6
0.37 0.134 0.6 0
```
### 样例输出 #2
```
2.143266
```
## 提示

样例解释1：以下八种情况出现概率都是 $\dfrac{1}{8}$。  
![](https://cdn.luogu.com.cn/upload/image_hosting/u1fkikj5.png)  
连通块的个数分别为 $3,2,2,2,1,1,1,1$。  
所以期望是 $\dfrac{1}{8}\times3+\dfrac{3}{8}\times2+\dfrac{4}{8}\times1=\dfrac{13}{8}=1.625$

|数据编号|$n$|特殊性质|
|:-:|:-:|:-:|
|$1\sim3$|$\le4$|无|
|$4$|$\le8$|$p_{i,j}=0$ 或 $p_{i,j}=1$|
|$5\sim6$|$\le8$|$i\not=j$ 时 $p_{i,j}=0.5$|
|$7\sim8$|$\le8$|无|
|$9\sim10$|$\le11$|无|
|$11\sim12$|$\le14$|无|


---

---
title: "「Stoi2031」蒲公英的约定（vol.1）"
layout: "post"
diff: 省选/NOI-
pid: P7490
tag: ['数学', '博弈论', '期望', 'SG 函数']
---
# 「Stoi2031」蒲公英的约定（vol.1）
## 题目背景

> 一起长大的约定 那样清晰 拉过勾的我相信 说好要一起旅行 是你如今 唯一坚持的任性 ——《蒲公英的约定》
## 题目描述

清和如在玩游戏。她们有 $n$ 丛 **蒲公英**，每丛分别有 $s_i$ 朵。这些 **蒲公英** 有一个神奇的性质：有一个给定的常数 $\sigma \in (0,1)$，$x$ 朵 **蒲公英** 会分出 $\lfloor \sigma x \rfloor$ 朵为一组，剩下 $x-\lfloor \sigma x \rfloor$ 朵继续分组，直到分出的组没有 **蒲公英** 即 $\lfloor \sigma x \rfloor=0$ 为止。她们称这种现象为 **任性**。现在她们的每丛 **蒲公英** 都有 **任性** 的现象。她们的游戏规则如下：从清开始，两人轮流进行 **旅行**。一次 **旅行** 为选择一丛 **蒲公英** 并吹散这一丛的第一组中的若干朵 **蒲公英**，至少要吹一朵，至多吹的朵数为第一组的朵数，即不能吹散除第一组外的 **蒲公英**。当第一组为空时，其下一组成为第一组。若这一丛只剩下一组 **蒲公英**，这一丛不能再被选定。每丛 **蒲公英** 都不能被选定时，游戏结束，当前轮到的人落败。她们想知道如果清第一次 **旅行** 时等概率选择其中一丛可吹散的 **蒲公英** 再等概率选择吹散的朵数后两人都按最优策略操作，那么清的胜率 $x \bmod 20190816170251$ 的值将会是多少。

与 vol.2 的区别是，**蒲公英** 在被吹散一部分后 **不会** 重新分组。
## 输入格式

第一行两个正整数 $id,n$，其中 $id$ 表示 Subtask 编号。

第二行 $n$ 个正整数，第 $i$ 个表示 $s_i$。

若 $id>3$，第三行输入两个正整数 $p,q$ 表示 $\sigma=\dfrac{p}{q}$。
## 输出格式

一行一个整数，表示清的胜率 $x \bmod{20190816170251}$。
## 样例

### 样例输入 #1
```
4 3
1 1 1
1 6

```
### 样例输出 #1
```
0

```
### 样例输入 #2
```
6 3
1 7 3
1 3

```
### 样例输出 #2
```
5047704042563

```
## 提示

#### 简述版题意：

有 $n$ 丛 **蒲公英**，第 $i$ 丛有 $s_i$ 朵。给定实数 $\sigma$，每丛会分为若干组，第 $j$ 组有 $t_j$ 朵，且满足 $t_j=\left\lfloor \sigma\left(s_i - \sum\limits_{k=1}^{j-1}t_k\right) \right\rfloor$，当 $t_j=0$ 时不再分组。两人轮流操作，每次操作可以选择一丛 **蒲公英**，并选择一个整数 $c \in t_j$，从这丛 **蒲公英** 中吹散 $c$ 朵，将 $t_j$ 变为 $t_j-c$，其中 $j$ 为操作之前这丛 **蒲公英** 中满足 $t_j \neq 0$ 的最小正整数。必须至少吹一朵，不能操作者败。求先手第一步等概率选择任意一丛可操作的 **蒲公英** 再等概率选择吹散的朵数后两人都采取最优策略时先手的胜率 $x \bmod{20190816170251}$ 的值。

#### 样例解释：

对于样例 $1$，清无法操作，胜率为 $0$。

对于样例 $2$，初始局面为 $\{0;1\},\{2,1,1,1,0;2\},\{1,0;2\}$，清可以选择第 $2$ 丛并在两种操作中选择吹散 $2$ 朵变成 $\{0;1\},\{1,1,1,0;2\},\{1,0;2\}$，选择第 $3$ 丛没有可取胜的策略，且第 $1$ 丛不能选择，总胜率为 $\dfrac{\frac{1}{2}+0}{2}=\dfrac{1}{4}$。

#### 数据范围：

**本题采用捆绑测试，各个 Subtask 的分数与限制如下。**

| Subtask No. | $n \le$ | $s_i \le$ | $\sigma$ 限制 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{2}+1}{3}$ | $10$ |
| $2$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{3}+1}{5}$ | $10$ |
| $3$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{5}-1}{2}$ | $10$ |
| $4$ | $100$ | $1$ | 无 | $3$ |
| $5$ | $100$ | $100$ | $\sigma=\dfrac{1}{2}$ | $7$ |
| $6$ | $100$ | $10^6$ | 无 | $13$ |
| $7$ | $3 \times 10^5$ | $10^{10}$ | $\sigma \ge \dfrac{1}{2}$ | $47$ |

对于 $100\%$ 的数据，$1 \le n \le 3 \times 10^5,1 \le s_i \le 10^{10},1 \le p<q \le 10^9$。

**本题读入量较大，可以选择使用比赛描述中的快速读入模板以加快读入速度。**


---

---
title: "「Stoi2031」蒲公英的约定（vol.2）"
layout: "post"
diff: 省选/NOI-
pid: P7491
tag: ['数学', '博弈论', '期望', 'SG 函数']
---
# 「Stoi2031」蒲公英的约定（vol.2）
## 题目背景

> 一起长大的约定 那样清晰 拉过勾的我相信 说好要一起旅行 是你如今 唯一坚持的任性 ——《蒲公英的约定》
## 题目描述

清和如在玩游戏。她们有 $n$ 丛 **蒲公英**，每丛分别有 $s_i$ 朵。这些 **蒲公英** 有一个神奇的性质：有一个给定的常数 $\sigma \in (0,1)$，$x$ 朵 **蒲公英** 会分出 $\lfloor \sigma x \rfloor$ 朵为一组，剩下 $x-\lfloor \sigma x \rfloor$ 朵继续分组，直到分出的组没有 **蒲公英** 即 $\lfloor \sigma x \rfloor=0$ 为止。她们称这种现象为 **任性**。现在她们的每丛 **蒲公英** 都有 **任性** 的现象。她们的游戏规则如下：从清开始，两人轮流进行 **旅行**。一次 **旅行** 为选择一丛 **蒲公英** 并吹散这一丛的第一组中的若干朵 **蒲公英**，至少要吹一朵，至多吹的朵数为第一组的朵数，即不能吹散除第一组外的 **蒲公英**。当第一组为空时，其下一组成为第一组。若这一丛只剩下一组 **蒲公英**，这一丛不能再被选定。每丛 **蒲公英** 都不能被选定时，游戏结束，当前轮到的人落败。她们想知道如果清第一次 **旅行** 时等概率选择其中一丛可吹散的 **蒲公英** 再等概率选择吹散的朵数后两人都按最优策略操作，那么清的胜率 $x \bmod{20190816170251}$ 的值将会是多少。

与 vol.1 的区别是，**蒲公英** 在被吹散一部分后 **会** 重新分组。
## 输入格式

第一行两个正整数 $id,n$，其中 $id$ 表示 Subtask 编号。

第二行 $n$ 个正整数，第 $i$ 个表示 $s_i$。

若 $id>3$，第三行输入两个正整数 $p,q$ 表示 $\sigma=\dfrac{p}{q}$。
## 输出格式

一行一个整数，表示清的胜率 $x \bmod{20190816170251}$。
## 样例

### 样例输入 #1
```
4 3
1 1 1
1 6

```
### 样例输出 #1
```
0

```
### 样例输入 #2
```
6 3
1 7 3
1 3

```
### 样例输出 #2
```
15143112127689

```
## 提示

#### 简述版题意：

有 $n$ 丛 **蒲公英**，第 $i$ 丛有 $s_i$ 朵。给定实数 $\sigma$，两人轮流操作，每次操作可以选择一丛 **蒲公英**，并选择一个整数 $c \in (0,\sigma s]$，从这丛 **蒲公英** 中吹散 $c$ 朵，其中 $s$ 为操作之前这丛 **蒲公英** 的朵数。必须至少吹一朵，不能操作者败。求先手第一步等概率选择任意一丛可操作的 **蒲公英** 再等概率选择吹散的朵数后两人都采取最优策略时先手的胜率 $x \bmod{20190816170251}$ 的值。

#### 样例解释：

对于样例 $1$，清无法操作，胜率为 $0$。

对于样例 $2$，清可以选择第 $2$ 丛并在两种操作中选择吹散 $2$ 朵变成 $1,5,3$，或选择第 $3$ 丛并选择唯一的操作变成 $1,7,2$，且第 $1$ 丛不能选择，总胜率为 $\dfrac{\frac{1}{2}+1}{2}=\dfrac{3}{4}$。

#### 数据范围：

**本题采用捆绑测试，各个 Subtask 的分数与限制如下。**

| Subtask No. | $n \le$ | $s_i \le$ | $\sigma$ 限制 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{2}+1}{3}$ | $10$ |
| $2$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{3}+1}{5}$ | $10$ |
| $3$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{5}-1}{2}$ | $10$ |
| $4$ | $100$ | $1$ | 无 | $3$ |
| $5$ | $100$ | $100$ | $\sigma=\dfrac{1}{2}$ | $7$ |
| $6$ | $100$ | $10^6$ | 无 | $13$ |
| $7$ | $3 \times 10^5$ | $10^{10}$ | $\sigma \ge \dfrac{1}{2}$ | $47$ |

对于 $100\%$ 的数据，$1 \le n \le 3 \times 10^5,1 \le s_i \le 10^{10},1 \le p<q \le 10^9$。

**本题读入量较大，可以选择使用比赛描述中的快速读入模板以加快读入速度。**


---

---
title: "狩猎（2021 CoE-II D）"
layout: "post"
diff: 省选/NOI-
pid: P7591
tag: ['动态规划 DP', '2021', 'Special Judge', 'O2优化', '期望']
---
# 狩猎（2021 CoE-II D）
## 题目描述

母狮 $\text{Dina}$ 的领地里有固定的 $n$ 个狩猎点，第 $i$ 个狩猎点有 $p_i$ 的概率可以捕捉到猎物，$\text{Dina}$ 的巢穴和 $n$ 个狩猎点相互之间存在若干条直接连接的双向道路。

每天早晨，$\text{Dina}$ 从她的巢穴出发，随机选择一个与巢穴相邻的狩猎点 $u$ 进行一次捕猎，如果她未捕捉到猎物，她会随机选择一个与当前狩猎点 $u$ 相邻的其他狩猎点 $v$ 继续进行一次捕猎，如果在狩猎点 $v$ 仍未捕捉到猎物，$\text{Dina}$ 会按照前述过程继续捕猎。如果在某个狩猎点捕捉到了猎物，$\text{Dina}$ 会立即返回巢穴，结束捕猎。若当前狩猎点 $u$ 与巢穴相邻，而与其他狩猎点不相邻，$\text{Dina}$ 也会选择立即返回巢穴，然后从与巢穴相邻的狩猎点中，随机选择一个狩猎点继续上述捕猎过程。$\text{Dina}$ 在每个狩猎点只进行一次捕猎，然后离开，但后续可能还会回到该狩猎点再次进行捕猎。在本题环境下，如果地点 $u$ 和地点 $v$ 之间有一条直接连接的双向道路，称地点 $u$ 和地点 $v$ **相邻**，否则称地点 $u$ 和地点 $v$ **不相邻**。

令巢穴的编号为 $0$，$n$ 个狩猎点的编号从 $1$ 到 $n$，$\text{Dina}$ 从编号为 $u$ 的地点到达另外一个编号为 $v$ 的地点需要消耗 $h_{u,v}$ 体力和 $t_{u,v}$ 时间。在第 $i$ 个狩猎点每进行一次捕猎，$\text{Dina}$ 会消耗 $h_i$ 体力和 $t_i$ 时间。每当 $\text{Dina}$ 到达某个狩猎点并进行一次捕猎后，她会评估自己的体力消耗和时间花费，如果体力消耗已经达到（或超过）限值 $H$，她就选择立即返回巢穴结束捕猎。如果时间花费已经达到（或超过）限值 $T$，她也会选择立即返回巢穴结束捕猎。$\text{Dina}$ 只有在到达狩猎点并进行一次捕猎后才进行评估，在任何其他时刻均不会进行评估。如果当前位于巢穴，她会在到达巢穴时就进行评估，因为巢穴并无猎物可供捕捉。

需要注意，$\text{Dina}$ 在沿着两个地点间的双向道路移动的过程中并不会评估，因此可能会出现以下情形：到达某个狩猎点且尚未进行捕猎时，$\text{Dina}$ 已消耗的体力或者已花费的时间已经超过限值。在这种情形下，$\text{Dina}$ 仍然会进行一次捕猎，之后再进行评估。

当 $\text{Dina}$ 因为捕猎成功、体力消耗或时间花费达到（或超过）相应限值、当前狩猎点与其他狩猎点不相邻而返回巢穴时，她总会选择一条具有最少时间花费的路径。如果存在多条具有最少时间花费的路径返回巢穴，她会选择其中体力消耗最少的路径。$\text{Dina}$ 在返回巢穴的过程中不会进行捕猎。

将 $\text{Dina}$ 从巢穴出发，因满足以下三个条件之一：

- 捕猎成功
- 体力消耗达到（或超过）限值 $H$
- 时间花费达到（或超过）限值 $T$

返回到达巢穴并结束捕猎的过程称为一次狩猎。给出巢穴和狩猎点之间的道路、每条道路所需要消耗的体力和花费的时间、每个狩猎点进行一次捕猎能够捕获猎物的概率以及所需消耗的体力、花费的时间，试确定 $\text{Dina}$ 完成一次狩猎所消耗体力和花费时间的平均值。
## 输入格式

输入的第一行包含一个整数 $n$，表示狩猎点的数量。

接下来 $n$ 行，每行包含三个数值：整数 $h_i$，整数 $t_i$，实数 $p_i$，分别表示在第 $i$ 个狩猎点进行一次捕猎所消耗的体力、花费的时间、能够捕获猎物的概率。

接下来是一个整数 $m$，表示连接各个地点的双向道路的数量。接着 $m$ 行，每行包含四个整数 $u$，$v$，$h_{u,v}$，$t_{u,v}$，表示从编号为 $u$（$0 \le i \le n$）的地点到另外一个编号为 $v$（$0 \le i \le n$，$u \ne v$）的地点之间存在一条直接连通的道路，需要消耗 $h_{u,v}$ 体力和花费 $t_{u,v}$ 时间。由于是双向道路，从地点 $u$ 到达地点 $v$ 与从地点 $v$ 到达地点 $u$ 所消耗体力和花费时间相同。

最后是两个整数 $H$ 和 $T$，表示体力和时间的限值。
## 输出格式

输出一行，包含两个实数，精确到小数点后一位，分别表示 $\text{Dina}$ 完成一次狩猎所消耗体力和花费时间的平均值。如果你的输出和参考输出绝对误差小于$10^{-1}$，均认为正确。
## 样例

### 样例输入 #1
```
1
1 2 1.00
1
0 1 2 3
10 20
```
### 样例输出 #1
```
5.0 8.0
```
### 样例输入 #2
```
3
1 2 1.00
2 3 0.50
3 4 0.70
2
0 1 2 3
0 2 4 5
10 20
```
### 样例输出 #2
```
7.5 10.5
```
## 提示

**子任务测试采用捆绑方式计分。**

**样例说明**

输入 #1

![](https://cdn.luogu.com.cn/upload/image_hosting/62vbngdn.png)

该输入只包含一个狩猎点，从巢穴到狩猎点 $1$ 之间的道路需要消耗 $2$ 体力和 $3$ 时间，体力的限值为 $10$，时间的限值为 $20$，在狩猎点 $1$ 进行一次捕猎需要消耗 $1$ 体力和 $2$ 时间，在狩猎点 $1$ 捕获猎物的概率为 $1.00$，即一定会捕捉到猎物。容易知道，进行一次狩猎所消耗的体力和花费时间的平均值分别为 $5.0=(2+1+2) \times 100\%$ 和 $8.0=(3+2+3) \times 100\%$。

输入 #2

![](https://cdn.luogu.com.cn/upload/image_hosting/k4q1qkwr.png)

相较于第一组输入，新增了两个狩猎点，但只有狩猎点 $1$ 和狩猎点 $2$ 与巢穴有直接道路相连。三个狩猎点之间无直接道路相连，但狩猎点 $1$ 可以间接通过巢穴与狩猎点 $2$ 连通。从巢穴到狩猎点 $2$ 的道路需要消耗 $4$ 体力和 $5$ 时间，在狩猎点 $2$ 进行一次捕猎需要消耗 $2$ 体力和 $3$ 时间。在狩猎点 $1$ 捕获猎物的概率为 $1.00$，即一定会捕捉到猎物，因此 $\text{Dina}$ 会立即返回巢穴并结束狩猎。在狩猎点 $2$ 捕获猎物的概率为 $0.50$，即有 $50\%$ 的概率会捕捉到猎物，但由于狩猎点 $2$ 没有其他狩猎点与之直接连通，因此不管在狩猎点 $2$ 是否捕获到猎物，$\text{Dina}$ 都会选择立即返回巢穴，在返回巢穴时，已经消耗 $10$ 体力，根据题意，不管 $\text{Dina}$ 是否已经捕捉到了猎物，她都会结束狩猎。由于是随机选择，故在巢穴时选择狩猎点 $1$ 和 $2$ 进行狩猎的概率均为 $50\%$，根据计算可知，进行一次狩猎所消耗的体力和花费时间的平均值分别为 $7.5=(2+1+2) \times 50\%+(4+2+4) \times 50\%$ 和 $10.5=(3+2+3) \times 50\%+(5+3+5) \times 50\%$。

------------

**数据范围**

- Subtask $1$：$n=1$，$10$ 分。
- Subtask $2$：$1 \le n \le 20$，每个狩猎点和其他狩猎点均无直接道路相连，$20$ 分。
- Subtask $3$：无特殊限制，$70$ 分。

对于 $100\%$ 的数据，$1 \le n \le 200$，$1 \le h_i \le 10$，$1 \le t_i \le 10$，$0 \le p_i \le 1$，$1 \le m \le \text{min}(n (n+1) / 2$，$2000$)，$1 \le h_{u,v} \le 20$，$1 \le t_{u,v} \le 20$，$1 \le H \le 200$，$1 \le T \le 200$。

------------

**约定**

- 地点 $u$ 和地点 $v$ 之间至多有一条直接连接的双向道路，两个地点之间的直连双向道路不会重复给出。
- 忽略 $\text{Dina}$ 进行评估所需要的时间。
- 在输入中，表示概率 $p_i$ 的数值是一个具有两位小数的实数。


---

---
title: "[USACO21DEC] HILO P"
layout: "post"
diff: 省选/NOI-
pid: P7986
tag: ['动态规划 DP', '数学', 'USACO', '2021', '期望']
---
# [USACO21DEC] HILO P
## 题目描述

Bessie 有一个数 $x+0.5$，其中 $x$ 是某个 $0$ 到 $N$ 之间的整数（$1\le N\le 5000$）。

Elsie 正试着猜这个数。她可以以如下形式对于某个 $1$ 到 $N$ 之间的整数提问：「$i$ 是大了还是小了？」如果 $i$ 大于 $x+0.5$，Bessie 会回答 "HI!"，如果 $i$ 小于 $x+0.5$ 则回答 "LO!"。

Elsie 想到了以下猜测 Bessie 的数的策略。在进行任何猜测之前，她创建了一个包含 $N$ 个整数的序列，其中从 $1$ 到 $N$ 的每个数均恰好出现一次（换句话说，这个序列是长为 $N$ 的一个排列）。然后她遍历这一列表，按列表中的数的顺序依次猜数。然而，Elsie 会跳过所有不必要的猜测。也就是说，如果 Elsie 将要猜某个数 $i$，而 Elsie 之前已经猜过了某个 $j < i$ 并且 Bessie 回答 "HI!"，Elsie 不会再猜 $i$，而是继续猜序列中的下一个数。类似地，如果她将要猜某个数 $i$，而她之前已经猜过了某个 $j > i$ 并且 Bessie 回答 "LO!"，Elsie 不会再猜 $i$，而是继续猜序列中的下一个数。可以证明，使用这一策略，对于 Elsie 创建的任意序列，她都可以唯一确定 $x$。

如果我们将所有 Bessie 回答的 "HI" 或 "LO" 拼接成一个字符串 $S$，那么 Bessie 说 "HILO" 的次数为 $S$ 等于 "HILO" 的长为 $4$ 的子串数量。

Bessie 知道 Elsie 将要使用这一策略，并且已经选定了值 $x$，但她不知道 Elsie 会使用什么排列。你的目标是对于所有 Elsie 可能选用的排列，计算 Bessie 说 "HILO" 的次数之和，对 $10^9+7$ 取模。
## 输入格式

输入一行，包含 $N$ 和 $x$。
## 输出格式

输出 HILO 的总数，对 $10^9+7$ 取模。
## 样例

### 样例输入 #1
```
4 2
```
### 样例输出 #1
```
17
```
### 样例输入 #2
```
60 10
```
### 样例输出 #2
```
508859913
```
## 提示

【样例解释1】

在这个测试用例中，Bessie 的数是 $2.5$。

例如，如果 Elsie 的排列是 $(4,1,3,2)$，那么 Bessie 会说 ""HILOHILO"，总计两次 "HILO"。又例如，如果 Elsie 的排列是 $(3,1,2,4)$，那么 Bessie 会说 "HILOLO"，总计一次 "HILO"。

【样例解释2】

确保输出总和对 $10^9+7$ 取模的结果。

【数据范围】

- 测试点 3-10 满足 $N\le 50$；
- 测试点 11-18 满足 $N\le 500$；
- 测试点 19-26 没有额外限制。


---

---
title: "黑暗（Darkness）"
layout: "post"
diff: 省选/NOI-
pid: P8558
tag: ['数学', '洛谷原创', 'O2优化', '组合数学', '期望']
---
# 黑暗（Darkness）
## 题目描述

铃在一个黑暗的三维空间内寻找澪。这个空间可以表示为 $\{(x,y,z) \mid x \in[0,A],y \in [0,B],z\in [0,C] \}$。铃初始站在坐标为 $(A,B,C)$ 处，澪站在 $(0,0,0)$ 处。假设铃在 $(x,y,z)$ 处，她每次移动会**均匀随机**地尝试移动到 $(x-1,y,z)$ 或 $(x,y-1,z)$ 或 $(x,y,z-1)$。

这个空间的外围是墙壁，不可穿过。由于空间内很暗，铃并不知道自己是否走到了墙边。也就是说，她在随机选择三种方向尝试移动时，有可能撞在墙上。

铃想要知道，自己在第一次撞墙时，「到澪的曼哈顿距离（在本题中的情况就是 $x,y,z$ 坐标之和）」的 $k$ 次方的期望值。

你只需要求出答案对 $998244353$ 取模的结果。
## 输入格式

输入一行四个正整数 $A,B,C,k$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
1 1 1 1
```
### 样例输出 #1
```
443664158
```
### 样例输入 #2
```
2 3 4 2
```
### 样例输出 #2
```
128260948
```
### 样例输入 #3
```
4 6 9 2
```
### 样例输出 #3
```
622775535
```
### 样例输入 #4
```
58 88 133 233
```
### 样例输出 #4
```
128518400
```
### 样例输入 #5
```
114514 1919810 4999231 8214898
```
### 样例输出 #5
```
823989766
```
## 提示

【样例 $1$ 解释】 

下表列出了走到各处并撞到墙的概率：

| $(0,0,0)$ | $(1,0,0)$ | $(0,1,0)$ | $(0,0,1)$ | $(1,1,0)$ | $(1,0,1)$ | $(0,1,1)$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $2/9$ | $4/27$ | $4/27$ | $4/27$ | $1/9$ | $1/9$ | $1/9$ |

可以发现只有在这 $7$ 个位置有可能撞到墙。由此算出期望值为 $\dfrac{10}{9}$，在模 $998244353$ 意义下为 $443664158$。


【样例 $2,3$ 解释】   

这里要算的都是距离的平方的期望。实际答案分别为 $\dfrac{30083}{2187}$ 和 $\dfrac{22748643655}{387420489}$。

【数据范围】  

**本题采用捆绑测试。**

Subtask1（8 pts）：$1\le A,B,C,k\le 6$；   
Subtask2（19 pts）：$1\le A,B,C \le 100$；  
Subtask3（13 pts）：$k=1$；  
Subtask4（23 pts）：$1\le A,B,C,k \le 10^5$；  
Subtask5（37 pts）：无特殊限制。

对于 $100\%$ 的数据，$1\le A,B,C \le 5\times 10^6$，$1\le k \le 10^7$。

【提示】  

对于离散随机变量 $X$，其取值等于 $k$ 的概率设为 $P_k$，则 $X$ 的期望值定义为：

$$\sum_k kP_k$$

对于有理数 $a/b$（$a,b$ 均为正整数），若整数 $r$ 满足 $r\in[0,p-1]$ 且 $rb \equiv a \pmod p$，则 $r$ 就是 $a/b$ 对 $p$ 取模的结果。


---

---
title: "追寻 | Pursuit of Dream"
layout: "post"
diff: 省选/NOI-
pid: P8967
tag: ['动态规划 DP', '洛谷原创', 'O2优化', '排列组合', '期望', '高斯消元', '洛谷月赛']
---
# 追寻 | Pursuit of Dream
## 题目背景

“遇到自己喜欢的人或事情的时候，千万不要放弃”

“要一直追寻下去…”

“因为即使成功希望渺茫，也有可能”

有谁和我说过这句话，脑海中忽然闪过一下，被当做无用的激励一同忘却了。现在想要回忆，却总也记不起来。

好不容易来人间一趟，那就别留下遗憾。

房檐落下的雨滴有规律的敲着石砖，那夜的雨声中，却也悄无声息了。

逆着风吹干眼泪，说不出口的痛越藏越多，腐烂在肚子里，却又不知道彼此心知且肚明，所以无法孕育出美好的结局，只会是恋者相残的戏码不停上演。

---

 看见了漫天星野坠落在你的眼底，从此甘愿在那海底般低压的梦境中堕落。

三千尺星空的光辉映照不出那人的身影，璀璨中徒留神明思故人；那人却散入了或许碎散的星辰大海，让神明寻觅了一生。

那些无法兑现的渴望，会日渐荒芜，然后梦境会失去生机，裂缝中会蔓出黑暗，泪无葬身之地。

是神明告诉我的，可是我不信，因为没有时间还等着我空想了。

神明还说，人死了以后，提前离开的亲人都会在另外一个世界等你。

其实，我也会想，这一定就是另外一个世界。
## 题目描述

在 $n$ 维空间中有一个梦想。这梦想坐落在 $(d_1, d_2, \ldots, d_n)$ 的地方。而你从 $(0, 0, \ldots, 0)$ 开始，开启寻梦的旅程。

你的步伐轻缓，每一步只能走一个单位长度。你并不知道你的梦想位于哪里，所以你只能随机选择 $n$ 个正方向中的一个，然后向这个方向走一步。也就是说，在 $[1, n]$ 中均匀随机选择一个正整数 $h$，然后，使你在第 $h$ 维的坐标变成原来的坐标加一。

然而，天有不测风云。在你走每一步的过程中，你会有 $p = \sum_{i = 1}^k p_i$ 的概率散入天际，并开始一段新的旅程。你会在 $k$ 个地点中的一个重新开始这段旅程，其中第 $i$ 个地点的坐标是 $(a_{i,1}, a_{i,2}, \ldots, a_{i,n})$，从这里重新开始的概率为 $p_i$。

那么，期望下，你离到达这个梦想还需要多少步呢？
## 输入格式

第一行，两个正整数 $n,k$。

第二行，$n$ 个非负整数 $d_1, d_2, \ldots, d_n$。

接下来 $k$ 行，第 $i$ 行 $n + 1$ 个整数 $a_{i, 1}, a_{i, 2}, \ldots, a_{i, n}, x_i$，每行最后一个整数 $x_i$ 表示 $p_i=x_i\times 10^{-8}$。

输入的 $x_i$ 保证了 $p_i > 0$ 且 $p < 1$。

保证每个 $x_i$ 在所有可能的组合中等概率随机生成。
## 输出格式

一行，一个整数，表示答案对 $998244353$ 取模的结果。

如果你不知道如何进行实数取模：可以说明答案一定是有限的，且是有理数，设它的最简分数形式为 $\frac{p}{q}$。如果存在一个整数 $x$ 满足 $x \cdot q \equiv p \pmod{998244353}$ 且 $0 \le x < 998244353$，那么你只需输出 $x$ 的值即可。

由于保证了 $x_i$ 是随机生成的，可以说明以接近 $1$ 的概率答案在模意义下存在。事实上，一个当 $x_i$ 尚不确定时以合理地高的概率给出正确答案的算法足以通过本题，考察复杂的模意义下的有理数的处理不是我们的本意。
## 样例

### 样例输入 #1
```
2 1
1 1
0 0 50000000

```
### 样例输出 #1
```
14

```
### 样例输入 #2
```
2 1
1 2
0 0 20000000

```
### 样例输出 #2
```
291154624

```
### 样例输入 #3
```
3 3
2 3 4
2 1 0 30000000
1 2 3 19000000
2 3 4 1000000

```
### 样例输出 #3
```
430536142

```
## 提示

**【样例解释 \#1】**

这是你的一种追寻梦想的方式：

你从 $(0,0)$ 出发，走一步到 $(1,0)$，再走一步到 $(2,0)$，再走一步到 $(3,0)$，但是在路上散入天际，从 $(0,0)$ 重新开始旅程。

然后继续从 $(0,0)$ 出发，走一步到 $(0,1)$，再走一步到 $(1,1)$，但是在路上散入天际，从 $(0,0)$ 重新开始旅程。

接着从 $(0,0)$ 出发，走一步到 $(1,0)$，再走一步到 $(1,1)$，找到了你的梦想。

在这种情况下，你需要 $7$ 步到达这个梦想。发生这种情况的概率是 $4^{-7}$。

---

**【样例解释 \#2】**

答案为 $\frac{505}{24} \approx 21.041667$。  
不难验证 $291154624 \times 24 \equiv 505 \pmod{998244353}$，故应输出 $291154624$。

---

**【样例解释 \#3】**

答案为 $\frac{1399505}{21519} \approx 65.035782$。

---

**【数据范围】**

**本题采用捆绑测试且使用子任务依赖。**

| 子任务编号 | 特殊限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $n=1$，$k=1$ | 11 |
| 2 | $n=1$ | 12 |
| 3 | $k=1$ | 12 |
| 4 | $n=2$，$1 \le d_1 \cdot d_2 \le 200$ | 13 |
| 5 | $k \le 200$ | 22 |
| 6 | 无特殊限制 | 30 |

对于 $100 \%$ 的数据：

- $1 \le n \le 100$，$1 \le k \le 10000$。
- $d_i \ge 0$，$\sum_i d_i \le 10^7$。
- $0 \le a_{i, j} \le {10}^7$。
- $x_i \ge 1$，$\sum_i x_i < {10}^8$。此即保证了 $p_i > 0$ 和 $p < 1$。
- 保证存在一个 $i \in [1, k]$ 使得对于每个 $j \in [1, n]$ 均有 $a_{i,j} \le d_j$。
- 保证每个 $(a_{i, 1}, a_{i, 2}, \ldots, a_{i, n})$ 作为空间中的点互不相同。
- 保证每个 $x_i$ 在所有可能的组合中等概率随机生成。

---

**【提示】**

由于保证了 $x_i$ 是随机生成的，可以说明以接近 $1$ 的概率答案在模意义下存在。事实上，一个当 $x_i$ 尚不确定时以合理地高的概率给出正确答案的算法足以通过本题，考察复杂的模意义下的有理数的处理不是我们的本意。

样例中的 $x_i$ 不是随机生成的，仅为理解题意所用。


---

---
title: "[THUPC 2023 决赛] 老虎机"
layout: "post"
diff: 省选/NOI-
pid: P9379
tag: ['2023', 'O2优化', '条件概率', '期望', 'THUPC', '状压 DP']
---
# [THUPC 2023 决赛] 老虎机
## 题目描述

小 I 经营着一个电玩城，最近引进的新型老虎机深受欢迎。

作为经营者，小 I 首先需要设定老虎机的状态。老虎机的状态为一个三元组 $(l,S,\mathbf{p})$，其中

- $l$ 是一个正整数；
- $S$ 是一个非空字符串集合，其中所有的字符串均是长度为 $l$ 的 01 串；
- $\mathbf{p}$ 是一个长度为 $l$ 的实数序列 $p_0,p_1,\dots,p_{l-1}$，其中对于任意 $0 \le i \le l - 1$，$0 < p_i \le 1$。

设定好状态后即可开始游戏。每一轮游戏的流程如下：

- 玩家首先获得老虎机的状态 $(l,S,\mathbf{p})$。
- 老虎机内部选择一个串 $s \in S$ 作为答案串，玩家需要通过与老虎机进行若干次交互得到答案串。
  - 每一次交互中，玩家投入一个游戏币并拉下老虎机的拉杆，然后老虎机的界面中会出现一个长度为 $l$ 的信息串 $t$。对于 $0 \le i \le l - 1$，$t_i$ 有 $p_i$ 的概率为 $s_i$，有 $(1-p_i)$ 的概率为 `?`。
  - 交互过程中生成信息串进行的所有随机过程两两独立。
- 当玩家可以根据**老虎机的状态和交互得到的若干信息串**唯一确定答案串后，即可将答案串输入老虎机并结束游戏、获得奖励。

小 I 设定好了一个状态，但还不知道设定多少奖励。为了让奖励和难度匹配，小 I 想知道：对于 $S$ 中的每个串 $t$，在玩家以最优策略游玩（即一旦可以唯一确定答案串就结束游戏）的情况下，若答案串为 $t$，玩家期望需要投入多少游戏币。

由于小 I 不喜欢实数，你需要将答案对 $998244353$ 取模。
## 输入格式

**本题有多组测试数据。** 第一行一个整数 $T$ 表示测试数据组数，接下来依次输入每组测试数据。

对于每组测试数据，

- 第一行两个整数 $l,n$，表示字符串长度和 $S$ 的大小。
- 第二行 $l$ 个整数 $c_0,c_1,\dots,c_{l-1}$，其中 $p_i = \frac{c_i}{10^4}$。
- 接下来 $n$ 行，第 $i$ 行一个长度为 $l$ 的 01 串 $s_i$，描述 $S$ 中的一个字符串。
## 输出格式

对于每组测试数据输出 $n$ 行，第 $i$ 行表示答案串为 $s_i$ 时，在最优策略下玩家期望投入多少游戏币，对 $998244353$ 取模，题目保证这个值总是在模意义下存在。
## 样例

### 样例输入 #1
```
4
1 2
5000
0
1
2 3
1 10000
00
01
10
1 1
1
1
3 4
8888 7777 5555
000
010
101
110

```
### 样例输出 #1
```
2
2
10000
1
10000
0
209031157
194428714
835313860
674719626

```
## 提示

**【样例解释 #1】**

- 对于第一组测试数据，每一次交互有 $\frac{5000}{10000} = \frac{1}{2}$ 的概率知道答案串是 $0$ 还是 $1$，有 $\frac{1}{2}$ 的概率不能获得信息，因此期望游戏币数为 $\sum_{i=1}^{+\infty} \frac{i}{2^i} = 2$。
- 对于第二组测试数据，每一次交互都可以得到字符串的第二位，有 $\frac{1}{10000}$ 的概率得到字符串的第一位。第二个字符串为答案串时可以通过字符串的第二位唯一确定，而其他两个字符串为答案串时必须要得到字符串的第一位。
- 对于第三组测试数据，由于 $|S| = 1$，所以不需要任何交互就可以确定答案串。
- 对于第四组测试数据，我有一个绝妙的解释，可这里空间太小写不下。

**【数据范围】**

对于所有测试数据，$1 \le T \le 10$，$1 \le l \le 15$，$1 \le n \le 2^l$，$1 \le c_i \le 10^4$，$s_1,\dots,s_n$ 为两两不同的长度为 $l$ 的 01 串。

**【后记】**

“喂喂喂，未成年人不准进入电玩城！什么？你们说你们要进去学算法竞赛？谁信你的鬼话！”

**【题目来源】**


来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）决赛。

题解等资源可在 [https://github.com/THUSAAC/THUPC2023](https://github.com/THUSAAC/THUPC2023) 查看。


---

---
title: "「DBOI」Round 1 烟花"
layout: "post"
diff: 省选/NOI-
pid: P9398
tag: ['数学', 'O2优化', '树论', '组合数学', '排列组合', '期望']
---
# 「DBOI」Round 1 烟花
## 题目背景

回忆本身就是惩罚，惩罚那些不愿往前走的人，将他们困在那条小巷子里，怎么也走不出去。

每一年都有烟花，唯独那一年的烟花最好看。

“我要对烟花许愿，许我们永远在一起。”

“就算不许愿，我们也会永远在一起的。”

再后来，死了的人被葬在了那座山上，活着的人被记忆困在了那条巷中。今天的我们听到这个故事，只是想再放一次故事里的烟花，放给那些再没能陪身旁的人看到一次烟花的人。
## 题目描述

烟花在夜空中绽放连成一片，我们把这些连成一片的烟花看成一棵含有 $n$ 个点的有根树，根为最早点燃的烟花 $1$。

烟花有红蓝两种颜色，为了方便，我们对这棵树黑白染色。最初有 $p$ 个限制，一条限制形如 $(x_i,y_i)$，表示树中编号为 $x_i$ 的点的子树中黑点只能**恰好**有 $y_i$ 个。当年，他们认为满足其**子树内所有有限制点的限制**的子树是**均好的子树**。显然，要想使一个子树成为均好的子树，可能有**多种染色方法**。

你需要回答以下两种询问：

- `Z k c`，表示给点 $k$ 以均等概率在 $[0,c]$ 中选择一个数 $f$，然后给点 $k$ 直接加上 $f$ 个没有限制的儿子，其它儿子状态不变。问点 $k$ 为根的子树成为**均好的子树**的期望染色方法数量。
- `H k`，表示如果去掉 $k$ 的所有有限制儿子的限制，询问 $k$ 为根的子树成为**均好的子树**的染色方法数量。

我们并没有必要点燃更多的烟花，因此所有的询问都是相互独立的，没有询问会真的影响原树。

我们深知可能复现不了当时完整的情况，历史太过斑驳，可能的烟花组合成千上万，因此你只需要得到答案对 $998244353$ 这个大质数取模的值。
## 输入格式

第一行两个整数 $n,p$，表示树的节点个数与限制个数。

接下来 $n-1$ 行，每行两个数 $u,v$，表示 $u,v$ 之间有一条直连边。这 $n-1$ 行表示树的结构。

接下来 $p$ 行，每行两个数 $(x_i,y_i)$，表示限制以 $x_i$ 点为根的子树，需要恰好存在 $y_i$ 个黑点在其子树内。

接下来一行一个整数 $q$，表示询问个数。

接下来 $q$ 行，每行一个字符另加 $1$ 或 $2$ 个整数表示题目中说明的询问。
## 输出格式

为了减小输出量，我们假设第 $i$ 个询问（$i$ 从 $1$ 开始）的答案为 $ans_i$，你只需要输出一行，表示所有询问的 $i\times ans_i$ 的异或和。最终的异或和以及每一个 $i\times ans_i$ 都**无需**对 $998244353$ 取模，但每个询问的答案 $ans_i$ 是对其取模后的答案。

**注意：std 不依赖于输出方式。也就是说，std 可以独立获取每一个询问的答案。**
## 样例

### 样例输入 #1
```
14 5
1 2
1 3
4 1
5 2
2 6
3 7
3 8
9 4
12 6
11 6
6 10
8 13
14 8
2 3
10 0
7 1
13 1
14 0
10
Z 2 5
H 14
Z 7 3
Z 7 1
H 6
Z 1 9
H 1
H 8
H 12
Z 10 1
```
### 样例输出 #1
```
665340330
```
## 提示

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/523p3yhk.png)

如图为样例 #1 的烟花，构成一个有 $14$ 个点，其中 $5$ 个限制点的树。与题目中不同的是，我们用红色烟花表示限制点，蓝色烟花表示无限制点。红色烟花右上角的浅蓝色数字表示其限制的黑点数量。

初始情况下每一个点为根子树的合法烟花燃放方法数量如下（从左至右第 $i$ 项表示以第 $i$ 个点为根的子树的答案）：

$$
[320,10,4,4,2,8,1,2,2,1,2,2,1,1]
$$

下面我们给出询问的答案与部分解释：

- `Z 2 5`，为 $2$ 号点添加 $i$ 个儿子后的 $2$ 号点子树内合法烟花燃放数量表示为此数列的第 $i+1$ 项：$[10,20,35,56,84,120]$。总期望即为 $\frac{325}{6}$。对 $998244353$ 取模之后得到 $166374113$。
- `H 14`，由于 $14$ 号点没有儿子，因此答案仍然为 $1$。
- `Z 7 3`，共有 $10$ 种可能的合法烟花燃放方案，总期望即为 $\frac{5}{2}$，对 $998244353$ 取模之后得到 $499122179$。
- `Z 7 1` 的答案为 $499122178$。
- `H 6` 的答案为 $16$。
- `Z 1 9` 的答案为 $32736$。
- `H 1`，去除 $1$ 的所有有限制儿子（仅有节点 $2$）的限制后有 $1024$ 种可能的合法烟花燃放方案。
- `H 8` 的答案为 $8$。
- `H 12` 没有儿子，因此答案不变，此询问的答案仍然为 $2$。
- `Z 10 1` 的答案为 $1$。

最终，所有询问的 $i\times ans_i$ 的异或和即为 $665340330$。

### 数据范围

**请注意常数因子对程序效率的影响。**

**本题采用捆绑测试与子任务依赖。**

下面定义 $S=3\times 10^5$。

| $\rm Subtask$ | $n$ | $q$ | $y_i$ | $c$ | 特殊性质 | 得分 | 子任务依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leqslant 10$ | $\leqslant 10$ | $\leqslant 5$ | $\leqslant 5$ | 无 | $10$ | 无 |
| $2$ | $\leqslant 200$  | $\leqslant 200$ | $\leqslant 200$ | $\leqslant 200$ | 无 | $15$ | $1$ |
| $3$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $\leqslant 10$ | 无 | $20$ | $1,2$ |
| $4$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $A$ | $15$ | 无 |
| $5$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $B$ | $20$ | 无 |
| $6$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | 无 | $20$ | $1,2,3,4,5$ |

特殊性质 $A$：$p=0$。

特殊性质 $B$：满足不存在 `Z` 询问。

对于 $100\%$ 的数据，存在输入的所有数均为 $\leqslant S$ 的整数。特别地，存在 $0\leqslant p\leqslant n$，输入的任何树的节点编号 $x$ 都满足 $1\leqslant x \leqslant n$。保证输入的询问字符都为 `Z` 或 `H`，输入的一定是一棵树。保证对于所有限制存在 $x_i\neq x_j(i\neq j)$。


------------

冬天的最后一场雪如约而至，很快又要迎来一个新的春天。万物都在等待复苏，可峰城里的一个小巷子，再也不复往日繁荣。

八十多年过去，我们早已找不到当初的巷子，只留下这样一个故事。

感谢你放的烟花。


---

---
title: "[ZSHOI-R1] 巡城"
layout: "post"
diff: 省选/NOI-
pid: P9454
tag: ['动态规划 DP', '期望']
---
# [ZSHOI-R1] 巡城
## 题目背景

在 X 国国王多年的建设之下，她的国家发生了质的蜕变，从众多 $n$ 座城市却只有 $n-1$ 条道路的国家中脱颖而出。也就是说，X 国不再是一棵树了，而是一张图。
## 题目描述

国王为了能够集中自己的权力，稳固城邦，她对国家道路设计要求十分严苛，**任何两个城市之间的路径至多只有一条不经过首都**，虽然但是，没有人知道为什么这样能够更好地稳固 X 国。

有一天，X 国国王决定巡视所有的城市，她通过无线电在巡城前一天向所有的城市通知了这个好消息。热情的群众们也积极地做出了响应，准备迎接国王的到来。

国王一天只能造访一座城市，而且第一天她会从首都开始。

在之后的每一天，她会随机从与她所在城市直接相连的城市中**等概率**地选择一个她**没有前往过的城市**前往。如果不存在这样的城市，她会立即**原路返回**，从她来这个城市的路回去，再重复上述操作，因为有携带宇宙射线的传送门，这个过程**不消耗时间**。

爱戴她的群众们想要知道，他们的国王第一次到达他们所在城市的日期（她造访首都的那一天为 $1$，之后每一天一次加 $1$）的期望是多少，答案对 $998244353$ 取模。

保证城市构成的图是连通图，无自环与重边，且首都编号为 $1$。
## 输入格式

第一行有两个数 $n,m$，代表X国的城市数和路径数。

接下来的 $m$ 行，每行两个数 $u,v$ 表示城市的一条路径。
## 输出格式

共 $1$ 行，$n$ 个数。

第 $i$ 个数代表 $i$ 号城市的期望。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
```
### 样例输出 #1
```
1 2 3 

```
### 样例输入 #2
```
4 3
1 2
2 3
2 4

```
### 样例输出 #2
```
1 2 499122180 499122180 

```
### 样例输入 #3
```
5 7
5 4
2 4
4 3
1 3
1 2
1 4
1 5

```
### 样例输出 #3
```
1 249561092 249561092 249561091 249561092 

```
## 提示

对于所有的数据点，$1\leqslant n\leqslant 5 \times 10^5$，$1\leqslant m \leqslant 6 \times 10^5$。
| 数据点 | n | m |
| :----------: | :----------: | :----------: |
| 1~2 | $5$ | $7$ |
| 3~5 | $\leqslant10^4$ | $n-1$ |
| 6~8 | $\leqslant10^4$ | $n$ |
| 9~10 | $\leqslant10^4$ | $2n-3$ |
| 11~15 | $\leqslant10^4$ | $\leqslant2\times10^4$ |
| 16~20 | $\leqslant5\times10^5$ | $\leqslant6\times10^5$ |


---

