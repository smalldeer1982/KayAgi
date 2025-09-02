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


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（期望DP）  

🗣️ **初步分析**：  
解决“Rainbow Balls”的关键，是用**期望动态规划（期望DP）**——它像“带概率的爬楼梯游戏”：每一步的期望步数不仅依赖“前一步”和“后一步”，还要根据“踩中某步的概率”调整。在本题中，我们需要计算**每种颜色“获胜”（成为最终颜色）的期望步数**，再乘以其获胜概率，最后求和得到总期望。  

### 核心思路与难点
题解的核心逻辑是：  
1. **枚举最终颜色**：假设最后所有球都是颜色`i`，计算从初始`a_i`个该颜色球到`s`个的期望步数`f(a_i)`；  
2. **获胜概率**：颜色`i`获胜的概率为`a_i/s`（`s`是总球数，等差数列推导得出）；  
3. **递推求`f(i)`**：通过概率转移方程`f(i) = 2f(i-1) - f(i-2) - (s-1)/(s-i)`，结合边界`f(1)=(s-1)²/s`和`f(s)=0`，递推所有`f(i)`。  

**核心难点**：  
- 如何避免无效的“0状态”（颜色球数变为0，无法获胜）？  
- 如何将复杂的期望分解为可递推的相邻状态？  

**解决方案**：  
引入“获胜概率`g(i)=i/s`”，将转移方程中的“1步贡献”修正为`g(i)`，从而排除0状态的影响；通过数学推导将期望DP转化为**线性递推**，只需计算到`max(a_i)`即可。  

### 可视化设计思路
我们用**8位像素风格**模拟“颜色扩张”过程：  
- 场景：像素化的球堆，用不同颜色区分“目标颜色”（比如红色）和“其他颜色”（灰色）；  
- 动态演示：`i`从`a_i`增长到`s`，每一步用“红色像素块增加”表示`i`的变化，高亮当前`f(i)`的值；  
- 交互：“单步执行”展示递推细节，“自动播放”模拟完整过程；  
- 音效：`i`变化时播放“叮”的像素音，完成时播放FC风格的胜利音效；  
- 提示：侧边文字说明当前步骤的`f(i)`计算逻辑（比如“`f(2)=2*f(1)-1`”）。  


## 2. 精选优质题解参考

为你筛选了以下**思路清晰、推导严谨、代码简洁**的优质题解：

### 题解一：DeaphetS（条件概率推导）
**点评**：这份题解用条件概率拆解问题，从“弱化版本”（每种颜色1个球）入手，逐步推导到原问题。对`f(i)`的转移方程分析细致，特别是通过`P(F_i|x_k=i)=i/s`修正了条件概率，避免了0状态的干扰。代码中`f`数组的递推逻辑清晰，边界处理严谨，是理解期望DP的好例子。

### 题解二：樱雪喵（简化递推式）
**点评**：此题解将复杂的转移方程简化为`f(i+1)=2f(i)-f(i-1)-(s-1)/(s-i)`，并直接递推求解。代码风格简洁规范，`f(1)`的计算和`f(2)`的初始化正确，适合作为入门参考。

### 题解三：Soulist（势能函数方法）
**点评**：这份题解用**势能函数**从更抽象的角度推导，将整个局面的势能定义为`sum f(a_i)`，通过鞅的性质证明了递推式的正确性。推导过程严谨，适合想深入理解期望DP本质的学习者。


## 3. 核心难点辨析与解题策略

### 1. 难点1：如何处理“0状态”的无效性？
**问题**：若目标颜色的球数变为0，该颜色无法获胜，但直接计算`f(0)`会得到无穷大。  
**解决方案**：引入**获胜概率`g(i)=i/s`**（表示有`i`个目标颜色球时获胜的概率），将转移方程中的“1步贡献”替换为`g(i)`，从而排除0状态的影响。例如，原转移方程中的`+1`改为`+g(i)`，确保只有获胜路径的贡献被计算。

### 2. 难点2：如何推导`f(i)`的递推式？
**问题**：期望的线性性质让`f(i)`依赖`f(i-1)`和`f(i+1)`，直接计算复杂。  
**解决方案**：通过概率转移和期望的线性性，将`f(i)`分解为相邻状态的加权和。例如，`f(i)`的转移方程可化简为：  
`f(i+1) = 2f(i) - f(i-1) - (s-1)/(s-i)`  
这一线性递推式将复杂的期望问题转化为“相邻状态的差值计算”，只需从`f(1)`开始递推即可。

