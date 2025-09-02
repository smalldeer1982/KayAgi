# 题目信息

# LuoTianyi and the Floating Islands (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ k\le n $ . You can make hacks only if both versions of the problem are solved.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/12896184a3f823fcd8518f46dc5b68823c932f0f.png) Chtholly and the floating islands.LuoTianyi now lives in a world with $ n $ floating islands. The floating islands are connected by $ n-1 $ undirected air routes, and any two of them can reach each other by passing the routes. That means, the $ n $ floating islands form a tree.

One day, LuoTianyi wants to meet her friends: Chtholly, Nephren, William, .... Totally, she wants to meet $ k $ people. She doesn't know the exact positions of them, but she knows that they are in pairwise distinct islands. She define an island is good if and only if the sum of the distances $ ^{\dagger} $ from it to the islands with $ k $ people is the minimal among all the $ n $ islands.

Now, LuoTianyi wants to know that, if the $ k $ people are randomly set in $ k $ distinct of the $ n $ islands, then what is the expect number of the good islands? You just need to tell her the expect number modulo $ 10^9+7 $ .

 $ ^{\dagger} $ The distance between two islands is the minimum number of air routes you need to take to get from one island to the other.

## 说明/提示

In the first example the air routes form the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/f98245759af7851bb13c350e387c9b296063f10a.png) If the people are in the islands $ 1 $ and $ 2 $ , then islands $ 1 $ and $ 2 $ will be good.

The sum of the distances from island $ 1 $ or $ 2 $ to all the people is $ 1+0=1 $ , which is the minimal. While the sum of the distances from island $ 3 $ to all the people is $ 2+1=3 $ , which is greater than $ 1 $ .

Like this, when the people are in island $ 1 $ and $ 3 $ , then islands $ 1,2 $ and $ 3 $ will be good.

When the people are in islands $ 1 $ and $ 4 $ , then islands $ 1,2,3 $ and $ 4 $ will be good.

When the people are in islands $ 2 $ and $ 3 $ , then islands $ 2 $ and $ 3 $ will be good.

When the people are in islands $ 2 $ and $ 4 $ , then islands $ 2,3 $ and $ 4 $ will be good.

When the people are in islands $ 3 $ and $ 4 $ , then islands $ 3 $ and $ 4 $ will be good.

So the expect of the number of the good islands is $ \frac{16}{6} $ , which equals to $ 666666674 $ modulo $ 10^9+7 $ .

In the second example the air routes form the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/2f411e079090512cd14c27f9186226921a07c282.png)We can see that there is one person in each island, and only the island $ 3 $ is good. So the expect number is $ 1 $ .

## 样例 #1

### 输入

```
4 2
1 2
2 3
3 4```

### 输出

```
666666674```

## 样例 #2

### 输入

```
5 5
1 2
2 3
3 4
3 5```

### 输出

```
1```

# AI分析结果


# 💡 Kay的C++算法解析：LuoTianyi and the Floating Islands (Hard Version) 深入学习指南 💡

> 欢迎来到树形算法世界！今天我们将探索树上期望问题的精妙解法，用组合数学和树形DFS解决难题。准备好开启像素风格的算法冒险了吗？

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`树形DFS` + `组合数学`（概率期望）

🗣️ **初步分析**：
> 想象一棵漂浮岛屿组成的树🌴，随机放置k个人后，寻找"好岛屿"（到所有人距离和最小的岛屿）。解题关键在于**树的结构特性**：
> - 当k为奇数时，好岛屿唯一（重心性质）
> - 当k为偶数时，好岛屿构成连通块，且**好边数量=好点数量-1**
>
> **核心流程**：
> 1. 特判k为奇数 → 直接返回1
> 2. k为偶数时DFS遍历树 → 计算子树大小
> 3. 枚举每条边 → 组合数计算贡献
> 4. 期望 = 边贡献和/总方案数 + 1
>
> **像素可视化设计**：
> 采用**8位像素风格**展示树结构，高亮当前遍历的边：
> - 边两侧显示子树大小
> - 满足条件（两侧各k/2人）时播放"叮！"音效
> - 进度条显示DFS进度，控制面板支持单步调试

