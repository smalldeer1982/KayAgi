# 题目信息

# [CRCI 2008] PLATFORME 平板

## 题目描述

为了进行一种游戏，现决定搭造一些平板，而各个平板的地址已经选定。基于最普遍的认识，没有任何支持物的平板不可能漂浮在空中。说的更精确些，任意一平板的两端必需有支柱或者它在另一块平板上。

你会得到各个平板在坐标系中的坐标（如左下图）。每一块平板的坐标都是由它的高度（与地板间的垂直距离）和它的水平方位（开始和结束）决定的。每个支柱都距它支撑的平板的边缘半个单位（如图）。

算出支持所有平板的支柱的总长度。

 ![](https://cdn.luogu.com.cn/upload/pic/994.png) 



## 样例 #1

### 输入

```
3

1 5 10

3 1 5

5 3 7

```

### 输出

```
14```

# AI分析结果

• 综合分析与结论：
    - 思路方面，多数题解先对平板按高度排序，再处理每块平板左右端点的支撑情况。少数题解未排序直接暴力枚举。
    - 算法要点：常见做法有暴力枚举（$O(n^2)$），利用数组模拟平板放置更新高度信息，以及使用线段树优化查询和更新操作（$O(nlogn + nlogh)$）。
    - 解决难点：主要是处理支柱位置（在平板边缘往里0.5距离），不少题解通过将坐标扩大两倍简化计算；还有判断平板间支撑关系，需注意端点对齐的不同情况。
    - 整体来看，暴力枚举因数据范围小能通过，但线段树等方法更具扩展性，适用于更大数据规模。

所选的题解：
  - 作者：mzyy1001 (赞：19)  星级：4星
    - 关键亮点：思路简洁清晰，直接双循环暴力枚举，无需排序，代码实现简单明了。
    - 个人心得：指出数据范围小，$n^3$都能过，强调判断平板支撑关系时注意端点对齐情况。
    - 重点代码核心思想：外层循环遍历每块平板，内层循环遍历其他平板，判断是否能支撑当前平板左右端点，更新支撑高度，最后计算支柱总长度。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int y,x1,x2;
}a[1001];
int main()
{
    int n;
    cin >> n;
    int ans = 0;
    for(int i = 1;i <= n;i++)
        scanf("%d%d%d",&a[i].y,&a[i].x1,&a[i].x2);
    for(int i = 1;i <= n;i++)
    {
        int y = a[i].y,x1 = a[i].x1,x2 = a[i].x2;  
        int h1 = 0,h2 = 0;
        for(int j = 1;j <= n;j++)
        {
            if(i == j) 
                continue;
            if(a[j].y >= y) 
                continue;
            if(a[j].x2 > x1 && a[j].x1 <= x1)
                h1 = max(h1,a[j].y);
            if(a[j].x2 >= x2 && a[j].x1 < x2)
                h2 = max(h2,a[j].y);
        }
        ans += y * 2 - h1 - h2;
    }
    cout << ans;
    return 0;
} 
```
  - 作者：Makasukaka (赞：18)  星级：4星
    - 关键亮点：不仅给出$O(n^2)$的暴力解法，还详细阐述线段树优化思路及实现，复杂度降为$O(nlogn + nlogh)$，适用更大数据。
    - 个人心得：事先声明此题小数据范围下不用线段树也能满分，但给出线段树解法用于学习提升。
    - 重点代码核心思想：
      - $O(n^2)$暴力：遍历每块平板，寻找能支撑其左右端点的最高平板，计算支柱长度。
      - 线段树：先按高度排序平板，利用线段树单点查询左右端点最大高度，区间修改更新平板覆盖区间高度。
```cpp
// O(n^2) 暴力解法
#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
#define INF 0x7fffffff
using namespace std;
const int N=1e2+5;
struct leb{
    int y,x1,x2;
}a[N];
LL ans=0;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main(){
    int n=read();
    for(int i=1;i<=n;++i){
        a[i].y=read();
        a[i].x1=read();
        a[i].x2=read();
    }
    for(int i=1;i<=n;++i){
        int c1=INF,c2=INF,f1=0,f2=0;
        double l=a[i].x1+0.5,r=a[i].x2-0.5;
        for(int j=1;j<=n;++j){
            if(i==j)continue;
            int ll=a[j].x1,rr=a[j].x2;
            if(l>ll&&l<rr&&a[i].y>a[j].y)c1=min(c1,a[i].y-a[j].y),f1=1;
            if(r>ll&&r<rr&&a[i].y>a[j].y)c2=min(c2,a[i].y-a[j].y),f2=1;
        }
        if(!f1)c1=min(c1,a[i].y);
        if(!f2)c2=min(c2,a[i].y);
        ans+=(c1+c2);
    }
    printf("%lld\n",ans);
    return 0;
}
// 线段树解法
#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
const int N=1e4+5;
struct leb{
    int y,x1,x2;
}a[N];
struct segtree{
    int l,r,v,tag;
}tr[N<<2];
LL ans=0;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline bool cmp(const leb &a,const leb &b){
    return a.y<b.y;
}
inline void build(int k,int s,int t){
    tr[k].l=s;tr[k].r=t;
    if(s==t)return ;
    int mid=(s+t)/2;
    build(k<<1,s,mid);
    build((k<<1)|1,mid+1,t);
}
inline void pushdown(int k){
    int w=tr[k].tag;
    tr[k<<1].v=max(tr[k<<1].v,w);
    tr[k<<1].tag=max(tr[k<<1].tag,w);
    tr[(k<<1)|1].v=max(tr[(k<<1)|1].v,w);
    tr[(k<<1)|1].tag=max(tr[(k<<1)|1].tag,w);
    tr[k].tag=0;
}
inline int query(int k,int s,int t){
    int l=tr[k].l,r=tr[k].r;
    if(s==l&&t==r)return tr[k].v;
    if(tr[k].tag)pushdown(k);
    int mid=(l+r)/2;
    if(t<=mid)return query(k<<1,s,t);
    else if(s>mid)return query((k<<1)|1,s,t);
    else return max(query(k<<1,s,mid),query((k<<1)|1,mid+1,t));
}
inline void insert(int k,int s,int t,int w){
    int l=tr[k].l,r=tr[k].r;
    if(s==l&&t==r){
        tr[k].v=max(tr[k].v,w);
        tr[k].tag=w;
        return ;
    }
    if(tr[k].tag)pushdown(k);
    int mid=(l+r)/2;
    if(t<=mid)insert(k<<1,s,t,w);
    else if(s>mid)insert((k<<1)|1,s,t,w);
    else {
        insert(k<<1,s,mid,w);
        insert((k<<1)|1,mid+1,t,w);
    }
    tr[k].v=max(tr[k<<1].v,tr[(k<<1)|1].v);
}
int main(){
    int n=read();
    for(int i=1;i<=n;++i){
        a[i].y=read();
        a[i].x1=read();
        a[i].x2=read();
    }
    sort(a+1,a+1+n,cmp);
    build(1,1,N);
    for(int i=1;i<=n;++i){
        int l=a[i].x1,r=a[i].x2;
        int d=query(1,l,l+1);
        ans+=(a[i].y-d);
        d=query(1,r-1,r);
        ans+=(a[i].y-d);
        insert(1,l+1,r-1,a[i].y);
    }
    printf("%lld\n",ans);
    return 0;
}
```
  - 作者：谬悠 (赞：4)  星级：4星
    - 关键亮点：提供不用线段树、搜索、枚举的模拟解法，思路独特，利用数组记录位置高度，通俗易懂。
    - 个人心得：表示自己不会线段树，采用模拟方法，强调因支柱位置特殊处理坐标（乘2），注意数组范围。
    - 重点代码核心思想：按高度排序平板后，依次模拟放置每块平板，查询左右端点已有平板高度计算支柱长度，更新数组表示平板放置情况。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int ans,tu[40050];
struct node {
    int a,b,c;
} num[200];
void jie(int a,int b,int c) {
    b=b+b;
    c=c+c;
    if(tu[b+1]!=0)ans+=(a-tu[b+1]);
    else ans+=a;
    if(tu[c-1]!=0)ans+=(a-tu[c-1]);
    else ans+=a;
    for(int j=b; j<=c; j++) {
        tu[j]=a;
    }
}
bool com(node x,node y){
    return x.a<y.a;
}
int main() {
    int n,a,b,c;
    cin>>n;
    for(int i=0; i<n; i++) {
        cin>>num[i].a>>num[i].b>>num[i].c;
    }
    sort(num,num+n,com);
    for(int i=0;i<n;i++)jie(num[i].a,num[i].b,num[i].c);
    cout<<ans<<endl;
    return 0;
}
```

