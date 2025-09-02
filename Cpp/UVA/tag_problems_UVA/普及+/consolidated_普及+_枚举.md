---
title: "Power Strings"
layout: "post"
diff: 普及+/提高
pid: UVA10298
tag: ['字符串', '枚举', 'KMP 算法']
---

# Power Strings

## 题目描述

### 题意简述：

求一个字符串最多由多少个重复的子串连接而成。

例如 `ababab` 由三个 `ab` 连接而成，`abcd` 由一个 `abcd` 连接而成。

## 输入格式

**本题多组数据**。

每一组数据仅有一行，这一行仅有一个字符串 $s$。

输入的结束标志为一个 `.`。

## 输出格式

对于每一组数据，输出这组字符串最多由多少个重复的子串连接而成。

## 说明/提示

$1\le |s|\le 10^6$。

## 样例 #1

### 输入

```
abcd
aaaa
ababab
.
```

### 输出

```
1
4
3
```



---

---
title: "The Lottery"
layout: "post"
diff: 普及+/提高
pid: UVA10325
tag: ['枚举', '容斥原理', '概率论']
---

# The Lottery

## 题目描述

给出 $n , m$，和 $m$ 个数 $a[1] \cdots a[m]$。

求 $1 \cdots n$ 中不被 $a[1] \cdots a[m]$ 中任意一个整除的数的个数。

## 输入格式

每组数据以 $n , m$ 为第一行。

第二行 $m$ 个数，表示 $a[i]$。

输入文件以 EOF 结尾。

## 输出格式

每组数据一行一个数字表示答案。

### 数据规模及约定

$ 10 \leqslant n < 2^{31} , m \leqslant 15$。

## 样例 #1

### 输入

```
10 2
2 3
20 2
2 4
```

### 输出

```
3
10
```



---

---
title: "Polynomial GCD"
layout: "post"
diff: 普及+/提高
pid: UVA10951
tag: ['多项式', '枚举', '最大公约数 gcd']
---

# Polynomial GCD

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1892

