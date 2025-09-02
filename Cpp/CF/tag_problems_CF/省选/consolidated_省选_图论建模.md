---
title: "Algebra Flash"
layout: "post"
diff: 省选/NOI-
pid: CF1767E
tag: ['状态合并', '图论建模', '快速沃尔什变换 FWT', '折半搜索 meet in the middle']
---

# Algebra Flash

## 题目描述

### 题目背景

Algebra Flash 2.2 刚刚发布！

更新日志：

- 全新游戏模式！

感谢您一直以来对游戏的支持！

就这？你略带失望地启动游戏，点进新的游戏模式，上面写着 "彩色平台"。


有 $n$ 个平台排成一列，编号从 $1$ 到 $n$。平台有 $m$ 种颜色，编号从 $1$ 到 $m$。第 $i$ 个平台的颜色是 $c_i$。

你从 $1$ 号平台开始，想要跳到 $n$ 号平台。在一次移动中，你可以从某个平台 $i$ 跳到平台 $i + 1$ 或 $i + 2$。

所有平台最初都未激活（包括平台 $1$ 和 $n$）。对于每种颜色 $j$，你可以支付 $x_j$ 枚金币来激活所有颜色为 $j$ 的平台。

你希望激活一些平台，然后从已激活的平台 $1$ 开始，跳过一些已激活的平台，到达已激活的平台 $n$。

要实现这个目标，你最少花费多少金币？

## 输入格式

第一行两个整数 $n$ 和 $m$（$2 \le n \le 3 \times 10^5$ ; $1 \le m \le 40$），分别表示平台数和颜色数。

第二行 $n$ 个整数 $c_1, c_2, \dots, c_n$（$1 \le c_i \le m$）表示平台的颜色。

第三行 $m$ 个整数 $x_1, x_2, \dots, x_m$（$1 \le x_i \le 10^7$）表示激活每种颜色的所有平台花费的金币数量。

## 输出格式

一行一个整数，表示从激活的平台 $1$ 开始，跳过一些激活的平台，到达激活的平台 $n$ 需要花费的最小金币数量。

Translated by UID 781046.

## 样例 #1

### 输入

```
5 3
1 3 2 3 1
1 10 100
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5 3
1 3 2 3 1
1 200 20
```

### 输出

```
21
```

## 样例 #3

### 输入

```
4 2
2 2 1 1
5 5
```

### 输出

```
10
```

## 样例 #4

### 输入

```
10 10
3 8 6 2 10 5 2 3 7 3
9 7 4 2 1 8 2 6 2 2
```

### 输出

```
15
```



---

---
title: "Legacy"
layout: "post"
diff: 省选/NOI-
pid: CF786B
tag: ['线段树', '图论建模', '最短路']
---

# Legacy

## 题目描述

Rick and his co-workers have made a new radioactive formula and a lot of bad guys are after them. So Rick wants to give his legacy to Morty before bad guys catch them.

There are $ n $ planets in their universe numbered from $ 1 $ to $ n $ . Rick is in planet number $ s $ (the earth) and he doesn't know where Morty is. As we all know, Rick owns a portal gun. With this gun he can open one-way portal from a planet he is in to any other planet (including that planet). But there are limits on this gun because he's still using its free trial.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786B/9ce8ffb5132d0e638eaee42e56a9bbc8517d720d.png)By default he can not open any portal by this gun. There are $ q $ plans in the website that sells these guns. Every time you purchase a plan you can only use it once but you can purchase it again if you want to use it more.

Plans on the website have three types:

1. With a plan of this type you can open a portal from planet $ v $ to planet $ u $ .
2. With a plan of this type you can open a portal from planet $ v $ to any planet with index in range $ [l,r] $ .
3. With a plan of this type you can open a portal from any planet with index in range $ [l,r] $ to planet $ v $ .

Rick doesn't known where Morty is, but Unity is going to inform him and he wants to be prepared for when he finds and start his journey immediately. So for each planet (including earth itself) he wants to know the minimum amount of money he needs to get from earth to that planet.

## 输入格式

The first line of input contains three integers $ n $ , $ q $ and $ s $ ( $ 1<=n,q<=10^{5} $ , $ 1<=s<=n $ ) — number of planets, number of plans and index of earth respectively.

The next $ q $ lines contain the plans. Each line starts with a number $ t $ , type of that plan ( $ 1<=t<=3 $ ). If $ t=1 $ then it is followed by three integers $ v $ , $ u $ and $ w $ where $ w $ is the cost of that plan ( $ 1<=v,u<=n $ , $ 1<=w<=10^{9} $ ). Otherwise it is followed by four integers $ v $ , $ l $ , $ r $ and $ w $ where $ w $ is the cost of that plan ( $ 1<=v<=n $ , $ 1<=l<=r<=n $ , $ 1<=w<=10^{9} $ ).

## 输出格式

In the first and only line of output print $ n $ integers separated by spaces. $ i $ -th of them should be minimum money to get from earth to $ i $ -th planet, or $ -1 $ if it's impossible to get to that planet.

## 说明/提示

In the first sample testcase, Rick can purchase $ 4 $ th plan once and then $ 2 $ nd plan in order to get to get to planet number $ 2 $ .

## 样例 #1

### 输入

```
3 5 1
2 3 2 3 17
2 3 2 2 16
2 2 2 3 3
3 3 1 1 12
1 3 3 17

```

### 输出

```
0 28 12 

```

## 样例 #2

### 输入

```
4 3 1
3 4 1 3 12
2 2 3 4 10
1 2 4 16

```

### 输出

```
0 -1 -1 12 

```



---

