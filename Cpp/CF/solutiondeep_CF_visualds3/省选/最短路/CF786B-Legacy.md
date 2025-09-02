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

今天我们来分析CF786B Legacy这道C++编程题。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`线段树优化建图` + `最短路算法`

🗣️ **初步分析**：
> 解决"Legacy"这道题，关键在于运用**线段树优化建图**技术。简单来说，这个技巧就像建造一座"虚拟立交桥"，将复杂的区间连边转化为高效的对数级别操作。在本题中，我们通过两棵线段树（入树和出树）将点对区间、区间对点的连边操作优化为O(log n)级别的边数。

- 题解核心思路是通过**两棵方向相反的线段树**处理区间操作：入树（子→父）处理区间向点连边，出树（父→子）处理点向区间连边，叶子节点相互连接打通两棵树。
- 难点在于**理解虚拟节点的作用和连边方向**，可视化设计将高亮线段树结构、连边过程（点对点/点对区间/区间对点）及最短路扩展路径。
- 像素动画采用**8位复古风格**，用蓝色/红色区分入树/出树，黄色表示叶子连接。关键操作时播放"滴"音效，最短路扩展时高亮当前节点，胜利时播放胜利音效。动画支持单步执行和调速滑块，帮助理解建图逻辑和Dijkstra执行过程。

---

## 2. 精选优质题解参考

<eval_intro>
从思路清晰度、代码规范性、算法优化度等维度，我为大家筛选了以下高质量题解（评分≥4★）：
</eval_intro>

**题解一（作者：tzc_wk）**
* **点评**：
  思路清晰度：★★★★★  
  用"出树"和"入树"的比喻形象解释线段树结构，图示展示建树过程（蓝/红边）和操作连边（橙/粉边）。推导过程从暴力建图痛点切入，自然引出优化方案。
  
  代码规范性：★★★★☆  
  使用`#define D 5e5`巧妙区隔两棵树，变量命名简洁（`leaf[]`表叶子）。建树函数`build`内联处理父子连接，`connect`函数封装区间查询。

  算法有效性：★★★★★  
  严格证明O((n+q)logn)边数复杂度，Dijkstra使用堆优化。亮点是图示解析两棵树协作原理，对理解虚拟节点作用帮助显著。

**题解二（作者：maoyiting）**
* **点评**：
  思路清晰度：★★★★☆  
  明确区分入树/出树概念（称"出树"为线段树A，"入树"为线段树B），配图展示操作2/3的连边方向。强调叶子节点共享特性。

  代码规范性：★★★★★  
  模块化设计：`build`建树、`modify`连边分离。`st`数组三维设计（维度/区间/类型）体现专业，内存计算精确（`MAXN<<2`）。

  实践价值：★★★★★  
  完整代码含详细注释，边界处理严谨（`l>=lx&&r<=rx`）。特别标注原图节点与叶子节点映射关系，避免索引混淆。

**题解三（作者：张鑫杰）**
* **点评**：
  思路清晰度：★★★★☆  
  独创"虚拟立交桥"比喻解释线段树作用，提出"错误连边示例"警示方向混淆问题。分层图示演示操作2/3。

  代码规范性：★★★★☆  
  动态分配节点编号（`cnt`控制），`treeIn/treeOut`数组明确。亮点是函数命名体现操作语义：`updateIn`处理入树连边。

  调试技巧：★★★★★  
  分享"叶子节点连接遗漏"调试经历，强调"两棵树叶子必须双向连接"，对实践者极具警示价值。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破以下关键难点，结合优质题解方案给出应对策略：
</difficulty_intro>

1.  **难点一：虚拟节点与真实节点的映射关系**
    * **分析**：线段树节点包含真实叶子节点（原图点）和虚拟区间节点。优质题解通过`leaf[]`数组（tzc_wk）或`a[]`数组（maoyiting）建立映射，操作时需区分三种连边：真实→虚拟、虚拟→虚拟、虚拟→真实。
    * 💡 **学习笔记**：虚拟节点是连通真实节点的"中转站"，映射关系决定算法正确性。

2.  **难点二：入树与出树的连边方向设计**
    * **分析**：入树（子→父0边）处理操作3（区间→点），出树（父→子0边）处理操作2（点→区间）。若方向颠倒会导致最短路计算错误（如张鑫杰错误示例图）。正确方向保证区间连边通过0边传递到目标点。
    * 💡 **学习笔记**："入树向上，出树向下"——子到父处理入，父到子处理出。

3.  **难点三：叶子节点的双向连接**
    * **分析**：两棵树叶子代表同一点，必须添加0权双向边（如maoyiting在`build`函数中实现）。遗漏将导致两棵树隔离，无法传递最短路信息。
    * 💡 **学习笔记**：叶子连接是打通两棵树的"桥梁"，缺少则信息无法互通。

