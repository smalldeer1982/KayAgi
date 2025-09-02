---
title: "Berland and the Shortest Paths"
layout: "post"
diff: 省选/NOI-
pid: CF1005F
tag: ['最短路']
---

# Berland and the Shortest Paths

## 题目描述

Berland 有 $n$ 座城市。一些城市通过道路连接。所有道路都是双向的。每条道路连接两个不同的城市。一对城市之间至多有一条道路。城市从 $1$ 到 $n$ 编号。

众所周知，从首都（编号为 $1$ 的城市），您可以沿着道路移动并到达任何其他城市。

Berland 的总统计划改善该国的道路网。预算足以修复 $n-1$ 道路。总统计划选择 $n-1$ 条道路，要求：

- 从首都出发沿着这 $n-1$ 条道路走可以到达其他所有的城市。
- 如果 $d_i$ 表示首都到 $i$ 号城市所需经过的路的条数，沿着选择的 n-1 条路走所得的 $d_1$+$d_2$+・・・+$d_n$ 应是最小的。

换句话说，这 $n-1$ 条道路的应该保持国家的连通性，并且使从城市 $1$ 到所有城市的距离的总和最小（你只能使用被选择的 $n-1$ 道路）。

总统命令有关部门准备 $k$ 个可能的选择，选择的 $n-1$ 条道路同时满足以上两个条件。

编写一个程序，找到 $k$ 种可能的方法来选择道路进行维修。如果少于 $k$ 种选法，则程序应输出所有可能的有效方式来选择道路。

## 输入格式

输入的第一行包含整数 $n,m,k.$ $(2 \leq$ $ n \le $ $2 \cdot $ $10^5,$ $n-1$ $\leq$ $m \leq$ $2$ $\cdot $ $10^5,$ $1 \leq$ $k$ $\leq$ $2 \cdot $ $10^5$ $),$ $n$ 是这个国家的城市数，$m$ 是道路数，并且 $k$ 是选 $n-1$ 条道路修复的方案数。 数据保证 $m \cdot k \leq 10^6.$

接下来的 $m$ 行描述路的情况，每条路的描述占一行。每行包括两个整数 $a_i,b_i (1 \leq a_i,b_i\leq n,a_i \neq b_i)$—— 第 $i$ 条道路连接的两座城市的编号。一对城市最多有一条路连接。给定的路足以使你从首都出发到达任意城市。

## 输出格式

输出 $t (1 \leq t \leq k)$— 可选择的方案数量。记得你需要找到 $k$ 种不同的可行解，如果解的个数少于 $k$ 种，你需要输出所有可行解。

在接下来的 $t$ 行中，输出道路选择情况，一种一行。用 $m$ 个字符的字符串输出选择情况，其中，第 $j$ 个字符表示第 $j$ 条道路是否被选中，若是则用 $1$ 表示，若不是则用 $0$ 表示。路应该按照它们输入的顺序编号。各种选择情况的输出没有指定顺序。$t$ 行的所有输出应该不同。

因为题目保证 $m \cdot k\leq 10^6,t$ 行输出的总长不超过 $10^6.$

如果有很多组答案，任意输出它们中的一些即可。

## 样例 #1

### 输入

```
4 4 3
1 2
2 3
1 4
4 3

```

### 输出

```
2
1110
1011

```

## 样例 #2

### 输入

```
4 6 3
1 2
2 3
1 4
4 3
2 4
1 3

```

### 输出

```
1
101001

```

## 样例 #3

### 输入

```
5 6 2
1 2
1 3
2 4
2 5
3 4
3 5

```

### 输出

```
2
111100
110110

```



---

---
title: "Long Way Home"
layout: "post"
diff: 省选/NOI-
pid: CF1715E
tag: ['斜率优化', '最短路']
---

# Long Way Home

## 题目描述

Stanley lives in a country that consists of $ n $ cities (he lives in city $ 1 $ ). There are bidirectional roads between some of the cities, and you know how long it takes to ride through each of them. Additionally, there is a flight between each pair of cities, the flight between cities $ u $ and $ v $ takes $ (u - v)^2 $ time.

