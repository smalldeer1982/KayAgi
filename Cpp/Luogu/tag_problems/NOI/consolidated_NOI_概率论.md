---
title: "[集训队互测 2023] Grievous Lady"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10010
tag: ['动态规划 DP', '数学', '集训队互测', '2023', '爬山算法 Local search', '模拟退火', '随机调整', '线性规划', '概率论', '线性代数', '随机化']
---
# [集训队互测 2023] Grievous Lady
## 题目背景

对立从那灰暗的塔楼进入，逐步踏入这个扭曲的迷宫深处。

对立的心突然绞痛起来。

对立后退了一步，扑腾了一下便跪倒下来。

未及碰到，灰黑的地板就突然崩裂瓦解，先一步向下坠落。

先前收集的纷争碎片，连同塔楼本身，一同化作了一场倾盆大雨，包围在对立四周。

异象骤起，对立的思维也陷入一片混乱。

塔楼落入了先前的由光芒碎片组成的欢乐海洋，但对立却被纷争碎片紧紧地包裹着。

在那由光芒和纷争碎片交错的风暴之中，对立所见的只有那些令人厌恶的纷争碎片。

那枚世界尽头的记忆映入了对立的视野。

面对着世界一点点地走向终结的景象，对立的理性在碎裂。

对立意识到，一切美好的记忆不过是须臾，最终都会走向破灭。

四周的碎片依旧在飞旋，对立试图看清那些玻璃碎片的变换。

对立意识到，现在围绕着的那些碎片，正以最恐怖的方式运转。

这个碎片风暴所带来的「忧郁度」，可以被简单地描述为外侧碎片的旋转速度之和乘上内侧碎片的旋转速度之和。

一片玻璃碎片在外侧总是以一种速度正旋，而在内侧总是以另一种速度逆旋。

每片碎片都是是来自不同世界的刹那记忆，故而其转速总可以认为是独立随机指定的。

在残存无几的希望将尽未尽之时，对立只想知道，现在的碎片风暴的忧郁度，也就是最大可能的忧郁度，究竟是多少。
## 题目描述

共有 $n$ 个元素，标号 $1\sim n$，每个元素 $j$ 有两个正整数权值 $a_j,b_j$。

你要确定一个 $[1,n]\cap\mathbb N$ 的子集 $S$，从而最大化

$$
(\sum_{k=1}^na_k[k\in S])(\sum_{k=1}^nb_k[k\notin S])
$$

这个问题显然不可做，因此**保证每个 $a_j,b_j$ 分别在 $[1,A]\cap\mathbb N,[1,B]\cap\mathbb N$ 内独立均匀随机生成**。

现在给定 $n,A,B$ 和每个元素的两个权值 $(a_j,b_j)$，请求出这个最大的答案。
## 输入格式

本题每个测试点中有多组测试数据。

第一行四个整数，$T,n,A,B$，$T$ 表示该组数据内的数据组数，$n,A,B$ 表示该测试点内的所有数据均对应此 $n,A,B$。

接下来每组数据占 $n$ 行，其中第 $j$ 行两个整数 $a_j,b_j$。

保证 $a_j,b_j$ 在对应范围内独立均匀随机生成。
## 输出格式

对于每组数据输出一行一个整数，表示其答案。

注意这个答案可能很大，你可能需要使用 `__int128` 类型来进行中间存储与运算，并最后输出。注意你可能需要使用一些正确的输出方式。

## 提示

#### 输入输出样例

**因为本题数据规模太大，直接提交评测会对评测机带来很大压力，本题将提供很多大样例；请尽量减少本题的提交次数。**

请参见下发文件 `grievouslady*.in/ans`，共 $50$ 组，基本按照部分分的方法造。

由于本题保证数据随机，不提供手搓样例。

#### 数据范围与提示

对于所有的数据，保证 $10\le n\le3000$，$10^4\le A,B\le10^{12}$，$1\le T\le50$。

~~本题设置子任务，各子任务~~共 $100$ 个测试点。具体的测试点分布可以见下表。

**本题在洛谷上的版本不设置子任务**。

（**由于表格比较宽，洛谷上较难完整显示，你可能要使用题目页面的“展开”功能**）

