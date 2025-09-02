---
title: "洞察（Insight）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10324
tag: ['数学', '洛谷原创', 'O2优化', '组合数学', '生成函数', '拉格朗日反演', '洛谷比赛']
---
# 洞察（Insight）
## 题目背景

看待万物毫无偏见的新视角 —— 洞察。

****
「洞察之光」凯伊·雅思·德·布拉德，是减法盗贼，也是背负黑暗命运的混沌骑士。

凯伊的右手内隐藏着混沌之剑，为了使其发挥出足够的力量又不至于失控，需要满足特定的内部结构。她想知道有多少种符合条件的结构，为了方便你的计算，她把问题转化为如下形式：
## 题目描述

赛时更新：题面中的笔误已修改为：相邻点对颜色**互不相同**。
****
在一个**无向连通图** $G$ 中，有黑色和白色的点各 $n$ 个，红色的点 $1$ 个。  
所有点都有标号，图中有 $2n$ 条边，且所有相邻点对（也就是有边直接相连的点对）的颜色也互不相同。

对于 $\text{type}$ 等于 $0$ 或 $1$，分别在不同条件下计算符合条件的图 $G$ 有多少个：

- $\text{type}=0$：无附加条件。  
- $\text{type}=1$：对于每个**不包含**红色点的极大连通子图，都要对**恰好一个**点做特殊标记（每个标记也都是不同的）。

答案对 $998244353$ 取模。
## 输入格式

输入一行两个整数 $n$ 和 $\text{type}$。

## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
1 1
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
2 0
```
### 样例输出 #2
```
45
```
### 样例输入 #3
```
2 1
```
### 样例输出 #3
```
149
```
### 样例输入 #4
```
10 0
```
### 样例输出 #4
```
36011666
```
### 样例输入 #5
```
20 1
```
### 样例输出 #5
```
593465999
```
### 样例输入 #6
```
106 1
```
### 样例输出 #6
```
516553582
```
## 提示

【样例 $1$ 解释】  
此时 $\text{type}=1$，所有 $5$ 种合法的图包括：

1. $R-W'-B$
2. $R-W-B'$
3. $R-B'-W$
4. $R-B-W'$
5. $B'-R-W'$

由于 $n=1$，可以仅用 $B$ 和 $W$ 来区分白点和黑点，$R$ 表示红点。中间的横杠表示连边，$B'$ 和 $W'$ 分别表示有标记的白点和黑点。

注意，由于第 $5$ 个图中，单个的 $B$ 和 $W$ 就是不包含 $R$ 的极大连通子图，必须各有一个标记在这唯一的位置上。

【样例 $2,3$ 解释】

见附件图片，其中展示了 $\text{type}=0$ 时全部的 $45$ 种可能的图 $G$。

对于 $\text{type}=1$ 的情况，只需要对每个图的基础上做标记，就可以数出答案为 $149$。

【样例 $4,5$ 解释】

取模前的答案分别为 $116758263583336861101$ 和 $4159784334433940020473603987503242886367209494283213841$。

【数据范围】

**本题采用捆绑测试。**

Subtask 1（8 pts）：$n \le4$；     
Subtask 2（10 pts）：$n \le 10^3$，$\text{type}=0$；  
Subtask 3（11 pts）：$\text{type}=0$；  
Subtask 4（13 pts）：$n \le 100$，$\text{type}=1$；     
Subtask 5（14 pts）：$n \le 10^3$，$\text{type}=1$；  
Subtask 6（21 pts）：$n\le 10^5$，$\text{type}=1$；  
Subtask 7（23 pts）：$\text{type}=1$。

对于全部的数据，$1\le n \le 10^7$，$\text{type}\in \{ 0,1\}$。

【提示】  
对于这类题目，你或许会想从 [OEIS](https://oeis.org/) 上寻找答案。但我要提醒你的是，直接搜索答案数列不会找到任何结果。然而，对于小数据范围，仍然可以提前处理出答案数列。



---

---
title: "自由（Freedom）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10326
tag: ['数学', '洛谷原创', '提交答案', '枚举', '组合数学', '生成函数', '线性代数', '洛谷比赛']
---
# 自由（Freedom）
## 题目背景

完全抽象的，只在数学中被允许的**无限**的「自由」。

****

「自由之光」，未知数的骑士 —— 知修。哪怕面对的是无限的绝望，他也能将其转变为无限的自由。
## 题目描述

给定一个 $n$ 个节点、$m$ 条边的**有向图**，节点和边都有权值，保证对于任意两个节点 $u,v$，从 $u$ 指向 $v$ 的边最多只有一条。

**路径** $P$ 是一个节点序列 $u_1,\cdots,u_k$，其中对于任意 $1\leq i < k$，$u_i$ 有指向 $u_{i+1}$ 的边（这条边记为 $e_i$）。则定义 $P$ 的**边权**是所有 $e_i$ 的权值的乘积，其**点权**是所有 $u_i$ 权值的和，其**长度**为 $k$。特别地，如果 $k=1$，则定义其**边权**为 $1$。

对于两条路径 $P_1,P_2$，长度分别为 $L_1,L_2$，包含的节点序列记为 $u_1,\cdots,u_{L_1}$ 和 $v_1,\cdots,v_{L_2}$。定义它们是**相同**的，当且仅当 $L_1=L_2$，且对于所有 $1\le i \le L_1$ 有 $u_i=v_i$。

给定正整数 $V$，请求出所有不相同的「**点权**为 $V$ 的路径」的**边权**之和。答案可能很大，请对 $998244353$ 取模后输出。

**题目的输入数据下载链接：[Link1](https://pan.baidu.com/s/1Gn0T5DNQBwC41oR-0hsh4A)，提取码：`92ih`；**   
备用下载路径与操作方法：[Link2](https://www.luogu.com.cn/paste/xkqpnptw)。
## 输入格式

第一行一个正整数 $T$，表示测试点编号。

第二行三个正整数 $n,m,V$，意义如题目描述。  
第三行 $n$ 个正整数 $a_1,\cdots,a_n$，$a_i$ 表示了编号为 $i$ 的节点的权值。  
接下来 $m$ 行，每行三个正整数 $u_i,v_i,w_i$，表示编号为 $u_i$ 的点有一条权值为 $w_i$ 的边指向 $v_i$。
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
0
3 5 12
2 4 6
2 3 5
1 2 3
3 1 7
3 2 11
1 1 2
```
### 样例输出 #1
```
155
```
## 提示

【样例 $1$ 解释】

样例中 $V=12$，满足点权为 $12$ 的路径有：   
（给出的是路径中节点的编号，样例中每个节点的权值恰好为其编号的两倍）

- $1 \to 1\to 1\to 1\to 1\to 1$，边权为 $2^5=32$。 
- $1\to 1\to 1\to 1 \to 2$，边权为 $3\times 2^3=24$。  
- $1\to 2 \to 3$，边权为 $3\times 5=15$。  
- $2\to 3\to 1$，边权为 $5\times 7=35$。  
- $3\to 1\to 1\to 1$，边权为 $7\times 2^2=28$。  
- $3\to 1\to 2$，边权为 $7\times 3=21$。

故答案为 $32+24+15+35+28+21=155$。

【数据信息】

| 测试点编号 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 测试点名称 | W | K\_1 | K\_2 | K\_3 | MP\_1 | MP\_2 | MP\_3 | MP\_4 | R | Finale |
| 测试点分数 | $10$ | $10$ | $10$ | $10$ | $10$ | $10$ | $10$ | $10$ | $10$ | $10$ |


对于全部的数据，$1\le n \le10^5$，$1\le m \le \min(n^2,10^6)$，$1\le V \le 10^{10000000}$。

【提示】   
**时间**是宝贵的。代码运行需要时间，你的思考也需要时间。好在这两件事可以同时进行，希望你可以在这有限的时间内做更多的事，拿到更好的成绩。


---

---
title: "「KDOI-07」能量场"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10881
tag: ['动态规划 DP', '2024', '洛谷原创', 'O2优化', '组合数学', '线性代数']
---
# 「KDOI-07」能量场
## 题目背景

4202 年，小 K 作为一名已经工作了 3143 天的 gaLaxy enGineer Master，在 XS41 星系的 OIPA115 星球上建立了据点，帮助人类探索未知。在这里，他建起了一些能量场。原本他决定使用一些卒来运输能量，然而在他操控的两个红色卒碰撞并损失所有能量后决定还是应该使用能量管道连接他们，~~并使能量管道呈 $(180+\mathrm{eps})^\circ$ 角~~。
## 题目描述

小 K 有 $n$ 个能量场，第 $i$ 个能量场存储 $a_i$ 点能量。

小 K 在能量场之间建立了 $n$ 条不同的双向能量管道，使得能量场两两连通。

对于一条能量管道，它的能量级为两端能量场能量之和。

小 K 对一组 $n$ 个不同能量管道集合的满意度是所有能量管道能量级的乘积。

现在小 K 想知道，对于所有不同的合法的搭建能量管道的方式，满意度的总和是多少。由于小 K 的满意度是一个 $[0,998244353)$ 之间的整数，所以你只需要输出满意度总和对 $998244353$ 取模后的值即可。

两种搭建管道的方式是不同的当且仅当存在至少一条管道连接能量场 $i,j$，且恰好在其中一种搭建管道的方式中出现。

---

**【形式化题意】**

有一个 $n$ 个点的完全图 $G(V,E)$。每个点有点权 $a_i$。$i,j$ 两点之间的边权 $w_{i,j}=a_i+a_j$。

定义一个连通子图 $G'(V,E')$ 使得 $E'\in E$ 的权值为 $\prod_{e\in E'}w_e$。注意，子图的点集是全集。

求 $G(V,E)$ 的连通子图中所有基环树的权值和，对 $998244353$ 取模。

基环树要求无重边无自环。
## 输入格式

第一行一个正整数 $n$，表示能量场数量。

第二行 $n$ 个非负整数 $a_i$，表示第 $i$ 个能量场存储的能量。
## 输出格式

一行，一个非负整数，表示对于所有不同搭建能量管道的方式，满意度的总和，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
60
```
### 样例输入 #2
```
4
1 2 3 4
```
### 样例输出 #2
```
8629
```
### 样例输入 #3
```
7
1 9 1 9 8 1 0
```
### 样例输出 #3
```
311816897
```
### 样例输入 #4
```
16
2 0 0 9 0 2 2 8 2 0 0 9 0 8 1 5
```
### 样例输出 #4
```
871736512
```
## 提示

### 样例解释 1

可能的基环树形态只有包含三个点的环，环边 $(1,2),(1,3),(2,3)$ 的边权分别是 $3,4,5$，乘积为 $60$。

### 数据规模与约定

**本题采用捆绑测试。**

| $\mathrm{Subtask}$ | $n\leq$ | 特殊性质 | 分数 |
|:--:|:--:|:--:|:--:|
| $1$ | $3$ |  | $1$ |
| $2$ | $7$ |  | $4$ |
| $3$ | $24$ | $\checkmark$ | $5$ |
| $4$ | $12$ |  | $10$ |
| $5$ | $18$ |  | $10$ |
| $6$ | $20$ |  | $5$ |
| $7$ | $23$ |  | $5$ |
| $8$ | $24$ |  | $30$ |
| $9$ | $50$ |  | $15$ |
| $10$ | $200$ |  | $5$ |
| $11$ | $500$ |  | $5$ |
| $12$ | $1000$ |  | $5$ |

特殊性质：保证 $\forall i\in[1,n],a_i=499122177$。

对于所有数据，保证 $3\leq n\leq 1000$，$0\leq a_i<998244353$。


---

---
title: "移言丁真：Unavoided linyue"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10896
tag: ['洛谷原创', '组合数学', 'Catalan 数']
---
# 移言丁真：Unavoided linyue
## 题目背景

**注：你不需要阅读此题题目背景。**

"$\textsf{linyue}$" 是我起过的唯一一个人名，所以 $\textsf{linyue}$ 成了唯一一个由我想象出来的角色。她是我脑海中所有故事的主角，对我而言非常地重要，以至于不知道为什么，每次我看到她的名字被写出来或是被读出来都会感到无所适从，所以我总是会想办法避免这样，比如说这个题的题面里我就用的是拼音作代替。

“跑团”这种游戏我最初了解的时候简直是“绝望地想要跟不管是谁玩随便什么”。可是疫情却让我的好多和同学玩的计划纷纷泡汤，所以我甚至走投无路到把它也纳入了计划的考虑范畴，不过由于它实在是太复杂了，没过多久我就把它抛诸脑后了（

“黑影杀”是一款在泞之翼官方交流群里兴起的游戏，玩家将会探索《泞之翼》原作的旅馆，躲避黑影以求逃出生天——对我而言没有比这更完美的事了！它完全实现了我上一段里的愿望，只要一有空，我便可以在群里“开鲨”！我给这个游戏准备了便于主持的程序，写了许多特殊规则，甚至还以它为背景出了题——尽管这题投到的比赛咕了（

《怪商一克拉》是一部我很喜欢的漫画。它的特点就是主角好像在每段故事里都只会最小程度地完成任务，然后哪怕这个故事还有好多未解之谜都只会跳到下一段故事。尽管这看起来像是没写好，但我相信这种效果作者是刻意为之。所以我期待着在未来看到这些故事的伏笔被精妙地解决，带来一个震撼的结局。可是有一天，我没有在漫画派对上看到这部漫画。这意味着以上就都不会发生了……我当时心态崩了好长时间，甚至都到泞之翼群里发癫了，不过事实上作者只是请了一个月假，接下来这漫画还会照常更新（

前两天，我终于又找到机会和同学出去玩了！这一次我们打算上一个主营镜土 TRPG 的店里试试跑团。要知道，这对我而言还是很有吸引力的，因为之前不管是玩什么，都是"我"在玩，跟 $\textsf{linyue}$ 没有什么关系。但要是玩跑团做角色卡的话，是不是就能填补这个遗憾了呢？所以这次我是有备而来！我提前十分费力地给 $\textsf{linyue}$ 画了一张简单的画，然后输入名字的时候，我决定不再回避——用她那两个汉字的真名，而非六个字母的替代。

然而，尽管我这一天听到和看到她名字的次数前所未有，但最后却并没什么很好的效果。我在游戏里确实是主打一个不入戏，对话内容有种全人类取平均的美，没推理出什么剧情的关键，也没想到什么新奇的点子。相信把我换成 Kimi AI 游戏绝对会更有趣……

——不过当然啦，这倒也在我意料之中，因为我知道我本来就非常非常不擅长这种角色扮演……看来对我而言，创造 $\textsf{linyue}$ 的故事会比别人更加困难。

所以我不会太受这个问题的困扰，一是因为习惯了，二是因为——我们出题组的比赛没过审。

![](https://cdn.luogu.com.cn/upload/image_hosting/7qwdep44.png)

“移言丁真”是这场比赛的原定 E 题之一，可是它被鉴定为了典……显然这最主要是我的锅。所以我现在的当务之急是要想一个新的 idea……
## 题目描述

定义一个括号串的权值为其中可配对的括号组数。也就是你重复地在里面删除掉某个为 ```()``` 的子串，最多可以删除的次数。

你会遇到 $m$ 个括号串，第 $i$ 个的长度是 $l_i$。你可以将它们按照任意顺序连接起来，然后连成一个长的括号串，而你的目标就是让最终的串的权值最小。

如果这 $m$ 个串是等概率随机生成的，而你的操作是最优的，请你求出最终权值的期望。也就是说你要对于初始括号串的所有可能性求出最小权值的和再除以 $2^n$，$n$ 为这些字符串的总长。对 $10^9+7$ 取模。
## 输入格式

第一行一个整数 $m$。

第二行 $m$ 个整数，表示 $l_1$ 到 $l_m$。
## 输出格式

一行一个整数表示答案，对 $10^9+7$ 取模。
## 样例

### 样例输入 #1
```
2
2 2
```
### 样例输出 #1
```
62500001
```
### 样例输入 #2
```
5
1 2 3 4 5
```
### 样例输出 #2
```
762695321
```
## 提示

**【样例解释1】**

这里 $\{S_1,S_2\}$ 表示两个括号串构成的无序可重集合，$P$ 表示取到这样集合的概率。

| $\{S_1,S_2\}$ | $P$ | 最优方案 | 权值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $\{$```((```$,$```((```$\}$ | $\frac{1}{16}$ | ```((((``` | $0$
| $\{$```((```$,$```()```$\}$ | $\frac{1}{8}$ | 任意 | $1$
| $\{$```((```$,$```)(```$\}$ | $\frac{1}{8}$ | ```)(((``` | $0$
| $\{$```((```$,$```))```$\}$ | $\frac{1}{8}$ | ```))((``` | $0$
| $\{$```()```$,$```()```$\}$ | $\frac{1}{16}$ | ```()()``` | $2$
| $\{$```()```$,$```)(```$\}$ | $\frac{1}{8}$ | 任意 | $1$
| $\{$```()```$,$```))```$\}$ | $\frac{1}{8}$ | 任意 | $1$
| $\{$```)(```$,$```)(```$\}$ | $\frac{1}{16}$ | ```)()(``` | $1$
| $\{$```)(```$,$```))```$\}$ | $\frac{1}{8}$ | ```)))(``` | $0$
| $\{$```))```$,$```))```$\}$ | $\frac{1}{16}$ | ```))))``` | $0$

最终答案为 $\dfrac{9}{16}$。

**【数据范围】**

令 $n$ 为 $l_i$ 的总和。

子任务 $1$（$20$ 分）: $n \le 20$。

子任务 $2$（$30$ 分）: $n \le 5000$。

子任务 $3$（$50$ 分）: $n \le 4000000$。

保证 $l_i \ge 1$。

**【后记】**

左括号和右括号可以是 $\textsf{linyue}$ 名字的第一个字和第二个字，也可以是一段故事的萌芽和结果。

下一次跑团遥遥无期，黑影杀渐渐无人问津，我们团的三个原定 E 题和其他好多好多的 idea 不知道何去何从，那些和 $\textsf{linyue}$ 有关的故事和设想更是也难以被呈现。有时我感觉自己就像是在《怪商一克拉》里一样，好多段经历都没等到自己的右括号，有种被最小化了权值的美。所以，我总是期待这些故事的伏笔被精妙地解决，带来最大的幸福。不过在这之前，我只好继续回避 “$\textsf{linyue}$” 了。


---

---
title: "【MX-X3-T7】「RiOI-4」Re：End of a Dream"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11040
tag: ['线段树', '平衡树', 'O2优化', '组合数学', '梦熊比赛']
---
# 【MX-X3-T7】「RiOI-4」Re：End of a Dream
## 题目背景

原题链接：<https://oier.team/problems/X3H>。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/dwohziu8.png)

（图片来自 phigros 曲绘，侵删。）

还是来谈点现实的吧。

身边的同学 NOI 拿了 Ag，APIO 捧了杯，省选啥的也比小 $\iiint$ 好。小 $\iiint$ 说，他的时间花在游戏上了。可看看隔壁提前招进高中的，florr 号里都有 Super Ant Egg 了。小 $\iiint$ 说，他网不好，实力发挥不出来。可再看隔壁 i wanna 大神，都开始速通 i wanna be the guy 了。小 $\iiint$ 争道，他也没打多久游戏，只是在专心文化课。但是成绩一拉出来，成了信竞班垫底。小 $\iiint$ 又说，可能是时间花在社交上了吧。大家都觉得他很幽默，因为他在班里一个朋友都没有。

小 $\iiint$ 不明白为什么会这样。

今年对于小 $\iiint$ 来说，可能就是他 OI 生涯的最后一年了。一年太短，能补救多少？能挽回多少？当年他刚学 OI 时，就暗暗地下定决心，要成为大家口中的“神犇”。三年过去，前途仍是一片昏暗。

这或许就是，$\color{#CD0000}\overset{\text{End of a Dream}}{\text{梦\ 的\ 终\ 结}}$。

也许，**梦是反着的吧。**

……

但是这里是梦熊周赛题目，不是出题人拿来写批话的地方，所以小 $\iiint$ 需要你做一道计数题。
## 题目描述

给定 $n,q$。现有一个初始为 $0$ 的整数 $m$。你需要支持以下操作：

- `0 x`：将 $m$ 加上 $2^x$。
- `1 x`：将 $m$ 减去 $2^x$。若 $m<2^x$，则忽略此操作。
- `2`：查询有多少长度为 $n$、每个数都在 $1\sim m$ 中的严格递增正整数序列，使得其前缀异或和与后缀异或和均严格递增。答案对 $998\,244\,353$ 取模。

其中，一个序列 $a_1,a_2,\cdots,a_n$ 的**前缀异或和**是指序列 $s_1,s_2,\cdots,s_n$，满足 $s_i=\begin{cases}a_1&i=1\\a_{i}\oplus s_{i-1}&i\ge2\end{cases}$，而其**后缀异或和**是指序列 $t_1,t_2,\cdots,t_n$，满足 $t_i=\begin{cases}a_n&i=1\\a_{n-i+1}\oplus t_{i-1}&i\ge2\end{cases}$，其中 $x\oplus y$ 表示 $x$ 与 $y$ 的按位异或。
## 输入格式

第一行两个正整数，表示 $n,q$。

接下来 $q$ 行，每行表示一个操作。
## 输出格式

对于每个 `2` 操作，输出对应的答案对 $998\,244\,353$ 取模的值。
## 样例

### 样例输入 #1
```
3 4
0 0
0 1
0 2
2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
20 15
0 1
0 2
0 21
0 5
2
0 15
1 18
0 7
0 8
0 25
2
1 22
0 12
0 13
2
```
### 样例输出 #2
```
313288290
39181640
134388812
```
## 提示

**【样例解释 #1】**

查询时 $m=7$，满足要求的序列为 $\{1,2,4\}$ 和 $\{1,3,5\}$，可以证明不存在其他解。

注意，序列 $\{1,3,1\}$ 是不满足要求的，尽管其前、后缀异或和均为严格递增数列 $\{1,2,3\}$，该序列本身并不满足严格递增的限制。

**【数据范围】**

**本题开启捆绑测试。**

|子任务|分数|$n\le$|$q\le$|$x\le$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$5$|$5$|$10$|$10$||
|$2$|$10$|$10^3$|$10^3$|$10^3$||
|$3$|$11$|$10^3$|$2\times10^5$|$10^5$|AB|
|$4$|$14$|$10^5$|$2\times10^5$|$10^5$|AB|
|$5$|$16$|$10^7$|$10^2$|$10^7$|B|
|$6$|$19$|$10^7$|$2\times10^5$|$10^7$|B|
|$7$|$25$|$10^7$|$2\times10^5$|$10^7$||

特殊性质 A：仅有最后一次操作为 `2` 操作。  
特殊性质 B：不包含 `1` 操作。

对于 $100\%$ 的数据，$3\le n\le 10^7$，$1\le q\le 2\times10^5$，$0\le x\le 10^7$。


---

---
title: "「CMOI R1」Looking For Edge Of Ground／City Planning"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11174
tag: ['数学', '2024', 'O2优化', '组合数学', '容斥原理', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT', '拉格朗日反演', '洛谷比赛']
---
# 「CMOI R1」Looking For Edge Of Ground／City Planning
## 题目背景

![](bilibili:BV1np4y19753)

[如何对 $n$ 个点的简单有标号无向连通图计数？](https://www.luogu.com.cn/problem/P4841)$\small\color{white}/42^{\text{nd}}\text{Problem by ArCu}.$

有一个显然错误的做法：枚举一棵树，然后在上面加边。

你需要求每张图被统计的次数的平方和。
## 题目描述

给定正整数 $n$。

一开始，$\text{ClBe}$ 会选定一棵 $n$ 个点的有标号无向无根树，将树上的边染成白色。然后他会在这棵树上加任意多条边，且满足：

* 新加的边是黑色的无向边；
* 加完边后的图忽略边的颜色后是一张简单图。

接下来 $\text{ClBe}$ 会将所有可能得到的结果放到一个集合 $S$ 中。

显然这种统计连通图个数的方法会把一个图算很多遍，所以 $\text{ClBe}$ 定义 $f(G)$：$S$ 中有 $f(G)$ 个图在忽略边的颜色后和 $G$ 相同（两个图 $A,B$ 相同指对于任意一条边 $(u,v)$，$(u,v)\in A\iff(u,v)\in B$）。

（$\sum_G$ 代表对所有可能的图 $G$ 求和。）显然

$$\sum_{G}f(G)=n^{n-2}2^\binom{n-1}2$$

所以你需要求

$$\sum_{G}f(G)^2$$

答案对 $998244353$ 取模。很可惜因为一些原因模数**不能**取 $1004535809$。
## 输入格式

一行一个正整数 $n(0<n<2^{25})$。
## 输出格式

一行一个整数，为你求得的答案。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
4
```
### 样例输出 #2
```
812
```
### 样例输入 #3
```
5
```
### 样例输出 #3
```
223440
```
### 样例输入 #4
```
107
```
### 样例输出 #4
```
404390093
```
## 提示

