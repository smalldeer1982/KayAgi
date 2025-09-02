# 题目信息

# Multicolored Markers

## 题目描述

There is an infinite board of square tiles. Initially all tiles are white.

Vova has a red marker and a blue marker. Red marker can color $ a $ tiles. Blue marker can color $ b $ tiles. If some tile isn't white then you can't use marker of any color on it. Each marker must be drained completely, so at the end there should be exactly $ a $ red tiles and exactly $ b $ blue tiles across the board.

Vova wants to color such a set of tiles that:

- they would form a rectangle, consisting of exactly $ a+b $ colored tiles;
- all tiles of at least one color would also form a rectangle.

Here are some examples of correct colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)Here are some examples of incorrect colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)Among all correct colorings Vova wants to choose the one with the minimal perimeter. What is the minimal perimeter Vova can obtain?

It is guaranteed that there exists at least one correct coloring.

## 说明/提示

The first four examples correspond to the first picture of the statement.

Note that for there exist multiple correct colorings for all of the examples.

In the first example you can also make a rectangle with sides $ 1 $ and $ 8 $ , though its perimeter will be $ 18 $ which is greater than $ 8 $ .

In the second example you can make the same resulting rectangle with sides $ 3 $ and $ 4 $ , but red tiles will form the rectangle with sides $ 1 $ and $ 3 $ and blue tiles will form the rectangle with sides $ 3 $ and $ 3 $ .

## 样例 #1

### 输入

```
4 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 9
```

### 输出

```
14
```

## 样例 #3

### 输入

```
9 3
```

### 输出

```
14
```

## 样例 #4

### 输入

```
3 6
```

### 输出

```
12
```

## 样例 #5

### 输入

```
506 2708
```

### 输出

```
3218
```

# AI分析结果


### 💡 Kay的C++算法解析：Multicolored Markers 深入学习指南 💡

**题目解读与核心算法识别**  
✨ **本题主要考察**：`枚举优化与因子应用`  
🗣️ **初步分析**：  
> 本题要求将 $a$ 个红色和 $b$ 个蓝色方块排列成一个大矩形（面积 $a+b$），且至少一种颜色的方块能形成独立矩形。核心挑战是**高效枚举大矩形的尺寸**并验证颜色矩形的嵌入可行性。  

> - **核心思路**：从 $\sqrt{a+b}$ 开始递减枚举大矩形宽度 $i$，对每个 $i$ 检查是否存在 $a$ 或 $b$ 的因子 $j \leq i$ 使得 $a/j \leq (a+b)/i$（即颜色矩形能嵌入大矩形）。  
> - **优化关键**：避免暴力枚举因子——通过动态维护最大因子（Bring法）或预处理因子+指针移动（Siyuan法）将复杂度优化至 $O(\sqrt{\max(a,b)})$。  
> - **可视化设计**：采用复古像素风格展示枚举过程。大矩形用绿色网格表示，红色/蓝色方块以闪烁像素块动态嵌入，超出边界时播放"失败音效"，成功时显示周长公式并播放"胜利音效"。  

---

### 2. 精选优质题解参考  
**题解一（Bring）**  
* **亮点**：  
  - **思路清晰性**：动态维护 $a,b$ 的最大因子 $f,g$，每次枚举时重置 $f,g$ 并递减至合法因子，逻辑直白。  
  - **代码规范性**：变量名 `f, g, tot` 含义明确，边界处理严谨（如 `f = min(f, i)`）。  
  - **算法有效性**：复杂度 $O(\sqrt{\max(a,b)})$，显著优于暴力枚举。  
  - **实践价值**：可直接用于竞赛，代码简洁高效（洛谷实测 1.46s）。  

**题解二（Siyuan）**  
* **亮点**：  
  - **思路清晰性**：预处理 $a$ 的因子，用指针 $p$ 快速定位不超过 $i$ 的最大因子，逻辑严谨。  
  - **代码规范性**：封装 `solve()` 函数处理核心逻辑，结构清晰。  
  - **算法有效性**：预处理因子 $O(\sqrt{a})$，枚举过程 $O(\sqrt{a+b})$，高效稳定。  

**题解三（guanyf-指针法）**  
* **亮点**：  
  - **思路创新性**：用指针 `id[]` 记录因子位置，避免重复枚举。  
  - **代码优化**：通过 `min(i, id[tot==b])` 快速调整指针，提升效率。  

---

### 3. 核心难点辨析与解题策略  
1. **高效因子检查**  
   * **分析**：暴力枚举因子会超时（$O(\sqrt{a+b} \times \sqrt{a})$）。优质题解用动态维护（Bring）或预处理+指针（Siyuan）保证单次检查 $O(1)$。  
   * 💡 **学习笔记**：因子枚举需结合单调性优化——因子范围随 $i$ 递减而缩小。  

2. **大矩形枚举顺序**  
   * **分析**：周长 $2(i + (a+b)/i)$ 在 $i \approx \sqrt{a+b}$ 时最小。从 $\sqrt{a+b}$ 递减枚举可优先获取最优解。  
   * 💡 **学习笔记**：数学性质（均值不等式）是优化枚举的基础。  

