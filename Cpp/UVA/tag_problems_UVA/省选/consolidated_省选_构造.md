---
title: "WonderTeam"
layout: "post"
diff: 省选/NOI-
pid: UVA1418
tag: ['构造']
---

# WonderTeam

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4164

[PDF](https://uva.onlinejudge.org/external/14/p1418.pdf)



---

---
title: "Picnic Planning"
layout: "post"
diff: 省选/NOI-
pid: UVA1537
tag: ['枚举', '生成树', '构造']
---

# Picnic Planning

## 题目描述

[PDF](https://onlinejudge.org/external/15/p1537.pdf)
# 题目背景
The Contortion Brothers是一组著名的马戏团小丑，以其令人难以置信的能力而闻名于世即使是最小的车辆，也能容纳无限的数量。在淡季期间，兄弟俩喜欢在当地公园聚在一起参加年度拳师大会。然而,兄弟俩不仅在狭小的空间里很紧张，而且在金钱上也很紧张，所以他们试图找到让每个人都参加聚会的方法，尽量**减少**每个人的汽车行驶里程（从而节省气体、磨损等）。为此，他们愿意在必要时把自己塞进少数几个车，尽量减少所有汽车的总里程。这经常导致许多兄弟开车去一个兄弟家，除了一辆车外，其他车都停在那里，然后挤进剩下的一个。然而，公园有一个限制：野餐地点的停车场可以只能容纳**有限数量**的汽车，因此必须将其纳入整体最小的计算中。同时，由于公园的入场费，一旦任何兄弟的车到达公园，它就会停在那里;他不会让乘客下车，然后去接其他兄弟。现在，对于你的普通马戏团来说，解决这个问题是一个挑战，所以留给你写一个程序来解决他们的最小化问题。

## 输入格式

第一行输入一个正整数 $ t $，**表示测试数据组数**

对于每一组测试样例:

**第一行**将包含一个整数 $ n ( n \leqslant 20) $，表示兄弟之间或兄弟与公园之间的公路连接数量。
空两行后接下来 $ n $ 行每行格式为“  $ name_1-name_2-dist $ ”  ，其中  $ name_1 $  和  $ name_2 $  要么是两个兄弟的名字。要么是“$ Park $ ”这个词和一个兄弟的姓名（**按任何顺序**），以及
$ dist $是它们之间的整数距离。这些道路都将是双向的。 

最后一行包含一个整数 $ s $ ，用于指定可以放在野餐地点停车场的汽车。你可以假设兄弟的房子都有一条路到公园，即每个问题都有解决方案。

**形式化地**:

给定一张 $ n $ 个点 $ n $ 条边的无向图，求出无向图的一棵最小生成树，满足一号节点的度数不超过给定的整数 $ s $.

## 输出格式

对于每个测试用例，输出必须遵循以下描述。连续两个案例的输出**将用空行分隔**。
对于每个测试用例，输出应该由以下组成:
```
Total miles driven: xxx
```
其中 `xxx` 是兄弟俩所有汽车的总行驶里程。
# 输入输出样例

### 输入 #1
```
2


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
3


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
1
```
### 输出 #1
```
Total miles driven: 183

Total miles driven: 255

```



---

