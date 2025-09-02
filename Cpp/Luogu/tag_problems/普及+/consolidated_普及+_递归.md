---
title: "[常州市赛 2024] 黑板"
layout: "post"
diff: 普及+/提高
pid: B4225
tag: ['数学', '递归', '2024', '江苏', 'Special Judge', '构造', '科创活动', '小学活动']
---
# [常州市赛 2024] 黑板
## 题目背景

搬运自 <http://czoj.com.cn/p/951>。数据为民间数据。
## 题目描述

小 Y 在黑板上从小到大依次写了若干个正整数，它们分别是 $a,a+1,a+2,\cdots,b-1,b$。接下来，小 Y 会对黑板上的数进行若干次操作，一次操作是选择两个奇偶性相同的数（两个奇数或两个偶数），将他们从黑板上擦掉，再在黑板上前一个数的位置写上它们的平均数。小 Y 想知道，经过若干次操作后能否使黑板上只剩下一个数 $x$？


## 输入格式

一行 $3$ 个正整数 $a,b,x$。
## 输出格式

如果不可能使黑板上只剩下一个数 $x$，输出 `-1`，否则输出一种可行的操作方案。

一种可行的操作方案共有 $b-a$ 行，每行**先小后大**依次输出两个非负整数，表示该次操作中选择的两个数的位置，注意位置**从 $\textbf 0$ 开始**。两数之间用严格用一个空格隔开，第二个数之后没有空格。
## 样例

### 样例输入 #1
```
2 3 2
```
### 样例输出 #1
```
-1
```
### 样例输入 #2
```
2 4 3
```
### 样例输出 #2
```
0 2
0 1
```
### 样例输入 #3
```
3 6 4
```
### 样例输出 #3
```
1 3
1 2
0 1
```
## 提示

### 样例 $\textbf2$ 解释

先选择位置 $0$ 和位置 $2$ 上的数 $2$ 和 $4$ 得到平均值 $3$ 放在位置 $0$ 上，然后选择位置 $0$ 和位置 $1$ 上的数 $3$ 和 $3$ 得到平均值 $3$ 放在位置 $0$ 上。

### 数据范围

对于所有数据，$1\le a<b\le 10^5,a\le x\le b$。

|测试点编号|特殊性质|
|:-:|:-:|
|$1\sim2$|$x=b-1$|
|$3\sim4$|$a=b-1$|
|$5\sim10$|$1\le a<b\le 6$|
|$11\sim25$|无|


---

---
title: "[NOIP 2000 提高组] 方格取数"
layout: "post"
diff: 普及+/提高
pid: P1004
tag: ['动态规划 DP', '2000', '递归', 'NOIP 提高组', '费用流']
---
# [NOIP 2000 提高组] 方格取数
## 题目背景

NOIP 2000 提高组 T4
## 题目描述

设有 $N \times N$ 的方格图 $(N \le 9)$，我们将其中的某些方格中填入正整数，而其他的方格中则放入数字 $0$。如下图所示（见样例）:

