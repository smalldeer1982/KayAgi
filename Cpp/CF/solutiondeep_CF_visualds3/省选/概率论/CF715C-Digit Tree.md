# 题目信息

# Digit Tree

## 题目描述

ZS the Coder has a large tree. It can be represented as an undirected connected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ n-1 $ edges between them. There is a single nonzero digit written on each edge.

One day, ZS the Coder was bored and decided to investigate some properties of the tree. He chose a positive integer $ M $ , which is coprime to $ 10 $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/9b5bdec4cb6231baa1f3fcb57eb25703ae0eed8f.png).

ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting when if he would follow the shortest path from vertex $ u $ to vertex $ v $ and write down all the digits he encounters on his path in the same order, he will get a decimal representaion of an integer divisible by $ M $ .

Formally, ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting if the following states true:

- Let $ a_{1}=u,a_{2},...,a_{k}=v $ be the sequence of vertices on the shortest path from $ u $ to $ v $ in the order of encountering them;
- Let $ d_{i} $ ( $ 1<=i&lt;k $ ) be the digit written on the edge between vertices $ a_{i} $ and $ a_{i+1} $ ;
- The integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/72be647436ef167ccaba4334e08ad71c22afc6b4.png) is divisible by $ M $ .

Help ZS the Coder find the number of interesting pairs!

## 说明/提示

In the first sample case, the interesting pairs are $ (0,4),(1,2),(1,5),(3,2),(2,5),(5,2),(3,5) $ . The numbers that are formed by these pairs are $ 14,21,217,91,7,7,917 $ respectively, which are all multiples of $ 7 $ . Note that $ (2,5) $ and $ (5,2) $ are considered different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/08c05395fdf8f9a998abf43b020555e6b5471bd5.png)In the second sample case, the interesting pairs are $ (4,0),(0,4),(3,2),(2,3),(0,1),(1,0),(4,1),(1,4) $ , and $ 6 $ of these pairs give the number $ 33 $ while $ 2 $ of them give the number $ 3333 $ , which are all multiples of $ 11 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/8a71025758e81b9cf19889885872aec3ca3f5ffc.png)

## 样例 #1

### 输入

```
6 7
0 1 2
4 2 4
2 0 1
3 0 9
2 5 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 11
1 2 3
2 0 3
3 0 3
4 3 3
```

### 输出

