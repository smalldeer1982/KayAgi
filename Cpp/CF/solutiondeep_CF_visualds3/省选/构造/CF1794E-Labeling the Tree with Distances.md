# 题目信息

# Labeling the Tree with Distances

## 题目描述

You are given an unweighted tree of $ n $ vertices numbered from $ 1 $ to $ n $ and a list of $ n-1 $ integers $ a_1, a_2, \ldots, a_{n-1} $ . A tree is a connected undirected graph without cycles. You will use each element of the list to label one vertex. No vertex should be labeled twice. You can label the only remaining unlabeled vertex with any integer.

A vertex $ x $ is called good if it is possible to do this labeling so that for each vertex $ i $ , its label is the distance between $ x $ and $ i $ . The distance between two vertices $ s $ and $ t $ on a tree is the minimum number of edges on a path that starts at vertex $ s $ and ends at vertex $ t $ .

Find all good vertices.

## 说明/提示

This is the tree for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1794E/f54192bbd4a09409727069f5296c3b8069512eac.png)And these are two possible labelings with the elements on the list so that $ 2 $ is a good vertex (left) and $ 4 $ is a good vertex (right).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1794E/e87e5306fe63a198bad6dafe8ce7c0bd63e8d99b.png)The square below each vertex represents its label. The black squares contain the numbers which were on the given list and the only white square contains the only number which was not on the given list.

In the second example, the only good vertex is vertex $ 3 $ .

In the third example, there are no good vertices.

## 样例 #1

### 输入

```
6
2 1 0 1 2
1 2
2 3
2 4
4 5
4 6```

### 输出

```
2
2 4```

## 样例 #2

### 输入

```
5
1 2 1 2
1 2
3 2
3 4
5 4```

### 输出

```
1
3```

## 样例 #3

### 输入

```
3
2 2
1 2
2 3```

### 输出

```
0```

# AI分析结果

# 💡 Kay的C++算法解析：Labeling the Tree with Distances 深入学习指南 💡

<introduction>
今天我们来一起分析「Labeling the Tree with Distances」这道C++编程题。这道题结合了树的换根动态规划（二次扫描法）和哈希技术，需要我们**快速计算每个节点作为根时的深度分布**，并**高效比较分布是否匹配题目要求**。本指南会帮你梳理思路、理解核心算法，还会用像素动画直观展示换根过程～
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：树的换根动态规划（二次扫描法） + 哈希集合匹配

🗣️ **初步分析**：
解决这道题的关键，是理解「好点」的本质——**当某个节点u作为根时，所有节点的深度（到u的距离）集合，恰好包含题目给的n-1个数（只剩一个数可以任意）**。

### 算法核心思想类比
- **换根动态规划**：就像给树换「视角」——原本我们只能计算以节点1为根的深度分布，但通过换根，我们能**O(n)时间**快速得到所有节点作为根的分布（不用重复遍历整棵树）。
- **哈希集合匹配**：把每个深度分布变成一个「数字指纹」（哈希值），这样比较两个分布是否一致，只需要比较指纹就行。比如，题目给的n-1个数的指纹是`target`，而每个根u的指纹是`hash_u`，如果`hash_u - target`是某个`base^k`（表示少了一个深度为k的点），那u就是好点！

### 核心流程与可视化设计思路
1. **计算子树哈希**：第一次DFS遍历树，计算每个节点作为子树根时的深度分布哈希（比如`f[u]`表示以u为根的子树哈希）。
2. **换根更新哈希**：第二次DFS遍历树，从父节点u换到子节点v时，**调整哈希值**（减去v子树的贡献，加上父节点那边的贡献，再乘base——因为深度增加1）。
3. **匹配哈希**：每得到一个节点的哈希，就检查`hash_u - target`是否是`base`的幂次（比如用set存所有`base^k`）。

