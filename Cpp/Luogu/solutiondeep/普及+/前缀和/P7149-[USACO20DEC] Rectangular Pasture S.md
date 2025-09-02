# 题目信息

# [USACO20DEC] Rectangular Pasture S

## 题目描述

Farmer John 最大的牧草地可以被看作是一个由方格组成的巨大的二维方阵（想象一个巨大的棋盘）。现在，有 $N$ 头奶牛正占据某些方格（$1≤N≤2500$）。

Farmer John 想要建造一个可以包围一块矩形区域的栅栏；这个矩形必须四边与 $x$ 轴和 $y$ 轴平行，最少包含一个方格。请帮助他求出他可以包围在这样的区域内的不同的奶牛子集的数量。注意空集应当被计算为答案之一。 

## 说明/提示

共有 $2^4$ 个子集。FJ 不能建造一个栅栏仅包围奶牛 $1$、$2$、$4$，或仅包围奶牛 $2$、$4$，或仅包围奶牛 $1$、$4$，所以答案为 $2^4-3=16-3=13$。 

 - 测试点 2-3 满足 $N≤20$。
 - 测试点 4-6 满足 $N≤100$。
 - 测试点 7-12 满足 $N≤500$。
 - 测试点 13-20 没有额外限制。

供题：Benjamin Qi 

## 样例 #1

### 输入

```
4
0 2
1 0
2 3
3 5```

### 输出

```
13```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何计算被矩形包围的不同奶牛子集数量展开。多数题解先对坐标离散化处理，将大值域问题转化为有限范围问题。主要思路可分为以下两类：
1. **基于枚举上下边界并结合二维前缀和**：离散化后，通过二维前缀和维护区域内奶牛数量。枚举矩形上下两条边，根据左右两侧奶牛位置条件，利用二维前缀和计算左右边界的可选数量，相乘得到该上下边界组合下的子集数量，最后累加所有组合结果并加上空集情况。
2. **基于枚举上下边界并维护左右侧奶牛数量**：对行坐标排序后，考虑下侧木板在第i行、上侧木板在第j行的情况。为避免重复计算，限定第i行和第j行的牛必须被圈住，根据这两行牛的相对位置，分别确定左右侧围栏可选位置的条件，在枚举过程中维护相关计数并累加答案。

在算法复杂度方面，多数题解时间复杂度为 \(O(N^2)\)，部分使用树状数组的题解时间复杂度为 \(O(N^2log_{2}N)\)。在思路清晰度、代码可读性和优化程度上，各题解存在一定差异。

### 所选的题解
1. **作者：SBofGaySchool (5星)**
    - **关键亮点**：思路清晰，直接暴力求解但通过巧妙的条件设定避免重复计算，代码简洁明了，注释详细，易于理解。
    - **核心代码片段**：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
