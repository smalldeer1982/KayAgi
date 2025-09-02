# 题目信息

# [USACO06OCT] Cows on Skates G

## 题目描述

**本题使用 Special Judge。**

Farmer John 把农场划分为了一个 $r$ 行 $c$ 列的矩阵，并发现奶牛们无法通过其中一些区域。此刻，Bessie 位于坐标为 $(1,1)$ 的区域，并想到坐标为 $(r,c)$ 的牛棚享用晚餐。她知道，以她所在的区域为起点，每次移动至相邻的四个区域之一，总有一些路径可以到达牛棚。

这样的路径可能有无数种，请你输出任意一种，并保证所需移动次数不超过 $100000$。

## 说明/提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le r\le 113$，$1\le c\le 77$。

------------

**【样例说明】* *

![](https://cdn.luogu.com.cn/upload/image_hosting/3gsutffb.png)

图为样例输出的示意图。答案不唯一。

## 样例 #1

### 输入

```
5 8
..*...**
*.*.*.**
*...*...
*.*.*.*.
....*.*.```

### 输出

```
1 1
1 2
2 2
3 2
3 3
3 4
2 4
1 4
1 5
1 6
2 6
3 6
3 7
3 8
4 8
5 8```

# AI分析结果



### 综合分析与结论
本题为迷宫路径输出问题，核心是路径记录与搜索剪枝。所有题解均采用DFS/BFS实现，核心差异在于：
1. **路径记录方式**：递归栈记录、前驱数组重构、全局数组回溯
2. **标记管理**：DFS中是否回溯vis数组是效率关键
3. **终止条件**：找到路径后立即退出（exit(0)/return标记）

### 高星题解推荐（≥4星）
#### 1. [作者：MY] ⭐⭐⭐⭐
**关键亮点**：
- DFS不回溯vis数组，避免重复搜索
- 路径记录与终止逻辑清晰，直接操作全局数组
- 代码注释明确，包含踩坑提醒（标记不回溯）

**核心代码**：
```cpp
void dfs(int x,int y,int step) {
    if(f) return; // 提前终止
    if(到达终点){
        // 输出路径（不包含终点）
        printf("%d %d",r,c); // 单独输出终点
        f = true;
    }
    for(四方向){
        if(可走且未访问){
            book[x][y] = 1; // 标记不回溯
            dfs(新坐标,step+1);
        }
    }
}
```

#### 2. [作者：wuyonghuming] ⭐⭐⭐⭐
**关键亮点**：
- 简洁的DFS实现，无回溯
- 路径数组直接记录坐标
- 输入优化（scanf字符串读取）

**核心实现**：
```cpp
void dfs(int x,int y,int w) {
    ansx[w]=x; ansy[w]=y; // 直接记录路径
    if(到达终点){
        for输出所有记录点
        exit(0); // 直接终止
    }
    for(四方向){
        p[nx][ny] = true; // 永久标记
        dfs(nx,ny,w+1);
    }
}
```

#### 3. [作者：☆木辛土申☆] ⭐⭐⭐⭐
**关键亮点**：
- BFS+前驱数组重构路径
- 使用pair队列简化代码
- 递归逆序输出路径

**核心片段**：
```cpp
void bfs(int sx,int sy) {
    queue<pair<int,int>> q;
    q.push({sx,sy});
    while(!q.empty()){
        auto [x,y] = q.front();
        for(四方向){
            dist[xx][yy] = {x,y}; // 记录前驱
            if(到达终点) return;
        }
    }
}

void WriteWay(int x,int y) { // 递归输出路径
    if(前驱存在){
        WriteWay(前驱坐标);
        printf("%d %d\n",x,y);
    }
}
```

### 最优关键思路总结
1. **DFS标记优化**：找到路径后无需回溯vis数组，直接终止搜索
2. **路径记录技巧**：
   - DFS：全局数组按递归顺序记录
   - BFS：前驱数组逆向重构路径
3. **终止方式**：使用`exit(0)`或标志变量立即结束搜索

### 拓展建议
1. **同类题目**：
   - [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)（基础DFS）
   - [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)（连通块+BFS）
   - [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)（BFS最短路）

2. **调试心得**：
   > "DFS中vis数组不回溯节省大量时间" —— 多个题解作者通过TLE教训发现此优化点  
   > "BFS路径重构时需递归输出" —— 前驱数组需逆序处理，避免使用额外存储

### 重点代码示例（BFS路径重构）
```cpp
// BFS核心路径记录
int dist[120][80][2]; // 存储前驱坐标

void bfs() {
    // ... BFS过程 ...
    dist[xx][yy][0] = x; // 当前点的前驱x
    dist[xx][yy][1] = y; // 前驱y
}

// 递归输出路径
void print_path(int x, int y) {
    if(x == 1 && y == 1) {
        cout << "1 1\n";
        return;
    }
    print_path(dist[x][y][0], dist[x][y][1]);
    cout << x << " " << y << endl;
}
```

---
处理用时：52.46秒