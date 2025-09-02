---
title: "[中山市赛 2023] 简单数学题"
layout: "post"
diff: 普及+/提高
pid: B4337
tag: ['数学', '2023', '广东', '期望', '科创活动', '小学活动']
---
# [中山市赛 2023] 简单数学题
## 题目描述

你有两个盒子，第一个盒子里有 $a1$ 个白球和 $a2$ 个黑球，第二个盒子里有 $b1$ 个白球和 $b2$ 个黑球，保证 $a1, a2, b1, b2$ 均大于 $0$。

每一轮你会从第一个盒子里均匀随机选取一个球放到第二个盒子，然后再从第二个盒子里均匀选取一个球放到第一个盒子，求经过 $n$ 轮后从第一个盒子里抽出白球的概率，对于 $998244353$ 取模。 
## 输入格式

一行五个正整数，表示 $n, a1, a2, b1, b2$。
## 输出格式

一行一个整数，表示经过 $n$ 轮后从第一个盒子里抽出白球的概率对于 $998244353$ 取模的值。 
## 样例

### 样例输入 #1
```
1 1 1 1 1
```
### 样例输出 #1
```
499122177
```
### 样例输入 #2
```
7 7 10 10 8
```
### 样例输出 #2
```
362469031
```
### 样例输入 #3
```
4740 3269 4174 4965 2811
```
### 样例输出 #3
```
346687824
```
### 样例输入 #4
```
9037963 835314984430355419 899360196062620295 733639079211073534 740230801366522939
```
### 样例输出 #4
```
35006812
```
### 样例输入 #5
```
912201558090168867 796120182038152428 730024589551167161 792537498108992240
973950897761711340
```
### 样例输出 #5
```
589508199
```
## 提示

### 数据范围

令 $m = \max(a1, a2, b1, b2)$。

对于 $20\%$ 的数据，满足 $m, n \le 20$。

对于 $40\%$ 的数据，满足 $m, n \le 100$。

对于 $60\%$ 的数据，满足 $m, n \le 5000$。

对于 $80\%$ 的数据，满足 $n \le 10^7$。

对于 $100\%$ 的数据，满足 $n, m \le 10^{18}$。 


---

---
title: "Rainbow的信号"
layout: "post"
diff: 普及+/提高
pid: P10500
tag: ['数学', '期望']
---
# Rainbow的信号
## 题目描述

Freda 发明了传呼机之后，rainbow 进一步改进了传呼机发送信息所使用的信号。

由于现在是数字、信息时代，rainbow 发明的信号用 $N$ 个自然数表示。

为了避免两个人的对话被大坏蛋 VariantF 偷听，rainbow 把对话分成 $A、B、C$ 三部分，分别用 $a、b、c$ 三个密码加密。

现在 Freda 接到了 rainbow 的信息，她的首要工作就是解密。

Freda 了解到，这三部分的密码计算方式如下：

在 $1 \sim N$ 这 $N$ 个数中，等概率地选取两个数 $l、r$，如果 $l>r$，则交换 $l、r$。

把信号中的第 $l$ 个数到第 $r$ 个数取出来，构成一个数列 $P$。

$A$ 部分对话的密码是数列 $P$ 的 $xor$ 和的数学期望值，$xor$ 和就是数列 $P$ 中各个数异或之后得到的数； $xor$ 和的期望就是对于所有可能选取的 $l、r$，所得到的数列的 $xor$ 和的平均数。

$B$ 部分对话的密码是数列 $P$ 的 $and$ 和的期望，定义类似于 $xor$ 和。

$C$ 部分对话的密码是数列 $P$ 的 $or$ 和的期望，定义类似于 $xor$ 和。

请你帮忙计算这三个密码。
## 输入格式

第一行一个正整数 $N$。

第二行 $N$ 个自然数，表示 Freda 接到的信号。
## 输出格式

一行三个实数，分别表示 $xor$ 和、$and$ 和、$or$ 和的期望，四舍五入保留 $3$ 位小数，相邻两个实数之间用一个空格隔开。
## 样例

### 样例输入 #1
```
2
4 5
```
### 样例输出 #1
```
2.750 4.250 4.750

```
## 提示

### 样例解释

样例 1 共包含四种可能的 $l,r$：

|c|c|c|c|
|-|-|-|-|
|$l, r$ | xor 和 | and 和 | or 和 |
|1,1 | 4 | 4 | 4 |
|1,2 | 1 | 4 | 5 |
|2,1 | 1 | 4 | 5 |
|2,2 | 5 | 5 | 5 |

以上每一对 $l,r$ 出现的概率均相同, 因此分别对 xor 和、and 和、or 和取平均数就是数学期望值。

## 数据范围与约定

对于 $20 \%$ 的数据， $1 \le N \le 100$ 。  
对于 $40 \%$ 的数据， $1 \le N \le 1000$ 。  
对于另外 $30 \%$ 的数据, $N$ 个数为 $0$ 或 $1$ 。  
对于 $100 \%$ 的数据, $1 \le N \le 100000$，$N$ 个自然数均不超过 $10^9$ 。


---

---
title: "守卫者的挑战"
layout: "post"
diff: 普及+/提高
pid: P10504
tag: ['动态规划 DP', 'O2优化', '期望']
---
# 守卫者的挑战
## 题目描述

打开了黑魔法师 Vani 的大门，队员们在迷宫般的路上漫无目的地搜寻着关押 applepi 的监狱的所在地。突然，眼前一道亮光闪过。“我，Nizem，是黑魔法圣殿的守卫者。如果你能通过我的挑战，那么你可以带走黑魔法圣殿的地图……”瞬间，队员们被传送到了一个擂台上，最初身边有一个容量为K的包包。
  
擂台赛一共有 $N$ 项挑战，各项挑战依次进行。第 $i$ 项挑战有一个属性 $a_i$，如果 $a_i\geq 0$，表示这次挑战成功后可以再获得一个容量为 $a_i$ 的包包；如果 $a_i=-1$，则表示这次挑战成功后可以得到一个大小为 $1$ 的地图残片。地图残片必须装在包包里才能带出擂台，包包没有必要全部装满，但是队员们必须把 【获得的所有的】地图残片都带走（没有得到的不用考虑，只需要完成所有N项挑战后背包容量足够容纳地图残片即可），才能拼出完整的地图。并且他们至少要挑战成功 $L$ 次才能离开擂台。
  
队员们一筹莫展之时，善良的守卫者 Nizem 帮忙预估出了每项挑战成功的概率，其中第 $i$ 项挑战成功的概率为 $p_i\%$。现在，请你帮忙预测一下，队员们能够带上他们获得的地图残片离开擂台的概率。
## 输入格式

第一行三个整数 $N,L,K$。
  
第二行 $N$ 个实数，第 $i$ 个实数 $p_i$ 表示第 $i$ 项挑战成功的百分比。
  
第三行 $N$ 个整数，第 $i$ 个整数 $a_i$ 表示第 $i$ 项挑战的属性值.
## 输出格式

一个整数，表示所求概率，四舍五入保留 $6$ 位小数。
## 样例

### 样例输入 #1
```
3 1 0
10 20 30
-1 -1 2
```
### 样例输出 #1
```
0.300000

```
### 样例输入 #2
```
5 1 2
36 44 13 83 63
-1 2 -1 2 1
```
### 样例输出 #2
```
0.980387
```
## 提示

