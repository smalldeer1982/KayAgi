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

✨ **本题主要考察**：图论（树的直径） + 根号分治 + 前缀和/二分查找

🗣️ **初步分析**：  
解决这道题的关键，在于**树的直径性质**和**高效查询优化**的结合。我们先拆解核心概念：  
- **树的直径**：树中最长的路径（比如一棵链式树的直径就是两端点的距离）。找直径有个“魔法”：随便选一个点做BFS/DFS找到最远点`u`，再从`u`做BFS/DFS找到最远点`v`，`u-v`就是直径！而且，**树中任意点的最远距离，一定是到直径两端点`u`或`v`的距离的最大值**——这个性质是解题的核心！  
- **期望计算的转化**：题目要求“随机连边后的直径期望”，其实等价于“所有连边方式的直径总和 ÷ 总连边数（`siz_x × siz_y`）”。而新树的直径是`max(原树1直径, 原树2直径, 点a的最远距离 + 点b的最远距离 + 1)`（`a`来自树1，`b`来自树2）。  
- **高效查询的关键**：直接枚举所有点对会超时（`O(n²)`），所以用**根号分治**优化——把树分成“小树”（大小≤√n）和“大树”（大小>√n）：  
  - 小树和任意树查询：枚举小树的所有点，用**前缀和+二分**快速计算大树的贡献（比如找哪些点`b`满足`a的最远距离 + b的最远距离 +1 ≥ max(原直径)`）。  
  - 大树之间的查询：由于大树数量不超过√n，预处理所有大树对的结果，用`map`记忆化避免重复计算。  

**可视化设计思路**：我们用“像素树探险家”的复古游戏风格，展示三个核心步骤：  
1. **找直径**：用像素块代表节点，BFS过程用“小探险家”一步步扩散，找到直径两端点时播放“叮”的音效，直径用金色像素块高亮。  
2. **算最远距离**：每个节点的最远距离用不同颜色深度表示（越深越远），鼠标 hover 时显示具体数值。  
3. **查询计算**：连接两棵树时，小树的点用“红色探险家”枚举，大树的前缀和数组用条形图展示，二分查找的位置用箭头标记，贡献计算时播放“刷刷”的音效。  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等角度筛选了以下优质题解，帮你快速掌握核心逻辑：
</eval_intro>

**题解一：Graphcity（赞14）**  
* **点评**：这份题解是本题的“标准解法模板”，思路极其清晰！作者先用量化的方式拆解问题（期望=总贡献÷总次数），再利用树的直径性质将“每个点的最远距离”转化为“到直径两端点的最大值”，避免了复杂的换根DP。代码中，**并查集处理连通块**、**两次DFS找直径**、**前缀和预处理**、**根号分治枚举小树**的步骤环环相扣，尤其是对时间复杂度的分析（`O(n√n)`）非常透彻，能帮你理解“为什么这样优化不会超时”。另外，`map`记忆化查询结果的技巧，也能有效避免重复计算，实践价值极高。

**题解二：violin_wyl（赞5）**  
* **点评**：这道题的“细节狂魔”解法！作者用**换根DP**求每个点的最远距离（避免了第三次BFS），虽然代码稍长，但逻辑更严谨。尤其是对“大树对”的预处理（枚举每棵大树，再枚举其所有点，用二分找另一棵大树的贡献），把根号分治的思想落地得非常彻底。代码中的`vec`数组存储每个点的最远距离并排序，`sum`数组存前缀和，这些细节都体现了作者对“高效计算”的深刻理解。唯一的小缺点是变量名稍显抽象（比如`Dim`、`bcnt`），但注释补充后不影响阅读。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的“拦路虎”主要有三个，我们逐一拆解：
</difficulty_intro>

1. **难点1：如何利用树的直径性质求每个点的最远距离？**  
   * **分析**：树的直径有个“万能”性质——任意点的最远距离，一定是到直径两端点的最大值。比如，假设直径是`u-v`，点`a`到`u`的距离是`3`，到`v`的距离是`5`，那么`a`的最远距离就是`5`。这样，我们只需要做**两次BFS/DFS**：第一次找`u`，第二次找`v`并记录所有点到`u`的距离，第三次（可选）记录到`v`的距离，取最大值即可。  
   * 💡 **学习笔记**：树的直径是处理“树中最远点”问题的“钥匙”，记住这个性质能省很多事！

