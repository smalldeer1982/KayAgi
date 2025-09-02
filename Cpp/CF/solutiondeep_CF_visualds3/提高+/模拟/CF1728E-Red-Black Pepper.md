# 题目信息

# Red-Black Pepper

## 题目描述

Monocarp is going to host a party for his friends. He prepared $ n $ dishes and is about to serve them. First, he has to add some powdered pepper to each of them — otherwise, the dishes will be pretty tasteless.

The $ i $ -th dish has two values $ a_i $ and $ b_i $ — its tastiness with red pepper added or black pepper added, respectively. Monocarp won't add both peppers to any dish, won't add any pepper multiple times, and won't leave any dish without the pepper added.

Before adding the pepper, Monocarp should first purchase the said pepper in some shop. There are $ m $ shops in his local area. The $ j $ -th of them has packages of red pepper sufficient for $ x_j $ servings and packages of black pepper sufficient for $ y_j $ servings.

Monocarp goes to exactly one shop, purchases multiple (possibly, zero) packages of each pepper in such a way that each dish will get the pepper added once, and no pepper is left. More formally, if he purchases $ x $ red pepper packages and $ y $ black pepper packages, then $ x $ and $ y $ should be non-negative and $ x \cdot x_j + y \cdot y_j $ should be equal to $ n $ .

For each shop, determine the maximum total tastiness of the dishes after Monocarp buys pepper packages only in this shop and adds the pepper to the dishes. If it's impossible to purchase the packages in the said way, print -1.

## 说明/提示

Consider the first example.

In the first shop, Monocarp can only buy $ 0 $ red pepper packages and $ 1 $ black pepper package. Black pepper added to all dishes will sum up to $ 10 + 50 + 2 = 62 $ .

In the second shop, Monocarp can buy any number of red and black pepper packages: $ 0 $ and $ 3 $ , $ 1 $ and $ 2 $ , $ 2 $ and $ 1 $ or $ 3 $ and $ 0 $ . The optimal choice turns out to be either $ 1 $ and $ 2 $ or $ 2 $ and $ 1 $ . Monocarp can add black pepper to the first dish, red pepper to the second dish and any pepper to the third dish, the total is $ 10 + 100 + 2 = 112 $ .

In the third shop, Monocarp can only buy $ 1 $ red pepper package and $ 0 $ black pepper packages. Red pepper added to all dishes will sum up to $ 5 + 100 + 2 = 107 $ .

In the fourth shop, Monocarp can only buy an even total number of packages. Since $ n $ is odd, it's impossible to get exactly $ n $ packages. Thus, the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
5 10
100 50
2 2
4
2 3
1 1
3 2
2 2```

### 输出

```
62
112
107
-1```

## 样例 #2

### 输入

```
10
3 1
2 3
1 1
2 1
6 3
1 4
4 3
1 3
5 3
5 4
10
8 10
9 3
1 4
2 5
8 3
3 5
1 6
7 2
6 7
3 1```

### 输出

```
26
-1
36
30
-1
26
34
26
-1
36```

# AI分析结果

---
# 💡 Kay的C++算法解析：Red-Black Pepper 深入学习指南 💡

<introduction>
今天我们来分析“Red-Black Pepper”这道题。它结合了贪心策略与数论中的扩展欧几里得算法，是一道非常有挑战性的题目。本指南将带大家拆解核心思路，理解关键步骤，并通过可视化动画直观感受算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法 + 扩展欧几里得算法（exgcd）

🗣️ **初步分析**：
解决这道题的关键在于两步：首先通过贪心预处理出“选k个红辣椒时的最大美味度”，然后用扩展欧几里得算法判断每个商店是否能满足“总份数等于n”的条件，并在可行解中找到最优的k值。

- **贪心算法**：可以理解为“优先选择收益最大的操作”。比如，我们先假设所有菜都加黑辣椒（总美味度为所有b_i之和），然后每次将一个黑辣椒换成红辣椒时，选择能带来最大额外收益（a_i - b_i最大）的菜。将这些收益排序后，前缀和就是选k个红辣椒时的最大美味度。
- **扩展欧几里得算法（exgcd）**：用于求解形如x_j * p + y_j * q = n的线性方程是否有非负整数解。若有解，需找到所有可能的(p, q)组合，并从中选出对应的k = x_j * p（红辣椒份数），使贪心前缀和最大。

**核心难点与解决方案**：
- 难点1：如何高效预处理“选k个红辣椒的最大美味度”？  
  解决方案：将每道菜的a_i - b_i排序，取前k大的数求和（贪心）。
- 难点2：如何快速判断商店是否有解，并找到最优k值？  
  解决方案：用exgcd求解方程，结合通解公式找到所有可能的k值，再在这些k中找最大前缀和（利用前缀和的单峰性质优化）。

**可视化设计思路**：  
用8位像素风格动画演示贪心排序过程（如不同颜色的像素块代表不同的a_i - b_i值，按从大到小排列），以及exgcd求解时的方程变形（用箭头标注解的扩展路径）。关键步骤（如排序完成、找到可行解）伴随“叮”的像素音效，目标达成时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰度、代码规范性和算法有效性评估，以下3篇题解（评分≥4星）值得重点参考：
</eval_intro>

**题解一：作者_•́へ•́╬_ (赞：10)**
* **点评**：此题解思路清晰，将问题拆解为“贪心预处理”和“exgcd求解”两部分，代码高效且注释到位。贪心部分通过排序a_i - b_i并计算前缀和，直接得到选k个红辣椒的最大美味度；exgcd部分利用通解公式快速枚举可行的k值，结合根号分治优化时间复杂度。代码中使用`#define int long long`避免溢出，边界处理严谨（如负数解的调整），是竞赛代码的典范。

