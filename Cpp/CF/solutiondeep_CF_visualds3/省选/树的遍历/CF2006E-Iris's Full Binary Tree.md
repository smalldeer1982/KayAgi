# 题目信息

# Iris's Full Binary Tree

## 题目描述

Iris likes full binary trees.

Let's define the depth of a rooted tree as the maximum number of vertices on the simple paths from some vertex to the root. A full binary tree of depth $ d $ is a binary tree of depth $ d $ with exactly $ 2^d - 1 $ vertices.

Iris calls a tree a  $ d $ -binary tree if some vertices and edges can be added to it to make it a full binary tree of depth $ d $ . Note that any vertex can be chosen as the root of a full binary tree.

Since performing operations on large trees is difficult, she defines the binary depth of a tree as the minimum $ d $ satisfying that the tree is $ d $ -binary. Specifically, if there is no integer $ d \ge 1 $ such that the tree is $ d $ -binary, the binary depth of the tree is $ -1 $ .

Iris now has a tree consisting of only vertex $ 1 $ . She wants to add $ n - 1 $ more vertices to form a larger tree. She will add the vertices one by one. When she adds vertex $ i $ ( $ 2 \leq i \leq n $ ), she'll give you an integer $ p_i $ ( $ 1 \leq p_i < i $ ), and add a new edge connecting vertices $ i $ and $ p_i $ .

Iris wants to ask you the binary depth of the tree formed by the first $ i $ vertices for each $ 1 \le i \le n $ . Can you tell her the answer?

## 说明/提示

In the first test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/7f900739a2145e9bd80715ede4260b35ba51b9fd.png)- The tree consisting of the vertex $ 1 $ has the binary depth $ 1 $ (the tree itself is a full binary tree of depth $ 1 $ ).
- The tree consisting of the vertices $ 1 $ and $ 2 $ has the binary depth $ 2 $ (we can add the vertex $ 3 $ to make it a full binary tree of depth $ 2 $ ).
- The tree consisting of the vertices $ 1 $ , $ 2 $ and $ 3 $ has the binary depth $ 2 $ (the tree itself is a full binary tree of depth $ 2 $ ).

In the second test case, the formed full binary tree after adding some vertices to the tree consisting of $ n $ vertices is shown below (bolded vertices are added):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/90faca99e1781d73f69b5b60a32aa2a2da38a68c.png)The depth of the formed full binary tree is $ 4 $ .

In the fifth test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/2c0d039efae462812828b42368688f46ffc8b41e.png)It can be proved that Iris can't form any full binary tree by adding vertices and edges, so the binary depth is $ -1 $ .

## 样例 #1

### 输入

```
7
3
1 1
6
1 2 3 4 5
7
1 1 3 2 5 1
10
1 1 2 1 4 2 4 5 8
10
1 1 3 1 3 2 2 2 6
20
1 1 2 2 4 4 5 5 7 6 8 6 11 14 11 8 13 13 12
25
1 1 3 3 1 5 4 4 6 8 11 12 8 7 11 13 7 13 15 6 19 14 10 23```

### 输出

```
1 2 2 
1 2 2 3 3 4 
1 2 2 3 3 4 4 
1 2 2 3 3 3 4 4 5 5 
1 2 2 3 3 4 4 4 -1 -1 
1 2 2 3 3 4 4 4 4 5 5 5 5 6 6 6 6 6 6 7 
1 2 2 3 3 4 4 4 4 5 5 6 6 6 6 6 7 7 7 7 7 8 8 8 8```

# AI分析结果


### 💡 Kay的C++算法解析：Iris's Full Binary Tree 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：动态树维护 + 线段树优化 + 树形结构分析  
🗣️ **初步分析**：
> 想象你在玩一款像素风树形建造游戏，每次添加新节点时，需要实时计算当前树的"二进制深度"——即通过添加节点能形成的最小满二叉树深度。核心挑战在于：
> - **动态维护树的直径**：每次加节点后，树的"最长枝干"（直径）可能变化
> - **中心点漂移**：树的中心（平衡点）会随直径移动，影响距离计算
> - **度数监狱**：任何节点度数≥4时立即判定为不可能（后续答案全-1）

