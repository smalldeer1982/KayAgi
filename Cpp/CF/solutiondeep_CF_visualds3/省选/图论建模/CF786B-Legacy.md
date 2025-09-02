# 题目信息

# Legacy

## 题目描述

Rick and his co-workers have made a new radioactive formula and a lot of bad guys are after them. So Rick wants to give his legacy to Morty before bad guys catch them.

There are $ n $ planets in their universe numbered from $ 1 $ to $ n $ . Rick is in planet number $ s $ (the earth) and he doesn't know where Morty is. As we all know, Rick owns a portal gun. With this gun he can open one-way portal from a planet he is in to any other planet (including that planet). But there are limits on this gun because he's still using its free trial.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786B/9ce8ffb5132d0e638eaee42e56a9bbc8517d720d.png)By default he can not open any portal by this gun. There are $ q $ plans in the website that sells these guns. Every time you purchase a plan you can only use it once but you can purchase it again if you want to use it more.

Plans on the website have three types:

1. With a plan of this type you can open a portal from planet $ v $ to planet $ u $ .
2. With a plan of this type you can open a portal from planet $ v $ to any planet with index in range $ [l,r] $ .
3. With a plan of this type you can open a portal from any planet with index in range $ [l,r] $ to planet $ v $ .

Rick doesn't known where Morty is, but Unity is going to inform him and he wants to be prepared for when he finds and start his journey immediately. So for each planet (including earth itself) he wants to know the minimum amount of money he needs to get from earth to that planet.

## 说明/提示

In the first sample testcase, Rick can purchase $ 4 $ th plan once and then $ 2 $ nd plan in order to get to get to planet number $ 2 $ .

## 样例 #1

### 输入

```
3 5 1
2 3 2 3 17
2 3 2 2 16
2 2 2 3 3
3 3 1 1 12
1 3 3 17
```

### 输出

```
0 28 12 
```

## 样例 #2

### 输入

```
4 3 1
3 4 1 3 12
2 2 3 4 10
1 2 4 16
```

### 输出

```
0 -1 -1 12 
```

# AI分析结果

# 💡 Kay的C++算法解析：Legacy 深入学习指南 💡

<introduction>
  今天我们来一起攻克Codeforces的经典题目「Legacy」！这道题的核心是**用线段树优化建图**解决大规模区间连边问题，再结合最短路算法找到答案。跟着Kay一步步拆解，你会发现“复杂的区间操作”其实可以用“线段树组长”轻松管理~
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：线段树优化建图 + Dijkstra最短路  

🗣️ **初步分析**：
> 题目要求我们处理三种连边操作：点到点、点到区间、区间到点，然后求从起点到所有点的最短路。如果暴力连边（比如点到区间连n条边），边数会爆炸到O(n²)，直接超时！  
> 这时候需要**线段树优化建图**——把“区间”打包成线段树的节点（像“组长”管理“组员”），用O(logn)条边代替O(n)条边。具体来说：
> - 建**两棵线段树**：  
  - 「出树」：处理“点到区间”的边（父节点连子节点，边权0，像组长给组员传话）；  
  - 「入树」：处理“区间到点”的边（子节点连父节点，边权0，像组员向组长汇报）；  
  - 两棵树的叶子节点（真正的点）互相连0权边，让“消息”能在两棵树间传递。  
> 处理完所有操作后，用**Dijkstra算法**跑最短路（因为边权都是正数，不能用SPFA哦~）。  

- **核心流程**：先建树→处理三种操作连边→跑Dijkstra→输出结果。  
- **可视化设计思路**：用FC红白机风格的像素画展示线段树结构，三种操作的连边过程用“箭头+颜色闪烁”表示，Dijkstra的松弛过程用“节点颜色变深”体现，搭配“叮”的操作音效和“胜利”音效增强记忆~


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等维度筛选了4篇优质题解，帮你快速抓住重点~
</eval_intro>

### 题解一：tzc_wk（赞113）  
* **点评**：这是一篇“线段树优化建图”的标准模板题解！思路直接——先建两棵线段树（出树和入树），用线段树节点代替区间连边，最后跑Dijkstra。代码结构清晰，变量命名规范（比如`leaf`数组存叶子节点编号），边界处理严谨（比如叶子节点互相连0边）。亮点是**用线段树拆分区间的逻辑写得非常直白**，适合新手模仿。

### 题解二：maoyiting（赞80）  
* **点评**：这篇题解的“图文解释”堪称一绝！用三张图分别展示了“点到区间连边”“区间到点连边”“两棵树的结构”，把抽象的线段树优化讲得通俗易懂。代码部分把“出树”和“入树”分开实现，逻辑更清晰，还贴心地注释了每一步的作用（比如`add(a[x]+K, a[y], z)`处理点到点连边）。亮点是**用比喻把线段树节点比作“区间代表”**，让新手瞬间理解为什么要拆区间。

