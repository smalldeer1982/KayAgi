# 题目信息

# Bishwock

## 题目描述

Bishwock is a chess figure that consists of three squares resembling an "L-bar". This figure can be rotated by 90, 180 and 270 degrees so it can have four possible states:

```
XX   XX   .X   X.
X.   .X   XX   XX
```

Bishwocks don't attack any squares and can even occupy on the adjacent squares as long as they don't occupy the same square.

Vasya has a board with $ 2\times n $ squares onto which he wants to put some bishwocks. To his dismay, several squares on this board are already occupied by pawns and Vasya can't put bishwocks there. However, pawns also don't attack bishwocks and they can occupy adjacent squares peacefully.

Knowing the positions of pawns on the board, help Vasya to determine the maximum amount of bishwocks he can put onto the board so that they wouldn't occupy the same squares and wouldn't occupy squares with pawns.

## 样例 #1

### 输入

```
00
00
```

### 输出

```
1```

## 样例 #2

### 输入

```
00X00X0XXX0
0XXX0X00X00
```

### 输出

```
4```

## 样例 #3

### 输入

```
0X0X0
0X0X0
```

### 输出

```
0```

## 样例 #4

### 输入

```
0XXX0
00000
```

### 输出

```
2```

# AI分析结果



---

### 唯一算法分类
**贪心算法**

---

### 题解思路与核心难点

#### 核心思路
1. **贪心策略**：从左到右扫描棋盘，遇到能放置的 L 形块立即放置，并标记已占用的格子。
2. **四种 L 形判断**：通过检查相邻两列的四种可能形态（覆盖三格）来决定是否放置。
3. **边界处理**：需确保遍历时不会越界访问棋盘范围外的位置（如最后一列的右侧）。

#### 难点与解决
- **正确性证明**：贪心策略的正确性基于“能放则放”原则，确保当前放置不影响后续更优解。
- **覆盖顺序优化**：部分题解提到优先处理开口朝外的 L 形块，避免后续无法放置（如连续三列全空时）。
- **边界条件**：需确保遍历到 `i+1` 时不越界，部分题解通过循环范围或条件判断处理。

---

### 题解评分（≥4星）

#### 1. QWQ_jyc （4星）
- **亮点**：代码简洁，直接遍历四种情况并标记，符合贪心直觉。
- **缺点**：未显式处理 `i+1` 越界问题，但通过隐式条件规避。
- **代码片段**：
  ```cpp
  if (a[i] == '0' && b[i] == '0' && a[i+1] == '0') {
      a[i] = b[i] = a[i+1] = '1'; // 标记已占用
      s++; // 计数
  }
  ```

#### 2. fish_love_cat （4星）
- **亮点**：强调优先处理开口朝外的情况，避免后续无法放置。
- **个人心得**：提到“俄罗斯方块原理”——尽量填满下方空间。
- **代码片段**：
  ```cpp
  if (a[i-1] == '0' && a[i] == '0' && b[i-1] == '0') {
      ans++; // 优先放置开口朝右的块
      a[i] = 'X'; // 标记
  }
  ```

#### 3. ALIN_lin （4星）
- **亮点**：代码结构清晰，显式处理四种 L 形状态。
- **缺点**：同样未处理 `i+1` 越界。
- **代码片段**：
  ```cpp
  if (a[i] == '0' && b[i] == '0' && a[i+1] == '0') {
      a[i] = b[i] = a[i+1] = 'X'; // 标记并计数
      s++;
  }
  ```

---

### 最优思路与技巧
1. **贪心策略**：从左到右扫描，优先处理开口朝外的 L 形块。
2. **标记机制**：放置后立即标记格子，避免重复计算。
3. **边界处理**：循环至 `i < n-1` 或检查 `i+1` 的有效性。

---

### 同类型题与算法套路
- **类似问题**：俄罗斯方块覆盖、棋盘填充问题。
- **通用解法**：贪心或动态规划（如 `f[i][状态]` 表示当前列状态）。

---

### 推荐题目
1. **P1005** 矩阵取数游戏（贪心/动态规划）
2. **P1058** 立体图（模拟与覆盖）
3. **P2831** 愤怒的小鸟（状态压缩动态规划）

---

### 个人心得摘录
- **fish_love_cat**：  
  *“当某区域有多种放法时，优先放开口朝外的，否则可能出现误差。”*
- **傅思维666**：  
  *“像俄罗斯方块一样，尽量填满下方空间。”*

---

### 可视化与算法演示

#### 动画设计
1. **棋盘扫描**：从左到右逐列高亮当前处理位置。
2. **L 形块放置**：用不同颜色标记四种 L 形，展示覆盖过程。
3. **标记更新**：动态显示格子被标记为已占用。
4. **音效提示**：放置时触发“像素音效”，错误时短促提示。

#### 复古像素风格
- **颜色方案**：8-bit 风格，棋盘用绿色格子，L 形用红色/蓝色。
- **Canvas 绘制**：网格化棋盘，L 形块以像素方块动画呈现。
- **AI 自动演示**：自动播放贪心策略，允许手动步进。

---

### 代码实现（核心逻辑）
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int ans = 0, n = a.size();
    for (int i = 0; i < n - 1; i++) { // 处理到倒数第二列
        // 检查四种 L 形，优先处理开口朝右
        if (a[i] == '0' && b[i] == '0' && a[i+1] == '0') {
            a[i] = a[i+1] = b[i] = 'X'; ans++;
        } else if (a[i] == '0' && b[i] == '0' && b[i+1] == '0') {
            a[i] = b[i] = b[i+1] = 'X'; ans++;
        } else if (a[i] == '0' && a[i+1] == '0' && b[i+1] == '0') {
            a[i] = a[i+1] = b[i+1] = 'X'; ans++;
        } else if (b[i] == '0' && a[i+1] == '0' && b[i+1] == '0') {
            a[i+1] = b[i] = b[i+1] = 'X'; ans++;
        }
    }
    cout << ans;
    return 0;
}
```

---
处理用时：252.16秒