|测试点编号|$n$|$A$|$B$|测试点编号|$n$|$A$|$B$|测试点编号|$n$|$A$|$B$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1\sim2$|$=10$|$=10^4$|$=10^4$|$33\sim34$|$=100$|$=10^4$|$=10^4$|$67\sim68$|$=1000$|$=10^5$|$=10^{12}$|
|$3\sim4$|$=10$|$=10^9$|$=10^9$|$35\sim36$|$=100$|$=10^5$|$=10^5$|$69\sim70$|$=1000$|$=10^9$|$=10^9$|
|$5\sim6$|$=10$|$=10^{12}$|$=10^{12}$|$37\sim38$|$=100$|$=10^5$|$=10^9$|$71\sim72$|$=1000$|$=10^{12}$|$=10^{12}$|
|$7\sim8$|$=20$|$=10^4$|$=10^4$|$39\sim40$|$=100$|$=10^9$|$=10^9$|$73\sim74$|$=1500$|$=10^5$|$=10^{12}$|
|$9\sim10$|$=20$|$=10^9$|$=10^9$|$41\sim42$|$=100$|$=10^{12}$|$=10^{12}$|$75\sim76$|$=1500$|$=10^9$|$=10^9$|
|$11\sim12$|$=20$|$=10^{12}$|$=10^{12}$|$43\sim44$|$=200$|$=10^5$|$=10^{12}$|$77\sim78$|$=1500$|$=10^{12}$|$=10^{12}$|
|$13\sim14$|$=30$|$=10^4$|$=10^4$|$45\sim46$|$=200$|$=10^9$|$=10^9$|$79\sim80$|$=2000$|$=10^5$|$=10^{12}$|
|$15\sim16$|$=30$|$=10^9$|$=10^9$|$47\sim48$|$=200$|$=10^{12}$|$=10^{12}$|$81\sim82$|$=2000$|$=10^9$|$=10^9$|
|$17\sim18$|$=30$|$=10^{12}$|$=10^{12}$|$49\sim50$|$=300$|$=10^5$|$=10^{12}$|$83\sim84$|$=2000$|$=10^{12}$|$=10^{12}$|
|$19\sim20$|$=40$|$=10^4$|$=10^4$|$51\sim52$|$=300$|$=10^9$|$=10^9$|$85\sim86$|$=2500$|$=10^4$|$=10^9$|
|$21\sim22$|$=40$|$=10^9$|$=10^9$|$53\sim54$|$=300$|$=10^{12}$|$=10^{12}$|$87\sim88$|$=2500$|$=10^5$|$=10^{12}$|
|$23\sim24$|$=40$|$=10^{12}$|$=10^{12}$|$55\sim56$|$=500$|$=10^5$|$=10^{12}$|$89\sim90$|$=2500$|$=10^9$|$=10^9$|
|$25\sim26$|$=50$|$=10^4$|$=10^4$|$57\sim58$|$=500$|$=10^9$|$=10^9$|$91\sim92$|$=2500$|$=10^{12}$|$=10^{12}$|
|$27\sim28$|$=50$|$=10^4$|$=10^9$|$59\sim60$|$=500$|$=10^{12}$|$=10^{12}$|$93\sim94$|$=3000$|$=10^4$|$=10^9$|
|$29\sim30$|$=50$|$=10^9$|$=10^9$|$61\sim62$|$=800$|$=10^5$|$=10^{12}$|$95\sim96$|$=3000$|$=10^5$|$=10^{12}$|
|$31\sim32$|$=50$|$=10^{12}$|$=10^{12}$|$63\sim64$|$=800$|$=10^9$|$=10^9$|$97\sim98$|$=3000$|$=10^9$|$=10^9$|
|||||$65\sim66$|$=800$|$=10^{12}$|$=10^{12}$|$99\sim100$|$=3000$|$=10^{12}$|$=10^{12}$|

~~我们按如下方式布局各测试点~~：
* ~~subtask $1$：$1\sim12$，占 $\rm12pts$~~。
* ~~subtask $2$：$13\sim32$，占 $\rm20pts$~~。
* ~~subtask $3$：$33\sim36$，占 $\rm4pts$~~。
* ~~subtask $4$：$37\sim48$，占 $\rm12pts$~~。
* ~~subtask $5$：$49\sim50$，占 $\rm2pts$~~。
* ~~subtask $6$：$51\sim60$，占 $\rm10pts$~~。
* ~~subtask $7$：$61\sim72$，占 $\rm12pts$~~。
* ~~subtask $8$：$73\sim84$，占 $\rm12pts$~~。
* ~~subtask $9$：$85\sim92$，占 $\rm8pts$~~。
* ~~subtask $10$：$93\sim100$，占 $\rm8pts$~~。

~~**本题不设置子任务依赖，因此请确保经样例测试后你的算法正确后再提交，以免卡评测机**。~~

#### 后记

这个世界——一切——都源于过去。过去的影像，哪怕是欢乐的记忆，就像是白昼过后的黑夜，渐渐导致了这份世界末日。

