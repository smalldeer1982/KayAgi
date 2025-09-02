---
title: "[蓝桥杯青少年组省赛 2023] 最大的矩形纸片"
layout: "post"
diff: 普及+/提高
pid: B4273
tag: ['2023', '单调栈', '蓝桥杯青少年组']
---
# [蓝桥杯青少年组省赛 2023] 最大的矩形纸片
## 题目描述

一张半边参差不齐的网格纸（网格边长均为 $1$），有一边是完整没有破损的。现要从中剪出一片面积最大的矩形纸片。

给定网格纸中完整边的长度 $N$（$1 \leq N \leq 1\,000\,000$），以及网格中每一列残存部分的高度（$1 \leq$ 高度 $\leq 10\,000$），输出能够剪出的最大矩形纸片面积。
## 输入格式

第一行输入一个正整数 $N$（$1 \leq N \leq 1\,000\,000$），表示纸片完整边的长度。  

第二行输入 $N$ 个正整数（$1 \leq$ 正整数 $\leq 10\,000$），表示每列格子残存部分的高度，两个正整数之间用一个空格隔开。  
## 输出格式

输出一个正整数，表示能够剪出的最大矩形纸片面积。
## 样例

### 样例输入 #1
```
6
3 2 1 4 5 2
```
### 样例输出 #1
```
8
```


---

---
title: "[USACO24OPEN] The 'Winning' Gene S"
layout: "post"
diff: 普及+/提高
pid: P10279
tag: ['USACO', '2024', '单调栈']
---
# [USACO24OPEN] The 'Winning' Gene S
## 题目背景

**注意：本题的内存限制为 512MB，通常限制的 2 倍。**
## 题目描述

在多年举办比赛并看着 Bessie 一次又一次地获得第一名后，Farmer John 意识到这绝非偶然。他得出结论，Bessie 一定将胜利写进了 DNA，于是他开始寻找这种「胜利」基因。

他设计了一个过程来识别这个「胜利」基因的可能候选。他获取了 Bessie 的基因组，为一个长为 $N$ 的字符串 $S$，其中 $1\le N\le 3000$。他选择某个数对 $(K,L)$，其中 $1\le L\le K\le N$，表示「胜利」基因候选的长度将为 $L$，并且将在一个较大的 $K$ 长度子串中进行寻找。为了识别这一基因，他从 $S$ 中取出所有 $K$ 长度的子串，我们将称这样的子串为一个 $K$-mer。对于一个给定的 $K$-mer，他取出其所有长度为 $L$ 的子串，将字典序最小的子串识别为胜利基因候选（如果存在并列则选择其中最左边的子串），然后将该字串在 $S$ 中的起始位置 $p_i$（从 $0$ 开始索引）写入一个集合 $P$。

由于他还没有选定 $K$ 和 $L$，他想知道每对 $(K,L)$ 将有多少个候选。

对于 $1\ldots N$ 中的每一个 $v$，帮助他求出满足 $|P|=v$ 的 $(K,L)$ 对的数量。 
## 输入格式

输入的第一行包含 $N$，为字符串的长度。第二行包含 $S$，为给定的字符串。输入保证所有字符均为大写字符，其中 $s_i\in \texttt A-\texttt Z$，因为奶牛遗传学远比我们的高级。
## 输出格式

对于 $1\ldots N$ 中的每一个 $v$，输出满足 $|P|=v$ 的 $(K,L)$ 对的数量，每行输出一个数。

## 样例

### 样例输入 #1
```
8
AGTCAACG
```
### 样例输出 #1
```
11
10
5
4
2
2
1
1
```
## 提示

### 样例解释 1

在这个测试用例中，输出的第三行为 $5$ 是因为我们发现恰好有 $5$ 对 $K$ 和 $L$ 存在三个「胜利」基因候选。这些候选为（其中 $p_i$ 从 $0$ 开始索引）：

```plain
(4,2) -> P = [0,3,4]
(5,3) -> P = [0,3,4]
(6,4) -> P = [0,3,4]
(6,5) -> P = [0,1,3]
(6,6) -> P = [0,1,2]
```

为了了解 $(4,2)$ 如何得到这些结果，我们取出所有的 $4$-mer

```plain
AGTC
GTCA
TCAA
CAAC
AACG
```

对于每一个 $4$-mer，我们识别出字典序最小的长度为 $2$ 的子串

```plain
AGTC -> AG
GTCA -> CA
TCAA -> AA
CAAC -> AA
AACG -> AA
```

我们取出所有这些子串在原字符串中的位置并将它们添加到集合 $P$ 中，得到 $P=[0,3,4]$。

另一方面，如果我们关注 $(4,1)$ 对，我们会发现这只会得到总共 $2$ 个「胜利」基因候选。如果我们取出所有的 $4$-mer 并识别字典序最小的长度为 $1$ 的子串（用 A，A' 和 A* 来区分不同的 A），我们得到

```plain
AGTC -> A
GTCA' -> A'
TCA'A* -> A'
CA'A*C -> A'
A'A*CG -> A'
```

尽管 A' 和 A* 在最后 3 种情况下字典序均为最小，但最左边的子串优先，因此仅有 A' 在所有这些情况中被视为候选。这意味着 $P=[0,4]$。

### 测试点性质

- 测试点 $2-4$：$N\le 100$。
- 测试点 $5-7$：$N\le 500$。
- 测试点 $8-16$：没有额外限制。


---

---
title: "[UESTCPC 2024] 饮料"
layout: "post"
diff: 普及+/提高
pid: P10334
tag: ['贪心', '2024', 'O2优化', '单调栈', '高校校赛']
---
# [UESTCPC 2024] 饮料
## 题目描述

有一个果汁机，每分钟可以制作一杯任意体积的果汁。

有 $n$ 个人排成一队。第 $i$ 个人将在第 $t_i$ 分钟走到果汁机前，并拿走当前已经制作的果汁中体积最大的一杯。第 $i$ 个人拿到体积大于等于 $a_i$ 的果汁就会满意。如果此时没有果汁，则第 $i$ 个人也会不满意。

问是否能够让所有人满意。如果是，输出让所有人满意所需的果汁体积之和的最小值。
## 输入格式

第一行一个整数 $n$ $(1\leq n\leq 2 \times 10^5)$，表示队伍中人的数量。

接下来一行 $n$ 个整数 $t_1,t_2,\ldots,t_n$ $(1\leq t_1\leq t_2\leq\ldots\leq t_n\leq 10^9)$，其中 $t_i$ 表示第 $i$ 个人到果汁机前的时间。如果两个人的到达时间相同，则按题目给出的顺序从左到右决定先后。

接下来一行 $n$ 个整数 $a_1,a_2,\ldots,a_n$ $(1\leq a_i\leq 10^9)$，其中 $a_i$ 表示第 $i$ 个人对果汁的体积要求。

## 输出格式

如果不能令所有人满意，输出 $-1$。

否则输出一行一个整数，表示所需的最小体积和。
## 样例

### 样例输入 #1
```
5
1 3 4 6 6
3 8 2 7 4
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
5
1 3 4 5 5
3 8 2 7 4
```
### 样例输出 #2
```
26
```
## 提示

样例一解释如下：

| 时间 | 制作 | 取走 |
| :----------: | :----------: | :----------: |
| $1$ | $3$ | $3$ |
| $2$ | $-$ | $-$ |
| $3$ | $8$ | $8$ |
| $4$ | $2$ | $2$ |
| $5$ | $4$ | $-$ |
| $6$ | $7$ | $7,4$ |

样例二解释如下：

| 时间 | 制作 | 取走 |
| :----------: | :----------: | :----------: |
| $1$ | $3$ | $3$ |
| $2$ | $4$ | $-$ |
| $3$ | $8$ | $8$ |
| $4$ | $4$ | $4$ |
| $5$ | $7$ | $7,4$ |
| $6$ | $-$ | $-$ |


---

---
title: "表达式计算4"
layout: "post"
diff: 普及+/提高
pid: P10473
tag: ['模拟', 'O2优化', '栈']
---
# 表达式计算4
## 题目描述

给出一个表达式，其中运算符仅包含 +，-，*，/，^，要求求出表达式的最终值。

数据可能会出现括号情况，还有可能出现多余括号情况。

数据保证不会出现超过 int 范围的数据，数据可能会出现负数情况。
## 输入格式

仅一行一个字符串，即为表达式。

## 输出格式

仅一行，既为表达式算出的结果。
## 样例

### 样例输入 #1
```
(2+2)^(1+1)
```
### 样例输出 #1
```
16
```
## 提示

表达式总长度不超过 $30$。


---

---
title: "「CZOI-R1」消除威胁"
layout: "post"
diff: 普及+/提高
pid: P10798
tag: ['贪心', 'O2优化', 'ST 表', '单调栈']
---
# 「CZOI-R1」消除威胁
## 题目背景

**本题数据已修复。**
## 题目描述

给定一个序列 $\{A_n\}$。

我们称序列 $A$ 中的一个区间 $[l,r]$ 具有威胁，当且仅当 $1\le l<r\le n$ 且 $A_l=A_r$，且 $\forall i\in[l,r]$ 满足 $|A_i|\le|A_l|$。

你可以操作 $A$ 任意次，每次操作选择一个 $A_i$ 修改为 $-A_i$。请问最后序列 $A$ 中具有威胁的**不同**区间**最少**有多少个？



两个区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 不同，当且仅当 $l_1 \ne l_2$ 或 $r_1 \ne r_2$。


## 输入格式

第一行一个整数 $n$ ，表示 $A$ 的长度。

第二行 $n$ 个整数，表示 $\{A_n\}$。
## 输出格式

第一行一个正整数，表示**最少**的具有威胁的区间个数。
## 样例

### 样例输入 #1
```
8
3 2 1 2 3 -1 3 3
```
### 样例输出 #1
```
2
```
## 提示

**【数据范围】**

**本题采用捆绑测试**。
- Subtask #1（$10\text{ pts}$）：$n\le10$。
- Subtask #2（$10\text{ pts}$）：$n\le10^3$。
- Subtask #3（$10\text{ pts}$）：$|A_i|\le60$。
- Subtask #4（$10\text{ pts}$）：$|A_i|$ 均相等。
- Subtask #5（$20\text{ pts}$）：$n\le10^5$。
- Subtask #6（$40\text{ pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le n\le5\times10^5$，$|A_i|\le10^9$。


---

---
title: "[ZJOI2007] 棋盘制作"
layout: "post"
diff: 普及+/提高
pid: P1169
tag: ['动态规划 DP', '2007', '各省省选', '浙江', '栈']
---
# [ZJOI2007] 棋盘制作
## 题目描述

国际象棋是世界上最古老的博弈游戏之一，和中国的围棋、象棋以及日本的将棋同享盛名。据说国际象棋起源于易经的思想，棋盘是一个 $8 \times 8$ 大小的黑白相间的方阵，对应八八六十四卦，黑白对应阴阳。

而我们的主人公 `小Q`，正是国际象棋的狂热爱好者。作为一个顶尖高手，他已不满足于普通的棋盘与规则，于是他跟他的好朋友 `小W` 决定将棋盘扩大以适应他们的新规则。

`小Q` 找到了一张由 $N \times M$ 个正方形的格子组成的矩形纸片，每个格子被涂有黑白两种颜色之一。`小Q` 想在这种纸中裁减一部分作为新棋盘，当然，他希望这个棋盘尽可能的大。