### 3. 难点3：如何求`f(1)`的初始值？
**问题**：递推需要初始值`f(1)`，但直接计算困难。  
**解决方案**：利用边界条件`f(s)=0`和递推式联立求解。例如，通过将`f(i)`的差分求和，结合`f(s)=0`，最终得到：  
`f(1) = (s-1)² / s`  
这一结果是递推的起点，确保后续计算的正确性。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
**说明**：综合樱雪喵、Cyhlnj等题解的思路，提炼出的简洁递推实现，覆盖核心逻辑。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 1e5 + 5;

long long qpow(long long x, int y) {
    long long res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

int main() {
    int n, sum = 0, max_a = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
        max_a = max(max_a, a[i]);
    }

    vector<long long> f(max_a + 2, 0);
    f[1] = 1LL * (sum - 1) * (sum - 1) % mod * qpow(sum, mod - 2) % mod;
    if (max_a >= 2) f[2] = (2 * f[1] - 1 + mod) % mod;

    for (int i = 2; i < max_a; ++i) {
        long long term = 1LL * (sum - 1) * qpow(sum - i, mod - 2) % mod;
        f[i + 1] = ((2 * f[i] % mod - f[i - 1] - term) % mod + mod) % mod;
    }

    long long ans = 0;
    for (int num : a) ans = (ans + f[num]) % mod;
    cout << ans << endl;

    return 0;
}
```

**代码解读概要**：  
1. **输入处理**：读取`n`和`a`数组，计算总球数`sum`和最大初始球数`max_a`；  
2. **初始化`f`数组**：计算`f(1)`（初始值）和`f(2)`（递推起点）；  
3. **递推计算`f`**：从`i=2`开始，按递推式计算到`max_a`；  
4. **求和答案**：累加所有`f(a[i])`，输出结果。


### 各优质题解的片段赏析

#### 题解一：DeaphetS（条件概率推导）
**亮点**：用条件概率修正转移方程，明确区分“有效状态”和“无效状态”。  
**核心代码片段**：
```cpp
// 计算f[i]的递推式
f[i+1] = (2LL * i * (n - i) % MOD * f[i] % MOD 
          - 1LL * (i - 1) * (n - i) % MOD * f[i-1] % MOD 
          - 1LL * n * (n - 1) % MOD) % MOD;
