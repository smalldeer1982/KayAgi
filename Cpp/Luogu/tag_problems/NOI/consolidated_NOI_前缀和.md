---
title: "[集训队互测 2024] 游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12510
tag: ['集训队互测', '2024', '前缀和']
---
# [集训队互测 2024] 游戏
## 题目描述

小 $\rm{A}$ 和小 $\rm{B}$ 喜欢玩游戏。

他们在数轴上玩游戏，数轴上的一些位置放着物品，最初他们有一个参数 $k$，**保证 $k=0/1$**。

接下来小 $\rm{A}$ 会选定一个位置 $x$，那么小 $\rm{B}$ 的位置就为 $x+k$，两个人会轮流取走物品，由小 $\rm{A}$ 先手。

对于当前操作的玩家，他会取走当前剩余物品中离自己的位置距离最近的一个物品，如果有两个物品距离相同，则他会取走位置更小的那个物品。

位置 $a$ 和 $b$ 的距离定义为 $|a-b|$。

最后，在所有物品都被取走后，小 $\rm{A}$ 想知道，他手上的物品位置的总和是多少。

但是，由于他们非常的闲，他们会进行 $q$ 次游戏，每次游戏结束后所有物品都会恢复原位置，对于每次游戏小 $\rm{A}$ 都想知道对于当前的位置 $x$，小 $\rm{B}$ 的位置 $x+k$，游戏完后小 $\rm{A}$ 手上的物品位置的总和。
## 输入格式

第一行三个数 $n,q,k$，表示数轴上存在 $n$ 个区间的物品，小 $\rm{A}$ 和小 $\rm{B}$ 的游戏次数和初始选定的参数。

接下来 $n$ 行，每行两个数 $l_i,r_i$ 表示在区间 $[l_i,r_i]$ 中的每个位置都有一个物品。

接下来 $q$ 行，每行一个数 $x$，表示此轮游戏小 $\rm{A}$ 的参数为 $x$，小 $\rm{B}$ 的参数为 $x+k$。
## 输出格式

设 $ans_i$ 表示第 $i$ 次询问的答案，那么输出一个整数表示 $\oplus_{i=1}^{q}i \times ans_i$。
## 样例

### 样例输入 #1
```
4 2 1
4 5
7 8
10 11
13 13
6
8
```
### 样例输出 #1
```
16
```
### 样例输入 #2
```
7 6 0
2 2
4 5
7 8
9 9
13 13
15 15
18 20
19
15
18
17
11
5
```
### 样例输出 #2
```
468
```
### 样例输入 #3
```
见 game3.in/ans
这个样例满足子任务 2 的约束条件
```
### 样例输出 #3
```

```
### 样例输入 #4
```
见 game4.in/ans
这个样例满足子任务 4 的约束条件
```
### 样例输出 #4
```

```
## 提示

### 样例 1 解释
对于 $x=8$ 的询问。

小 $\rm{A}$ 在结束时手上的物品的位置为 $8,7,5,4$。

小 $\rm{B}$ 在结束时手上的物品的位置为 $10,11,13$。

因此结束时小 $\rm{A}$ 手上的物品位置的总和为 $8+7+5+4 = 24$。

对于 $x=6$ 的询问，答案为 $32$。

### 数据范围

对于所有数据，保证：$1 \le n \le 5000$，$1 \le q \le 2 \times 10^6$，$1 \le x \le 5 \times 10^6$，$1 \le l_i \le r_i \le 5 \times 10^6$，$k=0/1$，$\forall i \in [1,n-1],r_i < l_{i+1}$。

subtask 1（$15$ 分）：$q \le 2000$；

subtask 2（$25$ 分）：$k=0$；

subtask 3（$20$ 分）：$k=1,l_i = r_i$； 

subtask 4（$40$ 分）：无。


---

---
title: "【MX-X13-T7】「KDOI-12」No one can be anything without comparison."
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13012
tag: ['O2优化', '深度优先搜索 DFS', '树论', '前缀和', '分块', '梦熊比赛']
---
# 【MX-X13-T7】「KDOI-12」No one can be anything without comparison.
## 题目描述

**请注意本题对 $\bm{n,k}$ 的特殊限制。**

$n$ 名选手参加了 $k$ 场 Tetris Tournament。每一场 Tetris Tournament 包含 $n-1$ 轮，每轮会选出两个目前还未淘汰的选手 $x,y$ 并让他们参加一场比赛，输的人淘汰。最后会有唯一胜者。你现在得知第 $j$ 个人在第 $i$ 场 Tetris Tournament 中被 $a_{i,j}$ 淘汰了。$j$ 是第 $i$ 场 Tetris Tournament 的胜者当且仅当 $a_{i,j}=0$。

选手们喜欢比较。他们都希望自己在某种意义上能够胜过别人，或至少跟别人水平差不多。

定义第 $i$ 场 Tetris Tournament 中 $x$ 严格吊打 $y$ 当且仅当存在 $x=p_1,p_2,\dots,p_m=y$（$m\ge 2$，也就是说 $x\neq y$），使得对于任意 $1\leq j<m$，$a_{i,p_{j+1}}=p_j$。

定义一个有序的选手 $k$ 元组 $(i_1,i_2,\dots,i_k)$ 是水平相似的当且仅当对于 $1\leq j<k$，$i_j$ 在第 $j$ 场比赛中严格吊打 $i_{j+1}$ 且 $i_k$ 在第 $k$ 场比赛中严格吊打 $i_1$。

求水平相似的 $k$ 元组数量，对 $998244353$ 取模。
## 输入格式

第一行，两个正整数 $n,k$。**保证 $\bm{3\leq k\leq 5}$**。

接下来 $k$ 行，第 $i$ 行 $n$ 个非负整数 $a_{i,1}, \ldots, a_{i,n}$。
## 输出格式