泪水盈眶。对立的眼神转为一片黑暗。

对立与这些玻璃起了共鸣，围绕于四周的回忆之壳开始崩裂。

对立就身处其中，站在那炫目的光芒前方，已经没有任何情感了。

扭曲的迷宫，也在对立的力量下，悉数损毁……

时光逝去，对立变了。不再激情地收集回忆，而是近乎无意识地走在这世界之中，并不再抱有任何雄心壮志。

如今，对立正在一个破旧坍塌的建筑旁行走着，旋转着某天在废墟中找到的太阳伞。




---

---
title: "[USACO24JAN] Island Vacation P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10140
tag: ['USACO', '2024', '树形 DP', '概率论', '圆方树']
---
# [USACO24JAN] Island Vacation P
## 题目描述

Bessie 正在一个 $N$（$2\le N\le 10^4$）座岛组成的岛屿网络中度假，编号为 $1\ldots N$，由 $M$ 座双向通行的桥连接，每座桥连接两座岛（$N−1\le M\le \dfrac{3(N-1)}{2}$）。保证所有桥形成连通的简单图（具体地说，没有两座桥连接同一对岛屿，也没有一座桥连接一座岛到其自身）。

另外保证没有一座桥处在多于一个简单环上。一个简单环是一个不包含重复岛的环。

Bessie 从岛 $1$ 开始，按以下过程旅行。假设她目前在岛 $i$ 上，

1. 如果不存在连接岛 $i$ 的她尚未穿过的桥，则她的度假结束。
2. 否则，以 $p_i \pmod {10^9+7}$ 的概率，她的度假结束。
3. 否则，在连接岛 $i$的所有她还没有穿过的桥中，她均匀地随机选择一座并穿过它。

对于每座岛，输出她在该岛上结束度假的概率，对 $10^9+7$ 取模。 
## 输入格式

输入的第一行包含独立的测试用例的数量 $T$（$1\le T\le 10$）。相邻的测试用例之间以一个空行分隔。

每一个测试用例的第一行包含 $N$ 和 $M$，其中 $N$ 为岛的数量，$M$ 为桥的数量。输入保证所有测试用例的 $N$ 之和不超过 $10^4$。

第二行包含 $p_1,p_2,\ldots,p_N$（$0\le p_i<10^9+7$）。

以下 $M$ 行描述所有的桥。第 $i$ 行包含整数 $u_i$ 和 $v_i$（$1\le u_i<v_i\le N$），表示第 $i$ 座桥连接岛 $u_i$ 和 $v_i$。输入保证所有桥满足上文中的限制。 
## 输出格式

对于每个测试用例输出一行，包含在岛 $1$ 到 $N$ 的每一座岛上结束度假的概率模 $10^9+7$ 的余数，用空格分隔。
## 样例

### 样例输入 #1
```
2

3 2
0 10 111111112
1 3
2 3

6 5
500000004 0 0 0 0 0
1 5
1 3
4 5
5 6
1 2
```
### 样例输出 #1
```
0 888888896 111111112
500000004 166666668 166666668 83333334 0 83333334
```
### 样例输入 #2
```
2

5 5
333333336 333333336 0 0 0
1 2
2 3
3 4
4 5
1 5

5 5
0 0 0 0 0
1 2
2 3
2 4
1 4
1 5
```
### 样例输出 #2
```
777777784 222222224 0 0 0
0 0 333333336 0 666666672
```
### 样例输入 #3
```
1

11 13
2 3 4 5 6 7 8 9 10 11 12
1 2
1 3
2 3
2 4
4 5
2 5
4 8
5 9
2 6
6 7
2 7
6 10
5 11
```
### 样例输出 #3
```
133332478 200000394 577778352 999999971 399999938 933333282 355555536 800000020 18 600000029 18
```
## 提示

### 样例解释 1

在第一个测试用例中，$p_3\equiv \frac{1}{9}\pmod {10^9+7}$。Bessie 有 $\frac{1}{9}$ 的概率在岛 $3$ 结束（经过路径 $1\to 3$），$\frac{8}{9}$ 的概率在岛 $2$ 结束（经过路径 $1\to 3\to 2$）。

在第二个测试用例中，$p_1\equiv \frac{1}{2}\pmod {10^9+7}$。Bessie 有 $\frac{1}{2}$ 的概率在岛 $1$ 结束，各 $\frac{1}{6}$ 的概率在岛 $2$ 和 $3$ 结束，各 $\frac{1}{12}$ 的概率在岛 $4$ 和岛 $6$ 结束。

