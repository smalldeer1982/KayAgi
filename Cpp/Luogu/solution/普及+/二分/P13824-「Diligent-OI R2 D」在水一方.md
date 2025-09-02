# 「Diligent-OI R2 D」在水一方

## 题目背景

Ns6 每次上冬公令的课程都会带来一堆零食。这令 Klg 和 acmp 觊觎已久。

于是，Klg 和 acmp 制定了一个秘密的劫掠计划。

机房中危机四伏。Ns6 能否逃过一劫？

## 题目描述

机房巨大无比，结构错综复杂。其中有 $n$ 个通道分叉口，有两个参数为 $x_i,y_i$。讲台也属于一个分叉口，编号是 $1$。从第 $i$ 个分叉口到第 $j$ 个分叉口的「NC2 距离」是 $(x_i-x_j)^2+(y_i-y_j)^2$。

有 $n-1$ 条双向的通道使得所有分叉口联通起来。换句话说，机房的结构构成了一棵以讲台为根的树。**每条通道的长度是连接的两个分叉口之间的「NC2 距离」。**

人只能在通道中行走，在一条通道的中间也不能拐进另一条通道。但零食可以在「NC2 距离」不大于 $d$ 的两点中进行抛接传递。

Klg 和 acmp 的劫掠计划如下：

- 先选择两个分叉口 $p,q$（$p\le q$），Klg 的起点为 $p$，acmp 的起点为 $q$。记机房中连接 $p$ 和 $q$ 两分叉口的最短的**通道形成的路径**为活动路径。
- 每次，两人之间都进行一次零食传递，也就是要求每一次两人所在的分叉口之间的「NC2 距离」不超过 $d$。请注意，初始两人在 $p,q$ 两点时也要进行传递。
- 每次传递完零食之后，两人必须选择**至少一个人向讲台的方向**走恰好一条通道，然后进行下一次零食传递。**但是全程两个人都不能离开活动路径。**
- 某次该传递零食时，如果两人已经到了同一个分叉口，劫掠停止，计划成功。

Klg 和 acmp 共计划了 $t$ 次劫掠，每次的 $d$ 可能变化。现在 Ns6 需要知道的是，对于每一次劫掠计划，如果它能成功，活动路径的长度（即活动路径上每条通道的长度之和）最长会是多少？请输出这个条件下的 $p,q$。如果有多解输出 $p$ 最小的，还有多解输出 $q$ 最小的。

**请注意，本题中的两点间距离是「NC2 距离」，并非欧几里得距离。**

## 说明/提示

#### 样例 #1 解释

样例中机房结构如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/t7bbmaa8.png)

以第一次劫掠为例：

点 $7$ 和 $12$ 的 $x,y$ 分别为 $(10,4)$ 和 $(10,2)$。

$7$ 和 $12$ 两点之间的活动路径长度为 $34+29+5=68$。

一开始两个人分别在 $7,12$，之间「NC2 距离」为 $4$。

第二步两个人分别在 $7,8$，之间「NC2 距离」为 $1$。

第三步两个人都在 $3$，劫掠结束。

可证明不存在更优方案。

#### 数据范围

所有数据保证，$3\le n\le 1000,1\le t\le 10^5,0\le x_i,y_i\le 10^6,0\le d\le2\times10^{12}$。

- Subtask 1（20pts）：$n\le10,t\le5$。
- Subtask 2（15pts）：$n\le100,t\le5$。
- Subtask 3（25pts）：$t\le5$。
- Subtask 4（10pts）：对于每个分叉口，仅与至多两条通道相邻。
- Subtask 5（30pts）：无特殊性质。

## 样例 #1

### 输入

```
12 4
10 10
9 7
13 9
5 6
3 4
7 4
10 4
11 4
13 4
5 1
8 1
10 2
1 2
1 3
2 4
4 5
4 6
3 7
3 8
3 9
6 10
8 11
8 12
9
20
45
1```

### 输出

```
7 12
7 11
10 11
7 8```

# 题解

## 作者：Night_sea_64 (赞：2)

出题人题解。

这题不难发现，只要求出任意点对之间最小的 $d$ 是多少就能用排序+双指针回答询问了。

我们需要知道，从初始两个点开始推后面的状态是很难的，不妨倒着处理。

设 dp 状态为 $f_{i,j}$ 表示两人分别在 $i$ 和 $j$ 时，最小的 $d$ 是多少。而起点肯定是所有 $i=j$ 的情况。

