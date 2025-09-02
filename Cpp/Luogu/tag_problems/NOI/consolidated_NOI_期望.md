---
title: "超越（Transcendent）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10325
tag: ['数学', '多项式', '洛谷原创', 'O2优化', '分治', '概率论', '期望', '快速傅里叶变换 FFT', '洛谷比赛']
---
# 超越（Transcendent）
## 题目背景

越过领域和现实的终极存在 —— 超越。

****
「超越之光」美娜，是亚特兰蒂斯最强的魔法师，亦是无人能及的贤者。即便如此，她也一刻都没有停下对数学的探索。

「最高次系数为 $1$ 的整系数多项式方程的解不一定是整数，」美娜自言自语道，「但是其所有根组成的对称多项式的值必然是整数。」

「这很容易证明，却也很有趣呢。」想到这里，美娜突然有了开发新魔法的思路。
## 题目描述

美娜的魔法需要 $m+1$ 个阶段来构建。第 $i \ (1 \leq i \leq m)$ 个阶段每次尝试的成功概率为 $a_i/b_i$，如果失败**只需要重试当前阶段**即可，如果成功就能进入下一个阶段。

最后的第 $m+1$ 个阶段需要选一个魔力基数 $c$。不过这个魔法现在并不稳定，设 $r$ 是一个不大于 $2n$ 的范围内**均匀随机**生成的正整数，则
$$c=\cos \frac{r\pi}{n}$$
最后，若美娜在前 $m$ 个阶段中总共尝试了 $k$ 次（每次无论失败或成功，都算多一次尝试），她的魔法会产生 $c^k$ 的能量。

美娜想知道这个魔法所产生能量的期望值是多少，当然她很容易就算出了答案，你能帮她验算一下吗？

你只用输出答案对 $998244353$ 取模的结果即可。显然，答案一定是有理数，所以你可以简单地计算其对 $998244353$ 取模的值。
## 输入格式

第一行两个正整数 $n,m$。  
接下来 $m$ 行，每行两个正整数 $a_i,b_i$，意义如题目描述。
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
2 3
1 2
2 3
2 3
```
### 样例输出 #1
```
103983787
```
### 样例输入 #2
```
4 5
1 3
1 2
1 4
1 5
1 6
```
### 样例输出 #2
```
525030616
```
### 样例输入 #3
```
7 17
1 5
1 5
1 5
1 5
1 3
1 3
1 3
1 2
1 2
1 6
1 6
1 6
1 6
1 6
1 6
1 6
1 6
```
### 样例输出 #3
```
308796722
```
## 提示

【样例 $1$ 解释】

此时 $m=3$，前 $m$ 个阶段中，第一阶段的成功概率为 $1/2$，之后两个阶段的成功概率都为 $2/3$。由此可以算出，恰好尝试 $k \ (k \geq m)$ 次完成前 $m$ 个阶段的概率为（我有一个巧妙的方法给出证明，可惜这里空间太小，写不下）：

$$p_k=2^{4-k}-4(k+1)3^{1-k}$$
例如 $p_3=2/9$，这是每个阶段都一次成功的概率 $1/2 \times 2/3 \times 2/3$。  
又如 $p_4=7/27$，这要求在某一阶段尝试恰好两次，其它阶段都一次成功，即：
$$p_4=\left( \frac 12\right)^2   \frac 23 \cdot \frac 23+\frac 12\left( \frac 29\right)\frac 23+\frac 12\cdot \frac 23\left( \frac 29\right)$$
样例中 $n=2$，可知 $c=1$ 的概率为 $1/4$，$c=-1$ 的概率为 $1/4$，还有 $1/2$ 的概率 $c=0$。故答案为

$$\frac 14\sum_{k\geq 3}p_k (1+(-1)^k)=\frac{11}{48}$$
对 $998244353$ 取模后为 $103983787$。

【样例 $2$ 解释】

取模前的答案为 $\dfrac{24284321}{191028915}$。

【数据范围】 

**本题使用捆绑测试。**


Subtask 1（7 pts）：$n\le 6$，$m=1$；   
Subtask 2（9 pts）：$n\le 6$，$m\le 10$；  
Subtask 3（13 pts）：$n\le 500$，$m\le 500$；   
Subtask 4（13 pts）：$n=2^{19}$；  
Subtask 5（15 pts）：$n \le 10^5$，$m\le 500$；  
Subtask 6（15 pts）：不同的 $a_i/b_i$ 最多有两组；   
Subtask 7（28 pts）：无特殊限制。


对于全部数据，$1\le n \le 10^8$，$1\le m \le 60000$，$1\le a_i<b_i\leq 10^8$。且保证

$$U_n\left( \frac{b_i}{b_i-a_i}\right)\not \equiv 0 \pmod{998244353}$$
其中 $U_n(x)$ 表示 $n$ 次的[第二类 Chebyshev 多项式](https://mathworld.wolfram.com/ChebyshevPolynomialoftheSecondKind.html)。

【提示】   
你在找什么呢？或许可以再看看题目背景，会有帮助的。


---

---
title: "Normal"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10632
tag: ['图论', '点分治', '多项式', 'Special Judge', 'O2优化', '期望', '快速数论变换 NTT']
---
# Normal
## 题目描述

某天 WJMZBMR 学习了一个神奇的算法：树的点分治！

这个算法的核心是这样的：

```cpp
time = 0
Solve(Tree a) {
  time += a.size;
  if (a.size == 1) return;
  else {
    select x in a;
    delete a[x];
  }
}
```

```
消耗时间 = 0
Solve(树 a)
  消耗时间 += a 的大小
  如果 a 中 只有 1 个点
    退出
  否则
    在 a 中选一个点x
    在 a 中删除点x
