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



### 综合分析结论
本题核心为八连通块计数问题，所有题解均围绕DFS/BFS/并查集三种思路展开。DFS实现最为简洁高效，BFS需注意队列优化，而并查集方法存在合并方向覆盖不全的隐患。核心优化点在于遍历时直接修改原数组避免重复访问，方向数组简化邻接点遍历。

---

### 优质题解推荐（评分≥4星）

#### 1. Fractures（DFS+BFS双解） ★★★★☆
**核心亮点**：
- 同时给出DFS/BFS双解思路，对比两种算法优劣势
- 方向遍历逻辑清晰（双重循环生成8方向偏移量）
- 代码结构规范，含详细注释说明
- 提出STL队列的性能优化思路（手写队列）

**关键代码（DFS核心）**：
```cpp
void dfs(int x,int y){
    a[x][y]='.';
    for(int i=-1;i<=1;i++){ // 双重循环生成8方向
        for(int j=-1;j<=1;j++){
            int dx=x+i, dy=y+j;
            if(dx>=0 && dx<n && dy>=0 && dy<m && a[dx][dy]=='W') 
                dfs(dx,dy);
        }
    }
}
```

#### 2. 高铁1号（标准DFS） ★★★★☆
**核心亮点**：
- 预定义方向数组提升可读性
- 边界判断逻辑简洁（坐标合法性+字符判断）
- 代码风格规范，适合初学者学习

**关键代码**：
```cpp
int fxx[9]={0,-1,-1,-1,0,0,1,1,1}; // 预定义8方向偏移量
int fxy[9]={0,-1,0,1,-1,1,-1,0,1};
void dfs(int x,int y){
    a[x][y] = '.'; 
    for(int i=1;i<=8;i++){
        int r=x+fxx[i], c=y+fxy[i];
        if(r>=1 && r<=n && c>=1 && c<=m && a[r][c]=='W')
            dfs(r,c);
    }
}
```

#### 3. liujiayuan（BFS优化） ★★★★
**核心亮点**：
- 结构体队列实现规范BFS
- 独立标记数组避免修改原数据
- 方向数组显式定义提升可维护性

**核心技巧**：
```cpp
int dirx[8]={0,1,0,-1,1,1,-1,-1}; // 显式定义8方向
int diry[8]={1,0,-1,0,1,-1,1,-1};
queue<Node> q;
q.push({x,y});
vis[x][y] = true;
while(!q.empty()){
    Node now = q.front(); q.pop();
    for(int i=0;i<8;i++){
        int nx=now.x+dirx[i], ny=now.y+diry[i];
        if(check(nx,ny)) {
            q.push({nx,ny});
            vis[nx][ny] = true;
        }
    }
}
```

---

### 关键优化思路总结
1. **空间优化**：直接修改原数组代替vis数组（DFS常用）
2. **方向遍历**：预定义偏移量数组简化代码
3. **输入处理**：按行读取字符串避免逐字符处理
4. **连通判断**：八个方向需包含斜对角（区别于四连通问题）

---

### 类似题目推荐
1. **P1451 求细胞数量**（四连通基础）
2. **P1506 拯救oibh总部**（连通块+边界条件）
3. **P1162 填涂颜色**（复杂连通区域处理）

---

### 调试经验摘录
1. **输入陷阱**：多位用户强调`scanf`读取字符时需注意换行符（如用`scanf("%s")`整行读取）
2. **越界处理**：循环前必须检查坐标是否在合法范围内
3. **方向遗漏**：有题解通过打印中间状态发现方向覆盖不全
4. **STL性能**：BFS使用STL队列时，大数据可能TLE，需手写队列优化

---
处理用时：56.06秒