$\text{Sample Explanation}:$

集合 $S$ 中包含以下 $6$ 张图（边权为 $0$ 代表白边，为 $1$ 代表黑边，点的编号为 $1A$ 代表这是图 $A$ 的 $1$ 号点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/neuo34c3.png)

$3$ 个点的连通图有 $4$ 种：

![](https://cdn.luogu.com.cn/upload/image_hosting/q8kvdjgj.png)

忽略颜色后，

* 与 $G$ 相同的有 $B$；
* 与 $H$ 相同的有 $A$；
* 与 $I$ 相同的有 $C$；
* 与 $J$ 相同的有 $D,E,F$；

答案为 $f(G)^2+f(H)^2+f(I)^2+f(J)^2=1^2+1^2+1^2+3^2=12$。

$\text{Details of Subtasks}:$

本题采用捆绑测试。

| $\text{Subtask}$ | $n<$ | $\text{Score}$ |
| :----------: | :----------: | :----------: | 
| $1$ | $10$ | $5$ |
| $2$ | $500$ | $25$ |
| $3$ | $1500$ | $30$ |
| $4$ | $4500$ | $5$ |
| $5$ | $2^{16}$ | $5$ |
| $6$ | $2^{17}$ | $5$ |
| $7$ | $2^{20}$ | $20$ |
| $8$ | $2^{25}$ | $5$ |


---

---
title: "[PA 2016] 覆盖 / Pokrycia"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11613
tag: ['动态规划 DP', '2016', '组合数学', '生成函数', 'Lucas 定理', 'PA（波兰）']
---
# [PA 2016] 覆盖 / Pokrycia
## 题目背景

译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R5 Pokrycia [A] (POK)。

## 题目描述


简单无向图 $G=(V,E)$ 的**点覆盖**是一个点集 $S\subseteq V$，使得 $\forall (u,v)\in E$，都有 $u\in S$ 或 $v\in S$。点覆盖 $S$ 的**大小**定义为 $|S|$。

给定点集 $V$ 和整数 $k$，求出有多少张以 $V$ 为点集的简单无向图 $G$ 的最小点覆盖大小为 $k$。

两张图 $G_1=(V,E_1)$ 和 $G_2=(V,E_2)$ 不同，当且仅当存在 $u,v\in V$，使得 $(u,v)$ 只属于 $E_1$ 或 $E_2$。

给定正整数 $n$，点集 $V=\{1,2,\ldots,n\}$。

由于答案可能很大，所以只需要输出答案模 $\textcolor{red}{\textbf{2}}$ 后的余数。
## 输入格式


**本题单个测试点内有多组测试数据。**

第一行一个正整数 $T$，表示测试数据组数。

接下来描述 $T$ 组测试数据：

每组测试数据只有一行两个整数 $n,k$，表示一次询问。$V=\{1,2,\ldots,n\}$。

## 输出格式


输出 $T$ 行，每行一个非负整数，表示答案模 $\textcolor{red}{\textbf{2}}$ 后的余数。
## 样例

### 样例输入 #1
```
4
3 1
5 4
5 3
57 32
```
### 样例输出 #1
```
0
1
1
1
```
## 提示



#### 样例解释

- 第一组测试数据中，$n=3,k=1$。符合条件的图要么只有一条边，要么有两条边，且这两条边共用一个顶点。不难验证，原始答案为 $6$。
- 第二组测试数据中，$n=5,k=4$。不难验证符合条件的图只有完全图。


#### 数据范围


- $1\le T\le 2^{14}$；
- $1\le n\lt 2^{14}$；
- $0\le k\lt n$。


---

---
title: "[PA 2019 Final] 数图 / Grafy 加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11821
tag: ['递推', '2019', '生成树', '组合数学', '容斥原理', '高斯消元', 'PA（波兰）']
---
# [PA 2019 Final] 数图 / Grafy 加强版
## 题目背景

P11817 的加强版。本题存在 $\Theta(\sqrt n\log n)$ 的做法。

本题数据为自造。

std: joke3579，validator & generator: Starrykiller。

**请勿提交 OEIS 题解。**


## 题目描述

求出 $n$ 个节点的满足以下条件的**有标号有向简单图**的数量：

- $\forall 1\le i\le n$，$\operatorname{deg_{out}}(i)=\operatorname{deg_{in}}(i)=2$。

这里，$\operatorname{deg_{out}}(u)$ 指节点 $u$ 的出度，$\operatorname{deg_{in}}(u)$ 指节点 $u$ 的入度。

你只需要输出答案对给定大素数 $p$ 取模后的结果。


注意我们是对**有标号**的「有向简单图」计数。也就是说，这张图中无重边自环。注意 $u\to v$ 和 $v\to u$ 同时出现是允许的。



## 输入格式

一行两个正整数 $n,p$。
## 输出格式

一行一个非负整数，表示答案。
## 样例

### 样例输入 #1
```
4 998244853
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
114514 1000000007

```
### 样例输出 #2
```
637348702

```
## 提示

- $3\le n\le 10^7$；
- $10^8+7\le p\le 10^9+7$，$p$ 为素数。




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
title: "[Math×Girl] 染色"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12471
tag: ['O2优化', '组合数学', '容斥原理']
---
# [Math×Girl] 染色
## 题目背景

>“等下，米尔嘉，你是什么时候拿到这道题的啊？”我问道。  
>“是中午我去老师办公室的时候，你现在就在这里从零开始思考吧。我到那边去想，再见。”米尔嘉朝我挥挥手，优雅的移到窗边的座位上。我的目光紧紧的追随着米尔嘉，透过窗户，我可以看到凋零的梧桐树，梧桐树的上面是广阔的冬季的蓝天，虽然是个晴天，但是外面看上去还是很冷。
## 题目描述

现在有一张 $a\times a$ 的网格，每个格子只能是黑色或白色。  
请问：对于其中每个 $b\times b$ 的网格，都恰好有 $n$ 个格子是黑色的颜色分布方案有几种？  
_为了不让题目太难，米尔嘉只需要你解决 $n\in\{1,2\}$ 的情况即可。_  

由于答案可能很大，你只需要输出方案数对 $998244353$ 取模后的结果就可以了。  
## 输入格式

本题有多组数据，第一行输入一个整数 $T$，表示数据组数。  

对于每一组询问，我们给出 $a,b,n$。 
## 输出格式

对于每组数据，一行输出一个数表示取模后的方案数。 
## 样例

### 样例输入 #1
```
8
3 2 1
10 3 1
100 3 1
1145141919810 23333333 1
3 2 2
10 3 2
100 3 2
1145141919810 23333333 2
```
### 样例输出 #1
```
8
261
792303199
491969808
14
16316
968654202
961966479
```
## 提示

### 样例解释

第一个例子中的 $8$ 种方案分别是：

![样例解释1](https://cdn.luogu.com.cn/upload/image_hosting/b2jppnoc.png)

第三个例子取模前的结果是：$55590605665555221$

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $5$ | $a\in[1,5]$ |
| $1$ | $15$ | $T=10,\text{答案}\in[1,10^6]$ |
| $2$ | $15$ | $T=10,b\le a\le2b\le10^3$ |
| $3$ | $10$ | $n=1,b\mid a$ |
| $4$ | $15$ | $n=1$ |
| $5$ | $15$ | $n=2,b\mid a$ |
| $6$ | $25$ | $n=2$ |

对于 $100\%$ 数据，保证 $T\in[1,10^5],n\in\{1,2\},1\le n\le b^2\le a^2\le (10^{18})^2$。  


---

---
title: "[GCJ 2022 #1C] Intranets"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12992
tag: ['2022', '组合数学', 'Google Code Jam']
---
# [GCJ 2022 #1C] Intranets
## 题目描述

Apricot Rules LLC is developing a new simplified networking protocol and wants to show off their routing algorithm. In their design, a network consists of $\mathbf{M}$ machines numbered from 1 to $\mathbf{M}$, and each pair of machines is connected by a direct link. Each of the links is given a unique integer priority value between 1 and $(\mathbf{M} \times (\mathbf{M} - 1)/2)$ and each machine routes traffic according to those priorities.

Unfortunately, the routing algorithm is too aggressive and will route all traffic from a machine through the highest priority link connected to it. This may make some groups of machines isolated from others.

Formally, we say that a machine $m$ uses a link $\ell$ if (and only if) $\ell$ is the highest priority link connected to $m$. We also say that a link is active if it is used by at least one of the two machines it connects. Given the link priorities, the original network becomes partitioned into disjoint intranets. Two machines belong to the same intranet if and only if there is some path between them using only active links.

![](https://cdn.luogu.com.cn/upload/image_hosting/hi8p2brt.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/aiu45d35.png)

For example, as seen in the left image above, only the links with priorities 6 and 5 are active. This creates two disjoint intranets. However, in the example on the right, three links are active, which results in one intranet consisting of all 4 machines.

As part of the quality assurance team at Apricot Rules LLC, you are investigating the extent of the problem. You are interested in knowing the probability of there being exactly $\mathbf{K}$ intranets if the priorities are assigned uniformly at random from among the $(\mathbf{M} \times (\mathbf{M} - 1)/2)!$ ways of doing so.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case is described in a single line containing two integers $\mathbf{M}$ and $\mathbf{K}$ : the number of machines and the target number of intranets, respectively.
## 输出格式

For each test case, output one line containing Case # $x: y$, where $x$ is the test case number (starting from 1) and $y$ is the sought probability computed modulo the prime $10^{9}+7$ ($1000000007$), which is defined precisely as follows. Represent the probability as as an irreducible fraction $p / q$ (with $p$ and $q$ being non-negative integers that minimize $p+q$ ). Then, $y$ must equal $p \cdot q^{-1} \bmod 10^{9}+7$, where $q^{-1}$ is the modular multiplicative inverse of $q$ with respect to the modulus $10^{9}+7$. It can be shown that under the constraints of this problem, such a number $y$ always exists and is unique.
## 样例

### 样例输入 #1
```
3
5 2
5 1
6 3
```
### 样例输出 #1
```
Case #1: 428571432
Case #2: 571428576
Case #3: 47619048
```
## 提示

**Sample Explanation**

In Sample Case #1, consider the following situation. Let's call $\mathbf{M}=5$ machines $1,2,3,4,5$ and denote the link connecting machine $a$ and machine $b$ by $(a, b)$. Assume that the priorities of links $(1,2),(1,3),(1,4),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5)$ are $9,8,7,6,5,4,3,2,1,10$, respectively. Then machines 1 and 2 use link $(1,2)$, machine 3 uses link $(1,3)$, and machines 4 and 5 use link $(4,5)$. Thus three links $(1,2),(1,3),(4,5)$ are active, and there are two intranets $\{1,2,3\}$ and $\{4,5\}$. Since $\mathbf{K}=2$, this situation counts the answer.

![](https://cdn.luogu.com.cn/upload/image_hosting/uoy2l0x6.png)

We can find that there are $1555200$ ways to assign the priorities to have exactly $2$ intranets among $10 !=3628800$ ways, so the probability is $3 / 7$.

In Sample Case #2, the probability is $4 / 7$.

In Sample Case #3, the probability is $1 / 21$.

**Limits**

- $1 \leq \mathbf{T} \leq 50$.
- $1 \leq \mathbf{K} \leq \mathbf{M} / 2$.

**Test Set 1 (17 Pts, Visible Verdict)**

- Time limit: 20 seconds.
- $2 \leq \mathbf{M} \leq 50$.

**Test Set 2 (27 Pts, Hidden Verdict)**

- Time limit: 60 seconds.
- $2 \leq \mathbf{M} \leq 5 \times 10^{5}$.


---

---
title: "[GCJ 2021 #3] Binary Search Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13042
tag: ['动态规划 DP', '2021', '多项式', '组合数学', '拉格朗日插值法', 'Google Code Jam']
---
# [GCJ 2021 #3] Binary Search Game
## 题目描述

Alice and Bob are going to play the Binary Search game. The game is played on a board consisting of a single row of $2^{\mathbf{L}}$ cells. Each cell contains an integer between 1 and $\mathbf{N}$, inclusive. There are also $\mathbf{N}$ cards numbered 1 through $\mathbf{N}$. Before the game starts, the referee writes an integer between 1 and $\mathbf{M}$, inclusive, on each card, in one of the $\mathbf{M}^{\mathbf{N}}$ ways in which that can be done. Alice and Bob know the integers in the cells and on each card before they start playing.

The game proceeds alternating turns, with Alice having the first turn. There are $\mathbf{L}$ turns in total, which means Alice plays $\lceil \mathbf{L}/2 \rceil$ turns and Bob plays $\lfloor \mathbf{L}/2 \rfloor$ turns. During a turn, a player can eliminate either the leftmost half or the rightmost half of the remaining cells. For example, let us consider a board that contains the numbers $[2, 4, 1, 1, 4, 5, 2, 5]$. In her first turn, Alice must choose to eliminate one half, leaving either $[2, 4, 1, 1]$ or $[4, 5, 2, 5]$. If she eliminates the leftmost half and leaves $[4, 5, 2, 5]$, then Bob must choose between leaving $[4, 5]$ and $[2, 5]$. If he were to leave $[2, 5]$, the game's final turn would have Alice choosing between $[2]$ and $[5]$.

When the game is over, they look at the number $X$ in the only remaining cell. The score of the game is the integer written on card number $X$. In the example above, if Alice were to eliminate $[5]$ and leave $[2]$ in her final turn, the score of the game would be the number the referee wrote on card number 2.

![](https://cdn.luogu.com.cn/upload/image_hosting/l71ofi6o.png)

Alice plays optimally to maximize the score of the game, while Bob plays optimally to minimize it. They are given a fixed board with integers $\mathbf{A}_1$, $\mathbf{A}_2$, …, $\mathbf{A}_{2^{\mathbf{L}}}$ in its cells. For maximal fairness, they will play $\mathbf{M}^{\mathbf{N}}$ games, and the referee will choose a different way to write integers on the cards for each one. That means that for any given way of writing integers on the cards, Alice and Bob will play exactly one game with it. Given the game parameters and the fixed board contents, please determine the sum of the scores of all those games. Since the output can be a really big number, we only ask you to output the remainder of dividing the result by the prime $10^9 + 7$ ($1000000007$).
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of exactly two lines. The first line of each test case contains the three integers $\mathbf{N}$, $\mathbf{M}$, and $\mathbf{L}$. The second line contains $2^{\mathbf{L}}$ integers $\mathbf{A}_1$, $\mathbf{A}_2$, …, $\mathbf{A}_{2^{\mathbf{L}}}$, where $\mathbf{A}_i$ is the integer contained in the $i$-th cell from the left of the board.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the sum of scores of all $\mathbf{M}^{\mathbf{N}}$ games, modulo the prime $10^9 + 7$ ($1000000007$).
## 样例

### 样例输入 #1
```
3
2 2 2
2 1 1 1
4 3 2
3 1 1 4
5 100 3
2 4 1 1 4 5 2 5
```
### 样例输出 #1
```
Case #1: 6
Case #2: 144
Case #3: 991661422
```
## 提示

**Sample Explanation**

In Sample Case #1, there are 4 ways to write the integers on the blank cards: $[1, 1], [1, 2], [2, 1]$, and $[2, 2]$. In the first two ways, no matter what Alice chooses in her first turn, Bob can always make the number in the last remaining cell be a 1, and card 1 contains a 1, which means those two games have a score of 1. In the last two ways, Alice can start by eliminating the leftmost half of the board, leaving $[1, 1]$ for Bob, who then has no choice but to leave $[1]$ at the end. Since card 1 has a 2 on it in these ways, the score of both of these games is 2. The sum of all scores is therefore $1 + 1 + 2 + 2 = 6$.

**Limits**

- $1 \leq \text{T} \leq 12$.
- $1 \leq \text{L} \leq 5$.
- $1 \leq \text{A}_i \leq \text{N}$, for all $i$.

**Test Set 1 (9 Pts, Visible Verdict)**

- $1 \leq \text{N} \leq 8$.
- $1 \leq \text{M} \leq 100$.

**Test Set 2 (26 Pts, Hidden Verdict)**

- $1 \leq \text{N} \leq 32$.
- $1 \leq \text{M} \leq 10^9$.


---

---
title: "[GCJ 2020 Finals] Hexacoin Jam"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13072
tag: ['数学', '2020', '组合数学', 'Google Code Jam']
---
# [GCJ 2020 Finals] Hexacoin Jam
## 题目描述

The Code Jam team's first cryptocurrency, jamcoins, never caught on. This year, we are trying again with $hexacoins$, which are named for their use of base 16. To "mine" a $\mathbf{D}$-digit hexacoin, one has to work with integers using exactly $\mathbf{D}$ base 16 digits, including leading zeroes if needed. Each value represents an integer between 0 and $16^{\mathbf{D}} - 1$, inclusive. Base 16 digits are represented by the numbers 0 through 9 and the uppercase letters A through F, as usual. For example, F2B, 0C8 and 000 are valid values when $\mathbf{D}=3$, corresponding to the base 10 values 3883, 200 and 0. On the other hand, 1234, DF, C0DE and JAM are not valid values when $\mathbf{D}=3$.

When performing addition of $\mathbf{D}$-digit base 16 values, any overflow digits are dropped. That is, the addition is performed modulo $16^{\mathbf{D}}$. For example, F2B + 0C8 = FF3 (4083 in base 10) and F2B + F2B = E56 (3670 in base 10, because the sum's result is 7766, and taking modulo $16^3$ yields 3670).

To "mine" a $\mathbf{D}$-digit hexacoin, a computer must perform the following steps:

1. Choose a list $\mathbf{L}$ of $\mathbf{N}$ $\mathbf{D}$-digit base 16 values $\mathbf{L}_1, \mathbf{L}_2, ..., \mathbf{L}_\mathbf{N}$.
2. Choose a target range of $\mathbf{D}$-digit base 16 values: the numbers from $\mathbf{S}$ to $\mathbf{E}$, inclusive.
3. Choose a permutation $\mathbf{P}$ of the base 16 digits 0 through F, uniformly at random from among all 16! such permutations.
4. Apply $\mathbf{P}$ to all digits of all numbers in the list, creating a new list $\mathbf{L}'$ consisting of $\mathbf{N}$ $\mathbf{D}$-digit base 16 values. Formally, the $j$-th digit of the $i$-th element of $\mathbf{L}'$ is the result of applying $\mathbf{P}$ to the $j$-th digit of the $i$-th element of $\mathbf{L}$.
5. Choose a pair of elements from $\mathbf{L}'$ without replacement, uniformly at random from among all such possible choices, and independently of the choice of permutation.
6. Calculate the sum (dropping overflow digits) of the two chosen elements.

If the sum calculated in the last step is between $\mathbf{S}$ and $\mathbf{E}$, inclusive, then a hexacoin has been found! For example, suppose that:

* $\mathbf{L} = [134, 000, FFB, 000, AA9]$.
* $\mathbf{S} = 85C$ and $\mathbf{E} = EDF$.
* The computer happens to choose $\mathbf{P} = (0 \rightarrow 4, 1 \rightarrow A, 2 \rightarrow 2, 3 \rightarrow 8, 4 \rightarrow 9, 5 \rightarrow B, 6 \rightarrow C, 7 \rightarrow 7, 8 \rightarrow F, 9 \rightarrow 1, A \rightarrow 0, B \rightarrow 3, C \rightarrow 5, D \rightarrow 6, E \rightarrow E, F \rightarrow D)$.

Then, when $\mathbf{P}$ is applied to $\mathbf{L}$, the resulting $\mathbf{L}'$ is [A89, 444, DD3, 444, 001]. Notice that $\mathbf{P}$ is not applied to $\mathbf{S}$ and $\mathbf{E}$.

There are $(5 \times 4) / 2 = 10$ pairs of values to choose, and each pair has a probability of $1/10$ of being chosen. The only sums that fall within the range are A89 + DD3 = 85C, 444 + 444 = 888, A89 + 001 = A8A, DD3 + 001 = DD4, and A89 + 444 = ECD (twice).

The first two steps are already computed and you know the list $\mathbf{L}$ and the range $[\mathbf{S}, \mathbf{E}]$ that were chosen. What is the probability that a hexacoin is found after the rest of the process is performed?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of three lines. The first line contains two integers $\mathbf{N}$ and $\mathbf{D}$: the size of the given list and the number of digits to work with, respectively. The second line contains two $\mathbf{D}$-digit base 16 numbers $\mathbf{S}$ and $\mathbf{E}$: the inclusive lower and upper bounds of the target range, respectively. Then there is one more line containing $\mathbf{N}$ $\mathbf{D}$-digit base 16 numbers $\mathbf{L}_1, \mathbf{L}_2, \dots, \mathbf{L}_\mathbf{N}$, representing the values in the list.
## 输出格式

For each test case, output one line containing `Case #x: y z`, where $x$ is the test case number (starting from 1) and $y$ and $z$ are non-negative integers, such that the fraction $y/z$ represents the probability of finding a hexacoin, under the conditions described above. All of $x$, $y$, and $z$ must be in base 10. If there are multiple acceptable values for $y$ and $z$, choose the ones such that $z$ is minimized.
## 样例

### 样例输入 #1
```
4
2 2
10 10
00 FF
2 2
10 11
00 FF
4 3
FFF FFF
230 A10 010 F70
4 3
AFF FFF
230 A10 010 F70
```
### 样例输出 #1
```
Case #1: 7 120
Case #2: 1 15
Case #3: 0 1
Case #4: 2731 8736
```
## 提示

**Sample Explanation**

In Sample Case #1, the target range is just a single value $10$. Since the result ends with $0$, the sum of the values assigned to both last digits $0$ and $F$ must end in $0$ as well. Since $\mathbf{P}[0]$ and $\mathbf{P}[F]$ are different values, their sum cannot be exactly $0$. Therefore, $\mathbf{P}[0] + \mathbf{P}[F]$ must be $10$ (in base 16). There are $7$ pairs of different digits that accomplish that. $\mathbf{P}[0]$ and $\mathbf{P}[F]$ cannot both be $8$. All $7$ pairs lead to an overall sum of $10$ (after dropping an overflow $1$). Therefore, there are $14$ assignments of different digits to $0$ and $F$ that lead to a hexacoin. There are $16 \times 15$ possible assignments to those digits, so the result is $14/240 = 7/120$.

In Sample Case #2, we need to add the probability of the result being exactly $11$ to the result of Sample Case #1. The only way that happens is if $0$ and $F$ are assigned to $0$ and $1$, in either order. That has a probability of $2/240 = 1/120$, leading to a total of $7/120 + 1/120 = 8/120 = 1/15$.

In Sample Case #3, notice that regardless of which permutation and pair of numbers the computer chooses from the list, we will add two numbers that end in the same digit. That produces an even result, even after taking it modulo $16^3$. Since the only value in range is odd, we have no hope of mining a hexacoin in this case. Notice that $0/2$ is an invalid representation of the answer because $z$ would not be minimum.

**Limits**

- $2 \leq \mathbf{N} \leq 450$.
- $\mathbf{S}$ contains exactly $\mathbf{D}$ characters.
- Each character of $\mathbf{S}$ is a base 16 digit.
- $\mathbf{E}$ contains exactly $\mathbf{D}$ characters.
- Each character of $\mathbf{E}$ is a base 16 digit.
- $\mathbf{S} \leq \mathbf{E}$.
- $\mathbf{L}_i$ contains exactly $\mathbf{D}$ characters, for all $i$.
- Each character of $\mathbf{L}_i$ is a base 16 digit, for all $i$.

**Test Set 1 (10 Pts, Visible Verdict)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{D} \leq 3$.

**Test Set 2 (10 Pts, Hidden Verdict)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{D} \leq 4$.

**Test Set 3 (22 Pts, Hidden Verdict)**

- $1 \leq \mathbf{T} \leq 10$.
- $2 \leq \mathbf{D} \leq 5$.


---

---
title: "[GCJ 2014 Finals] Allergy Testing"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13268
tag: ['动态规划 DP', '2014', '二分', '矩阵加速', '组合数学', 'Google Code Jam']
---
# [GCJ 2014 Finals] Allergy Testing
## 题目描述

Kelly is allergic to exactly one of $\mathrm{N}$ foods, but she isn't sure which one. So she decides to undergo some experiments to find out.

In each experiment, Kelly picks several foods and eats them all. She waits $\mathrm{A}$ days to see if she gets any allergic reactions. If she doesn't, she knows she isn't allergic to any of the foods she ate. If she does get a reaction, she has to wait for it to go away: this takes a total of $\mathrm{B}$ days (measured from the moment when she ate the foods).

To simplify her experimentation, Kelly decides to wait until each experiment is finished (after $\mathrm{A}$ or $\mathrm{B}$ days) before starting the next one. At the start of each experiment, she can choose the set of foods she wants to eat based on the results of previous experiments.

Kelly chooses what foods to eat for each experiment to minimize the worst-case number of days before she knows which of the $\mathrm{N}$ foods she is allergic to. How long does it take her in the worst case?
## 输入格式

The first line of the input gives the number of test cases, $\mathrm{T}$. $\mathrm{T}$ test cases follow. Each test case on a single line, containing three space-separated integers: $\mathrm{N}, \mathrm{A}$ and $\mathrm{B}$.

## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the number of days it will take for Kelly to find out which food she is allergic to, in the worst case.
## 样例

### 样例输入 #1
```
3
4 5 7
8 1 1
1 23 32
```
### 样例输出 #1
```
Case #1: 12
Case #2: 3
Case #3: 0
```
## 提示

In the first sample case:
- First, Kelly eats foods #1 and #2.
- If she gets no reaction after 5 days, she eats food #3. 5 days after that, she will know whether she is allergic to food #3 or food #4.
- If she does get a reaction to the first experiment, then 7 days after the first experiment, she eats food #1. 5 days after that, she will know whether she is allergic to food #1 or food #2.

**Limits**

- $1 \leq T \leq 200$

**Small dataset(15 Pts)**
- Time Limit: ~~60~~ 3 seconds
- $1 \leq N \leq 10^{15}$
- $1 \leq A\leq B \leq 100$

**Large dataset(35 Pts)**
- Time Limit: ~~120~~ 5 seconds
- $1 \leq N \leq 10^{15}$
- $1 \leq A\leq B \leq 10^{12}$


---

---
title: "[GCJ 2013 Finals] Let Me Tell You a Story"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13306
tag: ['动态规划 DP', '2013', '树状数组', '组合数学', 'Google Code Jam']
---
# [GCJ 2013 Finals] Let Me Tell You a Story
## 题目描述

The story goes...

A long, long time ago, King Tyrone the Fair had 4 ministers. The first minister (the king's top adviser) was paid 7 gold pieces per week. The second minister was paid 4 gold pieces per week. The third and fourth ministers were each paid 6 gold pieces per week. Unfortunately, Tyrone accidentally forgot the Ministerial Compensation List in the photo copier one day, and the List ended up on the front page of the Kingdom Times newspaper. At this point, the second minister requested to speak to the king, upset that his own salary was lower than that of the lower ranked third minister.

His Fairness King Tyrone saw no other solution than to fire the third minister. After all, lowering the third minister's salary, raising the salary of the second minister, or changing job titles were all unfair solutions to the problem, in the king's opinion. And who are we to question King Tyrone? Of course, firing the third minister did not solve the problem. The second minister continued to complain because his salary was still lower than that of the fourth minister. So King Tyrone fired the fourth minister as well. At this point, neither of the two remaining ministers complained, and everyone lived happily ever after.

...wait a minute. I messed that up. I'm sorry. My memory is not what it used to be. One moment please... Right. King Tyrone the Fair. Four ministers. Paid 7, 4, 6, and 6 respectively. Ah, yes. The ending went like this...

When the second minister complained of unfairness, King Tyrone fired the first minister. Some might say this was a bit harsh, as the first minister wasn't involved in any way, but we shouldn't question King Tyrone. Obviously, the second minister still complained, so King Tyrone simply fired him. Of the remaining two ministers, each one was being paid at least as much as any minister below him, so none of them complained. And everyone lived happily ever after.

Much better... I think? Now I'm not sure anymore. I know for certain that there were $N$ ministers, and I clearly remember their salaries. I also know that every time a minister's salary was lower than the salary of a minister below him, somebody would complain, and some minister got fired; but that it could have been any minister, regardless of whether that minister had anything at all to do with the problem. Ministers continued to be fired until no one complained because all of the salaries were non-increasing. At that point, the firings stopped. But I do not remember in which order the ministers got fired.

Can you help me fix my story? Or at least please tell me how many different stories I could have told. Two stories are different if the sequences of fired ministers in them are not the same.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one consists of two lines. The first line will contain an integer $N$, and the second line will contain $N$ space-separated integers denoting the ministers' salaries, in order from the first minister to the $N$'th minister.
## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the number of stories I could tell you, modulo 10007.
## 样例

### 样例输入 #1
```
3
4
7 4 6 6
8
90 80 70 60 50 50 40 30
2
7 8
```
### 样例输出 #1
```
Case #1: 14
Case #2: 1
Case #3: 2
```
## 提示

**Limits**

- Each salary will be positive and at most 10000.

**Small dataset (14 Pts, Test set 1 - Visible)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq T \leq 100.$
- $1 \leq N \leq 100.$

**Large dataset (50 Pts, Test set 2 - Hidden)**

- Time limit: ~~120~~ 12 seconds.
- $1 \leq T \leq 20.$
- For 80% of test cases, $1 \leq N \leq 2000.$
- For all test cases, $1 \leq N \leq 8000.$



---

---
title: "[ZJOI2012] 波浪"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P2612
tag: ['动态规划 DP', '2012', '各省省选', '浙江', '组合数学']
---
# [ZJOI2012] 波浪
## 题目描述

阿米巴和小强是好朋友。

阿米巴和小强在大海旁边看海水的波涛。小强第一次面对如此汹涌的海潮，他兴奋地叫个不停。而阿米巴则很淡定，他回想起曾经的那些日子，事业的起伏，情感的挫折……总之今天的风浪和曾经经历的那些风雨比起来，简直什么都不算。

于是，这对好朋友不可避免地产生了分歧。为了论证自己的观点，小强建立了一个模型。他海面抽象成一个 $1$ 到 $N$ 的排列 $P_{1\ldots N}$。定义波动强度等于相邻两项的差的绝对值的和，即：

$$L = | P_2 – P_1 | + | P_3 – P_2 | +\ldots + | P_N – P_{N-1} |$$

给你一个 $N$ 和 $M$，问：随机一个 $1\ldots N$ 的排列，它的波动强度不小于 $M$ 的概率有多大？

答案请保留小数点后 $K$ 位输出，四舍五入。

## 输入格式

第一行包含三个整数 $N, M$ 和 $K$，分别表示排列的长度，波动强度，输出位数。

## 输出格式

第一行包含一个小数点后 $K$ 位的实数。

## 样例

### 样例输入 #1
```
3 3 3
```
### 样例输出 #1
```
0.667
```
## 提示

$N = 3$ 的排列有 $6$ 个：$123, 132, 213, 231, 312, 321$；他们的波动强度分别为 $2, 3, 3, 3, 3, 2$。所以，波动强度不小于 $3$ 的概率是 $\frac 46$，即 $0.667$。

你也可以通过下面的代码来验证这个概率：

```cpp
int a[3]={0,1,2},s=0,n=3;
for (int i=0;i<1000000;i++){
random_shuffle(a,a+n);
int t=0;
for (int j=0;j<n-1;j++) t+=abs(a[j+1]-a[j]); 
if (t>=3) s++;
}
printf("%.3f\n",s/1000000.0);
```
### 【数据规模】

对于 $30\%$ 的数据，$N \leq 10$。

对于另外 $30\%$ 的数据， $K \leq 3$。

对于另外 $30\%$ 的数据，$K \leq 8$。

对于另外 $10\%$ 的数据，$N \leq 50$。

对于 $100\%$ 的数据，$N \leq 100，K \leq 30，0 \leq M \leq 2147483647$。


---

---
title: "幼儿园篮球题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P2791
tag: ['数学', '2019', 'O2优化', '组合数学', '快速数论变换 NTT']
---
# 幼儿园篮球题
## 题目背景

众所周知，全民制作幼儿园园龄两年半的蔡徐坤同学喜欢唱、跳、rap 和篮球。而作为欧文的老师，他的篮球技术自然比 ikun 们要强得多。
## 题目描述

全民制作幼儿园的蔡徐坤专属篮球场上总共有 $N$ 个蔡徐坤专属篮球，而其中有 $M$ 个是没气的。鉴于蔡徐坤的高超技术，他投**没气的球一定能进**，而投**有气的球一定不能**。

蔡徐坤举办了 $S$ 场巡回篮球表演，第 $i$ 场表演 ikun 们会指定投球个数 $k_i$ ，ikun 们会从 $N$ 个蔡徐坤专属篮球中准备 $n_i$ 个球放在场地上，其中恰好有 $m_i$ 个是没气的。蔡徐坤会在这 $n_i$ 个蔡徐坤专属篮球中**随机**选出 $k_i$ 个投篮。如果投进了 $x$ 个，则这次表演的**失败度**为 $x^L$。ikun 们想知道这 $S$ 场表演的**期望失败度**对 $998244353$ 取模的结果。篮球表演之间**相互独立**。
## 输入格式

第一行，四个正整数，$N,M,S,L$，表示蔡徐坤专属篮球总个数，没气的篮球总个数，蔡徐坤巡回篮球表演场数，以及失败度参数。

接下来的第 $i+1$ 行，每行三个正整数 $n_i,m_i,k_i$，表示第 $i$ 场表演蔡徐坤专属篮球个数、没气的篮球个数和 ikun 们指定的投球个数。
## 输出格式

输出共 $S$ 行，第 $i$ 行为一个正整数，表示第 $i$ 场表演的期望失败度对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
3 2 1 3
3 2 2
```
### 样例输出 #1
```
332748121
```
## 提示

对于样例，我们作出如下解释：设失败度为 $X$，蔡徐坤有 $\frac{1}{3}$ 的概率投进 $2$ 个，有 $\frac{2}{3}$ 的概率投进 $1$ 个，期望失败度为 $E(x)=\frac{2^3}{3}+\frac{1^3*2}{3}=\frac{10}{3}$，$\frac{10}{3}\equiv 332748121\pmod{998244353}$。

子任务 1 ($15\%$)：$1\leq L\leq2$。

子任务 2 ($10\%$)：$1\leq N\leq10^5$。

子任务 3 ($75\%$)：无特殊限制。

对于全部数据，$1\leq S\leq200$，$1\leq L\leq2\times 10^5$，$1\leq M\leq N\leq2\times 10^7$。并且对于 $1\leq i\leq S$，有 $1\leq m_i,k_i\leq n_i\leq N$，$1\leq m_i\leq M$。


---

---
title: "[集训队互测 2011] Crash 的文明世界"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4827
tag: ['动态规划 DP', '数学', '2011', '集训队互测', '组合数学', '二项式定理', '容斥原理', 'Stirling 数']
---
# [集训队互测 2011] Crash 的文明世界
## 题目描述

Crash 小朋友最近迷上了一款游戏——文明5 (Civilization V)。在这个游戏中，玩家可以建立和发展自己的国家，通过外交和别的国家交流，或是通过战争征服别的国家。

现在 Crash 已经拥有了一个 $n$ 个城市的国家，这些城市之间通过道路相连。由于建设道路是有花费的，因此 Crash 只修建了 $n-1$ 条道路连接这些城市，不过可以保证任意两个城市都有路径相通。

在游戏中，Crash 需要选择一个城市作为他的国家的首都，选择首都需要考虑很多指标，有一个指标是这样的：

$$S(i) = \sum_{j = 1}^{n}{\rm dist}(i, j) ^ k$$

其中 $S(i)$ 表示第 $i$ 个城市的指标值，${\rm dist}(i, j)$ 表示第 $i$ 个城市到第 $j$ 个城市需要经过的道路条数的最小值，$k$ 为一个常数且为正整数。

因此 Crash 交给你一个简单的任务：给出城市之间的道路，对于每个城市，输出这个城市的指标值，由于指标值可能会很大，所以你只需要输出这个数 $\bmod\ 10007$ 的值。
## 输入格式

输入的第一行包括两个正整数 $n$ 和 $k$。

接下来有 $n-1$ 行，每行两个正整数 $u, v$（$1\le u, v\le n$），表示第 $u$ 个城市和第 $v$ 个城市之间有道路相连。这些道路保证能符合题目的要求。
## 输出格式

输出共 $n$ 行，每行一个正整数，第 $i$ 行的正整数表示第 $i$ 个城市的指标值 $\bmod\ 10007$ 的值。
## 样例

### 样例输入 #1
```
5 2
1 2
1 3
2 4
2 5

```
### 样例输出 #1
```
10
7
23
18
18

```
## 提示

对于 $20 \%$ 的数据，$n\le 5000$，$k\le 30$。

对于 $50 \%$ 的数据，$n\le 5\times 10^4$，$k\le 30$。

对于 $100 \%$ 的数据，$1\le n\le 5\times 10^4$，$1\le k\le 150$。


---

---
title: "[MtOI2018] 情侣？给我烧了！（加强版）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4931
tag: ['递推', '2018', '洛谷原创', '组合数学', '生成函数', '逆元']
---
# [MtOI2018] 情侣？给我烧了！（加强版）
## 题目背景

FFF

本题原版：[P4921](https://www.luogu.com.cn/problem/P4921)
## 题目描述

有 $n$ 对情侣来到电影院观看电影。在电影院，恰好留有 $n$ 排座位，每排包含 $2$ 个座位，共 $2n$ 个座位。

现在，每个人将会随机坐在某一个位置上，且恰好将这 $2n$ 个座位坐满。

如果一对情侣坐在了同一排的座位上，那么我们称这对情侣是和睦的。

你的任务是求出共有多少种不同的就坐方案满足**恰好**有 *k* 对情侣是和睦的。

两种就坐方案不同当且仅当存在一个人在两种方案中坐在了不同的位置。不难发现，一共会有 $(2n)!$ 种不同的就坐方案。

由于结果可能较大，因此输出对 $998244353$ 取模的结果。
## 输入格式

输入包含多组数据。

输入的第 $1$ 行包含 $1$ 个正整数 $T$，表示数据的组数。

接下来 $T$ 行，每行包含 $2$ 个正整数 $n,k$。
## 输出格式

输出共 $T$ 行。

对于每组输入数据，输出共 $1$ 行，包含 $1$ 个整数，表示恰好有 $k$ 对情侣和睦的就坐方案数。
## 样例

### 样例输入 #1
```
5
1 1
2 0
2 2
2333 666
2333333 1000000

```
### 样例输出 #1
```
2
16
8
798775522
300377435

```
## 提示

### 子任务

对于 $10 \%$ 的数据，满足 $1 \leq T \leq 10, 1 \leq n \leq 5$。

对于 $40 \%$ 的数据，满足 $1 \leq n \leq 3 \times 10^3$。

对于 $100 \%$ 的数据，满足 $1 \leq T \leq 2 \times 10^5, 1 \leq n \leq 5 \times 10^6, 0 \leq k \leq n$。

### 题目来源

[MtOI2018 迷途の家の水题大赛](https://www.luogu.org/contest/11260) T2 加强版

出题人：Imagine

50167


---

---
title: "[Cnoi2019] 最终幻想"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5388
tag: ['递推', '2019', '组合数学', '快速数论变换 NTT']
---
# [Cnoi2019] 最终幻想
## 题目背景

理论上来说，压轴的应该是一道数据结构题，可是它咕咕咕~了.
## 题目描述

你有一个 $n$ 维超球, 求使用 $k$ 个 $n-1$ 维超平面可以将这个 $n$ 维超球划分成多少个 $n$ 维块。

答案对 $998244353$ 取模。
## 输入格式

输入两个数 $n$, $k$.
## 输出格式

一行，表示答案。
## 样例

### 样例输入 #1
```
3 4
```
### 样例输出 #1
```
15
```
## 提示

Subtask1( 21pts ) : $n \le 10^6$

Subtask2( 7pts )   : $k \le n$

Subtask3( 72pts ) : 无特殊限制

对于 100% 的数据 $n, k \in [1,998244353)$

~~其实可以出高精度范围的，但是出题人咕咕咕~了。~~


---

---
title: "[BJ United Round #3] 押韵"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5548
tag: ['数学', '北京', '组合数学', '生成函数']
---
# [BJ United Round #3] 押韵
## 题目背景

韵要怎么押？棋要怎么下？敌要怎么杀？旗要怎么插？
## 题目描述

现在你想要写一首歌词，一共有 $nd$ 个字，你一共设计了 $k$ 种韵脚，每个字恰好要符合一种韵脚。  

并且只有当每种韵脚在歌词中出现的字数恰为 $d$ 的倍数时，这首歌才好听。

试问一共有多少种韵脚的搭配方法，使得歌词好听？

你只需要回答方案数对于 $1049874433$ 取模的结果即可。
## 输入格式

一行三个整数 $n,k,d$，如题意所示。
## 输出格式

一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
2 2 2
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
2 3 4
```
### 样例输出 #2
```
213
```
### 样例输入 #3
```
2 4 6
```
### 样例输出 #3
```
5548
```
## 提示

对于 $100\%$ 的数据，保证：  
$0 \le n \le 10^9$  
$1\le k \le 2000$  
$d\in \{ 1,2,3,4,6 \}$

By：EntropyIncreaser


---

---
title: "十二重计数法"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5824
tag: ['数学', 'O2优化', '组合数学', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 十二重计数法
## 题目背景

组合数学是一门古老而迷人的学科。

传说早在 $114514$ 年前，一位名为忆哀的神灵来到地球，发现了人类——另一种有智慧的物种。  

她觉得这很有趣，为了加速人类文明的发展，她向人间传下了一类计数问题——十二重计数，这也正是组合数学的开端。  

而只有搞明白这类问题，才能在组合数学上继续深入。
## 题目描述

有 $n$ 个球和 $m$ 个盒子，要全部装进盒子里。  
还有一些限制条件，那么有多少种方法放球？（与放的先后顺序无关）  

限制条件分别如下：    

$\text{I}$：球之间互不相同，盒子之间互不相同。    
$\text{II}$：球之间互不相同，盒子之间互不相同，每个盒子至多装一个球。   
$\text{III}$：球之间互不相同，盒子之间互不相同，每个盒子至少装一个球。  

$\text{IV}$：球之间互不相同，盒子全部相同。        
$\text{V}$：球之间互不相同，盒子全部相同，每个盒子至多装一个球。   
$\text{VI}$：球之间互不相同，盒子全部相同，每个盒子至少装一个球。

$\text{VII}$：球全部相同，盒子之间互不相同。  
$\text{VIII}$：球全部相同，盒子之间互不相同，每个盒子至多装一个球。  
$\text{IX}$：球全部相同，盒子之间互不相同，每个盒子至少装一个球。   

$\text{X}$：球全部相同，盒子全部相同。   
$\text{XI}$：球全部相同，盒子全部相同，每个盒子至多装一个球。  
$\text{XII}$：球全部相同，盒子全部相同，每个盒子至少装一个球。

由于答案可能很大，所以要对 $998244353$ 取模。
## 输入格式

仅一行两个正整数 $n,m$
## 输出格式

输出十二行，每行一个整数，对应每一种限制条件的答案。
## 样例

### 样例输入 #1
```
13 6
```
### 样例输出 #1
```
83517427
0
721878522
19628064
0
9321312
8568
0
792
71
0
14
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n,m \le 2\times 10^5$。

orz $\mathsf E \color{red}\mathsf{ntropyIncreaser}$


---

---
title: "点双连通图计数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5827
tag: ['数学', 'O2优化', '组合数学', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 点双连通图计数
## 题目描述

求 $n$ 个点的有标号点双连通图（简单无向图，整个图是一个点双连通分量）的个数，答案对 $998244353$ 取模。
## 输入格式

共五行，每行一个整数 $n$，表示一次询问。
## 输出格式

共五行，每行一个整数，表示一次询问的答案。
## 样例

### 样例输入 #1
```
1
2
3
4
5

```
### 样例输出 #1
```
1
1
1
10
238

```
## 提示

$1 \le n \le 10^5$。


---

---
title: "边双连通图计数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5828
tag: ['数学', 'O2优化', '组合数学', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 边双连通图计数
## 题目描述

求 $n$ 个点的有标号边双连通图（简单无向图，整个图是一个边双连通分量）的个数，答案对 $998244353$ 取模。
## 输入格式

共五行，每行一个整数 $n$，表示一次询问。
## 输出格式

共五行，每行一个整数，表示一次询问的答案。
## 样例

### 样例输入 #1
```
1
2
3
4
5

```
### 样例输出 #1
```
1
0
1
10
253

```
## 提示

$1 \le n \le 10^5$。


---

---
title: "无标号无根树计数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5900
tag: ['数学', 'O2优化', 'Pólya 定理', '组合数学', '生成函数', '快速傅里叶变换 FFT']
---
# 无标号无根树计数
## 题目背景

考虑到你谷还没有这类题，于是就放了这么个水题   

## 题目描述

求 $n$ 个点的无标号无根树数量，答案对 $998244353$ 取模。
## 输入格式

输入一行一个正整数 $n$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
7
```
### 样例输出 #1
```
11
```
### 样例输入 #2
```
27
```
### 样例输出 #2
```
751065460
```
## 提示

【数据范围】   
对于 $30\%$ 的数据，$1\le n \le 1000$；   
对于 $100\%$ 的数据，$1\le n \le 2\times 10^5$。  

虽然 $\Theta(n \log^2 n)$ 也能过，但是没什么意义，建议写一下 $\Theta(n \log n)$ 的做法。


---

---
title: "『MdOI R1』Epic Convolution"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6073
tag: ['动态规划 DP', '数学', '组合数学', 'Stirling 数', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 『MdOI R1』Epic Convolution
## 题目背景

小 Q 是神仙，尤其喜欢多项式。

这天小 K 问了道题：

给定长度 $n$ 的序列 $g,h$，求 $f$ 满足 $f_n=\sum\limits_{k=0}^{n}g_kh_{n-k}$。

小 Q 对小 K 说：你这个菜鸡，这不随便卷一下就行了吗，你 FFT 怎么学的了。

然后小 K 花了一个月学习 FFT 和 NTT。又跑过去问小 Q 一道题：

给定长度 $n$ 的序列 $g,h$，求 $f$ 满足 $f_n=\sum\limits_{k=0}^{n}\binom{n}{k}g_kh_{n-k}$。

小 Q 对小 K 说：你这个菜鸡，这不随便卷一下就行了吗，你 FFT 怎么学的了。

然后小 K 又花了一个月学习 FFT 和 NTT。又跑过去问小 Q 一道题：

给定长度 $n$ 的序列 $g,h$，求 $f$ 满足 $f_n=\sum\limits_{k=0}^{n}k^ng_kh_{n-k}$。

小 Q 对小 K 说：你这个菜鸡，这不随便卷一下就行了吗，你 FFT 怎么学的了。

然后他仔细看了一遍，傻眼了，发现他不会这道题。

为了吊打小 K，你需要告诉他 $4$ 个特殊情况的做法。
## 题目描述

给定特定的序列 $g,h$，求 $f_n$ 满足 $f_n=\sum\limits_{k=0}^{n}k^ng_kh_{n-k}$。

本题有五个子任务，前四个子任务给定不同形式的 $g,h$，需要求出 $f_n$，第五个子任务不依赖于这个等式，但是形式上与此相似。

**注意，本题所有输出请对 $998244353$（$119\times 2^{23}+1$，一个质数）取模。**

---

**Subtask 1（4 pts）：**

给定一个 $n$，你需要回答 $q$ 组询问，每组询问给定一个整数 $m$。

每组询问的 $g$ 和 $h$ 如下所示（$0\leq k\leq n$）：

$$g_k=\begin{cases}1,&k<m\\0,&k\geq m\end{cases}$$

$$h_k=1$$

你需要回答出 $f_n$ 的值。

---

**Subtask 2,3（16,16 pts）：**

这两个子任务给定的序列 $g,h$ 形式相同，但数据范围不同，请仔细阅读数据范围。

你需要回答 $q$ 组询问，每组询问给定两个整数 $n,m$。

每组询问的 $g$ 和 $h$ 如下所示（$0\leq k\leq n$）：

$$g_k=\frac{1}{(k+m+1)!}$$

$$h_k=\begin{cases}0,&k<m\\\frac{(-1)^{k-m}}{(k-m)!},&k\geq m\end{cases}$$

你需要回答出 $f_n$ 的值。

---

**Subtask 4（32 pts）：**

你需要回答 $q$ 组询问，每组询问给定两个整数 $n,m$。

每组询问的 $g$ 和 $h$ 如下所示（$0\leq k\leq n$）：

$$g_k=\frac{k^m}{k!}$$

$$h_k=\frac{(-1)^k}{k!}$$

你需要回答出 $f_n$ 的值。

---

**Subtask 5（32 pts）：**

你需要回答 $q$ 组询问，每组询问给定两个整数 $n,m$。

**注意下面 $n,m$ 的含义，不要看反。**

$$\sum\limits_{k=0}^{m}(k+1)^m\dfrac{(k+1)^{n+1}}{(k+1)!}\sum\limits_{i=0}^{m-k}\dfrac{\binom{2n+1}{i}(-1)^{m-k}}{(m-k-i)!(k+1)^i}$$

你需要回答出上面这个式子的值。

与前四个 Subtask 相似之处是，求和的一开始是幂的形式。
## 输入格式

第一行一个整数 $op$，表示子任务编号。

若 $op=1$：  

第二行一个整数 $n$，第三行一个整数 $q$；  

接下来 $q$ 行，每行一个整数 $m$。

若 $op\in \{2,3,4,5\}$： 

第二行一个整数 $q$；  

接下来 $q$ 行：每行两个整数 $n,m$。  

所有变量含义见题目描述。
## 输出格式

对于每组询问，一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
1
5
2
2
3
```
### 样例输出 #1
```
1
33

```
### 样例输入 #2
```
2
2
4 2
18 7
```
### 样例输出 #2
```
440891256
841247136
```
### 样例输入 #3
```
4
2
4 2
20 9
```
### 样例输出 #3
```
65
429844531

```
### 样例输入 #4
```
5
2
4 2
30 12
```
### 样例输出 #4
```
58
475486366

```
## 提示

### 样例解释 1

在这组样例中，需要解决第一个子任务，$n=5,\ \ q=2$。

第一组询问中，$m=2$，则（省略了 $0$ 的加数项）：

$$[g_0\ \ g_1\ \ g_2\ \ g_3\ \ g_4\ \ g_5]=[1\ \ 1\ \ 0\ \ 0\ \ 0\ \ 0] $$

$$[h_0\ \ h_1\ \ h_2\ \ h_3\ \ h_4\ \ h_5]=[1\ \ 1\ \ 1\ \ 1\ \ 1\ \ 1] $$

$$f_5=1^5\times g_1h_4=1$$

第二组询问中，$m=3$，则：

$$[g_0\ \ g_1\ \ g_2\ \ g_3\ \ g_4\ \ g_5]=[1\ \ 1\ \ 1\ \ 0\ \ 0\ \ 0]$$

$$[h_0\ \ h_1\ \ h_2\ \ h_3\ \ h_4\ \ h_5]=[1\ \ 1\ \ 1\ \ 1\ \ 1\ \ 1]$$

$$f_5=1^5\times g_1h_4+2^5\times g_2h_3=33$$

------

### 样例解释 2

在这组样例中，需要解决第二个子任务，$q=2$。

第一组询问中，$n=4,\ \ m=2$，则：

$$[g_0\ \ g_1\ \ g_2\ \ g_3\ \ g_4]=[\dfrac{1}{6}\ \ \dfrac{1}{24}\ \ \dfrac{1}{120}\ \ \dfrac{1}{720}\ \ \dfrac{1}{5040}] $$

$$[h_0\ \ h_1\ \ h_2\ \ h_3\ \ h_4]=[0\ \ 0\ \ 1\ \ -1\ \ \dfrac{1}{2}] $$

$$f_5=1^4\times g_1h_3+2^4\times g_2h_2=\dfrac{11}{120} $$

$f_5=\dfrac{11}{120}$ 对 $998244353$ 取模后等于 $440891256$。

第二组询问范围过大，不进行样例解释。

------

### 样例解释 3

在这组样例中，需要解决第四个子任务，$q=2$。

第一组询问中，$n=4,\ \ m=2$，则：

$$[g_0\ \ g_1\ \ g_2\ \ g_3\ \ g_4]=[0\ \ \ 1\ \ \ 2\ \ \ \dfrac{3}{2}\ \ \dfrac{2}{3}] $$

$$[h_0\ \ h_1\ \ h_2\ \ h_3\ \ h_4]=[1\ \ -1\ \ \dfrac{1}{2}\ \ -\dfrac{1}{6}\ \ \dfrac{1}{24}] $$

$$f_5=1^4\times g_1h_3+2^4\times g_2h_2+3^4\times g_3h_1+4^4\times g_4h_0=65 $$

第二组询问范围过大，不进行样例解释。

---

### 样例解释 4

在这组样例中，需要解决第五个子任务，$q=2$。

第一组询问中，$n=4,\ \ m=2$，则枚举 $k,i$：

$$k=0,\ \ i=0:\ \ (k+1)^m\dfrac{(k+1)^{n+1}}{(k+1)!}\dfrac{\binom{2n+1}{i}(-1)^{m-k}}{(m-k-i)!(k+1)^i}=\dfrac{1}{2} $$

$$k=0,\ \ i=1:\ \ (k+1)^m\dfrac{(k+1)^{n+1}}{(k+1)!}\dfrac{\binom{2n+1}{i}(-1)^{m-k}}{(m-k-i)!(k+1)^i}=9 $$

$$k=0,\ \ i=2:\ \ (k+1)^m\dfrac{(k+1)^{n+1}}{(k+1)!}\dfrac{\binom{2n+1}{i}(-1)^{m-k}}{(m-k-i)!(k+1)^i}=36 $$

$$k=1,\ \ i=0:\ \ (k+1)^m\dfrac{(k+1)^{n+1}}{(k+1)!}\dfrac{\binom{2n+1}{i}(-1)^{m-k}}{(m-k-i)!(k+1)^i}=-64 $$

$$k=1\ \ i=1:\ \ (k+1)^m\dfrac{(k+1)^{n+1}}{(k+1)!}\dfrac{\binom{2n+1}{i}(-1)^{m-k}}{(m-k-i)!(k+1)^i}=-288 $$

$$k=2\ \ i=0:\ \ (k+1)^m\dfrac{(k+1)^{n+1}}{(k+1)!}\dfrac{\binom{2n+1}{i}(-1)^{m-k}}{(m-k-i)!(k+1)^i}=\dfrac{729}{2} $$

全部相加，结果为 $58$。

第二组询问范围过大，不进行样例解释。

---

### 数据范围

**本题采用捆绑测试，不同 Subtask 的题意不同。**

| 子任务编号 |    $q\leq$     |    $n\leq$     |    $m\leq$     | 分值 |
| :--------: | :------------: | :------------: | :------------: | :--: |
|     1      | $5\times 10^5$ |     $10^5$     | $\min(10^5,n)$ |  4   |
|     2      | $5\times 10^5$ |     $2\times 10^5$     |      $20$      |  16  |
|     3      |      $20$      |  $998244352$   |      $20$      |  16  |
|     4(31-40)      | $5\times 10^5$ | $2\times 10^5$ |      $10$      |  32  |
|     4(51-60)      | $20$ | $10^{10^5}$ |      $10$      |  32  |
|     5      | $5\times 10^5$ | $2\times 10^3$ | $2\times 10^3$ |  32  |

所有输入均为正整数。


---

---
title: "[集训队互测 2019] 简单计数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6132
tag: ['数学', '2019', '集训队互测', 'O2优化', '矩阵加速', '组合数学', '生成函数', '快速傅里叶变换 FFT']
---
# [集训队互测 2019] 简单计数
## 题目背景

## 警告，滥用本题者将被封号。


$\mathsf C \color{red}\mathsf{auchySheep}$ 近期优化了他的 快速数论变换 (NTT) 模板的常数，现在他能在 $0.1\text s$ 内轻松跑过 $n=10^9$ 了，所以他准备用下面的这个简单计数题也考验一下你的常数优化水平。
## 题目描述

传说，在很久很久以前，有一张 $n​$ 个点的带标号**有向无环**图。每条边有一个颜色，为 $k$ 种不同颜色中的一种。这张图满足如下性质：

- 每个点有不超过 $1$ 条出边  
- 每个点的入边条数在集合 $S$ 中

由于某种原因，你想知道这样的图的个数。由于这样的图可能很多，你只要输出答案对 $998244353​$ 取模的值。

两个图不同当且仅当存在一条从某个点 $a$ 到某个点 $b$ 的有向边，它只在恰好一个图中出现，或在两个图中都出现但颜色不同。
## 输入格式

第一行输入三个正整数 $n, k, |S|$。  
第二行从小到大输入 $|S|$ 个不同的非负整数，表示 $S$ 集合中的元素。
## 输出格式

输出一行一个 $[0,998244352]$ 的整数，表示符合题意的图的个数对 $998244353​$ 取模的值。
## 样例

### 样例输入 #1
```
3 1 2
0 1
```
### 样例输出 #1
```
13
```
### 样例输入 #2
```
8 2 3
0 2 3
```
### 样例输出 #2
```
7497953
```
### 样例输入 #3
```
3000 2 3
0 1 3
```
### 样例输出 #3
```
500207304
```
### 样例输入 #4
```
10000000 3 2
0 3
```
### 样例输出 #4
```
238588124
```
### 样例输入 #5
```
876543210 233 4
0 1 2 3
```
### 样例输出 #5
```
467638557
```
## 提示

【样例一解释】  
有如下 $13$ 个符合题意的图，其中 $a \to b$ 表示一条从 $a$ 连向 $b$ 的有向边：

1. 没有边
2. $1 \to 2$
3. $2 \to 1$
4. $1 \to3$
5. $3 \to 1$
6. $2 \to 3$
7. $3 \to 2$
8. $1 \to 2 \to 3$
9. $1 \to 3 \to 2$
10. $2 \to 1 \to 3$
11. $2 \to 3 \to 1$
12. $3 \to 1 \to 2$
13. $3 \to 2 \to 1$

【数据范围】  
数据共分为 $7$ 个子任务。

- 子任务 $1$（$5$ 分）：$n \leq 8$。
- 子任务 $2$（$10$ 分）：$n \leq 5000$。
- 子任务 $3$（$30$ 分）：$n \leq 10^5$。
- 子任务 $4$（$20$ 分）：$n \leq 10^7$。
- 子任务 $5$（$15$ 分）：$n \leq 10^8$。
- 子任务 $6$（$10$ 分）：$S=\{0,1\}$。
- 子任务 $7$（$10$ 分）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 9 \times 10^8​$，$1 \le k \le 10^7$，$S \neq \varnothing$，$S \subseteq \{0,1,2,3\}$。 

By：fjzzq2002  
来源：2019 年集训队互测 Day5


---

---
title: "[USACO20OPEN] Exercise P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6276
tag: ['2020', 'USACO', '组合数学', '容斥原理', '生成函数']
---
# [USACO20OPEN] Exercise P
## 题目描述

Farmer John（又）想到了一个新的奶牛晨练方案！  
如同之前，Farmer John 的 $N$ 头奶牛站成一排。对于 $1\le i\le N$ 的每一个 $i$，从左往右第 $i$ 头奶牛的编号为 $i$。他告诉她们重复以下步骤，直到奶牛们与她们开始时的顺序相同。

给定长为 $N$ 的一个排列 $A$，奶牛们改变她们的顺序，使得在改变之前从左往右第 $i$ 头奶牛在改变之后为从左往右第 $A_i$ 头。  
例如，如果 $A=(1,2,3,4,5)$，那么奶牛们总共进行一步就回到了同样的顺序。如果 $A=(2,3,1,5,4)$，那么奶牛们总共进行六步之后回到起始的顺序。每步之后奶牛们从左往右的顺序如下：

0 步：$(1,2,3,4,5)$  
1 步：$(3,1,2,5,4)$  
2 步：$(2,3,1,4,5)$  
3 步：$(1,2,3,5,4)$  
4 步：$(3,1,2,4,5)$  
5 步：$(2,3,1,5,4)$  
6 步：$(1,2,3,4,5)$  
**请你计算出所有可能的 $N!$ 种长为 $N$ 的排列 $A$ 回到起始顺序需要的步数的乘积。**

由于这个数字可能非常大，输出答案模 $M$ 的余数（$10^8\le M\le 10^9+7$，$M$ 是质数）。

-----

使用 C++ 的选手可以使用 [KACTL](https://github.com/kth-competitive-programming/kactl/blob/master/content/various/FastMod.h) 中的这一代码。这一名为 [Barrett 模乘](https://en.wikipedia.org/wiki/Barrett_reduction) 的算法可以以比通常计算快上数倍的速度计算 $a \% b$，其中 $b>1$ 为一个编译时未知的常数。（不幸的是，我们没有找到对于 Java 的这样的优化）。（译注：中文选手可以参考 几种取模优化方法[（译自 min-25 的博客）](https://loj.ac/article/327)）
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2);

int main() {
    int M = 1000000007; F = FastMod(M);
    ull x = 10ULL*M+3; 
    cout << x << " " << F.reduce(x) << "\n"; // 10000000073 3
}
```
## 输入格式

输入一行包含 $N$ 和 $M$。
## 输出格式

输出一个整数。
## 样例

### 样例输入 #1
```
5 1000000007
```
### 样例输出 #1
```
369329541
```
## 提示

#### 样例解释：
对于每一个 $1\le i\le N$，以下序列的第 $i$ 个元素等于奶牛需要使用 $i$ 步的排列数量：$[1,25,20,30,24,20]$。所以答案等于 $1^1\cdot 2^{25}\cdot 3^{20}\cdot 4^{30}\cdot 5^{24}\cdot 6^{20}\equiv 369329541\pmod{10^9+7}$。

**注意：这个问题的内存限制增加为 512 MB。**

---
对于 $100\%$ 的数据，满足 $1\le N\le 7500$。

共 $16$ 个测试点，其中 $1$ 为样例，其余性质如下：

测试点  $2$ 满足 $N=8$。  
测试点 $3\sim 5$ 满足 $N\le 50$。  
测试点 $6\sim 8$ 满足 $N\le 500$。  
测试点 $9\sim 12$ 满足 $N\le 3000$。  
测试点 $13\sim 16$ 没有额外限制。

----
  
出题人：Benjamin Qi


---

---
title: "[USACO20OPEN] Circus P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6277
tag: ['2020', 'USACO', '连通块', '组合数学', '容斥原理', 'Ad-hoc']
---
# [USACO20OPEN] Circus P
## 题目描述

Farmer John 马戏团中的 $N$ 头奶牛正在为即将到来的演出做准备。演出全部在一棵节点编号为 $1\ldots N$ 的树上举行。演出的“初始状态”被定义为一个整数 $K$（$1\leq K\leq N$）使得奶牛 $1\ldots K$ 分布在树上的节点上，并且没有任何两头牛位于相同的节点。

在一场演出中，奶牛们可以“移动”任意次数。在一次“移动”中，一头奶牛可以从自己当前所处的节点移动到一个未被占据的相邻节点。如果一个状态可以通过一系列移动到达另一个状态，我们就称这两个初始状态是等价的。

对于每一个 $1\leq K\leq N$，你需要帮助奶牛确定有多少类等价的初始状态。即选出最多的起始状态数目，使得它们两两不等价。由于数字可能很大，所以只需输出答案 $\bmod \ 10^9+7$ 的结果。



## 输入格式

第一行一个整数 $N$。

接下来的 $N-1$ 行，每行两个整数 $a_i,b_i$，表示树中有一条连接 $a_i$ 和 $b_i$ 的边。
## 输出格式

输出共 $N$ 行，对于每一个 $1\leq i\leq N$，在第 $i$ 行输出 $K=i$ 时的答案 $\bmod \ 10^9+7$ 的结果。
## 样例

### 样例输入 #1
```
5
1 2
2 3
3 4
3 5
```
### 样例输出 #1
```
1
1
3
24
120
```
### 样例输入 #2
```
8
1 3
2 3
3 4
4 5
5 6
6 7
6 8
```
### 样例输出 #2
```
1
1
1
6
30
180
5040
40320
```
## 提示

#### 样例 $1$ 解释：
对于 $K=1$ 和 $K=2$，任何两个状态都可以互相到达。

然后考虑 $K=3$，令 $c_i$ 表示奶牛 $i$ 的位置，则状态 $(c_1,c_2,c_3)=(1,2,3)$ 等价于状态 $(1,2,5)$ 和 $(1,3,2)$，但不等价于状态 $(2,1,3)$。

-----

对于 $100\%$ 的数据，保证 $1 \le N \le 10^5$。

共 $20$ 个测试点，其中 $1\sim 2$ 为样例，其余性质如下：

对于测试点 $3 \sim 4$，满足 $N \leq 8$。  
对于测试点 $5 \sim 7$，满足 $N \leq 16$。  
对于测试点 $8 \sim 10$，满足 $N \leq 100$，且这个树为“星形”，最多有一个度数大于 $2$ 的节点。  
对于测试点 $11 \sim 15$，满足 $N \leq 100$。  
对于测试点 $16 \sim 20$，无特殊限制。

------

出题人：Dhruv Rohatgi


---

---
title: "How Many of Them"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6596
tag: ['动态规划 DP', '组合数学', '生成函数']
---
# How Many of Them
## 题目描述

在无向连通图中，若一条边被删除后，图会分成不连通的两部分，则称该边为割边。

求满足如下条件的无向连通图的数量：

1. 由 $n$ 个结点构成，结点有标号。

2. 割边不超过 $m$ 条。

3. 没有重边和自环。

答案对 $10^{9}+7$ 取模。
## 输入格式

仅一行，两个整数 $n$ 和 $m$。
## 输出格式

一个整数，表示答案。
## 样例

### 样例输入 #1
```
3 3
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5 1
```
### 样例输出 #2
```
453
```
## 提示

$2≤n≤50,0≤m≤\dfrac{n(n-1)}{2}$

Source: Gennady Korotkevich (tourist), ITMO University.


---

---
title: "[SNOI2020] 生成树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6790
tag: ['树形数据结构', '2020', '各省省选', '组合数学']
---
# [SNOI2020] 生成树
## 题目描述

给定无向连通图 $G$，已知 $G$ 在删掉一条边后是一颗仙人掌（仙人掌：不存在两个拥有公共边的简单环的无向联通图），求 $G$ 的生成树个数。结果对 $998244353$ 取模。
## 输入格式

第一行两个整数 $n,m$，表示图 $G$ 的点数和边数。

接下来 $m$ 行，每行两个用空格分隔的正整数 $u,v(1 \le u,v  \le n)$，表示边 $(u,v)\in G$。
## 输出格式

输出一行一个整数，表示图 $G$ 的生成树个数对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
4 5
1 2
1 3
2 3
2 4
3 4
```
### 样例输出 #1
```
8
```
## 提示

对于所有数据，$1 \le n \le m \le2 \times 10^5$。

- 对于 $10\%$ 的数据，$1 \le n=m \le 2000$。
- 对于另外 $40\%$ 的数据，$1 \le n,m \le 10^5$ 且 $G$ 本身是仙人掌。
- 对于余下 $50\%$ 的数据，无特殊限制。


---

---
title: "[W1] 推"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7101
tag: ['计算几何', 'O2优化', '组合数学']
---
# [W1] 推
## 题目背景

一个”点集“为一个二维平面上的整点组成的**多重**集合。  
可以从一个点集构造一个三角形当且仅当这个三角形的所有顶点在该点集里面。  
从一个点集 $S$ 里可以构造恰好 $|S|^3$ 个三角形。（可能一些三角形会退化为一条面积为 0 的线段）
## 题目描述

有一个点集，初始为空集。  
有 $N$ 个操作，在每一个操作，会从这个点集插入或删除一个点。每一步完成后，询问这个点集可构造的所有三角形面积 *__八次方__* 之和。

所有询问答案都可以表示为 $a/b$，其中 $a$ 和 $b$ 互质。输出 $a\cdot b^{-1}\pmod{998244353}$。
## 输入格式

第一行一个正整数 $N$，表示接下来的步骤个数。  
接下来 $N$ 行，每一行三个正整数 $t,x,y$。  
如果 $t=1$，则插入 $(x,y)$ 这个点；如果 $t=2$ 则删除 $(x,y)$ 这个点。
## 输出格式

一共 $N$ 行，第 $i$ 行一个正整数，表示第 $i$ 个步骤完成之后的询问答案。
## 样例

### 样例输入 #1
```
7
1 0 0
1 0 1
1 2 0
2 2 0
1 4 0
2 4 0
1 6 0
```
### 样例输出 #1
```
0
0
1
0
256
0
6561
```
### 样例输入 #2
```
5
1 0 0
1 0 1
1 1 0
1 1 1
2 0 1
```
### 样例输出 #2
```
0
0
994344961
982646785
994344961
```
## 提示

对于 $10\%$ 的数据，$N\le10$；  
对于 $30\%$ 的数据，$N\le10^3$；  
对于另外 $10\%$ 的数据，没有删除步骤；  
对于 $100\%$ 的数据，$1\le N\le10^5,0\le x,y<998244353$，任何删除的点都保证原来存在。


---

---
title: "[W1] 算"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7102
tag: ['数学', 'O2优化', '组合数学', '快速数论变换 NTT']
---
# [W1] 算
## 题目描述

有一个 $m$ 项多项式 $p(x)$ 以及两个参数 $c$ 和 $t$，其中 $p(x)=a_0+a_1x+\dots+a_{m-1}x^{m-1}$。  
定义一个新函数 $s(n)$:
$$s(n)=\sum_{i=1}^np(i)[\gcd(i,n)=1]\bmod 998244353$$
请计算 $s(c),s(c^2),\dots,s(c^t)$。
## 输入格式

第一行三个正整数，分别表示 $m,c,t$。  
第二行 $m$ 个正整数，表示 $a_0,a_1,\dots,a_{m-1}$。
## 输出格式

输出 $t$ 行，第 $i$ 行一个正整数 $s(c^i)$。
## 样例

### 样例输入 #1
```
8 10 4
3 1 4 1 5 9 2 6
```
### 样例输出 #1
```
35683652
171899188
780914481
858211065
```
## 提示

对于 $10\%$ 的数据，$t\le2,c\le100$;  
对于 $30\%$ 的数据，$t\le1000,m\le1000$；  
对于 $50\%$ 的数据，$t\le5\cdot10^4,m\le5\cdot10^4,c\le10^{12}$；  
对于另外 $10\%$ 的数据，$c=123456789$；  
对于所有数据，$1\le t\le2\cdot10^5,1\le m\le2\cdot10^5,1\le c\le10^{18}$。


---

---
title: "[USACO20DEC] Spaceship P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7155
tag: ['动态规划 DP', '2020', 'USACO', 'O2优化', '组合数学']
---
# [USACO20DEC] Spaceship P
## 题目描述

奶牛 Bessie 外星人绑架了，现在被关在了一艘外星人的飞船里！飞船有 $N$（$1≤N≤60$）间房间，编号为 $1…N$，其中某些房间之间由单向通过的门所连接（由于使用了奇怪的外星技术，一扇门甚至可能从一间房间通回这间房间本身！）。然而，没有两扇门具有完全相同的出发和到达房间。此外，Bessie 有一个遥控器，上有编号为 $1…K$ （$1≤K≤60$）的按钮。

如果 Bessie 能够完成一个怪异的任务，外星人就会释放她。首先，他们会选择两间房间 $s$ 和 $t$（$1≤s,t≤N$），以及两个整数 $b_s$ 和 $b_t$（$1≤b_s,b_t≤K$）。他们会将 Bessie 放在房间 $s$ 内，并令她立刻按下按钮 $b_s$。然后 Bessie 需要继续在飞船内穿梭，同时按下按钮。有一些 Bessie 的行动需要遵守的规则：

 - 在每间房间内，在按下恰好一个按钮后，她必须选择从某扇门离开去往另一间房间（可能会回到同一间房间）或停止行动。
 - 一旦 Bessie 按下某个按钮，她再次按下这个按钮即为非法，除非在此之间她按下过编号更大的按钮。换句话说，按下编号为 x 的按钮会使得这个按钮变为非法，同时所有编号 $<x$ 的按钮会被重置为合法。
 - 如果 Bessie 按下非法的按钮，任务即失败，外星人就会把她关起来。 

仅当 Bessie 停止行动时位于房间 $t$，她最后按下的按钮是 $b_t$，并且没有按下过非法按钮时，Bessie 才会被释放。

Bessie 担心她可能无法完成这一任务。对于 $Q$
（$1≤Q≤60$）个询问，每个询问包含一组 Bessie 认为可能的 $s,t,b_s$ 以及 $b_t$，Bessie 想要知道可以使她得到释放的通过房间与按键序列的数量。由于答案可能非常大，输出对 $10^9+7$ 取模的结果。 
## 输入格式

输入的第一行包含 $N,K,Q$。

以下 $N$ 行每行包含 $N$ 个二进制位（$0$ 或 $1$）。如果从房间 $i$ 到房间 $j$ 存在一扇门，则第 $i$ 行的第 $j$ 位为 1，如果没有这样的门则为 0。

以下 $Q$ 行，每行包含四个整数 $b_s$、$s$、$b_t$、$t$，分别表示起始按钮、起始房间、结束按钮、结束房间。 
## 输出格式

对 $Q$ 个询问的每一个，在一行内输出操作序列的数量模 $10^9+7$ 的结果。 
## 样例

### 样例输入 #1
```
6 3 8
010000
001000
000100
000010
000000
000001
1 1 1 1
3 3 1 1
1 1 3 3
1 1 1 5
2 1 1 5
1 1 2 5
3 1 3 5
2 6 2 6

```
### 样例输出 #1
```
1
0
1
3
2
2
0
5
```
### 样例输入 #2
```
6 4 6
001100
001110
101101
010111
110111
000111
3 2 4 3
3 1 4 4
3 4 4 1
3 3 4 3
3 6 4 3
3 1 4 2
```
### 样例输出 #2
```
26
49
29
27
18
22
```
### 样例输入 #3
```
6 10 5
110101
011001
001111
101111
111010
000001
2 5 2 5
6 1 5 2
3 4 8 3
9 3 3 5
5 1 3 4
```
### 样例输出 #3
```
713313311
716721076
782223918
335511486
539247783
```
## 提示

门连接了房间 $1→2$、$2→3$、$3→4$、$4→5$ 以及 $6→6$。

对于第一个询问，Bessie 必须在按下第一个按钮后立刻停止行动。

对于第二个询问，答案显然为零，因为无法从房间 3 前往房间 1。

对于第三个询问，Bessie 的唯一选择是从房间 1 移动到房间 2 到房间 3，同时按下按钮 1、2 和 3。

对于第四个询问，Bessie 的移动方式是唯一的，她有三种可能的按键序列：

 - (1,2,3,2,1)
 - (1,2,1,3,1)
 - (1,3,1,2,1)

对于最后一个询问，Bessie 有五种可能的按键序列：

 - (2)
 - (2,3,2)
 - (2,3,1,2)
 - (2,1,3,2)
 - (2,1,3,1,2)

### 测试点性质：

 - 测试点 4-7 中，$K≤5$ 且 $(b_s,s)$ 在所有询问中均相同。
 - 测试点 8-11 中，对所有询问有 $b_s=K−1$ 以及 $b_t=K$。
 - 测试点 12-15 中，$N,K,Q≤20$。
 - 测试点 16-23 没有额外限制。

供题：Benjamin Qi 


---

---
title: "[USACO20DEC] Cowmistry P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7156
tag: ['动态规划 DP', '2020', 'USACO', 'O2优化', '数位 DP', '组合数学', '字典树 Trie']
---
# [USACO20DEC] Cowmistry P
## 题目描述

Bessie 的化学作业已经拖了很久，现在需要你的帮助！她需要用三种不同的化学品制造一种混合物。所有聪明的奶牛都知道，某些化学品之间不能进行混合，否则会产生爆炸。具体地说，两种标号为 $a$ 和 $b$ 的化学品当 $a⊕b≤K$ （$1≤K≤10^9$） 时可以出现在同一种混合物中。

注：这里，$a⊕b$ 表示非负整数 $a$ 与 $b$ 的「异或」。这一运算等价于在二进制下将每一对应位相加并且舍弃进位。例如， 
$$0⊕0=1⊕1=0$$
，
$$1⊕0=0⊕1=1$$
，
$$5⊕7=101_2⊕111_2=010_2=2$$
。

Bessie 有 $N$ 盒化学品，第 $i$ 个盒子内有标号从 $l_i$ 到 $r_i$ 的化学品（$0≤l_i≤r_i≤10^9$）。没有两个盒子中含有同一种化学品。她想要知道她可以得到多少种由三种不同的化学品混合而成的混合物。如果至少一种化学品出现在一种混合物中而没有出现在另一种中，则认为这两种混合物是不同的。由于答案可能非常大，输出对 $10^9+7$ 取模的结果。 
## 输入格式

输入的第一行包含两个整数 $N$ 和 $K$。

以下 $N$ 行，每行包含两个空格分隔的整数 $l_i$ 和 $r_i$。保证所有化学品盒子按其中内容的升序给出；也就是说，对所有 $1≤i<N$ 有 $r_i<l_{i+1}$。 
## 输出格式

输出 Bessie 可以由三种不同化学品制造的混合物的数量，对 $10^9+7$ 取模。 
## 样例

### 样例输入 #1
```
1 13
0 199
```
### 样例输出 #1
```
4280
```
### 样例输入 #2
```
6 147
1 35
48 103
125 127
154 190
195 235
240 250
```
### 样例输出 #2
```
267188
```
## 提示

我们可以将所有化学品分为不能交叉混合的 $13$ 组：$(0 \ldots 15)$，$(16 \ldots 31)$，… $(192 \ldots 199)$。前 $12$ 组每组贡献了 $352$ 种混合物，最后一组贡献了 $56$ 种（因为所有 $\binom{8}{3}$ 种 $(192 \ldots 199)$ 中三种不同化学品的组合均可行），总共为 $352 \cdot 12 + 56 = 4280$。 

 - 测试点 3-4 满足 $\max(K, r_N) \le {10}^4$。
 - 测试点 5-6 对某个 $k \ge 1$ 满足 $K = 2^k - 1$。
 - 测试点 7-11 满足 $\max(K, r_N) \le {10}^6$。
 - 测试点 12-16 满足 $N \le 20$。
 - 测试点 17-21 没有额外限制。

对于所有测试点，满足 $1 \le N \le 2 \times {10}^4$。

供题：Benjamin Qi 


---

---
title: "「EZEC-5」「KrOI2021」Chasse Neige"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7289
tag: ['动态规划 DP', '数学', '递推', 'O2优化', '组合数学', '排列组合', '生成函数', '微积分', '积分', '级数', '快速傅里叶变换 FFT', '快速数论变换 NTT', '洛谷月赛']
---
# 「EZEC-5」「KrOI2021」Chasse Neige
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/kben34ml.png)

『我喜欢雪。』

『之前虽然讨厌寒冷，现在却是最喜欢了。』

![](https://cdn.luogu.com.cn/upload/image_hosting/sbuj1tnc.png)
## 题目描述

Rikka 给了你 $T$ 组询问，每组询问给定两个正整数 $n,k$，你需要告诉 Rikka 有多少个长度为 $n$ 的排列 $\pi$ 满足如下条件：

- $\pi_1<\pi_2$

- $\pi_{n-1}>\pi_{n}$

- 恰好存在 $k$ 个位置 $i(2\leq i\leq n-1)$ 满足 $\pi_{i-1}<\pi_{i}$ 且 $\pi_{i}>\pi_{i+1}$。

答案对 $998244353$ 取模。
## 输入格式

第一行两个整数 $T,r$，表示询问次数以及 $n$ 的值域。

接下来 $T$ 行，每行两个整数 $n,k$，意义如题意所示。
## 输出格式

$T$ 行，每行一个正整数，表示答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
2 10
3 1
5 2
```
### 样例输出 #1
```
2
16
```
## 提示

### 样例解释 1

对于第一组询问，$n=3,k=1$，$(1,3,2)$ 和 $(2,3,1)$ 均满足条件，答案为 $2$。

对于第二组询问，满足条件的排列为：

$$(1,3,2,5,4),(1,4,2,5,3),(1,4,3,5,2),(1,5,2,4,3),(1,5,3,4,2)\\(2,3,1,5,4),(2,4,1,5,3),(2,4,3,5,1),(2,5,1,4,3),(2,5,3,4,1)\\(3,4,1,5,2),(3,4,2,5,1),(3,5,1,4,2),(3,5,2,4,1),(4,5,1,3,2),(4,5,2,3,1)$$

共 $16$ 个，所以答案为 $16$。

### 数据范围

| 子任务编号 | 分值 | $T\leq $ | $r\leq $ | 其他限制 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| Subtask 1 | $1$ | $1$ | $10$ |  |
| Subtask 2 | $5$ | $2\times 10^5$ | $10$ |  |
| Subtask 3 | $13$ | $1$ | $2\times 10^3$ |  |
| Subtask 4 | $13$ | $2\times 10^5$ | $2\times 10^3$ |  |
| Subtask 5 | $16$ | $2\times 10^5$ | $2\times 10^5$ | $k=\lfloor\frac{n-1}{2}\rfloor$ 且 $n$ 为奇数 |
| Subtask 6 | $16$ | $2\times 10^5$ | $2\times 10^5$ | $k=\lfloor\frac{n-1}{2}\rfloor-1$ |
| Subtask 7 | $36$ | $2\times 10^5$ | $2\times 10^5$ |  |

对于 $100\%$ 的数据，$1\leq T\leq 2\times 10^5,3\leq n\leq r\leq 2\times 10^5,\max(1,\lfloor\frac{n-1}{2}\rfloor-10)\leq k\leq \lfloor\frac{n-1}{2}\rfloor$。





---

---
title: "「EZEC-5」「KrOI2021」Chasse Neige 加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7292
tag: ['动态规划 DP', '数学', '递推', 'O2优化', '组合数学', '排列组合', '生成函数', '微积分', '积分', '级数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 「EZEC-5」「KrOI2021」Chasse Neige 加强版
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/kben34ml.png)

『我喜欢雪。』

『之前虽然讨厌寒冷，现在却是最喜欢了。』

![](https://cdn.luogu.com.cn/upload/image_hosting/sbuj1tnc.png)
## 题目描述

**本题与原题的区别是 $r$ 的范围扩大了，应该能卡掉 $O(n\log^2n)$ 的分治 FFT 做法，如果有分治 FFT 能过请联系我。同时，如果你的做法是 $O(n\log n)$ 的话，请注意常数优化。**

Rikka 给了你 $T$ 组询问，每组询问给定两个正整数 $n,k$，你需要告诉 Rikka 有多少个长度为 $n$ 的排列 $\pi$ 满足如下条件：

- $\pi_1<\pi_2$

- $\pi_{n-1}>\pi_{n}$

- 恰好存在 $k$ 个位置 $i(2\leq i\leq n-1)$ 满足 $\pi_{i-1}<\pi_{i}$ 且 $\pi_{i}>\pi_{i+1}$。

答案对 $998244353$ 取模。
## 输入格式

第一行两个整数 $T,r$，表示询问次数以及 $n$ 的值域。

接下来 $T$ 行，每行两个整数 $n,k$，意义如题意所示。
## 输出格式

$T$ 行，每行一个正整数，表示答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
2 10
3 1
5 2
```
### 样例输出 #1
```
2
16
```
## 提示

### 样例解释 1

对于第一组询问，$n=3,k=1$，$(1,3,2)$ 和 $(2,3,1)$ 均满足条件，答案为 $2$。

对于第二组询问，满足条件的排列为：

$$(1,3,2,5,4),(1,4,2,5,3),(1,4,3,5,2),(1,5,2,4,3),(1,5,3,4,2)\\(2,3,1,5,4),(2,4,1,5,3),(2,4,3,5,1),(2,5,1,4,3),(2,5,3,4,1)\\(3,4,1,5,2),(3,4,2,5,1),(3,5,1,4,2),(3,5,2,4,1),(4,5,1,3,2),(4,5,2,3,1)$$

共 $16$ 个，所以答案为 $16$。

### 数据范围

对于 $100\%$ 的数据，$1\leq T\leq 2\times 10^5,3\leq n\leq r\leq 10^6,\max(1,\lfloor\frac{n-1}{2}\rfloor-10)\leq k\leq \lfloor\frac{n-1}{2}\rfloor$。


---

---
title: "[USACO21JAN] Sum of Distances P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7293
tag: ['动态规划 DP', '线段树', 'USACO', '2021', 'O2优化', '组合数学', '容斥原理', '扫描线']
---
# [USACO21JAN] Sum of Distances P
## 题目描述

Bessie 有一些无向连通图 $G_1,G_2,…,G_K$（$2≤K≤5⋅10^4$）。对于每一个 $1≤i≤K$，$G_i$ 有 $N_i$（$N_i≥2$）个编号为 $1…N_i$ 的结点与 $M_i$（$M_i≥N_i−1$）条边。$G_i$ 可能含有自环，但同一对结点之间不会存在多条边。 现在 Elsie 用 $N_1⋅N_2⋯N_K$ 个结点建立了一个新的无向图 $G$，每个结点用一个 $K$ 元组 $(j_1,j_2,…,j_K)$ 标号，其中 $1≤j_i≤N_i$。若对于所有的 $1≤i≤K$，$j_i$ 与 $k_i$ 在 $G_i$ 中连有一条边，则在 $G$ 中结点 $(j_1,j_2,…,j_K)$ 和 $(k_1,k_2,…,k_K)$ 之间连有一条边。 定义 $G$ 中位于同一连通分量的两个结点的 *距离* 为从一个结点到另一个结点的路径上的最小边数。计算 $G$ 中结点 $(1,1,…,1)$ 与所有与其在同一连通分量的结点的距离之和，对 $10^9+7$ 取模。
## 输入格式

输入的第一行包含 $K$，为图的数量。

每个图的描述的第一行包含 $N_i$ 和 $M_i$，以下是 $M_i$ 条边。

为提高可读性，相邻的图之间用一个空行隔开。输入保证 $∑N_i≤10^5$ 以及 $∑M_i≤2⋅10^5$。
## 输出格式

输出结点 $(1,1,…,1)$ 与所有该结点可以到达的结点的距离之和，对 $10^9+7$ 取模。


## 样例

### 样例输入 #1
```
2

2 1
1 2

4 4
1 2
2 3
3 4
4 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3

4 4
1 2
2 3
3 1
3 4

6 5
1 2
2 3
3 4
4 5
5 6

7 7
1 2
2 3
3 4
4 5
5 6
6 7
7 1
```
### 样例输出 #2
```
706
```
## 提示

#### 样例 1 解释

$G$ 包含 $2⋅4=8$ 个结点，其中 $4$ 个结点不与结点 $(1,1)$ 连通。有 $2$ 个结点与 $(1,1)$ 的距离为 $1$，$1$ 个结点的距离为 $2$。所以答案为 $2⋅1+1⋅2=4$。 

#### 样例 2 解释

$G$ 包含 $4⋅6⋅7=168$ 个结点，均与结点 $(1,1,1)$ 连通。对于每一个 $i∈[1,7]$，与结点 $(1,1,1)$ 距离为 $i$ 的结点数量为下列数组中的第 $i$ 个元素：$[4,23,28,36,40,24,12]$。

#### 测试点特性

 - 测试点 $3-4$ 满足 $∏N_i≤300$。
 - 测试点 $5-10$ 满足 $∑N_i≤300$。
 - 测试点 $11-20$ 没有额外限制。

供题：Benjamin Qi 


---

---
title: "更简单的排列计数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7438
tag: ['动态规划 DP', '数学', '递推', 'O2优化', '置换', '组合数学', '排列组合', '前缀和', '二项式定理', '生成函数', '线性递推', '微积分', '导数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 更简单的排列计数
## 题目描述

设 $\text{cyc}_\pi$ 将长为 $n$ 的排列 $\pi$ 当成置换时所能分解成的循环个数。给定两个整数 $n,k$ 和一个 $k-1$ 次多项式，对 $1\leq m\leq n$ 求：

$$
\sum\limits_{\pi}F(\text{cyc}_{\pi})
$$

其中 $\pi$ 是长度为 $m$ 且不存在位置 $i$ 使得 $\pi_i=i$ 的排列。
## 输入格式

第一行两个整数，表示 $n$ 和 $k$。

第二行 $k$ 个整数，从低到高给出多项式的系数。
## 输出格式

一行 $n$ 个整数，表示答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
3 2
0 1
```
### 样例输出 #1
```
0 1 2
```
### 样例输入 #2
```
6 4
11 43 27 7
```
### 样例输出 #2
```
0 88 176 1311 7332 53070
```
## 提示

### 样例解释 1

下面是当 $m=1,2,3$ 时满足要求的所有排列：

$\text{cyc}_{(2,1)}=1,\text{cyc}_{(2,3,1)}=1,\text{cyc}_{(3,1,2)}=1$。
所以当 $m=1$ 时答案为 $0$，$m=2$ 时为 $1$，$m=3$ 时为 $2$。

### 数据范围

| 子任务编号 | 分值 | $n\leq$ | $k\leq$ | 其他限制 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| Subtask 1 | $1$ | $10$ | $6$ |  |
| Subtask 2 | $5$ | $2\times 10^3$ | $6$ |  |
| Subtask 3 | $6$ | $2\times 10^5$ | $1$ |  |
| Subtask 4 | $16$ | $2\times 10^5$ | $6$ | $F(x)=x^k$ |
| Subtask 5 | $16$ | $2\times 10^5$ | $3$ |  |
| Subtask 6 | $56$ | $6\times 10^5$ | $100$ |  |

对于 $100\%$ 的数据，$1\leq n\leq 6\times 10^5$，$1\leq k\leq 100$，$0\leq [x^k]F(x)\leq 998244352$。


---

---
title: "「KrOI2021」Feux Follets 弱化版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7439
tag: ['动态规划 DP', '数学', '递推', 'O2优化', '置换', '组合数学', '排列组合', '二项式定理', '生成函数', '微积分', '导数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 「KrOI2021」Feux Follets 弱化版
## 题目描述

设 $\text{cyc}_\pi$ 将长为 $n$ 的排列 $\pi$ 当成置换时所能分解成的循环个数。给定两个整数 $n,k$ 和一个 $k-1$ 次多项式，求：

$$
\sum\limits_{\pi}F(\text{cyc}_{\pi})
$$

其中 $\pi$ 是长度为 $n$ 且不存在位置 $i$ 使得 $\pi_i=i$ 的排列。
## 输入格式

第一行两个整数，表示 $n$ 和 $k$。

第二行 $k$ 个整数，从低到高给出多项式的系数。
## 输出格式

一行一个整数，表示答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
3 2
0 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 4
11 43 27 7
```
### 样例输出 #2
```
53070
```
### 样例输入 #3
```
6 4
9 72 22 7
```
### 样例输出 #3
```
60990
```
## 提示

### 数据范围

对于 $100\%$ 的数据，$1\leq n,k\leq 10^5$。


---

---
title: "「KrOI2021」Feux Follets"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7440
tag: ['动态规划 DP', '数学', '递推', '矩阵运算', 'O2优化', '矩阵加速', '置换', '组合数学', '排列组合', '生成函数', '线性代数', '矩阵乘法', '线性递推', '微积分', '导数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 「KrOI2021」Feux Follets
## 题目描述

设 $\text{cyc}_\pi$ 将长为 $n$ 的排列 $\pi$ 当成置换时所能分解成的循环个数。给定两个整数 $n,k$ 和一个 $k-1$ 次多项式，对 $1\leq m\leq n$ 求：

$$
\sum\limits_{\pi}F(\text{cyc}_{\pi})
$$

其中 $\pi$ 是长度为 $m$ 且不存在位置 $i$ 使得 $\pi_i=i$ 的排列。
## 输入格式

第一行两个整数，表示 $n$ 和 $k$。

第二行 $k$ 个整数，从低到高给出多项式的系数。
## 输出格式

一行 $n$ 个整数，表示答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
3 2
0 1
```
### 样例输出 #1
```
0 1 2
```
### 样例输入 #2
```
6 4
11 43 27 7
```
### 样例输出 #2
```
0 88 176 1311 7332 53070
```
### 样例输入 #3
```
6 4
9 72 22 7
```
### 样例输出 #3
```
0 110 220 1551 8580 60990
```
## 提示

### 数据范围

对于 $100\%$ 的数据，$1\leq n,k\leq 10^5$。


---

---
title: "「MCOI-06」Lost Desire"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7890
tag: ['数学', '2021', 'Special Judge', 'O2优化', '哈希 hashing', '素数判断,质数,筛法', '最大公约数 gcd', '莫比乌斯反演', '组合数学', '随机化', '洛谷月赛']
---
# 「MCOI-06」Lost Desire
## 题目背景

頰滴る　紅い涙

不安定な視界の中

差し出した手を取れたら

あぁ…そんな世界を夢みた

-------

哭いて…

激しく  燃やした 黒い感情 

届かぬ この手に

Cry 闇の中で

最果てから 光へ手を翳して

揺らいだ想いさえも 闇の奥底へ堕ちてく

[网易云本曲试听链接](https://music.163.com/song?id=1809745288&userid=1399272307)
## 题目描述

设正整数 $n, m$ 互质，$k$ 为整数，定义函数 $F(n, m, k)$ 为小于 $\displaystyle m+n$ 的正整数集合 $\{1, 2, \cdots, m + n - 1\}$ 中，所有满足 $\displaystyle\sum_{x \in S} x \equiv k \pmod n$ 的 $m$ 元子集 $S$ 的个数。

现给定正整数 $N, M, K$，求所有 $F(i,j,x)$ 之积，使得 $1\le i\le N$，$1\le j\le M$，$1\le x\le K$，并且 $i$ 与 $j$ 互质。

由于结果很大，所以你只需要求出结果对特定素数 $p$ 取模的值。

**同时请注意实现程序时常数因子带来的影响。**
## 输入格式

**本题多测。** 每个测试点共有 $T$ 组数据。

第一行两个正整数 $T,p$ 。

接下来 $T$ 行，每行三个正整数 $N, M, K$，由空格分开。
## 输出格式

对于每组数据：一行，一个整数，表示所求的值（对 $p$ 取模）。

## 样例

### 样例输入 #1
```
3 1926195307
2 3 3
3 3 3
5 6 1
```
### 样例输出 #1
```
8
64
363031200
```
## 提示

本题采用捆绑测试，分 $5$ 个 Subtask 。

+ 对于 Subtask 1 ~~(Tutorial)~~：
  + $T=1$
  + $1\leq N,M,K\leq 6$
  + $p=10^9+7$。
+ 对于 Subtask 2 ~~(PST 4.0)~~：
  + $T=1$
  + $1\leq N,M,K\leq200$
  + $p=10^9+7$。
+ 对于 Subtask 3 ~~(PRS 7.5)~~：
  + $T=100$
  + $1\leq N,M,K\leq 1000$
  + $p=10^9+7$。
+ 对于 Subtask 4 ~~(FTR 9.8)~~：
  + $T=10^3$
  + $1 \leq N,M,K\le 10^5$
  + $10^9\le p\le2\times10^9$。
+ 对于 Subtask 5 ~~(BYD 11.0)~~：
  + $T=9999$
  + $1 \leq N,M,K\le 5\times10^5$
  + $10^9\le p\le2\times10^9$。

Subtask $1\sim5$ 的分值分别为 $5,7,11,17,60$ 。

特别的，假设您在一个测试点中前 $x$ 个询问正确，则您得该测试点的分值的 $\left\lfloor100\times\sqrt\dfrac{x}{T}\right\rfloor\%$ 分。您在任何一个 Subtask 的得分则为对应 Subtask 中所有测试点得分的最小值。

特别的，**TLE 一律不得分。**（无需补满未在时间范围内解决的测试点的答案，会导致奇怪的错误。）

**再次提醒注意实现程序时常数因子带来的影响。**

---

Idea: Powerless Std&Data: w33z （Data was corrected on 2021.10.05）

Sub4 added by Prean, Sub 5 by w33z.

This problem was added on 2021.10.01. Thanks for their help.

2021.10.01 - 2021.12.07 : 68 days 1st kill (Leasier).

2021.10.01 - 2022.01.21 : 113 days 2nd kill (wkywkywky).

2021.10.01 - 2022.02.26 : 149 days 3rd kill (NaNH2).


---

---
title: "[Cnoi2021] 六边形战士"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8114
tag: ['2021', 'LGV 引理', 'O2优化', '组合数学', '线性代数', '行列式']
---
# [Cnoi2021] 六边形战士
## 题目背景

在 Cirno 的精心照料下，六边形成长为一只可爱的平行六边形。

现在，Cirno 很想知道它的战斗力是多少。
## 题目描述

可爱的平行六边形所有边的夹角均为 $\frac{2\pi}{3}$，三组对边的长度分别为 $a$，$b$，$c$ 个单位。如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/aa8i6soa.png)

在战斗力鉴定时，鉴定师会以六边形的每一条边所在的直线，间隔 $\frac{\sqrt{3}}{2}$ 个单位建立平行直线系。这样六边形战士会被划分成若干个正三角形。如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/mbkn807n.png)

鉴定师会将所有有公共边的正三角形连边。由于没有奇环，很容易知道这是一个二分图。然后鉴定师会试图构造该二分图的完美匹配。如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/in7c6cf7.png)

该六边形战士的战斗力为上述**二分图的完美匹配**可能的种类数。作为见习鉴定师，你需要帮 Cirno 求出该六边形的战斗力。

由于答案可能过大，仅需输出它对 $998244353$ 取模的结果即可。
## 输入格式

一行，三个整数，用空格隔开，表示 $a$，$b$，$c$。
## 输出格式

一行，一个整数，表示六边形战士的战斗力对 $998244353$ 取模后的结果。
## 样例

### 样例输入 #1
```
1 1 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 4 3
```
### 样例输出 #2
```
4116
```
## 提示

**数据范围与约定**

对于 $100\%$ 的数据，保证 $1\le a,b,c\le 10^6$。

**子任务**

Subtask1（$10$ points）：$a,b,c\le 3$。

Subtask2（$10$ points）：$a,b,c\le 8$。

Subtask3（$70$ points）：$a,b,c\le 100$。

Subtask4（$10$ points）：无特殊限制。

**提示**

 - **Krattenthaler’s formula**  
 $\displaystyle\det\left(\prod\limits_{k=2}^j(x_i+a_k)\prod\limits_{k=j+1}^n(x_i+b_k)\right)_{i,j=1}^{n}=\prod\limits_{1\le i<j\le n}{(x_i-x_j)}\prod\limits_{2<i\le j\le n}(a_i-b_j)$。


---

---
title: "[ZJOI2022] 计算几何"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8333
tag: ['各省省选', '2022', '浙江', 'O2优化', '组合数学', '线性代数']
---
# [ZJOI2022] 计算几何
## 题目描述

九条可怜是一个喜欢计算几何的女孩子，她画了一个特别的平面坐标系，其中 $x$ 轴正半轴与 $y$ 轴正半轴夹角为 $60$ 度。

从中，她取出所有横纵坐标不全为偶数，且满足 $-2 a + 1 \le x \le 2 a - 1$，$-2 b + 1 \le y \le 2 b - 1$，$-2 c + 1 \le x + y \le 2 c - 1$ 的整点。

可怜想将其中一些点染色，但相邻的点不能同时染色。具体地，对于点 $(x, y)$，它和 $(x, y + 1), (x, y - 1), (x + 1, y), (x - 1, y), (x + 1, y - 1), (x - 1, y + 1)$ 六个点相邻，可结合样例解释理解。

可怜想知道在这个规则下最多能将多少点染色，以及染最多点的染色方案数。由于后者值可能很大，对于染色方案数，你只需要输出对 $998244353$ 取模后的结果。**注意不需要将最多染色点数取模。**
## 输入格式

第一行一个整数 $T$ 代表数据组数。

接下来 $T$ 行，每行三个整数 $a, b, c$ 代表一组数据。
## 输出格式

输出共 $T$ 行，每行两个整数，代表最多能染的点数（**不取模**）和方案数对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
6
2 1 2
1 1 137
3 94 95
3 1998 1996
998244 353999 999999
50 120 150

```
### 样例输出 #1
```
7 4
4 1
1124 31585548
23951 33873190
1289433675488 748596399
23600 480090154

```
## 提示

**【样例解释】**

如下图所示，点 $J$ 的坐标为 $(2, 1)$，点 $F$ 的坐标为 $(-1, 0)$，点 $H$ 的坐标为 $(2, 0)$。在这三个点中，只有点 $H$ 是横纵坐标全为偶数的点。图中与点 $A$ 距离为 $1$ 的点有 $B C D E F G$ 六个点。

在样例的第一组数据中，满足条件的整点有 $N G B I J P F C K M L E D S T$。

最多能染 $7$ 个点，方案共 $4$ 种，具体为：$P N L B D J T$，$R M F B D J T$，$R M G E C J T$，$R M G E I S K$。

在样例的第二组数据中，满足条件的整点有 $G B I F C L E D$。

最多能染 $4$ 个点，方案共 $1$ 种，具体为：$L G I D$。

![](https://cdn.luogu.com.cn/upload/image_hosting/a3lp43vq.png)

**【数据范围】**

对于所有测试点：$1 \le T \le 10$，$1 \le a, b, c \le {10}^6$。

每个测试点的具体限制见下表：

| 测试点编号 | $a \le$ | $b, c \le$ | 特殊限制 |
|:-:|:-:|:-:|:-:|
| $1$ | $3$ | $3$ | $a = b = c$ |
| $2$ | $4$ | $4$ | $a = b = c$ |
| $3$ | $4$ | $4$ | 无 |
| $4$ | $3$ | $100$ | 无 |
| $5 \sim 6$ | $3$ | $1000$ | 无 |
| $7 \sim 8$ | $3$ | $5000$ | 无 |
| $9 \sim 10$ | $100$ | $100$ | $a = b = c$ |
| $11 \sim 14$ | $100$ | $100$ | 无 |
| $15$ | ${10}^5$ | ${10}^5$ | $a = b = c$ |
| $16$ | ${10}^5$ | ${10}^5$ | 无 |
| $17 \sim 18$ | ${10}^6$ | ${10}^6$ | $a \cdot b \cdot c \le {10}^6$ |
| $19$ | ${10}^6$ | ${10}^6$ | $a = b = c$ |
| $20$ | ${10}^6$ | ${10}^6$ | 无 |


---

---
title: "心跳 加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8556
tag: ['数学', '多项式', '洛谷原创', 'O2优化', '组合数学', '线性递推', '洛谷月赛']
---
# 心跳 加强版
## 题目背景

本题为 [洛谷 9 月月赛 II & NR I. E. 心跳](/problem/P8554) 的加强版，唯一的区别在于数据范围改为 $n \le 5 \times {10}^6$。

---

“清晰的跳动声传达来的，重叠的声响和流动的思念。

约定再也不要分开吧，希望无论何时都不要让你寂寞。”

恋爱之时，人的心情不会一成不变，可喜悦和悲伤会随着时间流逝而归于平淡。最令人难忘的是那些“心动”的感觉，那些因未曾经历而喜出望外的感觉。因此，有些时候，失去某些特别美好的回忆，反而能让心动的感觉增多。可为此失去那些回忆，真的值得吗？
## 题目描述

赫尔德想对上面的问题进行探究，她想先做一些统计，于是她抽象了这个问题。

我们对于一个长为 $l$ 的数列 $p$，定义函数：

-   $f(p)$ 表示有多少 $1\le i\le l$ 满足 $p_i=\max_{j=1}^i p_j$（即前缀最大值的个数）。

现在，给定 $n,m$，请求出有多少满足以下条件的长为 $n$ 的，值域在 $[m,n]$ 数列 $a$：

-   存在一个排列 $p$ 使得：令 $P_i$ 代表 $p$ 去掉 $p_i$ 后的数列（即 $[p_1,p_2,\dots,p_{i-1},p_{i+1},\dots,p_n]$），$f(P_i)=a_i$。

答案对 $10^9+7$ 取模。
## 输入格式

一行两个正整数表示 $n,m$。
## 输出格式

一行一个数，表示答案。
## 样例

### 样例输入 #1
```
3 1

```
### 样例输出 #1
```
6

```
### 样例输入 #2
```
5 3

```
### 样例输出 #2
```
8

```
### 样例输入 #3
```
500000 100000

```
### 样例输出 #3
```
226048544

```
## 提示

**【样例解释 \#2】**

有以下 $8$ 种不同的 $a$：

1. $\{4,4,4,4,4\}$，对应的一种 $p$ 为：$\{1,2,3,4,5\}$；
2. $\{3,3,3,4,4\}$，对应的一种 $p$ 为：$\{1,2,3,5,4\}$；
3. $\{3,3,4,4,3\}$，对应的一种 $p$ 为：$\{1,2,4,3,5\}$；
4. $\{3,3,3,3,4\}$，对应的一种 $p$ 为：$\{1,2,4,5,3\}$；
5. $\{3,4,4,3,3\}$，对应的一种 $p$ 为：$\{1,3,2,4,5\}$；
6. $\{3,3,3,4,3\}$，对应的一种 $p$ 为：$\{1,3,4,2,5\}$；
7. $\{4,4,3,3,3\}$，对应的一种 $p$ 为：$\{2,1,3,4,5\}$；
8. $\{3,3,4,3,3\}$，对应的一种 $p$ 为：$\{2,3,1,4,5\}$。

---

**【数据范围】**

对于所有数据，保证 $1 \le m < n \le 5 \times {10}^6$。

---

赫尔德成功算出了不同的恋爱的数量。但她只会经历其中一个。


---

---
title: "约定（Promise）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8560
tag: ['数学', '洛谷原创', 'O2优化', '组合数学', '生成函数', '快速傅里叶变换 FFT', '拉格朗日反演']
---
# 约定（Promise）
## 题目背景

在化为废墟的城市中，大雨倾盆而降。

「魔女之夜」被击败后，圆和焰也已遍体鳞伤，因魔力不足而倒地不起。

「我们，也已经完了......」圆轻叹道。  

「那悲叹之种呢？」焰的语气中还带着一丝希望。

圆沉默不语，望着天空，只是无奈地摇了摇头。

「是吗...... 我说，我们就这样一起变成怪物，把这世界的一切都搞得一团糟吧。」焰说着，不由地啜泣起来。「把那些讨厌的事和悲伤的事，全都和没发生过一样，破坏掉、破坏掉、破坏殆尽...... 你不觉得，这样也很好吗？」

随着一声清脆的碰撞，焰感觉到魔力流入了自己的灵魂宝石内。她转头看见圆正微笑着，拿着一枚悲叹之种。

「刚才那是骗你的，」圆的笑容依旧那么甜美，「我还留着一个呢。」

焰慌忙抱住了圆的手臂，问到：「为什么，为什么要给我？」

「因为有件我做不到，但是小焰能做到的事，我想拜托你...... 小焰，你可以回到过去对吧？你说过，为了避免这样的结局，而改写过历史的吧......」

「嗯...」

圆也终于忍不住悲伤，晶莹的泪珠从她脸上滑落。「你能去救救那个还没被丘比欺骗的，笨蛋的我吗？」

**「我答应你，一定会救你的！无论重复多少次，我都会保护好你！」**

「太好了......」圆平静了下来，但下一瞬间，她的灵魂宝石中就散出了黑雾，她的表情也痛苦地扭曲了起来。「再......拜托你一件事可以吗？」

焰轻轻点头答应。

「我，不想变成魔女......」圆的声音更加虚弱，「就算有讨厌的事和悲伤的事，但我想守护的东西，在这世上还有很多。」圆艰难地抬起手臂，支撑着手中漆黑的灵魂宝石。

「小圆......」焰拔出手枪，对准了圆的灵魂宝石。在焰的痛哭声中，她扣下了扳机。

## 题目描述

澪正陪着铃一起 N 刷《魔法少女小圆》，看到全剧最催人泪下的情节之一时，家长却突然推门进来了。澪不想被发现自己在摸鱼，就迅速切换界面，假装她们在做一道计数题：


> 定义一棵有标号、有根、不区分左右儿子的二叉树的权值是：以「根节点的所有儿子节点」为根的子树的权值之和加上 $d$，特别定义只有一个节点的树权值为 $1$。求所有 $n$ 个节点的这种树权值的 $k$ 次方和，答案对 $998244353$ 取模。

「这不是那个什么 [NaCly_Fish's Math Contest](https://www.luogu.com.cn/contest/53104) 的题... 吗？」铃看了看题，小声说道，「好无聊哦，不看这题。」
## 输入格式

输入一行三个正整数 $n,k,d$。
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3 0 2
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
3 2 2
```
### 样例输出 #2
```
198
```
### 样例输入 #3
```
4 3 2
```
### 样例输出 #3
```
16008
```
### 样例输入 #4
```
6 4 2
```
### 样例输出 #4
```
58351320
```
### 样例输入 #5
```
514 250 114
```
### 样例输出 #5
```
354914151
```
## 提示

【样例 $1$ 解释】

$3$ 个节点的有标号有根二叉树有 $9$ 种，分别如下，其中标红的节点表示树根。
![](https://cdn.luogu.com.cn/upload/image_hosting/266knse0.png)  
由于 $k=0$，所有树权值的 $k$ 次方和就等于树的总数，故答案为 $9$。

【样例 $2$ 解释】  
接上图，图中第一行的树权值都为 $5$，第二行的树权值为 $4$，故答案为 $6\times 5^2+3\times 4^2=198$。

【数据范围】

**本题采用捆绑测试。**

Subtask1（5 pts）：$n \le 6$；  
Subtask2（9 pts）：$k=0$，$n\le 10^7$；      
Subtask3（14 pts）：$n\le 10^5$；   
Subtask4（18 pts）：$k \le 4000$，$n\le 10^7$；  
Subtask5（23 pts）：$k \le 10^5$；  
Subtask6（31 pts）：无特殊限制。

对于 $100\%$ 的数据，$2\le n,d \le 9\times 10^8$，$0\le k \le 5\times 10^6$。




---

---
title: "送别（Farewell）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8561
tag: ['数学', '多项式', '洛谷原创', 'O2优化', '组合数学', 'Stirling 数', '生成函数', '快速傅里叶变换 FFT', '拉格朗日反演']
---
# 送别（Farewell）
## 题目背景

还是到了离别的时候呢...... 相聚的时间很短暂，不知是否给了你一次美好的经历呢？

我举办这场比赛，还是想给自己留下一些珍贵的回忆。虽然自己的水平并不高，但这对我还是很有纪念意义。

经过长时间的准备，在这送别之际，应当更隆重一些的 —— 可惜我并没有那样的能力。若不然，也不会只能以这种程度的题目来压轴。

既然如此，就不要让此次分别成为永别...... 我将全力以赴，为了我们下次再会。这是我自私的请求，但请你等着我回来！

我这贫乏的语言，难以表述心中的情感。不如我们就这样，在离别前静静地享受这段时光吧。
## 题目描述

铃来到了一个奇妙的 Gnilrits 星球，上面生活着一种奇妙的 Gnilrits 人。

这种生物有除了 $k$ 个寿命无限但不能繁殖的个体以外，设其它人的总数在第 $i$ 年为 $a_i$，她得知有规律 $a_i=qa_{i-1}-a_{i-2}$，其中 $a_0=0$，$a_1=1$。

在第 $i$ 年，若 $a_i > k$，则星球上都会依次发生如下事件：

1. 全部 $a_i+k$ 个人被分配到 $a_i$ 个**相同的**住房内，不能有空房（每个人都是不同的）。

2. 每个房屋都修建一条单向道路，连接另一个房屋（可以是自己）；且对任意房屋，都要有一条连向它的道路。最终形成 $a_i-k$ 个环，包括自环。

需要注意的是，在第一步后因为房屋有不同的人居住，它们之间也就是不同的了。

铃想到了一个问题：设第 $i$ 年分配房屋并修建道路的总方案数为 $b_i$（若 $a_i \leq k$ 则 $b_i=0$），则 $i\in [0,n]$ 的所有 $b_i$ 之和是多少呢？

铃在思考这个问题时，她突然惊醒了过来 —— 原来刚才的只是一场梦。她正想和澪分享梦中的见闻，才想起以往在她身边的澪，如今已经离开了。

没有办法，但铃还是想知道问题的答案，请你帮忙求出来吧。结果可能很大，你只需要告诉她答案对 $998244353$ 取模的结果即可。


## 输入格式

第一行三个正整数 $n,q,k$。 
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
4 2 2
```
### 样例输出 #1
```
765
```
### 样例输入 #2
```
233 2 99
```
### 样例输出 #2
```
161697303
```
### 样例输入 #3
```
7 4 5
```
### 样例输出 #3
```
322237710
```
### 样例输入 #4
```
10 3 17
```
### 样例输出 #4
```
146281933
```
### 样例输入 #5
```
1919810 114514 2333
```
### 样例输出 #5
```
426283611
```
## 提示

【样例 $1$ 解释】  

在 $i \leq 2$ 时 $b_i=0$。

对于 $i=3$ 的情况，$a_i=3$。首先要将 $5$ 个不同的人分配入 $3$ 个相同的房屋，有 $25$ 种方案；再把 $3$ 个变得不同的房屋用环路连接，形成 $1$ 个环，只有 $2$ 种方案，故 $b_3 = 25 \times 2 = 50$。  
（更具体的解释见[此处](https://www.luogu.com.cn/paste/usa2ggb4)）

对于 $i=4$，$a_i=4$，将 $6$ 个人分入 $4$ 个房屋有 $65$ 种方案；在 $4$ 个房屋间修路形成 $2$ 个环有 $11$ 种方案，总方案数为 $65\times 11 = 715$。

故答案为 $50+715=765$。

【数据范围】

**本题采用捆绑测试。**

Subtask 1（7 pts）：$1\le n\le 1000$，$1\le k \le 3$；   
Subtask 2（11 pts）：$1\le n,k \le 100$；   
Subtask 3（13 pts）：$1 \le k \le 1000$；  
Subtask 4（19 pts）：$1\le k \le 32000$，$q=2$；  
Subtask 5（23 pts）：$1\le k \le 16000$，$q \neq 2$；   
Subtsak 6（27 pts）：无特殊限制。

对于 $100\%$ 的数据，$1\le n \le 10^9$，$1\le k \le 64000$，$2\le q \le 10^9$。  


【提示】  
此题并不难，但可能需要一定程度的常数优化。




---

---
title: "十二重骗分法（Cheating XII）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8562
tag: ['数学', '洛谷原创', '提交答案', '枚举', '组合数学']
---
# 十二重骗分法（Cheating XII）
## 题目描述

一阵恍惚过后，你发现自己坐在机房里。一看时间，现在竟然是 2202 年！你又环视了一下周围的情况，原来自己在 CSP-J 2202 的考场上。

你还没搞清楚情况时，似乎听见有人对你低语：「想知道怎么回事吗？那就展现你以往的能力，把这次的 CSP-J 也 AK 掉吧。」

于是你看到四个题分别是：  

1. 输入一个正整数 $n$，求 $\lfloor \sqrt n \rfloor$。  

2. 给定一个左右各有 $n$ 个点的二分图，与其中的边，求它完美匹配的方案数，答案对 $998244353$ 取模。

3. 生命游戏（Conway's Game of Life）进行于一个无限大的二维网格上，每个格子要么是空地，要么有一个细胞。每个时刻都会进行一轮**迭代**，规则如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/do0c6ras.png)  
现在，给定你初始状态，求迭代 $k$ 次后的细胞数。  
ps：你可以在 [这里](https://playgameoflife.com/) 试玩。

4. 给你一个 $n$ 个点、 $m$ 条边的无向图，每个点都可以涂上 $k$ 种颜色中的一种，且相邻的点（即有边直接相连的点）不能有相同的颜色。求有多少种染色方案，答案对 $998244353$ 取模。

「这怎么可能啊！」你差点惊叫出来。不过你发现，唯独你的电脑上有题目的输入数据！你想暴力跑出答案，却发现 2202 年的评测机性能和一百多年前没差别。

那该怎么办呢？总之只能靠自己了吧。


**输入数据可以在题目下方的附件中下载。**
## 输入格式

第一行一个正整数 $T$，表示测试点编号。

若 $T \in \{ 1,2\}$，表示 Subtask 1。接下来一行仅一个正整数 $n$。

若 $T \in \{3,4,5,6\}$，表示 Subtask 2。第二行一个正整数 $n$。
接下来 $n$ 行，第 $i$ 行先输入一个正整数 $m_i$，表示左部分第 $i$ 个点（记作 $u_i$）的度数为 $m_i$；后面接着 $m_i$ 个整数 $v_{i,1},v_{i,2},\cdots,v_{i,m_i}$，依次表示与 $u_i$ 连接的右部分节点编号。  

若 $T \in\{ 7,8,9\}$，表示 Subtask 3。第二行输入三个正整数 $n,m,k$，表示输入的初始形态有 $n$ 行 $m$ 列（除此之外是无限大的二维平面，没有其它细胞），迭代 $k$ 次。接下来 $n$ 行，每行一个长度为 $m$ 的 01 串，`0` 表示空地，`1` 表示细胞，描述了一行的形态。

若 $T \in\{ 10,11,12\}$，表示 Subtask 4。第二行输入三个正整数 $n,m,k$。接下来 $m$ 行，每行两个正整数 $u,v$ 描述一条无向边，保证无重边和自环。
## 输出格式

输出一行一个正整数，表示答案。
## 样例

### 样例输入 #1
```
3
3
2 1 2
2 2 3
2 1 3
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
7
5 5 133
10001
00000
11111
00000
01010
```
### 样例输出 #2
```
129
```
## 提示

【样例 $1$ 解释】  
输入中 $T=3$，要求的问题是二分图完美匹配计数。  
可以发现，只有两种匹配方案：$1 \leftrightarrow 1,2 \leftrightarrow 2,3 \leftrightarrow 3$
 或 $1 \leftrightarrow 2,2 \leftrightarrow 3,3 \leftrightarrow 1$。
 
 【样例 $2$ 解释】  
 输入中 $T=7$，要求的问题是预测生命游戏细胞数。给出的输入是：  
 ![](https://cdn.luogu.com.cn/upload/image_hosting/0ukc526n.png)   
 经过 $133$ 轮迭代后为：  
 ![](https://cdn.luogu.com.cn/upload/image_hosting/g6yz6nf3.png)  
 可以数出其中细胞数为 $129$。  
 
样例中虽然有 $T\in[1,12]$，但并不代表实际输入。  

【测试点分数信息】   

| 编号 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| **分数** | $7$ | $8$ | $6$ | $7$ | $9$ | $11$ | $8$ | $9$ | $10$ | $7$ | $8$ | $10$ |




---

---
title: "[蓝桥杯 2021 国 A] 积木"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8768
tag: ['2021', '多项式', '组合数学', '快速数论变换 NTT', '蓝桥杯国赛']
---
# [蓝桥杯 2021 国 A] 积木
## 题目描述

小蓝有大量正方体的积木（所有积木完全相同），他准备用积木搭一个巨大的图形。

小蓝将积木全部平铺在地面上，而不垒起来，以便更稳定。他将积木摆成一行一行的，每行的左边对齐，共 $n$ 行，形成最终的图形。

第一行小蓝摆了 $H_{1}=w$ 块积木。从第二行开始，第 $i$ 行的积木数量 $H_{i}$ 都 至少比上一行多 $L$，至多比上一行多 $R$ (当 $L=0$ 时表示可以和上一行的积木数量相同)，即

$$
H_{i-1}+L \leq H_{i} \leq H_{i-1}+R_{\circ}
$$

给定 $x, y$ 和 $z$, 请问满足以上条件的方案中，有多少种方案满足第 $y$ 行的积木数量恰好为第 $x$ 行的积木数量的 $z$ 倍。
## 输入格式

输入一行包含 $7$ 个整数 $n, w, L, R, x, y, z$，意义如上所述。
## 输出格式

输出一个整数，表示满足条件的方案数，答案可能很大，请输出答案除以 $998244353$ 的余数。
## 样例

### 样例输入 #1
```
5 1 1 2 2 5 3
```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
233 5 1 8 100 215 3
```
### 样例输出 #2
```
308810105
```
## 提示

**【样例说明】**

符合条件的积木如图所示
![](https://luogu.oss-cn-hangzhou.aliyuncs.com/upload/vjudge_pic/lanqiao/2022_09_29_ca697d8d2e5bb8d06fa0g-17.jpg)

**【评测用例规模与约定】**

对于 $10 \%$ 的评测用例, $1 \leq n \leq 10,1 \leq w \leq 10,0 \leq L \leq R \leq 3$;

对于 $20 \%$ 的评测用例, $1 \leq n \leq 20,1 \leq w \leq 10,0 \leq L \leq R \leq 4$;

对于 $35 \%$ 的评测用例, $1 \leq n \leq 500,0 \leq L \leq R \leq 10$;

对于 $50 \%$ 的评测用例, $1 \leq n \leq 5000,0 \leq L \leq R \leq 10$;

对于 $60 \%$ 的评测用例, $1 \leq n \leq 20000,0 \leq L \leq R \leq 10$;

对于 $70 \%$ 的评测用例, $1 \leq n \leq 50000,0 \leq L \leq R \leq 10$;

对于 $85 \%$ 的评测用例, $1 \leq n \leq 3\times10^5,0 \leq L \leq R \leq 10$;

对于所有评测用例, $1 \leq n \leq 5\times10^5, 0 \leq w \leq 10^{9}, 0 \leq L \leq R \leq 40$, $1 \leq x<y \leq n, 0 \leq z \leq 10^{9}$ 。

蓝桥杯 2021 国赛 A 组 J 题。


---

---
title: "计数题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9151
tag: ['动态规划 DP', '数学', '洛谷原创', 'O2优化', '组合数学', '洛谷月赛']
---
# 计数题
## 题目背景

[Easy Counting Problem](https://atcoder.jp/contests/agc022/tasks/agc022_e)

> 身のうさを思ひしらでややみなまし そむくならひのなき世なりせば
## 题目描述

给定长度为 $N$ 的 $01$ 串 $S$，你可以做若干个操作，形如将长度为 $3$ 的子串变成它们的中位数（注意是变成一个数字），问可以得到多少个不同的串。

答案对 $998244353$ 取模。
## 输入格式

本题有多组数据。第一行输入数据组数 $T$。

对于每组数据，仅输入一个字符串 $S$ 表示给定的 $01$ 串。
## 输出格式

对每组数据输出一行一个整数，表示答案对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
4
1001
111000
101010
111000101010

```
### 样例输出 #1
```
3
7
3
25

```
## 提示

**【样例解释】**

可以证明，$1001$ 仅能通过操作获得串 $10,01,1001$ ，因此样例第一组数据的答案为 $3$。

---

**【数据范围】**

对于 $100 \%$ 的数据，满足 $1\le N \le 5\times {10}^6$，$S_i\in\{0,1\}$，$1 \le T \le 5$。

| 子任务 | $N \le$ | 特殊性质 | 分数 |
| - | - | - | - |
| 1 | $10$ | | $5$ |
| 2 | $50$ | | $10$ |
| 3 | $300$ | | $10$ |
| 4 | $2000$ | | $15$ |
| 5 | | A | $5$ |
| 6 | | B | $5$ |
| 7 | ${10}^5$ | | $20$ |
| 8 | | | $30$ |

特殊性质 A：保证 $S_i=0$。

特殊性质 B：保证 $S_{2k}=0$、$S_{2k+1}=1$。

**字符串下标的编号从 $1$ 开始。**


---

