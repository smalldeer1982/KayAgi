---
title: "Find the Winning Move"
layout: "post"
diff: 普及+/提高
pid: UVA10111
tag: ['剪枝']
---

# Find the Winning Move

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1052

[PDF](https://uva.onlinejudge.org/external/101/p10111.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10111/ebca7c72e9448d503158b6014fa855835320092f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10111/9055d46ebcb6e4c4c06061fdb646c962c6876665.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10111/2157b9dc71543030f751fb8a407ef6974e47cc6d.png)

## 样例 #1

### 输入

```
?
....
.xo.
.ox.
....
?
o...
.ox.
.xxx
xooo
$
```

### 输出

```
#####
(0,1)
```



---

---
title: "Robots on Ice"
layout: "post"
diff: 普及+/提高
pid: UVA1098
tag: ['搜索', '剪枝']
---

# Robots on Ice

## 题目描述

受哈尔滨冰雕的启发，来自北极机器人与自动机大学的参赛队员决定程序竞赛结束后在校园内举办自己的冰雪节。他们打算在冬天结冰的时候，从学校附近的一个湖里获取冰块。为了便于监测湖中冰层的厚度，他们先将湖面网格化，然后安置一个轻巧的机器人逐个方格测量冰层的厚度。在网格中有三个特殊方格被指定为“检查点”，对应着机器人在检查过程中经过整个行程的四分之一、二分之一、四分之三的位置，机器人在这三个特殊“检查点”会发送相应的进度报告。为了避免对冰面造成不必要的磨损和划痕而影响后续的使用，机器人需要从网格左下角坐标为 $(0，0)$ 的方格出发，经过所有方格仅且一次，然后返回位于坐标为 $(0，1)$ 的方格。如果有多种路线符合要求，则机器人每天会使用一条不同的路线。机器人只能沿北、南、东、西四个方向每次移动一个方格。  
给定网格的大小和三个检查点的位置，编写程序确定有多少种不同的检查路线。例如，湖面被划分为 $3 \times 6$ 的网格，三个检查点按访问的顺序分别为 $(2，1)，(2，4)$ 和 $(0，4)$，机器人必须从 $(0，0)$ 方格开始，路经 $18$ 个方格，最后终止于 $(0，1)$ 方格。机器人必须在第 $4（＝\left\lfloor\dfrac{18}{4}\right\rfloor）$ 步的时候经过 $(2，1)$ 方格，在第 $9（＝\left\lfloor\dfrac{18}{2}\right\rfloor）$ 步的时候经过 $(2，4)$ 方格，第 $13（＝\left\lfloor\dfrac{3 \times 18}{4}\right\rfloor）$ 步的时候经过 $(0，4)$ 方格，只有两种路线符合要求，如下图所示。  
![UVA1098 Robots on Ice](https://cdn.luogu.com.cn/upload/image_hosting/vy6tphyl.png)  
需要注意：（1）当网格的大小不是 $4$ 的倍数时，在计算步数时使用整除；（2）某些情况下可能不存在符合要求的路线，例如给定一个 $4 \times 3$的网格，三个检查点分别为 $(2，0)，(3，2)$ 和 $(0，2)$，那么将不存在从 $(0，0)$ 方格出发，结束于 $(0，1)$ 方格且满足要求的路线。

## 输入格式

**本题有多组数据**。  
每组测试数据的第一行包含两个整数 $m$ 和 $n（2 \leq m，n \leq 8）$，表示网格的行数和列数，接着的一行包含六个整数 $r_1，c_1，r_2，c_2，r_3，c_3$，其中 $0 \leq ri ＜ m，0 \leq c_i ＜ n（i＝1，2，3）$。输入的最后一行包含两个 $0$。

## 输出格式

从 $1$ 开始输出测试数据的组数，输出以下不同路线的数量：机器人从行 $0$ 列 $0$ 出发，在行 $0$ 列 $1$ 结束，在第 $\left\lfloor\dfrac{i \times m \times n}{4}\right\rfloor$ 步时经过行 $r_i$ 和列 $c_i（i＝1，2，3）$，能够路经所有方格仅且一次的路线。



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

