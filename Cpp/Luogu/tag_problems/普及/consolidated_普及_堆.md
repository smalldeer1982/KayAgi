---
title: "[NOIP 2004 提高组] 合并果子"
layout: "post"
diff: 普及/提高-
pid: P1090
tag: ['贪心', '2004', '堆', 'NOIP 提高组', '优先队列']
---
# [NOIP 2004 提高组] 合并果子
## 题目描述

在一个果园里，多多已经将所有的果子打了下来，而且按果子的不同种类分成了不同的堆。多多决定把所有的果子合成一堆。

每一次合并，多多可以把两堆果子合并到一起，消耗的体力等于两堆果子的重量之和。可以看出，所有的果子经过 $n-1$ 次合并之后， 就只剩下一堆了。多多在合并果子时总共消耗的体力等于每次合并所耗体力之和。

因为还要花大力气把这些果子搬回家，所以多多在合并果子时要尽可能地节省体力。假定每个果子重量都为 $1$ ，并且已知果子的种类 数和每种果子的数目，你的任务是设计出合并的次序方案，使多多耗费的体力最少，并输出这个最小的体力耗费值。

例如有 $3$ 种果子，数目依次为 $1$ ， $2$ ， $9$ 。可以先将 $1$ 、 $2$ 堆合并，新堆数目为 $3$ ，耗费体力为 $3$ 。接着，将新堆与原先的第三堆合并，又得到新的堆，数目为 $12$ ，耗费体力为 $12$ 。所以多多总共耗费体力 $=3+12=15$ 。可以证明 $15$ 为最小的体力耗费值。
## 输入格式

共两行。  
第一行是一个整数 $n(1\leq n\leq 10000)$ ，表示果子的种类数。  

第二行包含 $n$ 个整数，用空格分隔，第 $i$ 个整数 $a_i(1\leq a_i\leq 20000)$ 是第 $i$ 种果子的数目。


## 输出格式

一个整数，也就是最小的体力耗费值。输入数据保证这个值小于 $2^{31}$ 。
## 样例

### 样例输入 #1
```
3 
1 2 9 

```
### 样例输出 #1
```
15

```
## 提示

对于 $30\%$ 的数据，保证有 $n \le 1000$：

对于 $50\%$ 的数据，保证有 $n \le 5000$；

对于全部的数据，保证有 $n \le 10000$。



---

---
title: "「Stoi2025」爱你没差"
layout: "post"
diff: 普及/提高-
pid: P11886
tag: ['贪心', '堆', '2025', 'O2优化', '洛谷比赛']
---
# 「Stoi2025」爱你没差
## 题目背景

![](bilibili:BV1fx411N7bU?page=147)
## 题目描述

给定正整数 $n,m$ 和一个整数序列 $a_1,a_2,\dots,a_n$，每次可以选取其中两个数 $x,y$，去掉它们并往序列中加入 $x+y$，若有 $m \cdot x \ge y$ 且 $m \cdot y \ge x$，则得一分。求将全部数合并成一个数得分的最大可能值。
## 输入格式

第一行输入两个正整数表示 $n,m$。

第二行输入 $n$ 个正整数，表示序列 $a_i$。
## 输出格式

输出一行一个整数表示得分的最大可能值。
## 样例

### 样例输入 #1
```
3 2
1 2 3

```
### 样例输出 #1
```
2

```
## 提示

#### 样例解释

先选择 $1,2$，序列变为 $3,3$，再选择 $3,3$，序列变为 $6$，此时得分为 $2$。

若先选择 $2,3$，则得分为 $1$。

#### 数据范围与限制

对于 $20\%$ 的数据，满足 $n\le10$。

对于 $60\%$ 的数据，满足 $n\le10^3$。

对于所有数据，满足 $1\le n\le10^6$，$2\le m\le10$，$0\le a_i<2^{64}$，$\sum a_i<2^{64}$。


---

---
title: "[GCJ Farewell Round #3] Immunization Operation"
layout: "post"
diff: 普及/提高-
pid: P12957
tag: ['模拟', '堆', '2023', 'Google Code Jam']
---
# [GCJ Farewell Round #3] Immunization Operation
## 题目描述

Making every vaccine available to the entire world population is a complicated problem in many respects. Ñambi is leading the charge to optimize delivery. To reduce the access barriers as much as possible, she is trying to have automated robots deliver and apply vaccines directly in patients' homes.

In the current iteration, the robot that Ñambi is designing will work on a single street that runs from west to east. As such, the robot accepts a single command 'move $x$ meters'. If $x$ is positive, the robot moves $x$ meters to the east. If $x$ is negative, the robot moves $-x$ meters to the west.

The robot is loaded at the start of the day with the information about all immunizations it must provide that day. Each of these pieces of information consists of the current location of the vaccine, for pickup, and the location of the patient that must receive it, for delivery. Each vaccine is custom-made for one patient. Of course, the delivery location of a vaccine is never the same as its own pickup location. The robot must pick up the vaccine before it delivers it to the patient.

