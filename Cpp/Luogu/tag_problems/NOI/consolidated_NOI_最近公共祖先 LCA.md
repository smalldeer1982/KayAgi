---
title: "[集训队互测 2023] 虹"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10016
tag: ['集训队互测', '2023', '数论', '深度优先搜索 DFS', '最近公共祖先 LCA', '分块', '位运算']
---
# [集训队互测 2023] 虹
## 题目描述

给定一棵 $n$ 个点的树。

- 称点集 $S$ **连通**，当且仅当 $\forall u,v \in S$，所有 $u$ 到 $v$ 的简单路径上的点均在 $S$ 中。
- 称点集 $S$ 是 $[l,r]$ 的**虹**，当且仅当 $S$ **连通**，且 $S$ 包含 $[l,r]$ 中的所有点。
- 称点集 $S_0$ 是 $[l,r]$ 的**最小虹**，当且仅当 $S_0$ 是 $[l,r]$ 的所有**虹**中大小最小的。可以证明，$S_0$ 是唯一的。

点带权，点 $u$ 的权值为 $w_u$，初始所有点权均为 $0$。同时，给定序列 $\{z_1,z_2,\cdots,z_n\}$。

给定 $q$ 次命令，每次命令形如以下两类之一：

- `1 l r`：令 $S_0$ 为 $[l,r]$ 的**最小虹**，$\forall u \in S_0$，将 $w_u$ 加 $1$。
- `2 l r u`：求 $\left(\sum_{i=l}^r 19901991^{z_{\gcd(i,u)} w_i} \right) \bmod {20242024}$ 的值。
## 输入格式

第一行两个正整数 $n,q$。

第二行 $n$ 个非负整数，依次表示 $z_1,z_2,\cdots,z_n$。

接下来 $n-1$ 行，每行两个正整数 $u,v$，描述一条树上从 $u$ 到 $v$ 的边。

最后 $q$ 行，每行 $3$ 或 $4$ 个正整数，描述一次命令。

**注意：本题输入文件行末有 `\r`，请选手自行过滤。**
## 输出格式

对于每次询问（即第二类命令）输出答案。
## 样例

### 样例输入 #1
```
5 4
1 0 0 0 1
1 2
1 3
3 4
3 5
1 2 3
2 1 3 3
1 4 5
2 3 5 3
```
### 样例输出 #1
```
19561959
19561959
```
## 提示

**本题采用捆绑测试**。

对于所有测试数据保证：$1 \le n, q \le 8 \times 10^4,0 \le z_i \le 10^9$，所有命令满足 $1 \le l \le r \le n, 1 \le u \le n$，**保证第一类命令的 $(l,r)$ 随机生成**。随机生成方式如下：
- 在 $[1,n] \cap \mathrm{Z}$ 中等概率随机生成 $l$。
- 在 $[1,n] \cap \mathrm{Z}$ 中等概率随机生成 $r$。
- 若 $l>r$，则交换 $l,r$。

| 子任务编号 | 分值 | $n \le$ | $q \le$ | 特殊性质 | 子任务依赖 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :----------: |
| $1$ | $10$ | $10^3$ | $10^3$ | 无 | 无 |
| $2$ | $20$ | $65536$ | $65536$ | A, B | 无 |
| $3$ | $20$ | $65536$ | $65536$ | A | 依赖于子任务 $2$ |
| $4$ | $30$ | $65536$ | $65536$ | 无 | 依赖于子任务 $1,2,3$ |
| $5$ | $20$ | $80000$ | $80000$ | 无 | 依赖于子任务 $1,2,3,4$ |

特殊性质 A：保证所有第二类命令均在所有第一类命令之后。

特殊性质 B：保证第二类命令次数 $\le 20$。


---

---
title: "[集训队互测 2023] Axium Crisis"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10017
tag: ['集训队互测', '2023', 'Special Judge', '最近公共祖先 LCA', '均摊分析', '状压 DP']
---
# [集训队互测 2023] Axium Crisis
## 题目背景

在那灰暗的塔楼前，对立见到了些许光芒碎片。

那些光芒碎片萦绕在对立身旁，宛如繁花点缀。

步入那扭曲的迷宫，对立试图收集其中的纷争碎片，并尝试摧毁这个迷宫。

对立的身旁充斥着光芒和纷争碎片，交错纷飞。

终于，对立来到了那迷宫的最深处。

在那片形状极其古怪的记忆残片上，反射的，是一个世界走向灭亡的回忆。

末日来临，天空撕裂，大地崩坠。

由于这块残片上所承载的「能量」实在过于巨大，对立试图使用其身旁的光芒和纷争碎片来缓和这份巨大的精神上的冲击。

具体的，这块扭曲的残片形成一个「树」的结构，对立将在树的每条边上放上一片光芒或者纷争碎片。

对立将会把这颗树上的边切割成若干条链，使得最终每条边恰好属于其中的某一条链。由于残片的特殊结构，树上的一个节点可以同时属于多条链。

对立会取出一部分链，将放置碎片相同的前缀段进行合并，最后形成一颗新的树，也就是所谓的「Trie 树」。

这颗新的树上的节点越多，就越能缓和对立的情绪，让其冷静下来。

在疯狂中，对立已经给残片上的某些边放上了光芒碎片或者纷争碎片。

一刹那的清醒间，对立意识到了些许不对。因此对立还可以往剩下的边上任意选择光芒或者纷争碎片。

在恍惚间，对立发现自己并不知道如何放置并切割是最优的。

思绪飞快地运转起来。怎样是最优的呢？

相信你已有答案。
## 题目描述

给定一颗 $n$ 个节点的树，节点编号 $0\sim n-1$。

边有边权，边权一般为 $0$ 或者 $1$；但有的边的边权还未确定。

你要给每条未被确定边权的边确定一个 $0$ 或者 $1$ 的边权，然后从树上取出若干条有向路径，使得这些链两两之间满足**边不相交**。

