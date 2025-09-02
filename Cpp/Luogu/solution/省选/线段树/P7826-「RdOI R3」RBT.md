# 「RdOI R3」RBT

## 题目描述

你有一棵以 $1$ 为根，编号为 $1\sim n$ 的有根树，第 $i$ 号节点上有一个整数权值 $a_i$。同时每一个点都被染上了红色或蓝色。初始所有点全是红色点。你需要维护这棵树，进行 $q$ 次操作。操作分若干种，具体格式如下：

- `1 x v` ：使 $x$ 节点的子树中的每个节点的权值增加 $v$ 并对 $p$ 取模。
- `2 x v`：将 $a_x$ 赋值为 $v$。**注意不是赋值整棵子树。**
- `3 x`：将 $x$ 号点染成蓝色，设 $j$ 节点为 $x$ 号节点在它的**红色**兄弟节点中**编号**（不是权值）排名的前驱，将 $x$ 节点连接父亲的边删除。然后将 $x$ 节点作为儿子节点接到 $j$ 节点上，如果 $x$ 节点没有红色兄弟节点或 $x$ 节点的红色兄弟节点的编号均比 $x$ 大则什么都不做。
- `4 x`：设 $S$ 为 $x$ 的子树中的节点的权值中出现次数为奇数的数组成的集合。输出集合中的每个数的 $k$ 次方之和，对 $998244353$ 取模。即 $(\sum_{z\in S}z^k)\bmod 998244353$。

特别的，数据保证每个点只能被执行 $3$ 操作至多 $1$ 次。也就是说不会出现对一个蓝色点进行 $3$ 操作的情况。

## 说明/提示

### 样例解释

#### 样例 \#1

- 询问 `4 1`，子树中点的权值分别为 $3,2,1,2,1,3,2,1,3,4$，$S$ 集合为 $\{1,2,3,4\}$，故答案为 $10$。
- 修改 `1 3 1`，树中各点权值变为 $3,2,2,2,1,4,2,1,3,4$。
- 修改 `2 1 2`，树中各点权值变为 $2,2,2,2,1,4,2,1,3,4$。
- 询问 `4 1`，子树中点的权值分别为 $2,2,2,2,1,4,2,1,3,4$，$S$ 集合为 $\{2,3\}$，故答案为 $5$。
- 询问 `4 3`，子树中点的编号为 $3,6$，权值分别为 $2,4$，$S$ 集合为 $\{2,4\}$，故答案为 $6$。
- 询问 `4 6`，由于这是一个叶子节点，子树中点的权值为它本身的权值 $4$，$S$ 集合为 $\{4\}$，故答案为 $4$。
- 修改 `1 4 1`，树中各点权值变为 $2,2,2,3,1,4,2,1,3,4$。
- 修改 `3 7`，将 $7$ 涂成蓝色，删除树中的边 $2\leftrightarrow 7$，并将 $7$ 作为儿子节点接到 $5$ 上。
- 修改  `1 5 1`，树中各点权值变为 $2,2,2,3,2,4,3,2,4,5$。
- 询问 `4 5`，子树中各点编号为 $5,7,8,9,10$，权值分别为 $2,3,2,4,5$，$S$ 集合为 $\{3,4,5\}$，故答案为 $12$。

---

### 数据范围

**本题采用捆绑测试。**

对于所有数据，$1\le x\le n\le 10^5$，$1\le q \le 10^5$，$0 \le a_i, v < p \le 500$，$p\ne 0$，$0\le k \le 10^9$。

| subtask | 分值 | 特殊限制                                    |
| ------- | ---- | ------------------------------------------- |
| $1$     | $10$ | $op,a_i,x,v$ 和初始树的形态均等概率随机生成 |
| $2$     | $90$ | 无                                          |

## 样例 #1

### 输入

```
10 10 500 1
3 2 1 2 1 3 2 1 3 4
1 4
7 8
3 6
8 10
2 3
2 5
8 9
7 2
2 1
4 1
1 3 1
2 1 2
4 1
4 3
4 6
1 4 1
3 7
1 5 1
4 5
```

### 输出

```
10
5
6
4
12
```

# 题解

## 作者：eastcloud (赞：0)

官方题解似乎是带根号的，这里提供一个小清新 polylog 做法。

操作 3 一看就很抽象，先考虑不带操作 3 怎么做。由于 $k$ 可能很大，因此通过已知信息直接拆二项式维护 1 操作是很困难的，但是这题的模数很小，启发我们开一个桶记录目前拥有的数的状况。

想到这步问题就迎刃而解了，我们把树拍扁成 dfs 序，在线段树上维护这些操作，每个节点存一个大小为模数的 bitset，由于询问很特殊，子树信息合并就是异或，操作 1 就是区间循环移位，操作 2 就是单点修改，用线段树维护是简单的。

那带上操作 3 呢？由于每个点只会被过继到他的兄弟节点，不难发现每次操作后只有他的兄弟的子树集合发生了变化。我们先把树上所有边都拆开，考虑每次操作建一个虚点刻画上述性质。

类似并查集，我们每次相当于用虚点把两个点合并并向两个点连边，最后再把树结构补全，父亲只用向孩子中所有没被合并或者最终合并到的虚点连边即可。

这样重构完不难发现操作 3 就变成了把一个点的代表点改变，其他操作形式不变，于是可以简单维护。时间复杂度 $O(\frac{np\log n}{w})$。

