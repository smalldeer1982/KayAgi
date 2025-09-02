---
title: "The 3n + 1 problem"
layout: "post"
diff: 普及-
pid: UVA100
tag: ['模拟', '数学', '递归']
---

# The 3n + 1 problem

## 题目描述

考虑下面的程序：

1. 输入 $n$

2. 输出 $n$

3. 如果 $n=1$ 退出程序

4. 如果 $n$ 是奇数，$n \rightarrow 3 n + 1$

5. 如果 $n$ 是偶数 $n\rightarrow \dfrac n 2$

6. 回到第 $2$ 步 

若输入 $22$，会得出下面的数列： `22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1`。

我们推测，对于任何输入的正整数 $n$，程序最终都会输出 $1$（$n\le 10^6$ 时，保证推论正确）。 给定 $n$，可以计算这个程序输出的所有数字的数量（包括最后的 $1$）。我们把输出的数字总数称为这个 $n$ 的周期长度。对于上面的例子，周期长度为 $16$。 

对于输入的每对 $(i,j)$，计算 $[i,j]$ 内所有数字区间长度的最大值。

## 输入格式

输入几对整数 $(i,j)$，保证 $0<i,j\le 10^4$。对于每对 $(i,j)$，你需要计算 $[i,j]$ 内最大区间长度。数据保证 $32$ 位整数在计算过程中不溢出。

## 输出格式

对于每对 $(i,j)$，先输出 $i,j$，再输出 $[i,j]$ 范围内最大周期长度，每个数字中间一个空格，然后换行。

## 样例 #1

### 输入

```
1 10
100 200
201 210
900 1000
```

### 输出

```
1 10 20
100 200 125
201 210 89
900 1000 174
```



---

---
title: "卡片游戏 Throwing cards away I"
layout: "post"
diff: 普及-
pid: UVA10935
tag: ['模拟', '队列']
---

# 卡片游戏 Throwing cards away I

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1876

[PDF](https://uva.onlinejudge.org/external/109/p10935.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/04b5bf3f22988460c478d5e0eaad7b24fe43b5d4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/cc097601511901dac24f0e4d66cccd4367d03148.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/87cedea733d4be64fa50b2ae857327019eb4a64d.png)

## 样例 #1

### 输入

```
7
19
10
6
0
```

### 输出

```
Discarded cards: 1, 3, 5, 7, 4, 2
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 4, 8, 12, 16, 2, 10, 18, 14
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 2, 6, 10, 8
Remaining card: 4
Discarded cards: 1, 3, 5, 2, 6
Remaining card: 4
```



---

---
title: "Dragon of Loowater"
layout: "post"
diff: 普及-
pid: UVA11292
tag: ['模拟', '贪心', '排序']
---

# Dragon of Loowater

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/tqycbsg2.png)

从前，在 Loowater 王国，一场小麻烦变成了一个大问题。Loowater 中部的 Rellau 溪岸一直是大雁繁殖的理想之地。由于缺乏天敌，大雁的数量失控。Loowater 的人民大多远离大雁。偶尔会有一只大雁袭击人们，可能会咬掉一两个手指，但总的来说，人民把大雁当作一个小麻烦忍受着。

有一天，一次奇怪的变异发生了，一只大雁产下了一条多头的喷火龙。当这条龙长大后，它威胁要把 Loowater 王国烧成灰烬。Loowater 遇到了一个大问题。国王十分惊恐，召集他的骑士们去屠龙，拯救王国。

骑士们解释道：“要屠龙，我们必须砍下它所有的头。每个骑士只能砍掉龙的一个头。龙的头大小不一。为了砍掉一个头，骑士必须至少和龙头的直径一样高。骑士工会要求，砍掉一个头的骑士必须得到相当于其身高每厘米一枚金币的报酬。”

有足够的骑士来打败这条龙吗？国王召集他的顾问们来帮他决定该雇佣多少骑士以及选择哪些骑士。在花费大量金钱建造米尔公园后，国王想要将屠龙的开支降到最低。作为顾问之一，你的任务是帮助国王。你非常认真地对待这个任务：如果失败了，你和整个王国都将被烧成灰烬！

## 输入格式

输入包含多个测试用例。每个测试用例的第一行包含两个介于 $1$ 和 $20000$ 之间（包括 $1$ 和 $20000$）的整数，分别表示龙的头数 $n$ 和王国中骑士的数量 $m$。接下来的 $n$ 行每行包含一个整数，给出龙头的直径，单位为厘米。接下来的 $m$ 行每行包含一个整数，指定卢沃特骑士的身高，单位为厘米。

