---
title: "Forgery"
layout: "post"
diff: 普及-
pid: CF1059B
tag: ['枚举', '广度优先搜索 BFS']
---

# Forgery

## 题目描述

Student Andrey has been skipping physical education lessons for the whole term, and now he must somehow get a passing grade on this subject. Obviously, it is impossible to do this by legal means, but Andrey doesn't give up. Having obtained an empty certificate from a local hospital, he is going to use his knowledge of local doctor's handwriting to make a counterfeit certificate of illness. However, after writing most of the certificate, Andrey suddenly discovered that doctor's signature is impossible to forge. Or is it?

For simplicity, the signature is represented as an $ n\times m $ grid, where every cell is either filled with ink or empty. Andrey's pen can fill a $ 3\times3 $ square without its central cell if it is completely contained inside the grid, as shown below.

 `<br></br>xxx<br></br>x.x<br></br>xxx<br></br>`Determine whether is it possible to forge the signature on an empty $ n\times m $ grid.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 3 \le n, m \le 1000 $ ).

Then $ n $ lines follow, each contains $ m $ characters. Each of the characters is either '.', representing an empty cell, or '\#', representing an ink filled cell.

## 输出格式

If Andrey can forge the signature, output "YES". Otherwise output "NO".

You can print each letter in any case (upper or lower).

## 说明/提示

In the first sample Andrey can paint the border of the square with the center in $ (2, 2) $ .

In the second sample the signature is impossible to forge.

In the third sample Andrey can paint the borders of the squares with the centers in $ (2, 2) $ and $ (3, 2) $ :

1. we have a clear paper: `<br></br>...<br></br>...<br></br>...<br></br>...<br></br>`
2. use the pen with center at $ (2, 2) $ . `<br></br>###<br></br>#.#<br></br>###<br></br>...<br></br>`
3. use the pen with center at $ (3, 2) $ . `<br></br>###<br></br>###<br></br>###<br></br>###<br></br>`

In the fourth sample Andrey can paint the borders of the squares with the centers in $ (3, 3) $ and $ (3, 5) $ .

## 样例 #1

### 输入

```
3 3
###
#.#
###

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 3
###
###
###

```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 3
###
###
###
###

```

### 输出

```
YES
```

## 样例 #4

### 输入

```
5 7
.......
.#####.
.#.#.#.
.#####.
.......

```

### 输出

```
YES
```



---

---
title: "Product of Binary Decimals"
layout: "post"
diff: 普及-
pid: CF1950D
tag: ['模拟', '深度优先搜索 DFS']
---

# Product of Binary Decimals

## 题目描述

### 二进制小数的乘积
我们称一个数字为二进制小数，如果它是一个正整数，并且其十进制表示中的所有数字都是0或1。例如，$1010111$ 是一个二进制小数，而 $10201$ 和 $787788$ 不是。

给定一个数 $n$，你被要求判断是否可能将 $n$ 表示为一些（不一定是不同的）二进制小数的乘积。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 5 \cdot 10^4$）— 测试用例的数量。

每个测试用例的唯一一行包含一个整数 $n$（$1 \leq n \leq 10^5$）。

## 输出格式

对于每个测试用例，如果 $n$ 可以表示为一些二进制小数的乘积，则输出 "YES"（不带引号），否则输出 "NO"（不带引号）。

你可以以任何形式输出 "YES" 和 "NO"（例如，字符串 "yES"、"yes" 和 "Yes" 都将被认为是肯定的响应）。

## 说明/提示

前五个测试用例可以表示为二进制小数的乘积如下：

$121 = 11 \times 11$
$1 = 1$ 已经是一个二进制小数。
$14641 = 11 \times 11 \times 11 \times 11$
$12221 = 11 \times 11 \times 101$
$10110 = 10110$ 已经是一个二进制小数。

## 样例 #1

### 输入

```
11
121
1
14641
12221
10110
100000
99
112
2024
12421
1001
```

### 输出

```
YES
YES
YES
YES
YES
YES
NO
NO
NO
NO
YES
```



---

---
title: "Jumping on Walls"
layout: "post"
diff: 普及-
pid: CF198B
tag: ['搜索', '剪枝']
---

# Jumping on Walls

## 题目描述

瓦西亚在和忍者玩电脑游戏。在这个关卡，瓦西亚需要操控忍者走出一个很深的峡谷。

峡谷由两面垂直于地面且互相平行的墙组成，它们的高度为$n$米。我们将这些墙分成许多$1$米长的区域，并从下到上用$1$到$n$的正整数对它们进行编号。有些地方是安全的，忍者可以爬上去。有些地方石头很尖锐，忍者不能待在那里。我们称这些地区为危险地区。

最初忍者在左墙的最下方。他每秒可以执行以下操作之一：

* 向上爬一个区域；
* 向下爬一个区域；
* 跳到对面的墙上。忍者会跳到比他当前所在高度高$k$米的地方。更准确地说，如果在跳跃之前忍者位于一面墙的区域$x$，那么在跳跃之后，他位于另一面墙的区域$x + k$。

如果在某个时间点忍者到达了一个高度大于$n$的区域，那么忍者就可以从峡谷中出来了。

但峡谷被水淹没了，每秒水位会上升一米。最初，水位达到区域$1$的下边界。忍者不能待在被水淹没的地方。忍者和水轮流移动——首先忍者行动，然后水上升一米，然后忍者再行动，以此类推。

如果忍者可以离开峡谷，那这个关卡就完成了。

在几次失败的尝试之后，瓦西亚开始怀疑是否有可能完成这一关卡。请回答他的问题。

## 输入格式

第一行包含两个整数$n$和$k$ $(1 \leq n ,k \leq 10^5)$——峡谷的高度和忍者可以跳跃的高度

第二行包含左墙的描述——一个长度为$n$个字符的字符串。第$i$个字符表示墙的区域$i$的状态：字符“X”表示危险区域，“-”表示安全区域。

第三行以相同的格式描述了右墙。

数据保证左墙的第一个区域不是危险区域。

## 输出格式

如果忍者能从峡谷中出来，打印“YES”（不带引号），否则，打印“NO”（不带引号）。

## 说明/提示

在第一个样例中，忍者可以先跳到右边的墙，然后沿着右边的墙往下走一米，然后跳到左边的墙。再跳跃一次忍者就可以离开峡谷。

在第二个样例中，忍者是无法离开峡谷的。

## 样例 #1

### 输入

```
7 3
---X--X
-X--XX-

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
6 2
--X-X-
X--XX-