f[i+1] = f[i+1] * qpow(1LL * (i + 1) * (n - i) % MOD, MOD - 2) % MOD;
```
**代码解读**：  
这段代码对应条件概率推导的递推式`2i(n-i)f(i) = n(n-1) + (i-1)(n-i)f(i-1) + (i+1)(n-i)f(i+1)`。通过移项求解`f(i+1)`，并利用逆元处理除法（模运算中的除法需用逆元）。  
**学习笔记**：模运算中处理除法时，必须用快速幂求逆元，避免直接除以一个数。


#### 题解二：樱雪喵（简化递推）
**亮点**：将复杂的转移方程简化为线性递推，代码简洁高效。  
**核心代码片段**：
```cpp
f[1] = 1LL * (s - 1) * (s - 1) % mod * inv(s) % mod;
f[2] = (2 * f[1] - 1 + mod) % mod;
for (int i = 2; i < mx; ++i) {
    f[i+1] = (2 * f[i] % mod - f[i-1] - 1LL * (s-1) * inv(s - i) % mod + mod) % mod;
}
```
**代码解读**：  
直接使用简化后的递推式`f(i+1) = 2f(i) - f(i-1) - (s-1)/(s-i)`。其中`inv(x)`是`x`的逆元，用于处理模运算中的除法。  
**学习笔记**：简化递推式能大幅减少代码复杂度，关键是要理解推导过程中的数学变换。


#### 题解三：Soulist（势能函数）
**亮点**：用势能函数从更高层面证明递推式的合法性，推导严谨。  
**核心代码片段**：
```cpp
// 计算f(x) = (m-1)*(m-x)*sum_{j=0}^{x-1} 1/(m-j)
inv[0] = qpow(c - 0, P - 2);
for (int i = 1; i <= mx; ++i) inv[i] = (inv[i-1] + qpow(c - i, P - 2)) % P;
for (int i = 1; i <= mx; ++i) f[i] = 1LL * (c-1) * (c - i) % P * inv[i-1] % P;
```
**代码解读**：  
这段代码对应势能函数推导的结果`f(x) = (s-1)(s-x) * sum_{j=0}^{x-1} 1/(s-j)`。通过预处理逆元的前缀和，快速计算`f(x)`。  
**学习笔记**：势能函数是解决期望问题的高级技巧，能将复杂的随机过程转化为确定性的函数计算。


## 5. 算法可视化：像素动画演示方案

### 动画主题与设计思路
**主题**：像素探险家“小彩”扩张颜色领地，从`a_i`个红色球开始，逐步将所有灰色球染成红色。  
**设计思路**：用8位像素风格营造复古游戏氛围，通过“领地扩张”的直观动画展示`f(i)`的递推过程，结合音效和交互增强记忆点。


### 动画帧步骤与交互设计
1. **场景初始化**：  
   - 屏幕左侧显示像素化的球堆：红色块表示当前目标颜色的数量`i`，灰色块表示其他颜色；  
   - 右侧控制面板：`开始/暂停`、`单步`、`重置`按钮，速度滑块（1x~5x）；  
   - 底部显示当前`i`值和`f(i)`的计算结果（比如“i=3，f(i)=12”）；  
   - 播放FC风格的背景音乐（轻快的8位旋律）。

2. **算法启动**：  
   - 初始状态：红色块数量为`a_i`（比如`a_i=2`），灰色块数量为`s-a_i`；  
   - 弹出提示框：“目标：将所有灰色块染成红色！”，点击“开始”进入递推。

3. **核心步骤演示**：  
   - **单步执行**：点击“单步”，`i`增加1（红色块+1，灰色块-1），同时计算`f(i+1)`，高亮递推式（比如“f(3)=2*f(2)-f(1)-(s-1)/(s-2)”）；  
   - **自动播放**：滑块调整速度，动画按设定速度自动递推，`i`从`a_i`增长到`s`，每步伴随“叮”的音效；  
   - **状态高亮**：当前`i`对应的红色块闪烁，`f(i)`的值用黄色像素显示在底部；  
   - **完成提示**：当`i=s`时，所有块变为红色，播放胜利音效（FC风格的“叮~叮~”），弹出“完成！总期望步数：X”。

4. **交互控制**：  
   - 支持“重置”回到初始状态，重新演示；  
   - 支持“暂停”查看当前`i`和`f(i)`的细节；  
   - （可选）“挑战模式”：用户手动输入`a_i`，动画演示对应的递推过程，完成后获得“颜色大师”称号。


## 6. 拓展练习与相似问题思考

### 通用思路迁移
本题的核心技巧是**期望DP的线性递推**和**概率修正**，可迁移到以下场景：  
1. **图上随机游走**：计算从起点到终点的期望步数；  
2. **硬币游戏**：计算收集所有硬币的期望次数；  
3. **进化问题**：计算物种进化到某状态的期望时间。


### 洛谷相似问题推荐
1. **洛谷 P5516**：平衡树的期望操作次数，需处理类似的状态递推和概率修正；  
2. **洛谷 P6835**：图上随机游走的期望步数，考察期望DP的边界处理；  
3. **洛谷 P4389**：付公主的背包，虽然是多项式问题，但涉及递推和前缀和优化，锻炼递推思维；  
4. **洛谷 P2577**：午餐，考察贪心+DP，需结合概率和期望的线性性。


## 7. 学习心得与经验分享

### 参考经验（来自Soulist的势能函数推导）
> “构造势能函数时，关键是要让`E(Φ(A_{n+1}) - Φ(A_n)) = -1`，这样停时定理才能直接应用。这需要对随机过程的期望变化有深刻理解。”

**点评**：势能函数是解决期望问题的“利器”，但需要扎实的概率论基础。Soulist的经验提醒我们：**解决复杂期望问题时，要从“过程的期望变化”入手，而非直接计算每一步的期望**。


### 参考经验（来自樱雪喵的代码优化）
> “简化递推式是代码高效的关键。我最初写出的是复杂的条件概率式，后来通过数学变换得到了线性递推式，代码量减少了一半。”

**点评**：数学推导能大幅简化代码逻辑。在写代码前，一定要先将问题转化为最简的数学形式，避免冗余计算。


## 8. 总结

本次分析的“Rainbow Balls”题，核心是**期望DP的线性递推**，关键在于：  
- 用概率修正转移方程，避免无效状态；  
- 推导简洁的递推式，从`f(1)`开始逐步计算；  
- 结合像素动画直观展示递推过程。  

希望这份指南能帮助你理解期望DP的本质，掌握“将复杂问题分解为相邻状态递推”的技巧。下次遇到类似问题时，不妨先尝试推导递推式，再用代码实现——你会发现，期望问题并没有想象中那么难！

💪 继续加油，你一定能成为“期望DP大师”！ 💪

---
处理用时：90.35秒