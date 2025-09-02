---
title: "古老的密码 Ancient Cipher"
layout: "post"
diff: 普及-
pid: UVA1339
tag: ['字符串', '排序', '概率论']
---

# 古老的密码 Ancient Cipher

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4085

[PDF](https://uva.onlinejudge.org/external/13/p1339.pdf)

## 样例 #1

### 输入

```
JWPUDJSTVP
VICTORIOUS
MAMA
ROME
HAHA
HEHE
AAA
AAA
NEERCISTHEBEST
SECRETMESSAGES
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "DNA序列 DNA Consensus String"
layout: "post"
diff: 普及-
pid: UVA1368
tag: ['字符串', '贪心']
---

# DNA序列 DNA Consensus String

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4114

[PDF](https://uva.onlinejudge.org/external/13/p1368.pdf)



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
title: "分子量 Molar mass"
layout: "post"
diff: 普及-
pid: UVA1586
tag: ['字符串', '概率论']
---

# 分子量 Molar mass

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4461

[PDF](https://uva.onlinejudge.org/external/15/p1586.pdf)

## 样例 #1

### 输入

```
4
C
C6H5OH
NH2CH2COOH
C12H22O11
```

### 输出

```
12.010
94.108
75.070
342.296
```



---

---
title: "IP网络 IP Networks"
layout: "post"
diff: 普及-
pid: UVA1590
tag: ['字符串', '进制', '位运算']
---

# IP网络 IP Networks

## 题目描述

亚历克斯是IP网络的管理员。他的客户每个人有一组单独的IP地址，他决定将所有IP地址分组到最小可能的IP网络中。

每个IP地址有四个部分组成，每个部分用小数点分离。格式如a,b,c,d每个部分都是一个十进制的数（0≤这个数≤255）且没有多余的前导零。

IP网络由两个4各部分的数字——网络地址和网络掩码组成。网络地址和网络掩码和IP地址写入方式相同。为了理解网络地址和网络掩码的含义，我们将它们用二进制来表述。IP地址、网络地址和网络掩码的二进制都由32位组成：a的8位（从最重要到最不重要），其次是b的8位，其次是c的8位，其次是d的8位。

IP网络包含一个2n个IP地址的范围，其中所有n>32。网络掩码始终存在32~n个第一部分设置为一，n个最后部分在二进制表示中设置为零。网络地址已任意32个n个第一部分，n个最后部分在其二进制表示中设置为零。IP网络所有的32个n位第一位相当于32位n个任意位的网络地址的所有IP地址最后一位。

我们说，一个IP网络比其他IP网络更小，那么它包含更少的IP地址。

## 输入格式

有多个测试数据。

输入文件的第一行包含一个整数m。下面m行都是一个IP地址。IP地址可能重复。

## 输出格式

每个测试数据在第一行写上网络地址，在第二行写上网络掩码。 网络地址和网络掩码代表的IP网络包括所有IP地址且最小。

## 样例输入输出：
### 样例输入#1
3

194.85.160.177

194.85.160.183

194.85.160.178

### 样例输出#1
194.85.160.176

255.255.255.248

## 说明/提示

一个IP网络的网络地址是194.85.160.176它的网络掩码是255.255.255.248

那么这个IP网络包含8个IP地址从194.85.160.176到194.85.160.183

0 ≤ n ≤ 32,1 ≤ m ≤ 1000

感谢@BIGmrsrz 提供翻译



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
title: "回文词 Palindromes"
layout: "post"
diff: 普及-
pid: UVA401
tag: ['字符串']
---

# 回文词 Palindromes

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=342

[PDF](https://uva.onlinejudge.org/external/4/p401.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA401/b6c215fa795465f551b5ca7a97ddc3a7f22e50ab.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA401/765d17adb8ebb1c9f9f633813a123b3fdc93dfa5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA401/d9c985cc6ed58c99115e4db79b3515accf10435d.png)

注意要换两次行。

## 样例 #1

### 输入

```
NOTAPALINDROME
ISAPALINILAPASI
2A3MEAS
ATOYOTA
```

### 输出

```
NOTAPALINDROME -- is not a palindrome.

ISAPALINILAPASI -- is a regular palindrome.

2A3MEAS -- is a mirrored string.

ATOYOTA -- is a mirrored palindrome.
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
title: "Word Amalgamation"
layout: "post"
diff: 普及-
pid: UVA642
tag: ['字符串', '排序']
---

# Word Amalgamation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=583

[PDF](https://uva.onlinejudge.org/external/6/p642.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/798288cf0a5caae5367a31141c3cf2e90bd3b5cb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/d85b48af6838aac4769be70e174b7480fc2b98e7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/d8237ee3b00c49d0666058cf53b6b711aad2bdf6.png)

## 样例 #1

### 输入

```
tarp
given
score
refund
only
trap
work
earn
course
pepper
part
XXXXXX
resco
nfudre
aptr
sett
oresuc
XXXXXX
```

### 输出

```
score
******
refund
******
part
tarp
trap
******
NOT A VALID WORD
******
course
******
```



---

