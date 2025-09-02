# 题目信息

# Inconvenient Pairs

## 题目描述

There is a city that can be represented as a square grid with corner points in $ (0, 0) $ and $ (10^6, 10^6) $ .

The city has $ n $ vertical and $ m $ horizontal streets that goes across the whole city, i. e. the $ i $ -th vertical streets goes from $ (x_i, 0) $ to $ (x_i, 10^6) $ and the $ j $ -th horizontal street goes from $ (0, y_j) $ to $ (10^6, y_j) $ .

All streets are bidirectional. Borders of the city are streets as well.

There are $ k $ persons staying on the streets: the $ p $ -th person at point $ (x_p, y_p) $ (so either $ x_p $ equal to some $ x_i $ or $ y_p $ equal to some $ y_j $ , or both).

Let's say that a pair of persons form an inconvenient pair if the shortest path from one person to another going only by streets is strictly greater than the Manhattan distance between them.

Calculate the number of inconvenient pairs of persons (pairs $ (x, y) $ and $ (y, x) $ are the same pair).

Let's recall that Manhattan distance between points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ .

## 说明/提示

The second test case is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1569D/d6f9a0633b655a43f906c574ebac3d9bafe5fd65.png)For example, points $ 3 $ and $ 4 $ form an inconvenient pair, since the shortest path between them (shown red and equal to $ 7 $ ) is greater than its Manhattan distance (equal to $ 5 $ ).

Points $ 3 $ and $ 5 $ also form an inconvenient pair: the shortest path equal to $ 1000001 $ (shown green) is greater than the Manhattan distance equal to $ 999999 $ .

But points $ 5 $ and $ 9 $ don't form an inconvenient pair, since the shortest path (shown purple) is equal to its Manhattan distance.

## 样例 #1

### 输入

```
2
2 2 4
0 1000000
0 1000000
1 0
1000000 1
999999 1000000
0 999999
5 4 9
0 1 2 6 1000000
0 4 8 1000000
4 4
2 5
2 2
6 3
1000000 1
3 8
5 8
8 8
6 8```

### 输出

```
2
5```

# AI分析结果

### 题目翻译
## 不便的点对

### 题目描述
有一座城市，可以用一个顶点坐标为 $(0, 0)$ 和 $(10^6, 10^6)$ 的正方形网格来表示。

这座城市有 $n$ 条垂直街道和 $m$ 条水平街道，这些街道贯穿整个城市。即第 $i$ 条垂直街道从 $(x_i, 0)$ 延伸到 $(x_i, 10^6)$，第 $j$ 条水平街道从 $(0, y_j)$ 延伸到 $(10^6, y_j)$。

所有街道都是双向的，城市的边界也是街道。

有 $k$ 个人站在街道上，第 $p$ 个人位于点 $(x_p, y_p)$（所以要么 $x_p$ 等于某个 $x_i$，要么 $y_p$ 等于某个 $y_j$，或者两者都满足）。

如果一对人之间仅沿着街道行走的最短路径严格大于他们之间的曼哈顿距离，那么就称这对人为不便的点对。

计算不便的点对的数量（点对 $(x, y)$ 和 $(y, x)$ 视为同一对）。

回顾一下，点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 之间的曼哈顿距离是 $|x_1 - x_2| + |y_1 - y_2|$。

### 说明/提示
第二个测试用例如下图所示：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1569D/d6f9a0633b655a43f906c574ebac3d9bafe5fd65.png)

例如，点 $3$ 和 $4$ 构成一个不便的点对，因为它们之间的最短路径（如图中红色所示，长度为 $7$）大于它们的曼哈顿距离（等于 $5$）。

点 $3$ 和 $5$ 也构成一个不便的点对：最短路径长度为 $1000001$（如图中绿色所示），大于曼哈顿距离 $999999$。

但是点 $5$ 和 $9$ 不构成不便的点对，因为最短路径（如图中紫色所示）等于它们的曼哈顿距离。

### 样例 #1
#### 输入
```
2
2 2 4
0 1000000
0 1000000
1 0
1000000 1
999999 1000000
0 999999
5 4 9
0 1 2 6 1000000
0 4 8 1000000
4 4
2 5
2 2
6 3
1000000 1
3 8
5 8
8 8
6 8
```

