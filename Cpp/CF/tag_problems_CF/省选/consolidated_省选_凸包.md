---
title: "The Supersonic Rocket"
layout: "post"
diff: 省选/NOI-
pid: CF1017E
tag: ['字符串', '凸包', 'KMP 算法']
---

# The Supersonic Rocket

## 题目描述

After the war, the supersonic rocket became the most common public transportation.

Each supersonic rocket consists of two "engines". Each engine is a set of "power sources". The first engine has $ n $ power sources, and the second one has $ m $ power sources. A power source can be described as a point $ (x_i, y_i) $ on a 2-D plane. All points in each engine are different.

You can manipulate each engine separately. There are two operations that you can do with each engine. You can do each operation as many times as you want.

1. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i+a, y_i+b) $ , $ a $ and $ b $ can be any real numbers. In other words, all power sources will be shifted.
2. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i \cos \theta - y_i \sin \theta, x_i \sin \theta + y_i \cos \theta) $ , $ \theta $ can be any real number. In other words, all power sources will be rotated.

The engines work as follows: after the two engines are powered, their power sources are being combined (here power sources of different engines may coincide). If two power sources $ A(x_a, y_a) $ and $ B(x_b, y_b) $ exist, then for all real number $ k $ that $ 0 \lt k \lt 1 $ , a new power source will be created $ C_k(kx_a+(1-k)x_b,ky_a+(1-k)y_b) $ . Then, this procedure will be repeated again with all new and old power sources. After that, the "power field" from all power sources will be generated (can be considered as an infinite set of all power sources occurred).

A supersonic rocket is "safe" if and only if after you manipulate the engines, destroying any power source and then power the engine, the power field generated won't be changed (comparing to the situation where no power source erased). Two power fields are considered the same if and only if any power source in one field belongs to the other one as well.

Given a supersonic rocket, check whether it is safe or not.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 3 \le n, m \le 10^5 $ ) — the number of power sources in each engine.

Each of the next $ n $ lines contains two integers $ x_i $ and $ y_i $ ( $ 0\leq x_i, y_i\leq 10^8 $ ) — the coordinates of the $ i $ -th power source in the first engine.

Each of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 0\leq x_i, y_i\leq 10^8 $ ) — the coordinates of the $ i $ -th power source in the second engine.

It is guaranteed that there are no two or more power sources that are located in the same point in each engine.

## 输出格式

Print "YES" if the supersonic rocket is safe, otherwise "NO".

You can print each letter in an arbitrary case (upper or lower).

## 说明/提示

The first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/1f54366cb2efd6f1fd1d0617b722b5e3979dfd89.png)Those near pairs of blue and orange points actually coincide.First, manipulate the first engine: use the second operation with $ \theta = \pi $ (to rotate all power sources $ 180 $ degrees).

The power sources in the first engine become $ (0, 0) $ , $ (0, -2) $ , and $ (-2, 0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/d9732486b953667a46772450be0d244f2cb20626.png)Second, manipulate the second engine: use the first operation with $ a = b = -2 $ .

The power sources in the second engine become $ (-2, 0) $ , $ (0, 0) $ , $ (0, -2) $ , and $ (-1, -1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/f5d3a1ffc842f837240530d5f9c0ef57b3d408b7.png)You can examine that destroying any point, the power field formed by the two engines are always the solid triangle $ (0, 0) $ , $ (-2, 0) $ , $ (0, -2) $ .

In the second sample, no matter how you manipulate the engines, there always exists a power source in the second engine that power field will shrink if you destroy it.

## 样例 #1

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
1 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
0 0

```

### 输出

```
NO