2. **难点2：如何高效计算所有连边方式的直径总和？**  
   * **分析**：直接枚举所有点对会超时，所以要**拆分贡献**：总贡献=“原直径更大的情况”的贡献 + “新直径更大的情况”的贡献。比如，设`max_d = max(树1直径, 树2直径)`，对于点`a`（树1），我们需要找树2中所有点`b`：  
     - 若`a的最远距离 + b的最远距离 +1 < max_d`：贡献是`max_d`（新直径还是原直径）。  
     - 否则：贡献是`a的最远距离 + b的最远距离 +1`（新直径由连边决定）。  
   用**前缀和+二分**可以快速统计这两部分的数量和总和（比如排序后，二分找`b的最远距离 ≤ max_d - a的最远距离 -1`的位置）。  
   * 💡 **学习笔记**：把“求总和”拆成“符合条件的部分之和”，是处理大规模数据的常用技巧！

3. **难点3：如何用根号分治优化查询时间？**  
   * **分析**：根号分治的核心是“分而治之”——把树分成“小树”（≤√n）和“大树”（>√n）：  
     - 小树和任意树：枚举小树的所有点（最多√n次），用二分查大树的贡献（`O(log n)`），总复杂度`O(√n log n)`。  
     - 大树之间：由于大树数量≤√n，预处理所有大树对的结果（`O(√n × √n) = O(n)`），之后查询直接取记忆化结果。  
   这样，总时间复杂度被降到`O(n√n)`，完全能处理`n=2e5`的规模。  
   * 💡 **学习笔记**：根号分治是“平衡时间复杂度”的神器，当直接枚举超时但数据能分成“大小两部分”时，优先考虑它！

### ✨ 解题技巧总结
- **性质优先**：遇到树的“最远点”问题，先想树的直径性质，避免冗余计算。  
- **贡献拆分**：把“总期望”转化为“总贡献÷总次数”，再拆成可快速计算的部分。  
- **分治优化**：用根号分治平衡枚举和查询的时间，用前缀和+二分加速统计。  


## 4. C++核心代码实现赏析

<code_intro_overall>
我们先看一份**综合优质题解的通用核心代码**，帮你建立整体框架：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Graphcity和violin_wyl的思路，保留了最核心的逻辑（并查集、找直径、前缀和、根号分治），结构更简洁。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;

vector<int> g[MAXN];
int fa[MAXN], siz[MAXN]; // 并查集：父节点、连通块大小
int bel[MAXN], cnt_tree; // 每个点所属的树编号、树的总数
int diam[MAXN]; // 每棵树的直径
vector<int> far[MAXN]; // 每棵树中所有点的最远距离
vector<ll> sum_far[MAXN]; // 每棵树far数组的前缀和
map<pair<int, int>, double> memo; // 记忆化查询结果

// 并查集查找
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

// BFS找最远点，返回最远点和距离数组
pair<int, vector<int>> bfs(int start, int tree_id) {
    vector<int> dis(MAXN, -1);
    vector<int> q;
    q.push_back(start);
    dis[start] = 0;
    int max_dis = 0, far_node = start;
    for (int i = 0; i < q.size(); i++) {
        int u = q[i];
        for (int v : g[u]) {
            if (bel[v] == tree_id && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push_back(v);
                if (dis[v] > max_dis) {
                    max_dis = dis[v];
                    far_node = v;
                }
            }
        }
    }
    return {far_node, dis};
}

// 预处理每棵树的直径和每个点的最远距离
void preprocess(int tree_id, int root) {
    // 第一次BFS找u
    auto [u, _] = bfs(root, tree_id);
    // 第二次BFS找v和直径
    auto [v, dis_u] = bfs(u, tree_id);
    diam[tree_id] = dis_u[v];
    // 第三次BFS找所有点到v的距离
    auto [_, dis_v] = bfs(v, tree_id);
    // 每个点的最远距离是max(dis_u[x], dis_v[x])
    for (int x = 1; x < MAXN; x++) {
        if (bel[x] == tree_id) {
            far[tree_id].push_back(max(dis_u[x], dis_v[x]));
        }
    }
    // 排序并计算前缀和
    sort(far[tree_id].begin(), far[tree_id].end());
    sum_far[tree_id].resize(far[tree_id].size() + 1, 0);
    for (int i = 0; i < far[tree_id].size(); i++) {
        sum_far[tree_id][i+1] = sum_far[tree_id][i] + far[tree_id][i];
    }
}

