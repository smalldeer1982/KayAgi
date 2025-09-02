---
title: "[常州市赛 2025] 压缩"
layout: "post"
diff: 普及+/提高
pid: B4392
tag: ['字符串', '2025', '江苏', '枚举', '科创活动', '小学活动']
---
# [常州市赛 2025] 压缩
## 题目背景

搬运自 <http://czoj.com.cn/p/1409>。数据为民间数据。
## 题目描述

小 Y 开发了一种名为“别重复”的新型数据压缩策略。“别重复”作用于字符串，若字符串中存在两个连续相同的子串，则会删除其中一个。例如，在字符串 $\tt alfalfaseeds$ 中，“别重复”可删除 $\tt seeds$ 中的一个 $\tt e$和 $\tt alfalfa$ 中的一个 $\tt lfa$，得到 $\tt alfaseds$。 “别重复”还能利用先前的删除效果，例如在 $\tt seventeenth\ baggage$ 中，先删除重复的 $\tt e$ 和 $\tt g$ 得到 $\tt sevententh\ bagage$，再删除重复的 $\tt ent$ 和 $\tt ag$，最终得到 $\tt seventh\ bage$。

当存在多个重复子串可删除时，最优的“别重复”会选择使最终字符串最短的方式。例如，在 $\tt ABBCDCABCDCD$ 中，优先删除开头的 $\tt B$ 再删除 $\tt ABCDC$ 可压缩为 $\tt ABCD$，而若先删除末尾的 $\tt CD$ 再删除 $\tt B$ 则最终只能得到 $\tt ABCDCABCD$。最优的“别重复”会选择先删除 $\tt B$ 再删除 $\tt ABCDC$ 的方式。

小 Y 要求为带通配符的二进制字符串（仅含 $\tt 0,1,\#$，$\tt\#$ 为通配符）实现最优的“别重复”算法。你需要在进行“别重复”压缩算法前为通配符进行赋值，值为 $\tt 0$ 或者 $\tt 1$，使得赋值之后的二进制字符串通过应用最优的“别重复”能得到最短的字符串。
## 输入格式

一行一个带通配符的二进制字符串。
## 输出格式

一行一个字符串表示应用最优的“别重复”能得到的最短字符串。数据保证应用最优的“别重复”能得到的最短字符串有且只有一种唯一情况。
## 样例

### 样例输入 #1
```
111#
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
10#
```
### 样例输出 #2
```
10
```
### 样例输入 #3
```
10##1
```
### 样例输出 #3
```
101
```
## 提示

本任务共有 $10$ 个数据。

对于全部数据：保证字符串长度不超过 $10^5$，数据保证应用最优的“别重复”能得到的最短字符串有且只有一种唯一情况。

|测试点编号|特殊性质|
|:-:|:-:|
|$1\sim2$|字符串长度不超过 $3$|
|$3\sim4$|字符串中不包含 $\tt0$|
|$5\sim8$|字符串中不包含 $\tt\#$|
|$9\sim10$|无|


---

---
title: "[NOIP 2002 提高组] 字串变换"
layout: "post"
diff: 普及+/提高
pid: P1032
tag: ['字符串', '搜索', '2002', 'NOIP 提高组', '广度优先搜索 BFS', '剪枝', '折半搜索 meet in the middle']
---
# [NOIP 2002 提高组] 字串变换
## 题目背景

本题不保证存在靠谱的多项式复杂度的做法。测试数据非常的水，各种做法都可以通过，不代表算法正确。因此本题题目和数据仅供参考。

