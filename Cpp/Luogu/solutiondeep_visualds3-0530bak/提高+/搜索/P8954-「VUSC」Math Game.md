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



---

**唯一算法分类**  
其他搜索

---

## 综合分析与结论

### 核心思路与难点
1. **数学分解核心**：将每个数分解为最小基的幂（如 8=2³ → 基为2，指数为3），同一基的不同指数构成连通块。
2. **动态删除处理**：通过预处理基的层级关系，用哈希表或并查集维护连通性，删除操作转化为断开基的层级连接。
3. **高效查询**：利用幂次枚举或离散化技巧，在 O(log N) 时间内统计未被删除的连通节点数。

### 搜索过程可视化设计
1. **节点分解动画**：展示数 x 分解为最小基 y 的过程（如 16 → 2⁴ → 基2，指数4）。
2. **层级扩展演示**：以基 y 为中心，动态绘制其所有合法幂次节点（如 2²=4, 2³=8 等），高亮未被删除的节点。
3. **删除影响标记**：删除某节点时，用红色闪烁提示其所在层级断裂，影响连通块统计。
4. **复古像素风格**：以 8-bit 网格展示基与指数，不同基用不同颜色区块，访问路径用像素箭头连接。

---

## 题解清单（≥4星）

### 1. enucai（⭐️⭐️⭐️⭐️）
- **亮点**：提出基分解思想，预处理三次方与平方特判，用 set 高效维护删除状态。
- **关键代码**：
  ```cpp
  ll find(ll x) {
    if (mp.find(x) != mp.end()) return mp[x];
    else if (check(x) != -1) return check(x);
    else if ((ll)sqrtl(x) * (ll)sqrtl(x) == x) return sqrtl(x);
    else return x;
  }
  ```

### 2. STUDENT00（⭐️⭐️⭐️⭐️）
- **亮点**：离线逆向操作+离散化，用时间倒流实现并查集动态维护。
- **关键代码**：
  ```cpp
  void unnion(int id,int x,int y){
    x=find(id,x); y=find(id,y);
    if(x==y) return;
    fa[id][y]=x; siz[id][x]+=siz[id][y];
  }
  ```

### 3. Moeebius（⭐️⭐️⭐️⭐️）
- **亮点**：官方题解标准实现，双重预处理+并查集动态层级合并。
- **关键代码**：
  ```cpp
  For(j,1,cnt/2) {
    tmp*=num[i];
    if(vis[tmp]) continue;
    For(k,2,cnt/j) uni(i+1,j,j*k);
  }
  ```

---

## 最优思路提炼
1. **最小基分解**：每个数拆解为最小可能的基，如 64 → 2⁶（而非 8²或4³）。
2. **层级连通管理**：基的指数层级通过并查集或哈希表维护，删除操作影响上下层连接。
3. **幂次枚举剪枝**：仅枚举可能的指数范围（如 log₂N），避免全量遍历。

---

## 类似题目推荐
1. **P1197 [JSOI2008]星球大战**：逆向处理删除操作，维护连通块。
2. **P2421 [NOI2002]荒岛野人**：数学分解与模运算判断。
3. **P4219 [BJOI2014]大融合**：动态维护树边与子树大小。

---

## 可视化与游戏化设计
1. **像素动画**：基节点用 16x16 像素块，指数层级用垂直排列的方格，访问时填充颜色。
2. **音效触发**：分解成功时播放 8-bit 上升音阶，删除时播放爆炸音效。
3. **自动演示模式**：按基的层级顺序自动展开连通块，速度可调。
4. **积分系统**：正确统计连通块大小获得积分，错误操作扣分。

```html
<!-- 示例：Canvas绘制基层级 -->
<canvas id="grid" width="800" height="600"></canvas>
<script>
const canvas = document.getElementById('grid');
const ctx = canvas.getContext('2d');
const bases = new Map(); // 存储基与层级关系

function drawBase(base, levels) {
  ctx.fillStyle = '#FF0000'; // 基节点红色
  ctx.fillRect(base.x, base.y, 16, 16);
  levels.forEach((level, idx) => {
    ctx.fillStyle = level.active ? '#00FF00' : '#666666';
    ctx.fillRect(base.x + 20*(idx+1), base.y, 16, 16);
  });
}
</script>
```

---
处理用时：84.67秒