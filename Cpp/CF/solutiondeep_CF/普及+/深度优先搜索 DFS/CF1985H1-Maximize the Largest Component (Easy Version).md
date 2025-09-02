# 题目信息

# Maximize the Largest Component (Easy Version)

## 题目描述

Easy and hard versions are actually different problems, so read statements of both problems completely and carefully. The only difference between the two versions is the operation.

Alex has a grid with $ n $ rows and $ m $ columns consisting of '.' and '\#' characters. A set of '\#' cells forms a connected component if from any cell in this set, it is possible to reach any other cell in this set by only moving to another cell in the set that shares a common side. The size of a connected component is the number of cells in the set.

In one operation, Alex selects any row $ r $ ( $ 1 \le r \le n $ ) or any column $ c $ ( $ 1 \le c \le m $ ), then sets every cell in row $ r $ or column $ c $ to be '\#'. Help Alex find the maximum possible size of the largest connected component of '\#' cells that he can achieve after performing the operation at most once.

## 说明/提示

In the second test case, it is optimal for Alex to set all cells in column $ 2 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 6 $ .

In the third test case, it is optimal for Alex to set all cells in row $ 2 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 9 $ .

In the fourth test case, it is optimal for Alex to set all cells in row $ 4 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 11 $ .

## 样例 #1

### 输入

```
6
1 1
.
4 2
..
#.
#.
.#
3 5
.#.#.
..#..
.#.#.
5 5
#...#
....#
#...#
.....
...##
6 6
.#..#.
#..#..
.#...#
#.#.#.
.#.##.
###..#
6 8
..#....#
.####.#.
###.#..#
.##.#.##
.#.##.##
#..##.#.```

### 输出

```
1
6
9
11
15
30```

# AI分析结果



# Maximize the Largest Component (Easy Version)

## 题目描述

Alex 有一个由 `.` 和 `#` 组成的 $n$ 行 $m$ 列的网格。连通组件定义为相邻（共享边）的 `#` 单元格集合，其大小为包含的单元格数。允许选择任意一行或一列将其全部变为 `#`，求操作后最大连通组件的大小。

## 样例说明

- 样例2：选择第2列，得到大小为6的连通块
- 样例3：选择第2行，得到大小为9的连通块
- 样例4：选择第4行，得到大小为11的连通块

---

## 题解综合分析

### 核心思路
所有题解均采用**预处理连通块+枚举行列**的两阶段策略：
1. **连通块预处理**：使用DFS/BFS/并查集标记每个`#`所属连通块并记录大小
2. **行列枚举计算**：遍历所有行/列，计算该行/列变为`#`后连接的相邻连通块总和，使用集合去重避免重复累加

### 算法对比
| 方法       | 预处理方式 | 去重策略       | 实现复杂度 |
|------------|------------|----------------|------------|
| DFS/BFS    | 连通块标记 | Set存储块ID    | ★★★☆☆      |
| 并查集     | 合并相邻块 | Set统计根节点  | ★★★★☆      |

### 最优题解

#### 1. Eddie08012025（★★★★☆）
**关键亮点**：
- 使用DFS预处理连通块，逻辑清晰
- 行列处理对称实现，代码复用性高
- 通过`min/max`处理边界条件避免越界

**核心代码**：
```cpp
void dfs(int x,int y){
    vis[x][y] = 1;
    shu[cnt]++;
    a[x][y] = cnt;
    for(int i=0;i<4;i++){ // 四方向扩展
        int nx = x+dx[i], ny = y+dy[i];
        if(nx<1||ny<1||nx>n||ny>m||vis[nx][ny]||z[nx][ny]=='.')continue;
        dfs(nx,ny);
    }
}

// 行处理逻辑
for(int j=1;j<=m;j++){
    c.clear(); 
    sum = 0;
    for(int i=1;i<=n;i++){
        if(z[i][j]=='.') sum++; // 统计新增#
        else c.insert(a[i][j]); // 添加当前块
        // 添加相邻列块
        if(z[i][max(1,j-1)]=='#')c.insert(a[i][max(1,j-1)]);
        if(z[i][min(m,j+1)]=='#')c.insert(a[i][min(m,j+1)]);
    }
    for(int i:c) sum += shu[i]; // 累加连通块大小
    ans = max(ans,sum);
}
```

#### 2. Rachel_liu（★★★★☆）
**关键亮点**：
- 并查集实现连通块合并，适合动态扩展
- 一维化存储解决二维空间问题
- 使用Set快速统计关联块

**核心代码**：
```cpp
void join(ll x, ll y){
    ll fx = find(x), fy = find(y);
    if(fx != fy) {
        f[fx] = fy;
        size[fy] += size[fx];
    }
}

// 行处理逻辑
for(int i=1;i<=n;i++){
    set<ll> st; 
    ll sum = m; // 该行总格子数
    for(int j=1;j<=m;j++){
        if(!mp[id(i,j)]) sum--; // 原为.的格子
        // 收集相邻列连通块
        st.insert(find(id(i,j)));
        st.insert(find(id(max(1,i-1),j)));
        st.insert(find(id(min(n,i+1),j)));
    }
    // 累加连通块大小
    for(auto x : st) sum += size[x];
    ans = max(ans, sum);
}
```

#### 3. imsbNR（★★★★☆）
**关键亮点**：
- 哈希化二维坐标为线性地址
- 预处理时区分已处理单元格
- 简洁的边界条件处理

**核心技巧**：
```cpp
int ID(int x,int y){ return (x-1)*m + y; }

void solve(){
    // 预处理连通块
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!vis[ID(i,j)] && a[ID(i,j)] == -1)
                dfs(i,j,++cnt);
    
    // 行处理
    for(int i=1;i<=n;i++){
        set<int> st;
        int sum = 0;
        for(int j=1;j<=m;j++){
            sum += (a[ID(i,j)] == 0); // 新增#
            st.insert(a[ID(i,j)]);    // 当前块
            // 相邻行块
            if(i>1) st.insert(a[ID(i-1,j)]);
            if(i<n) st.insert(a[ID(i+1,j)]);
        }
        for(int x:st) sum += sz[x];
        ans = max(ans,sum);
    }
}
```

---

## 关键思路总结

1. **连通块预处理**：必须预先计算每个`#`的归属及块大小，后续才能快速统计
2. **集合去重机制**：使用Set存储关联块ID，避免重复累加同一块
3. **边界安全处理**：通过`min/max`或条件判断避免数组越界
4. **行列对称处理**：行列处理逻辑完全对称，可复用代码结构

---

## 拓展练习

1. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162) - 连通块边界处理
2. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141) - 连通块预处理+查询优化
3. [P1331 海战](https://www.luogu.com.cn/problem/P1331) - 连通块形状判断

---
处理用时：66.38秒