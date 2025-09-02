---
title: "[语言月赛202212] 狠狠地切割(Easy Version)"
layout: "post"
diff: 普及-
pid: B3691
tag: ['二分', '2022', 'O2优化', '排序', '双指针 two-pointer', '语言月赛']
---
# [语言月赛202212] 狠狠地切割(Easy Version)
## 题目描述

现给你一个长度为 $n$ 的序列 $a _ 1, \cdots, a _ n$ 和 $m$ 个互不相同的整数 $b _ 1, \cdots, b _ m$。你需要按照这 $m$ 个数对序列 $a$ 进行**狠狠地切割**。

具体的，对于一个数字 $i \in [1, n]$，如果存在一个整数 $j \in [1, m]$，使得 $a _ i = b _ j$，则将位置 $i$ 称为一个**切割点**。对序列 $a$ 中的每一个切割点，我们在这个位置进行一次**狠狠地切割**。方法是，将该位置的数字去除，然后在这个位置将其左右的**序列/片段**一分两半。

如果对**狠狠地切割**的定义有疑问，可以参照「样例 #1」及「样例解释 #1」进行理解。

你需要计算，在进行了所有可能的**狠狠地切割**后，序列被切割为了多少**片段**。

特别的，如果在切割后，某一段内没有数组，那这一段不可被叫做**片段**。同样的，如果 $1$ 或 $n$ 为切割点，其与开头和结尾之间也不存在片段。

如果对**片段**的概念有疑问，可以参照「样例 #2」及「样例解释 #2」进行理解。
## 输入格式

第一行为两个整数，依次表示序列 $a$ 的长度 $n$ 和序列 $b$ 的长度 $m$。  
第二行有 $n$ 个整数，第 $i$ 个整数表示 $a_i$。  
第三行有 $m$ 个整数，第 $i$ 个整数表示 $b_i$。
## 输出格式


输出一个整数，代表**狠狠地切割**后的**片段**的个数。
## 样例

### 样例输入 #1
```
6 2
3 4 3 5 2 6
5 4
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
6 3
3 4 3 5 2 6
3 5 6
```
### 样例输出 #2
```
2
```
## 提示

### 样例 1 解释

在**狠狠地切割**前，序列 $a$ 如下所示：

$$\begin{matrix} 3 & 4 & 3 & 5 & 2 & 6 \end{matrix}$$

容易知道，第二个位置和第四个位置为切割点，我们使用 `|` 对其进行替换，代表去除工作：

$$\begin{matrix} 3 & | & 3 & | & 2 & 6 \end{matrix}$$

我们将片段进行简单的标记：

$$\begin{matrix} \overbrace{3} ^ \text{片段 1} & | & \overbrace{3} ^ \text{片段 2} & | & \overbrace{2 \quad 6} ^ \text{片段 3} \end{matrix}$$

共计 $3$ 个片段。

### 样例 2 解释

以下我们展示去除之后的序列：

$$\begin{matrix} | & 4 & | & | & 2 & | \end{matrix}$$

我们将片段进行简单的标记：

$$\begin{matrix} \overbrace{\vphantom{0}} ^ \text{\color{red}这个不是片段} | & \overbrace{4} ^ \text{片段 1} & | & \overbrace{\vphantom{0}} ^ \text{\color{red}这个不是片段} & | & \overbrace{2} ^ \text{片段 2} & | \overbrace{\vphantom{0}} ^ \text{\color{red}这个不是片段}\end{matrix}$$

共计 $2$ 个片段。

### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n, m \leq 10$。
- 对于 $70\%$ 的数据，保证 $n, m \leq 5 \times 10 ^ 3$。
- 对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 5 \times 10 ^ 5$，$1 \leq a_i,b_i \leq 5 \times 10^{6}$。

### 提示
本题输入规模较大，建议考虑使用较快的读入读出方式。


---

---
title: "[GESP202406 四级] 宝箱"
layout: "post"
diff: 普及-
pid: B4006
tag: ['2024', '排序', '双指针 two-pointer', 'GESP']
---
# [GESP202406 四级] 宝箱
## 题目描述

小杨发现了 $n$ 个宝箱，其中第 $i$ 个宝箱的价值是 $a_i$。

小杨可以选择一些宝箱放入背包并带走，但是小杨的背包比较特殊，假设小杨选择的宝箱中最大价值为 $x$，最小价值为 $y$，小杨需要保证 $x-y\leq k$，否则小杨的背包会损坏。

小杨想知道背包不损坏的情况下，自己能够带走宝箱的总价值最大是多少。
## 输入格式

第一行包含两个正整数 $n,k$，含义如题面所示。

第二行包含 $n$ 个正整数 $a_1,a_2,\dots,a_n$，代表宝箱的价值。
## 输出格式

输出一个整数，代表带走宝箱的最大总价值。
## 样例

### 样例输入 #1
```
5 1
1 2 3 1 2
```
### 样例输出 #1
```
7
```
## 提示

**【样例解释】**

在背包不损坏的情况下，小杨可以拿走两个价值为 $2$ 的宝箱和一个价值为 $3$ 的宝箱。

**【数据范围】**

对于全部数据，保证有 $1\leq n\leq 1000$，$0\leq k\leq 1000$，$1\leq a_i\leq 1000$。


---

---
title: "[海淀区小学组 2023] 赛车游戏"
layout: "post"
diff: 普及-
pid: B4196
tag: ['数学', '2023', '北京', 'Special Judge', '双指针 two-pointer', '科创活动', '小学活动']
---
# [海淀区小学组 2023] 赛车游戏
## 题目背景

