# 【MX-X4-T7】「Jason-1」Ball

## 题目背景

原题链接：<https://oier.team/problems/X4H>。

## 题目描述

**这是一道提交答案题。**

你有 $10$ 个盒子，每个任务会给出一个 $n$，初始时前 $n$ 个盒子内**可能**有一些球，后 $10-n$ 个盒子为空。

用小写字母表示每种颜色的球，初始时最多只有三种颜色的球，分别用 $\tt a, b, c$ 表示。而在程序中，你可以使用**任何小写字母**表示对应颜色的球。

定义一个盒子**包含**一个字符串，表示对于每种颜色的球，盒子中出现的个数不小于字符串中出现的个数。

从一个盒子中**删除**一个字符串，表示对于字符串中每一个小写字母代表的球，从盒子中取走一个相同颜色的球。删除的前提是需要满足此盒子包含该字符串。

向一个盒子中**放入**一个字符串，表示对于字符串中每一个小写字母代表的每个球，向盒子中放入一个相同颜色的球。

你需要写一个程序完成一些任务，程序包含下面几种语句可供使用：

- `change x s y t`，其中 $x, y$ 是不超过 $10$ 的非负整数，$s, t$ 是仅由小写字母或单个字符 `@` 组成的**非空**字符串（**如果为 `@` 则表示将该字符串视作空串**）。如果 $x$ 为 $0$，则将 $k$ 由 $1$ 遍历到 $10$，否则 $k = x$。如果盒子 $k$ 中包含字符串 $s$，从其中删除 $s$，并在盒子 $y$ 中放入字符串 $t$，如果 $y=0$ 则在当前的 $k$ 中（原地）放入，这样就视为成功执行命令。每当成功执行命令后，立刻回到上一个断点，无论 $k$ 是否完全遍历。如果没有成功执行命令，跳转到下一条语句。
- `#` 表示一个断点。**你必须以一行断点结束整个程序**。认为第 $0$ 行也是一个断点，此断点不计入代价。

**语句数**可简单地视为程序中 `change` 和 `#` 的数量之和，第 $0$ 行的虚拟断点不计入，最后一行的断点计入。

**断点数**可简单地视为程序中 `#` 的数量。第 $0$ 行的虚拟断点不计入，最后一行的断点计入。

你不能使用超过 $100$ 条语句，超过 $10$ 的盒子或是非小写字母的球，任意一个盒子中某种颜色的球的个数均不能超过 $10^{8}$，程序中的单个字符串长度不能超过 $200$，你的程序单组数据实际遍历的语句条数不能超过 $4 \times 10^5$，单组数据实际判断包含的字符集大小之和不能超过 $10^7$（参考下发的检验器）。

约定 $n$ 表示输入至多使用的盒子数，$mx$ 表示初始时每个盒子中每种颜色球个数的最大值，$max$ 表示初始时所有盒子中球总数的最大值，$sum$ 表示初始时所有盒子中球的总数。**任务中未提及的盒子必须保持原状**，你需要分别完成下面 $10$ 个任务。

1. $n=10, sum \le 100$，你需要将所有 $\tt a$ 颜色球放入盒子 $1$，所有 $\tt b$ 颜色球放入盒子 $2$，所有 $\tt c$ 颜色球放入盒子 $3$。

2. $n=10, sum \le 100$，你需要将所有 $\tt a$ 颜色的球改为 $\tt b$ 颜色的球，将所有 $\tt b$ 颜色的球改为 $\tt c$ 颜色的球，将所有 $\tt c$ 颜色的球改为 $\tt a$ 颜色的球，这三个操作应同时完成。

3. $n=10, sum \le 100$，你需要将所有不包含 $\tt a$ 颜色球的盒子清空。

4. $n=10, sum \le 100$，你需要给所有非空的，不包含 $\tt a$ 颜色球的盒子放入一个 $\tt a$ 颜色球。

5. $n=5, sum \le 5$，你需要将所有球按照颜色从小到大（${\tt a} < {\tt b} < {\tt c}$）依次放入盒子 $1$ 到 $sum$，每个盒子恰好只放一个球，初始的球不保留。

6. $n=10, sum \le 100$，对于每个盒子，只保留一个出现次数最多的颜色的球，如果有多种颜色出现次数最多，将其变为空集。

7. $n=10, sum \le 100$，对于每个盒子，只保留出现次数最多的颜色的球，如果有多种颜色出现次数最多，保留颜色最小的（${\tt a} < {\tt b} < {\tt c}$）。

