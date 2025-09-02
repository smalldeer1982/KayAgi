---
title: "[GCJ 2019 #1A] Golf Gophers"
layout: "post"
diff: 提高+/省选-
pid: P13107
tag: ['2019', '交互题', 'Special Judge', '中国剩余定理 CRT', 'Google Code Jam']
---
# [GCJ 2019 #1A] Golf Gophers
## 题目描述

Last year, a bunch of pesky gophers took up residence in our orchard. We tried to change our line of work by opening up a miniature golf course, but it looks like the gophers have followed us here! Once again, we need to figure out how many gophers there are, but we cannot observe them directly because they are secretive and nocturnal, whereas we like to sleep at night. We do know there are between 1 and M gophers, inclusive.

Our mini golf course is famous for having a small electronic windmill on each of its 18 holes. The i-th windmill has $2 \leqslant \mathbf{B}_{\mathrm{i}} \leqslant 18$ blades, which are numbered from 0 to $\mathbf{B}_{\mathrm{i}}-1$, clockwise. Each night, before going to sleep, we turn off the windmills and set each one such that blade 0 is pointing downward, which is important so that the windmills can charge up properly for the next day. However, we have noticed that when we wake up, the windmills have been disturbed. Since our mini golf course is in a windless area, we think the mischievous gophers must be responsible!

We know that every night, all of the gophers emerge, one by one; each of them chooses one of the windmills independently and uniformly at random and rotates it counterclockwise by one blade. So, for example, for a windmill with 3 blades for which 0 is pointing downward, the first gopher to interact with it turns it so that 1 is pointing downward, and then the next gophers to interact with that windmill make the downward-pointing blade have number 2, then 0, then 1, and so on.

We have devised a plan. We designed our windmills so that we can easily change the number of blades (to modulate the difficulty of our course), and we will now take advantage of this! Each night, before going to sleep, we can choose the number of blades on each of the 18 windmills, within the given limits; we do not have to use the same number of blades on each windmill, or make the same choices every night. In the morning, we will observe the number on each windmill's downward-pointing blade.

We have $\mathbf{N}$ nights in which to figure out $\mathbf{G}$, the number of gophers. Can you help us?

### Interactive Protocol

This is an interactive problem.

Initially, your program should read a single line containing three integers $\mathbf{T}$, $\mathbf{N}$ and $\mathbf{M}$, the number of test cases, the number of nights allowed per test case and the maximum number of gophers, respectively. Then, you need to process $\mathbf{T}$ test cases.

In each test case, your program processes up to $\mathbf{N}+1$ exchanges with our judge. You may make up to $\mathbf{N}$ exchanges of the following form:

* Your program outputs one line with eighteen integers between 2 and 18, inclusive; the i-th of these represents the number of blades you want the i-th windmill to have on that night.
* The judge responds with one line with eighteen integers; the i-th of these represents the number on the downward-pointing blade of the i-th windmill in the morning, after the gophers have worked their mischief. If you sent invalid data (e.g., a number out of range, or a malformed line), the judge instead responds with -1.

On each night, for each gopher, the choice of which windmill the gopher turns is uniform at (pseudo)-random, and independent of any other choice by any gopher (including itself) on any night.

After making between 0 and $\mathbf{N}$ exchanges as explained above, you must make one more exchange of the following form:

* Your program outputs one integer: your guess for $\mathbf{G}$, the number of gophers.
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

This interaction corresponds to Test set 1. Suppose that, unbeknownst to us, the judge has decided that there are 10 gophers.

```
  t, n, m = readline_int_list()   // Reads 20 into t, 365 into n and 100 into m.
  // Choose numbers of blades for day 1.
  printline 2 2 2 2 18 3 3 3 3 3 3 4 4 4 4 5 2 2 to stdout
  flush stdout
  // Reads 0 0 0 0 0 0 1 2 1 0 1 2 0 0 0 0 1 0 into res.
  res = readline_int_list()
  // Choose numbers of blades for day 2.
  printline 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 to stdout
  flush stdout
  // Reads 0 1 1 2 0 0 1 0 0 0 0 0 0 1 0 0 0 0 into res.
  res = readline_int_list()
  printline 8 to stdout        // We make a wrong guess even though we could
  flush stdout                 // have investigated for up to 363 more nights.
  verdict = readline_int()     // Reads -1 into verdict (judge has decided our
                               //   solution is incorrect)
  exit                         // Exits to avoid an ambiguous TLE error
```

