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



### 综合分析与结论
本题核心是模拟Bessie的移动路径，每次选择相邻格子中木瓜最多的方向，直到终点。各题解主要采用DFS/BFS递归、循环模拟两种思路，通过修改原数组或标记数组避免重复访问。关键点在于正确累加路径上的木瓜值及终止条件处理。

### 高星题解推荐
#### 1. 作者：zjj20051228（5星）
**关键亮点**  
- 使用DFS递归实现，代码简洁清晰。  
- 通过方向数组遍历四个邻接点，动态更新最大值。  
- 直接修改原数组避免重复访问，无需额外空间。  
**核心代码**  
```cpp
void dfs(int x,int y) {
    sum += a[x][y];
    a[x][y] = 0;
    if (x == r && y == c) return;
    int mx, my, ans = 0;
    for (int i = 0; i < 4; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx >= 1 && tx <= r && ty >= 1 && ty <= c && a[tx][ty] > ans) {
            ans = a[tx][ty];
            mx = tx, my = ty;
        }
    }
    dfs(mx, my);
}
```

#### 2. 作者：SCLBJKD（4星）
**关键亮点**  
- 循环模拟移动过程，逻辑直观。  
- 使用标记数组避免重复访问，适合不修改原数组的场景。  
- 处理循环条件时强调使用`!(x == n && y == m)`防止边界错误。  
**个人心得**  
> "循环条件不能写成`x != n && y != m`，否则可能在单坐标到达终点时提前退出。"  

**核心代码**  
```cpp
while (1) {
    sum += g[i][j];
    g[i][j] = 0;
    if (i == r && j == c) break;
    // 选择下一个最大邻接点
    if (g[i+1][j] > g[i][j+1] && ...) i++;
    // 其他方向类似判断
}
```

#### 3. 作者：荷叶下（4星）
**关键亮点**  
- BFS思路实现，队列辅助控制流程。  
- 在循环外累加终点值，确保最终结果正确。  
**核心代码**  
```cpp
void bfs() {
    while (u != n || v != m) {
        ans += mapp[u][v];
        mapp[u][v] = 0;
        // 寻找最大值邻接点并更新u,v
    }
    ans += mapp[u][v]; // 确保终点值被累加
}
```

### 最优思路总结
- **贪心选择**：每次移动选择邻接点中最大值，无需回溯。  
- **空间优化**：直接修改原数组（置零）替代标记数组，节省内存。  
- **终止处理**：在递归或循环内部累加终点值，或循环外显式处理。  

### 拓展与相似题目
1. **P1135 奇怪的电梯** - 每一步选择楼层，模拟移动。  
2. **P1443 马的遍历** - BFS遍历棋盘，记录步数。  
3. **P1162 填涂颜色** - 矩阵遍历与标记技巧。  

### 关键实现技巧
- **方向数组**：使用`dx[4]`和`dy[4]`简化邻接点遍历。  
- **原地修改**：通过置零或标记数组避免重复计算，保证路径唯一性。  
- **边界检查**：在移动前验证坐标合法性（如`tx >= 1 && tx <= r`）。  

```cpp
// 方向数组与邻接点遍历示例
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
for (int i = 0; i < 4; i++) {
    int tx = x + dx[i], ty = y + dy[i];
    if (tx >= 1 && tx <= r && ty >= 1 && ty <= c) {
        // 处理邻接点
    }
}
```

---
处理用时：130.49秒