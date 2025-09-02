---
title: "[USACO1.1] 你的飞碟在这儿 Your Ride Is Here"
layout: "post"
diff: 入门
pid: P1200
tag: ['字符串', '数学', 'USACO']
---
# [USACO1.1] 你的飞碟在这儿 Your Ride Is Here
## 题目描述

众所周知，在每一个彗星后都有一只 UFO。这些 UFO 时常来收集地球上的忠诚支持者。不幸的是，他们的飞碟每次出行都只能带上一组支持者。因此，他们要用一种聪明的方案让这些小组提前知道谁会被彗星带走。他们为每个彗星起了一个名字，通过这些名字来决定这个小组是不是被带走的那个特定的小组（你认为是谁给这些彗星取的名字呢？）。关于如何搭配的细节会在下面告诉你；你的任务是写一个程序，通过小组名和彗星名来决定这个小组是否能被那颗彗星后面的 UFO 带走。


小组名和彗星名都以下列方式转换成一个数字：最终的数字就是名字中所有字母的积，其中 $\texttt A$ 是 $1$，$\texttt Z$ 是 $26$。例如，$\texttt{USACO}$ 小组就是 $21 \times 19 \times 1 \times 3 \times 15=17955$。如果小组的数字 $\bmod 47$ 等于彗星的数字 $\bmod 47$,你就得告诉这个小组需要准备好被带走！（记住“$a \bmod b$”是 $a$ 除以 $b$ 的余数，例如 $34 \bmod 10$ 等于 $4$）


写出一个程序，读入彗星名和小组名并算出用上面的方案能否将两个名字搭配起来，如果能搭配，就输出 `GO`，否则输出 `STAY`。小组名和彗星名均是没有空格或标点的一串大写字母（不超过 $6$ 个字母）。


## 输入格式

第1行：一个长度为 $1$ 到 $6$ 的大写字母串，表示彗星的名字。

第2行：一个长度为 $1$ 到 $6$ 的大写字母串，表示队伍的名字。

## 样例

### 样例输入 #1
```
COMETQ
HVNGAT
```
### 样例输出 #1
```
GO
```
### 样例输入 #2
```
ABSTAR
USACO
```
### 样例输出 #2
```
STAY
```
## 提示

题目翻译来自 NOCOW。

USACO Training Section 1.1



---

---
title: "梦中的统计"
layout: "post"
diff: 入门
pid: P1554
tag: ['模拟', '字符串', '数学', 'USACO']
---
# 梦中的统计
## 题目背景

Bessie 处于半梦半醒的状态。过了一会儿，她意识到她在数数，不能入睡。
## 题目描述

Bessie 的大脑反应灵敏，仿佛真实地看到了她数过的一个又一个数。她开始注意每一个数码（$0 \ldots 9$）：每一个数码在计数的过程中出现过多少次？

给出两个整数 $M$ 和 $N$，求在序列 $[M, M + 1, M + 2, \ldots, N - 1, N]$ 中每一个数码出现了多少次。
## 输入格式

第 $1$ 行: 两个用空格分开的整数 $M$ 和 $N$。
## 输出格式

第 $1$ 行: 十个用空格分开的整数，分别表示数码 $0 \ldots 9$ 在序列中出现的次数。
## 样例

### 样例输入 #1
```
129 137
```
### 样例输出 #1
```
1 10 2 9 1 1 1 1 0 1
```
## 提示

数据保证，$1 \leq M \leq N \leq 2 \times 10^9$，$N-M \leq 5 \times 10^5$。


---

---
title: "[USACO18FEB] Teleportation B"
layout: "post"
diff: 入门
pid: P1639
tag: ['贪心', '2018', 'USACO', 'O2优化']
---
# [USACO18FEB] Teleportation B
## 题目描述

Farmer John 最讨厌的农活是运输牛粪。为了精简这个过程，他制造了一个伟大的发明：便便传送门！与使用拖拉机拖着装满牛粪的大车从一个地点到另一个地点相比，他可以使用便便传送门将牛粪从一个地点瞬间传送到另一个地点。

Farmer John 的农场沿着一条长直道路而建，所以他农场上的每个地点都可以简单地用该地点在道路上的位置来表示（相当于数轴上的一个点）。一个传送门可以用两个数 $x$ 和 $y$ 表示，被拖到地点 $x$ 的牛粪可以瞬间传送到地点 $y$，反之亦然。

Farmer John 想要将牛粪从地点 $a$ 运输到地点 $b$，他建造了一个可能对这一过程有所帮助的传送门（当然，如果没有帮助，他也可以不用）。请帮助他求出他需要使用拖拉机运输牛粪的总距离的最小值。 
## 输入格式

