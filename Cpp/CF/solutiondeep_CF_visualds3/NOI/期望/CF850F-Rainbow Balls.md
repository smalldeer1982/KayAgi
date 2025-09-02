# 题目信息

# Rainbow Balls

## 题目描述

You have a bag of balls of $ n $ different colors. You have $ a_{i} $ balls of the $ i $ -th color.

While there are at least two different colored balls in the bag, perform the following steps:

- Take out two random balls without replacement one by one. These balls might be the same color.
- Color the second ball to the color of the first ball. You are not allowed to switch the order of the balls in this step.
- Place both balls back in the bag.
- All these actions take exactly one second.

Let $ M=10^{9}+7 $ . It can be proven that the expected amount of time needed before you stop can be represented as a rational number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/2c40be71c60fe708ee9e4e80e2cd7a26163f3bd6.png), where $ P $ and $ Q $ are coprime integers and where $ Q $ is not divisible by $ M $ . Return the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/a816c54f8859ee12f4e38a2cc4dba0d6f8dd5c0b.png).

## 说明/提示

In the first sample, no matter what happens, the balls will become the same color after one step.

For the second sample, we have 6 balls. Let’s label the balls from 1 to 6, and without loss of generality, let’s say balls 1,2,3 are initially color 1, balls 4,5 are color 2, and ball 6 are color 3.

Here is an example of how these steps can go:

- We choose ball 5 and ball 6. Ball 6 then becomes color 2.
- We choose ball 4 and ball 5. Ball 5 remains the same color (color 2).
- We choose ball 1 and ball 5. Ball 5 becomes color 1.
- We choose ball 6 and ball 5. Ball 5 becomes color 2.
- We choose ball 3 and ball 4. Ball 4 becomes color 1.
- We choose ball 4 and ball 6. Ball 6 becomes color 1.
- We choose ball 2 and ball 5. Ball 5 becomes color 1.

 At this point, the game ends since all the balls are the same color. This particular sequence took 7 seconds.It can be shown that the answer to this case is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/9f76609d2f8aa0999ab074d70f32e2692cee15a9.png).

## 样例 #1

### 输入

