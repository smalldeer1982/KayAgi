---
title: "KOZE - Sheep"
layout: "post"
diff: 普及/提高-
pid: SP12880
tag: ['广度优先搜索 BFS', '队列']
---

# KOZE - Sheep

## 题目描述

$a$ 行 $b$ 列（$3 \leq a,b \leq250$）的矩阵中：

- 字符 `.` 表示空白字段。

- 字符 `#` 表示一个围栏。

- 字符 `k` 代表绵羊。

- 字符 `v` 代表狼。

狼和羊存活的规则为：
1. 如果一片区域中羊比狼多，全部狼会死掉，**否则**全部羊会死掉。

2. 如果一个地方可以不通过围栏走出矩阵，该地区羊和狼**都会存活**。

求最后能有几只羊与狼。

## 输入格式

第1行：两个由空格分开的整数，R ,C (3≤R ,C≤250) 代表院子的长与宽；
      第2到R+1行: 给出院子情况图。

## 输出格式

仅一行，输出院子里最后会有几只羊与狼的数目，先输出羊，中间用一个空格格开。

【样例】
koze.in
8 8 
.######. 
#..k...# 
#.####.# 
#.#v.#.# 
#.#.k#k# 
#k.##..# 
#.v..v.# 
.######.	koze.out
3  1


【试题来源】
本题来源于克罗地亚2005年分区赛高年级组第三题，翻译来源于海州高中。

## 样例 #1

### 输入

```
\n8 8  \n.######.  \n#..k...#  \n#.####.#  \n#.#v.#.#  \n#.#.k#k#  \n#k.##..#  \n#.v..v.#  \n.######.
```

### 输出

```
3 1
```



---

---
title: "最近公共祖先（LCA）"
layout: "post"
diff: 普及/提高-
pid: SP14932
tag: ['搜索', '倍增', '最近公共祖先 LCA']
---

# 最近公共祖先（LCA）

## 题目描述

> 树是一种简单无向图，图中任意两个节点仅被一条边连接。所有连通无环无向图都是一棵树。
>
> 最近公共祖先（LCA）是图论和计算机科学中的一个概念。设 $\text{T}$ 是一个有 $N$ 个节点的有根树，树上有两个节点 $v$ 和 $w$，而这两个节点的最近公共祖先是 $u$，那么 $u$ 是 $v$ 和 $w$ 在 $\text{T}$ 上的祖先（允许自己是自己的祖先），且在满足上面的前提的所有节点中，其在 $T$ 上的高度最低。
> 
>——摘自维基百科

现在，你需要对于给定的树 $\text{T}$ 以及两个节点 $v$ 和 $w$，求出它们的最近公共祖先。

如下图所示，图中 $9$ 号节点与 $12$ 号节点的最近公共祖先为 $3$ 号节点。

![](https://cdn.luogu.org/upload/vjudge_pic/SP14932/0b23f0487b06b8d674d23253a6db517f49ca3acf.png)

## 输入格式

输入共有 $T$ 组数据。

对于每一组数据：  
第一行输入一个整数 $N$ 表示节点个数（节点编号为 $1 \to N$ 中的一个数字）。  
接下来 $N$ 行，每行开头是一个整数 $M_i$，表示 $i$ 号节点的子节点数量，后面的 $M_i$ 个整数分别表示子节点编号。  
随后一行输入一个整数 $Q$，表示询问的 $v_i$ 及 $w_i$ 的组数。  
最后 $Q$ 行，每行输入两个整数 $v_i$ 和 $w_i$，代表要询问的两个节点。

## 输出格式

输出共有 $T$ 组数据。

对于每一组数据：  
第一行输出一个形如 `Case X:` 的字符串，其中的 `X` 表示第几组数据。  
接下来 $Q$ 行（每组数据不一），输出每组 $v_i$ 和 $w_i$ 的最近公共祖先。

## 说明/提示

### 样例解释

**样例输入 1**

```plain
1
7
3 2 3 4
0
3 5 6 7
0
0
0
0
2
5 7
2 7
```

**样例输出 1**

```plain
Case 1:
3
1
```

此样例在【题目描述】中有解释。

### 数据范围

对于 $100\%$ 的数据，$1 \le N \le 1000,0 \le M \le N - 1,1 \le Q \le 1000$。



---

---
title: "ABCDEF - ABCDEF"
layout: "post"
diff: 普及/提高-
pid: SP4580
tag: ['搜索', '枚举']
---

# ABCDEF - ABCDEF

## 题目描述

You are given a set S of integers between -30000 and 30000 (inclusive).

Find the total number of sextuples ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/60da4a6ec7452a0168508bec756f9c6a0109d346.png) that satisfy:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/5ae23b14079f628cec1090fc74b452939c2ffbe4.png)

### Input

The first line contains integer N (1

Elements of S are given in the next N lines, one integer per line. Given numbers will be distinct.

## 输出格式

Output the total number of plausible sextuples.

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
2
3

```

### 输出

```
4
```

## 样例 #3

### 输入

```
2
-1
1

```

### 输出

```
24
```

## 样例 #4

### 输入

```
3
5
7
10

```

### 输出

```
10
```



---

---
title: "SHOP - Shopping"
layout: "post"
diff: 普及/提高-
pid: SP96
tag: ['广度优先搜索 BFS']
---

# SHOP - Shopping

## 题目描述

![Crowd in the supermarket](https://cdn.luogu.com.cn/upload/vjudge_pic/SP96/df9f7ec95f8af0b2332c4f2457bc0d39793311a7.png)The old tube screen to your computer turned out to be the cause of your chronic headaches. You therefore decide to buy one of these new flat TFT monitors. At the entrance of the computer shop you see that it is quite full with customers.

In fact, the shop is rather packed with customers and moving inside involves a certain amount of elbowing. Since you want to return home quickly to complete your half finished SPOJ tasks, you want to sidestep the crowd as much as possible. You examine the situation somewhat closer and realise that the crowding is less in some parts of the shop. Thus, there is reason for hope that you can reach your goal in due time, provided that you take the shortest way. But which way is the shortest way?

You sketch the situation on a piece of paper but even so, it is still a tricky affair. You take out your notebook from your pocket and start to write a program which will find the shortest way for you.

## 输入格式

The first line of the input specifies the width w and height h of the shop. Neither dimension exceeds 25.

The following h lines contain w characters each. A letter X symbolises a shelf, the letter S marks your starting position, and the letter D marks the destination (i.e. the square in front of the monitors). All free squares are marked with a digit from 1 to 9, meaning the number of seconds needed to pass this square.

There are many test cases separated by an empty line. Input terminates with width and height equal 0 0.

## 输出格式

Your program is to output the minimum number of seconds needed to reach to destination square. Each test case in a separate line. Movements can only be vertical and horizontal. Of course, all movements must take place inside the grid. There will always be a way to reach the destination.

## 样例 #1

### 输入

```
4 3

X1S3

42X4

X1D2



5 5

S5213

2X2X5

51248

4X4X2

1445D



0 0
```

### 输出

```
4

23
```



---