可视化设计思路：
> 采用《塞尔达传说》式的8-bit像素风格：
> 1. **树形沙盘**：左侧显示生长中的树，节点用不同颜色像素块表示（绿色=普通，红色=度数超限）
> 2. **直径追踪**：当前直径端点用闪烁金边标记，中心点用十字光标显示
> 3. **线段树仪表盘**：右侧用堆叠像素方块实时显示线段树状态，数值变化伴随"滴答"音效
> 4. **动态演示**：按空格键进入"AI建造模式"，自动逐步演示算法过程，伴随不同操作音效：
>    - 节点加入：短促"叮"声
>    - 直径扩展：上升音阶
>    - 中心移动：滑动音效
>    - 度数超限：警报声

---

#### 2. 精选优质题解参考
**题解一（Conan15）**  
* **点评**：思路如水晶般通透！将动态直径维护比作"双锚点漂移"，通过精妙的`move()`函数处理中心移动。代码中：
  - 直径端点`(a,b)`和半径`r`的维护堪称典范
  - 线段树区间更新处理子树加减（`add(1, l, r, ±1)`）展现扎实功底
  - 边界处理严谨（度数≥4时立即锁定后续答案为-1）
  > 💡 学习重点：动态树维护中"中心漂移"的数学证明与工程实现

**题解二（DaiRuiChen007）**  
* **点评**：算法手术刀般精准！亮点在于：
  - 用DFS序+ST表闪电计算LCA距离
  - 中心移动时`nxt()`函数定向跳转配合子树区间更新
  - 代码简洁如诗（仅83行解决5e5数据）
  > 💡 学习重点：如何用DFS序将树形问题转化为区间操作

---

#### 3. 核心难点辨析与解题策略
1. **难点1：直径的动态维护**  
   * **分析**：新节点加入时，直径可能扩展。关键证明：新直径端点必为{原端点, 新节点}的子集
   * 💡 学习笔记：维护双端点`(a,b)`，计算`max(dis(a,new), dis(b,new))`决定是否更新

2. **难点2：中心漂移的区间更新**  
   * **分析**：中心移动导致子树内/外距离值±1。通过DFS序映射为线段树区间操作：
   ```math
   ∀u ∈ Subtree(v): dist(u) ← dist(u) ± 1
   ```
   * 💡 学习笔记：DFS序是树形结构的"条形码"，使子树操作转化为连续区间

3. **难点3：度数监狱的实时监控**  
   * **分析**：满二叉树要求：
   - 根节点度数≤2（像素图示：👑→最多两分枝）
   - 其他节点≤3（图示：🟢→最多三分枝）
   * 💡 学习笔记：用`deg[]`数组实时监控，首次出现≥4时立即熔断

✨ **解题技巧总结**  
- **锚点追踪法**：用`(a,b)`双指针标记直径端点  
- **子树快照**：DFS序+线段树实现O(log n)区间更新  
- **熔断机制**：度数超限时立即终止后续计算  

---

#### 4. C++核心代码实现赏析
**本题通用核心实现参考**  
```cpp
// 精简版框架 (综合两题解精华)
const int N = 5e5+5, INF = 0x3f3f3f3f;
int a, b, r; // 直径端点 & 半径
vector<int> G[N];      // 树结构
int L[N], R[N], dep[N];// DFS序 & 深度

struct SegmentTree {    // 魔法线段树
    void add(int l, int r, int v); // 区间加减
    void set(int u, int v);        // 单点赋值
    int query();                   // 全局最小值
} T;

void update_diameter(int x) { // 动态维护直径
    int da = dis(a,x), db = dis(b,x);
    if(max(da,db) > dis(a,b)) 
        (da>db) ? b=x : a=x; // 更新端点
}

int main() {
    // 初始化树结构 & DFS序
    for(int i=2; i<=n; ++i) {
        if(deg[fa]++ >= 3) meltdown(); // 熔断检测
        update_diameter(i);            // 更新直径
        T.set(i, max(dis(i,a),dis(i,b)));// 更新距离
        ans = T.query() + 1;           // 二进制深度
    }
}
```