于是 $f_{i,j}$ 就可以从 $f_{fa_i,j}$、$f_{i,fa_j}$ 和 $f_{fa_i,fa_j}$ 转移了。设 $x,y$ 两点间 NC2 距离为 $dis(x,y)$，转移方程如下：

- 如果 $i$ 不是 $j$ 的祖先：$f_{i,j}$ 可以与 $\max\{f_{fa_i,j},dis(i,j)\}$ 取 min。
- 如果 $j$ 不是 $i$ 的祖先，$f_{i,j}$ 可以与 $\max\{f_{i,fa_j},dis(i,j)\}$ 取 min。
- 如果 $i$ 不是 $j$ 的祖先，且 $j$ 不是 $i$ 的祖先，$f_{i,j}$ 可以与 $\max\{f_{fa_i,fa_j},dis(i,j)\}$ 取 min。

如果 $i$ 是 $j$ 的祖先，说明 $i$ 不能再往上走了，否则就会走出原来的活动路径，$j$ 是 $i$ 的祖先同理。

但是 dp 显然是有顺序的，一个点的祖先显然得比它本身先 dp 到。所以按照 dfs 序 dp 即可。（dfs 序就是 dfs 过程中进入每个点的先后顺序。）

树上两点间最短距离的长度、是否存在祖先关系都可以通过 dfs 处理。

时间复杂度 $O(n^2\log n+t)$。

细节比较多，可以看代码。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#define int long long
using namespace std;
int n,t;
int xx[1010],yy[1010];
int dis(int x,int y){
    return (xx[x]-xx[y])*(xx[x]-xx[y])+(yy[x]-yy[y])*(yy[x]-yy[y]);
}
vector<int>v[1010];
int dfn[1010],cur,pos[1010],fa[1010];
void dfs(int x,int last)
{
    dfn[++cur]=x,pos[x]=cur,fa[x]=last;
    for(auto y:v[x])
        if(y!=last)dfs(y,x);
}
int d[1010][1010];
void dfs2(int s,int x,int last)
{
    for(auto y:v[x])
        if(y!=last)
        {
            d[s][y]=d[s][x]+dis(x,y);
            dfs2(s,y,x);
        }
}
bool isfa[1010][1010];
void dfs3(int s,int x)
{
    isfa[s][x]=1;
    for(auto y:v[x])
        if(y!=fa[x])dfs3(s,y);
}
int f[1010][1010];
struct nodepair{int x,y;int d;}a[1000010],ans[100010];
int cur2;
bool cmp(const nodepair &x,const nodepair &y){
    return x.d<y.d;
}
bool operator<(const nodepair &x,const nodepair &y){
    if(x.x==1e9)return 0;
    if(y.x==1e9)return 1;
    if(d[x.x][x.y]!=d[y.x][y.y])
        return d[x.x][x.y]>d[y.x][y.y];
    if(x.x!=y.x)return x.x<y.x;
    return x.y<y.y;
}
struct query{int x,id;}q[100010];
bool operator<(const query &x,const query &y){
    return x.x<y.x;
}
signed main()
{
    cin>>n>>t;
    for(int i=1;i<=n;i++)cin>>xx[i]>>yy[i];
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1;i<=t;i++)
    {
        cin>>q[i].x;
        q[i].id=i;
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)
    {
        dfs2(i,i,0);
        dfs3(i,i);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            int ii=dfn[i],jj=dfn[j];
            if(ii!=jj)
            {
                f[i][j]=9e18;
                if(!isfa[ii][jj])f[i][j]=min(f[i][j],max(f[pos[fa[ii]]][j],dis(ii,jj)));
                if(!isfa[jj][ii])f[i][j]=min(f[i][j],max(f[i][pos[fa[jj]]],dis(ii,jj)));
                if(!isfa[ii][jj]&&!isfa[jj][ii])f[i][j]=min(f[i][j],max(f[pos[fa[ii]]][pos[fa[jj]]],dis(ii,jj)));
            }
        }
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            a[++cur2]=(nodepair){i,j,f[pos[i]][pos[j]]};
    sort(a+1,a+cur2+1,cmp);
    sort(q+1,q+t+1);
    int now=0;
    nodepair minn={(int)1e9,(int)1e9,0};
    for(int i=1;i<=t;i++)
    {
        while(now<cur2&&a[now+1].d<=q[i].x)minn=min(minn,a[++now]);
        ans[q[i].id]=minn;
    }
    for(int i=1;i<=t;i++)cout<<ans[i].x<<" "<<ans[i].y<<endl;
    return 0;
}
```

---

