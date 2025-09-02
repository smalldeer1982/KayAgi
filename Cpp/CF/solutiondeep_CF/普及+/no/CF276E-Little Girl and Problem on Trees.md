# 题目信息

# Little Girl and Problem on Trees

## 题目描述

A little girl loves problems on trees very much. Here's one of them.

A tree is an undirected connected graph, not containing cycles. The degree of node $ x $ in the tree is the number of nodes $ y $ of the tree, such that each of them is connected with node $ x $ by some edge of the tree.

Let's consider a tree that consists of $ n $ nodes. We'll consider the tree's nodes indexed from 1 to $ n $ . The cosidered tree has the following property: each node except for node number 1 has the degree of at most 2.

Initially, each node of the tree contains number 0. Your task is to quickly process the requests of two types:

- Request of form: $ 0 $ $ v $ $ x $ $ d $ . In reply to the request you should add $ x $ to all numbers that are written in the nodes that are located at the distance of at most $ d $ from node $ v $ . The distance between two nodes is the number of edges on the shortest path between them.
- Request of form: $ 1 $ $ v $ . In reply to the request you should print the current number that is written in node $ v $ .

## 样例 #1

### 输入

```
3 6
1 2
1 3
0 3 1 2
0 2 3 1
0 1 5 2
1 1
1 2
1 3
```

### 输出

```
9
9
6
```

## 样例 #2

### 输入

```
6 11
1 2
2 5
5 4
1 6
1 3
0 3 1 3
0 3 4 5
0 2 1 4
0 1 5 5
0 4 6 2
1 1
1 2
1 3
1 4
1 5
1 6
```

### 输出

```
11
17
11
16
17
11
```

# AI分析结果

### 题目内容
# 小女孩与树上的问题

## 题目描述
一个小女孩非常喜欢关于树的问题。这是其中之一。

一棵树是一个无向连通图，不包含环。树中节点 $x$ 的度是指树中与节点 $x$ 通过树的某条边相连的节点 $y$ 的数量。

考虑一棵由 $n$ 个节点组成的树。我们将树的节点从 1 到 $n$ 进行编号。这棵树具有以下性质：除了节点 1 之外，每个节点的度最多为 2。

最初，树的每个节点都包含数字 0。你的任务是快速处理两种类型的请求：
- 请求形式：$0$ $v$ $x$ $d$。对于该请求，你应该将 $x$ 添加到距离节点 $v$ 最多为 $d$ 的所有节点中所写的数字上。两个节点之间的距离是它们之间最短路径上的边数。
- 请求形式：$1$ $v$。对于该请求，你应该输出当前节点 $v$ 中所写的数字。

## 样例 #1
### 输入
```
3 6
1 2
1 3
0 3 1 2
0 2 3 1
0 1 5 2
1 1
1 2
1 3
```
### 输出
```
9
9
6
```

## 样例 #2
### 输入
```
6 11
1 2
2 5
5 4
1 6
1 3
0 3 1 3
0 3 4 5
0 2 1 4
0 1 5 5
0 4 6 2
1 1
1 2
1 3
1 4
1 5
1 6
```
### 输出
```
11
17
11
16
17
11
```

### 算法分类
树状数组、线段树

### 题解综合分析与结论
这些题解主要围绕利用树的特殊结构（根节点下挂多条链）来解决两种操作（区间修改和单点查询）。大部分题解使用线段树或树状数组来维护节点信息，不同之处在于处理修改操作时对链上和跨链部分的具体实现方式。

