---
title: "[CCO 2022] Alternating Heights"
layout: "post"
diff: 普及/提高-
pid: P10050
tag: ['二分', '2022', 'CCO（加拿大）', '深度优先搜索 DFS', '图论建模', '双指针 two-pointer']
---
# [CCO 2022] Alternating Heights
## 题目描述

Troy 计划给 CCO 的学生拍一张合影，他向你寻求帮助。

有 $K$ 个学生，编号从 $1$ 到 $K$。Troy 忘记了学生的身高，但他记得没有两个学生的身高相同。

Troy 有一个序列 $A_{1}, A_{2}, \ldots, A_{N}$，表示合影中从左到右的学生顺序。一个学生可能在 $A$ 中出现多次。你不确定这张合影会怎么拍，但你不愿意认为 Troy 犯了错误。

Troy 会给你 $Q$ 个形式为 $x,y$ 的询问，每个询问为「给定学生序列 $A_{x}, A_{x+1}, \ldots, A_{y}$，他们的身高能否形成一个交替序列？」更具体地说，我们用 $h_i$ 表示第 $i$ 个学生的身高。如果存在一种身高分配$ h_1, h_2, \ldots, h_K$，使得 $h_{A_{x}}>h_{A_{x+1}}<h_{A_{x+2}}>h_{A_{x+3}}<\ldots h_{A_{y}}$，回答 `YES`；否则回答 `NO`。

注意，每个查询都是独立的：也就是说，询问 $i$ 的身高分配与询问 $j$ 的身高分配无关 $(i\neq j)$。
## 输入格式

第一行包含三个用空格分隔的整数 $N, K$ 和 $Q$。

第二行包含 $N$ 个整数，表示 $A_{1}, A_{2}, \ldots, A_{N}\left(1 \leq A_{i} \leq K\right)$。

接下来的 $Q$ 行，每行包含两个用空格分隔的整数 $x$ 和 $y (1 \leq x<y \leq N)$，表示一组查询。
## 输出格式

输出 $Q$ 行。第 $i$ 行，输出 `YES` 或者 `NO`，表示 Troy 的第 $i$ 个查询的答案。
## 样例

### 样例输入 #1
```
6 3 3
1 1 2 3 1 2
1 2
2 5
2 6
```
### 样例输出 #1
```
NO
YES
NO
```
## 提示

## 样例说明

对于第一个询问，不可能有 $h_1>h_1$，所以答案是 `NO`。

对于第二个询问，$h_1>h_2<h_3>h_1$ 的一种方案是 $h_1=160 \mathrm{~cm}, h_2=140 \mathrm{~cm}, h_3=180 \mathrm{~cm}$。另一种方案是 $h_1=1.55 \mathrm{~m}, h_2=1.473 \mathrm{~m}, h_3=1.81 \mathrm{~m}$。

对于第三个询问，不可能同时有 $h_1>h_2$ 和 $h_1<h_2$。

## 数据范围

对于所有的数据，有 $2 \leq N \leq 3000$，$2 \leq K \leq N$，$1 \leq Q \leq 10^{6}$。

子任务编号|	分值|	$N$|	$K$|	$Q$
:-:|:-:|:-:|:-:|:-:
$1$|	$16$|	$2 \leq N \leq 3000$|	$K=2$|	$1 \leq Q \leq 10^{6}$
$2$|	$24$|	$2 \leq N \leq 500$|	$2 \leq K \leq \min (N, 5)$|$1 \leq Q \leq 10^{6}$
$3$	|$28$|	$2 \leq N \leq 3000$	|$2 \leq K \leq N$	|$1 \leq Q \leq 2000$
$4$|	$32$| $2 \leq N \leq 3000$	|$2 \leq K \leq N$	|	$1 \leq Q \leq 10^{6}$


---

---
title: "「MYOI-R3」极差"
layout: "post"
diff: 普及/提高-
pid: P10444
tag: ['贪心', '二分', '洛谷原创', 'O2优化', '洛谷月赛', '双指针 two-pointer', 'Ad-hoc']
---
# 「MYOI-R3」极差
## 题目描述

对于一个序列 $c$ ，定义 $c$ 的极差为 $c$ 中最大值与最小值之差。现在给定一个长度为 $n$ 的序列 $a$，问是否能将其分成至少两个长度大于 $1$ 的子序列，使得每个子序列的极差都相等（注意，所有元素都必须分配且每个元素仅能分配到一个子序列中）。
## 输入格式

**本题包含多组数据**。

第一行两个整数 $T,id$，表示数据组数和子任务编号。

对于每组数据，

第一行一个正整数 $n$，表示数组长度。

第二行 $n$ 个整数表示序列 $a$。
## 输出格式


对于每组数据，输出一行一个字符串 `Yes` 或 `No`。
## 样例

### 样例输入 #1
```
2 1
6
1 1 4 5 1 4
7
1 9 1 9 8 1 0
```
### 样例输出 #1
```
No
Yes
```
## 提示

### 样例 $\small\text{1}$ 解释

样例符合子任务 1 的约束，$id=1$。


询问一：

可以证明，没有任何方案满足条件。

询问二：

合法分配的一种子序列集合如下：
- $\{1,9\}$。
- $\{1,9\}$。
- $\{8,1,0\}$。

答案不唯一。

### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 1（20 points）：$4\le \sum n\le 20,a_i\ge 0$。
- Subtask 2（20 points）：$4\le \sum n\le 100,a_i\ge 0$。
- Subtask 3（20 points）：$4\le \sum n\le 10^3,a_i\ge 0$。
- Subtask 4（10 points）：$a$ 数组中元素相等。
- Subtask 5（30 points）：无特殊限制。


对于 $100\%$ 的数据，$4\le \sum n\le 10^6,0\le |a_i|\le 10^9,1\le T\le 300$。



---

---
title: "[NOISG 2024 Prelim] School Photo"
layout: "post"
diff: 普及/提高-
pid: P10710
tag: ['2024', '双指针 two-pointer', 'NOISG（新加坡）']
---
# [NOISG 2024 Prelim] School Photo
## 题目背景

