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
title: "[THUPC 2024 决赛] 机器人"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10545
tag: ['模拟', '2024', 'Special Judge', '2-SAT', 'THUPC']
---
# [THUPC 2024 决赛] 机器人
## 题目背景

注意本题的指令含义与初赛的略有不同。

## 题目描述

有 $n$ 个机器人围成一圈，编号按照逆时针顺序分别为 $0\sim n-1$。

每个机器人有两只手。编号为 $i$ 的机器人初始「左手」指向编号 $l_i$ 的机器人，「右手」指向编号 $r_i$ 的机器人。

所有的机器人内部都写有一条「指令」，「指令」有以下这些形式：

### 指令

下面介绍这些「指令」的格式以及它们被「执行」时的效果。文中的“自己”一词均指拥有这条「指令」的机器人。

- `SLACKOFF`：**「摸鱼」**，即什么也不做。
- `MOVE h z`：将第 $h$ 只手向逆时针方向 **「移动」** $z$ 个机器人的位置。当 $h=0$ 时表示「左手」，当 $h=1$ 时表示「右手」，下同。
- `SWAP`：**「交换」** 双手指向的机器人的「指令」。
- `TRIGGER <COMMANDNAME>: <COMMAND>`：其中 `<COMMANDNAME>` 为 `SLACKOFF`、`MOVE`、`SWAP`、`TRIGGER`、`TOGGLETRIGGERREPLACE` 之一；`<COMMAND>` 表示一条完整的非 `TRIGGER` 「指令」。`TRIGGER` 指令本身不会被「执行」，但是，当一个**其他**机器人「执行」完一条「指令」之后，且「右手」指向自己的时候，自己满足如下条件的 `TRIGGER` 指令（如果有）就会被 **「触发」**——「执行」一次对应的 `<COMMAND>`：
  - `<COMMANDNAME>` 不为 `TRIGGER` 时，刚刚「执行」完毕的「指令」为 `<COMMANDNAME>` 指令；
  - `<COMMANDNAME>` 为 `TRIGGER` 时，刚刚「执行」完毕的「指令」是一条 `TRIGGER` 指令被「触发」时，「执行」的 `<COMMAND>` 部分。
- `TOGGLETRIGGERREPLACE h <COMMANDNAME> <NEWCOMMAND>`：如果第 $h$ 只手指向的机器人的「指令」是 `TRIGGER` 指令，则将其 **「切换」** 为该「指令」的 `<COMMAND>` 部分，即删去前面的 `TRIGGER` 及条件部分；如果这条「指令」不是 `TRIGGER` 指令，假设是 `<COMMAND>`，则将其「切换」为 `TRIGGER <COMMANDNAME>: <COMMAND>`。其中 `<COMMANDNAME>` 为 `SLACKOFF`、`MOVE`、`SWAP`、`TRIGGER`、`TOGGLETRIGGERREPLACE` 之一。然后将自己的「指令」（注意这可能不仅仅包含正在「执行」的那部分「指令」）修改为 `<NEWCOMMAND>`。其中，`<NEWCOMMAND>` 是一条完整的「指令」。

机器人「执行」各「指令」时的输出格式如下：

- 「摸鱼」时输出 `Robot <id> slacks off.`。其中 `<id>` 为一个整数，表示「执行」当前「指令」的机器人编号，下同。
- 「移动」时输出 `Robot <id> moves its <side> hand towards Robot <id2>.`。其中 `<side>` 为 `left` 或 `right`，表示移动了哪只手（`left` 表示「左手」，`right` 表示「右手」）；`<id2>` 为一个整数，表示移动之后这只手指向的机器人的编号。
- 「交换」时输出 `Robot <id> swaps the commands of Robot <id2> and Robot <id3>.`。其中 `<id2>` 和 `<id3>` 为整数，表示被「交换」「指令」的机器人编号，这两个数可以按任意顺序输出。
- 「切换」时输出 `Robot <id> toggles the trigger property of the command of Robot <id2>`。
- `TRIGGER` 指令不会被「执行」，但当它们被「触发」时，会按照上面的格式输出对应的「指令」被「执行」的信息。

你按照一定顺序选择了一些机器人（可能重复选择）并「执行」了对应机器人的「指令」，得到了「执行」的**完整**输出，也就是说，在「执行」完输出中最后一条「指令」之后，没有其他「指令」被「触发」。但是，你忘记了你选择机器人的顺序，也忘了每个机器人开始时有什么「指令」。你只记得机器人的总数以及开始时每个机器人的手指向什么位置。

你想通过已知的所有信息还原出最初所有机器人的「指令」都是什么。
## 输入格式

第一行两个正整数 $n,k$，其中 $k$ 表示输出的总行数。

接下来 $n$ 行，每行两个整数 $l_i,r_i$，按编号从小到大的顺序输入。

接下来 $k$ 行，每行一条「执行」「指令」的输出信息。

为了减轻处理输入的负担，输出信息被简化如下（没有特殊声明的参数信息含义同上）：

- 「摸鱼」时输出 `SLACKOFF <id>`。
- 「移动」时输出 `MOVE <id> <side> <id2>`。其中 `<side>` 为 `0` 或 `1`，表示移动了哪只手（`0` 表示「左手」，`1` 表示「右手」）。
- 「交换」时输出 `SWAP <id> <id2> <id3>`。
- 「切换」时输出 `TOGGLETRIGGERREPLACE <id> <id2>`。
- `TRIGGER` 指令不会被「执行」，但当它们被「触发」时，会按照上面的格式输出对应的「指令」被「执行」的信息。

输入保证存在一组初始的「指令」，使得存在一种选择机器人的方式，能够得到对应的输出。

保证 $1\le n,k \le 500000$。

保证 $0\le l_i,r_i<n$。
## 输出格式

输出 $n$ 行，按编号从小到大输出机器人最初的「指令」，每条一行。

你需要保证「指令」格式正确，且 $0\le z < n$。

你需要保证你的输出文件不能过大。若你的输出文件大小不超过 $100\texttt{MB}$，则一定能保证 Special Judge 能够正确返回结果。

此外任何能够得到输入中 $k$ 行输出的答案均算作正确。
## 样例

### 样例输入 #1
```
4 7
1 3
2 0
3 0
2 1
SWAP 1 0 2
SWAP 0 1 3
SWAP 1 2 0
MOVE 0 0 2
SWAP 1 0 2
SWAP 0 2 3
MOVE 3 0 3

```
### 样例输出 #1
```
MOVE 0 1
SWAP
TRIGGER SWAP: SWAP
SWAP

```
### 样例输入 #2
```
4 7
1 2
2 3
3 1
0 2
TOGGLETRIGGERREPLACE 0 1
SLACKOFF 3
MOVE 0 1 3
SWAP 1 2 3
TOGGLETRIGGERREPLACE 3 2
SLACKOFF 2
SLACKOFF 3

```
### 样例输出 #2
```
TOGGLETRIGGERREPLACE 0 MOVE MOVE 1 1
TRIGGER SLACKOFF: SWAP
TRIGGER SWAP: TOGGLETRIGGERREPLACE 1 TOGGLETRIGGERREPLACE SLACKOFF
SLACKOFF

```
### 样例输入 #3
```
4 4
2 1
1 2
0 3
1 3
SLACKOFF 0
SLACKOFF 1
SLACKOFF 2
SLACKOFF 3

```
### 样例输出 #3
```
SLACKOFF
TRIGGER SLACKOFF: SLACKOFF
TRIGGER SLACKOFF: SLACKOFF
TRIGGER TRIGGER: SLACKOFF

```
## 提示

**样例解释 1**

选择机器人的顺序为 $1,1,0,1,3$，其中第二、六条被「执行」的「指令」是「触发」`TRIGGER` 指令之后被「执行」的。

注意 `TRIGGER` 指令「触发」的时机是在「执行」上一条「指令」之后，所以第一次「交换」之后由于 $1$ 号机器人的「右手」指向了写有 `TRIGGER SWAP: SWAP` 的 $0$ 号机器人，所以这条 `TRIGGER` 指令能被「触发」。

**样例解释 2**

选择机器人的顺序为 $0,3,0,1,3$，其中第五、六条被「执行」的「指令」是「触发」`TRIGGER` 指令之后被「执行」的。

第一次「执行」会使 $1$ 号机器人的「指令」变为 `SWAP`，$0$ 号机器人的「指令」变为 `MOVE 1 1`。

第五次「执行」会使 $2$ 号机器人的「指令」由 `SLACKOFF` 变为 
```
TRIGGER TOGGLETRIGGERREPLACE: SLACKOFF
```
，$3$ 号机器人的「指令」由
```
TRIGGER SWAP: TOGGLETRIGGERREPLACE 1 TOGGLETRIGGERREPLACE SLACKOFF
```
会变为 `SLACKOFF` 而不是 `TRIGGER SWAP: SLACKOFF`。

**样例解释 3**

选择机器人的顺序为 $0$，其中第二、三、四条被「执行」的「指令」是「触发」`TRIGGER` 指令之后被「执行」的。

注意 $3$ 号机器人「执行」完「指令」后不会接着「触发」自己的 `TRIGGER` 「指令」，即使它的「右手」指向了自己。

另外，选择一个写有 `TRIGGER` 指令的机器人不会产生任何输出，所以这么做没有意义。

**样例解释 4**

见题目目录下的 *4.in*。该样例不提供样例输出。

**样例解释 5**

见题目目录下的 *5.in*。该样例不提供样例输出。

**提示**

我们会下发一个可执行文件 `checker` 来帮助你检查你的输出是否正确。使用方式为在该文件所在目录下使用如下指令：

```
./checker <输入文件路径> <你的输出文件路径>
```

若你的输出正确，程序会输出 `Accepted.`；否则会提示「执行」结果与输入文件最早一次不匹配的地方。

注意，若你使用的输入文件不是样例输入，该程序不会检查是否存在一组初始的「指令」，使得存在一种选择机器人的方式，能够得到对应的「执行」结果。

**来源与致谢**

来自 THUPC2024（2024年清华大学学生程序设计竞赛暨高校邀请赛）决赛。感谢 THUSAA 的提供的题目。

数据、题面、标程、题解等请参阅 THUPC 官方仓库 <https://thusaac.com/public>



---

---
title: "[GCJ 2015 Finals] Crane Truck"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13238
tag: ['模拟', '2015', 'Google Code Jam']
---
# [GCJ 2015 Finals] Crane Truck
## 题目描述

You are in a large storage facility, with $2^{40}$ storage locations arranged in a circle.

A truck with a crane on it moves along the circle of storage locations, picking up or putting down crates according to a program. (The truck has an unlimited supply of crates on board, so it can always put more crates down.)

The program consists of a sequence of these instructions:

