# 题目信息

# Temporarily unavailable

## 题目描述

Polycarp lives on the coordinate axis $ Ox $ and travels from the point $ x=a $ to $ x=b $ . It moves uniformly rectilinearly at a speed of one unit of distance per minute.

On the axis $ Ox $ at the point $ x=c $ the base station of the mobile operator is placed. It is known that the radius of its coverage is $ r $ . Thus, if Polycarp is at a distance less than or equal to $ r $ from the point $ x=c $ , then he is in the network coverage area, otherwise — no. The base station can be located both on the route of Polycarp and outside it.

Print the time in minutes during which Polycarp will not be in the coverage area of the network, with a rectilinear uniform movement from $ x=a $ to $ x=b $ . His speed — one unit of distance per minute.

## 说明/提示

The following picture illustrates the first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1282A/307b325125eb4f2400d0fb03b9026999f9da2b19.png)Polycarp goes from $ 1 $ to $ 10 $ . The yellow area shows the coverage area of the station with a radius of coverage of $ 1 $ , which is located at the point of $ 7 $ . The green area shows a part of the path when Polycarp is out of coverage area.

## 样例 #1

### 输入

```
9
1 10 7 1
3 3 3 0
8 2 10 4
8 2 10 100
-10 20 -17 2
-3 2 2 0
-3 1 2 0
2 3 2 3
-1 3 -2 2
```

### 输出

```
7
0
4
0
30
5
4
0
3
```

# AI分析结果

### 题目内容
Polycarp 生活在坐标轴 $Ox$ 上，他要从点 $x = a$ 移动到 $x = b$ 。他以每分钟一个单位距离的速度做匀速直线运动。

在坐标轴 $Ox$ 上的点 $x = c$ 处放置了移动运营商的基站。已知其覆盖半径为 $r$ 。因此，如果 Polycarp 距离点 $x = c$ 的距离小于或等于 $r$ ，那么他就在网络覆盖区域内，否则就不在。基站既可以位于 Polycarp 的移动路线上，也可以在路线之外。

请输出 Polycarp 在从 $x = a$ 到 $x = b$ 做匀速直线运动过程中，不在网络覆盖区域内的时间（单位：分钟）。他的速度是每分钟一个单位距离。

### 说明/提示
以下图片说明了第一个测试用例。
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1282A/307b325125eb4f2400d0fb03b9026999f9da2b19.png)
Polycarp 从 $1$ 移动到 $10$ 。黄色区域表示位于点 $7$ 、覆盖半径为 $1$ 的基站的覆盖区域。绿色区域表示 Polycarp 不在覆盖区域内的移动路径部分。

### 样例 #1
#### 输入
```
9
1 10 7 1
3 3 3 0
8 2 10 4
8 2 10 100
-10 20 -17 2
-3 2 2 0
-3 1 2 0
2 3 2 3
-1 3 -2 2
```
#### 输出
```
7
0
4
0
30
5
4
0
3
```

### 算法分类
数学

### 综合分析与结论
所有题解核心思路均为通过分类讨论动点移动区间与基站覆盖区间的位置关系，来计算动点不在网络覆盖区域内的时间。不同题解在分类方式和代码实现上略有差异。部分题解通过详细的多种情况列举分析，部分则通过简洁的数学表达式计算。整体来看，思路较为直接，主要难点在于全面且准确地考虑各种区间位置关系。

### 所选的题解
- **作者：chenyuchenghsefz (5星)**
    - **关键亮点**：思路清晰简洁，先对 $a$ 和 $b$ 排序，然后通过三种情况涵盖所有区间关系，代码实现简洁明了。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int a,b,c,r;
        cin>>a>>b>>c>>r;
        if(a>b)
            swap(a,b);
        if(c+r<a||c-r>b)
            cout<<b-a<<endl;
        else
            cout<<b-a-min(b,c+r)+max(a,c-r)<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：先确保 $a \leq b$ ，若基站覆盖区间完全在动点移动区间左侧（$c + r < a$）或右侧（$c - r > b$），则输出移动区间长度 $b - a$；否则，用移动区间长度减去覆盖区间与移动区间重叠部分的长度（$\min(c + r, b) - \max(c - r, a)$）。
- **作者：xuhanxi_dada117 (5星)**
    - **关键亮点**：代码简洁高效，同样先对 $a$ 和 $b$ 排序，通过简洁的数学表达式计算覆盖区间与移动区间关系，直接得出答案。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int _;cin>>_;
    while(_--){
        int a,b,c,r;
        cin>>a>>b>>c>>r;
        int r1=c-r,r2=c+r;
        if(a>b) swap(a,b);
        if(r2<a||r1>b) cout<<b-a<<"\n";
        else cout<<b-a/*原区间长*/-min(b,r2)+max(a,r1)/*被覆盖长*/<<"\n";
    }
    return 0;
}
```
    - **核心实现思想**：计算出基站覆盖区间端点 $r1 = c - r$ 和 $r2 = c + r$ ，确保 $a \leq b$ 后，若覆盖区间与移动区间无重叠（$r2 < a$ 或 $r1 > b$），输出移动区间长度；否则，用移动区间长度减去重叠部分长度（$\min(b, r2) - \max(a, r1)$）。
- **作者：liuyz11 (4星)**
    - **关键亮点**：通过宏定义等方式增加代码可读性，同样利用数学计算得出结果，思路清晰。
    - **重点代码**：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int a, b, c, r;
        scanf("%d%d%d%d", &a, &b, &c, &r);
        printf("%d\n", max(a, b) - min(a, b) - max(0, min(max(a, b), c + r) - max(min(a, b), c - r)));
    }
    return 0;
}
```
    - **核心实现思想**：先通过 `max(a, b) - min(a, b)` 得到移动区间长度，再通过 `min(max(a, b), c + r) - max(min(a, b), c - r)` 计算覆盖区间与移动区间重叠部分长度，用移动区间长度减去重叠部分长度（为避免重叠部分长度为负，用 `max(0,...)` 处理）得到答案。

### 最优关键思路或技巧
通过对动点移动区间 $[a, b]$ 和基站覆盖区间 $[c - r, c + r]$ 的位置关系进行分类讨论，利用简单的数学运算（如取最值、加减法）来计算未覆盖区间长度。关键在于准确判断区间位置关系，并简洁地用数学表达式表示重叠部分长度。

### 拓展
此类题目属于区间覆盖相关的数学问题，类似套路是清晰定义各区间，全面考虑区间间的包含、相交、相离等位置关系。同类型题可考虑改变区间数量、形状，或增加更多限制条件等。

### 推荐题目
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)
- [P2669 金币](https://www.luogu.com.cn/problem/P2669)
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)

### 个人心得摘录与总结
__Octhyccc__提到一定要先判断 $a,b$ 的大小关系，否则容易出错。总结为在处理区间问题时，区间端点的大小关系可能影响后续逻辑判断与计算，需谨慎处理。 

---
处理用时：65.19秒