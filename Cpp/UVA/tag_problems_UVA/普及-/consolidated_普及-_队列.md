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
title: "Age Sort"
layout: "post"
diff: 普及-
pid: UVA11462
tag: ['排序', '优先队列', '队列']
---

# Age Sort

## 题目描述

给定一个国家所有人的年龄（以年为单位），且每个人的年龄至少为 $1$ 岁。你知道该国没有人活到 $100$ 岁或以上。现在，你有一个非常简单的任务：将所有年龄按升序排序。

## 输入格式

输入文件中有多个测试用例。每个测试用例以一个整数 $n$ 开头（$0 < n \le 2 \times 10 ^ 6$)，表示总人数。接下来的一行中有 $n$ 个整数，表示每个人的年龄。输入以 $n = 0$ 终止，这个测试用例不应被处理。

## 输出格式

对于每个测试用例，打印一行包含 $n$ 个用空格分隔的整数。这些整数是该国家按升序排列的年龄。

**注意**：输入数据非常大（约 25MB），因此需要使用更快的输入输出。

---

Translated by User 735713.

## 样例 #1

### 输入

```
5
3 4 2 1 5
5
2 3 2 3 1
0
```

### 输出

```
1 2 3 4 5
1 2 2 3 3
```



---

---
title: "丑数 Ugly Numbers"
layout: "post"
diff: 普及-
pid: UVA136
tag: ['枚举', '优先队列', '队列']
---

# 丑数 Ugly Numbers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=72

[PDF](https://uva.onlinejudge.org/external/1/p136.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/9235847457e3c8f707f609605cbc21fd7bb05029.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/ed5a845059370c8ba7ec4955b10f7eead4ab3787.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/c8116baef73c601c2156d6d31ee1e30b14b9b560.png)

## 样例 #1

### 输入

```

```

### 输出

```
The 1500'th ugly number is &lt;number&gt;.
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

