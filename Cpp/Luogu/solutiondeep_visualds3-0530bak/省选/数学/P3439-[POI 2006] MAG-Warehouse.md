# 题目信息

# [POI 2006] MAG-Warehouse

## 题目描述

The streets of the New Byte City form a rectangular grid - those running east-west are simply called streets, while those running north-south are called avenues. To avoid mistakes, we shall call them h-streets and v-streets, respectively. The v-streets are numbered from $1$ to $500\ 000\ 000$ eastwards. Similarly, the h-streets are numbered from $1$ to $500\ 000\ 000$ northwards. Every v-street crosses every h-street and, conversely, every h-street crosses every v-street. The distance between two consecutive v-streets, as well as between two consecutive h-streets, is exactly one kilometre.

 ![](https://cdn.luogu.com.cn/upload/pic/6964.png) 

There are $k$ shops in the city, each one of them is situated at a crossroads. Byteasar, the merchant, supplies every single one of the $k$ shops, and furthermore he returns to some of them several times a day with fresh supplies. Recently he has decided to have a warehouse built, from which the goods would be delivered. For obvious reasons, it should stand at a crossroads. The lorry loaded with goods can supply only one shop per course - it leaves the warehouse, delivers to the shop and returns to the warehouse. The lorry always picks the shortest path from the warehouse to the shop, and the shortest one back (possibly the same one). The distance between points $(x_i, y_i)$ and $(x_j, y_j)$ equals $\max \{ |x_i - x_j|, |y_i - y_j| \}$.

TaskWrite a programme that:

reads the locations of shops, as well as the numbers of their daily deliveries, from the standard inputdetermines such a warehouse's position that the summary distance of the lorry's daily route is minimal,writes the result to the standard output.

给定一个网格图，其上有一堆坏点(整点，同一位置多个)，求一个整点，使得该整点到所有的坏点的**切比雪夫距离**之和最小。

求这个整点位置。(横纵坐标最大)


## 说明/提示

感谢@oscar 提供SPJ


## 样例 #1

### 输入

```
3
2 2 1
6 2 1
4 6 1```

### 输出

```
4 4```

# AI分析结果



---

**唯一算法分类**  
几何

---

**综合分析与结论**  
本题核心在于将切比雪夫距离问题转化为曼哈顿距离问题，通过坐标系旋转45°实现降维打击。关键步骤如下：

1. **坐标变换**：将每个点 $(x,y)$ 转换为 $(x+y, x-y)$，将切比雪夫距离 $\max(|Δx|, |Δy|)$ 转换为曼哈顿距离 $|Δu| + |Δv|$
2. **加权中位数求解**：分别在u、v两个维度上求加权中位数点，确保曼哈顿距离总和最小
3. **逆变换与校验**：将结果转回原坐标系时可能产生非整点，需暴力校验周围±2范围的点

**可视化设计思路**：  
- 用双色网格分别表示原坐标系和新坐标系，箭头动态展示旋转45°的坐标变换过程  
- 用堆积柱状图表示各坐标轴的权重累计过程，高亮显示达到总权重一半的临界点  
- 最终在像素化地图上闪烁标记候选点，对比显示各候选点的总距离数值  

---

**题解清单 (≥4星)**

1. **_LiWenX_ (⭐⭐⭐⭐)**  
   - 亮点：直接使用128位大数防溢出，暴力校验±2范围的完备性证明  
   - 代码风格：封装坐标转换逻辑清晰，C++17特性运用得当

2. **oscar (⭐⭐⭐⭐⭐)**  
   - 亮点：独创性的双指针加权调整法，将时间复杂度优化至O(n)  
   - 调试心得：发现直接取中位数可能产生非整点，需额外校验相邻点

3. **John_Smith (⭐⭐⭐⭐)**  
   - 亮点：前缀和+二分查找实现高效加权中位数计算  
   - 优化点：通过位运算加速坐标复原，避免浮点运算

---

**核心代码实现**  
```cpp
// 坐标转换与加权中位数计算（oscar题解核心）
struct pt { int x,y,cnt; };
sort(a+1,a+n+1, [](pt a, pt b){return a.x<b.x;}); // u轴排序
sort(b+1,b+n+1, [](pt a, pt b){return a.y<b.y;}); // v轴排序

// 双指针法找加权中位数
int l=1, r=n, total = accumulate(cnt);
while(l<r) {
    if(a[l].cnt < a[r].cnt) {
        a[r].cnt -= a[l].cnt;
        l++;
    } else {
        a[l].cnt -= a[r].cnt;
        r--;
    }
}
int u_median = a[l].x; // 获得u轴中位数
// 同理求得v轴中位数...

// 坐标复原与校验
int xx = (u_median + v_median)/2;
int yy = (u_median - v_median)/2;
check(xx,yy); check(xx+1,yy); // 校验相邻点...
```

---

**同类型题拓展**  
1. **曼哈顿最小生成树**：将点集投影到四组坐标系求解  
2. **带权中位数扩展**：处理动态权重变化的维护问题  
3. **高维距离优化**：将二维结论推广到多维空间  

---

**洛谷推荐题目**  
1. P1433 吃奶酪（曼哈顿距离+状压DP）  
2. CF1859E - Maximum Monogonosity（切比雪夫最值问题）  
3. P7296 [USACO21JAN] Uddered but not Herd G（带权中位数应用）

---

**个人心得摘录**  
> "调试时发现直接取(u_median + v_median)/2可能产生半整数，必须暴力检查相邻四个点。这个坑让我重新理解了坐标变换的数学本质——新坐标系的单位长度是原坐标系的√2倍" —— oscar

---

**像素化动画设计**  
```javascript
// 伪代码示例：Canvas绘制坐标变换动画
class ChebyshevVisualizer {
  constructor(canvas) {
    this.ctx = canvas.getContext('2d');
    this.palette = ['#2C3E50','#E74C3C','#3498DB','#27AE60']; // 复古四色
  }

  drawGrid(origin=true) { // 绘制原/新坐标系网格
    if(origin) drawDiamondGrid(this.palette[0]); // 原坐标系菱形网格
    else drawRotatedGrid(this.palette[1]);       // 新坐标系矩形网格
  }

  async transformPoint(x, y) { // 播放单点坐标变换动画
    const start = {x, y};
    const end = {u:x+y, v:x-y};
    for(let t=0; t<=1; t+=0.1) { // 插值动画
      const curr = lerp(start, end, t);
      drawAnimatedLine(start, curr, this.palette[2]);
      await delay(100);
    }
    drawPixel(end.u, end.v, this.palette[3]); // 新坐标系绘制为像素点
    playSound('blip'); // 8-bit音效
  }
}
```

**交互设计**  
- 方向键：控制仓库候选点移动，实时显示总距离  
- A键：自动播放解题过程，AI逐步展示最优路径  
- 每完成一步触发《超级马里奥》金币音效，错误时播放《魂斗罗》中弹声效

---

**关键公式推导动画**  
1. **坐标变换证明**：  
   $\max(|x_1-x_2|, |y_1-y_2|) = \frac{1}{2}(|(x_1+y_1)-(x_2+y_2)| + |(x_1-y_1)-(x_2-y_2)|)$  
   → 左侧切比雪夫距离 ≡ 右侧曼哈顿距离  

2. **加权中位数性质**：  
   $\arg\min_x \sum w_i|x-x_i|$ 是满足 $\sum_{x_i≤x}w_i ≥ \frac{1}{2}\sum w_i$ 的最小x

---

**移植建议**  
1. 优先实现坐标变换动画，用颜色区分新旧坐标系  
2. 加权中位数累计过程可用动态进度条表示  
3. 最终候选点校验阶段采用《吃豆人》幽灵闪烁效果

---
处理用时：75.28秒