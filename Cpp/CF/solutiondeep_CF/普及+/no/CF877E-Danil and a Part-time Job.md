# 题目信息

# Danil and a Part-time Job

## 题目描述

Danil decided to earn some money, so he had found a part-time job. The interview have went well, so now he is a light switcher.

Danil works in a rooted tree (undirected connected acyclic graph) with $ n $ vertices, vertex $ 1 $ is the root of the tree. There is a room in each vertex, light can be switched on or off in each room. Danil's duties include switching light in all rooms of the subtree of the vertex. It means that if light is switched on in some room of the subtree, he should switch it off. Otherwise, he should switch it on.

Unfortunately (or fortunately), Danil is very lazy. He knows that his boss is not going to personally check the work. Instead, he will send Danil tasks using Workforces personal messages.

There are two types of tasks:

1. pow v describes a task to switch lights in the subtree of vertex $ v $ .
2. get v describes a task to count the number of rooms in the subtree of $ v $ , in which the light is turned on. Danil should send the answer to his boss using Workforces messages.

A subtree of vertex $ v $ is a set of vertices for which the shortest path from them to the root passes through $ v $ . In particular, the vertex $ v $ is in the subtree of $ v $ .

Danil is not going to perform his duties. He asks you to write a program, which answers the boss instead of him.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF877E/76e99838c9d4f0aba9dd5ef366e55343e705a02b.png)The tree before the task pow 1.![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF877E/85a6f3926b45c5e1223a87bdba96341efa237d37.png)The tree after the task pow 1.

## 样例 #1

### 输入

```
4
1 1 1
1 0 0 1
9
get 1
get 2
get 3
get 4
pow 1
get 1
get 2
get 3
get 4
```

### 输出

```
2
0
0
1
2
1
1
0
```

# AI分析结果

### 题目内容
#### Danil和兼职工作
1. **题目描述**：Danil决定赚些钱，所以他找了一份兼职工作。面试进行得很顺利，现在他是一名灯光切换员。Danil在一棵有$n$个顶点的有根树（无向连通无环图）中工作，顶点$1$是树的根。每个顶点都有一个房间，每个房间的灯可以打开或关闭。Danil的职责包括切换顶点子树中所有房间的灯。这意味着如果子树中某个房间的灯是打开的，他应该关闭它。否则，他应该打开它。不幸的是（或者幸运的是），Danil非常懒惰。他知道他的老板不会亲自检查工作。相反，老板会通过Workforces私信向Danil发送任务。有两种类型的任务：
    - “pow v”描述的任务是切换顶点$v$子树中的灯。
    - “get v”描述的任务是计算$v$子树中灯打开的房间数量。Danil应该通过Workforces消息将答案发送给他的老板。顶点$v$的子树是一组顶点，从它们到根的最短路径经过$v$。特别地，顶点$v$在$v$的子树中。
2. **说明/提示**：[此处为两张图片链接，描述树在任务“pow 1”前后的状态，因无法直接展示，略过]
3. **样例 #1**
    - **输入**：
```
4
1 1 1
1 0 0 1
9
get 1
get 2
get 3
get 4
pow 1
get 1
get 2
get 3
get 4
```
    - **输出**：
```
2
0
0
1
2
1
1
0
```

### 算法分类
树状数组（通过DFS序将树结构问题转化为线性结构问题，再利用线段树进行区间操作和查询）

### 题解综合分析与结论
这些题解的核心思路均是利用DFS序将树上的子树操作转化为序列上的区间操作，然后借助线段树来高效地实现区间修改和区间查询。
1. **思路方面**：都先通过DFS遍历获取树中每个节点的DFS序，利用子树的DFS序连续这一性质，将对树中子树的操作映射到对序列区间的操作。
2. **算法要点**：
    - **DFS序获取**：通过DFS函数记录每个节点进入和离开的时间戳，或者记录子树大小等信息，确定子树在序列中的区间范围。
    - **线段树构建与操作**：构建线段树来维护序列信息，针对“pow”操作，通过修改线段树节点的标记和值来实现区间取反；针对“get”操作，通过查询线段树区间和得到子树中灯打开的房间数量。
