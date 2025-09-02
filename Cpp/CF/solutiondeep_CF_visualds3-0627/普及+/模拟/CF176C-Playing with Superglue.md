# 题目信息

# Playing with Superglue

## 题目描述

Two players play a game. The game is played on a rectangular board with $ n×m $ squares. At the beginning of the game two different squares of the board have two chips. The first player's goal is to shift the chips to the same square. The second player aims to stop the first one with a tube of superglue.

We'll describe the rules of the game in more detail.

The players move in turns. The first player begins.

With every move the first player chooses one of his unglued chips, and shifts it one square to the left, to the right, up or down. It is not allowed to move a chip beyond the board edge. At the beginning of a turn some squares of the board may be covered with a glue. The first player can move the chip to such square, in this case the chip gets tightly glued and cannot move any longer.

At each move the second player selects one of the free squares (which do not contain a chip or a glue) and covers it with superglue. The glue dries long and squares covered with it remain sticky up to the end of the game.

If, after some move of the first player both chips are in the same square, then the first player wins. If the first player cannot make a move (both of his chips are glued), then the second player wins. Note that the situation where the second player cannot make a move is impossible — he can always spread the glue on the square from which the first player has just moved the chip.

We will further clarify the case where both chips are glued and are in the same square. In this case the first player wins as the game ends as soon as both chips are in the same square, and the condition of the loss (the inability to move) does not arise.

You know the board sizes and the positions of the two chips on it. At the beginning of the game all board squares are glue-free. Find out who wins if the players play optimally.

## 样例 #1

### 输入

```
1 6 1 2 1 6
```

### 输出

```
First```

## 样例 #2

### 输入

```
6 5 4 3 2 1
```

### 输出

```
First```

## 样例 #3

### 输入

```
10 10 1 1 10 10
```

### 输出

```
Second```

# AI分析结果



1. **唯一算法分类**  
   博弈论/必胜态分析

2. **综合分析与结论**  
   该题的核心在于通过坐标差的几何关系判断必胜态。关键观察点是：当两棋子的最大坐标差超过4，或等于4且另一坐标差为3时，第二位玩家有必胜策略。其他情况第一位玩家必胜。  
   **核心算法流程**：  
   - 计算横向距离 `dx=abs(x1-x2)` 与纵向距离 `dy=abs(y1-y2)`  
   - 交换两值使得 `dx≥dy`  
   - 若 `dx>4` 或 `dx=4且dy=3`，第二位玩家胜；否则第一位胜  

   **可视化设计**：  
   - 使用 Canvas 绘制棋盘，棋子用圆形表示，胶水用叉号标记  
   - 关键步骤高亮：移动路径上被胶水封锁的位置用红色标记  
   - 动画展示：  
     - 每一步移动后，胶水涂布位置闪烁提示  
     - 最终合并成功或胶水封锁时，播放对应音效  

3. **题解清单 (≥4星)**  
   - **hongshixiaobai (4星)**：准确提炼出坐标差临界条件，代码简洁。  
   - **MsgNotFound (3星)**：条件描述存在错误，但代码框架正确。  
   - 其余题解因条件判断错误不达4星  

4. **最优思路代码片段**  
   ```cpp
   int d0 = abs(x0 - x1), d1 = abs(y0 - y1);
   if (d0 < d1) swap(d0, d1);
   if (d0 >4 || (d0 ==4 && d1 ==3)) cout << "Second";
   else cout << "First";
   ```

5. **同类型题目推荐**  
   - 洛谷 P1516（青蛙的约会）：距离与模数的博弈分析  
   - 洛谷 P1857（取石子游戏）：简单必胜态判断  
   - 洛谷 P3182（棋子移动）：路径封锁策略  

6. **可视化与复古动画实现思路**  
   - **像素风格**：使用 16 色调色板，棋盘网格用深灰色，棋子用蓝/绿色，胶水用红色叉号  
   - **音效设计**：  
     - 移动时播放 "beep" 音效  
     - 胶水涂布时播放 "click" 音效  
     - 胜利时播放 8-bit 胜利旋律  
   - **AI 演示**：自动模拟双方最优策略，单步执行时可观察胶水封锁逻辑  

---

**答案**
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, x1, y1, x2, y2;
    cin >> n >> m >> x1 >> y1 >> x2 >> y2;
    int dx = abs(x1 - x2), dy = abs(y1 - y2);
    if (dx < dy) swap(dx, dy);
    if (dx > 4 || (dx == 4 && dy == 3)) cout << "Second";
    else cout << "First";
    return 0;
}
```

---
处理用时：195.76秒