### 像素动画设计预告
我们会用**8位像素风**展示树结构：
- 节点用彩色方块表示，根节点闪烁高亮；
- 深度用颜色区分（比如深度0红、1蓝、2绿）；
- 换根时，节点颜色动态变化，伴随「叮」的音效；
- 匹配成功的好点会弹出像素星星，播放胜利音效～


## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度、代码可读性、算法有效性**三个维度筛选了2份优质题解，它们都完美覆盖了换根+哈希的核心逻辑，且各有亮点！
</eval_intro>

### 题解一（作者：小木虫，赞：7）
* **点评**：这份题解的**最大亮点是「多次哈希」**——用了3个不同的模数（998244353、1e9+7、1e9+9）和随机base，几乎彻底避免了哈希碰撞（竞赛中常用的「保险操作」）。代码结构非常清晰：
  - `getHash`函数后序遍历计算子树哈希；
  - `dfs`函数前序遍历换根，调整哈希值；
  - 最后统计3次哈希都匹配的节点（`res[i]==3`）。
  从实践角度看，这份代码的鲁棒性极强，直接用于竞赛也能轻松AC！

### 题解二（作者：CuCl4Loliko，赞：3）
* **点评**：这份题解的**亮点是「换根逻辑的明确拆分」**——用`f[u]`表示子树内的哈希，`g[u]`表示子树外的哈希，换根时通过`g[v] = (f[u] - f[v]*base + g[u]) * base`直接推导，逻辑非常直观。此外，它用了**双模哈希**（两次不同的模数计算），兼顾效率和准确性。对于刚学换根DP的同学，这份题解的推导过程能帮你更快理解「如何调整哈希」。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的难点集中在「如何高效计算每个根的深度分布」和「如何处理少一个点的情况」。结合题解的共性，我总结了3个核心关键点：
</difficulty_intro>

### 1. 关键点1：如何用哈希表示深度分布？
- **问题**：深度分布是「每个深度有多少个节点」（比如深度0有1个，深度1有2个），如何把这个分布转化为唯一的哈希值？
- **解决方案**：用**多项式哈希**——`hash = cnt_0*base^0 + cnt_1*base^1 + ... + cnt_{max_depth}*base^{max_depth} mod MOD`。其中`cnt_k`是深度为k的节点数，`base`是一个大于n的数（避免不同分布哈希相同）。
- 💡 **学习笔记**：多项式哈希是「集合/序列的指纹」，适合快速比较两个集合是否一致。

### 2. 关键点2：换根时如何更新哈希？
- **问题**：当根从u换到v（u是v的父节点），所有节点的深度都会变化（v的子树深度-1，其他节点深度+1），如何快速更新哈希？
- **解决方案**：换根时，**减去v子树的贡献**（`hash_u -= f[v] * base`），**加上父节点那边的贡献**（`hash_v += (hash_u + g[u]) * base`）。比如题解二中的`g[v]`就是父节点那边的哈希贡献。
- 💡 **学习笔记**：换根的核心是「调整子树内外的贡献」，避免重复计算整棵树。

### 3. 关键点3：如何处理「少一个点」的情况？
- **问题**：题目给的是n-1个数的集合，而每个根的深度分布是n个点的，如何判断「去掉一个点后是否匹配」？
- **解决方案**：计算目标哈希`target`（n-1个数的多项式哈希），然后检查`hash_u - target`是否是`base^k`（k是某个深度）——因为去掉一个深度为k的点，相当于哈希值减去`base^k`。
- 💡 **学习笔记**：把「少一个点」转化为「哈希差是base的幂」，用set存所有`base^k`就能快速判断。

