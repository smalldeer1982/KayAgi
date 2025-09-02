---
title: "James and the Chase"
layout: "post"
diff: 省选/NOI-
pid: CF1361E
tag: ['Tarjan', '随机化']
---

# James and the Chase

## 题目描述

James Bond has a new plan for catching his enemy. There are some cities and directed roads between them, such that it is possible to travel between any two cities using these roads. When the enemy appears in some city, Bond knows her next destination but has no idea which path she will choose to move there.

The city $ a $ is called interesting, if for each city $ b $ , there is exactly one simple path from $ a $ to $ b $ . By a simple path, we understand a sequence of distinct cities, such that for every two neighboring cities, there exists a directed road from the first to the second city.

Bond's enemy is the mistress of escapes, so only the chase started in an interesting city gives the possibility of catching her. James wants to arrange his people in such cities. However, if there are not enough interesting cities, the whole action doesn't make sense since Bond's people may wait too long for the enemy.

You are responsible for finding all the interesting cities or saying that there is not enough of them. By not enough, James means strictly less than $ 20\% $ of all cities.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 2\,000 $ ) — the number of test cases. Each test case is described as follows:

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n \le 10^5 $ , $ 0 \leq m \le 2 \cdot 10^5 $ ) — the number of cities and roads between them. Each of the following $ m $ lines contains two integers $ u $ , $ v $ ( $ u \neq v $ ; $ 1 \leq u, v \leq n $ ), which denote that there is a directed road from $ u $ to $ v $ .

You can assume that between each ordered pair of cities there is at most one road. The sum of $ n $ over all test cases doesn't exceed $ 10^5 $ , and the sum of $ m $ doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

If strictly less than $ 20\% $ of all cities are interesting, print $ -1 $ . Otherwise, let $ k $ be the number of interesting cities. Print $ k $ distinct integers in increasing order — the indices of interesting cities.

## 说明/提示

In all drawings, if a city is colored green, then it is interesting; otherwise, it is colored red.

In the first sample, each city is interesting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/ea02130aaa657158e02932dc79202b09c65411df.png)In the second sample, no city is interesting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/9f70c6807b725116da2e28994dd20c33629e3f31.png)In the third sample, cities $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ are interesting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/f1d050ad3537d17cb3725772a1afecd8c2c46f32.png)In the last sample, only the city $ 1 $ is interesting. It is strictly less than $ 20\% $ of all cities, so the answer is $ -1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/d74f523bcab5b0c943643c6309e1f1139462efcb.png)

## 样例 #1

### 输入

```
4
3 3
1 2
2 3
3 1
3 6
1 2
2 1
2 3
3 2
1 3
3 1
7 10
1 2
2 3
3 1
1 4
4 5
5 1
4 6
6 7
7 4
6 1
6 8
1 2
2 3
3 4
4 5
5 6
6 1
6 2
5 1
```

### 输出

```
1 2 3 
-1
1 2 3 5 
-1
```



---

---
title: "Beautiful Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1904F
tag: ['倍增', '强连通分量', 'Tarjan', '最近公共祖先 LCA']
---

# Beautiful Tree

## 题目描述

Lunchbox has a tree of size $ n $ rooted at node $ 1 $ . Each node is then assigned a value. Lunchbox considers the tree to be beautiful if each value is distinct and ranges from $ 1 $ to $ n $ . In addition, a beautiful tree must also satisfy $ m $ requirements of $ 2 $ types:

- "1 a b c" — The node with the smallest value on the path between nodes $ a $ and $ b $ must be located at $ c $ .
- "2 a b c" — The node with the largest value on the path between nodes $ a $ and $ b $ must be located at $ c $ .

Now, you must assign values to each node such that the resulting tree is beautiful. If it is impossible to do so, output $ -1 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \le n, m \le 2 \cdot 10^5 $ ).

The next $ n - 1 $ lines contain two integers $ u $ and $ v $ ( $ 1 \le u, v \le n, u \ne v $ ) — denoting an edge between nodes $ u $ and $ v $ . It is guaranteed that the given edges form a tree.

The next $ m $ lines each contain four integers $ t $ , $ a $ , $ b $ , and $ c $ ( $ t \in \{1,2\} $ , $ 1 \le a, b, c \le n $ ). It is guaranteed that node $ c $ is on the path between nodes $ a $ and $ b $ .

## 输出格式

If it is impossible to assign values such that the tree is beautiful, output $ -1 $ . Otherwise, output $ n $ integers, the $ i $ -th of which denotes the value of node $ i $ .

## 样例 #1

### 输入

```
7 5
1 2
1 3
1 4
3 5
4 6
3 7
1 6 5 1
2 6 7 3
1 2 7 1
1 7 5 7
2 4 2 2
```

### 输出

```
1 6 7 5 3 4 2
```

## 样例 #2

### 输入

```
2 2
1 2
1 1 2 1
1 1 2 2
```

### 输出

```
-1
```



---

---
title: "Leaders"
layout: "post"
diff: 省选/NOI-
pid: CF97E
tag: ['Tarjan']
---

# Leaders

## 题目描述

After a revolution in Berland the new dictator faced an unexpected challenge: the country has to be somehow ruled. The dictator is a very efficient manager, yet he can't personally give orders to each and every citizen. That's why he decided to pick some set of leaders he would control. Those leaders will directly order the citizens. However, leadership efficiency turned out to vary from person to person (i.e. while person A makes an efficient leader, person B may not be that good at it). That's why the dictator asked world-famous berland scientists for help. The scientists suggested an innovatory technology — to make the leaders work in pairs.

A relationship graph is some undirected graph whose vertices correspond to people. A simple path is a path with no repeated vertices. Long and frighteningly expensive research showed that a pair of people has maximum leadership qualities if a graph of relationships has a simple path between them with an odd number of edges. The scientists decided to call such pairs of different people leader pairs. Secret services provided the scientists with the relationship graph so that the task is simple — we have to learn to tell the dictator whether the given pairs are leader pairs or not. Help the scientists cope with the task.

## 输入格式

The first line contains integers $ n $ and $ m $ ( $ 1<=n<=10^{5},0<=m<=10^{5} $ ) — the number of vertices and edges in the relationship graph correspondingly. Next $ m $ lines contain pairs of integers $ a $ and $ b $ which mean that there is an edge between the $ a $ -th and the $ b $ -th vertices (the vertices are numbered starting from $ 1 $ , $ 1<=a,b<=n $ ). It is guaranteed that the graph has no loops or multiple edges.

Next line contains number $ q $ ( $ 1<=q<=10^{5} $ ) — the number of pairs the scientists are interested in. Next $ q $ lines contain these pairs (in the same format as the edges, the queries can be repeated, a query can contain a pair of the identical vertices).

## 输出格式

For each query print on a single line "Yes" if there's a simple odd path between the pair of people; otherwise, print "No".

## 说明/提示

Notes to the samples:

1\) Between vertices 1 and 2 there are 2 different simple paths in total: 1-3-2 and 1-4-2. Both of them consist of an even number of edges.

2\) Vertices 1 and 3 are connected by an edge, that's why a simple odd path for them is 1-3.

5\) Vertices 1 and 5 are located in different connected components, there's no path between them.

## 样例 #1

### 输入

```
7 7
1 3
1 4
2 3
2 4
5 6
6 7
7 5
8
1 2
1 3
1 4
2 4
1 5
5 6
5 7
6 7

```

### 输出

```
No
Yes
Yes
Yes
No
Yes
Yes
Yes

```



---