然后你会把这些路径插入一颗 0/1-Trie，你希望最大化这颗 0/1-Trie 上的节点数。（0/1-Trie 定义略）

你可能需要构造具体的选择方案。
## 输入格式

本题每个测试点中有多组测试数据。

第一行两个整数 $T,o$，其中 $T$ 表示测试数据组数，$o$ 表示该测试点的一些特殊性质（请参见「数据范围与提示」一节的描述）。

接下来有 $T$ 组测试数据。

每组数据第一行一个整数 $n$，表示点的个数。

接下来 $n-1$ 行，每行三个整数 $u,v,w$，表示一条连接点 $u,v$ 的边。当 $0\le w\le 1$ 时，表示这条边边权为 $w$；否则总有 $w=2$，表示这条边的边权还未确定。

保证这些边形成一颗点集为 $0\sim n-1$ 的树。
## 输出格式

开头应当输出一个数 $c$（$c\in\{0,1\}$），表示你是否选择在该测试点输出方案，我们会使用 Special Judge 来校验你的输出是否正确。**注意这将影响你在该测试点的得分上限，详见「数据范围与提示」一节的描述**。

对于每组测试数据，首先输出一行一个数 $A$，表示该组数据的答案。

当 $c=1$ 时，还需要继续按如下格式输出你所构造的方案：
* 先输出一行一个数 $m$，表示你构造的方案中路径的数目。
* 接下来一行 $n-1$ 个数，每个数为 $0$ 或者 $1$，表示按输入顺序各边的边权。**对于边权本身已经确定的边，请原样输出。**
* 接下来 $m$ 行，每行两个数 $u,v$，表示树上一条从 $u$ 到 $v$ 的路径。要求 $u\neq v$，且路径两两**边不相交**。
## 样例

### 样例输入 #1
```
9 0
9
1 2 1
3 4 1
5 6 1
7 8 1
2 0 0
4 0 0
6 0 0
8 0 0
9
1 2 2
3 4 1
5 6 1
7 8 1
2 0 0
4 0 0
6 0 0
8 0 0
5
1 2 2
3 4 1
0 3 1
2 3 0
17
1 2 1
2 3 0
3 4 1
4 0 0
5 6 1
6 7 0
7 8 1
8 0 0
9 10 1
10 11 0
11 12 1
12 0 0
13 14 1
14 15 0
15 16 1
16 0 0
17
1 2 1
2 0 0
3 4 1
4 0 0
5 6 1
6 0 0
7 8 1
8 0 0
9 10 1
10 11 0
11 12 1
12 0 0
13 14 1
14 15 0
15 16 1
16 0 0
17
1 2 2
2 0 2
3 4 2
4 0 2
5 6 2
6 0 2
7 8 2
8 0 2
9 10 2
10 11 2
11 12 2
12 0 2
13 14 2
14 15 2
15 16 2
16 0 2
18
1 2 1
2 0 0
3 4 1
4 0 0
5 6 1
6 0 0
7 8 1
8 0 0
9 10 1
10 11 0
11 12 1
12 0 0
13 14 1
14 15 0
15 16 1
16 0 0
0 17 2
18
1 2 2
2 0 2
3 4 2
4 0 2
5 6 2
6 0 2
7 8 2
8 0 2
9 10 2
10 11 2
11 12 2
12 0 2
13 14 2
14 15 2
15 16 2
16 0 2
17 0 2
18
1 2 2
2 3 2
3 4 2
4 5 2
5 6 2
6 7 2
7 8 2
8 9 2
9 10 2
10 11 2
11 12 2
12 13 2
13 14 2
14 15 2
15 16 2
16 17 2
17 0 2
```
### 样例输出 #1
```
1
8
3
1 1 1 1 0 0 0 0
1 3
5 6
6 7
9
2
0 1 1 1 0 0 0 0
3 5
1 7
5
2
0 1 1 0
4 3
1 0
16
3
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
5 1
13 14
14 9
14
5
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
3 1
5 6
14 13
14 7
6 9
16
3
0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0
7 5
1 3
13 9
15
4
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0
13 3
1 7
0 5
17 9
16
4
1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1
1 7
17 0
5 3
13 9
18
1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 0
```
## 提示

#### 样例解释

这组样例对应的答案文件为：

```plain
8
9
5
16
14
16
15
16
18
```

样例输出即 `.out` 文件，也就是你要输出的结果，在 $c=1$ 时需要构造一组合法方案。

样例答案即 `.ans` 文件，该文件中仅会给出每组数据的答案，不会给出构造方案。

接下来依次附上这 $9$ 组样例的图示（选择边权前 / 后各一张）。

