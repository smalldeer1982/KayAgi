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



# 【算法分类】  
**二分答案 + 单调队列**

---

# 【题解思路与核心难点】  
### **核心思路**  
1. **二分答案**：花盆宽度具有单调性（更大宽度一定满足时间差条件），通过二分确定最小可行宽度  
2. **滑动窗口+双单调队列**：固定宽度后，维护窗口内最大值（单调递减队列）和最小值（单调递增队列），检查差值是否≥D  

### **解决难点**  
1. **窗口移动的同步性**：两个单调队列需要同步处理窗口左端点出队  
2. **坐标离散化**：输入点无序需先按x坐标排序  
3. **边界条件处理**：花盆边缘恰好接触水滴也视为有效  

### **关键变量与操作**  
| 变量/操作 | 作用 |  
|-----------|------|  
| `deque<node> qmax, qmin` | 分别维护窗口内最大/最小y值 |  
| `qmax.pop_front()` | 窗口左移时弹出超出范围的元素 |  
| `while(qmax.back()<=cur) pop_back()` | 维护队列单调性 |  

---

# 【题解清单 (≥4星)】  
**4.5星**：llzzxx712  
- **亮点**：双单调队列实现清晰，注释详细，处理队列同步移动的边界条件严谨  
- **代码片段**：  
```cpp  
while(a[p1[head1]].y - a[p2[head2]].y < d && r<n) {  
    r++;  
    while(a[p1[tail1]].y < a[r].y) tail1--; //维护最大值队列  
    while(a[p2[tail2]].y > a[r].y) tail2--; //维护最小值队列  
}  
```  

**4星**：青衫白叙  
- **亮点**：右端点单调性证明简洁，代码结构紧凑  
- **个人心得**："如果一个左端点对应右端点r1，则更大的左端点对应r2≥r1"  

**4星**：老K  
- **亮点**：提出桶排序替代sort，时间效率优化  
- **关键代码**：  
```cpp  
int s=1;  
for(int i=1;i<=n;++i){  
    while(s<=n && !ok(i,s))++s;  
    f[i]=s; //f[i]单调不减  
}  
```  

---

# 【最优思路与技巧提炼】  
### **关键技巧**  
1. **双指针同步窗口**：左指针i右移时，右指针j只需单调右移，无需回溯  
2. **队列维护方向**：  
   - 最大值队列：新元素≥队尾时弹出队尾（维护递减）  
   - 最小值队列：新元素≤队尾时弹出队尾（维护递增）  
3. **二分答案检验**：将原问题转化为固定窗口大小的判定问题  

### **同类型题拓展**  
- **滑动窗口最值**：P1886 滑动窗口（模板题）  
- **二分答案+单调性**：P1419 寻找段落（均值最大子段）  

---

# 【推荐相似题目】  
1. **P1886** - 滑动窗口（单调队列模板）  
2. **P1712** - [NOI2016] 区间（滑动窗口+离散化）  
3. **P1419** - 寻找段落（二分答案+单调队列）  

---

# 【可视化与算法演示】  
### **动画方案**  
1. **像素风格界面**：  
   - 背景：黑色网格表示x轴，蓝色像素点表示水滴  
   - 花盆：红色矩形框，宽度随二分过程动态调整  
   - 队列状态：左侧显示qmax（黄色）、qmin（绿色）的队列元素  

2. **关键步骤高亮**：  
   - **窗口移动**：花盆框闪烁提示当前检查的窗口范围  
   - **队列更新**：入队元素高亮橙色，出队元素变灰  

3. **音效设计**：  
   - 队列弹出：8-bit "哔"声  
   - 找到解：NES过关音效  
   - 二分区间更新：电子"滴答"声  

### **交互控制**  
```javascript  
// 伪代码示例  
class Animation {  
  constructor() {  
    this.speed = 100; // 每步延迟(ms)  
    this.playMode = 'auto'; // auto/step  
  }  

  step() {  
    if (checkMid()) {  
      drawRedBox(mid); // 绘制当前花盆  
      updateQueues();  // 更新队列动画  
      playSound('blip');  
    }  
  }  
}  
```  

---

# **代码实现（核心逻辑）**  
```cpp  
bool check(int w) {  
    deque<int> qmax, qmin;  
    for(int i=1; i<=n; i++){  
        // 移除左边界外元素  
        while(!qmax.empty() && a[qmax.front()].x < a[i].x - w)  
            qmax.pop_front();  
        while(!qmin.empty() && a[qmin.front()].x < a[i].x - w)  
            qmin.pop_front();  

        // 维护队列单调性  
        while(!qmax.empty() && a[i].y >= a[qmax.back()].y)  
            qmax.pop_back();  
        qmax.push_back(i);  

        while(!qmin.empty() && a[i].y <= a[qmin.back()].y)  
            qmin.pop_back();  
        qmin.push_back(i);  

        if(a[qmax.front()].y - a[qmin.front()].y >= D)  
            return true;  
    }  
    return false;  
}  
```

---
处理用时：75.85秒