---
title: "[常州市赛 2023] 红绿灯"
layout: "post"
diff: 普及+/提高
pid: B4221
tag: ['2023', '数论', '江苏', '最大公约数 gcd', '中国剩余定理 CRT', '科创活动', '小学活动']
---
# [常州市赛 2023] 红绿灯
## 题目背景

搬运自 <http://czoj.com.cn/p/678>。数据为民间数据。
## 题目描述

小 X 家门前有两个红绿灯，小 X 做完了数学作业，闲着无聊便在窗边观察。他发现这两个红绿灯亮红灯和亮绿灯的时间是相等的，第一个红绿灯亮 $p$ 秒绿灯，再亮 $p$ 秒红灯……，第二个红绿灯亮 $q$ 秒绿灯，再亮 $q$ 秒红灯……，如此循环往复。

现在恰好两个红绿灯都从红灯变成了绿灯，小 X 想要知道未来的 $2\times p\times q$ 秒内，有多少秒满足两个红绿灯都亮绿灯。
## 输入格式

第一行 $2$ 个正整数 $p,q$，含义见题面。
## 输出格式

输出一行一个整数表示在未来的 $2\times p\times q$ 秒内，有多少秒满足两个红绿灯都亮绿灯。
## 样例

### 样例输入 #1
```
2 3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
18 66
```
### 样例输出 #2
```
612
```
### 样例输入 #3
```
2 255
```
### 样例输出 #3
```
128
```
## 提示

### 样例 $\textbf 1$ 解释

在未来的 $12$ 秒内，第一个红绿灯在第 $1,2,5,6,9,10$ 秒亮绿灯。

第一个红绿灯在第 $1,2,3,7,8,9$ 秒亮绿灯。

在第 $1,2,9$ 秒时，同时亮绿灯，一共 $3$ 秒。

### 数据范围

本题共有 $12$ 个测试点。

|测试点编号|$p,q$|特殊性质|
|:-:|:-:|:-:|
|$1\sim3$|$1\le p,q\le 1000$|无|
|$4\sim5$|$1=p\le q\le 10^9$|无|
|$6\sim9$|$1\le p,q\le10^9$|$p\perp q$|
|$10\sim12$|$1\le p,q\le 10^9$|无|


---

---
title: "[USACO24JAN] Cowlendar S"
layout: "post"
diff: 普及+/提高
pid: P10136
tag: ['USACO', '2024', '数论', '鸽笼原理']
---
# [USACO24JAN] Cowlendar S
## 题目描述

Bessie 在一个陌生的星球上醒来。这个星球上有 $N$（$1\le N\le 10^4$）个月，分别有 $a_1,\ldots,a_N$ 天（$1\le a_i\le 4\cdot 10^9$，所有 $a_i$ 均为整数）。此外，这个星球上还存在周，一周为 $L$ 天，其中 $L$ 是一个正整数。有趣的是，Bessie 知道以下事情：

- 对于正确的 $L$，每个月至少有 $4$ 周。
- 对于正确的 $L$，$a_i\bmod L$ 至多有 $3$ 个不同值。

不幸的是，Bessie 忘记了 $L$ 是多少！请通过输出 $L$ 的所有可能值之和来帮助她。

**注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C/C++ 中的 "long long"）。**
## 输入格式

输入的第一行包含一个整数 $N$。第二行包含 $N$ 个空格分隔的整数 $a_1,\ldots,a_N$。
## 输出格式

输出一个整数，为 $L$ 的所有可能值之和。
## 样例

### 样例输入 #1
```
12
31 28 31 30 31 30 31 31 30 31 30 31
```
### 样例输出 #1
```
28
```
### 样例输入 #2
```
4
31 35 28 29
```
### 样例输出 #2
```
23
```
## 提示

### 样例解释 1

$L$ 的可能值为 $1$，$2$，$3$，$4$，$5$，$6$ 和 $7$。例如，$L=7$ 是合法的，因为每个月的至少有 $4\cdot 7=28$ 天，且每个月的天数模 $7$ 的余数均为 $0$，$2$ 或 $3$。

### 样例解释 2

$L$ 的可能值为 $1$，$2$，$3$，$4$，$6$ 和 $7$。例如，$L=6$ 是合法的，因为每个月的至少有 $4\cdot 6=24$ 天，且每个月的天数模 $6$ 的余数均为 $1$，$4$ 或 $5$。

### 测试点性质

- 测试点 $3-4$：$1\le a_i\le 10^6$。
- 测试点 $5-14$：没有额外限制。


---

---
title: "[GESP202406 七级] 区间乘积"
layout: "post"
diff: 普及+/提高
pid: P10724
tag: ['2024', '数论', 'GESP']
---
# [GESP202406 七级] 区间乘积
## 题目描述

小杨有一个包含 $n$ 个正整数的序列 $A=[a_1,a_2,\ldots,a_n]$。

小杨想知道有多少对 $\langle l,r\rangle(1\leq l\leq r\leq n)$ 满足 $a_l\times a_{l+1}\times\ldots\times a_r$ 为完全平方数。

一个正整数 $x$ 为完全平方数当且仅当存在一个正整数 $y$ 使得 $x=y\times y$。

## 输入格式

第一行包含一个正整数 $n$，代表正整数个数。

第二行包含 $n$ 个正整数 $a_i$，代表序列 $A$。
## 输出格式

输出一个整数，代表满足要求的 $\langle l,r\rangle$ 数量。

## 样例

### 样例输入 #1
```
5
3 2 4 3 2
```
### 样例输出 #1
```
2
```
## 提示

### 样例解释

满足条件的 $\langle l,r\rangle$ 有  $\langle 1,5\rangle$ 和 $\langle 3,3\rangle$。


### 数据范围

子任务编号|数据点占比|$n$|$a_i$
:-:|:-:|:-:|:-:
$1$|$20\%$|$\leq 10^5$|$1\leq a_i\leq 2$
$2$|$40\%$|$\leq 100$|$1\leq a_i\leq 30$
$3$|$40\%$|$\leq 10^5$|$1\leq a_i\leq 30$



---

---
title: "【MX-X3-T3】「RiOI-4」GCD 与 LCM 问题"
layout: "post"
diff: 普及+/提高
pid: P11036
tag: ['数论', 'Special Judge', 'O2优化', 'Ad-hoc', '梦熊比赛']
---
# 【MX-X3-T3】「RiOI-4」GCD 与 LCM 问题
## 题目背景

原题链接：<https://oier.team/problems/X3D>。

---

「既然你说你不了解她，为什么又可以断言她一定是因为……」

是呀，自己对零羽还了解的确实不够多……泠珞这样想着。

在残缺的记忆当中，她只能想起，她和零羽的最大公约数，就是「音乐」。

还缺了什么呢？泠珞不知道。她只知道，那所缺失的，和「音乐」加起来，就是她的一切。一切的总和。

**滴答，滴答**。叮咚，叮咚。如果把长短不一、断断续续的钢琴声拼接在一起，能够回忆起什么吗。
## 题目描述

给定一个正整数 $a$，请你构造三个正整数 $b,c,d$ 使得 $a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)$。一个测试点内有多组数据。

由于出题人想把自己 QQ 号写题目里，你需要保证 $b,c,d\le 1\,634\,826\,193$。

**如有多种可能的答案，输出任意一个均可。**
## 输入格式

**第一行一个正整数 $t$ 表示数据组数。**

接下来 $t$ 行每行一个正整数 $a$。
## 输出格式

输出 $t$ 行，每行三个正整数 $b,c,d$。

**如有多种可能的答案，输出任意一个均可。**
## 样例

### 样例输入 #1
```
4
1
2
3
20120712
```
### 样例输出 #1
```
7 9 2
9 6 8
5 9 2
8065343 8750 6446
```
## 提示

**【样例解释】**

样例的构造为：

$1+7+9+2=19=\gcd(1,7)+\operatorname{lcm}(9,2)$  
$2+9+6+8=25=\gcd(2,9)+\operatorname{lcm}(6,8)$  
$3+5+9+2=19=\gcd(3,5)+\operatorname{lcm}(9,2)$  
$20\,120\,712+8\,065\,343+8\,750+6\,446=28\,201\,251=\gcd(20\,120\,712,8\,065\,343)+\operatorname{lcm}(8\,750,6\,446)$

容易验证均满足要求。

**【数据范围】**

