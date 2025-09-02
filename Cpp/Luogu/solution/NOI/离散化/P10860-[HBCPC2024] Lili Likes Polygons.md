# [HBCPC2024] Lili Likes Polygons

## 题目描述

莉莉和娜娜正在莉莉家后院除草。她们反复选择矩形区域，并移除其中的所有草坪。

后院可以被视为一个二维网格，每个方格表示一个单位面积。她们共进行了 $n$ 次操作。在第 $i$ 次操作中，她们选择了一个矩形的左、下、右、上的边界，分别表示为 $l_i, b_i, r_i, t_i$，并使用割草机清除该矩形内的所有方格。**注意，这些矩形可能会相互重叠。**

用 $[l_i, r_i] \times [b_i, t_i]$ 表示一个矩形。

以下是一个例子，如图所示。她们选择了 $2$ 个矩形，第一个矩形是 $[1, 5] \times [2, 3]$，第二个矩形是 $[2, 3] \times [1, 4]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/nb9g0n5i.png)

经过 $n$ 次除草操作后，裸露区域的联合可能不连通，但所有边都是水平或垂直的。因此，联合区域变成了一个或多个直角多边形，其中一些可能包含多边形孔洞。此外，在某些孔洞内部可能会有裸露的方格。更多细节和图示请参见示例输入。

现在，她们想通过在裸露的方格上种植植物来恢复土地。莉莉喜欢多边形，特别是矩形。因此，她们想选择若干个矩形，这些矩形之间不重叠，并且能够完全覆盖所有的裸露方格。然后，她们将在选择的不同矩形中种植不同的植物。

例如，下面是上述情况的一个可行的矩形选择：选择 $[1, 1] \times [2, 3]$、$[2, 3] \times [1, 4]$ 和 $[4, 5] \times [2, 3]$。

玩了一会儿，这两个小女孩已经累了，所以她们想知道覆盖所有裸露方格的最小不重叠矩形数量。

## 说明/提示

对于第一个例子，最优选择是 $[1, 1] \times [1, 3]$、$[2, 1] \times [2, 1]$、$[2, 3] \times [2, 3]$ 和 $[3, 1] \times [3, 3]$。

对于第二个例子，最优选择是 $[1, 1] \times [100, 100]$ 和 $[1, 501] \times [100, 600]$。

对于第三个例子，最优选择是 $[1, 1] \times [4, 1]$、$[1, 4] \times [5, 4]$、$[1, 2] \times [1, 3]$、$[4, 2] \times [4, 3]$ 和 $[4, 5] \times [4, 5]$。

对于第四个例子，裸露区域如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/uun9l7e6.png)