**题解二：作者STUDENT00 (赞：4)**
* **点评**：此题解亮点在于用整数三分法简化了最优k值的查找。由于贪心前缀和是单峰函数（先增后减），通过三分法可快速定位峰值附近的k值，减少枚举次数。代码结构清晰，关键变量（如`dx`、`dy`）命名明确，适合理解如何将数论与贪心结合。

**题解三：作者Deft_t (赞：3)**
* **点评**：此题解详细推导了exgcd的通解范围，并通过分类讨论（k在峰值左边、右边或跨过峰值）找到最优解。代码中对t的取值范围计算（`l`和`r`）逻辑严谨，适合学习如何处理线性方程的非负整数解。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点主要集中在预处理和数论求解两部分，以下是关键步骤和应对策略：
</difficulty_intro>

1.  **关键点1：贪心预处理的前缀和计算**  
    * **分析**：要计算选k个红辣椒的最大美味度，需先将所有菜的a_i - b_i从大到小排序。因为每次替换黑辣椒为红辣椒时，选择收益最大的菜（a_i - b_i最大），所以前缀和即为前k大的a_i - b_i之和。例如，排序后数组为[5,3,2,-1]，则k=2时的和为5+3=8。  
    * 💡 **学习笔记**：贪心的核心是“局部最优导致全局最优”，这里通过排序确保每一步替换都是当前最优。

2.  **关键点2：用exgcd求解线性方程的非负解**  
    * **分析**：方程x_j * p + y_j * q = n是否有解由裴蜀定理判断（n需是x_j和y_j的最大公约数的倍数）。若有解，需通过exgcd找到初始解(p0, q0)，再利用通解公式p = p0 + (y_j/g) * t，q = q0 - (x_j/g) * t（g为gcd(x_j,y_j)），调整t使p和q非负。  
    * 💡 **学习笔记**：exgcd不仅能判断解的存在性，还能通过通解公式枚举所有可能的解。

3.  **关键点3：在可行解中找到最优的k值**  
    * **分析**：k = x_j * p（红辣椒份数），需要在所有可行的k中找到对应的前缀和最大值。由于前缀和是单峰函数（先增后减），最优k通常在峰值附近，可通过枚举t的小范围或三分法快速定位。  
    * 💡 **学习笔记**：单峰函数的性质允许我们通过局部枚举或三分法替代全量枚举，大幅降低时间复杂度。

