---
title: "[集训队互测 2024] 生命的循环"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12474
tag: ['集训队互测', '2024', '数论', '强连通分量']
---
# [集训队互测 2024] 生命的循环
## 题目描述

生命是一张由 $n$ 个神经节点与 $m$ 条神经构成的**带权**有向图，允许存在**自环**、**重边**。

一条编号为 $i$ 的神经 $(u_i, v_i, w_i)$ **单向地**连接着两个神经节点 $u_i \rightarrow v_i$，长度为 $w_i$。

生命的网络不会过于复杂，对于任意一条**简单回路**，其包含的所有神经长度之和**不大于**一个定值 $B$。

神经节点在某些时刻会兴奋，定义 $f(u, t)$ 表示 $t$ 时刻神经节点 $u$ 是否处于兴奋状态。

兴奋会沿着神经传导，对于第 $i$ 条神经 $(u_i, v_i, w_i)$，若神经节点 $u_i$ 在时刻 $t$ 是兴奋的，那么其会向节点 $v_i$ 传递神经信号，使其在时刻 $t + w_i$ 进入兴奋状态。

神经节点的兴奋状态**不会保留**到下一个时刻，即神经节点 $u$ 在进入兴奋状态后会沿其它神经立刻向外传递神经信号；接下来的时刻里，如果没有其它神经向它传递神经信号，则该神经节点会**保持不兴奋**的状态。

如果在**同一个时刻**，一个节点进入兴奋状态后其递归地向自身传递了神经信号，兴奋状态也不会保留到下一个时刻。（换句话说，数据中存在边权和为 0 的简单回路，此时你可以将整条简单回路等效地看作单个神经节点处理。）

生命的伊始，神秘的力量刺激了 1 号神经节点，使其在**时刻 0** 时进入兴奋状态。从此开始无数的时间里，生命的讯号便在神经网络中不息传递着。

在经过葛立恒数个时刻的洗礼后，一位实力强大的 Oler——你，历经千辛万苦，终于抵达了 $n$ 号神经节点。在那里，你看到生命总是趋于循环。

即，保证经过充分长的时间后，$n$ 号神经节点以一个固定时间周期依据一定模式重复进入兴奋状态。

现在的你开始好奇，**此时** $n$ 号神经节点的进入兴奋状态的**最小周期**是多少？

亦即，你需要求出一个最小的正整数 $p$，满足存在一个**有限**的非负整数 $M$，使得

$$\forall x \geq M, f(n, x) = f(n, x + p)$$

由于 $p$ 可能很大，你只需要输出 $p$ 对 $10^9 + 9$ **取模**后的结果。
## 输入格式

第一行输入三个数 $n, m, type$，依次表示神经节点个数、神经条数、子任务编号。你可以通过 $type$ 来判断 $B$ 的取值。特别地，对于题面中的样例，$type = 0$。

接下来 $m$ 行，第 $i$ 行三个数 $u_i, v_i, w_i$，描述第 $i$ 条神经由神经节点 $u_i$ 指向神经节点 $v_i$，长度为 $w_i$。
## 输出格式

输出一行一个正整数，表示答案 $p$ 对于 $10^9 + 9$ 取模后的结果。
## 样例

### 样例输入 #1
```
5 7 0
1 2 0
2 3 1
3 2 5
3 5 1
1 4 0
4 4 9
4 5 1
```
### 样例输出 #1
```
18
```
## 提示

### 数据约束

对于所有数据满足 $2 \leq n \leq 5000, 0 \leq m \leq 10^4, 1 \leq u_i, v_i \leq n, 0 \leq w_i \leq B \leq 100$。

### 子任务

- Subtask 1 (1 pts): 神经构成的有向图是一张 DAG，即不存在任何简单回路。
- Subtask 2 (8 pts): $n, B \leq 10, m \leq 15$。
- Subtask 3 (11 pts): 原图强连通。即任意一对神经节点间都可以通过神经组成的有向路径互相可达。
- Subtask 4 (10 pts): 存在至少一条包含点 $n$ 的简单回路。
- Subtask 5 (19 pts): 所有的简单回路点集互不相交，且总长度两两互质。
- Subtask 6 (9 pts): 所有的简单回路点集互不相交，且总长度均为质数的若干次幂。
- Subtask 7 (18 pts): $B \leq 30$。
- Subtask 8 (24 pts): 无特殊限制。


---

---
title: "[GCJ 2022 Finals] Goose, Goose, Ducks?"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13002
tag: ['2022', '强连通分量', 'Google Code Jam']
---
# [GCJ 2022 Finals] Goose, Goose, Ducks?
## 题目描述

The first international Geese conference just wrapped up, and even though it should have been a happy occasion, it was bittersweet. The organizers found a paper with detailed plans of a duck infiltration. Now, they are trying to identify the infiltrating group from among the attendees.

