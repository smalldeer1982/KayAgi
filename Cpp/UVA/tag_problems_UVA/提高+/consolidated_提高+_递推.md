---
title: "Multi-peg Towers of Hanoi"
layout: "post"
diff: 提高+/省选-
pid: UVA10444
tag: ['动态规划 DP', '高精度', '递推']
---

# Multi-peg Towers of Hanoi

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1385

[PDF](https://uva.onlinejudge.org/external/104/p10444.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/b08ae043c16349a4e020bb344c82bd8559661c15.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/9918d07219dee733e043308fe7408963612853cc.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/28c5f29618658abb670593f72b8636cd5eadedfe.png)

## 样例 #1

### 输入

```
3 4
4 4
10 4
10 5
0 0
```

### 输出

```
Case 1: 5
Case 2: 9
Case 3: 49
Case 4: 31
```



---

---
title: "Tribles"
layout: "post"
diff: 提高+/省选-
pid: UVA11021
tag: ['递推', '期望', '线性递推']
---

# Tribles

## 题目描述

# Tribles

## 题面翻译

### 题目大意

一开始有 $k$ 只生物，这种生物只能活一天，死的时候有 $p_i$ 的概率生成 $i$ 只这种生物（也只能活一天），询问 $m$ 天内所有生物都死的概率（包括 $m$ 天前死亡的情况）


[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=1962

[PDF](https://uva.onlinejudge.org/external/110/p11021.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/dc00578efa81b6aad117bc54386f7e892627c921.png)

## 输入格式

第一行输入一个整数 $T$，表示数据总数

每一组先输入三个整数 $n(1<=n<=1000),k(0<=k<=1000),m(0<=m<=1000)$

接下来 $n$ 行，每行一个实数，分别为 $p_0$ 到 $p_{n-1}$


![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/08abc60eb45dcabca841e2417b496cd3ae2dca35.png)

## 输出格式

对于每一组数据，先输出"Case #x: "（请注意冒号后有一个**空格**）
再输出答案，精度要求在 1e-6 以内（即保留小数点后七位）

感谢@xMinh 提供翻译


![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/77ab0f01844658d722f6868f9a488841f59db741.png)

## 样例 #1

### 样例输入 #1

```
4
3 1 1
0.33
0.34
0.33
3 1 2
0.33
0.34
0.33
3 1 2
0.5
0.0
0.5
4 2 2
0.5
0.0
0.0
0.5
```

### 样例输出 #1

```
Case #1: 0.3300000
Case #2: 0.4781370
Case #3: 0.6250000
Case #4: 0.3164062
```

## 样例 #1

### 输入

```
4
3 1 1
0.33
0.34
0.33
3 1 2
0.33
0.34
0.33
3 1 2
0.5
0.0
0.5
4 2 2
0.5
0.0
0.0
0.5
```

### 输出

```
Case #1: 0.3300000
Case #2: 0.4781370
Case #3: 0.6250000
Case #4: 0.3164062
```



---

---
title: "Spreading the Wealth"
layout: "post"
diff: 提高+/省选-
pid: UVA11300
tag: ['递推', '排序', '前缀和']
---

# Spreading the Wealth

## 题目描述

圆桌旁边坐着$n$个人，每个人有一定数量的金币，金币的总数能被$n$整除。每个人可以给他左右相邻的人一些金币，最终使得每个人的金币数量相等。您的任务是求出被转手的金币的数量的最小值。

　

## 输入格式

输入包含多组数据。每组数据第一行为一个整数$n(n<=1000000)$,以下n行每行为一个整数，按逆时针顺序给出每个人拥有的金币数。输入结束标志为文件结束符($EOF$).

　

## 输出格式

对于每组数据，输出被转手的金币的数量的最小值。输入保证这个值在$64$位无符号整数的范围之内。

Translated by @洛谷万岁

## 样例 #1

### 输入

```
3
100
100
100
4
1
2
5
4
```

### 输出

```
0
4
```



---

---
title: "Even Parity"
layout: "post"
diff: 提高+/省选-
pid: UVA11464
tag: ['递推', '枚举', '进制', '概率论']
---

# Even Parity

## 题目描述

给你一个 $n \times n$ 的 $01$ 矩阵（每个元素非 $0$ 即 $1$），你的任务是把尽量少的 $0$ 变成 $1$，使得原矩阵便为偶数矩阵（矩阵中每个元素的上、下、左、右的元素（如果存在的话）之和均为偶数）。

## 输入格式

输入的第一行为数据组数 $T$（$T \le 30$）。每组数据：第一行为正整数 $n$（$1 \le n \le 15$）；接下来的 $n$ 行每行包含 $n$ 个非 $0$ 即 $1$ 的整数，相邻整数间用一个空格隔开。

## 输出格式

对于每组数据，输出被改变的元素的最小个数。如果无解，输出 $-1$。

## 样例 #1

### 输入

```
3
3
0 0 0
0 0 0
0 0 0
3
0 0 0
1 0 0
0 0 0
3
1 1 1
1 1 1
0 0 0
```

### 输出

```
Case 1: 0
Case 2: 3
Case 3: -1
```



---

---
title: "阿里巴巴 Alibaba"
layout: "post"
diff: 提高+/省选-
pid: UVA1632
tag: ['递推']
---

# 阿里巴巴 Alibaba

## 题目描述

## 题面描述
在**一条直线**的同一个方向上有  $n$ 件珠宝，已知每件珠宝的位置，并且第  $i$ 件珠宝在  $t_i$ 时刻就毁灭，问能否将所有的珠宝收集起来？搜集不耗时，移动需要耗时。

## 输入格式

第一行一个整数  $n$（ $n\le10000$）。  
接下来  $n$ 行，每行两个整数，分别为  $a_i$ 和  $t_i$ ，表示从起点走到此处的时间和珠宝消失的时间。

## 输出格式

如果可以收集所有珠宝，则输出最短的时间（不需要回到起点）否则输出`No solution`



---

---
title: "巴比伦塔 The Tower of Babylon"
layout: "post"
diff: 提高+/省选-
pid: UVA437
tag: ['动态规划 DP', '搜索', '递推', '排序']
---

# 巴比伦塔 The Tower of Babylon

## 题目描述

你可能已经听说过巴比伦塔的传说。现在这个传说的许多细节已经被遗忘。所以本着本场比赛的教育性质，我们现在会告诉你整个传说：

巴比伦人有 $n$ 种长方形方块，每种有无限个，第 $i$ 种方块的三边边长是 $xi,yi,zi$。对于每一个方块，你可以任意选择一面作为底，这样高就随着确定了。举个例子，同一种方块，可能其中一个是竖着放的，一个是侧着放的，一个是横着放的。

他们想要用堆方块的方式建尽可能高的塔。问题是，只有一个方块的底的两条边严格小于另一个方块的底的两条边，这个方块才能堆在另一个上面。这意味着，一个方块甚至不能堆在一个底的尺寸与它一样的方块的上面。

你的任务是编写一个程序，计算出这个塔可以建出的最高的高度。

## 输入格式

输入会包含至少一组数据，每组数据的第一行是一个整数 $n(n\le30)$，表示方块的种类数。 这组数据接下来的 $n$ 行，每行有三个整数，表示 $xi,yi,zi$。输入数据会以 $0$ 结束。

## 输出格式

对于每组数据，输出一行，其中包含组号（从 $1$ 开始）和塔最高的高度。按以下格式：``Case i: maximum height = __``。

## 样例 #1

### 输入

```
1
10 20 30
2
6 8 10
5 5 5
7
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
5
31 41 59
26 53 58
97 93 23
84 62 64
33 83 27
0
```

### 输出

```
Case 1: maximum height = 40
Case 2: maximum height = 21
Case 3: maximum height = 28
Case 4: maximum height = 342
```



---

---
title: "勤劳的蜜蜂 Bee Breeding"
layout: "post"
diff: 提高+/省选-
pid: UVA808
tag: ['数学', '递推']
---

# 勤劳的蜜蜂 Bee Breeding

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=749

[PDF](https://uva.onlinejudge.org/external/8/p808.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/9bab4a64afdd472dc2664e3eff03743e904c3d4a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/ece86ec0d7a73280a4d4325cfcfeda323b9b3cd5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/0f05e34c6915f5c4d3fc623283f0f02d6594ce4c.png)

## 样例 #1

### 输入

```
19 30
0 0
```

### 输出

```
The distance between cells 19 and 30 is 5.
```



---

