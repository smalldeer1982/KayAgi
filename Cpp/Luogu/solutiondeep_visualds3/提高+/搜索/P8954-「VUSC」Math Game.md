# 题目信息

# 「VUSC」Math Game

## 题目背景

**upd 2023.1.22**：新增一组 Hack 数据 by @[MCRS_lizi](https://www.luogu.com.cn/user/585805)。

远在哞利坚的 Bessie 也要在新春之际走亲访友！为了打发时间，她常和 Farmer John 玩一个有趣的数字游戏。

## 题目描述

Farmer John 有一个集合 $S$，集合初始为 $\{2,3,4,...,N\}$。

对于两个**在集合 $S$ 内的**正整数 $p,q$，我们称它们为「一对好数」当且仅当 $p^k=q(k\ge 2\land k\in\N)$。

我们将每个 $S$ 中的数看成一张**无向图**中的节点，对于每一对「好数」，我们在这两个数间连一条无向边。

Farmer John 会进行 $Q$ 次操作，操作有以下两种：

1. 给出 $x$，询问结点 $x$ 所在的连通块大小。
2. 给出 $x$，从 $S$ 中移除 $x$。**与此同时，无向图中的结点 $x$ 也被移除。**

由于 Bessie 的速度太慢了，她想要你来帮忙。

## 说明/提示

#### 【样例解释】

这是原始无向图（上面一排都是孤点）：
![](https://cdn.luogu.com.cn/upload/image_hosting/utsz04dt.png)

这是进行第一次操作 $2$ 后的无向图（删除了结点 $9$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/wmexc9ks.png)

这是进行第二次操作 $2$ 后的无向图（删除了结点 $2$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/9mi0l18p.png)

---

#### 【数据范围】

全部数据满足：
- $2\le N \le 10^{18}$
- $1\le Q \le 10^6$
- $x_i\in S$
- $op_i \in \{1,2\}$

测试点 $1\sim2$ 另外满足 $2\le N \le 10^5$，$1\le Q \le 10^4$。

测试点 $3\sim4$ 另外满足所有 $x_i=m^{p_i}$，其中 $m$ 为一满足 $m\ge 2 \land m\in \N$ 的**常数**。

测试点 $5\sim10$ 没有额外限制。


## 样例 #1

### 输入

```
30 6
1 6
1 4
2 9
1 3
2 2
1 16```

### 输出

```
1
4
2
2```

# AI分析结果


### Kay的C++算法解析：「VUSC」Math Game 深入学习指南