### ✨ 解题技巧总结
- **预处理优先**：先通过贪心预处理出所有可能的k值对应的最大美味度，后续查询只需查表。
- **数论与贪心结合**：用exgcd处理方程的解，再用贪心的前缀和数组快速求值。
- **单峰函数优化**：利用前缀和的单峰性质，通过三分法或局部枚举减少计算量。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合多个优质题解的通用核心实现，结合了贪心预处理和exgcd求解的关键逻辑。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了_•́へ•́╬_和STUDENT00的题解思路，包含预处理和查询处理的完整逻辑。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    #define int long long
    using namespace std;

    const int MAXN = 3e5 + 5;
    int n, m;
    int a[MAXN], b[MAXN], diff[MAXN], sum_b;
    int prefix[MAXN]; // prefix[k]表示选k个红辣椒的最大美味度

    // 扩展欧几里得算法求解ax + by = gcd(a,b)
    int exgcd(int a, int b, int& x, int& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        int g = exgcd(b, a % b, x, y);
        int tmp = x - (a / b) * y;
        x = y; y = tmp;
        return g;
    }

    signed main() {
        // 输入并预处理贪心前缀和
        cin >> n;
        sum_b = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i];
            sum_b += b[i];
            diff[i] = a[i] - b[i]; // 红辣椒比黑辣椒多的美味度
        }
        sort(diff, diff + n, greater<int>()); // 降序排序
        prefix[0] = sum_b;
        for (int k = 1; k <= n; ++k) {
            prefix[k] = prefix[k - 1] + diff[k - 1];
        }

        // 处理每个商店查询
        cin >> m;
        while (m--) {
            int x, y; // 当前商店的红、黑辣椒每包份数
            cin >> x >> y;
            int p0, q0;
            int g = exgcd(x, y, p0, q0);
            if (n % g != 0) { // 无解
                cout << -1 << "\n";
                continue;
            }
            // 调整初始解为通解形式
            p0 *= n / g; q0 *= n / g;
            int dx = y / g, dy = x / g; // 通解的步长

            // 找到p的最小非负解
            int t = (p0 % dx + dx) % dx;
            p0 -= t * dx; q0 += t * dy;
            if (p0 < 0) { // 若仍为负，加一个步长
                p0 += dx; q0 -= dy;
            }

            // 检查q是否非负，且x*p + y*q = n
            if (q0 < 0 || x * p0 + y * q0 != n) {
                cout << -1 << "\n";
                continue;
            }

            // 枚举可能的p值（k = x*p），找到最大prefix[k]
            int max_val = -1;
            for (int p = p0; x * p <= n; p += dx) {
                int k = x * p;
                if (k < 0 || k > n) continue;
                max_val = max(max_val, prefix[k]);
            }
            cout << max_val << "\n";
        }
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先预处理所有菜的a_i - b_i并排序，计算前缀和数组`prefix`，其中`prefix[k]`表示选k个红辣椒的最大美味度。对于每个商店查询，用exgcd判断是否存在非负整数解(p, q)，若存在则枚举所有可能的p值，计算对应的k = x*p，取`prefix[k]`的最大值。

---

<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段：
</code_intro_selected>

