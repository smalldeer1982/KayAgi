---
title: "【模板】栈"
layout: "post"
diff: 普及-
pid: B3614
tag: ['O2优化', '栈']
---
# 【模板】栈
## 题目描述

请你实现一个栈（stack），支持如下操作：
- `push(x)`：向栈中加入一个数 $x$。
- `pop()`：将栈顶弹出。如果此时栈为空则不进行弹出操作，输出 `Empty`。
- `query()`：输出栈顶元素，如果此时栈为空则输出 `Anguei!`。
- `size()`：输出此时栈内元素个数。
## 输入格式

**本题单测试点内有多组数据**。  
输入第一行是一个整数 $T$，表示数据组数。对于每组数据，格式如下：  
每组数据第一行是一个整数，表示操作的次数 $n$。  
接下来 $n$ 行，每行首先由一个字符串，为 `push`，`pop`，`query` 和 `size` 之一。若为 `push`，则其后有一个整数 $x$，表示要被加入的数，$x$ 和字符串之间用空格隔开；若不是 `push`，则本行没有其它内容。
## 输出格式

对于每组数据，按照「题目描述」中的要求依次输出。每次输出占一行。
## 样例

### 样例输入 #1
```
2
5
push 2
query
size
pop
query
3
pop
query
size
```
### 样例输出 #1
```
2
1
Anguei!
Empty
Anguei!
0
```
## 提示

### 样例 1 解释
对于第二组数据，始终为空，所以 `pop` 和 `query` 均需要输出对应字符串。栈的 size 为 0。

### 数据规模与约定

对于全部的测试点，保证 $1 \leq T, n\leq 10^6$，且单个测试点内的 $n$ 之和不超过 $10^6$，即 $\sum n \leq 10^6$。保证 $0 \leq x \lt 2^{64}$。

### 提示
- 请注意大量数据读入对程序效率造成的影响。
- 因为一开始数据造错了，请注意输出的 `Empty` 不含叹号，`Anguei!` 含有叹号。


---

---
title: "[蓝桥杯青少年组国赛 2023] 简单算术题"
layout: "post"
diff: 普及-
pid: B4278
tag: ['字符串', '2023', '栈', '蓝桥杯青少年组']
---
# [蓝桥杯青少年组国赛 2023] 简单算术题
## 题目描述

给定一道没有括号的四则混合运算算术题（可能包含多余的空格），请编程计算出结果。运算规则如下：  
1. 既有乘、除法又有加、减法的，要先算乘除法，再算加减法；  
2. 同级运算时，要从左往右按顺序计算；  
3. 所有除法运算的结果都只保留整数部分（直接舍弃小数部分）。

**例如**：当算术题为 $\tt{2 + 3*4 - 10/6 + 1/2*4}$ 时：  
- 优先计算乘除法，有 $\tt{3*4=12}$，$\tt{10/6=1}$，$\tt{1/2*4=0}$；  
- 然后计算加减法，$\tt{2+3*4-10/6+1/2*4} = \tt{2+12-1+0} = \tt{13}$，故输出 $13$。  
## 输入格式

输入一个字符串，表示算术题：  
- 字符串长度 $5 \leq$ 长度 $\leq 100000$；  
- 字符串中只包含数字字符以及 $\tt{+}$，$\tt{-}$，$\tt{*}$，$\tt{/}$ 运算符；  
- 不含括号，可能包含空格；  
- 算式中的运算数范围：$1 \leq$ 运算数 $\leq 200$。  
## 输出格式

输出一个整数，表示算术题的计算结果。题目数据保证算式的每一步运算的结果都在 $-2 \times 10^9 \sim 2 \times 10^9$ 之间。
## 样例

### 样例输入 #1
```
2+3*4-10/6+1/2*4
```
### 样例输出 #1
```
13
```


---

---
title: "[NOIP 2003 普及组] 栈"
layout: "post"
diff: 普及-
pid: P1044
tag: ['动态规划 DP', '数学', '递推', '2003', 'NOIP 普及组', 'Catalan 数', '栈']
---
# [NOIP 2003 普及组] 栈
## 题目背景

栈是计算机中经典的数据结构，简单的说，栈就是限制在一端进行插入删除操作的线性表。

栈有两种最重要的操作，即 pop（从栈顶弹出一个元素）和 push（将一个元素进栈）。

栈的重要性不言自明，任何一门数据结构的课程都会介绍栈。宁宁同学在复习栈的基本概念时，想到了一个书上没有讲过的问题，而他自己无法给出答案，所以需要你的帮忙。
## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/5qxy9fz2.png)

