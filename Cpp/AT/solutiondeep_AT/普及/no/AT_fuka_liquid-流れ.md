# 题目信息

# 流れ

## 题目描述

有一个$w\times h$的网格，网格上的每个格子都有对应的高度。

现在，往方格上倒水。

当某个方格内有水，而相邻的方格又比此方格低时，水就会向相邻的方格扩散。

两个方格在有同一条边时被认为是相邻的。

求一格水扩散的方格数量。

## 说明/提示

$1\leq w,h\leq 20$\
$0\leq p\leq w \times h$\
$0\leq Z_{i,j}\leq 100$\
$0\leq X_{i}<w$\
$0\leq Y_{i}<h$

# AI分析结果



# 中文题目重写

## 题目描述

有一个 $w \times h$ 的网格，每个格子有对应的高度。当向某个格子倒水时，若相邻格子高度低于当前格子，水会扩散。两个格子相邻定义为有公共边。求水扩散覆盖的格子总数。

## 输入说明
- 输入顺序为 $w$（列数）、$h$（行数）
- 每个注水点输入为 $X_i$（列坐标）、$Y_i$（行坐标）
- 多组数据输入，以 $w=h=p=0$ 结束

## 数据范围
- $1 \leq w,h \leq 20$
- $0 \leq Z_{i,j} \leq 100$

# 算法分类
搜索（洪水填充/BFS/DFS）

---

## 题解综合分析

### 核心思路对比
1. **DFS/BFS选择**：所有题解均采用搜索，DFS与BFS均可（20x20网格规模小）
2. **输入处理关键**：题目行列顺序易错（输入为列优先）
3. **多源扩散**：多个注水点需统一处理，多源BFS效率更优
4. **状态标记**：需记录已访问格子避免重复计算

### 最优解法提炼
1. **多源BFS**：将所有注水点同时入队，统一进行扩散
2. **坐标转换技巧**：输入坐标转换为行列索引时需交换顺序
3. **边界检查统一化**：通过方向数组简化扩散逻辑

---

## 精选题解（评分≥4星）

### 1. 见贤思齐_Seakies（5星）
**核心亮点**：
- 完整处理行列顺序转换
- 多源BFS实现清晰
- 包含详细注释和错误点分析
**核心代码**：
```cpp
queue<pii> q;
while (p--) {
    cin >> y >> x; // 输入列坐标y，行坐标x
    if (!vis[x][y]) q.push({x, y});
    while (!q.empty()) {
        auto [ux, uy] = q.front(); q.pop();
        if (vis[ux][uy]) continue;
        vis[ux][uy] = 1; ans++;
        for (int i = 0; i < 4; i++) {
            int tx = ux + dx[i], ty = uy + dy[i];
            if (tx >=0 && tx < w && ty >=0 && ty < h 
                && z[tx][ty] < z[ux][uy]) {
                q.push({tx, ty});
            }
        }
    }
}
```

### 2. HKHbest（4星）
**关键技巧**：
- 使用结构体封装坐标
- 边界检查函数化提升可读性
**实现亮点**：
```cpp
bool fw(int i,int j) { // 边界检查
    return i>=1 && i<=n && j>=1 && j<=m;
}
void bfs() {
    while(!q.empty()) {
        dian cur = q.front(); q.pop();
        for(int i=0;i<4;i++) {
            int tx = cur.x+dx[i], ty = cur.y+dy[i];
            if(fw(tx,ty) && !vis[tx][ty] && z[cur.x][cur.y]>z[tx][ty]) {
                vis[tx][ty] = true;
                q.push({tx, ty});
                ans++;
            }
        }
    }
}
```

### 3. COsm0s（4星）
**优化点**：
- 使用DFS实现洪水填充
- 显式标记初始注水点
**代码特色**：
```cpp
void DFS(int x,int y){
    for(int i=0;i<4;i++){
        int nx = x+dir[i][0], ny = y+dir[i][1];
        if(nx>=1 && nx<=w && ny>=1 && ny<=h 
           && !vis[nx][ny] && z[x][y]>z[nx][ny]){
            vis[nx][ny] = true;
            DFS(nx,ny);
        }
    }
}
```

---

## 关键技巧总结
1. **输入转换模板**：建立行列转换条件反射，如 `x = input_col_val, y = input_row_val`
2. **多源处理**：将多个起点统一入队，避免多次调用搜索函数
3. **方向数组应用**：`dx[]={-1,1,0,0}, dy[]={0,0,-1,1}` 简化邻接点遍历
4. **状态复用**：使用二维数组记录访问状态，同时表示水域覆盖情况

---

## 同类题目推荐
1. [P1434 滑雪](https://www.luogu.com.cn/problem/P1434) - 记忆化搜索与高度扩散
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443) - BFS步数扩散
3. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162) - 多源洪水填充应用

---

## 调试经验摘录
- **坐标转换教训**："题目输入先列后行，样例查不出这个错" —— HKHbest
- **标记时机**："将ans++放在标记后，避免重复统计" —— 见贤思齐_Seakies
- **初始状态**："倒水点本身也要计数" —— GODking

---
处理用时：63.61秒