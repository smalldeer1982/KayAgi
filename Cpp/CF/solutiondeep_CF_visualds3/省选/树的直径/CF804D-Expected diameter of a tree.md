# 题目信息

# Expected diameter of a tree

## 题目描述

Pasha is a good student and one of MoJaK's best friends. He always have a problem to think about. Today they had a talk about the following problem.

We have a forest (acyclic undirected graph) with $ n $ vertices and $ m $ edges. There are $ q $ queries we should answer. In each query two vertices $ v $ and $ u $ are given. Let $ V $ be the set of vertices in the connected component of the graph that contains $ v $ , and $ U $ be the set of vertices in the connected component of the graph that contains $ u $ . Let's add an edge between some vertex ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/8ef01bdc02f37e886781700f62479c92154da008.png) and some vertex in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/0479fe8afb5e9211cdac4c2d711ca0b8e2ad6e82.png) and compute the value $ d $ of the resulting component. If the resulting component is a tree, the value $ d $ is the diameter of the component, and it is equal to -1 otherwise. What is the expected value of $ d $ , if we choose vertices $ a $ and $ b $ from the sets uniformly at random?

Can you help Pasha to solve this problem?

The diameter of the component is the maximum distance among some pair of vertices in the component. The distance between two vertices is the minimum number of edges on some path between the two vertices.

Note that queries don't add edges to the initial forest.

## 说明/提示

In the first example the vertices $ 1 $ and $ 3 $ are in the same component, so the answer for the first query is -1. For the second query there are two options to add the edge: one option is to add the edge $ 1-2 $ , the other one is $ 2-3 $ . In both ways the resulting diameter is $ 2 $ , so the answer is $ 2 $ .

In the second example the answer for the first query is obviously -1. The answer for the second query is the average of three cases: for added edges $ 1-2 $ or $ 1-3 $ the diameter is $ 3 $ , and for added edge $ 1-4 $ the diameter is $ 2 $ . Thus, the answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/80f05d9f9a5abbad800eeb11e2f309500aaccabe.png).

## 样例 #1

### 输入

```
3 1 2
1 3
3 1
2 3
```

### 输出

```
-1
2.0000000000
```

## 样例 #2

### 输入

```
5 2 3
2 4
4 3
4 2
4 1
2 5
```

### 输出

```
-1
2.6666666667
2.6666666667
```

# AI分析结果

# 💡 Kay的C++算法解析：Expected diameter of a tree 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：图论（树的直径与偏心距计算） + 编程技巧应用（前缀和、二分查找、根号分治）

🗣️ **初步分析**：  
你可以把树想象成“由绳子连起来的珠子”，**树的直径**就是珠子串里最长的那根“绳子”（两个端点间的最长路径）。而**偏心距**是每个珠子到这根最长绳子两端的最远距离——就像每个珠子到绳子两头的“最远距离”。当我们把两棵树用一根新绳子（连边）连起来时，新树的最长绳子（直径）要么是原来两棵树的最长绳子，要么是“第一棵树的某个珠子的偏心距 + 第二棵树的某个珠子的偏心距 + 新绳子的长度1”。  

解决本题的关键步骤是：  
1. **预处理每棵树**：用两次BFS/DFS找到树的直径端点，再计算每个点的偏心距（到两端点的最远距离）；  
2. **优化查询**：将每棵树的偏心距排序并预处理前缀和，查询时枚举节点数少的树（小树），用二分查找快速计算大树中满足条件的节点数和距离和，避免暴力枚举所有点对；  
3. **根号分治**：将树按大小分为“小树”（≤√n）和“大树”（>√n），小树暴力枚举，大树预处理配对结果，减少重复计算。  

