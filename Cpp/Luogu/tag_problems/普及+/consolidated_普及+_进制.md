---
title: "[NOIP 1998 提高组] 进制位"
layout: "post"
diff: 普及+/提高
pid: P1013
tag: ['搜索', '1998', 'NOIP 提高组', '枚举', '进制']
---
# [NOIP 1998 提高组] 进制位
## 题目描述

著名科学家卢斯为了检查学生对进位制的理解，他给出了如下的一张加法表，表中的字母代表数字。 例如：

$$
\def\arraystretch{2}
\begin{array}{c||c|c|c|c}
\rm +  & \kern{.5cm} \rm \mathclap{L} \kern{.5cm}  &  \kern{.5cm} \rm \mathclap{K} \kern{.5cm} &  \kern{.5cm} \rm \mathclap{V} \kern{.5cm} & \kern{.5cm} \rm \mathclap{E} \kern{.5cm} \\ \hline\hline
\rm L  &  \rm L  &  \rm K  &  \rm V  & \rm E  \\ \hline
\rm K  &  \rm K  &  \rm V  &  \rm E  & \rm \mathclap{KL} \\ \hline
\rm V  &  \rm V  &  \rm E  &  \rm \mathclap{KL} & \rm \mathclap{KK} \\ \hline
\rm E  &  \rm E  &  \rm \mathclap{KL} &  \rm \mathclap{KK} & \rm \mathclap{KV} \\
\end{array}$$

其含义为：

$L+L=L$，$L+K=K$，$L+V=V$，$L+E=E$

$K+L=K$，$K+K=V$，$K+V=E$，$K+E=KL$    

$\cdots$

$E+E=KV$    

根据这些规则可推导出：$L=0$，$K=1$，$V=2$，$E=3$。

同时可以确定该表表示的是 $4$ 进制加法。
## 输入格式

第一行一个整数 $n$（$3\le n\le9$）表示行数。

以下 $n$ 行，每行包括 $n$ 个字符串，每个字符串间用空格隔开。）

若记 $s_{i,j}$ 表示第 $i$ 行第 $j$ 个字符串，数据保证 $s_{1,1}=\texttt +$，$s_{i,1}=s_{1,i}$，$|s_{i,1}|=1$，$s_{i,1}\ne s_{j,1}$ （$i\ne j$）。

保证至多有一组解。
## 输出格式

第一行输出各个字母表示什么数，格式如：`L=0 K=1` $\cdots$ 按给出的字母顺序排序。不同字母必须代表不同数字。

第二行输出加法运算是几进制的。

若不可能组成加法表，则应输出 `ERROR!`。
## 样例

### 样例输入 #1
```
5
+ L K V E
L L K V E
K K V E KL
V V E KL KK
E E KL KK KV

```
### 样例输出 #1
```
L=0 K=1 V=2 E=3
4

```
## 提示

NOIP1998 提高组 第三题


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
title: "[IOI 1994] 时钟 The Clocks"
layout: "post"
diff: 普及+/提高
pid: P1213
tag: ['搜索', '2001', 'USACO', 'IOI', '剪枝', '进制']
---
# [IOI 1994] 时钟 The Clocks
## 题目描述

考虑将如此安排在一个 $3 \times 3$ 行列中的九个时钟:

```plain
|-------|   |-------|   |-------|
|       |   |       |   |   |   |
|---o   |   |---o   |   |   o   |
|       |   |       |   |       |
|-------|   |-------|   |-------|
    A           B           C

|-------|   |-------|   |-------|
|       |   |       |   |       |
|   o   |   |   o   |   |   o   |
|   |   |   |   |   |   |   |   |
|-------|   |-------|   |-------|
    D           E           F

|-------|   |-------|   |-------|
|       |   |       |   |       |
|   o   |   |   o---|   |   o   |
|   |   |   |       |   |   |   |
|-------|   |-------|   |-------|
    G           H           I
```

目标要找一个最小的移动顺序将所有的指针指向 $12$ 点。下面原表格列出了 $9$ 种不同的旋转指针的方法，每一种方法都叫一次移动。  
选择 $1 \sim 9$ 号移动方法，将会使在表格中对应的时钟的指针顺时针旋转 
 $90$ 度。


|移动方法  | 受影响的时钟 |
| :----------: | :----------: |
| 1 | ABDE |
| 2 | ABC |
| 3 | BCEF |
| 4 | ADG |
| 5 | BDEFH |
| 6 | CFI |
| 7 | DEGH |
| 8 | GHI |
| 9 | EFHI |

例子：

```plain
9 9 12       9 12 12        9 12 12        12 12 12        12 12 12
6 6 6   5 -> 9  9  9   8 -> 9  9  9   4 -> 12  9  9   9 -> 12 12 12
6 3 6        6  6  6        9  9  9        12  9  9        12 12 12
```

**但这可能不是正确的方法，请看下文。**

## 输入格式

