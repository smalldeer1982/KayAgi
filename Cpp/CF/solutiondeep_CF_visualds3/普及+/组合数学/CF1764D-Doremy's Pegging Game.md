# 题目信息

# Doremy's Pegging Game

## 题目描述

Doremy has $ n+1 $ pegs. There are $ n $ red pegs arranged as vertices of a regular $ n $ -sided polygon, numbered from $ 1 $ to $ n $ in anti-clockwise order. There is also a blue peg of slightly smaller diameter in the middle of the polygon. A rubber band is stretched around the red pegs.

Doremy is very bored today and has decided to play a game. Initially, she has an empty array $ a $ . While the rubber band does not touch the blue peg, she will:

1. choose $ i $ ( $ 1 \leq i \leq n $ ) such that the red peg $ i $ has not been removed;
2. remove the red peg $ i $ ;
3. append $ i $ to the back of $ a $ .

Doremy wonders how many possible different arrays $ a $ can be produced by the following process. Since the answer can be big, you are only required to output it modulo $ p $ . $ p $ is guaranteed to be a prime number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png) game with $ n=9 $ and $ a=[7,5,2,8,3,9,4] $ and another game with $ n=8 $ and $ a=[3,4,7,1,8,5,2] $

## 说明/提示

In the first test case, $ n=4 $ , some possible arrays $ a $ that can be produced are $ [4,2,3] $ and $ [1,4] $ . However, it is not possible for $ a $ to be $ [1] $ or $ [1,4,3] $ .

## 样例 #1

### 输入

```
4 100000007```

### 输出

```
16```

## 样例 #2

### 输入

```
1145 141919831```

### 输出

```
105242108```

# AI分析结果


### 💡 Kay的C++算法解析：Doremy's Pegging Game 深入学习指南 💡

<introduction>
欢迎来到本次算法解析！今天我们将深入探讨「Doremy's Pegging Game」——一道结合组合数学与环上操作的计数问题。本指南将通过清晰的算法拆解、代码实现和像素动画演示，帮助大家掌握计数问题的核心技巧。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`组合数学`与`枚举技巧`

🗣️ **初步分析**：
> 这道题的本质是**计算满足特定终止条件的操作序列数量**。想象一个圆形城堡（红钉）守护中心宝石（蓝钉），每次移除一个守卫直到某段连续城墙（≥⌊n/2⌋个红钉）崩塌触碰到宝石。解题关键：
> - **终止条件**：当移除的红钉形成一段长度≥⌊n/2⌋的连续段时游戏结束。
> - **对称简化**：利用环形对称性，固定最后一步移除的钉子（如n号钉），最终结果×n即可覆盖所有情况。
> - **组合枚举**：枚举连续段长度和额外移除的钉子数，通过组合数+阶乘计算有效序列数。
>
> **可视化设计**：
> 我们将用**8位像素风格**模拟圆环钉子（红/蓝像素块），橡皮筋用彩色线条表示。动画高亮：①被移除的钉子（变灰） ②连续段检测（闪烁红光） ③橡皮筋收缩特效（命中蓝钉时触发胜利音效）。控制面板支持单步执行/调速，帮助观察组合计数中参数变化的影响。

---

## 2. 精选优质题解参考

<eval_intro>
综合思路清晰度、代码规范性和算法效率，精选3份优质题解（均≥4★）。重点解析其组合数学的建模技巧：

**题解一（VinstaG173）**  
* **点评**：思路直击本质——通过对称性将问题转化为线性序列计数。代码简洁高效：①预处理阶乘逆元优化组合数计算 ②精准处理n奇偶性特判 ③双重循环枚举参数，复杂度O(n²)。亮点在数学推导严谨性，尤其对连续段长度与额外钉子数的关系处理，是竞赛编程的典范。

**题解二（honglan0301）**  
* **点评**：采用动态规划框架，dp[i][j]表示连续段跨度为i且移除j个钉子的方案数。优势：①状态定义直观反映物理意义（连续段起止位置） ②显式处理边界条件 ③模块化代码结构（分离组合数预处理）。稍显不足是公式推导省略部分细节。

