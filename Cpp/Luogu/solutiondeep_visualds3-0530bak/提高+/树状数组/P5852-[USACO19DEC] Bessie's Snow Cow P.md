# 题目信息

# [USACO19DEC] Bessie's Snow Cow P

## 题目背景

Snow has arrived on the farm, and as she does at the beginning of every winter,
Bessie is building a snow-cow! Most of the time, Bessie strives to make her
sculpture look as much like a real cow as possible.  However, feeling
artistically inspired, this year she decides to pursue a more abstract route and
build a sculpture in the shape of a tree, consisting of $N$ snowballs
$(1\le N\le 10^5)$ connected by  $N-1$ branches, each connecting a pair of
snowballs such that there is a  unique path between every pair of snowballs. 

Bessie has added a nose to one of the snowballs, so it represents the head of
the abstract snow cow.  She designates it as snowball number 1.  To add more
visual interest, she plans to dye some of the snowballs different colors in an
artistic fashion by filling old milk pails with colored dye and splashing them
onto the sculpture.  Colors are identified by integers in the range
$1 \ldots 10^5$, and  Bessie has an unlimited supply of buckets filled with dyes
of every possible color.

When Bessie splashes a snowball with a bucket of dye, all the snowballs in its 
subtree are also splashed with the same dye (snowball $y$ is in the subtree of
snowball $x$ if $x$ lies on the path from $y$ to the head snowball). By
splashing each color with great care, Bessie makes sure that all colors a 
snowball has been splashed with will remain visible. For example, if a snowball
had colors $[1,2,3]$ and Bessie splashes it with color $4$, the snowball will
then have colors $[1,2,3,4]$. 

After splashing the snowballs some number of times, Bessie may also want to know
how colorful a part of her snow-cow is.  The "colorfulness" of a snowball $x$ is
equal to the number of distinct colors $c$ such that snowball $x$ is colored
$c$. If Bessie asks you about snowball $x$, you should reply with the sum of the
colorfulness values of all snowballs in the subtree of $x.$

Please help Bessie find the colorfulness of her snow-cow at certain points in
time.

## 题目描述

农场下雪啦！Bessie 和往年开冬一样在堆雪牛。她之前是个写实派，总是想把她的雪牛堆得和个真牛一样。但今年不一样，受到来自东方的神秘力量的影响，她想来点抽象艺术，因此她想堆成一棵树的样子。这棵树由 $N$ 个雪球，$N-1$ 根树枝构成，每根树枝连接两个雪球，并且每两个雪球之间路径唯一。

Bessie 要给她的雪牛来点细节。因此她给其中一个雪球加了个鼻子，来表示这是他那抽象的牛的头，并且把它称作雪球 $1$。为了让雪牛更好看，她还要给某些雪球来点不同的颜色。于是，她用旧牛奶桶装满了颜料泼到雪牛上。这些颜料分别被编号为 $1,2,\dots 10^5$，且每种颜色都无限量供应。

当 Bessie 把一桶颜料泼到一个雪球上时，这个雪球子树上的所有雪球也会被染色（我们称雪球 $y$ 在雪球 $x$ 的子树里当且仅当雪球 $x$ 处在雪球 $y$ 到雪球 $1$ 的路径上）。Bessie 有着精确的泼颜料技术，因此在泼完一种颜料后，一个雪球上之前被染过的所有颜色依然清晰可见。例如，一个雪球之前显现出来颜色 $\left[ 1,2,3 \right]$，然后 Bessie 把装有 $4$ 号颜色的牛奶桶泼上去，那么这个雪球将显现出来颜色 $\left[ 1,2,3,4 \right]$。 在泼了几桶颜料以后，Bessie 可能想要了解她的雪牛有多五彩斑斓。令雪球 $x$ 的『颜色丰富度』为这个雪球被染上的不同颜色总数 ，当 Bessie 想了解雪球 $x$ 的相关信息时，你应该回答她雪球 $x$ 的子树中所有的雪球的颜色丰富度之和。

救救孩子吧！

## 说明/提示

#### 样例解释
执行完第一个修改后雪球 $4$ 被染上了颜色 $1$。

执行完第二个修改后雪球 $4$ 和雪球 $5$ 被染上了颜色 $2$。

执行完第三个修改后所有雪球都被染上了颜色 $1$。
#### 数据范围
对于测试点 $2,3$，$1\le N\le 10^2,1\le Q\le 2\times 10^2$；

对于测试点 $4-6$，$1\le N\le 10^3,1\le Q\le 2\times 10^3$；

对于 $100\%$ 的数据，$1\le N,\ Q,\ c \le 10^5, 1\le a,\ b,\ x \le N$。

USACO 2019 December 铂金组T2

## 样例 #1

### 输入

