---
title: "切木棍 Cutting Sticks"
layout: "post"
diff: 普及+/提高
pid: UVA10003
tag: ['搜索', '记忆化搜索']
---

# 切木棍 Cutting Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=944

[PDF](https://uva.onlinejudge.org/external/100/p10003.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10003/958525065661f78575790c5f6aa2ffbee907fc0b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10003/e46a5b9b0f145857448142f8f46dfaa75e9f6e02.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10003/c84a21fce404c85a1c20be6e70d4c5e2aac71537.png)

## 样例 #1

### 输入

```
100
3
25 50 75
10
4
4 5 7 8
0
```

### 输出

```
The minimum cutting is 200.
The minimum cutting is 22.
```



---

---
title: "倒水问题 Fill"
layout: "post"
diff: 普及+/提高
pid: UVA10603
tag: ['搜索', '优先队列', '最短路']
---

# 倒水问题 Fill

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1544

[PDF](https://uva.onlinejudge.org/external/106/p10603.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/2d3a044bd29738a849110d68bb92f13a9aef7016.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/0432604430c8dd3aff84cb657eb403f61d1750f6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/ed317ca6c29f5bac166d1f6428122bcd61d81d18.png)

## 样例 #1

### 输入

```
2
2 3 4 2
96 97 199 62
```

### 输出

```
2 2
9859 62
```



---

---
title: "Seven Seas"
layout: "post"
diff: 普及+/提高
pid: UVA10923
tag: ['搜索']
---

# Seven Seas

## 题目描述

Seven Seas 是一个很棒的游戏。在游戏中，你是一艘战舰的舰长。你身处茫茫大海之中，有一些敌舰试图追上你。你的任务是逃脱并尽你所能地摧毁敌舰。  
游戏在一个 $9 \times 8$ 的地图中进行，你可以向八个方向移动，每次移动一步。你先移动，然后敌舰移动。这些敌舰非常愚蠢，他们总是会移动到离你最近的位置，即使这个位置会摧毁他们的战舰。当一艘战舰移动到一个有岩石的位置就会被摧毁。如果两艘战舰移动到同一个位置，它们都会被摧毁，它们的残骸将会遗留在那个位置，所以如果另一艘战舰再移动到这个位置也会被摧毁。如果敌舰接触到你的战舰，你将会死亡，游戏结束。

## 输入格式

**本题有多组数据**。   
第一行为数据组数。每组数据都是 $9 \times 8$ 的地图。S 表示你的战舰，E 表示敌舰，# 表示岩石，. 表示大海。两组数据之间有一行空行。

## 输出格式

对于每一组数据，如果在10步之内可以将敌舰全部摧毁，输出 `I'm the king of the Seven Seas!`；否则输出 `Oh no! I'm a dead man!`。

## 样例 #1

### 输入

```
3
........
.E.#....
...E....
..#.....
........
........
..S.....
........
........
........
.E.E....
...S....
.E..E...
........
........
........
........
........
E......#
........
........
........
........
........
........
.......S
#.......
```

### 输出

```
I’m the king of the Seven Seas!
Oh no! I’m a dead man!
Oh no! I’m a dead man!
```



---

---
title: "Robots on Ice"
layout: "post"
diff: 普及+/提高
pid: UVA1098
tag: ['搜索', '剪枝']
---

# Robots on Ice

## 题目描述

受哈尔滨冰雕的启发，来自北极机器人与自动机大学的参赛队员决定程序竞赛结束后在校园内举办自己的冰雪节。他们打算在冬天结冰的时候，从学校附近的一个湖里获取冰块。为了便于监测湖中冰层的厚度，他们先将湖面网格化，然后安置一个轻巧的机器人逐个方格测量冰层的厚度。在网格中有三个特殊方格被指定为“检查点”，对应着机器人在检查过程中经过整个行程的四分之一、二分之一、四分之三的位置，机器人在这三个特殊“检查点”会发送相应的进度报告。为了避免对冰面造成不必要的磨损和划痕而影响后续的使用，机器人需要从网格左下角坐标为 $(0，0)$ 的方格出发，经过所有方格仅且一次，然后返回位于坐标为 $(0，1)$ 的方格。如果有多种路线符合要求，则机器人每天会使用一条不同的路线。机器人只能沿北、南、东、西四个方向每次移动一个方格。  
给定网格的大小和三个检查点的位置，编写程序确定有多少种不同的检查路线。例如，湖面被划分为 $3 \times 6$ 的网格，三个检查点按访问的顺序分别为 $(2，1)，(2，4)$ 和 $(0，4)$，机器人必须从 $(0，0)$ 方格开始，路经 $18$ 个方格，最后终止于 $(0，1)$ 方格。机器人必须在第 $4（＝\left\lfloor\dfrac{18}{4}\right\rfloor）$ 步的时候经过 $(2，1)$ 方格，在第 $9（＝\left\lfloor\dfrac{18}{2}\right\rfloor）$ 步的时候经过 $(2，4)$ 方格，第 $13（＝\left\lfloor\dfrac{3 \times 18}{4}\right\rfloor）$ 步的时候经过 $(0，4)$ 方格，只有两种路线符合要求，如下图所示。  
![UVA1098 Robots on Ice](https://cdn.luogu.com.cn/upload/image_hosting/vy6tphyl.png)  
需要注意：（1）当网格的大小不是 $4$ 的倍数时，在计算步数时使用整除；（2）某些情况下可能不存在符合要求的路线，例如给定一个 $4 \times 3$的网格，三个检查点分别为 $(2，0)，(3，2)$ 和 $(0，2)$，那么将不存在从 $(0，0)$ 方格出发，结束于 $(0，1)$ 方格且满足要求的路线。

## 输入格式

**本题有多组数据**。  
每组测试数据的第一行包含两个整数 $m$ 和 $n（2 \leq m，n \leq 8）$，表示网格的行数和列数，接着的一行包含六个整数 $r_1，c_1，r_2，c_2，r_3，c_3$，其中 $0 \leq ri ＜ m，0 \leq c_i ＜ n（i＝1，2，3）$。输入的最后一行包含两个 $0$。

## 输出格式

从 $1$ 开始输出测试数据的组数，输出以下不同路线的数量：机器人从行 $0$ 列 $0$ 出发，在行 $0$ 列 $1$ 结束，在第 $\left\lfloor\dfrac{i \times m \times n}{4}\right\rfloor$ 步时经过行 $r_i$ 和列 $c_i（i＝1，2，3）$，能够路经所有方格仅且一次的路线。



---

---
title: "条件概率 Probability|Given"
layout: "post"
diff: 普及+/提高
pid: UVA11181
tag: ['搜索', '递推', '枚举', '深度优先搜索 DFS']
---

# 条件概率 Probability|Given

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2122

[PDF](https://uva.onlinejudge.org/external/111/p11181.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/e7ff179b70470ecd5bcdd2c359c9dec606f308e3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/c4a19b7e08ff7186da01119426d98cce50c64096.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/67d5194f9e66ef7ce5d79ddcd6cfb38fc83c93ca.png)

## 样例 #1

### 输入

```
3 2
0.10
0.20
0.30
5 1
0.10
0.10
0.10
0.10
0.10
0 0
```

### 输出

```
Case 1:
0.413043
0.739130
0.847826
Case 2:
0.200000
0.200000
0.200000
0.200000
0.200000
```



---

---
title: "Full Tank?"
layout: "post"
diff: 普及+/提高
pid: UVA11367
tag: ['广度优先搜索 BFS', '优先队列', '队列']
---

# Full Tank?

## 题目描述

有 $N$ 个城市和 $M$ 条道路，构成一条无向图。

在每个城市都有一个加油站，不同的加油站的价格都不一样。

通过一条道路的油耗就是该道路的边权。

现在你需要回答 $q$ 个问题，在每个问题中，请计算出一辆油箱容量为 $c$ 的，起始时油箱为空的车子，从起点 $s$ 到终点 $e$ 至少要花多少钱。

## 输入格式

第一行两个整数城市数 $N(1 \leq N \leq 1000)$，道路数$M(0 \leq M \leq 10000)$。

接下来 $N$ 个整数为每个城市的油的价格 $p_i(1 \leq p_i \leq 100)$。

接下来 $M$ 行每行三个整数$u,v,d$，描述 $u$ 城市到 $v$ 城市 $(0 \leq u,v < N)$ 有一条油耗为 $d(1 \leq d \leq 100)$ 的道路。

接下来的一个整数 $q(1 \leq q \leq 100)$ 为询问数量。

接下来的 $q$ 行每行三个整数 $c,s,e$。询问一辆容量为 $c$ 的车从 $s$ 城市到 $e$ 城市至少要花多少钱。

题目满足 $1 \leq c \leq 100$。

## 输出格式

对于每个询问，每一行回答一个数，为至少花费的钱。如果不能到达，输出`impossible`。

## 样例 #1

### 输入

```
5 5
10 10 20 12 13
0 1 9
0 2 8
1 2 1
1 3 11
2 3 7
2
10 0 3
20 1 4
```

### 输出

```
170
impossible
```



---

---
title: "Ocean Currents"
layout: "post"
diff: 普及+/提高
pid: UVA11573
tag: ['广度优先搜索 BFS']
---

# Ocean Currents

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2620

[PDF](https://uva.onlinejudge.org/external/115/p11573.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/d1e2b8169cdc10fcb6efb334ec4201d016849d2c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/d920afe01202359d2e8d70a7653121b90d9c46b7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/a0f8203bb0b484bf784b764bfe0ccec8f2b61d46.png)

## 样例 #1

### 输入

```
5 5
04125
03355
64734
72377
02062
3
4 2 4 2
4 5 1 4
5 3 3 4
```

### 输出

```
0
2
1
```



---

---
title: "划分成回文串 Partitioning by Palindromes"
layout: "post"
diff: 普及+/提高
pid: UVA11584
tag: ['字符串', '动态规划 DP', '搜索']
---

# 划分成回文串 Partitioning by Palindromes

## 题目描述

回文子串(palind)

**问题描述：**

当一个字符串正序和反序是完全相同时，我们称之为“回文串”。例如“racecar”就是一个回文串，而“fastcar”就不是。现在给一个字符串s，把它分割成若干个互不相交的回文子串，求分割的回文子串的最少个数。

## 输入格式

第一行为正整数t(≤10)，表示数据组数；接下来t行，每行一个完全由小写字母组成的字符串，长度不超过1000。

## 输出格式

对于每组数据，输出最少回文子串数。

由 @C919 提供翻译

## 样例 #1

### 输入

```
3
racecar
fastcar
aaadbccb
```

### 输出

```
1
7
3
```



---

---
title: "ICPC Team Strategy"
layout: "post"
diff: 普及+/提高
pid: UVA1240
tag: ['动态规划 DP', '搜索', '状态合并']
---

# ICPC Team Strategy

## 题目描述

ICPC（International Collegiate Programming Contest，国际大学生程序设计比赛），就像你所知道的那样，是大学生抱团参加的程序设计比赛。各个团队由 $3$ 个人组成，而他们将会解决一些程序设计问题。

安迪，布迪和坎达拉计划抱团参加 ICPC，至于团队策略，他们仨想到一个简易策略：

+ 在五个小时的比赛的前二十分钟，他们想要读所有的题目，而后他们三个人每个人给每一道题目标一个数字，即某个人 AC 某道题的最小时间，并且一定会 AC。
+ 每个队伍只有一台电脑，因而让一个队伍同时肝两道题是不可能的。
+ 为避免大脑烧毁或心肺骤停（他们比赛过太多次了），他们决定在每道题后交换角色，这样没有人会连续做两道题目。
+ 他们想要尽量多做题目，做题的顺序则无关紧要。

## 输入格式

$T$ 组数据。每组数据开头为整数 $n(1\le n\le 12)$，代表题目数量。第二行 $n$ 个整数 $a_{1\cdots n}(1\le a_i\le 300)$，代表安迪解每到题需要的时间，第三行和第四行分别是布迪和坎达拉解每到题所需的时间。限制同理。

## 输出格式

对于每组数据，输出一个数字，即团队最大可能解出的题目。

### 样例解释

第一组样例：安迪可以单独解出所有的题目，但是安迪不能连续解两道题。

第二组样例：团队可以解出所有的题目：让布迪解第二道题目，让安迪解第一道题目，让布迪解第三道题目，让坎达拉解最后一道题目，需要 $280$ 分钟。

## 样例 #1

### 输入

```
2
3
100 100 80
190 120 90
120 150 100
4
50 20 300 300
200 100 30 250
140 120 100 100
```

### 输出

```
2
4
```



---

---
title: "密码 Password"
layout: "post"
diff: 普及+/提高
pid: UVA1262
tag: ['递归', '枚举', '深度优先搜索 DFS']
---

# 密码 Password

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3703

[PDF](https://uva.onlinejudge.org/external/12/p1262.pdf)



---

---
title: "Exploring Pyramids"
layout: "post"
diff: 普及+/提高
pid: UVA1362
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS', '区间 DP']
---

# Exploring Pyramids

## 题目描述

虽然探索金字塔是极其老套的剧情，但是有一队探险家还是到了某金字塔脚下。

经过多年的研究，科学家对这座金字塔的内部结构已经有所了解。

首先，金字塔由若干房间组成，房间之间连有通道。

如果把房间看作节点，通道看作边的话，整个金字塔呈现一个有根树结构，节点的子树之间有序，金字塔有唯一的一个入口通向树根。

并且，每个房间的墙壁都涂有若干种颜色的一种。

探险队员打算进一步了解金字塔的结构，为此，他们使用了一种特殊设计的机器人。

这种机器人会从入口进入金字塔，之后对金字塔进行深度优先遍历。

机器人每进入一个房间（无论是第一次进入还是返回），都会记录这个房间的颜色。

最后，机器人会从入口退出金字塔。

显然，机器人会访问每个房间至少一次，并且穿越每条通道恰好两次（两个方向各一次）， 然后，机器人会得到一个颜色序列。

但是，探险队员发现这个颜色序列并不能唯一确定金字塔的结构。

现在他们想请你帮助他们计算，对于一个给定的颜色序列，有多少种可能的结构会得到这个序列。

因为结果可能会非常大，你只需要输出答案对 $10^9$ 取模之后的值。

## 输入格式

输入包含多组测试数据。

对于每组测试数据：输入一行，包含一个字符串 $S$，长度不超过 $300$，表示机器人得到的颜色序列。

## 输出格式

对于每组测试数据：输出一行，一个整数表示答案。

## 样例 #1

### 输入

```
ABABABA
AB
```

### 输出

```
5
0
```



---

---
title: "Keyboarding"
layout: "post"
diff: 普及+/提高
pid: UVA1714
tag: ['字符串', '枚举', '广度优先搜索 BFS']
---

# Keyboarding

## 题目描述

## 题目背景

输入一条信息需要敲几下键？或许你会认为它相当于文本中的字符数，但只有在按键与字符一一对应时方才如此。对于小型设备来说，输入文本通常很麻烦。有些设备只提供几个按钮，比字符数量少得多。对于这样的设备，键入一个字符就需要一系列操作。

现在就有一套这样的输入机制：屏幕虚拟键盘，上面有一个光标，可以在键与键来回移动来选择字符。四个箭头按钮控制光标的移动，当光标的位置在合适的虚拟键上时，按确认按钮即可输入相应的字符，且在文本的末尾必须回车。


现在给你一段字符串，并且你只有「上、下、左、右，确认」这五个按钮。本题中，你会得到一个虚拟键盘布局。你的任务是确定键入给定文本所需的最少操作数，按下一个按钮即视为一次操作。虚拟键分布在一个矩形网格中，这样每个虚拟键占用网格中一个或多个相连的单元方格。光标初始均在左上角并可四向移动，且每次都沿该方向移到下一个不同字符的虚拟键。光标不能移动到无效的格上。

每个虚拟键与字符唯一对应，其由一个或多个方格组成，这些方格相连为一块区域。

## 输入格式

**本题有多组数据**。

对于每组数据：

第一行三个整数 $n,m,k$，分别为虚拟键盘网格的行数和列数。

接下来 $r$ 行，每行 $c$ 个字符，为大写字母、数字、横杠或星号（表示回车键）其中之一。

最后一行为一个非空字符串，是要输入的文本，最多有10000个除星号外的有效字符。

## 输出格式

对于每组数据，输出键入整个文本所需的最少操作数，**包括最后按下的回车**。

## 样例

### 样例输入

```text
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB
```

### 样例输出

```text
30
160
19
7
```

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/uvrfluzd.png)

插图描述了一种经过30次操作后输入 `CONTEST` 的方式，红点表示按下该虚拟键。

#### 数据规模

- $1\le r,c\le50,|S|\le 100001\le r,c\le 50,|S|\le 10000$。
---
翻译: @QQzhi (UID:525682)



---

---
title: "小木棍 Sticks"
layout: "post"
diff: 普及+/提高
pid: UVA307
tag: ['搜索', '枚举', '剪枝']
---

# 小木棍 Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=243

[PDF](https://uva.onlinejudge.org/external/3/p307.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/c2647a7ca09eb1b551716900d2c482623b1264d7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/10cd3e738e54e4609c2084fe79f07f05c056540d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/4fe73bdc6626222b0f15df6a62fe404a56935dc3.png)

## 样例 #1

### 输入

```
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0
```

### 输出

```
6
5
```



---

---
title: "树 Tree"
layout: "post"
diff: 普及+/提高
pid: UVA548
tag: ['搜索', '递归', '深度优先搜索 DFS', '构造']
---

# 树 Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=489

[PDF](https://uva.onlinejudge.org/external/5/p548.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/78473d26dddbe5f8314b7aac17e37af6d9c18840.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/d5af82d5dd26aa1f11be5b3e1cfa80708b9d2173.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/235ec8eb49fbab76e59891f6d6b4f6deb21da67a.png)

## 样例 #1

### 输入

```
3 2 1 4 5 7 6
3 1 2 5 6 7 4
7 8 11 3 5 16 12 18
8 3 11 7 16 18 12 5
255
255
```

### 输出

```
1
3
255
```



---

