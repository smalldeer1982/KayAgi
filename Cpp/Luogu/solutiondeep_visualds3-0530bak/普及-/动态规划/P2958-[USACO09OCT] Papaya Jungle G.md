# 题目信息

# [USACO09OCT] Papaya Jungle G

## 题目描述

Bessie has wandered off the farm into the adjoining farmer's land. He raises delicious papaya fruit, which is a delicacy for cows. The papaya jungle is partitioned into a grid of squares with R rows and C columns (1 <= R <= 40, 1 <= C <= 40), as is popular in Wisconsin. Bessie can travel from a given square to any existing adjacent square whose route is parallel to the X or Y axis.  So in the

following diagram, if Bessie is at the square labeled 'B', she can travel to any of the squares labeled 'T':

.T.
TBT
.T.
Bessie always starts out by munching the papayas in square

(row=1,col=1).  After she's done with one square, Bessie always uses her trusty binoculars to count the low-hanging fruit in each of the adjacent squares. She then always moves to the square with the most visible uneaten fruit (a square that happily is always unique).

Sooner or later, following this rule, Bessie always ends up in square (R,C) and eats the fruit there.

Given the dimensions of the papaya jungle and the amount of fruit F\_ij in each square (1 <= F\_ij <= 100), determine the total number of fruit Bessie consumes for a given papaya jungle.

POINTS: 80

Bessie不小心游荡出Farmer John的田地，而走进了相邻的农民的地里。她举起一个木瓜，木瓜对奶牛来说可是不可多得得美味。这个木瓜林像一般的威斯康星州的田地一样被分割成一个R行C列的网格(1 <= R <= 40, 1 <= C <= 40)。Bessie可以从一个格沿着一条跟X轴或Y轴平行的直线走到邻接的另一个格。Bessie发现一开始她自己在木瓜林的(1,1)，也就是第一行第一列慢悠悠地咀嚼着木瓜。

Bessie总是用她最信赖地双筒望远镜去数每一个邻接的格里挂着的木瓜的数目。然后她就游荡到那个有最多没有被吃掉的木瓜的邻接的格子（保证这样的格子只有一个）。

按照这种移动方法，最终Bessie总是会在(R,C)停止然后吃掉那里的木瓜。

给定这个木瓜林的大小及每个格的木瓜数F\_ij(1 <= F\_ij <= 100), 要求Bessie一共吃了多少个木瓜。


## 说明/提示

Three rows; four columns. Bessie starts in upper left corner at the '3'.


Bessie eats the papayas in the order given by the letters next to the numbers below:

(1,1) ---> (1,C) 

(1,1) 3a  3   4g  5h  (1,C) 

|   4b  5c  3f  2i    |

(R,1) 1   7d  4e  2j  (R,C) 

(R,1) ---> (R,C) 

She declines to eat 4 of the papayas but consumes 39 (visiting all but two squares of the grid). 



## 样例 #1

### 输入

```
3 4 
3 3 4 5 
4 5 3 2 
1 7 4 2 
```

### 输出

```
39 
```

# AI分析结果



**唯一算法分类**：贪心

---

### **题解思路、算法要点与解决难点**

**核心思路**：  
Bessie 的移动路径由贪心策略决定，每次选择相邻未访问格子中木瓜最多的方向。关键点在于：
1. **移动方向选择**：每次遍历四个相邻格子，记录最大值位置。
2. **访问标记**：通过将已访问格子的木瓜数置零，避免重复访问。
3. **终止条件**：当到达终点 (R,C) 时停止，确保终点的值被正确累加。

**解决难点**：
- **方向优先级处理**：必须遍历四个方向找到最大值，而非依赖条件判断顺序。
- **终点处理**：需在移动后立即累加终点的值，避免遗漏。

---

### **题解评分（≥4星）**

1. **zjj20051228（递归DFS，4星）**  
   - **亮点**：递归实现简洁，正确通过置零标记已访问。
   - **缺点**：递归深度可能较大，但题目数据范围允许。

2. **荷叶下（循环模拟，4星）**  
   - **亮点**：循环遍历四个方向，记录最大值，结构清晰。
   - **代码示例**：
     ```cpp
     void bfs() {
         int maxn, maxx, maxy;
         while (u != n || v != m) {
             maxn = 0;
             for (int i = 1; i <= 4; i++) {
                 int tx = u + dx[i], ty = v + dy[i];
                 if (mapp[tx][ty] >= maxn) {
                     maxn = mapp[tx][ty];
                     maxx = tx; maxy = ty;
                 }
             }
             u = maxx; v = maxy;
             ans += maxn;
         }
     }
     ```

3. **鸿飞（BFS思想，4星）**  
   - **亮点**：循环模拟移动，通过置零避免重复访问，代码逻辑严密。

---

### **最优思路提炼**

1. **贪心移动**：每次选择相邻最大值方向，无需回溯。
2. **标记已访问**：通过置零或布尔数组标记，保证不重复计数。
3. **边界检查**：每次移动前检查坐标是否越界。

---

### **同类型题与类似算法**

- **类似题目**：机器人路径规划（每次选择最大收益方向）。
- **通用解法**：贪心模拟、BFS/DFS 路径遍历。

---

### **推荐题目**

1. **P1219 八皇后**（路径选择与回溯）
2. **P1443 马的遍历**（BFS 最短路径）
3. **P1135 奇怪的电梯**（BFS 最短步数）

---

### **个人心得摘录**

- **循环条件陷阱**：`while (x != r || y != c)` 必须用逻辑或，避免错误退出。
- **终点处理**：需显式累加终点的值，或在循环内提前处理。

---

### **可视化与算法演示**

**动画设计**：  
- **网格绘制**：用 Canvas 绘制 R×C 网格，当前格子高亮为绿色，已访问置灰。
- **移动过程**：每次遍历四个方向，红色闪烁显示最大值格子，并播放音效。
- **交互控制**：支持暂停/继续、步进执行、调整速度。

**复古像素风格**：  
- **8位调色板**：绿色（当前格子）、红色（最大值）、灰色（已访问）。
- **音效**：移动时播放短音效，到达终点播放胜利音效。

---

### **代码实现（核心逻辑）**

```cpp
#include <iostream>
using namespace std;

int main() {
    int r, c, sum = 0;
    cin >> r >> c;
    int grid[r+2][c+2] = {0};  // 多一圈边界避免越界检查
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            cin >> grid[i][j];
    
    int x = 1, y = 1;
    sum += grid[x][y];
    grid[x][y] = 0;
    
    while (x != r || y != c) {
        int max_val = -1, dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
        int next_x, next_y;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 1 && nx <= r && ny >= 1 && ny <= c && grid[nx][ny] > max_val) {
                max_val = grid[nx][ny];
                next_x = nx;
                next_y = ny;
            }
        }
        
        x = next_x, y = next_y;
        sum += grid[x][y];
        grid[x][y] = 0;
    }
    
    cout << sum << endl;
    return 0;
}
```

**核心思想**：  
- 初始化时处理起点，进入循环后遍历四个方向找到最大值。
- 每次移动后累加并置零，直到到达终点。

---
处理用时：165.29秒