### 样例解释 2

在第一个测试用例中，$p_1\equiv p_2\equiv \frac{1}{3}\pmod {10^9+7}$。Bessie 有 $\frac{7}{9}$ 的概率在岛 $1$ 结束（经过路径 $1$，$1\to 2\to 3\to 4\to 5\to 1$ 与 $1\to 5\to 4\to 3\to 2\to 1$ 之一），$\frac{2}{9}$ 的概率在岛 $2$ 结束。

在第二个测试用例中，Bessie 有 $\frac{1}{3}$ 的概率在岛 $3$ 结束，$\frac{2}{3}$ 的概率在岛 $5$ 结束。

### 测试点性质

- 测试点 $4-5$：$N\le 11$。
- 测试点 $6-7$：不存在简单环。
- 测试点 $8-11$：没有一座岛处在多于一个简单环上。
- 测试点 $12-15$：没有一座岛处在多于 $5$ 个简单环上。
- 测试点 $16-19$：没有一座岛处在多于 $50$ 个简单环上。
- 测试点 $20-23$：没有额外限制。


---

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
title: "[省选联考 2025] 岁月"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11834
tag: ['各省省选', '2025', '组合数学', '概率论']
---
# [省选联考 2025] 岁月
## 题目背景

> 希望大家一直记得我。  
> “希望大家永远忘了我。”
## 题目描述

小 Y 有一个 $n$ 个节点、$m$ 条边的带权**无向图** $G$，节点由 1 至 $n$ 编号。第 $i$ ($1 \leq i \leq m$) 条边连接 $u_i$ 和 $v_i$，边权为 $w_i$。保证 $G$ 连通且没有重边自环。

小 Y 预见到岁月将会磨灭图 $G$ 的痕迹，而这会导致一些边变成有向边，另一些边直接消失。具体地，图 $G$ 历经岁月将会磨损为 $n$ 个节点的带权**有向图** $G'$，其中对于第 $i$ ($1 \leq i \leq m$) 条边，$G'$ 上
- 有 $\frac{1}{4}$ 的概率同时存在 $u_i$ 向 $v_i$ 和 $v_i$ 向 $u_i$ 的有向边，它们的边权均为 $w_i$;
- 有 $\frac{1}{4}$ 的概率存在 $v_i$ 向 $u_i$、边权为 $w_i$ 的有向边，而不存在其反向边;
- 有 $\frac{1}{4}$ 的概率存在 $u_i$ 向 $v_i$、边权为 $w_i$ 的有向边，而不存在其反向边;
- 有 $\frac{1}{4}$ 的概率 $u_i$ 和 $v_i$ 之间没有边。

所有 $m$ 个随机事件是独立的。

小 Y 认为一个无向图的核心是最小生成树，而一个有向图的核心是最小外向生成树。称图 $G'$ 的一个边子集 $E$ 是**外向生成树**，当且仅当 $|E| = n - 1$ 且存在一个节点 $x$ 可以只经过 $E$ 中的有向边到达图 $G'$ 上的所有节点。图 $G'$ 的**最小外向生成树**即为图 $G'$ 上边权和最小的外向生成树。

小 Y 希望图的核心历经岁月侵蚀也保持不变，于是他想知道，有多大的概率，图 $G'$ 的最小外向生成树存在，且其边权和等于图 $G$ 的最小生成树边权和。

你需要将答案对 $(10^9 + 7)$ 取模。可以证明答案一定为有理数 $\frac{a}{b}$，其中 $a$ 和 $b$ 互质，且 $b$ 不是 $(10^9 + 7)$ 的倍数。因此你输出的数 $x$ 需要满足 $0 \leq x < 10^9 + 7$ 且 $a \equiv bx \pmod{10^9 + 7}$，可以证明这样的 $x$ 唯一存在。

## 输入格式

**本题有多组测试数据**。输入的第一行两个整数 $c, T$，分别表示测试点编号和测试数据组数，接下来输入每组测试数据。样例满足 $c = 0$。

对于每组测试数据，第一行两个整数 $n, m$，分别表示图 $G$ 的点数和边数，接下来 $m$ 行，第 $i$ ($1 \leq i \leq m$) 行三个整数 $u_i, v_i, w_i$，描述图 $G$ 上的一条边。
## 输出格式

对于每组测试数据，输出一行一个整数，表示图 $G'$ 的最小外向生成树存在且其边权和等于图 $G$ 的最小生成树边权和的概率，对 $(10^9 + 7)$ 取模。
## 样例

### 样例输入 #1
```
0 2
2 1
1 2 1
3 3
1 2 2
1 3 2
2 3 2
```
### 样例输出 #1
```
750000006
171875002
```
## 提示

