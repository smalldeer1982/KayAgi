---
title: "Trails and Glades"
layout: "post"
diff: 提高+/省选-
pid: CF209C
tag: ['连通块', '欧拉回路', '概率论']
---

# Trails and Glades

## 题目描述

Vasya went for a walk in the park. The park has $ n $ glades, numbered from 1 to $ n $ . There are $ m $ trails between the glades. The trails are numbered from 1 to $ m $ , where the $ i $ -th trail connects glades $ x_{i} $ and $ y_{i} $ . The numbers of the connected glades may be the same $ (x_{i}=y_{i}) $ , which means that a trail connects a glade to itself. Also, two glades may have several non-intersecting trails between them.

Vasya is on glade 1, he wants to walk on all trails of the park exactly once, so that he can eventually return to glade 1. Unfortunately, Vasya does not know whether this walk is possible or not. Help Vasya, determine whether the walk is possible or not. If such walk is impossible, find the minimum number of trails the authorities need to add to the park in order to make the described walk possible.

Vasya can shift from one trail to another one only on glades. He can move on the trails in both directions. If Vasya started going on the trail that connects glades $ a $ and $ b $ , from glade $ a $ , then he must finish this trail on glade $ b $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=10^{6}; 0<=m<=10^{6}) $ — the number of glades in the park and the number of trails in the park, respectively. Next $ m $ lines specify the trails. The $ i $ -th line specifies the $ i $ -th trail as two space-separated numbers, $ x_{i} $ , $ y_{i} $ $ (1<=x_{i},y_{i}<=n) $ — the numbers of the glades connected by this trail.

## 输出格式

Print the single integer — the answer to the problem. If Vasya's walk is possible without adding extra trails, print 0, otherwise print the minimum number of trails the authorities need to add to the park in order to make Vasya's walk possible.

## 说明/提示

In the first test case the described walk is possible without building extra trails. For example, let's first go on the first trail, then on the second one, and finally on the third one.

In the second test case the described walk is impossible without adding extra trails. To make the walk possible, it is enough to add one trail, for example, between glades number one and two.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
2 5
1 1
1 2
1 2
2 2
1 2

```

### 输出

```
1

```



---

---
title: "Connected Components?"
layout: "post"
diff: 提高+/省选-
pid: CF920E
tag: ['枚举', '广度优先搜索 BFS', '连通块']
---

# Connected Components?

## 题目描述

You are given an undirected graph consisting of $ n $ vertices and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920E/2671f3d87e6b285ebb30abeafea800e65bb56d51.png) edges. Instead of giving you the edges that exist in the graph, we give you $ m $ unordered pairs ( $ x,y $ ) such that there is no edge between $ x $ and $ y $ , and if some pair of vertices is not listed in the input, then there is an edge between these vertices.

You have to find the number of connected components in the graph and the size of each component. A connected component is a set of vertices $ X $ such that for every two vertices from this set there exists at least one path in the graph connecting these vertices, but adding any other vertex to $ X $ violates this rule.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=200000 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920E/2a08d4fdef413c2e634516e97a2188a97c148ac8.png)).

Then $ m $ lines follow, each containing a pair of integers $ x $ and $ y $ ( $ 1<=x,y<=n $ , $ x≠y $ ) denoting that there is no edge between $ x $ and $ y $ . Each pair is listed at most once; ( $ x,y $ ) and ( $ y,x $ ) are considered the same (so they are never listed in the same test). If some pair of vertices is not listed in the input, then there exists an edge between those vertices.

## 输出格式

Firstly print $ k $ — the number of connected components in this graph.

Then print $ k $ integers — the sizes of components. You should output these integers in non-descending order.

## 样例 #1

### 输入

```
5 5
1 2
3 4
3 2
4 2
2 5

```

### 输出

```
2
1 4 
```



---

---
title: "Lucky Country"
layout: "post"
diff: 提高+/省选-
pid: CF95E
tag: ['背包 DP', '连通块', '进制']
---

# Lucky Country

## 题目描述

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 744 $ , $ 4 $ are lucky and $ 5 $ , $ 17 $ , $ 467 $ are not.

One night Petya was sleeping. He was dreaming of being the president of some island country. The country is represented by islands connected by two-way roads. Between some islands there is no road way, even through other islands, that's why the country is divided into several regions. More formally, each island belongs to exactly one region, there is a path between any two islands located in the same region; there is no path between any two islands from different regions. A region is lucky if the amount of islands in it is a lucky number.

As a real president, Petya first decided to build a presidential palace. Being a lucky numbers' fan, Petya wants to position his palace in one of the lucky regions. However, it is possible that initially the country has no such regions. In this case Petya can build additional roads between different regions, thus joining them. Find the minimum number of roads needed to build to create a lucky region.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{5} $ ). They are the number of islands and the number of roads correspondingly. Next $ m $ lines contain road descriptions. Each road is defined by the numbers of islands that it connects: that is, by two integers $ u $ and $ v $ ( $ 1<=u,v<=n $ ). Some roads can connect an island with itself; there can be more than one road between a pair of islands. Numbers in each line are separated by exactly one space character.

## 输出格式

If there's no solution, output the only number "-1" (without the quotes). Otherwise, output the minimum number of roads $ r $ that need to be built to get a lucky region.

## 样例 #1

### 输入

```
4 3
1 2
2 3
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5 4
1 2
3 4
4 5
3 5

```

### 输出

```
-1

```



---

---
title: "A Mist of Florescence"
layout: "post"
diff: 提高+/省选-
pid: CF989C
tag: ['连通块', '构造']
---

# A Mist of Florescence

## 题目描述

**题目大意：**

让你构造一个$n*m$矩阵，这个矩阵由4种字符填充构成，给定4个整数，即矩阵中每种字符构成的四联通块个数，$n,m$需要你自己定，但是不能超过50

## 输入格式

一行，四个整数$a,b,c,d$，即每种字符构成的四联通块个数，$1<=a,b,c,d<=100$

## 输出格式

一个矩阵

感谢@守望 提供翻译

## 样例 #1

### 输入

```
5 3 2 1

```

### 输出

```
4 7
DDDDDDD
DABACAD
DBABACD
DDDDDDD
```

## 样例 #2

### 输入

```
50 50 1 1

```

### 输出

```
4 50
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
ABABABABABABABABABABABABABABABABABABABABABABABABAB
BABABABABABABABABABABABABABABABABABABABABABABABABA
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
```

## 样例 #3

### 输入

```
1 6 4 5

```

### 输出

```
7 7
DDDDDDD
DDDBDBD
DDCDCDD
DBDADBD
DDCDCDD
DBDBDDD
DDDDDDD
```



---

