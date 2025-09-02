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
title: "树 Tree"
layout: "post"
diff: 普及+/提高
pid: UVA548
tag: ['搜索', '递归', '深度优先搜索 DFS', '构造']
---

# 树 Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=489

[PDF](https://uva.onlinejudge.org/external/5/p548.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/78473d26dddbe5f8314b7aac17e37af6d9c18840.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/d5af82d5dd26aa1f11be5b3e1cfa80708b9d2173.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/235ec8eb49fbab76e59891f6d6b4f6deb21da67a.png)

## 样例 #1

### 输入

```
3 2 1 4 5 7 6
3 1 2 5 6 7 4
7 8 11 3 5 16 12 18
8 3 11 7 16 18 12 5
255
255
```

### 输出

```
1
3
255
```



---

