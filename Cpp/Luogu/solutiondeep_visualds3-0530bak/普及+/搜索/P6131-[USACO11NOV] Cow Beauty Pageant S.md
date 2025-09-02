# 题目信息

# [USACO11NOV] Cow Beauty Pageant S

## 题目描述

听说最近流行表皮有三个斑点的奶牛，Farmer John 迅速购买了不少这样的奶牛。但流行趋势也在改变，最近改为流行只有一个斑点的奶牛了。

FJ 决定在他的奶牛上涂色，从而把三个斑点合并成一个。牛皮由一个 $N \times M$ 的矩阵来表示，像这样：

```plain
................
..XXXX....XXX...
...XXXX....XX...
.XXXX......XXX..
........XXXXX...
..XXX....XXX....
```

每个 `X` 表示斑点的一部分。如果两个 `X` 在竖直或水平方向上相邻，则它们属于同一个斑点（对角线相邻不算）。因此上面表示的是一头具有三个斑点的奶牛。

FJ 可以通过将一些 `.` 涂成 `X` 来改变牛身上的图案。他希望使用尽可能少的涂料将三个斑点合并为一个斑点。对于上图，下面是一种消耗涂料最少的方案（只涂了 4 个格子，新涂的格将用 `*` 表示）：

```plain
................
..XXXX....XXX...
...XXXX*...XX...
.XXXX..**..XXX..
...*....XXXXX...
..XXX....XXX....
```

现在请你帮 FJ 算出将三个斑点合并为一个斑点最少需要涂多少格子。

## 样例 #1

### 输入

```
6 16
................
..XXXX....XXX...
...XXXX....XX...
.XXXX......XXX..
........XXXXX...
..XXX....XXX....```

### 输出

```
4```

# AI分析结果



# 【算法分类】
BFS

# 【题解思路与难点分析】

### 核心思路
所有题解均采用两阶段处理：
1. **连通块标记**：使用DFS/BFS识别三个斑点并编号
2. **连接策略**：分两种情况计算最优解：
   - 类型1：两两斑点直接连接（曼哈顿距离或BFS计算最短路径）
   - 类型2：通过中间点连接三个斑点（枚举所有空点计算综合距离）

### 关键难点对比
| 方法                | 连通块标记 | 距离计算方式         | 时间复杂度 | 优化点                      |
|---------------------|------------|----------------------|------------|----------------------------|
| 曼哈顿距离（qzhwlzy） | BFS        | 曼哈顿距离（O(n²m²)） | O(n²m²)   | 预处理斑点间最小距离        |
| BFS分层（wssdl）     | BFS        | BFS分层扩展（O(nm)）  | O(nm)     | 精确计算斑点到各点的真实距离 |
| 最小生成树（Exber）   | BFS        | Kruskal算法          | O(ElogE)  | 转化为图论问题              |

### 最优思路提炼
1. **双策略并行**：同时计算类型1和类型2的解，取最小值
2. **距离预处理**：
   - 类型1：预处理两两斑点间的最小曼哈顿距离（需-1）
   - 类型2：预处理每个空点到三个斑点的最小曼哈顿距离（需-1）
3. **公式推导**：
   - 最终解 = min(类型1解, 类型2解)
   - 类型1解 = min(dis12+dis13, dis12+dis23, dis13+dis23) - 2
   - 类型2解 = min(Σ(dis1[i][j]+dis2[i][j]+dis3[i][j]) - 2)

# 【题解评分（≥4星）】

1. **qzhwlzy（4.5★）**
   - 亮点：双策略思路清晰，曼哈顿距离实现简洁
   - 缺点：未优化曼哈顿距离计算（O(n⁴)）
   - 代码段：
     ```cpp
     int trypoint(int i,int j){ // 类型2计算
         int xx[4] = {999999,999999,999999,999999};
         for(int p=1;p<=n;p++) 
             for(int q=1;q<=m;q++)
                 if(a[p][q] != 0)
                     xx[a[p][q]] = min(xx[a[p][q]], abs(i-p)+abs(j-q)-1);
         return xx[1]+xx[2]+xx[3]+1;
     }
     ```