不过 `小Q` 还没有决定是找一个正方形的棋盘还是一个矩形的棋盘（当然，不管哪种，棋盘必须都黑白相间，即相邻的格子不同色），所以他希望可以找到最大的正方形棋盘面积和最大的矩形棋盘面积，从而决定哪个更好一些。

于是 `小Q` 找到了即将参加全国信息学竞赛的你，你能帮助他么？

## 输入格式

包含两个整数 $N$ 和 $M$，分别表示矩形纸片的长和宽。接下来的 $N$ 行包含一个 $N\times M$ 的 $01$ 矩阵，表示这张矩形纸片的颜色（$0$ 表示白色，$1$ 表示黑色）。

## 输出格式

包含两行，每行包含一个整数。第一行为可以找到的最大正方形棋盘的面积，第二行为可以找到的最大矩形棋盘的面积（注意正方形和矩形是可以相交或者包含的）。

## 样例

### 样例输入 #1
```
3 3
1 0 1
0 1 0
1 0 0

```
### 样例输出 #1
```
4
6

```
## 提示

对于 $20\%$ 的数据，$N, M ≤ 80$

对于 $40\%$ 的数据，$N, M ≤ 400$

对于 $100\%$ 的数据，$N, M ≤ 2000$



---

---
title: "表达式的转换"
layout: "post"
diff: 普及+/提高
pid: P1175
tag: ['模拟', '字符串', '线性数据结构', '栈']
---
# 表达式的转换
## 题目描述

平常我们书写的表达式称为中缀表达式，因为它将运算符放在两个操作数中间，许多情况下为了确定运算顺序，括号是不可少的，而后缀表达式就不必用括号了。

后缀标记法：书写表达式时采用运算紧跟在两个操作数之后，从而实现了无括号处理和优先级处理，使计算机的处理规则简化为：从左到右顺序完成计算，并用结果取而代之。

例如：`8-(3+2*6)/5+4` 可以写为：`8 3 2 6 * + 5 / - 4 +`

其计算步骤为：

```
8 3 2 6 * + 5 / - 4 +
8 3 12 + 5 / - 4 +
8 15 5 / - 4 +
8 3 - 4 +
5 4 +
9
```

编写一个程序，完成这个转换，要求输出的每一个数据间都留一个空格。
## 输入格式

就一行，是一个中缀表达式。输入的符号中只有这些基本符号 `0123456789+-*/^()`，并且不会出现形如 `2*-3` 的格式。

表达式中的基本数字也都是一位的，不会出现形如 `12` 形式的数字。

所输入的字符串不要判错。

## 输出格式

若干个后缀表达式，第 $i + 1$ 行比第 $i$ 行少一个运算符和一个操作数，最后一行只有一个数字，表示运算结果。

## 样例

### 样例输入 #1
```
8-(3+2*6)/5+4

```
### 样例输出 #1
```
8 3 2 6 * + 5 / - 4 + 
8 3 12 + 5 / - 4 + 
8 15 5 / - 4 + 
8 3 - 4 + 
5 4 + 
9

```
### 样例输入 #2
```
2^2^3

```
### 样例输出 #2
```
2 2 3 ^ ^
2 8 ^
256

```
## 提示

运算的结果可能为负数，`/` 以整除运算。并且中间每一步都不会超过 $2^{31}$。字符串长度不超过 $100$。

注意乘方运算 `^` 是从右向左结合的，即 `2 ^ 2 ^ 3` 为 `2 ^ (2 ^ 3)`，后缀表达式为 `2 2 3 ^ ^`。

其他同优先级的运算是从左向右结合的，即 `4 / 2 / 2 * 2` 为 `((4 / 2) / 2) * 2`，后缀表达式为 `4 2 / 2 / 2 *`。

保证不会出现计算乘方时幂次为负数的情况，故保证一切中间结果为整数。


---

---
title: "[JSOI2008] 最大数"
layout: "post"
diff: 普及+/提高
pid: P1198
tag: ['2008', '线段树', '二分', '各省省选', '江苏', '栈', 'ST 表']
---
# [JSOI2008] 最大数
## 题目描述

现在请求你维护一个数列，要求提供以下两种操作：

1.  查询操作。

语法：`Q L`

功能：查询当前数列中末尾 $L$ 个数中的最大的数，并输出这个数的值。

限制：$L$ 不超过当前数列的长度。$(L > 0)$

2. 插入操作。

语法：`A n`

功能：将 $n$ 加上 $t$，其中 $t$ 是最近一次查询操作的答案（如果还未执行过查询操作，则 $t=0$），并将所得结果对一个固定的常数 $D$ 取模，将所得答案插入到数列的末尾。

限制：$n$ 是整数（可能为负数）并且在长整范围内。

注意：初始时数列是空的，没有一个数。

## 输入格式

第一行两个整数，$M$ 和 $D$，其中 $M$ 表示操作的个数，$D$ 如上文中所述。

接下来的 $M$ 行，每行一个字符串，描述一个具体的操作。语法如上文所述。
## 输出格式

对于每一个查询操作，你应该按照顺序依次输出结果，每个结果占一行。

## 样例

### 样例输入 #1
```
5 100
A 96
Q 1
A 97
Q 1
Q 2

```
### 样例输出 #1
```
96
93
96

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq M \leq 2 \times 10^5$，$1 \leq D \leq 2 \times 10^9$。


---

---
title: "[蓝桥杯 2024 国 Python B] 括号与字母"
layout: "post"
diff: 普及+/提高
pid: P12271
tag: ['2024', '前缀和', '栈', '蓝桥杯国赛', '离线处理']
---
# [蓝桥杯 2024 国 Python B] 括号与字母
## 题目描述

给定一个仅包含小写字母和括号的字符串 $S$，保证括号可以两两匹配。

给出 $Q$ 组询问，每组询问给出一个小写字母 $c_i$ 和一个数 $x_i$，询问 $S$ 中有多少对匹配的括号之间有不少于 $x_i$ 个 $c_i$。

## 输入格式

输入的第一行包含一个字符串 $S$。

第二行包含一个整数 $Q$。

接下来 $Q$ 行，每行包含一个小写字母 $c_i$ 和一个整数 $x_i$ 表示一组询问，用一个空格分隔。
## 输出格式

输出 $Q$ 行，每行包含一个整数，依次表示每个询问的答案。
## 样例

### 样例输入 #1
```
((a)()((b)((c))))
3
a 2
b 1
c 1
```
### 样例输出 #1
```
0
3
4
```
## 提示

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$|S|, Q \leq 5000$；
- 对于 $70\%$ 的评测用例，$|S| \leq 100000$；
- 对于所有评测用例，$1 \leq |S| \leq 10^6$，$1 \leq Q \leq 100000$，$0 \leq x_i < 10^6$。其中 $|S|$ 表示 $S$ 的长度。


---

---
title: "[蓝桥杯 2025 省 A 第二场] 栈与乘积"
layout: "post"
diff: 普及+/提高
pid: P12347
tag: ['线段树', '2025', '栈', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 A 第二场] 栈与乘积
## 题目背景

目前测试数据可能较水，我们之后会加强数据。
## 题目描述

给定一个栈，给出若干次如下类型的操作：

1. $1 \ x$: 将 $x$ 加入栈顶。
2. $2$: 将栈顶的数弹出（如果栈是空的，则什么都不做）。
3. $3 \ y$: 查询栈内的最顶端 $y$ 个数的乘积。如果大于等于 $2^{32}$，输出 `OVERFLOW`。如果栈内不足 $y$ 个数，输出 `ERROR`。
## 输入格式

输入的第一行包含一个正整数 $Q$，表示操作次数。

接下来 $Q$ 行，每行包含一个或两个正整数表示一个操作，如果一行包含两个整数，两个整数之间用一个空格分隔。
## 输出格式

对于每个 $3 \ y$ 形式的操作，输出一行包含一个整数，表示答案。
## 样例

### 样例输入 #1
```
9
1 65536
1 65536
3 2
3 3
2
1 1024
1 2
3 2
3 3
```
### 样例输出 #1
```
OVERFLOW
ERROR
2048
134217728
```
## 提示

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$Q \leq 5000$；
- 对于所有评测用例，$1 \leq Q \leq 10^5$，$0 \leq x < 2^{30}$，$1 \leq y < 2^{30}$。


---

---
title: "「ROI 2025 Day1」奥林匹克楼梯"
layout: "post"
diff: 普及+/提高
pid: P12501
tag: ['2025', '单调栈', 'ROI（俄罗斯）']
---
# 「ROI 2025 Day1」奥林匹克楼梯
## 题目描述

**译自 [ROI 2025](https://neerc.ifmo.ru/school/archive/2024-2025.html) Day1 T1.** ***[Лестница для участников олимпиады](https://neerc.ifmo.ru/school/archive/2024-2025/ru-olymp-roi-2025-day1.pdf)***

在天狼星教育中心，学生们最喜欢聚集和交流的地方莫过于各式各样的楼梯。然而，信息学奥林匹克的参与者数量远远超过了其他任何教育项目的学生，现有的楼梯已无法满足需求。因此，装备部门决定利用一块特殊的模板，打造一座全新的楼梯。

这块模板是一个由 $h$ 行 $w$ 列组成的表格，行从上到下、列从左到右依次编号。表格的每个格子中记录了一个数字，要么是 `0`，要么是 `1`。而所谓的楼梯，只能由那些格子中填有 `1` 的格子构成。

楼梯是由若干连续行中填有 `1` 的格子集合组成的。在每一行中，被选中的格子必须形成一个连续的段。  
同时，满足以下条件：  
- 每下一行的选中格子数量不得少于紧邻其上的上一行；  
- 每行中最左边的选中格子必须位于同一列。

下图展示了一个楼梯的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/l57xqjcb.png)

你的任务是找出给定表格中，能够构成楼梯的最大格子数量。
## 输入格式

输入的第一行包含两个整数 $h$ 和 $w$ $(1 \le h, w \le 2 \cdot 10^5, h \cdot w \le 4 \cdot 10^6)$，分别表示表格的行数和列数。

接下来的 $h$ 行，每行包含 $w$ 个字符，每个字符为 `0` 或 `1`，表示表格中对应格子的数字。
## 输出格式

输出一个整数，表示能够构成楼梯的最大格子数量。
## 样例

### 样例输入 #1
```
6 4
0011
1101
0111
1110
0111
0100
```
### 样例输出 #1
```
8
```
## 提示

样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/prkfqb5m.png)

详细子任务附加限制及分值如下表所示。其中子任务 $0$ 是样例。

| 子任务 | 分值 | 附加限制 | 
| :-: | :-: | :-: |
| $1$        | $25$ | $h, w \le 50$ |
| $2$        | $25$ | $h, w \le 400$ |
| $3$        | $25$ | $h \cdot w \le 200\,000$ |
| $4$        | $25$ | 无附加限制 |


---

---
title: "[GCJ 2013 #1A] Manage your Energy"
layout: "post"
diff: 普及+/提高
pid: P13286
tag: ['贪心', '2013', '单调栈', 'Google Code Jam']
---
# [GCJ 2013 #1A] Manage your Energy
## 题目描述

You've got a very busy calendar today, full of important stuff to do. You worked hard to prepare and make sure all the activities don't overlap. Now it's morning, and you're worried that despite all of your enthusiasm, you won't have the energy to do all of this with full engagement.

You will have to manage your energy carefully. You start the day full of energy - $E$ joules of energy, to be precise. You know you can't go below zero joules, or you will drop from exhaustion. You can spend any non-negative, integer number of joules on each activity (you can spend zero, if you feel lazy), and after each activity you will regain $R$ joules of energy. No matter how lazy you are, however, you cannot have more than $E$ joules of energy at any time; any extra energy you would regain past that point is wasted.

Now, some things (like solving Code Jam problems) are more important than others. For the $i$th activity, you have a value $v_i$ that expresses how important this activity is to you. The gain you get from each activity is the value of the activity, multiplied by the amount of energy you spent on the activity (in joules). You want to manage your energy so that your total gain will be as large as possible.

Note that you cannot reorder the activities in your calendar. You just have to manage your energy as well as you can with the calendar you have.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case is described by two lines. The first contains three integers: $E$, the maximum (and initial) amount of energy, $R$, the amount you regain after each activity, and $N$, the number of activities planned for the day. The second line contains $N$ integers $v_i$, describing the values of the activities you have planned for today.

## 输出格式

For each test case, output one line containing "Case #x: $y$", where $x$ is the case number (starting from 1) and $y$ is the maximum gain you can achieve by managing your energy that day.
## 样例

### 样例输入 #1
```
3
5 2 2
2 1
5 2 2
1 2
3 3 4
4 1 3 5
```
### 样例输出 #1
```
Case #1: 12
Case #2: 12
Case #3: 39
```
## 提示

**Sample Explanation**

In the first case, we can spend all 5 joules of our energy on the first activity (for a gain of 10), regain 2 and spend them on the second activity. In the second case, we spend 2 joules on the first activity, regain them, and spend 5 on the second. In the third case, our regain rate is equal to the maximum energy, meaning we always recover all energy after each activity - so we can spend full 3 joules on each activity.

**Limits**

- $1 \leq T \leq 100 .$

**Small dataset (12 Pts, Test set 1 - Visible)**

- $1 \leq E \leq 5 .$
- $1 \leq R \leq 5 .$
- $1 \leq N \leq 10 .$
- $1 \leq v_{i} \leq 10 .$

**Large dataset (23 Pts, Test set 2 - Hidden)**

- $1 \leq E \leq 10^{7} .$
- $1 \leq R \leq 10^{7} .$
- $1 \leq N \leq 10^{4} .$
- $1 \leq v_{i} \leq 10^{7} .$


---

---
title: "幻象迷宫"
layout: "post"
diff: 普及+/提高
pid: P1363
tag: ['搜索', '图论', '深度优先搜索 DFS', '栈']
---
# 幻象迷宫
## 题目背景

（喵星人 LHX 和 WD 同心协力击退了汪星人的入侵，不幸的是，汪星人撤退之前给它们制造了一片幻象迷宫。）

WD：呜呜，肿么办啊……

LHX：momo...我们一定能走出去的！

WD：嗯，+U+U！
## 题目描述

幻象迷宫可以认为是无限大的，不过它由若干个 $N\times M$ 的矩阵重复组成。矩阵中有的地方是道路，用 $\verb!.!$ 表示；有的地方是墙，用 $\verb!#!$ 表示。LHX 和 WD 所在的位置用 $\verb!S!$ 表示。也就是对于迷宫中的一个点$(x,y)$，如果 $(x \bmod n,y \bmod m)$ 是 $\verb!.!$ 或者 $\verb!S!$，那么这个地方是道路；如果 $(x \bmod n,y \bmod m)$ 是$\verb!#!$，那么这个地方是墙。LHX 和 WD 可以向上下左右四个方向移动，当然不能移动到墙上。

请你告诉 LHX 和 WD，它们能否走出幻象迷宫（如果它们能走到距离起点无限远处，就认为能走出去）。如果不能的话，LHX 就只好启动城堡的毁灭程序了……当然不到万不得已，他不想这么做。
## 输入格式

输入包含多组数据，以 EOF 结尾。

每组数据的第一行是两个整数 $N,M$。

接下来是一个 $N\times M$ 的字符矩阵，表示迷宫里 $(0,0)$ 到 $(n-1,m-1)$ 这个矩阵单元。

## 输出格式

对于每组数据，输出一个字符串，`Yes` 或者 `No`。

## 样例

### 样例输入 #1
```
5 4
##.#
##S#
#..#
#.##
#..#
5 4
##.#
##S#
#..#
..#.
#.##