输入仅包含一行，为四个用空格分隔的整数：$a$ 和 $b$，表示起始地点和结束地点，后面是 $x$ 和 $y$，表示传送门。所有的位置都是范围为 $0\ldots 100$ 的整数，不一定各不相同。
## 输出格式

输出一个整数，为 Farmer John 需要用拖拉机运输牛粪的最小距离。 
## 样例

### 样例输入 #1
```
3 10 8 2
```
### 样例输出 #1
```
3
```
## 提示

在这个样例中，最佳策略是将牛粪从位置 $3$ 运到位置 $2$，传送到位置 $8$，再运到位置 $10$。 所以需要用拖拉机的总距离为 $1 + 2 = 3$。


---

---
title: "[USACO18JAN] Lifeguards B"
layout: "post"
diff: 入门
pid: P1697
tag: ['模拟', '2018', 'USACO', 'O2优化']
---
# [USACO18JAN] Lifeguards B
## 题目背景

本题翻译来自 deepseek-v3。
## 题目描述

Farmer John 为他的奶牛们开设了一个游泳池，认为这将帮助它们放松并产更多的奶。

为了确保安全，他雇佣了 $N$ 头奶牛作为救生员，每头奶牛的班次覆盖一天中的某个连续时间段。为简单起见，游泳池每天从时间 $t=0$ 开放到时间 $t=1000$，因此每个班次可以用两个整数描述，分别表示奶牛开始和结束其班次的时间。例如，一头救生员从时间 $t=4$ 开始到时间 $t=7$ 结束，覆盖了 $3$ 个单位的时间（注意端点表示时间点）。

不幸的是，Farmer John 多雇佣了 $1$ 名救生员，超出了他的资金支持范围。鉴于他必须解雇恰好 $1$ 名救生员，剩下的救生员的班次能够覆盖的最长时间是多少？如果至少有一名救生员在场，则某个时间段被视为被覆盖。
## 输入格式

输入的第一行包含 $N$（$1 \leq N \leq 100$）。接下来的 $N$ 行每行描述一名救生员，用两个范围在 $0 \ldots 1000$ 的整数表示该救生员班次的开始和结束时间。所有端点都是唯一的。不同救生员的班次可能会重叠。
## 输出格式

请输出一个数字，表示如果 Farmer John 解雇 $1$ 名救生员后，剩下的救生员的班次能够覆盖的最长时间。
## 样例

### 样例输入 #1
```
3
5 9
1 4
3 7
```
### 样例输出 #1
```
7
```


---

---
title: "第一次，第二次，成交！"
layout: "post"
diff: 入门
pid: P2637
tag: ['模拟', 'USACO', '枚举']
---
# 第一次，第二次，成交！
## 题目描述

因为奶牛们的节食运动给 FJ 余下了一大批干草无法处理，所以他准备要开一个拍卖会去出售他的干草。

他有 $n$ 批干草。他的客户有 $m$ 个，都是和他一样的农夫。第 $i$ 名农夫会告诉 FJ 他会为 FJ 的每批干草付 $p_i$ 的钱。每个农夫都想买（也只想买）FJ 的一批草料。

为了确保农夫们不会互相嫉妒，所以 FJ 决定要以一个固定的价格出售他的草料。每一个出价大于等于 FJ 的要价的农夫将会买到草料。

请你帮助 FJ 找出能让他卖出最多的钱的最低的单批草料的售价。
## 输入格式

第一行：两个被空格隔开的整数，$n$ 和 $m$。

第二行到第 $m+1$ 行：第 $i+1$ 行只包含一个整数：$p_i$。
## 输出格式

共一行，包含由空格隔开的两个整数：FJ 能出的每批草料的最低价格，以及他能赚到的最多的钱。

## 样例

### 样例输入 #1
```
5 4
2
8
10
7
```
### 样例输出 #1
```
7 21
```
## 提示

FJ 有 $5$ 批草料，$4$ 个农夫想要购买。他们出价分别为：每批草料为 $2$，$8$，$10$ 和 $7$。

FJ 应该把价格设定为 $7$，这样会有 $3$ 个农夫会付钱买草料，FJ 自己会挣到 $21$ 的钱。

---

对于 $100\%$ 的数据，$1\leq m, n\leq 1000$，$1\leq p_i\leq 1,000,000$。


---

---
title: "[USACO07DEC] Bookshelf B"
layout: "post"
diff: 入门
pid: P2676
tag: ['贪心', '2007', 'USACO', '排序']
---
# [USACO07DEC] Bookshelf B
## 题目描述

Farmer John 最近为奶牛们的图书馆添置了一个巨大的书架，尽管它是如此的大，但它还是几乎瞬间就被各种各样的书塞满了。现在，只有书架的顶上还留有一点空间。 