2. **wssdl（5★）**
   - 亮点：BFS精确计算真实距离，分层扩展保证最优性
   - 代码段：
     ```cpp
     int bfs(int x,int y, int target){ // BFS分层核心
         queue<Node> q;
         q.push({x,y,0});
         while(!q.empty()){
             Node cur = q.front(); q.pop();
             if(a[cur.x][cur.y] == target) 
                 return cur.step;
             for(int i=0;i<4;i++){
                 int nx = cur.x+dx[i], ny = cur.y+dy[i];
                 if(valid(nx,ny) && !vis[nx][ny]){
                     vis[nx][ny] = true;
                     q.push({nx, ny, cur.step+1});
                 }
             }
         }
         return INF;
     }
     ```

3. **Exber（4★）**
   - 亮点：最小生成树创新思路
   - 代码段：
     ```cpp
     // 构建边集
     for(int i=1;i<=3;i++)
         for(int j=i+1;j<=3;j++)
             edges.push_back({i, j, min_dis(i,j)});
     sort(edges.begin(), edges.end());
     // Kruskal算法
     int kruskal(){
         int res = 0;
         for(auto &e : edges){
             if(find(e.u) != find(e.v)){
                 res += e.w;
                 unite(e.u, e.v);
             }
         }
         return res - 2; // 调整重复计算
     }
     ```

# 【可视化设计】

### 动画方案
1. **连通块标记阶段**
   - 使用不同颜色（红/绿/蓝）扩散标记三个斑点
   - 音效：扩散时播放8-bit水滴声

2. **距离计算阶段**
   - 类型1：斑点间显示黄色连线，实时显示曼哈顿距离数值
   - 类型2：光标扫描每个空点，显示三色距离指示条

3. **最优解展示**
   - 最终路径以闪烁金色显示，播放胜利音效
   - 控制面板：暂停/步进/切换算法

### 复古像素风格实现
```javascript
// Canvas绘制示例
function drawPixelGrid(ctx) {
    for(let i=0; i<rows; i++){
        for(let j=0; j<cols; j++){
            ctx.fillStyle = getColor(grid[i][j]); // 根据状态返回颜色
            ctx.fillRect(j*16, i*16, 15, 15); // 16x16像素块
        }
    }
}

// 音效系统
const sfx = {
    expand: new Audio('data:audio/wav;base64,UklGRl9...'), // 扩展音效
    connect: new Audio('data:audio/wav;base64,UklGRk9...')  // 连接音效
};
```

# 【同类型题目】
1. P2124 奶牛美容（双倍经验）
2. P6135 网络设计（多连通块连接）
3. P1162 填涂颜色（连通块标记与处理）

# 【核心代码实现】
```cpp
// BFS分层计算各点到斑点距离
vector<vector<int>> calcDist(int spot_id) {
    queue<pair<int,int>> q;
    vector<vector<int>> dist(n, vector<int>(m, INF));
    // 初始化斑点起点
    for(auto &p : spots[spot_id]) {
        q.push(p);
        dist[p.first][p.second] = 0;
    }
    // BFS扩展
    while(!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for(int d=0; d<4; d++){
            int nx = x + dx[d], ny = y + dy[d];
            if(nx>=0 && nx<n && ny>=0 && ny<m && dist[nx][ny]==INF){
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    return dist;
}

// 主算法
int solve() {
    auto d1 = calcDist(0), d2 = calcDist(1), d3 = calcDist(2);
    int type1 = min({d12+d13, d12+d23, d13+d23}) - 2;
    int type2 = INF;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            type2 = min(type2, d1[i][j]+d2[i][j]+d3[i][j]-2);
    return min(type1, type2);
}
```

# 【个人心得】
调试时需注意：
1. 曼哈顿距离需-1：因连接n个点需要n-1个线段
2. BFS队列初始化：需将所有斑点起点同时入队
3. 类型2空点判断：必须排除斑点本身点（bel[i][j]==0）

---
处理用时：92.32秒