#### 输出
```
2
5
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是先对点进行分类，排除一些不可能构成不便点对的点（如位于横竖街道交点的点），然后分别考虑在横线上的点和在竖线上的点。对于同一类点，通过判断两点之间是否有不同类型的街道穿过，来确定它们是否构成不便点对。不同题解的主要区别在于具体的实现方式和数据结构的选择。

### 所选题解
- **作者：GaryH (赞：4)，4星**
    - **关键亮点**：思路清晰，先对特殊点进行排除，然后将在横线上的点与在竖线上的点分开考虑，利用排序和简单的计数方法来计算不便点对的数量，代码实现简洁。
- **作者：ran_qwq (赞：2)，4星**
    - **关键亮点**：准确总结出两点构成不便点对的充要条件，通过双指针的方法来找出区域和区域内的点，计算答案的思路明确。
- **作者：TernaryTree (赞：1)，4星**
    - **关键亮点**：对不便点对的条件分析详细，结合样例图片进行解释，通过排序分块的方式来计算答案，逻辑严谨。

### 重点代码
#### GaryH 的代码
```cpp
const int N(3e5+10);
typedef pair < int , int > pii ;
int n,m,k;
int xline[N];
int yline[N];
inline void work(){
    vector < pii > x , y ;
    n=read(),m=read(),k=read();
    int cntx[n+10]={},cnty[m+10]={};
    rep(i,0,n-1)xline[i]=read();
    rep(i,0,m-1)yline[i]=read();
    rep(i,0,k-1){
        int px=read(),py=read();
        bool fx=binary_search(xline,xline+n,px);
        bool fy=binary_search(yline,yline+m,py);
        if(fx&&fy)continue;
        if(fx){
            int pos=lower_bound(yline,yline+m,py)-yline-1;
            cnty[pos]++,x.pb(mp(px,pos));
        }else{
            int pos=lower_bound(xline,xline+n,px)-xline-1;
            cntx[pos]++,y.pb(mp(py,pos));
        }
    } 
    long long res=0;
    rep(i,0,n-1)res+=1ll*(cntx[i]-1)*cntx[i]/2;
    rep(i,0,m-1)res+=1ll*(cnty[i]-1)*cnty[i]/2;
    for(auto p:{x,y}){
        sort(p.begin(),p.end());
        for(int l=0,r;l<(int)(p.size());l=r){
            for(r=l;r<(int)(p.size())&&p[l]==p[r];r++);
            res-=1ll*(r-l)*(r-l-1)/2;
        }
    } 
    cout<<res<<endl;
}
```
**核心实现思想**：先读取输入，将点分类到横线上的点集 `x` 和竖线上的点集 `y` 中，同时统计每个区间内的点的数量。然后计算所有可能的点对数量，再减去同一位置的点对数量，得到最终的不便点对数量。

#### ran_qwq 的代码
```cpp
int n,m,k,x[N],y[N]; pii p[N],q[N]; ll ans;
void QwQ() {
    n=rd(),m=rd(),k=rd(),ans=0;
    for(int i=1;i<=n;i++) x[i]=rd();
    for(int i=1;i<=m;i++) y[i]=rd();
    for(int i=1;i<=k;i++) p[i]=q[i]={rd(),rd()};
    sort(p+1,p+1+k),sort(q+1,q+1+k,[&](pii x,pii y) {return pii{x.sec,x.fir}<pii{y.sec,y.fir};});
    for(int i=2,l=1,r=1;i<=n;i++) {
        while(l<=k&&p[l].fir==x[i-1]) l++;
        r=l; while(r<=k&&p[r].fir<x[i]) r++;
        sort(p+l,p+r,[&](pii x,pii y) {return x.sec<y.sec;});
        for(int j=l,cnt=0;j<=r;j++)
            if(j!=r&&(j==l||p[j].sec==p[j-1].sec)) cnt++;
            else ans-=1ll*cnt*(cnt-1)/2,cnt=1;
        ans+=1ll*(r-l)*(r-l-1)/2,l=r;
    }
    for(int i=2,l=1,r=1;i<=m;i++) {
        while(l<=k&&q[l].sec==y[i-1]) l++;
        r=l; while(r<=k&&q[r].sec<y[i]) r++;
        sort(q+l,q+r,[&](pii x,pii y) {return x.fir<y.fir;});
        for(int j=l,cnt=0;j<=r;j++)
            if(j!=r&&(j==l||q[j].fir==q[j-1].fir)) cnt++;
            else ans-=1ll*cnt*(cnt-1)/2,cnt=1;
        ans+=1ll*(r-l)*(r-l-1)/2,l=r;
    }
    wrll(ans,"\n");
}
```
**核心实现思想**：先读取输入并对所有点进行排序，然后通过双指针的方法找出每个区域内的点，对区域内的点按另一个坐标排序，统计同一位置的点对数量并从总点对数量中减去，得到最终结果。

#### TernaryTree 的代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6 + 10;
struct point {
    int x, y, r;
};
int t, n, m, k, ans;
int x[maxn], y[maxn];
map<int, bool> bx, by;
point cx[maxn], cy[maxn];
int dx, dy;
signed main() {
    ios::sync_with_stdio(0);
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        bx.clear(), by.clear();
        dx = dy = ans = 0;
        for (int i = 1; i <= n; i++) cin >> x[i], bx[x[i]] = 1;
        for (int i = 1; i <= m; i++) cin >> y[i], by[y[i]] = 1;
        for (int i = 1, x, y; i <= k; i++) {
            cin >> x >> y;
            if (bx.count(x) && by.count(y)) continue;
            if (bx.count(x)) cx[++dx] = {x, y};
            if (by.count(y)) cy[++dy] = {x, y};
        }
        sort(x + 1, x + 1 + n);
        sort(y + 1, y + 1 + m);
        for (int i = 1; i <= dx; i++) cx[i].r = lower_bound(y + 1, y + 1 + m, cx[i].y) - y;
        for (int i = 1; i <= dy; i++) cy[i].r = lower_bound(x + 1, x + 1 + n, cy[i].x) - x;
        sort(cx + 1, cx + 1 + dx, [] (point u, point v) {
            int p = u.r;
            int q = v.r;
            if (p == q) return u.x < v.x;
            else return p < q;
        });
        sort(cy + 1, cy + 1 + dy, [] (point u, point v) {
            int p = u.r;
            int q = v.r;
            if (p == q) return u.y < v.y;
            else return p < q;
        });
        int cur = 1;
        for (int i = 2; i <= m; i++) {
            int s = y[i - 1], e = y[i];
            int last = cur;
            while (cur <= dx && cx[cur].y < e) ++cur;
            int p = last;
            int sum = 0;
            for (int j = last + 1; j < cur; j++) {
                if (cx[j].x != cx[j - 1].x) sum += (j - p) * (j - p), p = j;
            }
            sum += (cur - p) * (cur - p);
            ans += ((last - cur) * (last - cur) - sum) / 2;
        }
        cur = 1;
        for (int i = 2; i <= n; i++) {
            int s = x[i - 1], e = x[i];
            int last = cur;
            while (cur <= dy && cy[cur].x < e) ++cur;
            int p = last;
            int sum = 0;
            for (int j = last + 1; j < cur; j++) {
                if (cy[j].y != cy[j - 1].y) sum += (j - p) * (j - p), p = j;
            }
            sum += (cur - p) * (cur - p);
            ans += ((last - cur) * (last - cur) - sum) / 2;
        }
        cout << ans << endl;
    }
    return 0;
}
```
**核心实现思想**：先读取输入，将点分类到 `cx` 和 `cy` 数组中，然后对 `x` 和 `y` 数组排序，计算每个点所在的区域。接着对 `cx` 和 `cy` 数组按区域和坐标排序，分块计算每个区域内的不便点对数量，最后将结果累加得到最终答案。

