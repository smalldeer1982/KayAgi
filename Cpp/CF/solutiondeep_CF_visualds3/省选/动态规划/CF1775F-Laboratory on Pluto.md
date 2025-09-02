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

<introduction>
今天我们来一起分析Codeforces 1775F「Laboratory on Pluto」这道C++编程题。这道题结合了**数学优化**、**动态规划**和**组合计数**，既需要用“数学脑”找最优形状，又需要用“DP脑”算方案数，非常锻炼综合能力。本指南会帮你一步步拆解问题，理解核心逻辑，还会用像素动画直观展示算法过程～
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学优化（均值不等式）+ 动态规划（整数分拆）+ 组合计数（背包卷积）

🗣️ **初步分析**：
解决这道题的关键，是先**找到周长最小的实验室形状**，再**计算这种形状的方案数**。我们可以把问题拆成两部分理解：

### 1.1 为什么最优形状是“接近正方形的矩形扣四个角”？
你肯定学过**均值不等式**：对于固定周长的矩形，边长越接近（越像正方形），面积越大。反过来，对于固定面积n的矩形，边长越接近，周长越小！比如n=7，最接近正方形的是3×3（面积9），扣掉2个格子，周长是(3+3)×2=12，比2×4（周长12，但扣掉1个格子）的方案数更多——这就是样例2中n=7输出周长12、方案数22的原因。

但直接用矩形的话，面积可能比n大（比如n=7用3×3，面积9），所以需要**从矩形的四个角扣掉多余的格子**。而且扣掉的格子必须是“阶梯状”（比如第一行扣1个，第二行扣2个，这样不会形成凹槽）——否则会增加周长，破坏“最小”的条件。

### 1.2 核心算法流程
1. **找最优矩形**：枚举接近$\sqrt{n}$的边长a，计算对应的另一边长b（满足a×b≥n，且a+b最小）。
2. **算单个角的方案数**：用动态规划计算“从一个角扣k个格子”的方案数（对应整数分拆问题）。
3. **合并四个角的方案数**：用背包卷积（类似“四个独立选择的组合”）计算总方案数。

### 1.3 可视化设计思路
我会用**8位像素风**（像FC红白机游戏）做动画：
- **场景**：屏幕左侧是一个黄色像素矩形（代表最优矩形），右侧是“DP状态面板”和“卷积计数器”。
- **关键动画**：
  - 矩形的四个角用蓝色闪烁，表示“可以扣掉”；
  - 单个角的阶梯状扣法：用像素块从角开始“逐层减少”，每减少一层播放“叮”的音效；
  - DP转移：用箭头连接“当前状态”和“下一个状态”，比如从dp[i-1][j-1]到dp[i][j]；
  - 卷积合并：四个角的方案数用不同颜色的进度条表示，合并时进度条“叠加”，播放“合并”音效。
- **交互**：支持“单步执行”（看每一步扣角/DP/卷积）、“自动播放”（快速过流程），还有“重置”按钮重新开始。


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性三个维度筛选了3份优质题解，帮你快速理解核心逻辑～
</eval_intro>

### 题解一：来源：Hovery（赞：8）
* **点评**：这份题解直接抓住了问题的“核心矛盾”——先找最优矩形，再算扣角方案数。作者用“枚举接近√n的a”快速定位最优矩形，然后把“扣角”转化为“整数分拆”（对应洛谷P1025），最后用“暴力卷积”合并四个角的方案数。思路像“剥洋葱”一样层层递进，而且提到“预处理f数组”优化时间，非常实用！

### 题解二：来源：Mine_King（赞：4）
* **点评**：这是最详细的题解之一！作者不仅画了示意图（虽然图炸了，但文字描述很清楚），还推导了DP转移方程：`dp[i][j] = dp[i-1][j-1] + dp[i][j-i]`（分别对应“加一个1”和“所有数加1”）。代码里的预处理和卷积步骤写得很规范，比如用`g`数组存单个角的方案数，`f`数组存卷积结果，非常适合初学者模仿。

### 题解三：来源：zac2010（赞：3）
* **点评**：这份题解的“模型转化”讲得特别好！作者明确指出“扣角的阶梯状对应整数分拆”，并把“四个角的组合”转化为“四次背包卷积”。代码里的`Init`函数预处理了所有需要的数组，`Solve2`函数直接枚举矩形计算答案，逻辑链非常清晰。而且作者提到“凸图形比凹图形优”，用例子（比如凹槽增加周长）帮你理解，很贴心～


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的难点在于“把实际问题转化为数学/DP模型”。结合优质题解，我帮你提炼了3个核心关键点和解决策略：
</difficulty_intro>

