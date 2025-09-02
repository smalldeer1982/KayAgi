# 题目信息

# Ring road

## 题目描述

Nowadays the one-way traffic is introduced all over the world in order to improve driving safety and reduce traffic jams. The government of Berland decided to keep up with new trends. Formerly all $ n $ cities of Berland were connected by $ n $ two-way roads in the ring, i. e. each city was connected directly to exactly two other cities, and from each city it was possible to get to any other city. Government of Berland introduced one-way traffic on all $ n $ roads, but it soon became clear that it's impossible to get from some of the cities to some others. Now for each road is known in which direction the traffic is directed at it, and the cost of redirecting the traffic. What is the smallest amount of money the government should spend on the redirecting of roads so that from every city you can get to any other?

## 样例 #1

### 输入

```
3
1 3 1
1 2 1
3 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 3 1
1 2 5
3 2 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
6
1 5 4
5 3 8
2 4 15
1 6 16
2 3 23
4 6 42
```

### 输出

```
39
```

## 样例 #4

### 输入

```
4
1 2 9
2 3 8
3 4 7
4 1 5
```

### 输出

```
0
```

# AI分析结果



# Ring road

## 题目描述

现在全世界都引入单向交通以提高驾驶安全性并减少交通堵塞。Berland 政府决定跟上新趋势。原先 Berland 的所有 $n$ 个城市通过 $n$ 条双向道路连接成环状，即每个城市直接连接两个其他城市，且可以从任一城市到达其他任何城市。政府将所有 $n$ 条道路改为单向，但很快发现某些城市之间无法通行。已知每条道路的当前方向及调整方向的成本，求政府需要投入的最小资金来调整道路方向，使得所有城市可以互相到达。

## 样例 #1

### 输入
```
3
1 3 1
1 2 1
3 2 1
```

### 输出
```
1
```

## 样例 #2

### 输入
```
3
1 3 1
1 2 5
3 2 1
```

### 输出
```
2
```

## 样例 #3

### 输入
```
6
1 5 4
5 3 8
2 4 15
1 6 16
2 3 23
4 6 42
```

### 输出
```
39
```

## 样例 #4

### 输入
```
4
1 2 9
2 3 8
3 4 7
4 1 5
```

### 输出
```
0
```

**算法分类**：图论

---

### 题解分析与结论

所有题解均围绕环状结构的特性展开，核心思路是发现合法解只能是全顺时针或全逆时针的单向环。关键差异在于实现方式：

1. **贪心思路**（Fearliciz）：通过统计两种环方向的总调整成本，取较小值。时间复杂度 O(n)。
2. **DFS遍历**（多个题解）：显式遍历两种环方向，计算各自成本。时间复杂度 O(n)。

---

### 高星题解推荐

1. **Fearliciz（★★★★☆）**
   - **关键亮点**：创新性贪心思路，利用环的对称性将问题简化为两种情况。代码极简，仅需遍历一次边集。
   - **代码核心**：
     ```cpp
     // 维护出度入度，动态计算一种环方向的调整成本
     if (from[x]) cnt += z; 
     cout << min(sum - cnt, cnt);
     ```

2. **Wsy_flying_forever（★★★★☆）**
   - **关键亮点**：双向建图后仅需两次DFS遍历，清晰体现环的双向特性。
   - **代码核心**：
     ```cpp
     void dfs(int x, int fa, int cost) {
         if (环形成) 更新答案;
         for (两种方向边) dfs(...);
     }
     ```

3. **WRuperD（★★★★☆）**
   - **关键亮点**：简洁的DFS实现，通过参数传递累计成本，避免全局变量。
   - **代码核心**：
     ```cpp
     dfs(1,0,0); // 两种方向的遍历
     dfs(1,0,0); // 隐含两种路径选择
     ```

---

### 最优思路总结

**关键技巧**：  
- **环的对称性**：所有合法解必为顺时针或逆时针单向环，只需计算这两种情况的成本。
- **成本互补性**：两种方向的总调整成本之和等于所有边反向成本总和，无需重复计算。

**代码优化**：  
- 贪心法通过动态维护节点出入度，在 O(n) 时间内直接推导两种方向的成本。
- DFS法通过双向建图（正向成本0，反向成本w），实现简洁的环遍历。

---

### 拓展与心得

**同类问题**：  
- 基环树相关问题（如 CF1027F）
- 强连通分量最小调整问题（如 POJ 1236）

**调试心得**：  
- 多个题解提到最初未意识到环方向仅有两种可能，通过样例分析才顿悟问题本质。
- 贪心法实现时需注意边的处理顺序不影响最终统计结果，需严格验证对称性。

---

### 推荐习题
1. [P1347 排序](https://www.luogu.com.cn/problem/P1347)（拓扑排序与环检测）
2. [P2741 [USACO4.4] 重叠矩形](https://www.luogu.com.cn/problem/P2741)（环状结构处理）
3. [CF875F Royal Questions](https://www.luogu.com.cn/problem/CF875F)（基环树应用）

---
处理用时：119.18秒