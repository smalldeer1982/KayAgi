# 题目信息

# Graph Cost

## 题目描述

You are given an initially empty undirected graph with $ n $ nodes, numbered from $ 1 $ to $ n $ (i. e. $ n $ nodes and $ 0 $ edges). You want to add $ m $ edges to the graph, so the graph won't contain any self-loop or multiple edges.

If an edge connecting two nodes $ u $ and $ v $ is added, its weight must be equal to the greatest common divisor of $ u $ and $ v $ , i. e. $ \gcd(u, v) $ .

In order to add edges to the graph, you can repeat the following process any number of times (possibly zero):

- choose an integer $ k \ge 1 $ ;
- add exactly $ k $ edges to the graph, each having a weight equal to $ k + 1 $ . Adding these $ k $ edges costs $ k + 1 $ in total.

 Note that you can't create self-loops or multiple edges. Also, if you can't add $ k $ edges of weight $ k + 1 $ , you can't choose such $ k $ .For example, if you can add $ 5 $ more edges to the graph of weight $ 6 $ , you may add them, and it will cost $ 6 $ for the whole pack of $ 5 $ edges. But if you can only add $ 4 $ edges of weight $ 6 $ to the graph, you can't perform this operation for $ k = 5 $ .

Given two integers $ n $ and $ m $ , find the minimum total cost to form a graph of $ n $ vertices and exactly $ m $ edges using the operation above. If such a graph can't be constructed, output $ -1 $ .

Note that the final graph may consist of several connected components.

## 说明/提示

In the first test case, we can add an edge between the vertices $ 2 $ and $ 4 $ with $ \gcd = 2 $ . This is the only possible way to add $ 1 $ edge that will cost $ 2 $ .

In the second test case, there is no way to add $ 10 $ edges, so the answer is $ -1 $ .

In the third test case, we can add the following edges:

- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 2 $ and $ 4 $ ( $ \gcd(2, 4) = 2 $ ). Cost: $ 2 $ ;
- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 4 $ and $ 6 $ ( $ \gcd(4, 6) = 2 $ ). Cost: $ 2 $ ;
- $ k = 2 $ : edges of weight $ 3 $ : $ (3, 6) $ and $ (3, 9) $ ( $ \gcd(3, 6) = \gcd(3, 9) = 3 $ ). Cost: $ 3 $ .

 As a result, we added $ 1 + 1 + 2 = 4 $ edges with total cost $ 2 + 2 + 3 = 7 $ , which is the minimal possible cost.

## 样例 #1

### 输入

```
4
4 1
6 10
9 4
10 11```

### 输出

```
2
-1
7
21```

# AI分析结果



---
# 💡 Kay的C++算法解析：Graph Cost 深入学习指南 💡

<introduction>
今天我们来一起分析“Graph Cost”这道题。这道题结合了数论与贪心策略，需要我们找到添加恰好m条边的最小代价。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法 + 数论（欧拉函数应用）

🗣️ **初步分析**：
解决“Graph Cost”的关键在于两点：一是用数论（欧拉函数）计算满足条件的边数，二是用贪心策略优先选择代价更低的操作。  
贪心算法的核心思想就像“先买贵的再买便宜的”——这里“贵”对应更大的k（因为k+1是单次操作的总代价，而k越大，每条边的平均代价越小）。例如，选k=2（代价3）时，每条边的平均代价是3/2=1.5，比k=1（代价2，平均2）更优。  

### 核心思路与难点：
- **计算可用边数**：对于每个k（对应边权为k+1），需要计算有多少对节点(u,v)满足gcd(u,v)=k+1。这可以通过欧拉函数转换问题：将u和v除以k+1，转化为求互质的数对个数（即欧拉函数前缀和）。
- **贪心选择**：从大到小枚举k，尽可能多选大的k（因为大k的平均代价更低），直到凑够m条边。