```

那么 $a$ 变成了几个小一点的树，对每个小树递归调用 `Solve`。

我们注意到的这个算法的时间复杂度跟选择的点 $x$ 是密切相关的，如果 $x$ 是树的重心，那么时间复杂度就是 $O(n \log n)$。

WJMZBMR 决定随机在 $a$ 中选择一个点作为 $x$，Sevenkplus 告诉他这样做的最坏复杂度是 $O(n^2)$，但是 WJMZBMR 就是不信，于是 Sevenkplus 花了几分钟写了一个程序证明了这一点，你也试试看吧。

现在给你一颗树，你能告诉 WJMZBMR 他的算法需要的期望消耗时间吗（以给出的 `Solve` 函数中的为标准）？
## 输入格式

第一行一个整数 $n$，表示树的大小；接下来 $n-1$ 行每行两个整数 $a,b$，表示 $a$ 和 $b$ 之间有一条边。

树的结点从 $0$ 开始编号。
## 输出格式

一行一个浮点数表示答案，并四舍五入到小数点后 $4$ 位。
## 样例

### 样例输入 #1
```
3
0 1
1 2
```
### 样例输出 #1
```
5.6667
```
## 提示

对于所有的数据，保证 $1\leq n\leq 30000$。


---

---
title: "[集训队互测 2015] 胡策的小树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11736
tag: ['2015', '集训队互测', 'Special Judge', '期望', '高斯消元']
---
# [集训队互测 2015] 胡策的小树
## 题目描述

在 OI 界，有一位无人不知无人不晓，OI 水平前无古人后无来者的胡策，江湖人称一眼秒题胡大爷。

胡策最近从一名自称是小 O 的神秘男子那里收到了一棵神奇的小树苗。

这是一棵 $n$ 个节点的有根树，节点标号为 $1, \dots, n$，其中 $1$ 号点为根。

这棵有根树上每个点都有一个权值，点 $i$ 的权值为 $a_i$。$a_1, \dots, a_n$ 构成了一个 $0\sim n-1$ 的排列，且 $a_1=0$。

胡策大爷十分喜欢猴子，他打算在这棵树上养 $n$ 只猴子。初始时，每个节点上将放着恰好一只猴子。猴子们十分好动，每过一秒，每只在 $i$ 节点的猴子会设法往 $i$ 的父亲节点上跳，有 $p(i)$ 的概率成功跳到父亲节点；否则跳跃失败，将等概率地随机落到子树 $i$ 里某个节点上（包括点 $i$）。

因为根节点没有父亲，所以 $p(1)=0$。对于 $2\leq i\leq n$，有 $p(i)=\frac{a_i}{n}$；

在第 $i$ 秒，胡策会观察并记录这 $n$ 只猴子中成功跳上父亲结点的猴子所占的比例 $g_i$。胡策认为 $g_0, \dots, g_T$ 的平均值就是这群猴子们生活的幸福指数，为保证准确，其中 $T$ 为很大很大的值，为 $(n+1)^{99999^{99999^{99999}}}$

为了让猴子们的幸福指数的期望更大，胡策又从那名自称是小 O 的神秘男子那里买来了一袋叫“金坷垃”的肥料。如果给这棵有根树掺 $x$ 克的金坷垃，那么这棵树每个点 $i$ 的权值将变化成 $(a_i+x)\bmod n$。因为胡策是土豪有钱任性，$x$ 可以取任意非负整数。

请你告诉胡策，他该掺多少克的金坷垃，才能使猴子们幸福指数的期望最大呢？
## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个用空格隔开的非负整数，第 $i$ 个为节点 $i$ 的父亲节点编号 $f_i$。（$f_1=0$，对于 $i>1$ 有 $1\leq f_i< i$）

第三行 $n$ 个用空格隔开的非负整数，为一个 $0\sim n-1$ 的排列，第 $i$ 个表示 $a_i$。
## 输出格式

一行一个实数，表示掺适量的金坷垃时的最大幸福指数期望。

你的答案被认为是正确的当且仅当你的答案与标准答案的绝对误差或相对误差不超过 $10^{-9}$。
## 样例

### 样例输入 #1
```
3
0 1 1
0 1 2
```
### 样例输出 #1
```
0.266666667
```
## 提示

- 对于 $10\%$ 的数据：$n = 2$。
- 对于 $20\%$ 的数据：$n\leq 5$。
- 对于 $30\%$ 的数据：$n\leq 100$。
- 对于 $50\%$ 的数据：$n\leq 2000$。
- 对于 $70\%$ 的数据：$n\leq 100000$。
- 对于 $100\%$ 的数据：$2\leq n\leq 500000$。

数据保证有一定梯度。

数据都是随机生成的。即：节点 $i$ 的父亲是从 $1\sim i-1$ 中随机选取的，$a_1 \dots a_n$ 是一个 $0 \sim n-1$ 的随机排列。


---

---
title: "[GCJ 2014 Finals] ARAM"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13269
tag: ['2014', 'Special Judge', '概率论', '期望', '随机游走 Markov Chain', 'Google Code Jam']
---
# [GCJ 2014 Finals] ARAM
## 题目背景

League of Legends is a trademark of Riot Games. Riot Games does not endorse and has no involvement with Google Code Jam.
## 题目描述

In the game League of Legends ${ }^{\mathrm{TM}}$, you can play a type of game called "ARAM", which is short for "All Random, All Mid". This problem uses a similar idea, but doesn't require you to have played League of Legends to understand it.

Every time you start playing an ARAM game, you're assigned one of $\mathrm{N}$ "champions", uniformly at random. You're more likely to win with some champions than with others, so if you get unlucky then you might wish you'd been given a different champion. Luckily for you, the game includes a "Reroll" function.

Rerolling randomly reassigns you a champion in a way that will be described below; but you can't reroll whenever you want to. The ability to reroll works like a kind of money. Before you play your first ARAM game, you begin with $\mathrm{R}$ RD ("reroll dollars"). You can only reroll if you have at least 1 RD, and you must spend 1 RD to reroll. After every game, you gain $1 / \mathrm{G}$ RD (where $\mathrm{G}$ is an integer), but you can never have more than $\mathrm{R}$ RD: if you have $\mathrm{R}$ RD and then play a game, you'll still have $\mathrm{R}$ RD after that game.

If you have at least $1 \mathrm{RD}$, and you choose to reroll, you will spend $1 \mathrm{RD}$ and be re-assigned one of the $\mathrm{N}$ champions, uniformly at random. There's some chance you might get the same champion you had at first. If you don't like the champion you rerolled, and you still have at least $1 \mathrm{RD}$ left, you can reroll again. As long as you have at least $1 \mathrm{RD}$ left, you can keep rerolling.

For example, if $\mathrm{R}=2$ and $\mathrm{G}=2$, and you use a reroll in your first game, then after your first game you will have $1.5 \mathrm{RD}$. If you play another game, this time without using a reroll, you will have $2.0 \mathrm{RD}$. If you play another game without using a reroll, you will still have $2.0 \mathrm{RD}$ (because you can never have more than $\mathrm{R}=2$ ). If you use two rerolls in your next game, then after that game you will have $0.5$ $\mathrm{RD}$.

You will be given the list of champions, and how likely you are to win a game if you play each of them. If you play $10^{100}$ games and choose your strategy optimally, what fraction of the games do you expect to win?
## 输入格式

The first line of the input gives the number of test cases, $\mathrm{T}$. $\mathrm{T}$ test cases follow. Each starts with a line containing three space-separated integers: $\mathrm{N}, \mathrm{R}$ and $\mathrm{G}$. The next line contains $\mathrm{N}$ space-separated, real-valued numbers $\mathrm{P}_{\mathrm{i}}$, indicating the probability that you will win if you play champion $\mathrm{i}$.

## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the proportion of games you will win if you play $10^{100}$ games.

$\mathrm{y}$ will be considered correct if it is within an absolute or relative error of $10^{-10}$ of the correct answer.
## 样例

### 样例输入 #1
```
3
2 1 1
1.0000 0.0000
3 1 1
1.0000 0.0000 0.5000
6 2 3
0.9000 0.6000 0.5000 0.1000 0.2000 0.8000
```
### 样例输出 #1
```
Case #1: 0.750000000000
Case #2: 0.666666666667
Case #3: 0.618728522337
```
## 提示

**Limits**

- $1 \leqslant \mathrm{T} \leqslant 100$.
- $0.0 \leqslant \mathrm{P}_{\mathrm{i}} \leqslant 1.0$.
- $\mathrm{P}_{\mathrm{i}}$ will be expressed as a single digit, followed by a decimal point, followed by 4 digits.

**Small dataset(22 Pts)**

- Time limit: ~~60~~ 3 seconds.
- $1 \leqslant \mathrm{N} \leqslant 1000$.
- $1 \leqslant \mathrm{R} \leqslant 2$.
- $1 \leqslant \mathrm{G} \leqslant 3$.

**Large dataset(42 Pts)**

- Time limit: ~~120~~ 5 seconds.
- $1 \leqslant \mathrm{N} \leqslant 1000$.
- $1 \leqslant \mathrm{R} \leqslant 20$.
- $1 \leqslant \mathrm{G} \leqslant 20$.


---

---
title: "[GCJ 2011 Finals] Google Royale"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13386
tag: ['2011', 'Special Judge', '概率论', '期望', 'Google Code Jam']
---
# [GCJ 2011 Finals] Google Royale
## 题目描述

While visiting the planet Theta VIII, your team of space explorers is forced to participate in the plot of a badly-written book, which takes place in a hotel/casino called the Google Royale. In order to escape the Royale, you will have to make enough money from gambling that you can buy the hotel for $V$ dollars and leave.

You start with $A$ dollars, and you will participate in betting rounds until one of two conditions is met. If you finish any betting round with $\leq 0$ dollars, you will lose; if you finish a betting round with $\geq V$ dollars, you will buy the hotel and leave. Otherwise you'll keep starting new betting rounds.

Each betting round consists of one or more coin flips. If you have $X$ dollars at the start of the round, you can choose any integer $B$ between $1$ and $\min(X, M)$ to bet on the first coin flip.

With probability $50\%$, you win the coin flip, and the Royale immediately pays you $B$ dollars. You now have $X + B$ dollars, and the betting round ends.

With probability $50\%$, you lose the coin flip and owe the Royale $B$ dollars. You can now pay the $B$ dollars you owe and end the round. Or if $2B \leq M$, you can instead delay the payment and do a second coin flip with twice the bet: $2B$ dollars. If you lose again, then you owe the Royale $B + 2B = 3B$ dollars. You can continue doubling your bet in this way to $4B$, $8B$, etc., until either you win a coin flip, you choose to stop, or your next bet would exceed $M$. You can even continue if the total of all your bets in the current betting round exceeds $X$.

Once the round is over, you must pay the Royale for each coin flip you lost, and if you won a coin flip, the Royale pays you for that. For example, if you start with a bet of $1$ dollar, lose three coin flips, and then win one, you would gain $8 - 4 - 2 - 1 = 1$ dollar. If you lose three coin flips and then stopped, you would lose $4 + 2 + 1 = 7$ dollars. If you are left with $0$ or less after paying, then you are broke, and you have just lost the game.

Luckily you have brought an android with you, and he is able to compute the probability that you will win if you follow an optimal strategy. What is that probability, and what is the largest possible first bet you could make to have that probability? Remember that you are not allowed to bet more than $M$!

### Example

Suppose that you decide to use the following (sub-optimal) strategy. You have $A=5$ dollars; $M=20$ and $V=40$. The following sequence of events is possible:

*   Round 1: You can start by betting $1$, $2$, $3$, $4$ or $5$ dollars. You decide to begin a betting round by betting $2$ dollars.
    *   Step 1 ($B=2$): You win the first coin flip. You gain $2$ dollars, and the betting round ends. Now you have $7$ dollars.
*   Round 2: You begin a betting round by betting $5$ dollars.
    *   Step 1 ($B=5$): You lose the first coin flip. Now you owe the Royale $5$ dollars. Since $5\times 2 \leq 20$, you may do another coin flip with a bet of $5\times 2=10$ dollars. You choose not to. You lose $5$ dollars, and the betting round ends. Now you have $2$ dollars.
*   Round 3: You begin a betting round by betting $2$ dollars.
    *   Step 1 ($B=2$): You lose. Now you owe the Royale $2$ dollars. You choose to flip another coin with a bet of $4$ dollars.
    *   Step 2 ($B=4$): You lose. Now you owe the Royale a total of $6$ dollars. That's more than you have, which is okay. You choose to flip another coin with a bet of $8$ dollars.
    *   Step 3 ($B=8$): You win. You gain $8$ dollars, pay the $2+4=6$ dollars you owe, and the betting round ends. Now you have $4$ dollars.
*   Round 4: You begin a betting round by betting $2$ dollars.
    *   Step 1 ($B=2$): You lose. Now you owe the Royale $2$ dollars. You choose to flip another coin with a bet of $4$ dollars.
    *   Step 2 ($B=4$): You lose. Now you owe the Royale a total of $6$ dollars. You choose to flip another coin with a bet of $8$ dollars.
    *   Step 3 ($B=8$): You lose. Now you owe the Royale a total of $14$ dollars. You choose to flip another coin with a bet of $16$ dollars.
    *   Step 4 ($B=16$): You lose. Now you owe the Royale a total of $30$ dollars. Since $2\times 16>M$, you cannot flip another coin and you must pay what you owe. Now you have $-26$ dollars; you have lost.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow. Each line contains three integers separated by single spaces: $A$, $M$ and $V$, in that order.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$ $z$", where $x$ is the case number (starting from $1$); $y$ is the probability of winning if you follow an optimal strategy; and $z$ is the maximum first bet you can make without reducing your probability of winning. $y$ must be correct to within an absolute or relative error of $10^{-6}$.
## 样例

### 样例输入 #1
```
4
1 1 3
3 6 12
4 20 15
13 6 20
```
### 样例输出 #1
```
Case #1: 0.333333333 1
Case #2: 0.500000000 3
Case #3: 0.755555555 3
Case #4: 0.730769231 6
```
## 提示

**Limits**

- $1 \leq T \leq 100$.

**Small dataset (20 Pts, Test set 1 - Visible)**

- $1 \leq M \leq 20$.
- $1 \leq A < V \leq 20$.
- Time limit: ~~30~~ 6 seconds.

**Large dataset (40 Pts, Test set 2 - Hidden)**

- $1 \leq M \leq 10^{16}$.
- $1 \leq A < V \leq 10^{16}$.
- Time limit: ~~60~~ 12 seconds.



---

---
title: "[ZJOI2015] 地震后的幻想乡"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3343
tag: ['2015', '浙江', '期望', '积分', '状压 DP']
---
# [ZJOI2015] 地震后的幻想乡
## 题目描述

傲娇少女幽香是一个很萌很萌的妹子，而且她非常非常地有爱心，很喜欢为幻想乡的人们做一些自己力所能及的事情来帮助他们。 

这不，幻想乡突然发生了地震，所有的道路都崩塌了。现在的首要任务是尽快让幻想乡的交通体系重新建立起来。幻想乡一共有 $n$ 个地方，那么最快的方法当然是修复 $n-1$ 条道路将这 $n$ 个地方都连接起来。 幻想乡这 $n$ 个地方本来是连通的，一共有 $m$ 条边。现在这 $m$ 条边由于地震的关系，全部都毁坏掉了。每条边都有一个修复它需要花费的时间，第 $i$ 条边所需要的时间为 $e_i$。地震发生以后，由于幽香是一位人生经验丰富，见得多了的长者，她根据以前的经验，知道每次地震以后，每个 $e_i$ 会是一个 $0$ 到 $1$ 之间均匀分布的随机实数。并且所有 $e_i$ 都是完全独立的。

现在幽香要出发去帮忙修复道路了，她可以使用一个神奇的大魔法，能够选择需要的那 $n-1$ 条边，同时开始修复，那么修复完成的时间就是这 $n-1$ 条边的 $e_i$ 的最大值。当然幽香会先使用一个更加神奇的大魔法来观察出每条边 $e_i$ 的值，然后再选择完成时间最小的方案。 幽香在走之前，她想知道修复完成的时间的期望是多少呢？
## 输入格式

第一行两个数 $n,m$，表示地方的数量和边的数量。其中点从 $1$ 到 $n$ 标号。

接下来 $m$ 行，每行两个数 $a,b$，表示点 $a$ 和点 $b$ 之间原来有一条边。这个图不会有重边和自环。
## 输出格式

一行输出答案，四舍五入保留 $6$ 位小数。

## 样例

### 样例输入 #1
```
5 4
1 2
1 5
4 3
5 3
```
### 样例输出 #1
```
0.800000
```
## 提示

### 样例解释

对于第一个样例，由于只有四条边，幽香显然只能选择这四条，那么答案就是四条边的 $e_i$ 中最大的数的期望，由提示中的内容，可知答案为 $0.8$。

### 提示 

（以下内容与题意无关，对于解题也不是必要的。） 

对于 $n$ 个 $[0,1]$ 之间的随机变量 $x_1,x_2,...,x_n$，第 $k$ 小的那个的期望值是 $k/(n+1)$。  

数据范围： 

对于所有数据：$n \leq 10, \ m \leq n(n-1)/2, \ n,m \geq 1$。 

对于 $15 \%$ 的数据：$n \leq 3$。 

另有 $15 \%$ 的数据：$n \leq 10, m=n$。 

另有 $10 \%$ 的数据：$n \leq 10, m=n(n-1)/2$。 

另有 $20 \%$ 的数据：$n \leq 5$。 

另有 $20 \%$ 的数据：$n \leq 8$。


---

---
title: "随机数生成器"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3600
tag: ['动态规划 DP', '洛谷原创', 'O2优化', '期望', '洛谷月赛']
---
# 随机数生成器
## 题目描述

sol 研发了一个神奇的随机数系统，可以自动按照环境噪音生成真·随机数。

现在 sol 打算生成 $n$ 个 $[1,x]$ 的整数 $a_1, ..., a_n$，然后进行一些询问。

$q$ 次询问，每次询问 $i$ 有两个参数 $l_i$ 和 $r_i$，sol 会计算 $\min_{l_i \leq j \leq r_i} a_j$（$a$ 数组中下标在 $l_i, r_i$ 之间的数的最小值）。

最后测试结果会是这些询问得到的结果的最大值。

sol 进行了很多次实验，现在他想问问你测试结果的期望大小是多少，对 $666623333$ 取模。

## 输入格式

第一行三个数 $n, x, q$。

下面 $q$ 行，第 $i$ 行两个数表示 $l_i$ 和 $r_i$。

## 输出格式

一行一个数，表示答案。

## 样例

### 样例输入 #1
```
2 2 1
1 2
```
### 样例输出 #1
```
499967501
```
### 样例输入 #2
```
6 6 6
1 3
2 4
3 5
4 6
5 6
3 4
```
### 样例输出 #2
```
88571635
```
## 提示

提示：一个分数 $\frac{a}{b}$ 对 $666623333$ 取模的结果为 $a\times b^{666623331}~\mod~666623333$。

对于 $10\%$ 的数据，$n,x,q \leq 6$。

对于另外 $20\%$ 的数据，$q=1$。

对于 $50\%$ 的数据，$n,x,q \leq 300$。

对于 $70\%$ 的数据，$n,x,q \leq 800$。

对于 $100\%$ 的数据，$1 \leq n,x,q \leq 2000$，对于每个 $i$，$1 \leq l_i \leq r_i \leq n$。



---

---
title: "[SDOI2017] 龙与地下城"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3779
tag: ['2017', '各省省选', '山东', 'Special Judge', 'O2优化', '期望', '积分']
---
# [SDOI2017] 龙与地下城
## 题目描述

小 Q 同学是一个热爱学习的人，但是他最近沉迷于各种游戏，龙与地下城就是其中之一。

在这个游戏中，很多场合需要通过掷骰子来产生随机数，并由此决定角色未来的命运，因此骰子堪称该游戏的标志性道具。

骰子也分为许多种类，比如 $4$ 面骰、$6$ 面骰、$8$ 面骰、$12$ 面骰、$20$ 面骰，其中 $20$ 面骰用到的机会非常多。当然，现在科技发达，可以用一个随机数生成器来取代真实的骰子，所以这里**认为骰子就是一个随机数生成器**。

在战斗中，骰子主要用来决定角色的攻击是否命中，以及命中后造成的伤害值。举个例子，假设现在已经确定能够命中敌人，那么 $YdX$（也就是掷出 $Y$ 个 $X$ 面骰子之后所有骰子显示的数字之和）就是对敌人的基础伤害。在敌人没有防御的情况下，这个基础伤害就是真实伤害。

众所周知，骰子显示每个数的概率应该是相等的，也就是说，对于一个 $X$ 面骰子，显示 $0, 1, 2,\dots ,X−1$ 中每一个数字的概率都是 $\dfrac {1}{X}$。

更形式化地说，这个骰子显示的数 $W$ 满足离散的均匀分布，其分布列为

| $H$ | $0$ | $1$ | $2$ | $\cdots$ | $X-1$ |
| :--: | :--: | :--: | :--: | :--: | :--: |
| $P$ | $\dfrac {1}{X}$ | $\dfrac {1}{X}$ | $\dfrac {1}{X}$ | $\cdots$ | $\dfrac {1}{X}$ |


除此之外还有一些性质：

- $W$ 的**一阶原点矩**（**期望**）为

$$v_1(W)=E(W)=\sum_{i=0}^{X-1}i\cdot P(W=i)=\frac {X-1}{2}$$

- $W$ 的**二阶中心矩**（**方差**）为

$$\mu_2(W)=E((W-E(W))^2)=\sum_{i=0}^{X-1}(i-E(W))^2\cdot P(W=i)=\frac {X^2-1}{12}$$

言归正传，现在小 Q 同学面对着一个生命值为 A 的没有防御的敌人，能够发动一次必中的 $YdX$ 攻击，显然只有造成的伤害不少于敌人的生命值才能打倒敌人。但是另一方面，小 Q 同学作为强迫症患者，不希望出现 overkill，也就是造成的伤害大于 $B$ 的情况，因此**只有在打倒敌人并且不发生 overkill 的情况下小 Q 同学才会认为取得了属于他的胜利**。

因为小 Q 同学非常谨慎，他会进行 $10$ 次模拟战，每次给出敌人的生命值 $A$以及 overkill 的标准 $B$，他想知道此时取得属于他的胜利的概率是多少，你能帮帮他吗？

## 输入格式

第一行是一个正整数 $T$，表示测试数据的组数，

对于每组测试数据：

第一行是两个整数 $X,Y$，分别表示骰子的面数以及骰子的个数；

接下来 $10$ 行，每行包含两个整数 $A,B$，分别表示敌人的生命值 $A$ 以及 overkill 的标准 $B$。
## 输出格式

对于每组测试数据，输出 $10$ 行，对每个询问输出一个实数，要求绝对误差不超过 $0.013\, 579$。

也就是说，记输出为 $a$，答案为 $b$，若满足 $|a-b|\leq 0.013\,579$，则认为输出是正确的。
## 样例

### 样例输入 #1
```
1
2 19
0 0
0 1
0 2
0 3
0 4
0 5
0 6
0 7
0 8
0 9
```
### 样例输出 #1
```
0.000002
0.000038
0.000364
0.002213
0.009605
0.031784
0.083534
0.179642
0.323803
0.500000
```
## 提示

对于 $100\%$ 的数据，$T \leq 10$，$2 \leq X \leq 20$，$1 \leq Y \leq 200000$，$0 \leq A \leq B \leq (X-1)Y$。

**保证满足 $Y > 800$ 的数据不超过 $2$ 组。**

| 测试点编号 | $X$ | $Y$ | 备注 |
| :--: | :--: | :--: | :--: |
| $1$ | $\le 20$ | $\le 40$ | $X^Y\le 10^7$ |
| $2\sim 4$ | $\le 20$ | $\le 1\, 600$ | - |
| $5\sim 10$ | $\le 20$ | $\le 8\, 000$ | - |
| $11,12$ | $=2$ | $\le 200\, 000$ | - |
| $13\sim 20$ | $\le 20$ | $\le 200\, 000$ | - |



---

---
title: "大学数学题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3923
tag: ['数学', '洛谷原创', '提交答案', 'Special Judge', '素数判断,质数,筛法', '进制', '群论', '期望']
---
# 大学数学题
## 题目背景

琪露诺：我知道了！答案一定是1！

露米娅：什么鬼啊（汗），你还是再想想去吧。。我先把最后一道题给你，这是一道大学数学题哦

## 题目描述

露米娅：大妖精想构造一个 $ n $ 元有限域，元素用 $ 0 \sim n - 1 $ 的整数表示


有限域需要满足以下条件


1.有加法单位元 $ o $ ，满足对于任意元素 $ a $ ， $ o + a = a + o = a $


2.对于任意元素 $ a $ ，存在加法逆元 $ a^{-1} $ ，使得 $ a + a^{-1} = a^{-1} + a = o $


3.有不同于加法单位元 $ o $ 的乘法单位元 $ i $ ，满足对于任意元素 $ a $ ， $ i \times a = a \times i = a $


4.对于任意非加法单位元元素 $ a $ ，存在乘法逆元 $ a^{-1} $ ，使得 $ a \times a^{-1} = a^{-1} \times a = i $


5.对于任意元素 $ x $ , $ y $ ，有加法交换律，即 $ x + y = y + x  $


6.对于任意元素 $ x $ , $ y $ ，有乘法交换律，即 $ x \times y = y \times x  $


7.对于任意元素 $ x $ , $ y $ , $ z $ ，有加法结合律，即 $ ( x + y ) + z = x + ( y + z ) $


8.对于任意元素 $ x $ , $ y $ , $ z $ ，有乘法结合律，即 $ ( x \times y ) \times z = x \times ( y \times z ) $


9.对于任意元素 $ x $ , $ y $ , $ z $ ，有乘法分配律，即 $ ( x + y ) \times z = x \times z + y \times z $


大妖精当然会做啦，但是他想考考你


在输出中加法单位元  $ o $ 即为 0，乘法单位元  $ i $ 即为 1

## 输入格式

一个正整数 $ n $

$ 2 \leq n \leq 350 $

## 输出格式

##第一行输出一个整数 $ k $ ，若存在 $ n $ 元有限域则 $ k = 0 $ ，否则 $ k = -1 $


若 $ k = 0 $ 则

1.接下来 $ n $ 行输出一个 $ n $ 元有限域的加法表，第 $ i + 1 $ 行第 $ j + 1 $ 列上的数代表有限域中 $ i + j $ 的运算结果

2.接下来 $ n $ 行输出一个 $ n $ 元有限域的乘法表，第 $ i + 1 $ 行第 $ j + 1 $ 列上的数代表有限域中 $ i \times j $ 的运算结果

共输出 $ n \times 2 + 1 $ 行


upd1:SPJ非常严格，请不要在行末输出多余空格

（答案文件末尾的换行还是会自动忽略的）

upd2:正解文件比较大，洛谷可能会一直judging...

如果遇到这种情况请直接提交源代码

## 样例

### 样例输入 #1
```
2