```
### 样例输出 #1
```
Yes
No


```
## 提示

- 对于 $30\%$ 的数据，$1\le N,M\le 20$；
- 对于 $50\%$ 的数据，$1\le N,M\le 100$；
- 对于 $100\%$ 的数据，$1\le N,M\le 1500$，每个测试点不超过 $10$ 组数据。


---

---
title: "【MGVOI R1-C】收集括号（brackets）"
layout: "post"
diff: 普及+/提高
pid: P13731
tag: ['动态规划 DP', 'O2优化', '深度优先搜索 DFS', '栈']
---
# 【MGVOI R1-C】收集括号（brackets）
## 题目描述


本题中 **合法括号串** 的定义如下：

::::info[合法括号串的定义]{open}
* ```()``` 是合法括号串。
* 若 ```A``` 是合法括号串，则 ```(A)``` 也是合法括号串。
* 若 ```A```，```B``` 均为合法括号串，则 ```AB``` 也是合法括号串。
* 所有的合法括号串都可以通过上述三条规则得到。

::::

Alice 和 Bob 正在合作玩一款叫做“收集括号”的游戏！这个游戏总共分为以下三步流程：

::::success[第一步：初始化]{open}

* 首先，计算机会自动生成一个 $n$ 行 $m$ 列的方格图，其中第 $i$ 行第 $j$ 列的方格对应的坐标为 $(i,j)$。例如，左上角方格的坐标为 $(1,1)$，右下角方格的坐标为 $(n,m)$。

* 然后，计算机会在每个方格中都填入一个字符（从 ```L```，```R```，```X``` 中选择）。若某个方格中的字符为 ```L```，则表示方格中有一个左括号；若为 ```R```，则表示方格中有一个右括号；若为 ```X```，则表示方格中有一个障碍物。

::::

::::success[第二步：Alice 的行动回合]{open}

* **在第一步流程完全结束之后**，Alice 可以对方格图进行任意次（包括 $0$ 次）**反转操作**。
  
* 在一次反转操作中，Alice 首先需要选择方格图的 **某一行或某一列** 作为这次操作的范围。

* 之后，计算机将遍历 Alice 选择的这一行（或这一列）。对于每一个范围内的方格（除了障碍物），计算机都会反转这个方格上的字符。也就是说，如果方格上原先的字符是 ```L```，那么就将其改为 ```R```；如果原先是 ```R```，那么就将其改为 ```L```；如果原先是 ```X```，那么不做任何改动。

* 对于这一次反转操作而言，如果 Alice 选择了第 $i$ 行（$1\le i\le n$）作为反转范围，那么需要花费 $a_i$ 枚金币；如果她选择了第 $j$ 列（$1\le j\le m$）作为反转范围，那么需要花费 $b_j$ 枚金币。

::::

::::success[第三步：Bob 的行动回合]{open}

* **在第二步流程完全结束之后**，Bob 将从坐标为 $(1,1)$ 的方格处（也就是方格图的左上角）出发，开始收集方格图中的括号。

* 在任意时刻，Bob 都可以选择 **向正下方或正右方** 移动一个方格（前提是要到达的位置既不超过方格图的边界，也没有障碍物）。也就是说，如果 Bob 位于方格 $(x,y)$，那么他下一步就可以前往方格 $(x+1,y)$ 或者方格 $(x,y+1)$，只要他保证自己 **始终位于方格图的范围内，并且不会前往有障碍物的方格**。

* Bob 每到达一个方格，就会收集这个方格中的括号。在抵达坐标为 $(n,m)$ 的终点方格（也就是方格图的右下角）之后，他会整理自己收集到的所有括号（包括起点和终点方格的括号），并将其 **由先到后按照收集的顺序** 排成一个字符串 $S$。

* 如果 $S$ 是一个合法括号串，则 Alice 和 Bob 在这局游戏中共同获胜；否则他们在这局游戏中落败。（如果 Bob 无法到达终点方格，则也认为他们落败）
::::


---


**注意：** 我们假设 Bob 是绝顶聪明的，也就是说，在 Alice 的所有操作完成之后，只要存在任何一种符合上述规则的行动方式能让他们获胜，Bob 就会采用这种行动方式。

在计算机已经填满方格图的情况下（即第一步的初始化流程已经完成），请你帮 Alice 判断，是否存在一种操作方案，使得她能够和 Bob 共同获胜？如果存在，则她最少需要花费多少枚金币来取胜？


## 输入格式

**每个测试点包含多组测试数据，各组测试数据之间相互独立。**

第一行包含一个正整数 $T$，表示测试数据的组数。

对于每组测试数据：

第一行包含两个正整数 $n,m$，分别表示方格图的行数和列数。**保证 $\bm{n+m}$ 是一个奇数**，这意味着 Bob 最终得到的字符串 $S$ 的长度一定为偶数。

第二行包含 $n$ 个正整数，其中第 $i$ 个正整数 $a_i$ 表示在方格图的第 $i$ 行进行反转操作需花费的金币数量。

第三行包含 $m$ 个正整数，其中第 $j$ 个正整数 $b_j$ 表示在方格图的第 $j$ 列进行反转操作需花费的金币数量。

接下来 $n$ 行，每行包含一个长度为 $m$ 的字符串（仅含 ```L```，```R```，```X``` 三种字符），其中第 $i$ 行第 $j$ 个字符即为计算机在方格 $(i,j)$ 中填入的字符。保证左上角和右下角方格中的字符不为 ```X```。


## 输出格式

对于每组测试数据，仅需在单独一行输出一个整数：

* 如果 Alice 有可能和 Bob 共同获胜，则输出她最少需要花费的金币数；
  
* 否则，输出 ```-1```。


## 样例

### 样例输入 #1
```
3
1 4
1
1 1 1 1
LXXR
1 4
1
1 1 1 1
LLRR
2 3
1 1
1 1 1
LRR
XRL
```
### 样例输出 #1
```
-1
0
1
```
### 样例输入 #2
```
4
4 3
1 1 1 9
1 1 1
LLL
LXL
LXL
LLL
4 3
1 1 1 1
1 1 1
LLL
LXL
LXL
LLL
4 5
8 5 6 3
8 5 6 5 3
RRRRR
RRXXR
XRRRL
RXLLR
7 10
10 100 1 1 100 1 10
10 1 1 1 1 1 1 1 1 10
RLLLLLLLXX
RXLXLXLLRL
RLLLLLXLLL
LLXXRRRXLX
LLLLLRLLLX
XLLLXLXLLR
LLXLXLLXLL
```
### 样例输出 #2
```
2
1
13
22
```
## 提示

**【样例 #1】**

::::info[样例 #1 解释]

对于第一组测试数据，计算机生成的方格图为 ```LXXR```。由于中间两个障碍物的阻挡，Bob 无法从方格 $(1,1)$ 向右移动到方格 $(1,4)$，故 Alice 和 Bob 不可能获胜，输出 ```-1```；

对于第二组测试数据，计算机生成的方格图为 ```LLRR```。显然，Bob 可以直接从方格 $(1,1)$ 向右移动到方格 $(1,4)$，最终得到的 $S=(())$ 就是一个合法括号串。因此，Alice 无需花费任何金币进行反转操作即可获胜，输出 ```0```；

对于第三组测试数据，Alice 只需花费 $b_3=1$ 枚金币对第三列使用一次反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{L}}$ |
| -----------: | -----------: | -----------: |
| $\mathtt{X}$ | $\mathtt{R}$ | $\orange{\mathtt{R}}$ |

Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=()()$，这是一个合法括号串。

容易证明，要让他们获胜最少需要 $1$ 枚金币，故输出 ```1```。

::::

**【样例 #2】**

::::info[样例 #2 解释]

:::success[第一组测试数据]

对于第一组测试数据，Alice 可以分别对第二行和第三列使用反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{R}}$ |
| -----------: | -----------: | -----------: |
| $\mathtt{R}$ | $\mathtt{X}$ | $\orange{\mathtt{L}}$ |
| $\mathtt{L}$ | $\mathtt{X}$ | $\orange{\mathtt{R}}$ |
| $\mathtt{L}$ | $\mathtt{L}$ | $\orange{\mathtt{R}}$ |

* 值得注意的一点是，对于方格 $(2,3)$，由于它总共经历了两次反转，所以仍然维持最开始的状态 $\mathtt{L}$。

Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=(()())$，这是一个合法括号串。

Alice 总共需要花费 $a_2+b_3=2$ 枚金币，可以证明为最小花费。
:::

:::success[第二组测试数据]

对于第二组测试数据，Alice 可以对第四行使用反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\mathtt{L}$ | $\mathtt{L}$ |
| -----------: | -----------: | -----------: |
| $\orange{\mathtt{L}}$ | $\mathtt{X}$ | $\mathtt{L}$ |
| $\orange{\mathtt{L}}$ | $\mathtt{X}$ | $\mathtt{L}$ |
| $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ |

Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=((()))$，这是一个合法括号串。

Alice 总共需要花费 $a_4=1$ 枚金币，可以证明为最小花费。

:::

:::success[第三组测试数据]

对于第三组测试数据，Alice 可以分别对第一行、第二行使用反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{L}$ |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\mathtt{X}$ | $\mathtt{X}$ | $\mathtt{L}$ |
| $\mathtt{X}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\mathtt{L}$ |
| $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{R}}$ |

Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=((()))()$，这是一个合法括号串。

Alice 总共需要花费 $a_1+a_2=13$ 枚金币，可以证明为最小花费。

:::

:::success[第四组测试数据]

对于第四组测试数据，Alice 可以分别对第一行、第六行、第七行、第二列使用反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{R}}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{X}$ |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| $\mathtt{R}$ | $\mathtt{X}$ | $\orange{\mathtt{L}}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{R}$ | $\mathtt{L}$ |
| $\mathtt{R}$ | $\mathtt{R}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\mathtt{L}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{L}$ |
| $\mathtt{L}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{X}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{X}$ |
| $\mathtt{L}$ | $\mathtt{R}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{R}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\mathtt{L}$ | $\mathtt{X}$ |
| $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\mathtt{L}$ |
| $\mathtt{R}$ | $\mathtt{L}$ | $\mathtt{X}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ |


Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=(\red{()}\blue{(}\red{((()))}\orange{(())}\blue{)})$，这是一个合法括号串。（注：括号串的颜色仅为方便观察，与答案无关）

Alice 总共需要花费 $a_1+a_6+a_7+b_2=22$ 枚金币，可以证明为最小花费。
:::

::::

**【样例 #3】**

见附件中的 ```brackets/brackets3.in``` 与 ```brackets/brackets3.ans```。

这个样例满足测试点 $5 \sim 8$ 的限制。

**【样例 #4】**

见附件中的 ```brackets/brackets4.in``` 与 ```brackets/brackets4.ans```。

这个样例满足测试点 $9 \sim 12$ 的限制。

**【样例 #5】**

见附件中的 ```brackets/brackets5.in``` 与 ```brackets/brackets5.ans```。

这个样例满足测试点 $13 \sim 20$ 的限制。

---



**【数据范围】**

对于所有测试点，保证 $1\le T\le 5$，$1\le n,m\le 100$（$n+m$ 为奇数），$1\le a_i,b_j\le 10^5$，并且方格图中初始填入的字符仅含 ```L```，```R```，```X```，其中左上角和右下角的字符一定不为 ```X```。

::cute-table{tuack}

| **测试点编号** | $T \le$ | $n,m \le$ | $n+m\le$ | **特殊性质** |
|:-:|:-:|:-:|:-:|:-:|
| $1 \sim 4$ | $1$ | $6$ | $7$ |  无
| $5 \sim 8$ | $2$ | $14$ | $15$ | ^
| $9 \sim 12$ | $5$ | $100$ | $101$ | **A**
| $13 \sim 20$ | ^ | ^ | $199$ | 无

特殊性质 **A**：保证 $n=1$。

* 分值分配：每个测试点的分值为 $5$ 分。
* 为避免对算法复杂度常系数的考察，本题的时间限制被设为 1.5s。


---

---
title: "正误问题"
layout: "post"
diff: 普及+/提高
pid: P1575
tag: ['线性数据结构', '栈']
---
# 正误问题
## 题目描述

小 bobo 迷上了逻辑值运算。但小 bobo 算的头都晕了，也没算出个所以然。他只好找到你，让你帮他解决这个问题。

## 输入格式

一个字符串表达逻辑式子，内只包含 `true`，`false`，`or`，`and`，`not` 和空格，(不包含括号和 `xor`)，优先级同 pascal。(从高到低依次为 `not`，`and`，`or`)，同级左边先算，如果逻辑式有误则输出 `error`。

## 输出格式

输出一行表示运算结果：`true` 或者 `false`，如果无法得到结果的输出 `error`。

## 样例

### 样例输入 #1
```
true or false and false
```
### 样例输出 #1
```
true
```
## 提示

对于全部数据，保证输入数据串长小于 $255$。

本题结果为 `true`，`false`，`error` 各占 $\dfrac{1}{3}$，允许“骗分”，但不值得，因为是“水题”。

---

- $\text{upd 2022.7.21}$：新增加 $5$ 组 [Hack 数据](https://www.luogu.com.cn/discuss/459823)。


---

---
title: "[COI 2007] Patrik 音乐会的等待"
layout: "post"
diff: 普及+/提高
pid: P1823
tag: ['2007', '栈', 'COI（克罗地亚）']
---
# [COI 2007] Patrik 音乐会的等待
## 题目描述

$n$ 个人正在排队进入一个音乐会。人们等得很无聊，于是他们开始转来转去，想在队伍里寻找自己的熟人。

队列中任意两个人 $a$ 和 $b$，如果他们是相邻或他们之间没有人比 $a$ 或 $b$ 高，那么他们是可以互相看得见的。

写一个程序计算出有多少对人可以互相看见。
## 输入格式

输入的第一行包含一个整数 $n$，表示队伍中共有 $n$ 个人。

接下来的 $n$ 行中，每行包含一个整数，表示人的高度，以毫微米(等于 $10^{-9}$ 米)为单位，这些高度分别表示队伍中人的身高。
## 输出格式

输出仅有一行，包含一个数 $s$，表示队伍中共有 $s$ 对人可以互相看见。
## 样例

### 样例输入 #1
```
7 
2 
4 
1 
2 
2 
5 
1
```
### 样例输出 #1
```
10
```
## 提示

#### 数据规模与约定
对于全部的测试点，保证 $1\le$ 每个人的高度 $< 2^{31}$，$1 \le n \le 5\times 10^5$。


---

---
title: "[USACO09DEC] Dizzy Cows G"
layout: "post"
diff: 普及+/提高
pid: P2017
tag: ['搜索', '图论', '2009', 'USACO', 'Special Judge', '栈']
---
# [USACO09DEC] Dizzy Cows G
## 题目描述

The cows have taken to racing each other around the farm but they get very dizzy when running in circles, and everyone knows that dizzy cows don't produce any milk. Farmer John wants to convert all of the two-way cow paths in the farm to one-way paths in order to eliminate any 'cycles' and prevent the cows from getting dizzy.  A 'cycle' enables a cow to traverse one or more cow paths and arrive back at her starting point, thus completing a loop or circle.

The farm comprises N pastures (1 <= N <= 100,000) conveniently numbered 1..N. M1 (1 <= M1 <= 100,000) one-way cow paths and M2 two-way cow paths (1 <= M2 <= 100,000) connect the pastures. No path directly connects a pasture to itself, although multiple paths might connect two different pastures. A cow may or may not be able to travel between any two given pastures by following a sequence of cow paths.

Your job is to assign a direction to the two-way cow paths such that the entire farm (ultimately with only one-way paths) has no cycles. That is, there should be no sequence of one-way cow paths which leads back to its starting position. The existing one-way cow paths do not form a cycle and should be left as they are.

One-way cow paths run from pasture A\_i (1 <= A\_i <= N) to pasture B\_i (1 <= B\_i <= N). Two-way cow paths connect pastures X\_i (1 <= X\_i <= N) and Y\_i (1 <= Y\_i <= N).

Consider this example:

```cpp
1-->2 
|  /| 
| / | 
|/  | 
3<--4 
```
The cow paths between pastures 1 and 3, 2 and 3, and 2 and 4 are two-way paths. One-way paths connect 1 to 2 and also 4 to 3. One valid way to convert the two-way paths into one-way paths in such a way that there are no cycles would be to direct them from 1 to 3, from 2 to 3, and from 3 to 4:

```cpp
1-->2 
|  /| 
| / | 
vL  v 
3<--4 
```

## 输入格式

第一行三个整数 $n,m_1,m_2$，分别表示点数，有向边的数量，无向边的数量。

第二行起输入 $m_1$ 行，每行 $2$ 个整数 $a,b$，表示 $a$ 到 $b$ 有一条有向边。

接下来输入 $m_2$ 行，每行 $2$ 个整数 $a,b$，表示 $a$ 和 $b$ 中间有一条无向边。

## 输出格式

对于每条无向边，我们要求按输入顺序输出你定向的结果，也就是如果你输出 $a\ b$，那表示你将 $a$ 和 $b$ 中间的无向边定向为 $a \to b$。

注意，也许存在很多可行的解。你只要输出其中任意一个就好。

## 样例

### 样例输入 #1
```
4 2 3
1 2
4 3
1 3
4 2
3 2