### ✨ 解题技巧总结
1. **换根DP是树的「全局视角工具」**：当需要计算所有节点作为根的信息时，优先考虑换根（二次扫描法），时间复杂度O(n)。
2. **哈希要「防碰撞」**：竞赛中常用多次哈希（不同模数+不同base），避免因为哈希冲突导致错误。
3. **问题转化是关键**：把「深度集合匹配」转化为「哈希值比较」，把「少一个点」转化为「哈希差是幂次」，让复杂问题变简单。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**通用核心实现**——综合了两份题解的思路，用换根DP计算每个根的哈希，并用哈希匹配找好点。
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：本代码基于「换根DP+多项式哈希」的经典思路，用两次DFS计算子树哈希和换根哈希，适合入门学习。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const ll MOD = 1e9 + 7;
const ll BASE = 20200721;

vector<int> edge[N];
ll f[N], g[N], target; // f[u]:子树内哈希；g[u]:子树外哈希
int a[N], n;
set<ll> power_set; // 存base的幂次

ll qpow(ll a, ll b) { // 快速幂计算base^b mod MOD
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void dfs1(int u, int fa) { // 第一次DFS：计算子树内哈希f[u]
    f[u] = 1; // 深度0的节点（自己）贡献1*base^0
    for (int v : edge[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        f[u] = (f[u] + f[v] * BASE) % MOD; // 子节点的哈希乘base（深度+1）后累加
    }
}

void dfs2(int u, int fa) { // 第二次DFS：换根计算全局哈希
    ll total_hash = (f[u] + g[u]) % MOD; // 全局哈希=子树内+子树外
    if (power_set.count((total_hash - target + MOD) % MOD)) {
        cout << "好点：" << u << endl; // 匹配成功
    }
    for (int v : edge[u]) {
        if (v == fa) continue;
        // 计算v的子树外哈希g[v]：父节点u的哈希减去v的贡献，再乘base（深度+1）
        g[v] = ((f[u] - f[v] * BASE % MOD + MOD) % MOD + g[u]) % MOD * BASE % MOD;
        dfs2(v, u);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    // 计算目标哈希target（n-1个数的多项式哈希）
    target = 0;
    for (int i = 1; i < n; i++) {
        target = (target + qpow(BASE, a[i])) % MOD; // a[i]是深度，贡献base^a[i]
    }

    // 预处理base的幂次（0到n，因为深度最大是n-1）
    ll power = 1;
    for (int i = 0; i <= n; i++) {
        power_set.insert(power);
        power = power * BASE % MOD;
    }

    dfs1(1, 0); // 以1为根计算子树哈希
    dfs2(1, 0); // 换根计算所有节点的全局哈希

    return 0;
}
```
* **代码解读概要**：
  1. `dfs1`：后序遍历，计算每个节点作为子树根的哈希（`f[u]`）——子节点的哈希乘`BASE`（深度+1）后累加。
  2. `dfs2`：前序遍历，换根时计算子树外的哈希（`g[v]`），然后合并`f[u]+g[u]`得到全局哈希。
  3. 匹配：检查全局哈希与`target`的差是否在`power_set`中（即少一个深度的点）。

---

<code_intro_selected>
接下来看两份优质题解的**核心片段**，重点分析它们的「换根逻辑」和「哈希处理」。
</code_intro_selected>

### 题解一（作者：小木虫）核心片段
* **亮点**：多次哈希+随机base，彻底避免碰撞。
* **核心代码片段**：
```cpp
void getHash(int u, int fa, const int base, const int mod) {
    Hash[u] = 0;
    for (auto v : edge[u]) {
        if (v == fa) continue;
        getHash(v, u, base, mod);
        Hash[u] = (Hash[u] + Hash[v] * base) % mod;
    }
    Hash[u] = (Hash[u] + 1) % mod; // 深度0的节点贡献1*base^0
}

void dfs(int u, int fa, const int base, const int mod) {
    Hash[u] = (Hash[u] + Hash[fa] * base) % mod; // 加上父节点那边的贡献（深度+1）
    if (table[(Hash[u] - tar + mod) % mod]) res[u]++; // 匹配哈希差

    for (auto v : edge[u]) {
        if (v == fa) continue;
        Hash[u] = (Hash[u] - Hash[v] * base % mod + mod) % mod; // 减去v子树的贡献
        dfs(v, u, base, mod);
        Hash[u] = (Hash[u] + Hash[v] * base % mod) % mod; // 恢复v子树的贡献
    }

    Hash[u] = (Hash[u] - Hash[fa] * base % mod + mod) % mod; // 恢复父节点的贡献
}
```
* **代码解读**：
  - `getHash`：计算子树哈希，`Hash[u] += 1`对应深度0的节点（自己）。
  - `dfs`：换根时，**先加上父节点的贡献**（`Hash[fa]*base`，因为从父节点到当前节点，深度+1），然后**减去子节点的贡献**（避免重复计算），递归处理子节点后再恢复。
* 💡 **学习笔记**：换根时的「加减恢复」是关键——确保每个节点的哈希计算只包含当前根的子树内外贡献。

### 题解二（作者：CuCl4Loliko）核心片段
* **亮点**：明确拆分`f`（子树内）和`g`（子树外）的哈希。
* **核心代码片段**：
```cpp
void dfs1(int u, int fa) {
    f[u] = BASE; // 深度0的节点贡献BASE^1？不，看后续推导：f[u] = base + sum(f[v]*base)
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        f[u] = (f[u] + f[v] * BASE) % MOD;
    }
}

void dfs2(int u, int fa) {
    ll now = (f[u] + g[u]) % MOD; // 全局哈希
    if (S.find((now - target + MOD) % MOD) != S.end()) ans[u]++;

    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        // g[v] = (父节点u的哈希 - v子树的贡献 + g[u]) * base
        g[v] = (f[u] - f[v] * BASE % MOD + g[u] + MOD) % MOD * BASE % MOD;
        dfs2(v, u);
    }
}
```
* **代码解读**：
  - `dfs1`：计算子树内哈希`f[u]`，`f[u] = BASE + sum(f[v]*BASE)`——这里的`BASE`对应深度0的节点（自己）的贡献（`BASE^1`？其实是作者调整了哈希的形式，不影响比较结果）。
  - `dfs2`：计算子树外哈希`g[v]`——父节点u的哈希（`f[u] - f[v]*BASE`）加上`g[u]`（u的子树外哈希），再乘`BASE`（深度+1）。
* 💡 **学习笔记**：把哈希拆分成「子树内」和「子树外」，能让换根逻辑更直观，适合刚学换根DP的同学。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让大家「看」到换根和哈希的过程，我设计了一个**8位像素风动画**——像玩FC游戏一样，直观感受树的视角变化和哈希匹配！
</visualization_intro>

### 动画演示主题
「像素树的视角大冒险」——你操控一个像素小人，给树换不同的根，寻找能匹配哈希的「好点」。

### 设计思路
用**FC红白机的色彩风格**（红、蓝、绿、黄四色为主），树节点用2x2像素方块表示，根节点闪烁，深度用颜色区分。通过**单步/自动播放**，让你清晰看到每个步骤的变化。

### 动画帧步骤与交互关键点
#### 1. 初始化场景（8位像素风）
- **树结构**：用像素方块画出样例1的树（节点1-6，边1-2、2-3、2-4、4-5、4-6）。
- **UI面板**：底部有「开始/暂停」「单步」「重置」按钮，右侧有速度滑块（1x~5x），顶部显示「目标哈希：xxx」。
- **音效**：播放8位风格的轻快BGM（如《超级马里奥》的背景音）。

#### 2. 第一次DFS：计算子树哈希
- **过程**：从根1开始，后序遍历每个节点，计算`f[u]`（子树哈希）。每个节点的哈希值显示在方块下方，用「叮」的音效提示计算完成。
- **高亮**：当前计算的节点闪烁黄色，子节点计算完成后变成绿色。

#### 3. 换根过程：从1到2
- **步骤**：
  1. 根从1换到2（1是2的父节点）。
  2. 计算2的子树外哈希`g[2]`：`(f[1] - f[2]*BASE + g[1]) * BASE`（`g[1]=0`，因为1是初始根）。
  3. 合并`f[2]+g[2]`得到2的全局哈希，检查是否匹配目标。
- **可视化**：
  - 节点2变成红色（新根），节点1的颜色从红变蓝（深度+1）。
  - 哈希值动态更新，匹配成功时节点2弹出像素星星，播放「叮~叮」的胜利音效。

#### 4. 自动演示模式
- 点击「自动播放」，小人会自动遍历所有节点，换根并计算哈希。匹配成功的好点（如样例1的2、4）会被标记为金色，最后显示所有好点。

#### 5. 交互设计
- **单步执行**：点击「单步」，动画走一步，显示当前步骤的伪代码（如「计算g[v] = ...」）。
- **速度滑块**：调整自动播放的速度，最慢1秒一步，最快0.1秒一步。
- **重置**：恢复初始状态，重新开始演示。

<visualization_conclusion>
通过这个动画，你能**直观看到换根时树的深度变化**，以及**哈希如何动态更新**。游戏化的元素（星星、音效）能让学习更有趣，也能帮你记住关键步骤～
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
换根DP是树算法中的「万能工具」，能解决很多「求所有节点作为根的信息」的问题。掌握了本题的思路，你可以尝试以下练习：
</similar_problems_intro>

### 通用思路迁移
- **求所有节点的子树大小**：换根时，子树大小=父节点的子树大小 - 当前节点的子树大小 + 1。
- **求所有节点的最长路径（树的直径）**：换根时，维护每个节点的最长和次长路径。
- **求所有节点的总距离**：换根时，总距离=父节点的总距离 + (n - 2*子树大小)。

### 洛谷练习推荐
1. **洛谷 P1352 没有上司的舞会**  
   🗣️ **推荐理由**：换根DP的经典入门题，需要计算每个节点作为根时的最大快乐值，帮你熟悉换根的基本逻辑。
2. **洛谷 P2986 [USACO10MAR]Great Cow Gathering G**  
   🗣️ **推荐理由**：需要计算所有节点作为聚会点的总移动距离，换根时的公式推导和本题类似，能巩固「调整子树内外贡献」的思路。
3. **洛谷 P3478 [POI2008]STA-Station**  
   🗣️ **推荐理由**：求所有节点作为根时的最长路径长度，需要维护每个节点的最长和次长路径，是换根DP的进阶练习。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
两份题解都提到了「哈希碰撞」的问题，这是竞赛中的常见陷阱。以下是值得借鉴的经验：
</insights_intro>

> **参考经验（来自小木虫）**：「我用了三次不同的模数和随机base，这样即使一次哈希碰撞，三次都碰撞的概率几乎为0。」  
> **点评**：哈希碰撞是「小概率但致命」的错误，多次哈希是最有效的解决方法。比如本题中，用3个模数计算，只有3次都匹配的节点才是好点，彻底避免了错误。

> **参考经验（来自CuCl4Loliko）**：「换根时的公式推导要仔细，比如g[v]的计算需要减去f[v]*base，再加上g[u]，最后乘base。」  
> **点评**：换根的核心是「调整贡献」，推导公式时要「代入具体例子」验证——比如样例1中，从1换到2，g[2]应该等于f[1] - f[2]*base（父节点1的哈希减去2的子树贡献），再乘base（深度+1），这样才能得到正确的子树外哈希。


<conclusion>
本次分析就到这里！这道题的核心是「换根DP+哈希」，关键在于**把树的全局信息转化为可快速比较的哈希值**。记住：换根DP能帮你快速遍历所有视角，哈希能帮你快速比较集合——两者结合，就能解决很多树的问题！

下次遇到树的问题，不妨想想：「能不能用换根DP计算所有根的信息？能不能用哈希快速比较？」——多思考，多练习，你会越来越厉害～💪
</conclusion>

---
处理用时：144.17秒