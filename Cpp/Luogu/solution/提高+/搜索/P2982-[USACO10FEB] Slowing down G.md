# [USACO10FEB] Slowing down G

## 题目描述

Every day each of Farmer John's N $(1 \le N \le 100,000)$ cows conveniently numbered $1..N$ move from the barn to her private pasture. The pastures are organized as a tree, with the barn being on pasture $1$. Exactly $N-1$ cow unidirectional paths connect the pastures; directly connected pastures have exactly one path. Path $i$ connects pastures $A_i$ and $B_i$ $(1 \le A_i \le N,1 \le B_i \le N)$.

Cow $i$ has a private pasture $P_i(1 \le P_i \le N)$. The barn's small door lets only one cow exit at a time; and the patient cows wait until their predecessor arrives at her private pasture. First cow $1$ exits and moves to pasture $P_1$. Then cow $2$ exits and goes to pasture $P_2$, and so on.

While cow $i$ walks to $P_i$ she might or might not pass through a pasture that already contains an eating cow. When a cow is present in a pasture, cow $i$ walks slower than usual to prevent annoying her friend.

```cpp
Consider the following pasture network, where the number between
parentheses indicates the pastures' owner.

        1 (3)        
       / \
  (1) 4   3 (5)
     / \   
(2) 2   5 (4)

First, cow 1 walks to her pasture:

        1 (3)        
       / \
  [1] 4*  3 (5)
     / \   
(2) 2   5 (4)

When cow 2 moves to her pasture, she first passes into the barn's
pasture, pasture 1. Then she sneaks around cow 1 in pasture 4 before
arriving at her own pasture.

        1 (3)
       / \
  [1] 4*  3 (5)
     / \   
[2] 2*  5 (4)

Cow 3 doesn't get far at all -- she lounges in the barn's pasture, #1.

        1* [3]
       / \
  [1] 4*  3 (5)
     / \   
[2] 2*  5 (4)

Cow 4 must slow for pasture 1 and 4 on her way to pasture 5:

        1* [3]
       / \
  [1] 4*  3 (5)
     / \   
[2] 2*  5* [4]

Cow 5 slows for cow 3 in pasture 1 and then enters her own private pasture:

        1* [3]
       / \
  [1] 4*  3*[5]
     / \   
[2] 2*  5* [4]
```

FJ would like to know how many times each cow has to slow down.

每天 Farmer John 的 $N$ 头奶牛，编号 $1 \ldots N$，从粮仓走向他的自己的牧场。牧场构成了一棵树，粮仓在 $1$ 号牧场。恰好有 $N-1$ 条道路直接连接着牧场，使得牧场之间都恰好有一条路径相连。第 $i$ 条路连接着 $A_i$ 和 $B_i$。奶牛们每人有一个私人牧场 $P_i$。粮仓的门每次只能让一只奶牛离开。耐心的奶牛们会等到他们的前面的朋友们到达了自己的私人牧场后才离开。首先奶牛 $1$ 离开，前往 $P_1$；然后是奶牛 $2$，以此类推。

当奶牛 $i$ 走向牧场 $P_i$ 的时候，他可能会经过正在吃草的同伴旁。当路过已经有奶牛的牧场时，奶牛 $i$ 会放慢自己的速度，防止打扰他的朋友。

FJ 想要知道奶牛们总共要放慢多少次速度。

## 说明/提示

数据范围：$1 \leq A_i,B_i,P_i\leq N \leq 10^5$。

## 样例 #1

### 输入

```
5 
1 4 
5 4 
1 3 
2 4 
4 
2 
1 
5 
3 
```

### 输出

```
0 
1 
0 
2 
1 
```

# 题解

## 作者：insprition (赞：13)

线段树  dfs序

数据结构的应用


“数据结构 是先有需求 再有应用” by mzx dalao

那么按照这个思路

先看看针对这道题 有什么需求

再考虑用什么数据结构去解决

以及怎么用该数据结构


这是一个树上的题

某个牛进了牧场

只会影响到他子树的答案

因为只有他的 子树 回牧场时

才要经过他 得slowing down对吧


这时 要对他的 子树的答案全部 区间+1

这是 对dfs序的需求

需要 dfs序 将树转换成区间


区间修改 单点查询 又是对 线段树 的需求

需要 线段树 的高效维护