|测试点|分数|$t\le$|$a\le$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$2$|$10$|$10$||
|$2$|$5$|$50$|$50$||
|$3$|$17$|$10^6$|$5\times10^8$||
|$4$|$29$|$10^6$|$10^9-1$|$a$ 为奇数|
|$5$|$47$|$2\times10^6$|$10^9$||

对于 $100\%$ 的数据，$1\le t\le2\times10^6$，$1\le a\le 10^9$。


---

---
title: "神奇的小江鸟"
layout: "post"
diff: 普及+/提高
pid: P11312
tag: ['数学', '数论', '洛谷原创', 'Special Judge', 'O2优化', '枚举', '洛谷月赛', '调和级数']
---
# 神奇的小江鸟
## 题目背景

[The English statement for T5](https://www.luogu.com.cn/problem/U508234)

You can also see the pdf at the bottom of the chinese problem statement.

感谢 [ineverleft](https://www.luogu.com.cn/user/362679) 为本题提供的本地调试 checker。

「愿有前程可奔赴，亦有岁月可回首。」
## 题目描述

小 $ \zeta $ 在探险过程中看到了一个大锁。

这个大锁有 $ n $ 个拨圈，第 $ i $ 个拨圈的拨动范围为 $ l_i $ 到 $ r_i $ 之间（含两个边界）的所有整数（保证 $ l_i \le r_i $）。

我们定义这个大锁的「自由度」为所有拨圈上的数的**最大公约数**，当锁的「自由度」大于等于 $ k $ 时，会被打开。

请你找到一种锁的开启方案，或报告无解。
## 输入格式

**本题单测试点内含有多组测试数据**，第一行一个整数 $ T $，代表数据组数。

对于每组数据：

第一行两个整数 $ n,k $，分别代表拨圈数量和自由度限制。

接下来 $ n $ 行，每行两个整数 $ l_i,r_i $，含义见题目描述。
## 输出格式

对于每组数据：

* 如果有解，第一行输出 `Yes`，下一行输出 $ n $ 个空格分隔的整数，第 $ i $ 个为你的构造方案中第 $ i $ 个拨圈显示的数。**本题使用了 Special Judge，符合要求的答案均判对。**

* 否则，输出一行 `No` 表示无解。
## 样例

### 样例输入 #1
```
1
5 10
1 12
44 50
9 10
88 99
29 99
```
### 样例输出 #1
```
Yes
10 50 10 90 30
```
### 样例输入 #2
```
2
3 11
99 10003
39 299
39 10003
5 55
1 54
1 20
1 300
1 300
1 300
```
### 样例输出 #2
```
Yes
123 246 369
No
```
### 样例输入 #3
```
3
6 1
1 10
1 10
1 10
1 10
1 10
1 10
5 4
11 15
6 10
9 14
20 23
27 29
5 11
20 30
50 70
111 120
72 77
119 121
```
### 样例输出 #3
```
Yes
1 1 4 5 1 4
Yes
14 7 14 21 28
Yes
24 60 120 72 120
```
### 样例输入 #4
```
4
3 33
32 34
65 67
97 101
3 5
299 99494993
499 49992999
499 39999939
4 25
719 830
2194 2893
132 142
199 225
3 10
140 143
131 135
238 241
```
### 样例输出 #4
```
Yes
33 66 99
Yes
1919810 11400 51400
Yes
729 2700 135 216
No
```
### 样例输入 #5
```
1
10 7
77 77
82 174
77 77
82 174
77 77
82 174
77 77
82 174
77 77
82 174
```
### 样例输出 #5
```
Yes
77 154 77 154 77 154 77 154 77 154
```
## 提示

**【样例 1 解释】**

唯一的一组数据 $ \gcd $ 为 $ 10 $。

五个样例自测均可使用下发的附件。**请注意部分样例可能存在多解，样例输出仅列举了一组可行解。**

**【数据规模与约定】**

对于 $ 100\% $ 的数据，$ 1 \le T \le 5 $，$ 2 \le n \le 10^4 $，$ 1 \le l_i \le r_i \le 10^9 $，$ 1 \le k \le 1000 $。

**本题开启子任务捆绑测试。**

* Subtask 1（10 pts）：$ k=1 $。
* Subtask 2（15 pts）：$ n \le 10 $，$ r_i - l_i + 1 \le 5 $。
* Subtask 3（15 pts）：$ r_i \le 10^3 $。
* Subtask 4（10 pts）：$ k \le 5 $，$ l_i,r_i $ 均在 $ 1 \le l_i \le r_i \le 10^9 $ 范围内等概率随机生成，该子任务只有 $ 1 $ 个测试点。
* Subtask 5（15 pts）：对于每组数据，$ \exist 1 \le i \le n,l_i=r_i $。
* Subtask 6（35 pts）：无特殊限制。

**【关于附加文件】**

**本题下发了 `checker.cpp` 作为自测器。**

请将输入内容、你的程序输出、参考答案输出分别放置在 `restore.in`、`restore.out`、`restore.ans` 中，这三个文件必须与 `checker.cpp` 在同一目录下，运行 `checker.cpp`，终端上会给出自测结果。

**你需要保证你的输入满足 $ 100\% $ 数据范围的要求。**

注意，如果你的输入/输出/答案的格式和范围不正确的话，`checker.cpp` 出现的结果是不可预料的。因此，**请先确保你的三个文件格式正确。**


---

---
title: "界分数"
layout: "post"
diff: 普及+/提高
pid: P11397
tag: ['2024', '数论', '洛谷原创', '洛谷月赛', 'Ad-hoc', '洛谷比赛']
---
# 界分数
## 题目背景

[标分数](https://www.luogu.com.cn/problem/P8319)
## 题目描述

定义函数 $f(x)$：

有一个 $\frac{0}{x}$ 的分数。你可以进行以下两种操作直到这个分数为 $1$：

1. 分子 $+1$，然后如果这个分数可以约分，约分到最简形式。
2. 分子分母同时 $+1$，然后如果这个分数可以约分，约分到最简形式。

$f(x)$ 的值为最小操作次数。

给定 $n$，求 $\sum\limits_{i=1}^n f(i) \bmod 998244353$。
## 输入格式

一行一个正整数 $n$。
## 输出格式

一行一个自然数，表示答案。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
114
```
### 样例输出 #2
```
785
```
### 样例输入 #3
```
114514
```
### 样例输出 #3
```
1930181
```
## 提示

【样例解释】

$f(1)=1$，$f(2)=2$，$f(3)=3$，$f(4)=3$（$\frac{1}{4}\rightarrow\frac{1}{2}\rightarrow 1$）。

【数据范围】

对于全部数据，$1\le n \le 10^{18}$。

**本题采用捆绑测试。**

| Subtask 编号 | 特殊性质 | 分值 |
| -----------: | -----------: |-----------: |
| 0 | $n=5$ | $5$ |
| 1 | $n\le 10$ | $20$ |
| 2 | $n\le 10^3$ | $40$ |
| 3 | $n\le 10^6$ | $25$ |
| 4 | 无特殊性质 | $10$ |




---

---
title: "[USACO25FEB] Transforming Pairs S"
layout: "post"
diff: 普及+/提高
pid: P11841
tag: ['USACO', '2025', '数论', '最大公约数 gcd']
---
# [USACO25FEB] Transforming Pairs S
## 题目描述

聪明奶牛 Bessie 发现了一种新的迷恋——数学魔法！一天，当她在 Farmer John 牧场的草地上小跑时，她偶然发现了两堆有魔法的干草。第一堆包含 $a$ 捆干草，第二堆包含 $b$ 捆干草（$1\le a,b\le 10^{18}$）。

在干草堆边上，半埋在泥土里，她发现了一卷古老的卷轴。当她展开卷轴时，发光的字母揭示了一个预言：

奉大草原之令，被选中者需令此平凡之干草堆转为恰好 $c$ 捆及 $d$ 捆——不可多，亦不可少。

Bessie 意识到她只能施展以下两种魔法：

- 她可以施法召唤新的干草捆以增加第一堆的大小，增加的数量等于当前第二堆的数量。
- 她可以施法召唤新的干草捆以增加第二堆的大小，增加的数量等于当前第一堆的数量。

她必须逐次执行这些操作，但可以任意顺序执行任意多次。她必须恰好使第一堆达到 $c$ 捆，第二堆达到 $d$ 捆（$1\le c,d\le 10^{18}$）。

对于 $T$（$1\le T\le 10^4$）个独立的测试用例中的每一个，输出实现预言所需的最小操作次数，或者如果不可能实现时输出 -1。
## 输入格式

输入的第一行包含 $T$。

以下 $T$ 行，每行包含四个整数 $a$，$b$，$c$，$d$。
## 输出格式

输出 $T$ 行，为每一个测试用例的答案。

## 样例

### 样例输入 #1
```
4
5 3 5 2
5 3 8 19
5 3 19 8
5 3 5 3
```
### 样例输出 #1
```
-1
3
-1
0
```
### 样例输入 #2
```
1
1 1 1 1000000000000000000
```
### 样例输出 #2
```
999999999999999999
```
## 提示

样例 1 解释：

在第一个测试用例中，由于 $b>d$，但操作只可能增加 $b$，因此不可能实现。

在第二个测试用例中，最初两堆有 $(5, 3)$ 捆。Bessie 可以将第一堆增加第二堆的数量，得到 $(8, 3)$ 捆。然后 Bessie 可以将第二堆增加第一堆的新数量，并执行该操作两次，得到 $(8, 11)$ 并最后得到 $(8, 19)$ 捆。这与 $c$ 和 $d$ 一致，且是达到目标的最小操作次数。

注意，第三个测试用例的答案与第二个不同，因为 $c$ 和 $d$ 的值交换了（堆的顺序有影响）。

在第四个测试用例中，不需要任何操作。

- 测试点 $3\sim 4$：$\max(c, d) \le 20 \cdot\min(a, b)$。
- 测试点 $5\sim 7$：$T \le 10$ 且 $a,b,c,d\le 10^6$。
- 测试点 $8\sim 12$：没有额外限制。


---

---
title: "面包题"
layout: "post"
diff: 普及+/提高
pid: P12021
tag: ['数论', 'Fibonacci 数列', '整除分块']
---
# 面包题
## 题目背景

面包（bread）
## 题目描述

从 $1 \sim n$ 的自然数中选出若干个数（可以不选），满足以下条件：

- 若选择了 $x$，则不能选择 $kx$。

求总共有多少种选法（不考虑顺序）。

答案需要**对** ${998244353}$ **取模**。
## 输入格式

第一行一个正整数 $T$ 表示数据组数。

接下来每组数据一行输入两个正整数：$n,k$，含义同题面所示。
## 输出格式

一共 $T$ 行，每行一个正整数表示对应的答案。
## 样例

### 样例输入 #1
```
3
4 2
2 2
10 20
```
### 样例输出 #1
```
10
3
1024
```
## 提示

### 样例解释

对于第一组数据，满足条件的 $S$ 有 $\varnothing,\{1\},\{1,3\},\{1,4\},\{1,3,4\},\{2\},\{2,3\},\{3\},\{3,4\},\{4\}$，共 $10$ 种 $S$ 满足上述条件。

对于第二组数据，满足条件的 $S$ 有 $\varnothing,\{1\},\{2\}$，共 $3$ 种 $S$ 满足上述条件。

对于第三组数据，任意满足 $S\subseteq\{1,2,3,\dots,10\}$ 的 $S$ 都符合条件，因此答案为 $2^{10}=1024$。

### 数据范围

对于 $20\%$ 的数据：$1\leq T\leq 10$，$2\leq n,k \leq 15$

对于 $40\%$ 的数据：$1\leq T\leq 10^2$，$2\leq n,k \leq 10^5$

对于 $100\%$ 的数据：$1\leq T\leq 10^5$，$2\leq n,k \leq 10^9$



---

---
title: "[蓝桥杯 2025 省 A] 黑客"
layout: "post"
diff: 普及+/提高
pid: P12142
tag: ['数学', '2025', '数论', '组合数学', '排列组合', '逆元', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 A] 黑客
## 题目描述

小蓝正在两台电脑之间拷贝数据，数据是一个 $n \times m$ 大小的正整数矩阵，因此总共有 $n \times m + 2$ 个由空格分开的整数，其中前两个整数分别为 $n$ 和 $m$。然而，有黑客入侵了小蓝的电脑，导致这 $n \times m + 2$ 个正整数的顺序被打乱了。小蓝想知道最多可能有多少个不同的原矩阵。

两个矩阵相同当且仅当它们行数相同、列数相同，且每个位置上的数相同。
## 输入格式

输入的第一行包含一个正整数 $n \times m + 2$。

第二行包含 $n \times m + 2$ 个正整数 $a_1, a_2, \cdots, a_{n \times m+2}$，相邻整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个整数表示答案。答案可能很大，请输出答案除以 $1000000007$ 的余数。
## 样例

### 样例输入 #1
```
6
2 2 1 4 3 3
```
### 样例输出 #1
```
24
```
## 提示

### 样例说明

可能的原矩阵情况包括：

1. $(n,m)=(1,4)$：有 $6$ 种原矩阵：$(2, 2, 3, 3), (2, 3, 2, 3), (2, 3, 3, 2), (3, 2, 2, 3), (3, 2, 3, 2), (3, 3, 2, 2)$；
2. $(n,m)=(4,1)$：有 $6$ 种原矩阵；
3. $(n,m)=(2,2)$：有 $12$ 种原矩阵；

总计 $6 + 6 + 12 = 24$ 种。

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$1 \leq n \times m + 2 \leq 10$；
- 对于所有评测用例，$1 \leq n \times m + 2 \leq 5 \times 10^5$，$1 \leq a_i \leq 5 \times 10^5$。


---

---
title: "[蓝桥杯 2025 省 Java B] 2 的幂"
layout: "post"
diff: 普及+/提高
pid: P12160
tag: ['动态规划 DP', '2025', '数论', '背包 DP', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 Java B] 2 的幂
## 题目描述

小明很喜欢 $2$ 的幂，所以他想对一个长度为 $n$ 的正整数数组 $\{a_1, a_2, \dots, a_n\}$ 进行改造。他可以进行如下操作任意多次（可以是 $0$ 次）：任选一个数 $a_i$ 加上任意正整数，但不能使得加完之后的结果超过 $10^5$。

在操作任意次后，小明希望所有数的乘积是 $2^k$ 的倍数。他想知道总共需要加的数的总和至少是多少？
## 输入格式

输入共两行。
- 第一行为两个正整数 $n, k$。
- 第二行为 $n$ 个由空格分开的正整数 $a_1, a_2, \dots, a_n$。
## 输出格式

输出共 $1$ 行，一个整数表示答案。如果不能满足条件，输出 $-1$。
## 样例

### 样例输入 #1
```
3 9
19 10 3
```
### 样例输出 #1
```
12
```
## 提示

### 样例说明

将三个数分别加到 $24, 16, 4$，它们的乘积为 $1536 = 2^9 \times 3$，加的数的总和为 $5 + 6 + 1 = 12$。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$n, k \leq 10$。
- 对于 $100\%$ 的评测用例，$1\leq n \leq 500$，$1\leq k \leq 5000$，$1\leq a_i \leq 100000$。


---

---
title: "[蓝桥杯 2024 国 Java B] 园丁"
layout: "post"
diff: 普及+/提高
pid: P12255
tag: ['2024', '数论', '树的遍历', '素数判断,质数,筛法', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Java B] 园丁
## 题目描述

小明是一位尽职尽责的园丁。这天他负责维护一棵树，树上有 $n$ 个结点 $1, 2, \ldots, n$，根结点为 $1$，结点 $i$ 的权值为 $a_i$。他需要更改一些结点的权值为任意正整数，使得对于任意一个至少有 $2$ 个儿子结点的结点 $i$ 满足：任意两个 $i$ 的儿子结点的权值的乘积都不是完全平方数。请问小明至少需要修改多少个结点的权值？
## 输入格式

输入共 $n+1$ 行。

第一行为一个正整数 $n$。

第二行为 $n$ 个由空格分开的正整数 $a_1, a_2, \ldots, a_n$。

后面 $n-1$ 行，每行两个正整数表示树上的一条边。
## 输出格式

输出共 $1$ 行，一个整数表示答案。
## 样例

### 样例输入 #1
```
6
1 2 9 8 4 4
1 2
1 3
1 4
2 5
2 6
```
### 样例输出 #1
```
2
```
## 提示

### 样例说明

其中一种方案：将结点 $2, 5$ 的权值分别修改为 $3, 2$。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，保证 $n \leq 10^3$。
- 对于 $100\%$ 的评测用例，保证 $1\leq n \leq 10^5$，$1 \leq a_i \leq 10^9$。


---

---
title: "[蓝桥杯 2024 国 Java A] 空间传送装置"
layout: "post"
diff: 普及+/提高
pid: P12286
tag: ['2024', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Java A] 空间传送装置
## 题目描述

蓝桥王国拥有 $42$ 座城市以及 $42$ 位骑士。这些骑士按照 $1$ 到 $42$ 的编号顺序，分别居住在对应编号的城市中。即第 $1$ 位骑士居住在城市 $1$，第 $2$ 位骑士居住在城市 $2$，依此类推。

最近，王国中引入了一项革命性技术：空间传送装置。该装置可以根据一个长度为 $42$ 的数字排列 $a$，将所有骑士一次性传送至新的城市。

排列 $a$ 必须由 $1 \sim 42$ 共 $42$ 个数字组成，且每个数字只出现一次。在传送操作中，位于城市 $i$（$i = 1, 2, 3, \cdots, 42$）的骑士会被传送到城市 $a_i$。例如，如果 $a_1$ 的值为 $3$，那么当前位于城市 $1$ 的骑士会被传送至城市 $3$。

为测试技术的可靠性，王国决定连续 $2024$ 天每天使用同一排列 $a$ 进行一次传送操作。

小蓝负责为这次测试设计排列 $a$，她的目标是确保所有骑士在经过 $2024$ 天传送后，都能返回自己的起始城市。而在此之前的任何一天，不会出现所有骑士都回到起始城市的情况。

请问，有多少种不同的数字排列 $a$ 能满足小蓝的需求？由于答案可能很大，因此你只需要将答案对 $10^9 + 7$ 取模后提交即可。

数字排列 $a$ 是由 $1$ 到 $42$ 这 $42$ 个数字按照一定顺序排列而成的序列。每个数字在排列中只能出现一次，且所有数字必须全部包含在排列中。

如果两个排列中至少有一个位置上的数字不同，则这两个排列被视为不同的数字排列。例如，$\{1, 2, 3, \cdots, 42\}$ 和 $\{1, 3, 2, \cdots, 42\}$ 就是不同的数字排列，因为它们在第二个位置上的数不相同。
## 输出格式

这是一道结果填空的题，你只需要算出结果后提交即可。本题的结果为一个整数，在提交答案时只需要**编写一个程序输出这个整数**，输出多余的内容将无法得分。


---

---
title: "「FAOI-R9」函数大师"
layout: "post"
diff: 普及+/提高
pid: P12397
tag: ['数论', '洛谷原创', 'O2优化', '枚举', '洛谷月赛']
---
# 「FAOI-R9」函数大师
## 题目背景

作为一名电脑技术大神，明月喜欢用几何画板画出各种奇形怪状函数的图象，例如 $ y=\frac{x^x}{\sin x} $，$ y=\lfloor x^{\tan x} \rfloor $，$ y=\frac{x+x^3+x^5+x^7}{1+x^2+x^4+x^6} $，它们有的连续，有的离散，有的长得很奇怪，但是作为一名中考数学 99/100 的 math master，他自信自己能掌握很多函数的规律。

于是，清风给了他一个这样的函数。
## 题目描述

清风定义函数 $ s(x)(x \in \mathbb{N^*}) $ 代表 $ x $ 在十进制表示下的的各位数字之和，即：

$$ s(x)=\sum_{i=0}^{+\infty}(\lfloor \frac{x}{10^i} \rfloor \bmod 10) $$
清风又定义 $ S_k(x) (x\in \mathbb {N^*},k\in \mathbb{N}) $，满足：

$$ S_0(x) = x,S_k(x) = s(S_{k-1}(x)) $$

清风再定义 $ f_k(x)(x\in \mathbb {N^*},k\in \mathbb{N}) $，满足：

$$ f_k(x)=\sum_{i=0}^{k}S_i(x) $$

清风把这个函数给了明月，明月自信满满地将函数输入几何画板后，显示的图象让他眼花缭乱。为了探究这个函数的性质，明月找到了你。

给定你 $ k $，每次询问给定你 $ m $，请你求出 $ y=f_k(x) $  与 $ y=m $ 两个函数图象的公共点个数，可以证明这个数值一定是有限的。
## 输入格式

第一行两个整数 $ T,k $，表示有 $ T $ 组询问，$ k $ 的意义见题目描述。

接下来 $ T $ 行，每行一个正整数，第 $ i $ 行的表示第 $ i $ 次询问的 $ m $。
## 输出格式

对于每次询问，输出公共点的个数。
## 样例

### 样例输入 #1
```
4 3
21
20
19
50
```
### 样例输出 #1
```
1
1
0
1
```
## 提示

**【样例 1 解释】**

对于样例 $ 1 $，每组数据对应的所有公共点的 $ x $ 坐标集合分别为 $ \{12\} $、$ \{5\} $、$ \varnothing $ 和 $ \{26\} $。

**【数据规模与约定】**

**本题采用捆绑测试。**

对于每个测试点，$ 1 \le T \le 10^5 $，$ 0 \le k \le 10^9 $，$ 1 \le m \le 10^{18} $。

* Subtask 1（5 pts）：$ k=0 $。
* Subtask 2（20 pts）：$ T \le 10 $，$ m \le 10^5 $，$ k \le 10 $。
* Subtask 3（25 pts）：$ T \le 10 $，$ m \le 10^6 $，$ k \le 10^4 $。
* Subtask 4（25 pts）：$ k \le 1 $。
* Subtask 5（25 pts）：无特殊限制。


---

---
title: "[GCJ 2021 #1B] Subtransmutation"
layout: "post"
diff: 普及+/提高
pid: P13030
tag: ['数学', '贪心', '2021', '数论', 'Bézout 定理', 'Google Code Jam']
---
# [GCJ 2021 #1B] Subtransmutation
## 题目描述

As the most skilled alchemist in your country, you were summoned yet again because powers beyond science were needed to satisfy your country's leader's ever increasing greed for rare metals.

Each metal is represented by a positive integer. You need to create $\mathbf{U}_{1}$ units of metal 1, $\mathbf{U}_{2}$ units of metal 2, … and $\mathbf{U}_{\mathrm{N}}$ units of metal $\mathrm{N}$. Metals $\mathrm{N}+1, \mathrm{~N}+2, \ldots$ do exist, but you are not required to create any specific amount of them. You are allowed to create excess amounts of any metal, which can just be discarded.

Unfortunately, budget cuts have left you only the materials for a simple alchemy spell. For some fixed numbers $\mathbf{A}$ and $\mathbf{B}$, with $\mathbf{A}<\mathbf{B}$, you can take one unit of metal $i$ and destroy it to create one unit of metal $(i-\mathbf{A})$ and one unit of metal $(i-\mathbf{B})$. If either of those integers is not positive, that specific unit is not created. In particular, if $i \leq \mathbf{A}$, the spell simply destroys the unit and creates nothing. If $\mathbf{A}<i \leq \mathbf{B}$ the spell destroys the unit and creates only a single unit of metal $(i-\mathbf{A})$.

You have been assigned an expert miner to assist you. The expert miner can fetch a single unit of any metal you want. From that unit, you can use your spell to create other metals and then use the spell on the resulting metals to create even more units. The picture below shows a single unit of metal 4 being converted into one unit of metal 1 and two units of metal 2 using two spells with $\mathbf{A}=1$ and $\mathbf{B}=2$.

![](https://cdn.luogu.com.cn/upload/image_hosting/imhnu3zr.png)

Metals represented by larger integers are heavier and more difficult to handle, so you want to ask the expert miner for a single unit of metal represented by the smallest possible integer that is sufficient to complete your task, or say that there is no such metal.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of two lines. The first line of a test case contains three integers $\mathbf{N}, \mathbf{A}$, and $\mathbf{B}$, representing the largest metal number that you are required to create, and the two values that define the available spell as described above, respectively. The second line of a test case contains $\mathbf{N}$ integers $\mathbf{U}_{1}, \mathbf{U}_{2}, \ldots, \mathbf{U}_{\mathbf{N}}$, representing the required units of metals $1,2, \ldots, \mathbf{N}$, respectively.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is IMPOSSIBLE if it is not possible to create all required units starting from a single unit of metal. Otherwise, $y$ is the smallest integer that represents a metal such that one unit of it is sufficient to create all the required units of metal.
## 样例

### 样例输入 #1
```
3
2 1 2
1 2
5 1 2
2 0 0 0 1
3 1 2
1 1 1
```
### 样例输出 #1
```
Case #1: 4
Case #2: 6
Case #3: 5
```
### 样例输入 #2
```
3
3 2 4
1 1 1
3 2 4
1 0 1
5 2 5
1 0 0 0 1
```
### 样例输出 #2
```
Case #1: IMPOSSIBLE
Case #2: 5
Case #3: 10
```
## 提示

**Sample Explanation**

In Sample Case #1, we require one unit of metal 1 and two units of metal 2. If we start with a single unit of metal 3, then applying the spell once will give us one unit of metal 1 and one unit of metal 2. There is no way to get an additional unit of metal 2. Similarly, starting with a single unit of metals 1 or 2 is not sufficient. However, a single unit of metal 4 is sufficient as is demonstrated in the picture in the main part of the statement.

In Sample Case #2, we can start with a single unit of metal 6 and apply the following operations:

* Apply spell on 6: $\{6\} \longrightarrow\{4,5\}$.
* Apply spell on 4: $\{4,5\} \longrightarrow\{2,3,5\}$.
* Apply spell on 2: $\{2,3,5\} \longrightarrow\{1,3,5\}$.
* Apply spell on 3: $\{1,3,5\} \longrightarrow\{1,1,2,5\}$.

Note that even though we have an extra unit of metal 2 , this solution is valid.

In Sample Case #3, we can start with a single unit of metal 5 and apply the following operations:

* Apply spell on 5: $\{5\} \longrightarrow\{3,4\}$.
* Apply spell on 4: $\{3,4\} \longrightarrow\{2,3,3\}$.
* Apply spell on 2: $\{2,3,3\} \longrightarrow\{1,3,3\}$.
* Apply spell on 3: $\{1,3,3\} \longrightarrow\{1,1,2,3\}$.

There are other ways to apply spells which also work but they all require starting with a single unit of metal 5 or higher.

Sample Test Set 2 fits the limits of Test Set 2. It will not be run against your submitted solutions.

In the first Sample Case for Test Set 2, it is impossible to start with a single unit of any metal and apply the spell with $\mathbf{A}=2$ and $\mathbf{B}=4$ several times and be left with one unit of metals $1,2$ and $3$.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{N} \leq 20$.
- $0 \leq \mathbf{U}_{\mathbf{i}} \leq 20$, for all $i$.
- $1 \leq \mathbf{U}_{\mathbf{N}}$.
- $2 \leq \mathbf{U}_{1}+\mathbf{U}_{2}+\cdots+\mathbf{U}_{\mathbf{N}}$.

**Test Set 1 (13 Pts, Visible Verdict)**

- $\mathbf{A}=1$.
- $\mathbf{B}=2$.

**Test Set 2 (18 Pts, Hidden Verdict)**

- $1 \leq \mathbf{A}<\mathbf{B} \leq 20$.


---

---
title: "[GCJ 2019 Qualification] Cryptopangrams"
layout: "post"
diff: 普及+/提高
pid: P13104
tag: ['数学', '2019', '数论', 'Google Code Jam']
---
# [GCJ 2019 Qualification] Cryptopangrams
## 题目描述

On the Code Jam team, we enjoy sending each other pangrams, which are phrases that use each letter of the English alphabet at least once. One common example of a pangram is "the quick brown fox jumps over the lazy dog". Sometimes our pangrams contain confidential information — for example, `CJ QUIZ: KNOW BEVY OF DP FLUX ALGORITHMS` — so we need to keep them secure.

We looked through a cryptography textbook for a few minutes, and we learned that it is very hard to factor products of two large prime numbers, so we devised an encryption scheme based on that fact. First, we made some preparations:

* We chose 26 different prime numbers, none of which is larger than some integer $N$.
* We sorted those primes in increasing order. Then, we assigned the smallest prime to the letter A, the second smallest prime to the letter B, and so on.
* Everyone on the team memorized this list.

Now, whenever we want to send a pangram as a message, we first remove all spacing to form a plaintext message. Then we write down the product of the prime for the first letter of the plaintext and the prime for the second letter of the plaintext. Then we write down the product of the primes for the second and third plaintext letters, and so on, ending with the product of the primes for the next-to-last and last plaintext letters. This new list of values is our ciphertext. The number of values is one smaller than the number of characters in the plaintext message.

For example, suppose that $N = 103$ and we chose to use the first 26 odd prime numbers, because we worry that it is too easy to factor even numbers. Then $A = 3$, $B = 5$, $C = 7$, $D = 11$, and so on, up to $Z = 103$. Also suppose that we want to encrypt the `CJ QUIZ KNOW BEVY OF DP FLUX ALGORITHMS` pangram above, so our plaintext is `CJQUIZKNOWBEVYOFDPFLUXALGORITHMS`. Then the first value in our ciphertext is $7$ (the prime for `C`) times $31$ (the prime for `J`) $= 217$; the next value is $1891$, and so on, ending with $3053$.

We will give you a ciphertext message and the value of $N$ that we used. We will not tell you which primes we used, or how to decrypt the ciphertext. Do you think you can recover the plaintext anyway?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow; each test case consists of two lines. The first line contains two integers: $N$, as described above, and $L$, the length of the list of values in the ciphertext. The second line contains $L$ integers: the list of values in the ciphertext.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is a string of $L + 1$ uppercase English alphabet letters: the plaintext.
## 样例

### 样例输入 #1
```
2
103 31
217 1891 4819 2291 2987 3811 1739 2491 4717 445 65 1079 8383 5353 901 187 649 1003 697 3239 7663 291 123 779 1007 3551 1943 2117 1679 989 3053
10000 25
3292937 175597 18779 50429 375469 1651121 2102 3722 2376497 611683 489059 2328901 3150061 829981 421301 76409 38477 291931 730241 959821 1664197 3057407 4267589 4729181 5335543
```
### 样例输出 #1
```
Case #1: CJQUIZKNOWBEVYOFDPFLUXALGORITHMS
Case #2: SUBDERMATOGLYPHICFJKNQVWXZ
```
## 提示

**Limits**

- $1 \leq T \leq 100$.
- $25 \leq L \leq 100$.
- The plaintext contains each English alphabet letter at least once.

**Test set 1 (10 Pts, Visible)**

- $101 \leq N \leq 10000$.

**Test set 2 (15 Pts, Hidden)**

- $101 \leq N \leq 10^{100}$.


---

---
title: "[GCJ 2011 #2] Expensive Dinner"
layout: "post"
diff: 普及+/提高
pid: P13376
tag: ['数学', '2011', '二分', '数论', '素数判断,质数,筛法', 'Google Code Jam']
---
# [GCJ 2011 #2] Expensive Dinner
## 题目描述

Your friends are all going to a restaurant for dinner tonight. They're all very good at math, but they're all very strange: your $a^{\text{th}}$ friend (starting from 1) will be unhappy unless the total cost of the meal is a positive integer, and is divisible by $a$.

Your friends enter the restaurant one at a time. As soon as someone enters the restaurant, if that person is unhappy then the group will call a waiter immediately.

As long as there is at least one unhappy person in the restaurant, one of those unhappy people will buy the lowest-cost item that will make him or her happy. This will continue until nobody in the restaurant is unhappy, and then the waiter will leave. Fortunately, the restaurant sells food at every integer price. See the explanation of the first test case for an example.

Your friends could choose to enter the restaurant in any order. After the waiter has been called, if there is more than one unhappy person in the restaurant, any one of those unhappy people could choose to buy something first. The way in which all of those choices are made could have an effect on how many times the group calls a waiter.

As the owner of the restaurant, you employ some very tired waiters. You want to calculate the spread of your friends: the difference between the maximum number of times they might call a waiter and the minimum number of times they might call a waiter.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, each on its own line. Each test case will contain one integer $N$, the number of friends you have.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the spread for that test case.
## 样例

### 样例输入 #1
```
4
1
3
6
16
```
### 样例输出 #1
```
Case #1: 0
Case #2: 1
Case #3: 2
Case #4: 5
```
## 提示

**Sample Explanation**

In Case #2, suppose your friends arrive in the order $[1, 2, 3]$. Then #1 arrives; is unhappy; calls a waiter; and buys something costing $1$. Now nobody is unhappy. #2 arrives next; is unhappy; calls a waiter; and buys something costing $1$ (for a total of $2$). Now nobody is unhappy. #3 arrives next; is unhappy; calls a waiter; and buys something costing $1$ (for a total of $3$). Now #2 is unhappy, and buys something costing $1$ (for a total of $4$). Now #3 is unhappy, and buys something costing $2$ (for a total of $6$). Finally nobody is unhappy, and a waiter was called three times.

Suppose instead that your friends arrived in the order $[3, 1, 2]$. Then #3 arrives; is unhappy; calls a waiter; and buys something costing $3$. Now nobody is unhappy. #1 arrives next; nobody is unhappy. #2 arrives next; is unhappy; calls a waiter; and buys something costing $1$ (for a total of $4$). Now #3 is unhappy, and buys something costing $2$ (for a total of $6$). Now nobody is unhappy, and a waiter was called two times. The spread is $1$.

**Limits**

**Small dataset (13 Pts, Test set 1 - Visible)**

- $1 \leq T \leq 100$.
- $1 \leq N \leq 1000$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (17 Pts, Test set 2 - Hidden)**

- $1 \leq T \leq 1000$.
- $1 \leq N \leq 10^{12}$.
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[GCJ 2010 Qualification] Fair Warning"
layout: "post"
diff: 普及+/提高
pid: P13388
tag: ['数学', '高精度', '2010', '数论', 'Google Code Jam']
---
# [GCJ 2010 Qualification] Fair Warning
## 题目背景

Fortunately for the peoples of the Jamcode system, "the apocalypse" turned out to be a mistranslation of "the giant party." Nobody from Jamcode IX bothered to pass this along, because they were having so much fun.
## 题目描述

On our planet, Jamcode IX, three Great Events occurred. They happened $26000$, $11000$ and $6000$ slarboseconds ago. In $4000$ slarboseconds, the amount of time since all of those events will be multiples of $5000$ slarboseconds, the largest possible amount... and the apocalypse will come.

Luckily for you, you live on Jamcode X! The apocalypse came on Jamcode IX less than a year ago. But Jamcode X has a worrying prophecy: "After the moment of reckoning, on the first optimum anniversary of the N Great Events, the apocalypse will come. 64 bits will not save you. You have been warned."

The people of Jamcode X are very concerned by this prophecy. All of the Great Events have already happened, and their times have been measured to the nearest slarbosecond; but nobody knows when their optimum anniversary will occur. After studying the diary of a scientist from Jamcode IX, scientists working on the problem have come up with a theory:

The moment of reckoning is now, the moment you solve this problem. At some time $y \geqslant 0$ slarboseconds from now, the number of slarboseconds since each of the Great Events will be divisible by some maximum number $T$. If you can find the smallest value of $y$ that gives this largest possible $T$, that will give you the optimum anniversary when the apocalypse will come.

On Jamcode IX, for example, there were 3 Great Events and they happened $26000$, $11000$ and $6000$ slarboseconds before the moment of reckoning. $4000$ slarboseconds later, the amount of time since each event was a multiple of $T=5000$ slarboseconds, and the apocalypse came.

Your job is to compute the amount of time until the apocalypse comes. But remember the prophecy: even though the people of Jamcode X have been solving problems for two years, and 64-bit integers have always been enough, they might not always be enough now or in the future.

## 输入格式

The first line of the input gives the number of test cases, $C$. $C$ lines follow. Each starts with a single integer $N$, which is followed by a space and then $N$ space-separated integers $t_i$, the number of slarboseconds since Great Event i occurred.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1) and $y$ is the minimum number of slarboseconds until $t_i + y$ is a multiple of the largest possible integer factor $T$ for all $i$.
## 样例

### 样例输入 #1
```
3
3 26000000 11000000 6000000
3 1 10 11
2 800000000000000000001 900000000000000000001
```
### 样例输出 #1
```
Case #1: 4000000
Case #2: 0
Case #3: 99999999999999999999
```
## 提示

**Limits**

- $1 \leqslant C \leqslant 100.$
- $t_{i} \neq t_{j}$ for some $i, j$.

**Small dataset (10 Pts, Test set 1 - Visible)**

- $2 \leqslant N \leqslant 3.$
- $1 \leqslant t_{i} \leqslant 10^{8}.$

**Large dataset (23 Pts, Test set 2 - Hidden)**

- $2 \leqslant N \leqslant 1000.$
- $1 \leqslant t_{i} \leqslant 10^{50}.$


---

---
title: "[GCJ 2010 #3] De-RNG-ed"
layout: "post"
diff: 普及+/提高
pid: P13403
tag: ['2010', '数论', '扩展欧几里德算法', '分类讨论', 'Google Code Jam']
---
# [GCJ 2010 #3] De-RNG-ed
## 题目描述

I want to make an online poker website. A very important component of such a system is the random number generator. It needs to be fast and random enough. Here is a compromise I came up with. I need a way to generate random numbers of length at most $D$. My plan is to select a prime number $P \leq 10^D$. I am also going to pick non-negative integers $A$ and $B$. Finally, I'm going to pick an integer seed $S$ between $0$ and $P-1$, inclusive.

To output my sequence of pseudo-random numbers, I'm going to first output $S$ and then compute the new value of $S$ like this:

$$S := (A\times S + B) \bmod P$$

Then I will output the new value of $S$ as the next number in the sequence and update $S$ again by using the same formula. I can repeat this as many times as I want.

Do you think that this is a good random number generator? Can you write a program that takes $K$ consecutive elements of a sequence that was generated by my random number generator, and prints the next element of the sequence?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one starts with a line containing $D$ and $K$. The next line contains $K$ consecutive elements generated by a random number generator of the kind described above.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is either the next number in the sequence, or the string "I don't know." if the answer is ambiguous.
## 样例

### 样例输入 #1
```
3
2 10
0 1 2 3 4 5 6 7 8 9
3 1
13
1 5
6 6 6 6 6
```
### 样例输出 #1
```
Case #1: 10
Case #2: I don't know.
Case #3: 6
```
## 提示

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq K \leq 10$.
- The $K$ integers will be consecutive elements of a sequence generated by a random number generator of the type described above.

**Small dataset (4 Pts, Test set 1 - Visible)**

- $1 \leq D \leq 4$.

**Large dataset (10 Pts, Test set 2 - Hidden)**

- $1 \leq D \leq 6$.



---

---
title: "[GCJ 2008 #1C] Ugly Numbers"
layout: "post"
diff: 普及+/提高
pid: P13464
tag: ['动态规划 DP', '数学', '2008', '数论', 'Google Code Jam']
---
# [GCJ 2008 #1C] Ugly Numbers
## 题目描述

Once upon a time in a strange situation, people called a number *ugly* if it was divisible by any of the one-digit primes ($2$, $3$, $5$ or $7$). Thus, $14$ is ugly, but $13$ is fine. $39$ is ugly, but $121$ is not. Note that $0$ is ugly. Also note that negative numbers can also be ugly; $-14$ and $-39$ are examples of such numbers.

One day on your free time, you are gazing at a string of digits, something like:

$123456$

You are amused by how many possibilities there are if you are allowed to insert *plus* or *minus* signs between the digits. For example you can make

$1 + 234 - 5 + 6 = 236$

which is ugly. Or

$123 + 4 - 56 = 71$

which is not ugly.

It is easy to count the number of different ways you can play with the digits: Between each two adjacent digits you may choose put a plus sign, a minus sign, or nothing. Therefore, if you start with $D$ digits there are $3^{D-1}$ expressions you can make.

Note that it is fine to have leading zeros for a number. If the string is "01023", then "01023", "0+1-02+3" and "01-023" are legal expressions.

Your task is simple: Among the $3^{D-1}$ expressions, count how many of them evaluate to an ugly number.
## 输入格式

The first line of the input file contains the number of cases, $N$. Each test case will be a single line containing a non-empty string of decimal digits.

## 输出格式

For each test case, you should output a line

Case #X: Y

where $X$ is the case number, starting from $1$, and $Y$ is the number of expressions that evaluate to an ugly number.
## 样例

### 样例输入 #1
```
4
1
9
011
12345
```
### 样例输出 #1
```
Case #1: 0
Case #2: 1
Case #3: 6
Case #4: 64
```
## 提示

**Limits**

- $0 \leq N \leq 100$.
- The string in each test case will be non-empty and will contain only characters '0' through '9'.

**Small dataset (Test set 1 - Visible)**

- Each string is no more than 13 characters long.

**Large dataset (Test set 2 - Hidden)**

- Each string is no more than 40 characters long.



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
title: "「Wdoi-1.5」魔理沙的计算器"
layout: "post"
diff: 普及+/提高
pid: P8116
tag: ['数论', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「Wdoi-1.5」魔理沙的计算器
## 题目背景

魔理沙是普通而平凡的魔法使。在解决了大大小小的异变后，她终于攒足了足够多的钱在香霖堂里购置了一台 $\verb!Carno!$ 计算器，用来计算魔女之汤各种配料的含量之比。

魔理沙早就听闻灵梦通过河童重工网络[入手了一部 $\verb!Casio!$ 计算器](https://www.luogu.com.cn/problem/P5515)，来计算神社的香火钱，却买到了假货，最多只能显示整数部分（下取整）。而魔理沙的这部可以精确到小数点后面若干位（下取整）的计算器。更高级的是，这部计算器还可以支持其他的进制，其强大的功能高出了灵梦一大截。因此作为灵梦真挚的朋友，魔理沙希望向灵梦表达真挚的遗憾之情。

正当魔理沙打算出发之时，她发现虽然 $\verb!Carno!$ 计算器不会导致一些特别大的误差，但是在计算除法时仍然会出现一定的问题。考虑将计算器的进制调整为 $10$ 进制，而计算器屏幕上最多可以显示 $5$ 位数字（小数点不计入显示位数）。比如，魔理沙希望计算 $1\div 3$ 的值，那么真正显示在屏幕上的则是：

$$
0.3333
$$

按照道理上来讲，$1\div(1\div 3)$ 结果应当等于 $3$。但出乎意料的是，当魔理沙输入 $1\div 0.3333$ 后，得到的结果却是：

$$
3.0003
$$

这当然只是一个个例。当魔理沙计算 $1\div(1\div 4)$ 时，屏幕上显示出了正确的数字。

为了防止在表达遗憾之情的时候自己的计算器也出了漏子，魔理沙希望找到有多少个数字使得计算出的结果是正确的，因此她向你求助了。
## 题目描述

魔理沙的计算器可以进行 $b$ 进制的运算，屏幕上可以显示 $k$ 个数字（不包含小数点）。进行计算后，若某个数字超出了屏幕，就会被**直接舍去**（例如 $b=10$ 时 $1\div 7=0.142857\cdots$，若屏幕大小为 $4$，那么最终显示为 $0.142$）。

魔理沙用计算器计算了 $1\div n=n'$，再计算 $1\div n'=n''$（$n'$ 和 $n''$ 均为显示在屏幕上的结果）。魔理沙希望知道，有多少个正整数 $n$ 使得 $n=n''$。你只需要输出这个答案对 $998,244,353$ 取模后的结果即可。
## 输入格式

- 第一行有一个正整数 $T$，表示数据组数。
- 接下来 $T$ 行，每行有两个正整数 $b,k$，分别表示计算器的进制、屏幕上能显示的数字个数。
## 输出格式

- 输出共 $T$ 行。
- 每行输出一个整数。第 $i$ 行的整数表示第 $i$ 组数据中合法的 $n$ 的总数对 $998,244,353$ 取模后的结果。
## 样例

### 样例输入 #1
```
3
4 2
5 3
12 99
```
### 样例输出 #1
```
3
3
19503
```
## 提示

### 样例解释

- 对于第一组询问，符合条件的数（转换成十进制）为 $1,2,4$。
- 对于第二组询问，符合条件的数（转换成十进制）为 $1,5,25$。

### 数据范围及约定

$$
\def{\arraystretch}{1.5}
\begin{array}{|c|c|c|c|c|c|}\hline
\textbf{subtask}&\textbf{分值} & \bm{b\le} & \bm {k\le } & \textbf{特殊性质} & \textbf{subtask 依赖} \cr\hline
1 & 20 & 10 & 7 & - &-\cr\hline
2 & 20 & 10^5 & 2 & k=2&-\cr\hline
3 & 10 & 10^5 & 3 & k=3&- \cr\hline
4 & 50& 10^5 & 500 & -&1,2,3\cr\hline
\end{array}
$$

对于 $100\%$ 的数据，满足 $1\le T\le 10$，$2\le b\le 10^5$，$1\le k\le 500$。


---

---
title: "「EZEC-11」Sequence"
layout: "post"
diff: 普及+/提高
pid: P8178
tag: ['数论', 'O2优化', '逆元', '洛谷月赛']
---
# 「EZEC-11」Sequence
## 题目描述

已知数列 $f$ 满足 $f_n=a_nf_{n-1}+b_n\ (n\ge 1)$。

问是否存在非负整数 $f_0$，使得 $\forall 1\le i\le k$，$f_i$ 为**质数** $p_i$ 的倍数。
## 输入格式

**本题有多组测试数据**。

第一行一个整数 $T$，表示测试数据组数。

对于每组测试数据：

- 第一行一个整数 $k$。
- 第二行 $k$ 个整数 $a_1,a_2,\dots,a_k$。
- 第三行 $k$ 个整数 $b_1,b_2,\dots,b_k$。
- 第四行 $k$ 个整数 $p_1,p_2,\dots,p_k$，**保证 $p$ 为质数**。
## 输出格式

对于每组测试数据：

- 一行一个字符串，若存在满足条件的 $f_0$ 则输出 `Yes`，否则输出 `No`。
## 样例

### 样例输入 #1
```
2
3
1 1 1
2 2 2
3 5 7
3
1 1 1
2 2 2
3 3 3
```
### 样例输出 #1
```
Yes
No
```
## 提示

**【样例 1 解释】**

对于第一组测试数据，一个可行的解为 $f_0=1$，此时 $f_1=3,f_2=5,f_3=7$。

对于第二组测试数据，没有满足条件的 $f_0$。

**【数据规模与约定】**

**本题采用捆绑测试。**

-  Subtask 1（10 points）：$k=1$。
-  Subtask 2（20 points）：$k\le 2$。
-  Subtask 3（20 points）：$k\le 5$，$p_i\le 20$。
-  Subtask 4（50 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le T\le 10$，$1\le k\le 10^3$，$0\le a_i,b_i\le 10^9$，$2\le p_i\le 10^9$，**$p$ 为质数**。


---

---
title: "[蓝桥杯 2017 国 C] 小数第 n 位"
layout: "post"
diff: 普及+/提高
pid: P8652
tag: ['模拟', '2017', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2017 国 C] 小数第 n 位
## 题目描述

我们知道，整数做除法时，有时得到有限小数，有时得到无限循环小数。

如果我们把有限小数的末尾加上无限多个 $0$，它们就有了统一的形式。

本题的任务是：在上面的约定下，求整数除法小数点后的第 $n$ 位开始的 $3$ 位数。
## 输入格式

一行三个整数：$a$，$b$，$n$，用空格分开。$a$ 是被除数，$b$ 是除数，$n$ 是所求的小数后位置（$0<a,b,n<10^9$）
## 输出格式

一行 $3$ 位数字，表示：$a$ 除以 $b$，小数后第 $n$ 位开始的 $3$ 位数字。
## 样例

### 样例输入 #1
```
1 8 1
```
### 样例输出 #1
```
125
```
### 样例输入 #2
```
1 8 3
```
### 样例输出 #2
```
500
```
### 样例输入 #3
```
282866 999000 6
```
### 样例输出 #3
```
914
```
## 提示

时限 1 秒, 256M。蓝桥杯 2017 年第八届国赛


---

---
title: "[蓝桥杯 2022 省 A] 数的拆分"
layout: "post"
diff: 普及+/提高
pid: P8778
tag: ['2022', '数论', '素数判断,质数,筛法', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 A] 数的拆分
## 题目描述

给定 $T$ 个正整数 $a_{i}$，分别问每个 $a_{i}$ 能否表示为 $x_{1}^{y_{1}} \cdot x_{2}^{y_{2}}$ 的形式，其中 $x_{1}, x_{2}$ 为正整数，$y_{1}, y_{2}$ 为大于等于 $2$ 的正整数。
## 输入格式

输入第一行包含一个整数 $T$ 表示询问次数。

接下来 $T$ 行，每行包含一个正整数 $a_{i}$ 。
## 输出格式

对于每次询问，如果 $a_{i}$ 能够表示为题目描述的形式则输出 `yes`，否则输出 `no`。
## 样例

### 样例输入 #1
```
7
2
6
12
4
8
24
72
```
### 样例输出 #1
```
no
no
no
yes
yes
no
yes
```
## 提示

**【样例说明】**

第 $4,5,7$ 个数分别可以表示为:

$$
\begin{aligned}
&a_{4}=2^{2} \times 1^{2} ; \\
&a_{5}=2^{3} \times 1^{2} ; \\
&a_{7}=2^{3} \times 3^{2} 。
\end{aligned}
$$

**【评测用例规模与约定】**

对于 $10 \%$ 的评测用例，$1 \leq T \leq 200, a_{i} \leq 10^{9}$;

对于 $30 \%$ 的评测用例，$1 \leq T \leq 300, a_{i} \leq 10^{18}$;

对于 $60 \%$ 的评测用例，$1 \leq T \leq 10000, a_{i} \leq 10^{18}$;

对于所有评测用例，$1 \leq T \leq 100000,1 \leq a_{i} \leq 10^{18}$ 。 

蓝桥杯 2022 省赛 A 组 I 题。


---

---
title: "[蓝桥杯 2022 国 A] 最大公约数"
layout: "post"
diff: 普及+/提高
pid: P8792
tag: ['贪心', '2022', '数论', '枚举', '蓝桥杯国赛']
---
# [蓝桥杯 2022 国 A] 最大公约数
## 题目描述

给定一个数组，每次操作可以选择数组中任意两个相邻的元素 $x, y$ 并将其中的一个元素替换为 $\gcd(x, y)$，其中 $\gcd(x, y)$ 表示 $x$ 和 $y$ 的最大公约数。请问最少需要多少次操作才能让整个数组只含 $1$。
## 输入格式

输入的第一行包含一个整数 $n$，表示数组长度。

第二行包含 $n$ 个整数 $a_1, a_2,\dots, a_n$，相邻两个整数之间用一个空格分隔。
## 输出格式

输出一行包含一个整数，表示最少操作次数。如果无论怎么操作都无法满足要求，输出 $-1$。
## 样例

### 样例输入 #1
```
3
4 6 9
```
### 样例输出 #1
```
4
```
## 提示

**【评测用例规模与约定】**

- 对于 $30\%$ 的评测用例，$n \leq 500$，$a_i \leq 1000$；
- 对于 $50\%$ 的评测用例，$n \leq 5000$，$a_i \leq 10^6$；
- 对于所有评测用例，$1 \leq n \leq 10^5$，$1 \leq a_i \leq 10^9$。

蓝桥杯 2022 国赛 A 组 D 题。


---

---
title: "[蓝桥杯 2022 国 A] 选素数"
layout: "post"
diff: 普及+/提高
pid: P8795
tag: ['2022', '数论', '枚举', '蓝桥杯国赛']
---
# [蓝桥杯 2022 国 A] 选素数
## 题目描述

小蓝有一个数 $x$，每次操作小蓝会选择一个小于 $x$ 的素数 $p$，然后在 $x$ 成为 $p$ 的倍数前不断将 $x$ 加 $1$，（如果 $x$ 一开始就是 $p$ 的倍数则 $x$ 不变）。

小乔看到了小蓝进行了 $2$ 次上述操作后得到的结果 $n$，他想知道 $x$ 在一开始是多少。如果有多种可能，他想知道 $x$  一开始最小可以是多少，而如果不存在任何解，说明小乔看错了，此时请输出 $-1$。
## 输入格式

输入一行包含一个整数 $n$，表示经过两次操作后 $x$ 的值。
## 输出格式

输出一行包含一个整数表示 $x$ 的初始值。如果有多个解，输出最小的。如果不存在解，请输出 $-1$。
## 样例

### 样例输入 #1
```
22
```
### 样例输出 #1
```
8
```
## 提示

**【评测用例规模与约定】**

- 对于 $60\%$ 的评测用例，$1 \leq n \leq 5000$；
- 对于所有评测用例，$1 \leq n \leq 10^6$。

蓝桥杯 2022 国赛 A 组 G 题。


---

---
title: "「GMOI R1-T3」Number Pair"
layout: "post"
diff: 普及+/提高
pid: P8926
tag: ['数学', '数论', 'O2优化', '最大公约数 gcd']
---
# 「GMOI R1-T3」Number Pair
## 题目描述

我们定义满足如下条件的数对 $(x,y)$ 叫做奇妙数对：

$k \times \gcd(x,y)=\operatorname{lcm}(x,y)$ 并且 $P \le \gcd(x,y) \le Q$（保证 $P \le Q$）。

有 $T$ 组数据，对于每一组数据，给定 $k,P,Q$ 三个数，求符合条件的数对 $(x,y)$ 的对数。

**答案对 $10^9+7$ 取模。**
## 输入格式

**本题有多组数据。**

第一行一个整数 $T$，表示数据数量。

接下来 $T$ 行，每行三个整数 $k,P,Q$。
## 输出格式

对于每一组数据，给出对应答案，每组数据一行。


## 样例

### 样例输入 #1
```
5
10 1 3
30 1 5
997 24 35
34 39 99
210 1000 1001
```
### 样例输出 #1
```
12
40
24
244
32
```
## 提示

**注意并不寻常的时间限制。**

对于 $100\%$ 的数据 $1 \le k \le 10^{16}$，$1 \le T \le 50$，$1 \le P \le Q \le 2\times 10^9$。

| 测试点 | $k$ | $T$ | $P$ | $Q$ | 总分 |
| :----------: | :----------: | :----------: | :-------------: | :----------: | :----------: |
| $1\sim 3$ | $k \le 3$ | $T=1$ | $P=1$ | $Q=1$ | $15$ |
| $4\sim 8$ | $k \le 100$ | $T \le 8$ | $P \le 30$ |  $Q \le 30$ |$15$ |
| $9\sim 13$ | $k \le 10^3$ | $T \le 50$ | $P \le 500$ | $Q \le 500$ | $25$ |
| $14\sim 18$ | $k \le 10^{12}$ | $T \le 50$ | $P \le 10^4$ | $Q \le 10^4$ | $15$ |
| $19\sim 22$ | $k \le 10^{13}$ | $T \le 50$ | $P \le 10^6$ | $Q \le 10^6$ | $12$ |
| $23\sim 28$ | $k \le 10^{16}$ | $T \le 50$ | $P \le 2\times10^9$ | $Q \le 2\times10^9$ | $18$ |

**本题保证 $k$ 随机生成，并不存在极限卡人数据，时限已经开到 std 两倍，请各位选手放心。**


---

---
title: "除法题"
layout: "post"
diff: 普及+/提高
pid: P9148
tag: ['数学', '数论', '洛谷原创', 'O2优化', '组合数学', '前缀和', '洛谷月赛']
---
# 除法题
## 题目描述

给定大小为 $n$ 的集合 $a$，保证其中元素互不相同且均为正整数。

如果我们从中**按顺序**取出三个元素 $a, b, c$，则共有 $n \cdot (n-1) \cdot (n-2)$ 种不同的选择方案。

现在对于一种选择方案 $(a,b,c)$，定义其权值为 $\Bigl\lfloor\dfrac{a}{b}\Bigr\rfloor\Bigl\lfloor\dfrac{a}{c}\Bigr\rfloor\Bigl\lfloor\dfrac{b}{c}\Bigr\rfloor$。

你需要对所有的选择方案计算权值的总和，你只需输出这个总和对 $2^{32}$ 取模的结果。

注：$\lfloor a\rfloor$ 表示不大于 $a$ 的最大整数。如 $\lfloor 2.4\rfloor=2$、$\lfloor 5\rfloor=5$。
## 输入格式

第一行，一个正整数 $n$，表示序列的长度。

第二行，$n$ 个正整数 $a_1, a_2, \ldots, a_n$，每个数描述了集合 $a$ 的一个元素，这些数互不相同。
## 输出格式

输出一行一个整数，表示答案对 $2^{32}$ 取模的结果。
## 样例

### 样例输入 #1
```
4
1 2 3 4

```
### 样例输出 #1
```
36

```
### 样例输入 #2
```
6
8 6 4 2 10 15

```
### 样例输出 #2
```
268

```
## 提示

**【样例解释 \#1】**

对于样例 \#1，权值不为 $0$ 的选择方案只有以下几种：

- $(3,2,1)$，权值为 $6$。
- $(4,2,1)$，权值为 $16$。
- $(4,3,1)$，权值为 $12$。
- $(4,3,2)$，权值为 $2$。

因此，样例 \#1 的答案为 $6+16+12+2=36$。

---

**【数据范围】**

对于 $100\%$ 的数据，$1 \le n, a_i \le 5000$。

**本题采用捆绑测试。**

|子任务|$n$|特殊性质|分值|
|-|-|-|-|
|1|$=3$||$10$|
|2|$\le 300$||$20$|
|3|$\le 2000$||$20$|
|4||A|$20$|
|5|||$30$|

特殊性质 A：保证 $a_i=i$。

---

**【提示】**

本题中大部分算法都拥有较小的常数，请相信你的复杂度。


---