```

### 输出

```
NO

```



---

---
title: "Queue at the School"
layout: "post"
diff: 普及-
pid: CF266B
tag: ['字符串', '搜索', '队列']
---

# Queue at the School

## 题目描述

During the break the schoolchildren, boys and girls, formed a queue of $ n $ people in the canteen. Initially the children stood in the order they entered the canteen. However, after a while the boys started feeling awkward for standing in front of the girls in the queue and they started letting the girls move forward each second.

Let's describe the process more precisely. Let's say that the positions in the queue are sequentially numbered by integers from $ 1 $ to $ n $ , at that the person in the position number $ 1 $ is served first. Then, if at time $ x $ a boy stands on the $ i $ -th position and a girl stands on the $ (i+1) $ -th position, then at time $ x+1 $ the $ i $ -th position will have a girl and the $ (i+1) $ -th position will have a boy. The time is given in seconds.

You've got the initial position of the children, at the initial moment of time. Determine the way the queue is going to look after $ t $ seconds.

## 输入格式

The first line contains two integers $ n $ and $ t $ $ (1<=n,t<=50) $ , which represent the number of children in the queue and the time after which the queue will transform into the arrangement you need to find.

The next line contains string $ s $ , which represents the schoolchildren's initial arrangement. If the $ i $ -th position in the queue contains a boy, then the $ i $ -th character of string $ s $ equals "B", otherwise the $ i $ -th character equals "G".

## 输出格式

Print string $ a $ , which describes the arrangement after $ t $ seconds. If the $ i $ -th position has a boy after the needed time, then the $ i $ -th character $ a $ must equal "B", otherwise it must equal "G".

## 样例 #1

### 输入

```
5 1
BGGBG

```

### 输出

```
GBGGB

```

## 样例 #2

### 输入

```
5 2
BGGBG

```

### 输出

```
GGBGB

```

## 样例 #3

### 输入

```
4 1
GGGB

```

### 输出

```
GGGB

```



---

---
title: "DZY Loves Chessboard"
layout: "post"
diff: 普及-
pid: CF445A
tag: ['模拟', '字符串', '搜索', '深度优先搜索 DFS']
---

# DZY Loves Chessboard

## 题目描述

一个棋盘上有一些格子是坏的，另一些是正常的。对于每一个正常的格子，都要在上面放上棋子。
请找到一组解使没有两个相同颜色的棋子相邻(两个格子相邻为它们存在共同的边)

## 输入格式

第一行为两个数n,m。(1<=n,m<=100)
下面n行，每个格子上的字符为'-'或'.','-'表示坏掉的格子,'.'表示正常的格子。

## 输出格式

输出n行，每行m个字符。第i个字符串的第j个字符应为“W”，“B”或“ - ”。字符“W”是指在格子上放白色的棋子，“B”意味着放黑色的棋子，“ - ”表示坏掉的格子。
如果有多组答案，输出其中的一个

感谢@zhaotiensn 提供的翻译

## 样例 #1

### 输入

```
1 1
.