### 所选的题解
#### 作者：玖梦 (5星)
- **关键亮点**：思路清晰，利用树的结构特点，通过线段树维护链上区间权值，树状数组维护根节点标记，详细讨论了修改操作中不同情况的处理方式，时间复杂度分析准确。
- **个人心得**：无
```cpp
// 线段树相关结构体及操作
struct Segment_Tree{
    int l,r;
    ll sum;
    ll add;
    #define l(p) tree[p].l
    #define r(p) tree[p].r
    #define sum(p) tree[p].sum
    #define add(p) tree[p].add
}tree[N<<2];

void push_up(int p){sum(p)=sum(p<<1)+sum(p<<1|1);}

void spread(int p)
{
    if(add(p))
    {
        sum(p<<1)+=add(p)*(r(p<<1)-l(p<<1)+1);
        sum(p<<1|1)+=add(p)*(r(p<<1|1)-l(p<<1|1)+1);
        add(p<<1)+=add(p);
        add(p<<1|1)+=add(p);
        add(p)=0; 
    }
}

void build(int p,int l,int r)
{
    l(p)=l,r(p)=r;
    if(l==r)return;
    int mid=l+r>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}

void change(int p,int l,int r,int v)
{
    if(l<=l(p)&&r>=r(p))
    {
        sum(p)+=(ll)v*(r(p)-l(p)+1);
        add(p)+=v;
        return;
    }
    spread(p);
    int mid=l(p)+r(p)>>1;
    if(l<=mid)change(p<<1,l,r,v);
    if(r>mid)change(p<<1|1,l,r,v);
    push_up(p);
}

int query(int p,int pos)
{
    if(l(p)==r(p))return sum(p);
    spread(p);
    int mid=l(p)+r(p)>>1;
    if(pos<=mid)return query(p<<1,pos);
    else return query(p<<1|1,pos);
}

// 树状数组相关操作
int tr[N];
int lowbit(int x){return x&-x;}

void add_tree(int x,int y){for(;x<=n;x+=lowbit(x))tr[x]+=y;}

int ask(int x)
{
    int ans=0;
    for(;x;x-=lowbit(x))ans+=tr[x];
    return ans;
}

// 主函数中处理修改和查询操作
while(m--)
{
    int tp;scanf("%d",&tp);
    if(!tp) //修改操作 
    {
        int u,x,d;scanf("%d%d%d",&u,&x,&d);
        if(u==1)add_tree(d+1,x); //根节点直接特殊处理，d+1是下标后移一位 
        else if(d<dep[u]) //完全在链上的情况 
            change(1,max(id[u]-d,id[u]-dep[u]+1),min(id[u]+len[ch[u]]-dep[u],id[u]+d),x); //顶端取max，末端取min 
        else //需要在根上挂标记的情况 
        {
            add_tree(d-dep[u]+1,x); //处理根上的标记，+1同样也是因为下标后移一位 
            if(id[u]+len[ch[u]]-dep[u]<id[u]+d-2*dep[u]+1)continue; //链尾<未被覆盖的第一个点，即链尾已被覆盖 
            change(1,id[u]+d-2*dep[u]+1,min(id[u]+len[ch[u]]-dep[u],id[u]+d),x); //末端取min 
        }
    }
    else //查询操作 
    {
        int u;scanf("%d",&u);
        int ans=query(1,id[u]); //已经被修改的部分 
        int sum=ask(n)-ask(dep[u]); //还保留在根上的待修改部分，范围是[dep[u],n-1]，下标后移一位[dep[u]+1,n]
        //由于树状数组查询的是前缀和，所以查询1~n和1~dep[u]相减即可。 
        printf("%d\n",ans+sum); //两部分相加即为答案 
    }
}
```
核心实现思想：线段树用于维护链上区间修改和单点查询，树状数组用于维护根节点标记的后缀和。在修改操作中，根据距离与节点深度的关系，分别进行链上修改和根节点标记处理；查询时，结合线段树和树状数组的结果得到最终答案。

#### 作者：_edge_ (4星)
- **关键亮点**：提出倍增做法，可处理有边权情况，将修改操作分解为不同情况，利用树状数组和树上差分思想，对每种情况分别处理，有独特的解题视角。
- **个人心得**：无
```cpp
// 倍增和树状数组相关操作
void DFS(int x,int fa) {
    fa1[x][0]=fa;sz[x]=1;
    dep[x]=dep[fa]+1;dfn[++dfn[0]]=x;pre[x]=dfn[0];
    for (int i=1;i<=23;i++)
        fa1[x][i]=fa1[fa1[x][i-1]][i-1];
    for (int i=head[x];i;i=edge[i].next_) {
        int v=edge[i].to_;
        if (v==fa) continue;
        DFS(v,x);son1[x][0]=v;sz[x]+=sz[v];
    }
    for (int i=1;i<=23;i++)
        son1[x][i]=son1[son1[x][i-1]][i-1];
}

struct BIT{
    int tree[INF];
    void add(int x,int y) {for (int i=x;i<=1e5;i+=i&-i) tree[i]+=y;}
    int query(int x) {int sum=0;for (int i=x;i;i-=i&-i) sum+=tree[i];return sum;}
}T1,T2;

// 主函数中处理修改和查询操作
for (int i=1;i<=q;i++) {
    int op=0,x=0,y=0,z=0;cin>>op;
    if (op==0) {
        cin>>x>>z>>y;
        if (x==1) T1.add(y+1,z);
        else {
            if (dep[x]-y>=1) {
                int xx=x,yy=dep[x]+y;
                for (int i=23;i>=0;i--) {
                    if (!son1[xx][i]) continue;
                    if (dep[son1[xx][i]]>yy) continue;
                    xx=son1[xx][i];
                }
                T2.add(pre[xx],z);
                
                xx=x,yy=dep[x]-y;
                for (int i=23;i>=0;i--) {
                    if (!fa1[xx][i]) continue;
                    if (dep[fa1[xx][i]]<yy) continue;
                    xx=fa1[xx][i];
                }
                xx=fa1[xx][0];
                if (xx) T2.add(pre[xx],-z);
            }
            else {
                int xx=x,yy=dep[x]+y;
                for (int i=23;i>=0;i--) {
                    if (!son1[xx][i]) continue;
                    if (dep[son1[xx][i]]>yy) continue;
                    xx=son1[xx][i];
                }
                T2.add(pre[xx],z);
                T1.add(y-dep[x]+2,z);
                xx=x,yy=y-dep[x]+2;int fl=0;
                if (dep[xx]>yy) fl=1;
                for (int i=23;i>=0;i--) {
                    if (!fa1[xx][i]) continue;
                    if (dep[fa1[xx][i]]<=yy) continue;
                    xx=fa1[xx][i];
                }
                if (fl) xx=fa1[xx][0];
                if (!fl) {
                    xx=x,yy=y-dep[x]+2;
                    for (int i=23;i>=0;i--) {
                        if (!son1[xx][i]) continue;
                        if (dep[son1[xx][i]]>yy) continue;
                        xx=son1[xx][i];fl=1;
                    }
                }
                T2.add(pre[xx],-z);
            }
        }
    }
    else {
        int x=0;cin>>x;
        cout<<T1.query(1e5)-T1.query(dep[x]-1)+T2.query(pre[x]+sz[x]-1)-T2.query(pre[x]-1)<<"\n";
    }
}
```
核心实现思想：通过倍增找到满足条件的链头和链尾，利用树状数组T1处理根节点修改，树状数组T2处理链上修改，查询时结合两个树状数组的结果。

