# 题目信息

# [USACO06JAN] Corral the Cows G

## 题目描述

Farmer John wishes to build a corral for his cows. Being finicky beasts, they demand that the corral be square and that the corral contain at least C (1 <= C <= 500) clover fields for afternoon treats. The corral's edges must be parallel to the X,Y axes.


FJ's land contains a total of N (C <= N <= 500) clover fields, each a block of size 1 x 1 and located at with its lower left corner at integer X and Y coordinates each in the range 1..10,000. Sometimes more than one clover field grows at the same location; such a field would have its location appear twice (or more) in the input. A corral surrounds a clover field if the field is entirely located inside the corral's borders.


Help FJ by telling him the side length of the smallest square containing C clover fields.

Farmer John 希望为他的奶牛们建立一个畜栏。

这些挑剔的奶牛要求畜栏必须是正方形的，而且至少要包含 $C$ 片三叶草，来当做它们的下午茶。

约翰的土地里一共包含 $N$ 片三叶草，每单位三叶草位于一个 $1\times 1$ 的土地区域内。坐标都为整数，范围在 $1$ 到 $10000$ 以内。

**多片的三叶草可能会位于同一个 $1\times 1$ 的区域内，所以在输入内，同一个区域坐标可能出现多次。**

请你帮 Farmer John 计算一下，在能包含至少 $C$ 片三叶草的情况下，畜栏的最小边长是多少。

$1\le C\le N\le 500$。

## 说明/提示

Explanation of the sample:



```php
|*   *
| * *
+------
```

Below is one 4x4 solution (C's show most of the corral's area); many others exist.

```php
|CCCC
|CCCC
|*CCC*
|C*C*
+------
```

## 样例 #1

### 输入

```
3 4
1 2
2 1
4 1
5 2```

### 输出

```
4```

# AI分析结果

### 综合分析与结论
这些题解的核心思路大多围绕二分答案展开，通过判断不同边长的正方形是否能包含至少 $C$ 片三叶草来确定最小边长。为了优化复杂度，多数题解采用了离散化和二维前缀和的方法。离散化可以缩小数据规模，避免因坐标范围过大导致的空间和时间浪费；二维前缀和则能在 $O(1)$ 时间内查询正方形内的三叶草数量。部分题解还运用了双指针、扫描线、线段树等技巧进一步优化。

### 所选题解
- **作者：RyexAwl（4星）**
  - **关键亮点**：思路清晰，详细阐述了二分答案、离散化和二维前缀和的实现过程，代码注释丰富，易于理解。
  - **个人心得**：无
- **作者：zhzh2001（4星）**
  - **关键亮点**：提供了多种思路，包括将判定性问题转换为“USACO14MAR The Lazy Cow”问题，使用扫描线 + 线段树优化，复杂度较低。
  - **个人心得**：提到这题虽简单但易写错细节，还分享了出题经验，如 $N$ 增大时不同复杂度算法的表现。
- **作者：ysner（4星）**
  - **关键亮点**：采用二维双指针法结合二分答案，代码简洁，运行效率高，实现了 0ms 跑过。
  - **个人心得**：无

### 重点代码与核心实现思想
#### RyexAwl 的题解
```cpp
// 离散化
for (int i = 0; i < n; i++){
    int x,y;
    cin >> x >> y;
    numbers.push_back(x);
    numbers.push_back(y);
}
sort(numbers.begin(),numbers.end());
numbers.erase(unique(numbers.begin(),numbers.end()),numbers.end());

// 初始化二维前缀和数组
for (int i = 0; i < n; i++){
    int x = get(points[i].first),y = get(points[i].second);
    sum[x][y]++;
}
for (int i = 1; i < numbers.size(); i++){
    for (int j = 1; j < numbers.size(); j++){
        sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    }
}

// 二分答案
int l = 1,r = 10000;
while (l < r){
    int mid = (l + r) >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
}

// 检查函数
bool check(int len){
    for (int x1 = 0,x2 = 1; x2 < numbers.size(); x2++){
        while(numbers[x2] - numbers[x1 + 1] + 1 > len)x1++;
        for (int y1 = 0, y2 = 1; y2 < numbers.size(); y2++){
            while(numbers[y2] - numbers[y1 + 1] + 1 > len)y1++;
            if (sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1] >= c) return true;
        }
    }
    return false;
}
```
**核心实现思想**：先进行离散化缩小数据规模，再利用二维前缀和预处理每个区域的三叶草数量。二分答案，对于每个中间值，枚举所有可能的正方形，通过二维前缀和快速判断正方形内的三叶草数量是否满足条件。