**题解三（MortisM）**  
* **点评**：回归枚举本源，清晰拆解为三步：①确定连续段位置 ②选择额外钉子 ③计算排列数。亮点：强调终止条件检查的数学本质（2⌊n/2⌋-l系数），虽代码有边界瑕疵，但解题思路极具教学价值。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此类环上计数问题的三大关键难点及突破策略：

1.  **难点1：环形条件的线性转化**  
    * **分析**：环形结构难以直接计数，需利用对称性破环为链。优质题解均固定最后移除的钉子（如n号），转化为线性序列问题。
    * 💡 **学习笔记**：环形问题固定参照点是简化计数的黄金法则。

2.  **难点2：终止条件的数学表征**  
    * **分析**：终止条件对应⌊n/2⌋连续移除段。需推导：①该段长度范围（⌊n/2⌋≤l≤n） ②位置可能性（2⌊n/2⌋-l种）。核心技巧：通过两侧连续未移除段长度(s,t)推导。
    * 💡 **学习笔记**：组合问题中，将约束转化为参数枚举是通用解题框架。

3.  **难点3：组合计数的效率优化**  
    * **分析**：公式含大量组合数和阶乘运算。必须：①预处理阶乘及其逆元 ②O(1)计算组合数。避免暴力递归导致O(n³)复杂度。
    * 💡 **学习笔记**：模数p为质数时，费马小定理求逆元是优化关键。

### ✨ 解题技巧总结
<summary_best_practices>
- **技巧1：对称破环法** – 环形问题固定起始点转化为线性序列  
- **技巧2：参数枚举法** – 将复杂约束拆解为可枚举参数（连续段长l/额外钉子数x）  
- **技巧3：组合预处理** – 预处理阶乘逆元，将组合数计算降至O(1)  
- **技巧4：边界特判** – 特别注意n为偶数时需补充单点移除方案  
---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下通用实现融合了优质题解精华，包含：①对称性处理 ②组合数优化 ③边界特判：

```cpp
#include <iostream>
using namespace std;
typedef long long ll;

ll qpow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

ll C(int n, int k, ll fac[], ll fic[], ll mod) {
    if (k<0 || k>n) return 0;
    return fac[n] * fic[k] % mod * fic[n-k] % mod;
}

int main() {
    int n, p;
    cin >> n >> p;
    ll fac[5005], fic[5005];
    // 预处理阶乘及逆元
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) 
        fac[i] = fac[i-1] * i % p;
    fic[n] = qpow(fac[n], p-2, p);
    for (int i = n; i >= 1; --i) 
        fic[i-1] = fic[i] * i % p;

    int c = n / 2; // ⌊n/2⌋
    ll ans = 0;
    // 枚举连续段参数m（m = s+t ≥ c-1）
    for (int m = c-1; m <= n-2; ++m) {
        ll tmp = 0;
        int M = max(0, n - m - 3); // 可选的额外钉子数
        for (int i = 0; i <= M; ++i) 
            tmp = (tmp + fac[m+i] * C(M, i, fac, fic, p)) % p;
        ans = (ans + (2*c - m - 1) * tmp) % p;
    }
    // n为偶数时的特判（最后仅剩1个钉子）
    if (n % 2 == 0) 
        ans = (ans + fac[n-2]) % p; 
    ans = ans * n % p; // 对称性乘n
    cout << (ans + p) % p << endl;
}
```

**代码解读概要**：  
1. **预处理阶段**：计算fac[n]（阶乘）和fic[n]（逆元）  
2. **主计算循环**：  
   - 外层枚举连续段参数m（范围⌊n/2⌋-1至n-2）  
   - 内层累加公式：`Σ[ fac[m+i]×C(M,i) ]`（M为可选额外钉子数）  
3. **特判处理**：n为偶数时补充`fac[n-2]`（最后移除单个钉子的排列）  
4. **对称扩展**：结果×n覆盖所有终点位置  

### 题解片段赏析
**题解一（VinstaG173）**  
* **亮点**：精炼实现组合核心公式，完美融合数学推导  
* **核心代码**：  
  ```cpp
  for(int m=n/2-1; m<n-2; ++m) {
      tmp=0;
      for(int i=0; i<=n-m-3; ++i)
          tmp = (tmp + fac[m+i]*C(n-m-3,i)) % mod;
      res = (res + (n-(n&1)-1-m)*tmp) % mod;
  }
  res = (res + (1-(n&1))*fac[n-2]) % mod;
  ```
