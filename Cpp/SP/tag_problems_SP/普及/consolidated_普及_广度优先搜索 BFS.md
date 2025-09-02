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