### ✨ 解题技巧总结
<summary_best_practices>
通过对本题的总结，提炼以下核心技巧：
</summary_best_practices>
-   **技巧一：双树分工**  
    入树专攻区间到点（操作3），出树专攻点到区间（操作2），通过方向区分功能。
-   **技巧二：映射封装**  
    用`leaf[]`或`pos[]`数组封装原图点到线段树叶子的映射，避免索引混乱。
-   **技巧三：边界处理**  
    线段树查询时使用`[l, r]`完全覆盖判断（`l<=ql && r>=qr`），保证区间拆分的完备性。
-   **技巧四：内存预计算**  
    动态开点需预计算节点数（通常`4*n`），静态分配建议`MAXN<<3`避免越界。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
下面展示综合优质题解思路的通用实现，完整呈现线段树优化建图+Dijkstra的核心框架：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合tzc_wk、maoyiting思路，采用静态数组分配，两棵线段树共用建树函数，通过偏移量`D`区隔。
* **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5+5, D = 5e5;
const ll INF = 1e18;

vector<pair<int, int>> g[N<<1];
int n, q, s, cnt;
int leaf[N]; // 原图点i对应的叶子节点编号

struct SegNode { int l, r; } seg[N<<2];

void build(int k, int l, int r) {
    seg[k] = {l, r};
    if (l == r) {
        leaf[l] = k; // 叶子节点映射
        return;
    }
    int mid = (l+r)>>1;
    // 向左右儿子连0边（出树方向）
    g[k].push_back({k<<1, 0});
    g[k].push_back({k<<1|1, 0});
    // 左右儿子向父节点连0边（入树方向）
    g[(k<<1)+D].push_back({k+D, 0});
    g[(k<<1|1)+D].push_back({k+D, 0});
    build(k<<1, l, mid);
    build(k<<1|1, mid+1, r);
}

void connect(int k, int ql, int qr, int v, int w, int type) {
    int l = seg[k].l, r = seg[k].r;
    if (ql <= l && r <= qr) {
        if (type == 1) // 操作3：入树区间->目标点
            g[k+D].push_back({v, w});
        else // 操作2：源点->出树区间
            g[v].push_back({k, w});
        return;
    }
    int mid = (l+r)>>1;
    if (qr <= mid) connect(k<<1, ql, qr, v, w, type);
    else if (ql > mid) connect(k<<1|1, ql, qr, v, w, type);
    else {
        connect(k<<1, ql, mid, v, w, type);
        connect(k<<1|1, mid+1, qr, v, w, type);
    }
}