所有 $N(1 \le N \le 20,000)$ 头奶牛都有一个确定的身高 $H_i(1 \le H_i \le 10,000)$。设所有奶牛身高的和为S。书架的高度为 $B$，并且保证 $1 \le B \le S < 2,000,000,007$。 

为了够到比最高的那头奶牛还要高的书架顶，奶牛们不得不像演杂技一般，一头站在另一头的背上，叠成一座“奶牛塔”。当然，这个塔的高度，就是塔中所有奶牛的身高之和。为了往书架顶上放东西，所有奶牛的身高和必须不小于书架的高度。

显然，塔中的奶牛数目越多，整座塔就越不稳定，于是奶牛们希望在能够到书架顶的前提下，让塔中奶牛的数目尽量少。 现在，奶牛们找到了你，希望你帮她们计算这个最小的数目。

## 输入格式

* 第 $1$ 行: 2 个用空格隔开的整数：$N$ 和 $B$；
* 第 $2\dots N+1$ 行: 第 $i+1$ 行是 $1$ 个整数：$H_i$。

## 输出格式

* 第 $1$ 行: 输出 $1$ 个整数，即最少要多少头奶牛叠成塔，才能够到书架顶部

## 样例

### 样例输入 #1
```
6 40
6
18
11
13
19
11
```
### 样例输出 #1
```
3
```
## 提示

输入说明:

一共有 $6$ 头奶牛，书架的高度为 $40$，奶牛们的身高在 $6\dots19$之间。


输出说明:

一种只用 $3$ 头奶牛就达到高度 $40$ 的方法：$18+11+13$。当然还有其他方法，在此不一一列出了。



---

---
title: "[USACO08OPEN] Roads Around The Farm S"
layout: "post"
diff: 入门
pid: P2907
tag: ['2008', 'USACO']
---
# [USACO08OPEN] Roads Around The Farm S
## 题目描述

Farmer John's cows have taken an interest in exploring the territory around the farm. Initially, all N (1 <= N <= 1,000,000,000) cows commence traveling down a road in one big group. Upon encountering a fork in the road, the group sometimes chooses to break into two smaller (nonempty) groups with each group continuing down one of the roads.  When one of those groups arrives at another fork, it might split again, and so on.

The cows have crafted a peculiar way of splitting: if they can split into two groups such that the sizes of the groups differ by exactly K (1 <= K <= 1000), then they will split in that way; otherwise, they stop exploring and just start grazing peacefully.

Assuming that there will always be new forks in the road, compute the final number of groups of peacefully grazing cows.
## 输入格式

\* Line 1: Two space-separated integers: N and K

## 输出格式

\* Line 1: A single integer representing the number of groups of grazing cows

## 样例

### 样例输入 #1
```
6 2 

```
### 样例输出 #1
```
3 

```
## 提示

There are 6 cows and the difference in group sizes is 2.


There are 3 final groups (with 2, 1, and 3 cows in them). 

6
/ \
2   4
/ \
1   3
## 题目翻译

约翰的 $ N $ 只奶牛要出发去探索牧场四周的土地。它们将沿着一条路走，一直走到三岔路口（可以认为所有的路口都是这样的）。这时候，这一群奶牛可能会分成两群，分别沿着接下来的两条路继续走。如果她们再次走到三岔路口，那么仍有可能继续分裂成两群继续走。 

奶牛的分裂方式十分古怪：  

如果这一群奶牛可以精确地分成两部分，这两部分的牛数恰好相差 $ K $ 头，那么在三岔路口牛群就会分裂。

否则，牛群不会分裂，她们都将在这里待下去，平静地吃草。 请计算，最终将会有多少群奶牛在平静地吃草。

数据范围：

$ 1 \le N \le 10^{9}$ 

$ 1 \le K \le 10^{3}$


---

---
title: "[USACO08OCT] Bovine Bones G"
layout: "post"
diff: 入门
pid: P2911
tag: ['2008', 'USACO', '枚举', '期望']
---
# [USACO08OCT] Bovine Bones G
## 题目描述

Bessie loves board games and role-playing games so she persuaded Farmer John to drive her to the hobby shop where she purchased three dice for rolling. These fair dice have S1, S2, and S3 sides

respectively (2 <= S1 <= 20; 2 <= S2 <= 20; 2 <= S3 <= 40). 

Bessie rolls and rolls and rolls trying to figure out which three-dice sum appears most often.

Given the number of sides on each of the three dice, determine which three-dice sum appears most frequently. If more than one sum can appear most frequently, report the smallest such sum.

POINTS: 70

## 输入格式

\* Line 1: Three space-separated integers: S1, S2, and S3

## 输出格式

