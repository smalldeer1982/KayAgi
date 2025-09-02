# 题目信息

# Danger of Mad Snakes

## 题目描述

Mr. Chanek The Ninja is one day tasked with a mission to handle mad snakes that are attacking a site. Now, Mr. Chanek already arrived at the hills where the destination is right below these hills. The mission area can be divided into a grid of size $ 1000 \times 1000 $ squares. There are $ N $ mad snakes on the site, the i'th mad snake is located on square $ (X_i, Y_i) $ and has a danger level $ B_i $ .

Mr. Chanek is going to use the Shadow Clone Jutsu and Rasengan that he learned from Lord Seventh to complete this mission. His attack strategy is as follows:

1. Mr. Chanek is going to make $ M $ clones.
2. Each clone will choose a mad snake as the attack target. Each clone must pick a different mad snake to attack.
3. All clones jump off the hills and attack their respective chosen target at once with Rasengan of radius $ R $ . If the mad snake at square $ (X, Y) $ is attacked with a direct Rasengan, it and all mad snakes at squares $ (X', Y') $ where $ max(|X' - X|, |Y' - Y|) \le R $ will die.
4. The real Mr. Chanek will calculate the score of this attack. The score is defined as the square of the sum of the danger levels of all the killed snakes.

Now Mr. Chanek is curious, what is the sum of scores for every possible attack strategy? Because this number can be huge, Mr. Chanek only needs the output modulo $ 10^9 + 7 $ .

## 说明/提示

Here is the illustration of all six possible attack strategies. The circles denote the chosen mad snakes, and the blue squares denote the region of the Rasengan:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1425D/5a0ae1573d7d9d31c9abffd632aa62031298b56e.png)So, the total score of all attacks is: $ 3.600 + 3.600 + 4.900 + 3.600 + 10.000 + 8.100 = 33.800 $ .

## 样例 #1

### 输入

```
4 2 1
1 1 10
2 2 20
2 3 30
5 2 40```

### 输出

```
33800```

# AI分析结果

---
# 💡 Kay的C++算法解析：Danger of Mad Snakes 深入学习指南 💡

<introduction>
今天我们来一起分析“Danger of Mad Snakes”这道C++编程题。本指南将帮助大家梳理题目思路，理解如何通过组合数学和二维前缀和解决此类问题，并掌握关键解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`组合数学与二维前缀和应用`

🗣️ **初步分析**：
解决这道题的关键在于将“和的平方”分解为“平方的和”与“两两乘积的和”，并分别计算它们的贡献次数。简单来说，组合数学用于计算不同选择策略的数量，二维前缀和则用于快速统计某个矩形区域内的蛇的数量（即覆盖范围）。

在本题中，我们需要：
- 将总得分展开为 $\sum B_i^2 \times \text{包含}i\text{的方案数} + \sum_{i<j} 2B_iB_j \times \text{同时包含}i,j\text{的方案数}$。
- 用二维前缀和快速计算每个蛇的覆盖区域（以蛇为中心，切比雪夫距离≤R的正方形内的蛇数），以及两个蛇的共同覆盖区域（两正方形的交集内的蛇数）。
- 利用容斥原理计算“至少包含某个区域”的方案数，例如：包含蛇i的方案数 = 总方案数 - 不包含i的方案数（即所有选择的蛇都不在i的覆盖区域内的方案数）。

可视化设计思路：采用8位像素风格的网格地图，用不同颜色标记蛇的位置（如红色方块）、覆盖区域（蓝色透明方块）。动画中，当选择M个蛇时，动态展示每个选择的覆盖区域如何叠加，并用数字显示当前覆盖的蛇数。关键步骤（如计算交集、容斥组合数）用文字气泡和音效提示（如“叮”声表示覆盖区域计算完成）。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和算法有效性，以下题解质量较高（≥4星）：
</eval_intro>

**题解一：作者Fairicle**
* **点评**：此题解思路清晰，直接点明“分解平方和”的关键，并详细推导了每对蛇的贡献计算方式。代码规范，变量名（如`calc_pre`计算前缀和）含义明确，边界处理严谨（如`max(1,x)`限制坐标范围）。亮点在于对容斥原理的灵活应用，特别是对“同时包含i和j的方案数”的计算，通过`C(n,m)-C(n-num,m)`快速求解，时间复杂度为O(N²)，适合本题数据范围。

**题解二：作者出言不逊王子**
* **点评**：此题解对平方展开的数学推导非常详细，明确区分了“平方项”和“乘积项”的贡献。代码中`qsum`函数实现了二维前缀和查询，逻辑清晰。亮点在于对容斥过程的解释（如“无法同时碰到i和j的方案数”的计算），并通过取模细节处理避免了负数问题，代码健壮性强。

