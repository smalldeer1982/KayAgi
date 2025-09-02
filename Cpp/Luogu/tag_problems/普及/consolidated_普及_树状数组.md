---
title: "[GESP202309 六级] 小杨的握手问题"
layout: "post"
diff: 普及/提高-
pid: B3874
tag: ['树状数组', '递归', '2023', '排序', 'GESP']
---
# [GESP202309 六级] 小杨的握手问题
## 题目描述

小杨的班级里共有 $N$ 名同学，学号从 $0$ 至 $N-1$。

某节课上，老师安排全班同学进行一次握手游戏，具体规则如下：老师安排了一个顺序，让全班 $N$ 名同学依次进入教室。每位同学进入教室时，需要和 **已经在教室内** 且 **学号小于自己** 的同学握手。

现在，小杨想知道，整个班级总共会进行多少次握手。

**提示：可以考虑使用归并排序进行降序排序，并在此过程中求解。**
## 输入格式

输入包含 $2$ 行。第一行一个整数 $N$ ，表示同学的个数；第二行 $N$ 个用单个空格隔开的整数，依次描述同学们进入教室的顺序，每个整数在 $0 \sim N-1$ 之间，表示该同学的学号。

保证每位同学会且只会进入教室一次。

## 输出格式

输出一行一个整数，表示全班握手的总次数。
## 样例

### 样例输入 #1
```
4
2 1 3 0
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6
0 1 2 3 4 5
```
### 样例输出 #2
```
15
```
## 提示

**样例解释 1**:

$2$ 号同学进入教室，此时教室里没有其他同学。

$1$ 号同学进入教室，此时教室里有 $2$ 号同学。$1$ 号同学的学号小于 $2$ 号同学，因此他们之间不需要握手。

$3$ 号同学进入教室，此时教室里有 $1,2$ 号同学。$3$ 号同学的学号比他们都大，因此 $3$ 号同学需要分别和另外两位同学握手。

$0$ 号同学进入教室，此时教室里有 $1,2,3$ 号同学。$0$ 号同学的学号比他们都小，因此 $0$ 号同学不需要与其他同学握手。

**样例解释2：**

全班所有同学之间都会进行握手，因为每位同学来到教室时，都会发现他的学号是当前教室里最大的，所以他需要和教室里的每位其他同学进行握手。

对于 $30\%$ 的测试点，保证 $N\le100$。

对于所有测试点，保证 $2\le N\le3\times10^5$。



---

---
title: "[USACO03Open] Lost Cows"
layout: "post"
diff: 普及/提高-
pid: P10497
tag: ['线段树', '树状数组']
---
# [USACO03Open] Lost Cows
## 题目描述

N (2 <= N <= 8,000) cows have unique brands in the range 1..N. In a spectacular display of poor judgment, they visited the neighborhood 'watering hole' and drank a few too many beers before dinner. When it was time to line up for their evening meal, they did not line up in the required ascending numerical order of their brands.Regrettably, FJ does not have a way to sort them. 

Furthermore, he's not very good at observing problems. Instead of writing down each cow's brand, he determined a rather silly statistic: For each cow in line, he knows the number of cows that precede that cow in line that do, in fact, have smaller brands than that cow.Given this data, tell FJ the exact ordering of the cows.
## 输入格式

Line 1: A single integer, N

Lines 2..N: These N-1 lines describe the number of cows that precede a given cow in line and have brands smaller than that cow. Of course, no cows precede the first cow in line, so she is not listed. Line 2 of the input describes the number of preceding cows whose brands are smaller than the cow in slot #2; line 3 describes the number of preceding cows whose brands are smaller than the cow in slot #3; and so on.
## 输出格式

Lines 1..N: Each of the N lines of output tells the brand of a cow in line. Line #1 of the output tells the brand of the first cow in line; line 2 tells the brand of the second cow; and so on.
## 样例

### 样例输入 #1
```
5
1
2
1
0
```
### 样例输出 #1
```
2
4
5
3
1
```
## 题目翻译

### 题目描述

有 $N$ 头奶牛，已知它们的编号为 $1∼N$ 且各不相同，但不知道每头奶牛的具体编号。

现在这 $N$ 头奶牛站成一列，已知第 $i$ 头奶牛前面有 $a_i$ 头牛编号小于它，求每头奶牛的编号。

### 输入格式

第 $1$ 行，输入一个整数 $N$

第 $2...N$ 行，每行输入一个整数 $a_i$，表示第 $i$ 头奶牛前面有 $a_i$ 头奶牛的编号小于它（因为第一头奶牛前面没有奶牛，所以 $i$ 从 $2$ 开始）。