* **代码解读**：  
  > 内层循环计算「选定i个额外钉子时的排列数」——fac[m+i]是序列排列数，C(n-m-3,i)是选择钉子的组合数。系数`(n-(n&1)-1-m)`即`2⌊n/2⌋-m-1`，来自连续段位置可能性。  
* 💡 **学习笔记**：位运算`n&1`高效处理奇偶性，是竞赛编程常用技巧。

**题解二（honglan0301）**  
* **亮点**：DP状态定义直观，显式处理连续段起止  
* **核心代码**：  
  ```cpp
  for(int i=c+1; i<=n-1; ++i) // i:连续段跨度
  for(int j=i-1; j<=n-2; ++j) { // j:总移除数
      dp[i][j] = (2*c-i+1) * C(n-i-1, j-i+1) % mod;
      dp[i][j] = dp[i][j] * fac[j-1] % mod;
      ans = (ans + dp[i][j]) % mod;
  }
  ```
* **代码解读**：  
  > 状态dp[i][j]三要素：①`2c-i+1`为连续段位置选择 ②`C(n-i-1,j-i+1)`选额外钉子 ③`fac[j-1]`排列前j-1步。物理意义清晰但需注意i的取值范围。  
* 💡 **学习笔记**：DP适用于有显式状态转移的问题，组合问题中可优先考虑。

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
**8位像素风格**动画演示算法核心——随着钉子移除，实时检测连续段并触发终止条件：

  * **主题**：复古游戏《圆环守卫战》  
  * **核心演示**：钉子移除 → 连续段检测 → 橡皮筋收缩  

### 动画帧步骤设计
1. **场景初始化**（像素风格）：  
   - 红钉：8×8像素方块（红色）环状排列  
   - 蓝钉：中心蓝色闪烁方块  
   - 控制面板：速度滑块/单步/暂停/重置按钮（复古游戏UI）  

2. **算法启动**：  
   - 移除钉子：点击或自动选中钉子→变灰色→播放"咔嚓"音效  
   - 实时检测：每步扫描最长连续灰钉，≥⌊n/2⌋时触发警报（红光闪烁）  

3. **终止特效**：  
   - 橡皮筋收缩：彩色线段从环状收缩至中心蓝钉  
   - 胜利音效：8-bit风格胜利旋律 + 积分显示（根据操作序列长度评分）  

4. **交互控制**：  
   - **单步模式**：逐步观察组合数计算中m/i参数变化  
   - **自动演示**：AI自动运行（类似贪吃蛇AI），可调速观察不同n的解法差异  

5. **信息同步**：  
   - 代码高亮：右侧同步显示当前计算的C++代码行  
   - 参数面板：实时显示m/M/ans等变量值（像素数字字体）  

> **设计意图**：通过游戏化机制（音效/积分/关卡）降低组合数学的理解门槛，连续段检测的闪烁特效直观呈现核心难点。

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的枚举+组合技巧后，可解决更多环形计数与序列约束问题：

1. **洛谷 P2362** [序列问题]  
   → **推荐理由**：同样需要处理环形序列的终止条件计数，强化对称破环技巧  

2. **洛谷 P2513** [逆序对数列]  
   → **推荐理由**：将组合计数技巧拓展到逆序对场景，训练状态转移思维  

3. **洛谷 P2217** [分割矩阵]  
   → **推荐理由**：非环形但含连续段约束，可对比学习连续条件的数学表征  

---

## 7. 学习心得与经验分享

<insights_intro>
题解中的调试经验是宝贵的学习资源：

> **作者VinstaG173提到**：  
> *“n为偶数时的特判极易遗漏，需在纸上验证小数据（如n=4）”*  
> **Kay点评**：边界特判是组合问题的常见陷阱，建议：  
> ① 用n=3,4等小样例验证公式完备性  
> ② 调试时输出中间变量（如m/tmp值）定位逻辑漏洞  

---

<conclusion>
本次解析揭示了组合计数问题的核心方法论：对称简化→参数枚举→数学优化。通过像素动画的直观演示和代码实现剖析，希望大家不仅能解决本题，更能掌握举一反三的解题思维。下次我们将探索图论中的巧妙计数，继续挑战吧！🚀
</conclusion>
```

---
处理用时：235.79秒