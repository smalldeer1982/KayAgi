# 题目信息

# [ARC031B] 埋め立て

## 题目描述

很久很久以前，某地曾有一个岛国。这个岛国由一些岛屿组成。现在，这个岛国决定填海造陆，但还没有决定填海造陆的位置。政府希望填海造陆工程能够将所有岛屿连接起来，成为一个岛屿。



给出 $10$ 格 $×10$ 格的该国地图，请判断：能否仅将一格海洋变成陆地，使该国所有岛屿连接成一个岛屿。另外，地图中表示陆地的格子上下左右互相连接的区域称为一个岛屿。

## 样例 #1

### 输入

```
xxxxxxxxxx

xoooooooxx

xxoooooxxx

xxxoooxxxx

xxxxoxxxxx

xxxxxxxxxx

xxxxoxxxxx

xxxoooxxxx

xxoooooxxx

xxxxxxxxxx```

### 输出

```
YES```

## 样例 #2

### 输入

```
xxxxxxxxxx

xoooooooxx

xxoooooxxx

xxxoooxxxx

xxxxxxxxxx

xxxxxxxxxx

xxxxxxxxxx

xxxoooxxxx

xxoooooxxx

xxxxxxxxxx```

### 输出

```
NO```

## 样例 #3

### 输入

```
xxxxoxxxxx

xxxxoxxxxx

xxxxoxxxxx

xxxxoxxxxx

ooooxooooo

xxxxoxxxxx

xxxxoxxxxx

xxxxoxxxxx

xxxxoxxxxx

xxxxoxxxxx```

### 输出

```
YES```

# AI分析结果



# [ARC031B] 埋め立て

## 题目描述

给出一个 10×10 的网格地图，判断能否通过将恰好一个海洋格子（用 'x' 表示）变为陆地（用 'o' 表示），使得所有陆地连接成一个岛屿。岛屿定义为上下左右相邻的陆地组成的连通区域。

---

**算法分类**: 枚举 + 深度优先搜索（DFS） / 广度优先搜索（BFS）

---

### 通用解题思路与优化建议

#### 关键思路
1. **暴力枚举**：遍历所有海洋格子，逐一尝试将其变为陆地。
2. **连通性验证**：对每个填充后的地图，使用 DFS/BFS 计算连通块数量。若存在一个填充点使得连通块数量为 1，则输出 "YES"。
3. **时间复杂度优化**：由于网格固定为 10×10，总枚举次数为 100 次，每次连通性检查的时间复杂度为 O(10×10) = O(1)，整体时间复杂度可接受。

#### 解决难点
- **正确性保证**：必须枚举所有可能的填充点，而不仅仅是某个初始岛屿周围的点。
- **状态恢复**：每次枚举后需恢复地图原状，避免影响后续判断。

---

### 推荐题目
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)（连通块预处理）
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)（BFS 应用）
3. [P2895 USACO08FEB Meteor Shower S](https://www.luogu.com.cn/problem/P2895)（BFS 最短路径）

---

### 正确代码实现（核心逻辑）
```cpp
#include <bits/stdc++.h>
using namespace std;

char grid[12][12];
bool vis[12][12];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

// 计算连通块数量
int count_components() {
    memset(vis, 0, sizeof vis);
    int cnt = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j] == 'o' && !vis[i][j]) {
                cnt++;
                queue<pair<int, int>> q;
                q.push({i, j});
                vis[i][j] = true;
                while (!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dx[d], ny = y + dy[d];
                        if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && !vis[nx][ny] && grid[nx][ny] == 'o') {
                            vis[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }
    return cnt;
}

int main() {
    for (int i = 0; i < 10; ++i) cin >> grid[i];
    
    // 检查原始地图是否已经连通
    if (count_components() == 1) {
        cout << "YES\n";
        return 0;
    }

    // 枚举每个海洋格子尝试填充
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j] == 'x') {
                grid[i][j] = 'o';
                if (count_components() == 1) {
                    cout << "YES\n";
                    return 0;
                }
                grid[i][j] = 'x'; // 恢复原状
            }
        }
    }
    cout << "NO\n";
    return 0;
}
```

#### 核心思想
- **主循环枚举**：遍历每个海洋格子进行填充尝试。
- **BFS 计数**：对填充后的地图统计连通块数量，直接判断是否满足条件。
- **提前终止**：一旦找到可行解立即输出结果，避免无效计算。

---
处理用时：140.11秒