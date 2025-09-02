# 题目信息

# Anton and School - 2

## 题目描述

As you probably know, Anton goes to school. One of the school subjects that Anton studies is Bracketology. On the Bracketology lessons students usually learn different sequences that consist of round brackets (characters "(" and ")" (without quotes)).

On the last lesson Anton learned about the regular simple bracket sequences (RSBS). A bracket sequence $ s $ of length $ n $ is an RSBS if the following conditions are met:

- It is not empty (that is $ n≠0 $ ).
- The length of the sequence is even.
- First ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to "(".
- Last ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to ")".

For example, the sequence "((()))" is an RSBS but the sequences "((())" and "(()())" are not RSBS.

Elena Ivanovna, Anton's teacher, gave him the following task as a homework. Given a bracket sequence $ s $ . Find the number of its distinct subsequences such that they are RSBS. Note that a subsequence of $ s $ is a string that can be obtained from $ s $ by deleting some of its elements. Two subsequences are considered distinct if distinct sets of positions are deleted.

Because the answer can be very big and Anton's teacher doesn't like big numbers, she asks Anton to find the answer modulo $ 10^{9}+7 $ .

Anton thought of this task for a very long time, but he still doesn't know how to solve it. Help Anton to solve this task and write a program that finds the answer for it!

## 说明/提示

In the first sample the following subsequences are possible:

- If we delete characters at the positions $ 1 $ and $ 5 $ (numbering starts with one), we will get the subsequence "(())".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".

The rest of the subsequnces are not RSBS. So we got $ 6 $ distinct subsequences that are RSBS, so the answer is $ 6 $ .

## 样例 #1

### 输入

```
)(()()
```

### 输出

```
6
```

## 样例 #2

### 输入

```
()()()
```

### 输出

```
7
```

## 样例 #3

### 输入

```
)))
```

### 输出

```
0
```

# AI分析结果


# 💡 Kay的C++算法解析：Anton and School - 2 深入学习指南 💡

<introduction>
今天我们来分析CF785D "Anton and School - 2" 这道组合数学与字符串处理的经典问题。本指南将帮助你理解题目核心、掌握组合数学技巧，并通过生动的像素动画演示算法过程。让我们一起探索如何高效计算括号子序列的数量！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`组合数学应用` (范德蒙德卷积)

🗣️ **初步分析**：
> 解决这道题的关键在于**组合数学的巧妙应用**。想象你在玩一个"括号积木"游戏：我们需要从原序列中选取若干括号，使它们形成"前半全左括号，后半全右括号"的结构。这就像用积木搭建一座左塔右堡的城堡！

> - **核心思路**：枚举每个左括号作为子序列的最后一个左括号，利用前缀和快速计算可用括号数量，再通过范德蒙德卷积公式将组合数求和优化为单次组合数计算
> - **算法流程**：预处理前缀和→遍历字符串→遇左括号时计算组合数贡献→累加结果
> - **可视化设计**：在像素动画中，我们将用蓝色方块表示左括号，红色表示右括号。当扫描到关键左括号时，会高亮显示并展示组合数的"积木选择"过程
> - **游戏化元素**：采用复古像素风格，扫描指针像超级玛丽一样移动。计算组合数时播放"拼装"音效，正确累加时显示得分动画，最终展示"城堡建成"的胜利画面

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法优化等维度评估了多篇题解，精选以下3篇≥4星的优质解法：

**题解一（作者：_Life_）**
* **点评**：此解法思路清晰且完整，从暴力思路引出范德蒙德卷积优化，推导过程严谨。代码采用线性预处理阶乘逆元，时间复杂度O(n)达到最优。变量命名规范（fac/inv），边界处理严谨（组合数参数检查），可直接用于竞赛。亮点在于清晰展示了数学推导与代码实现的完美结合。

**题解二（作者：是个汉子）**
* **点评**：解法结构清晰，模块化优秀。将阶乘/逆元初始化封装为独立函数，提高代码复用性。特别值得学习的是逆元数组的倒推计算技巧：inv[i]=inv[i+1]*(i+1)%mod，避免了重复快速幂计算，显著提升效率。代码风格工整易读，实践参考价值高。

**题解三（作者：Last_Reincarnation）**
* **点评**：采用"由浅入深"的教学方式，先展示暴力搜索和特殊数据解法，再引出正解，极大降低了理解门槛。题解中强调的"边界条件测试"(如n<0时的组合数处理)是调试经验的宝贵结晶。代码中详细注释了范德蒙德卷积的应用原理，帮助学习者举一反三。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题的三大核心难点及应对策略如下：

1.  **难点：避免子序列的指数级枚举**
    * **分析**：直接枚举所有子序列会导致O(2^n)复杂度，完全不可行
    * **策略**：通过**枚举关键位置**（最后一个左括号）将问题转化为组合数求和，复杂度降为O(n²)