// 计算两棵树a和b的总贡献
ll calculate(int a, int b) {
    if (memo.count({a, b})) return memo[{a, b}] * siz[a] * siz[b]; // 先算总贡献
    ll max_d = max(diam[a], diam[b]);
    ll total = 0;
    // 枚举较小的树
    if (siz[a] > siz[b]) swap(a, b);
    for (int f_a : far[a]) {
        // 找b中满足f_b <= max_d - f_a -1的最大索引
        int l = 0, r = far[b].size() - 1;
        int pos = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (far[b][mid] <= max_d - f_a - 1) {
                pos = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        // 前pos+1个点贡献max_d，后面的贡献f_a + f_b +1
        total += (ll)(pos + 1) * max_d;
        total += (ll)(f_a + 1) * (far[b].size() - pos - 1);
        total += sum_far[b][far[b].size()] - sum_far[b][pos + 1];
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    // 初始化并查集
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        siz[i] = 1;
    }
    // 读入边
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            fa[fu] = fv;
            siz[fv] += siz[fu];
        }
    }
    // 分配树编号
    for (int i = 1; i <= n; i++) {
        if (find(i) == i) {
            cnt_tree++;
            bel[i] = cnt_tree;
            // BFS标记所有点的树编号
            vector<int> q_bfs;
            q_bfs.push_back(i);
            while (!q_bfs.empty()) {
                int u = q_bfs.back();
                q_bfs.pop_back();
                for (int v : g[u]) {
                    if (bel[v] == 0) {
                        bel[v] = cnt_tree;
                        q_bfs.push_back(v);
                    }
                }
            }
            // 预处理这棵树的直径和far数组
            preprocess(cnt_tree, i);
            siz[cnt_tree] = far[cnt_tree].size(); // 更新树的大小
        }
    }
    // 处理查询
    while (q--) {
        int u, v;
        cin >> u >> v;
        int a = bel[u], b = bel[v];
        if (a == b) {
            cout << "-1\n";
            continue;
        }
        if (a > b) swap(a, b); // 保证a <= b，避免重复记忆化
        if (!memo.count({a, b})) {
            ll total = calculate(a, b);
            memo[{a, b}] = (double)total / (siz[a] * siz[b]);
        }
        cout.precision(10);
        cout << memo[{a, b}] << '\n';
    }
    return 0;
}
```
* **代码解读概要**：  
  1. **并查集**：处理连通块，给每个点分配树编号。  
  2. **BFS找直径**：三次BFS分别找直径两端点`u`、`v`，并计算每个点到`u`、`v`的距离，取最大值得到`far`数组。  
  3. **前缀和预处理**：排序`far`数组并计算前缀和，方便后续二分查找。  
  4. **查询处理**：用`map`记忆化结果，枚举较小的树，用二分找另一棵树的贡献，计算总期望。


<code_intro_selected>
接下来，我们赏析两道优质题解的核心片段：
</code_intro_selected>

**题解一：Graphcity的“找直径+前缀和”片段**  
* **亮点**：用两次DFS找直径，代码更简洁（避免了BFS的队列操作）。
* **核心代码片段**：
```cpp
inline void dfs(int x, int f, int d) {
    mx[x] = max(mx[x], d), dis[x] = d;
    for (auto y : v[x]) if (y != f) dfs(y, x, d + 1);
}

