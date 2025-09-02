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

# 💡 Kay的C++算法解析：Rainbow Balls 深入学习指南 💡

## 引言
今天我们要分析的问题是「Rainbow Balls」——一个关于**期望操作次数**的编程题。这个问题需要我们计算将袋子里的所有球变成同一种颜色的平均时间，核心是利用**动态规划（DP）**结合**数学推导**解决期望问题。让我们一起拆解它吧！


## 1. 题目解读与核心算法识别

### ✨ 本题主要考察：动态规划（DP）与数学期望推导
动态规划（DP）的核心思想是**「用子问题的解构建原问题的解」**——就像爬楼梯时，第10级的步数等于第9级或第8级的步数之和。在本题中，我们需要计算「有`i`个目标颜色球时，将所有球变成该颜色的期望步数」（记为`f_i`），而`f_i`的解依赖于`f_{i-1}`（少一个目标球）和`f_{i+1}`（多一个目标球）的结果。


### 🗣️ 初步分析
1. **问题拆解**：所有题解的核心思路一致——将问题拆解为「每种颜色留到最后的期望步数」，再乘以该颜色留到最后的概率（`p_i = i/s`，`s`是总球数），最后求和得到答案。
2. **核心难点**：
   - 如何处理「颜色数为0」的无效状态？（一旦目标颜色数为0，就无法再变成该颜色）
   - 如何推导正确的状态转移方程？
3. **解决方案**：
   - 引入概率`g_i`（目标颜色留到最后的概率），将转移方程中的「贡献」从1改为`g_i`，避开无效状态。
   - 利用等差数列性质（`g_i = i/s`）简化推导，得到`f_i`的递推式：`f_{i+1} = 2f_i - f_{i-1} - (s-1)/(s-i)`。
4. **可视化设计思路**：
   - 用**8位像素风格**展示袋子里的小球，目标颜色的小球用红色高亮，数量变化时播放「叮」（增加）或「咔」（减少）的音效。
   - 控制面板包含「单步执行」「自动播放」「重置」按钮，自动播放时像「贪吃蛇AI」一样逐步完成递推，每一步对应代码中的一行（如计算`f_{i+1}`）。


## 2. 精选优质题解参考

### 题解一：DeaphetS（5星）
- **点评**：这道题解的推导过程**极其详细**，从符号约定到弱化版本的分析，再到原问题的解决，每一步都有严谨的数学证明。代码风格规范，变量名（如`f_i`、`P_{i,j}`）清晰对应推导中的符号，非常适合初学者理解。亮点是**将问题拆解为弱化版本**，降低了理解门槛。

### 题解二：樱雪喵（5星）
- **点评**：代码**简洁高效**，推导过程直击要害——通过引入`g_i`（留到最后的概率），快速将转移方程中的贡献改为`g_i`，避免了无效状态。代码中的`inv`函数（求逆元）和`f`数组的递推逻辑非常清晰，是「理论推导→代码实现」的完美范例。

### 题解三：Leasier（5星）
- **点评**：思路**直截了当**，从「n=2的简化问题」入手，逐步推导到原问题。亮点是**利用差分求和**快速求出`f_1`的值（`f_1 = (s-1)^2/s`），并给出了清晰的递推式。代码中的`quick_pow`函数和`f`数组的计算逻辑非常易读。


## 3. 核心难点辨析与解题策略

### 1. 难点1：处理「颜色数为0」的无效状态
- **分析**：如果直接定义`f_i`为「有`i`个目标球的期望步数」，当`i=0`时，`f_0`是无穷大（无法再变成目标颜色），无法参与计算。
- **解决方案**：引入概率`g_i`（目标颜色留到最后的概率），将转移方程中的「贡献」从1改为`g_i`（只有当目标颜色能留到最后时，这一步才有效）。`g_i`是等差数列，`g_i = i/s`，完美避开无效状态。


### 2. 难点2：推导状态转移方程
- **分析**：直接推导`f_i`的转移方程会涉及「无效状态」和「概率权重」，容易出错。
- **解决方案**：利用**期望的线性性质**，将总期望拆解为「每种颜色留到最后的期望×概率」，再通过数学推导得到`f_i`的递推式：`f_{i+1} = 2f_i - f_{i-1} - (s-1)/(s-i)`。


### 3. 难点3：确定初始值与边界条件
- **分析**：`f_s = 0`（已经全是目标颜色，无需操作），但`f_1`的值需要通过递推式反推。
- **解决方案**：利用`f_s = 0`和递推式，通过**差分求和**反推`f_1`的值：`f_1 = (s-1)^2/s`。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
- **说明**：综合DeaphetS、樱雪喵和Leasier的题解，提炼出最简洁的核心实现。
- **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

