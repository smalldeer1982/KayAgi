# 题目信息

# Airport

## 题目描述

Lolek and Bolek are about to travel abroad by plane. The local airport has a special "Choose Your Plane" offer. The offer's conditions are as follows:

- it is up to a passenger to choose a plane to fly on;
- if the chosen plane has $ x $ $ (x&gt;0) $ empty seats at the given moment, then the ticket for such a plane costs $ x $ zlotys (units of Polish currency).

The only ticket office of the airport already has a queue of $ n $ passengers in front of it. Lolek and Bolek have not stood in the queue yet, but they are already wondering what is the maximum and the minimum number of zlotys the airport administration can earn if all $ n $ passengers buy tickets according to the conditions of this offer?

The passengers buy tickets in turn, the first person in the queue goes first, then goes the second one, and so on up to $ n $ -th person.

## 说明/提示

In the first test sample the number of passengers is equal to the number of empty seats, so regardless of the way the planes are chosen, the administration will earn the same sum.

In the second sample the sum is maximized if the 1-st person in the queue buys a ticket to the 1-st plane, the 2-nd person — to the 2-nd plane, the 3-rd person — to the 3-rd plane, the 4-th person — to the 1-st plane. The sum is minimized if the 1-st person in the queue buys a ticket to the 1-st plane, the 2-nd person — to the 1-st plane, the 3-rd person — to the 2-nd plane, the 4-th person — to the 2-nd plane.

## 样例 #1

### 输入

```
4 3
2 1 1
```

### 输出

```
5 5
```

## 样例 #2

### 输入

```
4 3
2 2 2
```

### 输出

```
7 6
```

# AI分析结果


### 💡 Kay的C++算法解析：Airport 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`贪心算法与优先队列应用`

🗣️ **初步分析**：
> 解决"Airport"这道题的核心在于运用**贪心策略**。想象你经营一个游乐园，游客（乘客）依次选择最刺激（空位最多）或最平缓（空位最少）的游乐设施（飞机），票价等于设施的当前热度（空位数）。贪心算法就像让每个游客都做出**当下最优选择**，从而获得整体最优解。
> - **核心思路**：最大值策略每次选当前空位最多的飞机；最小值策略每次选当前空位最少的非零飞机
> - **算法流程**：  
>   **最大值**：大根堆维护飞机→取堆顶→收入+=堆顶值→堆顶值-1→若>0重新入堆  
>   **最小值**：小根堆维护飞机→取堆顶→收入+=堆顶值→堆顶值-1→若>0重新入堆
> - **可视化设计**：用8位像素风格展示乘客队列和飞机（方块+数字）。乘客移动时：  
>   - 最大值模式：乘客走向**红色高亮**（当前最大）飞机，伴随"叮！"音效  
>   - 最小值模式：乘客走向**绿色高亮**（当前最小）飞机，伴随"滴！"音效  
>   - 收入数值实时跳动，飞机方块高度随座位数减少

---

#### 2. 精选优质题解参考
**题解一：_byta（优先队列）**
* **点评**：思路清晰直白，用大根堆求最大值和小根堆求最小值，代码简洁规范（变量名`q`/`q2`直观）。亮点在于**完美应用STL容器特性**——优先队列的O(log n)操作使算法高效（O(n log m)），优于暴力排序法。实践价值极高，可直接用于竞赛。

**题解二：xiaomuyun（优先队列）**
* **点评**：代码结构严谨，详细注释帮助理解。亮点在于**边界处理严谨性**——通过`if(val>0)`确保不压入0值飞机。虽与题解一思路相同，但对优先队列的定义和使用讲解更细致，适合初学者学习STL容器。

**题解三：LeiZeProMax（优先队列）**
* **点评**：最小堆处理时额外判断`if(b.top()==0)b.pop()`，体现**防御性编程思维**。虽然实际不会出现0值（因初始>0且只压入>0值），但这种严谨性值得学习。代码中`register`关键字尝试优化性能，展现进阶技巧。

---

#### 3. 核心难点辨析与解题策略
1.  **难点1：如何动态维护最值？**  
    * **分析**：飞机座位实时变化，需快速获取当前最大/最小值。优质题解用优先队列（堆）实现O(log m)的插入删除，远优于暴力排序O(m log m)
    * 💡 **学习笔记**：优先队列是动态最值问题的黄金搭档

2.  **难点2：为何最小值策略要避免选0？**  
    * **分析**：空位为0的飞机不可售票。贪心时需确保每次选择合法（非零）。小根堆虽天然排除0值，但代码中显式判断`if(top-1>0)`更鲁棒
    * 💡 **学习笔记**：贪心选择必须满足问题约束条件

3.  **难点3：贪心策略的正确性证明**  
    * **分析**：最大值策略的全局最优性：每次选最大使后续可选值尽量大；最小值策略：每次选最小避免浪费大座位飞机
    * 💡 **学习笔记**：贪心算法的正确性依赖"当前最优导致全局最优"的性质

