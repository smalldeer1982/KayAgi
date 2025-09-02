# 题目信息

# Fetch the Treasure

## 题目描述

Rainbow built $ h $ cells in a row that are numbered from 1 to $ h $ from left to right. There are $ n $ cells with treasure. We call each of these $ n $ cells "Treasure Cell". The $ i $ -th "Treasure Cell" is the $ a_{i} $ -th cell and the value of treasure in it is $ c_{i} $ dollars.

Then, Freda went in the first cell. For now, she can go just $ k $ cells forward, or return to the first cell. That means Freda was able to reach the 1st, ( $ k+1 $ )-th, ( $ 2·k+1 $ )-th, ( $ 3·k+1 $ )-th cells and so on.

Then Rainbow gave Freda $ m $ operations. Each operation is one of the following three types:

1. Add another method $ x $ : she can also go just $ x $ cells forward at any moment. For example, initially she has only one method $ k $ . If at some moment she has methods $ a_{1},a_{2},...,a_{r} $ then she can reach all the cells with number in form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF311C/098e382b3b8846367b54760ca19a29ffa8e34102.png), where $ v_{i} $ — some non-negative integer.
2. Reduce the value of the treasure in the $ x $ -th "Treasure Cell" by $ y $ dollars. In other words, to apply assignment $ c_{x}=c_{x}-y $ .
3. Ask the value of the most valuable treasure among the cells Freda can reach. If Freda cannot reach any cell with the treasure then consider the value of the most valuable treasure equal to 0, and do nothing. Otherwise take the most valuable treasure away. If several "Treasure Cells" have the most valuable treasure, take the "Treasure Cell" with the minimum number (not necessarily with the minimum number of cell). After that the total number of cells with a treasure is decreased by one.

As a programmer, you are asked by Freda to write a program to answer each query.

## 说明/提示

In the sample, there are 10 cells and 3 "Treasure Cells". The first "Treasure Cell" is cell 5, having 50 dollars tresure in it. The second "Treasure Cell" is cell 7, having 60 dollars tresure in it. The third "Treasure Cell" is cell 8, having 100 dollars tresure in it.

At first, Freda can only reach cell 1, 3, 5, 7 and 9. In the first operation, we reduce the value in the second "Treasure Cell" from 60 to 55. Then the most valuable treasure among the "Treasure Cells" she can reach is max(50, 55) = 55. After the third operation, she can also go 3 cells forward each step, being able to reach cell 1, 3, 4, 5, 6, 7, 8, 9, 10. So the most valuable tresure is 100.

Noticed that she took the 55 dollars and 100 dollars treasure away, so the last answer is 50.

## 样例 #1

### 输入

```
10 3 5 2
5 50
7 60
8 100
2 2 5
3
1 3
3
3
```

### 输出

```
55
100
50
```

# AI分析结果

# 💡 Kay的C++算法解析：Fetch the Treasure 深入学习指南 💡

<introduction>
今天我们要拆解一道**结合图论最短路与动态数据维护**的编程题——《Fetch the Treasure》。题目里Freda要在格子间移动取宝藏，而我们需要处理三种动态操作：添加移动方式、修改宝藏价值、查询并取走最大价值的可达宝藏。这道题的核心是**用“同余最短路”解决可达性问题**，再配合高效的数据结构维护宝藏状态。跟着Kay一步步分析，你会发现“复杂问题”其实是“简单模型的组合”！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：同余最短路（图论应用） + 动态集合维护（multiset/线段树）

🗣️ **初步分析**：
解决这道题的关键，是先搞懂“Freda能到达哪些格子”——这正好是**同余最短路**的经典场景！  
简单来说，同余最短路就像“给格子按余数分组”：把所有格子编号`x`写成`x = q*k + r`（`r`是`x`模`k`的余数，`q`是“段数”）。比如`k=5`时，`x=7`就是`1*5+2`，余数`r=2`，段数`q=1`。Freda能到达某个格子`x`的条件是：**该余数`r`对应的“最小段数”`d[r] ≤ q`**（`d[r]`表示到达余数`r`类的格子至少需要多少段）。  