int main() {
    cin >> n >> q >> s;
    cnt = n; build(1, 1, n);
    
    // 两棵树叶子节点互连（0边）
    for (int i = 1; i <= n; i++) {
        g[leaf[i]].push_back({leaf[i]+D, 0});
        g[leaf[i]+D].push_back({leaf[i], 0});
    }

    while (q--) {
        int op, v, l, r, w;
        cin >> op;
        if (op == 1) {
            cin >> v >> l >> w;
            g[leaf[v]].push_back({leaf[l], w});
        } else {
            cin >> v >> l >> r >> w;
            if (op == 2) // 点->区间（连出树）
                connect(1, l, r, leaf[v], w, 0);
            else // 区间->点（连入树）
                connect(1, l, r, leaf[v], w, 1);
        }
    }

    // Dijkstra
    vector<ll> dis(N<<1, INF);
    priority_queue<pair<ll, int>> pq;
    dis[leaf[s]+D] = 0; // 从入树叶子开始
    pq.push({0, leaf[s]+D});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (-d != dis[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push({-dis[v], v});
            }
        }
    }
    
    for (int i = 1; i <= n; i++) 
        cout << (dis[leaf[i]] < INF ? dis[leaf[i]] : -1) << " ";
}
```
* **代码解读概要**：
  - **建图部分**：`build()`递归构造线段树，处理父子0边；`connect()`实现区间查询与连边
  - **初始化**：主函数中连接两棵树叶子节点
  - **操作处理**：操作1直接连边，操作2/3调用`connect`（type参数区分方向）
  - **最短路**：从入树叶子（`leaf[s]+D`）启用的Dijkstra

---
<code_intro_selected>
优质题解核心代码片段赏析：
</code_intro_selected>

**题解一（tzc_wk）**
* **亮点**：用常量`D`分隔两棵树，高效清晰
* **核心代码片段**：
```cpp
void connect(int k,int l,int r,int v,int w,int tp){
    if(l<=s[k].l&&s[k].r<=r){
        if(tp) g[k+D].push_back(pii(v,w));
        else g[v].push_back(pii(k,w));
        return;
    }
    // 递归连接子区间
}
```
* **代码解读**：`tp`参数区分操作类型（tp=1为操作3），`g[k+D]`访问入树节点。递归拆分区间时，通过比较区间边界决定递归方向。
* 💡 **学习笔记**：偏移量`D`是处理两棵树的经典技巧，避免节点编号冲突。

**题解二（maoyiting）**
* **亮点**：独立建树函数，内存规划精确
* **核心代码片段**：
```cpp
void build(int p,int l,int r){
    if(l==r){ a[l]=p; return; } // a[l]记录叶子
    // 入树：子->父；出树：父->子
    add(p,p<<1,0); add(p<<1+K,p+K,0);
    build(p<<1,l,mid); build(p<<1|1,mid+1,r);
}
```
* **代码解读**：`add`实现加边操作，`K`作为出树偏移量（类似`D`）。递归建树同时完成树内连边，结构清晰。
* 💡 **学习笔记**：独立建树函数提升代码复用性，结构体封装线段树节点增强可读性。

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
为直观理解线段树优化建图与Dijkstra，设计像素动画方案：
</visualization_intro>

* **主题**：**"双树寻径"** 复古像素游戏  
* **风格**：8-bit像素风（FC红白机），使用限定16色调色板

* **场景设计**：
  - **左面板**：入树（蓝色系），节点编号A1、A2...
  - **右面板**：出树（红色系），节点编号B1、B2...
  - **底部**：原图节点（绿色块），编号1~n
  - **控制台**：速度滑块/单步/暂停/重置按钮

* **关键帧流程**：
  1. **初始化阶段**（音效：电子启动音）
     - 像素动画展示两棵树构建过程：入树自底向上生长（子→父蓝边），出树自顶向下扩展（父→子红边）
     - 底部绿色块间出现黄色双向箭头（叶子连接）

  2. **操作演示**（音效：操作音效）
     - 操作1（点→点）：底部两点间出现紫色箭头，标注权值
     - 操作2（点→区间）：
        - 高亮源点（闪烁）→ 出树中覆盖区间节点变橙色 → 源点到这些节点连粉色边 → 出树向下传递（红边流动）
     - 操作3（区间→点）：
        - 入树中区间节点变蓝 → 连浅蓝边到目标点 → 入树向上传递（蓝边流动）

  3. **Dijkstra执行**（音效：脚步声/滴声）
     - 起点像素块亮起，扩展时播放"滴"声
     - 当前节点变为灰色，更新邻居距离（显示距离标签）
     - 路径发现时亮起金色路径，终点播放胜利音效

* **技术实现**：
  ```javascript
  // 伪代码：绘制线段树节点
  function drawNode(x, y, color, id) {
      ctx.fillStyle = color;
      ctx.fillRect(x, y, 16, 16); // 16x16像素块
      ctx.fillText(id, x+2, y+12); // 节点编号
  }
  
  // 操作2动画示例
  function animateOp2(v, l, r) {
      highlight(v, GREEN); // 高亮源点
      setTimeout(() => {
          const nodes = getSegNodes(l, r, OUT_TREE); // 获取区间覆盖节点
          nodes.forEach(node => {
              drawEdge(v, node, PINK, w); // 绘制连边
              playSound('connect'); // 连接音效
          });
      }, 500);
  }
  ```

<visualization_conclusion>
通过像素化演示，算法执行流程和数据流动变得直观可见，帮助理解虚拟节点如何优化连边。
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
线段树优化建图技巧可迁移至多种区间操作场景：
</similar_problems_intro>

* **通用思路迁移**：
  - 区间到区间连边（如洛谷P3588）
  - 动态更新后的连通性查询（如BZOJ5017炸弹）
  - 结合网络流建模（如CF1045A）

* **练习推荐（洛谷）**：
  1. **P3588 [POI2015]PUS**  
     🗣️ 强化线段树优化建图基础，增加约束条件
  2. **P5025 [SNOI2017]炸弹**  
     🗣️ 应用线段树建图后计算可达点数量
  3. **P6348 [COCI2007-2008#2] PASCAL**  
     🗣️ 结合拓扑排序与线段树建图

---

## 7. 学习心得与经验分享

<insights_intro>
题解中调试经验与技巧总结：
</insights_intro>

> **调试经验（张鑫杰）**：  
> "两棵树叶子节点未连接时，最短路始终为0。通过打印节点队列发现未扩展至原图点，添加双向连接后解决。"  
> **启示**：虚拟节点系统需严格验证连通性，可通过小规模数据遍历验证。

> **优化技巧（tzc_wk）**：  
> "D偏移量避免重编号，常量声明提升可读性"  
> **启示**：内存规划是线段树建图核心，静态分配需预留4倍空间。

---

<conclusion>
本次关于CF786B Legacy的解析就到这里。记住：线段树优化建图是处理区间连边的利器，掌握"双树分工+叶子连接"核心思想即可举一反三。下次挑战再见！🚀
</conclusion>
```

---
处理用时：191.63秒