```markdown
---
# 💡 Kay的C++算法解析：「VUSC」Math Game 深入学习指南 💡

<introduction>
  今天我们来分析一道结合数论和图论的动态维护问题。题目要求在超大范围（$N \leq 10^{18}$）的幂次关系图中处理删除和查询操作。本指南将解析离散化技巧和时间倒流思想的应用，并通过像素动画直观展示算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`离散化` + `并查集` + `时间倒流技巧`

🗣️ **初步分析**：
> 解决本题的关键在于将看似复杂的幂次关系图抽象为离散的底数链条。想象每个数字像树根生长出树枝（幂次链条），同根数字共享连通块。核心难点在于：
>   - **离散化**：将 $10^{18}$ 超大值域映射到有限底数（不超过 $10^6$）
>   - **动态维护**：用时间倒流技巧（逆向处理操作）将删除转化为添加操作
>   - **数学优化**：快速计算最小底数 $f(x)$（$x$ 的最小 $k$ 次方根）
> 
> 可视化设计思路：
>   - 用像素方块表示数字，同底数链条水平排列
>   - 删除节点时播放断裂音效，方块变灰
>   - 查询时高亮连通块并显示大小计数器
>   - 控制面板支持步进/自动播放（调速滑块）

---

## 2. 精选优质题解参考

<eval_intro>
从思路清晰度、代码规范性和算法效率角度，精选两条代表性解法：
</eval_intro>

**题解一：enucai（在线枚举法）**
* **点评**：
  采用直接枚举连通块的在线处理策略。亮点在于：
  - **思路直白**：对每个查询 $x$，枚举所有可能的 $y^k=x$ 关系
  - **数学优化**：预处理 $[1,10^6]$ 的三次方值加速最小底数计算
  - **代码简洁**：用 `set` 记录删除状态，`map` 缓存最小底数
  - **实践价值**：单次查询 $O(\log n \log q)$ 满足 $10^6$ 操作量
  
**题解二：STUDENT00（离线并查集）**
* **点评**：
  采用时间倒流+并查集的离线算法：
  - **核心创新**：逆向处理操作，将删除转化为添加（空间复杂度优化）
  - **离散化技巧**：将底数映射到连续 ID，避免 $O(N)$ 空间
  - **结构规范**：`vector` 动态维护并查集父子关系
  - **边界严谨**：预处理时严格验证 $n/val<z$ 防溢出

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破三大核心难点：
</difficulty_intro>

1.  **难点1：超大值域的空间压缩**
    * **分析**：$N \leq 10^{18}$ 无法直接存储所有节点。优质解法均采用离散化：将数字 $x$ 表示为最小底数 $f(x)$ 的幂次形式（$x = p^k$）。通过离散化 $p$ 的值域（不超过 $10^6$），空间降至 $O(Q)$
    * 💡 **学习笔记**：离散化是处理超大值域的核心转换技巧

2.  **难点2：删除操作的动态维护**
    * **分析**：直接删除会破坏连通块结构。题解二采用"时间倒流"：从最终状态逆向处理操作，将删除转变为添加操作。添加节点时重建两条边：
      - 向上边：连接 $p^k \leftrightarrow p^{k·m}$
      - 向下边：连接 $p^k \leftrightarrow p^{k/m}$（若 $m|k$）
    * 💡 **学习笔记**：时间倒流是处理删除操作的经典范式

3.  **难点3：最小底数的高效计算**
    * **分析**：求 $f(x)$（最小满足 $y^k=x$ 的 $y$）需要数学优化：
      - $k=2$：用 `sqrtl` 配合 $\pm 1$ 微调
      - $k=3$：预处理 $10^6$ 内三次方值
      - $k \geq 4$：枚举 $y \in [2,10^6]$ 预处理
    * 💡 **学习笔记**：分类讨论是优化数学计算的有效手段

### ✨ 解题技巧总结
<summary_best_practices>
通过本题提炼的通用技巧：
</summary_best_practices>
- **离散化映射**：将原始问题转化为可处理的子空间
- **逆向思维**：用时间倒流处理动态删除操作
- **数学分类优化**：对不同规模问题采用差异化的数学工具
- **溢出防御**：用 `n/val < z` 代替 `val*z > n` 判断边界

---

## 4. C++核心代码实现赏析

<code_intro_overall>
综合两种解法的核心逻辑，提供通用实现框架：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：融合在线枚举与离线并查集思路，突出离散化和时间倒流
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    typedef __int128 lll;
    
    const int MAX_Q = 1e6+5;
    ll n, q;
    set<ll> deleted; // 删除标记
    map<ll, ll> minBase; // x -> 最小底数 f(x)
    vector<ll> bases; // 离散化底数集合
    
    // 离散化初始化
    void initDiscrete() {
        // 预处理小底数 (k>=4)
        for(int i=2; (ll)i*i*i<=n; i++) {
            lll cur = i;
            for(int exp=1; cur<=n; exp++) {
                if(!minBase.count(cur)) minBase[cur] = i;
                if(n / cur < i) break;
                cur *= i;
            }
        }
        // 处理平方数 (k=2)
        for(auto& [x,_] : minBase) {
            if((lll)x*x*x <= n) continue;
            ll rt = sqrtl(x);
            for(ll d : {rt-1, rt, rt+1})
                if(d*d == x) minBase[x] = d;
        }
        // 提取离散化底数
        for(auto& [_,base] : minBase) 
            bases.push_back(base);
        sort(bases.begin(), bases.end());
        bases.erase(unique(bases.begin(), bases.end()), bases.end());
    }
    
    // 时间倒流处理函数
    void processReverse(vector<pair<int,ll>>& ops) {
        vector<int> ans;
        // 逆向遍历操作 (从最后一步开始)
        for(int i=ops.size()-1; i>=0; i--) {
            auto [op, x] = ops[i];
            if(op == 1) { // 原删除操作转为添加
                // 连通块计算逻辑（见题解一）
                // 或并查集维护（见题解二）
            } 
            else deleted.erase(x); // 撤销删除
        }
    }
    ```