那“添加前进`x`步”的操作怎么处理？其实是**给余数类之间连边**：比如前进`x`步，余数`r`会变成`(r+x) mod k`，段数增加`(r+x)/k`（比如`r=3`、`x=5`，`(3+5)=8`，`mod 5`是`3`，段数增加`1`）。我们可以把每个余数类当作图的节点，前进`x`步当作边，然后用**Dijkstra算法**计算每个余数类的最小段数`d[r]`——这就是同余最短路的核心！  

题解的通用思路是：  
1. 用同余最短路维护每个余数类的最小段数`d[r]`；  
2. 用`multiset`或线段树维护**当前可达的宝藏价值**（支持动态插入、删除、查最大值）；  
3. 处理三种操作时，更新`d[r]`或宝藏集合，再响应查询。  

**可视化设计思路**：  
我们会用**8位像素风**模拟这个过程——比如用不同颜色的像素块代表余数类（红色表示未更新，绿色表示已计算最小段数），Dijkstra的优先队列用“跳动的像素方块”展示，`multiset`的最大值用“闪烁的金币”表示。操作1时，“新边”会以“蓝线”连接两个余数块，Dijkstra运行时块会“闪烁”并更新数字（段数）；操作3时，最大价值的“金币”会“飞进背包”并播放“咻”的音效～


## 2. 精选优质题解参考

<eval_intro>
我从“思路清晰度、代码可读性、算法有效性”三个维度筛选了2份优质题解，它们分别用不同的数据结构解决了“动态维护宝藏”的问题，各有亮点！
</eval_intro>

### 题解一：LTb_（同余最短路 + multiset）
* **点评**：这份题解的思路**直白且高效**，完美贴合“同余最短路”的核心逻辑。作者把每个余数类当作图节点，操作1（添加前进`x`步）转化为“给所有余数类连边”，然后用Dijkstra更新每个余数的最小段数`d[r]`——这个转化非常关键！  
代码里的`ok`函数（判断宝藏是否可达）、`upd`函数（处理操作1）逻辑清晰，`multiset`的使用也很巧妙：直接用`multiset`存可达宝藏的价值，操作2（修改价值）就是“删旧值、插新值”，操作3（查最大值）就是取`multiset`的最后一个元素（因为`multiset`默认升序排列）。  
特别值得学习的是**边界处理**：初始时`d[1%k] = 0`（因为Freda一开始在第1格，对应余数`1%k`，段数0），避免了“起点不可达”的错误。

### 题解二：bluewindde（同余最短路 + 线段树）
* **点评**：这份题解的亮点是**用线段树解决“最大价值+最小编号”的查询**。题目中操作3要求“取最大价值的宝藏，若有多个取编号最小的”——`multiset`无法直接处理“编号最小”的条件，但线段树可以！作者定义了`node`结构体，重载`+`运算符：合并两个节点时，优先选价值大的；价值相同时选编号小的。这样线段树的根节点就是“当前可达的最优宝藏”。  
代码中的`build`函数会重新计算同余最短路的`dis`数组（即题解一的`d`数组），然后更新每个宝藏的可达性（`b`数组），再重建线段树。这种“重新计算+更新状态”的思路，适合处理“动态添加移动方式”的场景。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的“拦路虎”主要有三个：如何建模可达性？如何动态维护宝藏？如何处理操作1的更新？结合题解的思路，我们逐一突破！
</difficulty_intro>

### 1. 难点1：如何用同余最短路建模可达性？
* **分析**：Freda的移动方式是“前进`x`步”，每次移动会改变余数和段数。我们把每个余数`r`（0≤r<k）当作图的节点，前进`x`步对应一条边：从`r`到`(r+x) mod k`，边权是`(r+x)/k`（段数增加量）。然后从“起点余数”（`1%k`）出发，用Dijkstra计算每个节点的**最小段数**`d[r]`——这样，只要格子`x`的段数`q = x/k ≥ d[r]`（`r=x%k`），Freda就能到达`x`！  
* 💡 **学习笔记**：同余最短路的核心是“按余数分组”，把“能否到达”转化为“是否满足段数条件”。

