# Lomsat gelral

## 题目描述

You are given a rooted tree with root in vertex $ 1 $ . Each vertex is coloured in some colour.

Let's call colour $ c $ dominating in the subtree of vertex $ v $ if there are no other colours that appear in the subtree of vertex $ v $ more times than colour $ c $ . So it's possible that two or more colours will be dominating in the subtree of some vertex.

The subtree of vertex $ v $ is the vertex $ v $ and all other vertices that contains vertex $ v $ in each path to the root.

For each vertex $ v $ find the sum of all dominating colours in the subtree of vertex $ v $ .

## 样例 #1

### 输入

```
4
1 2 3 4
1 2
2 3
2 4
```

### 输出

```
10 9 3 4
```

## 样例 #2

### 输入

```
15
1 2 3 1 2 3 3 1 1 3 2 2 1 2 3
1 2
1 3
1 4
1 14
1 15
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13
```

### 输出

```
6 5 4 3 2 3 3 1 1 3 2 2 1 2 3
```

# 题解

## 作者：YellowBean_Elsa (赞：102)

## 这是一道练启发式合并 （dsu on tree） 的好题

### 先简单说一下启发式合并吧

这道题我们可以遍历整棵树，并用一个数组ap（appear）记录每种颜色出现几次

但是每做完一棵子树就需要清空ap，以免对其兄弟造成影响。

而这样做它的祖先时就要把它重新搜一遍，浪费时间

但是我们发现，对于每个节点v，最后一棵子树是不用清空的，因为做完那棵子树后可
以把其结果直接加入v的答案中。

选哪棵子树呢？当然是所含节点最多的一棵咯，我们称之为“重儿子”

其实感觉这样快不了多少……但是它竟然是nlogn的！

### 对于这道题

先用一遍dfs算出每个点是否为重儿子

再dfs统计答案，每次碰到重儿子就跳过，递归完清空ap数组等东东

最后dfs重儿子，不清空

再对当前节点进行另一种dfs，暴力统计ap，不做重儿子

看代码吧~~~（这是帅的人最不关心的部分）

------------我是分割线

```cpp
//written by YellowBean, the AKer of IMO (rubbish)
#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
const int N=2e5+10;
int n;
int c[N];//color
int v[N],nex[N],first[N],tot=1;
inline void add(int x,int y){
	v[++tot]=y;
	nex[tot]=first[x];
	first[x]=tot;
}
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}
ll ans[N],ap[N],mx,sum;//十年OI一场空，不开 long long 见祖宗 
//ap表示每种颜色出现几次 mx表示出现最多的次数 sum表示颜色编号和 
int sz[N];//子树大小 
bool gson[N];//表示一个点是否为重儿子 
void getg(int x,int f){//get 子树大小 以及 重儿子 
	sz[x]=1;
	int mx=0,p=0;
	for(re int i=first[x];i;i=nex[i]){
		int y=v[i];
		if(y==f)continue;
		getg(y,x);sz[x]+=sz[y];
		if(sz[y]>mx){
			mx=sz[y];
			p=y;
		}
	}if(p)gson[p]=1;
}
void DFS(int x,int f,int p){//暴力遍历子树 p为重儿子 之后需init清空 
	//统计答案 
	ap[c[x]]++;
	if(ap[c[x]]>mx){
		mx=ap[c[x]];
		sum=c[x];
	}else if(ap[c[x]]==mx)sum+=c[x];
	for(re int i=first[x];i;i=nex[i]){
		int y=v[i];
		if(y==f || y==p)continue;//不要把重儿子也一起遍历了！ 
		DFS(y,x,p);
	}
}
inline void init(int x,int f){//暴力遍历后清空 
	ap[c[x]]--;
	for(re int i=first[x];i;i=nex[i]){
		int y=v[i];
		if(y==f)continue;
		init(y,x);
	}
}
void dfs(int x,int f){//启发式合并关键函数！ 
	int p=0;//重儿子标记 
	for(re int i=first[x];i;i=nex[i]){
		int y=v[i];
		if(y==f)continue;
		if(!gson[y]){//不是重儿子的暴力做 
			dfs(y,x);
			init(y,x);
			sum=mx=0;
		}
		else p=y;
	}if(p)dfs(p,x);//重儿子单独特判
	DFS(x,f,p);
	ans[x]=sum;
}
int main(){
	n=read();
	for(re int i=1;i<=n;i++)c[i]=read();
	for(re int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y),add(y,x);
	}getg(1,0);
	dfs(1,0);
	for(re int i=1;i<=n;i++)
		printf("%lld ",ans[i]);
}
//those who read but don't copy are handsome
```

关于复杂度证明：

对于每个节点，它被计算的次数就是它到根节点路径上的轻边（连到轻儿子的边）数

我们只需算出轻边有几条

由于每从一个深度为d的节点沿一条轻边走到深度（d-1）的节点，子树大小就至少*2
（这是因为有一个重儿子>=当前子树）

所以最多只有logn条轻边！

故复杂度为O（nlogn）！

#### 皆大欢喜！


---

## 作者：辰星凌 (赞：60)

# **【题解】Lomsat gelral [CF600E]**

