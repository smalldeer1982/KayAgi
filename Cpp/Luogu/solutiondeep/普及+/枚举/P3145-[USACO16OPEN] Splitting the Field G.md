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
这些题解的核心思路基本一致，都是先求出用一个矩形围住所有点的面积，再考虑用两个矩形的情况。用两个矩形时，通过将点按 $x$ 轴或 $y$ 轴排序，枚举分割点，计算不同分割方式下两个矩形的面积和，取最小值。对于区间最值的查询，部分题解使用 RMQ 算法（ST 表），部分题解使用递推预处理，还有题解使用线段树。

### 所选题解
- **作者：Outer_Horizon (赞：7)，4星**
    - **关键亮点**：思路清晰，详细阐述了使用 RMQ 算法优化区间最值查询的过程，代码注释丰富，可读性强。
    - **个人心得**：提到了一些注意事项，如要将 $x$、$y$ 分别排序取最小值，不开 long long 会出错，RMQ 要设置初始值等。
- **作者：caddy (赞：7)，4星**
    - **关键亮点**：通过图形直观展示了沿 $x$ 轴和 $y$ 轴划分矩形的方式，思路清晰，代码简洁易懂。
    - **个人心得**：无。
- **作者：Hoks (赞：3)，4星**
    - **关键亮点**：对 RMQ 算法进行了详细科普，结合本题讲解了如何使用 RMQ 快速查找区间极值，代码实现规范。
    - **个人心得**：介绍了 RMQ 算法的思想和应用场景，帮助读者更好理解。

### 重点代码及核心实现思想
#### Outer_Horizon 的题解
```cpp
// RMQ 初始化
void rmq(){
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= 30; j++){
            fx[i][j][0] = fy[i][j][0] = 1e20;
        }
    }
    for (int i = 1; i <= n; i++) fx[i][0][0] = fx[i][0][1] = a[i].x, fy[i][0][0] = fy[i][0][1] = a[i].y;

    for (int j = 1; j <= 30; j++){
        for (int i = 1; i + (1 << j) - 1 <= n; i++){
            fx[i][j][0] = min(fx[i][j - 1][0], fx[i + (1 << j - 1)][j - 1][0]);
            fx[i][j][1] = max(fx[i][j - 1][1], fx[i + (1 << j - 1)][j - 1][1]);
            fy[i][j][0] = min(fy[i][j - 1][0], fy[i + (1 << j - 1)][j - 1][0]);
            fy[i][j][1] = max(fy[i][j - 1][1], fy[i + (1 << j - 1)][j - 1][1]);
        }
    }
}
// 计算区间面积
int find(int l, int r){
    t = log2(r - l + 1);
    lx = max(fx[l][t][1], fx[r - (1 << t) + 1][t][1]);
    rx = min(fx[l][t][0], fx[r - (1 << t) + 1][t][0]);
    ly = max(fy[l][t][1], fy[r - (1 << t) + 1][t][1]);
    ry = min(fy[l][t][0], fy[r - (1 << t) + 1][t][0]);
    return (lx - rx) * (ly - ry);
}
```
**核心实现思想**：先使用 RMQ 算法预处理出所有区间的 $x$ 和 $y$ 的最值，然后在枚举分割点时，通过 `find` 函数快速计算区间面积。

#### caddy 的题解
```cpp
// 递推预处理最大与最小值
for(int i=1;i<=n;i++)
    aminyzuo[i]=min2(aminyzuo[i-1],a[i].y),amaxyzuo[i]=max2(amaxyzuo[i-1],a[i].y),
    bminxxia[i]=min2(bminxxia[i-1],b[i].x),bmaxxxia[i]=max2(bmaxxxia[i-1],b[i].x);
aminyyou[n+1]=bminxshang[n+1]=0x7fffffffffff;
for(int i=n;i>=1;i--)
    aminyyou[i]=min2(a[i].y,aminyyou[i+1]),amaxyyou[i]=max2(a[i].y,amaxyyou[i+1]),
    bminxshang[i]=min2(b[i].x,bminxshang[i+1]),bmaxxshang[i]=max2(b[i].x,bmaxxshang[i+1]);
// 枚举分割点计算面积
for(int i=1;i<n;i++)
{
    long long  ta=(a[i].x-wl)*(amaxyzuo[i]-aminyzuo[i]);//横着分的面积
    ta+=(el-a[i+1].x)*(amaxyyou[i+1]-aminyyou[i+1]);
    long long  tb=(nl-b[i].y)*(bmaxxshang[i]-bminxshang[i]);//竖着分的面积
    tb+=(b[i-1].y-sl)*(bmaxxxia[i-1]-bminxxia[i-1]);
    tans=min2(ta,tans);
    tans=min2(tans,tb);
}
```
**核心实现思想**：通过递推预处理出每个点左右、上下区域的 $x$ 和 $y$ 的最值，然后枚举分割点，计算不同分割方式下两个矩形的面积和，取最小值。