#### zhzh2001 的题解
```cpp
// 扫描线 + 线段树部分
struct event
{
    int x, yl, yr, val;
    bool operator<(const event &rhs) const
    {
        return x < rhs.x;
    }
} e[N * 2];
struct node
{
    int max, lazy;
} tree[1 << 11];

// 线段树更新
void update(int id, int l, int r, int L, int R, int val)
{
    if (L <= l && R >= r)
    {
        tree[id].lazy += val;
        tree[id].max += val;
    }
    else
    {
        pushdown(id, l, r);
        int mid = (l + r) / 2;
        if (L <= mid)
            update(id * 2, l, mid, L, R, val);
        if (R > mid)
            update(id * 2 + 1, mid + 1, r, L, R, val);
        tree[id].max = max(tree[id * 2].max, tree[id * 2 + 1].max);
    }
}

// 二分答案
int l = 1, r = 1e4;
while (l < r)
{
    int mid = (l + r) / 2, en = 0, yn = 0;
    for (int i = 1; i <= n; i++)
    {
        e[++en].x = a[i].x - mid + 1;
        e[en].yl = a[i].y - mid + 1;
        e[en].yr = a[i].y;
        e[en].val = 1;
        e[++en].x = a[i].x + 1;
        e[en].yl = a[i].y - mid + 1;
        e[en].yr = a[i].y;
        e[en].val = -1;
    }
    sort(e + 1, e + en + 1);
    sort(y + 1, y + yn + 1);
    build(1, 1, yn);
    int now = 0;
    for (int i = 1; i <= en; i++)
    {
        if (e[i].x != e[i - 1].x)
            now = max(now, tree[1].max);
        update(1, 1, yn, lower_bound(y + 1, y + yn + 1, e[i].yl) - y, lower_bound(y + 1, y + yn + 1, e[i].yr) - y, e[i].val);
    }
    if (now < c)
        l = mid + 1;
    else
        r = mid;
}
```
**核心实现思想**：将每个草场看作两个事件，用扫描线处理。通过线段树维护区间最大值，在二分答案的过程中，判断是否存在一个点被覆盖的次数达到 $C$ 次。

#### ysner 的题解
```cpp
// 双指针 + 二分答案
bool solve(int ml)
{
    int i,a,b,c,d,sc,sd;
    a=b=0;
    memset(s,0,sizeof(s));
    while(b<n&&rx[p[b+1].x]-rx[1]+1<=ml)  s[p[++b].y]++;
    for(;b<=n;s[p[++b].y]++)
    {
        while(rx[p[b].x]-rx[p[a+1].x]+1>ml)  s[p[++a].y]--;
        c=d=sc=sd=0;
        while(d<ny&&ry[d+1]-ry[1]+1<=ml)  sd+=s[++d];
        for(;d<=ny;sd+=s[++d])
        {
            while(ry[d]-ry[c+1]+1>ml)    sc+=s[++c];
            if(sd-sc>=m) return true;
        }
    }
    return false;
}

// 二分答案
int l = 1,r = max(rx[nx],ry[ny]),mid;
while(l<r)
{
    mid=l+r>>1;
    if(solve(mid))  r=mid;
    else    l=mid+1;
}
```
**核心实现思想**：使用二维双指针法，分别维护横坐标和纵坐标。在二分答案的过程中，对于每个中间值，通过双指针快速找到满足条件的区域，判断该区域内的三叶草数量是否满足要求。

### 最优关键思路或技巧
- **二分答案**：利用问题的单调性，通过二分答案缩小查找范围，将时间复杂度从 $O(n)$ 优化到 $O(\log n)$。
- **离散化**：当数据范围较大但数据量较小时，离散化可以有效缩小数据规模，避免空间和时间的浪费。
- **二维前缀和**：可以在 $O(1)$ 时间内查询矩形区域内的元素和，提高查询效率。
- **双指针、扫描线、线段树等技巧**：根据具体问题选择合适的技巧，进一步优化算法复杂度。

### 可拓展之处
同类型题或类似算法套路：
- **二维区域查询问题**：如求二维矩阵中某个矩形区域的元素和、最大值等，可以使用二维前缀和或二维线段树解决。
- **区间覆盖问题**：如判断某个区间是否被多个线段覆盖，可使用扫描线和线段树结合的方法。
- **二分查找优化问题**：对于具有单调性的问题，可尝试使用二分查找优化时间复杂度。

### 推荐题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：求矩阵中最大的全 1 正方形，可使用动态规划或二分答案解决。
- [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)：在矩阵中选择一个固定大小的矩形，使其元素和最大，可使用二维前缀和解决。
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：线段树的基础模板题，可用于练习线段树的基本操作。

### 个人心得摘录与总结
- **zhzh2001**：提到这题虽简单但易写错细节，很适合用于出题。当 $N$ 增大时，$O(N^2\log N)$ 会被卡常，需要用官方的神奇优化或 $O(N\log^2N)$ 的方法。
- **LiRewriter**：分享了自己 WA 了八次的调试经历，提醒注意指针可能滚过头的细节。

总结：这些个人心得提醒我们在做题时要注意细节，不同复杂度的算法在数据规模变化时表现不同，需要根据实际情况选择合适的算法。同时，调试过程中要仔细检查边界条件和特殊情况。

---
处理用时：73.62秒