\* Line 1: The smallest integer sum that appears most frequently when the dice are rolled in every possible combination.

## 样例

### 样例输入 #1
```
3 2 3 

```
### 样例输出 #1
```
5 

```
## 提示

Here are all the possible outcomes.

```
1 1 1 -> 3  
1 2 1 -> 4  
2 1 1 -> 4  
2 2 1 -> 5  
3 1 1 -> 5  
3 2 1 -> 6 
1 1 2 -> 4  
1 2 2 -> 5  
2 1 2 -> 5  
2 2 2 -> 6  
3 1 2 -> 6  
3 2 2 -> 7 
1 1 3 -> 5  
1 2 3 -> 6  
2 1 3 -> 6  
2 2 3 -> 7  
3 1 3 -> 7  
3 2 3 -> 8
```
Both 5 and 6 appear most frequently (five times each), so 5 is the answer.

## 题目翻译

贝茜喜欢玩棋盘游戏和角色扮演游戏，所以她说服了约翰开车带她去小商店.在那里她买了三个骰子。这三个不同的骰子的面数分别为 $s_1,s_2,s_3$。

对于一个有 $S$ 个面的骰子每个面上的数字是 $1,2,3,\ldots,S$。每个面（上的数字）出现的概率均等。贝茜希望找出在所有“三个面上的数字的和”中，哪个和的值出现的概率最大。

现在给出每个骰子的面数，需要求出哪个所有“三个面上的数字的和”出现得最频繁。如果有很多个和出现的概率相同，那么只需要输出最小的那个。

数据范围： $2\le s_1\leq 20$，$2 \leq s_2\leq 20$，$2 \leq s_3\leq 40$。


---

---
title: "[USACO09OCT] Even? Odd? G"
layout: "post"
diff: 入门
pid: P2955
tag: ['2009', 'USACO']
---
# [USACO09OCT] Even? Odd? G
## 题目描述

Bessie's cruel second grade teacher has assigned a list of N (1 <= N <= 100) positive integers I (1 <= I <= 10^60) for which Bessie must determine their parity (explained in second grade as 'Even... or odd?'). Bessie is overwhelmed by the size of the list and by the size of the numbers. After all, she only learned to count recently.

Write a program to read in the N integers and print 'even' on a single line for even numbers and likewise 'odd' for odd numbers.

POINTS: 25

Bessie那惨无人道的二年级老师搞了一个有 N 个正整数 I 的表叫Bessie去判断“奇偶性”（这个词语意思向二年级的学生解释，就是“这个数是单数，还是双数啊？”）。Bessie被那个表的长度深深地震惊到了，竟然跟栋栋的泛做表格一样多道题！！！毕竟她才刚刚学会数数啊。

写一个程序读入N个整数，如果是双数，那么在单立的一行内输出"even"，如果是单数则类似地输出"odd".

数据范围：每个正整数不超过 ${10}^{60}$。
## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line j+1 contains I\_j, the j-th integer to determine even/odd

## 输出格式

\* Lines 1..N: Line j contains the word 'even' or 'odd', depending on the parity of I\_j

## 样例

### 样例输入 #1
```
2 
1024 
5931 

```
### 样例输出 #1
```
even 
odd 

```
## 提示

Two integers: 1024 and 5931


1024 is eminently divisible by 2; 5931 is not 




---

---
title: "[USACO09OCT] The Robot Plow G"
layout: "post"
diff: 入门
pid: P2956
tag: ['2009', 'USACO']
---
# [USACO09OCT] The Robot Plow G
## 题目描述

Farmer John has purchased a new robotic plow in order to relieve him from the drudgery of plowing field after field after field. It achieves this goal but at a slight disadvantage: the robotic plow can only plow in a perfect rectangle with sides of integer length.

Because FJ's field has trees and other obstacles, FJ sets up the plow to plow many different rectangles, which might end up overlapping. He's curious as to just how many squares in his field are actually plowed after he programs the plow with various plow instructions, each of which describes a rectangle by giving its lower left and upper right x,y coordinates.

As usual, the field is partitioned into squares whose sides are parallel to the x and y axes. The field is X squares wide and Y squares high (1 <= X <= 240; 1 <= Y <= 240). Each of the I (1 <= I <= 200) plow instructions comprises four integers: Xll, Yll, Xur, and Yur (1 <= Xll <= Xur; Xll <= Xur <= X; 1 <= Yll <= Yur; Yll <= Yur <= Y) which are the lower left and upper right coordinates of the rectangle to be plowed. The plow will plow all the field's squares in the range (Xll..Xur, Yll..Yur) which might be one more row and column than would initially be assumed (depending on how you go about your assumptions, of course).

