# 题目信息

# Grid Game 2

## 题目描述

You are playing "Grid Game 2" with your friend. There is a grid with $ 10^9 $ rows (numbered from $ 1 $ to $ 10^9 $ ) and $ 10^9 $ columns (numbered from $ 1 $ to $ 10^9 $ ). The cell at row $ r $ and column $ c $ is denoted as $ (r, c) $ .

Each cell can have a colour of either black or white. Initially, there are exactly $ N $ black cells (numbered from $ 1 $ to $ N $ ). Black cell $ i $ is located at $ (R_i, C_i) $ . The rest of the cells are white.

You and your friend will alternately take turn playing on this grid, and you are playing in the first turn. In one turn, a player will choose a black cell $ (r, c) $ , then toggle cells $ (r - x, c - y) $ for all $ 0 \leq x, y < \min(r, c) $ . If a cell is toggled, then the cell becomes black if it was a white cell, and the cell becomes white if it was a black cell.

For example, the following illustration shows how the grid changes after a player chooses a black cell $ (5, 4) $ in their turn.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/e2fd54c73d9615e1033b8dd1a01d70086e6fa600.png)A player who is unable to play on their turn, i.e. no remaining black cells, loses the game, and the opposing player wins the game. If you and your friend are playing optimally, determine who will win the game.

## 说明/提示

Explanation for the sample input/output #1

You can start your move by choosing $ (2, 4) $ , whose effect was demonstrated in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/2b04f438065762fd04c672bc2aeca49fdf0ed64a.png)The remaining black cells are $ (1, 3) $ and $ (1, 4) $ , each of which will only toggle itself when chosen. Whichever your friend chooses on the next move, the you can choose the remaining black cell.

Explanation for the sample input/output #2

You have only one cell to choose, and will toggle cells $ (1, 1) $ , $ (1, 2) $ , $ (2, 1) $ , and $ (2, 2) $ . Your friend and you will alternately choose the remaining black cells with your friend choosing the last black cell.

## 样例 #1

### 输入

```
2
2 3
2 4```

### 输出

```
FIRST```

## 样例 #2

### 输入

```
1
2 2```

### 输出

```
SECOND```

## 样例 #3

### 输入

```
13
1 1
1 4
1 5
2 1
2 4
2 5
4 1
4 2
4 4
5 1
5 2
5 4
5 5```

### 输出

```
SECOND```

# AI分析结果



**唯一算法分类**：博弈论（SG函数与异或游戏）

---

### **题解思路与核心难点**

1. **关键思路**  
   - **SG函数转化**：每个点的胜负状态可转化为类似最大公约数的递归计算，通过坐标的辗转相除与奇偶性判断快速求解。  
   - **异或性质**：所有点的SG值异或总和决定胜负，若总和非零则先手必胜。  
   - **二维差分优化**：通过四次递归调用（如`sol(x,y)`、`sol(x-1,y-1)`等）简化二维区域的影响计算。

2. **解决难点**  
   - **大数处理**：直接计算每个点的SG函数对$10^9$规模不可行，需通过数学推导找到递推规律。  
   - **递归简化**：利用类似欧几里得算法的辗转相除，将问题分解为更小的子问题，每次处理奇偶性决定是否异或1。

---

### **最优思路与技巧提炼**

- **核心公式**  
  对坐标$(x,y)$，其SG值为四次递归调用的异或：  
  ```text
  SG(x,y) = sol(x,y) ^ sol(x-1,y) ^ sol(x,y-1) ^ sol(x-1,y-1)
  ```
  其中`sol(x,y)`的递归逻辑为：  
  ```cpp
  void sol(int x, int y) {
    while (x && y) {
        if (x > y) swap(x, y);
        y %= (x + x);           // 对2x取模
        if (y >= x) ans ^= 1, y -= x; // 奇数次段则异或1
    }
  }
  ```

- **技巧总结**  
  - **辗转相除优化**：通过取模和奇偶判断，将问题规模快速缩小。  
  - **异或差分**：利用四次调用的异或抵消冗余计算，避免直接处理二维区域。

---

### **题解评分（≥4星）**

1. **EnofTaiPeople（5星）**  
   - 代码简洁高效，直接通过循环处理避免了递归栈溢出。  
   - 利用数学规律快速推导，适合大规模数据。

2. **Mars_Dingdang（4星）**  
   - 详细推导SG函数与二维前缀和的关系，逻辑清晰。  
   - 提供递推公式，便于理解数学本质。

3. **封禁用户（4星）**  
   - 代码极简，递归函数直观体现辗转相除思想。  
   - 快速处理边界条件，适合竞赛场景。

---

### **可视化与算法演示**

1. **动画设计**  
   - **坐标变换**：用网格动态展示$(x,y)$逐步缩小到$(x', y')$的过程，高亮当前操作区域。  
   - **异或标记**：每次取模或减法时，若异或1，显示红色闪烁提示。  
   - **胜负结果**：最终异或结果以像素火焰特效呈现（非零为胜利动画）。

2. **复古风格实现**  
   - **像素网格**：使用16色像素画风，每个格子表示为8x8像素块。  
   - **音效触发**：  
     - 坐标更新时播放“哔”声（8-bit音效）。  
     - 异或操作时播放“叮”声，胜负结果播放胜利/失败旋律。

3. **交互功能**  
   - **步进控制**：允许单步执行循环，观察模运算细节。  
   - **自动演示**：AI模式自动运行算法，速度可调（1x~10x）。

---

### **同类型题推荐**

1. **洛谷 P2580**（博弈论+SG函数）  
2. **洛谷 P3182**（Nim游戏变种）  
3. **洛谷 P2148**（二维棋盘博弈）

---

### **代码实现（核心逻辑）**

```cpp
int ans;
void sol(int x, int y) {
    while (x && y) {
        if (x > y) swap(x, y);
        y %= (x + x);
        if (y >= x) ans ^= 1, y -= x;
    }
}
// 主函数中对每个坐标调用四次
sol(r, c);
sol(r-1, c-1);
sol(r-1, c);
sol(r, c-1);
```

---

### **个人心得摘录**

- **EnofTaiPeople**：  
  “打表无规律后转向数学推导，发现递推式类似gcd，直接递归可破。”  
- **封禁用户**：  
  “独立想出时意识到SG函数的分形性质，辗转相除是唯一出路。”

---

### **总结**

通过数学建模将博弈问题转化为递归计算，结合异或性质和辗转相除法，是处理大规模坐标问题的核心技巧。

---
处理用时：93.82秒