```



---

---
title: "Spaceship Exploration"
layout: "post"
diff: 省选/NOI-
pid: CF1906D
tag: ['计算几何', '凸包']
---

# Spaceship Exploration

## 题目描述

In The ICPC Galaxy, there exists a zone filled with asteroids that is unsafe to enter. The map of the galaxy is represented in a 2D Cartesian coordinate system. The zone is in the shape of an $ N $ -sided convex polygon. Each corner is numbered from $ 1 $ to $ N $ ; corner $ i $ is located at $ (X_i, Y_i) $ . At any moment, you should not be inside this polygon; however, it is safe to touch the side of the polygon.

There are $ Q $ scenarios (numbered from $ 1 $ to $ Q $ ). In scenario $ j $ , you want to go from a starting point at $ (A_j, B_j) $ to an ending point at $ (C_j, D_j) $ . You will be riding on a special spaceship that can only travel in a straight line. First, you set the direction of the spaceship, then the spaceship will start traveling in that direction. During the travel, you are only allowed to change direction at most once. Changing direction means you stop the spaceship, set a new direction, and then start traveling again in the new direction.

For each scenario, determine the minimum distance required to travel without being inside of the zone at any moment, or report if it is impossible to reach the ending point.

## 输入格式

The first line consists of an integer $ N $ ( $ 3 \leq N \leq 100\,000 $ ).

Each of the next $ N $ lines consists of two integers $ X_i $ $ Y_i $ ( $ -10^9 \leq X_i, Y_i \leq 10^9 $ ). The points form a convex polygon in counterclockwise order. There are no three points which are collinear.

The following line consists of an integer $ Q $ ( $ 1 \leq Q \leq 100\,000 $ ).

Each of the next $ Q $ lines consists of four integers $ A_j $ $ B_j $ $ C_j $ $ D_j $ ( $ -10^9 \leq A_j, B_j, C_j, D_j \leq 10^9 $ ). There are no starting points and ending points inside the zone. However, it is possible for the starting point and the ending point to be at the side of the zone.

All the coordinates in the input are integers.

## 输出格式

For each scenario, output the answer in a single line.

If it is possible to reach the ending point without being inside the zone at any moment, then output the minimum distance required to travel. Otherwise, output -1.

Your answer is considered correct if its absolute error or relative error does not exceed $ 10^{-6} $ . Namely, if your answer is $ a $ and the jury's answer is $ b $ , then your answer is accepted if $ \frac{|a - b|}{\max(1, |b|)} \leq 10^{-6} $ .

## 说明/提示

Explanation for the sample input/output #1

This sample is depicted in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906D/3b577bd1075a31373238167ad213c432f7146baa.png)During scenario $ 1 $ and $ 4 $ , you can directly go to the ending point without changing the direction.

During scenario $ 2 $ , you can go to $ (0, 2) $ , then change direction to the ending point.

During scenario $ 3 $ , you can go to $ (6, 2) $ , then change direction to the ending point.

During scenario $ 5 $ , it can be shown that it is impossible to reach the ending point.

## 样例 #1

### 输入

```
5
0 2
2 0
4 0
4 4
2 4
5
6 1 6 3
2 5 0 0
3 5 3 -1
1 4 5 4
3 4 3 0
```

### 输出

```
2
5.6055512755
8.48528137422
4
-1
```

## 样例 #2

### 输入

```
4
-10 -9
10 -9
10 9
-10 9
2
0 10 0 -10
-10 -10 -10 -10
```

### 输出

```
200.9975124224
0
```

## 样例 #3

### 输入

```
8
-20 -10
10 -20
25 -15
35 -5
30 10
15 20
-25 15
-30 5
6
-15 -15 -15 20
-30 -5 30 15
25 20 -5 -20
-5 25 20 -20
-30 10 30 -10
-30 -50 50 0
```

### 输出

```
59.0857761929
103.2455532034
94.7213595500
101.5640991922
164.8528137424
94.3398113206
```



---

---
title: "Digital Village (Extreme Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2021E3
tag: ['动态规划 DP', 'Kruskal 重构树', '凸包']
---

# Digital Village (Extreme Version)

## 题目描述

**这是问题的极端版本。在三个版本中，$n$ 和 $m$ 的约束条件不同。只有所有版本的问题都解决了，你才能进行 hack。**

Pak Chanek 正在为 Khuntien 村设置互联网连接。这个村庄可以表示为一个连通的简单图，其中有 $n$ 栋房屋和 $m$ 条互联网电缆，每条电缆连接房屋 $u_i$ 和房屋 $v_i$，并且具有延迟 $w_i$。

有 $p$ 栋房屋需要互联网。Pak Chanek 最多可以在 $k$ 栋房屋中安装服务器。需要互联网的房屋将连接到其中一个服务器。但是，由于每条电缆都有其延迟，对于需要互联网的房屋 $s_i$，其经历的延迟将是该房屋与其连接的服务器之间电缆的**最大**延迟。

对于每个 $k = 1,2,\ldots,n$，帮助 Pak Chanek 确定所有需要互联网的房屋所能达到的最小**总**延迟。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 2000$ )。对每个测试用例说明如下：

每个测试用例的第一行包含三个整数 $n$ , $m$ , $p$ ( $2 \le n \le 2\times 10^5$ ; $n-1 \le m \le 2\times 10^5$ ; $1 \le p \le n$ )，表示房屋数量、电缆数量和需要网络的房屋数量。

每个测试用例的第二行包含 $p$ 个整数 $s_1, s_2, \ldots, s_p$ ( $1 \le s_i \le n$ )，表示需要上网的房屋。保证 $s$ 中的所有元素都是不同的。

每个测试用例下 $m$ 行每行包含三个整数 $u_i$、$v_i$ 和 $w_i$（$1 \le u_i , v_i \le n$ ; $1 \le w_i \le 10^9$）表示一条连接房屋 $u_i$ 和房屋 $v_i$ 的网线，延迟为 $w_i$。保证给定的边构成一个连通的简单图。

保证 $n$ 和 $m$ 之和不超过 $2 \times 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数：对**每个**$k = 1,2,\ldots,n$，计算所有需要上网的房屋所能达到的最小总延迟。

**样例解释**

第一个测试用例中，$k=3$ 的一个的最佳解决方案是在顶点 $2$ 、 $6$ 和 $8$ 安装服务器，并获得以下延迟：

- $\text{latency}(2) = 0$
- $\text{latency}(5) = \max(3, 5) = 5$
- $\text{latency}(6) = 0$
- $\text{latency}(8) = 0$
- $\text{latency}(9) = \max(2, 4) = 4$

因此总延迟为 $0+5+0+0+4=9$ 。

## 样例 #1

### 输入

```
2
9 8 5
2 5 6 8 9
1 2 1
1 3 2
3 4 10
4 5 3
4 6 5
1 7 10
7 8 4
7 9 2
3 3 2
3 1
1 2 1
2 3 3
1 3 2
```

### 输出

```
34 19 9 4 0 0 0 0 0
2 0 0
```



---

---
title: "Tavas and Pashmaks"
layout: "post"
diff: 省选/NOI-
pid: CF535E
tag: ['排序', '栈', '凸包']
---

# Tavas and Pashmaks

## 题目描述

现在有两个比赛项目:跑步和游泳.每一个人在这两个项目都有一个正整数的值,第i个人分别为$a_i,b_i$,表示他在这个项目上的速度.
我们假定游泳的距离为$S_1$,跑步的距离为$S_2$(都是**正实数**),知道每一个人的值,如果对于第i个人,存在这样子的$S_1$和$S_2$使得$S_1/a_i+S_2/b_i<=S_1/a_j+S_2/b_j(1<=j<=n)$,那么就称这个人可以夺冠.
求出有多少个人可以夺冠.

## 输入格式

第$1$行一个正整数$n$,表示有$n$个人.
第$2$~$n+1$,每行有$2$个正整数分别表示每一个人在跑步和游泳上的速度.

## 输出格式

一行,输出所有可以夺冠的人.

## 样例 #1

### 输入

```
3
1 3
2 2
3 1

