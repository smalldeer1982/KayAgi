# [Vani有约会] 雨天的尾巴 /【模板】线段树合并

## 题目背景

深绘里一直很讨厌雨天。

灼热的天气穿透了前半个夏天，后来一场大雨和随之而来的洪水，浇灭了一切。

虽然深绘里家乡的小村落对洪水有着顽固的抵抗力，但也倒了几座老房子，几棵老树被连根拔起，以及田地里的粮食被弄得一片狼藉。

无奈的深绘里和村民们只好等待救济粮来维生。

不过救济粮的发放方式很特别。

## 题目描述

村落里一共有 $n$ 座房屋，并形成一个树状结构。然后救济粮分 $m$ 次发放，每次选择两个房屋 $(x, y)$，然后对于 $x$ 到 $y$ 的路径上（含 $x$ 和 $y$）每座房子里发放一袋 $z$ 类型的救济粮。

然后深绘里想知道，当所有的救济粮发放完毕后，每座房子里存放的最多的是哪种救济粮。

## 说明/提示

- 对于 $20\%$ 的数据，保证 $n, m \leq 100$。
- 对于 $50\%$ 的数据，保证 $n, m \leq 2 \times 10^3$。
- 对于 $100\%$ 测试数据，保证 $1 \leq n, m \leq 10^5$，$1 \leq a,b,x,y \leq n$，$1 \leq z \leq 10^5$。

## 样例 #1

### 输入

```
5 3
1 2
3 1
3 4
5 3
2 3 3
1 5 2
3 3 3```

### 输出

```
2
3
3
0
2```

# 题解

## 作者：shadowice1984 (赞：191)

线段树合并板子题

 _对了，楼下的题解是假的可以被hack掉_ 
_____________

这里简单介绍一下线段树合并这种神奇的操作了

## 前置芝士：线段树合并

所谓线段树合并就是将两个线段树合并成一颗线段树的算法

下面的合并暂时可以理解成我们使用线段树维护了两个数组的一些信息(比如区间和，区间最大值之类的)，现在我们需要将这两个数组按位相加，同时得到这个数组所对应的线段树

问题来了线段树明明是好好的线段树我们为什么要合并它呢?

显然两个普通的线段树(也就是那种左儿子是p<<1右儿子是p<<1|1的线段树)没有必要专门设计一个算法合并它们，因为他们已经满了，换句话说我们直接把两个数组按位相加然后重新建一遍线段树可能是最快的方法了

但是线段树众所周知有很多的变体，比如说动态开点线段树，这种线段树很有可能不是满的，甚至只有一条链$O(logn)$个节点，这时候我们合并两个动态开点线段树的时候接着用刚才的方法合并可能就有些不妙了

那么当然这里有一个几乎对于所有数据结构都适用的合并算法叫做启发式合并，当我们合并两个动态开点线段树的时候我们就暴力的把小的线段树中的元素插入到大的线段树里面去。

不过我们会觉得其实这个算法也是有点暴力的，通过这种算法把n个仅有一个元素的动态开点线段树合并成一颗完整的大线段树的复杂度是O(nlog^2n)的

那这里就是线段树合并这个算法出场的时候了，这个算法合并两个动态开点线段树的复杂度是O(两个线段树重叠部分)的

那么我们是如何实现两个线段树合并起来的操作呢？

假设我们现在要把线段树2所对应的数组加到线段树1上

那么我们在两个线段树上同时进行dfs，然后我们dfs的时候判断一下左儿子是否同时有两个节点，如果同时有的话就进去dfs，否则我们看一下是线段树1没有左儿子还是线段树2没有左儿子，如果是线段树2没有左儿子的话我们什么事也不用干，因为线段树2对应的这部分区间全是0加了也白加。

然后如果是线段树1没有左儿子的话，我们发现此时的相加操作相当于把这一段区间全部换成线段树2所对应的区间，因此我们直接让线段树1的左儿子等于线段树2的左儿子就可以了(这一部分有点像主席树的工作方式，因为这样合并之后线段树1和线段树2将会共用一些节点)

当然对于右儿子也要采取同样的处理方式了

最后一个问题是这两个节点都是叶子，既没有左儿子也没有右儿子，那么我们直接将节点2加到节点1上然后返回就可以了

最后就是因为线段树1上左右儿子的信息会发生改变，我们需要对这个节点进行一次$update/pushup/merge$操作(不同人起不一样的函数名，但是干的应该都是同一件事情)

于是我们就成功完成了将两个线段树合并的操作辣~

那么我们可以证明的是，通过这种方法将n个只有1个元素的线段树合并成1个有n个元素的线段树的复杂度就是O(nlogn)的

为什么呢？

考虑我们刚才的算法流程，我们每次dfs一个节点，显然我们可以dfs到这个节点就证明这两个位置都有节点,我们发现合并之后属于线段树2的节点就不会被dfs到了(因为线段树1的节点替换了它的位置)，可能被dfs到的属于线段树2的节点是被接到线段树1的那一部分，但是那部分节点根本就没被dfs到，所以每个节点至多被dfs一次，所以总的复杂度就是O(nlogn)了

_____________________

## 本题题解

对于这道题来讲，我们有一个显然的暴力是利用树上差分的思想，把$u,v$上发放一个数字改成u到1发放一个数字，v到1发放一个数字，u,v的lca到1撤回一个数字
，u,v的lca的father到1撤回一个数字这4个操作

接下来我们每个节点上开一个cnt数组$cnt_{i}$表示i这个数字出现了多少次，那么节点i上出现最多的数字就是cnt数组的最大值(这不是废话嘛)

那么我们求i节点的cnt数组可以暴力的把它的所有孩子的cnt数组按位相加起来来进行求解，然后如果这个节点上有插入或者删除数字的操作我们再对cnt数组进行几次操作就行了~

不过这样太慢了……发现这个东西慢主要是数组按位相加这个操作，所以我们可以用线段树合并来实现数组按位相加这个操作

具体来讲，每个点开一颗权值线段树表示这个点上有什么数字，每个数字出现了几次，然后求点i的权值线段树就是将它所有孩子的线段树合并到一起然后再对合并出来的线段树进行一些在这个节点的插入和删除操作

那么我们的线段树需要维护的信息就是区间的最大值，我们最后查找i点最大的数字的时候就在点i的权值线段树上查一下$1-10^5$这个区间的最大值就行了

然后，这题131mb，虽然空间复杂度$O(nlogn)$但是略微算算空间还是可以卡过去的……

上代码~

```C
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;const int N=1e5+10;typedef long long ll;
int n;int m;int v[2*N];int x[2*N];int ct;int al[N];int fa[N][22];int dep[N];int ans[N];
struct data//存最大值的结构体 
{
    int u;int cnt;
    friend bool operator <(data a,data b){return (a.cnt==b.cnt)?a.u>b.u:a.cnt<b.cnt;}
    friend data operator +(data a,data b){return (data){a.u,a.cnt+b.cnt};}
};vector <data> ve[N];
inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
struct linetree//动态开点线段树合并 
{
    int s[40*N][2];data v[40*N];int ct;
    inline void ih(){ct=n;}
    inline void ins(int p,int l,int r,data va)//插入 
    {
        if(r-l==1){v[p]=va+v[p];return;}int mid=(l+r)/2;
        if(va.u<=mid)ins(s[p][0]=s[p][0]?s[p][0]:++ct,l,mid,va);
        else ins(s[p][1]=s[p][1]?s[p][1]:++ct,mid,r,va);v[p]=max(v[s[p][0]],v[s[p][1]]);
    }
    inline void mg(int p1,int p2,int l,int r)//合并 
    {
        if(r-l==1){v[p1]=v[p1]+v[p2];return;}int mid=(l+r)/2;//分情况讨论下 
        if(s[p1][0]&&s[p2][0])mg(s[p1][0],s[p2][0],l,mid);else if(s[p2][0])s[p1][0]=s[p2][0];
        if(s[p1][1]&&s[p2][1])mg(s[p1][1],s[p2][1],mid,r);else if(s[p2][1])s[p1][1]=s[p2][1];
        v[p1]=max(v[s[p1][0]],v[s[p1][1]]);
    }
}lt;
inline void dfs1(int u)//处理lca 
{
    for(int i=0;fa[u][i];i++)fa[u][i+1]=fa[fa[u][i]][i];dep[u]=dep[fa[u][0]]+1;
    for(int i=al[u];i;i=x[i])if(v[i]!=fa[u][0])fa[v[i]][0]=u,dfs1(v[i]);
}
inline int lca(int u,int v)//求lca 
{
    if(dep[u]<dep[v])swap(u,v);for(int d=dep[u]-dep[v],i=0;d;d>>=1,i++)if(d&1)u=fa[u][i];
    if(u==v)return u;for(int i=18;i>=0;i--)if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
inline void dfs2(int u)//线段树合并 
{
    for(int i=al[u];i;i=x[i])if(v[i]!=fa[u][0])dfs2(v[i]),lt.mg(u,v[i],0,1e5);
    vector <data> :: iterator it;
    for(it=ve[u].begin();it!=ve[u].end();++it){lt.ins(u,0,1e5,*it);}
    ans[u]=lt.v[u].u;
}
int main()
{
    scanf("%d%d",&n,&m);lt.ih();
    for(int i=1,u,v;i<n;i++){scanf("%d%d",&u,&v);add(u,v),add(v,u);}dfs1(1);
    for(int i=1,u,v,va;i<=m;i++)//拆成4个操作 
    {
        scanf("%d%d%d",&u,&v,&va);int lc=lca(u,v);
        ve[u].push_back((data){va,1});ve[v].push_back((data){va,1});
        ve[lc].push_back((data){va,-1});ve[fa[lc][0]].push_back((data){va,-1});
    }dfs2(1);for(int i=1;i<=n;i++)printf("%d\n",ans[i]);return 0;//拜拜程序~ 
}

```









---

## 作者：x义x (赞：148)

怎么你谷人均线段树合并啊……来一发虽然$\log^2 n$但是常数小很多的树剖解法吧。

树剖解法的核心内容是：

- 把树搞成一个序列；

- 把一次链修改搞成$\log n$次新序列上的区间修改；

- 然后愉快差分。

