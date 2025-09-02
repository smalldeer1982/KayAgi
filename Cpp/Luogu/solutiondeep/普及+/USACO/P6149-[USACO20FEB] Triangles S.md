# 题目信息

# [USACO20FEB] Triangles S

## 题目描述

Farmer John 想要给他的奶牛们建造一个三角形牧场。

有 $N$（$3\leq N\leq 10^5$）个栅栏柱子分别位于农场的二维平面上不同的点 $(X_1,Y_1)\ldots (X_N,Y_N)$。他可以选择其中三个点组成三角形牧场，只要三角形有一条边与 $x$ 轴平行，且有另一条边与 $y$ 轴平行。

FJ 可以组成的所有可能的牧场的面积之和等于多少？

## 说明/提示

#### 样例解释：
栅栏木桩 ($0,0$)、($1,0$) 和 ($1,2$) 组成了一个面积为 $1$ 的三角形，($0,0$)、($1,0$) 和 ($0,1$) 组成了一个面积为 $0.5$ 的三角形。所以答案为 $2\times (1+0.5)=3$。

#### 子任务：
- 测试点 $2$ 满足 $N=200$。
- 测试点 $3$-$4$ 满足 $N\leq 5000$。
- 测试点 $5$-$10$ 没有额外限制。

## 样例 #1

### 输入

```
4
0 0
0 1
1 0
1 2```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是通过枚举直角顶点，计算以该点为直角顶点的所有三角形面积之和。不同题解在实现细节和优化方法上有所差异，主要包括排序方式、前缀和的运用、坐标旋转处理等。部分题解使用了简单的暴力枚举，时间复杂度较高，而大部分题解通过优化将时间复杂度降低到了 $O(N \log N)$ 或 $O(N)$。

### 所选题解
- 作者：泥土笨笨 (赞：30)  ★★★★★
    - 关键亮点：思路清晰，通过枚举直角顶点，利用前缀和的思想计算面积和，考虑了三角形直角的四个方向，代码实现较为完整。
- 作者：7KByte (赞：8)  ★★★★
    - 关键亮点：方法简单，只统计直角顶点在右上角的三角形，通过旋转点的坐标处理其他方向的三角形，时间复杂度为 $O(N)$。
- 作者：tuxiaobei (赞：7)  ★★★★
    - 关键亮点：提供了多种算法思路，从暴力枚举到逐步优化，最后通过排序和状态转移将时间复杂度优化到 $O(N \log N)$，对不同算法的复杂度和得分有清晰的分析。

### 重点代码及核心实现思想
#### 泥土笨笨的题解
```cpp
// 按照不同方向排序并计算结果
sort(points, points + n, cmp1);
work();
sort(points, points + n, cmp2);
work();
sort(points, points + n, cmp3);
work();
sort(points, points + n, cmp4);
work();

void work() {
    memset(sumX, 0, sizeof(sumX));
    memset(sumY, 0, sizeof(sumY));
    memset(cntX, 0, sizeof(cntX));
    memset(cntY, 0, sizeof(cntY));
    for (ll i = 0; i < n; ++i) {
        ll x = points[i].x, y = points[i].y;
        sumX[x] = (sumX[x] + abs(y - lastX[x]) * cntX[x]) % MOD;
        cntX[x]++;
        lastX[x] = y;
        sumY[y] = (sumY[y] + abs(x - lastY[y]) * cntY[y]) % MOD;
        cntY[y]++;
        lastY[y] = x;
        ans = (ans + sumX[x] * sumY[y]) % MOD;
    }
}
```
核心思想：通过四次排序分别处理四个方向的直角三角形，每次排序后遍历每个点，利用前缀和的思想计算以该点为直角顶点的三角形面积和。

#### 7KByte的题解
```cpp
// 统计直角顶点在右上角的三角形
void solve(){
    sort(a+1,a+n+1);
    memset(sum,0,sizeof(sum));
    memset(cnt,0,sizeof(cnt));
    ll now = 0,tot = 0 ;
    rep( i , 1 , n ){
        if(a[i].x != a[i-1].x )now = 0 ,tot = 0 ;
        ans=(ans + ( a[i].x * cnt[a[i].y + bas] - sum[ a[i].y + bas ] )
            % P * ( a[i].y * tot - now ) % P ) % P;
        tot++;now=(now+a[i].y)%P;
        cnt[a[i].y+bas]++;
        sum[a[i].y+bas]=(a[i].x+sum[a[i].y+bas])%P;
    }
}
// 旋转点的坐标
void rev(){
    rep(i,1,n){
        int x=a[i].x,y=a[i].y;
        a[i].x=y;a[i].y=-x;
    }
}
```
核心思想：先统计直角顶点在右上角的三角形，通过旋转点的坐标处理其他方向的三角形。

#### tuxiaobei的题解
```cpp
// 按x坐标排序计算y方向的距离和
for (int i = 1; i <= n;) {
    int l = i;
    int sum = 0;
    for (; a[i].x == a[l].x; i++) sum += a[i].y - a[l].y, sum %= mod;
    int r = i;
    int cnt = r - l;
    for (int i = l; i < r; i++) {
        p[a[i].p] = sum;
        long long dis = a[i + 1].y - a[i].y;
        sum = (sum + ((i - l + 1) * 2 - cnt) * dis) % mod;
        if (sum < 0) sum += mod;
    }
}
// 按y坐标排序计算x方向的距离和
for (int i = 1; i <= n;) {
    int l = i;
    int sum = 0;
    for (; b[i].y == b[l].y; i++) sum += b[i].x - b[l].x, sum %= mod;
    int r = i;
    int cnt = r - l;
    for (int i = l; i < r; i++) {
        q[b[i].p] = sum;
        long long dis = b[i + 1].x - b[i].x;
        sum = (sum + ((i - l + 1) * 2 - cnt) * dis) % mod;
        if (sum < 0) sum += mod;
    }
}
```
核心思想：通过排序和状态转移，利用前一个点的答案计算当前点的距离和，从而优化时间复杂度。

### 最优关键思路或技巧
- **枚举直角顶点**：避免了暴力枚举三个顶点的高复杂度，通过枚举直角顶点可以更高效地计算三角形面积。
- **前缀和思想**：在计算点与其他点的距离和时，利用前缀和可以减少重复计算，提高效率。
- **坐标旋转**：通过旋转点的坐标可以处理不同方向的直角三角形，简化了计算过程。

### 可拓展之处
同类型题可能会改变三角形的条件，如要求三角形的边与坐标轴成一定角度，或者在三维空间中寻找满足条件的三角形。类似算法套路可以应用于其他几何问题，如计算多边形的面积、判断点是否在多边形内等。

### 推荐题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)
- [P2736 最大矩阵](https://www.luogu.com.cn/problem/P2736)
- [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)

### 个人心得摘录与总结
- **Justin0779**：提到这道题细节很多，与 [NOIP2022种花](https://www.luogu.com.cn/problem/P8865) 很像，是一道不错的好题，在模拟赛上切到有感而发。总结：在做几何类题目时要注意细节，多做类似题目积累经验。

---
处理用时：51.02秒