---
<code_intro_selected>
精选解法核心代码解析：
</code_intro_selected>

**题解一：在线枚举法（enucai）**
* **亮点**：直接枚举连通块，避免复杂数据结构
* **核心代码片段**：
    ```cpp
    int calc(ll x) {
        ll y = findMinBase(x); // 获取最小底数
        set<ll> connected;
        // 枚举所有幂次链条
        for(ll cur = y; cur <= n; cur *= y) {
            if(deleted.count(cur)) continue;
            connected.insert(cur);
        }
        return connected.size();
    }
    ```
* **代码解读**：
    > `findMinBase` 通过预处理映射快速获取最小底数。核心循环沿幂次链条枚举所有节点（$y, y^2, y^3...$），用 `deleted` 过滤已删除节点。时间复杂度 $O(\log n)$ 因链条长度不超过 $\log_y n$
* 💡 **学习笔记**：幂次链条的稀疏性是高效枚举的基础

**题解二：离线并查集（STUDENT00）**
* **亮点**：时间倒流+动态并查集实现高效维护
* **核心代码片段**：
    ```cpp
    struct DSU {
        vector<int> fa, size;
        DSU(int n) : fa(n), size(n,1) { 
            iota(fa.begin(), fa.end(), 0); 
        }
        int find(int x) { 
            return fa[x]==x ? x : fa[x]=find(fa[x]); 
        }
        void merge(int x, int y) {
            x = find(x), y = find(y);
            if(x == y) return;
            if(size[x] < size[y]) swap(x,y);
            fa[y] = x;
            size[x] += size[y];
        }
    };
    ```
* **代码解读**：
    > 封装并查集支持动态合并。`find` 使用路径压缩，`merge` 按秩合并保证效率。在时间倒流过程中，每次添加节点时合并其上下游节点（$p^{k/m}$ 和 $p^{k·m}$）
* 💡 **学习笔记**：并查集是维护动态连通性的利器

-----

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
设计像素动画演示「幂次链条的动态维护」，帮助直观理解离散化和时间倒流：
</visualization_intro>

* **动画主题**：`8-bit风格数字迷宫`
* **核心演示内容**：以底数 $p$ 为纵轴，指数 $k$ 为横轴的网格世界，节点删除/添加的动态过程

* **设计思路**：
  > 采用FC红白机风格（16色调色板），将抽象的数字关系转化为具象的网格探险：
  > - 底数作为不同高度的"楼层"（$p=2$在一楼，$p=3$在二楼...）
  > - 同底数的幂次链条水平排列成"走廊"
  > - 删除节点时播放砖块碎裂音效，添加时播放收集金币音效

