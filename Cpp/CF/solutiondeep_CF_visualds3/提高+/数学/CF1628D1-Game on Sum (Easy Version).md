# 题目信息

# Game on Sum (Easy Version)

## 题目描述

This is the easy version of the problem. The difference is the constraints on $ n $ , $ m $ and $ t $ . You can make hacks only if all versions of the problem are solved.

Alice and Bob are given the numbers $ n $ , $ m $ and $ k $ , and play a game as follows:

The game has a score that Alice tries to maximize, and Bob tries to minimize. The score is initially $ 0 $ . The game consists of $ n $ turns. Each turn, Alice picks a real number from $ 0 $ to $ k $ (inclusive) which Bob either adds to or subtracts from the score of the game. But throughout the game, Bob has to choose to add at least $ m $ out of the $ n $ turns.

Bob gets to know which number Alice picked before deciding whether to add or subtract the number from the score, and Alice gets to know whether Bob added or subtracted the number for the previous turn before picking the number for the current turn (except on the first turn since there was no previous turn).

If Alice and Bob play optimally, what will the final score of the game be?

## 说明/提示

In the first test case, the entire game has $ 3 $ turns, and since $ m = 3 $ , Bob has to add in each of them. Therefore Alice should pick the biggest number she can, which is $ k = 2 $ , every turn.

In the third test case, Alice has a strategy to guarantee a score of $ \frac{75}{8} \equiv 375000012 \pmod{10^9 + 7} $ .

In the fourth test case, Alice has a strategy to guarantee a score of $ \frac{45}{2} \equiv 500000026 \pmod{10^9 + 7} $ .

## 样例 #1

### 输入

```
7
3 3 2
2 1 10
6 3 10
6 4 10
100 1 1
4 4 0
69 4 20```

### 输出

```
6
5
375000012
500000026
958557139
0
49735962```

# AI分析结果


# 💡 Kay的C++算法解析：Game on Sum (Easy Version) 深入学习指南 💡

> 大家好，我是Kay！今天我们来一起分析博弈论题目「Game on Sum (Easy Version)」。这道题考察双方最优策略下的动态规划，就像两位棋手在棋盘上博弈——Alice进攻，Bob防守，最终分数由他们的精妙决策共同决定。本指南将带你拆解核心算法逻辑，并通过像素动画直观感受决策过程！

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`动态规划` + `博弈论决策`

🗣️ **初步分析**：
> 想象Alice和Bob在玩一个「数字攻防战」：Alice每轮出招（0到k间的实数），Bob选择加分（盾）或减分（矛），但至少用m次盾。Alice想最大化分数，Bob想最小化分数。这就像两个人在多轮博弈中预判对方的策略！

- **核心难点**：双方决策相互影响，需通过动态规划模拟所有可能状态
- **解法精髓**：用`dp[i][j]`表示进行i轮游戏且Bob使用j次加法时Alice能获得的最大分数。转移时Alice会选择一个**平衡点t**使Bob的两种选择结果相同
- **可视化设计**：我们将用像素网格展示DP表填充过程（行=轮数，列=加法次数），高亮状态转移路径（当前状态值=上方和左上方的平均值），并加入8-bit音效（计算时"叮"声，完成时胜利音效）

---

## 2. 精选优质题解参考

> 我从30+篇题解中精选3份最优解，从思路清晰度、代码质量、算法效率等维度评估（均≥⭐️⭐️⭐️⭐️⭐️）

### 题解一：Alex_Wei（24赞）
* **思路亮点**：清晰推导"为什么用倒序DP"——因当前决策依赖后续结果，如同下棋需往后看三步。边界处理严谨（`j=0`和`i=j`）
* **代码亮点**：用`inv2 = 500000004`巧妙处理除法取模（2的逆元），变量名`f[i][j]`直观
* **效率优化**：预处理DP表后O(1)响应查询

