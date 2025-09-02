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



# 算法分类  
**树状数组/线段树 + DFS序**

---

# 题解思路、算法要点与解决难点  
**核心思路**：  
1. 将操作拆解为两部分：与节点深度无关的常数项 `x + dep[v] * k` 和与深度相关的线性项 `-k * dep[u]`  
2. 利用DFS序将子树映射为连续区间，通过两个树状数组分别维护两部分的值  
3. 查询时组合两个树状数组的结果，计算公式：`ans = (sum_const - sum_k * dep[v]) % mod`

**关键实现步骤**：  
1. **DFS序预处理**：记录每个节点的进入时间戳`l[u]`和离开时间戳`r[u]`  
2. **树状数组操作**：  
   - `a`数组维护`x + dep[v] * k`的区间加  
   - `b`数组维护`k`的区间加  
3. **查询计算**：`ans = (a.ask(v) - b.ask(v) * dep[v] + mod) % mod`

**解决难点**：  
- 将距离计算转化为深度差，实现线性项的拆分  
- 通过DFS序将子树操作转化为区间操作，降低时间复杂度至`O(q log n)`

---

# 题解评分 (≥4星)  
1. **nekko（赞8）**  
   - 思路清晰度：⭐⭐⭐⭐⭐  
   - 代码可读性：⭐⭐⭐⭐（简洁的树状数组实现）  
   - 算法优化：⭐⭐⭐⭐⭐（最优时间复杂度）  
   - 关键亮点：巧妙拆分操作项，仅用两个树状数组实现  

2. **Pengzt（赞3）**  
   - 思路清晰度：⭐⭐⭐⭐  
   - 代码可读性：⭐⭐⭐（使用vector存储DFS序）  
   - 算法优化：⭐⭐⭐⭐  
   - 个人心得：提到扩展到全局操作的思路，具有启发性  

3. **lbmzxhb（赞0）**  
   - 思路清晰度：⭐⭐⭐  
   - 代码可读性：⭐⭐⭐⭐（完整注释+调试记录）  
   - 算法优化：⭐⭐⭐  
   - 独特价值：提供数据生成器和完整测试用例  

---

# 最优思路/技巧提炼  
1. **贡献拆分**：  
   ```math
   x - (dep[u]-dep[v])k = (x + dep[v]k) - dep[u]k
   ```  
   将操作拆分为常数项和线性项，分别维护  
2. **DFS序映射**：子树操作 → 区间操作  
3. **双树状数组**：分别处理常数项和线性系数，查询时组合结果  

---

# 同类题目推荐  
1. [P3178 树上操作](https://www.luogu.com.cn/problem/P3178)  
   （区间加+子树求和）  
2. [P3384 树链剖分](https://www.luogu.com.cn/problem/P3384)  
   （路径修改+子树查询）  
3. [CF343D Water Tree](https://www.luogu.com.cn/problem/CF343D)  
   （子树赋值+路径查询）

---

# 可视化设计要点  
**动画方案**：  
1. **树结构展示**：  
   - 用颜色标记当前操作的子树区间（如红色高亮`l[v]`到`r[v]`）  
   - 节点深度用不同颜色渐变表示（浅蓝→深蓝）  

2. **树状数组更新**：  
   - 操作1时，显示两个树状数组的区间加动画  
   - 查询时，高亮`l[v]`位置的两个数组查询路径  

3. **像素风格特效**：  
   - 关键操作触发8-bit音效（如"哔-"声表示区间更新）  
   - 使用Canvas绘制树状数组的二进制索引过程（闪烁显示lowbit计算）  

**交互功能**：  
- 速度调节滑块控制动画节奏  
- 单步执行按钮观察每个bit的更新  
- 点击节点显示其`(l[u], r[u])`区间范围  

---

# 核心代码实现  
```cpp
// DFS序预处理
void dfs(int u) {
    static int tot = 0;
    l[u] = ++tot;
    for(int v : g[u]) {
        dep[v] = dep[u] + 1;
        dfs(v);
    }
    r[u] = tot;
}

// 树状数组操作
struct BIT {
    ll sum[N];
    void addsig(int x, ll y) {
        for(; x<=n; x+=x&-x) sum[x] = (sum[x]+y) % mod;
    }
    void add(int l, int r, ll s) {
        addsig(l,s), addsig(r+1,-s);
    }
    ll ask(int x) {
        ll r = 0;
        for(; x; x-=x&-x) r = (r+sum[x]) % mod;
        return r;
    }
} a, b;

// 处理操作
if(op == 1) {
    scanf("%d%d%d", &v, &x, &k);
    a.add(l[v], r[v], (x + 1ll*dep[v]*k) % mod);
    b.add(l[v], r[v], k % mod);
} else {
    ll qa = a.ask(l[v]);
    ll qb = b.ask(l[v]);
    ll ans = (qa - qb*dep[v] % mod + mod) % mod;
    printf("%lld\n", ans);
}
```

---

# 个人心得摘录  
> "调试时发现负数取模问题，最终通过`(ans%mod + mod)%mod`解决。教训：所有中间结果都要考虑负值！" —— nekko  
> "最初想用线段树维护深度权重，后来发现拆分成两个数组更简洁" —— Pengzt  
> "生成随机数据时，特别注意子树大小为1的边界情况" —— N2MENT  

---

通过将复杂操作拆解为可维护的数学形式，结合DFS序和树状数组的高效区间操作，本解法在时间复杂度和代码简洁性上达到最优平衡。可视化设计中强调操作拆分和区间映射的直观展示，帮助理解核心算法思想。

---
处理用时：73.63秒