---
title: "「QMSOI R1」 三服同构"
layout: "post"
diff: 提高+/省选-
pid: P11070
tag: ['动态规划 DP', 'Special Judge', 'O2优化', '概率论', '期望']
---
# 「QMSOI R1」 三服同构
## 题目背景

前不久，三国杀上线了一位三服同构的赛事专属武将...

[那这道题与SP孙策的关系呢？](https://www.luogu.com.cn/paste/g68kquaa)

![](https://patchwiki.biligame.com/images/sgs/thumb/4/46/ekgr28n00suo1zkuksp047802wfl4a6.png/401px-SP%E5%AD%99%E7%AD%96-%E7%BB%8F%E5%85%B8%E5%BD%A2%E8%B1%A1.png)
## 题目描述

现在有 $4$ 种扑克牌：红桃 A，红桃 K，黑桃 A，黑桃 K，小 Q 的手上现在有 $n$ 张黑桃牌，$m$ 张红桃牌，其中有 $u$ 张黑桃 A，$v$ 张红桃 A，而对手有 $k$ 张牌。

现在小 Q 知道对手第 $i$ 张牌点数为 A 的概率为 $a_i$，接下来他将持续执行以下操作，直到他的回合结束。

1. 若你手中有至少 $1$ 张红桃 A 或红桃 K，则你**必须**等概率随机弃置 $1$ 张花色为红桃的牌，并与对手进行决斗。
2. 否则，你结束你的回合。

决斗的流程如下：

从对手开始，双方交替进行以下操作：

1. 若其手上有至少 $1$ 张红桃 A 或黑桃 A，则其**必须**等概率随机弃置 $1$ 张点数为 A 的牌。
2. 否则，其受到 $1$ 点伤害,并结束此次决斗。

现在你想要知道在你的回合结束前，对手期望会受到多少点伤害。
## 输入格式

第一行 $5$ 个整数分别表示 $n,m,u,v,k$。

第二行 $k$ 个实数，依次表示 $a_1,a_2,\cdots,a_k$。
## 输出格式

输出一行一个实数，表示期望伤害。

**本题使用 Special Judge 进行评测**，只要你的答案与标准输出**绝对误差**在 $10^{-6}$ 以内，则判定答案正确。
## 样例

### 样例输入 #1
```
2 2 1 1 2
0.2 0.8
```
### 样例输出 #1
```
1.670000000
```
## 提示

### 样例解释

可以得出对手牌中有 $0,1,2$ 张 A 的概率分别为 $0.16,0.68,0.16$。

当对手牌中有 $0$ 张 A 时，无论小 Q 每次耗费的哪张红色牌，都能对对手造成伤害，所以这种情况期望伤害为 $0.16*2=0.32$。

当对手牌中有 $1$ 张 A 时，假设小 Q 第一次耗费的是 A 进行决斗，那对手打出 A 后，小 Q 就会打出一张黑桃 A，对手没 A 了就会受到伤害，而小 Q 的另一张红桃 K 依然能被耗费，以进行决斗对对手造成伤害，所以这种情况期望伤害为 $0.68*0.5*2=0.68$。

当对手牌中有 $1$ 张 A 时，假设小 Q 第一次耗费的是 K 进行决斗，那对手打出 A 后，小 Q 打出黑桃 A 或红桃 A 的概率就是相等的，然后对手没 A 了就会受到伤害，但是如果打出的是红桃 A 就无法再进行决斗了，而打出黑桃 A 另一张红桃 A 依然被耗费，进行决斗对对手造成伤害，所以这种情况期望伤害为 $0.68*0.5*0.5*1+0.68*0.5*0.5*2=0.51$。

当对手牌中有 $2$ 张 A，这时如果小 Q 先耗费的 A 进行决斗，那对手打出 A 后，小 Q 就会打出一张黑桃 A，对手再打出 A 后，小 Q 就会受到伤害，而小 Q 的另一张红桃 K 依然能被耗费，以进行决斗对对手造成伤害，所以这种情况期望伤害为 $0.16*0.5*1=0.08$。

当对手牌中有 $2$ 张 A，这时如果小 Q 先耗费的 K 进行决斗，双方就会各打出两张 A，然后敌人受到伤害，小 Q 就不能再进行决斗了，所以这种情况期望伤害同样为 $0.16*0.5*1=0.08$。

所以对手受到的期望伤害就是 $0.32+0.68+0.51+0.08+0.08=1.67$。

### 数据范围
**本题使用 subtask 进行捆绑测试**，每个 subtask 的具体分值如下：
| 子任务 | 值域 | 分值 |
| :----------: | :----------: | :----------: |
| $0$ | $1\le n,m\le 10$ | $30$ |
| $1$ | $1\le n,m\le 2000$ | $70$ |

对于所有的数据，满足 $1 \leq n,m,k \leq 2000,1\le u<n,1\le v <m$。


---

---
title: "[USTCPC 2025] 公平抉择"
layout: "post"
diff: 提高+/省选-
pid: P12040
tag: ['2025', '数论', '概率论', '期望', '高校校赛']
---
# [USTCPC 2025] 公平抉择
## 题目背景

考虑到评测机性能差异，改为 400ms 时限。USTCPC 时限为 600ms。

**请注意本题非常规时空限制！**

所以要“费厄”，最好是首先看清对手，倘是些不配承受“费厄”的，大可以老实不客气；待到它也“费厄”了，然后再与它讲“费厄”不迟。(节选自鲁迅《论“费厄泼赖”应该缓行》)

克露丝卡尔酱选择困难！她甚至无法抉择午饭去吃什么，作为她的朋友，你需要和她一起完整**公平的抉择**。
## 题目描述

克露丝卡尔酱在做选择，食堂共有 $n$ 种菜品可选，而她手里只有一个 $k$ 面的骰子(如果 $k = 2$ 则为硬币)。

为了落实公平抉择的理念，她希望她的策略选择到每个菜品的概率相等。

求她期望投掷次数的最小值，**答案对质数 $M$ 取模**。
## 输入格式

一行三个正整数 $n, k, M$ ,分别表示选项数、骰子面数和模数。

$2 \le k \le n \le 3 \times 10^6$，$10^8 \le M \le 10^9$，**保证 $M$ 为质数且对于任意 $1 \le i \le n,k^i \bmod M > 1$**。
## 输出格式

一个整数表示模意义下的答案。

关于分数取模：设答案为 $\dfrac{q}{p}$ 且 $M \nmid p,q$，那么取模结果 $x$ 为 唯一 $x\in[0,M)$ 使得 $px\equiv q\pmod M$。
## 样例

### 样例输入 #1
```
3 2 998244353
```
### 样例输出 #1
```
665496238
```
### 样例输入 #2
```
10 2 998244353
```
### 样例输出 #2
```
798595487
```
## 提示

在样例 $1$ 中，不妨设答案为 $E$。考虑扔两次硬币，得到四种情况，出现概率各为 $\dfrac{1}4$。前三种情况分配给三种菜品，第四种情况重投。故 $E=2+\dfrac{E}4$，解得 $E=\dfrac{8}3$。


---

---
title: "[Math×Girl] 距离"
layout: "post"
diff: 提高+/省选-
pid: P12468
tag: ['数学', 'O2优化', '概率论', '根号分治']
---
# [Math×Girl] 距离
## 题目背景

>“哥哥，你说什么呢？” 尤里问道。  
>“看上去仙女座也在研究数学。”我回答道。  
>“那里也有图书室吗？”泰朵拉微笑道。  
>“以居住的星球为模，是不是存在跟我们同余的宇宙人呢？”米尔嘉说道。

## 题目描述

给你两个数 $a$ 和 $b$ ，每次可以对任意一个数 $\pm1$。  
求最少进行多少次操作，才能使 $a\mid b$ 或 $b\mid a$。

其中 $\mid$ 为整除符号，$a\mid b$ 表示 $a$ 整除 $b$。  

## 输入格式

本题有多组数据，第一行输入一个整数 $T$，表示数据组数。 

对于每一组询问，我们给出 $a,b$。
## 输出格式

对于每组数据，一行输出一个数表示操作次数。 
## 样例

### 样例输入 #1
```
3
15 33
2024 34
1145141919810721 987654321666
```
### 样例输出 #1
```
2
7
388749955
```
## 提示

### 样例解释

第一个例子为 $(15+1)\mid(33-1)$。  
第二个例子为 $(34+1)\mid(2024+6)$。  

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $15$ | $a,b\in[1,10^4]$ |
| $1$ | $10$ | $T\in[1,10],a,b\in[1,10^8]$ |
| $2$ | $5$ | $a,b\in[1,10^8]$ |
| $3$ | $20$ | $T\in[1,10],\frac{a}{b}\in[10^{-8},10^8]$ |
| $4$ | $5$ | $\frac{a}{b}\in[10^{-8},10^8]$ |
| $5$ | $25$ | $T\in[1,10]$ |
| $6$ | $20$ | - |

对于 $100\%$ 数据，保证 $T\in[1,1000],a,b\in[1,10^{16}]$。

本题请相信你的算法的常数。


---

---
title: "[GCJ 2021 Qualification] Cheating Detection"
layout: "post"
diff: 提高+/省选-
pid: P13025
tag: ['2021', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2021 Qualification] Cheating Detection
## 题目描述

100 players are competing in a 10000-question trivia tournament; the players are numbered from 1 to 100. Player $i$ has a skill level of $S_i$ and question $j$ has a difficulty level of $Q_j$. Each skill level and each question difficulty are chosen uniformly at random from the range $[-3.00, 3.00]$, and independently of all other choices. For example, a player can have a skill level of 2.47853 and a question can have a difficulty level of -1.4172.

When player $i$ tries to answer question $j$, the probability that they answer it correctly is $f(S_i - Q_j)$, where $f$ is the sigmoid function:

$$f(x) = \frac{1}{1 + e^{-x}}$$

where $e$ is Euler's number (approximately 2.718...), the mathematical constant. Notice that $0 < f(x) < 1$ for all $x$, so $f(S_i - Q_j)$ is always a valid probability. Each of these answer attempts is chosen at random independently of all other choices.

There is one exception: exactly one of the players is a cheater! The cheater is chosen uniformly at random from among all players, and independently of all other choices. The cheater behaves as follows: before answering each question, they flip a fair coin. If it comes up heads, they do not cheat and the rules work as normal. If it comes up tails, they secretly look up the answer on the Internet and answer the question correctly. Formally, they decide whether to cheat at random with 0.5 probability for each question, independently of all other choices.

The results of a tournament consist of only the per-question results (correct or incorrect) for each player. Apart from the general description above, you do not know anything about the skill levels of the players or the difficulties of the questions.

You must correctly identify the cheater in at least $\mathbf{P}$ percent of the test cases. That is, you must succeed in at least $\mathbf{P} \cdot \mathbf{T}/100$ out of $\mathbf{T}$ cases.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. The second line of the input gives the percentage of test cases, $\mathbf{P}$, that you must answer correctly for your solution to be considered correct. $\mathbf{T}$ test cases follow. Each case consists of 100 lines of 10000 characters each. The $j$-th character on the $i$-th line is $1$ if the $i$-th player answered the $j$-th question correctly, or $0$ if they answered it incorrectly.
## 输出格式

For each test case, output one line containing Case #$x$: $y$, where $x$ is the test case number (starting from 1) and $y$ is the number of the cheater (with player numbers starting from 1).
## 样例

### 样例输入 #1
```
Use the download button above to view the full sample input.
```
### 样例输出 #1
```
Use the download button above to view the full sample input.
```
## 提示

**Sample Explanation**

Notice that the sample input uses $\mathbf{T} = 1$ and $\mathbf{P} = 0$ and therefore does not meet the limits of any test set. The sample output for it is the actual cheater.

**Limits**

- $\mathbf{T} = 50$.

**Test Set 1 (11 Pts, Visible Verdict)**

- $\mathbf{P} = 10$.

**Test Set 2 (20 Pts, Visible Verdict)**

- $\mathbf{P} = 86$.


---

---
title: "[GCJ 2021 #1B] Digit Blocks"
layout: "post"
diff: 提高+/省选-
pid: P13031
tag: ['动态规划 DP', '贪心', '2021', '交互题', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2021 #1B] Digit Blocks
## 题目描述

You are going to build $N$ towers of $B$ cubic blocks each, one block at a time. Towers are built bottom-up: the $i$-th block to be placed in a tower ends up as the $i$-th from the bottom. You need to decide where to place each block before getting to see any of the upcoming blocks, and once placed, blocks cannot be moved.

Each block has a single decimal digit printed on it, and towers are built such that the faces with digits are all facing the front. The font is such that blocks cannot be rotated to obtain a different digit (for example, a block with a 6 on it cannot be rotated to obtain a block with a 9 on it, nor vice versa).

For example, suppose $N = 3$ and $B = 3$ and you currently have towers as shown in Picture 1. If a block with a 6 shows up next, you have two options: either place it on top of the tower with only two blocks (as shown in Picture 2) or start the third tower (as shown in Picture 3). Note that you cannot put it on top of the first tower since the first tower already has $B$ blocks.


After the building is done, we read the $B$ digit integer printed on the front of each tower from the top to the bottom (that is, the digit on the last block placed on a tower is the most significant digit). Notice that these integers may have any number of leading zeroes. Then, we add those $N$ integers together to obtain the score of our building operation.

![](https://cdn.luogu.com.cn/upload/image_hosting/47a718u8.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/c8lwc9qg.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/wdg8ljcv.png)

For example, in Picture 4 below, the integers read on each tower, from left to right, are $123$, $345$, and $96$. The score of that building operation would be $123 + 345 + 96 = 564$.

![](https://cdn.luogu.com.cn/upload/image_hosting/6aiwqzwm.png)

The digit for each block is generated uniformly at random, and independently of any other information. In order for your solution to be judged correct, the sum of its scores over all $\textbf{T}$ test cases must be at least $\textbf{P}$.

### Interactive Protocol

This is an interactive problem.

Initially the judge will send you a single line containing four integers $\textbf{T}$, $\textbf{N}$, $\textbf{B}$, and $\textbf{P}$: the number of test cases, the number of towers, the number of blocks in each tower, and the minimum total score you need to reach to pass this test set.

Then, you must process $\textbf{T}$ test cases. Each test case consists of $\textbf{N} \times \textbf{B}$ exchanges. Each exchange corresponds to placing one block. Within each exchange, the judge will first print a line containing a single integer $\textbf{D}$ representing the digit printed on the block you need to place. You need to respond with a single line containing a single integer $\textbf{i}$, the number (between $1$ and $\textbf{N}$) of the tower you want to place that block on.

After the last exchange of each test case except the last one, the judge will immediately start the next test case. After the last exchange of the last test case, the judge will print an additional line containing a single integer: $1$ if your total score is at least $\textbf{P}$ or $-1$ if it is not.

If the judge receives an invalidly formatted line, an invalid tower number, or the number of a tower that already contains $\textbf{B}$ blocks from your program, the judge will print a single number $-1$. After the judge prints $-1$ for any of the reasons explained above, it will not print any further output. If your program continues to wait for the judge after receiving a $-1$, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.

You can assume that the digit for each block is generated uniformly at random, and independently for each digit, for each test case and for each submission. Therefore even if you submit exactly the same code twice, the judge could use different random digits.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
2 3 3 1500
3

2

5

4

1

6

3

9

0
```
### 样例输出 #1
```


1

1

2

2

1

3

2

3

3
```
## 提示

**Sample Explanation**

In the sample, we are now at the state shown in Picture 4 (sum = 564).

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our interactive runner for that.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

- $\textbf{T} = 50$.
- $\textbf{N} = 20$.
- $\textbf{B} = 15$.
- $\textbf{D}$ is a decimal digit between $0$ and $9$.

**Test Set 1 (16 Pts, Visible Verdict)**

$\textbf{P} = 860939810732536850$ (approximately $8.6 \times 10^{17}$).

Note that this boundary is chosen as approximately $90\%$ of $\textbf{T} \times S$, where $S = 19131995794056374.42\dots$ (approximately $1.9 \times 10^{16}$) is the highest possible expected score that a solution to this problem can achieve on one test case given unbounded running time.

The exact value of $S$ as defined above can be found in lines 13 and 14 of the local testing tool.

**Test Set 2 (21 Pts, Visible Verdict)**

$\textbf{P} = 937467793908762347$ (approximately $9.37 \times 10^{17}$).

Note that this boundary is chosen as approximately $98\%$ of $\textbf{T} \times S$.


---

---
title: "[GCJ 2020 #1B] Blindfolded Bullseye"
layout: "post"
diff: 提高+/省选-
pid: P13057
tag: ['计算几何', '2020', '二分', '交互题', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2020 #1B] Blindfolded Bullseye
## 题目描述

Gary has a large square wall that is exactly $2 \times 10^{9}$ nanometers tall and $2 \times 10^{9}$ nanometers wide. Gary has a dartboard placed on the wall. The dartboard is circular and its radius is between A and B nanometers, inclusive. The dartboard is fully contained within the wall, but it may touch its edges. The center of the dartboard is an integer number of nanometers from each edge of the wall.

Gary invited his friend Mika over to play an interesting game. Gary blindfolds Mika and challenges her to throw a dart at the center of the dartboard. To help her, whenever Mika throws a dart at the wall, Gary will tell her whether the dart hit the dartboard.

Mika does not know where on the wall the dartboard is, but since Mika is very skilled at darts, she can throw darts with nanometer precision. That is, she can aim and hit exactly any point that is an integer number of nanometers away from each edge of the wall. Immediately after throwing each dart, Gary tells her whether she hit the center of the dartboard, some other part of it, or missed it completely and hit the bare wall.

Can you help Mika hit the center of the dartboard, without throwing more than 300 darts?

### Interactive Protocol

Initially, your program should read a single line containing three integers $\mathbf{T}$, $\mathbf{A}$ and $\mathbf{B}$, indicating the number of test cases and the inclusive minimum and maximum values for the dartboard's radius, in nanometers, respectively. (Notice that $\mathbf{A}$ and $\mathbf{B}$ are the same for every test case within a test set.) Then, you need to process $\mathbf{T}$ test cases.

We represent the points that darts can be aimed at as pairs $(x, y)$, where $x$ and $y$ are integers between $-10^{9}$ and $10^{9}$, inclusive. The pair $(x, y)$ is the point that is $x + 10^{9}$ nanometers away from the left edge of the wall and $y + 10^{9}$ nanometers away from the bottom edge of the wall. Point $(0, 0)$ is therefore at the exact center of the wall.

For each test case, there is a secretly chosen radius $R$ for the dartboard, and a secretly chosen center of the dartboard $(X, Y)$. $R$, $X$, and $Y$ are integers chosen for each test case by the judges in a designed (not random) way, within the limits. For each test case you need to process up to 300 exchanges with the judge. Your program represents Mika and the judge program represents Gary. Each exchange consists of Mika (your program) choosing where to throw a dart and Gary (the judging program) giving information about that position.

The $i$-th exchange consists of your program first outputting a single line containing two integers $X_{i}$ and $Y_{i}$, both between $-10^{9}$ and $10^{9}$, inclusive, and the judge responding with a single line containing either:

* `CENTER` if $X_{i} = X$ and $Y_{i} = Y$
* `HIT` if $0 < (X - X_{i})^{2} + (Y - Y_{i})^{2} \leq R^{2}$
* `MISS` in all other cases.

After sending CENTER, the judge will start waiting for the first exchange of the next test case, if there is any.

If you output a line that is incorrectly formatted or with an out of bounds value, the judge will respond with a single line containing WRONG. If 300 exchanges occur (including 300 responses from the judge) without you receiving CENTER, or if you ever receive WRONG, the judge will finish all communication, wait for your own program to also finish, and give a Wrong Answer verdict. After sending the $T$-th CENTER, on the other hand, the judge will finish all communication, wait for your own program to finish, and give a Correct verdict. If, while waiting for your program to finish, time or memory limits are exceeded, the corresponding verdict will be assigned instead. (Note that verdicts are not messages sent to your program.)
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```

```
### 样例输出 #1
```

```
## 提示

**Sample Explanation**

The following sample interaction uses the limits of Test Set 1.

```
  // The following reads 20 into t and 999999995 into a and b.
  t, a, b = readline_int_list()
  // The judge secretly picks R = 999999995 (it had no choice) and X = -1,
  // Y = 3 (it did have a choice here). (Note: the actual Test Set 1 will
  // not necessarily use the values in this example.)
  // We try to throw at the upper left corner of the wall, and the dartboard
  // does not overlap with that point.
  printline -1000000000 1000000000 to stdout
  flush stdout
  r = readline_string()  // reads MISS.
  // We try to throw at the center of the wall. That does hit the dartboard,
  // but not the center.
  printline 0 0 to stdout
  flush stdout
  r = readline_string()  // reads HIT.
  // We make a super lucky choice and throw at the center of the dartboard.
  printline -1 3 to stdout
  flush stdout
  r = readline_string()  // reads CENTER.
  // The judge begins the next test case. It secretly picks R = 999999995
  // and X = 5, Y = 5.
  // We accidentally throw a dart out of the allowed range.
  printline -1234567890 1234567890 to stdout
  flush stdout
  r = readline_string()  // reads WRONG.
  exit  // exits to avoid an ambiguous TLE error.
```

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our [interactive runner](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py) for that.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 20$.
- $\mathbf{A} \leqslant \mathbf{R} \leqslant \mathbf{B}$.
- $-10^{9} + \mathbf{R} \leqslant \mathbf{X} \leqslant 10^{9} - \mathbf{R}$.
- $-10^{9} + \mathbf{R} \leqslant \mathbf{Y} \leqslant 10^{9} - \mathbf{R}$.

**Test set 1 (3 Pts, Visible Verdict)**

- $\mathbf{A} = \mathbf{B} = 10^{9} - 5$.

**Test set 2 (12 Pts, Visible Verdict)**

- $\mathbf{A} = \mathbf{B} = 10^{9} - 50$.

**Test set 3 (19 Pts, Hidden Verdict)**

- $\mathbf{A} = 10^{9} / 2$.
- $\mathbf{B} = 10^{9}$.


---

---
title: "[GCJ 2018 Qualification] Go, Gopher!"
layout: "post"
diff: 提高+/省选-
pid: P13134
tag: ['2018', '交互题', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2018 Qualification] Go, Gopher!
## 题目描述

The Code Jam team has just purchased an orchard that is a two-dimensional matrix of cells of unprepared soil, with $1000$ rows and $1000$ columns. We plan to use this orchard to grow a variety of trees — AVL, binary, red-black, splay, and so on — so we need to prepare some of the cells by digging holes:

- In order to have enough trees to use for each year's tree problems, we need there to be at least $A$ prepared cells.
- In order to care for our trees properly, the set of all prepared cells must form a single grid-aligned rectangle in which every cell within the rectangle is prepared.

Note that the above also implies that none of the cells outside of that rectangle can be prepared. We want the orchard to look tidy!

For example, when $\mathbf A=11$, although the eleven prepared cells in the left figure below form a $3 \times 4$ rectangle (that is, with $3$ rows and $4$ columns), the cell in the center of the rectangle is not prepared. As a result, we have not yet completed preparing our orchard, since not every cell of the $3 \times 4$ rectangle is prepared. However, after just preparing the center cell, the rectangle of size at least $11$ is fully filled, and the orchard is ready.

![](https://cdn.luogu.com.cn/upload/image_hosting/qetth289.png)

See below for another example. In this case, $\mathbf{A}=6$. Note that the middle figure prepares a cell outside the $3\times 2$ rectangle, so although the rightmost figure prepares a rectangle of size $6$, the entire set of the prepared cells does not form a rectangle (due to the extra cell on the left). As a result, the orchard is not ready.

![](https://cdn.luogu.com.cn/upload/image_hosting/twco3tpd.png)

Digging is hard work for humans, so we have borrowed the [Go gopher](https://blog.golang.org/gopher) from the [Google Go](https://golang.org/) team and trained it to help us out by preparing cells. We can deploy the gopher by giving it the coordinates of a target cell in the matrix that is not along any of the borders of the matrix. However, we have not yet perfected the gopher's training, so it will choose a cell uniformly at [(pseudo-)random](https://en.wikipedia.org/wiki/Pseudorandom_number_generator) from the $3\times 3$ block of nine cells centered on the target cell, and then prepare the cell it has chosen. (If it chooses a cell that was already prepared, it will uselessly prepare it again.)

We can only deploy the gopher up to $1000$ times before it gets too tired to keep digging, so we need your help in figuring out how to deploy it strategically. When you deploy the gopher, you will be told which cell the gopher actually prepared, and you can take this information into account before deploying it again, if needed. Note that you do not have to declare the dimensions or location of a rectangle in advance.

### Interactive Protocol

This problem is interactive, which means that the concepts of input and output are different than in standard Code Jam problems. You will interact with a separate process that both provides you with information and evaluates your responses. All information comes into your program via standard input; anything that you need to communicate should be sent via standard output. Remember that many programming languages buffer the output by default, so make sure your output actually goes out (for instance, by flushing the buffer) before blocking to wait for a response. See the FAQ for an explanation of what it means to flush the buffer. Anything your program sends through standard error is ignored, but it might consume some memory and be counted against your memory limit, so do not overflow it. To help you debug, a local testing tool script (in Python) is provided at the very end of the problem statement. In addition, sample solutions to a previous Code Jam interactive problem (in all of our supported languages) are provided in the analysis for Number Guessing.

Initially, your program should read a single line containing a single integer $\mathbf T$ indicating the number of test cases. Then, you need to process $\mathbf T$ test cases.

For each test case, your program will read a single line containing a single integer $\mathbf A$ indicating the minimum required prepared rectangular area. Then, your program will process up to $1000$ exchanges with our judge.

For each exchange, your program needs to use standard output to send a single line containing two integers $I$ and $J$: the row and column number you want to deploy the gopher to. The two integers must be between $2$ and $999$, and written in base-10 without leading zeroes. If your output format is wrong (e.g., out of bounds values), your program will fail, and the judge will send you a single line with $-1 -1$ which signals that your test has failed, and it will not send anything to your input stream after that. Otherwise, in response to your deployment, the judge will print a single line containing two integers $I'$ and $J'$ to your input stream, which your program must read through standard input.

If the last deployment caused the set of prepared cells to be a rectangle of area at least $\mathbf A$, you will get $I' = J' = 0$, signaling the end of the test case. Otherwise, $I'$ and $J'$ are the row and column numbers of the cell that was actually prepared by the gopher, with $\text{abs}(I'-I) \leq 1$ and $\text{abs}(J'-J) \leq 1$. Then, you can start another exchange.

If your program gets something wrong (e.g. wrong output format, or out-of-bounds values), as mentioned above, the judge will send $I' = J' = -1$, and stop sending output to your input stream afterwards. If your program continues to wait for the judge after reading in $I' = J' = -1$, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive the appropriate verdict (Wrong Answer, Runtime Error, etc.) instead of a Time Limit Exceeded error. As usual, if the total time or memory is exceeded, or your program gets a runtime error, you will receive the appropriate verdict.

If the test case is solved within $1000$ deployments, you will receive the $I' = J' = 0$ message from the judge, as mentioned above, and then continue to solve the next test case. After $1000$ exchanges, if the test case is not solved, the judge will send the $I' = J' = -1$ message, and stop sending output to your input stream after.

You should not send additional information to the judge after solving all test cases. In other words, if your program keeps printing to standard output after receiving $I' = J' = 0$ message from the judge for the last test case, you will receive a Wrong Answer judgment.

Please be advised that for a given test case, the cells that the gopher will pick from each $3 \times 3$ block are (pseudo-)random and independent of each other, but they are determined using the same seed each time for the same test case, so a solution that gives an incorrect result for a test case will do so consistently across all attempts for the same test case. We have also set different seeds for different test cases.

## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```

```
### 样例输出 #1
```

```
## 提示

**Sample Interaction**

```
  t = readline_int()         // reads 2 into t
  a = readline_int()         // reads 3 into a
  printline 10 10 to stdout  // sends out cell 10 10 to prepare
  flush stdout
  x, y = readline_two_int()  // reads 10 11, since cell 10 11 is prepared
  printline 10 10 to stdout  // sends out cell 10 10 again to prepare
  flush stdout
  x, y = readline_two_int()  // reads 10 10, since cell 10 10 is prepared
  printline 10 12 to stdout  // sends out cell 10 12 to prepare
  flush stdout
  x, y = readline_two_int()  // reads 10 11, since cell 10 11 is prepared again
  printline 10 10 to stdout  // sends out cell 10 10 to prepare
  flush stdout
  x, y = readline_two_int()  // reads 11 10, since cell 11 10 is prepared
  printline 11 10 to stdout  // sends out cell 11 10 to prepare
  flush stdout
  x, y = readline_two_int()  // reads 0 0; since cell 11 11 is prepared, a rectangle of size 4
```

The pseudocode above is the first half of a sample interaction for one test set. Suppose there are only two test cases in this test set. The pseudocode first reads the number of test cases into an integer $t$. Then the first test case begins. For the first test case, suppose $\mathbf A$ is $3$ (although, in the real test sets, $\mathbf A$ is always either $20$ or $200$). The pseudocode first reads the value of $\mathbf A$ into an integer $a$, and outputs $10 \ 10$ the location of the cell to prepare. By (pseudo-)random choice, the cell at location $10 \ 11$ is prepared, so the code reads $10 \ 11$ in response. Next, the code outputs cell $10 \ 10$ again for preparation, and the gopher prepares $10 \ 10$ this time. The code subsequently sends $10 \ 12$ with the goal of finishing preparing a rectangle of size $3$, but only gets cell $10 \ 11$ prepared again. $10 \ 10$ is then sent out, and this time $11 \ 10$ is prepared. Notice that although the prepared area is of size $3$, a rectangle has not been formed, so the preparation goes on. In the end, the pseudocode decides to try out cell $11 \ 10$, and $0 \ 0$ is sent back, which implies that cell $11 \ 11$ has been prepared, completing a rectangle (or square, rather) or size $4$. As a result, the first test case is successfully solved.

```
  a = readline_int()         // reads 3 into a
  printline 10 10 to stdout  // sends out cell 10 10 to prepare
  x, y = readline_two_int()  // does not flush stdout; hangs on the judge
```

Now the pseudocode is ready for the second test case. It again first reads an integer $a = 3$ and decides to send cell $10\ 10$ to prepare. However, this time, the code forgets to flush the stdout buffer! As a result, $10\ 10$ is buffered and not sent to the judge. Both the judge and the code wait on each other, leading to a deadlock and eventually a Time Limit Exceeded error.

```
  a = readline_int()         // reads 3 into a
  printline 1 1 to stdout    // sends out cell 1 1 to prepare
  x, y = readline_two_int()  // reads -1 -1, since 1 is outside the range [2, 999]
  printline 10 10 to stdout  // sends a cell location anyway
  x, y = readline_two_int()  // hangs since the judge stops sending info to stdin
```

The code above is another example. Suppose for the second test case, the code remembers to flush the output buffer, but sends out cell $1 \ 1$ to prepare. Remember that the row and column of the chosen cell must both be in the range $[2, 999]$, so $1 \ 1$ is illegal! As a result, the judge sends back $-1 \ -1$. However, after reading $-1 \ -1$ into $x$ and $y$, the code proceeds to send another cell location to the judge, and wait. Since there is nothing in the input stream (the judge has stopped sending info), the code hangs and will eventually receive a Time Limit Exceeded error.

Note that if the code in the example above exits immediately after reading $-1 \ -1$, it will receive a Wrong Answer instead:

```
  a = readline_int()         // reads 3 into a
  printline 1 1 to stdout    // sends out cell 1 1 to prepare
  x, y = readline_two_int()  // reads -1 -1, since 1 is outside the range [2, 999]
  exit                       // receives a Wrong Answer judgment
```

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our [interactive runner](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py) for that. For more information, read the instructions in comments in that file.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

$1 \leqslant T \leqslant 20$.

**Test set 1 (10 Pts, Visible)**

- $A=20$.
- Time limit (for the entire test set): 20 seconds.

**Test set 2 (20 Pts, Hidden)**

- $A=200$.
- Time limit (for the entire test set): 60 seconds.


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
title: "[GCJ 2014 #1A] Proper Shuffle"
layout: "post"
diff: 提高+/省选-
pid: P13249
tag: ['2014', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2014 #1A] Proper Shuffle
## 题目描述

A permutation of size $N$ is a sequence of $N$ numbers, each between $0$ and $N-1$, where each number appears exactly once. They may appear in any order.

There are many ($N$ factorial, to be precise, but it doesn't matter in this problem) permutations of size $N$. Sometimes we just want to pick one at random, and of course we want to pick one at random uniformly: each permutation of size $N$ should have the same probability of being chosen.

Here's the pseudocode for one of the possible algorithms to achieve that goal (we'll call it the good algorithm below):

```
for k in 0 .. N-1:
  a[k] = k
for k in 0 .. N-1:
  p = randint(k .. N-1)
  swap(a[k], a[p])
```

In the above code, `randint(a .. b)` returns a uniform random integer between $a$ and $b$, inclusive.

Here's the same algorithm in words. We start with the identity permutation: all numbers from $0$ to $N-1$ written in increasing order. Then, for each $k$ between $0$ and $N-1$, inclusive, we pick an independent uniform random integer $p_k$ between $k$ and $N-1$, inclusive, and swap the element at position $k$ (0-based) in our permutation with the element at position $p_k$.

Here's an example for $N=4$. We start with the identity permutation:

$$0 \ 1 \ 2 \ 3$$

Now $k=0$, and we pick a random $p_0$ between $0$ and $3$, inclusive. Let's say we picked $2$. We swap the 0th and 2nd elements, and our permutation becomes:

$$2 \ 1 \ 0 \ 3$$

Now $k=1$, and we pick a random $p_1$ between $1$ and $3$, inclusive. Let's say we picked $2$ again. We swap the 1st and 2nd elements, and our permutation becomes:

$$2 \ 0 \ 1 \ 3$$

Now $k=2$, and we pick a random $p_2$ between $2$ and $3$, inclusive. Let's say we picked $3$. We swap the 2nd and 3rd elements, and our permutation becomes:

$$2 \ 0 \ 3 \ 1$$

Now $k=3$, and we pick a random $p_3$ between $3$ and $3$, inclusive. The only choice is $3$. We swap the 3rd and 3rd elements, which means that the permutation doesn't change:

$$2 \ 0 \ 3 \ 1$$

The process ends now, and this is our random permutation.

There are many other algorithms that produce a random permutation uniformly. However, there are also many algorithms to generate a random permutation that look very similar to this algorithm, but are not uniform — some permutations are more likely to be produced by those algorithms than others.

Here's one bad algorithm of this type. Take the good algorithm above, but at each step, instead of picking $p_k$ randomly between $k$ and $N-1$, inclusive, let's pick it randomly between $0$ and $N-1$, inclusive. This is such a small change, but now some permutations are more likely to appear than others!

Here's the pseudocode for this algorithm (we'll call it the bad algorithm below):

```
for k in 0 .. N-1:
  a[k] = k
for k in 0 .. N-1:
  p = randint(0 .. N-1)
  swap(a[k], a[p])
```

In each test case, you will be given a permutation that was generated in the following way: first, we choose either the good or the bad algorithm described above, each with probability 50%. Then, we generate a permutation using the chosen algorithm. Can you guess which algorithm was chosen just by looking at the permutation?

This problem is a bit unusual for Code Jam. You will be given $T = 120$ permutations of $N = 1000$ numbers each, and should print an answer for each permutation – this part is as usual. However, you don't need to get all of the answers correct! Your solution will be considered correct if your answers for at least $G = 109$ cases are correct. However, you must follow the output format, even for cases in which your answer doesn't turn out to be correct. The only thing that can be wrong on any case, yet still allow you to be judged correct, is swapping GOOD for BAD or vice versa; but you should still print either GOOD or BAD for each case.

It is guaranteed that the permutations given to you were generated according to the method above, and that they were generated independently of each other.

This problem involves randomness, and thus it might happen that even the best possible solution doesn't make 109 correct guesses for a certain input, as both the good and the bad algorithms can generate any permutation. Because of that, this problem doesn't have a Large input, and has just the Small input which you can try again if you think you got unlucky. Note that there is the usual 4-minute penalty for incorrect submissions if you later solve that input, even if the only reason you got it wrong was chance.

In our experience with this problem, that did happen (getting wrong answer just because of chance); so if you are confident that your solution should be working, but it failed, it might be a reasonable strategy to try again with the same solution which failed.

Good luck!
## 输入格式

The first line of the input gives the number of test cases, $T$ (which will always be $120$). Each test case contains two lines: the first line contains the single integer $N$ (which will always be $1000$), and the next line contains $N$ space-separated integers - the permutation that was generated using one of the two algorithms.
## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from $1$) and $y$ is either "GOOD" or "BAD" (without the quotes). You should output "GOOD" if you guess that the permutation was generated by the first algorithm described in the problem statement, and "BAD" if you guess that the permutation was generated by the second algorithm described in the problem statement.
## 样例

### 样例输入 #1
```
2
3
0 1 2
3
2 0 1
```
### 样例输出 #1
```
Case #1: BAD
Case #2: GOOD
```
## 提示

**Sample Explanation**

The sample input doesn't follow the limitations from the problem statement - the real input will be much bigger.

**Limits(45 Pts)**

- $T = 120$
- $G = 109$
- $N = 1000$
- Each number in the permutation will be between $0$ and $N-1$ (inclusive), and each number from $0$ to $N-1$ will appear exactly once in the permutation.


---

---
title: "[GCJ 2012 Finals] Upstairs/Downstairs"
layout: "post"
diff: 提高+/省选-
pid: P13333
tag: ['贪心', '2012', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2012 Finals] Upstairs/Downstairs
## 题目描述

Konstantin and Ilia live in the same house. Konstantin lives upstairs, and enjoys activities that involve jumping, moving furniture around, and - in general - making noise. Ilia lives downstairs, and enjoys sleep.

In order to have a good evening, Konstantin wants to do at least $K$ activities. Last night, Ilia asked Konstantin to try not to wake him up; and because Konstantin is a very nice neighbor, he agreed. Unfortunately, he took Ilia's request a bit too literally, and he will choose his activities in such a way as to minimize the probability that Ilia is woken up after falling asleep.

Each possible activity for Konstantin has an associated probability $a_i / b_i$. If Konstantin performs this activity, then at the end of it, Ilia will be awake with probability $a_i / b_i$, and asleep otherwise, regardless of whether he was asleep at the start. Moreover, for each possible activity Konstantin can perform it at most $c_i$ times (more than that would be boring, and Konstantin won't have a good evening if he's bored).

Konstantin wants to choose a number of activities to do, in order, so that:

* The total number of activities done is at least $K$.
* The $i$th activity is performed no more than $c_i$ times.
* The probability $Q$ that Ilia is woken up one or more times during the course of the activities is as small as possible.

Ilia starts awake, so in order for him to be woken up, he must be asleep at the end of some activity, and then awake at the end of the next activity.

What is the smallest $Q$ Konstantin can achieve while having a good evening? Note that Konstantin cannot tell whether Ilia is awake or asleep, and so he cannot adapt his activities using that information.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a pair of integers, $N$, $K$, on a line by themselves. $N$ lines follow, each of which represents an activity that Konstantin can choose. Each of those lines is formatted as "$a_i/b_i$ $c_i$", indicating that there is an activity which would leave Ilia awake with probability $a_i/b_i$ and which Konstantin can perform at most $c_i$ times without being bored.

## 输出格式

For each test case, output one line containing "Case #$x$: $Q$", where $x$ is the case number (starting from 1) and $Q$ is the smallest probability of Ilia waking up during the course of the activities that Konstantin performs. Answers with absolute or relative error no larger than $10^{-6}$ will be accepted.
## 样例

### 样例输入 #1
```
3
4 1
1/2 3
1/5 2
2/5 1
2/2 2
3 2
1/2 2
1/3 2
3/4 2
3 3
99/100 1
1/2 2
1/50 3
```
### 样例输出 #1
```
Case #1: 0.000000000
Case #2: 0.083333333
Case #3: 0.015000000
```
## 提示

**Limits**

- $1 \leq T \leq 100.$
- $0 \leq a_i \leq b_i \leq 1000000$ for all $i$.
- $1 \leq b_i$ and $1 \leq c_i$ for all $i$.
- $1 \leq K \leq$ the sum of all $c_i$ in that test case.

**Test set 1 (13 Pts, Visible Verdict)**

- Time limit: ~~30~~ 6 seconds.
- $1 \leq N \leq 100.$
- The sum of all $c_i$ is no larger than $100$ in each test case.

**Test set 2 (17 Pts, Hidden Verdict)**

- Time limit: ~~60~~ 12 seconds.
- $1 \leq N \leq 10000.$
- The sum of all $c_i$ is no larger than $10^6$ in each test case.


---

---
title: "[GCJ 2009 #1A] Collecting Cards"
layout: "post"
diff: 提高+/省选-
pid: P13433
tag: ['动态规划 DP', '2009', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2009 #1A] Collecting Cards
## 题目描述

You've become addicted to the latest craze in collectible card games, PokeCraft: The Gathering. You've mastered the rules! You've crafted balanced, offensive, and defensive decks! You argue the merits of various cards on Internet forums! You compete in tournaments! And now, as they just announced their huge new set of cards coming in the year 2010, you've decided you'd like to collect every last one of them! Fortunately, the one remaining sane part of your brain is wondering: how much will this cost?

There are $C$ kinds of card in the coming set. The cards are going to be sold in "booster packs", each of which contains $N$ cards of different kinds. There are many possible combinations for a booster pack where no card is repeated. When you pay for one pack, you will get any of the possible combinations with equal probability. You buy packs one by one, until you own all the $C$ kinds. What is the expected (average) number of booster packs you will need to buy?

## 输入格式

The first line of input gives the number of cases, $T$. $T$ test cases follow, each consisting of a line containing $C$ and $N$.

## 输出格式

For each test case, output one line in the form

Case #$x$: $E$

where $x$ is the case number, starting from 1, and $E$ is the expected number of booster packs you will need to buy. Any answer with a relative or absolute error at most $10^{-5}$ will be accepted.
## 样例

### 样例输入 #1
```
2
2 1
3 2
```
### 样例输出 #1
```
Case #1: 3.0000000
Case #2: 2.5000000
```
## 提示

**Limits**

- $1 \leq T \leq 100$

**Small dataset(10 Pts)**

- $1 \leq N \leq C \leq 10$

**Large dataset(30 Pts)**

- $1 \leq N \leq C \leq 40$


---

---
title: "[GCJ 2008 APAC SemiFinal] Millionaire"
layout: "post"
diff: 提高+/省选-
pid: P13476
tag: ['动态规划 DP', '2008', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2008 APAC SemiFinal] Millionaire
## 题目描述

You have been invited to the popular TV show "Would you like to be a millionaire?". Of course you would!

The rules of the show are simple:

- Before the game starts, the host spins a wheel of fortune to determine $P$, the probability of winning each bet.
- You start out with some money: $X$ dollars.
- There are $M$ rounds of betting. In each round, you can bet any part of your current money, including none of it or all of it. The amount is not limited to whole dollars or whole cents. If you win the bet, your total amount of money increases by the amount you bet. Otherwise, your amount of money decreases by the amount you bet.
- After all the rounds of betting are done, you get to keep your winnings (this time the amount is rounded down to whole dollars) only if you have accumulated $1000000 or more. Otherwise you get nothing.

Given $M$, $P$ and $X$, determine your probability of winning at least $1000000 if you play optimally (i.e. you play so that you maximize your chances of becoming a millionaire).

## 输入格式

The first line of input gives the number of cases, $N$.

Each of the following $N$ lines has the format "$M$ $P$ $X$", where:

- $M$ is an integer, the number of rounds of betting.
- $P$ is a real number, the probability of winning each round.
- $X$ is an integer, the starting number of dollars.
## 输出格式

For each test case, output one line containing "Case #$X$: $Y$", where:

- $X$ is the test case number, beginning at $1$.
- $Y$ is the probability of becoming a millionaire, between $0$ and $1$.

Answers with a relative or absolute error of at most $10^{-6}$ will be considered correct.
## 样例

### 样例输入 #1
```
2
1 0.5 500000
3 0.75 600000
```
### 样例输出 #1
```
Case #1: 0.500000
Case #2: 0.843750
```
## 提示

**Sample Explanation**

In the first case, the only way to reach $1000000 is to bet everything in the single round.

In the second case, you can play so that you can still reach $1000000 even if you lose a bet. Here's one way to do it:

- You have \$600000 on the first round. Bet \$150000.
- If you lose the first round, you have \$450000 left. Bet \$100000.
- If you lose the first round and win the second round, you have \$550000 left. Bet \$450000.
- If you win the first round, you have \$750000 left. Bet \$250000.
- If you win the first round and lose the second round, you have \$500000 left. Bet \$500000.

**Limits**

- $1 \leq N \leq 100$
- $0 \leq P \leq 1.0$, there will be at most 6 digits after the decimal point.
- $1 \leq X \leq 1000000$

**Small dataset (13 Pts, Test set 1 - Visible)**

- $1 \leq M \leq 5$

**Large dataset (16 Pts, Test set 2 - Hidden)**

- $1 \leq M \leq 15$


---

---
title: "[GCJ 2008 AMER SemiFinal] Test Passing Probability"
layout: "post"
diff: 提高+/省选-
pid: P13480
tag: ['动态规划 DP', '2008', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2008 AMER SemiFinal] Test Passing Probability
## 题目描述

Dave is taking a multiple choice test on the Internet. Dave possibly gets many opportunities to submit his answers to the test, but he passes only if he gets all the questions correct. He must answer every question on the test to make a submission. The only information he receives after he submits is whether he has passed.

For each question, he estimates the probability that each of 4 responses is correct, independent of his responses to other questions. Given a fixed number of submissions he can make, Dave wants to choose his responses so that he maximizes the probability of passing the test.

What is the probability that Dave will pass the test if he chooses his responses optimally?

## 输入格式

The first line of input gives the number of cases, $C$. $C$ test cases follow.

Each test case starts with a line containing $M$ and $Q$. Dave is allowed to make $M$ submissions to solve the test. There are $Q$ questions on the test. $Q$ lines follow, each containing 4 probabilities of correctness. There will be at most 6 digits after the decimal point. The probabilities for each line are non-negative and sum to 1.

## 输出格式

For each test case, output one line containing "Case #$X$: $Y$" where $X$ is the number of the test case (starting from 1), and $Y$ is the probability of success.

Answers with a relative or absolute error of at most $10^{-6}$ will be considered correct.
## 样例

### 样例输入 #1
```
3
10 2
0.25 0.25 0.25 0.25
0.25 0.25 0.25 0.25
64 3
0.3 0.4 0.0 0.3
1.0 0.0 0.0 0.0
0.2 0.2 0.2 0.4
3 2
0.5 0.17 0.17 0.16
0.5 0.25 0.25 0.0
```
### 样例输出 #1
```
Case #1: 0.625
Case #2: 1.0
Case #3: 0.5
```
## 提示

**Limits**

- $1 \leqslant C \leqslant 100$

**Small dataset (Test set 1 - Visible)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leqslant Q \leqslant 6$
- $1 \leqslant M \leqslant 1000$

**Large dataset (Test set 2 - Hidden)**

- Time limit: ~~180~~ 18 seconds.
- $1 \leqslant Q \leqslant 30$
- $1 \leqslant M \leqslant 10000$



---

---
title: "可爱の#10数字划分"
layout: "post"
diff: 提高+/省选-
pid: P4257
tag: ['O2优化', '排序', '素数判断,质数,筛法', '概率论']
---
# 可爱の#10数字划分
## 题目背景

可可可可可可爱的付公主 qwq 有 $n$ 个数，$1\sim n$，每个数都有价值 $V_i$，你要将它们划分成若干个集合，每个数属于一个集合。
## 题目描述

我们这里规定:

1. 质数只能和质数分在同一个集合。  
2. 合数只能和合数分在同一个集合（$1$ 也算在合数内）。   
3. 我们假设目前所有质数集合的并集为 $U$（也就是之前所有质数集合以及 $S$ 的并集），每个质数集合 $S$ 的价值定义如下：  
$$V_S=\frac {(\sum_{i\in S}V_i)^p} {\prod_{i\in U}V_i}$$

4. 我们定义每个合数集合 $S$ 的价值如下:

令 $k=|S|$，我们用这 $k$ 个数分别作为 $k$ 条边的权值，连接 $k+1$ 个点，构成一棵树。对于一个排列 $P(1\sim k+1)$，价值为：

$$V_P=\sum_{i=1}^{n-1} f(P_i,P_{i+1})$$

其中 $f(u,v)$ 为路径 $(u,v)$ 上最大的边权。

集合 $S$ 的价值为：

$$V_S=E(\min\{V_P\})\times|S|$$

其中 $E(X)$ 代表 $X$ 的数学期望，期望是针对所有可能的有标号无根树，$\min$ 是针对所有可能的 $P$。这时集合内所有元素都不同，也就是所有边不同。

5. 一个划分方案的价值定义为所有集合的价值的乘积。
6. 两个划分方案相同当且仅当它们中所有集合对应相同，且质数集合的相对顺序相同。

现在给定 $n,p$ 和 $V_i$，请你求出所有合法的不同划分方案的价值之和。

结果对 $10^9+7$ 取模，除法请使用乘法逆元。
## 输入格式

第一行输入两个正整数 $n,p$。

第二行输入 $n$ 个正整数 $V_i$。
## 输出格式

共一行一个非负整数，代表答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
4 1
1 2 3 4

```
### 样例输出 #1
```
333333359
```
## 提示

### 样例解释

有以下 $6$ 种划分方案:

1. $(2,3)$ 和 $(1,4)$。$(2,3)$ 的价值为 ${\dfrac 5 6}$，$(1,4)$ 的价值为 $10$，总价值为 ${\dfrac {25} 3}$。
2. $(2),(3)$ 和 $(1,4)$。$(2)$ 的价值为 $1$，$(3)$ 的价值为 ${\dfrac 1 2}$，$(1,4)$ 的价值为 $10$，总价值为 $5$。
3. $(3),(2)$ 和 $(1,4)$。$(3)$ 的价值为 $1$，$(2)$ 的价值为 ${\dfrac 1 3}$，$(1,4)$ 的价值为 $10$，总价值为 ${\dfrac {10} 3}$。
4. $(2,3)$ 和 $(1),(4)$。$(2,3)$ 的价值为 ${\dfrac 5 6}$，$(1)$ 的价值为 $1$，$(4)$ 的价值为 $4$，总价值为 ${\dfrac {10} 3}$。
5. $(2),(3)$ 和 $(1),(4)$。$(2)$ 的价值为 $1$，$(3)$ 的价值为 ${\dfrac 1 2}$，$(1)$ 的价值为 $1$，$(4)$ 的价值为 $4$，总价值为 $2$。
6. $(3),(2)$ 和 $(1),(4)$。$(3)$ 的价值为 $1$，$(2)$ 的价值为 ${\dfrac 1 3}$，$(1)$ 的价值为 $1$，$(4)$ 的价值为 $4$，总价值为 ${\dfrac 4 3}$。

因此所有划分方案的价值和为${\dfrac {70} 3}$。对 $10^9+7$ 取模后结果为 $333333359$。

### 数据范围

对于 $100\%$ 的数据，满足 $1\le n\le 70$，$1\le V_i\le 10^{12}$。

下表中给出了每个测试点具体的数据范围，都表示小于等于。为了防止卡 OJ，所以本题数据组数进行压缩，分值改变，具体参照表格。

| 数据编号 |  n   |  p   |  Vi   | 测试点分值 | 时限 |
| :------: | :--: | :--: | :---: | :--------: | :--: |
|    1     |  10  |  1   |  100  |     10     |  1s  |
|    2     |  20  |  1   | 1000  |     10     |  1s  |
|    3     |  30  |  1   | 10000 |     10     |  1s  |
|    4     |  40  | 1e9  | 1e12  |     10     |  1s  |
|    5     |  50  |  1   | 1e12  |     5      |  1s  |
|    6     |  50  | 1e9  | 1e12  |     5      |  1s  |
|    7     |  60  |  1   | 1e12  |     5      |  2s  |
|    8     |  60  | 1e9  | 1e12  |     5      |  2s  |
|    9     |  70  | 1e9  | 1e12  |     20     |  10s  |
|    10    |  70  | 1e9  | 1e12  |     20     |  5s  |

提示：大家不要太过相信自己的常数，尽量做好常数优化。


---

---
title: "[1007] 梦美与线段树"
layout: "post"
diff: 提高+/省选-
pid: P4927
tag: ['线段树', '概率论', '期望', '洛谷月赛']
---
# [1007] 梦美与线段树
## 题目背景

欢迎大家光临星象馆

这里有着无论何时永远不会消失

美丽的无穷光辉

满天的星星等候着大家的到来
## 题目描述

梦美为了研究星象馆的星星，用巨型投影机——耶拿将星星排成了一个序列，接着梦美将这个星星序列建成了一棵线段树。

这是一棵维护区间和的线段树，每个节点的权值是该节点所对应的区间中，所有星星的权值和。有的时候梦美会从这棵线段树的根节点开始在星空游历。当她要进入子节点的时候，假设左右子树对应区间的权值和分别为 $sum_l$  和 $sum_r$，当前节点的权值为 $sum_{cur}$ ，梦美会以 $\frac{sum_l}{sum_{cur}}$ 的概率进入左子树，否则进入右子树。

游历的时候，梦美会把她经过的节点的权值累加起来，现在她希望您帮她设计一个算法求出这个权值期望下是多少。

当然，如果星星都是不变的梦美会觉得很没有意思，因此她会发出一些指令，每个指令是，对下标在 $[l,r]$ 的星星，权值加上 $v$ 。不过由于馆里的工作人员全都离开了，因此没有人教梦美在线段树上维护懒标记，所以梦美的每次指令都会实时更新所有的线段树节点。

为了解决线段树写法不一的问题，此处给出梦美维护这个问题时的部分代码：
```cpp
const int N = 100010, MOD = 998244353;
int a[N], sum[N << 2];
#define lson (o << 1)
#define rson (o << 1 | 1)
void pushup(int o) {
	sum[o] = (sum[lson] + sum[rson]) % MOD;
}
void build(int o, int l, int r) {
	if (l == r) {
		sum[o] = a[l];
	} else {
		int mid = (l + r) >> 1;
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(o);
	}
}
void change(int o, int l, int r, int q, int v) {
	if (l == r) {
		sum[o] = (sum[o] + v) % MOD;
		return;
	}
	int mid = (l + r) >> 1;
	if (q <= mid) change(lson, l, mid, q, v);
	else change(rson, mid + 1, r, q, v);
	pushup(o);
}
void add_to_interval(int l, int r, int v) {
	for (int i = l; i <= r; i ++) {
		change(1, 1, n, i, v);
	}
}
```
其中 `a` 数组表示每个星星的权值，`sum` 数组表示每个线段树节点的权值，`add_to_interval` 函数表示一次操作。
## 输入格式

第一行两个整数 $n,m$，表示序列长度和操作次数。

第二行 $n$ 个整数，表示这个序列。

接下来 $m$ 行，每行为

$1 \ l \ r \ v$，表示区间 $[l,r]$ 的节点加上了 $v$；

$2$ ，表示一次询问。
## 输出格式

对于每一个 $2$ 操作，输出一个答案。令答案化成最简分数为 $\frac{p}{q}$（保证 $q$ 不是 $998244353$ 的倍数），则输出 $p\cdot q^{-1}\mod 998244353$。
## 样例

### 样例输入 #1
```
4 3
1 2 3 4
2
1 1 3 1
2
```
### 样例输出 #1
```
399297760
844668322
```
## 提示

对于 $30\%$ 的数据，保证 $1 \leq n,m\leq 100$；

对于另外 $20\%$ 的数据，满足所有操作 1 中 $l=r$；

对于 $100\%$ 的数据，保证 $1\leq n,m \leq 10^5,1 \leq a_i,v \leq 10^9,1\le l\le r\le n$。

样例答案实际是 $\frac{94}{5}$ 和 $\frac{303}{13}$。


---

---
title: "[Cnoi2019] 数学课"
layout: "post"
diff: 提高+/省选-
pid: P5389
tag: ['数学', '2019', '概率论']
---
# [Cnoi2019] 数学课
## 题目描述

聪明的 Cirno 开始学习计算，于是她很开心的算出了从 $1$ 一直加到 $n$。

得到了一个 $n$ 项的数列 : $ \{ a_n$ = $1 + 2 + 3 + 4 + ... + n \} $

为了验证自己算是否算错，她需要以某种规律从数列里取出两个元素 $v_1, v_2$（元素可以相同），并等概率的选出整数 $a \in [ 1,v_1 ]$，$b \in [ 1,v_2 ]$ 判断哪个比较大.

所以她需要你来计算 $a>b$ 的概率。

某种规律：
选到数列第 $i$ 个元素的概率是：

$$\frac{a_i}{\sum\limits_{n=1}^n a_n}=\frac{3i\times(i+1)}{n(n+1)(n+2)}$$
## 输入格式

输入一个正整数 $n$。
## 输出格式

输出在模 $998244353$ 意义下的概率。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
686292993
```
## 提示

对于前 $5\%$ 的数据 $n = 3$；

对于前 $15\%$ 的数据 $n \le 100$；

对于前 $30\%$ 的数据  $n \le 5000$；

对于前 $55\%$ 的数据 $n \le 10^7$；

对于前 $95\%$ 的数据 $1\le n \le 10^{18}$；

对于最后 $5\%$ 的数据 $n = 0$ 表示 **正无穷**；

对于 100% 的数据 $n$ 不为 $998244353$ 的倍数。


---

---
title: "[JSOI2015] 非诚勿扰"
layout: "post"
diff: 提高+/省选-
pid: P6089
tag: ['2015', '各省省选', '江苏', '概率论']
---
# [JSOI2015] 非诚勿扰
## 题目背景

JYY 赶上了互联网创业的大潮，为非诚勿扰开发了最新的手机 App 实现单身大龄青年之间的“速配”。然而随着用户数量的增长，JYY 发现现有速配的算法似乎很难满足大家的要求，因此 JYY 决定请你来调查一下其中的原因。
## 题目描述

应用的后台一共有 $N$ 个女性和 $N$ 个男性，他们每个人都希望能够找到自己的合适伴侣。为了方便，每个男性都被编上了 $1$ 到 $N$ 之间的一个号码，并且任意两个人的号码不一样。每个女性也被如此编号。

JYY 应用的最大特点是赋予女性较高的选择权，让每个女性指定自己的“如意郎君列表”。每个女性的如意郎君列表都是所有男性的一个子集，并且可能为空。如果列表非空，她们会在其中选择一个男性作为自己最终接受的对象。

JYY 用如下算法来为每个女性速配最终接受的男性：将“如意郎君列表”中的男性按照编号从小到大的顺序呈现给她。对于每次呈现，她将独立地以 $P$ 的概率接受这个男性（换言之，会以 $1-P$ 的概率拒绝这个男性）。如果她选择了拒绝，App 就会呈现列表中下一个男性，以此类推。如果列表中所有的男性都已经呈现，那么中介所会重新按照列表的顺序来呈现这些男性，直到她接受了某个男性为止。显然，在这种规则下，每个女性只能选择接受一个男性，而一个男性可能被多个女性所接受。当然，也可能有部分男性不被任何一个女性接受。

这样，每个女性就有了自己接受的男性（“如意郎君列表”为空的除外）。现在考虑任意两个不同的、如意郎君列表非空的女性 $a$ 和 $b$，如果 $a$ 的编号比 $b$ 的编号小，而 $a$ 选择的男性的编号比 $b$ 选择的编号大，那么女性 $a$ 和女性 $b$ 就叫做一对不稳定因素。

由于每个女性选择的男性是有一定的随机性的，所以不稳定因素的数目也是有一定随机性的。JYY 希望你能够求得不稳定因素的期望个数（即平均数目），从而进一步研究为什么速配算法不能满足大家的需求。
## 输入格式

输入第一行包含 $2$ 个自然数 $N,M$，表示有 $N$ 个女性和 $N$ 个男性，以及所有女性的“如意郎君列表”长度之和是 $M$。

接下来一行一个实数 $P$，为女性接受男性的概率。

接下来 $M$ 行，每行包含两个整数 $a,b$，表示男性 $b$ 在女性 $a$ 的“如意郎君列表”中。
## 输出格式

输出 $1$ 行，包含一个实数，四舍五入后保留到小数点后 $2$ 位，表示不稳定因素的期望数目。
## 样例

### 样例输入 #1
```
5 5
0.5
5 1
3 2
2 2
2 1
3 1
```
### 样例输出 #1
```
0.89
```
## 提示

对于 $100\%$ 的数据，$1\leq N,M\leq 5\times 10^5$，$0.4\leq P<0.6$。

输入保证每个女性的“如意郎君列表”中的男性出现且仅出现一次。



---

---
title: "异位坍缩"
layout: "post"
diff: 提高+/省选-
pid: P7495
tag: ['递推', '2021', '矩阵运算', '概率论', '矩阵乘法']
---
# 异位坍缩
## 题目背景

>自然的法则隐藏在黑暗之中。

月光之下，菲欧娜和一群与她有着同样信仰的信徒们聚集在一起，等待着他们所信仰的神明降临。

「神明大人，我们愿意永远追随您。」
## 题目描述

神明想要测试他的信徒们是否忠诚，他决定用运气来进行测试。

神明事先准备了 $n$ 个问题，每个问题都有两种选择：**「相对激进的」** 和 **「相对保守的」**。神明已经定好了自己的选择。

为了考验他的信徒们，神明会在所有可行的问题选择方式中**等概率选出一种**（可行的选择方式指选出**连续的** $k$ 个问题，满足 $l\leq k\leq r$，其中 $l,r$ 给定），然后信徒们会依次对这 $k$ 个问题中的每个问题回答「相对激进的」或「相对保守的」。神明会根据自己的选择以及某个信徒的回答来判定这名信徒是否忠诚。

神明的判定方式是这样的：

+ 这是第一个问题：无论回答如何，神明都愿意相信这名信徒是忠诚的。
+ 这不是第一个问题：如果这名信徒的上一个回答与神明的选择相同，那么神明会需要他去对更先进的选择进行探索，因此这名信徒在这个问题的回答**不能比神明的选择更保守**；否则，神明会要求这名信徒服从于自己，在这个问题的回答**不能比神明的选择更激进**。

如果这名信徒的回答满足上述要求，那么这名信徒就是忠诚的。

现在，神明想要知道，如果信徒对每个问题都会**等概率回答「相对激进的」或「相对保守的」**，那么一名信徒有多大的概率会是忠诚的。他通过菲欧娜向你提出了这个问题，并要求你将结果对 $998244353$ 取模。如果你无法及时回答出，那么你就会失去神明的信任。

------------

#### 简要题意：

给定一个长度为 $n$ 的 01 串 $a$ 以及 $l,r(l\leq r)$。

对于两个长度均为 $k$ 的 01 串 $p,q$，我们认为 $q$ 对于 $p$ 是「忠诚的」，当且仅当 $p$ 和 $q$ 满足如下要求：

+ 对于任意 $1<i\leq k$，如果 $q_{i-1}=p_{i-1}$，那么 $q_i\geq p_i$，否则 $q_i\leq p_i$。

你需要求出如果**先等概率随机选出一个长度 $k$ 满足 $l\leq k\leq r$ 的 $a$ 的子串**，然后**再等概率随机出一个长度为 $k$ 的 01 串 $b$**，有多大的概率使得 $b$ 对于这个子串是「忠诚的」，结果对 $998244353$ 取模。
## 输入格式

第一行三个整数 $n,l,r$，意义如上。

第二行有一个长度为 $n$ 的字符串，表示 $a$。保证字符串只含字符 `0` 和 `1`。
## 输出格式

一行一个整数，表示结果。
## 样例

### 样例输入 #1
```
5 2 3
01101

```
### 样例输出 #1
```
338690049
```
### 样例输入 #2
```
17 4 13
10101110100101101

```
### 样例输出 #2
```
512357021
```
## 提示

#### 样例一解释：

我们用 $\left[l,r\right]$ 表示所选择的子串所在区间。

+ 选择 $\left[1,2\right]$，子串为 `01`，长度为 $2$，有 $3$ 个 01 串对这个子串是「忠诚的」，概率为 $\dfrac{3}{4}$。
+ 选择 $\left[1,3\right]$，子串为 `011`，长度为 $3$，有 $4$ 个 01 串对这个子串是「忠诚的」，概率为 $\dfrac{1}{2}$。
+ 选择 $\left[2,3\right]$，概率为 $\dfrac{3}{4}$。

+ 选择 $\left[2,4\right]$，概率为 $\dfrac{5}{8}$。
+ 选择 $\left[3,4\right]$，概率为 $\dfrac{3}{4}$。
+ 选择 $\left[3,5\right]$，概率为 $\dfrac{1}{2}$。
+ 选择 $\left[4,5\right]$，概率为 $\dfrac{3}{4}$。

结果为 $\dfrac{\dfrac{3}{4}+\dfrac{1}{2}+\dfrac{3}{4}+\dfrac{5}{8}+\dfrac{3}{4}+\dfrac{1}{2}+\dfrac{3}{4}}{7}=\dfrac{37}{56}$，取模意义下为 $338690049$。

------------

**本题采用捆绑测试**

+ Subtask 1 ( $1\%$ )：$n=1$。
+ Subtask 2 ( $13\%$ )：$n\leq100$。
+ Subtask 3 ( $3\%$ )：保证 $\forall1\leq i\leq n,a_i=0$。
+ Subtask 4 ( $3\%$ )：保证 $\forall1\leq i\leq n,a_i=1$。
+ Subtask 5 ( $20\%$ )：$n\leq10^3$。
+ Subtask 6 ( $15\%$ )：$l=r$。
+ Subtask 7 ( $20\%$ )：$n\leq 5\times 10^5$。
+ Subtask 8 ( $25\%$ )：无特殊限制。

对于所有数据，$1\leq n\leq5\times 10^6,1\leq l\leq r\leq n$。


---

---
title: "[_-0 A] 考试"
layout: "post"
diff: 提高+/省选-
pid: P9475
tag: ['O2优化', '组合数学', '二项式定理', '概率论', '期望']
---
# [_-0 A] 考试
## 题目背景

小 $\mathfrak{g}$ 参加一场考试时，不小心把答题卡填反了。
## 题目描述

答题卡有 $n (1 \le n \le 10^9)$ 行，$m (1 \le m \le 10^9)$ 列，共 $nm$ 道题，**从左到右，从上到下，横向排列**。

每道题有 $c (4 \le c \le 10^9)$ 个选项。其中，前 $k(0 \le k \le nm)$ 道题为单选题，**有且仅有一个**正确选项；后 $nm - k$ 道题为多选题，正确选项个数**严格大于** $1$ 且**严格小于** $c$。

小 $\mathfrak{g}$ 正确地回答了所有题，但是她不小心把答题卡的方向看反了，从而她的答案排列方式为**从上到下，从左到右，纵向排列**。

题目的评分方式为：选项完全正确得 $1$ 分，多选或错选得 $0$ 分，漏选按比例给分。

形式化地说，若 $A$ 为某道题正确答案选项的集合，$B$ 为答题卡上选项的集合（均为 $\{1,2,3,\cdots,c\}$ 的子集），则该题得分为：

$$\begin{cases}\frac{\lvert B \rvert}{\lvert A \rvert}&\text{if\quad}
B\sube A\\0&\text{otherwise}\end{cases}$$

小 $\mathfrak{g}$ 忘记考试的正确答案是什么了，于是她去问小 $\mathfrak{f}$，如果考试的正确答案在合法范围内等概率随机，那么自己期望得分是多少。由于结果可能很大，她只需要知道结果对 $10^9+7$ 取模的值。

**题目保证 $c$ 和 $2^c-c-2$ 都不是 $10^9+7$ 的倍数。**


但是小 $\mathfrak{f}$ 也不会，所以他来求助万能的你。
## 输入格式

一行，四个用空格分隔的整数 $n,m,k,c$，分别表示答题卡的行数，列数，单选题的数量和每道题的选项个数。
## 输出格式

一行，一个整数，表示期望得分，对 $10^9+7$ 取模。
## 样例

### 样例输入 #1
```
2 3 3 4
```
### 样例输出 #1
```
760000008
```
### 样例输入 #2
```
314159265 358979323 84626433832795028 841971693
```
### 样例输出 #2
```
465094894
```
## 提示

**样例 $1$ 解释：**

得分的期望为 $\frac{67}{25}$，对 $10^9+7$ 取模为 $760000008$。

一种可能的考试的正确答案依次为：

$\texttt{C,D,B,AD,ABD,BC}$

那么答题卡上应该填写：

| $\texttt{C}$ | $\texttt{D}$ | $\texttt{B}$ |
| :----------: | :----------: | :----------: |
| $\texttt{AD}$ | $\texttt{ABD}$ | $\texttt{BC}$ |

实际填写：

| $\texttt{C}$ | $\texttt{B}$ | $\texttt{ABD}$ |
| :----------: | :----------: | :----------: |
| $\texttt{D}$ | $\texttt{AD}$ | $\texttt{BC}$ |

答案为 $\texttt{C}$，填写 $\texttt{C}$，得 $1$ 分。

答案为 $\texttt{D}$，填写 $\texttt{B}$，得 $0$ 分。

答案为 $\texttt{B}$，填写 $\texttt{ABD}$，得 $0$ 分。

答案为 $\texttt{AD}$，填写 $\texttt{D}$，得 $\frac{1}{2}$ 分。

答案为 $\texttt{ABD}$，填写 $\texttt{AD}$，得 $\frac{2}{3}$ 分。

答案为 $\texttt{BC}$，填写 $\texttt{BC}$，得 $1$ 分。

综上，这种情况下，考试得分为：

$1+0+0+\frac{1}{2}+\frac{2}{3}+1=
\frac{19}{6}$ 分。

**本题采用捆绑测试且使用子任务依赖。**

| 编号 | 分值 | $n,m\le$ | $c\le$ | 性质 | 依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $0$ | N/A| N/A | 样例 | 无 |
| $1$ | $5$ | $10^9$ | $10^9$ | A | 无 |
| $2$ | $5$ | $2$ | $4$ | 无 | 无 |
| $3$ | $20$ | $10^3$ | $10$ | 无 | $2$ |
| $4$ | $15$ | $10^9$ | $10$ | 无 | $2,3$ |
| $5$ | $15$ | $10^3$ | $10^3$ | 无 | $2,3$ |
| $6$ | $15$ | $10^3$ | $10^5$ | 无 | $2,3,5$ |
| $7$ | $10$ | $10^3$ | $10^9$ | B | 无 |
| $8$ | $10$ | $10^3$ | $10^9$ | 无 | $2,3,5,6,7$ |
| $9$ | $5$ | $10^9$ | $10^9$ | 无 | $0,1,2,3,4,5,6,7,8$ |

特殊性质 A：$n=1$ 或 $m=1$

特殊性质 B：$k=nm-2$


---