在第一个样例中，若第三项挑战成功，如果前两场中某场胜利，队员们就有空间来容纳得到的地图残片，如果挑战失败，根本就没有获得地图残片，不用考虑是否能装下；若第三项挑战失败，如果前两场有胜利，没有包来装地图残片，如果前两场都失败，不满足至少挑战成功1次的要求。因此所求概率就是第三场挑战获胜的概率。

对于 $100\%$ 的数据，保证 $0\leq K\leq 2000$，$0\leq N\leq 200$，$-1\leq a_i\leq 1000$，$0\leq L\leq N$，$0\leq p_i\leq 100$。


---

---
title: "BZOJ2720 [Violet 5] 列队春游"
layout: "post"
diff: 普及+/提高
pid: P10668
tag: ['O2优化', '期望']
---
# BZOJ2720 [Violet 5] 列队春游
## 题目描述

给定正整数数列 $h_1,h_2,\cdots,h_n$。设 $p$ 为 $1\sim n$ 的随机排列。

定义 $h'_i=h_{p_i}$。定义 $\mathrm{pre}_i$ 为最大的 $j\lt i$ 满足 $h'_j\ge h'_i$（如果不存在，规定为 $0$）。

求出 $\displaystyle \sum_{i=1}^n (i-\mathrm{pre}_i)$ 的期望值，保留两位小数输出。
## 输入格式

第一行一个正整数 $n$，表示数列长度。

第二行 $n$ 个正整数 $h_i$。
## 输出格式

输出一行一个实数，表示答案，保留两位小数。
## 样例

### 样例输入 #1
```
3
3 2 1
```
### 样例输出 #1
```
4.33
```
## 提示

对于 $20\%$ 的数据，$1\leq n\leq 10$；

对于 $50\%$ 的数据，$1\leq n\leq 70$，且 $h_i$ 互不相同；

对于 $100\%$ 的数据，保证 $1\leq n\leq 300$，$1\leq h_i\leq 1000$。


---

---
title: "『SpOI - R1』笑起来最帅的小孩"
layout: "post"
diff: 普及+/提高
pid: P10792
tag: ['O2优化', '组合数学', '期望']
---
# 『SpOI - R1』笑起来最帅的小孩
## 题目描述

**本题包含多组数据。**

有一个数字序列 $a$，长度为 $n$。序列中每一项均为 $0$ 到 $9$ 的数字。

另有一个空数字序列 $b$，$b$ 中会出现一个**光标**（你可以理解为能够出现在数字之间，或整个数字序列之前，或整个数字序列之后的细线），此时**光标**前后均没有数字。

现在向 $b$ 中依次输入数字序列 $a$。每输入一个数字，数字立即出现在**光标**之后。

接下来**光标**立即随机地移动到任意一个数字之前或所有数字之后。随机是均匀的。换句话说，**光标**移动到所有可移动到的位置的概率是均等的。

现在告诉你数字序列 $a$。你需要输出的是，最终得到的 $b$ 直接转为十进制后的大小（无视前导零）的期望，对质数 $2007072007$ 取模。

由于 $a$ 可能很长，所以本题采用压缩输入。

具体来说，最开始 $a$ 是空的数字序列，输入会给你一个 $k$ 长的二元组数组，其中第 $i$ 项为 $(x_i,l_i)$，表示数字 $x_i$ 连续出现 $l_i$ 次接在之前的 $a$ 之后。你可以用此方法解压缩真正的 $a$，再解决问题。

----------

**在本题，你可以对期望的理解**：对于一个变量可能的结果 $X$，若其权值为 $v_X$，得到该结果的概率为 $p_X$，则对于结果集 $S$，变量的期望 $E=\sum\limits_{X\in S}p_Xv_X$。