### 题解二：DaiRuiChen007（11赞）
* **教学亮点**：从`n=2, m=1`简单案例推广到通用DP方程，新手友好
* **代码细节**：完整注释关键步骤，强调`dp[i][i]=i`是为分离k的优化
* **实践价值**：完整可运行代码，适合竞赛直接使用

### 题解三：KingPowers（3赞）
* **代码简洁性**：仅20行核心逻辑，全局数组隐式初始化`j=0`边界
* **算法等效性**：相同DP思想但更精简，适合快速理解
* **工程价值**：用`For`宏提升可读性，主函数分离初始化与查询

> 💡 学习提示：三份题解都采用`dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) / 2`的核心策略，区别在于代码风格和解释深度

---

## 3. 核心难点辨析与解题策略

### 🔑 难点1：状态定义与博弈关系
* **问题**：如何定义状态才能捕捉双方最优策略？
* **分析**：需同时考虑**剩余轮数**和**可用加法次数**。`dp[i][j]`中：
  - `i`是总轮数（已进行轮数）
  - `j`是Bob已用加法次数
* **策略**：从结束状态反推（倒序思想），边界`dp[i][0]=0`（无加法）和`dp[i][i]=i*k`（全加法）

### 🔑 难点2：转移方程的数学推导
* **问题**：为什么转移是`(上+左上)/2`？
* **分析**：设Alice选择`t`，Bob会选择`min(左上+t, 上-t)`。Alice通过令两者相等求得最优`t`：
  ```math
  dp[i-1][j-1] + t = dp[i-1][j] - t  
  => t = (dp[i-1][j] - dp[i-1][j-1])/2
  ```
  代入即得`dp[i][j] = (dp[i-1][j-1] + dp[i-1][j])/2`
* **策略**：用逆元处理除法（`2^{-1} mod 1e9+7 = 500000004`）

### 🔑 难点3：k的分离优化
* **问题**：k变化时如何避免重复计算？
* **分析**：发现分数与k成正比，可先计算`k=1`的情况，最终乘`k`
* **策略**：令`dp[i][i]=i`而非`i*k`，答案输出`dp[n][m]*k`

### ✨ 解题技巧总结
1. **逆向DP**：博弈问题常从结束状态倒推
2. **鞍点决策**：连续选择问题中，令对手两种选择等效是最优策略
3. **模数优化**：除法用逆元转乘法，边界预处理提速
4. **维度分离**：将参数（如k）从状态转移中分离

---

## 4. C++核心代码实现赏析

### 本题通用核心实现（综合优化版）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
const int inv2 = 500000004; // 2的逆元
const int MAXN = 2005;

int dp[MAXN][MAXN];

void init() {
    // 边界初始化
    for (int i = 1; i < MAXN; i++) {
        dp[i][0] = 0;    // 无加法操作
        dp[i][i] = i;    // 全加法操作 (k=1)
    }
    // DP转移：核心方程
    for (int i = 2; i < MAXN; i++)
        for (int j = 1; j < i; j++)
            dp[i][j] = 1LL * (dp[i-1][j-1] + dp[i-1][j]) * inv2 % mod;
}

int main() {
    init(); // 预处理DP表
    int T; cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        cout << 1LL * dp[n][m] * k % mod << '\n';
    }
}
```

### 分题解核心片段赏析

**题解一：Alex_Wei**
```cpp
// 初始化边界
for (int i = 1; i <= 2000; i++) {
    f[i][0] = 0;
    f[i][i] = i; // k=1时的分数
}
// 核心转移：从第2行开始
for (int i = 2; i <= 2000; i++) {
    for (int j = 1; j < i; j++) {
        f[i][j] = (f[i-1][j-1] + f[i-1][j]) % mod;
        f[i][j] = 1LL * f[i][j] * inv2 % mod; // 乘逆元等效除以2
    }
}
```
* **代码精读**：
  - 第1层循环：`i`从2开始（因`i=1`时只有`j=0/1`已处理）
  - 第2层循环：`j`严格小于`i`（避免越界）
  - 分开取模与乘法：先加后乘逆元，避免溢出

**题解二：DaiRuiChen007**
```cpp
// 注册变量提升速度(编译器优化)
for(register int i=2; i<MAXN; ++i) 
    for(register int j=1; j<i; ++j)
        dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % mod * INV % mod;