### ✨ 解题技巧总结
- **技巧1：STL容器巧用** → 优先队列(`priority_queue`)处理动态最值
- **技巧2：问题分解** → 最大/最小策略独立求解，逻辑更清晰
- **技巧3：边界防御** → 显式检查空位>0，避免无效操作

---

#### 4. C++核心代码实现赏析
**通用核心实现（综合优质题解）**
```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n, m, x;
    cin >> n >> m;
    
    // 大根堆求最大值 | 小根堆求最小值
    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    
    for (int i = 0; i < m; ++i) {
        cin >> x;
        max_heap.push(x);
        min_heap.push(x);
    }

    int max_ans = 0, min_ans = 0;
    
    // 最大值策略
    for (int i = 0; i < n; ++i) {
        int top = max_heap.top(); max_heap.pop();
        max_ans += top;
        if (top - 1 > 0) max_heap.push(top - 1);
    }
    
    // 最小值策略
    for (int i = 0; i < n; ++i) {
        int top = min_heap.top(); min_heap.pop();
        min_ans += top;
        if (top - 1 > 0) min_heap.push(top - 1);
    }
    
    cout << max_ans << " " << min_ans;
    return 0;
}
```
**代码解读概要**：  
> 1. 用两个优先队列分别维护当前飞机状态  
> 2. **最大值循环**：反复取大根堆顶累加收入，座位-1后若仍有余位则放回堆中  
> 3. **最小值循环**：取小根堆顶累加，同样处理余位  
> 4. 两策略独立计算，避免状态干扰  

**题解一（_byta）片段赏析**
```cpp
priority_queue<int> q; // 大根堆
priority_queue<int, vector<int>, greater<int>> q2; // 小根堆

for(int i=1;i<=n;i++) {
    int maxn = q.top(); q.pop();
    ans += maxn;
    if(maxn-1 != 0) q.push(maxn-1); // 余位处理
    
    int minn = q2.top(); q2.pop();
    sum += minn;
    if(minn-1 != 0) q2.push(minn-1); // 同理
}
```
💡 **学习笔记**：同步计算最大/最小值时需保持堆状态独立  

**题解二（xiaomuyun）片段赏析**
```cpp
// 最大值计算专用循环
for(int i=1;i<=n;++i){
    int val = q1.top(); q1.pop();
    res1 += val--;
    if(val > 0) q1.push(val); // 显式>0判断
}
```
💡 **学习笔记**：分离循环使逻辑更清晰，>0判断增强健壮性  

**题解三（LeiZeProMax）片段赏析**
```cpp
ans2 += b.top();
c = b.top()-1; b.pop();
b.push(c);
if(b.top()==0) b.pop(); // 防御性弹出0值
```
💡 **学习笔记**：冗余检查在复杂问题中可能避免隐蔽错误

---

#### 5. 算法可视化：像素动画演示  
**主题**：机场售票大冒险（8-bit像素风）  
**核心演示**：乘客队列移动 → 飞机选择 → 收入实时更新  

**动画流程**：  
1. **初始化**：  
   - 左侧：像素小人排成竖列（n个）  
   - 右侧：颜色各异的飞机方块（高度=座位数），顶部显示数字  
   - 控制面板：▶️开始｜⏸️暂停｜🔄重置｜🐢/🐇速度滑块  

2. **最大值模式（红框高亮）**：  
   - **Step1**：队首小人移动到最高飞机（红色闪烁+"叮！"音效）  
   - **Step2**：飞机高度-1，顶部数字减少，收入栏+当前票价  
   - **Step3**：飞机重组（大根堆调整动画：飞机重新排序）  

3. **最小值模式（绿框高亮）**：  
   - 小人移动到最矮非零飞机（绿色闪烁+"滴！"音效）  
   - 收入栏显示累加过程（数字滚动动画）  

4. **完成效果**：  
   - 所有小人消失 → 飞机变灰色  
   - 播放胜利音效 + 收入数字烟花特效  

**交互设计**：  
- **AI演示模式**：自动播放（可调速），像"吃豆人"般自动导航  
- **音效体系**：  
  - 选择飞机：8-bit短音（不同音调区分最大/最小）  
  - 错误操作：低沉警告音  
  - 关卡完成：经典FC过关旋律  

---

#### 6. 拓展练习与相似问题
1. **P1090 [NOIP2004]合并果子**  
   → 同款优先队列贪心，巩固堆的应用  
2. **P1325 雷达安装**  
   → 区间贪心选择，强化最小覆盖策略  
3. **P1230 智力大冲浪**  
   → 带时限的贪心任务安排，需结合时间排序  

---

#### 7. 学习心得与经验分享
> 本次题解未包含作者个人心得，但Kay强调：  
> **调试技巧**：在贪心算法中，用`cout`打印每次选择的飞机座位号，可快速定位逻辑错误！

---

### 结语  
通过贪心策略和优先队列的完美配合，我们高效解决了Airport问题。记住：**合适的数据结构能让算法事半功倍**！下次遇到动态最值问题时，不妨优先考虑堆结构。继续加油，少年！🚀

---
处理用时：153.51秒