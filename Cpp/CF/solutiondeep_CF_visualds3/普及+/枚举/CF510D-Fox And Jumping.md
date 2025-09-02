# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Fox And Jumping 深入学习指南 💡

<introduction>
今天我们来一起分析“Fox And Jumping”这道C++编程题。题目要求我们找到一组卡片，使得它们的跳跃长度的最大公约数（gcd）为1，从而能跳到纸带上的任意位置，并求最小代价。本指南将帮助大家梳理核心思路，解析关键算法，并通过可视化方案直观理解过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（状态压缩/Map优化）与数论结合

🗣️ **初步分析**：
解决这道题的关键在于理解“能跳到任意位置”的条件——所选卡片长度的gcd必须为1（由裴蜀定理可知）。我们需要找到这样的卡片集合，并使总代价最小。  

核心算法可归类为**动态规划优化**，具体有两种主流思路：  
- **状态压缩DP**：利用数的质因数分解，将gcd的质因数集合状态压缩（因10^9内的数最多有9个质因数，故状态数为2^9=512），通过状压DP记录不同质因数集合的最小代价。  
- **Map优化DP**：直接以gcd值为状态，用Map动态记录各gcd值的最小代价，逐步更新。  

核心难点在于处理大范围的gcd值（传统数组无法存储），需通过状态压缩或Map优化来高效管理状态。例如，状态压缩DP通过质因数分解将大问题转化为小状态空间；Map优化则利用动态哈希表存储有效状态，避免无效计算。  

可视化设计中，我们将用8位像素风展示状态转移过程：  
- 质因数集合用像素块表示（如每个质因数对应一个颜色块），状态压缩后的二进制位用亮/灭灯显示。  
- Map优化的DP则用动态气泡显示当前gcd值及其最小代价，每次转移时气泡合并（计算新gcd）并更新代价，伴随“叮”的音效提示状态更新。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，筛选出以下3篇优质题解：
</eval_intro>

**题解一：ZYF_B的状态压缩DP（来源：用户ZYF_B）**
* **点评**：此题解巧妙利用质因数分解和状态压缩，将问题转化为小状态空间的DP。思路清晰（明确“质因数集合”的状态定义），代码规范（变量名如`g[i][k]`表示第i个数的第k个质因数，`f[s]`表示质因数集合s的最小代价），时间复杂度O(n²2⁹)可接受。亮点在于通过质因数分解将大问题降维，避免了Map的低效访问。

**题解二：Kohakuwu的Map优化DP（来源：用户Kohakuwu）**
* **点评**：此题解用Map动态维护各gcd值的最小代价，代码简洁（仅20行核心逻辑）。思路直观（直接以gcd为状态，逐步合并新卡片的gcd），适合理解基础DP转移。亮点在于利用Map自动过滤无效状态，降低了实现复杂度。

**题解三：fanfansann的Dijkstra最短路（来源：用户fanfansann）**
* **点评**：此题解将问题建模为最短路，gcd值为节点，代价为边权，用Dijkstra算法求到节点1的最短路径。思路新颖（将DP转移视为最短路松弛），代码结构清晰（优先队列优化）。亮点在于将动态规划转化为图论问题，拓宽了解题思路。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题的关键在于处理大范围的gcd状态，以下是核心难点及应对策略：
</difficulty_intro>

1.  **关键点1：如何将问题转化为gcd为1的最小代价子集？**
    * **分析**：根据裴蜀定理，能跳到任意位置的充要条件是所选卡片长度的gcd为1。因此，问题等价于寻找gcd为1的最小代价子集。  
    * 💡 **学习笔记**：抓住问题本质（gcd=1）是解题的第一步，需熟练应用数论中的裴蜀定理。

2.  **关键点2：如何高效处理大范围的gcd状态？**
    * **分析**：直接用数组存储所有可能的gcd值不可行（因l_i可达1e9）。解决方案有两种：  
      - 状态压缩DP：将gcd的质因数分解，用二进制位表示质因数集合（最多9位），状态数仅512。  
      - Map优化DP：用Map动态记录已出现的gcd值及其最小代价，避免存储无效状态。  
    * 💡 **学习笔记**：当状态范围大时，需通过数学性质（如质因数分解）或动态数据结构（如Map）压缩状态空间。

3.  **关键点3：如何设计状态转移？**
    * **分析**：状态转移需考虑新增卡片后的gcd变化。例如，当前状态为gcd=g，新增卡片长度为l_i，则新状态为gcd(g, l_i)，代价为原代价+c_i。需取所有可能转移中的最小代价。  
    * 💡 **学习笔记**：状态转移的核心是“合并新卡片后的gcd计算”，需确保每次转移都保留最小代价。

