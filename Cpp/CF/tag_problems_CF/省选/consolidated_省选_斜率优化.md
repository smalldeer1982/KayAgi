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
title: "Cycling (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2107F2
tag: ['动态规划 DP', '贪心', '斜率优化']
---

# Cycling (Hard Version)

## 题目描述

> 这是此问题的困难版本，和其他版本的区别是此版本中 $1\le n\le 10^6$，且需要对每个前缀都求解。

Leo 骑车去见他的女朋友。在 Leo 的前面有 $n$ 名骑手，从前往后排在第 $i$ 名的骑手的灵活度为 $a_i$。

Leo 将要加速超过前面的所有骑手，他可以执行以下两种操作：
- 当他在骑手 $i$ 后面，骑手 $i+1$ 前面（或 $i=n$）时，付出 $a_i$ 的代价超过骑手 $i$，之后他将在骑手 $i$ 前面，骑手 $i-1$ 后面（如果 $i>1$）；
- 使用他的超级力量交换 $a_i$ 和 $a_j$，代价为 $\vert i-j\vert$。

请你找出超过所有 $n$ 名骑手的最小代价。

额外地，Leo 想知道对于每个 $i(1\le i\le n)$，当只有骑手 $1,2,\cdots,i$ 存在时，他超过所有 $i$ 名骑手的最小代价。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$，表示数据组数。

对于每组数据，第一行一个整数 $n(1\le n\le 10^6)$。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le 10^9)$。

保证单个测试点中 $\sum n\le 10^6$。

## 输出格式

对于每组数据，输出一行 $n$ 个整数，第 $i$ 个数表示只存在前 $i$ 个骑手时的答案。

## 说明/提示

**样例解释**

第一组数据中，当存在所有 $n$ 名骑手时，一组操作如下所示：
- 交换 $a_2$ 和 $a_3$，之后 $a=(1,4,2)$，代价为 $1$；
- 超过第 $3$ 名骑手，代价为 $2$；
- 交换 $a_1$ 和 $a_2$，$a=(4,1,2)$，代价为 $1$；
- 超过第 $2$ 名骑手，代价为 $1$；
- 交换 $a_1$ 和 $a_2$，$a=(1,4,2)$，代价为 $1$；
- 超过第 $1$ 名骑手，代价为 $1$。

总代价为 $7$。可以证明这是最小的代价。

第二组数据中，当存在所有 $n$ 名骑手时，如果一直执行“超过”操作，花费为 $4$。可以证明这是最小的代价。

By chenxi2009

## 样例 #1

### 输入

```
4
3
1 2 4
4
1 1 1 1
2
1 2
4
4 1 3 2
```

### 输出

```
1 3 7
1 2 3 4
1 3
4 3 6 8
```



---

---
title: "Cats Transport"
layout: "post"
diff: 省选/NOI-
pid: CF311B
tag: ['枚举', '斜率优化', '前缀和']
---

# Cats Transport

## 题目描述

Zxr960115 is owner of a large farm. He feeds $ m $ cute cats and employs $ p $ feeders. There's a straight road across the farm and $ n $ hills along the road, numbered from 1 to $ n $ from left to right. The distance between hill $ i $ and $ (i-1) $ is $ d_{i} $ meters. The feeders live in hill 1.

One day, the cats went out to play. Cat $ i $ went on a trip to hill $ h_{i} $ , finished its trip at time $ t_{i} $ , and then waited at hill $ h_{i} $ for a feeder. The feeders must take all the cats. Each feeder goes straightly from hill 1 to $ n $ without waiting at a hill and takes all the waiting cats at each hill away. Feeders walk at a speed of 1 meter per unit time and are strong enough to take as many cats as they want.

For example, suppose we have two hills $ (d_{2}=1) $ and one cat that finished its trip at time 3 at hill 2 $ (h_{1}=2) $ . Then if the feeder leaves hill 1 at time 2 or at time 3, he can take this cat, but if he leaves hill 1 at time 1 he can't take it. If the feeder leaves hill 1 at time 2, the cat waits him for 0 time units, if the feeder leaves hill 1 at time 3, the cat waits him for 1 time units.

Your task is to schedule the time leaving from hill 1 for each feeder so that the sum of the waiting time of all cats is minimized.

## 输入格式

The first line of the input contains three integers $n,m,p$ $(2 \le n\le 10^5,1 \le m \le 10^5, 1\le p \le 100)$.

The second line contains $n-1$ positive integers $d_{2},d_{3},...,d_{n}$  $(1 \le d_{i} < 10^{4}) .$

Each of the next $m$ lines contains two integers $h_i$ and $t_i$ $(1 \le h_i \le n,0 \le t_i \le 10^9)$.

## 输出格式

Output an integer, the minimum sum of waiting time of all cats.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
4 6 2
1 3 5
1 0
2 1
4 9
1 10
2 10
3 12

```

### 输出

```
3

```



---

---
title: "Levels and Regions"
layout: "post"
diff: 省选/NOI-
pid: CF643C
tag: ['斜率优化', '前缀和', '期望']
---

# Levels and Regions

## 题目描述

Radewoosh is playing a computer game. There are $ n $ levels, numbered $ 1 $ through $ n $ . Levels are divided into $ k $ regions (groups). Each region contains some positive number of consecutive levels.

The game repeats the the following process:

1. If all regions are beaten then the game ends immediately. Otherwise, the system finds the first region with at least one non-beaten level. Let $ X $ denote this region.
2. The system creates an empty bag for tokens. Each token will represent one level and there may be many tokens representing the same level.
  - For each already beaten level $ i $ in the region $ X $ , the system adds $ t_{i} $ tokens to the bag (tokens representing the $ i $ -th level).
  - Let $ j $ denote the first non-beaten level in the region $ X $ . The system adds $ t_{j} $ tokens to the bag.
3. Finally, the system takes a uniformly random token from the bag and a player starts the level represented by the token. A player spends one hour and beats the level, even if he has already beaten it in the past.

Given $ n $ , $ k $ and values $ t_{1},t_{2},...,t_{n} $ , your task is to split levels into regions. Each level must belong to exactly one region, and each region must contain non-empty consecutive set of levels. What is the minimum possible expected number of hours required to finish the game?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=n<=200000 $ , $ 1<=k<=min(50,n) $ ) — the number of levels and the number of regions, respectively.

The second line contains $ n $ integers $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=100000 $ ).

## 输出格式

Print one real number — the minimum possible expected value of the number of hours spent to finish the game if levels are distributed between regions in the optimal way. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-4} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643C/73b7e412a182af1e0d063e02722d13792ecaced8.png).

## 说明/提示

In the first sample, we are supposed to split $ 4 $ levels into $ 2 $ regions. It's optimal to create the first region with only one level (it must be the first level). Then, the second region must contain other three levels.

In the second sample, it's optimal to split levels into two regions with $ 3 $ levels each.

## 样例 #1

### 输入

```
4 2
100 3 5 7

```

### 输出

```
5.7428571429

```

## 样例 #2

### 输入

```
6 2
1 2 4 8 16 32

```

### 输出

```
8.5000000000

```



---

