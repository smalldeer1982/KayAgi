# 「CROI · R1」浣熊的阴阳鱼

## 题目背景

> 往昔，阴阳由天地所创，孕大含深；今昔，时光为记忆所刻，随行如影。\
流水落花间，嬉闹于阴阳树的意境；沧海桑田间，铭心于阴阳忆的缤斓。\
阴鱼，阳鱼……挥翰着日月的闲情，留存着浣熊的惬意，却不复存在……\
小浣熊 CleverRaccoon 与最后一瞬阴阳，含泪而笑……

## 题目描述

一棵树的各结点都悬挂着 $1$ 条阴鱼或阳鱼（分别用 $0,1$ 表示），它们可能在某刻由于基因突变互相转化。

小浣熊 CleverRaccoon 带着一只能装 $2$ 条鱼的篮筐在此树的某条链上行走。当他所在点上的鱼与某条筐内鱼的属性相反时，他会将这 $2$ 条鱼合成 $1$ 条阴阳鱼并吃下；在筐中没有满的条件下，他会将所在点上的鱼放入筐中。

现有两种操作：

1. 一个结点上的阴阳鱼发生基因突变，变为另一种类型的阴阳鱼。
2. 帮助聪明的小浣熊 CleverRaccoon 求出：当他沿着这棵树上的某条链行走时，能吃下的阴阳鱼的条数。

## 说明/提示

**数据范围**

**本题采用 Subtask 捆绑测试**。

- Subtask 0（10 points）：$n,q \leq 10$。
- Subtask 1（15 points）：$n,q \leq 2\times10^3$。
- Subtask 2（15 points）：保证树的深度小于 $10^3$。
- Subtask 3（60 points）：无特殊限制。

对于所有测试数据： $1 \leq n,q\leq 10^5$。

## 样例 #1

### 输入

```
9 3
1 1 1 0 1 1 0 0 0
1 2
2 3
3 4
3 5
1 6
6 7
7 8
7 9
2 9 4
1 9
2 4 9
```

### 输出

```
3
2```

# 题解

## 作者：yydtq (赞：13)

众所周知，本题的代码可以不到 2k，那些场上迅速过了的大多都预存了模板，我也不是说这样不行，不过即使不预存模板也能首 A，因为有一个能常数之外偏序掉树剖的数据结构：Link-Cut-Tree！

首先本题的信息具有结合律，可以看作一种矩阵，鱼框的状态只有五种，我们将一条链的信息看作从鱼框的每一种状态开始，经过这条链之后会变成什么状态，吃下了几条阴阳鱼，实现时可以将末三位表示状态：
```cpp
struct dat{
    int p[5];//0,10,20,11,21;
    dat operator*(const dat &z)const{
        return{
            ((p[0]>>3)<<3)+z.p[p[0]&7],
            ((p[1]>>3)<<3)+z.p[p[1]&7],
            ((p[2]>>3)<<3)+z.p[p[2]&7],
            ((p[3]>>3)<<3)+z.p[p[3]&7],
            ((p[4]>>3)<<3)+z.p[p[4]&7]
        };
    }
    void init(int d){
        if(d)*this={3,8,9,4,4};
        else *this={1,2,2,8,11};
    }
    void init(){*this={0,1,2,3,4};}
    void put(){
        for(int i=0;i<5;++i)
            printf("%d%c",p[i]," \n"[i==4]);
    }
}
```

而每次询问的初始状态都是 $0$，即鱼框里没有鱼，所以将链上的信息合并之后的 $p_0$ 除去末三位就是答案。

为了实现方便需要换根，可以将正的和反的信息都存下来，翻转时交换即可。

