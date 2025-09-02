# 题目信息

# Anna, Svyatoslav and Maps

## 题目描述

The main characters have been omitted to be short.

You are given a directed unweighted graph without loops with $ n $ vertexes and a path in it (that path is not necessary simple) given by a sequence $ p_1, p_2, \ldots, p_m $ of $ m $ vertexes; for each $ 1 \leq i < m $ there is an arc from $ p_i $ to $ p_{i+1} $ .

Define the sequence $ v_1, v_2, \ldots, v_k $ of $ k $ vertexes as good, if $ v $ is a subsequence of $ p $ , $ v_1 = p_1 $ , $ v_k = p_m $ , and $ p $ is one of the shortest paths passing through the vertexes $ v_1 $ , $ \ldots $ , $ v_k $ in that order.

A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements. It is obvious that the sequence $ p $ is good but your task is to find the shortest good subsequence.

If there are multiple shortest good subsequences, output any of them.

## 说明/提示

Below you can see the graph from the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1204C/71cf125b3567a608d3e838a04ba123f82afa0825.png)

The given path is passing through vertexes $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ . The sequence $ 1-2-4 $ is good because it is the subsequence of the given path, its first and the last elements are equal to the first and the last elements of the given path respectively, and the shortest path passing through vertexes $ 1 $ , $ 2 $ and $ 4 $ in that order is $ 1-2-3-4 $ . Note that subsequences $ 1-4 $ and $ 1-3-4 $ aren't good because in both cases the shortest path passing through the vertexes of these sequences is $ 1-3-4 $ .

In the third example, the graph is full so any sequence of vertexes in which any two consecutive elements are distinct defines a path consisting of the same number of vertexes.

In the fourth example, the paths $ 1-2-4 $ and $ 1-3-4 $ are the shortest paths passing through the vertexes $ 1 $ and $ 4 $ .

## 样例 #1

### 输入

```
4
0110
0010
0001
1000
4
1 2 3 4
```

### 输出

```
3
1 2 4 ```

## 样例 #2

### 输入

```
4
0110
0010
1001
1000
20
1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4
```

### 输出

```
11
1 2 4 2 4 2 4 2 4 2 4 ```

## 样例 #3

### 输入

```
3
011
101
110
7
1 2 3 1 3 2 1
```

### 输出

```
7
1 2 3 1 3 2 1 ```

## 样例 #4

### 输入

```
4
0110
0001
0001
1000
3
1 2 4
```

### 输出

```
2
1 4 ```

# AI分析结果

### 题目翻译
# Anna、Svyatoslav和地图

## 题目描述
为了简洁起见，省略了主要人物。

给定一个有 $n$ 个顶点的有向无环且无自环的图，以及图中的一条路径（该路径不一定是简单路径），用一个包含 $m$ 个顶点的序列 $p_1, p_2, \ldots, p_m$ 表示；对于每个 $1 \leq i < m$，都存在一条从 $p_i$ 到 $p_{i + 1}$ 的弧。

定义一个包含 $k$ 个顶点的序列 $v_1, v_2, \ldots, v_k$ 为“好”序列，如果 $v$ 是 $p$ 的子序列，$v_1 = p_1$，$v_k = p_m$，并且 $p$ 是按顺序经过顶点 $v_1, \ldots, v_k$ 的最短路径之一。

如果序列 $a$ 可以通过删除序列 $b$ 中的若干（可能为零个或全部）元素得到，则称 $a$ 是 $b$ 的子序列。显然，序列 $p$ 是一个“好”序列，但你的任务是找到最短的“好”子序列。

如果存在多个最短的“好”子序列，输出其中任意一个即可。

## 说明/提示
下面是第一个样例中的图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1204C/71cf125b3567a608d3e838a04ba123f82afa0825.png)

给定的路径经过顶点 $1$、$2$、$3$、$4$。序列 $1 - 2 - 4$ 是“好”序列，因为它是给定路径的子序列，其第一个和最后一个元素分别等于给定路径的第一个和最后一个元素，并且按顺序经过顶点 $1$、$2$ 和 $4$ 的最短路径是 $1 - 2 - 3 - 4$。注意，子序列 $1 - 4$ 和 $1 - 3 - 4$ 不是“好”序列，因为在这两种情况下，经过这些序列顶点的最短路径都是 $1 - 3 - 4$。

在第三个样例中，图是完全图，因此任何顶点序列（其中任意两个相邻元素都不同）都定义了一条包含相同数量顶点的路径。

在第四个样例中，路径 $1 - 2 - 4$ 和 $1 - 3 - 4$ 是经过顶点 $1$ 和 $4$ 的最短路径。

## 样例 #1
### 输入
```
4
0110
0010
0001
1000
4
1 2 3 4
```
### 输出
```
3
1 2 4
```

## 样例 #2
### 输入
```
4
0110
0010
1001
1000
20
1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4
```
### 输出
```
11
1 2 4 2 4 2 4 2 4 2 4
```