```
### 样例输出 #1
```
0
0 1
1 0
0 0
0 1

```
## 提示

| 测试点  |  [$ n $ 的范围]       | 特殊性质|
| :-------: | :----------: | :-----------------: |
|1  | [$ n = 3 $]     | $ n $ 是质数           |
|2  | [$ n = 4 $]     | $ n $ 是2的整数次方 |
|3  | [$ n = 6 $]     |                无            |
|4  | [$ n = 8 $]     | $ n $ 是2的整数次方 |
|5  | [$ n = 9 $]     |                无            |
|6  | [$ n = 19 $]   | $ n $ 是质数           |
|7  | [$ n = 89 $]   | $ n $ 是质数           |
|8  | [$ n = 181 $] | $ n $ 是质数           |
|9  | [$ n = 233 $] | $ n $ 是质数           |
|10| [$ n = 25 $]   | $ n $ 是质数的平方|
|11| [$ n = 121 $] | $ n $ 是质数的平方|
|12| [$ n = 169 $] | $ n $ 是质数的平方|
|13| [$ n = 27 $]   |                无            |
|14| [$ n = 143 $] |                无            |
|15| [$ n = 128 $] | $ n $ 是2的整数次方 |
|16| [$ n = 81 $]   |                无            |
|17| [$ n = 125 $] |                无            |
|18| [$ n = 243 $] |                无            |
|19| [$ n = 256 $] | $ n $ 是2的整数次方 |
|20| [$ n = 343 $] |                无            |



---

---
title: "期望逆序对"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4223
tag: ['树状数组', '枚举', '期望', '矩阵乘法']
---
# 期望逆序对
## 题目背景

WXH大定理定律n
## 题目描述

mcfx领导的修道院试图通过古老的膜法阵召唤出传说中的膜法处佬WXH。在他把召唤用具准备齐全后，mcfx在众人的键盘声中启动了召唤阵。

这时，天地突然暗了下来，膜法阵中心电闪雷鸣。一道金光从天而降，金色的代码飘在了半空中。不一会，一个登陆界面显现了出来。mcfx仔细观察后发现上面有如下文字：

"WXHCoder是过去到未来所有的题目都有的题库。如果想要登陆它，你们必须解决接下来这道题。"

这道题目是这样子的：给你一个长为$n$的排列，有$k$次操作，每次随机选择两个不同的数交换，问期望逆序对数乘${{n}\choose{2}}^k$的结果。

mcfx发现数据范围是$n,k≤10^{20010910}$，他打算先探究更小的$n,k$。

${n}\choose{2}$表示在$n$个球中选两个的方案数
## 输入格式

第一行两个整数$n,k$

第二行一个$1$到$n$的排列
## 输出格式

输出期望逆序对数乘${{n}\choose{2}}^k$的结果模$10^9+7$
## 样例

### 样例输入 #1
```
5 4 
1 5 4 3 2
```
### 样例输出 #1
```
50000
```
## 提示

$n≤500000,k≤10^9$


---

---
title: "无意识之外的捉迷藏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4232
tag: ['递归', '线性规划', '期望']
---
# 无意识之外的捉迷藏
## 题目背景

### （五）心与心的对话

旧都还在下着雪。

不知道走了多远的路，已经远离街市了。

眼前隐隐约约能看到一座巨大的宫殿。

那就是，地灵殿吗？

心里突然紧张了起来。

这里住着旧地狱最可怕的觉妖怪。

古明地觉，她拥有读心的能力。人类，妖怪，甚至是怨灵，站在她面前的时候都如同赤身裸体，没有任何秘密可言。而且，听说在战斗中，她还会使用催眠术不断激起对手内心深处的恐怖回忆，从心灵上打垮对手。这样的妖怪自然会被人讨厌啦。

不过，此次地底之旅可不能因为要遇到可怕的妖怪而就此结束。

咚咚咚，敲了敲地灵殿的大门。

“来客吗，真是少见呢。”

眼前，站着一个少女，穿着蓝色的衣服，粉红色的裙子，头发也是粉红色的。

在她的胸前，悬着一只红色的大眼睛，通过眼睛周围的六根管子连接着身体。

她看起来很温柔的样子，完全不像听说的那样恐怖。

“来地底旅行的外面世界的人类吗？真是非常少见呢，居然找到了这里”

“看起来没有别的想法，就是想来转转呢，那就进来吧”

走进大门。

不愧是地灵”殿”，真的是好大的一个宫殿，桃红色和黑色相间的地板，印有花纹的窗户。

眼前是一组很宽的台阶，通向二楼，然后分成左右两个通道。

“很漂亮吧，这里空间大，宠物们都很喜欢呢。”

就这样，我跟着觉进入了她工作的房间，我们坐在沙发上聊了很久，虽然我很少说话。

在聊天的过程中，我了解到她还有一个妹妹古明地恋，由于不愿让别人因为自己会读心而讨厌自己，闭上了觉之瞳。觉为了开导妹妹，经常和宠物陪着她玩。

地灵殿，觉和妹妹，宠物们，一直在过着平静又温馨的生活。

“既然来这里了，就和我们一起玩吧。”觉邀请我们参与她们的游戏。

地底的妖怪会玩怎样的游戏呢？

于是，就这样，我就答应参与觉和恋的“无意识的捉迷藏”了。

说是”捉迷藏”，其实和普通的捉迷藏区别很大，更类似于”捉人游戏”。

就是觉和恋一开始分别站在两个地方，觉要捉到恋就算赢了。

但为什么又说是”捉迷藏”呢？

原来恋恋可以无意识地行动，也就是可以让周围人在潜意识里忽略她的存在，类似隐身，但又不是隐身。真是有趣的能力呢，是不是闭上了觉之瞳的缘故？

我们玩得很开心。有时无意识碰到了恋恋的手，还吓了一跳呢。

一段时间后，姐妹俩累了，觉还有工作要处理，就先回去了。

宠物们似乎意犹未尽，她们还想继续。

“可是在这个旧地狱啊，除了主人的妹妹恋以外，哪里又有妖怪能够操纵无意识呢？

算了,干脆玩普通的捉人游戏吧。”阿燐提议道。

于是宠物们很快又忘我地投入了”无意识之外的捉迷藏”中。

不知什么时候，我感到背后一凉，回过头一看，原来是恋恋。

我们就这样站在这里看着宠物们玩。

虽然不知道为什么能耐心地看那么长时间，但几个小时过去了，我们依然站在这里。

恋恋好像有一些疑问，在经过简单的交流后，我把她的疑问做了一个总结。

(见题目描述)

这个问题对无意识的恋恋来说果然无法解决啊。

能和姐妹俩聊得这么开心，真是很感激呢，那就尽自己的努力思考一下这个问题吧。

(后续剧情见题解，接下来请看T4)

## 题目描述

###问题摘要：

在一个有向无环图上，阿燐和阿空第0个时刻分别站在编号为$s_r$,$s_k$的节点，二人都知道双方的初始位置，对地图完全了解。

从第1个时刻起，每个时刻阿燐和阿空都可以选择站着不动，也可以选择移动到相邻的节点，二人每时刻的移动是同时开始的，并且不能中途改变方向。

阿燐被阿空捉住时，游戏立即结束。如果阿空一直没有捉住阿燐，第$t$个时刻结束后两人就不能再继续移动了，游戏将在第$t+1$个时刻结束。

阿空的目的是尽快捉住阿燐(捉住的定义是与阿燐同一时刻站在同一节点)，而阿燐的目的是尽可能更长时间不被阿空捉住。具体而言，若一场游戏进行了$t_0$时刻，阿燐的得分是$t_0$，阿空的得分是$-t_0$，双方都希望自己得分(或得分的期望值)更高。

我们认为在这个过程中阿燐和阿空随时都能知道对方的位置。两人在第$t$个时刻不能看出第$t+1$个时刻对方要走到哪里。

恋恋想知道，在双方最优决策的情况下，游戏结束时刻的期望值是多少。

## 输入格式

第一行5个整数$n$,$m$,$s_r$,$s_k$,$t$，用空格隔开，下同。

$n$表示地图点数，$m$表示边数。

接下来$m$行，每行两个整数$a$,$b$，表示从$a$到$b$有一条单向边(不存在重边)。

## 输出格式

一个实数，四舍五入保留3位小数，表示游戏结束时刻的期望值。

你的答案必须和标准答案完全相同才算正确。

## 样例

### 样例输入 #1
```
3 2 1 2 10
1 3
2 3

