# 题目信息

# Laboratory on Pluto

## 题目描述

As you know, Martian scientists are actively engaged in space research. One of the highest priorities is Pluto. In order to study this planet in more detail, it was decided to build a laboratory on Pluto.

It is known that the lab will be built of $ n $ square blocks of equal size. For convenience, we will assume that Pluto's surface is a plane divided by vertical and horizontal lines into unit squares. Each square is either occupied by a lab block or not, and only $ n $ squares are occupied.

Since each block is square, it has four walls. If a wall is adjacent to another block, it is considered inside, otherwise — outside.

Pluto is famous for its extremely cold temperatures, so the outside walls of the lab must be insulated. One unit of insulation per exterior wall would be required. Thus, the greater the total length of the outside walls of the lab (i. e., its perimeter), the more insulation will be needed.

Consider the lab layout in the figure below. It shows that the lab consists of $ n = 33 $ blocks, and all the blocks have a total of $ 24 $ outside walls, i. e. $ 24 $ units of insulation will be needed.

You should build the lab optimally, i. e., minimize the amount of insulation. On the other hand, there may be many optimal options, so scientists may be interested in the number of ways to build the lab using the minimum amount of insulation, modulo a prime number $ m $ .

Two ways are considered the same if they are the same when overlapping without turning. Thus, if a lab plan is rotated by $ 90^{\circ} $ , such a new plan can be considered a separate way.

To help scientists explore Pluto, you need to write a program that solves these difficult problems.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/19a2731aaaa55a0f9a8048f01dd79ff768ce23d2.png)

## 说明/提示

Consider the second example.

If $ n=1 $ , the only way to build a lab is to place a single block. In this case, the perimeter will be equal to four.

When $ n=2 $ , you must place two blocks side by side. This can be done either vertically or horizontally, so there are two ways. It is easy to see that the lab has six outside walls in this case.

For $ n=7 $ , all the $ 22 $ optimal plans are shown in the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/2d61b154960a5ef9890728641d5e6f811e5f6274.png)

## 样例 #1

### 输入

```
3 1
1
2
7```

### 输出

```
1 1
#
1 2
##
2 4
.###
####```

## 样例 #2

### 输入

```
3 2
1000000007
1
2
7```

### 输出

```
4 1
6 2
12 22```

# AI分析结果



---

## **算法分类**  
动态规划、组合数学

---

## **综合分析与结论**  

### **核心思路**  
1. **最小周长确定**：最优形状为接近正方形的矩形，可能扣除四个角的阶梯形区域以保持周长最小。  
2. **方案数计算**：每个角的扣除方案转化为整数分拆问题，通过动态规划预处理分拆数，合并四个角的方案数（卷积实现）。  

### **解决难点**  
- **分拆数 DP 设计**：状态 `dp[i][j]` 表示总和为 `i`、划分为 `j` 个数的方案数，转移方程 `dp[i][j] = dp[i-1][j-1] + dp[i-j][j]`。  
- **高效合并方案**：四个角的方案数通过三次卷积合并（单角→两角→四角），利用 `O(√n)` 的稀疏性暴力卷积。  
- **枚举优化**：仅需枚举 `√n ± C` 范围内的矩形边长，避免 `O(n)` 枚举。  

### **可视化设计**  
- **像素动画**：用 Canvas 绘制网格，动态演示矩形边长调整与四个角阶梯形扣除过程。  
- **分步高亮**：  
  - 红色边框标记当前枚举的矩形。  
  - 蓝色方块表示扣除的角区域，每步挖角时触发闪烁动画。  
- **音效提示**：  
  - 挖角时播放 `8-bit` 挖矿音效。  
  - 找到最优解时播放经典 FC 过关音效。  

---

## **题解评分 (≥4星)**  

### **Hovery (★★★★☆)**  
- **亮点**：  
  - 明确分拆数转移方程，预处理 `f[i]` 后三次卷积合并。  
  - 代码结构清晰，暴力卷积实现高效。  
- **改进点**：卷积部分可优化为更通用的循环结构。  

### **Mine_King (★★★★★)**  
- **亮点**：  
  - 图文结合，分阶段解析角扣除与卷积逻辑。  
  - 预处理 `dp` 和 `f` 数组，代码模块化程度高。  
- **代码片段**：  
  ```cpp  
  // 分拆数预处理  
  dp[0][0] = 1;  
  for (int i=1; i<=1000; i++)  
    for (int j=i; j<=1000; j++)  
      dp[i][j] = dp[i-1][j-1] + dp[i][j-i];  
  ```  

### **zac2010 (★★★★☆)**  
- **亮点**：  
  - 将四个角方案数合并简化为四次独立卷积。  
  - 动态规划状态定义与转移直观易懂。  
- **心得摘录**：  
  > “四次卷积看似暴力，但由于角扣除数 `k=O(√n)`，实际复杂度可控。”  

---

## **最优思路或技巧提炼**  

### **关键技巧**  
1. **整数分拆模型**：将每个角扣除的阶梯形转化为单调序列分拆，使用经典 DP 预处理。  
2. **卷积合并**：通过三次卷积合并四个角的可能性，利用稀疏性优化计算。  
3. **边长枚举优化**：仅需在 `√n ± 100` 范围内枚举矩形尺寸，避免全范围搜索。  

### **代码实现要点**  
- **预处理 `f[i]`**：计算单角扣除 `i` 块的方案数。  
- **暴力卷积**：合并四次角的方案数，代码片段如下：  
  ```cpp  
  // 合并四个角的方案数  
  for (int i=0; i<=1000; i++)  
    for (int j=0; j<=1000-i; j++)  
      g[i+j] += f[i] * f[j]; // 合并两次  
  ```  

---

## **类似题目推荐**  
1. **洛谷 P1025**：数的划分（分拆数问题原型）。  
2. **CF1515E**：区间覆盖方案数（组合数学+动态规划）。  
3. **洛谷 P4389**：生成函数卷积优化（进阶版方案数合并）。  

---

## **复古像素化动画实现**  

### **设计细节**  
1. **Canvas 初始化**：  
   - 网格尺寸 `32x32` 像素，使用 `#FF6B6B`（红）标记实验室块，`#4ECDC4`（蓝）标记扣除区域。  
2. **动画流程**：  
   - **Step 1**：绘制初始矩形，红色边框高亮当前枚举的 `a×b`。  
   - **Step 2**：从四个角依次扣除阶梯形块，每扣除一个块触发蓝色闪烁（`requestAnimationFrame` 控制）。  
3. **音效设计**：  
   - 使用 `Web Audio API` 播放 `8-bit` 音效：  
     - 扣除块：短促 `square` 波形（频率 `440Hz`，时长 `0.1s`）。  
     - 找到最优解：上升琶音（`C4→G4→C5`）。  

### **自动演示模式**  
- **AI 决策逻辑**：  
  1. 计算 `√n` 并生成候选边长列表。  
  2. 对每个候选边长，计算扣除块数并触发动画。  
  3. 自动选择周长最小的方案，播放过关音效。  

---

**可视化演示代码片段**  
```javascript  
// Canvas 绘制扣除角示例  
function drawCorner(ctx, x, y, steps) {  
  steps.forEach((s, i) => {  
    for (let j=0; j<s; j++) {  
      ctx.fillStyle = '#4ECDC4';  
      ctx.fillRect(x*32 + j*32, y*32 + i*32, 32, 32);  
    }  
  });  
}  
```  

---

通过上述分析与实现，学习者可深入理解动态规划在组合问题中的应用，并掌握高效枚举与卷积优化的核心技巧。

---
处理用时：66.19秒