Consider a field that is 6 squares wide and 4 squares high. As FJ issues a pair of plowing instructions (shown), the field gets plowed as shown by '\*' and '#' (normally plowed field all looks the same, but '#' shows which were most recently plowed):

```cpp
......             **....             #####. 
......  (1,1)(2,4) **....  (1,3)(5,4) #####. 
......             **....             **.... 
......             **....             **.... 
```
A total of 14 squares are plowed.

POINTS: 25

Farmer John为了让自己从无穷无尽的犁田工作中解放出来，于是买了个新机器人帮助他犁田。这个机器人可以完成犁田的任务，可惜有一个小小的缺点：这个犁田机器人一次只能犁一个边的长度是整数的长方形的田地。

因为FJ的田地有树和其它障碍物，所以FJ设定机器人去犁很多不同的长方形。这些长方形允许重叠。他给机器人下了P个指令，每个指令包含一个要犁长方形的地。这片田地由长方形的左下角和右上角坐标决定。他很好奇最后到底有多少个方格的地被犁过了。

一般来说，田地被分割为很多小方格。这些方格的边和x轴或y轴平行。田地的宽度为X个方格，高度为Y个方格 (1 <= X <= 240; 1 <= Y <= 240). FJ执行了I (1 <= I <= 200)个指令，每个指令包含4个整数：Xll, Yll, Xur, Yur (1 <= Xll <= Xur; Xll <= Xur <=X; 1 <= Yll <= Yur; Yll <= Yur <= Y), 分别是要犁的长方形的左下角坐标和右上角坐标。机器人会犁所有的横坐标在Xll..Xur并且纵坐标在Yll..Yur范围内的所有方格的地。可能这个长方形会比你想象的多一行一列（就是说从第Xll列到第Xur列一共有Xur - Xll + 1列而不是Xur - Xll列）。

考虑一个6方格宽4方格高的田地。FJ进行了2个操作（如下），田地就被犁成"\*"和"#"了。虽然一般被犁过的地看起来都是一样的。但是标成"#"可以更清晰地看出最近一次被犁的长方形。

一共14个方格的地被犁过了。

## 输入格式

\* Line 1: Three space-separated integers: X, Y, and I

\* Lines 2..I+1: Line i+1 contains plowing instruction i which is described by four integers: Xll, Yll, Xur, and Yur

## 输出格式

\* Line 1: A single integer that is the total number of squares plowed

## 样例

### 样例输入 #1
```
6 4 2 
1 1 2 4 
1 3 5 4 

```
### 样例输出 #1
```
14 

```
## 提示

As in the task's example.



---

---
title: "[USACO19DEC] Cow Gymnastics B"
layout: "post"
diff: 入门
pid: P5831
tag: ['2019', 'USACO', '枚举']
---
# [USACO19DEC] Cow Gymnastics B
## 题目描述

为了提高健康水平，奶牛们开始进行体操训练了！Farmer John 选定了他最喜爱的奶牛 Bessie 来执教其他 $N$ 头奶牛，同时评估她们学习不同的体操技术的进度。

$K$ 次训练课的每一次，Bessie 都会根据 $N$ 头奶牛的表现给她们进行排名。之后，她对这些排名的一致性产生了好奇。称一对不同的奶牛是**一致的**，如果其中一头奶牛在每次训练课中都表现得都比另一头要好。

请帮助 Bessie 计算一致的奶牛的对数。
## 输入格式

输入的第一行包含两个正整数 $K$ 和 $N$。以下 $K$ 行每行包含整数 $1 \ldots N$ 的某种排列，表示奶牛们的排名（奶牛们用编号 $1 \ldots N$ 进行区分）。如果在某一行中 $A$ 出现在 $B$ 之前，表示奶牛 $A$ 表现得比奶牛 $B$ 要好。
## 输出格式

输出一行，包含一致的奶牛的对数。
## 样例

### 样例输入 #1
```
3 4
4 1 2 3
4 1 3 2
4 2 1 3
```
### 样例输出 #1
```
4
```
## 提示

一致的奶牛对为 $(1,4)$、$(2,4)$、$(3,4)$ 和 $(1,3)$。

$1 \leq K \leq 10$，$1 \leq N \leq 20$。

供题：Nick Wu


---

---
title: "[USACO19DEC] Where Am I? B"
layout: "post"
diff: 入门
pid: P5832
tag: ['字符串', '2019', 'USACO']
---
# [USACO19DEC] Where Am I? B
## 题目描述

Farmer John 出门沿着马路散步，但是他现在发现可能迷路了！

沿路有一排共 $N$ 个农场。不幸的是农场并没有编号，这使得 Farmer John 难以分辨他在这条路上所处的位置。然而，每个农场都沿路设有一个彩色的邮箱，所以 Farmer John 希望能够通过查看最近的几个邮箱的颜色来唯一确定他所在的位置。

