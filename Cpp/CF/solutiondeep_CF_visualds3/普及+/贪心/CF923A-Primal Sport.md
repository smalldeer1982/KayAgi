# 题目信息

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20
```

### 输出

```
15
```

## 样例 #3

### 输入

```
8192
```

### 输出

```
8191
```

# AI分析结果


### 💡 Kay的C++算法解析：Primal Sport 深入学习指南 💡

<introduction>
今天我们分析「Primal Sport」这道C++编程题。这道题要求根据给定的$X_2$反推最小的起始数$X_0$，涉及质数操作和逆向推导。本指南将帮助你理解核心算法、掌握解题技巧，并通过像素动画直观理解算法流程。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学推导 + 线性筛法预处理` (算法分类：数学/枚举)

🗣️ **初步分析**：
> 解决本题如同在迷宫中倒退行走：我们从终点$X_2$出发，用质数这把"钥匙"打开上一扇门找到$X_1$，再用同样方法找到起点$X_0$。  
> - **核心思路**：利用不等式关系反推。给定$X_2$，$X_1$的范围是$[X_2-p_2+1, X_2]$（$p_2$是$X_2$的最大质因数）。同理，$X_0$的范围是$[X_1-p_1+1, X_1]$（$p_1$是$X_1$的最大质因数）。
> - **关键技巧**：使用线性筛法在$O(n)$时间内预处理每个数的最大质因数，避免重复计算。
> - **可视化设计**：在复古像素动画中，用网格表示数字序列（3→$X_2$），质数用蓝色方块、合数用绿色方块。倒退时高亮当前数字（红色边框），显示质因数分解过程（金色粒子特效），音效标记关键操作（"叮"声表示质因数选择）。

---

## 2. 精选优质题解参考

<eval_intro>
基于思路清晰度、代码规范性、算法优化度等标准，我精选了3份优质题解：

**题解一（来源：ModestCoder_）**
* **点评**：该解法使用线性筛法预处理最大质因数，代码结构清晰严谨。亮点在于：
  - 筛法过程中同步记录最大质因数（`a[i*prime[j]]=a[i]`），利用筛法性质保证正确性
  - 变量命名规范（`a[]`表最大质因数，`flag[]`标记合数）
  - 边界处理完整（跳过质数$X_1$）
  - 时间复杂度$O(n)$，空间优化到位

**题解二（来源：Blunt_Feeling）**
* **点评**：采用埃筛思想预处理最大质因数，代码简洁高效：
  - 外层循环判断质数后直接标记其倍数
  - 用`a[j]=i`更新合数的最大质因数
  - 枚举$X_1$时直接调用预处理结果
  - 虽略逊于线性筛但代码更简短

**题解三（来源：Patrickpwq）**
* **点评**：线性筛法实现与题解一类似：
  - 正确性保障：`a[i*prime[j]]=a[i]`的传递性证明充分
  - 用`bitset`优化空间占用
  - 枚举时显式跳过质数$X_1$
  - 可读性稍弱但算法本质正确

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破三个核心难点：

1.  **倒退关系建模**  
    * **分析**：$X_1$范围$[X_2-p_2+1, X_2]$（$p_2$为$X_2$最大质因数），同理$X_0$依赖$X_1$的质因数。关键是通过数学证明确定区间边界。
    * 💡 **学习笔记**：逆向推导需严格依赖质数操作的定义约束。

2.  **高效获取最大质因数**  
    * **分析**：暴力分解质因数（$O(\sqrt{n})$）在$n=10^6$时会超时。必须用筛法预处理：
      - 线性筛：时空复杂度$O(n)$，同步记录最大质因数
      - 埃筛：实现更简单但部分重复计算
    * 💡 **学习笔记**：筛法预处理是处理质数相关问题的核心技巧。

3.  **枚举范围优化**  
    * **分析**：$X_1$只需在$[X_2-p_2+1, X_2]$内取合数（质数无法产生合法$X_0$）。预处理后$X_0$计算降为$O(1)$。
    * 💡 **学习笔记**：利用问题约束（$X_0 \geq 3$）可大幅缩小搜索空间。

