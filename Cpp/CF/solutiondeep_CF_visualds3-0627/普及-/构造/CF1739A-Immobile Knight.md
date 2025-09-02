# 题目信息

# Immobile Knight

## 题目描述

There is a chess board of size $ n \times m $ . The rows are numbered from $ 1 $ to $ n $ , the columns are numbered from $ 1 $ to $ m $ .

Let's call a cell isolated if a knight placed in that cell can't move to any other cell on the board. Recall that a chess knight moves two cells in one direction and one cell in a perpendicular direction:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1739A/a0d7d8c62ba0d8d73d58490b8d2222f35ced96b2.png)Find any isolated cell on the board. If there are no such cells, print any cell on the board.

## 说明/提示

In the first testcase, all cells are isolated. A knight can't move from any cell of the board to any other one. Thus, any cell on board is a correct answer.

In the second testcase, there are no isolated cells. On a normal chess board, a knight has at least two moves from any cell. Thus, again, any cell is a correct answer.

In the third testcase, only the middle cell of the board is isolated. The knight can move freely around the border of the board, but can't escape the middle.

## 样例 #1

### 输入

```
3
1 7
8 8
3 3```

### 输出

```
1 7
7 2
2 2```

# AI分析结果



## 算法分类
**构造/数学分析**

---

## 综合分析与结论

### 核心思路与难点
题目要求在棋盘上找到无法移动的"孤立马位"，本质是通过观察棋盘尺寸特征构造解。所有题解的核心思路可归纳为：
1. **行或列为1**：所有位置均为孤立（输出(1,1)）
2. **其他情况**：输出(2,2)（可能并非孤立，但题目允许任意输出）

**关键难点**在于快速判断是否存在孤立位置，而无需暴力遍历。通过数学分析发现：当棋盘尺寸满足某些条件时，孤立位置必定存在且具有固定模式。

### 算法流程可视化设计
1. **棋盘绘制**：根据输入n和m生成对应网格，行列号从1开始。
2. **颜色标记**：
   - 红色高亮：当前选中的输出位置（如(2,2)）
   - 绿色闪烁：若该位置确实为孤立（如3x3的中间格）
3. **动态检测**：展示马的8种跳跃方向，若某方向越界则灰化该箭头。
4. **自动模式**：根据n和m自动选择输出位置，并播放对应音效（成功/普通）。

---

## 题解评分（≥4星）

1. **zhujiangyuan（5星）**  
   - 亮点：详尽分类讨论，覆盖所有边界情况，代码简洁。
   - 代码：直接根据n和m判断，时间复杂度O(1)。

2. **L_zaa_L（4星）**  
   - 亮点：暴力枚举所有格子，确保正确性。
   - 代码：双重循环检查8个方向，时间复杂度O(nm)。

3. **binaryBard（4星）**  
   - 亮点：提出输出棋盘中心点，思路独特。
   - 代码：使用(n+1)/2计算中点，适应部分特殊棋盘。

---

## 最优思路与代码

### 关键技巧
- **尺寸特征法**：通过n和m的尺寸直接判定输出位置，无需计算。
- **统一输出策略**：当存在多个可行解时，选择固定位置（如(2,2)）简化逻辑。

### 核心代码
```cpp
if(n==1 || m==1) cout<<"1 1\n";
else cout<<"2 2\n";
```

### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t,n,m;
    cin>>t;
    while(t--){
        cin>>n>>m;
        if(n==1||m==1) cout<<"1 1\n";
        else cout<<"2 2\n";
    }
    return 0;
}
```

---

## 相似题目推荐
1. **CF1739B** - 数组构造（类似构造性思维）
2. **P1219** 八皇后（棋盘特殊位置构造）
3. **CF1772C** - 等差数列构造（数学分析+构造）

---

## 可视化设计（复古像素版）

### 实现方案
1. **Canvas绘制**：
   - 棋盘网格：16x16像素格子，使用棕褐色调。
   - 马匹动画：8位风格马头图标，跳跃时播放4帧动画。
2. **音效设计**：
   - 选择成功：8-bit上升音阶
   - 无孤立格：短促"哔"声
3. **自动演示**：
   - 根据输入尺寸自动计算输出位置，箭头指示所有可能移动方向。
   - 按空格键单步执行，Enter键自动播放。

### 交互示例
```javascript
// 伪代码示例
function drawBoard(n, m) {
    // 绘制n行m列棋盘
    for(let i=0; i<n; i++) {
        for(let j=0; j<m; j++) {
            // 交替填充棋盘颜色
            ctx.fillStyle = (i+j)%2 ? "#C0A080" : "#E0C090";
            ctx.fillRect(j*16, i*16, 16, 16);
        }
    }
    // 标记输出位置
    let [x,y] = (n==1||m==1) ? [0,0] : [1,1];
    ctx.drawImage(knightImg, y*16, x*16); // 绘制马图标
}
```

---

## 个人心得摘录
- **zhujiangyuan**：通过绘制不同尺寸的棋盘示意图，直观发现输出规律。
- **L_zaa_L**：暴力法虽看似笨拙，但在小数据范围（n,m≤8）中效率足够，且保证正确性。

---
处理用时：110.83秒