The document that they found contained a list of $\mathbf{M}$ triples of integers $(\mathbf{X}_i, \mathbf{Y}_i, \mathbf{C}_i)$ meaning the ducks would meet exactly $\mathbf{C}_i$ seconds after the start of the conference at point $(\mathbf{X}_i, \mathbf{Y}_i)$, which is $\mathbf{X}_i$ meters east and $\mathbf{Y}_i$ meters north of the center of the conference floor. Each goose may or may not have been at those specific points at those specific times, but every duck certainly was.

Both ducks and geese walk at a maximum speed of one meter per second, which means an attendee that is at point $(x, y)$ at time $t$ can reach any point of the form $(x + \Delta_x, y + \Delta_y)$ by time $t + \Delta_t$ as long as $\Delta_x^2 + \Delta_y^2 \leq \Delta_t^2$. Each attendee's position at time 0 can be any point, independently of the other attendees.

![](https://cdn.luogu.com.cn/upload/image_hosting/mq68x9yi.png)

After the discovery, the group held a questioning session to try to identify the ducks. During that session, attendees issued a series of statements, one at a time. The $j$-th of those, in the order they were issued, was made by attendee $\mathbf{A}_j$, claiming that both they and attendee $\mathbf{B}_j$ were at point $(\mathbf{U}_j, \mathbf{V}_j)$ exactly $\mathbf{D}_j$ seconds after the start of the conference. Points in statements may or may not be points where duck meetings happened.

Statements from geese are always true, but ducks may lie. Moreover, ducks know which attendees are ducks and which are geese. To avoid getting caught easily, ducks only make statements that are consistent with all statements previously made by geese. Note that statements made by geese are consistent with all ducks being at all duck meetings.

It may not be possible to determine all the ducks with the information provided. However, knowing the minimum number of ducks will at least provide a lower bound on the level of duck activity. Note that there was at least one duck. Find this minimum number of ducks.

Formally, a hypothesis $H$ is a partition of all attendees into a set of ducks (named $H$-ducks) and geese (named $H$-geese). $H$ is consistent with a set of statements $S$ if there exists a path for each attendee moving at most one meter per second such that:

* all $H$-ducks were at all duck meetings and
* for each statement in $S$ claiming that $A$ saw $B$ at point $P$ at time $T$, both $A$ and $B$'s paths went through point $P$ at time $T$.

A hypothesis $H$ is feasible under a set of statements $S$ if:

* $H$-ducks is not empty (i.e., there was at least one duck),
* the subset of all statements from $S$ made by members of $H$-geese is consistent with $H$ (i.e., statements from geese are always true), and
* for each statement $s \in S$ made by a member of $H$-ducks, if $P \subseteq S$ is the subset of statements made by members of $H$-geese issued before $s$, there exists a hypothesis $H'$ (which may or may not be equal to $H$) such that $\{s\} \cup P$ is consistent with $H'$ (i.e., ducks do not contradict previous statements made by geese).

Notice that the hypotheses $H$ such that $H$-ducks contains all attendees is always feasible.

Find the minimum size of $H$-ducks over all feasible hypotheses $H$.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing three integers, $\mathbf{N}$, $\mathbf{M}$, and $\mathbf{S}$, representing the numbers of attendees, duck meetings, and statements, respectively. The next $\mathbf{M}$ lines each describe a different duck meeting with three integers $\mathbf{X}_i$, $\mathbf{Y}_i$, and $\mathbf{C}_i$, representing that there was a meeting at point $(\mathbf{X}_i, \mathbf{Y}_i)$, held exactly $\mathbf{C}_i$ seconds after the start of the conference. Then, the last $\mathbf{S}$ lines of a test case each describe a statement. The $j$-th of these lines describes the $j$-th issued statement with five integers $\mathbf{A}_j$, $\mathbf{B}_j$, $\mathbf{U}_j$, $\mathbf{V}_j$, and $\mathbf{D}_j$, representing that attendee $\mathbf{A}_j$ stated that they and attendee $\mathbf{B}_j$ were both at point $(\mathbf{U}_j, \mathbf{V}_j)$ exactly $\mathbf{D}_j$ seconds after the start of the conference.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the minimum number of ducks that might have infiltrated the conference.
## 样例

### 样例输入 #1
```
2
2 1 2
1 2 3
1 2 1 1 1
2 1 2 2 2
4 2 4
4 3 10
-4 -3 20
1 3 4 3 11
2 4 0 0 16
3 1 6 3 9
4 2 0 0 16
```
### 样例输出 #1
```
Case #1: 1
Case #2: 2
```
## 提示

**Sample Explanation**

In Sample Case #1, attendee 1 being the only duck is a feasible hypothesis.

In Sample Case #2, attendees 2 and 4 being the only ducks is a feasible hypothesis. Note that there is at least one duck, so all attendees being geese is not feasible.

**Limits**

- $1 \leq \mathbf{T} \leq 50$.
- $-10^9 \leq \mathbf{X}_i \leq 10^9$, for all $i$.
- $-10^9 \leq \mathbf{Y}_i \leq 10^9$, for all $i$.
- $1 \leq \mathbf{C}_i \leq 10^9$, for all $i$.
- $\mathbf{C}_i < \mathbf{C}_{i+1}$, for all $i$.
- $(\mathbf{X}_i - \mathbf{X}_{i+1})^2 + (\mathbf{Y}_i - \mathbf{Y}_{i+1})^2 \leq (\mathbf{C}_i - \mathbf{C}_{i+1})^2$, for all $i$.
- $1 \leq \mathbf{A}_j \leq \mathbf{N}$, for all $j$.
- $1 \leq \mathbf{B}_j \leq \mathbf{N}$, for all $j$.
- $\mathbf{A}_j \neq \mathbf{B}_j$, for all $j$.
- $-10^9 \leq \mathbf{U}_j \leq 10^9$, for all $j$.
- $-10^9 \leq \mathbf{V}_j \leq 10^9$, for all $j$.
- $1 \leq \mathbf{D}_j \leq 10^9$, for all $j$.
- $(\mathbf{A}_j, \mathbf{B}_j, \mathbf{U}_j, \mathbf{V}_j, \mathbf{D}_j) \neq (\mathbf{A}_k, \mathbf{B}_k, \mathbf{U}_k, \mathbf{V}_k, \mathbf{D}_k)$, for all $j \neq k$.

**Test Set 1 (11 Pts, Visible Verdict)**

- Time limit: 20 seconds.
- $2 \leq \mathbf{N} \leq 50$.
- $1 \leq \mathbf{M} \leq 50$.
- $1 \leq \mathbf{S} \leq 50$.

**Test Set 2 (24 Pts, Hidden Verdict)**

- Time limit: 60 seconds.
- $2 \leq \mathbf{N} \leq 10^5$.
- $1 \leq \mathbf{M} \leq 10^5$.
- $1 \leq \mathbf{S} \leq 10^5$.


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
title: "[ZJOI2018] 迷宫"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4339
tag: ['数学', '2018', '各省省选', '浙江', '强连通分量']
---
# [ZJOI2018] 迷宫
## 题目背景

九条可怜是一个贪玩的女孩子。
## 题目描述

暑假快要到了，可怜打算在她家的私人海滩旁边建一座城堡，这样就可以在放暑假的时候 邀请她的朋友们来玩了。同时，可怜打算在城堡的地下修建一座迷宫，因为探险总是一件充满 乐趣的事情。

经过简单的设计，可怜打算修建一座这样的迷宫：
- 迷宫可以被抽象成 $n$ 个点，$nm$ 条边的有向图。$1$ 号点是唯一的入口也是唯一的出口。 
- 每一个点恰好有 $m$ 条出边，且这些出边被依次标号为 $[0,m)$ 的正整数。 
- 迷宫允许自环和重边。

同时，一座优秀的迷宫应该有一定的解谜因素。因此可怜希望每一条从 $1$ 号点出发并回到 $1$ 号点的回路都有着一定的规律。可怜发现，如果把一条从 $1$ 出发的路径经过的所有边的编号都记录下来，那么能得到一个（可能有前导 $0$）的 $m$ 进制数；同时对于每一个（可能有前导 $0$）的 $m$ 进制数，都能对应回一 条从 $1$ 出发的路径。

于是可怜选定了一个整数 $K$，她希望这个迷宫满足一条从 $1$ 出发的路径能回到 $1$ **当且仅当**这条路径对应的数是 $K$ 的倍数。

现在可怜已经选定了 $m$ 和 $K$，但是她发现并不是对所有的 $n$，都存在满足上述所有条件的迷宫设计方案。建造迷宫是一件费时费力的事情，于是可怜想要找到一个最小的满足条件的 $n$。

然而可怜对复杂的计算并不感兴趣，因此她想让你来帮她计算一下这个数值。
## 输入格式

第一行输入一个整数 $T$ 表示数据组数。 

接下来 $T$ 行每行两个十进制正整数 $m,K$ 表示可怜选定的整数。
## 输出格式

对于每组数据，输出一行一个整数表示能够满足所有条件的最小的 $n$。如果不存在这样的 $n$，输出 `-1`。
## 样例

### 样例输入 #1
```
3 
2 3
2 4 
6 8
```
### 样例输出 #1
```
3 
3
5
```
## 提示

第一组数据（左）和第二组数据（右）的一种设计方案如下图所示。其中紫色边表示 $0$ 号边，蓝色边表示 $1$ 号边。

![](https://cdn.luogu.com.cn/upload/pic/16017.png)

![](https://cdn.luogu.com.cn/upload/pic/16018.png)


---

