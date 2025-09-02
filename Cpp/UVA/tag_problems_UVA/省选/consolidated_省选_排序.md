---
title: "DNA Regions"
layout: "post"
diff: 省选/NOI-
pid: UVA1392
tag: ['单调队列', '枚举', '排序']
---

# DNA Regions

## 题目描述

## 题面
给定两个长度为 $n$ 的字符串 $A$ 和 $B$，满足 $A$ 和 $B$ 都只由大写字母 A、C、G、T 组成。

求一个长度最长的闭区间 $[L,R]$，满足对于 $i \in [L,R]$，有不超过 $p \%$ 的 $i$ 满足 $A_i \neq B_i$。

## 输入格式

包含多组数据。

对于每组数据，第一行为两个整数 $n$ 和 $q$。
接下来两行分别是 $A$ 和 $B$。

结束的标志是 $n=0$。

## 输出格式

对于每组数据，若有解，输出满足条件的区间长度的最大值，若无解，输出`No solution.`。

## 输入输出样例
### 输入
```
14 25
ACCGGTAACGTGAA
ACTGGATACGTAAA
14 24
ACCGGTAACGTGAA
ACTGGATACGTAAA
8 1
AAAAAAAA
CCCCCCCC
8 33
AAACAAAA
CCCCCCCC
0 0

```
### 输出
```
8
7
No solution.
1
```

## 说明/提示

$1 \le n \le 1.5 \times 10^5$，$1 \le p \le 99$。



---

---
title: "Robotic Sort"
layout: "post"
diff: 省选/NOI-
pid: UVA1402
tag: ['排序', '期望', '栈']
---

# Robotic Sort

## 题目描述

通过一系列移动，将某些物品按顺序摆好。规定只能使用如下方式排序：
先找到编号最小的物品的位置P1，将区间[1,P1]反转，再找到编号第二小的物品的位置P2，将区间[2,P2]反转……

（如图）
上图是有6个物品的例子，编号最小的一个是在第4个位置。因此，最开始把前面4个物品反转，第二小的物品在最后一个位置，所以下一个操作是把2-6的物品反转，第三部操作则是把3-4的物品进行反转……
在数据中可能存在有相同的编号，如果有多个相同的编号，则按输入的原始次序操作。

## 输入格式

多组数据以0结尾，每组输入共两行，第一行为一个整数N，N表示物品的个数，1<=N<=100000
第二行为N个用空格隔开的正整数，表示N个物品最初排列的编号。

## 输出格式

每组数据输出一行，N个用空格隔开的正整数P1,P2,P3…Pn，Pi表示第i次操作前第i小的物品所在的位置。 注意：如果第i次操作前，第i小的物品己经在正确的位置Pi上，我们将区间[Pi,Pi]反转(单个物品)。

感谢@enor2017 提供翻译



---

---
title: "占领新区域 Conquer a New Region"
layout: "post"
diff: 省选/NOI-
pid: UVA1664
tag: ['并查集', '排序']
---

# 占领新区域 Conquer a New Region

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4539

[PDF](https://uva.onlinejudge.org/external/16/p1664.pdf)

## 样例 #1

### 输入

```
4
1 2 2
2 4 1
2 3 1
4
1 2 1
2 4 1
2 3 1
```

### 输出

```
4
3
```



---

---
title: "岛屿 Islands"
layout: "post"
diff: 省选/NOI-
pid: UVA1665
tag: ['并查集', '枚举', '排序']
---

# 岛屿 Islands

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4540

[PDF](https://uva.onlinejudge.org/external/16/p1665.pdf)



---