[PDF](https://uva.onlinejudge.org/external/109/p10951.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10951/27f28d739e35835743ed24591d9545837d82f420.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10951/360b18a2c9c0ae5abe1a36e006ef5f0c115af329.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10951/7ec15d368dfaec2cc7886207c522c4ae00b6990f.png)

## 样例 #1

### 输入

```
3
3 2 2 1 1
4 1 0 2 2 2
0
```

### 输出

```
Case 1: 2 1 2 1
```



---

---
title: "条件概率 Probability|Given"
layout: "post"
diff: 普及+/提高
pid: UVA11181
tag: ['搜索', '递推', '枚举', '深度优先搜索 DFS']
---

# 条件概率 Probability|Given

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2122

[PDF](https://uva.onlinejudge.org/external/111/p11181.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/e7ff179b70470ecd5bcdd2c359c9dec606f308e3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/c4a19b7e08ff7186da01119426d98cce50c64096.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/67d5194f9e66ef7ce5d79ddcd6cfb38fc83c93ca.png)

## 样例 #1

### 输入

```
3 2
0.10
0.20
0.30
5 1
0.10
0.10
0.10
0.10
0.10
0 0
```

### 输出

```
Case 1:
0.413043
0.739130
0.847826
Case 2:
0.200000
0.200000
0.200000
0.200000
0.200000
```



---

---
title: "和为 0 的 4 个值 4 Values whose Sum is 0"
layout: "post"
diff: 普及+/提高
pid: UVA1152
tag: ['二分', '枚举', '排序']
---

# 和为 0 的 4 个值 4 Values whose Sum is 0

## 题目描述

给出四个数组  $A,B,C,D$ ，每个数组中有  $n$  个整数。求有多少组  $i,j,k,l$  满足  $A_i+B_j+C_k+D_l=0$ 。

## 输入格式

**本题有多组测试数据。**

第一行一个正整数  $T$ ，表示数据组数。

对于每组数据:

第一行一个整数  $n$ 。

接下来  $n$  行，一行四个整数，分别表示  $A_i,B_i,C_i,D_i$ 。

## 输出格式

共  $2\times T$  行。

对于每组数据：

第一行一个整数，表示该组测试数据的答案。

接下来输出一个空行。

## 说明/提示

$1\le n\le4000$ 。数组中所有数的绝对值不大于  $2^{28}$ 。



---

---
title: "Chess Queen"
layout: "post"
diff: 普及+/提高
pid: UVA11538
tag: ['数学', '枚举', '组合数学']
---

# Chess Queen

## 题目描述

你一定知道国际象棋是怎么玩的，以及皇后是怎么运作的吧。如果两个皇后在同一列，同一行或者同一对角线上，她们就会互相攻击。

例如，有两个皇后（一白一黑）放置在$2×2$的棋盘上，那么有$12$中放置方式可以使她们互相攻击。如下图所示。（见PDF版题面）

给出棋盘的大小，请你计算有多少种放置皇后的方式，可以使她们互相攻击。

## 输入格式

输入文件包含至多$5,000$行，每行包含两个非负整数$M,N(1< M,N \leq 10^6 )$，表示棋盘的规格为$M × N$。输入以$M=N=0$结束。

## 输出格式

对每组数据输出一行，表示可以使两个皇后互相攻击的放置方案数。

保证答案在$64$位有符号整数范围内。

Translation provided by @Zaoaa

## 样例 #1

### 输入

```
2 2
100 223
2300 1000
0 0
```

### 输出

```
12
10907100
11514134000
```



---

---
title: "Benefit"
layout: "post"
diff: 普及+/提高
pid: UVA11889
tag: ['数学', '数论', '枚举', '最大公约数 gcd']
---

# Benefit

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=226&page=show_problem&problem=2989

[PDF](https://uva.onlinejudge.org/external/118/p11889.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/1588740ad2fa4cdc66ad2b07066e440857631a2c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/f5b692d330a8fdf0363839f65b9e9c8828b4274a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/3a5d4ba6e6d358c9a17c026a907c021a72350aa8.png)

## 样例 #1

### 输入

```
3
2 6
32 1760
7 16
```

### 输出

```
3
55
NO SOLUTION
```



---

---
title: "密码 Password"
layout: "post"
diff: 普及+/提高
pid: UVA1262
tag: ['递归', '枚举', '深度优先搜索 DFS']
---

# 密码 Password

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3703

[PDF](https://uva.onlinejudge.org/external/12/p1262.pdf)



---

---
title: "Hypertransmission"
layout: "post"
diff: 普及+/提高
pid: UVA1325
tag: ['枚举', '排序']
---

# Hypertransmission

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4071

[PDF](https://uva.onlinejudge.org/external/13/p1325.pdf)



---

---
title: "Exploring Pyramids"
layout: "post"
diff: 普及+/提高
pid: UVA1362
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS', '区间 DP']
---

# Exploring Pyramids

## 题目描述

虽然探索金字塔是极其老套的剧情，但是有一队探险家还是到了某金字塔脚下。

经过多年的研究，科学家对这座金字塔的内部结构已经有所了解。

首先，金字塔由若干房间组成，房间之间连有通道。

如果把房间看作节点，通道看作边的话，整个金字塔呈现一个有根树结构，节点的子树之间有序，金字塔有唯一的一个入口通向树根。

并且，每个房间的墙壁都涂有若干种颜色的一种。

探险队员打算进一步了解金字塔的结构，为此，他们使用了一种特殊设计的机器人。

这种机器人会从入口进入金字塔，之后对金字塔进行深度优先遍历。

机器人每进入一个房间（无论是第一次进入还是返回），都会记录这个房间的颜色。

最后，机器人会从入口退出金字塔。

显然，机器人会访问每个房间至少一次，并且穿越每条通道恰好两次（两个方向各一次）， 然后，机器人会得到一个颜色序列。

但是，探险队员发现这个颜色序列并不能唯一确定金字塔的结构。

现在他们想请你帮助他们计算，对于一个给定的颜色序列，有多少种可能的结构会得到这个序列。

因为结果可能会非常大，你只需要输出答案对 $10^9$ 取模之后的值。

## 输入格式

输入包含多组测试数据。

对于每组测试数据：输入一行，包含一个字符串 $S$，长度不超过 $300$，表示机器人得到的颜色序列。

## 输出格式

对于每组测试数据：输出一行，一个整数表示答案。

## 样例 #1

### 输入

```
ABABABA
AB
```

### 输出

```
5
0
```



---

---
title: "Ping pong"
layout: "post"
diff: 普及+/提高
pid: UVA1428
tag: ['树状数组', '枚举']
---

# Ping pong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4174

[PDF](https://uva.onlinejudge.org/external/14/p1428.pdf)



---

---
title: "Keyboarding"
layout: "post"
diff: 普及+/提高
pid: UVA1714
tag: ['字符串', '枚举', '广度优先搜索 BFS']
---

# Keyboarding

## 题目描述

## 题目背景

输入一条信息需要敲几下键？或许你会认为它相当于文本中的字符数，但只有在按键与字符一一对应时方才如此。对于小型设备来说，输入文本通常很麻烦。有些设备只提供几个按钮，比字符数量少得多。对于这样的设备，键入一个字符就需要一系列操作。

现在就有一套这样的输入机制：屏幕虚拟键盘，上面有一个光标，可以在键与键来回移动来选择字符。四个箭头按钮控制光标的移动，当光标的位置在合适的虚拟键上时，按确认按钮即可输入相应的字符，且在文本的末尾必须回车。


现在给你一段字符串，并且你只有「上、下、左、右，确认」这五个按钮。本题中，你会得到一个虚拟键盘布局。你的任务是确定键入给定文本所需的最少操作数，按下一个按钮即视为一次操作。虚拟键分布在一个矩形网格中，这样每个虚拟键占用网格中一个或多个相连的单元方格。光标初始均在左上角并可四向移动，且每次都沿该方向移到下一个不同字符的虚拟键。光标不能移动到无效的格上。

每个虚拟键与字符唯一对应，其由一个或多个方格组成，这些方格相连为一块区域。

## 输入格式

**本题有多组数据**。

对于每组数据：

第一行三个整数 $n,m,k$，分别为虚拟键盘网格的行数和列数。

接下来 $r$ 行，每行 $c$ 个字符，为大写字母、数字、横杠或星号（表示回车键）其中之一。

最后一行为一个非空字符串，是要输入的文本，最多有10000个除星号外的有效字符。

## 输出格式

对于每组数据，输出键入整个文本所需的最少操作数，**包括最后按下的回车**。

## 样例

### 样例输入

```text
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB
```

### 样例输出

```text
30
160
19
7
```

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/uvrfluzd.png)

插图描述了一种经过30次操作后输入 `CONTEST` 的方式，红点表示按下该虚拟键。

#### 数据规模

- $1\le r,c\le50,|S|\le 100001\le r,c\le 50,|S|\le 10000$。
---
翻译: @QQzhi (UID:525682)



---

---
title: "小木棍 Sticks"
layout: "post"
diff: 普及+/提高
pid: UVA307
tag: ['搜索', '枚举', '剪枝']
---

# 小木棍 Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=243

[PDF](https://uva.onlinejudge.org/external/3/p307.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/c2647a7ca09eb1b551716900d2c482623b1264d7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/10cd3e738e54e4609c2084fe79f07f05c056540d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/4fe73bdc6626222b0f15df6a62fe404a56935dc3.png)

## 样例 #1

### 输入

```
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0
```

### 输出

```
6
5
```



---

