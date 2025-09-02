---
title: "Ecological Bin Packing"
layout: "post"
diff: 普及/提高-
pid: UVA102
tag: ['字符串', '枚举', '深度优先搜索 DFS']
---

# Ecological Bin Packing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

[PDF](https://uva.onlinejudge.org/external/1/p102.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ef84892469f793327bfb4a3ea04e4237b1761a6d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ae3b90e524e6ffd7e27eab05a64abfd8be7111ef.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/249702f9f5f1e91446cb32d9b3ad6a7eca7264f5.png)

## 样例 #1

### 输入

```
1 2 3 4 5 6 7 8 9
5 10 5 20 10 5 10 20 10
```

### 输出

```
BCG 30
CBG 50
```



---

---
title: "最长的滑雪路径 Longest Run on a Snowboard"
layout: "post"
diff: 普及/提高-
pid: UVA10285
tag: ['字符串', '搜索', '记忆化搜索']
---

# 最长的滑雪路径 Longest Run on a Snowboard

## 题目描述

$ben$喜欢滑雪。（以下简叙）在一个$R*C(R,C\leq100)$的整数矩阵上找一条高度严格递减的最长路。起点任意，但每次只能沿着上下左右$4$个方向之一走一格，并且不能走出矩阵外。如图所示，最长路是按照高度$25,24,23,...,2,1$这样走，长度为$25$。矩阵中的数均为$0$~$100$.

## 输入格式

有多组数据。

第一行为一个整数$N$，表示数据组数。
对于每组数据，第一行包括一个字符串和两个整数$R,C$，为此滑雪者的姓名和矩阵的长宽。

## 输出格式

对于每组数据，输出一行，格式为：
``name: answer``

$name$为当前数据的滑雪者姓名，$answer$为你的答案。

## 样例 #1

### 输入

```
2
Feldberg 10 5
56 14 51 58 88
26 94 24 39 41
24 16 8 51 51
76 72 77 43 10
38 50 59 84 81
5 23 37 71 77
96 10 93 53 82
94 15 96 69 9
74 0 62 38 96
37 54 55 82 38
Spiral 5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
```

### 输出

```
Feldberg: 7
Spiral: 25
```



---

---
title: "Square"
layout: "post"
diff: 普及/提高-
pid: UVA10364
tag: ['深度优先搜索 DFS']
---

# Square

## 题目描述

给定 $N$ 根木棍，每根木棍的长度为 $x$ 。

尝试用所有的木棍围成一个正方形。

## 输入格式

第一行输入一个整数 $T$，代表 $T$ 组数据。

接下来 $T$ 行，每行开头输入一个整数 $N$，即有 $N$ 根木棍，接着输入 $N$ 个整数代表每根木棍的长度。

## 输出格式

$T$ 行，每行输出一个字符串，若能围成正方形，输出 ``yes``，否则输出 ``no``。

## 样例 #1

### 输入

```
3
4 1 1 1 1
5 10 20 30 40 50
8 1 7 2 6 4 4 3 5
```

### 输出

```
yes
no
yes
```



---

---
title: "Chinese Mahjong"
layout: "post"
diff: 普及/提高-
pid: UVA11210
tag: ['模拟', '字符串', '搜索', '枚举']
---

# Chinese Mahjong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2151

[PDF](https://uva.onlinejudge.org/external/112/p11210.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/00db9c6ee014cb07d2ff71e0aff3d224225bbbd1.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/1402d96f2257d9e8bce6c1fccdee577f9b27804e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/0cc0c231da6a95552468965d5df9b75080e2ca2a.png)

## 样例 #1

### 输入

```
1S 1S 2S 2S 2S 3S 3S 3S 7S 8S 9S FA FA
1S 2S 3S 4S 5S 6S 7S 8S 9S 1T 3T 5T 7T
0
```

### 输出

```
Case 1: 1S 4S FA
Case 2: Not ready
```



---

---
title: "Commandos"
layout: "post"
diff: 普及/提高-
pid: UVA11463
tag: ['广度优先搜索 BFS', '最短路']
---

# Commandos

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2458

[PDF](https://uva.onlinejudge.org/external/114/p11463.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/6db49602a4d25da560ee412c34699e1614bef1f2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/6dd5f0f8ad77e22ca50b6445d392ed09627aa84c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/f01cfb1355e55dd1b4f293845dd5f685541a310d.png)

## 样例 #1

### 输入

```
2
4
3
0 1
2 1
1 3
0 3
2
1
0 1
1 0
```

### 输出

```
Case 1: 4
Case 2: 1
```



---

---
title: "Dominos 2"
layout: "post"
diff: 普及/提高-
pid: UVA11518
tag: ['搜索', '图论']
---

# Dominos 2

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2513

[PDF](https://uva.onlinejudge.org/external/115/p11518.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/7f28ab761227ecc0796512e3a227ad6b7d28229e.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/358c7d33d629af402b53bf37fed925488939a6c1.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/66db10874dbf273f4e15346e2df8aeb00eddd6c8.png)

## 样例 #1

### 输入

```
1
3 2 1
1 2
2 3
2
```

### 输出

```
2
```



---

---
title: "困难的串 Krypton Factor"
layout: "post"
diff: 普及/提高-
pid: UVA129
tag: ['搜索', '递归']
---

# 困难的串 Krypton Factor

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=65

[PDF](https://uva.onlinejudge.org/external/1/p129.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/acf4a8193efdffb3da55bab10c0c0b1353f2dc09.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/b923e93bcc47c02bfb54e49f8ec2dafc214ee3e7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/2bee9ae1cb76c0f477ce304cd2c16b191025d687.png)

## 样例 #1

### 输入

```
7 3
30 3
0 0
```

### 输出

```
ABAC ABA
7
ABAC ABCA CBAB CABA CABC ACBA CABA
28
```



---

---
title: "骑士的移动 Knight Moves"
layout: "post"
diff: 普及/提高-
pid: UVA439
tag: ['搜索', '广度优先搜索 BFS', '队列']
---

# 骑士的移动 Knight Moves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=380

[PDF](https://uva.onlinejudge.org/external/4/p439.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/49281f2a839995de267463a506fc7b04652bcf4a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/f986ca9c080d4c2fa5952f61f878eaafe27fdf4b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/e3265edbb46489790ff00e32193564840a6de7fe.png)

## 样例 #1

### 输入

```
e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6
```

### 输出

```
To get from e2 to e4 takes 2 knight moves.
To get from a1 to b2 takes 4 knight moves.
To get from b2 to c3 takes 2 knight moves.
To get from a1 to h8 takes 6 knight moves.
To get from a1 to h7 takes 5 knight moves.
To get from h8 to a1 takes 6 knight moves.
To get from b1 to c3 takes 1 knight moves.
To get from f6 to f6 takes 0 knight moves.
```



---

---
title: "素数环 Prime Ring Problem"
layout: "post"
diff: 普及/提高-
pid: UVA524
tag: ['搜索', '深度优先搜索 DFS', '素数判断,质数,筛法']
---

# 素数环 Prime Ring Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=465

[PDF](https://uva.onlinejudge.org/external/5/p524.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/5273edd790a23e1ad73d017fd355830ccb468915.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/564d6b149cca77cbaf1583cf2a35822a0f78251c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/3944acd7f0b0909cb25a01cbb113e5507c6e3a72.png)

## 样例 #1

### 输入

```
6
8
```

### 输出

```
Case 1:
1 4 3 2 5 6
1 6 5 2 3 4

Case 2:
1 2 3 8 5 6 7 4
1 2 5 8 3 4 7 6
1 4 7 6 5 8 3 2
1 6 7 4 3 8 5 2
```



---

---
title: "Dungeon Master"
layout: "post"
diff: 普及/提高-
pid: UVA532
tag: ['搜索', '广度优先搜索 BFS', '队列']
---

# Dungeon Master

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=473

[PDF](https://uva.onlinejudge.org/external/5/p532.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/f5204064f9aec4c41d412eb29fbc006dac1f717c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/bc032dafb23822eecdf0192d86ea58ddcaa98ec5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/30d36b3bfe984f90284eb870b4006708e8229767.png)

## 样例 #1

### 输入

```
3 4 5
S....
.###.
.##..
###.#
#####
#####
##.##
##...
#####
#####
#.###
####E
1 3 3
S##
#E#
###
0 0 0
```

### 输出

```
Escaped in 11 minute(s).
Trapped!
```



---

---
title: "Goldbach's Conjecture"
layout: "post"
diff: 普及/提高-
pid: UVA543
tag: ['搜索', '枚举', '素数判断,质数,筛法']
---

# Goldbach's Conjecture

## 题目描述

哥德巴赫猜想的内容如下：

任意一个大于 $4$ 的偶数都可以拆成两个奇质数之和。

比如：

$
\begin{aligned}
8&=3+5\\
20&=3+17=7+13\\
42&=5+37=11+31=13+29=19+23
\end{aligned}
$

你的任务是：验证小于 $10^6$ 的数满足哥德巴赫猜想。

## 输入格式

输入包含多组数据。

每组数据占一行，包含一个偶数 $n(n \le 10^6)$。 读入以 $0$ 结束。

## 输出格式

对于每组数据，输出形如 `n = a + b`，其中 $a,b$ 是奇质数。若有多组满足条件的 $a,b$，输出 $b−a$ 最大的一组。

若无解，输出 `Goldbach's conjecture is wrong.`。

## 样例 #1

### 输入

```
8
20
42
0
```

### 输出

```
8 = 3 + 5
20 = 3 + 17
42 = 5 + 37
```



---

