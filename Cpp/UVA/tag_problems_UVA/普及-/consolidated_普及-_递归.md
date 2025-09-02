---
title: "The 3n + 1 problem"
layout: "post"
diff: 普及-
pid: UVA100
tag: ['模拟', '数学', '递归']
---

# The 3n + 1 problem

## 题目描述

考虑下面的程序：

1. 输入 $n$

2. 输出 $n$

3. 如果 $n=1$ 退出程序

4. 如果 $n$ 是奇数，$n \rightarrow 3 n + 1$

5. 如果 $n$ 是偶数 $n\rightarrow \dfrac n 2$

6. 回到第 $2$ 步 

若输入 $22$，会得出下面的数列： `22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1`。

我们推测，对于任何输入的正整数 $n$，程序最终都会输出 $1$（$n\le 10^6$ 时，保证推论正确）。 给定 $n$，可以计算这个程序输出的所有数字的数量（包括最后的 $1$）。我们把输出的数字总数称为这个 $n$ 的周期长度。对于上面的例子，周期长度为 $16$。 

对于输入的每对 $(i,j)$，计算 $[i,j]$ 内所有数字区间长度的最大值。

## 输入格式

输入几对整数 $(i,j)$，保证 $0<i,j\le 10^4$。对于每对 $(i,j)$，你需要计算 $[i,j]$ 内最大区间长度。数据保证 $32$ 位整数在计算过程中不溢出。

## 输出格式

对于每对 $(i,j)$，先输出 $i,j$，再输出 $[i,j]$ 范围内最大周期长度，每个数字中间一个空格，然后换行。

## 样例 #1

### 输入

```
1 10
100 200
201 210
900 1000
```

### 输出

```
1 10 20
100 200 125
201 210 89
900 1000 174
```



---

---
title: "大理石在哪儿 Where is the Marble?"
layout: "post"
diff: 普及-
pid: UVA10474
tag: ['搜索', '二分', '递归', '枚举', '排序']
---

# 大理石在哪儿 Where is the Marble?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1415

[PDF](https://uva.onlinejudge.org/external/104/p10474.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/2bb1c26d80e7830dba0391c0afa3b04c198f8ee0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/6c2a03977a6e49d286d2fa5cc116d53d9da95e8b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/03b79b1f48ddec6133706f0b92ca55a3ecd02a38.png)

## 样例 #1

### 输入

```
4 1
2
3
5
1
5
5 2
1
3
3
3
1
2
3
0 0
```

### 输出

```
CASE# 1:
5 found at 4
CASE# 2:
2 not found
3 found at 3
```



---

---
title: "Help is needed for Dexter"
layout: "post"
diff: 普及-
pid: UVA11384
tag: ['模拟', '递归']
---

# Help is needed for Dexter

## 题目描述

Dexter 对 Dee Dee 感到厌烦了，所以他决定让 Dee Dee 玩一个游戏来让她忙起来。这个游戏很容易玩，但至少对 Dee Dee 来说不容易赢。但是，Dexter 没有时间浪费在这种无聊的任务上，所以他需要你的帮助。

游戏中有一个按钮，当按下按钮时，电脑将随机选择一个数字 $N$。然后屏幕上会显示从 $1$ 到 $N$ 的数字。Dee Dee 可以从屏幕上的数字中选择任意数量的数字，然后她将命令计算机从所选数字中减去她选择的一个正整数（不一定是屏幕上的数字）。她的目标是让所有数字都变成 $0$。

例如，如果 $N = 3$，屏幕上将显示 $3$ 个数字：$1$、$2$、$3$。假设她现在选择 $1$ 和 $2$，命令计算机减去 $1$，那么屏幕上的数字将变为：$0$、$1$、$3$。然后她选择 $1$ 和 $3$，并命令减去 $1$，现在屏幕上的数字是 $0$、$0$、$2$。最后她选择 $2$ 并减去 $2$，所有数字变为 $0$。

Dexter 并不愚蠢，明白这可以很容易地完成，所以为了增加难度，他将为每个 $N$ 给出一个限制 $L$，并且确保 $L$ 是仍然能在 $L$ 步内完成的最小值。但 Dexter 没有时间去思考如何为每个 $N$ 确定 $L$，因此他请求你编写一个程序，输入 $N$，输出 $L$。

## 输入格式

输入由多行组成，每行包含一个 $N$，其中 $1 \le N \le 10 ^ 9$。输入将由文件末尾终止。

## 输出格式

对于每个 $N$，在单独的一行中输出对应的 $L$。

---

Translated by User 735713.

## 样例 #1

### 输入

```
1
2
3
```

### 输出

```
1
2
2
```



---

