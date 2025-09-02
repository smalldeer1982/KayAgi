# 题目信息

# UCV2013H - Slick

## 题目描述

一片大小为 $n\times m$ 的海面发生了石油泄漏，石油表示为 $1$，海水表示为 $0$。

求石油组成的连通块总数，以及每种面积连通块的个数。

**本题多测**

## 样例 #1

### 输入

```
10 10
1 1 1 1 1 1 1 1 1 1
1 1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 1 1 1
1 1 0 0 1 0 0 1 1 1
1 0 1 0 0 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0```

### 输出

```
7
1 2
2 1
6 1
10 2
20 1```

# AI分析结果



## 算法分类
图遍历（BFS/DFS）

---

## 综合分析与结论
### 核心思路
所有题解均采用以下流程：  
1. 遍历矩阵，遇到未访问的石油点（1）时启动 BFS/DFS  
2.在搜索过程中标记已访问节点（直接修改原数组或使用辅助数组）  
3. 统计连通块面积并存入桶数组（下标为面积值）  
4. 最后输出桶数组中非零元素  

### 关键难点与解决方案
1. **多测初始化**：每组数据前必须重置标记数组和统计数组（如 Lion_Li 题解因未初始化导致 WA）  
2. **坐标处理**：注意矩阵行列的存储顺序（部分题解将输入行列倒置存入数组）  
3. **面积统计优化**：使用桶数组（ans[90010]）替代排序，实现 O(1) 时间统计  

### 可视化设计
1. **像素网格动画**：  
   - 初始网格：绿色像素（1）、蓝色像素（0）  
   - BFS扩展：当前处理节点变为红色，队列中的节点显示为橙色边框  
   - 最终效果：每个连通块用不同渐变色填充  
2. **音效设计**：  
   - "滴"声：发现新连通块  
   - "咔嗒"声：每次队列弹出操作  
   - 背景音乐：8-bit 海洋环境音效  
3. **自动演示模式**：  
   - 按连通块发现顺序分步演示，可调节 0.5x/1x/2x 速度  
   - 右侧面板实时显示当前面积统计表  

---

## 题解评分（≥4星）
### [lzxhdxx] ⭐⭐⭐⭐⭐  
- 亮点：清晰的 BFS 实现 + 原数组标记法（节省内存）  
- 代码示例：  
```cpp
int bfs(int x, int y) {
    queue<pair<int, int>> Q;
    Q.push({x, y});
    a[x][y] = 0; // 直接在原数组标记
    int area = 1;
    while (!Q.empty()) {
        // ...四方向扩展逻辑
    }
    return area;
}
```

### [Lion_Li] ⭐⭐⭐⭐  
- 亮点：DFS 递归实现 + 错误处理提醒  
- 关键心得：  
  > "每一遍处理完要初始化一次，不然一定会 WA"  

### [zhenglier] ⭐⭐⭐⭐  
- 亮点：独立 visited 数组 + 规范的方向数组定义  
- 优化点：  
  ```cpp
  const int dx[] = {0,1,0,-1,0}; // 五个元素对齐方向
  const int dy[] = {0,0,1,0,-1};
  ```

---

## 最优技巧提炼
1. **双标记策略**：通过修改原矩阵值代替额外存储，节省 300x300 的数组空间  
2. **桶式统计**：利用面积值直接作为数组下标，避免排序操作  
3. **方向数组模板**：  
   ```cpp
   // 四方向（上右下左）
   int dx[] = {-1,0,1,0}; 
   int dy[] = {0,1,0,-1};
   ```

---

## 相似题目推荐
1. **P1162 填涂颜色**（连通块边界处理）  
2. **P1506 拯救oibh总部**（反向连通区域标记）  
3. **P2298 寻找数对**（双向 BFS 优化）  

---

## 核心代码实现
```cpp
#include <queue>
using namespace std;

int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};
int n, m, grid[300][300], cnt[90001];

void bfs(int x, int y) {
    queue<pair<int,int>> q;
    q.push({x,y});
    grid[x][y] = 0;
    int area = 1;
    
    while (!q.empty()) {
        auto [cx, cy] = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i], ny = cy + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny]) {
                grid[nx][ny] = 0;
                q.push({nx, ny});
                area++;
            }
        }
    }
    cnt[area]++;
}

int main() {
    while (cin >> n >> m && n && m) {
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> grid[i][j];
                
        int total = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i][j])
                    bfs(i,j), total++;
        
        cout << total << endl;
        for (int i = 1; i <= 90000; ++i)
            if (cnt[i]) cout << i << " " << cnt[i] << endl;
    }
}
```

---

## 可视化方案
### 动画逻辑
1. **初始化阶段**：  
   - Canvas 绘制 n×m 网格，1→绿色方块，0→蓝色方块  
2. **BFS 过程**：  
   - 当前处理节点变为红色，已访问节点渐变至紫色  
   - 队列节点显示橙色边框，扩展方向用箭头指示  
3. **统计显示**：  
   - 右侧面板动态更新桶数组，高亮当前处理的面积值  

### 复古特效
```javascript
// 示例：8-bit 音效生成
function playBFSound() {
    const ctx = new AudioContext();
    const osc = ctx.createOscillator();
    osc.frequency.setValueAtTime(800 + Math.random()*200, ctx.currentTime);
    osc.connect(ctx.destination);
    osc.start(); osc.stop(ctx.currentTime + 0.1);
}
```

### 交互设计
- **WASD 控制**：手动移动起始点  
- **F1 键**：切换自动演示/手动模式  
- **F2 键**：开启/关闭 8-bit 背景音乐  

---

**可视化演示地址**（虚拟）：  
https://algorithm-visualizer.org/bfs-slick

---
处理用时：98.15秒