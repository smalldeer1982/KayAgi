---
title: "[语言月赛202305] 你的牌太多了 2"
layout: "post"
diff: 普及/提高-
pid: B3767
tag: ['2023', 'O2优化', '函数与递归', '语言月赛']
---
# [语言月赛202305] 你的牌太多了 2
## 题目背景

相信你对笨蛋扶苏和坏蛋小 F 打牌的[故事](https://www.luogu.com.cn/problem/B3745)记忆犹新。这次，她们又在打一种很新的牌。
## 题目描述

初始时，扶苏和小 F 手中各有 $n$ 张牌。每张牌有一个花色 $f$ 和一个点数 $p$。在本题中，花色是不超过 $m$ 的正整数，点数是不超过 $r$ 的正整数。

我们定义『一轮出牌』是指从某人开始出牌，双方轮流按规则打出手中的手牌，直到一方打不出符合要求的手牌结束。

在一轮出牌中，第一个出牌的人会打出**点数最小**的那张手牌。如果有多张手牌点数最小，则打出**点数最小且花色最小的那张手牌**。然后双方轮流出牌，规则是打出手中**花色与对方刚才打出的牌相同且点数大于对方的刚才打出的牌的点数中，点数最小的那张牌**。如果这样的牌不存在，那么本轮游戏结束，且下一轮由**对方**先出牌（即，本轮最后一手出牌的人下一轮先出）。

现在，给出双方的手牌和第一轮出牌的人，请你求出谁先打完手里的牌。
## 输入格式

**本题单测试点内有多组测试数据**。

输入的第一行是一个整数，表示测试数据的组数 $T$。接下来依次给出每组数据的输入信息：

第一行是四个整数，表示一个人的手牌数 $n$，花色的上界 $m$ ，点数的上界 $r$ 和第一轮出牌的人 $s$。$s = 1$ 表示扶苏先出牌，$s = 2$ 表示小 F 先出牌。  
第二行有 $n$ 个整数，第 $i$ 个整数表示扶苏第 $i$ 张牌的花色 $f1_i$。  
第三行有 $n$ 个整数，第 $i$ 个整数表示扶苏第 $i$ 张牌的点数 $p1_i$。  
第四行有 $n$ 个整数，第 $i$ 个整数表示小 F 第 $i$ 张牌的花色 $f2_i$。  
第五行有 $n$ 个整数，第 $i$ 个整数表示小 F 第 $i$ 张牌的点数 $p2_i$。  
## 输出格式

对每组数据，输出一行一个字符串。如果扶苏先打完手里的牌，请输出 `FS wins!`；如果小 F 先打完手里的牌，请输出 `FR wins!`。
## 样例

### 样例输入 #1
```
1
3 1 2 1
1 1 1
1 2 1
1 1 1
2 2 1
```
### 样例输出 #1
```
FS wins!
```
### 样例输入 #2
```
1
3 1 2 2
1 1 1
1 2 1
1 1 1
2 2 1
```
### 样例输出 #2
```
FR wins!
```
## 提示

## 数据规模与约定

- 对于 $10\%$ 的数据，$r = 1$；
- 对于 $20\%$ 的数据，$n = 1$；
- 对于 $50\%$ 的数据，$m = 1$；
- 对于 $100\%$ 的数据，$1 \leq T \leq 10$，$1 \leq n,m,r \leq 100$，$1 \leq s \leq 2$，$1 \leq f1_i, f2_i \leq m$，$1 \leq p1_i, p2_i \leq r$。


---

---
title: "[信息与未来 2023] 程序分析"
layout: "post"
diff: 普及/提高-
pid: B3789
tag: ['模拟', '递归', '2023', '江苏', '信息与未来']
---
# [信息与未来 2023] 程序分析
## 题目描述

程序分析技术是一种用于理解和改进计算机程序的方法。它可以帮助我们找出程序中的错误、提高程序的性能、优化代码结构等。其中，静态分析技术在不运行程序的情况下对程序代码进行分析。它可以检查代码的语法、风格、潜在错误等。例如，静态分析可以帮助我们找出程序中未使用的变量、可能的数组越界等问题。

小小设计了一个自己的编程语言，并命名为 X 语言。你能为它设计一个静态分析器吗？

X 语言程序中只有两个整型变量 $x$ 和 $y$，且无需定义，可以直接使用。变量 $x$ 的值从程序外输入（输入值可以是任何 C++ int 范围内的值），$y$ 的初始值是 $0$。一个 X 语言程序由若干行组成，每行恰好包含一条命令，是以下三种命令之一：
1. 条件分支：`if (条件) {`；
2. 对 $y$ 赋值：`y = 数字;`；
3. 条件结束：`}`。

其中，“条件”要么是 `x > 数字`，要么是 `x < 数字`。赋值语句和条件中的“数字”都是 $1$ 到 $10^9$ 之间的常数。`if` 和赋值的含义同 C++ 语言中的条件和赋值语句。

请你编写一个静态分析器，分析一个 X 语言程序执行结束时，所有可能的 $y$ 的值。
## 输入格式

输入数据第一行为整数 $n$，代表程序的行数。

接下来 $n$ 行，每行一个命令，描述了一个合法的 X 语言程序：输入的程序保证括号配对，且符合问题描述中的约定。为了便于大家解析 (例如用 `cin` 或 `scanf` 读入)，输入程序中的 `if` 后、`{` 前、`=`、`<`、`>` 左右都恰好有一个空格，行首可能有若干空格缩进。除此之外，输入不含多余的空格或空白字符。
## 输出格式

输出一行，从小到大不重复地输出程序结束时，变量 $y$ 所有可能的值。数字之间由一个空格隔开。
## 样例

### 样例输入 #1
```
10
if (x > 1) {
  y = 2;
  if (x > 10) {
    y = 1;
    y = 4;
    if (x < 5) {
      y = 3;
    }
  }
}
```
### 样例输出 #1
```
0 2 4
```
### 样例输入 #2
```
(见 p4.zip 中的 2-in.txt)
```
### 样例输出 #2
```
(见 p4.zip 中的 2-out.txt)
```
### 样例输入 #3
```
(见 p4.zip 中的 3-in.txt)
```
### 样例输出 #3
```
(见 p4.zip 中的 3-out.txt)
```
## 提示

对于 $100\%$ 的数据，满足 $1\le n \le 10^3$。输入数据的每行都不超过 $10^3$ 个字符。

>本题原始满分为 $20\text{pts}$。


---

---
title: "[GESP202306 四级] 图像压缩"
layout: "post"
diff: 普及/提高-
pid: B3851
tag: ['模拟', '2023', '函数与递归', 'GESP']
---
# [GESP202306 四级] 图像压缩
## 题目描述

图像是由很多的像素点组成的。如果用 $0$ 表示黑，$255$ 表示白，$0$ 和 $255$ 之间的值代表不同程度的灰色，则可以用一个字节表达一个像素（取值范围为十进制 `0-255`、十六进制 `00-FF`）。这样的像素组成的图像，称为 $256$ 级灰阶的灰度图像。

现在希望将 $256$ 级灰阶的灰度图像压缩为 $16$ 级灰阶，即每个像素的取值范围为十进制 `0-15`、十六进制 `0-F`。压缩规则为：统计出每种灰阶的数量，取数量最多的前 $16$ 种灰阶（如某种灰阶的数量与另外一种灰阶的数量相同，则以灰阶值从小到大为序），分别编号 `0-F`（最多的编号为 `0`，以此类推）。其他灰阶转换到最近的 $16$ 种灰阶之一，将某个点的灰阶值（灰度，而非次数）与 $16$ 种灰阶中的一种相减，绝对值最小即为最近，如果绝对值相等，则编号较小的灰阶更近。
## 输入格式

输入第 $1$ 行为一个正整数 $n(10\le n \le 20)$，表示接下来有 $n$ 行数据组成一副 $256$ 级灰阶的灰度图像。

第 $2$ 行开始的 $n$ 行，每行为长度相等且为偶数的字符串，每两个字符用十六进制表示一个像素。约定输入的灰度图像至少有 $16$ 种灰阶。约定每行最多 $20$ 个像素。
## 输出格式

第一行输出压缩选定的 $16$ 种灰阶的十六进制编码，共计 $32$ 个字符。

第二行开始的 $n$ 行，输出压缩后的图像，每个像素一位十六进制数表示压缩后的灰阶值。
## 样例

### 样例输入 #1
```
10
00FFCFAB00FFAC09071B5CCFAB76
00AFCBAB11FFAB09981D34CFAF56
01BFCEAB00FFAC0907F25FCFBA65
10FBCBAB11FFAB09981DF4CFCA67
00FFCBFB00FFAC0907A25CCFFC76
00FFCBAB1CFFCB09FC1AC4CFCF67
01FCCBAB00FFAC0F071A54CFBA65
10EFCBAB11FFAB09981B34CFCF67
01FFCBAB00FFAC0F071054CFAC76
1000CBAB11FFAB0A981B84CFCF66
```
### 样例输出 #1
```
ABCFFF00CB09AC07101198011B6776FC
321032657CD10E
36409205ACC16D
B41032657FD16D
8F409205ACF14D
324F326570D1FE
3240C245FC411D
BF4032687CD16D
8F409205ACC11D
B240326878D16E
83409205ACE11D
```
## 提示

【样例 $1$ 解释】

灰阶 `AB`、`CF` 和 `FF` 出现 $14$ 次，`00` 出现 $10$ 次，`CB` 出现
$9$ 次，`09` 出现 $7$ 次，`AC` 出现 $6$ 次，`07` 出现 $5$ 次，`10`、`11`
和 `98` 出现 $4$ 次，`01`、`1B`、`67`、`76` 和 `FC` 出现 $3$ 次。


---

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
title: "[ROIR 2023] 斐波那契乘积 (Day 1)"
layout: "post"
diff: 普及/提高-
pid: P10095
tag: ['搜索', '数学', '递归', '2023', 'Special Judge', '枚举', '深度优先搜索 DFS', '斐波那契数列', 'ROIR（俄罗斯）']
---
# [ROIR 2023] 斐波那契乘积 (Day 1)
## 题目背景

翻译自 [ROIR 2023 D1T2](https://neerc.ifmo.ru/school/archive/2022-2023/ru-olymp-regional-2023-day1.pdf)。

斐波那契数指斐波那契数列（$f_0=1,f_1=1,f_i=f_{i-2}+f_{i-1}$）中出现的数。
## 题目描述

给定一个自然数 $n$，求出将其表示为若干个大于 $1$ 的斐波那契数的乘积的方案数。
## 输入格式

第一行一个数 $t$，表示数据组数。

接下来 $t$ 行，每行输入一个数 $n$。
## 输出格式

对于每组测试数据，输出一个数表示答案。
## 样例

### 样例输入 #1
```
5
2
7
8
40
64
```
### 样例输出 #1
```
1
0
2
2
3
```
## 提示

样例解释：
- $2=2$。
- $7$ 无法被表示为斐波那契乘积。
- $8=8=2\times2\times2$。
- $40=5\times8=2\times2\times2\times5$。
- $64=8\times8=2\times2\times2\times8=2\times2\times2\times2\times2\times2$。

本题使用捆绑测试。

| 子任务编号 | 分值 | $2\le n\le$ |
| :----------: | :----------: | :----------: |
| $1$ | $15$ | $100$ |
| $2$ | $17$ | $10^5$ |
| $3$ | $9$ | $n$ 是 $2$ 的整数次幂 |
| $4$ | $38$ | $10^9$ |
| $5$ | $21$ | $10^{18}$ |

对于所有数据，$1\le t\le50$，$2\le n\le10^{18}$。


---

---
title: "[NOIP 1999 提高组] 旅行家的预算"
layout: "post"
diff: 普及/提高-
pid: P1016
tag: ['贪心', '1999', '递归', 'NOIP 普及组', 'NOIP 提高组']
---
# [NOIP 1999 提高组] 旅行家的预算
## 题目描述

一个旅行家想驾驶汽车以最少的费用从一个城市到另一个城市（假设出发时油箱是空的）。给定两个城市之间的距离 $D_1$、汽车油箱的容量 $C$（以升为单位）、每升汽油能行驶的距离 $D_2$、出发点每升汽油价格$P$和沿途油站数 $N$（$N$ 可以为零），油站 $i$ 离出发点的距离 $D_i$、每升汽油价格 $P_i$（$i=1,2,…,N$）。计算结果四舍五入至小数点后两位。如果无法到达目的地，则输出 `No Solution`。

## 输入格式

第一行，$D_1$，$C$，$D_2$，$P$，$N$。

接下来有 $N$ 行。

第 $i+1$ 行，两个数字，油站 $i$ 离出发点的距离 $D_i$ 和每升汽油价格 $P_i$。

## 输出格式

所需最小费用，计算结果四舍五入至小数点后两位。如果无法到达目的地，则输出 `No Solution`。

## 样例

### 样例输入 #1
```
275.6 11.9 27.4 2.8 2
102.0 2.9
220.0 2.2

```
### 样例输出 #1
```
26.95

```
## 提示

$N \le 6$，其余数字 $ \le 500$。

NOIP1999 普及组第三题、提高组第三题


---

---
title: "[NOIP 2007 普及组] Hanoi 双塔问题"
layout: "post"
diff: 普及/提高-
pid: P1096
tag: ['数学', '高精度', '递推', '2007', '递归', 'NOIP 普及组']
---
# [NOIP 2007 普及组] Hanoi 双塔问题
## 题目描述

给定 A、B、C 三根足够长的细柱，在 A 柱上放有 $2n$ 个中间有孔的圆盘，共有 $n$ 个不同的尺寸，每个尺寸都有两个相同的圆盘，注意这两个圆盘是不加区分的（下图为 $n=3$ 的情形）。

![](https://cdn.luogu.com.cn/upload/image_hosting/mq2iklbv.png)

现要将这些圆盘移到 C 柱上，在移动过程中可放在 B 柱上暂存。要求：

1. 每次只能移动一个圆盘；
2. A、B、C 三根细柱上的圆盘都要保持上小下大的顺序。

任务：设 $A_n$ 为 $2n$ 个圆盘完成上述任务所需的最少移动次数，对于输入的 $n$，输出 $A_n$。


## 输入格式

一个正整数 $n$，表示在 A 柱上放有 $2n$ 个圆盘。

## 输出格式

一个正整数, 为完成上述任务所需的最少移动次数 $A_n$。

## 样例

### 样例输入 #1
```
1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
2
```
### 样例输出 #2
```
6
```
## 提示

**限制**

- 对于 $50\%$ 的数据，$1  \le  n  \le  25$；
- 对于 $100\%$ 的数据，$1  \le  n  \le  200$。

**提示**

设法建立 $A_n$ 与 $A_{n-1}$ 的递推关系式。



---

---
title: "[PA 2016] 运算 / Jedynki"
layout: "post"
diff: 普及/提高-
pid: P11605
tag: ['数学', '贪心', '2016', '递归', 'Special Judge', 'PA（波兰）']
---
# [PA 2016] 运算 / Jedynki
## 题目背景

译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R2 Jedynki [B] (JED)。$\texttt{1s,256M}$。

## 题目描述


给定正整数 $k$。构造一个只包含 $\texttt{1},\texttt{+},\texttt{*},\texttt{(},\texttt{)}$ 的**合法**表达式，满足：
- 不存在两个相邻的 $1$；
- $1$ 的数量最多为 $100$；
- 表达式运算结果为 $k$。

输出你构造的表达式，或者判断无解。

我们给定合法表达式的形式化定义：

- $\texttt{1}$ 是合法表达式。
- 若 $\texttt{a},\texttt{b}$ 是合法表达式，则 $\texttt{a+b},\texttt{a*b},\texttt{(a+b)},\texttt{(a*b)}$ 都是合法表达式。
## 输入格式


**本题单个测试点内有多组测试数据。**

第一行，一个正整数 $T$。接下来描述 $T$ 组测试数据：

每组测试数据只有一行一个正整数 $k$。

## 输出格式


输出 $T$ 行，每行一个字符串：
- 若无解，输出 $\texttt{NIE}$；
- 否则输出你构造的表达式。
## 样例

### 样例输入 #1
```
2
6
10
```
### 样例输出 #1
```
(1+1)*(1+1+1)
1+1+1+1+1+1+1+1+1+1
```
## 提示


- $1\le T\le 100$；
- $1\le k\le 10^9$。


---

---
title: "地毯填补问题"
layout: "post"
diff: 普及/提高-
pid: P1228
tag: ['递归', 'Special Judge', '分治']
---
# 地毯填补问题
## 题目描述

相传在一个古老的阿拉伯国家里，有一座宫殿。宫殿里有个四四方方的格子迷宫，国王选择驸马的方法非常特殊，也非常简单：公主就站在其中一个方格子上，只要谁能用地毯将除公主站立的地方外的所有地方盖上，美丽漂亮聪慧的公主就是他的人了。公主这一个方格不能用地毯盖住，毯子的形状有所规定，只能有四种选择（如图）：

![](https://cdn.luogu.com.cn/upload/image_hosting/cik5fiow.png)

并且每一方格只能用一层地毯，迷宫的大小为 $2^k\times 2^k$ 的方形。当然，也不能让公主无限制的在那儿等，对吧？由于你使用的是计算机，所以实现时间为 $1$ 秒。

## 输入格式

输入文件共 $2$ 行。

第一行一个整数 $k$，即给定被填补迷宫的大小为 $2^k\times 2^k$（$0\lt k\leq 10$）；
第二行两个整数 $x,y$，即给出公主所在方格的坐标（$x$ 为行坐标，$y$ 为列坐标），$x$ 和 $y$ 之间有一个空格隔开。

## 输出格式

将迷宫填补完整的方案：每一补（行）为 $x\ y\ c$（$x,y$ 为毯子拐角的行坐标和列坐标，$c$ 为使用毯子的形状，具体见上面的图 $1$，毯子形状分别用 $1,2,3,4$ 表示，$x,y,c$ 之间用一个空格隔开）。

## 样例

### 样例输入 #1
```
3                          
3 3   
```
### 样例输出 #1
```
5 5 1
2 2 4
1 1 4
1 4 3
4 1 2
4 4 1
2 7 3
1 5 4
1 8 3
3 6 3
4 8 1
7 2 2
5 1 4
6 3 2
8 1 2
8 4 1
7 7 1
6 6 1
5 8 3
8 5 2
8 8 1

```
## 提示

spj 报错代码解释：

1. $c$ 越界；
2. $x,y$ 越界；
3. $(x,y)$ 位置已被覆盖；
4. $(x,y)$ 位置从未被覆盖。

$\text{upd 2023.8.19}$：增加样例解释。

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/r9j8r452.png)



---

---
title: "编码"
layout: "post"
diff: 普及/提高-
pid: P1246
tag: ['递推', '递归', '线性递推']
---
# 编码
## 题目描述

编码工作常被运用于密文或压缩传输。这里我们用一种最简单的编码方式进行编码：把一些有规律的单词编成数字。

字母表中共有 $26$ 个字母 $\mathtt{a,b,c,\cdots,z}$，这些特殊的单词长度不超过 $6$ 且字母按升序排列。把所有这样的单词放在一起，按字典顺序排列，一个单词的编码就对应着它在字典中的位置。

例如：

- $\verb!a! \to 1$；
- $\verb!b! \to 2$；
- $\verb!z! \to 26$；
- $\verb!ab! \to 27$；
- $\verb!ac! \to 28$。

你的任务就是对于所给的单词，求出它的编码。

## 输入格式

仅一行，被编码的单词。

## 输出格式

仅一行，对应的编码。如果单词不在字母表中，输出 $0$。

## 样例

### 样例输入 #1
```
ab


```
### 样例输出 #1
```
27


```


---

---
title: "黑白棋子的移动"
layout: "post"
diff: 普及/提高-
pid: P1259
tag: ['递归', 'Special Judge']
---
# 黑白棋子的移动
## 题目描述

有 $2n$ 个棋子排成一行，开始为位置白子全部在左边，黑子全部在右边，如下图为 $n=5$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/dzfwand6.png)

移动棋子的规则是：每次必须同时移动相邻的两个棋子，颜色不限，可以左移也可以右移到空位上去，但不能调换两个棋子的左右位置。每次移动必须跳过若干个棋子（不能平移），要求最后能移成黑白相间的一行棋子。如 $n=5$ 时，成为：

![](https://cdn.luogu.com.cn/upload/image_hosting/yus9ph6d.png)

任务：编程打印出移动过程。
## 输入格式


一个整数 $n$。
## 输出格式

若干行，表示初始状态和每次移动的状态，用 $\verb!o!$ 表示白子，$\verb!*!$ 表示黑子，$\verb!-!$ 表示空行。

## 样例

### 样例输入 #1
```
7
```
### 样例输出 #1
```
ooooooo*******--
oooooo--******o*
oooooo******--o*
ooooo--*****o*o*
ooooo*****--o*o*
oooo--****o*o*o*
oooo****--o*o*o*
ooo--***o*o*o*o*
ooo*o**--*o*o*o*
o--*o**oo*o*o*o*
o*o*o*--o*o*o*o*
--o*o*o*o*o*o*o*

```
## 提示

 $ 4\leq n\leq 100$ 


---

---
title: "[NOIP 2011 普及组] 瑞士轮"
layout: "post"
diff: 普及/提高-
pid: P1309
tag: ['模拟', '2011', '递归', 'NOIP 普及组', '排序']
---
# [NOIP 2011 普及组] 瑞士轮
## 题目背景

在双人对决的竞技性比赛，如乒乓球、羽毛球、国际象棋中，最常见的赛制是淘汰赛和循环赛。前者的特点是比赛场数少，每场都紧张刺激，但偶然性较高。后者的特点是较为公平，偶然性较低，但比赛过程往往十分冗长。

本题中介绍的瑞士轮赛制，因最早使用于$1895$年在瑞士举办的国际象棋比赛而得名。它可以看作是淘汰赛与循环赛的折中，既保证了比赛的稳定性，又能使赛程不至于过长。

## 题目描述

$2 \times N$ 名编号为 $1\sim 2N$ 的选手共进行R 轮比赛。每轮比赛开始前，以及所有比赛结束后，都会按照总分从高到低对选手进行一次排名。选手的总分为第一轮开始前的初始分数加上已参加过的所有比赛的得分和。总分相同的，约定编号较小的选手排名靠前。

每轮比赛的对阵安排与该轮比赛开始前的排名有关：第$1$ 名和第$2$ 名、第 $3$ 名和第 $4$名、……、第$2K - 1 $名和第$ 2K$名、……  、第$2N - 1 $名和第$2N$名，各进行一场比赛。每场比赛胜者得$1 $分，负者得 $0 $分。也就是说除了首轮以外，其它轮比赛的安排均不能事先确定，而是要取决于选手在之前比赛中的表现。

现给定每个选手的初始分数及其实力值，试计算在R 轮比赛过后，排名第$ Q$ 的选手编号是多少。我们假设选手的实力值两两不同，且每场比赛中实力值较高的总能获胜。

## 输入格式

第一行是三个正整数$N,R ,Q$,每两个数之间用一个空格隔开，表示有 $2 \times N $名选手、$R$ 轮比赛，以及我们关心的名次 $Q$。

第二行是$2 \times N$ 个非负整数$s_1, s_2, …, s_{2N}$，每两个数之间用一个空格隔开，其中$ s_i $表示编号为$i$ 的选手的初始分数。 第三行是$2 \times N$ 个正整数$w_1 , w_2 , …, w_{2N}$，每两个数之间用一个空格隔开，其中 $w_i$ 表示编号为$i$ 的选手的实力值。

## 输出格式

一个整数，即$R$ 轮比赛结束后，排名第$ Q$ 的选手的编号。

## 样例

### 样例输入 #1
```
2 4 2 
7 6 6 7 
10 5 20 15 

```
### 样例输出 #1
```
1

```
## 提示

【样例解释】

 ![](https://cdn.luogu.com.cn/upload/pic/98.png) 

【数据范围】

对于$30\% $的数据，$1 ≤ N ≤ 100$；

对于$50\% $的数据，$1 ≤ N ≤ 10,000 $；

对于$100\%$的数据，$1 ≤ N ≤ 100,000,1 ≤ R ≤ 50,1 ≤ Q ≤ 2N,0 ≤ s_1, s_2, …, s_{2N}≤10^8,1 ≤w_1, w_2 , …, w_{2N}≤ 10^8$。

noip2011普及组第3题。



---

---
title: "[GCJ 2017 #1A] Alphabet Cake"
layout: "post"
diff: 普及/提高-
pid: P13162
tag: ['数学', '贪心', '2017', '递归', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2017 #1A] Alphabet Cake
## 题目描述

You are catering a party for some children, and you are serving them a cake in the shape of a grid with $R$ rows and $C$ columns. Your assistant has started to decorate the cake by writing every child's initial in icing on exactly one cell of the cake. Each cell contains at most one initial, and since no two children share the same initial, no initial appears more than once on the cake.

Each child wants a single rectangular (grid-aligned) piece of cake that has their initial and no other child's initial(s). Can you find a way to assign every blank cell of the cake to one child, such that this goal is accomplished? It is guaranteed that this is always possible. There is no need to split the cake evenly among the children, and one or more of them may even get a 1-by-1 piece; this will be a valuable life lesson about unfairness.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each begins with one line with two integers $R$ and $C$. Then, there are $R$ more lines of $C$ characters each, representing the cake. Each character is either an uppercase English letter (which means that your assistant has already added that letter to that cell) or ? (which means that that cell is blank).

## 输出格式

For each test case, output one line containing `Case #x:` and nothing else. Then output $R$ more lines of $C$ characters each. Your output grid must be identical to the input grid, but with every `?` replaced with an uppercase English letter, representing that that cell appears in the slice for the child who has that initial. You may not add letters that did not originally appear in the input. In your grid, for each letter, the region formed by all the cells containing that letter must be a single grid-aligned rectangle.
## 样例

### 样例输入 #1
```
3
3 3
G??
?C?
??J
3 4
CODE
????
?JAM
2 2
CA
KE
```
### 样例输出 #1
```
Case #1:
GGJ
CCJ
CCJ
Case #2:
CODE
COAE
JJAM
Case #3:
CA
KE
```
## 提示

**Sample Explanation**

The sample output displays one set of answers to the sample cases. Other answers may be possible.

**Limits**

- $1 \leq T \leq 100$.
- There is at least one letter in the input grid.
- No letter appears in more than one cell in the input grid.
- It is guaranteed that at least one answer exists for each test case.

**Small dataset (8 Pts, Test Set 1 - Visible)**

- $1 \leq R \leq 12$.
- $1 \leq C \leq 12$.
- $R \times C \leq 12$.

**Large dataset (13 Pts, Test Set 2 - Hidden)**

- $1 \leq R \leq 25$.
- $1 \leq C \leq 25$.


---

---
title: "logo语言"
layout: "post"
diff: 普及/提高-
pid: P1322
tag: ['字符串', '搜索', '递归']
---
# logo语言
## 题目描述

Logo 语言命令可以指挥海龟在屏幕中爬行。本问题只使用 Logo 语言的三个语句：前进 `FD`，倒退 `BK` 和重复 `REPEAT`，因此，海龟只在一条直线上来回爬行。输入一行 logo 的命令行，输出海龟在屏幕中离开原来位子的距离（假设屏幕很大，可以让海龟移开 $10^9$ 的距离）。

例如：

- 输入 `FD 100` ，输出：$100$。

- 输入 `FD 100 BK 150`， 输出：$50$。

- 输入 `REPEAT 5[FD 100 BK 50]`， 输出：$250$。

- 输入 `REPEAT 5[FD 50 REPEAT 10[FD 100]]`， 输出：$5250$。
## 输入格式

一行，一个字符串，符合上述规定的 logo 命令行。
## 输出格式

一个数据，海龟离开原来位子的距离。
## 样例

### 样例输入 #1
```
FD 100

```
### 样例输出 #1
```
100

```
## 提示

每个语句输入数据的绝对值不超过 $1000$。输出结果不会超过 $10^9$。



---

---
title: "[COCI 2012/2013 #4] DLAKAVAC"
layout: "post"
diff: 普及/提高-
pid: P13417
tag: ['数学', '递推', '2012', '递归', 'COCI（克罗地亚）']
---
# [COCI 2012/2013 #4] DLAKAVAC
## 题目描述

In the faraway city of Xanadu, a flu epidemic has broken out, caused by a strain known as hairy flu. There are $M$ people living in the city, each resident having a unique personal ID number from the range of $0$ to $M - 1$, inclusive. Infection with this strain lasts exactly one day, and a person can catch it multiple times per season (since it mutates too quickly for lasting immunity).

On the first day of the epidemic, the flu was brought from another faraway country by a group of residents nicknamed "init-patients", whose ID numbers are known. The flu's spread is based on them. Each following day, a resident with ID number $p$ will catch the flu iff there exists a resident with ID $a$ who was infected the previous day, as well as an init-patient with ID $b$, such that:

$$
(a \times b) \bmod M = p.
$$

The numbers $a$ and $b$ need not be distinct. For example, consider a case where there are $101$ people in the town, and the init-patients are $5$ and $50$. On the first day, the init-patients are infected by definition. On the second day, the residents infected are $25$, $48$ ($250 \mod 101$), and $76$ ($2500 \mod 101$). On the third day, one of the infected patients is $77$, since $(48 \times 50) \mod 101 = 77$.

Who will catch the flu on the $K$-th day?
## 输入格式

The first line of input contains three positive integers, $K$, $M$, and $N$ ($1 \leq K \leq 10^{18}$, $3 \leq M \leq 1500$, $N < M$).

The second line of input contains $N$ space-separated nonnegative integers, the personal ID numbers of residents who were infected on the first day (the init-patients). These numbers are unique, increasing, and do not exceed $M - 1$.

## 输出格式

The first and only line of output must contain the personal ID numbers of residents infected with flu on the $K$-th day, given space-separated and in increasing order.
## 样例

### 样例输入 #1
```
1 100 3
1 2 3 
```
### 样例输出 #1
```
1 2 3
```
### 样例输入 #2
```
2 100 3
1 2 3
```
### 样例输出 #2
```
1 2 3 4 6 9
```
### 样例输入 #3
```
10 101 2
5 50
```
### 样例输出 #3
```
36 44 57 65
```


---

---
title: "[GCJ 2008 AMER SemiFinal] Mixing Bowls"
layout: "post"
diff: 普及/提高-
pid: P13478
tag: ['贪心', '2008', '递归', 'Google Code Jam']
---
# [GCJ 2008 AMER SemiFinal] Mixing Bowls
## 题目描述

You are following a recipe to create your lunch.

The recipe is a mixture made by combining ingredients together in a bowl. Each ingredient will be either:

- Another mixture which you must make first in a separate bowl; or
- A basic ingredient you already have in your kitchen, which can be added directly.

To make a mixture, you need to have all its ingredients ready, take an empty bowl and mix the ingredients in it. It is not possible to make mixtures by adding ingredients to an already-existing mixture in a bowl.

For example, if you want to make CAKE (a mixture) out of CAKEMIX (a mixture) and lies (a basic ingredient), then you must first make CAKEMIX in its own bowl, then add the CAKEMIX and lies to a second bowl to make the CAKE.

Once you have used a mixture as an ingredient and emptied the bowl it was prepared in, you can re-use that bowl for another mixture. So the number of bowls you need to prepare the recipe will depend on the order in which you decide to make mixtures.

Determine the minimum number of bowls you will need.

## 输入格式

The first line will contain an integer $C$, the number of test cases in the input file.

For each test case, there will be:

- One line containing an integer $N$, the number of mixtures in the test case.
- $N$ lines, one for each mixture, containing:
    - One string giving the mixture name;
    - An integer $M$, the number of ingredients in this mixture;
    - $M$ strings, giving the names of each of the ingredients of this mixture.

The tokens on one line will be separated by single spaces.

The first mixture in a test case is the recipe you are making.

The names of mixtures are strings of between $1$ and $20$ UPPERCASE letters.

The names of basic ingredients are strings of between $1$ and $20$ lowercase letters.

Each mixture is used in exactly one other mixture, except for the recipe, which is not used in any other mixture. Each ingredient will appear at most once in the ingredient list for a mixture. No mixture will (directly or indirectly) require itself as an ingredient.
## 输出格式

For each test case, output one line containing "Case #$X$: $Y$" where $X$ is the number of the test case, starting from $1$, and $Y$ is the minimum number of mixing bowls required.
## 样例

### 样例输入 #1
```
2
3
SOUP 3 STOCK salt water
STOCK 2 chicken VEGETABLES
VEGETABLES 2 celery onions
5
MILKSHAKE 4 milk icecream FLAVOR FRUIT
FRUIT 2 banana berries
FLAVOR 2 SPICES CHOCOLATE
SPICES 2 nutmeg cinnamon
CHOCOLATE 2 cocoa syrup
```
### 样例输出 #1
```
Case #1: 2
Case #2: 3
```
## 提示

**Sample Explanation**

In the first case, to satisfy your craving for SOUP, you follow these steps:

1. Make VEGETABLES by mixing celery and onions in a bowl.
2. Make STOCK in a second bowl by mixing chicken and VEGETABLES from the first bowl. The first bowl becomes empty.
3. Make SOUP in the first bowl by mixing STOCK, salt and water.

In the second case, you have a choice of whether to make FLAVOR or FRUIT first before mixing them with milk and icecream to make MILKSHAKE.

If we make FRUIT first, we use four bowls:

1. Make FRUIT in a bowl by mixing banana and berries.
2. Make SPICES in a second bowl by mixing nutmeg and cinnamon, and CHOCOLATE in a third bowl by mixing cocoa and syrup. (In either order)
3. Make FLAVOR in a fourth bowl by mixing SPICES and CHOCOLATE.
4. Make MILKSHAKE in the second or third bowl by mixing FRUIT, FLAVOR, milk and icecream.

However if we make FRUIT after FLAVOR, we use three bowls:

1. Make SPICES in a bowl by mixing nutmeg and cinnamon, and CHOCOLATE in a second bowl by mixing cocoa and syrup. (In either order)
2. Make FLAVOR in a third bowl by mixing SPICES and CHOCOLATE.
3. Make FRUIT in the first bowl by mixing banana and berries.
4. Make MILKSHAKE in the second bowl by mixing FRUIT, FLAVOR, milk and icecream.

**Limits**

- $1 \leq C \leq 10$
- $2 \leq M \leq 10$

**Small dataset (5 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 10$

**Large dataset (9 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 1000$



---

---
title: "[SHOI2002] 滑雪"
layout: "post"
diff: 普及/提高-
pid: P1434
tag: ['动态规划 DP', '搜索', '2002', '各省省选', '递归', '上海', '记忆化搜索']
---
# [SHOI2002] 滑雪
## 题目描述

Michael 喜欢滑雪。这并不奇怪，因为滑雪的确很刺激。可是为了获得速度，滑的区域必须向下倾斜，而且当你滑到坡底，你不得不再次走上坡或者等待升降机来载你。Michael 想知道在一个区域中最长的滑坡。区域由一个二维数组给出。数组的每个数字代表点的高度。下面是一个例子：
```plain
1   2   3   4   5
16  17  18  19  6
15  24  25  20  7
14  23  22  21  8
13  12  11  10  9
```
一个人可以从某个点滑向上下左右相邻四个点之一，当且仅当高度会减小。在上面的例子中，一条可行的滑坡为 $24-17-16-1$（从 $24$ 开始，在 $1$ 结束）。当然    $25$－$24$－$23$－$\ldots$－$3$－$2$－$1$ 更长。事实上，这是最长的一条。
## 输入格式

输入的第一行为表示区域的二维数组的行数 $R$ 和列数 $C$。下面是 $R$ 行，每行有 $C$ 个数，代表高度(两个数字之间用 $1$ 个空格间隔)。
## 输出格式

输出区域中最长滑坡的长度。
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9

```
### 样例输出 #1
```
25
```
## 提示

对于 $100\%$ 的数据，$1\leq R,C\leq 100$。


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
title: "Moo"
layout: "post"
diff: 普及/提高-
pid: P1885
tag: ['模拟', '字符串', '递归', '分治']
---
# Moo
## 题目描述

奶牛 Bessie 最近在学习字符串操作，它用如下的规则逐一的构造出新的字符串：

$S(0) =$ `moo`

$S(1) = S(0) +$ `m` $+$ `ooo` $+ S(0) =$ `moo` $+$ `m` $+$ `ooo` $+$ `moo` $=$ `moomooomoo`

$S(2) = S(1) +$ `m` $+$ `oooo` $+ S(1) =$ `moomooomoo` $+$ `m` $+$ `oooo` $+$  `moomooomoo` $=$ `moomooomoomoooomoomooomoo`

$\dots$

Bessie 就这样产生字符串，直到最后产生的那个字符串长度不小于读入的整数 $N$ 才停止。

通过上面观察，可以发现第 $k$ 个字符串是由：第 $k-1$ 个字符串 $+$ `m` $+$  $(k+2$ 个 $o) +$ 第 $k-1$ 个字符串连接起来的。

现在的问题是：给出一个整数 $N (1 \leq N \leq 10^9)$，问第 $N$ 个字符是字母 `m` 还是 `o`？

## 输入格式

一个正整数 $N$。

## 输出格式

一个字符，`m` 或者 `o`。

## 样例

### 样例输入 #1
```
11
```
### 样例输出 #1
```
m
```
## 提示

样例解释：

由题目所知：字符串 $S(0)$ 是 `moo`, 现在要求第 $11$ 个字符，显然字符串 $S(0)$ 不够长；

同样 $S(1)$ 的长度是 $10$，也不够长；$S(2)$ 的长度是 $25$，够长了，$S(2)$ 的第 $11$ 个字符是 `m`，所以答案就输出 `m`。



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
title: "L 国的战斗之排兵布阵"
layout: "post"
diff: 普及/提高-
pid: P1911
tag: ['递归', '洛谷原创', '分治']
---
# L 国的战斗之排兵布阵
## 题目背景

L 国即将与 I 国发动战争！！
## 题目描述

L 国的指挥官想让他的每一个军营都呈现出国徽形——L 形（方向无所谓）。当然，他的指挥营除外（这叫做个性），他想不出该怎么排，就这样，这任务又变成了你的······
## 输入格式

一行三个数：$n$，$x$，$y$ 表示军营大小为  $2^n$，指挥营在 $(x,y)$ 的位置上。
## 输出格式

$2^n$ 行，每行 $2^n$ 个数，表示军营号（按先行后列顺序）指挥营用 $0$ 表示。
## 样例

### 样例输入 #1
```
4 1 3
```
### 样例输出 #1
```
1 1 0 2 3 3 4 4 5 5 6 6 7 7 8 8
1 9 2 2 3 10 10 4 5 11 11 6 7 12 12 8
13 9 9 14 15 15 10 16 17 11 18 18 19 19 12 20
13 13 14 14 21 15 16 16 17 17 18 22 22 19 20 20
23 23 24 21 21 25 26 26 27 27 28 28 22 29 30 30
23 31 24 24 25 25 32 26 27 33 33 28 29 29 34 30
35 31 31 36 37 32 32 38 39 39 33 40 41 34 34 42
35 35 36 36 37 37 38 38 43 39 40 40 41 41 42 42
44 44 45 45 46 46 47 43 43 48 49 49 50 50 51 51
44 52 52 45 46 53 47 47 48 48 54 49 50 55 55 51
56 52 57 57 58 53 53 59 60 54 54 61 62 62 55 63
56 56 57 64 58 58 59 59 60 60 61 61 65 62 63 63
66 66 67 64 64 68 69 69 70 70 71 65 65 72 73 73
66 74 67 67 68 68 75 69 70 76 71 71 72 72 77 73
78 74 74 79 80 75 75 81 82 76 76 83 84 77 77 85
78 78 79 79 80 80 81 81 82 82 83 83 84 84 85 85

```
## 提示

$1\le n\le10$，$1\le x,y\le2^n$。


---

---
title: "外星密码"
layout: "post"
diff: 普及/提高-
pid: P1928
tag: ['模拟', '字符串', '递归', '分治']
---
# 外星密码
## 题目描述

有了防护伞，并不能完全避免 2012 的灾难。地球防卫小队决定去求助外星种族的帮助。经过很长时间的努力，小队终于收到了外星生命的回信。但是外星人发过来的却是一串密码。只有解开密码，才能知道外星人给的准确回复。解开密码的第一道工序就是解压缩密码，外星人对于连续的若干个相同的子串 $\texttt{X}$ 会压缩为 $\texttt{[DX]}$ 的形式（$D$ 是一个整数且 $1\leq D\leq99$），比如说字符串 $\texttt{CBCBCBCB}$ 就压缩为 $\texttt{[4CB]}$ 或者$\texttt{[2[2CB]]}$，类似于后面这种压缩之后再压缩的称为二重压缩。如果是 $\texttt{[2[2[2CB]]]}$ 则是三重的。现在我们给你外星人发送的密码，请你对其进行解压缩。

## 输入格式

输入一行，一个字符串，表示外星人发送的密码。

## 输出格式

输出一行，一个字符串，表示解压缩后的结果。
## 样例

### 样例输入 #1
```
AC[3FUN]
```
### 样例输出 #1
```
ACFUNFUNFUN
```
## 提示

【数据范围】

对于 $50\%$ 的数据：解压后的字符串长度在 $1000$ 以内，最多只有三重压缩。

对于 $100\%$ 的数据：解压后的字符串长度在 $20000$ 以内，最多只有十重压缩。保证只包含数字、大写字母、`[` 和 `]`。



---

---
title: "[NOIP 2013 提高组] 积木大赛"
layout: "post"
diff: 普及/提高-
pid: P1969
tag: ['模拟', '贪心', '2013', '递归', 'NOIP 提高组']
---
# [NOIP 2013 提高组] 积木大赛
## 题目背景

NOIP2013 提高组 D2T1
## 题目描述

春春幼儿园举办了一年一度的“积木大赛”。今年比赛的内容是搭建一座宽度为 $n$ 的大厦，大厦可以看成由 $n$ 块宽度为 $1$ 的积木组成，第 $i$ 块积木的最终高度需要是 $h_i$。

在搭建开始之前，没有任何积木（可以看成 $n$ 块高度为 $0$ 的积木）。接下来每次操作，小朋友们可以选择一段连续区间 $[l, r]$，然后将第 $L$ 块到第 $R$ 块之间（含第 $L$ 块和第 $R$ 块）所有积木的高度分别增加 $1$。

小 M 是个聪明的小朋友，她很快想出了建造大厦的最佳策略，使得建造所需的操作次数最少。但她不是一个勤于动手的孩子，所以想请你帮忙实现这个策略，并求出最少的操作次数。

## 输入格式

包含两行，第一行包含一个整数 $n$，表示大厦的宽度。

第二行包含 $n$ 个整数，第 $i$ 个整数为 $h_i$。

## 输出格式

建造所需的最少操作数。

## 样例

### 样例输入 #1
```
5
2 3 4 1 2
```
### 样例输出 #1
```
5
```
## 提示

**样例解释**

其中一种可行的最佳方案，依次选择：$[1,5]$，$ [1,3]$，$[2,3]$，$[3,3]$，$ [5,5]$。

**数据范围**

- 对于 $30\%$ 的数据，有 $1 \leq n \leq 10$；
- 对于 $70\%$ 的数据，有 $1 \leq n \leq 1000$；
- 对于 $100\%$ 的数据，有 $1 \leq n \leq 100000$，$0 \leq h_i \leq 10000$。



---

---
title: "打开所有的灯"
layout: "post"
diff: 普及/提高-
pid: P2040
tag: ['模拟', '搜索', '递归', '枚举', '剪枝']
---
# 打开所有的灯
## 题目背景

pmshz在玩一个益(ruo)智(zhi)的小游戏，目的是打开九盏灯所有的灯，这样的游戏难倒了pmshz。。。

## 题目描述

这个灯很奇(fan)怪(ren)，点一下就会将这个灯和其周围四盏灯的开关状态全部改变。现在你的任务就是就是告诉pmshz要全部打开这些灯。



例如
```
0  1  1
1  0  0
1  0  1
```

点一下最中间的灯【2,2】就变成了
```
0  0  1
0  1  1
1  1  1
```

再点一下左上角的灯【1,1】就变成了

```
1  1  1
1  1  1
1  1  1
```

达成目标。最少需要2步。

输出2即可。

## 输入格式

九个数字，3\*3的格式输入，每两个数字中间只有一个空格，表示灯初始的开关状态。（0表示关，1表示开）

## 输出格式

1个整数，表示最少打开所有灯所需要的步数。

## 样例

### 样例输入 #1
```
0 1 1
1 0 0
1 0 1
```
### 样例输出 #1
```
2
```
## 提示

这个题水不水，就看你怎么考虑了。。。。



---

---
title: "朋友"
layout: "post"
diff: 普及/提高-
pid: P2078
tag: ['并查集', '递归']
---
# 朋友
## 题目背景

小明在 A 公司工作，小红在 B 公司工作。
## 题目描述

这两个公司的员工有一个特点：一个公司的员工都是同性。

A 公司有 $N$ 名员工，其中有 $P$ 对朋友关系。B 公司有 $M$ 名员工，其中有 $Q$ 对朋友关系。朋友的朋友一定还是朋友。

每对朋友关系用两个整数 $(X_i,Y_i)$ 组成，表示朋友的编号分别为 $X_i,Y_i$。男人的编号是正数，女人的编号是负数。小明的编号是 $1$，小红的编号是 $-1$。

大家都知道，小明和小红是朋友，那么，请你写一个程序求出两公司之间，通过小明和小红认识的人最多一共能配成多少对情侣（包括他们自己）。
## 输入格式

输入的第一行，包含 $4$ 个空格隔开的正整数 $N,M,P,Q$。

之后 $P$ 行，每行两个正整数 $X_i,Y_i$。

之后 $Q$ 行，每行两个负整数 $X_i,Y_i$。
## 输出格式

输出一行一个正整数，表示通过小明和小红认识的人最多一共能配成多少对情侣（包括他们自己）。
## 样例

### 样例输入 #1
```
4 3 4 2
1 1
1 2
2 3
1 3
-1 -2
-3 -3

```
### 样例输出 #1
```
2
```
## 提示

对于 $30 \%$ 的数据，$N,M \le 100$，$P,Q \le 200$；

对于 $80 \%$ 的数据，$N,M \le 4 \times 10^3$，$P,Q \le 10^4$；

对于 $100 \%$ 的数据，$N,M \le 10^4$，$P,Q \le 2 \times 10^4$。


---

---
title: "Hz吐泡泡"
layout: "post"
diff: 普及/提高-
pid: P2171
tag: ['树形数据结构', '递归']
---
# Hz吐泡泡
## 题目背景

Hz大大是一种可爱的动物（神）。他很喜欢吐泡泡（更喜欢写作业）。

## 题目描述

这天，Hz大大心血来潮，吐了n个不同的泡泡玩（保证没有重复的泡泡）。因为他还要写作业，所以他请你帮他把这些泡泡排序成树（左子树<=根<右子树）。输出它的后序遍历。

## 输入格式

共2行。

第一行，1个整数n。(1<=n<=300000)

第二行，n个数，代表泡泡的大小。

## 输出格式

共2行。

第一行，输出树的深度。

第二行，输出数的后序遍历。

详见样例输出。

## 样例

### 样例输入 #1
```
8
1 4 3 9 10 35 2 7

```
### 样例输出 #1
```
deep=5
2
3
7
35
10
9
4
1

```
## 提示

水题一道。



---

---
title: "木材加工"
layout: "post"
diff: 普及/提高-
pid: P2440
tag: ['贪心', '线性数据结构', '二分', '递归']
---
# 木材加工
## 题目背景

要保护环境

## 题目描述

木材厂有 $n$ 根原木，现在想把这些木头切割成 $k$ 段长度**均**为 $l$ 的小段木头（木头有可能有剩余）。

当然，我们希望得到的小段木头越长越好，请求出 $l$ 的最大值。

木头长度的单位是 $\text{cm}$，原木的长度都是正整数，我们要求切割得到的小段木头的长度也是正整数。

例如有两根原木长度分别为 $11$ 和 $21$，要求切割成等长的 $6$ 段，很明显能切割出来的小段木头长度最长为 $5$。
## 输入格式


第一行是两个正整数 $n,k$，分别表示原木的数量，需要得到的小段的数量。

接下来 $n$ 行，每行一个正整数 $L_i$，表示一根原木的长度。
## 输出格式

仅一行，即 $l$ 的最大值。

如果连 $\text{1cm}$ 长的小段都切不出来，输出 `0`。
## 样例

### 样例输入 #1
```
3 7
232
124
456
```
### 样例输出 #1
```
114
```
## 提示


#### 数据规模与约定

对于 $100\%$ 的数据，有 $1\le n\le 10^5$，$1\le k\le 10^8$，$1\le L_i\le 10^8(i\in[1,n])$。


---

---
title: "[TJOI2007] 跳棋"
layout: "post"
diff: 普及/提高-
pid: P3848
tag: ['搜索', '2007', '各省省选', '递归', '深度优先搜索 DFS', '天津']
---
# [TJOI2007] 跳棋
## 题目背景

在一个n×n的棋盘上，布满了0和1，如图（a）所示（n=7），为叙述方便，将0用字母表示，如图（b）。

![](https://cdn.luogu.com.cn/upload/pic/6077.png)

## 题目描述

跳棋规则：

（1）从某个0格出发，可以向上，下，左，右4个方向连续越过若干个（至少1个）

1格而跳入下一个0格。如图（b）中从A出发，可跳到B，或者到E，但不能直接到K。在跳到B之后还可以继续跳到F;在跳到E之后可继续跳到F或K。直到不能再跳为止。

（2）每个0格只能到达一次，给出的起始点不能再到达，也不能越过。

跳过的距离为跳过1格个数加1，如从A到B，跳过距离为3，从B到F，跳过距离为2。

问   题： 当棋盘和起始点给出之后，问最远能跳的距离是多少？

如上图（b）中，从A出发，可跳过的路线不止一条，其中一条为：

A － B － F － L － K － E  （可能不唯一）

3    2    3    3     3

它的距离为14。

## 输入格式

第一行三个整数  n（1≤n≤100），x，y（起点坐标，上图（b）中A处坐标为1，3）

接下来n行，每行n个数（0或1），数与数之间用一个空格分隔。

## 输出格式

一个整数，即最大可跳距离（若不能跳，输出0）。

## 样例

### 样例输入 #1
```
4  3  2
1  0  1  0 
1  1  1  1
0  0  1  0
1  1  0  1
```
### 样例输出 #1
```
6
```
## 提示

$\text{upd 2022.7.27}$：新增加一组 Hack 数据。


---

---
title: "数列之异或"
layout: "post"
diff: 普及/提高-
pid: P3908
tag: ['数学', '递归', '进制']
---
# 数列之异或
## 题目描述

求$1 \bigoplus 2 \bigoplus\cdots\bigoplus N$ 的值。

$A \bigoplus B$ 即$A$ , $B$ 按位异或。

## 输入格式

1 个整数$N$。

## 输出格式

1 个整数，表示所求的值。

## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
0
```
## 提示

• 对于50% 的数据，$1 \le N \le 10^6$；

• 对于100% 的数据，$1 \le N \le 10^{18}$。



---

---
title: "赦免战俘"
layout: "post"
diff: 普及/提高-
pid: P5461
tag: ['模拟', '递归', '洛谷月赛']
---
# 赦免战俘
## 题目背景

借助反作弊系统，一些在月赛有抄袭作弊行为的选手被抓出来了！
## 题目描述

现有 $2^n\times 2^n (n\le10)$ 名作弊者站成一个正方形方阵等候 kkksc03 的发落。kkksc03 决定赦免一些作弊者。他将正方形矩阵均分为 4 个更小的正方形矩阵，每个更小的矩阵的边长是原矩阵的一半。其中左上角那一个矩阵的所有作弊者都将得到赦免，剩下 3 个小矩阵中，每一个矩阵继续分为 4 个更小的矩阵，然后通过同样的方式赦免作弊者……直到矩阵无法再分下去为止。所有没有被赦免的作弊者都将被处以棕名处罚。

给出 $n$，请输出每名作弊者的命运，其中 0 代表被赦免，1 代表不被赦免。
## 输入格式

一个整数 $n$。
## 输出格式

$2^n \times 2^n$ 的 01 矩阵，代表每个人是否被赦免。数字之间有一个空格。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
0 0 0 0 0 0 0 1
0 0 0 0 0 0 1 1
0 0 0 0 0 1 0 1
0 0 0 0 1 1 1 1
0 0 0 1 0 0 0 1
0 0 1 1 0 0 1 1
0 1 0 1 0 1 0 1
1 1 1 1 1 1 1 1
```


---

---
title: "[USACO22OPEN] Alchemy B"
layout: "post"
diff: 普及/提高-
pid: P8268
tag: ['二分', 'USACO', '递归', '2022']
---
# [USACO22OPEN] Alchemy B
## 题目描述

总是热衷于培养新的爱好的奶牛 Bessie 正在学习如何转化金属。对于 $1 \le i \le N \le 100$，她有 $a_i$（$0 \le a_i \le 10^4$）单位的金属 $i$。此外，她知道 $K$（$1\le K< N$）个配方，她可以融合若干种金属各一单位，制造一单位编号大于所有被融合金属的金属。另外保证，对于每种金属，Bessie 最多知道一种制造该金属的配方。

计算经过一系列转化后，Bessie 可能拥有的金属 $N$ 的最大单位数。
## 输入格式

输入的第一行包含 $N$。

第二行包含 $N$ 个整数 $a_i$。

第三行包含 $K$。

以下 $K$ 行每行包含两个整数 $L$ 和 $M$（$M\ge 1$），随后是 $M$ 个整数。后 $M$ 个整数表示配方中用于制造一单位金属 $L$ 所需要被融合的金属。输入保证 $L$ 大于这 $M$ 个数。
## 输出格式

输出在应用一系列零次或多次转化后，Bessie 可能拥有的金属 $N$ 的最大单位数。
## 样例

### 样例输入 #1
```
5
2 0 0 1 0
3
5 2 3 4
2 1 1
3 1 2
```
### 样例输出 #1
```
1
```
## 提示

【样例解释】

在这个例子中，以下是一种最优的转化方式：

- 将一单位金属 1 转化为金属 2。
- 将一单位金属 2 转化为金属 3。
- 将一单位金属 3 和金属 4 转化为金属 5。

现在 Bessie 还有一单位金属 1 和一单位金属 5。她无法再制造更多的金属 5。

【测试点性质】

- 测试点 2 中，对于 $1\le i< N$，一单位金属 $i$ 可以被转化为一单位金属 $i+1$；

- 测试点 3-4 中，每个配方均将一单位的一种金属转化为另一种金属；

- 测试点 5-11 没有额外限制。


---