### ✨ 解题技巧总结
<summary_best_practices>
综合本题经验，总结以下通用技巧：
</summary_best_practices>
- **逆向推导法**：从结果反推初始状态，结合数学不等式建模
- **预处理优化**：对频繁使用的数据（如质因数）预先计算存储
- **边界敏感处理**：特别注意质数/合数的不同处理逻辑
- **算法选择评估**：埃筛代码简洁，线性筛效率更优

---

## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个综合优质题解的精炼实现：

**本题通用核心C++实现参考**
* **说明**：基于线性筛法预处理，融合题解一和三的优点
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 10;

int main() {
    int x2;
    cin >> x2;
    
    // 线性筛预处理
    vector<int> a(N);       // 最大质因数
    vector<bool> flag(N);  // 合数标记
    vector<int> primes;    // 质数表
    for (int i = 2; i <= x2; ++i) {
        if (!flag[i]) {
            primes.push_back(i);
            a[i] = i;      // 质数的最大质因数是自身
        }
        for (int p : primes) {
            if (i * p > x2) break;
            flag[i * p] = true;
            a[i * p] = a[i];  // 关键传递
            if (i % p == 0) break;
        }
    }

    // 计算X0最小值
    int p2 = a[x2]; 
    int ans = x2;
    for (int x1 = x2 - p2 + 1; x1 <= x2; ++x1) {
        if (!flag[x1]) continue;  // 跳过质数
        ans = min(ans, x1 - a[x1] + 1);
    }
    cout << ans << endl;
    return 0;
}
```
* **代码解读概要**：
  > 1. **预处理阶段**：线性筛法标记合数并记录最大质因数。质数`i`的`a[i]=i`，合数`i*p`的`a[i*p]=a[i]`  
  > 2. **核心逻辑**：获取$X_2$的最大质因数$p_2$，在区间$[X_2-p_2+1, X_2]$枚举$X_1$（仅合数）  
  > 3. **结果计算**：对每个$X_1$计算$X_0=X_1-p_1+1$，取最小值

---
<code_intro_selected>
各优质题解的核心片段解析：

**题解一片段（来源：ModestCoder_）**
* **亮点**：线性筛同步处理质因数的优雅实现
* **核心代码片段**：
```cpp
for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
    flag[i * prime[j]] = 1;
    a[i * prime[j]] = a[i];  // 传递最大质因数
    if (i % prime[j] == 0) break;
}
```
* **代码解读**：
  > 这段代码是线性筛的核心。当用`prime[j]`筛合数`i*prime[j]`时：
  > - `flag[]`标记合数
  > - `a[i*prime[j]]=a[i]`继承最大质因数（证明：当`i%prime[j]==0`时，`a[i]`已含该因子；否则`prime[j]`是最大质因数）
  > - `i%prime[j]==0`时跳出保证$O(n)$复杂度
* 💡 **学习笔记**：线性筛中合数的最大质因数由其因子继承而来

**题解二片段（来源：Blunt_Feeling）**
* **亮点**：埃筛直接更新最大质因数，代码极简
* **核心代码片段**：
```cpp
For(i, 2, x2) if (!a[i])  // 发现质数
    for (int j = i * 2; j <= x2; j += i)
        a[j] = i;  // 更新倍数
