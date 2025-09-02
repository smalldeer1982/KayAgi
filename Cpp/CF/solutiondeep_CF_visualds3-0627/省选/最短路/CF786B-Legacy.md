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



# 算法分类
**线段树优化建图**

---

## 题解思路与核心难点

### 核心算法流程
1. **双线段树结构**：构建两棵线段树（入树和出树）
   - 入树：子节点向父节点连边（0权值），用于处理区间到点的连接（操作3）
   - 出树：父节点向子节点连边（0权值），用于处理点到区间的连接（操作2）
2. **叶子节点互通**：两棵线段树的叶子节点相互连接（0权值），确保路径互通
3. **区间操作优化**：
   - 操作2：从出树叶子节点向入树的区间拆分节点连边
   - 操作3：从出树的区间拆分节点向入树叶子节点连边
4. **最短路计算**：使用Dijkstra算法处理带权边

### 解决难点
- **边数爆炸问题**：通过线段树将O(n²)边数优化为O(n log n)级别
- **方向控制**：入树处理流入操作，出树处理流出操作，通过树结构自动维护方向性
- **多级节点映射**：建立虚拟节点系统，原始点映射到两棵线段树的叶子节点

---

## 题解评分（≥4星）

1. **tzc_wk（5星）**
   - 亮点：清晰的图示说明两棵线段树结构，代码实现规范
   - 关键代码：
     ```cpp
     // 线段树构建
     void build(int k,int l,int r){
         if(l==r){ leaf[l]=k; return; }
         g[k].push_back({k<<1,0}); // 出树边
         g[(k<<1)+D].push_back({k+D,0}); // 入树边
     }
     ```

2. **maoyiting（4.5星）**
   - 亮点：详细描述入树/出树区别，附带完整代码
   - 关键优化：使用常数D区分两棵线段树的内存空间

3. **Karry5307（4星）**
   - 亮点：ST表替代线段树的创新解法，时间复杂度更优
   - 核心代码：
     ```cpp
     // ST表预处理
     for(int w=1;w<LOG;w++)
         for(int i=1;i+(1<<w)-1<=n;i++)
             st[w][i][0]=++tot; // 出节点
     ```

---

## 最优技巧提炼

### 数据结构设计
1. **双树映射系统**：
   ```text
   原始点 → 出树叶子 ←0→ 入树叶子 ←0→ 原始点
   ```
2. **虚拟区间节点**：每个线段树节点代表一个区间，连接时自动处理区间拆分

### 实现技巧
- **内存预分配**：使用偏移量（如D=5e5）区分两棵树
- **分层建边**：先构建线段树结构边，再处理题目特定边

---

## 同类型题目推荐
1. [P3588 [POI2015] PUS](https://www.luogu.com.cn/problem/P3588)
2. [P5025 [SNOI2017] 炸弹](https://www.luogu.com.cn/problem/P5025)
3. [CF1045A Last chance](http://codeforces.com/problemset/problem/1045/A)

---

## 可视化设计

### 算法演示方案
**8位像素风格动画**：
1. **线段树结构展示**：
   - 绿色方块表示出树节点，红色表示入树节点
   - 黄色线条连接父子节点（方向箭头区分出/入树）

2. **连边过程**：
   ```javascript
   // 示例：操作2连边动画
   function drawEdge(v, l, r) {
       let segNodes = splitSegment(l, r); // 获取拆分后的区间节点
       segNodes.forEach(node => {
           animateArrow(v, node, 0xFF9900); // 橙色箭头表示操作2
           playSound('connect.wav');
       });
   }
   ```

3. **最短路追踪**：
   - 紫色光点沿Dijkstra的优先队列移动
   - 已确定节点变为灰色，未处理节点保持闪烁

### 交互功能
- **速度控制**：滑块调节动画速度（0.5x~5x）
- **模式切换**：手动步进/AutoPlay
- **音效反馈**：
  - 连边时：8-bit "哔"声
  - 路径更新：上升音阶
  - 错误操作：低频警报声

---

## 核心代码示例

### 线段树构建
```cpp
const int D = 5e5;
void build(int k, int l, int r) {
    if(l == r) {
        in_tree[l] = k;       // 入树叶子
        out_tree[l] = k + D;  // 出树叶子
        return;
    }
    // 出树向下连边
    addEdge(k, k<<1, 0);
    addEdge(k, (k<<1)+1, 0);
    // 入树向上连边 
    addEdge((k<<1)+D, k+D, 0);
    addEdge((k<<1|1)+D, k+D, 0);
    build(lson); build(rson);
}
```

### 区间操作处理
```cpp
// 操作2：点v向区间[l,r]连边
void connect(int v, int l, int r, int w) {
    if(l > r) return;
    function<void(int,int,int)> dfs = [&](int k, int L, int R) {
        if(l <= L && R <= r) {
            addEdge(out_tree[v], k, w);
            return;
        }
        if(l <= mid) dfs(lson);
        if(r > mid) dfs(rson);
    };
    dfs(1, 1, n);
}
```

---

## 总结
本题解通过**双线段树结构**将区间操作优化为对数级别，结合Dijkstra算法，在保证正确性的同时大幅降低时间复杂度。可视化设计采用游戏化交互，帮助理解虚拟节点的映射关系和最短路传播过程。同类题目可基于此模板进行拓展，重点掌握线段树优化建图的核心思想。

---
处理用时：68.43秒