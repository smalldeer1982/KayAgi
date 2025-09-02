---
title: "The Rank"
layout: "post"
diff: 入门
pid: CF1017A
tag: ['枚举', '排序']
---

# The Rank

## 题目描述

John Smith knows that his son, Thomas Smith, is among the best students in his class and even in his school. After the students of the school took the exams in English, German, Math, and History, a table of results was formed.

There are $ n $ students, each of them has a unique id (from $ 1 $ to $ n $ ). Thomas's id is $ 1 $ . Every student has four scores correspond to his or her English, German, Math, and History scores. The students are given in order of increasing of their ids.

In the table, the students will be sorted by decreasing the sum of their scores. So, a student with the largest sum will get the first place. If two or more students have the same sum, these students will be sorted by increasing their ids.

Please help John find out the rank of his son.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 1000 $ ) — the number of students.

Each of the next $ n $ lines contains four integers $ a_i $ , $ b_i $ , $ c_i $ , and $ d_i $ ( $ 0\leq a_i, b_i, c_i, d_i\leq 100 $ ) — the grades of the $ i $ -th student on English, German, Math, and History. The id of the $ i $ -th student is equal to $ i $ .

## 输出格式

Print the rank of Thomas Smith. Thomas's id is $ 1 $ .

## 说明/提示

In the first sample, the students got total scores: $ 398 $ , $ 400 $ , $ 398 $ , $ 379 $ , and $ 357 $ . Among the $ 5 $ students, Thomas and the third student have the second highest score, but Thomas has a smaller id, so his rank is $ 2 $ .

In the second sample, the students got total scores: $ 369 $ , $ 240 $ , $ 310 $ , $ 300 $ , $ 300 $ , and $ 0 $ . Among the $ 6 $ students, Thomas got the highest score, so his rank is $ 1 $ .

## 样例 #1

### 输入

```
5
100 98 100 100
100 100 100 100
100 100 99 99
90 99 90 100
100 98 60 99

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6
100 80 90 99
60 60 60 60
90 60 100 60
60 100 60 80
100 100 0 100
0 0 0 0

```

### 输出

```
1

```



---

---
title: "Power Consumption Calculation"
layout: "post"
diff: 入门
pid: CF10A
tag: ['模拟', '排序', '概率论']
---

# Power Consumption Calculation

## 题目描述

Tom is interested in power consumption of his favourite laptop. His laptop has three modes. In normal mode laptop consumes $ P_{1} $ watt per minute. $ T_{1} $ minutes after Tom moved the mouse or touched the keyboard for the last time, a screensaver starts and power consumption changes to $ P_{2} $ watt per minute. Finally, after $ T_{2} $ minutes from the start of the screensaver, laptop switches to the "sleep" mode and consumes $ P_{3} $ watt per minute. If Tom moves the mouse or touches the keyboard when the laptop is in the second or in the third mode, it switches to the first (normal) mode. Tom's work with the laptop can be divided into $ n $ time periods $ [l_{1},r_{1}],[l_{2},r_{2}],...,[l_{n},r_{n}] $ . During each interval Tom continuously moves the mouse and presses buttons on the keyboard. Between the periods Tom stays away from the laptop. Find out the total amount of power consumed by the laptop during the period $ [l_{1},r_{n}] $ .

## 输入格式

The first line contains 6 integer numbers $ n $ , $ P_{1} $ , $ P_{2} $ , $ P_{3} $ , $ T_{1} $ , $ T_{2} $ ( $ 1<=n<=100,0<=P_{1},P_{2},P_{3}<=100,1<=T_{1},T_{2}<=60 $ ). The following $ n $ lines contain description of Tom's work. Each $ i $ -th of these lines contains two space-separated integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<r_{i}<=1440 $ , $ r_{i}<l_{i+1} $ for $ i<n $ ), which stand for the start and the end of the $ i $ -th period of work.

## 输出格式

Output the answer to the problem.

## 样例 #1

### 输入

```
1 3 2 1 5 10
0 10

```

### 输出

```
30
```

## 样例 #2

### 输入

```
2 8 4 2 5 10
20 30
50 100

```

### 输出

```
570
```



---

---
title: "Business trip"
layout: "post"
diff: 入门
pid: CF149A
tag: ['贪心', '排序', '概率论']
---

# Business trip

## 题目描述

多么令人开心啊！Petya的父母去了一个长达一年的商业旅行并且把这个爱玩的孩子独自留下了。Petya高兴到了极点。他跳上床并扔了一整天的枕头，直到...
（这和做题有什么关系，汗）

