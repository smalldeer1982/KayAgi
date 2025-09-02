# 题目信息

# Rudolf and CodeVid-23

## 题目描述

A new virus called "CodeVid-23" has spread among programmers. Rudolf, being a programmer, was not able to avoid it.

There are $ n $ symptoms numbered from $ 1 $ to $ n $ that can appear when infected. Initially, Rudolf has some of them. He went to the pharmacy and bought $ m $ medicines.

For each medicine, the number of days it needs to be taken is known, and the set of symptoms it removes. Unfortunately, medicines often have side effects. Therefore, for each medicine, the set of symptoms that appear when taking it is also known.

After reading the instructions, Rudolf realized that taking more than one medicine at a time is very unhealthy.

Rudolph wants to be healed as soon as possible. Therefore, he asks you to calculate the minimum number of days to remove all symptoms, or to say that it is impossible.

## 说明/提示

In the first example, we can first apply medicine number $ 4 $ , after which the symptoms will look like "00101". After that, medicine number $ 2 $ , then all symptoms will disappear, and the number of days will be $ 5 + 3 = 8 $ . Another option is to apply the medicines in the order $ 1, 3, 2 $ . In this case, all symptoms will also disappear, but the number of days will be $ 3 + 3 + 3 = 9 $ .

In the second example, there are no symptoms initially, so the treatment will take $ 0 $ days.

In the third example, there are no options to remove all symptoms.

## 样例 #1

### 输入

```
4
5 4
10011
3
10000
00110
3
00101
00000
3
01010
00100
5
11010
00100
4 1
0000
10
1011
0100
2 2
11
2
10
01
3
01
10
2 3
11
3
01
10
3
10
00
4
10
01```

### 输出

```
8
0
-1
6```

# AI分析结果

### 题目内容重写

#### 题目描述

一种名为“CodeVid-23”的新病毒在程序员中传播开来。Rudolf 作为一名程序员，也不幸感染了这种病毒。

感染后可能会出现编号从 $1$ 到 $n$ 的 $n$ 种症状。最初，Rudolf 表现出其中的一些症状。他去了药店，购买了 $m$ 种药物。

对于每种药物，已知其需要服用的天数，以及它能消除的症状集合。不幸的是，药物通常会有副作用。因此，对于每种药物，已知服用后会出现的新症状集合。

在阅读了说明书后，Rudolf 意识到同时服用多种药物是非常不健康的。

Rudolf 希望尽快康复。因此，他请你计算消除所有症状所需的最少天数，或者判断这是否是不可能的。

#### 说明/提示

在第一个样例中，我们可以先服用药物 $4$，之后症状将变为 "00101"。接着服用药物 $2$，所有症状将消失，所需天数为 $5 + 3 = 8$。另一种选择是按顺序服用药物 $1, 3, 2$，所有症状也会消失，但所需天数为 $3 + 3 + 3 = 9$。

在第二个样例中，初始时没有症状，因此治疗需要 $0$ 天。

在第三个样例中，没有消除所有症状的方案。

#### 样例输入

```
4
5 4
10011
3
10000
00110
3
00101
00000
3
01010
00100
5
11010
00100
4 1
0000
10
1011
0100
2 2
11
2
10
01
3
01
10
2 3
11
3
01
10
3
10
00
4
10
01
```

#### 样例输出

```
8
0
-1
6
```

### 算法分类
最短路

### 题解分析与结论

这道题的核心是将症状的状态表示为二进制数，通过药物的作用进行状态转移，最终求从初始状态到全零状态的最短路径。题解中大多数解法都采用了 Dijkstra 算法，利用位运算进行状态转移，最终求得最短时间。

### 评分较高的题解

#### 题解1：作者：tbdsh (赞：4)
**星级：5星**
**关键亮点：**
- 详细解释了如何通过位运算进行状态转移，思路清晰。
- 代码简洁，可读性强，使用了 Dijkstra 算法。
- 提供了状态转移的公式，帮助理解。

**核心代码：**
```cpp
int u = (v & (((1 << n) - 1) ^ a[i].z)) | a[i].d;
dis[u] = min(dis[u], dis[v] + w);
```
**核心思想：**
通过位运算计算服用药物后的新状态，并更新最短路径。

#### 题解2：作者：Coffee_zzz (赞：3)
**星级：4星**
**关键亮点：**
- 详细分析了如何通过位运算进行状态转移，思路清晰。
- 代码结构清晰，使用了 Dijkstra 算法。
- 提供了状态转移的详细解释。

**核心代码：**
```cpp
int w = a[i].day, u = (v & (((1 << n) - 1) ^ a[i].z)) | a[i].d;
dis[u] = min(dis[u], dis[v] + w);
```
**核心思想：**
通过位运算计算服用药物后的新状态，并更新最短路径。

#### 题解3：作者：未来姚班zyl (赞：2)
**星级：4星**
**关键亮点：**
- 提供了状态转移的详细解释，思路清晰。
- 代码简洁，使用了 Dijkstra 算法。
- 提供了状态转移的公式，帮助理解。

**核心代码：**
```cpp
int nx = (i & state0) | state1;
add(i, nx, w);
```
**核心思想：**
通过位运算计算服用药物后的新状态，并更新最短路径。

### 最优关键思路或技巧
- **位运算**：通过位运算高效地进行状态转移，减少了计算复杂度。
- **Dijkstra 算法**：利用 Dijkstra 算法求最短路径，适用于正权图。
- **状态压缩**：将症状状态压缩为二进制数，方便进行状态转移和存储。

### 可拓展之处
- **类似题目**：可以扩展到其他需要状态转移的问题，如状态机、自动机等。
- **优化**：可以考虑使用 A* 算法或其他启发式搜索算法进行优化。

### 推荐题目
1. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
2. [P1462 通往奥格瑞玛的道路](https://www.luogu.com.cn/problem/P1462)
3. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)

### 个人心得
- **调试经历**：在实现位运算时，需要注意位运算的优先级，避免出现错误。
- **顿悟感想**：通过位运算进行状态转移，极大地简化了问题的复杂度，提高了代码的效率。

---
处理用时：45.33秒