**【样例 1 解释】**

该组样例共有 2 组测试数据。
- 对于第一组测试数据，由于图上只有一条边，因此只要 $G'$ 上有边，$G'$ 的最小外向生成树边权和就一定等于 $G$ 的最小生成树边权和。$G'$ 上存在边的概率为 $\frac{3}{4}$，故答案为 $\frac{3}{4}$，取模后的结果为 $750\,000\,006$。
- 对于第二组测试数据，在所有 $2^{2m} = 64$ 种 $G'$ 中，有 13 种情况不满足 $G'$ 的最小外向生成树边权和等于 $G$ 的最小生成树边权和：
  - $G'$ 为空图;
  - $G'$ 仅包含一条有向边，共 6 种情况;
  - $G'$ 仅包含两条有向边，且指向同一个节点，共 3 种情况;
  - $G'$ 仅包含两条有向边，且构成一个二元环，共 3 种情况。

由于所有情况等概率出现，因此答案为 $1 - \frac{13}{64} = \frac{51}{64}$，取模后的结果为 $171\,875\,002$。

**【样例 2】**

见选手目录下的 `years/years2.in` 与 `years/years2.ans`。

该组样例共有 5 组测试数据。其中每组测试数据分别满足测试点 $1 \sim 3$、$4 \sim 6$、$7,8$、$9 \sim 11$、$12,13$ 的限制。

**【样例 3】**

见选手目录下的 `years/years3.in` 与 `years/years3.ans`。

该组样例共有 5 组测试数据。其中每组测试数据分别满足测试点 $14 \sim 16$、$17, 18$、$19, 20$、$21 \sim 23$、$24, 25$ 的限制。

**【子任务】**

对于所有测试点，
- $1 \leq T \leq 5$,
- $2 \leq n \leq 15$, $n - 1 \leq m \leq \frac{n(n-1)}{2}$,
- $\forall 1 \leq i \leq m$, $1 \leq u_i < v_i \leq n$, $1 \leq w_i \leq m$,
- $\forall 1 \leq i < j \leq m$, $(u_i, v_i) \neq (u_j, v_j)$，即 $G$ 没有重边，
- 保证 $G$ 连通。

| 测试点编号 | $n \leq$ | 特殊性质 |
|:------------:|:------------:|:----------:|
| $1 \sim 3$      | $6$          | A        |
| $4 \sim 6$      | $15$         | B        |
| $7, 8$       | $9$          | C         |
| $9 \sim 11$     | $12$         | C         |
| $12, 13$     | $14$         | C         |
| $14 \sim 16$    | $15$         | C         |
| $17, 18$     | $9$          | 无       |
| $19, 20$     | $12$         | 无       |
| $21 \sim 23$    | $14$         | 无       |
| $24, 25$     | $15$         | 无       |

- 特殊性质 A：$m \leq 6$, $\forall 1 \leq i \leq m$, $w_i \leq 2$。
- 特殊性质 B：$\forall 1 \leq i < j \leq m$, $w_i \neq w_j$。
- 特殊性质 C：$\forall 1 \leq i \leq m$, $w_i = 1$。


---

---
title: "[NERC 2020 Online] Hit the Hay"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12857
tag: ['2020', 'Special Judge', '概率论', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020 Online] Hit the Hay
## 题目描述

Some consider putting a baby to sleep to be an art, but this problem will show it is all just maths.

Consider a night during which a parent is trying to put a baby to sleep. An alarm clock will sound at the end of the night, and the parent is not allowed to change the alarm time, so the length of the night is fixed at $k$ hours from now.

The baby can be in one of the three states: state 0 means the baby is awake, state 1 means the baby is in light sleep, and state 2 means the baby is in deep sleep. The baby starts in state 0, and the change in a state happens continuously rather than discretely. You are given three numbers $p_0$, $p_1$, and $p_2$. Whenever the baby is in state $i$, the probability that no state change will happen in the next $x$ hours is $p_i^x$, where $x$ is a positive real number. In other words, the time before the next state change is picked from the $\emph{exponential distribution}$ with the cumulative distribution function of $1-p_i^x$.

Whenever a state change does happen, if the baby was in state 0, it will always switch to state 1; if the baby was in state 2, it will also always switch to state 1; if the baby was in state 1, it will switch to state 0 with the probability $q_0$ and to state 2 with the probability $1-q_0$.