### 题解三：张鑫杰（赞40）  
* **点评**：这篇题解用`vector`建图（比链表更直观），代码风格简洁。建树时直接把叶子节点编号设为原节点编号，减少了映射的复杂度。亮点是**明确指出“SPFA会被卡”**（因为边权为正，Dijkstra更稳定），并提醒用`long long`避免溢出——这些细节能帮你少踩坑！

### 题解四：Nekroz（赞15）  
* **点评**：这篇题解用“动态开点线段树”实现，适合处理更大的数据规模。代码注释详细（比如`build1`建出树，`build2`建入树），连边逻辑和前面的题解一致，但用“前向星”存边更省空间。亮点是**用样例输入画出了具体的图**，帮你直观理解线段树如何连接。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的关键是“把区间连边转化为线段树连边”，以下三个难点最容易卡壳，我们逐一攻破~
</difficulty_intro>

### 1. 为什么要建两棵线段树？  
* **分析**：如果只用一棵线段树，“点到区间”和“区间到点”的边会互相干扰（比如父节点连子节点的边会让区间到点的边变成“全区间连点”）。建两棵树：  
  - 出树（父→子）：处理“点到区间”——点连到出树的区间节点，再通过父→子边传递到所有叶子；  
  - 入树（子→父）：处理“区间到点”——区间的叶子节点连到入树的父节点，再传递到目标点。  
* 💡 **学习笔记**：两棵树分工明确，避免边的方向混乱。

### 2. 线段树内部的边怎么连？  
* **分析**：  
  - 出树（点→区间）：父节点连子节点，边权0——比如父节点代表[1,4]，连到子节点[1,2]和[3,4]，这样点连到父节点后，能通过0权边到达所有子节点（即区间内的点）；  
  - 入树（区间→点）：子节点连父节点，边权0——比如子节点[1,2]连到父节点[1,4]，这样区间内的点连到子节点后，能通过0权边传递到父节点（再连到目标点）。  
* 💡 **学习笔记**：线段树内部的边是“传递消息的通道”，边权0保证不影响最短路。

### 3. 三种操作怎么对应到线段树？  
* **分析**：  
  - 操作1（点→点）：直接连两棵树的叶子节点（比如入树的u叶子连到出树的v叶子）；  
  - 操作2（点→区间）：点连到出树的区间节点（用线段树拆分区间，连O(logn)条边）；  
  - 操作3（区间→点）：入树的区间节点连到点（同样拆分区间，连O(logn)条边）。  
* 💡 **学习笔记**：操作的本质是“找线段树中的区间节点，代替原区间连边”。

### ✨ 解题技巧总结  
- **技巧A**：遇到“区间连边”先想线段树——把区间拆成logn个节点，减少边数；  
- **技巧B**：边权为正时优先用Dijkstra（堆优化），避免SPFA被卡；  
- **技巧C**：数组要开大——线段树的节点数是原节点的4倍，加上两棵树，要开足空间（比如`1e5`的点需要开`4e5*2`的数组）。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**通用核心实现**，综合了优质题解的思路，结构清晰，适合入门~
</code_intro_overall>

### 本题通用核心C++实现参考  
* **说明**：本代码综合了tzc_wk和maoyiting的思路，用线段树优化建图，堆优化Dijkstra求解。  
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 1e18;
const int MAXN = 1e5 + 5;
const int MAXM = 4e6 + 5;

int n, m, s;
int leaf[MAXN]; // 叶子节点编号（原节点i对应线段树的leaf[i]）
vector<pli> g[MAXM]; // 图的邻接表
int tot; // 线段树节点总数

// 建线段树（type=0:出树（父→子）；type=1:入树（子→父））
void build(int k, int l, int r, int type) {
    if (l == r) {
        leaf[l] = k;
        return;
    }
    int mid = (l + r) >> 1;
    // 出树：父连子；入树：子连父
    if (type == 0) {
        g[k].emplace_back(0, k << 1);
        g[k].emplace_back(0, k << 1 | 1);
    } else {
        g[k << 1].emplace_back(0, k);
        g[k << 1 | 1].emplace_back(0, k);
    }
    build(k << 1, l, mid, type);
    build(k << 1 | 1, mid + 1, r, type);
}

// 连边：from连到区间[l,r]（type=0:出树；type=1:入树）
void connect(int k, int l, int r, int ql, int qr, int from, ll w, int type) {
    if (ql <= l && r <= qr) {
        if (type == 0) g[from].emplace_back(w, k); // 点→区间（出树）
        else g[k].emplace_back(w, from); // 区间→点（入树）
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) connect(k << 1, l, mid, ql, qr, from, w, type);
    if (qr > mid) connect(k << 1 | 1, mid + 1, r, ql, qr, from, w, type);
}