```
### 样例输出 #1
```
1 3
4 2
2 3
```
## 题目翻译

奶牛们发现，在农场里面赛跑是很有趣的一件事.可是她们一旦在农场里面不断地转圈，就 会变得头晕目眩.众所周知，眩晕的奶牛是无法产奶的.于是，农夫约翰想要把他农场里面的双 向道路全部改为单向道路，使得他的农场里面一个圈都没有，以避免他的奶牛们被搞得晕头转 向.如果奶牛可以经过若干条道路回到起点，那么这些道路就称为一个圈.

农场有 $n\ (1 < n < 100000)$ 片草地，编号为 $1$ 到 $n$。这些草地由 $m_1$ 条单向 道路和 $m_2$ 条双向道路连接起来.任何一条道路都不会把一片草地和这片草地本身连接起来.但是，任意两片草地之间都可能有多条道路连接.不保证任意两片草地之间都有路 径相连。

你的任务是给所有的双向道路设定一个方向，使得整个农场(只剩下单向道路)最后一个圈都没有。也就是说，不存在一个单向道路序列的终点和起点重合。数据保证一开始就有的单向道路中，一个圈都没有。而且一开始就有的单向道路不能改变。

单向道路的起点是草地 $A_i$，终点是草地 $B_i$。双向道路连接草地 $X_i,Y_i$。



---

---
title: "[USACO14MAR] Mooo Moo S"
layout: "post"
diff: 普及+/提高
pid: P2214
tag: ['2014', 'USACO', '背包 DP', '栈']
---
# [USACO14MAR] Mooo Moo S
## 题目描述

Farmer John has completely forgotten how many cows he owns!  He is too embarrassed to go to his fields to count the cows, since he doesn't want the cows to realize his mental lapse.  Instead, he decides to count his cows secretly by planting microphones in the fields in which his cows tend to gather, figuring that he can determine the number of cows from the total volume of all the mooing he hears.

FJ's N fields (1 <= N <= 100) are all arranged in a line along a long straight road.  Each field might contain several types of cows; FJ owns cows that come from B different breeds (1 <= B <= 20), and a cow of breed i moos at a volume of V(i) (1 <= V(i) <= 100).  Moreover, there is a strong wind blowing down the road, which carries the sound of mooing in one direction from left to right: if the volume of mooing in some field is X, then in the next field this will contribute X-1 to the total mooing volume (and X-2 in the field after that, etc.). Otherwise stated, the mooing volume in a field is the sum of the contribution due to cows in that field, plus X-1, where X is the total mooing volume in the preceding field.

Given the volume of mooing that FJ records in each field, please compute the minimum possible number of cows FJ might own.

The volume FJ records in any field is at most 100,000.

### 题目背景
农夫约翰完全忘了他有多少头牛了！他不好意思到牧场里去数牛，因为他不想让牛意识到他的健忘。取而代之的是，他决定在奶牛聚集的牧场里安装麦克风，秘密计算出他能从中听到的所有牛叫声的总音量，以便以此确定奶牛的数量。
### 题目描述
$FJ$ 的 $N(1\le N\le 100)$ 个牧场都是沿着一条笔直的道路分布的。每一个牧场可能有许多种品种的奶牛； $FJ$ 拥有 $B(1\le B\le 20)$ 个不同品种的奶牛，而第 $i$ 种奶牛的叫声音量为 $V_i(1\le V_i \le 100)$ 。此外，有一股强风沿着道路吹来，将牛的叫声从左往右传递，如果某个牧场的总音量是 $x$ ，那么它将传递 $x-1$ 的音量到右边的下一个牧场。这就意味着，一个牧场里的总音量是处在该牧场的奶牛所发出的音量加上左边前一个牧场的总音量 $-1$ 。数据保证，每一个牧场内由该牧场所有奶牛所发出的总音量最多为$10^5$。
### 输入格式
第 $1$ 行：两个用空格分隔的整数 $N$ 和 $B$。      
第 $2...B+1$ 行：第 $i+1$ 行包含整数 $V_i$ 。        
第 $B+2...B+N+1$ 行：第 $B+i+1$ 行表示在第 $i$ 个牧场内所能监听到的总音量。
### 输出格式
共一行，即 $FJ$ 拥有的最小奶牛数量。

如果 FJ 不可能拥有一种牧场配置满足给出的条件，输出 `-1`。
### 说明/提示
#### 输入说明：
$FJ$ 拥有 $5$ 个牧场，每个牧场总音量从左到右分别为为$0、17、16、20、19$。 $FJ$ 有两种不同品种的奶牛；第一种奶牛的叫声音量是 $5$，第二种奶牛的叫声音量是 $7$ 。
#### 输出说明：
$2$ 号牧场场有  $2$ 头 $1$ 号品种的奶牛， $1$ 头 $2$ 号品种奶牛；还有一头牛在 $4$ 号牧场，共 $4$ 头奶牛。
## 输入格式

\* Line 1: The integers N and B.



\* Lines 2..1+B: Line i+1 contains the integer V(i).

\* Lines 2+B..1+B+N: Line 1+B+i contains the total volume of all mooing

in field i.

## 输出格式

\* Line 1: The minimum number of cows owned by FJ, or -1 if there is no

configuration of cows consistent with the input.

## 样例

### 样例输入 #1
```
5 2
5
7
0
17
16
20
19
```
### 样例输出 #1
```
4

