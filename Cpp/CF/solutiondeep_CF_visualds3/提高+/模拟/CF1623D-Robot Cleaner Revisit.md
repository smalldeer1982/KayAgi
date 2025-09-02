# 题目信息

# Robot Cleaner Revisit

## 题目描述

The statement of this problem shares a lot with problem A. The differences are that in this problem, the probability is introduced, and the constraint is different.

A robot cleaner is placed on the floor of a rectangle room, surrounded by walls. The floor consists of $ n $ rows and $ m $ columns. The rows of the floor are numbered from $ 1 $ to $ n $ from top to bottom, and columns of the floor are numbered from $ 1 $ to $ m $ from left to right. The cell on the intersection of the $ r $ -th row and the $ c $ -th column is denoted as $ (r,c) $ . The initial position of the robot is $ (r_b, c_b) $ .

In one second, the robot moves by $ dr $ rows and $ dc $ columns, that is, after one second, the robot moves from the cell $ (r, c) $ to $ (r + dr, c + dc) $ . Initially $ dr = 1 $ , $ dc = 1 $ . If there is a vertical wall (the left or the right walls) in the movement direction, $ dc $ is reflected before the movement, so the new value of $ dc $ is $ -dc $ . And if there is a horizontal wall (the upper or lower walls), $ dr $ is reflected before the movement, so the new value of $ dr $ is $ -dr $ .

Each second (including the moment before the robot starts moving), the robot cleans every cell lying in the same row or the same column as its position. There is only one dirty cell at $ (r_d, c_d) $ . The job of the robot is to clean that dirty cell.

After a lot of testings in problem A, the robot is now broken. It cleans the floor as described above, but at each second the cleaning operation is performed with probability $ \frac p {100} $ only, and not performed with probability $ 1 - \frac p {100} $ . The cleaning or not cleaning outcomes are independent each second.

Given the floor size $ n $ and $ m $ , the robot's initial position $ (r_b, c_b) $ and the dirty cell's position $ (r_d, c_d) $ , find the expected time for the robot to do its job.

It can be shown that the answer can be expressed as an irreducible fraction $ \frac x y $ , where $ x $ and $ y $ are integers and $ y \not \equiv 0 \pmod{10^9 + 7}  $ . Output the integer equal to $ x \cdot y^{-1} \bmod (10^9 + 7) $ . In other words, output such an integer $ a $ that $ 0 \le a < 10^9 + 7 $ and $ a \cdot y \equiv x \pmod {10^9 + 7} $ .

## 说明/提示

