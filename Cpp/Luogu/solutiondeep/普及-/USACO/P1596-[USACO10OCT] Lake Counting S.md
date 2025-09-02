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



### 综合分析与结论
本题核心是八连通块的计数问题，主流解法为DFS/BFS遍历标记，亦有少量并查集解法。题解质量差异主要体现在代码规范度、边界处理、优化技巧等方面。关键技巧在于方向数组的灵活运用、访问标记的优化处理，以及输入方法的正确性保证。

---

### 高星题解推荐（评分≥4星）

#### 1. Fractures（DFS+BFS对比） ⭐⭐⭐⭐⭐
**核心亮点**：  
- 对比DFS/BFS优劣，代码规范易读  
- 标记与访问逻辑清晰（原地修改数组）  
- 包含STL队列优化讨论  
**关键代码**：
```cpp
// DFS核心
void dfs(int x,int y){
    a[x][y]='.';
    for(int i=-1;i<=1;i++){  // 三循环替代方向数组
        for(int j=-1;j<=1;j++){
            int dx=x+i, dy=y+j;
            if(dx>=0 && dx<n && dy>=0 && dy<m && a[dx][dy]=='W')
                dfs(dx,dy);
        }
    }
}
```

#### 2. 高铁1号（方向数组DFS） ⭐⭐⭐⭐  
**核心亮点**：  
- 预定义方向数组提升可读性  
- 显式坐标偏移更易维护  
**关键代码**：
```cpp
int fxx[9]={0,-1,-1,-1,0,0,1,1,1}; // 八方向预定义
int fxy[9]={0,-1,0,1,-1,1,-1,0,1};
void dfs(int x,int y){
    a[x][y]='.';
    for(int i=1;i<=8;i++){  // 显式枚举八个方向
        int r=x+fxx[i], c=y+fxy[i];
        if(r>=1 && r<=n && c>=1 && c<=m && a[r][c]=='W')
            dfs(r,c);
    }
}
```

#### 3. liujiayuan（BFS手写队列） ⭐⭐⭐⭐  
**核心亮点**：  
- 手写队列避免STL性能问题  
- 结构体存储坐标逻辑清晰  
**关键代码**：
```cpp
queue<node> q;
void bfs(int a,int b){
    q.push({a,b});
    while(!q.empty()){
        node now = q.front();
        q.pop();
        for(int i=0;i<8;i++){
            int nx=now.x+dx[i], ny=now.y+dy[i];
            if(nx>=0 && nx<n && ny>=0 && ny<m && !vis[nx][ny]){
                vis[nx][ny] = true;
                q.push({nx,ny});
            }
        }
    }
}
```

---

### 关键技巧总结
1. **方向数组优化**：使用预定义的dx/dy数组简化八个方向的遍历  
2. **原地标记法**：直接修改输入数组代替额外vis数组，节省内存  
3. **输入处理技巧**：  
   ```cpp
   scanf("%s",a[i]); // 整行读取避免换行符问题
   ```  
4. **连通性判断**：遇到'W'立即展开搜索并计数，保证不重复统计  

---

### 同类题目推荐
1. [P1451 求细胞数量](https://www.luogu.com.cn/problem/P1451)（四连通基础）  
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)（连通区域边界处理）  
3. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)（连通块预处理+查询）  

---

### 题解心得摘录
1. **输入陷阱**：  
   > "注意用`scanf("%s")`整行读取避免换行问题，60分教训" —— xukuan  
   **总结**：字符串输入需处理行末换行符  

2. **调试技巧**：  
   > "WA后发现方向数组下标错误，一个符号导致40分" —— LevenKoko  
   **总结**：方向数组应严格测试八个方向的正确性  

3. **算法选择**：  
   > "BFS用空间换时间，但STL队列可能TLE，手写队列优化后AC" —— Fractures  
   **总结**：大规模数据时需考虑容器性能

---
处理用时：54.55秒