8. $n=1, mx \le 10$，记 $\tt a, b, c$ 颜色的球的个数为 $A, B, C$，你需要对于满足 $1 \le x \le 5$ 的整数 $x$ 使得盒子 $x$ 在最终恰好有 $A+Bx+Cx^2$ 个 $\tt a$ 颜色球，不能有其它颜色球。

9. $n=5, max \le 10$，所有 $n$ 个盒子中球总数相等。将每个盒子中的球按从小到大排序，组成一个字符串，保证字符串两两不同。你需要对于每个字符串求出其字典序排名，按字典序从小到大依次将盒子改为 $\tt a, b, c, d, e$。

10. $n=5, max \le 10$，你需要对 $n$ 个盒子求前缀和，即将前面所有盒子的球复制一份放入自己。

**注：子任务按某种规则排序，与难度无关。**

## 说明/提示

**【自定义校验器数据格式】**

第一行，两个整数 $T, V$，分别表示数据组数与评分参数。

对于接下来每组数据：

第一行，两个整数 $n,m$，表示需要描述的输入盒子数与输出盒子数。

第二行，$n$ 个字符串，描述输入时前 $n$ 个盒子的状态。

第三行，$m$ 个字符串，描述输出时前 $m$ 个盒子的状态，**你仍然需要保证其它盒子为空**。

**同样地，使用 `@` 表示空串**。

**【自定义校验器使用方法】**

将 `checker.cpp` 编译后，在命令行执行

```
checker [in] [out] [ans]
```

其中 `[in]` 为测试数据，`[out]` 为你需要测试的程序，`[ans]` 输入和 `[in]` 相同的内容。

例如你需要测试第一个样例，且你的程序名为 `1.out`，需先将 `1.in` 复制到当前目录，并执行

```
checker 1.in 1.out 1.in
```

**【评分标准】**

对于每个测试点，其内部会评测若干组测试数据。

若你的输出出现下列情况，那么该测试点不得分：

- 输出与要求不符。
- 出现无法识别或不合法的语句。
- 某个盒子中某种颜色的球数量超过 $10^8$。
- 使用超过 $100$ 条语句。
- 程序中单个字符串长度超过 $200$。
- 使用不在 $1$ 到 $10$ 之间的盒子。
- 使用非小写字母颜色的球。
- 单组数据实际语句遍历次数大于 $4 \times 10^5$。
- 单组数据实际判断包含的字符集大小之和超过 $10^7$（参考下发的检验器）。

语句数可简单地视为程序中 `change` 和 `#` 的数量之和，第 $0$ 行的虚拟断点不计入，最后一行的断点计入。

断点数可简单地视为程序中 `#` 的数量。第 $0$ 行的虚拟断点不计入，最后一行的断点计入。

一个程序的代价是你给出的断点数量乘以程序的语句数，记作 $val$。

否则设对应子任务的评分标准为 $V$，那么你的得分为：

$$\mathrm{score}=\begin{cases}11&V>val\\\Big\lfloor\frac{10}{\exp\left(1-\frac {V}{val}\right)}\Big\rfloor&\text{otherwise.}\end{cases}$$

下面给出各个任务对应的评分标准 $V$:

| 编号 | $1$ | $2$ | $3$ | $4$ | $5$| $6$ | $7$ | $8$ | $9$ | $10$ |
| :-: | :-: | :-: | :-: | :-: | :-: |  :-: | :-: | :-: | :-: | :-: |
| $V$ | $16$ | $16$ | $16$ | $16$ | $26$ | $8$ | $10$ | $18$ | $20$ | $30$ |

## 样例 #1

### 输入

```
见附件 down.zip 中的 sample 文件夹```

### 输出

```
见附件 down.zip 中的 sample 文件夹```

# 题解

## 作者：wukaichen888 (赞：4)

神仙题。

大概按难度排序。

task1
----
考虑引入其他字符进行计数，注意不要漏掉 $L$。

```txt
8
change 0 a 1 d
change 0 b 2 e
change 0 c 3 f
#
change 1 d 1 a
change 2 e 2 b
change 3 f 3 c
#
```

task2
---
与 task1 大致相同。

```txt
8
change 0 a 0 d
change 0 b 0 e
change 0 c 0 f
#
change 0 d 0 b
change 0 e 0 c
change 0 f 0 a
#
```

task6
---
循环删除 `abc` 串，剩至多两种字符。

然后删除 `ab`、`bc`、`ac` 即可。

然后去重。