宁宁考虑的是这样一个问题：一个操作数序列，$1,2,\ldots ,n$（图示为 1 到 3 的情况），栈 A 的深度大于 $n$。

现在可以进行两种操作，

1. 将一个数，从操作数序列的头端移到栈的头端（对应数据结构栈的 push 操作）
2. 将一个数，从栈的头端移到输出序列的尾端（对应数据结构栈的 pop 操作）

使用这两种操作，由一个操作数序列就可以得到一系列的输出序列，下图所示为由 `1 2 3` 生成序列 `2 3 1` 的过程。

![](https://cdn.luogu.com.cn/upload/image_hosting/8uwv2pa2.png)

（原始状态如上图所示）

你的程序将对给定的 $n$，计算并输出由操作数序列 $1,2,\ldots,n$ 经过操作可能得到的输出序列的总数。
## 输入格式

输入文件只含一个整数 $n$（$1 \leq n \leq 18$）。

## 输出格式

输出文件只有一行，即可能输出序列的总数目。
## 样例

### 样例输入 #1
```
3

```
### 样例输出 #1
```
5

```
## 提示

**【题目来源】**

NOIP 2003 普及组第三题


---

---
title: "括号画家"
layout: "post"
diff: 普及-
pid: P10472
tag: ['O2优化', '栈']
---
# 括号画家
## 题目描述

Candela 是一名漫画家，她有一个奇特的爱好，就是在纸上画括号。这一天，刚刚起床的 Candela 画了一排括号序列，其中包含小括号 `()`、中括号 `[]` 和大括号 `{}`，总长度为 $N$。这排随意绘制的括号序列显得杂乱无章，于是 Candela 定义了什么样的括号序列是美观的：

1. 空的括号序列是美观的；
2. 若括号序列 A 是美观的，则括号序列 `(A)`、`[A]`、`{A}` 也是美观的；
3. 若括号序列 A、B 都是美观的，则括号序列 `AB` 也是美观的；

例如 `[(){}]()` 是美观的括号序列，而 `)({)[}](` 则不是。

现在 Candela 想在她绘制的括号序列中，找出其中连续的一段，满足这段子序列是美观的，并且长度尽量大。你能帮帮她吗？
## 输入格式

第一行一个长度为 $N$ 的括号序列。


## 输出格式

一个整数，表示最长的美观的连续子序列的长度。
## 样例

### 样例输入 #1
```
({({(({()}})}{())})})[){{{([)()((()]]}])[{)]}{[}{)
```
### 样例输出 #1
```
4
```
## 提示

数据保证，各个测试点的 $N$ 的大小分别为：$5,10,50,100,100,1000,1000,10000,10000,10000$。


---

---
title: "日志分析"
layout: "post"
diff: 普及-
pid: P1165
tag: ['模拟', '线性数据结构', '栈']
---
# 日志分析
## 题目描述

M 海运公司最近要对旗下仓库的货物进出情况进行统计。目前他们所拥有的唯一记录就是一个记录集装箱进出情况的日志。该日志记录了两类操作：第一类操作为集装箱入库操作，以及该次入库的集装箱重量；第二类操作为集装箱的出库操作。这些记录都严格按时间顺序排列。集装箱入库和出库的规则为先进后出，即每次出库操作出库的集装箱为当前在仓库里所有集装箱中最晚入库的集装箱。

出于分析目的，分析人员在日志中随机插入了若干第三类操作――查询操作。分析日志时，每遇到一次查询操作，都要报告出当前仓库中最大集装箱的重量。

## 输入格式

包含 $N+1$ 行：

第一行为一个正整数 $N$，对应于日志内所含操作的总数。

接下来的 $N$ 行，分别属于以下三种格式之一：

- 格式 1：`0 X`，表示一次集装箱入库操作，正整数 $X$ 表示该次入库的集装箱的重量。
- 格式 2：`1`，表示一次集装箱出库操作，（就当时而言）最后入库的集装箱出库。
- 格式 3：`2`，表示一次查询操作，要求分析程序输出当前仓库内最大集装箱的重量。

当仓库为空时你应该忽略出库操作，当仓库为空查询时你应该输出 $0$。

## 输出格式

输出行数等于日志中查询操作的次数。每行为一个整数，表示查询结果。

## 样例

### 样例输入 #1
```
13
0 1
0 2
2
0 4
0 2
2
1
2
1
1
2
1
2

```
### 样例输出 #1
```
2
4
4
1
0

```
## 提示

### 数据范围及约定

- 对于 $20\%$ 的数据，有 $N \le 10$；
- 对于 $40\%$ 的数据，有 $N \le 1000$；
- 对于 $100\%$ 的数据，有 $1 \le N \le 200000$，$1 \le X \le 10^8$。



---

---
title: "[COCI 2012/2013 #4] ESEJ"
layout: "post"
diff: 普及-
pid: P13414
tag: ['2012', '栈', 'COCI（克罗地亚）']
---
# [COCI 2012/2013 #4] ESEJ
## 题目描述

Mirko's latest homework assignment is writing an essay. However, he finds writing essays so boring that, after working for two hours, he realized that all he has written are $N$ long words consisting entirely of letters $A$ and $B$. Having accepted that he will never finish the essay in time, poor Mirko has decided to at least have some fun with it by counting nice words.

Mirko is connecting pairs of identical letters ($A$ with $A$, $B$ with $B$) by drawing arches above the word. A given word is nice if each letter can be connected to exactly one other letter in such a way that no two arches intersect. Help Mirko count how many words are nice.

## 输入格式

The first line of input contains the positive integer $N$ ($1 \leq N \leq 100$), the number of words written down by Mirko.

Each of the following $N$ lines contains a single word consisting of letters $A$ and $B$, with length between $2$ and $100\,000$, inclusive. The sum of lengths of all words doesn't exceed $1\,000\,000$.

## 输出格式

The first and only line of output must contain the number of nice words.
## 样例

### 样例输入 #1
```
3
ABAB
AABB
ABBA
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3
AAA
AA
AB
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
1
ABBABB
```
### 样例输出 #3
```
1
```


---

---
title: "后缀表达式"
layout: "post"
diff: 普及-
pid: P1449
tag: ['模拟', '字符串', '线性数据结构', '栈']
---
# 后缀表达式
## 题目描述

所谓后缀表达式是指这样的一个表达式：式中不再引用括号，运算符号放在两个运算对象之后，所有计算按运算符号出现的顺序，严格地由左而右新进行（不用考虑运算符的优先级）。

本题中运算符仅包含 $\texttt{+-*/}$。保证对于 $\texttt{/}$ 运算除数不为 0。特别地，其中 $\texttt{/}$ 运算的结果需要**向 0 取整**（即与 C++ `/` 运算的规则一致）。

如：$\texttt{3*(5-2)+7}$ 对应的后缀表达式为：$\texttt{3.5.2.-*7.+@}$。在该式中，`@` 为表达式的结束符号。`.` 为操作数的结束符号。

## 输入格式

输入一行一个字符串 $s$，表示后缀表达式。

## 输出格式

输出一个整数，表示表达式的值。
## 样例

### 样例输入 #1
```
3.5.2.-*7.+@
```
### 样例输出 #1
```
16
```
### 样例输入 #2
```
10.28.30./*7.-@
```
### 样例输出 #2
```
-7
```
## 提示

数据保证，$1 \leq |s| \leq 50$，答案和计算过程中的每一个值的绝对值不超过 $10^9$。


---

---
title: "鸡蛋饼"
layout: "post"
diff: 普及-
pid: P1976
tag: ['洛谷原创', 'Catalan 数', '栈']
---
# 鸡蛋饼
## 题目背景

Czyzoiers 都想知道小 x 为什么对鸡蛋饼情有独钟。经过一番逼问，小 x 道出了实情：因为他喜欢圆。

## 题目描述

最近小 x 又发现了一个关于圆的有趣的问题：在圆上有 $2N$ 个不同的点，小 x 想用 N 条线段把这些点连接起来（每个点只能连一条线段）， 使所有的线段都不相交，他想知道这样的连接方案有多少种？

## 输入格式

有且仅有一个正整数 N 。 （$N \le 2999$）

## 输出格式

要求的方案数（结果 $\bmod 100000007$）。

## 样例

### 样例输入 #1
```
24
```
### 样例输出 #1
```
4057031
```


---

---
title: "[NOIP 2013 普及组] 表达式求值"
layout: "post"
diff: 普及-
pid: P1981
tag: ['模拟', '字符串', '2013', 'NOIP 普及组', '栈']
---
# [NOIP 2013 普及组] 表达式求值
## 题目背景

NOIP2013 普及组 T2
## 题目描述

给定一个只包含加法和乘法的算术表达式，请你编程计算表达式的值。

## 输入格式

一行，为需要你计算的表达式，表达式中只包含数字、加法运算符 `+` 和乘法运算符 `*`，且没有括号，所有参与运算的数字均为 $0$ 到   $2^{31}-1$ 之间的整数。  

输入数据保证这一行只有 `0123456789+*` 这 $12$ 种字符。

## 输出格式

一个整数，表示这个表达式的值。  

注意：当答案长度多于 $4$ 位时，请只输出最后 $ 4$ 位，前导 $ 0$ 不输出。

## 样例

### 样例输入 #1
```
1+1*3+4

```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
1+1234567890*1
```
### 样例输出 #2
```
7891
```
### 样例输入 #3
```
1+1000000003*1
```
### 样例输出 #3
```
4
```
## 提示

对于 $30\%$ 的数据，$0≤$ 表达式中加法运算符和乘法运算符的总数 $≤100$。

对于 $80\%$ 的数据，$0≤$ 表达式中加法运算符和乘法运算符的总数 $≤1000$。

对于 $100\%$ 的数据，$0≤$ 表达式中加法运算符和乘法运算符的总数 $≤100000$。



---

---
title: "[USACO12NOV] Clumsy Cows S"
layout: "post"
diff: 普及-
pid: P3056
tag: ['模拟', '贪心', '2012', 'USACO', '前缀和', '栈']
---
# [USACO12NOV] Clumsy Cows S
## 题目描述

Bessie the cow is trying to type a balanced string of parentheses into her new laptop, but she is sufficiently clumsy (due to her large hooves) that she keeps mis-typing characters.  Please help her by computing the minimum number of characters in the string that one must reverse (e.g., changing a left parenthesis to a right parenthesis, or vice versa) so that the string would become balanced.

There are several ways to define what it means for a string of parentheses to be "balanced".  Perhaps the simplest definition is that there must be the same total number of ('s and )'s, and for any prefix of the string, there must be at least as many ('s as )'s.  For example, the following strings are all balanced:

() 
(()) 
()(()()) 

while these are not:

)( 
())( 
((()))) 

给出一个偶数长度的括号序列，问最少修改多少个括号可以使其平衡。

## 输入格式

\* Line 1: A string of parentheses of even length at most 100,000 characters.

## 输出格式

\* Line 1: A single integer giving the minimum number of parentheses that must be toggled to convert the string into a balanced string.

## 样例

### 样例输入 #1
```
())( 

```
### 样例输出 #1
```
2 

```
## 提示

The last parenthesis must be toggled, and so must one of the two middle right parentheses.




---

---
title: "[USACO17JAN] Secret Cow Code S"
layout: "post"
diff: 普及-
pid: P3612
tag: ['字符串', '2017', 'USACO', '递归', '分治', '栈']
---
# [USACO17JAN] Secret Cow Code S
## 题目描述

The cows are experimenting with secret codes, and have devised a method for creating an infinite-length string to be used as part of one of their codes.

Given a string $s$, let $F(s)$ be $s$ followed by $s$ "rotated" one character to the right (in a right rotation, the last character of $s$ rotates around and becomes the new first character). Given an initial string $s$, the cows build their infinite-length code string by repeatedly applying $F$; each step therefore doubles the length of the current string.


Given the initial string and an index $N$, please help the cows compute the character at the $N$th position within the infinite code string.


## 输入格式

The input consists of a single line containing a string followed by $N$. The string consists of at most 30 uppercase characters, and $N \leq 10^{18}$.

Note that $N$ may be too large to fit into a standard 32-bit integer, so you may want to use a 64-bit integer type (e.g., a "long long" in C/C++).


## 输出格式

Please output the $N$th character of the infinite code built from the initial string. The first character is $N=1$.



## 样例

### 样例输入 #1
```
COW 8
```
### 样例输出 #1
```
C
```
## 提示

In this example, the initial string COW expands as follows:


COW -> COWWCO -> COWWCOOCOWWC

12345678



## 题目翻译

### 题目描述

奶牛们正在实验秘密代码，并设计了一种方法用于生成无限长度的字符串，作为他们代码的一部分。

给定一个字符串 $s$，令 $F(s)$ 为 $s$ 后接 $s$ 向右“旋转”一个字符的结果（在右旋转中，$s$ 的最后一个字符旋转并成为新的第一个字符）。给定初始字符串 $s$，奶牛们通过重复应用 $F$ 来构建他们的无限长度代码字符串；因此每一步都会使当前字符串的长度翻倍。

给定初始字符串和一个索引 $N$，请帮助奶牛计算无限代码字符串中第 $N$ 个位置的字符。

### 输入格式

输入由一行组成，包含一个字符串和 $N$。字符串最多由 30 个大写字母组成，且 $N \leq 10^{18}$。

请注意，$N$ 可能太大，无法放入标准的 32 位整数中，因此你可能需要使用 64 位整数类型（例如，C/C++ 中的 "long long"）。

### 输出格式

请输出从初始字符串构建的无限代码字符串的第 $N$ 个字符。第一个字符的位置为 $N=1$。

### 提示

在这个例子中，初始字符串 COW 按以下方式扩展：

COW -> COWWCO -> COWWCOOCOWWC


---

