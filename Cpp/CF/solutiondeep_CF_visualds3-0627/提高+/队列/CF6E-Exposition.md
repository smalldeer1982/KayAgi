# 题目信息

# Exposition

## 题目描述

There are several days left before the fiftieth birthday of a famous Berland's writer Berlbury. In this connection the local library decided to make an exposition of the works of this famous science-fiction writer. It was decided as well that it is necessary to include into the exposition only those books that were published during a particular time period. It is obvious that if the books differ much in size, the visitors will not like it. That was why the organizers came to the opinion, that the difference between the highest and the lowest books in the exposition should be not more than $ k $ millimeters.

The library has $ n $ volumes of books by Berlbury, arranged in chronological order of their appearance. The height of each book in millimeters is know, it is $ h_{i} $ . As Berlbury is highly respected in the city, the organizers want to include into the exposition as many books as possible, and to find out what periods of his creative work they will manage to cover. You are asked to help the organizers cope with this hard task.

## 样例 #1

### 输入

```
3 3
14 12 10
```

### 输出

```
2 2
1 2
2 3
```

## 样例 #2

### 输入

```
2 0
10 10
```

### 输出

```
2 1
1 2
```

## 样例 #3

### 输入

```
4 5
8 19 10 13
```

### 输出

```
2 1
3 4
```

# AI分析结果



---

## 唯一算法分类  
**滑动窗口（双指针）**

---

## 综合分析与结论  
### 核心算法流程  
所有题解的核心目标是寻找满足极差约束的最长连续子数组。关键差异在于维护极差的方式：  
1. **ST表+二分**：预处理区间极差查询结构，对每个左端点二分右端点  
2. **双指针+multiset**：动态维护窗口内的元素集合，通过红黑树特性获取极差  
3. **双指针+单调队列**：使用两个队列分别维护窗口内的单调极值  

### 核心难点与解决方案  
| 难点 | 解决方案 |
|------|----------|
| 快速获取窗口极差 | ST表预处理 / multiset自动排序 / 单调队列维护极值序列 | 
| 窗口扩展收缩策略 | 右指针贪心扩展，左指针被动收缩（满足单调性） |  

### 可视化设计要点  
**动画方案**：  
1. 用蓝色高亮当前窗口区间，红色标记左右指针  
2. 每次右指针移动时，在右侧显示插入元素到单调队列的过程（如绿色方块入队，淘汰灰色方块）  
3. 窗口收缩时，用闪烁效果强调被移除元素，并更新队列状态  

**复古像素风格**：  
- 使用 16 色调色板（NES 风格）  
- 窗口区间用砖块网格表示，极差数值用 8-bit 字体显示  
- 音效设计：移动指针时播放短促的电子音，找到最长窗口时播放经典 FC 过关音效  

---

## 题解清单 (≥4星)  
### 1. 小闸蟹（5★）  
- **亮点**：双指针+multiset实现简洁，时间复杂度 O(n log n)  
- **核心代码**：  
```cpp
s.insert(Book[r]);
while(*s.rbegin() - *s.begin() > k) 
    s.erase(s.find(Book[l++]));
```

### 2. zrzring（4.5★）  
- **亮点**：单调队列维护极值，O(n) 时间复杂度  
- **关键实现**：  
```cpp
while(h1 <= t1 && a[x] >= a[q1[t1]]) t1--; // 维护最大值队列
while(h2 <= t2 && a[x] <= a[q2[t2]]) t2--; // 维护最小值队列
```

### 3. kczno1（4★）  
- **亮点**：独立发现题目翻译问题，提出子序列与子串的两种解法  
- **调试心得**："样例3过不了才发现是子串问题" 体现实际调试经验  

---

## 最优思路提炼  
### 关键技巧  
1. **极值维护三件套**：  
   - ST表：适合静态区间查询  
   - multiset：动态维护简洁但带 log 因子  
   - 单调队列：最优线性复杂度，需维护两个方向  

2. **窗口滑动策略**：  
   ```python
   while 右指针可扩展：
       右移右指针
       while 当前窗口不满足条件：
           右移左指针
       更新最优解
   ```

---

## 同类题目推荐  
1. P1886 滑动窗口（单调队列模板）  
2. P1440 求区间最小值（ST表应用）  
3. P1714 切蛋糕（前缀和+单调队列）  

---

## 个人心得摘录  
> "样例3过不了才发现是子串问题" —— kczno1  
> "multiset.erase要注意删除迭代器而非值" —— 小闸蟹  
> "二分答案时注意右端点初始值要+1避免死循环" —— 伊凡  

---

## 核心代码实现（zrzring 题解）  
```cpp
int h1=1, t1=0, h2=1, t2=0; // 单调队列头尾指针
int q1[N], q2[N]; // 最大值队列、最小值队列

void ins(int x) {
    // 维护最大值队列（单调递减）
    while(h1<=t1 && a[x]>=a[q1[t1]]) t1--;
    q1[++t1] = x;
    // 维护最小值队列（单调递增）
    while(h2<=t2 && a[x]<=a[q2[t2]]) t2--;
    q2[++t2] = x;
}

// 在滑动窗口循环中调用
ins(++r);
while(a[q1[h1]] - a[q2[h2]] > k) {
    if(q1[h1] == l) h1++;
    if(q2[h2] == l) h2++;
    l++;
}
```

---

## 可视化演示设计  
### 动画逻辑  
1. **初始化阶段**：  
   - 绘制书本高度的像素柱状图（高度用不同颜色表示）  
   - 初始化左右指针为最左侧，显示空队列  

2. **滑动过程**：  
   ```javascript
   function animateStep() {
       moveRightPointer(); 
       drawCurrentWindow('blue');
       updateMaxMinQueues(); // 高亮队列变化
       if (overLimit()) {
           flashRed();
           moveLeftPointer();
       }
   }
   ```

3. **复古特效**：  
   - 使用 32x32 像素的 FC 风格精灵图表示指针  
   - 极差超标时屏幕抖动+红色闪烁滤镜  
   - 8-bit 音效使用 Web Audio API 的方波振荡器实现  

### 交互控制  
```html
<div class="control-panel">
    <button onclick="togglePlay()">▶/⏸</button>
    <input type="range" id="speed" min="1" max="10">
    <button onclick="step()">⏩单步</button>
</div>
```

---
处理用时：77.52秒