每个邮箱的颜色用 A..Z 之间的一个字母来指定，所以沿着道路的 $N$ 个邮箱的序列可以用一个长为 $N$ 的由字母 A..Z 组成的字符串来表示。某些邮箱可能会有相同的颜色。Farmer John 想要知道最小的 $K$ 的值，使得他查看任意连续 $K$ 个邮箱序列，他都可以唯一确定这一序列在道路上的位置。

例如，假设沿路的邮箱序列为 `ABCDABC` 。Farmer John 不能令 $K=3$，因为如果他看到了 `ABC`，沿路有两个这一连续颜色序列可能所在的位置。最小可行的 $K$ 的值为 $K=4$，因为如果他查看任意连续 4 个邮箱，这一颜色序列可以唯一确定他在道路上的位置。
## 输入格式

输入的第一行包含 $N$，第二行包含一个由 $N$ 个字符组成的字符串，每个字符均在 A..Z 之内。
## 输出格式

输出一行，包含一个整数，为可以解决 Farmer John 的问题的最小 $K$ 值。
## 样例

### 样例输入 #1
```
7
ABCDABC
```
### 样例输出 #1
```
4
```
## 提示

$1 \leq N \leq 100$。


---

---
title: "[USACO06OCT] Another Cow Number Game G"
layout: "post"
diff: 入门
pid: P6206
tag: ['模拟', '2006', 'USACO']
---
# [USACO06OCT] Another Cow Number Game G
## 题目描述

奶牛们在玩一种数字游戏，Bessie 想让你帮她预测一下结果。游戏开始时，Bessie 将得到一个正整数 $N$。此时她的分数为 $0$。

奶牛们按照以下规则对 $N$ 进行变换：

- 如果 $N$ 是奇数，那么将它乘以 $3$ 后再加 $1$。
- 如果 $N$ 是偶数，那么将它除以 $2$。

数字每变换一次，Bessie 就得到 $1$ 分。当 $N=1$ 时，游戏结束。此时的分数就是她的最终得分。
## 输入格式

一行，一个整数 $N$。
## 输出格式

一行，一个整数，为 Bessie 的最终得分。
## 样例

### 样例输入 #1
```
5
```
### 样例输出 #1
```
5
```
## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le N\le 10^6$。

------------

**【样例说明】**

当 $N$ 的初始值为 $5$ 时，游戏的过程如下：

| $N$ | 变换后的数字 | 变换过程 | 总分 |
| :----------: | :----------: | :----------: | :----------: |
| $5$ | $16$ | $3\times 5+1$ | $1$ |
| $16$ | $8$ | $16\div 2$ | $2$ |
| $8$ | $4$ | $8\div 2$ | $3$ |
| $4$ | $2$ | $4\div 2$ | $4$ |
| $2$ | $1$ | $2\div 2$ | $5$ |

Bessie 的最终得分为 $5$。



---

---
title: "[USACO22JAN] Herdle B"
layout: "post"
diff: 入门
pid: P8090
tag: ['模拟', 'USACO', '2022']
---
# [USACO22JAN] Herdle B
## 题目描述

奶牛们发明了一种名为 Herdle 的新型解谜游戏，在牛界引起了轰动。

每天都会有一个新谜题发布供奶牛解决。游戏采用 $3\times 3$ 方阵的形式表示农场的一块田地，田地的每个方格都由特定品种的奶牛占据。总共只有 $26$ 种可能的品种，每一种由 $\text{A}$ 到 $\text{Z}$ 中的不同大写字母标识。玩家不会被告知田地中的奶牛品种排列方式——游戏目标是通过一系列猜测确定它们。

每次猜测，奶牛们输入一个 $3\times 3$ 的大写字母方阵，表示该田地可以用奶牛填充的可能方式。猜测的某些方格可能是正确的。这些方格以绿色高亮显示，让奶牛们知道这些是正确的。猜测的另一些方格可能填入了品种正确但位置错误的奶牛。这些以黄色高亮显示。

黄色高亮显示的方格的数量可以帮助指示某个品种的奶牛数量。 例如，假设猜测方阵包含 $4$ 头品种 $\text{A}$ 的奶牛，而答案方阵包含 $2$ 只品种 $\text{A}$ 的奶牛，其中没有正确位置上的 $\text{A}$ （即，它们都不应该是绿色的）。 在这种情况下，猜测方阵中只有两个 $\text{A}$ 应以黄色高亮显示。 更准确地说，如果猜测方阵中有 $x$ 个特定品种的奶牛，并且 答案方阵中有 $y \le x$ 头该品种奶牛（不包括位置正确而得到绿色高亮显示的奶牛），那么猜测方阵的 $x$ 头奶牛中只有 $y$ 头奶牛应该以黄色高亮显示。

