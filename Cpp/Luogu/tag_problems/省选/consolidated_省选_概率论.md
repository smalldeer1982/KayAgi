---
title: "[USACO24JAN] Merging Cells P"
layout: "post"
diff: 省选/NOI-
pid: P10141
tag: ['动态规划 DP', 'USACO', '2024', '概率论']
---
# [USACO24JAN] Merging Cells P
## 题目背景

**注意：本题的内存限制为 512MB，通常限制的两倍。**
## 题目描述

Bessie 正在玩一个著名的在线游戏，游戏中有许多不同编号和大小的细胞。细胞会被其他细胞吞噬，直到只剩下一个胜利者。

有 $N$（$2\le N\le 5000$）个细胞从左到右排成一行，编号为 $1\ldots N$，初始大小为 $s_1,s_2,\ldots,s_N$（$1\le s_i\le 10^5$）。当存在多个细胞时，均匀地随机选择一对相邻细胞，并根据以下规则合并为一个新的细胞：

如果编号为 $a$ 且当前大小为 $c_a$ 的细胞与编号为 $b$ 且当前大小为 $c_b$ 的细胞合并，则合并成的细胞的大小为 $c_a+c_b$，且编号等于较大细胞的编号，并列时则为编号较大的细胞的编号。形式化地说，合并成的细胞的编号为 $\begin{cases}a & c_a>c_b\\b & c_a<c_b\\ \max(a,b) & c_a=c_b \end{cases}$。

对于 $1\ldots N$ 范围内的每个编号 $i$，最终的细胞具有编号 $i$ 的概率可以以 $\frac{a_i}{b_i}$ 的形式表示，其中 $b_i\not \equiv 0 \pmod {10^9+7}$。输出 $a_ib_i^{-1}\pmod {10^9+7}$。 
## 输入格式

输入的第一行包含 $N$。

第二行包含 $s_1,s_2,\ldots,s_N$。 
## 输出格式

对于 $1\ldots N$ 内的每个 $i$ 输出一行，为输出最终的细胞具有编号 $i$ 的概率模 $10^9+7$ 的余数。 
## 样例

### 样例输入 #1
```
3
1 1 1
```
### 样例输出 #1
```
0
500000004
500000004
```
### 样例输入 #2
```
4
3 1 1 1
```
### 样例输出 #2
```
666666672
0
166666668
166666668
```
## 提示

### 样例解释 1

存在两种可能性，其中 $(a,b)\to c$ 表示编号为 $a$ 和 $b$ 的细胞合并成了一个编号为 $c$ 的新的细胞。

$(1, 2) \to 2, (2, 3) \to 2$  
$(2, 3) \to 3, (1, 3) \to 3$

所以有各 $\frac{1}{2}$ 的概率最终的细胞具有编号 $2$ 或 $3$。


### 样例解释 2

六种可能性如下：

$(1, 2) \to 1, (1, 3) \to 1, (1, 4) \to 1$  
$(1, 2) \to 1, (3, 4) \to 4, (1, 4) \to 1$  
$(2, 3) \to 3, (1, 3) \to 1, (1, 4) \to 1$  
$(2, 3) \to 3, (3, 4) \to 3, (1, 3) \to 3$  
$(3, 4) \to 4, (2, 4) \to 4, (1, 4) \to 4$  
$(3, 4) \to 4, (1, 2) \to 1, (1, 4) \to 1$

所以有 $\frac{2}{3}$ 的概率最终的细胞具有编号 $1$，各 $\frac{1}{6}$ 的概率最终的细胞具有编号 $3$ 或 $4$。

### 测试点性质

- 测试点 3：$N\le 8$。
- 测试点 $4-8$：$N\le 100$。
- 测试点 $9-14$：$N\le 500$。
- 测试点 $15-22$：没有额外限制。


---

---
title: "「HOI R1」杂交选种"
layout: "post"
diff: 省选/NOI-
pid: P10384
tag: ['2024', '交互题', 'Special Judge', '概率论', '洛谷比赛']
---
# 「HOI R1」杂交选种
## 题目背景

$\clubsuit$ 星球盛产“代马”，其优越的速度与耗能使得它风靡整个银河系。可小 $\iiint$ 并不满足于此，他想培育出更好的“代马”，并取代掉还在用传统能源的落后四足兽。于是，他开始研究基因技术……

**本题仅支持 C++ 语言提交。**

**由于技术限制，请勿使用 C++14 (GCC 9) 语言提交，否则将会得到 Compile Error 的结果。**

你的代码中需如下进行 `query` 和 `cross` 函数的声明：

```cpp
char query(int k);
void cross(int i, int j);
```

调用 $10^6$ 次 `query` 与 `cross` 函数的时间不超过 50 毫秒，除这两个函数所占用的时间外，交互库运行所占用的时间不超过 100 毫秒。
## 题目描述

#### 【形式化题意】

**这是一道交互题。**

定义 **基因** 为一个字符，其内容为 $\verb!A!$ 或 $\verb!a!$。定义 **基因型** 为由两个基因组成，且大写字母在小写字母之前的字符串。也即 $\{\verb!aa!,\verb!Aa!,\verb!AA!\}$ 中的一种。一个基因型的 **表现** 如下：

- 若基因型中含有 $\verb!A!$，则表现为 $\verb!A!$。
- 否则，表现为 $\verb!a!$。

两个基因型可以相互 **杂交**，其定义如下：

- 在两个基因型中各均匀随机取一个基因，并将两个基因组合成基因型作为结果输出。

小 $\iiint$ 有 $n$ 个基因型，编号为 $1,2,\cdots,n$。每次询问可以给交互库两个不同的编号 $i,j$。若当前是第 $k$ 次杂交，交互库会新建一个编号为 $n+k$ 的基因型，其基因型为 $i,j$ 杂交后的结果。

你可以在时限范围内任意次查询编号为 $x$ 的种子的表现。你需要在 $4.5\times10^5$ 次杂交内，求出初始给定的 $n$ 个基因型。

### 实现细节

**你不需要，也不应该实现主函数。** 你需要实现下面的函数：

```cpp
vector<string> guess(int n)
```

- $n$ 表示初始基因型个数。
- 该函数应当返回一个长度恰好为 $n$ 的数组，数组中的每一个元素是一个长度为二的字符串，表示你所求出的基因型。**你需要保证大写字母在小写字母的前面**。
- 对于每个测试点，该函数被恰好调用一次。

该函数可调用以下函数：

```cpp
char query(int k)
```

- $k$ 表示你要查询的基因型的编号。**你需要保证这个编号对应的基因型存在**。
- 该函数将返回该基因型的表现。
- 该函数可以在时限内被调用任意次。

```cpp
void cross(int i, int j)
```

- $i,j$ 代表你要杂交的两个基因的编号。**你需要保证 $i\not=j$ 且对应的基因型存在**。
- 若是第 $k$ 次调用该函数，该函数会新建一个编号为 $n+k$ 的基因型，其基因型为 $i,j$ 杂交后的结果。保证杂交过程为均匀随机。
- 你最多可以调用该函数 $4.5\times10^5$ 次。
- 评测程序不是适应性的。也就是说，所有初始元素的基因型在 `guess` 函数被调用前已经确定。
## 提示

#### 【交互示例】

以下为 $n=2$，基因型为 $\{\verb!Aa!,\verb!AA!\}$ 时一种可能的交互过程。

|选手程序|交互库|
|:-:|:-:|
||`guess(2)`|
|`cross(1,2)`||
||$\{\verb!Aa!,\verb!AA!,\verb!Aa!\}$|
|`cross(1,3)`||
||$\{\verb!Aa!,\verb!AA!,\verb!Aa!,\verb!aa!\}$|
|`query(4)`||
||$\verb!a!$|
|$\{\verb!Aa!,\verb!AA!\}$||
||`Ok,accepted.`|

#### 【约束条件】

+ $2\le n\le 2\times10^4$，$n$ 为偶数。
+ 每次程序运行时将恰好调用一次 `guess()` 函数。
+ 保证交互库是非自适应性的，即所有初始元素的基因型不在交互过程中发生改变。

#### 【子任务】

|Subtask|分值|$n\le$|特殊性质|
|:-:|:-:|:-:|:-:|
|$0$|$0$|$2$|无|
|$1$|$5$|$2\times10^4$|保证不存在 $\verb!Aa!$|
|$2$|$15$|$500$|无|
|$3$|$20$|$2\times10^4$|保证至少存在一个 $\verb!aa!$|
|$4$|$25$|$5\times10^3$|无|
|$5$|$35$|$2\times10^4$|无|

对于所有数据，$2\le n\le 2\times10^4$，保证 $n$ 为偶数。

由于本题涉及概率与期望，如果你确定你的算法无误，可以尝试多交几发。


---

---
title: "[COTS 2023] 三角形 Trokuti"
layout: "post"
diff: 省选/NOI-
pid: P10831
tag: ['2023', '交互题', 'Special Judge', 'O2优化', '概率论', '随机化', 'COCI（克罗地亚）']
---
# [COTS 2023] 三角形 Trokuti
## 题目背景

