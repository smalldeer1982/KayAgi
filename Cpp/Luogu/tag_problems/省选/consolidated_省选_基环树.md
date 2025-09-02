---
title: "[GCJ 2022 Finals] Schrödinger and Pavlov"
layout: "post"
diff: 省选/NOI-
pid: P13004
tag: ['动态规划 DP', '2022', '概率论', '基环树', 'Google Code Jam']
---
# [GCJ 2022 Finals] Schrödinger and Pavlov
## 题目描述

 _The story, all names, characters, and incidents portrayed in this problem statement are fictitious. No identification with actual persons is intended or should be inferred._ 

It is 1935 and a meeting between two Nobel prize winners is producing astonishing results. Schrödinger, a famous physicist, invited Pavlov, a famous physiologist, to see his experiments with cats in boxes. Pavlov brought his dog with him to keep up with his own research, and the combination proved interesting, to say the least.

Schrödinger had a row of $\mathbf{N}$ boxes. Some boxes definitely contain a cat, some boxes definitely do not contain a cat, and some boxes may or may not contain a cat. Each box is only big enough to hold a single cat. Each box is also equipped with a special quantum tunnel, that allows the cat in the box to move to some other specific box if the destination was empty. The tunnels work in a single direction.

Cats are usually mellow and quiet and do not use the tunnels unless they become startled. When a third unannounced guest rings the bell, Pavlov's dog gets excited immediately and starts running and barking. The dog starts at box 1 and runs towards box $\mathbf{N}$. As the dog runs, it passes right next to each box, one at a time. When it passes next to a box that contains a cat, the cat in that box becomes startled. The startled cat checks the available tunnel and, if the destination box is empty, uses it to escape. If the destination box is occupied, the cat stays in its current box. The same cat can be startled more than once if they move to a box the dog will get to afterwards, and will proceed in the same way every time it is startled (using only the newly available tunnel each subsequent time).