**如果你不知道如何对有理数取模**：请查看[此题](https://www.luogu.com.cn/problem/P2613)。
## 输入格式

第一行一个整数 $T$，表示数据组数。

对于每组数据：

一行一个整数 $k$，表示 $a$ 压缩后得到的二元组数组包含多少项。

接下来共 $k$ 行，每行两个整数 $x_i,l_i$，表示在上一项所得 $a$ 序列的基础上，在末尾增加 $l_i$ 个数字 $x_i$ 得到新的 $a$ 序列。你可以用这种方式解压缩真正的 $a$ 序列。
## 输出格式

对于每组数据，输出一行一个整数，表示在光标每次都随机移动的情况下，可能得到的 $b$ 转化为十进制后的大小（无视前导零）的期望，对质数 $2007072007$ 取模的值。
## 样例

### 样例输入 #1
```
1
2
4 1
2 1
```
### 样例输出 #1
```
33
```
### 样例输入 #2
```
1
3
1 2
3 1
7 2
```
### 样例输出 #2
```
1204285426
```
## 提示

### 数据范围

**本题开启子任务捆绑和子任务依赖。**

令 $n=\sum\limits_{i=1}^k l_i$。

对于 $100\%$ 的数据，保证 $1\leq T\leq 15$，$1\leq n\leq 2\times 10^9$，$1\leq k\leq 10^5$，且对于任意 $i$ 均有 $0\leq a_i\leq 9$，$1\leq l_i\leq 2\times 10^9$。


| Subtask | $T\leq$ | $n\leq$ | 特殊性质 | 得分 | 子任务依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $15$ | $2\times 10^9$ | $A$ | $10$ | 无 |
| 2 | $15$ | $100$ | 无 | $15$ | 无 |
| 3 | $5$ | $2000$ | 无 | $15$ | 2 |
| 4 | $5$ | $10^6$ | 无 | $15$ | 2,3 |
| 5 | $5$ | $2\times 10^9$ | 无 | $45$ | 1,2,3,4 |

特殊性质 $A$：保证在解压缩后的 $a$ 中，任意一个数字都出现了最多一次。


---

---
title: "[蓝桥杯 2024 省 Java B] 最优分组"
layout: "post"
diff: 普及+/提高
pid: P11045
tag: ['数学', '2024', '枚举', '期望', '蓝桥杯省赛']
---
# [蓝桥杯 2024 省 Java B] 最优分组
## 题目描述

小蓝开了一家宠物店，最近有一种 X 病毒在动物之间进行传染，小蓝为了以防万一打算购买测试剂对自己的宠物进行病毒感染测试。

为了减少使用的测试剂数目，小蓝想到了一个好方法：将 $N$ 个宠物平均分为若干组，使得每组恰好有 $K$ 只宠物，这样对同一组的宠物进行采样并混合后用一个试剂进行检测，如果测试结果为阴性则说明组内宠物都未感染 X 病毒；如果是阳性的话则需要对组内所有 $K$ 只宠物单独检测，需要再消耗 $K$ 支测试剂（当 $K=1$ 时，就没必要再次进行单独检测了，因为组内只有一只宠物，一次检测便能确认答案）。

现在我们已知小蓝的宠物被感染的概率为 $p$，请问 $K$ 应该取值为多少，才能使得期望的测试剂的消耗数目最少？如果有多个答案，请输出最小的 $K$。
## 输入格式

第一行，一个整数 $N$。

第二行，一个浮点数 $p$。
## 输出格式

输出一行，一个整数 $K$ 表示答案。
## 样例

### 样例输入 #1
```
1000
0.05
```
### 样例输出 #1
```
5
```
## 提示

**【评测用例规模与约定】**

对于 $30\%$ 的评测用例：$1\leq N\leq 10$。

对于 $60\%$ 的评测用例：$1\leq N\leq 1000$。

对于 $100\%$ 的评测用例：$1\leq N\leq 10^6$，$0\leq p\leq 1$。


---

---
title: "[蓝桥杯 2023 国 Java B] 游戏"
layout: "post"
diff: 普及+/提高
pid: P12225
tag: ['单调队列', '2023', '期望', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Java B] 游戏
## 题目描述

熊大和熊二在玩游戏。他们将 $n$ 个正整数 $a_1, a_2, \dots, a_n$ 排成一行，然后各用一个长度为 $k$ 的框在这个数组中各自随机框选出一段长度为 $k$ 的连续子序列（随机框选指在合法的 $n - k + 1$ 个连续子序列中均匀随机）。熊大记录了他框出的 $k$ 个数中的最大值 $P$，熊二记录了他框出的 $k$ 个数的最小值 $Q$，他们突然有个疑问：$P - Q$ 的期望是多少？
## 输入格式

输入共 $2$ 行。

第一行为两个正整数 $n, k$。

第二行为 $n$ 个由空格隔开的正整数 $a_1, a_2, \dots, a_n$。
## 输出格式

输出共 $1$ 行，一个浮点数（请保留两位小数）。
## 样例

### 样例输入 #1
```
3 2
1 2 3
```
### 样例输出 #1
```
1.00
```
## 提示

### 样例说明

一共有四种情况：

- 熊大框出 $[1, 2]$，$P = 2$；熊二框出 $[1, 2]$，$Q = 1$，$P - Q = 1$。
- 熊大框出 $[1, 2]$，$P = 2$；熊二框出 $[2, 3]$，$Q = 2$，$P - Q = 0$。
- 熊大框出 $[2, 3]$，$P = 3$；熊二框出 $[1, 2]$，$Q = 1$，$P - Q = 2$。
- 熊大框出 $[2, 3]$，$P = 3$；熊二框出 $[2, 3]$，$Q = 2$，$P - Q = 1$。

所以 $P - Q$ 的期望为 $(1 + 0 + 2 + 1) / 4 = 1.00$。

### 评测用例规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 10^2$。
- 对于 $40\%$ 的数据，保证 $n \leq 10^3$。
- 对于 $100\%$ 的数据，保证 $n \leq 10^5$，$0 < a_i \leq 10^9$，$0 < k \leq n$。


---

---
title: "[蓝桥杯 2024 国 Python A] 羊圈"
layout: "post"
diff: 普及+/提高
pid: P12282
tag: ['2024', 'Special Judge', '期望', '蓝桥杯国赛', '状压 DP']
---
# [蓝桥杯 2024 国 Python A] 羊圈
## 题目描述

小蓝养了 $m$ 头羊，它们站成一排，第 $i$ 头羊有 $p_i$ 的概率跑掉。小蓝为了不让他的羊跑掉，购买了 $n$ 个羊圈，第 $i$ 个羊圈最多可以框住连续的 $l_i$ 只羊，让它们无法逃跑。小蓝想知道，在合理安排羊圈位置的情况下，能跑掉的羊的数量的期望的最小值是多少？

请注意：羊圈不一定都使用，也不一定按顺序使用。
## 输入格式

输入的第一行包含两个正整数 $n, m$，用一个空格分隔。

第二行包含 $n$ 个正整数 $l_1, l_2, \cdots, l_n$，相邻整数之间使用一个空格分隔。

第三行包含 $m$ 个浮点数 $p_1, p_2, \cdots, p_m$，每个浮点数小数点后不超过 $2$ 位小数，相邻浮点数之间使用一个空格分隔。
## 输出格式

输出一行包含一个浮点数表示答案，四舍五入保留正好两位小数。
## 样例

### 样例输入 #1
```
3 10
1 2 3
0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
```
### 样例输出 #1
```
1.00
```
## 提示

### 样例说明

第一个羊圈框住第 $5$ 头羊，第二个羊圈框住第 $9$ 至第 $10$ 头羊，第三个羊圈框住第 $6$ 至第 $8$ 头羊，剩下的羊逃跑的数量的期望为 $0.1 + 0.2 + 0.3 + 0.4 = 1.0$

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n \leq 8$；
- 对于所有评测用例，$1 \leq n \leq 15$，$1 \leq m \leq 200$，$1 \leq l_i \leq m$，$0 \leq p_i \leq 1$。


---

---
title: "[国家集训队] 单选错位"
layout: "post"
diff: 普及+/提高
pid: P1297
tag: ['数学', '集训队互测', '概率论', '期望']
---
# [国家集训队] 单选错位
## 题目描述

gx 和 lc 去参加 noip 初赛，其中有一种题型叫单项选择题，顾名思义，只有一个选项是正确答案。

试卷上共有 $n$ 道单选题，第 $i$ 道单选题有 $a_i$ 个选项，这 $a_i$ 个选项编号是 $1,2,3,\ldots,a_i$，每个选项成为正确答案的概率都是相等的。

lc 采取的策略是每道题目随机写上 $1 \sim a_i$ 的某个数作为答案选项，他用不了多少时间就能期望做对 $\sum_{i=1}^n \frac{1}{a_i}$ 道题目。gx 则是认认真真地做完了这 $n$ 道题目，可是等他做完的时候时间也所剩无几了，于是他匆忙地把答案抄到答题纸上，没想到抄错位了：第 $i$ 道题目的答案抄到了答题纸上的第 $i+1$ 道题目的位置上，特别地，第 $n$ 道题目的答案抄到了第 $1$ 道题目的位置上。

现在 gx 已经走出考场没法改了，不过他还是想知道自己期望能做对几道题目，这样他就知道会不会被 lc 鄙视了。

我们假设 gx 没有做错任何题目，只是答案抄错位置了。

## 输入格式

$n$ 很大，为了避免读入耗时太多，输入文件只有 $5$ 个整数参数 $n, A, B, C, a_1$，由上交的程序产生数列 $a$。下面给出 pascal/C/C++ 的读入语句和产生序列的语句（默认从标准输入读入）：

```cpp
// for pascal
readln(n,A,B,C,q[1]);
for i:=2 to n do
q[i] := (int64(q[i-1]) * A + B) mod 100000001;
for i:=1 to n do
q[i] := q[i] mod C + 1;


// for C/C++
scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
for (int i = 2; i <= n; i++)
	a[i] = ((long long) a[i - 1] * A + B) % 100000001;
for (int i = 1; i <= n; i++)
	a[i] = a[i] % C + 1;
```

选手可以通过以上的程序语句得到 $n$ 和数列 $a$（$a$ 的元素类型是 $32$ 位整数），$n$ 和 $a$ 的含义见题目描述。

## 输出格式

输出一个实数，表示 gx 期望做对的题目个数，保留三位小数。

## 样例

### 样例输入 #1
```
3 2 0 4 1
```
### 样例输出 #1
```
1.167

```
## 提示

【样例说明】

| 正确答案   |   gx的答案    | 做对题目 | 出现概率 |
| :----------: | :----------: |:----------: | :----------: |
| $\{1,1,1\}$  |    $\{1,1,1\}$    |    $3$    |    $\frac16$ |
| $\{1,2,1\}$    |   $ \{1,1,2\}$   |    $1$    |    $\frac16$ |
|$\{1,3,1\}$    |   $ \{1,1,3\} $   |    $1$    |    $\frac16$ |
|$\{2,1,1\}$    |   $ \{1,2,1\} $   |    $1$    |    $\frac16$|
|$\{2,2,1\}$    |   $ \{1,2,2\}$    |    $1$    |    $\frac16$ |
|$\{2,3,1\}$    |    $\{1,2,3\} $   |    $0$    |    $\frac16$ |




$a = \{2,3,1\}$。

共有 $6$ 种情况，每种情况出现的概率是 $\frac{1}{6}$，gx 期望做对 $\frac{3+1+1+1+1+0}6 = \frac76$ 题。（相比之下，lc 随机就能期望做对 $\frac{11}6$ 题）



对于 $30\%$ 的数据，$n\leq 10, C\leq 10$。

对于 $80\%$ 的数据，$n\leq 10^4, C\leq 10$。

对于 $90\%$ 的数据，$n\leq 5\times 10^5, C\leq 10^8$。

对于 $100\%$ 的数据，$2\leq n\leq 10^7, 0\leq A,B,C \leq 10^8$，$1 \leq a_i \leq 10^8$。



---

---
title: "[GCJ 2015 #1C] Typewriter Monkey"
layout: "post"
diff: 普及+/提高
pid: P13222
tag: ['动态规划 DP', '2015', 'Special Judge', '期望', 'KMP 算法', 'Google Code Jam']
---
# [GCJ 2015 #1C] Typewriter Monkey
## 题目描述

Your publishing house has decided to use monkeys randomly typing at keyboards to write great works of literature. You are the supervisor for one monkey with a keyboard containing $K$ keys, each of which is labeled with an uppercase English letter. (There may be multiple keys displaying the same letter.) The monkey will start with an empty string and repeat the following $S$ times: choose a key from its keyboard uniformly at random and press it, adding a copy of that key's letter to the right end of the string. The final resulting string will have length $S$.

You have a *target word* of length $L$ that you are hoping the monkey will type. (The target word will not necessarily be a real English word.) This target word may even appear multiple times in what the monkey types. (Overlapping instances count too -- for example, if "ABA" is the target word and the monkey types "ABABA", that contains two instances of the target.)

You plan to pay the monkey one banana for each instance of the target word that it types. When you go to inspect the monkey's work, you will bring along the minimum number of bananas that you need to ensure that you will always have enough bananas to pay the monkey, no matter what it has typed. Then, you will pay the monkey one banana for each instance of the target word that it actually typed. You will keep the remaining bananas that you brought with you.

What is the expected number of bananas that you will get to keep?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each consists of three lines. The first contains three space-separated positive integers: $K$, $L$, and $S$. The second contains a string of $K$ uppercase English letters representing the monkey's keyboard. The third contains a string of $L$ uppercase English letters representing the target word.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $y$ is the expected number of bananas you will get to keep after paying the monkey.

$y$ will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer.
## 样例

### 样例输入 #1
```
5
7 6 6
BANANAS
MONKEY
2 3 4
AA
AAA
2 1 2
AB
B
6 2 2
GOOGLE
GO
26 11 100
ABCDEFGHIJKLMNOPQRSTUVWXYZ
ROSENCRANTZ
```
### 样例输出 #1
```
Case #1: 0.0
Case #2: 0.0
Case #3: 1.0
Case #4: 0.8888889
Case #5: 9.0
```
## 提示

**Sample Explanation**

Note that Case #5 is not within the limits for the Small dataset.

In Case #1, the monkey has no chance of typing the target word "MONKEY" even once (because his keyboard lacks most of the letters in "MONKEY"), so you do not bring any bananas along when you visit, and of course you do not pay any. Poor monkey!

In Case #2, the monkey is guaranteed to type "AAAA", which has two overlapping instances of the target word "AAA". You will bring two bananas and then pay both.

In Case #3, the monkey will produce the following outputs with equal probability (1/4 each): "AA", "AB", "BA", "BB". These have 0, 1, 1, and 2 instances of the target word, respectively. You must bring 2 bananas to be ready for the "BB" case, but you will on average pay $(0 + 1 + 1 + 2) / 4 = 1$.

In Case #4, the monkey has a $1/3$ chance of typing a "G" first and a $1/3$ chance of typing an "O" second, for a $1/9$ chance of typing "GO". You will bring one banana and give it up $1/9$ of the time.

In Case #5, the monkey could in theory type "ROSENCRANTZ" up to nine times, but the chances of this happening even once are so small that they are negligible compared to the acceptable margin of error for answers.

**Limits**

$1 \leq T \leq 100$.

**Small dataset(11 Pts)**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq K \leq 7$.
- $1 \leq L \leq S \leq 7$.

**Large dataset**

- Time limit: ~~480~~ 10 seconds.
- $1 \leq K \leq 100$.
- $1 \leq L \leq S \leq 100$.


---

---
title: "[GCJ 2012 #1A] Password Problem"
layout: "post"
diff: 普及+/提高
pid: P13315
tag: ['2012', 'Special Judge', '期望', 'Google Code Jam']
---
# [GCJ 2012 #1A] Password Problem
## 题目描述

I have a really long password, and sometimes I make a mistake when I type it. Right now I've typed part of my password, but I might have made some mistakes. In particular, I might have pressed the wrong key while typing one or more of the previous characters. Given how likely I was to get each character right, what should I do?

I have three options:

1. Finish typing the password, then press "enter". I know I'll type the rest of the characters perfectly. If it turns out that one of the earlier characters was wrong, I'll have to retype the whole thing and hit "enter" again -- but I know I'll get it right the second time.
2. Hit "backspace" some number of times, deleting the last character(s) I typed, and then complete the password and press "enter" as in option 1. If one of the characters I didn't delete was wrong, I'll have to retype the whole thing and press "enter", knowing I'll get it right the second time.
3. Give up by pressing "enter", retyping the password from the start, and pressing "enter" again. I know I'll get it right this time.

I want to minimize the expected number of keystrokes needed. Each character in the password costs 1 keystroke; each "backspace" costs 1 keystroke; pressing "enter" to complete an attempt or to give up costs 1 keystroke.

Note: The "expected" number of keystrokes is the average number of keystrokes that would be needed if the same situation occurred a very large number of times. See the example below.

**Example**

Suppose my password is "guest" and I have already typed the first two characters, but I had a $40\%$ chance of making a mistake when typing each of them. Then there are four cases:

* I typed "gu" without error. This occurs with probability $0.6 \times 0.6 = 0.36$.
* I typed the 'g' correctly but I made a mistake typing the 'u'. Then I have two letters typed still, but the second one is wrong: "gx". (Here, the 'X' character represents a mistyped letter.) This occurs with probability $0.6 \times 0.4 = 0.24$.
* I typed the 'u' correctly but I made a mistake typing the 'g': "xu". This occurs with probability $0.4 \times 0.6 = 0.24$.
* I made a mistake typing both letters, so I have two incorrect letters: "xx". This occurs with probability $0.4 \times 0.4 = 0.16$.

I don't know how many mistakes I actually made, but for any strategy, I can calculate the expected number of keys required to use it. This is shown in the table below:

| Probability | "gu" | "gx" | "xu" | "xx" | Expected |
|:-:|:-:|:-:|:-:|:-:|:-:|
| Keystrokes if I keep typing | $4$ | $10$ | $10$ | $10$ | $7.84$ |
| Keystrokes if I press backspace once | $6$ | $6$ | $12$ | $12$ | $8.4$ |
| Keystrokes if I press backspace twice | $8$ | $8$ | $8$ | $8$ | $8$ |
| Keystrokes if I press enter right away | $7$ | $7$ | $7$ | $7$ | $7$ |

If I keep typing, then there is an $0.36$ probability that I will need $4$ keystrokes, and an $0.64$ probability that I will need $10$ keystrokes. If I repeated the trial many times, then I would use $4$ keystrokes $36\%$ of the time, and $10$ keystrokes the remaining $64\%$ of the time, so the average number of keystrokes needed would be $0.36 \times 4 + 0.64 \times 10 = 7.84$. In this case however, it is better to just press enter right away, which requires $7$ keystrokes.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing two integers, $A$ and $B$. $A$ is the number of characters that I have already typed, and $B$ is the total number of characters in my password.

This is followed by a line containing $A$ real numbers: $p_1$, $p_2$, $\dots$, $p_A$. $p_i$ represents the probability that I correctly typed the $i^{th}$ letter in my password. These real numbers will consist of decimal digits and at most one decimal point. The decimal point will never be the first or the last character in a number.
## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1) and $y$ is the expected number of additional keystrokes I need, not counting the letters I have typed so far, and assuming I choose the optimal strategy. $y$ must be correct to within an absolute or relative error of $10^{-6}$.
## 样例

### 样例输入 #1
```
3
2 5
0.6 0.6
1 20
1
3 4
1 0.9 0.1
```
### 样例输出 #1
```
Case #1: 7.000000
Case #2: 20.000000
Case #3: 4.500000
```
## 提示

**Limits**

- $1 \leq T \leq 20$.
- $0 \leq p_i \leq 1$ for all $i$.

**Test set 1 (10 Pts, Visible Verdict)**

- $1 \leq A \leq 3$.
- $A < B \leq 100$.

**Test set 2 (10 Pts, Hidden Verdict)**

- $1 \leq A \leq 99999$.
- $A < B \leq 100000$.


---

---
title: "小魔女帕琪"
layout: "post"
diff: 普及+/提高
pid: P3802
tag: ['洛谷原创', '排列组合', '条件概率', '期望']
---
# 小魔女帕琪
## 题目背景

从前有一个聪明的小魔女帕琪，兴趣是狩猎吸血鬼。

帕琪能熟练使用七种属性（金、木、水、火、土、日、月）的魔法，除了能使用这么多种属性魔法外，她还能将两种以上属性组合，从而唱出强力的魔法。比如说为了加强攻击力而将火和木组合，为了掩盖弱点而将火和土组合等等，变化非常丰富。
## 题目描述

现在帕琪与强大的夜之女王，吸血鬼蕾咪相遇了，夜之女王蕾咪具有非常强大的生命力，普通的魔法难以造成效果，只有终极魔法：帕琪七重奏才能对蕾咪造成伤害。帕琪七重奏的触发条件是：连续施放的 $7$ 个魔法中，如果魔法的属性各不相同，就能触发一次帕琪七重奏。

请注意，无论前 $6$ 个魔法是否已经参与施放终极魔法，只要连续 $7$ 个魔法的属性各不相同，就会再触发一次终极魔法。例如，如果用序号来代表一种魔法，魔法的施放序列为 $1, 2, 3, 4, 5, 6,7, 1$，则前 $7$ 个魔法会触发一次终极魔法，后 $7$ 个魔法会再触发一次终极魔法。

现在帕琪有 $7$ 种属性的能量晶体，第 $i$ 种晶体可以施放出属性为 $i$ 的魔法，共有 $a_i$ 个。每次施放魔法时，会等概率随机消耗一个现有的能量晶体，然后释放一个对应属性的魔法。

现在帕琪想知道，她触发帕琪七重奏的期望次数是多少，可是她并不会算，于是找到了学 OI 的你。
## 输入格式

输入只有一行 $7$ 个整数，第 $i$ 个整数代表 $a_i$。
## 输出格式

输出一行一个实数代表答案，四舍五入保留三位小数。
## 样例

### 样例输入 #1
```
1 1 1 1 1 1 1
```
### 样例输出 #1
```
1.000
```
## 提示

#### 样例输入输出 1 解释

显然一定会触发一次帕琪七重奏。

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $\sum_{i = 1}^7 a_i \leq 10$。
- 对于 $100\%$ 的数据，保证 $0 \leq a_i \leq 10^9$，且 $\sum_{i = 1}^7 a_i \leq 10^9$。


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
title: "荷取融合"
layout: "post"
diff: 普及+/提高
pid: P5131
tag: ['动态规划 DP', '期望']
---
# 荷取融合
## 题目背景

作为一款Rougelike类游戏，TODR具有丰富的装备系统。每一款装备独特的外观和华丽的特效，上百种各有效果的印记，复杂的炼成调和分解融合系统都塑造了这款游戏极高的游戏性。    

现在你的装备刷到了满级，需要和其他装备融合来继续成长，当然，你需要让河城荷取将你原装备中的印记抽取出来以便和新装备合成。 
## 题目描述

已知原装备有 $n$ 个印记槽，每个印记槽中有无限多的一种印记，第 $i$ 个印记槽中的这种印记价值为 $a_{i}$。     

河城荷取会用机械臂抽取印记槽内的印记，每一次抽取时，机械臂会向下抓取，从正下方的印记槽中抽取出一个印记，之后机械臂会向右移动或停留在原地(如果移动，那么可以移动任意格)，开始时机械臂的位置任意，但是任意时刻机械臂都必须在某个印记槽上。  

河城荷取会进行 $k$ 次抓取，抓取结束后，你获得的总收益等于抓上来的 $k$ 个印记价值的乘积。

假设河城荷取进行的一切操作都是随机的，那么你能获得的收益的平均值是多少呢?  

由于答案可能不是整数，你只需输出答案对 $\text{19260817}$ 取模后的结果。  
## 输入格式

第一行两个整数 $n,k$ ，表示印记槽的个数和抓取的次数。 
  
第二行 $n$ 个正整数 $a_{i}$ ，表示每个印记槽内印记的价值 。 
## 输出格式

一个整数，表示 $k$ 次抓取结束后的收益的平均值。
## 样例

### 样例输入 #1
```
3 2
3 1 2
```
### 样例输出 #1
```
16050685
```
### 样例输入 #2
```
6 3
1 1 4 5 1 4
```
### 样例输出 #2
```
16509294
```
## 提示

#### 样例 $1$ 解释:  

机械臂开始可以停在三个槽上方。  

先后抓取的印记槽的位置可以是 $(1,1),(1,2),(1,3),(2,2),(2,3),(3,3)$ 六种,每一种抓取方案的收益分别是 $9,3,6,1,2,4$ ，平均值为 $\frac{25}{6}$，在 $ \text{mod 19260817}$ 的意义下等于 $16050685$   


#### 数据范围:  

$a_{i}<19260817$  

![](https://cdn.luogu.com.cn/upload/pic/42182.png)   


---

---
title: "游走"
layout: "post"
diff: 普及+/提高
pid: P6154
tag: ['2020', '记忆化搜索', '拓扑排序', '期望']
---
# 游走
## 题目背景

zbw 在 B 城游走。
## 题目描述

B 城可以看作一个有 $n$ 个点 $m$ 条边的**有向无环图**。**可能存在重边**。

zbw 在 B 城随机游走，他会在所有路径中随机选择一条路径，选择所有路径的概率相等。路径的起点和终点可以相同。

定义一条路径的长度为经过的边数，你需要求出 zbw 走的路径长度的期望，答案对 $998244353$ 取模。
## 输入格式

第一行两个整数 $n,m$。

接下来 $m$ 行，每行两个整数 $x,y$，表示存在一条从 $x$ 到 $y$ 的有向边。
## 输出格式

一行一个整数，表示答案对 $998244353$ 取模后的值。
## 样例

### 样例输入 #1
```
3 2
1 2
3 2
```
### 样例输出 #1
```
199648871
```
### 样例输入 #2
```
6 5
1 3
2 3
3 4
4 5
4 6
```
### 样例输出 #2
```
630470119
```
### 样例输入 #3
```
5 6
1 2
1 3
4 5
3 4
3 5
2 4
```
### 样例输出 #3
```
887328315
```
## 提示

样例说明：样例的答案分别为 $\dfrac{2}{5}$，$\dfrac{25}{19}$ 和 $\dfrac{11}{9}$。

| 测试点编号 | $n$ | $m$ | 特殊性质 | 每测试点分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1,2$ | $\le 10$ | $\le 10$ | 无 | $2$ |
| $3,4,5$ | $\le 15$ | $\le 100$ | 无 | $2$ |
| $6,7,8$ | $\le 100$ | $\le 10^3$ | 无 | $2$ |
| $9,10$ | $\le 10^3$ | $\le 10^4$ | 无 | $2$ |
| $11,12$ | $\le 10^4$ | $\le 10^5$ | 无 | $5$ |
| $13,14$ | $\le 10^5$ | $\le 2\times10^5$ | 无 | $5$ |
| $15,16$ | $\le 10^5$ | $\le 7\times10^5$ | 无 | $10$ |
| $17$ | $\le 10$ | $=n-1$ | 有向树 | $10$ |
| $18$ | $\le 10^3$ | $=n-1$ | 有向树 | $10$ |
| $19$ | $\le 10^4$ | $=n-1$ | 有向树 | $10$ |
| $20$ | $\le 10^5$ | $=n-1$ | 有向树 | $10$ |

其中，“有向树”的定义是：若把图视为无向图，则为一棵树（如样例 $1,2$）。

保证所有数据均按照某种方式随机，这意味着你可以认为算法执行过程中，你可以放心执行模意义下除法操作而不用担心除以零。


---

---
title: "[RC-03] 随机树生成器"
layout: "post"
diff: 普及+/提高
pid: P6862
tag: ['O2优化', '前缀和', '期望', '逆元']
---
# [RC-03] 随机树生成器
## 题目描述

小 R 有一个随机树生成器，其工作原理如下：
- 输入 $n$，则对于每个 $1<i\le n$，随机选择一个 $[1,i)$ 中的节点作为其父亲。返回这棵树。

给定 $n,k$，小 R 想知道可能生成的所有 $n$ 个点的树中，$k$ 号点的度数和。

由于答案可能很大，请输出答案模 $10^9+9$ 的值。
## 输入格式

**本题有多组数据。**

第一行一个整数，是数据组数 $T$。

接下来 $T$ 行，每行两个正整数 $n,k$。
## 输出格式

$T$ 行，每行一个整数，为这组数据的答案模 $10^9+9$ 的值。
## 样例

### 样例输入 #1
```
3
3 1
3 2
3 3
```
### 样例输出 #1
```
3
3
2
```
## 提示

【样例说明】

- 数据 $1$：一共有两种情况，$1$ 号点的度数分别为 $1,2$。因此答案为 $3$。
- 数据 $2$：一共有两种情况，$2$ 号点的度数分别为 $1,2$。因此答案为 $3$。
- 数据 $3$：一共有两种情况，$3$ 号点的度数均为 $1$。因此答案为 $2$。

【数据范围】

本题捆绑测试。

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le k\le n\le 10^7$。详细数据范围如下。

- Subtask 1（20 分）：$T\le 50$，$n\le 8$。
- Subtask 2（55 分）：$T=1$，$n\le 10^5$。
- Subtask 3（20 分）：$T=1$。
- Subtask 4（5 分）：没有任何附加限制。


---

---
title: "「C.E.L.U-02」学术精神"
layout: "post"
diff: 普及+/提高
pid: P7474
tag: ['动态规划 DP', '数学', 'Special Judge', '动态规划优化', '连通块', '期望']
---
# 「C.E.L.U-02」学术精神
## 题目描述

提供 **一句话题意** 阅读。

某地有 $n$ 个小朋友，每个小朋友都有一个**独特的**  idea，其中第 $i$ 个小朋友的 idea 的 **编号** 为 $i$。老师让这个每一个小朋友在一组编号分别为 $1\sim n$ 的卡片中随机抽一个，**抽完后把卡片放回去**，这个小朋友会和编号为卡片上数字的小朋友**交换** idea（交换指**两人**把**所有**自己知道的 idea 告诉对方）。因为自己和自己交换 idea 在他们眼中也许是一件很傻的事情，所以如果**卡片上的编号与自己的相同**，他将再抽一次（此时他已经把卡片放回去了），**直到编号不是自己**的为止。

不久，每个小朋友都抽完了一遍，每个小朋友将把收集到的**所有** idea 出成一场比赛，因为有 idea 的交换，有很多比赛之间都是**有联系**的。

如果两场比赛中存在 idea **相同**的题目，我们认为这两场比赛是有联系的。「联系」具有**传递性**：**如果比赛 $\mathbf A$、$\mathbf B$ 有联系，比赛 $\mathbf B$、$\mathbf C$ 有联系，则比赛 $\mathbf A$、$\mathbf C$ 也有联系**。为了避免理解错误，在这举一个例子：

若仅有四场比赛：比赛一出现了 idea $1$、$2$；比赛二出现 idea $2$、$5$ ；比赛三出现 idea $3$、$5$、$8$，比赛四出现 idea $4$、$7$。则比赛一、二之间有**直接联系**。比赛一、三之间虽然没有公共 idea，但它们之间是**有联系**的。比赛四与其他所有比赛没有联系。  

而所有有联系的比赛都将属于同一个比赛集，没有联系的比赛处在不同的比赛集。

上例中比赛一、二、三属于一个比赛集，比赛四属于另一个。

求所有人**抽球卡片的次数和**的期望 $E_0$ 和比赛集的个数 $s$ 的期望 $E_1$。

---

**一句话题意：**

对于每个点 $i$ 随机与 $[1,n]$ 中的一点连无向边，若连向自己，则保留该边并再次连边，一直重复至连到别的点上为止，求边数与连通块个数期望。
## 输入格式

输入一行一个正整数 $n$。
## 输出格式

第一行输出一个数 $E_0$ ，第二行输出一个数 $E_1$ ，可以证明它们都是**有理数**。

为了避免精度误差，您只需要输出它们对质数 $998244353$ 取模的结果即可，如果您不会分数取模，您可以查找关于费马小定理与乘法逆元的相关资料。

如果输出格式错误或两问答案均错误，该测试点得 $0$ 分；

如果仅答对第一问，该测试点得 $3$ 分；

如果仅答对第二问，该测试点得 $7$ 分；

如果两问均正确，该测试点得 $10$ 分。

**请务必输出两个整数。**
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
4
1
```
### 样例输入 #2
```
7
```
### 样例输出 #2
```
166374067
539688692
```
## 提示

---

### 样例解释  

**样例解释一**

- 每个小朋友摸卡片次数为 $1$ 的概率为 $\dfrac{1}{2}$，摸卡片次数为 $2$ 的概率为 $\dfrac{1}{4}$，摸卡片次数为 $i$ 的期望次数为 $\dfrac{1}{2^i}$，期望摸卡片次数为 $2$，总摸卡片次数为 $4$。

- $1$ 号小朋友一定会和 $2$ 号小朋友交换 idea，所以他们出的比赛之间一定是属于同一个比赛集。$E_1=1$。

**样例解释二**

- 第一问取模前的答案为 $\dfrac{49}{6}$。

- 第二问取模前的答案为 $\dfrac{2245}{1944}$。

---

### 数据范围

| 测试点编号 | $n$ | 测试点编号 | $n$ | 
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leq 3$ | $5$ | $\leq 1000$ |
| $2$ | $\leq 5$ | $6$ | $\leq 2000$ | 
| $3$ | $\leq 9$ | $7\sim8$ | $\leq 5000$ | 
| $4$ | $\leq 12$ | $9\sim 10$ | $\leq10^4$ | 

对于 $100\%$ 的数据，有 $2\leq n\leq10^4$。

---



---

---
title: "「SWTR-7」IOI 2077"
layout: "post"
diff: 普及+/提高
pid: P7875
tag: ['数学', 'O2优化', '概率论', '期望', '洛谷月赛']
---
# 「SWTR-7」IOI 2077
## 题目背景

#### 友情提醒：本题输入输出量很大，请不要使用 cin 或 scanf。题目最下方附有快读及其使用方法。

#### 赛时提醒：若对于选出的 $m$ 无解，则期望值为 $0$。可以结合样例 2 的解释说明以更好理解。

#### 赛时提醒：你需要求的是能力值之和的期望而不是最大值。

---

小 A 被 FCC 钦定参加 IOI 2077！71 岁老将请求出战！
## 题目描述

IOI 2077 有 $n$ 位**候选**参赛者，他们分别编号为 $1\sim n$。每位候选参赛者都有一个能力值，且**能力值互不相等**，第 $i$ 位候选参赛者的能力值为 $a_i$。小 A 更喜欢有序的数字，所以他将这 $n$ 位候选参赛者按照能力值**从小到大**排好了序，即**满足 $a_i<a_{i+1}\ (1\leq i<n)$。**

正式参赛者将会从这 $n$ 位候选参赛者中产生。具体地，所有参赛者将是候选参赛者的一个子串 $[l,r]$，即编号为 $l,l+1,\cdots,r$ 的选手将参加 IOI 2077，其中，小 A 的编号为 $k$。因为他知道自己被钦定参加 IOI 2077，所以 $l\leq k\leq r$。可能的参赛者一共有 $q$ 种情况，每种情况用三个数 $l_i,r_i,k_i\ (l_i\leq k_i\leq r_i)$ 描述，即参赛者为编号在区间 $[l_i,r_i]$ 中的候选参赛者，而小 A 的编号为 $k_i$。

由于自己太菜，小 A 对即将到来的 IOI 感到力不从心。他决定选择一些参赛者作为队友，并与他们在赛场上相互帮（zuo）助（bi）。具体地，设正式参赛人数为 $s$，那么小 A 会在 $[0,\lfloor\frac{s-1}{2}\rfloor]$ 中**等概率随机**选择一个数 $m$，并从 $s$ 位参赛者中**随机**选出 $2m$ 个作为他的队友。不过，小 A 不希望自己显得太菜，所以**他的能力值 $a_k$ 必须是这 $2m+1$ 个人的能力值的中位数**。

俗话说，人多力量大，小 A 希望他与所有选出的队友的能力值之和尽量地大。**不过在此之前，他想知道这个值的期望值是多少**。请对 $998244353$ 取模，保证答案在该模数下有意义。**对于每一种可能的参赛者情况，你都需计算该情况下的答案。为了避免过大的输出，你只需要计算所有答案的异或和。**
## 输入格式

第一行一个整数 $t$，**表示该测试点 Subtask 编号。**  
第二行两个整数 $n,q$，分别表示候选参赛者个数和情况总数。  
第三行 $n$ 个整数 $a_1,a_2,\cdots,a_n$ 表示每个候选参赛者的能力值。**保证 $a_i$ 递增。**  
接下来 $q$ 行，每行三个整数 $l_i,r_i,k_i$ 描述一个可能的参赛者情况。
## 输出格式

输出一行一个整数，表示所有答案的异或和。
## 样例

### 样例输入 #1
```
0
5 2
2 3 5 7 8
1 5 3
2 4 2

```
### 样例输出 #1
```
499122189
```
## 提示

**「样例 1 说明」**

- 第 1 个询问：  
  因为 $s_1=r_1-l_1+1=5$，所以 $m$ 可以为 $0,1$ 或 $2$。  
  $m=0$ 时：小 A 没有队友，那么期望值就是他自身的能力值 $a_{k_1}=a_3=5$。    
  $m=1$ 时：小 A 可以选**编号** $(1, 4)$ 或 $(1, 5)$ 或 $(2, 4)$ 或 $(2, 5)$ 的参赛者作为他的队友，能力值之和分别为 $14,15,15,16$，期望值为 $\frac{14+15+15+16}{4}=15$。    
  $m=2$ 时：小 A 只能全选，期望值为 $2+3+5+7+8=25$。  
	综上，期望值为 $\frac{5+15+25}{3}=15$。

- 第 2 个询问：  
  因为 $s_2=r_2-l_2+1=3$，所以 $m$ 可以为 $0$ 或 $1$。  
  $m=0$ 时，小 A 没有队友，期望值为 $3$。    
  $m=1$ 时，小 A 无法选择，期望值为 $0$。  
  综上，期望值为 $\frac{3+0}{2}=\frac{3}{2}$，对 $998244353$ 取模后为 $499122178$。
  
$15\oplus499122178=499122189$。

**「数据范围与约定」**

**本题采用捆绑测试。**

记 $s_i=r_i-l_i+1$。

- Subtask #0（1 point）：是样例。
- Subtask #1（10 points）：$s_i\leq 2$。
- Subtask #2（20 points）：$s_i\leq 16$，$q\leq 40$，$n\leq 640$。
- Subtask #3（15 points）：$s_i,q\leq 500$，$n\leq 10^5$。
- Subtask #4（15 points）：$s_i,q\leq 3\times 10^3$，$n\leq 10^5$。
- Subtask #5（15 points）：$s_i,q\leq 2\times 10^5$，$n\leq 5\times 10^5$。
- Subtask #6（24 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,q\leq 2\times 10^6$，$1\leq l_i\leq k_i\leq r_i\leq n$，$1 \le a_i \le 998244352$，$a_i<a_{i+1}\ (1\leq i<n)$。

对于所有测试点，时间限制 1s，空间限制 512MB。

**「帮助/提示」**

关于 [有理数取余](https://www.luogu.com.cn/problem/P2613)，[中位数](https://baike.baidu.com/item/%E4%B8%AD%E4%BD%8D%E6%95%B0/3087401?fr=aladdin)。

本题输入输出量**极大**，**请注意 I/O 优化。**  
本题提供**有符号 32 位整数**快读模板，保证读入用时不超过 250ms：

```cpp
#define gc getchar()
inline int read(){
	int x=0; bool sgn=0; char s=gc;
	while(!isdigit(s))sgn|=s=='-',s=gc;
	while(isdigit(s))x=(x<<1)+(x<<3)+(s-'0'),s=gc;
	return sgn?-x:x;
}

// 如果需要读入直接调用 read() 即可。
// 一个例子（与正解无关，仅供参考）：

int t=read(),n=read(),q=read();
int a[2000005],l[2000005],r[2000005],k[2000005];
for(int i=1;i<=n;i++)a[i]=read();
for(int i=1;i<=q;i++)l[i]=read(),r[i]=read(),k[i]=read();

// 这样你就可以在 250ms 内读入全部数据了。
```

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) C。  
idea & solution：[SSerWarriors_Cat](https://www.luogu.com.cn/user/147999)；data：[Alex_Wei](https://www.luogu.com.cn/user/123294) ；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。

---

IOI 2077 落下帷幕，小 A 凭借出（dui）色（you）的发（bang）挥（zhu）成功 AK 了 IOI，这不禁让他回想起曾经满腔热血的自己，以及和他共同奋斗在 OI 路上的战友们。如今他们虽已天各一方，说起来也有十几年没见过面了，但他们真挚的友谊未曾淡去，也将永远不会褪色。

>*“爷爷，您手机里有段录音，还写着 'ycx txdy!'。”*  
>*“哦，是嘛？放出来听听。”*  
>>*“I AK IOI. I AK ACM World Final. I AK Universe OI. I think all of you are vegetable chickens.”*  
>>*“I AK IOI. I AK ACM World Final. I AK Universe OI. I think all of you are vegetable chickens.”*  
>>*“I AK IOI. I AK ACM World Final. I AK Universe OI. I think all of you ............”*

2077.7.7


---

---
title: "[蓝桥杯 2022 省 A] 爬树的甲壳虫"
layout: "post"
diff: 普及+/提高
pid: P8774
tag: ['动态规划 DP', '2022', '期望', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 A] 爬树的甲壳虫
## 题目描述

有一只甲壳虫想要爬上一颗高度为 $n$ 的树，它一开始位于树根, 高度为 $0$，当它尝试从高度 $i-1$ 爬到高度为 $i$ 的位置时有 $P_{i}$ 的概率会掉回树根, 求它从树根爬到树顶时, 经过的时间的期望值是多少。

## 输入格式

输入第一行包含一个整数 $n$ 表示树的高度。

接下来 $n$ 行每行包含两个整数 $x_{i}, y_{i}$, 用一个空格分隔，表示 $P_{i}=\frac{x_{i}}{y_{i}}$ 。

## 输出格式

输出一行包含一个整数表示答案，答案是一个有理数，请输出答案对质数 $998244353$ 取模的结果。其中有理数 $\frac{a}{b}$ 对质数 $P$ 取模的结果是整数 $c$ 满足 $0 \leq c<P$ 且 $c \cdot b \equiv a\pmod P$ 。

## 样例

### 样例输入 #1
```
1
1 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3
1 2
3 5
7 11
```
### 样例输出 #2
```
623902744
```
## 提示

对于 $20 \%$ 的评测用例, $n \leq 2,1 \leq x_{i}<y_{i} \leq 20$;

对于 $50 \%$ 的评测用例, $n \leq 500,1 \leq x_{i}<y_{i} \leq 200$;

对于所有评测用例, $1 \leq n \leq 10^5,1 \leq x_{i}<y_{i} \leq 10^{9}$ 。 

蓝桥杯 2022 省赛 A 组 E 题。


---

---
title: "[蓝桥杯 2023 国 B] 逃跑"
layout: "post"
diff: 普及+/提高
pid: P9428
tag: ['2023', '期望', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 B] 逃跑
## 题目描述

小明所在星系有 $n$ 颗星球，编号为 $1$ 到 $n$。这些星球通过 $n-1$ 条无向边连成一棵树。根结点为编号为 $1$ 的星球。

为了在星际战争到来时逃到其他星系，小明在根结点设置了逃离用的传送门。每个星球的人只需要一直往父结点星球移动就可以抵达根结点。为了方便各个星球的人去往根结点，小明将其中 $m$ 个星球设置为了跳板星球。在从某个星球去往根结点的路径上，当一个人经过任意星球（包括起点星球）时，他可以尝试直接跳跃到 **其前往根结点路径上的除当前星球以外的第一个跳板星球**，其时间花费和走到父结点星球的时间花费相同，都是 $1$ 单位时间。

然而，因为技术问题，向跳板星球的跳跃并不一定成功，每一次跳跃都有 $p$ 的概率失败，并转而跳跃到当前星球的父结点星球（相当于直接走到父结点星球）；同时此跳板星球失效，将 **不再视为跳板星球**。

为了衡量移动效率，小明想知道，如果一个人在这 $n$ 颗星球中随机选择一颗出发前往根结点，其花费的最短时间的期望是多少单位时间？
## 输入格式

输入共 $n + 1$ 行，第一行为两个正整数 $n$、$m$ 和一个浮点数 $p$。

后面 $n - 1$ 行，每行两个正整数 $x_i,y_i$ 表示第 $i$ 条边的两个端点。

最后一行，共 $m$ 个正整数表示所有跳板星球的编号。
## 输出格式

一行，一个浮点数，表示答案（请保留两位小数）。
## 样例

### 样例输入 #1
```
4 1 0.2
1 2
2 3
3 4
2
```
### 样例输出 #1
```
1.30
```
## 提示

### 样例说明

从 $1$ 号星球出发的时间花费为 $0$；  
从 $2$ 号星球出发的时间花费为 $1$；  
从 $3$ 号星球出发的时间花费为 $2$；  
从 $4$ 号星球出发的时间花费为 $0.8 \times 2 + 0.2 \times 3 = 2.2$。

所以期望时间为 $\dfrac{0+1+2+2.2}{4}=1.3$。

### 评测用例规模与约定

 - 对于 $30\%$ 的数据，保证 $1 \le n \le 2000$。
 - 对于 $100\%$ 的数据，保证 $1 \le n \le 10^6$，$1 \le m \le n$，$0 < p < 1$。
 
 第十四届蓝桥杯大赛软件赛决赛 C/C++ 大学 B 组 J 题


---