#### 作者：MeowScore (4星)
- **关键亮点**：重新描述题面，清晰阐述思路，先考虑简单情况，再将两种简单情况结合应对所有情况，代码实现中对线段树的操作较为清晰，细节处理较好。
- **个人心得**：无
```cpp
// 线段树1（基于时间戳）相关操作
struct ST1{
    int tag;
    int sum;
}st1[N*4];

void push_down1(int root,int l,int r){
    int k=st1[root].tag;
    int mid=(l+r)/2;
    st1[root].tag=0;
    st1[root*2].tag+=k;
    st1[root*2+1].tag+=k;
    st1[root*2].sum+=(mid-l+1)*k;
    st1[root*2+1].sum+=(r-mid)*k;
}

void add1(int root,int l,int r,int x,int y,int k){
    if(l>=x&&r<=y){
        st1[root].tag+=k;
        st1[root].sum+=(r-l+1)*k;
        return;
    }
    int mid=(l+r)/2;
    push_down1(root,l,r);
    if(mid>=x)
        add1(root*2,l,mid,x,y,k);
    if(mid+1<=y)
        add1(root*2+1,mid+1,r,x,y,k);
}

void ask1(int root,int l,int r,int x){
    if(l==r){
        res1=st1[root].sum;
        return;
    }
    int mid=(l+r)/2;
    push_down1(root,l,r);
    if(mid>=x)
        ask1(root*2,l,mid,x);
    else
        ask1(root*2+1,mid+1,r,x);
}

// 线段树2（基于深度）相关操作
struct ST2{
    int tag;
    int sum;
}st2[N*4];

void push_down2(int root,int l,int r){
    int k=st2[root].tag;
    int mid=(l+r)/2;
    st2[root].tag=0;
    st2[root*2].tag+=k;
    st2[root*2+1].tag+=k;
    st2[root*2].sum+=(mid-l+1)*k;
    st2[root*2+1].sum+=(r-mid)*k;
}

void add2(int root,int l,int r,int x,int y,int k){
    if(l>=x&&r<=y){
        st2[root].tag+=k;
        st2[root].sum+=(r-l+1)*k;
        return;
    }
    int mid=(l+r)/2;
    push_down2(root,l,r);
    if(mid>=x)
        add2(root*2,l,mid,x,y,k);
    if(mid+1<=y)
        add2(root*2+1,mid+1,r,x,y,k);
}

void ask2(int root,int l,int r,int x){
    if(l==r){
        res2=st2[root].sum;
        return;
    }
    int mid=(l+r)/2;
    push_down2(root,l,r);
    if(mid>=x)
        ask2(root*2,l,mid,x);
    else
        ask2(root*2+1,mid+1,r,x);
}

// 主函数中处理修改和查询操作
while(m--){
    int opt;
    opt=read();
    if(opt==0){
        int x,y,k;
        x=read();
        k=read();
        y=read();
        if(x==1){
            add2(1,1,n,1,y+1,k);
            continue;
        }
        add1(1,1,n,dfn[x],min(dfn[x]+y,bt[x]),k);
        if(dep[x]-2>=y)
            add1(1,1,n,dfn[x]-y,dfn[x]-1,k);
        else{
            if(tp[x]!=dfn[x])
                add1(1,1,n,tp[x],dfn[x]-1,k);
            int DEP=y-(dep[x]-dep[id[tp[x]]]);
            add2(1,1,n,1,DEP,k);
            if(DEP!=1)
                add1(1,1,n,tp[x],min(tp[x]+DEP-2,bt[x]),-k);
        }
    }
    else{
        int x;
        x=read();
        res1=0;
        ask1(1,1,n,dfn[x]);
        res2=0;
        ask2(1,1,n,dep[x]);
        printf("%d\n",res1+res2);
    }
}
```
核心实现思想：用两棵线段树，一棵基于时间戳维护链上修改，另一棵基于深度维护根节点相关修改，修改时根据不同情况分别操作两棵线段树，查询时将两棵线段树的结果相加。

### 最优关键思路或技巧
利用树的特殊结构（根下挂链

---
处理用时：139.47秒