如有dalao有更高效的方法请[博客](http://www.cnblogs.com/1227xq/p/6847229.html)留言

我目前只学了线段树这个家伙啦


具体应用


dfs序
```cpp
void dfs(int u){
    dfn[u]=++cnt;//dfn[]为树转换为dfs序中的下标
    size[u]=1;//u为根的子树大小
    int v;
    for(int i=head[u];i;i=next[i]){
        v=to[i];
        if(dfn[v])continue;
        dfs(v);
        size[u]+=size[v];
    }
}
```
这样一棵子树 就对应了 dfn[]数组 的一段区间
以点k为根的 区间

左端点 是 dfn[k],

右端点 是 dfn[k] + size [k] - 1 。


线段树


         
         
 
```cpp
//main() 函数中的代码
for(int k,i=1;i<=n;i++){
      k=read();
      //单点查询
      printf("%d\n",query(dfn[k],root));
      //区间修改
      update(dfn[k],dfn[k]+size[k]-1,root);
}
//其他函数
 void pushdown(int rt){//懒标记下传
    if(!add[rt])return;
    add[rt<<1]+=add[rt];
    add[rt<<1|1]+=add[rt];
    add[rt]=0;
}
void update(int x,int y,int l,int r,int rt){
    if(x<=l&&r<=y){
        add[rt]++;//区间修改时 针对本题 懒标记+1 
        return;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    if(x<=mid)update(x,y,lson);
    if(mid<y)update(x,y,rson);
}
int query(int k,int l,int r,int rt){
    //单点查询 所以线段树只用 懒标记add[]数组 即可
    if(l==r)return add[rt];
    pushdown(rt);
    int mid=(l+r)>>1;
    if(k<=mid)return query(k,lson);
    return query(k,rson);
}
```
这样就 滋瓷 了本题的修改与查询操作
完

总代码

         
         
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100015
#define root 1,n,1
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
int n,cnt;
int head[N],next[N<<1],to[N<<1];
int dfn[N],size[N];
int add[N<<2];
int read(){
    int ans=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar());
    for(;isdigit(ch);ch=getchar())
        ans=(ans<<3)+(ans<<1)+ch-'0';
    return ans;
}
void ad(int from,int too){
    next[++cnt]=head[from];
    to[cnt]=too;
    head[from]=cnt;
}
void dfs(int u){
    dfn[u]=++cnt;//dfn[]为树转换为dfs序中的下标
    size[u]=1;//u为根的子树大小
    int v;
    for(int i=head[u];i;i=next[i]){
        v=to[i];
        if(dfn[v])continue;
        dfs(v);
        size[u]+=size[v];
    }
}
void pushdown(int rt){//懒标记下传
    if(!add[rt])return;
    add[rt<<1]+=add[rt];
    add[rt<<1|1]+=add[rt];
    add[rt]=0;
}
void update(int x,int y,int l,int r,int rt){
    if(x<=l&&r<=y){
        add[rt]++;//区间修改时 针对本题 懒标记+1 
        return;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    if(x<=mid)update(x,y,lson);
    if(mid<y)update(x,y,rson);
}
int query(int k,int l,int r,int rt){
    //单点查询 所以线段树只用 懒标记add[]数组 即可
    if(l==r)return add[rt];
    pushdown(rt);
    int mid=(l+r)>>1;
    if(k<=mid)return query(k,lson);
    return query(k,rson);
}
int main(){
    n=read();
    for(int x,y,i=1;i<n;i++){
        x=read(),y=read();
        ad(x,y);
        ad(y,x);
    }
    cnt=0;
    dfs(1);
    for(int k,i=1;i<=n;i++){
        k=read();
        //单点查询
        printf("%d\n",query(dfn[k],root));
        //区间修改
        update(dfn[k],dfn[k]+size[k]-1,root);
    }
    return 0;
}
```

---

## 作者：老咸鱼了 (赞：5)

这题的前置知识是前向星和树状数组或者线段树，这里因为是单点修改区间查询，所以我们用树状数组方便点。
题目大意是从根节点往下搜，只要搜到它的祖先里面有比他小的节点那么他就要等一次，计算总共等几次。

核心代码就这么些
```cpp
void dfs(int u,int fa)
{
	int k=a[u];//这个节点的牛的编号
	ans[k]=sum(k-1);//查询这头牛要等的牛的总数
	add(k,1);//单点修改
	for(int i=0;i<q[u].size();i++)
	{
		int t=q[u][i];
		if(t==fa)//题目是双向边所以不能搜到父亲节点
		continue;
		dfs(t,u);
	}
	add(k,-1);//回溯
}
```
//
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>q[100001];
int a[100001],num[100001],ans[100001];
int lowbit(int x)
{
	return -x & x;
}
void add(int x,int k)
{
	while(x<=n)
	{
		num[x]+=k;
		x+=lowbit(x);
	}
}
int sum(int x)
{
	int s=0;
	while(x>0)
	{
		s+=num[x];
		x-=lowbit(x);		
	}
	return s;
}
void dfs(int u,int fa)
{
	int k=a[u];
	ans[k]=sum(k-1);
	add(k,1);
	for(int i=0;i<q[u].size();i++)
	{
		int t=q[u][i];
		if(t==fa)
		continue;
		dfs(t,u);
	}
	add(k,-1);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		q[u].push_back(v);
		q[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		int t;
		scanf("%d",&t);
		a[t]=i;
	}
	dfs(1,1);
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：FutureThx (赞：3)

### 题目大意

一共有 $N$ 头奶牛，$N$ 个牧场，$N-1$ 条道路将牧场连接成树状，每头奶牛都有一个私人牧场，第 $i$ 头奶牛的私人牧场记作 $P_i$ 。

一开始所有奶牛都聚集在 $1$ 号节点，然后从 $1-N$ 每次第 $i$ 头奶牛去往其私人牧场 $P_i$ ，问对于每一头奶牛它返回的路途上经过多少个奶牛已返回的牧场。

### 解题思路

套路题，考虑如何将整棵树转换成一个序列然后上数据结构维护。

显然可以用 dfs 序，但接着又一个问题如何维护这个序列。

dfs 序有一个性质：当两个节点的 LCA 为其中一个的时候，其在 dfs 序上 ```in``` 时刻区间或者 ```out``` 时刻区间即为两个节点的唯一路径。

这里 ```in``` 表示节点进入 dfs 的时刻，```out``` 表示离开 dfs 的时刻。

所以根据这个性质，我们就很容易用线段树维护了。

### 代码

```cpp
#include <iostream> 
#include <vector>
using namespace std;
#define MAX_N 100010
struct Tree{
	vector<int> next;
}node[MAX_N];
int n,p[MAX_N],in[MAX_N],out[MAX_N],B[MAX_N],A[MAX_N],t = 0;
void dfs(int u,int fa){
	B[++t] = u;
	in[u] = t;
	for(int i = 0;i < node[u].next.size();i++){
		int v = node[u].next[i];
		if(v != fa)dfs(v,u);
	}
	B[++t] = u;
	out[u] = t;
}
struct SegmentTree{
	int lson,rson,sum;
}tree[MAX_N * 8];
void build(int l,int r,int p){
	tree[p].lson = l;
	tree[p].rson = r;
	if(l == r){
		tree[p].sum = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l,mid,p << 1);
	build(mid + 1,r,p << 1 | 1);
	tree[p].sum = 0;
}
void change(int x,int a,int p){
	if(tree[p].lson == tree[p].rson && tree[p].lson == x){
		tree[p].sum = a;
		return;
	}
	int mid = (tree[p].lson + tree[p].rson) >> 1;
	if(x <= mid)change(x,a,p << 1);
	else change(x,a,p << 1 | 1);
	tree[p].sum = tree[p << 1].sum + tree[p << 1 | 1].sum;
}
int query(int L,int R,int p){
	if(tree[p].lson == L && tree[p].rson == R)
		return tree[p].sum;
	int mid = (tree[p].lson + tree[p].rson) >> 1;
	if(R <= mid)return query(L,R,p << 1);
	else if(L > mid)return query(L,R,p << 1 | 1);
	else return query(L,mid,p << 1) + query(mid + 1,R,p << 1 | 1);
}
int qnode(int u){
	return query(in[1],in[p[u]],1);
}
void updnode(int u){
	change(in[p[u]],1,1);
	change(out[p[u]],-1,1);
	return;
}
int main(){
	cin >> n;
	for(int i = 1;i < n;i++){
		int u,v;
		cin >> u >> v;
		node[u].next.push_back(v);
		node[v].next.push_back(u);
	}
	dfs(1,-1);
	build(1,2 * n,1);
	for(int i = 1;i <= n;i++)cin >> p[i];
	for(int i = 1;i <= n;i++){
		cout << qnode(i) << endl;
		updnode(i); 
	}
	return 0;
}
```


## 后记

Updata 2021.6.13 : 完成题解


---

## 作者：asd_a (赞：3)

# 简直就是树剖模板题！！！
我直接把[P3384 【模板】树链剖分](https://www.luogu.org/problemnew/show/P3384)的代码复制过来，只改了输入与输出就A了（当然dfs+线段树做）  
好了，步入正题：  
初始化一个值都为0的线段树存储树剖，每输入一个$P_i$就查询$1$到$P_i$路径上之和，再将$P_i$在线段树中的值改为1，供后续查询。  
上代码：
```
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,R=1,P=1e9+7;//R为根，%P防爆
int fi[N],ne[N<<1],to[N<<1],seg[N],dad[N],son[N],top[N],rev[N],siz[N],dep[N],tot;
/*
邻接表存边，son为重儿子，top为重链顶，dep为深度，
siz为子树大小，seg为线段树中编号，rev[seg[x]]=x
*/
struct L_TREE{
    int sum,lzy;//lazy标记，习惯了
}t[N<<2];
inline void add(int x,int y){ne[++tot]=fi[x];to[tot]=y;fi[x]=tot;}
inline void ad(int x,int y){add(x,y);add(y,x);}
inline void up(int x){t[x].sum=(t[x<<1].sum+t[x<<1|1].sum)%P;}
inline void usd(int x,int l,int r,int k)
{
    t[x].lzy=(t[x].lzy+k)%P;
    t[x].sum=(t[x].sum+k*(r-l+1))%P;
}
inline void down(int x,int l,int r)
{
    int mid=(l+r)>>1;
    usd(x<<1,l,mid,t[x].lzy);
    usd(x<<1|1,mid+1,r,t[x].lzy);
    t[x].lzy=0;
}
inline void dfs1(int x,int fa)
{
    dep[x]=dep[fa]+1;
    siz[x]=1;
    dad[x]=fa;
    for(int i=fi[x];i;i=ne[i])
    {
        int y=to[i];
        if(y!=fa)
        {
            dfs1(y,x);
            siz[x]+=siz[y];
            if(siz[y]>siz[son[x]])son[x]=y;
        }
    }
}
inline void dfs2(int x,int fa)
{
    if(son[x])
    {
        seg[son[x]]=++seg[0];
        top[son[x]]=top[x];
        rev[seg[0]]=son[x];
        dfs2(son[x],x);
    }
    for(int i=fi[x];i;i=ne[i])
    {
        int y=to[i];
        if(y!=fa && y!=son[x])
        {
            seg[y]=++seg[0];
            rev[seg[0]]=y;
            top[y]=y;
            dfs2(y,x);
        }
    }
}//树剖预处理
inline void update(int now,int l,int r,int L,int R,int x)
{
    if(L<=l&&R>=r)
    {
        t[now].sum=(t[now].sum+(r-l+1)*x)%P;
        t[now].lzy=(t[now].lzy+x)%P;
        return ;
    }
    down(now,l,r);
    int mid=(l+r)>>1;
    if(L<=mid) update(now<<1,l,mid,L,R,x);
    if(R>mid)update(now<<1|1,mid+1,r,L,R,x);
    up(now);
}
inline int query(int now,int l,int r,int L,int R)
{
    if(L<=l&&R>=r) return t[now].sum;
    int mid=(l+r)>>1,anss=0;
    down(now,l,r);
    if(L<=mid) anss=(anss+query(now<<1,l,mid,L,R))%P;
    if(R>mid) anss=(anss+query(now<<1|1,mid+1,r,L,R))%P;
    return anss%P;
}
inline int askline(int x,int y)
{
    int fx=top[x],fy=top[y],anss=0;
    while(fx!=fy)
    {
        if(dep[fx]<dep[fy]) swap(x,y),swap(fx,fy);//深度大的往上跳
        anss=(anss+query(1,1,n,seg[fx],seg[x]))%P;
        x=dad[fx];fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    anss=(anss+query(1,1,n,seg[x],seg[y]))%P;
    return anss%P;
}
int main()
{
    cin>>n;
    int x,y,z;
    for(int i=1;i<n;i++)	cin>>x>>y,ad(x,y);
    dfs1(R,0);
    seg[0]=seg[R]=1;
    top[R]=rev[1]=R;
    dfs2(R,0);
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        cout<<askline(1,x)<<endl;
        update(1,1,n,seg[x],seg[x],1);
    }
    return 0;
}
```

---

## 作者：HSY666 (赞：2)

这道题虽然是一道线段树或树状数组模板题 ~~（也可以用树剖，不过树剖码量有点大qwq）~~，但是非常有价值，需要点思维。

由题目可知，每一只奶牛走的路线，都只在其中一条链上，再根据题目要求，容易发现每只奶牛的答案其实就是它所在的家（也就是树上的节点）的祖先所住的奶牛中，序号比它小的奶牛数量。

口胡一个证明：因为每个奶牛都从根节点出发，所以设树上节点的深度为 $ dep $ ，奶牛经过的节点为 $ i $ ，奶牛的家为 $ n $ ，则对于每一个 $ i $ 有 $ dep_i \leqslant dep_n $ ，又因为树上任意两个节点的路径唯一，所以所有的 $ i $ 一定都是 $ n $ 的祖先。又序号小的奶牛先到家，所以只有序号小的奶牛对答案有贡献，因此上述结论成立，证毕。

考虑怎么统计答案。考虑暴力，先深搜找点，然后暴力枚举祖先，统计奶牛编号小于该节点奶牛编号的数量。然而这样时间复杂度是 $ O(n^2) $ 的，肯定过不了。

考虑用数据结构优化，其实有很多数据结构都可以用，比如树剖，树状数组，线段树。这里只说线段树做法。因为只有修改和查询操作，所以码量还是很少的，也很好理解。

我们定义一颗线段树，每个节点存的是当前状态下序号在区间 $ \left[ l , r \right ] $ 中的奶牛的数量，然后在向下深搜时，将这个节点的奶牛序号所在区间在线段树上都加一，并顺便统计答案，设奶牛编号为 $ x $ ，当前区间为 $ \left[ l , r \right ] $ ，区间中点为 $ mid $ ，先修改这个区间的值，显然当 $ x \leqslant mid $ 时，对答案没有贡献，继续修改左子树；当 $ x > mid $ 时，对答案的贡献为当前区间的左儿子的值，更新答案后继续修改右子树，在回溯时再将这个节点的奶牛序号所在区间在线段树上都加一即可。由于修改和查询都是 $ O(\log n) $ 的，又每个点一次加一次删（查询在加入时已顺便统计），所以总的时间复杂度为 $ O(2 n \log n) $ ，忽略常数就是 $ O(n \log n) $ 。

上代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n,cow[100005],u,v,tre[400005],ret[100005];
bool vis[100005];
vector <int> e[100005];

void add (int x,int l,int r,int y)
{
	++tre[x];
	if (l==r)  return ;
	int mid=(l+r)/2;
	if (y<=mid)  add(x*2,l,mid,y);
	else
	{
		ret[y]+=tre[x*2];  //顺便统计答案
		add(x*2+1,mid+1,r,y);
	}
}

void del (int x,int l,int r,int y)
{
	--tre[x];
	if (l==r)  return ;
	int mid=(l+r)/2;
	if (y<=mid)  del(x*2,l,mid,y);
	else  del(x*2+1,mid+1,r,y);
}

void dfs (int x)
{
	add(1,1,n,cow[x]);
	vis[x]=1;
	for (int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if (vis[y])  continue;
		dfs(y);
	}
	del(1,1,n,cow[x]);  //回溯时删除
}

int main ()
{
	scanf ("%d",&n);
	for (int i=1;i<n;++i)
	{
		scanf ("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i=1;i<=n;++i)
	{
		int a;
		scanf ("%d",&a);
		cow[a]=i;
	}
	dfs(1);
	for (int i=1;i<=n;++i)
	{
		printf ("%d\n",ret[i]);
	}
	return 0;
}
```


---

## 作者：Argentum (赞：2)

## 由数据标签可以发现，这是一道树状数组的水题

题意大致是对一棵树上进行若干次操作，每次操作时先查询当前节点到根的路径上所有点权的和，然后使当前节点的权值+1

那么瓶颈在于统计路径上的点权和

~~直接熟练剖分即可~~

但作为新时代的青年，我们要有开拓精神（大雾）

于是我们点开数据标签：“树状数组”

很自然地可以想到，对于每一条从根出发的路径建立一个树状数组进行统计（请类比AC自动机）~~（突然玄学）~~

~~（我简直忘了有dfs序这种好东西，但没有关系）~~

对于每一个节点x定义一个数组NEXT[]（此处我使用了vector降低了空间复杂度），指向x子树中所有满足dep[v]=dep[x]+lowit(x)的子节点。直接求NEXT显然不怎么方便，于是我们反过来，每搜到一个节点时将其压入它的每一个前驱的NEXT中：

```c
void dfsson(re x)
{
	vis[x]=1;
	for(re v,i=h[x];i;i=e[i].next)
	if(!vis[v=e[i].to])
	dfsson(v);
	for(re i=round(log((double)lowbit(dep[x]))/log(2.0)-1);i>=0;i--)
	NEXT[fa[x][i]].push_back(x);
	vis[x]=0;
}
```
~~浮点误差是个巨坑~~

father数组利用倍增预处理即可

剩下的事情就完全类似普通的树状数组了

注意存在多头牛共享私人牧场的情况
~~（私人？）~~

插值和查询的代码:
```c
inline void add(re x)
{
	val[x]++;
	for(re i=0;i<NEXT[x].size();i++)
	add(NEXT[x][i]);
}
int query(re x)
{
	if(!x)return 0;
	re last=round(log((double)lowbit(dep[x]))/log(2.0));
	return val[x]+query(fa[x][last]);
}
```
完整代码如下：
```c
#include<bits/stdc++.h>
#define MAXN 1000005
#define re register int
using namespace std;
typedef long long ll;
ll read()
{
	ll ret=0,f=1;char ch=getchar();
	while('0'>ch||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){ret=(ret<<3)+(ret<<1)+(ch^48);ch=getchar();}
	return ret*f;
}
struct edge
{
	int to,next;
}e[MAXN<<1];
int h[MAXN],fa[MAXN][18];
int dep[MAXN],pos[MAXN],val[MAXN];//pos存放奶牛的私人牧场，val是节点的权值
int n,m,top;
bool vis[MAXN];
vector<int> NEXT[MAXN];
int lowbit(re x)
{return x&(-x);}
inline void ins(re u,re v)
{
	e[++top].to=v;
	e[top].next=h[u];
	h[u]=top;
}
void dfsfa(re x)
{
	vis[x]=1;
	for(re i=1;(1<<i)<=dep[x];i++)
	fa[x][i]=fa[fa[x][i-1]][i-1];
	for(re v,i=h[x];i;i=e[i].next)
	if(!vis[v=e[i].to])
	{
		fa[v][0]=x;
		dep[v]=dep[x]+1;
		dfsfa(v);
	}
	vis[x]=0;
}
void dfsson(re x)
{
	vis[x]=1;
	for(re v,i=h[x];i;i=e[i].next)
	if(!vis[v=e[i].to])
	dfsson(v);
	for(re i=round(log((double)lowbit(dep[x]))/log(2.0)-1);i>=0;i--)
	NEXT[fa[x][i]].push_back(x);
	vis[x]=0;
}
inline void add(re x)
{
	val[x]++;
	for(re i=0;i<NEXT[x].size();i++)
	add(NEXT[x][i]);
}
int query(re x)
{
	if(!x)return 0;
	re last=round(log((double)lowbit(dep[x]))/log(2.0));
	return val[x]+query(fa[x][last]);
}
int main()
{
	n=read();
	re u,v;
	for(re i=1;i<n;i++)
	{
		u=read();
		v=read();
		ins(u,v);
		ins(v,u);
	}
	for(re i=1;i<=n;i++)
	pos[i]=read();
	dep[1]=1;
	dfsfa(1);
	dfsson(1);
	for(re i=1;i<=n;i++)
	{
		printf("%d\n",query(pos[i]));
		add(pos[i]);
	}
	return 0;
}
```


---

## 作者：123hh2 (赞：1)

--->[传送门](https://www.luogu.com.cn/problem/P2982)

---

### 前言

upd:2021.7.1 改正了一些已知错误 qwq

这是一道树剖板子题，如果不会树剖的可以先左转--->[传送门](https://www.luogu.com.cn/problem/P3384)

---

### 题目大意

给你一棵树，给你 $q$ 个点，依次将这些点赋值为 $1$ 并输出出从 $1$ 到这个点的路径上的点权之和

**注意**：初始时这棵树上的每个点的点权值都为 $0$

---
### 思路

我们能够想到树剖可以 $\log^2n$ 求出 $[1,q]$ 的权值和,所以我们就可以先整一个树剖板子上来

然后对于给出的 $q$ 个点可以看成是修改区间 $[q,q]$ 为 $1$

所以我们在树剖的基础上将原询问改成修改区间和求权值和就好了

---

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define in inline
#define ri register
#define _123hh2 0
using namespace std;
in int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
in void write(int x)
{
    if(x<0) {x=-x;putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int maxn=3e5+1;
struct awa
{
	int nxt,to;
}edge[maxn];
int head[maxn],cnt;
int n,m,s;
inline void add(int u,int v)
{
	edge[++cnt].to=v;edge[cnt].nxt=head[u];head[u]=cnt;
}
int a[maxn],lazy[maxn],tree[maxn],neww[maxn];
inline void pushup(int rt)
{
	tree[rt]=tree[rt<<1]+tree[rt<<1|1];
	tree[rt];
}
inline void build(int rt,int l,int r)
{
	lazy[rt]=0;
	if(l==r)
	{
		tree[rt]=neww[l];
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);build(rt<<1|1,mid+1,r);
	pushup(rt);
}
inline void pushdown(int rt,int l,int r)
{
	if(!lazy[rt]) return;
	int mid=(l+r)>>1;
	lazy[rt<<1]+=lazy[rt];lazy[rt<<1|1]+=lazy[rt];
	tree[rt<<1]+=lazy[rt]*(mid-l+1);
	tree[rt<<1|1]+=lazy[rt]*(r-mid);
	lazy[rt]=0;
}
inline void update(int rt,int l,int r,int ql,int qr,int k)
{
	if(qr<l||r<ql) return ;
	if(ql<=l&&r<=qr) 
	{
		tree[rt]+=k*(r-l+1);
		lazy[rt]+=k;
		return;
	}
	pushdown(rt,l,r);
	int mid=(l+r)>>1;
	update(rt<<1,l,mid,ql,qr,k);
	update(rt<<1|1,mid+1,r,ql,qr,k);
	pushup(rt);
}
inline int query(int rt,int l,int r,int ql,int qr)
{
	if(qr<l||r<ql) return 0;
	if(ql<=l&&r<=qr) return tree[rt];
	pushdown(rt,l,r);
	int mid=(l+r)>>1;
	return (query(rt<<1,l,mid,ql,qr)+query(rt<<1|1,mid+1,r,ql,qr));
}
int deep[maxn],top[maxn],id[maxn],fa[maxn],size[maxn];
inline void updated(int x,int y,int k)
{
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]]) swap(x,y);
		update(1,1,n,id[top[x]],id[x],k);
		x=fa[top[x]];
	}
	if(deep[x]>deep[y]) swap(x,y);
	update(1,1,n,id[x],id[y],k);
}
inline int querysum(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]]) swap(x,y);
		int res=query(1,1,n,id[top[x]],id[x]);
		ans=(ans+res);
		x=fa[top[x]];
	}
	if(deep[x]>deep[y]) swap(x,y);
	int res=query(1,1,n,id[x],id[y]);
	ans=(ans+res);
	return ans;
}
inline void updateson(int u,int k)
{
	update(1,1,n,id[u],id[u]+size[u]-1,k);
}
inline int queryson(int u)
{
	return query(1,1,n,id[u],id[u]+size[u]-1);
}
int son[maxn];
inline void dfs1(int u,int f)//
{
	size[u]=1;fa[u]=f;deep[u]=deep[f]+1;
	for(int i=head[u];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(v==f) continue;
		dfs1(v,u);
		size[u]+=size[v];size[u]; 
		if(size[v]>size[son[u]]) son[u]=v;
	}
}
int dfn;
inline void dfs2(int u,int topf)//
{
	id[u]=++dfn;neww[dfn]=a[u];top[u]=topf;
	if(!son[u]) return;
	dfs2(son[u],topf);
	for(int i=head[u];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
signed main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v),add(v,u);//双向边
	}
	dfs1(1,0);dfs2(1,1);build(1,1,n);//正常树剖处理
	for(int i=1;i<=n;i++)
	{
		int x=read();
		write(querysum(1,x)),puts("");//这里直接输出权值
		updated(x,x,1);//看成区间修改就好了
	}
    return _123hh2;
}
```

---

## 作者：编程客 (赞：1)

## 关于自己
- 刚看到这道题很懵逼……想了几十分钟，放弃了。结果看到另一道题，联想到这道题就有思路了……
- 让后很快就`AC`了。
## 思路
- 看到`树状数组`时很难想，但看到`DFS`的时候就可以思考一下了。

- 这道题实际上求的是枚举每一头牛，把这头牛的目标点的状态设为1。实际求这头牛的目标点到根节点中状态为一的点的个数。

- 接着思考一下，我们定义一个数组`a[N]`，`a[i]`表示这个点的牛主人，就是说，第`a[i]`次牛的行走的目标点为`a[i]`。

- 深捜一遍，每到节点`x`的时候实际上是求所有从根节点到此节点路径上的点中`a[i]`值比`a[x]`小的点的个数。

- 然后就能够想到如何用树状数组来做了。

- 总体思路：深捜一遍，每到节点`x`的时候`ans[sum(x)]++`,再用树状数组在`add(x,1)`，然后枚举所有子节点，遇到非父节点就递归。枚举完子节点后，再`add(x,-1)`。

- 最好自己好好想一下。
## Code

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define lowbit(x) x&-x 
const int N=100005;
using namespace std;
int n,m,c[N],cnt;
int a[N],ans[N];
vector<int> g[N];
void add(int x,int d)				//模板 
{
	while(x<=n)
	{
		c[x]+=d;
		x+=lowbit(x);
	}
}
int sum(int x)
{
	int s=0;
	while(x>0)
	{
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
void dfs(int u,int fa)				//深捜 
{
	ans[a[u]]=sum(a[u]);			//所有比他小的节点个数 
	add(a[u],1);
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fa) continue;			//非父节点 
		dfs(v,u);
	}
	add(a[u],-1);
}
int main()
{
	scanf("%d",&n);
    for(int i=1;i<n;i++)			//读边 
    {
    	int u,v;
    	scanf("%d%d",&u,&v);
    	g[u].push_back(v);
    	g[v].push_back(u);
	}
	for(int i=1;i<=n;i++)			//为树上每个节点编号 
	{
		int x;
		scanf("%d",&x);
		a[x]=i;
	}
	dfs(1,0);						//深捜求答案 
	for(int i=1;i<=n;i++)			//输出 
	{
		printf("%d\n",ans[i]);
	}
    return 0;
}
```

