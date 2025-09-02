---
title: "Gergovia的酒交易 Wine trading in Gergovia"
layout: "post"
diff: 普及-
pid: UVA11054
tag: ['贪心', '前缀和']
---

# Gergovia的酒交易 Wine trading in Gergovia

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=1995

[PDF](https://uva.onlinejudge.org/external/110/p11054.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/ced1606866ddabe301a52d0310f9433bc4587f7e.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/26ec5db5cf20e0de0ecadbcd24f88389305b92a4.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/178f45e194980c55bc177e289c65e48b01d9fea5.png)

## 样例 #1

### 输入

```
5
5 -4 1 -3 1
6
-1000 -1000 -1000 1000 1000 1000
0
```

### 输出

```
9
9000
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
title: "装箱 Bin Packing"
layout: "post"
diff: 普及-
pid: UVA1149
tag: ['贪心']
---

# 装箱 Bin Packing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3590

[PDF](https://uva.onlinejudge.org/external/11/p1149.pdf)



---

---
title: "Commando War"
layout: "post"
diff: 普及-
pid: UVA11729
tag: ['贪心', '排序']
---

# Commando War

## 题目描述

>  _我们在树林里等待命令，前线的消息却始终没有传来  
到傍晚，枪声已经遥远  
啊，我们悄悄地穿过阴影，轻轻地从树间溜走  
在薄雾中穿过他们的防线，跪着爬过田野  
而我所能看到的  
是空中的火焰，发出红光，映衬着随风飘散的烟雾_

有一场对你的国家来说形势并不乐观的战争。现在是时候行动了。你有一支突击队可以调遣，并计划对附近一个重要的敌军营地进行伏击。你的队伍里有 $N$ 名士兵。在你总体的计划中，每个士兵都有独特的职责，你不希望任何士兵知道其他人的计划，以便每个人都能专注于自己的任务。为了达成这一点，你分别向每个士兵简要说明任务，并在他们被派往战场之前单独进行简报。你知道每个士兵完成任务需要一定的时间。你也很清楚给每个士兵进行简报需要多长时间。由于你急于尽快完成整个行动，你需要找到一个简报顺序，使所有士兵完成任务的总时间最少。你可以假设，没有士兵的计划依赖于其他士兵的任务。换句话说，一旦士兵开始执行任务，他可以不间断地完成任务。

## 输入格式

输入文件中会有多个测试用例。每个测试用例以一个整数 $N$（$1 \le N \le 1000$）开始，表示士兵的数量。接下来 $N$ 行，每行描述一个士兵，并给出两个整数 $B$（$1 \le B \le 10000$）和 $J$（$1 \le J \le 10000$）。表示向该士兵简报所需的时间是 $B$ 秒，该士兵完成任务所需的时间是 $J$ 秒。输入由 $N = 0$ 表示结束，这个测试用例不应被处理。

## 输出格式

对于每个测试用例，按 $\texttt{Case }X\texttt{: }Y$ 的格式打印一行，其中 $X$ 是测试用例编号，$Y$ 是从第一次简报开始到所有任务完成所经过的总秒数。

---

Translated by User 735713.

## 样例 #1

### 输入

```
3
2 5
3 2
2 1
3
3 3
4 4
5 5
0
```

### 输出

```
Case 1: 8
Case 2: 15
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

