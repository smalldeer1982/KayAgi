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
这些题解主要围绕如何统计被矩形包围的奶牛子集数量展开。由于奶牛坐标值域较大，多数题解先对坐标进行离散化处理。主要思路可分为以下两类：
1. **暴力枚举边界类**：通过枚举矩形的上下边界（通常是奶牛所在行），再根据边界上奶牛的相对位置，确定左右边界的可选范围，进而计算出每种上下边界组合下的子集数量。如“作者：SBofGaySchool”和“作者：chlchl”的题解。
2. **二维前缀和类**：先离散化坐标，构建二维前缀和数组，通过枚举矩形上下边界，利用二维前缀和快速计算出左右边界可选奶牛数量，从而得到子集数量。如“作者：Skies”“作者：Unordered_OIer”“作者：lnwhl”“作者：andyc_03”“作者：xbb2”“作者：ETHANK”的题解。
3. **树状数组类**：离散化后，按横坐标排序，枚举起点和终点确定横坐标区间，用树状数组维护纵坐标区域点数，根据乘法原理统计合法子集个数。如“作者：wsyhb”“作者：MolotovM”“作者：Ark__Skadi”的题解。

暴力枚举边界类思路直接，但代码实现稍复杂；二维前缀和类通过预处理简化了计算，代码相对简洁；树状数组类在维护点数时更高效，时间复杂度为 \(O(n^2log_{2}n)\)，但理解和实现难度稍高。

### 所选的题解
- **作者：SBofGaySchool（5星）**
    - **关键亮点**：思路清晰，详细阐述了如何避免重复计算相同奶牛子集的情况，代码简洁且注释详细，时间复杂度 \(O(N^2)\) 较优。
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
    - **核心实现思想**：先按行坐标排序，枚举下侧木板所在行 \(i\) 和上侧木板所在行 \(j\)，根据 \(i\) 行和 \(j\) 行奶牛的列坐标相对位置，分别计算左右边界的可选数量，累加答案。
- **作者：Skies（5星）**
    - **关键亮点**：详细讲解了离散化和二维前缀和的使用方法，代码结构清晰，逻辑连贯，通过二维前缀和优化计算，时间复杂度 \(O(N^2)\)。
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
bool cmp(node x,node y){
    return x.y<y.y;
}
int get(int x1,int y1,int x2,int y2){
    return s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &po[i].x, &po[i].y);
        ax[i]=po[i].x;ay[i]=po[i].y;
    }
    sort(ax + 1, ax + n + 1);
    sort(ay + 1, ay + n + 1);
    for (int i = 1; i <= n; i++) {
        po[i].x = lower_bound(ax + 1, ax + n + 1, po[i].x) - ax;
        po[i].y = lower_bound(ay + 1, ay + n + 1, po[i].y) - ay;
        s[po[i].x][po[i].y] = 1;
    }
    sort(po + 1, po + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int x1 = min(po[i].x, po[j].x), x2 = max(po[i].x, po[j].x);
            ans += get(1, po[i].y, x1, po[j].y) * get(x2, po[i].y, n, po[j].y);
        }
    }
    cout << ans + 1 << endl;
    return 0;
}
```
    - **核心实现思想**：离散化坐标后构建二维前缀和数组 \(s\)，枚举矩形上下边界 \(i\) 和 \(j\)，通过 \(get\) 函数利用二维前缀和计算左右边界可选奶牛数量，相乘累加得到答案。
- **作者：wsyhb（4星）**
    - **关键亮点**：分析详细，提出用树状数组维护点数，避免算重的方法新颖，代码注释详细，时间复杂度 \(O(N^2log_{2}N)\)。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int N;
const int max_N = 2500 + 5;
struct node {
    int x, y;
} p[max_N];
bool cmp(node a, node b) {
    return a.x < b.x;
}
int Hash[max_N];
namespace BIT {
    int c[max_N];
    inline void init() {
        for (int i = 1; i <= N; ++i)
            c[i] = 0;
    }
    inline void modify(int k, int v) {
        if (k > 0) {
            for (int i = k; i <= N; i += i & (-i))
                c[i] += v;
        }
    }
    inline int query(int k) {
        int res = 0;
        for (int i = k; i > 0; i -= i & (-i))
            res += c[i];
        return res;
    }
}
int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
        scanf("%d%d", &p[i].x, &p[i].y);
    sort(p + 1, p + N + 1, cmp);
    for (int i = 1; i <= N; ++i)
        Hash[i] = p[i].y;
    sort(Hash + 1, Hash + N + 1);
    for (int i = 1; i <= N; ++i)
        p[i].y = lower_bound(Hash + 1, Hash + N + 1, p[i].y) - Hash;
    long long ans = N + 1;
    for (int i = 1; i <= N; ++i) {
        BIT::init();
        for (int j = i + 1; j <= N; ++j) {
            int l = min(p[i].y, p[j].y);
            int r = max(p[i].y, p[j].y);
            int a = BIT::query(l - 1);
            int b = (j - i - 1) - BIT::query(r);
            ans += 1ll * (a + 1) * (b + 1);
            BIT::modify(p[j].y, 1);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```
    - **核心实现思想**：离散化后按横坐标排序，枚举最靠左和最靠右的奶牛 \(i\) 和 \(j\)，用树状数组维护纵坐标区域点数，计算满足条件的上下边界数量，根据乘法原理统计子集数量。

### 最优关键思路或技巧
1. **离散化**：由于奶牛坐标值域大但数量有限，通过离散化将大坐标映射到较小范围，降低问题规模。
2. **避免重复计算**：如固定矩形边界上的奶牛，确保每种奶牛子集只被计算一次。
3. **利用数据结构优化**：二维前缀和可快速计算矩形区域内的奶牛数量；树状数组能高效维护和查询特定区间内的点数，优化时间复杂度。

### 可拓展之处
此类题目属于计算几何与组合数学结合的问题，类似套路可用于解决在二维平面上统计满足特定形状（如矩形、圆形等）区域内元素组合数量的问题。例如，给定平面上一些点，统计能被特定多边形覆盖的点集数量，同样可考虑离散化、利用数据结构优化等方法。

### 相似知识点洛谷题目
1. [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：涉及二维数组的动态规划与类似的边界处理思想。
2. [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)：需要离散化和树状数组维护区间信息。
3. [P1712 [NOI2016] 区间](https://www.luogu.com.cn/problem/P1712)：离散化后通过排序和数据结构维护区间关系。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：87.01秒