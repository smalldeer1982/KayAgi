# 题目信息

# Polygon

## 题目描述

Polygon is not only the best platform for developing problems but also a square matrix with side $ n $ , initially filled with the character 0.

On the polygon, military training was held. The soldiers placed a cannon above each cell in the first row and a cannon to the left of each cell in the first column. Thus, exactly $ 2n $ cannons were placed.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/af538d3417e3bff02f7ca9d4302ffeb8985b4df9.png)Initial polygon for $ n=4 $ . Cannons shoot character 1. At any moment of time, no more than one cannon is shooting. When a 1 flies out of a cannon, it flies forward (in the direction of the shot) until it collides with a polygon border or another 1. After that, it takes the cell in which it was before the collision and remains there. Take a look at the examples for better understanding.

More formally:

- if a cannon stands in the row $ i $ , to the left of the first column, and shoots with a 1, then the 1 starts its flight from the cell ( $ i, 1 $ ) and ends in some cell ( $ i, j $ );
- if a cannon stands in the column $ j $ , above the first row, and shoots with a 1, then the 1 starts its flight from the cell ( $ 1, j $ ) and ends in some cell ( $ i,         j $ ).

For example, consider the following sequence of shots:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/b0a2a2240d9a0a11c84c2c0dd9be686db3e431b3.png) 1. Shoot the cannon in the row $ 2 $ . 2. Shoot the cannon in the row $ 2 $ . 3. Shoot the cannon in column $ 3 $ .

You have a report from the military training on your desk. This report is a square matrix with side length $ n $ consisting of 0 and 1. You wonder if the training actually happened. In other words, is there a sequence of shots such that, after the training, you get the given matrix?

Each cannon can make an arbitrary number of shots. Before the training, each cell of the polygon contains 0.

## 说明/提示

The first test case was explained in the statement.

The answer to the second test case is NO, since a 1 in a cell ( $ 1, 1 $ ) flying out of any cannon would continue its flight further.

## 样例 #1

### 输入

```
5
4
0010
0011
0000
0000
2
10
01
2
00
00
4
0101
1111
0101
0111
4
0100
1110
0101
0111```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果



---

### 唯一算法分类：其他搜索

---

### 题解思路与核心难点

#### 核心思路
所有题解均基于以下关键观察：  
**每个非边界的 `1` 必须满足右侧或下侧存在 `1` 或边界**。否则，该 `1` 无法被任何炮弹生成（炮弹无法停在无阻挡的位置）。  
- **边界处理**：最后一行和最右一列的 `1` 天然合法（直接由边界阻挡）。
- **条件检查**：遍历所有非边界的 `1`，若其右侧和下侧均为 `0`，则矩阵非法。

#### 解决难点
- **逆向思维**：不模拟炮弹发射过程，而是通过结果矩阵的形态反推合法性。
- **高效验证**：通过线性遍历直接验证条件，避免复杂搜索或动态规划。

---

### 题解评分 (≥4星)

1. **Zhoumy (5星)**  
   - **亮点**：代码极简，直接遍历非边界点，时间复杂度 O(n²)。  
   - **代码片段**：  
     ```cpp
     for(int j=1;j<n;j++) for(int k=1;k<n;k++)
         if(a[j][k]=='1' && a[j][k+1]=='0' && a[j+1][k]=='0') die=1;
     ```

2. **Warriors_Cat (5星)**  
   - **亮点**：通过预处理边界为 `1`，简化条件判断逻辑。  
   - **代码片段**：  
     ```cpp
     for(int i=1;i<=n;i++) a[n+1][i]=1, a[i][n+1]=1;
     if(a[i][j] && !a[i+1][j] && !a[i][j+1]) flag=0;
     ```

3. **Eraine (4星)**  
   - **亮点**：通过数学归纳法思想解释条件正确性，适合教学。  
   - **代码片段**：  
     ```cpp
     for(int i=1;i<n;i++) for(int j=1;j<n;j++)
         if(a[i][j] && !a[i][j+1] && !a[i+1][j]) book=false;
     ```

---

### 最优思路与技巧

1. **关键条件提炼**：将复杂运动规则简化为静态条件判断（右/下方需有阻挡）。
2. **边界预处理**：将矩阵外扩一层虚拟 `1`，避免单独处理最后一行/列。
3. **线性遍历优化**：通过一次遍历完成所有检查，时间复杂度最优。

---

### 同类型题与算法套路

- **通用套路**：  
  - **矩阵合法性检查**：通过特定条件快速验证（如迷宫可达性、数独规则等）。  
  - **逆向思维**：从结果反推生成过程的可行性（如动态规划逆向验证）。  
- **类似题目**：  
  - 洛谷 P1126（机器人路径阻挡条件）  
  - 洛谷 P1141（01 迷宫连通性）  
  - LeetCode 463（岛屿周长：边界条件统计）

---

### 个人心得摘录

- **Zhoumy**：  
  > “因为一个在边界的炮弹一定是合法的，不用判断，所以遍历时只需检查前 `n-1` 行/列。”  
- **mot1ve**：  
  > “最后一行和最后一列的点不用考虑，因为它们靠墙停下来。其他点必须有承接物。”  
- **Eraine**：  
  > “类似数学归纳法，从边界向内递归覆盖，条件满足即可构造合法序列。”

---

### 可视化与算法演示

#### 动画设计
1. **网格绘制**：  
   - 使用 Canvas 绘制 `n×n` 网格，每个单元格显示 `0`/`1`。  
   - 最后一行/列用灰色背景标记边界合法性。  
2. **检查过程**：  
   - 遍历非边界单元格，高亮当前检查的 `1`（红色）。  
   - 若右侧或下侧有 `1`，标记为绿色；若均为 `0`，标记为红色并触发警报音效。  
3. **复古风格**：  
   - 8-bit 音效：合法检查通过时播放短促“滴”声，非法时播放“哔”声。  
   - 像素字体与方格颜色（绿/红/灰）模仿经典游戏风格。  

#### 交互功能
- **步进控制**：允许用户逐单元格观察检查过程。  
- **自动模式**：AI 自动遍历，速度可调（慢/快/极速）。  
- **音效开关**：可关闭背景音乐（8-bit 循环曲）或效果音。  

---

### 推荐题目
1. **洛谷 P1126** - 机器人移动路径阻挡验证。  
2. **洛谷 P1141** - 矩阵连通性检查（BFS/DFS 应用）。  
3. **LeetCode 463** - 岛屿周长统计（边界条件处理）。

---
处理用时：67.56秒