# 题目信息

# [USACO16OPEN] Splitting the Field G

## 题目描述

Farmer John 的 $N$ 头奶牛（$3 \leq N \leq 50,000$）位于他二维牧场的不同位置。FJ 想要用一个与 x 轴和 y 轴平行的矩形围栏将所有奶牛围住，并且他希望这个围栏尽可能小，以便它包含每一头奶牛（允许奶牛位于边界上）。

由于上季度牛奶产量低，FJ 的预算紧张。因此，他希望围住更小的区域以减少维护成本，而他唯一能想到的方法就是建造两个围栏而不是一个。请帮助他计算使用两个围栏而不是一个围栏总共可以减少多少面积。与原始围栏一样，这两个围栏必须共同包含所有奶牛（允许奶牛位于边界上），并且它们的边必须与 $x$ 轴和 $y$ 轴平行。这两个围栏不允许重叠——即使在它们的边界上也不行。注意，零面积的围栏是合法的，例如如果一个围栏的宽度和/或高度为零。

## 样例 #1

### 输入

```
6
4 2
8 10
1 1
9 12
14 7
2 3```

### 输出

```
107```

# AI分析结果

### 综合分析与结论
1. **思路**：多数题解思路为将点按x轴或y轴排序，枚举分界点，把点分成两组，分别计算两个矩形面积和，取最小值。曹老师、Orion_Rigel、kardsOI等题解明确指出分上下或左右两种划分方式；Outer_Horizon、Hoks、liuzhengtao等题解通过排序枚举分界点来涵盖所有可能划分。
2. **算法要点**：需计算包含给定点集的矩形面积，通过找出点集中横纵坐标的最大最小值来确定矩形长和宽。为优化查找区间最值操作，Outer_Horizon、Hoks、liuzhengtao使用RMQ（ST表）；miserExist使用线段树；caddy、曹老师、Orion_Rigel、kardsOI通过递推预处理区间最值。
3. **解决难点**：难点在于如何高效划分点集以得到最小面积的两个矩形。通过按x、y轴排序并枚举分界点解决，同时利用数据结构或递推优化区间最值查询。

综合质量，以下题解评分较高：
- **Outer_Horizon**：★★★★
    - **关键亮点**：思路清晰，先简化问题，提出以(0,0)为锚点排序并划分点序列的方法，且证明其合理性；详细介绍RMQ算法及应用，代码注释详细。
    - **个人心得**：强调注意事项，如要对x、y分别排序取最小值、开long long、RMQ设置初始值、最后用总面积减所求最小值。
```cpp
// 计算l - r区间内的面积
int find(int l, int r){ 
    t = log2(r - l + 1);
    lx = max(fx[l][t][1], fx[r - (1 << t) + 1][t][1]);
    rx = min(fx[l][t][0], fx[r - (1 << t) + 1][t][0]);
    ly = max(fy[l][t][1], fy[r - (1 << t) + 1][t][1]);
    ry = min(fy[l][t][0], fy[r - (1 << t) + 1][t][0]);
    return (lx - rx) * (ly - ry);
}
signed main() {
    n = read();
    for (int i = 1; i <= n; i++) a[i].x = read(), a[i].y = read();
    // x 
    sort(a + 1, a + 1 + n, cmp1);
    rmq();
    for (int i = 1; i < n; i++){
        int k = find(1, i), q = find(i + 1, n);
        ans = min(ans, k + q);
    }
    // y
    sort(a + 1, a + 1 + n, cmp2);
    rmq();
    for (int i = 1; i < n; i++){
        int k = find(1, i), q = find(i + 1, n);
        ans = min(ans, k + q);
    }

    cout << find(1, n) - ans;  // 输出答案，大面积减去小面积
    return 0;
}
```
- **caddy**：★★★★
    - **关键亮点**：思路直观，通过图形展示沿x轴或y轴划分矩形的方式；代码简洁，利用宏定义简化代码，递推预处理区间最值。