#### 希望此篇题解对你有帮助！

---

## 作者：abandentsky (赞：1)

思路：先按测试样例画个树形图。大概这样
                       （1）
                     （3）（4）
                         （2）（5）；
 图就是这样了。我是按楼下某大佬的思路做的。（刚开始用的修土路的思路处理的，结果答案不正确。不知道哪里错了。）先说这个题。按题目给的数据，dfs序列为：1->4->5->2->3。好了，现在我们可以知道每个牛棚对应一个奶牛，而奶牛是由编号的。奶牛回棚是按奶牛的编号走的。那么我们在回牛棚的路上统计比自己编号小的有几个不就好了。（编号比自己小的有几个，这不就是求前缀和嘛。）完事儿，当访问这个节点（牛棚）结束就减去这个节点（牛棚）所对应编号减一。这样，他就不会影响其他节点了嘛。（此时你可以想想dfs实现过程就明白了为啥减去了。他不对比他大的奶牛编号做贡献，但是在前缀和序列里，为了不影响就得减去。）这样，就可以解决所有问题了。
按之前思路，一号牛棚对应三号奶牛。（那么三号牛要慢几次，完全取决于这条路径上小于3的有几个，就是0了）。四号牛棚对应一号奶牛。（比1小的没有，就是0了）五号牛棚对应四号奶牛。（比四小的有1和3，加起来就是2）。完了退出五号牛棚，所以就减去五号牛棚对应奶牛编号（减一）。也就是四号奶牛减一。（因为他比五号奶牛编号大，但是不是五号奶牛的父节点，不做贡献，但是影响前缀和）。之后是二号牛棚，对应二号奶牛。（比二号奶牛编号小的有1号奶牛，故为1）。之后二号奶牛减一，一号减一。三号牛棚对应五号奶牛，（比5小的有1,2,3,4这个时候可以注意到1,2,4已经被减为0了，这个时候只有3号做贡献，所以就是1了）。