输入的最后一个测试用例之后，接着一行 $\texttt{0 0}$ 表示输入结束。

## 输出格式

对于每个测试用例，输出一行，包含国王需要支付的最少金币数量来屠龙。如果卢沃特的骑士无法屠龙，输出 $\texttt{Loowater is doomed!}$。

---

Translated by User 735713.

## 样例 #1

### 输入

```
2 3
5
4
7
8
4
2 1
5
5
10
0 0
```

### 输出

```
11
Loowater is doomed!
```



---

---
title: "Help is needed for Dexter"
layout: "post"
diff: 普及-
pid: UVA11384
tag: ['模拟', '递归']
---

# Help is needed for Dexter

## 题目描述

Dexter 对 Dee Dee 感到厌烦了，所以他决定让 Dee Dee 玩一个游戏来让她忙起来。这个游戏很容易玩，但至少对 Dee Dee 来说不容易赢。但是，Dexter 没有时间浪费在这种无聊的任务上，所以他需要你的帮助。

游戏中有一个按钮，当按下按钮时，电脑将随机选择一个数字 $N$。然后屏幕上会显示从 $1$ 到 $N$ 的数字。Dee Dee 可以从屏幕上的数字中选择任意数量的数字，然后她将命令计算机从所选数字中减去她选择的一个正整数（不一定是屏幕上的数字）。她的目标是让所有数字都变成 $0$。

例如，如果 $N = 3$，屏幕上将显示 $3$ 个数字：$1$、$2$、$3$。假设她现在选择 $1$ 和 $2$，命令计算机减去 $1$，那么屏幕上的数字将变为：$0$、$1$、$3$。然后她选择 $1$ 和 $3$，并命令减去 $1$，现在屏幕上的数字是 $0$、$0$、$2$。最后她选择 $2$ 并减去 $2$，所有数字变为 $0$。

Dexter 并不愚蠢，明白这可以很容易地完成，所以为了增加难度，他将为每个 $N$ 给出一个限制 $L$，并且确保 $L$ 是仍然能在 $L$ 步内完成的最小值。但 Dexter 没有时间去思考如何为每个 $N$ 确定 $L$，因此他请求你编写一个程序，输入 $N$，输出 $L$。

## 输入格式

输入由多行组成，每行包含一个 $N$，其中 $1 \le N \le 10 ^ 9$。输入将由文件末尾终止。

## 输出格式

对于每个 $N$，在单独的一行中输出对应的 $L$。

---

Translated by User 735713.

## 样例 #1

### 输入

```
1
2
3
```

### 输出

```
1
2
2
```



---

---
title: "UVA141 The Spot Game"
layout: "post"
diff: 普及-
pid: UVA141
tag: ['模拟', '字符串']
---

# UVA141 The Spot Game

## 题目背景