今天Petya打开橱柜发现了一个吓人的字条。他的父母给他留了家务：他应该给他们最喜爱的花浇一整年的水，每一天，无论早上，下午，还是晚上。“等一下”——Petya想。他明白一个事实，如果他在一年中的第$i$月（$1\leq i\leq12$）完成父母的任务，这个花就会生长$a_i$厘米，并且如果他在第$i$月不给花浇水，花在这个月就不会长。他的父母不会相信他给花浇过水了，如果这花生长的严格少于$k$厘米。

帮助Petya选择最少的月数浇花，使得这花能够长得不少于$k$厘米。

## 输入格式

第一行正好包含一个整数$k$（$0\leq k\leq100$）。下一行包含十二个整数：第$i$个数代表$a_i$（$0\leq a_i\leq100$）

## 输出格式

输出的仅仅一个整数，表示Petya给花浇水的最少月数，使得花生长不少于$k$厘米。如果花一年不能生长$k$厘米，输出$-1$。

## 说明/提示

让我们考虑第一个样例。在第七个月和第九个月给花浇水。然后花长五厘米。

第二样例Petya的父母会相信他，即使花不生长（$k=0$ ）。所以，Petya可能根本不浇花。

Translated by @Khassar

## 样例 #1

### 输入

```
5
1 1 1 1 2 2 3 2 2 1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
0
0 0 0 0 0 0 0 1 1 2 3 0

```

### 输出

```
0

```

## 样例 #3

### 输入

```
11
1 1 4 1 1 5 1 1 4 1 1 1

```

### 输出

```
3

```



---

---
title: "I_love_%username%"
layout: "post"
diff: 入门
pid: CF155A
tag: ['模拟', '排序', '概率论']
---

# I_love_%username%

## 题目描述

Vasya很喜欢一个coder，他喜欢看那个coder的节目，那个coder每次编程可以得到一个非负分数（不超过10000），而有两种情况能使Vasya惊讶：
·coder得到的分数完全大于过去的分数；
·coder得到的分数完全小于过去的分数。
注意：第一次得到的分数不会使人惊讶。
给定coder编程次数n，给定每次编程得到的分数，请你求出Vasya的惊讶次数。

~~看着题面上好像没有介绍输入输出和数据范围就来多嘴一句~~

## 输入格式

第一行包括一个整数n（1<=n<=1000），代表coder参加比赛时的编码数量；

第二行包括了n个用空格分开的整数，即coder每一个编码在比赛中的得分（得分均不超过10000）；

## 输出格式

输出一行，包括一个整数，代表整场比赛中Vasya被coder惊讶到的总次数；


由 @strike 提供翻译

## 样例 #1

### 输入

```
5
100 50 200 150 200

```

### 输出

```
2

```

## 样例 #2

### 输入

```
10
4664 6496 5814 7010 5762 5736 6944 4850 3698 7242

```

### 输出

```
4

```



---

---
title: "Download More RAM"
layout: "post"
diff: 入门
pid: CF1629A
tag: ['贪心', '排序']
---

# Download More RAM

## 题目描述

有一家商店有 $n$ 种不同的软件，可以增加你的内存。第 $i$ 个内存增加软件需要 $a_i$ GB 的内存来运行（这是暂时的。一旦程序运行完毕，您就可以恢复内存），并**永久**提供额外的 $b_i$ GB 内存。**每个软件只能使用一次**。您的电脑当前有 $k$ GB 内存。请注意，如果需要使用比当前更多 GB 的内存，则不能使用内存增加软件。

因为内存是世界上最重要的东西，你想知道，能运行的软件全部运行完后，可以达到的最大内存量是多少？

## 输入格式

输入的第一行包含一个整数 $t$ $(1 \leq t \leq 100)$，为测试用例的数量。测试用例的描述如下：

每个测试用例的第一行包含两个整数 $n$ 和 $k$ $(1 \leq n \leq 100,1 \leq K \leq 1000)$。接下来是两行，每行包含 $n$ 个整数，为数组 $a$ 和 $b$ $(1 \leq a_i,b_i \leq 1000)$。

## 输出格式

对于每个测试用例，输出一行一个整数，为可以达到的最大内存量。

## 样例 #1

### 输入

```
4
3 10
20 30 10
9 100 10
5 1
1 1 5 1 1
1 1 1 1 1
5 1
2 2 2 2 2
100 100 100 100 100
5 8
128 64 32 16 8
128 64 32 16 8
```

### 输出

```
29
6
1
256
```



---

---
title: "Alice and Books"
layout: "post"
diff: 入门
pid: CF1978A
tag: ['贪心', '排序']
---

# Alice and Books

## 题目描述

### 题意翻译
Alice有n本书，第一本书有
$a_1$页，序号为1，第二本书有$a_2$页,序号为2， …… , 第n本书有$a_n$页，序号为n。Alice将把所有书分成两堆，并阅读每一堆中序号最大的一本书。