```txt
8
change 0 abc 0 @
change 0 ab 0 @
change 0 ac 0 @
change 0 bc 0 @
change 0 aa 0 a
change 0 bb 0 b
change 0 cc 0 c
#
```

task7
---
考虑用以下做法保留两数众数。

```txt
change 0 ab 0 w
change 0 bw 0 bb
change 0 w 0 a
```

整三遍就过了。

ex_task7
---
考虑将其中两次「保留两数众数」并起来。

```txt
9
change 0 bc 0 f
change 0 cf 0 cc
change 0 f 0 b
change 0 ac 0 d
change 0 cd 0 cc
change 0 ab 0 d
change 0 bd 0 bb
change 0 d 0 a
#
```

task3
---
考虑将含 `a` 盒子的 `b`、`c` 替换为 `d`、`e`。

然后删除 `b`、`c`。

`d`、`e` 替换为 `b`、`c`。

```txt
8
change 0 ab 0 ae
change 0 ac 0 af
change 0 b 0 @
change 0 c 0 @
#
change 0 e 0 b
change 0 f 0 c
#
```

task4
---
结构上类似 task3。

```txt
8
change 0 ab 0 ae
change 0 ac 0 af
change 0 b 0 ab
change 0 c 0 ac
#
change 0 e 0 b
change 0 f 0 c
#
```

task8
---
手算每个字符对每个点贡献，优化掉其中一个位置。

```txt
9
change 1 a 2 dafgh
change 1 b 2 daafffgggghhhhh
change 1 c 2 daaaafffffffffgggggggggggggggghhhhhhhhhhhhhhhhhhhhhhhhh
#
change 2 d 1 a
change 2 f 3 a
change 2 g 4 a
change 2 h 5 a
#
```

task5
---
进制优化：压成一个字母进行操作。

```txt
13
change 0 a 1 wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
change 0 b 1 wwwwww
change 0 c 1 w
#
change 4 ws 5 w
change 3 ws 4 w
change 2 ws 3 w
change 1 ws 2 w
change 0 wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww 0 assssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
change 0 wwwwww 0 bssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
change 0 w 0 csssss
change 0 s 0 @
#
```

ex_task3
---
利用 task5 的进制优化技巧可以四行优化为三行。

```txt
7
change 0 b 0 ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
change 0 ac 0 ae
change 0 c 0 @
#
change 0 e 0 c
change 0 ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc 0 b
#
```

ex_task4
---
利用 task5 的进制优化技巧可以四行优化为三行。

```txt
7
change 0 ac 0 ae
change 0 b 0 ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
change 0 c 0 ac
#
change 0 e 0 c
change 0 ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc 0 b
#
```

task10/ex_task10
---
直接进制优化，然后前缀和，这是容易的。

然后加一行运行次数的优化就行：

```txt
14
change 3 i 4 ij
change 2 i 3 ij
change 1 i 2 ij
change 4 iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii 5 jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
change 4 i 5 j
change 0 c 0 ij
change 0 b 0 iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiijjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
change 0 a 0 bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
#
change 0 i 0 @
change 0 jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj 0 b
change 0 bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb 0 a
change 0 j 0 c
#
```

task9
---
大概是进制优化，用官方题解所说的批量操作，然后合并优化一下。