**可视化设计思路**：  
我们用8位像素风模拟树的结构（用不同颜色像素块表示节点、直径端点、偏心距）：  
- **直径计算**：用“像素蚂蚁”从任意点出发，BFS遍历找到最远端点（第一次BFS），再从该端点出发找到另一端点（第二次BFS），动画展示“蚂蚁”逐层扩展，高亮直径路径；  
- **偏心距计算**：用“彩色光线”从直径两端点出发，照亮每个节点的距离，取最大值作为偏心距，像素块颜色深浅表示距离大小；  
- **查询处理**：用“像素指针”枚举小树的每个节点，在大树的偏心距排序数组中二分查找，高亮符合条件的节点范围，伴随“叮”的音效表示找到匹配。  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解，帮你快速抓住核心！
</eval_intro>

**题解一：Graphcity（赞：14）**  
* **点评**：这份题解的思路像“搭积木”一样清晰——先点明期望的本质是“总直径和除以点对数”，再用两次DFS找直径和偏心距，预处理每个树的偏心距前缀和。查询时枚举小树，用前缀和快速计算大树的贡献，还用到了map记忆化避免重复计算。时间复杂度分析（O(n√n)）很透彻，代码中的变量命名（如`mx`表示偏心距、`cnt`表示前缀计数）也很易懂，是一份“知行合一”的好题解。

**题解二：violin_wyl（赞：5）**  
* **点评**：此题解用“换根DP”计算偏心距，比BFS更灵活！它把树按大小根号分治，小树暴力枚举，大树预处理配对结果，避免了重复计算。代码中的`vec`数组存每个树的偏心距（已排序），`sum`数组存前缀和，查询时用二分查找快速定位，逻辑严谨。唯一的小遗憾是换根DP的代码有点抽象，但注释到位，适合进阶学习。

**题解三：i207M（赞：3）**  
* **点评**：这份题解用BFS求直径和偏心距，代码像“流水线”一样流畅——先BFS找直径端点，再BFS计算每个点到两端点的距离（偏心距），预处理前缀和。查询时枚举小树，用二分查找大树的前缀和数组，计算贡献。代码中的`hv`数组存每个树的节点，`sumlen`数组存偏心距前缀和，逻辑简单直接，适合初学者理解“预处理+查询优化”的思路。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的“拦路虎”主要有三个，我们逐个击破！
</difficulty_intro>

### 1. 如何快速计算新树的直径？  
**难点**：连接两棵树后，新直径可能是原直径，也可能是“第一棵树的某个点的偏心距 + 第二棵树的某个点的偏心距 + 1”，直接枚举所有点对会超时。  
**解决策略**：利用树的性质——**一个点的最远距离一定是到直径端点的距离**，所以每个点的偏心距等于到直径两端点的最远距离。新直径的公式就变成`max(原直径1, 原直径2, 偏心距a + 偏心距b + 1)`，不用再计算所有点对的距离！  

### 2. 如何高效处理大量查询？  
**难点**：如果每次查询都枚举两棵树的所有点对（O(siz1*siz2)），当siz1和siz2很大时会超时。  
**解决策略**：  
- **预处理排序+前缀和**：将每棵树的偏心距排序，计算前缀和（如`sum`数组存前k个偏心距的和，`cnt`数组存前k个偏心距的个数）；  
- **枚举小树**：查询时选择节点数少的树（小树），枚举每个点的偏心距`e_a`，用二分查找大树中满足`e_a + e_b + 1 < max_d`的节点数（`max_d`是原直径的最大值），这部分贡献`max_d * 个数`；剩下的节点贡献`e_a + e_b + 1`，用前缀和快速计算总和。  

### 3. 如何优化重复查询？  
**难点**：如果多次查询同一对树，重复计算会浪费时间。  
**解决策略**：  
- **记忆化**：用map存储已经计算过的树对答案，下次直接取用；  
- **根号分治**：将树按大小分为“小树”（≤√n）和“大树”（>√n）。小树和任意树查询时，暴力枚举小树的点；大树之间的查询，预处理所有配对结果（因为大树数量最多√n个，配对数是O(√n²)=O(n)）。  

💡 **学习笔记**：预处理和优化的核心是“用空间换时间”——提前计算好常用的结果，查询时直接取用，避免重复劳动！


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个通用的核心实现，帮你把握整体框架！
</code_intro_overall>