```c
#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#define MAXN  100005
using namespace std;

int n,m,tot;
vector<int> G[MAXN];
bool vis[MAXN];
int c[MAXN];
int cnt[MAXN];
int d[MAXN];

int lowbit(int x)
{
    return (x&((-1)*x));
}

void add(int x,int d)
{
    while(x<=n)
    {
        c[x]+=d;
        x+=lowbit(x);
    }
}

int sum(int x)
{
    int ans=0;
    while(x>0)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}

void dfs(int u,int fa)
{
    vis[u]=true;
    int kk=cnt[u];                   //其实序就是1,2,3,4,5
    d[kk]=sum(cnt[u]);          //某个奶牛（奶牛是有序的，从一号开始回自己的农场）求前缀和
    //printf("第%d头奶牛的值为%d\n",kk,d[kk]);
    add(kk,1);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(vis[v])
            continue;
        dfs(v,u);
    }
    add(kk,-1);
}

int main()
{
    scanf("%d",&n);
    //tot=0;
    memset(vis,false,sizeof(vis));
    for(int i=1;i<n;i++)
    {
        int uu,vv;
        scanf("%d %d",&uu,&vv);
        G[uu].push_back(vv);
        G[vv].push_back(uu);
    }
    for(int i=1;i<=n;i++)
    {
        int op;
        scanf("%d",&op);
        cnt[op]=i;                     //将节点编号映射成奶牛编号
    }
    dfs(1,-1);
    for(int i=1;i<=n;i++)
    {
       printf("%d\n",d[i]);
    }
    return 0;
}

```


---

## 作者：秋日私语 (赞：1)