输入三行，每行三个正整数，表示一个时钟的初始时间，数字的含意和上面第一个例子一样。

## 输出格式

单独的一行包括一个用空格分开的将所有指针指向 $12$ 点的最短移动顺序的列表。

如果有多种方案，输出那种使其连接起来的数字最小的方案。（举例来说 $5\ 2\ 4\ 6 < 9\ 3\ 1\ 1$）。

## 样例

### 样例输入 #1
```
9 9 12
6 6 6
6 3 6 

```
### 样例输出 #1
```
4 5 8 9

```
## 提示

题目翻译来自NOCOW。

USACO Training Section 1.4



---

---
title: "[蓝桥杯 2025 省研究生组] 01 串"
layout: "post"
diff: 普及+/提高
pid: P12191
tag: ['数学', '2025', '进制', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省研究生组] 01 串
## 题目描述

给定一个由 $0, 1, 2, 3 \dots$ 的二进制表示拼接而成的长度无限的 $01$ 串。其前若干位形如 $011011100101110111\dots$。

请求出这个串的前 $x$ 位里有多少个 $1$。
## 输入格式

输入的第一行包含一个正整数 $x$。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
7
```
### 样例输出 #1
```
5
```
## 提示

### 样例说明

给定的串的前 $7$ 位为 $0110111$。

### 评测用例规模与约定

- 对于 $60\%$ 的评测用例，$x \leq 10^6$；
- 对于所有评测用例，$1 \leq x \leq 10^{18}$。


---

---
title: "[GCJ 2019 #1B] Draupnir"
layout: "post"
diff: 普及+/提高
pid: P13110
tag: ['2019', '交互题', 'Special Judge', '进制', '位运算', 'Google Code Jam']
---
# [GCJ 2019 #1B] Draupnir
## 题目描述

Odin has some magical rings which produce copies of themselves. Each "X-day ring" produces one more X-day ring every X days after the day it came into existence. These rings come in six possible varieties: 1-day, 2-day, ..., all the way up to 6-day.

For example, a 3-day ring that came into existence on day 0 would do nothing until day 3, when it would produce another 3-day ring. Then, on day 6, each of those two rings would produce another 3-day ring, and so on.

You know that Odin had no rings before day 0. On day 0, some rings came into existence. At the end of day 0, Odin had $R_i$ i-day rings, for each $1 \leqslant i \leqslant 6$. You know that $0 \leqslant R_i \leqslant 100$, for all $i$, and at least one of the $R_i$ values is positive.

Fortunately, you also have access to the secret well of knowledge. Each time you use it, you can find out the total number of rings that Odin had at the end of a particular day between day 1 and day 500, inclusive. The well will give you the answer modulo $2^{63}$, because even it can only hold so much information! Moreover, you can only use the well up to W times.

Your goal is to determine how many rings of each type Odin had at the end of day 0 — that is, you must find each of the $R_i$ values.

### Interactive Protocol

This is an interactive problem.

Initially, your program should read a single line containing two integers $\mathbf{T}$, the number of test cases, and $\mathbf{W}$, the number of times you are allowed to use the well of knowledge per test case. Then, you need to process $\mathbf{T}$ test cases.

In each test case, your program processes up to $\mathbf{W} + 1$ exchanges with our judge. You may make up to $\mathbf{W}$ exchanges of the following form:

* Your program outputs one line with a single integer $\mathbf{D}$ between 1 and 500, inclusive.
* The judge responds with one line with a single integer: the total number of rings that Odin had at the end of day $\mathbf{D}$, modulo $2^{63}$. If you send invalid data (e.g., a number out of range, or a malformed line), the judge instead responds with -1.

After between 0 and $\mathbf{W}$ exchanges as explained above, you must perform one more exchange of the following form:

* Your program outputs one line with six integers $\mathbf{R}_1$, $\mathbf{R}_2$, $\mathbf{R}_3$, $\mathbf{R}_4$, $\mathbf{R}_5$, $\mathbf{R}_6$, where $\mathbf{R}_i$ represents the number of i-day rings that Odin had at the end of day 0.
* The judge responds with one line with a single integer: 1 if your answer is correct, and -1 if it is not (or you have provided a malformed line).

After the judge sends -1 to your input stream (because of either invalid data or an incorrect answer), it will not send any other output. If your program continues to wait for the judge after receiving -1, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```

```
### 样例输出 #1
```

```
## 提示

**Sample Interaction**

This interaction corresponds to Test set 1. Suppose that, unbeknownst to us, the judge has decided that Odin had one ring of each of the six types at the end of day 0.

```
  t, w = readline_int_list()   // Reads 50 into t and 6 into w
  printline 3 to stdout        // Asks about day 3.
  flush stdout
  n = readline_int()           // Reads 15 into n.
  printline 1 to stdout        // Asks about day 1.
  flush stdout
  n = readline_int()           // Reads 7 into n.
  printline 1 1 1 3 0 0 to stdout
  flush stdout                 // We make a guess even though we could have
                               // queried the well up to four more times.
  verdict = readline_int()     // Reads -1 into verdict (judge has decided our
                               //   solution is incorrect)
  exit                         // Exits to avoid an ambiguous TLE error