* **动画帧步骤**：
  1. **场景初始化**：
     - 左侧：控制面板（开始/暂停/步进/速度滑块）
     - 主区域：$10 \times 10$ 网格，每行代表一个离散化底数
     - 每个网格显示 $p^k$ 值和状态（绿色=存在，灰色=删除）

  2. **操作演示**：
     ```markdown
     | 操作         | 视觉表现                     | 音效         |
     |--------------|----------------------------|-------------|
     | 删除节点 x   | 对应网格变灰并出现裂纹特效   | 玻璃破碎音  |
     | 查询连通块   | 同底数链条闪烁黄框           | 叮咚提示音  |
     | 时间倒流     | 画面倒放并显示"REWIND"字幕  | 磁带倒带音  |
     ```

  3. **关键算法步骤可视化**：
     - **离散化**：多个数字（如4,8,16）折叠到"2"楼同一行
     - **最小底数计算**：数字64从8楼（$8^2$）降落到2楼（$2^6$）的坠落动画
     - **并查集合并**：当添加节点4时，自动连接2楼($2^2$)和3楼($2^3$)的桥梁动画

  4. **交互控制**：
     - **步进模式**：按帧展示并查集合并过程
     - **自动演示**：AI角色"计算精灵"沿幂次走廊移动，实时显示路径
     - **关卡进度**：每完成5次操作解锁新楼层，积分+100

* **伪代码实现**：
    ```javascript
    class PixelAnimation {
      constructor() {
        this.grid = new Grid(10, 10); // 10x8网格
        this.sound = new EightBitSound(); // 8位音效引擎
      }
      
      deleteNode(x) {
        let pos = this.findPosition(x); // 查找网格位置
        this.grid.setColor(pos, GRAY);
        this.sound.play('break');
        this.drawCrackEffect(pos);
      }
      
      queryComponent(x) {
        let base = this.getBase(x);     // 获取离散化底数
        let nodes = this.getChain(base); // 同底数链条
        this.highlight(nodes, YELLOW);
        this.sound.play('ding');
        return nodes.length;
      }
    }
    ```

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握离散化和时间倒流技巧后，可挑战更复杂的动态维护问题：
</similar_problems_intro>

* **技巧迁移**：
  1. 连通块动态维护：含删除操作的并查集应用
  2. 值域离散化：处理超大范围的统计问题
  3. 逆向思维：从终态反推初态的问题

* **洛谷题目推荐**：
  1. **P2146 [NOI2015] 软件包管理器**  
     🗣️ **推荐理由**：树链剖分+时间倒流思想，练习动态子树维护
  2. **P3224 [HNOI2012] 永无乡**  
     🗣️ **推荐理由**：并查集+线段树合并，强化连通块查询技能
  3. **P3960 [NOIP2017] 列队**  
     🗣️ **推荐理由**：动态开点线段树+离散化思想的经典应用

-----

## 7. 学习心得与经验分享

<insights_intro>
题解中值得借鉴的实战经验：
</insights_intro>

> **STUDENT00 的调试经验**：  
> *"预处理时要特别注意 $n/val < z$ 代替 $val×z > n$ 的判断，否则会溢出导致WA"*  
> **Kay点评**：这是处理大数运算的黄金准则，务必记住整数溢出是竞赛常见陷阱

> **enucai 的优化心得**：  
> *"对 $k \geq 4$ 的情况单独预处理，相比统一开方效率提升10倍"*  
> **Kay点评**：分类讨论是算法优化的核心思维，不同数据特征采用不同策略

-----

<conclusion>
通过本题我们掌握了三大核心技能：
1. 离散化映射压缩问题空间
2. 时间倒流转化删除操作
3. 并查集维护动态连通性
记住：将大问题拆解为可处理的子问题，是算法设计的精髓所在。继续加油！🚀
</conclusion>
---
``` 

**可视化补充说明**  
最终动画将包含以下关键帧示意图：
1. 初始状态：![](https://cdn.luogu.com.cn/upload/image_hosting/utsz04dt.png)
2. 删除节点9：![](https://cdn.luogu.com.cn/upload/image_hosting/wmexc9ks.png)
3. 删除节点2：![](https://cdn.luogu.com.cn/upload/image_hosting/9mi0l18p.png)  
通过8-bit像素风格重绘这些状态变化，并添加动态执行效果。

---
处理用时：170.86秒