Stanley is quite afraid of flying because of watching "Sully: Miracle on the Hudson" recently, so he can take at most $ k $ flights. Stanley wants to know the minimum time of a journey to each of the $ n $ cities from the city $ 1 $ .

## 输入格式

In the first line of input there are three integers $ n $ , $ m $ , and $ k $ ( $ 2 \leq n \leq 10^{5} $ , $ 1 \leq m \leq 10^{5} $ , $ 1 \leq k \leq 20 $ ) — the number of cities, the number of roads, and the maximal number of flights Stanley can take.

The following $ m $ lines describe the roads. Each contains three integers $ u $ , $ v $ , $ w $ ( $ 1 \leq u, v \leq n $ , $ u \neq v $ , $ 1 \leq w \leq 10^{9} $ ) — the cities the road connects and the time it takes to ride through. Note that some pairs of cities may be connected by more than one road.

## 输出格式

Print $ n $ integers, $ i $ -th of which is equal to the minimum time of traveling to city $ i $ .

## 说明/提示

In the first sample, it takes no time to get to city 1; to get to city 2 it is possible to use a flight between 1 and 2, which will take 1 unit of time; to city 3 you can get via a road from city 1, which will take 1 unit of time.

In the second sample, it also takes no time to get to city 1. To get to city 2 Stanley should use a flight between 1 and 2, which will take 1 unit of time. To get to city 3 Stanley can ride between cities 1 and 2, which will take 3 units of time, and then use a flight between 2 and 3. To get to city 4 Stanley should use a flight between 1 and 2, then take a ride from 2 to 4, which will take 5 units of time.

## 样例 #1

### 输入

```
3 1 2
1 3 1
```

### 输出

```
0 1 1
```

## 样例 #2

### 输入

```
4 3 1
1 2 3
2 4 5
3 4 7
```

### 输出

```
0 1 4 6
```

## 样例 #3

### 输入

```
2 1 1
2 1 893746473
```

### 输出

```
0 1
```

## 样例 #4

### 输入

```
5 5 2
2 1 33
1 5 93
5 3 48
2 3 21
4 2 1
```

### 输出

```
0 1 2 2 3
```



---

---
title: "Circling Round Treasures"
layout: "post"
diff: 省选/NOI-
pid: CF375C
tag: ['图论', '状态合并', '最短路']
---

# Circling Round Treasures

## 题目描述

给你一个 $N \times M$ 的地图（$N,M \le 20$），地图上 `#` 表示障碍物，`B` 表示炸弹，数字表示宝藏序号（宝藏+炸弹个数 $\le 8$），每个宝藏有价值（$-200 \le v \le 200$），`S` 表示出发点。每次移动可以从一个格子移动到相邻格子（上下左右）。寻找一条路径从 `S` 出发再回到 `S` 的封闭路径，移动步数记为 $K$，这个路径所包围的宝藏价值总和记为 $V$，则这条路径的价值为 $V - K$。题目即是求可行的最大的路径价值，并且不能包围炸弹。

## 输入格式

第一行两个整数 $N, M$ 表示地图的长和宽 

接下来 $N$ 行，每行 $M$ 个字符，描述整个地图，地图只可能包含如下字符: 

字符 `B` 表示炸弹；

字符 `S` 表示起点,保证有且只有一个；

数字 $c$（$1 \sim 8$）代表宝藏标号，宝藏和炸弹加起来最多只有 $8$ 个；

字符 `.` 表示空白格；

字符 `#` 表示障碍物(墙)；

假设地图包含 $t$ 个宝藏，接下来 $t$ 行，每行一个整数 $v_i$（$-200 \le v_i \le 200$），依序表示第 $i$ 个宝藏的价值。

## 输出格式

一个整数，即能够获得的最大价值

感谢@xjdx 提供的翻译

## 样例 #1

### 输入

```
4 4
....
.S1.
....
....
10

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7 7
.......
.1###2.
.#...#.
.#.B.#.
.3...4.
..##...
......S
100
100
100
100

```

### 输出

```
364

```