The parent decides when to go to sleep themselves. However, if the baby is in state 0, it will cry and wake the parent up, so the parent can only be asleep if the baby is in state 1 or 2. The parent can choose to still stay awake even if the baby is in one of those states. If they do stay awake, they can:
- see which of the three states the baby is in;
- prevent the baby from waking up: if the baby decides to switch from state 1 to state 0 according to the above rules, and the parent is not asleep, then the baby will be comforted and will stay in state~1 instead.

The parent can decide to go to sleep arbitrarily, for example using the current state of the baby or the current time to make this decision. However, if they do go to sleep, then they will be asleep until either the baby wakes up (goes to state 0), or the alarm clock sounds at the end of the $k$ hours. If they get woken up by the baby waking up, then they can later decide to go to sleep again arbitrarily.

What is the maximum expected number of hours of sleep the parent can get if they decide to go to sleep in the optimal fashion?
## 输入格式

The first line of the input contains an integer $t$ ($1 \le t \le 1000$) --- the number of test cases.

The next $t$ lines describe test cases, each contains five floating-point numbers with exactly $\emph{one}$ digit after the decimal point, in the following order: $k$, $p_0$, $p_1$, $p_2$, $q_0$ ($0.1 \le k \le 10$; $0.1 \le p_0, p_1, p_2, q_0 \le 0.9$).
## 输出格式

Output $t$ lines with a floating-point number on each line --- the maximum expected amount of sleep for each test case. Your outputs will be considered correct if they are within $10^{-9}$ absolute difference from the answers.
## 样例

### 样例输入 #1
```
2
10.0 0.5 0.5 0.5 0.5
8.0 0.1 0.9 0.9 0.1
```
### 样例输出 #1
```
6.5990202123649855
7.540407031059442
```


---