**题解一：作者_•́へ•́╬_**
* **亮点**：使用根号分治优化枚举，当通解步长较大时直接暴力枚举，步长较小时记忆化预处理，时间复杂度更优。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=n&&!(i>>B);++i) 
        for(int j=0;j<=n;++j) 
            max(c[i][j%i],b[j]);
    // ...
    if((v>>B)||v>n) 
        for(;x<=n;max(maxn,b[x]),x+=v);
    else 
        maxn=c[v][x];
    ```
* **代码解读**：  
  `c[i][j]`是记忆化数组，存储步长为i时余数j对应的最大前缀和。当步长v较小时（`v<=2^B`），直接查表；步长较大时，暴力枚举x的所有可能值。这种优化避免了重复计算，提升了效率。  
* 💡 **学习笔记**：根号分治通过分情况处理不同规模的输入，是竞赛中常用的优化技巧。

**题解二：作者STUDENT00**
* **亮点**：利用整数三分法快速定位单峰函数的峰值，减少枚举次数。
* **核心代码片段**：
    ```cpp
    l=0,r=(mx-mn)/dy;
    while(r-l>2){
        int mid1=l+(r-l)/3,mid2=r-(r-l)/3;
        if(c[f(mid1)]<=c[f(mid2)]) l=mid1;
        else r=mid2;
    }
    int ans=-INF;
    for(int i=l;i<=r;i++) ans=max(ans,c[f(i)]);
    ```
* **代码解读**：  
  由于前缀和数组是单峰的，三分法通过比较中间两个点的函数值，缩小搜索范围，最终在小范围内枚举找到最大值。这种方法的时间复杂度为O(log n)，比全量枚举更高效。  
* 💡 **学习笔记**：单峰函数的极值问题可通过三分法高效解决，适用于无法直接求导的离散场景。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解贪心预处理和exgcd求解的过程，我们设计了一个“像素辣椒探险”主题的8位风格动画。
</visualization_intro>

  * **动画演示主题**：像素辣椒探险——贪心排序与方程求解  
  * **核心演示内容**：  
    1. **贪心排序**：用不同颜色的像素块代表每道菜的a_i - b_i值（红色块表示大值，蓝色块表示小值），通过“交换动画”将它们从大到小排列。  
    2. **前缀和计算**：排列完成后，依次累加红色块的值，生成“美味度条”（绿色进度条，高度表示当前k的前缀和）。  
    3. **exgcd求解**：用“方程精灵”演示线性方程x_j*p + y_j*q = n的变形过程，通过箭头标注通解的扩展路径（p和q的变化），并高亮非负解的范围。  

  * **设计思路简述**：  
    8位像素风格（如FC游戏画面）营造轻松氛围，颜色标记（红/蓝块、绿色进度条）帮助区分关键数据。音效（交换时的“咔嗒”声、找到解时的“叮”声）强化操作记忆，游戏化的“关卡”设计（每完成一个商店查询即过一关）增加成就感。

  * **动画帧步骤与交互关键点**：  
    1. **初始化场景**：  
       - 左侧显示n个彩色像素块（代表a_i - b_i），右侧显示“美味度条”和“方程面板”。  
       - 控制面板包含“开始排序”“单步执行”“自动播放”按钮。  
    2. **贪心排序动画**：  
       - 点击“开始排序”后，像素块两两比较，较大的块向右移动（类似冒泡排序），伴随“咔嗒”音效。  
       - 排序完成后，顶部显示“排序完成！”文字，背景播放短旋律。  
    3. **前缀和计算动画**：  
       - 从k=0开始，依次累加红色块的值，绿色进度条逐渐升高，数值实时更新（如“k=1，和=50”）。  
       - 峰值位置（k=mx）用金色边框高亮，提示“这里是最大美味度！”。  
    4. **exgcd求解动画**：  
       - 输入商店的x和y后，“方程精灵”弹出，显示方程x*p + y*q = n。  
       - 用箭头演示exgcd求解过程（如“初始解p0=2, q0=3”），然后通过通解公式扩展（p=2+3t, q=3-2t）。  
       - 非负解用黄色边框标记，无效解（p<0或q<0）用灰色覆盖。  
    5. **最优解查找**：  
       - 在可行的p值中，对应的k=x*p用紫色箭头指向“美味度条”，找到最大值时，进度条闪烁金色，播放“胜利”音效。  

  * **旁白提示**：  
    - 排序时：“看！我们在把红辣椒比黑辣椒多的美味度从大到小排，这样选前k个就能得到最大收益～”  
    - 求解方程时：“现在要找到p和q的非负整数解，使得总份数正好是n哦！”  
    - 找到最优解时：“看！这里的k值对应的美味度最大，这就是答案～”

<visualization_conclusion>
通过这个动画，我们可以直观看到贪心排序如何为后续查询提供支持，以及exgcd如何一步步找到可行解。像素风格和游戏化元素让学习过程更有趣！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是贪心预处理与数论方程求解的结合，这类思路还可用于以下场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - 资源分配问题：如用两种包装的资源满足总量需求，最大化收益（类似本题的红/黑辣椒）。  
    - 线性方程最优解：如用两种面值的硬币凑出总金额，求最少硬币数（需结合动态规划或贪心）。  
    - 单峰函数优化：如寻找数组中的峰值元素（可通过二分或三分法）。  

  * **练习推荐 (洛谷)**：  
    1.  **洛谷 P1083 借教室**  
        * 🗣️ **推荐理由**：涉及线性方程的区间修改与贪心判断，锻炼对问题的转化能力。  
    2.  **洛谷 P5656 【模板】扩展欧几里得算法**  
        * 🗣️ **推荐理由**：直接练习exgcd的应用，巩固数论基础。  
    3.  **洛谷 P1282 多米诺骨牌**  
        * 🗣️ **推荐理由**：结合贪心与动态规划，需预处理可能的状态，与本题的预处理思想类似。  

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，例如：
</insights_intro>

> **参考经验 (来自作者_•́へ•́╬_)**：“一开始没考虑到负数解的调整，导致样例出错。后来通过打印中间变量（如p0和q0），发现需要对初始解进行模运算调整，确保p和q非负。”

**点评**：这位作者的经验提醒我们，在处理数论问题时，必须仔细检查解的非负性。打印中间变量是调试数论代码的有效手段，能快速定位解的范围错误。

---

<conclusion>
通过本次分析，我们掌握了“Red-Black Pepper”的核心解法：贪心预处理前缀和 + exgcd求解方程。希望大家在练习中多思考如何将贪心与数论结合，提升综合解题能力！下次见～💪
</conclusion>

---
处理用时：149.25秒