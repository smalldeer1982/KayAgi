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



### 题目翻译
# Inna 和 Dima

## 题目描述

Inna 和 Dima 在商店买了一个大小为 $n×m$ 的桌子。每个单元格包含一个字母："D"、"I"、"M"或"A"。

Inna 想通过移动在桌子中尽可能多次地遍历 Dima 的名字。具体规则如下：

1. 初始时选择包含字母"D"的单元格；
2. 然后可以移动到相邻的"I"，接着移动到相邻的"M"，再移动到相邻的"A"，完成一次遍历；
3. 后续移动必须从"A"回到"D"继续循环。

需要判断最大遍历次数：无限次（输出"Poor Inna!"）、无法完成一次（输出"Poor Dima!"）或给出具体数值。

---

### 题解综合分析

#### 核心算法思路
1. **DFS 找最长路径**：从每个 D 出发，按 D→I→M→A→D 顺序递归
2. **环检测**：维护访问路径数组，发现重复访问即存在环
3. **记忆化优化**：存储每个节点的最大步长避免重复计算
4. **隐式建图**：直接通过方向数组判断邻接关系，不显式建立邻接表

#### 最优题解亮点
1. **隐式路径处理**（Binary_Lee 题解）
   - 直接通过坐标计算相邻节点，节省内存
   - 方向数组遍历替代显式建图
   ```cpp
   int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
   for (int k=0; k<4; k++) {
       int x = i+dx[k], y = j+dy[k];
       if (cango(i,j,x,y)) // 判断字母顺序
   }
   ```
2. **路径状态双标记**（封禁用户题解）
   - `vis[][]` 记录永久访问状态
   - `on[][]` 记录当前 DFS 路径状态
   ```cpp
   void dfs(int x,int y){
       if(vis[x][y]) return;
       vis[x][y] = on[x][y] = 1;
       // ...遍历邻接点
       on[x][y] = 0;
   }
   ```

---

### 精选题解（评分≥4★）

#### 1. 作者：Binary_Lee（4.5★）
**关键亮点**：
- 使用坐标映射函数替代显式编号
- 简洁的方向遍历实现隐式建图
- 路径步长与环检测逻辑清晰

**核心代码**：
```cpp
void dfs(int sx,int sy) {
    if(dis[sx][sy]) return;
    vis[sx][sy] = 1;
    dis[sx][sy] = 1;
    for(int k=0; k<4; k++) {
        int x = sx+dx[k], y = sy+dy[k];
        if (字母顺序合法) {
            if(vis[x][y]) { /* 检测环 */ }
            dfs(x,y);
            dis[sx][sy] = max(dis[sx][sy], dis[x][y]+1);
        }
    }
    vis[sx][sy] = 0;
}
```

#### 2. 作者：NaN_HQJ2007_NaN（4★）
**关键亮点**：
- 极简代码风格（80行完整实现）
- 动态字母顺序判断
- 快速终止检测逻辑

**调试心得**：
> "判环时一定要仔细检查，我因为判环导致死循环，空间炸了，调了半小时愣是没调出来"

---

### 相似题目推荐
1. **P1137 旅游计划** - 拓扑排序求最长路径
2. **P2419 合唱队形** - 网格中的动态规划路径
3. **CF510C Fox And Names** - 字母顺序拓扑排序

---
处理用时：62.13秒