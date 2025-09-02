# [EC Final 2021] Check Pattern is Good

## 题目描述

教授 Shou 得到了一个 $(n \times m)$ 的棋盘。一些格子被涂成了黑色，一些被涂成了白色，还有一些没有上色。

教授 Shou 喜欢**棋盘图案**，所以他想给所有未上色的格子涂色，并最大化棋盘上的棋盘图案数量。

如果四个形成一个 $(2 \times 2)$ 方格的单元格以以下任一种方式上色，则说它们形成了一个棋盘图案：

`BW `

`WB`

或者

`WB `

`BW`

这里的 `W`（在奇瓦语中是“wakuda”，意为黑色）表示格子被涂成了黑色，而 `B`（在科西嘉语中是“biancu”，意为白色）表示格子被涂成了白色。

## 样例 #1

### 输入

```
3
2 2
??
??
3 3
BW?
W?B
?BW
3 3
BW?
W?W
?W?
```

### 输出

```
1
WB
BW
1
BWB
WWB
BBW
4
BWB
WBW
BWB
```

# 题解

## 作者：liangbowen (赞：7)

update 2024/6/17：修改了一处笔误。

[blog](https://www.cnblogs.com/liangbowen/p/17870924.html)。找网络流水题写题解 /hsh。

---

间隔染色（$i+j$ 分奇偶染不同色）后，所有 $i+j$ 为奇数的格子反色，题目的 Pattern 等价于是 $2\times2$ 的全黑或全白格子。

然后很自然地想 Flow 了。每个点分黑白两种状态。

+ 如果 $(x,y)$ 对应的 Pattern 有机会染成全黑，就连边 $S\xrightarrow{1} \operatorname{Black}(x,y)$。流这条边表示 $(x,y)$ 染成全黑。
+ 如果 $(x,y)$ 对应的 Pattern 有机会染成全白，就连边 $\operatorname{White}(x,y)\xrightarrow{1} T$。流这条边表示 $(x,y)$ 染成全白。
+ 将所有相邻的 $\operatorname{Black}(x,y)\xrightarrow{+\infty}\operatorname{White}(x_0,y_0)$。限制不能同时将一个点染成黑色与白色。

这个本质是[二者选一式问题](https://www.luogu.com.cn/problem/P1361)，所以答案是总数减去最小割。

求方案的话，先 DFS 求出那些边是没有被割掉的，然后直接覆盖上全黑 / 全白即可。输出记得把格子重新反色回去。

[code](https://www.luogu.com.cn/paste/ffrn37o8)，时间复杂度 $O(\text{能过})$，反正 10.00s 随便冲。

---

## 作者：zheng_zx (赞：0)

## P9879 [EC Final 2021] Check Pattern is Good

[题目传送门](https://www.luogu.com.cn/problem/P9879)

### 分析

---

一道网络流~~水~~题。

先把各自按奇偶反色，然后就变成要最多的全黑或全白；

建立一个两侧各是 $n \times n$ 的二分图，

左边表示将这个小矩形，右边表示将这个小矩形染成黑色；

相交的黑白小矩形之间连接 $inf$；

- 如果还有希望变白的小矩形，就让 $s$ 连到它，流量为 $1$。

- 如果还有希望变黑的小矩形，就让它连到 $t$，流量为 $1$。

跑最小割就可以了不难感受到这种建图的正确性。

---

