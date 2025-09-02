# 题目信息

# Beard Graph

## 题目描述

Let's define a non-oriented connected graph of $ n $ vertices and $ n-1 $ edges as a beard, if all of its vertices except, perhaps, one, have the degree of 2 or 1 (that is, there exists no more than one vertex, whose degree is more than two). Let us remind you that the degree of a vertex is the number of edges that connect to it.

Let each edge be either black or white. Initially all edges are black.

You are given the description of the beard graph. Your task is to analyze requests of the following types:

- paint the edge number $ i $ black. The edge number $ i $ is the edge that has this number in the description. It is guaranteed that by the moment of this request the $ i $ -th edge is white
- paint the edge number $ i $ white. It is guaranteed that by the moment of this request the $ i $ -th edge is black
- find the length of the shortest path going only along the black edges between vertices $ a $ and $ b $ or indicate that no such path exists between them (a path's length is the number of edges in it)

The vertices are numbered with integers from $ 1 $ to $ n $ , and the edges are numbered with integers from $ 1 $ to $ n-1 $ .

## 说明/提示

In the first sample vertices $ 1 $ and $ 2 $ are connected with edge number $ 1 $ , and vertices $ 2 $ and $ 3 $ are connected with edge number $ 2 $ . Before the repainting edge number $ 2 $ each vertex is reachable from each one along the black edges. Specifically, the shortest path between $ 1 $ and $ 3 $ goes along both edges.

If we paint edge number $ 2 $ white, vertex $ 3 $ will end up cut off from other vertices, that is, no path exists from it to any other vertex along the black edges.

## 样例 #1

### 输入

```
3
1 2
2 3
7
3 1 2
3 1 3
3 2 3
2 2
3 1 2
3 1 3
3 2 3
```

### 输出

```
1
2
1
1
-1
-1
```

## 样例 #2

### 输入

```
6
1 5
6 4
2 3
3 5
5 6
6
3 3 4
2 5
3 2 6
3 1 2
2 3
3 3 1
```

### 输出

```
3
-1
3
2
```

# AI分析结果



### 唯一算法分类  
树链剖分（重链剖分）

---

### 综合分析与结论  
#### 核心算法流程  
1. **边权转点权**：将每条边映射到其较深端点的点权，确保 LCA 的父边不被计入路径  
2. **树链剖分**：将树拆分为重链，用线段树维护每个点的权值（0=黑边，1=白边）  
3. **查询优化**：查询路径权值和，若存在白边（和>0）返回-1，否则返回路径长度  

#### 可视化设计要点  
- **像素风格渲染**：用 16 色网格表示树结构，深色方块表示重链节点，浅色表示轻链节点  
- **动态高亮**：  
  - 修改操作时，对应点权方块闪烁黄色  
  - 查询路径时，遍历的链用红色边框标记  
- **音效设计**：  
  - 线段树更新时播放短促 "哔" 声（8-bit 风格）  
  - 发现白边时播放低沉 "嗡" 声，全黑路径则播放上扬音阶  

---

### 题解清单（≥4星）  
#### 1. Farkas_W（★★★★☆）  
- **亮点**：  
  1. 清晰图解边权转点权策略  
  2. 用线段树同时维护区间和与区间最大值  
  3. 详细注释 LCA 的特殊处理逻辑  
```cpp
int query(int x, int y) {
    int fx=top[x], fy=top[y], ans=0;
    while(fx != fy) {
        if(dep[fx] < dep[fy]) swap(x,y), swap(fx,fy);
        if(!query1(1,1,n,seg[fx],seg[x])) return 0; // 关键判断
        ans += seg[x]-seg[fx]+1;
        x = father[fx]; fx = top[x];
    }
    // ...处理 LCA
}
```

#### 2. doby（★★★★☆）  
- **亮点**：  
  1. 单点修改优化时间复杂度  
  2. 通过 `id[x]-id[top[x]]+1` 快速计算重链长度  
  3. 精简的 LCA 处理逻辑  
```cpp
int LCA(int x, int y) {
    while(top[x]^top[y]) {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x = dad[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}
```

#### 3. zhengrunzhe（★★★★☆）  
- **亮点**：  
  1. 创新使用 LCT 实现 O(n log n) 复杂度  
  2. 通过维护连通性直接判断路径有效性  
  3. 代码高度模块化，可读性强  
```cpp
int distance(int x,int y) {
    if(findroot(x)^findroot(y)) return -1;
    split(x,y); return siz[y]-1; // 利用 size 直接计算长度
}
```

---

### 最优思路提炼  
**边权转点权的树剖范式**：  
1. **映射策略**：边(u,v) → max_depth(u,v) 的点权  
2. **线段树维护**：  
   - 黑边存0，白边存1  
   - 查询路径和判断是否存在1  
3. **LCA 规避**：最后处理 LCA 的父边，确保不越界  

---

### 类似题目推荐  
1. [P3384 树链剖分模板](https://www.luogu.com.cn/problem/P3384)  
2. [P3950 部落冲突](https://www.luogu.com.cn/problem/P3950)  
3. [P2486 染色](https://www.luogu.com.cn/problem/P2486)  

---

### 可视化方案示例（伪代码）  
```javascript
class BeardGraphVisualizer {
  constructor(tree) {
    this.canvas = document.createElement('canvas');
    this.ctx = this.canvas.getContext('2d');
    this.nodes = this.parseTree(tree); // 解析树结构为像素坐标
  }

  highlightPath(u, v) {
    const path = this.getPath(u, v); // 获取树剖路径
    path.forEach(node => {
      this.drawNode(node, '#FF0000'); // 红色高亮路径
      playSound('blip'); // 播放路径音效
    });
  }

  updateEdge(edgeId, color) {
    const node = this.getMappedNode(edgeId); // 获取映射点
    this.drawNode(node, color ? '#000000' : '#FFFFFF'); // 黑白交替
    this.node.flash(); // 闪烁动画
  }
}
```

---

### 关键代码片段（树剖核心）  
```cpp
void modify_edge(int edge_id, int color) {
    int u = edges[edge_id].u, v = edges[edge_id].v;
    int node = (dep[u] > dep[v]) ? u : v; // 选择较深端点
    update_segtree(id[node], color); // 线段树单点更新
}

int query_path(int a, int b) {
    int sum = 0, lca = get_lca(a, b);
    while(top[a] != top[b]) {
        if(dep[top[a]] < dep[top[b]]) swap(a, b);
        sum += query_segtree(id[top[a]], id[a]);
        a = fa[top[a]];
    }
    if(dep[a] > dep[b]) swap(a, b);
    sum += query_segtree(id[a]+1, id[b]); // 跳过 LCA
    return sum > 0 ? -1 : (dep[a] + dep[b] - 2*dep[lca]);
}
```

---
处理用时：84.59秒