#### Hoks 的题解
```cpp
// RMQ 初始化
for(int i=1;i<=n;i++) f[i][0][0][0]=f[i][0][0][1]=e[i].x,f[i][0][1][0]=f[i][0][1][1]=e[i].y;
for(int i=0;i<=n;i++)
    for(int j=1;j<=16;j++)
        f[i][j][1][1]=f[i][j][0][1]=0x3f3f3f3f3f3f3f3f;
for(int j=1;j<=16;j++)
    for(int i=0;i<=n-(1<<j)+1;i++)
        f[i][j][0][0]=max(f[i][j-1][0][0],f[i+(1<<j-1)][j-1][0][0]),f[i][j][0][1]=min(f[i][j-1][0][1],f[i+(1<<j-1)][j-1][0][1]),
        f[i][j][1][0]=max(f[i][j-1][1][0],f[i+(1<<j-1)][j-1][1][0]),f[i][j][1][1]=min(f[i][j-1][1][1],f[i+(1<<j-1)][j-1][1][1]);
// 枚举分割点计算面积
for(int i=1;i<n;i++) 
{
    int k=log2(i),maxx1,minn1,maxx2,minn2,num;
    maxx1=max(f[1][k][0][0],f[i-(1<<k)+1][k][0][0]);
    maxx2=max(f[1][k][1][0],f[i-(1<<k)+1][k][1][0]);
    minn1=min(f[1][k][0][1],f[i-(1<<k)+1][k][0][1]);
    minn2=min(f[1][k][1][1],f[i-(1<<k)+1][k][1][1]);
    num=(maxx1-minn1)*(maxx2-minn2);	
    k=log2(n-i);
    maxx1=max(f[i+1][k][0][0],f[n-(1<<k)+1][k][0][0]);
    maxx2=max(f[i+1][k][1][0],f[n-(1<<k)+1][k][1][0]);
    minn1=min(f[i+1][k][0][1],f[n-(1<<k)+1][k][0][1]);
    minn2=min(f[i+1][k][1][1],f[n-(1<<k)+1][k][1][1]);
    ans=min(ans,num+(maxx1-minn1)*(maxx2-minn2));
}
```
**核心实现思想**：使用 RMQ 算法预处理出所有区间的 $x$ 和 $y$ 的最值，然后枚举分割点，计算不同分割方式下两个矩形的面积和，取最小值。

### 最优关键思路或技巧
- **排序枚举**：将点按 $x$ 轴或 $y$ 轴排序，枚举分割点，将点集分成两部分，计算两个矩形的面积和。
- **RMQ 算法（ST 表）**：用于快速查询区间最值，将时间复杂度从 $O(n)$ 优化到 $O(\log n)$。
- **递推预处理**：通过递推的方式预处理出每个点左右、上下区域的最值，避免重复计算。

### 可拓展之处
同类型题：在二维平面上进行区域划分，求满足某种条件的最优解。类似算法套路：排序、枚举、区间最值查询（RMQ、线段树等）。

### 推荐题目
- [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)：考察 RMQ 算法。
- [P2880 [USACO07JAN] Balanced Lineup G](https://www.luogu.com.cn/problem/P2880)：考察 RMQ 算法。
- [P3865 [模板] ST 表](https://www.luogu.com.cn/problem/P3865)：考察 ST 表的使用。

### 个人心得总结
- 注意数据范围，使用 long long 避免溢出。
- 要将 $x$、$y$ 分别排序，取最小值，只对 $x$ 排序可能会导致部分测试点错误。
- RMQ 算法要设置初始值，避免出现未定义行为。

---
处理用时：70.29秒