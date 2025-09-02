---
title: "大理石在哪儿 Where is the Marble?"
layout: "post"
diff: 普及-
pid: UVA10474
tag: ['搜索', '二分', '递归', '枚举', '排序']
---

# 大理石在哪儿 Where is the Marble?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1415

[PDF](https://uva.onlinejudge.org/external/104/p10474.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/2bb1c26d80e7830dba0391c0afa3b04c198f8ee0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/6c2a03977a6e49d286d2fa5cc116d53d9da95e8b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/03b79b1f48ddec6133706f0b92ca55a3ecd02a38.png)

## 样例 #1

### 输入

```
4 1
2
3
5
1
5
5 2
1
3
3
3
1
2
3
0 0
```

### 输出

```
CASE# 1:
5 found at 4
CASE# 2:
2 not found
3 found at 3
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
title: "盒子 Box"
layout: "post"
diff: 普及-
pid: UVA1587
tag: ['排序']
---

# 盒子 Box

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4462

[PDF](https://uva.onlinejudge.org/external/15/p1587.pdf)



---

---
title: "对称轴 Symmetry"
layout: "post"
diff: 普及-
pid: UVA1595
tag: ['枚举', '排序', '构造']
---

# 对称轴 Symmetry

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4470

[PDF](https://uva.onlinejudge.org/external/15/p1595.pdf)



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

