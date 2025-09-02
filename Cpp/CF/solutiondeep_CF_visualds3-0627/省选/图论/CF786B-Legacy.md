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



### 唯一算法分类
线段树优化建图

### 综合分析与结论
**核心思路**：建立两棵线段树（出树和入树），通过线段树节点表示区间，将点与区间、区间与点的连边操作转化为对数个线段树节点的连边，总边数从 O(n²) 优化至 O(n log n + q log n)。

**算法流程**：
1. **线段树构建**：
   - 出树（自上而下）：父节点向子节点连边权为 0 的边，用于处理点→区间的操作
   - 入树（自下而上）：子节点向父节点连边权为 0 的边，用于处理区间→点的操作
   - 两棵树的叶子节点相互连接，表示实际图中的点

2. **连边操作**：
   - 点→区间：从出树叶子节点向出树对应区间节点连边
   - 区间→点：从入树对应区间节点向入树叶子节点连边

3. **最短路计算**：以起点所在叶子节点为源点，跑 Dijkstra 算法

**可视化设计要点**：
- **颜色标记**：出树用蓝色表示，入树用橙色，实际节点为绿色，当前处理的区间节点高亮闪烁
- **动画步骤**：
  1. 展示两棵线段树的层级结构
  2. 操作2时，从绿点向蓝色区间节点扩散黄色连接线
  3. 操作3时，从橙色区间节点向绿点扩散红色连接线
  4. 最短路算法运行时，用光波扩散效果表示距离更新

### 题解清单 (≥4星)
1. **tzc_wk（5星）**：双线段树结构清晰，配图直观展示节点连接关系
2. **maoyiting（4.5星）**：详细说明入树和出树的连边方向，代码可读性强
3. **LawrenceSivan（4星）**：完整注释代码 + 分步骤讲解建图逻辑

### 核心代码实现
```cpp
const int D = 5e5;
int n, q, s, leaf[100005];
vector<pair<int, int>> g[1000005];

void build(int k, int l, int r) {
    if (l == r) {
        leaf[l] = k;
        return;
    }
    int mid = (l + r) >> 1;
    g[k].push_back({k<<1, 0});    // 出树向下连
    g[k].push_back({k<<1|1, 0});
    g[(k<<1)+D].push_back({k+D, 0}); // 入树向上连
    g[(k<<1|1)+D].push_back({k+D, 0});
    build(k<<1, l, mid);
    build(k<<1|1, mid+1, r);
}

void connect(int k, int l, int r, int v, int w, int tp) {
    if (l <= s[k].l && s[k].r <= r) {
        if (tp) g[k+D].push_back({v, w}); // 入树区间→点
        else g[v].push_back({k, w});     // 点→出树区间
        return;
    }
    // 递归处理子区间...
}

// 操作处理示例：
for (int i = 1; i <= n; i++) {
    g[leaf[i]].push_back({leaf[i]+D, 0}); // 连接两棵树叶子
    g[leaf[i]+D].push_back({leaf[i], 0});
}
```

### 同类型题扩展
- **区间覆盖优化**：POJ 3667 Hotel（线段树区间覆盖）
- **多层图优化**：LOJ 分块九练（分块思想处理区间）

### 推荐题目
1. [P3588 [POI2015] PUS](https://www.luogu.com.cn/problem/P3588)
2. [P5025 [SNOI2017] 炸弹](https://www.luogu.com.cn/problem/P5025)
3. [P6348 [PA2011] Journeys](https://www.luogu.com.cn/problem/P6348)

### 复古像素化实现思路
1. **Canvas 绘制**：
   - 使用 32x32 像素块表示线段树节点
   - 出树绘制在左侧（蓝调），入树在右侧（橙调）
   - 连边时显示 8-bit 风格的闪电动画

2. **音效设计**：
   - 连边成功：NES 风格的 "哔" 声（440Hz 方波）
   - 最短路更新：快速上升琶音
   - 错误操作：低沉噪音

3. **自动演示模式**：
   ```javascript
   function autoDemo() {
     showBuildTree();      // 展示建树过程
     setTimeout(() => showConnect(2), 2000); // 演示操作2
     setTimeout(() => showConnect(3), 4000); // 演示操作3
     setTimeout(runDijkstra, 6000);          // 自动运行最短路
   }
   ```

### 调试心得
- **线段树编号冲突**：初始未考虑两棵树节点编号范围，导致越界
- **边权方向混淆**：入树连边时误用出树方向，通过单步调试发现
- **叶子节点连接**：忘记双向连接两棵树叶子，导致最短路无法传递

---

通过将复杂的区间操作抽象为线段树节点间的连接，该算法在时间和空间效率上均有质的提升。配合像素化演示，可直观理解线段树优化建图的核心思想。

---
处理用时：75.59秒