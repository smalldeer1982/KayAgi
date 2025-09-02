# 题目信息

# Lomsat gelral

## 题目描述

You are given a rooted tree with root in vertex $ 1 $ . Each vertex is coloured in some colour.

Let's call colour $ c $ dominating in the subtree of vertex $ v $ if there are no other colours that appear in the subtree of vertex $ v $ more times than colour $ c $ . So it's possible that two or more colours will be dominating in the subtree of some vertex.

The subtree of vertex $ v $ is the vertex $ v $ and all other vertices that contains vertex $ v $ in each path to the root.

For each vertex $ v $ find the sum of all dominating colours in the subtree of vertex $ v $ .

## 样例 #1

### 输入

```
4
1 2 3 4
1 2
2 3
2 4
```

### 输出

```
10 9 3 4
```

## 样例 #2

### 输入

```
15
1 2 3 1 2 3 3 1 1 3 2 2 1 2 3
1 2
1 3
1 4
1 14
1 15
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13
```

### 输出

```
6 5 4 3 2 3 3 1 1 3 2 2 1 2 3
```

# AI分析结果



### 唯一算法分类
**树上启发式合并（DSU on Tree）**

---

### 综合分析与结论
**核心思路**：  
通过轻重链剖分优化子树统计过程。对每个节点：  
1. 递归处理轻儿子子树并清空统计信息  
2. 保留重儿子子树的信息  
3.暴力统计当前节点及其轻儿子子树信息  

**解决难点**：  
- 通过保留重儿子信息减少重复计算，将复杂度从 O(n²) 优化到 O(n log n)  
- 通过颜色计数桶（`cnt[]`）和最大值跟踪（`maxv, sum`）动态维护众数和  

**可视化设计要点**（DSU on Tree 流程演示）：  
1. **颜色标记**：  
   - 红色高亮当前处理的节点  
   - 蓝色标记重儿子子树  
   - 绿色标记需要暴力统计的轻儿子子树  
2. **动画步骤**：  
   - 递归进入轻儿子→统计→清空（用爆炸粒子特效表示清除）  
   - 递归进入重儿子→保留统计结果（持续高亮）  
   - 合并时用流动线条表示轻儿子数据并入重儿子数据  

---

### 题解清单（≥4星）

#### 1. YellowBean_Elsa（★★★★★）
**亮点**：  
- 完整实现 DSU 模板，含详细注释  
- 复杂度证明清晰（轻边数 ≤ log n）  
- 核心代码片段：  
  ```cpp
  void DFS(int x,int f,int p) {
    ap[c[x]]++;  // 统计颜色出现次数
    if(ap[c[x]]>mx) mx=ap[c[x]], sum=c[x];
    else if(ap[c[x]]==mx) sum+=c[x];
    // 跳过重儿子子树（p为重儿子标记）
    for(int i=first[x];i;i=nex[i])
      if(v[i]!=f && v[i]!=p) DFS(v[i],x,p);
  }
  ```

#### 2. 辰星凌（★★★★☆）
**亮点**：  
- 提供 DSU 与线段树合并双解法  
- 分治思路的 DFS 序转化极具启发性  
- 关键变量说明：  
  ```cpp
  struct QAQ{int to,next;}a[N<<1];  // 链式前向星存图
  int sz[N], son[N];                // 子树大小与重儿子
  ```

#### 3. 曾爷爷（★★★★☆）
**优化技巧**：  
- 使用时间戳清空计数桶（`tme`变量）  
- 将颜色计数封装为结构体提升可维护性  
- 核心清空逻辑：  
  ```cpp
  void clear() { tme++; maxsize = sum = 0; }  // O(1)清空
  ```

---

### 最优思路提炼
**DSU 三步核心操作**：  
1. **轻重链划分**：预处理重儿子（`dfs1`）  
2. **轻子树处理**：递归计算后清空（`init`函数）  
3. **重子树保留**：直接继承结果（`if(p) dfs(p,x)`）  

**数据结构创新**：  
- 使用双计数桶（`cnt[color]`统计颜色数，`sum[count]`统计对应次数的颜色和）

---

### 同类型题目推荐
1. [CF208E] Blood Cousins（子树层级统计）  
2. [CF570D] Tree Requests（子树字符奇偶性）  
3. [CF741D] Arpa’s letter-marked tree（路径字符奇偶性+dsu）

---

### 个人心得摘录
> "十年OI一场空，不开 long long 见祖宗" —— YellowBean_Elsa  
> 调试时发现颜色和会爆 int，改用 `long long sum` 后 AC

> "map合并时注意先判断key存在性，否则会插入无效键" —— He_Ren  
> 使用 `map::count()` 预判避免内存浪费

---

### 可视化算法演示（伪代码）
```javascript
// 使用 Canvas 绘制树结构
class DSUVisualizer {
  constructor(tree) {
    this.nodes = tree.getNodes(); // 节点坐标预计算
    this.currentNode = null;      // 当前处理节点（红色）
    this.heavyEdges = new Set();  // 重边集合（蓝色粗线）
  }

  // 单步执行动画
  async step() {
    // 1. 处理轻儿子（绿色闪烁）
    await this.processLightChild(node);
    // 2. 清除轻儿子统计（爆炸特效）
    this.clearCounters(node); 
    // 3. 处理重儿子（持续高亮）
    await this.processHeavyChild(node);
    // 4. 合并结果（流动线条动画）
    this.mergeResults(node);
  }
}
```

---

### 核心代码实现（DSU 模板）
```cpp
int sz[N], son[N], cnt[N], col[N];
ll sum[N], ans[N], max_cnt;

void dfs1(int u, int fa) { // 找重儿子
  sz[u] = 1;
  for(int v : G[u]) if(v != fa) {
    dfs1(v, u);
    sz[u] += sz[v];
    if(sz[v] > sz[son[u]]) son[u] = v;
  }
}

void update(int u, int fa, int val) { // 统计/清除颜色
  cnt[col[u]] += val;
  if(cnt[col[u]] > max_cnt) 
    max_cnt = cnt[col[u]], sum[max_cnt] = 0;
  sum[cnt[col[u]]] += col[u];
  for(int v : G[u]) if(v != fa && !vis[v]) 
    update(v, u, val);
}

void dfs2(int u, int fa, bool keep) {
  for(int v : G[u]) // 先处理轻儿子
    if(v != fa && v != son[u]) dfs2(v, u, false);
  
  if(son[u]) {      // 处理重儿子
    dfs2(son[u], u, true);
    vis[son[u]] = true; // 标记保留
  }
  
  update(u, fa, 1); // 合并当前节点
  ans[u] = sum[max_cnt];
  
  if(son[u]) vis[son[u]] = false;
  if(!keep) {       // 清除非保留子树
    update(u, fa, -1);
    max_cnt = sum[0] = 0;
  }
}
```

---
处理用时：81.36秒