![](https://cdn.luogu.com.cn/upload/image_hosting/0bpummja.png)

某人从图的左上角的 $A$ 点出发，可以向下行走，也可以向右走，直到到达右下角的 $B$ 点。在走过的路上，他可以取走方格中的数（取走后的方格中将变为数字 $0$）。  
此人从 $A$ 点到 $B$ 点共走两次，试找出 $2$ 条这样的路径，使得取得的数之和为最大。

## 输入格式

输入的第一行为一个整数 $N$（表示 $N \times N$ 的方格图），接下来的每行有三个整数，前两个表示位置，第三个数为该位置上所放的数。一行单独的 $0$ 表示输入结束。

## 输出格式

只需输出一个整数，表示 $2$ 条路径上取得的最大的和。

## 样例

### 样例输入 #1
```
8
2 3 13
2 6  6
3 5  7
4 4 14
5 2 21
5 6  4
6 3 15
7 2 14
0 0  0

```
### 样例输出 #1
```
67
```
## 提示

数据范围：$1\le N\le 9$。


---

---
title: "[NOIP 2003 提高组] 加分二叉树"
layout: "post"
diff: 普及+/提高
pid: P1040
tag: ['动态规划 DP', '2003', '递归', 'NOIP 提高组', 'Special Judge', 'O2优化', '枚举']
---
# [NOIP 2003 提高组] 加分二叉树
## 题目描述

设一个 $n$ 个节点的二叉树 $\text{tree}$ 的中序遍历为$(1,2,3,\ldots,n)$，其中数字 $1,2,3,\ldots,n$ 为节点编号。每个节点都有一个分数（均为正整数），记第 $i$ 个节点的分数为 $d_i$，$\text{tree}$ 及它的每个子树都有一个加分，任一棵子树 $\text{subtree}$（也包含 $\text{tree}$ 本身）的加分计算方法如下：


$\text{subtree}$ 的左子树的加分 $\times$ $\text{subtree}$ 的右子树的加分 $+$ $\text{subtree}$ 的根的分数。

若某个子树为空，规定其加分为 $1$，叶子的加分就是叶节点本身的分数。不考虑它的空子树。

试求一棵符合中序遍历为 $(1,2,3,\ldots,n)$ 且加分最高的二叉树 $\text{tree}$。要求输出

1. $\text{tree}$ 的最高加分。

2. $\text{tree}$ 的前序遍历。
## 输入格式

第 $1$ 行 $1$ 个整数 $n$，为节点个数。

第 $2$ 行 $n$ 个用空格隔开的整数，为每个节点的分数

## 输出格式

第 $1$ 行 $1$ 个整数，为最高加分（$ Ans \le 4,000,000,000$）。

第 $2$ 行 $n$ 个用空格隔开的整数，为该树的前序遍历。


## 样例

### 样例输入 #1
```
5
5 7 1 2 10

```
### 样例输出 #1
```
145
3 1 2 4 5

```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $1 \leq n< 30$，节点的分数是小于 $100$ 的正整数，答案不超过 $4 \times 10^9$。


---

---
title: "[NOIP 2006 提高组] 能量项链"
layout: "post"
diff: 普及+/提高
pid: P1063
tag: ['动态规划 DP', '2006', '递归', 'NOIP 提高组', '枚举', '区间 DP']
---
# [NOIP 2006 提高组] 能量项链
## 题目描述

在 Mars 星球上，每个 Mars 人都随身佩带着一串能量项链。在项链上有 $N$ 颗能量珠。能量珠是一颗有头标记与尾标记的珠子，这些标记对应着某个正整数。并且，对于相邻的两颗珠子，前一颗珠子的尾标记一定等于后一颗珠子的头标记。因为只有这样，通过吸盘（吸盘是 Mars 人吸收能量的一种器官）的作用，这两颗珠子才能聚合成一颗珠子，同时释放出可以被吸盘吸收的能量。如果前一颗能量珠的头标记为 $m$，尾标记为 $r$，后一颗能量珠的头标记为 $r$，尾标记为 $n$，则聚合后释放的能量为 $m \times r \times n$（Mars 单位），新产生的珠子的头标记为 $m$，尾标记为 $n$。

需要时，Mars 人就用吸盘夹住相邻的两颗珠子，通过聚合得到能量，直到项链上只剩下一颗珠子为止。显然，不同的聚合顺序得到的总能量是不同的，请你设计一个聚合顺序，使一串项链释放出的总能量最大。

例如：设 $N=4$，$4$ 颗珠子的头标记与尾标记依次为 $(2,3)(3,5)(5,10)(10,2)$。我们用记号 $\oplus$ 表示两颗珠子的聚合操作，$(j \oplus k)$ 表示第 $j,k$ 两颗珠子聚合后所释放的能量。则第 $4$，$1$ 两颗珠子聚合后释放的能量为：

$(4 \oplus 1)=10 \times 2 \times 3=60$。

这一串项链可以得到最优值的一个聚合顺序所释放的总能量为：

$(((4 \oplus 1) \oplus 2) \oplus 3)=10 \times 2 \times 3+10 \times 3 \times 5+10 \times 5 \times 10=710$。
## 输入格式

第一行是一个正整数 $N$（$4 \le N \le 100$），表示项链上珠子的个数。第二行是 $N$ 个用空格隔开的正整数，所有的数均不超过 $1000$。第 $i$ 个数为第 $i$ 颗珠子的头标记（$1 \le i \le N$），当 $i<N$ 时，第 $i$ 颗珠子的尾标记应该等于第 $i+1$ 颗珠子的头标记。第 $N$ 颗珠子的尾标记应该等于第 $1$ 颗珠子的头标记。

至于珠子的顺序，你可以这样确定：将项链放到桌面上，不要出现交叉，随意指定第一颗珠子，然后按顺时针方向确定其他珠子的顺序。
## 输出格式

一个正整数 $E$（$E\le 2.1 \times 10^9$），为一个最优聚合顺序所释放的总能量。

## 样例

### 样例输入 #1
```
4
2 3 5 10

```
### 样例输出 #1
```
710
```
## 提示

NOIP 2006 提高组 第一题



---

---
title: "[Code+#6] 坐标转换"
layout: "post"
diff: 普及+/提高
pid: P11442
tag: ['模拟', '递归', '进制', 'Code+']
---
# [Code+#6] 坐标转换
## 题目背景

搬运自 [Code+ 第 6 次网络赛](https://gitlink.org.cn/thusaa/codeplus6/)。
## 题目描述

在视频编码中，往往需要将一帧画面分块。

为了简化问题，我们考虑将一幅图片看作 $2^n\times 2^n$ 的网格。为了对图片进行处理，编码器往往会遍历每个格子，但遍历格子的方式在不同的应用中是不同的。

其中一种方式叫做光栅遍历，就是按照从左到右，从上到下的顺序依次进行标号。下图是一个 $8\times 8$ 的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/jzhd5wk1.png)

另一种方式叫做 Z 字型遍历。先看一个 $8\times 8$ 的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ywh3ycrt.png)

可以构造性的给出描述：

1.对于 $2^0\times2^0$ 的网格，直接遍历；

2.对于 $2^k\times2^k(k>0)$ 的网格，将其横着从中间、竖着从中间各分成两半，形成 $4$ 个 $2^{k-1}\times2^{k-1}$ 的方格，这四个方格按照左上、右上、左下、右下的顺序依次遍历。
## 输入格式

输入的第一行为两个整数 $n,m$，其中 $2^n$ 为矩形的边长，$m$ 为询问次数。

接下来 $m$ 行，每行是一个询问，每个询问给出一个方格，方式有两种，如下：

- `Z x`：给出 Z 字形遍历中标号是 $x$ 的方格。
- `R x`：给出光栅遍历中标号是 $x$ 的方格。

保证存在标号为 $x$ 的方格。
## 输出格式

对于每种询问，请输出一行一个正整数，表示在另一种遍历方式中，给出格子的标号。
## 样例

### 样例输入 #1
```
3 2
Z 37
R 37
```
### 样例输出 #1
```
35
49
```
## 提示

### 样例解释

如上图所示。

### 数据范围

对于所有数据，保证 $1\le n\le 30$，$1\le m\le 5\times10^5$。


---

---
title: "[USACO25FEB] Printing Sequences B"
layout: "post"
diff: 普及+/提高
pid: P11838
tag: ['模拟', 'USACO', '递归', '2025', '区间 DP']
---
# [USACO25FEB] Printing Sequences B
## 题目描述

Bessie 正在学习使用一种简单的编程语言进行编程。她首先定义一个合法的程序，然后执行该程序以产生一些输出序列。

### 定义：

一个程序是一个非空的语句序列。

一个语句的形式或者是 "PRINT $c$"，其中 $c$ 是一个整数，或者是 "REP $o$"，随后是一个程序，随后是 "END"，其中 $o$ 是一个不小于 1 的整数。

### 执行：

执行一个程序将依次执行其语句。

执行语句 "PRINT $c$" 将使 $c$ 追加到输出序列中。

执行以 "REP $o$" 开始的语句将依次执行内部程序共 $o$ 次。

Bessie 知道如何编写的一个程序示例如下。

```plain
REP 3
    PRINT 1
    REP 2
        PRINT 2
    END
END
```

该程序输出序列 $[1,2,2,1,2,2,1,2,2]$。

Bessie 想要输出一个包含 $N$（$1 \le N \le 100$）个正整数的序列。Elsie 挑战她使用不超过 $K$（$1 \le K \le 3$）个 "PRINT" 语句。注意，Bessie 可以使用任意数量的 "REP" 语句。同时注意，序列中的每个正整数都不超过 $K$。