```

### 输出

```
1 2 3 

```

## 样例 #2

### 输入

```
3
1 2
1 1
2 1

```

### 输出

```
1 3 

```



---

---
title: "Freelancer's Dreams"
layout: "post"
diff: 省选/NOI-
pid: CF605C
tag: ['向量', '凸包']
---

# Freelancer's Dreams

## 题目描述

Mikhail the Freelancer dreams of two things: to become a cool programmer and to buy a flat in Moscow. To become a cool programmer, he needs at least $ p $ experience points, and a desired flat in Moscow costs $ q $ dollars. Mikhail is determined to follow his dreams and registered at a freelance site.

He has suggestions to work on $ n $ distinct projects. Mikhail has already evaluated that the participation in the $ i $ -th project will increase his experience by $ a_{i} $ per day and bring $ b_{i} $ dollars per day. As freelance work implies flexible working hours, Mikhail is free to stop working on one project at any time and start working on another project. Doing so, he receives the respective share of experience and money. Mikhail is only trying to become a cool programmer, so he is able to work only on one project at any moment of time.

Find the real value, equal to the minimum number of days Mikhail needs to make his dream come true.

For example, suppose Mikhail is suggested to work on three projects and $ a_{1}=6 $ , $ b_{1}=2 $ , $ a_{2}=1 $ , $ b_{2}=3 $ , $ a_{3}=2 $ , $ b_{3}=6 $ . Also, $ p=20 $ and $ q=20 $ . In order to achieve his aims Mikhail has to work for $ 2.5 $ days on both first and third projects. Indeed, $ a_{1}·2.5+a_{2}·0+a_{3}·2.5=6·2.5+1·0+2·2.5=20 $ and $ b_{1}·2.5+b_{2}·0+b_{3}·2.5=2·2.5+3·0+6·2.5=20 $ .

## 输入格式

The first line of the input contains three integers $ n $ , $ p $ and $ q $ ( $ 1<=n<=100000,1<=p,q<=1000000 $ ) — the number of projects and the required number of experience and money.

Each of the next $ n $ lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=1000000 $ ) — the daily increase in experience and daily income for working on the $ i $ -th project.

## 输出格式

Print a real value — the minimum number of days Mikhail needs to get the required amount of experience and money. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF605C/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

First sample corresponds to the example in the problem statement.

## 样例 #1

### 输入

```
3 20 20
6 2
1 3
2 6

