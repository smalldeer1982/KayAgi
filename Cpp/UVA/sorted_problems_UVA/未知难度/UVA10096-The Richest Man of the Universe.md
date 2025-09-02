---
title: "The Richest Man of the Universe"
layout: "post"
diff: 难度0
pid: UVA10096
tag: []
---

# The Richest Man of the Universe

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=1037

[PDF](https://uva.onlinejudge.org/external/100/p10096.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10096/b5c735ba86039b12a05a5e7884c12f4acf62941f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10096/1a7bedcf97dcf6d0f287432fcaecba607a395ce0.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10096/b6c0adacf65eb75c3ea1568417f40f38e6951618.png)

## 说明/提示

距离地球 200 光年的阿卡迪亚星球有一个叫 Charge Doors 的人。这个名字听上去很奇怪，但如果你很聪明，你会发现他名字中的秘密。他很可能毕业于现今最好的药学学校（你可能好奇为什么你不知道这个学校，这是因为消息来自阿卡迪亚，你将在 200 年后得知）。虽然他是个及其出色的程序员，但奇怪的是，他在大学的大部分时间都在病毒实验室度过（也许他的朋友知道这个原因）。他在那里研究一种叫 ”Archadian Bascillae“ 的病毒，这种病毒是圆形的。

它们可以在繁殖季节发生 **分裂**，在敌对季节发生 **融合**。

- 在繁殖季节，每个病毒都被保存在一个 **长方形** 盒子里，每个病毒将分裂为两个 **大小** 和 **形状** 相同的病毒，分裂后的 **两个病毒面积和** 与 **原病毒面积** 相等。分裂后，它们将在盒子中保持 **尽可能远的距离**，现在你知道 **原病毒的半径** 和 **盒子的大小（长宽）**，你需要确定分裂后 **两病毒中心的距离**。

- 在敌对季节，**融合**过程中，两个病毒将会合并在一起，**但并不完全**。具体来说，一个病毒的会和另一个病毒部分重叠，他们共同部分的厚度将会加倍，其他部分 **形状**与厚度均**不变**（这种情况就像两个刚性磁盘被粘在一起）。它们的大小可能不同，而你需要确定这些 **半合并病毒所覆盖的区域**。

  **你将要参加他的大型软件公司的面试，所以你必须解决这些问题**。



**形式化的说**，**你需要解决两个问题：**

-  第一个问题 给出**一个圆**和一个矩形，圆会分裂为两个**相同的新圆**，两圆的面积和等于原来的圆，并且会在这个矩形里保持**两圆圆心的距离最大**。如果两个圆**不重叠**，输出**两圆圆心的距离**，否则输出 `Not enough space for fission.`。

  \- 第二个问题 给出两个圆 $C_1,C_2$ 和**圆心的距离**，求 $\dfrac{S_{C_1 \cap C_2}}{S_{C_1}+S_{C_2}}$。如果结果为 $1.0000$ 还要输出 `No compaction has occurred.`。

  所有实数保留**四位小数**，每组数据**多输出一个换行**。

## 样例 #1

### 输入

```
4
S 10.1 10.1 1
M 5 5 8
S 10 5 20
M 5 5 15
```

### 输出

```
12.2836
0.9480
Not enough space for fission.
1.0000
No compaction has occurred.
```