```

Notice that even though the guess was consistent with the information we received from the judge, we were still wrong because we did not find the correct values.

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our [interactive runner](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py) for that. For more information, read the instructions in comments in that file.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

- $1 \leq T \leq 50$.

**Test set 1 (10 Pts, Visible)**

- $W = 6$.

**Test set 2 (21 Pts, Hidden)**

- $W = 2$.


---

---
title: "宝物筛选"
layout: "post"
diff: 普及+/提高
pid: P1776
tag: ['动态规划 DP', '单调队列', 'NOI 导刊', '背包 DP', '进制']
---
# 宝物筛选
## 题目描述

终于，破解了千年的难题。小 FF 找到了王室的宝物室，里面堆满了无数价值连城的宝物。

这下小 FF 可发财了，嘎嘎。但是这里的宝物实在是太多了，小 FF 的采集车似乎装不下那么多宝物。看来小 FF 只能含泪舍弃其中的一部分宝物了。

小 FF 对洞穴里的宝物进行了整理，他发现每样宝物都有一件或者多件。他粗略估算了下每样宝物的价值，之后开始了宝物筛选工作：小 FF 有一个最大载重为 $W$ 的采集车，洞穴里总共有 $n$ 种宝物，每种宝物的价值为 $v_i$，重量为 $w_i$，每种宝物有 $m_i$ 件。小 FF 希望在采集车不超载的前提下，选择一些宝物装进采集车，使得它们的价值和最大。
## 输入格式

第一行为一个整数 $n$ 和 $W$，分别表示宝物种数和采集车的最大载重。

接下来 $n$ 行每行三个整数 $v_i,w_i,m_i$。
## 输出格式

输出仅一个整数，表示在采集车不超载的情况下收集的宝物的最大价值。
## 样例

### 样例输入 #1
```
4 20
3 9 3
5 9 1
9 4 2
8 1 3
```
### 样例输出 #1
```
47
```
## 提示

对于 $30\%$ 的数据，$n\leq \sum m_i\leq 10^4$，$0\le W\leq 10^3$。

对于 $100\%$ 的数据，$n\leq \sum m_i \leq 10^5$，$0\le W\leq 4\times 10^4$，$1\leq n\le 100$。


---

---
title: "[HNOI2006] 鬼谷子的钱袋"
layout: "post"
diff: 普及+/提高
pid: P2320
tag: ['2006', '各省省选', '湖南', 'Special Judge', '进制']
---
# [HNOI2006] 鬼谷子的钱袋
## 题目描述

鬼谷子非常聪明，正因为这样，他非常繁忙，经常有各诸侯的特派员前来向他咨询时政。

有一天，他在咸阳游历的时候，朋友告诉他在咸阳最大的拍卖行（聚宝商行）将要举行一场拍卖会，其中有一件宝物引起了他极大的兴趣，那就是无字天书。

但是，他的行程安排得很满，他已经买好了去邯郸的长途马车票，不巧的是出发时间是在拍卖会快要结束的时候。于是，他决定事先做好准备，将自己的金币数好并用一个个的小钱袋装好，以便在他现有金币的支付能力下，任何数目的金币他都能用这些封闭好的小钱的组合来付账。

鬼谷子也是一个非常节俭的人，他想方设法使自己在满足上述要求的前提下，所用的钱袋数最少，并且不有两个钱袋装有相同的大于 $1$ 的金币数。假设他有 $m$ 个金币，你能猜到他会用多少个钱袋，并且每个钱袋装多少个金币吗？
## 输入格式

包含一个整数，表示鬼谷子现有的总的金币数目 $m$。其中，$1 \le m \le {10}^9$。
## 输出格式

两行，第一行一个整数 $h$，表示所用钱袋个数。

第二行表示每个钱袋所装的金币个数，由小到大输出，空格隔开。
## 样例

### 样例输入 #1
```
3

```
### 样例输出 #1
```
2
1 2