2.  **难点：组合数求和的复杂度优化**
    * **分析**：朴素实现需要O(n)时间计算每个位置，整体O(n²)仍超时
    * **策略**：运用**范德蒙德卷积公式** ∑C(a,i)C(b,i+1)=C(a+b-1,a)，将求和优化为O(1)计算

3.  **难点：大数组合数的高效计算**
    * **分析**：n可达2e5，需要频繁计算大组合数
    * **策略**：**预处理阶乘+线性求逆元**，实现O(1)的组合数查询

### ✨ 解题技巧总结
<summary_best_practices>
通过本题可提炼以下通用解题技巧：
</summary_best_practices>
- **关键点枚举法**：在序列问题中，枚举分割点/边界点往往能分解问题
- **组合恒等式应用**：范德蒙德卷积可优化形如∑C(n,i)C(m,k-i)的求和
- **模数预处理技巧**：阶乘及其逆元可O(n)预处理，O(1)查询组合数
- **边界防御性编程**：组合数计算需检查n≥m≥0，避免非法访问

---

## 4. C++核心代码实现赏析

<code_intro_overall>
下面展示综合优质题解提炼的通用实现。该代码采用线性预处理+组合数公式，时间复杂度O(n)，空间复杂度O(n)：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合_Life_、是个汉子等题解优化，包含完整预处理和主逻辑
* **完整核心代码**：
```cpp
#include <iostream>
#include <cstring>
#define int long long
using namespace std;

const int MAXN = 200005;
const int MOD = 1e9+7;

char s[MAXN];
int n, ans;
int fac[MAXN], inv[MAXN];
int l[MAXN], r[MAXN]; 

// 快速幂函数（用于初始化逆元）
int power(int base, int exp) {
    int res = 1;
    while (exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

// 预处理阶乘和逆元数组
void precompute() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) 
        fac[i] = fac[i-1] * i % MOD;
    inv[MAXN-1] = power(fac[MAXN-1], MOD-2);
    // 倒推计算逆元：inv[i] = inv[i+1]*(i+1)%mod
    for (int i = MAXN-2; i >= 0; i--) 
        inv[i] = inv[i+1] * (i+1) % MOD;
}

// 组合数计算函数
int C(int n, int m) {
    if (m < 0 || m > n) return 0; // 边界保护
    return fac[n] * inv[m] % MOD * inv[n-m] % MOD;
}

signed main() {
    precompute(); // 初始化阶乘表
    cin >> (s+1);
    n = strlen(s+1);
    
    // 前缀和：l[i]表示[1,i]中'('的数量
    for (int i = 1; i <= n; i++)
        l[i] = l[i-1] + (s[i]=='(');
    
    // 后缀和：r[i]表示[i,n]中')'的数量
    for (int i = n; i >= 1; i--)
        r[i] = r[i+1] + (s[i]==')');
    
    // 枚举每个字符
    for (int i = 1; i <= n; i++) {
        if (s[i]=='(') {
            int a = l[i];      // 当前位置及左侧的'('总数
            int b = r[i+1];    // 当前位置右侧的')'数量
            ans = (ans + C(a+b-1, a)) % MOD; // 范德蒙德卷积应用
        }
    }
    cout << ans << endl;
    return 0;
}
```
* **代码解读概要**：
  1. **预处理阶段**：`precompute()`初始化阶乘数组`fac`和逆元数组`inv`
  2. **前缀/后缀和处理**：`l[i]`记录到i位置的左括号数，`r[i]`记录从i开始的右括号数
  3. **主逻辑循环**：对每个左括号，计算组合数`C(l[i]+r[i+1]-1, l[i])`并累加
  4. **边界保护**：组合数函数中检查`m<0||m>n`，避免非法访问

---
<code_intro_selected>
接下来分析精选题解中的关键代码片段：
</code_intro_selected>

**题解一（作者：_Life_）**
* **亮点**：线性预处理逆元，高效计算组合数
* **核心代码片段**：
```cpp
inv[n] = fastpow(fac[n], mod-2);
for(int i=n-1;i>=0;i--) 
    inv[i] = inv[i+1]*(i+1)%mod; // 逆元递推关系
```
* **代码解读**：
  > 这里展示了逆元数组的**高效计算技巧**。由于`fac[n]`的逆元已知，利用`inv[i] = inv[i+1]*(i+1) % mod`的递推关系，只需O(n)时间即可完成所有逆元计算。相比对每个阶乘单独用快速幂求逆元(O(n log n))，效率显著提升

**题解二（作者：是个汉子）**
* **亮点**：模块化设计与防御性编程
* **核心代码片段**：
```cpp
int C(int n,int m){
    if(n<m||n<0||m<0) return 0; // 边界检查
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
```
* **代码解读**：
  > 此组合数函数体现了**防御性编程思想**。在计算前先检查`n<m`、`n<0`、`m<0`等非法情况，返回0避免内存访问错误。这种严谨性在竞赛编程中至关重要，尤其当组合数参数由复杂表达式计算时

