# 题目信息

# Cutting Figure

## 题目描述

You've gotten an $ n×m $ sheet of squared paper. Some of its squares are painted. Let's mark the set of all painted squares as $ A $ . Set $ A $ is connected. Your task is to find the minimum number of squares that we can delete from set $ A $ to make it not connected.

A set of painted squares is called connected, if for every two squares $ a $ and $ b $ from this set there is a sequence of squares from the set, beginning in $ a $ and ending in $ b $ , such that in this sequence any square, except for the last one, shares a common side with the square that follows next in the sequence. An empty set and a set consisting of exactly one square are connected by definition.

## 说明/提示

In the first sample you can delete any two squares that do not share a side. After that the set of painted squares is not connected anymore.

The note to the second sample is shown on the figure below. To the left there is a picture of the initial set of squares. To the right there is a set with deleted squares. The deleted squares are marked with crosses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF193A/cc2de3ad5afd093ec1251f928cbdde2a451e56d2.png)

## 样例 #1

### 输入

```
5 4
####
#..#
#..#
#..#
####
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5
#####
#...#
#####
#...#
#####
```

### 输出

```
2
```

# AI分析结果



# Cutting Figure 切割图形

## 题目描述
给定一个 $n×m$ 的方格纸，部分方格被涂色。定义涂色方格的集合 $A$ 是连通的。要求找出使 $A$ 不再连通所需删除的最小方格数。

连通性定义：任意两个涂色方格间存在相邻路径（四连通）。空集和单一方格视为连通。

## 算法分类
深度优先搜索 DFS / 广度优先搜索 BFS

---

## 题解分析与结论

### 核心思路
1. **特判总点数**：当涂色格子数 < 3 时，无法分割，直接返回 -1
2. **单点割裂验证**：枚举每个涂色点，模拟删除后通过 DFS/BFS 检查剩余图是否保持连通
3. **结论上界**：若存在单点割裂则返回 1，否则答案必为 2

### 最优思路提炼
- **暴力枚举+连通性检查**：通过删除每个点并验证图的分裂情况
- **复杂度控制**：O(nm(n+m)) 的复杂度在 50x50 数据范围内可行
- **边界处理**：特别注意总点数小于3时的特判

---

## 精选题解

### 题解1：_StarBird_（⭐⭐⭐⭐⭐）
**亮点**：
- 详细论证答案上界为2的数学证明
- 使用DFS实现连通性检查，代码结构清晰
- 包含调试反例说明（如中心点割裂案例）

**核心代码**：
```cpp
bool check(int x,int y) {
    memset(vis, 0, sizeof(vis));
    vis[x][y] = true;
    bool flag = false;
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
            if(map[i][j] && !vis[i][j]) {
                if(flag) return true; // 发现第二连通块
                flag = true;
                dfs(i,j);
            }
    return false;
}
```

### 题解2：qusia_MC（⭐⭐⭐⭐）
**亮点**：
- 使用BFS进行连通性检查
- 采用队列实现，避免递归栈溢出风险
- 引入围棋角点分析的特殊情况处理

**代码片段**：
```cpp
bool ok(int x, int y) {
    memset(vis, 0, sizeof(vis));
    queue<pair<int,int>> q;
    // 查找首个未删除点启动BFS
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(a[i][j]=='#' && !(i==x && j==y)) {
                q.push({i,j});
                vis[i][j] = 1;
                goto bfs;
            }
bfs:
    while(!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for(int k=0; k<4; k++) {
            int nx = x+dx[k], ny = y+dy[k];
            if(nx>=1 && ny>=1 && nx<=n && ny<=m 
               && !vis[nx][ny] && a[nx][ny]=='#') {
                vis[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
    }
    // 验证未访问点存在性
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(a[i][j]=='#' && !vis[i][j]) 
                return true;
    return false;
}
```

### 题解3：AC_love（⭐⭐⭐）
**亮点**：
- 提出Tarjan点双连通分量优化思路
- 适用于更大数据规模的扩展思考
- 给出点双连通分量解法的实现方向

---

## 关键实现技巧
1. **快速连通性检查**：
   - 删除目标点后，随机选择一个剩余点进行DFS/BFS
   - 统计访问点数是否等于总点数-1
2. **空间优化**：
   - 使用原地标记（修改地图值）替代额外vis数组
3. **剪枝优化**：
   - 发现第一个分割成功立即返回，避免全枚举

---

## 拓展思考
- **图论扩展**：本题本质是寻找图的割点（若存在答案1则为割点）
- **高效算法**：可结合Tarjan算法求点双连通分量判断割点
- **三维扩展**：若问题扩展到三维空间，需使用三维连通分量分析

---

## 推荐练习题
1. P3388 【模板】割点 - 练习Tarjan算法求割点
2. P2860 [USACO06JAN] Redundant Paths G - 双连通分量应用
3. P3225 [HNOI2012] 矿场搭建 - 点双连通分量综合应用

---
处理用时：68.31秒