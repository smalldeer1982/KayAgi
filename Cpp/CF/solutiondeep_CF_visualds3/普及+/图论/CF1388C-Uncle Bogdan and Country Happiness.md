# 题目信息

# Uncle Bogdan and Country Happiness

## 题目描述

Uncle Bogdan is in captain Flint's crew for a long time and sometimes gets nostalgic for his homeland. Today he told you how his country introduced a happiness index.

There are $ n $ cities and $ n−1 $ undirected roads connecting pairs of cities. Citizens of any city can reach any other city traveling by these roads. Cities are numbered from $ 1 $ to $ n $ and the city $ 1 $ is a capital. In other words, the country has a tree structure.

There are $ m $ citizens living in the country. A $ p_i $ people live in the $ i $ -th city but all of them are working in the capital. At evening all citizens return to their home cities using the shortest paths.

Every person has its own mood: somebody leaves his workplace in good mood but somebody are already in bad mood. Moreover any person can ruin his mood on the way to the hometown. If person is in bad mood he won't improve it.

Happiness detectors are installed in each city to monitor the happiness of each person who visits the city. The detector in the $ i $ -th city calculates a happiness index $ h_i $ as the number of people in good mood minus the number of people in bad mood. Let's say for the simplicity that mood of a person doesn't change inside the city.

Happiness detector is still in development, so there is a probability of a mistake in judging a person's happiness. One late evening, when all citizens successfully returned home, the government asked uncle Bogdan (the best programmer of the country) to check the correctness of the collected happiness indexes.

Uncle Bogdan successfully solved the problem. Can you do the same?

More formally, You need to check: "Is it possible that, after all people return home, for each city $ i $ the happiness index will be equal exactly to $ h_i $ ".

## 说明/提示

Let's look at the first test case of the first sample:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/001794ade043a3f0f7ed603305eb551246689207.png)At first, all citizens are in the capital. Let's describe one of possible scenarios:

- a person from city $ 1 $ : he lives in the capital and is in good mood;
- a person from city $ 4 $ : he visited cities $ 1 $ and $ 4 $ , his mood was ruined between cities $ 1 $ and $ 4 $ ;
- a person from city $ 3 $ : he visited cities $ 1 $ and $ 3 $ in good mood;
- a person from city $ 6 $ : he visited cities $ 1 $ , $ 3 $ and $ 6 $ , his mood was ruined between cities $ 1 $ and $ 3 $ ;

 In total, - $ h_1 = 4 - 0 =         4 $ ,
- $ h_2 = 0 $ ,
- $ h_3 = 1 - 1 = 0 $ ,
- $ h_4 = 0 - 1 = -1 $ ,
- $ h_5 = 0 $ ,
- $ h_6 = 0 - 1 = -1 $ ,
- $ h_7 = 0 $ .

The second case of the first test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/a9264c4828a85c9989a95ed8604e23cfb9f3dcda.png)All people have already started in bad mood in the capital — this is the only possible scenario.

The first case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/b8bbd8cbfa8f12355a17c596fd18bc65433a619c.png)The second case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/5c48a1551b8fe0dc0edc02bc5782fb0068b84587.png)It can be proven that there is no way to achieve given happiness indexes in both cases of the second test.

## 样例 #1

### 输入

```
2
7 4
1 0 1 1 0 1 0
4 0 0 -1 0 -1 0
1 2
1 3
1 4
3 5
3 6
3 7
5 11
1 2 5 2 1
-11 -2 -6 -2 -1
1 2
1 3
1 4
3 5```

### 输出

```
YES
YES```

## 样例 #2

### 输入

```
2
4 4
1 1 1 1
4 1 -3 -1
1 2
1 3
1 4
3 13
3 3 7
13 1 4
1 2
1 3```

### 输出

```
NO
NO```

# AI分析结果


# 💡 Kay的C++算法解析：Uncle Bogdan and Country Happiness 深入学习指南 💡

<introduction>
今天我们来一起分析"Uncle Bogdan and Country Happiness"这道C++编程题。这道题考察树形结构上的动态统计和条件验证，将帮助你掌握树形DFS遍历和状态验证的关键技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`树形动态规划/树形统计` 与 `条件验证`