仅一行，一个非负整数，表示水平相似的 $k$ 元组数量，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3 3
0 1 2
3 0 2
3 1 0
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 5
0 1 1 2 3 4
3 3 0 6 6 1
2 4 1 0 1 1
3 0 2 6 6 2
5 3 6 1 0 4
```
### 样例输出 #2
```
18
```
## 提示

**【样例解释 \#1】**

符合要求的三元组 $(i_1,i_2,i_3)$ 有：$(1,2,3)$，$(2,3,1)$。

**【数据范围】**

**本题使用捆绑测试。**

| 子任务编号 | 分值 | $n\leq$ | $k=$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | $7$ | $100$ | $3$ | 无 |
| $2$ | $8$ | $500$ | $3$ | 无 |
| $3$ | $13$ | $3\times10^3$ | $3$ | 无 |
| $4$ | $14$ | $2.5\times10^5$ | $3$ | A |
| $5$ | $15$ | $10^5$ | $3$ | B |
| $6$ | $7$ | $10^5$ | $3$ | 无 |
| $7$ | $14$ | $2.5\times10^5$ | $3$ | 无 |
| $8$ | $7$ | $5\times10^4$ | $4$ | 无 |
| $9$ | $6$ | $7.5\times10^4$ | $4$ | 无 |
| $10$ | $9$ | $4\times10^4$ | $5$ | 无 |

* 特殊性质 A：对于 $1\leq i\leq n$，$a_{1,i}=a_{2,i}$；
* 特殊性质 B：对于 $1\leq i\leq k$，不存在 $1\leq j_1<j_2\leq n$ 使得 $a_{i,j_1}=a_{i,j_2}$。

对于所有数据：$1\leq n\leq2.5\times10^5$，$\bm{3\leq k\leq 5}$，保证 $a$ 数组符合题意，且：

* $k=3$ 时，$n\leq2.5\times10^5$；
* $k=4$ 时：$n\leq7.5\times10^4$；
* $k=5$ 时：$n\leq4\times10^4$。


---

---
title: "[USACO16OPEN] Bull in a China Shop P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3148
tag: ['模拟', '2016', '二分', 'USACO', 'O2优化', '哈希 hashing', '前缀和']
---
# [USACO16OPEN] Bull in a China Shop P
## 题目描述

Farmer John has decided his home needs more decoration. Visiting the local china shop, he finds a delicate glass cow figurine that he decides to purchase, knowing that it will fit perfectly on the mantel above his fireplace.

The shape of the cow figurine is described by an $N \times M$ grid of haracters like the one below ($3 \leq N, M \leq 500$), where lowercase letter characters are each part of the figurine (indicating different colors) and '.' characters are not.

```
...............
...............
x..x...........
xxxx...........
xxxxaaaaaaa...
.xx.aaaaaaaaa..
....aaaaaaa.aa.
....ll...ll....
....vv...vv....
...............
```

Unfortunately, right before FJ can make his purchase, a bull runs through the shop  and breaks not only FJ's figurine, but many of the other glass objects on the shelves as well!  FJ's figurine breaks into 3 pieces, which quickly becomelost  among $K$ total pieces lying on the ground ($4 \leq K \leq 100$).  Each ofthe $K$ pieces is described by a grid of characters, just like the originalfigurine.

Please help FJ determine how many sets of 3 pieces (out of the $K$ on the floor)could be glued back together to mend his broken figurine.

The pieces on the ground might have been flipped vertically or horizontally, orrotated by some multiple of 90 degrees. Therefore, given the original grid aswell as $K$ grids describing pieces, you want to find sets of 3 pieces that canbe joined together to form the original picture, allowing the pieces to betranslated, flipped, or rotated multiples of 90 degrees.  When thensuperimposed, the 3 pieces should exactly form the original picture, with eachcolored square in the original picture represented in exactly one of the pieces.
## 输入格式

The first line contains a single integer $K$. Following that will be $K + 1$ piece descriptions.  The first description will describe the original glass cow,the following $K$ descriptions will be of the broken pieces.

Each description begins with a line containing two integers $R$ and $C$ ($1 \le R, C \le 100$).  The following $R$ lines contain $C$ lowercase alphabet characters describing the color of each cell.  Each piece will be horizontally/vertically connected and have at least one non-empty cell.

## 输出格式

Output the number of triples $i, j, k$ ($i < j < k$) such that pieces $i$, $j$, and $k$ can be arranged to form the original glass cow.
## 样例

### 样例输入 #1
```
5
5 5
aaaaa
..a..
bbabb
..a..
aaaaa
3 5
..abb
..a..
aaaaa
5 2
a.
a.
aa
a.
a.
1 2
bb
1 5
bbabb
2 5
aaaaa
..a..
```
### 样例输出 #1
```
3
```
## 提示

The three solutions use pieces $(0, 1, 2)$, $(0, 2, 4)$, $(1, 3, 4)$.

Note that this problem has a time limit of 6 seconds per test case (and twice that  for Java and Python submissions).
## 题目翻译

### 题目描述

Farmer John 决定给他的家增添一些装饰。在当地的瓷器店里，他发现了一尊精致的玻璃牛雕像，决定购买它，因为它完美地适合放在壁炉上方的壁炉架上。

牛雕像的形状由一个 $N \times M$ 的字符网格描述（$3 \leq N, M \leq 500$），其中小写字母字符代表雕像的各个部分（表示不同的颜色），而 '.' 字符则不代表雕像部分。

```cpp
...............
...............
x..x...........
xxxx...........
xxxxaaaaaaa...
.xx.aaaaaaaaa..
....aaaaaaa.aa.
....ll...ll....
....vv...vv....
...............
```

不幸的是，就在 FJ 准备购买之前，一头公牛冲进了商店，不仅撞碎了 FJ 的雕像，还撞碎了许多其他货架上的玻璃制品！FJ 的雕像碎成了 3 块，并迅速混入了地上的 $K$ 块碎片中（$4 \leq K \leq 100$）。每一块碎片都由一个字符网格描述，就像原来的雕像一样。

请帮助 FJ 确定有多少组 3 块碎片（地上的 $K$ 块中）可以粘合在一起修复他破碎的雕像。

地上的碎片可能被垂直或水平翻转，或者旋转了 90 度的倍数。因此，给定原始网格以及描述碎片的 $K$ 个网格，你需要找到可以组合成原始图片的 3 块碎片，允许碎片被平移、翻转或旋转 90 度的倍数。当这 3 块碎片叠加在一起时，它们应该准确地形成原始图片，且原始图片中的每个彩色方块都恰好出现在一块碎片中。

### 输入格式

第一行包含一个整数 $K$。接下来是 $K + 1$ 个碎片的描述。第一个描述是原始玻璃牛的描述，接下来的 $K$ 个描述是破碎的碎片。

每个描述以两个整数 $R$ 和 $C$（$1 \le R, C \le 100$）开始。接下来的 $R$ 行包含 $C$ 个小写字母字符，描述每个单元格的颜色。每块碎片在水平/垂直方向上都是连通的，并且至少有一个非空单元格。

### 输出格式

输出满足条件的三元组 $i, j, k$（$i < j < k$）的数量，使得碎片 $i$、$j$ 和 $k$ 可以排列成原始玻璃牛。

### 说明/提示

三个解决方案使用了碎片 $(0, 1, 2)$、$(0, 2, 4)$ 和 $(1, 3, 4)$。

请注意，这个问题每个测试用例的时间限制为 6 秒（Java 和 Python 提交的时间限制为 12 秒）。


---

---
title: "[CQOI2017] 小 Q 的表格"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3700
tag: ['数学', '2017', '重庆', '各省省选', '枚举', '前缀和']
---
# [CQOI2017] 小 Q 的表格
## 题目描述

小 Q 是个程序员。

作为一个年轻的程序员，小 Q 总是被老 C 欺负，老 C 经常把一些麻烦的任务交给小 Q 来处理。每当小 Q 不知道如何解决时，就只好向你求助。

为了完成任务，小 Q 需要列一个表格，表格有无穷多行，无穷多列，行和列都从 $1$ 开始标号。为了完成任务，表格里面每个格子都填了一个整数，为了方便描述，小 Q 把第 $a$ 行第 $b$ 列的整数记为 $f(a, b)$。为了完成任务，这个表格要满足一些条件：

1. 对任意的正整数 $a, b$，都要满足 $f(a, b) = f(b, a)$；
2. 对任意的正整数 $a, b$，都要满足 $b \times f(a, a + b) = (a + b) \times f(a, b)$。

为了完成任务，一开始表格里面的数很有规律，第 $a$ 行第 $b$ 列的数恰好等于 $a \times b$，显然一开始是满足上述两个条件的。为了完成任务，小 Q 需要不断的修改表格里面的数，每当修改了一个格子的数之后，为了让表格继续满足上述两个条件，小 Q 还需要把这次修改能够波及到的全部格子里都改为恰当的数。由于某种神奇的力量驱使，已经确保了每一轮修改之后所有格子里的数仍然都是整数。为了完成任务，小 Q 还需要随时获取前 $k$ 行前 $k$ 列这个有限区域内所有数的和是多少，答案可能比较大，只需要算出答案 ${} \bmod 1,000,000,007$ 之后的结果。
## 输入格式

输入文件第一行包含两个整数 $m, n$，表示共有 $m$ 次操作，所有操作和查询涉及到的行编号和列编号都不超过 $n$。

接下来 $m$ 行，每行四个整数 $a, b, x, k$，表示把第 $a$ 行 $b$ 列的数改成 $x$，然后把它能够波及到的所有格子全部修改，保证修改之后所有格子的数仍然都是整数，修改完成后计算前 $k$ 行前 $k$ 列里所有数的和。
## 输出格式

输出共 $m$ 行，每次操作之后输出一行，表示答案 ${} \bmod 1,000,000,007$ 之后的结果。
## 样例

### 样例输入 #1
```
3 3
1 1 1 2
2 2 4 3
1 2 4 2

