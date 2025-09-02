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


### 💡 Kay的C++算法解析：Exposition 深入学习指南 💡

#### **1. 题目解读与核心算法识别**  
✨ **本题主要考察**：滑动窗口（双指针技巧）  

🗣️ **初步分析**：  
> 解决书籍展览问题，关键在于维护一个动态窗口（子串），使其极差（最高-最低）≤k。这就像在书架上移动一个可伸缩的"阅读框"，框内书籍高度差不能超过k毫米，我们要找到最长的框。  
- **核心思路**：使用双指针（l左边界，r右边界）遍历序列。右指针r扩张窗口，若极差>k则左指针l收缩窗口，实时记录最长合法子串。  
- **算法选择**：最优解是**单调队列**（O(n)），可高效维护窗口内最大值/最小值；**平衡树(multiset)**（O(n log n)）更易实现，适合初学者。  
- **可视化设计**：像素动画中，用**绿色方块**表示当前窗口，**红色/蓝色**高亮最大值/最小值位置。窗口移动时触发像素位移动画，极差超标时播放警示音效，找到最长窗口时展示"胜利星闪"特效（复古8-bit风格）。

---

#### **2. 精选优质题解参考**  
**题解一（kczno1）**  
* **点评**：  
  手写单调队列实现极值维护（双队列分存最大值/最小值），O(n)时间复杂度极致优化。代码精炼，边界处理严谨（队列头过期检测），直接体现滑动窗口本质，竞赛实战首选。亮点：用负值技巧统一队列逻辑。

**题解二（zrzring）**  
* **点评**：  
  STL deque实现双单调队列（递增/递减），逻辑清晰注释详尽。严格保证队列单调性，实时比较新元素与队尾值，避免经典Hack案例。亮点：详细分析错误做法，强化理解。

**题解三（小闸蟹）**  
* **点评**：  
  multiset自动排序特性实现极差计算，代码简洁易懂。虽复杂度O(n log n)，但平衡树操作直观展现窗口维护过程，适合初学者理解核心思想。亮点：完整输入输出处理和边界记录。

---

#### **3. 核心难点辨析与解题策略**  
1. **实时维护窗口极值**  
   *分析*：暴力计算极差（O(n)）导致超时。  
   *解决*：单调队列（O(1)）或平衡树（O(log n)）动态追踪最值。  
   💡 **学习笔记**：单调队列是滑动窗口极值的标准解法。

2. **最长子串的完整记录**  
   *分析*：多个等长最优解需全部输出。  
   *解决*：当`r-l+1 > maxLen`时清空答案数组；等于时追加。  
   💡 **学习笔记**：窗口移动中同步更新答案集合。

3. **边界条件与下标过期**  
   *分析*：左指针移动需同步移除队列中过期下标。  
   *解决*：检查队头元素下标是否`<l`，若是则出队。  
   💡 **学习笔记**：双指针移动需与队列状态严格同步。

✨ **解题技巧总结**：  
- **滑动窗口三要素**：右扩左缩、极差检测、答案更新  
- **数据结构选择**：追求效率选单调队列，求简易用平衡树  
- **调试关键**：可视化模拟小规模数据（如[14,12,10]）

---

#### **4. C++核心代码实现赏析**  
**通用核心实现（单调队列版）**  
```cpp
#include <iostream>
#include <deque>
using namespace std;
const int N = 1e5+5;
int main() {
    int n, k, a[N], maxLen = 0; 
    deque<int> qmax, qmin; // 双单调队列
    vector<pair<int, int>> ans;
    for (int l=1, r=1; r<=n; r++) {
        while (!qmax.empty() && a[qmax.back()] <= a[r]) qmax.pop_back(); // 维护递减队列
        qmax.push_back(r);
        while (!qmin.empty() && a[qmin.back()] >= a[r]) qmin.pop_back(); // 维护递增队列
        qmin.push_back(r);
        while (a[qmax.front()] - a[qmin.front()] > k) { // 极差超标
            if (qmax.front() == l) qmax.pop_front();   // 移除过期下标
            if (qmin.front() == l) qmin.pop_front();
            l++;
        }
        if (r-l+1 > maxLen) { ... } // 更新答案
    }
}
```
* **代码解读概要**：  
  双队列分别维护窗口内最大值/最小值的**下标**。右移r时维护队列单调性；极差超标时左移l并检查队头过期；实时记录最长窗口。

**题解片段赏析**  
1. **kczno1手写队列**  
   ```cpp
   struct que { // 自定义队列结构
       pii q[N]; int h,t;
       void push(const pii &x) { // 维护单调性
           while(h<=t && x.second>q[t].second) t--;
           q[++t]=x;
       }
   } zheng, fu; // 正负双队列
   ```
   * **学习笔记**：避免STL开销，负值队列巧妙转化最小值维护。

2. **小闸蟹multiset应用**  
   ```cpp
   multiset<int> s;
   s.insert(a[r]);
   while (*s.rbegin() - *s.begin() > k) 
       s.erase(s.find(a[l++]));
   ```
   * **学习笔记**：crbegin()/cbegin()快速获取极值，注意删除时用find定位迭代器。

---

#### **5. 算法可视化：像素动画演示**  
* **主题**：8-bit风格《书架探险》  
* **核心演示**：  
  - **像素建模**：书籍化为彩色方块（高度=颜色饱和度），窗口框用闪烁绿边  
  - **动态过程**：  
    1. 右指针r右移：新书加入，播放"叮"声，队列动画更新（红/蓝光柱标识极值）  
    2. 极差>k：左指针l右移，灰色遮罩覆盖移出书籍，"哔"声警示  
    3. 发现最长窗口：金色星光特效 + 胜利音效，记录当前区间  
  - **控制面板**：速度滑块调速，单步/自动模式切换，极差实时显示  

* **技术细节**：  
  - **Canvas绘制**：网格布局，帧动画基于requestAnimationFrame  
  - **音效设计**：Web Audio API触发8-bit音效（加入/移除/胜利）  
  - **游戏化元素**：每找到最长窗口得1星，集星解锁"快速扫描"技能  

---

#### **6. 拓展练习与相似问题思考**  
* **技巧迁移**：滑动窗口用于解决：  
  1. 最长无重复字符子串（LeetCode 3）  
  2. 和≥target的最短子数组（LeetCode 209）  
  3. 区间覆盖问题（NOI2016 区间）  

* **洛谷推荐**：  
  1. **P1886 滑动窗口**：单调队列模板题  
  2. **P1712 [NOI2016]区间**：双指针+线段树进阶  
  3. **P1638 逛画展**：最短满足条件子串变形  

---

#### **7. 学习心得与经验分享**  
> **小闸蟹的调试经验**："我在处理[6,4,7]时发现错误，因未比较新元素与队尾值，导致漏解。"  
> **Kay点评**：经典案例揭示单调队列核心——**严格维护单调性**。建议：  
> - 测试边界数据：全相同值、递增/递减序列  
> - 单步调试打印队列状态  

---

本次解析深入探索了滑动窗口的两种实现范式，并融合游戏化视觉设计辅助理解。记住：**高效算法的核心在于选择合适的数据结构！** 动手实现单调队列与平衡树解法，感受时间效率差异吧！ 🚀

---
处理用时：215.08秒