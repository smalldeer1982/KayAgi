# 题目信息

# [ARC177C] Routing

## 题目描述

有一个 $N$ 行 $N$ 列（用 $(i, j)$ 表示矩阵第 $i$ 行第 $j$ 列的元素）的矩阵被刷满了红色和蓝色。现在要矩阵的一些格子刷上紫色，使得矩阵**同时**满足以下两个条件：
- 从 $(1, 1)$ 走到 $(N, N)$，保证存在一条路径使其只经过红色和紫色；
- 从 $(1, N)$ 走到 $(N, 1)$，保证存在一条路径使其只经过蓝色和紫色

注意，**行动时他可以往任何一个方向前进。**

那么，问题来了，至少要将多少格子刷成紫色才能使以上两个条件成立呢？

## 样例 #1

### 输入

```
5

RBRBB

RBRRR

RRRBR

RBBRB

BBRBR```

### 输出

```
3```

## 样例 #2

### 输入

```
5

RBBBB

BBBBB

BBBBB

BBBBB

BBBBR```

### 输出

```
7```

## 样例 #3

### 输入

```
10

RRBBBBBBBB

BRRBBBBBBB

BBRRBBBBBB

BBBRRBBBBB

BBBBRRBBBB

BBBBBRRBBB

BBBBBBRRBB

BBBBBBBRRB

BBBBBBBBRR

BBBBBBBBBR```

### 输出

```
2```

## 样例 #4

### 输入

```
17

RBBRRBRRRRRBBBBBB

BBRBRBRRBRRBRRBBR

BRBRBBBRBBRBBRBBB

RBRRBBBBBBRRBRRRR

RRRRRBRBRRRBBRBBR

RRRRRBRRBRBBRRRBB

BBBRRRBRBRBBRRRBB

BBRRRBRBBBRBRRRBR

RRBBBBBBBBBBBRBRR

RRRBRRBRBRBRBRBBB

RRBRRRRBRBRRBRBBR

RRRBBRBRBBBRBBRBR

BBRBBRRBRRRBBRBBB

BBBRBRRRRRRRBBRBB

RRRRRBRBRBBRRBRRR

BRRRRBBBRRRBRRBBB

BBRRBBRRRBBBRBBBR```

### 输出

```
8```

# AI分析结果



---

## **算法分类**
**01BFS**

---

## **题解思路与算法要点**

### **核心思路**
将问题拆分为两个独立的最短路径问题：
1. **红色路径**：从(1,1)到(n,n)，允许经过红/紫色，求最少需要将多少蓝格子涂紫。
2. **蓝色路径**：从(1,N)到(N,1)，允许经过蓝/紫色，求最少需要将多少红格子涂紫。

### **解决难点**
- **图建模**：将每个格子视为图节点，相邻格子连边，边权由目标格子颜色决定（红路径中蓝格子边权为1，反之同理）。
- **独立性问题**：两条路径的修改互不影响，因为紫色对两种颜色均合法。
- **高效计算**：使用01BFS处理边权仅为0/1的最短路问题，时间复杂度优化至O(N²)。

### **关键变量与数据结构**
- **双端队列 (deque)**：优先处理边权为0的节点（队头插入），边权为1的节点（队尾插入）。
- **距离数组 dis[][]**：记录从起点到每个节点的最小代价（需涂紫的格子数）。

---

## **题解评分 (≥4星)**

1. **__Floze3__ (5星)**  
   - **亮点**：明确解释01BFS的正确性，代码简洁高效，使用双端队列优化。
   - **代码**：两次01BFS直接叠加，正确处理颜色判断逻辑。

2. **what_can_I_do (5星)**  
   - **亮点**：提供完整可运行代码，使用双端队列实现01BFS，逻辑清晰。
   - **代码**：通过 `ch != mp[x][y]` 动态计算边权，直接累加两次BFS结果。