### 2. 难点2：如何动态维护“可达的宝藏集合”？
* **分析**：操作2要修改宝藏价值，操作3要取最大价值（且编号最小）的宝藏。题解一用`multiset`（支持O(log n)插入、删除、查最大值），但无法处理“编号最小”；题解二用线段树（自定义合并逻辑），完美解决双条件查询。选择哪种数据结构，取决于题目要求的**查询条件**！  
* 💡 **学习笔记**：动态集合问题，先想清楚“需要哪些操作”，再选对应的数据结构（`multiset`适合简单最值，线段树适合复杂条件）。

### 3. 难点3：如何处理“添加移动方式”（操作1）？
* **分析**：添加新的前进`x`步，意味着图中多了新的边（每个余数`r`到`(r+x) mod k`的边）。此时需要**重新跑Dijkstra**，更新每个余数的最小段数`d[r]`，然后遍历所有宝藏，将“新可达的宝藏”加入集合，“不再可达的”移除。题解一的`upd`函数就是这么做的！  
* 💡 **学习笔记**：动态添加边时，最短路可能变化，需要重新计算——这是图论中的“动态最短路”问题，这里因为`k`很小（≤1e4），所以暴力重新跑Dijkstra是可行的。

### ✨ 解题技巧总结
- **问题转化**：把“能否到达格子”转化为“同余最短路的段数条件”，将复杂的移动问题抽象成图论模型；  
- **数据结构选择**：根据查询条件选`multiset`（简单最值）或线段树（复杂条件）；  
- **边界处理**：初始时要正确设置起点的`d[r]`（比如`d[1%k] = 0`），避免遗漏起点。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合题解一思路的核心代码**——它用同余最短路+multiset，逻辑简洁，适合入门理解！
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：本代码基于LTb_的题解优化，保留了“同余最短路+multiset”的核心逻辑，变量名更直观。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

typedef long long ll;
const ll INF = 1e18;
const int MAXN = 1e5 + 5;
const int MAXK = 1e4 + 5;

ll h, n, m, k;
ll a[MAXN], c[MAXN];  // a[i]是第i个宝藏的位置，c[i]是价值
ll d[MAXK];           // d[r]表示余数r的最小段数
multiset<ll> s;       // 存当前可达的宝藏价值
bool in[MAXN];        // 标记第i个宝藏是否在s中

// 判断宝藏i是否可达
bool is_reachable(int i) {
    ll x = a[i];
    ll r = x % k;
    ll q = x / k;
    return d[r] <= q;
}

struct Node {
    int r;  // 余数
    ll w;   // 段数
    bool operator<(const Node& other) const {
        return w > other.w;  // 小根堆（优先队列默认大根堆，所以反过来）
    }
};

vector<Node> G[MAXK];  // 图的邻接表
ll dis[MAXK];          // Dijkstra的距离数组
bool vis[MAXK];        // 标记是否访问过

// 跑Dijkstra更新d数组
void dijkstra() {
    fill(dis, dis + k, INF);
    fill(vis, vis + k, false);
    priority_queue<Node> pq;

    // 起点是余数1%k，段数0
    int start_r = 1 % k;
    dis[start_r] = 0;
    pq.push({start_r, 0});

    while (!pq.empty()) {
        Node u = pq.top();
        pq.pop();
        if (vis[u.r]) continue;
        vis[u.r] = true;

        for (Node v : G[u.r]) {
            if (!vis[v.r] && dis[v.r] > u.w + v.w) {
                dis[v.r] = u.w + v.w;
                pq.push({v.r, dis[v.r]});
            }
        }
    }

    // 更新d数组（取更小的段数）
    for (int r = 0; r < k; r++) {
        if (dis[r] < d[r]) {
            d[r] = dis[r];
        }
    }
}

