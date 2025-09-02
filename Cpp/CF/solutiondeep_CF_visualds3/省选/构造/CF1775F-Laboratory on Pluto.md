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

# 💡 Kay的C++算法解析：Laboratory on Pluto 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（分拆数）、枚举优化、卷积合并  

🗣️ **初步分析**：  
解决“Laboratory on Pluto”的关键，在于**用最小周长构造n个格子的凸图形**。根据小学数学的均值不等式，**矩形的周长最小**（当长和宽越接近时，周长越小）。但n不一定是矩形面积，因此需要从矩形的**四个角去掉多余格子**（必须是阶梯型，否则会增加周长）。  

- **核心思路**：  
  1. 枚举矩形的长`a`和宽`b`（`a≤b`，且`a×b≥n`），找到使周长`2(a+b)`最小的组合。  
  2. 计算从四个角去掉`k=a×b-n`个格子的方案数（每个角的去掉方式是阶梯型，方案数为分拆数）。  
  3. 合并四个角的方案数（用卷积，因为四个角独立）。  

- **核心难点**：  
  - 如何快速找到最优矩形的`a`和`b`？（解决：枚举根号附近的`a`，因为`a`接近`√n`时周长最小）。  
  - 如何计算每个角的阶梯型去掉方案数？（解决：经典分拆数DP，类似洛谷P1025）。  
  - 如何合并四个角的方案数？（解决：用背包卷积，暴力乘四次）。  

- **可视化设计思路**：  
  用8位像素风格展示矩形构造过程：  
  - 初始时，屏幕显示一个`a×b`的像素矩形（用绿色方块表示）。  
  - 每个角的阶梯型去掉过程：用红色方块标记要去掉的格子，从外到内逐层减少（比如左上角，第一行去掉1个，第二行去掉2个，依此类推）。  
  - 关键操作音效：去掉一个格子时播放“叮”的声音，合并四个角时播放“嗡”的声音。  
  - 交互：支持“单步执行”（逐行去掉格子）和“自动播放”（快速展示整个过程）。  


## 2. 精选优质题解参考

### 题解一（来源：Hovery，赞：8）  
* **点评**：  
  这份题解的思路**非常清晰**，直接抓住了问题的核心——“矩形+四个角去掉多余格子”。作者提出“`a×b-n≤a`”的条件，确保去掉的格子不会超过矩形的一边，避免了复杂的边界处理。对于每个角的方案数，作者用分拆数DP（类似P1025）计算，然后用卷积合并四个角的方案数，算法有效性很高。代码结构规范，变量命名清晰（如`f[i]`表示一个角去掉i个格子的方案数），实践价值强。  

### 题解二（来源：Mine_King，赞：4）  
* **点评**：  
  题解详细解释了DP的转移方程（`dp[i][j] = dp[i-1][j-1] + dp[i][j-i]`），让学习者能理解分拆数的计算逻辑。作者还提到“空格数不超过长宽的较小值”，避免了重复计算，优化了效率。代码中的预处理部分（`dp`、`f`数组）和卷积合并（`g`、`gg`数组）结构清晰，易于模仿。  

### 题解三（来源：zac2010，赞：3）  
* **点评**：  
  作者强调了“凸图形”的重要性，并用多次DP解决问题：第一次计算分拆数（`g[i][j]`），第二次求前缀和（`s[i]`），第三次用背包合并四个角的方案数（`f[i]`）。思路连贯，步骤明确。代码中的循环结构（如`L(i, 1, N)`表示从1到N的循环）符合竞赛编程的规范，可读性强。  


## 3. 核心难点辨析与解题策略

### 1. 关键点1：如何找到最优矩形的长和宽？  
* **分析**：  
  矩形的周长`2(a+b)`最小当且仅当`a`和`b`尽可能接近`√n`。因此，枚举`a`从`max(1, √n-100)`到`min(n, √n+100)`，计算对应的`b=(n+a-1)/a`（向上取整），找到使`a+b`最小的组合。  
* 💡 **学习笔记**：枚举根号附近的数，可以快速找到最优解，避免遍历所有可能的`a`。  

### 2. 关键点2：如何计算每个角的阶梯型去掉方案数？  
* **分析**：  
  阶梯型去掉的格子数是一个**单调不降的序列**（比如第一行去掉1个，第二行去掉2个，总和为k）。用`dp[i][j]`表示总和为i、分成j个单调不降的数的方案数，转移方程为`dp[i][j] = dp[i-1][j-1] + dp[i-j][j]`（前者表示新增一个1，后者表示所有数加1）。然后`f[i] = sum(dp[i][j])`（j从1到i）表示一个角去掉i个格子的方案数。  