把树搞成序列和把链修改搞成区间修改（一个个区间正是链修改分割出的一条条重链在新序列上的映射）正是树剖的意义所在，如果你不会，我强烈推荐[这个博客](https://www.luogu.org/blog/zyxxs/post-xiao-yi-jiang-tan-dfs-xu-yu-shu-lian-pou-fen)，我个人认为他讲的还是不错的。~~（我吹我自己）~~

这时，一条链$(x,y)$的修改已经被搞成区间$[a_1,b_1],[a_2,b_2]...[a_k,b_k]$的修改。考虑一下差分思想，区间修改可以转变成在$a_i$打一个“增加第$z$种救济粮”的标记，在$b_i+1$处打一个“减少第$z$种救济粮”的标记，然后从$1$扫描到$N$累加一遍所有这种标记。如果只有一种救济粮，我们直接设一个整数$S$不断累加就行了。然而救济粮种类太多，弄一个大小为$10^5$的桶又很难查询最大值，现在的问题就是用什么东西累加标记。

因为我们需要增加、减少救济粮并在线查询最多的救济粮品种，所以你会很容易地想到权值线段树：它维护的是一个桶序列$A[i]$，第$i$种救济粮有$A[i]$个。上文的“累加标记”于是也就变成在这棵权值线段树上进行修改。增加第$z$种救济粮就是在这棵线段树上的第$z$位置+1，减少则反之。同时，因为它是一棵线段树所以可以直接查询最大值。

我刚才可能讲的有点乱，所以我们理一下，总结一下算法流程：

```
- 树剖初始化
- 把每一次在链(x,y)投放救济粮拆成在区间[a[1],b[1]],[a[2],b[2]]...[a[k],b[k]]上的修改
~ （对区间[a[i],b[i]]的修改变成当权值线段树扫到a[i]处时增加一个z品种救济粮，在b[i]+1处减少一个）
- 权值线段树从1位置向后开始扫描，每到一个点就处理这个点的修改（增加/减少z种救济粮）（翻译：把线段树
  的z位置增加/减少1），然后输出最多的救济粮
```

具体实现如下。

```cpp
#include<bits/stdc++.h>
using namespace std; 

const int maxN=1000005;

int N,M;

int lnk[maxN];
int pre[maxN<<1],tgt[maxN<<1],cnt;
void add_E(int u,int v){pre[++cnt]=lnk[u],tgt[cnt]=v,lnk[u]=cnt;}

//非常模板的树剖初始化
int fa[maxN],A[maxN],siz[maxN],son[maxN],dep[maxN],
    top[maxN],seg[maxN],rev[maxN],idx;
void DFS1(int u,int f){
    fa[u]=f;siz[u]=1;dep[u]=dep[f]+1;
    for(int e=lnk[u];e;e=pre[e])if(tgt[e]!=f){
        DFS1(tgt[e],u);
        siz[u]+=siz[tgt[e]];
        if(siz[tgt[e]]>siz[son[u]]||!son[u]) son[u]=tgt[e];
    }
}
void DFS2(int u,int f){
    seg[u]=++idx;rev[idx]=u;
    if(son[u]) top[son[u]]=top[u],DFS2(son[u],u);
    for(int e=lnk[u];e;e=pre[e])if(tgt[e]!=f&&tgt[e]!=son[u]){
        top[tgt[e]]=tgt[e];
        DFS2(tgt[e],u);
    }
}

int Lnk[maxN];
int Pre[maxN*20],Val[maxN*20],Cnt;
void add_O(int x,int val){    //这里采用类似前向星的方式存储修改
    Pre[++Cnt]=Lnk[x],Val[Cnt]=val,Lnk[x]=Cnt;
}

void CHAI(int u,int v,int c){  //拆！
    int fu=top[u],fv=top[v];
    while(fu!=fv){
        if(dep[fu]<dep[fv]) swap(u,v),swap(fu,fv);
        add_O(seg[fu],c);add_O(seg[u]+1,-c);  //-c表示减少c位置救济粮
        u=fa[fu],fu=top[u];
    }
    if(dep[u]<dep[v]) swap(u,v);
    add_O(seg[v],c);add_O(seg[u]+1,-c);
}

//线段树部分
int Max_cnt[maxN<<2],Max_pos[maxN<<2];
void push_up(int x){
    if(Max_cnt[x*2]>=Max_cnt[x*2+1]) Max_cnt[x]=Max_cnt[x*2],Max_pos[x]=Max_pos[x*2];
    //小于等于很关键，把小于等于改成小于你样例都过不了
    else Max_cnt[x]=Max_cnt[x*2+1],Max_pos[x]=Max_pos[x*2+1];
}
void Build(int x,int l,int r){
    if(l==r){Max_cnt[x]=0;Max_pos[x]=l;return;}
    int mid=(l+r)>>1;
    Build(x*2,l,mid);Build(x*2+1,mid+1,r);
    push_up(x);
}
void Update(int x,int l,int r,int pos,int K){
    if(l==r){Max_cnt[x]+=K;return;}
    int mid=(l+r)>>1;
    if(pos<=mid) Update(x*2,l,mid,pos,K);
    else Update(x*2+1,mid+1,r,pos,K);
    push_up(x);
}

int ans[maxN];

int main(){
    scanf("%d%d",&N,&M);
    for(int i=1;i<N;i++){
        int u,v;scanf("%d%d",&u,&v);
        add_E(u,v);add_E(v,u);
    }
    DFS1(1,0);top[1]=1;DFS2(1,0);  //树剖初始化
    while(M--){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        CHAI(x,y,z);  //拆掉！
    }
    Build(1,1,100000);  //权值线段树初始化
    for(int i=1;i<=N;i++){
        for(int e=Lnk[i];e;e=Pre[e]){  //“前缀和”的“累加”
            if(Val[e]>0) Update(1,1,100000,Val[e],1);
            else Update(1,1,100000,-Val[e],-1);
        }
        ans[rev[i]]=Max_cnt[1]?Max_pos[1]:0;  //题目强调过了
    }
    for(int i=1;i<=N;i++) cout<<ans[i]<<endl;
}
```

---

## 作者：SovietPower✨ (赞：31)

### $dsu\ on\ tree$的做法：
(如果没写过$dsu$可以看[这里](https://blog.csdn.net/QAQ__QAQ/article/details/53455462))

对修改操作做一下差分放到对应点上，就成了求每个点子树内出现次数最多的颜色，这就和[CF600E](http://codeforces.com/contest/600/problem/E)类似了。直接用$dsu$。

修改某个颜色出现次数的时候，最大值不能$O(1)$求出，得套个$set$，所以复杂度是$O(q\log^2n)$，空间是$O(n)$的。但常数并不大。

> 关于复杂度，在CF600E中对一个点的修改是$O(1)$的，而本题中可能是$O(q)$（一个点上挂着很多次修改）。但$dsu$的复杂度保证在于，每个点只会被统计$O(\log n)$次，所以不算$set$复杂度依旧是$O(q\log n)$。

一些细节：

计算轻儿子子树贡献的时候必须自叶子向上更新，否则在中间会出现某种颜色出现次数$<0$的情况导致RE...（因为差分的减标记在上面，加标记在底层）；

对子树的DFS可以通过枚举DFS序代替，应该能优化不少常数。

代码：

```cpp
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int dep[N],fa[N],sz[N],son[N],top[N],L[N],R[N],A[N],Max,tm[N],cnt[N],Ans[N];
std::set<int> st[N];
struct Graph
{
	int Enum,H[N],nxt[N<<2],to[N<<2];
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
	inline void AQ(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
}T,Q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]<dep[v]?u:v;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	static int Index=0;
	A[L[x]=++Index]=x, top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=T.H[x],v; i; i=T.nxt[i])
			if((v=T.to[i])!=fa[x] && v!=son[x]) DFS2(v,v);
	}
	R[x]=Index;
}
inline void Add(int c)
{
	int t=tm[c]; ++tm[c];
	--cnt[t], ++cnt[t+1], st[t].erase(c), st[t+1].insert(c);
	if(t+1>tm[Max]||(t+1==tm[Max] && c<Max)) Max=c;
}
inline void Subd(int c)
{
	int t=tm[c]; --tm[c];
	--cnt[t], ++cnt[t-1], st[t].erase(c), st[t-1].insert(c);
	if(c==Max) !cnt[t] ? Max=*st[t-1].begin() : Max=*st[t].begin();
}
inline void Upd(int x)
{
	for(int i=Q.H[x]; i; i=Q.nxt[i])
		i&1 ? Add(Q.to[i]) : Subd(Q.to[i]);
}
void Solve(int x,bool keep)
{
	static int Time,vis[N];
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x] && v!=son[x]) Solve(v,0);
	if(son[x]) Solve(son[x],1);

	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x] && v!=son[x])
			for(int j=R[v]; j>=L[v]; --j) Upd(A[j]);//要倒序枚举
	Upd(x), Ans[x]=tm[Max]?Max:0;

	if(!keep)
	{
		Max=0, ++Time;
		for(int u=L[x]; u<=R[x]; ++u)
			for(int i=Q.H[A[u]]; i; i=Q.nxt[i])
			{
				int c=Q.to[i];
				if(vis[c]!=Time) vis[c]=Time, --cnt[tm[c]], st[tm[c]].erase(c), ++cnt[tm[c]=0], st[0].insert(c);
			}
	}
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<n; ++i) T.AE(read(),read());
	DFS1(1), DFS2(1,1);
	for(int i=1; i<=m; ++i)
	{
		int x=read(),y=read(),z=read(),w=LCA(x,y);
		Q.AQ(x,z), Q.AQ(w,z), Q.AQ(y,z), Q.AQ(fa[w],z);
	}
	for(int i=1; i<=n; ++i) st[0].insert(i);
	Max=0, cnt[0]=n, Solve(1,1);
	for(int i=1; i<=n; ++i) printf("%d\n",Ans[i]);

	return 0;
}
```

---

## 作者：mona (赞：31)

感谢 @cx233666 给我提供的线段树合并毒瘤题

首先楼上的那个代码被某位大佬$Hack$了，我开始被卡空间来看题解结果发现楼上跟我差不多过了很惊讶？？？（懵逼状态）

我当时以为我学了个假的线段树合并，一看右边，诶被$Hack$了就很舒服。

反正我是只会新建节点的那种，有谁会不新建的可以来教我。

$Update$：这道题还是可以不新建的好像，同理于修改不用新建，理解了一下，不过貌似还是对遍历顺序有要求。

本文着重讲解对于线段树合并的空间优化问题，存在其他写法不需要涉及本文写法。

----


## 本题思路 (前置技能 线段树合并）

首先肯定直观的想法就是**树上差分然后线段树合并**是吧，具体就是对于一条$(u,v)$的路径，在$u$和$v$上放下$+1$的标记，然后在$lca$与$lca$父亲处放上$-1$的标记，最后一遍$dfs$用线段树合并统计所有答案（线段树求全局最大值应该会吧）。然后我们就可以直接在根节点处得到答案了。


然后你发现这道题的**空间只有苦逼的$128MB$**，对啊，问题就在这里，不然我还讲什么。

我开始像上面那样打了，是最原始的做法，放标记就直接在$Dfs$之前放完了，而且用的还是新增节点的那种$Update$，然后一波线段树合并，这样$100$倍空间好像都过不了。

这样算一波空间复杂度大概是 $O(nlogn*4)$ 级别的

然后这个是处理放标记的一个数组，开四个总共是$100MB$左右，然后你还要线段树合并一波，同样是这么大，所以大概要$200MB$，我只是算了个大概，没仔细分析，但也差不多了。如果有哪位大佬可以有更好的处理空间方式可以告诉我一下，目前这样是完全不行的。

然后我就在网上找标程，结果发现自己很蠢。

----
## 线段树合并空间优化
（部分内容仅限拥有某种性质的题目）

首先最基本的一点，因为我们是先修改再合并吧，所以对于已经存在的节点，我们可以直接修改该节点的值，而不是新建节点，这样我们可以优化一部分空间，但是仅仅是常数级别的优化。

但是别着急。

第二点，我们可以打一个垃圾回收（大概是叫这个）。

我们发现在线段树合并之后，并不需要查询某棵树的信息，而对于所有的答案我们可以直接记录下来，所以事实上来说，如果一棵树合并到了它父亲节点上，并且我们记录了这棵树的答案，那么这棵树就没用了，它的空间就可以空出来留给后面用了。

所以我们记一下可以重复利用的点，每次新建节点的时候就优先用这些点，具体代码如下。

```cpp
	inline int New() { if(tot) return rab[tot--]; return ++cnt; }
	inline void Throw(int x) { rab[++top]=x,ls[x]=rs[x]=Max[x]=id[x]=0; }

```

$rab$数组是垃圾数组，也就是记录所有可以重复利用的点。

$tot$是垃圾数 $cnt$是所有节点的个数，也就是新建全新的节点。

$New$ 函数在你需要新建节点的时候用，返回节点编号。

$Throw$ 意味着这个节点没用了，你可以直接丢掉它。


这样我们就可以极大的提高空间的利用率。

**但是你发现单纯加这个依然过不了。**

（如果你是$Dfs$之前加标记的话）

这样我们看起来优化了大概一半的空间，看起来是过了的，实际上，是假的，看起来大概是合并时保留的节点数只有当前几个线段树？再想想，不只是这些，所有询问的空间还在里面，你会带着这些空间一起跑，而这样的空间并不是一层，而是所有的空间慢慢减小，最后只剩下根节点那棵树的空间。

所以我们考虑边$Dfs$边放标记，当然这里指把标记丢进线段树里，不过如果你是将儿子合并向自己的话，依旧是假的，菊花树大概就凉了，所以这里我们要把自己合并向父亲，这样我们每次就是用到了当前这个点的线段树和正在被合并的父亲的那棵线段树，这样的复杂度最大就是两倍的$nlogn$吧，而实际上取决于信息的密度，实际比这个好像要小很多，本题数据开$40$倍空间是完全足够的，网上看见一个二十倍空间的写$Bfs$的过了，就很强。

关于空间问题，如果有更加详细的证明可以教我一下，本人并不是特别能够理解这个。本文仅当抛砖引玉，或是给予为空间问题而烦恼的选手指引道路。

下面是通过代码。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<ctime>
using namespace std;
#define ll long long
#define N 101000
#define Z 100000
#define inf 1e9
#define RG register
inline ll read(){
    RG ll x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

int n,m,top,first[N],ans[N];
struct mona { int nxt,en; } s[N<<1];
struct joker { int nxt,en,op; } ;
inline void Insert(int x,int y) { s[++top]=(mona) { first[x],y },first[x]=top; }
struct SeqTree{
	int cnt,ls[N*40],rs[N*40],Max[N*40],id[N*40],rt[N],rab[N*40],tot,top,first[N]; joker s[N<<2]; 
	inline void Insert(int x,int y,int op) { s[++top]=(joker) { first[x],y,op },first[x]=top; }
	inline int New() { if(tot) return rab[tot--]; return ++cnt; }
	inline void Throw(int x) { rab[++top]=x,ls[x]=rs[x]=Max[x]=id[x]=0; }
	inline void Pushup(int x){
		if(Max[ls[x]]>=Max[rs[x]]) Max[x]=Max[ls[x]],id[x]=id[ls[x]];
		else Max[x]=Max[rs[x]],id[x]=id[rs[x]];
	}
	inline void Modify(int l,int r,int &x,int pos,int val){
		if(!x) x=New(); if(l==r) { Max[x]+=val,id[x]=l;  }
		else{int mid=l+r>>1;
		if(pos<=mid) Modify(l,mid,ls[x],pos,val);
		else Modify(mid+1,r,rs[x],pos,val);
		Pushup(x);} if(!Max[x]) id[x]=0;
	}
	inline int Merge(int l,int r,int u,int v){
		if(!u||!v) return u|v;
		int now=New(),mid=l+r>>1; if(l==r) Max[now]=Max[u]+Max[v],id[now]=l;
		else ls[now]=Merge(l,mid,ls[u],ls[v]),rs[now]=Merge(mid+1,r,rs[u],rs[v]),Pushup(now);
		Throw(u),Throw(v); return now;
	}
} T;

struct Tree{
	int top[N],son[N],siz[N],fa[N],dep[N];
	inline void Dfs(int k,int Fa){
		fa[k]=Fa,siz[k]=1,dep[k]=dep[Fa]+1;
		for(RG int i=first[k];i;i=s[i].nxt){
			int en=s[i].en; if(en==Fa) continue ;
			Dfs(en,k),siz[k]+=siz[en];
			if(siz[son[k]]<siz[en]) son[k]=en;
		}   return ;
	}
	inline void Dfs2(int k,int to){
		top[k]=to; if(son[k]) Dfs2(son[k],to);
		for(RG int i=first[k];i;i=s[i].nxt){
			int en=s[i].en; if(en==fa[k]||en==son[k]) continue ;
			Dfs2(en,en);
		}
	}
	inline int Lca(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			u=fa[top[u]];
		}   return dep[u]<dep[v]?u:v;
	}
} S;

inline void Dfs(int k,int fa){
	for(RG int i=first[k];i;i=s[i].nxt) if(s[i].en!=fa) Dfs(s[i].en,k);
	for(RG int i=T.first[k];i;i=T.s[i].nxt) T.Modify(1,Z,T.rt[k],T.s[i].en,T.s[i].op);
	ans[k]=T.id[T.rt[k]];
	if(S.fa[k]) T.rt[S.fa[k]]=T.Merge(1,Z,T.rt[S.fa[k]],T.rt[k]);
	return ;
}

int main(){
	n=read(),m=read();
	for(RG int i=1;i<n;++i){
		int x=read(),y=read();
		Insert(x,y),Insert(y,x);
	}   S.Dfs(1,0),S.Dfs2(1,1);
	for(RG int i=1;i<=m;++i){
		int u=read(),v=read(),val=read();
		int lca=S.Lca(u,v),Flca=S.fa[lca];
		T.Insert(u,val,1),T.Insert(v,val,1),T.Insert(lca,val,-1),T.Insert(Flca,val,-1);
	}   Dfs(1,0); for(RG int i=1;i<=n;++i) printf("%d\n",ans[i]);
}

```

---

## 作者：Ireliaღ (赞：21)

**怎么没人写Splay启发式合并啊，我来写一个**

## 前置知识

1. 树上差分。一言以蔽之，**当对$x$，$y$的路径添加贡献时，转化为对$x$，$y$添加贡献，对$lca$，和$lca$的父亲添加负贡献，最后计算时，计算$x$为根的子树的答案，就是$x$的答案。**

2. $Splay$。不会的去普通平衡树写写吧。之前在洛谷QQ群认识的一个大佬跟我说，$Splay$启发式合并时，如果每次按升序插入，有一种叫做“Finger Search”的性质，它会让最后总复杂度只有一个$\log$。我不会证，估计也得势能分析。并且他跟我说只有$Splay$启发式合并是一个$\log$，其他平衡树都是两个$\log$。

## 本题解法

每一个点开两个`vector`，记录每个点都加了什么，删了什么。

当对$x$，$y$路径分发$z$时，转化为对$x$添加$z$，对$y$添加$z$，对$lca$和$lca$的父亲删除$z$。每一个点开一个`Splay`记录答案。

计算一个点$x$的答案时，先`DFS`$x$的所有儿子，然后把儿子的`Splay`启发式合并进$x$的`Splay`，再遍历$x$的两个`vector`进行添加删除，就是$x$的答案。

启发式合并，就是把`size`小的平衡树里的所有元素一个一个往大的里面塞。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> poi;
const int MAXN = 2e5 + 5;

struct SplayTree{
	struct Node{
		Node *fa, *ch[2];
		int val, cnt;
		poi res;
		Node() {}
		
		Node(Node *fa, int val, int cnt) : fa(fa), val(val), cnt(cnt) {
			res = make_pair(cnt, -val);
			ch[0] = ch[1] = NULL;
		}
	};
	
	Node *rt;
	int size;
	Node *New(Node*, int, int);
	SplayTree() {rt = NULL; size = 0;}
	void Del(Node*);
	
	void Update(Node *x) {
		x->res = make_pair(x->cnt, -x->val);
		if (x->ch[0]) x->res = max(x->res, x->ch[0]->res);
		if (x->ch[1]) x->res = max(x->res, x->ch[1]->res);
	}
	
	void Rotate(Node *now) {
		Node *fa = now->fa, *anc = fa->fa;
		int d = (now == fa->ch[1]);
		if (anc) anc->ch[fa == anc->ch[1]] = now;
		now->fa = anc;
		fa->fa = now;
		fa->ch[d] = now->ch[!d];
		now->ch[!d] = fa;
		if (fa->ch[d]) fa->ch[d]->fa = fa;
		Update(fa); Update(now);
		if (!now->fa) rt = now;
	}
	
	void Splay(Node *now) {
		if (!now) return;
		while (now->fa) {
			Node *fa = now->fa, *anc = fa->fa;
			if (anc) {
				if ((fa == anc->ch[1]) ^ (now == fa->ch[1])) Rotate(now);
				else Rotate(fa);
			}
			Rotate(now);
		}
	}
	
	void Insert(int val, int cnt) {
		size += cnt;
		if (!rt) {
			rt = New(NULL, val, cnt);
			return;
		}
		Node *now = rt;
		while (now) {
			if (val < now->val) {
				if (now->ch[0]) {
					now = now->ch[0];
				} else {
					now->ch[0] = New(now, val, cnt);
					now = now->ch[0];
					break;
				}
			} else if (val == now->val) {
				now->cnt += cnt;
				Update(now);
				break;
			} else {
				if (now->ch[1]) {
					now = now->ch[1];
				} else {
					now->ch[1] = New(now, val, cnt);
					now = now->ch[1];
					break;
				}
			}
		}
		Splay(now);
	}
	
	void Find(int val) {
		Node *now = rt;
		while (now) {
			if (val < now->val) {
				now = now->ch[0];
			} else if (val == now->val) {
				break;
			} else {
				now = now->ch[1];
			}
		}
		Splay(now);
	}
	
	void Remove(int val) {
		Find(val);
		if (!rt || rt->val != val) return;
		size--;
		rt->cnt--;
		Update(rt);
		return;
	}
	
	void Merge(Node *now) {
		if (!now) return;
		Merge(now->ch[0]);
		if (now->cnt) Insert(now->val, now->cnt);
		Merge(now->ch[1]);
		Del(now);
	}
	
	void Join(SplayTree &T) {
		if (size < T.size) {
			swap(size, T.size);
			swap(rt, T.rt);
		}
		Merge(T.rt);
	}
};

SplayTree::Node npool[1000000];
SplayTree::Node* tra[MAXN << 1];
int ncnt, tcnt;

SplayTree::Node* SplayTree::New(SplayTree::Node *fa, int val, int cnt) {
	SplayTree::Node *res = tcnt ? tra[tcnt--] : &npool[ncnt++];
	*res = SplayTree::Node(fa, val, cnt);
	return res;
}

void SplayTree::Del(SplayTree::Node *now) {
	tra[++tcnt] = now;
}
//----------
int n, m;
int to[MAXN], nxt[MAXN], head[MAXN], ecnt;

void Add(int u, int v) {
	to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
	to[++ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt;
}
//----------
int stt[20][MAXN], tot, id1[MAXN], lg2[MAXN], fa[MAXN];
int dep[MAXN];

void DFS1(int u, int last, int depth) {
	stt[0][++tot] = u;
	id1[u] = tot;
	dep[u] = depth;
	fa[u] = last;
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v == last) continue;
		DFS1(v, u, depth + 1);
		stt[0][++tot] = u;
	}
}

int Lower(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}

void GetST() {
	for (int i = 2; i <= tot; i++) lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; (1 << i) <= tot; i++) {
		int w = (1 << i);
		for (int j = 1; j + w - 1 <= tot; j++) {
			stt[i][j] = Lower(stt[i - 1][j], stt[i - 1][j + w / 2]);
		}
	}
}

int LCA(int x, int y) {
	x = id1[x]; y = id1[y];
	if (x > y) swap(x, y);
	int i = lg2[y - x + 1], w = (1 << i);
	return Lower(stt[i][x], stt[i][y - w + 1]);
}
//----------
vector<int> add[MAXN];
vector<int> del[MAXN];
SplayTree T[MAXN];
int ans[MAXN];

void Ins(int x, int y, int val) {
	int lca = LCA(x, y);
	add[x].push_back(val);
	add[y].push_back(val);
	del[lca].push_back(val);
	del[fa[lca]].push_back(val);
}

void DFS2(int u) {
	T[u].Insert(0, 0);
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v == fa[u]) continue;
		DFS2(v);
		T[u].Join(T[v]);
	}
	for (unsigned i = 0; i < add[u].size(); i++) T[u].Insert(add[u][i], 1);
	for (unsigned i = 0; i < del[u].size(); i++) T[u].Remove(del[u][i]);
	ans[u] = -T[u].rt->res.second;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	for (int i = 1; i <= n - 1; i++) {
		int x, y;
		cin >> x >> y;
		Add(x, y);
	}
	DFS1(1, 0, 0);
	GetST();
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		Ins(x, y, z);
	}
	DFS2(1);
	for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
	return 0;
}
```

~~`Splay`这种东西常数极大，以前模拟赛我写`Splay`一个$\log$被`BIT`的两个$\log$吊打了。这道题也是，如果不吸氧的话，就得看评测姬给不给面子~~

**12.27 Update**

貌似做麻烦了，根本不用离线，`Splay`的一个节点中的`cnt`，也就是一个数出现的次数是负数其实一点问题都没有，所以不需要通过离线保证删除时一定存在，直接操作就OK了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> poi;
const int MAXN = 2e5 + 5;

struct SplayTree{
    struct Node{
        Node *fa, *ch[2];
        int val, cnt;
        poi res;
        Node() {}

        Node(Node *fa, int val, int cnt) : fa(fa), val(val), cnt(cnt) {
            res = make_pair(cnt, -val);
            ch[0] = ch[1] = NULL;
        }
    };

    Node *rt;
    int size;
    Node *New(Node*, int, int);
    SplayTree() {rt = NULL; size = 0;}
    void Del(Node*);

    void Update(Node *x) {//更新答案
        x->res = make_pair(x->cnt, -x->val);
        if (x->ch[0]) x->res = max(x->res, x->ch[0]->res);
        if (x->ch[1]) x->res = max(x->res, x->ch[1]->res);
    }

    void Rotate(Node *now) {
        Node *fa = now->fa, *anc = fa->fa;
        int d = (now == fa->ch[1]);
        if (anc) anc->ch[fa == anc->ch[1]] = now;
        now->fa = anc;
        fa->fa = now;
        fa->ch[d] = now->ch[!d];
        now->ch[!d] = fa;
        if (fa->ch[d]) fa->ch[d]->fa = fa;
        Update(fa); Update(now);
        if (!now->fa) rt = now;
    }

    void Splay(Node *now) {
        if (!now) return;
        while (now->fa) {
            Node *fa = now->fa, *anc = fa->fa;
            if (anc) {
                if ((fa == anc->ch[1]) ^ (now == fa->ch[1])) Rotate(now);
                else Rotate(fa);
            }
            Rotate(now);
        }
    }

    void Insert(int val, int cnt) {//把cnt个val加进来
        size += cnt;
        if (!rt) {
            rt = New(NULL, val, cnt);
            return;
        }
        Node *now = rt;
        while (now) {
            if (val < now->val) {
                if (now->ch[0]) {
                    now = now->ch[0];
                } else {
                    now->ch[0] = New(now, val, cnt);
                    now = now->ch[0];
                    break;
                }
            } else if (val == now->val) {
                now->cnt += cnt;
                Update(now);
                break;
            } else {
                if (now->ch[1]) {
                    now = now->ch[1];
                } else {
                    now->ch[1] = New(now, val, cnt);
                    now = now->ch[1];
                    break;
                }
            }
        }
        Splay(now);
    }

    void Find(int val) {
        Node *now = rt;
        while (now) {
            if (val < now->val) {
                now = now->ch[0];
            } else if (val == now->val) {
                break;
            } else {
                now = now->ch[1];
            }
        }
        Splay(now);
    }

    void Remove(int val) {
        Find(val);
        if (!rt || rt->val != val) return;
        size--;
        rt->cnt--;
        Update(rt);
        return;
    }

    void Merge(Node *now) {
        if (!now) return;
        Merge(now->ch[0]);
        if (now->cnt) Insert(now->val, now->cnt);
        Merge(now->ch[1]);
        Del(now);
    }

    void Join(SplayTree &T) {
        if (size < T.size) {
            swap(size, T.size);
            swap(rt, T.rt);
        }
        Merge(T.rt);
    }
};

SplayTree::Node npool[1000000];
SplayTree::Node* tra[MAXN << 1];
int ncnt, tcnt;

SplayTree::Node* SplayTree::New(SplayTree::Node *fa, int val, int cnt) {
    SplayTree::Node *res = tcnt ? tra[tcnt--] : &npool[ncnt++];
    *res = SplayTree::Node(fa, val, cnt);
    return res;
}

void SplayTree::Del(SplayTree::Node *now) {
    tra[++tcnt] = now;
}
//----------
int n, m;
int to[MAXN], nxt[MAXN], head[MAXN], ecnt;

void Add(int u, int v) {
    to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
    to[++ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt;
}
//----------
int stt[20][MAXN], tot, id1[MAXN], lg2[MAXN], fa[MAXN];
int dep[MAXN];

void DFS1(int u, int last, int depth) {
    stt[0][++tot] = u;
    id1[u] = tot;
    dep[u] = depth;
    fa[u] = last;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == last) continue;
        DFS1(v, u, depth + 1);
        stt[0][++tot] = u;
    }
}

int Lower(int x, int y) {
    return dep[x] < dep[y] ? x : y;
}

void GetST() {
    for (int i = 2; i <= tot; i++) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; (1 << i) <= tot; i++) {
        int w = (1 << i);
        for (int j = 1; j + w - 1 <= tot; j++) {
            stt[i][j] = Lower(stt[i - 1][j], stt[i - 1][j + w / 2]);
        }
    }
}

int LCA(int x, int y) {
    x = id1[x]; y = id1[y];
    if (x > y) swap(x, y);
    int i = lg2[y - x + 1], w = (1 << i);
    return Lower(stt[i][x], stt[i][y - w + 1]);
}
//----------
SplayTree T[MAXN];
int ans[MAXN];

void Ins(int x, int y, int val) {
    int lca = LCA(x, y);
    T[x].Insert(val, 1);
    T[y].Insert(val, 1);
    T[lca].Insert(val, -1);
    T[fa[lca]].Insert(val, -1);
}

void DFS2(int u) {
    T[u].Insert(0, 0);//防止出现空树
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u]) continue;
        DFS2(v);
        T[u].Join(T[v]);
    }
    ans[u] = -T[u].rt->res.second;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        cin >> x >> y;
        Add(x, y);
    }
    DFS1(1, 0, 0);
    GetST();
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        Ins(x, y, z);
    }
    DFS2(1);
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
    return 0;
}
```

~~但是这种在线的写法会产生很多多余的点，所以比离线要慢，即使吸氧了还是要看评测姬给不给面子~~

---

## 作者：critnos (赞：16)

对每种颜色分别处理。

对每种颜色的操作建立虚树。这里对原树预处理 $O(n)-O(1)$ LCA 即可线性。

那么对虚树上每一条边即原树上的一条链，可以求出他被加入这种颜色多少次，设为边权。

那么相当于若干次操作，每次对一条链取 $\max$。

把所有虚树上的边按权排序。从大到小扫描，维护树上并查集。即维护每个点最深的没有被操作过的祖先。每次取 $\max$ 相当于从链底向上跳，利用并查集跳过已经被操作过的点，把未被操作过的点 $\max$ 设成当前虚树边的权值并标记即可。

这个树上并查集是可以线性的。树分块后四毛子或者利用位运算即可。

---

## 作者：STDLRZ (赞：5)

本题解总结了大部分原题解里面的做法，并且对其加以详细讲解，目的是让大家可以更好的理解题解的思路。

同时，作者本身也添加了几种方法供大家参考。

因为作者是个蒟蒻，所以若该题解有问题，请指出，感激不尽！

## 方法 1

前置知识：动态开点线段树、树上差分、LCA。

参考 @shadowice1984 的做法。

### 做法 & 思考

首先，考虑本题存放救济粮这个操作有什么特点。

因为救济粮可能有很多种，于是就需要用值域线段树。

但是很明显将所有点全部来一棵值域线段树，然后又依次修改肯定是不现实的。

于是考虑树上差分，将一次操作差分成对四个点 $x,y,LCA(x,y)$ 以及 $LCA(x,y)$ 的父亲进行操作。

接着，因为需要做一次类似于前缀和的操作，而一个节点 $x$ 的最终状态是以 $x$ 为根的子树里所有的线段树全部合并起来所得到的最终结果。

考虑如何对线段树进行合并。

~~我们充分发挥人类智慧~~，显然如果两个节点 $x,y$ 在合并时已经有一个节点为空，那么直接返回就行。

理解的话，就是相当于把那个不为空的节点的子树给黏贴一份到他的父亲的下面。

然后，如果 $x,y$ 均为叶子节点，我们就需要对其进行相加操作。

理解的话，就是最终 $x$ 的结果肯定是他子树所有救济粮的个数加起来，再去算，而不是全部取 $\max$。

对于其他情况，则递归到左儿子和右儿子进行合并。

本题该部分该部分代码长这样：

```cpp
int merge(int x,int y,int l,int r){
	if(!x || !y) return x|y;
	if(l==r) {mx[x]+=mx[y];return x;}
	int mid=(l+r)>>1;
	ls[x]=merge(ls[x],ls[y],l,mid),
	rs[x]=merge(rs[x],rs[y],mid+1,r),
	mx[x]=max(mx[ls[x]],mx[rs[x]]);
	return x;
}
```

变量含义：`ls[x]` 为线段树节点 $x$ 的左儿子，`rs[x]` 为线段树节点 $x$ 的右儿子，`mx[x]` 为线段树节点 $x$ 所存储的最大值。

### 时间复杂度证明

线段树合并的时间复杂度是 $\mathcal O(n \log n)$ 的。

证明如下：

设当前 `merge` 到的两个节点分别为 $x,y$，现在，我们要将以 $rtx$ 节点为根的线段树和以 $rty$ 节点为根的线段树合并。

首先，一个位置能被递归到，证明这两个位置都有节点（只有一个节点不为空的直接返回了）。

这样，接下来 $y$ 节点在接下来的线段树合并中就不会用到了，因为被 $x$ 节点合并成一个点了（由代码可知）。

这样的话，那些对时间复杂度产生贡献的 $x$ 节点，肯定是在函数 `merge(x,y,l,r)`，$y$ 节点为空时才会继续往下遍历。

但是，这些 $x$ 节点一旦遇到这种情况则会直接返回，产生的代价为 $1$。

这样，最多当 $y$ 节点为空，$x$ 节点不为空的时候，$x$ 节点产生一次贡献。而这一次接上去之后，这棵线段树的这个位置上将不会为空。

否则，则为 $y$ 节点产生一次贡献，然后不再产生任何贡献。

为了方便分析，我们可以在一个节点 $x$ 遍历左右儿子节点的时候，先特判一下 `if(!x || !y) return x|y;` 的情况，如果不满足再递归下去，则此时单个节点仍然最多访问 $1$ 次。

又考虑到原来的 $n$ 棵线段树共有 $\log n$ 个节点，所以综上，时间复杂度为 $\mathcal O(n \log n)$。

至于空间复杂度，已经在证明里面分析出来了，也是 $\mathcal O(n \log n)$。

### 代码 & 实现细节

但是注意，在代码里面，因为一次操作被拆分成了 $4$ 个点，所以此时会约有 $4n(\log n+2)$ 个节点同时存在。

稍微算一下，最坏情况下要开 $80$ 倍的 $n$。当然可能有优化常数方法，那我就不太清楚了。

[方法 1 代码](https://www.luogu.com.cn/paste/nyzx8dq6)。

### 扩展部分

有一些题目的线段树合并，可能合并之后要访问合并之前的数据，此时这种做法将会失效。

我们可以先对这两棵线段树做一份备份，但是带来的代价就是，空间常数会翻 $2$ 倍。

在做题目的时候可以留心注意一下两者的区别。这里就没有另写一份代码来展示这种做法了。

## 方法 2

其实方法 2 挺傻的（没有方法 1 聪明），这里只是稍微提一下思路，并给出代码。

前置知识：动态开点线段树、启发式合并、LCA。

### 做法 & 思考 & 时间复杂度

考虑方法 1 中线段树合并的~~弱智做法~~。

我们可以比较两棵线段树节点的个数，选一棵节点少的合并到节点多的即可。

这样的话，共有 $n \log n$ 个线段树节点，而启发式合并带一只 $\log n$，所以时间复杂度是 $\mathcal O(n \log^2 n)$ 的，我写的是空间复杂度为 $\mathcal O(n \log^2 n)$ 的版本。

其实挺像方法 1 的代码的，有兴趣的人可以比较比较两个代码之间的差异。

但不过看起来这个方法没意义。。。

令人惊奇的是，跑的跟方法 1 差不多快，可能是数据没卡吧。

### 代码

[方法 2 代码](https://www.luogu.com.cn/paste/k4lpm5c3)。

### 扩展部分

听说用 $\tt Splay$ 可以做到 $\mathcal O(n \log n)$ 的时间复杂度合并，说不定把线段树稍微换一下会有奇效呢！

感兴趣的可以去看一看别的题解怎么写 $\tt Splay$ 的（有写，这里就不赘述了。）

## 方法 3

前置知识：值域线段树、莫队、树上差分、LCA。

### 做法 & 思考

因为不能真的给每个节点都分一次救济粮，这样就凉凉了。

所以我们还是考虑树上差分，一个操作对四个点进行操作。

然后，利用 $\tt dfn$ 序的性质：以 $x$ 为根的子树的 $\tt dfn$ 编号是连续的（$x$ 可任意），可以想到，先将所有节点的编号转为 $\tt dfn$ 编号，如果我能求一段区间内的 $tag$ 全部加起来，那我们照样也可以做这道题了。

考虑一个最垃圾的做法，树套树。

但是对于这一道题，线段树中的每一棵线段树看起来需要进行 $\mathcal O(\log n)$ 次合并操作才能查询。

问题就出在这里。如果真的合并，你肯定要先合并线段树上的叶子节点是吧。那已经超时了，时间复杂度达 $\mathcal O(n^2)$（甚至更高），这个方法没得玩了。

但是，莫队是个好东西啊。你可以放 $n$ 个询问区间进去，然后莫队一下，所有的询问结果就出来了。

这样的好处是，我们只需要用一棵线段树就可以解决问题。

坏处是，时间复杂度为 $\mathcal O(n \sqrt[2] n \log n)$。

此处空间复杂度为 $\mathcal O(n \log n)$（因为树上倍增的原因，但是可以优化到 $\mathcal O(n)$，用树链剖分求 $\tt LCA$ 即可）。

### 时间复杂度证明

假设 $n$ 与 $m$ 同阶，则时间复杂度 $\mathcal O(n \sqrt[2] n \log n)$ 证明：

设第 $i$ 个块中有 $t_i$ 个 $tag$，有 $s_i$ 个区间的左端点在第 $i$ 个块中。

则由莫队特性——先按照左端点所在的块编号排序，在一样的情况下按照右端点从小到大排序可得第 $i$ 个块对时间复杂度的贡献：

$$
s_i \cdot t_i+\sum_{x=1}^{\sqrt[2]n} t_x
$$

由 $n,m$ 同阶，且操作总次数（每一个点操作的次数的总和）为 $n$（准确来说应该是 $4n$，这里忽略常数），有：

$$
\sum_{x=1}^{\sqrt[2]n} t_x=n
$$

设其为 $1$ 式。

则原式用 $1$ 式化简可得：

$$
s_i \cdot t_i+n
$$

考虑 $\tt dfn$ 序的性质。

对于同一个节点 $x$ 的 $\tt dfn$ 序区间（以 $x$ 为根的子树的 $\tt dfn$ 范围，下同）的儿子的 $\tt dfn$ 序互不相干。

并且每一个节点 $x$ 的 $\tt dfn$ 序区间的左端点都不一样。

为什么呢？很好证明（甚至不用证）。节点 $x$ 的 $\tt dfn$ 序区间的左端点是 $dfn_x$（以 $x$ 为根的树第一个访问的肯定是 $x$ 节点），而每一个点的 $\tt dfn$ 都是不一样的，所以左端点也就不一样了。

利用这个性质，我们得知 $s_i=\sqrt[2]n$，带入原式，得：

$$
t_i\sqrt[2]n+n
$$

则时间复杂度式子为：

$$
\sum_{x=1}^{\sqrt[2] n} (t_i\sqrt[2]n+n)
$$

拆开，得：

$$
\sqrt[2]n \cdot (\sum_{x=1}^{\sqrt[2] n} t_i)+n \sqrt[2]n
$$

用 $1$ 式化简，可得最终结果为 $2n \sqrt[2]n$，忽略常数为 $n \sqrt[2]n$。

因为线段树一次操作时间复杂度为 $\mathcal O(\log n)$，所以综上，时间复杂度为 $\mathcal O(n \sqrt[2]n \log n)$。

### 扩展 & 为什么要证明时间复杂度？

相信很多人有这个疑问：为什么要证明？这不是很显然的嘛？

不不不，那就错了。

根据证明中的一个式子（第 $i$ 个块对时间复杂度的贡献）：$s_i \cdot t_i+n$，其实说明了一些问题。

现在，让我们思考一下，能不能把这个算法卡掉呢？

由这个式子，我们知道，后面的一项 $n$ 已经卡不了了，于是我们想办法卡前面的。

我们可以让所有操作都集中在第 $i$ 个块内的点中，这样就有 $t_i=n$ 了。

然后，我们可以让所有的询问的左端点全部集中在第 $i$ 个块内，那么又有 $s_i=n$。

欸，这样时间复杂度不就变成了 $n^2+n \sqrt[2] n$ 了嘛？

这就是问题所在。但是真实可不可以卡呢？（前面只是理论可卡）

其实是可以的。我们设第一个块的左端点为 $1$，右端点为 $k(k=\lfloor \sqrt[2]n \rfloor)$，那么可以有如下询问：

第 $i$ 个询问：

- 若 $i$ 为奇数，则区间为 $[1,k+i]$；
- 若 $i$ 为偶数，则区间为 $[k,k+i]$。

这样，右端点总贡献是 $n$，但是左端点不断的在整个块内横扫（从 $1$ 扫到 $k$，又从 $k$ 扫到 $1$，以此类推）。我们将所有的操作全部都集中到 $[2,k-1]$ 中，这样每一次扫，都需要 $\mathcal O(n)$ 的时间。

但是因为有 $n$ 个区间（上面的询问个数至少也有 $n-k$ 个，而 $k$ 很小，直接忽略），所以时间复杂度为 $\mathcal O(n^2+n)$。

但是为什么本题是正确的呢？

因为 $\tt dfn$ 序有一个特点：左端点互不相同。

这样我们就控制了 $s_i$，使得 $s_i=\sqrt[2]n$，然后再化简式子，就得到了正确的结果。

所以，以后如果有题目，说左端点互不相同，说不定就可以用上莫队了呢！

### 代码

温馨提示：

- 请使用 `vector`，若您使用链式前向星，则您有可能会 `TLE`。
- 因为本题莫队带了 $4$ 倍常数，所以请使用奇偶性优化，否则也可能会 `TLE`。
- 您的线段树的左儿子和右儿子请不要写成 `x*2` 和 `x*2+1`，应该要写成 `x<<1` 和 `x<<1|1`，否则也有可能过不了。
- 其他卡常方法。

[方法 3 代码](https://www.luogu.com.cn/paste/tba4o5n3)。

## 方法 4

### 做法 & 思考

前置知识：树链剖分、线段树、差分。

参考 @x义x 的做法。

容易想到，我们不一定要树上差分，我们如果能将树上的一条链给搞成多段连续区间，再差分也是可以的。

所以，我们使用树链剖分将树上的一条链剖成 $\log n$ 个连续区间，然后再进行差分，使得左端点添加 $z$ 种类救济粮，右端点 $+1$ 减少 $z$ 类救济粮即可。

这样，我们只需要算一遍前缀和，我们就可以知道所有节点的答案了。

具体的，若 $dfn_x=u$，则设 $fid_u=x$，则算完 $1 \sim x$ 的前缀和后，你就算出来了 $fid_x$ 节点的答案。

在本题来说，除了 $\mathcal O(n \cdot \alpha(n))$ 的解法（或者说是 $\mathcal O(n)$ 吧，$\alpha(n)$ 直接看成常数，当然题解区确实有一个严格 $\mathcal O(n)$ 的做法），其他的都不如他快了。

树链剖分的常数是很小的，所以本题中，若没有和其他常数很大的数据结构结合，那么这种做法已经算是很优了。

时间复杂度为 $\mathcal O(n \log^2 n)$，并不需要证明，学过树链剖分的都知道。

但不过看在 `oi-wiki` 也没有的份上，我就给个链接（我自己写的），这里就不偏题了，有兴趣的可以自己去看。

[树链剖分时间复杂度证明](https://www.luogu.com.cn/paste/a5qpxy01)。

### 总结

有的时候在树上合并线段树很困难，就可以先转成序列再差分就简单许多倍。

### 代码

[方法 4 代码](https://www.luogu.com.cn/paste/qt3l4fzm)。

## 方法 5

前置知识：树链剖分、动态开点线段树、值域线段树、并查集。

### 暴力

参考 @AC_love 的做法。

首先，我们考虑不差分怎么办。

不差分？首先需要使用树链剖分，先将问题转换为多段连续的区间。

接下来，因为把这些救济粮真的发给他们实在是太不现实了，于是我们转而考虑统计 $y$ 节点有第 $x$ 种救济粮，并且对于每一个救济粮开一个线段树存起来就行了。

这里需要用到动态 $\tt push\_down$ 开点线段树，具体代码如下：

```cpp
void push_down(int x){
	if(lazy[x]){
		if(!ls[x]) ls[x]=++idcnt;
		if(!rs[x]) rs[x]=++idcnt;
		lazy[ls[x]]+=lazy[x],lazy[rs[x]]+=lazy[x],
		mx[ls[x]]+=lazy[x],mx[rs[x]]+=lazy[x],
		mn[ls[x]]+=lazy[x],mn[rs[x]]+=lazy[x],lazy[x]=0;
	}
	return ;
}
void upd(int &x,int l,int r,int fl,int fr){
	if(!x) x=++idcnt;
	if(l==fl && r==fr) {++mx[x],++mn[x],++lazy[x];return ;}
	push_down(x);
	int mid=(l+r)>>1;
	if(fr<=mid) upd(ls[x],l,mid,fl,fr);
	else if(fl>mid) upd(rs[x],mid+1,r,fl,fr);
	else upd(ls[x],l,mid,fl,mid),upd(rs[x],mid+1,r,mid+1,fr);
	mx[x]=max(mx[ls[x]],mx[rs[x]]),
	mn[x]=min(mn[ls[x]],mn[rs[x]]);
	return ;
}
```

变量含义：`ls[x],rs[x]` 分别为 $x$ 的左儿子和 $x$ 的右儿子，`mx[x],mn[x]` 分别为线段树节点 $x$ 所存储的最大值和线段树节点 $x$ 所存储的最小值，`lazy[x]` 为懒标记，`idcnt` 为节点编号。

考虑如何统计答案。

首先，考虑到要统计哪个救济粮数量最多，先从单个救济粮的数量入手。

#### 引理 1 & 证明

先来个引理 $1$：

- 经过 $t$ 次上面的 `upd` 后，线段树最多会分为 $2t+1$ 段极大且值相同的段。对于一段值相同且极大，仅当这一段的所有位置的值都为某个数~~废话~~，该区间极大仅当这个区间的左端点和右端点都不能延申了。

证明：

我们发现，刚开始就有 $1$ 段，这就是 $1$ 的来历。

假设之前有 $x$ 段极大值相同的段（以后简写为 `m-s` 段），那么这一次的修改操作可能导致的结果如下：

- 这一次修改是对其中一个 `m-s` 段内进行了一次 $+1$ 操作。
- 这一次修改是对 $k$ 个 `m-s` 段进行了一次 $+1$ 操作，其中中间的 $k-2$ 段被完全覆盖，开头和结尾两段可能被完全覆盖，也可能只是被覆盖部分。

对于第 $1$ 种情况，如果完全覆盖该 `m-s` 段，则不会产生新的 `m-s` 段；如果只覆盖了左端点或者右端点，则会产生 $1$ 个新的 `m-s` 段（两段分裂），否则就会新产生 $2$ 段 `m-s` 段。

对于第 $2$ 种情况，对于中间的 $k-2$ 个 `m-s` 段不会产生新的 `m-s` 段，讨论最左边和最右边的两个 `m-s` 段。

若最左边和最右边的 `m-s` 段都被完全覆盖，则不会产生新的 `m-s` 段；

若最左边 `m-s` 段的左端点未被覆盖，而最右边的 `m-s` 段被完全覆盖，则会产生 $1$ 个 `m-s` 段；

若最右边 `m-s` 段的右端点未被覆盖，而最左边的 `m-s` 段被完全覆盖，则会产生 $1$ 个 `m-s` 段；

否则会产生 $2$ 个 `m-s` 段。

综上，每一次分裂最多产生 $2$ 个 `m-s` 段，$t$ 次分裂后最多产生 $2t+1$ 个 `m-s` 段。

#### 运用引理 1

我们只需要找到值相同的极大 `m-s` 段，然后对这一段区间进行答案更新即可。

对于每一个 `m-s` 段，最多会分为 $\log n$ 段进行修改，但是最多会有 $n \log n$ 个 `m-s` 段，所以这一部分的时间复杂度为 $\mathcal O(n \log^2 n)$。

考虑如何修改答案。

我们维护一段区间的答案的最小值，如果当前答案比这段区间最小的答案还要裂，则不管；否则更新。

这一次修改，每一个点最坏情况下会被修改 $2\sqrt[2]n$ 次。

至于为什么是这样，很好解释。最坏情况如下：第一次修改，答案被更新为只有一包救济粮的那种，第二次修改，答案被更新为只有两包救济粮的那种，以此类推，第 $2\sqrt[2]n$ 次修改，答案会被更新为只有 $2\sqrt[2]n$ 包救济粮的那种。

所以，有：

$$
\begin{align*}
1+2+\cdots+2\sqrt[2]n=&(1+2\sqrt[2]n) \cdot 2\sqrt[2]n \cdot \frac{1}{2} \\
=& \sqrt[2]n+2n>n
\end{align*}
$$

所以解释完毕。

因为每一个点递归修改需要 $\log n$ 的时间（代码里面分了 $3$ 段函数，那就是 $3 \log n$），所以时间复杂度为 $O(n \log^3 n+n \sqrt[2]n \log n)$。

#### 时间复杂度说明

为什么是 $n \log^3 n+n \sqrt[2]n \log n$ 呢？

首先，我们看第一项：他是 $n \log^2 n \cdot \log n$，其中 $n \log^2 n$ 表示共有 $n \log^2 n$ 段要进行答案更新。

我们来考虑如下情况。

首先，如果一段没有要更新的，那么在这一段被分成了 $\log n$ 段后，程序就会意识过来，没有必要继续往下递归了，就会自己终止，这部分的时间复杂度为 $O(n \log^3 n)$。

否则，如果有一个点要更新，那么就会再走 $\log n$ 的距离去更新这个点，因为每一个点都要走 $\log n$ 的距离才能得到更新，所以这一部分的时间复杂度就是 $\mathcal O(n \sqrt[2] n \log n)$ 的。

所以时间复杂度就是这么多。

可以通过。

### 代码

[方法 5 暴力代码](https://www.luogu.com.cn/paste/ixdlzfm7)。

### 优化

有的人肯定会说了，你这时间复杂度是不是太逆天了，该优化优化了吧。

我们这里来搞搞优化。

首先，我们不用每一次都去更新他的答案，想想可不可以只更新一次就行。这样就更好了。

我们只需要保存下来每一次要更新的东西，然后排一下序，再从大到小更新一遍，更新过的不管，没更新过的更新，这样就可以了。

时间复杂度此时被我们优化到了 $\mathcal O(n \log^3 n+(n \log^2 n) \cdot \log(n \log^2 n)$，其中 $\log(n \log^2 n)$ 的意思不是 $n \log^3 n$，意思是对 $n \log^2 n$ 取以二为底的对数。

考虑能不能进一步优化。

首先，对于排序，因为每一个更新都有两维，第一维是这种救济粮的包数，第二维是救济粮的编号。因为两者均小于 $10^5$，做类似于基数排序的操作，先对第二维排个序，再对第一维排个序，排序的时间复杂度就能被优化到 $\mathcal O(n \log^2 n)$。

考虑对第一部分进行优化。

我们发现，并查集最适合搞这种只覆盖一次的问题了。直接用并查集跳过那些已经被更新的点不就行了么？

不不不，那你的时间复杂度也并没有优化，仍然是 $\mathcal O(n \log^3 n)$ 的。因为只使用路径压缩最坏还是 $\log$ 的。

我们只要能够有办法，再使用一个按秩合并就可以做到常数级了。

对此，我的解决办法是，定义一个 $bid_i$ 表示这个点实际所代表的位置，初始值有 $bid_i=i$。

假设我们现在要使 $fa_x=y$，如果此时 $sz_y$ 更小，则我们在将 $x$ 合并到 $y$ 后，将 $bid_x$ 和 $bid_y$ 互换一下，这样我们得到的 $bid_y$ 就是 $y$ 此时代表的真实编号。

可以自己举几个例子模拟一下。

然后至于在更新的时候，注意要访问到的是那个真实的点 $bid_x$，不是那个没有实在意义的 $x$！！

该部分代码：

```cpp
for(int i=1;i<=gxcnt;++i){
  int l=gx[i].l,r=gx[i].r;
  int x=find(l);
  while(bid[x]<=r) ans[bid[x]]=gx[i].id,merge(bid[x],bid[x]+1),x=find(x);
}
```

其中，`merge` 表示并查集合并，`gx` 表示那 $n \log^2 n$ 个更新答案的东西。

这样我们就以非常妙的方法使得时间复杂度变为 $\mathcal O(n \log^2 n \alpha(n))$ 了，直接忽略掉 $\alpha(n)$ 即可，这是常数级。

但是，咱就是说，因为没差分的原因，常数比人家要大几倍。

### 代码

[方法 5 优化代码](https://www.luogu.com.cn/paste/d57hs28s)。

### 总结

所有的只用路径压缩没用按秩合并的都可以通过 $bid$ 这个巧妙的数组转换为既用按秩合并又路径压缩的并查集，时间复杂度直接优化到常数级。

## 结尾

方法 $6$ 那个 $\mathcal O(n)$ 我现在是实在不会，等我学了虚树后一定过来补。

至于那个并查集，我觉得通过这篇题解，那些只按秩合并的并查集的时间复杂度都将不是问题，~~因为 $bid$ 帮我们解决了所有问题。~~

说句实话，~~希望那群卡只按秩合并的并查集的人不要恨我！~~

---

## 作者：zhou2414 (赞：2)

本文所说线段树均指权值线段树。
# 前置知识
- 线段树（~~废话~~）。
- 树上差分。
### 树上差分
已经会的巨佬们可以跳过。

讲差分是一定要先讲前缀和的。树上前缀和有两种，一种是从根节点到当前节点的路径权值和，一种是这个节点的子树和。这里我们只关心后一种前缀和。

容易发现只要从下往上，将每个节点的所有儿子合并再与它自己合并就可以求出树上前缀和。

由此可以启发出树上差分的方法。

假设我们要让点 $i$ 到点 $j$ 的路径上所有的点权加上 $x$，那么只需要让点 $i,j$ 的权值加上 $x$，让 $lca_{i,j}$ 的权值减去 $x$，同时让 $lca_{i,j}$ 的父节点（如果存在）减去 $x$ 即可。读者可以结合上文所讲树上前缀和，自己去思考一下这样的正确性。
# 线段树合并
## 一般情况
先不考虑树上，先来考虑普通的两棵线段树如何合并。

将两棵线段树合并，那么其实就是建一棵新的线段树，将两棵线段树维护的信息合并在新树上。权值线段树维护的是桶，将两个桶对应下标的值相加即为合并。

那么显然，对于叶子节点，将其维护的值相加即可。对于非叶子节点，直接 `push_up` 即可。具体实现就是一个 dfs 的过程，~~非常简单~~。

实际为了节约空间复杂度，往往选择将一棵线段树合并到另一棵上。

设树的大小为 $n$，这么做的时间复杂度是稳定 $O(n\log n)$ 的。这显然不是我们想要的复杂度。

这时就要用到权值线段树的一个重要技巧：**动态开点**。这样可以最大化节约内存。如果合并时，遇到其中一个线段树的当前节点为空，那么直接将另一个节点作为新线段树对应位置的儿子即可。即共用这个儿子。
### 复杂度分析
将两个线段树合并时，遇到空节点直接返回，也就是只有两个线段树的重合部分会被 dfs 到。所以总的合并次数不会超过较小的线段树的节点数。即单次合并复杂度不会超过 $O(n\log n)$。

如果进行了很多次合并，那么时间复杂度依然是 $O(n\log n)$，原因是如果将两个线段树合并，事实上不会增加新的节点，而较小的线段树永远的消失了，也就是对于每一棵线段树，在合并一次后，要么对方消失，要么自己消失。即所有的节点都只会被合并一次。那么无论合并多少次，总的时间复杂度就是 $O(n\log n)$。

这一部分参考了[这一篇题解](https://www.luogu.com.cn/article/f0qav84x)。

由上面的分析也可知空间复杂度为 $O(n\log n)$。但是常数较大。对于本题，由于利用树上差分修改，每次需要修改至多四个节点，空间复杂度有四倍的常数。
## 树上合并
和一般情况其实并没有什么区别。用树上前缀和的思想，将一个节点所有儿子对应的线段树合并，然后再和它自身合并即可。
# 本题解法
对于每一个节点，开一颗权值线段树，维护值域最大值。修改时利用树上差分进行修改。然后进行树上前缀和合并即可。

时空复杂度 $O(n\log n)$，注意空间有四倍的常数。
# 代码
代码有较为详细的注释。
```cpp
#include<bits/stdc++.h>
#define ll int
#define dd double
#define lson c[id].ls
#define rson c[id].rs
#define mid ((l+r)/2)
using namespace std;
inline ll read(){
	
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
}
const ll N=1e5+9,R=1e5;
ll n,m;
ll ccnt;//动态开点
struct NODE{
	ll ls,rs,sum,lei;//左右儿子，最大值的大小和种类 
}c[N*80];//权值树 
//由于对于每次修改，根据树上差分的思想，只需要修改四个点，由于动态开点
//至多只需要新开4*logn个点，合并是可以共用节点
//所以空间复杂度o(n*4*logn) 
ll root[N*80];//以i号节点为根的权值树的根节点编号 
//ll li[N],p;//离散化数组 长度
ll deep[N],fa[N][20];//lca
ll h[N*2],bcnt;//i节点的最后一条子边的编号 边的最大编号
struct LIAN{
	ll to,ne;
}b[N*2];//链式前向星
ll ans[N];//答案 
//ll getid(ll x){//得到x在离散化数组中的位置
//	return lower_bound(li+1,li+n+1,x)-li;
//}
inline void addb(ll u,ll v){//前向星建立一条从u到v的边

	b[++bcnt].ne=h[u];
	b[bcnt].to=v;
	h[u]=bcnt;
}
void init(ll now,ll father){//lca预处理
	fa[now][0]=father;
	deep[now]=deep[father]+1;
	for(int i=1;i<=19;i++){
		fa[now][i]=fa[fa[now][i-1]][i-1];
	}
	for(ll i=h[now];i;i=b[i].ne){
		if(b[i].to==father){
			continue;
		}
		init(b[i].to,now);
	}
	return;
}
ll lca(ll u,ll v){//u和v的lca
	if(deep[u]!=deep[v]){
		if(deep[u]<deep[v]){
			swap(u,v);
		}
		for(int i=19;i>=0;i--){
			if(deep[fa[u][i]]>=deep[v]){
				u=fa[u][i];
			}
		}
	}
	if(u==v){
		return u;
	}
	for(int i=19;i>=0;i--){
		if(fa[u][i]!=fa[v][i]){
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	return fa[u][0];
}
void pu(ll id){//push_up
	if(lson==0){
		c[id].sum=c[rson].sum;
		c[id].lei=c[rson].lei;
		return;
	}
	if(rson==0){
		c[id].sum=c[lson].sum;
		c[id].lei=c[lson].lei;
		return;
	}
	if(c[lson].sum>=c[rson].sum ){
		c[id].sum =c[lson].sum ;
		c[id].lei =c[lson].lei ;
	}
	if(c[lson].sum <c[rson].sum ){
		c[id].sum =c[rson].sum ;
		c[id].lei =c[rson].lei ;
	}
}
void change(ll &id,ll l,ll r,ll v,ll val){//某个节点上增加一袋v类型的救济粮 
	
	if(!id){
		id=++ccnt;
	}
	if(l==r){
		c[id].sum +=val;//l==r时，此区间只有一种救济粮，可以直接相加 
		c[id].lei =v;
		return;
	}
	if(v<=mid){
		change(lson,l,mid,v,val);
	}
	else{
		change(rson,mid+1,r,v,val);
	}
	pu(id);
}
ll merge(ll u,ll v,ll l,ll r){//将v合并到v上 

	if(u==0||v==0){
		return u+v;
	}
	if(l==r){
		c[u].sum +=c[v].sum ;
		c[u].lei=l;//l==r时，此区间只有一种救济粮，可以直接相加 
		return u;
	} 
	c[u].ls =merge(c[u].ls ,c[v].ls ,l,mid);//当u.ls等0而v.ls不等0时，共用v.ls这个节点，所以u.ls可能变化
	c[u].rs =merge(c[u].rs ,c[v].rs ,mid+1,r);//同上
	pu(u); 
	return u; 
}
void cacl(ll id,ll fa){//统计答案 

	for(int i=h[id];i;i=b[i].ne ){
		ll u=b[i].to ;
		if(u==fa)continue;
		cacl(u,id);
		root[id]=merge(root[id],root[u],1,R);//如果id这个点上没做任何修改，
		//也就是root[id]是一颗空树，那么root[id]可能会与子节点共用一些节点所以可能会改变 
	}
	if(c[root[id]].sum ==0){
		ans[id]=0;
	}
	else{
		ans[id]=c[root[id]].lei ;
	}
}
int main(){
//	freopen("P4556_15.in","r",stdin);
	n=read();
	m=read();
	for(int i=1;i<n;i++){
		
		ll a=read(),b=read();
		addb(a,b);
		addb(b,a);
	} 
	
	init(1,0);
	for(int i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		change(root[x],1,R,z,1);
		change(root[y],1,R,z,1);
		change(root[lca(x,y)],1,R,z,-1);
		change(root[fa[lca(x,y)][0]],1,R,z,-1);//树上差分 
	}
	cacl(1,0);
	for(int i=1;i<=n;i++){
		write(ans[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：AC_love (赞：2)

大家好，这个人没有脑子，没想到树上差分，也不会线段树合并和启发式合并。于是这个人用了一种最暴力的做法把这道题硬艹过去了。

这个人看到题目的第一眼，发现只有一种操作：链加。于是立刻想到用树链剖分 + 线段树来维护。

但这个人很快注意到：链加其实是对于一条链上的每个点发放一袋救济粮，而不同的救济粮之间是互相独立的。所以没办法在一棵线段树上存下所有救济粮的信息。

于是这个人理所当然地想到给每种救济粮各开一棵线段树。那么每次链加操作都可以直接用树剖转化为在对应的线段树上的 $\log n$ 次区间加操作。

显然普通线段树会把空间爆掉，所以这个人开的是动态开点线段树。

执行完所有操作后，这个人开始思考如何统计答案。

他发现他需要统计每个点上哪种救济粮最多。

于是他拿出了之前给每种救济粮开的线段树，分别遍历这些线段树。如果线段树上某个节点对应的区间内，每个点发放的这种救济粮数量都一样多，就可以直接查询一下这个区间内所有的节点，看看当前这种救济粮的数量是否是最多的。

问题被转化成：有一些操作，每组操作给定 $l, r, x, y$，对于 $[l, r]$ 区间内所有 $a_i < x$ 的点，令 $a_i = x, b_i = y$。我们想要的是最终的 $b$ 序列。

这个东西可以用线段树或分块来维护，操作数是 $O(n \log^2 n)$ 的，总复杂度分别为 $O(n \log^3 n)$ 和 $O(n \sqrt n \log^2 n)$。

虽然理论复杂度看起来很劣，但由于实际实现时的常数很小，所以还是可以轻松跑过的。

---

## 作者：Ryanhao (赞：1)

# [【Vani 有约会】雨天的尾巴](https://www.luogu.com.cn/problem/P4556)
欠揍的我不用线段树合并。I use 树剖。

## 思路

发现我们需要维护 $10^5$ 种救济粮，直接在线搞需要开一个 $n\cdot m$ 的数组，空间爆炸。因此我们可以先用 `vector` 标记一下这里应有的操作，到时候把所有的点扫一遍慢慢把操作补上，此时我们发现，太多救济粮，普通的桶在求解时耗时 $O(m)$，过于复杂。考虑使用权值线段树。

传统差分把一次发放操作分成 $4$ 部分：

1. 在从根到 $x$ 的路径上放一袋 $z$；
2. 在从根到 $y$ 的路径上放一袋 $z$；
3. 在从根到 $\operatorname{LCA}(x,y)$的路径上拿掉一袋 $z$；
4. 在从根到 $\operatorname{parent}[\operatorname{LCA}(x,y)]$的路径上拿掉一袋 $z$。

但对于树剖来说，情况就变了：

![](https://cdn.luogu.com.cn/upload/image_hosting/nopx1sqe.png)

如图，我们要给 $5$ 到 $7$ 的节点添加一份救济粮。这实际上会被拆成从 $2$ 到 $5$、从 $6$ 到 $7$ 分别加一份救济粮。再细分，可以拆成如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/5hlnzsdi.png)

如果你担心会被污染，参考两幅图你会发现，只要你给每一段的结尾都封上，就不会导致后面的“污染”。具体操作工艺如下：

```cpp
void upd(int u, int v, int fr) {
  while(top[u] ^ top[v]) {
    if (d[top[u]] < d[top[v]]) swap(u,v);
    mk[I[top[u]]].push_back(make_pair(fr,+1));
    mk[I[u]+1]   .push_back(make_pair(fr,-1));
    // 从 top[u] 到 u 加上救济粮
    // 相当于在 I[top[u]] 打上增加标记，在 I[u]+1 打上减少标记
    u = vat[top[u]];
  }
  if (d[u] > d[v]) swap(u,v);
  mk[I[u]]  .push_back(make_pair(fr,+1));
  mk[I[v]+1].push_back(make_pair(fr,-1));
  // 此处同理。只要封尾勤快，就不会造成“污染”。
}
```
然后就是处理这堆差分了：

```cpp
// 以上省略 1904 字节
int main() {
  // 此处省略 292 字节
  for (int i = 1; i <= n; i++) {
    for (pair<int,int> j : mk[i]) {
      int fr = j.first;
      int w = j.second;
      change(1,fr,w);
      // 暴力地把每个点的差分标到权值线段树里。
      // 总时间复杂度为 O(n log n log n) ???
    }
    ans[i] = T[1].ans;
    // 可以发现 ans 是以 dfs 序存储的
  }
  for (int i = 1; i <= n; i++) {
    printf("%d\n",ans[I[i]]);
    // 因此输出答案时我们要输出其 dfs 序的 ans
  }
  return 0;
}
```
于是完结撒花。

## ACCode

```cpp
// P4556
#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

const int maxn = 1e5+5;
vector<int> G[maxn];
vector<pair<int,int>/**/> mk[maxn];
int siz[maxn],son[maxn],I[maxn];
int vat[maxn],top[maxn],d[maxn];
void init1(int u, int fa) {
  d[u] = d[fa]+1;
  vat[u] = fa;
  siz[u] = 1;
  for (int v : G[u]) {
    if (v == fa) continue;
    init1(v,u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
}
int __cnt;
void init2(int u, int tp) {
  I[u] = ++__cnt;
  top[u] = tp;
  if (son[u]) init2(son[u],tp);
  for (int v : G[u]) {
    if (v == vat[u] || v == son[u]) continue;
    init2(v,v);
  }
}

struct node {
  int l,r,cnt,ans;
} T[maxn<<2];
inline int lch(int x) { return x << 1; }
inline int rch(int x) { return x << 1 | 1; }
void push_up(int u) {
  T[u].cnt = max(T[lch(u)].cnt,T[rch(u)].cnt);
  if (T[lch(u)].cnt || T[rch(u)].cnt) {
    if (T[lch(u)].cnt >= T[rch(u)].cnt) {
      T[u].ans = T[lch(u)].ans;
    } else {
      T[u].ans = T[rch(u)].ans;
    }
  } else T[u].ans = 0;
}
void build(int u, int l, int r) {
  T[u].l = l; T[u].r = r;
  if (l == r) {
    T[u].ans = l; return;
  }
  int mid = (l+r)>>1;
  build(lch(u),l,mid+0);
  build(rch(u),mid+1,r);
  push_up(u); 
}
void change(int u, int x, int w) {
  if (T[u].l == x && T[u].r == x) {
    T[u].cnt += w; return;
  }
  int mid = (T[u].l + T[u].r) >> 1;
  if (x <= mid) change(lch(u),x,w);
  else          change(rch(u),x,w);
  push_up(u);
}

void upd(int u, int v, int fr) {
  while(top[u] ^ top[v]) {
    if (d[top[u]] < d[top[v]]) swap(u,v);
    mk[I[top[u]]].push_back(make_pair(fr,+1));
    mk[I[u]+1]   .push_back(make_pair(fr,-1));
    u = vat[top[u]];
  }
  if (d[u] > d[v]) swap(u,v);
  mk[I[u]]  .push_back(make_pair(fr,+1));
  mk[I[v]+1].push_back(make_pair(fr,-1));
}

int ans[maxn];

int main() {
  int n,m,k = 1e5;
  scanf("%d%d",&n,&m);
  for (int i = 1; i < n; i++) {
    int u,v; scanf("%d%d",&u,&v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  init1(1,0); init2(1,1); build(1,1,k);
  while(m--) {
    int l,r,fr;
    scanf("%d%d%d",&l,&r,&fr);
    upd(l,r,fr);
  }
  for (int i = 1; i <= n; i++) {
    for (pair<int,int> j : mk[i]) {
      int fr = j.first;
      int w = j.second;
      change(1,fr,w);
    }
    ans[i] = T[1].ans;
  }
  for (int i = 1; i <= n; i++) {
    printf("%d\n",ans[I[i]]);
  }
  return 0;
}
```

---