// 处理操作1：添加前进x步
void add_step(ll x) {
    // 给每个余数r连边：r -> (r+x)%k，边权是(r+x)/k
    for (int r = 0; r < k; r++) {
        int nr = (r + x) % k;
        ll w = (r + x) / k;
        G[r].push_back({nr, w});
    }
    // 重新跑Dijkstra更新d数组
    dijkstra();
    // 更新所有宝藏的可达性
    for (int i = 1; i <= n; i++) {
        if (is_reachable(i)) {
            if (!in[i]) {
                s.insert(c[i]);
                in[i] = true;
            }
        } else {
            if (in[i]) {
                s.erase(s.find(c[i]));
                in[i] = false;
            }
        }
    }
}

int main() {
    cin >> h >> n >> m >> k;

    // 初始化d数组为INF
    fill(d, d + k, INF);
    // 起点是第1格，余数1%k，段数0
    int start_r = 1 % k;
    d[start_r] = 0;

    // 初始化宝藏
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> c[i];
        if (is_reachable(i)) {
            s.insert(c[i]);
            in[i] = true;
        }
    }

    // 处理m个操作
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            add_step(x);
        } else if (op == 2) {
            int x;
            ll y;
            cin >> x >> y;
            // 修改第x个宝藏的价值
            if (in[x]) {
                s.erase(s.find(c[x]));
            }
            c[x] -= y;
            if (in[x]) {
                s.insert(c[x]);
            }
        } else {
            // 查询并取走最大价值
            if (s.empty()) {
                cout << 0 << endl;
            } else {
                auto it = prev(s.end());  // 最大元素（multiset升序）
                cout << *it << endl;
                s.erase(it);
            }
        }
    }

    return 0;
}
```
* **代码解读概要**：
  1. **初始化**：`d`数组存每个余数的最小段数，初始时只有起点（第1格）的余数`1%k`的段数为0；  
  2. **操作1**：`add_step`函数给每个余数连边，跑Dijkstra更新`d`数组，再更新所有宝藏的可达性；  
  3. **操作2**：修改宝藏价值时，先从`multiset`中删除旧值，再插入新值；  
  4. **操作3**：取`multiset`的最后一个元素（最大值），输出后删除。

<code_intro_selected>
接下来看两份优质题解的核心片段，学习它们的“亮点技巧”！
</code_intro_selected>

### 题解一：LTb_的“同余最短路建模”
* **亮点**：把“添加前进x步”转化为“给所有余数连边”，用Dijkstra高效更新最小段数。
* **核心代码片段**：
```cpp
// 处理操作1的upd函数
inline void upd(int x) {
    // 清空旧图，重置dis数组
    for (int i = 0; i < k; i++)
        G[i].clear(), dis[i] = INF;
    // 给每个余数r连边：r -> (r+x)%k，边权是(r+x)/k
    for (int i = 0; i < k; i++) {
        G[i].push_back((Node){(i + x) % k, (i + x) / k});
        G[k].push_back((Node){i, d[i]});  // 源点S（k号节点）连向每个余数i，边权d[i]
    }
    // 从源点k跑Dijkstra
    dijkstra(k);
    // 更新d数组（取更小的段数）
    for (int i = 0; i < k; i++) {
        chmin(d[i], dis[i]);
    }
    // 更新宝藏的可达性
    for (int i = 1; i <= n; i++) {
        if (ok(a[i]) && !in[i]) {
            in[i] = true;
            s.insert(c[i]);
        }
    }
}
```
* **代码解读**：
  - 作者引入了一个**源点S（k号节点）**，把原来的`d`数组作为“源点到每个余数i的边权”——这样可以合并“旧的最小段数”和“新的边”，重新计算更优的`d`数组；  
  - `chmin(d[i], dis[i])`保证`d`数组始终存最小段数，避免重复计算。
* 💡 **学习笔记**：引入源点可以简化“合并新旧状态”的逻辑，是图论中的常用技巧！

### 题解二：bluewindde的“线段树处理双条件查询”
* **亮点**：用线段树的自定义合并逻辑，解决“最大价值+最小编号”的查询。
* **核心代码片段**：
```cpp
// 线段树的节点结构体
struct node {
    int val, id;  // val是宝藏价值，id是宝藏编号
    // 重载+运算符：合并两个节点，优先选价值大的；价值相同选编号小的
    friend inline node operator+(const node &x, const node &y) {
        if (x.val > y.val)
            return {x.val, x.id};
        else if (x.val < y.val)
            return {y.val, y.id};
        return {x.val, min(x.id, y.id)};
    }
} d[400005];  // 线段树数组