---

## 2. 精选优质题解参考

<eval_intro>
综合代码简洁性、思路清晰度和实现效率，精选3份优质题解：

**题解一：Reunite（思路最简洁）**
* **点评**：从简单情况推广的思维流畅自然，代码结构清晰（DFS+组合数计算一气呵成）。亮点在于：
  - 严格证明k为奇数时答案=1
  - 组合数公式推导严谨（$C_{sz}^{k/2}×C_{n-sz}^{k/2}$）
  - 边界处理完整（避免无效计算）
  - 代码可直接用于竞赛（30行核心逻辑）

**题解二：Register_int（实现最规范）**
* **点评**：工业级代码规范，模块化设计优秀：
  - 独立组合数预处理函数
  - 严格的内存控制（vector存图）
  - 时间复杂度O(n)最优
  - 变量命名清晰（sz/total等）
  - 调试友好（无全局依赖）

**题解三：Un1quAIoid（思路最独特）**
* **点评**：提供全新视角（枚举点+容斥原理）：
  - 拓展思维（不同解法对比）
  - 完整推导$f_{x+1}-f_x$差分优化
  - 适用性广（可处理点权扩展）
  - 代码稍复杂但教学价值高

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
攻克本题需突破三大难点：

1.  **好点与好边的转化**  
    * **分析**：树结构中点与边存在拓扑关系（$点数=边数+1$）。优质题解通过证明：
      - 好点构成连通块 → 转化为好边计数
      - 好边定义：断开后两侧各有$k/2$人
    * 💡 **学习笔记**：树问题中，点边关系转化是突破口

2.  **组合数公式推导**  
    * **分析**：每条边的贡献是$C_{sz}^{k/2}×C_{n-sz}^{k/2}$，需理解：
      - $sz$：子树大小（DFS预处理）
      - 分子：当前边满足条件的方案数
      - 分母：总方案数$C_n^k$
    * 💡 **学习笔记**：概率期望=方案数/总方案数

3.  **树形DFS实现**  
    * **分析**：必须高效计算子树大小：
      - 递归时传递父节点避免回环
      - $sz[u] =1 + \sum sz[v]$
      - 回溯时累加贡献
    * 💡 **学习笔记**：DFS是树问题的基础工具

### ✨ 解题技巧总结
<summary_best_practices>
通用解题框架：
- **技巧1 问题转化**：将复杂期望转化为方案数统计
- **技巧2 树形处理**：DFS预处理子树信息
- **技巧3 组合优化**：预处理阶乘和逆元加速组合数
- **技巧4 边界特判**：优先处理特殊情形（如k奇数）

---

## 4. C++核心代码实现赏析

<code_intro_overall>
**通用核心实现**（综合优质题解优化版）：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+10;
const int mod = 1e9+7;

ll fac[N], inv[N];
vector<int> g[N];
int n, k, sz[N];
ll ans;

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void init() { // 组合数预处理
    fac[0] = 1;
    for (int i=1; i<N; i++) fac[i] = fac[i-1]*i%mod;
    inv[N-1] = qpow(fac[N-1], mod-2);
    for (int i=N-2; ~i; i--) inv[i] = inv[i+1]*(i+1)%mod;
}

ll C(int n, int m) { // 组合数计算
    return (n<0||m<0||n<m)?0:fac[n]*inv[m]%mod*inv[n-m]%mod;
}

void dfs(int u, int fa) { // 树形DFS
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (k%2 == 0) // 累加边贡献
            ans = (ans + C(sz[v],k/2)*C(n-sz[v],k/2)) % mod;
    }
}