对于 $T$（$1 \le T \le 100$）个独立的测试用例中的每一个，求 Bessie 是否可以编写一个程序，使用至多 $K$ 个 "PRINT" 语句输出给定的序列。
## 输入格式

输入的第一行包含 $T$。

每一个测试用例的第一行包含空格分隔的两个整数 $N$ 和 $K$。

每一个测试用例的第二行包含一个由 $N$ 个空格分隔的正整数组成的序列，每个数都不超过 $K$，为 Bessie 想要产生的序列。
## 输出格式

对于每一个测试用例输出一行，包含 "YES" 或 "NO"（大小写敏感）。

## 样例

### 样例输入 #1
```
2
1 1
1
4 1
1 1 1 1
```
### 样例输出 #1
```
YES
YES
```
### 样例输入 #2
```
11
4 2
1 2 2 2
4 2
1 1 2 1
4 2
1 1 2 2
6 2
1 1 2 2 1 1
10 2
1 1 1 2 2 1 1 1 2 2
8 3
3 3 1 2 2 1 2 2
9 3
1 1 2 2 2 3 3 3 3
16 3
2 2 3 2 2 3 1 1 2 2 3 2 2 3 1 1
24 3
1 1 2 2 3 3 3 2 2 3 3 3 1 1 2 2 3 3 3 2 2 3 3 3
9 3
1 2 2 1 3 3 1 2 2
6 3
1 2 1 2 2 3
```
### 样例输出 #2
```
YES
NO
YES
NO
YES
YES
YES
YES
YES
NO
NO
```
## 提示

样例 1 解释：

对于第二个测试用例，以下代码使用了 $1$ 个 "PRINT" 语句输出了序列 $[1,1,1,1]$。

```plain
REP 4
    PRINT 1
END
```

样例 2 解释：

对于第一个测试用例，以下代码使用了 $2$ 个 "PRINT" 语句输出了序列 $[1,2,2,2]$。

```plain
PRINT 1
REP 3
    PRINT 2
END
```

对于第二个测试用例，答案是 "NO"，因为使用不超过 $2$ 个 "PRINT" 语句输出序列 $[1,1,2,1]$ 是不可能的。

对于第六个测试用例，以下代码使用了 $3$ 个 "PRINT" 语句输出了序列 $[3,3,1,2,2,1,2,2]$。

```plain
REP 2
    PRINT 3
END
REP 2
    PRINT 1
    REP 2
        PRINT 2
    END
END
```

- 测试点 $3$：$K=1$。
- 测试点 $4\sim 7$：$K \le 2$。
- 测试点 $8\sim 13$：没有额外限制。


---

---
title: "算24点"
layout: "post"
diff: 普及+/提高
pid: P1236
tag: ['搜索', '递归', 'Special Judge', '枚举']
---
# 算24点
## 题目描述

几十年前全世界就流行一种数字游戏，至今仍有人乐此不疲．在中国我们把这种游戏称为“算 $24$ 点”。您作为游戏者将得到 $4$ 个 $1 \sim 9$ 之间的自然数作为操作数，而您的任务是对这 $4$ 个操作数进行适当的算术运算，要求运算结果等于 $24$。

您可以使用的运算只有：$\verb!+!,\verb!-!,\verb!*!,\verb!/!$，您还可以使用 $\verb!()!$ 来改变运算顺序。注意：所有的中间结果须是整数，所以一些除法运算是不允许的（例如，$(2\ \times 2)/4$ 是合法的，$2\times (2/4)$ 是不合法的）。下面我们给出一个游戏的具体例子：

若给出的 $4$ 个操作数是：$1$ 、 $2$ 、 $3$ 、 $7$，则一种可能的解答是 $1+2+3\ \times 7=24$。
## 输入格式

只有一行，四个1到9之间的自然数。

## 输出格式

如果有解的话，只要输出一个解。输出的是三行数据，分别表示运算的步骤。

- 其中第一行是输入的两个数和一个运算符和运算后的结果；
- 第二行是第一行的结果和一个输入的数据、运算符、运算后的结果，或者是另外两个数的输出结果；
- 第三行是前面的结果第二行的结果或者剩下的一个数字、运算符和 $\verb!=24!$。如果两个操作数有大小的话则先输出大的。

如果没有解则输出 `No answer!`。

如果有多重合法解，输出任意一种即可。

注：所有运算结果均为正整数。

## 样例

### 样例输入 #1
```
1 2 3 7

```
### 样例输出 #1
```
2+1=3
7*3=21
21+3=24

```
## 提示

感谢 chenyy 提供 special judge

---

$\text{upd 2022.8.1}$：新增加一组 Hack 数据。



---

---
title: "有线电视网"
layout: "post"
diff: 普及+/提高
pid: P1273
tag: ['动态规划 DP', '树形数据结构', '递归', '背包 DP']
---
# 有线电视网
## 题目描述

某收费有线电视网计划转播一场重要的足球比赛。他们的转播网和用户终端构成一棵树状结构，这棵树的根结点位于足球比赛的现场，树叶为各个用户终端，其他中转站为该树的内部节点。

从转播站到转播站以及从转播站到所有用户终端的信号传输费用都是已知的，一场转播的总费用等于传输信号的费用总和。

现在每个用户都准备了一笔费用想观看这场精彩的足球比赛，有线电视网有权决定给哪些用户提供信号而不给哪些用户提供信号。

写一个程序找出一个方案使得有线电视网在不亏本的情况下使观看转播的用户尽可能多。

## 输入格式

输入文件的第一行包含两个用空格隔开的整数 $N$ 和 $M$，其中 $2 \le N \le 3000$，$1 \le M \le N-1$，$N$ 为整个有线电视网的结点总数，$M$ 为用户终端的数量。

第一个转播站即树的根结点编号为 $1$，其他的转播站编号为 $2$ 到 $N-M$，用户终端编号为 $N-M+1$ 到 $N$。

接下来的 $N-M$ 行每行表示—个转播站的数据，第 $i+1$ 行表示第 $i$ 个转播站的数据，其格式如下：

$K \ \ A_1 \ \ C_1 \ \ A_2 \ \ C_2 \ \ \ldots \ \ A_k \ \ C_k$