### 1. 关键点1：如何确定最优矩形的尺寸？
* **问题**：为什么要找接近$\sqrt{n}$的a和b？
* **分析**：根据均值不等式，a+b最小当且仅当a和b最接近。比如n=7，$\sqrt{7}≈2.64$，所以a=3，b=3（面积9≥7），此时a+b=6，周长12，是最小的。
* 💡 **学习笔记**：找最优矩形的关键是“枚举$\sqrt{n}$附近的a”，计算对应的b，取a+b最小的组合。

### 2. 关键点2：如何把“扣角方案数”转化为整数分拆？
* **问题**：为什么扣角的方案数等于“整数分拆数”？
* **分析**：扣角的阶梯状要求“每行扣的格子数单调不增”（比如第一行扣1个，第二行扣2个，第三行扣3个，总和是6）。这正好对应“将k拆分成若干正整数之和，且序列单调不增”的方案数——也就是整数分拆问题！
* 💡 **学习笔记**：遇到“阶梯状”“单调序列”的计数问题，先想整数分拆的DP模型。

### 3. 关键点3：如何合并四个角的方案数？
* **问题**：四个角的方案数为什么可以用背包卷积？
* **分析**：四个角是独立的（扣一个角不会影响其他角），所以总方案数是“四个角方案数的卷积”——比如总扣k个格子，等于第一个角扣a个，第二个扣b个，第三个扣c个，第四个扣d个，a+b+c+d=k，方案数是f[a]×f[b]×f[c]×f[d]的总和。这正好是背包问题的“多重选择合并”，用暴力卷积（因为k很小，只有√n级别）就能解决。
* 💡 **学习笔记**：独立事件的组合计数，优先考虑背包卷积（或生成函数）。

### ✨ 解题技巧总结
- **技巧1：数学优化优先**：遇到“最小周长”“最大面积”问题，先想均值不等式，找接近正方形的尺寸。
- **技巧2：模型转化**：把实际问题（扣角）转化为经典问题（整数分拆），减少思考量。
- **技巧3：预处理优化**：对于多次询问的问题，提前预处理DP数组和卷积结果，避免重复计算。


## 4. C++核心代码实现赏析

<code_intro_overall>
我们先看一份**综合优质题解的通用核心代码**，帮你把握整体框架。这份代码来自Mine_King的题解，调整后更简洁～
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：本代码综合了Mine_King和zac2010的思路，预处理了整数分拆的DP数组和四个角的卷积结果，支持Type 2的询问。
* **完整核心代码**：
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1005;
int dp[MAX][MAX], f[MAX], g[MAX], gg[MAX];
int T, Type, n, mod;

void preprocess() {
    // 预处理整数分拆的DP数组：dp[i][j]表示长度为i，总和为j的方案数
    dp[0][0] = 1;
    for (int i = 1; i < MAX; ++i) {
        for (int j = i; j < MAX; ++j) {
            dp[i][j] = (dp[i-1][j-1] + (j > i ? dp[i][j-i] : 0)) % mod;
        }
    }
    // 计算单个角的方案数f[i]：总和为i的所有长度的方案数之和
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j <= i; ++j) {
            f[i] = (f[i] + dp[j][i]) % mod;
        }
    }
    // 卷积合并四个角的方案数：gg[i] = f*f*f*f的卷积结果
    memset(g, 0, sizeof(g));
    g[0] = 1;
    for (int k = 0; k < 4; ++k) { // 合并4次f数组
        memset(gg, 0, sizeof(gg));
        for (int i = 0; i < MAX; ++i) {
            for (int j = 0; j + i < MAX; ++j) {
                gg[i+j] = (gg[i+j] + 1LL * g[i] * f[j]) % mod;
            }
        }
        memcpy(g, gg, sizeof(g));
    }
}

void solve2() {
    int best_a = 1;
    // 找接近sqrt(n)的a，使得a + ((n+a-1)/a)最小
    for (int i = max(1, (int)sqrt(n)-100); i <= min(n, (int)sqrt(n)+100); ++i) {
        int b1 = (n + best_a - 1) / best_a;
        int b2 = (n + i - 1) / i;
        if (best_a + b1 > i + b2) {
            best_a = i;
        }
    }
    int best_b = (n + best_a - 1) / best_a;
    int min_perim = 2 * (best_a + best_b);
    int ans = 0;
    // 枚举所有可能的a（满足a+b等于best_a+best_b），计算方案数
    for (int a = max(1, (int)sqrt(n)-100); a <= min(n, (int)sqrt(n)+100); ++a) {
        int b = (n + a - 1) / a;
        if (a + b != best_a + best_b) continue;
        int k = a * b - n; // 需要扣掉的总格子数
        if (k < 0) continue;
        ans = (ans + (a == b ? 1 : 2) * 1LL * gg[k]) % mod;
    }
    printf("%d %d\n", min_perim, ans);
}