#define MAXN 2505
ll N;
pair<ll, ll> x[MAXN];
ll ans = 1;
ll l[MAXN], r[MAXN];
int main() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> x[i].first >> x[i].second;
    sort(x, x + N);
    for (ll i = 0; i < N; i++) {
        ans++;
        ll lt = 0, rt = 0;
        for (ll j = i - 1; j >= 0; j--) {
            if (x[i].second > x[j].second) {
                ans += (rt + 1) * (l[j] + 1);
                r[j]++;
                lt++;
            } else {
                ans += (lt + 1) * (r[j] + 1);
                l[j]++;
                rt++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```
    - **核心实现思想**：先对奶牛坐标按行排序，枚举下侧和上侧木板所在行i和j，根据i行和j行奶牛列坐标的相对位置，分别更新左右侧围栏可选位置的计数，并累加相应的子集数量。
2. **作者：Skies (4星)**
    - **关键亮点**：思路明确，利用离散化和二维前缀和的经典组合，代码结构清晰，注释较详细。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
const int N=2501;
int ax[N],ay[N];
struct node{
    int x,y;
}po[N];
int s[N][N];
bool cmp(node x,node y)
{
    return x.y<y.y;
}
int get(int x1,int y1,int x2,int y2)
{
    return s[x2][y2] - s[x2][y1-1] - s[x1-1][y2] + s[x1-1][y1-1];
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&po[i].x,&po[i].y);
        ax[i]=po[i].x;ay[i]=po[i].y;
    }
    sort(ax+1,ax+n+1);
    sort(ay+1,ay+n+1);
    for(int i=1;i<=n;i++)
    {
        po[i].x=lower_bound(ax+1,ax+n+1,po[i].x)-ax;
        po[i].y=lower_bound(ay+1,ay+n+1,po[i].y)-ay;
        s[po[i].x][po[i].y]=1;
    }
    sort(po+1,po+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            int x1=min(po[i].x,po[j].x),x2=max(po[i].x,po[j].x);
            ans+=get(1,po[i].y,x1,po[j].y)*get(x2,po[i].y,n,po[j].y);
        }
    }
    cout<<ans+1;
    return 0;
}
```
    - **核心实现思想**：先离散化奶牛坐标，构建二维前缀和数组s。枚举矩形上下边界，通过get函数利用二维前缀和计算左右边界可选数量，相乘累加得到答案，最后加上空集。
3. **作者：lnwhl (4星)**
    - **关键亮点**：思路阐述详细，结合图示说明，代码实现完整，对二维前缀和的应用清晰。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{int x,y;}poi[2505];
int n,whl1[2505],whl2[2505],sum[2505][2505];
long long ans=0;
int get_s(int a,int b,int c,int d)
{
    return sum[c][d]-sum[a-1][d]-sum[c][b-1]+sum[a-1][b-1];
}
bool cmp(node q,node w){return q.y<w.y;}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>poi[i].x>>poi[i].y;
        whl1[i]=poi[i].x;
        whl2[i]=poi[i].y;
    }
    sort(whl1+1,whl1+n+1);
    sort(whl2+1,whl2+n+1);
    for(int i=1;i<=n;i++)
    {
        poi[i].x=lower_bound(whl1+1,whl1+n+1,poi[i].x)-whl1;
        poi[i].y=lower_bound(whl2+1,whl2+n+1,poi[i].y)-whl2;
        sum[poi[i].x][poi[i].y]=1;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
    sort(poi+1,poi+1+n,cmp);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
        {
            int xmin=min(poi[i].x,poi[j].x);
            int xmax=max(poi[i].x,poi[j].x);
            ans+=get_s(1,i,xmin,j)*get_s(xmax,i,n,j); 
        }
    cout<<ans+1;
    return 0;
}
```
    - **核心实现思想**：离散化奶牛坐标后构建二维前缀和数组sum。枚举矩形上下边界，通过get_s函数利用二维前缀和计算左右边界可选数量，相乘累加答案并加上空集。

### 最优关键思路或技巧
1. **离散化**：由于题目中坐标值域大但奶牛数量有限，通过离散化将大值域坐标映射到有限范围，简化问题处理。
2. **避免重复计算**：如固定矩形上下边界的奶牛，根据相对位置确定左右边界可选条件，避免相同奶牛子集被重复计数。
3. **二维前缀和**：快速计算矩形区域内奶牛数量，提高计算效率。

### 可拓展思路
此类题目属于计数类几何问题，常见拓展方向是增加限制条件或改变图形形状。类似算法套路通常围绕如何高效统计满足特定条件的元素组合，如在不同几何形状（如三角形、圆形等）内统计元素，或在高维空间中进行类似计数，可能会用到前缀和的高维拓展、扫描线算法等。

### 相似知识点洛谷题目
1. **P1387 最大正方形**：涉及在矩阵中寻找满足条件的最大正方形，可利用动态规划和前缀和思想。
2. **P2367 语文成绩**：需要对数据进行离散化处理，并结合树状数组维护区间信息。
3. **P3397 地毯**：通过二维前缀和解决矩形区域内元素统计问题。 

---
处理用时：66.91秒