```
* **代码解读**：
  > - 外层循环遇到质数`i`时（`!a[i]`），内层更新其所有倍数
  > - `a[j]=i`将当前质数作为合数`j`的最大质因数（后续更大质数会覆盖）
  > - 实际保存的是最大质因数（因为外层循环从小到大，最后处理的质因数最大）
* 💡 **学习笔记**：埃筛中合数的最大质因数即最后标记的质因数

**题解三片段（来源：Patrickpwq）**
* **亮点**：`bitset`优化空间，工业级实现
* **核心代码片段**：
```cpp
bitset <1000005> is;  // 合数标记
for (int i = 2; i <= n; i++) {
    if (is[i] == 0) {    
        big[i] = i;   // 质数处理
        prime[++cnt] = i;
    }   
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
        is[i * prime[j]] = 1;
        big[i * prime[j]] = big[i];  // 传递
        if (i % prime[j] == 0) break;
    }
}
```
* **代码解读**：
  > - `bitset`压缩标记数组，减少内存占用
  > - 质数单独处理（`big[i]=i`）
  > - 合数继承`big[i]`的逻辑与题解一一致
  > - 循环条件优化防止越界
* 💡 **学习笔记**：`bitset`可高效处理大数组标记

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
设计「质数迷宫倒退记」像素动画，帮你直观理解倒退推导过程：

* **主题**：8位像素风格，类似复古RPG迷宫探索
* **核心演示**：从$X_2$倒退寻找$X_1$和$X_0$，动态展示质因数分解

* **设计实现**：
  1. **场景构建**：
     - 垂直网格：1列多行，数字从下(3)到上($X_2$)
     - 质数→蓝色方块，合数→绿色方块，当前数字→闪烁红框
     - 控制面板：开始/暂停、单步、速度滑块（复古按钮样式）

  2. **初始化阶段**：
     - 显示$X_2$位置（顶部），播放"登场"音效
     - 分解$X_2$质因数：粒子特效展示$p_2$计算
     - 高亮区间$[X_2-p_2+1, X_2]$（红色遮罩覆盖）

  3. **倒退阶段**：
     - **单步模式**：按空格键逐步移动焦点到候选$X_1$
     - **自动模式**：AI自动遍历区间（速度可调），类似贪吃蛇移动
     - 遇到$X_1$时：显示其质因数分解（金色粒子），计算$X_0=X_1-p_1+1$
     - 音效：选择数字("叮")，错误("哔")，找到解("胜利号角")

  4. **结果展示**：
     - 回溯路径：$X_2$→$X_1$→$X_0$显示发光路径
     - 显示最小$X_0$位置，播放庆祝动画（像素烟花+得分显示）

  5. **游戏化元素**：
     - 计分系统：$X_0$越小得分越高
     - 关卡制：每关对应不同$X_2$，通关解锁更复杂数字
     - 背景音乐：8-bit风格循环BGM

* **技术要点**：
  - Canvas绘制网格和动画
  - 关键帧控制：质因数分解→区间高亮→路径回溯
  - Web Audio API实现音效：不同操作触发不同音频

</visualization_intro>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题核心思想后，可挑战以下相似问题：

* **通用技巧迁移**：
  - 质因数分解预处理：P1075（质因数分解）
  - 数学逆向推导：P2926（反推初始状态）
  - 筛法优化：P3383（线性筛质数）

* **洛谷练习推荐**：
  1. **P1075** - 质因数分解  
     🗣️ **推荐理由**：直接应用质因数分解，巩固筛法基础
  2. **P1217** - 回文质数  
     🗣️ **推荐理由**：结合质数与回文判断，练习筛法优化
  3. **P1372** - 又是毕业季  
     🗣️ **推荐理由**：训练数学推导能力，理解范围约束
  4. **P2926** - 反推问题  
     🗣️ **推荐理由**：强化逆向推导思维，迁移本题解法

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中的调试经验值得借鉴：

> **参考经验**：多位作者强调在线性筛中验证`a[i*prime[j]]=a[i]`的正确性  
> **点评**：通过小数据验证（如$X_2=6,20$）可快速发现逻辑错误。建议：
> - 编写`print_debug`函数输出中间状态
> - 对边界值($X_2$=质数/合数)单独测试
> - 画图辅助理解最大质因数传递

---

<conclusion>
本次分析帮助你深入理解「Primal Sport」的数学本质和实现技巧。记住：
1. 逆向推导需严格依赖数学约束
2. 筛法预处理是质数问题的通用优化手段
3. 边界处理决定代码鲁棒性

尝试用像素动画可视化算法，并在洛谷练习巩固。下次我们将探索更有趣的数学问题！💪
</conclusion>

---
处理用时：311.21秒