于是代码很好写：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct dat{
    int p[5];//0,10,20,11,21;
    dat operator*(const dat &z)const{
        return{
            ((p[0]>>3)<<3)+z.p[p[0]&7],
            ((p[1]>>3)<<3)+z.p[p[1]&7],
            ((p[2]>>3)<<3)+z.p[p[2]&7],
            ((p[3]>>3)<<3)+z.p[p[3]&7],
            ((p[4]>>3)<<3)+z.p[p[4]&7]
        };
    }
    void init(int d){
        if(d)*this={3,8,9,4,4};
        else *this={1,2,2,8,11};
    }
    void init(){*this={0,1,2,3,4};}
    void put(){
        for(int i=0;i<5;++i)
            printf("%d%c",p[i]," \n"[i==4]);
    }
}s1[N],s2[N],v[N];
int n,q,cl[N],rv[N],t[N][2],f[N];
#define ls t[x][0]
#define rs t[x][1]
#define tp(x) (t[f[x]][1]==x)
#define in(x) (t[f[x]][0]==x||tp(x))
void pp(int x){
    s1[x]=s2[x]=v[x];
    if(ls)s1[x]=s1[ls]*s1[x],s2[x]=s2[x]*s2[ls];
    if(rs)s1[x]=s1[x]*s1[rs],s2[x]=s2[rs]*s2[x];
}
void rev(int x){
    rv[x]^=1,swap(ls,rs);
    swap(s1[x],s2[x]);
}
void pd(int x){
    if(rv[x]){
        if(ls)rev(ls);
        if(rs)rev(rs);rv[x]=0;
    }
}
void ppd(int x){
    if(in(x))ppd(f[x]);pd(x);
}
void rot(int x){
    int y=f[x],k=tp(x),w=t[x][!k];
    t[f[w]=t[x][!k]=y][k]=w;
    if(in(y))t[f[y]][tp(y)]=x;
    f[x]=f[y],f[y]=x,pp(y);
}
void splay(int x){
    ppd(x);
    for(int y=f[x];in(x);rot(x),y=f[x])
        if(in(y))rot(tp(x)^tp(y)?x:y);pp(x);
}
void acs(int x){
    for(int y=0;x;x=f[y=x])
        splay(x),rs=y,pp(x);
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    int i,j,k,l,r,x,y;
    for(x=1;x<=n;++x)cin>>cl[x],v[x].init(cl[x]),pp(x);
    for(i=1;i<n;++i){
        cin>>x>>y;
        acs(x),splay(x),rev(x),f[x]=y;
    }
    s1[0].init(),s1[0].init();
    while(q--){
        cin>>k>>x;
        if(k==1)splay(x),v[x].init(cl[x]^=1),pp(x);
        else{
            cin>>y,acs(x),splay(x),rev(x);
            acs(y),splay(x);
            printf("%d\n",s1[x].p[0]>>3);
        }
    }return 0;
}
```

---

## 作者：lzyqwq (赞：8)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17639118.html)**

树链剖分真可爱。

**[题目链接](https://www.luogu.com.cn/problem/P9555 "题目链接")**

> - 给出 $n$ 个点的树，点有点权 $a_i(a_i\in\{0,1\})$。支持 $q$ 次操作：
>
>     - $\texttt{1 }u$，$a_u\leftarrow \lnot a_u$。
>
>     - $\texttt{2 }u\texttt{ }v$，你带着一个最大大小为 $2$ 的可重集 $S$ 从 $u$ 走到 $v$，初始 $S=\varnothing$，遇到一个点 $x$，若 $\lnot a_x\in S$，则删除 $\lnot a_x$，得分 $+1$，否则将 $a_x$ 插入 $S$。求最终的得分。
>
> - $n,q\le 10^5$。

看到树上修改和路径查询，首先想到树剖。我们发现 $|S|\le 2$，且 $S$ 内元素的顺序不影响答案，因此我们可以用一个二元组 $(i,j)(0\le i\le j\le 2)$ 记录 $S$ 的状态（$0,1$ 表示放了什么元素，$2$ 表示没有元素）。为了方便表述，将 $2$ 也认为是 $S$ 内的元素，即强制 $|S|=2$。

分析一下询问，相当于已经给定了初始状态 $S=\{a_u,2\}$。再根据树剖的思想，我们要快速查询一条重链上的信息，即快速查询那条链对应的区间的信息。考虑使用线段树维护。具体地，对于线段树上的一个节点 $x$（设对应的区间为 $[l,r]$），记 $f_{x,i,j}$ 表示从 $l$ 位置开始走，**经过 $l$ 位置后** $S=\{i,j\}$，走到 $r$ 时的得分，类似地 $g_{x,i,j}$ 表示从 $r$ 走到 $l$ 的得分。还需要记录 $LtoR_{x,i,j}$ 表示从 $l$ 位置开始走，**经过 $l$ 位置后** $S=\{i,j\}$，到达 $r$ 后 $S$ 的状态，同理还有 $RtoL_{x,i,j}$ 表示从 $r$ 到达 $l$ 后 $S$ 的状态。注意，我们强调了**初始 $S$ 是经过起点后的状态**，意味着上述的 $S$ 都**已经受起点的影响**，即**统计答案的时候不再受到起点的影响（因为已经受过了）**。类似地，强调 $LtoR$ 和 $RtoL$ 是到达端点后的状态，说明信息已经受到终点的影响，因为状态的定义里保证了它受到起点的影响，所以同时保证了统计了**完整**的信息。

考虑如何合并区间信息，我们发现需要快速计算出已经到了一个区间末尾，下一步走到另一半区间开头时，$S$ 的状态，因此还需要记录 $lc_{x},rc_{x}$ 来存储 $a_l$ 和 $a_r$。所以线段树的节点是张这样的：

```cpp
#define pii pair<int,int>
struct node{//变量名有部分不同。
    int cnt_l[3][3],cnt_r[3][3],lc,rc;//f,g,lc,rc。
    pii status_l[3][3],status_r[3][3];//LtoR,RtoL。
}seg[N<<2];
```

然后计算状态可以通过以下的函数实现（我写的比较暴力，直接枚举 $12$ 种情况分类讨论）：

```cpp
#define ppi pair<pii,int>
#define mp make_pair
ppi get_status(pii p,int x){//第二维表示得分增量。
    if(p==mp(0,0)&&!x){
        return mp(p,0);
    }
    if(p==mp(0,0)&&x){
        return mp(mp(0,2),1);
    }
    if(p==mp(0,1)&&!x){
        return mp(mp(0,2),1);
    }
    if(p==mp(0,1)&&x){
        return mp(mp(1,2),1);
    }
    if(p==mp(0,2)&&!x){
        return mp(mp(0,0),0);
    }
    if(p==mp(0,2)&&x){
        return mp(mp(2,2),1);
    }
    if(p==mp(1,1)&&!x){
        return mp(mp(1,2),1);
    }
    if(p==mp(1,1)&&x){
        return mp(mp(1,1),0);
    }
    if(p==mp(1,2)&&!x){
        return mp(mp(2,2),1);
    }
    if(p==mp(1,2)&&x){
        return mp(mp(1,1),0);
    }
    return mp(mp(x,2),0);//空集就直接放。
}
```

区间信息具体合并方法为，先从计算当前状态走到区间末尾的信息，然后计算跨过区间后的状态，以及计算跨区间这一步对得分的贡献。然后再从另一半区间，以跨区间后的状态开始走，计算得分。从当前起点走到另一个端点的状态，就是从另一半区间，以跨区间后的状态开始走，走到那个端点时的状态。代码如下:

```cpp
#define fi first 
#define se second
node merge(node l,node r){
    node ret;
    ret.lc=l.lc;
    ret.rc=r.rc;
    for(int i=0;i<=2;++i){
        for(int j=i;j<=2;++j){
            ppi l_start=get_status(r.status_r[i][j],l.rc),r_start=get_status(l.status_l[i][j],r.lc);
            ret.cnt_l[i][j]=l.cnt_l[i][j]+r_start.se+r.cnt_l[r_start.fi.fi][r_start.fi.se];
            ret.status_l[i][j]=r.status_l[r_start.fi.fi][r_start.fi.se];
            ret.cnt_r[i][j]=r.cnt_r[i][j]+l_start.se+l.cnt_r[l_start.fi.fi][l_start.fi.se];
            ret.status_r[i][j]=l.status_r[l_start.fi.fi][l_start.fi.se];
        }
    }
    return ret;
}
```

对于长度为 $1$ 的区间，有初始化：

```cpp
seg[x].lc=seg[x].rc=b[l];//b[l] 是那个点的元素值。
for(int i=0;i<=2;++i){
    for(int j=i;j<=2;++j){
        seg[x].cnt_l[i][j]=seg[x].cnt_r[i][j]=0;//端点已经考虑过且没有遇到新元素，对得分无贡献。
        seg[x].status_l[i][j]=seg[x].status_r[i][j]=mp(i,j);//起点终点相同，受到起点的影响即受到了终点的影响。
    }
}
```

那么单点修改也很好维护：

```cpp
seg[x].lc^=1;
seg[x].rc^=1;
```

查询就是跳链查询。**注意合并信息的顺序**，具体可以参考 [GSS7](https://www.luogu.com.cn/problem/SP6779 "GSS7")。

时间复杂度为 $\mathcal{O}(q\log ^2n)$，空间复杂度为 $\mathcal{O}(n)$。

**[评测记录](https://www.luogu.com.cn/record/121487490 "评测记录")**

**代码**

```cpp
#include<bits/stdc++.h>
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
#define fi first 
#define se second 
#define pii pair<int,int> 
#define ppi pair<pii,int>
#define mp make_pair
using namespace std;
const int N=1e5+5;
int n,q,a[N],siz[N],dep[N],top[N],hson[N],fa[N],dfn[N],id,b[N];
vector<int>g[N];
struct node{
    int cnt_l[3][3],cnt_r[3][3],lc,rc;//l to r;r to l;
    pii status_l[3][3],status_r[3][3];//start l;start r;
}seg[N<<2];
void dfs1(int u){
    siz[u]=1;
    for(int v:g[u]){
        if(v!=fa[u]){
            dep[v]=dep[u]+1;
            fa[v]=u;
            dfs1(v);
            siz[u]+=siz[v];
        }
    }
}
void dfs2(int u){
    for(int v:g[u]){
        if(v!=fa[u]){
            if((siz[v]<<1)>siz[u]){
                hson[u]=v;
                top[v]=top[u];
            }else{
                top[v]=v;
            }
            dfs2(v);
        }
    }
}
void dfs3(int u){
    dfn[u]=++id;
    b[id]=a[u];
    if(hson[u]){
        dfs3(hson[u]);
    }
    for(int v:g[u]){
        if(v!=fa[u]&&v!=hson[u]){
            dfs3(v);
        }
    }
}
ppi get_status(pii p,int x){
    if(p==mp(0,0)&&!x){
        return mp(p,0);
    }
    if(p==mp(0,0)&&x){
        return mp(mp(0,2),1);
    }
    if(p==mp(0,1)&&!x){
        return mp(mp(0,2),1);
    }
    if(p==mp(0,1)&&x){
        return mp(mp(1,2),1);
    }
    if(p==mp(0,2)&&!x){
        return mp(mp(0,0),0);
    }
    if(p==mp(0,2)&&x){
        return mp(mp(2,2),1);
    }
    if(p==mp(1,1)&&!x){
        return mp(mp(1,2),1);
    }
    if(p==mp(1,1)&&x){
        return mp(mp(1,1),0);
    }
    if(p==mp(1,2)&&!x){
        return mp(mp(2,2),1);
    }
    if(p==mp(1,2)&&x){
        return mp(mp(1,1),0);
    }
    return mp(mp(x,2),0);
}
node merge(node l,node r){
    node ret;
    ret.lc=l.lc;
    ret.rc=r.rc;
    for(int i=0;i<=2;++i){
        for(int j=i;j<=2;++j){
            ppi l_start=get_status(r.status_r[i][j],l.rc),r_start=get_status(l.status_l[i][j],r.lc);
            ret.cnt_l[i][j]=l.cnt_l[i][j]+r_start.se+r.cnt_l[r_start.fi.fi][r_start.fi.se];
            ret.status_l[i][j]=r.status_l[r_start.fi.fi][r_start.fi.se];
            ret.cnt_r[i][j]=r.cnt_r[i][j]+l_start.se+l.cnt_r[l_start.fi.fi][l_start.fi.se];
            ret.status_r[i][j]=l.status_r[l_start.fi.fi][l_start.fi.se];
        }
    }
    return ret;
}
void build(int x,int l,int r){
    if(l==r){
        seg[x].lc=seg[x].rc=b[l];
        for(int i=0;i<=2;++i){
            for(int j=i;j<=2;++j){
                seg[x].cnt_l[i][j]=seg[x].cnt_r[i][j]=0;
                seg[x].status_l[i][j]=seg[x].status_r[i][j]=mp(i,j);
            }
        }
        return;
    }
    int mid=(l+r)>>1;
    build(ls(x),l,mid);
    build(rs(x),mid+1,r);
    seg[x]=merge(seg[ls(x)],seg[rs(x)]);
}
void modify(int x,int l,int r,int k){
    if(l==r){
        seg[x].lc^=1;
        seg[x].rc^=1;
        return;
    }
    int mid=(l+r)>>1;
    if(k<=mid){
        modify(ls(x),l,mid,k);
    }else{
        modify(rs(x),mid+1,r,k);
    }
    seg[x]=merge(seg[ls(x)],seg[rs(x)]);
}
node query(int x,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        return seg[x];
    }
    int mid=(l+r)>>1;
    if(qr<=mid){
        return query(ls(x),l,mid,ql,qr);
    }
    if(ql>mid){
        return query(rs(x),mid+1,r,ql,qr);
    }
    return merge(query(ls(x),l,mid,ql,qr),query(rs(x),mid+1,r,ql,qr));
}
node pathquery(int x,int y){
    node info_x,info_y,temp;
    bool empty_x=1,empty_y=1;
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]){
            temp=query(1,1,n,dfn[top[x]],dfn[x]);
            if(empty_x){
                info_x=temp;
                empty_x=0;
            }else{
                info_x=merge(temp,info_x);
            }
            x=fa[top[x]];
        }else{
            temp=query(1,1,n,dfn[top[y]],dfn[y]);
            if(empty_y){
                info_y=temp;
                empty_y=0;
            }else{
                info_y=merge(temp,info_y);
            }
            y=fa[top[y]];
        }
    }
    if(dep[x]<dep[y]){
        temp=query(1,1,n,dfn[x],dfn[y]);
        if(!empty_x){
            swap(info_x.cnt_l,info_x.cnt_r);
            swap(info_x.status_l,info_x.status_r);
            if(!empty_y){
                return merge(info_x,merge(temp,info_y));
            }
            return merge(info_x,temp);
        }
        if(!empty_y){
            return merge(temp,info_y);
        }
        return temp;
    }else{
        temp=query(1,1,n,dfn[y],dfn[x]);
        if(!empty_x){
            info_x=merge(temp,info_x);
            swap(info_x.cnt_l,info_x.cnt_r);
            swap(info_x.status_l,info_x.status_r);
            if(!empty_y){
                return merge(info_x,info_y);
            }
            return info_x;
        }
        swap(temp.cnt_l,temp.cnt_r);
        swap(temp.status_l,temp.status_r);
        if(!empty_y){
            return merge(temp,info_y);
        }
        return temp;
    }
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1,u,v;i<n;++i){
        cin>>u>>v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(1);
    top[1]=1;
    dfs2(1);
    dfs3(1);
    build(1,1,n);
    for(int op,u,v,i=1;i<=q;++i){
        cin>>op>>u;
        if(op==1){
            a[u]^=1;
            modify(1,1,n,dfn[u]);
        }else{
            cin>>v;
            node ans=pathquery(u,v);
            cout<<ans.cnt_l[a[u]][2]<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：5)

对于题意，我们可以这样转化：维护一个变量 $F$，初始为 $0$。每走到一个白色节点，$F\leftarrow \max(-2,F-1)$；每走到一个黑色节点，$F\leftarrow \min(2,F+1)$。在 $F>0$ 时做减法或在 $F<0$ 时做加法可以使答案增加 $1$。

用上面的做法就可以 $O(nq)$ 拿到 $40$ 分了。

---

系统性地，我们重新记录空篮子为 0，装有一条 / 两条黑鱼为 1 / 2，装有一条 / 两条白鱼为 3 / 4。

对于树上单点修改与路径查询，想到树链剖分。

先跑树链剖分得到树的 $\rm dfs$ 序，然后对于线段树的每个区间，它代表了一段 **有序的** 黑白点序列；考虑到过程中的 $F$ 有且仅有 $5$ 种状态，于是我们可以在线段树上的每个区间维护这些信息：

$sum_j$：该变量表示，**当在来到该区间序列前篮子的状态为 $j$ 时，该区间对答案的贡献。**

$suf_j$：该变量表示，**当在来到该区间序列前篮子的状态为 $j$ 时，该区间走完后篮子中的状态。**

对于每个节点，有 $j\in[0,4]$。

那么当区间 $A$ 与区间 $B$ **顺次** 拼接在一起时，可以用以下方式合并出区间 $C$：

```
for i = 0 to 4:
	C.sum[i] = A.sum[i] + B.sum[A.suf[i]]
	C.suf[i] = B.suf[A.suf[i]]

```

也即，让 `A.suf[i]` 代表前一区间的结果作为后一区间的参数即可成功维护信息。我们发现，这样的维护是具有结合律的。

序列中只有一个点时的情况是平凡的。

于是单点修改就可以秒杀了。

那么路径查询呢？注意我们维护的是 $\rm dfs$ 序上递增的点序列，但路径中有一半是递减的。于是我们考虑多开一倍空间，按照 $\rm dfs$ 序的反序维护另一段递减的点序列。查询的时候，将这两段的贡献拼接在一起就行了。

最终复杂度 $O(q\log^2n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 100005

//树链剖分线段树，对一个节点维护 sum[i],suf[i] 当该区间获得了 i 标记的前缀，答案是什么以及最后留下了什么
//i = 0 无前缀 i = 1 一个黑色节点 i = 2 两个黑色节点 i = 3 一个白色节点 i = 4 两个白色节点

int n,q,siz[MAXN],son[MAXN],dep[MAXN],top[MAXN],f[MAXN],F[MAXN][17],c[MAXN];
int dfn[MAXN],pos[MAXN],idx = 0;
vector<int> E[MAXN];

struct node{
	int sum[5],suf[5];
	node(){}
	inline node operator *( node B ){
		node C;
		for( int i = 0 ; i < 5 ; i ++ ){
			C.sum[i] = sum[i] + B.sum[suf[i]];
			C.suf[i] = B.suf[suf[i]];
		}
		return C;
	}
}T[MAXN << 2],revT[MAXN << 2],C0,C1;

void build( int index , int l , int r ){
	if( l == r ){
		if( c[pos[l]] ) T[index] = revT[index] = C1; else T[index] = revT[index] = C0;
		return;
	}
	int mid = ( l + r ) >> 1;
	build( index * 2 , l , mid ),build( index * 2 + 1 , mid + 1 , r );
	T[index] = T[index * 2] * T[index * 2 + 1];
	revT[index] = revT[index * 2 + 1] * revT[index * 2];
}

void dfs1( int x , int fa ){
	siz[x] = 1,son[x] = 0,dep[x] = dep[fa] + 1,f[x] = fa;
	for( int v : E[x] ){
		if( v == fa ) continue;
		dfs1( v , x ); siz[x] += siz[v]; if( siz[v] > siz[son[x]] ) son[x] = v;
	}
}

void dfs2( int x ){
	dfn[x] = ++idx,pos[idx] = x;
	if( !top[x] ) top[x] = x;
	if( son[x] ) top[son[x]] = top[x],dfs2( son[x] );
	for( int v : E[x] ){
		if( v == son[x] || v == f[x] ) continue;
		dfs2( v );
	}
}

void modify( int index , int l , int r , int x , int k ){
	if( l == r ){ if( k ) T[index] = revT[index] = C1; else T[index] = revT[index] = C0; return; }
	int mid = ( l + r ) >> 1;
	if( x <= mid ) modify( index * 2 , l , mid , x , k );
	else modify( index * 2 + 1 , mid + 1 , r , x , k );
	T[index] = T[index * 2] * T[index * 2 + 1];
	revT[index] = revT[index * 2 + 1] * revT[index * 2];
}

node query( int index , int l , int r , int Ql , int Qr ){
	if( Ql <= l && r <= Qr ) return T[index];
	int mid = ( l + r ) >> 1;
	if( Qr <= mid ) return query( index * 2 , l , mid , Ql , Qr );
	if( Ql > mid ) return query( index * 2 + 1 , mid + 1 , r , Ql , Qr );
	return query( index * 2 , l , mid , Ql , Qr ) * query( index * 2 + 1 , mid + 1 , r , Ql , Qr );
}

node reversequery( int index , int l , int r , int Ql , int Qr ){
	if( Ql <= l && r <= Qr ) return revT[index];
	int mid = ( l + r ) >> 1;
	if( Qr <= mid ) return reversequery( index * 2 , l , mid , Ql , Qr );
	if( Ql > mid ) return reversequery( index * 2 + 1 , mid + 1 , r , Ql , Qr );
	return reversequery( index * 2 + 1 , mid + 1 , r , Ql , Qr ) * reversequery( index * 2 , l , mid , Ql , Qr );
}

inline int lca( int u , int v ){
	while( top[u] != top[v] ){
		if( dep[top[u]] < dep[top[v]] ) swap( u , v );
		u = f[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}

inline int getnear( int w , int u ){
	for( int i = 16 ; ~i ; i -- )
		if( dep[F[u][i]] <= dep[w] ) continue;
		else u = F[u][i];
	if( u == w ) return 0;
	return u;
}

inline int Query( int u , int v ){
	int Lca = lca( u , v ),Uw = getnear( Lca , v );
	vector< pair<int,int> > Qs,Qd;
	while( top[u] != top[Lca] ){
		Qs.emplace_back( make_pair( -dfn[top[u]] , -dfn[u] ) );
		u = f[top[u]];
	}
	Qs.emplace_back( make_pair( -dfn[Lca] , -dfn[u] ) );
	if( Uw ){
		while( top[v] != top[Uw] ){
			Qd.emplace_back( make_pair( dfn[top[v]] , dfn[v] ) );
			v = f[top[v]];
		}
		Qd.emplace_back( make_pair( dfn[Uw] , dfn[v] ) );
	}
	reverse( Qd.begin() , Qd.end() );
	for( pair<int,int> ele : Qd ) Qs.emplace_back( ele );
	node Ans;
	if( Qs[0].first < 0 ) Ans = reversequery( 1 , 1 , n , -Qs[0].first , -Qs[0].second );
	else Ans = query( 1 , 1 , n , Qs[0].first , Qs[0].second );
	int rlen = (int)Qs.size();
	for( int j = 1 ; j < rlen ; j ++ ){
		if( Qs[j].first < 0 )
			Ans = Ans * reversequery( 1 , 1 , n , -Qs[j].first , -Qs[j].second );
		else Ans = Ans * query( 1 , 1 , n , Qs[j].first , Qs[j].second );;
	}
	return Ans.sum[0];
}

inline void init(){
	C1.sum[0] = 0,C1.suf[0] = 1;
	C1.sum[1] = 0,C1.suf[1] = 2;
	C1.sum[2] = 0,C1.suf[2] = 2;
	C1.sum[3] = 1,C1.suf[3] = 0;
	C1.sum[4] = 1,C1.suf[4] = 3;
	C0.sum[0] = 0,C0.suf[0] = 3;
	C0.sum[1] = 1,C0.suf[1] = 0;
	C0.sum[2] = 1,C0.suf[2] = 1;
	C0.sum[3] = 0,C0.suf[3] = 4;
	C0.sum[4] = 0,C0.suf[4] = 4;
}

signed main(){
	init();
	scanf("%lld%lld",&n,&q);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&c[i]);
	for( int i = 1 ; i < n ; i ++ ){
		int u,v; scanf("%lld%lld",&u,&v);
		E[u].emplace_back( v ),E[v].emplace_back( u );	
	} dfs1( 1 , 0 ),dfs2( 1 ),build( 1 , 1 , n );
	for( int i = 1 ; i <= n ; i ++ ) F[i][0] = f[i];
	for( int j = 1 ; j <= 16 ; j ++ )
		for( int i = 1 ; i <= n ; i ++ ) F[i][j] = F[F[i][j - 1]][j - 1];
	for( int i = 1 ; i <= q ; i ++ ){
		int opt; scanf("%lld",&opt);
		if( opt == 1 ){
			int u; scanf("%lld",&u);
			c[u] ^= 1,modify( 1 , 1 , n , dfn[u] , c[u] );
		}
		else if( opt == 2 ){
			int u,v; scanf("%lld%lld",&u,&v);
			printf("%lld\n",Query( u , v ));
		}
	}
	return 0;
}
```

---

## 作者：LuoFeng_Nanami (赞：4)

显然地，查询树上两点路径上的信息，这题需要用到树链剖分与线段树维护。

但是，我们很快就会遇到一个棘手的问题：如何合并两端区间的信息？

一个直观的想法是，以每个区间第一个数为起始点，算出这几个区间贡献后相加。可真的是这样吗？我们看一个例子：$10110\ 01001001\ 1$

这样计算之后，我们算出来第一段的贡献是 $2$，剩下一个 $1$ 第二段的贡献为 $2$，剩下一个 $0$，第三段无贡献，剩下一个 $1$。将剩下的 $1$ 与 $0$ 融合，总贡献是 $6$。但是，我们合并过后算出来的正确贡献为 $7$，这是为什么呢？

仔细思考，我们可以发现，我们这么做，相当于小浣熊提着空篮子从每个区间的起点开始走。而实际上，小浣熊的篮子在一开始是可能并不是空的！

但是，我们并不知道在走这一段之前，小浣熊的篮子的状态怎么办？容易发现，篮子状态只可能有以下几种：
* 空的；
* 有一个 $0$；
* 有一个 $1$；
* 有两个 $0$；
* 有两个 $1$。

（为什么没有一个 $0$ 一个 $1$ 的情况呢？因为这种情况下小浣熊会将它们合成吃掉。）

因此，我们可以用线段树维护每种状态下，每段区间的贡献已及走过每段区间之后篮子的状态。

但这道题到这里就结束了吗？

事实上，我们还有两个地方需要注意：

一是，在查询的时候，我们并不知道篮子的状态，因此不可以直接查询出贡献。我们可以建一个 vector，将要用到的线段树上的点都存入 vector 中，等查询完路径时一并处理。

二是，在处理树上路径时，我们会遇到下图所示的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/4ub5mnyr.png)

图中，箭头表示小浣熊走的方向，我们会发现，在 $x$ 所在的链上，访问顺序与 dfs 序相反；而在 $y$ 所在的链上，访问顺序与 dfs 相同，所以，我们需要分类处理。

在 $x$ 所在的链上，我们之前用线段树维护的信息正好是颠倒的，因此，我们还需要用线段树维护一个反过来的情况，查询后，将返回的序列翻转进行处理。

而在 $y$ 所在的链上，我们发现无法确定篮子的状态，所以将所有询问返回的点再加入另一个 vector，最后一并处理。

Talk is cheap.Let me show u the code.

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rll register ll
#define F(i, a, b) for(rll i = a; i <= b; i++)
#define Fdn(i, a, b) for(rll i = a; i >= b; i--)
#define int ll
#define pii pair<int, int>

using namespace std;

const int inf = 0x3f3f3f3f,mod = 1e9 + 7;
const int maxn = 1e5 + 7;

int n, _;
vector<int> G[maxn];
vector<int> ops, yousa;
int num[maxn];
int dfn[maxn], top[maxn], fa[maxn], siz[maxn], hson[maxn], rnk[maxn], dep[maxn], dfn_clock;
int Tree[5][maxn << 2], Left[5][maxn << 2];
int _Tree[5][maxn << 2], _Left[5][maxn << 2];
// 0:empty; 1:0; 2:1; 3:00; 4:11;

inline void dfs1(int u, int f) {
	fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1, hson[u] = -1;
	for(int v : G[u]) {
		if(v == f) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		if(hson[u] == -1 || siz[v] > siz[hson[u]]) hson[u] = v;
	}
}

inline void dfs2(int u, int tp) {
	top[u] = tp, dfn[u] = ++dfn_clock, rnk[dfn_clock] = u;
	if(hson[u] != -1) dfs2(hson[u], tp);
	for(int v : G[u]) 
		if(v != fa[u] && v != hson[u])
			dfs2(v, v);
}

inline void PushUp(int p) {
	F(i, 0, 4) 
		Tree[i][p] = Tree[i][p << 1] + Tree[Left[i][p << 1]][p << 1 | 1],
		Left[i][p] = Left[Left[i][p << 1]][p << 1 | 1];
	F(i, 0, 4)
		_Tree[i][p] = _Tree[i][p << 1 | 1] + _Tree[_Left[i][p << 1 | 1]][p << 1],
		_Left[i][p] = _Left[_Left[i][p << 1 | 1]][p << 1];
}

inline void calc(int k, int l) { //对于长度为 1 的区间，根据 num[k] 进行处理
	Left[0][l] = (num[k] == 0 ? 1 : 2);
	Tree[1][l] = (num[k] == 0 ? 0 : 1), Left[1][l] = (num[k] == 0 ? 3 : 0);
	Tree[2][l] = (num[k] == 0 ? 1 : 0), Left[2][l] = (num[k] == 0 ? 0 : 4);
	Tree[3][l] = (num[k] == 0 ? 0 : 1), Left[3][l] = (num[k] == 0 ? 3 : 1);
	Tree[4][l] = (num[k] == 0 ? 1 : 0), Left[4][l] = (num[k] == 0 ? 2 : 4);
	F(i, 0, 4)
		_Tree[i][l] = Tree[i][l], _Left[i][l] = Left[i][l];
}

inline void Build(int p, int l, int r) {
	if(l == r) {
		int k = rnk[l];
		calc(k, p);
		return ;
	}
	int mid = (l + r) >> 1;
	Build(p << 1, l, mid), Build(p << 1 | 1, mid + 1, r);
	PushUp(p);
}

inline void Modify(int p, int l, int r, int k) {
	if(l == r && l == k) {
		int kkk = rnk[l];
		num[kkk] ^= 1;
		calc(kkk, p);
		return ;
	}
	int mid = (l + r) >> 1;
	if(k <= mid) Modify(p << 1, l, mid, k);
	else Modify(p << 1 | 1, mid + 1, r, k);
	PushUp(p);
}

inline void Query(int p, int l, int r, int s, int t) {
	if(s <= l && r <= t) 
		return ops.push_back(p), void();
	int mid = (l + r) >> 1;
	if(s <= mid) Query(p << 1, l, mid, s, t);
	if(mid < t) Query(p << 1 | 1, mid + 1, r, s, t);
}

inline int QueryPath(int x, int y) {
	int tot = 0, lst = 0; yousa.clear();
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) {
			ops.clear();
			Query(1, 1, n, dfn[top[y]], dfn[y]);
			yousa.insert(yousa.begin(), ops.begin(), ops.end());
			y = fa[top[y]];
		} else {
			ops.clear();
			Query(1, 1, n, dfn[top[x]], dfn[x]);
			reverse(ops.begin(), ops.end());
			for(int i : ops)
				tot += _Tree[lst][i], lst = _Left[lst][i];
			x = fa[top[x]];
		}
	}
	if(dep[x] < dep[y]) {
		ops.clear();
		Query(1, 1, n, dfn[x], dfn[y]);
		yousa.insert(yousa.begin(), ops.begin(), ops.end());
	} else {
		ops.clear();
		Query(1, 1, n, dfn[y], dfn[x]);
		reverse(ops.begin(), ops.end());
		for(int i : ops)
			tot += _Tree[lst][i], lst = _Left[lst][i];
	}
	for(int i : yousa)
		tot += Tree[lst][i], lst = Left[lst][i];
	return tot;
	
}
 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> _;
	F(i, 1, n) cin >> num[i];
	F(i, 1, n - 1) {
		int u, v; cin >> u >> v;
		G[u].push_back(v);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	Build(1, 1, n);
	while(_--) {
		int op, u, v; cin >> op >> u;
		if(op == 1) Modify(1, 1, n, dfn[u]);
		else {
			cin >> v;
			cout << QueryPath(u, v) << '\n';
		}
	}

	return 0;
}
```

---

## 作者：One_JuRuo (赞：4)

## 思路

### 暴力

比赛的时候想过树链剖分，然后想不出来怎么处理区间合并，再加上树链剖分代码量比较大，我又比较懒，就随手写了个暴力拿了40pts。

思路就是暴力求得 $u$ 到 $v$ 的简单路径，然后暴力枚举模拟一遍。

### 40pts 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[100005],e[200005],ne[200005],h[100005],idx=1,k,x,y;
int dep[100005],fa[100005][25],z[100005],cnt;
int f[2];
void dfs1(int u,int f)
{
	for(int i=h[u];i;i=ne[i]) if(e[i]!=f) fa[e[i]][0]=u,dep[e[i]]=dep[u]+1,dfs1(e[i],u);
}
inline void add(int a,int b)
{
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;--i) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;--i) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<n;++i) scanf("%d%d",&x,&y),add(x,y),add(y,x);
	fa[1][0]=1,dep[1]=1,dfs1(1,0);
	for(int i=1;i<=20;++i) for(int u=1;u<=n;++u) fa[u][i]=fa[fa[u][i-1]][i-1];
	while(q--)
	{
		scanf("%d%d",&k,&x);
		if(k==1) a[x]^=1;
		else
		{
			int f[2],lca,ans,cnt,sum;
			scanf("%d",&y),f[0]=f[1]=cnt=ans=0,lca=LCA(x,y);
			while(x!=lca) z[++cnt]=x,x=fa[x][0];
			z[++cnt]=x,cnt+=dep[y]-dep[lca],sum=cnt;
			while(y!=lca) z[sum--]=y,y=fa[y][0];
			sum=0;
			for(int i=1;i<=cnt;++i)
			{
				if(f[a[z[i]]^1]) ans++,f[a[z[i]]^1]--,sum--;
				else if(sum<2) f[a[z[i]]]++,sum++;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

### 正解：树链剖分

显然，暴力时间复杂度非常高，最后一个 subtask 会 TLE。

看了 MaxBlazeResFire 巨佬的题解后恍然大悟，是类似状压的思路，因为篮子里不可能放一阴一阳，因为遇到就会被吃掉，所以篮子里的状态只有 $5$ 个。分别是：啥都没有，有一条阴，有两条阴，有一条阳，有两条阳，分别用数字 $0,1,2,3,4$ 对应。

因为前面区间过了后，篮子里的鱼会对后续区间产生影响，所以我们自然而然地想到，需要用一个变量储存某个状态经过该区间后的状态，用 $suf_i$ 表示状态 $i$ 经过该区间后状态为 $suf_i$，然后再随便用一个 $sum_i$ 代表该区间能吃几条阴阳鱼，也就是答案贡献。

区间合并就很容易推出来了，假设我们用区间 $a$ 和区间 $b$ 合并为区间 $c$。

$$c.suf_i=b.suf_{a.suf_i}$$
$$c.sum_i=a.sum_i+b.sum_a.suf_i$$

用代码表示就是，

```cpp
for(long long i=0;i<=4;i++) c.sum[i]=a.sum[i]+b.sum[a.suf[i]],c.suf[i]=b.suf[a.suf[i]];
```

需要注意的是，因为对于同一个区间，方向不同，答案也不一样，所以需要一个对应的反转的数组。

题目要求里有两个操作，一个是单点修改，一个是区间查询。

单点修改很容易，这里就不展开了。

重点是查询，其实查询和上面的暴力思路差别不大，只不过上面是老实的挨个找，这里可以用树链剖分分成一段一段，这就是这道题用树链剖分的原因。

还不会树链剖分的，可以去[这道模板题](https://www.luogu.com.cn/problem/P3384)。

对于点 $u$, $v$。我们设它们的 LCA 为 $l$。

整个路径就分成了两部分：$u\to l$ 和 $l\to v$。

由于树的性质，点往上找很容易，往下找就很麻烦。

所以我们就都往上找，用一个 vector 存下每段。

需要注意的是，两边方向不一样，记得要颠转。

因为树链剖分是从上往下，所以到时候需要注意那些部分需要用反转的数组，哪些部分用没反转的数组。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,a,b,k,siz[100005],son[100005],dep[100005],top[100005],f[100005][17],c[100005];
long long dfn[100005],wc[100005],cnt;
vector<long long>v[100005];
struct node{long long sum[5],suf[5];}t[400005],ft[400005],s[2];
inline void init()//s是单位数组，用来直接赋值，这个可以自己按照定义推出来 
{
	s[0].sum[0]=0,s[0].sum[1]=1,s[0].sum[2]=1,s[0].sum[3]=0,s[0].sum[4]=0;
	s[0].suf[0]=3,s[0].suf[1]=0,s[0].suf[2]=1,s[0].suf[3]=4,s[0].suf[4]=4;
	s[1].sum[0]=0,s[1].sum[1]=0,s[1].sum[2]=0,s[1].sum[3]=1,s[1].sum[4]=1;
	s[1].suf[0]=1,s[1].suf[1]=2,s[1].suf[2]=2,s[1].suf[3]=0,s[1].suf[4]=3;
}
/*树链剖分部分*/
void dfs1(long long u,long long fa)
{
	siz[u]=1,dep[u]=dep[fa]+1;
	for(long long j:v[u])
		if(j!=fa)
		{
			dfs1(j,u),siz[u]+=siz[j],f[j][0]=u;
			if(siz[j]>siz[son[u]]) son[u]=j;
		}
}
void dfs2(long long u)
{
	dfn[u]=++cnt,wc[cnt]=c[u];
	if(!top[u]) top[u]=u;
	if(son[u]) top[son[u]]=top[u],dfs2(son[u]);
	for(long long j:v[u]) if(j!=son[u]&&j!=f[u][0]) dfs2(j);
}
/*线段树部分*/ 
inline node merge(node a,node b){node c;for(long long i=0;i<=4;i++) c.sum[i]=a.sum[i]+b.sum[a.suf[i]],c.suf[i]=b.suf[a.suf[i]];return c;}//区间合并 
inline void pushup(long long p){t[p]=merge(t[p<<1],t[p<<1|1]),ft[p]=merge(ft[p<<1|1],ft[p<<1]);}//注意：反向的合并是右+左 
void build(long long p,long long l,long long r)
{
	if(l==r)
	{
		t[p]=ft[p]=s[wc[l]];
		return;
	}
	long long mid=l+r>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	pushup(p);
}
void update(long long p,long long l,long long r,long long x,long long k)//单点修改 
{
	if(l==r)
	{
		t[p]=ft[p]=s[k];
		return;
	}
	long long mid=l+r>>1;
	if(x<=mid) update(p<<1,l,mid,x,k);
	else update(p<<1|1,mid+1,r,x,k);
	pushup(p);
}
node ask(long long p,long long l,long long r,long long L,long long R)//正向区间查询 
{
	if(L<=l&&r<=R) return t[p];
	long long mid=l+r>>1;
	if(R<=mid) return ask(p<<1,l,mid,L,R);
	if(L>mid) return ask(p<<1|1,mid+1,r,L,R);
	return merge(ask(p<<1,l,mid,L,R),ask(p<<1|1,mid+1,r,L,R));
}
node revask(long long p,long long l,long long r,long long L,long long R)//反向区间查询 
{
	if(L<=l&&r<=R) return ft[p];
	long long mid=l+r>>1;
	if(R<=mid) return revask(p<<1,l,mid,L,R);
	if(L>mid) return revask(p<<1|1,mid+1,r,L,R);
	return merge(revask(p<<1|1,mid+1,r,L,R),revask(p<<1,l,mid,L,R));//区间右+左 
}
inline long long LCA(long long x,long long y)//求LCA 
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=f[top[x]][0];
	}
	return (dep[x]<dep[y])?x:y;
}
inline long long nson(long long rt,long long u)//求rt的那个儿子是u的祖宗 
{
	for(long long i=16;i>=0;--i) if(dep[f[u][i]]>dep[rt]) u=f[u][i];
	return (u==rt)?0:u;//记得特判特殊情况 
}
inline long long gask(long long u,long long v)
{
	long long lca=LCA(u,v),j=nson(lca,v),len;node ans;
	vector<pair<long long,long long>>l,r;//用两个vector存两边的路径 
	while(top[u]!=top[lca]) l.push_back(make_pair(-dfn[top[u]],-dfn[u])),u=f[top[u]][0];//左侧路径是深度高到低，所以需要反转，赋称负值标记 
	l.push_back(make_pair(-dfn[lca],-dfn[u]));
	if(j)
	{
		while(top[v]!=top[j]) r.push_back(make_pair(dfn[top[v]],dfn[v])),v=f[top[v]][0];//右侧路径是深度低到高，不需要反转 
		r.push_back(make_pair(dfn[j],dfn[v]));
	}
	reverse(r.begin(),r.end());//颠转右侧路径 
	for(pair<long long,long long>i:r) l.push_back(i);//把左右侧路径合并
	/*先算一端区间，让后面好写一点*/ 
	if(l[0].first<0) ans=revask(1,1,n,-l[0].first,-l[0].second);//需要反转 
	else ans=ask(1,1,n,l[0].first,l[0].second);
	len=l.size();
	for(long long i=1;i<len;++i)
		if(l[i].first<0) ans=merge(ans,revask(1,1,n,-l[i].first,-l[i].second));//需要反转 
		else ans=merge(ans,ask(1,1,n,l[i].first,l[i].second));
	return ans.sum[0];//求得是以状态0（什么鱼也没有）开始的答案 
}
int main()
{
	init();
	scanf("%lld%lld",&n,&q);
	for(long long i=1;i<=n;++i) scanf("%lld",&c[i]);
	for(long long i=1;i<n;++i) scanf("%lld%lld",&a,&b),v[a].push_back(b),v[b].push_back(a);	
	f[1][0]=1,dfs1(1,0),dfs2(1),build(1,1,n);
	for(long long j=1;j<=16;++j) for(long long i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1];
	for(long long i=1;i<=q;++i)
	{
		scanf("%lld%lld",&k,&a);
		if(k==1) c[a]^=1,update(1,1,n,dfn[a],c[a]);
		else scanf("%lld",&b),printf("%lld\n",gask(a,b));
	}
	return 0;
}
```

---

## 作者：2020kanade (赞：4)

[题目链接。](https://www.luogu.com.cn/problem/P9555) 注意：本写法难写的要死，截至本次更新时作者正在补能够通过的写法。

注意题目里篮子中不可能存在异色鱼，不然直接合起来吃了，因此实际上整个篮子只有 $5$ 种本质不同状态：空，一条鱼（两种颜色两种情况），两条鱼（同上）。根据遇到的鱼的颜色我们可以刻画出一个只有 $10$ 条边的状态转移图，其中有 $4$ 条边会产生 $1$ 的贡献。由于这个状态转移体量很小，考虑用矩阵描述。

考虑列向量
$\begin{bmatrix}
	a_{0}\cr
   a_{1}\cr
   a_{2}\cr
   a_{3}\cr
   a_{4}\cr
   ans
\end{bmatrix}$，其中 $a_0,a_1,a_2,a_3,a_4$ 分别代表的状态为空，一条 $0$，一条 $1$，两条 $0$，两条 $1$，取值为 $0$ 或 $1$；$ans$ 为答案。

现在构造捡到一条 $0$ 的转移矩阵。注意相关转移：$a_0\rightarrow a_1,a_1\rightarrow a_3,a_3\rightarrow a_3,a_2\rightarrow a_0(ans+1),a_4\rightarrow a_2(ans+1)$，可以构造转移矩阵：
$
\begin{bmatrix}
	0 & 0 & 1 & 0 & 0 & 0 \cr
   1 & 0 & 0 & 0 & 0 & 0 \cr
   0 & 0 & 0 & 0 & 1 & 0 \cr
   0 & 1 & 0 & 1 & 0 & 0 \cr
   0 & 0 & 0 & 0 & 0 & 0 \cr
	0 & 0 & 1 & 0 & 1 & 1
\end{bmatrix}
$。

对于捡到一条 $1$ 的转移矩阵，同理可得为
$
\begin{bmatrix}
	0 & 1 & 0 & 0 & 0 & 0 \cr
   0 & 0 & 0 & 1 & 0 & 0 \cr
   1 & 0 & 0 & 0 & 0 & 0 \cr
   0 & 0 & 0 & 0 & 0 & 0 \cr
   0 & 0 & 1 & 0 & 1 & 0 \cr
	0 & 1 & 0 & 1 & 0 & 1
\end{bmatrix}
$。

既然操作能直接上矩阵了，剩下的就简单了。

剖，线段树，注意维护两个不同方向，统计时跳重链查询，注意合并时谁左乘谁。

复杂度 $\Theta(6^3 n\log^2 n)$，怕超时可以给每条重链单独开线段树，查询时整条的重链只需要看看树根，不是整条的最多区间查四次，能做到 $\Theta(6^3n\log n)$。

---

## 作者：sail_with_pleasure (赞：4)

这是一道被某位大佬评价为非常水的题，所以我就随便投到 unrated 赛中了。

此题不算难，但是有一些麻烦。显然这是一道线段树加上树链剖分的题，重点在于我们需要维护一些什么东西。

由于那个人只有两个篮筐，所以，他在某一个点上篮筐的状态只有五种，分别是没有鱼，一条阴鱼，两条阴鱼，一条阳鱼，两条阳鱼。那么我们就可以维护这一个区间内某个状态进来会以什么样的状态出去，又会吃掉几条阴阳鱼，显然这样的状态是可以递推的，即合并两个处理好的 $a$ 和 $b$ 的区间为 $c$：

- $ c.f[i]=b.f[a.f[i]]; $
- $ c.sum[i]=b.sum[a.f[i]]+sum[i]; $

大概解释一下，线段树最底层的状态一定是有一条阴鱼或一条阳鱼的一种，我们在最底层维护这两种情况的初始状态。

例：对于最底层只有一条阴鱼的状态，如果 进入这个区间的篮筐状态是两个阳鱼，那么维护离开这个区间的状态是一条阳鱼，然后此情况的 $sum=1$。

然后发现这个东西不具备取反区间的能力，所以我们还需要再维护一个数组表示反着走的情况，树剖的时候注意一下正反，剩下的就是树剖模板啦！！

代码如下：

```cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define mid ((l+r)/2)
#define N 200001
#define endl '\n'
using namespace std;
int n,m,e[N],son[N],fa[N],siz[N],top[N],dep[N],id[N],cnt;
vector<int> q[N];
struct node{
	int f[5];
	int sum[5];
	node(){
	    for(int i=0;i<=4;i++)f[i]=i;
	    memset(sum,0,sizeof sum);
    	}
	node operator+(node b)const{
		node c;
		for(int i=0;i<=4;i++){
			c.f[i]=b.f[f[i]];
			c.sum[i]=b.sum[f[i]]+sum[i];
		}
		return c;
	}
}a[4*N],b[4*N];
void cge(int s,int l,int r,int x,int k){
	if(l==r){
		if(k==0){
			a[s].f[0]=1;
			a[s].f[1]=2;
			a[s].f[2]=2;
			a[s].f[3]=0;
			a[s].f[4]=3;
			a[s].sum[0]=0;
			a[s].sum[1]=0;
			a[s].sum[2]=0;
			a[s].sum[3]=1;
			a[s].sum[4]=1;
		}else{
			a[s].f[0]=3;
			a[s].f[1]=0;
			a[s].f[2]=1;
			a[s].f[3]=4;
			a[s].f[4]=4;
			a[s].sum[0]=0;
			a[s].sum[1]=1;
			a[s].sum[2]=1;
			a[s].sum[3]=0;
			a[s].sum[4]=0;
		}
		b[s]=a[s];
		return;
	}
	if(x<=mid)cge(s*2,l,mid,x,k);
	else cge(s*2+1,mid+1,r,x,k);
	a[s]=a[s*2]+a[s*2+1];
	b[s]=b[s*2+1]+b[s*2];
}
node ans(int s,int l,int r,int ll,int rr){
	if(ll<=l&&rr>=r){
		return a[s];
	}
	if(ll<=mid&&rr>mid)return ans(s*2,l,mid,ll,rr)+ans(s*2+1,mid+1,r,ll,rr);
	if(ll<=mid)return ans(s*2,l,mid,ll,rr);
	if(rr>mid)return ans(s*2+1,mid+1,r,ll,rr);
    exit(114514);
}
node bans(int s,int l,int r,int ll,int rr){
	if(ll<=l&&rr>=r){
		return b[s];
	}
	if(ll<=mid&&rr>mid)return bans(s*2+1,mid+1,r,ll,rr)+bans(s*2,l,mid,ll,rr);
	if(ll<=mid)return bans(s*2,l,mid,ll,rr);
	if(rr>mid)return bans(s*2+1,mid+1,r,ll,rr);
	exit(114514);
}
void dfs(int s){
	siz[s]=1;
	dep[s]=dep[fa[s]]+1;
	for(int i=0;i<q[s].size();i++){
		int l=q[s][i];
		if(fa[s]==l)continue;
		fa[l]=s;
		dfs(l);
		siz[s]+=siz[l];
		if(siz[son[s]]<siz[l]){
			son[s]=l;
		}
	}
	return;
}
void dfs2(int s,int topr){
	id[s]=++cnt;
	cge(1,1,n,id[s],e[s]);
	top[s]=topr;
	if(!son[s])return;
	dfs2(son[s],topr);
	for(int i=0;i<q[s].size();i++){
		int l=q[s][i];
		if(fa[s]==l||son[s]==l)continue;
		dfs2(l,l);
	}
	return;
}
int split(int x,int y){
	node l,r;
	int tx=top[x],ty=top[y];
	while(tx!=ty){
        if(dep[tx]>dep[ty]){
            l=l+bans(1,1,n,id[tx],id[x]);
            x=fa[tx];
        }else{
            r=ans(1,1,n,id[ty],id[y])+r;
            y=fa[ty];
        }
        tx=top[x],ty=top[y];
	}
	if(dep[x]>dep[y]){
        l=l+bans(1,1,n,id[y],id[x]);
	}else{
        r=ans(1,1,n,id[x],id[y])+r;
	}
	l=l+r;
	return l.sum[0];
}
signed main(){
    //freopen("fish12.in","r",stdin);
    //freopen("fish12.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>e[i];
	}
	for(int i=1;i<n;i++){
		static int u,v;
		cin>>u>>v;
		q[u].push_back(v);
		q[v].push_back(u);
	}
	dfs(1);
	dfs2(1,1);
	for(int i=1;i<=m;i++){
        static int op;
		cin>>op;
		if(op==1){
		    static int u;
			cin>>u;
			assert(e[u]>=0);
			cge(1,1,n,id[u],1-e[u]);
			e[u]=1-e[u];
		}else{
		    static int u,v;
			cin>>u>>v;
			cout<<split(u,v)<<endl;
		}
	}
	return 0;
}
```

---

## 作者：_Jocularly_ (赞：2)

我们发现筐子里的情况总共五种，没有鱼、有一个阴或阳鱼、有两个阴或阳鱼，我们分别用一到五的数字表示他们的状态，那么定义经过点 $i$ 后的答案为 $num_i$，经过点 $i$ 后的状态为 $next_i$，那么如果合并 $u$ 和 $v$ 为 $ans$，就可以写出合并转移式。

那么已知上面的转移方程后，我们就可以预处理出阴或阳鱼对应的状态。注意合并不支持交换律，所以需要看好先后顺序。因为树剖是同时向上跳，但是答案要求顺序，所以左侧的需要翻转求解。可以单独写一个翻转查询的函数，显然函数内合并的时候也需要翻转。因为这里翻转了，所以在树链剖分查询操作的合并时，用到这个的也需要前后调换，相当于负负得正。

那么定义 $lval_i$ 和 $rval_i$ 分别为从 $i$ 状态开始走，从左向右走和从右向左走的答案。对于操作一暴力修改即可，对于操作二直接树剖即可。显然答案就是从当前节点出发，筐子里什么都没有的状态开始。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls(x) (x << 1)
#define rs(x) ((x << 1) | 1)
int n,m;
struct node{
    int to;
    int next;
}e[200005];
int cnt;
int head[200005];
int dep[100005],top[100005];
int siz[100005],father[100005];
int son[100005];
int tot;
int dfn[100005],id[100005];
int val[100005];
struct data{
    int num[6];
    int next[6];
    data(){
        for(int i=1;i<=5;i++){
            num[i] = 0;
            next[i] = i;
        }
    }
    int empty(){
        int flag = 0;
        for(int i=1;i<=5;i++){
            flag |= num[i];
            flag |= next[i];
        }
        return !flag;
    }
    void init(int x){
        memset(num,0,sizeof(num));
        if(x){
            next[1] = 2;
			next[2] = 5;
			next[3] = 1;
            next[4] = 3;
			next[5] = 5;
            num[3] = 1;
			num[4] = 1;
        }else{
            next[1] = 3;
			next[2] = 1;
			next[3] = 4;
			next[4] = 4;
			next[5] = 2;
            num[2] = 1;
	        num[5] = 1;
        }
    }
};
struct segment{
    int l,r;
    data lval,rval;
}tree[800005];
data merge(data u,data v){
    if(u.empty()) return v;
    if(v.empty()) return u;
    data ans;
    for(int i=1;i<=5;i++){
        ans.num[i] = u.num[i] + v.num[u.next[i]];
        ans.next[i] = v.next[u.next[i]];
    }
    return ans;
}
void pushup(int x){
    tree[x].lval = merge(tree[ls(x)].lval,tree[rs(x)].lval);
    tree[x].rval = merge(tree[rs(x)].rval,tree[ls(x)].rval);
}
void build(int l,int r,int x){
    tree[x].l = l;
    tree[x].r = r;
    if(l == r){
        tree[x].lval.init(val[id[l]]);
        tree[x].rval.init(val[id[l]]);
        return ;
    }
    int mid = (l + r) / 2;
    build(l,mid,ls(x));
    build(mid+1,r,rs(x));
    pushup(x);
}
void update(int q,int l,int r,int x,int k){
    if(l == r){
        tree[x].lval.init(k);
        tree[x].rval.init(k);
        return ;
    }
    int mid = (l + r) / 2;
    if(q <= mid) update(q,l,mid,ls(x),k);
    else update(q,mid+1,r,rs(x),k);
    pushup(x);
}
data query_forward(int ql,int qr,int l,int r,int x){
    if(ql <= l && r <= qr) return tree[x].lval;
    int mid = (l + r) / 2;
    if(qr <= mid) return query_forward(ql,qr,l,mid,ls(x));
    else if(ql > mid) return query_forward(ql,qr,mid+1,r,rs(x));
    else return merge(query_forward(ql,qr,l,mid,ls(x)),query_forward(ql,qr,mid+1,r,rs(x)));
}
data query_backward(int ql,int qr,int l,int r,int x){
    if(ql <= l && r <= qr) return tree[x].rval;
    int mid = (l + r) / 2;
    if(qr <= mid) return query_backward(ql,qr,l,mid,ls(x));
    else if(ql > mid) return query_backward(ql,qr,mid+1,r,rs(x));
    else return merge(query_backward(ql,qr,mid+1,r,rs(x)),query_backward(ql,qr,l,mid,ls(x)));
}
int query_chain(int u,int v){
    data ans1,ans2;
    while(top[u] != top[v]){
        if(dep[top[u]] > dep[top[v]]) ans1 = merge(ans1,query_backward(dfn[top[u]],dfn[u],1,n,1));
        else ans2 = merge(query_forward(dfn[top[v]],dfn[v],1,n,1),ans2);
        if(dep[top[u]] > dep[top[v]]) u = father[top[u]];
        else v = father[top[v]];
    }
    if(dep[u] > dep[v]) ans1 = merge(ans1,query_backward(dfn[v],dfn[u],1,n,1));
    else ans2 = merge(query_forward(dfn[u],dfn[v],1,n,1),ans2);
    data ans = merge(ans1,ans2);
    return ans.num[1];
}
void add(int u,int v){
    e[++ cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
void dfs1(int u,int fa){
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    father[u] = fa;
    for(int i=head[u];i;i=e[i].next){
        int v = e[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        siz[u] += siz[v];
        if(siz[son[u]] < siz[v]) son[u] = v;
    }
}
void dfs2(int u,int ntop){
    top[u] = ntop;
    dfn[u] = ++ tot;
    id[tot] = u;
    if(son[u]) dfs2(son[u],ntop);
    for(int i=head[u];i;i=e[i].next){
        int v = e[i].to;
        if(v == son[u] || v == father[u]) continue;
        dfs2(v,v);
    }
}
signed main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> val[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    while(m --){
        int op;
        int u,v;
        cin >> op >> u;
        if(op == 1){
            val[u] ^= 1;
            update(dfn[u],1,n,1,val[u]);
        }else{
            cin >> v;
            cout << query_chain(u,v) << "\n";
        }
    }
    return 0;
}
```

---

## 作者：Spouter_27 (赞：1)

看到这种题大概率是树剖。浣熊的篮子最多只有 $5$ 种状态：全空，一黑，两黑，一白，两白。考虑树剖后，用线段树维护每个节点每个初始状态走过去后会变成什么状态、对答案有多少贡献。

对于只有一个点的情况是平凡的，只需要讨论一下。合并也是比较简单的。但是我们是在路径上做这个问题，所以还要维护一下反着走的状态和贡献。之后的细节可以仿照 P7735 轻重边的做法来做就好了。复杂度 $O(n\log^2n)$。

代码：[**Code**](https://www.luogu.com.cn/paste/xu5qdiy5)。

里面有一些注释，希望能帮助你理解。

---

## 作者：Wei_Han (赞：0)

疑似获得全场最唐写法。

简单分析发现，我们需要用线段树维护每个区间在某一起始条件下最终能够的得到的剩余鱼的个数和阴阳鱼的个数，这个起始条件就是当前有几条阴鱼，几条阳鱼。

考虑把这个问题下放到每一个区间，因为有篮子里最多只能有 $2$ 条同种鱼的限制，我们的起始状态数就很小，只有五个子状态，直接枚举分类讨论就好了。

有了序列上的区间做法，拓展到树上的链查询就很简单了，可是发现树剖是从两端同时开始维护答案的，而我们在区间上维护的答案是有方向的，所以需要同时维护从左到右和从右到左的两棵线段树，合并答案时可以画出图来仔细分析一下。

代码实现太困难了。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#define pis pair<ll,char >
//#pragma GCC optimize(2)
using namespace std;
typedef int ll;
//typedef long long ll;
//typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=2e6+5,M=5e6,mod=998244353;
ll n,q,a[N],top[N],id[N],w[N],fa[N],dep[N],son[N],siz[N],cnt;
vector<ll> g[N];
inline void dfs1(ll x,ll fat,ll depth){dep[x]=depth,siz[x]=1,fa[x]=fat;for(ll y:g[x]){if(y==fa[x]) continue;dfs1(y,x,depth+1);siz[x]+=siz[y];if(siz[y]>siz[son[x]]) son[x]=y;}}
inline void dfs2(ll x,ll nowtop){top[x]=nowtop,id[x]=++cnt,w[cnt]=x;if(!son[x]) return;dfs2(son[x],nowtop);for(ll y:g[x]) if(y!=fa[x]&&y!=son[x]) dfs2(y,y);}
struct SGT{ll l,r,ans[5],sum[5];}tree[N<<2],tr[N<<2];
SGT null={0,0,{0,0,0,0,0},{0,0,0,0,0}};
inline void merge(SGT &rt,SGT ls,SGT rs)
{
	fo(0,i,4) 
		rt.ans[i]=ls.ans[i]+rs.ans[ls.sum[i]+2],
		rt.sum[i]=rs.sum[ls.sum[i]+2];
}
#define rt tree[root]
#define ls tree[root<<1]
#define rs tree[root<<1|1]
inline void build(ll root,ll l,ll r)
{
	rt.l=l,rt.r=r;
	if(l==r)
	{
		if(a[w[l]]==1) 
			rt.ans[0]=1,rt.sum[0]=-1,tr[root].ans[0]=1,tr[root].sum[0]=-1,
			rt.ans[1]=1,rt.sum[1]=0,tr[root].ans[1]=1,tr[root].sum[1]=0,
			rt.ans[2]=0,rt.sum[2]=1,tr[root].ans[2]=0,tr[root].sum[2]=1,
			rt.ans[3]=0,rt.sum[3]=2,tr[root].ans[3]=0,tr[root].sum[3]=2,
			rt.ans[4]=0,rt.sum[4]=2,tr[root].ans[4]=0,tr[root].sum[4]=2;
		if(a[w[l]]==-1)
			rt.ans[0]=0,rt.sum[0]=-2,tr[root].ans[0]=0,tr[root].sum[0]=-2,
			rt.ans[1]=0,rt.sum[1]=-2,tr[root].ans[1]=0,tr[root].sum[1]=-2,
			rt.ans[2]=0,rt.sum[2]=-1,tr[root].ans[2]=0,tr[root].sum[2]=-1,
			rt.ans[3]=1,rt.sum[3]=0,tr[root].ans[3]=1,tr[root].sum[3]=0,
			rt.ans[4]=1,rt.sum[4]=1,tr[root].ans[4]=1,tr[root].sum[4]=1;
		return;			
	}
	ll mid=l+r>>1;build(root<<1,l,mid),build(root<<1|1,mid+1,r);merge(rt,ls,rs);merge(tr[root],tr[root<<1|1],tr[root<<1]);
}
inline void upd(ll root,ll x)
{
	ll l=rt.l,r=rt.r;
	if(l==r)
	{
		if(a[w[l]]==1) 
			rt.ans[0]=1,rt.sum[0]=-1,tr[root].ans[0]=1,tr[root].sum[0]=-1,
			rt.ans[1]=1,rt.sum[1]=0,tr[root].ans[1]=1,tr[root].sum[1]=0,
			rt.ans[2]=0,rt.sum[2]=1,tr[root].ans[2]=0,tr[root].sum[2]=1,
			rt.ans[3]=0,rt.sum[3]=2,tr[root].ans[3]=0,tr[root].sum[3]=2,
			rt.ans[4]=0,rt.sum[4]=2,tr[root].ans[4]=0,tr[root].sum[4]=2;
		if(a[w[l]]==-1)
			rt.ans[0]=0,rt.sum[0]=-2,tr[root].ans[0]=0,tr[root].sum[0]=-2,
			rt.ans[1]=0,rt.sum[1]=-2,tr[root].ans[1]=0,tr[root].sum[1]=-2,
			rt.ans[2]=0,rt.sum[2]=-1,tr[root].ans[2]=0,tr[root].sum[2]=-1,
			rt.ans[3]=1,rt.sum[3]=0,tr[root].ans[3]=1,tr[root].sum[3]=0,
			rt.ans[4]=1,rt.sum[4]=1,tr[root].ans[4]=1,tr[root].sum[4]=1;
		return;			
	}
	ll mid=l+r>>1;if(x<=mid) upd(root<<1,x);else upd(root<<1|1,x);merge(rt,ls,rs);merge(tr[root],tr[root<<1|1],tr[root<<1]);
}
inline SGT ask1(ll root,ll x,ll y)
{
	ll l=rt.l,r=rt.r;if(x<=l&&y>=r) return rt;
	ll mid=l+r>>1;if(x>mid) return ask1(root<<1|1,x,y);if(y<=mid) return ask1(root<<1,x,y);
	SGT a=ask1(root<<1,x,y),b=ask1(root<<1|1,x,y),c=null;
	merge(c,a,b);return c;
}
inline SGT ask2(ll root,ll x,ll y)
{
	ll l=rt.l,r=rt.r;if(x<=l&&y>=r) return tr[root];
	ll mid=l+r>>1;if(x>mid) return ask2(root<<1|1,x,y);if(y<=mid) return ask2(root<<1,x,y);
	SGT a=ask2(root<<1,x,y),b=ask2(root<<1|1,x,y),c=null;
	merge(c,b,a);return c;
}
inline ll ask_chain(ll x,ll y)
{
	SGT now1=null,now2=null;ll fl1=0,fl2=0;
	while(top[x]^top[y])
	{
		if(dep[top[x]]<dep[top[y]])
		{
			if(!fl2) now2=ask1(1,id[top[y]],id[y]),fl2=1;
			else merge(now2,ask1(1,id[top[y]],id[y]),now2);
			y=fa[top[y]];
		}
		else
		{
			if(!fl1) now1=ask2(1,id[top[x]],id[x]),fl1=1;
			else merge(now1,now1,ask2(1,id[top[x]],id[x]));
			x=fa[top[x]];
		}
	}
	if(dep[x]<dep[y])
	{
		if(!fl1) now1=ask1(1,id[x],id[y]),fl1=1;
		else merge(now1,now1,ask1(1,id[x],id[y]));
		if(!fl2) return now1.ans[2];
		merge(now1,now1,now2);
	}	
	else
	{
		if(!fl2) now2=ask2(1,id[y],id[x]),fl2=1;
		else merge(now2,ask2(1,id[y],id[x]),now2);
		if(!fl1) return now2.ans[2];
		merge(now1,now1,now2);
	}
	return now1.ans[2];
}
signed main(){
	read(n),read(q);fo(1,i,n) read(a[i]),a[i]=(!a[i]?-1:a[i]);
	ll u,v;fo(1,i,n-1) read(u),read(v),g[u].pb(v),g[v].pb(u);
	dfs1(1,0,1),dfs2(1,1),build(1,1,n);
	fo(1,i,q)
	{
		ll opt,u,v;read(opt),read(u);
		if(opt==1) a[u]=(a[u]==1?-1:1),upd(1,id[u]);
		if(opt==2) read(v),wr(ask_chain(u,v)),pr;
	}
	return 0;
}
``````

---

## 作者：Genius_Star (赞：0)

### 思路：

注意到，每时每刻篮筐内只有 $5$ 种状态，分别为：

- 没有鱼。

- 有一条阳鱼。

- 有一条阴鱼。

- 有两条阴鱼。

- 有两条阳鱼。

则我们可以使用线段树维护区间以 $5$ 种状态进入后分别得到的贡献和离开时篮筐内的状态，则状态转移为：

$$data_i=Ldata_i+Rdata_{Lend_i}$$

$$end_i=Rend_{Lend_i}$$

那么对于一条链上的查询，考虑树链剖分算法，将路径的链都提取出来。

但是这样会有一个顺序的问题，从 $u \to v$ 和从 $v \to u$ 的答案是不一样的。

所以不仅要维护 $[l,r]$ 区间从 $l \to r$ 的贡献，还要维护 $r \to l$ 的贡献。

时间复杂度为 $O((N+Q) \log N)$。

**常数偏大，谨慎使用！**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100,M=6; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
// 1:00,2:01,3:10,4:20,5:02
class St{
public:
	ll data[M]; // 以状态 i 进入后数量为 data[i] 
	ll end[M]; // 以状态 i 出来后状态为 end[i] 
	St(){
		for(int i=1;i<M;i++)
		  end[i]=i;
		memset(data,0,sizeof(data));
	}
	bool empty(){
		for(int i=0;i<M;i++)
		  if(data[i]||end[i])
		    return 0;
		return 1;
	}
	void init(ll x){
		memset(data,0,sizeof(data));
		if(x){
			end[1]=2;
			end[2]=5;
			end[3]=1;
			data[3]=1;
			end[4]=3;
			data[4]=1;
			end[5]=5;
		}
		else{
			end[1]=3;
			end[2]=1;
			data[2]=1;
			end[3]=4;
			end[4]=4;
			end[5]=2;
			data[5]=1;
		}
	}
};
struct Node{
	ll l,r;
	St h,t;
}X[N<<2];
ll n,m,cnt,op,x,y;
ll a[N],d[N],p[N],t[N],z[N],fa[N];
ll A[N],B[N];
vector<ll> E[N];
vector<St> V;
void add(ll u,ll v){
	E[u].push_back(v);
	E[v].push_back(u);
}
void dfs1(ll u,ll f){
	p[u]=1;
	for(auto v:E[u]){
		if(v==f)
		  continue;
		fa[v]=u;
		d[v]=d[u]+1;
		dfs1(v,u);
		p[u]+=p[v];
		if(p[v]>p[z[u]])
		  z[u]=v;
	}
}
void dfs2(ll u,ll k){
	++cnt;
	A[u]=cnt;
	B[cnt]=u;
	t[u]=k;
	if(!z[u])
	  return ;
	dfs2(z[u],k);
	for(auto v:E[u]){
		if(v==z[u]||v==fa[u])
		  continue;
		dfs2(v,v);
	}
}
St Union(St x,St y){
	if(x.empty())
	  return y;
	St ans;
	for(int i=1;i<M;i++){
		ans.data[i]=x.data[i]+y.data[x.end[i]];
		ans.end[i]=y.end[x.end[i]];
	}
	return ans;
}
void pushup(ll k){
	X[k].h=Union(X[k<<1].h,X[k<<1|1].h);
	X[k].t=Union(X[k<<1|1].t,X[k<<1].t);
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	if(l==r){
		X[k].h.init(a[B[l]]);
		X[k].t.init(a[B[l]]);
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
void add(ll k,ll i,ll v){
	if(X[k].l==i&&i==X[k].r){
		X[k].h.init(v);
		X[k].t.init(v);
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  add(k<<1,i,v);
	else
	  add(k<<1|1,i,v);
	pushup(k);
}
St qurey(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return X[k].h;
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return qurey(k<<1,l,r);
	else if(l>mid)
	  return qurey(k<<1|1,l,r);
	else
	  return Union(qurey(k<<1,l,mid),qurey(k<<1|1,mid+1,r));
}
St qureyReverse(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return X[k].t;
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return qureyReverse(k<<1,l,r);
	else if(l>mid)
	  return qureyReverse(k<<1|1,l,r);
	else
	  return Union(qureyReverse(k<<1|1,mid+1,r),qureyReverse(k<<1,l,mid));
}
St qurey(ll u,ll v){
	St l,r;
	while(t[u]!=t[v]){
		if(d[t[u]]>d[t[v]]){
			l=Union(l,qureyReverse(1,A[t[u]],A[u]));
			u=fa[t[u]];
		}
		else{
			r=Union(qurey(1,A[t[v]],A[v]),r);
			v=fa[t[v]];
		}
	}
	if(d[u]>d[v])
	  l=Union(l,qureyReverse(1,A[v],A[u]));
	else
	  r=Union(qurey(1,A[u],A[v]),r);
	return Union(l,r);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int u,v,i=1;i<n;i++){
		u=read(),v=read();
		add(u,v);
	}
	dfs1(1,1);
	dfs2(1,1);
	build(1,1,cnt);
	while(m--){
		op=read(),x=read();
		if(op==1){
			a[x]^=1ll;
			add(1,A[x],a[x]); 
		}
		else{
			y=read();
			write(qurey(x,y).data[1]);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

可以用 LCT 这种数据结构 。 
# 注意！  
题目中说浣熊带着能装两条鱼的篮筐在此树的某条链上行走。当他所在点上的鱼与某条筐内鱼的属性相反时，他会将这两条鱼合成一条阴阳鱼并吃下；在筐中没有满的条件下，他会将所在点上的鱼放入筐中。  
也就是说，你可以当他是一个侦测器，当两种属性不同时抵消，同时给予变量加一的选择，鱼筐的状态只有五种。我们将一条链的信息看作从鱼框的一种状态开始，经过这条链之后会变成什么状态，变量一开始必须重置为 $0$ 代表与鱼筐里没鱼，看看最后变量变成了几。所以将链上的信息合并之后的 $p_0$ 去末三位就是答案。

于是，代码就出来了：
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct dat{
    int p[5];//0,10,20,11,21;
    dat operator*(const dat &z)const{
        return{
            ((p[0]>>3)<<3)+z.p[p[0]&7],
            ((p[1]>>3)<<3)+z.p[p[1]&7],
            ((p[2]>>3)<<3)+z.p[p[2]&7],
            ((p[3]>>3)<<3)+z.p[p[3]&7],
            ((p[4]>>3)<<3)+z.p[p[4]&7]
        };
    }
    void init(int d){
        if(d)*this={3,8,9,4,4};
        else *this={1,2,2,8,11};
    }
    void init(){*this={0,1,2,3,4};}
    void put(){
        for(int i=0;i<5;++i)
            printf("%d%c",p[i]," \n"[i==4]);
    }
}s1[N],s2[N],v[N];
int n,q,cl[N],rv[N],t[N][2],f[N];
#define ls t[x][0]
#define rs t[x][1]
#define tp(x) (t[f[x]][1]==x)
#define in(x) (t[f[x]][0]==x||tp(x))
void pp(int x){
    s1[x]=s2[x]=v[x];
    if(ls)s1[x]=s1[ls]*s1[x],s2[x]=s2[x]*s2[ls];
    if(rs)s1[x]=s1[x]*s1[rs],s2[x]=s2[rs]*s2[x];
}
void rev(int x){
    rv[x]^=1,swap(ls,rs);
    swap(s1[x],s2[x]);
}
void pd(int x){
    if(rv[x]){
        if(ls)rev(ls);
        if(rs)rev(rs);rv[x]=0;
    }
}
void ppd(int x){
    if(in(x))ppd(f[x]);pd(x);
}
void rot(int x){
    int y=f[x],k=tp(x),w=t[x][!k];
    t[f[w]=t[x][!k]=y][k]=w;
    if(in(y))t[f[y]][tp(y)]=x;
    f[x]=f[y],f[y]=x,pp(y);
}
void splay(int x){
    ppd(x);
    for(int y=f[x];in(x);rot(x),y=f[x])
        if(in(y))rot(tp(x)^tp(y)?x:y);pp(x);
}
void acs(int x){
    for(int y=0;x;x=f[y=x])
        splay(x),rs=y,pp(x);
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    int i,j,k,l,r,x,y;
    for(x=1;x<=n;++x)cin>>cl[x],v[x].init(cl[x]),pp(x);
    for(i=1;i<n;++i){
        cin>>x>>y;
        acs(x),splay(x),rev(x),f[x]=y;
    }
    s1[0].init(),s1[0].init();
    while(q--){
        cin>>k>>x;
        if(k==1)splay(x),v[x].init(cl[x]^=1),pp(x);
        else{
            cin>>y,acs(x),splay(x),rev(x);
            acs(y),splay(x);
            printf("%d\n",s1[x].p[0]>>3);
        }
    }return 0;
}
```


---

