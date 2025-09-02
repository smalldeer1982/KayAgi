# 题目信息

# Statues

## 题目描述

In this task Anna and Maria play a game with a very unpleasant rival. Anna and Maria are in the opposite squares of a chessboard ( $ 8×8 $ ): Anna is in the upper right corner, and Maria is in the lower left one. Apart from them, the board has several statues. Each statue occupies exactly one square. A square that contains a statue cannot have anything or anyone — neither any other statues, nor Anna, nor Maria.

Anna is present on the board as a figurant (she stands still and never moves), and Maria has been actively involved in the game. Her goal is — to come to Anna's square. Maria and statues move in turn, Maria moves first. During one move Maria can go to any adjacent on the side or diagonal cell in which there is no statue, or she can stay in the cell where she is. The statues during their move must go one square down simultaneously, and those statues that were in the bottom row fall from the board and are no longer appeared.

At that moment, when one of the statues is in the cell in which the Maria is, the statues are declared winners. At the moment when Maria comes into the cell where Anna has been waiting, Maria is declared the winner.

Obviously, nothing depends on the statues, so it all depends on Maria. Determine who will win, if Maria does not make a strategic error.

## 样例 #1

### 输入

```
.......A
........
........
........
........
........
........
M.......
```

### 输出

```
WIN
```

## 样例 #2

### 输入

```
.......A
........
........
........
........
........
SS......
M.......
```

### 输出

```
LOSE
```

## 样例 #3

### 输入

```
.......A
........
........
........
........
.S......
S.......
MS......
```

### 输出

```
LOSE
```

# AI分析结果



# Statues 题解分析

## 题目重述
### 题目描述
Anna和Maria在一个8x8的棋盘的对角位置：Anna在右上角，Maria在左下角。棋盘上有若干雕像，每个雕像占据一个格子。Maria和雕像交替移动，Maria先动。每回合Maria可移动到相邻（包括对角线）的无雕像格子或停留，雕像则同步下移一格，底行雕像会掉出棋盘。若Maria到达Anna的位置则胜利，若与雕像同位置则失败。求Maria能否必胜。

## 算法分类
深度优先搜索 DFS

---

## 题解对比与结论

### 核心思路
所有题解均采用DFS模拟移动，关键点在于：
1. **存活步数限制**：雕像最多8步会掉出棋盘，只需判断8步内存活即可到达终点。
2. **雕像位置计算**：不显式模拟下落，而是通过当前步数反推雕像初始行，判断是否会与当前位置冲突。

### 最优题解亮点

#### 题解1：JiaY19（4星）
- **关键实现**：用数组`f`记录初始雕像位置，DFS时通过步数计算当前行是否有雕像。
- **代码亮点**：
  ```cpp
  // 判断移动后位置(vx,vy)在s步时是否安全
  if(f[vx - 8 + s -1][vy] || f[vx - 8 + s][vy]) continue;
  ```
- **心得**：通过数学推导将动态下落转化为静态计算，极大简化逻辑。

#### 题解2：yzh_Error404（4星）
- **关键实现**：将步数`step`作为参数，直接计算当前行可能存在的雕像。
- **代码亮点**：
  ```cpp
  if(ma[nx-step-1][ny]==2||ma[nx-step][ny]==2) continue;
  ```
- **心得**：通过`step`参数逆向推算雕像位置，避免动态维护地图状态。

---

## 关键代码实现
以 yzh_Error404 的代码为例：
```cpp
bool dfs(int x, int y, int step) {
    if(step == 8) return true;
    for(移动9个方向) {
        // 计算新坐标(nx, ny)
        if(越界) continue;
        // 判断新坐标是否会被当前或下一时刻的雕像击中
        if(初始地图[nx - step][ny]有雕像 || 初始地图[nx - step -1][ny]有雕像)
            continue;
        if(dfs(nx, ny, step+1)) return true;
    }
    return false;
}
```

---

## 拓展建议
- **类似题目**：棋盘移动+动态障碍类问题
  - 洛谷P1443 马的遍历（BFS基础）
  - 洛谷P1132 数字生成游戏（状态转移）
  - 洛谷P3958 奶酪（三维空间DFS）

## 个人心得摘录
> "通过数学推导将动态下落转化为静态计算，代码复杂度从O(2^N)降为O(9^8)" —— 逆向思维是优化搜索的关键。  
> "不要尝试模拟每个雕像的位置变化，而要通过相对位置计算碰撞" —— 空间换时间的典型应用。

---
处理用时：69.02秒