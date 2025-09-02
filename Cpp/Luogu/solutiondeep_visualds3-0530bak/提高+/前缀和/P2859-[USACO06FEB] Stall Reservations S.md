# 题目信息

# [USACO06FEB] Stall Reservations S

## 题目描述

Oh those picky $N$ ($1 \leq N \leq 50,000$) cows! They are so picky that each one will only be milked over some precise time interval $A..B$ ($1 \leq A \leq B \leq 1,000,000$), which includes both times $A$ and $B$. Obviously, FJ must create a reservation system to determine which stall each cow can be assigned for her milking time. Of course, no cow will share such a private moment with other cows.

Help FJ by determining: The minimum number of stalls required in the barn so that each cow can have her private milking period. An assignment of cows to these stalls over time. Many answers are correct for each test dataset; a program will grade your answer.

约翰的 $N$（$1\leq N\leq 50000$）头奶牛实在是太难伺候了，她们甚至有自己独特的产奶时段。对于某一头奶牛，她每天的产奶时段是固定的时间段 $[A,B]$（即 $A$ 到 $B$，包括 $A$ 和 $B$）。这使得约翰必须开发一个调控系统来决定每头奶牛应该被安排到哪个牛棚去挤奶，因为奶牛们并不希望在挤奶时被其它奶牛看见。

请帮约翰计算：如果要满足奶牛们的要求，并且每天每头奶牛都要被挤过奶，至少需要多少牛棚和每头牛应该在哪个牛棚被挤奶。如果有多种答案，输出任意一种均可。


## 说明/提示

Explanation of the sample:







Here's a graphical schedule for this output:

Time     1  2  3  4  5  6  7  8  9 10


Stall 1 c1>>>>>>>>>>>>>>>>>>>>>>>>>>>


Stall 2 .. c2>>>>>> c4>>>>>>>>> .. ..


Stall 3 .. .. c3>>>>>>>>> .. .. .. ..


Stall 4 .. .. .. c5>>>>>>>>> .. .. ..Other outputs using the same number of stalls are possible.

由@FlierKing提供spj


## 样例 #1

### 输入

```
5
1 10
2 4
3 6
5 8
4 7```

### 输出

```
4
1
2
3
2
4```

# AI分析结果



---

### **算法分类**  
**贪心算法**

---

### **综合分析与结论**  
本题核心为区间调度问题，需确定最少不重叠区间分组数。最优解法采用**贪心策略**：按开始时间排序，维护最早结束的牛棚。  
**关键步骤**：  
1. 按开始时间排序所有区间，确保处理顺序。  
2. 使用优先队列（小根堆）维护当前牛棚的最早结束时间。  
3. 若当前牛的开始时间晚于堆顶结束时间，复用该牛棚并更新堆；否则新建牛棚。  

**难点**在于正确维护可用牛棚的状态并快速决策，优先队列高效解决了动态查找最早结束时间的需求。  

**可视化设计**：  
- **动画流程**：将牛按开始时间依次排列，优先队列动态展示最早结束时间。分配时高亮当前牛和堆顶元素，牛棚颜色区分。  
- **复古像素风**：用不同颜色方块代表牛棚，牛以像素图标表示移动至对应方块。音效提示分配成功或新建牛棚。  
- **交互控制**：支持暂停/继续，调整速度观察堆的更新与牛棚分配过程。

---

### **题解清单 (≥4星)**  
1. **sy_zmq_001 (5星)**  
   - **亮点**：代码简洁，优先队列反向存储实现小根堆，详细注释。  
   - **核心**：`priority_queue`存储负数结束时间，动态复用牛棚。  

2. **SegTre (5星)**  
   - **亮点**：结构体设计清晰，重载运算符直接维护小根堆。  
   - **核心**：堆中记录牛棚编号和结束时间，直接复用逻辑明确。  

