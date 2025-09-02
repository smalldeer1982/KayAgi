# 题目信息

# [USACO1.2] 挤牛奶Milking Cows

## 题目描述

三个农民每天清晨 $5$ 点起床，然后去牛棚给三头牛挤奶。

第一个农民在 $300$ 秒 (从 $5$ 点开始计时) 给他的牛挤奶，一直到 $1000$ 秒。第二个农民在 $700$ 秒开始，在 $1200$ 秒结束。第三个农民在 $1500$ 秒开始，$2100$ 秒结束。  

期间最长的至少有一个农民在挤奶的连续时间为 $900$ 秒 (从 $300$ 秒到 $1200$ 秒)，而最长的无人挤奶的连续时间(从挤奶开始一直到挤奶结束)为 $300$ 秒 (从 $1200$ 秒到 $1500$ 秒)。
****

你的任务是编一个程序，读入一个有 $n$ 个农民挤 $n$ 头牛的工作时间列表，计算以下两点(均以秒为单位):

最长至少有一人在挤奶的时间段。

最长的无人挤奶的时间段。（从有人挤奶开始算起）


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 5000$，$0 \le l \le r \le 10^6$。

题目翻译来自NOCOW。

USACO Training Section 1.2


## 样例 #1

### 输入

```
3
300 1000
700 1200
1500 2100
```

### 输出

```
900 300
```

# AI分析结果

### 综合分析与结论
这些题解思路多样，涵盖了多种算法和数据结构。常见思路有暴力模拟、差分、排序合并区间、线段树、离散化等。暴力模拟简单直接，但数据规模大时易超时；差分和前缀和能优化时间复杂度；排序合并区间通过排序和遍历处理区间；线段树和离散化适用于处理复杂区间问题。

### 所选题解
- **学而思李老师（5星）**
    - **关键亮点**：提供了多种解法，思路清晰，对每种方法的原理和实现细节都有详细说明，还配有图示帮助理解。
    - **核心代码**：
```cpp
// 方法2：结构体sort
#include <bits/stdc++.h>
using namespace std;
int N; 
struct node{
    int begin, end;
}m[5005];
bool cmp(node a, node b){
    return a.begin < b.begin;
}
int main(){
    scanf("%d", &N);
    for(register int i = 1; i <= N; ++ i)
        scanf("%d%d", &m[i].begin, &m[i].end);
    sort(m + 1, m + 1 + N, cmp);
    int begin = m[1].begin;
    int end = m[1].end;
    int ans1 = 0, ans2 = 0;
    for(register int i = 2; i <= N; ++ i){
        if(m[i].begin <= end)
            end = max(end, m[i].end);
        else{
            ans1 = max(ans1, end - begin);
            ans2 = max(ans2, m[i].begin - end);
            begin = m[i].begin;
            end = m[i].end;
        }
    }
    ans1 = max(ans1, end - begin);
    printf("%d %d", ans1, ans2);
    return 0;
}
```
    - **核心思想**：先对区间按开始时间排序，然后遍历区间，合并重叠区间，计算最长有人挤奶时间和最长无人挤奶时间。

- **KesdiaelKen（4星）**
    - **关键亮点**：使用差分思想，复杂度较低，代码简洁明了。
    - **核心代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int c[1000002]={0};//差分数列
int main()
{
    int start=2e9,end=-2e9;
    int n;
    int a,b;
    int tf=1;
    int t[2]={0};
    int nstart;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        c[a]++;
        c[b]--;
        start=min(start,a);
        end=max(end,b-1);
    }
    nstart=start;
    int nc;
    end++;
    for(int i=start;i<=end;i++)
    {
        c[i]=c[i-1]+c[i];
        nc=c[i]==0?0:1;
        if(nc!=tf||i==end)
        {
            t[tf]=max(t[tf],i-nstart);
            nstart=i;
            tf=1-tf;
        }
    }
    printf("%d %d",t[1],t[0]);
    return 0;
}
```
    - **核心思想**：利用差分标记区间，再通过前缀和还原，最后遍历统计最长有人挤奶时间和最长无人挤奶时间。

- **Mys_C_K（4星）**
    - **关键亮点**：思路新颖，将每个时间段的端点看作事件，按时间排序后模拟事件发生过程。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 5000
using namespace std;
struct events{
    int seconds;
    bool is_sore;
}event[maxn*2+10];
int scount=0;
int n;
bool eventcmp(const events &a,const events &b)
{
    if(a.seconds!=b.seconds)
        return a.seconds<b.seconds;
    return a.is_sore;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&event[2*i-1].seconds);event[2*i-1].is_sore=true;
        scanf("%d",&event[2*i].seconds);event[2*i].is_sore=false;
    }
    int eventcount=n*2;
    sort(event+1,event+eventcount+1,eventcmp);
    int ans1=0,ans2=0;
    int last=event[1].seconds;scount++;
    for(int i=2;i<=eventcount;i++)
    {
        if(event[i].is_sore==true)
        {
            if(scount==0)
            {
                ans2=max(ans2,event[i].seconds-last);
                last=event[i].seconds;
            }
            scount++;
        }
        else{
            scount--;
            if(scount==0)
            {
                ans1=max(ans1,event[i].seconds-last);
                last=event[i].seconds;
            }
        }
    }
    cout<<ans1<<" "<<ans2<<endl;
    return 0;
}
```
    - **核心思想**：将每个时间段的开始和结束看作事件，按时间排序，模拟事件发生，根据事件类型更新有人和无人挤奶的最长时间。

### 最优关键思路或技巧
- **排序合并区间**：对区间按开始时间排序，遍历过程中合并重叠区间，可有效处理区间覆盖问题，降低复杂度。
- **差分与前缀和**：用差分标记区间变化，前缀和还原区间状态，能以较低复杂度处理区间修改和查询问题。
- **事件模拟**：将区间端点看作事件，按时间顺序模拟事件发生，可清晰处理区间的开始和结束情况。

### 可拓展之处
同类型题如区间覆盖、区间合并、区间查询等问题，可使用排序、差分、线段树、离散化等算法套路。例如，在处理多个区间的合并和查询时，可先排序再合并区间；处理区间修改和查询时，可使用差分和前缀和或线段树。

### 推荐题目
- P1182 数列分段 Section II：考察二分查找和区间划分。
- P2082 区间覆盖：涉及区间覆盖和贪心算法。
- P3372 【模板】线段树 1：可练习线段树的基本操作。

### 个人心得摘录与总结
- **学而思李老师**：使用暴力布尔数组标记法时，要注意区间端点处理；使用结构体排序法时，要对数据排序，否则可能出错。
- **chenxuanting**：使用初始方法会TLE，未认真读题会WA，要注意每次加的时候是开始时间到结束时间 - 1都加上一。
- **shutdown**：本来想用线段树做，但一直WA和运行时错误，最后只能骗分解决，说明线段树实现时要注意细节。 

---
处理用时：43.38秒