# 题目信息

# Points

## 题目描述

Pete and Bob invented a new interesting game. Bob takes a sheet of paper and locates a Cartesian coordinate system on it as follows: point $ (0,0) $ is located in the bottom-left corner, $ Ox $ axis is directed right, $ Oy $ axis is directed up. Pete gives Bob requests of three types:

- add x y — on the sheet of paper Bob marks a point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is not yet marked on Bob's sheet at the time of the request.
- remove x y — on the sheet of paper Bob erases the previously marked point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is already marked on Bob's sheet at the time of the request.
- find x y — on the sheet of paper Bob finds all the marked points, lying strictly above and strictly to the right of point $ (x,y) $ . Among these points Bob chooses the leftmost one, if it is not unique, he chooses the bottommost one, and gives its coordinates to Pete.

Bob managed to answer the requests, when they were 10, 100 or 1000, but when their amount grew up to $ 2·10^{5} $ , Bob failed to cope. Now he needs a program that will answer all Pete's requests. Help Bob, please!

## 样例 #1

### 输入

```
7
add 1 1
add 3 4
find 0 0
remove 1 1
find 0 0
add 1 1
find 0 0
```

### 输出

```
1 1
3 4
1 1
```

## 样例 #2

### 输入

```
13
add 5 5
add 5 6
add 5 7
add 6 5
add 6 6
add 6 7
add 7 5
add 7 6
add 7 7
find 6 6
remove 7 7
find 6 6
find 4 4
```

### 输出

```
7 7
-1
5 5
```

# AI分析结果



### 算法分类  
线段树 + 有序集合（Set）

---

### 题解思路与核心难点  
#### 核心逻辑  
1. **离散化**：将大范围的坐标离散化为连续整数，便于数据结构处理  
2. **线段树**：维护每个 x 坐标对应的最大 y 值，用于快速筛选可能满足条件的 x  
3. **有序集合**：每个 x 坐标维护一个有序的 y 集合，支持快速插入、删除和二分查找  

#### 解决难点  
1. **高效查询**：在线段树上二分查找满足 x>X 的最小 x，且该 x 对应存在 y>Y 的点  
2. **动态维护**：插入/删除时需同步更新线段树的最大值，并维护有序集合  
3. **严格右上条件**：通过离散化后查询 x+1 到最大值范围，并在集合中找第一个 y>Y 的值  

---

### 最优思路提炼  
1. **离散化 x 和 y**，压缩坐标范围  
2. **线段树维护 x 轴的最大 y 值**，支持区间查询与单点更新  
3. **每个 x 对应一个有序集合**存储所有 y 值  
4. **线段树上二分**：递归优先检查左子树，找到满足条件的最小 x  
5. **集合内二分**：找到对应 x 后，用 upper_bound 快速定位最小 y  

---

### 题解评分（≥4星）  
1. **作者：_Anchor（⭐⭐⭐⭐⭐）**  
   - 思路清晰，代码结构合理  
   - 关键优化：线段树内部递归二分，时间复杂度 O(logn)  
   - 代码可读性强，注释详细  

2. **作者：mrsrz（⭐⭐⭐⭐）**  
   - 实现简洁，使用 STL 特性高效  
   - 采用线段树上二分，但代码可读性稍弱  

3. **作者：一扶苏一（⭐⭐⭐⭐）**  
   - 详细解释线段树维护逻辑  
   - 包含调试心得："注意离散化后的最大值需特殊处理"  

---

### 核心代码实现（作者：_Anchor）  
```cpp
// 线段树查询最小 x
int QueryPos(int x, int l, int r, int X, int Y) {
    if (l == r) return (Max[x] > Y) ? l : -1;
    int mid = (l + r) >> 1, res = -1;
    if (X <= mid && Max[x<<1] > Y) 
        res = QueryPos(x<<1, l, mid, X, Y);
    if (res != -1) return res;
    return (Max[x<<1|1] > Y) ? QueryPos(x<<1|1, mid+1, r, X, Y) : -1;
}

// 处理查询操作
int x = QueryPos(1, 1, idx, X+1, Y);
if (x == -1) cout << "-1\n";
else {
    auto it = ST[x].upper_bound(Y);
    cout << b[x] << " " << b[*it] << "\n";
}
```

---

### 相似题目推荐  
1. **P1972 [SDOI2009]HH的项链**（区间唯一性查询）  
2. **CF1093E Intersection of Permutations**（二维范围查询）  
3. **LOJ 6039 珠宝商**（动态维护有序数据与范围查询）

---

### 可视化设计  
#### 动画方案  
1. **线段树结构**：  
   - 每个节点显示区间 [l, r] 和当前最大值  
   - 查询时高亮路径（橙色），命中节点闪烁（红色）  
2. **有序集合**：  
   - 用垂直柱状图表示每个 x 的 y 集合，插入/删除时动态调整高度  
3. **复古像素风格**：  
   - 线段树节点用 8x8 像素块表示，集合用垂直排列的像素条  
   - 音效：插入（短促“滴”声），删除（低沉“咚”声），查询成功（上扬音阶）  

#### 交互功能  
- **步进控制**：支持暂停/继续/单步执行  
- **参数调节**：动画速度（1x, 2x, 5x）  
- **AI 演示**：自动播放典型测试案例（如样例1和样例2）  

---

### 个人心得摘录  
> "线段树二分必须优先递归左子树，否则无法保证找到最小 x。我在调试时发现若先查右子树，会漏掉更小的可行解。" —— 作者：resftlmuttmotw  

---

### 结论  
通过离散化 + 线段树维护区间最大值的框架，结合每个 x 对应有序集合的精细操作，能在 O(n logn) 时间内高效处理动态二维点集的查询问题。该方案在代码实现和理论复杂度上均达到最优，适合作为此类问题的标准解法。

---
处理用时：68.95秒