long long quick_pow(long long a, long long b) {
    long long res = 1;
    for (; b; b >>= 1, a = a * a % MOD)
        if (b & 1) res = res * a % MOD;
    return res;
}

long long inv(long long x) {
    return quick_pow(x, MOD - 2);
}

int main() {
    int n, s = 0, max_a = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        s += a[i];
        if (a[i] > max_a) max_a = a[i];
    }

    vector<long long> f(max_a + 2, 0);
    f[1] = (1LL * (s - 1) * (s - 1) % MOD) * inv(s) % MOD;
    for (int i = 2; i <= max_a; ++i) {
        f[i] = (2 * f[i-1] % MOD - f[i-2] + MOD) % MOD;
        f[i] = (f[i] - 1LL * (s - 1) * inv(s - i + 1) % MOD + MOD) % MOD;
    }

    long long ans = 0;
    for (int num : a) ans = (ans + f[num]) % MOD;
    cout << ans << endl;
    return 0;
}
```
- **代码解读概要**：
  - 输入处理：读取球的颜色数量`a`，计算总球数`s`和最大颜色数`max_a`。
  - 递推计算`f`数组：`f[1]`是初始值，`f[i]`通过递推式计算。
  - 结果求和：将每种颜色的`f[a[i]]`相加，得到最终答案。


### 题解一（DeaphetS）核心片段赏析
- **亮点**：将问题拆解为弱化版本，降低理解门槛。
- **核心代码片段**：
```cpp
// 弱化版本：n种颜色各1个球，求f_1
f[1] = (n-1) * (n-1) % MOD;
for (int i = 1; i < N-5; ++i) {
    long long tot = 2LL * i * (n - i) % MOD * f[i] % MOD;
    tot = (tot + MOD - 1LL * (i-1) * (n - i) % MOD * f[i-1] % MOD) % MOD;
    tot = (tot + MOD - 1LL * n * (n-1) % MOD) % MOD;
    tot = tot * inv(i+1) % MOD * inv(n - i) % MOD;
    f[i+1] = tot;
}
```
- **代码解读**：
  - 这段代码计算弱化版本的`f`数组。`f[i]`表示有`i`个目标球的期望步数。
  - `tot`是递推式的分子部分，通过`inv`函数求逆元，计算`f[i+1]`。
- **学习笔记**：遇到复杂问题时，可以先解决**弱化版本**（如所有颜色各1个球），再推广到原问题。


## 5. 算法可视化：像素动画演示

### 动画演示主题：「像素袋子的颜色魔法」
- **核心演示内容**：展示目标颜色球数量从`a_i`到`s`的递推过程，每一步对应`f_i`的计算。
- **设计思路**：用8位像素风格模拟袋子，目标颜色球用红色，其他用蓝色。每执行一步，红色球数量变化，播放对应音效，增强记忆点。
- **动画帧步骤**：
  1. **初始化**：屏幕显示像素袋子，里面有`s`个球，红色球数量为`a_i`，控制面板有「单步」「自动」「重置」按钮。
  2. **单步执行**：点击「单步」，选中两个球（蓝色和红色），蓝色球变成红色，红色数量+1，播放「叮」的音效，同时代码中的`f[i+1]`行高亮。
  3. **自动播放**：点击「自动」，AI逐步完成递推，红色球数量从`a_i`增加到`s`，完成时播放「胜利」音效。
- **交互设计**：速度滑块可以调整自动播放的速度，重置按钮将动画恢复到初始状态。


## 6. 拓展练习与相似问题

### 相似问题
1. **洛谷P5516**：与本题几乎相同，只是输入格式略有差异，适合巩固递推式的应用。
2. **洛谷P4389**：生成函数问题，需要计算拆分数，锻炼数学推导能力。
3. **洛谷P6835**：随机游走问题，需要计算期望步数，与本题的动态规划思路一致。


## 7. 学习心得与经验分享
- **参考经验**：DeaphetS在题解中提到「将问题拆解为弱化版本」，这是解决复杂问题的关键技巧——当原问题难以直接解决时，可以先解决简化版，再寻找规律推广。
- **点评**：这种「从简到繁」的思维方式非常重要，不仅适用于编程题，也适用于生活中的问题。比如学习数学时，先学整数运算，再学分数运算，最后学实数运算。


## 结论
「Rainbow Balls」的核心是**动态规划结合数学推导**，关键在于拆解问题、推导递推式、处理无效状态。通过本题的学习，你不仅能掌握动态规划的应用，还能提升数学推导能力。记住：**编程的本质是解决问题，而数学是解决问题的工具**！下次我们再一起探索更多有趣的算法问题吧！💪

---
处理用时：80.90秒