翻译自 [NOI SG 2024 Prelim C.School Photo](https://github.com/noisg/noi-2024-prelim)。
## 题目描述

Zane 是 NOI 学校的校长。NOI 学校有 $n$ 个班，每个班有 $s$ 名同学。第 $i$ 个班中的第 $j$ 名同学的身高是 $a_{i,j}$。

现在 Zane 想从每个班上选出一名同学拍照，使得这 $n$ 名同学中最高的同学和最低的同学的身高差最小。

请你输出这个最小值。
## 输入格式

第一行，两个整数 $n,s$；

接下来 $n$ 行，每行 $s$ 个整数，表示 $a$。
## 输出格式

一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2 3
2 1 8
5 4 7

```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3 3
3 1 4
2 7 18
9 8 10
```
### 样例输出 #2
```
4
```
## 提示

### 【样例 #2 解释】

选择 $a_{1,3},a_{2,2},a_{3,2}$，答案为 $8-4=4$。

### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$11$|$n=2$|
|$2$|$22$|$n,s\le100$|
|$3$|$9$|$n,s\le250$|
|$4$|$33$|$n,s\le500$|
|$5$|$25$|无|

对于 $100\%$ 的数据，$1\le n,s \le 1000,1\le a_{i,j} \le 10^9$。


---

---
title: "繁花"
layout: "post"
diff: 普及/提高-
pid: P11243
tag: ['递推', '洛谷原创', 'O2优化', '洛谷月赛', '双指针 two-pointer']
---
# 繁花
## 题目背景

[English statement](https://www.luogu.com.cn/problem/U505208). **You must submit your code at the Chinese version of the statement.**

我已经知道，在设置好循环播放时就已经知道，我是在麻痹自己，在逃避问题。

我承认如此，可捞起那些沉于水底的细节时，却一瞬间突然和所有所有真实的心跳共鸣。

那时总想的太少，现在常想得太多，不知所措似荒塘里的绿藻蔓延着。

然而这世间情感太多，小 R 也只能体会更开心和更难过。
## 题目描述

小 R 想对上面的问题进行探究，她想先做一些统计，于是她抽象了这个问题。

小 R 有 $n$ 个未知量 $a_1\dots a_n$，对每个 $1 \leq i < n$，她都比较了 $a_i$ 和 $a_{i+1}$ 并写下了一个字符 $c_i \in \{\texttt <, \texttt >, \texttt =\}$，表示两个未知量之间的比较结果。具体地：

- 若 $c_i = \texttt >$，则 $a_i > a_{i+1}$；
- 若 $c_i = \texttt <$，则 $a_i < a_{i+1}$；
- 否则（$c_i = \texttt =$），表示 $a_i = a_{i+1}$。

小 R 称 $\bm{a_i}$ **比** $\bm{a_j}$ **更开心**，当且仅当对任何 **满足上述 $\bm{n - 1}$ 条约束的** $[a_1, \dots, a_n] \in \mathbb R^n$，都有 $a_i < a_j$。请你帮她数出 $1 \leq i, j \leq n$ 且 $a_i$ 比 $a_j$ 更开心的整数数对 $(i, j)$ 个数。

因为要循环播放，所以有多组数据。
## 输入格式

**本题有多组数据。**

第一行，一个整数 $T$，表示数据组数。对于每组数据：

- 第一行一个整数 $n$。
- 接下来一行，一个长度为 $n - 1$ 的字符串 $c_1c_2\dots c_{n-1}$。
## 输出格式

对于每组数据，输出仅一行一个整数，表示符合条件的整数数对个数。
## 样例

### 样例输入 #1
```
5
5
<<<<
7
<=><=<
9
=<<><==<
11
>=<<=>>>=>
13
=><<=<=>=><>

```
### 样例输出 #1
```
10
9
13
29
25

```
## 提示

### 样例解释

- 对于第一组数据，$a_i$ 比 $a_j$ 开心当且仅当 $1 \leq i < j \leq n$，故共有 $\frac{5\times 4}{2} = 10$ 对合法的 $(i, j)$。
- 对于第二组数据，合法的 $(i, j)$ 分别为：$(1, 2), (1, 3), (4, 2), (4, 3), (4, 5), (4, 6), (4, 7), (5, 7), (6, 7)$，共 $9$ 对。
- 对于其他几组数据，聪明的读者可以自行验证。

### 数据规模与约定

**本题采用捆绑测试和子任务依赖。**

- Subtask 0（0 pts）：样例。
- Subtask 1（10 pts）：$n \leq 8$，$T \leq 8$。
- Subtask 2（20 pts）：$n \leq 5000$，$T \leq 8$。依赖于子任务 $0, 1$。
- Subtask 3（20 pts）：$c_i \neq \texttt =$。
- Subtask 4（50 pts）：无特殊限制。依赖于子任务 $0 \sim 3$。

对于所有数据，保证 $2 \leq n \leq 2\times 10^5$，$1 \leq T \leq 10^4$，$c_i \in \{\texttt <, \texttt >, \texttt =\}$，$\sum n \leq 5\times 10^5$。


---

---
title: "[TOIP 2023] 裁員風暴"
layout: "post"
diff: 普及/提高-
pid: P11849
tag: ['二分', '2023', '双指针 two-pointer', '台湾']
---
# [TOIP 2023] 裁員風暴
## 题目描述

孫執行長任職於美味蛋糕股份有限公司，
因為今年財報不如預期股東寄了公開信呼應公司能刪減成本，
孫執行長決定要讓公司一些夥伴走自己的路。

孫執行長列出 $n$ 個公司目標，
並請員工們各自從 $n$ 個公司目標挑 $1$ 個或 $2$ 個他們認為最重要的目標，
做出相同選擇的員工會被分類到同一個**小組**。
已知每種可能的目標組合都至少有一位員工選擇，
可以計算出恰選擇 $1$ 個目標的小組有 $n$ 組，恰選擇 $2$ 個目標的小組有 $\frac{n(n-1)}{2}$ 組，
合計共有 $n + \frac{n(n-1)}{2} = \frac{n(n+1)}{2}$ 個小組。

透過 AI 大數據分析，每個公司目標都被 AI 賦予一個權重，這裡用 $w_i$ 來表示第 $i$ 的公司目標的權重。
並且我們可以用一個 $01$-序列 $y$ 序列：$y_1, y_2, \cdots, y_n$ 來表示一個小組所選擇的目標，
有選擇第 $i$ 個公司目標則 $y_i = 1$，否則 $y_i = 0$。
AI 定義**裁指數**為：

$$\left( \dfrac{\displaystyle \sum_{i=1}^{n}w_i\times y_i}{\displaystyle \sum_{j=1}^{n} y_j} \right)$$

孫執行長決定把所有小組的裁指數排名，如果一個人所屬於**裁指數前 $k$ 大的小組**就予以開除。

想請你幫忙孫執行長找出排序後第 $k$ 大的裁指數。

例如：$n=3$ 而 $k=4$，
$w_1=5, w_2=-2, w_3=3$，
會有 $\dfrac{3(3+1)}{2} = 6$ 個小組，
每個小組的裁指數如下表 :

|$y_1$|$y_2$|$y_3$|裁指數                 |
|:---:|:---:|:---:|:------------------------------|
| $0$ | $0$ | $1$ |$(0+0+3)/(0+0+1) =           3$|
| $0$ | $1$ | $0$ |$(0-2+0)/(0+1+0) =          -2$|
| $0$ | $1$ | $1$ |$(0-2+3)/(0+1+1) = \frac{1}{2}$|
| $1$ | $0$ | $0$ |$(5+0+0)/(1+0+0) =           5$|
| $1$ | $0$ | $1$ |$(5+0+3)/(1+0+1) =           4$|
| $1$ | $1$ | $0$ |$(5-2+0)/(1+1+0) = \frac{3}{2}$|

裁指數排序後為 $-2, \frac{1}{2}, \frac{3}{2}, 3, 4, 5$，
並且第 $4$ 大為 $\frac{3}{2}$。
（備註：如果裁指數排名第 $k$ 大和第 $k+1$ 大的裁指數相等，
那孫執行長會另外想方法決定裁員名單，不需替他擔心）
## 样例

### 样例输入 #1
```
3 4
5 -2 3
```
### 样例输出 #1
```
3
2
```
### 样例输入 #2
```
3 3
5 -2 3
```
### 样例输出 #2
```
3
1
```
### 样例输入 #3
```
9 45
5 -1 2 -3 6 -9 7 3 2
```
### 样例输出 #3
```
-9
1
```


---

---
title: "[蓝桥杯 2024 国 Python A] 特别的数组"
layout: "post"
diff: 普及/提高-
pid: P12280
tag: ['贪心', '2024', '双指针 two-pointer', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Python A] 特别的数组
## 题目描述

如果一个数组中的所有元素都互不相同，我们称其为一个特别的数组。

给定一个数组 $(a_1, a_2, \cdots, a_n)$，你可以选择一对 $L, R$ 并将数组中的第 $L$ 至 $R$ 个元素移除。求对给定的数组进行一次这样的操作后可以得到的特别的数组的长度最大是多少。
## 输入格式

输入的第一行包含一个整数 $n$，表示数组的长度。

第二行包含 $n$ 个整数 $a_1, a_2, \cdots, a_n$，相邻整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个整数表示进行一次移除操作后可以得到的特别的数组的最大长度。
## 样例

### 样例输入 #1
```
9
1 2 3 4 2 5 7 6 3
```
### 样例输出 #1
```
7
```
## 提示

### 样例说明

移除第 $2, 3$ 个元素可以得到 $1 \ 4 \ 2 \ 5 \ 7 \ 6 \ 3$。

### 评测用例规模与约定

- 对于 $60\%$ 的评测用例，$n \leq 5000$；
- 对于所有评测用例，$1 \leq n, a_i \leq 10^5$。


---

---
title: "[蓝桥杯 2024 国 Java A] 修改数位"
layout: "post"
diff: 普及/提高-
pid: P12289
tag: ['贪心', '2024', '双指针 two-pointer', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Java A] 修改数位
## 题目描述

给定一个 $n$ 位的没有前导零的十进制数 $m$，你可以将其任意位 $a_i$ 改为任意其它数字 $b_i$，花费为 $|b_i - a_i|$。我们希望通过最少的花费使得修改后的数中存在连续的 $10$ 位，包含了从 $0$ 到 $9$ 的所有数字，且每个数字恰好出现一次。

请输出最少需要的花费是多少（修改后也要求没有前导零）。
## 输入格式

输入一行包含一个整数表示 $m$。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
123456789301
```
### 样例输出 #1
```
1
```
## 提示

### 样例说明

将右边第 $3$ 位改为 $2$ 是一种方案，此时后 $10$ 位恰好含有 $0 \sim 9$ 各一个。

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$1 \leq n \leq 500$；
- 对于 $60\%$ 的评测用例，$1 \leq n \leq 5000$；
- 对于所有评测用例，$1 \leq n \leq 10^6$，请注意 $n$ 表示数位个数。


---

---
title: "[蓝桥杯 2024 国 C] 挑苹果"
layout: "post"
diff: 普及/提高-
pid: P12315
tag: ['2024', '双指针 two-pointer', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 C] 挑苹果
## 题目描述

老师在班级里准备给同学们发苹果，一共有 $n$ 种苹果，第 $i$ 种苹果的美味值为 $a_i$，每名同学需要选择一个非负整数 $x$，这名同学可以获得所有满足条件 $[(a_i + x) \bmod k] \leq t$ 的苹果每种一个。小蓝使用魔法偷偷得知了 $k$ 和 $t$ 的值，小蓝想知道自己最多能获得多少个苹果。

## 输入格式

输入的第一行包含三个正整数 $n, k, t$，相邻整数之间使用一个空格分隔。

第二行包含 $n$ 个正整数 $a_1, a_2, \cdots, a_n$，相邻整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
5 5 1
8 4 6 7 6
```
### 样例输出 #1
```
3
```
## 提示

### 样例说明

取 $x = 4$ 时，第 $3, 4, 5$ 种苹果都能获得。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n, t, k \leq 1000$；
- 对于所有评测用例，$1 \leq n \leq 10^5$，$1 \leq a_i \leq 10^8$，$1 \leq t, k \leq 10^8$。


---

---
title: "穿睡衣军训"
layout: "post"
diff: 普及/提高-
pid: P12597
tag: ['模拟', '字符串', '有限状态自动机', '双指针 two-pointer']
---
# 穿睡衣军训
## 题目背景

在本题中，我们称一个串 $x$ 是一个串 $y$ 的**子串**当且仅当在 $y$ 开头和结尾删除若干个（可以为 $0$ 个）字符后得到的字符串与 $x$ 相同。例如，$\texttt{bc}$,$\texttt{abc}$,$\texttt{a}$,$\texttt{abcd}$ 都是字符串 $\texttt{abcd}$ 的子串，但 $\texttt{abd}$ 不是。

我们称一个串 $x$ 是一个串 $y$ 的**子序列**当且仅当在 $y$ 中删除若干个（可以为 $0$ 个）字符后得到的字符串与 $x$ 相同。例如，$\texttt{bc}$,$\texttt{abc}$,$\texttt{a}$,$\texttt{abcd}$,$\texttt{abd}$ 都是字符串 $\texttt{abcd}$ 的子串，但 $\texttt{dcba}$ 不是。

特别的，空串是任何串的子串，也是任何串的子序列。
## 题目描述

给定两个字符串 $s,t$，扶苏想让你求出一个字符串 $x$，满足：

- $x$ 是 $s$ 的**子串**。
- $x$ 是 $t$ 的**子序列**。
- 在所有满足前述两条的字符串中，$x$ 的长度最长。
- 在所有满足前述三条的字符串中，$x$ 的字典序最小。

请你帮她求出这样的字符串 $x$。
## 输入格式

**本题单个测试点内有多组测试数据**，第一行是一个整数，表示数据组数 $T$。

对每组数据，输入两行，每行一个字符串，依次表示 $s$ 和 $t$。
## 输出格式

对每组数据，输出一行一个字符串，表示你找到的 $x$。  
特别的，如果 $x$ 是空串，你需要输出一个空行。
## 样例

### 样例输入 #1
```
3
xyzdabc
xaybzc
abc
xyz
abbcd
aabbdcd
```
### 样例输出 #1
```
abc

abbcd
```
## 提示

## 数据规模与约定

用 $|x|$ 表示字符串 $x$ 的长度。

- 对 $10\%$ 的数据，$T = 0$。
- 对 $30\%$ 的数据，$|s| = 1$。
- 对 $50\%$ 的数据，$|s|, |t| \leq 10$。
- 对 $80\%$ 的数据，$|s|, |t| \leq 100$。
- 对 $100\%$ 的数据，保证 $0 \leq T \leq 10$，$1 \leq |s|\leq 10^3$，$1 \leq |t| \leq 10^5$，输入字符串只含小写英文字母。


---

---
title: "[EGOI 2025] Gift Boxes"
layout: "post"
diff: 普及/提高-
pid: P13339
tag: ['贪心', '2025', 'Special Judge', '双指针 two-pointer', 'EGOI（欧洲/女生）']
---
# [EGOI 2025] Gift Boxes
## 题目描述

This year's EGOI is organized in Bonn. The organizers want to distribute at most one gift box to every team in the contest, with each team represented by a number from $0$ to $T-1$. The contestants are standing in a single row. However, they are mixed up such that people from the same team might not be standing next to each other. Note that there will be at least one team with more than one person in the row. There are $N$ people in the row. Person $i$ is part of the team $a_i$. The problem is: each team should only receive a maximum of one gift box. In order to ensure the process runs smoothly - and willing to leave some teams with no gift as a consequence - the organizers wish to pause the gifting process exactly once, skipping a few contestants before resuming the gift box handouts. In other words, they will skip one consecutive segment $[\ell, r]$ of the contestants.

It is not necessary that every team receives a gift. Nevertheless, the organizers want to maximize the number of teams that will receive their gifts while ensuring that no team ends up with two or more gifts, equivalent to minimizing the number of contestants that are skipped under this condition. Please help the organizers to decide when it is best to pause and when to continue distributing gifts such that as few contestants as possible are skipped.
## 输入格式

The first line of input contains two integers, $T$ and $N$ – the number of teams and the number of contestants in the row.

The second line contains $N$ integers, $a_i$, where the $i$th integer describes which team the person at position $i$ in the row belongs to. It is guaranteed that every integer between $0$ and $T-1$ appears at least once.
## 输出格式

Output two integers, $\ell$ and $r$, where $\ell$ is the index of the first person that is skipped and $r$ is the index of the last skipped person. Note that $\ell$ and $r$ are indexed from $0$ to $N-1$. If there is more than one solution, print any one of them.
## 样例

### 样例输入 #1
```
4 5
1 3 0 2 3
```
### 样例输出 #1
```
1 1
```
### 样例输入 #2
```
3 6
1 0 2 2 1 0
```
### 样例输出 #2
```
0 2
```
### 样例输入 #3
```
4 8
0 2 0 1 2 1 3 3
```
### 样例输出 #3
```
2 6
```
### 样例输入 #4
```
3 6
1 1 2 0 1 0
```
### 样例输出 #4
```
0 3
```
### 样例输入 #5
```
4 6
0 1 2 0 3 2
```
### 样例输出 #5
```
2 3
```
### 样例输入 #6
```
5 13
3 3 3 1 2 0 3 3 2 1 4 1 0
```
### 样例输出 #6
```
1 9
```
## 提示

### Examples

The first sample satisfies the constraints of test groups 1, 3, 5 and 6. Two different outputs are possible: $1 \ 1$ corresponding to the solid blue line and $4 \ 4$ corresponding to the red dotted line, as described in the picture below. Either way, all four teams receive gifts and no team receives more than one gift.

$\begin{array}{lllll} 1 & \blue 3 & 0 & 2 & \red 3 \end{array}$

The second sample satisfies the constraints of test groups 2, 3, 4, 5 and 6. Again, two different outputs are possible: $0 \ 2$ and $3 \ 5$, as described in the picture below. In both cases, all three teams receive gifts.

$\begin{array}{lllll} \blue 1 & \blue 0 & \blue 2 & \red 2 & \red 1 & \red 0 \end{array}$

The third sample satisfies the constraints of test groups 3, 4, 5, 6. The optimal solution is that three teams receive a gift, as shown below. The contestants with indices 0, 1 and 7, who are in teams 0, 2 and 3, respectively, receive gifts. This is the only possible solution.

$\begin{array}{lllllll} 0 & 2 & \blue 0 & \blue 1 & \blue 2 & \blue 1 & \blue 3 & 3 \end{array}$

The fourth sample satisfies the constraints of test groups 3, 5 and 6. Again two different outputs are possible: $0 \ 3$ and $1 \ 4$, as described in the picture below. In both cases, exactly two teams (team 0 and team 1) receive gifts. Team 2 does not receive a gift as doing so would require giving team 0 or 1 two gifts, which is strictly forbidden.

$\begin{array}{lllllll} \blue 1 & \blue 1 & \blue 2 & \blue 0 & 1 &  0 \end{array}$

$\begin{array}{lllllll}  1 & \red 1 & \red 2 & \red 0 & \red 1 &  0 \end{array}$

The fifth sample satisfies the constraints of test groups 3, 5 and 6. The only possible answer is $2 \ 3$, as described in the picture below. All four teams receive gifts.

$\begin{array}{lllllll} 0 & 1 & \blue 2 & \blue 0 & 3 & 2 \end{array}$

The sixth sample satisfies the constraints of test groups 3, 5 and 6. A maximum of four out of five teams can receive a gift, as shown below. The contestants with indices 0, 10, 11 and 12, who are in teams 3, 4, 1 and 0, respectively, receive gifts. This is the only possible solution.

$\begin{array}{lllllll} 3 & \blue 3 & \blue 3 & \blue 1 & \blue 2 & \blue 0 & \blue 3 & \blue 3 & \blue 2 & \blue 1 & 4 & 1 & 0 \end{array}$

### Constraints and Scoring

* $1 \leq T < N \leq 500\,000$.
* $0 \leq a_i \leq T-1$.

Your solution will be tested on a set of test groups, each worth a number of points. Each test group contains a set of test cases. To get the points for a test group, you need to solve all test cases in the test group.

| Group | Score | Limits |
| :-: | :-: | :-: |
| 1 | 8 | $N = T + 1$, i.e. only one team will appear twice |
| 2 | 11 | $N = 2 \cdot T$ and every team will appear exactly once in the first half and exactly once in the second half of the line |
| 3 | 14 | $1 \leq T < N \leq 500$ |
| 4 | 21 | $N = 2 \cdot T$ and every team will appear twice |
| 5 | 22 | $1 \leq T < N \leq 5\,000$ |
| 6 | 24 | No additional constraints |


---

---
title: "【MGVOI R1-B】完美重排（sort）"
layout: "post"
diff: 普及/提高-
pid: P13730
tag: ['二分', 'O2优化', '排序', '前缀和', '双指针 two-pointer']
---
# 【MGVOI R1-B】完美重排（sort）
## 题目描述

Siby 同学有一个长度为 $n$ 的数组 $a$，其下标编号为 $1 \sim n$。保证数组 $a$ 是一个长度为 $n$ 的排列，也就是说，$1\sim n$ 中的每个正整数都在数组 $a$ 中出现 **恰好一次**。

在此基础上，Siby 同学定义了 **完美重排** 操作：

::::info[完美重排的定义]{open}

* 第一步：选择两个下标 $L,R$（必须满足 $1\le L\le R\le n$）；
  
* 第二步：将 $a_L,...,a_R$ （即数组 $a$ 中下标在 $L$ 和 $R$ 之间的元素）按照 **从小到大** 的顺序重新排序。

::::

例如，若 $a=[4,3,2,1]$，选择 $L=2,R=4$ 进行一次完美重排操作（也就是将 $a_2,a_3,a_4$ 按照从小到大的顺序排序），得到的新数组为 $a'=[4,1,2,3]$。

接下来，他将进行 $Q$ 组询问（询问之间彼此独立），其中第 $i$ 组询问包含两个参数 $x_i,y_i$（$x_i< y_i$），表示询问你有多少种进行 **恰好一次** 完美重排的方案，使得数组 $a$ 中原先下标为 $x_i$ 的元素，在重排后的下标为 $y_i$。

提示：只要完美重排操作中选择的 $L$ 不同或 $R$ 不同，就被认为是两种不同的方案。
## 输入格式

第一行包含两个正整数 $n,Q$，分别表示数组 $a$ 的长度和询问的次数。

第二行包含 $n$ 个正整数，其中第 $i$ 个正整数表示数组 $a$ 中的元素 $a_i$（$1\le a_i\le n$）。

接下来 $Q$ 行，其中第 $i$ 行包含两个正整数 $x_i,y_i$（$1\le x_i< y_i \le n$），表示第 $i$ 组询问的两个参数。
## 输出格式

共输出 $Q$ 行。

对于第 $i$ 组询问而言：仅需在第 $i$ 行输出一个非负整数，表示完美重排的方案数。方案应进行恰好一次完美重排，使得数组 $a$ 中原先下标为 $x_i$ 的元素，在重排后的下标为 $y_i$。


## 样例

### 样例输入 #1
```
4 3
3 4 1 2
1 3
1 4
2 4
```
### 样例输出 #1
```
1
0
2
```
### 样例输入 #2
```
7 10
6 3 5 7 2 4 1
1 3
1 4
1 7
2 3
2 4
2 5
3 5
4 6
5 6
6 7

```
### 样例输出 #2
```
2
1
0
3
1
0
3
4
1
2
```
## 提示


**【样例 #1】**

::::info[样例 #1 解释]
此样例下，$a=[3,4,1,2]$。

* 对于第一组询问：只需取 $L=1，R=4$ 进行一次完美重排，就能使得 $a_1$ 在重排后的下标为 $3$（重排前：$a=[\red{3},4,1,2]$，重排后：$a'=[1,2,\red{3},4]$）。可以证明这是唯一的一种方案，故方案数为 $1$；

* 对于第二组询问：可以证明，无论如何选取 $L,R$，都不可能使得 $a_1$ 在重排后的下标为 $4$，故方案数为 $0$；

* 对于第三组询问：

1. 第一种方案是取 $L=1，R=4$ 进行一次完美重排（重排前：$a=[3,\red{4},1,2]$，重排后：$a'=[1,2,3,\red{4}]$）；
  
2. 第二种方案是取 $L=2，R=4$ 进行一次完美重排（重排前：$a=[3,\red{4},1,2]$，重排后：$a'=[3,1,2,\red{4}]$），可以验证均满足条件。不存在其它满足条件的方案了，故方案数为 $2$。
::::


**【样例 #2】**

::::info[样例 #2 解释]
此样例下，$a=[6,3,5,7,2,4,1]$。

为了简便，我们用数对 $(i,j)$ 来表示选取 $L=i$，$R=j$ 进行一次完美重排的方案。各组询问对应的所有方案见下表：

| 询问编号 | 方案数 | 方案 1 | 方案 2 | 方案 3 | 方案 4 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| **1** | $2$ | $(1,3)$ | $(1,4)$
| **2** | $1$ | $(1,5)$
| **3** | $0$ |
| **4** | $3$ | $(1,7)$ | $(2,5)$ | $(2,6)$
| **5** | $1$ | $(2,7)$
| **6** | $0$ |
| **7** | $3$ | $(1,7)$ | $(2,6)$ | $(3,6)$
| **8** | $4$ | $(1,6)$ | $(2,6)$ | $(3,6)$ | $(4,6)$ 
| **9** | $1$ | $(5,7)$ |
| **10** | $2$ | $(5,7)$ | $(6,7)$ |

::::



**【样例 #3】**

见附件中的 ```sort/sort3.in``` 与 ```sort/sort3.ans```。

这个样例满足测试点 $7 \sim 12$ 的限制。

**【样例 #4】**

见附件中的 ```sort/sort4.in``` 与 ```sort/sort4.ans```。

这个样例满足测试点 $13 \sim 14$ 的限制。

**【样例 #5】**

见附件中的 ```sort/sort5.in``` 与 ```sort/sort5.ans```。

这个样例满足测试点 $15 \sim 20$ 的限制。



---




**【数据范围】**

对于所有测试点，保证 $2\le n\le 10^4$，$1\le Q\le 2\times 10^3$，$1\le x_i< y_i\le n$，且数组 $a$ 是 $1\sim n$ 的排列。

::cute-table{tuack}

| **测试点编号** | $n \le$ | $Q \le$ |  **特殊性质** |
|:-:|:-:|:-:|:-:|
| $1 \sim 6$ | $20$ | $20$ | 无 | 
| $7 \sim 12$ | $500$ | $100$ | ^ | 
| $13 \sim 14$ | $10^4$ | $2\times 10^3$ | **A** | 
| $15 \sim 20$ | ^ | ^ | 无 | 

特殊性质 **A**：保证 $a_i=n-i+1$。

* 分值分配：每个测试点的分值为 $5$ 分。
  
* 请注意本题特殊的内存限制。


---

---
title: "Clock Paradox"
layout: "post"
diff: 普及/提高-
pid: P13760
tag: ['数学', 'O2优化', '前缀和', '双指针 two-pointer']
---
# Clock Paradox
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/a4u4v5x2.png)

（来自 phigros 曲绘，侵删）
## 题目描述

给定一个序列 $a$，要求区间 $[l,r]$ 满足 $a_l$ 至 $a_r$ 每个数只在该区间出现一次。设共 $t$ 个区间满足要求，编号为 $[l_1,r_1]$ 至 $[l_t,r_t]$。

求：

$$\sum_{i=1}^t\sum_{j=l_i}^{r_i}a_j$$

请将答案对 $10^9+7$ 取模。
## 输入格式

第一行输入一个自然数 $n$，表示序列长度。

第二行输入 $n$ 个非负整数，表示序列 $a$。
## 输出格式

一行一个非负整数，表示答案取模 $10^9+7$ 后的数。
## 样例

### 样例输入 #1
```
6
1 2 3 3 2 1
```
### 样例输出 #1
```
40
```
### 样例输入 #2
```
13
1 1 4 5 1 4 1 9 1 9 8 1 0
```
### 样例输出 #2
```
239
```
### 样例输入 #3
```
10 
5 4 3 2 5 6 1 3 1 4
```
### 样例输出 #3
```
315
```
## 提示

数据范围
| 测试点编号 | $n$ | $a_i$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: |:-----------: |
| $1$ | $n\le2×10^5$ | $0\le a_i\le10^9$ | A |
| $2$ | $n\le2×10^5$ | $0\le a_i\le10^9$ | B |
| $3,4$ | $n\le 2×10^5$| $0\le a_i\le1$ | |
|$5,6$|$n\le500$|$0\le a_i\le10^9$ | |
|$7\sim10$|$n\le 5×10^3$|$0\le a_i\le n$| |
|$11\sim20$|$n\le2×10^5$|$0\le a_i\le10^9$| |

特殊性质 A：满足所有 $a_i$ 都相等。

特殊性质 B：满足所有 $a_i$ 都互不相等。

对于 $100\%$ 的数据，满足 $1\le n\le2×10^5,0\le a_i\le 10^9$。



---

---
title: " 「CZOI-R6」Permutation and Subsequence"
layout: "post"
diff: 普及/提高-
pid: P13788
tag: ['动态规划 DP', 'O2优化', '双指针 two-pointer']
---
#  「CZOI-R6」Permutation and Subsequence
## 题目描述

给定两个长为 $n$ 的由 $1 \sim n$ 构成的**排列** $a, b$。你需要求出有多少个 $a$ 的 **非空** 连续子段是 $b$ 的子序列。

序列 $c$ 是序列 $a$ 的连续子段，当且仅当在序列 $a$ 的 *开头和结尾* 各删除若干（可能为 $0$）个元素，能够得到序列 $c$；序列 $c$ 是序列 $b$ 的子序列，当且仅当在序列 $b$ 中 *任意位置* 删除若干（可能为 $0$）个元素，能够得到序列 $c$。
## 输入格式

第一行输入 $1$ 个整数 $n$。

第二行输入 $n$ 个整数，表示排列 $a_1, \ldots, a_n$。

第三行输入 $n$ 个整数，表示排列 $b_1, \ldots, b_n$。
## 输出格式

第一行输出 $1$ 个整数，表示答案。
## 样例

### 样例输入 #1
```
5
3 5 2 4 1 
2 4 5 3 1 
```
### 样例输出 #1
```
8
```
## 提示

**【数据范围】**

**本题采用捆绑测试。**

- Subtask #1（$10\ \text{pts}$）：$n\le 5$。
- Subtask #2（$30\ \text{pts}$）：$n\le 10^3$。
- Subtask #3（$30\ \text{pts}$）：$a_i=i$。
- Subtask #4（$30\ \text{pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le n\le 10^6$，$a,b$ 构成 $1 \sim n$ 的排列。


---

---
title: "逛画展"
layout: "post"
diff: 普及/提高-
pid: P1638
tag: ['二分', 'USACO', '单调队列', '队列', '双指针 two-pointer']
---
# 逛画展
## 题目描述


博览馆正在展出由世上最佳的 $m$ 位画家所画的图画。

游客在购买门票时必须说明两个数字，$a$ 和 $b$，代表他要看展览中的第 $a$ 幅至第 $b$ 幅画（包含 $a,b$）之间的所有图画，而门票的价钱就是一张图画一元。

Sept 希望入场后可以看到所有名师的图画。当然，他想最小化购买门票的价格。

请求出他购买门票时应选择的 $a,b$，数据保证一定有解。

若存在多组解，**输出 $a$ 最小的那组**。
## 输入格式

第一行两个整数 $n,m$，分别表示博览馆内的图画总数及这些图画是由多少位名师的画所绘画的。

第二行包含 $n$ 个整数 $a_i$，代表画第 $i$ 幅画的名师的编号。

## 输出格式

一行两个整数 $a,b$。
## 样例

### 样例输入 #1
```
12 5
2 5 3 1 3 2 4 1 1 5 4 3

```
### 样例输出 #1
```
2 7
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，有 $n\le200$，$m\le20$。
- 对于 $60\%$ 的数据，有 $n\le10^5$，$m\le10^3$。
- 对于 $100\%$ 的数据，有 $1\leq n\le10^6$，$1 \leq a_i \leq m\le2\times10^3$。


---

---
title: "[USACO11NOV] Cow Lineup S"
layout: "post"
diff: 普及/提高-
pid: P3029
tag: ['2011', 'USACO', '单调队列', '离散化', '队列', '双指针 two-pointer']
---
# [USACO11NOV] Cow Lineup S
## 题目描述

Farmer John has hired a professional photographer to take a picture of some of his cows.  Since FJ's cows represent a variety of different breeds, he would like the photo to contain at least one cow from each distinct breed present in his herd.

FJ's N cows are all standing at various positions along a line, each described by an integer position (i.e., its x coordinate) as well as an integer breed ID.  FJ plans to take a photograph of a contiguous range of cows along the line.  The cost of this photograph is equal its size -- that is, the difference between the maximum and minimum x coordinates of the cows in the range of the photograph.

Please help FJ by computing the minimum cost of a photograph in which there is at least one cow of each distinct breed appearing in FJ's herd.

## 输入格式

\* Line 1: The number of cows, N (1 <= N <= 50,000). 

\* Lines 2..1+N: Each line contains two space-separated positive integers specifying the x coordinate and breed ID of a single cow.  Both numbers are at most 1 billion.

## 输出格式

\* Line 1: The smallest cost of a photograph containing each distinct breed ID.

## 样例

### 样例输入 #1
```
6 
25 7 
26 1 
15 1 
22 3 
20 1 
30 1 

```
### 样例输出 #1
```
4 

```
## 提示

There are 6 cows, at positions 25,26,15,22,20,30, with respective breed IDs 7,1,1,3,1,1.


The range from x=22 up through x=26 (of total size 4) contains each of the distinct breed IDs 1, 3, and 7 represented in FJ's herd.

## 题目翻译

### 问题描述

农民约翰雇一个专业摄影师给他的部分牛拍照。由于约翰的牛有好多品种，他喜欢他的照片包含每个品种的至少一头牛。

约翰的牛都站在一条沿线的不同地方， 每一头牛由一个整数位置 $X_i$ 以及整数品种编号 $ID_i$ 表示。

约翰想拍一张照片，这照片由沿线的奶牛的连续范围组成。照片的成本与规模相当，这就意味着，在一系列照片中的最大和最小 $X$ 坐标的差距决定了照片的成本。

请帮助约翰计算最小的照片成本，这些照片中有每个不同的品种的至少一头牛，没有两头牛愿意站在同一个地点的。


### 输入格式 


第 $1$ 行：牛的数量 $N$；


第 $2..1+N$ 行：每行包含 2 个以空格分隔的正整数 $X_i$ 和 $ID_i$；意义如题目描述；


### 输出格式 


输出共一行，包含每个不同品种 $\rm ID$ 的照片的最低成本。


---

---
title: "[USACO16OPEN] Diamond Collector S"
layout: "post"
diff: 普及/提高-
pid: P3143
tag: ['贪心', '2016', 'USACO', '枚举', '双指针 two-pointer']
---
# [USACO16OPEN] Diamond Collector S
## 题目描述

Bessie the cow, always a fan of shiny objects, has taken up a hobby of mining diamonds in her spare time!  She has collected $N$ diamonds ($N \leq 50,000$) of varying sizes, and she wants to arrange some of them in a pair of  display cases in the barn.


Since Bessie wants the diamonds in each of the two cases to be relatively similar in  size, she decides that she will not include two diamonds in the same case if their sizes differ by more than $K$ (two diamonds can be displayed together in the same case if their sizes differ by exactly $K$).  Given $K$, please help Bessie determine the maximum number of diamonds she can display in both cases together.
## 输入格式

The first line of the input file contains $N$ and $K$ ($0 \leq K \leq 1,000,000,000$).

The next $N$ lines each contain an integer giving the size of one of the diamonds.  All sizes will be positive and will not exceed $1,000,000,000$.

## 输出格式

Output a single positive integer, telling the maximum number of diamonds that Bessie can showcase in total in both the cases.
## 样例

### 样例输入 #1
```
7 3
10
5
1
12
9
5
14
```
### 样例输出 #1
```
5
```
## 题目翻译

### 题目描述

奶牛 Bessie 一直喜欢闪闪发光的物体，她最近在业余时间开始了一项爱好——挖掘钻石！她收集了 $N$ 颗大小各不相同的钻石（$N \leq 50,000$），并希望将它们中的一部分放在谷仓里的两个展示柜中展示。

由于 Bessie 希望每个展示柜中的钻石大小相对接近，她决定如果两颗钻石的大小相差超过 $K$，就不能将它们放在同一个展示柜中（如果两颗钻石的大小相差恰好为 $K$，则可以将它们一起展示在同一个展示柜中）。给定 $K$，请帮助 Bessie 确定她可以在两个展示柜中一起展示的最大钻石数量。

### 输入格式

输入文件的第一行包含 $N$ 和 $K$（$0 \leq K \leq 1,000,000,000$）。

接下来的 $N$ 行每行包含一个整数，表示一颗钻石的大小。所有钻石的大小均为正数且不超过 $1,000,000,000$。

### 输出格式

输出一个正整数，表示 Bessie 可以在两个展示柜中一起展示的最大钻石数量。


---

---
title: "[蓝桥杯 2020 省 A1] 整数小拼接"
layout: "post"
diff: 普及/提高-
pid: P8708
tag: ['2020', '枚举', '双指针 two-pointer', '蓝桥杯省赛']
---
# [蓝桥杯 2020 省 A1] 整数小拼接
## 题目描述

给定一个长度为 $n$ 的数组 $A_1,A_2,\cdots,A_n$。你可以从中选出两个数 $A_i$ 和 $A_j$($i\neq j$)，然后将 $A_i$ 和 $A_j$ 一前一后拼成一个新的整数。例如 `12` 和 `345` 可以拼成 `12345` 或 `34512`。注意交换 $A_i$ 和 $A_j$ 的顺序总是被视为 $2$ 种拼法，即便是 $A_i=A_j$ 时。

请你计算有多少种拼法满足拼出的整数小于等于 $K$。

## 输入格式

第一行包含 $2$ 个整数 $n$ 和 $K$。

第二行包含 $n$ 个整数 $A_1,A_2,\cdots,A_n$。
## 输出格式

一个整数代表答案。
## 样例

### 样例输入 #1
```
4 33
1 2 3 4
```
### 样例输出 #1
```
8
```
## 提示

对于 $30\%$ 的评测用例 $1\le n\le1000$，$1\le k\le10^8$，$1\le A_i\le10^4$。

对于所有评测用例，$1\le n\le10^5$，$1\le k\le10^{10}$，$1\le A_i\le10^9$。

蓝桥杯 2020 第一轮省赛 A 组 H 题。


---

---
title: "[蓝桥杯 2022 省 B] 统计子矩阵"
layout: "post"
diff: 普及/提高-
pid: P8783
tag: ['2022', '枚举', '双指针 two-pointer', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 B] 统计子矩阵
## 题目描述

给定一个 $N \times M$ 的矩阵 $A$，请你统计有多少个子矩阵 (最小 $1 \times 1$, 最大 $N \times M)$ 满足子矩阵中所有数的和不超过给定的整数 $K$。

## 输入格式

第一行包含三个整数 $N, M$ 和 $K$。

之后 $N$ 行每行包含 $M$ 个整数, 代表矩阵 $A$。
## 输出格式

一个整数代表答案。
## 样例

### 样例输入 #1
```
3 4 10
1 2 3 4
5 6 7 8
9 10 11 12
```
### 样例输出 #1
```
19
```
## 提示

**【样例说明】**

满足条件的子矩阵一共有 $19$，包含:

大小为 $1 \times 1$ 的有 $10$ 个。

大小为 $1 \times 2$ 的有 $3$ 个。 大小为 $1 \times 3$ 的有 $2$ 个。

大小为 $1 \times 4$ 的有 $1$ 个。

大小为 $2 \times 1$ 的有 $3$ 个。

**【评测用例规模与约定】**

对于 $30 \%$ 的数据, $N, M \leq 20$.

对于 $70 \%$ 的数据, $N, M \leq 100$.

对于 $100 \%$ 的数据, $1 \leq N, M \leq 500,0 \leq A_{i j} \leq 1000,1 \leq K \leq 2.5\times10^8$. 

蓝桥杯 2022 省赛 B 组 F 题。


---

---
title: "[CCC 2023 S2] Symmetric Mountains"
layout: "post"
diff: 普及/提高-
pid: P9325
tag: ['模拟', '2023', '枚举', 'CCC（加拿大）', '区间 DP', '双指针 two-pointer']
---
# [CCC 2023 S2] Symmetric Mountains
## 题目描述

Rebecca is a tour guide and is trying to market the Rocky Mountains for her magazine. She recently took a beautiful picture consisting of $N$ mountains where the $i\text{-th}$ mountain from the left has a height $h_i$. She will crop this picture for her magazine, by possibly removing some mountains from the left side of the picture and possibly removing some mountains from the right side of the picture. That is, a crop consists of consecutive mountains starting from the $l\text{-th}$ to the $r\text{-th}$ mountain where $l \leq r$. To please her magazine readers, Rebecca will try to find the most symmetric crop.

We will measure the $asymmetric\ value$ of a crop as the sum of the absolute difference for every pair of mountains equidistant from the midpoint of the crop. To help understand that definition, note that the absolute value of $a$ number $v$, written as $|v|$, is the non-negative value of v: for example $\lvert -6 \rvert = 6$ and $|14| = 14$. The asymmetric value of a crop is the sum of all $|h_{l+i} - h_{r-i}|$ for $0 \leq i \leq \frac{r-l}{2}$. To put that formula in a different way, we pair up the mountains working from the outside in toward the centre, calculate the absolute difference in height of each of these pairs, and sum them up.

Because Rebecca does not know how wide the picture needs to be, for all possible crop lengths, find the asymmetric value of the most symmetric crop (the crop with the minimum asymmetric value).
## 输入格式

The first line consists of an integer $N$, representing the number of mountains in the picture.

The second line consists of $N$ space-separated integers, where the $i\text{-th}$ integer from the left represents $h_i$.

The following table shows how the available 15 marks are distributed:

| Marks | Bounds on $N$ | Bounds on $h_i$ | Additional Constraints |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $5$ | $1 \leq N \leq 300$ | $0 \leq h_i \leq 10^5$ | None. |
| $5$ | $1 \leq N \leq 5000$ | $0 \leq h_i \leq 10^5$ | Height of mountains are in non-decreasing order from left to right. |
| $5$ | $1 \leq N \leq 5000$ | $0 \leq h_i \leq 10^5$ | None. |

## 输出格式

Output on one line $N$ space-separated integers, where the $i\text{-th}$ integer from the left is the asymmetric value of the most symmetric picture of crops of length $i$.
## 样例

### 样例输入 #1
```
7
3 1 4 1 5 9 2
```
### 样例输出 #1
```
0 2 0 5 2 10 10
```
### 样例输入 #2
```
4
1 3 5 6
```
### 样例输出 #2
```
0 1 3 7
```
## 提示

Explanation of Output for Sample Input $1$:

We will show why the fifth value from the left is $2$.Let us try to compute all the asymmetric values of crops with length $5$.

The height of the mountains in the first crop is $[3, 1, 4, 1, 5]$. The asymmetric value of this crop is $|3 - 5| + |1 - 1| + |4 - 4| = 2$.

The height of the mountains in the second crop is $[1, 4, 1, 5, 9]$. The asymmetric value of this crop is $|1 - 9| + |4 - 5| + |1 - 1| = 9$.

The height of the mountains in the last crop is $[4, 1, 5, 9, 2]$. The asymmetric value of this crop is $|4 - 2| + |1 - 9| + |5 - 5| = 10$.

Hence, the most symmetric crop of length $5$ is $2$.

Explanation of Output for Sample Input $2$:

This sample satisfies the second subtask. Note that the only crop of length $4$ is $[1, 3, 5, 6]$ which has asymmetric value of $|1 - 6| + |3 - 5| = 7$.

**本题采用捆绑测试**：

- Subtask 1（5 points）：$1\leq N \leq 300$，$0\leq h_i \leq 10^5$。

- Subtask 2（5 points）：$1 \leq N \leq 5000$，$0 \leq h_i \leq 10^5$，保证山的高度从左到右单调不减。

- Subtask 3（5 points）：$1\leq N\leq 5000$，$0 \leq h_i \leq 10^5$。
## 题目翻译

Rebecca 有一张落基山脉的照片，上面排列着 $N(1\leq N \leq 5000)$ 座山，从左向右的第 $i$ 座山的高度是 $h_i(1\leq h_i \leq 10^5)$。Rebecca 截图保留照片的一个连续段，这张截图的不对称性定义为：处于截图上对称位置的山的高度差的绝对值之和（截图最左和最右的山的高度差，左数第二和右数第二的山的高度差，诸如此类的和）。

Rebecca 想要知道对于长度为 $i$ 的截图，拥有的最小不对称性。请你对于 $1\leq i \leq N$，输出这个值。


---

---
title: "「RiOI-03」匀速相遇"
layout: "post"
diff: 普及/提高-
pid: P9914
tag: ['洛谷原创', 'O2优化', '哈希 hashing', '洛谷月赛', '双指针 two-pointer']
---
# 「RiOI-03」匀速相遇
## 题目背景

当大家都在加速时，我与你，在人生中的十字路口，匀速地相遇了。

确是惊动我心的一瞥，却是无法逗留的遗憾，我们再次，朝着自己的方向匀速奔跑。下次再见，又会是什么时候呢……
## 题目描述

平面直角坐标系上有 $n + m$ 个点，其中：

- 有 $n$ 个 $\rm A$ 类点，它们在初始时依次位于位置 $(1, 0), (2, 0), (3, 0), \dots, (n, 0)$。
- 有 $m$ 个 $\rm B$ 类点，它们在初始时依次位于位置 $(0, 1), (0, 2), (0, 3), \dots, (0, m)$。

在某一个时刻，$\rm A, B$ 类点同时开始运动。具体地：

- 对于第 $i$ 个 $\rm A$ 类点，其以 $a_i$ 个单位长度每秒的速度向上（即 $y$ 轴正方向）匀速运动。特别地，若 $a_i = 0$，则该点始终保持静止。
- 对于第 $i$ 个 $\rm B$ 类点，其以 $b_i$ 个单位长度每秒的速度向右（即 $x$ 轴正方向）匀速运动。特别地，若 $b_i = 0$，则该点始终保持静止。

相遇与分离实在是再平凡不过的了。作为匆匆时光里的一名过客，在这个你暂留的驿站里，你能否帮小 T 解决这个简单的问题：求出有多少点对会在某个时刻相遇，即它们在某一刻共点。

由于你无法使时间静止，所以所有点无论相遇与否，都会永无止境地运动下去。祝愿在这道路上奔跑的你，能有一天与理想匀速相遇，永不停息。
## 输入格式

第一行两个正整数 $n, m$。

第二行 $n$ 个整数 $a_1\dots a_n$，依次表示第 $1\dots n$ 个 $\rm A$ 类点的运动速度。

第三行 $m$ 个整数 $b_1\dots b_m$，依次表示第 $1\dots m$ 个 $\rm B$ 类点的运动速度。
## 输出格式

一行一个整数，表示有多少点对会在某个时刻相遇。
## 样例

### 样例输入 #1
```
3 3
1 2 3
3 2 1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3 3
2 5 1
83 101 98
```
### 样例输出 #2
```
0
```
## 提示

### 样例解释 1

当 $t = 1$ 时，第 $2$ 个 $\rm A$ 类点和第 $2$ 个 $\rm B$ 类点同时到达点 $(2, 2)$。这也是在本组样例中的唯一一次相遇，故输出 $1$。

### 数据规模与约定

**本题开启捆绑测试。**

+ Subtask 0（10 pts）：$n \leq 10$，$m \leq 10$。
+ Subtask 1（20 pts）：$n \leq 5\times 10^3$，$m \leq 5\times 10^3$。
+ Subtask 2（30 pts）：保证 $\forall a_i \geq 1$，$\forall b_i \geq 1$。
+ Subtask 3（40 pts）：无特殊限制。

对于所有数据，$1 \leq n, m \leq 10^6$，$0 \leq a_i, b_i \leq 10^9$。


---

