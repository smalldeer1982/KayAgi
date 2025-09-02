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
本题核心是求八方向连通的'W'块数量，属于经典连通块问题。主流解法为DFS/BFS（时间O(nm)），少量题解尝试并查集（需处理复杂合并逻辑）。关键优化点包括方向数组简化代码、原地标记替代额外空间、字符串读入处理换行符等。

---

### 高星题解推荐

#### 1. Fractures（DFS+BFS对比） ★★★★☆
**核心亮点**  
- 对比DFS/BFS优缺点，提供双解法代码  
- 强调DFS易写、BFS需手写队列优化  
- 关键代码段注释清晰，边界条件处理规范  
```cpp
// DFS核心代码
void dfs(int x,int y){
    a[x][y]='.'; // 原地标记避免重复访问
    for(int i=-1;i<=1;i++){ // 双循环生成8方向
        for(int j=-1;j<=1;j++){
            int dx=x+i, dy=y+j;
            if(dx>=0 && dx<n && dy>=0 && dy<m && a[dx][dy]=='W')
                dfs(dx, dy);
        }
    }
}
```

#### 2. 高铁1号（DFS标准模板） ★★★★
**核心亮点**  
- 预定义方向数组提升可读性  
- 严格边界检查，代码结构工整  
**个人心得**  
"注意数组下标从1开始，避免混淆行列值"  
```cpp
int fxx[9]={0,-1,-1,-1,0,0,1,1,1}; // 方向数组明确
void dfs(int x,int y){
    a[x][y]='.';
    for(int i=1;i<=8;i++){ // 严格遍历8方向
        int r=x+fxx[i], c=y+fxy[i];
        if(r>=1 && r<=n && c>=1 && c<=m && a[r][c]=='W')
            dfs(r,c);
    }
}
```

#### 3. loceaner（BFS手写队列） ★★★★
**核心亮点**  
- 手写队列避免STL性能问题  
- 显式八方向判断，适合教学  
```cpp
void bfs(int x,int y){
    int head=0,tail=1;
    q[tail] = {x,y};
    while(head<tail){
        auto p = q[++head];
        for(int i=0;i<8;i++){ // 直接枚举8方向
            int xx=p.x+dx[i], yy=p.y+dy[i];
            if(xx>=1 && xx<=n && yy>=1 && yy<=m && a[xx][yy]=='W'){
                a[xx][yy] = '.'; // 先标记后入队
                q[++tail] = {xx,yy};
            }
        }
    }
}
```

---

### 关键思路总结
1. **方向数组**：预定义dx/dy数组（如`{-1,0,1}`的笛卡尔积）简化方向遍历  
2. **原地标记**：将访问过的'W'改为'.'，省去visited数组空间  
3. **输入优化**：按行读入字符串避免逐字符处理换行符  
4. **边界检查**：先判断坐标合法性再访问数组元素  

---

### 拓展练习推荐
1. **P1451 求细胞数量** - 四连通块基础模板  
2. **P1506 拯救oibh总部** - 连通块边界处理  
3. **P2298 Mzc和男家丁的游戏** - BFS求最短路径  

---

### 调试经验摘录
- **Caicz**：使用`scanf(" %c")`而非`%c`过滤空白符，避免换行符错误  
- **焚魂**：因未改方向数组符号导致40分，强调边界检查重要性  
- **SasukeUchiha**：并查集解法中发现行列混淆导致错误，建议优先选择DFS/BFS  

核心教训：**方向数组必须完整覆盖8方向，输入时注意换行符处理，优先使用更易调试的DFS实现**。

---
处理用时：63.17秒