```


---

---
title: "正妹吃月饼"
layout: "post"
diff: 普及+/提高
pid: P2431
tag: ['数学', '贪心', '洛谷原创', '进制']
---
# 正妹吃月饼
## 题目描述

今天是中秋节。uim 带来了一堆大小不同且味道各异的月饼。

这些月饼的质量分别是 $1g,2g,4g,8g,16g$....后面一个是前面的 $2$ 倍。每种只有一个。

uim 让正妹随便吃。

正妹希望尝试尽可能多的口味，所以会吃尽可能多数量的月饼（不是重量）。而且她的确有些饿了，至少总共要吃掉 $A\text{g}$ 的月饼才能满足。

然而正妹怕长胖，所以吃月饼不能合计超过 $B\text{g}$ 。

她希望知道自己最多能吃多少个月饼

## 输入格式

共一行，包含两个数，$A,B$。

## 输出格式

正妹能吃到最多的数量。
## 样例

### 样例输入 #1
```
16 25
```
### 样例输出 #1
```
4
```
## 提示

**样例解释**：

正妹可以吃 $1,2,4,16$ 这 $4$ 个月饼（吃法可能不唯一）。

**数据范围**：

对于 $30\%$ 数据，$1\le A,B \le 1000$；

对于 $60\%$ 数据，$1 \le A,B \le 100000$；

对于 $100\%$ 数据，$1 \le A,B \le 2^{63}-1$。



---

---
title: "[USACO08DEC] Secret Message G"
layout: "post"
diff: 普及+/提高
pid: P2922
tag: ['2008', 'USACO', '进制', '字典树 Trie']
---
# [USACO08DEC] Secret Message G
## 题目描述

Bessie is leading the cows in an attempt to escape! To do this, the cows are sending secret binary messages to each other.

Ever the clever counterspy, Farmer John has intercepted the first $b_i$ ($1 \le b_i \le 10,000$) bits of each of $M$ ($1 \le M \le 50,000$) of these secret binary messages.

He has compiled a list of $N$ ($1 \le N \le 50,000$) partial codewords that he thinks the cows are using. Sadly, he only knows the first $c_j$ ($1 \le c_j \le 10,000$) bits of codeword $j$.

For each codeword $j$, he wants to know how many of the intercepted messages match that codeword (i.e., for codeword $j$, how many times does a message and the codeword have the same initial bits). Your job is to compute this number.

The total number of bits in the input (i.e., the sum of the $b_i$ and the $c_j$) will not exceed  $500,000$.

贝茜正在领导奶牛们逃跑．为了联络，奶牛们互相发送秘密信息．

信息是二进制的，共有 $M$（$1 \le M \le 50000$）条，反间谍能力很强的约翰已经部分拦截了这些信息，知道了第  $i$ 条二进制信息的前 $b_i$（$1 \le b_i \le 10000$）位，他同时知道，奶牛使用 $N$（$1 \le N \le 50000$）条暗号．但是，他仅仅知道第 $j$ 条暗号的前 $c_j$（$1 \le c_j \le 10000$）位。

对于每条暗号 $j$，他想知道有多少截得的信息能够和它匹配。也就是说，有多少信息和这条暗号有着相同的前缀。当然，这个前缀长度必须等于暗号和那条信息长度的较小者。

在输入文件中，位的总数（即 $\sum b_i + \sum c_i$）不会超过 $500000$。
## 输入格式

Line $1$: Two integers: $M$ and $N$.

Lines $2 \ldots M+1$: Line $i+1$ describes intercepted code $i$ with an integer $b_i$ followed by $b_i$ space-separated `0`'s and `1`'s.

Lines $M+2 \ldots M+N+1$: Line $M+j+1$ describes codeword $j$ with an integer $c_j$ followed by $c_j$ space-separated `0`'s and `1`'s.
## 输出格式

Lines $1 \ldots N$: Line $j$: The number of messages that the $j$-th codeword could match.
## 样例

### 样例输入 #1
```
4 5 
3 0 1 0 
1 1 
3 1 0 0 
3 1 1 0 
1 0 
1 1 
2 0 1 
5 0 1 0 0 1 
2 1 1 

```
### 样例输出 #1
```
1 
3 
1 
1 
2 