本题为搜索题，本题不接受 hack 数据。[关于此类题目的详细内容](https://www.luogu.com.cn/paste/isdgwj5l)
## 题目描述

已知有两个字串 $A,B$ 及一组字串变换的规则（至多 $6$ 个规则），形如：

- $A_1\to B_1$。
- $A_2\to B_2$。

规则的含义为：在 $A$ 中的子串 $A_1$ 可以变换为 $ B_1$，$A_2$ 可以变换为 $B_2\cdots$。

例如：$A=\texttt{abcd}$，$B＝\texttt{xyz}$，

变换规则为：

- $\texttt{abc}\rightarrow\texttt{xu}$，$\texttt{ud}\rightarrow\texttt{y}$，$\texttt{y}\rightarrow\texttt{yz}$。

则此时，$A$ 可以经过一系列的变换变为 $B$，其变换的过程为：

- $\texttt{abcd}\rightarrow\texttt{xud}\rightarrow\texttt{xy}\rightarrow\texttt{xyz}$。

共进行了 $3$ 次变换，使得 $A$ 变换为 $B$。

## 输入格式

第一行有两个字符串 $A,B$。

接下来若干行，每行有两个字符串 $A_i,B_i$，表示一条变换规则。

## 输出格式

若在 $10$ 步（包含 $10$ 步）以内能将 $A$ 变换为 $B$，则输出最少的变换步数；否则输出 `NO ANSWER!`。

## 样例

### 样例输入 #1
```
abcd xyz
abc xu
ud y
y yz

```
### 样例输出 #1
```
3

```
## 提示

对于 $100\%$ 数据，保证所有字符串长度的上限为 $20$。

**【题目来源】**

NOIP 2002 提高组第二题


---

---
title: "文件压缩"
layout: "post"
diff: 普及+/提高
pid: P1124
tag: ['模拟', '字符串']
---
# 文件压缩
## 题目背景

提高文件的压缩率一直是人们追求的目标。近几年有人提出了这样一种算法，它虽然只是单纯地对文件进行重排，本身并不压缩文件，但是经这种算法调整后的文件在大多数情况下都能获得比原来更大的压缩率。

## 题目描述

该算法具体如下：对一个长度为 $n$ 的字符串 $S$，首先根据它构造 $n$ 个字符串，其中第 $i$ 个字符串由将 $S$ 的前 $i-1$ 个字符置于末尾得到。然后把这 $n$ 个字符串按照首字符从小到大排序，如果两个字符串的首字符相等，则按照它们**在 $S$ 中的位置**从小到大排序。排序后的字符串的尾字符可以组成一个新的字符串 $S'$ ，它的长度也是 $n$，并且包含了 $S$ 中的每一个字符。最后输出 $S'$ 以及 $S$ 的首字符在 $S'$ 中的位置 $p$。

举例：$S$ 是 `example`

1. 构造 $n$ 个字符串。

```plain
example
xamplee
ampleex
mpleexa
pleexam
leexamp
eexampl
```

2. 将字符串排序。

```plain
ampleex
example
eexampl
leexamp
mpleexa
pleexam
xamplee
```
3. 压缩结果。

$S' = \texttt{xelpame}$，$p = 7$

由于英语单词构造的特殊性，某些字母对出现的频率很高，因此在 $S'$ 中相同的字母有很大几率排在一起，从而提高 $S'$ 的压缩率。虽然这种算法利用了英语单词的特性，然而在实践的过程中，人们发现它几乎适用于所有的文件压缩。

请你编一个程序，读入 $S'$ 和 $p$，输出字符串 $S$。

保证 $S$ 仅含小写字母（所以输入的 $S'$ 也仅含小写字母）。
## 输入格式

共三行。

第一行是一个整数 $n$（$1 \le n \le 10000$），代表 $S'$ 的长度。

第二行是字符串 $S'$。

第三行是整数 $p$。
## 输出格式

一行，$S$。

## 样例

### 样例输入 #1
```
7
xelpame
7

```
### 样例输出 #1
```
example

```


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
title: "[蓝桥杯 2024 省 B 第二场] 前缀总分"
layout: "post"
diff: 普及+/提高
pid: P12124
tag: ['字符串', '2024', '蓝桥杯省赛']
---
# [蓝桥杯 2024 省 B 第二场] 前缀总分
## 题目描述

给定 $n$ 个由小写英文字母组成的字符串 $s_1, s_2, \dots , s_n$，定义前缀总分为：

$$V=\sum_{i<j} P(s_i,s_j)$$

其中 $P(s_i, s_j)$ 表示 $s_i, s_j$ 的最长公共前缀的长度。

小蓝可以选择其中一个字符串，并修改其中的一个字符。请问修改后前缀总分最大为多少？
## 输入格式

输入的第一行包含一个正整数 $n$。
接下来 $n$ 行，每行包含一个字符串 $s_i$。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
3
aab
bbb
abb
```
### 样例输出 #1
```
5
```
## 提示

### 样例说明

将第二个字符串改为 $\tt{abb}$ ，得分为 $P(\tt{aab}, \tt{abb})+P(\tt{aab}, \tt{abb})+P(\tt{abb}, \tt{abb}) = 1 + 1 + 3 = 5$。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n \leq 20$；
- 对于所有评测用例，$1 \leq n \leq 200$，$1 \leq |s_i| \leq 200$，其中 $|s_i|$ 表示 $s_i$ 的长度。



---

---
title: "[蓝桥杯 2024 国研究生组] 分割字符串"
layout: "post"
diff: 普及+/提高
pid: P12318
tag: ['模拟', '字符串', '图论', '2024', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国研究生组] 分割字符串
## 题目描述

给定一个仅含小写字母的字符串 $S$ ，你可将其分割成任意份子串。我们要求分割后任何一段的长度都不大于 $5$ ，且相邻的两个子串不能含有相同的字母。例如 $\tt{abcdae}$ 分割为 $\tt{abcd}$ 和 $\tt{ae}$ 都含 $\tt{a}$，不合法，但可以分割为 $\tt{abcda}$ 和 $\tt{e}$，或者 $\tt{ab}$、$\tt{cd}$、$\tt{ae}$ 等。

问该字符串的所有长度小于等于 $5$ 的本质不同的子串中，哪些在任何分割方案中都没有出现过，按字典序将它们全部输出。

## 输入格式

输入一行包含一个字符串表示 $S$。
## 输出格式

输出的第一行包含一个整数 $t$ ，表示题目要求的字符串的数量。

接下来 $t$ 行，每行包含一个要求的字符串 $r_i$ ，按字典序排序。
## 样例

### 样例输入 #1
```
abab
```
### 样例输出 #1
```
4
ab
aba
ba
bab
```
## 提示

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$|S| \leq 10$；
- 对于 $60\%$ 的评测用例，$|S| \leq 5000$；
- 对于所有评测用例，$1 \leq |S| \leq 10^5$。


---

---
title: "[蓝桥杯 2025 国 Python A] 网络流量监控"
layout: "post"
diff: 普及+/提高
pid: P12875
tag: ['模拟', '字符串', '2025', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 Python A] 网络流量监控
## 题目背景

2025-06-16 21:45 根据题意和样例，目前洛谷数据的 $q_i$ 中不带 `*` 通配符。如果蓝桥杯官方数据中证实带有通配符，那么我们会修改本题数据。
## 题目描述

网络安全团队需要开发一个系统来监控和检测恶意网络流量。他们收集了一系列已知的恶意请求路径模式，每个模式都有一个对应的风险等级。你的任务是实现一个算法，检测给定的网络请求路径是否匹配这些模式，并返回匹配模式中最高的风险等级。下面是恶意请求路径的相关描述：

### 路径格式
- 路径由斜杠（/）分隔的若干段组成，如 `/api/users/profile`。
- 路径总是以斜杠（/）开头。
- 路径中的每一段可以是由小写英文字母和数字组成的非空字符串。当路径为路径模式时，路径中的一段还可以是通配符 `*` 或 `**`。

### 通配符规则
- 通配符包括单通配符（`*`）和双通配符（`**`），只能是路径模式中的完整一段。一个路径中最多有一段通配符，不能出现两个单通配符，不能出现两个双通配符，也不能同时出现单通配符和双通配符。
- 单通配符（`*`）用于匹配路径中的任意一段。
    - 例如：`/api/*/delete` 可以匹配 `/api/users/delete` 或 `/api/files/delete`，但不能匹配 `/api/admin/users/delete`。
- 双通配符（`**`）用于匹配路径中的零段或连续多段。
    - 例如：`/api/admin/**` 可以匹配 `/api/admin`、`/api/admin/users` 或 `/api/admin/users/profile`。
    - 例如：`/static/**/execute` 可以匹配 `/static/execute`、
`/static/js/execute` 或 `/static/css/js/execute`。

### 风险评估
- 每个恶意路径模式都有一个风险等级。
- 如果一个请求同时匹配多个模式，返回风险等级最高的。
- 如果不匹配任何模式，返回 `SAFE`。

你需要实现一个算法，给定恶意请求路径模式集合和一系列网络请求路径，判断每个网络请求是否触发警报，并且返回触发的最高风险等级。
## 输入格式

输入的第一行包含一个正整数 $n$ ，表示恶意路径模式的数量

接下来 $n$ 行，每行包含一个整数 $l_i$ 和一个字符串 $p_i$ ，用一个空格分隔，表示一个恶意请求路径模式，$l_i$ 表示风险等级，$p_i$ 表示路径模式。

接下来一行包含一个整数 $m$ ，表示要检测的网络请求数量。

接下来 $m$ 行，每行包含一个字符串 $q_i$ ，表示一个网络请求路径。
## 输出格式

对于每个网络请求路径，输出一行，包含检测结果。如果触发警报，输出 `ALERT: [风险等级]`；如果没有触发警报，输出 `SAFE`。
## 样例

### 样例输入 #1
```
5
80 /api/admin/**
60 /api/*/delete
75 /*/config/system
90 /api/users/*/password
50 /static/**/execute
8
/api/users/profile
/api/admin/users
/api/config/delete
/dev/config/system
/static/js/execute
/api/users/123/password
/static/css/js/execute
/api/admin
```
### 样例输出 #1
```
SAFE
ALERT: 80
ALERT: 60
ALERT: 75
ALERT: 50
ALERT: 90
ALERT: 50
ALERT: 80
```
## 提示

**【样例说明】**

1. `/api/users/profile` - 不匹配任何模式，所以是 SAFE。
2. `/api/admin/users` - 匹配 `/api/admin/**`，风险等级 80。
3. `/api/config/delete` - 匹配 `/api/*/delete`，其中 `*` 匹配 `config`，风险等级 60。
4. `/dev/config/system` - 匹配 `/*/config/system`，其中 `*` 匹配 `dev`，风险等级 75。
5. `/static/js/execute` - 匹配 `/static/**/execute`，其中 `**` 匹配 `js`，风险等级 50。
6. `/api/users/123/password` - 匹配 /`api/users/*/password`，其中 `*` 匹配 `123`，风险等级 90。
7. `/static/css/js/execute` - 匹配 `/static/**/execute`，其中 `**` 匹配 `css/js`，风险等级 50。
8. `/api/admin` - 匹配 `/api/admin/**`，其中 `**` 匹配空（0 个段），风险等级 80。

**【评测用例规模与约定】**

对于 $20\%$ 的评测用例，$1 \leq n \leq 10, 1 \leq m \leq 10$；

对于 $40\%$ 的评测用例，$1 \leq n \leq 100, 1 \leq m \leq 100$；

对于 $60\%$ 的评测用例，$1 \leq n \leq 1000, 1 \leq m \leq 1000$；

对于所有评测用例，$1 \leq n \leq 10,000$，$1 \leq m \leq 1000$，$1 \leq l_i \leq 50000$，$1 \leq |p_i| \leq 50$，$1 \leq |q_i| \leq 50$。


---

---
title: "[GCJ 2022 #1C] Letter Blocks"
layout: "post"
diff: 普及+/提高
pid: P12990
tag: ['字符串', '贪心', '2022', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2022 #1C] Letter Blocks
## 题目描述

It is a rainy day, so you are indoors building towers of letter blocks. A letter block is a wooden cube that has a letter printed on one of its sides. The font used for the letters makes the blocks have a clear orientation: that is, there is only one side that can be pointed down (toward the floor) and one side that can be pointed up (toward the ceiling).

You have built multiple separate towers so far. Now you want to combine all of them into a single megatower by choosing one of your towers as the base, then picking up another tower (without changing the order of its blocks) and stacking the whole thing on top of that, and so on, until all towers have been used.

As an additional constraint for the megatower, for any two blocks that have the same letter, all blocks between them must also have that letter. That is, each letter of the alphabet that appears in the megatower needs to appear in one contiguous group (of one or more blocks).

For example, consider the following three possible megatowers. (These are separate examples, not built from the same original towers. Also note that the different block sizes are just for fun and are not part of the problem.)

![](https://cdn.luogu.com.cn/upload/image_hosting/s3qed2k7.png)

The leftmost two megatowers are valid, since each letter appears in a contiguous group. However, the rightmost megatower is not valid, because there is a B in between two Cs.

Given the towers that you have built so far, can you stack them all up into a valid megatower?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case is described by two lines. The first line consists of a single integer $\mathbf{N}$, the number of towers that are currently built. The second line consists of $\mathbf{N}$ strings $\mathbf{S}_{1}, \mathbf{S}_{2}, \ldots, \mathbf{S}_{\mathbf{N}}$ representing the towers. Each of these strings consists of only uppercase letters. The $i$-th letter of each of these strings is the letter on the $i$-th block from the bottom in the represented tower.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is a string representing a valid megatower as described above, or the word IMPOSSIBLE if no valid megatower can be built. (Notice that the string IMPOSSIBLE can never itself represent a valid megatower, since the two $\mathbf{i}$ s have other letters in between.)
## 样例

### 样例输入 #1
```
6
5
CODE JAM MIC EEL ZZZZZ
6
CODE JAM MIC EEL ZZZZZ EEK
2
OY YO
2
HASH CODE
6
A AA BB A BA BB
2
CAT TAX
```
### 样例输出 #1
```
Case #1: ZZZZZJAMMICCODEEEL
Case #2: IMPOSSIBLE
Case #3: IMPOSSIBLE
Case #4: IMPOSSIBLE
Case #5: BBBBBAAAAA
Case #6: IMPOSSIBLE
```
## 提示

**Sample Explanation 1**

In Sample Case #1, `JAMMICCODEEELZZZZZ` and `ZZZZZJAMMICCODEEEL` are the only two valid outputs.

In Sample Case #2, recall that all towers must be used in the megatower, so even though the first five towers together would form a valid megatower (as in Sample Case #1), the additional `EEK` makes the case impossible. No matter how the `EEL` and `EEK` towers are stacked relative to each other, there will be at least two non-contiguous groups of `E`s.

In Sample Case #3, no matter how you stack the towers, either the two `O`s are not contiguous or the two Ys are not contiguous.

In Sample Case #4, there are non-H letters in between the `H`s of `HASH`, so this case is also impossible.

In Sample Case #5, this answer is the only valid one. Also notice that the towers are not necessarily all distinct.

In Sample Case #6, no matter how you stack the towers, the two `A`s cannot be contiguous.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \text{the length of } \mathbf{S}_i \leq 10$, for all $i$.

**Test Set 1 (10 Pts, Visible Verdict)**

- $2 \leq \mathbf{N} \leq 6$.

**Test Set 2 (15 Pts, Visible Verdict)**

- $2 \leq \mathbf{N} \leq 100$.


---

---
title: "[NOIP 2011 普及组] 表达式的值"
layout: "post"
diff: 普及+/提高
pid: P1310
tag: ['字符串', '动态规划 DP', '2011', 'NOIP 普及组']
---
# [NOIP 2011 普及组] 表达式的值
## 题目描述

对于1 位二进制变量定义两种运算：

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|} \hline
\kern{5em}\mathclap\textsf{运算符}\kern{5em} & \kern{5em}\mathclap\textsf{运算规则}\kern{5em} \\ \hline
\oplus &
\begin{aligned}
0 \oplus 0 &= 0 \\
0 \oplus 1 &= 1 \\
1 \oplus 0 &= 1 \\
1 \oplus 1 &= 1 \\
\end{aligned} \\ \hline
\times &
\begin{aligned}
0 \times 0 &= 0 \\
0 \times 1 &= 0 \\
1 \times 0 &= 0 \\
1 \times 1 &= 1 \\
\end{aligned} \\ \hline
\end{array}
$$

运算的优先级是：

1. 先计算括号内的，再计算括号外的。

2. “× ”运算优先于“⊕”运算，即计算表达式时，先计算× 运算，再计算⊕运算。例如：计算表达式A⊕B × C时，先计算 B × C，其结果再与 A 做⊕运算。

现给定一个未完成的表达式，例如\_+(\_\*\_)，请你在横线处填入数字$0 $或者$1$ ，请问有多少种填法可以使得表达式的值为$0 $。

## 输入格式

共 2 行。

第1 行为一个整数 $L$，表示给定的表达式中除去横线外的运算符和括号的个数。

第2 行为一个字符串包含 $L$ 个字符，其中只包含’（’、’）’、’+’、’\*’这$4$ 种字符，其中’（’、’）’是左右括号，’+’、’\*’分别表示前面定义的运算符“⊕”和“×”。这行字符按顺序给出了给定表达式中除去变量外的运算符和括号。

## 输出格式

共1 行。包含一个整数，即所有的方案数。注意：这个数可能会很大，请输出方案数对$10007 $取模后的结果。

## 样例

### 样例输入 #1
```
4
+(*)

```
### 样例输出 #1
```
3

```
## 提示

【输入输出样例说明】

  给定的表达式包括横线字符之后为：\_+(\_\*\_) 

  在横线位置填入(0 、0 、0) 、(0 、1 、0) 、(0 、0 、1) 时，表达式的值均为0 ，所以共有3种填法。 

【数据范围】

对于 $20\%$ 的数据有 $ 0 \le L \le 10$。

对于 $50\%$ 的数据有 $0 \le L \le 1,000$。

对于 $70\%$ 的数据有 $ 0 \le L \le 10,000$ 。

对于 $100\%$的数据有 $ 0 \le L \le 100,000$。

对于$50\%$ 的数据输入表达式中不含括号。



---

---
title: "单词背诵"
layout: "post"
diff: 普及+/提高
pid: P1381
tag: ['模拟', '字符串', '二分', '福建省历届夏令营', '哈希 hashing', '双指针 two-pointer']
---
# 单词背诵
## 题目描述

灵梦有 $n$ 个单词想要背，但她想通过一篇文章中的一段来记住这些单词。

文章由 $m$ 个单词构成，她想在文章中找出连续的一段，其中包含最多的她想要背的单词（重复的只算一个）。并且在背诵的单词量尽量多的情况下，还要使选出的文章段落尽量短，这样她就可以用尽量短的时间学习尽可能多的单词了。
## 输入格式

第 $1$ 行一个数 $n$，接下来 $n$ 行每行是一个长度不超过 $10$ 的字符串，表示一个要背的单词。

接着是一个数 $m$，然后是 $m$ 行长度不超过 $10$ 的字符串，每个表示文章中的一个单词。
## 输出格式

输出文件共 $2$ 行。第 $1$ 行为文章中最多包含的要背的单词数，第 $2$ 行表示在文章中包含最多要背单词的最短的连续段的长度。
## 样例

### 样例输入 #1
```
3

hot

dog

milk

5

hot

dog

dog

milk

hot


```
### 样例输出 #1
```
3

3


```
## 提示

### 数据规模与约定

- 对于 $30\%$ 的数据，$n \le 50$，$m \le 500$；
- 对于 $60\%$ 的数据，$n \le 300$，$m \le 5000$；
- 对于 $100\%$ 的数据，$n \le 1000$，$m \le 10^5$。


---

---
title: "[USACO2.3] 最长前缀 Longest Prefix"
layout: "post"
diff: 普及+/提高
pid: P1470
tag: ['字符串', '动态规划 DP', 'USACO', 'KMP 算法']
---
# [USACO2.3] 最长前缀 Longest Prefix
## 题目描述

在生物学中，一些生物的结构是用包含其要素的大写字母序列来表示的。生物学家对于把长的序列分解成较短的序列（即元素）很感兴趣。

如果一个集合 $P$ 中的元素可以串起来（元素可以重复使用）组成一个序列 $s$ ，那么我们认为序列 $s$ 可以分解为 $P$ 中的元素。元素不一定要全部出现（如下例中 `BBC` 就没有出现）。举个例子，序列 `ABABACABAAB` 可以分解为下面集合中的元素：`{A,AB,BA,CA,BBC}`

序列 $s$ 的前面 $k$ 个字符称作 $s$ 中长度为 $k$ 的前缀。设计一个程序，输入一个元素集合以及一个大写字母序列  ，设 $s'$ 是序列 $s$ 的最长前缀，使其可以分解为给出的集合 $P$ 中的元素，求 $s'$ 的长度 $k$。

## 输入格式

输入数据的开头包括若干个元素组成的集合 $P$，用连续的以空格分开的字符串表示。字母全部是大写，数据可能不止一行。元素集合结束的标志是一个只包含一个 `.` 的行，集合中的元素没有重复。  

接着是大写字母序列 $s$ ，长度为，用一行或者多行的字符串来表示，每行不超过 $76$ 个字符。换行符并不是序列 $s$ 的一部分。

## 输出格式

只有一行，输出一个整数，表示 S 符合条件的前缀的最大长度。

## 样例

### 样例输入 #1
```
A AB BA CA BBC
.
ABABACABAABC

```
### 样例输出 #1
```
11

```
## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le \text{card}(P) \le 200$，$1\le |S| \le 2\times 10^5$，$P$ 中的元素长度均不超过 $10$。

翻译来自NOCOW

USACO 2.3



---

---
title: "Kruscal的加法"
layout: "post"
diff: 普及+/提高
pid: P1557
tag: ['模拟', '字符串', 'USACO']
---
# Kruscal的加法
## 题目背景

奶牛 Kruscal 认为人类的加法太落后了。比如说有时候想要用加法计算 `+15*3`，只能写成 `+15+15+15`，真是浪费精力啊！于是，Kruscal 决定开发出一种新的加法算式。
## 题目描述

当然，新的算式也是建立在原本算式的基础上的，不同就在于上式可以直接写成 `+++15`，同理，对于 `-15*3` 这样的算式可以写成 `---15`。一段时间后，Kruscal 又被那无穷多个 `+-` 号囧到了，于是他又将这个算式改进了一下。

比如 `+15*3` 又可以写成 `+(3)15`，同样，`-15*3` 等价于 `-(3)15`。但从上面可以看出，对于乘数较小的情况，如 `+++15` 这样的表述还是很方便的，于是在新的算式中还是保留了这种形式。

对于算式还要做一点特殊的说明：`+15*3` 转换成 Kruscal 型算式时可以写成 `+++15` 或 `+(3)15`，但不可以写成 `++(2)15` 这样的形式。

对于算式 `23+15*3-2` 可以表示为以下几种形式：`23+++15-2`、`23+(3)15-2`、`+23+++15-2`、`+23+(3)15-2、+(1)23+(3)15-(1)2`。不会出现如下几种形式：`(1)23+++15-2`、`+23++(2)15-(1)2`、`23+++15-2+(0)100`、`23-(-3)15-2`。
## 输入格式

一行，一个 Kruscal 型算式。
## 输出格式

一行，为运算结果。
## 样例

### 样例输入 #1
```
+(1)23+(3)15-(1)2
```
### 样例输出 #1
```
66
```
## 提示

对于 $100 \%$ 的数据，算式长度不超过 $2000$。


---

---
title: "万能的OIH搜索"
layout: "post"
diff: 普及+/提高
pid: P1770
tag: ['字符串']
---
# 万能的OIH搜索
## 题目背景

以下皆为真实的故事。

OIH（Oi in hand <http://www.oiinhand.info/> ）是洛谷的官方战略合作伙伴。

洛谷的题目搜索功能（请看看上面的搜索框）、在线 IDE 功能均使用 OIH 的服务。

OIH 的搜索功能很强大，其庞大的数据库拥有 $8000+$ 道中外主流 OJ 的题目。只需要只言片语（题目名称、描述、甚至是测试数据）就可以很快的搜出这道题的出处（“改编题”的杀手）。

以后，OIH 还将收录全网上的题解（数量是万级别的），只要通过题目名称，就可以搜到这个题目的题解。

OIH 的目标是制作出一个适合 OIers 的 app。虽然 OIH 不是 OJ，但是 OIH 的辅助功能能够给 OIers 带来很大的便利。如果您有任何的 idea，请 @soha（oih 的作者）。
## 题目描述

经过多次谈判，kkksc03 终于取得了 OIH 搜索的接口，现在向 OIH 服务器发送了一个查询请求，返回了一道题目。

查询关键词是一句话，由汉字（我们用它的拼音代替）、空格（每个汉字之间都有空格）、半角标点组成。返回的题目也是这样的。kkksc03 希望将题目中的某些词语加粗。所谓词语，就是连续两个或以上汉字。比如说 `tao tao`,`zhai ping guo` 都是词语，而 `hao`,`ni,hao` 不是词语。如果一个在题目中出现的词语也在关键词中出现的词语，那么加粗。加粗的方法是在词语前加上 `<b>`，在词语后面加上一个 `</b>`。至于标点符号么加不加粗无所谓。kkksc03 希望添加标记（`<b>` `</b>`对）的数量尽可能少，而且每个标记之间的的字符数最少。
## 输入格式

两行。第一行为一个字符串 $S_1$，关键词字符串。第二行 $S_2$，是 OIH 返回的题目字符串。

## 输出格式

一行，处理的结果。
## 样例

### 样例输入 #1
```
Shang wang dou tmd bei ping ping an an he xie diao le.
Tian yao mie he xie, tui he xie bao ping an.  shang Wang sou suo jiu ping cha cha cha ,you       zhen       xiang!
```
### 样例输出 #1
```
Tian yao mie <b>he xie</b>, tui <b>he xie</b> bao <b>ping an.  shang Wang</b> sou suo jiu ping cha cha cha ,you       zhen       xiang!
```
## 提示

每个汉字不超过 $7$ 个英文字符。

关键字不超过 $100$ 个汉字。

返回的题目不超过 $1000$ 个汉字。


---

---
title: "[USACO12MAR] Tractor S"
layout: "post"
diff: 普及+/提高
pid: P1849
tag: ['字符串', '图论', '贪心', '2012', 'USACO', '枚举']
---
# [USACO12MAR] Tractor S
## 题目描述

经过一天漫长的工作，农场主 John 完全忘记了他的拖拉机还在场地中央。他的奶牛们总喜欢和他搞些恶作剧，它们在场地的不同位置丢下 $n$ 堆干草。这样 John 就必须先移走一些干草堆才能将拖拉机开走。

拖拉机和干草堆都可以看作是二维平面上的点，它们的坐标都是整数，没有哪堆干草的坐标和拖拉机的初始坐标一致。John 驾驶拖拉机只能沿着坐标轴的方向移动若干单位长度，比如说，他可以先朝北移动 $2$ 个单位长度，再向东移动 $3$ 个单位长度等等。拖拉机不能移动到干草堆所占据的点。

请你帮助 John 计算一下，最少要移动多少堆干草才能将拖拉机开回坐标原点。
## 输入格式

输入的第一行是三个用空格隔开的整数，依次代表干草的堆数 $n$ 和拖拉机的起始坐标 $(x_0, y_0)$。

第 $2$ 行到第 $(n+1)$ 行，每行有两个用空格隔开的整数，第 $(i + 1)$ 行的整数 $x_i, y_i$ 代表第 $i$ 堆干草的坐标为 $(x_i, y_i)$。
## 输出格式

一行一个整数，表示最少要移动多少堆干草 John 才能将拖拉机开回坐标原点。
## 样例

### 样例输入 #1
```
7 6 3 
6 2 
5 2 
4 3 
2 1 
7 3 
5 4 
6 4 
```
### 样例输出 #1
```
1 
```
## 提示

对于 $100\%$ 的数据，保证 $1 \leq n \leq 5 \times 10^4$，$1 \leq x_i, y_i \leq 10^3$。


---

---
title: "易语言"
layout: "post"
diff: 普及+/提高
pid: P1953
tag: ['模拟', '字符串', 'NOI 导刊']
---
# 易语言
## 题目描述

老师近段时间正在研究易语言，这是一款 Windows 下的可视化编程系统，由大连大有吴涛软件开发公司开发的、具有中国知识产权的系统。为了更好地学习该套系统，老师总是有意识地在实践中运用这套系统来开发程序。

这不，今天老师碰到了一个问题，那就是“当把数据放置到 KOJ 上去时，需要把测试数据改成相应的文件名”。举个例子说，如果原始测试数据文件名是 $\text{e0.in,\,e1.in\;...\;e9.in}$ 和 $\text{e0.out,\,e1.out\;...\;e9.out}$，则老师需要把文件全部改为 $\text{data1.in,\,data2.in\;...\;data10.in}$ 和 $\text{data1.out,\,data2.out\;...\;data10.out}$。程序界面如下图所示：

*（注：此处似乎缺少一张图片，但不影响对题意的理解）*

当然了，老师是编程的菜鸟，比起你可是差多了，所以他的程序不是很好，现在想请你帮老师改进这个程序。

事先，老师会告诉你所需要生成的目标文件名格式，比如，他告诉你 $\text{enger0.in}$ 和 $\text{ans}$ ，则表示目标文件中输入文件的主名是 $\text{enger}$，扩展名是 $\text{in}$，编号从 $0$ 开始而且跟在主名后面，当然了，输出文件名就依次是 $\text{enger0.ans,\,enger1.ans\;...\;enger}x\text{.ans}$，其中的 $x$ 你可以统计老师告诉你的原始文件名的个数来确定。另外，老师也会告诉你原始的所有输入数据的文件名全称，比如 $\text{a1.txt,\,a2.txt\;...\;a}x\text{.txt}$。但老师是一个粗心的人，你不要期望老师给你的文件名是按照编号从小到大给出的，但给出的文件名肯定是正确的而且满足一般输入输出文件名的规律的(编号数字肯定出现在文件主名末尾或者扩展名末尾，而且除了这个编号数字外，在原始文件名和生成的目标文件名其他的任何地方都不会出现数字)。

有些原始的输入输出文件名并不需要改变主名和扩展名，而只需改变文件编号即可，此时，老师首先会告诉你一个数字 $1$（或者 $0$），表示最终生成的目标文件的主名和扩展名不必改变，而只需把编号改为从 $1$（或者 $0$）开始即可。

## 输入格式

输入的第一行有两种情况，第一种情况是两个字符串，分别表示最终生成的目标文件名的格式（第一个表示生成的目标文件中的第一个输入文件的名字）；第二种情况是只有一个数字 $1$（或者 $0$），表示文件名主名和扩展名不必更改，只需修改成从 $1$（或者 $0$）开始编号的文件名即可。接下来 $n$ 行（$1 \le n \le 10^5$），每行两个用一个空格分隔的字符串，分别表示原始输入和输出文件的文件名（对于输入和输出文件中所有文件名的主名和扩展名都不超过 $10$ 个字符，而且文件的最大编号不会超过 $2 \times 10^5$）。

## 输出格式

输出包含 $n$ 行，每行两个用一个空格分隔的字符串，分别表示最终生成的目标文件的文件名。第一个表示输入文件，第二个表示输出文件。按照编号从小到大输出。
## 样例

### 样例输入 #1
```
enger0.in ans
abc1.in abc1.out
abc2.in abc2.out
abc3.in abc3.out
abc4.in abc4.out

```
### 样例输出 #1
```
enger0.in enger0.ans
enger1.in enger1.ans
enger2.in enger2.ans
enger3.in enger3.ans

```
### 样例输入 #2
```
1
aa.in0 aa.ou0
aa.in1 aa.ou1
aa.in2 aa.ou2

```
### 样例输出 #2
```
aa.in1 aa.ou1
aa.in2 aa.ou2
aa.in3 aa.ou3

```


---

---
title: "有趣的数"
layout: "post"
diff: 普及+/提高
pid: P2022
tag: ['模拟', '字符串', '搜索', '二分']
---
# 有趣的数
## 题目描述

让我们来考虑 $1$ 到 $N$ 的正整数集合。让我们把集合中的元素按照字典序排列，例如当 $N=11$ 时，其顺序应该为：$1,10,11,2,3,4,5,6,7,8,9$。

定义 $K$ 在 $N$ 个数中的位置为 $Q(N,K)$，例如 $Q(11,2)=4$。现在给出整数 $K$ 和 $M$，要求找到最小的 $N$，使得 $Q(N,K)=M$。
## 输入格式

输入文件只有一行，是两个整数 $K$ 和 $M$。
## 输出格式

输出文件只有一行，是最小的 $N$，如果不存在这样的 $N$ 就输出 $0$。
## 样例

### 样例输入 #1
```
2 4

```
### 样例输出 #1
```
11

```
### 样例输入 #2
```
100000001 1000000000
```
### 样例输出 #2
```
100000000888888879
```
## 提示

【数据约定】


$40\%$ 的数据，$1 \le K,M \le 10^5$；

$100\%$ 的数据，$1 \le K,M \le 10^9$。



---

---
title: "[AHOI2005] 病毒检测"
layout: "post"
diff: 普及+/提高
pid: P2536
tag: ['字符串', '2005', '各省省选', '安徽', '字典树 Trie', 'AC 自动机']
---
# [AHOI2005] 病毒检测
## 题目描述

科学家们在 Samuel 星球上的探险仍在继续。非常幸运的，在 Samuel 星球的南极附近，探险机器人发现了一个巨大的冰湖！机器人在这个冰湖中搜集到了许多 RNA 片段运回了实验基地。

科学家们经过几个昼夜的研究，发现这些 RNA 片段中有许多是未知的病毒！

每个 RNA 片段都是由 `A`、`C`、`T`、`G` 组成的序列。科学家们也总结出了 Samuel 星球上的“病毒模版片段”。一个模版片段是由 `A`、`C`、`T`、`G` 的序列加上通配符 `*` 和 `?` 来表示。其中 `*` 的意思是可以匹配上 $0$ 个或任意多个字符，而 `?` 的意思是匹配上任意一个字母。

如果一个 RNA 片段能够和“病毒模版片段”相匹配，那么这个 RNA 片段就是未知的病毒。

例如，假设 “病毒模版片段”为 `A*G?C`。RNA 片段：`AGTC`，`AGTGTC` 都是未知的病毒，而 RNA 片段 `AGTGC` 则不是病毒。

由于，机器人搜集的这些 RNA 片段中除去病毒的其他部分都具有非常高的研究价值。所以科学家们希望能够分辨出其中哪些 RNA 片段不是病毒，并将不是病毒的 RNA 片段运回宇宙空间站继续进行研究。

科学家将这项任务交给了小联。现在请你为小联编写程序统计哪些 RNA 片段不是病毒。
## 输入格式

共 $N+2$ 行输入。

第一行有一个字符串，由 `A`、`C`、`T`、`G`、`*`、`?` 组成，表示“病毒模版片段”。“病毒模版片段”的长度不超过 $1000$。

第二行有一个整数 $N$，表示机器人搜集到的 RNA 片段的数目。

随后的 $N$ 行，每一行有一个字符串，由 `A`、`C`、`T`、`G` 组成，表示一个 RNA 片段。
## 输出格式

只有一行输出，为整数 $M$，即不是病毒的 RNA 片段的数目。

## 样例

### 样例输入 #1
```
A*G?C
3
AGTC
AGTGTC
AGTGC
```
### 样例输出 #1
```
1
```
## 提示

输入中的 RNA 片段 `AGTGC` 不是病毒。

对于所有数据，$0 < N < 500$。

特别的：

- 每个 RNA 片段的长度不超过 $500$；
- “病毒模版片段”和 RNA 片段的长度都至少为 $1$。


---

---
title: "[NOIP 2015 提高组] 子串"
layout: "post"
diff: 普及+/提高
pid: P2679
tag: ['字符串', '动态规划 DP', '2015', 'NOIP 提高组', 'O2优化', '枚举']
---
# [NOIP 2015 提高组] 子串
## 题目背景

NOIP2015 Day2T2
## 题目描述

有两个仅包含小写英文字母的字符串 $A$ 和 $B$。

现在要从字符串 $A$ 中取出 $k$ 个互不重叠的非空子串，然后把这 $k$ 个子串按照其在字符串 $A$ 中出现的顺序依次连接起来得到一个新的字符串。请问有多少种方案可以使得这个新串与字符串 $B$ 相等？

注意：子串取出的位置不同也认为是不同的方案。
## 输入格式

第一行是三个正整数 $n,m,k$，分别表示字符串 $A$ 的长度，字符串 $B$ 的长度，以及问题描述中所提到的 $k$，每两个整数之间用一个空格隔开。

第二行包含一个长度为 $n$ 的字符串，表示字符串 $A$。

第三行包含一个长度为 $m$ 的字符串，表示字符串 $B$。
## 输出格式

一个整数，表示所求方案数。

由于答案可能很大，所以这里要求输出答案对 $1000000007$ 取模的结果。
## 样例

### 样例输入 #1
```
6 3 1 
aabaab 
aab
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 3 2 
aabaab 
aab
```
### 样例输出 #2
```
7
```
### 样例输入 #3
```
6 3 3 
aabaab 
aab
```
### 样例输出 #3
```
7
```
## 提示

**样例解释**

所有合法方案如下：（加下划线的部分表示取出的字串）

样例 1：$\texttt{\underline{aab}\,aab,aab\,\underline{aab}}$。  
样例 2：$\texttt{\underline{a}\,\underline{ab}\,aab,\underline{a}\,aba\,\underline{ab},a\,\underline{a}\,ba\,\underline{ab},aab\,\underline{a}\,\underline{ab},\underline{aa}\,\underline{b}\,aab,\underline{aa}\,baa\,\underline{b},aab\,\underline{aa}\,\underline{b}}$。  
样例 3：$\texttt{\underline{a}\,\underline{a}\,\underline{b}\,aab,\underline{a}\,\underline{a}\,baa\,\underline{b},\underline{a}\,ab\,\underline{a}\,a\,\underline{b},\underline{a}\,aba\,\underline{a}\,\underline{b},a\,\underline{a}\,b\,\underline{a}\,a\,\underline{b},a\,\underline{a}\,ba\,\underline{a}\,\underline{b},aab\,\underline{a}\,\underline{a}\,\underline{b}}$。

**数据范围**

对于第 1 组数据：$1≤n≤500,1≤m≤50,k=1$;  
对于第 2 组至第 3 组数据：$1≤n≤500,1≤m≤50,k=2$;   
对于第 4 组至第 5 组数据：$1≤n≤500,1≤m≤50,k=m$;   
对于第 1 组至第 7 组数据：$1≤n≤500,1≤m≤50,1≤k≤m$;  
对于第 1 组至第 9 组数据：$1≤n≤1000,1≤m≤100,1≤k≤m$;   
对于所有 10 组数据：$1≤n≤1000,1≤m≤200,1≤k≤m$。  



---

---
title: "【模板】KMP"
layout: "post"
diff: 普及+/提高
pid: P3375
tag: ['字符串', 'O2优化', 'KMP 算法']
---
# 【模板】KMP
## 题目描述

给出两个字符串 $s_1$ 和 $s_2$，若 $s_1$ 的区间 $[l, r]$ 子串与 $s_2$ 完全相同，则称 $s_2$ 在 $s_1$ 中出现了，其出现位置为 $l$。  
现在请你求出 $s_2$ 在 $s_1$ 中所有出现的位置。

定义一个字符串 $s$ 的 border 为 $s$ 的一个**非 $s$ 本身**的子串 $t$，满足 $t$ 既是 $s$ 的前缀，又是 $s$ 的后缀。  
对于 $s_2$，你还需要求出对于其每个前缀 $s'$ 的最长 border $t'$ 的长度。
## 输入格式

第一行为一个字符串，即为 $s_1$。  
第二行为一个字符串，即为 $s_2$。

## 输出格式

首先输出若干行，每行一个整数，**按从小到大的顺序**输出 $s_2$ 在 $s_1$ 中出现的位置。  
最后一行输出 $|s_2|$ 个整数，第 $i$ 个整数表示 $s_2$ 的长度为 $i$ 的前缀的最长 border 长度。
## 样例

### 样例输入 #1
```
ABABABC
ABA

```
### 样例输出 #1
```
1
3
0 0 1 

```
## 提示

### 样例 1 解释

 ![](https://cdn.luogu.com.cn/upload/pic/2257.png)。
 
对于 $s_2$ 长度为 $3$ 的前缀 `ABA`，字符串 `A` 既是其后缀也是其前缀，且是最长的，因此最长 border 长度为 $1$。


### 数据规模与约定

**本题采用多测试点捆绑测试，共有 3 个子任务**。

- Subtask 1（30 points）：$|s_1| \leq 15$，$|s_2| \leq 5$。
- Subtask 2（40 points）：$|s_1| \leq 10^4$，$|s_2| \leq 10^2$。
- Subtask 3（30 points）：无特殊约定。

对于全部的测试点，保证 $1 \leq |s_1|,|s_2| \leq 10^6$，$s_1, s_2$ 中均只含大写英文字母。


---

---
title: "[AHOI2017初中组] alter"
layout: "post"
diff: 普及+/提高
pid: P3718
tag: ['字符串', '贪心', '2017', '二分', '安徽', '枚举', '队列']
---
# [AHOI2017初中组] alter
## 题目描述

有 $n$ 盏灯排成一列，其中有些灯开着，有些灯关着。小可可希望灯是错落有致的，他定义一列灯的状态的不优美度为这些灯中最长的连续的开着或关着的灯的个数。小可可最多可以按开关 $k$ 次，每次操作可以使该盏灯的状态取反：原来开着的就关着，反之开着。现在给出这些灯的状态，求操作后最小的不优美度。
## 输入格式

第一行两个整数 $n,k$。

第二行是一个长度为 $n$ 的字符串，其中有两种字符：`N` 和 `F`。其中 `N` 表示该灯开着，`F` 表示该灯关着。
## 输出格式

最小的不优美度。
## 样例

### 样例输入 #1
```
8 1
NNNFFNNN
```
### 样例输出 #1
```
3
```
## 提示

$30\%$ 的数据：$1\le k \le n\le20$；

$50\%$ 的数据：$1\le k \le n\le300$；

另有 $15\%$ 的数据：$1\le k \le n\le 10^5$，字符串为全 `N` 或全 `F`；

$100\%$ 的数据：$1\le k \le n\le 10^5$。

本题已经加入 hack 数据。


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
title: "龙盘雪峰信息解析器"
layout: "post"
diff: 普及+/提高
pid: P3982
tag: ['模拟', '字符串', '2017', '进制']
---
# 龙盘雪峰信息解析器
## 题目背景

```cpp
薄雾笼罩，远方的雪峰无限迷人，感慨之间，阴影将至。
```
与真程海洋毗邻的龙盘雪山与我们保持着联系，但是龙盘雪山的通讯员常常把信息进行奇怪的加密，然后要我们来破译，很是谨慎。但是，久而久之，我们的通讯员不耐烦了，差点掀桌子砸凳子不干了。所以我们想做一个信息解析器，就是这样。

## 题目描述

龙盘雪峰传来的信息都加密成了复杂的代码，我们需要你来做一个程序，按照解析规则解密这些代码，翻译成文字信息，以下是其解析规则：

该代码应为一连串的二进制码（只存在$ 0 $和$ 1 $，做加法时满$ 2 $进$ 1 $，每个$ 0 $或$ 1 $占一个字符），每八个字符为一单元（这也是规则）。

每个单元都有这样的规则：一、若【前三个字符】为$ 101 $时表示需要转换为字母$ A-Z $，字母$ A $代码为$ 10100000 $，字母$ C $为$ 10100010 $，$ 26 $个**大写字母**以字母表顺序按照这种规律顺序排列，分别对应一个二进制代码。二、若【前三个字符】为$ 111 $，则该单元翻译为空格。三、若【第一个字符】为$ 0 $，则该单元表示一个数，待定**与下一个单元所表示的数做加法**。加法过程中，这两个单元应转换为十进制，然后除以$ 2 $并**舍弃余数**才相加，加法结束后，这两个单元做加法得到的结果即为这两个单元的翻译结果（翻译结果用十进制表示，**这两个单元**就都翻译完毕了，详见样例$ 3 $）。

由于保险，龙盘雪峰经常发送【假代码】，而假代码则不存在上述规则，如果是假代码，**仅**输出$ Error $。

## 输入格式

输入仅一行，包含一串连续的代码（长度不超过$ 171111 $个字符），中间不会出现空格，保证不出现空代码。

## 输出格式

输出仅一行，包含一个字符串，是二进制代码按照上述规则翻译后的文字信息。

若该二进制代码中存在假代码信息，则**只**输出$ Error $。

## 样例

### 样例输入 #1
```
1010000011100000101011111010100010100110
```
### 样例输出 #1
```
A PIG
```
### 样例输入 #2
```
1
```
### 样例输出 #2
```
Error
```
### 样例输入 #3
```
0000001000000010000000100000001010100000
```
### 样例输出 #3
```
22A
```
### 样例输入 #4
```
IOIOOOOI
```
### 样例输出 #4
```
Error
```
## 提示

### 样例一说明：

$ 10100000 $代表$ A $，下一个单元开头为$ 111 $，那么翻译为空格，再下一个单元开头为$ 101 $，后接$ 01111 $，比$ A $多了$ 2^0+2^1+2^2+2^3=15 $，那么代表的就是$ P $了，以此类推，最后翻译为$ A\;PIG $。

### 注意：

对于规则一的解释：$ 26 $个大写字母按照字母表的顺序排列，以$ A=10100000 $开始，往后的每一个字母的二进制码的值都比前面一个字母的二进制码的值多$ 1 $（注意满二进一）；

此题目有误解题意的现象，请一定要看清楚题目，搞清楚逻辑关系，注意细节！



---

---
title: "[BalticOI 2009] Radio Transmission 无线传输"
layout: "post"
diff: 普及+/提高
pid: P4391
tag: ['字符串', '2009', '前缀和', 'KMP 算法', 'BalticOI（波罗的海）']
---
# [BalticOI 2009] Radio Transmission 无线传输
## 题目描述

给你一个字符串 $s_1$，它是由某个字符串 $s_2$ 不断自我连接形成的（保证至少重复 $2$ 次）。但是字符串 $s_2$ 是不确定的，现在只想知道它的最短长度是多少。
## 输入格式

第一行一个整数 $L$，表示给出字符串的长度。 

第二行给出字符串 $s_1$ 的一个子串，全由小写字母组成。  
## 输出格式

仅一行，表示 $s_2$ 的最短长度。
## 样例

### 样例输入 #1
```
8
cabcabca
```
### 样例输出 #1
```
3
```
## 提示

#### 样例输入输出 1 解释
对于样例，我们可以利用 $\texttt{abc}$ 不断自我连接得到 $\texttt{abcabcabcabc}$，读入的 $\texttt{cabcabca}$，是它的子串。

#### 规模与约定
对于全部的测试点，保证 $1\le L \le 10^6$。


---

---
title: "[JSOI2009] 电子字典"
layout: "post"
diff: 普及+/提高
pid: P4407
tag: ['字符串', '2009', '各省省选', '江苏', '枚举', '深度优先搜索 DFS', '字典树 Trie']
---
# [JSOI2009] 电子字典
## 题目描述


人们在英文字典中查找某个单词的时候可能不知道该单词的完整拼法，而只知道该单词的一个错误的近似拼法，这时人们可能陷入困境，为了查找一个单词而浪费大量的时间。带有模糊查询功能的电子字典能够从一定程度上解决这一问题：用户只要输入一个字符串，电子字典就返回与该单词编辑距离最小的几个单词供用户选择。

字符串 $a$ 与字符串 $b$ 的编辑距离是指：允许对 $a$ 或 $b$ 串进行下列“编辑”操作，将 $a$ 变为 $b$ 或 $b$ 变为 $a$，最少“编辑”次数即为距离。

1. 删除串中某个位置的字母；
2. 添加一个字母到串中某个位置；
3. 替换串中某一位置的一个字母为另一个字母。

JSOI 团队正在开发一款电子字典，你需要帮助团队实现一个用于模糊查询功能的计数部件：对于一个待查询字符串，如果它是单词，则返回 $-1$；如果它不是单词，则返回字典中有多少个单词与它的编辑距离为 $1$。
## 输入格式

第一行包含两个正整数 $N$ 和 $M$。

接下来的 $N$ 行，每行一个字符串，第 $i+1$ 行为单词 $W_i$，单词长度在 $1$ 至 $20$ 之间。

再接下来 $M$ 行，每行一个字符串，第 $i+N+1$ 表示一个待查字符串 $Q_i$。待查字符串长度在 $1$ 至 $20$ 之间。$W_i$ 和 $Q_i$ 均由小写字母构成，文件中不包含多余空格。
## 输出格式

输出应包括 $M$ 行，第 $i$ 行为一个整数 $X_i$：

- $X_i = -1$ 表示 $Q_i$ 为字典中的单词；

- 否则 $X_i$ 表示与 $Q_i$ 编辑距离为 $1$ 的单词的个数。
## 样例

### 样例输入 #1
```
4 3
abcd
abcde
aabc
abced
abcd
abc
abcdd
```
### 样例输出 #1
```
-1
2
3
```
## 提示

### 样例解释

- `abcd` 在单词表中出现过；
- `abc` 与单词 `abcd`、`aabc` 的编辑距离都是 $1$；
- `abcdd` 与单词 `abcd`、`abcde`、`abced` 的编辑距离都是 $1$。

### 数据范围与约定

- 所有单词互不相同，但是查询字符串可能有重复；
- 对 $50\%$ 的数据范围，$N,M\le 10^3$；
- 对 $100\%$ 的数据范围，$N,M\le 10^4$。


---

---
title: "[COCI 2017/2018 #1] Lozinke"
layout: "post"
diff: 普及+/提高
pid: P4421
tag: ['字符串', '2017', '哈希 hashing', 'COCI（克罗地亚）']
---
# [COCI 2017/2018 #1] Lozinke
## 题目描述

Recently, there has been a breach of user information from the mega-popular social network Secret Network. Among the confidential information are the passwords of all users.

Mihael, a young student who has been exploring computer security lately, found the whole thing really interesting. While experimenting with the social network, he found another security breach! When you input any string of characters that contains a substring equal to the actual password, the login will be successful. For example, if the user whose password is abc inputs one of the strings abc, abcd or imaabcnema, the system will successfully log him in, whereas the login will fail for axbc.

Mihael wants to know how many ordered pairs of different users exist such that the first user, using their own password, can login as the second user.
## 输入格式

The first line of input contains the positive integer N (1 ≤ N ≤ 20 000), the number of users.

Each of the following N lines contains the user passwords. The passwords consist of at least one and at most 10 lowercase letters of the English alphabet.
## 输出格式

The first and only line of output must contains the number of ordered pairs from the task.
## 样例

### 样例输入 #1
```
3
aaa
aa
abb

```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3
x
x
xy

```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
5
mir
mirta
ta
ir
t

```
### 样例输出 #3
```
6
```
## 提示

Clarification​ ​of​ ​the​ ​second​ ​test​ ​case:

The first user can login as the second user, the second user can login as the first, and the third user can login as both the first and the second user.
## 题目翻译

【题目描述】

最近，某社交网络平台出现了用户信息的泄露。

Mihal 是一个喜欢探索计算机安全的学生，他发现整个事情非常有趣。在经过一段时间的研究，他发现了一个安全漏洞。当你输入任何字符串时，如果用户的密码在这个字符串中出现， 那么你就可以通过这个字符串成功登录。 例如，如果密码为 abc 的用户输入了一个字符串为 abc 或 abcdde 或 imaabcnema，他将会成功登录，而 axbc 则会登录失败。

现在 Mihal 想知道会出现多少次用户可以用自己的密码成功登录其他用户的情况。

【输入】

输入第一行为正整数 N，表示用户数量。（N<=20000）

接下来 N 行包含 N 个用户的密码，每个密码小写字母组成，长度不超过 10。

【输出】

输出共一行，输出出现用户可以用自己的密码成功登录其他用户的总次数。

【样例3解释】

第一个用户可以成功登录第二个用户，第二个用户可以成功登录第一个用户，第三个用户可以登录第一个用户和第二个用户，总共出现 4 次本用户成功登录其他用户的情况。



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
title: "[1007] Scarlet的字符串不可能这么可爱"
layout: "post"
diff: 普及+/提高
pid: P4925
tag: ['字符串', '数学', '洛谷月赛']
---
# [1007] Scarlet的字符串不可能这么可爱
## 题目描述

Scarlet妄图构造字符集为$k$，长度为$L$的字符串，满足没有任何一个长度超过$1$的回文连续子串。

看起来这样的字符串太多了，Scarlet随手加了个限制：她指定了字符串的第$s$位为$w$。

这下Scarlet不会做了，请你来帮她计算究竟有多少满足条件的字符串。按照套路，你只要求出答案对$p$取模后的结果。
## 输入格式

第一行三个整数$k,L$和$p$，分别表示构造的字符串的的字符集、长度和模数。

第二行两个整数$s,w$，描述Scarlet给的限制。

**注意：$s=0$表示该数据点中Scarlet十分良心地没有添加限制**
## 输出格式

一行一个整数，表示答案对$p$的取模后的结果。
## 样例

### 样例输入 #1
```
3 3 233
1 1
```
### 样例输出 #1
```
2
```
## 提示

字符集：一个字符串中不同字符的数量。例如，字符集是3的话，你可以认为字符串仅由“A”、“B”、“C”三个字母组成。

样例解释：第一个字符固定A，那么符合要求的字符串是ABC,ACB。而AAB字符串包括AA这个回文子串，ACA本身就是回文串，一次类推。

对于50%的数据，$k\leq5,L\leq10$

对于另30%的数据，$s=0$

对于100%的数据$1\leq k,L\leq 10^{18},0\leq s\leq L,1\leq w\leq k,1\leq p\leq 10^9$



---

---
title: "[NOI Online 2021 提高组] 积木小赛"
layout: "post"
diff: 普及+/提高
pid: P7469
tag: ['字符串', '2021', '哈希 hashing', 'NOI Online']
---
# [NOI Online 2021 提高组] 积木小赛
## 题目描述

Alice 和 Bob 最近热衷于玩一个游戏——积木小赛。

Alice 和 Bob 初始时各有 $n$ 块积木从左至右排成一排，每块积木都被标上了一个英文小写字母。

Alice 可以从自己的积木中丢掉任意多块（也可以不丢）；Bob 可以从自己的积木中丢掉最左边的一段连续的积木和最右边的一段连续的积木（也可以有一边不丢或者两边都不丢）。两人都不能丢掉自己所有的积木。然后 Alice 和 Bob 会分别将自己剩下的积木按原来的顺序重新排成一排。

Alice 和 Bob 都忙着去玩游戏了，于是想请你帮他们算一下，有多少种不同的情况下他们最后剩下的两排积木是相同的。

两排积木相同，当且仅当这两排积木块数相同且每一个位置上的字母都对应相同。

两种情况不同，当且仅当 Alice（或者 Bob）剩下的积木在两种情况中不同。
## 输入格式

第一行一个正整数 $n$，表示积木的块数。

第二行一个长度为 $n$ 的小写字母串 $s$，表示 Alice 初始的那一排积木，其中第 $i$ 个字母 $s_i$ 表示第 $i$ 块积木上的字母。

第三行一个长度为 $n$ 的小写字母串 $t$，表示 Bob 初始的那一排积木，其中第 $i$ 个字母 $t_i$ 表示第 $i$ 块积木上的字母。
## 输出格式

一行一个非负整数表示答案。
## 样例

### 样例输入 #1
```
5
bcabc
bbcca
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
20
egebejbhcfabgegjgiig
edfbhhighajibcgfecef
```
### 样例输出 #2
```
34
```
## 提示

对于所有测试点：$1\le n \le 3000$，$s$ 与 $t$ 中只包含英文小写字母。

测试点 $1$ 满足：$n\le3000$，$s$ 与 $t$ 中只包含同一种字母。

测试点 $2,3,4$ 满足：$n\le100$。

测试点 $5,6,7$ 满足：$n\le500$。

测试点 $8,9,10$ 满足：$n\le3000$。

感谢 [w33z8kqrqk8zzzx33](https://www.luogu.com.cn/user/220037) 提供测试数据。


---

---
title: "[USACO23OPEN] Moo Language B"
layout: "post"
diff: 普及+/提高
pid: P9184
tag: ['模拟', '字符串', '贪心', 'USACO', '2023', 'Special Judge']
---
# [USACO23OPEN] Moo Language B
## 题目背景

Farmer John is interested in better interacting with his fellow cows, so he
decided he will learn the moo language!
## 题目描述

Moo language is actually quite similar to English, but more minimalistic. There
are only four types of words: nouns, transitive verbs, intransitive verbs, and
conjunctions. Every two consecutive words must be separated by a space.  There
are also only two types of punctuation: periods and commas.  When a period or
comma appears after a word, it appears directly after the word, and is then
followed  by a space if another word appears next.

A sentence needs to follow one of the following formats:
- Type 1: noun + intransitive verb.
- Type 2: noun + transitive verb + noun(s). Specifically, at least one noun
must follow the transitive verb, and there must be a comma in front of every 
following noun besides the first following noun.

Two sentences may be joined into a compound sentence if a conjunction is placed
in between them.  The resulting compound sentence cannot be further joined with
other sentences or other compound sentences.  Every sentence (or compound
sentence, if two sentences are joined) must end with a period.

Farmer John has a word bank of $N$ words, $C$ commas, and $P$ periods. He may only use a word or punctuation mark as
many times as it appears in the word bank. Help him output a sequence of
sentences containing the maximum possible number of words.

Each input file contains $T$ independent instances of this
problem.

## 输入格式

The first line contains $T$, the number of instances. Each instance is specified
as follows:

The first line consists of three integers $N, C$ and $P$.

The $N$ following lines will consist of two strings. The first string will be
the word itself that FJ can use (a string of at least $1$ and at most $10$ lowercase
letters), and the second string will be either one of the following: noun,
transitive-verb, intransitive-verb, or conjunction, denoting the type of the
word. It is possible the same word occurs more than once in FJ's word bank, but
it will always have the same type each time it appears.
## 输出格式

In the first line, output the maximum possible number of words.

In the second line, output any sequence of sentences with the maximum possible
number of words. Any valid sequence will be accepted.

**The grader is sensitive to whitespace, so make sure not to output any
extraneous spaces, particularly at the end of each line.**
## 样例

### 样例输入 #1
```
3
1 1 1
bessie noun
10 5 4
bessie noun
taught transitive-verb
flew intransitive-verb
elsie noun
farmer noun
john noun
and conjunction
and conjunction
nhoj noun
mooed intransitive-verb
24 5 4
but conjunction
bessie noun
taught transitive-verb
flew intransitive-verb
elsie noun
farmer noun
john noun
and conjunction
and conjunction
nhoj noun
mooed intransitive-verb
bob noun
impressed transitive-verb
cow noun
impressed transitive-verb
leaped intransitive-verb
elsie noun
bella noun
buttercup noun
pushed transitive-verb
mooed intransitive-verb
envy noun
john noun
nhoj noun

```
### 样例输出 #1
```
0

9
nhoj mooed. farmer taught elsie, bessie and john flew.
23
nhoj mooed. nhoj impressed john, farmer, elsie, bessie and cow impressed bob. bella pushed elsie and buttercup flew. envy mooed but john leaped.
```
## 提示

$1\le T\le 100$，$1 \leq P,C\le N \leq 10^3$.

- Inputs 2-6: $N\le 10$.
- Inputs 7-11: $N\le 100$.
- Inputs 12-16: $N\le 1000$.
- Inputs with remainder 2 when divided by 5: There are no transitive
verbs.
- Inputs with remainder 3 when divided by 5: There are no intransitive
verbs.
- Inputs with remainder 4 when divided by 5: There are no conjunctions.
## 题目翻译

### 题目背景

FJ 对与奶牛更好地互动感兴趣，所以他决定学习 moo 语言！

### 题目描述

moo 语言与英语相似，但更为简单。单词只有四种类型：名词、及物动词、不及物动词和连词，每两个单词之间必须用空格隔开。标点符号仅包含逗号和句号，它会跟在单词后面，若该标点符号后面存在单词，则需要隔一个空格再放单词。

对于每个句子，都需要遵循以下格式中的一条：

1. 名词+不及物动词。
2. 名词+及物动词+名词（可以有多个）。及物动词后面必须有至少一个名词。除及物动词后面的第一个名词外，后面的每个名词前面都必须加一个逗号。

也可以在两个句子之间加一个连词，形成复合句，复合句不能与其他句子用连词连接。每一个句子（包括复合句）都必须以句号结尾。

FJ 的词库中有 $N$ 个单词、$C$ 个逗号和 $P$ 个句号。每个单词的使用次数不能超过这个单词在词库中出现的次数。现在，你要帮他输出几个符合以上要求的句子，使总单词数尽量多。

每个输入文件中共包含 $T$ 组样例。

### 输入格式

第一行输入 $T$，表示样例组数。对于每组样例，格式如下：

第一行输入三个正整数 $N$、$C$ 和 $P$。

在接下来的 $N$ 行，每行输入两个字符串。第一个字符串输入一个 FJ 可以用的单词（全为小写字母，长度为 $1$ 至 $10$），第二个字符串为以下字符串中的任意一个，表示该单词的类型：

- `noun`（名词）；
- `transitive-verb`（及物动词）；
- `intransitive-verb`（不及物动词）；
- `conjunction`（连词）。

同一个单词可能在词库中出现多次，但是每次出现时它们的类型都相同。

### 输出格式

第一行输出组成符合以上要求的句子序列的最大单词数。

在第二行中，输出句子序列，使单词数最多。本题开启 SPJ，任何符合以上要求的句子序列均可通过。

**请不要输出多余的空格，尤其是在每行末尾。**

### 数据范围

$1 \leq T \leq 100$，$1 \leq P, C \leq N \leq 10^3$。

- 输入 2-6：$N \leq 10$。
- 输入 7-11：$N \leq 100$。
- 输入 12-16：$N \leq 1000$。
- 输入编号除以 5 余 2 的测试点：没有及物动词。
- 输入编号除以 5 余 3 的测试点：没有不及物动词。
- 输入编号除以 5 余 4 的测试点：没有连词。

translated by [liyuanchen2021](https://www.luogu.com.cn/user/557680)


---

---
title: "[CCC 2023 S3] Palindromic Poster"
layout: "post"
diff: 普及+/提高
pid: P9326
tag: ['模拟', '字符串', '2023', 'Special Judge', 'CCC（加拿大）', '分类讨论']
---
# [CCC 2023 S3] Palindromic Poster
## 题目描述

Ryo and Kita are designing a new poster for Kessoku Band. After some furious brainstorming, they came to the conclusion that the poster should come in the form of a $2\text{-D}$ grid of lowercase English letters (i.e. `a` to `z`), with $N$ rows and $M$ columns.

Furthermore, it is known that Ryo and Kita both have peculiar tastes in palindromes. Ryo will only be satisfied with the poster if exactly $R$ of its rows are palindromes, and Kita will only be satisfied with the poster if exactly $C$ of its columns are palindromes. Can you design a poster that will satisfy both Ryo and Kita, or determine that it is impossible to do so?

**Note**: A string is considered a palindrome if it is the same when read forwards and backwards. For example, `kayak` and `bb` are palindromes, whereas `guitar` and `live` are not.

## 输入格式

The first and only line of input consists of $4$ space-separated integers $N, M, R$, and $C$.

The following table shows how the available $15$ marks are distributed.

| Marks | Bounds on $N$ | Bounds on $M$ | Bounds on $R$ | Bounds on $C$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $2$ marks | $2 \leq N \leq 2000$ | $2 \leq M \leq 2000$ | $R = 1$ | $C = 1$ |
| $2$ marks | $N = 2$ | $M = 2$ | $0 \leq R \leq N$ | $0 \leq C \leq M$ |
| $4$ marks | $N = 2$ | $2 \leq M \leq 2000$ | $0 \leq R \leq N$ | $0 \leq C \leq M$ |
| $7$ marks | $2 \leq N \leq 2000$ | $2 \leq M \leq 2000$ | $0 \leq R \leq N$ | $0 \leq C \leq M$ |


## 输出格式

If it is impossible to design a poster that will satisfy both Ryo and Kita, output `IMPOSSIBLE` on a single line.

Otherwise, your output should contain $N$ lines, each consisting of $M$ lowercase English letters, representing your poster design. If there are multiple possible designs, output any ofthem.
## 样例

### 样例输入 #1
```
4 5 1 2
```
### 样例输出 #1
```
union
radar
badge
anime
```
### 样例输入 #2
```
2 2 2 1
```
### 样例输出 #2
```
IMPOSSIBLE
```
## 提示

Explanation of Output for Sample Input $1$：

In the given design, only the second row (namely `radar`) and the second and third columns (namely `naan` and `iddi`) are palindromes. Since exactly $R = 1$ of the rows and $C = 2$ of the
columns are palindromes, this is an acceptable design.

Explanation of Output for Sample Input $2$：

In this case, it can be proven that it is impossible to satisfy both Ryo and Kita.

**本题采用捆绑测试**：

- Subtask 1（2 points）：数据保证 $2 \leq N \leq 2000$，$2\leq M\leq 2000$，$R = 1$，$C = 1$。

- Subtask 2（2 points）：数据保证 $N = 2$，$M = 2$，$0\leq R\leq N$，$0\leq C\leq M$。

- Subtask 3（4 points）：数据保证 $N = 2$，$2\leq M \leq2000$，$0\leq R\leq N$，$0\leq C\leq M$。

- Subtask 4（7 points）：数据保证 $2\leq N\leq 2000$，$2\leq M \leq2000$，$0\leq R\leq N$，$0\leq C\leq M$。
## 题目翻译

Ryo 和 Kita 正在为 Kessoku 乐队设计一张新的海报，他们两个人都有各自不同的审美，但都同时认为一份符合他们审美的海报的内容应该都为小写字母，且大小为 $N \times M$。Ryo 认为当有 $R$ 数量的行是回文时，这个海报是符合其审美的；Kita 认为当有 $C$ 数量的列是回文时，这个海报是符合其审美的。

现在分别给出 $N,M,R,C$，问你是否可以构造出一个 $N \times M$ 的海报满足要求，可以就输出你的方案，不行的话输出 `IMPOSSIBLE`。


---

---
title: "[CERC2019] ABB"
layout: "post"
diff: 普及+/提高
pid: P9606
tag: ['字符串', '2019', '哈希 hashing', 'KMP 算法', 'Manacher 算法', 'ICPC']
---
# [CERC2019] ABB
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[ABB](https://contest.felk.cvut.cz/19cerc/solved/abb.pdf)」**
## 题目描述

Fernando 受雇于滑铁卢大学，负责完成该大学不久前开始的一个开发项目。在校园外，该大学希望为重要的外国游客和合作者建造具有代表性的平房街。

目前，这条街只建了一部分，它从湖岸开始，一直延伸到森林尽头。Fernando 的任务是通过在森林尽头建造更多的平房来完成这条街。所有现有的平房都坐落在街道的一侧，新的平房应该建在同一侧。这些平房有各种各样的类型，漆成各种各样的颜色。

在 Fernando 看来，整条街的布局有点混乱。他担心增加新平房后，它会看起来更加混乱。所以他想通过为新平房选择合适的颜色来增加一些排列顺序。当项目完成时，平房的整个颜色序列将是对称的，也就是说，从街道的两端观察时，颜色序列是相同的。

在其他问题中，Fernando 想知道，在满足平房颜色限制的情况下，他最少需要用来建造和适当染色才能完成项目的新平房数量。

### 简要题意

求使给定小写字母字符串成为回文串需在字符串末尾加入字母的最少数量。
## 输入格式

第一行包含一个整数 $N\ (1\le N\le 4\times 10^5)$，代表街道上现有平房的数量。

第二行包含一个由 $N$ 个小写字母（从 `a` 到 `z`）组成的字符串，代表从湖岸开始的街道现有的平房颜色顺序，其中不同的字母表示不同的颜色。
## 输出格式

输出一个整数，代表满足 Fernando 要求的新平房的最少数量。
## 样例

### 样例输入 #1
```
3
abb

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
12
recakjenecep

```
### 样例输出 #2
```
11

```
### 样例输入 #3
```
15
murderforajarof

```
### 样例输出 #3
```
6

```


---