2023 年海淀区中小学生信息学竞赛小学组复赛题目，数据为洛谷自造。
## 题目描述

陶陶和天天喜欢玩赛车游戏，在游戏中有一条直赛道长度为 $ l $，陶陶的赛车在起点为 $0$ 的位置，准备向终点行驶，天天的赛车在终点为 $ l $ 的位置，准备向起点行驶。赛车的初始速度都为 $1$，在赛道上有 $ n $ 个加速带，第 $ i $ 加速带的位置为 $ a_i $，当小车经过一个加速带时，它的速度就增加 $1$，请你帮忙计算出两车相遇时间。
## 输入格式

第一行仅有一个整数 $ T $ 表示测试数据的组数，每组测试数据的第一行包含两个整数 $ n $ 和 $ l $，第二行包含 $ n $ 个整数 $ a_1, a_2, a_3, \ldots, a_n $。
## 输出格式

共有 $ T $ 行，每行仅有一个数，依次对应每组测试数据的答案，表示两车相遇的时间。允许绝对误差、相对误差不超过 $ 10^{-6} $。
## 样例

### 样例输入 #1
```
5
2 10
1 9
1 10
1
5 7
1 2 3 4 6
2 1000000000
413470354 982876160
9 478
1 10 25 33 239 445 453 468 477
```
### 样例输出 #1
```
3.000000000000000
3.666666666666667
2.047619047619048
329737645.7500000
53.70000000000000
```
## 提示

对于 $100\%$ 的数据： $ 1 \leq T \leq 10^4 $， $ 1 \leq n \leq 10^5 $， $ 1 \leq l \leq 10^9 $， $ 1 \leq a_1 < a_2 < \ldots < a_n < l $。

保证所有测试用例中 $ n $ 的总和不超过 $ 10^5 $。


---

---
title: "[常州市赛 2024] 盒子"
layout: "post"
diff: 普及-
pid: B4228
tag: ['贪心', '2024', '江苏', '排序', '双指针 two-pointer', '科创活动', '小学活动']
---
# [常州市赛 2024] 盒子
## 题目背景

搬运自 <http://czoj.com.cn/p/954>。数据为民间数据。
## 题目描述

小 Y 有 $n$ 个盒子，第 $i$ 个盒子的大小是 $a_i$，小 Y 保证 $a_i$ 一定是 $2$ 的若干次方，比如 $1,2,4,8,16,32,64,128,256,512,1024\cdots$，一个大小为 $a_i$ 的盒子的容量是 $\dfrac{a_i}2$，就是说它可以装下总大小不超过 $\dfrac{a_i}2$ 的其他盒子，特别地，大小为 $1$ 的盒子不能装下其他盒子。并且，装在盒子里的盒子也可以装其他盒子，比如，大小为 $8$ 的盒子可以装下一个大小为 $4$ 的盒子且大小为 $4$ 的盒子事先已经装了一个大小为 $2$ 的盒子。

现在小 Y 想知道，最少能有多少个不被其他盒子装下的盒子？
## 输入格式

第一行 $1$ 个正整数 $n$，表示盒子的数量。

第二行 $n$ 个正整数 $a_i$，表示每个盒子的大小，保证 $a_i$ 一定是 $2$ 的若干次方。
## 输出格式

一行一个正整数表示最少能有多少个不被其他盒子装下的盒子。


## 样例

### 样例输入 #1
```
5
1 2 1 1 8
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3
1 1 1
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
6
1 1 1 4 1 2
```
### 样例输出 #3
```
3
```
### 样例输入 #4
```
3
8 4 2
```
### 样例输出 #4
```
1
```
## 提示

