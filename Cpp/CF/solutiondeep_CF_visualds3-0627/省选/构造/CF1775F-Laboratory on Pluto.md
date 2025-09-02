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

## 唯一算法分类  
动态规划（分拆数应用）

---

## 综合分析与结论  
### 题解核心思路  
所有题解均基于以下核心逻辑：  
1. **最优形状推导**：将实验室视为矩形扣除四个角的阶梯形结构，周长最小的矩形尺寸满足 $a \times b \geq n$ 且 $a+b$ 最小  
2. **分拆数建模**：每个角扣除的块数对应单调递减的阶梯形，转化为分拆数问题（将整数拆分为多个有序数的和）  
3. **动态规划预处理**：  
   - `dp[i][j]` 表示用 j 个数拆分为 i 个块的方案数  
   - 转移方程：`dp[i][j] = dp[i-1][j-1] + dp[i-j][j]`（新增一个1或所有数加1）  
4. **四角方案合并**：通过三次卷积操作（暴力合并）将单个角的方案数扩展为四角组合方案  

### 可视化设计要点  
1. **像素化动态规划过程**：  
   - 在 Canvas 网格中动态绘制 `dp[i][j]` 的变化，用不同颜色标记新增1和全体加1的操作  
   - 每完成一次转移播放短促的“滴”声提示  
2. **矩形枚举演示**：  
   - 以 8-bit 像素方块表示不同 $a \times b$ 矩形，高亮当前最优矩形  
   - 当检测到合法矩形时，播放上升音阶并显示其扣除角后的形状  
3. **四角方案合成动画**：  
   - 四个角的方案数显示为四个独立像素条，每次卷积时用闪光效果连接对应数值  
   - 最终合成方案数时触发“完成”音效（类似马里奥吃到金币的音效）

---

## 题解清单（≥4星）  
### Hovery（⭐⭐⭐⭐⭐）  
- **核心亮点**：  
  1. 引入分拆数的经典模型 P1025 进行类比，思路迁移清晰  
  2. 预处理逻辑完整，三次卷积合并四角方案的代码简洁高效  
  3. 枚举矩形时采用根号附近±100的范围优化，平衡了准确性与效率  

### Mine_King（⭐⭐⭐⭐）  
- **核心亮点**：  
  1. 图文并茂的阶梯形示意图，直观展示扣除角的形状特性  
  2. 明确推导 `dp[i][j]` 的数学意义，强调空格数不超过边长的关键限制  
  3. 代码中采用分层预处理结构，逻辑模块化程度高  

### zac2010（⭐⭐⭐⭐）  
- **核心亮点**：  
  1. 使用逆向思维从答案形态反推模型  
  2. 提出“凸图形一定比凹图形优”的重要观察  
  3. 代码中 `f[0]=1` 的初始化处理巧妙，避免边界条件错误  

---

## 最优思路与代码实现  
### 关键代码片段（Hovery 题解核心）  
```cpp
// 分拆数预处理
dp[0][0] = 1;
for (int i=1; i<=1000; i++)
    for (int j=i; j<=1000; j++) 
        dp[i][j] = (dp[i-1][j-1] + dp[i][j-i]) % mod;

// 单个角方案数计算
for (int i=1; i<=1000; i++)
    for (int j=1; j<=i; j++)
        f[i] = (f[i] + dp[j][i]) % mod;

// 三次卷积合并四角方案
for (int i=0; i<=1000; i++)
    for (int j=0; j<=1000; j++)
        if (i+j <= 1000) 
            g[i+j] = (g[i+j] + f[i]*f[j]) % mod; // 二次卷积
// 重复三次得到四角合并结果
```

### 实现思想  
1. **分拆数生成**：通过双重循环动态构建所有可能的分拆方案  
2. **卷积合并**：利用数组累加实现暴力卷积，将四个独立角的方案组合为整体  
3. **矩形枚举优化**：仅检查 $\sqrt{n}$ 附近有限范围，避免全范围枚举的低效  

---

## 同类题目推荐  
1. **P1025 数的划分** - 分拆数的经典模型  
2. **CF1513C Staircases** - 阶梯形结构的动态规划应用  
3. **P4389 付公主的背包** - 生成函数与分拆数的进阶应用  

---

## 个人心得摘录  
> "意识到四个角的方案独立是突破的关键，这让我联想到信号处理中的卷积操作。虽然暴力合并看似笨拙，但在数据规模较小时反而比FFT更高效。" —— Hovery  
> 
> "调试时发现忘记处理矩形长宽相等的情况，导致方案数少算一倍。这种边界条件需要特别标记！" —— Mine_King  
> 
> "将问题分解为形状确定和方案计算两个独立阶段，大大简化了思考复杂度。" —— zac2010  

---

## 可视化算法演示（核心逻辑）  
### 动画流程设计  
1. **初始化阶段**：  
   - 16x16 像素网格展示原始矩形，右下角显示当前枚举的 a×b 尺寸  
   - 背景播放 8-bit 风格循环音乐（类似《俄罗斯方块》BGM）  

2. **动态规划演示**：  
   ```javascript
   // 伪代码示例
   function showDP(i, j) {
       ctx.fillStyle = (operation === 'add1') ? '#FF5555' : '#55AAFF';
       drawCell(i, j); // 在Canvas绘制当前更新的dp[i][j]
       playSound('blip'); // 播放短促音效
   }
   ```

3. **矩形枚举过程**：  
   - 当前候选矩形用闪烁的黄色边框高亮  
   - 合法矩形触发绿色闪光，非法矩形显示红色叉号  

4. **方案合成高潮**：  
   - 四角方案合并时，四个像素条从屏幕四角飞向中心合并  
   - 最终方案数显示为复古LED数字样式，伴随胜利音效  

### 交互控制面板  
- **速度调节**：滑动条控制动画速度（0.5x~3x）  
- **单步模式**：Space键单步执行关键步骤  
- **AI 自动演示**：按'A'键自动完成最优路径演示  

---

通过这种将算法核心步骤具象化为像素动画的设计，学习者可以直观理解分拆数的生成过程与方案合并逻辑，同时复古游戏风格的交互增强了学习的趣味性。

---
处理用时：70.23秒