```

### 输出

```
B

```

## 样例 #2

### 输入

```
2 2
..
..

```

### 输出

```
BW
WB

```

## 样例 #3

### 输入

```
3 3
.-.
---
--.
```

### 输出

```
B-B
---
--B
```



---

---
title: "President's Office"
layout: "post"
diff: 普及-
pid: CF6B
tag: ['搜索', '深度优先搜索 DFS', '概率论']
---

# President's Office

## 输入格式

第一行：

房间长n,宽m,总统办公桌代表的字符串

接下来2 ~ n+1行,每行输入m列:

房间内的办公桌的颜色（大写字母）。"."为空单元格。

## 输出格式

一行一个变量：

求出在总统桌四周相邻的办公桌数量
样例1 解释：

3 4 R

G . B .

. R R .

T T T .

此办公室的总统桌在二排的第二，三列（连起来的并且颜色相同算一个办公桌，此样例总统桌面积为1*2）

那么四周则有办公桌：

TTT（TTT面积为1*3）

B

因此输出2
Translated by @s5_gan

## 样例 #1

### 输入

```
3 4 R
G.B.
.RR.
TTT.

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 3 Z
...
.H.
..Z

```

### 输出

```
0

```



---

---
title: "Ilya and tic-tac-toe game"
layout: "post"
diff: 普及-
pid: CF754B
tag: ['模拟', '搜索', '枚举']
---

# Ilya and tic-tac-toe game

## 题目描述

题目大意：

伊莉雅是一个4x4井字棋的年迈棋手，他总是用x（英文小写）棋，今天，他跟他的朋友亚瑟玩了很多很多局游戏，亚瑟很累了，但是现在还剩下最后一场游戏，现在轮到伊莉雅下棋，请问伊莉雅下完这颗棋子后能否取得胜利？
井字棋规则：

 棋盘的规格为4*4，其中伊莉雅棋子为x，亚瑟的棋子为o（英文小写o），x先下，o后下，当某种棋子在棋盘上连成三个时取得胜利！（这三个棋子可以是水平、竖直或斜方向的连续三个）

## 输入格式

输入的数据为给定的棋盘，其中.为空格，x（英文小写）为伊莉雅的棋子， o（英文小写）为亚瑟的棋子，棋盘保证有空格子，现在轮到伊莉雅。 （有可能整个棋盘都没有棋子，意味着亚瑟还没有下）

## 输出格式

输出为单行：如果伊莉雅下完一颗棋子后能够取得胜利，输出YES，如果不能，则输出NO。


感谢@icebird  提供的翻译

## 样例 #1

### 输入

```
xx..
.oo.
x...
oox.

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
x.ox
ox..
x.o.
oo.x

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
x..x
..oo
o...
x.xo

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
o.x.
o...
.x..
ooxx

```

### 输出

```
NO

```



---

---
title: "Obsession with Robots"
layout: "post"
diff: 普及-
pid: CF8B
tag: ['广度优先搜索 BFS', '最短路']
---

# Obsession with Robots

## 题目描述

The whole world got obsessed with robots,and to keep pace with the progress, great Berland's programmer Draude decided to build his own robot. He was working hard at the robot. He taught it to walk the shortest path from one point to another, to record all its movements, but like in many Draude's programs, there was a bug — the robot didn't always walk the shortest path. Fortunately, the robot recorded its own movements correctly. Now Draude wants to find out when his robot functions wrong. Heh, if Draude only remembered the map of the field, where he tested the robot, he would easily say if the robot walked in the right direction or not. But the field map was lost never to be found, that's why he asks you to find out if there exist at least one map, where the path recorded by the robot is the shortest.

The map is an infinite checkered field, where each square is either empty, or contains an obstruction. It is also known that the robot never tries to run into the obstruction. By the recorded robot's movements find out if there exist at least one such map, that it is possible to choose for the robot a starting square (the starting square should be empty) such that when the robot moves from this square its movements coincide with the recorded ones (the robot doesn't run into anything, moving along empty squares only), and the path from the starting square to the end one is the shortest.

In one movement the robot can move into the square (providing there are no obstrutions in this square) that has common sides with the square the robot is currently in.

## 输入格式

The first line of the input file contains the recording of the robot's movements. This recording is a non-empty string, consisting of uppercase Latin letters L, R, U and D, standing for movements left, right, up and down respectively. The length of the string does not exceed 100.

## 输出格式

In the first line output the only word OK (if the above described map exists), or BUG (if such a map does not exist).

## 样例 #1

### 输入

```
LLUUUR

