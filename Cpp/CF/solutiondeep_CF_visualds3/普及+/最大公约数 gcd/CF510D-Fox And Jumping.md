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
今天我们来一起分析“Fox And Jumping”这道C++编程题。题目要求我们选择一些卡片，使得它们的跳跃长度的最大公约数（gcd）为1，从而能够跳到纸带上的任意位置，并求最小成本。本指南将帮助大家梳理思路，理解核心算法，并掌握解题技巧。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（DP）与数论结合（gcd应用）

🗣️ **初步分析**：
解决这道题的关键在于理解“能够跳到任意位置”的数学条件——所选卡片跳跃长度的最大公约数（gcd）必须为1（根据裴蜀定理）。我们需要找到总成本最小的卡片集合，使其gcd为1。

题解中主要有三种思路：
1. **状压DP**：利用质因数分解，将每个数的质因数集合压缩为状态，通过位运算转移（如ZYF_B的题解）。
2. **map优化DP**：用map动态维护当前所有可能的gcd值及其最小成本，逐步更新（如Kohakuwu、Gaode_Sean等题解）。
3. **Dijkstra最短路**：将gcd值视为图节点，选择卡片的过程视为边，用最短路算法求到gcd=1的最小成本（如fanfansann、dks0311的题解）。

**核心算法流程**（以map优化DP为例）：  
初始时，map中无状态。遍历每张卡片，对于当前卡片的长度l_i和成本c_i，遍历map中已有状态（gcd值g），计算新的gcd值new_g = gcd(g, l_i)，并更新map[new_g]为min(原值, 当前成本+ c_i)。最终map[1]即为答案。

**可视化设计思路**：  
采用8位像素风格，用不同颜色的像素块表示不同的gcd值（如红色代表gcd=1，蓝色代表其他值）。动画中，每选择一张卡片，当前所有gcd状态会“生长”出新的gcd值（通过像素块分裂/合并），同时显示成本的更新。关键步骤（如生成gcd=1）会伴随“叮”的音效和闪烁效果，帮助学习者直观看到状态转移过程。

---

## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰度、代码规范性、算法有效性等维度的评估，以下3篇题解评分≥4星，值得重点学习：
</eval_intro>

**题解一：ZYF_B（赞：37）**
* **点评**：此题解巧妙利用质因数分解和状压DP，将问题转化为质因数集合的覆盖问题。思路清晰，通过预处理每个数的质因数，用位掩码表示质因数集合，状态转移时仅需考虑质因数的交集，时间复杂度为O(n²2⁹)（因10⁹内的数最多有9个质因数），效率极高。代码中变量命名规范（如`g[i][k]`表示第i个数的第k个质因数），边界处理严谨（如处理x>1的质因数），是状压DP的典型应用。

**题解二：Kohakuwu（赞：21）**
* **点评**：此题解用map动态维护gcd状态，代码简洁易懂。通过遍历每张卡片和map中的已有状态，逐步更新最小成本。思路直接（“map能搞定的题为什么用复杂方法？”），适合理解动态规划的核心思想。代码中利用`__gcd`函数简化计算，边界处理（如初始化map[a[i]]）体现了对问题的深刻理解。

**题解三：fanfansann（赞：8）**
* **点评**：此题解将问题转化为最短路问题，用Dijkstra算法求解。将gcd值视为图节点，选择卡片的过程视为边（权重为c_i），目标是从gcd=0（初始状态）到gcd=1的最短路径。思路新颖，利用优先队列优化，时间复杂度可控。代码中使用`unordered_map`存储距离和访问状态，避免了大数组的空间问题，适合理解算法迁移的思想。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题时，主要存在以下核心难点，结合优质题解的思路，我们逐一分析：
</difficulty_intro>

1.  **关键点1：如何将问题转化为gcd=1的子集选择**  
    * **分析**：根据裴蜀定理，能跳到任意位置的充要条件是所选卡片的l_i的gcd为1。优质题解（如ZYF_B、Kohakuwu）均明确这一点，将问题转化为“选卡片使gcd=1且成本最小”。  
    * 💡 **学习笔记**：遇到“覆盖所有可能值”的问题时，常需利用数论中的裴蜀定理，转化为gcd条件。

2.  **关键点2：如何高效维护gcd状态（因l_i可能极大）**  
    * **分析**：直接用数组存储所有可能的gcd值不可行（l_i可达10⁹）。优质题解采用map（如Kohakuwu）或质因数状压（如ZYF_B）解决：map动态记录已有gcd值，状压则通过质因数集合压缩状态，均避免了无效状态的存储。  
    * 💡 **学习笔记**：当状态空间大时，用map/哈希表或质因数分解压缩状态是常用优化手段。