### 输出格式

输出包含 $N$ 行，每行输出一个整数表示奶牛的编号。

第 $i$ 行输出第 $i$ 头奶牛的编号。

### 数据范围

$2 \le N \le 8000$。


---

---
title: "最接近神的人"
layout: "post"
diff: 普及/提高-
pid: P1774
tag: ['线段树', '树状数组', '递归', 'NOI 导刊', '排序']
---
# 最接近神的人
## 题目描述

破解了符文之语，小 FF 开启了通往地下的道路。当他走到最底层时，发现正前方有一扇巨石门，门上雕刻着一幅古代人进行某种活动的图案。而石门上方用古代文写着“神的殿堂”。小 FF 猜想里面应该就有王室的遗产了。但现在的问题是如何打开这扇门……。

仔细研究后，他发现门上的图案大概是说：古代人认为只有智者才是最容易接近神明的。而最聪明的人往往通过一种仪式选拔出来。仪式大概是指，即将隐退的智者为他的候选人写下一串无序的数字，并让他们进行一种操作，即交换序列中相邻的两个元素。而用最少的交换次数使原序列变成不下降序列的人即是下一任智者。

小 FF 发现门上同样有着 $n$ 个数字。于是他认为打开这扇门的秘诀就是找到让这个序列变成不下降序列所需要的最小次数。但小 FF 不会……只好又找到了你，并答应事成之后与你三七分……
## 输入格式

第一行为一个整数 $n$，表示序列长度。

第二行为 $n$ 个整数，表示序列中每个元素。
## 输出格式

一个整数 $\mathit{ans}$，即最少操作次数。

## 样例

### 样例输入 #1
```
4
2 8 0 3

```
### 样例输出 #1
```
3
```
## 提示

### 数据范围及约定

- 对于 $30\%$ 的数据 $1≤n≤10^4$。
- 对于 $100\%$ 的数据 $1≤n≤5\times 10^5$，$A_i\in [-2^{31}, 2^{31})$。

### 样例解释

开始序列为 $[2,8,0,3]$，目标序列为 $[0, 2, 3, 8]$，可进行三次操作的目标序列：

1. 交换 $(8,0)$，序列变成 $[2,0,8,3]$；
2. 交换 $(2,0)$，序列变成 $[0,2,8,3]$；
3. 交换 $(8,3)$，序列变成 $[0,2,3,8]$。



---

---
title: "逆序对"
layout: "post"
diff: 普及/提高-
pid: P1908
tag: ['树状数组', '递归', '离散化', '排序']
---
# 逆序对
## 题目描述

猫猫 TOM 和小老鼠 JERRY 最近又较量上了，但是毕竟都是成年人，他们已经不喜欢再玩那种你追我赶的游戏，现在他们喜欢玩统计。

最近，TOM 老猫查阅到一个人类称之为“逆序对”的东西，这东西是这样定义的：对于给定的一段正整数序列，逆序对就是序列中 $a_i>a_j$ 且 $i<j$ 的有序对。知道这概念后，他们就比赛谁先算出给定的一段正整数序列中逆序对的数目。注意序列中可能有重复数字。

**Update：数据已加强。**
## 输入格式

第一行，一个数 $n$，表示序列中有 $n$ 个数。

第二行 $n$ 个数，表示给定的序列。序列中每个数字不超过 $10^9$。

## 输出格式

输出序列中逆序对的数目。

## 样例

### 样例输入 #1
```
6
5 4 2 6 3 1

```
### 样例输出 #1
```
11
```
## 提示

对于 $25\%$ 的数据，$n \leq 2500$。

对于 $50\%$ 的数据，$n \leq 4 \times 10^4$。

对于所有数据，$1 \leq n \leq 5 \times 10^5$。

请使用较快的输入输出。

应该不会有人 $O(n^2)$ 过 50 万吧 —— 2018.8 chen_zhe。


---

---
title: "[USACO04OPEN] MooFest G"
layout: "post"
diff: 普及/提高-
pid: P2345
tag: ['模拟', '2004', 'USACO', '树状数组', 'cdq 分治']
---
# [USACO04OPEN] MooFest G
## 题目背景

