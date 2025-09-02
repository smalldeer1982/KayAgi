# 题目信息

# Glass Carving

## 题目描述

Leonid wants to become a glass carver (the person who creates beautiful artworks by cutting the glass). He already has a rectangular $ w $ mm $ × $ $ h $ mm sheet of glass, a diamond glass cutter and lots of enthusiasm. What he lacks is understanding of what to carve and how.

In order not to waste time, he decided to practice the technique of carving. To do this, he makes vertical and horizontal cuts through the entire sheet. This process results in making smaller rectangular fragments of glass. Leonid does not move the newly made glass fragments. In particular, a cut divides each fragment of glass that it goes through into smaller fragments.

After each cut Leonid tries to determine what area the largest of the currently available glass fragments has. Since there appear more and more fragments, this question takes him more and more time and distracts him from the fascinating process.

Leonid offers to divide the labor — he will cut glass, and you will calculate the area of the maximum fragment after each cut. Do you agree?

## 说明/提示

Picture for the first sample test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/6468d2fd0321178fa316ccb774411f002769e9ee.png) Picture for the second sample test:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/40ba2772b27431a21bc874ab308dc348ec8365fd.png)

## 样例 #1

### 输入

```
4 3 4
H 2
V 2
V 3
V 1
```

### 输出

```
8
4
4
2
```

## 样例 #2

### 输入

```
7 6 5
H 4
V 3
V 5
H 2
V 1
```

### 输出

```
28
16
12
6
4
```

# AI分析结果



### 题目中文翻译
#### 玻璃雕刻

**题目描述**  
Leonid想成为一名玻璃雕刻家。他有一块 $w$ 毫米 × $h$ 毫米的矩形玻璃板，一个钻石玻璃切割器和满腔热情。他希望通过垂直和水平切割练习雕刻技术，每次切割会将玻璃分成更小的矩形碎片（碎片保持原位）。每次切割后需要计算当前最大玻璃碎片的面积。

**输入格式**  
输入包含若干次切割操作，每次操作指定切割方向（H为水平，V为垂直）和切割位置（距离边界的距离）。

**输出格式**  
每次切割后输出当前最大碎片面积。

**样例输入1**  
```
4 3 4
H 2
V 2
V 3
V 1
```

**样例输出1**  
```
8
4
4
2
```

---

### 题解对比分析与结论

#### 最优题解推荐
1. **KNO3（5星）**
   **关键亮点**：
   - 使用`set`维护切割点，`multiset`维护区间长度
   - 每次切割后通过`lower_bound`快速找到相邻切割点
   - 时间复杂度$O(n \log n)$，代码简洁高效
   **核心代码**：
   ```cpp
   multiset<int> sx, sy;  // 存储当前所有区间长度
   set<int> lx, ly;       // 存储所有切割点
   
   void process_cut(char type, int pos) {
       auto& points = (type == 'H') ? ly : lx;
       auto& intervals = (type == 'H') ? sy : sx;
       
       auto it = points.insert(pos).first;
       int l = *prev(it), r = *next(it);
       
       intervals.erase(intervals.find(r - l));
       intervals.insert(r - pos);
       intervals.insert(pos - l);
   }
   ```

2. **生而为人（4星）**
   **关键亮点**：
   - 线段树维护最长连续零的长度
   - 每个节点记录左/右连续长度和区间最大值
   - 通过区间合并处理跨节点的连续段
   **核心实现**：
   ```cpp
   struct Node { int lmax, rmax, max; };
   void pushup(Node& p, Node& lc, Node& rc) {
       p.lmax = (lc.lmax == lc.len) ? lc.lmax + rc.lmax : lc.lmax;
       p.rmax = (rc.rmax == rc.len) ? rc.rmax + lc.rmax : rc.rmax;
       p.max = max({lc.max, rc.max, lc.rmax + rc.lmax});
   }
   ```

3. **Liu_zj（4星）**
   **关键亮点**：
   - 双线段树分别维护横纵切割
   - 维护区间全零标记和边界连续性
   **调试心得**：
   - 注意输入切割位置需要-1处理（题目描述为距离，线段树存储间隙）
   - 输出时+1转换为实际长度

---

### 关键思路总结
1. **问题转化**：将二维面积问题拆解为两个一维的最长连续段问题
2. **数据结构选择**：
   - **有序集合**：利用`set`的自动排序特性快速找到相邻切割点
   - **线段树**：维护区间最大连续零长度，需处理区间合并逻辑
3. **实现技巧**：
   - 切割方向与维护轴的对应关系（H切割影响垂直轴）
   - 使用`multiset`自动维护区间长度的有序性
   - 线段树合并时处理跨节点连续段

---

### 类似题目推荐
1. [P2894 酒店](https://www.luogu.com.cn/problem/P2894) - 线段树维护最长连续空房
2. [P3870 开关](https://www.luogu.com.cn/problem/P3870) - 区间异或操作与区间求和
3. [P1198 最大数](https://www.luogu.com.cn/problem/P1198) - 动态维护区间最大值

---

### 调试经验摘录
1. **数据类型**："开longlong好习惯"（多个题解强调）
2. **边界处理**："输入的是距离，建树时要-1，输出时+1"
3. **方向对应**："横切影响纵轴，纵切影响横轴，容易搞反"
4. **STL使用**："multiset的erase需用find获取迭代器，直接erase值会删全部相同元素"

---
处理用时：51.19秒