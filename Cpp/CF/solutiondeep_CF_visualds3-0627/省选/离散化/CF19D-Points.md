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



# 算法分类
**线段树 + 集合（Set）**

---

## 综合分析与结论

### 核心思路
1. **离散化**：将大范围的坐标映射到紧凑的整数区间，便于数据结构处理。
2. **线段树维护最大值**：每个线段树节点存储对应横坐标区间的最大纵坐标值，便于快速判断是否存在满足条件的点。
3. **集合存储纵坐标**：每个横坐标对应的所有纵坐标存入有序集合（如 `set`），支持快速插入、删除和二分查找。
4. **线段树二分查询**：查询时在线段树上二分找到最小的满足条件的横坐标，再在集合中找到对应的最小纵坐标。

### 解决难点
- **高效查询**：通过线段树二分快速定位可能的横坐标，避免暴力遍历。
- **动态维护**：插入和删除操作需同步更新线段树的最大值，确保查询准确性。

---

## 题解评分（≥4星）

1. **作者：_Anchor（★★★★☆）**  
   - **亮点**：代码结构清晰，线段树与集合结合紧密，离散化处理得当。
   - **核心代码**：  
     ```cpp
     int QueryPos(int x, int l, int r, int X, int Y) {
         if (l == r) return (Max[x] > Y) ? l : -1;
         int mid = (l + r) >> 1, res = -1;
         if (X <= mid && Max[x<<1] > Y) res = QueryPos(x<<1, l, mid, X, Y);
         if (res != -1) return res;
         return (Max[x<<1|1] > Y) ? QueryPos(x<<1|1, mid+1, r, X, Y) : -1;
     }
     ```

2. **作者：mrsrz（★★★★☆）**  
   - **亮点**：简洁的线段树二分实现，`set` 操作与线段树更新高效结合。
   - **核心代码**：  
     ```cpp
     void modify(int l, int r, int o, int pos, int v) {
         if (l == r) d[o] = v;
         else {
             int mid = (l + r) >> 1;
             (pos <= mid) ? modify(l, mid, o<<1, pos, v) : modify(mid+1, r, o<<1|1, pos, v);
             d[o] = max(d[o<<1], d[o<<1|1]);
         }
     }
     ```

3. **作者：一扶苏一（★★★★☆）**  
   - **亮点**：详细的线段树二分逻辑，`set` 维护最大值并处理边界情况。
   - **核心代码**：  
     ```cpp
     int ask(int l, int r, int o, int X, int Y, int& x) {
         if (l == r) { if (d[o] >= Y) x = l; return; }
         int mid = (l + r) >> 1;
         if (X <= mid && d[o<<1] >= Y) ask(l, mid, o<<1, X, Y, x);
         if (~x) return;
         if (d[o<<1|1] >= Y) ask(mid+1, r, o<<1|1, X, Y, x);
     }
     ```

---

## 最优思路提炼
1. **离散化处理**：将大范围坐标映射到连续整数，缩小数据范围。
2. **线段树维护区间最大值**：快速判断某个横坐标区间是否存在满足条件的点。
3. **集合存储纵坐标**：利用有序集合的自动排序特性，支持快速插入、删除和二分查找。
4. **线段树二分查询**：在线段树上递归查找最小的满足条件的横坐标，避免暴力遍历。

---

## 类似题目推荐
1. **洛谷 P1908 逆序对**（线段树/分治）  
2. **洛谷 P3369 普通平衡树**（集合/平衡树操作）  
3. **洛谷 P5490 矩形面积并**（线段树扫描线）

---

## 可视化设计
### 动画方案
- **像素风格**：用 8-bit 网格展示坐标系，每个点以像素块表示。
- **颜色标记**：  
  - **红色**：当前操作的坐标点（如查询点）。  
  - **绿色**：候选点（线段树二分过程中检查的区间）。  
  - **黄色**：最终找到的答案点。
- **步进控制**：支持暂停/继续，单步执行观察线段树二分过程。
- **音效触发**：  
  - **插入/删除**：短促“滴”声。  
  - **查询成功**：上扬音效；**失败**：低沉音效。

### 复古游戏化实现
```javascript
// 示例：Canvas 绘制像素点
const canvas = document.getElementById('grid');
const ctx = canvas.getContext('2d');
function drawPoint(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x * 10, canvas.height - y * 10, 8, 8); // 像素块大小为 8x8
}
```

---

## 核心代码实现
```cpp
// 离散化坐标并处理查询
void solve() {
    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    for (int i = 1; i <= n; ++i) {
        auto& q = queries[i];
        q.x = lower_bound(X.begin(), X.end(), q.x) - X.begin();
        if (q.op == 'add' || q.op == 'remove') {
            q.y = lower_bound(Y.begin(), Y.end(), q.y) - Y.begin();
            st[q.x].insert(q.y);
            update_max(q.x); // 更新线段树中的最大值
        } else {
            int pos = query_segment_tree(q.x + 1, q.y);
            if (pos == -1) cout << "-1\n";
            else {
                auto it = st[pos].upper_bound(q.y);
                cout << X[pos] << ' ' << Y[*it] << '\n';
            }
        }
    }
}
```

---

**总结**：通过离散化、线段树和集合的高效结合，解决了动态点集的查询问题，核心在于线段树二分与有序集合的协同操作。

---
处理用时：61.89秒