int main() {
    init();
    cin >> n >> k;
    if (k & 1) { cout << 1; return 0; } // 特判奇数
    
    for (int i=1; i<n; i++) { // 建图
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    ll total = C(n, k); // 总方案数
    ans = (ans * qpow(total, mod-2) % mod + 1) % mod;
    cout << ans;
}
```

<code_intro_selected>
**题解片段赏析**：

**题解一：Reunite**
```cpp
void dfs(int u, int f) {
    s[u] = 1;
    for (int v : g[u]) {
        if (v == f) continue;
        dfs(v, u);
        s[u] += s[v]; // 累加子树大小
        // 核心：组合数计算边贡献
        ans = (ans + C(s[v], k/2) * C(n-s[v], k/2)) % mod;
    }
}
```
> **代码解读**：  
> - DFS递归计算子树大小（`s[u]`初始为1）
> - 回溯时累加每条边的组合数贡献
> - 简洁明了体现"好边"判定条件

**题解二：Register_int**
```cpp
// 组合数预处理（工业级规范）
void init() {
    fac[0] = 1;
    for (int i=1; i<=n; i++) fac[i] = fac[i-1]*i%mod;
    inv[n] = qpow(fac[n], mod-2);
    for (int i=n-1; i>=0; i--) 
        inv[i] = inv[i+1]*(i+1)%mod;
}
```
> **代码解读**：  
> - 预处理阶乘数组（`fac[0..n]`）
> - 逆元递推优化（$O(n)$计算）
> - 避免重复计算（竞赛最佳实践）

**题解三：Un1quAIoid**
```cpp
// 容斥解法核心差分
f[x] = Σ_{i=k/2+1}^k C(x,i)C(n-x,k-i) 
f[x+1]-f[x] = C(x, k/2)C(n-x-1, k-k/2-1)
```
> **代码解读**：  
> - 提供全新视角（点贡献容斥）
> - 差分优化避免重复计算
> - 拓展性强（支持动态修改）

-----

## 5. 算法可视化：像素动画演示

<visualization_intro>
**像素探险指南**：  
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/12896184a3f823fcd8518f46dc5b68823c932f0f.png)  
设计8-bit风格动画，直观展示算法执行：

* **主题**：像素岛屿探险  
* **核心演示**：树形DFS + 好边判定

1. **场景初始化**  
   - 像素化树结构（FC游戏风格）
   - 控制面板：开始/暂停/单步/速度滑块
   - 8-bit背景音乐循环

2. **DFS遍历演示**  
   ```mermaid
   graph LR
   A[启动DFS] --> B[选择根节点]
   B --> C{遍历子节点}
   C -->|是| D[计算子树大小]
   C -->|否| E[回溯累加贡献]
   E --> F[高亮当前边]
   ```
   - 当前节点闪烁（金色边框）
   - 子树大小动态显示（像素数字）

3. **好边判定动画**  
   - 条件检测：`sz[v] == k/2 && n-sz[v] == k/2`
   - 满足条件：  
     * 边变绿色
     * 播放"叮！"音效
     * 显示组合数公式
   - 不满足：  
     * 边变红色
     * 播放"噗"音效

4. **结果展示**  
   - 成功：显示期望值 + 胜利音效
   - 失败：显示错误路径

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握核心思路后，挑战同类问题：

1. **洛谷 P1395** - 会议（树的重心）  
   🗣️ *推荐理由*：巩固树的重心性质，本题的简化版

2. **洛吉 P1352** - 没有上司的舞会  
   🗣️ *推荐理由*：树形DP基础，理解状态转移

3. **洛谷 P1040** - 加分二叉树  
   🗣️ *推荐理由*：树形DP+组合数学综合应用

---

## 7. 学习心得与经验分享

<insights_intro>
作者调试经验摘录：

> **Reunite**：  
> *"在组合数边界处理栽跟头，切记检查$C(n,m)$中$n≥m≥0$"*

> **Register_int**：  
> *"逆元预处理写错导致WA#3，推荐模数检测工具"*

> **Kay的总结**：  
> 树问题注意三点：  
> 1. DFS防回环（记录父节点）  
> 2. 组合数防越界  
> 3. 模运算一致性检查  

---

<conclusion>
> 树形问题就像探险地图🗺️，掌握DFS和组合数学两把钥匙，就能打开期望计算的大门！下次遇到树上期望问题，记得：
> 1. 分析奇偶性  
> 2. 找好边关系  
> 3. DFS+组合数  
> 勇敢挑战更多树形问题吧！🚀

---
处理用时：236.09秒