**题解三：作者jasonliujiahua**
* **点评**：此题解从集合论角度深入分析了容斥原理的本质（如$A_{B_i}\cap A_{B_j}=A_{B_i\cup B_j}$的证明），理论深度突出。代码结构工整，`init`函数预处理组合数和前缀和，`work`函数分离计算逻辑，可读性高。亮点在于对数学原理的透彻解释，帮助学习者理解“为什么这样算”。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们通常会遇到以下核心难点，结合优质题解的共性，提炼解决策略：
</difficulty_intro>

1.  **关键点1：平方和的分解与贡献拆分**
    * **分析**：总得分是“和的平方”，直接计算所有策略的和的平方非常困难。优质题解通过展开平方公式，将问题拆分为“每个蛇的平方项”和“每对蛇的乘积项”，分别计算它们的贡献次数。例如，$(a+b+c)^2 = a²+b²+c²+2ab+2ac+2bc$，因此总得分等于所有蛇的平方项贡献加上所有蛇对的乘积项贡献的两倍。
    * 💡 **学习笔记**：遇到“和的平方”问题时，优先考虑展开为平方项和乘积项，分别计算贡献。

2.  **关键点2：覆盖区域的快速计算（二维前缀和）**
    * **分析**：需要快速计算“以某蛇为中心，切比雪夫距离≤R的正方形内的蛇数”，以及“两个蛇覆盖区域的交集内的蛇数”。优质题解使用二维前缀和数组`sum`，通过`sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1]`实现O(1)查询，避免了O(N²)的暴力枚举。
    * 💡 **学习笔记**：二维前缀和是处理网格区域统计问题的“利器”，预处理时间复杂度为O(N²)，查询为O(1)。

3.  **关键点3：容斥原理计算方案数**
    * **分析**：计算“至少包含蛇i的方案数”时，直接计算较难，优质题解采用“正难则反”：总方案数 - 所有选择的蛇都不包含i的方案数（即从非覆盖i的蛇中选M个）。类似地，计算“同时包含i和j的方案数”需要容斥处理交集和并集的情况。
    * 💡 **学习笔记**：容斥原理的核心是“总方案数减去不满足条件的方案数”，适用于“至少包含某条件”的计数问题。

### ✨ 解题技巧总结
- **问题分解**：将复杂问题（和的平方）拆分为简单子问题（平方项和乘积项），分别求解。
- **预处理组合数**：提前计算阶乘和逆元，快速获取组合数C(n,m)，避免重复计算。
- **边界处理**：在二维前缀和查询时，用`max(1, x)`和`min(1000, x)`限制坐标范围，防止越界。
- **模运算细节**：所有减法操作后加模数再取模，避免负数结果（如`(a - b + mod) % mod`）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，代码清晰且覆盖所有关键逻辑。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Fairicle、出言不逊王子等题解的思路，包含预处理组合数、二维前缀和计算覆盖区域、容斥计算贡献次数等核心逻辑。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int MOD = 1e9 + 7;
    const int N = 2010; // 蛇的数量上限
    const int MAX_COORD = 1000; // 网格最大坐标

    ll n, m, r;
    ll x[N], y[N], a[N]; // 蛇的坐标和危险值
    ll sum[MAX_COORD + 2][MAX_COORD + 2]; // 二维前缀和数组
    ll fac[N], inv_fac[N]; // 阶乘和逆元

    // 快速幂求逆元
    ll qpow(ll x, ll y) {
        ll res = 1;
        while (y) {
            if (y & 1) res = res * x % MOD;
            x = x * x % MOD;
            y >>= 1;
        }
        return res;
    }

    // 预处理阶乘和逆元
    void init_comb() {
        fac[0] = 1;
        for (int i = 1; i < N; ++i)
            fac[i] = fac[i - 1] * i % MOD;
        inv_fac[N - 1] = qpow(fac[N - 1], MOD - 2);
        for (int i = N - 2; i >= 0; --i)
            inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
    }

    // 计算组合数C(n, k)
    ll C(ll n, ll k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD;
    }

    // 二维前缀和查询矩形(x1,y1)-(x2,y2)内的蛇数
    ll query(int x1, int y1, int x2, int y2) {
        x1 = max(x1, 1); y1 = max(y1, 1);
        x2 = min(x2, MAX_COORD); y2 = min(y2, MAX_COORD);
        if (x1 > x2 || y1 > y2) return 0;
        return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);

        init_comb();
        cin >> n >> m >> r;
        for (int i = 1; i <= n; ++i) {
            cin >> x[i] >> y[i] >> a[i];
            sum[x[i]][y[i]]++; // 初始化前缀和数组
        }

        // 构建二维前缀和数组
        for (int i = 1; i <= MAX_COORD; ++i)
            for (int j = 1; j <= MAX_COORD; ++j)
                sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];

        ll ans = 0;
        // 计算每个蛇的平方项贡献
        for (int i = 1; i <= n; ++i) {
            int cover_i = query(x[i] - r, y[i] - r, x[i] + r, y[i] + r);
            ll cnt = (C(n, m) - C(n - cover_i, m) + MOD) % MOD;
            ans = (ans + a[i] * a[i] % MOD * cnt) % MOD;
        }

        // 计算每对蛇的乘积项贡献
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                // 计算i和j的共同覆盖区域
                int x1 = max(x[i] - r, x[j] - r);
                int y1 = max(y[i] - r, y[j] - r);
                int x2 = min(x[i] + r, x[j] + r);
                int y2 = min(y[i] + r, y[j] + r);
                int common = query(x1, y1, x2, y2);

                // 计算i和j各自的覆盖区域（减去共同部分）
                int cover_i = query(x[i] - r, y[i] - r, x[i] + r, y[i] + r) - common;
                int cover_j = query(x[j] - r, y[j] - r, x[j] + r, y[j] + r) - common;

                // 计算同时包含i和j的方案数（容斥）
                ll total = C(n, m);
                ll not_common = C(n - common, m);
                ll not_i = C(n - common - cover_i, m);
                ll not_j = C(n - common - cover_j, m);
                ll not_any = C(n - common - cover_i - cover_j, m);
                ll cnt = (total - not_common + MOD) % MOD;
                cnt = (cnt + (not_common - not_i - not_j + not_any + MOD) % MOD) % MOD;

                ans = (ans + 2 * a[i] * a[j] % MOD * cnt) % MOD;
            }
        }

        cout << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：
  1. **预处理**：`init_comb`函数计算阶乘和逆元，用于快速获取组合数。
  2. **二维前缀和**：通过遍历网格，构建`sum`数组，支持O(1)查询矩形区域内的蛇数。
  3. **平方项计算**：对每个蛇i，计算其覆盖区域内的蛇数`cover_i`，用`C(n,m)-C(n-cover_i,m)`得到包含i的方案数，乘以$B_i^2$累加到答案。
  4. **乘积项计算**：对每对蛇i,j，计算共同覆盖区域`common`，以及各自的覆盖区域（减去共同部分），通过容斥计算同时包含i和j的方案数，乘以$2B_iB_j$累加到答案。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，理解其亮点和关键逻辑。
