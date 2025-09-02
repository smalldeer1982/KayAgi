# [ICPC 2021 Nanjing R] Paimon's Tree

## 题目描述

# Paimon's Tree

## Translation


派蒙在她的左口袋中找到了一颗有 $(n+1)$ 个白色节点的树。一颗有 $(n+1)$ 个节点的树是一个有 $n$ 条边的无向连通图。

派蒙会给你一个长度为 $n$ 的整数序列 $a_1,a_2,...,a_n$ 。我们首先需要选择这棵树中的一个节点并将它涂黑。接下来进行以下操作 $n$ 次。

> 在第 $i$ 次操作中，我们选择一个与一个黑色节点 $y_i$ 直连的白色节点 $x_i$ ，将这条边的权值设为 $a_i$ ，并且将节点 $x_i$ 涂黑。

进行上述的 $n$ 次操作后，我们会得到一棵每条边都有权值的树。

在最优的选择节点策略下，这颗树的直径最大是多少？一棵树的直径是这棵树中的最长简单路径的长度。一条简单路径的长度是这条路径中所有边的权值之和。

## 说明/提示

* $1\le T\le 5\times 10^3$
* $1\le n\le 150$
* $1\le a_i\le 10^9$
* $1\le u_i,v_i\le n+1$
* 保证每个样例中最多有 $10$ 组测试数据满足 $n>20$ 。

## 样例 #1

### 输入

```
2
5
1 7 3 5 4
1 3
2 3
3 4
4 5
4 6
1
1000000000
1 2
```

### 输出

```
16
1000000000
```

# 题解

## 作者：Sampson_YW (赞：5)