```
## 提示

Four messages; five codewords. 

The intercepted messages start with 010, 1, 100, and 110.

The possible codewords start with 0, 1, 01, 01001, and 11.


0 matches only 010: 1 match

1 matches 1, 100, and 110: 3 matches

01 matches only 010: 1 match

01001 matches 010: 1 match

11 matches 1 and 110: 2 matches



---

---
title: "数列找不同"
layout: "post"
diff: 普及+/提高
pid: P3901
tag: ['模拟', '莫队', '排序', '进制']
---
# 数列找不同
## 题目描述

现有数列 $A_1,A_2,\ldots,A_N$，$Q$ 个询问 $(L_i,R_i)$，询问 $A_{L_i} ,A_{L_i+1},\ldots,A_{R_i}$ 是否互不相同。

## 输入格式

第一行，两个整数$N,Q$。  
第二行，$N$ 个整数$A_1, A_2, \ldots , A_N$。  
接下来 $Q$ 行，每行两个整数 $L_i,R_i$。
## 输出格式

对每个询问输出一行，`Yes` 或 `No`。

## 样例

### 样例输入 #1
```
4 2
1 2 3 2
1 3
2 4
```
### 样例输出 #1
```
Yes
No
```
## 提示

对于 $50\%$ 的数据，$N,Q  \le 10^3$。  
对于 $100\%$ 的数据，$1 \le N,Q \le 10^5$，$1 \le A_i \le N$，$1 \le L_i \le R_i \le N$。


---

---
title: "异或序列"
layout: "post"
diff: 普及+/提高
pid: P3917
tag: ['数学', '枚举', '进制']
---
# 异或序列
## 题目描述

给出序列 $A_1,A_2,\cdots,A_N$，求

$$\sum_{1\le i\le j\le N} A_i\oplus A_{i+1}\oplus\cdots\oplus A_j$$

的值。其中，$\bigoplus$ 表示按位异或。

## 输入格式

第一行，一个整数 $N$。

第二行，$N$个整数 $A_1,A_2,\cdots,A_N$。

## 输出格式

一个数，为表达式的值。
## 样例

### 样例输入 #1
```
2
1 2
```
### 样例输出 #1
```
6
```
## 提示

- 对于 $60\%$ 的数据，$1 \le N \le 10^3$；
- 对于 $100\%$ 的数据，$1 \le N \le 10^5$，$0 \le A_i \le 10^9$。



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
title: "不开心的金明"
layout: "post"
diff: 普及+/提高
pid: P3985
tag: ['模拟', '排序', '背包 DP', '进制', '洛谷月赛']
---
# 不开心的金明
## 题目描述

金明今天很不开心，家里购置的二手房就要领钥匙了，房里并没有一间他自己专用的很宽敞的房间。更让他不高兴的是，妈妈昨天对他说：“你需要购买哪些物品，怎么布置，你说了不算（有很大的限制），而且不超过 $W$ 元钱。”。今天一早金明就开始做预算，但是他想买的东西太多了，肯定会超过妈妈限定的 $W$ 元。于是，他把每件物品规定了一个重要度整数 $p_i$ 表示。他还从因特网上查到了每件物品的价格 $v_i$（都是整数元）。

妈妈看到购物单后进行了审查，要求购物单上所有的物品价格的极差（最贵的减去最便宜的）不超过 $3$（当然金明至今不知道为什么会这样）。他希望在不超过 $W$ 元（可以等于 $W$ 元）的前提下，使购买的重要度总和 $\sum p_i$ 的最大。


请你帮助金明设计一个满足要求的购物单，你只需要告诉我们重要度的最大的和。

## 输入格式

输入的第 $1$ 行，为两个正整数，用一个空格隔开：

$n,W$（其中 $W$ 表示总钱数，$n$ 为希望购买物品的个数。）

从第 $2$ 行到第 $n+1$ 行，第 $j$ 行给出了编号为 $j-1$ 的物品的基本数据，每行有 $2$ 个非负整数 $v_p$（其中 $v$ 表示该物品的价格，$p$ 表示该物品的重要度）
## 输出格式

输出只有一个正整数，为不超过总钱数的物品的重要度的总和的最大值。
## 样例

### 样例输入 #1
```
5 10
2 800
5 400
5 300
3 400
2 200

```
### 样例输出 #1
```
1600
```
## 提示

$1 \le N \le 100$。

$1 \le W \le 10^9$。

$1 \le v_i \le 10^9$。

对所有的 $i=1,2,3,…,N$，$\min(v_i) \le v_i \le \min(v_i)+3$。

$1 \le p_i \le 10^7$。



---

---
title: "大河的序列"
layout: "post"
diff: 普及+/提高
pid: P4144
tag: ['贪心', '进制', '位运算']
---
# 大河的序列
## 题目背景

“唯有龙虎相伴 最是脉脉深情”


题目来源：[KingSann](https://www.luogu.org/space/show?uid=47111)

## 题目描述

大河有一些袜子，但经常十分散乱的堆放着。


有一天龙儿忍不住了，于是将袜子放到了一个序列上（称作袜子序列）。


每个袜子都有一个$dirty$值，定义袜子序列的$dirty$值为 $ \max  \left( (dirty_{l} \ bitand \ dirty_{l+1} \ bitand \ \cdots \ bitand \ dirty_{r}) + (dirty_{l} \ bitor \ dirty_{l+1} \ bitor \ \cdots \ bitor \ dirty_{r}) \right) $ ，其中 $ dirty_{i} $ 表示 第 $ i $ 只袜子 的 $ dirty $ 值，$bitand$表示按位与（C++中是`&`），$bitor$表示按位或（C++中是`|`）。


简而言之，就是找一段连续子序列，使得所有数字的按位与加上按位或最大。


如果这个袜子序列的$dirty$值达到了某个**阈**值，那么龙儿会讨厌大河的。


大河当然不希望这样了，于是她想知道这个袜子序列的$dirty$值是多少。

## 输入格式

第一行三个整数 $ n,b,p $ ，分别表示数列长度和输出相关的东西


第二行有 $ n $ 个整数，表示这个数列的初始数值

## 输出格式

设答案为 $ x $ ，你需要输出 $ (x+233)^{b} \,\, \text{mod} \,\,p $

## 样例

### 样例输入 #1
```
10 1 10000000
7 9 9 4 0 0 8 8 4 7
```
### 样例输出 #1
```
251
```
## 提示

$ 1 \le n, p \le 10^{5} $


$ 0 \le b, ditry_{i} \le 10^{7} $


对于测试点 $ 1 $ 和测试点 $ 2 $ 的数据，保证 $ 1 \le n \le 100 $



---

---
title: "绝世好题"
layout: "post"
diff: 普及+/提高
pid: P4310
tag: ['枚举', '进制', '位运算']
---
# 绝世好题
## 题目描述

给定一个长度为 $n$ 的数列 $a_i$，求 $a_i$ 的子序列 $b_i$ 的最长长度 $k$，满足 $b_i \& b_{i-1} \ne 0 $，其中 $2\leq i\leq k$， $\&$ 表示位运算取与。
## 输入格式

输入文件共 2 行。
第一行包括一个整数 $n$。
第二行包括 $n$ 个整数，第 $i$ 个整数表示 $a_i$。
## 输出格式

输出文件共一行。
包括一个整数，表示子序列 $b_i$ 的最长长度。
## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
2
```
## 提示

