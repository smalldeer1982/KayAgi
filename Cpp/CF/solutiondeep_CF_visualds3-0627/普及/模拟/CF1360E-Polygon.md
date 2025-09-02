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

**算法分类**  
无算法分类（核心为逻辑推理与条件判断）

---

## 题解思路与核心难点

### 核心思路
所有合法矩阵必须满足：**非边界位置**的 `1` 必须满足其右侧或下侧有 `1` 或处于边界。若存在一个非边界的 `1` 其右侧和下侧均为 `0`，则矩阵非法。

### 解决难点
1. **逻辑推导**：通过炮弹飞行规则，逆向推导合法 `1` 的位置条件。
2. **边界处理**：最后一行和最后一列无需检查（边界本身合法）。
3. **高效验证**：只需遍历矩阵一次，时间复杂度为 O(n²)。

### 可视化设计思路
- **网格绘制**：用像素风格绘制 n×n 网格，0/1 用不同颜色填充。
- **动态检查**：高亮当前检查的单元格，标记其右侧和下侧单元格。
- **结果反馈**：若发现非法单元格，播放错误音效并标红；否则继续检查。
- **复古效果**：采用 8-bit 音效（如检查时“滴”声，错误时“哔”声）。

---

## 题解评分（≥4星）

### 1. Zhoumy（★★★★★）
- **亮点**：代码极简，直接遍历非边界点，判断条件仅需 3 行。
- **代码片段**：
  ```cpp
  for(int j=1;j<n;j++) 
    for(int k=1;k<n;k++)
      if(a[j][k]=='1' && a[j][k+1]=='0' && a[j+1][k]=='0') die=1;
  ```

### 2. Warriors_Cat（★★★★☆）
- **亮点**：预处理边界为 `1`，简化条件判断逻辑。
- **代码片段**：
  ```cpp
  for(int i=1; i<=n; i++) a[n+1][i] = 1, a[i][n+1] = 1;
  if(a[i][j] && !a[i+1][j] && !a[i][j+1]) flag=0;
  ```

### 3. rui_er（★★★★☆）
- **亮点**：数学归纳法思想解释条件正确性，代码清晰。
- **代码片段**：
  ```cpp
  for(int i=1; i<n; i++) 
    for(int j=1; j<n; j++)
      if(a[i][j] && !a[i][j+1] && !a[i+1][j]) book=false;
  ```

---

## 最优思路提炼

**关键条件**：每个非边界的 `1` 必须满足右侧或下侧有 `1` 或处于边界。  
**实现技巧**：
- 预处理右/下边界为 `1` 简化判断（如 Warriors_Cat）。
- 仅需遍历前 n-1 行和列，避免冗余检查。

---

## 同类型题与算法套路

### 类似题目特征
- 二维矩阵的合法性验证。
- 动态规划中的前置条件检查（如路径可达性）。

### 推荐题目
1. **洛谷 P1036**：选数（组合验证条件）
2. **洛谷 P1141**：01迷宫（连通性验证）
3. **洛谷 P3395**：路障（动态规划条件判断）

---

## 个人心得摘录

- **Warriors_Cat**：预处理边界为 `1` 可避免循环中的额外判断，代码更简洁。
- **mot1ve**：从炮弹停止条件逆向推导，直接得出核心判断条件。

---

## 可视化与算法演示

### 动画方案
1. **初始化**：绘制 n×n 网格，0 为白色，1 为蓝色。
2. **步进检查**：
   - 高亮当前单元格（黄色）。
   - 标记右侧（绿色）和下侧（绿色）单元格。
   - 若均为 `0`，标红并播放错误音效。
3. **复古风格**：
   - **音效**：检查时“滴”声，错误时“哔”声，成功时 8-bit 胜利音乐。
   - **像素绘制**：用 Canvas 绘制 16×16 像素的单元格，仿 FC 风格。

### 交互设计
- **控制面板**：开始/暂停、步进、重置。
- **自动模式**：以 1秒/步的速度自动遍历所有单元格。

---

**代码片段（JS 可视化核心）**
```javascript
// 绘制复古网格
function drawGrid(matrix) {
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
      ctx.fillStyle = matrix[i][j] ? '#00F' : '#FFF';
      ctx.fillRect(j*16, i*16, 16, 16);
    }
  }
}

// 检查单元格 (i,j)
function checkCell(i, j) {
  highlight(i, j, 'yellow');
  if (matrix[i][j] && (i < n-1 || j < n-1)) {
    if (matrix[i+1][j] === 0 && matrix[i][j+1] === 0) {
      playSound('error');
      highlight(i, j, 'red');
      return false;
    }
  }
  return true;
}
```

---

**总结**：本题通过逆向推导炮弹停止条件，将问题转化为二维矩阵的条件检查，无需复杂算法，核心在于逻辑推理与高效实现。

---
处理用时：71.42秒