3. **嵌入条件验证**  
   * **分析**：检查 $a/j \leq (a+b)/i$ 时，$j$ 需是 $a$ 的最大因子 $\leq i$。动态维护 $j$ 可避免重复计算。  
   * 💡 **学习笔记**：将条件转化为 $j \times \text{大矩形高} \geq a$ 更易实现。  

### ✨ 解题技巧总结  
- **单调性优化**：因子大小与 $i$ 正相关，逆序枚举 $i$ 时因子范围单调缩小。  
- **状态复用**：用变量（如 `f, g`）记录前次因子位置，减少冗余计算。  
- **边界剪枝**：当 $a/j > (a+b)/i$ 时立即终止检查（因子越大 $a/j$ 越小）。  

---

### 4. C++核心代码实现赏析  
**本题通用核心实现（Bring 优化法）**  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll a, b;
    cin >> a >> b;
    ll tot = a + b;
    ll f = sqrt(a), g = sqrt(b);
    while (f * f > a) f--;
    while (g * g > b) g--;

    for (ll i = sqrt(tot); i >= 1; i--) {
        if (tot % i != 0) continue;
        ll h = tot / i; // 大矩形高度
        ll f1 = min(f, i), g1 = min(g, i);
        while (a % f1) f1--;   // 找 a 的最大因子 ≤i
        if (a / f1 <= h) {     // 检查红色矩形嵌入
            cout << 2*(i + h);
            return 0;
        }
        while (b % g1) g1--;   // 找 b 的最大因子 ≤i
        if (b / g1 <= h) {     // 检查蓝色矩形嵌入
            cout << 2*(i + h);
            return 0;
        }
    }
    return 0;
}
```
* **代码解读概要**：  
  - 初始化 $f,g$ 为 $\sqrt{a},\sqrt{b}$（最大可能因子）。  
  - 逆序枚举大矩形宽度 $i$，对每个 $i$ 计算高度 $h = (a+b)/i$。  
  - 动态调整 $f1,g1$ 为 $\min(f,i)$ 和 $\min(g,i)$，递减至合法因子。  
  - 一旦 $a$ 或 $b$ 的矩形可嵌入（$a/f1 \leq h$ 或 $b/g1 \leq h$），输出周长并终止。  

---

### 5. 算法可视化：像素动画演示  
**主题**：复古像素风矩形嵌入模拟（灵感：FC游戏《俄罗斯方块》）  

**设计思路**：  
> 8位像素风格降低理解门槛，通过动态嵌入方块的成败直观展示算法逻辑。音效强化关键操作记忆，游戏化进度提升学习动力。  

**动画流程**：  
1. **初始化**：  
   - 像素网格背景（16色），左侧显示参数 $a,b$，右侧控制面板（开始/步进/调速滑块）。  
   - 播放8-bit背景音乐（循环）。  

2. **枚举大矩形**：  
   - 绿色网格表示大矩形（宽 $i$，高 $h$），$i$ 从 $\sqrt{a+b}$ 递减。  
   - 每次步进播放"滴"音效，$i$ 值显示于顶部。  

3. **颜色矩形嵌入**：  
   - **尝试红色**：左上角生成红色矩形（宽 $f1$，高 $a/f1$）。若 $a/f1 > h$，红色闪烁并播放"失败"音效。  
   - **尝试蓝色**：左上角生成蓝色矩形（宽 $g1$，高 $b/g1$）。若 $b/g1 > h$，蓝色闪烁+失败音效。  
   - **成功嵌入**：颜色矩形稳定显示，大矩形边框闪烁绿色，播放"胜利"音效，显示周长公式 $2(i+h)$。  

4. **交互控制**：  
   - **步进模式**：手动触发枚举下一步。  
   - **自动模式**：AI自动执行（速度可调），类似"贪吃蛇AI"逐步解题。  
   - **重置**：恢复初始状态。  

---

### 6. 拓展练习与相似问题  
**通用技巧迁移**：  
- 因子枚举优化可用于：质数筛法优化、背包问题剪枝、矩形分割问题。  

**洛谷推荐**：  
1. **P1077 摆花**：枚举因子优化计数DP。  
   > 🗣️ 巩固因子枚举在组合问题中的应用。  
2. **P1217 回文质数**：结合质数判断与回文数生成。  
   > 🗣️ 练习数学性质与枚举的协同优化。  
3. **P1363 幻象迷宫**：无限网格中的路径枚举。  
   > 🗣️ 迁移矩形枚举思维至图论问题。  

---

### 7. 学习心得与经验分享  
> 本次题解未包含作者个人心得，但从算法实现可提炼：  
> - **调试技巧**：当 $a/j > h$ 时，输出 $i,j,h$ 的值可快速定位逻辑错误。  
> - **优化意识**：$10^{14}$ 数据范围需 $O(\sqrt{n})$ 解法，暴力枚举必然超时。  

---  
**结语**：通过因子枚举的单调性优化，我们高效解决了矩形嵌入问题。记住：好的算法 = 数学洞察 + 状态复用！下次挑战见！ 💪

---
处理用时：205.49秒