### 本题通用核心C++实现参考  
* **说明**：综合优质题解的思路，用BFS求直径和偏心距，预处理前缀和，查询时枚举小树+二分查找。  
* **完整核心代码**：  
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

const int MAXN = 2e5 + 5;
vector<int> adj[MAXN]; // 树的邻接表
int bel[MAXN], cnt_tree; // bel[i]表示i所属的树编号，cnt_tree是树的总数
int diam[MAXN]; // 每棵树的直径
vector<int> e[MAXN]; // 每棵树的偏心距数组
vector<long long> sum_e[MAXN]; // 偏心距的前缀和
vector<int> cnt_e[MAXN]; // 偏心距的前缀计数
int siz[MAXN]; // 每棵树的节点数

// BFS找最远点，返回(最远点编号, 最远距离)
pair<int, int> bfs(int start, int tree_id) {
    vector<int> dist(MAXN, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int far_node = start, max_dist = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (bel[v] == tree_id && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > max_dist) {
                    max_dist = dist[v];
                    far_node = v;
                }
            }
        }
    }
    return {far_node, max_dist};
}

// 预处理每棵树的直径、偏心距、前缀和
void preprocess(int tree_id) {
    // 第一次BFS找第一个端点
    int u = -1;
    for (int i = 1; i < MAXN; ++i) {
        if (bel[i] == tree_id) {
            u = i;
            break;
        }
    }
    auto [p, _] = bfs(u, tree_id);
    // 第二次BFS找第二个端点和直径
    auto [q, d] = bfs(p, tree_id);
    diam[tree_id] = d;
    // 计算每个点到p和q的距离，取最大值作为偏心距
    vector<int> dist_p(MAXN, -1), dist_q(MAXN, -1);
    queue<int> q_p, q_q;
    q_p.push(p); dist_p[p] = 0;
    q_q.push(q); dist_q[q] = 0;
    while (!q_p.empty()) {
        int u = q_p.front(); q_p.pop();
        for (int v : adj[u]) {
            if (bel[v] == tree_id && dist_p[v] == -1) {
                dist_p[v] = dist_p[u] + 1;
                q_p.push(v);
            }
        }
    }
    while (!q_q.empty()) {
        int u = q_q.front(); q_q.pop();
        for (int v : adj[u]) {
            if (bel[v] == tree_id && dist_q[v] == -1) {
                dist_q[v] = dist_q[u] + 1;
                q_q.push(v);
            }
        }
    }
    // 收集偏心距
    for (int i = 1; i < MAXN; ++i) {
        if (bel[i] == tree_id) {
            e[tree_id].push_back(max(dist_p[i], dist_q[i]));
        }
    }
    siz[tree_id] = e[tree_id].size();
    // 排序并计算前缀和
    sort(e[tree_id].begin(), e[tree_id].end());
    sum_e[tree_id].resize(siz[tree_id] + 1, 0);
    cnt_e[tree_id].resize(siz[tree_id] + 1, 0);
    for (int i = 0; i < siz[tree_id]; ++i) {
        sum_e[tree_id][i+1] = sum_e[tree_id][i] + e[tree_id][i];
        cnt_e[tree_id][i+1] = cnt_e[tree_id][i] + 1;
    }
}

map<pair<int, int>, double> memo;