给定正确答案的方阵和一个表示对该答案的猜测的方阵，请计算绿色和黄色高亮显示的方格的数量。
## 输入格式

输入的前 3 行给定了正确答案的方阵。以下 3 行表示对该答案的猜测。
## 输出格式

输出两行。输出的第一行包含应当以绿色高亮显示的方格的数量。输出的第二行包含应当以黄色高亮显示的方格的数量。

## 样例

### 样例输入 #1
```
COW
SAY
MOO
WIN
THE
IOI
```
### 样例输出 #1
```
1
1

```
### 样例输入 #2
```
AAA
BBB
CCC
AYY
AAA
ZZZ
```
### 样例输出 #2
```
1
2
```
## 提示

【样例解释 1】

在这个例子中，最后一行中间的 O 是正确的，所以这个方格以绿色高亮显示。字母 W 位于错误的位置，所以它以黄色高亮显示。

【样例解释 2】

在这里，其中一个 A 位于正确的位置，所以它以绿色高亮显示。余下的 A 均不在正确位置上，由于答案方阵中有两个 A，所以有两个 A 应当以黄色高亮显示。




---

---
title: "[USACO21JAN] Uddered but not Herd B"
layout: "post"
diff: 入门
pid: P9940
tag: ['模拟', 'USACO', '2021', 'O2优化']
---
# [USACO21JAN] Uddered but not Herd B
## 题目描述

一个鲜为人知的事实是，奶牛拥有自己的文字：「牛文」。牛文由 $26$ 个字母 `a` 到 `z` 组成，但是当奶牛说牛文时，可能与我们所熟悉的 `abcdefghijklmnopqrstuvwxyz` 不同，她会按某种特定的顺序排列字母。

为了打发时间，奶牛 Bessie 在反复哼唱牛文字母歌，而 Farmer John 好奇她唱了多少遍。

给定一个小写字母组成的字符串，为 Farmer John 听到 Bessie 唱的字母，计算 Bessie 至少唱了几遍完整的牛文字母歌，使得 Farmer John 能够听到给定的字符串。Farmer John 并不始终注意 Bessie 所唱的内容，所以他可能会漏听 Bessie 唱过的一些字母。给定的字符串仅包含他记得他所听到的字母。 
## 输入格式

输入的第一行包含 $26$ 个小写字母 `a` 到 `z` 的牛文字母表顺序。下一行包含一个小写字母组成的字符串，为 Farmer John 听到 Bessie 唱的字母。字符串的长度不小于 $1$ 且不大于 $1000$。
## 输出格式

输出 Bessie 所唱的完整的牛文字母歌的最小次数。 
## 样例

### 样例输入 #1
```
abcdefghijklmnopqrstuvwxyz
mood
```
### 样例输出 #1
```
3
```
## 提示

### 样例解释 1

在这个样例中，牛文字母表与日常的字母表的排列一致。

Bessie 至少唱了三遍牛文字母歌。有可能 Bessie 只唱了三遍牛文字母歌，而 Farmer John 听到了以下被标记为大写的字母。

`abcdefghijklMnOpqrstuvwxyz`  
`abcdefghijklmnOpqrstuvwxyz`  
`abcDefghijklmnopqrstuvwxyz`  

### 测试点性质

- 测试点 $2-5$ 中，牛文字母表与日常的字母表相同。
- 测试点 $6-10$ 没有额外限制。


---

---
title: "[USACO20JAN] Word Processor B"
layout: "post"
diff: 入门
pid: P9946
tag: ['模拟', '字符串', '2020', 'USACO', 'O2优化']
---
# [USACO20JAN] Word Processor B
## 题目描述

奶牛 Bessie 正在完成她的写作课的一篇作文。由于她写字很难看，她决定用一个文字处理器来输入这篇作文。

这篇作文共有 $N$ 个单词（$1\le N\le 100$），用空格分隔。每个单词的长度在 $1$ 到 $15$ 之间，仅由大写和小写字母组成。根据作业的要求，这篇作文需要用一种特别的方式排版：每一行包含的字符不超过 $K$ 个（$1\le K\le 80$），空格不计。幸好 Bessie 的文字处理器能够处理这样的要求，它会按照如下的方式：

 - 如果 Bessie 输入了一个单词，这个单词能够放进当前行，就放在当前行。
 - 否则，将这个单词放到下一行，然后继续向下一行添加单词。

当然，同一行中的单词之间仍然用一个空格分隔。每一行的结尾都不应当有空格。

很不幸，Bessie 的文字处理器刚好坏了。请帮助她正确地排版她的作文！ 
## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $K$。