```
* **学习笔记**：
  - `register`关键字建议编译器将变量存入寄存器（C++17后失效但保留兼容）
  - 合并计算：`(a+b)*inv % mod` 更简洁

**题解三：KingPowers**
```cpp
// 简洁版初始化
For(i,1,2000) f[i][i] = i; // 对角线初始化
For(i,2,2000) For(j,1,i-1)
    f[i][j] = (f[i-1][j-1] + f[i-1][j]) % mod * inv2 % mod;
```
* **关键技巧**：
  - 利用全局数组自动初始化为0的特性，省略`j=0`的显式赋值
  - 宏定义`For`提升循环可读性（需提前`#define For(i,a,b) for(int i=a; i<=b; i++`）

---

## 5. 算法可视化：像素动画演示

> 想象一个8-bit风格游戏：网格世界中的数字战场！

### 🎮 动画设计
* **视觉设计**：
  - 16色FC红白机色调（深蓝网格+黄/绿状态块）
  - 网格行=游戏轮数（1→n），列=加法次数（0→m）
  - 当前计算格闪烁，上方和左上方格高亮提示数据来源
* **动态流程**：
  1. 初始化：第0列全绿（值0），对角线全蓝（值i）
  2. 填充过程：从(2,1)开始Z字形扫描
      - 当前格显示`(上+左上)/2`公式
      - 实时显示计算结果（像素数字）
  3. 特效：
      - 计算时：当前格旋转缩放+“叮”声
      - 完成行：像素烟花+升级音效
* **交互控制**：
  - 步进模式：方向键控制移动，Enter确认计算
  - 自动模式：AI机器人自动填充（速度滑块调节）
  - 战斗界面：Alice和Bob像素小人表情随分数变化

![](https://assetsio.gnwcdn.com/coadaf.gif?width=717&height=717&fit=bounds&quality=70&format=jpg&auto=webp)

### 🎵 音效设计
| 事件         | 音效                  | 触发逻辑                |
|--------------|-----------------------|-------------------------|
| 选择格子     | 短促"滴"声           | 光标移动时              |
| 计算完成     | 中频"叮"声(440Hz)    | 状态转移完成时          |
| 完成一行     | 上升琶音             | 每行最后一个格子完成时  |
| 游戏通关     | 8-bit胜利音乐        | dp[n][m]计算完成时     |

> 💡 设计目的：通过游戏化降低理解门槛，声音反馈强化状态转移记忆

---

## 6. 拓展练习与相似问题思考

### 同类博弈DP问题
1. **洛谷 P2583**：[高级打字机]
   - 推荐理由：同样需要结合博弈思想设计DP状态
2. **洛谷 P2734**：[游戏 A Game]
   - 推荐理由：双人轮流决策求最优值，状态设计技巧迁移
3. **CodeForces 1628D2**：[Game on Sum (Hard Version)]
   - 推荐理由：本题进阶版，需组合数学优化DP

### 思维进阶
- **变形思考**：若Bob不知道Alice的选择会怎样？
- **挑战问题**：若k随时间变化如何修改DP状态？

---

## 7. 学习心得与经验分享

> 来自Alex_Wei的调试经验：
> *"我在边界条件`dp[i][i]=i*k`卡了很久，直到意识到k可分离优化"*

**Kay的总结**：
1. **边界检查**：博弈DP的边界（如全加/全减）决定算法正确性
2. **数学工具**：逆元是模运算下处理除法的关键武器
3. **维度分离**：将固定参数从状态中分离可大幅提升效率

---

通过本指南，希望大家不仅理解本题解法，更掌握**博弈论DP的设计思想**。记住：编程如棋，每一步决策都影响最终结局！下次见~ 🚀

---
处理用时：223.95秒