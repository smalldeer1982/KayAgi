# 题目信息

# Kalevitch and Chess

## 题目描述

A famous Berland's painter Kalevitch likes to shock the public. One of his last obsessions is chess. For more than a thousand years people have been playing this old game on uninteresting, monotonous boards. Kalevitch decided to put an end to this tradition and to introduce a new attitude to chessboards.

As before, the chessboard is a square-checkered board with the squares arranged in a $ 8×8 $ grid, each square is painted black or white. Kalevitch suggests that chessboards should be painted in the following manner: there should be chosen a horizontal or a vertical line of 8 squares (i.e. a row or a column), and painted black. Initially the whole chessboard is white, and it can be painted in the above described way one or more times. It is allowed to paint a square many times, but after the first time it does not change its colour any more and remains black. Kalevitch paints chessboards neatly, and it is impossible to judge by an individual square if it was painted with a vertical or a horizontal stroke.

Kalevitch hopes that such chessboards will gain popularity, and he will be commissioned to paint chessboards, which will help him ensure a comfortable old age. The clients will inform him what chessboard they want to have, and the painter will paint a white chessboard meeting the client's requirements.

It goes without saying that in such business one should economize on everything — for each commission he wants to know the minimum amount of strokes that he has to paint to fulfill the client's needs. You are asked to help Kalevitch with this task.

## 样例 #1

### 输入

```
WWWBWWBW
BBBBBBBB
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
```

### 输出

```
3
```

## 样例 #2

### 输入

```
WWWWWWWW
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
```

### 输出

```
1
```

# AI分析结果



## 唯一算法分类  
**贪心算法**

## 题解思路与核心难点  
**核心思路**：统计所有全黑的行数和列数之和，特判全棋盘全黑的情况。  
**算法流程**：  
1. 遍历每一行，统计完全由 `B` 组成的行数（`row_count`）  
2. 遍历每一列，统计完全由 `B` 组成的列数（`col_count`）  
3. 若 `row_count + col_count == 16`（全棋盘全黑），则取最小值 `8`  
4. 否则，结果为 `row_count + col_count`  

**解决难点**：  
- **覆盖逻辑**：未被全黑行覆盖的格子必须被全黑列覆盖，反之亦然。  
- **特判全黑棋盘**：当 8 行和 8 列均被统计时，实际只需涂 8 次行或列。  

## 题解评分（≥4星）  
1. **Tune_ 的题解（4.5星）**  
   - 思路清晰，直接统计全黑行/列  
   - 代码简洁，包含特判逻辑  
   - 未优化遍历，但时间复杂度低（8×8 数据规模）  

2. **呵呵侠 的题解（4星）**  
   - 与 Tune_ 思路一致，代码结构类似  
   - 变量命名更规范（如 `flag` 替代 `f`）  
   - 注释详细，适合新手理解  

3. **_Legacy 的题解（4星）**  
   - 正确实现核心逻辑  
   - 输入处理部分稍有不同（逐行读取字符串）  
   - 代码风格简洁，但变量命名可优化（如 `t` 改为 `is_col_all_B`）  

## 最优思路与技巧提炼  
1. **贪心选择全黑行/列**：优先涂全黑的行或列，每次操作覆盖最多格子。  
2. **特判全黑棋盘**：当同时满足 8 行和 8 列全黑时，结果取 8。  
3. **覆盖验证**：无需验证非全黑行/列的覆盖情况，隐含条件保证合法性。  

## 同类型题与算法套路  
- **覆盖问题**：通过最少的行/列操作覆盖所有目标点。  
- **贪心选择局部最优**：如选择能覆盖最多未覆盖区域的行或列。  

## 推荐相似题目  
1. [P3384 覆盖模型](https://www.luogu.com.cn/problem/P3384)  
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)（覆盖与回溯思想）  
3. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（贪心策略应用）  

## 个人心得摘录  
> “特判全黑棋盘时，最初可能会忽略 `row_count + col_count == 16` 的情况，导致结果错误。需注意题目隐含的全覆盖条件。”  

## 可视化与算法演示  
### 算法步骤动画设计  
1. **棋盘绘制**：在 Canvas 中绘制 8×8 网格，初始全白。  
2. **遍历行/列**：  
   - 高亮当前遍历的行或列，检查是否全黑。  
   - 若全黑，标记该行/列为红色，并播放“涂色”音效。  
3. **计数更新**：实时显示 `row_count` 和 `col_count` 的数值。  
4. **特判处理**：若最终结果为 16，替换为 8 并触发“胜利”音效。  

### 复古像素风格设计  
- **颜色方案**：使用 8 位色调色板（如黑色 `#000000`，白色 `#FFFFFF`，红色 `#FF0000`）。  
- **音效设计**：  
  - 涂色操作：8-bit “哔”声（Web Audio API 生成）。  
  - 特判触发：经典 FC 过关音效。  
- **自动演示模式**：按固定间隔逐步遍历行和列，模拟 AI 决策。  

### 关键代码片段（JavaScript）  
```javascript  
// 绘制棋盘  
function drawBoard(ctx, board) {  
  for (let i = 0; i < 8; i++) {  
    for (let j = 0; j < 8; j++) {  
      ctx.fillStyle = board[i][j] === 'B' ? '#000' : '#FFF';  
      ctx.fillRect(j * 20, i * 20, 18, 18);  
    }  
  }  
}  

// 自动演示核心逻辑  
function autoSolve() {  
  let rowCount = 0, colCount = 0;  
  // 遍历行...  
  // 遍历列...  
  if (rowCount + colCount === 16) result = 8;  
}  
```  

---

## 正确题解代码  
```cpp  
#include<bits/stdc++.h>  
using namespace std;  
char a[8][8];  

int main() {  
    for(int i=0; i<8; i++)  
        for(int j=0; j<8; j++)  
            cin >> a[i][j];  
    int ans = 0;  

    // 统计全黑行  
    for(int i=0; i<8; i++) {  
        bool isRowAllB = true;  
        for(int j=0; j<8; j++) {  
            if(a[i][j] != 'B') {  
                isRowAllB = false;  
                break;  
            }  
        }  
        if(isRowAllB) ans++;  
    }  

    // 统计全黑列  
    for(int i=0; i<8; i++) {  
        bool isColAllB = true;  
        for(int j=0; j<8; j++) {  
            if(a[j][i] != 'B') {  
                isColAllB = false;  
                break;  
            }  
        }  
        if(isColAllB) ans++;  
    }  

    // 特判全棋盘全黑  
    if(ans == 16) ans = 8;  
    cout << ans;  
    return 0;  
}  
```

---
处理用时：239.92秒