```
2
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
750000026
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Rainbow Balls 深入学习指南 💡

<introduction>
今天我们来一起分析「Rainbow Balls」这道C++编程题。这道题看起来是关于“随机操作的期望步数”，但其实藏着**概率期望与动态规划**的巧妙结合。本指南会帮你梳理思路、理解核心算法，并通过像素动画直观感受过程！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（概率期望DP）

🗣️ **初步分析**：
你可以把每个颜色的球想象成一个“小国家”，每个国家的“人口”是球的数量。我们的目标是计算每个国家从初始人口发展到“统治全球”（所有球都是它的颜色）的期望时间，再根据每个国家“统治成功”的概率加权求和——这就是最终的期望操作次数。

### 核心算法的比喻解释
动态规划（DP）就像“预言家”：它通过“现在的状态”预测“未来的期望”。在本题中，我们用`f[i]`表示“某国家有`i`个球时，统治全球的期望时间”。因为每个国家的发展是独立的（只和自己的数量有关），我们可以先算每个`f[i]`，再用“每个国家初始人口的`f`值×它统治成功的概率”求和，得到答案。

### 题解思路与核心难点
- **题解思路**：所有优质题解的核心都是推导`f[i]`的递推式：`f[i+1] = 2f[i] - f[i-1] - (s-1)/(s-i)`（`s`是总球数），并通过边界条件`f[s]=0`求出`f[1]=(s-1)²/s`，再递推所有`f[i]`。
- **核心难点**：
  1. 如何处理“某颜色数量降到0就失败”的边界？→ 用**条件概率**，只考虑该颜色最终获胜的路径（即不降到0的路径）。
  2. 状态转移中的“有效贡献”是什么？→ 不是1！而是当前状态下该颜色最终获胜的概率`v=i/s`（因为只有获胜的路径才对期望有贡献）。
  3. 如何求出`f[1]`的初始值？→ 联立递推式和`f[s]=0`，解出`f[1]`。
- **可视化设计思路**：用像素块表示球的数量，动态展示`i`的变化（比如`i`从`a_i`增长到`s`），高亮当前计算的`f[i]`，用颜色变化表示递推的依赖关系（比如`f[i]`依赖`f[i-1]`和`f[i+1]`）。

### 复古像素动画的小预告
我们会做一个**FC红白机风格**的动画：
- 屏幕左侧是“颜色势力榜”：用不同颜色的像素块堆叠表示每个颜色的当前数量。
- 中间是“操作区”：随机闪烁两个像素块（代表选球），然后第二个块的颜色变成第一个（颜色渐变动画）。
- 右侧是“DP面板”：显示当前的`i`、`f[i]`和递推式，高亮正在计算的项。
- 控制面板有“单步”“自动播放”“重置”按钮，还有速度滑块——就像玩《超级马里奥》一样操作算法！


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、推导严谨性等角度，筛选了3份优质题解，帮你快速掌握核心！
</eval_intro>

**题解一：DeaphetS（条件概率推导）**
* **点评**：这份题解用**条件概率**完美解决了“边界不能到0”的问题。作者先推导弱化版（每种颜色初始1个球），再推广到原题，逻辑链非常清晰。特别是对`P(x_{k+1}=i-1|x_k=i,F_1)`的推导，把“条件概率”的本质讲透了——只关注“该颜色最终获胜”的路径，排除了失败的可能。

**题解二：樱雪喵（简洁递推实现）**
* **点评**：此题解的代码堪称“教科书级简洁”！作者直接抓住递推式`f[i+1] = 2f[i] - f[i-1] - (s-1)/(s-i)`，用`f[1]=(s-1)²/s`作为初始值，递推所有`f[i]`。代码结构清晰，变量命名直观（比如`sum`是总球数，`f`数组存期望时间），非常适合新手模仿。

**题解三：Soulist（势能函数方法）**
* **点评**：这是一份“理论派”题解！作者用**势能函数**（把整个局面的“能量”定义为`∑f(a_i)`）推导状态转移，从更抽象的角度证明了递推式的正确性。虽然理论性强，但能帮你理解“为什么递推式是这样的”——就像知道了“游戏规则的底层逻辑”！


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的“拦路虎”主要是3个问题，解决它们就能打通思路！
</difficulty_intro>

### 1. 难点：如何处理“某颜色数量降到0”的边界？
- **分析**：如果某颜色数量变成0，就永远无法获胜，所以这些路径不能算入期望。
- **解决策略**：用**条件概率**（比如`E(N_i|F_j)`表示“在颜色j最终获胜的条件下，当前数量为i的期望时间”），只考虑“不会降到0”的路径。

### 2. 难点：状态转移中的“有效贡献”为什么不是1？
- **分析**：每次操作的“有效贡献”不是“1步”，而是“这步操作对最终答案的贡献概率”——因为只有当该颜色最终获胜时，这步操作才算“有效”。
- **解决策略**：通过概率DP推导`v=i/s`（`v`是当前状态下该颜色最终获胜的概率），所以转移式中的贡献是`v`而不是1。

### 3. 难点：如何求出`f[1]`的初始值？
- **分析**：递推式需要初始值，但`f[0]`无意义，`f[s]=0`是边界，所以需要联立方程求解`f[1]`。
- **解决策略**：利用递推式`f[i+1] = 2f[i] - f[i-1] - (s-1)/(s-i)`和`f[s]=0`，代入`i=1`到`i=s-1`，联立解得`f[1]=(s-1)²/s`。

### ✨ 解题技巧总结
- **技巧A：条件概率缩小区间**：当边界状态无法处理时，用条件概率只关注“有效路径”，排除无效情况。
- **技巧B：概率DP求有效贡献**：对于期望问题，“每一步的贡献”往往不是1，而是当前状态下“目标达成的概率”。
- **技巧C：联立边界求初始值**：递推式需要初始值时，利用边界条件（比如`f[s]=0`）联立方程，避免“凭空假设”。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**通用核心实现**，它综合了优质题解的思路，代码简洁，容易理解！
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：本代码来自樱雪喵的题解，调整了变量命名，增加了注释，更适合新手阅读。
* **完整核心代码**：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX_A = 1e5 + 5;

long long qpow(long long base, int exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

long long inv(long long x) {
    return qpow(x, MOD - 2); // 费马小定理求逆元
}

int main() {
    int n;
    cin >> n;
    int a[2505]; // 颜色数量不超过2500
    long long sum = 0;
    int max_a = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
        if (a[i] > max_a) max_a = a[i];
    }

    long long f[MAX_A]; // f[i]表示有i个球时的期望时间
    // 计算f[1]：(sum-1)^2 / sum
    f[1] = ((sum - 1) % MOD) * ((sum - 1) % MOD) % MOD;
    f[1] = f[1] * inv(sum % MOD) % MOD;
    // 计算f[2]：2*f[1] - 1
    f[2] = (2 * f[1] - 1 + MOD) % MOD; // +MOD避免负数

    // 递推f[3]到f[max_a]
    for (int i = 2; i < max_a; ++i) {
        // f[i+1] = 2*f[i] - f[i-1] - (sum-1)/(sum - i)
        long long term1 = (2 * f[i]) % MOD;
        long long term2 = f[i-1];
        long long term3 = ((sum - 1) % MOD) * inv((sum - i) % MOD) % MOD;
        f[i+1] = (term1 - term2 - term3 + 2 * MOD) % MOD; // +2*MOD确保非负
    }

    // 计算答案：sum(f[a[i]])
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = (ans + f[a[i]]) % MOD;
    }
    cout << ans << endl;

    return 0;
}
```
* **代码解读概要**：
  1. **输入处理**：读取颜色数量`n`，每个颜色的初始球数`a[i]`，计算总球数`sum`和最大初始数量`max_a`。
  2. **初始化f数组**：用费马小定理求逆元，计算`f[1]`（初始值）和`f[2]`。
  3. **递推f数组**：根据递推式计算`f[3]`到`f[max_a]`，注意取模避免负数。
  4. **计算答案**：累加每个颜色初始数量对应的`f[a[i]]`，输出结果。