Alice喜欢读书，请你告诉她，她最多可以读多少页的书。

## 输入格式

一个正整数t（$ 1 \le t\le500$),表示数据组数。

每组数据的第一行一个正整数n（$2 \le n \le 100$)，表示书本的数量.

每组数据的第二行包含n个数，$a_1,a_2,...,a_n$,表示每本书的页数。

## 输出格式

对于每组数据，输出一个正整数,表示Alice可以阅读的最大页数。

## 样例 #1

### 输入

```
5
2
1 1
4
2 3 3 1
5
2 2 3 2 2
2
10 3
3
1 2 3
```

### 输出

```
2
4
5
13
5
```



---

---
title: "Choosing Cubes"
layout: "post"
diff: 入门
pid: CF1980B
tag: ['排序']
---

# Choosing Cubes

## 题目描述

Dmitry has $ n $ cubes, numbered from left to right from $ 1 $ to $ n $ . The cube with index $ f $ is his favorite.

Dmitry threw all the cubes on the table, and the $ i $ -th cube showed the value $ a_i $ ( $ 1 \le a_i \le 100 $ ). After that, he arranged the cubes in non-increasing order of their values, from largest to smallest. If two cubes show the same value, they can go in any order.

After sorting, Dmitry removed the first $ k $ cubes. Then he became interested in whether he removed his favorite cube (note that its position could have changed after sorting).

For example, if $ n=5 $ , $ f=2 $ , $ a = [4, \color{green}3, 3, 2, 3] $ (the favorite cube is highlighted in green), and $ k = 2 $ , the following could have happened:

- After sorting $ a=[4, \color{green}3, 3, 3, 2] $ , since the favorite cube ended up in the second position, it will be removed.
- After sorting $ a=[4, 3, \color{green}3, 3, 2] $ , since the favorite cube ended up in the third position, it will not be removed.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. Then follow the descriptions of the test cases.

The first line of each test case description contains three integers $ n $ , $ f $ , and $ k $ ( $ 1 \le f, k \le n \le 100 $ ) — the number of cubes, the index of Dmitry's favorite cube, and the number of removed cubes, respectively.

The second line of each test case description contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 100 $ ) — the values shown on the cubes.

## 输出格式

For each test case, output one line — "YES" if the cube will be removed in all cases, "NO" if it will not be removed in any case, "MAYBE" if it may be either removed or left.

You can output the answer in any case. For example, the strings "YES", "nO", "mAyBe" will be accepted as answers.

## 样例 #1

### 输入

```
12
5 2 2
4 3 3 2 3
5 5 3
4 2 1 3 5
5 5 2
5 2 4 1 3
5 5 5
1 2 5 4 3
5 5 4
3 1 2 4 5
5 5 5
4 3 2 1 5
6 5 3
1 2 3 1 2 3
10 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1
42
5 2 3
2 2 1 1 2
2 1 1
2 1
5 3 1
3 3 2 3 2
```

### 输出

```
MAYBE
YES
NO
YES
YES
YES
MAYBE
MAYBE
YES
YES
YES
NO
```



---

---
title: "X Axis"
layout: "post"
diff: 入门
pid: CF1986A
tag: ['排序']
---

# X Axis

## 题目描述

你得到了三个点 $x_1$，$x_2$ 和 $x_3$。 你需要求出一个点使得 $x_1$，$x_2$，$x_3$ 与这个点的距离和最小。

## 输入格式

第一行为一个整数 $t$，表示测试数据的组数。

接下来 $t$ 行，每行三个整数 $x_1$，$x_2$ 和 $x_3$。

## 输出格式

输出共 $t$ 行，每行一个整数表示与给出的三个点最小的距离和。

## 说明/提示

$1 \le t \le 10^3$，$1 \le x_i \le 10$。