解法建议看 [std](https://www.luogu.com/paste/57zgqvpt)。

ex_task9
---
```txt
19
change 0 f 1 r
change 0 g 2 r
change 0 h 3 r
change 0 i 4 r
change 0 j 5 r
change 0 rrrr 0 vssssa
change 0 vssssab 0 ovssssa
change 0 vssssac 0 vssssa
change 0 aa 0 abcoooooooooo
change 0 bc 0 bcffffgggghhhhiiiijjjj
change 0 srr 0 @
change 0 or 0 v
change 0 rssssa 0 effgghhiijj
change 0 rsssa 0 dffgghhiijj
change 0 rssa 0 cffgghhiijj
change 0 rsa 0 bffgghhiijj
change 0 r 0 @
change 0 v 0 fghij
#
```

---

## 作者：xuanxuan001 (赞：3)

写这题的题解给我一种抄答案的感觉（特别是场上没有做出来的任务），但如果没人写的话之后的人又该怎么知道做法呢。

题意自行阅读，挺抽象的就对了。

发现题目限制要我们尽量少用断点，但分析这个问题首先要知道，对于其中大概一半的任务，你是无法区分输入的数据和输出的数据的（其中只有），因此你注定需要使用两个断点，可能在思考解法时会因确定函数数量而有一点帮助，因为事实证明这些正解都是只用两个断点。

# Task 1

显然需要两次断点，然后就没了。

```
8
change 0 a 1 x
change 0 b 2 y
change 0 c 3 z
#
change 1 x 1 a
change 2 y 2 b
change 3 z 3 c
#
```

# Task 2

跟前一个几乎一样，就不贴答案了。

# Task 3

大概就是把 bc 跟 a 一块转成另一个字母，然后把没转成功的 bc 扔了就行~~a 有点像催化剂~~。

```
8
change 0 ab 0 ae
change 0 ac 0 af
change 0 b 0 @
change 0 c 0 @
#
change 0 e 0 b
change 0 f 0 c
#
```

# Task 4

跟前一个类似，只需要在转 bc 的时候把扔个 a 进去而不是删除即可，这样其他的 bc 就会直接选择跟 a 的语句。但如果有空集会寄，不懂，但官解也会寄。

# Task 5

较为抽象。发现 abc 出现次数都不多，于是用 $6$ 进制强行压成一个字符的出现次数。剩下的实现直接看答案吧，也讲不太清楚（？），手模一遍语句就啥都懂了。

```
13
change 0 c 1 d
change 0 b 1 dddddd
change 0 a 1 dddddddddddddddddddddddddddddddddddd
#
change 1 dz 2 d
change 2 dz 3 d
change 3 dz 4 d
change 4 dz 5 d
change 0 dddddddddddddddddddddddddddddddddddd 0 azzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
change 0 dddddd 0 bzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
change 0 d 0 czzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
change 0 z 0 @
#
```

# Task 6

直接不断消不同字符即可。

```
8
change 0 abc 0 @
change 0 ab 0 @
change 0 bc 0 @
change 0 ac 0 @
change 0 aa 0 a
change 0 bb 0 b
change 0 cc 0 c
#
```

# Task 7

赛时以为这个也是只保留一个众数然后这个任务就没拿分:(

当时应该是做了个 12 步的，所以本来就应该显示 WA，也没拿出来测试，也没估总分，总之就是没管，赛后按那个做法搞出了个 10 步的交上去才发现问题。

考虑比较 a 和 b 的出现次数，每次将一个 ab 变成 x，然后最后如果剩下有 b 就让 x 变 b，否则变 a，大概就是这样，原题整三遍就行了。

```
change 0 ab 0 x
change 0 xb 0 bb
change 0 x 0 a
```

# Task 8

赛时写了半天的各种拆分转换怎么也不行。

直接用 5 中字母分别代表给每个位置的数量即可。

```
9
change 1 a 2 awxyz
change 1 b 2 aawxxxyyyyzzzzz
change 1 c 2 aaaawxxxxxxxxxyyyyyyyyyyyyyyyyzzzzzzzzzzzzzzzzzzzzzzzzz
#
change 2 w 1 a
change 2 x 3 a
change 2 y 4 a
change 2 z 5 a
#
```

# Task 9

我也没太搞懂，半 whk 选手没时间细研究。。。

大概就是将 a 对应 $11$ 个 o，b 对应 $1$ 个 o，然后只需要比较 o 的数量从大到小即可。每次循环给每个还有 o 的都删一个 o，并用另一个符号记录每个位置还有没有被标号并依次编号。

说的读入优化就是看似输入和输出无法区分，但实际上由于保证互不相同，所以输入的长度不小于 2，因此可以每次都按照两个字符操作来保证程序结束。

上面说的从第二句话开始就可能不对，都是我瞎猜的，解法[看出题人写的](https://www.luogu.com/paste/57zgqvpt)。

# Task 10

发现最后一个位置的字母数不超过 50，不能再用进制压了，但把三种字母分开搞步数又太多。

这时考虑在运算的优先级上找到一些奇妙的方法。前缀和操作只需要不断把 abc 向后传递并将原来的改成 xyz 即可，不需要在意操作顺序。

因此将 b 对应 51 个 a，c 对应 52 个 a，每次转换后立刻将它们转移到下一个位置并引发下一个位置的对应转换即可保证不出现混乱，注意优先顺序的设计，具体看答案。

```
15
change 1 d 2 a
change 2 d 3 a
change 3 d 4 a
change 4 d 5 a
change 5 d 5 @
change 0 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa 0 c
change 0 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa 0 b
change 0 a 0 xd
change 0 b 0 yddddddddddddddddddddddddddddddddddddddddddddddddddd
change 0 c 0 zdddddddddddddddddddddddddddddddddddddddddddddddddddd
#
change 0 x 0 a
change 0 y 0 b
change 0 z 0 c
#
```

---

