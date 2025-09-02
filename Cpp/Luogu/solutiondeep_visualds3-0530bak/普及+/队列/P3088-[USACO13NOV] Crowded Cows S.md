# 题目信息

# [USACO13NOV] Crowded Cows S

## 题目描述

Farmer John's N cows (1 <= N <= 50,000) are grazing along a one-dimensional fence.  Cow i is standing at location x(i) and has height h(i) (1 <= x(i),h(i) <= 1,000,000,000).

A cow feels "crowded" if there is another cow at least twice her height within distance D on her left, and also another cow at least twice her height within distance D on her right (1 <= D <= 1,000,000,000).  Since crowded cows produce less milk, Farmer John would like to count the number of such cows.  Please help him.

FJ有 $N(1\le N\le50000)$ 头奶牛沿着一维的栅栏吃草，第 $i$ 头奶牛在目标点 $x_i$ ，它的身高是 $h_i (1 \le x_i,h_i\le10^9)$。

当一头奶牛左边 $D(1\le D\le10^9)$ 距离内且右边 $D$ 距离内有身高至少是它的两倍的奶牛，它就会觉得拥挤。

请计算觉得拥挤的奶牛的数量。


## 说明/提示

There are 6 cows, with a distance threshold of 4 for feeling crowded.  Cow #1 lives at position x=10 and has height h=3, and so on.


The cows at positions x=5 and x=6 are both crowded. 



## 样例 #1

### 输入

```
6 4 
10 3 
6 2 
5 3 
9 7 
3 6 
11 2 
```

### 输出

```
2 
```

# AI分析结果



# 算法分类：单调队列

## 综合分析与结论
题目核心是判断每个奶牛左右D距离内是否存在两倍身高的奶牛。主要解法为**两次单调队列扫描**，正序处理左侧区间，逆序处理右侧区间，维护单调递减队列以保证队首为区间最大高度。时间复杂度 O(n)，空间复杂度 O(n)，是本题最优解法。

### 核心算法流程与可视化设计
**关键步骤动画演示方案：**
1. **初始化排序**：将奶牛按坐标排序，显示排序后的位置与高度。
2. **正序扫描左侧区间**：
   - 新奶牛入队时，用**红色高亮**显示当前处理的奶牛。
   - **弹出队尾较小元素**（黄色闪烁），保持队列递减。
   - 队首超出距离时弹出（灰色淡化），更新有效区间。
   - 若队首高度≥2倍当前高度，标记左侧满足条件（绿色边框）。
3. **逆序扫描右侧区间**：流程同上，标记右侧满足条件（蓝色边框）。
4. **最终统计**：同时有绿蓝边框的奶牛计数+1（金色高亮）。

**复古像素风格设计：**
- 奶牛显示为 16x16 像素方块，颜色按高度梯度变化。
- 队列用横向滑动条表示，元素高度映射实际数值。
- 音效：入队“滴”声，弹出“咔嚓”声，标记成功时 8-bit 胜利音效。

---

## 题解评分（≥4星）
1. **jzqjzq（★★★★★）**  
   使用两次单调队列，代码简洁高效，O(n) 复杂度，队列维护逻辑清晰，边界处理准确。

2. **一只书虫仔（★★★★☆）**  
   结构体排序+双端队列实现，注释详细，包含调试心得（教练调试过程），可读性强。

3. **EarthGiao（★★★★☆）**  
   独立封装单调队列处理逻辑，结构清晰，变量命名规范，适合学习队列维护的细节。

---

## 最优思路与技巧提炼
**核心技巧：**
1. **坐标排序预处理**：确保后续处理按空间顺序扫描。
2. **单调队列维护最大值**：
   ```cpp
   while (队尾元素 <= 新元素) 弹出队尾; // 保持递减
   while (队首超出距离范围) 弹出队首;    // 维护有效窗口
   ```
3. **正逆序两次独立处理**：分别统计左右条件，最后合并结果。

---

## 相似题目推荐
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)  
   单调队列求区间最值模板题。
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)  
   单调队列维护滑动窗口最小值。
3. [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)  
   前缀和+单调队列求最大区间和。

---

## 关键代码实现
**jzqjzq 的单调队列核心代码：**
```cpp
int l=1, r=0;
for(int i=1; i<=n; i++){ // 正序处理左侧
    while(l<=r && qq[r].y < a[i].y) r--; // 弹出较小队尾
    qq[++r] = a[i];
    while(q[i].x - qq[l].x > d) l++;     // 维护窗口左边界
    if(qq[l].y >= 2*a[i].y) left[i] = 1;
}

memset(qq,0,sizeof qq); l=1; r=0;
for(int i=n; i>=1; i--){ // 逆序处理右侧
    while(l<=r && qq[r].y < a[i].y) r--;
    qq[++r] = a[i];
    while(qq[l].x - a[i].x > d) l++;     // 维护窗口右边界
    if(qq[l].y >= 2*a[i].y) right[i] = 1;
}
```

---

## 可视化演示代码片段（JS Canvas）
```javascript
// 绘制奶牛队列（像素风格）
function drawCow(x, y, height, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x, 300 - height*2, 16, 16); // 高度映射
    ctx.strokeStyle = '#000';
    ctx.strokeRect(x, 300 - height*2, 16, 16);
}

// 单调队列动画更新
function animateQueueStep(cows, currentIndex) {
    let current = cows[currentIndex];
    // 高亮当前牛
    drawCow(current.x, 0, current.h, '#FF0000'); 
    playSound('beep'); 
    
    // 弹出队尾较小元素
    while (queue.length > 0 && queue[queue.length-1].h < current.h) {
        let removed = queue.pop();
        drawCow(removed.x, 0, removed.h, '#FFFF00');
        playSound('pop');
    }
    
    queue.push(current);
    // 更新队列位置显示...
}
```

---

## 个人心得摘录
> "WA 了 3 次才发现是逆序处理时边界判断写反了符号，一定要仔细检查队列弹出条件！" —— yangzechenc  
> "用双端队列比数组模拟更直观，但要注意清空操作避免残留数据。" —— 一只书虫仔

---

**总结**：单调队列是本题最优解，通过两次扫描高效维护区间最大值，结合像素动画和音效能直观展示算法核心流程。

---
处理用时：79.08秒