```cpp

#include<bits/stdc++.h>

#define ll long long
#define pi pair<int,int>
#define vi vector<int>
#define cpy(x,y,s) memcpy(x,y,sizeof(x[0])*(s))
#define mset(x,v,s) memset(x,v,sizeof(x[0])*(s))
#define all(x) begin(x),end(x)
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ary array
#define eb emplace_back
#define IL inline
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Fol(i,k,j) for(int i=(k);i>=(j);i--)

using namespace std;

#define N 200005
#define P 998244353

int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')f=(ch=='-'?-1:f),ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x/10)write(x/10);
    putchar(x%10+'0');
}

void debug(auto &&...x){
    ((cerr<<x<<' '),...);
    cerr<<'\n';
}

bool Mbe;

int id[N],a[N],tot;
set<int> s[N];
basic_string<int> e[N],g[N];
int fat[N],cnt,L[N],R[N],n,mod,f[N],pw[N],ID[N];
struct Node{
    int opt,x,v;
    Node(int opt=0,int x=0,int v=0):opt(opt),x(x),v(v){}
}Q[N];

int qp(int x,int y){int ans=1;while(y){if(y&1)ans=ans*1ll*x%P;x=x*1ll*x%P;y>>=1;}return ans;}

void dfs(int x,int fa){
    fat[x]=fa;
    for(auto v:e[x]){
        if(v==fa)continue;
        s[x].insert(v);dfs(v,x);
    }
}
void dfs2(int x){
    L[x]=R[x]=++tot;ID[tot]=x;
    for(auto v:g[x])dfs2(v),R[x]=R[v];
}

void opr(bitset<501> &f,int x){
    f=(f>>(mod-x))|((f<<(501-(mod-x)))>>(501-mod));
}

struct seg{
    int ls[N<<1],tot,rs[N<<1],tg[N<<1];bitset<501> v[N<<1];
    void build(int &x,int l=1,int r=cnt){
        x=++tot;if(l==r){if(ID[l]<=n)v[x].set(a[ID[l]]);return;}int mid=(l+r)>>1;
        build(ls[x],l,mid);build(rs[x],mid+1,r);v[x]=v[ls[x]]^v[rs[x]];
    }
    void ps(int x,int val){if(val)opr(v[x],val);tg[x]+=val;tg[x]%=mod;}
    void pd(int x){ps(ls[x],tg[x]);ps(rs[x],tg[x]);tg[x]=0;}
    bitset<501> ask(int x,int L,int R,int l=1,int r=cnt){
        if(l>=L && r<=R)return v[x];int mid=(l+r)>>1;bitset<501> res;pd(x);
        if(L<=mid)res^=ask(ls[x],L,R,l,mid);
        if(R>mid)res^=ask(rs[x],L,R,mid+1,r);return res;
    }
    void chg(int x,int p,int now,int l=1,int r=cnt){
        if(l==r){v[x].reset(),v[x].set(now,1);return;}int mid=(l+r)>>1;pd(x);
        (p<=mid)?chg(ls[x],p,now,l,mid):chg(rs[x],p,now,mid+1,r);v[x]=v[ls[x]]^v[rs[x]];
    }
    void upd(int x,int L,int R,int b,int l=1,int r=cnt){
        if(l>=L && r<=R)return ps(x,b);int mid=(l+r)>>1;pd(x);
        if(L<=mid)upd(ls[x],L,R,b,l,mid);
        if(R>mid)upd(rs[x],L,R,b,mid+1,r);v[x]=v[ls[x]]^v[rs[x]];
    }
}T;

bool Med;

int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.ans","w",stdout);
    #endif
 
    n=read();int q=read();mod=read();int k=read();cnt=n;
    For(i,1,n)a[i]=read(),id[i]=i;
    For(i,1,n-1){
        int u=read(),v=read();
        e[u]+=v;e[v]+=u;
    }
    dfs(1,0);
    For(i,1,q){
        Q[i].opt=read();Q[i].x=read();
        int x=Q[i].x;
        if(Q[i].opt==1 || Q[i].opt==2)Q[i].v=read();
        if(Q[i].opt==3){
            if(x==1 || !s[fat[x]].size())continue;
            auto it=s[fat[x]].lower_bound(x);
            if(it!=s[fat[x]].begin()){
                Q[i].v=(*prev(it));
                cnt++;f[id[Q[i].v]]=cnt;
                g[cnt]+=id[Q[i].v];g[cnt]+=id[x];
                id[Q[i].v]=cnt;id[x]=0;
                s[fat[x]].erase(x);
            }
        }
    }
    For(i,1,n){
        for(auto v:e[i]){
            if(v==fat[i] || !id[v])continue;
            g[i]+=id[v];
        }
    }
    dfs2(1);
    int rt;T.build(rt);
    For(i,0,mod-1)pw[i]=qp(i,k);
    For(i,1,n)id[i]=i;
    For(i,1,q){
        int x=Q[i].x;
        if(Q[i].opt==1)T.upd(1,L[id[x]],R[id[x]],Q[i].v);
        else if(Q[i].opt==2)T.chg(1,L[x],Q[i].v);
        else if(Q[i].opt==3)id[Q[i].v]=f[id[Q[i].v]];
        else{
            bitset<501> res=T.ask(1,L[id[x]],R[id[x]]);
            ll ans=0;
            For(j,0,mod-1)if(res[j])ans+=pw[j];
            write(ans%P);putchar('\n');
        }
    }
    return 0;
}
```

---

