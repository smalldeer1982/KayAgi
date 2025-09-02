---
title: "Manhattan Wiring"
layout: "post"
diff: 省选/NOI-
pid: UVA1214
tag: ['动态规划 DP', '图论', '进制']
---

# Manhattan Wiring

## 题目描述

题目大意

n×m网格里有空格和障碍，还有两个2和两个3.要求把这两个2和两个3各用一条折线连起来，使得总长度尽量小（线必须穿过格子中心，每个单位正方形的边长为1）。

限制条件如下：障碍格里不能有线，而每个空格里最多只能有一条线。由此可知，两条折线不能相交，每条折线不能自交。

如图所示，折线总长度为18（2、2、3、3格子中各有一条长度0.5的线）。

## 输入格式

输入包含多组数据。每组数据的第一行为正整数n、m（1≤n，m≤9），以下n行每行为m个整数，描述该网格。0表示空格，1表示障碍，2表示写有“2”的格子，3表示写有“3”的格子。

## 输出格式

对于每组数据输出一行，输出两条折线最小总长度，如果无解，输出0。



---

---
title: "修缮长城 Fixing the Great Wall"
layout: "post"
diff: 省选/NOI-
pid: UVA1336
tag: ['动态规划 DP', '区间 DP', '前缀和']
---

# 修缮长城 Fixing the Great Wall

## 题目描述

为了简化这个问题，我们把长城看成是一条直线，每个需要修补的点都被用它离起点的距离（一个整数）标记了。GWARR被放在长城的一个随机位置上，并且可以以恒定的速度双向移动。每个点距离起点的距离，现在立即修复的花费，以及每过单位时间修复花费的增长量都已知。GWARR的工作效率极高，以至于它可以立即修复好经过的需要修复的地方。

## 输入格式

输入包含多组测试数据。每组测试数据的格式如下：
第一行包含$3$个整数$N, V, X$，分别表示点的数量，GWARR的移动速度，GWARR的出发点位置。  
接下来$n$行，每行$3$个整数$x,c,\Delta$，表示这个点的位置，现在立即修复的花费，以及每过单位时间修复花费的增长量。保证没有两个点的位置相同。  
输入以一行$N=V=X=0$作为结束标记。

## 输出格式

$N$行，每行一个整数，表示每组数据的最小总花费（**向下取整**），保证输出结果不超过$10^9$。

## 样例输入输出
### 样例输入\#1：
	3 1 1000
	1010 0 100
	998 0 300
	996 0 3
	3 1 1000
	1010 0 100
	998 0 3
	996 0 3
	0 0 0 
### 样例输出\#1：
	2084
    1138
### 样例输入输出解释：
对于第一种情况，我们选择先修复距离$998$处，花费$600$，然后是$1010$处，花费$1400$，然后是$996$处，花费$84$。合计$2084$。

由 @Sparky_14145 提供翻译

## 说明/提示

对于$100 \%$数据有：
$1 \leq N \leq 1000, 1 \leq V \leq 100,1 \leq X \leq 500,000$；  
$1 \leq x \leq 500,000, 1 \leq c \leq 50,000, 1 \leq \Delta \leq 50,000$。



---

---
title: "String painter"
layout: "post"
diff: 省选/NOI-
pid: UVA1437
tag: ['动态规划 DP']
---

# String painter

## 题目描述

有两个仅含有小写字母的等长字符串 $A$ 和 $B$，每次操作可以将 $A$ 的其中一个子串的所有位置修改为同一个任意字符。求将 $A$ 覆盖成  $B$ 的最小操作次数。

$1\le |a |=|b|\le100。$

## 输入格式

输入包含多组数据，每组数据由两行组成，第一行为字符串 $A$，第二行为字符串 $B$。

## 输出格式

对于每组数据，输出最小操作次数。

## 样例 #1

### 输入

```
hfcnndeziymohaewnrbmquyhigwm
bcbysbjvxbzvmspshggrzaukbipm
jmmeqimjobpxyavjneyvyuuhhwiqowmme
kmpgpviubhzrjkezqqoilsuwgedctxkxl
ikynfrlcsltkrbdkdqpirtdnajhzhbhipeqtyxvskhkti
qmziwxbbjzjfymrzvflthsbaqgdoqmiduiudviqzztclb
vwysgqniecydcycqk
cqgudqbkgcsvimpdj
mcrrqwfegpnukyuk
vezrniuriscgtcth
rdjtgk
wzfycu
nwxqfdtigwj
rrhcndwcohx
knjmrwlwxfroyppgxhrknntrvbcqjrranufutrginldqydsjsfyjqfyqq
lghrdjsgvbffgfpclqmrzzoniyhlsoisgpbfdqpiblsbtirrbdjdjxsuy
nujagihmgqvwiwvbmbe
pnxicvskosnzneztzhd
bzjvffvyv
mnvjbgwdw
```

### 输出

```
20
26
33
15
13
6
8
43
15
8
```



---

---
title: "独占访问2 Exclusive Access 2"
layout: "post"
diff: 省选/NOI-
pid: UVA1439
tag: ['动态规划 DP']
---

# 独占访问2 Exclusive Access 2

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4185

[PDF](https://uva.onlinejudge.org/external/14/p1439.pdf)

## 样例 #1

### 输入

```
2
P Q
R S
6
P Q
Q R
R S
S T
T U
U P
4
P Q
P Q
P Q
P Q
3
P Q
Q R
R P
6
P Q
Q S
S R
R P
P S
R Q
```

### 输出

```
0
P Q
R S
0
P Q
R Q
R S
T S
T U
P U
0
P Q
P Q
P Q
P Q
1
P Q
Q R
P R
2
P Q
Q S
R S
P R
P S
R Q
```



---

---
title: "Alice and Bob"
layout: "post"
diff: 省选/NOI-
pid: UVA1500
tag: ['动态规划 DP', '博弈论']
---

# Alice and Bob

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4246

[PDF](https://uva.onlinejudge.org/external/15/p1500.pdf)



---

---
title: "串折叠 Folding"
layout: "post"
diff: 省选/NOI-
pid: UVA1630
tag: ['字符串', '动态规划 DP']
---

# 串折叠 Folding

## 题目描述

折叠由大写字母组成的长度为 $n$（$1\leqslant n\leqslant100$）的一个字符串，使得其成为一个尽量短的字符串，例如 `AAAAAA` 变成 `6(A)`。

这个折叠是可以嵌套的，例如 `NEEEEERYESYESYESNEEEEERYESYESYES` 会变成 `2(N5(E)R3(YES))`。

多解时可以输出任意解。

Translated by @_UKE自动机_

## 输入格式

**输入有多组数据**。

输入若干行，第 $i$ 行有一个仅由大写字母组成的，长度小于等于 $100$ 的字符串。

## 输出格式

对于每组输入，输出折叠后的字符串。

多解时可以输出任意解。

## 样例 #1

### 输入

```
AAAAAAAAAABABABCCD
NEERCYESYESYESNEERCYESYESYES
```

### 输出

```
9(A)3(AB)CCD
2(NEERC3(YES))
```



---

