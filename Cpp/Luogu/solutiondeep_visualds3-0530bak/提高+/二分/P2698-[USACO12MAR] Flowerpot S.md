# 题目信息

# [USACO12MAR] Flowerpot S

## 题目描述

Farmer John has been having trouble making his plants grow, and needs your help to water them properly.  You are given the locations of N raindrops (1 <= N <= 100,000) in the 2D plane, where y represents vertical height of the drop, and x represents its location over a 1D number line:

 ![](https://cdn.luogu.com.cn/upload/pic/9174.png) 

Each drop falls downward (towards the x axis) at a rate of 1 unit per second.  You would like to place Farmer John's flowerpot of width W somewhere along the x axis so that the difference in time between the first raindrop to hit the flowerpot and the last raindrop to hit the flowerpot is at least some amount D (so that the flowers in the pot receive plenty of water).  A drop of water that lands just on the edge of the flowerpot counts as hitting the flowerpot. 

Given the value of D and the locations of the N raindrops, please compute the minimum possible value of W.

老板需要你帮忙浇花。给出 $N$ 滴水的坐标，$y$ 表示水滴的高度，$x$ 表示它下落到 $x$ 轴的位置。

每滴水以每秒 $1$ 个单位长度的速度下落。你需要把花盆放在 $x$ 轴上的某个位置，使得从被花盆接着的第 $1$ 滴水开始，到被花盆接着的最后 $1$ 滴水结束，之间的时间差至少为 $D$。

我们认为，只要水滴落到 $x$ 轴上，与花盆的边沿对齐，就认为被接住。给出 $N$ 滴水的坐标和 $D$ 的大小，请算出最小的花盆的宽度 $W$。

## 说明/提示

有 $4$ 滴水，$(6,3)$ ，$(2,4)$ ，$(4,10)$ ，$(12,15)$ 。水滴必须用至少 $5$ 秒时间落入花盆。花盆的宽度为 $2$ 是必须且足够的。把花盆放在 $x=4\dots6$ 的位置，它可以接到 $1$ 和 $3$ 水滴, 之间的时间差为 $10-3=7$ 满足条件。

**【数据范围】**

$40\%$ 的数据：$1 \le N \le 1000$ ，$1 \le D \le 2000$ 。

$100\%$ 的数据：$1 \le N \le 10 ^ 5$ ，$1 \le D \le 10 ^ 6$ ，$0\le x,y\le10^6$ 。

## 样例 #1

### 输入

```
4 5
6 3
2 4
4 10
12 15```

### 输出

```
2```

# AI分析结果



**算法分类**  
二分答案

---

**题解思路与核心分析**  
题目要求找到最小的花盆宽度，使得花盆接到的雨滴时间差至少为 D。核心思路是通过二分答案确定宽度，利用单调队列维护滑动窗口内的最大值和最小值以验证当前宽度是否可行。

**二分过程关键点**  
1. **搜索区间**：初始左边界为0，右边界为最大x坐标差。  
2. **验证方法**：对每个二分值 mid，维护两个单调队列：  
   - 单调递减队列存储窗口内的最大值  
   - 单调递增队列存储窗口内的最小值  
   每次右指针移动时更新队列，左指针移动时弹出过期元素。  
3. **边界收缩**：若窗口内极差 ≥D，则尝试缩小右边界；否则扩大左边界。

---

**题解评分（≥4星）**  
1. **llzzxx712（5星）**  
   - 思路清晰，完整实现二分+单调队列  
   - 代码注释详尽，处理边界条件严谨  
   - 关键优化：遍历左端点时动态维护队列  

2. **青衫白叙（5星）**  
   - 直接双指针+单调队列，无需二分，O(n)复杂度  
   - 利用r的单调性优化遍历过程  
   - 代码简洁高效，处理队列更新逻辑明确  

3. **老K（4星）**  
   - 提出“拉窗口”的双指针思路  
   - 代码实现类似滑动窗口，时间复杂度优秀  
   - 桶排序预处理减少排序开销  

---

**最优思路提炼**  
1. **双指针+单调队列**：  
   - 左指针遍历，右指针单调扩展，确保每个元素仅入队两次  
   - 两个队列分别维护最大/最小值，队列头部即为当前窗口极值  
   - 窗口满足条件时立即记录最小宽度  

2. **二分答案的验证优化**：  
   - 滑动窗口验证时队列维护需严格与窗口位置同步  
   - 初始将雨滴按x排序，确保窗口连续性  

---

**同类型题目与算法套路**  
1. **滑动窗口极值**（模板题：P1886）  
2. **二分答案验证**（如：P1873 砍树求最值）  
3. **区间极值差约束**（如：P1712 [NOI2016] 区间）  

**推荐题目**  
1. P1886 滑动窗口  
2. P1102 A-B 数对（二分查找差值）  
3. P1712 [NOI2016] 区间  

---

**个人心得摘录**  
- **边界处理**：初始化 ans 为极大值，避免无解未处理（llzzxx712）  
- **单调队列维护顺序**：右指针扩展时先维护队列再判断条件，避免遗漏（青衫白叙）  
- **无需二分的顿悟**：“当左端点右移时，右端点只需继续扩展而非回溯”（老K）  

---

**可视化设计（二分过程）**  
```javascript
// 伪代码演示二分过程
function binarySearch() {
  let left = 0, right = maxX;
  while (left <= right) {
    const mid = Math.floor((left + right) / 2);
    if (check(mid)) {  // 绿色高亮mid
      right = mid - 1; // 收缩右边界（红色箭头）
      updateVisual(mid, 'valid'); 
    } else {
      left = mid + 1;  // 扩展左边界（蓝色箭头）
      updateVisual(mid, 'invalid');
    }
  }
}

// 单调队列维护动画
function updateQueues(r) {
  while (maxQueue.length && y[r] >= maxQueue.last().y) {
    maxQueue.pop(); // 弹出队尾（黄色闪烁）
  }
  maxQueue.push({x: r, y: y[r]}); // 入队（绿色高亮）
  // 类似处理minQueue...
}
```

**复古像素化实现**  
- **Canvas绘制**：x轴以像素块表示雨滴，窗口区间用绿色边框  
- **音效设计**：  
  - 移动指针时播放8-bit“滴”声  
  - 找到解时播放胜利音效（类似马里奥吃金币）  
- **自动演示模式**：AI按帧推进二分步骤，速度可调  

---

**核心代码（双指针+单调队列）**  
```cpp
struct Point { int x, y; };
Point a[N];
int qmax[N], qmin[N], hmax=0, tmax=-1, hmin=0, tmin=-1;

int solve() {
  sort(a+1, a+n+1, [](Point a, Point b){ return a.x < b.x; });
  int ans = INF;
  for (int l=1, r=1; r <= n; r++) {
    // 维护最大值队列（递减）
    while (hmax <= tmax && a[r].y >= a[qmax[tmax]].y) tmax--;
    qmax[++tmax] = r;
    // 维护最小值队列（递增）
    while (hmin <= tmin && a[r].y <= a[qmin[tmin]].y) tmin--;
    qmin[++tmin] = r;
    
    // 收缩左边界直到不满足条件
    while (a[qmax[hmax]].y - a[qmin[hmin]].y >= d) {
      ans = min(ans, a[r].x - a[l].x);
      if (qmax[hmax] == l) hmax++;
      if (qmin[hmin] == l) hmin++;
      l++;
    }
  }
  return ans == INF ? -1 : ans;
}
```

---
处理用时：185.87秒