```
### 样例输出 #1
```
9
36
14

```
### 样例输入 #2
```
4 125
1 2 4 8
1 3 9 27
1 4 16 64
1 5 25 125

```
### 样例输出 #2
```
2073
316642
12157159
213336861

```
## 提示

**【样例解释 #1】**

一开始，表格的前 $3$ 行前 $3$ 列如图中左边所示。前 $2$ 次操作后表格没有变化，第 $3$ 次操作之后的表格如右边所示。

```cpp
1 2 3     2  4  6
2 4 6     4  4 12
3 6 9     6 12  9
```

**【数据范围】**

对于 $100 \%$ 的测试点，$1 \le m \le {10}^4$，$1 \le a, b, k \le n \le 4 \times {10}^6$，$0 \le x \le {10}^{18}$。

![](https://cdn.luogu.com.cn/upload/pic/5012.png)



---

---
title: "普通数学题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3791
tag: ['洛谷原创', 'O2优化', '枚举', '进制', '前缀和', '洛谷月赛']
---
# 普通数学题
## 题目背景

一天 zzq 没有题可以出了。于是他随便写了一个式子，求$\sum_{i=0}^n \sum_{j=0}^m i \operatorname{xor}j\operatorname{xor}x$，其中 $\operatorname{xor}$ 表示异或。

zzy 一看，这不是水题吗，就随便加了一个函数：$\sum_{i=0}^n \sum_{j=0}^m d(i \operatorname{xor}j\operatorname{xor}x)$，其中 $\operatorname{xor}$ 表示异或，$d(x)$ 表示 $x$ 的约数个数。**注意 $d(0)=0$。**

现在 zzq 不会做了，只好写了一个暴力造了数据，然后把这道题丢给了你。

## 题目描述

输入三个数 $n,m,x$，要求计算 $\sum_{i=0}^n \sum_{j=0}^m d(i \operatorname{xor}j\operatorname{xor}x)$，其中 $\operatorname{xor}$ 表示二进制下的异或，$d(x)$ 表示 $x$ 的约数个数。

由于答案比较大，要求输出答案模 $ 998244353$ 后的结果。

## 输入格式

一行三个数 $n,m,x$。

## 输出格式

输出答案模 $ 998244353$ 后的结果。
## 样例

### 样例输入 #1
```
0 2 233
```
### 样例输出 #1
```
14
```
### 样例输入 #2
```
123 234 345
```
### 样例输出 #2
```
205761
```
## 提示

对于 $20\%$ 的数据，$n,m,x \leq 2000$。

对于 $50\%$ 的数据，$n,m,x \leq 10^6$。

对于 $80\%$ 的数据，$n,m,x \leq 10^8$。

对于 $100\%$ 的数据，$1 \leq n,m,x \leq 10^{10}$。



---

---
title: "[BJOI2017] 开车"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3992
tag: ['2017', '各省省选', '北京', 'O2优化', '排序', '前缀和', '分块']
---
# [BJOI2017] 开车
## 题目描述

有 $n$ 辆车，分别在 $a_1, a_2, \ldots , a_n$ 位置和 $n$ 个加油站，分别在 $b_1, b_2, \ldots ,b_n$ 位置。

每个加油站只能支持一辆车的加油，所以你要把这些车开到不同的加油站加油。一个车从 $x$ 位置开到 $y$ 位置的代价为 $|x-y|$，问如何安排车辆，使得代价之和最小。

同时你有 $q$ 个操作，每次操作会修改第 $i$ 辆车的位置到 $x$，你要回答每次修改操作之后最优安排方案的总代价。

## 输入格式

第一行一个正整数 $n$。

接下来一行 $n$ 个整数 $a_1, a_2,\ldots,a_n$。

接下来一行 $n$ 个整数 $b_1, b_2,\ldots,b_n$。

接下来一行一个正整数 $q$，表示操作的个数。

接下来 $q$ 行，每行有两个整数 $i$（$1\leq i\leq n$）和 $x$，表示将i这辆车开到 $x$ 位置的操作。

所有的车和加油站的范围一直在 $0$ 到 $10^9$ 之间。

## 输出格式

共 $q+1$ 行，第一行表示一开始的最优代价。

接下来 $q$ 行，第 $i$ 行表示操作 $i$ 之后的最优代价。

## 样例

### 样例输入 #1
```
2
1 2
3 4
1
1 3

