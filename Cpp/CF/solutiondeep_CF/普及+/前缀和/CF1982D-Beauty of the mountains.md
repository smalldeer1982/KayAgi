# 题目信息

# Beauty of the mountains

## 题目描述

Nikita loves mountains and has finally decided to visit the Berlyand mountain range! The range was so beautiful that Nikita decided to capture it on a map. The map is a table of $ n $ rows and $ m $ columns, with each cell containing a non-negative integer representing the height of the mountain.

He also noticed that mountains come in two types:

- With snowy caps.
- Without snowy caps.

Nikita is a very pragmatic person. He wants the sum of the heights of the mountains with snowy caps to be equal to the sum of the heights of the mountains without them. He has arranged with the mayor of Berlyand, Polikarp Polikarpovich, to allow him to transform the landscape.

Nikita can perform transformations on submatrices of size $ k \times k $ as follows: he can add an integer constant $ c $ to the heights of the mountains within this area, but the type of the mountain remains unchanged. Nikita can choose the constant $ c $ independently for each transformation. Note that $ c $ can be negative.

Before making the transformations, Nikita asks you to find out if it is possible to achieve equality of the sums, or if it is impossible. It doesn't matter at what cost, even if the mountains turn into canyons and have negative heights.

If only one type of mountain is represented on the map, then the sum of the heights of the other type of mountain is considered to be zero.

## 说明/提示

The mountain array from the first test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/c2cad4d039daa4458ac8328be539df0f39115b35.png)Initially, the sum of the heights of the mountains with snowy caps is $ 11 + 3 + 4 + 3 + 0 + 1 + 15 = 37 $ , and without them is $ 7 + 2 = 9 $ .

To equalize these sums, we can perform two transformations:

First transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/26401332927c782774104130bd94cec3d8dea8ef.png)Note that the constant $ c $ can be negative.

After the first transformation, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/8985a2e394a22468e2807bb57386a8c62bc3f888.png)Second transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/83de4303ed287bb4d20cf33c8ab2494ed765c011.png)As a result, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/1dfddde2b777b3b24d753c3d41d8fe42319ee24e.png)The sum of the heights of the mountains with snowy caps is $ 17 + 9 + 9 - 16 - 20 - 19 + 15 = -5 $ , and without them is $ 7 - 12 = -5 $ , thus the answer is YES.

## 样例 #1

### 输入

```
8
3 3 2
7 11 3
4 2 3
0 1 15
100
010
000
4 4 3
123 413 24 233
123 42 0 216
22 1 1 53
427 763 22 6
0101
1111
1010
0101
3 3 2
2 1 1
1 1 2
1 5 4
010
101
010
3 3 2
2 1 1
1 1 2
1 5 3
010
101
010
3 4 3
46 49 50 1
19 30 23 12
30 25 1 46
1000
0100
0010
5 4 4
39 30 0 17
22 42 30 13
10 44 46 35
12 19 9 39
21 0 45 40
1000
1111
0011
0111
1100
2 2 2
3 4
6 7
00
00
2 2 2
0 0
2 0
01
00```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
YES```

# AI分析结果



# Beauty of the mountains

## 题目描述

Nikita 热爱山脉，终于决定去贝里安德山脉游览！这个山脉非常美丽，Nikita 决定用地图记录下来。地图是一个 $n$ 行 $m$ 列的表格，每个单元格包含一个非负整数表示山的高度。

他注意到山脉有两种类型：
- 有雪顶的
- 无雪顶的

Nikita 希望有雪顶的山脉高度之和等于无雪顶的高度之和。他可以通过对 $k \times k$ 的子矩阵进行变换：每次给子矩阵内所有山脉的高度加上任意整数 $c$（可为负数），山脉类型保持不变。请判断是否能通过若干次操作达成目标。

当只有一种类型的山脉时，另一种类型的总和视为零。

---

## 综合分析与结论

所有题解均采用**二维前缀和+裴蜀定理**的核心思路：

1. **问题转化**：将初始两种类型的总高度差记为 $\Delta$，每个 $k \times k$ 操作的影响系数为 $(k^2-2\times \text{雪顶数})$。
2. **系数计算**：通过二维前缀和快速统计每个子矩阵的雪顶数量，计算对应的系数。
3. **裴蜀定理应用**：所有操作系数的最大公约数 $g$ 需整除 $\Delta$ 才有解，特判 $g=0$ 时需 $\Delta=0$。

---

## 精选题解

### 题解作者：xhhhh36（5星）
**关键亮点**：
- 直接计算系数的绝对值并逐步求 GCD，节省内存
- 代码简洁高效，循环条件处理巧妙
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
int t,n,m,k,a[N][N],s[N][N],sa,sb,b[N][N];
signed main(){
    ios::sync_with_stdio(0);
    cin>>t;
    while (t--){
        cin>>n>>m>>k;sa=sb=0;k--;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++) cin>>b[i][j];
        // 前缀和与初始差计算
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++){
                char x; cin>>x; a[i][j]=x-'0';
                s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
                if(a[i][j]) sb += b[i][j]; else sa += b[i][j];
            }
        sa = abs(sa - sb); // 总差绝对值
        int g=0;
        // 遍历所有k+1子矩阵
        for (int i=1;i+k<=n;i++) 
            for (int j=1;j+k<=m;j++){
                int siz = s[i+k][j+k] - s[i-1][j+k] - s[i+k][j-1] + s[i-1][j-1];
                g = __gcd(g, abs((k+1)*(k+1) - 2*siz)); // 关键系数计算
            }
        // 判断逻辑
        if(g==0) cout<<(sa==0?"YES\n":"NO\n");
        else cout<<(sa%g==0?"YES\n":"NO\n");
    }
    return 0;
}
```

### 题解作者：SnapYust（4星）
**核心实现**：显式存储所有系数，完整展示问题转化过程
```cpp
void solve(){
    // 前缀和计算
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=m;j++){
            sum[i][j] = c[i][j-1]-'0' + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
            if(c[i][j-1]-'0'==1) c1 += a[i][j];
            else c2 += a[i][j];
        }
    // 系数收集
    for(int i=1;i+k-1<=n;i++)
        for(int j=1;j+k-1<=m;j++){
            int s1 = sum[i+k-1][j+k-1] - ...; // 雪顶数
            x1[++cn] = s1; x2[cn] = k*k - s1;
        }
    // 裴蜀定理应用
    long long h = x2[1]-x1[1];
    for(int i=2;i<=cn;i++) h = gcd(h, x2[i]-x1[i]);
    if(h==0) cout<<(c2==0?"YES\n":"NO\n");
    else cout<<(c2%h==0?"YES\n":"NO\n");
}
```

---

## 关键思路总结

1. **前缀和优化**：快速统计子矩阵类型数量。
2. **问题线性化**：将操作影响转化为线性方程组。
3. **数论转化**：利用裴蜀定理判断解的存在性。
4. **边界处理**：处理无有效操作时的特殊情况。

---

## 拓展练习

1. [P4549 裴蜀定理](https://www.luogu.com.cn/problem/P4549)  
2. [P3397 地毯](https://www.luogu.com.cn/problem/P3397)（二维差分）
3. [CF798C Mike and gcd problem](https://codeforces.com/problemset/problem/798/C)（gcd性质应用）

---
处理用时：150.84秒