# 题目信息

# The Labyrinth

## 题目描述

You are given a rectangular field of $ n×m $ cells. Each cell is either empty or impassable (contains an obstacle). Empty cells are marked with '.', impassable cells are marked with '\*'. Let's call two empty cells adjacent if they share a side.

Let's call a connected component any non-extendible set of cells such that any two of them are connected by the path of adjacent cells. It is a typical well-known definition of a connected component.

For each impassable cell $ (x,y) $ imagine that it is an empty cell (all other cells remain unchanged) and find the size (the number of cells) of the connected component which contains $ (x,y) $ . You should do it for each impassable cell independently.

The answer should be printed as a matrix with $ n $ rows and $ m $ columns. The $ j $ -th symbol of the $ i $ -th row should be "." if the cell is empty at the start. Otherwise the $ j $ -th symbol of the $ i $ -th row should contain the only digit —- the answer modulo $ 10 $ . The matrix should be printed without any spaces.

To make your output faster it is recommended to build the output as an array of $ n $ strings having length $ m $ and print it as a sequence of lines. It will be much faster than writing character-by-character.

As input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 说明/提示

In first example, if we imagine that the central cell is empty then it will be included to component of size $ 5 $ (cross). If any of the corner cell will be empty then it will be included to component of size $ 3 $ (corner).

## 样例 #1

### 输入

```
3 3
*.*
.*.
*.*
```

### 输出

```
3.3
.5.
3.3
```

## 样例 #2

### 输入

```
4 5
**..*
..***
.*.*.
*.*.*
```

### 输出

```
46..3
..732
.6.4.
5.4.3
```

# AI分析结果



【中文重写题目】

# 迷宫

## 题目描述

给定一个 $n×m$ 的矩形网格，每个单元格是空地（用 '.' 表示）或障碍（用 '*' 表示）。定义两个相邻的空单元格为共享边的单元格。连通分量是指无法再扩展的、所有单元格通过相邻路径连接的集合。

对于每个障碍单元格 $(x,y)$，假设将其变为空地，计算其所在的连通分量大小（单元格数量），结果对 $10$ 取模。最终输出一个矩阵，其中原有空地保留 '.'，障碍位置替换为计算结果。

## 输入输出

输入格式：  
- 第一行两个整数 $n,m$  
- 接下来 $n$ 行每行 $m$ 个字符表示网格  

输出格式：  
- $n$ 行每行 $m$ 个字符的结果矩阵  

## 样例

样例1输入：
```
3 3
*.*
.*.
*.*
```
样例1输出：
```
3.3
.5.
3.3
```

---

**算法分类**: 深度优先搜索(DFS)/广度优先搜索(BFS) + 连通分量预处理

---

### 综合题解分析

**核心思路**：  
1. **预处理连通块**：通过DFS/BFS标记每个连通块，记录每个块的编号和大小  
2. **障碍处理**：对每个障碍点，统计其四个方向不同连通块的总和（去重）  
3. **结果计算**：总和+1后取模  

**关键优化点**：  
- 预处理避免重复计算  
- 使用集合或标记数组去除重复连通块  
- 邻接方向处理技巧  

---

### 精选题解

#### 1. yaolibo 题解（⭐⭐⭐⭐⭐）  
**核心亮点**：  
- 清晰的DFS预处理逻辑  
- 使用方向数组实现简洁的邻接判断  
- 通过数组标记去重  

**关键代码**：  
```cpp
void dfs(int x, int y) {
    vis[x][y] = cnt;
    res++;
    for (int i = 0; i < 4; i++) {
        int nx = x + lx[i], ny = y + ly[i];
        if (边界合法且未访问) dfs(nx, ny);
    }
}
// 障碍处理部分
for (k = 0; k < 4; k++) {
    // 检查四个方向并去重
    if (新块的编号未出现过) sum += ans[块编号];
}
```

#### 2. 开始新的记忆 题解（⭐⭐⭐⭐）  
**核心亮点**：  
- 使用STL set简化去重逻辑  
- 代码结构清晰易读  

**关键实现**：  
```cpp
set<int> s;
for (四个方向) {
    if 是空地则插入集合
}
for (auto it : s) ans += 块大小;
```

#### 3. wind_whisper 题解（⭐⭐⭐⭐）  
**核心亮点**：  
- BFS预处理保证层级扩展  
- 集合去重与模运算结合  

**代码片段**：  
```cpp
void bfs(int x,int y,int f){
    // 标准BFS标记连通块
}
// 处理障碍时
set<int> s;
for (四个方向) s.insert(块编号);
int ans = 1 + 集合内总和;
```

---

### 最优思路总结

1. **连通块预处理**：通过DFS/BFS遍历所有空地，为每个连通块分配唯一编号并记录大小  
2. **四方向去重**：使用集合或临时标记数组避免重复累加同一连通块  
3. **高效结果计算**：直接引用预处理的块大小数据  

**代码实现技巧**：  
- 方向数组统一管理邻接坐标计算  
- 二维坐标与连通块编号的映射  
- 结果计算时采用 (sum + 1) % 10 的简洁写法  

---

### 拓展练习

1. **P1141 01迷宫** - 连通块预处理基础  
2. **P1331 海战** - 相邻块检测与形状判断  
3. **P1162 填涂颜色** - 边界扩展+BFS应用  

---

### 调试心得摘录

- **yaolibo**：注意处理方向数组的越界判断，否则会导致RE  
- **hxhhxhmz**：使用时间戳替代memset提升效率  
- **Insouciant21**：发现原代码在去重逻辑中存在边界条件错误，修正后AC

---
处理用时：71.35秒