### 可视化设计思路：
我们将设计一个“像素边工厂”动画，用8位像素风格展示边权为k+1的边如何被“生产”。例如：
- 用不同颜色的像素块表示不同边权（如红色=2，绿色=3等）。
- 动态显示剩余需要的边数（m）和总代价（ans）。
- 每次选择一个k时，动画展示“生产”k条边（像素块滑动到图中），并伴随“叮”的音效；若无法选k，则显示灰色不可用。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选了以下优质题解（评分≥4星）：
</eval_intro>

**题解一：作者Inui_Sana（赞4）**
* **点评**：此题解思路清晰，直接点明“优先选大k”的贪心策略，并通过线性筛欧拉函数预处理前缀和，高效计算可用边数。代码中变量命名合理（如`sum`存前缀和），边界处理（如`m%=i`）严谨，是竞赛代码的典范。亮点在于将数论与贪心结合，时间复杂度O(n)，适合快速实现。

**题解二：作者MortisM（赞2）**
* **点评**：此题解补充了贪心策略的证明（大k更优），增强了思路的严谨性。代码虽然未完整展示，但提到“线性筛欧拉函数比官方题解更优”，强调了预处理的重要性，对理解算法原理有帮助。

**题解三：作者yingkeqian9217（赞0）**
* **点评**：此题解详细解释了欧拉函数的应用（将gcd问题转化为互质问题），代码中对phi数组的预处理（前缀和）逻辑清晰，适合新手理解。但需注意代码中phi数组的覆盖是否正确（如phi[1]的处理），这是值得学习的调试点。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题时，主要难点集中在以下三个方面：
</difficulty_intro>

1.  **关键点1**：如何计算边权为k+1的可用边数？
    * **分析**：边权为k+1的边要求gcd(u,v)=k+1。将u和v除以k+1，得到x=u/(k+1)，y=v/(k+1)，此时需gcd(x,y)=1。因此，可用边数等于1到n/(k+1)范围内互质的数对个数，这可以通过欧拉函数前缀和计算（因为φ(i)表示与i互质的数的个数，前缀和即所有互质对的总数）。
    * 💡 **学习笔记**：欧拉函数前缀和是处理互质对数的“万能钥匙”。

2.  **关键点2**：为什么贪心选择大k更优？
    * **分析**：单次操作选k条边，代价为k+1，每条边的平均代价是(k+1)/k。k越大，平均代价越小（如k=2时平均1.5，k=3时≈1.33）。因此，优先选大k能最小化总代价。
    * 💡 **学习笔记**：平均代价是贪心选择的核心依据。

3.  **关键点3**：如何高效预处理欧拉函数？
    * **分析**：使用线性筛（欧拉筛）预处理欧拉函数，时间复杂度O(n)。筛法过程中，若i是质数，φ(i)=i-1；若i被质数p整除，则φ(i*p)=φ(i)*p（否则φ(i*p)=φ(i)*(p-1)）。最后计算前缀和，得到互质对数。
    * 💡 **学习笔记**：线性筛是预处理数论函数的“标配工具”。