3. **Santiego (5星)**  
   - **亮点**：极简实现，堆操作与答案记录一体化。  
   - **核心**：结构体`nod`直接关联牛棚编号，分配逻辑高效。  

---

### **最优思路提炼**  
**贪心 + 优先队列**  
1. **排序**：按开始时间升序处理区间。  
2. **维护堆**：堆中存储（结束时间, 牛棚编号），确保快速获取最早可用牛棚。  
3. **复用/新建**：若当前区间可插入堆顶牛棚则复用，否则新建。  

**关键代码片段**（sy_zmq_001）：  
```cpp
sort(cow + 1, cow + n + 1, cmp1); // 按开始时间排序
priority_queue<pair<int, int>> q; // 结束时间（负数）和牛棚编号
q.push(make_pair(-cow[1].end, 1));
for (int i = 2; i <= n; i++) {
    int earliest_end = -q.top().first;
    if (cow[i].begin > earliest_end) {
        int stall_id = q.top().second;
        q.pop();
        q.push(make_pair(-cow[i].end, stall_id)); // 复用
    } else {
        num++;
        q.push(make_pair(-cow[i].end, num)); // 新建
    }
}
```

---

### **同类型题与拓展**  
- **通用解法**：区间调度问题均可尝试贪心排序+动态维护最早结束点。  
- **类似题目**：  
  1. **LeetCode 253. 会议室 II**：同一模型，求最少会议室数。  
  2. **洛谷 P1803 线段覆盖**：选择最多不重叠区间。  
  3. **CF 1132F Clear the String**：区间动态规划变种。  

**推荐洛谷题目**：  
1. P4059 找爸爸（贪心排序）  
2. P2285 打鼹鼠（时间轴动态规划）  
3. P2949 工作调度（堆优化贪心）  

---

### **个人心得摘录**  
- **调试教训**（sy_zmq_001）：需注意排序后原序号丢失，必须记录原始索引以便输出。  
- **优化技巧**（SegTre）：重载运算符实现小根堆比存负数更直观，减少出错。  
- **思维突破**（sjie）：双指针法排序左右端点，避免堆操作，但分配逻辑较难理解。  

---

### **可视化与复古动画设计**  
**核心演示逻辑**：  
1. **初始化**：牛按开始时间排序后水平排列，右侧为优先队列（堆结构）。  
2. **步进分配**：  
   - 当前牛高亮，比较其开始时间与堆顶结束时间。  
   - 若可复用：牛移至对应牛棚方块，堆顶更新结束时间。  
   - 若不可用：新建牛棚，堆插入新结束时间。  
3. **音效与反馈**：  
   - 复用成功：短促“滴”声。  
   - 新建牛棚：低沉“咚”声。  

**复古风格**：  
- **8位色块**：牛棚用绿/蓝/黄像素块，牛图标为红色方块。  
- **Canvas动画**：网格布局，牛移动时有轨迹残影。  
- **自动演示**：按帧推进，用户可暂停调整速度。  

**代码片段（JS伪代码）**：  
```javascript
class StallVisualizer {
  constructor(cows) {
    this.cows = cows.sort((a, b) => a.start - b.start);
    this.heap = new PriorityQueue((a, b) => a.end < b.end);
    this.currentStep = 0;
  }

  nextStep() {
    if (this.currentStep >= this.cows.length) return;
    const cow = this.cows[this.currentStep];
    if (this.heap.peek()?.end < cow.start) {
      const stall = this.heap.pop();
      stall.end = cow.end; // 复用
      this.heap.push(stall);
    } else {
      this.heap.push({ end: cow.end, id: this.heap.size() + 1 }); // 新建
    }
    this.currentStep++;
  }
}
```  

--- 

**总结**：贪心结合优先队列是此类问题的标准解法，重点在于排序策略与数据结构的选择。通过动画演示可直观理解堆的动态维护过程，复古风格增添学习趣味性。

---
处理用时：91.80秒