对于100%的数据，$1\leq n\leq 100000$，$a_i\leq 10^9$。


---

---
title: "浏览器"
layout: "post"
diff: 普及+/提高
pid: P4932
tag: ['O2优化', '进制', '位运算', '洛谷月赛']
---
# 浏览器
## 题目背景

\_\_stdcall在用Edge玩slay的时候，鼠标会经常失灵，这让她十分痛苦，因此她决定也要让你们感受一下Edge制造的痛苦。
## 题目描述

\_\_stdcall给了你n个点，第i个点有权值x[i]，对于两个点u和v，如果x[u] xor x[v]的结果在二进制表示下有奇数个1，那么在u和v之间连接一个Edge，现在\_\_stdcall想让你求出一共有多少个Edge。

如果你没能成功完成任务，那么\_\_stdcall会让你痛苦一下，你这个测试点就没分了。
## 输入格式

一行六个整数，n，a，b，c，d，x[0]。

n是点的个数，每个点的权值需要用如下的方式生成。

你需要使用a，b，c，d和x[0]生成一个数组x，生成方式是这样的。

$x_i = (ax_{i-1}^2 + bx_{i-1} + c) \mod d$

x[i]就是第i个点的权值，点的标号是1到n。
## 输出格式

输出一个整数，表示一共有多少个Edge。
## 样例

### 样例输入 #1
```
8 98 24 20 100 44

```
### 样例输出 #1
```
12

```
### 样例输入 #2
```
1000 952537 601907 686180 1000000 673601

```
### 样例输出 #2
```
249711

```
## 提示

我们用v表示权值中的最大值。

对于前20%的数据，n<=10。

对于前40%的数据，n<=100。

对于前60%的数据，n<=1000。

对于前80%的数据，n<=1e6。

对于前90%的数据，v<=1e6。

对于100%的数据，n<=1e7，v<=1e9。

保证a，b，c，d，x[0]都是int内的非负整数。


---

---
title: "「Wdsr-1」小铃的书"
layout: "post"
diff: 普及+/提高
pid: P6306
tag: ['2020', '哈希 hashing', '进制']
---
# 「Wdsr-1」小铃的书
## 题目背景

本居小铃在人间之里经营着一家名为“铃奈庵”的书店。店里井井有条地堆放着很多很多书。  

一天，魔理沙来铃奈庵借书，搞得店里十分混乱，魔理沙随身携带的魔导书与铃奈庵的书籍全都混在了一起。
## 题目描述

小铃一共有 $n-1$ 本书，每本书有一个编号 $a_i$，两本书属于同一种类当且仅当两本书的编号相同。  

由于小铃平时将这些书整理得井井有条，因此在小铃的 $n-1$ 本书中，每个种类的书的数量都恰好是 $k$ 的倍数，其中 $k$ 是一给出的常数。
 
现在，魔理沙的一本编号未知的魔导书与小铃的 $n-1$ 本书混在了一起，而魔理沙只有知道魔导书的编号才能将其找回。  

由于书的数量实在太多，魔理沙找到了你来帮忙，希望聪明的你能帮她求出混入的魔导书的编号。

**注意：魔理沙的魔导书可能与小铃的某本书有着相同的编号。**
## 输入格式

第一行是两个整数 $n,k$，含义与题目描述一致。

保证 $n\equiv 1 \pmod k$ 。

第二行共 $n$ 个整数，表示混在一起的 $n$ 本书的编号 $a_i$ 。
## 输出格式

共一行一个整数，表示魔理沙的魔导书的编号。
## 样例

### 样例输入 #1
```
10 3
1 1 2 2 3 5 3 2 1 3
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
13 4
1 1 4 5 1 4 1 4 4 5 5 5 1
```
### 样例输出 #2
```
1
```
## 提示