Notice that even though the guess was consistent with the information we received from the judge, we were still wrong because we did not find the correct value.

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our [interactive runner](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py) for that. For more information, read the instructions in comments in that file.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

- $1 \leqslant \mathrm{T} \leqslant 20 .$

**Test set 1 (11 Pts, Visible)**

- $\mathrm{N}=365$.
- $\mathrm{M}=100$.

**Test set 2 (21 Pts, Hidden)**

- $\mathrm{N}=7$.
- $\mathrm{M}=10^{6}$.


---

---
title: "【模板】中国剩余定理（CRT）/ 曹冲养猪"
layout: "post"
diff: 提高+/省选-
pid: P1495
tag: ['数学', '中国剩余定理 CRT']
---
# 【模板】中国剩余定理（CRT）/ 曹冲养猪
## 题目描述

自从曹冲搞定了大象以后，曹操就开始捉摸让儿子干些事业，于是派他到中原养猪场养猪，可是曹冲满不高兴，于是在工作中马马虎虎，有一次曹操想知道母猪的数量，于是曹冲想狠狠耍曹操一把。举个例子，假如有 $16$ 头母猪，如果建了 $3$ 个猪圈，剩下 $1$ 头猪就没有地方安家了。如果建造了 $5$ 个猪圈，但是仍然有 $1$ 头猪没有地方去，然后如果建造了 $7$ 个猪圈，还有 $2$ 头没有地方去。你作为曹总的私人秘书理所当然要将准确的猪数报给曹总，你该怎么办？
## 输入格式

第一行包含一个整数 $n$ —— 建立猪圈的次数，接下来 $n$ 行，每行两个整数 $a_i, b_i$，表示建立了 $a_i$ 个猪圈，有 $b_i$ 头猪没有去处。你可以假定 $a_1 \sim a_n$ 互质。
## 输出格式

输出包含一个正整数，即为曹冲至少养母猪的数目。

## 样例

### 样例输入 #1
```
3
3 1
5 1
7 2
```
### 样例输出 #1
```
16
```
## 提示

$1 \leq n\le10$，$0 \leq b_i\lt a_i\le100000$，$1 \leq \prod a_i \leq 10^{18}$


---

---
title: "[TJOI2009] 猜数字"
layout: "post"
diff: 提高+/省选-
pid: P3868
tag: ['数学', '2009', '各省省选', '扩展欧几里德算法', '中国剩余定理 CRT', '天津']
---
# [TJOI2009] 猜数字
## 题目描述

现有两组数字，每组 $k$ 个。

第一组中的数字分别用 $a_1,a_2,\cdots ,a_k$ 表示，第二组中的数字分别用 $b_1,b_2,\cdots ,b_k$ 表示。

其中第二组中的数字是两两互素的。求最小的 $n\in \mathbb{N}$，满足对于 $\forall i\in [1,k]$，有 $b_i | (n-a_i)$。
## 输入格式

第一行一个整数 $k$。

第二行 $k$ 个整数，表示：$a_1,a_2,\cdots ,a_k$。

第三行 $k$ 个整数，表示：$b_1,b_2,\cdots ,b_k$。
## 输出格式

输出一行一个整数，为所求的答案 $n$。
## 样例

### 样例输入 #1
```
3
1 2 3
2 3 5

```
### 样例输出 #1
```
23
```
## 提示

对于 $100\%$ 的数据：

$1\le k \le 10$，$|a_i|\le 10^9$，$1\le b_i\le 6\times 10^3$，$\prod_{i=1}^k b_i\le 10^{18}$。