译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D1T3。$\texttt{1s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）
## 题目描述

有一个隐藏的简单无向图 $G$，其中恰有 $N=100$ 个节点。试通过以下询问重建 $G$：

> **询问** 给定两两不同的节点 $u,v,w$，回答这三个节点的导出子图（induced subgraph）的边数。注意到答案只会是 $0,1,2,3$。

【实现细节】

你的程序通过标准输入输出与交互库交互。

- $\texttt{? u v w}$：发起一次询问，回答 $u,v,w$ 的导出子图的边数（从标准输入读取），注意到答案只会是 $0,1,2,3$。

    你需要保证 $1\le u,v,w\le 100$，$u,v,w$ 两两不同。最多询问 $161\, 700$ 次。
- $\texttt{!}$：回答答案。在输出 $\texttt{!}$ 后换行，接下来输出 $N$ 行，每行一个长度为 $N$ 的 $\texttt{01}$ 字符串。

    第 $i$ 行第 $j$ 个字符如果是 $\texttt{1}$，代表 $(i,j)$ 间有边；否则代表 $(i,j)$ 间无边。

每次输出后，你需要刷新缓冲区。如：C++ 中的 `cout.flush()`。

## 输入格式

见【实现细节】。
## 输出格式

见【实现细节】。
## 样例

### 样例输入 #1
```

0

2

2
```
### 样例输出 #1
```
? 1 2 3

? 1 2 4

? 1 3 4

!
0001
0001
0001
1110
```
## 提示


#### 评分方式

记 $Q$ 为你程序询问的最多次数。

若 $Q\gt 161\, 700$，得 $0$ 分。

否则，你的得分将由下表确定：

| $Q$ | 得分 |
|:-----:|:------:|
| $9\, 900\le Q\le 161\, 700$  | $\displaystyle 10+10\cdot \frac{161\, 700-Q}{161\, 700-9\, 900}$  | 
| $4\, 950 \le Q\le 9\, 900$  | $\displaystyle 20+10\cdot \frac{9\, 900-Q}{9\,900-4\,500}$  |
| $3\, 400\le Q\le 4\, 950$  | $\displaystyle 30+70\cdot \frac{4\,950-Q}{4\,950-3\,400}$  |
| $Q\le 3\, 400$  | $100$  |




---

---
title: "不知道"
layout: "post"
diff: 省选/NOI-
pid: P11900
tag: ['数学', '概率论']
---
# 不知道
## 题目背景

不知道，令人闻风丧胆的猫猫魔，福尔魔斯的宿敌。

某一天，她在网上看到了一道小学奥数问题：约瑟夫问题。
## 题目描述

不知道又要作案了。她让 $n$ 只猫猫站成一行，从左到右初始编号为 $1,2,\dots,n$。同时，它们初始站在与自己编号相同的格子上。

不知道有 $k+1$ 个喜欢的数字 $t_0,t_1,\dots,t_k$ 。它们满足：  
- $t_0=1$ 
- 对于 $1\le i\le k$ , $t_{i-1}<t_i$ 
- $t_k\le n$

不知道会摸 $n-1$ 轮猫猫，每一轮她都会摸正好一只猫猫。一次摸猫猫遵循以下规则：  
1. 从 $0$ 到 $k$ 中随机选择一个数 $i$ 。
1. 若有猫猫现在待在第 $t_i$ 格上，不知道会摸摸这个猫猫，随后这个猫猫将会跑出格子，不再参与后续的任何流程，然后进行第三步；否则回到第一步。
1. 让所有猫猫跑到新的格子上。若此时有 $p$ 只猫猫，它们会在保证相对顺序不变的情况下排到 $[1,p]$ 的格子上。

但是虽然猫猫很可爱，猫猫和不知道都是会厌烦的，所以当只剩一只猫猫时，不知道会停止摸猫猫。请求出每只猫猫最终没被摸的概率。
 
最终答案对 $998244353$ 取模。
## 输入格式

第一行两个整数 $n$ 和 $k$ ，代表总共有 $n$ 个猫猫，不知道共有 $k+1$ 个喜欢的数字。  
第二行 $k$ 个整数，分别代表 $t_1$ 至 $t_k$ 共 $k$ 个数，中间用空格隔开。
## 输出格式

一行 $n$ 个整数，第 $i$ 个数表示初始编号为 $i$ 的猫猫没被摸的概率，空格隔开；对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
2 0

```
### 样例输出 #1
```
0 1 

```
### 样例输入 #2
```
4 1 
3 

```
### 样例输出 #2
```
0 748683265 748683265 499122177 

```
### 样例输入 #3
```
8 3 
3 6 8 

```
### 样例输出 #3
```
0 291154603 291154603 582309206 166374059 166374059 748683265 748683265 

```
## 提示

#### 样例解释：
在第一组样例中，不知道只喜欢 $1$ 这个数字，因此她每次一定会摸当前的第一只猫猫，那么第一只猫猫一定会被摸，第二只猫猫一定不会被摸。  

第二组样例中，四只猫猫从左到右不被摸的概率分别为 $0,\frac{1}{4},\frac{1}{4},\frac{1}{2}$ 。

#### 数据范围：

**本题采用捆绑测试。**

对所有数据，保证 $1\le n,k\le10^6$ ； $t_i$ 范围见上。

|  #   |       特殊性质        | 分值 |
| :--: | :-------------------: | :--: |
|  0   | $n\le 8$ |  10  |
|  1   | $k=0$ |  5  |
|  2   | $k=1$ |  10  |
|  3   | $n\le5\times10^3$ |  15  |
|  4   | $k\le 10$ |  15  |
|  5   | $n\le2\times10^5$ |  20  |
|  6   | 无特殊限制 |  25  |

后记：  
花生：话说不知道本名叫什么   
福尔魔斯：不知道，所以叫不知道  
花生：？


---

---
title: "[蓝桥杯 2024 国 Python A] 药剂"
layout: "post"
diff: 省选/NOI-
pid: P12285
tag: ['数学', '2024', '概率论', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Python A] 药剂
## 题目描述

小蓝今天的实验内容是合并 $N$ 瓶试剂。每瓶试剂初始都有一个魔法值 $a_i$，所有魔法值都是正整数。

每次小蓝会随机从手头的试剂中选出两瓶，将其合并。合并时，两瓶试剂会发生化学反应，产生强大的力量，也有可能效果没有那么好。但无论如何，小蓝会得到一瓶全新的，可以和其他试剂合并的试剂。我们认为，小蓝在合并两瓶试剂时，如果两瓶试剂的魔法值分别是 $x$ 和 $y$，有 $\frac{1}{2}$ 的概率，小蓝得到的新试剂魔法值为 $x+y$，对于另 $\frac{1}{2}$ 概率，小蓝得到的新试剂的魔法值为 $xy$。

像这样，小蓝重复合并操作 $n-1$ 次，最后只会剩下一瓶试剂。小蓝希望知道，最后这瓶试剂的魔法值期望是多少。为了方便，假定这个值是 $ans$，你只需要告诉小蓝，$ans$ 乘上 $2^{n-1}\displaystyle \prod_{i=2}^{n}C_i^2$ 的结果，其中 $C_i^2$ 是组合数。不难证明这个值一定是一个整数。但这个乘积显然太大了，小蓝只希望你告诉她这个乘积对整数 $mo$ 取模之后的结果。
## 输入格式

输入的第一行包含两个正整数 $N, mo$，用一个空格分隔。

第二行包含 $N$ 个正整数，相邻整数之间使用一个空格分隔，其中第 $i$ 个正整数表示第 $i$ 瓶试剂的魔法值 $a_i$。
## 输出格式

输出一行包含一个整数表示答案，即最后一瓶试剂魔法值的期望乘上 $2^{n-1}\displaystyle \prod_{i=2}^{n}C_i^2$ 的结果。
## 样例

### 样例输入 #1
```
3 1000000007
1 2 3
```
### 样例输出 #1
```
75
```
## 提示

### 样例说明

可能的合并情形较多，这里给出样例中两种可能的情况：

- 第一次小蓝随机选中魔法值为 $1$ 和 $3$ 的试剂进行合并，得到魔法值为 $1+3=4$ 的一瓶新的试剂。
- 然后小蓝对仅剩的两瓶试剂进行合并，得到 $4 \times 2=8$ 的一瓶试剂。
- 因此这种情况最终试剂的魔法值为 $8$。

又或者：

- 第一次小蓝随机选中魔法值为 $1$ 和 $2$ 的试剂进行合并，得到魔法值为 $1 \times 2=2$ 的一瓶新的试剂。
- 然后小蓝对仅剩的两瓶试剂进行合并，得到 $2+3=5$ 的一瓶试剂。
- 因此这种情况最终试剂的魔法值为 $5$。

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$1 \leq N \leq 5$，$mo = 10^9 + 7$；
- 对于 $50\%$ 的评测用例，$1 \leq N \leq 50$，$mo = 10^9 + 7$；
- 对于 $70\%$ 的评测用例，$1 \leq N \leq 300$，$mo = 10^9 + 7$；
- 对于 $80\%$ 的评测用例，$mo = 10^9 + 7$；
- 对于所有评测用例，$1 \leq N \leq 3000$，$1 \leq a_i \leq 10^9$，$1 \leq mo \leq 10^9 + 7$。


---

---
title: "[蓝桥杯 2024 国 Java A] 斗蛐蛐"
layout: "post"
diff: 省选/NOI-
pid: P12292
tag: ['2024', '概率论', '蓝桥杯国赛', '状压 DP']
---
# [蓝桥杯 2024 国 Java A] 斗蛐蛐
## 题目描述

小蓝最近非常热衷于斗蛐蛐。她有 $n$ 只不同的蛐蛐，每只蛐蛐的战斗力都可以用一个数 $a_i$ 表示，含义是当第 $i$ 只蛐蛐攻击别的蛐蛐时有 $a_i$ 的概率打倒对方，有 $1 - a_i$ 的概率无事发生。

小蓝将 $n$ 只蛐蛐按编号由 $1$ 到 $n$ 顺时针的顺序排成一圈，然后从 $1$ 号蛐蛐开始发生以下的过程直到只剩下 $1$ 只蛐蛐：

1. 这只蛐蛐以各 $1/2$ 的概率选定顺时针或逆时针方向。
2. 这只蛐蛐攻击这个方向上第一只未被打倒的蛐蛐。
3. 无论这次攻击是否打倒了蛐蛐，顺时针方向的下一只蛐蛐开始行动。

现在小蓝希望知道，最后剩下的蛐蛐是 $i$ 号蛐蛐的概率是多少。为了防止精度误差，她希望你给出这个值在模素数 $m$ 下的结果。
## 输入格式

输入的第一行包含两个正整数 $n, m$，用一个空格分隔。

第二行包含 $n$ 个正整数，其中第 $i$ 个正整数表示第 $i$ 只蛐蛐在模 $m$ 下的战斗力 $a_i$。
## 输出格式

输出一行包含 $n$ 整数，相邻整数之间使用一个空格分隔，其中第 $i$ 个整数表示最后一只蛐蛐是 $i$ 号蛐蛐的概率在模 $m$ 下的表示。
## 样例

### 样例输入 #1
```
2 1000000007
500000004 500000004
```
### 样例输出 #1
```
666666672 333333336
```
## 提示

### 样例说明

一共两只蛐蛐，蛐蛐的战斗力都是 $1/2$，$1$ 号蛐蛐攻击 $2$ 号蛐蛐若成功，则 $1$ 号蛐蛐获胜，若失败则相当于双方位置交换，所以最终 $1$ 号蛐蛐获胜概率 $p$ 满足 $p = 1/2 + 1/2(1 - p)$ 解得 $p = 2/3$。

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$n \leq 8$，$a_i = (m + 1)/2$，即 $a_i$ 在模 $m$ 意义下为 $\frac{1}{2}$；
- 对于 $50\%$ 的评测用例，$n \leq 8$；
- 对于所有评测用例，$2 \leq a_i < m \leq 10^9 + 7$，$2 \leq n \leq 15$，$m$ 必定为一个大于 $2$ 的素数。


---

---
title: "[GCJ 2022 Qualification] Twisty Little Passages"
layout: "post"
diff: 省选/NOI-
pid: P12983
tag: ['2022', '交互题', 'Special Judge', '概率论', '期望', 'Google Code Jam']
---
# [GCJ 2022 Qualification] Twisty Little Passages
## 题目描述

You are investigating a cave. The cave has $\mathbf{N}$ rooms. There are underground passages that bidirectionally connect some pairs of rooms. Each room has at least one passage connected to it. No passage goes from a room to itself, and no two rooms are connected by more than one passage.

When in a room, you can identify what room you are in and see how many passages it connects to, but you cannot distinguish the passages. You want to estimate the number of passages that exist in the cave. You are allowed to do up to $\mathbf{K}$ operations. An operation is either:

* be magically teleported to a room of your choice, or
* walk through a random passage connected to the room you are in, taking you to the room at the other end of that passage.

When you decide to walk through a passage, you are unable to choose which one, because they are all alike. A passage is chosen for you uniformly at random.

You begin the investigation in an arbitrary room. Estimate the number of passages between rooms in the cave with at most $\mathbf{K}$ operations.

If $E$ is your estimate and $P$ is the actual number of passages, your solution is considered correct for a test case if and only if $P \cdot 2/3 \leq E \leq P \cdot 4/3$.

To pass a test set, your solution must be correct for at least 90% of the test cases in that set.

### Interactive Protocol

This is an interactive problem.

Initially, your program should read a single line containing an integer, $\mathbf{T}$, the number of test cases. Then, $\mathbf{T}$ test cases must be processed.

For each test case, your program must first read a line containing two integers $\mathbf{N}$ and $\mathbf{K}$: the number of rooms in the cave, and the maximum number of room operations you are allowed. Rooms are numbered between $1$ and $\mathbf{N}$. The cave is determined at the beginning of the test case – it won't be changed while you explore it. Then, your program must process up to $\mathbf{K} + 1$ exchanges.

The $i$-th exchange starts with you reading a line containing two integers $\mathbf{R}_i$ and $\mathbf{P}_i$, representing the number of the room you are currently in and the number of passages it connects to. Then, you must output a single line containing one of the following:

* A single uppercase $\mathbf{w}$: this means you want to walk through a random passage.
* A single uppercase $\mathbf{t}$ and an integer $S$: this means you want to teleport to room $S$.
* A single uppercase $\mathbf{e}$ and an integer $E$: this means you want to finish exploring and estimate that the cave contains $E$ passages.

After an estimation operation, the judge will immediately start the next test case if there is one, regardless of the correctness of your estimation. If there is no next test case, the judge will wait for you to finish without any further output.

If the judge receives an invalidly formatted line from your program at any moment, or if your $(\mathbf{K} + 1)$-th exchange for a test case is not an estimation operation, the judge will print a single number $-1$ and will not print any further output. If your program continues to wait for the judge after receiving a $-1$, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
1
5 3
4 1

5 2

4 1

1 3
```
### 样例输出 #1
```



T 5

W

T 1

E 5
```
## 提示

**Sample Explanation**

![](https://cdn.luogu.com.cn/upload/image_hosting/ve57bfoy.png)

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our interactive runner for that. For more information, read the instructions in comments in that file.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

**Test Set 1 (29 Pts, Visible Verdict)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{N} \leq 10^5$.
- $K = 8000$.
- Each room has at least one passage connected to it.


---

---
title: "[GCJ 2022 Finals] Schrödinger and Pavlov"
layout: "post"
diff: 省选/NOI-
pid: P13004
tag: ['动态规划 DP', '2022', '概率论', '基环树', 'Google Code Jam']
---
# [GCJ 2022 Finals] Schrödinger and Pavlov
## 题目描述

 _The story, all names, characters, and incidents portrayed in this problem statement are fictitious. No identification with actual persons is intended or should be inferred._ 

It is 1935 and a meeting between two Nobel prize winners is producing astonishing results. Schrödinger, a famous physicist, invited Pavlov, a famous physiologist, to see his experiments with cats in boxes. Pavlov brought his dog with him to keep up with his own research, and the combination proved interesting, to say the least.

Schrödinger had a row of $\mathbf{N}$ boxes. Some boxes definitely contain a cat, some boxes definitely do not contain a cat, and some boxes may or may not contain a cat. Each box is only big enough to hold a single cat. Each box is also equipped with a special quantum tunnel, that allows the cat in the box to move to some other specific box if the destination was empty. The tunnels work in a single direction.

Cats are usually mellow and quiet and do not use the tunnels unless they become startled. When a third unannounced guest rings the bell, Pavlov's dog gets excited immediately and starts running and barking. The dog starts at box 1 and runs towards box $\mathbf{N}$. As the dog runs, it passes right next to each box, one at a time. When it passes next to a box that contains a cat, the cat in that box becomes startled. The startled cat checks the available tunnel and, if the destination box is empty, uses it to escape. If the destination box is occupied, the cat stays in its current box. The same cat can be startled more than once if they move to a box the dog will get to afterwards, and will proceed in the same way every time it is startled (using only the newly available tunnel each subsequent time).

![](https://cdn.luogu.com.cn/upload/image_hosting/xcqaev9m.png)

After Pavlov's dog finally stops right next to the last box, Pavlov asks Schrödinger whether there is a cat in that last box. Schrödinger, true to his fame, replies that he does not know. Pavlov notices that the answer may depend on whether or not there were cats in the unknown boxes. Moreover, he also notices that because there are $k$ unknown boxes, there are $2^k$ possible *initial configurations*, one for each combination of statuses of the unknown boxes. Pavlov tells Schrödinger that they should try to calculate how many of the $2^k$ initial configurations would result in having a cat in the last box. You are asked to recreate that calculation. Since the output can be a really big number, we only ask you to output the remainder of dividing the result by the prime $10^9 + 7$ (1000000007).

*Neither cats, nor dogs, nor Nobel prize winners were harmed in the making of this problem statement.*
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow, each described by exactly three lines. The first line of a test case contains a single integer $\mathbf{N}$, the number of boxes in Schrödinger's experiment. Boxes are numbered between 1 and $\mathbf{N}$, in the order Pavlov's dog passes them by. The second line of a test case contains a single string $\mathbf{S}$ of $\mathbf{N}$ characters. The $i$-th character of $\mathbf{S}$ (counting from left to right) represents the contents of box $i$: it is an uppercase 'c' if the box contains a cat, a period '.' if the box does not contain a cat and a question mark '?' if it is unknown whether the box contains a cat or not. The third line of a test case contains $\mathbf{N}$ integers $\mathbf{B}_1$, $\mathbf{B}_2$, $\dots$, $\mathbf{B}_\mathbf{N}$, representing that there is a tunnel going out of box $i$ and into box $\mathbf{B}_i$, for all $i$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the number of initial configurations that would result in a cat being in the last box and unable to escape despite hearing the barking, modulo the prime $10^9 + 7$ ($1000000007$).
## 样例

### 样例输入 #1
```
4
4
??.C
2 3 1 3
4
????
2 3 1 3
6
?.????
6 6 6 6 6 5
34
????????????????????????????????CC
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 33
```
### 样例输出 #1
```
Case #1: 1
Case #2: 2
Case #3: 15
Case #4: 294967268
```
## 提示

**Sample Explanation**

Sample Case #1 is illustrated in the problem statement. There are 4 possible configurations:

*   `...C`: the dog runs through the first 3 boxes without changing anything because there is no cat there. Then, when it gets to the last box, the cat hears it and escapes to box 3. Therefore, there is no cat in the last box in this case.
*   `C..C`: when the dog barks near box 1, that startles the cat that goes through the tunnel to get to box 2, which was empty. Then, the same cat gets startled again when the dog barks near box 2 and gets to box 3. And when the dog barks next to box 3, the cat hears it and returns to box 1. Therefore, when the dog gets to box 4 and the other cats hears it, box 3 is empty so the cat escapes and the last box ends up empty.
*   `.C.C`: This case is very similar to the previous one. After the dog goes through the first box and nothing happens, the state is the same as before, so the ultimate result is the same: last box empty.
*   `CC.C`: In this case, the cat in the first box cannot escape when it hears the dog, so it remains in box 1. Then, when the cat in box 2 gets startled it escapes to box 3 leaving a state of `C.CC`. When the dog gets to the box 3, the cat currently there cannot escape to box 1 so the state remains the same. Finally, when the dog gets to the last box, the cat that is there cannot escape because box 3 is occupied this time. So, in this case, the last box ends up with a cat after the dog ends its journey.

Out of the 4 possibilities, only 1 (the last one) ends up with a cat in the last box, so the answer is 1.

In Sample Case #2, the tunnels are set up the same as in Sample Case #1. Since no tunnel ends at the last box, the configurations that start with no cat at the last box will also not end with a cat there, so we do not need to count them. Then, we have 8 additional configurations. The 4 we considered for Sample Case #1, out of which only 1 ends up with a cat at the last box. The remaining 4 configurations are: `..CC`, `C.CC`, `.CCC`, `CCCC`. From these additional 4 configurations, only in the last one listed a cat ends up in the last box, for a total of 2 overall.

In Sample Case #3, notice that for a cat to remain in the last box after the dog barks near it, both that box and box 5 must be occupied then (otherwise, either there is no cat in the last box, or it will escape to box 5). Since there is no tunnel going into box 5, a cat must start there. As long as there is another cat in any other box, box 6 will get (or remain) occupied before the cat in box 5 gets an opportunity to escape, so all of those will end up with a cat in the last box. As we argued before, a single cat is not enough. Thus, we need to count the number of configurations with a cat in box 5 and at least one other cat. There are $2^4$ configurations with a cat in box 5, and out of those, only 1 has no other cat, so the answer is $2^4 - 1 = 15$.

In Sample Case #4, in all of the $2^k$ ways in which the $k$ unknown boxes may exist a cat would be left in the last box.

**Limits**

- $1 \leq \mathbf{T} \leq 1234$.
- the length of $\mathbf{S} = \mathbf{N}$.
E- ach character of $\mathbf{S}$ is either an upper case 'c', a period '.' or a question mark '?'.
- $1 \leq \mathbf{B}_i \leq \mathbf{N}$, for all $i$.
- $\mathbf{B}_i \neq i$, for all $i$.

**Test Set 1 (8 Pts, Visible Verdict)**

- $1 \leq \mathbf{N} \leq 100$.
- $i - 5 \leq \mathbf{B}_i \leq i + 5$, for all $i$. (All tunnels connect to nearby boxes.)

**Test Set 2 (42 Pts, Hidden Verdict)**

- $1 \leq \mathbf{N} \leq 5000$.


---

---
title: "[GCJ 2020 #3] Pen Testing"
layout: "post"
diff: 省选/NOI-
pid: P13068
tag: ['2020', '交互题', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2020 #3] Pen Testing
## 题目描述

You have $N$ ballpoint pens. You know that each has a distinct integer number of units of ink between $0$ and $N-1$, but the pens are given to you in random order, and therefore you do not know which pen is which.

You are about to go on a trip to the South Pole (where there are no pens), and your luggage only has room for two pens, but you know you will need to do a lot of important postcard writing. Specifically, the two pens you choose must have a total of at least $N$ ink units.

Your only way to get information about the pens is to choose one and try writing something with it. You will either succeed, in which case the pen will now have one unit of ink less (and is now possibly empty), or fail, which means that the pen already had no ink left. You can repeat this multiple times, with the same pen or different pens.

Eventually, you must select the two pens to take on your trip, and you succeed if the total amount of ink remaining in those two pens is at least $N$ units.

You will be given $T$ test cases, and you must succeed in at least $C$ of them. Note that all test sets in this problem are Visible.

### Interactive Protocol

This is an interactive problem.

Initially, your program should read a single line containing three integers $\mathbf{T}$, $\mathbf{N}$, and $\mathbf{C}$: the number of test cases, the number of pens, and the minimum number of test cases you must succeed in. (Note that the value of $\mathbf{N}$ is the same for all test sets, and is provided as input only for convenience; see the Limits section for more details.)

Then, your program needs to process all $\mathbf{T}$ test cases at the same time (this is done to reduce the number of roundtrips between your solution and the judging program). The interaction is organized into rounds.

At the beginning of each round, your program must print one line containing $\mathbf{T}$ integers: the i-th integer is the number of the pen you want to try writing with in the i-th test case, or 0 if you do not want to write with any pen in this test case in this round. The pens are numbered from 1 to $\mathbf{N}$.

Be aware that flushing the output buffer after each one of these integers, instead of only once after printing all $\mathbf{T}$, could cause a Time Limit Exceeded error because of the time consumed by the flushing itself.

The judge responds with one line containing $\mathbf{T}$ integers: the i-th integer is the amount of ink spent in the i-th test case in this round. It will be equal to 1 if the writing in the i-th test case was successful. Otherwise, it will be equal to 0, which could mean that you tried to write in the i-th test case but the pen you chose had no ink left, or that you did not try to write in the i-th test case at all.

You may participate in at most $\mathbf{N} \times (\mathbf{N}+1)/2$ rounds. Note that this is enough to be confident that all pens are empty.

When your program is ready to submit an answer for all test cases, it must print a line containing the number 0 $\mathbf{T}$ times. This line is not counted towards the limit on the number of rounds, and the judge will not send a response.

Then, your program must print another line with $2 \times \mathbf{T}$ integers: the $(2 \times \mathbf{i}-1)$-th and the $(2 \times \mathbf{i})$-th integers in this line are the distinct numbers of the pens that you take to the South Pole in the i-th test case. The judge will not send a response, and your program must then terminate with no error.

If the judge receives unexpected output from your program at any moment, the judge will print a single number -1 and not print any further output. If your program continues to wait for the judge after receiving a -1, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.

You can assume that the pens are given to you in random order. These orders are chosen uniformly at random and independently for each test case and for each submission. Therefore even if you submit exactly the same code twice the judge will use different random orders.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
2 5 1

1 0

0 1

0 1
```
### 样例输出 #1
```

4 5

4 3

0 2

0 0
3 4 3 4
```
## 提示

**Sample Explanation**

Here is the same interaction, explained:

```
  // The following reads 2 into t, 5 into n and 1 into c.
  t, n, c = readline_int_list()
  // The judge secretly picks the number of units for each pen:
  // in test case 1: 2 0 4 1 3
  // in test case 2: 1 3 2 4 0
  // We write with the 4-th pen in test case 1, and with the 5-th pen in test case 2.
  printline 4 5 to stdout
  flush stdout
  // Reads 1 0, as the 4-th pen in test case 1 still had ink left,
  // but the 5-th pen in test case 2 did not.
  a1, a2 = readline_int_list()
  // We write with the 4-th pen in test case 1 again, and with the 3-rd pen in test case 2.
  printline 4 3 to stdout
  flush stdout
  // Reads 0 1.
  a1, a2 = readline_int_list()
  // We only write in test case 2 this time, with the 2-nd pen.
  printline 0 2 to stdout
  flush stdout
  // Reads 0 1.
  a1, a2 = readline_int_list()
  // We decide we are ready to answer.
  printline 0 0 to stdout
  flush stdout
  // We take the 3-rd and the 4-th pens to the South Pole in both test cases.
  printline 3 4 3 4 to stdout
  flush stdout
  // In test case 1, the remaining amounts in the 3-rd and the 4-th pens are 4 and 0, and 4+0<5,
  // so we did not succeed.
  // In test case 2, the remaining amounts in the 3-rd and the 4-th pens are 1 and 4, and 1+4≥5,
  // so we succeeded.
  // We have succeeded in 1 out of 2 test cases, which is good enough since c=1.
  exit
```

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our [interactive runner](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py) for that. For more information, read the instructions in comments in that file.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

- $\mathbf{N} = 15$.

**Test Set 1 (6 Pts, Visible Verdict)**

- $\mathbf{T} = 20000$.
- $\mathbf{C} = 10900$ ($\mathbf{C} = 0.545 \times \mathbf{T}$).

**Test Set 2 (11 Pts, Visible Verdict)**

- $\mathbf{T} = 20000$.
- $\mathbf{C} = 12000$ ($\mathbf{C} = 0.6 \times \mathbf{T}$).

**Test Set 3 (15 Pts, Visible Verdict)**

- $\mathbf{T} = 100000$.
- $\mathbf{C} = 63600$ ($\mathbf{C} = 0.636 \times \mathbf{T}$).


---

---
title: "[GCJ 2016 Finals] Family Hotel"
layout: "post"
diff: 省选/NOI-
pid: P13207
tag: ['动态规划 DP', '2016', '概率论', 'Google Code Jam']
---
# [GCJ 2016 Finals] Family Hotel
## 题目描述

You run a hotel with $\mathbf{N}$ rooms arranged along one long corridor, numbered from 1 to $\mathbf{N}$ along that corridor. Your guests are big families, and every family asks for exactly two adjacent rooms when they arrive. Two rooms are adjacent if their numbers differ by exactly 1.

At the start of the day today, your hotel was empty. You have been using the following simple strategy to assign rooms to your guests. As each family arrives, you consider all possible pairs of adjacent rooms that are both free, pick one of those pairs uniformly at random, and assign the two rooms in that pair to the family. New families constantly arrive, one family at a time, but once there are no more pairs of adjacent rooms that are both free, you turn on the NO VACANCY sign and you do not give out any more rooms.

Given a specific room number, what is the probability that it will be occupied at the time that you turn on the NO VACANCY sign?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ lines follow. Each line contains two numbers: the number of rooms $\mathbf{N}$ and the room number $\mathbf{K}$ that we are interested in.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the sought probability computed modulo $10^9 + 7$, which is defined precisely as follows. Represent the probability that room $\mathbf{K}$ is occupied as an irreducible fraction $\frac{p}{q}$. The number $y$ then must satisfy the modular equation $y \times q \equiv p \pmod{10^9 + 7}$, and be between 0 and $10^9 + 6$, inclusive. It can be shown that under the constraints of this problem such a number $y$ always exists and is uniquely determined.
## 样例

### 样例输入 #1
```
4
3 1
3 2
4 1
4 2
```
### 样例输出 #1
```
Case #1: 500000004
Case #2: 1
Case #3: 666666672
Case #4: 1
```
## 提示

**Sample Explanation**

In sample case #3, there are four rooms and we are looking for probability that the first room is occupied. When the first family arrives, there are 3 possible situations, each with probability $1/3$: occupy rooms $1+2, 2+3$ or $3+4$. In the first situation, the first room is already occupied and will stay occupied. In the second situation, the first room is free and no more families can be accommodated, so it will stay free. Finally, in the third situation, the next arriving family will definitely get rooms $1+2$, and thus the first room will be occupied. The probability that the first room is occupied is thus $2/3$, and the answer is $666666672$, since $(666666672 \times 3) \mod 1000000007 = 2 \mod 1000000007$.

The probability for sample case #1 is $1/2$, and for sample cases #2 and #4 it is $1$.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $1 \leqslant \mathbf{K} \leqslant \mathbf{N}$.

**Small dataset (10 Pts, Test Set 1 - Visible)**

- $2 \leqslant \mathbf{N} \leqslant 10^{4}$.

**Large dataset (20 Pts, Test Set 2 - Hidden)**

- $2 \leqslant \mathbf{N} \leqslant 10^{7}$.


---

---
title: "[GCJ 2013 #1A] Good Luck"
layout: "post"
diff: 省选/NOI-
pid: P13287
tag: ['2013', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2013 #1A] Good Luck
## 题目描述

Maryam and Peiling have recently been practicing a new number trick, and they need your help to get it right. The trick goes as follows: Maryam starts by picking $N$ independent random integer numbers, each between 2 and $M$, inclusive, appearing with equal probability, and writes them down on $N$ cards, one number per card. Note that some numbers might be equal. Then, she repeats the following $K$ times: take a random subset of cards (each card is taken with probability 0.5), and write down the product of the numbers on those cards. Having done all that, she shows all $K$ products to Peiling, and Peiling's goal is to guess what the original $N$ numbers were, knowing just $N$, $M$, and the products.

An example game with $N=3$, $M=4$, $K=4$ might go like this: first, Maryam picks 3 random numbers between 2 and 4, inclusive - let's say she randomly chose $A_1=3$, $A_2=3$ and $A_3=4$. Then, she calculates four products of random subsets of those three numbers. For example, let's say those products are $A_1 \cdot A_2=9$, $A_3=4$, $A_1 \cdot A_2 \cdot A_3=36$, and $1=1$ (the last product has no numbers in it, so it's equal to 1). Peiling receives numbers 9, 4, 36, 1 from her, and she's also told that $N=3$ and $M=4$. In this case, just seeing the number 36 is enough to find what the original numbers were, since the only way to represent that as a product of up to 3 numbers, each up to 4, is $3 \cdot 3 \cdot 4$. So Peiling says that the original numbers were 3, 3 and 4, and the audience is impressed.

In some other cases, guessing the original numbers is not as simple. For example, it might happen that all products are equal to 1. In that case there is no way to know anything about the hidden numbers, so Peiling cannot always be right. However, Peiling knows that Maryam follows the procedure exactly as described above: she selects the first $N$ numbers as independent uniform integers between 2 and $M$, and then selects $K$ independent random subsets, picking each number into each subset independently with probability 0.5. Help Peiling use that knowledge to make better guesses!

This problem is a bit unusual for Code Jam. You will be given $R$ independent sets of $K$ numbers each, and should print an answer for each set — this part is as usual. However, you don't need to get all of your answers right! Your solution will be considered correct if answers for at least $X$ sets are correct, with the value of $X$ given in the Limits for the given input, below. However, you must follow the output format, even for sets in which your answer doesn't turn out to be correct. The only thing that can be wrong on any sets, yet still allow you to be judged correct, is the digits you output; but there should still be exactly $N$ digits printed for each case, and each digit must be between 2 and $M$.

This problem involves randomness, and thus it might happen that even the best possible solution doesn't make $X$ correct guesses (remember the situation when all products are equal to 1?) for a certain input. Because of that, this problem doesn't have a Large input, but instead has two Small inputs. That means you can try again if you think you got unlucky. You may only attempt to solve the second Small input once you have solved the first one. Otherwise, both Small inputs work in the same way as Small inputs for any other problem: you may try multiple times, and there is a 4-minute penalty for incorrect submissions if you later solve that input, even if the only reason you got it wrong was chance.

Good luck!
## 输入格式

The first line of the input gives the number of test cases, $T$, which is always equal to 1. The second line of the input file contains four space-separated integers $R$, $N$, $M$ and $K$, in that order. The next $R$ lines describe one set of $K$ products each. Each of those lines contains $K$ space-separated integers — the products that Maryam passes to Peiling. It is guaranteed that all sets in the input are generated independently randomly according to the procedure from the problem statement.

## 输出格式

On the first line, output "Case #1:". On each of the next $R$ lines output $N$ digits — your guess for Maryam's hidden numbers for the corresponding set of products. You can print the numbers for each set in any order, but there must be exactly $N$ digits, each between 2 and $M$, inclusive (note that $M<10$, so none of the numbers will be more than one digit). Do not put spaces between the digits.
## 样例

### 样例输入 #1
```
1
2 3 4 4
9 4 36 1
1 1 1 1
```
### 样例输出 #1
```
Case #1:
343
222
```
## 提示

**Sample Explanation**

The sample input doesn't follow the limitations for either input. In the sample input, you need to get at least $X=1$ sets right.

In the sample input, Maryam picked the numbers $3, 3, 4$ the first time, and the numbers $2, 4, 4$ the second time. In the sample output, Peiling guessed correctly the first time, but not the second time.

**First Small dataset (10 Pts, Test set 1 - Visible)**

- $T = 1$.
- $R = 100$.
- $N = 3$.
- $M = 5$.
- $K = 7$.
- You need to get at least $X=50$ sets right.

**Second Small dataset (31 Pts, Test set 2 - Visible)**

- $T = 1$.
- $R = 8000$.
- $N = 12$.
- $M = 8$.
- $K = 12$.
- You need to get at least $X=1120$ sets right.



---

---
title: "[GCJ 2013 #3] Observation Wheel"
layout: "post"
diff: 省选/NOI-
pid: P13301
tag: ['动态规划 DP', '2013', 'Special Judge', '区间 DP', '概率论', '期望', 'Google Code Jam']
---
# [GCJ 2013 #3] Observation Wheel
## 题目描述

An observation wheel consists of $N$ passenger gondolas arranged in a circle, which is slowly rotating. Gondolas pass the entrance one by one, and when a gondola passes the entrance, a person may enter that gondola.

In this problem, the gondolas are so small that they can take just one person each, so if the gondola passing by the entrance is already occupied, the person waiting at the entrance will have to wait for the next one to arrive. If that gondola is also occupied, the person will have to wait for the next one after that, and so on, until a free gondola arrives. For simplicity, we will not consider people exiting the gondolas in this problem — let's assume that all people do is enter the gondolas, and then rotate with the wheel for an arbitrarily long time.

We want to make sure people are not disappointed because of long waiting times, and so we have introduced a flexible pricing scheme: when a person approaches the wheel, and the first gondola passing by the entrance is free, she pays $N$ dollars for the ride. If the first gondola is occupied and she has to wait for the second one, she pays $N-1$ dollars for the ride. If the first two gondolas are occupied and she has to wait for the third one, she pays $N-2$ dollars for the ride. Generally, if she has to wait for $K$ occupied gondolas to pass by, she pays $N-K$ dollars. In the worst case, when she has to wait for all but one gondola to pass, she will pay just 1 dollar.

Let's assume that people approach our wheel at random moments in time, so for each person approaching the wheel, the first gondola to pass the entrance is picked uniformly and independently. Let's also assume that nobody will come to the wheel while there's already at least one person waiting to enter, so that we don't have to deal with queueing. A person will always take the first free gondola that passes the entrance.

You are given the number of gondolas and which gondolas are already occupied. How much money are we going to make, on average, until all gondolas become occupied?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow. Each line describes one test case and contains only '.' (dot) or 'X' (capital letter X) characters. The number of characters in this line gives you $N$. The $i$-th character is 'X' when the $i$-th gondola is already occupied, and '.' when it's still free. The gondolas are numbered in the order they pass the entrance, so the 1st gondola is followed by the 2nd gondola, and so on, starting over from the beginning after the last gondola passes.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1) and $y$ is the average amount of money we will get, in dollars. Answers with absolute or relative error no larger than $10^{-9}$ will be accepted. See the FAQ for an explanation of what that means, and what formats of floating-point numbers we accept.
## 样例

### 样例输入 #1
```
5
.X.
X.X.
.XX.
X..XX.
.XX..X
```
### 样例输出 #1
```
Case #1: 4.66666666666667
Case #2: 6.00000000000000
Case #3: 5.75000000000000
Case #4: 13.4722222222222
Case #5: 13.5277777777778
```
## 提示

**Sample Explanation**

Here's how the first example works. There are nine possibilities, each with probability $1/9$:

The first person comes. If the next gondola to pass the entrance is:

* The 1st gondola, which is free, the first person enters it and pays 3 dollars. Then, some time later, the second person comes. If the next gondola to pass the entrance is:
    * The 1st gondola, which is occupied, and so is the 2nd gondola, the second person has to wait until the 3rd gondola, and thus she pays just 1 dollar before entering it. In total, we've earned 4 dollars.
    * The 2nd gondola, which is occupied, the second person has to skip it and enter the 3rd gondola and thus pays 2 dollars. In total, we've earned 5 dollars.
    * The 3rd gondola, which is free, so the second person pays 3 dollars. In total, we've earned 6 dollars.
* The 2nd gondola, which is occupied, the first person has to skip it and enter the 3rd gondola, paying 2 dollars. Then, some time later, the second person comes. If the next gondola to pass the entrance is:
    * The 1st gondola, which is free, the second person pays 3 dollars. In total, we've earned 5 dollars.
    * The 2nd gondola, which is occupied (as is the 3rd gondola), the second person has to wait until the 1st gondola, and thus she pays just 1 dollar before entering it. In total, we've earned 3 dollars.
    * The 3rd gondola, which is occupied, the second person has to skip it and enter the 1st gondola and thus pays 2 dollars. In total, we've earned 4 dollars.
* The 3rd gondola, which is free, the first person enters it and pays 3 dollars. Then, some time later, the second person comes. If the next gondola to pass the entrance is:
    * The 1st gondola, which is free, the second person pays 3 dollars. In total, we've earned 6 dollars.
    * The 2nd gondola, which is occupied (as is the 3rd gondola), the second person has to wait until the 1st gondola, and thus she pays just 1 dollar before entering it. In total, we've earned 4 dollars.
    * The 3rd gondola, which is occupied, the second person has to skip it and enter the 1st gondola and thus pays 2 dollars. In total, we've earned 5 dollars.

We have nine possibilities, earning 3 dollars in one of them, 4 dollars in three of them, 5 dollars in three of them, and 6 dollars in two of them. On average, we earn $(1\times 3+3\times 4+3\times 5+2\times 6)/9=42/9=4.6666666666\dots$ dollars.

**Limits**

- $1 \leq T \leq 50$. 

**Small dataset (8 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq N \leq 20$.

**Large dataset (23 Pts, Test set 2 - Hidden)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq N \leq 200$.


---

---
title: "[GCJ 2012 #1B] Equal Sums"
layout: "post"
diff: 省选/NOI-
pid: P13320
tag: ['2012', 'Special Judge', '鸽笼原理', '概率论', 'Google Code Jam']
---
# [GCJ 2012 #1B] Equal Sums
## 题目描述

I have a set of positive integers $\mathbf{S}$. Can you find two non-empty, distinct subsets with the same sum?

Note: A subset is a set that contains only elements from $\mathbf{S}$, and two subsets are distinct if they do not have exactly the same elements.

## 输入格式

he first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow, one per line. Each test case begins with $\mathbf{N}$, the number of positive integers in $\mathbf{S}$. It is followed by $\mathbf{N}$ distinct positive integers, all on the same line.

## 输出格式

For each test case, first output one line containing "Case #x:", where $\mathbf{x}$ is the case number (starting from 1).

* If there are two different subsets of $\mathbf{S}$ that have the same sum, then output these subsets, one per line. Each line should contain the numbers in one subset, separated by spaces.
* If it is impossible, then you should output the string "Impossible" on a single line.

If there are multiple ways of choosing two subsets with the same sum, any choice is acceptable.
## 样例

### 样例输入 #1
```
2
20 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 120 266 858 1243 1657 1771 2328 2490 2665 2894 3117 4210 4454 4943 5690 6170 7048 7125 9512 9600
```
### 样例输出 #1
```
Case #1: Possible
Case #2: Possible
```
## 提示

**Limits**

- No two numbers in $\mathbf{S}$ will be equal.
- $1 \leq \mathbf{T} \leq 10$.

**Test set 1 (6 Pts, Visible Verdict)**

- Time limit: ~~60~~ 12 seconds.
- $\mathbf{N}$ is exactly equal to $20$.
- Each number in $\mathbf{S}$ will be a positive integer less than $10^5$.

**Test set 2 (37 Pts, Hidden Verdict)**

- Time limit: ~~120~~ 24 seconds.
- $\mathbf{N}$ is exactly equal to $500$.
- Each number in $\mathbf{S}$ will be a positive integer less than $10^{12}$.


---

---
title: "「ZYZ 2025」遗传"
layout: "post"
diff: 省选/NOI-
pid: P13350
tag: ['O2优化', '树形 DP', '概率论']
---
# 「ZYZ 2025」遗传
## 题目背景

唉，转生竞吧！
## 题目描述

**如果你不了解生物的遗传学知识，可以阅读以下部分：**

> 每个生物 M 都有两个属性，记属性一为 $X\in\{A,a\}$，属性二为 $Y\in\{A,a\}$，称 $XY$ 为其**基因型**，包括 $AA,Aa,aa$ 三种，这里认为 $Aa$ 和 $aA$ 等价。
>
> 对于生物 M 可患的遗传病 I，若 I 为**隐性遗传病**，则该生物患病当且仅当其基因型为 $aa$，若 I 为**显性遗传病**，则该生物患病当且仅当其基因型为 $Aa$ 或 $AA$。
>
> 若基因型为 $X_1Y_1$ 和 $X_2Y_2$ 的生物交配，则其后代的基因型有四种情况：$X_1X_2,X_1Y_2,Y_1X_2,Y_1Y_2$，且每种情况的概率相同，均为 $\dfrac{1}{4}$。
>
> 若 $A$ 的**基因频率**为 $p$，则认为在没有其他条件的影响下（在本题中“其他条件”包括“知道其父母”），一个生物 M 的两个属性各自有 $p$ 的概率为 $A$，$1-p$ 的概率为 $a$，且相互独立。
>
> 现在有一种生物 M 可患的遗传病 I，已知其是显性还是隐性，$A$ 的基因频率为 $p$。

**否则，你可以阅读以下部分：**

> 现在有一种和生物 M 有关的遗传病 I，已知其是显性还是隐性，其受一对常染色体等位基因 $(A,a)$ 控制，该基因的遗传符合孟德尔遗传规律，不考虑基因突变、染色体变异，交叉互换等特殊情况。
>
> **已知** $A$ 的基因频率是 $p$，即认为在没有其他条件的影响下（在本题中“其他条件”包括“知道其父母”），一个生物 M 的两个基因各自有 $p$ 的概率为 $A$，$1-p$ 的概率为 $a$，且相互独立。

现在有 $n$ 个生物 M，第 $i$ 个生物的父亲为 $fa_i$，母亲为 $mo_i$，若 $fa_i=0$ 或 $mo_i=0$ 则表示父亲或母亲未知。为了简化问题，保证 $fa_i$ 和 $mo_i$ 要么**均为** $0$，要么**均不为** $0$，且**恰有一个**生物 M 没有孩子，其余生物 M **恰有一个孩子**。

给出 $n$ 个生物的关系，已知部分生物的患病情况，你需要分别求出每一个生物基因型为 $AA,Aa,aa$ 的概率，对 $10^9+7$ 取模。

你可以参见样例解释以更好的理解这个题目。

**保证数据合法且保证数据随机生成**。
## 输入格式

第一行输入四个整数 $n,t,a,b$，$n$ 表示生物总数，$t = 0$ 表示疾病 I 为隐性，$t = 1$ 表示疾病 I 为显性，$A$ 的基因频率 $p=\dfrac{a}{b}$。

接下来 $n$ 行，第 $i$ 行首先输入一个整数 $k_i$，若 $k_i=0$ 表示第 $i$ 个生物患病，$k_i=1$ 表示不患病，$k_i=2$ 表示患病状况未知。再输入两个整数 $fa_i,mo_i$ 分别表示其父亲、母亲的编号，若编号为 $0$，则表示父母未知。
## 输出格式

输出 $n$ 行，其中的第 $i$ 行输出三个整数，分别表示第 $i$ 个生物基因型为 $AA,Aa,aa$ 的概率，结果对 $10^9+7$ 取模。
## 样例

### 样例输入 #1
```
3 0 1 2
2 0 0
0 0 0
1 1 2
```
### 样例输出 #1
```
500000004 500000004 0
0 0 1
0 1 0
```
## 提示

**【样例解释】**

记第 $i$ 个生物为 $M_i$，其基因型为 $S_i$。由于 $M_2$ 患隐性遗传病，所以 $S_2=aa$ 且 $M_3$ 含有基因（属性）$a$。又因为 $M_3$ 不患病，所以 $S_3=Aa$。

因为 $M_1$ 和患病的 $M_2$ 生出不患病的 $M_3$，所以 $M_1$ 一定不患病。因为 $p=\dfrac12$，所以对于一个随机的不患病的个体，其基因型为 $AA$ 和 $Aa$ 的概率之比为：

$$\left(\dfrac12\times\dfrac12\right):\left(2\times\dfrac12\times(1-\dfrac12)\right)=1:2$$

又因为基因型为 $AA$ 和 $aa$ 的个体生出 $Aa$ 个体的概率为 $1$，基因型为 $Aa$ 和 $aa$ 的个体生出 $Aa$ 个体的概率为 $\dfrac12$，所以 $S_1$ 为 $AA$ 和 $Aa$ 的概率之比为：

$$\left(\dfrac13\times1\right):\left(\dfrac23\times\dfrac12\right)=1:1$$

所以 $S_1$ 为 $AA$ 和 $Aa$ 的概率相同，均为 $\dfrac12$。

**【数据范围】**

**本题采用捆绑测试。**

|子任务编号|特殊性质|分值|
|:-:|:-:|:-:|
|$0$|$n\leq5$|$15$|
|$1$|任意 $i\in[1,n]$ 满足 $k_i=2$|$15$|
|$2$|$n\leq 5\times 10^3$|$30$|
|$3$|无|$40$|

对于 $100\%$ 的测试数据，保证：$1\leq fa_i,mo_i\leq n \leq10^5$，$t\in\{0,1\}$，$1\leq a< b\leq 10^9$，$k_i\in\{0,1,2\}$，**保证数据随机生成**。


---

---
title: "仓鼠找sugar II"
layout: "post"
diff: 省选/NOI-
pid: P3412
tag: ['洛谷原创', '概率论', '期望', '洛谷月赛']
---
# 仓鼠找sugar II
## 题目描述

小仓鼠和他的基（mei）友（zi）sugar 住在地下洞穴中，每个节点的编号为 $1\sim n$ 间的一个整数。地下洞穴是一个树形结构（两个洞穴间距离为 $1$）。这一天小仓鼠打算从从他的卧室 $a$（**是任意的**）走到他的基友卧室 $b$（还**是任意的**）（注意，$a$ 有可能等于 $b$）。然而小仓鼠学 OI 学傻了，不知道怎么怎么样才能用最短的路程走到目的地，于是他只能随便乱走。当他在一个节点时，会等概率走到这个点的母亲或者所有孩子节点（例如这个节点有一个母亲节点和两个子节点，那么下一步走到这 $3$ 个节点的概率都是 $\dfrac{1}{3}$），一旦走到了他基友的卧室，就会停下。

现在小仓鼠希望知道，他走到目的地时，走的步数的期望。这个期望本来是一个有理数，但是为了避免误差，我们要求输出这个有理数对 $998,244,353$ 取模的结果。

形式化地说，可以证明答案可以被表示为既约分数 $\dfrac{y}{x}$，其中 $x\not\equiv 0\pmod {998,244,353}$。可以证明存在一个唯一的整数 $z$（$0\le z\lt 998,244,353$），使得 $xz=y$，你只需要输出 $z$ 的值。


小仓鼠那么弱，还要天天被 JOHNKRAM 大爷虐，请你快来救救他吧！
## 输入格式

第一行一个正整数 $n$，表示这棵树节点的个数。

接下来 $n-1$ 行，每行两个正整数 $u$ 和 $v$，表示节点 $u$ 到节点 $v$ 之间有一条边。
## 输出格式

一个整数，表示取模后的答案。
## 样例

### 样例输入 #1
```
3
1 2
1 3

```
### 样例输出 #1
```
110916041
```
## 提示

样例解释：期望的真实值为 $\dfrac {16}{9}$。

如果 $a$ 是叶子，$b$ 是根，此时期望 $\mathbb{E}_1=1$，有 $2$ 种情况。

如果 $a$ 是根，$b$ 是叶子，则 $\displaystyle \mathbb{E}_2=\frac{1}{2}+\frac{3}{4}+\frac{5}{8}+\cdots=3$。有 $2$ 种情况。

如果 $a,b$ 是不同的叶子，则 $\mathbb{E}_3=\mathbb{E}_2+1=4$。有 $2$ 种情况。

如果 $a=b$，则 $\mathbb{E}_4=0$。有 $3$ 种情况。

所以答案为 $\displaystyle \frac{2\times 1+2\times 3+2\times 4+3\times 0}{2+2+2+3}=\frac{16}{9}$。

由于 $110,916,041\times 9=998,244,369\equiv 16\pmod {998,244,353}$，所以输出 $110,916,041$。

对于 $30\%$ 的数据，$n\le 5$；

对于 $50\%$ 的数据，$n\le 5000$；

对于所有数据，$n\le 100000$。

$\text{Statement fixed by @Starrykiller.}$


---

---
title: "富金森林公园"
layout: "post"
diff: 省选/NOI-
pid: P3616
tag: ['线段树', '树状数组', '离散化', '概率论', '洛谷月赛']
---
# 富金森林公园
## 题目描述

博艾的富金森林公园里有一个长长的富金山脉，山脉是由一块块巨石并列构成的，编号从 $1$ 到 $N$ 。每一个巨石有一个海拔高度。而这个山脉又在一个盆地中，盆地里可能会积水，积水也有一个海拔高度，所有**严格低于**这个海拔高度的巨石，就会在水面下隐藏。


由于地壳运动，巨石的海拔高度可能会随时变化，每次一块的巨石会变成新的海拔高度。当然，水面的高度也会随时发生变化。


因为有这样奇妙的地质奇观，吸引了很多游客来游玩。uim 作为一个游客，可以告诉你此时水位海拔，你得告诉他，能看到有几个连续露出水面的部分。（与水面持平我们也认为是露出）
## 输入格式

第一行两个整数 $N$ 和 $M$,分别表示 $N$ 块石头，$M$ 个询问。

接下来一行，$N$ 个整数 $A_i$ 表示每个巨石的初始海拔。

接下来 $M$ 行，每行有两个或者三个数，每一行如果第一个数是 `1`，那么后面跟一个 $B_j$，表示水面海拔。如果第一个数是 `2`，后面跟两个整数，$C_j$ 和 $D_j$，表示编号 $C_j$ 的巨石海拔变为 $D_j$。
## 输出格式

对于每个 `1` 询问，给出一个整数答案，也就是露出了几部分的山峰。
## 样例

### 样例输入 #1
```
5 4
8 6 3 5 4
1 5
2 4 1
1 5
1 3
```
### 样例输出 #1
```
2
1
2
```
## 提示

$10\%$ 的数据，$N,M<=2000$。

另外 $30\%$ 的数据， 只有 `1` 的询问。

$100\%$ 的数据，$1<=N,M<=200000,1<=A_i,B_j,D_j<=10^9$，一定有 `1` 询问。



---

---
title: "小 Y 和恐怖的奴隶主"
layout: "post"
diff: 省选/NOI-
pid: P4007
tag: ['2017', 'O2优化', '矩阵加速', '概率论', '期望', 'CTT（清华集训/北大集训）']
---
# 小 Y 和恐怖的奴隶主
## 题目背景

“A fight? Count me in!” 要打架了，算我一个。

“Everyone, get in here!” 所有人，都过来！

## 题目描述

小 Y 是一个喜欢玩游戏的 OIer。一天，她正在玩一款游戏，要打一个 Boss。

虽然这个 Boss 有 $10^{100}$ 点生命值，但它只带了一个随从——一个只有 $m$ 点生命值的“恐怖的奴隶主”。

这个“恐怖的奴隶主”有一个特殊的技能：每当它被扣减生命值但没有死亡（死亡即生命值 $\leq 0$），且 Boss 的随从数量小于上限 $k$，便会召唤一个新的具有 $m$ 点生命值的“恐怖的奴隶主”。

现在小 Y 可以进行 $n$ 次攻击，每次攻击时，会从 Boss 以及 Boss 的所有随从中的等概率随机选择一个，并扣减 $1$ 点生命值，她想知道进行 $n$ 次攻击后扣减 Boss 的生命值点数的期望。为了避免精度误差，你的答案需要对 $998244353$ 取模。
## 输入格式

输入第一行包含三个正整数 $T, m, k$，$T$ 表示询问组数，$m, k$ 的含义见题目描述。

接下来 $T$ 行，每行包含一个正整数 $n$，表示询问进行 $n$ 次攻击后扣减Boss的生命值点数的期望。
## 输出格式

输出共 $T$ 行，对于每个询问输出一行一个非负整数，表示该询问的答案对 $998244353$ 取模的结果。

可以证明，所求期望一定是一个有理数，设其为 $p / q$ $(\mathrm{gcd}(p,q) = 1)$，那么你输出的数 $x$ 要满足 $p \equiv qx \pmod{998244353}$。
## 样例

### 样例输入 #1
```
3 2 6
1
2
3
```
### 样例输出 #1
```
499122177
415935148
471393168
```
## 提示

【样例 $1$ 解释】

对于第一次询问，第一次攻击有 $\frac{1}{2}$ 的概率扣减 Boss 的生命值，有 $\frac{1}{2}$ 的概率扣减随从的生命值，所以答案为 $\frac{1}{2}$。$1 \equiv 2 \times 499122177 \pmod{998244353}$。

对于第二次询问，如果第一次攻击扣减了 Boss 的生命值，那么有 $\frac{1}{2}$ 的概率第二次攻击仍扣减 Boss 的生命值，有 $\frac{1}{2}$ 的概率第二次攻击扣减随从的生命值；如果第一次攻击扣减了随从的生命值，那么现在又新召唤了一个随从（“恐怖的奴隶主”），于是有 $\frac{1}{3}$ 的概率第二次攻击扣减 Boss 的生命值，有 $\frac{2}{3}$ 的概率第二次攻击扣减随从的生命值。所以答案为 $\frac{1}{2}\times\frac{1}{2}\times2+\frac{1}{2}\times\frac{1}{2}\times1+\frac{1}{2}\times\frac{1}{3}\times1+\frac{1}{2}\times\frac{2}{3}\times0 = \frac{11}{12}$。 $11 \equiv 12 \times 415935148\pmod{998244353}$。

【提示】

题目顺序可能与难度无关。

【子任务】

在所有测试点中，$1 \leq T \leq 1000, 1 \leq n \leq {10}^{18}, 1 \leq m \leq 3, 1 \leq k \leq 8$。

各个测试点的分值和数据范围如下：

![12058](https://cdn.luogu.com.cn/upload/pic/12058.png)


---

---
title: "[JXOI2017] 颜色"
layout: "post"
diff: 省选/NOI-
pid: P4065
tag: ['2017', '线段树', '各省省选', '枚举', '概率论', '栈']
---
# [JXOI2017] 颜色
## 题目描述

可怜有一个长度为 $n$ 的正整数序列 $A_i$，其中相同的正整数代表着相同的颜色。

现在可怜觉得这个序列太长了，于是她决定选择一些颜色把这些颜色的所有位置都删去。

删除颜色 $i$ 可以定义为把所有满足 $A_j = i$ 的位置 $j$ 都从序列中删去。

然而有些时候删去之后，整个序列变成了好几段，可怜不喜欢这样，于是她想要知道有多少种删去颜色的方案使得最后剩下来的序列非空且连续。

例如颜色序列 $\{1, 2, 3, 4, 5\}$，删除颜色 $3$ 后序列变成了 $\{1, 2\}$ 和 $\{4, 5\}$ 两段，不满足条件。而删除颜色 $1$ 后序列变成了 $\{2, 3, 4, 5\}$，满足条件。

两个方案不同当且仅当至少存在一个颜色 $i$ 只在其中一个方案中被删去。

## 输入格式

第一行输入一个整数 $T$ 表示数据组数。

每组数据第一行，输入一个整数 $n$ 表示数列长度；第二行输入 $n$ 个整数描述颜色序列。

## 输出格式

对于每组数据输出一个整数表示答案。
## 样例

### 样例输入 #1
```
1
5
1 3 2 4 3
```
### 样例输出 #1
```
6
```
## 提示

满足条件的删颜色方案有 $\{1\}, \{1, 3\}, \{1, 2, 3\}, \{1, 3, 4\}, \{2, 3, 4\}, \varnothing$。

对于 $20\%$ 的数据，保证 $1 \le \sum n \le  20$。

对于 $40\%$ 的数据，保证 $1 \le \sum n \le  500$。

对于 $60\%$ 的数据，保证 $1 \le \sum n \le  10^4$。

对于 $100\%$ 的数据，保证 $1 \le  T,\sum n \le  3 \times 10^5, 1 \le  A_i \le  n$。

$\text{Statement fixed by @Starrykiller.}$


---

---
title: "Hash?"
layout: "post"
diff: 省选/NOI-
pid: P4235
tag: ['字符串', '哈希 hashing', '概率论']
---
# Hash?
## 题目背景

**zhoutb2333**学习了哈希算法，他于是去统计给定一些字符串，其中有多少个本质不同的字符串。


但是**zhoutb2333**突发奇想，如果哈希采用的$base$每次随机，那么结果会变成什么样呢？

**辣鸡出题人又出锅了！subtask3的数据有问题，现在统一将模数改为65537**

题目来源：[zhoutb2333](https://www.luogu.org/space/show?uid=31564)
## 题目描述

他通过某种办法，获得了一个函数:$int \ Rand(int  \ x)$，它会等概率地返回一个$[0,x)$中的整数。

他写下了这样的代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int x=10,maxn=35,maxlen=16010;
ll HASH[maxn];
const ll p=65537;
char str[maxlen];
ll Hash(){
    int base=Rand(x);
    ll ret=0;
    for(int i=1;str[i];i++)
        ret=(ret*base+str[i]-'a'+1)%p;
    return ret;
}
int main(){
    int ans=0,n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",str+1),HASH[i]=Hash();
    sort(HASH+1,HASH+n+1);
    HASH[0]=-1;
    for(int i=1;i<=n;i++)
        ans+=(HASH[i]!=HASH[i-1]);
    printf("%d\n",ans);
    return 0;
}
```
**zhoutb2333**想问你，给定一些字符串和参数$x$，答案$ans$的期望是多少呢？

$65537= 2^{16}+1$**是质数**

**参数$x$在这个程序中是确定的$10$，但是每次输入会给定。**
## 输入格式

第一行三个整数$x,N$，表示$base$生成的参数和字符串的个数

接下来$N$行每行一个字符串，字符串仅由小写字母组成。
## 输出格式

一行一个小数，表示答案$ans$的期望，**模$65537$输出**。

即：如果你的答案为$\frac{q}{p}$（$gcd(p,q)=1$），那么输出使得$px \equiv q \ (mod \ 65537$的最小正整数$x$。可以证明答案$ans$一定为正有理数，并且这样的$x$一定存在。
## 样例

### 样例输入 #1
```
2 2
aa
aa
```
### 样例输出 #1
```
32770

```
### 样例输入 #2
```
3 6
i
dont
know
what
to
say
```
### 样例输出 #2
```
58261

```
## 提示

本题由$3$个$subtask$组成，设$M$为这$N$个字符串中，每个字符串长度的最大值。

对于$subtask \ 1$：$1 \le N \le 8 , M \le 10,x \le 4$，分值为$20$，时间限制为$1s$。

对于$subtask \ 2$：$1 \le N \le 30 , M \le 500,x \le 500$，分值为$50$，时间限制为$1s$。

对于$subtask \ 3$：$1 \le N \le 5 , M \le 16000,x \le 16000$，分值为$30$，时间限制为$4.5s$。

**样例#1解释：**

参数$x=2$，那么可能的哈希$base$为$0,1$。

如果哈希第一个`aa`采用的$base$和第二个`aa`的$base$相同，那么答案为$1$。

如果两个$base$不相同，那么答案为$2$。

分析发现这两种情况发生的概率相同，都是$\frac{1}{2}$，那么答案$ans$的期望为$1 * \frac{1}{2} + 2 * \frac{1}{2}=\frac{3}{2}$。使得$2x \equiv 3 \ (mod \ 65537)$的最小正整数$x$为$32770$。

**样例#2解释：**

求得答案为$\frac{53}{9}$。使得$9x \equiv 53 \ (mod \ 65537)$的最小正整数$x$为$58261$。

**注意：本题允许手动开$O2$优化以避免被卡常数，方法如下：**
``` cpp
%:pragma GCC optimize(2)
/*程序*/
```


---

---
title: "[HAOI2018] 苹果树"
layout: "post"
diff: 省选/NOI-
pid: P4492
tag: ['2018', '河南', '各省省选', 'O2优化', '树形 DP', '双连通分量', '概率论']
---
# [HAOI2018] 苹果树
## 题目背景

HAOI2018 Round2 第一题
## 题目描述

小 C 在自己家的花园里种了一棵苹果树, 树上每个结点都有恰好两个分支. 经过细心的观察, 小 C 发现每一天这棵树都会生长出一个新的结点.

第一天的时候, 果树会长出一个根结点, 以后每一天, 果树会随机选择一个当前树中没有长出过结点 的分支, 然后在这个分支上长出一个新结点, 新结点与分支所属的结点之间连接上一条边.

小 C 定义一棵果树的不便度为树上两两结点之间的距离之和, 两个结点之间 的距离定义为从一个点走到另一个点的路径经过的边数.

现在他非常好奇, 如果 $N$ 天之后小 G 来他家摘苹果, 这个不便度的期望 $E$ 是多少. 但是小 C 讨厌分数, 所以他只想知道 $E \times N !$ 对 $P$ 取模的结果, 可以证明这是一个整数.
## 输入格式

从标准输入中读入数据. 一行两个整数 $N$, $P$ .
## 输出格式

输出到标准输出中. 输出一个整数表示答案．
## 样例

### 样例输入 #1
```
3 610745795
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
305 1000000007
```
### 样例输出 #2
```
865018107
```
## 提示

![Explanation](https://cdn.luogu.com.cn/upload/pic/18067.png)

以上是所有 $N = 3$ 时可能的苹果树形态, 其中编号表示这个结点是第几天生
长出来的, 显然每种情况两两结点的距离均为 $4$ .

### 数据范围与约定
| 测试点编号   | $N$  | $P$  |
| :--------: | :--: | :--: |
| $1$ |  $\le 10$    |  $\le 10^9 + 7$    |
| $2$ |  $\le 10$    |   $\le 10^9 + 7$    |
| $3$ |  $\le 500$    |  $\le 10^9 + 7$     |
| $4$ |  $\le 500$    |   $\le 10^9 + 7$    |
| $5$ |  $\le 500$    |   $\le 10^9 + 7$    |
| $6$ |  $\le 2000$    |   $= 10^9 + 7$    |
| $7$ |  $\le 2000$    |   $= 10^9 + 7$    |
| $8$ |  $\le 2000$    |   $\le 10^9 + 7$    |
| $9$ |  $\le 2000$    |   $\le 10^9 + 7$    |
| $10$ | $\le 2000$     |    $\le 10^9 + 7$   |




---

---
title: "取石子"
layout: "post"
diff: 省选/NOI-
pid: P4706
tag: ['枚举', '素数判断,质数,筛法', '概率论']
---
# 取石子
## 题目描述

现在 Yopilla 和 yww 要开始玩游戏！

他们在一条直线上标记了 $n$ 个点，从左往右依次标号为 $1, 2, ..., n$ 。然后在每个点上放置一些棋子，其中第 $i$ 个点放置了 $a_i$ 个棋子。接下来，从 Yopilla 开始操作，双方轮流操作，谁不能操作谁输。每次的操作是：当前操作方选定一个有棋子的点 $x$ ，然后选择至少一个点 $x$ 上的棋子，然后把这些棋子全都移动到点 $x / prime$ 上，其中 $prime$ 是一个质数，且 $prime \mid x$ 。

Yopilla 最初一次操作的策略是随机的：随机找到一个有棋子的点 $x$ ，随机选择正整数个棋子 $y$ ，随机转移到一个能转移到的点 $z$ 。所有棋子可以看作是一样的，换句话说：两种操作不同，当且仅当三元组 $(x, y, z)$ 不同。之后双方都按照最优策略来操作。

Yopilla 想要预测，他能够获胜的概率是多少，答案对 $998244353$ 取模。
## 输入格式

第一行一个数 $n$ 。

第二行 $n$ 个数 $a_1, a_2, ..., a_n$ 。
## 输出格式

输出 $m$ 行，表示 Yopilla 能够获胜的概率对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3
3 1 2
```
### 样例输出 #1
```
332748118
```
## 提示

样例解释：

$1$ 号点有 $3$ 个棋子，$2$ 号点有 $1$ 个棋子，$3$ 号点有 $2$ 个棋子。第一次操作的时候，能进行的有三种可能：将 $2$ 号点的 $1$ 个棋子移到 $1$ 号点，将 $3$ 号点的 $1$ 个棋子移到 $1$ 号点，将 $3$ 号点的 $2$ 个棋子移到一号点。而其中只有一种情况能使得 Yopilla 有必胜策略。所以答案为
$$\frac{1}{3} \equiv 332748118 \pmod {998244353}$$

对于 $20 \%$ 的数据，只有一个石子。

对于 $100 \%$ 的数据，$1 \le n \le {10} ^ 6, 0 \le a_i \le {10} ^ 9$ ，保证至少有一个不在一号点的石子。


---

---
title: "[PKUWC2018] Minimax"
layout: "post"
diff: 省选/NOI-
pid: P5298
tag: ['2018', '线段树', '树形 DP', '概率论']
---
# [PKUWC2018] Minimax
## 题目描述

小 $C$ 有一棵 $n$ 个结点的有根树，根是 $1$ 号结点，且每个结点最多有两个子结点。

定义结点 $x$ 的权值为：

1.若 $x$ 没有子结点，那么它的权值会在输入里给出，**保证这类点中每个结点的权值互不相同**。

2.若 $x$ 有子结点，那么它的权值有 $p_x$ 的概率是它的子结点的权值的最大值，有 $1-p_x$ 的概率是它的子结点的权值的最小值。

现在小 $C$ 想知道，假设 $1$ 号结点的权值有 $m$ 种可能性，**权值第 $i$ 小**的可能性的权值是 $V_i$，它的概率为 $D_i(D_i>0)$，求：

$$\sum_{i=1}^{m}i\cdot V_i\cdot D_i^2$$

你需要输出答案对 $998244353$ 取模的值。

## 输入格式

第一行一个正整数 $n$；

第二行 $n$ 个整数，第 $i$ 个整数表示第 $i$ 个结点的父亲的编号，其中第 $1$ 个结点的父亲为 $0$；

第三行 $n$ 个整数，若第 $i$ 个结点没有子结点，则第 $i$ 个数为它的权值，否则第 $i$ 个数为 $p_i\cdot 10000$，保证 $p_i\cdot 10000$ 是个正整数。
## 输出格式

输出答案。

## 样例

### 样例输入 #1
```
3
0 1 1
5000 1 2
```
### 样例输出 #1
```
748683266
```
## 提示


#### 样例解释
1号结点的权值有 $\frac{1}{2}$ 的概率是 $1$，有 $\frac{1}{2}$ 的概率是 $2$，所以答案是 $\frac{5}{4}$。

#### 数据范围

- 对于 $10\%$ 的数据，有 $1\leq n\leq 20$；  
- 对于 $20\%$ 的数据，有 $1\leq n\leq 400$；  
- 对于 $40\%$ 的数据，有 $1\leq n\leq 5000$；  
- 对于 $60\%$ 的数据，有 $1\leq n\leq 10^5$；  
- 另有 $10\%$ 的数据保证树的形态随机；  
- 对于 $100\%$ 的数据，有 $1\leq n\leq 3\times 10^5$，$1\leq w_i\leq 10^9$。

对于所有数据，满足 $0 < p_i \cdot 10000 < 10000$，所以易证明所有叶子的权值都有概率被根取到。



---

---
title: "[YNOI2019] 游戏"
layout: "post"
diff: 省选/NOI-
pid: P5415
tag: ['数学', '2019', '各省省选', '云南', '概率论']
---
# [YNOI2019] 游戏
## 题目描述

在经历了漫长的烧脑之旅后，相信同学们的思维已经充分地活跃起来了。最后，让我们玩一个游戏来结束这次充满乐趣和挑战的冒险之旅！

有 $n$ 个人在玩游戏，游戏规则如下：

在游戏开始之前，将这 $n$ 个人按照 $1\sim n$ 的顺序唯一编号。游戏开始后，每一轮只允许 $4$ 个人进入游戏，其他人按照各自的编号组成等待队列，等待参加游戏。

游戏中每个人赢得比赛的机会是同等的，游戏举办多轮，每一轮的获胜者可以继续参加下一轮的比赛，输家将根据本轮比赛开始之前的顺序排在等待队列的末尾（如果本轮的输家中有人之前赢得过比赛，那么他将在等待队列中排在本轮所有输家的前面）。

例如，在某一轮比赛开始之前小明排在小红和小刚前面，如果在该轮比赛中小明、小红和小刚都没有赢，那么小明、小红和小刚将退出比赛排在等待队列的末尾，但是小明将会继续按照比赛开始之前的顺序排在小红和小刚前面。存在的特殊情况是，如果小刚在这轮比赛之前赢得过比赛，那么小刚将在等待序列中排在小明和小红的前面。

比赛中，如果有人连续赢了 $m$ 次，那么他就是这个游戏最后的赢家。你的任务是，预测第 $k$ 个人成为最终赢家的可能。
## 输入格式

**输入包含多组数据。**

第一行，包含一个正整数 $T$，代表该输入文件中所含的数据组数。

接下来是 $T$ 组数据，每组数据的格式如下：

每组数据仅一行，包含三个整数 $n,m,k$。
## 输出格式

输出包含 $T$ 行，分别对应 $T$ 组数据的答案，即第 $k$ 个人成为最终赢家的可能（结果保留 $6$ 位小数）。
## 样例

### 样例输入 #1
```
3
4 1 1
5 1 5
5 2 1

```
### 样例输出 #1
```
0.250000
0.000000
0.217626
```
## 提示

#### 数据规模与约定
- 对于 $30\%$ 的数据：保证 $ n \le 5$，$m \le 5$。
- 对于 $60\%$ 的数据：保证 $n \le 8$，$m \le 8$。
- 对于100%的数据：保证 $4 \le n \le 10$，$0 < m \le 10$，$1\le k \le n$，$T=1$。


---

