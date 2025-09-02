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

### **唯一算法分类**  
**组合数学**

---

### **综合分析与结论**  
题目核心是通过构造矩形并抠角的方式最小化周长，方案数转化为四个角的分拆数组合问题。关键公式推导基于阶梯型分块的动态规划模型，通过预处理分拆数 + 四次卷积统计组合方案。可视化设计聚焦分块动态规划和矩形构造过程，采用像素风格展示分块逻辑。

---

### **题解思路与解决难点**  
1. **核心思路**  
   - 构造最接近正方形的矩形（长宽差 ≤1）作为基底，使得周长最小。  
   - 多余的空格数需满足 `a*b - n ≤ min(a,b)`，确保只能在四个角独立抠块。  
   - 每个角的抠块方案为单调递减的阶梯型，对应分拆数问题。  

2. **关键公式推导**  
   - **分拆数 DP**:  
     `dp[i][j]` 表示总和为 `i` 且分 `j` 个数的方案数，转移方程：  
     ```  
     dp[i][j] = dp[i-1][j-1] + dp[i-j][j]  
     ```  
     前者表示新增一个 `1`，后者表示所有数加 `1`。  
   - **卷积合并**: 四个角的方案数为 `f[i]` 的四次卷积，其中 `f[i] = ∑dp[i][j]`。  

3. **难点与优化**  
   - **矩形枚举优化**：仅需枚举 `sqrt(n)` 附近的有限长宽组合。  
   - **预处理加速**：分拆数 DP 和卷积结果预先计算，避免重复运算。  

---

### **题解清单 (≥4星)**  
1. **Hovery (★★★★☆)**  
   - **亮点**：清晰拆分矩形构造与分块逻辑，引入 P1025 分拆数模型。  
   - **代码**：预处理 `dp/f/g` 数组，暴力卷积四次，枚举矩形高效。  

2. **Mine_King (★★★★★)**  
   - **亮点**：图文结合解释阶梯型分块，动态规划推导详尽，代码模块化。  
   - **预处理优化**：分拆数计算和卷积分离，避免冗余运算。  

3. **zac2010 (★★★★☆)**  
   - **亮点**：简洁的枚举策略，动态规划状态定义明确。  
   - **心得**：强调凹/凸形状对周长的影响，直观解释独立抠角条件。  

---

### **最优思路/技巧提炼**  
1. **分拆数模型**：将每个角的抠块方案转化为分拆数问题，通过 `dp[i][j]` 高效计算。  
2. **卷积合并**：利用四个角独立的性质，通过三次卷积合并方案数。  
3. **矩形快速枚举**：仅检查 `sqrt(n) ± 100` 范围内的长宽组合，避免全量枚举。  

---

### **同类型题与通用套路**  
- **通用思路**：  
  1. 构造最优几何形状（如矩形/圆形）。  
  2. 多余元素独立分块处理（如四角/边缘）。  
  3. 组合方案数通过分拆数 + 卷积合并。  
- **类似题目**：  
  - **洛谷 P1025**：数的分拆问题。  
  - **CF118D**：组合数乘法的卷积应用。  
  - **LeetCode 221. Maximal Square**：矩形构造与优化。  

---

### **推荐练习题**  
1. **CF1523D**（构造最优形状）  
2. **洛谷 P1025**（分拆数模型）  
3. **洛谷 P4389**（组合卷积应用）  

---

### **可视化与动画设计**  
1. **像素风格演示**  
   - **分拆数 DP 过程**：在 Canvas 网格中逐步填充 `dp[i][j]` 值，高亮当前转移路径。  
   - **矩形构造**：绘制基底矩形，以不同颜色标记四个角的抠块区域。  
   - **卷积合并**：显示四个角的方案数分布，动态合并为最终结果。  

2. **音效与交互**  
   - **音效**：分块完成时播放 8-bit 音效，错误操作触发警示音。  
   - **步进控制**：用户可调节动画速度，单步观察分拆数转移。  

3. **自动推导模式**  
   - **AI 演示**：自动枚举矩形并显示最优解，模拟分块和卷积计算流程。  

---

### **代码片段 (Mine_King 题解核心)**  
```cpp
// 分拆数预处理
dp[0][0] = 1;
for (int i = 1; i <= 1000; i++)
    for (int j = i; j <= 1000; j++) {
        if (i == j) dp[i][j] = 1;
        else dp[i][j] = dp[i-1][j-1] + dp[i][j-i];
    }

// 卷积合并四个角
f[0] = 1;
for (int i = 1; i <= 1000; i++)
    for (int j = 1; j <= i; j++)
        f[i] = (f[i] + dp[j][i]) % mod;

// 三次卷积合并
for (int i = 0; i <= 1000; i++)
    for (int j = 0; j <= 1000; j++)
        gg[i+j] = (gg[i+j] + f[i] * g[j]) % mod;
```

---

### **个人心得摘录**  
> “凹槽会增加周长，因此最优解必为凸形。四个角的独立分块是关键，若相邻会影响周长，但通过限制 `a*b - n ≤ a` 确保不会重叠。”（zac2010）

---
处理用时：63.98秒