每个测试点时限 $1$ 秒。

注意：对于 ```C/C++``` 语言，对 $64$ 位整型数应声明为 ```long long```。

若使用 ```scanf```，```printf``` 函数（以及 ```fscanf```，```fprintf``` 等），应采用 ```%lld``` 标识符。


---

---
title: "[ZJOI2006] 皇帝的烦恼"
layout: "post"
diff: 提高+/省选-
pid: P4409
tag: ['贪心', '递推', '2006', '各省省选', '浙江', '中国剩余定理 CRT']
---
# [ZJOI2006] 皇帝的烦恼
## 题目描述

经过多年的杀戮，秦皇终于统一了中国。为了抵御外来的侵略，他准备在国土边境安置 $n$ 名将军。不幸的是这 $n$ 名将军羽翼渐丰，开始展露他们的狼子野心了。他们拒绝述职、拒绝接受皇帝的圣旨。

秦皇已经准备好了秘密处决这些无礼的边防大将。

不过为防兵变，他决定先授予这些将军一些勋章，为自己赢得战略时间。将军们听说他们即将被授予勋章都很开心，他们纷纷上书表示感谢。第 $i$ 个将军要求得到 $a_i$ 枚不同颜色的勋章。但是这些将军都很傲气，如果两个相邻的将军拥有颜色相同的勋章他们就会认为皇帝不尊重他们，会立即造反（编号为 $i$ 的将军和编号为 $i+1$ 的将军相邻；因为他们驻扎的边境可以类似看成一个圆形，所以编号 $1$ 和编号 $n$ 的将军也相邻）。

皇帝不得不满足每个将军的要求，但对他们的飞扬跋扈感到很气愤。于是皇帝决定铸造尽量少种类的勋章来满足这些狂妄者的要求。请问他至少要铸造多少种颜色的勋章？
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行每行一个整数 $a_i$，表示第 $i$ 个将军要求得到多少种勋章。
## 输出格式

输出一个整数，即最少需要多少种勋章。
## 样例

### 样例输入 #1
```
4
2
2
1
1
```
### 样例输出 #1
```
4
```
## 提示

$1 \leq n \leq 2 \times 10^4$，$1 \leq a_i  \leq 10^5$。


---

---
title: "按钮"
layout: "post"
diff: 提高+/省选-
pid: P4861
tag: ['数学', '枚举', '中国剩余定理 CRT']
---
# 按钮
## 题目背景

Ada被关在了一个房间里。
## 题目描述

房间的铁门上有一个按钮，还有一个显示屏显示着“1”。    
旁边还有一行小字：“这是一个高精度M进制计算器，每按一次按钮，屏幕上的数便会乘以K。当个位数再次变为1时，门就开了。”    
由于Ada急于出去，所以你要在1s之内求出她的最小按键次数。
## 输入格式

一行，两个整数M和K。
## 输出格式

一行一个数字，表示最小按键次数。   
如果无论Ada按多少次都无法让门打开，输出"Let's go Blue Jays!"（不含引号）。
## 样例

### 样例输入 #1
```
11 2
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
6 26
```
### 样例输出 #2
```
Let's go Blue Jays!
```
## 提示

对于30%的数据，$2\leq M,K\leq10^4$。    
对于100%的数据，$2\leq M,K\leq2\times 10^{9}$。  
update：我们不认为个位为11,21,...为问题的解（例如，11在16进制下记为B）    


---

---
title: "[POI 2003] Sums"
layout: "post"
diff: 提高+/省选-
pid: P8060
tag: ['2003', 'POI（波兰）', '最短路', '中国剩余定理 CRT']
---
# [POI 2003] Sums
## 题目描述

我们给定一个整数集合 $A$。考虑一个非负整数集合 $A'$，所有属于 $A'$ 的集合的数 $x$ 满足当且仅当能被表示成一些属于 $A$ 的元素的和（数字可重复）。

