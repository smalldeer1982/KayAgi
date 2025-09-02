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

**算法分类**：其他搜索  

---

### **题解思路与算法要点**  
1. **核心思路**：  
   - 每个非边界的 `1` 必须满足右侧或下侧至少有一个 `1`（或边界）。否则，该 `1` 无法由任何炮弹生成，因为炮弹的飞行路径必须被提前存在的 `1` 或边界阻挡。  
   - **关键条件**：对矩阵中所有非右下边界的点 `(i,j)`（即 `i < n` 且 `j < n`），若 `a[i][j] == 1`，则需检查 `a[i+1][j]` 或 `a[i][j+1]` 是否为 `1`。若存在不满足条件的点，则矩阵非法。  

2. **解决难点**：  
   - 发现每个 `1` 的生成必须依赖右侧或下侧的阻挡条件。  
   - 边界（最后一行和最后一列）无需检查，因为它们的 `1` 可以直接由对应方向的炮弹生成。  

---

### **题解评分 (≥4星)**  
1. **Zhoumy (5星)**  
   - 思路清晰，代码极简，直接遍历检查条件。  
   - 代码仅需双重循环，时间复杂度 `O(n²)`，无冗余操作。  

2. **Warriors_Cat (5星)**  
   - 使用预处理填充虚拟边界，代码逻辑明确。  
   - 检查条件时巧妙处理边界，避免越界问题。  

3. **rui_er (4星)**  
   - 逆向分析，从边界反向推导合法条件。  
   - 代码简洁，仅需一次遍历即可判断。  

---

### **最优思路提炼**  
- **条件判断法**：遍历所有非边界的 `1`，若其右侧和下侧均为 `0`，则矩阵非法。  
- **无需显式搜索**：通过观察规律直接验证条件，无需模拟炮弹发射过程，极大优化时间复杂度。  

---

### **同类型题与算法套路**  
- **矩阵合法性检查**：类似问题需验证矩阵中元素是否满足某种局部条件（如依赖相邻元素的特定关系）。  
- **贪心策略**：通过局部条件推导全局合法性，避免复杂模拟。  

---

### **推荐题目**  
1. **P1083 [NOIP2012 提高组] 借教室**（区间覆盖与条件检查）  
2. **P1219 [USACO1.5] 八皇后 Checker Challenge**（矩阵条件验证）  
3. **P2895 [USACO08FEB] Meteor Shower S**（BFS 与动态条件判断）  

---

### **个人心得摘录**  
> “发现每个 `1` 的右侧或下侧必须有一个阻挡物，否则无法生成。边界条件无需检查，因为它们天然由炮台位置决定。” —— rui_er  

---

### **可视化与算法演示**  
1. **动画设计**：  
   - **像素网格**：将矩阵绘制为 `n×n` 的像素网格，初始为灰色。  
   - **遍历检查**：逐个检查非边界点，若 `1` 的右侧和下侧均为 `0`，标记为红色并停止动画；否则标记为绿色。  
   - **音效提示**：发现非法点时播放“失败”音效，合法流程播放轻快音效。  

2. **复古风格**：  
   - **8位像素风**：使用 16 色调色板，矩阵点显示为 8×8 像素方块。  
   - **自动演示模式**：逐行扫描矩阵，高亮当前检查点，动态显示条件判断过程。  

---

### **核心代码实现**  
```cpp
#include <iostream>
using namespace std;

int main() {
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        char a[55][55];
        bool valid = true;
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                cin >> a[i][j];
        
        for (int i = 0; i < n-1; i++) 
            for (int j = 0; j < n-1; j++) 
                if (a[i][j] == '1' && a[i+1][j] == '0' && a[i][j+1] == '0') 
                    valid = false;
        
        cout << (valid ? "YES" : "NO") << endl;
    }
    return 0;
}
```

---

**可视化代码片段（伪代码）**  
```javascript
// 在 Canvas 上绘制矩阵并检查条件
function checkMatrix() {
    for (let i = 0; i < n-1; i++) {
        for (let j = 0; j < n-1; j++) {
            highlightCell(i, j); // 高亮当前检查点
            if (matrix[i][j] === 1 && matrix[i+1][j] === 0 && matrix[i][j+1] === 0) {
                playSound("error"); // 播放错误音效
                return false;
            }
        }
    }
    playSound("success"); // 播放成功音效
    return true;
}
```

---
处理用时：85.66秒