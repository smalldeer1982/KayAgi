---
title: "Clock Patience"
layout: "post"
diff: 普及-
pid: UVA170
tag: ['模拟', '栈', '队列']
---

# Clock Patience

## 题目描述

Card sharp Albert (Foxy) Smith 正在写一本有关于耐心游戏的书。为了仔细检查书中的例子，他正在编写程序以找到最佳玩法。

一个叫做 Clock Patience 的游戏的描述如下：

扑克牌面朝下按顺时针方向绕一个圆形发牌，代表一个时钟。每个小时上有一堆卡片，时钟中心还有一堆额外的卡片。第一张牌放在一点钟的位置，第二张放在两点钟，依此类推，顺时针方向放置，每第十三张牌放到时钟的中心。这就形成了十三堆，每堆里有四张牌是面朝下的。（下文中用 T 来代替 $10$）
![](https://cdn.luogu.com.cn/upload/image_hosting/zxlzflxl.png)

发完牌后游戏开始。K 牌堆的顶牌（即最后一张发的牌）作为当前牌。此后按照如下方式进行：

1. 将当前牌翻开，放在其点数对应的牌堆的最下面。
2. 当前牌堆的最上面的牌成为新的当前牌。
3. 如果当前牌正面朝上，游戏结束。

现在写一个程序，输入一叠被打乱的牌，然后玩这个游戏。

## 输入格式

（译者注：虽然原题面没提及，但根据译者的尝试，此题应该有多组测试数据）

此题有多组测试数据，每一个测试数据包含 $4$ 行，每行有 $13$ 张牌，每场牌用两个字母表示。第一个字母表示点数（用 T 来代替 $10$），第二个字母表示花色。输入是倒序输入的，因此放的第一张牌就是输入的最后一张牌。

输入以一行 ```#``` 结束。

## 输出格式

对于每一个测试数据输出一行。

每一行先包含一个数字，表示总共翻开了多少张牌。数字有两位，必要时在前面补 ```0```。接着紧接着是一个 ```,```，和最后的当前牌（按照输入的格式输出）。

## 样例 #1

### 输入

```
TS QC 8S 8D QH 2D 3H KH 9H 2H TH KS KC
9D JH 7H JD 2S QS TD 2C 4H 5H AD 4D 5D
6D 4S 9S 5S 7S JS 8H 3D 8C 3S 4C 6S 9C
AS 7C AH 6H KD JC 7D AC 5C TC QD 6C 3C
#
```

### 输出

```
44,KD
```



---

---
title: "铁轨 Rails"
layout: "post"
diff: 普及-
pid: UVA514
tag: ['模拟', '栈']
---

# 铁轨 Rails

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=455

[PDF](https://uva.onlinejudge.org/external/5/p514.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/a8f0af9a2adeaeaab1d1906c3f3116afa0c6b444.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/03b4e1924e74948bc01f3f42cd5a31502f1c39b6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/7e96780a876f827180dea25139c1c77bbfb94937.png)

## 样例 #1

### 输入

```
5
1 2 3 4 5
5 4 1 2 3
0
6
6 5 4 3 2 1
0
0
```

### 输出

```
Yes
No

Yes
```



---