---
title: "[GCJ 2017 #1C] Core Training"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13170
tag: ['动态规划 DP', '2017', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2017 #1C] Core Training
## 题目描述

Writing Code Jam problems is hard, so we have built an AI to come up with new ideas. To make the AI as creative as possible, we have given it $N$ different "cores", each of which has its own "personality". However, just like people, these cores may become distracted or corrupt or may refuse to work; the i-th core has a success probability $P_i$ of functioning properly. As long as at least $K$ of the cores function properly, the AI will function properly. Otherwise, it will probably become evil and trap us in a maze of fiendish puzzles of its own design. And who knows what it might do to Code Jam — it might just write a bunch of tough probability problems!

To prevent this from happening, we plan to train one or more of the cores to become more reliable. We have a total of $U$ "training units" that we can use to improve the cores. Spending $X$ units on the i-th core will add $X$ to its success probability. We can divide up the units among the cores however we like, and it is possible that one or more cores may not receive any units. Of course, a core's success probability cannot be increased above 1.

If we assign the training units to maximize the probability that the AI will function properly, what is that probability?

~~**Solving this problem**~~

~~This problem has 2 Small datasets and no Large dataset. You must solve the first Small dataset before you can attempt the second Small dataset. You will be able to retry either of the datasets (with a time penalty).~~
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow; each consists of three lines. The first line contains two integers $N$ and $K$: the total number of cores, and the minimum number of cores that must succeed for the AI to function properly. The second line contains one rational $U$: the number of training units. The third line contains $N$ rational numbers $P_i$; the i-th of these gives the probability that the i-th core will function properly. All of these probabilities are specified to exactly four decimal places of precision.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the probability that the AI will function properly if the training units are assigned optimally. $y$ will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer.
## 样例

### 样例输入 #1
```
4
4 4
1.4000
0.5000 0.7000 0.8000 0.6000
2 2
1.0000
0.0000 0.0000
2 1
0.0000
0.9000 0.8000
2 1
0.1000
0.4000 0.5000
```
### 样例输出 #1
```
Case #1: 1.000000
Case #2: 0.250000
Case #3: 0.980000
Case #4: 0.760000
```
## 提示

**Sample Explanation**

Note that the last two sample cases would not appear in Small dataset 1.

In Sample Case #1, we have enough training units to spend to give all cores a success probability of 1, so the AI will certainly function properly.

In Sample Case #2, both of the cores must function properly for the AI to function properly, so we must give each core at least some training units. The best option turns out to be to train each one up to $0.5$. Then the probability that the AI functions properly is $0.5 \times 0.5 = 0.25$. Any other assignment is inferior; for instance, if we train one core to $0.9$ and the other core to $0.1$, the probability of success is only $0.9 \times 0.1 = 0.09$.

In Sample Case #3, we have no training units to spend, and at least one of the two cores must function properly for the AI to function properly. We can approach this by first calculating the probability that the AI does not function properly, which happens only if both cores fail to function properly. The probability that both cores fail is $(1 - 0.9) \times (1 - 0.8) = 0.02$. So the probability that at least one core functions properly, and thus that the AI functions properly, is $1 - 0.02 = 0.98$.

In Sample Case #4, the optimal strategy is to give all the training units to the second core. That makes the probability of at least one core functioning properly $1 - (0.4 \times 0.6) = 0.76$. All other options are inferior; for example, giving all the training units to the first core only yields $0.75$, and dividing them equally among the cores gives $0.7525$.

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq N \leq 50$.
- For all $i$, $0.0000 \leq P_i \leq 1.0000$.
- $0.0000 \leq U \leq N - \sum P_i$. (There will not be more training units than can be used.)

**Small dataset 1 (15 Pts, Test Set 1 - Visible)**

- Time limit: ~~20~~ 5 seconds.
- $K = N$. (All of the cores must function properly for the AI to function properly.)

**Small dataset 2 (28 Pts, Test Set 2 - Visible)**

- Time limit: ~~40~~ 10 seconds.
- $1 \leq K \leq N$.


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
title: "[JSOI2018] 防御网络"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4517
tag: ['2018', '各省省选', '江苏', '枚举', '前缀和', '概率论']
---
# [JSOI2018] 防御网络
## 题目描述

虽然成功得到了外星人的进攻计划，但 ``JYY`` 意外地发现,外星母舰对地球的攻击竟然是随机的！必须尽快在地球上部署防御网络,抵御外星人母舰的攻击。
地球上的防御网络由节点和节点之间的能量连接组成,防御网络可以看成是一个 $n$ 个点、 $m$ 条边的简单无向图 $G(V,E)$ ,每个防御节点对应 $V$ 中的一个节点、每个能量连接对应 $E$ 中的一条边。此外,在防御网络修建时考虑到能量传输效率，防御网络 $G$ 中**每个节点至多只包含在一个简单环中**。

外星母舰的攻击是随机的，每次攻击开始后， ``JYY`` 都会本次攻击的情况选择一些防御节点 $S\subseteq V$ ，并且用能量连接将这些防御节点连通，从而启动一个防御子网络。换言之， ``JYY`` 会选择 $G$ 中边集的一个子集 $H(S)\subseteq E$ ,它满足:

1.    (防御子网络**连通**) 如果我们建立新图 $G'(V,H(S))$ ，即用 $H(S)$ 中的边连接 $G$ 中的节点，则对于任意选择的防御节点 $x,y\in S$ ，它们在 $G'$​​ 中都连通。

2.    (防御子网络**最小**) 在满足条件 1 (防御子网络连通)的前提，选取的边数最小，即 $\vert H(S)\vert$ 最小。

$H(S)$ 是点集 $S$ 在图 $G$ 生成的斯坦纳树 (Steiner Tree) ，而 $\vert H(S)\vert$ 则是启动防御子网络的最小代价。考虑到外星母舰随机攻击的方式， ``JYY`` 希望你计算启动防御子网络代价的**期望**:

$$\frac{1}{2^{\vert V\vert}}\sum_{S\subseteq V}\vert H(S)\vert$$
## 输入格式

输入第一行两个整数 $n,m$ ，分别表示图中的节点数和边数。

接下来 $m$ 行,每行两个整数 $u,v(1\le u,v\le n)$ ，表示图中的一条边。输入保证没有自环和重边，并且满足每个节点至多包含在一个简单环中。
## 输出格式

输出一行，表示启动防御子网络的期望。

假设期望写成最简分式 $P/Q$ 的形式, 则输出 $P⋅Q^{-1} \text{mod 1,000,000,007}$ 的余数,其中 $Q^{-1}$​​ 为唯一的满足 $Q⋅Q^{-1} ≡ \text{1 (mod 1,000,000,007)}$ 的整数。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
```
### 样例输出 #1
```
750000006
```
### 样例输入 #2
```
6 6
1 2
2 3
3 1
1 4
2 5
3 6
```
### 样例输出 #2
```
468750006
```
## 提示

**样例解释**

样例输入 1 是一条链，包含以下情况:

1.    $\{\}, \{1\}, \{2\}, \{3\},\vert H(S)\vert = 0$ ;
2.    $\{1, 2\}, \{2, 3\}, \vert H(S)\vert = 1$ ;
3.    $\{1, 3\}, \{1, 2, 3\}, \vert H(S)\vert = 2$ 。

因此 $P/Q=3/4$ ， $P\cdot Q^{-1} = 750,000,006$ 。

样例输入 2 中 $\sum_{S\subseteq V}\vert H(S)\vert = 174$ ，因此 $P/Q=87/32$ ， $P⋅Q^{-1}=468,750,006 \text{ mod 1,000,000,007}$ 。

**数据范围**

对于 $20\%$ 的数据,有 $1\le n\le 8$ 。

对于 $40\%$ 的数据,有 $1\le n\le 20$ 。

对于 $100\%$ 的数据,有 $1\le n\le 200$ 。


---

---
title: "[_-0 C] 猜数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9477
tag: ['交互题', 'Special Judge', 'O2优化', '信息论', '概率论', '条件概率']
---
# [_-0 C] 猜数
## 题目背景

小 $\mathfrak{f}$ 和小 $\mathfrak{g}$ 在玩猜数游戏，但是因为风声太大，他们听不清楚对方说的话……
## 题目描述

评测机在区间 $[1,n]$ 中等概率随机地选择一个整数 $x$，你的任务是猜测这个数。

你可以每次给出一个 $[1,n]$ 中的整数 $y$，询问 $y$ 和 $x$ 的大小关系。你最多可以询问 $q$ 次。

但是，由于某些原因，评测机有 $p\%$ 的概率会出错。

具体地说：

- 如果 $y=x$，那么评测机返回 `=`。
- 如果 $y\ne x$，且当前已经是第 $q$ 次询问，那么评测机返回 `!`。
- **得到以上两种结果后，你应当停止询问。**
- 如果 $y>x$，那么评测机有 $(100-p)\%$ 的概率返回 `>`，有 $p\%$ 的概率返回 `<`。
- 如果 $y<x$，那么评测机有 $(100-p)\%$ 的概率返回 `<`，有 $p\%$ 的概率返回 `>`。

每次询问，你需要向**标准输出**输出一个 $[1,n]$ 中的整数，**然后清空缓冲区**。

你可以使用如下语句来清空缓冲区：

- 对于 C/C++：`fflush(stdout)`；
- 对于 C++：`std::cout << std::flush`；
- 对于 Java：`System.out.flush()`；
- 对于 Python：`stdout.flush()`；
- 对于 Pascal：`flush(output)`；
- 对于其他语言，请自行查阅对应语言的帮助文档。

特别的，对于 C++ 语言，在输出换行时如果你使用 `std::endl` 而不是 `'\n'`，也可以自动刷新缓冲区。

然后你需要从**标准输入**中输入一个字符，代表评测机返回的结果。
## 输入格式

开始询问之前，一行，三个用空格分隔的整数 $n,p,q$。

对于每一次询问，一行，一个字符，一定是 `=`，`!`，`>`，`<` 四者之一。
## 输出格式

对于每一次询问，一行，一个 $[1,n]$ 中的整数。
## 样例

### 样例输入 #1
```
100 0 10

>

<

=
```
### 样例输出 #1
```

50

25

37
```
### 样例输入 #2
```
100 10 10

<

<

=
```
### 样例输出 #2
```

50

25

37
```
### 样例输入 #3
```
100 0 2

>

!
```
### 样例输出 #3
```

50

25
```
## 提示

**样例 $1$ 解释：**

此时该测试点的状态为 `AC`。

**样例 $2$ 解释：**

$x=37,y=50$ 时，$y>x$，有 $10\%$ 的概率输出 `<`，恰好输出了 `<`。

**样例 $3$ 解释：**

此时该测试点的状态为 `WA`。

**本题采用捆绑测试。**

每个 Subtask 下设有 $5$ 个测试点，你只需通过其中**至少 $3$ 个**测试点即可得到该 Subtask 对应的分数。

本题不使用子任务依赖。

对于所有数据，$n=10^{18}$。

| 编号 | 分值 | $p=$ | $q=$ | 时限 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $5$ | $0$ | $60$ | $\texttt{1s}$ |
| $1$ | $10$ | $10$ | $500$ | $\texttt{1s}$ |
| $2$ | $10$ | $25$ | $2000$ | $\texttt{1s}$ |
| $3$ | $15$ | $25$ | $1000$ | $\texttt{1s}$ |
| $4$ | $20$ | $25$ | $700$ | $\texttt{1s}$ |
| $5$ | $10$ | $25$ | $400$ | $\texttt{1s}$ |
| $6$ | $10$ | $40$ | $2500$ | $\texttt{1s}$ |
| $7$ | $10$ | $45$ | $10000$ | $\texttt{1s}$ |
| $8$ | $5$ | $48$ | $62500$ | $\texttt{3s}$ |
| $9$ | $5$ | $49$ | $250000$ | $\texttt{10s}$ |


---