🗣️ **初步分析**：
> 这道题就像在管理一个像素王国的交通网络🌳：首都（节点1）是所有公民工作的起点，他们通过树状道路回到家乡城市。关键是要验证每个城市的"幸福指数检测器"读数是否合理：
> - 公民心情只能由好变坏（像单行道）
> - 每个城市的检测值$h_i$ = 经过的好心情人数 - 坏心情人数
>
> 解题分两步：首先用**树形DFS统计**每个节点经过的总人数（类似统计王国各城镇人流量），然后用**条件验证**检查三个约束：
> 1. $|h_i| \leq$ 总人数（检测值不能超过实际人数）
> 2. (总人数 - $|h_i|$)为偶数（好/坏心情人数必须是整数）
> 3. 当前节点好心情人数 ≥ 所有子节点好心情人数之和（心情只能变坏不能变好）
>
> 在可视化方案中（像素王国模拟器👾）：
> - 树形结构用8-bit像素网格展示，节点用不同颜色方块表示
> - DFS遍历时：节点会发光，人数统计用像素方块堆叠动画
> - 验证失败时：节点闪烁红色+错误音效；成功时播放胜利音乐
> - 控制面板：步进执行/调速滑块/重置按钮，像复古游戏机🎮

---

## 2. 精选优质题解参考

<eval_intro>
我根据思路清晰度、代码规范性和算法完整性，精选了以下优质题解（评分≥4星）：
</eval_intro>

**题解一：fls233666**
* **点评**：此解思路清晰完整，提出三个关键验证条件：人数上限、奇偶性、父子节点心情约束。代码结构规范，变量命名合理（p为人口，h为幸福指数），DFS分两阶段（统计+验证）逻辑直白。边界处理严谨，可直接用于竞赛，是学习树形统计的典范。

**题解二：两年打铁**
* **点评**：解法亮点在于用公式$al_i=(p_i-h_i)/2$直接计算坏心情人数，推导过程清晰。虽然变量名al(anger level)稍简略，但算法核心有效，父子节点约束验证($al_x-now_x\leq sum$)体现问题本质。实践价值高，适合掌握数学推导技巧。

**题解三：F_Mu**
* **点评**：采用逆向思维，将"回家"转化为"从家到首都"，心情变为"由坏变好"。思路新颖，展示问题多角度解法。代码模块化好，但变量名gd(good)可更直观。提供独特视角，启发灵活转换问题模型。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题的三大核心难点及应对策略：
</difficulty_intro>

1. **难点：准确计算节点心情分布**
   * **分析**：根据$h_i$和总人数$p_i$解方程：$good_i = (p_i + h_i)/2$, $bad_i = (p_i - h_i)/2$。需验证非负性和整数解（奇偶性）
   * 💡 **学习笔记**：方程求解是转换问题关键，注意除以2前的奇偶验证

2. **难点：验证心情变化合理性**
   * **分析**：坏心情只能增加的特性要求：节点$i$的好心情人数≥所有子节点好心情人数之和。因为子节点的好心情可能在该节点到子节点路径上变坏
   * 💡 **学习笔记**：树形问题中，父子节点状态约束常反映问题核心逻辑

3. **难点：高效统计子树总人数**
   * **分析**：通过DFS后序遍历（自底向上）累加子树人数。用`vector`或邻接表存储树结构，递归返回时父节点累加子节点数据
   * 💡 **学习笔记**：树形DFS统计是基础但关键技巧，注意避免重复计算

### ✨ 解题技巧总结
<summary_best_practices>
通用解题策略：
</summary_best_practices>
- **树形问题分解**：将树分解为子树处理，递归求解子问题
- **状态方程转换**：将约束条件转化为数学方程（如好/坏心情人数计算）
- **边界防御性编程**：检查数据范围（人数非负）、奇偶性、父子状态一致性
- **增量验证**：DFS中实时验证条件，提前终止无效分支

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解提炼的通用实现，包含关键步骤：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合自优质题解，包含树形统计和三层验证
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1e5+5;

vector<int> tree[MAXN];
int p[MAXN], h[MAXN], total[MAXN], good[MAXN];
bool valid;

// 统计子树总人数
void dfs_stats(int u, int parent) {
    total[u] = p[u];
    for (int v : tree[u]) {
        if (v == parent) continue;
        dfs_stats(v, u);
        total[u] += total[v]; // 累加子树人数
    }
}