translate by @[I_am_a_big_juruo](https://www.luogu.com.cn/user/1197299)

## 样例 #1

### 输入

```
8
1 1 1
1 5 9
8 2 8
10 9 3
2 1 1
2 4 1
7 3 5
1 9 4
```

### 输出

```
0
8
6
7
1
3
4
8
```



---

---
title: "Second Order Statistics"
layout: "post"
diff: 入门
pid: CF22A
tag: ['搜索', '排序', '概率论']
---

# Second Order Statistics

## 题目描述

### 题面描述

给定一个数组，输出其中第二小的整数（相等的整数只计算一次）。

## 输入格式

第一行，一个整数 $n$（$1 \leq n \leq 100$），表示数组长度。

第二行，$n$ 个绝对值小于 $100$ 的整数。

## 输出格式

一行。如果该数组存在第二小整数，则输出第二小整数。如果不存在，则输出`NO`。

## 样例 #1

### 输入

```
4
1 2 2 -4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
1 2 3 1 1

```

### 输出

```
2

```



---

---
title: "Dragons"
layout: "post"
diff: 入门
pid: CF230A
tag: ['贪心', '排序']
---

# Dragons

## 题目描述

小方在跟龙进行比赛，他要是想进入下一层级，就必须要击败在这一层级上的所有的n条龙。 小方和每一条龙都有一个可以用整数表示的力量值，在每一次战斗中，该次战斗的结果由战斗的双方的力量值所决定。在一开始，小方的力量值是s。

在任意一次战斗中，如果小方的力量值比第i条龙（1<=i<=n）的力量值大，那么小方可以击败这头龙并且获得额外的力量值y(i)，如果小方的力量值不大于这头龙的力量值，那么小方将在这场战斗中死亡。

小方可以以任意的一个顺序和龙进行战斗。请编写程序确定小方是否可以继续进入下一层级的比赛，即击败所有的龙族并且自己没有任何损失。

## 输入格式

第一行包括2个用空格分隔的整数s,n,（1<=s<=10000,1<=n<=1000）表示小方初始的力量值和龙的总个数

接下来n行包含2个用空格分开的整数x(i),y(i) 表示第i头龙的力量值以及击败第i头龙可以获得的额外力量值

## 输出格式

一行，如果小方可以进入下一层级，则输出“YES”（不包含引号），否则输出“NO”（不包含引号）。

## 说明/提示

在第一个样例中，小方力量初始值为2，第一条龙的力量值小于2，那么小方将击败他并获得额外的力量值99，此时小方的力量值为2+99=101，大于第二条龙的力量值，小方将击败他，因此小方可以进入下个层级。

在第二个样例中，小方力量初始值为10，小于唯一的一条龙的力量值100，那么小方将无法击败这条龙，因此无法进入下一层级。

感谢@wcy1056935201 提供翻译

## 样例 #1

### 输入

```
2 2
1 99
100 0

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
10 1
100 100

```

### 输出

```
NO

```



---

---
title: "Spit Problem"
layout: "post"
diff: 入门
pid: CF29A
tag: ['模拟', '枚举', '排序']
---

# Spit Problem

## 题目描述

In a Berland's zoo there is an enclosure with camels. It is known that camels like to spit. Bob watched these interesting animals for the whole day and registered in his notepad where each animal spitted. Now he wants to know if in the zoo there are two camels, which spitted at each other. Help him to solve this task.

The trajectory of a camel's spit is an arc, i.e. if the camel in position $ x $ spits $ d $ meters right, he can hit only the camel in position $ x+d $ , if such a camel exists.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the amount of camels in the zoo. Each of the following $ n $ lines contains two integers $ x_{i} $ and $ d_{i} $ ( $ -10^{4}<=x_{i}<=10^{4},1<=|d_{i}|<=2·10^{4} $ ) — records in Bob's notepad. $ x_{i} $ is a position of the $ i $ -th camel, and $ d_{i} $ is a distance at which the $ i $ -th camel spitted. Positive values of $ d_{i} $ correspond to the spits right, negative values correspond to the spits left. No two camels may stand in the same position.

## 输出格式

If there are two camels, which spitted at each other, output YES. Otherwise, output NO.

## 样例 #1

### 输入

```
2
0 1
1 -1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3
0 1
1 1
2 -2

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
2 -10
3 10
0 5
5 -5
10 1

```

### 输出

```
YES

```



---

---
title: "Helpful Maths"
layout: "post"
diff: 入门
pid: CF339A
tag: ['字符串', '排序', '概率论']
---

# Helpful Maths

## 题目描述

Xenia the beginner mathematician is a third year student at elementary school. She is now learning the addition operation.

The teacher has written down the sum of multiple numbers. Pupils should calculate the sum. To make the calculation easier, the sum only contains numbers 1, 2 and 3. Still, that isn't enough for Xenia. She is only beginning to count, so she can calculate a sum only if the summands follow in non-decreasing order. For example, she can't calculate sum 1+3+2+1 but she can calculate sums 1+1+2 and 3+3.

You've got the sum that was written on the board. Rearrange the summans and print the sum in such a way that Xenia can calculate the sum.

## 输入格式

The first line contains a non-empty string $ s $ — the sum Xenia needs to count. String $ s $ contains no spaces. It only contains digits and characters "+". Besides, string $ s $ is a correct sum of numbers 1, 2 and 3. String $ s $ is at most 100 characters long.

## 输出格式

Print the new sum that Xenia can count.

## 样例 #1

### 输入

```
3+2+1

```

### 输出

```
1+2+3

```

## 样例 #2

### 输入

```
1+1+3+1+3

```

### 输出

```
1+1+1+3+3

```

## 样例 #3

### 输入

```
2

```

### 输出

```
2

```



---

---
title: "Second-Price Auction"
layout: "post"
diff: 入门
pid: CF386A
tag: ['排序']
---

# Second-Price Auction

## 题目描述

In this problem we consider a special type of an auction, which is called the second-price auction. As in regular auction $ n $ bidders place a bid which is price a bidder ready to pay. The auction is closed, that is, each bidder secretly informs the organizer of the auction price he is willing to pay. After that, the auction winner is the participant who offered the highest price. However, he pay not the price he offers, but the highest price among the offers of other participants (hence the name: the second-price auction).

Write a program that reads prices offered by bidders and finds the winner and the price he will pay. Consider that all of the offered prices are different.

## 输入格式

The first line of the input contains $ n $ ( $ 2<=n<=1000 $ ) — number of bidders. The second line contains $ n $ distinct integer numbers $ p_{1},p_{2},...\ p_{n} $ , separated by single spaces ( $ 1<=p_{i}<=10000 $ ), where $ p_{i} $ stands for the price offered by the $ i $ -th bidder.

## 输出格式

The single output line should contain two integers: index of the winner and the price he will pay. Indices are 1-based.

## 样例 #1

### 输入

```
2
5 7

```

### 输出

```
2 5

```

## 样例 #2

### 输入

```
3
10 2 8

```

### 输出

```
1 8

```

## 样例 #3

### 输入

```
6
3 8 2 9 4 14

```

### 输出

```
6 9

```



---

---
title: "Gravity Flip"
layout: "post"
diff: 入门
pid: CF405A
tag: ['排序']
---

# Gravity Flip

## 题目描述

小克里斯在物理课上很无聊（太容易了），所以他建了一个玩具箱让自己的有事做。这个盒子很特别，因为它有改变重力的能力。 盒子内排列 NN 列的玩具立方体。第$i$列包含$A_i$个立方体。首先，盒子里的重力向下拉动立方体。当克里斯切换重力时，它开始将所有立方体拉到盒子的右侧。

![](https://cdn.luogu.org/upload/vjudge_pic/CF405A/f9e5056d82c9422148cc319b310a47b3094fcd5f.png)

该图显示了方块中的立方体的初始和最终位置：改变了它们的位置的立方体用橙色突出显示。 给定盒子中的玩具立方体的初始位置，在重力开关之后找到$N$列中的每个立方体的数量！

## 输入格式

输入的第一行包含整数$n(1<=n<=100)$，表示玩具箱中玩具的列数。下一行包含 nn 个用空隔分隔的整数。第$i$个数$A_i(1<=A_i<=100)$表示第i列中立方体的数目。

## 输出格式

输出$n$个整数，由空隔分隔，其中第$i$个数是重力切换后第$i$列中的立方体数量。

## 样例 #1

### 输入

```
4
3 2 1 2

```

### 输出

```
1 2 2 3 

```

## 样例 #2

### 输入

```
3
2 3 8

```

### 输出

```
2 3 8 

```



---

---
title: "Laptops"
layout: "post"
diff: 入门
pid: CF456A
tag: ['贪心', '枚举', '排序']
---

# Laptops

## 题目描述

有一天Dima和Alex正在讨论关于 $n$ 台笔记本电脑的价格与质量。Dima认为价格高的笔记本质量也高，而Alex认为笔记本是物美价廉，价格低的笔记本质量反而高。

正当他们争（吵）论得不可开交之时，您过来了。现在您需要写出一个程序去确认谁是谁非。

## 输入格式

第一行输入笔记本个数 $n$ $(n \leqslant 10^5)$ 。

接下来的 $n$ 行输入两个数,分别是第 $n$ 个笔记本的价值 $a_i$ 与质量 $b_i$。

保证所有的 $a_i$ 与 $b_i$ 不同，且属于 $int$ 范围。

## 输出格式

如果存在符合Alex的要求的两台笔记本电脑（即一台的价格比另一台低且质量比另一台高），则输出"Happy Alex"，否则输出"Poor Alex"。

翻译提供者：Black_white_tony

## 样例 #1

### 输入

```
2
1 2
2 1

```

### 输出

```
Happy Alex

```



---

---
title: "Fortune Telling"
layout: "post"
diff: 入门
pid: CF59B
tag: ['模拟', '排序', '概率论']
---

# Fortune Telling

## 题目描述

玛丽娜喜欢萨沙。但她一直在想萨沙是否爱她。当然，知道的最好方法就是去占卜。占卜的方法有很多，但是玛丽娜选择了最简单的一个方法。她拿起一只或几只甘菊，一个接一个地掰下花瓣。在每个花瓣之后，她说出“爱”或“不爱”，第一个掰的花瓣后先说“爱”。有 $n$ 朵甘菊在田间生长，它们的花瓣数等于$a_1$，$a_2$，$\ldots$ $a_n$。玛丽娜想挑一束可能有最大花瓣总数的花束，且结果仍然是“爱”。帮她做到这一点：找到花瓣的最大数量可能在哪一个花束中。

## 输入格式

第一行包含一个整数 $n$（$1\leq n\leq 10 0$），这是在田间种植的甘菊数量。第二行包含$n$个整数 $a_i$（$ 1 \leq a_i\leq100$），表示第 $i$ 朵甘菊的花瓣数量。

## 输出格式

输出一个数字，代表花束中最大的花瓣数量，这就会导致“爱”。如果没有这样的花束，请输出$0$。花束可能只由一朵花组成。
感谢@MarshalKen 提供的翻译

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1
2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
5 6 7

```

### 输出

```
13

```



---

---
title: "USB Flash Drives"
layout: "post"
diff: 入门
pid: CF609A
tag: ['模拟', '贪心', '排序']
---

# USB Flash Drives

## 题目描述

Sean正在把一个大文件考到n个U盘里。这个文件足有m MB那么大。第i个U盘的容量是a[i]。
假设Sean能把文件分装到多个U盘中，请求出他最少需要用多少个U盘来考这个文件。

## 输入格式

第一行包括一个整数n(1<=n<=100)-U盘的个数。

第二行包含一个整数m(1<=m<=10^5)-文件的大小。

以下n行每一行包括一个整数a[i] (1<=a[i]<=1000)-第i个U盘的大小。

确定答案出现-也就是说所有a[i]的总和不小于m。

## 输出格式

输出至少要多少U盘。

翻译提供者：sunhaina061031

## 样例 #1

### 输入

```
3
5
2
1
3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
6
2
3
2

```

### 输出

```
3

```

## 样例 #3

### 输入

```
2
5
5
10

```

### 输出

```
1

```



---

---
title: "Wet Shark and Odd and Even"
layout: "post"
diff: 入门
pid: CF621A
tag: ['排序']
---

# Wet Shark and Odd and Even

## 题目描述

Today, Wet Shark is given $ n $ integers. Using any of these integers no more than once, Wet Shark wants to get maximum possible even (divisible by $ 2 $ ) sum. Please, calculate this value for Wet Shark.

Note, that if Wet Shark uses no integers from the $ n $ integers, the sum is an even integer $ 0 $ .

## 输入格式

The first line of the input contains one integer, $ n $ ( $ 1<=n<=100000 $ ). The next line contains $ n $ space separated integers given to Wet Shark. Each of these integers is in range from $ 1 $ to $ 10^{9} $ , inclusive.

## 输出格式

Print the maximum possible even sum that can be obtained if we use some of the given integers.

## 说明/提示

In the first sample, we can simply take all three integers for a total sum of $ 6 $ .

In the second sample Wet Shark should take any four out of five integers $ 999999999 $ .

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
999999999 999999999 999999999 999999999 999999999

```

### 输出

```
3999999996
```



---

---
title: "Triangle"
layout: "post"
diff: 入门
pid: CF6A
tag: ['枚举', '排序', '深度优先搜索 DFS', '排列组合']
---

# Triangle

## 题目描述

给定 $4$ 根木棍的长度，如果它们中存在 $3$ 根木棍可以组成三角形，输出 ```TRIANGLE``` ;如果它们无法组成三角形，但是它们中存在 $3$ 根木棍可以组成退化的三角形(任意两边之和大于等于第三边，但是不是三角形)，输出 ```SEGMENT``` ;否则，输出 ```IMPOSSIBLE``` 。

注意: 木棍不能折断，也不能只用一部分长度。

## 输入格式

一行 $4$ 个整数，$4$ 根木棍的长度。

## 输出格式

如果它们中存在 $3$ 根木棍可以组成三角形，输出 ```TRIANGLE``` ;如果它们无法组成三角形，但是它们中存在3根木棍可以组成退化的三角形，输出 ```SEGMENT``` ;否则，输出 ```IMPOSSIBLE```。

By @PC_DOS

## 样例 #1

### 输入

```
4 2 1 3

```

### 输出

```
TRIANGLE

```

## 样例 #2

### 输入

```
7 2 2 4

```

### 输出

```
SEGMENT

```

## 样例 #3

### 输入

```
3 5 9 1

```

### 输出

```
IMPOSSIBLE

```



---

---
title: "Holiday Of Equality"
layout: "post"
diff: 入门
pid: CF758A
tag: ['模拟', '枚举', '排序']
---

# Holiday Of Equality

## 题目描述

## 题目大意
今天是Berland的平等节。为了庆祝节日，国王决定用国库里的钱来使Berland所有公民的福利均等。

在Berland，有$N$个公民，每个人的福利都被估计为一个整数$a_{i}$ burle（burle是Berland的货币）。

你是皇家财政管理员，你需要计算国王为此要付出的最低费用。国王只能给公民们钱，他没有权力夺走任何钱财。

## 输入格式

输入数据的第一行有一个整数$n$，表示Berland中公民的数量。

数据的第二行包括$n$个整数$a_{1},a_{2},...,a_{n}$，表示每个公民原有的福利。

## 输出格式

输出仅包括一个整数$S$，表示国王最少需要花费$S$ burle。

## 输入输出样例

略

## 说明/提示

第一个样例中，如果我们给第一个公民4 burles，第二个3 burles，第三个2 burles，第四个1 burle，那么所有公民的福利都等于4 burles。

第二个样例中，我们只需要给第三个公民1 burle就可以使得福利均等。

第三个样例中，我们需要分别给第一个和第三个公民2 burles，使得福利都等于3 burles。

第四个样例中，我们不需要给任何人钱因为所有人的福利都是12 burles。


对于100%的数据，$1 \leq n \leq 100$，$0 \leq a_{i} \leq 10^{6}$。

翻译提供者：Simpson561

## 样例 #1

### 输入

```
5
0 1 2 3 4

```

### 输出

```
10
```

## 样例 #2

### 输入

```
5
1 1 0 1 1

```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
1 3 1

```

### 输出

```
4
```

## 样例 #4

### 输入

```
1
12

```

### 输出

```
0
```



---

---
title: "Fair Game"
layout: "post"
diff: 入门
pid: CF864A
tag: ['模拟', '排序']
---

# Fair Game

## 题目描述

Petya and Vasya decided to play a game. They have $ n $ cards ( $ n $ is an even number). A single integer is written on each card.

Before the game Petya will choose an integer and after that Vasya will choose another integer (different from the number that Petya chose). During the game each player takes all the cards with number he chose. For example, if Petya chose number $ 5 $ before the game he will take all cards on which $ 5 $ is written and if Vasya chose number $ 10 $ before the game he will take all cards on which $ 10 $ is written.

The game is considered fair if Petya and Vasya can take all $ n $ cards, and the number of cards each player gets is the same.

Determine whether Petya and Vasya can choose integer numbers before the game so that the game is fair.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=100 $ ) — number of cards. It is guaranteed that $ n $ is an even number.

The following $ n $ lines contain a sequence of integers $ a_{1},a_{2},...,a_{n} $ (one integer per line, $ 1<=a_{i}<=100 $ ) — numbers written on the $ n $ cards.

## 输出格式

If it is impossible for Petya and Vasya to choose numbers in such a way that the game will be fair, print "NO" (without quotes) in the first line. In this case you should not print anything more.

In the other case print "YES" (without quotes) in the first line. In the second line print two distinct integers — number that Petya should choose and the number that Vasya should choose to make the game fair. If there are several solutions, print any of them.

## 说明/提示

In the first example the game will be fair if, for example, Petya chooses number $ 11 $ , and Vasya chooses number $ 27 $ . Then the will take all cards — Petya will take cards $ 1 $ and $ 4 $ , and Vasya will take cards $ 2 $ and $ 3 $ . Thus, each of them will take exactly two cards.

In the second example fair game is impossible because the numbers written on the cards are equal, but the numbers that Petya and Vasya should choose should be distinct.

In the third example it is impossible to take all cards. Petya and Vasya can take at most five cards — for example, Petya can choose number $ 10 $ and Vasya can choose number $ 20 $ . But for the game to be fair it is necessary to take $ 6 $ cards.

## 样例 #1

### 输入

```
4
11
27
27
11

```

### 输出

```
YES
11 27

```

## 样例 #2

### 输入

```
2
6
6

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
6
10
20
30
20
10
20

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
6
1
1
2
2
3
3

```

### 输出

```
NO

```



---

---
title: "Search for Pretty Integers"
layout: "post"
diff: 入门
pid: CF870A
tag: ['模拟', '排序', '剪枝']
---

# Search for Pretty Integers

## 题目描述

You are given two lists of non-zero digits.

Let's call an integer pretty if its (base $ 10 $ ) representation has at least one digit from the first list and at least one digit from the second list. What is the smallest positive pretty integer?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=9 $ ) — the lengths of the first and the second lists, respectively.

The second line contains $ n $ distinct digits $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=9 $ ) — the elements of the first list.

The third line contains $ m $ distinct digits $ b_{1},b_{2},...,b_{m} $ ( $ 1<=b_{i}<=9 $ ) — the elements of the second list.

## 输出格式

Print the smallest pretty integer.

## 说明/提示

In the first example $ 25 $ , $ 46 $ , $ 24567 $ are pretty, as well as many other integers. The smallest among them is $ 25 $ . $ 42 $ and $ 24 $ are not pretty because they don't have digits from the second list.

In the second example all integers that have at least one digit different from $ 9 $ are pretty. It's obvious that the smallest among them is $ 1 $ , because it's the smallest positive integer.

## 样例 #1

### 输入

```
2 3
4 2
5 7 6

```

### 输出

```
25

```

## 样例 #2

### 输入

```
8 8
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1

```

### 输出

```
1

```



---

---
title: "Perfect Squares"
layout: "post"
diff: 入门
pid: CF914A
tag: ['模拟', '枚举', '排序']
---

# Perfect Squares

## 题目描述

Given an array $ a_{1},a_{2},...,a_{n} $ of $ n $ integers, find the largest number in the array that is not a perfect square.

A number $ x $ is said to be a perfect square if there exists an integer $ y $ such that $ x=y^{2} $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of elements in the array.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{6}<=a_{i}<=10^{6} $ ) — the elements of the array.

It is guaranteed that at least one element of the array is not a perfect square.

## 输出格式

Print the largest number in the array which is not a perfect square. It is guaranteed that an answer always exists.

## 说明/提示

In the first sample case, $ 4 $ is a perfect square, so the largest number in the array that is not a perfect square is $ 2 $ .

## 样例 #1

### 输入

```
2
4 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
8
1 2 4 8 16 32 64 576

```

### 输出

```
32

```



---

---
title: "Supermarket"
layout: "post"
diff: 入门
pid: CF919A
tag: ['数学', '贪心', '排序']
---

# Supermarket

## 题目描述

We often go to supermarkets to buy some fruits or vegetables, and on the tag there prints the price for a kilo. But in some supermarkets, when asked how much the items are, the clerk will say that $ a $ yuan for $ b $ kilos (You don't need to care about what "yuan" is), the same as $ a/b $ yuan for a kilo.

Now imagine you'd like to buy $ m $ kilos of apples. You've asked $ n $ supermarkets and got the prices. Find the minimum cost for those apples.

You can assume that there are enough apples in all supermarkets.

## 输入格式

The first line contains two positive integers $ n $ and $ m $ ( $ 1<=n<=5000 $ , $ 1<=m<=100 $ ), denoting that there are $ n $ supermarkets and you want to buy $ m $ kilos of apples.

The following $ n $ lines describe the information of the supermarkets. Each line contains two positive integers $ a,b $ ( $ 1<=a,b<=100 $ ), denoting that in this supermarket, you are supposed to pay $ a $ yuan for $ b $ kilos of apples.

## 输出格式

The only line, denoting the minimum cost for $ m $ kilos of apples. Please make sure that the absolute or relative error between your answer and the correct answer won't exceed $ 10^{-6} $ .

Formally, let your answer be $ x $ , and the jury's answer be $ y $ . Your answer is considered correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919A/9c418c1ac059184ac2ec8107da47a63db7a44091.png).

## 说明/提示

In the first sample, you are supposed to buy $ 5 $ kilos of apples in supermarket $ 3 $ . The cost is $ 5/3 $ yuan.

In the second sample, you are supposed to buy $ 1 $ kilo of apples in supermarket $ 2 $ . The cost is $ 98/99 $ yuan.

## 样例 #1

### 输入

```
3 5
1 2
3 4
1 3

```

### 输出

```
1.66666667

```

## 样例 #2

### 输入

```
2 1
99 100
98 99

```

### 输出

```
0.98989899

```



---

---
title: "Game"
layout: "post"
diff: 入门
pid: CF984A
tag: ['模拟', '排序']
---

# Game

## 题目描述

Two players play a game.

Initially there are $ n $ integers $ a_1, a_2, \ldots, a_n $ written on the board. Each turn a player selects one number and erases it from the board. This continues until there is only one number left on the board, i. e. $ n - 1 $ turns are made. The first player makes the first move, then players alternate turns.

The first player wants to minimize the last number that would be left on the board, while the second player wants to maximize it.

You want to know what number will be left on the board after $ n - 1 $ turns if both players make optimal moves.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 1000 $ ) — the number of numbers on the board.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ).

## 输出格式

Print one number that will be left on the board.

## 说明/提示

In the first sample, the first player erases $ 3 $ and the second erases $ 1 $ . $ 2 $ is left on the board.

In the second sample, $ 2 $ is left on the board regardless of the actions of the players.

## 样例 #1

### 输入

```
3
2 1 3

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
2 2 2

```

### 输出

```
2
```



---

