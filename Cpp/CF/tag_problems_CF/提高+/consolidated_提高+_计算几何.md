---
title: "Letter A"
layout: "post"
diff: 提高+/省选-
pid: CF13B
tag: ['模拟', '计算几何']
---

# Letter A

## 题目描述

Little Petya learns how to write. The teacher gave pupils the task to write the letter $ A $ on the sheet of paper. It is required to check whether Petya really had written the letter $ A $ .

You are given three segments on the plane. They form the letter $ A $ if the following conditions hold:

- Two segments have common endpoint (lets call these segments first and second), while the third segment connects two points on the different segments.
- The angle between the first and the second segments is greater than $ 0 $ and do not exceed $ 90 $ degrees.
- The third segment divides each of the first two segments in proportion not less than $ 1/4 $ (i.e. the ratio of the length of the shortest part to the length of the longest part is not less than $ 1/4 $ ).

## 输入格式

The first line contains one integer $ t $ ( $ 1<=t<=10000 $ ) — the number of test cases to solve. Each case consists of three lines. Each of these three lines contains four space-separated integers — coordinates of the endpoints of one of the segments. All coordinates do not exceed $ 10^{8} $ by absolute value. All segments have positive length.

## 输出格式

Output one line for each test case. Print «YES» (without quotes), if the segments form the letter $ A $ and «NO» otherwise.

## 样例 #1

### 输入

```
3
4 4 6 0
4 1 5 2
4 0 4 4
0 0 0 6
0 6 2 -4
1 1 0 1
0 0 0 5
0 5 2 -1
1 2 0 1

```

### 输出

```
YES
NO
YES

```



---

---
title: "Ancient Berland Circus"
layout: "post"
diff: 提高+/省选-
pid: CF1C
tag: ['计算几何', '枚举', '最大公约数 gcd']
---

# Ancient Berland Circus

## 题目描述

Nowadays all circuses in Berland have a round arena with diameter 13 meters, but in the past things were different.

In Ancient Berland arenas in circuses were shaped as a regular (equiangular) polygon, the size and the number of angles could vary from one circus to another. In each corner of the arena there was a special pillar, and the rope strung between the pillars marked the arena edges.

Recently the scientists from Berland have discovered the remains of the ancient circus arena. They found only three pillars, the others were destroyed by the time.

You are given the coordinates of these three pillars. Find out what is the smallest area that the arena could have.

## 输入格式

The input file consists of three lines, each of them contains a pair of numbers –– coordinates of the pillar. Any coordinate doesn't exceed 1000 by absolute value, and is given with at most six digits after decimal point.

## 输出格式

Output the smallest possible area of the ancient arena. This number should be accurate to at least 6 digits after the decimal point. It's guaranteed that the number of angles in the optimal polygon is not larger than 100.

## 样例 #1

### 输入

```
0.000000 0.000000
1.000000 1.000000
0.000000 1.000000

```

### 输出

```
1.00000000

```



---

---
title: "Help Greg the Dwarf"
layout: "post"
diff: 提高+/省选-
pid: CF98C
tag: ['计算几何']
---

# Help Greg the Dwarf

## 题目描述

一个很不寻常的市民住在一个遥远的国度——他是矮人格库拉。然而，他不寻常的名字不是最奇怪的事情（而且，过去的每个人都习惯了只是叫他矮人格雷格），还有一些关于矮人格雷格的一些特殊的事实——他已经活了两百多年，而且，他住在一个废弃墓地的墓穴中，没人见他在白天出来过。此外，也没人见过他给自己买食物。这就是为什么在恶龙悲剧地死亡、牛持续从田野中消失后没人感到特别惊讶。邻里的人们非常确信无害的龙对消失的牛没有责任（考虑到恶龙一直对他的素食主义观点很诚挚）。但是甚至那也不是整个故事的最坏的部分。

最坏的部分是仅仅几分钟前，矮人格雷格用某些难以理解的方式进入了你的房子，并且让你帮他解决一个问题。关键是在很短的一段时间以前，格雷格决定订一口新的棺材（知道他怪异的性格，你一点也不会感到奇怪）。但问题是：一段非常长的双向的L形走廊通向格雷格的墓穴，无法拖着任何一口棺材通过那个走廊，这就是为什么他来寻求你的帮助。

你已经将任务抽象化到了一个这样的平面上：让走廊在转弯前和转弯后的宽度为 $a$ 和 $b$ （如图）。两端走廊相交成一个直角，棺材是一个边长分别为 $l$ 和 $w$ $(l\ge w)$ 的矩形。矮人格雷格已经决定了棺材的长$(l)$，这取决于他的身高；你的任务是决定棺材的最大可能的宽$(w)$，以这样的长和宽棺材可以被带到墓穴里。而且，由于棺材的质量很大（纯大理石！），棺材配备了轮子，因此它不能被抬离地面，但是可以在平面内平移和旋转。在进入走廊之前，你可以任意旋转棺材。

格雷格保证如果你帮助他，他就会奖励你永生（我想知道怎么实现？）。而且如果你不帮助他，嗯……相信我，你不想知道会发生什么的。

一句话题意：给出一个有直角拐角的L形走廊和一个长确定、宽不确定（宽不大于长）的矩形，矩形可以任意平移、旋转，要求求出能够通过拐角的矩形的最大的宽。

## 输入格式

第一行包含三个以空格分隔的整数 $a,b,l$ （见题面陈述）$(1\le a,b,l\le10^4)$

## 输出格式

输出棺材最大可能的宽度，绝对或相对误差不超过 $10^{-7}$。如果不存在具有给定长度和正宽度的棺材（可以满足问题陈述要求的棺材），输出"My poor head =("（不含引号）。

数据保证如果答案为正，不会小于 $10^{-7}$。

## 说明/提示

在第一个样例里答案被棺材的长度限制（请记住——棺材的宽不能大于长）

在第二个样例里，棺材由于用于旋转的轮子可以被运送通过走廊：首先，从一端拖着棺材，直到有墙阻止继续前进，然后垂直于初始移动方向将其向前移到相邻的一侧。（请记住——棺材可以任意平移、旋转）

## 样例 #1

### 输入

```
2 2 1

```

### 输出

```
1.0000000

```

## 样例 #2

### 输入

```
2 2 2

```

### 输出

```
2.0000000
```

## 样例 #3

### 输入

```
2 2 3

```

### 输出

```
1.3284271

```

## 样例 #4

### 输入

```
2 2 6

```

### 输出

```
My poor head =(

```



---