```

### 输出

```
OK

```

## 样例 #2

### 输入

```
RRUULLDD

```

### 输出

```
BUG

```



---

---
title: "Water The Garden"
layout: "post"
diff: 普及-
pid: CF920A
tag: ['搜索', '枚举', '广度优先搜索 BFS']
---

# Water The Garden

## 题目描述

It is winter now, and Max decided it's about time he watered the garden.

The garden can be represented as $ n $ consecutive garden beds, numbered from $ 1 $ to $ n $ . $ k $ beds contain water taps ( $ i $ -th tap is located in the bed $ x_{i} $ ), which, if turned on, start delivering water to neighbouring beds. If the tap on the bed $ x_{i} $ is turned on, then after one second has passed, the bed $ x_{i} $ will be watered; after two seconds have passed, the beds from the segment $ [x_{i}-1,x_{i}+1] $ will be watered (if they exist); after $ j $ seconds have passed ( $ j $ is an integer number), the beds from the segment $ [x_{i}-(j-1),x_{i}+(j-1)] $ will be watered (if they exist). Nothing changes during the seconds, so, for example, we can't say that the segment $ [x_{i}-2.5,x_{i}+2.5] $ will be watered after $ 2.5 $ seconds have passed; only the segment $ [x_{i}-2,x_{i}+2] $ will be watered at that moment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/13bc7cf6794d83f150515b3ef05c019c5a177edb.png) The garden from test $ 1 $ . White colour denotes a garden bed without a tap, red colour — a garden bed with a tap.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/7701b634db65a2b1523162fa68f6ca25374deecc.png) The garden from test $ 1 $ after $ 2 $ seconds have passed after turning on the tap. White colour denotes an unwatered garden bed, blue colour — a watered bed. Max wants to turn on all the water taps at the same moment, and now he wonders, what is the minimum number of seconds that have to pass after he turns on some taps until the whole garden is watered. Help him to find the answer!

## 输入格式

The first line contains one integer $ t $ — the number of test cases to solve ( $ 1<=t<=200 $ ).

Then $ t $ test cases follow. The first line of each test case contains two integers $ n $ and $ k $ ( $ 1<=n<=200 $ , $ 1<=k<=n $ ) — the number of garden beds and water taps, respectively.

Next line contains $ k $ integers $ x_{i} $ ( $ 1<=x_{i}<=n $ ) — the location of $ i $ -th water tap. It is guaranteed that for each ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/2023391807a0506d9aa6b2ab3f46eb89dee16074.png) condition $ x_{i-1}<x_{i} $ holds.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 200 $ .

Note that in hacks you have to set $ t=1 $ .

## 输出格式

For each test case print one integer — the minimum number of seconds that have to pass after Max turns on some of the water taps, until the whole garden is watered.

## 说明/提示

The first example consists of $ 3 $ tests:

1. There are $ 5 $ garden beds, and a water tap in the bed $ 3 $ . If we turn it on, then after $ 1 $ second passes, only bed $ 3 $ will be watered; after $ 2 $ seconds pass, beds $ [1,3] $ will be watered, and after $ 3 $ seconds pass, everything will be watered.
2. There are $ 3 $ garden beds, and there is a water tap in each one. If we turn all of them on, then everything will be watered after $ 1 $ second passes.
3. There are $ 4 $ garden beds, and only one tap in the bed $ 1 $ . It will take $ 4 $ seconds to water, for example, bed $ 4 $ .

## 样例 #1

### 输入

```
3
5 1
3
3 3
1 2 3
4 1
1

```

### 输出

```
3
1
4

```



---

---
title: "Lucky Numbers (easy)"
layout: "post"
diff: 普及-
pid: CF96B
tag: ['广度优先搜索 BFS']
---

# Lucky Numbers (easy)

## 题目描述

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 744 $ , $ 4 $ are lucky and $ 5 $ , $ 17 $ , $ 467 $ are not.

Lucky number is super lucky if it's decimal representation contains equal amount of digits $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 7744 $ , $ 474477 $ are super lucky and $ 4 $ , $ 744 $ , $ 467 $ are not.

One day Petya came across a positive integer $ n $ . Help him to find the least super lucky number which is not less than $ n $ .

## 输入格式

The only line contains a positive integer $ n $ ( $ 1<=n<=10^{9} $ ). This number doesn't have leading zeroes.

## 输出格式

Output the least super lucky number that is more than or equal to $ n $ .

Please, do not use the %lld specificator to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 样例 #1

### 输入

```
4500

```

### 输出

```
4747

```

## 样例 #2

### 输入

```
47

```

### 输出

```
47

```



---