不好意思，我应该声明一下这个做法不是正解的（我不会证明/证伪复杂度）。[看见有人被误导了](https://www.luogu.com.cn/discuss/757183)。。

枚举直径端点 $(x,y)$，将 $x\to y$ 这条路径提取出来做区间 DP。

具体地，设 $f_{t,l,r}$ 表示用了 $a$ 序列用了前 $t$ 个数，区间 $[l,r]$ 中的边已经填好了。那么这个区间的子树里的所有点都可以用来放垃圾。

记 $s_{l,r}$ 表示区间 $[l,r]$ 去掉枚举的直径上的点后的大小，那么当 $s_{l,r}>t-(r-l)$ 时 $f_{t,l,r}$ 可以转移到 $f_{t+1,l,r}$。

还有两种转移是 $f_{t,l,r}+a_{t+1}\to f_{t+1,l-1,r}$ 和 $f_{t,l,r}+a_{t+1}\to f_{t+1,l,r+1}$，表示区间向左/向右扩展。

这样是 $O(n^5)$ 的，但是注意到直径端点只需要枚举叶子，再对 $s$ 数组相同的记忆化一下就可以过了。

[code](https://www.luogu.com.cn/paste/flc34t6k)

---

## 作者：sunzz3183 (赞：4)

# [ICPC2021 Nanjing R] Paimon's Tree

## 题意

给定一棵 $n+1$ 个点的树，和一个长度为 $n$ 的序列 $a$，现在你需要任选一个点，从这个点开始扩大连通块（即每次选一个与连通块相连的点将它加入连通块），然后以扩大顺序给边赋权值，输出能得到的最大**直径**。

## 分析

容易想到动态规划。

直接想不太好像，我们换一种思路：

如果钦定一条路径 $(u,v)$ 作为直径，应该怎么动态规划？

发现一条路径就是一个区间，可以直接跑区间动态规划。

设 $f_{l,r,k}$ 表示现在区间 $[l,r]$ 被加入连通块，已经赋值了 $k$ 次时的答案。

转移时考虑第 $k+1$ 次是否在区间上，每次转移有两种选择：

1. 使区间左边或右边长度增加，可转移到 $f_{l-1,r,k+1},f_{l,r+1,k+1}$。

2. 将区间相连的冗余边赋值，可转移到 $f_{l,r,k+1}$。

因为冗余数量有限，所以 $k$ 有上界 $sum$，发现得知 $l,r$ 后可以直接求出来，如下图：

![](https://cdn.jsdelivr.net/gh/sunzz3183/szzphoto@img/img/202402052017085.png)

既可以总数减去区间两端点多出的部分，也可以每次增加的时候把多出的部分（橙色圈部分）和新加边的加上，这里作者选用的是后者。

这种做法可以推广到树上，做树上的“类区间”动态规划。

但是有个问题，在确定路径的时候，我们知道下一步要去哪里，所以我们不会将要去的地方算作冗余部分（上图橙色圈），但是树上就不一定了，这里有个简单的处理方法：将区间 $[l,r]$ 换成开区间 $(l,r)$，这样就好转移了，但又多了点细节，状态还要记录此时是否将端点选上了。

设状态 $f_{l,r,k,0/1,0/1}$ 表示现在 $l\sim r$ 被加入连通块，已经赋值了 $k$ 次，左端点为闭或开，右端点为闭或开时的答案。

转移依旧要考虑端点：

- 选冗余节点：

$$ f_{x,y,k+1,0/1,0/1}\gets f_{x,y,k,0/1,0/1} $$

- 选左右端点：

$$ f_{x,y,k+1,1,0/1}\gets f_{x,y,k,0,0/1}+a_{k+1},f_{x,y,k+1,0/1,1}\gets f_{x,y,k,0/1,0}+a_{k+1} $$

- 向左右拓展：

$$ f_{z,y,k+1,0,0/1}\gets f_{x,y,k,0,0/1}+a_{k+1},f_{x,y,k+1,0/1,0}\gets f_{x,y,k,0/1,0}+a_{k+1} $$

同时注意上述三个的顺序，具体看代码。

然后一些零碎的东西：

转移的顺序，这个不好搞，作者采用了一个比较笨的方法：暴力搜索出每一条路径同时记录 $sum$（见上文）和 $len$（路径长度），然后按 $len$ 从小到大排序，按 $len$ 大小枚举区间。

## 代码

```cpp
#include<bits/stdc++.h>
#define fs first
#define sc second
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=153;
struct edge{
    int nxt,v;
}ed[N<<1];
int en,first[N];
void add(int u,int v){
    ed[++en]={first[u],v};
    first[u]=en;
}
int n,a[N],siz[N][N],f[N][N][N][2][2];
void init(int u,int fa){
    siz[u][u]=1;
    for(int i=first[u];i;i=ed[i].nxt)
        if(ed[i].v!=fa)
            init(ed[i].v,u),siz[u][ed[i].v]=siz[ed[i].v][ed[i].v],siz[u][u]+=siz[ed[i].v][ed[i].v];
    siz[u][fa]=n+1-siz[u][u];
}
struct node{
    int x,y,fx,fy,sum;
    bool operator <(const node &a)const{
        if(a.x>x)return 1;
        else if(a.y>y)return 1;
        else return 0;
    }
};
vector<pair<int,node>>q;
void dfs(int x,int fx,int y,int fy,int len,int sum){
    if(len>1)q.push_back({len,{x,y,fx,fy,sum}});
    if(len==2)f[x][y][0][0][0]=0;
    for(int i=first[x];i;i=ed[i].nxt)
        if(ed[i].v!=fx)
            dfs(ed[i].v,x,y,fy,len+1,sum+n-siz[x][fx]-siz[x][ed[i].v]+(len>1));
}
void bfs(){
    for(auto IT:q){
        node it=IT.sc;
        int x=it.x,y=it.y,fx=it.fx,fy=it.fy,sum=it.sum;
        for(int k=0;k<n&&k<sum;k++)//拓展冗余边，可以无限消除，所以 k 从小到大转移，类似于完全背包
            f[x][y][k+1][0][0]=max(f[x][y][k+1][0][0],f[x][y][k][0][0]);
        for(int k=0;k<n;k++)
            f[x][y][k+1][1][0]=max(f[x][y][k+1][1][0],f[x][y][k][0][0]+a[k+1]),//[封口
            f[x][y][k+1][0][1]=max(f[x][y][k+1][0][1],f[x][y][k][0][0]+a[k+1]);//]封口
        for(int k=0;k<n&&k<sum+n+1-siz[x][fx];k++)//处理冗余边
            f[x][y][k+1][1][0]=max(f[x][y][k+1][1][0],f[x][y][k][1][0]);
        for(int k=0;k<n&&k<sum+n+1-siz[y][fy];k++)//处理冗余边
            f[x][y][k+1][0][1]=max(f[x][y][k+1][0][1],f[x][y][k][0][1]);
        for(int k=0;k<n;k++)
            f[x][y][k+1][1][1]=max(f[x][y][k+1][1][1],f[x][y][k][1][0]+a[k+1]),//[]封口
            f[x][y][k+1][1][1]=max(f[x][y][k+1][1][1],f[x][y][k][0][1]+a[k+1]);
        for(int k=0;k<n&&k<sum+n+2-siz[x][fx]+n-siz[y][fy];k++)//处理冗余边
            f[x][y][k+1][1][1]=max(f[x][y][k+1][1][1],f[x][y][k][1][1]);
        for(int i=first[y];i;i=ed[i].nxt)
            if(ed[i].v!=fy)
                for(int k=0;k<n;k++)
                    f[x][ed[i].v][k+1][0][0]=max(f[x][ed[i].v][k+1][0][0],f[x][y][k][0][0]+a[k+1]),//()扩展
                    f[x][ed[i].v][k+1][1][0]=max(f[x][ed[i].v][k+1][1][0],f[x][y][k][1][0]+a[k+1]);//[)扩展
        for(int i=first[x];i;i=ed[i].nxt)
            if(ed[i].v!=fx)
                for(int k=0;k<n;k++)
                    f[ed[i].v][y][k+1][0][0]=max(f[ed[i].v][y][k+1][0][0],f[x][y][k][0][0]+a[k+1]),//()扩展
                    f[ed[i].v][y][k+1][0][1]=max(f[ed[i].v][y][k+1][0][1],f[x][y][k][0][1]+a[k+1]);//(]扩展
    }
}
void Main(){
    n=read();en=0;
    for(int i=1;i<=n+1;i++)first[i]=0;
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++){
        int u=read(),v=read();
        add(u,v);add(v,u);
    }
    if(n==1)return printf("%lld\n",a[1]),void();
    init(1,0);
    for(int u=1;u<=n+1;u++)
        for(int i=first[u];i;i=ed[i].nxt)
            dfs(ed[i].v,u,u,ed[i].v,1,0);
    sort(q.begin(),q.end(),[](pair<int,node>a,pair<int,node>b){return a.fs<b.fs;});
    bfs();q.clear();
    int ans=0;
    for(int u=1;u<=n+1;u++)
        for(int v=1;v<=n+1;v++){
            if(u!=v)ans=max(ans,f[u][v][n][1][1]);
            siz[u][v]=0;
            for(int k=0;k<=n;k++)
                f[u][v][k][0][0]=f[u][v][k][0][1]=f[u][v][k][1][0]=f[u][v][k][1][1]=-0x3f3f3f3f3f3f3f3f;
        }
    printf("%lld\n",ans);
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    memset(f,-0x3f,sizeof(f));
    int T=read();
    while(T--)Main();
    return 0;
}
```


---

## 作者：InoueTakina (赞：0)

一个朴素的做法是枚举路径一条路径作为直径，然后求出这条最多能填入多少。

考虑“选择一个点作为起点，然后向两侧扩展”的形式类似于区间 dp，不难以此设计一个 $\mathcal{O}(n^3)$ 的 dp：$f(l,r,k)$ 表示我把这条路径上 $[l,r]$ 之间的点都染成了黑色，$a_{1\sim k}$ 已经被填入了路径最大权值和。转移时向两边扩展并把 $a_{k+1}$ 计入权值，或者空放一个数。

注意到之所以要枚举路径再 dp，是因为我们以“空放”进行转移时，需要保证有足够的边给我们空放，而如果某一段点 $u$ 在后面还要向一个 $v$ 扩展，那么 $u$ 上可以空放的边数是有变化的。

解决这个问题是简单的，我们直接多计入 $p_1,p_2$，表示当前路径的两端是否扩展，实现上若某一段需要扩展，我们要记录其具体的扩展方向，注意到我们只需要记录扩展的下一个节点是什么即可，另外需要预处理 $(u,v,p_1,p_2)$ 对应的路径上的可“空放”位置个数，这是易于实现的。

使用记忆化搜索将更易于实现。

综合时间复杂度 $\mathcal{O}(n^3)$。

---

