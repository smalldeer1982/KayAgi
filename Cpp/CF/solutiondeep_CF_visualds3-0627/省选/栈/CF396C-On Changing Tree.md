# 题目信息

# On Changing Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is a vertex number $ 1 $ .

Initially all vertices contain number $ 0 $ . Then come $ q $ queries, each query has one of the two types:

- The format of the query: $ 1 $ $ v $ $ x $ $ k $ . In response to the query, you need to add to the number at vertex $ v $ number $ x $ ; to the numbers at the descendants of vertex $ v $ at distance $ 1 $ , add $ x-k $ ; and so on, to the numbers written in the descendants of vertex $ v $ at distance $ i $ , you need to add $ x-(i·k) $ . The distance between two vertices is the number of edges in the shortest path between these vertices.
- The format of the query: $ 2 $ $ v $ . In reply to the query you should print the number written in vertex $ v $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

Process the queries given in the input.

## 说明/提示

You can read about a rooted tree here: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 样例 #1

### 输入

```
3
1 1
3
1 1 2 1
2 1
2 2
```

### 输出

```
2
1
```

# AI分析结果



# 【算法分类】
树状数组/DFS序

---

# 【题解思路与核心难点】

**题目核心**：在树上处理子树区间修改与单点查询，要求高效处理每次操作的影响。

**关键思路**：将修改拆解为与深度无关的常数项和与深度相关的线性项，利用两个辅助数组分别维护。通过DFS序将子树转化为连续区间，实现O(logn)的区间更新与查询。

**算法步骤**：
1. **DFS预处理**：计算每个节点的入/出时间戳，将子树转化为连续区间。
2. **拆解公式**：每个修改 `x - k*(dep_u-dep_v)` 转化为 `(x+dep_v*k) - k*dep_u`。
3. **维护两个树状数组**：
   - 数组A维护 `x + dep_v*k` 的区间加
   - 数组B维护 `k` 的区间加
4. **查询时计算**：`A.query(u) - dep_u * B.query(u)`

**解决难点**：
- **子树的高效处理**：DFS序将树结构转化为线性区间，使区间操作可用树状数组实现。
- **公式分解**：将原始复杂公式拆分为可分别维护的独立项，避免直接处理动态变化的深度差。

---

# 【题解评分 ≥4星】

1. **nekko (5星)**  
   - 思路清晰，代码简洁  
   - 双树状数组拆分思路直观，时间复杂度O(qlogn)  
   - 核心代码仅需20行，易于理解与实现  
   ```cpp
   struct BIT { /* 树状数组实现 */ };
   BIT a, b; // 分别维护x+dep_v*k和k的和
   dfs预处理后：
   操作1：a.add区间(x+dep_v*k), b.add区间(k)
   查询：a.ask - dep[u]*b.ask
   ```

2. **Pengzt (4星)**  
   - 使用线段树维护差分，适合理解线段树操作  
   - 通过维护两个标记简化公式处理  
   - 代码稍长但逻辑明确  
   ```cpp
   void Update() { 
       sgt.Update(区间减k); 
       sgt.Update(单点加x+dep_v*k);
   }
   ```

3. **shadowice1984 (4星)**  
   - 离线处理+树上路径维护  
   - 通过DFS栈维护有效修改，适合动态路径查询场景  
   ```cpp
   dfs时动态维护当前路径上的修改
   查询时直接访问树状数组历史记录
   ```

---

# 【最优思路提炼】

**核心技巧**：
- **公式拆解**：`x - k*(d_u-d_v) = (x+k*d_v) - k*d_u`，分离常数项与线性项
- **双数组维护**：独立处理不同性质的项，避免混合计算
- **DFS序应用**：将子树操作转化为区间操作的关键预处理

**适用场景**：需要处理子树/路径上的线性组合修改时，如带权值的批量增减操作。

---

# 【同类题目推荐】

1. **P3384 树链剖分**  
   树链剖分基础题，练习路径与子树操作

2. **CF877E XOR and Favorite Number**  
   子树异或操作与查询，类似区间处理思想

3. **LOJ 6281 数列分块入门5**  
   分块处理区间操作，体会不同数据结构的适用场景

---

# 【可视化设计】

**动画方案**：
1. **DFS序展示**：以像素风格绘制树结构，节点按DFS遍历顺序排列成线性序列，突出子树对应连续区间。
2. **操作演示**：
   - **修改操作**：点击节点v后，其对应区间以蓝色闪烁，两个树状数组分别显示数值增加效果
   - **查询操作**：目标节点显示红色边框，动态计算并弹出公式`A值 - 深度×B值`
3. **复古特效**：
   - 8-bit音效：修改时播放短促"哔"声，查询成功时播放上升音阶
   - 像素字体显示当前树状数组状态，用不同颜色区分A/B数组
4. **交互控制**：
   - 速度调节滑块控制动画播放速度
   - 单步执行按钮观察每一步数据变化

**代码片段示例**（伪代码）：
```javascript
// 树状数组更新动画
function animateUpdate(l, r, value, isA) {
  for(let i=l; i<=r; i++) {
    drawPixel(i, isA ? 'blue' : 'red', value); // 像素块颜色变化
    playSound('beep', 100 + i*10); // 音调递增
  }
}
```

---

# 【核心代码实现】

nekko题解关键代码：
```cpp
struct BIT {
    ll sum[N];
    void addsig(int x, ll y) {
        for(;x<=n;x+=x&-x) sum[x] = (sum[x]+y) % mod;
    }
    void add(int l, int r, ll s) {
        addsig(l,s), addsig(r+1,-s);
    }
    ll ask(int x) {
        ll r = 0;
        for(;x;x-=x&-x) r = (r+sum[x])%mod;
        return r;
    }
} a, b;

// 修改操作
a.add(lv, rv, (x + 1ll*dep[v]*k%mod)%mod);
b.add(lv, rv, k%mod);

// 查询操作
ll ans = (1ll*-dep[v]*a.ask(pos) + b.ask(pos)) % mod;
```

---

# 【总结】

本题解通过巧妙的公式拆解与数据结构选择，将复杂的树操作转化为高效的区间处理。使用双树状数组的方案时间复杂度最优，代码实现简洁，是处理类似子树线性修改问题的典范解法。结合DFS序与树状数组的特性，展现了树结构与线性数据结构的精妙结合。

---
处理用时：71.25秒