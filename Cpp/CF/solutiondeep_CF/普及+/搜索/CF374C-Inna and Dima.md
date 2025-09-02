# 题目信息

# Inna and Dima

## 题目描述

Inna and Dima bought a table of size $ n×m $ in the shop. Each cell of the table contains a single letter: "D", "I", "M", "A".

Inna loves Dima, so she wants to go through his name as many times as possible as she moves through the table. For that, Inna acts as follows:

1. initially, Inna chooses some cell of the table where letter "D" is written;
2. then Inna can move to some side-adjacent table cell that contains letter "I"; then from this cell she can go to one of the side-adjacent table cells that contains the written letter "M"; then she can go to a side-adjacent cell that contains letter "A". Then Inna assumes that she has gone through her sweetheart's name;
3. Inna's next move can be going to one of the side-adjacent table cells that contains letter "D" and then walk on through name DIMA in the similar manner. Inna never skips a letter. So, from the letter "D" she always goes to the letter "I", from the letter "I" she always goes the to letter "M", from the letter "M" she always goes to the letter "A", and from the letter "A" she always goes to the letter "D".

Depending on the choice of the initial table cell, Inna can go through name DIMA either an infinite number of times or some positive finite number of times or she can't go through his name once. Help Inna find out what maximum number of times she can go through name DIMA.

## 说明/提示

Notes to the samples:

In the first test sample, Inna cannot go through name DIMA a single time.

In the second test sample, Inna can go through the infinite number of words DIMA. For that, she should move in the clockwise direction starting from the lower right corner.

In the third test sample the best strategy is to start from the cell in the upper left corner of the table. Starting from this cell, Inna can go through name DIMA four times.

## 样例 #1

### 输入

```
1 2
DI
```

### 输出

```
Poor Dima!
```

## 样例 #2

### 输入

```
2 2
MA
ID
```

### 输出

```
Poor Inna!
```

## 样例 #3

### 输入

```
5 5
DIMAD
DIMAI
DIMAM
DDMAA
AAMID
```

### 输出

```
4
```

# AI分析结果



### 题目内容中文重写

#### 题目名称：Inna and Dima

**题目描述**  
Inna和Dima在商店购买了一个大小为 $n×m$ 的表格。每个单元格包含一个字母："D"、"I"、"M"或"A"。

Inna深爱Dima，因此她希望通过在表格中移动尽可能多次地遍历他的名字"DIMA"。具体规则如下：  
1. 初始时，Inna必须选择一个包含字母"D"的单元格；  
2. 从"D"出发，她只能移动到相邻（上下左右）的"I"；接着从"I"移动到相邻的"M"；再移动到相邻的"A"；完成一次完整的"DIMA"遍历；  
3. 完成一次遍历后，她必须从"A"移动到相邻的"D"开始下一次遍历，循环往复。  

请帮助Inna确定，从某个初始"D"出发，最多能完成多少次完整的"DIMA"遍历。若可以无限循环则输出对应提示。

**输入输出样例**  
样例1：  
输入：  
1 2  
DI  
输出：  
Poor Dima!  

样例2：  
输入：  
2 2  
MA  
ID  
输出：  
Poor Inna!  

样例3：  
输入：  
5 5  
DIMAD  
DIMAI  
DIMAM  
DDMAA  
AAMID  
输出：  
4  

---

### 题解综合分析

#### 核心思路与关键技巧
1. **建图策略**：将表格映射为有向图，每个单元格为一个节点。根据字母顺序建立边（D→I→M→A→D）。
2. **判环检测**：DFS过程中维护访问标记，若在搜索路径中重复访问同一节点，则存在无限循环。
3. **记忆化搜索**：记录每个节点的最长路径长度（`dis[]`数组），避免重复计算。
4. **步数转换**：总步数除以4得到完整"DIMA"次数（每个字母对应一步）。

#### 优化亮点
- **邻接表建图**：仅存储有效移动边，空间复杂度优化至$O(nm)$。
- **双标记法**：用`vis[]`标记当前路径节点（判环），`dis[]`记录已计算节点的最长路径。
- **提前终止**：发现环时立即终止程序，减少无效计算。

---

### 高星题解推荐

#### 1. 作者：Komorebi_03（⭐⭐⭐⭐⭐）
**关键亮点**  
- 清晰的邻接表建图逻辑，通过坐标映射唯一节点编号。
- 使用`vis[]`数组标记当前DFS路径，精准检测环。
- 完整处理所有初始"D"节点的最长路径计算。

**核心代码片段**  
```cpp
void DFS(int u) {
    if(dis[u]) return;
    vis[u] = true; // 标记当前路径
    dis[u] = 1;
    for (int i=head[u]; ~i; i=e[i].nxt) {
        int v = e[i].v;
        if (vis[v]) { // 发现环路
            flag = true;
            vis[u] = false;
            return;
        }
        DFS(v);
        dis[u] = max(dis[u], dis[v]+1);
    }
    vis[u] = false; // 回溯清除标记
}
```

#### 2. 作者：Binary_Lee（⭐⭐⭐⭐）
**关键亮点**  
- 直接通过坐标DFS，避免显式建图，节省内存。
- 动态更新最大步数，代码简洁高效。
- 利用`on[][]`数组区分全局访问和当前路径访问。

**调试心得**  
> "发现二维坐标DFS中，忘记回溯`on[x][y]`会导致误判环，通过增加`on`数组解决。"

**核心代码片段**  
```cpp
void dfs(int x, int y) {
    if (vis[x][y]) return;
    vis[x][y] = on[x][y] = 1;
    for (int k=0; k<4; k++) {
        int nx=x+dx[k], ny=y+dy[k];
        if (非表格范围 || 非下一字母) continue;
        if (on[nx][ny]) { // 当前路径成环
            cout << "Poor Inna!";
            exit(0);
        }
        dfs(nx, ny);
        dis[x][y] = max(dis[x][y], dis[nx][ny]+1);
    }
    on[x][y] = 0; // 回溯
}
```

#### 3. 作者：_Sonnet（⭐⭐⭐⭐）
**关键亮点**  
- 动态规划思路，`f[i][j]`表示从(i,j)出发的最长路径。
- 直接利用方向数组遍历，减少建图开销。
- 简洁的递归终止条件与状态转移。

**核心代码片段**  
```cpp
int dfs(int x, int y) {
    if (f[x][y]) return f[x][y];
    vis[x][y] = 1;
    int max_step = 0;
    for (int k=0; k<4; k++) {
        int nx=x+dx[k], ny=y+dy[k];
        if (非表格范围 || 非下一字母) continue;
        if (vis[nx][ny]) exit(0); // 存在环
        max_step = max(max_step, dfs(nx, ny));
    }
    vis[x][y] = 0;
    return f[x][y] = max_step + 1;
}
```

---

### 相似题目推荐
1. **P1137 旅行计划** - 拓扑排序求最长路径  
2. **P3385 【模板】负环** - DFS/BFS判环  
3. **P2746 [USACO5.3] 校园网** - 强连通分量与DAG最长路

---
处理用时：57.01秒