---
title: "Exploration plan"
layout: "post"
diff: 省选/NOI-
pid: CF852D
tag: ['网络流', '图论建模', '最短路']
---

# Exploration plan

## 题目描述

The competitors of Bubble Cup X gathered after the competition and discussed what is the best way to get to know the host country and its cities.

After exploring the map of Serbia for a while, the competitors came up with the following facts: the country has $ V $ cities which are indexed with numbers from $ 1 $ to $ V $ , and there are $ E $ bi-directional roads that connect the cites. Each road has a weight (the time needed to cross that road). There are $ N $ teams at the Bubble Cup and the competitors came up with the following plan: each of the $ N $ teams will start their journey in one of the $ V $ cities, and some of the teams share the starting position.

They want to find the shortest time $ T $ , such that every team can move in these $ T $ minutes, and the number of different cities they end up in is at least $ K $ (because they will only get to know the cities they end up in). A team doesn't have to be on the move all the time, if they like it in a particular city, they can stay there and wait for the time to pass.

Please help the competitors to determine the shortest time $ T $ so it's possible for them to end up in at least $ K $ different cities or print -1 if that is impossible no matter how they move.

Note that there can exist multiple roads between some cities.

## 输入格式

The first line contains four integers: $ V $ , $ E $ , $ N $ and $ K\ (1<=V<=600,\ 1<=E<=20000,\ 1<=N<=min(V,200),\ 1<=K<=N) $ , number of cities, number of roads, number of teams and the smallest number of different cities they need to end up in, respectively.

The second line contains $ N $ integers, the cities where the teams start their journey.

Next $ E $ lines contain information about the roads in following format: $ A_{i}\ B_{i}\ T_{i}\ (1<=A_{i},B_{i}<=V,\ 1<=T_{i}<=10000) $ , which means that there is a road connecting cities $ A_{i} $ and $ B_{i} $ , and you need $ T_{i} $ minutes to cross that road.

## 输出格式

Output a single integer that represents the minimal time the teams can move for, such that they end up in at least $ K $ different cities or output -1 if there is no solution.

If the solution exists, result will be no greater than $ 1731311 $ .

## 说明/提示

Three teams start from city 5, and two teams start from city 2. If they agree to move for 3 minutes, one possible situation would be the following: Two teams in city 2, one team in city 5, one team in city 3 , and one team in city 1. And we see that there are four different cities the teams end their journey at.

## 样例 #1

### 输入

```
6 7 5 4
5 5 2 2 5
1 3 3
1 5 2
1 6 5
2 5 4
2 6 7
3 4 11
3 5 3

```

### 输出

```
3
```



---

---
title: "Winning Strategy"
layout: "post"
diff: 省选/NOI-
pid: CF97C
tag: ['倍增', '背包 DP', '图论建模']
---

# Winning Strategy

## 题目描述

One university has just found out about a sport programming contest called ACM ICPC v2.0. This contest doesn't differ much from the well-known ACM ICPC, for example, the participants are not allowed to take part in the finals more than two times. However, there is one notable difference: the teams in the contest should consist of exactly $ n $ participants.

Having taken part in several ACM ICPC v2.0 finals and having not won any medals, the students and the university governors realized that it's high time they changed something about the preparation process. Specifically, as the first innovation it was decided to change the teams' formation process. Having spent considerable amount of time on studying the statistics of other universities' performance, they managed to receive some interesting information: the dependence between the probability of winning a medal and the number of team members that participated in the finals in the past. More formally, we know $ n+1 $ real numbers $ p_{0}<=p_{1}<=...<=p_{n} $ , where $ p_{i} $ is the probability of getting a medal on the finals if the team has $ i $ participants of previous finals, and other $ n-i $ participants arrived to the finals for the first time.

Despite such useful data, the university governors are unable to determine such team forming tactics that would provide the maximum probability of winning a medal at ACM ICPC v2.0 finals on average (we are supposed to want to provide such result to the far future and we are also supposed to have an endless supply of students). And how about you, can you offer such optimal tactic? At the first stage the university governors want to know the value of maximum average probability.

More formally, suppose that the university sends a team to the $ k $ -th world finals. The team has $ a_{k} $ participants of previous finals ( $ 0<=a_{k}<=n $ ). Since each person can participate in the finals no more than twice, the following condition must be true: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/b04e8ade7d007ad0702101fe8e64b638ac1fbbe2.png). Your task is to choose sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) so that the limit $ Ψ $ exists and it's value is maximal:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/cb2ffabcf620f29ef29bcdc17d35b1562b965de1.png)As ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) is an infinite sequence, you should only print the maximum value of the $ Ψ $ limit.

## 输入格式

The first line contains an integer $ n $ ( $ 3<=n<=100 $ ), $ n $ is the number of team participants. The second line contains $ n+1 $ real numbers with no more than 6 digits after decimal point $ p_{i} $ ( $ 0<=i<=n,0<=p_{i}<=1 $ ) — the probability of that the team will win a medal if it contains $ i $ participants who has already been on the finals. Also the condition $ p_{i}<=p_{i+1} $ should be fulfilled for all $ 0<=i<=n-1 $ .

## 输出格式

Print the only real number — the expected average number of medals won per year if the optimal strategy is used. The result may have absolute or relative error $ 10^{-6} $ .

## 说明/提示

In the second test, no matter what participants the team contains, it is doomed to be successful.

## 样例 #1

### 输入

```
3
0.115590 0.384031 0.443128 0.562356

```

### 输出

```
0.4286122500

```

## 样例 #2

### 输入

```
3
1 1 1 1

```

### 输出

```
0.9999999999

```



---