最优关键思路或技巧：
    - 数据处理技巧：将平板坐标扩大两倍，简化支柱位置在平板边缘往里0.5距离的处理。
    - 算法优化：对于大数据范围，使用线段树优化查询和更新操作，将时间复杂度从$O(n^2)$降为$O(nlogn + nlogh)$。
    - 思维方式：按平板高度排序后处理，便于利用已有平板信息，减少不必要判断。

可拓展之处：同类型题常涉及区间覆盖、高度统计等，类似算法套路如用线段树、扫描线算法解决矩形面积并、周长并等问题。

推荐洛谷题目：
    - P1823 [COI2007] Patrik 音乐会的等待 （涉及排序和利用数据结构优化查询）
    - P3372 【模板】线段树 1 （线段树基础模板题，巩固线段树操作）
    - P2163 [SHOI2007]园丁的烦恼 （结合扫描线和线段树解决矩形覆盖问题）

个人心得摘录及总结：
    - 作者重回巅峰！提到因支柱位置特殊需扩大坐标计算，且数组不能开小，否则易RE。总结为处理特殊位置要合理变换坐标，注意数组范围避免运行错误。
    - 作者谬悠表示不会线段树而采用模拟方法，强调处理支柱位置要变换坐标，且数组要开够大。即若不熟悉复杂数据结构，可从模拟入手，同时关注细节处理。 

---
处理用时：141.03秒