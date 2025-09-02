---
title: "HAREFOX - Hares and Foxes"
layout: "post"
diff: 难度0
pid: SP49
tag: []
---

# HAREFOX - Hares and Foxes

## 题目描述

Malidinesia对二元生态系统（野兔和狐狸之间吃与被吃的关系，本题的SHF系统）产生了浓厚的兴趣。于是，他决定研究那个生态系统。而你此刻就是他的手下。

Malidinesia需要你，一个程序员办一件事：

>写一个程序，来在实验时模拟这个生态系统。

你已知这个生态系统(SHF)的方程组如下：

>$h_{y+1}=a.h_y-b.f_y$
>
>$f_{y+1}=c.f_y+d.h_y$

（$h_y$和$f_y$均为实数）

其中， $h_y resp.f_y$代表第$y$年内野兔(Hares)和狐狸(fox)的差异。这也是实验开始时的初始计数。现在请你编写一个程序，确定SHF系统的长期演变。

## 输入格式

第一行：一个整数n，表示有n组需要你进行实验的数据

接下来：输入案例。案例由六个实数$a,b,c,d,h_{1998},f_{1998}$组成。每行两个数字，用空格分隔。数字可能是浮点型，由不超过10个字符构成。

## 输出格式

一共有六种可能：

1.Ecological balance will develop. (生态系统将会维持平衡，即 $i.e. lim, h _{y} y=0 $)

2.Hares will die out while foxes will overgrow.(野兔死掉，狐狸疯长，如果经过足够长的时间，野兔的数量会增加。狐狸属于resp.超过任何先验给定的阈值,即 i.e. lim $h _{y}$ =-infinity 且 lim $f _{y}$ 
y=+infinit)

3.Hares will overgrow while foxes will die out.（狐狸死掉，野兔疯长，如果经过足够长的时间，狐狸的数量会增加。野兔属于resp.超过任何先验给定的,即阈值i.e. lim $h _{y}$ =+infinity 且 lim $f _{y}$ =-infinity）

4.Both hares and foxes will die out.（他们都得死， 如果在足够长的时间之后，野兔和狐狸的数量都落在任何先验给定的阈值之下，即 i.e. lim $h _{y}$ =-infinity 且 lim $f _{y}$ =-infinity）

5.Both hares and foxes will overgrow.（都过度生长，即 i.e. lim $h _{y}$ =+infinity and lim $f _{y}$ =+infinity）

6.Chaos will develop.（混乱，即以上描述均不符合）

## 样例 #1

### 输入

```
2
2 0.5
0.5 0.6
2 3

0.1 1 
2 0.1
1 1
```

### 输出

```
Both hares and foxes will overgrow.
Hares will die out while foxes will overgrow.
```