* 💡 **学习笔记**：分拆数DP是处理单调序列问题的常用方法，记住转移方程可以快速解决类似问题。  

### 3. 关键点3：如何合并四个角的方案数？  
* **分析**：  
  四个角的去掉方式独立，因此合并方案数相当于**四个`f`数组的卷积**（即求`f*f*f*f`）。由于`k=a×b-n`很小（根号级别），可以用暴力卷积（三重循环）计算，时间复杂度可行。  
* 💡 **学习笔记**：独立事件的方案数合并，常用卷积（背包问题）解决，暴力卷积适用于小规模数据。  

### ✨ 解题技巧总结  
- **枚举优化**：对于求极值的问题，枚举根号附近的数可以减少计算量。  
- **分拆数DP**：处理单调序列的方案数问题，记住经典转移方程。  
- **卷积合并**：独立事件的方案数合并，用背包卷积（暴力或FFT）。  


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考（来自Mine_King的题解）  
* **说明**：此代码综合了分拆数DP、预处理和卷积合并，是Type2询问的典型实现。  
* **完整核心代码**：  
  ```cpp
  #include <cmath>
  #include <cstdio>
  #include <iostream>
  #include <algorithm>
  using namespace std;

  int T, Type, n, mod;
  int dp[1005][1005], f[1005], g[1005], gg[1005];

  void solve2() {
      int len = 1;
      for (int i = max((int)sqrt(n) - 100, 1); i <= min((int)sqrt(n) + 100, n); i++)
          if (len + (n + len - 1) / len > i + (n + i - 1) / i) len = i;
      printf("%d ", (len + (n + len - 1) / len) * 2);
      int ans = 0;
      for (int r = max((int)sqrt(n) - 100, 1); r <= min((int)sqrt(n) + 100, n); r++) {
          if (len + (n + len - 1) / len != r + (n + r - 1) / r) continue;
          int c = (n + r - 1) / r;
          if (r > c) break;
          int k = r * c - n;
          ans = (ans + gg[k] * (r == c ? 1 : 2) % mod) % mod;
      }
      printf("%d\n", ans);
  }

  int main() {
      scanf("%d%d", &T, &Type);
      if (Type == 2) {
          scanf("%d", &mod);
          dp[0][0] = 1;
          for (int i = 1; i <= 1000; i++)
              for (int j = i; j <= 1000; j++) {
                  if (i == j) { dp[i][j] = 1; continue; }
                  dp[i][j] = dp[i-1][j-1];
                  if (j > i) dp[i][j] = (dp[i][j] + dp[i][j-i]) % mod;
              }
          for (int i = 1; i <= 1000; i++)
              for (int j = 1; j <= i; j++)
                  f[i] = (f[i] + dp[j][i]) % mod;
          for (int i = 0; i <= 1000; i++)
              for (int j = 0; j <= 1000; j++)
                  if (i + j <= 1000) g[i+j] = (g[i+j] + 1LL * f[i] * f[j] % mod) % mod;
          for (int i = 0; i <= 1000; i++)
              for (int j = 0; j <= 1000; j++)
                  if (i + j <= 1000) gg[i+j] = (gg[i+j] + 1LL * f[i] * g[j] % mod) % mod;
      }
      while (T--) {
          scanf("%d", &n);
          if (Type == 2) solve2();
      }
      return 0;
  }
  ```  
* **代码解读概要**：  
  1. **预处理**：计算`dp`数组（分拆数）、`f`数组（一个角的方案数）、`g`数组（两个角的方案数）、`gg`数组（四个角的方案数）。  
  2. **枚举矩形**：找到使周长最小的`r`和`c`，计算`k=r*c-n`。  
  3. **合并方案数**：用`gg[k]`计算四个角的方案数，乘以矩形的方向数（`r==c`时1种，否则2种）。  


### 题解一（来源：Hovery）核心代码片段  
* **亮点**：用分拆数DP计算一个角的方案数，思路清晰。  
* **核心代码片段**：  
  ```cpp
  int dp[1005][1005], f[1005];
  void init() {
      dp[0][0] = 1;
      for (int i = 1; i <= 1000; i++)
          for (int j = i; j <= 1000; j++) {
              if (i == j) dp[i][j] = 1;
              else dp[i][j] = (dp[i-1][j-1] + dp[i][j-i]) % mod;
          }
      for (int i = 1; i <= 1000; i++)
          for (int j = 1; j <= i; j++)
              f[i] = (f[i] + dp[j][i]) % mod;
  }
  ```  