int main() {
    scanf("%d%d", &T, &Type);
    if (Type == 2) {
        scanf("%d", &mod);
        preprocess();
    }
    while (T--) {
        scanf("%d", &n);
        if (Type == 2) solve2();
        // Type 1的代码可以参考Mine_King的solve1函数，这里省略
    }
    return 0;
}
```
* **代码解读概要**：
  1. **preprocess函数**：预处理整数分拆的DP数组（dp）、单个角的方案数（f）、四个角的卷积结果（gg）。
  2. **solve2函数**：找最优矩形的a和b，计算最小周长，然后枚举所有可能的a（满足a+b最小），计算对应的方案数（用预处理好的gg数组）。

<code_intro_selected>
接下来我们剖析**Mine_King题解中的核心代码片段**，看看DP转移和卷积是怎么实现的～
</code_intro_selected>

### 题解二：来源：Mine_King
* **亮点**：用简洁的DP转移方程实现整数分拆，用暴力卷积合并四个角的方案数。
* **核心代码片段（DP转移）**：
```cpp
dp[0][0] = 1;
for (int i = 1; i <= 1000; ++i) {
    for (int j = i; j <= 1000; ++j) {
        if (i == j) {
            dp[i][j] = 1;
            continue;
        }
        dp[i][j] = dp[i-1][j-1]; // 加一个1
        if (j > i) dp[i][j] = (dp[i][j] + dp[i][j-i]) % mod; // 所有数加1
    }
}
```
* **代码解读**：
  - `dp[i][j]`表示“把j拆成i个正整数，且单调不增”的方案数。
  - 第一个转移`dp[i-1][j-1]`：在之前的i-1个数前面加一个1（比如[1,2]变成[1,1,2]，总和从3变成4）。
  - 第二个转移`dp[i][j-i]`：把之前的i个数每个都加1（比如[1,2]变成[2,3]，总和从3变成5）。
  - 为什么这样是对的？因为单调不增的序列可以通过这两种操作生成所有可能的分拆！
* 💡 **学习笔记**：整数分拆的DP转移要抓住“生成所有可能序列”的两种方式，这样写既简洁又正确。

### 题解二：来源：Mine_King
* **亮点**：用暴力卷积合并四个角的方案数，适合小数据量的情况。
* **核心代码片段（卷积合并）**：
```cpp
// 合并4次f数组：g = f*f*f*f
memset(g, 0, sizeof(g));
g[0] = 1;
for (int k = 0; k < 4; ++k) {
    memset(gg, 0, sizeof(gg));
    for (int i = 0; i <= 1000; ++i) {
        for (int j = 0; j + i <= 1000; ++j) {
            gg[i+j] = (gg[i+j] + 1LL * g[i] * f[j]) % mod;
        }
    }
    memcpy(g, gg, sizeof(g));
}
```
* **代码解读**：
  - 初始时`g[0] = 1`（表示“没有扣任何角”的方案数是1）。
  - 每次循环合并一个f数组（对应一个角的方案数）：`gg[i+j]`表示“前k个角扣i个，第k+1个角扣j个”的总方案数，等于`g[i] * f[j]`的总和。
  - 合并4次后，`g[k]`就是“四个角总共扣k个格子”的方案数！
* 💡 **学习笔记**：暴力卷积的时间复杂度是O(k²)（k是最大扣格子数，约√n），对于n≤1e5来说，k≤300，完全没问题～


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了帮你直观理解“整数分拆”和“卷积合并”的过程，我设计了一个**8位像素风动画**，像玩FC游戏一样学算法！
</visualization_intro>

### 动画演示主题
**像素实验室：扣角大挑战**——你是一个“实验室设计师”，需要从黄色矩形的四个角扣掉多余的格子，同时保持周长最小。

### 核心演示内容
1. **场景初始化**：
   - 屏幕左侧是一个3×3的黄色像素矩形（代表n=7的最优矩形），右侧是“DP面板”和“卷积计数器”。
   - 控制面板有“单步”“自动”“重置”按钮，还有速度滑块（从“慢”到“快”）。
   - 背景播放8位风格的轻松BGM（比如《超级马里奥》的背景音乐）。

2. **整数分拆DP演示**：
   - 点击“单步”，DP面板上会出现`dp[1][1] = 1`（表示“拆1个1”的方案数是1）。
   - 再点“单步”，`dp[2][3] = dp[1][2] + dp[2][1]`（哦，`dp[2][1]`不存在，所以等于`dp[1][2] = 1`）——这对应“拆3为[1,2]”的方案数。
   - 每一步转移都会有**像素箭头**从“前一个状态”指向“当前状态”，同时播放“叮”的音效。

3. **扣角动画**：
   - 点击“自动”，矩形的左上角开始“扣掉”格子：第一行扣1个（蓝色像素块消失），第二行扣2个（两个蓝色像素块消失）——总和是3，对应`f[3] = 2`（方案数是2）。
   - 扣掉的格子会变成“透明”，同时右侧的“卷积计数器”会显示当前扣的格子数（比如3）。

4. **卷积合并演示**：
   - 四个角的方案数分别用红、绿、蓝、黄四个进度条表示。
   - 合并时，进度条会“叠加”：比如红色进度条到3（第一个角扣3），绿色到2（第二个角扣2），蓝色到1（第三个角扣1），黄色到0（第四个角扣0），总和是6——对应的方案数是`f[3] * f[2] * f[1] * f[0] = 2*2*1*1=4`，会显示在“总方案数”面板上。

5. **目标达成**：
   - 当总扣格子数等于`a*b -n`（比如3×3-7=2）时，矩形会“闪烁”，播放“胜利”音效（比如《魂斗罗》的过关音乐），同时显示“方案数：22”（对应样例2的n=7）。

### 设计思路
- **8位像素风**：用简单的颜色和形状降低认知负担，让你专注于算法逻辑。
- **音效提示**：关键操作（比如DP转移、扣角、卷积合并）用不同的音效强化记忆，比如“叮”对应DP转移，“啪”对应扣角，“嗡”对应卷积合并。
- **游戏化交互**：用“单步”“自动”按钮让你控制节奏，用“进度条”和“计数器”直观展示数据变化，增加学习的趣味性。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
这道题的核心是“数学优化+整数分拆+背包卷积”，这些技巧可以迁移到很多问题中。比如：
</similar_problems_intro>

### 通用思路/技巧迁移
1. **数学优化**：求“最小周长”“最大面积”的问题，优先用均值不等式找接近正方形的尺寸（比如洛谷P1002的“过河卒”问题，虽然不是同一类，但思路类似）。
2. **整数分拆**：遇到“阶梯状”“单调序列”的计数问题，用DP求分拆数（比如洛谷P1025的“数的划分”）。
3. **背包卷积**：独立事件的组合计数，用暴力卷积或生成函数（比如洛谷P1466的“集合划分”）。

### 练习推荐 (洛谷)
1. **洛谷 P1025** - 数的划分  
   🗣️ **推荐理由**：这是整数分拆的经典题，直接对应本题的“扣角方案数”计算，帮你巩固DP转移方程。
2. **洛谷 P1466** - 集合划分  
   🗣️ **推荐理由**：这道题需要用生成函数求组合计数，类似本题的“四个角方案数合并”，帮你理解卷积的应用。
3. **洛谷 P2347** - 砝码称重  
   🗣️ **推荐理由**：这是背包问题的变形，帮你练习“状态转移”和“预处理优化”，和本题的卷积合并思路一致。
4. **洛谷 P3951** - 小凯的疑惑  
   🗣️ **推荐理由**：这是数学优化的题，帮你练习“用均值不等式找最优解”，和本题的“找最优矩形”思路一致。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
很多作者在题解中分享了自己的解题心得，比如：
</insights_intro>

> **参考经验 (来自 Priestess_SLG)**：“这是我第一次打现场CF的2500分题，一开始没想到扣角的方案数是整数分拆，后来画了个图才想通——阶梯状的扣法正好对应分拆数！”
>
> **点评**：这位作者的经验很真实！遇到复杂问题时，**画图**是最好的工具——把抽象的“扣角”变成具体的“阶梯状”，瞬间就能和经典问题（整数分拆）联系起来。

> **参考经验 (来自 Mine_King)**：“一开始我用了FFT做卷积，但后来发现k很小（只有√n级别），暴力卷积更快更简单！”
>
> **点评**：这提醒我们，**不要盲目用高级算法**——对于小数据量，暴力方法往往更高效、更易写！


<conclusion>
本次关于「Laboratory on Pluto」的分析就到这里啦！这道题把数学、DP、组合计数结合在一起，非常锻炼综合能力。记住：**遇到问题先拆分成小部分，再找经典模型，最后用预处理优化**——这是解决复杂算法题的通用思路～

下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：129.94秒