**题解一核心片段赏析**  
```cpp
// Conan15的直径更新魔法
void move(int &a, int x) {
    if(x在a的子树内) {
        T.add(1, n, +1);   // 全局+1
        a = x的某个子孙;    // 中心下移
        T.add(a的子树, -1); // 局部抵消
    } else { 
        T.add(a的子树, +1);
        a = 父节点;        // 中心上移
    }
}
```
> **代码解读**：中心移动如电梯运作  
> - 当新节点在下方：全局抬升后对移动子树局部回调  
> - 当新节点在侧面：当前子树增重后中心上浮  
> 💡 学习笔记：区间操作需保持"能量守恒"

**题解二核心片段赏析**  
```cpp
// DaiRuiChen007的LCA闪电战
int dis(int x,int y) {
    int a = LCA(x,y);            // ST表跳跳乐
    return dep[x]+dep[y]-2*dep[a];// 几何距离公式
}
```
> **代码解读**：ST表预处理实现O(1)LCA查询  
> 💡 学习笔记：`dep[u]`是节点的"海拔高度"，LCA即"山脉交汇点"

---

### 5. 算法可视化：像素动画演示  
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/7f900739a2145e9bd80715ede4260b35ba51b9fd.png)  
* **主题**：《二叉树建造大师》8-bit模拟  
* **核心交互**：  
  1. **树形沙盘**（左）  
     - 节点加入：像素方块从天而降  
     - 直径显示：金边连接端点  
     - 中心标记：十字光标闪烁  

  2. **线段树控制台**（右）  
     - 数值更新：方块高度=存储值  
     - 区间操作：色块波浪式流动  

  3. **音效系统**  
     | 事件 | 音效 | 可视化反馈 |
     |---|---|---|
     | 加节点 | 清脆"叮"声 | 绿色像素弹出 |
     | 中心移动 | 滑动声 | 十字光标滑行 |
     | 直径扩展 | 上升音阶 | 金边闪烁 |
     | 度数超限 | 警报声 | 节点变红爆裂 |

* **AI演示模式**：  
  按A键触发自动建造，速度滑块控制演示节奏，关键步骤自动暂停+文字提示：
  > "中心移动！子树A距离值全体+1"

---

### 6. 拓展练习与相似问题  
* **思维迁移**：  
  1. 动态直径维护 → 网络延迟监测  
  2. DFS序区间操作 → 子树权重统计  
  3. 度数约束 → 化学分子结构验证  

* **洛谷推荐**：  
  1. **P1099 树网的核**  
     🗣️ 巩固树的直径与中心应用  
  2. **P2146 软件包管理器**  
     🗣️ 掌握DFS序+线段树的魔力  
  3. **P2680 运输计划**  
     🗣️ 进阶版直径问题+二分答案  

---

### 7. 学习心得与经验分享  
> **来自Conan15的调试经验**：  
> "中心移动时区间更新方向极易出错，建议在纸上画出子树分区图"  
>  
> **Kay的总结**：  
> 调试树形问题要善用"纸笔模拟法"，将抽象移动具象化为：
> ```
> 中心移动 = 电梯运行 + 跷跷板平衡
> 线段树更新 = 水池注水/排水
> ```

--- 
树形问题犹如培育像素花园，每次扩展都需精心计算。掌握动态维护的奥义，你也能成为算法建筑师！🚀

---
处理用时：260.87秒