$K$ 表示该转播站下接 $K$ 个结点（转播站或用户），每个结点对应一对整数 $A$ 与 $C$ ，$A$ 表示结点编号，$C$ 表示从当前转播站传输信号到结点 $A$ 的费用。最后一行依次表示所有用户为观看比赛而准备支付的钱数。单次传输成本和用户愿意交的费用均不超过 10。

[](https://paste.ubuntu.com/p/xN9NRmYvpY/)
## 输出格式

输出文件仅一行，包含一个整数，表示上述问题所要求的最大用户数。

## 样例

### 样例输入 #1
```
5 3

2 2 2 5 3

2 3 2 4 3

3 4 2
```
### 样例输出 #1
```
2


```
## 提示

**样例解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/7yj4u55m.png)

如图所示，共有五个结点。结点 ① 为根结点，即现场直播站，② 为一个中转站，③④⑤ 为用户端，共 $M$ 个，编号从 $N-M+1$ 到 $N$，他们为观看比赛分别准备的钱数为 $3$、$4$、$2$。

从结点 ① 可以传送信号到结点 ②，费用为 $2$；

也可以传送信号到结点 ⑤，费用为 $3$（第二行数据所示）；

从结点 ② 可以传输信号到结点 ③，费用为$2$；

也可传输信号到结点 ④，费用为 $3$（第三行数据所示）。

如果要让所有用户（③④⑤）都能看上比赛，则信号传输的总费用为：$2+3+2+3=10$，大于用户愿意支付的总费用 $3+4+2=9$，有线电视网就亏本了，而只让 ③④ 两个用户看比赛就不亏本了。