[$\mathcal{My}\ \mathcal{Blog}$](https://www.cnblogs.com/Xing-Ling/p/12334816.html)

## **【前言】**

树上启发式合并 $\text{Dsu on tree}$ 一般用来解决一类不带修的子树查询问题（据说这玩意儿原名 静态链分治？）。

其核心思想为：**利用重链剖分的性质优化子树贡献的计算。**

由于 [$\text{zwfymqz}$](https://www.cnblogs.com/zwfymqz/) 巨佬一讲得比较简略，一开始我并没有理解到其精髓，导致一度怀疑其时间复杂度的合理性，甚至连代码都看不懂。  
后来看了看 [$\text{YudeS}$ 楪](https://www.luogu.com.cn/user/118662) 神仙的另一种写法 自己手玩了几棵树就懂了。  
个人认为后者更好理解，因此本文讲解后者，可能与网上大多数写法略有不同。

## **【算法实现】**

先看板题：[$\text{Lomsat gelral [CF600E]}$](https://www.luogu.com.cn/problem/CF600E)

题目描述：给出一棵 $n$ 个结点的树，每个结点都有一种颜色编号，求该树中每棵子树里的出现次数最多的颜色的编号和。

算法流程如下：

- 跑一遍 $dfs$ 预处理出每个点的重儿子 $son$ 。  

- 对于一个点 $x$，首先遍历计算他所有轻儿子的 $ans$，并且每算完一个儿子就要清除它的所有贡献。  
接下来计算重儿子 $son[x]$ 的答案，并保留 $subtree(son[x])$ 中所有点的贡献，然后再暴力加入 $subtree(x)$ 中除 $subtree(son[x])$ 以外的所有点的贡献，此时即可得到 $ans[x]$ 。  
随后回溯到 $fa[x]$，如果 $x$ 是 $fa[x]$ 的轻儿子，那么将在 $x$ 这一波计算下来的贡献全部清除，反之则全部保留。

## **【时间复杂度】**

经过多次~~不靠谱的~~手玩尝试，我们可以发现：每一个点只会在其到根路径中若干重链交界处被统计（也即是从该点到根路径上的轻边数量）。

而由于重链剖分的性质，任意一个点往上跳时所经过的重链数量不超过 $O(logn)$，所以重链交界处（轻边）的数量也不会超过 $O(logn)$，因此每个点的统计次数也为 $O(logn)$ 。

总复杂度为：$O(nlogn)$，并带上一个通常为 $O(1)$ 的常数（统计一个点贡献的复杂度）。

## **【Code】**

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int o,n,m,x,y,t,K,tmp,A[N],Q[N],cnt[N],son[N],size[N],head[N];LL ans,Ans[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void dfs(Re x,Re fa){//预处理重儿子
    size[x]=1;
    for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=fa){
            dfs(to,x),size[x]+=size[to];
            if(size[to]>size[son[x]])son[x]=to;
        }
}
inline void CL(){//清空贡献，从zero开始
    while(t)cnt[Q[t--]]=0;ans=tmp=0;
}
inline void insert(Re x){//加入点x的贡献
    ++cnt[Q[++t]=A[x]];
    if(cnt[A[x]]>tmp)tmp=cnt[ans=A[x]];
    else if(cnt[A[x]]==tmp)ans+=A[x];
}
inline void addson(Re x,Re fa){//加入subtree(x)的贡献（以x为根的整棵子树）
    insert(x);
    for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=fa)addson(to,x);
}
inline void sakura(Re x,Re fa){
    for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=fa&&to!=son[x])sakura(to,x),CL();//计算轻儿子的答案并清空贡献
    if(son[x])sakura(son[x],x);//计算重儿子的答案并保留subtree(son[x])（以son[x]为根的整棵子树贡献）
    for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=fa&&to!=son[x])addson(to,x);//加入subtree(x)-subtree(son[x])-x（以x的所有轻儿子为根的子树贡献）
    insert(x),Ans[x]=ans;//注意还要把x的贡献也加进去
}
int main(){
//  freopen("123.txt","r",stdin);
    in(n),m=n-1;
    for(Re i=1;i<=n;++i)in(A[i]);
    while(m--)in(x),in(y),add(x,y),add(y,x);
    dfs(1,0),sakura(1,0);
    for(Re i=1;i<=n;++i)printf("%lld ",Ans[i]);
}
```

##  **【参考资料】**

- [$\text{Dsu on tree}$ 入门](https://www.cnblogs.com/zwfymqz/p/9683124.html)

---------

## **【后记】**

[$\mathcal{My}\ \mathcal{Blog}$](https://www.cnblogs.com/Xing-Ling/p/12336327.html)

再补充一下另一种做法吧。

大致浏览了网上的题解，常见做法有以下几种：

- $\text{Dsu on tree}$（占大多数，毕竟是板子）

- 线段树合并（空间巨大）

- $O(n\sqrt{n}logn)$ 的 $\text{DFS}$ 序 $+$ $sb$ 暴力莫队（时间巨大）

- $O(n\sqrt{n})$ 的 $\text{DFS}$ 序 $+$ 回滚莫队（效率一般）

但就是没找到一篇 $\text{DFS}$ 序 $+$ 分治，让我来做全网第一篇吧（~~只是我没有找到，希望不要打脸吧~~）。

### **【分析】**

子树查询转到序列上后其本质是一系列的区间查询，我们知道，要想用分治是需要满足一定单调性的，那么这些区间是否有我们想要的性质呢？

先给出一些定义：

- $size(x)$ 表示 $|subtree(x)|$，即以 $x$ 为根的子树大小。

- $dfn(x)$ 表示节点 $x$ 的 $\text{DFS}$ 序。

- $idx(i)$ 表示 $\text{DFS}$ 序 $i$ 所对应的节点编号，满足 $dfn(idx(i))=i,\ idx(dfn(x))=x$。

- $Rdfn(i)$ 表示 $i+size(idx(i))-1$，即 $\text{DFS}$ 序 $i$ 所对应的的节点子树中最大的 $\text{DFS}$ 序。

#### **【引理】**

**抛结论**：   
设 $i'<i$，若存在一个 $j$ 满足 $i \leqslant j \leqslant Rdfn(i)$ 且 $i' \leqslant j \leqslant Rdfn(i')$，那么 一定有 $Rdfn(i') \geqslant Rdfn(i)$ 。  
（按照 [$\text{YudeS}$ 楪](https://www.cnblogs.com/yudes/) 巨佬所说，穿过 $j$ 的区间有互相包含的关系，放在此处即是区间 $[i,Rdfn(i)]$ 被包含于 $[i',Rdfn(i')]$ 中 ）。

其实很简单，稍想一下就明白了。

**证明**：  
由给出的两个条件可知 $idx(j) \in subtree(idx(i))$ 且  $idx(j) \in subtree(idx(i'))$，所以 $idx(i),idx(i')$ 均为$idx(j)$ 的祖先节点。  
又因为 $i'<i$，且任意一个节点 $x$ 的所有祖先都在从根到 $x$ 的简单路径上，所以 $idx(i')$ 应为 $idx(i)$ 的祖先节点，于是有 $Rdfn(i') \geqslant Rdfn(i)$。

#### **【算法实现】**

回到这道题，有了上面那个性质，用分治已经很显然了吧，对于一层 $(L,mid,R)$ 扫一遍计算出：满足 $L \leqslant i \leqslant mid$ 且 $mid+1 \leqslant Rdfn(i) \leqslant R$ 的所有 $ans[i]$ 。

时间复杂度为：$O(nlogn)$。

核心操作就一个分治函数，好想又好写，居然没人用....

像这种 $dot$ 的题应该都可以用 $\text{DFS}$ 序 $+$ 回滚莫队/分治 搞吧，$insert$ 函数都不需要改，时间复杂度和分治基本一样（~~蒟蒻瞎口胡，可信度极低~~）

### **【Code】**

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int o,n,m,x,y,t,tmp,dfn_O,A[N],Q[N],cnt[N],dfn[N],idx[N],size[N],head[N];LL ans,Ans[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void dfs(Re x,Re fa){//预处理dfn序
    idx[dfn[x]=++dfn_O]=x,size[x]=1;
    for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=fa)dfs(to,x),size[x]+=size[to];
}
inline void CL(){//清空贡献，从zero开始
    while(t)cnt[Q[t--]]=0;ans=tmp=0;
}
inline void insert(Re x){//加入点x的贡献
    ++cnt[Q[++t]=A[x]];
    if(cnt[A[x]]>tmp)tmp=cnt[ans=A[x]];
    else if(cnt[A[x]]==tmp)ans+=A[x];
}
inline void sakura(Re L,Re R){//分治解决(L,R)
    if(L==R){if(size[L]==1)Ans[L]=A[L];return;}
    Re mid=L+R>>1;
    sakura(L,mid),sakura(mid+1,R);//递归解决下面的
    Re p=mid;CL();//搞一个指针p
    for(Re i=mid,j;i>=L&&(j=i+size[idx[i]]-1)<=R;--i){//当j=Rdfn(i)大于R时就可以结束了
        insert(idx[i]);
        if(j<=mid)continue;//只解决对于j>mid的部分
        while(p<j)insert(idx[++p]);//由性质可知满足大于mid的那部分j是单调递增的，不断移动指针p即可
        Ans[idx[i]]=ans;//获得答案
    }
}
int main(){
//  freopen("123.txt","r",stdin);
    in(n),m=n-1;
    for(Re i=1;i<=n;++i)in(A[i]);
    while(m--)in(x),in(y),add(x,y),add(y,x);
    dfs(1,0),sakura(1,n);
    for(Re i=1;i<=n;++i)printf("%lld ",Ans[i]);
}
```

#### **【参考资料】**

- [$\text{YudeS}$ 楪](https://www.luogu.com.cn/user/118662) 神仙的 $\text{DFS}$ 序分治代码。



---

## 作者：Styx (赞：39)

没有人写线段树合并吗qwq  
反正蒟蒻来写线段树合并的题解啦～

就是把每个点的颜色先插入每个点的对应的线段树里，然后dfs时把子树的线段树合并到父节点上，维护题意要求的值就可以了

代码长这样：
```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson tr[now].l
#define rson tr[now].r
#define int long long
using namespace std;

struct tree
{
	int l,r,sum,val,ans;
}tr[5000050];

int rt[100010],cl[100010],cnt,n,anss[100010];
vector<int> g[100010];

int push_up(int now)
{
	if(tr[lson].sum>tr[rson].sum)
	{
		tr[now].sum=tr[lson].sum;
		tr[now].val=tr[lson].val;
		tr[now].ans=tr[lson].ans;
	}
	if(tr[rson].sum>tr[lson].sum)
	{
		tr[now].sum=tr[rson].sum;
		tr[now].val=tr[rson].val;
		tr[now].ans=tr[rson].ans;
	}
	if(tr[lson].sum==tr[rson].sum)
	{
		tr[now].sum=tr[lson].sum;
		tr[now].val=tr[lson].val;
		tr[now].ans=tr[lson].ans+tr[rson].ans;
	}
}

int update(int &now,int l,int r,int pos,int v)
{
	if(!now) now=++cnt;
	if(l==r)
	{
		tr[now].val=l;
		tr[now].sum+=v;
		tr[now].ans=l;
		return 0;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) update(lson,l,mid,pos,v);
	else update(rson,mid+1,r,pos,v);
	push_up(now);
}

int merge(int a,int b,int l,int r)
{
	if(!a) return b;
	if(!b) return a;
	if(l==r)
	{
		tr[a].val=l;
		tr[a].sum+=tr[b].sum;
		tr[a].ans=l;
		return a;
	}
	int mid=(l+r)>>1;
	tr[a].l=merge(tr[a].l,tr[b].l,l,mid);
	tr[a].r=merge(tr[a].r,tr[b].r,mid+1,r);
	push_up(a);
	return a;
}

int dfs(int now,int f)
{
	for(int i=0;i<g[now].size();i++)
	{
		if(g[now][i]==f) continue;
		dfs(g[now][i],now);
		merge(rt[now],rt[g[now][i]],1,100000);
	}
	update(rt[now],1,100000,cl[now],1);
	anss[now]=tr[rt[now]].ans;
}

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&cl[i]);
		rt[i]=i;
		cnt++;
	}
	int from,to;
	for(int i=1;i<n;i++)
	{
		scanf("%lld%lld",&from,&to);
		g[from].push_back(to);
		g[to].push_back(from);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		printf("%lld ",anss[i]);
	}
}
```

---

## 作者：King_of_gamers (赞：26)

这题可以说是线段树合并板子题了......

那我们现在就先来说说线段树合并该怎么做.问题是这样的:给你两棵动态开点线段树tree1和tree2,让你合并成tree3(注意一定要是动态开点,不然时空复杂度会爆炸).

我们考虑当前正在合并tree1的k1节点和tree2的k2节点

#### 1.k1节点为空,k2节点为空

如果是这种情况,那么合并后显然还是为空,于是我们就不用继续递归处理.


#### 2.k1节点为空,k2节点不为空

这种情况下合并后显然只有k2,那么直接把新树的tree3的k3节点赋值成k2节点就好了.

#### 3.k1节点不为空,k2节点为空.

和第二种情况类似,赋值成k1就行了.

前三种情况用代码表示也就是:

```
if ((k1==0)||(k2==0)) return k1+k2;
```

#### 4.k1节点不为空,k2节点也不为空.

那么合并这颗树就要再递归合并了.

用代码表示也就是:

```
t[k3].l=merge(t[k1].l,t[k2].l,l,mid);
t[k3].r=merge(t[k1].r,t[k2].r,mid+1,r);
```

#### 整个合并过程也就是:

```

	if ((k1==0)||(k2==0)) return k1+k2;
	if (l==r) return k1;
	int mid=(l+r)>>1;
	t[k1].l=merge(t[k1].l,t[k2].l,l,mid);
	t[k1].r=merge(t[k1].r,t[k2].r,mid+1,r);
	return k1;
```

#### 那么讲完了线段树合并,就该讲讲这题了.

对于每个节点u,我们把u的子树信息塞进动态开点权值线段树里,我们可以在线段树上维护出所有个数最大的下标之和.我们定义$t[i].max$表示i这个区间里个数最大有几个,$t[i].ans$为个数最大的下标之和是多少,那么节点u的答案也就是t[root[u]].ans了.

考虑暴力情况,如果我们做到每个点都把所有子树都加进线段树里面一次复杂度是根据树高而变化的,复杂度也就是$树高*n*logn$,在最好的情况里也是$nloglogn$,实在不可取.

那我们就可以用一个线段树合并的方法了!

假设我们当前递归到节点u,就把所有u的所有儿子v的线段树给合并起来然后把节点u的权值更新一下就行了,不用把所有的点都重新加进线段树一遍.

那么这么做的时间复杂度会是多少呢?线段树合并的复杂度其实是和叶节点个数有关系的.在这题里面我们只会加进去$n$个节点,所以线段树合并的时间复杂度也就是$nlogn$,但是遗憾的是空间复杂度也会是$nlogn$(别跟我说动态开点线段树开n个点不是$nlogn$),但这题还是能做的,做到这边我们就可以完美解决了这题了.

最后附上代码,有些小注释

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node//我定义的t
{
	int l,r,max;
	long long ans;
}t[10000005];
int n,u,v,top,nex[200005],head[100005],go[200005],root[100005],color[100005];
long long ans[100005];
void add(int u,int v)//链式前向星
{
	top++;
	nex[top]=head[u];
	head[u]=top;
	go[top]=v;
}
int merge(int k1,int k2,int l,int r)//即当前合并k1节点和k2节点
{
	if ((k1==0)||(k2==0)) return k1+k2;//考虑前三种情况
	if (l==r)//边界情况就是max值相加
	{
		t[k1].max=t[k1].max+t[k2].max;
		return k1;
	}
	int mid=(l+r)>>1;//第四种情况就是递归合并
	t[k1].l=merge(t[k1].l,t[k2].l,l,mid);
	t[k1].r=merge(t[k1].r,t[k2].r,mid+1,r);
    //下面这一段是push_up,也就是线段树常规维护
	int ls=t[k1].l,rs=t[k1].r;
	if (t[ls].max>t[rs].max)
	{
		t[k1].max=t[ls].max;
		t[k1].ans=t[ls].ans;
	}
	else
	if (t[ls].max<t[rs].max)
	{
		t[k1].max=t[rs].max;
		t[k1].ans=t[rs].ans;
	}
	else
	{
		t[k1].max=t[ls].max;
		t[k1].ans=t[ls].ans+t[rs].ans;
	}
	return k1;
}
void add(int p,int l,int r,int k)//在权值线段树中加入p这个点
{
	if (l==r)
	{
		t[k].max++;
		t[k].ans=l;
		return;
	}
	int mid=(l+r)>>1;
	if (p<=mid) 
	{
		if (t[k].l==0)
		{
			top++;
			t[k].l=top;
		}
		add(p,l,mid,t[k].l);
	}
	else
	{
		if (t[k].r==0)
		{
			top++;
			t[k].r=top;
		}
		add(p,mid+1,r,t[k].r);
	}
	int ls=t[k].l,rs=t[k].r;
	if (t[ls].max>t[rs].max)
	{
		t[k].max=t[ls].max;
		t[k].ans=t[ls].ans;
	}
	else
	if (t[ls].max<t[rs].max)
	{
		t[k].max=t[rs].max;
		t[k].ans=t[rs].ans;
	}
	else
	{
		t[k].max=t[ls].max;
		t[k].ans=t[ls].ans+t[rs].ans;
	}
}
void dfs(int u,int fa)
{
	for (int i=head[u];i!=0;i=nex[i])//先递归儿子
	{
		int v=go[i];
		if (v!=fa)
		{
			dfs(v,u);
			root[u]=merge(root[u],root[v],1,n);//把儿子合并
		}
	}
	if (root[u]==0)
	{
		top++;
		root[u]=top;
	}
	add(color[u],1,n,root[u]);//把节点u的权值更新
	ans[u]=t[root[u]].ans;//更新答案
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	scanf("%d",&color[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for (int i=1;i<=n;i++)//输出答案
	printf("%lld ",ans[i]);
}
```

---

## 作者：He_Ren (赞：25)

比赛的时候不会启发式合并所以没写出来

暴力是不难想的，对于每个点，求出$cnt[u][clr]$表示点$u$的子树，颜色$clr$的出现次数；然后对于每个点，分别求出答案

这个方法肯定会TLE+MLE

**这可以成为比赛的一贯思路，先想暴力，然后加以优化或寻找规律；做题不能要求一步登天**

我们可以分部分考虑这个问题

先考虑如何求$cnt$

不难想到用map保存，$t[u][clr]$表示点$u$的子树，颜色$clr$的出现次数

这样看起来使程序更慢了，于是考虑如何优化

**这里就是启发式合并的核心思想**

思考一下，在合并两棵子树时，是 将小的合并到大的上 还是 将大的合并到小的上？

当然是前者，将小的合并到大的上

看起来没优化多少，但是现在算一下这种方法的时间复杂度

每个map在被合并给其他map时，长度最少变为原来的两倍，那么一个map最多被合并多少次？

显然是$O(\log n)$级的

换句话说，每个点最多被移动的次数是$O(\log n)$级的，那么总共就是$O(n\log n)$级的，算上map的时间，总时间是$O(n\log^2 n)$

然后第二部分，计算答案，只要对每个点记录$mx[u]$（最大出现次数）和$ans[u]$（此次数对应的答案），然后在合并时维护就行了

代码实现不多说，这种题是练习stl的好题

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef pair<int,ll> pil;
#define fir first
#define sec second
#define mp make_pair
const int MAXN = 1e5 + 5;

struct Edge
{
	int next,to;
}e[MAXN*2];
int head[MAXN],etot=0;
inline void add(int u,int v)
{
	e[++etot] = (Edge){ head[u],v};
	head[u]=etot;
}

int c[MAXN];

map<int,int> t[MAXN];
int mx[MAXN];
ll ans[MAXN];
int p[MAXN];

void dfs(int u,int fa)
{
	p[u]=u;
	t[u][c[u]]=1;
	mx[u]=1;
	ans[u]=c[u];
		
	for(int i=head[u]; i; i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
		if(t[p[u]].size() < t[p[v]].size())
		{
			swap(p[u],p[v]);
			mx[u]=mx[v];
			ans[u]=ans[v];
		}
		
		map<int,int> &mpu=t[p[u]], &mpv=t[p[v]];
		for(map<int,int>::iterator it=mpv.begin(); it!=mpv.end(); ++it)
		{
			int clr=it->fir, tot=it->sec;
			mpu[clr] += tot;
			
			if(mpu[clr]>mx[u])
				mx[u]=mpu[clr], ans[u]=0;
			if(mpu[clr]==mx[u])
				ans[u]+=clr;
		}
	}
}

int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&c[i]);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v); add(v,u);
	}
	
	dfs(1,0);
	for(int i=1; i<=n; ++i) cout<<ans[i]<<' ';
	return 0;
}
```


---

## 作者：MILLOPE (赞：17)

## 题目

一棵树有n个结点，每个结点都是一种颜色，每个颜色有一个编号，求树中每个子树的最多的颜色编号的和。（注意不是颜色和而是节点的编号和）

## 题解

-   ~~线段树合并的板子题~~
-   这道题首先我们需要一个维护在值域范围内的线段树（权值线段树），而如果我们直接建造一棵树复杂度会非常高。 为了降低复杂度，我们可以不用建出整个线段树的结构，在我们需要时再建出我们想要的节点。这种方法维护的线段树叫做动态开点线段树。 
-   而线段树合并就是将两棵动态开点的线段树合并到一起。 合并具体操作见代码（~~其实很好理解~~）
-   对于本题来说$t[i].max$表示区间$i$内颜色最多的节点个数，$t[i].ans$表示区间答案
-   直接$dfs$更新即可

## code

```cpp
#include <bits/stdc++.h> 
using namespace std; 
const int maxn = 1e5 + 100; 
typedef long long LL; 

template <class T> 
inline void read(T &s) {
	s = 0; T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

int n, m, tot, cnt; 
int c[maxn], lin[maxn], rt[maxn]; 
LL ans[maxn]; 
struct node {
	int next, to; 
} e[maxn << 1]; 
struct tree {
	int lc, rc, num; 
	LL ans; 
} t[maxn * 60]; 

inline void add(int from, int to) {
	e[++tot].to = to; 
	e[tot].next = lin[from]; 
	lin[from] = tot; 
}

void push_up(int p) {
	int ls = t[p].lc, rs = t[p].rc; 
	if (t[ls].num > t[rs].num) {
		t[p].num = t[ls].num; 
		t[p].ans = t[ls].ans; 
	}
	else if (t[ls].num < t[rs].num) {
		t[p].num = t[rs].num; 
		t[p].ans = t[rs].ans; 
	}
	else {
		t[p].num = t[ls].num; 
		t[p].ans = t[ls].ans + t[rs].ans; 
	}
	return ; 
}

int merge(int p, int q, int l, int r) {
	if (!p || !q) return p + q; 
	if (l == r) {
		t[p].num += t[q].num; 
		t[p].ans = l; 
		return p; 
	}
	int mid = (l + r) >> 1; 
	t[p].lc = merge(t[p].lc, t[q].lc, l, mid); 
	t[p].rc = merge(t[p].rc, t[q].rc, mid + 1, r); 
	push_up(p); 
	return p; 
}

void update(int &p, int l, int r, int x) {
	if (!p) p = ++cnt; 
	if (l == r) {
		t[p].num++; 
		t[p].ans = l; 
		return ; 
	}
	int mid = (l + r) >> 1; 
	if (x <= mid) update(t[p].lc, l, mid, x); 
	else update(t[p].rc, mid + 1, r, x); 
	push_up(p); 
}

void dfs(int u, int fa) {
	for (int i = lin[u]; i; i = e[i].next) {
		int v = e[i].to; 
		if (v == fa) continue; 
		dfs(v, u); 
		rt[u] = merge(rt[u], rt[v], 1, maxn); 
	}
	update(rt[u], 1, maxn, c[u]); 
	ans[rt[u]] = t[rt[u]].ans; 
}

int main() {
	read(n); cnt = n; 
	for (int i = 1; i <= n; ++i) {
		read(c[i]); 
		rt[i] = i; 
	}
	for (int i = 1; i < n; ++i) {
		int x, y; read(x), read(y); 
		add(x, y); add(y, x); 
	}
	dfs(1, 0); 
	for (int i = 1; i <= n; ++i) 
		printf("%lld ", ans[i]); 
	return 0; 
}
```





---

## 作者：abjfj (赞：16)

关于dsu on tree qwq

在查询子树信息时 如果不把信息清空 会对其他子树产生影响

然而 可以看到的是 当前节点的最后一个子树 是不会对其他子树产生影响的

所以 我们选择不清空最后一个子树 而是保留它

我们选择 大小最大的那个子树 也就是以当前节点的重儿子为根的子树！

这样复杂度就由原来的n^2 变为了 nlogn！

dalao们证的都比我好我就不证了qwq(懒 

推广到每个节点 用这个方法去处理 自然也是成立的

```cpp
#include<iostream>
#include<cstdio>
#define int long long
#define maxn 100001
using namespace std;
void read(int &x)
{
	x = 0;int f = 1;
	char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')f = -1; ch = getchar();}
	while(isdigit(ch)){x = (x<<3) + (x<<1) + ch - '0'; ch = getchar();}
	x = x*f;
} 
int color[maxn],son[maxn],size[maxn],fa[maxn];
int ans[maxn],cnt[maxn],sum = 0,Max = 0,Son = 0;
int head[maxn],nxt[maxn<<1],ver[maxn<<1],tot = 0;
int n,root = 1;
void add(int x,int y)
{
	nxt[++tot] = head[x]; head[x] = tot; ver[tot] = y;	
}
void dfs1(int x,int f)
{
	size[x] = 1; fa[x] = f;
	int maxson = 0;
	for(int i = head[x]; i; i = nxt[i])
	{
		int y = ver[i];
		if(y == f)continue;
		dfs1(y,x);
		size[x] += size[y];
		if(size[y] > maxson)son[x] = y,maxson = size[y];
	}
}
void change(int x,int val)
{
	cnt[color[x]] += val;
	if(cnt[color[x]] > Max)Max = cnt[color[x]],sum = color[x];
	else if(cnt[color[x]] == Max)sum += color[x];
	for(int i = head[x]; i; i = nxt[i])
	{
		//注意此处 
		//由于重儿子的信息没有被删去 已经统计过了 所以不能再计算一次。 
		int y = ver[i];
		if(y == fa[x] || y == Son)continue;
		change(y,val);
	}
}
void dfs2(int x,int opt)
{
	for(int i = head[x]; i; i = nxt[i])
	{
		int y = ver[i];
		if(y == fa[x] || y == son[x])continue;
		dfs2(y,0);
	}
	if(son[x])dfs2(son[x],1),Son = son[x];
	change(x,1);ans[x] = sum;Son = 0;
	if(!opt)change(x,-1),sum = Max = 0;
}
signed main()
{ 
	read(n);
	for(int i = 1; i <= n; i++)read(color[i]);
	for(int i = 1; i <= n-1; i++)
	{
		int x,y; read(x),read(y); add(x,y),add(y,x);
	}
	dfs1(root,0);
	dfs2(root,0);
	for(int i = 1; i <= n; i++)printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：线段树壹零 (赞：9)

没有多少人用莫队做吗？

~~蒟蒻水一波莫队~~

时间复杂度（$n\sqrt{n}logn$)

~~蒟蒻过菜，不会去掉logn的做法qaq~~

思路很简单：

1.dfs跑一下树上点的dfs序。

2.将树上点按dfs序进行$\sqrt{n}$ 分块。

3.对每个点按左端点的块序号和右端点的大小排序。

```cpp
inline int cmp(Node aa,Node bb)
{
	return aa.ls==bb.ls?aa.r<bb.r:aa.ls<bb.ls;
}
```

4.开始莫队，用num[x]数组统计出现x次的颜色的序号和。转移时将原先的减去，再加上现在的。

```cpp
inline void add(int x)
{
	int xx=coll[x];
	if(num[xx])
	add(num[xx],-xx,1);
	num[xx]++;
	add(num[xx],xx,1);
}
inline void del(int x)
{
	int xx=coll[x];
	add(num[xx],-xx,1);
	num[xx]--;
	if(num[xx])
	add(num[xx],xx,1);
}
```
5.将num用线段树维护最大值。

6.查找num[x]中使num[x]！=0的x最大值，并num[x]为答案。（用线段树维护）

p.s.程序理论上时间复杂度爆了，但是经过我在考场上拍的时候没有多少数据可以卡掉，并且可以卡掉这个程序的数据第二次试的时候就不会爆，所以这个程序只要评测机高兴，就不会挂。

上代码（预警，代码中含有大量无用数组）

码长：3000B

~~当当当当~~

```cpp
#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define ll long long
using namespace std;
inline ll read()
{
	ll f=0,x=1;char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')x=-1;ch=getchar();
	}
	while(ch>='0'&&ch<='9')f=(f<<1)+(f<<3)+ch-'0',ch=getchar();
	return f*x;
}
ll n,col[100009],siz,cnt=0,head[100009],dfn[100009],
	l[100009],r[100009],num[100009],ans=0,maxx=0,anss[100009],
	coll[100009];
struct edge
{
	ll to,nxt;
}e[200009];
struct Node
{
	ll l,r,id,bh,col,ls,rs;
}a[100009];
struct segtree
{
	ll l,r,w;
}tree[400009];
inline void adde(int a,int b)
{
	cnt++;
	e[cnt].nxt=head[a];
	e[cnt].to=b;
	head[a]=cnt;
}
inline void dfs(int x,int fa)
{
	dfn[x]=++cnt;
	l[cnt]=x;coll[cnt]=col[x];
	a[cnt].id=x;a[cnt].l=cnt;a[cnt].col=col[x];
	for(int i=head[x];~i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,x);
	}
	r[x]=cnt;
	a[dfn[x]].r=cnt;
}
inline int cmp(Node aa,Node bb)
{
	return aa.ls==bb.ls?aa.r<bb.r:aa.ls<bb.ls;
}
inline void build(int l,int r,int p)
{
	tree[p].l=l;tree[p].r=r;
	if(l==r)
	return ;
	int mid=(l+r)>>1;
	build(l,mid,p*2);build(mid+1,r,p*2+1);
}
inline void add(int x,int xx,int p)
{
	if(tree[p].l==tree[p].r)
	{
		tree[p].w+=xx;
		//printf("%d %d %d\n",tree[p].l,tree[p].r,tree[p].w);
		return ;
	}
	int mid=(tree[p].l+tree[p].r)>>1;
	if(x<=mid)add(x,xx,p*2);
	else add(x,xx,p*2+1);
	tree[p].w=tree[p*2].w+tree[p*2+1].w;
	//printf("%d %d %d %d\n",tree[p].l,tree[p].r,tree[p].w,xx);
}
inline void add(int x)
{
	int xx=coll[x];
	//ans[num[xx]]-=x;
	if(num[xx])
	add(num[xx],-xx,1);
	num[xx]++;
	add(num[xx],xx,1);
	//printf("!!!%d %d %d\n",x,xx,a[x].id);
	//ans[num[xx]]+=x
	//if(num[x]==maxx)ans+=x;
}
inline void del(int x)
{
	int xx=coll[x];
	add(num[xx],-xx,1);
	num[xx]--;
	//printf("!!!%d %d %d\n",x,xx,a[x].id);
	if(num[xx])
	add(num[xx],xx,1);
}
inline void find(int l,int r,int p)
{
	if(ans)return ;
	if(l<=tree[p].l&&r>=tree[p].r){
		int mid=(tree[p].l+tree[p].r)>>1;
		if(tree[p].l==tree[p].r){
			ans=max(ans,tree[p].w);return ;
		}
		if(tree[p*2+1].w)find(l,r,p*2+1);
		else if(tree[p*2].w)find(l,r,p*2);
		return ;
	}
	int mid=(tree[p].l+tree[p].r)>>1;
	if(r>mid)find(l,r,p*2+1);
	if(l<=mid)find(l,r,p*2);
}
int main()
{
	n=read();siz=sqrt(n);
	build(1,n,1);
	memset(head,-1,sizeof(head));
	//printf("%d\n",n);
	for(int i=1;i<=n;i++){
		col[i]=read(); 
	}
	for(int i=1;i<=n-1;i++){
		int a=read(),b=read();
		adde(a,b);adde(b,a);
	}
	cnt=0;
	dfs(1,1);
	for(int i=1;i<=n;i++)
	{
		a[i].ls=(a[i].l+siz-1)/siz;
	}
	sort(a+1,a+n+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=n;i++)
	{
		ans=0;
		while(r<a[i].r)add(++r);
		while(r>a[i].r)del(r--);
		while(l<a[i].l)del(l++);
		while(l>a[i].l)add(--l);
		find(1,n,1);
		anss[a[i].id]=ans;
		//printf("ans %d %d %d %d\n",a[i].l,a[i].r,a[i].id,ans);
	}
	for(int i=1;i<=n;i++)printf("%lld ",anss[i]);
	return 0;
}
```

---

## 作者：曾爷爷 (赞：9)

Dsu on Tree 板子题
具体思想康代码
```cpp
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define int long long
#define N 100005
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1 == p2)?EOF:*p1++)
using namespace std ;
//char buf[(1 << 22)] , *p1 = buf , *p2 = buf ;
inline int read ()
{
    char c = getchar () ; int x = 0 , f = 1 ;
    while (c < '0' || c > '9') { if (c == '-') f = -1 ; c = getchar () ; }
    while (c >= '0' && c <= '9'){ x = x * 10 + c - '0' ; c = getchar () ; }
    return x * f ;
}
int n , sz[N] , ver[N << 1] , nxt[N << 1] , hed[N << 1] , col[N] , sum , cnt[N] , ans[N] , son[N] , mx , tot ;
void add (int x , int y) { ver[++ tot] = y ; nxt[tot] = hed[x] ; hed[x] = tot ; }
void dfs (int x , int fa) //找每个节点的重儿子，不用讲了吧
{
	int mx = -1e9 ;
	sz[x] = 1 ;
	for (int i = hed[x] ; i ; i = nxt[i])
	{
		int y = ver[i] ;
		if (y == fa) continue ;
		dfs (y , x) ;
		sz[x] += sz[y] ;
		if (sz[y] > mx)
		{
			mx = sz[y] ;
			son[x] = y ;
		}
	}
}
void change (int x , int fa , int val , int p) //p是不能访问的点 
{
	cnt[col[x]] += val ;//统计当前这个颜色出现的次数
	if (cnt[col[x]] > mx) mx = cnt[col[x]] , sum = col[x] ;//更新答案
	else if (cnt[col[x]] == mx) sum += col[x] ;//如果没有更大值，就加上答案
	for (int i = hed[x] ; i ; i = nxt[i])
	{
		int y = ver[i] ;
		if (y == fa || y == p) continue ;//如果是当前这个点的父亲或是不能访问的点就不要计算
		change (y , x , val , p) ;
	} 
}
void dsu (int x , int fa , int op)//op [0/1]表示是轻儿子或重儿子
{
	for (int i = hed[x] ; i ; i = nxt[i])
	{
		int y = ver[i] ;
		if (y == fa || y == son[x]) continue ;// 如果是当前这个点的父亲或是重儿子就不要计算
		dsu (y , x , 0) ;//计算轻儿子
	}
	if (son[x]) dsu (son[x] , x , 1) ;//如果x的重儿子是y，就递归重儿子，不消除影响
	change (x , fa , 1 , son[x]) ;//暴力统计轻儿子的答案
	ans[x] = sum ;//记录答案
	if (op == 0) change (x , fa , -1 , 0) , sum = mx = 0 ;//如果要删除贡献的话就删除
}
signed main ()
{
//	freopen ("dsutree.in" , "r" , stdin) ; freopen ("dsutree.out" , "w" , stdout) ;
	n = read () ;
	for (int i = 1 ; i <= n ; i ++) col[i] = read () ;
	for (int i = 1 , x , y ; i < n ; x = read () , y = read () , add (x , y) , add (y , x) , i ++) ;
	dfs (1 , 0) ;
	dsu (1 , 0 , 0) ;
	for (int i = 1 ; i <= n ; i ++) printf ("%lld " , ans[i]) ;
}
```

---

## 作者：Holy_Push (赞：7)

一开始想拿这道题做树上启发式合并的练习题的……后来发现，貌似莫队更好想一点。

这种处理子树信息的问题，一般有两种选择，一种是树上合并（启发式合并、线段树合并等），一种是$dfs$序。$dfs$序可以将子树问题转化为区间问题，这样我们就可以用莫队啦！

我们记$dfn[x],size[x]$为$x$的$dfs$序和子树大小，那么$x$的子树就可以映射到$dfs$序中$[dfn[x],dfn[x]+size[x]-1]$这一段。我们用莫队处理这个问题就很方便了，每次移动维护最大值及最大值的编号和即可。

但是我们发现维护最大值是很难实现的，因为最大值不具有可减性。这时候我们可能会想到用线段树或者$set$帮忙维护，这样我们可以做到$O(n\sqrt nlogn)$的复杂度，并不是很优秀。

如何把$logn$给去掉呢？我们使用分块。众所周知，根号算法和根号算法放在一起比较搭，因为如果使用$log$数据结构，每移动一次指针都需要$log$的时间。而如果使用分块，则可以变为用$O(1)$时间移动指针，在每次指针移完后用$\sqrt n$的时间处理答案。

我们记录$f[x],Count[x],tag[x]$三个变量。其中$f[x]$表示颜色为$x$的点出现的次数，$Count[x]$表示出现次数为$x$的点的编号和，$tag$是分块数组，$tag[x]$表示位于第$x$块的所有$Count$的和，这样指针移动一次就只需要$O(1)$时间了。

至于指针移完之后如何处理，就很简单了。先用$\sqrt n$的时间遍历一遍$tag$数组，找到最大的有值的块，然后再在这个块内找最大的$Coung[i]$即可。整体时间复杂度$O(n\sqrt n)$

```cpp
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
const int N=200000;
int n,blk[N],fst[N],lst[N],dfn[N],cnt;
int ans[N],c[N],C[N],size[N],S,f[N],Count[N],tag[N];
vector<int>V[N];

struct Que
{
	int L,R,id;
	bool operator <(const Que &x) const {return blk[L]<blk[x.L]||blk[L]==blk[x.L]&&R<x.R;}
} Q[N];

void dfs(int x,int fat)
{
	dfn[x]=++cnt;size[x]=1;c[cnt]=C[x];
	for (int i=0,s=V[x].size();i<s;i++)
	{
		int v=V[x][i];if (v==fat) continue;
		dfs(v,x);size[x]+=size[v];
	}
	Q[x].L=dfn[x];Q[x].R=dfn[x]+size[x]-1;Q[x].id=x;
}

signed main()
{
	scanf("%lld",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&C[i]);
	for (int i=1;i<n;i++)
	{
		int x,y;scanf("%lld%lld",&x,&y);
		V[x].push_back(y);V[y].push_back(x);
	}
	dfs(1,0);S=(int)sqrt(n);
	for (int i=1;i<=n;i++) 
	{
		blk[i]=(i-1)/S+1;
		if (blk[i]!=blk[i-1]) fst[blk[i]]=i,lst[blk[i-1]]=i-1;
	}
	lst[blk[n]]=n;
	sort(Q+1,Q+n+1);
	int l=1,r=0;
	for (int i=1;i<=n;i++)
	{
		while (r<Q[i].R) {++r;int x=c[r];Count[f[x]]-=x;tag[blk[f[x]]]-=x;++f[x];Count[f[x]]+=x;tag[blk[f[x]]]+=x;}
		while (l>Q[i].L) {--l;int x=c[l];Count[f[x]]-=x;tag[blk[f[x]]]-=x;++f[x];Count[f[x]]+=x;tag[blk[f[x]]]+=x;}
		while (r>Q[i].R) {int x=c[r];Count[f[x]]-=x;tag[blk[f[x]]]-=x;--f[x];Count[f[x]]+=x;tag[blk[f[x]]]+=x;--r;}
		while (l<Q[i].L) {int x=c[l];Count[f[x]]-=x;tag[blk[f[x]]]-=x;--f[x];Count[f[x]]+=x;tag[blk[f[x]]]+=x;++l;}
		int pos=0;
		for (int j=1;j<=blk[n];j++) if (tag[j]>0) pos=j;
		if (!pos) {ans[Q[i].id]=0;continue;}
		for (int j=fst[pos];j<=lst[pos];j++) if (Count[j]>0) ans[Q[i].id]=Count[j];
	}
	for (int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：Treaker (赞：4)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 线段树合并
裸的线段树合并。

一般看到这种维护颜色之类的东西，应该往线段树合并这方面想一想。

那么这道题我们维护什么呢。

通过观察题面，容易发现我们需要维护颜色的最多的是什么，所有最多的颜色的编号和是什么。具体如何维护可以去看看代码（应该不难吧。）

然后合并就行了。

这里来一篇指针题解~~指针大法吼啊，清新靓丽~~

完整代码如下：
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int N = 1e5+5;
inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
int n;
int fa[N] , dep[N];
ll ans[N];
struct Segment_Tree
{
	struct node
	{
		node *ls , *rs;
		int maxn;
		ll sum;
		node() {ls = rs = NULL; maxn = 0; sum = 0;}
		inline void up()
		{
			if(!ls) return (void)(maxn = rs -> maxn , sum = rs -> sum);
			if(!rs) return (void)(maxn = ls -> maxn , sum = ls -> sum);
			if(ls -> maxn > rs -> maxn) return (void)(maxn = ls -> maxn , sum = ls -> sum);
			if(rs -> maxn > ls -> maxn) return (void)(maxn = rs -> maxn , sum = rs -> sum);
			if(ls -> maxn == rs -> maxn) return (void)(maxn = ls -> maxn , sum = ls -> sum + rs -> sum);
		}
	}*root[N];
	#define mid ((l + r) >> 1)
	void chenge(node *&p,int x,int l,int r)
	{
		if(!p) p = new node();
		if(l == r) return (void)(p -> maxn = 1 , p -> sum = x);
		if(x <= mid) chenge(p -> ls,x,l,mid);
		else chenge(p -> rs,x,mid+1,r);
		p -> up();
	}
	struct Edge
	{
		int to; Edge *nxt;
		Edge(int to,Edge *nxt) : to(to) , nxt(nxt) {}
	}*head[N];
	inline void add(int u,int v) {head[u] = new Edge(v,head[u]);}
	#define to (i -> to)
	node *merge(node *p,node *o,int l,int r)
	{
		if(!p || !o) return p ? p : o;
		if(l == r) 
		{
			p -> maxn = p -> maxn + o -> maxn;
			return p;
		}
		p -> ls = merge(p -> ls,o -> ls,l,mid);
		p -> rs = merge(p -> rs,o -> rs,mid+1,r);
		return p -> up() , p;
	}
	void dfs(int x)
	{
		for(Edge *i = head[x];i;i = i -> nxt)
		{
			if(dep[to]) continue;
			dep[to] = dep[x] + 1;
			dfs(to);
			root[x] = merge(root[x],root[to],1,n);
		}
		ans[x] = root[x] ? root[x] -> sum : 0;
	}
	inline void LOL()
	{
		n = read();
		for(int i = 1;i <= n;i ++) chenge(root[i],read(),1,n);
		for(int i = 1 , u , v;i < n;i ++)
		{
			u = read(); v = read();
			add(u,v); add(v,u);
		} dep[1] = 1;
		dfs(1);
		for(int i = 1;i <= n;i ++) printf("%lld ",ans[i]);
	}
}DNF;
int main()
{
	DNF.LOL();
	return 0;
}
```

---

## 作者：qiyue7 (赞：4)

朴素的启发式合并就是大型STL练习系列。。。


[STL实现dsu的经典实现](https://www.luogu.org/blog/qiyue7ACM/solution-cf1009f)

对于这题的话我们需要注意到一个关键点就是：区间众数只在modify的时候会发生修改。 那么我们就可以用个map很简单的就进行维护了


由于是很久之前写的题，当时只写了java代码，用hashmap实现，C++用unordered_map替换即可

java AC代码：
```java
import java.io.*;
import java.util.*;
public class Main
{
    public static InputReader in = new InputReader(System.in);
    public static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    public static void main(String[] args)
    {
        int n;
        n=in.nextInt();
        dsu_on_tree d=new dsu_on_tree(n+1);
        for(int i=1;i<=n;++i)
            d.ans2[i]=in.nextInt();
        for(int i=1;i<n;++i)
            d.insert(in.nextInt(),in.nextInt());
        d.topo(1);
        d.solve(n);
        for(int i=1;i<=n;++i)
            out.print(d.ans2[i]+" ");
        out.flush();
        out.close();
    }
 
}
class graph_list
{
    LinkedList<Integer> edge[];
    void add(int u,int v)
    {
        edge[u].add(v);
    }
    graph_list(int n)
    {
        edge=new LinkedList[n];
        for(int i=0;i<n;++i)
            edge[i]=new LinkedList<Integer>();
    }
}
class graph //前向星
{
    int Begin[], to[], Next[], e;
    void add(int u, int v)
    {
        to[++e] = v;
        Next[e] = Begin[u];
        Begin[u] = e;
    }
    graph(int a)
    {
        e=0;
        to=new int[a];
        Next=new int[a];
        Begin=new int[a];
        Arrays.fill(Begin,-1);
    }
}
class dsu_on_tree
{
    graph p;
    HashMap<Integer,Integer> ans[];
    int topo1[],time,fa[],K,sum[],max1[];
    long ans2[];
    dsu_on_tree(int n)
    {
        fa=new int[n+1];
        max1=new int[n+1];
        ans=new HashMap[n];
        ans2=new long[n+1];
        topo1=new int[n];
        p=new graph(2*n+10);
        for(int i=0;i<n;++i)
            ans[i]=new HashMap<Integer,Integer>();
    }
    void insert(int u,int v)
    {
        p.add(u,v);
        p.add(v,u);
    }
    void solve(int N)
    {
        for(int i=1;i<=N;++i)
        {
            ans[i].put((int)ans2[i],1);
            max1[i]=1;
        }
        for(int i=time-1;i>0;--i)
            ans[fa[topo1[i]]]=merge(ans[topo1[i]],ans[fa[topo1[i]]],topo1[i]);
 
    }
    HashMap<Integer,Integer> merge(HashMap<Integer,Integer> a,HashMap<Integer,Integer> b,int p)
    {
        if(a.size()>b.size())
        {
            ans2[fa[p]]=ans2[p];
            max1[fa[p]]=max1[p];
            p=fa[p];
            for(Map.Entry<Integer,Integer> i:b.entrySet())
            {
                if (a.containsKey(i.getKey())) {
                    int p2 = a.get(i.getKey());
                    if(max1[p]==p2+i.getValue())
                        ans2[p]+=(long)i.getKey();
                    else if(max1[p]<p2+i.getValue())
                    {
                        ans2[p]=(long)i.getKey();
                        max1[p]=p2+i.getValue();
                    }
                    a.replace(i.getKey(), p2 + i.getValue());
                }
                else
                    {
                    a.put(i.getKey(), i.getValue());
                        if (max1[p]==i.getValue())
                            ans2[p]+=(long)i.getKey();
                        else if(max1[p]<i.getValue())
                        {
                            ans2[p]=(long)i.getKey();
                            max1[p]=i.getValue();
                        }
                }
            }
            b.clear();
            return a;
        }
        p=fa[p];
        for(Map.Entry<Integer,Integer> i:a.entrySet()) {
            if (b.containsKey(i.getKey()))
            {
                int p2 = b.get(i.getKey());
                if(max1[p]==p2+i.getValue())
                    ans2[p]+=(long)i.getKey();
                else if(max1[p]<p2+i.getValue())
                {
                    ans2[p]=(long)i.getKey();
                    max1[p]=p2+i.getValue();
                }
                b.replace(i.getKey(), p2 + i.getValue());
            }
            else
                {
                b.put(i.getKey(), i.getValue());
                if (max1[p]==i.getValue())
                    ans2[p]+=(long)i.getKey();
                else if(max1[p]<i.getValue())
                {
                    ans2[p]=(long)i.getKey();
                    max1[p]=i.getValue();
                }
            }
        }
        a.clear();
        return b;
    }
    void topo(int root)
    {
        Arrays.fill(fa,-1);
        Arrays.fill(topo1,0);
        int que[]=new int[100010];
        int tail=0,head=0;
        int cur=0;
        que[tail++]=root;
        time=0;
        while (tail!=head)
        {
            cur=que[head++];
            topo1[time++]=cur;
            for(int i=p.Begin[cur];i!=-1;i=p.Next[i])
                if(p.to[i]!=fa[cur])
                {
                    que[tail++]=(p.to[i]);
                    fa[p.to[i]]=cur;
                }
        }
    }
}
class InputReader{
    private final static int BUF_SZ = 65536;
    BufferedReader in;
    StringTokenizer tokenizer;
    public InputReader(InputStream in) {
        super();
        this.in = new BufferedReader(new InputStreamReader(in),BUF_SZ);
        tokenizer = new StringTokenizer("");
    }
    public String next() {
        while (!tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(in.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }
    public boolean hasNext() {  //处理EOF
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                String line = in.readLine();
                if(line == null) return false;
                tokenizer = new StringTokenizer(line);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return true;
    }
    public int nextInt() {
        return Integer.parseInt(next());
    }
    public long nextLong()
    {
        return Long.parseLong(next());
    }
}
```


---

## 作者：iodwad (赞：4)

值域线段树 + 线段树合并。


对于每一个树上的结点，开一个以颜色为编号的值域线段树，线段树上的每个结点要维护这两个东西：出现最多次颜色的个数，最多次颜色的和。

然后每次父结点把所有子结点的线段树合并起来就行了。

注意要开 `long long`。

这里的代码可能会对指针党有帮助qwq

```cpp
#include <iostream>
#include <cstdio>
#include <vector>

typedef long long LL;
#define int LL

const int MAXN = 1e5;

int n;
int c[MAXN | 1], ans[MAXN | 1];
std::vector < int > e[MAXN | 1];

struct Segtree {
	int maxv, sumv;
	Segtree *ch[2];
	Segtree() : maxv(0), sumv(0) {
		ch[0] = ch[1] = NULL;
	}
} *root[MAXN | 1];

inline int read() {
	register int x = 0;
	register char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x;
}

inline void pushup(Segtree *o) {
	if(o -> ch[0] == NULL) {
		if(o -> ch[1] == NULL) return;
		else {
			o -> maxv = o -> ch[1] -> maxv;
			o -> sumv = o -> ch[1] -> sumv;
		}
		return;
	} else {
		if(o -> ch[1] == NULL) {
			o -> maxv = o -> ch[0] -> maxv;
			o -> sumv = o -> ch[0] -> sumv;
			return;
		}
	}
	if(o -> ch[0] -> maxv > o -> ch[1] -> maxv) {
		o -> maxv = o -> ch[0] -> maxv;
		o -> sumv = o -> ch[0] -> sumv;
	} else if(o -> ch[0] -> maxv < o -> ch[1] -> maxv) {
		o -> maxv = o -> ch[1] -> maxv;
		o -> sumv = o -> ch[1] -> sumv;
	} else {
		o -> maxv = o -> ch[0] -> maxv;
		o -> sumv = o -> ch[0] -> sumv + o -> ch[1] -> sumv;
	}
}

void insert(Segtree *&o, int cor, int l = 1, int r = n) {
	if(o == NULL) o = new Segtree;
	if(l == r) {
		++(o -> maxv);
		o -> sumv = cor;
		return;
	}
	int mid = (l + r) >> 1;
	if(cor <= mid) insert(o -> ch[0], cor, l, mid);
	else insert(o -> ch[1], cor, mid + 1, r);	
	pushup(o);
}

Segtree *merge(Segtree *x, Segtree *y, int l = 1, int r = n) {
	if(x == NULL) return y;
	if(y == NULL) return x;
	Segtree *res = new Segtree;
	if(l == r) {
		res -> maxv = x -> maxv + y -> maxv;
		res -> sumv = l;
	} else {
		int mid = (l + r) >> 1;
		res -> ch[0] = merge(x -> ch[0], y -> ch[0], l, mid);
		res -> ch[1] = merge(x -> ch[1], y -> ch[1], mid + 1, r);
		pushup(res);
	}
	delete x;
	delete y;
	return res;
}

void dfs(int x, int fa) {
	insert(root[x], c[x]);
	for(std::vector < int >::iterator it = e[x].begin(); it != e[x].end(); ++it) {
		int to = *it;
		if(to == fa) continue;
		dfs(to, x);
		root[x] = merge(root[x], root[to]);
	}
	ans[x] = root[x] -> sumv;
}

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) c[i] = read();
	for(int i = 1; i < n; ++i) {
		int a = read(), b = read();
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; ++i) printf("%lld ", ans[i]);
	return 0;
}
```



---

## 作者：GUO大侠 (赞：4)

### DSU
#### 类似并查集的按秩合并
#### 步骤
1.先处理轻儿子的树,再把他们全部清空   
2.处理重儿子树   
3.把轻儿子和重儿子合并起来.   
#### 复杂度
$O(nlogn)$   
因为一个点被处理(暴力清空)只可能因为某个祖先是轻儿子,而这(轻儿子)在链上不会超过$logn$个.    
#### 针对本题
搞几个桶存某颜色出现的次数,某次数内所有的color之和.   
今天yyb说:"暴力清空."
只要是没有清空,所有信息肯定是在一起的,清空以后再upd就是扫重儿子或者合并了,不要怕清空时丢了什么东西,以后upd扫重儿子或者合并时会再弄回来的.
#### pps:清空时必判断不要清空重儿子

----
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define ll long long
const int N = 1e5+10;
using namespace std;
int n,co[N],h[N],cnt,son[N],siz[N],ctl[N],num[N],top;ll A[N],sum[N];
struct ed{int t,nxt;}e[N<<1];
void add(int fr,int t){e[++cnt]=(ed){t,h[fr]};h[fr]=cnt;}
void Dfs1(int u,int fa){
	siz[u]=1;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].t;if(v==fa)continue;
		Dfs1(v,u);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
			son[u]=v;
	}
}
void upd(int u,int fa,int va){
	sum[num[co[u]]]-=co[u];
	num[co[u]]+=va;
	sum[num[co[u]]]+=co[u];
	if(sum[top+1])++top;
	if(!sum[top])--top;
	for(int i=h[u];i;i=e[i].nxt){
		if(e[i].t!=fa&&!ctl[e[i].t])upd(e[i].t,u,va);//!ctl[e[i].t];
	}
}
void Dfs2(int u,int fa,int keep){
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].t;if(v==fa||v==son[u])continue;
		Dfs2(v,u,0);
	}
	if(son[u])
		Dfs2(son[u],u,1),ctl[son[u]]=1;
	upd(u,fa,1);
	ctl[son[u]]=0;
	A[u]=sum[top];
	if(!keep)
		upd(u,fa,-1);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&co[i]);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	Dfs1(1,0);Dfs2(1,0,1);
	for(int i=1;i<=n;i++)printf("%lld ",A[i]);
	return 0;
}
-------------------------------------------------
```

---

## 作者：Drind (赞：2)

### 题目解析

本题要求每个子树中众数和，那么我们考虑使用 dfn 序把整棵树拍到一个序列上，这样就变成了区间众数和问题，结合一下本题不强制在线和  $n\le 10^5$ 的数据范围很容易想到用莫队算法来解决。

一开始我想的是回滚莫队，后来机房大佬指点了一下发现只需要最朴素的莫队就能做。

我们设 $cnt_i$ 为第 $i$ 个数的出现次数，$num_i$ 为出现次数为 $i$ 次的数之和，$ans$ 为目前出现次数最多的数的**出现次数**。

每次在端点上加的时候判断新的这个数是不是原来出现次数最多的数，如果是就将 $ans$ 加上 $1$。

每次在端点上减的时候判断这个数是不是原来**唯一**出现次数最多的数，如果是就将 $ans$ 减去 $1$。

移动完区间答案就是 $num_{ans}$

代码如下

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=5e5+10;

struct node{
	int to,nxt;
}edge[N*2]; int head[N],res2;
void add(int u,int v){
	edge[++res2].to=v;
	edge[res2].nxt=head[u];
	head[u]=res2;
}
void adde(int u,int v){
	add(u,v); add(v,u);
}

int tmp[N],a[N],siz[N];
int id[N],rev[N],res;
int pos[N];

void dfs(int u,int f){
	id[u]=++res; rev[res]=u;
	a[id[u]]=tmp[u]; siz[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==f) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}

struct query{
	int l,r,id,ans;
}q[N];

int cnt[N],num[N];
int ans=0;

inline void fake_main(){
	int n; cin>>n;
	int len=sqrt(n);
	for(int i=1;i<=n;i++) pos[i]=(i-1)/len+1;
	for(int i=1;i<=n;i++) cin>>tmp[i];
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		adde(u,v);
	}
	dfs(1,0);//处理dfn序
	int l=1,r=0;
	for(int i=1;i<=n;i++){
		q[i].id=i;
		q[i].l=id[i]; q[i].r=id[i]+siz[i]-1;//处理每个子树询问
	}
	sort(q+1,q+n+1,[](query x,query y){
		if(pos[x.l]==pos[y.l]) return x.r<y.r;
		return x.l<y.l;
	});
	
	for(int i=1;i<=n;i++){
		for(;l>q[i].l;){//注意莫队要先加后减不然会导致cnt数组变成负数，带入num数组导致RE
			l--;
			num[cnt[a[l]]]-=a[l];
			if(ans==cnt[a[l]]) ans++;//如果这个数就是出现次数最多的那个
			cnt[a[l]]++;
			num[cnt[a[l]]]+=a[l];
		}
		for(;r<q[i].r;){
			r++;
			num[cnt[a[r]]]-=a[r];
			if(ans==cnt[a[r]]) ans++;
			cnt[a[r]]++;
			num[cnt[a[r]]]+=a[r];
		}
		for(;l<q[i].l;){
			num[cnt[a[l]]]-=a[l]; 
			if(ans==cnt[a[l]]&&num[cnt[a[l]]]==0) ans--;//如果这个数就是出现次数最多的那个，记得特判是不是唯一的那个
			cnt[a[l]]--;
			num[cnt[a[l]]]+=a[l];
			l++;
		}
		for(;r>q[i].r;){
			num[cnt[a[r]]]-=a[r]; 
			if(ans==cnt[a[r]]&&num[cnt[a[r]]]==0) ans--;
			cnt[a[r]]--;
			num[cnt[a[r]]]+=a[r];
			r--;
		}
		q[i].ans=num[ans];//更新答案
	}
	sort(q+1,q+n+1,[](query x,query y){
		return x.id<y.id;
	});
	
	for(int i=1;i<=n;i++){
		cout<<q[i].ans<<" ";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}
```

---

## 作者：PerfessorZhang (赞：1)

典型的dsu on tree
递归处理轻儿子，计算轻儿子答案， 
然后消去轻儿子对于答案的影响。 
然后递归处理重儿子，不消去影响，最后加入所有轻儿子贡献，计算答案。
还可以将树处理成序列，用莫队进行处理
dsu on tree时间复杂度O（nlogn）
莫队时间复杂度O（n√n）
显然前者更优
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define ll long long
ll cnt=0,top=0,n;
ll head[maxn],size[maxn],deep[maxn],f[maxn],son[maxn],sum[maxn],num[maxn],c[maxn],ans[maxn];
bool vis[maxn];
struct node
{
	int to,next;
}e[maxn*2];
inline ll read()
{
	ll w=1,s=0; char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')w=-1; ch=getchar();}
	while(ch>='0' && ch<='9'){s=s*10+ch-'0'; ch=getchar();}
	return w*s;
}
void add(int x,int y)
{
	cnt++;
	e[cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}
void dfs1(int u,int fa)
{
	size[u]=1; deep[u]=deep[fa]+1; f[u]=fa;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]]) son[u]=v;
	}
}
void update(int u,int fa,int tp)
{
	sum[num[c[u]]]-=c[u];
	num[c[u]]+=tp;
	sum[num[c[u]]]+=c[u];
	if(sum[top+1]) top++;
	if(!sum[top]) top--;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa || vis[v]) continue;
		update(v,u,tp);
	}
}
void dfs(int u,int fa,int tp)
{
	
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa || v==son[u]) continue;
		dfs(v,u,0);
	}
	if(son[u]) 
	{
		dfs(son[u],u,1); vis[son[u]]=true;
	}
	update(u,fa,1); vis[son[u]]=false;
	ans[u]=sum[top];
	if(!tp) update(u,fa,-1);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) c[i]=read();
	for(int i=1;i<n;i++)
	{
		int a=read(),b=read();
		add(a,b); add(b,a);
	}
	dfs1(1,0);
	dfs(1,0,1);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：hehezhou (赞：1)

## 一道树上启发式合并
### 有更新
我也不知道上次为什么能过。。。数据范围开错还忘了long long。。。

首先跑一边dfs，找出父节点和重儿子（不知道的先看树剖）

因为数据范围，只能开一个记录颜色数量的数组。最优的办法是保留重儿子的情况。

然而还有一个问题：数组归零和统计答案每次是$O(n)$的，一共$O(n^2)$。于是我用了一个时间戳的优化（见代码，有说明）


代码丑勿喷：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
struct Array{                                     //优化
    int tme,a[100010],t[100010],maxsize;
    ll sum; //t为上次更改时间，a为数量，time为目前时间，maxn为最大的数量，sum为最大的之和
    void clear(){tme++,maxsize=sum=0;}              //只要把时间戳++，两个统计最大的归零即可(O(1))。
    void inc(int k){
        if(t[k]!=tme)a[k]=0,t[k]=tme;           //如果上次更改之后有归零，则归零
        a[k]++;
        if(a[k]>maxsize)sum=0,maxsize=a[k];
        if(a[k]==maxsize)sum+=k;
    }
    ll ans(){return sum;}
}a;
int head[100010],nxt[200010],cnt,v[200010];
int c[100010],wson[100010],fa[100010],s[100010];
ll ans[100010];
void add(int U,int V){            //加边
    nxt[++cnt]=head[U];
    head[U]=cnt;
    v[cnt]=V;
}
void dfs1(int now){               //找重儿子
    s[now]=1;
    wson[now]=0;
    for(register int i=head[now];i;i=nxt[i])
        if(v[i]!=fa[now]){
            fa[v[i]]=now;
            dfs1(v[i]);
            s[now]+=s[v[i]];
            if(s[v[i]]>s[wson[now]])wson[now]=v[i];
        }
}
void dfs2(int now,Array& a){  //统计以now为根子树中的颜色数量。
    a.inc(c[now]);
    for(register int i=head[now];i;i=nxt[i])
        if(v[i]^fa[now])dfs2(v[i],a);
}
void dfs3(int now,Array& a){  //核心代码
    if(wson[now]==0){    //叶子节点
        ans[now]=c[now];
        a.inc(c[now]);
        return;
    }
    for(register int i=head[now];i;i=nxt[i]){
        if(v[i]!=fa[now]&&v[i]!=wson[now]){
            dfs3(v[i],a);
            a.clear();
        }
    }
    dfs3(wson[now],a);  //重儿子影响保留
    for(register int i=head[now];i;i=nxt[i]){  //加上其它子树
        if(v[i]!=fa[now]&&v[i]!=wson[now]){
            dfs2(v[i],a);
        }
    }
    a.inc(c[now]);  //别忘了加上自己
    ans[now]=a.ans();//统计答案
}
int main(int argc,char**argv){ //主程序没啥可讲
    scanf("%d",&n);
    for(register int i=1;i<=n;i++)scanf("%d",c+i);
    for(register int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs1(1);
    dfs3(1,a);
    for(register int i=1;i<=n;i++)printf("%lld ",ans[i]);
    return 0;
}
```

---

