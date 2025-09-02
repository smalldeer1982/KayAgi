# 题目信息

# Mike and Fish

## 题目描述

As everyone knows, bears love fish. But Mike is a strange bear; He hates fish! The even more strange thing about him is he has an infinite number of blue and red fish.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF547D/031dc6fdab66492c31079b30a48004c3918930a2.png)He has marked $ n $ distinct points in the plane. $ i $ -th point is point $ (x_{i},y_{i}) $ . He wants to put exactly one fish in each of these points such that the difference between the number of red fish and the blue fish on each horizontal or vertical line is at most 1.

He can't find a way to perform that! Please help him.

## 样例 #1

### 输入

```
4
1 1
1 2
2 1
2 2
```

### 输出

```
brrb
```

## 样例 #2

### 输入

```
3
1 1
1 2
2 1
```

### 输出

```
brr
```

# AI分析结果



---

## 唯一算法分类  
**无算法分类**  

---

## 综合分析与结论  
该问题的核心是构造一种颜色分配方案，使得每条水平线或垂直线上的红蓝鱼数量差不超过 1。题解主要围绕以下两种思路展开：  
1. **二分图染色**：将同一行/列的点两两配对形成边，构建二分图后进行染色，确保每行/列最多剩余一个未配对点。  
2. **欧拉回路定向**：将横纵坐标视为顶点，点视为边，通过欧拉回路定向边，保证每个顶点的入度与出度差不超过 1。  

**关键难点与解决思路**：  
- 如何保证每行/列颜色差 ≤1 → 通过配对或欧拉回路定向强制平衡。  
- 处理奇度数顶点 → 引入虚拟点使其度数为偶，确保欧拉回路存在。  

**可视化设计思路**（以欧拉回路为例）：  
- **动画方案**：  
  - 将横纵坐标绘制为两列顶点，点 $(x_i,y_i)$ 显示为连接 $x_i$ 和 $y_i$ 的边。  
  - 用不同颜色（红/蓝）表示边的方向（$x_i→y_i$ 或 $y_i→x_i$）。  
  - 高亮当前遍历的边，动态更新顶点的入度/出度统计。  
- **复古像素风格**：  
  - 使用 8-bit 色块表示顶点，箭头表示边方向。  
  - 音效：遍历边时播放“滴”声，完成回路后播放成功音效。  
- **AI 自动演示**：模拟欧拉回路的逐步构建过程，展示边的定向逻辑。  

---

## 题解清单（≥4星）  
1. **shadowice1984（4星）**  
   - **亮点**：简单配对+二分图染色，代码简洁易懂。  
   - **关键代码**：横向/纵向配对后 DFS 染色。  
2. **Kinandra（5星）**  
   - **亮点**：欧拉回路定向法，时间复杂度 O(n)，理论严谨。  
   - **关键代码**：虚拟点处理奇度数顶点，欧拉回路遍历。  
3. **xht（5星）**  
   - **亮点**：极简实现，仅 30 行代码完成欧拉回路逻辑。  

---

## 最优思路与技巧提炼  
1. **图模型转化**：将点 $(x_i,y_i)$ 视为连接横纵坐标顶点的边，问题转化为边定向问题。  
2. **欧拉回路处理奇点**：通过连接虚拟点使所有顶点度数为偶，保证回路存在。  
3. **边定向即颜色分配**：欧拉回路中边的方向决定红/蓝，确保出入度差 ≤1。  

---

## 同类型题与算法套路  
- **类似算法**：欧拉回路定向（CF429E）、二分图染色（棋盘覆盖问题）。  
- **核心套路**：将几何问题转化为图论模型，利用图的性质（如二分图、欧拉回路）构造解。  

---

## 推荐相似题目  
1. [CF429E] Points and Segments  
2. [洛谷 P3520] 最小生成树计数  
3. [洛谷 P6066] Watchcow（欧拉回路模板）  

---

## 个人心得摘录  
- **shadowice1984**：提到“红蓝染色失败的唯一可能是存在奇环，但未找到构造反例的方法”。  
- **tzc_wk**：强调“将点转化为边的技巧是解题关键，类似 CF429E 的套路”。  

---

## 核心代码实现（欧拉回路法）  
```cpp  
// xht 的代码（核心逻辑）  
const int N = 2e5 + 7;  
int n, v[N<<1], d[N<<1], h[N<<1], e[N<<2], t[N<<2], c = 1;  

void add(int x, int y) {  
    e[++c] = y, t[c] = h[x], h[x] = c;  
    if (x != 0 && y != 0) add(y, x); // 无向边  
}  

void dfs(int x) {  
    for (int &i = h[x]; i; i = t[i])  
        if (!v[i>>1])  
            v[i>>1] = (x < N ? 1 : 2), dfs(e[i]);  
}  

int main() {  
    rd(n);  
    for (int i = 1, x, y; i <= n; i++) {  
        rd(x), rd(y);  
        add(x, y + N);  
        d[x]++, d[y + N]++;  
    }  
    // 处理奇度数顶点  
    for (int i = 1; i < N << 1; i++)  
        if (d[i] & 1) add(0, i);  
    // 跑欧拉回路  
    for (int i = 1; i < N; i++) dfs(i);  
    // 输出颜色  
    for (int i = 1; i <= n; i++)  
        putchar("br"[v[i] - 1]);  
}  
```  

---

## 可视化设计要点  
1. **Canvas 动态绘制**：  
   - 左侧列表示横坐标顶点，右侧列表示纵坐标顶点。  
   - 边动态绘制为箭头，红色表示 $x→y$，蓝色表示 $y→x$。  
2. **音效触发**：  
   - 每次遍历边时触发“滴”声，成功定向后播放 8-bit 胜利音效。  
3. **AI 自动演示**：  
   - 初始化后自动遍历所有顶点，模拟欧拉回路生成过程。  
   - 单步执行模式允许观察每个顶点的处理步骤。  

通过交互式学习，用户可直观理解欧拉回路如何保证颜色平衡，并掌握图模型转化的核心技巧。

---
处理用时：77.55秒