```
## 提示

INPUT DETAILS:


FJ owns 5 fields, with mooing volumes 0,17,16,20,19.  There are two breeds

of cows; the first moos at a volume of 5, and the other at a volume of 7.

OUTPUT DETAILS:


There are 2 cows of breed #1 and 1 cow of breed #2 in field 2, and there is

another cow of breed #1 in field 4.


Source: USACO 2014 March Contest, Silver



---

---
title: "[USACO03FALL / HAOI2006] 受欢迎的牛 G"
layout: "post"
diff: 普及+/提高
pid: P2341
tag: ['图论', '2003', '2006', '河南', 'USACO', '各省省选', '强连通分量', 'Tarjan', '栈']
---
# [USACO03FALL / HAOI2006] 受欢迎的牛 G
## 题目背景

本题测试数据已修复。
## 题目描述

每头奶牛都梦想成为牛棚里的明星。被所有奶牛喜欢的奶牛就是一头明星奶牛。所有奶牛都是自恋狂，每头奶牛总是喜欢自己的。奶牛之间的“喜欢”是可以传递的——如果 $A$ 喜欢 $B$，$B$ 喜欢 $C$，那么 $A$ 也喜欢 $C$。牛栏里共有 $N$ 头奶牛，给定一些奶牛之间的爱慕关系，请你算出有多少头奶牛可以当明星。
## 输入格式

第一行：两个用空格分开的整数：$N$ 和 $M$。

接下来 $M$ 行：每行两个用空格分开的整数：$A$ 和 $B$，表示 $A$ 喜欢 $B$。

## 输出格式

一行单独一个整数，表示明星奶牛的数量。

## 样例

### 样例输入 #1
```
3 3
1 2
2 1
2 3
```
### 样例输出 #1
```
1
```
## 提示

只有 $3$ 号奶牛可以做明星。

【数据范围】

对于 $10\%$ 的数据，$N\le20$，$M\le50$。

对于 $30\%$ 的数据，$N\le10^3$，$M\le2\times 10^4$。

对于 $70\%$ 的数据，$N\le5\times 10^3$，$M\le5\times 10^4$。

对于 $100\%$ 的数据，$1\le N\le10^4$，$1\le M\le5\times 10^4$。


---

---
title: "角色属性树"
layout: "post"
diff: 普及+/提高
pid: P2441
tag: ['数学', '树形数据结构', '枚举', '素数判断,质数,筛法', '栈']
---
# 角色属性树
## 题目描述

绪萌同人社是一个有趣的组织，该组织结构是一个树形结构。有一个社长，直接下属一些副社长。每个副社长又直接下属一些部长……。

每个成员都有一个萌点的属性，萌点属性是由一些质数的萌元素乘积构成（例如，猫耳的值是 $2$，弱气的值是 $3$，黄毛的值是 $5$，病娇的值是 $7$，双马尾的值是 $11$ 等等）

举个例子，正妹是双份的猫耳，而且有一份弱气，她的属性值为 $2\times 2\times 3=12$。

现在组员关心一个问题，希望知道离自己最近且有相同萌元素上司是谁，例如，属性值为 $2、4、6、45$ 这样的属性值都算是和正妹有相同的属性。


然而，组员可能会随时变化自己的属性。啊。。感觉好麻烦啊。。

## 输入格式

第一行，$n,k$ 表示成员数与询问的次数

第二行，$n$ 个数，分别是 $1$ 到 $n$ 号成员的属性值

接下来 $n-1$ 行，$x_i,y_i$ 表示 $x_i$ 是 $y_i$ 的上司。

接下来来 $k$ 行，有两种情况

$1\ u_i$：询问离 $u_i$ 成员最近且有相同萌元素上司。

$2\ u_i$：$a$ 更改 $u_i$ 的属性值为 $a$。

## 输出格式

对于每个 $1$ 类型的询问，输出符合要求的编号。如果没有符合要求的编号，输出 $-1$。

## 样例

### 样例输入 #1
```
4 6

10 8 4 3

1 2

2 3

3 4

1 1

1 2

1 3

1 4

2 1 9

1 4
```
### 样例输出 #1
```
-1

1

2

-1

1
```
## 提示

对于 $20\%$ 的数据，没有修改的操作。

对于 $50\%$ 的数据，$n\le 100$，修改次数 $<10$。

对于 $100\%$ 的数据，$n\le 200000$，$k<100000$，修改次数 $\le 50,a\_i\le 2^{31}-1$

UPD：本题测试数据随机，可能是假题。


---

---
title: "[AHOI2002] 网络传输"
layout: "post"
diff: 普及+/提高
pid: P2558
tag: ['动态规划 DP', '搜索', '2002', '各省省选', '安徽', '栈']
---
# [AHOI2002] 网络传输
## 题目描述

在计算机网络中所有数据都是以二进制形式来传输的。但是在进行较大数据的传输时，直接使用该数的二进制形式加以传输则往往传输的位数过多。譬如要传输 $1024$ 就需要 $11$ 位二进制数。于是小可可提出了一种数据优化传输的设想，并打算对这一设想进行试验。

该设想是：正整数的所有方幂以及任意多个互不相等的 $k$ 的方幂之和排成一个递增数列 $\{a(k)n\}$，例如当 $k=3$ 时，$\{a(k)n\}$ 的前 $7$ 项为 $1(=3^0)$ 、 $3(=3^1)$ 、 $4(=3^0+3^1)$ 、 $9(=3^2)$ 、 $10(=3^0+3^2)$ 、 $12(=3^1+3^2)$ 、 $13(=3^0+3^1+3^2)$。

如果数 $d$ 是数列 $\{a(k)n\}$ 中的第 $p$ 项，则可以通过传送 $k$ 和 $p$ 这两个数来表示数 $d$。由于 $k$ 和 $p$ 这两个相对很小的数就可以表达出很大的数，因而理论上可以减少网络传输的位数。

小可可现在请你编写程序把接收到的数 $k$ 和 $p$ 所代表的数 $d$ 计算出来。
## 输入格式

文件中以一行的形式存放了两个正整数 $k$ 和 $p$，$1<k \le 1024$，
$1 \le p \le 1024$。
## 输出格式

以一行的形式输出问题的解（解的位数不超过 $50$ 位）。
## 样例

### 样例输入 #1
```
3 2
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 7
```
### 样例输出 #2
```
13
```


---

---
title: "[POI 2013] USU-Take-out"
layout: "post"
diff: 普及+/提高
pid: P3551
tag: ['2013', 'POI（波兰）', 'Special Judge', '栈']
---
# [POI 2013] USU-Take-out
## 题目描述

Little Edna has received the take-out game as a present.

Take-out is a single player game, in which the player is given a sequence of $n$ adjacent blocks, numbered from $1$ to $n$.

Each block is either black or white, and there are $k$ times as many white    blocks as there are black ones.

The player's goal is to remove all the blocks by certain permissible moves.

A single move consists in removing exactly $k$ white blocks and a single    black block without changing the positions of other blocks.

The move is permissible if there is no "gap" (a space left by    a previously taken out block) between any two blocks being removed.

Help poor little Edna in finding any sequence of permissible moves that    remove all the blocks.

有n块砖，其中白色是黑色的k倍，求一个消除序列，满足以下条件：

每次消除k+1个砖，其中k块白色，1块黑色，并且这k+1块砖从开始到结束，中间不能路过已经消除过的砖

数据保证有解

## 输入格式

In the first line of the standard input there are two integers, $n$ and $k$ ($2\le n\le 1\ 000\ 000$, $1\le k\le n-1$), separated by a single space, that denote the total number of blocks used in the gameand the number of white blocks per black node (to be removed in every move).  In all the tests the condition $k+1|n$ holds.

In the second line there is a string of $n$ letters b      or c.  These tell the colours of successive blocks (in Polish):

b (for biały) - white, c (for czarny)      - black.  You may assume that in all the tests there exists a sequence      of permissible moves that takes out all the blocks.

## 输出格式

Your program should print $\frac{n}{k+1}$ lines to the standard output.

Successive lines should describe successive moves.

Each line should contain $k+1$ integers, in increasing order,separated by single spaces, that denote the numbers of blocks to be removed in the move.

## 样例

### 样例输入 #1
```
12 2
ccbcbbbbbbcb