* b: move back one location
* f: move forward one location
* u: pick up one crate at the current location
* d: put down one crate at the current location
* (: do nothing
* ): if there is more than one crate at the current location, move back to the most recent ( in the sequence of instructions, and continue the program from there. (This doesn't move the truck.)

( and ) instructions in the program will always come in pairs: a ( will be followed later by a matching ). There will be at most two such pairs in the program, and if there are two pairs, they will not be nested – that is, there will be either:

* no ( or ) instructions;
* one ( instruction somewhere in the program, followed later by one ) instruction;
* a ( instruction, followed later by a ) instruction, followed later by another (, and again later by another ).

The sample cases contain examples of each of these.

Each storage location begins with one crate, before the crane truck starts running its program.

Mysteriously, if the truck picks up the last crate at a location, another truck instantly comes along and puts down 256 crates there! Similarly, if the truck puts down a crate at a location, and that location then has 257 crates, another truck instantly drives past and picks up 256 of the crates, leaving one behind! So every location always has between 1 and 256 crates.

How many times will the truck move forward or backward before reaching the end of its program?
## 输入格式

One line containing an integer $T$, the number of test cases in the program.

$T$ lines, each containing a crane truck program with up to 2000 characters.
## 输出格式

$T$ lines, one for each test case, containing "Case #$X$: $Y$" where $X$ is the test case number, and $Y$ is the number of times the truck moves.

## 样例

### 样例输入 #1
```
4
ufffdddbbbdd
dddd(fdbu)fff
dddd(fdddddbu)f(fdddddbu)
bf
```
### 样例输出 #1
```
Case #1: 6
Case #2: 11
Case #3: 49
Case #4: 2
```
## 提示

**Limits**

- $1 \leq T \leq 20$.
- $1 \leq$ the length of the program $\leq 2000$.
- The program is guaranteed to terminate.

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- The program will contain at most one pair of ( and ) instructions.

**Large dataset**

- Time limit: ~~480~~ 10 seconds.
- The program will contain at most two pairs of ( and ) instructions.


---

---
title: "[GCJ 2012 #3] Lost Password"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13331
tag: ['2012', '模拟费用流', 'Google Code Jam']
---
# [GCJ 2012 #3] Lost Password
## 题目描述

Ashish has forgotten his password. He remembers that he used the following algorithm to create his password: Ashish took up to $k$ consecutive words from a passage of text, and took the first letter from each word. Then, he might have changed some of the letters to their "l33tspeak" equivalents. Specifically, he might have changed "o" to "0", "i" to "1", "e" to "3", "a" to "4", "s" to "5", "t" to "7", "b" to "8" and/or "g" to "9".

For example, if Ashish took his password from the first sentence of The Fellowship of the Ring -- "This book is largely concerned with Hobbits, and from its pages a reader may discover much of their character and a little of their history" -- Ashish would have reduced that to "tbilcwhafiparmdmotcaaloth". Then the password might be "tbilcwh", "7b1lcwh4f", "a", "4", or "4al07h", etc.

Ashish has a special extension installed in his browser that will prevent his computer from uploading any string that contains his password. In order to figure out which passage of text he took his password from, Ashish has created a webpage to take advantage of this extension. Every second, the webpage will tell the browser to post a "password string" for a new passage of text: a string that contains all of the possible passwords that Ashish could have chosen from that passage of text. As soon as his browser fails to post such a string, Ashish will know where he took his password from.

For example, if $k = 2$ and the passage of text contains words starting with the letters "google", then one password string for that passage is "goo0og00gle9o909l3". All substrings of length $\leq 2$ from the original string, and all of their l33tspeak equivalents, are contained in the new string.

Given the first letters of the words in a passage of text, what is the minimum number of characters in the "password string" of that passage?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case consists of two lines. The first line contains the integer $k$. The second line contains a string $S$, representing the first letters of the words in a passage of text. $S$ contains only the characters 'a' - 'z', with no spaces.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the minimum number of characters in the password string for $S$.
## 样例

### 样例输入 #1
```
4
2
poppop
2
google
2
tbilcwhafiparmdmotcaaloth
10
tbilcwhafiparmdmotcaaloth
```
### 样例输出 #1
```
Case #1: 6
Case #2: 18
Case #3: 53
Case #4: 1136
```
## 提示

**Sample Explanation**

- In the first sample input, one possible password string is "0ppop0".
- In the second sample input, one possible password string is "goo0og00gle9o909l3".

**Limits**

- $1 \leq T \leq 20.$
- $S$ will contain at least $2 \times k$ characters.
- There will exist a password string with at most $10^{18}$ characters.

**Test set 1 (7 Pts, Visible Verdict)**

- $S$ will contain at most 1000 characters.
- $k = 2.$

**Test set 2 (36 Pts, Hidden Verdict)**

- $S$ will contain at most 5000 characters.
- $2 \leq k \leq 500.$


---

---
title: "[NOI2013] 小 Q 的修炼"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1335
tag: ['模拟', '字符串', '2013', 'NOI', '提交答案', 'Special Judge', '枚举']
---
# [NOI2013] 小 Q 的修炼
## 题目描述

小 Q 最近发现了一款新游戏，游戏的目标是从一个新手修炼成为武功高强的大侠。面对错综复杂的游戏世界，小 Q 要对他面临的每件事情做出谨慎的选择。例如，是否参加一个陌生人邀请的比武；同意或是拒绝用宝剑交换他人的武功秘籍......而小 Q 做出的每一个选择都有可能影响到他以后的发展：面对一个高手，若主动与之比武，很可能会损失惨重；但若不去比武，也许今后就再也见不到这个高手了。

对着这个游戏，小 Q 玩了很多次仍然玩不出他想要的结局，于是他费尽千辛万苦找到了游戏的剧本。令人惊讶的是,游戏的剧本并不像我们平时见到的剧本，反而很像代码。这个剧本是这样描述的：
- 量：有 $2$ 种量，常数和变量。
- 常数：一个整数。
- 变量：初始值为 $0$ 的可变整数，不同变量用不同正整数编号区分。
- 事件：整个剧本由若干个事件构成。所有的事件按照给定的顺序从 $1$ 开始依次编号。事件共有 $3$ 种：普通事件、选择跳转和条件跳转。
- 执行位置：一个整数，表示接下来将会执行的事件编号，如果不存在这个编号的事件则停止，即游戏到了一个结局。最初的时候执行位置为 $1$。
- 普通事件：一个变量增加或减少一个量的值。之后执行位置增加 $1$。
- 选择跳转：两个整数。执行到这里时玩家需要在这两个整数中选择一个，之后执行位置将被修改为这个整数。
- 条件跳转：两个量和两个整数。执行到这里时，若第一个量小于第二个量，则执行位置将被修改为第一个整数，否则将被修改为第二个整数。

小 Q 认为，整个游戏是希望一个叫做「成就值」的变量（编号为 $1$）最大。
## 输入格式

该题为提交答案型试题，所有输入数据 `train1.in`~`train10.in` 已在附加文件中。

输入的第一行包含两个正整数 $n, m$，表示事件的个数和变量的个数。

接下来有 $n$ 行，每行描述一个事件。这些事件按照给出的顺序依次编号为 $1$ 到 $n$。

描述量和事件的格式如下（格式中 `#`表示空格）


| 类型 | 格式 | 例子 |
|:-:|:-:|:-:|
| 常数 | `c#整数` | `c -2` |
| 变量 | `v#正整数` | `v 5` |
| 普通事件 | `变量#+#量` | `v 1 + c 1` |
| 普通事件 | `变量#-#量` | `v 2 - c 2` |
| 选择跳转 | `s#整数 1#整数 2` | `s 10 20` |
| 条件跳转 | `i#量 1#量 2#整数 1#整数 2` | `i c 99 v 2 0 1` |

## 输出格式

针对给定的 $10$ 个输入文件 `train1.in`~`train10.in`，你需要分别提交你的输出文件 `train1.out`~`train10.out`。

每个文件需要输出若干行，每行输出一个字符 `1` 或 `2`，表示执行过程中遇到的每个选择跳转所作的选择。输出的行数需要严格等于此次游戏执行过程中遇到的选择跳转的个数。
## 样例

### 样例输入 #1
```
11 2
v 2 + c 19
i v 2 c 3 7 3
s 4 7
v 1 + c 13
v 2 - c 3
i c 0 c 1 2 0
i v 2 c 5 12 8
s 9 12
v 1 + c 23
v 2 - c 5
i c 0 c 1 7 0

```
### 样例输出 #1
```
1
1
1
2
1
1

```
## 提示

### 评分标准

对于每组数据，我们采用如下方式评分：
- 如果你的输出不合法,得 $0$ 分。
- 如果你的输出执行了超过 $10^6$ 行剧本,得 $0$ 分。
- 如果你的输出能让剧本正常结束，得 $1$ 分。
- 如果你的输出能让剧本正常结束，且结束时成就值为正数，得 $2$ 分。

我们设置了 $8$ 个评分参数 $a_3 , a_4 , \ldots , a_{10}$。

如果你的输出能让剧本正常结束，且结束时成就值不小于 $a_s$，得 $s$ 分。

如果以上条目有多项满足，则取满足条件中的最高得分。

### 如何测试你的输出

我们提供 `checker` 这个工具来测试你的输出文件是否是可接受的。使用这个工具的方法是，首先进入终端，在终端中运行下面的命令进入本题的文件夹：

`cd train`

然后运行：

`./checker <case_no>`

其中 `case_no` 是测试数据的编号。例如

`./checker 3`

将测试 `train3.out` 是否可以接受。

在你调用这个程序后，`checker` 将根据你给出的输出文件给出测试的结果，其中包括：
- 非法退出：未知错误。
- `Input/Output file does not exist.`：输入/输出文件不存在。
- `Output invalid.`：输出文件有误,此时可能包含具体错误信息。
- `Correct! Your answer is x.`：输出可接受,最后的成就值为 $x$。

### 更多功能
`checker` 还可以检查任意输入输出文件的测试结果，方法是在终端中运行：

`cd train`

`./checker <input_file_name> <output_file_name>`

其中 `input_file_name` 和 `output_file_name` 分别是输入输出文件的名称。例如

`./checker train3.in train3.out`

将测试 `train3.out` 是否可以接受。

使用 `-w` 可以输出每步运行的结果。用法是

`./checker -w <input_file_name> <output_file_name>`

或者

`./checker -w <case_no>`

例如

`./checker -w train3.in train3.out`

### 特别提示

如果选手使用自己生成输入文件进行调试，有可能因规模过大造成 checker 出错。若发生这类情况，请尝试较小规模的数据。


---

---
title: "[USACO16OPEN] Bull in a China Shop P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3148
tag: ['模拟', '2016', '二分', 'USACO', 'O2优化', '哈希 hashing', '前缀和']
---
# [USACO16OPEN] Bull in a China Shop P
## 题目描述

Farmer John has decided his home needs more decoration. Visiting the local china shop, he finds a delicate glass cow figurine that he decides to purchase, knowing that it will fit perfectly on the mantel above his fireplace.

The shape of the cow figurine is described by an $N \times M$ grid of haracters like the one below ($3 \leq N, M \leq 500$), where lowercase letter characters are each part of the figurine (indicating different colors) and '.' characters are not.

```
...............
...............
x..x...........
xxxx...........
xxxxaaaaaaa...
.xx.aaaaaaaaa..
....aaaaaaa.aa.
....ll...ll....
....vv...vv....
...............
```

Unfortunately, right before FJ can make his purchase, a bull runs through the shop  and breaks not only FJ's figurine, but many of the other glass objects on the shelves as well!  FJ's figurine breaks into 3 pieces, which quickly becomelost  among $K$ total pieces lying on the ground ($4 \leq K \leq 100$).  Each ofthe $K$ pieces is described by a grid of characters, just like the originalfigurine.

Please help FJ determine how many sets of 3 pieces (out of the $K$ on the floor)could be glued back together to mend his broken figurine.

The pieces on the ground might have been flipped vertically or horizontally, orrotated by some multiple of 90 degrees. Therefore, given the original grid aswell as $K$ grids describing pieces, you want to find sets of 3 pieces that canbe joined together to form the original picture, allowing the pieces to betranslated, flipped, or rotated multiples of 90 degrees.  When thensuperimposed, the 3 pieces should exactly form the original picture, with eachcolored square in the original picture represented in exactly one of the pieces.
## 输入格式

The first line contains a single integer $K$. Following that will be $K + 1$ piece descriptions.  The first description will describe the original glass cow,the following $K$ descriptions will be of the broken pieces.

Each description begins with a line containing two integers $R$ and $C$ ($1 \le R, C \le 100$).  The following $R$ lines contain $C$ lowercase alphabet characters describing the color of each cell.  Each piece will be horizontally/vertically connected and have at least one non-empty cell.

## 输出格式

Output the number of triples $i, j, k$ ($i < j < k$) such that pieces $i$, $j$, and $k$ can be arranged to form the original glass cow.
## 样例

### 样例输入 #1
```
5
5 5
aaaaa
..a..
bbabb
..a..
aaaaa
3 5
..abb
..a..
aaaaa
5 2
a.
a.
aa
a.
a.
1 2
bb
1 5
bbabb
2 5
aaaaa
..a..
```
### 样例输出 #1
```
3
```
## 提示

The three solutions use pieces $(0, 1, 2)$, $(0, 2, 4)$, $(1, 3, 4)$.

Note that this problem has a time limit of 6 seconds per test case (and twice that  for Java and Python submissions).
## 题目翻译

### 题目描述

Farmer John 决定给他的家增添一些装饰。在当地的瓷器店里，他发现了一尊精致的玻璃牛雕像，决定购买它，因为它完美地适合放在壁炉上方的壁炉架上。

牛雕像的形状由一个 $N \times M$ 的字符网格描述（$3 \leq N, M \leq 500$），其中小写字母字符代表雕像的各个部分（表示不同的颜色），而 '.' 字符则不代表雕像部分。

```cpp
...............
...............
x..x...........
xxxx...........
xxxxaaaaaaa...
.xx.aaaaaaaaa..
....aaaaaaa.aa.
....ll...ll....
....vv...vv....
...............
```

不幸的是，就在 FJ 准备购买之前，一头公牛冲进了商店，不仅撞碎了 FJ 的雕像，还撞碎了许多其他货架上的玻璃制品！FJ 的雕像碎成了 3 块，并迅速混入了地上的 $K$ 块碎片中（$4 \leq K \leq 100$）。每一块碎片都由一个字符网格描述，就像原来的雕像一样。

请帮助 FJ 确定有多少组 3 块碎片（地上的 $K$ 块中）可以粘合在一起修复他破碎的雕像。

地上的碎片可能被垂直或水平翻转，或者旋转了 90 度的倍数。因此，给定原始网格以及描述碎片的 $K$ 个网格，你需要找到可以组合成原始图片的 3 块碎片，允许碎片被平移、翻转或旋转 90 度的倍数。当这 3 块碎片叠加在一起时，它们应该准确地形成原始图片，且原始图片中的每个彩色方块都恰好出现在一块碎片中。

### 输入格式

第一行包含一个整数 $K$。接下来是 $K + 1$ 个碎片的描述。第一个描述是原始玻璃牛的描述，接下来的 $K$ 个描述是破碎的碎片。

每个描述以两个整数 $R$ 和 $C$（$1 \le R, C \le 100$）开始。接下来的 $R$ 行包含 $C$ 个小写字母字符，描述每个单元格的颜色。每块碎片在水平/垂直方向上都是连通的，并且至少有一个非空单元格。

### 输出格式

输出满足条件的三元组 $i, j, k$（$i < j < k$）的数量，使得碎片 $i$、$j$ 和 $k$ 可以排列成原始玻璃牛。

### 说明/提示

三个解决方案使用了碎片 $(0, 1, 2)$、$(0, 2, 4)$ 和 $(1, 3, 4)$。

请注意，这个问题每个测试用例的时间限制为 6 秒（Java 和 Python 提交的时间限制为 12 秒）。


---

---
title: "辉夜姬的十道难题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3798
tag: ['模拟', '动态规划 DP', '搜索', '贪心', '洛谷原创', '提交答案', '剪枝', '记忆化搜索']
---
# 辉夜姬的十道难题
## 题目背景

妹红最近玩了一款叫 $2048$ 的小游戏。

![](https://cdn.luogu.com.cn/upload/pic/5857.png)

(图为个人无撤销最高纪录~ 纯手玩)。
## 题目描述

$2048$ 是一个非常简单的数字游戏，它在 $4\times 4$ 的棋盘上进行，通过移动来合并数字，达到 $2048$ 即算胜利。妹红最近沉迷上了这个游戏，事情传到辉夜那里后，辉夜决定用曾经无人破解的十道难题来考考妹红。

游戏规则：

1. 游戏在 $n\times m$ 的方格棋盘上进行。

2. 两个玩家，其中一个可以移动棋盘上的数字，记做 M，另外一个可以向棋盘上放数字，记做 C。

3. 移动数字的规则如下：可以向上/下/左/右四个方向的其中之一移动。选定好方向后，所有数字都会向该方向靠拢，相同的两个数字相撞时会合并成一个新数字，这个数字是它们的和。在一次移动中，每个数字最多只能合并一次，优先合并靠近移动方向棋盘边缘的数字。

以 $n=2,m=4$ 的情况举例如下（$0$ 表示该位置为空）：

```
2 2 2 2
2 2 0 2
```

向左移动后变为：

```
4 4 0 0
4 2 0 0
```

每次合并后，将会获得一定的分数，获得的分数等于所有合并后数字相加之和。若无任何合并发生，则不得分。在上例中，得分为 $12$。

移动前后，若棋盘上的所有数字大小和位置均没有变化，则不算做有效移动，否则即是有效移动。

4. 向棋盘放置数字的规则如下：只能选择棋盘上没有数字的位置放置一个数字，可以放置的数字和放置方法在每个子任务中会具体描述。

5. 游戏开始时棋盘为空，分数为 $0$。先由玩家 C 行动两步，接着玩家 M 和 C 轮流行动，中间的每一步都必须是有效的。当轮到玩家 M 时，若不能够进行有效移动，则游戏结束，此时的得分为最终得分。

本题目为提交答案题，共有 $10$ 个子任务需要你来完成。将你的答案写到 $10$ 个文件中，分别命名为 ```gamex.out```，$x$ 表示子任务的编号（$0\ldots 9$）。

子任务内无部分分，你可以得到该任务的分数当且仅当你的输出和标准答案完全相同。

十道难题如下:

0. $n=1,m=2$。玩家 C 行动时可以放置 $2$ 或 $4$。若用 $x$ 表示在一局游戏中玩家 M 最多可以行动 $x$ 次，那么这个 $x$ 的最值是多少？输出两行，第一行一个整数表示 $x$ 的最小值，第二行一个整数表示 $x$ 的最大值。

1. $n=10738029,m=921023$。玩家 C 行动时可以放置 $2$ 或 $4$。若用 $x$ 表示棋盘上所有数字之和，请问 $x$ 的最大值是多少。因为这个值可能过大，只需要输出它除以 $10^9+7$ 的余数即可。

2. $n=2,m=2$。玩家 C 行动时可以放置 $2,4$。用 $x$ 表示目标数字， $x$ 一定为 $2$ 的正整数幂。玩家 M 的目标是使盘面上出现大于等于数字 $x$ 的数，玩家 C 的目标是在盘面上出现数字 $x$ 之前使游戏结束。在两方均最优决策的情况下，求一个最大的 $x$，使得玩家 M 能达到自己的目标。

3. $n=4,m=4$。玩家 C 行动时可以放置 $2,4$。输出两行，每行一个数字。第一行的数字表示能达到的最大分数。第二行的数字表示当数字总和达到最大时，分数的最小值。

4. $n=7393,m=9133$。玩家 C 可以放置数字 $2$ 共 $6144$ 次。棋盘初始为空，初始分数为 $0$。首先由玩家 C 连续行动，直到用完所有放置机会或中途主动放弃。然后连续向上移动直到向上方向不能构成有效移动。输出一行一个整数，表示最大得分。

5. $n=7,m=233$。初始分数为 $0$,玩家 C 可以放置数字 $2$ 共 $233$ 次，数字 $4$ 共 $66$ 次。棋盘第一行一开始有若干数字，第 $i$ 列的数字为 $\text{lowbit}(i)\times 2$，$\text{lowbit}(i)$ 表示数字 $i$ 的二进制形式只取最后一个 $1$ 构成的数字。如 $\text{lowbit}(1\ldots 8)$ 为 $1,2,1,4,1,2,1,8$。棋盘的其他位置均为空。首先由玩家 C 连续行动，直到用完所有放置机会或中途主动放弃。然后连续向上移动直到向上方向不能构成有效移动。输出一行一个整数，表示最大得分。

6. $n=3,m=3$。玩家 C 行动时可以放置 $2,4$。用 $x$ 表示目标数字，$x$ 一定为 $2$ 的正整数幂。玩家 M 的目标是使盘面上出现数字 $x$，玩家 C 的目标是在盘面上出现数字 $x$ 之前使游戏结束。在两方均最优决策的情况下，输出一个最大的 $x$，使得玩家 M 能达到自己的目标。

7. $n=3,m=3$。玩家 C 行动时可以放置 $2,4$。玩家 M 的目标是让得分最大化，玩家 C 的目标是让得分最小化，在两方均最优决策的情况下，输出一个整数，表示最终的分数。

8. $n=3,m=3$。玩家 C 行动时，有 $90\%$ 的几率放置一个 $2$，$10\%$ 的几率放置一个 $4$，放置在各个空位的几率均等。用 $x$ 表示目标数字，玩家 M 的目标是使盘面上出现大于等于数字 $x$ 的数。在玩家 M 最优决策的情况下，输出一行，$9$ 个实数，四舍五入到小数点后 $2$ 位，用空格隔开，分别表示 $x=2,4,8,16,32,64,128,256,512$ 时，达成目标数字的概率。

9. $n=3,m=3$。玩家 C 行动时，有 $90\%$ 的几率放置一个 $2$，$10\%$ 的几率放置一个 $4$，放置在各个空位的几率均等。玩家 M 的目标是让分数最大化。在玩家 M 最优决策的情况下，输出一个实数，四舍五入保留整数，表示分数的期望值。

妹红虽然对 $2048$ 有一定了解，但她并不能解决全部的问题，于是就交给了学 OI 的你。
## 输入格式

见题目描述

## 输出格式

见题目描述

## 样例

### 样例输入 #1
```
样例任务（无需提交）:
 n=2,m=2。 玩家C行动时只可以放置2。请输出一个整数，表示棋盘上可能出现的最大数字。

```
### 样例输出 #1
```
16
```
## 提示

如果对移动规则有疑惑，可以到 $2048$ 网站进行尝试:

http://gabrielecirulli.github.io/2048/

by-orangebird



---

---
title: "[CTSC2010] 产品销售"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4217
tag: ['2010', '线段树', '模拟费用流', 'CTSC/CTS']
---
# [CTSC2010] 产品销售
## 题目描述

A 公司正在热销某计算机产品，作为 A 公司 CEO 的小 A 打算为接下来连续的 $N$ 个销售季度制定一份具体的生产和销售方案。 已知第 $i$ 个销售季度该产品的订购量为 $D_i$，在第 $i$ 个季度，A 公司会通过如下几种方式来解决用户的订购需求：

○ 在第 $i$ 个季度生产新的产品来销售。

○ 若在第 $i$ 个季度以前库存还有多余的产品，则可以直接在第 $i$ 个季度销售(注意第一个季度之前没有任何库存产品)。

○ 在第 $i$ 个季度可以不完成全部的订购需求，而将未完成的订购需求推迟，归入到下一个季度$(i + 1)$的产品订购需求中。

A 公司需要考虑以下几种耗费： 生产新产品的成本耗费、库存产品的额外储存耗费以及推迟订购需求而需要赔偿给用户的损失费。另外由于劳力和资源的限制，每个销售季度能够生产新产品的数量是有限的，各季度的耗费和可以生产的产品上限数也不尽相同，具体如下：

○ 在第 $i$ 个季度最多可以生产 $U_i$ 件新的产品，每一件的成本为 $P_i$。

○ 第 $i$ 个季度保存下来的产品，可以用于以后季度的销售。对于每一件产品，若从第 $i$ 季度保存到第 $i + 1$ 季度， 需要额外支付 $M_i$ 的存储费用(注意产品保存到下个季度后可能再次库存)。

○ 对于第 $i$ 个季度需要推迟而归入到下一个季度订购需求的每一件产品， A
公司需要赔偿给用户损失费 $C_i$(注意延迟到下个季度可能再次被延迟, 费
用按后面季度的延迟费用计)。

在第 $N$ 个季度结束后， A 公司必须解决之前所有的用户订单。可以保证， A公司能够生产的产品总数不会低于总订购量， 也就是说一定存在一组生产和销售方案使得满足所有的用户订购需求。小 A 想知道如何来安排产品的生产和销售，使得在满足所有订购需求的前提下公司总的耗费最小。
## 输入格式

输入文件 $\tt{product.in}$ 第一行是一个正整数 $N$，表示有 $N$ 个销售季度。

第二行有 $N$ 个非负整数 $D_1$, $D_2$, .., $D_N$，表示第 $i$ 个季度的订购量。

第三行有 $N$ 个非负整数 $U_1$, $U_2$, .., $U_N$，表示第 $i$ 个季度最多可以生产的新的产品数。

第四行有 $N$ 个非负整数 $P_1$, $P_2$, .., $P_N$，表示第 $i$ 个季度生产一件新产品的成本。

第五行有 $N - 1$ 个非负整数 $M_1$, $M_2$, ..,$M_{N-1}$，表示将一件产品从第 $i$ 个季度保存到第 $i +1$ 个季度所需要的额外的耗费。

第六行有 $N-1$ 个非负整数 $C_1$, $C_2$, .., $C_{N-1}$，表示一件产品的订购需求在第 $i$ 个季度没有完成而归入到第 $i +1$ 个季度的订购量中，需要赔偿给用户的损失费。
## 输出格式

输出文件 $\tt{product.out}$ 仅包含一个非负整数，表示公司的最小总耗费。
## 样例

### 样例输入 #1
```
4
3 2 1 2
2 5 2 2
5 1 5 5
1 2 1
5 3 3
```
### 样例输出 #1
```
30
```
## 提示

【样例说明】

第一个季度生产 $2$ 件产品，第二个季度生产 $5$ 件产品，第三个季度不生产产品，第四个季度生产 $1$ 件产品，成本为 $2 * 5 + 5 * 1 + 0 * 5 + 1 * 5 = 20$。

因为第一个季度最多只能生产 $2$ 件产品，无法满足 $3$ 件的订购量，因此将 $1$件产品的订购量推迟到第二个季度，赔偿给用户的损失费为 $5$。

第二个季度由于第一个季度推迟了一件产品的订购需求， 因而订购量变为 $3$。该季度生产了 $5$ 件产品，剩下的 $2$ 件保存下来。第三个季度直接销售库存的产品，再多出来的 $1$ 件产品继续储存到第四个季度，加上第四个季度生产了 $1$ 件产品，因此满足了所有订单需求。总的储存费用为 $2 * 2 + 1 * 1 = 5$。

总的费用为 $20 + 5 + 5 = 30$。

【数据规模】

对于 $30\%$的数据， $N \leq 1,000$。

对于 $100\%$的数据， $1 \leq N \leq 100,000$， $1 \leq D_i, U_i, P_i, M_i,C_i \leq  10,000$。


---

---
title: "[NOI2019] 序列"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5470
tag: ['贪心', '2019', 'NOI', 'O2优化', '优先队列', '模拟费用流']
---
# [NOI2019] 序列
## 题目描述

给定两个长度为 $n$ 的正整数序列 $\{a_i\}$ 与 $\{b_i\}$，序列的下标为 $1, 2, \cdots , n$。现在你需要分别对两个序列各指定**恰好** $K$ 个下标，要求**至少**有 $L$ 个下标在两个序列中都被指定，使得这 $2K$ 个下标在序列中对应的元素的总和**最大**。

形式化地说，你需要确定两个长度为 $K$ 的序列 $\{c_i\}, \{d_i\}$，其中
$1 \leq c_1 < c_2 < \cdots < c_K \leq n , 1 \leq d_1 < d_2 < \cdots < d_K \leq n$

并要求 $\{c_1, c_2, \cdots , c_K\} \cap \{d_1, d_2, · · · , d_K\}\geq L$

目标是最大化 $\sum^{K}_{i=1} a_{c_i} +\sum^{K}_{i=1} b_{d_i}$

## 输入格式

**本题输入文件包含多组数据**。

第一行一个正整数 $T$ 表示数据组数。接下来每三行表示一组数据。

每组数据第一行三个整数 $n, K, L$，变量意义见题目描述。

每组数据第二行 $n$ 个整数表示序列 $\{a_i\}$。

每组数据第三行 $n$ 个整数表示序列 $\{b_i\}$。
## 输出格式

对于每组数据输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
5
1 1 1
7
7
3 2 1
4 1 2
1 4 2
5 2 1
4 5 5 8 4
2 1 7 2 7
6 4 1
1 5 8 3 2 4
2 6 9 3 1 7
7 5 4
1 6 6 6 5 9 1
9 5 3 9 1 4 2
```
### 样例输出 #1
```
14
12
27
45
62

```
## 提示

### 更多样例

您可以通过附加文件获得更多样例。

#### 样例 2

见选手目录下的 `sequence/sequence2.in` 与 `sequence/sequence2.ans`。

#### 样例 3

见选手目录下的 `sequence/sequence3.in` 与 `sequence/sequence3.ans`。

### 样例 1 解释

第一组数据选择的下标为：$\{c_i\} = \{1\} , \{d_i\} = \{1\}$。

第二组数据选择的下标为：$\{c_i\} = \{1, 3\} , \{d_i\} = \{2, 3\}$

第三组数据选择的下标为：$\{c_i\} = \{3, 4\} , \{d_i\} = \{3, 5\}$。

第四组数据选择的下标为：$\{c_i\} = \{2, 3, 4, 6\} , \{d_i\} = \{2, 3, 4, 6\}$。

第五组数据选择的下标为：$\{c_i\} = \{2, 3, 4, 5, 6\} , \{d_i\} = \{1, 2, 3, 4, 6\}$。

### 数据范围

对于所有测试点：$T \leq 10 , 1 \leq \sum n \leq 10^6, 1 \leq L \leq K \leq n \leq 2 \times 10^5, 1 \leq a_i, b_i \leq 10^9$。

| 测试点编号 | $n\le$ | $\sum n \le$ |
| :----------: | :----------: | :----------: |
| $1\sim3$ | $10$ | $3\times 10^5$ |
| $4\sim5$ | $18$ | $3\times 10^5$ |
| $6\sim7$ | $30$ | $3\times 10^5$ |
| $8\sim10$ | $150$ | $3\times 10^5$ |
| $11\sim16$ | $2\times 10^3$ | $3\times 10^5$ |
| $17\sim21$ | $2\times 10^5$ | $3\times 10^5$ |
| $22\sim25$ | $2\times 10^5$ | $10^6$ |


---

---
title: "[BalticOI 2010] Lego (Day1)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6762
tag: ['模拟', '搜索', '2010', 'BalticOI（波罗的海）', '状压 DP']
---
# [BalticOI 2010] Lego (Day1)
## 题目描述

给定一些 $2 \times 2$ 的乐高方块，分别有白色（W），灰色（G）和黑色（B）。现在您要往 $6 \times 6$ 的底板上放置方块，需要保证不能有完全浮空的方块（即四个方格均无放置的地方）也不能超出 $6 \times 6$ 的底板。

现在给定一个放置完方块的底板的一面的示意图，和这一面逆时针旋转 $90^\circ$ 后的一面的示意图，求有多少种放置方块的方法数。
## 输入格式

第一行一个整数 $H$ 代表这种放置方块的高度。    
接下来 $H$ 行每行六个字符，代表从这一面看到的示意图。    
接下来 $H$ 行每行六个字符，代表从上一面逆时针旋转 $90^\circ$ 后的示意图。   
只能从前面，后面，左面，右面看，不能从上面，下面看。
## 输出格式

一行一个整数代表答案。          
答案保证在 64 位有符号整数内。
## 样例

### 样例输入 #1
```
2
WWGG..
.BB.WW
.WGG..
WWGG..
```
### 样例输出 #1
```
6
```
## 提示

#### 样例 1 解释

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/njr2rk9l.png)

第一个是从 $A$ 面观察到的示意图。    
第二个是从 $B$ 面（$A$ 面逆时针旋转 $90^\circ$）观察到的示意图。

下面是这 $6$ 种情况（感谢 Vonov 提供的图片！）：

![](https://cdn.luogu.com.cn/upload/image_hosting/wymozlif.png)         
![](https://cdn.luogu.com.cn/upload/image_hosting/1vw0fu3t.png)         
![](https://cdn.luogu.com.cn/upload/image_hosting/umn2hync.png)             
![](https://cdn.luogu.com.cn/upload/image_hosting/pykojvay.png)           
![](https://cdn.luogu.com.cn/upload/image_hosting/9z9wvzxp.png)          
![](https://cdn.luogu.com.cn/upload/image_hosting/hkp3tjfp.png)

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le H \le 6$。

#### 说明

翻译自 [BalticOI 2010 Day1 B Lego](https://boi.cses.fi/files/boi2010_day1.pdf)。


---

---
title: "[THUWC 2017] 大葱的神力"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6849
tag: ['动态规划 DP', '搜索', '2017', '提交答案', 'Special Judge', '剪枝', '模拟退火', '背包 DP', '费用流', '随机化', 'THUWC']
---
# [THUWC 2017] 大葱的神力
## 题目背景

**本题为提交答案题。**

大葱是我国自古以来的美食，像我国传统美食北京烤鸭，用鸭子点缀出大葱的香味，令人赞不绝口。民间也流传着有「每天一棵葱，不当单身狗」的说法。

然而，大葱要发挥出独属于自己的神力，也是有条件的。
## 题目描述

现在小葱同学有 $N$ 棵大葱和 $M$ 个抽屉，将第 $i$ 棵大葱放到第 $j$ 个抽屉里面会产生 $w_{i,j}$ 的神力。自然小葱同学希望获得尽量多的神力，但是抽屉有着容积的限制，大葱也有着自己的体积。第 $i$ 棵大葱的体积为 $a_i$，第 $j$ 个抽屉的容积为 $b_j$。一个抽屉里面装着的大葱的体积之和不能超过这个抽屉的容积，一棵大葱不能拆分放到两个抽屉中。

小葱同学现在想知道，在这样的条件下，这些大葱最多会产生多少的神力？
## 输入格式

**本题为提交答案题**，输入文件为 `drawer1.in ~ drawer10.in`，详见附加文件。

第一行两个整数 $N,M$，代表大葱的个数和抽屉的个数。

接下来一行 $N$ 个整数，代表每棵大葱的体积。

接下来一行 $M$ 个整数，代表每个抽屉的容积。

接下来 $N$ 行每行 $M$ 个整数，第 $i$ 行第 $j$ 个数代表第 $i$ 棵大葱放到第 $j$ 个抽屉中会产生的神力。
## 输出格式

输出文件为 `drawer1.out ~ drawer10.out`，分别对应相应的输入文件。

对于每组输入数据，输出 $N$ 行每行一个整数，第 $i$ 个数代表第 $i$ 棵大葱被放到了哪个抽屉里面。如果第 $i$ 棵大葱没有被放到任何一个抽屉里面，则输出 $0$。
## 样例

### 样例输入 #1
```
3 4
1 1 2
2 1 2 3
1 2 1 1
2 1 2 1
3 1 0 1
```
### 样例输出 #1
```
2
0
1
```
## 提示

#### 样例说明

样例只是一种合法情况，获得的总神力值为 $2+3=5$。

#### 评分方式

**本题使用 Special Judge**，对于每个测试点，我们都有 $10$ 个参数 $a_1,a_2,\cdots,a_{10}$，如果你的输出所产生的的神力 $v$ 满足 $v \ge a_i$，则我们保证该测试点你至少会得到 $i$ 分。

#### 如何测试你的输出

在附加文件中，我们提供了 `scorer.cpp`，请自行编译来测试输出，这个程序将用于评判你的输出能够产生多少的神力。

若编译后文件名称为 `scorer`，在终端（Linux）中，输入以下命令：

```plain
./scorer <input_name> <output_name>
```

或在命令提示符（Windows）中，输入以下命令：
```plain
scorer <input_name> <output_name>
```
来对你的输出进行评判。其中 `<input_name>` 为输入文件名称，`<output_name>` 为输出文件名称。


---

---
title: "[WFOI - 02] I wanna cross the grid（穿越网格）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8224
tag: ['洛谷原创', '提交答案', 'Special Judge', 'O2优化', '模拟退火', '随机调整', '其它技巧', '构造', '洛谷月赛']
---
# [WFOI - 02] I wanna cross the grid（穿越网格）
## 题目背景

>  相信奇迹的人，本身比奇迹更伟大吧

突然，存档点落到了一个巨大的网格中，只有走过所有必经区域，才能出现下一个存档点...
## 题目描述

给定一张 $n$ 行 $m$ 列的网格图，行和列从 $1$ 开始编号，定义二元组 $(x,y)$ 表示第 $x$ 行第 $y$ 列的格子，每一行的第 $L$ 到第 $R$ 列的格子是必经区域，形式化地，设 $D$ 是必经区域集合，则 $D=\{(x,y)|1\leq x\leq n,L\leq y\leq R,x,y\in N_+\}$。

每次 kid 可以向上下左右四个方向走一步，且不能超过边界。形式化地，若现在 kid 现在在 $(x,y)$，则 kid 可以走到 $(x+1,y),(x,y+1),(x-1,y),(x,y-1)$。

初始时 kid 在 $(S_x,S_y)$（保证 $S_y=L$），他需要走过所有的必经区域，且任何一个格子最多只经过一次。形式化地，kid 走的路径形如一个二元组序列 $P=(x_1,y_1),(x_2,y_2)...(x_k,y_k)$，需要满足 $\forall (x_0,y_0)\in D，\exist i\in[1,k]，(x_0,y_0)=(x_i,y_i)$，且 $\forall i\not= j，(x_i,y_i)\not= (x_j,y_j)$。

同时，kid 还要记录一个通关序列 $p$，当 kid 第一次进入某一行的必经区域之后，就要把行号写在当前序列的后面，且立刻经过本行所有的必经区域。同时，$p$ 必须包含一个长度为 $L_q$ 的子序列 $q$ 才是一个合法的通关序列，从而真正通关。形式化地，$p$ 合法当且仅当存在长度为 $L_q$ 的序列 $c$ 满足 $p_{c_i}=q_i$，且 $c$ 单调上升。

同时，为了给 lindongli2004 降低操作难度，lindongli2004 希望 kid 走的步数越少越好。

给定 $n,m,L,R,S_x,S_y,q$，请你为 kid 规划一条通关路线，或者告诉他不存在一条路线。剩下的操作就交给 lindongli2004 吧！
## 输入格式

第一行 $8$ 个正整数 $n,m,L,R,S_x,S_y,L_q,s$，分别表示矩阵的行数和列数，必经区域的左边界和右边界，起点的 $x$ 坐标和 $y$ 坐标，序列 $q$ 的长度和评分参数。

第二行 $L_q$ 个不重复的正整数，表示序列 $q$ 。
## 输出格式

第一行一个字符串 `YES` 或者 `NO` 表示是否存在一条路径（不包含引号）。

若存在一条路径，第二行一个正整数 $cnt$ 表示路径长度，接下来 $cnt$ 行每行两个正整数 $x,y$ 表示路径的坐标。
## 样例

### 样例输入 #1
```
5 4 2 3 2 2 2 15
3 1
```
### 样例输出 #1
```
YES
15
2 2
2 3
3 3
3 2
4 2
4 3
5 3
5 2
5 1
4 1
3 1
2 1
1 1
1 2
1 3
```
## 提示

#### 数据范围：

$1\leq L\leq R\leq m$，$1\leq S_x\leq n$，其他详见下发文件。

#### 评分规则：

下发文件中第一行的最后一个数为 $s$，设你的操作步数为 $cnt$。那么
 - 若 $cnt\leq s$，你将获得 $10$ 分。
 - 若 $cnt> s$ 且能通关，你将获得 $9- \frac{cnt-s}{\lfloor\frac{n}{2}\rfloor}$ 分。
 - 若你不能通关，你将获得 $0$ 分。
 
#### checker：

[自取](/paste/c4omcrf2)

使用方法：在同一目录下，把下发的数据放到 data.in 中，把你的答案放到 data.out 中，编译运行即可。

注意事项：
 - 此 checker 默认存在一组方案，并 check 该方案是否合法。
 - 此 checker 的最大方案容量为 $2.5 \times 10^{8}$ ，也就是说，你的方案中不能有超过 $2.5 \times 10^{8}$ 个数。


---

---
title: "[THUPC 2023 初赛] 乱西星上的空战"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9141
tag: ['模拟', '计算几何', '2023', 'O2优化', 'THUPC']
---
# [THUPC 2023 初赛] 乱西星上的空战
## 题目背景

众所周知，在乱西星的现代战争中，制空权是很重要的。为此，人们发展出了无人机技术——遗憾的是，由于乱西星的算法水平和各种意义上的通讯水平实在太落后了，所以这些无人机只能采用各自独立的傻瓜式战斗模式，这些模式不含任何随机因素，因此一场傻瓜式无人机空战总是几乎能在开始前就被预测到结果。

总而言之，乱西星上正在相互战争的 |\\| 国和 () 国的傻瓜式无人机战斗机编队在其边境交界处的空域遭遇了，现在两国军方希望你能预测这一空战的结果。
## 题目描述

### 空域与时刻

由于乱西星的神秘物理法则，乱西星的时间和空间并不是连续的；若认为遭遇战开始的时刻是第 $1$ 时刻，那么对于任意的第 $k\in \N$ 个时刻，在这一时刻开始和结束时，一个物体（无人机或导弹）只能在形如 $(x,y,z)\in\mathbb Z^3$ 的位置（即空域内的整点）上。

### 无人机

由于空域相比无人机要大得多，因此我们可以将无人机视为一个质点（尽管他们实际上长得和地球上的一般意义上的飞机十分相似）。

#### 飞行状态

在每个时刻，一架无人机的飞行状态可以用以下三组参数描述：

1. 当前时刻所在的坐标 $\vec p=(x,y,z)\in\mathbb Z^3$；
2. 当前时刻的飞行方向向量 $\vec{d},\|\vec d\|=1$；
   - 其中， $\|\vec{v}\|$ 表示向量 $\vec v$ 的长度：设 $\vec{v}=(v_x,v_y,v_z)$，则 $\|\vec{v}\|=\sqrt{v_x^2+v_y^2+v_z^2}$。
   - 你可以简单地将 $\vec d$ 理解为机头指向的方向。
3. 当前时刻的无人机升力线方向 $\vec u,\|\vec u\|=1,\vec u\bot \vec d$；
   - 你可以简单的将 $\vec u$ 理解为飞机所在平面的、从机腹指向机背的单位法向量。
   - 此时，$\vec d$ 和 $\vec u$ 可以唯一确定一个“左手向” $\vec l=\vec u\times \vec d$。

#### 飞行性能

不严格地讲，一般而言，一架飞机通常有三个操作轴，即俯仰、滚转和偏航：俯(负杆)和仰(正杆)分别对应飞机机头向下和向上（即保持 $\vec l$ 不变）；滚转即飞机以飞行方向为中轴线旋转（即保持 $\vec d$ 不变）；偏航则为飞机机头向左或者向右（即保持 $\vec u$ 不变）。由于无人机的特殊设计，其**没有偏航**轴，只能进行俯仰和滚转——容易看出，即使仅进行俯仰和滚转，一架无人机也能随意地改变 $\vec d$ 和 $\vec u$ （在保持 $\|\vec u\|=\|\vec d\|=1,\vec u\bot \vec d$ 的前提下）。

以上的俯仰(正杆或负杆)、滚转操作，以及直线飞行，及其复合统称“机动”。

由于无人机型号差异，一架无人机的飞行性能可以用以下三组参数描述（为方便起见，在本节中，对进行一次机动前的飞行状态对应参数为 $\vec p=(x,y,z),\vec d,\vec u,\vec l$，进行一次机动后的飞行状态对应的参数为 $\vec p'=(x',y',z'),\vec d',\vec u',\vec l'$）：

1. 正杆率 $\theta_u\in(\dfrac\pi4,\dfrac\pi2)$ 和负杆率 $\theta_d\in(\dfrac\pi4,\dfrac \pi2)$；
   - 若无人机**仅进行正杆**机动，则必须有 $\vec p=\vec p',\vec l=\vec l',\vec u\cdot \vec d'\ge 0$；此时，进行一次这样的机动花费的时间是 $\dfrac{\angle(\vec d,\vec d')}{\theta_u}$。
   - 若无人机**仅进行负杆**机动，则必须有 $\vec p=\vec p',\vec l=\vec l',\vec u\cdot \vec d'\le 0$；此时，进行一次这样的机动花费的时间是 $\dfrac{\angle(\vec d,\vec d')}{\theta_d}$。
2. 滚转率 $\gamma\in(\dfrac\pi4,\dfrac \pi 2)$；
   - 若无人机**仅进行滚转**机动，则必须有 $\vec p=\vec p',\vec d=\vec d'$；此时，进行一次这样的机动花费的时间是 $\dfrac{\angle(\vec u,\vec u')}{\gamma}$。
3. 飞行极速 $v_{m}>0$；
   - 若无人机**仅进行直线飞行**，则必须有 $\vec d=\vec d',\vec u=\vec u'$；此时，花费的时间是 $\dfrac{\|\vec p'-\vec p\|}{v_m}$。

#### 合法位移

在每个时刻，若一架无人机可以从 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 这一飞行状态，严格按照**滚转**、**俯仰**(正杆或负杆)和**直线飞行**的顺序进行机动，使飞行状态变为 $\vec p'=(x',y',z')\not=\vec p,\vec d',\vec u',\vec l'$，满足 $\vec d'//(\vec p'-\vec p)$，并且各机动花费的时间之和不超过 $1$，则称这是一次(无人机的)合法的综合机动。

如果一架无人机可以从 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 通过一次合法的综合机动，使飞行状态变为 $\vec p'=(x',y',z')\not=\vec p,\vec d',\vec u',\vec l'$，并且在所有使飞行状态变为 $\vec p''=\vec p',\vec d'',\vec u'',\vec l''$ 的合法综合机动中，总用时是最短的，则称之为一次（无人机的）合法位移（或称该位移合法）。此时，无人机会沿直线从 $\vec p$ 移动到 $\vec p'$。如无特殊指明，下文中“位移”均默认(应当为)合法位移。

#### 眼镜蛇机动

在每个时刻，无论无人机飞行性能如何，无人机总是可以通过眼镜蛇机动，从 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 这一飞行状态，变为 $\vec p'=\vec p,\vec d'=\vec u,\vec u'=-\vec d,\vec l'=\vec l$ 这一飞行状态。注意，这种机动不被视为合法机动。

#### 其它参数

除此之外，一架无人机还具有以下参数：

1. 无人机编号（简称“编号”）；
   - 保证任意两架无人机编号不同。
2. 所在阵营（简称“阵营”）；
   - 所在阵营必须是|\\| 国或者是 () 国中之一，并且双方互称敌方阵营。

#### 坠毁

一架无人机坠毁，当且仅当其符合下列条件之一：

1. 在某激活的导弹位移过程中，与该导弹的距离不大于导弹的空爆距离（详见下文）。
2. 在某导弹位移结束后，与该导弹位置重合（从而导弹直接命中无人机导致坠毁，下同）。
3. 在无人机位移过程中，存在至少一枚激活的导弹，与其距离不大于该导弹的空爆距离。
4. 在无人机位移结束后，存在至少一枚导弹所在位置与其位置重合。
5. 在无人机位移结束后，存在另一架无人机与其坐标相同（从而发生碰撞导致双双坠毁）。

无人机坠毁后将立即消失，此后不会发射导弹，也不会导致其它无人机坠毁。但无人机已经发射的导弹不会立刻消失或爆炸。

此时也称无人机被摧毁。

### 空空红外制导导弹

类似的，一枚空空红外制导导弹（下文简称“导弹”）也可视为一质点，并且同样可以描述其飞行状态和飞行性能。

#### 飞行状态

由于导弹无所谓上下左右，因此仅需要以下两组参数以描述一个导弹的飞行状态：

1. 当前时刻所在的坐标 $\vec p=(x,y,z)\in\Z^3$；
2. 当前时刻的飞行方向向量 $\vec{d},\|\vec d\|=1$；
   - 你可以简单地将 $\vec d$ 理解为导弹弹头指向的方向。

#### 飞行性能

同样由于一枚导弹无所谓上下左右，因此其不存在俯仰、滚转和偏航轴，其向各个方向改变 $\vec d$ 的性能是相同的，此时统称仅改变 $\vec d$ 的操作为 "偏航"。其与直线飞行及复合统称“机动”。

因此一枚导弹的飞行性能可以用以下两组参数描述（为方便起见，在本节中，对进行一次机动前的飞行状态对应参数为 $\vec p=(x,y,z),\vec d$，进行一次机动后的飞行状态对应的参数为 $\vec p'=(x',y',z'),\vec d'$）：

1. 偏航率 $\theta_r\in(\dfrac\pi4,\dfrac\pi2)$；
   - 若导弹**仅进行偏航**机动，则必须有 $\vec p=\vec p'$；此时，进行一次这样的机动花费的时间是 $\dfrac{\angle(\vec d,\vec d')}{\theta_r}$；
2. 飞行极速 $v_m>0$；
   - 若导弹**仅进行直线飞行**，则必须有 $\vec d=\vec d'$；此时，花费的时间是 $\dfrac{\|\vec p'-\vec p\|}{v_m}$。

#### 合法位移

在每个时刻，若一枚导弹可以从 $\vec p=(x,y,z),\vec d$ 这一飞行状态，严格按照**偏航**和**直线飞行**的顺序进行机动，使飞行状态变为 $\vec p'=(x',y',z')\not=\vec p,\vec d'$，满足 $\vec d//(\vec p'-\vec p)$，并且各机动花费的时间之和不超过 $1$，则称这是一次(导弹的)合法位移（或称该位移合法）。此时，导弹会沿直线从 $\vec p$ 移动到 $\vec p'$。如无特殊指明，下文中“位移”均（应当）默认为合法位移。

#### 其它参数

除此之外，一枚导弹还具有以下参数：

1. 保险距离 $d_s>0$ 和激活状态；
   - 导弹被发射后立即处于未激活状态。
   - 每个时刻结束时，若导弹处于未激活状态，并且发射该导弹的无人机已坠毁，或者与发射该导弹的无人机的距离大于保险距离 $d_s$ 时，进入激活状态。此后将保持激活状态，并称该导弹被激活，或称其为一枚激活的导弹。
2. 空爆距离 $d_p>0$；
   - 每次导弹位移过程中，当一枚激活的导弹与任一无人机（包括发射该导弹的无人机）距离不大于 $d_p$ 时，该导弹会进入可空爆状态（详见下文“可空爆”）。
   - 每次无人机位移过程中，若存在一无人机与一枚激活的导弹距离不大于 $d_p$ 时，该导弹也会进入可空爆状态。
3. 最大锁定角 $\beta_s\in(\dfrac\pi4,\dfrac\pi2)$；
   - 任意时刻，一枚飞行状态为 $\vec p=(x,y,z),\vec d$、最大锁定角的导弹能锁定到 $\vec p'$ 处的无人机，当且仅当 $\vec d\cdot(\vec p'-\vec p)>0$，并且 $\angle(\vec d,\vec p'-\vec p)\le \beta_s$。
   - 此时称该无人机能被该导弹锁定，或称其在导弹的锁定范围内。
   - 称 $\angle(\vec d,\vec p'-\vec p)$ 为锁定角。
4. 制导时长 $t_z>0$；
   - 若导弹在第 $k$ 个时刻被发射，则到第 $k+t_z$ 个时刻结束时，若导弹仍未爆炸，则导弹会立刻消失（见“爆炸、消失与可空爆”）。此时称导弹超过制导时长。

#### 爆炸、消失与可空爆

一枚导弹在符合下列全部条件时，会立刻爆炸并消失：

1. 在导弹位移开始前，导弹处于激活状态；

2. 符合以下条件之一：
   
   1. 在该导弹位移过程中，存在一架位于 $\vec q$ 的无人机，使 $\min_{\lambda\in[0,1]}\|\lambda \vec p+(1-\lambda)\vec p'-\vec q\|\le d_p$，其中  $\vec p,\vec p'$ 为导弹本次位移的起点和终点。
      
      - 此时，所有这样的无人机都会被该导弹摧毁。同时，一架无人机可能同时被若干枚导弹摧毁。
   
   2. 在无人机位移过程中，存在一架无人机，记其从位置 $\vec q$ 位移到 $\vec q'$ ，满足 $\min_{\lambda\in[0,1]}\|\lambda \vec q+(1-\lambda)\vec q'-\vec p\|\le d_p$，其中 $\vec p$ 为导弹此时的位置。
      
      - 此时，所有这样的无人机都会被该导弹摧毁。同时，该导弹也可能同时摧毁若干这样的无人机。

此时，称该导弹可空爆，或该导弹进入可空爆状态。

一枚导弹在符合下列条件之一时，不会发生爆炸，但是会在当前时刻结束时消失：

1. 导弹脱锁（见下文“导弹脱锁”），并且在当前时刻开始时已被激活；

2. 导弹超过制导时长；

3. 导弹未激活，并且导弹位移结束后与一无人机位置重合；
   
   - 此时，该无人机会被这枚导弹摧毁。同时，一架无人机可能同时被若干枚导弹摧毁。

4. 导弹未激活，无人机位移结束后，该导弹与一无人机位置重合。
   
   - 此时，该无人机会被这枚导弹摧毁。同时，一枚导弹可能同时摧毁若干这样的无人机。

### 无人机视野、雷达搜索与导弹锁定

#### 无人机视野

任意时刻，一架飞行状态为 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 的无人机能够发现一架位于 $\vec p'=(x',y',z')$ 的无人机，当且仅当 $\vec d\cdot(\vec p'-\vec p)> 0$；此时称 $\vec p'$ 处的无人机在 $\vec p$ 处无人机的视野内。

#### 无人机机载雷达搜索范围

一架无人机的机载雷达（下文简称“雷达”）的扫描范围可以用以下两个参数描述：

1. 水平扫描范围 $L_x\in\N^+$ 和垂直扫描范围 $H_y\in\N^+$；
   - 任意时刻，一架飞行状态为 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 、雷达扫描范围为 $L_x,H_y$ 的无人机的能够扫描到一架位于 $\vec p'$ 的无人机，当且仅当，$\vec d\cdot(\vec p'-\vec p)>0$ 并且 $\exist x,y,s.t.\ |x|\le L_x,|y|\le H_y$ 且 $[\vec p'-(\vec p+x\vec l+y\vec u)]//\vec d$。
   - 即若以 $\vec p$ 为原点、以 $\vec l$ 和 $\vec u$ 为 $X,Y$ 轴建一平面 $\alpha=\alpha(\vec p;\vec l,\vec u)$，则  $\vec p'$ 在这一平面上的投影 $\vec r=P(\vec p';\alpha)$ 应当落在 $[-L_x,L_x]\times [-H_y,H_y]$ 中。
   - 此时称 $\vec p'$ 处的无人机在 $\vec p$ 处无人机雷达扫描范围内。

#### 导弹脱锁

当无人机位移结束后，若一枚导弹选定的目标已坠毁，或其不能被该导弹锁定，则称该导弹脱锁，或处于脱锁状态。

此后将一直保持脱锁状态，无论是否此前选定的无人机是否重新可以被导弹锁定。

### 无人机选定目标策略

任意时刻，无人机（简称"本机"，下同）按下述策略选择目标无人机。

1. 若本机视野内无敌方阵营无人机（简称“敌机”，下同），则本机无选定目标；
2. 否则，若上一时刻本机选择的无人机仍位于本机视野内，则本机仍选定该目标；
3. 否则，若存在至少一架敌机处于本机雷达扫描范围内，则选取其中与本机距离最近的；若与本机距离最近的敌机不唯一，则选取编号最小的。
4. 否则，对视野内的处于 $\vec p'$ 的敌机，记 $\alpha=\alpha(\vec p;\vec l,\vec u),\vec r=P(\vec p';\alpha)=(r_x,r_y)$，则选取 $\min\{|r_x-L_x|,|r_x+L_x|\}+\min\{|r_y-H_y|,|r_y+H_y|\}$ 最小的。若有多个最小值，则同样选择编号最小的。

### 飞行策略

#### 无人机飞行策略

设无人机飞行状态是 $\vec p=(x,y,z),\vec d,\vec u,\vec l$，其飞行极速为 $v_m$，机载雷达扫描范围为 $L_x,H_y$。

1. 若无人机有位于 $\vec p'$ 的选定目标：
   1. 若无人机能够合法地位移到某个位置，使敌机现在的位置 $\vec p'$ 仍处于本机的视野内，则无人机会合法地移动到飞行状态 $\vec q=(x_q,y_q,z_q),\vec d_q,\vec u_q,\vec l_q$，使敌机现在的位置 $\vec p'$ 仍处于本机视野内，且 $\|\vec p'-\vec q\|$ 最小。
      1. 若有多个这样的位置，记 $\alpha_q=\alpha(\vec q;\vec l_q,\vec u_q),\vec r_q=P(\vec p';\alpha_q)=(r_{qx},r_{qy})$，则优先选取使 $\vec r_q=(r_{qx},r_{qy})\in[-L_x,L_x]\times [-H_y,H_y]$ 的位置；
         1. 若仍有多个这样的位置，则选取使 $\|\vec r_q\|=\sqrt{r_{qx}^2+r_{qy}^2}$ 最小的；
         2. 若仍有多个这样的位置，则选取 $\vec q$ 字典序最小的。
      2. 若不存在这样的 $\vec r_q$，则选取使 $\min\{|r_{qx}-L_x|,|r_{qx}+L_x|\}+\min\{|r_{qy}-H_y|,|r_{qy}+H_y|\}$ 最小的；
         1. 若仍有多个这样的位置，则选取 $\vec q$ 字典序最小的。
   2. 否则，无人机会合法地移动到某个位置 $\vec q$，使 $\|\vec q-\vec p-v_m\vec d\|$ 最小；
      1. 若有多个这样的位置，则选取 $\vec q$ 字典序最小的。
2. 否则，无人机通过眼镜蛇机动，将飞行状态变为 $\vec p=(x,y,z),\vec u,-\vec d,\vec l$。

保证在上述1.的情况下，无人机总能合法地移动到某个位置。

#### 导弹飞行策略

设导弹当前时刻飞行状态 $\vec p,\vec d$，其选定的敌机飞行状态为 $\vec p',\vec d',\vec u',\vec l'$；

若上一时刻结束时，导弹未脱锁，则记 $\vec q'$ 为敌机根据其飞行策略，下一时刻会移动到的位置。

若导弹能合法位移到 $\vec q'$，则导弹会直接位移到 $\vec q'$。

否则，导弹会合法地位移到能使敌机位移后的位置 $\vec q'$ 处于锁定范围内的位置 $\vec q$ ，且 $\|\vec q-\vec q'\|$ 最小。

1. 若有多个这样的 $\vec q$，则选取位移后锁定角最小的；
2. 若仍有多种可能，则选取 $\vec q$ 字典序最小的。

若不存在这样的位置，或者上个时刻结束时，导弹已经脱锁，则导弹会合法地位移到某个位置 $\vec q$，使 $\|\vec q-\vec p-v_m\vec d\|$ 最小。

保证导弹总能合法地移动到某个位置。

### 无人机发射导弹规则

一飞行状态为 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 的无人机（简称"本机"）向**被本机选定**的、处于 $\vec p'$ 的目标无人机（简称“敌机”）发射导弹的规则为：

在每个时刻开始时，若选定的敌机已处于本机雷达扫描范围内，且当前不存在由本机发射且未爆炸（或消失）的导弹，则向敌机发射一初始飞行状态为 $\vec p,\vec d=\dfrac{\vec p'-\vec p}{\|\vec p'-\vec p\|}$ 的未激活的导弹，该导弹选定敌机。

### 同一时刻内各事件发生顺序

1. 所有无人机选定目标，并确定当前时刻内的飞行策略；
2. 所有能发射导弹的无人机发射导弹；
3. 所有导弹确定飞行策略并位移，该过程中部分无人机可能被摧毁；
4. 所有可空爆的导弹爆炸并消失；
5. 所有无人机按 1. 中确定的飞行策略位移，该过程中部分无人机可能被摧毁；
6. 所有可空爆的导弹爆炸并消失；
7. 所有位置相同的无人机发生碰撞并坠毁。
8. 所有超过制导时长和脱锁且已激活的导弹消失。
9. 所有可激活的导弹被激活。

### 任务

给定空域开始时（即第 $1$ 时刻开始时），各无人机的飞行性能与状态、导弹的飞行性能，假定这场空战会持续 $T$ 个时刻，双方指挥官希望你能按时间顺序依次给出每个时刻发生的所有重要事件。
## 输入格式

第一行两个正整数 $n,T$ ，表示共有 $2n$ 架无人机，模拟前 $T$ 个时刻。其中，前 $n$ 架阵营是 |\\| 国，后 $n$ 架阵营是 () 国。

接下来有 $2n$ 组数据，每一组包含若干行，其中第 $i$ 组描述了编号为 $i$ 的无人机。

在每组数据中：

第一行三个整数表示 $\vec p\in\mathbb Z^3$；保证所有的 $\vec p$ 两两不同，且坐标的绝对值不超过 $100$。

第二行六个整数依次表示无人机的 $\vec d,\vec u$，保证 $\vec d,\vec u\in S_v$；

- 其中， $S_v=\{(1,0,0),(-1,0,0),(0,1,0),(0,-1,0),(0,0,1),(0,0,-1)\}$；

第三行六个实数依次表示无人机的 $\theta_u,\theta_d,\gamma,v_m,L_x,H_y$；

第四行五个实数和一个正整数依次表示导弹的 $\theta_r,v_m,d_s,d_p,\beta_s,t_z$。
## 输出格式

输出 $T$ 组数据，第 $i$ 组数据表示第 $i$ 个时刻发生的重要事件。

在每组数据中：

第一行三个非负整数 $p_1,p_2,p_3$ ，表示在这个时刻的导弹位移过程中被摧毁的无人机数量、在这个时刻的无人机位移过程中被摧毁的无人机数量、这个时刻结束时，有多少组无人机因位置相同而两两碰撞坠毁。

接下来 $p_1$ 行，每行形如 $id_0\ k\ id_1\ id_2\ \cdots\ id_k$，表示编号为 $id_0$ 的无人机在这个时刻的导弹位移过程中被摧毁，并且在该过程中摧毁该无人机的导弹共有 $k$ 枚，分别来自编号为 $id_1,id_2,\cdots,id_k$ 的无人机。

为保证输出唯一，这 $p_1$ 行中的每一行内，$id_1,\dots,id_k$ 应当从小到大输出，行之间按 $id_0$ 从小到大输出。

接下来 $p_2$ 行，每行形如 $id_0\ k\ id_1\ id_2\ \cdots\ id_k$，表示编号为 $id_0$ 的无人机在这个时刻的无人机位移过程中被摧毁，并且在该过程中摧毁该无人机的导弹共有 $k$ 枚，分别来自编号为 $id_1,id_2,\cdots,id_k$ 的无人机。

为保证输出唯一，这 $p_2$ 行中的每一行内，$id_1,\dots,id_k$ 应当从小到大输出，行之间按 $id_0$ 从小到大输出。

接下来 $p_3$ 行，每行形如 $k\ id_1\ id_2\ \dots id_k$，表示该时刻结束时，有 $k$ 架无人机位置相同 ，它们的编号是 $id_1,...,id_n$。

为保证输出唯一，这 $p_3$ 行中的每一行内，$id_1,\dots,id_k$ 应当从小到大输出，行之间按 $id_1$ 从小到大输出，并且每个编号出现至多一次。
## 样例

### 样例输入 #1
```
1 1
0 0 0
1 0 0 0 0 1
1 1 1 4 1 1
1 3 1 1 1 1
8 0 0
-1 0 0 0 0 1
1 1 1 4 1 1
1 3 1 1 1 1

```
### 样例输出 #1
```
0 0 1
2 1 2

```
### 样例输入 #2
```
1 4
0 0 0
1 0 0 0 0 1
1 1 1 3 1 1
1 15 3 2 1 10
60 0 0
-1 0 0 0 0 1
1 1 1 3 1 1
1 15 3 2 1 10

```
### 样例输出 #2
```
0 0 0
0 0 0
0 0 0
0 2 0
1 1 2
2 1 1

```
## 提示

#### 样例解释 1

在第 $1$ 时刻，两架飞机于 $(4,0,0)$ 处相撞。

#### 样例解释 2

在第 $4$ 时刻，两枚导弹分别摧毁了敌机。

#### 数据范围

$T,n\le 100,3\le v_m\le 20$；

$v_m>10$ 的无人机和导弹总数不超过 $10$；

$\theta_u,\theta_d,\gamma,\theta_r,\beta_s\in(\dfrac\pi4,\dfrac\pi2)$；

$1\le d_s,d_p\le 20,1\le t_z\le 100$；

$|x|,|y|,|z|\le 100$；

$1\le L_x,H_y\le 100$。

所有输入的实数精确到小数点后不超过 $6$ 位。

最初时，$\vec p$ 两两不同。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。


---

---
title: "[POI 2020/2021 R3] Surowa zima"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9404
tag: ['模拟', '贪心', '2020', '平衡树', 'POI（波兰）', '构造', '分类讨论']
---
# [POI 2020/2021 R3] Surowa zima
## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Surowa zima](https://szkopul.edu.pl/problemset/problem/QCCQf92wAoWAOoJ3tHoypvp3/statement/)。

d1t3。
## 题目描述

有一条长 $l$ 米的道路（数轴）。路上有 $n$ 个充电站。每天整条路上（坐标 $[0,l]$）都会落满雪。

有一台机器能扫雪。充一次电可以扫至多 $k$ 米的雪。扫雪是和移动同时进行的，详见样例解释。机器一秒能移动一米，充电不消耗时间。

简单来说，**移动不扫雪不消耗电，需要一秒；移动并扫雪消耗最大电量的 $\bold{\frac1k}$，需要一秒；扫雪必须移动。**

给出每天机器的初始位置，机器初始没电，问每天清除所有雪的最少时间。终点任意。

带修，即充电站可能损坏或修好（第一天之前都是好的），但保证每天都至少有一个好的充电站（所以不会无解）。
## 输入格式

第一行四个整数 $n,l,k,d$。

第二行 $n$ 个整数 $x_1,x_2,\dots,x_n$，表示充电站的位置，保证 $0\leq x_1<x_2<\dots<x_n\leq l$。

接下来 $3d$ 行，描述 $d$ 天的事件：

- 第一行三个整数 $z,u,p$，分别表示昨晚修好的充电站数量，损坏的数量，和机器的初始位置。
- 第二行 $z$ 个整数，表示被修好的充电站编号。
- 第三行 $u$ 个整数，表示损坏的充电站编号。
## 输出格式

$d$ 行，每行一个整数，表示每天的答案。
## 样例

### 样例输入 #1
```
3 5 2 1
2 3 5
0 1 3

2

```
### 样例输出 #1
```
9

```
### 样例输入 #2
```
5 12 1 5
1 3 6 9 11
0 1 1

1
1 1 3
1
2
1 1 6
2
3
1 1 9
3
4
1 1 11
4
5

```
### 样例输出 #2
```
33
33
36
33
33

```
### 样例输入 #3
```
11 100 1 26
0 10 20 30 40 50 60 70 80 90 100
0 5 0

2 4 6 8 10
5 6 4
2 4 6 8 10
1 3 5 7 9 11
6 5 8
1 3 5 7 9 11
2 4 6 8 10
5 6 12
2 4 6 8 10
1 3 5 7 9 11
6 5 16
1 3 5 7 9 11
2 4 6 8 10
5 6 20
2 4 6 8 10
1 3 5 7 9 11
6 5 24
1 3 5 7 9 11
2 4 6 8 10
5 6 28
2 4 6 8 10
1 3 5 7 9 11
6 5 32
1 3 5 7 9 11
2 4 6 8 10
5 6 36
2 4 6 8 10
1 3 5 7 9 11
6 5 40
1 3 5 7 9 11
2 4 6 8 10
5 6 44
2 4 6 8 10
1 3 5 7 9 11
6 5 48
1 3 5 7 9 11
2 4 6 8 10
5 6 52
2 4 6 8 10
1 3 5 7 9 11
6 5 56
1 3 5 7 9 11
2 4 6 8 10
5 6 60
2 4 6 8 10
1 3 5 7 9 11
6 5 64
1 3 5 7 9 11
2 4 6 8 10
5 6 68
2 4 6 8 10
1 3 5 7 9 11
6 5 72
1 3 5 7 9 11
2 4 6 8 10
5 6 76
2 4 6 8 10
1 3 5 7 9 11
6 5 80
1 3 5 7 9 11
2 4 6 8 10
5 6 84
2 4 6 8 10
1 3 5 7 9 11
6 5 88
1 3 5 7 9 11
2 4 6 8 10
5 6 92
2 4 6 8 10
1 3 5 7 9 11
6 5 96
1 3 5 7 9 11
2 4 6 8 10
5 6 100
2 4 6 8 10
1 3 5 7 9 11

```
### 样例输出 #3
```
1090
1096
1098
1092
1094
1100
1094
1092
1098
1096
1090
1096
1098
1092
1094
1100
1094
1092
1098
1096
1090
1096
1098
1092
1094
1100

```
### 样例输入 #4
```
见附件
```
### 样例输出 #4
```
见附件
```
### 样例输入 #5
```
见附件
```
### 样例输出 #5
```
1000000000000000000
2001007996000

```
## 提示

样例解释：$3\rightarrow2_{充电}\Rightarrow0\rightarrow2_{充电}\Rightarrow4\rightarrow5_{充电}\Rightarrow4$。$\rightarrow$ 表示移动，$\Rightarrow$ 表示移动并扫雪。

对于所有数据，$1\leq n\leq 250000$，$1\leq l\leq 10^9$，$1\leq k\leq l$，$1\leq d\leq 250000$，$\sum z,\sum u\leq 500000$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $l\leq 12$，$d\leq 50$ | 10 |
| 2 | $l\leq 500$，$d\leq 50$，$k=1$ | 12 |
| 3 | $l\leq 5000000$，$d\leq 20$ | 8 |
| 4 | $z=u=0$ | 8 |
| 5 | $z,u\leq 100$，$k\leq 50$ | 20 |
| 6 | $k=1$ | 18 |
| 7 |  | 24 |



---

---
title: "[POI 2021/2022 R1] Układanie kart"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9419
tag: ['模拟', '递推', 'POI（波兰）', '2021']
---
# [POI 2021/2022 R1] Układanie kart
## 题目背景

译自 [XXIX Olimpiada Informatyczna – I etap](https://sio2.mimuw.edu.pl/c/oi29-1/dashboard/) [Układanie kart](https://sio2.mimuw.edu.pl/c/oi29-1/p/ukl/)。
## 题目描述

我们用以下方法将一个排列递增排序:

一次操作：记第一个数字为 $k$，在排列中找到 $k-1$（$k=1$ 则取 $n$），把 $k-1$ 拉到排列的第一个位置，中间的数字依次后移。

一次操作的价值：$k-1$（或 $n$）在原排列的位置（这个从 $0$ 开始标号）。

一个排列的价值：进行若干次操作直到排列有序，价值为每次操作的价值之和。

给你 $n,m$，求所有 $n!$ 个排列的价值之和，对 $m$ 取模。
## 输入格式

一行两个正整数，$n,m$。
## 输出格式

一行一个整数，答案对 $m$ 取模的结果。
## 样例

### 样例输入 #1
```
2 100

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
3 100

```
### 样例输出 #2
```
15

```
### 样例输入 #3
```
10 1000

```
### 样例输出 #3
```
100

```
### 样例输入 #4
```
500 100000

```
### 样例输出 #4
```
60000

```
### 样例输入 #5
```
100000 1000

```
### 样例输出 #5
```
0

```
## 提示

对于所有数据，$2\leq n\leq 1000000$，$2\leq m\leq 10^9$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $n\leq 10$ | 10 |
| 2 | $n\leq 2000$ | 60 |
| 3 |  | 30 |


---

---
title: "「RiOI-2」change"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9499
tag: ['模拟', '贪心', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「RiOI-2」change
## 题目背景

小 E 终于在今天收回了被妈妈保管的压岁钱。

作为有远见的收藏家，小 E 知道，如果她从现在开始收集东西，以后就会变得值钱了。

小 E 的世界里有一些纸币。她知道这些纸币未来的价值，但遗憾的是，这些纸币只能从小换到大。如何是好？
## 题目描述

给定 $n$ 种物品，每种物品 $i$ 价值为 $v_i$，个数为 $c_i$。

定义总价值为 $\sum\limits_{i=1}^nc_iv_i$，你可以进行一些（可能为 $0$）次操作来最大化总价值。

一次操作为：选定一个 $i$ 满足 $c_i \geq x_i$，让 $c_i\gets c_i - x_i$，$c_{i+1}\gets c_{i+1}+ 1$。

输出最大的总价值对 $998,\!244,\!353$ 取模。

**注意，你需要最大化总价值，再对 $998,\!244,\!353$ 取模，而不是最大化「总价值对 $998,\!244,\!353$ 取模的值」。**
## 输入格式

**本题有多组数据。**

第一行一个正整数 $\text{sid}$，表示该测试数据所属子任务编号。

第二行一个正整数 $t$，表示数据组数。对于每组数据：

+ 输入共四行。
+ 第一行，一个正整数 $n$，表示钱的种数。
+ 第二行，$n$ 个非负整数分别表示 $v_1, v_2 \dots v_n$。
+ 第三行，$n$ 个非负整数分别表示 $c_1, c_2 \dots c_n$。
+ 第四行，$n - 1$ 个正整数分别表示 $x_1, x_2 \dots x_{n - 1}$。
## 输出格式

输出 $t$ 行，每行一个整数，表示物品总价值的最大值。所有答案对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
0
2
2
1 5
5 1
4
10
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
```
### 样例输出 #1
```
11
172998509
```
## 提示

### 样例解释

对于样例的第一组数据，$v=[1,5]$，$c=[5,1]$，$x=[4]$。可以选定 $i=1$ 进行一次操作，此时 $c=[1,2]$，总价值为 $1\cdot 1+5\cdot 2=11$，可以证明它是最大的。

### 数据规模与约定

**本题采用捆绑测试。**

下面是各 Subtask 的特殊性质，斜杠表示该栏无特殊限制。

|$\text{sid}=$| $\sum n\le$ | $c_i,v_i\le$ | 特殊性质 |分值|
| :-: | :---------: | :----------: | :------: | :-: |
| $1$ | / | / | 特殊性质 A | $5$ |
| $2$ | / | / | 特殊性质 B | $15$ |
| $3$ | / | / | 特殊性质 C | $15$ |
| $4$ | $300$ | $300$ | / | $15$ |
| $5$ | $2000$ | $2000$ | / | $20$ |
| $6$ | $2000$ | / | / | $15$ |
| $7$ | / | / | / | $15$ |

+ 特殊性质 A：$x_i = 10^9$。
+ 特殊性质 B：$x_i = 1$。
+ 特殊性质 C：所有 $c_i, v_i$ 均在 $[0, 10^5]$ 间均匀随机生成；所有 $x_i$ 均在 $[1, 10^5]$ 间均匀随机生成。

对于所有数据，$1\le t \le 10^5$，$2\le n$，$\sum n\le 2\times 10^5$，$1\le x_i\le 10^9$，$0\le c_i,v_i\le 10^9$。

upd：新增一组 hack 数据，$\text{sid}$ 为 $7$。


---

