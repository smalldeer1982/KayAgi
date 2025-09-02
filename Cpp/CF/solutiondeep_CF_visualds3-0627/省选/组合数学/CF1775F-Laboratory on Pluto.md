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



### 唯一算法分类
**动态规划与组合数学**

---

### 综合分析与结论
**核心思路**  
题目要求构造周长最小的网格布局，并统计方案数。最优解的形状是接近正方形的矩形，挖去四个角的部分块。关键步骤如下：
1. **确定最优矩形**：通过枚举长宽，找到周长最小的矩形 `a×b`，满足 `a×b ≥n` 且 `|a−b|` 最小。
2. **分拆数动态规划**：每个角的挖取方案转化为整数分拆问题（阶梯形排列），预处理每个角的方案数 `f[i]`。
3. **组合方案数**：将四个角的方案数通过卷积合并，得到总方案数 `h[k]`，其中 `k = a×b −n`。

**难点与解决**  
- **分拆数的状态转移**：定义 `dp[i][j]` 表示分拆 `i` 个块、最大项为 `j` 的方案数，转移方程为 `dp[i][j] = dp[i−j][j] + dp[i−1][j−1]`。
- **卷积合并优化**：四个角独立，四次暴力卷积合并 `f` 数组，时间复杂度为 `O(k^2)`（`k` 最大为 `√n`）。

**可视化设计思路**  
- **像素化展示**：用网格动态显示矩形挖角过程，每个角的分拆用不同颜色标记。
- **动态规划步骤高亮**：在分拆数生成时，高亮当前处理的块数 `i` 和分拆项 `j`。
- **音效与交互**：在枚举矩形长宽时，播放不同音效提示合法解；卷积合并时用进度条显示计算步骤。

---

### 题解清单（评分≥4星）
1. **Hovery的题解（4.5星）**  
   - **亮点**：清晰推导分拆数与卷积合并逻辑，代码预处理好 `f` 和 `h` 数组，时间复杂度严格。
   - **核心代码**：预处理 `dp[i][j]` 并合并四次。

2. **Mine_King的题解（4.5星）**  
   - **亮点**：图文结合解释阶梯形分拆，动态规划转移方程详细，预处理优化枚举范围。
   - **关键图示**：展示矩形挖角后的形状，直观说明方案独立性。

3. **zac2010的题解（4星）**  
   - **亮点**：代码简洁高效，预处理与卷积合并逻辑明确，适合快速实现。
   - **优化点**：限制预处理数组大小为 `1000`，避免冗余计算。

---

### 核心代码实现（以 Mine_King 代码为例）
```cpp
int dp[1005][1005], f[1005], g[1005], gg[1005];
void solve2() {
    // 预处理分拆数
    dp[0][0] = 1;
    for (int i=1; i<=1000; i++)
        for (int j=i; j<=1000; j++)
            dp[i][j] = (dp[i-1][j-1] + dp[i][j-i]) % mod;
    for (int i=1; i<=1000; i++)
        for (int j=1; j<=i; j++)
            f[i] = (f[i] + dp[j][i]) % mod;
    // 合并四个角的方案数
    for (int i=0; i<=1000; i++)
        for (int j=0; j<=1000; j++)
            if (i+j <= 1000) g[i+j] = (g[i+j] + f[i]*f[j]) % mod;
    for (int i=0; i<=1000; i++)
        for (int j=0; j<=1000; j++)
            if (i+j <= 1000) gg[i+j] = (gg[i+j] + f[i]*g[j]) % mod;
    // 枚举合法矩形计算答案
    int len = sqrt(n), ans = 0;
    for (int r = max((int)sqrt(n)-100,1); r<=min((int)sqrt(n)+100,n); r++) {
        int c = (n + r -1)/r;
        int k = r*c -n;
        ans = (ans + gg[k] * (r==c ? 1 : 2)) % mod;
    }
}
```

---

### 同类型题与相似套路
1. **整数分拆问题**：如 [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)，要求将数分拆为特定项。
2. **组合方案合并**：如卷积合并独立事件的方案数（类似生成函数思想）。
3. **最优形状构造**：如 [CF1584D Guess the Permutation](https://codeforces.com/problemset/problem/1584/D)，通过数学推导确定最优结构。

---

### 推荐题目
1. **P1025**：数的划分，练习分拆数动态规划。
2. **CF1527D**：MEX Tree，组合数学与树结构结合。
3. **P6189**：跑步，分拆数的高级应用。

---

### 个人心得摘录
- **调试教训**：预处理数组大小需足够大（如 `1000`），否则会遗漏大 `n` 的情况。
- **思维突破**：四个角独立性的发现是关键，避免重复计算重叠区域。

---

### 可视化与算法演示
**动画方案设计**  
1. **网格绘制**：  
   - 使用 Canvas 绘制初始矩形，动态挖去四个角，用不同颜色标记每个角的块。
2. **分拆数生成**：  
   - 高亮当前分拆的块数 `i` 和分拆项 `j`，显示 `dp[i][j]` 的更新过程。
3. **卷积合并演示**：  
   - 用进度条表示四个合并步骤，每个步骤显示当前卷积结果。
4. **音效与交互**：  
   - 合法矩形枚举成功时播放“叮”声，分拆数更新时播放轻微点击声。

**复古像素风格**  
- **颜色方案**：16色调色板，挖角用红色，保留块用绿色。
- **自动演示**：模拟“贪吃蛇”式移动，从左上角开始逐块填充挖取区域。

---
处理用时：71.51秒