### 样例 $\textbf 1$ 解释
![](https://cdn.luogu.com.cn/upload/image_hosting/uo8jxn0g.png)
图中盒子内部的灰色部分表示盒子不能用来装东西的一半容量，白色部分表示能用来装东西的一半容量，图中只有最大的盒子没有被装在其它盒子中，因此答案为 $1$。
### 样例 $\textbf 2$ 解释
![](https://cdn.luogu.com.cn/upload/image_hosting/ygt207eh.png)
### 样例 $\textbf 3$ 解释
![](https://cdn.luogu.com.cn/upload/image_hosting/znl0c65g.png)
### 样例 $\textbf 4$ 解释
![](https://cdn.luogu.com.cn/upload/image_hosting/pis9wn32.png)
### 数据范围
参考数据：$2^{60}=1\ 152\ 921\ 504\ 606\ 846\ 976$。

对于所有数据，$1≤n≤10^5, 1≤a_i≤2^{60}$。

|测试点编号|特殊性质|
|:-:|:-:|
|$1\sim3$|$1\le n\le 3$|
|$4\sim5$|$1\le a_i\le 4$|
|$6\sim9$|$1\le n\le 1000$|
|$10\sim12$|无|


---

---
title: "[海淀区小学组 2025] 最短字符串"
layout: "post"
diff: 普及-
pid: B4240
tag: ['2025', '北京', '双指针 two-pointer', '科创活动', '小学活动']
---
# [海淀区小学组 2025] 最短字符串
## 题目背景

2025 年海淀区中小学生信息学竞赛小学组复赛题目，数据为洛谷自造。
## 题目描述

给定一个仅由大小写字母构成的长度为 $n$ 的字符串 $S$，求字符串 $S$ 的一个子串 $T$，使得字符串 $T$ 中包含字符串 $S$ 中所有种类的字母（区分大小写），输出子串 $T$ 的最小长度。例如，如果 $S = \tt{aaBCCe}$，则 $S$ 中包含的不同种类的字母有 $\tt a$，$\tt b$，$\tt c$，$\tt e$，要子串中包含全部的这四类字母，则子串的索引区间为 $[2, 6]$，即 $S$ 中的第 $2$ 个字符到第 $6$ 个字符，即字符串 $\tt{abCce}$。
## 输入格式

第一行仅有一个整数 $n$，第二行包含一个符合题目要求的长度为 $n$ 的字符串 $S$。
## 输出格式

仅有一个不超过 $n$ 的正整数，表示符合题目要求的子串的最小长度。
## 样例

### 样例输入 #1
```
3
AaA
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
7
bcAAcbc
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
6
aaBCCe
```
### 样例输出 #3
```
5
```
## 提示

- 对于 $10\%$ 的数据，所有字符都不相同；
- 对于另外 $30\%$ 的数据，字符串 $S$ 中只包含两种类别的字符。
- 对于另外 $60\%$ 的数据，字符串的长度不会超过 $10^5$。

对于所有数据，字符串的长度不超过 $10^5$，且只包含大小写字母。


---

---
title: "[AHOI2024 初中组] 立方根"
layout: "post"
diff: 普及-
pid: P10373
tag: ['数学', '递推', '2024', '安徽', 'O2优化', '前缀和', '分块', '双指针 two-pointer']
---
# [AHOI2024 初中组] 立方根
## 题目背景

**特别提示：**

1. 请使用 `(int) cbrt(x + 0.5)` 计算 $\lfloor \sqrt[3]{x} \rfloor$ 的值，否则可能会出现精度误差。
2. 本题包含两组针对时间复杂度为 $O(q\sqrt[3]{x})$ 的算法的 hack 数据（#11 和 #12）。
## 题目描述

小可可想计算所有不大于 $x$ 的正整数的立方根下取整之和，但是她不会做，你能帮帮她吗？

为了彻底帮小可可弄懂这个问题，你需要回答 $q$ 组询问，对于每组询问给定的一个正整数 $x_i$，输出：

$$\sum _{j=1} ^{x_i} \lfloor j^{\frac{1}{3}} \rfloor$$

其中，$\lfloor x \rfloor$ 表示不大于 $x$ 的最大整数。
## 输入格式

第一行一个正整数 $q$。

接下来 $q$ 行，第 $i$ 行一个正整数 $x_i$。

**保证给出的 $\bm{x_1 \sim x_q}$ 单调不降。**
## 输出格式

$q$ 行，每行一个正整数，表示该组询问的答案。

**请注意答案的范围。**
## 样例

### 样例输入 #1
```
2
5
10
```
### 样例输出 #1
```
5
13
```
## 提示

### 样例 1 解释

$1 \sim 10$ 的立方根下取整的结果是：$1,1,1,1,1,1,1,2,2,2$。

### 数据范围

对于 $20\%$ 的数据，$x_q,q \le 1000$。

对于另外 $20\%$ 的数据，$q=1$。

对于另外 $20\%$ 的数据，$q \le 5000$。

对于另外 $20\%$ 的数据，$q \le 10^5$，$x_q \le 10^6$。 

对于 $100\%$ 的数据，$1 \le q \le 2 \times 10^5$，$1 \le x_1 \le x_2 \le \ldots \le x_q \le 10^{12}$。


---

---
title: "A-B 数对"
layout: "post"
diff: 普及-
pid: P1102
tag: ['模拟', '数学', '二分', '排序', '哈希 hashing', '双指针 two-pointer']
---
# A-B 数对
## 题目背景

出题是一件痛苦的事情！

相同的题目看多了也会有审美疲劳，于是我舍弃了大家所熟悉的 A+B Problem，改用 A-B 了哈哈！
## 题目描述

给出一串正整数数列以及一个正整数 $C$，要求计算出所有满足 $A - B = C$ 的数对的个数（不同位置的数字一样的数对算不同的数对）。
## 输入格式

输入共两行。

第一行，两个正整数 $N,C$。

第二行，$N$ 个正整数，作为要求处理的那串数。
## 输出格式

一行，表示该串正整数中包含的满足 $A - B = C$ 的数对的个数。
## 样例

### 样例输入 #1
```
4 1
1 1 2 3

```
### 样例输出 #1
```
3
```
## 提示

对于 $75\%$ 的数据，$1 \leq N \leq 2000$。

对于 $100\%$ 的数据，$1 \leq N \leq 2 \times 10^5$，$0 \leq a_i <2^{30}$，$1 \leq C < 2^{30}$。

2017/4/29 新添数据两组


---

---
title: "连续自然数和"
layout: "post"
diff: 普及-
pid: P1147
tag: ['数学', '枚举', '前缀和', '双指针 two-pointer']
---
# 连续自然数和
## 题目描述

对一个给定的正整数 $M$，求出所有的连续的正整数段（每一段至少有两个数），这些连续的自然数段中的全部数之和为 $M$。

例子：$1998+1999+2000+2001+2002 = 10000$，所以从 $1998$ 到 $2002$ 的一个自然数段为 $M=10000$ 的一个解。

## 输入格式

包含一个整数的单独一行给出 $M$ 的值（$10 \le M \le 2,000,000$）。

## 输出格式

每行两个正整数，给出一个满足条件的连续正整数段中的第一个数和最后一个数，两数之间用一个空格隔开，所有输出行的第一个按从小到大的升序排列，对于给定的输入数据，保证至少有一个解。

## 样例

### 样例输入 #1
```
10000

```
### 样例输出 #1
```
18 142 
297 328 
388 412 
1998 2002

```


---

---
title: "[科大国创杯初中组 2023] 数数"
layout: "post"
diff: 普及-
pid: P11951
tag: ['二分', '2023', '安徽', '双指针 two-pointer', '科大国创杯']
---
# [科大国创杯初中组 2023] 数数
## 题目描述

小可可和小多在拼木棍。

他们现在拿到了 $n$ 根木棍，第 $i$ 根木棍的长度是 $a_i$。他们现在想知道，有多少种在里面选三根木棍的方案，使得这三根木棍能组成一个三角形？

三根木棍能组成一个三角形，当且仅当较短的两根木棍长度和大于最长的那根木棍长度。
## 输入格式

第一行一个正整数 $n$，表示木棍的个数。

第二行 $n$ 个正整数，第 $i$ 个正整数 $a_i$ 表示第 $i$ 根木棍的长度。
## 输出格式

一行一个整数，表示有多少种选三根木棍的方案，使得这三根木棍能组成一个三角形。
## 样例

### 样例输入 #1
```
5
3 2 5 3 4
```
### 样例输出 #1
```
8
```
## 提示

### 样例 1 解释

可以选择的编号的方案是：$(1,2,4)$，$(1,2,5)$, $(1,3,4)$，$(1,3,5)$，$(1,4,5)$，$(2,3,5)$, $(2,4,5)$，$(3,4,5)$。

### 数据规模与约定

对于 $20\%$ 的数据，满足 $n \leq 100$；

对于 $40\%$ 的数据，满足 $n \leq 10^3$；

对于另外 $20\%$ 的数据，满足 $a_i \leq 5 \times 10^3$；

对于 $100\%$ 的数据，满足 $3 \leq n \leq 8 \times 10^3$，$1 \leq a_i \leq 10^9$。


---

---
title: "[蓝桥杯 2025 省 B] 画展布置"
layout: "post"
diff: 普及-
pid: P12134
tag: ['数学', '2025', '排序', '双指针 two-pointer', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 B] 画展布置
## 题目描述

画展策展人小蓝和助理小桥为即将举办的画展准备了 $N$ 幅画作，其艺术价值分别为 $A_1, A_2, \dots , A_N$。他们需要从这 $N$ 幅画中挑选 $M$ 幅，并按照一定顺序布置在展厅的 $M$ 个位置上。如果随意挑选和排列，艺术价值的变化可能会过于突兀，导致观众的观展体验不够流畅。

为了优化布置，他们查阅了《画展布置指南》。指南指出，理想的画展应使观众在欣赏画作时，艺术价值的过渡尽量平缓。指南建议，选择并排列 $M$ 幅画，应使艺术价值的变化程度通过一个数值 $L$ 来衡量，且该值越小越好。数值 $L$ 的定义为：

$$L=\sum_{i=1}^{M-1} |B_{i+1}^2-B_i^2|$$

其中 $B_i$ 表示展厅第 $i$ 个位置上画作的艺术价值。

现在，他们希望通过精心挑选和排列这 $M$ 幅画作，使 $L$ 达到最小值，以提升画展的整体协调性。请你帮他们计算出这个最小值是多少。
## 输入格式

输入共两行。

第一行包含两个正整数 $N$ 和 $M$，分别表示画作的总数和需要挑选的画作数量。

第二行包含 $N$ 个正整数 $A_1, A_2, \dots , A_N$，表示每幅画作的艺术价值。

## 输出格式

输出一个整数，表示 $L$ 的最小值。
## 样例

### 样例输入 #1
```
4 2
1 5 2 4
```
### 样例输出 #1
```
3
```
## 提示

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$2 \leq M \leq N \leq 10^3$，$1 \leq A_i \leq 10^3$。
- 对于 $100\%$ 的评测用例，$2 \leq M \leq N \leq 10^5$，$1 \leq A_i \leq 10^5$。


---

---
title: "[蓝桥杯 2023 国 Java B] 玩具"
layout: "post"
diff: 普及-
pid: P12218
tag: ['贪心', '2023', '排序', '双指针 two-pointer', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Java B] 玩具
## 题目描述

小明的妈妈给他买了 $n$ 个玩具，但是为了同时考察他的智力，只给了他 $2 \times n$ 个零件，第 $i$ 个零件的重量为 $w_i$（$1 \leq i \leq 2 \times n$）。

其中任意两个零件都可以拼接成一个玩具，这个玩具的权重就等于拼接所用的 **两个零件的重量的乘积**。小明的妈妈希望小明能够使用这 $2 \times n$ 个零件拼接出 $n$ 个玩具（每个零件必须使用且只能用一次），使得所有玩具的权重的和最小。小明希望你帮帮他计算出最小的权重和。

## 输入格式

输入共 $2$ 行。

第一行为一个正整数 $n$。

第二行为 $2 \times n$ 个由空格隔开的整数 $w_1, w_2, \ldots, w_{2 \times n}$。
## 输出格式

输出共 $1$ 行，一个整数。
## 样例

### 样例输入 #1
```
2
2 2 3 4
```
### 样例输出 #1
```
14
```
## 提示

### 样例说明

由于有两个零件的重量都为 $2$，所以一共有两种结果:
- $(2 \times 2) + (3 \times 4) = 16$;
- $(2 \times 3) + (2 \times 4) = 14$。

### 评测用例规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 10^3$。
- 对于 $100\%$ 的数据，保证 $n \leq 10^5$，$0 \leq w_i \leq 10^5$。


---

---
title: "[蓝桥杯 2024 国 Java B] 分组"
layout: "post"
diff: 普及-
pid: P12257
tag: ['贪心', '2024', '双指针 two-pointer', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Java B] 分组
## 题目描述

小明班上有 $n$ 名同学，老师准备按上一次考试的分数对同学们进行分组，第 $i$ 名同学的分数为 $a_i$。老师希望把同学们分为尽可能多的小组，且满足每个小组中的同学分数的最大值至少是最小值的两倍。请问最多能分出多少个小组？如果把所有人分到同一组都不能满足条件则输出 $0$。
## 输入格式

输入共 $2$ 行。

第一行为一个正整数 $n$。

第二行为 $n$ 个由空格分开的正整数表示 $a_1, a_2, \ldots, a_n$。
## 输出格式

输出共 $1$ 行，一个整数表示答案。
## 样例

### 样例输入 #1
```
6
3 5 2 1 4 2
```
### 样例输出 #1
```
3
```
## 提示

### 样例说明

其中一种分组方式：第一组 $\{a_4, a_1\} = \{1, 3\}$，第二组 $\{a_3, a_2\} = \{2, 5\}$，第三组 $\{a_6, a_5\} = \{2, 4\}$。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，保证 $n \leq 10$。
- 对于 $100\%$ 的评测用例，保证 $1\leq n \leq 10^5$，$0 < a_i \leq 10^8$。


---

---
title: "[蓝桥杯 2025 省 A/Python B 第二场] 消消乐"
layout: "post"
diff: 普及-
pid: P12341
tag: ['贪心', '2025', '双指针 two-pointer', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 A/Python B 第二场] 消消乐
## 题目描述

小蓝正在玩一个叫“一维消消乐”的游戏。游戏初始时给出一个长度为 $n$ 的字符串 $S = S_0S_1\ldots S_{n-1}$，字符串只包含字符 $\text{A}$ 和 $\text{B}$。小蓝可以对这个字符串进行若干次操作，每次操作可以选择两个下标 $i, j \in [0, n-1]$，如果 $i < j$ 且 $S_i = \text{A}$ 且 $S_j = \text{B}$，小蓝就可以把它们同时消掉。小蓝想知道在经过若干次操作后，直到无法对字符串继续进行操作时，字符串最多剩下多少个字符。
## 输入格式

输入一行包含一个长度为 $n$ 的字符串 $S$。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
BABAABBA
```
### 样例输出 #1
```
4
```
## 提示

### 样例说明

先消掉 $(S_1, S_6)$，再消掉 $(S_4, S_5)$，此时剩下 $\text{BBAA}$，无法继续进行操作。

### 评测用例规模与约定

- 对于 $10\%$ 的评测用例，$1 \leq n \leq 20$；
- 对于 $20\%$ 的评测用例，$1 \leq n \leq 100$；
- 对于 $50\%$ 的评测用例，$1 \leq n \leq 10000$；
- 对于所有评测用例，$1 \leq n \leq 10^6$。


---

---
title: "[蓝桥杯 2025 省 B/Python B 第二场] 数列差分"
layout: "post"
diff: 普及-
pid: P12342
tag: ['贪心', '二分', '2025', '双指针 two-pointer', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 B/Python B 第二场] 数列差分
## 题目描述

小蓝有两个长度均为 $n$ 的数列 $A=\{a_1, a_2, \cdots, a_n\}$ 和 $B=\{b_1, b_2, \cdots, b_n\}$，将两个数列作差定义为 $C=A-B=\{c_1=a_1-b_1, c_2=a_2-b_2, \cdots, c_n=a_n-b_n\}$。小蓝将对数列 $B$ 进行若干次操作，每次操作可以将数列 $B$ 中的任意一个数更改为任意一个整数。在进行完所有操作后，小蓝可以按任意顺序将数列 $B$ 重排，之后再计算数列 $C$。小蓝想知道，最少操作多少次可以使得数列 $C$ 中的所有数都为正整数。
## 输入格式

输入的第一行包含一个正整数 $n$；

第二行包含 $n$ 个整数 $a_1, a_2, \cdots, a_n$，相邻整数之间使用一个空格分隔。

第三行包含 $n$ 个整数 $b_1, b_2, \cdots, b_n$，相邻整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
4
22 31 12 14
3 19 27 44
```
### 样例输出 #1
```
1
```
## 提示

### 样例说明

其中一种方案：将 $44$ 改为 $0$，重新排列 $B$ 为 $\{19, 27, 3, 0\}$，使得数列 $C=\{3, 4, 9, 14\}$ 均为正整数。

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$n \leq 10$；
- 对于所有评测用例，$1 \leq n \leq 10^5$，$-10^9 \leq a_i \leq 10^9$，$-10^9 \leq b_i \leq 10^9$。


---

---
title: "[CCC 2025 Junior] Sunny Days"
layout: "post"
diff: 普及-
pid: P12612
tag: ['递推', '2025', 'CCC（加拿大）', '双指针 two-pointer']
---
# [CCC 2025 Junior] Sunny Days
## 题目背景

Score: 15.
## 题目描述

There is a large amount of historical weather data for CEMCity. Each day in the data is listed as either a day with sunshine or a day with precipitation. Jeremy is interested in finding the record for the most consecutive days with sunshine. Unfortunately, the data is incorrect for exactly one day, but Jeremy doesn't know which day this is.

Your job is to help Jeremy determine the maximum possible number of consecutive days with sunshine.

![](https://cdn.luogu.com.cn/upload/image_hosting/mirndz24.png)
## 输入格式

The first line of input contains a positive integer, $N$, representing the number of days in the historical data. The following $N$ lines each contain either the character $S$ or the character $P$, representing a day with sunshine or a day with precipitation, respectively, in chronological order.
## 输出格式

Output the non-negative integer, $M$, which is the maximum possible number of consecutive days with sunshine.
## 样例

### 样例输入 #1
```
8
P
S
P
S
S
P
P
S
```
### 样例输出 #1
```
4
```
## 提示

**Explanation of Output for Sample Input**

If the data is incorrect for the third day, then there was sunshine from the second day to the fifth day which is four consecutive days with sunshine. This is the maximum possible number of consecutive days with sunshine. That is, no matter which day the data is incorrect for, there were not five (or more) consecutive days of sunshine.

The following table shows how the available 15 marks are distributed:

|Marks|Description|Bounds|
|:-:|:-:|:-:|
|2|There are not many days in the historical data. The data consists of a single block of all S's followed by a single block of all P's. One of these blocks may be empty.|$N\leq 1000$|
|4|There are not many days in the historical data. The data contains S's and P's possibly in mixed order.|$N\leq 1000$|
|9|There are possibly many days in the historical data.|$N\leq 500\,000$|


---

---
title: "[GCJ 2014 #2] Data Packing"
layout: "post"
diff: 普及-
pid: P13256
tag: ['贪心', '2014', '双指针 two-pointer', 'Google Code Jam']
---
# [GCJ 2014 #2] Data Packing
## 题目描述

Adam, being a well-organized man, has always been keenly interested in organizing all his stuff. In particular, he fondly remembers the many hours of his youth that were spent moving files from his computer onto Compact Discs.

There were two very important rules involved in this procedure. First, in order to ensure that all discs could be labeled clearly, Adam would never place more than two files on the same disc. Second, he would never divide a single file over multiple discs. Happily, the discs he was using were always large enough to make this possible.

Thinking back, Adam is now wondering whether he arranged his files in the best way, or whether he ended up wasting some Compact Discs. He will provide you with the capacity of the discs he used (all his discs had the same capacity) as well as a list of the sizes of the files that he stored. Please help Adam out by determining the minimum number of discs needed to store all his files—following the two very important rules, of course.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing two integers: the number of files to be stored $N$, and the capacity of the discs to be used $X$ (in MBs). The next line contains the $N$ integers representing the sizes of the files $S_i$ (in MBs), separated by single spaces.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the minimum number of discs needed to store the given files.
## 样例

### 样例输入 #1
```
3
3 100
10 20 70
4 100
30 40 60 70
5 100
10 20 30 40 60
```
### 样例输出 #1
```
Case #1: 2
Case #2: 2
Case #3: 3
```
## 提示

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq X \leq 700$.
- $1 \leq S_i \leq X$.

**Small dataset(5 Pts)**

- Time limit: ~~60~~ 3 seconds.
- $1 \leq N \leq 10$.

**Large dataset(8 Pts)**

- Time limit: ~~120~~ 5 seconds.
- $1 \leq N \leq 10^4$.


---

---
title: "[KOI 2025 #2] 包"
layout: "post"
diff: 普及-
pid: P13521
tag: ['2025', '排序', '前缀和', '双指针 two-pointer', 'KOI（韩国）']
---
# [KOI 2025 #2] 包
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

商户是在 KOI 市经营商店的一位市民。商户的店里有 $N$ 件商品，其中第 $i$ 件商品的重量为 $A_i$。商户收到了情报，得知小偷“金基范”正觊觎自己的店铺，于是他准备采取措施，将损失降到最低。

小偷金基范计划从店里偷走 $K$ 件商品。但如果商品太重，不仅难以偷窃，被警察抓住的可能性也会变高。因此，小偷金基范会**最小化**他所偷商品的总重量。不过，如果店里的商品总数不足 $K$ 件，小偷金基范会偷走店里所有的商品。

在小偷金基范到达店铺之前，商户会把店里的一些商品装进一个包里带走。之后，小偷金基范会对商户没有带走的那些商品，以上述方式实施盗窃。商户希望通过合理地往包里装商品，来**最大化**小偷金基范最终偷走的商品总重量。

商户的包能承受的重量是有限的。当给定一个最大承重 $C$ 时，请对所有的 $x = 1, 2, \ldots, C$ 回答以下问题：

*   在商户能放入包中的商品总重量不超过 $x$ 的条件下，小偷金基范偷走的商品总重量的最大值是多少？
## 输入格式

第一行给定 $N, K, C$，由空格分隔。

第二行给定 $N$ 个整数 $A_1, A_2, \ldots, A_N$，由空格分隔。
## 输出格式

输出 $C$ 行。第 $i$ 行输出当 $x = i$ 时，小偷金基范偷走的商品总重量的最大值。
## 样例

### 样例输入 #1
```
5 1 6
1 2 3 4 5
```
### 样例输出 #1
```
2
2
3
3
3
4
```
### 样例输入 #2
```
5 2 5
2 3 5 7 11
```
### 样例输出 #2
```
5
8
8
8
12
```
### 样例输入 #3
```
3 2 3
1 1 7
```
### 样例输出 #3
```
8
8
8
```
## 提示

### 限制条件

*   所有给定的数都是整数。
*   $1 \le K \le N \le 5\,000$
*   $1 \le C \le 1\,000\,000$
*   对于所有 $i$ ($1 \le i \le N$)，满足 $1 \le A_i \le 1\,000\,000$

### 子任务

1.  (13 分) $N \le 10, A_i \le 10\,000, C \le 10\,000$
2.  (17 分) $N \le 80, A_i \le 10\,000, C \le 10\,000$
3.  (23 分) $A_i \le 10\,000, C \le 10\,000$
4.  (16 分) $K = 1$
5.  (31 分) 无额外限制条件。


---

---
title: "「EZEC-10」排列排序"
layout: "post"
diff: 普及-
pid: P7714
tag: ['模拟', '\ufeff基础算法', '构造', '差分', '双指针 two-pointer']
---
# 「EZEC-10」排列排序
## 题目描述

给你一个长度为 $n$ 的排列 $p_1,p_2, \cdots ,p_n$。你需要把它排序。

每次可以花区间长度，即 $r-l+1$ 的代价，选择排列中的任意一段区间 $[l,r]$，并将 $[l,r]$ 从小到大排序。

现在你可以让他进行若干次这个操作，直到 $p$ 中元素的值从 $1$ 到 $n$ 按升序排序，即对于 $1$ 到 $n$ 的每一个 $i$，都有 $p_i=i$。

求问花的代价最少为多少？
## 输入格式

本题有多组询问，第一行有一个数 $T$ 表示询问组数。

对于每组询问：

第一行给出一个整数 $n$。

第二行 $n$ 个整数，由空格隔开，代表排列 $p$ 中元素的值。
## 输出格式

$T$ 行，每行一个整数表示一组询问的答案。
## 样例

### 样例输入 #1
```
2
3
1 3 2
4
3 2 1 4
```
### 样例输出 #1
```
2
3
```
## 提示

【样例 $1$ 说明】

对于第一组数据，可选择区间 $[2,3]$ 进行排序。

对于第二组数据，可选择区间 $[1,3]$ 进行排序。

【数据规模与约定】

对于 $20\%$ 的数据，$n\leq 4$。

对于另 $30\%$ 的数据，$\sum n\leq5000$。

对于另 $10\%$ 的数据，$p_1=n$。

对于 $100\%$ 的数据，$1\le T,\sum n\le 10^6$。


---

---
title: "[JOI 2022 Final] 星际蛋糕 (Intercastellar)"
layout: "post"
diff: 普及-
pid: P8160
tag: ['2022', 'O2优化', '前缀和', 'JOI（日本）', '双指针 two-pointer']
---
# [JOI 2022 Final] 星际蛋糕 (Intercastellar)
## 题目背景

在 30XX 年，由于科学家和工程师的不断努力，不同星球之间的互动变得非常活跃。比太郎是一只河狸，他现在是一项交流项目的大使。他的任务是向不同星球的居民介绍地球上的食物。他将在下午 1 点出发去 JOI 星球。

现在，比太郎正计划向 JOI 星球的居民介绍 castella。castella 已经被切成了若干段。castella 是一种由面粉、鸡蛋、糖和淀粉糖浆制成的烘烤海绵蛋糕。

![](https://cdn.luogu.com.cn/upload/image_hosting/krpqlhl4.png)
## 题目描述

castella 的形状是一个在水平方向上很长的长方体。它被切成了 $N$ 段，其中从左往右的第 $i$ 段的长度为整数 $A_i$。

几分钟前，我们得知 JOI 星球的居民不喜欢偶数。为了解决此问题，你需要不断执行下列操作，直到不存在长度为偶数的段。

1. 在长度为偶数的段中，你选择最靠右的一段。
2. 你将选中的这一段切成两个长度相等的段。也就是说，假设选中的这一段的长度是 $k$，你将其切成长度为 $\displaystyle \frac{k}{2}$ 的两段。你不改变其他段的位置。

为了确认操作是否被正确地执行了，比太郎让你回答 $Q$ 个询问。第 $j$ 个询问如下：

- 当所有操作执行完毕后，从左往右的第 $X_j$ 段的长度为多少？

给定 castella 的信息与询问，请写一个程序回答所有询问。
## 输入格式

第一行，一个正整数 $N$。

接下来 $N$ 行，第 $i$ 行一个正整数 $A_i$。

接下来一行，一个正整数 $Q$。

接下来 $Q$ 行，第 $j$ 行一个正整数 $X_j$。
## 输出格式

输出 $Q$ 行，第 $j$ 行一个数，表示第 $j$ 个询问的答案。
## 样例

### 样例输入 #1
```
4
14
9
8
12
6
2
3
5
7
11
13

```
### 样例输出 #1
```
7
9
1
1
1
3

```
### 样例输入 #2
```
13
1
4
1
4
2
1
3
5
6
2
3
7
3
8
2
10
11
13
15
17
18
20

```
### 样例输出 #2
```
1
1
1
1
5
3
1
3

```
### 样例输入 #3
```
16
536870912
402653184
536870912
536870912
134217728
536870912
671088640
536870912
536870912
536870912
939524096
805306368
536870912
956301312
536870912
536870912
5
2500000000
3355443201
4294967296
5111111111
6190792704

```
### 样例输出 #3
```
5
1
7
57
1

```
## 提示

**【样例解释 \#1】**

一开始，castella 从左到右的段的长度分别为 $14, 9, 8, 12$。

当所有操作执行完毕后，castella 被切成了 $15$ 段。从左到右的段的长度分别为 $7, 7, 9, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3$。

这个样例满足子任务 $2, 3$ 的限制。

**【样例解释 \#2】**

这个样例满足所有子任务的限制。

**【样例解释 \#3】**

这个样例满足子任务 $2, 3$ 的限制。

----

**【数据范围】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，$1 \le N, Q \le 2 \times {10}^5$，$1 \le A_i \le {10}^9$，$1 \le X_j \le {10}^{15}$，$X_j \le X_{j + 1}$，保证当所有操作执行完毕后，castella 被切成了至少 $X_Q$ 段。

- 子任务 $1$（$25$ 分）：$A_i \le 8$。
- 子任务 $2$（$35$ 分）：$N, Q \le 1000$。
- 子任务 $3$（$40$ 分）：无特殊限制。

----

**译自 [JOI 2022 Final](https://www.ioi-jp.org/joi/2021/2022-ho/index.html) T1「[インターカステラー](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t1.pdf) / [Intercastellar](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t1-en.pdf)」**


---

---
title: "[入门赛 #7] 狠狠地切割 (Hard Version)"
layout: "post"
diff: 普及-
pid: P8889
tag: ['二分', '2022', 'O2优化', '排序', '双指针 two-pointer', '语言月赛']
---
# [入门赛 #7] 狠狠地切割 (Hard Version)
## 题目背景

**本题与 H1 的题意完全一致，区别仅在数据范围。在语言月赛中不存在 H2 题目，本题仅用于增加公开赛的区分度，并不严格遵循比赛考察范围，请酌情完成。**
## 题目描述

现给你一个长度为 $n$ 的序列 $a _ 1, \cdots, a _ n$ 和 $m$ 个互不相同的整数 $b _ 1, \cdots, b _ m$。你需要按照这 $m$ 个数对序列 $a$ 进行**狠狠地切割**。

具体的，对于一个数字 $i \in [1, n]$，如果存在一个整数 $j \in [1, m]$，使得 $a _ i = b _ j$，则将位置 $i$ 称为一个**切割点**。对序列 $a$ 中的每一个切割点，我们在这个位置进行一次**狠狠地切割**。方法是，将该位置的数字去除，然后在这个位置将其左右的**序列/片段**一分两半。

如果对**狠狠地切割**的定义有疑问，可以参照「样例 #1」及「样例解释 #1」进行理解。

你需要计算，在进行了所有可能的**狠狠地切割**后，序列被切割为了多少**片段**。

特别的，如果在切割后，某一段内没有数组，那这一段不可被叫做**片段**。同样的，如果 $1$ 或 $n$ 为切割点，其与开头和结尾之间也不存在片段。

如果对**片段**的概念有疑问，可以参照「样例 #2」及「样例解释 #2」进行理解。
## 输入格式

第一行为两个整数，依次表示序列 $a$ 的长度 $n$ 和序列 $b$ 的长度 $m$。  
第二行有 $n$ 个整数，第 $i$ 个整数表示 $a_i$。  
第三行有 $m$ 个整数，第 $i$ 个整数表示 $b_i$。
## 输出格式


输出一个整数，代表**狠狠地切割**后的**片段**的个数。
## 样例

### 样例输入 #1
```
6 2
3 4 3 5 2 6
5 4
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
6 3
3 4 3 5 2 6
3 5 6
```
### 样例输出 #2
```
2
```
## 提示

### 样例 1 解释

在**狠狠地切割**前，序列 $a$ 如下所示：

$$\begin{matrix} 3 & 4 & 3 & 5 & 2 & 6 \end{matrix}$$

容易知道，第二个位置和第四个位置为切割点，我们使用 `|` 对其进行替换，代表去除工作：

$$\begin{matrix} 3 & | & 3 & | & 2 & 6 \end{matrix}$$

我们将片段进行简单的标记：

$$\begin{matrix} \overbrace{3} ^ \text{片段 1} & | & \overbrace{3} ^ \text{片段 2} & | & \overbrace{2 \quad 6} ^ \text{片段 3} \end{matrix}$$

共计 $3$ 个片段。

### 样例 2 解释

以下我们展示去除之后的序列：

$$\begin{matrix} | & 4 & | & | & 2 & | \end{matrix}$$

我们将片段进行简单的标记：

$$\begin{matrix} \overbrace{\vphantom{0}} ^ \text{\color{red}这个不是片段} | & \overbrace{4} ^ \text{片段 1} & | & \overbrace{\vphantom{0}} ^ \text{\color{red}这个不是片段} & | & \overbrace{2} ^ \text{片段 2} & | \overbrace{\vphantom{0}} ^ \text{\color{red}这个不是片段}\end{matrix}$$

共计 $2$ 个片段。

### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $a$ 序列中没有任何元素在 $b$ 中出现过。形式化的，$\forall i \in [1, n], \forall j \in [1, m], a _ i \neq b _ j$。
- 对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 5 \times 10 ^ 5$，$- 10 ^ {18} \leq a _ i, b_i \leq 10 ^ {18}$，序列 $b$ 中的元素两两不同。

### 提示
本题输入规模较大，建议考虑使用较快的读入读出方式。


---