翻译者：[Immunoglobules](https://www.luogu.com.cn/user/1066251)

## 样例 #1

### 输入

```
8
1 1 1 1
1 2 1 2
1 3 1 3
2 1 2 1
2 3 2 3
3 1 3 1
3 2 3 2
3 3 3 3```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1 1 100 100
1 501 100 600```

### 输出

```
2```

## 样例 #3

### 输入

```
4
1 1 4 1
1 4 5 4
1 1 1 4
4 1 4 5```

### 输出

```
5```

## 样例 #4

### 输入

```
9
1 1 9 1
1 1 1 9
1 9 9 9
9 1 9 9
3 3 7 3
3 3 3 7
3 7 7 7
7 3 7 7
5 5 5 5```

### 输出

```
9```

# 题解

## 作者：dspt (赞：9)

本题来源是 [Gym 105139C](https://codeforces.com/gym/105139/problem/C)，[官方题解链接](https://codeforces.com/gym/105139/attachments/download/25287/Sol_ICPC_hubei_24.pdf)。这是本场的防 AK 题，当然也是道思路很巧妙的网络流建模问题。

我们考虑对多边形 $P$ 求出它**最少不交矩形覆盖**，那么答案就是图上所有多边形的最少不交矩形覆盖和。

约定：记 ∟ 表示直角，2∟表示平角，3∟ 表示凹角（270°的角）。

引理 1：分割线与原图形的边不重合。证明显然。

引理 2：每条分割线的两个端点至少有一个是 3∟，并且没有一个是 ∟。

> 如果端点是 ∟，那么必然与原图形的边重合，不符合结论 1。那么剩下两个端点的情况就是：两个 2∟、一个 3∟ 一个 2∟、两个 3∟。
>
> 如果两个端点均为 2∟，容易发现这条分割线没有意义。即对于任意一组包含这条分割线的合法划分，去掉这条分割线仍然合法。除掉这种情况，剩下的情况中至少有一个端点为 3∟。

引理 3：任意两条分割线，要么不交，要么交于端点。

> 考虑平行于垂直两种情况。平行必然不交，垂直的话，两条分割线构成了一个十字形，可以发现这个十字形的四边必然存在一边是毫无必要的，把那条边去掉，答案不会更劣。

假设我们已经得知了一组合法划分，我们怎么计算出划分了有多少个矩形呢？我们可以使用**内角和**计算。划分后图形的内角和除以 4∟ 就是矩形数量。

但是我们在划分的过程中会让原图形的内角和改变，具体而言：

1. 分割 2∟：内角和增大了 2∟
2. 分割 3∟ 一次：内角和减小了 2∟
3. 分割 3∟ 两次：内角和不变

考虑前面所说的分割线的两种情况：

1. 分割 2∟ 和 3∟，内角和不受影响。
2. 分割 3∟ 和 3∟，内角和减少了 4∟。

值得注意的是，3∟ 被分割后会变成 2∟。

我们称端点为 3∟ 的分割线是**好分割线**。

引理 4：任意合法分割内角和减少量等于不相交的好分割线条数乘以 4∟。

> 合法方案的必要条件：所有 3∟ 都至少被分割一次。
>
> 如果 3∟ 被好分割线分割，那么必然可以带来 2∟ 的贡献。那么这些不相交好分割线每条就会带来 4∟ 的贡献。对于其它没有被好分割线分割的 3∟，从它连出去的分割线必然无法分割另一个 3∟，只能分割 2∟。而这些分割线不会对答案产生影响。

---

于是做法就显而易见了：离散化，求出多边形的内角和。

对于每个 3∟，它在水平方向和竖直方向各至多有一个 3∟ 与其匹配，换言之，每个 3∟ 的水平 / 竖直好分割线都只有一条。我们把这些好分割线看作点，经过公共点的水平好分割线与竖直好分割线连边（只能选一条），可以建成一张二分图，不相交的好分割线条数 = **最大独立集** = 二分图总点数 - 最大匹配。

这张二分图的点数是原多边形的点数级别的，需要用最大流进行匹配。最后用原多边形内角和除以 4∟ 再减去最大独立集就是答案。

---

## 作者：是青白呀 (赞：2)

首先，最小矩形剖分的分割线必定过至少一个凹角，且不过凸角、不与已有边重合。

我们考虑用分割后矩形的内角和计算矩形剖分的数目。先计算原图形的内角和，然后考虑分割对于内角和的影响。

- 对于分割两个凹角的分割线，它会将内角和减少 $360^{\circ}$。
- 对于分割一个凹角和一个平角的分割线，它不影响内角和。

需要注意的是，一个凹角被分割一次后就会变成一个平角和一个凸角，不再产生新的减少量。因此我们找出所有的凹角、以及凹角之间可能存在的分割线，将凹角作为点、分割线作为边建图。不难发现一个凹角最多对应两个分割线，也就是说连出来的图仅包含偶环和链，是一个二分图。

我们要求每个凹点只给至多一个分割线作贡献，因此减少的次数就是这个二分图的最大匹配数，跑网络流即可。

注意到矩形和角的数目都很小，所以可以离散化坐标，然后暴力覆盖求内角和；也可以暴力找凹角和凹角之间的分割线。细节较多。

设 $k$ 表示原始多边形的角数。最终复杂度 $O(n(n+k)+k\sqrt k)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define qingbai 666
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=3005,M=6,S=(1<<15)+5,inf=1e9+7,mo=998244353;
const double eps=1e-8;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m;
int lshx[N],cntx,cnty,lshy[N];
struct oper{
    int l,r,op;
};
vector<oper>op[N];
struct rect{
    int l,r,b,t;
}rec[N];
int vis[N][N];
struct inter{
    int x,y,tp;
}itr[N];
int cnta;
int dx[8]={-1,-1,0,1,1,1,0,-1},dy[8]={0,1,1,1,0,-1,-1,-1};
struct edge{
    int to,nxt,val;
}e[10*N];
int fir[N],np=1,st[N];//flow
void add(int x,int y,int w){
    e[++np]=(edge){y,fir[x],w};
    fir[x]=np;
}
int co[N];
bool exi[N][N];//邻接矩阵
int id[N][N];
void checkadd(int i,int dir){
    if(dir==1){
        repp(x,itr[i].x-1,1){
            int y=itr[i].y;
            if(id[x][y]){
                int nid=id[x][y];
                if(itr[nid].tp==2||itr[nid].tp==3)exi[i][nid]=1;
                break;
            }
            if(!vis[x][y])break;
        }
    }
    else if(dir==2){
        rep(y,itr[i].y+1,cnty){
            int x=itr[i].x;
            if(id[x][y]){
                int nid=id[x][y];
                if(itr[nid].tp==3||itr[nid].tp==4)exi[i][nid]=1;
                break;
            }
            if(!vis[x][y])break;
        }
    }
    else if(dir==3){
        rep(x,itr[i].x+1,cntx){
            int y=itr[i].y;
            if(id[x][y]){
                int nid=id[x][y];
                if(itr[nid].tp==1||itr[nid].tp==4)exi[i][nid]=1;
                break;
            }
            if(!vis[x][y])break;
        }
    }
    else{
        repp(y,itr[i].y-1,1){
            int x=itr[i].x;
            if(id[x][y]){
                int nid=id[x][y];
                if(itr[nid].tp==1||itr[nid].tp==2)exi[i][nid]=1;
                break;
            }
            if(!vis[x][y])break;
        }
    }
}
void dfsc(int x){
    rep(i,1,cnta){
        if(!exi[x][i])continue;
        if(co[i])continue;
        co[i]=co[x]==2?1:2;
        dfsc(i);
    }
}
int dep[N];
bool bfs(){
    rep(i,0,cnta+1)
        dep[i]=0;
    dep[0]=1;
    queue<int>q;
    q.push(0);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        st[x]=fir[x];
        for(int i=fir[x];i;i=e[i].nxt){
            int j=e[i].to;
            if(dep[j]||!e[i].val)continue;
            dep[j]=dep[x]+1,q.push(j);
        }
    }
    return dep[cnta+1]!=0;
}
int dinic(int x,int num){
    if(x==cnta+1)return num;
    if(!num)return 0;
    int lst=num;
    for(int i=st[x];i;i=e[i].nxt){
        int j=e[i].to;
        st[x]=i;
        if(!e[i].val||dep[j]!=dep[x]+1)continue;
        int gnum=dinic(j,min(e[i].val,lst));
        e[i].val-=gnum,e[i^1].val+=gnum,lst-=gnum;
        if(!lst)break;
    }
    return num-lst;
}
signed main(){
    read(n);
    rep(i,1,n){
        read(rec[i].l),read(rec[i].b),read(rec[i].r),read(rec[i].t);//修改了一下输入，长方形i轴范围(l,r),j轴范围(b,t)
        lshx[++cntx]=rec[i].l-1,lshx[++cntx]=rec[i].l,lshx[++cntx]=rec[i].l+1;
        lshx[++cntx]=rec[i].r-1,lshx[++cntx]=rec[i].r,lshx[++cntx]=rec[i].r+1;
        lshy[++cnty]=rec[i].b-1,lshy[++cnty]=rec[i].b,lshy[++cnty]=rec[i].b+1;
        lshy[++cnty]=rec[i].t-1,lshy[++cnty]=rec[i].t,lshy[++cnty]=rec[i].t+1;
    }
    sort(lshx+1,lshx+cntx+1),sort(lshy+1,lshy+cnty+1);
    cntx=unique(lshx+1,lshx+cntx+1)-lshx-1;
    cnty=unique(lshy+1,lshy+cnty+1)-lshy-1;
    rep(i,1,n){
        rec[i].l=lower_bound(lshx+1,lshx+cntx+1,rec[i].l)-lshx;
        rec[i].r=lower_bound(lshx+1,lshx+cntx+1,rec[i].r)-lshx;
        rec[i].b=lower_bound(lshy+1,lshy+cnty+1,rec[i].b)-lshy;
        rec[i].t=lower_bound(lshy+1,lshy+cnty+1,rec[i].t)-lshy;
    }
    rep(i,1,n){
        op[rec[i].l].push_back((oper){rec[i].b,rec[i].t,1});
        op[rec[i].r+1].push_back((oper){rec[i].b,rec[i].t,-1});
    }
    rep(i,1,cntx){
        rep(j,1,cnty)
            vis[i][j]=vis[i-1][j];
        for(auto j:op[i]){
            int l=j.l,r=j.r,v=j.op;
            rep(k,l,r)
                vis[i][k]+=v;
        }
    }
    rep(i,1,cntx){
        rep(j,1,cnty)
            vis[i][j]=min(vis[i][j],1);
    }
    int ans=0;
    rep(i,1,cntx){
        rep(j,1,cnty){
            for(int ls=0;ls<=6;ls+=2){
                bool ok=1,ok2=1;
                rep(l,ls,ls+2){
                    int x=i+dx[l%8],y=j+dy[l%8];
                    if(x<1||y<1||x>cntx||y>cnty)ok=0;
                    else if(!(vis[x][y]^vis[i][j]))ok=0;
                    if(l==ls+1)continue;
                    if(x<1||y<1||x>cntx||y>cnty)ok2=0;
                    else if(!(vis[x][y]^vis[i][j]))ok2=0;
                }
                if(ok){
                    if(vis[i][j])ans++;
                    else{
                        ans+=3;
                        if(ls==0)itr[++cnta]={i,j+1,1},id[i][j+1]=cnta;
                        if(ls==2)itr[++cnta]={i+1,j+1,2},id[i+1][j+1]=cnta;
                        if(ls==4)itr[++cnta]={i+1,j,3},id[i+1][j]=cnta;
                        if(ls==6)itr[++cnta]={i,j,4},id[i][j]=cnta;
                    }
                }
                else if(ok2&&vis[i][j])ans++;
            }
        }
    }
    rep(i,1,cnta){
        if(itr[i].tp==1)checkadd(i,1),checkadd(i,2);
        else if(itr[i].tp==2)checkadd(i,2),checkadd(i,3);
        else if(itr[i].tp==3)checkadd(i,3),checkadd(i,4);
        else checkadd(i,4),checkadd(i,1);
    }
    rep(i,1,cnta)
        if(!co[i])co[i]=1,dfsc(i);
    rep(i,1,cnta){
        if(co[i]==1)add(0,i,1),add(i,0,0);
        else add(i,cnta+1,1),add(cnta+1,i,0);
    }
    rep(i,1,cnta){
        if(co[i]==2)continue;
        rep(j,1,cnta){
            if(co[j]==1)continue;
            if(!exi[i][j])continue;
            add(i,j,1),add(j,i,0);
        }
    }
    int resm=0;
    while(bfs())
        resm+=dinic(0,inf);
    printf("%d\n",(ans-4*resm)/4);
    return 0;
}
```

---