</code_intro_selected>

**题解一：作者Fairicle（核心代码片段）**
* **亮点**：`calc_pre`函数规范处理边界条件，`C`函数直接计算组合数，代码简洁高效。
* **核心代码片段**：
    ```cpp
    inline ll C(int m,int n){
        if(n<0||m<0||m>n) return 0;
        return fac[n]*inv[m]%mod*inv[n-m]%mod;
    }
    inline int calc_pre(int x,int y,int _x,int _y){
        x=max(1,x),_x=min(1000,_x),y=max(1,y),_y=min(1000,_y);
        if(x>_x||y>_y) return 0;
        return s[_x][_y]-s[x-1][_y]-s[_x][y-1]+s[x-1][y-1];
    }
    ```
* **代码解读**：
  - `C`函数：利用预处理的阶乘和逆元快速计算组合数，处理了边界情况（如m>n时返回0）。
  - `calc_pre`函数：通过`max`和`min`限制坐标范围，避免越界，然后用二维前缀和公式计算矩形区域内的蛇数。这是覆盖区域计算的核心。
* 💡 **学习笔记**：边界条件处理是二维前缀和的关键，`max`和`min`确保坐标在网格范围内。

**题解二：作者jasonliujiahua（核心代码片段）**
* **亮点**：将容斥原理的数学推导转化为代码，`work`函数分离平方项和乘积项的计算，逻辑清晰。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=n;i++){ // ai^2
        int num=(C(n,m)-C(n-b[i],m)+p)%p;
        ans=(ans+num*a[i].val%p*a[i].val%p)%p;
    }
    for(int i=1;i<=n;i++){ // 2*ai*aj
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            int num=(C(n,m)-C(n-b[i],m)-C(n-b[j],m)+C(n-b[i]-b[j]+c[i][j],m)+4*p)%p;
            ans=(ans+a[i].val*a[j].val%p*num%p)%p;
        }
    }
    ```
* **代码解读**：
  - 平方项计算：`C(n,m)-C(n-b[i],m)`表示至少选一个覆盖i的蛇的方案数，乘以$B_i^2$。
  - 乘积项计算：通过容斥计算同时包含i和j的方案数（`C(n,m)-C(n-b[i],m)-C(n-b[j],m)+C(n-b[i]-b[j]+c[i][j],m)`），其中`c[i][j]`是i和j的共同覆盖区域大小。
* 💡 **学习笔记**：容斥的关键是正确计算“不满足条件的方案数”，并通过加减抵消重复部分。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解覆盖区域计算和容斥过程，我们设计了一个“像素蛇灾”动画，采用8位复古风格，让你“看”到算法如何工作！
</visualization_intro>

  * **动画演示主题**：`像素蛇灾：覆盖区域与组合数的冒险`

  * **核心演示内容**：展示二维网格中蛇的位置，动态计算每个蛇的覆盖区域（切比雪夫距离≤R的正方形），以及两个蛇的共同覆盖区域。动画中，选择M个蛇时，会显示这些蛇的覆盖区域叠加后的总覆盖蛇数，并计算对应的得分贡献。

  * **设计思路简述**：8位像素风格（如FC游戏）降低学习门槛，颜色标记（红色蛇、蓝色覆盖区域）增强视觉区分。音效（“叮”声标记覆盖区域计算完成，“胜利”音效标记得分累加）强化操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕显示1000x1000的像素网格（简化为20x20，方便展示），红色方块表示蛇的位置。
          * 控制面板包含“单步执行”、“自动播放”按钮和速度滑块（1-10级）。
          * 播放8位风格背景音乐（如《超级马里奥》的轻快旋律）。

    2.  **覆盖区域计算**：
          * 点击“开始”，选中蛇i，其覆盖区域（蓝色透明方块，边长2R+1）从中心扩散，伴随“刷”的音效。
          * 二维前缀和计算结果（如“覆盖5条蛇”）显示在右侧信息栏。

    3.  **组合数容斥演示**：
          * 计算“包含蛇i的方案数”时，总方案数（C(n,m)）和不包含的方案数（C(n-cover_i,m)）用动态数字显示，差值（包含的方案数）用绿色高亮。
          * 计算“同时包含i和j的方案数”时，共同覆盖区域（紫色方块）与各自覆盖区域（蓝色、绿色）叠加，容斥过程用箭头标注（总方案数 - 不包含i的 - 不包含j的 + 不包含i和j的）。

    4.  **得分累加**：
          * 每个贡献项（如$B_i^2 \times cnt$或$2B_iB_j \times cnt$）计算完成后，得分数字从0开始增长，伴随“滴”的音效。
          * 最终总得分用金色字体高亮，播放“胜利”音效（如《星之卡比》的胜利旋律）。

    5.  **交互控制**：
          * 单步执行：点击“下一步”，逐步展示覆盖区域计算、组合数容斥、得分累加。
          * 自动播放：选择速度后，算法自动演示完整过程，适合观察整体流程。
          * 重置：点击“重置”，清空当前状态，重新开始。

  * **旁白提示**：
      * （覆盖区域计算时）“看！蓝色区域是蛇i的攻击范围，里面有5条蛇，包括i自己哦～”
      * （容斥计算时）“总共有C(4,2)=6种选法，其中不包含i的有C(4-5,2)=0种，所以包含i的方案数是6-0=6种！”
      * （得分累加时）“现在，蛇i的B_i²贡献了10²×6=600分，加到总得分里～”

<visualization_conclusion>
通过这个动画，你不仅能看到覆盖区域如何计算，还能直观理解容斥原理和组合数的应用，就像在玩一款“数学冒险游戏”！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是“组合数学+二维前缀和”，这类方法还适用于以下场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 统计网格中矩形区域的元素数（如统计某区域内的资源点）。
      - 计算“至少满足一个条件”的方案数（如抽奖活动中至少中一个奖的概率）。
      - 处理“和的平方”类问题（如多个变量和的平方的期望）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1378 油滴扩展**
          * 🗣️ **推荐理由**：需要计算圆的覆盖区域，与本题的切比雪夫距离覆盖类似，可练习几何区域统计。
    2.  **洛谷 P1443 马的遍历**
          * 🗣️ **推荐理由**：BFS遍历网格，结合二维前缀和统计可达区域，锻炼网格处理能力。
    3.  **洛谷 P3397 地毯**
          * 🗣️ **推荐理由**：二维差分与前缀和的典型应用，巩固二维区域修改与查询的技巧。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
题解中作者提到的调试经验对我们很有启发：
</insights_intro>

> **参考经验 (来自作者Fairicle)**：“在计算覆盖区域时，一开始没考虑坐标越界（如x=0或x=1001），导致前缀和查询出错。后来通过添加`max(1,x)`和`min(1000,x)`解决了问题。”

**点评**：边界条件是编程中最容易出错的地方之一。在处理网格问题时，一定要用`max`和`min`限制坐标范围，避免数组越界。调试时，可以打印中间结果（如覆盖区域的蛇数），快速定位错误。

-----

<conclusion>
本次关于“Danger of Mad Snakes”的分析就到这里。希望你通过这份指南，掌握了组合数学、二维前缀和和容斥原理的应用。记住，多动手调试、多思考问题分解，编程能力会越来越强！下次见～ 💪
</conclusion>

---
处理用时：168.41秒