## 样例 #3

### 输入

```
7 8
........
........
....1B..
.S......
....2...
3.......
........
100
-100
100

```

### 输出

```
0

```

## 样例 #4

### 输入

```
1 1
S

```

### 输出

```
0

```



---

---
title: "Team Rocket Rises Again"
layout: "post"
diff: 省选/NOI-
pid: CF757F
tag: ['最短路']
---

# Team Rocket Rises Again

## 题目描述

It's the turn of the year, so Bash wants to send presents to his friends. There are $ n $ cities in the Himalayan region and they are connected by $ m $ bidirectional roads. Bash is living in city $ s $ . Bash has exactly one friend in each of the other cities. Since Bash wants to surprise his friends, he decides to send a Pikachu to each of them. Since there may be some cities which are not reachable from Bash's city, he only sends a Pikachu to those friends who live in a city reachable from his own city. He also wants to send it to them as soon as possible.

He finds out the minimum time for each of his Pikachus to reach its destination city. Since he is a perfectionist, he informs all his friends with the time their gift will reach them. A Pikachu travels at a speed of $ 1 $ meters per second. His friends were excited to hear this and would be unhappy if their presents got delayed. Unfortunately Team Rocket is on the loose and they came to know of Bash's plan. They want to maximize the number of friends who are unhappy with Bash.

They do this by destroying exactly one of the other $ n-1 $ cities. This implies that the friend residing in that city dies, so he is unhappy as well.

Note that if a city is destroyed, all the roads directly connected to the city are also destroyed and the Pikachu may be forced to take a longer alternate route.

Please also note that only friends that are waiting for a gift count as unhappy, even if they die.

Since Bash is already a legend, can you help Team Rocket this time and find out the maximum number of Bash's friends who can be made unhappy by destroying exactly one city.

## 输入格式

The first line contains three space separated integers $ n $ , $ m $ and $ s $ ( $ 2<=n<=2·10^{5} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757F/a96c653ce18839af52c685b3a4dac28dbdbbdc23.png), $ 1<=s<=n $ ) — the number of cities and the number of roads in the Himalayan region and the city Bash lives in.

Each of the next $ m $ lines contain three space-separated integers $ u $ , $ v $ and $ w $ ( $ 1<=u,v<=n $ , $ u≠v $ , $ 1<=w<=10^{9} $ ) denoting that there exists a road between city $ u $ and city $ v $ of length $ w $ meters.

It is guaranteed that no road connects a city to itself and there are no two roads that connect the same pair of cities.

## 输出格式

Print a single integer, the answer to the problem.

## 说明/提示

In the first sample, on destroying the city $ 2 $ , the length of shortest distance between pairs of cities $ (3,2) $ and $ (3,4) $ will change. Hence the answer is $ 2 $ .

## 样例 #1

### 输入

```
4 4 3
1 2 1
2 3 1
2 4 1
3 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7 11 2
1 2 5
1 3 5
2 4 2
2 5 2
3 6 3
3 7 3
4 6 2
3 4 2
6 7 3
4 5 7
4 7 7

```

### 输出

