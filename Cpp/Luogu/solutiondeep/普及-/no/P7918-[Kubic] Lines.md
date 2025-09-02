# 题目信息

# [Kubic] Lines

## 题目背景

建议先看 C 题题目背景。

## 题目描述

平面直角坐标系中有 $n$ 条直线，**任意三条直线不交于一点且没有两条直线重合**。显然这些直线形成了不超过 $\dfrac{n(n-1)}{2}$ 个**交点**。你可以从这些直线中选出一部分，一个点被**覆盖**当且仅当有**至少一条**被选中的直线经过了它。求最少选出多少条直线才能**覆盖**所有**交点**。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^5,|a|,|b|,|c|\le 10^9,a,b$ 不全为 $0$。

||分值|$n$|特殊性质|
|:-:|:-:|:-:|:-:|
|$\operatorname{Subtask}1$|$10$|$\le 20$|无|
|$\operatorname{Subtask}2$|$30$|$\le 100$|无|
|$\operatorname{Subtask}3$|$10$|无特殊限制|$ab=0$|
|$\operatorname{Subtask}4$|$50$|无特殊限制|无|

### 样例解释

一种方法是选出 $x+2y+3=0$ 和 $4x+5y+6=0$ 两条线。

可以证明没有更优的方案。

## 样例 #1

### 输入

```
3
1 2 3
4 5 6
7 8 10```

### 输出

```
2
```

# AI分析结果

### 算法分类
数学、贪心

### 综合分析与结论
本题的核心在于通过数学分析得出最优解。题目要求覆盖所有交点，而交点的覆盖可以通过选择直线来实现。通过分析，发现当一组直线平行时，这些直线可以视为一条直线，从而减少需要选择的直线数量。因此，问题转化为找出斜率相同的直线中数量最多的一组，然后用总直线数减去这组直线的数量，即为所需的最少直线数。

### 所选高星题解

#### 题解1：银杉水杉秃杉 (赞：6)
- **星级**：5星
- **关键亮点**：清晰地解释了平行线的处理方式，提供了两种实现方法（有map版和无map版），并详细说明了斜率计算和精度问题。
- **个人心得**：提到double精度问题，改用long double避免精度误差。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, inf = 0x3f3f3f3f;
int n, m, mx;
map<long double, int> s;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        long double f = (a == 0) ? inf : (long double)b / a; //当a=0时，斜率为正无穷
        if (++s[f] > mx)
            mx = s[f];
    }
    printf("%d\n", n - mx);
    return 0;
}
```

#### 题解2：VinstaG173 (赞：5)
- **星级**：4星
- **关键亮点**：通过约分处理斜率，避免了精度问题，代码简洁高效。
- **个人心得**：提到使用约分方法处理斜率，避免double精度问题。

```cpp
#include<map>
#include<cstdio>
#define rg register
using std::map;
using std::pair;
using std::make_pair;
inline int GCD(int a,int b)
{
    while(b^=a^=b^=a%=b);return a;
}
int n,a,b,c,d,mx;
map<pair<int,int>,int>ap;
int main()
{
    n=read();
    for(rg int i=0;i<n;++i)
    {
        a=read(),b=read(),c=read(),d=(a&&b)?GCD(a,b):a+b;
        if((++ap[make_pair(a/d,b/d)])>mx)mx=ap[make_pair(a/d,b/d)];
    }
    printf("%d\n",n-mx);
    return 0;
}
```

#### 题解3：A_Đark_Horcrux (赞：3)
- **星级**：4星
- **关键亮点**：详细分析了平行线的处理方式，并提供了约分方法的正确实现。
- **个人心得**：提到double精度问题，并提供了正确的约分方法。

```cpp
#include<cstdio>
#include<algorithm>
#include<map> 
using namespace std;
int read()
{
    int s=0,b=1; char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') b=-1; c=getchar();}
    while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
    return s*b;
}
map<pair<int,int>,int> m;//索引改为分子和分母！
pair<int,int> f(int x,int y) {return make_pair(x/__gcd(x,y),y/(__gcd(x,y)));} //约分
int n,maxx,s,t,a[100010],b[100010],c[100010];
int main()
{
    n=read();
    for(int i=1;i<=n;i++)//以下操作相同。
        a[i]=read(),b[i]=read(),c[i]=read(),a[i]&&b[i]?m[f(a[i],b[i])]++:(!a[i]?s++:t++);
    for(int i=1;i<=n;i++) if(a[i]&&b[i]) maxx=max(maxx,m[f(a[i],b[i])]);
    printf("%d\n",s+t==n?min(s,t):n-maxx);
    return 0;
 } 
```

### 最优关键思路或技巧
1. **斜率计算与平行线处理**：通过计算直线的斜率，找出斜率相同的直线中数量最多的一组，从而减少需要选择的直线数量。
2. **精度处理**：使用long double或约分方法处理斜率，避免double精度问题。
3. **贪心策略**：通过贪心策略选择最少的直线覆盖所有交点。

### 可拓展之处
类似的问题可以扩展到三维空间中的平面覆盖，或者更复杂的几何图形覆盖问题。通过类似的数学分析和贪心策略，可以解决更复杂的覆盖问题。

### 推荐题目
1. [P7918 [Kubic] Lines](https://www.luogu.com.cn/problem/P7918)
2. [P7919 [Kubic] Lines II](https://www.luogu.com.cn/problem/P7919)
3. [P7920 [Kubic] Lines III](https://www.luogu.com.cn/problem/P7920)

---
处理用时：38.75秒