```
### 样例输出 #1
```
4
2

```
## 提示

【样例解释】

一开始将第一辆车开到位置 $4$，将第二辆车开到位置 $3$，代价为 $|4-1|+|3-2|=4$。

修改后第一辆车的位置变成 $3$，代价为 $|3-3|+|4-2|=2$。

|测试点|数据范围|
|:-:|:-:|
|$1$| $n\leq 10^3$，$q=0$|
|$2$| $n\leq 10^3$，$q\leq 10^3$|
|$3$| $n\leq 10^4$，$q\leq 10^4$|
|$4$| $n\leq 5\times 10^4$，$q=0$|
|$5\sim 6$| $n\leq 3\times 10^4$，$q\leq 3\times 10^4$|
|$7\sim 10$| $n\leq 5\times 10^4$，$q\leq 5\times 10^4$|

对于 $100\%$ 的数据，$1\leq n\leq 5\times 10^4$，$0\leq q\leq 5\times 10^4$。


---

---
title: "毒瘤之神的考验"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4240
tag: ['数学', '莫比乌斯反演', '前缀和']
---
# 毒瘤之神的考验
## 题目背景

Salamander 的家门口是一条长长的公路。


又是一年春天将至，Salamander 发现路边长出了一排毒瘤！

Salamander 想带一些毒瘤回家，但是，这时毒瘤当中钻出来了一个毒瘤之神！

毒瘤之神：你想要带毒瘤走吗？想要带走毒瘤，就必须回答我的问题！如果答不出来的话，你还是乖乖回家吧！
## 题目描述

毒瘤之神会问 $T$ 次，每次给定 $n, m$，Salamander 需要回答出 $\left( \sum_{i=1}^n \sum_{j=1}^m \varphi(ij) \right)\! \bmod 998244353$。

Salamander 这么辣鸡当然不会做啦，于是把问题丢给了你。
## 输入格式

第一行包含一个正整数 $T$。

接下来 $T$ 行，每行包含两个正整数，用空格隔开，表示这次询问的 $n, m$。
## 输出格式

包含 $T$ 行，每行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
1 1
2 2
3 3
```
### 样例输出 #1
```
1
5
19
```
## 提示

对于 $40\%$ 的数据，$T=1$，$n, m \le {10}^5$。  
对于 $50\%$ 的数据，$T \le {10}^3$，$n, m \le {10}^5$。  
对于另外 $10\%$ 的数据，$T \le {10}^4$，$n = m \le {10}^5$。  
对于 $100\%$ 的数据，$1 \le T \le {10}^4$，$1 \le n, m \le {10}^5$。


---

---
title: "[BJOI2018] 链上二次求和"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4458
tag: ['2018', '线段树', '各省省选', '北京', '枚举', '前缀和', '差分']
---
# [BJOI2018] 链上二次求和
## 题目描述

有一条长度为 $n$ 的链（ $\forall 1 \leq i < n$ ，点 $i$ 与点 $i+1$ 之间有一条边的无向图）， 每个点有一个整数权值，第 $i$ 个点的权值是 $a_i$ 。现在有 $m$ 个操作，每个操作如下：

操作 1（修改）：给定链上两个节点 $u,v$ 和一个整数 $d$，表示将链上 $u$ 到 $v$ 唯一的简单路径上每个点权值都加上 $d$。

操作 2（询问）：给定两个正整数 $l,r$，表示求链上所有节点个数大于等于 $l$ 且小于等于 $r$ 的简单路径节点权值和之和。由于答案很大，只用输出对质数 $1000000007$ 取模的结果即可。

一条节点个数为 $k$ 的简单路径节点权值和为这条上所有 $k$ 个节点（包括端点）的权值之和，而本题中要求是对所有满足要求的简单路径，求这一权值和的和。

由于是无向图，路径也是无向的，即点 $1$ 到点 $2$ 的路径与点 $2$ 到点 $1$ 的路径是同一条，不要重复计算。
## 输入格式

输入第一行包含两个正整数 $n,m$，分别表示节点个数和操作次数。

第二行包含 $n$ 个整数，其中第 $i$ 个数 $a_i$ 为第 $i$ 个点的初始权值。

接下来 $m$ 行，每行为 ```1 u v d```或 ```2 l r```的形式，分别表示进行一次操作 1（修改）或操作 2（询问）。 
## 输出格式

对于每次询问，输出一行一个整数，表示答案对 $1000000007$ 取模的余数。
## 样例

### 样例输入 #1
```
5 5
1 1 1 1 1
2 5 5
2 1 2
1 1 2 2
2 1 1
1 1 5 3
```
### 样例输出 #1
```
5
13
9
```
## 提示

### 样例解释：
节点个数为 $5$ 的简单路径只有 $1$ 条，权值和为 $5$，故第1次询问输出 $5$。

节点个数为 $1$ 的简单路径有 $5$ 条，每条权值和都是 $1$；节点个数为 $2$ 的简单路径有 $4$ 条，每条权值和都是 $2$，故第2次询问输出 $13 $。

在将点 $1$ 和点 $2$ 的权值加 $2$ 后， $5$ 条节点个数为 $1$ 的简单路径权值和分别为 $3$、$3$、$1$、$1$、$1$，故第 3 次询问输出 $9$。

### 数据范围：
记操作 1（修改）的次数为 $m^\prime$。

对于全部数据， 保证 $n \leq 200000$，$m \leq 500000$，$ m^\prime \leq 100000$，$ 0 \leq a_i < 1000000007$。