// 验证幸福指数条件
void dfs_check(int u, int parent) {
    // 1. 解方程求好心情人数
    int g = (total[u] + h[u]) / 2;
    int b = (total[u] - h[u]) / 2;
    
    // 2. 验证三个条件
    if (abs(h[u]) > total[u] || (total[u] + h[u]) % 2 != 0 || g < 0 || b < 0) {
        valid = false; return;
    }
    good[u] = g;

    // 3. 统计子节点好心情人数
    int childGood = 0;
    for (int v : tree[u]) {
        if (v == parent) continue;
        dfs_check(v, u);
        if (!valid) return;
        childGood += good[v];
    }
    
    // 4. 验证父子约束
    if (good[u] < childGood) {
        valid = false; return;
    }
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        valid = true;
        // 初始化树结构
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            tree[i].clear();
        }
        for (int i = 1; i <= n; i++) cin >> h[i];
        for (int i = 1; i < n; i++) {
            int u, v; cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        // 执行两轮DFS
        dfs_stats(1, -1);
        dfs_check(1, -1);
        cout << (valid ? "YES" : "NO") << endl;
    }
    return 0;
}
```
* **代码解读概要**：
  1. `dfs_stats`：后序遍历统计每个节点的总经过人数
  2. `dfs_check`：验证三个核心条件，计算好心情人数
  3. 主函数：处理多组数据，构建树结构，调用DFS验证

---
<code_intro_selected>
优质题解核心代码亮点解析：
</code_intro_selected>

**题解一：fls233666**
* **亮点**：三步验证完整，代码结构清晰
* **核心代码片段**：
```cpp
void ck(int rp) {
    if (h[rp] > p[rp]) { // 条件1: |h| ≤ 总人数
        ans = false; return; 
    }
    if ((p[rp] - h[rp]) % 2) { // 条件2: 奇偶性验证
        ans = false; return;
    }
    hp[rp] = (p[rp] + h[rp]) / 2; // 计算好心情人数
    int s = 0;
    for (/*遍历子节点*/) {
        s += hp[child]; // 子节点好心情人数和
    }
    if (hp[rp] < s) { // 条件3: 父子约束
        ans = false; return;
    }
}
```
* **代码解读**：
  > 这段代码精炼实现了三层验证：
  > 1. 条件1直接比较`h[rp]`和`p[rp]`
  > 2. 条件2用`(p[rp]-h[rp])%2`检查奇偶性
  > 3. 条件3比较当前节点好心情人数`hp[rp]`和子节点总和`s`
  > 验证失败立即返回，优化执行效率
* 💡 **学习笔记**：树形验证时，父子状态约束是常见模式

**题解二：两年打铁**
* **亮点**：公式推导清晰，直接计算坏心情人数
* **核心代码片段**：
```cpp
void dfs(int x, int fa) {
    int sum = 0;
    // 递归处理子节点
    for (/*遍历子节点*/) {
        dfs(child, x);
        sum += al[child]; // 子节点坏心情人数和
    }
    // 计算并验证坏心情人数
    al[x] = (p[x] - h[x]) / 2; 
    if (al[x] - now[x] > sum) { // 父子约束
        flag = false; return;
    }
}
```
* **代码解读**：
  > 此解亮点：
  > 1. 用`al[x] = (p[x]-h[x])/2`直接得坏心情人数
  > 2. 约束条件`al[x]-now[x] ≤ sum`确保坏心情人数合理
  > 3. `now[x]`(当前节点居住人数)反映本地坏心情增量
  > 像管理连锁店，总部需确保各分店数据合理汇总
* 💡 **学习笔记**：逆向计算（坏心情）可简化问题

**题解三：F_Mu**
* **亮点**：逆向思维转换问题模型
* **核心代码片段**：
```cpp
pii dfs(int x, int fa) {
    pii res = {0, 0}; // (good, bad)
    // 合并子树结果
    for (/*遍历子节点*/) {
        pii childRes = dfs(child, x);
        res.first += childRes.first; // 累加子树好心情
        res.second += childRes.second; // 累加子树坏心情
    }
    // 验证当前节点
    int total = res.first + res.second + p[x];
    int x_good = (total + h[x]) / 2; 
    if (x_good < res.first || x_good > total) {
        flag = false; // 验证失败
    }
    return {x_good, total - x_good};
}
```
* **代码解读**：
  > 创新性转换问题方向：
  > 1. 从"回家"变为"去首都"，心情"由坏变好"
  > 2. 递归合并子树结果时累加(good, bad)对
  > 3. 验证时检查计算值是否在理论范围内
  > 像逆向追踪河流源头，获得新视角
* 💡 **学习笔记**：灵活转换问题模型可打开新思路

-----

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
下面是为本题设计的"像素王国幸福验证器"动画方案，采用8-bit复古风格，帮助直观理解算法流程：
</visualization_intro>

* **动画主题**：像素王国交通网与心情验证大冒险

* **核心演示内容**：树形DFS统计与三层验证过程

* **设计思路**：采用FC红白机像素风格，用颜色区分算法状态。游戏化进度条和音效增强学习动力，关键操作可视化降低理解门槛。

* **动画帧步骤**：
  1. **场景初始化**（像素网格+控制面板）
     - 树形结构：节点用彩色像素方块（首都=金色，其他=蓝色）
     - 控制面板：开始/暂停/步进/速度滑块/重置
     - 信息栏：显示当前节点ID/总人数/好心情人数
     - 背景：低饱和度像素网格，播放轻松8-bit音乐

  2. **人口统计阶段**（自底向上DFS）
     - 叶子节点先亮起，显示人口数`p[i]`（像素数字跳动）
     - 递归返回时：父节点方块膨胀，显示累加值（`p[父] += p[子]`）
     - 音效：节点激活=清脆"叮"声，数据累加=齿轮转动声

  3. **幸福验证阶段**（自顶向下DFS）
     - **条件1验证**：若`|h_i| > p_i`，节点闪烁红色+警报音
     - **条件2验证**：奇偶检查失败时，节点交替黄蓝闪烁+错误音
     - **条件3验证**：
       - 当前节点：顶部绿色条=好心情人数
       - 子节点：显示绿色条并连线汇总
       - 违反时：绿色条断裂+碎裂动画音效

  4. **游戏化进度与反馈**
     - 成功通过节点：像素烟花+金币音效，进度条增长
     - 完全通过：全屏彩虹动画+胜利音乐
     - 失败：屏幕抖动，显示"Game Over"像素字体

  5. **AI演示模式**（自动播放）
     - 像"吃豆人"AI自动遍历树结构
     - 可调速观察细节（0.5x-4x速度）
     - 暂停时显示当前步骤的伪代码和变量值

* **交互控制**：
  - 步进模式：按一次键前进一个算法步骤
  - 速度滑块：实时调整动画速度
  - 模式切换：手动/AI演示/对比模式（并排不同解法）

* **音效设计**：
  - 关键操作：选择节点（水滴声），验证通过（上升音阶）
  - 错误提示：短促"哔"声
  - 背景音乐：轻快8-bit循环旋律

<visualization_conclusion>
这个像素动画方案将抽象算法转化为可交互的游戏体验，通过视觉反馈和音效强化对树形统计和条件验证的理解。
</visualization_conclusion>

-----

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题技巧后，可尝试以下相似问题：
</similar_problems_intro>

* **通用技巧迁移**：
  树形统计和状态验证技巧适用于：
  1. 树形路径统计（如节点覆盖问题）
  2. 父子状态约束问题（如资源分配）
  3. 树形动态规划优化

* **练习推荐 (洛谷)**：
  1. **洛谷 P1352** - 没有上司的舞会
     * 🗣️ **推荐理由**：基础树形DP，练习父子状态转移（类似心情传递约束）
  
  2. **洛谷 P2014** - 选课
     * 🗣️ **推荐理由**：树形依赖背包问题，强化DFS统计和资源分配技巧
  
  3. **洛谷 P1273** - 有线电视网
     * 🗣️ **推荐理由**：树形统计+成本验证，与本题人口统计高度相似

-----

## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中的调试经验值得借鉴：
</insights_intro>

> **参考经验 (来自 fls233666)**：
> "在解决这个问题时，最初在边界条件处理上卡了很久，后来通过构造极端测试用例（如单节点、全坏心情情况）才定位到问题"
>
> **点评**：这提醒我们：
> 1. 树形问题中，单节点和链状结构是重要边界用例
> 2. 极端数据测试（如最大规模、全负值）能暴露隐藏bug
> 3. 分步验证比整体调试更高效

<conclusion>
本次"Uncle Bogdan and Country Happiness"的解析就到这里。记住核心技巧：树形统计DFS + 三层条件验证。多练习树形问题，下次遇到类似挑战时，你一定能像像素勇士一样顺利通关！💪
</conclusion>

-----

---
处理用时：269.44秒