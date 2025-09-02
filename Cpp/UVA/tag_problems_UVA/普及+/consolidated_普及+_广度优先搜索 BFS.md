---
title: "Full Tank?"
layout: "post"
diff: 普及+/提高
pid: UVA11367
tag: ['广度优先搜索 BFS', '优先队列', '队列']
---

# Full Tank?

## 题目描述

有 $N$ 个城市和 $M$ 条道路，构成一条无向图。

在每个城市都有一个加油站，不同的加油站的价格都不一样。

通过一条道路的油耗就是该道路的边权。

现在你需要回答 $q$ 个问题，在每个问题中，请计算出一辆油箱容量为 $c$ 的，起始时油箱为空的车子，从起点 $s$ 到终点 $e$ 至少要花多少钱。

## 输入格式

第一行两个整数城市数 $N(1 \leq N \leq 1000)$，道路数$M(0 \leq M \leq 10000)$。

接下来 $N$ 个整数为每个城市的油的价格 $p_i(1 \leq p_i \leq 100)$。

接下来 $M$ 行每行三个整数$u,v,d$，描述 $u$ 城市到 $v$ 城市 $(0 \leq u,v < N)$ 有一条油耗为 $d(1 \leq d \leq 100)$ 的道路。

接下来的一个整数 $q(1 \leq q \leq 100)$ 为询问数量。

接下来的 $q$ 行每行三个整数 $c,s,e$。询问一辆容量为 $c$ 的车从 $s$ 城市到 $e$ 城市至少要花多少钱。

题目满足 $1 \leq c \leq 100$。

## 输出格式

对于每个询问，每一行回答一个数，为至少花费的钱。如果不能到达，输出`impossible`。

## 样例 #1

### 输入

```
5 5
10 10 20 12 13
0 1 9
0 2 8
1 2 1
1 3 11
2 3 7
2
10 0 3
20 1 4
```

### 输出

```
170
impossible
```



---

---
title: "Ocean Currents"
layout: "post"
diff: 普及+/提高
pid: UVA11573
tag: ['广度优先搜索 BFS']
---

# Ocean Currents

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2620

[PDF](https://uva.onlinejudge.org/external/115/p11573.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/d1e2b8169cdc10fcb6efb334ec4201d016849d2c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/d920afe01202359d2e8d70a7653121b90d9c46b7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/a0f8203bb0b484bf784b764bfe0ccec8f2b61d46.png)

## 样例 #1

### 输入

```
5 5
04125
03355
64734
72377
02062
3
4 2 4 2
4 5 1 4
5 3 3 4
```

### 输出

```
0
2
1
```



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