$1 \leq u \leq n$，$ 1\leq v \leq n$，$ 0 \leq d < 1000000007$，$l \leq r \leq n$。

对于每个数据点的详细规模与约定见下表。

![pic](https://cdn.luogu.com.cn/upload/pic/17580.png)


---

---
title: "[JSOI2018] 防御网络"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4517
tag: ['2018', '各省省选', '江苏', '枚举', '前缀和', '概率论']
---
# [JSOI2018] 防御网络
## 题目描述

虽然成功得到了外星人的进攻计划，但 ``JYY`` 意外地发现,外星母舰对地球的攻击竟然是随机的！必须尽快在地球上部署防御网络,抵御外星人母舰的攻击。
地球上的防御网络由节点和节点之间的能量连接组成,防御网络可以看成是一个 $n$ 个点、 $m$ 条边的简单无向图 $G(V,E)$ ,每个防御节点对应 $V$ 中的一个节点、每个能量连接对应 $E$ 中的一条边。此外,在防御网络修建时考虑到能量传输效率，防御网络 $G$ 中**每个节点至多只包含在一个简单环中**。

外星母舰的攻击是随机的，每次攻击开始后， ``JYY`` 都会本次攻击的情况选择一些防御节点 $S\subseteq V$ ，并且用能量连接将这些防御节点连通，从而启动一个防御子网络。换言之， ``JYY`` 会选择 $G$ 中边集的一个子集 $H(S)\subseteq E$ ,它满足:

1.    (防御子网络**连通**) 如果我们建立新图 $G'(V,H(S))$ ，即用 $H(S)$ 中的边连接 $G$ 中的节点，则对于任意选择的防御节点 $x,y\in S$ ，它们在 $G'$​​ 中都连通。

2.    (防御子网络**最小**) 在满足条件 1 (防御子网络连通)的前提，选取的边数最小，即 $\vert H(S)\vert$ 最小。

$H(S)$ 是点集 $S$ 在图 $G$ 生成的斯坦纳树 (Steiner Tree) ，而 $\vert H(S)\vert$ 则是启动防御子网络的最小代价。考虑到外星母舰随机攻击的方式， ``JYY`` 希望你计算启动防御子网络代价的**期望**:

$$\frac{1}{2^{\vert V\vert}}\sum_{S\subseteq V}\vert H(S)\vert$$
## 输入格式

输入第一行两个整数 $n,m$ ，分别表示图中的节点数和边数。

接下来 $m$ 行,每行两个整数 $u,v(1\le u,v\le n)$ ，表示图中的一条边。输入保证没有自环和重边，并且满足每个节点至多包含在一个简单环中。
## 输出格式

输出一行，表示启动防御子网络的期望。

假设期望写成最简分式 $P/Q$ 的形式, 则输出 $P⋅Q^{-1} \text{mod 1,000,000,007}$ 的余数,其中 $Q^{-1}$​​ 为唯一的满足 $Q⋅Q^{-1} ≡ \text{1 (mod 1,000,000,007)}$ 的整数。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
```
### 样例输出 #1
```
750000006
```
### 样例输入 #2
```
6 6
1 2
2 3
3 1
1 4
2 5
3 6
```
### 样例输出 #2
```
468750006
```
## 提示

**样例解释**

样例输入 1 是一条链，包含以下情况:

1.    $\{\}, \{1\}, \{2\}, \{3\},\vert H(S)\vert = 0$ ;
2.    $\{1, 2\}, \{2, 3\}, \vert H(S)\vert = 1$ ;
3.    $\{1, 3\}, \{1, 2, 3\}, \vert H(S)\vert = 2$ 。

因此 $P/Q=3/4$ ， $P\cdot Q^{-1} = 750,000,006$ 。

样例输入 2 中 $\sum_{S\subseteq V}\vert H(S)\vert = 174$ ，因此 $P/Q=87/32$ ， $P⋅Q^{-1}=468,750,006 \text{ mod 1,000,000,007}$ 。

**数据范围**

对于 $20\%$ 的数据,有 $1\le n\le 8$ 。

对于 $40\%$ 的数据,有 $1\le n\le 20$ 。

对于 $100\%$ 的数据,有 $1\le n\le 200$ 。


---

---
title: "[SDOI2018] 物理实验"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4605
tag: ['2018', '各省省选', '平衡树', '山东', 'Special Judge', 'O2优化', '前缀和', '向量']
---
# [SDOI2018] 物理实验
## 题目描述

小 T 这学期有物理实验课，为了顺利完成下一节课的实验，他打算在课前对实验内容进行预习。

这次实验在一个二维平面上进行，平面上放置了一条无限长的直线导轨，导轨上放置了一个长为$L$的激光发射器，激光发射器会向导轨两侧沿导轨垂直方向发射宽度为$L$的激光束。

平面上还放置了 $n$ 个挡板，每个挡板可以看作是一条线段，现在每个挡板都不和直线导轨接触，且
和直线导轨的夹角不超过 $85	\degree$，任意两个挡板也不会相互接触，激光束不能穿透这些挡板，并且会被挡板吸收掉，不会被挡板反射出去。

小 T 想确定一个激光发射器的位置使得被激光束照射到的挡板长度之和最大，你需要帮小 T 算出这
个最大值。
## 输入格式

第一行包含一个正整数 T，表示测试数据的组数。

对于每组测试数据，第一行是一个整数 $n$，表示挡板个数；  
接下来 n 行，每行包含四个整数 $x1, y1, x2, y2$，表示挡板的两端点分别是 $(x1, y1)$ 和 $(x2, y2)$，保证$(x1, y1){=}\mathllap{/\,}(x2, y2)$。  
第 $n + 2$ 行是五个整数 $x1, y1, x2, y2, L$，表示直线导轨经过了点 $(x1, y1)$ 和 $(x2, y2)$，且激光发射器的长度为 $L$，同样保证 $(x1, y1)\mathrlap{\,/}{=}(x2, y2)$。
## 输出格式

对于每组测试数据，输出一行，包含一个实数，表示激光束能照射到的挡板长度之和的最大值，要求相对误差不超过 $10^{-6}$，也就是说，令输出结果为 $a$，标准答案为 $b$，若满足 $\dfrac{|a-b|}{max(1,b)}$ $≤$ $10^{-6}$，则输出结果会被认为是正确答案。
## 样例

### 样例输入 #1
```
3
4
-3 2 -1 2
-1 -1 1 -1
0 1 2 1
2 -2 4 -2
0 0 1 0 2
4
1 1 3 3
2 1 4 2
3 1 5 1
3 -1 4 -1
0 0 -1 0 2
4
-2 0 1 2
1 3 -3 2
1 -3 5 -1
2 -1 4 3
0 0 1 1 2

```
### 样例输出 #1
```
3.000000000000000
3.118033988749895
4.251303782246768

```
## 提示

- $T ≤ 100$
- $1 ≤ n ≤ 10^4$，
- $1 ≤ L ≤ 2 × 10^9$，
- 所有坐标的绝对值不超过 $10^9$。

## SubTasks

- 子任务 1 (40 分)：满足 $1 ≤ n ≤ 100$ 且所有坐标的绝对值不超过 $10^4$。
- 子任务 2 (40 分)：所有坐标的绝对值不超过 $10^6$。
- 子任务 3 (20 分)：没有任何附加的限制。



---

---
title: "『MdOI R3』Pekka Bridge Spam"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6750
tag: ['动态规划 DP', '数学', '单调队列', 'O2优化', '前缀和', '二项式定理', '生成函数', '快速数论变换 NTT', '洛谷月赛']
---
# 『MdOI R3』Pekka Bridge Spam
## 题目背景

JohnVictor 比较喜欢玩 Clash Royale。

他喜欢玩一套叫做 Pekka Bridge Spam 的卡组，然而这卡组被削弱了。现在他天梯已经掉了很多分了，不会玩了，只能在竞技场上给他的攻城锤安排地方了。

于是就有了这道题。
## 题目描述

JohnVictor 的皇室竞技场是一个 $2n \times 2m$（$2n$ 行，$2m$ 列）的方格表，他要在上面放 $n\times m$ 个 $1 \times 2$ 的攻城锤，使得任意两个攻城锤不相交。

然而攻城锤里面的野蛮人靠太近会打架，所以他要求任意一个 $2 \times 2$ 的正方形中有两个相邻的格子没有被任何攻城锤占有。

现在已经摆好了 $k$ 个攻城锤了，JohnVictor 想要知道有多少种方法能摆放这些攻城锤，注意，攻城锤两两之间没有区别。

由于这个答案实在是太大了，JohnVictor 只想知道这个答案对素数 $p$ 取模后的余数。**保证取模前的真实答案大于 $0$**。

为了避免玩过皇室的参赛者对题目理解产生问题，这里的攻城锤看做一个 $1 \times 2$ 的多米诺，翻转后也与自身一样。如果还是不理解可以参考样例。

**由于本题数据范围较大，使用 C++ 的选手可以使用以下代码来加快取模速度。**

代码出自 [KATCL](https://github.com/kth-competitive-programming/kactl/blob/master/content/various/FastMod.h) 。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2);

int main() {
    int M = 1000000007; F = FastMod(M);
    ull x = 10ULL*M+3; 
    cout << x << " " << F.reduce(x) << "\n"; // 10000000073 3
}
```

使用方法：

假设当前程序中需要取模的数为 $p$，那么就在 `main` 函数开头处调用 `F = FastMod(p);`。

计算 $a\bmod p$ 的时候调用
`
F.reduce(a);
`，
返回值就是 $a\bmod p$ 的值。
## 输入格式

第一行为四个整数 $n,m,k,p$。

接下来 $k$ 行，每行四个整数 $x_{1i},y_{1i},x_{2i},y_{2i}(1 \le i \le k)$，代表一块攻城锤的位置。

注意这里 $x,y$ 坐标表示的是在第 $x$ 行第 $y$ 列，并不是横纵坐标。
## 输出格式

一行一个整数，输出答案对 $p$ 取模后的值。
## 样例

### 样例输入 #1
```
1 2 0 19260817
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
2 2 0 19260817
```
### 样例输出 #2
```
36
```
### 样例输入 #3
```
1 2 1 19260817
1 1 2 1
```
### 样例输出 #3
```
4
```
### 样例输入 #4
```
3 3 1 19260817
1 2 1 1
```
### 样例输出 #4
```
190
```
## 提示

【样例 1 解释】   
$9$ 种情况如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/0s4px806.png)

