# 题目信息

# [USACO11NOV] Cow Lineup S

## 题目描述

### 问题描述

农民约翰雇一个专业摄影师给他的部分牛拍照。由于约翰的牛有好多品种，他喜欢他的照片包含每个品种的至少一头牛。

约翰的牛都站在一条沿线的不同地方， 每一头牛由一个整数位置 $X_i$ 以及整数品种编号 $ID_i$ 表示。

约翰想拍一张照片，这照片由沿线的奶牛的连续范围组成。照片的成本与规模相当，这就意味着，在一系列照片中的最大和最小 $X$ 坐标的差距决定了照片的成本。

请帮助约翰计算最小的照片成本，这些照片中有每个不同的品种的至少一头牛，没有两头牛愿意站在同一个地点的。

## 样例 #1

### 输入

```
6 
25 7 
26 1 
15 1 
22 3 
20 1 
30 1 
```

### 输出

```
4 
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是先对牛按位置排序，再找出包含所有品种牛的最小连续区间。主要差异在于处理品种编号和查找区间的方法。

在处理品种编号时，部分题解使用 `map` 进行离散化，部分使用哈希函数。查找区间的方法有尺取法、双指针法、单调队列法、优先队列法、二分法等。

### 所选题解
- **作者：糪眾脦颰罷（5星）**
    - **关键亮点**：思路清晰，使用 `map` 存储种类，代码简洁易懂，采用尺取法查找区间。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x;
    int p;
};
node s[70000];
int ans=2e9,sum,n,z,tail;
map<int,int>t;
map<int,bool>pan;
bool cmp(node a,node b){
    return a.x<b.x;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i].x>>s[i].p;
        if(pan[s[i].p]==false){
            sum++;
            pan[s[i].p]=true;
        }
    }
    sort(s+1,s+n+1,cmp);
    tail=1;
    t[s[1].p]++;
    z=1;
    for(int i=1;i<=n;i++){
        while(z<sum&&tail<n){
            tail++;
            t[s[tail].p]++;
            if(t[s[tail].p]==1)z++;
        }
        if(z==sum)ans=min(ans,s[tail].x-s[i].x);
        t[s[i].p]--;
        if(t[s[i].p]==0)z--;
    }
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：先预处理出奶牛的种类总数，然后对奶牛按位置排序。使用尺取法，通过头指针 `i` 和尾指针 `tail` 不断查找包含所有品种牛的区间，并更新最小成本。

- **作者：Priori_Incantatem（4星）**
    - **关键亮点**：双倍经验提示，详细阐述思路，使用双指针法，代码规范。
    - **核心代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
const int Maxn=50000+20,inf=0x3f3f3f3f;
map <int, int> vis;
int a[Maxn],id[Maxn],c[Maxn];
struct cow{
    int x,d;
}srt[Maxn];
int n,ans=inf,tot;
inline bool cmp(cow u,cow v)
{
    return u.x<v.x;
}
int main()
{
    n=read();
    for(int i=1;i<=n;++i)
    {
        srt[i].x=read();
        int tmp=read();
        srt[i].d=calc(tmp);
    }
    sort(srt+1,srt+1+n,cmp);
    for(int i=1;i<=n;++i)
        a[i]=srt[i].x,id[i]=srt[i].d;
    int l=1,r=0,sum=0;
    while(r<n)
    {
        ++r,c[id[r]]++;
        if(c[id[r]]==1)++sum;
        while(c[id[l]]>1)
        {
            c[id[l]]--;
            if(!c[id[l]])--sum;
            ++l;
            if(l>r)break;
        }
        if(sum==tot)
        {
            ans=min(ans,a[r]-a[l]);
            c[id[l]]--;
            if(!c[id[l]])--sum;
            ++l;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
    - **核心实现思想**：先将牛按坐标升序排列，用 `map` 离散化牛的 ID。使用双指针 `l` 和 `r` 维护区间，不断扩展右指针，当区间内牛的种类数足够时，收缩左指针，更新最小成本。

### 最优关键思路或技巧
- **离散化**：使用 `map` 或哈希函数将大的品种编号映射为连续的小编号，方便处理。
- **尺取法/双指针法**：通过移动左右指针，在 $O(n)$ 时间内找到包含所有品种牛的最小连续区间。

### 可拓展之处
同类型题或类似算法套路：
- 滑动窗口问题：如求包含特定元素的最小子数组长度。
- 区间查找问题：如求满足特定条件的最大或最小区间。

### 推荐题目
- [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)
- [P2564 [SCOI2009]生日礼物](https://www.luogu.com.cn/problem/P2564)
- [P3674 小清新人渣的本愿](https://www.luogu.com.cn/problem/P3674)

### 个人心得摘录与总结
- **作者：RainFestival**：提到由于 `ID` 范围大，使用普通方法会有问题，采用离散化处理，但使用了牺牲正确性的方法（取模），因数据量小冲突可能性小而通过。总结：处理大范围数据时要考虑离散化，同时要注意方法的正确性。 

---
处理用时：34.88秒