有一种叫做 Spot 的游戏，在一个 $N \times N$ 的棋盘上玩，下图是当 $N=4$ 时一些可能的样子：
![](https://cdn.luogu.com.cn/upload/image_hosting/6j8s01tj.png)

游戏中，玩家可以在空的地方放置一颗黑棋或拿走一颗黑棋，从而产生多种图案。如果棋盘上的图案（或者旋转了 $90^{\circ}$ 或 $180^{\circ}$）在之前重复过，则产生了这个图案的玩家失败，另一个玩家胜利。

例如，如果上图中第一种图案出现过，那么另外三种都会结束游戏，但最后一种不会。

## 题目描述

现在给出若干个游戏中每个玩家的操作，请你判断游戏的胜负情况。

## 输入格式

输入包含若干个游戏，每一行首先输入一个整数 $N$ （$2 \leq N \leq 50$），代表棋盘的大小。

接下来有 $2N$ 行，每一行代表一个操作，每一行不一定是必要的。每一行都输入两个整数（$x,y$）代表棋盘上的一个坐标（$1 \leq x,y \leq N$），接着一个空格后输入一个字符```+```或```-```代表增加或者删除。

保证每一个操作中不会在已有棋子的地方放下棋子或在没有棋子的地方拿走棋子。

输入的最后一行为一个```0```。

## 输出格式

对于每个游戏，输出哪位玩家在游戏进行到第几步时获得了胜利。如果平局，则输出```Draw```。

## 说明/提示

在输入的第一个游戏中，第二位玩家在第 $3$ 步时取得胜利。

第二个游戏到最后没有出现重复的情况，因此平局。

## 样例 #1

### 输入

```
2
1 1 +
2 2 +
2 2 -
1 2 +
2
1 1 +
2 2 +
1 2 +
2 2 -
0
```

### 输出

```
Player 2 wins on move 3
Draw
```



---

---
title: "环状序列 Circular Sequence"
layout: "post"
diff: 普及-
pid: UVA1584
tag: ['模拟', '字符串']
---

# 环状序列 Circular Sequence

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4459

[PDF](https://uva.onlinejudge.org/external/15/p1584.pdf)



---

---
title: "Ducci序列 Ducci Sequence"
layout: "post"
diff: 普及-
pid: UVA1594
tag: ['模拟']
---

# Ducci序列 Ducci Sequence

## 题目描述

对于一个 $n$ 元组（$a_1,a_2,\cdots,a_n$），可以对每个数求出它和下一个数的差的绝对值，得到一个新的 $n$ 元组（$|a_1-a_2|,|a_2-a_3|,\cdots,|a_n-a_1|$）。重复这个过程，得到的序列称为 Ducci 序列，例如：

$$(8,11,2,7)\rightarrow(3,9,5,1)\rightarrow(6,4,4,2)\rightarrow(2,0,2,4)\rightarrow(2,2,2,2)\rightarrow(0,0,0,0)$$

也有的 Ducci 序列最终会循环。输入 $n$ 元组（$3\le n\le15$），你的任务是判断它最终会变成0还是会循环。输入保证最多 $1000$ 步就会变成 $0$ 或循环。

## 输出格式

感谢 @andyli 提供的翻译

## 样例 #1

### 输入

```
4
4
8 11 2 7
5
4 2 0 2 0
7
0 0 0 0 0 0 0
6
1 2 3 1 2 3

```

### 输出

```
ZERO
LOOP
ZERO
LOOP

```



---

---
title: "Clock Patience"
layout: "post"
diff: 普及-
pid: UVA170
tag: ['模拟', '栈', '队列']
---

# Clock Patience

## 题目描述

Card sharp Albert (Foxy) Smith 正在写一本有关于耐心游戏的书。为了仔细检查书中的例子，他正在编写程序以找到最佳玩法。

一个叫做 Clock Patience 的游戏的描述如下：

扑克牌面朝下按顺时针方向绕一个圆形发牌，代表一个时钟。每个小时上有一堆卡片，时钟中心还有一堆额外的卡片。第一张牌放在一点钟的位置，第二张放在两点钟，依此类推，顺时针方向放置，每第十三张牌放到时钟的中心。这就形成了十三堆，每堆里有四张牌是面朝下的。（下文中用 T 来代替 $10$）
![](https://cdn.luogu.com.cn/upload/image_hosting/zxlzflxl.png)

发完牌后游戏开始。K 牌堆的顶牌（即最后一张发的牌）作为当前牌。此后按照如下方式进行：

1. 将当前牌翻开，放在其点数对应的牌堆的最下面。
2. 当前牌堆的最上面的牌成为新的当前牌。
3. 如果当前牌正面朝上，游戏结束。

现在写一个程序，输入一叠被打乱的牌，然后玩这个游戏。

## 输入格式

（译者注：虽然原题面没提及，但根据译者的尝试，此题应该有多组测试数据）

此题有多组测试数据，每一个测试数据包含 $4$ 行，每行有 $13$ 张牌，每场牌用两个字母表示。第一个字母表示点数（用 T 来代替 $10$），第二个字母表示花色。输入是倒序输入的，因此放的第一张牌就是输入的最后一张牌。

输入以一行 ```#``` 结束。

## 输出格式

对于每一个测试数据输出一行。

每一行先包含一个数字，表示总共翻开了多少张牌。数字有两位，必要时在前面补 ```0```。接着紧接着是一个 ```,```，和最后的当前牌（按照输入的格式输出）。

## 样例 #1

### 输入

```
TS QC 8S 8D QH 2D 3H KH 9H 2H TH KS KC
9D JH 7H JD 2S QS TD 2C 4H 5H AD 4D 5D
6D 4S 9S 5S 7S JS 8H 3D 8C 3S 4C 6S 9C
AS 7C AH 6H KD JC 7D AC 5C TC QD 6C 3C
#
```

### 输出

```
44,KD
```



---

---
title: "纵横字谜的答案 Crossword Answers"
layout: "post"
diff: 普及-
pid: UVA232
tag: ['模拟', '字符串', '队列']
---

# 纵横字谜的答案 Crossword Answers

## 题目描述

有一个 $r$ 行 $c$ 列 $(1<r,c<10)$ 的网格，黑格为 `*` ，每个白格都填有一个字母。如果一个白格的左边相邻位置或者上边相邻位置没有白格（可能是黑格，也可能出了网格边界），则称这个白格是一个起始格。

你的任务是先找出网格中所有横向单词（`Across`）。这些单词必须从一个起始格（左边是黑格，或是第一列）开始，向右延伸到一个黑格的左边或者整个网格的最右列。然后找出所有竖向单词（`Down`），规则同上，这些单词必须从一个起始格（上边是黑格，或是第一行）开始，向下延伸到一个黑格的上边或者整个网格的最下行。

## 输入格式

有多个矩阵输入，对于第 $i$ 个矩阵，第一行输入 $r_i$ 和 $c_i$ 并以空格隔开。 $(1<r_i,c_i<10)$，表示此网格为 $r_i$ 行 $c_i$ 列，然后下面输入矩阵的内容，里面为大写字母或是 `*`，以 `0` 代表所有矩阵输入结束。

## 输出格式

每个谜题的输出包括谜题的标识符（如 `puzzle #1:`）和横向竖向单词列表。每个单词每行只输出一个并先输出以其相应定义的数量的递增顺序数字再输出单词。

数字的输出占据三个场宽并右对齐。

横向列表的标题是 `Across`，竖向单词列表的标题是 `Down`。

在列表为空的情况下（网格中的所有正方形均为黑色），`Across` 和 `Down` 标题仍应出现。

## 样例 #1

### 输入

```
2 2
AT
*O
6 7
AIM*DEN
*ME*ONE
UPON*TO
SO*ERIN
*SA*OR*
IES*DEA
0
```

### 输出

```
puzzle #1:
Across
1.AT
3.O
Down
1.A
2.TO
puzzle #2:
Across
1.AIM
4.DEN
7.ME
8.ONE
9.UPON
11.TO
12.SO
13.ERIN
15.SA
17.OR
18.IES
19.DEA
Down
1.A
2.IMPOSE
3.MEO
4.DO
5.ENTIRE
6.NEON
9.US
10.NE
14.ROD
16.AS
18.I
20.A
```



---

---
title: "Encoder and Decoder"
layout: "post"
diff: 普及-
pid: UVA444
tag: ['模拟']
---

# Encoder and Decoder

## 题目描述

### 题意简述
给定一串字符(长度$\le80$)，如果它是明文，转成密文，如果它是密文，转成明文。  
明文中只会出现以下字符：大小写字母，感叹号，逗号，句号，空格，冒号，分号，问号(均为英文标点)。  
加密方式是：把每个字符转换成对应的ASCII码，然后整体反转。  
e.g. 对于明文`abc`，首先将其转成对应的ASCII码：`97 98 99`，去除中间的空格：`979899`，整体反转输出：`998979`。

## 输入格式

输入有多组数据，每组数据一行，一个字符串表示明文或密文(需要自己判断)。

## 输出格式

对于每组数据，输出共一行，一个字符串表示答案。

## 样例 #1

### 输入

```
abc
798999
Have a Nice Day !
```

### 输出

```
998979
cba
332312179862310199501872379231018117927
```



---

---
title: "刽子手的游戏 Hangman Judge"
layout: "post"
diff: 普及-
pid: UVA489
tag: ['模拟', '字符串', '搜索']
---

# 刽子手的游戏 Hangman Judge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=430

[PDF](https://uva.onlinejudge.org/external/4/p489.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/5235bc315d8684bc30728d37f52e7f53bcd8dccb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/c4ea20c647fbaae88cdeb4ee1428a3bc412a001f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/1fdc8a8950ad27b9c821b2ad0fbaf563f3f4bca0.png)

## 样例 #1

### 输入

```
1
cheese
chese
2
cheese
abcdefg
3
cheese
abcdefgij
-1
```

### 输出

```
Round 1
You win.
Round 2
You chickened out.
Round 3
You lose.
```



---

---
title: "铁轨 Rails"
layout: "post"
diff: 普及-
pid: UVA514
tag: ['模拟', '栈']
---

# 铁轨 Rails

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=455

[PDF](https://uva.onlinejudge.org/external/5/p514.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/a8f0af9a2adeaeaab1d1906c3f3116afa0c6b444.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/03b4e1924e74948bc01f3f42cd5a31502f1c39b6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/7e96780a876f827180dea25139c1c77bbfb94937.png)

## 样例 #1

### 输入

```
5
1 2 3 4 5
5 4 1 2 3
0
6
6 5 4 3 2 1
0
0
```

### 输出

```
Yes
No

Yes
```



---

