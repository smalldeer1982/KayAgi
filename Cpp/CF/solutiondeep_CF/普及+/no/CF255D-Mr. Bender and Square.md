# 题目信息

# Mr. Bender and Square

## 题目描述

Mr. Bender has a digital table of size $ n×n $ , each cell can be switched on or off. He wants the field to have at least $ c $ switched on squares. When this condition is fulfilled, Mr Bender will be happy.

We'll consider the table rows numbered from top to bottom from 1 to $ n $ , and the columns — numbered from left to right from 1 to $ n $ . Initially there is exactly one switched on cell with coordinates $ (x,y) $ ( $ x $ is the row number, $ y $ is the column number), and all other cells are switched off. Then each second we switch on the cells that are off but have the side-adjacent cells that are on.

For a cell with coordinates $ (x,y) $ the side-adjacent cells are cells with coordinates $ (x-1,y) $ , $ (x+1,y) $ , $ (x,y-1) $ , $ (x,y+1) $ .

In how many seconds will Mr. Bender get happy?

## 说明/提示

Initially the first test has one painted cell, so the answer is 0. In the second test all events will go as is shown on the figure. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF255D/b709c1aa5b91b7af907cf3f3ca10b895a1b76650.png).

## 样例 #1

### 输入

```
6 4 3 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
9 3 8 10
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# Mr. Bender和正方形

## 题目描述
Mr. Bender有一个大小为$n×n$的数字表格，每个单元格可以打开或关闭。他希望表格中至少有$c$个打开的方格。当这个条件满足时，Mr Bender会很高兴。

我们将表格的行从顶部到底部编号为1到$n$，列从左到右编号为1到$n$。最初，恰好有一个坐标为$(x,y)$（$x$是行号，$y$是列号）的单元格是打开的，其他所有单元格都是关闭的。然后，每秒我们会打开那些处于关闭状态但与已打开的单元格相邻的单元格。

对于坐标为$(x,y)$的单元格，其相邻单元格的坐标为$(x - 1,y)$、$(x + 1,y)$、$(x,y - 1)$、$(x,y + 1)$。

Mr. Bender需要多少秒才能高兴起来？

## 说明/提示
最初，第一个测试用例有一个已填充的单元格，所以答案是0。在第二个测试用例中，所有事件将如图所示发生。![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF255D/b709c1aa5b91b7af907cf3f3ca10b895a1b76650.png)

## 样例 #1
### 输入
```
6 4 3 1
```
### 输出
```
0
```
## 样例 #2
### 输入
```
9 3 8 10
```
### 输出
```
2
```

### 算法分类
数学、二分

### 题解综合分析与结论
两道题解思路相似，均先推导无边界情况下扩散点数与时间的关系，再考虑边界情况减去突出部分点数并加上重叠部分点数，最后通过二分查找满足面积条件的最小时间。
- **思路**：先假设无边界得出点数与时间的二次函数关系，再针对边界问题，分析突出部分和重叠部分的点数计算方式。
- **算法要点**：利用数学知识推导公式，结合二分查找优化时间复杂度。
- **解决难点**：关键在于准确分析边界处突出和重叠部分的点数规律并推导相应公式。

### 所选的题解
- **作者LYR_ （5星）**
  - **关键亮点**：思路清晰，通过列表、公式推导及配图详细展示每一步过程，代码简洁明了且注释清晰。
  - **重点代码核心实现思想**：通过二分查找，在每次循环中根据当前时间计算出实际覆盖点数，与目标点数$c$比较，调整查找范围，最终找到满足条件的最小时间。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=1e9+10;
ll n,x,y,c; 
int main() {
    cin>>n>>x>>y>>c;
    x--;y--;
    ll l=0,r=2*n+1,ans=INF;
    while(l<=r) {
        ll mid=(l+r)/2;
        ll s=2*mid*mid+2*mid+1; 
        if(mid-x>0) s-=(mid-x)*(mid-x); 
        if(mid-(n-1-x)>0) s-=(mid-(n-1-x))*(mid-(n-1-x)); 
        if(mid-y>0) s-=(mid-y)*(mid-y); 
        if(mid-(n-1-y)>0) s-=(mid-(n-1-y))*(mid-(n-1-y)); 

        if(mid-x-(n-y-1)-1>0) s+=(1+mid-x-(n-y-1)-1)*(mid-x-(n-y-1)-1)/2; 
        if(mid-(n-1-x)-(n-1-y)>0) s+=(1+mid-(n-1-x)-(n-1-y)-1)*(mid-(n-1-x)-(n-1-y)-1)/2; 
        if(mid-(n-1-x)-y-1>0) s+=(1+mid-(n-1-x)-y-1)*(mid-(n-1-x)-y-1)/2; 
        if(mid-y-x-1>0) s+=(1+mid-y-x-1)*(mid-y-x-1)/2; 

        if(s>=c) {
            r=mid-1;
            ans=min(mid,ans);
        }
        else {
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
- **作者tallnut （4星）**
  - **关键亮点**：逐步推导公式，过程详细，代码通过定义函数使逻辑更清晰。
  - **重点代码核心实现思想**：与LYR_类似，通过二分查找，在`check`函数中计算当前时间下的覆盖点数与$c$比较，主函数中根据比较结果调整二分范围。
```cpp
#include <iostream>
using namespace std;
long long n,x,y,c,l,r,mid,ans;
inline long long sq(long long a) { return a * a; }
inline long long tri(long long a) { return (a * (a + 1)) >> 1; }
bool check()
{
    unsigned long long area = ((mid * mid) << 1) + (mid << 1) + 1;
    if (mid > x) area -= sq(mid - x);
    if (mid + x + 1 > n) area -= sq(mid + x + 1 - n);
    if (mid > y) area -= sq(mid - y);
    if (mid + y + 1 > n) area -= sq(mid + y + 1 - n);
    if (mid > x + y + 1) area += tri(mid - x - y - 1);
    if (mid > n - x + y) area += tri(mid - n + x - y);
    if (mid > n - y + x) area += tri(mid - n + y - x);
    if (mid > (n << 1) - x - y - 1) area += tri(mid - (n << 1) + x + y + 1);
    return (area >= c);
}
int main()
{
    cin >> n >> x >> y >> c;
    x--;
    y--;
    l = 0;
    r = 1e9;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check())
        {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    cout << ans;
}
```

### 最优关键思路或技巧
- **数学推导**：通过分析扩散规律，利用二次函数、等差数列求和等数学知识推导出无边界及边界情况下的点数计算公式。
- **二分查找**：由于时间具有单调性，使用二分查找快速定位满足条件的最小时间，优化了时间复杂度。

### 拓展
同类型题通常涉及图形生长、扩散等场景，类似算法套路为先推导无约束情况下的规律公式，再针对边界或其他约束条件进行修正，最后结合二分查找等优化手段求解。

### 推荐题目
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：通过二分答案解决数列分段问题，考察二分查找及对问题的数学建模。
- [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：同样运用二分查找，在跳跃石头场景下寻找满足条件的最小距离，与本题思路类似。
- [P3853 [TJOI2007] 路标设置](https://www.luogu.com.cn/problem/P3853)：利用二分查找确定路标的合理设置数量，涉及对实际问题的抽象和数学分析。 

---
处理用时：65.83秒