// 预处理每棵树的直径和mx数组（mx[x]是x的最远距离）
For(i, 1, n) if (fa[i] == i) {
    int rt = 0; dfs(i, 0, 0);
    for (auto j : w[i]) if (dis[j] > dis[rt]) rt = j;
    dfs(rt, 0, 0);
    for (auto j : w[i]) if (dis[j] > dis[rt]) rt = j;
    dfs(rt, 0, 0);
    // 处理前缀和
    sum[i].resize(siz[i]+3), cnt[i].resize(siz[i]+3);
    for (auto j : w[i]) cnt[i][mx[j]]++, sum[i][mx[j]] += mx[j]+1, ans[i] = max(ans[i], mx[j]);
    For(j, 1, siz[i]) cnt[i][j] += cnt[i][j-1], sum[i][j] += sum[i][j-1];
}
```
* **代码解读**：  
  - `dfs`函数计算从`x`出发的距离，更新`mx[x]`（最远距离）和`dis[x]`（当前距离）。  
  - 三次`dfs`：第一次找`rt`（任意点的最远点），第二次找直径的另一端点，第三次计算所有点的最远距离。  
  - 前缀和`cnt`（统计每个最远距离的出现次数）和`sum`（统计每个最远距离的总和），方便后续快速查询。  
* 💡 **学习笔记**：DFS比BFS更省代码，但要注意栈溢出（本题`n`≤2e5，递归会栈溢出，实际应改用非递归DFS或BFS）！

**题解二：violin_wyl的“换根DP求最远距离”片段**  
* **亮点**：用换根DP避免第三次BFS，更高效。
* **核心代码片段**：
```cpp
void dfs (int u, int f, int b) {
    vis[u] = 1;
    siz[b]++; len[u] = 0;
    belong[u] = b;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].ver;
        if (v == f) continue;
        dfs (v, u, b);
        Dim = max (Dim, len[u] + len[v] + 1);
        if (len[v] + 1 >= len[u]) { len2[u] = len[u]; len[u] = len[v] + 1; son[u] = v; }
        else len2[u] = max (len2[u], len[v] + 1);
    }
}

