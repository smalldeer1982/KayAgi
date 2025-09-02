# 题目信息

# MEX Queries

## 题目描述

You are given a set of integer numbers, initially it is empty. You should perform $ n $ queries.

There are three different types of queries:

- 1 $ l $ $ r $ — Add all missing numbers from the interval $ [l,r] $
- 2 $ l $ $ r $ — Remove all present numbers from the interval $ [l,r] $
- 3 $ l $ $ r $ — Invert the interval $ [l,r] $ — add all missing and remove all present numbers from the interval $ [l,r] $

After each query you should output MEX of the set — the smallest positive (MEX $ >=1 $ ) integer number which is not presented in the set.

## 说明/提示

Here are contents of the set after each query in the first example:

1. $ {3,4} $ — the interval $ [3,4] $ is added
2. $ {1,2,5,6} $ — numbers $ {3,4} $ from the interval $ [1,6] $ got deleted and all the others are added
3. $ {5,6} $ — numbers $ {1,2} $ got deleted

## 样例 #1

### 输入

```
3
1 3 4
3 1 6
2 1 3
```

### 输出

```
1
3
1
```

## 样例 #2

### 输入

```
4
1 1 3
3 5 6
2 4 4
3 1 6
```

### 输出

```
4
4
4
1
```

# AI分析结果


# 💡 Kay的C++算法解析：MEX Queries 深入学习指南 💡

