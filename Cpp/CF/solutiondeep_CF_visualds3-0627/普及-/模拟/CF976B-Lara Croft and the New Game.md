# 题目信息

# Lara Croft and the New Game

## 题目描述

You might have heard about the next game in Lara Croft series coming out this year. You also might have watched its trailer. Though you definitely missed the main idea about its plot, so let me lift the veil of secrecy.

Lara is going to explore yet another dangerous dungeon. Game designers decided to use good old 2D environment. The dungeon can be represented as a rectangle matrix of $ n $ rows and $ m $ columns. Cell $ (x,y) $ is the cell in the $ x $ -th row in the $ y $ -th column. Lara can move between the neighbouring by side cells in all four directions.

Moreover, she has even chosen the path for herself to avoid all the traps. She enters the dungeon in cell $ (1,1) $ , that is top left corner of the matrix. Then she goes down all the way to cell $ (n,1) $ — the bottom left corner. Then she starts moving in the snake fashion — all the way to the right, one cell up, then to the left to the cell in $ 2 $ -nd column, one cell up. She moves until she runs out of non-visited cells. $ n $ and $ m $ given are such that she always end up in cell $ (1,2) $ .

Lara has already moved to a neighbouring cell $ k $ times. Can you determine her current position?

## 说明/提示

Here is her path on matrix $ 4 $ by $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF976B/1b2df8f31f927201c078b0cd1ef3dccbc8991311.png)

## 样例 #1

### 输入

```
4 3 0
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
4 3 11
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
4 3 7
```

### 输出

```
3 2
```

# AI分析结果



**唯一算法分类**：数学模拟/规律推导

---

### 题解思路与核心难点

1. **路径分段处理**  
   - **第一部分**：垂直向下移动到左下角 `(n,1)`，共 `n-1` 步。若 `k < n`，直接返回 `(k+1,1)`。
   - **第二部分**：蛇形移动，以每行 `m-1` 步的方式从 `(n,2)` 走到 `(1,2)`。关键难点在于如何通过数学计算快速定位到当前行和列。

2. **数学推导关键点**  
   - 剩余步数 `k1 = k - (n-1)`，计算行数 `row = n - (k1 // (m-1))`。
   - **列方向判断**：根据 `(k1 // (m-1))` 的奇偶性决定当前行是向右（偶数列）还是向左（奇数列）走。
     - 偶数行（向右）：列号为 `k1 % (m-1) + 2`。
     - 奇数行（向左）：列号为 `m - (k1 % (m-1))`。

3. **解决难点**  
   - **边界处理**：如 `k` 刚好为 `n-1` 时需停留在 `(n,1)`。
   - **大数运算**：由于 `n` 和 `m` 可达 `1e9`，需使用长整型避免溢出。

---

### 题解评分（≥4星）

1. **wwwidk1234（5星）**  
   - 思路清晰，详细推导分阶段逻辑，代码简洁且注释明确，处理边界完整。

2. **GordonLu（4星）**  
   - 代码极简，直接体现核心公式，但缺乏详细解释，适合有经验的读者。

3. **Yizhixiaoyun（4星）**  
   - 代码简短且高效，特判处理干净，但对奇偶性判断的解释较简略。

---

### 最优思路提炼

- **分段处理**：将路径拆分为垂直和蛇形两阶段，减少计算复杂度。
- **行列快速计算**：通过商（确定行方向）和余数（确定列位置）的数学关系直接推导坐标，避免逐格模拟。
- **奇偶性判断方向**：利用商的奇偶性切换列递增/递减模式，统一处理所有情况。

---

### 同类型题与算法套路

- **类似问题**：螺旋矩阵、蛇形填数、Z 字形变换。
- **通用套路**：将复杂路径分解为可数学描述的规律，通过分块和模运算快速定位。

---

### 推荐题目

1. **P5731 蛇形方阵**（模拟蛇形填数）
2. **P2239 螺旋矩阵**（数学推导螺旋位置）
3. **CF1175B（CodeForces 螺旋遍历）**

---

### 个人心得摘录

- **KEBrantily**：思考两小时，写码两分钟。强调规律发现的重要性。
- **EternalAlexander**：调试时发现 `%d` 读取 `long long` 的错误，提醒注意数据类型匹配。

---

### 可视化与算法演示设计

1. **像素动画效果**  
   - **路径绘制**：以 8-bit 风格绘制矩阵，Lara 的移动轨迹用高亮像素块表示。
   - **方向箭头**：蛇形阶段每行切换方向时显示箭头动画，对应奇偶行方向。
   - **变量跟踪**：实时显示当前计算的 `k1`、商、余数及对应的行列变化公式。

2. **交互功能**  
   - **步进控制**：允许单步执行，观察每个公式计算后的坐标变化。
   - **音效提示**：移动时播放经典 FC 音效，错误输入时触发“失败”音效。

3. **代码演示片段**  
   ```javascript
   // 计算核心逻辑（伪代码）
   function calculatePosition(n, m, k) {
       if (k < n) return {x: k+1, y: 1};
       let k1 = k - n;
       let quotient = Math.floor(k1 / (m-1));
       let remainder = k1 % (m-1);
       let x = n - quotient;
       let y = (quotient % 2 === 0) ? (remainder + 2) : (m - remainder);
       return {x, y};
   }
   ```

---

### 核心代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    long long n, m, k;
    cin >> n >> m >> k;
    if (k < n) {
        cout << k+1 << " 1";
        return 0;
    }
    long long k1 = k - n;
    long long row = n - k1 / (m-1);
    long long col = ( (k1/(m-1)) % 2 ) ? (m - k1 % (m-1)) : (k1 % (m-1) + 2);
    cout << row << " " << col;
    return 0;
}
```

---

**总结**：通过数学规律将路径分段处理，结合商和余数的奇偶性快速定位坐标，是解决此类大规模模拟问题的关键技巧。

---
处理用时：119.66秒