* **代码解读**：  
  - `dp[i][j]`表示总和为`j`、分成`i`个单调不降的数的方案数。  
  - 转移方程`dp[i][j] = dp[i-1][j-1] + dp[i][j-i]`：`dp[i-1][j-1]`表示新增一个1，`dp[i][j-i]`表示所有数加1。  
  - `f[i]`是`dp[j][i]`的前缀和，表示一个角去掉`i`个格子的方案数。  
* 💡 **学习笔记**：分拆数DP的核心是转移方程，记住这个方程可以解决很多类似问题。  


## 5. 算法可视化：像素动画演示 (核心部分)

### 动画演示主题：像素矩形的“角切割”游戏  
**设计思路**：用8位像素风格模拟矩形的构造和四个角的切割过程，结合复古游戏元素（如音效、关卡），让学习者直观理解算法逻辑。  

### 动画帧步骤与交互关键点  
1. **场景初始化**：  
   - 屏幕显示一个`a×b`的绿色像素矩形（`a`和`b`是最优矩形的长和宽）。  
   - 控制面板有“开始”、“单步”、“重置”按钮，以及速度滑块。  
   - 播放8位风格的背景音乐（如《超级马里奥》的轻快旋律）。  

2. **矩形构造**：  
   - 从左上角开始，逐行填充绿色方块，直到形成`a×b`的矩形（伴随“填充”音效：每填充一个方块播放“滴”的声音）。  

3. **角切割过程**：  
   - 选择左上角作为第一个切割角，用红色方块标记要去掉的格子（阶梯型）：第一行去掉1个，第二行去掉2个，依此类推（伴随“切割”音效：每去掉一个方块播放“叮”的声音）。  
   - 切割完成后，左上角的红色方块消失，显示切割后的矩形（绿色方块）。  
   - 依次切割右上角、右下角、左下角，每个角的切割过程类似。  

4. **目标达成**：  
   - 四个角切割完成后，播放“胜利”音效（如《魂斗罗》的通关音乐），屏幕显示“完成！”的字样，并展示最终的凸图形（绿色方块）。  

5. **交互功能**：  
   - **单步执行**：点击“单步”按钮，逐行切割一个角的格子。  
   - **自动播放**：点击“开始”按钮，快速播放整个切割过程（速度可通过滑块调整）。  
   - **重置**：点击“重置”按钮，回到初始状态。  

### 旁白提示  
- “现在我们要构造一个`a×b`的矩形，这是周长最小的形状！”（矩形构造时）  
- “看，左上角的格子要被切割成阶梯型，这样才不会增加周长！”（切割时）  
- “四个角都切割完成了，最终的图形周长最小！”（完成时）  


## 6. 拓展练习与相似问题思考

### 通用思路/技巧迁移  
- **分拆数DP**：适用于处理单调序列的方案数问题（如洛谷P1025《数的划分》）。  
- **卷积合并**：适用于独立事件的方案数合并（如洛谷P2224《矩形周长》）。  
- **枚举优化**：适用于求极值的问题（如洛谷P3951《小凯的疑惑》）。  

### 练习推荐 (洛谷)  
1. **洛谷 P1025** - 数的划分  
   * 🗣️ **推荐理由**：这道题是分拆数DP的经典问题，能帮助你巩固`dp[i][j]`的转移方程。  
2. **洛谷 P2224** - 矩形周长  
   * 🗣️ **推荐理由**：这道题考察矩形周长的计算，能帮助你理解本题中矩形周长的最小化逻辑。  
3. **洛谷 P3951** - 小凯的疑惑  
   * 🗣️ **推荐理由**：这道题考察枚举优化，能帮助你掌握如何快速找到最优解。  


## 7. 学习心得与经验分享 (若有)  
**参考经验 (来自Mine_King)**：“我在解决这个问题时，最初在处理四个角的方案数合并时卡了很久，后来想到用卷积（背包）合并，才解决了问题。这让我意识到，独立事件的方案数合并，卷积是一个很好的工具。”  
**点评**：这位作者的经验很典型。在编程过程中，遇到独立事件的方案数合并问题，要想到用卷积（背包）解决。暴力卷积适用于小规模数据，FFT适用于大规模数据。  


## 结语  
本次关于“Laboratory on Pluto”的C++解题分析就到这里。希望这份学习指南能帮助大家更好地理解动态规划（分拆数）、枚举优化和卷积合并的技巧。记住，编程能力的提升在于持续学习、勤于思考和勇于实践。下次我们再一起探索新的编程挑战！💪

---
处理用时：148.44秒