![](https://cdn.luogu.com.cn/upload/image_hosting/xcqaev9m.png)

After Pavlov's dog finally stops right next to the last box, Pavlov asks Schrödinger whether there is a cat in that last box. Schrödinger, true to his fame, replies that he does not know. Pavlov notices that the answer may depend on whether or not there were cats in the unknown boxes. Moreover, he also notices that because there are $k$ unknown boxes, there are $2^k$ possible *initial configurations*, one for each combination of statuses of the unknown boxes. Pavlov tells Schrödinger that they should try to calculate how many of the $2^k$ initial configurations would result in having a cat in the last box. You are asked to recreate that calculation. Since the output can be a really big number, we only ask you to output the remainder of dividing the result by the prime $10^9 + 7$ (1000000007).

*Neither cats, nor dogs, nor Nobel prize winners were harmed in the making of this problem statement.*
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow, each described by exactly three lines. The first line of a test case contains a single integer $\mathbf{N}$, the number of boxes in Schrödinger's experiment. Boxes are numbered between 1 and $\mathbf{N}$, in the order Pavlov's dog passes them by. The second line of a test case contains a single string $\mathbf{S}$ of $\mathbf{N}$ characters. The $i$-th character of $\mathbf{S}$ (counting from left to right) represents the contents of box $i$: it is an uppercase 'c' if the box contains a cat, a period '.' if the box does not contain a cat and a question mark '?' if it is unknown whether the box contains a cat or not. The third line of a test case contains $\mathbf{N}$ integers $\mathbf{B}_1$, $\mathbf{B}_2$, $\dots$, $\mathbf{B}_\mathbf{N}$, representing that there is a tunnel going out of box $i$ and into box $\mathbf{B}_i$, for all $i$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the number of initial configurations that would result in a cat being in the last box and unable to escape despite hearing the barking, modulo the prime $10^9 + 7$ ($1000000007$).
## 样例

### 样例输入 #1
```
4
4
??.C
2 3 1 3
4
????
2 3 1 3
6
?.????
6 6 6 6 6 5
34
????????????????????????????????CC
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 33
```
### 样例输出 #1
```
Case #1: 1
Case #2: 2
Case #3: 15
Case #4: 294967268
```
## 提示

**Sample Explanation**

Sample Case #1 is illustrated in the problem statement. There are 4 possible configurations:

*   `...C`: the dog runs through the first 3 boxes without changing anything because there is no cat there. Then, when it gets to the last box, the cat hears it and escapes to box 3. Therefore, there is no cat in the last box in this case.
*   `C..C`: when the dog barks near box 1, that startles the cat that goes through the tunnel to get to box 2, which was empty. Then, the same cat gets startled again when the dog barks near box 2 and gets to box 3. And when the dog barks next to box 3, the cat hears it and returns to box 1. Therefore, when the dog gets to box 4 and the other cats hears it, box 3 is empty so the cat escapes and the last box ends up empty.
*   `.C.C`: This case is very similar to the previous one. After the dog goes through the first box and nothing happens, the state is the same as before, so the ultimate result is the same: last box empty.
*   `CC.C`: In this case, the cat in the first box cannot escape when it hears the dog, so it remains in box 1. Then, when the cat in box 2 gets startled it escapes to box 3 leaving a state of `C.CC`. When the dog gets to the box 3, the cat currently there cannot escape to box 1 so the state remains the same. Finally, when the dog gets to the last box, the cat that is there cannot escape because box 3 is occupied this time. So, in this case, the last box ends up with a cat after the dog ends its journey.

Out of the 4 possibilities, only 1 (the last one) ends up with a cat in the last box, so the answer is 1.

In Sample Case #2, the tunnels are set up the same as in Sample Case #1. Since no tunnel ends at the last box, the configurations that start with no cat at the last box will also not end with a cat there, so we do not need to count them. Then, we have 8 additional configurations. The 4 we considered for Sample Case #1, out of which only 1 ends up with a cat at the last box. The remaining 4 configurations are: `..CC`, `C.CC`, `.CCC`, `CCCC`. From these additional 4 configurations, only in the last one listed a cat ends up in the last box, for a total of 2 overall.

In Sample Case #3, notice that for a cat to remain in the last box after the dog barks near it, both that box and box 5 must be occupied then (otherwise, either there is no cat in the last box, or it will escape to box 5). Since there is no tunnel going into box 5, a cat must start there. As long as there is another cat in any other box, box 6 will get (or remain) occupied before the cat in box 5 gets an opportunity to escape, so all of those will end up with a cat in the last box. As we argued before, a single cat is not enough. Thus, we need to count the number of configurations with a cat in box 5 and at least one other cat. There are $2^4$ configurations with a cat in box 5, and out of those, only 1 has no other cat, so the answer is $2^4 - 1 = 15$.

In Sample Case #4, in all of the $2^k$ ways in which the $k$ unknown boxes may exist a cat would be left in the last box.

**Limits**

- $1 \leq \mathbf{T} \leq 1234$.
- the length of $\mathbf{S} = \mathbf{N}$.
E- ach character of $\mathbf{S}$ is either an upper case 'c', a period '.' or a question mark '?'.
- $1 \leq \mathbf{B}_i \leq \mathbf{N}$, for all $i$.
- $\mathbf{B}_i \neq i$, for all $i$.

**Test Set 1 (8 Pts, Visible Verdict)**

- $1 \leq \mathbf{N} \leq 100$.
- $i - 5 \leq \mathbf{B}_i \leq i + 5$, for all $i$. (All tunnels connect to nearby boxes.)

**Test Set 2 (42 Pts, Hidden Verdict)**

- $1 \leq \mathbf{N} \leq 5000$.


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
title: "[SCOI2008] 城堡 - 数据加强版"
layout: "post"
diff: 省选/NOI-
pid: P2454
tag: ['基环树']
---
# [SCOI2008] 城堡 - 数据加强版
## 题目背景

[原题弱化版](https://www.luogu.com.cn/problem/P2538)
## 题目描述

在一个国家里，有 $n$ 个城市（编号为 $0$ 到 $n-1$）。这些城市之间有 $n$ 条双向道路相连（编号为 $0$ 到 $n-1$），其中编号为 $i$ 的道路连接了城市 $i$ 和城市 $r_i$（一条道路可以连接一个城市和它自身），长度为 $d_i$。$n$ 个城市中有 $m$ 个拥有自己城堡，可以抵御敌人侵略。如果没有城堡的城市遭受攻击，则离它最近的城堡将派兵前往救援。

你的任务是在不超过 $k$ 个没有城堡的城市中建立城堡，使得所有城市中“离最近城堡的距离”的最大值尽量小。换句话说，若令 $dist(c)$ 表示城市 $c$ 的最近城堡离它的距离，则你的任务是让 $\max\{dist(c)\}$ 尽量小。

输入数据保证存在方案使得对于每个城市，至少有一个城堡能够到达。
## 输入格式

输入第一行为三个正整数 $n, m, k$。第二行包含 $n$ 个整数 $r_0,r_1,\ldots,r_{n-1}$。第三行包含 $n$ 个整数 $d_0,d_1,\ldots,d_{n-1}$。第四行包含 $m$ 个各不相同的 $0$ 到 $n-1$ 之间的整数，分别为 $m$ 个城堡所在的城市编号。
## 输出格式

输出仅一行，包含一个整数，即 $\max\{dist(c)\}$ 的最小值。
## 样例

### 样例输入 #1
```
5 0 1
1 2 3 4 0
1 1 1 1 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 1 1
1 2 0
1 2 3
2
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
2 1 1  
0 1  
1 1  
1
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
10 3 3
0 2 0 0 2 2 8 3 8 7
10 9 1 8 1 3 7 2 8 1
3 4 6
```
### 样例输出 #4
```
3
```
### 样例输入 #5
```
2 0 1
1 0
5 10
```
### 样例输出 #5
```
5
```
## 提示

$100\%$ 的数据满足：$1\leq d_i\leq 10^5$，$0\leq m\leq n-k$。

- Subtask 1：$2 \leq n \leq 3000$。
- Subtask 2：$2 \leq n \leq 10^5$。


---

---
title: "[SCOI2008] 城堡"
layout: "post"
diff: 省选/NOI-
pid: P2538
tag: ['动态规划 DP', '搜索', '2008', '四川', '各省省选', '基环树']
---
# [SCOI2008] 城堡
## 题目背景

2008NOI四川省选

## 题目描述

在一个国家里，有 $n$ 个城市（编号为 $0$ 到 $n-1$）。这些城市之间有 $n$ 条双向道路相连（编号为 $0$ 到 $n-1$），其中编号为 $i$ 的道路连接了城市 $i$ 和城市 $r_i$（一条道路可以连接一个城市和它自身），长度为 $d_i$。$n$ 个城市中有 $m$ 个拥有自己城堡，可以抵御敌人侵略。如果没有城堡的城市遭受攻击，则离它最近的城堡将派兵前往救援。

你的任务是在不超过 $k$ 个没有城堡的城市中建立城堡，使得所有城市中“离最近城堡的距离”的最大值尽量小。换句话说，若令 $dist(c)$ 表示城市 $c$ 的最近城堡离它的距离，则你的任务是让 $\max\{dist(c)\}$ 尽量小。

输入数据保证存在方案使得对于每个城市，至少有一个城堡能够到达。
## 输入格式

输入第一行为三个正整数 $n, m, k$。第二行包含 $n$ 个整数 $r_0,r_1,\ldots,r_{n-1}$。第三行包含 $n$ 个整数 $d_0,d_1,\ldots,d_{n-1}$。第四行包含 $m$ 个各不相同的 $0$ 到 $n-1$ 之间的整数，分别为 $m$ 个城堡所在的城市编号。
## 输出格式

输出仅一行，包含一个整数，即 $\max\{dist(c)\}$ 的最小值。
## 样例

### 样例输入 #1
```
5 0 1
1 2 3 4 0
1 1 1 1 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 1 1
1 2 0
1 2 3
2
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
2 1 1  
0 1  
1 1  
1 
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
10 3 3
0 2 0 0 2 2 8 3 8 7
10 9 1 8 1 3 7 2 8 1
3 4 6
```
### 样例输出 #4
```
3
```
### 样例输入 #5
```
2 0 1
1 0
5 10
```
### 样例输出 #5
```
5
```
## 提示

$100\%$ 的数据满足: $2\leq n\leq 50$，$1\leq d_i\leq 10^6$，$0\leq m\leq n-k$。


---

---
title: "小清新计数题"
layout: "post"
diff: 省选/NOI-
pid: P3673
tag: ['洛谷原创', 'O2优化', '枚举', '生成树', '基环树', '洛谷月赛']
---
# 小清新计数题
## 题目描述

小 A 正在电脑上玩一个叫做 Truth or Lie 的游戏。

游戏开始时电脑会给出 $n$ 句话，每句话形如“第 $x$ 句话为真”或“第 $x$ 句话为假”，其中 $x$ 是一个 $1$ 到 $n$ 的整数，你只要选择“Good”或者“Bad”，“Good”表示可以决定每句话的真假使每句话的内容都成立，“Bad”反之。

作为一个菜鸡，小 A 只会不停地点“Good”，靠脸过关。

在无数次失败后，非洲人小 A 发现游戏每关中，每句话包含的是“真”还是“假”是固定的，但是每句话中的 $x$ 是在 $1$ 到 $n$ 均匀随机的。

现在小 A 告诉了你某一关每句话的真假，用一个 $01$ 序列表示。第 $i$ 位为 $0$ 表示第 $i$ 句话包含“假”，否则表示包含“真”。现在他想要知道使得点击“Good”正确的方案数。

由于方案数可能比较大，你需要输出方案数对 $998244353$ 取模的结果。

（读不懂题的请移步样例解释）
## 输入格式

一行一个 $01$ 序列，它的长度即为 $n$。
## 输出格式

输出方案数对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
01
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
10101
```
### 样例输出 #2
```
1154
```
### 样例输入 #3
```
10101101010111110100110100101010110001010010101001
```
### 样例输出 #3
```
322173207
```
## 提示

### 样例解释

第一句话的内容为“某句话为假”，第二句话的内容为“某句话为真”。所有可能情况如下：

1. 第一句话的内容为“第一句话为假”，第二句话的内容为“第一句话为真”，结果应为 Bad。

2. 第一句话的内容为“第一句话为假”，第二句话的内容为“第二句话为真”，结果应为 Bad。

3. 第一句话的内容为“第二句话为假”，第二句话的内容为“第一句话为真”，结果应为 Bad。

4. 第一句话的内容为“第二句话为假”，第二句话的内容为“第二句话为真”，结果应为 Good，因为只需认为第一句话为假，第二句话为真就符合两句话，所以是 Good。

所以共有一种合法方案。

### 数据范围

- 对于$10\%$ 的数据，$n \leq 7$；
- 对于$20\%$ 的数据，$n \leq 9$；
- 对于$60\%$ 的数据，$n \leq 20$；
- 对于$100\%$ 的数据，$1 \leq n \leq 50$。



---

---
title: "[NOIP 2018 提高组] 旅行 加强版"
layout: "post"
diff: 省选/NOI-
pid: P5049
tag: ['2018', 'NOIP 提高组', '基环树']
---
# [NOIP 2018 提高组] 旅行 加强版
## 题目描述

小 Y 是一个爱好旅行的 OIer。她来到 X 国，打算将各个城市都玩一遍。 
  
小Y了解到，X 国的 $n$ 个城市之间有 $m$ 条双向道路。每条双向道路连接两个城市。 不存在两条连接同一对城市的道路，也不存在一条连接一个城市和它本身的道路。并且， 从任意一个城市出发，通过这些道路都可以到达任意一个其他城市。小 Y 只能通过这些 道路从一个城市前往另一个城市。   

小 Y 的旅行方案是这样的：任意选定一个城市作为起点，然后从起点开始，每次可 以选择一条与当前城市相连的道路，走向一个没有去过的城市，或者沿着第一次访问该 城市时经过的道路后退到上一个城市。当小 Y 回到起点时，她可以选择结束这次旅行或 继续旅行。需要注意的是，小 Y 要求在旅行方案中，每个城市都被访问到。   

为了让自己的旅行更有意义，小 Y 决定在每到达一个新的城市（包括起点）时，将 它的编号记录下来。她知道这样会形成一个长度为 $n$ 的序列。她希望这个序列的字典序 最小，你能帮帮她吗？  对于两个长度均为 $n$ 的序列 $A$ 和 $B$，当且仅当存在一个正整数 $x$，满足以下条件时， 我们说序列 $A$ 的字典序小于 $B$。 
  
- 对于任意正整数 $1 ≤ i < x$，序列 $A$ 的第 $i$ 个元素 $A_i$ 和序列 $B$ 的第 $i$ 个元素 $B_i$ 相同。   
- 序列 $A$ 的第 $x$ 个元素的值小于序列 $B$ 的第 $x$ 个元素的值。 
## 输入格式

输入文件共 $m + 1$ 行。第一行包含两个整数 $n,m(m ≤ n)$，中间用一个空格分隔。
 
接下来 m 行，每行包含两个整数 $u,v (1 ≤ u,v ≤ n)$ ，表示编号为 $u$ 和 $v$ 的城市之 间有一条道路，两个整数之间用一个空格分隔。 
## 输出格式

输出文件包含一行，$n$ 个整数，表示字典序最小的序列。相邻两个整数之间用一个 空格分隔。 
## 样例

### 样例输入 #1
```
6 5 
1 3 
2 3 
2 5 
3 4 
4 6
```
### 样例输出 #1
```
1 3 2 5 4 6
```
### 样例输入 #2
```
6 6 
1 3 
2 3 
2 5 
3 4 
4 5 
4 6
```
### 样例输出 #2
```
1 3 2 4 5 6
```
## 提示

【数据规模与约定】   

对于 $100\%$ 的数据和所有样例， $1 \le n \le 500000 $ 且 $m = n - 1$ 或 $m = n$ 。

具体规定详见正常版本（除 testcase11-13）


---

---
title: "「DAOI R1」Fireworks"
layout: "post"
diff: 省选/NOI-
pid: P8288
tag: ['并查集', '树形 DP', '拓扑排序', '基环树']
---
# 「DAOI R1」Fireworks
## 题目背景

> 俯首，满城灯火交辉。
> 
> 回眸，漫天流星逆飞。
## 题目描述

人们以前通常会放烟花，而每个烟花都有它本身的美观度。

$ \texttt{Iratis} $ 想要在户外放烟花，但是有烟花之间有一些关系：

- 关系一：对于烟花 $ x $ ，有一个对应烟花 $ a_x $ ，若烟花 $ x $ 与烟花 $ a_x $ 一起燃放，就会使烟花 $ x $ 的美观度减少 $ b_x $ 。

- 关系二：有一些烟花是一个系列，必须同时燃放，其中有一个是主烟花，**每个烟花只会属于一个系列**。

特别地，若有一系列 $ S_1 $ （主烟花为 $ p_1 $ ） 。 $ p_1 $ 关系一所对应的烟花为系列 $ S_2 $ 中的烟花。而 $ S_1 $ 系列中的其他烟花与非 $ S_1,S_2 $ 系列中的烟花形成关系一。**那么对于这条关系一，它不会降低美观度。**

$ \texttt{Iratis} $ 家里有 $ n $ 个烟花，他希望选择其中的一些烟花燃放，使得这些**烟花的美观度总和**最大。
## 输入格式

第一行包含两个整数 $ n,m $，分别描述烟花的个数和和关系二的个数。

接下来 $ n $ 行，每行三个整数 $ v_i,a_i,b_i $ ，分别是这个烟花的美观度、关系一对应的烟花、关系一降低的美观度。

最后 $ m $ 行，每行先读入两个数 $ p_i,k_i $，然后是 $ k_i $ 个数，表示这 $ k_i $ 个烟花是一个系列，编号为 $ p_i $ 的烟花为主烟花。
## 输出格式

输出一行一个整数，表示烟花的美观度总和。
## 样例

### 样例输入 #1
```
3 0
2 2 1
2 3 1
2 1 1

```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4 1
3 2 1
3 1 3
3 4 2
3 3 2
1 2 1 3

```
### 样例输出 #2
```
7
```
## 提示

### 样例解释
#### 样例1解释

烟花 $ 1,2,3 $ 一起燃放，最大美观度为 $ 2+2+2-1-1-1=3 $ 。

#### 样例2解释

烟花 $ 1,3,4 $ 一起燃放。

由于 $ 1,3 $ 为同一系列且 $ 1 $ 为主烟花，所以 $ 3 $ 烟花的关系一不会生效。

故总的美观度为 $ 3 \times 3-2=7 $ 。

### 数据规模

**本题采用捆绑测试**

| Subtask | $ m $  | 分值 |
| :----------: | :----------: | :----------: |
| $ 0 $ | $ =0 $ | $ 30 $ |
| $ 1 $ | 无特殊限制 | $ 70 $ |

对于 $ 100\% $ 的数据，满足 $ 0 \leq m \leq n \leq 5 \times 10^5,0 \leq b_i \leq v_i \leq 10^{12},1 \leq a_i \leq n,a_i \neq i $ 。 


---

---
title: "Altale (Fan-made FTR 7)"
layout: "post"
diff: 省选/NOI-
pid: P8439
tag: ['贪心', '洛谷原创', 'O2优化', '基环树', '洛谷月赛']
---
# Altale (Fan-made FTR 7)
## 题目背景

[![](https://cdn.luogu.com.cn/upload/image_hosting/inglwsjz.png)](https://music.163.com/#/program?id=2067229684)

为什么评级 7？

Powerless：Equilibrium FTR 9.
## 题目描述

小机器人又在钓星星了。

星星在天空中形成了若干个星座，每个星座有一个“中心点”，如果星星脱离了与中心点的直接或间接的联系，那么星星就会从星座中脱离，掉落到地面上。

经过小机器人日日夜夜的观测，他发现了这些星座的性质：每一个星座内部都是联通的，星星的联系的数量总与星座中星星的数量相等。

另外，不同的星座之间星星没有联系，同一个星座中的星星都有间接或直接的联系。

他通过观测天体运动给星星编了号，他发现每个星座的中心点都是星座中编号最小的星星。

可惜的是，小机器人只能通过随（diao）缘（yu）的方式获得取消这些联系的钥匙。

小机器人非常贪心，想要用尽量少的时间获得尽量多的星星。

他想要 $k$ 颗星星，你能告诉他他至少需要钓上几把钥匙吗？

如果你解决了这个问题，说不定小机器人会送给你几颗星星哦~

**[简化题意](https://www.luogu.com.cn/paste/5nhqqjzm)**
## 输入格式

第一行两个整数 $n,k$，表示**天空中**所有的星星的**总数**和星星之间联系**总数**，和小机器人希望获得的星星数。

接下来 $n$ 行，每行两个整数 $u,v$ 表示 第 $u$ 颗和第 $v$ 颗星星之间存在联系。

保证任意星座内星星联系条数等于星星数，星星不会有自己到自己的联系，不会有两条联系建立在同样两颗星星上。
## 输出格式

一行一个整数，表示小机器人需要获得足够的星星所需最少的钥匙数。
## 样例

### 样例输入 #1
```
4 1
1 2
2 3
3 1
1 4
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
17 9
1 2
1 6
1 3
3 4
4 5
5 6
6 7
8 10
10 9
10 11
11 12
11 13
13 14
14 8
15 13
8 16
16 17
```
### 样例输出 #2
```
3
```
## 提示

**本题采用捆绑测试。**

设星座共有 $l$ 个。

对于 $100\%$ 的数据，保证 $1\le n\le 10^6,1\le k\le n-l$。

Subtask 1：对于 $20\%$ 的数据，保证 $n\le 1000$。

Subtask 2：对于 $10\%$ 的数据，保证 $l\le 5$。

Subtask 3：对于 $20\%$ 的数据，保证 $l\le 15$。

Subtask 4：无特殊限制。

----

样例解释 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/ov9db62k.png)

消除 $(1,4)$ 间联系即可。

样例解释 $2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/wh22obzj.png)

消除 $(8,14),(8,10),(8,16)$ 三条联系即可。

可以证明没有消除联系更少的方法。

可能有别的方法也仅需要消除 $3$ 条联系。


---

---
title: "「CGOI-2」No mind to think"
layout: "post"
diff: 省选/NOI-
pid: P8503
tag: ['动态规划 DP', 'O2优化', '基环树']
---
# 「CGOI-2」No mind to think
## 题目背景

“我的王，这个孩子……不纯粹……他……”

“嗯。容器不能拥有与人交流的能力，否则可能会在交流中产生思维。它们只应该有猎杀的本能，和战斗的天分。就像我的守卫们一样。”

“那些不过是傀儡……”

“傀儡也比这个有思维的家伙好。改天把它带走，它真的好吵……我累了，我出去走走。”

~~无敌的勇敢的性感的神秘的迷人的神气的勤勉的强势的华丽的激情的可怕的漂亮的强大的灰色王子左特骂骂咧咧地滚出了白色宫殿。~~
## 题目描述

圣巢有 $n$ 个鹿角虫车站和 $n$ 条轨道，第 $i$ 条轨道连接 $u_i$ 和 $v_i$ 两个车站。初始时轨道是单向的，第一次经过第 $i$ 条轨道时，只能从 $u_i$ 到达 $v_i$；第一次经过后该轨道变为双向，既可以从 $u_i$ 到 $v_i$，又可以从 $v_i$ 到 $u_i$。

现在白王在 $1$ 号车站，他要经过若干条轨道到达 $2$ 号车站，再从 $2$ 号车站经过若干条轨道到达 $3$ 号车站……一直到 $x$ 号车站。因为白王需要尽快走遍整个王国以便探清瘟疫的情况，所以他问你，当 $x$ 取遍 $[2,n]$ 中的每一个整数时，所经过的最少的轨道数分别是多少。
## 输入格式

第一行一个整数 $n$，表示车站数与轨道数。

接下来 $n$ 行，每行两个整数。第 $i$ 行的数 $u_i,v_i$ 表示第 $i$ 条轨道第一次经过时只能从 $u_i$ 走到 $v_i$，此后可以双向经过。
## 输出格式

输出 $n-1$ 行，每行一个数，第 $i$ 个数表示当 $x=i+1$ 时，经过的最少轨道数。
## 样例

### 样例输入 #1
```
7
1 7
7 6
1 2
2 3
3 4
4 5
5 6
```
### 样例输出 #1
```
1
2
3
4
5
10
```
### 样例输入 #2
```
6
1 4
4 2
2 6
6 1
6 3
1 5
```
### 样例输出 #2
```
2
4
7
9
11
```
### 样例输入 #3
```
18
14 15
8 12
5 4
10 14
15 17
7 5
3 9
9 18
11 13
1 2
16 10
5 11
5 6
6 8
2 3
2 7
18 16
7 10
```
### 样例输出 #3
```
1
2
6
7
8
10
13
19
22
26
30
35
40
41
45
49
54
```
## 提示

### 样例说明

对于样例 1，地图如下所示：

![样例 1 地图](https://z3.ax1x.com/2021/06/24/RMPoN9.png)

$x=2,3,4,5,6$ 的最短路径均为沿着 $1\to 2\to3\to4\to5\to6$ 这条路径走，答案分别是 $1,2,3,4,5$。

$x=7$ 时，若仍按照上述路径走，就不能从 $6$ 号车站直接通过 $7\to 6$ 这条轨道到 $7$ 号车站，因为这条轨道还是单向的。绕路回去需要再经过 $6$ 条轨道，总共 $11$ 条轨道。

但如果先走一遍 $7\to6$，即沿着 $1\to7\to6\to7\to1\to2\to3\to4\to5\to6$ 的路径走，来到 $6$ 时就能直接走到 $7$，总共只需要经过 $10$ 条轨道，同时也满足了依次经过 $1\sim 7$ 号点，比上一种方案更优。

---

### 数据范围

**本题采用捆绑测试。**

| 编号 | $n$ |分值|
| :-: | :-: | :-: |
| 0 | $\le6$ | 10pts|
| 1 | $\le18$ | 20pts |
| 2 | $\le3\times10^3$ | 32pts |
| 3 | $\le5\times10^5$ | 38pts |

对于 $100\%$ 的数据，$3\le n\le5\times10^5$。

数据保证从 $1$ 号车站出发可以到达任意车站，且无重边自环、二元环。


---

---
title: "『GROI-R1』 古朴而优雅"
layout: "post"
diff: 省选/NOI-
pid: P8974
tag: ['数学', '图论', 'O2优化', '最近公共祖先 LCA', '基环树']
---
# 『GROI-R1』 古朴而优雅
## 题目背景


会馆内忽地安静了下来。

「敝姓言，名杉。」

他的声音沉稳而凝重，略带沙哑，却不失力度，极具穿透力。每个字都重重地打在耳畔，渗进头脑里，让人想不认真听都难。

「这所学院的院长。」
## 题目描述

杉虽然年事已高，但是还是保持与时俱进。他学习了深度优先遍历算法，觉得这种新潮的东西在一所古朴而优雅的学院里会很受欢迎。所以，他找到了在走廊里晃荡的寒，向他提出了一个问题：

「我们知道，对一棵树进行深度优先遍历可以用下面的伪代码很好地解决。」

$$
\begin{array}{l}
\text{DFS-TREE}(u)\\
\begin{array}{ll}
1 & p\gets p+1\\
2 & t_p\gets u\\
3 & vis_u\gets 1\\
4 & \textbf{for }\text{each edge }(u,v)\in E \\
5 & \qquad \textbf{if }vis_v=0\\
6 & \qquad \qquad \text{DFS-TREE}(v)\\
7 & p\gets p+1\\
8 & t_p\gets u\\
\end{array}
\end{array}
$$

起初，所有变量或数组的值均为 $0$。

「我们把调用 $\text{DFS-TREE}(1)$ 在遍历过程中得到的数组 $t$ 称为这棵树的**遍历顺序**。」

「你看这段代码的第 $4$ 行，这句话**遍历每一条边的顺序是不固定的**。」

寒素来最讨厌不确定的东西，可是碍于院长的颜面，还是继续听下去。

「你能数出这段代码**会生成多少种不同的遍历顺序**吗？」

寒发现他曾经做过这个题，很快地报出了解法。本以为就结束了，可是杉继续说：

「如果我**在树上增加一条边**，你还会做吗？」

寒发现他的那点水平完全不够了，于是他去请教玘。玘却认为这道题目依然很简单，他告诉了寒这道题的做法。可是寒找不到杉了。

这个世界到底怎么了呢？
## 输入格式

第一行，两个整数 $n$ 和 $q$，表示树上有 $n$ 个结点，编号为 $1\sim n$，有 $q$ 次询问。

接下来 $n-1$ 行，每行两个整数 $u,v$，描述这棵树上的一条边。

接下来 $q$ 行，每行两个整数 $x,y$，表示在树上添加连接 $x$ 和 $y$ 的一条边，询问有多少种可能的遍历顺序。注意：每次询问是**互相独立的**，也就是说，上一次询问添加的边不会保留到下一次询问。
## 输出格式

共 $q$ 行，每行一个整数表示这次询问的答案对 $10^9+7$ 取模后得到的值。
## 样例

### 样例输入 #1
```
4 2
1 2
1 3
1 4
2 3
1 4
```
### 样例输出 #1
```
4
6
```
## 提示

**样例解释**

对于第一次询问可以得到如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ojeiswc8.png)

能得到的遍历顺序有：

- $\{1,2,3,3,2,4,4,1\}$
- $\{1,4,4,2,3,3,2,1\}$
- $\{1,3,2,2,3,4,4,1\}$
- $\{1,4,4,3,2,2,3,1\}$

对于第二次询问可以得到如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6dut5s4r.png)

能得到的遍历顺序有：

- $\{1,2,2,3,3,4,4,1\}$
- $\{1,2,2,4,4,3,3,1\}$
- $\{1,3,3,2,2,4,4,1\}$
- $\{1,3,3,4,4,2,2,1\}$
- $\{1,4,4,2,2,3,3,1\}$
- $\{1,4,4,3,3,2,2,1\}$

**数据范围**

**本题采用捆绑测试。**

| 测试点编号 | 数据范围 | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $\text{Subtask1}$ | $n,q\le8$ |  | $5$ |
| $\text{Subtask2}$ | $n,q\le20$ |  | $10$ |
| $\text{Subtask3}$ | $n,q\le500$ |  | $10$ |
| $\text{Subtask4}$ | $n,q\le3000$ |  | $15$ |
| $\text{Subtask5}$ | $n,q\le2\times10^5$ | $\text{A}$ | $15$ |
| $\text{Subtask6}$ | $n,q\le2\times10^5$ | $\text{B}$ | $10$ |
| $\text{Subtask7}$ | $n,q\le2\times10^5$ |  | $35$ |

特殊性质 $\text{A}$：保证每一次询问的边 $(x,y)\in E$。

特殊性质 $\text{B}$：保证树退化成一条链。

对于 $100\%$ 的数据保证 $1\le n,q\le2\times10^5$，$1\le u,v,x,y\le n$，$x\ne y$。


---

---
title: "「TFOI R1」Ride the Wind and Waves"
layout: "post"
diff: 省选/NOI-
pid: P9706
tag: ['动态规划 DP', 'O2优化', '前缀和', '基环树', '差分']
---
# 「TFOI R1」Ride the Wind and Waves
## 题目背景

Z 教授是 C 班的老师。

Z 教授最近发现一个神奇的现象，他的学生竟然都有自己暗恋的对象，但是没有一个人勇于表白。

Z 教授作为过来人，当然懂得每一个学生心里最真实纯真的想法，以及自认为的爱意情愫。Z 教授想起了初恋蕉太狼，他不想让自己的学生在青春年华失去色彩，于是 Z 教授冒着被开除的风险，主动帮助学生表达心意。

然后 Z 教授被开除了。
## 题目描述

有一棵 $n$ 个节点的内向基环树（**保证弱连通**），树上每条边都有一个权值。现有一个特定参数 $k$。

由于基环树是内向的，所以一个点 $x$ 可能会有无法直接到达的节点。但是我们可以翻转树上的一些有向边，这样 $x$ 就可以到达树上每一个节点。如果一个节点 $x$ 需要**至少**翻转 $k$ 条边才能到达 $y$，则称 $y$ 是 $x$ 的乘风破浪点。在翻转了**最少的边**使得 $x$ 可以到达 $y$ 之后，在 $x$ 到 $y$ 的最短路径上，定义 $F(x, y)$ 为**未翻转**的边的权值之和，$R(x, y)$ 为**已翻转**的边的权值之和。

如果 $y$ 是 $x$ 的乘风破浪点，那么有一个值 $G(x, y)$ 表示 $x$ 到 $y$ 的浪涛值，定义 $G(x, y) = F(x, y) \times  R(x,y)$。

请你对于每一个节点 $i$，输出 $\sum G(i, y)$ 的值，其中 $y$ 是 $i$ 的乘风破浪点。
## 输入格式

第一行输入两个正整数 $n, k$，表示基环树大小和一个比较的参数。

接下来 $n$ 行，每行输入 $u, v, w$ 三个正整数，表示树上存在一条边 $(u, v, w)$，表示其起点为 $u$，终点为 $v$，权值为 $w$。
## 输出格式

输出 $n$ 行，每行一个正整数，表示每个节点到它的所有乘风破浪点的浪涛值之和。
## 样例

### 样例输入 #1
```
7 1
1 4 3
2 1 2
3 1 6
4 3 4
5 2 4
6 4 1
7 5 2
```
### 样例输出 #1
```
3
5
105
160
9
176
11
```
### 样例输入 #2
```
7 1
1 2 3
2 3 2
3 1 2
4 1 3
5 4 2
6 2 1
7 6 4
```
### 样例输出 #2
```
18
32
46
36
48
40
72
```
## 提示

#### 样例解释 #1

拿 $3$ 节点的答案为例子，基环树的形状如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/a3ocyi6o.png)

可知 $2,5,6,7$ 为 $3$ 的乘风破浪点，统计答案：

- $G(3, 2) = 6 \times 2 = 12$。

- $G(3, 5) = 6 \times 6 = 36$。

- $G(3, 6) = 9 \times 1 = 9$。

- $G(3, 7) = 6 \times 8 = 48$。

所以 $\sum G(3, j) = 12 + 36 + 9 + 48$，答案为 $105$。

#### 数据范围

**本题采用捆绑测试**。

- Subtask 1（5 points）：$1 \leqslant n \leqslant 10$，**包含特殊性质**。
- Subtask 2（10 points）：$1 \leqslant n \leqslant 5000$，**包含特殊性质**。
- Subtask 3（25 points）：$1 \leqslant n \leqslant 10^5$，**包含特殊性质**。
- Subtask 4（60 points）：$1 \leqslant n \leqslant 10^6$，无特殊限制。

**特殊性质：保证环上节点的个数在 $10^3$ 以内。**

对于所有数据，$1 \leqslant n \leqslant 10^6$，$1 \leqslant k \leqslant 10$，保证答案不会超过 $10^{18}$。


---

---
title: "[EC Final 2022] Coloring"
layout: "post"
diff: 省选/NOI-
pid: P9716
tag: ['动态规划 DP', '2022', 'O2优化', '基环树', 'ICPC']
---
# [EC Final 2022] Coloring
## 题目描述

You are given $n$ elements numbered from $1$ to $n$. Element $i$ has value $w_i$ and color $c_i$. Each element also has a pointer $a_i$ to some other element.

Initially, the color of element $s$ is $1$, while the color of all the other elements is $0$. More formally, $c_s=1$ and $c_i=0$ for all $i\neq s$ $(1 \le i \le n)$.

You can perform the following operation for any number of times:

- Assign $c_i\leftarrow c_{a_i}$ at a cost of $p_i$.

Your score is equal to the sum of values of all the elements with color $1$ after the operations minus the sum of costs of the operations.

Find the maximum possible score you can obtain.
## 输入格式

The first line contains two integers $n,s$ ($1 \leq s\le n \leq 5\times 10^3$) $-$ the number of elements and the element with color $1$ initially.

The second line contains $n$ integers $w_1,w_2,\dots,w_n$ ($-10^9\le w_i\le 10^9$) $-$ the value of the elements.

The third line contains $n$ integers $p_1,p_2,\dots,p_n$ ($0\le p_i\le 10^9$) $-$ the cost of changing the color of each element.

The fourth line contains $n$ integers $a_1,a_2,\dots,a_n$ ($1\le a_i\le n$, $a_i\neq i$).
## 输出格式

Output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
3 1
-1 -1 2
1 0 0
3 1 2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
10 8
36175808 53666444 14885614 -14507677 
-92588511 52375931 -87106420 -7180697 
-158326918 98234152
17550389 45695943 55459378 18577244 
93218347 64719200 84319188 34410268 
20911746 49221094
8 1 2 2 8 8 4 7 8 4
```
### 样例输出 #2
```
35343360
```
## 提示

(There won’t be extra line breakers 
in the actual test cases.)

In the first sample, you can successively perform the following operations:

- Assign $c_2\leftarrow c_{a_2}$ at a cost of $p_2$, then $c=[1,1,0]$;
- Assign $c_1\leftarrow c_{a_1}$ at a cost of $p_1$, then $c=[0,1,0]$;
- Assign $c_3\leftarrow c_{a_3}$ at a cost of $p_3$, then $c=[0,1,1]$;
- Assign $c_2\leftarrow c_{a_2}$ at a cost of $p_2$, then $c=[0,0,1]$.

After the operations, only the color of element $3$ is $1$, so your score is equal to $w_3-(p_2+p_1+p_3+p_2)=1$. It can be shown that it is impossible to obtain a score greater than $1$.
## 题目翻译

**【题目描述】**

给定 $n$ 个元素，编号从 $1$ 到 $n$。元素 $i$ 的值为 $w_i$，颜色为 $c_i$。每个元素还有一个指针 $a_i$ 指向另一个元素。

最初，元素 $s$ 的颜色为 $1$，而所有其他元素的颜色都为 $0$。更正式地说，对于所有 $i\neq s$ $(1 \le i \le n)$，有 $c_s=1$ 和 $c_i=0$。

你可以任意多次执行以下操作：

- 以代价 $p_i$ 将 $c_i\leftarrow c_{a_i}$。

你的得分等于所有颜色为 $1$ 的元素值的总和减去操作的总代价。

找出你能够获得的最大可能得分。

**【输入格式】**

第一行包含两个整数 $n$ 和 $s$（$1 \leq s\le n \leq 5\times 10^3$）$-$ 元素数量以及初始颜色为 $1$ 的元素。

第二行包含 $n$ 个整数 $w_1,w_2,\dots,w_n$（$-10^9\le w_i\le 10^9$）$-$ 元素的值。

第三行包含 $n$ 个整数 $p_1,p_2,\dots,p_n$（$0\le p_i\le 10^9$）$-$ 改变每个元素颜色的代价。

第四行包含 $n$ 个整数 $a_1,a_2,\dots,a_n$（$1\le a_i\le n$, $a_i\neq i$）。

**【输出格式】**

输出一行一个整数，表示答案。

**【样例解释】**

在第一个样例中，你可以依次执行以下操作：

- 以代价 $p_2$ 将 $c_2\leftarrow c_{a_2}$，然后 $c=[1,1,0]$；
- 以代价 $p_1$ 将 $c_1\leftarrow c_{a_1}$，然后 $c=[0,1,0]$；
- 以代价 $p_3$ 将 $c_3\leftarrow c_{a_3}$，然后 $c=[0,1,1]$；
- 以代价 $p_2$ 将 $c_2\leftarrow c_{a_2}$，然后 $c=[0,0,1]$。

操作后，只有元素 $3$ 的颜色为 $1$，因此你的得分等于 $w_3-(p_2+p_1+p_3+p_2)=1$。可以证明无法获得大于 $1$ 的得分。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