```
4

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
title: "Password"
layout: "post"
diff: 省选/NOI-
pid: CF79D
tag: ['状态合并', '最短路', '差分']
---

# Password

## 题目描述

Finally Fox Ciel arrived in front of her castle!

She have to type a password to enter her castle. An input device attached to her castle is a bit unusual.

The input device is a $ 1×n $ rectangle divided into $ n $ square panels. They are numbered $ 1 $ to $ n $ from left to right. Each panel has a state either ON or OFF. Initially all panels are in the OFF state. She can enter her castle if and only if $ x_{1} $ -th, $ x_{2} $ -th, $ ... $ , $ x_{k} $ -th panels are in the ON state and other panels are in the OFF state.

She is given an array $ a_{1} $ , $ ... $ , $ a_{l} $ . In each move, she can perform the following operation: choose an index $ i $ ( $ 1<=i<=l $ ), choose consecutive $ a_{i} $ panels, and flip the states of those panels (i.e. ON $ → $ OFF, OFF $ → $ ON).

Unfortunately she forgets how to type the password with only above operations. Determine the minimal number of operations required to enter her castle.

## 输入格式

The first line contains three integers $ n $ , $ k $ and $ l $ ( $ 1<=n<=10000,1<=k<=10,1<=l<=100 $ ), separated by single spaces.

The second line contains $ k $ integers $ x_{1} $ , ..., $ x_{k} $ ( $ 1<=x_{1}&lt;x_{2}&lt;...&lt;x_{k}<=n $ ), separated by single spaces.

The third line contains $ l $ integers $ a_{1} $ , ..., $ a_{l} $ ( $ 1<=a_{i}<=n $ ), separated by single spaces. It is possible that some elements of the array $ a_{i} $ are equal value.

## 输出格式

Print the minimal number of moves required to type the password. If it's impossible, print -1.

## 说明/提示

One possible way to type the password in the first example is following: In the first move, choose 1st, 2nd, 3rd panels and flip those panels. In the second move, choose 5th, 6th, 7th, 8th, 9th panels and flip those panels.

## 样例 #1

### 输入

```
10 8 2
1 2 3 5 6 7 8 9
3 5

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 2 1
1 2
3

```

### 输出

```
-1

```



---

---
title: "An unavoidable detour for home"
layout: "post"
diff: 省选/NOI-
pid: CF814E
tag: ['最短路', '构造']
---

# An unavoidable detour for home

## 题目描述

Those unwilling to return home from a long journey, will be affected by the oddity of the snail and lose their way. Mayoi, the oddity's carrier, wouldn't like this to happen, but there's nothing to do with this before a cure is figured out. For now, she would only like to know the enormous number of possibilities to be faced with if someone gets lost.

There are $ n $ towns in the region, numbered from $ 1 $ to $ n $ . The town numbered $ 1 $ is called the capital. The traffic network is formed by bidirectional roads connecting pairs of towns. No two roads connect the same pair of towns, and no road connects a town with itself. The time needed to travel through each of the roads is the same. Lost travelers will not be able to find out how the towns are connected, but the residents can help them by providing the following facts:

- Starting from each town other than the capital, the shortest path (i.e. the path passing through the minimum number of roads) to the capital exists, and is unique;
- Let $ l_{i} $ be the number of roads on the shortest path from town $ i $ to the capital, then $ l_{i}>=l_{i-1} $ holds for all $ 2<=i<=n $ ;
- For town $ i $ , the number of roads connected to it is denoted by $ d_{i} $ , which equals either $ 2 $ or $ 3 $ .

You are to count the number of different ways in which the towns are connected, and give the answer modulo $ 10^{9}+7 $ . Two ways of connecting towns are considered different if a pair $ (u,v) $ ( $ 1<=u,v<=n $ ) exists such there is a road between towns $ u $ and $ v $ in one of them but not in the other.

## 输入格式

The first line of input contains a positive integer $ n $ ( $ 3<=n<=50 $ ) — the number of towns.

The second line contains $ n $ space-separated integers $ d_{1},d_{2},...,d_{n} $ ( $ 2<=d_{i}<=3 $ ) — the number of roads connected to towns $ 1,2,...,n $ , respectively. It is guaranteed that the sum of $ d_{i} $ over all $ i $ is even.

## 输出格式

Output one integer — the total number of different possible ways in which the towns are connected, modulo $ 10^{9}+7 $ .

## 说明/提示

In the first example, the following structure is the only one to satisfy the constraints, the distances from towns $ 2,3,4 $ to the capital are all $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/41aec6960c240a1fb09480a0a613ecf71bad9b6b.png)In the second example, the following two structures satisfy the constraints.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/5dfe5b5d19d9938739604a89ad14ef6620891ff1.png)

## 样例 #1

### 输入

```
4
3 2 3 2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
2 3 3 2 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5
2 2 2 2 2

```

### 输出

```
2

```

## 样例 #4

### 输入

```
20
2 2 2 2 3 2 3 2 2 2 2 2 2 2 2 2 2 3 3 2

```

### 输出

```
82944

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