```
### 样例输出 #1
```
1 8 12
2 6 7
3 4 5
9 10 11

```
## 提示

有n块砖，其中白色是黑色的k倍，求一个消除序列，满足以下条件：

每次消除k+1个砖，其中k块白色，1块黑色，并且这k+1块砖从开始到结束，中间不能路过已经消除过的砖

数据保证有解


返回`TAT1`：同一个位置输出$2$次

返回`TAT2`：输出的$k+1$个位置不满足白色是黑色$k$倍

返回`TAT3`：未按照升序输出或者中间路过已经消除的砖

SPJ provided by @colazcy


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
title: "[NOIP 2017 提高组] 时间复杂度"
layout: "post"
diff: 普及+/提高
pid: P3952
tag: ['模拟', '字符串', '2017', 'NOIP 提高组', '栈']
---
# [NOIP 2017 提高组] 时间复杂度
## 题目背景

NOIP2017 提高组 D1T2
## 题目描述

小明正在学习一种新的编程语言 A++，刚学会循环语句的他激动地写了好多程序并 给出了他自己算出的时间复杂度，可他的编程老师实在不想一个一个检查小明的程序， 于是你的机会来啦！下面请你编写程序来判断小明对他的每个程序给出的时间复杂度是否正确。

A++语言的循环结构如下：

 
```cpp
F i x y
    循环体
E
```
 
 
其中`F i x y`表示新建变量 $i$（变量 $i$ 不可与未被销毁的变量重名）并初始化为 $x$， 然后判断 $i$ 和 $y$ 的大小关系，若 $i$ 小于等于 $y$ 则进入循环，否则不进入。每次循环结束后 $i$ 都会被修改成 $i +1$，一旦 $i$ 大于 $y$ 终止循环。

$x$ 和 $y$ 可以是正整数（$x$ 和 $y$ 的大小关系不定）或变量 $n$。$n$ 是一个表示数据规模的变量，在时间复杂度计算中需保留该变量而不能将其视为常数，该数远大于 $100$。

`E` 表示循环体结束。循环体结束时，这个循环体新建的变量也被销毁。

注：本题中为了书写方便，在描述复杂度时，使用大写英文字母 $\operatorname O$ 表示通常意义下 $Θ$ 的概念。

## 输入格式

输入文件第一行一个正整数 $t$，表示有 $t$（$t \le 10$）个程序需要计算时间复杂度。 每个程序我们只需抽取其中 `F i x y` 和 `E` 即可计算时间复杂度。注意：循环结构允许嵌套。

接下来每个程序的第一行包含一个正整数 $L$ 和一个字符串，$L$ 代表程序行数，字符串表示这个程序的复杂度，`O(1)` 表示常数复杂度，`O(n^w)` 表示复杂度为 $n^w$，其中 $w$ 是一个小于 $100$ 的正整数，输入保证复杂度只有 `O(1)` 和 `O(n^w)` 两种类型。

接下来 $L$ 行代表程序中循环结构中的`F i x y`或者 `E`。 程序行若以`F`开头，表示进入一个循环，之后有空格分离的三个字符（串）`i x y`， 其中 $i$ 是一个小写字母（保证不为$n$），表示新建的变量名，$x$ 和 $y$ 可能是正整数或 $n$ ，已知若为正整数则一定小于 $100$。

程序行若以`E`开头，则表示循环体结束。

## 输出格式

输出文件共 $t$ 行，对应输入的 $t$ 个程序，每行输出 `Yes` 或 `No` 或者 `ERR`，若程序实际复杂度与输入给出的复杂度一致则输出 `Yes`，不一致则输出 `No`，若程序有语法错误（其中语法错误只有: ① `F` 和 `E` 不匹配 ②新建的变量与已经存在但未被销毁的变量重复两种情况），则输出 `ERR`。

注意：即使在程序不会执行的循环体中出现了语法错误也会编译错误，要输出 `ERR`。

## 样例

### 样例输入 #1
```
8
2 O(1)
F i 1 1
E
2 O(n^1)
F x 1 n
E
1 O(1)
F x 1 n
4 O(n^2)
F x 5 n
F y 10 n
E
E
4 O(n^2)
F x 9 n
E
F y 2 n
E
4 O(n^1)
F x 9 n
F y n 4
E
E
4 O(1)
F y n 4
F x 9 n
E
E
4 O(n^2)
F x 1 n
F x 1 10
E
E
```
### 样例输出 #1
```
Yes
Yes
ERR
Yes
No
Yes
Yes
ERR
```
## 提示

【输入输出样例解释 $1$】

第一个程序 $i$ 从 $1$ 到 $1$ 是常数复杂度。

第二个程序 $x$ 从 $1$ 到 $n$ 是 $n$ 的一次方的复杂度。

第三个程序有一个 `F` 开启循环却没有 `E` 结束，语法错误。

第四个程序二重循环，$n$ 的平方的复杂度。

第五个程序两个一重循环，$n$ 的一次方的复杂度。

第六个程序第一重循环正常，但第二重循环开始即终止（因为 $n$ 远大于 $100$，$100$ 大于 $4$）。

第七个程序第一重循环无法进入，故为常数复杂度。

第八个程序第二重循环中的变量 $x$ 与第一重循环中的变量重复，出现语法错误②，输出 `ERR`。

【数据规模与约定】

对于 $30\%$ 的数据：不存在语法错误，数据保证小明给出的每个程序的前 $L/2$ 行一定为以 `F` 开头的语句，第 $L/2+1$ 行至第 $L$ 行一定为以 `E` 开头的语句，$L  \le 10$，若 $x$、$y$ 均为整数，$x$ 一定小于 $y$，且只有 $y$ 有可能为 $n$。

对于 $50\%$ 的数据：不存在语法错误，$L  \le 100$，且若 $x$、$y$ 均为整数，$x$ 一定小于 $y$， 且只有 $y$ 有可能为 $n$。

对于 $70\%$ 的数据：不存在语法错误，$L  \le 100$。

对于 $100\%$ 的数据：$L  \le 100$。


---
如果需要Hack请私信@zhouyonglong或发讨论，提供数据和能Hack掉的本题的AC记录。


---

---
title: "玉蟾宫"
layout: "post"
diff: 普及+/提高
pid: P4147
tag: ['动态规划 DP', '枚举', '单调栈']
---
# 玉蟾宫
## 题目背景

有一天，小猫 rainbow 和 freda 来到了湘西张家界的天门山玉蟾宫，玉蟾宫宫主蓝兔盛情地款待了它们，并赐予它们一片土地。

## 题目描述

这片土地被分成 $N\times M$ 个格子，每个格子里写着 'R' 或者 'F'，R 代表这块土地被赐予了 rainbow，F 代表这块土地被赐予了 freda。

现在 freda 要在这里卖萌。。。它要找一块矩形土地，要求这片土地都标着 'F' 并且面积最大。

但是 rainbow 和 freda 的 OI 水平都弱爆了，找不出这块土地，而蓝兔也想看 freda 卖萌（她显然是不会编程的……），所以它们决定，如果你找到的土地面积为 $S$，它们每人给你 $S$ 两银子。

## 输入格式

第一行两个整数 $N$，$M$，表示矩形土地有 $N$ 行 $M$ 列。

接下来 $N$ 行，每行 $M$ 个用空格隔开的字符 'F' 或 'R'，描述了矩形土地。

## 输出格式

输出一个整数，表示你能得到多少银子，即 ($3\times \text{最大 'F' 矩形土地面积}$) 的值。

## 样例

### 样例输入 #1
```
5 6 
R F F F F F 
F F F F F F 
R R R F F F 
F F F F F F 
F F F F F F
```
### 样例输出 #1
```
45
```
## 提示

对于 $50\%$ 的数据，$1 \leq N, M \leq 200$。  
对于 $100\%$ 的数据，$1 \leq N, M \leq 1000$。


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
title: "Portal2"
layout: "post"
diff: 普及+/提高
pid: P4940
tag: ['O2优化', '枚举', '栈']
---
# Portal2
## 题目背景

某地`ENLIGHTENED`的`XM`研究所正在研究`Portal`的处理法则，想要揭示`XM能量`的来源以及应用`XM能量`。`ENLIGHTENED`的首席科学家`Jacks`发现其能量的运算法则以及运算方法，但是方法十分复杂，仅靠人手工计算是很难算出答案的，所以它需要你协助他完成计算。
## 题目描述

`Portal`计算`XM能量`是通过个$2$个栈（$0$号栈，$1$号栈）实现的，它把对`XM`能量的操作如下

$PUSH$ $X$ $NUM$

把$NUM$加入到X号栈的栈顶。 

$POP$ $X$

把$X$号栈的栈顶元素**删除**。

$ADD$ $X$

**取出**$0$号栈和$1$号栈的元素各一个，并且把它的和放入$X$号栈。

$SUB$ $X$

**取出**$0$号栈和$1$号栈的元素各一个，并且把它的差的绝对值放入$X$号栈。
 
$DEL$ $X$

**清空**$X$号栈中所有元素不管栈是否为空。 

$MOVE$ $X$ $Y$ 

循环操直到$Y$号栈为空，把$Y$号栈的栈顶元素加入到$X$号栈，删除$Y$号栈的栈顶元素。 

**数据保证X和Y不相同**

$SWAP$

将两个栈的所有元素调换。

$END$

代表命令结束，并且分两行分别输出0号栈和1号栈由栈顶到栈底的元素的值，若栈内无元素，输出`NONE`。数据保证指令以`END`结束且仅有一个`END`，并且也需要输出`SUCCESS`。

~~$AKNOI$~~

~~等为无效操作，**无效操作后不接数字**。~~

**更正不会有类似无效操作**

对于每一行指令，若当前指令成功执行输出`SUCCESS`，若**取出**或**删除**元素时栈内为空或者没有对应指令输出`UNSUCCESS`并且不执行该行指令。
## 输入格式

输入若干行指令，以`END`指令结束
## 输出格式

对于每一次操作，都要对应输出`SUCCESS`或者`UNSUCCESS`，对于`END`根据指令描述输出栈内元素。
## 样例

### 样例输入 #1
```
PUSH 0 10
PUSH 0 20
PUSH 0 30
PUSH 0 40
PUSH 1 50
PUSH 1 60
ADD 0
ADD 0
ADD 0
END
```
### 样例输出 #1
```
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
UNSUCCESS
SUCCESS
150 30 20 10
NONE
```
### 样例输入 #2
```
PUSH 0 10
PUSH 0 20
PUSH 0 30
PUSH 0 40
PUSH 1 50
PUSH 1 60
MOVE 0 1
END
```
### 样例输出 #2
```
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
50 60 40 30 20 10
NONE
```
## 提示

对于$20\%$的数据 数据保证不会出现`MOVE/SWAP`操作，$命令总数 \leq 100$

对于$40\%$的数据 $命令总数 \leq 1000$

对于$60\%$的数据 数据保证`MOVE/SWAP`的操作次数不会超过$10000$次，$命令总数 \leq 10^5$

对于$100\%$的数据 $0 \leq X,Y \leq 1,命令总数 \leq 10^6$ 

**数据保证无论任何情况，栈中元素的值$X$满足$0 \leq x \leq 2^{63}-1​$**

[题目创意来源OIERBBS](https://www.oierbbs.cn)


---

---
title: "修改"
layout: "post"
diff: 普及+/提高
pid: P6155
tag: ['贪心', '2020', '栈']
---
# 修改
## 题目描述

给定一个长度为 $n$ 的整数序列 $a_i$，再给定一个长度为 $n$ 的整数序列 $b_i$。

你可以进行一些修改，每次你可以将一个 $a_i$ 增加 $1$，花费为 $b_i$，你需要使所有的 $a_i$ 不相等，且同时满足花费最少。

但 zbw 认为太过简单，于是他规定，你可以在修改前进行**无限**次如下操作：交换 $b_i,b_j(1 \leq i,j \leq n)$。

求最小的花费。

**由于答案可能很大，请输出答案对  $2^{64}$ 取模后的值。**



## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个整数，第 $i$ 个数表示 $a_i$。

第三行 $n$ 个整数，第 $i$ 个数表示 $b_i$。
## 输出格式

输出一行一个整数，表示答案对 $2^{64}$ 取模的值。
## 样例

### 样例输入 #1
```
3
3 3 3
1 2 3
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3
3 3 4
3 2 1
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
3
3 4 5
2 1 3
```
### 样例输出 #3
```
0
```
## 提示

样例 $1$：不改变 $b$，让 $a_1$ 增加 $2$，$a_2$ 增加 $1$，总花费为 $4$。

样例 $2$：交换 $b_1,b_3$，让 $a_1$ 增加 $2$，总花费为 $2$。

样例 $3$：不做任何改变。

**本题输入量较大，请使用读入优化。**



| 测试点 |$n$  |$a_i$  |特殊性质|
| :----------: | :----------: | :----------: |  :----------: |
| $1,2$ |$\leq10$  |$\leq10^9$  |无 |
| $3\sim6$ |$\leq10^3$  |$\leq10^9$  |无| 
| $7\sim10$ |$\leq10^6$  |$\leq10^6$  | 无|
| $11\sim14$ |$\leq10^6$  |$\leq10^9$  |所有 $b_i$ 相等 |
| $15\sim20$ |$\leq10^6$  |$\leq10^9$  |无|

对于所有数据 $1 \leq n \leq 10^6$，$1\leq a_i,b_i\leq10^9$。


---

---
title: "[USACO10OPEN] Time Travel S"
layout: "post"
diff: 普及+/提高
pid: P6182
tag: ['2010', 'USACO', '可持久化', '栈']
---
# [USACO10OPEN] Time Travel S
## 题目描述

Farmer John 买了台时光机，这使得他可以方便地管理自己的奶牛群。

他现在有 $N$ 个操作（$1 \leq N \leq 8 \times 10^4$），每次操作仅可能是如下三种之一：

1. `a x`：添加一头编号为 $x$ 的奶牛（$1 \leq x \leq 10^6$）。
2. `s`：卖掉最近添加的奶牛（保证此时至少有一头奶牛）。
3. `t x`：回到**第 $x$ 次操作前**的状态（保证第 $x$ 次操作存在）。

你需要在 FJ 执行每次操作后输出他拥有的最新的奶牛的编号。特别地，如果没有奶牛，输出 $-1$。
## 输入格式

第一行一个整数 $N$。

接下来 $N$ 行，每行描述一次操作。
## 输出格式

第 $i$ 行输出第 $i$ 次操作后 FJ 拥有的最新的奶牛的编号。特别地，如果没有奶牛，输出 $-1$。
## 样例

### 样例输入 #1
```
12
a 5
a 3
a 7
s
t 2
a 2
t 4
a 4
s
t 7
s
s
```
### 样例输出 #1
```
5
3
7
3
5
2
7
4
7
2
5
-1
```
## 提示

下面是样例解释，其中拥有的奶牛已经按添加顺序排好。

| 操作编号 | 操作  | 拥有的奶牛 | 输出 |
| -------- | ----- | ---------- | ---- |
| 1        | `a 5` | 5          | 5    |
| 2        | `a 3` | 5,3        | 3    |
| 3        | `a 7` | 5,3,7      | 7    |
| 4        | `s`   | 5,3        | 3    |
| 5        | `t 2` | 5          | 5    |
| 6        | `a 2` | 5,2        | 2    |
| 7        | `t 4` | 5,3,7      | 7    |
| 8        | `a 4` | 5,3,7,4    | 4    |
| 9        | `s`   | 5,3,7      | 7    |
| 10       | `t 7` | 5,2        | 2    |
| 11       | `s`   | 5          | 5    |
| 12       | `s`   | /          | -1   |


---

---
title: "[COCI 2010/2011 #3] DIFERENCIJA"
layout: "post"
diff: 普及+/提高
pid: P6503
tag: ['2010', '单调队列', 'O2优化', '栈', 'COCI（克罗地亚）']
---
# [COCI 2010/2011 #3] DIFERENCIJA
## 题目描述

给出一个长度为 $n$ 的序列 $a_i$，求出下列式子的值：

$$\sum_{i=1}^{n} \sum_{j=i}^{n} (\max_{i\le k\le j} a_k-\min_{i\le k\le j} a_k)$$



即定义一个子序列的权值为序列内最大值与最小值的差。求出所有连续子序列的权值和。


## 输入格式

输入第一行一个整数 $n$，表示序列的长度。

接下来的 $n$ 行，每行一个整数 $a_i$，描述这个序列。
## 输出格式

输出一行一个整数，表示式子的答案。
## 样例

### 样例输入 #1
```
3
1
2
3
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
4
7
5
7
5
```
### 样例输出 #2
```
12
```
### 样例输入 #3
```
4
3
1
7
2
```
### 样例输出 #3
```
31
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le n\le 3\times 10^5$，$1\le a_i\le 10^8$。