```
### 样例输出 #1
```
11.000
```
### 样例输入 #2
```
6 8 2 1 2
1 2
1 3
1 5
2 3
3 5
5 6
6 4
2 4

```
### 样例输出 #2
```
2.333
```
## 提示

###样例解释：

样例1：阿燐只要一直不动，阿空在前$t$单位时间内就无法抓到阿燐，答案为$t+1$，即```11.000```

样例2：无可奉告

###数据范围：

对于30%的数据 $n\leqslant3$，捆绑测试

对于100%的数据 $n,t\leqslant20$，前40%的数据和后30%的数据分别捆绑测试

###提示：
本题主要考察你能否使用正确的方法算出答案，对算法运行耗时要求不高。

by orangebird



---

---
title: "射命丸文的笔记"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4233
tag: ['O2优化', '剪枝', '强连通分量', '概率论', '期望', '快速傅里叶变换 FFT']
---
# 射命丸文的笔记
## 题目背景

### （七）再见，地底世界的朋友们

在地灵殿住了许多天了呢。

这些日子里，觉分享了很多旧地狱的故事。

此次地底旅行，可以说是非常充实了。

虽然仍旧有些不舍，不过人类总是要见太阳的，再说这样麻烦觉姐姐招待我们也有些过意不去呢。

那么，和觉，恋，阿燐，阿空，以及其他宠物们说再见吧。

......

旧地狱的街市，依旧飘着雪。

已经能看到溶洞了。

环境又变得幽闭起来。

诶，前面不是山女吗？

“啊，你们要回地面了吗，玩的怎样？”

“很开心呢，对了，剩下的问题已经解决了”

我们向山女解释了从荷取那里听到的方法。

“谢谢!”

“不客气，那么再见了~”

世界一片白茫茫的...

阳光是那么的刺眼，以至于几分钟后我们才能睁开眼睛看清楚地面的景色。

沿着魔法森林中的小路向神社走去，这次的旅行也在我们的脚步声中走向了尾声。

前方的地面上忽然出现了一页破损的笔记。

捡起来一看，发现是从文文的笔记本上脱落下来的。

射命丸文，作为（不靠谱的）新闻记者，观察到最近地灵殿里的宠物们偶尔会互相打架，于是将每场决斗的胜负关系写在了她的笔记本上。刚刚捡起来的这页笔记，上面就记录着几场“单循环赛”。

每场循环赛被抽象成一张竞赛图，其中顶点代表参加循环赛的宠物，从顶点 $u$ 指向顶点 $v$ 的边代表在一场比赛中宠物 $u$ 战胜了宠物 $v$。

观察到这页笔记上所有的竞赛图中都至少存在一条经过所有顶点的回路，我们猜想文文只会记录这样的循环赛。

可能是因为文文不清楚宠物们谁能打过谁，于是在那页笔记的最下面留下了一个这样的问题...

(见题目描述)

这最后一个问题，就留给你来解决啦。

博丽大结界，已经在我们身后了。

希望这次地底旅行，能给你留下美好的记忆~

(全文完)
## 题目描述

如果一个竞赛图含有哈密顿回路，则称这张竞赛图为值得记录的。

从所有含有 $n$ 个顶点（顶点互不相同）的，值得记录的竞赛图中等概率随机选取一个。

求选取的竞赛图中哈密顿回路数量的期望值。

由于答案可能过大/丢失精度，只需要输出答案除以 $998244353$ 的余数。

即：设答案为 $\frac{q}{p}$，则你需要输出一个整数 $x$，满足 $px\equiv q \mod 998244353$ 且 $0\leqslant x<998244353$，可以证明恰好存在一个这样的 $x$。

若不存在这样的竞赛图，输出 `-1`。
## 输入格式

一行一个正整数 $n$。
## 输出格式

$n$ 行，第 $i$ 行一个数字，代表输入为 $i$ 时的答案
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
1
-1
1
1
```
## 提示