<code_intro_selected>
接下来剖析优质题解的核心片段，看看它们的“巧思”！
</code_intro_selected>

**题解一：DeaphetS（条件概率推导）**
* **亮点**：用条件概率公式推导`P(x_{k+1}=i-1|x_k=i,F_1)`，解决边界问题。
* **核心代码片段**：
```cpp
// 计算条件概率P(x_{k+1}=i-1 | x_k=i, F_1)
long long calc_P(int i, long long sum) {
    // 公式：(n-i)*(i-1)/(n*(n-1)) （n是sum）
    long long numerator = ((sum - i) % MOD) * ((i - 1) % MOD) % MOD;
    long long denominator = (sum % MOD) * ((sum - 1) % MOD) % MOD;
    return numerator * inv(denominator) % MOD;
}
```
* **代码解读**：
  这个函数计算的是“在颜色1最终获胜的条件下，数量从i降到i-1的概率”。公式来自条件概率的推导——分子是“选到一个颜色1的球和一个其他颜色的球，且其他颜色的球变成颜色1”的情况数，分母是总情况数。**为什么要算这个？**因为递推式中的转移概率是“条件概率”，不是原始概率！
* **学习笔记**：条件概率是处理“边界无效状态”的利器，关键是“缩小样本空间到有效路径”。

**题解二：樱雪喵（简洁递推）**
* **亮点**：直接用递推式计算，代码无冗余。
* **核心代码片段**：
```cpp
for (int i = 2; i < mx; ++i) {
    f[i+1] = ((2*f[i]%mod - f[i-1] - (s-1)*inv(s-i)%mod) % mod + mod) % mod;
}
```
* **代码解读**：
  这行代码就是递推式的直接实现！`2*f[i]`是递推式的第一项，`-f[i-1]`是第二项，`-(s-1)*inv(s-i)`是第三项（`inv`是逆元）。`+mod`再取模是为了避免结果变成负数——这是模运算的常见技巧！
* **学习笔记**：递推式的代码实现要“精准对应公式”，避免多余的计算。

**题解三：Soulist（势能函数）**
* **亮点**：用势能函数推导递推式，理论严谨。
* **核心代码片段**：
```cpp
// 势能函数f(x)的递推：f(x+1) - 2f(x) + f(x-1) = -(sum-1)/(sum - x)
for (int i = 1; i <= mx; ++i) {
    inv[i] = inv[i-1] + inv(sum - i + 1); // 预处理逆元前缀和
}
f[x] = (sum-1) * (sum - x) % mod * inv[x-1] % mod;
```
* **代码解读**：
  作者用**二阶差分**（`f(x+1)-2f(x)+f(x-1)`）推导势能函数的递推式，然后通过前缀和预处理逆元，快速计算`f(x)`。这种方法的优势是**更抽象，更通用**——可以推广到类似的期望问题！
* **学习笔记**：势能函数是解决“随机过程期望”的高级技巧，当递推式复杂时，不妨试试“能量守恒”的思路。


## 5. 算法可视化：像素动画演示

<visualization_intro>
我们设计了一个**FC红白机风格的像素动画**，让算法“动起来”！就像玩《俄罗斯方块》一样，你可以操作算法的每一步，直观感受DP的递推过程。
</visualization_intro>

### 🌟 动画主题：《颜色帝国的崛起》
- **核心演示内容**：展示一个颜色从初始数量`a_i`发展到`sum`的过程，同时显示DP递推式的计算。
- **设计思路**：用8位像素风格营造复古氛围，用“游戏化操作”降低学习门槛——就像玩游戏一样学算法！

### 🎮 动画细节设计
#### 1. 场景与UI初始化（FC风格）
- **屏幕布局**：
  - 左侧（20%宽度）：颜色势力榜——每个颜色用不同颜色的像素块堆叠（比如红色代表颜色1，蓝色代表颜色2），显示当前数量。
  - 中间（60%宽度）：操作区——随机闪烁两个像素块（代表选球），然后第二个块的颜色变成第一个（颜色渐变动画，比如从蓝色变成红色）。
  - 右侧（20%宽度）：DP面板——显示当前的`i`（数量）、`f[i]`（期望时间）和递推式`f[i+1] = 2f[i] - f[i-1] - (s-1)/(s-i)`，高亮正在计算的项（比如`f[i+1]`用黄色闪烁）。
