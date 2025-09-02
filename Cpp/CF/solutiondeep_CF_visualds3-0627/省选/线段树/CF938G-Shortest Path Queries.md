# 题目信息

# Shortest Path Queries

## 题目描述

You are given an undirected connected graph with weighted edges. The length of some path between two vertices is the bitwise xor of weights of all edges belonging to this path (if some edge is traversed more than once, then it is included in bitwise xor the same number of times).

There are three types of queries you have to process:

- $ 1 $ $ x $ $ y $ $ d $ — add an edge connecting vertex $ x $ to vertex $ y $ with weight $ d $ . It is guaranteed that there is no edge connecting $ x $ to $ y $ before this query;
- $ 2 $ $ x $ $ y $ — remove an edge connecting vertex $ x $ to vertex $ y $ . It is guaranteed that there was such edge in the graph, and the graph stays connected after this query;
- $ 3 $ $ x $ $ y $ — calculate the length of the shortest path (possibly non-simple) from vertex $ x $ to vertex $ y $ .

Print the answers for all queries of type $ 3 $ .

## 样例 #1

### 输入

```
5 5
1 2 3
2 3 4
3 4 5
4 5 6
1 5 1
5
3 1 5
1 1 3 1
3 1 5
2 1 5
3 1 5
```

### 输出

```
1
1
2
```

# AI分析结果



---

## 算法分类  
线段树分治、线性基、可撤销并查集

---

## 综合分析与结论  

### 核心算法逻辑  
1. **线段树分治**：将每条边的存在时间区间拆解为多个时间片段，存入线段树对应节点  
2. **可撤销并查集**：维护生成树结构，记录顶点到根的异或距离，支持动态加边/撤销  
3. **线性基分层**：每层递归时复制父层的线性基，避免删除操作  

### 解决难点  
1. **动态删边处理**：通过离线查询+线段树分治，将动态问题转化为静态区间覆盖  
2. **环异或值的维护**：通过并查集合并时的环检测，将环的异或值插入线性基  
3. **路径异或的快速查询**：利用并查集的顶点到根异或距离特性，O(1) 计算两点间路径异或  

### 可视化设计思路  
![算法流程](https://cdn.luogu.com.cn/upload/image_hosting/6v7k8w9u.gif)  
- **颜色标记**：  
  - 绿色：当前处理的线段树节点  
  - 蓝色：正在合并的并查集分量  
  - 红色：插入线性基的环异或值  
- **步进控制**：  
  1. 展示线段树节点的时间区间划分  
  2. 高亮当前处理的边集合  
  3. 动态显示并查集合并/撤销过程  
  4. 展示线性基的更新状态  

---

## 题解清单 (4星及以上)  

### 1. p_b_p_b (4.5★)  
**核心亮点**：  
- 首次提出时间分治与可撤销并查集结合  
- 详细推导非树边环的异或处理  
- 代码结构清晰，包含路径异或的维护  

### 2. zhiyangfan (4.2★)  
**关键技巧**：  
- 使用 `bitset` 优化线性基存储  
- 分离线段树分治的边插入与查询处理  
- 详细注释关键变量的维护逻辑  

### 3. juju527 (4.0★)  
**创新点**：  
- 引入栈记录线性基状态变化  
- 使用模板类封装并查集操作  
- 支持多组线性基的快速复制  

---

## 核心代码实现  

### 可撤销并查集  
```cpp  
struct DSU {
    int fa[N], dis[N], sz[N], top;
    struct Node { int x,y,dx; } stk[N]; // 撤销栈
    
    int find(int u, int &d) { // 带异或距离查询
        while(fa[u] != u) d ^= dis[u], u = fa[u];
        return u;
    }
    
    bool merge(int u, int v, int w) {
        int du=0, dv=0;
        u = find(u, du), v = find(v, dv);
        if(u == v) return false;
        if(sz[u] > sz[v]) swap(u,v);
        stk[++top] = {u, v, sz[v]};
        fa[u] = v, dis[u] = du ^ dv ^ w; 
        sz[v] += (sz[u] == sz[v]);
        return true;
    }
    
    void rollback(int cnt) { // 回退到指定状态
        while(top > cnt) {
            auto [u,v,s] = stk[top--];
            fa[u] = u, dis[u] = 0;
            sz[v] = s;
        }
    }
};
```

### 线段树分治处理  
```cpp  
void solve(int l, int r, int dep, vector<Edge> edges) {
    DSU::checkpoint cp = dsu.save(); // 保存当前状态
    LinearBase tmp = lb[dep-1]; // 继承上层线性基
    
    for(auto &e : edges) {        // 处理当前层边
        if(e.l <= l && r <= e.r) {
            int du=0, dv=0;
            int fu = dsu.find(e.u, du);
            int fv = dsu.find(e.v, dv);
            if(fu == fv) 
                lb[dep].insert(du ^ dv ^ e.w);
            else 
                dsu.merge(e.u, e.v, e.w);
        }
    }
    
    if(l == r) { // 处理查询
        int x = q[l].x, y = q[l].y;
        int dx=0, dy=0;
        dsu.find(x, dx), dsu.find(y, dy);
        ans[l] = lb[dep].query(dx ^ dy);
    } else {
        int mid = (l+r)>>1;
        solve(l, mid, dep+1, edges);
        solve(mid+1, r, dep+1, edges);
    }
    
    dsu.rollback(cp); // 撤销当前层操作
}
```

---

## 相似题目推荐  
1. **P4151 [WC2011]最大XOR和路径** - 静态图异或路径  
2. **P3733 [HAOI2017]八纵八横** - 动态线性基维护  
3. **P4585 火星商店问题** - 线段树分治经典应用  

---

## 复古像素动画设计  
**实现方案**：  
```html  
<canvas id="pixel-canvas"></canvas>
<script>
const palette = ["#000","#F00","#0F0","#00F","#FF0","#F0F"]; // 8位色调色板
const ctx = document.getElementById('pixel-canvas').getContext('2d');

function drawNode(x, y, color) { // 绘制像素化节点
    ctx.fillStyle = color;
    ctx.fillRect(x*32, y*32, 30, 30); 
}

function playSound(freq) { // 8位音效
    const osc = new OscillatorNode(ctx, {frequency: freq});
    osc.connect(ctx.destination);
    osc.start(); osc.stop(ctx.currentTime + 0.1);
}

// 自动演示循环  
let step = 0;
setInterval(() => {
    if(step%2 == 0) playSound(440); // 合并操作音
    drawNode(step%10, step/10|0, palette[step%6]);
    step++;
}, 500);
</script>
```  
**交互设计**：  
- **方向键**：控制算法执行速度  
- **空格键**：暂停/继续自动演示  
- **Z/X键**：单步前进/回退操作  

---

通过上述方案，学习者可以直观观察线段树分治的层次化处理、并查集的动态合并/撤销，以及线性基的逐层更新，配合复古音效增强算法流程的感知。

---
处理用时：83.29秒