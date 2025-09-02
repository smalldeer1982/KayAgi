---
title: "THEWAR - Revenge of Arjuna"
layout: "post"
diff: 难度0
pid: SP26119
tag: []
---

# THEWAR - Revenge of Arjuna

## 题目描述

《摩诃婆罗多》是一部史诗巨著，主要描述了俱卢族和般度族王子们在俱卢之野大战中的命运。阿周那是般度五兄弟中的第三位，与克里希纳一起被视为故事的主角。他和苏波德拉的儿子名叫阿比曼尤。战争进行到第十三天，阿比曼尤因进入由俱卢族军队布下的强大车轮阵而声名鹊起。这个阵型是德罗纳设计的，目的是为了抓住坚战。只有克里希纳和阿周那知道如何破解这个复杂的七层螺旋防御阵。

在坚战惶恐之际，阿比曼尤表示虽然他不知道如何脱出阵型，但他可以进入。于是制订了一个计划，即般度族的军队将在阿比曼尤之后进入车轮阵，从内部打破它。然而，当阿比曼尤成功进入车轮阵时，杰德拉塔阻挡了其他四位兄弟的进入，最终导致阿比曼尤在阵中牺牲。天黑时，阿比曼尤殉难的消息传到了他的父亲阿周那耳中。阿周那誓言要在下一天日落之前杀死杰德拉塔，否则就自焚。因此，他必须在太阳落山前赶到杰德拉塔那里。

在俱卢族军队中，有 $N$ 个位置，编号从 $0$ 到 $N-1$。阿周那总是从位置 $0$ 出发，而杰德拉塔则处在位置 $1$。阿周那需要尽快赶到位置 $1$，期间需要消灭沿途的敌兵。每两点之间的行军时间以一个 $N \times N$ 的矩阵给出。此外，阿周那还拥有 $K$ 支神箭，每支神箭可以将到达某一位置的时间减半，但同一时刻只能使用一支。他可以选择是否使用这些神箭。请计算阿周那达到杰德拉塔所需的最少时间。

## 输入格式

第一行是一个整数 $T$，表示测试用例的数量。（$T \leq 55$）

第二行包含一个整数 $N$，表示战场上位置的数量。（$2 \leq N \leq 50$）

接下来是一个 $N \times N$ 的矩阵，表明从一个位置到另一个位置所需的时间。（每个值不超过 $50$）

最后一行是一个整数 $K$，表示阿周那最初有多少支神箭。（$0 \leq K \leq 50$）

## 输出格式

输出一个整数，表示阿周那从出发地到达杰德拉塔的最短时间。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
3
0 9 4
9 0 4
4&nbsp;4 0
1
```

### 输出

```
4.5
Explanation:
  According to given data, you need:\n  9 units of time to move between spots 0 and 1\n  4 units of time to move between spots 0 and 2\n  4 units of time o move between spots 1 and 2 \n  You have a single Divyastra. The optimal solution is to use a Divyastra and move&nbsp; directly from spot 0 to spot 1. This &nbsp;will take 9/2 = 4.5 units of time.
```

