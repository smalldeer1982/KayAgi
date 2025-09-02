# 题目信息

# Vanya and Lanterns

## 题目描述

Vanya walks late at night along a straight street of length $ l $ , lit by $ n $ lanterns. Consider the coordinate system with the beginning of the street corresponding to the point $ 0 $ , and its end corresponding to the point $ l $ . Then the $ i $ -th lantern is at the point $ a_{i} $ . The lantern lights all points of the street that are at the distance of at most $ d $ from it, where $ d $ is some positive number, common for all lanterns.

Vanya wonders: what is the minimum light radius $ d $ should the lanterns have to light the whole street?

## 说明/提示

Vanya walks late at night along a straight street of length $ l $ , lit by $ n $ lanterns. Consider the coordinate system with the beginning of the street corresponding to the point $ 0 $ , and its end corresponding to the point $ l $ . Then the $ i $ -th lantern is at the point $ a_{i} $ . The lantern lights all points of the street that are at the distance of at most $ d $ from it, where $ d $ is some positive number, common for all lanterns.

Vanya wonders: what is the minimum light radius $ d $ should the lanterns have to light the whole street?

## 样例 #1

### 输入

```
7 15
15 5 3 7 9 14 0
```

### 输出

```
2.5000000000
```

## 样例 #2

### 输入

```
2 5
2 5
```

### 输出

```
2.0000000000
```

# AI分析结果

### 题目中文重写
# Vanya和灯笼

## 题目描述
Vanya在一条长度为 $l$ 的笔直街道上夜行，街道由 $n$ 个灯笼照亮。建立一个坐标系，街道的起点对应坐标 $0$，终点对应坐标 $l$。第 $i$ 个灯笼位于坐标 $a_{i}$ 处。每个灯笼的照亮范围是以其为中心，半径为 $d$（$d$ 为正数且所有灯笼相同）的区域。

Vanya想知道：为了照亮整条街道，灯笼的最小照亮半径 $d$ 应该是多少？

## 说明/提示
Vanya在一条长度为 $l$ 的笔直街道上夜行，街道由 $n$ 个灯笼照亮。建立一个坐标系，街道的起点对应坐标 $0$，终点对应坐标 $l$。第 $i$ 个灯笼位于坐标 $a_{i}$ 处。每个灯笼的照亮范围是以其为中心，半径为 $d$（$d$ 为正数且所有灯笼相同）的区域。

Vanya想知道：为了照亮整条街道，灯笼的最小照亮半径 $d$ 应该是多少？

## 样例 #1
### 输入
```
7 15
15 5 3 7 9 14 0
```
### 输出
```
2.5000000000
```

## 样例 #2
### 输入
```
2 5
2 5
```
### 输出
```
2.0000000000
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先对灯笼的位置进行排序，然后找出相邻灯笼之间距离的最大值的一半，同时考虑街道两端的灯笼到街道两端的距离，最终取这几个值中的最大值作为最小的照亮半径。

思路方面，大家都认识到要贪心选取最大的距离来确定半径，并且都注意到了街道两端的特殊情况需要单独处理。

算法要点在于排序和遍历计算距离，难点在于正确处理街道两端的边界情况，避免错误地将两端距离也除以 2。

### 所选题解
- **作者：封禁用户（5星）**
    - **关键亮点**：思路清晰，对问题分析详细，代码注释丰富，输出格式控制准确。
- **作者：伟大的王夫子（4星）**
    - **关键亮点**：思路简洁明了，代码实现简洁，使用 `register` 进行一定优化。
- **作者：YONIC（4星）**
    - **关键亮点**：对问题的分析很直观，代码简洁易懂，对边界问题有明确的提示。

### 重点代码
```cpp
// 封禁用户的代码
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<iomanip>
using namespace std;
double a[1001];
int main()
{
    int n;
    double l,r;
    cin>>n>>l;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }	
    sort(a+1,a+1+n);
    r=max(a[1],l-a[n]);
    for(int i=1;i<n;i++)
    {
        r=max(r,(a[i+1]-a[i])/2);
    }
    cout<<fixed<<setprecision(10)<<r;
    return 0;
}

// 伟大的王夫子的代码
#include <bits/stdc++.h>
using namespace std;
int n;
double a[1010], L, ans;
int main() {
    cin >> n >> L;
    for (register int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    ans = max(a[1], L - a[n]);
    for (register int i = 2; i <= n; ++i) ans = max(ans, (a[i] - a[i - 1]) / 2);
    printf("%.10lf", ans);
}

// YONIC的代码
#include<bits/stdc++.h>
using namespace std;
int n;
double l,r,d[1003];
int main(){
    scanf("%d%lf",&n,&l);
    for(int i=1;i<=n;++i) scanf("%lf",d+i);
    sort(d+1,d+1+n);
    r=max(d[1],l-d[n]);
    for(int i=1;i<n;++i) r=max(r,(d[i+1]-d[i])/2);
    printf("%.10lf",r);
    return 0;
}
```
**核心实现思想**：先读取输入的灯笼数量和街道长度，以及每个灯笼的位置。对灯笼位置进行排序，先求出街道两端的灯笼到街道两端的距离的最大值，再遍历相邻灯笼，求出相邻灯笼距离的最大值的一半，不断更新半径值，最后输出结果。

### 关键思路或技巧
- 排序：对灯笼的位置进行排序，方便后续计算相邻灯笼之间的距离。
- 贪心策略：选取最大的距离来确定最小的照亮半径。
- 边界处理：单独处理街道两端的灯笼到街道两端的距离，避免错误地将其除以 2。

### 拓展思路
同类型题可能会改变街道的形状（如环形街道）、增加不同类型的灯笼（不同照亮半径）等，但核心思路还是贪心选取最大的距离来确定最小的照亮范围。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，通过每次合并最小的两堆果子来求解最小代价。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心算法的应用，通过排序来使总等待时间最短。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：贪心算法，根据物品的性价比来选取物品。

### 个人心得
- **Histone**：因为边界与路灯的距离也除了 2，导致 WA 好多次，提醒大家要正确处理边界情况。 

---
处理用时：32.76秒