#### 样例说明

样例 $1$ 中，小铃的书的编号为 $1,2,3$，分别有 $3$ 本。因此魔导书的编号为 $5$。

样例 $2$ 中，小铃的书的编号为 $1,4,5$，分别有 $4$ 本。因此魔导书的编号为 $1$。

------------------------

#### 数据范围及约定

**本题采取捆绑测试。**

$$
\def{\arraystretch}{1.5}
\def\cuteran{https://www.luogu.com.cn/paste/iyzwht7l}
\begin{array}{|c|c|c|}\hline
\textbf{Subtask} & \bm{n\le} & \textbf{分值} \cr\hline
1 & 10^5 & 50 \cr\hline
2 & 10^6 & 25 \cr\hline
3 & 10^7 & 25 \cr\hline
\end{array}
$$

对于全部数据，保证 $1 \le n \le 10^7$  ，$2 \le k \le 10^3$  ，$1 \le a_i \le 10^{18}$。保证数据合法，即有且只有一本混入的魔导书。   

-----------------

#### 提示

**请注意时空限制。**

**使用 $\texttt{cin}$ / $\texttt{cout}$ 可能超时，这里给出一个快速读入模板：**

```cpp
long long qread(){
    long long w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
```

**或者使用这份模板：**

```cpp
typedef long long LL;
#define gc pa==pb&&(pb=(pa=buf)+fread(buf,1,100000,stdin),pa==pb)?EOF:*pa++
static char buf[100000],*pa(buf),*pb(buf);
inline LL readint() {
	LL x=0;char c=gc;
	while(c<'0'||c>'9')c=gc;
	for(;c>='0'&&c<='9';c=gc)x=x*10+(c&15);
	return x;
}
```

**其中，在开启 O2 开关的前提下，前者在极限数据下的读入要 $500\texttt{ms}$，而后者需要 $300\texttt{ms}$。也就是说，你的程序至少有 $500\sim 700\texttt{ms}$ 的时间执行主要算法。**


---

---
title: "[USACO21OPEN] Maze Tac Toe S"
layout: "post"
diff: 普及+/提高
pid: P7555
tag: ['USACO', '2021', '记忆化搜索', '进制']
---
# [USACO21OPEN] Maze Tac Toe S
## 题目描述

奶牛 Bessie 喜欢玩走迷宫。她同样喜欢玩井字棋（更准确地说，奶牛版的井字棋，马上会进行介绍）。Farmer John 找到了一种全新的方式，可以使她同时玩到这两种游戏！

首先，奶牛井字棋：与在 $3 \times 3$ 棋盘内放置 `X` 和 `O` 不同，奶牛当然是在 $3 \times 3$ 棋盘内放置 `M` 和 `O`。在一方的回合内，玩家可以选择将一个 `M` 或一个 `O` 放在任意一个空格内（这是另一个与标准井字棋的不同之处，标准的井字棋中一名玩家始终放 `X` 而另一名玩家始终放 `O`）。奶牛井字棋的胜利方是首位拼出 `MOO` 的玩家，可以是同行、同列或对角线。倒着拼出也是可以的，例如一名玩家在棋盘的一行内拼出 `OOM` 也可以获胜。如同标准井字棋一样，有可能最后没有玩家取得胜利。奶牛井字棋的一次行动通常用 3 个字符表示，`Mij` 或 `Oij`，其中 $i$ 和 $j$ 在范围 $1 \ldots 3$ 之间，表示放置 `M` 或 `O` 的行与列。

为了给 Bessie 增加一些挑战，Farmer John 设计了一个由 $N \times N$ 个方格组成的正方形迷宫（$3 \leq N \leq 25$）。某些方格，包括所有的边界方格，有巨大的草堆，使得 Bessie 不能移动到这些方格。Bessie 可以沿东南西北四个方向在迷宫内的所有其他方格内自由行动。某些方格内有一张纸，上面写有奶牛井字棋的一次行动。当 Bessie 在迷宫中移动时，任何时刻她停留在这样的方格上，她都必须于迷宫中移动之时在同时进行的奶牛井字棋游戏内做出对应的行动（除非奶牛井字棋中对应的方格已经被填上了，在这种情况下她不进行行动）。在奶牛井字棋游戏内没有与她对阵的玩家，但迷宫中的某些方格可能会不利于她最终拼出 `MOO`。

如果 Bessie 在获胜之时就会立刻停止奶牛井字棋，请求出她可以通过适当的方式在迷宫中移动而完成的不同的胜利状态棋盘数量。
## 输入格式

输入的第一行包含 $N$。

以下 $N$ 行，每行包含 $3N$ 个字符，描述迷宫。每个方格用 3 个字符表示，`###` 代表墙，`...` 代表空格，`BBB` 代表 Bessie 所在的一个非墙方格，或者一个奶牛井字棋的行动，表示 Bessie 必须进行对应行动的一个非墙方格。恰好一个方格为 `BBB`。
## 输出格式

输出 Bessie 可以通过在迷宫中行动并在获胜时立刻停止而产生的不同的胜利状态下的奶牛井字棋盘数量（可能为 $0$）。
## 样例

### 样例输入 #1
```
7
#####################
###O11###...###M13###
###......O22......###
###...######M22######
###BBB###M31###M11###
###...O32...M33O31###
#####################
```
### 样例输出 #1
```
8
```
## 提示

#### 样例说明

在这个样例中，Bessie 最终可能达成 $8$ 种胜利的棋盘状态：

```plain
O.M
.O.
MOM

O..
.O.
.OM

O.M
.O.
.OM

O..
.O.
MOM

O..
...
OOM

..M
.O.
OOM

...
.O.
OOM

...
...
OOM
```

对其中一种情况进行说明：

```plain
O..
...
OOM
```

在这里，Bessie 可以先移动到 `O11` 方格，然后移动到下方并通过 `O32`、`M33` 和 `O31`。此时游戏结束，因为她获得了胜利（例如她不能再前往位于她当前所在的 `O31` 方格北面的 `M11` 方格）。

#### 说明

供题：Brian Dean


---

---
title: "[COCI 2011/2012 #2] KOMPIĆI"
layout: "post"
diff: 普及+/提高
pid: P7617
tag: ['2011', '进制', 'COCI（克罗地亚）']
---
# [COCI 2011/2012 #2] KOMPIĆI
## 题目描述

给定 $N$ 个正整数 $A_1,A_2,...,A_N$，求有多少整数对 $(i,j)$，满足以下条件：

- $1 \le i < j \le N$
- **$A_i$ 和 $A_j$ 至少有一位数字是相同的（不一定要在相同的数位）**。
## 输入格式

输入的第一行包含一个正整数 $N$。

接下来 $N$ 行，每行包含一个正整数 $A_i$。
## 输出格式

输出一行一个整数，表示满足条件的整数对。
## 样例

### 样例输入 #1
```
3
4
20
44
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
4
32
51
123
282
```
### 样例输出 #2
```
4
```
## 提示

#### 【样例解释】

样例 1 中，满足要求的整数对为 $(1,3)$。

样例 2 中，满足要求的整数对为 $(1,3)$，$(1,4)$，$(2,3)$，$(3,4)$。

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le N \le 10^6$，$1 \le A_i \le 10^{18}$。

#### 【说明】

本题分值按 COCI 原题设置，满分 $120$。

题目译自 **[COCI2011-2012](https://hsin.hr/coci/archive/2011_2012/) [CONTEST #2](https://hsin.hr/coci/archive/2011_2012/contest2_tasks.pdf)** ___T4 KOMPIĆI___。


---

---
title: "[USACO22JAN] Searching for Soulmates S"
layout: "post"
diff: 普及+/提高
pid: P8093
tag: ['数学', '贪心', 'USACO', '2022', '进制']
---
# [USACO22JAN] Searching for Soulmates S
## 题目描述

Farmer John 的每头奶牛都想找到她们的灵魂伴侣——另一头具有相似特点的奶牛，与她们最大程度地相容。每头奶牛的性格由一个整数 $p_i$（$1 \leq p_i \leq 10^{18}$）描述。两头性格相同的奶牛就是灵魂伴侣。奶牛可以通过「改变操作」，对她的性格乘以 $2$，除以 $2$（当 $p_i$ 是偶数时），或者加上 $1$。

Farmer John 最初以任意方式配对了他的奶牛。他很好奇为使每对奶牛成为灵魂伴侣需要进行多少次改变操作。对于每对奶牛，求配对中的第一头奶牛所必须进行的最小改变操作次数，从而可以与第二头奶牛成为灵魂伴侣。
## 输入格式

输入的第一行包含 $N$（$1\le N\le 10$），为奶牛配对的数量。以下 $N$ 行每行描述了一对奶牛，包含两个整数，为她们的性格值。第一个整数是需要被改变与另一头奶牛相匹配的奶牛的性格。
## 输出格式

输出 $N$ 行。对于每一对奶牛，输出第一头奶牛需要进行的最小操作次数，使得她的性格与第二头奶牛相匹配。
## 样例

### 样例输入 #1
```
6
31 13
12 8
25 6
10 24
1 1
997 120
```
### 样例输出 #1
```
8
3
8
3
0
20
```
## 提示

【样例解释】

对于第一个子测试用例，一个最优的操作序列为 $31 \implies 32 \implies 16 \implies 8 \implies 9 \implies 10 \implies 11 \implies 12 \implies 13$。

对于第二个子测试用例，一个最优的操作序列为 $12 \implies 6 \implies 7 \implies 8$.

【数据范围】

- 测试点 1-4 满足 $p_i \le 10^5$。
- 测试点 5-12 没有额外限制。




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