#### 说明

**题目译自 [COCI2010-2011](https://hsin.hr/coci/archive/2010_2011/) [CONTEST #3](https://hsin.hr/coci/archive/2010_2011/contest3_tasks.pdf) *T5 DIFERENCIJA***。


---

---
title: "奶牛排队"
layout: "post"
diff: 普及+/提高
pid: P6510
tag: ['单调队列', 'NOI 导刊', 'O2优化', '分治', '栈']
---
# 奶牛排队
## 题目描述

奶牛在熊大妈的带领下排成了一条直队。

显然，不同的奶牛身高不一定相同……

现在，奶牛们想知道，如果找出一些连续的奶牛，要求最左边的奶牛 $A$ 是最矮的，最右边的 $B$ 是最高的，且 $B$ 高于 $A$ 奶牛。中间如果存在奶牛，则身高不能和 $A,B$ 奶牛相同。问这样的奶牛最多会有多少头？

从左到右给出奶牛的身高，请告诉它们符合条件的最多的奶牛数（答案可能是 $0,2$，但不会是 $1$）。
## 输入格式

第一行一个正整数 $N$，表示奶牛的头数。

接下来 $N$ 行，每行一个正整数，从上到下表示从左到右奶牛的身高 $h_i$。

## 输出格式

一行一个整数，表示最多奶牛数。
## 样例

### 样例输入 #1
```
5
1
2
3
4
1
```
### 样例输出 #1
```
4
```
## 提示

#### 样例解释

取第 $1$ 头到第 $4$ 头奶牛，满足条件且为最多。

#### 数据范围

对于全部的数据，满足 $2 \le N \le 10^5$，$1 \le h_i <2^{31}$。


---

---
title: "[COCI 2015/2016 #3] SLON"
layout: "post"
diff: 普及+/提高
pid: P7229
tag: ['数学', '2015', '数论', '栈', 'COCI（克罗地亚）']
---
# [COCI 2015/2016 #3] SLON
## 题目描述

小 Q 在学校里非常调皮。

他上课时总是很无聊，他总是把课堂弄得一团糟。老师希望让他冷静下来，所以给他出了一道很难的数学题。

老师给小 Q 一个算术表达式 $A$、整数 $P$ 和 $M$，小 Q 要回答的是以下问题：

> 求最小非负整数  $x$，使含  $x$ 的表达式  $A$ 除以  $M$ 余数等于  $P$。

注意每一个运算符均会连接两个数或是变量。每一个乘号都不会省略且不允许连接两个含有 $x$ 的表达式。括号均合法，可能存在括号内容仅有一个数或变量的情况。

题目保证原表达式化简后一定能写成一个形如 $kx+b$ 的一元一次式。
## 输入格式

第一行，一行表达式 $A$。

第二行，两个正整数 $P, M$。
## 输出格式

第一行，一个正整数 $x$。
## 样例

### 样例输入 #1
```
5+3+x
9 10

```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
20+3+x
0 5

```
### 样例输出 #2
```
2
```
## 提示

#### 数据规模及约定

对于 $100\%$ 的数据：
- 令 $|A|$ 为字符串 $A$ 的长度，那么 $1 \le |A| \le 10 ^ 5$。
- 表达式 $A$ 中仅会有 $\texttt{+}$，$\texttt{-}$，$\texttt{*}$，$\texttt{(}$，$\texttt{)}$，$\texttt{x}$，和 $\texttt{0}$ $\sim$ $\texttt{9}$。
- $0 \le P \le M - 1$。
- $1 \le M \le 10 ^ 6$。

#### 说明
翻译自 [COCI 2015-2016 #3 D SLON](https://hsin.hr/coci/archive/2015_2016/contest3_tasks.pdf)，满分 120。


---

---
title: "[CSP-J 2022] 逻辑表达式"
layout: "post"
diff: 普及+/提高
pid: P8815
tag: ['模拟', '2022', 'O2优化', '栈', 'CSP-J 入门级']
---
# [CSP-J 2022] 逻辑表达式
## 题目描述

逻辑表达式是计算机科学中的重要概念和工具，包含逻辑值、逻辑运算、逻辑运算优先级等内容。

在一个逻辑表达式中，元素的值只有两种可能：$0$（表示假）和 $1$（表示真）。元素之间有多种可能的逻辑运算，本题中只需考虑如下两种：“与”（符号为 `&`）和“或”（符号为 `|`）。其运算规则如下：

$0 \mathbin{\&} 0 = 0 \mathbin{\&} 1 = 1 \mathbin{\&} 0 = 0$，$1 \mathbin{\&} 1 = 1$；  
$0 \mathbin{|} 0 = 0$，$0 \mathbin{|} 1 = 1 \mathbin{|} 0 = 1 \mathbin{|} 1 = 1$。

在一个逻辑表达式中还可能有括号。规定在运算时，括号内的部分先运算；两种运算并列时，`&` 运算优先于 `|` 运算；同种运算并列时，从左向右运算。

比如，表达式 `0|1&0` 的运算顺序等同于 `0|(1&0)`；表达式 `0&1&0|1` 的运算顺序等同于 `((0&1)&0)|1`。

此外，在 C++ 等语言的有些编译器中，对逻辑表达式的计算会采用一种“短路”的策略：在形如 `a&b` 的逻辑表达式中，会先计算 `a` 部分的值，如果 $a = 0$，那么整个逻辑表达式的值就一定为 $0$，故无需再计算 `b` 部分的值；同理，在形如 `a|b` 的逻辑表达式中，会先计算 `a` 部分的值，如果 $a = 1$，那么整个逻辑表达式的值就一定为 $1$，无需再计算 `b` 部分的值。

现在给你一个逻辑表达式，你需要计算出它的值，并且统计出在计算过程中，两种类型的“短路”各出现了多少次。需要注意的是，如果某处“短路”包含在更外层被“短路”的部分内则不被统计，如表达式 `1|(0&1)` 中，尽管 `0&1` 是一处“短路”，但由于外层的 `1|(0&1)` 本身就是一处“短路”，无需再计算 `0&1` 部分的值，因此不应当把这里的 `0&1` 计入一处“短路”。
## 输入格式

输入共一行，一个非空字符串 $s$ 表示待计算的逻辑表达式。
## 输出格式

输出共两行，第一行输出一个字符 `0` 或 `1`，表示这个逻辑表达式的值；第二行输出两个非负整数，分别表示计算上述逻辑表达式的过程中，形如 `a&b` 和 `a|b` 的“短路”各出现了多少次。
## 样例

### 样例输入 #1
```
0&(1|0)|(1|1|1&0)

```
### 样例输出 #1
```
1
1 2

```
### 样例输入 #2
```
(0|1&0|1|1|(1|1))&(0&1&(1|0)|0|1|0)&0

```
### 样例输出 #2
```
0
2 3

```
## 提示

**【样例解释 \#1】**

该逻辑表达式的计算过程如下，每一行的注释表示上一行计算的过程：

```plain
0&(1|0)|(1|1|1&0)
=(0&(1|0))|((1|1)|(1&0)) //用括号标明计算顺序
=0|((1|1)|(1&0))   //先计算最左侧的 &，是一次形如 a&b 的“短路”
=0|(1|(1&0))       //再计算中间的 |，是一次形如 a|b 的“短路”
=0|1               //再计算中间的 |，是一次形如 a|b 的“短路”
=1
```

**【样例 \#3】**

见附件中的 `expr/expr3.in` 与 `expr/expr3.ans`。

**【样例 \#4】**

见附件中的 `expr/expr4.in` 与 `expr/expr4.ans`。

**【数据范围】**

设 $\lvert s \rvert$ 为字符串 $s$ 的长度。

对于所有数据，$1 \le \lvert s \rvert \le {10}^6$。保证 $s$ 中仅含有字符 `0`、`1`、`&`、`|`、`(`、`)` 且是一个符合规范的逻辑表达式。保证输入字符串的开头、中间和结尾均无额外的空格。保证 $s$
中没有重复的括号嵌套（即没有形如 `((a))` 形式的子串，其中 `a` 是符合规范的逻辑表
达式）。

| 测试点编号 | $\lvert s \rvert \le$ | 特殊条件 |
|:-:|:-:|:-:|
| $1 \sim 2$ | $3$ | 无 |
| $3 \sim 4$ | $5$ | 无 |
| $5$ | $2000$ | 1 |
| $6$ | $2000$ | 2 |
| $7$ | $2000$ | 3 |
| $8 \sim 10$ | $2000$ | 无 |
| $11 \sim 12$ | ${10}^6$ | 1 |
| $13 \sim 14$ | ${10}^6$ | 2 |
| $15 \sim 17$ | ${10}^6$ | 3 |
| $18 \sim 20$ | ${10}^6$ | 无 |

其中：  
特殊性质 1 为：保证 $s$ 中没有字符 `&`。  
特殊性质 2 为：保证 $s$ 中没有字符 `|`。  
特殊性质 3 为：保证 $s$ 中没有字符 `(` 和 `)`。

**【提示】**

以下给出一个“符合规范的逻辑表达式”的形式化定义：

- 字符串 `0` 和 `1` 是符合规范的；
- 如果字符串 `s` 是符合规范的，且 `s` 不是形如 `(t)` 的字符串（其中 `t` 是符合规范的），那么字符串 `(s)` 也是符合规范的；
- 如果字符串 `a` 和 `b` 均是符合规范的，那么字符串 `a&b`、`a|b` 均是符合规范的；
- 所有符合规范的逻辑表达式均可由以上方法生成。


---

---
title: "「TAOI-1」Apollo"
layout: "post"
diff: 普及+/提高
pid: P9218
tag: ['O2优化', '深度优先搜索 DFS', '最近公共祖先 LCA', '进制', '字典树 Trie', '单调栈']
---
# 「TAOI-1」Apollo
## 题目背景

Execution.

这题原来叫 `std::cout << std::fixed << std::setprecision(1) << 6.5 << '\n';`。

[被当事人删掉的图片.jpg]

**【Upd 2023/04/15 21:42】添加了一组 Hack 数据位于 Subtask 2，#13。现在所有赛时的 $\bm{50}$ 分提交理论上均只能获得 $\bm{30}$ 分。**
## 题目描述

给出 $n$ 个十进制小数 $a_1 \dots a_n$。

对于一个 **数** $a$，定义其精度 $f(a)$ 表示最小的非负整数 $k$ 使得 $10^k\times a$ 为整数；对于整数 $a$，定义 $f(a) = 0$。对于两个十进制小数 $a, b$，定义 $g(a, b)$ 为对于所有 **数** $c \in [\min(a,b), \max(a,b)]$ 的 $f(c)$ 的最小值。

对于所有 $1 \leq i \leq n$，你需要求出 $\sum\limits_{j=1}^ng(a_i, a_j)$ 的值并输出。

定义十进制小数是一个含有整数部分和小数部分的数，其小数部分不为 $0$。之所以描述得这么愚蠢是因为保证输入的每个数都有小数点，但是好像无论什么写法都会有人提出不满，真是抱歉了。~~所以还是得看看被当事人删掉的图片。所以我在这里写闲话有人看得到吗。~~
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，每行一个十进制小数 $a_i$。
## 输出格式

$n$ 行，每行一个整数，分别表示 $i = 1 \dots n$ 对应的答案。
## 样例

### 样例输入 #1
```
5
11.4514
11.4778
11.1338
11.1236
11.4789
```
### 样例输出 #1
```
10
11
9
9
11
```
### 样例输入 #2
```
8
1.1145
1.114
1.1145
1.514
1.19198
1.1154
1.114
1.1145
```
### 样例输出 #2
```
24
21
24
10
18
22
21
24
```
## 提示

### 数据范围

**本题采用捆绑测试。**

令 $\sum\limits_{i=1}^n f(a_i) = t$。

- Subtask 1（15 points）：$a_i \leq 10$，$n \leq 5$，$t \leq 10$。
- Subtask 2（15 points）：$a_i \leq 10$，$n \leq 100$，$t \leq 1000$。
- Subtask 3（20 points）：$n \leq 1722$。
- Subtask 4（15 points）：$a_i \leq 1$。
- Subtask 5（35 points）：无特殊限制。

对于所有数据，$0 \lt a_i \lt 10^9$，$1 \leq n \leq 10^5$，$1 \leq t \leq 3 \times 10^6$，**保证 $\bm{a_i}$ 没有后导 [$\color{black}\bm 0$](https://cdn.luogu.com.cn/upload/image_hosting/pg66fm1z.png)，不保证 $\bm{a_i}$ 互不相同**。

### 样例解释

以 $i = 1$ 为例：

+ $j = 1$：取 $c = 11.4514$，$f(c) = 4$；
+ $j = 2$：取 $c = 11.46$，$f(c) = 2$；
+ $j = 3$：取 $c = 11.2$，$f(c) = 1$；
+ $j = 4$：取 $c = 11.3$，$f(c) = 1$；
+ $j = 5$：取 $c = 11.47$，$f(c) = 2$。

故 $\sum\limits_{j=1}^n g(a_1, a_j) = 4 + 2 + 1 + 1 + 2 = 10$。对于同一个 $j$，上文给出的所有 $c$，都可能有其它的不同的 $c$ 满足 $f(c)$ 同样最小。


---

---
title: "[ROI 2018]  Decryption"
layout: "post"
diff: 普及+/提高
pid: P9290
tag: ['2018', '单调栈', 'ROI（俄罗斯）']
---
# [ROI 2018]  Decryption
## 题目背景

译自 [ROI 2018 Day2](https://neerc.ifmo.ru/school/archive/2017-2018.html) T1. [Расшифровка](https://neerc.ifmo.ru/school/archive/2017-2018/ru-olymp-roi-2018-day2.pdf) ([Decryption](https://codeforces.com/gym/102154/problem/B))。 
## 题目描述

研究表明，汉字的顺序并不一定能影响阅读。科学家们对数列进行了类似的研究。

给一个正整数数列，若数列首项为数列中所有数的最小值，末项为数列中的最大值，则我们称这是个正确的数列。例如，序列 $[1, 3, 2, 4]$ 和 $[1, 2, 1, 2]$ 是正确的，但序列 
$[1, 3, 2]$ 不是。

给出长度为 n 的序列 $[a_1, a_2, \ldots, a_n]$。对于该序列的某个片段 $[a_l, a_{l+1}, \ldots, a_r]$, 若该片段的首项为该片段中的最小值，末项为该片段中的最大值，则我们称这是个正确的片段。

对于给定的序列，请求出该序列至少需要被分成多少段，才能使得每个片段均为正确的片段。序列 $[2, 3, 1, 1, 5, 1]$ 可以分为三个正确的段：$[2, 3]$ 和 $[1, 1, 5]$ 和 $[1]$。

需要编写一个程序，该程序按给定的顺序确定可以划分的最小正确段数。
## 输入格式

第一行一个整数 $n$。

接下来一行 $n$ 个数，分别为 $a_1,a_2,\ldots,a_n$。
## 输出格式

输出可以划分的最小正确段数。
## 样例

### 样例输入 #1
```
5
5 4 3 2 1
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
4
1 3 2 4
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
6
2 3 1 1 5 1
```
### 样例输出 #3
```
3
```
## 提示

对于 $30\%$ 的数据，$1 \leq n \leq 500$。

对于 $60\%$ 的数据，$1 \leq n \leq 5000$。

对于所有数据，$1 \leq n \leq3 \times 10^5$，$1\leq a_i \leq 10^9$。


---

