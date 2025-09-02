# 题目信息

# [USACO10OCT] Lake Counting S

## 题目描述

Due to recent rains, water has pooled in various places in Farmer John's field, which is represented by a rectangle of N x M (1 <= N <= 100; 1 <= M <= 100) squares. Each square contains either water ('W') or dry land ('.'). Farmer John would like to figure out how many ponds have formed in his field. A pond is a connected set of squares with water in them, where a square is considered adjacent to all eight of its neighbors. Given a diagram of Farmer John's field, determine how many ponds he has.






## 说明/提示

OUTPUT DETAILS: There are three ponds: one in the upper left, one in the lower left, and one along the right side.


## 样例 #1

### 输入

```
10 12
W........WW.
.WWW.....WWW
....WW...WW.
.........WW.
.........W..
..W......W..
.W.W.....WW.
W.W.W.....W.
.W.W......W.
..W.......W.
```

### 输出

```
3
```

# AI分析结果



## 算法分类
**图遍历算法（DFS/BFS）**

---

## 题解分析与结论

### 核心思路与解决难点
所有题解均围绕**连通块计数**展开，核心差异在于遍历方式与标记策略：
1. **DFS**：递归/栈实现，每次向8个方向探索，标记已访问节点（改为'.'或单独标记数组）
2. **BFS**：队列实现，逐层扩展，避免递归栈溢出风险
3. **并查集**：按扫描顺序合并相邻水块，最终统计根节点数量
4. **Tarjan强连通分量**：二维扩展的Tarjan算法（非常规解法，性能较差）

**关键难点**：
- **边界处理**：确保坐标不越界
- **标记优化**：原地修改字符数组（O(1)空间） vs 独立标记数组（更清晰但O(nm)空间）
- **方向遍历**：8方向循环写法（dx/dy数组） vs 8个独立判断

---

## 高星题解推荐 (≥4★)

### 1. Fractures的DFS/BFS对比（5★）
**亮点**：
- 清晰对比两种算法优劣，提供完整可运行代码
- 注释详细，变量命名规范（dx/dy方向数组）
- 包含输入优化（字符串读取）与边界检查
**核心代码片段**：
```cpp
// DFS核心逻辑
void dfs(int x, int y) {
    a[x][y] = '.'; // 原地标记
    for (int i =-1; i<=1; i++)
        for (int j=-1; j<=1; j++)
            if (valid(x+i, y+j) && a[x+i][y+j] == 'W')
                dfs(x+i, y+j);
}
```

### 2. 子谦的并查集解法（4★）
**亮点**：
- 非搜索思路，提供独特解题视角
- 仅需扫描四个方向即可完成合并（避免重复计数）
**核心思路**：
```cpp
void hebing(int x, int y) {
    int fx=fa(x), fy=fa(y);
    if (fx != fy) f[fx] = fy; // 合并祖先
}
// 扫描时检查右、下、左下、右下四个方向
```

### 3. liujiayuan的BFS优化（4★）
**亮点**：
- 使用独立标记数组，代码可读性强
- 结构体存储坐标，队列操作规范
**核心代码**：
```cpp
queue<node> q;
q.push({i,j});
while(!q.empty()) {
    node now = q.front(); q.pop();
    for(int k=0; k<8; k++) {
        int nx = now.x + dx[k], ny = now.y + dy[k];
        if (valid(nx,ny) && !vis[nx][ny] && map[nx][ny]=='W') {
            vis[nx][ny] = true;
            q.push({nx,ny});
        }
    }
}
```

---

## 最优技巧提炼
1. **方向数组遍历法**  
   使用dx[8]、dy[8]数组统一管理8个方向，替代8个独立判断：
   ```cpp
   int dx[] = {-1,-1,0,1,1,1,0,-1};
   int dy[] = {0,1,1,1,0,-1,-1,-1};
   for(int i=0; i<8; i++){
       int nx = x + dx[i], ny = y + dy[i];
       // ...判断逻辑
   }
   ```
2. **原地标记优化**  
   直接修改输入数组的'W'为'.'，省去独立标记数组：
   ```cpp
   if (grid[x][y] == 'W') {
       grid[x][y] = '.'; // 标记为已访问
       dfs(x, y);        // 继续搜索
   }
   ```
3. **输入优化**  
   按行读取字符串避免逐字符处理换行符：
   ```cpp
   for(int i=0; i<n; i++) 
       scanf("%s", grid[i]); // 自动跳过换行符
   ```

---

## 类似题目推荐
1. **P1451 求细胞数量**  
   四方向连通块计数，输入为数字矩阵
2. **P1162 填涂颜色**  
   BFS标记闭合区域，需处理边界
3. **P1141 01迷宫**  
   连通块预处理+查询，大数据量优化

---

## 算法可视化设计

### 核心动画方案（DFS示例）
1. **初始化**：渲染N×M像素网格，'W'显示为蓝色方块，'.'为灰色
2. **搜索过程**：
   - 当前访问节点显示为红色闪烁方块
   - 已访问节点渐变为灰色
   - 每次递归/入队时绘制方向箭头（8方向）
3. **交互功能**：
   - **速度滑块**：调整搜索动画速度（100ms~2s/步）
   - **模式切换**：DFS/BFS对比演示
   - **高亮开关**：显示/隐藏访问路径

### 复古像素风格实现
```javascript
// Canvas绘制示例
function drawPixel(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x*10, y*10, 8, 8); // 10x10像素含边框
}
// 音效触发
function playSound(effect) {
    const sfx = {
        visit: [140,0.2,,,0.3], // 8-bit音效参数
        mark: [220,0.1,,,0.2]
    };
    synth.triggerAttackRelease(sfx[effect][0], sfx[effect][1]);
}
```

---

## 核心代码实现（DFS）
```cpp
#include <iostream>
using namespace std;

int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,1,1,1,0,-1,-1,-1};
char grid[105][105];
int n, m, cnt = 0;

void dfs(int x, int y) {
    grid[x][y] = '.';
    for(int i=0; i<8; i++) {
        int nx = x+dx[i], ny = y+dy[i];
        if(nx>=0 && nx<n && ny>=0 && ny<m && grid[nx][ny]=='W')
            dfs(nx, ny);
    }
}

int main() {
    cin >> n >> m;
    for(int i=0; i<n; i++) 
        cin >> grid[i];
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(grid[i][j] == 'W') {
                dfs(i, j);
                cnt++;
            }
    
    cout << cnt;
    return 0;
}
```

---
处理用时：83.39秒