比如，当 $A = \{2,5,7\}$，属于 $A'$ 的数为：$0$（$0$ 个元素的和），$2$，$4$（$2 + 2$）和 $12$（$5 + 7$ or $7 + 5$ or $2 + 2 + 2 + 2 + 2 + 2$）；但是元素 $1$ 和 $3$ 不属于 $A'$。
## 输入格式

第一行有一个整数 $n$，代表集合 $A$ 的元素个数。接下来每行一个数 $a_i$ 描述一个元素。$A = \{a_1,a_2,...,a_n\}$。

接下来一个整数 $k$，然后每行一个整数，分别代表 $b_1,b_2,...,b_k$。
## 输出格式

输出 $k$ 行。如果 $b_i$ 属于 $A'$，第 $i$ 行打印 `TAK`，否则打印 `NIE`。
## 样例

### 样例输入 #1
```
3
2
5
7
6
0
1
4
12
3
2
```
### 样例输出 #1
```
TAK
NIE
TAK
TAK
NIE
TAK
```
## 提示

对于所有数据，$1 \le n \le 5 \times 10^3$，$1 \le k \le 10^4$，$1 \le a_1 < a_2 < ... < a_n \le 5 \times 10^4$，$0 \le b_i \le 10^9$。


---

---
title: "「WHOI-4」ggcd"
layout: "post"
diff: 提高+/省选-
pid: P8961
tag: ['数论', 'Special Judge', 'O2优化', '素数判断,质数,筛法', '中国剩余定理 CRT']
---
# 「WHOI-4」ggcd
## 题目背景

如何输入输出 `__int128`：

```cpp
__int128 read() {
  char c = getchar();
  __int128 x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar()) f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
  if (f) x = -x;
  return x;
}
void write(__int128 x, char c = '\0') {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
  if (c != '\0') putchar(c);
}
```
## 题目描述

**本题已新增一组样例，请注意查看。**

小 Y 给了你长度为 $n$ 的数组 $y$ 以及一个正整数 $m$，保证 $0\le y_i<m$，请你构造一个同样长为 $n$ 的数组 $x$，使得：

1. $x_i$ 在 `__int128` 范围内；
2. $x_i\bmod m=y_i$；
3. $\gcd(|x_1|,\cdots,|x_n|)\bmod m$ 最大。

注意，$x_i$ **可以为负**，此时 $m\mid (x_i-y_i)$ 且 $0\le y_i<m$。 
## 输入格式

第一行两个正整数 $n,m$。

接下来一行 $n$ 个非负整数，代表 $x_i \bmod m$ 的值。
## 输出格式

第一行一个非负整数 $g$，代表 $\gcd(|x_1|,|x_2|,\cdots,|x_n|)\mod m$ 的可能最大值。

接下来一行 $n$ 个整数，代表 $x_i$。
## 样例

### 样例输入 #1
```
1 10
4
```
### 样例输出 #1
```
6
-6
```
### 样例输入 #2
```
1 10
7
```
### 样例输出 #2
```
7
7
```
### 样例输入 #3
```
2 9
3 3
```
### 样例输出 #3
```
6
12 -6
```
### 样例输入 #4
```
10 7
1 2 3 4 5 6 0 1 2 3
```
### 样例输出 #4
```
6
36 30 24 18 12 6 42 -6 30 24
```
## 提示

**数据范围**

**本题采用捆绑测试。**

Subtask 1（$30$ pts）：$m$ 是素数。

Subtask 2（$70$ pts）：无特殊限制。

对于所有数据，保证 $2\le m \le10^9$，$1\le n\le10^6$。

**关于 Special Judge**

对于每个测试点：

如果你输出的格式不正确，你将会获得 $0$ 分。

如果你输出的数中有不在 `__int128` 范围的数，可能导致溢出所以你可能无法获得预期的分数。

如果你的数列 $x$ 不符合题目给定的 $y$，你将会获得 $0$ 分。

如果你的数列 $x$ 不符合你输出的 $g$，你将会获得 $0$ 分。

如果你的 $g$ 不为最大，你将会获得 $0$ 分。

否则你将获得该测试点的所有分数。


---