In the first test case, the robot has the opportunity to clean the dirty cell every second. Using the [geometric distribution](https://en.wikipedia.org/wiki/Geometric_distribution), we can find out that with the success rate of $ 25\% $ , the expected number of tries to clear the dirty cell is $ \frac 1 {0.25} = 4 $ . But because the first moment the robot has the opportunity to clean the cell is before the robot starts moving, the answer is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623D/1348996177ef0ab22704318e93e1192dad2b1f54.png)Illustration for the first example. The blue arc is the robot. The red star is the target dirt cell. The purple square is the initial position of the robot. Each second the robot has an opportunity to clean a row and a column, denoted by yellow stripes.In the second test case, the board size and the position are different, but the robot still has the opportunity to clean the dirty cell every second, and it has the same probability of cleaning. Therefore the answer is the same as in the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623D/8530d74bbb858250eb8f573d1b14027e43bcb77e.png)Illustration for the second example.The third and the fourth case are almost the same. The only difference is that the position of the dirty cell and the robot are swapped. But the movements in both cases are identical, hence the same result.

## 样例 #1

### 输入

```
6
2 2 1 1 2 1 25
3 3 1 2 2 2 25
10 10 1 1 10 10 75
10 10 10 10 1 1 75
5 5 1 3 2 2 10
97 98 3 5 41 43 50```

### 输出

```
3
3
15
15
332103349
99224487```

# AI分析结果

---
# 💡 Kay的C++算法解析：Robot Cleaner Revisit 深入学习指南 💡

<introduction>
今天我们要分析的题目是“Robot Cleaner Revisit”。这道题结合了机器人移动的周期性分析与概率期望计算，需要我们理解机器人的运动规律，并利用数学方法求解期望时间。让我们一步步拆解问题，掌握核心思路！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学（期望计算）与模拟（周期检测）

🗣️ **初步分析**：
解决这道题的关键在于两点：一是发现机器人移动的周期性规律，二是利用期望的线性性质建立方程求解。  
简单来说，机器人的移动方向（dr, dc）和位置（r, c）会形成一个循环（周期），因为方向只有±1两种可能，位置受限于房间大小，所以状态数有限（最多4nm种）。我们需要先找到这个周期，然后分析周期内每个时间点机器人是否能清理脏点，最后通过期望公式计算总时间。  

题解的核心思路是：  
- **周期检测**：机器人每移动一步，状态（位置+方向）可能重复，形成周期。  
- **期望建模**：在周期内，每个时间点清理成功的概率为p/100，失败则进入下一状态。通过建立周期内的期望方程，联立求解总期望。  

例如，若周期长度为k，每个时间点i的清理失败概率为q_i（若能清理则q_i=1-p/100，否则q_i=1），则总期望满足方程：  
$$ x = q_1(1 + q_2(1 + ... + q_k(1 + x) ... )) $$  
展开后通过模逆元计算分数结果。  

可视化设计上，我们可以用8位像素风格模拟机器人移动：  
- 用不同颜色标记机器人位置（蓝色）、脏点（红色）、已清理区域（黄色）。  
- 每移动一步，播放“滴答”音效；清理成功时播放“叮”声，失败时播放“噗”声。  
- 控制面板支持单步/自动播放，显示当前状态（位置、方向、剩余周期）和概率值变化。

---

## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰性、代码规范性和算法有效性评估，以下题解表现突出（评分≥4星）：
</eval_intro>

**题解一：TonyYin的题解（来源：个人博客）**  
* **点评**：此题解从样例入手，直观展示了机器人的周期运动（如样例一的两步循环），并通过联立方程推导期望公式。代码简洁高效，利用模运算和快速幂处理分数逆元，边界条件处理严谨（如倒序模拟周期）。亮点在于通过观察一维周期（2(n-1)和2(m-1)）直接确定总周期为4(n-1)(m-1)，避免了暴力搜索，时间复杂度低。

**题解二：GaryH的题解（来源：Codeforces讨论区）**  
* **点评**：此题解明确提出用四元组（dr, dc, r, c）记录状态，通过map检测循环节，逻辑清晰。期望方程的推导（T = Σ(q^{i-1}pt_i) + q^k(z+T)）直观易懂，代码中使用数组记录时间点，结合逆元计算，实践价值高。适合理解周期检测与期望方程的结合。

**题解三：Priestess_SLG的题解（来源：Codeforces提交）**  
* **点评**：此题解直接推导了期望的闭合表达式（x = Σf_i / (1 - Πp_i)，其中f_i是前i个失败概率的乘积），数学推导简洁。代码通过预处理周期内的失败概率，线性计算分子和分母，时间复杂度O(k)（k为周期长度），适合追求代码简洁性的学习者。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点在于周期性分析和期望方程的建立。以下是关键步骤和应对策略：
</difficulty_intro>

1.  **关键点1：机器人移动的周期性检测**  
    * **分析**：机器人状态由位置（r,c）和方向（dr,dc）决定，方向只有±1两种可能，位置受限于n和m，因此状态总数最多为4nm（每个位置有4种方向组合）。通过模拟移动并记录状态，可检测到循环节。  
    * 💡 **学习笔记**：周期检测是处理无限循环问题的关键，通过记录已访问状态可快速找到循环。

2.  **关键点2：期望方程的建立与求解**  
    * **分析**：周期内每个时间点i的清理失败概率q_i（能清理则q_i=1-p/100，否则q_i=1）。总期望x满足方程：x = q_1(1 + q_2(1 + ... + q_k(1 + x)...))。展开后移项可得x = (Σq_1q_2...q_i) / (1 - q_1q_2...q_k)。  
    * 💡 **学习笔记**：期望的线性性质允许将无限过程转化为有限方程，关键是找到周期内的失败概率乘积和求和。

3.  **关键点3：模运算下的分数处理**  
    * **分析**：题目要求输出分数x/y的模逆元结果（x·y⁻¹ mod 1e9+7）。需用快速幂计算逆元（如100的逆元是100^(mod-2) mod mod），并在计算过程中保持模运算的正确性。  
    * 💡 **学习笔记**：模逆元是处理分数取模的核心工具，需熟练掌握快速幂求逆元的方法。

### ✨ 解题技巧总结
- **周期模拟**：用四元组（dr, dc, r, c）记录状态，避免重复计算。  
- **期望方程简化**：将无限循环的期望转化为周期内的有限和与乘积，利用闭合公式求解。  
- **模运算优化**：预处理失败概率的乘积和求和，减少重复计算，确保每一步都取模防止溢出。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合多个优质题解的通用核心实现，结合了周期检测与期望计算，代码简洁高效。
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：本代码综合了TonyYin和GaryH的题解思路，通过模拟周期内的移动，计算失败概率的乘积和求和，最终用逆元求解期望。  
* **完整核心代码**：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int fast_pow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

int inv(int x) { return fast_pow(x, MOD - 2); }

void solve() {
    int n, m, rb, cb, rd, cd, p;
    cin >> n >> m >> rb >> cb >> rd >> cd >> p;
    int q = (100 - p) * inv(100) % MOD; // 失败概率（模意义下）
    int dr = 1, dc = 1;

    vector<int> prob_list; // 存储周期内每个时间点的失败概率
    map<tuple<int, int, int, int>, bool> vis; // 记录状态（dr, dc, r, c）

    int r = rb, c = cb;
    while (true) {
        auto state = make_tuple(dr, dc, r, c);
        if (vis.count(state)) break;
        vis[state] = true;

        // 判断当前位置是否能清理脏点
        int can_clean = (r == rd || c == cd) ? 1 : 0;
        prob_list.push_back(can_clean ? q : 1); // 不能清理则失败概率为1

        // 移动并更新方向
        int nr = r + dr, nc = c + dc;
        if (nr < 1 || nr > n) dr = -dr;
        if (nc < 1 || nc > m) dc = -dc;
        r += dr;
        c += dc;
    }

    // 计算分子（sum f_i）和分母（1 - product f_i）
    int product = 1, sum = 0;
    for (int f : prob_list) {
        product = 1LL * product * f % MOD;
        sum = (sum + product) % MOD;
    }
    int denominator = (1 - product + MOD) % MOD;
    int ans = 1LL * sum * inv(denominator) % MOD;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
```
* **代码解读概要**：  
代码首先模拟机器人移动，记录每个状态（方向+位置）以检测周期。周期内每个时间点，根据是否能清理脏点，记录失败概率q或1。然后计算周期内失败概率的乘积（product）和累加和（sum），最终用公式sum/(1-product)求得期望，并通过逆元处理模运算。

---
<code_intro_selected>
接下来，分析优质题解的核心代码片段，学习其亮点。
</code_intro_selected>

**题解一：TonyYin的代码片段**  
* **亮点**：通过观察一维周期（2(n-1)和2(m-1)）直接确定总周期为4(n-1)(m-1)，避免暴力状态记录，时间复杂度O(4(n-1)(m-1))。  
* **核心代码片段**：  
```cpp
int u = 0, v = 1;
dx = dy = -1; // 倒序模拟
for(int cas = 1; cas <= 4 * (n - 1) * (m - 1); cas++) { 
    if(ax + dx > n || ax + dx < 1) dx = -dx;
    if(ay + dy > m || ay + dy < 1) dy = -dy;
    ax += dx; ay += dy;
    u = (u + 1) % mod;
    if(ax == bx || ay == by) u = u * pp % mod, v = v * pp % mod;
}
cout << u * inv(mod + 1 - v) % mod << endl;
```
* **代码解读**：  
这段代码通过倒序模拟周期（4(n-1)(m-1)步），计算u（分子）和v（失败概率乘积）。每一步更新u（累加时间）和v（乘积），若当前位置能清理脏点，则u和v乘以失败概率q。最终ans = u/(1-v)，用逆元计算。  
* 💡 **学习笔记**：利用一维周期的最小公倍数确定总周期，可简化状态检测，适合n和m较大的情况。

**题解二：Priestess_SLG的代码思路**  
* **亮点**：直接推导期望的闭合公式（x = Σf_i / (1 - Πf_i)），代码线性计算分子和分母，时间复杂度O(k)（k为周期长度）。  
* **核心代码逻辑**：  
```cpp
vector<int> prob_list; // 周期内失败概率列表
int product = 1, sum = 0;
for (int f : prob_list) {
    product = product * f % MOD;
    sum = (sum + product) % MOD;
}
int ans = sum * inv(1 - product + MOD) % MOD;
```
* **代码解读**：  
product记录周期内失败概率的乘积（Πf_i），sum记录前i项乘积的和（Σf_1...f_i）。最终ans = sum / (1 - product)，通过逆元处理模运算。  
* 💡 **学习笔记**：闭合公式避免了复杂的方程联立，适合快速编码实现。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

\<visualization_intro\>
为了直观理解机器人的周期运动和期望计算过程，我们设计一个“像素机器人清洁大冒险”的8位风格动画！
\</visualization_intro\>

  * **动画演示主题**：像素机器人的清洁之旅  
  * **核心演示内容**：展示机器人在房间内的周期性移动，标记每个时间点是否能清理脏点，并动态计算期望时间的累加过程。  

  * **设计思路简述**：  
采用8位像素风格（类似FC游戏），用不同颜色区分机器人（蓝色方块）、脏点（红色星星）、已清理区域（黄色条纹）。通过单步/自动播放，观察机器人方向变化（箭头标记dr/dc）和周期循环，配合音效强化关键操作（移动“滴答”、清理成功“叮”、失败“噗”）。

  * **动画帧步骤与交互关键点**：  

    1.  **场景初始化**：  
        - 绘制n×m的网格房间（每格16x16像素），用深灰色表示墙壁。  
        - 机器人（蓝色方块）初始位置（rb, cb），脏点（红色星星）在（rd, cd）。  
        - 控制面板：开始/暂停、单步、重置按钮，速度滑块（1-10倍速）。  
        - 播放8位风格背景音乐（轻快的电子旋律）。

    2.  **周期检测与移动演示**：  
        - 每移动一步（单步/自动），机器人按dr/dc方向移动，方向变化时（撞墙）播放“叮”声，箭头（↑/↓/←/→）闪烁。  
        - 用淡紫色标记已访问的状态（位置+方向），当状态重复时，显示“发现周期！”提示。  

    3.  **清理概率与期望计算**：  
        - 当前时间点若能清理（同列/行），脏点周围出现黄色条纹，显示概率“p%”；否则显示“无清理”。  
        - 右侧面板动态更新：失败概率q的累乘（product）、时间累加（sum）、当前期望（sum/(1-product)）。  

    4.  **目标达成与反馈**：  
        - 若清理成功（概率触发），播放“胜利”音效，机器人变绿色，显示“成功！时间：t秒”。  
        - 若周期结束未成功，显示“进入下一轮周期”，时间累加周期长度z。  

  * **旁白提示**：  
    - “看！机器人撞到下边界了，方向dr变成-1！”  
    - “当前位置和脏点同列，有25%的概率清理成功哦～”  
    - “状态重复了，说明机器人进入循环啦！”

\<visualization_conclusion\>
通过这个动画，我们能直观看到机器人的周期运动、清理概率的影响，以及期望时间的计算过程，让抽象的数学公式“动”起来！
\</visualization_conclusion\>

---

## 6\. 拓展练习与相似问题思考

\<similar_problems_intro\>
本题的核心是周期检测与期望计算，这类思路在以下场景也有应用：
\</similar_problems_intro\>

  * **通用思路/技巧迁移**：  
    - 周期性运动问题（如行星轨道、钟表指针）：通过周期检测简化无限过程。  
    - 概率期望问题（如抽奖、游戏暴击）：利用期望的线性性质建立方程。  
    - 模逆元计算（如分数取模、组合数）：快速幂求逆元是关键工具。  

  * **练习推荐 (洛谷)**：  
    1.  **洛谷 P1297 [国家集训队]单选错位**  
        * 🗣️ **推荐理由**：考察期望的线性性质，需分析题目中的周期性规律，与本题思路类似。  
    2.  **洛谷 P4316 绿豆蛙的归宿**  
        * 🗣️ **推荐理由**：经典期望DP问题，需建立反向图计算期望，适合练习期望方程的建立。  
    3.  **洛谷 P3811 乘法逆元**  
        * 🗣️ **推荐理由**：直接练习模逆元的计算，是解决本题分数取模的基础。  

---

## 7\. 学习心得与经验分享 (若有)

\<insights_intro\>
部分题解作者分享了调试经验，例如TonyYin提到“倒序模拟周期可以避免状态重复检测的麻烦”，这对我们有重要参考意义：
\</insights_intro\>

> **参考经验 (来自 TonyYin)**：“在模拟周期时，直接利用一维周期的最小公倍数（如4(n-1)(m-1)）可以避免用map记录状态，减少代码复杂度和时间消耗。”  
> **点评**：作者的经验提醒我们，观察问题的数学性质（如一维周期的LCM）可以简化实现，这在处理大n/m时尤为重要。遇到周期性问题，先分析其数学规律，可能比暴力模拟更高效！

---

\<conclusion\>
通过对“Robot Cleaner Revisit”的分析，我们掌握了周期检测、期望方程建立和模逆元计算的核心技巧。希望大家能举一反三，在类似问题中灵活运用这些方法。编程的乐趣在于探索，继续加油吧！💪
\</conclusion\>

---
处理用时：149.75秒