ll dis[MAXM];
bool vis[MAXM];
void dijkstra(int start) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dis[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto [w, v] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.emplace(dis[v], v);
            }
        }
    }
}

int main() {
    cin >> n >> m >> s;
    tot = n * 4 * 2; // 两棵线段树，每棵4倍原节点
    // 建出树（根1）和入树（根tot/2+1，避免冲突）
    build(1, 1, n, 0);
    build(tot / 2 + 1, 1, n, 1);
    // 叶子节点互相连0边（出树→入树，入树→出树）
    for (int i = 1; i <= n; i++) {
        g[leaf[i]].emplace_back(0, leaf[i] + tot / 2);
        g[leaf[i] + tot / 2].emplace_back(0, leaf[i]);
    }
    // 处理操作
    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int v, u; ll w;
            cin >> v >> u >> w;
            g[leaf[v]].emplace_back(w, leaf[u]); // 点→点
        } else if (opt == 2) {
            int v, l, r; ll w;
            cin >> v >> l >> r >> w;
            connect(1, 1, n, l, r, leaf[v], w, 0); // 点→区间（出树）
        } else {
            int v, l, r; ll w;
            cin >> v >> l >> r >> w;
            connect(tot / 2 + 1, 1, n, l, r, leaf[v], w, 1); // 区间→点（入树）
        }
    }
    dijkstra(leaf[s]); // 从起点的叶子节点开始
    for (int i = 1; i <= n; i++) {
        if (dis[leaf[i]] == INF) cout << "-1 ";
        else cout << dis[leaf[i]] << " ";
    }
    return 0;
}
```
* **代码解读概要**：  
  1. **建树**：`build`函数建出树（父→子）和入树（子→父），`leaf`数组存原节点对应的叶子节点编号；  
  2. **连边**：`connect`函数处理区间连边，拆分区间并连到线段树节点；  
  3. **最短路**：`dijkstra`函数用堆优化求解单源最短路；  
  4. **主函数**：处理输入，调用建树、连边、最短路函数，输出结果。

<code_intro_selected>
接下来剖析优质题解的核心片段，看看他们的“小技巧”~
</code_intro_selected>

### 题解一（tzc_wk）：核心代码片段  
* **亮点**：用`D=5e5`区分两棵树的节点，避免编号冲突。  
* **核心代码片段**：
```cpp
const int D=5e5;
void build(int k,int l,int r){
    if(l==r){ leaf[l]=k; return; }
    int mid=(l+r)>>1;
    g[k].push_back(pii(k<<1,0)); // 出树：父→子
    g[(k<<1)+D].push_back(pii(k+D,0)); // 入树：子→父
    build(k<<1,l,mid); build(k<<1|1,mid+1,r);
}
```
* **代码解读**：  
  - `D=5e5`是两棵树的“偏移量”：出树节点编号是`k`，入树是`k+D`；  
  - 出树的父节点`k`连子节点`k<<1`（左）和`k<<1|1`（右），边权0；  
  - 入树的子节点`k<<1+D`连父节点`k+D`，边权0。  
* 💡 **学习笔记**：用偏移量区分两棵树，是一种简洁的编号方式。

### 题解二（maoyiting）：核心代码片段  
* **亮点**：用`K`作为偏移量，把入树和出树的连边逻辑写得更直观。  
* **核心代码片段**：
```cpp
const int K = 1e5 * 4; // 偏移量
void build(int p,int l,int r){
    if(l==r){ a[l]=p; return; }
    add(p,p<<1,0); // 出树：父→子
    add((p<<1)+K,p+K,0); // 入树：子→父
    build(p<<1,l,mid); build(p<<1|1,mid+1,r);
}
```
* **代码解读**：  
  - `a[l]`存原节点`l`对应的叶子节点编号；  
  - 出树的父节点`p`连子节点`p<<1`，边权0；  
  - 入树的子节点`p<<1+K`连父节点`p+K`，边权0。  
* 💡 **学习笔记**：用`add`函数封装连边操作，代码更简洁。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“看”到线段树优化建图的过程，Kay设计了一个**FC红白机风格的像素动画**！像玩《超级马里奥》一样理解算法~
</visualization_intro>

### 动画演示主题  
**像素探险家：线段树寻路记**——你扮演“Rick”（起点），用线段树“组长”帮你快速连接所有星球，找到最短路径！

### 设计思路  
- **风格**：8位像素风（像FC游戏《塞尔达传说》），用红、蓝、绿三色区分出树、入树、原节点；  
- **交互**：支持“单步执行”“自动播放”“重置”，速度滑块调节动画速度；  
- **音效**：连边时“叮”一声，松弛成功时“哔”一声，找到最短路径时播放“胜利”旋律。

### 动画帧步骤  
1. **场景初始化**：  
   - 屏幕左侧显示“出树”（红色节点，父→子边），右侧显示“入树”（蓝色节点，子→父边）；  
   - 底部是“控制面板”（开始/暂停、单步、重置按钮，速度滑块）；  
   - 原节点（绿色像素块）位于两棵树的叶子位置，互相连0权边（黄色虚线）。

2. **操作2演示（点→区间）**：  
   - Rick（起点s）要连到区间[2,5]：  
     1. 点击“操作2”按钮，输入v=1, l=2, r=5, w=10；  
     2. 动画显示Rick（绿色块）向出树的[2,4]和[5,5]节点（红色块）连边（橙色箭头），边权10；  
     3. 出树的[2,4]节点向子节点[2,2]和[3,4]连0权边（红色箭头），最终传递到所有叶子节点。

3. **Dijkstra演示**：  
   - 点击“开始寻路”：  
     1. 起点s的距离变为0（绿色块闪烁）；  
     2. 堆优化的优先队列弹出距离最小的节点（红色框选中），松弛其邻接节点；  
     3. 被松弛的节点距离变小（颜色变深），并加入队列（蓝色框标记）；  
     4. 最终所有节点的最短距离显示在屏幕下方（绿色数字）。

### 游戏化元素  
- **关卡设计**：把“建树→连边→寻路”分成3关，完成每关获得“线段树徽章”；  
- **积分系统**：连边次数越少（用logn条边代替n条），积分越高；  
- **AI演示**：点击“AI自动玩”，观察算法如何自动完成所有操作，像“AI马里奥”一样聪明！

<visualization_conclusion>
通过这个动画，你能直观看到“线段树如何把区间连边变简单”，以及“Dijkstra如何一步步找到最短路径”。赶紧动手实现这个动画，或者找类似的在线可视化工具（比如「算法可视化平台」）试试吧！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
线段树优化建图的思路能解决很多“区间操作”问题，比如区间连边、区间更新、区间查询。以下是几个相似问题，帮你巩固技巧~
</similar_problems_intro>

### 通用思路迁移  
- **场景1**：区间内的所有点向另一个区间连边（比如「P3588 [POI2015]PUS」）；  
- **场景2**：动态维护区间的最短路（比如「P5025 [SNOI2017]炸弹」）；  
- **场景3**：区间内的点互相连边（比如「BZOJ3073 [Pa2011]Journeys」）。

### 洛谷练习推荐  
1. **洛谷 P3588** - [POI2015]PUS  
   * 🗣️ **推荐理由**：这道题需要“区间连向区间”，是线段树优化建图的进阶版，能帮你巩固“两棵树连边”的思路。  
2. **洛谷 P5025** - [SNOI2017]炸弹  
   * 🗣️ **推荐理由**：题目要求“炸弹的爆炸范围”，本质是区间连边求最短路，能锻炼你“将实际问题转化为图论模型”的能力。  
3. **洛谷 P3384** - 树链剖分  
   * 🗣️ **推荐理由**：虽然是树链剖分，但核心是“用线段树处理路径区间”，能帮你加深对“线段树处理区间”的理解。  
4. **洛谷 P4172** - [WC2006]水管局长  
   * 🗣️ **推荐理由**：动态图连通性问题，用到“线段树分治”，是线段树优化的高级应用，适合挑战自我。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中的“踩坑经验”能帮你少走弯路，以下是几个关键心得：
</insights_intro>

> **经验1（来自tzc_wk）**：“一开始我只用了一棵线段树，结果所有点的距离都是0，后来才明白需要两棵树分工！”  
> **点评**：这是新手最容易犯的错误——线段树的边方向会导致“消息乱窜”。记住：点→区间用出树（父→子），区间→点用入树（子→父）。  

> **经验2（来自张鑫杰）**：“我一开始用SPFA，结果被卡了，后来换成Dijkstra才过！”  
> **点评**：边权为正时，Dijkstra的堆优化更稳定，不会被恶意数据卡超时。记住：SPFA适合负权边，正权边优先用Dijkstra。  

> **经验3（来自maoyiting）**：“数组开小了会RE，线段树的节点数要开原节点的4倍以上！”  
> **点评**：线段树的节点数通常是原节点的4倍（比如n=1e5，线段树需要4e5节点），加上两棵树，要开足8e5甚至更大的空间。


<conclusion>
本次关于「Legacy」的分析就到这里！线段树优化建图的核心是“用区间代表节点，减少边数”，而最短路是“找到最优路径”。记住：遇到“区间连边”先想线段树，边权为正用Dijkstra！  
下次我们会分析更复杂的线段树优化问题，比如“区间连向区间”，敬请期待~ 💪
</conclusion>

---
处理用时：133.84秒