3. **破壁人罗辑 (4星)**  
   - **亮点**：提出类似动态规划的BFS更新策略，分队列处理0/1边权。
   - **优化**：通过两个队列（当前层/下一层）实现隐式01BFS，避免显式优先队列。

---

## **最优思路提炼**
### **核心技巧**
1. **问题分解**：将双路径问题拆解为两个独立的最短路径子问题。
2. **01BFS优化**：利用双端队列处理边权0/1的最短路，时间复杂度O(N²)。
3. **颜色互斥建模**：对红/蓝路径分别定义边权，红路径中蓝格子代价+1，反之亦然。

### **代码片段**
```cpp
// 01BFS 核心逻辑（以红色路径为例）
deque<aaa> q;
q.push_front({sx, sy, (起点颜色是否为红)});
while (!q.empty()) {
    auto now = q.front(); q.pop_front();
    for (四个方向) {
        int cost = (目标颜色 != 'R'); // 蓝格子需涂紫，代价+1
        if (dis[x][y] > now.s + cost) {
            dis[x][y] = now.s + cost;
            if (cost == 0) q.push_front({x, y, dis[x][y]});
            else q.push_back({x, y, dis[x][y]});
        }
    }
}
```

---

## **同类型题目推荐**
1. **洛谷 P1141** - 01迷宫（BFS处理连通块）
2. **洛谷 P3958** - 奶酪（三维BFS/DFS）
3. **AtCoder ABC213E** - 01BFS模板题

---

## **可视化与算法演示**
### **动画设计**
- **网格渲染**：用不同颜色表示红(R)、蓝(B)、紫(P)格子，路径扩展时高亮当前节点。
- **队列状态**：可视化双端队列，区分队头（0权边）和队尾（1权边）的节点插入过程。
- **动态更新**：实时显示距离矩阵的数值变化，紫色格子数量累加过程。

### **复古像素风格**
- **调色板**：红(#FF0000)、蓝(#0000FF)、紫(#FF00FF)、路径高亮(#FFFF00)。
- **音效**：
  - **节点扩展**：8-bit "beep" 音效（0权边低音，1权边高音）。
  - **路径完成**：经典 FC 过关音效。
- **自动演示**：按步进播放BFS过程，支持暂停/加速。

---

## **代码实现**
### **完整代码（基于 what_can_I_do 题解）**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, dis[510][510];
char mp[510][510];
struct Node { int x, y, s; };
deque<Node> q;
int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};

void bfs(int sx, int sy, int ex, int ey, char target) {
    memset(dis, 0x3f, sizeof(dis));
    q.push_front({sx, sy, (mp[sx][sy] != target)});
    dis[sx][sy] = (mp[sx][sy] != target);
    while (!q.empty()) {
        auto now = q.front(); q.pop_front();
        if (now.x == ex && now.y == ey) {
            q.clear();
            return;
        }
        for (int i = 0; i < 4; i++) {
            int x = now.x + dx[i], y = now.y + dy[i];
            if (x <1 || x>n || y<1 || y>n) continue;
            int cost = (mp[x][y] != target);
            if (dis[x][y] > now.s + cost) {
                dis[x][y] = now.s + cost;
                cost == 0 ? q.push_front({x,y,dis[x][y]}) 
                          : q.push_back({x,y,dis[x][y]});
            }
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> mp[i][j];
    
    bfs(1, 1, n, n, 'R');
    int ans = dis[n][n];
    
    bfs(1, n, n, 1, 'B');
    cout << ans + dis[n][1];
    return 0;
}
```

---

## **个人心得**
- **调试教训**：初始队列的起点代价必须根据起点颜色动态计算（如起点是蓝色则初始代价为1）。
- **优化顿悟**：01BFS中双端队列的队首/队尾插入策略，相比优先队列减少一个log因子。
- **思维陷阱**：误以为两条路径的交点会重复计算，实际因颜色互斥可独立处理。

---
处理用时：98.43秒