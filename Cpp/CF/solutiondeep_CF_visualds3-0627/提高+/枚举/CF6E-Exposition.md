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



# 算法分类与题解分析

## 唯一算法分类
**滑动窗口/双指针**

---

## 题解思路、算法要点与解决难点

### 核心逻辑对比
所有题解围绕**如何高效维护连续子串的最大最小值差**展开，主要分为以下三类思路：

| 方法               | 数据结构/算法       | 时间复杂度   | 核心难点解决思路                     |
|--------------------|--------------------|-------------|------------------------------------|
| 滑动窗口+单调队列   | 双单调队列（最大/最小） | O(n)        | 队列头部始终维护当前窗口极值         |
| 滑动窗口+multiset   | 红黑树（有序集合）    | O(n log n)  | 利用自动排序特性快速获取极值         |
| ST表预处理+二分枚举 | RMQ+二分查找        | O(n log n)  | 预处理极值后快速判断任意区间是否合法 |

---

## 题解评分（≥4星）

### 五星题解
1. **zrzring（单调队列双指针）**  
   - 亮点：最优时间复杂度，清晰的单调队列维护逻辑  
   - 核心代码：
     ```cpp
     while (h1 <= t1 && a[x] >= a[q1[t1]]) t1--; // 维护最大值队列
     while (h2 <= t2 && a[x] <= a[q2[t2]]) t2--; // 维护最小值队列
     ```

2. **kczno1（单调队列优化）**  
   - 亮点：独创性维护极差的方式，极简代码风格  
   - 心得：通过独立推导发现原题翻译错误，强调测试样例验证的重要性

### 四星题解
1. **小闸蟹（multiset双指针）**  
   - 亮点：代码简洁易理解，适合快速实现  
   - 核心逻辑：
     ```cpp
     s.insert(Book[r]); // 动态维护有序集合
     while (*s.rbegin() - *s.begin() > k) s.erase(...); // 滑动窗口收缩
     ```

---

## 最优思路提炼
**双单调队列维护极值的滑动窗口算法**  
关键实现步骤：
1. **维护两个单调队列**  
   - `q1` 递减队列维护当前窗口最大值（队头为最大）
   - `q2` 递增队列维护当前窗口最小值（队头为最小）
   
2. **滑动窗口扩展**  
   ```python
   for 右指针r in 0..n-1:
       while q1非空且a[r]≥q1队尾: 弹出队尾
       q1.append(r)
       while q2非空且a[r]≤q2队尾: 弹出队尾  
       q2.append(r)
   ```
   
3. **窗口收缩条件**  
   ```python
   while q1队头值 - q2队头值 > k:
       左指针l += 1
       if q1队头 < l: 弹出q1队头
       if q2队头 < l: 弹出q2队头
   ```

---

## 同类型题与算法套路
**滑动窗口极值问题通用解法**  
1. **维护极值的单调队列结构**  
   - 最大值队列：严格递减，队头为当前窗口最大
   - 最小值队列：严格递增，队头为当前窗口最小

2. **滑动窗口收缩条件**  
   - 极差超过阈值时收缩左边界
   - 队列中存储下标而非值，便于判断元素是否在窗口内

---

## 推荐相似题目
1. **洛谷 P1886** - 滑动窗口（模板题）  
2. **LeetCode 239** - 滑动窗口最大值  
3. **洛谷 P1714** - 限定长度区间和极值  

---

## 可视化与算法演示
### 动画设计要点
1. **像素风格可视化**  
   - **颜色编码**：  
     - 红色方块：当前右指针位置  
     - 蓝色方块：窗口左指针位置  
     - 绿色/黄色：单调队列中的元素  
   - **Canvas 渲染**：  
     ```javascript
     function drawQueue(ctx, queue, y, color) {
         queue.forEach((idx, i) => {
             ctx.fillStyle = color;
             ctx.fillRect(i*20, y, 15, 15); // 绘制队列元素
         });
     }
     ```

2. **音效设计**  
   - `insert_sound`：元素入队时播放高频"哔"声  
   - `pop_sound`：元素出队时播放低频"嘟"声  
   - `max_update`：更新最长窗口时播放胜利音效

3. **自动演示模式**  
   ```javascript
   function autoPlay() {
       if (r < n) {
           moveRight(); 
           setTimeout(autoPlay, 500);
       }
   }
   ```

---

## 关键代码片段
### 单调队列核心实现
```cpp
// 维护最大值队列（递减）
while (h1 <= t1 && a[x] >= a[q1[t1]]) t1--;
q1[++t1] = x;

// 维护最小值队列（递增） 
while (h2 <= t2 && a[x] <= a[q2[t2]]) t2--;
q2[++t2] = x;

// 窗口收缩
while (q1[h1] < l) h1++;
while (q2[h2] < l) h2++;
```

---

## 个人心得摘录
> **kczno1调试经验**：  
> "最初用单调队列实现时，遇到测试用例`[1,6,4,7]`无法正确处理。后发现队列更新逻辑未考虑中间元素的极值影响，改为存储下标后解决。验证算法时务必构造包含非单调数据的测试用例。"

> **小闸蟹实现心得**：  
> "虽然multiset的O(n log n)理论复杂度稍高，但在实际竞赛中其代码简洁性带来的时间优势往往超过理论复杂度差异。"

---

## 算法演示示例
**步骤说明**（以输入`3 3 14 12 10`为例）：
1. 初始窗口`[14]`，极差0 → 记录长度1  
2. 右扩至`[14,12]`，极差2 → 更新长度2  
3. 右扩至`[14,12,10]`，极差4 >3 → 左缩至`[12,10]`，极差2 → 最终最长长度2  

可视化中，队列元素随窗口移动动态变化，背景色高亮当前最长有效窗口。

---
处理用时：124.23秒