void dfs2 (int u, int f, int l) {
    vis[u] = 1;
    if (son[u]) dfs2 (son[u], u, max (len2[u], l) + 1);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].ver;
        if (v != f && v != son[u])
            dfs2 (v, u, max (len[u], l) + 1);
    }
    len[u] = max (len[u], l);
    vec[belong[u]].pb (len[u]);
}
```
* **代码解读**：  
  - `dfs`（第一次DFS）：计算每个点的“向下最长距离”`len[u]`（从`u`到子树中的最远点）和“向下次长距离”`len2[u]`，同时找树的直径`Dim`。  
  - `dfs2`（换根DFS）：计算每个点的“向上最长距离”`l`（从`u`到父树中的最远点），最终`len[u] = max(向下最长, 向上最长)`，即点`u`的最远距离。  
* 💡 **学习笔记**：换根DP是处理“树中每个点的全局属性”的高效方法，比如最远距离、深度等，能把时间复杂度从`O(n)`降到`O(n)`（和BFS一样，但更省空间）！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地“看到”算法运行，我设计了一个**8位像素风格的“树直径探险家”游戏**，结合复古游戏元素，让学习更有趣！
</visualization_intro>

### **动画演示主题**：像素探险家找树的直径，计算连边后的期望直径
### **设计思路**：  
用FC红白机的8位像素风格（16色调色板），把树节点做成“方块人”，直径用“金色路径”标记，查询过程用“探险家枚举”+“条形图统计”展示。加入音效增强记忆：  
- 找直径时，BFS扩散播放“滴滴”声；找到直径两端点播放“叮”的胜利声。  
- 计算贡献时，二分查找播放“刷刷”声；统计完成播放“哗啦”声。  
- 背景音乐用《超级马里奥》的轻松BGM，增强复古氛围。

### **动画帧步骤与交互关键点**：
1. **场景初始化**：  
   - 屏幕左侧是“树视图”：节点是3x3的像素方块（不同颜色代表不同树），边是1x1的线条。  
   - 屏幕右侧是“控制面板”：有“开始”“单步”“重置”按钮，速度滑块（1x8像素），以及“算法说明”文字气泡。  
   - 背景音乐开始播放（8位风格的《小蜜蜂》BGM）。

2. **找直径演示**：  
   - 第一步：随机选一个节点（比如“方块人1号”），BFS扩散（节点变成浅蓝色），找到最远点`u`（变成红色），播放“叮”声。  
   - 第二步：从`u`出发BFS，找到最远点`v`（变成蓝色），`u-v`的路径变成金色（直径），播放“叮”声。  
   - 第三步：计算每个节点的最远距离（节点颜色深度变化：越深越远），鼠标 hover 时显示“最远距离：X”。

3. **查询计算演示**：  
   - 输入查询的两个点（比如树A的“方块人2号”和树B的“方块人3号”），屏幕显示两棵树的直径（金色路径）和大小。  
   - 枚举树A的所有点（红色探险家逐个移动），树B的`far`数组用条形图展示（高度代表最远距离）。  
   - 二分查找时，条形图上的箭头标记“分界点”（左边贡献原直径，右边贡献新直径），同时右侧面板显示“当前贡献：X”。  
   - 计算完成后，屏幕显示“总期望：X.XXXXXX”，播放“胜利”音效（上扬的8位音调）。

4. **交互设计**：  
   - **单步执行**：点击“单步”按钮，动画执行一步（比如BFS扩散一个节点，枚举一个点）。  
   - **自动播放**：拖动速度滑块调节速度（1x8像素，从慢到快），动画自动执行。  
   - **重置**：点击“重置”按钮，回到初始状态，重新选择树和查询。

<visualization_conclusion>
通过这个动画，你能清晰看到“找直径”“算最远距离”“查贡献”的每一步，甚至能通过音效和颜色变化“记住”关键逻辑。就像玩《超级马里奥》一样，在游戏中学会算法！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了本题的思路后，你可以尝试以下相似问题，巩固“树的直径”和“根号分治”的应用：
</similar_problems_intro>

### **通用思路迁移**：  
树的直径性质不仅能解决“连边后的直径期望”，还能解决：  
1. **树网的核**：找树中最长路径的“核”（中间部分）。  
2. **树上最远点对**：多次查询树中两点的最远点对。  
3. **树的中心**：找树中到所有点距离最小的点（中心一定在直径上）。

### **洛谷练习推荐**：
1. **洛谷 P1099 树网的核**  
   🗣️ **推荐理由**：这是树的直径的经典应用！需要找到直径上的“核”，使得核到所有点的最远距离最小。能帮你巩固“直径是树的最长路径”的性质。  
2. **洛谷 P2146 软件包管理器**  
   🗣️ **推荐理由**：虽然是“树链剖分”的题，但需要计算树的深度和子树大小，能帮你练习“树的遍历”和“动态维护树的属性”。  
3. **洛谷 P3398 仓鼠找 sugar**  
   🗣️ **推荐理由**：结合了LCA（最近公共祖先）和树的直径，需要判断两条路径是否相交。能帮你练习“树的路径查询”和“直径性质的灵活应用”。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
从题解中，我提炼了两个“踩坑经验”，帮你避免走弯路：
</insights_intro>

> **经验1**：Graphcity提到“递归DFS会栈溢出”——本题`n`≤2e5，递归深度可能达到2e5，远超C++默认的栈大小（约1MB），所以实际代码中**必须用非递归DFS或BFS**！  
> **点评**：这是很多初学者容易忽略的细节！写递归时一定要想“数据规模会不会导致栈溢出”，如果会，就改用迭代版。

> **经验2**：violin_wyl提到“前缀和数组的索引要注意”——比如`sum[i]`是前`i`个元素的和，所以`sum[b.size()] - sum[pos+1]`才是`pos+1`到`b.size()-1`的和。  
> **点评**：前缀和的索引错误是“高频bug”，写代码时一定要画个小例子验证（比如`sum[0]=0, sum[1]=a[0], sum[2]=a[0]+a[1]`）。


## 结语
本次分析覆盖了“树的直径”“根号分治”“前缀和+二分”三个核心知识点，希望能帮你理解“如何将理论性质转化为高效代码”。记住：**算法的本质是“解决问题的步骤”，而代码是“步骤的实现”**——先想清楚“怎么做”，再写“怎么实现”，就能少走很多弯路！

下次我们再一起探索更有趣的算法问题，比如“动态树的直径”或“树上的动态规划”，加油！💪

---
处理用时：156.00秒