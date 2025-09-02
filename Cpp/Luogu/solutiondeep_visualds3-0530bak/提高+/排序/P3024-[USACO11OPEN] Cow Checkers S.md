# 题目信息

# [USACO11OPEN] Cow Checkers S

## 题目描述

One day, Bessie decides to challenge Farmer John to a game of 'Cow Checkers'. The game is played on an M\*N (1 <= M <= 1,000,000; 1 <= N <= 1,000,000) checkerboard that initially contains a single checker piece on the checkboard square coordinates (X, Y) (0 <= X < M; 0 <= Y < N). The bottom leftmost square of the checkerboard has

coordinates (0, 0), and the top rightmost square has coordinates (M-1, N-1). Bessie always moves first, and then the two players alternate turns.  Each turn comprises one of three types of moves:

1) Move the checker piece to any square on the same row to the left of its current position.

2) Move the checker piece to any square on the same column below its current position.

3) Move the checker piece to any spot k squares below and k squares to the left of the current square (where k is any positive integer such that this new spot is still on the checkerboard).

The first player unable to make a move (i.e., because the checker is at (0, 0)) loses. Given that Bessie always goes first, determine who will win the game if both play optimally.

Play and report the winner for T games (1 <= T <= 1,000) reading in a new X,Y starting value for each new game.

有一天，Bessie准备玩一个叫做奶牛跳棋的游戏，来挑战Farmer John。


这个游戏的棋盘大小为 M\*N (1 <= M <= 1,000,000; 1 <= N <= 1,000,000) 。最初棋盘上只有一个棋子在（x,y），棋盘的左下角坐标是（0,0），右上角的坐标是（M-1，N-1）。


每次游戏Bessie都是第一个开始，之后两个人轮流。


每次下棋的时候都有三种走法：


1.向左走任意步


2.向下走任意步


3.向左走k步然后向下走k步（k可随便取值，只要不走出棋盘）


首先走到（0,0）的人为胜利者。


游戏共有T次，每次都会给出一个新的坐标（x,y），请输出每一轮赢家的名字。


## 说明/提示

Farmer John and Bessie are playing one game on a 3\*3 checkerboard with the checker piece initially at (1, 1) (i.e. at the center of the board).


Bessie initially can only move the checker piece to either (1, 0) or (0, 1), or (0, 0). Bessie can immediately win by moving the piece to (0, 0).


起点在（1,1），一开始有三种选择（1,0）,（0,1），（0,0）只要Bessie在开始时将棋子移到（1,0）或（0,1），就必胜无疑。


感谢@ 2014nhc  提供的翻译


## 样例 #1

### 输入

```
3 3 
1 
1 1 
```

### 输出

```
Bessie 
```

# AI分析结果



## 唯一算法分类
**威佐夫博弈**

---

## 综合分析与结论
### 核心思路与难点
1. **模型转换**：将棋盘坐标 (x,y) 转化为威佐夫博弈中的两堆石子模型，三种移动方式对应三种取石子操作。
2. **必败态判定**：根据威佐夫博弈结论，当坐标满足 $\frac{\sqrt{5}+1}{2} \cdot (y-x) = x$（假设 x ≤ y）时为必败态，此时先手必输。
3. **实现方式**：两种主流解法：
   - **数学公式法**：直接通过黄金分割比计算必败态。
   - **预处理法**：构造必败点序列，通过对称性生成二维坐标系中的必败点。

### 可视化设计思路
- **棋盘渲染**：用 Canvas 绘制棋盘，必败点用红色标记，必胜点用蓝色标记。
- **动态高亮**：用户输入坐标后，高亮该点并显示胜负结果。
- **预处理动画**：展示如何逐行生成必败点，通过颜色渐变表示填充过程。
- **音效触发**：正确判定时播放 8-bit 胜利音效，错误时播放低沉音效。
- **复古风格**：采用 16 色像素调色板，棋盘网格线用浅灰色，控制面板仿 FC 手柄按键。

---

## 题解清单 (评分≥4星)
1. **Water_Cows（5⭐️）**  
   - 亮点：直观的预处理数组法，完美避开浮点精度问题，代码可读性极强。
   - 关键代码片段：
     ```cpp
     for(int k=0, i=1; i<=1e6; i++)
         if(!f[i]) f[i] = i + (++k), f[f[i]] = i;
     ```

2. **yaoyuchen2021（4⭐️）**  
   - 亮点：感性证明预处理正确性，数组命名清晰易懂。
   - 关键注释：`j表示横纵坐标差`，直接点破预处理核心逻辑。

3. **xiwang（4⭐️）**  
   - 亮点：直接调用威佐夫定理，代码极简。
   - 注意点：浮点计算可能存在精度风险，但实际测试可通过。

---

## 最优思路代码实现
### 预处理法（推荐）
```cpp
#include <iostream>
using namespace std;
const int N = 2e6 + 7; // 两倍空间防止越界

int f[N]; // f[x]记录x行对应的必败点y坐标

void init() {
    for(int k=0, i=1; i<=1e6; ++i) {
        if(!f[i]) {
            f[i] = i + (++k);  // 生成当前行的必败点
            f[f[i]] = i;       // 对称点标记
        }
    }
}

int main() {
    init();
    int T, x, y;
    cin >> T; // 实际题目中M,N无意义
    while(T--) {
        cin >> x >> y;
        cout << (f[x] == y ? "Farmer John\n" : "Bessie\n");
    }
    return 0;
}
```

---

## 相似题目推荐
1. **P2252 [SHOI2002]取石子游戏**  
   - 威佐夫博弈模板题，直接应用黄金分割比。

2. **P1245 取石子游戏**  
   - 扩展威佐夫博弈，引入多堆石子规则。

3. **P2548 [AHOI2004]智能探险车**  
   - 博弈论与动态规划结合，需要预处理胜负状态。

---

## 可视化核心逻辑（伪代码）
```javascript
// Canvas初始化
const canvas = document.getElementById('board');
const ctx = canvas.getContext('2d');
const CELL_SIZE = 20;

function drawBoard() {
    // 绘制棋盘网格
    for(let x=0; x<M; x++) {
        for(let y=0; y<N; y++) {
            ctx.fillStyle = isLosing(x,y) ? '#FF4444' : '#44AAFF';
            ctx.fillRect(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }
    }
}

// 预处理动画
let k = 0, i = 1;
function animatePreprocess() {
    if(i > 1e6) return;
    if(!f[i]) {
        f[i] = i + (++k);
        f[f[i]] = i;
        // 高亮当前处理的i和f[i]
    }
    i++;
    requestAnimationFrame(animatePreprocess);
}
```

---

## 复古音效设计
- **胜利音效**：8-bit 短促上升音阶（频率 523Hz → 784Hz）
- **失败音效**：低频脉冲波（频率 220Hz，持续 200ms）
- **点击反馈**：经典 FC 按钮按压声效

---
处理用时：63.66秒