### ✨ 解题技巧总结
- **质因数分解**：对卡片长度分解质因数，可将大问题转化为小状态空间（状压DP关键）。  
- **动态状态管理**：用Map或状态压缩避免存储无效状态，提升效率。  
- **最短路建模**：将gcd值视为节点，代价视为边权，可用Dijkstra算法求解最小代价。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，结合了状态压缩DP的高效性和Map优化的简洁性：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了状态压缩DP的思路，通过质因数分解和状态压缩高效求解最小代价。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int INF = 1e9;
    int a[305], cost[305];
    int primes[305][10], cnt[305]; // primes[i]存储第i个数的质因数，cnt[i]为质因数个数
    int dp[1 << 9]; // 最多9个质因数，状态数为2^9=512

    int main() {
        int n; cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> cost[i];

        // 分解质因数
        for (int i = 1; i <= n; ++i) {
            int x = a[i];
            for (int j = 2; j * j <= x; ++j) {
                if (x % j == 0) {
                    primes[i][++cnt[i]] = j;
                    while (x % j == 0) x /= j;
                }
            }
            if (x > 1) primes[i][++cnt[i]] = x;
        }

        int ans = INF;
        for (int i = 1; i <= n; ++i) { // 枚举必选第i个数
            memset(dp, 0x3f, sizeof(dp));
            int state_num = 1 << cnt[i];
            dp[state_num - 1] = cost[i]; // 初始状态：仅选第i个数，质因数全包含

            for (int j = 1; j <= n; ++j) { // 枚举其他数
                if (i == j) continue;
                int s = 0;
                for (int k = 1; k <= cnt[i]; ++k) { // 计算j的质因数在i的质因数中的位置
                    for (int x = 1; x <= cnt[j]; ++x) {
                        if (primes[i][k] == primes[j][x]) {
                            s |= (1 << (k - 1)); // 标记共有质因数
                            break;
                        }
                    }
                }
                for (int k = 0; k < state_num; ++k) // 状态转移
                    dp[k & s] = min(dp[k & s], dp[k] + cost[j]);
            }
            ans = min(ans, dp[0]); // 全0状态表示质因数被完全覆盖（gcd=1）
        }

        cout << (ans == INF ? -1 : ans) << endl;
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先分解每个卡片长度的质因数，然后枚举必选的卡片i，初始化状态为i的质因数集合。通过状态转移（合并其他卡片的质因数），最终找到覆盖所有质因数（即gcd=1）的最小代价。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：ZYF_B的状态压缩DP（来源：用户ZYF_B）**
* **亮点**：通过质因数分解和状态压缩，将状态数限制在512，时间复杂度可控。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= n; ++i) {
        memset(f, 0x3f, sizeof(f));
        int M = 1 << cnt[i];
        f[M - 1] = cost[i];
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            int s = 0;
            for (int k = 1; k <= cnt[i]; ++k) {
                for (int x = 1; x <= cnt[j]; ++x) {
                    if (g[i][k] == g[j][x]) {
                        s |= (1 << (k - 1));
                        break;
                    }
                }
            }
            for (int k = 0; k < M; ++k)
                f[k & s] = min(f[k & s], f[k] + cost[j]);
        } 
        ans = min(ans, f[0]);
    }
    ```
* **代码解读**：  
  外层循环枚举必选卡片i，初始化状态为i的质因数全选（M-1）。内层循环枚举其他卡片j，计算j的质因数与i的交集（s），然后通过位运算k&s合并状态，更新最小代价。最终f[0]表示质因数全被覆盖（gcd=1）的最小代价。  
* 💡 **学习笔记**：状态压缩的关键是将质因数集合映射到二进制位，通过位运算高效合并状态。

**题解二：Kohakuwu的Map优化DP（来源：用户Kohakuwu）**
* **亮点**：用Map动态维护各gcd值的最小代价，代码简洁。
* **核心代码片段**：
    ```cpp
    for(int i=1; i<=n; i++) {
        for(pair<int,int> x:mp) {
            int num=__gcd(a[i],x.first),val=x.second+b[i];
            if(mp[num]==0) mp[num]=val; else mp[num]=min(mp[num],val);
        }
        if(mp[a[i]]==0) mp[a[i]]=b[i]; else mp[a[i]]=min(mp[a[i]],b[i]);
    }
    ```
* **代码解读**：  
  遍历每张卡片i，对Map中的每个现有gcd值x.first，计算新gcd（num），并更新其最小代价（val）。同时单独处理仅选i的情况（mp[a[i]]）。最终Map[1]即为答案。  
* 💡 **学习笔记**：Map自动过滤无效状态（未出现的gcd值），适合处理大范围状态。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为直观理解状态压缩DP的转移过程，我们设计一个“质因数探险”像素动画，以8位复古风格展示状态变化。
</visualization_intro>

  * **动画演示主题**：`质因数探险——寻找gcd=1的最小代价`

  * **核心演示内容**：  
    展示卡片的质因数分解、状态压缩后的二进制位变化，以及状态转移时的代价更新。例如，初始状态为必选卡片i的质因数全选（二进制位全1），每次加入新卡片j时，计算与i的共有质因数（二进制位交集），并更新对应状态的最小代价。

  * **设计思路简述**：  
    8位像素风营造轻松氛围，质因数用不同颜色的像素块表示（如2为红色，3为蓝色）。状态压缩的二进制位用8x8的LED灯板显示（亮灯表示包含该质因数）。每次状态转移时，LED灯板的灯按位与操作变化，伴随“叮”的音效；代价更新时，数值用像素数字动态跳动。

  * **动画帧步骤与交互关键点**：

    1.  **初始化场景**：  
        - 屏幕左侧显示卡片列表（像素图标+长度/代价），右侧为8x8 LED灯板（表示状态）和代价显示框。  
        - 顶部控制面板：单步/自动播放按钮、速度滑块（1-5倍速）。  

    2.  **分解质因数**：  
        - 点击卡片i，其长度分解为质因数（如100→2²×5²，显示红色2和蓝色5的像素块）。  
        - LED灯板对应位（假设2是第0位，5是第1位）亮起（0b11），代价框显示c[i]。  

    3.  **状态转移**：  
        - 选择卡片j，分解其质因数（如99→3²×11，无共有质因数）。  
        - LED灯板计算位与操作（0b11 & 0b00=0b00），灯板全灭，代价框更新为c[i]+c[j]（伴随“叮”音效）。  

    4.  **目标达成**：  
        - 当LED灯板全灭（状态0，gcd=1），播放胜利音效（如FC游戏通关音），代价框高亮显示最小代价。  

    5.  **交互控制**：  
        - 单步播放：每点击一次，执行一次状态转移，显示中间过程。  
        - 自动播放：按设定速度连续演示，学习者可观察状态变化规律。  

  * **旁白提示**：  
    - “看！卡片i的质因数是2和5，对应的LED灯第0、1位亮啦～”  
    - “现在加入卡片j，它的质因数是3和11，和i没有共有质因数，所以新状态的LED灯全灭（gcd=1）！”  

<visualization_conclusion>
通过这个像素动画，我们能直观看到质因数如何影响状态，以及状态转移时的代价变化，轻松理解状态压缩DP的核心逻辑。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，可尝试以下拓展练习，巩固gcd相关的动态规划/最短路技巧：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    本题的核心是“求子集的gcd=1的最小代价”，类似的问题包括：  
    - 求子集的lcm=K的最小代价（需处理最小公倍数）。  
    - 求子集的异或和为0的最小代价（状态为异或值）。  
    - 求子集的和为S的最小代价（经典背包问题）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1072 [HNOI2007] 覆盖问题**  
        * 🗣️ **推荐理由**：需计算多个区间的gcd，巩固gcd的性质应用。  
    2.  **洛谷 P2341 [HAOI2006] 受欢迎的牛**  
        * 🗣️ **推荐理由**：涉及图论与gcd的结合，拓展问题建模能力。  
    3.  **洛谷 P3951 [NOIP2017 提高组] 小凯的疑惑**  
        * 🗣️ **推荐理由**：经典gcd应用，理解互质数的性质。  

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，例如：
</insights_intro>

> **参考经验 (来自用户inexistent)**：“初始化时忘记设置f[0]=0，导致无法进入循环。后来通过打印中间状态发现问题。”  
> **点评**：初始化是动态规划的关键步骤，需确保初始状态正确（如本题中必选卡片i时，初始状态应为i的质因数全选）。调试时打印中间状态（如Map中的gcd值或状态压缩的二进制位）是定位错误的有效方法。

---

<conclusion>
本次关于“Fox And Jumping”的分析就到这里。通过理解gcd的性质、状态压缩/Map优化的DP，以及可视化演示，相信大家已掌握核心思路。记住，多动手调试、分析状态转移是提升算法能力的关键！下次见～💪
</conclusion>

---

---
处理用时：139.01秒