下一行包含 $N$ 个单词，单词之间用单个空格分隔。所有单词的长度都不超过一行中的字符上限数 $K$。 
## 输出格式

输出正确排版的 Bessie 的作文。
## 样例

### 样例输入 #1
```
10 7
hello my name is Bessie and this is my essay
```
### 样例输出 #1
```
hello my
name is
Bessie
and this
is my
essay
```
## 提示

### 样例解释 1

第一行包含 $7$ 个非空格字符，包括 `hello` 以及 `my`。再加入 `name` 会使得第一行包含 $11>7$ 个非空格字符，所以这个单词会被放到下一行。


---

---
title: "[USACO20FEB] Mad Scientist B"
layout: "post"
diff: 入门
pid: P9950
tag: ['2020', 'USACO', 'O2优化', '双指针 two-pointer']
---
# [USACO20FEB] Mad Scientist B
## 题目描述

Farmer John 的远房亲戚 Ben 是一个疯狂的科学家。通常这会在家庭聚会时造成不小的摩擦，但这偶尔也会带来些好处，尤其是当 Farmer John 发现他正面对一些有关他的奶牛们的独特而不寻常的问题时。

Farmer John 当前正面对一个有关她的奶牛们的独特而不寻常的问题。他最近订购了 $N$ 头奶牛（$1\le N\le 1000$），包含两种不同品种：荷斯坦牛和更赛牛。他在订单中用一个长为 $N$ 的字符串来指定奶牛，其中的字符为 `H`（表示荷斯坦牛）或 `G`（表示更赛牛）。不幸的是，当这些奶牛到达他的农场，他给她们排队时，她们的品种组成的字符串与原先的不同。

我们将这两个字符串称为 $A$ 和 $B$，其中 $A$ 是 Farmer John 原先想要的品种字符组成的字符串，$B$ 是他的奶牛们到达时组成的字符串。Farmer John 并没有简单地检查重新排列 $B$ 中的奶牛是否能得到 $A$，而是请他的远房亲戚 Ben 利用他的科学才华来解决这一问题。

经过数月的研究，Ben 发明了一台不同寻常的机器：奶牛品种转换机 3000，能够选择任意奶牛组成的子串并反转她们的品种：在这个子串中的所有 `H` 变为 `G`，所有 `G` 变为 `H`。Farmer John 想要求出将他当前的序列 $B$ 变为他本来订购时想要的 $A$ 需要使用这台机器的最小次数。然而，Ben 的疯狂的科学家技能并不会处理开发奇异机器以外的事，所以你需要帮助 Farmer John 解决这个计算难题。 
## 输入格式

输入的第一行包含 $N$，以下两行包含字符串 $A$ 和 $B$。每个字符串均包含 $N$ 个字符，字符均为 `H` 和 `G` 之一。
## 输出格式

输出将 $B$ 变为 $A$ 需要使用机器的最小次数。 
## 样例

### 样例输入 #1
```
7
GHHHGHH
HHGGGHH
```
### 样例输出 #1
```
2
```
## 提示

### 样例解释 1

首先，FJ 可以仅改变第一个字符组成的子串，将 $B$ 变为 `GHGGGHH`。然后，他可以改变由第三和第四个字符组成的子串，得到 $A$。当然，还存在其他有效的执行两次操作的方案。 


---

---
title: "[USACO20DEC] Do You Know Your ABCs? B"
layout: "post"
diff: 入门
pid: P9955
tag: ['数学', '2020', 'USACO', 'O2优化']
---
# [USACO20DEC] Do You Know Your ABCs? B
## 题目描述

Farmer John 的奶牛正在 "mooZ" 视频会议平台上举行每日集会。她们发明了一个简单的数字游戏，为会议增添一些乐趣。

Elsie 有三个正整数 $A$、$B$ 和 $C$（$A\le B\le C$）。这些数字是保密的，她不会直接透露给她的姐妹 Bessie。她告诉 Bessie 七个范围在 $1\ldots 10^9$ 之间的整数（不一定各不相同），并宣称这是 $A$、$B$、$C$、$A+B$、$B+C$、$C+A$ 和 $A+B+C$ 的某种排列。

给定这七个整数，请帮助 Bessie 求出 $A$、$B$ 和 $C$。可以证明，答案是唯一的。 
## 输入格式

输入一行，包含七个空格分隔的整数。 
## 输出格式

输出 $A$、$B$ 和 $C$，用空格分隔。 
## 样例

### 样例输入 #1
```
2 2 11 4 9 7 9
```
### 样例输出 #1
```
2 2 7
```
## 提示

### 测试点性质

- 测试点 $2-3$ 满足 $C\le 50$。
- 测试点 $4-10$ 没有额外限制。


---