![sample0_1_1.png](https://sy.hhwdd.com/RequireFile.do?fid=01t7zGM4)![sample0_1_2.png](https://sy.hhwdd.com/RequireFile.do?fid=EHOyk2Uz)

![sample0_2_1.png](https://sy.hhwdd.com/RequireFile.do?fid=FP2WnHn3)![sample0_2_2.png](https://sy.hhwdd.com/RequireFile.do?fid=c4cKvUgH)

![sample0_3_1.png](https://sy.hhwdd.com/RequireFile.do?fid=U4UoWyyU)![sample0_3_2.png](https://sy.hhwdd.com/RequireFile.do?fid=59JlIWvn)

![sample0_4_1.png](https://sy.hhwdd.com/RequireFile.do?fid=cm5NQIRx)![sample0_4_2.png](https://sy.hhwdd.com/RequireFile.do?fid=jM6lGPo8)

![sample0_5_1.png](https://sy.hhwdd.com/RequireFile.do?fid=7jKRZ9i9)![sample0_5_2.png](https://sy.hhwdd.com/RequireFile.do?fid=Fb1HkD1s)

![sample0_6_1.png](https://sy.hhwdd.com/RequireFile.do?fid=CbEmirO0)![sample0_6_2.png](https://sy.hhwdd.com/RequireFile.do?fid=4GrzzBbe)

![sample0_7_1.png](https://sy.hhwdd.com/RequireFile.do?fid=hRWoM1xi)![sample0_7_2.png](https://sy.hhwdd.com/RequireFile.do?fid=8OgPPrFB)

![sample0_8_1.png](https://sy.hhwdd.com/RequireFile.do?fid=ws6t9q9g)![sample0_8_2.png](https://sy.hhwdd.com/RequireFile.do?fid=RkDgZv7G)

![sample0_9_1.png](https://sy.hhwdd.com/RequireFile.do?fid=MlI0m1pW)![sample0_9_2.png](https://sy.hhwdd.com/RequireFile.do?fid=KJLtHLs7)

#### 更多样例

**因为本题数据规模太大，直接提交评测会对评测机带来很大压力，本题将提供很多大样例；请尽量减少本题的提交次数。**

更多样例请参见下发文件 `axiumcrisis*.in/ans`，共 $20$ 组，基本按照部分分的方法造。

注意下发的答案文件中**没有给出构造方案**，仅会给出每组数据的答案。

下发了一个 `checker.cpp`，你可以自行编译并在终端运行校验合法性。具体使用方法请参考「数据范围与提示」一节的描述。正式测评时使用的 Special Judge 与其并不相同。

为了方便你更好地理解题意，此处额外附一个手搓的样例，这份样例未被放入下发文件。

**建议使用该组样例及样例解释校验你对题意的理解，以免误读**。

#### 数据范围与提示

与[互测实际使用的版本](https://qoj.ac/problem/7769)不同，本题此处将采用数据范围更大的版本。

对于所有的数据，保证 $2\le n\le18$，$1\le T\le3000$。

具体的数据规模分布可以见下表，**各子任务等分，即满分均为 $\rm5pts$**。其中形如 $(l,r)$ 的一列对应的数据表示 $l\le n\le r$ 的数据组数，「无限制」表示无额外限制。

各子任务**捆绑评测**，其分数为该子任务各测试点分数最小值。子任务依赖意味着只有所依赖的子任务分数均非 $0$ 才会评测当前子任务，且分数与所依赖的子任务也取最小值。$o$ 的含义将在之后注明。

|子任务|$(2,4)$|$(5,6)$|$(7,8)$|$(9,11)$|$(12,14)$|$(15,17)$|$(18,18)$|$o$|子任务依赖|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$\le1000$|$=0$|$=0$|$=0$|$=0$|$=0$|$=0$|$=0$|无|
|$2$|无限制|$\le15$|$=0$|$=0$|$=0$|$=0$|$=0$|$=0$|$1$|
|$3$|无限制|$\le500$|$\le10$|$=0$|$=0$|$=0$|$=0$|$=0$|$2$|
|$4$|无限制|$\le1000$|$\le50$|$\le10$|$=0$|$=0$|$=0$|$=2$|无|
|$5$|无限制|$\le1000$|$\le50$|$\le10$|$=0$|$=0$|$=0$|$=3$|无|
|$6$|无限制|$\le1000$|$\le50$|$\le10$|$=0$|$=0$|$=0$|$=4$|$4$|
|$7$|无限制|$\le1000$|$\le50$|$\le10$|$=0$|$=0$|$=0$|$=0$|$3,5,6$|
|$8$|无限制|无限制|$\le1000$|$\le60$|$\le10$|$=0$|$=0$|$=2$|$4$|
|$9$|无限制|无限制|$\le1000$|$\le60$|$\le10$|$=0$|$=0$|$=3$|$5$|
|$10$|无限制|无限制|$\le1000$|$\le60$|$\le10$|$=0$|$=0$|$=4$|$6,8$|
|$11$|无限制|无限制|$\le1000$|$\le60$|$\le10$|$=0$|$=0$|$=0$|$7,9,10$|
|$12$|无限制|无限制|无限制|$\le300$|$\le30$|$\le10$|$=0$|$=2$|$8$|
|$13$|无限制|无限制|无限制|$\le300$|$\le30$|$\le10$|$=0$|$=3$|$9$|
|$14$|无限制|无限制|无限制|$\le300$|$\le30$|$\le10$|$=0$|$=4$|$10,12$|
|$15$|无限制|无限制|无限制|$\le300$|$\le30$|$\le10$|$=0$|$=0$|$11,13,14$|
|$16$|无限制|无限制|无限制|$\le500$|$\le60$|$\le20$|$\le10$|$=1$|无|
|$17$|无限制|无限制|无限制|$\le500$|$\le60$|$\le20$|$\le10$|$=2$|$12$|
|$18$|无限制|无限制|无限制|$\le500$|$\le60$|$\le20$|$\le10$|$=3$|$13,16$|
|$19$|无限制|无限制|无限制|$\le500$|$\le60$|$\le20$|$\le10$|$=4$|$14,16,17$|
|$20$|无限制|无限制|无限制|$\le500$|$\le60$|$\le20$|$\le10$|$=0$|$15,18,19$|

接下来阐述关于 $o$ 的特殊性质。
* $o=0$ 时，不保证特殊性质。
* $o=1$ 时，保证输入中 $w=0$。
* $o=2$ 时，保证输入中 $w=2$。
* $o=3$ 时，保证输入中 $w=0$ 或 $w=1$。
* $o=4$ 时，保证输入中 $w=0$ 或 $w=2$。

接下来阐述是否输出方案对答案带来的影响。
* 如果选择了 $c=0$，则答案正确时，你将获得该测试点 $80\%$ 的分数，否则该测试点不得分。
* 如果选择了 $c=1$，则答案和构造方案**均正确**时，你将获得该测试点的全部分数，**否则该测试点不得分**。

因此如果你的输出方案可能写错，请慎重考虑是否改为不输出方案。

接下来介绍 `checker.cpp` 使用方法。

`checker.cpp` 使用类似于 Testlib 的命令行格式，但是并不基于 Testlib，因此**不需要 `testlib.h` 文件**；同时**兼容 Lemon 格式**。具体的，你可以这么使用：

打开终端，进入 `checker.cpp` 所在文件夹后，首先使用 `g++ checker.cpp -o checker` 命令生成可执行文件（需要本地默认采用 C++11 及以上标准）。

假设输入文件为 `data.in`，输出文件为 `data.out`，标准答案文件为 `data.ans`，则你需要将可执行文件 `checker` 和 `data.in/out/ans` 文件放置于同一文件夹下，然后在终端中输入如下命令执行：
* 如果你使用 Windows 操作系统，请在 cmd 中使用 `checker data.in data.out data.ans 5` 执行。
* 如果你使用 Linux 操作系统，请在 bash 中使用 `./checker data.in data.out data.ans 5` 执行。

如命令中去掉最后的这个 `5` 将认为 $c=0$ 时也为 AC。

稍等片刻即会返回提示信息。

如果你使用 Lemon 来进行本地评测，可以把 `checker.cpp` 的可执行文件直接作为 Lemon 中的「自定义校验器」使用。

#### 后记

透过指缝观看着那世界末日之景。对立咽了口口水，靠着那股不知名的勇气，将手从自己的脸上移开。

对立伸出了手，把那世界尽头收入了自己所搜集的无数回忆之中。

其余的悲惨记忆，在这枚残片的映衬下显得不足一提。

对立确信自己已经变得足够强大，理所当然地想立刻把一切都摧毁。

就这样，伴随着那抹真诚的微笑与疲惫的笑声，对立从天空中降落到了地面上。

那座古老的塔楼在这般力量驱使下逐渐陨落。

而对立则怀抱着英雄般的信念，坚定不移地迈步向前。




---

---
title: "[GCJ 2021 Finals] Infinitree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13047
tag: ['2021', '矩阵加速', '最近公共祖先 LCA', 'Google Code Jam']
---
# [GCJ 2021 Finals] Infinitree
## 题目描述

This problem is about finding the distance between two nodes of a strictly binary tree. Oh, is that too easy?! Ok, the tree is potentially infinite now. Keep it up and we will start going up the aleph numbers.

In this problem, a tree is either a single node $X$, or a node $X$ with two trees attached to it: a left subtree and a right subtree. In both cases, $X$ is the root of the tree. If the tree is not a single node, the roots of both the left and right subtrees are the only children of $X$.

There is a set of colors numbered from 0 to $\mathbf{N}$, inclusive. Each node is of exactly one color. There might be zero, one, or multiple nodes of each color. Each node of color 0 (white) is a leaf node (that is, it has no children). Each node of color $i$, for $1 \leq i \leq \mathbf{N}$, has exactly 2 children: the left one is color $\mathbf{L}_{i}$ and the right one is color $\mathbf{R}_{i}$. The root of the tree is color 1 (black). Note that the tree may have a finite or countably infinite number of nodes.

For example, the following picture illustrates a finite tree defined by the lists $\mathbf{L}=[3,0,0]$ and $\mathbf{R}=[2,0,2]$. Color 2 is blue and color 3 is yellow.

![](https://cdn.luogu.com.cn/upload/image_hosting/sj19pjad.png)

The distance between two nodes in the tree is the minimum number of steps that are needed to get from one node to the other. A step is a move from a node to its direct parent or its direct child.

Nodes in the tree are indexed using positive integers. The root has index $1$. Then, other nodes are indexed using consecutive integers, with nodes with smaller distances to the root being indexed first. For nodes that are equidistant to the root, nodes that are further to the left are indexed first. For example, the following picture adds indices to each node in the tree we presented before. Notice that each node's index is independent from its color.

![](https://cdn.luogu.com.cn/upload/image_hosting/nx04usnw.png)

As another example, the following picture shows the first $33$ nodes of an infinite tree defined by the lists $\mathbf{L}=[3,4,2,4]$ and $\mathbf{R}=[2,2,4,0]$. Color $4$ is green.

![](https://cdn.luogu.com.cn/upload/image_hosting/zc3569sp.png)

Given the lists $\mathbf{L}$ and $\mathbf{R}$ that define a tree and the indices of two different nodes in the tree, return the distance between those two nodes.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of three lines. The first line contains $\mathbf{N}$, $\mathbf{A}$, and $\mathbf{B}$: the size of the lists that define the tree, and the indices of the two nodes whose distance you need to calculate, respectively. The second line contains $\mathbf{N}$ integers $\mathbf{L}_{1}$, $\mathbf{L}_{2}$, $\ldots$, $\mathbf{L}_{\mathbf{N}}$ and the third line contains $\mathbf{N}$ integers $\mathbf{R}_{1}$, $\mathbf{R}_{2}$, $\ldots$, $\mathbf{R}_{\mathbf{N}}$, as described above.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the distance between the nodes with indices $\mathbf{A}$ and $\mathbf{B}$ in the tree defined by the lists $\mathbf{L}$ and $\mathbf{R}$.
## 样例

### 样例输入 #1
```
5
3 1 8
3 0 0
2 0 2
3 1 5
3 0 0
2 0 2
4 1 27
3 4 2 4
2 2 4 0
4 1 28
3 4 2 4
2 2 4 0
3 1 10
1 3 1
3 2 1
```
### 样例输出 #1
```
Case #1: 3
Case #2: 2
Case #3: 4
Case #4: 5
Case #5: 3
```
### 样例输入 #2
```
4
3 5 7
3 0 0
2 0 2
3 4 9
3 0 0
2 0 2
4 11 18
3 4 2 4
2 2 4 0
4 21 22
3 4 2 4
2 2 4 0
```
### 样例输出 #2
```
Case #1: 4
Case #2: 3
Case #3: 5
Case #4: 8
```
## 提示

**Sample Explanation**

The tree in Sample Cases #1 and #2 is the first tree shown in the statement. The tree in Sample Cases #3 and #4 is the last tree shown in the statement. The same is true for the additional samples below. In Sample Case #5, notice that some colors may not be present in the tree.

Sample Test Set 2 fits the limits of Test Set 2. It will not be run against your submitted solutions.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{N} \leq 50$.
- $0 \leq \mathbf{L}_{i} \leq \mathbf{N}$.
- $0 \leq \mathbf{R}_{i} \leq \mathbf{N}$.
- $\mathbf{A} < \mathbf{B} \leq 10^{18}$.
- The tree defined by $\mathbf{L}$ and $\mathbf{R}$ has at least $\mathbf{B}$ nodes.

**Test Set 1 (25 Pts, Visible Verdict)**

- $\mathbf{A} = 1$.

**Test Set 2 (40 Pts, Hidden Verdict)**

- $1 \leq \mathbf{A} \leq 10^{18}$.


---

---
title: "[GCJ 2020 #2] Emacs++"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13065
tag: ['2020', '最短路', '最近公共祖先 LCA', 'Google Code Jam']
---
# [GCJ 2020 #2] Emacs++
## 题目描述

In 2016's Distributed Code Jam, we introduced the Lisp++ language for Lisp fans who prefer a higher density of parentheses. Here is a reminder of how the language's syntax works:

A Lisp++ program is a string of balanced parentheses. More formally, a Lisp++ program consists of one of the following. (In this specification, C stands for some program code — not necessarily the same code each time.)

- `()` Literally, just an opening parenthesis and a closing parenthesis. We say that this `(` matches this `)`, and vice versa.
- `(C)` A program within a pair of enclosing parentheses. We say that this `(` matches this `)`, and vice versa.
- `CC` Two programs (not necessarily the same), back to back.

This year, we are pleased to announce Emacs++, a text viewer for Lisp++. Emacs++ displays a Lisp++ program of length K as a single long line with a cursor that you can move around. The cursor is a "block cursor" that is always located on one of the K characters in the program, rather than between characters.

At any point, you can perform one of the following three actions to move the cursor. (i represents the current position of the cursor, counting starting from 1 for the leftmost position.)

- Move the cursor one character to the left (or, if the cursor is already on the leftmost character, does nothing). This takes $L_i$ seconds.
- Move the cursor one character to the right (or, if the cursor is already on the rightmost character, does nothing). This takes $R_i$ seconds.
- Teleport the cursor to the parenthesis matching (as described above) the parenthesis that is the i-th character. This takes $P_i$ seconds.

We think Emacs++ will be simple for power users, but we still need to understand how efficient it is. We have a single Lisp++ program and list of Q queries about that program; each query consists of a start position $S_j$ and an end position $E_j$. To answer the j-th query, you must determine the smallest possible amount of time $N_j$ (in seconds) that it will take to take the cursor from position $S_j$ to position $E_j$, if you make optimal decisions.

Please output the sum of all of those $N_j$ values.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. The first line of a test case contains two integers $K$, which is the length of the Lisp++ program, and $Q$, which is the number of queries.

The second line of a test case contains a string $P$ of $K$ characters, each of which is either ( or ), representing a Lisp++ program (string of balanced parentheses), as described above.

The third, fourth, and fifth lines of a test case each contain $K$ integers. The $i$-th integers in these lines are the values $L_i$, $R_i$, and $P_i$, respectively, that are described above.

The sixth and seventh lines of a test case each contain $Q$ integers. The $j$-th integers in these lines are $S_j$ and $E_j$, respectively, that are described above.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the sum of the $N_j$ values that are described above.
## 样例

### 样例输入 #1
```
1
12 5
(()(((()))))
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
7 4 4 12 5
12 11 10 1 6
```
### 样例输出 #1
```
Case #1: 10
```
## 提示

**Sample Explanation**

In the sample case, which obeys the limits for Test Set 1, all of the time costs are the same ($1$ second per move). The shortest times for the queries are as follows:

1. Move right from $7$ five times to $12$ taking $5$ seconds.
2. Teleport from $4$ to $11$ taking $1$ second.
3. Teleport from $4$ to $11$, then move left to $10$ taking $2$ seconds.
4. Teleport from $12$ to $1$, taking $1$ second.
5. Move right from $5$ to $6$ taking $1$ second.

Thus, the sum of query times is $5+1+2+1+1 = 10$ seconds.

**Limits**

- $1 \leq T \leq 100$.
- $K = 10^5$ and $Q = 10^5$, for at most 9 test cases.
- $2 \leq K \leq 1000$ and $1 \leq Q \leq 1000$, in all other cases.
- length of $P = K$ $P$ is a string of balanced parentheses, as described above.
- $1 \leq S_j \leq K$, for all $j$.
- $1 \leq E_j \leq K$, for all $j$.

**Test Set 1 (12 Pts, Visible Verdict)**

- $L_i = 1$, for all $i$.
- $R_i = 1$, for all $i$.
- $P_i = 1$, for all $i$.

**Test Set 2 (23 Pts, Hidden Verdict)**

- $1 \leq L_i \leq 10^6$, for all $i$.
- $1 \leq R_i \leq 10^6$, for all $i$.
- $1 \leq P_i \leq 10^6$, for all $i$.


---

---
title: "[NOI2006] 网络收费"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4297
tag: ['2006', 'NOI', 'O2优化', '最近公共祖先 LCA', '状压 DP']
---
# [NOI2006] 网络收费
## 题目背景

noi2006 day1t1

## 题目描述

网络已经成为当今世界不可或缺的一部分。每天都有数以亿计的人使用网络进行学习、科研、娱乐等活动。然而，不可忽视的一点就是网络本身有着庞大的运行费用。所以，向使用网络的人进行适当的收费是必须的，也是合理的。

MY 市NS 中学就有着这样一个教育网络。网络中的用户一共有$2^N$个，编号依次为1, 2, 3, …, $2^N$。这些用户之间是用路由点和网线组成的。用户、路由点与网线共同构成一个满二叉树结构。树中的每一个叶子结点都是一个用户，每一个非叶子结点（灰色）都是一个路由点，而每一条边都是一条网线（见下图，用户结点中的数字为其编号）。

 ![](https://cdn.luogu.com.cn/upload/pic/12807.png) 

MY 网络公司的网络收费方式比较奇特，称为“ 配对收费 ”。即对于每两个用户$i, j (1≤i < j ≤2^N )$ 进行收费。由于用户可以自行选择两种付费方式A、B中的一种，所以网络公司向学校收取的费用与每一位用户的付费方式有关。该费用等于每两位不同用户配对产生费用之和。

为了描述方便，首先定义这棵网络树上的一些概念：

- 祖先：根结点没有祖先，非根结点的祖先包括它的父亲以及它的父亲的祖先；
- 管辖叶结点：叶结点本身不管辖任何叶结点，非叶结点管辖它的左儿子所管辖的叶结点与它的右儿子所管辖的叶结点；
- 距离：在树上连接两个点之间的用边最少的路径所含的边数。

对于任两个用户$i, j (1≤i<j≤2^N )$，首先在树上找到与它们距离最近的公共祖先：路由点$P$，然后观察$P$ 所管辖的叶结点（即用户）中选择付费方式A 与B的人数，分别记为$n_A$ 与$n_B$，接着按照网络管理条例第X 章第Y 条第Z 款进行收费（如下表），其中$F_{i,j}$ 为$i$ 和$j$ 之间的流量，且为已知量。

 ![](https://cdn.luogu.com.cn/upload/pic/12809.png) 

由于最终所付费用与付费方式有关，所以NS 中学的用户希望能够自行改变自己的付费方式以减少总付费。然而，由于网络公司已经将每个用户注册时所选择的付费方式记录在案，所以对于用户$i$，如果他/她想改变付费方式（由A 改为B 或由B 改为A），就必须支付$C_i$ 元给网络公司以修改档案（修改付费方式记录）。

现在的问题是，给定每个用户注册时所选择的付费方式以及$C_i$，试求这些用户应该如何选择自己的付费方式以使得NS 中学支付给网络公司的总费用最少（更改付费方式费用+配对收费的费用）。

## 输入格式

输入文件中第一行有一个正整数N。

第二行有$2^N$ 个整数，依次表示$1$ 号，$2$ 号，…，$2^N$ 号用户注册时的付费方式，每一个数字若为`0`，则表示对应用户的初始付费方式为A，否则该数字为`1`，表示付费方式为B。

第三行有$2^N$ 个整数，表示每一个用户修改付费方式需要支付的费用，依次为$C_1$, $C_2$, …,$C_M$。( M=$2^N$ )

以下 $2^N$-1 行描述给定的两两用户之间的流量表F，总第(i + 3)行第j 列的整数为$F_{i, j+i}$ 。（1≤i<$2^N$，1≤j≤$2^N$ – i）

所有变量的含义可以参见题目描述。

## 输出格式

你的程序只需要向输出文件输出一个整数，表示NS 中学支付给网络公司的最小总费用。（单位：元）

## 样例

### 样例输入 #1
```
2
1 0 1 0
2 2 10 9
10 1 2
2 1
3
```
### 样例输出 #1
```
8
```
## 提示

【样例说明】

将 1 号用户的付费方式由B 改为A，NS 中学支付给网络公司的费用达到最小。

【数据范围】

40%的数据中$N≤4$；  
80%的数据中$N≤7$；  
100%的数据中$N≤10$，$0≤F_{i, j}≤500$，$0≤C_i≤500 000$。



---

---
title: "[CTSC2018] 暴力写挂"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4565
tag: ['2018', '线段树', 'O2优化', '分治', '最近公共祖先 LCA', 'CTSC/CTS']
---
# [CTSC2018] 暴力写挂
## 题目描述

temporaryDO 是一个很菜的 OIer。在 4 月，他在省队选拔赛的考场上见到了《林克卡特树》一题，其中 $k = 0$ 的部分分是求树 $T$ 上的最长链。可怜的 temporaryDO 并不会做这道题，他在考场上抓猫耳挠猫腮都想不出一点思路。

这时，善良的板板出现在了空中，他的身上发出璀璨却柔和的光芒，荡漾在考场上。“题目并不难。” 板板说。那充满磁性的声音，让 temporaryDO 全身充满了力量。

他决定：写一个枚举点对求 LCA 算距离的 $k = 0$ 的 $O(n^2 \log n)$ 的部分分程序！于是， temporaryDO 选择以 $1$ 为根，建立了求 LCA 的树链剖分结构，然后写了二重 for 循环枚举点对。

然而，菜菜的 temporaryDO 不小心开小了数组，于是数组越界到了一片神秘的内存区域。但恰好的是，那片内存区域存储的区域恰好是另一棵树 $T'$ 。这样一来，程序并没有 RE ，但他求 $x$ 和 $y$ 的距离的时候，计算的是 

$$ \mathrm{depth}(x) + \mathrm{depth}(y) -  ({\mathrm{depth}(\mathrm{LCA}(x,y))}+{\mathrm{depth'}(\mathrm{LCA'}(x,y))})$$



最后程序会输出每一对点对 $i, j$（$i \le j$） 的如上定义的“距离” 的最大值。
temporaryDO 的程序在评测时光荣地爆零了。但他并不服气，他决定花好几天把自己的程序跑出来。请你根据 $T$ 和 $T'$ 帮帮可怜的 temporaryDO 求出他程序的输出。
## 输入格式

第一行包含一个整数 $n$ ，表示树上的节点个数。

第 $2$ 到第 $n$ 行，每行三个整数 $x , y , v$ ，表示 $T$ 中存在一条从 $x$ 到 $y$ 的边，其长度为 $v$。

第 $n + 1$ 到第 $2n-1$ 行 ，每行三个整数 $x , y , v$ ，表示 $T'$ 中存在一条从 $x$ 到 $y$ 的边，其长度为 $v$。
## 输出格式

输出一行一个整数，表示 temporaryDO 的程序的输出。

## 样例

### 样例输入 #1
```
6
1 2 2
1 3 0
2 4 1
2 5 -7
3 6 0
1 2 -1
2 3 -1
2 5 3
2 6 -2
3 4 8
```
### 样例输出 #1
```
5

```
## 提示

### 样例解释 1
点对 $(3, 4)$ 的距离计算为 $3 + 0 - (0 + (-2)) = 5$ 。

### 数据范围
对于所有数据， $1\le n \le 366666$，$|v| \le 2017011328$ 。 详细数据范围见下表，表格中的“无” 表示无特殊限制。

测试点编号|$n \le$|$v$|$T$ 是一条链|$T'$ 是一条链
-|-|-|-|-
$1$|$36$|$=1$|否|否
$2$|$366$|$=1$|否|否
$3$|$1388$|$>0$|否|否
$4$|$1999$|$>0$|否|否
$5$|$2666$|$>0$|否|否
$6$|$5666$|无|否|否
$7$|$8666$|无|否|否
$8$|$11111$|无|否|否
$9$|$12345$|无|否|否
$10$|$366666$|$>0$|是|是
$11$|$366666$|无|是|是
$12\sim 13$|$366666$|$>0$|是|否
$14$|$366666$|无|是|否
$15\sim 16$|$366666$|$>0$|否|是
$17$|$366666$|无|否|是
$18\sim 20$|$366666$|无|否|否

$\mathrm{depth}(p)$ 和 $\mathrm{depth'}(p)$ 分别表示树 $T$，$T'$ 中点 $1$ 到点 $p$ 的距离，这里规定，距离指的是经过的边的边权总和，其中 $\mathrm{depth}(1) = 0$。

$\mathrm{LCA}(x, y)$ 和 $\mathrm{LCA'}(x, y)$ 分别表示树 $T$，$T'$ 中点 $x$ 与点 $y$ 的最近公共祖先，即在从 $x$ 到 $y$ 的最短路径上的距离根**经过边数最少**的点。


---

---
title: "[NOI2018] 情报中心"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4775
tag: ['2018', '线段树', 'NOI', 'O2优化', '最近公共祖先 LCA']
---
# [NOI2018] 情报中心
## 题目描述

C 国和 D 国近年来战火纷飞。

最近，C 国成功地渗透进入了 D 国的一个城市。这个城市可以抽象成一张有 $n$ 个节点，节点之间由 $n − 1$ 条双向的边连接的无向图，使得任意两个点之间可以互相到达。也就是说，这张无向图实际上是一棵树。

经过侦查，C 国情报部部长 GGB 惊讶地发现，这座看起来不起眼的城市竟然是 D 国的军事中心。因此 GGB 决定在这个城市内设立情报机构。情报专家 TAC 在侦查后，安排了 $m$ 种设立情报机构的方案。这些方案中，第 $i$ 种方案是在节点 $x_i$ 到节点 $y_i$ 的最短路径的所有边上安排情报人员收集情报，这种方案需要花费 $v_i$ 元的代价。

但是，由于人手不足，GGB 只能安排上述 $m$ 种方案中的两种进行实施。同时 TAC 指出，为了让这两个情报机构可以更好的合作，它们收集情报的范围应**至少有一条公共的边**。为了评估一种方案的性能，GGB 和 TAC 对所有的边进行了勘察，给每一条边制定了一个情报价值 $c_i$，表示收集这条边上的情报能够带来 $c_i$ 元的收益。注意，情报是唯一的，因此当一条边的情报被两个情报机构收集时，也同样只会有 $c_i$ 的收益。

现在，请你帮 GGB 选出两种合法的设立情报机构的方案进行实施，使得这两种方案收集情报的范围至少有一条公共的边，并且在此基础上**总收益减去总代价的差**最大。

注意，这个值可能是负的，但仍然是合法的。如果无法找到这样的两种方案，请输出 `F`。

## 输入格式

从文件 `center.in` 中读入数据。

本题包含多组测试数据。

输入文件的第一行包含一个整数 $T$，表示数据组数；

每组数据包含 $(n + m + 1)$ 行：

第 $1$ 行包含一个整数 $n$，表示城市的点数；

第 $2$ 到第 $n$ 行中，第 $(i + 1)$ 行包含三个整数 $a_i$，$b_i$，$c_i$，表示城市中一条连接节点 $a_i$ 和 $b_i$、情报价值为 $c_i$ 的双向边，保证 $a_i < b_i$ 且 $b_i$ 互不相同；

第 $(n + 1)$ 行包含一个整数 $m$，表示 TAC 设立的 $m$ 种设立情报机构的方案；

第 $(n + 2)$ 到 $(n + m + 1)$ 行中，第 $(n + i + 1)$ 行包含三个整数 $x_i$，$y_i$，$v_i$，表示第 $i$ 种设立情报机构的方案是在节点 $x_i$ 到节点 $y_i$ 的最短路径上的所有边上安排情报人员收集情报，并且需要花费 $v_i$ 元的代价。
## 输出格式

输出到文件 `center.out` 中。

输出文件包含 $T$ 行；

对于每组数据，输出一行：如果存在合法的方案，则输出一个整数表示最大的总收益减去总代价的差；否则输出 `F`。

## 样例

### 样例输入 #1
```
2
5
1 2 1
2 3 3
3 4 2
1 5 8
2
1 4 5
3 5 8
5
1 2 1
2 3 3
3 4 3
1 5 9
2
1 5 5
2 3 8
```
### 样例输出 #1
```
1
F
```
### 样例输入 #2
```
1
11
1 2 2
1 3 0
2 4 1
3 5 7
1 6 0
1 7 1
1 8 1
6 9 3
4 10 2
4 11 8
10
7 10 2
10 7 0
2 11 1
8 6 7
7 7 0
10 1 1
8 2 1
7 8 3
7 7 3
3 9 9

```
### 样例输出 #2
```
13

```
## 提示

### 样例 1 解释

这个样例中包含两组数据。这两组数据的城市相同，只是在情报的价值和情报机构的方案上有所不同。城市地图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/mfs5k9ob.png)

* 对于第一组数据，方案一中的节点 $1$ 到节点 $4$ 的最短路径为 $1 \rightarrow 2 \rightarrow 3 \rightarrow 4$，方案二中的节点 $3$ 到节点 $5$ 的最短路径为 $3 \rightarrow 2 \rightarrow 1 \rightarrow 5$。选择这两种方案需要花费 $5 + 8 = 13$ 的代价，并且每一条边的情报都被收集从而得到 $1 + 3 + 2 + 8 = 14$ 的收益，因此总收益减去总代价为 $14 − 13 = 1$。
* 对于第二组数据，方案一中的节点 $1$ 到节点 $5$ 的最短路径为 $1 \rightarrow 5$，方案二中的节点 $2$ 到节点 $3$ 的最短路径为 $2 \rightarrow 3$。这两种方案收集情报的范围没有公共的边，因此非法，所以这组数据不存在合法方案，应输出 `F`。

### 样例 2 解释

见附加文件中的 `center2.in` 与 `center2.ans`。

这个样例只包含一组数据。这一数据中，最优方案为选择第 $2$ 种和第 $3$ 种方案。

这组数据的城市地图如下，其中**加粗**的边表示被情报中心收集情报的边，红色的边表示只被第 $2$ 种方案的情报中心收集情报的边，蓝色的边表示只被第 $3$ 种方案的情报中心收集情报的边，紫色的边表示同时被两个情报中心收集情报的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/s9blcjri.png)

### 样例 3

见附加文件中的 `center3.in` 与 `center3.ans`。

这个样例和第 $4$ 个测试点的性质相同。每个测试点的性质见下文的表格。

### 样例 4

见附加文件中的 `center4.in` 与 `center4.ans`。

这个样例，无疑是善良的出题人无私的馈赠。大量精心构造的 $n\le 100,m\le 200$ 的测试数据，涵盖了测试点中所有出现性质的组合。你可以利用这个测试点，对自己的程序进行全面的检查。足量的数据组数、不大的数据范围和多种多样的数据类型，能让程序中的错误无处遁形。出题人相信，这个美妙的样例，可以给拼搏于 AC 这道题的逐梦之路上的你，提供一个有力的援助。

### 数据范围

各测试点的数据规模和性质如下表：

| 测试点 | $n \le$ | $m \le$ | $T \le 50$ | 特殊性质 |
| :-: | :-: | :-: | :-: | :-: |
| 1 | $2$ | $3$ | 保证 | 无 |
| 2 | $10$ | $30$ | 保证 | 无 |
| 3 | $200$ | $300$ | 保证 | 无 |
| 4 | $10^3$ | $2,000$ | 保证 | $a_i = b_i - 1$ |
| 5 | $10^4$ | $3 \times 10^4$ | 保证 | $a_i = b_i - 1$ |
| 6 | $5 \times 10^4$ | $3 \times 10^4$ | 保证 | $a_i = b_i - 1$ |
| 7 | $10^4$ | $3 \times 10^4$ | 保证 | $c_i=0$ |
| 8 | $5 \times 10^4$ | $10^5$ | 保证 | $c_i=0$ |
| 9 | $5 \times 10^4$ | $10^5$ | 保证 | $c_i=0$ |
| 10 | $10^4$ | $n$ | 保证 | $S_1$ |
| 11 | $5 \times 10^4$ | $n$ | 不保证 | $S_1$ |
| 12 | $5 \times 10^4$ | $n$ | 不保证 | $S_1$ |
| 13 | $10^4$ | $3 \times 10^4$ | 保证 | $S_2$ |
| 14 | $10^4$ | $3 \times 10^4$ | 保证 | $S_2$ |
| 15 | $5 \times 10^4$ | $10^5$ | 不保证 | $S_2$ |
| 16 | $5 \times 10^4$ | $10^5$ | 不保证 | $S_2$ |
| 17 | $10^4$ | $3 \times 10^4$ | 保证 | 无 |
| 18 | $5 \times 10^4$ | $ 10^5$ | 保证 | 无 |
| 19 | $5 \times 10^4$ | $ 10^5$ | 不保证 | 无 |
| 20 | $5 \times 10^4$ | $ 10^5$ | 不保证 | 无 |

表格中的特殊性质如下：
* 特殊性质 $S_1$：对于任意 $i, j$，保证 $x_i$ 到 $y_i$ 的最短路径所经过的编号最小的节点不同于 $x_j$ 到 $y_j$ 的最短路径所经过的编号最小的节点；

* 特殊性质 $S_2$：对于任意 $i$，保证 $x_i$ 到 $y_i$ 的最短路径所经过的编号最小的节点为节点 $1$。

对于所有的数据，$1 \le n \le 5 \times 10^4$，$0 \le m \le 10^5$，$0 \le c_i \le 10^9$，$0 \le v_i \le 10^{10} \times n$。每个测试点中，所有 $n$ 的和不会超过 $1\,000\,233$，所有 $m$ 的和不会超过 $2\,000\,233$。



---