<introduction>
  今天我们来分析“MEX Queries”这道C++编程题。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。题目要求维护一个初始为空的整数集合，支持三种区间操作，并在每次操作后输出集合的MEX（最小未出现正整数）。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数据结构应用` 与 `区间操作`

🗣️ **初步分析**：
> 解决"MEX Queries"的关键在于高效处理大值域（1e18）上的区间操作。这就像在管理一个巨大的像素画布（10^18像素），我们需要快速完成三种画笔操作：填充区域（添加数字）、擦除区域（删除数字）、反色区域（添加缺失的/删除存在的），每次操作后找出画布上最左边的空白像素（MEX）。

- **核心难点**：值域巨大但操作点有限（O(n)级别），需要设计高效数据结构。离散化（压缩坐标）或动态开点是主要解决方案，配合线段树/珂朵莉树实现区间操作。
- **题解思路对比**：珂朵莉树（随机数据高效）代码简洁但理论复杂度不稳定；线段树+离散化（稳定O(n log n)）是通用解法；平衡树/分块提供替代思路。
- **可视化设计**：采用8位像素风格网格，每个单元格代表离散化后的区间。操作时高亮变化区域（绿色表示添加，灰色表示删除，翻转时颜色反转），查询时闪烁第一个空白格子。动画同步显示当前线段树节点状态和标记传递过程。

---

## 2. 精选优质题解参考

<eval_intro>
我们从思路清晰度、代码规范性、算法效率和实践价值等方面筛选出3条优质题解：

**题解一：珂朵莉树（作者：Unnamed114514）**
* **点评**：思路直接巧妙，利用STL set维护区间碎片。代码简洁规范（宏定义简化迭代器，快读优化），区间赋值（assign）和翻转（rever）实现高效。在本题随机数据特性下表现优异（CF通过），实践价值高，特别适合竞赛快速编码。亮点在于将复杂区间操作转化为O(区间数)的碎片管理。

**题解二：线段树+离散化（作者：Acestar）**
* **点评**：经典解法，结构严谨。离散化处理完整（关键点r+1和1的加入避免边界错误），线段树维护区间和与双重标记（赋值tag/翻转rev）。标记下传逻辑清晰（赋值优先于翻转），查询时左优先二分确保高效。代码规范（模块化函数），边界处理严谨，稳定O(n log n)复杂度，是通用性强的工业级方案。

**题解三：平衡树（作者：Froggy）**
* **点评**：创新采用FHQ Treap动态维护区间，避免离散化。通过分裂/合并实现区间操作，map记录节点位置处理大值域。算法设计巧妙（节点存储[l,r]区间状态），复杂度稳定O(n log n)。亮点在于真正动态处理大值域，适合强制在线场景，但实现复杂度较高。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破三大难点，结合优质题解策略如下：

1.  **关键点1：大值域压缩**
    * **分析**：值域1e18无法直接建树。Acestar题解通过离散化所有操作点（含r+1和1）压缩为O(n)坐标，配合线段树处理。Froggy题解用平衡树动态开点避免压缩。
    * 💡 **学习笔记**：离散化必须包含1和r+1！否则会遗漏MEX=1或r+1的情况。

2.  **关键点2：标记冲突处理**
    * **分析**：赋值操作（1/2）与翻转（3）标记共存时产生冲突。Acestar题解设计"赋值优先"规则：下传时先处理赋值标记，翻转操作遇到赋值标记转为相反赋值（e.g., 赋值1+翻转→赋值0）。
    * 💡 **学习笔记**：多重标记需定义明确优先级（赋值>翻转），类似绘画中先覆盖底色再局部反色。

3.  **关键点3：MEX查询效率**
    * **分析**：暴力扫描O(n)不可取。线段树解法（Acestar）在树上二分：若左子树不满（sum < 区间长度）则进左子树，否则进右子树，复杂度O(log n)。珂朵莉树（Unnamed114514）遍历区间碎片找首个0区间。
    * 💡 **学习笔记**：利用数据结构特性（线段树二分/珂朵莉树区间连续性）优化查询。

### ✨ 解题技巧总结
<summary_best_practices>
通过对本题的深度分析，提炼以下核心技巧：
</summary_best_practices>
- **技巧1：离散化关键点**——除操作端点外，强制加入1和r+1，确保答案正确性。
- **技巧2：标记优先级设计**——赋值操作重置状态，翻转操作需考虑当前标记（赋值时翻转→相反赋值）。
- **技巧3：结构选择策略**——随机数据用珂朵莉树（码量小），稳定需求用线段树（效率保障），动态开点平衡树处理强制在线大值域。
- **技巧4：边界防御**——叶子节点直接修改，非叶节点标记处理，避免无效更新。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是基于优质题解提炼的通用核心实现（线段树+离散化），完整展现解题框架：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合Acestar等题解思路，采用离散化+线段树，稳定高效处理三种操作。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm>
    #define int long long
    using namespace std;
    const int N = 12e5+10, M = 1e5+10;
    int sum[N], tag[N], rev[N], t[M], l[M], r[M], q[N];
    
    void pushup(int rt) { sum[rt] = sum[rt<<1] + sum[rt<<1|1]; }
    
    void build(int l, int r, int rt) {
        tag[rt] = -1; rev[rt] = 0;
        if (l == r) return;
        int mid = (l+r)>>1;
        build(l, mid, rt<<1);
        build(mid+1, r, rt<<1|1);
    }
    
    void pushdown(int l, int r, int rt) {
        int mid = (l+r)>>1;
        if (tag[rt] != -1) {
            tag[rt<<1] = tag[rt<<1|1] = tag[rt];
            rev[rt<<1] = rev[rt<<1|1] = 0;
            sum[rt<<1] = tag[rt] ? mid-l+1 : 0;
            sum[rt<<1|1] = tag[rt] ? r-mid : 0;
            tag[rt] = -1;
        }
        if (rev[rt]) {
            if (tag[rt<<1] != -1) tag[rt<<1] ^= 1;
            else rev[rt<<1] ^= 1;
            if (tag[rt<<1|1] != -1) tag[rt<<1|1] ^= 1;
            else rev[rt<<1|1] ^= 1;
            sum[rt<<1] = mid-l+1 - sum[rt<<1];
            sum[rt<<1|1] = r-mid - sum[rt<<1|1];
            rev[rt] = 0;
        }
    }
    
    void update(int t, int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (l == r) { // 叶子直接修改
                if (t == 1) sum[rt] = 1;
                else if (t == 2) sum[rt] = 0;
                else sum[rt] ^= 1;
            } else if (t == 1 || t == 2) { // 赋值操作
                tag[rt] = t-1; rev[rt] = 0; // t=1->tag=1, t=2->tag=0
                sum[rt] = t==1 ? r-l+1 : 0;
            } else { // 翻转操作
                if (tag[rt] != -1) tag[rt] ^= 1;
                else rev[rt] ^= 1;
                sum[rt] = r-l+1 - sum[rt];
            }
            return;
        }
        pushdown(l, r, rt);
        int mid = (l+r)>>1;
        if (L <= mid) update(t, L, R, l, mid, rt<<1);
        if (R > mid) update(t, L, R, mid+1, r, rt<<1|1);
        pushup(rt);
    }
    
    int query(int l, int r, int rt) {
        if (l == r) return l;
        pushdown(l, r, rt);
        int mid = (l+r)>>1;
        if (sum[rt<<1] < mid-l+1) return query(l, mid, rt<<1); // 左子树有0
        return query(mid+1, r, rt<<1|1);
    }
    
    signed main() {
        int n = 0, m; cin >> m;
        q[++n] = 1; // 离散化数组必须含1
        for (int i = 1; i <= m; i++) {
            cin >> t[i] >> l[i] >> r[i];
            q[++n] = l[i]; q[++n] = r[i]; q[++n] = r[i]+1; // 关键点
        }
        sort(q+1, q+n+1);
        n = unique(q+1, q+n+1) - q - 1;
        build(1, n, 1);
        for (int i = 1; i <= m; i++) {
            int L = lower_bound(q+1, q+n+1, l[i]) - q;
            int R = lower_bound(q+1, q+n+1, r[i]) - q;
            update(t[i], L, R, 1, n, 1);
            cout << q[query(1, n, 1)] << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
  - **离散化处理**：收集所有操作端点+1和r+1，排序去重后映射到[1,n]。
  - **线段树构建**：初始化tag=-1（无赋值），rev=0（无翻转）。
  - **更新操作**：赋值操作（t=1/2）直接设标记；翻转操作（t=3）根据当前标记转换（赋值标记取反，无则设翻转标记）。
  - **标记下传**：先处理赋值标记（覆盖子树），再处理翻转标记（转换子树状态）。
  - **MEX查询**：在线段树二分搜索，左子树不满则向左，否则向右。

---
<code_intro_selected>
以下精选题解的代码亮点解析：
</code_intro_selected>

**题解一：珂朵莉树（Unnamed114514）**
* **亮点**：STL set管理区间碎片，代码简洁高效。
* **核心代码片段**：
    ```cpp
    struct node { ll l, r; mutable bool v; };
    set<node> s;
    void assign(ll l, ll r, bool v) {
        auto itr = split(r+1), itl = split(l);
        s.erase(itl, itr);
        s.insert({l, r, v});
    }
    void rever(ll l, ll r) {
        auto itr = split(r+1), itl = split(l);
        for (auto it = itl; it != itr; it++) it->v ^= 1;
    }
    ll query() {
        for (auto& x : s) if (!x.v) return x.l;
        return s.rbegin()->r + 1;
    }
    ```
* **代码解读**：
  > `split(pos)`将包含pos的区间分裂为两部分，返回后半部分的迭代器。`assign`先分裂出[l,r]区间，删除旧区间后插入新状态区间。`rever`遍历区间碎片逐个翻转状态。`query`遍历set找首个v=0的区间左端点。
* 💡 **学习笔记**：珂朵莉树将区间视为对象管理，避免显式树结构，但碎片增多会降低效率。

**题解二：线段树（Acestar）**
* **亮点**：双重标记处理逻辑严谨，离散化完整。
* **核心代码片段**：
    ```cpp
    void update(int t, int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            // ... 赋值和翻转的状态转换逻辑
        }
        pushdown(l, r, rt); // 关键：下传标记
        // 递归更新子树
    }
    void pushdown(...) {
        if (tag[rt] != -1) { // 优先处理赋值标记
            // 清空子节点翻转标记，设赋值标记
        }
        if (rev[rt]) { // 再处理翻转
            // 转换子节点状态（赋值则取反，翻转则抵消）
        }
    }
    ```
* **代码解读**：
  > 更新时若区间完整则直接修改当前节点状态，否则下传标记后递归。下传时**先处理赋值标记**（覆盖子树原有状态），再处理翻转标记（需考虑子树当前标记状态）。这种分层处理确保状态一致性。
* 💡 **学习笔记**：标记下传顺序是多重标记设计的核心，赋值操作具有"重置"特性应优先处理。

**题解三：平衡树（Froggy）**
* **亮点**：FHQ Treap动态开点处理大值域。
* **核心代码片段**：
    ```cpp
    void split(int k, int data, int &l, int &r) { ... } // 按值分裂
    int merge(int l, int r) { ... } // 合并子树
    void New(ll pos) { // 动态开点
        int k = mp.lower_bound(pos)->second;
        split(k, pos, l, r); // 分裂出pos位置
        // 创建新节点并合并
    }
    ```
* **代码解读**：
  > `split`和`merge`实现平衡树核心操作。`New(pos)`在pos位置开点：找到包含pos的节点，分裂为[L,pos-1]、[pos,pos]、[pos+1,R]三个节点，用新节点[pos,pos]替换原节点。动态开点避免离散化，直接处理原始坐标。
* 💡 **学习笔记**：平衡树通过分裂/合并维护区间，动态开点适合值域巨大的在线问题。

-----

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为直观理解算法，我设计了"像素探险家"动画方案。采用FC红白机复古风格，通过网格动态展示线段树操作，让算法过程如游戏般清晰可见！
</visualization_intro>

  * **动画演示主题**：`"像素探险家"在线段树森林中寻找MEX宝藏`

  * **核心演示内容**：离散化后的值域映射为像素网格，三种操作对应不同颜色变化，查询时探险家路径追踪MEX位置。

  * **设计思路简述**：8位像素风降低认知负担；音效强化操作反馈；游戏化关卡提升参与感。动画同步显示线段树节点状态，帮助理解标记传递。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 16色调色板（灰：0，绿：1，红：翻转区）
          * 网格画布（行：离散区间，列：线段树节点）
          * 控制面板（开始/暂停/单步/速度条）

    2.  **操作可视化**：
          - **操作1（填充）**：点击区间→绿色扩散动画+"叮"声效
          - **操作2（擦除）**：点击区间→灰色扩散动画+"叮"声效
          - **操作3（翻转）**：点击区间→绿灰闪烁转换+"哔"声效
          - **数据结构同步**：右侧显示线段树，当前操作节点高亮

    3.  **标记下传演示**：
          * 赋值操作：子节点瞬间变色（覆盖原有状态）
          * 翻转操作：子节点颜色反转（绿↔灰），若遇赋值标记则显示转换过程

    4.  **MEX查询过程**：
          - 像素小人从左端出发，沿线段树二分路径移动
          - 路径显示：`左子树? → 未满→左移 : 右移`
          - 找到MEX时像素闪烁+胜利音效，显示`MEX=值`

    5.  **游戏化元素**：
          - 每完成一次操作解锁"关卡"，连续正确速度加快
          - 积分系统：快速完成+10分，错误-5分
          - "AI演示"模式：自动展示三种操作组合，如解密游戏

  * **技术实现**：HTML5 Canvas绘制网格，JavaScript驱动动画，Web Audio API添加音效。轻量化设计（单文件<100KB）。

<visualization_conclusion>
通过像素化动态演示，我们不仅直观看到算法流程，更在游戏化体验中理解离散化、标记下传等核心概念，让算法学习如探险般有趣！
</visualization_conclusion>

-----

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，可尝试以下相似问题巩固技能：
</similar_problems_intro>

  * **通用思路迁移**：区间赋值/翻转操作模型适用于：
      1. 动态统计区间特征（如CF915E Physical Education Lessons）
      2. 位运算维护（如P2574 XOR的艺术）
      3. 颜色段管理（如P1558 色板游戏）

  * **练习推荐 (洛谷)**：
    1.  **P2574 - XOR的艺术**  
        🗣️ **推荐理由**：纯区间翻转+查询，巩固标记处理技巧，学会维护异或状态。
    2.  **CF915E - Physical Education Lessons**  
        🗣️ **推荐理由**：大值域区间开关灯，直接应用本题离散化+线段树解法。
    3.  **P1558 - 色板游戏**  
        🗣️ **推荐理由**：区间染色+颜色查询，练习复杂状态维护，提升线段树设计能力。

-----

## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中的调试经验尤其珍贵：
</insights_intro>

> **参考经验**：多位作者提到离散化遗漏r+1导致WA，或标记处理错误引发死循环。

> **点评**：这提醒我们：1) 离散化必须包含所有关键点（1和r+1）；2) 标记下传需严格测试边界条件。建议编码时先小数据模拟，逐步验证标记传递。

-----

<conclusion>
本次"MEX Queries"分析就到这里。记住：离散化处理是空间压缩的利器，标记设计是线段树的灵魂。勤练相似题目，你将成为区间操作的大师！下次挑战再见！💪
</conclusion>

-----

---
处理用时：280.15秒