[](https://paste.ubuntu.com/p/H9BMGJvFHH/)


---

---
title: "欧几里德的游戏"
layout: "post"
diff: 普及+/提高
pid: P1290
tag: ['数学', '博弈论', '递归']
---
# 欧几里德的游戏
## 题目描述

欧几里德的两个后代 Stan 和 Ollie 正在玩一种数字游戏，这个游戏是他们的祖先欧几里德发明的。给定两个正整数 $M$ 和 $N$，从 Stan 开始，从其中较大的一个数，减去较小的数的正整数倍，当然，得到的数不能小于 $0$。然后是 Ollie，对刚才得到的数，和 $M,N$ 中较小的那个数，再进行同样的操作……直到一个人得到了 $0$，他就取得了胜利。下面是他们用 $(25,7)$ 两个数游戏的过程：

- 初始：$(25,7)$；
- Stan：$(11,7)$；
- Ollie：$(4,7)$；
- Stan：$(4,3)$；
- Ollie：$(1,3)$；
- Stan：$(1,0)$。

Stan 赢得了游戏的胜利。

现在，假设他们完美地操作，谁会取得胜利呢？
## 输入格式

**本题有多组测试数据。**

第一行为测试数据的组数 $C$。
下面 $C$ 行，每行为一组数据，包含两个正整数 $M,N(M,N<2^{31})$。
## 输出格式

对每组输入数据输出一行，如果 Stan 胜利，则输出 `Stan wins`；否则输出 `Ollie wins`。

## 样例

### 样例输入 #1
```
2
25 7
24 15

```
### 样例输出 #1
```
Stan wins
Ollie wins

```
## 提示

$1 \leq C \leq 6$。


---

---
title: "[GCJ 2017 #3] Googlements"
layout: "post"
diff: 普及+/提高
pid: P13175
tag: ['2017', '递归', '枚举', 'Google Code Jam']
---
# [GCJ 2017 #3] Googlements
## 题目描述

Chemists work with periodic table elements, but here at Code Jam, we have been using our advanced number smasher to study googlements. A googlement is a substance that can be represented by a string of at most nine digits. A googlement of length $L$ must contain only decimal digits in the range $0$ through $L$, inclusive, and it must contain at least one digit greater than $0$. Leading zeroes are allowed. For example, $103$ and $001$ are valid googlements of length $3$. $400$ (which contains a digit, $4$, greater than the length of the googlement, $3$) and $000$ (which contains no digit greater than 0) are not.

Any valid googlement can appear in the world at any time, but it will eventually decay into another googlement in a deterministic way, as follows. For a googlement of length $L$, count the number of $1$s in the googlement (which could be $0$) and write down that value, then count the number of $2$s in the googlement (which could be $0$) and write down that value to the right of the previous value, and so on, until you finally count and write down the number of $L$s. The new string generated in this way represents the new googlement, and it will also have length $L$. It is even possible for a googlement to decay into itself!

For example, suppose that the googlement $0414$ has just appeared. This has one $1$, zero $2$s, zero $3$s, and two $4$s, so it will decay into the googlement $1002$. This has one $1$, one $2$, zero $3$s, and zero $4$s, so it will decay into $1100$, which will decay into $2000$, which will decay into $0100$, which will decay into $1000$, which will continuously decay into itself.

You have just observed a googlement $G$. This googlement might have just appeared in the world, or it might be the result of one or more decay steps. What is the total number of possible googlements it could have been when it originally appeared in the world?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each consists of one line with a string $G$, representing a googlement.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the number of different googlements that the observed googlement could have been when it first appeared in the world.
## 样例

### 样例输入 #1
```
3
20
1
123
```
### 样例输出 #1
```
Case #1: 4
Case #2: 1
Case #3: 1
```
## 提示

**Sample Explanation**

In sample case #1, the googlement could have originally been $20$, or it could have decayed from $11$, which could have itself decayed from $12$ or $21$. Neither of the latter two could have been a product of decay. So there are four possibilities in total.

In sample case #2, the googlement must have originally been $1$, which is the only possible googlement of length $1$.

In sample case #3, the googlement must have been $123$; no other googlement could have decayed into it.

**Limits**

- $1 \leq T \leq 100$.
- Each digit in $G$ is a decimal digit between $0$ and the length of $G$, inclusive.
- $G$ contains at least one non-zero digit.

**Small dataset (3 Pts, Test Set 1 - Visible)**

- Time limit: ~~20~~ 5 seconds.
- $1 \leq$ the length of G $\leq 5$.

**Large dataset (10 Pts, Test Set 2 - Hidden)**

- Time limit: ~~60~~ 15 seconds.
- $1 \leq$ the length of G $\leq 9$.


---

---
title: "[GCJ 2011 #1A] The Killer Word"
layout: "post"
diff: 普及+/提高
pid: P13366
tag: ['模拟', '2011', '递归', '记忆化搜索', 'Google Code Jam']
---
# [GCJ 2011 #1A] The Killer Word
## 题目描述

You are playing Hangman with your friend Sean. And while you have heard that Sean is very good at taking candy from a baby, he is not as good at this game. Can you take advantage of Sean's imperfect strategy, and make him lose as badly as possible?

```
 +--+
 |  O
 | /|\       Mystery word: _ a _ a _ a _
 | / \
 |
+-+---+
```

Hangman is played as follows:

* There is a dictionary $D$ of all valid words, which both you and Sean know. A word consists only of the characters a - z. In particular, there are no spaces.
* You begin by choosing any word from $D$, and writing it down on a blackboard with each letter replaced by a blank: _.
* On his turn, Sean can choose any letter and ask you if it is in the word. If it is, you reveal all locations of that letter. Otherwise, Sean loses a point.
* Once all letters in the word have been revealed, the round ends.
* The round never ends early, no matter how many points Sean loses.

Sean uses a very simple strategy. He makes a list $L$ of the 26 letters in some order, and goes through the list one letter at a time. If there is at least one word in $D$ that (a) has the letter he is thinking of, and (b) is consistent with what you have written down so far and the result of all of Sean's previous guesses, then Sean guesses that letter. Otherwise, he skips it. No matter what, Sean then moves on to the next letter in his list.

Given Sean's list, what word should you choose to make Sean lose as many as points as possible? If several choices are equally good, you should choose the one that appears first in $D$.

**Example**

Suppose Sean decides to guess the letters in alphabetical order (i.e., $L = $ "abcdefghijklmnopqrstuvwxyz"), and $D$ contains the words banana, caravan, and pajamas. If you choose pajamas, the game would play out as follows:

* You begin by writing 7 blanks _ _ _ _ _ _ _ on the blackboard. Based on the number of blanks, Sean knows immediately that the word is either caravan or pajamas.
* Sean begins by guessing a since it is first in $L$, and you reveal all locations of the letter a on the blackboard: _ a _ a _ a _.
* Sean skips b even though it is used in banana. Sean already knows that is not your word.
* He then guesses c because it appears in caravan. It does not appear in the word you actually chose though, so Sean loses a point and nothing more is revealed.
* By process of elimination, Sean now knows your word has to be pajamas, so he proceeds to guess j, m, p, and s in order, without losing any more points.

So Sean loses one point if you choose pajamas. He would have gotten either of the other words without losing any points.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing integers $N$ and $M$, representing the number of words in the dictionary and the number of lists to consider.

The next $N$ lines contain the words in the dictionary, one per line: $D_1$, $D_2$, ..., $D_N$. Each word is an arbitrary sequence of characters a - z.

The final $M$ lines contain all of the lists Sean will use, one per line: $L_1$, $L_2$, ..., $L_M$. Each list is exactly 26 letters long, containing each letter exactly once. Sean will use these lists to guess letters as described above.

## 输出格式

For each test case, output one line containing "Case #x: $w_1$ $w_2$ ... $w_M$", where $x$ is the case number (starting from 1) and $w_i$ is the word you should choose if Sean guesses the letters in order $L_i$. If multiple words cause Sean to lose the same number of points, you should choose the option that appears first in the dictionary.
## 样例

### 样例输入 #1
```
2
3 2
banana
caravan
pajamas
abcdefghijklmnopqrstuvwxyz
etaoisnhrdlcumwfgypbvkjxqz
4 1
potato
tomato
garlic
pepper
zyxwvutsrqponmlkjihgfedcba
```
### 样例输出 #1
```
Case #1: pajamas caravan
Case #2: garlic
```
## 提示

**Limits**

- $1 \leq T \leq 10$.
- Each word in $D$ will have between $1$ and $10$ characters inclusive.
- No two words in $D$ will be the same within a single test case.

**Small dataset (10 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 100$.
- $1 \leq M \leq 10$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 10000$.
- $1 \leq M \leq 100$.
- Time limit: ~~60~~ 6 seconds.


---

---
title: "无聊的数列"
layout: "post"
diff: 普及+/提高
pid: P1438
tag: ['线段树', '树状数组', '递归', '洛谷原创', '差分']
---
# 无聊的数列
## 题目背景

无聊的 YYB 总喜欢搞出一些正常人无法搞出的东西。有一天，无聊的 YYB 想出了一道无聊的题：无聊的数列。。。
## 题目描述

维护一个数列 $a_i$，支持两种操作：

 - `1 l r K D`：给出一个长度等于 $r-l+1$ 的等差数列，首项为 $K$，公差为 $D$，并将它对应加到 $[l,r]$ 范围中的每一个数上。即：令 $a_l=a_l+K,a_{l+1}=a_{l+1}+K+D\ldots a_r=a_r+K+(r-l) \times D$。

 - `2 p`：询问序列的第 $p$ 个数的值 $a_p$。
## 输入格式

第一行两个整数数 $n,m$ 表示数列长度和操作个数。

第二行 $n$ 个整数，第 $i$ 个数表示 $a_i$。

接下来的 $m$ 行，每行先输入一个整数 $opt$。

若 $opt=1$ 则再输入四个整数 $l\ r\ K\ D$；

若 $opt=2$ 则再输入一个整数 $p$。

## 输出格式

对于每个询问，一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5 2
1 2 3 4 5
1 2 4 1 2
2 3

```
### 样例输出 #1
```
6
```
## 提示

#### 数据规模与约定

对于 $100\%$ 数据，$0\le n,m \le 10^5,-200\le a_i,K,D\le 200, 1 \leq l \leq r \leq n, 1 \leq p \leq n$。


---

---
title: "[NOIP 2010 提高组] 乌龟棋"
layout: "post"
diff: 普及+/提高
pid: P1541
tag: ['动态规划 DP', '2010', '递归', 'NOIP 提高组', '枚举']
---
# [NOIP 2010 提高组] 乌龟棋
## 题目背景

NOIP2010 提高组 T2
## 题目描述

小明过生日的时候，爸爸送给他一副乌龟棋当作礼物。

乌龟棋的棋盘是一行 $N$ 个格子，每个格子上一个分数（非负整数）。棋盘第 $1$ 格是唯一的起点，第 $N$ 格是终点，游戏要求玩家控制一个乌龟棋子从起点出发走到终点。

乌龟棋中 $M$ 张爬行卡片，分成 $4$ 种不同的类型（$M$ 张卡片中不一定包含所有 $4$ 种类型的卡片，见样例），每种类型的卡片上分别标有 $1,2,3,4$ 四个数字之一，表示使用这种卡片后，乌龟棋子将向前爬行相应的格子数。游戏中，玩家每次需要从所有的爬行卡片中选择一张之前没有使用过的爬行卡片，控制乌龟棋子前进相应的格子数，每张卡片只能使用一次。


游戏中，乌龟棋子自动获得起点格子的分数，并且在后续的爬行中每到达一个格子，就得到该格子相应的分数。玩家最终游戏得分就是乌龟棋子从起点到终点过程中到过的所有格子的分数总和。


很明显，用不同的爬行卡片使用顺序会使得最终游戏的得分不同，小明想要找到一种卡片使用顺序使得最终游戏得分最多。


现在，告诉你棋盘上每个格子的分数和所有的爬行卡片，你能告诉小明，他最多能得到多少分吗？

## 输入格式

每行中两个数之间用一个空格隔开。

第 $1$ 行 $2$ 个正整数 $N,M$，分别表示棋盘格子数和爬行卡片数。


第 $2$ 行 $N$ 个非负整数，$a_1,a_2,…,a_N$，其中 $a_i$ 表示棋盘第 $i$ 个格子上的分数。


第 $3$ 行 $M$ 个整数，$b_1,b_2,…,b_M$，表示 $M$ 张爬行卡片上的数字。


输入数据保证到达终点时刚好用光 $M$ 张爬行卡片。


## 输出格式

一个整数，表示小明最多能得到的分数。

## 样例

### 样例输入 #1
```
9 5
6 10 14 2 8 8 18 5 17
1 3 1 2 1

```
### 样例输出 #1
```
73

```
## 提示

每个测试点 1s。

小明使用爬行卡片顺序为 $1,1,3,1,2$，得到的分数为 $6+10+14+8+18+17=73$。注意，由于起点是 $1$，所以自动获得第 $1$ 格的分数 $6$。


对于 $30\%$ 的数据有 $1≤N≤30,1≤M≤12$。


对于 $50\%$ 的数据有 $1≤N≤120,1≤M≤50$，且 $4$ 种爬行卡片，每种卡片的张数不会超过 $20$。


对于 $100\%$ 的数据有 $1≤N≤350,1≤M≤120$，且 $4$ 种爬行卡片，每种卡片的张数不会超过 $40$；$0≤a_i≤100,1≤i≤N,1≤b_i≤4,1≤i≤M$。



---

---
title: "偶数"
layout: "post"
diff: 普及+/提高
pid: P1762
tag: ['数学', '递归']
---
# 偶数
## 题目描述

给定一个正整数 $n$，请输出杨辉三角形前 $n$ 行的偶数个数对 $1000003$ 取模后的结果。

## 输入格式

一行一个正整数 $n$。

## 输出格式

一行一个整数表示答案。
## 样例

### 样例输入 #1
```
6

```
### 样例输出 #1
```
6

```
## 提示

对于 $30\%$ 的数据，$n\le 4\times 10^3$。

对于 $70\%$ 的数据，$n\le 4\times 10^9$。

对于 $100\%$ 的数据，$1\le n\le 10^{15}$。

杨辉三角形的前七行：

```plain
       1
      1 1
     1 2 1
    1 3 3 1
   1 4 6 4 1
 1 5 10 10 5 1
1 6 15 20 15 6 1
```


---

---
title: "直线交点数"
layout: "post"
diff: 普及+/提高
pid: P2789
tag: ['模拟', '数学', '递归']
---
# 直线交点数
## 题目描述

假设平面上有 $N$ 条直线，且无三线共点，那么这些直线有多少种可能的交点数？
## 输入格式

一行，一个整数 $N$，代表有 $N$ 条直线。
## 输出格式

一行，一个整数，表示方案总数。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
5
```
## 提示

对于所有数据，满足 $1 \le N \le 25$。


---

---
title: "神秘数字"
layout: "post"
diff: 普及+/提高
pid: P2804
tag: ['搜索', '数学', '线性数据结构', '二分', '递归']
---
# 神秘数字
## 题目背景

在公元XXXX年，侦探小明收到了组织的神秘信息，在Y市的某个地方有一道神秘的门。小明到达了那个门后，发现门上有一行字：“这个门需要密码才能解锁。”小明左找右找，终于找到了一张字条：“现在给你n个数，请你求出这n个数里面，有多少个连续的数的平均数大于某个给定的数M？注意：这个数可能会很大，请输出这个数对92084931取模的结果。最终的结果即是这个门的密码。”小明苦思冥想了半天，但始终找不到答案。于是他来求助于你。请你帮他解决这个问题。由于小明十分着急，他最多只能等1秒。

## 题目描述

给定n个数，请你帮助小明求出里面有多少个连续的数的平均数大于给定的某个数M.并将这个方案数输出。注意：这个数可能会很大，所以请输出这个数对92084931取模的结果。

## 输入格式

两行。第一行为两个数n和M。第二行为n个数。

## 输出格式

一行一个数，即问题的解对92084931取模的结果

## 样例

### 样例输入 #1
```
4 3
1 5 4 2
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
4 4
5 2 7 3
```
### 样例输出 #2
```
6
```
## 提示

【样例解释】

①对于这4个数，问题的解有{5}，{4}，{5,4}，{1,5,4}，{5,4,2}共5组。

②对于这4个数，问题的解有{5}，{7}，{2,7}，{7,3}，{5,2,7}，{5,2,7,3}共6组。

【数据规模】

对于10%的数据，1＜n≤10.

对于30%的数据，1＜n≤1000.

对于50%的数据，1＜n≤30000.

对于100%的数据，1＜n≤200000，1＜M≤3000，每个数均为正整数且不大于5000.



---

---
title: "[AHOI2017初中组] rexp"
layout: "post"
diff: 普及+/提高
pid: P3719
tag: ['模拟', '字符串', '2017', '递归', '安徽', '栈']
---
# [AHOI2017初中组] rexp
## 题目背景

为了解决形形色色的字符串匹配问题，正则表达式是一个强有力的工具。正则表达式通过定义一套符号体系，能够表示出需要查找的字符串所具有的性质。如 `a|aa` 能匹配 `a` 或 `aa`，`(a|b)c` 能匹配 `ac` 或 `bc`。

## 题目描述

完整的正则表达式过于复杂，在这里我们只考虑由 `(`、`)`、`|` 和 `a` 组成的正则表达式。运算遵循下列法则：

1. 有括号时，我们总是先算括号内的部分；

2. 当两个字符串（或由括号定义的子串）间没有符号时，我们总把它们连起来作为一个整体；

3. `|` 是或连接符，表示两边的字符串任取其一，若同一层里有多个或连接符，可以看作在这些或连接符所分开的若干字符串里任取其一。

例如，`(aaa)aa|aa|(a(aa)a)`、`(aaaaa)|(aa)|aaaa` 和 `aaaaa|aaaa|aa` 是等价的，它们都能匹配长度为 $2,4$ 或 $5$ 的全 `a` 字符串。

下面给定一个简化正则表达式，试编程计算它最多能匹配多长的全 `a` 字符串。
## 输入格式

输入一行一个合法的简化正则表达式。

## 输出格式

一行一个整数，表示能匹配的最长全 `a` 字符串长度。
## 样例

### 样例输入 #1
```
(aaa)aa|aa|(a(aa)a)
```
### 样例输出 #1
```
5

```
### 样例输入 #2
```
((a|aaa)|aa)|a
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
(a(aa|aaa)a|(a|aa))aa
```
### 样例输出 #3
```
7
```
## 提示

**【数据范围】**

对于 $20\%$ 数据，表达式长度不超过 $100$，且不存在括号。

对于 $40\%$ 数据，表达式长度不超过 $100$。

对于 $70\%$ 数据，表达式长度不超过 $2 \times 10^3$。

对于 $100\%$ 的数据，表达式长度不超过 $10^5$。

保证表达式合法（即 `|` 两端和括号内运算结果均非空字符串）。


---

---
title: "绿豆蛙的归宿"
layout: "post"
diff: 普及+/提高
pid: P4316
tag: ['递归', '拓扑排序', '期望', '栈']
---
# 绿豆蛙的归宿
## 题目背景

随着新版百度空间的上线，Blog 宠物绿豆蛙完成了它的使命，去寻找它新的归宿。
## 题目描述

给出张 $n$ 个点 $m$ 条边的有向无环图，起点为 $1$，终点为 $n$，每条边都有一个长度，并且从起点出发能够到达所有的点，所有的点也都能够到达终点。

绿豆蛙从起点出发，走向终点。 到达每一个顶点时，如果该节点有 $k$ 条出边，绿豆蛙可以选择任意一条边离开该点，并且走向每条边的概率为 $\frac{1}{k}$ 。现在绿豆蛙想知道，从起点走到终点的所经过的路径总长度期望是多少？
## 输入格式

输入的第一行是两个整数，分别代表图的点数 $n$ 和边数 $m$。

第 $2$ 到第 $(m + 1)$ 行，每行有三个整数 $u, v, w$，代表存在一条从 $u$ 指向 $v$ 长度为 $w$ 的有向边。
## 输出格式

输出一行一个实数代表答案，四舍五入保留两位小数。
## 样例

### 样例输入 #1
```
4 4 
1 2 1 
1 3 2 
2 3 3 
3 4 4
```
### 样例输出 #1
```
7.00
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 10^2$。
- 对于 $40\%$ 的数据，保证 $n \leq 10^3$。
- 对于 $60\%$ 的数据，保证 $n \leq 10^4$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$1 \leq m \leq 2 \times n$，$1 \leq u, v \leq n$，$0 \leq w \leq 10^9$，给出的图无重边和自环。


---

---
title: "[CQOI2007] 三角形"
layout: "post"
diff: 普及+/提高
pid: P4536
tag: ['字符串', '2007', '重庆', '各省省选', '递归', '深度优先搜索 DFS']
---
# [CQOI2007] 三角形
## 题目描述

画一个等边三角形，把三边的中点连接起来，得到四个三角形，把它们称为 $T_1,T_2,T_3,T_4$，如图1。

把前三个三角形也这样划分，得到 $12$ 个更小的三角形，$T_{11},T_{12},T_{13},T_{14},T_{21},T_{22},T_{23},T_{24},T_{31},T_{32},T_{33},T_{34}$，如图2。

把编号以 $1,2,3$ 结尾的三角形又继续划分……最后得到的分形称为 Sierpinski 三角形。

![](https://cdn.luogu.com.cn/upload/pic/18501.png)

如果三角形 $B$ 不包含三角形 $A$，且 $A$ 的某一条完整的边是 $B$ 的某条边的一部分，则我们说 $A$ 靠在 $B$ 的边上。例如 $T_{12}$ 靠在 $T_{14}$ 和 $T_4$ 上，但不靠在 $T_{32}$ 上。

给出 Spierpinski 三角形中的一个三角形，找出它靠着的所有三角形。
## 输入格式

输入仅一行，即三角形的编号，以 `T` 开头，后面有 $n$ 个 $1$ 到 $4$ 的数字。仅最后一个数字可能为 $4$。
## 输出格式

输出每行一个三角形编号，按字典序从小到大排列。

## 样例

### 样例输入 #1
```
T312
```
### 样例输出 #1
```
T314
T34
T4
```
## 提示

对于 $100 \%$ 的数据，$1 \le n \le 50$。


---

---
title: "「化学」相对分子质量"
layout: "post"
diff: 普及+/提高
pid: P4711
tag: ['模拟', '字符串', '递归', 'Special Judge', 'O2优化', '洛谷月赛']
---
# 「化学」相对分子质量
## 题目描述

做化学题时，小 F 总是里算错相对分子质量，这让他非常苦恼。

小 F 找到了你，请你来帮他算一算给定物质的相对分子质量。

如果你没有学过相关内容也没有关系，你可以从样例和提示里理解该题所求内容。
## 输入格式

输入一行，为一个长度为 $L$ $(L\leq 100)$ 的不含空格的字符串，表示给定物质的化学式。

化学式仅包括以下内容:

* 元素：如 `Au`(金)，`Hf`(铪)，**出现的所有元素及其相对原子质量以附表为准**。
* 下标 `_{}` ：表示某个原子、离子或者原子团的个数，如 `H_{2}O` 表示 $H_2O$ (水)，`C_{60}` 表示 $C_{60}$ (足球烯)。
* 括号 `()`：表示一个原子团，下标对团内物质生效。如 `Ca(OH)_{2}` 表示 $Ca(OH)_2$ (熟石灰)。
* 水合物 `~`：如 `CuSO_{4}~5H_{2}O` 表示 $CuSO_4 \cdot 5H_2O$（胆矾）。水之前如果存在数字，保证一定是大于 $2$ 的正整数，如果省略该部分则默认为 $1$ 。如上述胆矾中，表示水的个数的 `5`。

形式化地讲，你处理的化学式满足以下规则：

> 分子`~`数量`H_{2}O` 

其中数量或水合部分可省。

对于分子，满足：

> 部分`_{`数量`}`部分`_{`数量`}`...部分`_{`数量`}`

其中数量可省。

对于每个“部分”（原子，原子团，离子……），满足：

> 元素

或

> `(`元素`_{` 数量 `}`元素`_{` 数量`}`... 元素`_{`数量`})`

其中数量可省。

请注意，满足上述条件的化学式不会出现括号嵌套；上文中出现的 “数量” 所指代的数字不超过 $10000$。
## 输出格式

输出一行，包含一个整数或者小数部分为 `.5` 的实数，为你的计算结果。

保证结果不超过 $10000$。

## 样例

### 样例输入 #1
```
Au
```
### 样例输出 #1
```
197
```
### 样例输入 #2
```
HfO_{2}
```
### 样例输出 #2
```
210.5
```
### 样例输入 #3
```
Ca(OH)_{2}
```
### 样例输出 #3
```
74
```
### 样例输入 #4
```
CuSO_{4}~5H_{2}O
```
### 样例输出 #4
```
250
```
### 样例输入 #5
```
KAl(SO_{4})_{2}~12H_{2}O
```
### 样例输出 #5
```
474
```
## 提示

### 样例解释
金 $Au : 197$

二氧化铪 $HfO_{2}: 178.5 + 2 \times 16= 210.5$

氢氧化钙（熟石灰）$Ca(OH)_2 : 40 + (1 + 16) \times 2 = 74$

五水硫酸铜（胆矾）$CuSO_4 \cdot 5H_2O: 64 + 32 + 16 \times 4 + 5 \times (1 \times 2 + 16) = 250$

十二水合硫酸铝钾（明矾）$KAl(SO_{4})_{2} \cdot 12H_{2}O$ （嗯 用心感受 $474$ 是对的）

### 附表：可能用到的相对原子质量

|元素|相对原子质量|
|:-:|:-:|
|H|1|
|C|12|
|N|14|
|O|16|
|F|19|
|Na|23|
|Mg|24|
|Al|27|
|Si|28|
|P|31|
|S|32|
|Cl|35.5|
|K|39|
|Ca|40|
|Mn|55|
|Fe|56|
|Cu|64|
|Zn|65|
|Ag|108|
|I|127|
|Ba|137|
|Hf|178.5|
|Pt|195|
|Au|197|
|Hg|201|

### 提示

如果你没有学习过相关内容，下面的内容可能有帮助：

> zcy 教你算相对分子质量

1. 每个元素以大写开头；
2. 计算分子质量的方法就是对每个原子出现的次数乘对应的相对原子质量求和；
3. ~( $\cdot$ ) 相当于加；
4. 下标相当于乘。


---

---
title: "[COCI 2020/2021 #1] Papričice"
layout: "post"
diff: 普及+/提高
pid: P7165
tag: ['树形数据结构', '2020', '递归', 'COCI（克罗地亚）']
---
# [COCI 2020/2021 #1] Papričice
## 题目描述

给定一个 $n$ 个点的树，这 $n$ 个点编号为 $1$ 到 $n$。

现在要选择断掉两条边，会形成三个连通块，假设这三个连通块内的点数分别为 $a,b,c$，那么您要做的就是最小化 $\max\{a,b,c\}-\min\{a,b,c\}$ 的大小，求这个最小值。
## 输入格式

第一行一个整数 $n$ 代表树的点数。        
接下来 $n-1$ 行每行两个整数 $x,y$ 代表树的一条边。
## 输出格式

一行一个整数代表答案。
## 样例

### 样例输入 #1
```
4
1 2
2 3
3 4

```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
6
1 2
1 3
3 4
3 5
5 6
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
9
1 3
2 3
3 4
3 5
5 6
5 7
7 8
7 9
```
### 样例输出 #3
```
2
```
## 提示

#### 样例 1 解释

能构造的最优解三个连通块的点数都为 $1,1,2$，所以输出 $2-1=1$。

#### 样例 2 解释

断掉点 $1$ 到点 $3$ 的边，点 $3$ 到点 $5$ 的边，形成的三个连通块点数相同。

#### 样例 3 解释

如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/nybys0n6.png)

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（15 pts）：$3 \le n \le 200$。
- Subtask 2（35 pts）：$3 \le n \le 2000$。
- Subtask 3（60 pts）：$3 \le n \le 2 \times 10^5$。

对于 $100\%$ 的数据，$1 \le x,y \le n$。

**本题满分 $110$ 分。**

#### 说明

翻译自 [Croatian Open Competition in Informatics 2020 ~ 2021 Round 1 D Papričice
](https://hsin.hr/coci/contest1_tasks.pdf)。


---

---
title: "[蓝桥杯 2017 省 A] 正则问题"
layout: "post"
diff: 普及+/提高
pid: P8650
tag: ['2017', '递归', '蓝桥杯省赛']
---
# [蓝桥杯 2017 省 A] 正则问题
## 题目描述

考虑一种简单的正则表达式：

只由 `x` `(` `)` `|` 组成的正则表达式。

小明想求出这个正则表达式能接受的最长字符串的长度。  

例如 `((xx|xxx)x|(x|xx))xx` 能接受的最长字符串是： `xxxxxx`，长度是 $6$。

## 输入格式

一个由 `x()|` 组成的正则表达式。输入长度不超过 $100$，保证合法。
## 输出格式

这个正则表达式能接受的最长字符串的长度。  
## 样例

### 样例输入 #1
```
((xx|xxx)x|(x|xx))xx  
```
### 样例输出 #1
```
6
```
## 提示

蓝桥杯 2022 省赛 A 组 G 题。


---