### 样例解释：

$n=1$ 时只有一种满足条件的竞赛图，就是一个点。

$n=2$ 时竞赛图中只有一条边，不能形成哈密顿回路。

$n=3$ 时有两种满足条件的竞赛图，分别为 $1\to2\to3\to1$ 和 $1\to3\to2\to1$，都只有 $1$ 条哈密顿回路，随机取出后期望值为 $1$。

$n=4$ 时有很多种满足条件的的竞赛图，这里写不下了，但是所有满足条件的竞赛图都是同构的，所以随机取出后期望值为 $1$。

### 数据范围：

测试点 1~3 中 $n\leqslant7$。

测试点 4~6 中 $n\leqslant10$。

测试点 7~10 中 $n\leqslant1000$。

测试点 11~16 中 $n\leqslant10000$。

测试点 17~25 中 $n\leqslant100000$。

数据有梯度，每个测试点 $4$ 分。

为防止卡常，最后两个点开 2s 时限。

### 名词解释：

[竞赛图](https://en.wikipedia.org/wiki/Tournament_(graph_theory))：指任意两个顶点间恰有一条有向边的有向图。

[哈密顿回路](https://en.wikipedia.org/wiki/Hamiltonian_cycle)：指除起点和终点外经过所有顶点恰好一次且起点和终点相同的路径。


by oscar



---

---
title: "[BJOI2018] 治疗之雨"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4457
tag: ['递推', '2018', '各省省选', '北京', 'O2优化', '期望', '高斯消元']
---
# [BJOI2018] 治疗之雨
## 题目背景

（没玩过《炉石传说》的人可以跳过这一段）今天我们来探讨下《炉石传说》中“治疗之雨”（恢复 $12$ 点生命值，随机分配到所有友方角色上）和“暗影打击装甲”（每当一个角色获得治疗，便对随机敌人造成 $1$点伤害）这两张卡牌之间的互动效果。假设你场上有 $m$个剩余生命值无限大且生命值上限减去剩余生命值也无限大的随从，而对方的场上有 $k$个暗影打击装甲，你的英雄剩余生命值为 $p$、生命值上限为 $n$，现在你使用了一张可以恢复无限多（而不是 $12$ 点）生命值的治疗之雨，问治疗之雨期望总共恢复了几点生命值以后你的英雄会死亡（生命值降为 $0$；治疗之雨的判定机制使得在此后再也不会为英雄恢复生命值）。

注：题目背景与题目描述有冲突的地方请以题目描述为准

下面让我们再形式化地描述一遍问题。
## 题目描述

**题目更新：鉴于很多人反映看不懂题，但是出于尊重原题面的原则不进行大幅度更改。您可以将最小值和最大值理解为下限和上限，类似于题目背景中的血量。**


你现在有 $m+1$ 个数：第一个为 $p$，最小值为 $0$，最大值为 $n$；剩下 $m$个都是无穷，没有最小值或最大值。你可以进行任意多轮操作，每轮操作如下：

在不为最大值的数中等概率随机选择一个（如果没有则不操作），把它加一；

进行 $k$次这个步骤：在不为最小值的数中等概率随机选择一个（如果没有则不操作），把它减一。 

现在问期望进行多少轮操作以后第一个数会变为最小值 $0$。
## 输入格式

输入包含多组数据。
输入第一行包含一个正整数 $T$，表示数据组数。
接下来 $T$行 ，每行 4个非负整数 $n$、$p$、$m$、$k$（含义见题目描述），表示一次询问。
## 输出格式

输出 $T$行，每行一个整数，表示一次询问的答案。

如果无论进行多少轮操作，第一个数都不会变为最小值 $0$，那么输出```-1```；

否则，可以证明答案一定为有理数，那么请输出答案模 $1000000007$ 的余数，即设答案为 $\frac{a}{b}$（$a$、$b$为互质的正整数 ），你输出的整数为 $x$，那么你需要保证 $0 \leq x < 1000000007$且 $a \equiv bx\ mod\ 1000000007$。
## 样例

### 样例输入 #1
```
2
2 1 1 1
2 2 1 1
```
### 样例输出 #1
```
6
8
```
## 提示

###数据范围

对于 $10\%$ 的数据， $n \leq 3$ ，$m, k \leq 2$ 。

对于 $20\%$ 的数据， $n, m, k \leq 5$ 。

对于 $30\%$ 的数据， $n, m, k \leq 30$ 。

对于 $40\%$ 的数据， $n, m, k \leq 50$ 。

对于 $50\%$ 的数据， $n, m, k \leq 200$ 。

对于 $70\%$ 的数据， $n \leq 200$ 。

对于 $80\%$ 的数据， $n \leq 500$ 。

对于 $100\%$ 的数据， $1 \leq T \leq 100$，$1 \leq p \leq n \leq 1500$ ，$0 \leq m, k \leq 1000000000$。

保证不存在$n=p=k=1$,$m=0$的情况（因为出题人判错了）

保证不存在答案的分母是$1000000007$的倍数的情况（因为出题人没想到）


---

---
title: "玩游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4705
tag: ['数学', 'O2优化', '分治', '期望', '快速傅里叶变换 FFT', '洛谷月赛']
---
# 玩游戏
## 题目背景

### 警告：恶意提交评测将被封号。
## 题目描述

Alice 和 Bob 又在玩游戏。

对于一次游戏，首先 Alice 获得一个长度为 $n$ 的序列 $a$，Bob 获得一个长度为 $m$ 的序列 $b$。之后他们各从自己的序列里随机取出一个数，分别设为 $a_x, b_y$，定义这次游戏的 $k$ 次价值为 $(a_x + b_y)^k$。

由于他们发现这个游戏实在是太无聊了，所以想让你帮忙计算对于 $i = 1, 2, \cdots, t$，一次游戏 $i$ 次价值的期望是多少。

由于答案可能很大，只需要求出模 $998244353$ 下的结果即可。
## 输入格式

第一行两个整数 $n, m(1 \leq n, m \leq 10^5)$，分别表示 Alice 和 Bob 序列的长度。

接下来一行 $n$ 个数，第 $i$ 个数为 $a_i(0 \leq a_i < 998244353)$，表示 Alice 的序列。

接下来一行 $m$ 个数，第 $j$ 个数为 $b_j(0 \leq b_j < 998244353)$，表示 Bob 的序列。

接下来一行一个整数 $t(1 \leq t \leq 10^5)$，意义如上所述。
## 输出格式

共 $t$ 行，第 $i$ 行表示一次游戏 $i$ 次价值的期望。
## 样例

### 样例输入 #1
```
1 1
1
2
3
```
### 样例输出 #1
```
3
9
27
```
### 样例输入 #2
```
2 8
764074134 743107904
663532060 183287581 749169979 7678045 393887277 27071620 13482818 125504606
6
```
### 样例输出 #2
```
774481679
588343913
758339354
233707576
36464684
461784746
```


---

---
title: "CF1278F Cards 加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6031
tag: ['数学', '递推', '期望']
---
# CF1278F Cards 加强版
## 题目背景

[原题链接](https://www.luogu.com.cn/problem/CF1278F)
## 题目描述

有 $m$ 张牌，其中有一张是王牌。将这些牌均匀随机打乱 $n$ 次，设有 $x$ 次第一张为王牌，求 $x^k$ 的期望值。

答案对 $998244353$ 取模。
## 输入格式

一行三个正整数 $n,m,k$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
1234 2345 3456
```
### 样例输出 #1
```
398700213
```
### 样例输入 #2
```
998244352 1337 5000
```
### 样例输出 #2
```
326459680
```
### 样例输入 #3
```
233333333 114514 9982443
```
### 样例输出 #3
```
825888958
```
## 提示

【数据范围】  
对于 $20\%$ 的数据，$1\le k \le 5000$；  
对于 $40\%$ 的数据，$1\le k \le 10^5$；  
对于 $100\%$ 的数据，$1\le k \le 10^7$，$1\le n,m \le 998244352$。

Solution：iostream  
Data：NaCly\_Fish


---

---
title: "[ICPC 2014 WF] Pachinko"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6899
tag: ['数学', '2014', 'Special Judge', '期望', 'ICPC']
---
# [ICPC 2014 WF] Pachinko
## 题目描述

You have been hired by Addictive Coin Machines to help design the next hit in their line of eye-catching, coin-guzzling, just-one-more-try Pachinko machines for casinos around the world.

Playing a Pachinko machine involves launching balls into a rectangular grid filled with pegs, obstacles, and targets. The ball bounces around the grid until it eventually hits one of the targets. The player earns a certain number of points depending on which target is hit.

The grid pattern for the next Pachinko machine has already been designed, but point values for the targets have not been assigned. These must be set so that like all casino machines, the machine is profitable but not too profitable. Thus it is important to figure out the probability of a ball hitting any particular target. That’s your job!

For simplicity, the grid is modeled as a tall rectangle filled with mostly-open spaces (each represented by ‘.’), impassable obstacles (each represented by ‘X’), and targets (each represented by ‘T’).

A ball is launched randomly with uniform probability into one of the mostly-open spaces on the top row of the grid. From that point on, collisions with pegs cause the ball to randomly bounce up, down, left, or right, with various given probabilities. For simplicity, assume these probabilities are the same for every space in the grid. If the ball bounces into an obstacle or attempts to move off the grid, it won’t actually move from its current space. When the ball moves into a target it is removed from play.

You can safely assume that the average number of spaces visited by a ball before hitting a target will not exceed $10^{9}$. It would not make for a very enjoyable game if the ball just bounces forever!

For each target, calculate the probability that it is the one hit by a launched ball.
## 输入格式

The input consists of a single test case. The first line contains integers $w$ and $h$, which are the width and height of the Pachinko grid ($1 \leq w \leq 20$ and $2 \leq h \leq 10\, 000$). The next line contains four non-negative integers $u$, $d$, $l$, and $r$, which sum to 100 and are the percentage probabilities of the ball bouncing up, down, left, or right from any open space.

Each of the next $h$ lines contains $w$ characters, each of which is ‘.’, ‘X’, or ‘T’. These lines describe the Pachinko grid. The first line, which describes the top row of the grid, contains at least one ‘.’ and no ‘T’s.
## 输出格式

Display one line for each ‘T’ in the grid, in order from top to bottom, breaking ties left to right. For each target, display the probability that a launched ball will hit it. Give the answer with an absolute error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
3 2
20 20 20 40
X.X
T.T

```
### 样例输出 #1
```
0.333333333
0.666666667

```
### 样例输入 #2
```
4 5
12 33 28 27
....
.XX.
....
T..T
XTTX

```
### 样例输出 #2
```
0.435853889
0.403753221
0.081202502
0.079190387

```
## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

**题目描述**

有一个宽度为 $w$ 高度为 $h$ 的方格纸， $ w \times h$ 的格子中，有一些是空的，有一些是洞，有一些是障碍物。从第一行的空的格子中随机选一个放置一个球，向上下左右移动的概率比为 $p_u : p_d : p_l : p_r$（满足 $p_u + p_d + p_l + p_r = 100$），不能移动到有障碍物的格子上。对于每个洞，输出落入该洞的概率。$w \le 20, h \le 10000$。保证第一行没有洞。

**输入格式**

第一行两个整数表示 $w, h$ 。

第二行四个整数表示 $p_u, p_d, p_l, p_r$ 。

接下来有一个 $h$ 行 $w$ 的字符矩阵，其中 `.` 表示空，`X` 表示障碍物，`T` 表示洞。

**输出格式**

若干行，每一行一个整数，按照矩阵从上到下，从左到右的顺序，输出每个洞的答案。绝对误差不超过 $10^{-6}$ 即为正确。


---

---
title: "「EZEC-7」线段树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7445
tag: ['O2优化', '生成函数', '期望', '快速傅里叶变换 FFT', '快速数论变换 NTT', '洛谷月赛']
---
# 「EZEC-7」线段树
## 题目背景

Bob 喜欢线段树。

## 题目描述

如果你不知道线段树，可以看 提示说明 中的定义。

Bob 得到了一个长度为 $n$ 的序列 $a_{1,2,\cdots,n}$，初始全为 $0$。

接着 Bob 进行了 $m$ 次区间加操作，每次操作会等概率地从 $[1,n]$ 的所有 $\dfrac{n(n+1)}{2}$ 个子区间中随机选择一个进行操作，每次加的数是 $[-1,V]$ 之间等概率随机的整数。

$m$ 次操作完之后要求出每一个位置的值。

由于 Bob 喜欢线段树，他熟练地打出一颗 $[1,n]$ 上的线段树来解决这个问题，使用懒惰标记来解决区间加的问题。

打代码的过程中 Bob 忽然想到了两个减小 $\mathrm{Pushdown}$（下传懒惰标记）次数的方法：

+ 修改的时候不 $\mathrm{Pushdown}$，最后一次性 $\mathrm{Pushdown}$（即 $\mathrm{Pushall}$ 函数）。

+ $\mathrm{Pushall}$ 到一个节点的时候，如果这个节点的懒惰标记为 $0$ 那么不 $\mathrm{Pushdown}$。

现在 Bob 想知道期望 $\mathrm{Pushdown}$ 次数，可是他不会算，于是来问你。

下面是 Bob 写的线段树伪代码（其中 `tag` 数组为懒惰标记）：

$
\displaystyle
\begin{array}{l}
\mathrm{pushdown\_counter}\leftarrow 0\\
\\
\textbf{function }\mathrm{Update(Node},l,r,ql,qr,Delta)\\
\qquad \textbf{if } [l,r]\cap [ql,qr] = \varnothing \textbf{ then}\\
\qquad \qquad \textbf{return}\\
\qquad \textbf{end if}\\
\qquad \textbf{if }[l,r] \subseteq [ql,qr] \textbf{ then}\\
\qquad \qquad \mathrm{tag[Node]\leftarrow tag[Node]}+Delta\\
\qquad \qquad \textbf{return}\\
\qquad \textbf{end if}\\
\qquad mid\leftarrow \lfloor\dfrac{l+r}{2}\rfloor\\
\qquad \mathrm{Update(LeftChild},l,mid,ql,qr,Delta)\\
\qquad \mathrm{Update(RightChild},mid+1,r,ql,qr,Delta)\\
\textbf{end function}\\
\\
\textbf{function }\mathrm{Pushdown(Node)} \\
\qquad \mathrm{tag[LeftChild]\leftarrow tag[LeftChild]+tag[Node]}\\
\qquad \mathrm{tag[RightChild]\leftarrow tag[RightChild]+tag[Node]}\\
\qquad \mathrm{pushdown\_counter}\leftarrow \mathrm{pushdown\_counter}+1\\
\textbf{end function}\\
\\
\textbf{function }\mathrm{Pushall(Node},l,r)\\
\qquad \textbf{if } \mathrm{Node\ is\ Leaf} \textbf{ then}\\
\qquad \qquad \textbf{return}\\
\qquad \textbf{end if}\\
\qquad \textbf{if } \mathrm{tag[Node] \not= 0} \textbf{ then}\\
\qquad \qquad \mathrm{Pushdown(Node)}\\
\qquad \textbf{end if}\\
\qquad mid\leftarrow \lfloor\dfrac{l+r}{2}\rfloor\\
\qquad \mathrm{Pushall(LeftChild},l,mid)\\
\qquad \mathrm{Pushall(RightChild},mid+1,r)\\
\textbf{end function}
\end{array}
$


换句话说，你要帮 Bob 求出 `pushdown_counter` 的期望值。

答案对 $998244353$ 取模。

## 输入格式

一行三个整数 $n,m,V$。
## 输出格式

一个整数，期望 $\mathrm{Pushdown}$ 次数对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
2 1 0

```
### 样例输出 #1
```
166374059

```
### 样例输入 #2
```
2 2 1

```
### 样例输出 #2
```
813384288

```
### 样例输入 #3
```
3 2 1

```
### 样例输出 #3
```
462150164

```
### 样例输入 #4
```
100 114 514

```
### 样例输出 #4
```
718571152

```
## 提示

**【样例解释 #1】**

整颗线段树只有 $3$ 个节点：$[1,2],[1,1],[2,2]$。

只有节点 $[1,2]$ 可能 $\mathrm{Pushdown}$。

当操作为 $\mathrm{Update(1,2,-1)}$ 的时候，根节点的懒惰标记为 $-1$， $\mathrm{Pushall}$ 在根号节点会 $\mathrm{Pushdown}$；而 $\mathrm{Update(1,2,0)}$ 之后，由于根节点懒惰标记为 $0$ 不 $\mathrm{Pushdown}$。

其余 $4$ 种操作均把懒惰标记打在叶子节点，即 $\mathrm{Update(1,1,-1)},\mathrm{Update(1,1,0)},\mathrm{Update(2,2,-1)},\mathrm{Update(2,2,0)}$，不会 $\mathrm{Pushdown}$。

所以，总共 $6$ 种情况，能 $\mathrm{Pushdown}$ 的只有 $1$ 种，期望次数为 $\dfrac{1}{6}$。

**【样例解释 #2】**

由于情况过多，不一一解释，只解释一种情况。

如果执行的 $2$ 次操作分别为 $\mathrm{Update(1,2,-1)},\mathrm{Update(1,2,1)}$，由于这时候根节点的懒惰标记为 $0$，在 $\mathrm{Pushall}$ 的时候仍然不会 $\mathrm{Pushdown}$。

---------

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n\le$       | $m\le$       | $V$               | 分值 | 时间限制$\text{ / ms}$ |
| :----: | :------------: | :------------: | :-----------------: | :----: | :--------: |
| $1$        | $4$  | $4$   | $\le 2$         | $3$  | $500$    |
| $2$        | $300$ | $300$ | $\le 300$       | $7$  | $500$    |
| $3$        | $1000$ | $1000$ | $\le 1000$      | $10$ | $500$    |
| $4$       | $300$  | $10^5$ | $=1000$          | $15$ | $2000$   |
| $5$        | $10^5$ | $10^5$ | $\le 0$         | $10$ | $3000$   |
| $6$        | $10^5$ | $10^5$ | $=1000$          | $15$ | $3000$   |
| $7$        | $10^5$ | $10^5$ | $\le 998244350$ | $40$ | $3000$   |


对于 $100\%$ 的数据，$1 \le n \le 10^5$，$1 \le m \le 10^5$，$-1 \le V \le 998244350$。

----------

**【线段树定义】**

线段树是一棵每个节点上都记录了一个线段的二叉树。根节点记录的线段是 $[1, n]$。对于每个节点，若它记录的线段是 $[l, r]$ 且 $l\not= r$，取 $m = \lfloor \dfrac{l+r}{2} \rfloor$，则它的左右儿子节点记录的线段分别是 $[l, m]$ 和 $[m+1,r]$；若 $l=r$，则它是叶子节点。



---

---
title: "磁控法则"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7498
tag: ['2021', 'O2优化', '树形 DP', '期望']
---
# 磁控法则
## 题目背景

>那只不过是别人的不幸。

诺顿进入了一个结构复杂的洞穴。在之前的勘察中，他已经得知了这个洞穴里有他梦寐以求的宝藏。

然而这个洞穴是如此的黑暗与复杂，以至于他探索了许久都没有找到宝藏的所在地。但宝藏强大的吸引力仍驱使着他继续搜寻。然而很快他就意识到了不对劲，因为那股吸引力不仅作用在他脑海中，也作用在他身体上——宝藏的防御机关正释放巨大的磁力试图驱逐外来者。

「果然，这就是它自带的保护机制吗？」诺顿笑了笑，拿出了一小块散发着奇特光芒的金属。

「不过，我也是有准备的。」
## 题目描述

诺顿所在的洞穴可以看作是由 $n$ 个洞窟和 $n-1$ 条通道形成的树状结构，诺顿在石窟 $s$，宝藏在石窟 $t$。在宝藏所在的石窟里有一块拥有强大磁场的特殊的磁铁，诺顿身上也有一块小型的同样材质的磁铁。宝藏石窟里的磁铁**只有一个磁极**（N 或 S），并且**磁极不会发生变化**。诺顿身上的磁铁也**只有一个磁极**（N 或 S），但**每个时刻开始时会有 $p$ 的概率切换磁极**（N 变成 S，S 变成 N）。

每个时刻诺顿的移动方式由宝藏石窟磁铁的磁极和诺顿身上磁铁的磁极决定：

1. 两块磁铁磁极不同。此时两块磁铁会触发「吸引」效果。诺顿会因为磁铁间的吸引力移动到与 $s$ 相连的石窟中到 $t$ 距离 $-1$ 的石窟中（即**以 $t$ 为根时 $s$ 的父亲**）。

2. 两块磁铁磁极相同。此时两块磁铁会触发「弹射」效果。诺顿会因为磁铁间的排斥力**等概率**移动到与 $s$ 相连的石窟中到 $t$ 距离 $+1$ 的石窟（即**以 $t$ 为根时 $s$ 的任意一个儿子**）。如果没有满足的石窟，将触发「眩晕」效果，下个时刻诺顿将**不进行任何的移动，也不会进行任何的磁极切换**。

经过一段时间的勘察，诺顿已经知道了整个洞穴的结构以及磁极切换的概率 $p$。为了更好的寻找宝藏，他每次会向你提出询问，你需要回答他如果一开始诺顿在石窟 $x$，身上磁铁磁极为 $c_1$，宝藏在石窟 $y$，石窟内磁铁磁极为 $c_2$，期望在多少时刻后诺顿可以找到宝藏。
## 输入格式

第一行三个整数 $n,q,p$，分别表示石窟数，询问数和磁极切换概率。其中磁极切换概率为在 $998244353$ 取模意义下的概率。

接下来 $n-1$ 行，每行两个正整数 $u,v$，表示石窟 $u$ 和石窟 $v$ 之间存在一条通道。保证最后结构为一棵树。

接下来 $q$ 行，每行**依次**有一个正整数 $x$，一个字符 $c_1$，一个正整数 $y$，一个字符 $c_2$，表示一个询问，各自意义如上。保证 $c_1,c_2$ 为 `N` 或 `S`。
## 输出格式

$q$ 行，每行一个非负整数，表示询问答案对 $998244353$ 取模后的结果。
## 样例

### 样例输入 #1
```
6 4 499122177
1 2
1 3
5 3
4 6
4 3
2 N 1 S
3 S 1 S
5 N 6 N
1 S 4 N
```
### 样例输出 #1
```
3
6
17
11
```
### 样例输入 #2
```
10 6 199648871
3 7
4 9
2 3
5 6
7 10
5 7
5 9
8 2
1 3
10 S 5 S
1 N 7 S
1 N 4 N
1 S 4 N
4 N 3 S
7 N 4 N
```
### 样例输出 #2
```
332748127
8
665496262
665496261
665496253
831870314
```
## 提示

#### 样例一解释
每个时刻磁极切换概率为 $\dfrac{1}{2}$。

洞窟结构如下：  
![](https://cdn.luogu.com.cn/upload/image_hosting/od4ixuog.png)

对于询问 $1$，诺顿在第 $1$ 个时刻有 $\dfrac{1}{2}$ 的概率移动到 $1$，有 $\dfrac{1}{2}$ 的概率触发「眩晕」进入第 $3$ 个时刻。在第 $3$ 个时刻同样有 $\dfrac{1}{2}$ 的概率移动到 $1$，有 $\dfrac{1}{2}$ 的概率触发「眩晕」进入第 $5$ 个时刻……期望结果为 $1\times\dfrac{1}{2}+3\times\left(\dfrac{1}{2}\right)^2+5\times\left(\dfrac{1}{2}\right)^3+\ldots=3$。

------------
#### 数据范围

**本题采用捆绑测试**。

+ Subtask 1 ( $10\%$ )：$n,q\leq15$。
+ Subtask 2 ( $20\%$ )：$n\leq10^3$。
+ Subtask 3 ( $25\%$ )：对于所有询问，保证 $y=1$。
+ Subtask 4 ( $45\%$ )：无特殊限制。

对于所有数据，$2\leq n\leq5\times 10^5,1\leq q\leq5\times10^5,1\leq u,v,x,y\leq n,x\neq y,2\leq p\leq998244352$。

------------
**本题读入量较大，请使用较快的读入方式。**


---