## 样例 #3
### 输入
```
3
011
101
110
7
1 2 3 1 3 2 1
```
### 输出
```
7
1 2 3 1 3 2 1
```

## 样例 #4
### 输入
```
4
0110
0001
0001
1000
3
1 2 4
```
### 输出
```
2
1 4
```

### 算法分类
最短路

### 综合分析与结论
这些题解的核心思路都是先使用 Floyd 算法预处理出图中任意两点之间的最短路径，然后根据最短路径的信息来判断原路径序列中的哪些点可以被删除，从而得到最短的“好”子序列。不同题解的主要区别在于判断点是否可以删除的具体方法和实现细节。

### 所选题解
- **作者：te5555 (赞：8)，4星**
    - **关键亮点**：思路清晰，代码简洁，通过记录当前累计距离和最短距离的比较来判断点是否可以删除。
    - **个人心得**：无
- **作者：兮水XiShui丶 (赞：8)，4星**
    - **关键亮点**：通过分析最短路径和序列长度的关系来判断点是否可以删除，逻辑明确。
    - **个人心得**：个人感觉比 D 难。
- **作者：Minakami_Yuki (赞：4)，4星**
    - **关键亮点**：使用栈来维护答案序列，通过贪心的方法判断点是否可以删除，实现较为巧妙。
    - **个人心得**：考场没做出来，身败名裂。

### 重点代码
#### 作者：te5555
```cpp
// Floyd 预处理最短路径
for (register int k = 1; k <= n; k++) {
    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j <= n; j++) {
            dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
        }
    }
}
v.push_back(p[1]);
int las = p[1];
int cur = 0;
// 判断点是否可以删除
for (register int i = 2; i <= m; i++) {
    cur += dis[p[i - 1]][p[i]];
    if (dis[las][p[i]] < cur)
        las = p[i - 1], v.push_back(las), cur = dis[las][p[i]];
}
v.push_back(p[m]);
```
**核心实现思想**：先使用 Floyd 算法求出任意两点之间的最短路径，然后遍历原路径序列，记录当前累计距离 `cur`，当从上次保留的点 `las` 到当前点 `p[i]` 的最短距离小于 `cur` 时，说明中间的点不能删除，将上一个点加入答案序列，并更新 `las` 和 `cur`。

#### 作者：兮水XiShui丶
```cpp
// Floyd 预处理最短路径
for (int k = 1; k <= n; k++) 
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++) 
            G[i][j] = min (G[i][j], G[i][k] + G[k][j]);
int st = 1, now = 2;
// 判断点是否可以删除
while (now <= m) {
    int diss = now - st;
    if (diss == G[point[st]][point[now]]) {
        if (head <= tai)
            head++;
        qu[++tai] = now;
        now++;
    }
    else {
        ans[++idx] = point[st];
        if (head <= tai)
            st = qu[head++];
    }
}
ans[++idx] = point[st];
if (ans[idx] != point[m])
    ans[++idx] = point[m];
```
**核心实现思想**：同样先使用 Floyd 算法预处理最短路径，然后使用双指针 `st` 和 `now` 遍历原路径序列，当从 `point[st]` 到 `point[now]` 的最短路径长度等于 `now - st` 时，说明中间的点可以删除，将 `now` 加入队列；否则，将 `point[st]` 加入答案序列，并更新 `st`。

#### 作者：Minakami_Yuki
```cpp
// Floyd 预处理最短路径
for (register int k = 1; k <= n; k++) {
    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j <= n; j++) {
            f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
        }
    }
}
s[++stop] = a[1];
// 判断点是否可以删除
for (register int i = 2; i <= m; i++) {
    if (f[s[stop]][a[i + 1]] != f[s[stop]][a[i]] + f[a[i]][a[i + 1]]) s[++stop] = a[i];
}
```
**核心实现思想**：先使用 Floyd 算法求出最短路径，然后使用栈 `s` 维护答案序列，遍历原路径序列，当从栈顶元素 `s[stop]` 到 `a[i + 1]` 的最短路径不等于从 `s[stop]` 到 `a[i]` 再到 `a[i + 1]` 的最短路径之和时，说明 `a[i]` 不能删除，将其加入栈中。

### 最优关键思路或技巧
- 使用 Floyd 算法预处理最短路径，时间复杂度为 $O(n^3)$，可以方便地得到任意两点之间的最短距离。
- 贪心策略：根据最短路径的信息，判断原路径序列中的点是否可以删除，从而得到最短的“好”子序列。

### 拓展思路
同类型题或类似算法套路：
- 涉及图的路径优化问题，如求图中满足特定条件的最短路径、最长路径等。
- 子序列优化问题，需要根据一定的规则从原序列中选择元素，得到满足条件的最短或最长子序列。

### 推荐题目
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：涉及 Floyd 算法和图的动态更新。
- [P2888 [USACO07NOV]Sunscreen G](https://www.luogu.com.cn/problem/P2888)：贪心算法的应用。
- [P1629 邮递员送信](https://www.luogu.com.cn/problem/P1629)：最短路问题，需要考虑往返的情况。

---
处理用时：63.77秒