[P5094 [USACO04OPEN] MooFest G 加强版](https://www.luogu.com.cn/problem/P5094)

## 题目描述

约翰的 $n$ 头奶牛每年都会参加“哞哞大会”。

哞哞大会是奶牛界的盛事。集会上的活动很多，比如堆干草，跨栅栏，摸牛仔的屁股等等。

它们参加活动时会聚在一起，第 $i$ 头奶牛的坐标为 $x_i$，没有两头奶牛的坐标是相同的。

奶牛们的叫声很大，第 $i$ 头和第 $j$ 头奶牛交流，会发出
$\max\{v_i,v_j\}\times |x_i − x_j |$ 
的音量，其中 $v_i$ 和 $v_j$ 分别是第 $i$ 头和第 $j$ 头奶牛的听力。

假设每对奶牛之间同时都在说话，请计算所有奶牛产生的音量之和是多少。
## 输入格式

第一行：单个整数 $n$，$1\le n\le2\times 10^4$

第二行到第 $n + 1$ 行：第 $i + 1$ 行有两个整数 $v_i$ 和 $x_i$（$1\le v_i,x_i\le2\times 10^4$）。
## 输出格式

单个整数：表示所有奶牛产生的音量之和
## 样例

### 样例输入 #1
```
4
3 1
2 5
2 6
4 3
```
### 样例输出 #1
```
57
```


---

---
title: "[USACO07JAN] Balanced Lineup G"
layout: "post"
diff: 普及/提高-
pid: P2880
tag: ['2007', 'USACO', '树状数组', 'ST 表']
---
# [USACO07JAN] Balanced Lineup G
## 题目描述

For the daily milking, Farmer John's N cows (1 ≤ N ≤ 50,000) always line up in the same order. One day Farmer John decides to organize a game of Ultimate Frisbee with some of the cows. To keep things simple, he will take a contiguous range of cows from the milking lineup to play the game. However, for all the cows to have fun they should not differ too much in height.

Farmer John has made a list of Q (1 ≤ Q ≤ 180,000) potential groups of cows and their heights (1 ≤ height ≤ 1,000,000). For each group, he wants your help to determine the difference in height between the shortest and the tallest cow in the group.

每天,农夫 John 的 $n(1\le n\le 5\times 10^4)$ 头牛总是按同一序列排队。

有一天, John 决定让一些牛们玩一场飞盘比赛。他准备找一群在队列中位置连续的牛来进行比赛。但是为了避免水平悬殊，牛的身高不应该相差太大。John 准备了 $q(1\le q\le 1.8\times10^5)$ 个可能的牛的选择和所有牛的身高 $h_i(1\le h_i\le 10^6,1\le i\le n)$。他想知道每一组里面最高和最低的牛的身高差。
## 输入格式

Line 1: Two space-separated integers, N and Q.


Lines 2..N+1: Line i+1 contains a single integer that is the height of cow i


Lines N+2..N+Q+1: Two integers A and B (1 ≤ A ≤ B ≤ N), representing the range of cows from A to B inclusive.

第一行两个数 $n,q$。

接下来 $n$ 行，每行一个数 $h_i$。

再接下来 $q$ 行，每行两个整数 $a$ 和 $b$，表示询问第 $a$ 头牛到第 $b$ 头牛里的最高和最低的牛的身高差。

## 输出格式

Lines 1..Q: Each line contains a single integer that is a response to a reply and indicates the difference in height between the tallest and shortest cow in the range.

输出共 $q$ 行，对于每一组询问，输出每一组中最高和最低的牛的身高差。
## 样例

### 样例输入 #1
```
6 3
1
7
3
4
2
5
1 5
4 6
2 2
```
### 样例输出 #1
```
6
3
0
```


---

---
title: "递增"
layout: "post"
diff: 普及/提高-
pid: P3902
tag: ['动态规划 DP', '二分', '树状数组', '离散化']
---
# 递增
## 题目描述

现有数 $A_1,A_2,\cdots,A_n$，修改最少的数字为**实数**，使得数列严格单调递增。

注：原题误表述为修改为整数，现已纠正为实数。本题数据确保按照修改为整数的做法也可以 AC（只是不能过样例）
## 输入格式

第一行，一个整数 $n$。

第二行，$n$ 个整数$A_1,A_2,\cdots,A_n$

## 输出格式

1 个整数，表示最少修改多少个数字

## 样例

### 样例输入 #1
```
3
1 3 2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
8
1 2 3 4 4 5 6 7
```
### 样例输出 #2
```
1
```
## 提示

• 对于50% 的数据，$N \le 10^3$

• 对于100% 的数据，$1 \le N \le 10^5 , 1 \le A_i \le 10^9$



---

---
title: "数据结构"
layout: "post"
diff: 普及/提高-
pid: P3948
tag: ['线段树', '树状数组', '前缀和', '差分']
---
# 数据结构
## 题目背景

**引言**

数据结构学的好，未来工作没烦恼。

![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999\_10000&sec=1508946101936&di=0c08b703e466d2a3b2d20dd8008821fc&imgtype=0&src=http%3A%2F%2Fjoymepic.joyme.com%2Farticle%2Fuploads%2Fallimg%2F201511%2F1446516425349678.gif)


Edgration 是一个喜欢乱搞数据结构的蒟蒻（以下简称edt），有一天，他作死想去刁难一下dalao：

edt想求一种数据结构，使得可以实现区间加，求出某一区间大于k的元素的个数

dalao1：sb线段树

dalao2：sb分块

dalao3：sb平衡树

edt: 不行，那就加上取模，求区间取膜mod后大于MIN小于MAX的元素个数

dalao1：线段树&……￥#&……%……&\*&%￥

dalao2：sb分块 &%￥……%#￥#&……&\*

dalao3：\*&……%&￥LCT维护SBT水题 &……%&……%

edt：那不仅取模，每个数乘上数组下标再取模

dalao：￥%￥￥&\*（#￥% 叽里呱啦叽里呱啦

edt：不行，在把取模的值丢到一棵树上，维护一棵仙人掌乘积方差的最小极差

dalao：替罪羊树上用sb块状链表维护Toptree上的最小费用最大流和可持久化仙人掌，算出来在基尔霍夫矩阵中反演后跑一遍fft维护的插头DP就好了，给我三分钟轻松水过。。

edt：mmp

## 题目描述

蒟蒻Edt把这个问题交给了你 ———— 一个精通数据结构的大犇，由于是第一题，这个题没那么难。。


edt 现在对于题目进行了如下的简化：


最开始的数组每个元素都是0


给出$n$，$opt$，$mod$，$min$，$max$，$mod$在int范围内


操作$A$，$Q$


$A$: $L$,$R$,$X$ 表示把$[l,R]$这个区间加上$X$

**（数组的从L到R的每个元素都加上X）**


$Q$: $L$,$R$ 表示询问$[L,R]$这个区间中元素T满足  $min<=(T*i$%$ mod)<=max$  的 T这样的数的个数（i是数组下标）

**（元素的值\*数组下标%mod在min到max范围内）**


由于 edt 请来了一位非三次元的仓鼠，他帮你用延后了部分问题，将这些询问打入了混乱时空，你的询问操作不会超过1000次，不幸的是，对于延后的询问操作可能有很多次（小于1e7次），但是保证这些延后的询问操作之后不会再次有修改操作

（就是在最后会有很多次询问，但不会进行修改）

## 输入格式

给出n，opt，mod，min，max表示序列大小，操作次数，取膜，最小值，最大值


下面opt行，给出


$A$: $L$，$R$，$X$表示区间加，保证X在int范围内(<2147483647）


$Q$：$L$，$R$表示区间查询满足条件的个数


再给出一个$Final$值，表示后面有$Final$个询问


下面$Final$行，给出


$L$，$R$表示询问区间$[L,R]$表示询问$[L,R]$之间满足条件的个数

## 输出格式

每行对于每个$Q$操作输出$Q$个数表示每次询问的值，


下面$Final$行表示$Final$个询问的值

## 样例

### 样例输入 #1
```
3 2 4 0 2
A 1 3 5
Q 2 3 
5
1 3
2 3
1 1 
2 2 
3 3

```
### 样例输出 #1
```
1
2
1
1
1
0

```
### 样例输入 #2
```
17 25 4098 310 2622
A 10 16 657212040
A 4 15 229489140
A 1 2 -433239891
A 3 12 532385784
A 10 17 56266644
A 8 10 10038874
A 6 9 13084764
A 4 5 -9206340
Q 2 8
A 2 4 -43223955
A 6 9 31478706
A 2 4 189818310
A 2 8 179421180
A 2 8 40354938
Q 8 14
A 3 6 57229575
A 6 13 132795740
A 2 17 14558022
A 14 15 -552674185
A 5 11 -1104138
Q 2 12
Q 1 14
A 3 9 524902182
A 8 12 114291440
A 3 7 107531442
1
11 12

```
### 样例输出 #2
```
3
6
7
8
2

```
### 样例输入 #3
```
20 3 4317 1020 2232
A 8 15 -434078222
A 1 2 54988154
A 13 19 81757858
15
7 11
3 5
3 9
6 9
9 13
6 19
1 20
3 5
3 10
1 7
2 14
6 10
2 3
2 3
10 12

```
### 样例输出 #3
```
0
0
0
0
0
2
2
0
0
0
0
0
0
0
0

```
## 提示

## 样例说明

给出样例1的解释：

样例1中，$a$数组修改为$5$，$5$，$5$

每个$a[i]*i$%$4$ 的值为$1$,$2$,$3$

对于Final的询问

询问$[1$，$3]$中大于等于0小于等于2的个数为2个

剩下的询问类似

## 题目说明

**注意**：

### 1.关于负数取模问题，请以 c++ 的向0取整为标准，即如：

[ $ -7 $%$ 3 = -1 $ ]  [ $ 7 $%$ 3 = 1 $ ]

### 2.一共会有50个测试点，每个点分值为2分。

因为测试点数较多，请oier们自觉地不要故意多次提交来卡评测机，出题人 edt 在这里表示由衷的感谢

## 数据范围

如果你不能作对所有点，请尝试获得部分分，所有数据都是随机生成

![](https://cdn.luogu.com.cn/upload/image_hosting/whf39g4d.png)


---

---
title: "[USACO18OPEN] Out of Sorts S"
layout: "post"
diff: 普及/提高-
pid: P4378
tag: ['2018', 'USACO', '树状数组', '排序']
---
# [USACO18OPEN] Out of Sorts S
## 题目描述

留意着农场之外的长期职业生涯的可能性，奶牛 Bessie 开始在不同的在线编程网站上学习算法。

她到目前为止最喜欢的算法是“冒泡排序”。这是 Bessie 的对长度为 $N$ 的数组 $A$ 进行排序的奶牛码实现。

```
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
         sorted = false
```
显然，奶牛码中的“moo”指令的作用只是输出“moo”。奇怪的是，Bessie 看上去执着于在她的代码中的不同位置使用这个语句。

给定一个输入数组，请预测 Bessie 的代码会输出多少次“moo”。
## 输入格式

输入的第一行包含 $N$（$1 \leq N \leq 100,000$）。接下来 $N$ 行描述了 $A[0] \ldots A[N-1]$，每个数都是一个范围为 $0 \ldots 10^9$ 的整数。输入数据不保证各不相同。
## 输出格式

输出“moo”被输出的次数。
## 样例

### 样例输入 #1
```
5
1
5
3
8
2
```
### 样例输出 #1
```
4

```
## 提示

供题：Brian Dean


---

---
title: "[NOIP 2018 提高组] 铺设道路"
layout: "post"
diff: 普及/提高-
pid: P5019
tag: ['贪心', '2018', '树状数组', 'NOIP 提高组']
---
# [NOIP 2018 提高组] 铺设道路
## 题目背景

NOIP2018 提高组 D1T1
## 题目描述

春春是一名道路工程师，负责铺设一条长度为 $n$ 的道路。 

铺设道路的主要工作是填平下陷的地表。整段道路可以看作是 $n$ 块首尾相连的区域，一开始，第 $i$ 块区域下陷的深度为 $d_i$ 。 

春春每天可以选择一段连续区间 $[L,R]$ ，填充这段区间中的每块区域，让其下陷深度减少 $1$。在选择区间时，需要保证，区间内的每块区域在填充前下陷深度均不为 $0$ 。 

春春希望你能帮他设计一种方案，可以在最短的时间内将整段道路的下陷深度都变为 $0$ 。 
## 输入格式

输入文件包含两行，第一行包含一个整数 $n$，表示道路的长度。 第二行包含 $n$ 个整数，相邻两数间用一个空格隔开，第 $i$ 个整数为 $d_i$ 。 
## 输出格式

输出文件仅包含一个整数，即最少需要多少天才能完成任务。 
## 样例

### 样例输入 #1
```
6   
4 3 2 5 3 5 

```
### 样例输出 #1
```
9
```
## 提示

【样例解释】

一种可行的最佳方案是，依次选择： 
$[1,6]$、$[1,6]$、$[1,2]$、$[1,1]$、$[4,6]$、$[4,4]$、$[4,4]$、$[6,6]$、$[6,6]$。   

【数据规模与约定】

对于 $30\%$ 的数据，$1 ≤ n ≤ 10$ ；    
对于 $70\%$ 的数据，$1 ≤ n ≤ 1000$ ；     
对于 $100\%$ 的数据，$1 ≤ n ≤ 100000 , 0 ≤ d_i ≤ 10000$ 。   


---