3.  **关键点3：如何设计状态转移以降低时间复杂度**  
    * **分析**：状压DP通过限制质因数数量（最多9个）将时间复杂度降至O(n²2⁹)；map DP通过仅处理已有状态，时间复杂度依赖于实际生成的gcd数量（通常较小）；Dijkstra则利用优先队列优先处理更优路径，避免无效计算。  
    * 💡 **学习笔记**：状态转移的设计需结合问题特性（如gcd的递减性），优先处理更可能接近目标的状态。

### ✨ 解题技巧总结
- **问题转化**：将“覆盖所有位置”转化为“gcd=1”的子集选择问题。
- **状态压缩**：利用质因数分解或map动态维护状态，避免大数组存储。
- **算法迁移**：将动态规划问题转化为最短路问题（如Dijkstra），利用优先队列优化。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们选择Kohakuwu的map优化DP代码作为通用核心实现，因其思路简洁、代码规范，适合初学者理解。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了map优化DP的思路，动态维护gcd状态及其最小成本，代码简洁高效。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    inline int read() {
        int x = 0, f = 1; char ch = getchar();
        while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
        while (ch >= '0' && ch <= '9') { x = x * 10 + (ch ^ 48); ch = getchar(); }
        return x * f;
    }

    int main() {
        int n = read();
        vector<int> l(n + 1), c(n + 1);
        for (int i = 1; i <= n; ++i) l[i] = read();
        for (int i = 1; i <= n; ++i) c[i] = read();

        map<int, int> mp;
        for (int i = 1; i <= n; ++i) {
            // 复制当前map的状态，避免迭代器失效
            auto temp = mp;
            for (auto [g, cost] : temp) {
                int new_g = gcd(g, l[i]);
                if (mp.count(new_g)) mp[new_g] = min(mp[new_g], cost + c[i]);
                else mp[new_g] = cost + c[i];
            }
            // 单独处理只选当前卡片的情况
            if (mp.count(l[i])) mp[l[i]] = min(mp[l[i]], c[i]);
            else mp[l[i]] = c[i];
        }

        if (mp.count(1)) cout << mp[1] << endl;
        else cout << -1 << endl;
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先读取输入，然后用map`mp`维护当前所有可能的gcd值及其最小成本。遍历每张卡片时，先复制当前map状态（避免迭代器失效），然后对每个已有gcd值g，计算与当前卡片l_i的新gcd`new_g`，并更新`mp[new_g]`的最小成本。最后单独处理只选当前卡片的情况。最终输出`mp[1]`（若存在）。

---
<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段：
</code_intro_selected>

**题解一：ZYF_B（状压DP）**
* **亮点**：利用质因数分解和状压，将状态数压缩至2⁹，时间复杂度低。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=n;i++) {
        memset(f,0x3f,sizeof(f));
        int M=1<<cnt[i];
        f[M-1]=cost[i];
        for(int j=1;j<=n;j++) {
            if(i==j) continue;
            int s=0;
            for(int k=1;k<=cnt[i];k++) {
                for(int x=1;x<=cnt[j];x++) {
                    if(g[i][k]==g[j][x]) { s|=(1<<(k-1)); break; }
                }
            }
            for(int k=0;k<M;k++)
                f[k&s]=min(f[k&s],f[k]+cost[j]);
        } 
        ans=min(ans,f[0]);
    }
    ```
* **代码解读**：  
  `cnt[i]`是第i个数的质因数个数，`g[i][k]`存储第i个数的第k个质因数。状态`f[s]`表示覆盖第i个数的质因数集合为s时的最小成本。初始时，选第i个数的成本为`cost[i]`（对应质因数集合全选，即`M-1`）。遍历其他卡片j，计算j的质因数与i的交集s，然后状态转移`f[k&s] = min(f[k&s], f[k]+cost[j])`。最终`f[0]`表示覆盖所有质因数（即gcd=1）的最小成本。  
* 💡 **学习笔记**：质因数分解是处理大数gcd问题的关键，状压适合状态数少的场景（如质因数≤9）。

**题解二：fanfansann（Dijkstra最短路）**
* **亮点**：将gcd状态视为图节点，用优先队列优化，直观易懂。
* **核心代码片段**：
    ```cpp
    void dijkstra() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.push({0, 0});
        dist[0] = 0;

        while (!q.empty()) {
            auto [d, u] = q.top(); q.pop();
            if (u == 1) break;
            if (vis.count(u)) continue;
            vis.insert(u);

            for (int i = 1; i <= n; ++i) {
                int v = gcd(u, l[i]);
                if (!dist.count(v)) dist[v] = INT_MAX;
                if (dist[v] > d + c[i]) {
                    dist[v] = d + c[i];
                    q.push({dist[v], v});
                }
            }
        }
    }
    ```
* **代码解读**：  
  `dist[u]`表示到达gcd=u的最小成本，初始时`dist[0]=0`（未选任何卡片时gcd=0）。优先队列按成本从小到大取出节点u，若u未访问过，则遍历所有卡片，计算新的gcd=v，并更新`dist[v]`。当取出u=1时，提前终止。  
* 💡 **学习笔记**：最短路算法适合处理“求最小成本路径”的问题，优先队列确保每次处理当前最优路径。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解gcd状态的转移过程，我们设计一个“像素gcd探险”动画，以8位复古风格展示map优化DP的状态更新。
</visualization_intro>

  * **动画演示主题**：像素探险——寻找gcd=1的宝藏  
  * **核心演示内容**：从初始状态（无卡片，gcd=0）开始，每选择一张卡片，生成新的gcd值，最终找到gcd=1的最小成本。

  * **设计思路简述**：  
    8位像素风格（如FC游戏画面）让学习更轻松；不同颜色的像素块代表不同gcd值（红色=1，蓝色=其他）；每生成新gcd值时，像素块分裂/合并并伴随“叮”声，强化操作记忆；目标达成（找到gcd=1）时播放胜利音效，增加成就感。

  * **动画帧步骤与交互关键点**：
    1. **场景初始化**：  
       屏幕左侧为“卡片库”（排列像素卡片，显示l_i和c_i），右侧为“gcd状态区”（空白网格，初始无状态）。控制面板有“单步”“自动播放”按钮和速度滑块。
    2. **选择第一张卡片**：  
       点击卡片1，卡片飞入状态区，生成gcd=l₁的像素块（如蓝色），显示成本c₁，播放“滴”声。
    3. **选择后续卡片**：  
       点击卡片i，遍历已有状态区的gcd块（如g），计算new_g = gcd(g, l_i)。若new_g未存在，生成新蓝色块；若已存在，比较成本，更新为更小值（像素块闪烁绿色）。
    4. **生成gcd=1**：  
       当某次计算得到new_g=1时，该像素块变为红色并放大，播放“胜利”音效（如《超级玛丽》吃金币声），状态区显示“找到宝藏！”。
    5. **控制面板交互**：  
       支持单步执行（逐张卡片选择）、自动播放（按设定速度连续选择）、重置（清空状态区，重新开始）。

  * **旁白提示**：  
    - “现在选择卡片i，它的l_i是XX，成本是XX。”  
    - “当前状态区有gcd=YY的块，计算与l_i的gcd得到ZZ。”  
    - “红色块出现！我们找到了gcd=1，总成本是XX！”

<visualization_conclusion>
通过这个动画，大家可以直观看到gcd状态如何从无到有，逐步更新，最终找到目标状态的过程，理解动态规划的核心思想。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，我们可以将思路迁移到其他需要“求最小成本的gcd条件子集”的问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    本题的核心是“选子集使gcd=1”，类似问题包括：  
    - 选数使gcd=k（调整目标gcd）；  
    - 选数使gcd的倍数覆盖特定范围；  
    - 多条件约束下的最小成本子集选择（如同时要求和最小、gcd=1）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1072  Hankson的趣味题**  
        * 🗣️ **推荐理由**：考察gcd的性质与因数分解，与本题的数论基础密切相关。
    2.  **洛谷 P2152 [SDOI2009] 晨跑**  
        * 🗣️ **推荐理由**：结合最短路与动态规划，适合练习算法迁移能力。
    3.  **洛谷 P3951 [NOIP2017 提高组] 小凯的疑惑**  
        * 🗣️ **推荐理由**：利用裴蜀定理解决“无法组成的最大数”问题，深化对数论应用的理解。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，例如：
</insights_intro>

> **参考经验 (来自AC自动机)**：“一开始没想到用map，直接用二维数组DP，结果空间和时间都爆炸。后来看题解才知道可以用map动态维护状态，避免无效计算。”

> **点评**：这位作者的经验提醒我们，当状态空间大时，要灵活使用map/哈希表等动态数据结构。遇到复杂问题时，参考题解的优化思路（如状态压缩、动态维护）能快速找到突破口。

---

<conclusion>
本次关于“Fox And Jumping”的分析就到这里。通过理解gcd的性质、动态规划的状态维护和最短路的迁移应用，相信大家已掌握此类问题的核心解法。编程的关键在于多思考、多实践，下次我们再一起探索新的挑战！💪
</conclusion>

---
处理用时：117.63秒