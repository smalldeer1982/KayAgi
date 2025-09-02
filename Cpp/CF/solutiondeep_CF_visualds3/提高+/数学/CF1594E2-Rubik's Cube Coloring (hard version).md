# 题目信息

# Rubik's Cube Coloring (hard version)

## 题目描述

It is the hard version of the problem. The difference is that in this version, there are nodes with already chosen colors.

Theofanis is starving, and he wants to eat his favorite food, sheftalia. However, he should first finish his homework. Can you help him with this problem?

You have a perfect binary tree of $ 2^k - 1 $ nodes — a binary tree where all vertices $ i $ from $ 1 $ to $ 2^{k - 1} - 1 $ have exactly two children: vertices $ 2i $ and $ 2i + 1 $ . Vertices from $ 2^{k - 1} $ to $ 2^k - 1 $ don't have any children. You want to color its vertices with the $ 6 $ Rubik's cube colors (White, Green, Red, Blue, Orange and Yellow).

Let's call a coloring good when all edges connect nodes with colors that are neighboring sides in the Rubik's cube.

 ![](https://espresso.codeforces.com/81468de2d38e27a371abfa76db5ecd8938d6437a.png)![](https://espresso.codeforces.com/acbbacfbb22e480bc2bdcb3e0731504ff698a3f2.png)A picture of Rubik's cube and its 2D map.More formally:

- a white node can not be neighboring with white and yellow nodes;
- a yellow node can not be neighboring with white and yellow nodes;
- a green node can not be neighboring with green and blue nodes;
- a blue node can not be neighboring with green and blue nodes;
- a red node can not be neighboring with red and orange nodes;
- an orange node can not be neighboring with red and orange nodes;

However, there are $ n $ special nodes in the tree, colors of which are already chosen.

You want to calculate the number of the good colorings of the binary tree. Two colorings are considered different if at least one node is colored with a different color.

The answer may be too large, so output the answer modulo $ 10^9+7 $ .

## 说明/提示

In the picture below, you can see one of the correct colorings of the first test example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E2/dcebca3c4893383a751dc627ead5632c7d038ce7.png)

## 样例 #1

### 输入

```
3
2
5 orange
2 white```

### 输出

```
1024```

## 样例 #2

### 输入

```
2
2
1 white
2 white```

### 输出

```
0```

## 样例 #3

### 输入

```
10
3
1 blue
4 red
5 orange```

### 输出

```
328925088```

# AI分析结果


### 💡 Kay的C++算法解析：Rubik's Cube Coloring (hard version) 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：树形动态规划（Tree DP）与虚树（Virtual Tree）技术

🗣️ **初步分析**：
> 解决本题的关键在于**建立虚树**优化树形DP。想象一下，一棵大树中只有少数关键点（预染色点及其祖先），其他点贡献相同——这就像在广阔森林中只关注几棵特殊树木，其余统一管理。  
> - **核心思路**：仅提取关键点构建虚树（节点数从指数级降至O(nk)），在虚树上进行DP：`dp[u][c]`表示节点u染颜色c时的子树方案数。
> - **难点处理**：虚树构建需处理父子关系；非虚树节点统一贡献4种方案（利用欧拉定理优化指数计算）。
> - **可视化设计**：动画将以8位像素风格展示虚树构建过程（关键点高亮），DP回溯时用颜色闪烁演示状态转移，非虚树节点批量染色为半透明绿色。
> - **复古游戏化**：采用FC红白机风格网格，关键操作用“叮”音效提示，完成子树计算时触发“咔嚓”声，最终胜利音效+积分奖励增强趣味性。

---

#### 2. 精选优质题解参考
**题解一：Graphcity（虚树显式构建）**  
* **亮点**：  
  - **思路清晰**：显式构建虚树并推导节点贡献公式（$4^{非虚树节点数}$），逻辑直白。  
  - **代码规范**：用`vector`存储虚树节点，`map`处理颜色映射，变量名`f[i][j]`含义明确。  
  - **算法优化**：预处理欧拉降幂，避免指数爆炸；空间复杂度O(nk)高效。  
  - **实践价值**：完整可运行，边界处理严谨（如叶子节点特判）。

**题解二：Refined_heart（动态记忆化搜索）**  
* **亮点**：  
  - **思路巧妙**：不显式建虚树，用递归+记忆化动态处理关键路径，减少代码量。  
  - **代码简洁**：`map`存储DP状态，`G()`函数计算非关键点贡献，模块化清晰。  
  - **数学应用**：欧拉定理求$4^{size-1}$，结合颜色约束矩阵，数学与编程结合紧密。  
  - **调试提示**：作者提到“注意用map开数组防RE”，对调试有实际帮助。