### ✨ 解题技巧总结
- **问题转化**：将gcd问题转化为互质问题（除以k+1），简化计算。
- **贪心顺序**：从大到小枚举k，优先选大k以降低平均代价。
- **预处理优化**：提前用线性筛计算欧拉函数及其前缀和，避免重复计算。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
首先，我们来看一个综合优质题解的通用核心实现，它结合了欧拉筛、前缀和与贪心策略。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Inui_Sana和yingkeqian9217的思路，通过线性筛预处理欧拉函数及其前缀和，再从大到小枚举k，贪心选择可用边数。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int MAXN = 2e6 + 10; // 预处理到2e6足够覆盖题目范围
    int phi[MAXN];
    long long sum_phi[MAXN]; // 欧拉函数前缀和
    bool is_prime[MAXN];
    int primes[MAXN], cnt;

    void preprocess() {
        fill(is_prime, is_prime + MAXN, true);
        is_prime[0] = is_prime[1] = false;
        phi[1] = 1;
        for (int i = 2; i < MAXN; ++i) {
            if (is_prime[i]) {
                primes[++cnt] = i;
                phi[i] = i - 1;
            }
            for (int j = 1; j <= cnt && i * primes[j] < MAXN; ++j) {
                is_prime[i * primes[j]] = false;
                if (i % primes[j] == 0) {
                    phi[i * primes[j]] = phi[i] * primes[j];
                    break;
                } else {
                    phi[i * primes[j]] = phi[i] * (primes[j] - 1);
                }
            }
        }
        // 计算前缀和（互质对数）
        sum_phi[1] = 0; // 1个数没有数对
        sum_phi[2] = 1; // (1,2)
        for (int i = 3; i < MAXN; ++i) {
            sum_phi[i] = sum_phi[i - 1] + phi[i];
        }
    }

    long long solve(int n, long long m) {
        long long ans = 0;
        for (int k = n - 1; k >= 1 && m > 0; --k) { // k对应边权k+1
            int w = k + 1; // 边权
            int max_x = n / w; // x的范围是1~max_x
            if (max_x < 2) continue; // 无法形成边对（至少需要两个数）
            long long available = sum_phi[max_x]; // 互质对数
            long long can_take = min(available, m) / k; // 最多选can_take次k条边
            long long take = min(can_take, m / k); // 实际选的次数
            ans += take * w;
            m -= take * k;
        }
        return m == 0 ? ans : -1;
    }

    int main() {
        preprocess();
        int T;
        scanf("%d", &T);
        while (T--) {
            int n; long long m;
            scanf("%d %lld", &n, &m);
            printf("%lld\n", solve(n, m));
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先通过`preprocess`函数线性筛预处理欧拉函数`phi`和前缀和`sum_phi`（表示1~i的互质对数）。`solve`函数从大到小枚举k，计算当前k对应的边权w=k+1，可用边数`available`（即sum_phi[n/w]），然后贪心选择最多的k条边，直到m条边凑满或无法凑满返回-1。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者Inui_Sana**
* **亮点**：线性筛与前缀和结合，代码简洁高效。
* **核心代码片段**：
    ```cpp
    void solve(){
        scanf("%d%lld",&n,&m);
        ll ans=0;
        for(int i=n-1;i&&m;i--){
            if(i>m)continue;
            ll x=sum[n/(i+1)]/i;
            if(i*x>=m)ans+=(ll)(i+1)*(m/i),m%=i;
            else ans+=(ll)(i+1)*x,m-=(ll)i*x;
        }
        if(m)puts("-1");
        else printf("%lld\n",ans);
    }
    ```
* **代码解读**：
    > 这段代码实现了贪心逻辑。`i`是k（对应边权i+1），从大到小枚举。`sum[n/(i+1)]`是互质对数（可用边数），`x`是能选多少次k条边。若`i*x`（总边数）≥m，则选m/i次，否则全选。最后处理剩余边数。
* 💡 **学习笔记**：贪心的核心是“能选大的就选大的”，通过`sum`快速计算可用边数。

**题解三：作者yingkeqian9217**
* **亮点**：详细解释了欧拉函数的应用，代码注释清晰。
* **核心代码片段**：
    ```cpp
    void solve(){
        int ans=0;
        scanf("%lld%lld",&n,&m);
        for(int i=n;i>=2;i--){//枚举k+1
            int num=min(phi[n/i],m)/(i-1);
            ans+=num*i;
            m-=num*(i-1);
        }
        if(m) ans=-1;
        printf("%lld\n",ans);
    }
    ```
* **代码解读**：
    > 这里`i`是边权w=k+1，所以k=i-1。`phi[n/i]`是互质对数（可用边数），`num`是能选多少次k=i-1条边。总代价累加`num*i`（i是边权），边数减少`num*(i-1)`。最后判断m是否为0。
* 💡 **学习笔记**：注意变量名的对应（i是边权，k=i-1），避免混淆。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解贪心选择大k的过程，我们设计一个“像素边工厂”动画，用8位复古风格展示边权选择与代价计算。
</visualization_intro>

  * **动画演示主题**：`像素边工厂：贪心选大k`

  * **核心演示内容**：展示如何从大k开始，逐步选择边权为k+1的边，直到凑满m条边，同时动态显示剩余边数和总代价。

  * **设计思路简述**：
    采用8位像素风（如FC游戏画面），用不同颜色的方块表示不同边权（红色=2，绿色=3，蓝色=4…）。通过动态滑动的“边条”和闪烁的提示，让学习者直观看到“选大k更优”的原因（平均代价更低）。

  * **动画帧步骤与交互关键点**：

    1.  **初始化场景**：
        - 左侧显示“边权工厂”，顶部有m的计数器（初始为输入值），右侧显示总代价（初始0）。
        - 底部是k的滑动条（从n-1到1），每个k对应一个像素按钮（如k=5的按钮是黄色）。

    2.  **贪心选择过程**：
        - 自动播放时，动画从最大的k开始（如k=10），检查该k是否可用：计算n/(k+1)，生成对应互质对数（用像素条长度表示）。
        - 若可用边数≥k，则按钮变亮，点击后“生产”k条边（像素方块从工厂滑出到图中），m减少k，代价增加k+1（伴随“叮”的音效）。
        - 若可用边数<k，按钮变灰，跳过该k。

    3.  **关键步骤高亮**：
        - 当前处理的k用闪烁的像素箭头标记。
        - 互质对数的计算过程（如n=9，k=2时，n/(k+1)=3，显示1~3的互质对：(1,2),(1,3),(2,3)）用小弹窗解释。
        - 剩余m和总代价实时更新，用大字体高亮。

    4.  **结束状态**：
        - 若m=0，播放“胜利”音效（如8位版《超级玛丽》通关音），总代价闪烁绿色。
        - 若m>0，显示红色“-1”，播放短促“失败”音效。

  * **旁白提示**：
    - “现在处理k=5，边权是6。我们需要检查是否能选5条边…”
    - “看，选k=5的话，每条边的平均代价是6/5=1.2，比k=4更划算！”
    - “如果剩余边数不够选k条，就跳过这个k，选更小的k。”

<visualization_conclusion>
通过这个动画，我们能直观看到贪心策略如何一步步选择最优的k，理解“大k更优”的核心逻辑，以及欧拉函数如何帮助计算可用边数。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，我们可以迁移贪心+数论的思路到以下场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 当问题需要“最小化总代价”且操作具有“规模效应”（大操作更优）时，贪心策略是首选。
    - 涉及gcd的计数问题，常通过除以公因数转化为互质问题，利用欧拉函数或莫比乌斯反演。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1890** - `gcd区间`
          * 🗣️ **推荐理由**：练习gcd的区间查询，巩固数论基础。
    2.  **洛谷 P2158** - `[SDOI2008]仪仗队`
          * 🗣️ **推荐理由**：经典欧拉函数应用题，与本题的“互质对数”计算类似。
    3.  **洛谷 P3455** - `[POI2007]ZAP-Queries`
          * 🗣️ **推荐理由**：莫比乌斯反演的应用，深入理解gcd计数问题的转化。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了调试经验，例如Inui_Sana指出“前缀和数组要开long long”，这对避免溢出非常重要。
</insights_intro>

> **参考经验 (来自Inui_Sana)**：“注意前缀和数组要开long long。”
>
> **点评**：在数论问题中，互质对数可能很大（如n=1e6时，sum_phi可能超过int范围）。使用long long能避免溢出错误，这是竞赛中常见的“防坑”技巧。

-----

<conclusion>
本次关于“Graph Cost”的C++解题分析就到这里。希望大家通过本指南掌握贪心+数论的解题思路，理解欧拉函数的应用，并能在类似问题中举一反三。编程的乐趣在于不断挑战，下次见！💪
</conclusion>

---
处理用时：130.17秒