- **控制面板**：
  - 底部有“开始/暂停”“单步”“重置”按钮（像素风格，比如用白色方块加黑色边框）。
  - 速度滑块：从“慢”（1帧/秒）到“快”（10帧/秒），调整动画速度。
  - 背景音乐：循环播放8位风格的《超级马里奥》背景音乐（轻快，不会分心）。

#### 2. 算法启动与数据初始化
- 点击“开始”按钮：
  - 颜色势力榜的像素块初始化（比如颜色1有`a_1`个红色块，颜色2有`a_2`个蓝色块……）。
  - DP面板显示`i=1`，`f[1]=(s-1)²/s`，递推式高亮`f[1]`。
  - 播放“叮”的音效（表示算法启动）。

#### 3. 核心算法步骤演示
- **单步操作**：
  1. 操作区随机闪烁两个像素块（比如红色和蓝色）——代表选球。
  2. 第二个块的颜色渐变（比如蓝色变成红色）——代表“涂色”操作。
  3. 颜色势力榜的红色块数量+1，蓝色块数量-1——更新数量。
  4. DP面板更新`i`（比如从1变成2），计算`f[2]`（`2*f[1]-1`），高亮`f[2]`。
  5. 播放“啪”的音效（表示操作完成）。
- **自动播放**：
  - 按设定的速度重复单步操作，直到某颜色的数量达到`sum`（全屏幕变成该颜色）。
  - 当数量达到`sum`时，播放“胜利音效”（比如《超级马里奥》的通关音乐），并弹出“恭喜！该颜色统治全球！”的像素文字。

#### 4. 交互与控制
- **重置**：点击后回到初始状态，所有像素块恢复初始数量，DP面板重置为`i=1`。
- **速度滑块**：拖动滑块调整自动播放的速度——慢速度适合仔细观察，快速度适合看整体流程。

#### 5. 技术实现（轻量化）
- **技术栈**：纯HTML+CSS+JavaScript（Canvas API），单文件实现（比如`rainbow_balls.html`），无需安装任何软件，直接用浏览器打开。
- **像素绘制**：用`ctx.fillRect(x, y, 8, 8)`绘制8x8的像素块（FC风格的标准像素大小）。
- **音效**：用`Web Audio API`播放8位音效（比如从[Free 8-bit Sound Effects](https://freesound.org/tag:8bit/)下载）。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了这道题的思路，你可以挑战以下相似问题，巩固所学！
</similar_problems_intro>

### 🎯 通用思路迁移
本题的核心思路是**“概率期望+动态规划”**，适用于所有“随机操作的期望步数”问题，比如：
1. 随机游走问题（从起点到终点的期望步数）。
2. 卡牌收集问题（收集所有卡牌的期望抽卡次数）。
3. 病毒传播问题（所有节点被感染的期望时间）。

### 📚 拓展练习推荐（洛谷）
1. **P5516 题**：和本题几乎一样，只是输入格式略有不同——直接用本题的代码就能AC！
2. **P2554 颜色**：本题的弱化版（每种颜色初始1个球），可以用本题的思路快速解决。
3. **P6835 随机游走**：经典的随机游走期望问题，用类似的DP递推式求解。
4. **P1365 WJMZBMR打osu!**：另一种期望DP问题，需要计算“连续长度的期望平方”——锻炼你的期望推导能力！


## 7. 学习心得与经验分享 (若有)

<insights_intro>
很多题解作者分享了自己的推导心得，比如：
</insights_intro>

> **参考经验（来自DeaphetS）**：“我一开始卡在‘边界条件’，后来想到用条件概率缩小区间，只考虑有效路径，问题就解决了。”
> **点评**：这是非常典型的“思维转换”——当直接处理所有路径有困难时，不妨“聚焦有效路径”，排除无效情况。

> **参考经验（来自樱雪喵）**：“递推式的代码实现要注意模运算的负数问题，一定要+MOD再取模！”
> **点评**：模运算的负数处理是OI中的常见坑，作者的经验能帮你避免调试时的“奇怪错误”。


<conclusion>
本次关于「Rainbow Balls」的分析就到这里！这道题的核心是**概率期望与动态规划的结合**，关键是要理解“有效贡献”和“条件概率”的应用。记住：算法不是“魔法”，而是“逻辑的延伸”——只要把问题拆分成小步骤，逐一解决，再难的题也能拿下！

下次我们再一起探索更有趣的算法问题，比如“图论中的最短路径”或者“字符串的匹配算法”——不见不散！💪
</conclusion>

---

---
处理用时：137.99秒