```

### 输出

```
5.000000000000000

```

## 样例 #2

### 输入

```
4 1 1
2 3
3 2
2 3
3 2

```

### 输出

```
0.400000000000000

```



---

---
title: "Professor's task"
layout: "post"
diff: 省选/NOI-
pid: CF70D
tag: ['计算几何', '排序', '凸包', '叉积']
---

# Professor's task

## 题目描述

Once a walrus professor Plato asked his programming students to perform the following practical task.

The students had to implement such a data structure that would support a convex hull on some set of points $ S $ . The input to the program had $ q $ queries of two types:

1\. Add a point with coordinates $ (x,y) $ into the set $ S $ . Note that in this case the convex hull of $ S $ could have changed, and could have remained the same.

2\. Say whether a point with coordinates $ (x,y) $ belongs to an area limited by the convex hull, including the border.

All the students coped with the task. What about you?

## 输入格式

The first line contains an integer $ q $ ( $ 4<=q<=10^{5} $ ).

Then follow $ q $ lines in the following way: " $ t $ $ x $ $ y $ ", where $ t $ is the query type (1 or 2), and $ (x,y) $ are the coordinates of the point ( $ -10^{6}<=x,y<=10^{6} $ , $ x $ and $ y $ are integers).

There is at least one query of type 2.

It is guaranteed that the three queries of the first type follow first and the points given in the queries form a non-degenerative triangle. Also all the points added in $ S $ are distinct.

## 输出格式

For each query of the second type print one string containing "YES", if the point lies inside the convex hull or on its border. Otherwise, print "NO".

## 样例 #1

### 输入

```
8
1 0 0
1 2 0
1 2 2
2 1 0
1 0 2
2 1 1
2 2 1
2 20 -1

```

### 输出

```
YES
YES
YES
NO

```



---