```
5 18
1 2
1 3
3 4
3 5
1 4 1
2 1
2 2
2 3
2 4
2 5
1 5 1
2 1
2 2
2 3
2 4
2 5
1 1 1
2 1
2 2
2 3
2 4
2 5
```

### 输出

```
1
0
1
1
0
2
0
2
1
1
5
1
3
1
1
```

# AI分析结果



# 算法分类：树状数组/线段树 + 离线处理

## 综合分析与结论

### 核心思路
1. **DFS序转换**：将树转化为线性结构，子树对应连续区间。
2. **颜色区间管理**：对每种颜色维护一个`set`，存储不交的染色子树的根节点dfn。
3. **贡献拆分**：
   - **祖先贡献**：通过树状数组维护区间加（染色时给子树区间+1，查询时单点求和）。
   - **子树贡献**：通过树状数组维护单点加（每个子树根的贡献乘以其size，查询时区间求和）。
4. **去重逻辑**：染色时若祖先已被同色覆盖则跳过；若当前染色子树包含旧染色点，则删除旧点。

### 解决难点
- **动态覆盖处理**：通过`set`快速定位需删除的子节点区间，保证每个颜色下无重叠子树。
- **高效区间操作**：利用树状数组实现O(logn)的区间加减与求和，支撑1e5量级操作。

### 可视化设计
1. **树转线性结构**：以像素块展示DFS序排列的节点，子树对应连续色块。
2. **染色动画**：
   - 染色时高亮对应区间，若触发旧区间删除，旧色块闪烁后消失。
   - 树状数组数值变化以柱状图动态显示。
3. **复古交互**：
   - **8-bit音效**：染色成功时播放“滴”声，删除旧区间时播放“咔嚓”声。
   - **自动演示**：按操作顺序逐步执行，用户可暂停/调速观察覆盖逻辑。

---

## 题解清单 (4星及以上)

### 1. KaisuoShutong (5星)
- **亮点**：双树状数组拆分贡献，代码简洁高效。
- **关键代码**：
  ```cpp
  void upd(int x, int d) {
      A.ins(dfn[x], d);  // 祖先贡献区间加
      B.ins(dfn[x], (low[x]-dfn[x]+1)*d); // 子树贡献单点加
  }
  int que(int x) {
      return (low[x]-dfn[x]+1)*A.ask(dfn[x]) + B.ask(low[x]) - B.ask(dfn[x]);
  }
  ```

### 2. Drifty (4.5星)
- **亮点**：线段树直接维护区间和，逻辑直观。
- **关键处理**：
  ```cpp
  while (it != s[c].end() && *it <= r) {
      T.modify(1, 1, N, *it, *it+siz[...]-1, -1); // 删除旧区间
      s[c].erase(it++);
  }
  ```

### 3. Purple_wzy (4星)
- **亮点**：详细注释与调试经验，适合新手理解。
- **个人心得**："注意set的边界判断，prev(it)需先检查非begin"。

---

## 核心代码实现

```cpp
// 树状数组实现（KaisuoShutong方案）
struct BIT {
    int tr[N];
    void add(int x, int v) { for(;x<=n;x+=x&-x) tr[x]+=v; }
    int ask(int x) { int r=0; for(;x;x-=x&-x) r+=tr[x]; return r; }
} A, B;

void upd(int u) {
    A.add(dfn[u], 1);          // 祖先贡献：区间[dfn, low]+1
    A.add(low[u]+1, -1);
    B.add(dfn[u], siz[u]);      // 子树贡献：单点加siz[u]
}

int query(int u) {
    return siz[u] * A.ask(dfn[u]) + (B.ask(low[u]) - B.ask(dfn[u]));
}
```

---

## 相似题目推荐
1. **P3384 【模板】树链剖分** - 子树/路径修改查询。
2. **P5494 【模板】线段树分裂** - 动态区间管理。
3. **P4211 [LNOI2014] LCA** - 离线处理与树上前缀和。

---

## 可视化示例（伪代码）

```javascript
// Canvas绘制子树区间
function drawSubtree(dfn, low, color) {
    ctx.fillStyle = color;
    ctx.fillRect(dfn*10, 0, (low-dfn+1)*10, 50); // 矩形表示区间
}

// 染色操作动画
function animateColor(c, u) {
    let oldNodes = s[c].queryRange(dfn[u], low[u]); // 获取待删除节点
    oldNodes.forEach(node => {
        flash(node.dfn, node.low, 'red'); // 红色闪烁提示删除
        s[c].delete(node);
    });
    drawSubtree(dfn[u], low[u], colors[c]); // 新染色
    playSound('blip.mp3');
}
```

---

## 总结
本题解通过DFS序与高效数据结构，将复杂的子树操作转化为区间问题，结合去重逻辑实现线性复杂度。可视化重点在于展示区间覆盖与数据结构联动，复古风格增强理解趣味性。

---
处理用时：82.72秒