### 最优关键思路或技巧
- **分类讨论**：将点分为在横线上的点、在竖线上的点和在横竖线交点的点，排除不可能构成不便点对的交点，简化问题。
- **排序**：对同一类点进行排序，方便后续统计和计算。
- **双指针或分块**：通过双指针或分块的方法找出区域和区域内的点，避免不必要的枚举。

### 可拓展之处
同类型题可能会改变城市的形状、街道的分布或点的限制条件，但核心思路仍然是判断两点之间的最短路径是否大于曼哈顿距离。类似的算法套路包括对图形进行划分、对元素进行分类和排序，以及利用双指针或分块的方法进行统计。

### 推荐洛谷题目
- P1106 删数问题（排序、贪心）
- P1223 排队接水（排序、贪心）
- P1090 合并果子（排序、贪心）

### 个人心得摘录与总结
- **ran_qwq**：“和人 duel 到这道题，傻逼题还做三十分钟，退役吧。” 总结：该作者认为此题花费时间较长，可能在解题过程中遇到了困难。
- **Daidly**：“赛时调了 1h......” 总结：该作者在比赛时调试代码花费了较长时间，可能在实现细节上遇到了问题。
- **The_foolishest_OIer**：“独一档做法，调了两天，终于过了（这种超大网格题我的做法总是很奇怪）。” 总结：该作者为解决此题花费了两天时间，且认为自己的做法比较奇怪，可能在处理超大网格问题时没有找到合适的方法。

---
处理用时：138.15秒