**题解三（作者：Last_Reincarnation）**
* **亮点**：清晰的后缀和实现
* **核心代码片段**：
```cpp
for(int i = n; i >= 1; i--)
    r[i] = r[i+1] + (s[i]==')');  // 后缀和计算
```
* **代码解读**：
  > 后缀和数组`r[i]`的**高效计算方法**：从右向左遍历，`r[i]`的值等于`r[i+1]`加上当前位置是否为右括号。注意数组下标从1开始，需预留`r[n+1]=0`的边界条件。这种处理避免了对每个位置单独循环计算

-----

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
下面设计一个8位像素风格的动画方案，帮助直观理解算法执行过程。主题为"括号城堡建造师"：
</visualization_intro>

  * **动画演示主题**：`像素风括号扫描与组合数计算`
  * **核心演示内容**：算法遍历字符串过程，关键左括号的识别，组合数贡献的图形化表示
  * **设计思路**：采用FC游戏风格，将括号序列可视化为可交互积木。通过颜色区分括号类型，动态展示范德蒙德卷积的"积木组合"过程，音效增强关键操作反馈

  * **动画帧步骤与交互关键点**：

    1. **场景初始化(8位像素风)**：
        - 屏幕顶部显示括号序列：左括号=蓝色砖块，右括号=红色砖块
        - 控制面板：开始/暂停按钮、单步执行、速度滑块(1x-5x)
        - 底部信息栏：当前累计答案 = 0

    2. **扫描指针移动**：
        - 马里奥角色从左向右移动，扫描每个字符
        - 扫描线采用黄色光柱高亮当前字符
        - 背景播放轻快的8位芯片音乐

    3. **关键帧：识别左括号**：
        - 当扫描到左括号时，播放"叮"音效，该砖块闪烁绿光
        - 显示当前变量值：`a = 左侧(数`，`b = 右侧)数`
        - 右侧信息板显示公式：`贡献值 += C(a+b-1, a)`

    4. **组合数可视化(核心)**：
        - 画面分割为两个区域：左侧a个蓝砖，右侧b个红砖
        - 从混合区域(a+b-1个砖块)中选择a个砖块的动画：
            1) 混合区域砖块随机闪烁
            2) 被选中的砖块变为金色，伴随"咔嗒"音效
            3) 最终形成金色路径连接左右区域
        - 底部信息栏更新：`当前贡献 = C(...) = 值`

    5. **结果累计**：
        - 金色路径融入底部城堡建筑
        - 城堡高度随答案增加而增长
        - 播放"金币"音效，得分增加动画

    6. **结束画面**：
        - 扫描完成后，城堡顶部显示最终答案
        - 播放胜利音乐，烟花绽放特效

  * **技术实现要点**：
    - 使用Canvas绘制动态网格，每个字符用16x16像素块表示
    - 音效系统：Web Audio API播放8位音效(扫描声/选择声/得分声)
    - 动画同步：通过requestAnimationFrame实现60FPS流畅动画
    - 游戏化进度：将算法执行转化为城堡建造进度，提升学习动力

<visualization_conclusion>
这个像素动画将抽象的算法转化为直观的建造游戏，帮助理解组合数计算的物理意义，同时增强学习趣味性！
</visualization_conclusion>

-----

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的范德蒙德卷积技巧后，可解决更多组合计数问题：
</similar_problems_intro>

  * **通用技巧迁移**：
    - **排列组合优化**：类似技巧可用于优化多重组合数求和问题
    - **字符串计数**：处理需满足特定模式的子序列计数
    - **概率计算**：二项分布相关概率计算中可应用类似恒等式

  * **练习推荐 (洛谷)**：
    1. **P2307 [NOI2015] 程序自动分析** 
        - 🗣️ 考察离散化与并查集，但包含类似"括号对"的约束条件处理
    2. **P1044 [NOIP2003 普及组] 栈** 
        - 🗣️ 经典的卡特兰数应用，强化组合数学思维
    3. **P2679 [NOIP2015 提高组] 子串** 
        - 🗣️ 动态规划与组合计数的结合，训练状态设计能力

-----

## 7. 学习心得与经验分享 (若有)

<insights_intro>
从题解中提炼的宝贵调试经验：
</insights_intro>

> **参考经验 (来自 Last_Reincarnation)**："我在处理组合数时曾忽略n<0的情况，导致程序崩溃。这提醒我们：**边界条件测试是避免Runtime Error的关键**"
>
> **Kay的总结**：在组合数学问题中要特别注意：
> 1. 组合数参数范围检查（n≥m≥0）
> 2. 前缀和/后缀和数组的边界初始化（sum[0]=0）
> 3. 模运算中负数的处理（ans = (ans%mod+mod)%mod）

<conclusion>
本次关于"Anton and School - 2"的解析就到这里。记住：组合数学的核心在于将问题转化为可计算的模型，而优化常源于数学洞察力。多练习恒等式应用，你也能成为组合高手！下次挑战再见！💪
</conclusion>

---
处理用时：246.67秒