3. **解决难点**：主要难点在于理解并实现如何将树结构问题转化为序列问题，以及正确处理线段树的延迟标记。在处理延迟标记时，要注意标记的下传方式以及对区间和的影响，确保在区间修改和查询时结果的正确性。

### 所选的题解
1. **作者：SalomeJLQ (5星)**
    - **关键亮点**：思路清晰，详细阐述了从树到序列的转化过程以及线段树的具体修改思路。代码注释详细，对每个关键函数都有清晰的说明，便于理解。
    - **重点代码**：
```cpp
//对树搜索 
void dfs(ll u,ll fa)
{
    dfn[u]=++cnt,num[cnt]=u;
    for(ll i=head[u];i;i=edge[i].nxt)
    {
        ll v=edge[i].to;
        if(v==fa)continue;
        dfs(v,u);
    }
    out[u]=cnt;
}

//下传延迟标记 
void spread(ll p)
{
    if(t[p].tag)
    {
        t[p<<1].val=t[p<<1].size-t[p<<1].val;
        t[p<<1|1].val=t[p<<1|1].size-t[p<<1|1].val;
        t[p<<1].tag^=1,t[p<<1|1].tag^=1;
        t[p].tag=0;
    }
}

//区间修，只要有递归就下传标记 
void change(ll p,ll l,ll r)
{
    if(l<=t[p].l&&r>=t[p].r)
    {
        t[p].val=t[p].size-t[p].val,t[p].tag^=1;
        return;
    }
    spread(p);
    int mid=t[p].l+t[p].r>>1;
    if(l<=mid)change(p<<1,l,r);
    if(r>mid)change(p<<1|1,l,r);
    t[p].val=t[p<<1].val+t[p<<1|1].val;
    t[p].size=t[p<<1].size+t[p<<1|1].size;
}

//区间查，只要有递归就下传标记 
ll ask(ll p,ll l,ll r)
{
    if(l<=t[p].l&&r>=t[p].r)
        return t[p].val;
    spread(p);
    ll mid=t[p].l+t[p].r>>1,ans=0;
    if(l<=mid)ans+=ask(p<<1,l,r);
    if(r>mid)ans+=ask(p<<1|1,l,r);
    return ans;
}

//建树，注意num的映射 
void build(ll p,ll l,ll r)
{
    t[p].l=l,t[p].r=r;
    if(l==r)
    {
        t[p].val=a[num[l]],t[p].size=1;
        return;
    }
    ll mid=l+r>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    t[p].val=t[p<<1].val+t[p<<1|1].val;
    t[p].size=t[p<<1].size+t[p<<1|1].size;
}
```
    - **核心实现思想**：`dfs`函数用于获取节点的DFS序，`spread`函数负责延迟标记的下传，`change`函数实现区间修改，`ask`函数实现区间查询，`build`函数构建线段树，并通过`num`数组建立树上节点和序列元素的对应关系。
2. **作者：jun头吉吉 (4星)**
    - **关键亮点**：代码采用了自定义的输入输出优化，在处理大数据时效率更高。对DFS序和线段树的原理有清晰的解释，代码结构清晰，每个功能模块独立成函数。
    - **重点代码**：
```cpp
//DFS求子树信息 
void dfs(int x,int fa)
{
    dfn[x]=++tot,size[x]=1;
    for(int i=head[x];i;i=e[i].nxt)
        if(e[i].v!=fa)dfs(e[i].v,x),size[x]+=size[e[i].v];
}

//下传延迟标记 
void pushdown(int x)
{
    if(tag(x)){
        tag(lson)^=1,val(lson)=r(lson)-l(lson)+1-val(lson);
        tag(rson)^=1,val(rson)=r(rson)-l(rson)+1-val(rson);
        tag(x)=0;
    }
} 

//区间修改 
void change(int x,int l,int r){//将[l,r]取反 
    if(r<l(x)||r(x)<l)return;
    if(l<=l(x)&&r(x)<=r){
        tag(x)^=1;
        val(x)=r(x)-l(x)+1-val(x);
        return;
    }
    pushdown(x);
    change(lson,l,r);
    change(rson,l,r);
    pushup(x);
}

//区间查询 
int query(int x,int l,int r)
{
    if(r<l(x)||r(x)<l)return 0;
    if(l<=l(x)&&r(x)<=r)return val(x);
    pushdown(x);
    return query(lson,l,r)+query(rson,l,r); 
}

//建树 
void build(int x,int l,int r)
{
    l(x)=l,r(x)=r;tag(x)=0;
    if(l==r){val(x)=a[l];return;}
    build(lson,l(x),mid(x));
    build(rson,mid(x)+1,r(x));
    pushup(x);
}
```
    - **核心实现思想**：`dfs`函数确定节点的DFS序和子树大小，`pushdown`函数下传延迟标记，`change`函数完成区间取反操作，`query`函数查询区间和，`build`函数构建线段树。
