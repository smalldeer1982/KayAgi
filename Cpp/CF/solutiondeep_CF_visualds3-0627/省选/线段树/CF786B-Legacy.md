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



**算法分类**  
线段树优化建图

---

### **综合分析与结论**

**核心思路**：
- 建立两棵线段树（出树和入树），通过线段树的区间拆分特性将点与区间、区间与点的连边拆分为对数级别的边数，避免暴力连边。
- 出树（父节点向子节点连0权边）处理**点→区间**连边，入树（子节点向父节点连0权边）处理**区间→点**连边，两棵树的叶子节点共享原图节点。
- 通过Dijkstra算法求解最短路。

**可视化设计**：
- **线段树结构展示**：用不同颜色区分出树和入树，动态展示线段树节点的拆分过程。
- **连边动画**：当处理区间连边时，高亮对应的线段树节点并显示权值边的建立。
- **Dijkstra过程**：用颜色渐变表示距离更新，优先队列的弹出节点以闪烁效果标记。
- **复古像素风格**：使用8位色块表示线段树节点，连边时播放经典音效，背景音乐采用8位循环曲调。

---

### **题解清单（≥4星）**

1. **tzc_wk（5星）**  
   - **亮点**：代码结构清晰，两棵线段树通过偏移量D区分，边处理逻辑简洁。
   - **关键代码**：
     ```cpp
     const int D=5e5;
     void build(int k,int l,int r) { // 两棵树共用build函数
         if(l==r) { leaf[l]=k; return; }
         // 父子节点连0权边
         g[k].push_back(pii(k<<1,0)); g[k].push_back(pii(k<<1|1,0));
         build(k<<1,l,mid); build(k<<1|1,mid+1,r);
     }
     ```

2. **maoyiting（4星）**  
   - **亮点**：详细图示解释入树和出树的方向，代码中通过K区分两棵树。
   - **关键代码**：
     ```cpp
     void build(int p,int l,int r) {
         if(l==r) { a[l]=p; return; }
         add(p,p<<1,0); add(p,p<<1|1,0); // 出树向下连边
         add((p<<1)+K,p+K,0); add((p<<1|1)+K,p+K,0); // 入树向上连边
     }
     ```

3. **LawrenceSivan（4星）**  
   - **亮点**：通过递归建树明确父子关系，代码注释详细。
   - **关键代码**：
     ```cpp
     void build_in(int &rt,int l,int r) {
         rt=++tot; // 动态开点
         if(l==r) { in[l]=rt; return; }
         build_in(ls[rt],l,mid); build_in(rs[rt],mid+1,r);
         add(ls[rt],rt,0); add(rs[rt],rt,0); // 入树向上连边
     }
     ```

---

### **最优思路与技巧**

1. **两棵线段树结构**  
   - **出树**：父节点向子节点连0权边，用于处理**点→区间**操作。
   - **入树**：子节点向父节点连0权边，用于处理**区间→点**操作。
   - **叶子节点共享**：两棵树的叶子节点对应原图节点，通过0权边互连。

2. **区间拆分为线段树节点**  
   - 例如，点v到区间[l,r]的连边转换为v连向覆盖[l,r]的O(logn)个线段树节点。

3. **Dijkstra优化**  
   - 使用优先队列实现，总时间复杂度O((n+q) logn logn)。

---

### **类似题目推荐**

1. [P3588 [POI2015]PUS](https://www.luogu.com.cn/problem/P3588)  
2. [P5025 [SNOI2017]炸弹](https://www.luogu.com.cn/problem/P5025)  
3. [CF1045A Last chance](https://www.luogu.com.cn/problem/CF1045A)

---

### **代码片段（tzc_wk）**

```cpp
const int D=5e5;
int n=read(),m=read(),st=read(),dist[1000005],leaf[100005];
vector<pii> g[1000005];

void build(int k,int l,int r) {
    if(l==r) { leaf[l]=k; return; }
    g[k].push_back(pii(k<<1,0)); // 出树向下连边
    g[k].push_back(pii(k<<1|1,0));
    build(k<<1,l,mid); build(k<<1|1,mid+1,r);
}

void connect(int k,int l,int r,int v,int w,int tp) {
    if(l<=s[k].l&&s[k].r<=r) {
        if(tp) g[k+D].push_back(pii(v,w)); // 入树连边
        else g[v].push_back(pii(k,w)); // 出树连边
        return;
    }
    // 递归处理子区间
}

priority_queue<pii,vector<pii>,greater<pii>> q;
q.push(pii(0,leaf[st]+D)); // 起点为入树的叶子节点
```

---

### **可视化设计**

1. **动画流程**  
   - **步骤1**：展示两棵线段树的构建过程，出树（蓝色）和入树（红色）。
   - **步骤2**：处理操作时，高亮涉及的线段树节点并绘制权值边（如点→区间时，出树节点闪烁黄色）。
   - **步骤3**：Dijkstra执行时，用绿色标记当前处理的节点，红色标记已确定最短路的节点。

2. **复古风格**  
   - **调色板**：16色，线段树节点用蓝色/红色块，边用白色像素线。
   - **音效**：连边时播放“哔”声，最短路更新时播放“叮”声。

3. **交互控制**  
   - 速度滑块调节动画速度，空格键暂停/继续。
   - “AI演示”模式自动逐步展示建图和最短路过程。

---
处理用时：77.73秒