// 构建线段树
static inline void build(int s, int t, int p) {
    if (s == t) {
        if (b[s])  // b[s]标记第s个宝藏是否可达
            d[p] = {a[s].y, s};
        else
            d[p] = {0, -1};  // 不可达的宝藏用{0,-1}表示
        return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, p << 1);
    build(mid + 1, t, p << 1 | 1);
    d[p] = d[p << 1] + d[p << 1 | 1];  // 合并左右子节点
}
```
* **代码解读**：
  - 线段树的每个节点存“该区间内的最优宝藏”（最大价值+最小编号）；  
  - 构建线段树时，`b[s]`标记宝藏`s`是否可达，不可达的节点用`{0,-1}`表示；  
  - 合并左右子节点时，用重载的`+`运算符选出最优宝藏——这样根节点就是整个区间的最优解！
* 💡 **学习笔记**：线段树的自定义合并逻辑，可以处理各种复杂的查询条件，比如“最大值+最小下标”“最小值+最大下标”等。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“亲眼看到”同余最短路的运行过程，Kay设计了一个**8位像素风的动画**——像玩FC游戏一样学算法！
</visualization_intro>

### 动画演示主题
**《像素探险家Freda的宝藏之旅》**  
以FC《超级马里奥》的像素风格为基础，模拟Freda的移动、同余最短路的计算，以及宝藏的动态维护。

### 设计思路
- **8位像素风**：用16色 palette（比如红、绿、蓝、黄），元素都是“方块+像素字”，营造复古游戏感；  
- **游戏化交互**：用“方向键”控制单步执行，“空格”自动播放，“R”重置——像玩游戏一样操作算法；  
- **音效增强**：执行关键操作时播放8位音效（比如Dijkstra入队是“叮”，取宝藏是“咻”，成功是“嘟嘟嘟”）。

### 动画帧步骤与交互关键点
#### 1. 场景初始化（FC风格UI）
- 屏幕左侧：**余数类网格**（k个像素块，每个块显示余数`r`和当前最小段数`d[r]`，初始时只有`1%k`的块是绿色，其他是红色）；  
- 屏幕中间：**优先队列可视化**（Dijkstra的小根堆，用“跳动的方块”表示待处理的节点）；  
- 屏幕右侧：**宝藏集合**（用“金币”表示可达的宝藏，金币上显示价值，最大价值的金币闪烁）；  
- 底部控制面板：**单步/自动/重置**按钮，**速度滑块**（1x~5x），**当前操作提示**（比如“正在处理操作1：添加前进3步”）。

#### 2. 操作1：添加前进x步（同余最短路更新）
- **步骤1**：屏幕上方弹出“新技能！前进x步”的提示，同时**余数类网格**中每个红色块（余数`r`）会射出一条蓝线，连接到`(r+x) mod k`的块——这是“新边”的可视化；  
- **步骤2**：Dijkstra开始运行：优先队列中的第一个方块（起点`1%k`）会“跳动”并变成绿色，然后遍历它的所有边，把相邻节点加入队列（队列中的方块会“闪烁”）；  
- **步骤3**：每个余数块的`d[r]`值更新时，块会“闪一下”并显示新的数字——比如`d[2]`从INF变成1，块会从红色变成绿色；  
- **音效**：每加入一个队列节点，播放“叮”的音效；更新`d[r]`时，播放“滴”的音效。

#### 3. 操作3：取走最大价值宝藏
- **步骤1**：右侧的宝藏集合中，最大价值的金币会“放大+闪烁”，并显示“选中！”的提示；  
- **步骤2**：金币会“飞”向屏幕左上角的“背包”图标，同时**multiset/线段树**的可视化区域会“减少一个元素”；  
- **步骤3**：屏幕下方弹出“获得××金币！”的提示，播放“咻”的音效；若没有可达宝藏，弹出“没有宝藏！”并播放“哔”的音效。

#### 4. AI自动演示模式
- 点击“AI自动”按钮，算法会像“马里奥自动闯关”一样，一步步执行操作：自动添加前进步骤、自动更新余数块、自动取宝藏——你可以坐下来观察整个流程，重点部分会慢动作播放！

<visualization_conclusion>
通过这个动画，你能**直观看到**同余最短路如何计算“最小段数”，宝藏集合如何动态变化——就像玩游戏一样，把抽象的算法变成“看得见、摸得着”的过程！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
同余最短路是**处理“模运算+可达性”问题**的神器，掌握它能解决很多类似的题目！
</similar_problems_intro>

### 通用思路/技巧迁移
同余最短路的核心是“按余数分组+最短路”，适用于以下场景：
1. **格子移动问题**：比如“每次走x步，问能否到达某个格子”；  
2. **硬币问题**：比如“用给定面值的硬币，求组成某个金额的最小硬币数”（本质是模硬币面值的最短路）；  
3. **周期问题**：比如“有周期的任务调度，求完成任务的最短时间”。

### 练习推荐 (洛谷)
1. **洛谷 P2384 最短路计数**  
   🗣️ **推荐理由**：这是同余最短路的基础题，要求计算“从起点到每个点的最短路数目”——练习如何建模余数类和边。  
2. **洛谷 P1462 收集邮票**  
   🗣️ **推荐理由**：结合了动态规划和同余最短路的思想，要求“收集所有邮票的最小花费”——练习如何将复杂问题抽象成最短路模型。  
3. **洛谷 P3953 逛公园**  
   🗣️ **推荐理由**：进阶题，要求“在允许k次偏离最短路径的情况下，求从起点到终点的路径数目”——练习动态最短路的处理。  
4. **洛谷 P5662 纪念品**  
   🗣️ **推荐理由**：结合了动态规划和同余最短路，要求“用有限的钱买纪念品的最大价值”——练习如何用同余优化动态规划的状态。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
两份题解的作者都分享了“如何将问题转化为图论模型”的思路，这些经验能帮你少走弯路！
</insights_intro>

> **参考经验 (来自 LTb_)**：“一开始我没想到用同余最短路，直到把格子按模k分组后，发现‘可达性’其实是‘段数是否足够’——这才想到用Dijkstra计算每个余数的最小段数。”  
> **点评**：作者的“分组思维”很重要！当遇到“模运算+可达性”问题时，先尝试“按余数分组”，往往能找到突破口。

> **参考经验 (来自 bluewindde)**：“操作3要求‘最大价值+最小编号’，multiset无法处理，所以我想到用线段树的自定义合并——这让我意识到‘数据结构的选择要贴合查询条件’。”  
> **点评**：作者的“条件匹配”思路值得学习！遇到动态查询问题时，先明确“需要哪些操作”，再选对应的结构（比如线段树处理复杂条件，`multiset`处理简单最值）。


<conclusion>
《Fetch the Treasure》的核心是“同余最短路+动态集合维护”——把复杂的移动问题转化为图论模型，再用高效的数据结构处理动态查询。通过这份指南，你不仅学会了这道题的解法，更掌握了“问题转化”“数据结构选择”的通用技巧！  

记住：编程的本质是“将现实问题抽象成数学模型，再用代码实现”——多思考“为什么这么做”，而不是“怎么做”，你会进步更快！下次我们再一起拆解更有趣的算法题～💪
</conclusion>

---
处理用时：136.27秒