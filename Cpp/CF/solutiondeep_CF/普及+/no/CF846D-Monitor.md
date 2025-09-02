# 题目信息

# Monitor

## 题目描述

## [题目简述]

Luba最近买了个显示器，这个显示器是一个n×m的矩形。但是不久之后她发现这个显示器上有些像素不正常工作（可能会成为坏点）。如果屏幕上有一块k*k的区域都是坏点，那么Luba就觉得这个显示器坏了。她知道有q个像素不正常，而且知道它们彻底罢工变成坏点的时间。

请告诉Luba显示器会不会坏掉，如果会请告诉她具体时间。

## 样例 #1

### 输入

```
2 3 2 5
2 1 8
2 2 8
1 2 1
1 3 4
2 3 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 3 2 5
1 2 2
2 2 1
2 3 5
3 2 10
2 1 100
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# Monitor

## 题目描述

## [题目简述]

Luba最近买了个显示器，这个显示器是一个n×m的矩形。但是不久之后她发现这个显示器上有些像素不正常工作（可能会成为坏点）。如果屏幕上有一块k*k的区域都是坏点，那么Luba就觉得这个显示器坏了。她知道有q个像素不正常，而且知道它们彻底罢工变成坏点的时间。

请告诉Luba显示器会不会坏掉，如果会请告诉她具体时间。

## 样例 #1

### 输入
```
2 3 2 5
2 1 8
2 2 8
1 2 1
1 3 4
2 3 2
```

### 输出
```
8
```

## 样例 #2

### 输入
```
3 3 2 5
1 2 2
2 2 1
2 3 5
3 2 10
2 1 100
```

### 输出
```
-1
```

### 算法分类
二分

### 综合分析与结论
这些题解主要围绕如何高效判断显示器何时坏掉展开。思路可分为两类，一类是直接通过数据结构或算法优化来查找所有k×k区域中坏点时间的最大值的最小值；另一类是先二分时间，再判断在该时间下是否存在全为坏点的k×k区域。各题解在算法复杂度、实现难度和代码可读性上有所不同。

### 所选的题解
- **作者：泠小毒 (4星)**
    - **关键亮点**：思路清晰，先预处理每行中长度为k的子列的最大值，再遍历所有可能的k×k正方形区域，找出其中最大值的最小值。代码简洁明了，易于理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,k,q,x,y,t,s,ans=0x3f3f3f3f,a[510][510],maxx[510][510];
int main()
{
    memset(a,0x3f,sizeof(a)),memset(maxx,0,sizeof(maxx)),scanf("%d%d%d%d",&n,&m,&k,&q);
    for(int i=1;i<=q;i++)scanf("%d%d%d",&x,&y,&t),a[x][y]=t;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m-k+1;j++)
            for(int kk=0;kk<k;kk++)
                maxx[i][j]=max(maxx[i][j],a[i][j+kk]);
    for(int i=1;i<=n-k+1;i++)
        for(int j=1;j<=m-k+1;j++)
        {
            s=0;
            for(int kk=0;kk<k;kk++)
                s=max(s,maxx[i+kk][j]);
            ans=min(ans,s);
        }
    if(ans>1e9)puts("-1");
    else printf("%d\n",ans);
    return 0;
}
```
    - **核心思想**：首先初始化数组，读入数据。通过三层循环预处理每行特定子列的最大值存于`maxx`数组。再通过两层循环遍历所有k×k区域，找出其中最大值并更新`ans`。最后根据`ans`判断显示器是否会坏及坏掉时间。
- **作者：Error_Eric (4星)**
    - **关键亮点**：将二维滑动窗口问题拆解为两个一维滑动窗口问题，提出严格O(nm)的做法，理论上复杂度最优，能通过加强数据。
    - **重点代码**：链接：[https://codeforc.es/contest/846/submission/179836876](https://codeforc.es/contest/846/submission/179836876)
    - **核心思想**：通过对每行做滑动窗口得到每行特定子列的最大值存于`b`数组，再对`b`数组的每列做滑动窗口得到`c`数组，`c`数组表示对应k×k窗口内的最大值，对`c`数组取min即为所求。
- **作者：Acfboy (4星)**
    - **关键亮点**：先提出二分+优化判断的思路，后进一步优化为直接用单调队列求出每个k×k矩形中的最大值，时间复杂度O(nm)，在洛谷上获得最优解。
    - **重点代码**：
```cpp
#include <cstdio>
#include <deque>
#include <algorithm>
const int N = 505, INF = 0x3f3f3f3f;
int n, m, k, q, f[N][N], cnt[N][N], map[N][N], tot, ans = INF, max[N][N],
    twt[N][N];
std::deque<int> que;
int main() {
    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (int i = 1, x, y, z; i <= q; i++) {
        scanf("%d%d%d", &x, &y, &z);
        map[x][y] = z + 1;
    }
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) {
            f[i][j] = (map[i][j])? (f[i][j - 1] + 1) : 0;
            cnt[i][j] = (f[i][j] >= k)? (cnt[i - 1][j] + 1) : 0;
        }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            while (!que.empty() && map[i][que.back()] < map[i][j]) que.pop_back();
            que.push_back(j);
            max[i][j] = map[i][que.front()];
            while (!que.empty() && j - que.front() + 1 >= k) que.pop_front();
        }
        while (!que.empty()) que.pop_back();
    }
    for (int j = 1; j <= m; j++) { 
        for (int i = 1; i <= n; i++) {
            while (!que.empty() && max[que.back()][j] < max[i][j]) que.pop_back();
            que.push_back(i);
            twt[i][j] = max[que.front()][j];
            while (!que.empty() && i - que.front() + 1 >= k) que.pop_front();
        }
        while (!que.empty()) que.pop_back();
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) 
            if (cnt[i][j] >= k) ans = std::min(ans, twt[i][j]);
    if (ans == INF) ans = -1;
    else ans -= 1;
    printf("%d", ans);
    return 0;
}
```
    - **核心思想**：首先读入数据并初始化，通过两层循环更新`f`和`cnt`数组，`f`数组表示每行连续坏点长度，`cnt`数组表示以某点为右下角满足长为k的矩形的最大高度。再通过单调队列分别求出每行和每列滑动窗口内的最大值存于`max`和`twt`数组，最后根据`cnt`数组判断并更新答案。

### 最优关键思路或技巧
将二维问题转化为一维问题处理，如通过两次一维滑动窗口解决二维滑动窗口问题；利用单调队列优化查找特定区域最大值的过程，减少时间复杂度。

### 同类型题或类似算法套路
此类题目通常围绕二维区域内特定条件的查找与最值求解。常见套路是利用数据结构（如树状数组、ST表）优化查找，或通过滑动窗口、二分等算法降低时间复杂度。

### 洛谷题目推荐
- [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)：经典的滑动窗口题目，有助于理解滑动窗口算法。
- [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)：与本题类似，求二维矩阵中特定大小子矩阵的最值。
- [P9905 [USACO04OPEN]Cube Stacking S](https://www.luogu.com.cn/problem/P9905)：同样涉及二维区域内的最值求解，可巩固相关算法。

### 个人心得摘录与总结
- **Acfboy**：注意单调队列别搞错头尾、时间可以有0。总结为在实现单调队列时要仔细处理边界条件，同时要考虑题目中数据的取值范围。 

---
处理用时：72.13秒