```
8
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Digit Tree 深入学习指南 💡

<introduction>
今天我们来一起分析“Digit Tree”这道C++编程题。这道题要求我们统计树中所有有趣的点对(u, v)，即u到v路径上的边权拼接成的数字能被给定的M整除（M与10互质）。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`图论（点分治/树上启发式合并）与数论（模运算、逆元）结合`

🗣️ **初步分析**：
解决“Digit Tree”的关键在于高效统计树上满足条件的路径。由于树的结构复杂，直接枚举所有路径会超时（O(n²)），因此需要利用分治思想（点分治或DSU on Tree）将问题分解为子树问题，结合数论处理模运算。

简单来说，点分治的核心思想是找到树的重心（当前子树中最大子树最小的节点），统计经过该重心的所有路径，再递归处理子树。这样可以将时间复杂度从O(n²)优化到O(n log n)。在本题中，点分治用于分解树结构，而数论中的模逆元用于处理路径数字拼接的模运算（因M与10互质，10的幂次在模M下可逆）。

- **题解思路对比**：大部分题解采用点分治（如MikukuOvO、xfrvq等）或树上启发式合并（DSU on Tree，如orangejuice、whiteqwq）。点分治通过递归分解树，每次处理经过重心的路径；DSU on Tree则利用重儿子子树的信息保留特性，减少重复计算。两种方法均通过维护路径的正向/反向模值（如`disup`和`disdown`），结合map统计匹配的路径数。
- **核心算法流程**：以点分治为例，步骤包括：找重心→统计经过重心的路径→递归处理子树。统计路径时，计算每条路径的正向（从重心到节点）和反向（从节点到重心）模值，利用`map`记录反向值，用正向值查询匹配的反向值数量。
- **可视化设计思路**：设计8位像素风格的动画，展示树的分解过程（重心高亮）、路径的正向/反向模值计算（像素块移动+数值变化）、map的查询过程（高亮匹配的键值对）。关键步骤用颜色标记（如重心为绿色，当前处理路径为蓝色），音效提示（如匹配成功时“叮”声）。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码可读性、算法有效性等，筛选出以下优质题解：
</eval_intro>

**题解一：orangejuice（DSU on Tree）**
* **点评**：此题解详细推导了路径的数学表达式（`disup`和`disdown`的递推关系），并结合DSU on Tree的重儿子保留特性，避免重复计算。代码中变量命名清晰（如`disup`表示节点到根的反向路径模值，`disdown`表示根到节点的正向路径模值），边界处理严谨（如轻儿子处理时清空map）。亮点在于利用DSU on Tree将时间复杂度优化至O(n log n)，适合学习树的分治技巧。

**题解二：MikukuOvO（点分治）**
* **点评**：此题解思路简洁，直接点明路径拼接的模运算条件（`d1×10^l + d2 ≡ 0 mod M`），并通过变形为`d1 ≡ -d2×10^{-l} mod M`，利用map统计匹配的路径数。代码结构清晰，关键步骤注释明确（如`getdis`函数计算路径模值），适合理解点分治的核心流程。

**题解三：Register_int（点分治）**
* **点评**：此题解完整实现了点分治的核心逻辑，包括找重心、统计路径、容斥去重（减去同一子树内的重复路径）。代码中预处理了10的幂次和逆元（`pw`和`inv`数组），模运算处理细致，适合学习点分治的具体实现细节。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们通常会遇到以下关键点或难点：
</difficulty_intro>

1.  **关键点1：路径的数学建模**
    * **分析**：路径的拼接数字（如u到v的路径）可分解为u到LCA（最近公共祖先）的反向路径和LCA到v的正向路径。需要将这两部分的拼接转化为模运算，即`d1×10^l + d2 ≡ 0 mod M`（d1为反向路径模值，d2为正向路径模值，l为正向路径的边数）。
    * 💡 **学习笔记**：路径拼接的模运算可通过分解为两部分，并利用10的逆元将乘法转化为加法，简化计算。

2.  **关键点2：高效统计路径数**
    * **分析**：直接枚举所有路径会超时，需用点分治或DSU on Tree分解问题。点分治通过重心分解树，每次处理经过重心的路径；DSU on Tree利用重儿子子树的信息保留，减少重复计算。统计时用map记录反向路径的模值，正向路径查询匹配的反向值数量。
    * 💡 **学习笔记**：分治思想是处理树路径问题的核心，结合map等数据结构可高效统计匹配路径。

3.  **关键点3：模逆元的计算**
    * **分析**：因M与10互质，10的幂次在模M下存在逆元（通过扩展欧几里得算法计算）。逆元用于将`10^l`的除法转化为乘法（如`10^{-l} ≡ inv(10^l) mod M`），确保模运算的正确性。
    * 💡 **学习笔记**：模逆元是处理含除法模运算的关键，需熟练掌握扩展欧几里得算法。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题分解**：将树路径问题分解为经过当前根节点（重心或重儿子）的路径，递归处理子树。
- **数学变形**：将路径拼接的模条件变形为可统计的形式（如`d1 ≡ -d2×10^{-l} mod M`），利用map快速查询。
- **预处理优化**：预处理10的幂次和逆元（`pw`和`inv`数组），避免重复计算，提高效率。
- **容斥去重**：统计路径时，需减去同一子树内的重复路径（如点分治中先统计所有路径，再减去子树内的路径）。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个基于点分治的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了多个点分治题解的思路，实现了找重心、统计路径、递归处理子树的核心逻辑，适合学习点分治的完整流程。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int N = 1e5 + 10;

    int n, mod;
    vector<pair<int, int>> G[N];
    int siz[N], vis[N], rt, sum;
    ll ans;
    ll pw[N], inv[N];

    void exgcd(ll a, ll b, ll &x, ll &y) {
        if (!b) x = 1, y = 0;
        else exgcd(b, a % b, y, x), y -= a / b * x;
    }

    ll get_inv(ll a) {
        ll x, y;
        exgcd(a, mod, x, y);
        return (x % mod + mod) % mod;
    }

    void get_rt(int u, int fa) {
        siz[u] = 1;
        int maxp = 0;
        for (auto [v, w] : G[u]) {
            if (v == fa || vis[v]) continue;
            get_rt(v, u);
            siz[u] += siz[v];
            maxp = max(maxp, siz[v]);
        }
        maxp = max(maxp, sum - siz[u]);
        if (maxp < sum) sum = maxp, rt = u;
    }

    void dfs(int u, int fa, ll d1, ll d2, int dep, vector<pair<ll, int>> &tmp) {
        tmp.emplace_back(d2, dep); // 反向路径模值d2和边数dep
        for (auto [v, w] : G[u]) {
            if (v == fa || vis[v]) continue;
            ll new_d1 = (d1 * 10 + w) % mod; // 正向路径模值
            ll new_d2 = (d2 + w * pw[dep]) % mod; // 反向路径模值
            dfs(v, u, new_d1, new_d2, dep + 1, tmp);
        }
    }

    void calc(int u) {
        map<ll, int> cnt;
        cnt[0] = 1; // 处理d2=0的情况（根到自身的路径）
        for (auto [v, w] : G[u]) {
            if (vis[v]) continue;
            vector<pair<ll, int>> tmp;
            dfs(v, u, w, w, 1, tmp); // 计算子树v的路径信息
            for (auto [d2, dep] : tmp) {
                ll need = (-d2 * inv[dep] % mod + mod) % mod; // 计算需要的d1
                ans += cnt[need]; // 统计匹配的d1数量
            }
            for (auto [d2, dep] : tmp) {
                ll key = (d2 * inv[dep] % mod + mod) % mod; // 更新map中的d1
                cnt[key]++;
            }
        }
    }

    void solve(int u) {
        vis[u] = 1;
        calc(u); // 统计经过u的路径
        for (auto [v, w] : G[u]) {
            if (vis[v]) continue;
            sum = siz[v];
            get_rt(v, -1); // 找子树v的重心
            solve(rt); // 递归处理子树
        }
    }

    int main() {
        cin >> n >> mod;
        pw[0] = 1;
        for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * 10 % mod;
        inv[0] = 1;
        ll inv_10 = get_inv(10);
        for (int i = 1; i <= n; i++) inv[i] = inv[i - 1] * inv_10 % mod;

        for (int i = 1; i < n; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u++, v++;
            G[u].emplace_back(v, w % mod);
            G[v].emplace_back(u, w % mod);
        }

        sum = n;
        get_rt(1, -1);
        solve(rt);

        cout << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 该代码首先预处理10的幂次和逆元（`pw`和`inv`数组）。`get_rt`函数找树的重心，`dfs`函数计算子树内的路径模值，`calc`函数统计经过重心的路径数（利用map记录反向路径的模值，正向路径查询匹配的反向值）。`solve`函数递归处理子树，确保时间复杂度为O(n log n)。

---
<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段：
</code_intro_selected>

**题解一：orangejuice（DSU on Tree）**
* **亮点**：利用DSU on Tree的重儿子保留特性，减少重复计算，时间复杂度O(n log n)。
* **核心代码片段**：
    ```cpp
    void dfs_getans(int u, int f, int h) {
        for (int i = head[u]; ~i; i = e[i].nxt)
            if (e[i].to != f && e[i].to != son[u])
                dfs_getans(e[i].to, u, 0);
        if (son[u]) dfs_getans(son[u], u, 1);
        for (int i = head[u]; ~i; i = e[i].nxt) 
            if (e[i].to != f && e[i].to != son[u]) {
                Upd(e[i].to, u, u, 1); // 统计轻儿子子树的路径
                Upd(e[i].to, u, u, 0); // 将轻儿子子树的信息加入map
            }
        Calc(u, u); // 统计u自身的路径
        Add(u); // 将u的信息加入map
        if (!h) U.clear(), D.clear(); // 非重儿子时清空map
    }
    ```
* **代码解读**：
    > 这段代码是DSU on Tree的核心。首先递归处理轻儿子（`dfs_getans(e[i].to, u, 0)`），并清空其map；然后处理重儿子（`dfs_getans(son[u], u, 1)`），保留其map。接着处理轻儿子子树，统计路径后将信息加入map。最后统计当前节点u的路径，并根据是否是重儿子决定是否清空map。
* 💡 **学习笔记**：DSU on Tree通过保留重儿子的信息，避免重复计算子树，适合处理需要合并子树信息的问题。

**题解二：MikukuOvO（点分治）**
* **亮点**：直接利用点分治统计路径，代码简洁，思路清晰。
* **核心代码片段**：
    ```cpp
    void getdis(int u, int fa, ll d1, ll d2, int dep) {
        if (dep) mp[d1]++, dis[++cnt] = d2, dep[++cnt] = dep;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (v == fa || vis[v]) continue;
            getdis(v, u, (d1 + 1ll * pow[dep] * w) % mod, (d2 * 10 + w) % mod, dep + 1);
        }
    }
    ```
* **代码解读**：
    > `getdis`函数递归计算子树内的路径模值。`d1`为反向路径模值（从节点到重心），`d2`为正向路径模值（从重心到节点），`dep`为边数。若`dep>0`，将`d1`存入map，`d2`和`dep`存入数组，用于后续统计。
* 💡 **学习笔记**：点分治中，`getdis`函数负责收集子树的路径信息，是统计匹配路径的基础。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解点分治的过程，我们设计一个8位像素风格的动画，演示树的分解、路径统计和模运算匹配。
</visualization_intro>

  * **动画演示主题**：`像素树探险——寻找M的倍数路径`
  * **核心演示内容**：演示点分治的找重心、统计路径、递归处理子树的全过程，重点展示路径的正向/反向模值计算和map的匹配过程。
  * **设计思路简述**：采用8位像素风格（FC红白机配色），用不同颜色标记节点（重心为绿色，当前处理节点为蓝色）、路径（正向为红色，反向为黄色）。通过像素块移动和数值变化展示路径拼接，音效提示匹配成功（“叮”声）或递归处理（“滴答”声）。

  * **动画帧步骤与交互关键点**：
    1.  **场景初始化**：
        - 屏幕展示树的像素化结构（节点为圆形，边为直线，数字标在边上）。
        - 控制面板：单步/自动播放按钮、速度滑块、重置按钮。
        - 8位风格背景音乐（轻快的电子音乐）。

    2.  **找重心**：
        - 遍历树节点，计算各节点的最大子树大小（像素条长度表示），最终高亮重心（绿色闪烁）。

    3.  **统计路径**：
        - 从重心出发，递归访问子树，计算每条路径的正向/反向模值（像素块从节点移动到重心，数值动态更新）。
        - 将反向模值存入map（像素盒子弹出，显示键值对）。
        - 正向模值查询map，匹配时高亮对应的键值对（蓝色闪烁），并累加答案（数字弹出）。

    4.  **递归处理子树**：
        - 重心标记为已访问（灰色），对每个子树重复找重心、统计路径的过程（分屏展示子树）。

    5.  **完成提示**：
        - 所有路径处理完成后，播放胜利音效（上扬音），显示总答案（大字号数字）。

  * **旁白提示**：
      - “现在找树的重心，它能让子树尽可能平衡！”
      - “这条路径的正向模值是d1，反向模值是d2，我们需要d1 ≡ -d2×10^{-l} mod M。”
      - “匹配成功！答案加1！”

<visualization_conclusion>
通过这样的动画，我们能清晰看到点分治的每一步操作，理解路径统计和模运算的核心逻辑，让抽象的算法变得直观有趣。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考该算法/技巧的适用范围和变形应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 点分治不仅能解决本题，还适用于统计树上满足特定条件的路径数（如路径和为定值、路径异或和为定值）。
      - 模逆元的应用场景包括处理含除法的模运算（如组合数计算、路径拼接问题）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P2634 [国家集训队]聪聪可可**
          * 🗣️ **推荐理由**：统计树上路径和为3的倍数的点对，是点分治的经典应用，适合巩固路径统计技巧。
    2.  **洛谷 P4149 [IOI2011]Race**
          * 🗣️ **推荐理由**：统计树上长度不超过K的路径，需结合点分治和双指针，拓展路径统计的变形应用。
    3.  **洛谷 P3806 【模板】点分治1**
          * 🗣️ **推荐理由**：点分治的模板题，直接练习找重心、统计路径的核心步骤。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，对我们有重要参考价值：
</insights_intro>

> **参考经验 (来自 orangejuice)**：“在处理轻儿子时，一定要先统计路径再添加信息，否则会重复计算同一子树内的路径。”
>
> **点评**：这位作者的经验提醒我们，分治或DSU on Tree中，路径统计的顺序（先统计后添加）是避免重复的关键。在实际编码中，需严格遵循“先统计轻儿子，再添加信息”的流程。

-----

<conclusion>
本次关于“Digit Tree”的C++解题分析就到这里。希望这份学习指南能帮助大家理解点分治和DSU on Tree的核心思想，掌握路径统计和模运算的技巧。记住，多动手编码、调试，才能真正掌握算法的精髓！下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：164.20秒