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



### 综合分析与结论

该题目为威佐夫博弈的变种，核心在于识别必败点（先手无法必胜的位置）。各题解主要采用两种思路：  
1. **数学推导（威佐夫博弈）**：利用贝蒂定理和黄金分割比公式直接判断必败点。  
2. **打表找规律**：通过观察必败点的横纵坐标差呈等差递增，预处理数组存储映射关系。  

**贪心策略与难点**：  
- 必败点的确定需满足无法通过一步操作到达其他必败点，类似贪心的“最优子结构”。  
- 关键难点在于发现必败点的对称性和差值规律，或理解威佐夫博弈的数学推导。

**可视化设计思路**：  
1. **棋盘绘制**：以网格展示必败点（红色）和必胜点（蓝色），动态标记用户输入的坐标。  
2. **黄金分割动画**：通过滑动条调整坐标差值，实时计算并高亮符合公式的必败点。  
3. **像素风格交互**：8-bit 音效提示胜负结果，自动演示必败点生成过程（如逐行填充）。

---

### 题解清单（≥4星）

1. **Water_Cows（4.5星）**  
   - **亮点**：通过画图找规律，代码直观易实现，适合无博弈论背景的选手。  
   - **心得**：“发现等差数列规律后预处理数组，避免复杂数学推导。”

2. **xiwang（4星）**  
   - **亮点**：直接应用威佐夫博弈公式，代码简洁高效。  
   - **不足**：缺乏对公式的详细解释，新手可能难以理解。

3. **yaoyuchen2021（4星）**  
   - **亮点**：感性证明打表正确性，预处理逻辑清晰。  
   - **心得**：“每行每列仅有一个必败点，对称性简化计算。”

---

### 最优思路提炼

**威佐夫博弈公式法**：  
- **公式**：若 `(y - x) * (sqrt(5) + 1) / 2 ≈ x`，则 `(x, y)` 为必败点。  
- **代码实现**：  
  ```cpp
  bool is_losing(int x, int y) {
      if (x > y) swap(x, y);
      int k = (int)((y - x) * (1 + sqrt(5)) / 2);
      return k == x;
  }
  ```

**预处理数组法**：  
- **核心逻辑**：按差值递增生成必败点，记录横纵坐标映射。  
  ```cpp
  int f[MAXN * 2];
  void preprocess() {
      for (int k = 0, i = 1; i <= 1e6; i++) {
          if (!f[i]) {
              f[i] = i + (++k);
              f[f[i]] = i;
          }
      }
  }
  ```

---

### 同类型题与算法套路

**常见套路**：  
- **威佐夫博弈**：两堆石子操作问题，必败点与黄金分割比相关。  
- **打表找规律**：适用于大数范围且存在数学规律的博弈问题。

**推荐题目**：  
1. [P1247] 取石子游戏（威佐夫博弈裸题）  
2. [P2252] 取石子游戏（进阶威佐夫变种）  
3. [P1199] 三国游戏（贪心策略与博弈结合）

---

### 复古游戏化动画设计

**实现方案**：  
1. **像素棋盘**：Canvas 绘制网格，必败点用红色方块闪烁。  
2. **音效设计**：  
   - **正确选择**：8-bit 上升音效。  
   - **错误选择**：短促“哔”声。  
3. **自动演示**：AI 按差值递增生成必败点，逐帧动画展示。  
4. **关卡积分**：用户输入坐标后，正确判断得10分，错误扣5分。

**代码片段（JS）**：  
```javascript
// 绘制必败点
function drawLosingPoints(ctx) {
    for (let x = 0; x < maxX; x++) {
        const y = f[x];
        ctx.fillStyle = '#FF0000';
        ctx.fillRect(x * gridSize, y * gridSize, gridSize, gridSize);
    }
}
// 音效触发
function playSound(success) {
    const audio = new Audio(success ? 'correct.wav' : 'wrong.wav');
    audio.play();
}
```

---

### 个人心得摘录

- **调试教训**：“预处理数组大小需开双倍，避免越界。”  
- **思维突破**：“必败点的对称性大幅简化问题，转化为单向生成。”  
- **优化技巧**：“黄金分割公式避免预处理，适合超大范围查询。”

---

### 可视化与算法演示

**核心贪心过程动画**：  
1. **初始化棋盘**：绘制空棋盘，标记 (0,0) 为红色。  
2. **逐行生成**：从左到右扫描，若当前位置未标记，则生成必败点并对称标记。  
3. **用户交互**：点击坐标显示胜负结果，播放对应音效。  
4. **自动模式**：AI 模拟生成过程，高亮当前操作的行和生成的必败点。

**交互控制面板**：  
- **速度调节**：滑动条控制生成速度（100ms~1s）。  
- **模式切换**：手动点击 vs 自动播放。  
- **重置/暂停**：随时重置棋盘或暂停动画。

---
处理用时：82.07秒