```cpp
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld %lld",&a[i].x,&a[i].y);
        b[i].x=a[i].x,b[i].y=a[i].y;
    }
    sort(a+1,a+1+n,cmp1);
    sort(b+1,b+1+n,cmp2);
    aminyzuo[0]=bminxxia[0]=0x7fffffff;
    for(int i=1;i<=n;i++)
    aminyzuo[i]=min2(aminyzuo[i-1],a[i].y),amaxyzuo[i]=max2(amaxyzuo[i-1],a[i].y),
    bminxxia[i]=min2(bminxxia[i-1],b[i].x),bmaxxxia[i]=max2(bmaxxxia[i-1],b[i].x);
    aminyyou[n+1]=bminxshang[n+1]=0x7fffffffffff;
    for(int i=n;i>=1;i--)
    aminyyou[i]=min2(a[i].y,aminyyou[i+1]),amaxyyou[i]=max2(a[i].y,amaxyyou[i+1]),
    bminxshang[i]=min2(b[i].x,bminxshang[i+1]),bmaxxshang[i]=max2(b[i].x,bmaxxshang[i+1]);//递推预处理最大与最小值
    long long  el=a[n].x,wl=a[1].x,nl=b[n].y,sl=b[1].y;
    long long ans=(nl-sl)*(el-wl);
    long long tans=0x7fffffffffffffff;
    for(int i=1;i<n;i++)
    {
        long long  ta=(a[i].x-wl)*(amaxyzuo[i]-aminyzuo[i]);//横着分的面积
        ta+=(el-a[i+1].x)*(amaxyyou[i+1]-aminyyou[i+1]);
        long long  tb=(nl-b[i].y)*(bmaxxshang[i]-bminxshang[i]);//竖着分的面积
        tb+=(b[i-1].y-sl)*(bmaxxxia[i-1]-bminxxia[i-1]);
        tans=min2(ta,tans);
        tans=min2(tans,tb);
    }
    printf("%lld",ans-tans);
}
```
- **liuzhengtao**：★★★★
    - **关键亮点**：题目分析清晰，明确指出解题需按x、y排序并枚举分界点求区间最值；代码结构清晰，使用函数封装RMQ的构建和查询操作。
```cpp
inline void build()
{
    for(int i=1;i<=n;i++)
    {
        fx[i][0][0]=fx[i][0][1]=a[i].x;
        fy[i][0][0]=fy[i][0][1]=a[i].y;    
    }    
    for(int e=1;e<=20;e++)
    {
        for(int i=1;i+(1<<e)-1<=n;i++)
        {
            fx[i][e][0]=min(fx[i][e-1][0],fx[i+(1<<(e-1))][e-1][0]);
            fx[i][e][1]=max(fx[i][e-1][1],fx[i+(1<<(e-1))][e-1][1]);
            fy[i][e][0]=min(fy[i][e-1][0],fy[i+(1<<(e-1))][e-1][0]);
            fy[i][e][1]=max(fy[i][e-1][1],fy[i+(1<<(e-1))][e-1][1]);            
        }
    }
}
inline int find(int l,int r)
{
    int t=log2(r-l+1);
    int lx = max(fx[l][t][1],fx[r-(1 << t)+1][t][1]);
    int rx = min(fx[l][t][0],fx[r-(1 << t)+1][t][0]);
    int ly = max(fy[l][t][1],fy[r-(1 << t)+1][t][1]);
    int ry = min(fy[l][t][0],fy[r-(1 << t)+1][t][0]);
    return (lx - rx) * (ly - ry);
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x>>a[i].y;
    }
    sort(a+1,a+n+1,cmp1);
    build();
    for(int i=1;i<=n;i++)
    {
        int k1=find(1,i),k2=find(i+1,n);
        ans=min(ans,k1+k2);
    }
    sort(a+1,a+n+1,cmp2);
    build();
    for(int i=1;i<=n;i++)
    {
        int k1=find(1,i),k2=find(i+1,n);
        ans=min(ans,k1+k2);
    }
    cout<<find(1,n)-ans;    
    return 0;
}
```

### 最优关键思路或技巧
1. **排序与枚举**：按x轴和y轴分别排序点集，枚举分界点划分点集为两组，全面考虑所有可能的矩形划分方式。
2. **区间最值优化**：使用RMQ（ST表）、线段树或递推方式优化区间最值查询，降低时间复杂度。如RMQ利用倍增思想，将区间最值查询复杂度从O(n)降至O(log n)；递推方式通过预处理，以O(n)时间复杂度完成区间最值计算。

### 可拓展思路
此类题目可拓展到更高维度或增加限制条件，如三维空间中用多个长方体包围点集，或要求矩形满足特定比例等。类似算法套路为通过排序、枚举等方式确定划分方式，利用合适数据结构优化关键操作。

### 相似知识点洛谷题目
1. **P1816 忠诚**：典型RMQ问题，给定序列求区间最小值，可加深对RMQ算法理解。
2. **P3865 [模板]  ST 表**：模板题，用于练习ST表构建和查询操作。
3. **P1440 求m区间内的最小值**：结合排序和区间最值查询，与本题部分思路相似。 

---
处理用时：65.40秒