【样例 2 解释】   
我有一种绝妙的解释方法，可惜这里位置太小，我写不下。

【样例 3 解释】  
上图中第一行的第 $1,2$ 幅和第二行的第 $1,2$ 幅图就是要求的 $4$ 种情况。

更多样例请[到这里](https://www.luogu.com.cn/paste/b2ad2hoy)领取。

【数据范围】

本题采用捆绑测试，共有 $7$ 个子任务。

对于 $100\%$ 的数据，$1 \le n \le 9 \times 10^3$，$1 \le m \le 10^{18}$，$0 \le k \le  10^5$，$|x_{1i}-x_{2i}|+|y_{1i}-y_{2i}|=1$，$1 \le x_{1i},x_{2i} \le 2n$，$1 \le y_{1i},y_{2i} \le 2m$，$10^7\le p \le 10^9 + 9 $，**输入数据保证有解且 $p$ 为素数**。

|子任务编号|$n\leq$|$m\leq$|其他性质|分值|时间限制|
|:-:|:-:|:-:|:-:|:-:|:-:|
|1|$3$|$3$||$5$|$1.0s$|
|2|$10$|$10$|$k=0$|$10$|$1.0s$|
|3|$5 \times 10^3$|$5 \times 10^3$||$13$|$2.0s$|
|4|$80$|||$17$|$1.0s$|
|5|$2\times 10^3$||$p=998244353$|$20$|$3.0s$|
|6||||$35$|$3.0s$|
【温馨提示】

为了确保卡掉小常数的错解本题开大了数据范围，请注意常数因子对程序运行效率的影响。


---

---
title: "[USACO21JAN] Paint by Letters P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7295
tag: ['图论', 'USACO', '并查集', '2021', 'cdq 分治', '广度优先搜索 BFS', '平面图欧拉公式', '前缀和', '栈', '分块']
---
# [USACO21JAN] Paint by Letters P
## 题目描述

Bessie 最近收到了一套颜料。画布可以用一个 $N×M$ 的矩形方阵表示，其中行从上往下编号为 $1…N$，列从左往右编号为 $1…M$（$1≤N,M≤1000$）。被涂色的方格的颜色可以用一个 `A` 到 `Z` 的大写字母表示。初始时，所有方格均未被涂色，每个方格至多只能被涂色一次。

Bessie 指定了每个方格她所希望的颜色。她一笔可以将一些组成连通分量的方格涂上颜色，也就是说这些方格之间可以通过相邻方格互相到达。如果两个方格有公共边则认为它们是相邻的。

例如，$3×3$ 的画布

```
AAB
BBA
BBB
```

可以用如下四笔完成涂色：

```
...    ..B    AAB    AAB    AAB
... -> ... -> ... -> BB. -> BBA
...    ...    ...    BBB    BBB
```

使用少于四笔不可能得到最终结果。

作为一名先锋派艺术家，Bessie 只会对这个画布中的一个子矩形进行涂色。现在，她正在考虑 $Q$
个候选子矩形（$1≤Q≤1000$），每一候选给定四个整数 $x_1$、$y_1$、$x_2$ 和 $y_2$，表示由第 $x_1$ 行到第 $x_2$ 行及第 $y_1$ 列到第 $y_2$ 列的所有方格组成的子矩形。

对于每个候选子矩形，将所有子矩形内的方格都涂上所希望的颜色，并且子矩形外的方格均不涂色，最少需要涂多少笔？注意在这个过程中 Bessie 并没有真正进行任何的涂色，所以对于每个候选的回答是独立的。

注意：本题每个测试点的时间限制为默认限制的 1.5 倍，且内存限制为默认限制的 2 倍，为 512MB。 
## 输入格式

输入的第一行包含 $N$、$M$ 和 $Q$。

以下 $N$ 行每行包含一个由 $M$ 个大写字母组成的字符串，表示画布每行所希望的颜色。

以下 $Q$ 行每行包含四个空格分隔的整数 $x_1,y_1,x_2,y_2$，表示一个候选子矩形（$1≤x_1≤x_2≤N$, $1≤y_1≤y_2≤M$）。
## 输出格式

对于 $Q$ 个候选子矩形的每一个，输出一行，包含答案。
## 样例

### 样例输入 #1
```
4 8 9
ABBAAAAA
ABAAAABA
CAADABBA
AAAAAAAA
1 1 4 8
3 5 3 8
1 3 2 4
1 4 2 5
1 1 3 3
4 4 4 4
2 6 4 8
3 5 4 6
1 6 3 8
```
### 样例输出 #1
```
6
3
2
1
4
1
3
2
2
```
## 提示

#### 样例 1 解释

第一个候选由整个画布组成，可以用六笔完成涂色。

第二个候选的子矩形所希望的颜色为

```
ABBA
```

可以用三笔完成涂色。注意，尽管在考虑整个画布时方格 $(3,5)$ 和 $(3,8)$ 可以用一笔涂上颜色 $A$，但如果仅考虑子矩形内的方格则并非如此。 

#### 测试点性质：

 - 测试点 1-2 满足 $N,M≤50$。
 - 测试点 3-5 中，画布不包含由单一颜色所组成的环。也就是说，不存在由不同方格所组成的序列 $c_1,c_2,c_3,…,c_k$ 满足以下条件：
   - $k>2$
   - 所有的 $c_1,…,c_k$ 颜色相同。
   - 对于所有的 $1≤i<k$，$c_i$ 与 $c_i+1$ 相邻。
   - $c_k$ 与 $c_1$ 相邻。
   注意，问题描述中的 3×3 画布包含单一颜色所组成的环（左下角的四个 B）。
 - 测试点 6-8 中，每个由相同期望颜色的方格组成的连通分量均能够被一个四边平行于坐标轴的两行两列的正方形所包含。问题描述中的 $3×3$ 画布不符合这一性质（由五个 B 组成的连通分量不能被一个两行两列的正方形包含）。
 - 测试点 9-11 中，每个由相同期望颜色的方格组成的连通分量均能够被一个四边平行于坐标轴的三行三列的正方形所包含。问题描述中的 $3×3$ 画布符合这一性质。
 - 测试点 12-20 没有额外限制。

供题：Andi Qu 


---

---
title: "更简单的排列计数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7438
tag: ['动态规划 DP', '数学', '递推', 'O2优化', '置换', '组合数学', '排列组合', '前缀和', '二项式定理', '生成函数', '线性递推', '微积分', '导数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 更简单的排列计数
## 题目描述

设 $\text{cyc}_\pi$ 将长为 $n$ 的排列 $\pi$ 当成置换时所能分解成的循环个数。给定两个整数 $n,k$ 和一个 $k-1$ 次多项式，对 $1\leq m\leq n$ 求：

$$
\sum\limits_{\pi}F(\text{cyc}_{\pi})
$$

其中 $\pi$ 是长度为 $m$ 且不存在位置 $i$ 使得 $\pi_i=i$ 的排列。
## 输入格式

第一行两个整数，表示 $n$ 和 $k$。

第二行 $k$ 个整数，从低到高给出多项式的系数。
## 输出格式

一行 $n$ 个整数，表示答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
3 2
0 1
```
### 样例输出 #1
```
0 1 2
```
### 样例输入 #2
```
6 4
11 43 27 7
```
### 样例输出 #2
```
0 88 176 1311 7332 53070
```
## 提示

### 样例解释 1

下面是当 $m=1,2,3$ 时满足要求的所有排列：

$\text{cyc}_{(2,1)}=1,\text{cyc}_{(2,3,1)}=1,\text{cyc}_{(3,1,2)}=1$。
所以当 $m=1$ 时答案为 $0$，$m=2$ 时为 $1$，$m=3$ 时为 $2$。

### 数据范围

| 子任务编号 | 分值 | $n\leq$ | $k\leq$ | 其他限制 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| Subtask 1 | $1$ | $10$ | $6$ |  |
| Subtask 2 | $5$ | $2\times 10^3$ | $6$ |  |
| Subtask 3 | $6$ | $2\times 10^5$ | $1$ |  |
| Subtask 4 | $16$ | $2\times 10^5$ | $6$ | $F(x)=x^k$ |
| Subtask 5 | $16$ | $2\times 10^5$ | $3$ |  |
| Subtask 6 | $56$ | $6\times 10^5$ | $100$ |  |

对于 $100\%$ 的数据，$1\leq n\leq 6\times 10^5$，$1\leq k\leq 100$，$0\leq [x^k]F(x)\leq 998244352$。


---

---
title: "[ICPC 2021 Macao R] the Matching System"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9657
tag: ['动态规划 DP', '2021', 'Special Judge', 'O2优化', '前缀和', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] the Matching System
## 题目描述

As the leader of the safety department, you are asked to check an ancient matching system in your company. 

The system is fed with two strings, a to-be-matched string and a pattern string, and will determine whether the former can match the latter. The former string is a strict binary string(i.e., contains only $\textbf{0}$ and $\textbf{1}$), and the latter string consists of four types of characters $\textbf{0}$, $\textbf{1}$, $\textbf{*}$, $^$, where $\textbf{*}$ means match zero or more arbitrary binary characters, and $^$ means match exactly one binary character. 

The system has two matching methods: maximum matching and minimum matching.

Consider the starting positions of the two strings. The maximum matching method will make different decisions based on the current character of the pattern string:
- $\textbf{*}$: The system will enumerate $i$ from $L$ to $0$, where $L$ is the remaining length of the to-be-matched string. Before each enumeration starts, the system consumes 1 unit of energy. Then it temporarily assumes that the current $\textbf{*}$ in the pattern string matches the consecutive $i$ characters in the to-be-matched string, and tries to match the remaining positions of two strings recursively. As long as one attempt is successful, the system will give up the remaining enumeration and stop the whole system. Otherwise, it will try the next enumeration until all attempts are tried and finally return to the previous $\textbf{*}$ enumeration.
- $\textbf{0,1}$: The system will stop and return to the previous $\textbf{*}$ enumeration if the to-be-matched string has been exhausted. Otherwise, it consumes $1$ unit of energy to compare the current characters between the pattern string and the to-be-matched string. It will continue analyzing the remaining positions of these two strings if the result is the same, otherwise, return back to the previous $\textbf{*}$ enumeration.
- $^$: The system will stop and return to the previous $\textbf{*}$ enumeration if the to-be-matched string has been exhausted. Otherwise, it consumes $1$ unit of energy and moves on of two strings.

When the pattern string is exhausted, the system will check the to-be-matched string at the same time. It will return ``Yes`` and stop the whole process if the to-be-matched string is also exhausted, otherwise, it will return to the previous $\textbf{*}$ enumeration. After all attempts are tried and no matching method is found, the system will eventually return ``No``.

Minimum matching does a similar thing except for the enumeration order of $\textbf{*}$ (i.e., enumerate $i$ from $0$ to $L$).

These two matching methods seem not very effective, so you want to hack them. Please construct both a pattern string and a to-be-matched string of length $n$ for each matching method, so that the system answers ``Yes`` and the energy consumption is as large as possible.

## 输入格式

There is only one test case in each test file.

The first and only line contains an integer $n$ ($1 \le n \le 10^3$) indicating the length of strings need to be constructed.
## 输出格式

Please output the pattern string, the to-be-matched string, and the energy cost for the maximum matching method in the first $3$ lines. Then output the pattern string, the to-be-matched string, and the energy cost for the minimum matching method in the next $3$ lines.

If there are multiple constructing ways, you can output any of them.

The energy cost may be very large, so you need to output the value modulo $(10^9+7)$. Note that this is only for your convenience and you need to maximize the energy cost before the modulus.
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
*0*
011
8
**1
101
7
```
## 提示

**【题目描述】**

作为安全部门的负责人，你被要求检查公司的一个古老匹配系统。

该系统输入两个字符串，一个待匹配字符串和一个模式字符串，并确定前者是否能匹配后者。前者字符串是严格的二进制字符串（即仅包含 $\textbf{0}$ 和 $\textbf{1}$），而后者字符串由四种类型的字符组成 $\textbf{0}$、$\textbf{1}$、$\textbf{*}$ 和 $^$，其中 $\textbf{*}$ 表示匹配零个或多个任意二进制字符，$^$ 表示匹配恰好一个二进制字符。

该系统有两种匹配方法：最大匹配和最小匹配。

考虑两个字符串的起始位置。最大匹配方法将根据模式字符串的当前字符做出不同的决定：
- $\textbf{*}$: 系统将从 $L$ 到 $0$ 枚举 $i$，其中 $L$ 是待匹配字符串的剩余长度。在每次枚举开始之前，系统消耗 1 单位的能量。然后，它临时假设模式字符串中的当前 $\textbf{*}$ 匹配待匹配字符串中的连续 $i$ 个字符，并尝试递归地匹配两个字符串的剩余位置。只要有一次尝试成功，系统将放弃剩余的枚举并停止整个系统。否则，它将尝试下一次枚举，直到所有尝试都尝试完毕，最后返回到先前的 $\textbf{*}$ 枚举。
- $\textbf{0,1}$: 如果待匹配字符串已经耗尽，则系统将停止并返回到先前的 $\textbf{*}$ 枚举。否则，它将消耗 $1$ 单位的能量来比较模式字符串和待匹配字符串之间的当前字符。如果结果相同，它将继续分析这两个字符串的剩余位置，否则，返回到先前的 $\textbf{*}$ 枚举。
- $^$: 如果待匹配字符串已经耗尽，则系统将停止并返回到先前的 $\textbf{*}$ 枚举。否则，它将消耗 $1$ 单位的能量并继续分析两个字符串。

当模式字符串耗尽时，系统将同时检查待匹配字符串。如果待匹配字符串也已经耗尽，则系统将返回“是”并停止整个过程，否则，它将返回到先前的 $\textbf{*}$ 枚举。在尝试了所有尝试并找不到匹配方法后，系统最终将返回“否”。

最小匹配执行类似的操作，除了 $\textbf{*}$ 的枚举顺序（即从 $0$ 到 $L$ 枚举 $i$）。

这两种匹配方法似乎不太有效，所以你想黑掉它们。请为每种匹配方法构造一个长度为 $n$ 的模式字符串和待匹配字符串，使得系统返回“是”，能量消耗尽可能大。

**【输入格式】**

每个测试文件中只有一个测试用例。

第一行仅包含一个整数 $n$（$1 \le n \le 10^3$），表示需要构造的字符串的长度。

请输出最大匹配方法的模式字符串、待匹配字符串和能量消耗的前 $3$ 行。然后输出最小匹配方法的模式字符串、待匹配字符串和能量消耗的后 $3$ 行。

**【输出格式】**

如果有多种构造方式，你可以输出任何一种。

能量消耗可能非常大，所以你需要输出取模 $(10^9+7)$ 后的值。请注意，这仅供您方便，您需要在取模之前最大化能量消耗。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

