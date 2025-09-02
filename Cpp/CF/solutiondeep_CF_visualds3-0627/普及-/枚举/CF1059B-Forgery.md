# 题目信息

# Forgery

## 题目描述

Student Andrey has been skipping physical education lessons for the whole term, and now he must somehow get a passing grade on this subject. Obviously, it is impossible to do this by legal means, but Andrey doesn't give up. Having obtained an empty certificate from a local hospital, he is going to use his knowledge of local doctor's handwriting to make a counterfeit certificate of illness. However, after writing most of the certificate, Andrey suddenly discovered that doctor's signature is impossible to forge. Or is it?

For simplicity, the signature is represented as an $ n\times m $ grid, where every cell is either filled with ink or empty. Andrey's pen can fill a $ 3\times3 $ square without its central cell if it is completely contained inside the grid, as shown below.

 `<br></br>xxx<br></br>x.x<br></br>xxx<br></br>`Determine whether is it possible to forge the signature on an empty $ n\times m $ grid.

## 说明/提示

In the first sample Andrey can paint the border of the square with the center in $ (2, 2) $ .

In the second sample the signature is impossible to forge.

In the third sample Andrey can paint the borders of the squares with the centers in $ (2, 2) $ and $ (3, 2) $ :

1. we have a clear paper: `<br></br>...<br></br>...<br></br>...<br></br>...<br></br>`
2. use the pen with center at $ (2, 2) $ . `<br></br>###<br></br>#.#<br></br>###<br></br>...<br></br>`
3. use the pen with center at $ (3, 2) $ . `<br></br>###<br></br>###<br></br>###<br></br>###<br></br>`

In the fourth sample Andrey can paint the borders of the squares with the centers in $ (3, 3) $ and $ (3, 5) $ .

## 样例 #1

### 输入

```
3 3
###
#.#
###
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3 3
###
###
###
```

### 输出

```
NO```

## 样例 #3

### 输入

```
4 3
###
###
###
###
```

### 输出

```
YES```

## 样例 #4

### 输入

```
5 7
.......
.#####.
.#.#.#.
.#####.
.......
```

### 输出

```
YES```

# AI分析结果



# Forgery 题解分析

## 算法分类
**模拟**

---

## 题解思路与解决难点

### 核心算法流程
1. **初始化**：创建与目标图相同大小的模拟数组，初始全为 `.`。
2. **枚举有效中心点**：遍历所有可能的染色中心点，这些点必须满足其周围 8 格均在网格内（即中心点范围限制为 `[2, n-1]` 行和 `[2, m-1]` 列，以 1-based 索引为例）。
3. **染色条件检查**：对每个有效中心点，检查目标图中其周围 8 格是否全为 `#`，若满足则进行染色。
4. **模拟染色**：对满足条件的中心点，在模拟数组中标记其周围 8 格为 `#`。
5. **结果比对**：最终检查模拟数组与目标数组是否完全一致。

### 解决难点
- **边界处理**：通过限制中心点的遍历范围，避免染色操作越界，减少无效判断。
- **高效枚举**：仅检查可能染色的中心点，时间复杂度优化至 `O((n-2)(m-2))`。
- **多次染色覆盖**：允许重复染色，无需考虑操作顺序，只需确保所有必要区域被覆盖。

---

## 题解评分（≥4星）

1. **Abyss_Bright（5星）**  
   - **亮点**：代码结构清晰，通过移动数组简化染色逻辑，处理越界检查全面。  
   - **优化**：遍历全图但内部条件判断完备，适合教学理解。

2. **氢氧化铯CsOH（5星）**  
   - **亮点**：枚举 3x3 左上角，逻辑简洁高效，直接处理有效范围。  
   - **优化**：限制遍历范围至 `n-3` 和 `m-3`，避免冗余判断。

3. 「已注销」（4星）  
   - **亮点**：通过预处理目标图，直接覆盖所有可行染色区域，代码简洁。  
   - **优化**：使用固定偏移量处理 3x3 区域，直观易扩展。

---

## 最优思路提炼
**核心技巧**：  
- **有效范围限制**：仅遍历中心点范围 `[2, n-1] × [2, m-1]`，确保染色操作不越界。  
- **批量染色**：对满足条件的中心点，直接标记周围 8 格，无需考虑覆盖顺序。  
- **预处理比对**：初始模拟数组全为 `.`，仅通过染色生成最终结果，简化比对逻辑。

---

## 同类题型推荐
1. **P1162 填涂颜色**（二维矩阵扩散填充）  
2. **P2895 [USACO08FEB]Meteor Shower S**（动态更新网格危险区域）  
3. **P1505 扫雷游戏**（模拟相邻格状态计算）

---

## 个人心得摘录
- **Forever1507**：深搜在本题中效率劣于枚举，因需额外维护访问状态。  
- **Abyss_Bright**：越界检查必须严格，否则会错误染色导致比对失败。  
- **氢氧化铯CsOH**：通过固定偏移量处理 3x3 区域，避免坐标计算错误。

---

## 可视化与算法演示

### 动画设计
1. **网格展示**：  
   - 初始网格全白（`.`），目标网格用不同颜色标记 `#`。  
   - 当前染色中心点高亮为黄色，染色区域标记为蓝色。

2. **染色过程**：  
   - 自动模式：按行优先顺序遍历中心点，满足条件时触发染色动画。  
   - 手动模式：支持暂停/继续，单步观察染色逻辑。

3. **音效交互**：  
   - 染色时播放短促“点击”音效，成功匹配后播放胜利音效。  
   - 错误点闪烁红色，并播放警示音。

### 复古像素风格
- **调色板**：8-bit 风格，使用有限颜色（蓝、黄、红、绿）。  
- **Canvas 绘制**：每个格子为 16x16 像素，染色时动态填充颜色。  
- **自动演示**：AI 按最优路径遍历中心点，速度可调（1x~5x）。

---

## 关键代码片段
```cpp
// 氢氧化铯CsOH 的核心逻辑
bool all(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int r = x + dx[i], c = y + dy[i];
        if (r < 0 || r >= n || c < 0 || c >= m) return false; 
        if (s[r][c] == '.') return false;
    }
    return true;
}

void set(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int r = x + dx[i], c = y + dy[i];
        vis[r][c] = true;
    }
}

// 主逻辑：遍历所有可能的 3x3 左上角
for (int i = 0; i + 2 < n; i++) {
    for (int j = 0; j + 2 < m; j++) {
        if (all(i, j)) set(i, j);
    }
}
```

---

## 总结
本题通过模拟所有可能的染色操作，并高效限制遍历范围，确保了算法的最优性。核心在于正确处理边界条件和染色覆盖逻辑，最终通过比对验证结果。

---
处理用时：155.11秒