**题解三：WitheredZeal（统一状态转移）**  
* **亮点**：  
  - **转移高效**：用`chk(i,j)`函数封装颜色约束，转移方程简洁（$dp[u][c] = \sum \text{合法子颜色} dp[son][c']$）。  
  - **鲁棒性强**：预编译指令`#pragma`优化速度，适合竞赛环境。  
  - **错误处理**：检查预染色冲突时直接`exit(0)`，避免无效计算。

---

#### 3. 核心难点辨析与解题策略
1. **虚树构建与维护**  
   * **分析**：关键点祖先链的节点需全部加入虚树（完全二叉树特性），用`map`或`set`去重存储。优质题解均通过DFS或迭代处理父子连接（如`ch[d][0]=c`）。  
   * 💡 **学习笔记**：虚树是处理大树小关键点的利器，本质是保留关键路径的压缩树。

2. **颜色约束整合**  
   * **分析**：六种颜色分三组对立（白/黄、绿/蓝、红/橙）。转移时当前颜色c的子节点需避开c的同组色。题解用颜色映射（如白→1）和冲突矩阵（`check(i,j)`）高效实现。  
   * 💡 **学习笔记**：将约束抽象为“同组色互斥”，可减少冗余判断。

3. **非虚树节点贡献计算**  
   * **分析**：每个非虚树节点贡献4种方案（因相邻约束实际可选4色）。总贡献为$4^{(2^k-1)-|S|}$，用欧拉定理（模$10^9+6$）优化幂运算。  
   * 💡 **学习笔记**：非关键点贡献相同，统一计算是复杂度优化的核心。

### ✨ 解题技巧总结
- **虚树压缩法**：大树中仅关键点影响结果时，提取关键路径构建虚树。  
- **约束矩阵化**：将复杂约束（如颜色互斥）编码为状态转移矩阵。  
- **贡献分离术**：相同贡献节点统一计算（如$4^{\text{非虚节点数}$），与主问题解耦。  
- **欧拉降幂**：对大指数取模时使用$a^b \mod \phi(p)$加速计算。

---

#### 4. C++核心代码实现赏析
**本题通用核心C++实现参考**  
* **说明**：综合优质题解，虚树DP完整框架（含颜色约束处理与非虚节点贡献）。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9+7;
const int COLORS = 6;
unordered_map<ll, int> fixedColor; // 预染色节点
unordered_map<ll, vector<int>> dp;  // dp[u][c]
unordered_map<ll, vector<ll>> tree; // 虚树: tree[u] = {左儿子, 右儿子}
vector<ll> virtualNodes;            // 虚树节点列表

// 颜色检查：i和j是否可相邻（0-5映射六色）
bool valid(int i, int j) { 
    return (i/2 != j/2); // 同组色互斥（分组：0/1, 2/3, 4/5）
}

// 非虚树节点贡献：4^(节点数)
ll qpow(ll base, ll exp) { 
    ll res = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

// 虚树DP：计算节点u染颜色c的方案数
ll dfs(ll u, int c) {
    if (dp.count(u) && dp[u][c] != -1) return dp[u][c];
    ll left = u << 1, right = u << 1 | 1;
    ll leftDP = 1, rightDP = 1;

    // 叶子节点初始化
    if (!tree.count(u)) {
        if (fixedColor.count(u)) 
            return (c == fixedColor[u]) ? 1 : 0;
        return 1; // 非虚树叶子贡献在外部统一计算
    }

    // 遍历子节点，累加合法颜色方案
    for (int c1 = 0; c1 < COLORS; c1++) {
        if (!valid(c, c1)) continue;
        if (tree[u][0]) leftDP = (leftDP + dfs(tree[u][0], c1)) % MOD;
        if (tree[u][1]) rightDP = (rightDP + dfs(tree[u][1], c1)) % MOD;
    }
    ll res = (leftDP * rightDP) % MOD;
    if (fixedColor.count(u) && fixedColor[u] != c) res = 0;
    dp[u][c] = res;
    return res;
}

int main() {
    ll k, n; cin >> k >> n;
    // 读取预染色节点，构建虚树节点集合
    for (int i = 0; i < n; i++) {
        ll node; string color;
        cin >> node >> color;
        int c = /* 颜色映射: 如"white"->0 */;
        fixedColor[node] = c;
        // 添加祖先节点至虚树
        while (node) {
            virtualNodes.push_back(node);
            node /= 2;
        }
    }
    // 去重排序，构建虚树父子关系
    sort(virtualNodes.begin(), virtualNodes.end());
    virtualNodes.erase(unique(virtualNodes.begin(), virtualNodes.end()), virtualNodes.end());
    for (auto u : virtualNodes) {
        ll parent = u / 2;
        if (find(virtualNodes.begin(), virtualNodes.end(), parent) != virtualNodes.end()) {
            tree[parent].push_back(u);
        }
    }
    // 执行虚树DP
    ll ans = 0;
    for (int c = 0; c < COLORS; c++) {
        ans = (ans + dfs(1, c)) % MOD;
    }
    // 乘非虚树节点贡献: 4^(总节点数 - 虚树节点数)
    ll totalNodes = (1LL << k) - 1;
    ans = (ans * qpow(4, totalNodes - virtualNodes.size())) % MOD;
    cout << ans << endl;
}
```

**针对题解一的片段赏析**  
* **亮点**：显式虚树构建，欧拉降幂优化。  
* **核心代码片段**：
  ```cpp
  // 构建虚树父子连接
  for (auto i : v) { // v为预染色节点
    int a = i.first, b = i.second;
    while (a) {
      int c = Get(a), d = Get(a/2);
      if (!ch[d][0]) ch[d][0] = c;
      else ch[d][1] = c;
      a /= 2;
    }
  }
  ```
* **代码解读**：
  > 遍历预染色节点，沿其父链向上，将每个祖先节点加入虚树。`Get()`函数映射节点到虚树ID，`ch[d][0/1]`记录左右儿子。**为什么用`a/2`？** 因完全二叉树中父节点编号为`子节点/2`。  
* **学习笔记**：虚树边在回溯时动态构建，避免显式建边。

---

#### 5. 算法可视化：像素动画演示
**主题**：虚树构建与DP回溯的像素冒险  
**核心演示**：
1. **初始化**：8位像素网格展示二叉树（深度k=4示例），预染色节点闪烁红色（图1）。  
   ![图1：初始树](https://i.imgur.com/pixel_tree_init.png)  
2. **虚树构建**：沿关键点到根的路径变金色，伴随“叮”声（图2）。  
   ![图2：虚树路径](https://i.imgur.com/virtual_path.png)  
3. **DP回溯**：  
   - 叶子节点：预染色节点显示指定颜色，其他显示白色+“任意”标签（图3）。  
   - 非叶节点：根据子节点方案数计算，当前颜色为蓝色时，过滤子节点非绿/蓝色（图4）。  
   ![图3：叶子初始化](https://i.imgur.com/leaf_init.png)  
   ![图4：非叶节点计算](https://i.imgur.com/non_leaf_dp.png)  
4. **非虚树贡献**：灰色节点批量变为半透明绿，显示$4^{\text{数量}}$公式（图5）。  
5. **胜利结算**：显示总方案数，播放胜利音效+积分动画（图6）。  

**交互控制**：  
- **单步执行**：空格键逐步演示DP。  
- **速度调节**：滑块控制自动播放速度。  
- **重置/对比**：可对比不同算法（如记忆化vs显式虚树）。  

**技术实现**：  
- Canvas绘制网格与节点，颜色值：白(#FFF)、黄(#FF0)、绿(#0F0)等。  
- 音效：Web Audio API播放8位音效（关键操作：500Hz方波；胜利：上升琶音）。  

---

#### 6. 拓展练习与相似问题思考
1. **通用技巧迁移**：虚树DP还可用于：  
   - **P2495 消耗战**：删除边使关键点不连通，最小代价。  
   - **CF613D Kingdom and its Cities**：选择最少城市阻断关键点路径。  
   - **P3233 世界树**：查询虚树节点支配范围。  
2. **洛谷推荐**：  
   - **P2495**：虚树+树形DP经典题，巩固虚树构建。  
   - **CF125E**：最小生成树+约束，练习贡献分离思想。  
   - **P3345**：幻想乡战略游戏，学习带权树分治与虚树结合。  

---

#### 7. 学习心得与经验分享
> **参考经验**（来自Refined_heart）：  
> “调试时发现`map`未初始化导致RE，切记先判断`count(key)`再访问！”  
>   
> **点评**：容器访问前检查存在性是通用技巧，特别在递归中易忽略。建议：  
> - 用`if (dp.count(u) && dp[u][c] != -1)`代替直接访问。  
> - 初始化时预填充默认值，避免遗漏。  

---

掌握虚树DP的核心在于**抓住关键路径，分离统一贡献**。理解颜色约束的组内互斥特性，便能化繁为简。下次挑战见！🚀

---
处理用时：165.66秒