3. **作者：genshy (4星)**
    - **关键亮点**：对题目分析详细，明确指出了利用DFS序性质和线段树维护区间和及区间取反的思路，并强调了线段树标记操作中的注意事项。代码简洁明了，变量命名有意义。
    - **重点代码**：
```cpp
//dfs求dfs序
void dfs(int x,int fa)
{
    size[x] = 1; dfn[x] = ++num; w[dfn[x]] = a[x];
    for(int i = head[x]; i; i = e[i].net)
    {
        int to = e[i].to;
        if(to == fa) continue;
        dfs(to,x);
        size[x] += size[to];
    }
}

//下放标记
void down(int o)
{
    if(tag(o) == -1)
    {
        cover(o<<1); cover(o<<1|1);
        tag(o) = 1;
    }
}

//区间取反
void chenge(int o,int L,int R)
{
    if(L <= l(o) && R >= r(o))
    {
        cover(o); return;
    }
    down(o);
    int mid = (l(o) + r(o))>>1;
    if(L <= mid) chenge(o<<1,L,R);
    if(R > mid) chenge(o<<1|1,L,R);
    up(o);
}

//区间和
int ask(int o,int L,int R)
{
    int ans = 0;
    if(L <= l(o) && R >= r(o)) {return sum(o);}
    down(o);
    int mid = (l(o) + r(o))>>1;
    if(L <= mid) ans += ask(o<<1,L,R);
    if(R > mid) ans += ask(o<<1|1,L,R);
    return ans;
}

//建树
void build(int o,int L,int R)
{
    l(o) = L, r(o) = R; tag(o) = 1;//tag初始化一定要为1
    if(L == R)
    {
        sum(o) = w[L]; return;
    }
    int mid = (L + R)>>1;
    build(o<<1,L,mid);
    build(o<<1|1,mid+1,R);
    up(o);
}
```
    - **核心实现思想**：`dfs`函数获取DFS序及子树大小信息，`down`函数下放标记，`chenge`函数实现区间取反，`ask`函数查询区间和，`build`函数构建线段树，特别注意`tag`标记初始化为1。

### 最优关键思路或技巧
1. **DFS序应用**：利用DFS序将树结构转化为线性序列，使得对树中子树的操作能够转化为对序列区间的操作，大大简化了问题的处理难度。
2. **线段树延迟标记**：通过合理设置和下传延迟标记，优化区间修改操作，避免每次修改都直接更新所有节点，提高了算法效率。在本题中，延迟标记用于记录区间取反操作，当下传标记时，根据标记调整子区间的和及标记状态。

### 拓展思路
同类型题通常围绕树结构上的区间操作展开，常见的套路是利用DFS序、树链剖分等技术将树问题转化为序列问题，再结合线段树、树状数组等数据结构进行处理。例如，可能会改变树的权值类型或操作类型，但核心思路类似。

### 推荐洛谷题目
1. **P3372 【模板】线段树 1**：基础的线段树区间修改、区间查询模板题，帮助巩固线段树的基本操作。
2. **P3384 【模板】树链剖分**：经典的树链剖分模板题，通过树链剖分将树转化为线性结构，结合线段树进行操作，与本题思路相关。
3. **P1501 积木城堡**：涉及到树的DFS序和区间修改操作，可进一步加深对树结构与序列操作转化的理解。 

---
处理用时：98.01秒