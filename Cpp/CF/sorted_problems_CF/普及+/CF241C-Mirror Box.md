---
title: "Mirror Box"
layout: "post"
diff: 普及+/提高
pid: CF241C
tag: []
---

# Mirror Box

## 题目描述

Mirror Box is a name of a popular game in the Iranian National Amusement Park (INAP). There is a wooden box, $ 10^{5} $ cm long and $ 100 $ cm high in this game. Some parts of the box's ceiling and floor are covered by mirrors. There are two negligibly small holes in the opposite sides of the box at heights $ h_{l} $ and $ h_{r} $ centimeters above the floor. The picture below shows what the box looks like.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241C/6424a01d70e5009585312ab434deff869a3c6956.png)In the game, you will be given a laser gun to shoot once. The laser beam must enter from one hole and exit from the other one. Each mirror has a preset number $ v_{i} $ , which shows the number of points players gain if their laser beam hits that mirror. Also — to make things even funnier — the beam must not hit any mirror more than once.

Given the information about the box, your task is to find the maximum score a player may gain. Please note that the reflection obeys the law "the angle of incidence equals the angle of reflection".

## 输入格式

The first line of the input contains three space-separated integers $ h_{l},h_{r},n $ ( $ 0&lt;h_{l},h_{r}&lt;100 $ , $ 0<=n<=100 $ ) — the heights of the holes and the number of the mirrors.

Next $ n $ lines contain the descriptions of the mirrors. The $ i $ -th line contains space-separated $ v_{i},c_{i},a_{i},b_{i} $ ; the integer $ v_{i} $ ( $ 1<=v_{i}<=1000 $ ) is the score for the $ i $ -th mirror; the character $ c_{i} $ denotes $ i $ -th mirror's position — the mirror is on the ceiling if $ c_{i} $ equals "T" and on the floor if $ c_{i} $ equals "F"; integers $ a_{i} $ and $ b_{i} $ ( $ 0<=a_{i}&lt;b_{i}<=10^{5} $ ) represent the $ x $ -coordinates of the beginning and the end of the mirror.

No two mirrors will share a common point. Consider that the $ x $ coordinate increases in the direction from left to right, so the border with the hole at height $ h_{l} $ has the $ x $ coordinate equal to 0 and the border with the hole at height $ h_{r} $ has the $ x $ coordinate equal to $ 10^{5} $ .

## 输出格式

The only line of output should contain a single integer — the maximum possible score a player could gain.

## 说明/提示

The second sample is depicted above. The red beam gets $ 10+50+5+35+8+2=110 $ points and the blue one gets $ 120 $ .

The red beam on the picture given in the statement shows how the laser beam can go approximately, this is just illustration how the laser beam can gain score. So for the second sample there is no such beam that gain score 110.

## 样例 #1

### 输入

```
50 50 7
10 F 1 80000
20 T 1 80000
30 T 81000 82000
40 T 83000 84000
50 T 85000 86000
60 T 87000 88000
70 F 81000 89000

```

### 输出

```
100

```

## 样例 #2

### 输入

```
80 72 9
15 T 8210 15679
10 F 11940 22399
50 T 30600 44789
50 F 32090 36579
5 F 45520 48519
120 F 49250 55229
8 F 59700 80609
35 T 61940 64939
2 T 92540 97769

```

### 输出

```
120

```