double query(int tree_a, int tree_b) {
    if (tree_a == tree_b) return -1.0;
    if (memo.count({tree_a, tree_b})) return memo[{tree_a, tree_b}];
    if (siz[tree_a] > siz[tree_b]) swap(tree_a, tree_b);
    long long total = 0;
    int max_d = max(diam[tree_a], diam[tree_b]);
    for (int ea : e[tree_a]) {
        // 找大树中满足 ea + eb + 1 < max_d 的eb的数量
        int target = max_d - ea - 1;
        // 二分查找第一个大于target的位置
        auto it = upper_bound(e[tree_b].begin(), e[tree_b].end(), target);
        int k = it - e[tree_b].begin();
        // 前k个贡献max_d * k
        total += (long long)max_d * k;
        // 剩下的贡献 ea + eb + 1，即 (ea+1)*(siz_b -k) + sum(eb from k to end)
        total += (long long)(ea + 1) * (siz[tree_b] - k);
        total += sum_e[tree_b][siz[tree_b]] - sum_e[tree_b][k];
    }
    double ans = (double)total / (siz[tree_a] * 1.0 * siz[tree_b]);
    memo[{tree_a, tree_b}] = ans;
    memo[{tree_b, tree_a}] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // 给每个节点分配树编号
    cnt_tree = 0;
    fill(bel, bel + MAXN, 0);
    for (int i = 1; i <= n; ++i) {
        if (!bel[i]) {
            cnt_tree++;
            queue<int> q;
            q.push(i);
            bel[i] = cnt_tree;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (!bel[v]) {
                        bel[v] = cnt_tree;
                        q.push(v);
                    }
                }
            }
        }
    }
    // 预处理每棵树
    for (int i = 1; i <= cnt_tree; ++i) {
        preprocess(i);
    }
    // 处理查询
    while (q--) {
        int u, v;
        cin >> u >> v;
        int tree_u = bel[u], tree_v = bel[v];
        if (tree_u == tree_v) {
            cout << "-1\n";
        } else {
            double ans = query(tree_u, tree_v);
            cout.precision(10);
            cout << ans << '\n';
        }
    }
    return 0;
}
```
* **代码解读概要**：  
  1. **输入处理**：读取树的边，用BFS给每个节点分配树编号；  
  2. **预处理**：对每棵树用两次BFS找直径端点，计算每个点的偏心距，排序并计算前缀和；  
  3. **查询处理**：枚举小树的每个偏心距，用二分查找大树的前缀和数组，计算总贡献，返回期望。  


<code_intro_selected>
再看优质题解的核心片段，学习它们的亮点！
</code_intro_selected>

### 题解一：Graphcity（来源：综合题解内容）  
* **亮点**：用记忆化和前缀和优化查询，时间复杂度分析透彻。  
* **核心代码片段**：  
```cpp
inline double Solve(int x,int y) {
    int dx=max(ans[x],ans[y]); ll s1=1ll*siz[x]*siz[y],s2=0;
    for(auto i:w[x]) if(dx-mx[i]<=siz[y]) {
        if(!(dx-mx[i])) {
            s1-=cnt[y][siz[y]],s2+=sum[y][siz[y]];
            s2+=1ll*mx[i]*cnt[y][siz[y]];
        } else {
            ll a=cnt[y][siz[y]]-cnt[y][dx-mx[i]-1];
            ll b=sum[y][siz[y]]-sum[y][dx-mx[i]-1];
            s1-=a,s2+=b+a*mx[i];
        }
    }
    ll res=s1*dx+s2; return 1.0*res/(1ll*siz[x]*siz[y]);
}
```
* **代码解读**：  
  这段代码是查询的核心逻辑。`dx`是原直径的最大值，`w[x]`是x树的所有节点，`mx[i]`是节点i的偏心距。循环枚举x树的每个节点，计算`dx - mx[i]`（即大树中满足`mx[i] + mx[j] +1 < dx`的`mx[j]`的上限）。用前缀和数组`cnt`（计数）和`sum`（和）快速计算符合条件的节点数和距离和，最后计算总贡献`res = s1*dx + s2`（s1是不影响直径的节点对数，s2是影响直径的节点对的距离和）。  
* **学习笔记**：前缀和是处理区间查询的“神器”，能把O(k)的查询变成O(1)！


## 5. 算法可视化：像素动画演示

### 动画主题：像素树的“直径探索之旅”  
**设计思路**：用8位FC游戏风格模拟树的直径计算和查询过程，结合音效和交互，让学习更有趣！


### 核心演示内容  
1. **场景初始化**：  
   - 屏幕左侧是**树的像素地图**：用绿色像素块表示普通节点，红色表示直径端点，蓝色表示当前查询的节点；  
   - 屏幕右侧是**控制面板**：有“开始/暂停”“单步执行”“重置”按钮，速度滑块（1x~5x），以及“算法说明”文字框；  
   - 背景播放轻松的8位BGM（如《超级马里奥》的背景音乐）。  

2. **直径计算动画**：  
   - **第一次BFS**：从任意绿色节点出发，用“黄色蚂蚁”像素块逐层扩展，每个被访问的节点变成浅黄色，找到最远端点（变成红色）；  
   - **第二次BFS**：从红色端点出发，“黄色蚂蚁”再次扩展，找到另一端点（也变成红色），红色节点之间的路径用红色虚线连接（表示直径）；  
   - **偏心距计算**：从两个红色端点出发，用“蓝色光线”和“紫色光线”照亮每个节点，颜色深浅表示距离（越深距离越远），每个节点的颜色取两种光线的最深颜色（表示偏心距）。  

3. **查询处理动画**：  
   - **选择树对**：用户点击两个不同的树（用不同颜色框住），屏幕显示“查询开始”；  
   - **枚举小树**：小树的节点逐个闪烁（蓝色），每个节点的偏心距显示在旁边；  
   - **二分查找**：大树的偏心距数组用像素块排列（从左到右从小到大），用“红色指针”找到第一个大于`dx - mx[i] -1`的位置，指针移动时伴随“叮”的音效；  
   - **结果展示**：总贡献用数字动画从0增长到最终值，期望结果显示在屏幕中央，伴随“胜利”音效（如《魂斗罗》的通关音效）。  


### 交互与控制  
- **步进控制**：点击“单步”按钮，动画执行一步（如BFS的一层扩展、查询的一个节点枚举）；  
- **自动播放**：拖动速度滑块调整播放速度（1x最慢，5x最快）；  
- **重置动画**：点击“重置”按钮，回到初始状态，重新开始演示。  


## 6. 拓展练习与相似问题思考

### 通用思路迁移  
本题的核心思路（树的直径计算、偏心距预处理、前缀和+二分优化查询）可以迁移到以下场景：  
1. **连接多棵树的直径**：比如连接k棵树，求新树的直径期望；  
2. **树的重心与直径结合**：比如求树的重心，再计算重心的偏心距；  
3. **动态树的直径**：比如动态加边/删边，维护树的直径（需要更高级的数据结构，如Link-Cut Tree）。  


### 洛谷拓展练习推荐  
1. **洛谷 P1099 树网的核**（P1099）  
   - 🗣️ 推荐理由：这道题需要计算树网的核（直径上的一段路径），进一步巩固树的直径计算和路径查询的技巧。  
2. **洛谷 P2053 [SCOI2007] 修车**（P2053）  
   - 🗣️ 推荐理由：虽然是贪心题，但需要用前缀和优化计算，锻炼“用空间换时间”的思维。  
3. **洛谷 P3398 树的重心**（P3398）  
   - 🗣️ 推荐理由：树的重心是树的重要性质，与直径结合可以解决更多树的问题，比如求树的最小最大距离。  


## 7. 学习心得与经验分享 (若有)

> **参考经验 (来自 Graphcity)**：“我在解决这个问题时，最初在计算`mx_a + mx_b +1`的贡献时卡了很久，后来想到用前缀和预处理，把每个树的偏心距排序，用二分查找快速计算符合条件的节点数，才解决了超时问题。这让我意识到，预处理和排序是处理大规模数据的关键！”  
> **点评**：这位作者的经验很实用——当直接计算所有情况超时的时候，不妨想想“能不能把数据排序，用前缀和或二分来优化”？很多时候，排序+前缀和能把O(n)的查询变成O(log n)！


## 结语  
本次关于“Expected diameter of a tree”的分析就到这里啦！希望这份指南能帮你掌握树的直径计算、偏心距预处理，以及前缀和、二分、根号分治的技巧。记住：**编程的乐趣在于“解决问题”，而解决问题的关键是“找对方法”**——先想清楚思路，再写代码，才能事半功倍！下次我们再一起探索更有趣的算法问题吧！💪

---
处理用时：116.06秒