原文点[这里](https://blog.csdn.net/A_Comme_Amour/article/details/79722330)

题目
-
[传送门](https://www.luogu.org/problemnew/show/P2982)
题解
-

这道题还是比较好的；

我们先考虑树形成一条链的情况，那就成了单点修改 区间查询操作，都是线段树的基本操作；

那么我们就使用dfs序的方法，把它变成一条链，那么某棵子树的区间就是 dfn[i]+tot[i]-1，进行区间修改，单点查询；

通过dfs序，我们实现了从二维降到一维，类似“索引表”的思想，大家可以去看看这道题—[海港](https://blog.csdn.net/a_comme_amour/article/details/78384395)
代码
-

```
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn=1000001;
const int inf=1e9;

int n,m,tot[maxn],dfn[maxn],idfn[maxn],a[maxn];
struct Node{
    int sum,tag;
}tree[maxn<<1|1];
struct Edge{
    int next,to;
}edge[maxn<<1];
int num_edge=-1,head[maxn];

void add_edge(int from,int to)
{
    edge[++num_edge].next=head[from];
    edge[num_edge].to=to;
    head[from]=num_edge;
}

int cnt;
void dfs(int x,int fa)
{
    dfn[x]=++cnt; 
	idfn[cnt]=x;
    tot[x]=1;
    for (int i=head[x]; i!=-1; i=edge[i].next)
    {
        int to=edge[i].to;
        if (to!=fa) 
		{
			dfs(to,x);
			tot[x]+=tot[to];
		}
    }
}

void pushup(int rt) {tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;}
void pushdown(int rt,int ln,int rn)
{
    if (tree[rt].tag)
    {
        tree[rt<<1].tag+=tree[rt].tag;
		tree[rt<<1|1].tag+=tree[rt].tag;
        tree[rt<<1].sum+=tree[rt].tag*ln;
        tree[rt<<1|1].sum+=tree[rt].tag*rn;
        tree[rt].tag=0;
    }
}

void change(int L,int R,int C,int l,int r,int rt)
{
    if (L<=l && r<=R){
        tree[rt].sum+=(r-l+1)*C; tree[rt].tag+=C; return;
    }
    int mid=(l+r)>>1;
    pushdown(rt,mid-l+1,r-mid);
    if (L<=mid) change(L,R,C,l,mid,rt<<1);
    if (R>mid)  change(L,R,C,mid+1,r,rt<<1|1);
    pushup(rt);
}

int ques(int x,int l,int r,int rt)
{
    if (l==r && x==l) return tree[rt].sum;
    int mid=(l+r)>>1;
    pushdown(rt,mid-l+1,r-mid);
    if (x<=mid) return ques(x,l,mid,rt<<1);
    else return ques(x,mid+1,r,rt<<1|1);
}

int main()
{
	memset(head,-1,sizeof(head));
    scanf("%d",&n); 
    for (int i=1; i<=n-1; i++)
    {
        int x,y; scanf("%d%d",&x,&y);
        add_edge(x,y); add_edge(y,x);
	}
//  for (int i=0; i<=num_edge; i++) printf("%d: %d %d\n",i,edge[i^1].to,edge[i].to);
    dfs(1,0);
    for (int i=1; i<=n; i++)
    {
    	int x; scanf("%d",&x);// printf("%d %d\n",dfn[x],dfn[x]+tot[x]-1);
		printf("%d\n",ques(dfn[x],1,n,1));
		change(dfn[x],dfn[x]+tot[x]-1,1,1,n,1);
	}
//    for (int i=1; i<=n; i++) printf("%d %d\n",idfn[i],tot[idfn[i]]);
    return 0;
}
```


总结
-
我考虑到了如果使用暴力的话相当于把每个点标记一个深度，然后就相当于一个无向图进行搜索，与dfs序有相通之处；

通过这道题终于明白了树链剖分中dfn数组的用处

---

## 作者：Mychael (赞：1)

庆祝300通过！写一个题解。

**看起来好像dfs加求和【树状数组】就可以了**


在从父节点dfs到每个节点的过程中，对于节点u，他有几个祖先访问顺序【也就是奶牛编号】比他小，他就要停几次

所以在遍历过程中把每个节点所对应的奶牛编号+1，在遍历完该节点后-1【改回来，因为不同树上的节点互不影响，而该节点的儿子都访问完了，不会有牛再经过这个节点了】


对于+1和求和操作，我蒟蒻用了个快一点的树状数组【这种点修改、区间询问[1,n]的用树状数组写多简洁】


附代码：




```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#include<algorithm>
#define lowerbit(x) (x&-x)
using namespace std;
const int maxn=100005,INF=2000000000;
int d[maxn],A[maxn],own[maxn],L,R,N;  //d是答案,A是树状数组,own是节点与奶牛编号的映射
int read()   //快速读入
{
    int out=0,flag=1;char c=getchar();
    while(c<48||c>57) {if(c=='-') flag=-1;c=getchar();}
    while(c>=48&&c<=57){out=out*10+c-48;c=getchar();}
    return out*flag;
}
int head[maxn],nedge=0;
class EDGE                //链式前向星
{
```
public:




```cpp
        int to,next;
}edge[maxn*3];
inline void addedge(int a,int b)
{
    edge[nedge]=(EDGE){b,head[a]};head[a]=nedge++;
    edge[nedge]=(EDGE){a,head[b]};head[b]=nedge++;
}
void update(int u,int v){while(u<=N) {A[u]+=v;u+=lowerbit(u);}} //树状数组部分
int sum(int u) {int tot=0;while(u>0){tot+=A[u];u-=lowerbit(u);} return tot;}//多紧凑
void dfs(int u,int fa)     //深搜求解
{
    int cow=own[u],to;
    d[cow]=sum(cow);
    update(cow,1);
    for(int k=head[u];k!=-1;k=edge[k].next)
        if((to=edge[k].to)!=fa)
            dfs(to,u);
    update(cow,-1);
}
int main()
{
    fill(head,head+maxn,-1);
    N=read();
    for(int i=1;i<N;i++) addedge(read(),read());  //链式前向星构图
    for(int i=1;i<=N;i++) own[read()]=i;  //记录每个节点对应的奶牛编号
    fill(A,A+maxn,0);
    dfs(1,0);
    for(int i=1;i<=N;i++) printf("%d\n",d[i]); //输出结果
    return 0;
}

```

---

## 作者：阿廖 (赞：1)

本题目可以理解为给出一颗n个节点的树，顺序激活每个点，并询问每个点到根的路径上经过了多少个已经激活的点。使用线段树+DFS序。与其他线段树不同，本题的线段树存储的是一个点的子树，所以用DFS序把树转化为线段来存。单点修改，区间求和。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct pig
{
    int end,next;
}a[200005];
int n,tot,head[200005],l[100005],r[100005],tree[400005];
inline void add(int x,int y)
{
    a[++tot].end=y,a[tot].next=head[x],head[x]=tot;
    return;
}
void dfs(int k,int f)
{
    l[k]=++tot;
    for(int i=head[k];i;i=a[i].next)
        if(a[i].end!=f)dfs(a[i].end,k);
    r[k]=tot;
    return;
}
int query(int l,int r,int k,int x)
{
    int mid=(l+r)>>1;
    if(l==r)return tree[k];
    if(x<=mid)return tree[k]+query(l,mid,k<<1,x);
    return tree[k]+query(mid+1,r,(k<<1)+1,x);
}
void insert(int l,int r,int k,int start,int end)  
{  
    int mid=(l+r)>>1;
    if(l==start && r==end){tree[k]++;return;}
    if(mid>=end)return insert(l,mid,k<<1,start,end);
    if(mid<start)return insert(mid+1,r,(k<<1)+1,start,end);
    return insert(l,mid,k<<1,start,mid),insert(mid+1,r,(k<<1)+1,mid+1,end);
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1,x,y;i<n;i++)cin>>x>>y,add(x,y),add(y,x);
    tot=0,dfs(1,0);
    for(int i=1,x;i<=n;i++)
    {
        cin>>x;
        cout<<query(1,n,1,l[x])<<endl;
        insert(1,n,1,l[x],r[x]);
    }
    return 0;
}
```

---

## 作者：嘒彼小星 (赞：1)


对于每只牛，我们很容易确定答案

我们设muchang[i]表示以节点i为目的地的奶牛编号，


那么对于奶牛k：

muchang[k]所有祖先节点集E的muchang[e],e∈E中，满足muchang[e] < muchang[k] 的e的个数就是奶牛k的答案。


详情见<http://www.cnblogs.com/huibixiaoxing/p/6849588.html>





```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) > (b) ? (b) : (a))
#define lowbit(a) ((a) & (-(a)))
int read()
{
    int x = 0;char ch = getchar();char c = ch;
    while(ch > '9' || ch < '0')c = ch, ch = getchar();
    while(ch <= '9' && ch >= '0')x = x * 10 + ch - '0', ch = getchar();
    if(c == '-')return -x;
    return x;
}
const int INF = 0x3f3f3f3f;
const int MAXN = 1000000 + 10;
int n,muchang[MAXN],ans[MAXN],head[MAXN],cnt,step,data[MAXN];
bool b[MAXN];
struct Edge{int u,v,next;}edge[MAXN];
void insert(int a,int b){edge[++cnt] = Edge{a, b, head[a]};head[a] = cnt;}
inline void modify(int x, int k){for(;k <= n;k += lowbit(k))data[k] += x;}
inline int ask(int k){int x = 0;for(;k;k -= lowbit(k))x += data[k];return x;}
void dfs(int x){
    b[x] = true;
    ans[muchang[x]] = ask(muchang[x]);
    modify(1, muchang[x]);
    for(int pos = head[x];pos;pos = edge[pos].next)
    {
        int y = edge[pos].v;
        if(b[y])continue;
        dfs(y);
    }
    modify(-1, muchang[x]);
}
int main()
{
    freopen("data.txt", "r", stdin);
    n = read();
    int tmp1,tmp2;
    for(int i = 1;i < n;i ++){
        tmp1 = read();tmp2 = read();
        insert(tmp1, tmp2);
        insert(tmp2, tmp1);
    }
    for(int i = 1;i <= n;i ++)
        muchang[read()] = i;
    dfs(1);
    for(int i = 1;i <= n;i ++)
        printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：Kiloio (赞：0)

## 简述题意  
在一棵以 $1$ 为**根**的树上，每个奶牛从**根**走向自己的点（就是牧场 $P_i$ ）。  
  
在它从根走向 $P_i$ 的**过程**中，会遇见其他**已经到达**的奶牛，求所有遇见次数。  
  
## 题目分析  
题目规定：恰好有 $N-1$ 条道路直接连接着根，所以**每个点之间是连通的**。  
  
直接在树上求解不方便，可以考虑用 dfs 序，将树变成**线段**区间维护。  
  
维护线段，可以选择**线段树**或者**树状数组**，这道题都可以。  
  
因为树状数组码量要小很多，我就选的树状数组。~~其实就是我懒~~    
  
但是，如果**简单的**用树状数组需要去维护相遇的次数，时间并不允许。  
  
- 查询没问题，正常时间复杂度 $\log_2{N}$ 。  

- 但修改就不行了，因为奶牛每次影响的是一个**区间**，而普通修改是针对的**单点**。  
  
接下来可以用**差分数组的思想**维护，也就是平常我们所说的树状数组**区间修改**。  
  
总结来说，这道题就是 dfs 序 + 树状数组 + 树上差分。  
  
要注意的地方代码里有。  
  
## 代码  
```
#include <bits/stdc++.h>
using namespace std;
int n,a,b,op,tot,last[200005],in[100005],out[100005],tim,tr[100005],vis[200005];
//in、out记录dfs序的数据，tr是树状数组维护次数用的变量 
struct node{
	int x,y,nex;
}e[200005];
int lowbit(int x){
	return x&(-x);
}
void add(int a,int b){//链式存图 
	tot++;
	e[tot].x=a,e[tot].y=b,e[tot].nex=last[a],last[a]=tot;
}
void dfs_build(int u,int fa){
	in[u]=++tim;
	for(int i=last[u]; i; i=e[i].nex){
		vis[i]=1;
		int v=e[i].y;
		if(in[v]){
			continue;
		}
		if(u!=v){
			dfs_build(v,u);
		}
	}
	out[u]=tim;
}
int get_sum(int x){//查询操作 
	int sum=0;
	for(int i=x; i>=1; i-=lowbit(i)){
		sum+=tr[i];
	}
	return sum;
}
void modify(int x,int k){//修改操作(区间) 
	for(int i=x; i<=n; i+=lowbit(i)){
		tr[i]+=k;
	}
}
int main(){
	cin>>n;
	for(int i=1; i<=n-1; i++){
		scanf("%d%d",&a,&b);
		add(a,b),add(b,a);//注意是无向图 
	}
	dfs_build(1,1);
	for(int i=1; i<=n; i++){
		scanf("%d",&op);
		//注意要先查询再修改，i号奶牛不会影响它自己，是i号以后的奶牛 
		cout<<get_sum(in[op])<<endl;
		modify(in[op],1),modify(out[op]+1,-1);
	}
	return 0;
}
```


---

## 作者：CG__HeavenHealer (赞：0)

### 题意

给一棵树，有 $m$ 个操作，每次操作先输出根节点到这个点的点权和，再修改这个点的权值为 $1$ 。

### 解法

如果把树上问题转换到序列，就是简单的单点修改，区间查询，显然可以用线段树或树状数组维护。

问题就在于能否将树上问题转换为序列问题。

如果了解过树链剖分的同学一定能想到：**DFS序**。

如果使用树状数组，我们可以用差分的思想，在第一次遍历一个待修改的节点时加1，回溯到时减1，这样求前缀和即可得到区间值；使用线段树的话直接修改、查询即可。

这里普及一个特殊的DFS序，也是本题解的核心思路：**欧拉序**。

欧拉序是指对于树上的每一个节点，第一次遍历到它时记录一下，在搜索回溯时再记录一下，所以**整个欧拉序长度为节点数的2倍**。（因为这个调了半天。。。）

在这段代码中， ```euler``` 数组记录了遍历时的欧拉序。

```cpp
int euler[N], dfn;
void dfs(int u, int fa) {
	euler[++dfn] = u;
	for (ri i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fa) continue;
		dfs(v, u);
	}
	euler[++dfn] = u;
}
```

但仅记录一个数组是不能够分清是第几次遍历的，所以我们用两个数组 ```id1``` ， ```id2``` 分别表示第一次遍历和搜索回溯时的时间戳。

这种做法其实等价于记录了一个欧拉序，所以**长度还是节点数的2倍**。

以下是DFS部分：

```cpp
int id1[N], id2[N], dfn;
void dfs(int u, int fa) {
	id1[++dfn] = u;
	for (ri i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fa) continue;
		dfs(v, u);
	}
	id2[++dfn] = u;
}
```

单点修改、区间查询就很简单了。

树状数组：

```
namespace BIT {
int tree[N];
#define lowbit(x) x&(-x)
inline void add(int x, int d) {
    for (; x <= n * 2; x += lowbit(x)) tree[x] += d;
}
inline int sum(int x) {
    int res = 0;
    for (; x; x -= lowbit(x)) res += tree[x];
    return res;
}
}  // namespace BIT
```

线段树：

```cpp
namespace SegmentTree {
int t[N << 2];
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
inline void push_up(int u) { t[u] = t[ls] + t[rs]; }
void update(int u, int l, int r, int pos, int val) {
    if (l == r && l == pos) return t[u] = val, void();
    if (pos <= mid)
        update(ls, l, mid, pos, val);
    else
        update(rs, mid + 1, r, pos, val);
    push_up(u);
}
int query(int u, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return t[u];
    int lson = query(ls, l, mid, ql, qr);
    int rson = query(rs, mid + 1, r, ql, qr);
    return lson + rson;
}
}  // namespace SegmentTree
```

### Code：

1.线段树版本：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ri register int
const int N = 2e5 + 10;
inline int read() {
    int x = 0;
    char ch = getchar();
    bool f = 1;
    while (!isdigit(ch)) {
        if (ch == '-') f = 0;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return f ? x : -x;
}
int n;
struct Edge {
    int to, nxt;
} e[N];
int head[N], cnt;
inline void link(int u, int v) {
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
#define Ergodic(u) for (ri i = head[u]; i; i = e[i].nxt)
int id1[N], id2[N], dfn, euler[N];
void dfs(int u, int fa) {
    id1[u] = dfn;
    Ergodic(u) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u);
    }
    id2[u] = dfn;
    return;
}
namespace SegmentTree {
int t[N << 2];
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
inline void push_up(int u) { t[u] = t[ls] + t[rs]; }
void update(int u, int l, int r, int pos, int val) {
    if (l == r && l == pos) return t[u] = val, void();
    if (pos <= mid)
        update(ls, l, mid, pos, val);
    else
        update(rs, mid + 1, r, pos, val);
    push_up(u);
}
int query(int u, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return t[u];
    int lson = query(ls, l, mid, ql, qr);
    int rson = query(rs, mid + 1, r, ql, qr);
    return lson + rson;
}
}  // namespace SegmentTree
using namespace SegmentTree;
signed main() {
    n = read();
    for (ri i = 1; i < n; i++) {
        int u = read(), v = read();
        link(u, v), link(v, u);
    }
    dfs(1, 0);
    for (ri i = 1; i <= n; i++) {
        int x = read();
        printf("%lld\n", query(1, 1, 2 * n, id1[1], id1[x]));
        update(1, 1, 2 * n, id1[x], 1);
        update(1, 1, 2 * n, id2[x], -1);
    }
    return 0;
}
```

2.树状数组版本：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ri register int
const int N = 2e5 + 10;
inline int read() {
    int x = 0;
    char ch = getchar();
    bool f = 1;
    while (!isdigit(ch)) {
        if (ch == '-') f = 0;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return f ? x : -x;
}
int n;
struct Edge {
    int to, nxt;
} e[N];
int head[N], cnt;
inline void link(int u, int v) {
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
#define Ergodic(u) for (ri i = head[u]; i; i = e[i].nxt)
int id1[N], id2[N], dfn;
void dfs(int u, int fa) {
    id1[u] = dfn;
    Ergodic(u) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u);
    }
    id2[u] = dfn;
    return;
}
namespace BIT {
int tree[N];
#define lowbit(x) x&(-x)
inline void add(int x, int d) {
    for (; x <= n * 2; x += lowbit(x)) tree[x] += d;
}
inline int sum(int x) {
    int res = 0;
    for (; x; x -= lowbit(x)) res += tree[x];
    return res;
}
}  // namespace BIT
using namespace BIT;
signed main() {
    n = read();
    for (ri i = 1; i < n; i++) {
        int u = read(), v = read();
        link(u, v), link(v, u);
    }
    dfs(1, 0);
    for (ri i = 1; i <= n; i++) {
        int x = read();
        printf("%lld\n", sum(id1[x]));
        add(id1[x], 1);
        add(id2[x], -1);
    }
    return 0;
}
```



---

## 作者：Na2PtCl6 (赞：0)

## 分析题目
这题的难点在于如何将树上问题转化为区间问题。

### 前置知识：dfs序
顾名思义，就是在一棵树上跑一遍 dfs ，然后按顺序记录下走到的点是第几个被遍历到的点。

dfs 的本质是 **深度优先** ，即的顺序是由根向叶子，所以一个节点在 dfs 序中的 $[ ord_x,ord_x + size_i - 1]$ （$ord_x$ 指 $x$ 的 dfs 序， $size_i$ 是以 $i$ 为根的子树的大小）就是这个节点子树对应的区间。

### 维护子树加，单节点询问
既然已经转化为区间问题了，我们就可以用树状数组差分来维护这个东西了。

我们顺序遍历每一头牛，先查询该头牛所在点的值，再把每头牛所在节点的子树加 $1$。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100004;
char vis[maxn],res[maxn<<3];
int n,u,v,p,cnt;
int head[maxn],to[maxn<<1],nxt[maxn<<1],ord[maxn],treesz[maxn],tree[maxn];

inline void read(int &x){
	char c=getchar();bool f=0;x=0;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-')
			f=1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+(c^48);
	x=f?-x:x;
}

void save(const int x){
	if(x>9)
		save(x/10);
	res[++cnt]=x%10+48;
}

inline void add_edge(const int &a,const int &b){
	++cnt;
	to[cnt]=b;
	nxt[cnt]=head[a];
	head[a]=cnt;
}

inline const int lowbit(const int &x){ return x&-x;}

void add(int p,int v){
	while(p<=n){
		tree[p]+=v;
		p+=lowbit(p);
	}
}

int sum(int p){
	int ans=0;
	while(p){
		ans+=tree[p];
		p-=lowbit(p);
	}
	return ans;
}

void dfs(int node,int fa){
	ord[node]=++cnt; 
	treesz[node]=1;  //不要定义成size,有可能会CE 
	for(int i=head[node];i;i=nxt[i]){
		if(to[i]==fa)
			continue;
		dfs(to[i],node);
		treesz[node]+=treesz[to[i]];
	}
}

int main(){
	read(n);
	for(int i=1;i<n;i++){
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	cnt=0;
	dfs(1,0);
	cnt=0;
	for(int i=1;i<=n;i++){
		read(p);
		save(sum(ord[p]));
		res[++cnt]='\n';
		add(ord[p],1);
		add(ord[p]+treesz[p],-1);
	}
	fwrite(res+1,1,cnt,stdout);
	return 0;
}		
```

---

## 作者：brealid (赞：0)

**这篇题解用的确实都是已有的解法，但是它对已有的两种解法进行了梳理，帮助读者比较两者在两方面上的优劣**

---

简单梳理一下这道题可以用的两种方法  

首先基础是：**dfs序+区间数据结构(线段树，树状数组)**

## 1. 树链剖分（对于每个节点考虑“从哪里来”）
对于每个点，查询从这个节点到根节点经过了多少个有奶牛的点，作为其 $ans$  
可以处理一个点就输出这个点的 $ans$  
因此需要 **树链剖分**   
时间复杂度：$n$ 个节点 $\times$ 树链剖分的 $\log n$ 段链 $\times$ 区间查询(区间加)的 $\log n$，总时间复杂度 $O(n \log^2 n)$  

优点是可以**在线查询**  
缺点是**时间复杂度较大，常数相对较大**，不过足已通过本题  

代码: [传送门](https://gitee.com/hkxa/mycode/blob/master/luogu/P2982.cpp)

## 2. dfs 序（对于每个节点考虑“到哪里去”）
对于每个点，使其所有子树的 $ans = ans + 1$  
最后处理完每个点后再输出每个点的 $ans$  
不需要 **树链剖分**，仅需要 **dfs序**  
时间复杂度：$n$ 个节点 $\times$ 区间查询(区间加)的 $\log n$，总时间复杂度 $O(n \log n)$  

优点是**时间复杂度较小，常数相对较小**，可以应对时间卡的比较严格的题目   
缺点是不可以**在线查询** 

这种代码就不贴了，大部分题解都是这种

---

## 作者：Baihua (赞：0)

### 题解 P2982 【[USACO10FEB]慢下来Slowing down】

[博客内阅读](https://www.cnblogs.com/bj2002/p/10432150.html)

- 题目大意 ：给出一棵树，节点有点权，求每个节点的**祖先**中点权小于该节点的结点的个数 。

- 思路如下 ：

  - 从根节点开始，对树进行深度优先遍历。
  - 当进行到节点 i 时，有：
    -  $\text{i}$ 的祖先们 $\text{Father[i]}$ 已经被访问过了，但还没有退出。
    - 其他节点或者已经被访问过并退出了，或者还没有被访问。
  - 那么需要一个数据结构，维护那些**已经被访问过了，但还没有退出的点权**，支持查询**小于特定值的元素的数量** 。
  - 可以使用**树状数组**或者**线段树**。

- Code

  ```
  #include <cstdio>
  #include <cstring>
  #define re register
  #define GC getchar()
  #define Clean(X,K) memset(X,K,sizeof(X))
  #define Lowbit(X) (X&(-X))
  int Qread () {
      int X = 0 ;    char C = GC ;
      while (C > '9' || C < '0') C = GC ;
      while (C >='0' && C <='9') {
          X = X * 10 + C - '0' ;
          C = GC ;
      }
      return X ;
  }
  const int Maxn = 100005 ;
  int N ,  P_C[Maxn] , Ans[Maxn] , En = 0 , Head[Maxn] , T[Maxn];
  struct Edge {
      int From_Where , Goto_Where , Next_Edge ;
  };
  Edge E[Maxn * 2] ;
  void Adg (int X , int Y) {
      E[++En].From_Where = X ;
      E[En].Goto_Where = Y ;
      E[En].Next_Edge = Head[X] ;
      Head[X] = En ;
  }
  void Add (int X , int K) {
      while (X <= N) {
          T[X] += K ;
          X += Lowbit(X) ;
      }
  }
  int Ask (int X) {
      int Ans = 0 ;
      while (X > 0) {
          Ans += T[X] ;
          X -= Lowbit(X) ;
      }
      return Ans ;
  }
  void Super_Powerful_DFS (int X , int Lst) {
      Ans[P_C[X]] = Ask (P_C[X]) ;
      //printf ("%d %d %d\n" , X , P_C[X],Ans[P_C[X]]) ;
      Add (P_C[X] , 1) ;
      for (re int i = Head[X] ; i ; i = E[i].Next_Edge ) {
          if (E[i].Goto_Where == Lst) continue ;
          Super_Powerful_DFS ( E[i].Goto_Where , X) ;
      }
      Add (P_C[X] , -1) ;
  }
  int main () {
      //freopen ("P2982.in" , "r" , stdin) ;
      Clean (Ans , 0) , Clean (Head , 0) , Clean (T , 0) , En = 0 ;
      N = Qread () ;
      for (re int i = 1 ; i < N ; ++ i) {
          int X = Qread () , Y = Qread () ;
          Adg (X , Y) , Adg (Y , X) ;
      }
      for (re int i = 1 ; i <= N; ++ i) {
          int X = Qread () ;
          P_C[X] = i ;
      }
      Super_Powerful_DFS ( 1 , -1) ;
      for (re int i = 1 ; i <= N; ++ i) printf ("%d\n" , Ans[i]) ;
      fclose (stdin) ;
      fclose (stdout);
      return 0;
  }
  ```

  点击[这里](https://www.luogu.org/problemnew/show/P3374)学习树状数组

### Thanks ！

---

## 作者：AugustineYang (赞：0)

介绍一个通解想法，虽然可能在这道题上有点大材小用

原因是我觉得dfs太暴力不优雅

看到 “牧场构成了一棵树” 以及 “粮仓走向他的自己的牧场（树上从根到某一节点，即树上路径）”，可以想到树链剖分。

~~dfs暴力不优雅？树剖不是有两个dfs吗~~

首先说一下，树链剖分不是NOIP考点，如果目标是NOIP的暂时可以不掌握。

树链剖分的详细讲解在此→https://www.luogu.org/problemnew/solution/P3384

用树剖+树状数组（有单点修改，所以绝对比树剖+线段树快）解决，在线处理询问。

每一次输入一个奶牛的目标牧场，就询问该目标牧场到根的路径上点的权值和，然后把目标牧场点的权值+1

```cpp
#include <cstdio>
#include <cstring>
#include <cctype>
#define MAXN (int)(1e5+7)
using namespace std;
int n, num_edge, head[MAXN], p[MAXN], cnt;
int size[MAXN], son[MAXN], father[MAXN], dep[MAXN];
int top[MAXN], bit[MAXN];
int sum[MAXN];
struct add
{
	int to, next;
}edge[MAXN<<1];
int read()
{
	int tt = 0;
	char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c))
	{
		tt = (tt<<1)+(tt<<3)+(c&15);
		c = getchar();
	}
	return tt;
}
void add_edge(int from, int to)
{
	edge[++num_edge] = (add){to, head[from]};
	head[from] = num_edge;
}
void dfs1(int u, int fa)
{
	father[u] = fa;
	size[u] = 1;
	dep[u] = dep[fa]+1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int v = edge[i].to;
		if(v == fa) continue;
		dfs1(v, u);
		size[u] += size[v];
		if(size[v] > size[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int topu)
{
	top[u] = topu;
	bit[u] = ++cnt;
	if(!son[u]) return;
	dfs2(son[u], topu);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int v = edge[i].to;
		if(v==father[u] || v==son[u]) continue;
		dfs2(v, v);
	}
}
int lowbit(int x)
{
	return x&-x;
}
int query(int pos)
{
	int res = 0;
	while(pos)
	{
		res += sum[pos];
		pos -= lowbit(pos);
	}
	return res;
}
void update(int pos, int v)
{
	while(pos <= n)
	{
		sum[pos] += v;
		pos += lowbit(pos);
	}
} 
//因为计算的总是根(1)到某一点的距离，所以就做了个小改动
int query_path(int x) 
{
	int res = 0;
	while(1 != top[x])
	{
		res += query(bit[x])-query(bit[top[x]]-1);
		x = father[top[x]];
	}
	res += query(bit[x]);
	return res;
}
int main()
{
	n = read();
	for(int i=1; i<=n-1; ++i)
	{
		int x = read(), y = read();
		add_edge(x, y);
		add_edge(y, x);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	for(int i=1; i<=n; ++i)
	{
		int x = read();
		printf("%d\n", query_path(x));
		update(bit[x], 1);
	}
	return 0;	
}
```

---

## 作者：七条玲奈 (赞：0)

对于这题来说 我们跑一遍DFS 记录每个节点第一次被访问的时间和结束访问的时间

一个节点的所有子树就一定在它第一次被访问的时间到结束访问的时间之间

将它第一次被访问的时间c[graw[i]]++，结束访问的时间c[black[i]--，每次求解的时候只要求1~graw[p]的前缀和就行了
快速求前缀和？

树状数组啊！【滑稽】

下面上代码【代码写的丑QAQ】


```cpp
/*
DFS序
然后！！！对于每一个点来说 他的子节点就是graw[i]~black[i]这个区间
所以我们用差分
把c[graw[i]]++,c[black[i]]--
统计的时候直接跑一遍graw[i]前缀和就可以了
*/
#include <bits/stdc++.h>
using namespace std;
int n,c[100005];
int numm[100005],ans;
int black[100005],graw[100005],cnt,next[200005],last[200005],Arrive[200005],Time;
void jt(int x,int y) {
	cnt++;
	next[cnt]=last[x];
	last[x]=cnt;
	Arrive[cnt]=y;
}
void dfs(int r,int fa) {
	Time++;
	graw[r]=Time;
	for (int i=last[r]; i; i=next[i]) {
		if (Arrive[i]!=fa)
			dfs(Arrive[i],r);
	}
	Time++;
	black[r]=Time;
}
int lowbit(int kk) {
	return kk&(-kk);
}
void add(int wz,int x) {
	for (int i=wz; i<=2*n; i+=lowbit(i))
		c[i]+=x;
}
int summ(int From) {
	int ans=0;
	for (int i=From; i>0; i-=lowbit(i))
		ans+=c[i];
	return ans;
}
int main() {
	scanf("%d",&n);
	for (int i=1; i<=n-1; i++) {
		int xx,yy;
		scanf("%d%d",&xx,&yy);
		jt(xx,yy);
		jt(yy,xx);
	}
	dfs(1,0);
	for (int i=1; i<=n; i++) {
		int p;
		scanf("%d",&p);
		printf("%d\n",summ(graw[p]));
		add(graw[p],1);
		add(black[p],-1);
	}
	return 0;
}
```

---

## 作者：Adove (赞：0)

区间修改单点查询居然没人写zkw线段树；

我们先确定数据贡献的范围，对某节点的牛会且只会影响以该节点为根的整棵子树；

树上问题我们通常需要用到dfs序；

对于一棵树来说，某节点及其子树的dfs序必然在一段连续的区间内，原因是dfs遍历时先遍历根节点，后遍历子树的各个节点。

这样我们就可以对dfs序进行操作了。

上代码↓

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN=(1<<17)-1;

int n,x,y,np;
int tree[MAXN<<1],tp[MAXN],siz[MAXN],h[MAXN];
struct rpg{
    int li,nx;
}a[MAXN<<1];

inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}return x;
}

void add(int ls,int nx){
    a[++np]=(rpg){h[ls],nx};
    h[ls]=np;
}

void dfs(int x){
    tp[x]=++tp[0];
    siz[x]=1;
    for(int i=h[x];i;i=a[i].li){
        if(!tp[a[i].nx]){
            dfs(a[i].nx);
            siz[x]+=siz[a[i].nx];
        }
    }return;
}

void init(){
    scanf("%d",&n);
    for(int i=1;i<n;++i){
        x=read(),y=read();
        add(x,y);add(y,x);
    }return;
}

void solve(){
    dfs(1);
    for(int i=1;i<=n;++i){
    	x=read();
    	int ct=tp[x]+MAXN,sum=0;
    	while(ct){
    		sum+=tree[ct];
    		ct>>=1;
		}printf("%d\n",sum);
        int l=MAXN+tp[x]-1,r=MAXN+tp[x]+siz[x];
        while(l^r^1){
        	if(~l&1) ++tree[l^1];
        	if(r&1) ++tree[r^1];
        	int ct=min(tree[l],tree[l^1]);
        	tree[l]-=ct;tree[l^1]-=ct;
        	tree[l>>=1]+=ct;
        	ct=min(tree[r],tree[r^1]);
        	tree[r]-=ct;tree[r^1]-=ct;
        	tree[r>>=1]+=ct;
		}while(l){
			int ct=min(tree[l],tree[l^1]);
			tree[l]-=ct;tree[l^1]-=ct;
			tree[l>>=1]+=ct;
		}
	}return;
}

int main(){
    init();
    solve();
    return 0;
}
```

---

## 作者：Dispwnl (赞：0)

用$dfs$序储存每个点到1号点的距离和路线，因为没有值所以只用储存懒标记

懒标记表示$1$号点到自己农场这段区间有多少回到农场的牛，当一头牛走时目标点$+1$，并顺便下推懒标记

 ![](https://a-failure.github.io/img/study/slowdown.png) 

如图所示（样例），当去$2$的牛走时，必定经过$4$号点，$4$号点已经有牛了，所以下推标记，$5$号点、$2$号点懒标记各$+1$

最后统计每个点懒标记

代码：
```
# include<iostream>
# include<cstdio>
# include<cstring>
using namespace std;
struct p{
    int x,y;
}c[200001];
struct q{
    int dfn,l;
}d[100001];
int n,num,tot;
int lazy[400001],h[100001];
void add(int x,int y)
{
    c[++num].x=h[x];
    c[num].y=y;
    h[x]=num;
}
void dfs(int x)
{
    d[x].dfn=++tot;
    for(int i=h[x];i;i=c[i].x)
      if(!d[c[i].y].dfn)
      dfs(c[i].y),d[x].l+=d[c[i].y].l;
}
void down(int k)
{
    lazy[k<<1]+=lazy[k];
    lazy[k<<1|1]+=lazy[k];
    lazy[k]=0;
}
void change(int x,int y,int k,int l,int r)
{
    if(l>=x&&r<=y)
    {
        lazy[k]++;
        return;
    }
    if(lazy[k]) down(k);
    int mid=(l+r)>>1;
    if(x<=mid) change(x,y,k<<1,l,mid);
    if(y>mid) change(x,y,k<<1|1,mid+1,r); 
}
int ask(int x,int k,int l,int r)
{
    if(l==r)
    return lazy[k];
    if(lazy[k]) down(k);
    int mid=(l+r)>>1;
    if(x<=mid) return ask(x,k<<1,l,mid);
    else return ask(x,k<<1|1,mid+1,r);
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
      d[i].l=1;
    for(int i=1;i<n;i++)
      {
          int x,y;
          cin>>x>>y;
          add(x,y);
          add(y,x);
      }
    dfs(1);
    for(int i=1;i<=n;i++)
      {
          int x;
          cin>>x;
          cout<<ask(d[x].dfn,1,1,n)<<endl;
          change(d[x].dfn,d[x].dfn+d[x].l-1,1,1,n);
      }
    return 0;
}
```
也可以用树链剖分做

处理出每一条链后，每次回自己农场时，剖分统计区间和，然后自己农场值$+1$

跑的还不慢，$O_2$后$200ms$左右

代码：
```
# include<iostream>
# include<cstdio>
# include<cstring>
#define mid ((l+r)>>1)
#define tl (k<<1)
#define tr (k<<1|1)
#define ini inline int
#define inv inline void
#define is isdigit(ch)
using namespace std;
const int MAX=1e5+1;
struct p{
    int x;
}s[MAX<<2];
struct q{
    int x,y;
}c[MAX<<1];
int n,num,cnt;
int h[MAX],id[MAX],top[MAX],son[MAX],fa[MAX],siz[MAX],d[MAX];
ini read()
{
    int x=0;
    char ch=getchar();
    while(!is) ch=getchar();
    while(is)
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x;
}
inv add(int x,int y)
{
    c[++num].x=h[x];
    c[num].y=y;
    h[x]=num;
}
void dfs(int x,int f)
{
    d[x]=d[f]+1;
    fa[x]=f;
    siz[x]=1;
    for(int i=h[x];i;i=c[i].x)
      {
          int y=c[i].y;
          if(y==f) continue;
          dfs(y,x);
          siz[x]+=siz[y];
          if(siz[son[x]]<siz[y])
          son[x]=y;
      }
}
void dfs1(int x,int tp)
{
    top[x]=tp;
    id[x]=++cnt;
    if(son[x]) dfs1(son[x],tp);
    for(int i=h[x];i;i=c[i].x)
      {
          int y=c[i].y;
          if(y==fa[x]||y==son[x]) continue;
          dfs1(y,y);
      }
}
inv pus(int k)
{
    s[k].x=s[tl].x+s[tr].x;
}
void change(int l,int r,int k,int x)
{
    if(l==r)
    {
        s[k].x++;
        return;
    }
    if(x<=mid) change(l,mid,tl,x);
    else change(mid+1,r,tr,x);
    pus(k);
}
int ask(int l,int r,int k,int L,int R)
{
    if(l>=L&&r<=R)
    return s[k].x;
    if(l>R||r<L) return 0;
    return ask(l,mid,tl,L,R)+ask(mid+1,r,tr,L,R);
}
int ASK(int x,int y)
{
    int ans=0;
    while(top[x]!=top[y])
    {
        if(d[top[x]]<d[top[y]]) swap(x,y);
        ans+=ask(1,n,1,id[top[x]],id[x]);
        x=fa[top[x]];
    }
    if(d[x]>d[y]) swap(x,y);
    ans+=ask(1,n,1,id[x],id[y]);
    return ans;
}
int main()
{
    n=read();
    for(int i=1;i<n;i++)
      {
          int x=read(),y=read();
          add(x,y);
          add(y,x);
      }
    dfs(1,0);
    dfs1(1,1);
    for(int i=1;i<=n;i++)
      {
          int x=read();
          printf("%d\n",ASK(1,x));
          change(1,n,1,id[x]);
      }
    return 0;
}
```


---