The robot is programmed to automatically pick up and load onto its cargo area vaccines when it passes through their pickup locations for the first time. The robot is also programmed to deliver the vaccine to its recipient as soon as it passes through their location if the vaccine was already picked up. Ñambi wants to track how many vaccinations happen after each movement command. A vaccination happens when the vaccine is delivered. Notice that the vaccine might be picked up during any of the previous commands, or during the same command, but before delivery.

The following picture illustrates one possible scenario (Sample Case #1 below). The smiley face represents the initial position of the robot, and the long black line is the street. The marks above the line are the pickup locations and the marks below are the delivery locations. Finally, the arrows below represent the moves the robot makes, in order from top to bottom, labeled with how many deliveries are completed during the move.

![](https://cdn.luogu.com.cn/upload/image_hosting/05p9howp.png)

This is what happens during each move, in order:

* Move 1. The robot picks up vaccines 5 and 1, then delivers vaccine 1, and then picks up vaccine 3 just as the move is finishing. Notice that the robot passes through the delivery location for vaccine 3, but since that happens before picking vaccine 3 up, it cannot deliver it.
* Move 2. The robot passes through the delivery locations of vaccines 1 and 4. However, vaccine 1 is already delivered and vaccine 4 has not been picked up, so no vaccination is finished.
* Move 3. The robot delivers vaccine 3.
* Move 4. The robot picks up vaccine 2, delivers vaccine 5 and picks up vaccine 4.

Notice that vaccine 2 and 4 were picked up but not delivered because the delivery location of vaccine 2 was never reached, and the delivery location of vaccine 4 was not reached after the vaccine had been picked up.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of 4 lines. The first line of a test case contains 2 integers $\mathbf{V}$ and $\mathbf{M}$, the number of vaccinations and the number of move commands.

The second line of a test case contains $\mathbf{V}$ integers $\mathbf{P}_1, \mathbf{P}_2, \ldots, \mathbf{P}_\mathbf{V}$, representing that the $i$-th vaccine must be picked up exactly $\mathbf{P}_i$ meters to the east of the robot's initial location. Note that several vaccines can have the same pickup location.

The third line contains $\mathbf{V}$ integers $\mathbf{D}_1, \mathbf{D}_2, \ldots, \mathbf{D}_\mathbf{V}$, representing that the $i$-th vaccine must be delivered exactly $\mathbf{D}_i$ meters to the east of the robot's initial location. Note that several vaccines can have the same delivery location.

The final line of a test case contains $\mathbf{M}$ integers $\mathbf{X}_1, \mathbf{X}_2, \ldots, \mathbf{X}_\mathbf{M}$, where the absolute value of $\mathbf{X}_j$ is the number of meters the robot must move for the $j$-th movement command. The $j$-th move must be towards the east if $\mathbf{X}_j$ is positive, and towards the west if it is negative. Notice that the vaccinations can happen in an order different than the numbering of the input, but movement commands happen in the given order.
## 输出格式

For each test case, output one line containing `case #x: y1 y2 ... yM`, where $x$ is the test case number (starting from 1) and $y_j$ is the number of vaccinations completed while performing the $j$-th given movement command.
## 样例

### 样例输入 #1
```
4
5 4
121 312 271 422 75
199 464 160 234 368
271 -109 -70 371
2 2
1 3
4 4
4 -1
2 2
1 4
4 3
4 -1
1 10
1
2
-987654321 -987654321 -987654321 -987654321 -987654321 987654321 987654321 987654321 987654321 987654323
```
### 样例输出 #1
```
Case #1: 1 0 1 1
Case #2: 2 0
Case #3: 1 1
Case #4: 0 0 0 0 0 0 0 0 0 1
```
## 提示

**Sample Explanation**

Sample Case #1 is the one explained and illustrated in the problem statement.

In Sample Case #2 and Sample Case #3, notice that it is possible to pick up and deliver vaccines in the same move only if the pickup place is visited first. In addition, notice that it is possible pick up and to deliver exactly as a move is ending.

Sample Case #4, the robot moves $987654321$ meters to the west five times, then $987654321$ meters to the east four times, then $987654323$ meters to the east. The only pickup and delivery are both made in the final move. Note that the commands can be very extreme so the robot can be at some point very far away from its initial position, either west or east.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{P}_i \leq 10^9$, for all $i$.
- $1 \leq \mathbf{D}_i \leq 10^9$, for all $i$.
- $\mathbf{P}_i \neq \mathbf{D}_i$, for all $i$.
- $-10^9 \leq \mathbf{X}_j \leq 10^9$, for all $j$.
- $\mathbf{X}_j \neq 0$, for all $j$.

**Test Set 1 (4 Pts, Visible Verdict)**

- Time limit: 20 seconds.
- $1 \leq \mathbf{V} \leq 100$.
- $1 \leq \mathbf{M} \leq 100$.

**Test Set 2 (9 Pts, Hidden Verdict)**

- Time limit: 40 seconds.
- $1 \leq \mathbf{V} \leq 10^5$.
- $1 \leq \mathbf{M} \leq 10^5$.



---

---
title: "[GCJ 2017 #1C] Ample Syrup"
layout: "post"
diff: 普及/提高-
pid: P13168
tag: ['2017', '堆', 'Special Judge', '排序', 'Google Code Jam']
---
# [GCJ 2017 #1C] Ample Syrup
## 题目描述

The kitchen at the Infinite House of Pancakes has just received an order for a stack of $K$ pancakes! The chef currently has $N$ pancakes available, where $N \geq K$. Each pancake is a cylinder, and different pancakes may have different radii and heights.

As the sous-chef, you must choose $K$ out of the $N$ available pancakes, discard the others, and arrange those $K$ pancakes in a stack on a plate as follows. First, take the pancake that has the largest radius, and lay it on the plate on one of its circular faces. (If multiple pancakes have the same radius, you can use any of them.) Then, take the remaining pancake with the next largest radius and lay it on top of that pancake, and so on, until all $K$ pancakes are in the stack and the centers of the circular faces are aligned in a line perpendicular to the plate, as illustrated by this example:

![](https://cdn.luogu.com.cn/upload/image_hosting/57lkgshp.png)

You know that there is only one thing your diners love as much as they love pancakes: syrup! It is best to maximize the total amount of exposed pancake surface area in the stack, since more exposed pancake surface area means more places to pour on delicious syrup. Any part of a pancake that is not touching part of another pancake or the plate is considered to be exposed.

If you choose the $K$ pancakes optimally, what is the largest total exposed pancake surface area you can achieve?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each begins with one line with two integers $N$ and $K$: the total number of available pancakes, and the size of the stack that the diner has ordered. Then, $N$ more lines follow. Each contains two integers $R_i$ and $H_i$: the radius and height of the $i$-th pancake, in millimeters.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the maximum possible total exposed pancake surface area, in millimeters squared. $y$ will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer.
## 样例

### 样例输入 #1
```
4
2 1
100 20
200 10
2 2
100 20
200 10
3 2
100 10
100 10
100 10
4 2
9 3
7 1
10 1
8 4
```
### 样例输出 #1
```
Case #1: 138230.076757951
Case #2: 150796.447372310
Case #3: 43982.297150257
Case #4: 625.176938064
```
## 提示

**Sample Explanation**

In sample case #1, the "stack" consists only of one pancake. A stack of just the first pancake would have an exposed area of $\pi \times R_0^2 + 2 \times \pi \times R_0 \times H_0 = 14000\pi \text{ mm}^2$. A stack of just the second pancake would have an exposed area of $44000\pi \text{ mm}^2$. So it is better to use the second pancake.

In sample case #2, we can use both of the same pancakes from case #1. The first pancake contributes its top area and its side, for a total of $14000\pi \text{ mm}^2$. The second pancake contributes some of its top area (the part not covered by the first pancake) and its side, for a total of $34000\pi \text{ mm}^2$. The combined exposed surface area is $48000\pi \text{ mm}^2$.

In sample case #3, all of the pancakes have radius 100 and height 10. If we stack two of these together, we effectively have a single new cylinder of radius 100 and height 20. The exposed surface area is $14000\pi \text{ mm}^2$.

In sample case #4, the optimal stack uses the pancakes with radii of 8 and 9.

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq K \leq N$.
- $1 \leq R_i \leq 10^6$, for all $i$.
- $1 \leq H_i \leq 10^6$, for all $i$.

**Small dataset (9 Pts, Test Set 1 - Visible)**

- $1 \leq N \leq 10$.

**Large dataset (16 Pts, Test Set 2 - Hidden)**

- $1 \leq N \leq 1000$.


---

---
title: "[GCJ 2016 #1C] Senate Evacuation"
layout: "post"
diff: 普及/提高-
pid: P13195
tag: ['数学', '2016', '堆', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2016 #1C] Senate Evacuation
## 题目描述

A small fire started in the senate room, and it needs to be evacuated!

There are some senators in the senate room, each of whom belongs to one of $\mathbf{N}$ political parties. Those parties are named after the first $\mathbf{N}$ (uppercase) letters of the English alphabet.

The emergency door is wide enough for up to two senators, so in each step of the evacuation, you may choose to remove either one or two senators from the room.

The senate rules indicate the senators in the room may vote on any bill at any time, even in the middle of an evacuation! So, the senators must be evacuated in a way that ensures that no party ever has an absolute majority. That is, it can never be the case after any evacuation step that more than half of the senators in the senate room belong to the same party.

Can you construct an evacuation plan? The senate is counting on you!

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of two lines. The first line contains a single integer $\mathbf{N}$, the number of parties. The second line contains $\mathbf{N}$ integers, $\mathbf{P}_{1}, \mathbf{P}_{2}, \ldots, \mathbf{P}_{\mathbf{N}}$, where $\mathbf{P}_{i}$ represents the number of senators of the party named after the i-th letter of the alphabet.

## 输出格式

For each test case, output one line containing Case #x: y, where $x$ is the test case number (starting from 1) and $y$ is the evacuation plan. The plan must be a space-separated list of instructions, in the order in which they are to be carried out, where each instruction is either one or two characters, representing the parties of the senators to evacuate in each step.

It is guaranteed that at least one valid evacuation plan will exist. If multiple evacuation plans are valid, you may output any of them.
## 样例

### 样例输入 #1
```
4
2
2 2
3
3 2 2
3
1 1 2
3
2 3 1
```
### 样例输出 #1
```
Case #1: AB BA
Case #2: AA BC C BA
Case #3: C C AB
Case #4: BA BB CA
```
## 提示

**Sample Explanation**

The sample output displays one set of answers to the sample cases. Other answers may be possible.

In Case #1, there are two senators from each of the parties A and B. If we remove one from each party every time, the perfect balance is maintained until evacuation is complete.

Case #2 proceeds as follows:

- Initially in the room: 3 A, 2 B, 2 C.
- Evacuate AA. Still in the room: 1 A, 2 B, 2 C.
- Evacuate BC. Still in the room: 1 A, 1 B, 1 C.
- Evacuate C. Still in the room: 1 A, 1 B.
- Evacuate AB. Evacuation complete!

Note that it would not be valid to begin the evacuation with BC, which would leave 3 A, 1 B, and 1 C in the room; party A would have an absolute majority (3 out of 5 = 60%).

For Case #3, note that CC AB would also be a valid answer, and C C AB is also valid even though it requires three evacuation steps instead of two.

**Sample Explanation**

- $1 \leqslant \mathbf{T} \leqslant 50$.
- No party will have an absolute majority before the start of the evacuation.
- $1 \leqslant \mathbf{P}_{\mathbf{i}} \leqslant 1000$, for all i.

**Small dataset (8 Pts, Test set 1 - Visible)**

- $2 \leqslant \mathbf{N} \leqslant 3$.
- sum of all $\mathbf{P}_{\mathbf{i}} \leqslant 9$.

**Large dataset (10 Pts, Test set 2 - Hidden)**

- $2 \leqslant \mathbf{N} \leqslant 26$.
- sum of all $\mathbf{P}_{\mathbf{i}} \leqslant 1000$.


---

---
title: "瑞瑞的木板"
layout: "post"
diff: 普及/提高-
pid: P1334
tag: ['堆', '福建省历届夏令营', '排序']
---
# 瑞瑞的木板
## 题目背景

瑞瑞想要亲自修复在他的一个小牧场周围的围栏。
## 题目描述

他测量栅栏并发现他需要 $n$ 根木板，每根的长度为整数 $l_i$。于是，他买了一根足够长的木板，长度为所需的 $n$ 根木板的长度的总和，他决定将这根木板切成所需的 $n$ 根木板（瑞瑞在切割木板时不会产生木屑，不需考虑切割时损耗的长度)。

瑞瑞切割木板时使用的是一种特殊的方式，这种方式在将一根长度为 $x$ 的木板切为两根时，需要消耗 $x$ 个单位的能量。瑞瑞拥有无尽的能量，但现在提倡节约能量，所以作为榜样，他决定尽可能节约能量。显然，总共需要切割 $(n-1)$ 次，问题是，每次应该怎么切呢？请编程计算最少需要消耗的能量总和。
## 输入格式

输入的第一行是整数，表示所需木板的数量 $n$。

第 $2$ 到第 $(n + 1)$ 行，每行一个整数，第 $(i + 1)$ 行的整数 $l_i$ 代表第  $i$ 根木板的长度 $l_i$。
## 输出格式

一个整数，表示最少需要消耗的能量总和。
## 样例

### 样例输入 #1
```
3
8
5
8

```
### 样例输出 #1
```
34

```
## 提示

#### 输入输出样例 1 解释

将长度为 $21$ 的木板，第一次切割为长度为 $8$ 和长度为 $13$ 的，消耗 $21$ 个单位的能量，第二次将长度为 $13$ 的木板切割为长度为 $5$ 和 $8$ 的，消耗 $13$ 个单位的能量，共消耗 $34$ 个单位的能量，是消耗能量最小的方案。

----

#### 数据规模与约定

- 对于 $100\%$ 的数据，保证 $1\le n \le 2 \times 10^4$，$1 \leq l_i \leq 5 \times 10^4$。


---

---
title: "[GCJ 2008 Qualification] Train Timetable"
layout: "post"
diff: 普及/提高-
pid: P13455
tag: ['贪心', '2008', '堆', 'Google Code Jam']
---
# [GCJ 2008 Qualification] Train Timetable
## 题目描述

A train line has two stations on it, A and B. Trains can take trips from A to B or from B to A multiple times during a day. When a train arrives at B from A (or arrives at A from B), it needs a certain amount of time before it is ready to take the return journey - this is the turnaround time. For example, if a train arrives at 12:00 and the turnaround time is 0 minutes, it can leave immediately, at 12:00.

A train timetable specifies departure and arrival time of all trips between A and B. The train company needs to know how many trains have to start the day at A and B in order to make the timetable work: whenever a train is supposed to leave A or B, there must actually be one there ready to go. There are passing sections on the track, so trains don't necessarily arrive in the same order that they leave. Trains may not travel on trips that do not appear on the schedule.
## 输入格式

The first line of input gives the number of cases, $N$. $N$ test cases follow.

Each case contains a number of lines. The first line is the turnaround time, $T$, in minutes. The next line has two numbers on it, $N_A$ and $N_B$. $N_A$ is the number of trips from A to B, and $N_B$ is the number of trips from B to A. Then there are $N_A$ lines giving the details of the trips from A to B.

Each line contains two fields, giving the HH:MM departure and arrival time for that trip. The departure time for each trip will be earlier than the arrival time. All arrivals and departures occur on the same day. The trips may appear in any order - they are not necessarily sorted by time. The hour and minute values are both two digits, zero-padded, and are on a 24-hour clock (00:00 through 23:59).

After these $N_A$ lines, there are $N_B$ lines giving the departure and arrival times for the trips from B to A.
## 输出格式

For each test case, output one line containing "Case #$x$: " followed by the number of trains that must start at A and the number of trains that must start at B.
## 样例

### 样例输入 #1
```
2
5
3 2
09:00 12:00
10:00 13:00
11:00 12:30
12:02 15:00
09:00 10:30
2
2 0
09:00 09:01
12:00 12:02
```
### 样例输出 #1
```
Case #1: 2 2
Case #2: 2 0
```
## 提示

**Limits**

**Small dataset (5 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 20$
- $0 \leq N_A, N_B \leq 20$
- $0 \leq T \leq 5$

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 100$
- $0 \leq N_A, N_B \leq 100$
- $0 \leq T \leq 60$


---

---
title: "[KOI 2025 #1] 稻草人"
layout: "post"
diff: 普及/提高-
pid: P13512
tag: ['堆', '2025', '优先队列', 'KOI（韩国）']
---
# [KOI 2025 #1] 稻草人
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

一支带有力量 $P$ 的箭从数轴上的位置 0 向右方发射。在每个整数位置 $i$ ($1 \le i \le N$)，最多可以设置一个防御力为 $A_i$ 的稻草人。当箭撞到稻草人时，如果箭的力量小于或等于稻草人的防御力，箭会立即停止。反之，如果箭的力量大于防御力，箭的力量会减去 $A_i$ 并继续前进。

对于整数 $i$，我们将 $f(i)$ 的值定义为“为了使箭在位置 $i$ 或其左侧停止所需要的**稻草人的最小数量**”。如果无法使箭停止，则值为 $-1$。

例如，假设 $N=5, P=10$ 并且 $A_1=3, A_2=6, A_3=1, A_4=1, A_5=10$。所有 $f(i)$ 的值和安装的稻草人的位置如下表所示。

| $i$ | $f(i)$ 的值 | 安装的稻草人的位置 |
| :--: | :--: | :--: |
| $i=1$ | $-1$ | 不可能 |
| $i=2$ | $-1$ | 不可能 |
| $i=3$ | $3$ | $[1, 2, 3]$ |
| $i=4$ | $3$ | 可选择 $[1, 2, 3]$ 或 $[1, 2, 4]$ 之一 |
| $i=5$ | $1$ | $[5]$ |

请编写一个程序，求出对于所有 $1 \le i \le N$ 的 $i$ 的 $f(i)$ 值。
## 输入格式

第一行给定整数 $N$ 和箭的力量 $P$，以空格分隔。

第二行给定 $N$ 个整数 $A_1, A_2, \cdots, A_N$，以空格分隔。
## 输出格式

在第一行输出 $f(1), f(2), \cdots, f(N)$ 的值，以空格分隔。
## 样例

### 样例输入 #1
```
5 10
3 6 1 1 10
```
### 样例输出 #1
```
-1 -1 3 3 1
```
### 样例输入 #2
```
3 10
20 20 20
```
### 样例输出 #2
```
1 1 1
```
### 样例输入 #3
```
1 5
3
```
### 样例输出 #3
```
-1
```
## 提示

### 限制条件

*   给定的所有数都是整数。
*   $1 \le N \le 500,000$
*   $1 \le P \le 10^9$
*   对于每个 $1 \le i \le N$ 的 $i$，都有 $1 \le A_i \le 10^9$。

### 子任务

1.  (4 分) $N \le 8$
2.  (8 分) $N \le 5000$
3.  (8 分) 对于所有 $1 \le i \le N$ 的 $i$，$A_i = 1$。
4.  (20 分) 对于所有 $1 \le i \le N$ 的 $i$，$A_i = 2$ 或 $A_i = 3$。
5.  (40 分) 对于所有 $1 \le i \le N$ 的 $i$，$A_i \le 50$。
6.  (40 分) 对于所有 $1 \le i < N$ 的 $i$，$A_i \le A_{i+1}$。
7.  (30 分) 无附加限制条件。


---

---
title: "舞蹈课"
layout: "post"
diff: 普及/提高-
pid: P1878
tag: ['堆']
---
# 舞蹈课
## 题目描述

有 $n$ 个人参加一个舞蹈课。每个人的舞蹈技术由整数来决定。在舞蹈课的开始，他们从左到右站成一排。当这一排中至少有一对相邻的异性时，舞蹈技术相差最小的那一对会出列并开始跳舞。如果不止一对，那么最左边的那一对出列。一对异性出列之后，队伍中的空白按原顺序补上（即：若队伍为 `ABCD`，那么 `BC` 出列之后队伍变为 `AD`）。舞蹈技术相差最小即是 $a_i$ 的绝对值最小。

任务是模拟以上过程，确定跳舞的配对及顺序。

## 输入格式

第一行一个正整数 $n$ 表示队伍中的人数。

第二行包含 $n$ 个字符 `B` 或者 `G`，`B` 代表男，`G` 代表女。

第三行为 $n$ 个整数 $a_i$。所有信息按照从左到右的顺序给出。

## 输出格式

第一行一个整数表示出列的总对数 $k$。

接下来 $k$ 行，每行是两个整数。按跳舞顺序输出，两个整数代表这一对舞伴的编号（按输入顺序从左往右 $1$ 至 $n$ 编号）。请先输出较小的整数，再输出较大的整数。

## 样例

### 样例输入 #1
```
4

BGBG

4 2 4 3


```
### 样例输出 #1
```
2

3 4

1 2


```
## 提示

对于 $50\%$ 的数据，$1\leq n\leq 200$。

对于 $100\%$ 的数据，$1\leq n\leq 2\times 10^5$，$1\le a_i\le 10^7$。


---

---
title: "最小函数值"
layout: "post"
diff: 普及/提高-
pid: P2085
tag: ['数学', '堆', '排序', '优先队列']
---
# 最小函数值
## 题目描述

有 $n$ 个函数，分别为 $F_1,F_2,\dots,F_n$。定义 $F_i(x)=A_ix^2+B_ix+C_i(x\in\mathbb N*)$。给定这些 $A_i$、$B_i$ 和 $C_i$，请求出所有函数的所有函数值中最小的 $m$ 个（如有重复的要输出多个）。
## 输入格式

第一行输入两个正整数 $n$ 和 $m$。  

以下 $n$ 行每行三个正整数，其中第 $i$ 行的三个数分别为 $A_i$、$B_i$ 和 $C_i$。
## 输出格式

输出将这 $n$ 个函数所有可以生成的函数值排序后的前 $m$ 个元素。这 $m$ 个数应该输出到一行，用空格隔开。
## 样例

### 样例输入 #1
```
3 10
4 5 3
3 4 5
1 7 1

```
### 样例输出 #1
```
9 12 12 19 25 29 31 44 45 54
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n,m\le10000$，$1 \leq A_i\le10,B_i\le100,C_i\le10^4$。


---

---
title: "【模板】堆"
layout: "post"
diff: 普及/提高-
pid: P3378
tag: ['堆', 'O2优化']
---
# 【模板】堆
## 题目描述

给定一个数列，初始为空，请支持下面三种操作：

1. 给定一个整数 $x$，请将 $x$ 加入到数列中。
2. 输出数列中最小的数。
3. 删除数列中最小的数（如果有多个数最小，只删除 $1$ 个）。



## 输入格式

第一行是一个整数，表示操作的次数 $n$。  
接下来 $n$ 行，每行表示一次操作。每行首先有一个整数 $op$ 表示操作类型。
- 若 $op = 1$，则后面有一个整数 $x$，表示要将 $x$ 加入数列。
- 若 $op = 2$，则表示要求输出数列中的最小数。
- 若 $op = 3$，则表示删除数列中的最小数。如果有多个数最小，只删除 $1$ 个。
## 输出格式

对于每个操作 $2$，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5
1 2
1 5
2
3
2

```
### 样例输出 #1
```
2
5
```
## 提示

**【数据规模与约定】**
- 对于 $30\%$ 的数据，保证 $n \leq 15$。
- 对于 $70\%$ 的数据，保证 $n \leq 10^4$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^6$，$1 \leq x \lt 2^{31}$，$op \in \{1, 2, 3\}$。


---

---
title: "[USACO18DEC] Convention II S"
layout: "post"
diff: 普及/提高-
pid: P5120
tag: ['模拟', '2018', 'USACO', '堆']
---
# [USACO18DEC] Convention II S
## 题目描述

虽然在接机上耽误了挺长时间，Farmer John 为吃草爱好牛们举行的大会至今为止都非常顺利。大会吸引了世界各地的奶牛。

然而大会的重头戏看起来却给 Farmer John 带来了一些新的安排上的困扰。他的农场上的一块非常小的牧草地出产一种据某些识货的奶牛说是世界上最美味的品种的草。因此，所有参会的 $N$ 头奶牛（$1\le N\le 10^5$）都想要品尝一下这种草。由于这块牧草地小到仅能容纳一头奶牛，这很有可能会导致排起长龙。

Farmer John 知道每头奶牛i计划到达这块特殊的牧草地的时间 $a_i$，以及当轮到她时，她计划品尝这种草花费的时间 $t_i$。当奶牛 $i$ 开始吃草时，她会在离开前花费全部 $t_i$ 的时间，此时其他到达的奶牛需要排队等候。如果这块牧草地空出来的时候多头奶牛同时在等候，那么资历最深的奶牛将会是下一头品尝鲜草的奶牛。在这里，恰好在另一头奶牛吃完草离开时到达的奶牛被认为是“在等待的”。类似地，如果当没有奶牛在吃草的时候有多头奶牛同时到达，那么资历最深的奶牛是下一头吃草的奶牛。

请帮助 FJ 计算所有奶牛中在队伍里等待的时间（$a_i$ 到这头奶牛开始吃草之间的时间）的最大值。
## 输入格式

输入的第一行包含 $N$。以下 $N$ 行按资历顺序给出了 $N$ 头奶牛的信息（资历最深的奶牛排在最前面）。每行包含一头奶牛的 $a_i$ 和 $t_i$。所有的 $t_i$ 为不超过 $10^4$ 的正整数，所有 $a_i$ 为不超过 $10^9$ 的正整数。
## 输出格式

输出所有奶牛中的最长等待时间。
## 样例

### 样例输入 #1
```
5
25 3
105 30
20 50
10 17
100 10
```
### 样例输出 #1
```
10
```
## 提示

在这个例子中，我们有 $5$ 头奶牛（按输入中的顺序编号为 $1\dots 5$）。奶牛 $4$ 最先到达（时间 $10$），在她吃完之前（时间 $27$）奶牛 $1$ 和奶牛 $3$ 都到达了。由于奶牛 $1$ 拥有较深的资历，所以她先吃，从她到达开始共计等待了 $2$ 个单位时间。她在时间 $30$ 结束吃草，随后奶牛 $3$ 开始吃草，从她到达开始共计等待了 $10$ 单位时间。在一段没有奶牛吃草的时间过后，奶牛 $5$ 到达，在她正在吃草的时间里奶牛 $2$ 也到达了，在 $5$ 个单位时间之后能够吃到草。相比到达时间等待最久的奶牛是奶牛 $3$。


---

---
title: "[POI 2018] Prawnicy"
layout: "post"
diff: 普及/提高-
pid: P6044
tag: ['贪心', '2018', '堆', 'POI（波兰）', 'Special Judge']
---
# [POI 2018] Prawnicy
## 题目背景

**题目译自 [POI XXV - I etap](https://sio2.mimuw.edu.pl/c/oi25-1/dashboard/) 「[Prawnicy](https://sio2.mimuw.edu.pl/c/oi25-1/p/pra/)」**
## 题目描述

“Bajtazar 父子”律师事务所刚刚收到一位非常重要的客户的订单。案件严重、紧急，需要与律师事务所的律师举行会议。每个律师都有一段固定的空闲时间可以参加会议。你应该选择这样的 $k$ 位律师，以便召开会议的时间（即他们都空闲的时间）尽可能长。

[简要题意](https://www.luogu.com.cn/problem/U252799)
## 输入格式

第一行包含两个整数 $n$ 和 $k\ (1\le k\le n)$，以一个空格隔开，表示事务所雇用的律师人数和召开会议所需的律师人数。

接下来 $n$ 行，第 $i$ 行包含两个整数 $a_i$ 和 $b_i\ (1\le a_i<b_i\le 10^9)$，以一个空格隔开，表示第 $i$ 个律师在**时刻 $a_i$ 和时刻 $b_i$ 之间**是空闲的。
## 输出格式

第一行输出一个整数，表示会议可能的最大时长。你可以假设你能够召开至少 $1$ 人的会议。

第二行输出空格分隔的 $k$ 个数，代表参加会议的律师编号（从 $1$ 开始）。如果有多个正确答案，您的程序应输出其中任何一个。
## 样例

### 样例输入 #1
```
6 3
3 8
4 12
2 6
1 10
5 9
11 12

```
### 样例输出 #1
```
4
1 2 4

```
## 提示

#### 样例解释

三位律师会议可能的最大时长是 $4$。编号为 $1$、$2$ 和 $4$ 的律师可以参加，持续时间从 $4$ 到 $8$。另一个同样好的方案是让编号为 $2$、$4$ 和 $5$ 的律师参加，持续时间从 $5$ 到 $9$。

![](https://cdn.luogu.com.cn/upload/image_hosting/187yuqy1.png)

#### 附加样例

参见 `pra/pra*.in` 和 `pra/pra*.out`：

- 附加样例 $1$：$1$ 组数据，$n=7$，$k=3$，且选择律师的方案有两种。

- 附加样例 $2$：$1$ 组数据，$n=k=1000$，$a_i=i$，$b_i=10^6+i$；

- 附加样例 $3$：$1$ 组数据，$n=1000$，$k=1$，$a_i=2i-1$，$b_i=2i$；

#### 数据范围与提示

测试集分为以下子任务。每个子任务的测试由一个或多个单独的测试组组成。

| Subtask # | 额外限制                         | 分值  |
|:---------:|:----------------------------:|:---:|
| $1$         | $n\le 20$       | $20$  |
| $2$         | $n\le 300$，$a_i,b_i\le 300$      | $15$  |
| $3$         | $n\le 5000$       | $15$  |
| $4$         | $n\le 10^6$，$k\in \{1,n\}$       | $15$  |
| $5$         | $n\le 10^6$       | $35$  |

如果你的程序在第一行输出了正确的时长，但其余的输出是错误的，那么你将获得 $40\%$ 的分数。


---

---
title: "[蓝桥杯 2021 省 AB2] 负载均衡"
layout: "post"
diff: 普及/提高-
pid: P8755
tag: ['模拟', '堆', '2021', '蓝桥杯省赛']
---
# [蓝桥杯 2021 省 AB2] 负载均衡
## 题目描述

有 $n$ 台计算机，第 $i$ 台计算机的运算能力为 $v_{i}$ 。

有一系列的任务被指派到各个计算机上，第 $i$ 个任务在 $a_{i}$ 时刻分配，指定计算机编号为 $b_{i}$, 耗时为 $c_{i}$ 且算力消耗为 $d_{i}$。如果此任务成功分配，将立刻开始运行, 期间持续占用 $b_{i}$ 号计算机 $d_{i}$ 的算力, 持续 $c_{i}$ 秒。

对于每次任务分配，如果计算机剩余的运算能力不足则输出 $-1$，并取消这次分配，否则输出分配完这个任务后这台计算机的剩余运算能力。
## 输入格式

输入的第一行包含两个整数 $n, m$，分别表示计算机数目和要分配的任务数。

第二行包含 $n$ 个整数 $v_{1}, v_{2}, \cdots v_{n}$，分别表示每个计算机的运算能力。

接下来 $m$ 行每行 $4$ 个整数 $a_{i}, b_{i}, c_{i}, d_{i}$，意义如上所述。数据保证 $a_{i}$ 严格递增，即 $a_{i}<a_{i+1}$ 。

## 输出格式

输出 $m$ 行，每行包含一个数，对应每次任务分配的结果。
## 样例

### 样例输入 #1
```
2 6
5 5
1 1 5 3
2 2 2 6
3 1 2 3
4 1 6 1
5 1 3 3
6 1 3 4
```
### 样例输出 #1
```
2
-1
-1
1
-1
0
```
## 提示

**【样例说明】**

时刻 $1$，第 $1$ 个任务被分配到第 $1$ 台计算机，耗时为 $5$，这个任务时刻 $6$ 会结束, 占用计算机 $1$ 的算力 $3$。

时刻 $2$，第 $2$ 个任务需要的算力不足，所以分配失败了。

时刻 $3$，第 $1$ 个计算机仍然正在计算第 $1$ 个任务，剩余算力不足 $3$，所以失败。

时刻 $4$，第 $1$ 个计算机仍然正在计算第 $1$ 个任务，但剩余算力足够，分配后剩余算力 $1$。

时刻 $5$，第 $1$ 个计算机仍然正在计算第 $1$，$4$ 个任务，剩余算力不足 $4$，失败。

时刻 $6$，第 $1$ 个计算机仍然正在计算第 $4$ 个任务，剩余算力足够，且恰好用完。

**【评测用例规模与约定】**

对于 $20 \%$ 的评测用例, $n, m \leq 200$。

对于 $40 \%$ 的评测用例, $n, m \leq 2000$。

对于所有评测用例, $1 \leq n, m \leq 2\times 10^5,1 \leq a_{i}, c_{i}, d_{i}, v_{i} \leq 10^{9}, 1 \leq b_{i} \leq n$。 

蓝桥杯 2021 第二轮省赛 A 组 H 题（B 组 I 题）。


---

