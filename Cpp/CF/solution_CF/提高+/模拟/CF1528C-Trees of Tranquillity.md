# Trees of Tranquillity

## 题目描述

Soroush and Keshi each have a labeled and rooted tree on $ n $ vertices. Both of their trees are rooted from vertex $ 1 $ .

Soroush and Keshi used to be at war. After endless decades of fighting, they finally became allies to prepare a Codeforces round. To celebrate this fortunate event, they decided to make a memorial graph on $ n $ vertices.

They add an edge between vertices $ u $ and $ v $ in the memorial graph if both of the following conditions hold:

- One of $ u $ or $ v $ is the ancestor of the other in Soroush's tree.
- Neither of $ u $ or $ v $ is the ancestor of the other in Keshi's tree.

Here vertex $ u $ is considered ancestor of vertex $ v $ , if $ u $ lies on the path from $ 1 $ (the root) to the $ v $ .

Popping out of nowhere, Mashtali tried to find the maximum clique in the memorial graph for no reason. He failed because the graph was too big.

Help Mashtali by finding the size of the maximum clique in the memorial graph.

As a reminder, clique is a subset of vertices of the graph, each two of which are connected by an edge.

## 说明/提示

In the first and third test cases, you can pick any vertex.

In the second test case, one of the maximum cliques is $ \{2, 3, 4, 5\} $ .

In the fourth test case, one of the maximum cliques is $ \{3, 4, 6\} $ .

## 样例 #1

### 输入

```
4
4
1 2 3
1 2 3
5
1 2 3 4
1 1 1 1
6
1 1 1 1 2
1 2 1 2 2
7
1 1 3 4 4 5
1 2 1 4 2 5```

### 输出

```
1
4
1
3```

# 题解

## 作者：KaisuoShutong (赞：13)

## 翻译

给定两棵树，要求选出一个极大的集合 $P$，使得 $P$ 中任意两点都满足：

1. 在第一棵树上，两个点中一个为另一个的祖先；
2. 在第二棵树上，两个点互不为祖先关系。

$n\leq 3\times 10^5$。

## 题解

考虑更优秀的限制，也就是第一棵树的，容易发现我们会选一条祖先-子孙链上的某些点。  

发现一个性质，对于任意 $i$ 都满足 $fa_i\leq i$。这提示我们若将第二棵树映射到 dfs 序上去，那么对于任意 $i<j$，$i$ 所管辖的区间和 $j$ 所管辖的区间 要么是 $i$ 包含 $j$，要么不相交。

那么我们可以直接在第一棵树上贪心。如果祖先和当前点冲突了，就把它删了选当前点。

需要用一个数据结构维护相交关系。可以使用 `STL::set` 或线段树/平衡树。

点个赞吧。

参考代码：

```cpp
//伟大的导师，伟大的领袖，伟大的统帅，伟大的舵手
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char __buf[1<<20],*__p1,*__p2;
#define getchar() (__p1==__p2?(__p2=__buf+fread(__p1=__buf,1,1<<20,stdin),__p1==__p2?EOF:*__p1++):*__p1++)
int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
const int maxn = 3e5+10;
int s[maxn<<2],tg[maxn<<2],ans,res;
void Tag(int k,int vl) {s[k]=tg[k]=vl;}
void psd(int k) {if(~tg[k]) Tag(k<<1,tg[k]),Tag(k<<1|1,tg[k]),tg[k]=-1;}
void ins(int k,int l,int r,int L,int R,int vl) {
	if(l>R||L>r) return;
	if(L<=l&&r<=R) return Tag(k,vl);psd(k);int mid=l+r>>1;
	ins(k<<1,l,mid,L,R,vl),ins(k<<1|1,mid+1,r,L,R,vl),s[k]=max(s[k<<1],s[k<<1|1]);
}
int ask(int k,int l,int r,int L,int R) {
	if(l>R||L>r) return 0;
	if(L<=l&&r<=R) return s[k];psd(k);int mid=l+r>>1;
	return max(ask(k<<1,l,mid,L,R),ask(k<<1|1,mid+1,r,L,R));
}
int dfn[maxn],low[maxn],dfx,n;
vector<int>G[maxn],C[maxn];
void dfs(int x) {
	dfn[x]=++dfx;
	for(auto y:C[x]) dfs(y);
	low[x]=dfx;
}
void _dfs(int x) {
	int t=ask(1,1,n,dfn[x],low[x]);
	if(t) ins(1,1,n,dfn[t],low[t],0);else ++ans;
	ins(1,1,n,dfn[x],low[x],x);
	res=max(res,ans);for(auto y:G[x]) _dfs(y);
	if(t) ins(1,1,n,dfn[t],low[t],t);else ins(1,1,n,dfn[x],low[x],0),--ans;
}
signed main() {
	int T=read();
	while(T--) {
		n=read(),dfx=0,res=0;
		for(int i=1;i<=n;i++) G[i].clear(),C[i].clear();
		for(int i=1;i<=n<<2;i++) tg[i]=-1,s[i]=0;
		for(int i=2;i<=n;i++) G[read()].push_back(i);
		for(int i=2;i<=n;i++) C[read()].push_back(i);
		dfs(1),_dfs(1),cout<<res<<'\n';
	}
	return 0;
}
```

---

## 作者：iMya_nlgau (赞：11)

### 题目大意

给你两棵 $n$ 个节点的树，要你找一个最大的点集 $S$，使得对于任意 $u,v\in S$，都满足 $u,v$ 在第一棵树上一个是另一个的祖先，在第二棵树上互相都没有祖先关系，输出 $S$ 的大小即可。

### 思路

我们可以 dfs 第一棵树，搜到节点 $x$ 的时候维护 $x$ 到根节点的路径上的点（它们在第一棵树上一定满足两两有祖先关系）。现在要做的就是在第二棵树上维护在这些点最多选多少点两两没有祖先关系。

我们可以维护当前这些点在第二棵树上构成的虚树（只是这么说，并不是真的要建虚树）。容易发现，虚树的叶子节点就是能选出的满足条件的最大点集。

于是可以树剖维护第二棵树，每加入一个点 $x$，如果 $x$ 没被标记，就把 $x$ 的子树以及 $x$ 到根节点路径都打上标记（比如异或上 $x$），如果标记过了，若标记的点是 $x$ 的祖先，删掉它并加入 $x$，如果 $x$ 是标记的点的祖先，那就不加入 $x$。

dfs 第一棵树时，还要在搜完一个点的时候回溯，所以记录下所有操作，回溯时在树剖上把操作撤销。

这个做法是我赛后想到的（wtcl 赛时没做出来）。时间复杂度为 $O(n\log^2 n)$，应该能过。

后来看了官方题解的做法，它用 set 维护当前答案集合里点的欧拉序，做的更简单些。

欧拉序（对每个点记录一个进入的时间戳 $st$，和离开的时间戳 $ed$）有点像一个括号序列，即每个区间 $[st_i,ed_i]$ 都要么是包含关系，要么不相交。我们要做的就是维护当前最多多少个区间两两不相交，这个可以用 set 维护。采用一个贪心的思路，加入一个区间时，如果它被其他区间包含，那么把包含它的区间换成它一定不劣，如果新加入的区间包含了其他区间，那么加入它一定不优，不加入它，如果新加入的区间不与其他区间相交，直接加入即可。

依然是在 dfs 第一棵树的时候维护上述东西，搜完一个点时回溯。这个做法的时间复杂度为 $O(n\log n)$。

[代码实现（set）](https://www.luogu.com.cn/paste/wb3pveco)

---

## 作者：wmy_goes_to_thu (赞：6)

首先，一个团的所有点一定在第一棵树（简称树 $A$，第二棵简称树 $B$）上的一条链上。注意到数据范围中 $1<=a_i<i$ 和 $1<=b_i<i$ 的限制，$i$ 在 $A$ 上的一个祖先在 $B$ 上一定不是 $i$ 的子孙。

首先，定义祖先链为一个集合，在这个集合里任意两个点都是祖先或子孙的关系。所以，我们考虑树 $A$ 上的每一条链，容易发现它可以被拆成在 $B$ 上的若干个祖先链，而祖先链的个数就是这条链的答案。

如果记录 $v_i$ 代表最接近 $i$ 的在 $A$ 和 $B$ 上都是 $i$ 的祖先的节点，那么一个祖先链中只有最后一个元素不是这条链上一个点的 $v$ 值，所以又等价于求有多少个元素 $u$，使得对于链上任何一个点，它的 $v$ 值都不是 $u$。

维护 $v$ 值不难，直接 dfs 一下树 $A$，经过一个点就把它在 $B$ 上的子树 dfs 序（一段区间）标在树状数组里，就不难做了（可以自己想一想）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f1[300005],f2[300005],t1=0,t2=0,b1[300005],e1[300005],b2[300005],e2[300005];
int n,f[300005],v[300005],ans=0;
long long c[300005];
vector<int>g1[300005],g2[300005];
void dfs1(int x)
{
	b1[x]=e1[x]=++t1;
	for(int i=0;i<g1[x].size();i++)
	{
		int cu=g1[x][i];
		dfs1(cu);
		e1[x]=max(e1[x],e1[cu]);
	}
}
void dfs2(int x)
{
	b2[x]=e2[x]=++t2;
	for(int i=0;i<g2[x].size();i++)
	{
		int cu=g2[x][i];
		dfs2(cu);
		e2[x]=max(e2[x],e2[cu]);
	}
}
void add(int x,int s)
{
	while(x<=n)
	{
		c[x]+=s;
		x+=x&-x;
	}
}
int query(int x)
{
	int ans=0;
	while(x)
	{
		ans+=c[x];
		x-=x&-x;
	}
	return ans;
}
void dfs3(int x,int dd)
{
	int S1=query(b2[x]);
	if(S1)
	{
		add(b2[S1],-S1);
		add(e2[S1]+1,S1);
	}else dd++;
	ans=max(ans,dd);
	add(b2[x],x);
	add(e2[x]+1,-x);
	for(int i=0;i<g1[x].size();i++)
	{
		int cu=g1[x][i];
		dfs3(cu,dd);
	}
	add(b2[x],-x);
	add(e2[x]+1,x);
	if(S1)
	{
		add(b2[S1],S1);
		add(e2[S1]+1,-S1);
	}
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)g1[i].clear(),g2[i].clear(),c[i]=0;
		for(int i=2;i<=n;i++)
		{
			int u;
			scanf("%d",&u);
			f1[i]=u;
			g1[u].push_back(i);
		}
		for(int i=2;i<=n;i++)
		{
			int u;
			scanf("%d",&u);
			f2[i]=u;
			g2[u].push_back(i);
		}
		t1=0,t2=0;
		dfs1(1),dfs2(1);
		for(int i=1;i<=n;i++)f[i]=1;
		ans=0,dfs3(1,0);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：walk_alone (赞：4)

在实现难度上，个人更倾向于本题使用欧拉序列+ set 去实现。本题解主要是对官方代码进行一个分析。

考虑欧拉序列的性质。详细性质可以参见本文：[树的其他知识——欧拉序列](https://www.luogu.com.cn/blog/walk-alone/shu-de-qi-ta-zhi-shi-ou-la-xu-lie)。其中一个很重要的性质，就是**任意两个节点对应的区间 $[st_1,ed_1],[st_2,ed_2]$，这俩区间要么完全包含要么完全不相交**。并且，如果是包含关系的话，一定有祖先关系。因而我们利用好这个性质。

考虑最后最大团的组成。它需要这里面每个节点都和其他的都有边相连，由于有第一个条件——Soroush 树上有祖先关系的存在，这些点必然是 Soroush 上的一条链。 为了构造最大团，最好使得初始待选择的点尽可能的多，因而是 Soroush 树上的一条链。

接下来考虑这条链上满足第二条件的点集。由于欧拉序列的性质，我们将问题等价于从这些点中选取一些，使得它们都不相交（等价于不存在包含关系）。那么一个贪心的基本原则：能选小区间就不选大区间，因而有官方题解的两条原则：

1. 如果之前的链上无区间覆盖当前节点区间，直接贪心加入；

1. 如果有，保留小区间，删去大区间。

接下来就是实现问题。

首先是求 Keshi 树的欧拉序列。然后去遍历 Soroush 树，在 set 中仅维护当前节点到根节点这些区间中合法的部分，然后统计答案。我们就不一定要求一定要到根节点去了。

鉴于 CF 的官方题解实现的较为简洁，因而在这里我对 CF 的题解代码进行一个详细的评述。

下面是一个大体的流程：

这里是判断一个点所对应的欧拉序列区间是否在 set 中有重叠部分，以及重叠情况，来判断是否要加点。

```cpp
int judge(int place)
{
    auto iter = exist.lower_bound(make_pair(st[place], place));
    //首先是找到该点附近的几个区间。注意这里我们在set中维护的是它的起始点和当前节点编号。可以存储当前节点对应的欧拉区间（即开始和结束），但是这里不便于后面的处理。
    //这里使用起始点和当前节点编号的另一个好处在于，在set中排序时是优先按照起始点在排序，因而可以快速找到这样的区间。
    //iter现在指向的是第一个大于当前点对应区间的区间。由于欧拉序列的性质，两个点对应的欧拉序列起始点和终止点必不相同。
    //因而现在的情况是 iter对应的点的起始点start>st[place]
    if(iter!=exist.end() && ed[iter->second]<=ed[place])
    //如果当前点的终止点还在place终止点前，那么证明这是个被place包络的一个小区间，place就不必加入set了。
        return -2;
    //特供于set为空。
    if(iter==exist.begin())
        return -1;
    iter--;
    //返回-1的含义：当前set中无包络区间。
    //返回-2的含义：set中已有较小区间，当前点不必加入
    if(ed[iter->second]<ed[place])
    //现在的起始点一定在st[place]前，那么如果当前终点也在place前，证明无包络。
        return -1;
    exist.erase(iter);
    //iter指向的区间为大区间，但是这个老区间辈分高，因而在place子树处理完后要补回来，因而需要记录。但是在place子树下，这个大区间是没有必要的，因而要删掉。
    return iter->second;
}
```

考虑 judge 函数的定义，我们有如下的主要递归函数：

```cpp
void solve(int place)
{
    int res = judge(place);
    if(res!=-2)
    //只要不是-2的不必加入，在处理place子树的时候都需要加入。
        exist.insert(make_pair(st[place], place));
    ans = max(ans, (int)exist.size());
    for (int i = headers[0][place]; i; i = que[0][i].next)
        solve(que[0][i].to);
    if(res!=-2)//回溯工作
    {
        exist.erase(make_pair(st[place], place));
        //首当其冲，子树遍历完它也不在正在求的链上了，删掉
        if (res != -1)//有老的、包络大区间，因而需要恢复
            exist.insert(make_pair(st[res], res));
    }
}
```

其余代码实现就非常简单了。

---

## 作者：FjswYuzu (赞：3)

考场上没做出来亏大了。谨以此题解膜拜 @Reanap 和记录我的傻逼。

显然，我们选作为答案的点在第一棵树上的根到某一个叶子的链上。不妨先考虑第一棵树是一条链的做法。我们在考虑加入一个点的时候，有以下三种情况：

1. 在第二棵树上加入这个点，使得选的点的公共祖先发生改变且仍然满足条件；   
2. 在第二棵树上加入这个点，使得之前选的点的公共祖先是这个点的祖先；    
3. 在第二棵树上加入这个点，使得这个点是之前选的点的公共祖先的祖先。

分情况讨论。对于第一种情况，显然答案可以增加不要白不要；对于第二三种情况贪心考虑，显然答案无变化，那么让公共祖先的深度越深越好，即第二种情况不管，第三种情况将原来的公共祖先删去，将当前的公共祖先置为新加入的点。

注意到我们整个的讨论只跟选的点的公共祖先有关，我们没必要管哪些点实际在。

注意到链与链之间互不冲突可以合并，于是就可以做到 $O(n \log n)$ 了。完全不懂为什么有人会用树剖。

因为懒得写代码所以讲一下实现细节。我们在遍历第一棵树的时候将在第二棵树上的当前的公共祖先记下来。每次修改的时候比较深度即可。

我怎么这么傻逼啊？？

---

## 作者：XL4453 (赞：2)

### 解题思路：

树上贪心。

为了方便记述，在这篇题解里：第一个树，也就是要求每一个点都是祖先关系的那一棵，被认为是左边的树，第二棵树，也就是没有任何祖先关系的那一棵，被认为是右边的树。~~（其实是写完了发现和定义不一样然后不想改了）~~

对于左边树上的节点，上面的所有点都是在一条链上的，而在右边的树上，所有的点一定是分散的。

尽管在左子树上判断同链比较容易，但在右边树上找分散的点并不好做，所以考虑在左边的某一条链上找点。

对于左边的某一个点，若这个点在右边的树上不仅不是任何一个节点的子树，也不是任何一个节点的祖先，那么一定可以直接加。

而如果这个点包含了至少一个节点，那么如果把这些节点换成当前节点一定不优，可以理解为在价值没有增加的前提下还导致了占用的不可使用节点更多。

反之若这个节点被某一个节点包含了，那么把这一个节点换下来一定是优的，可以理解为在代价没有减小的前提下使得占用的不可使用节点变少了。

这样就可以通过当前节点和已选的节点的关系来做。

---

但是维护似乎没有那么简单。。。

如果 $O(n)$ 地枚举已选节点，然后 $O(logn)$ 地判断是否存在包含或被包含关系，复杂度是无法接受的。

考虑用欧拉序优化，直接用一个 set 维护当前已选节点的欧拉序情况，然后在实现的时候可以直接用二分法找出相邻的区间，判断即可。

在具体实现的时候，set 中记录的其实并不是完整的区间，而应当是区间的头和节点编号。这是因为在 dfs 回溯时需要取消当前节点的影响，如果这个节点将某一个节点顶出去了，那么还需要再加回来，这里需要用到节点的编号。



---
### 代码：

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
using namespace std;
const int MAXN=300010;
set<pair<int,int> > st;
vector <int> T1[MAXN],T2[MAXN];
int T,low[MAXN],dfn[MAXN],dfs_num,x,n,ans;
int add(int now){
	set<pair<int,int> >::iterator it=st.lower_bound(make_pair(dfn[now],now));
	if(it!=st.end()&&low[it->second]<=low[now])return -2;
	if(it==st.begin())return -1;it--;
	int res=it->second;
	if(low[now]>low[res])return -1;
	st.erase(it);
	return res;
}
void dfs1(int now){
	dfn[now]=++dfs_num;
	for(int i=0;i<T2[now].size();i++)dfs1(T2[now][i]);
	low[now]=dfs_num;
}
void dfs2(int now){
	int res=add(now);
	if(res!=-2)st.insert(make_pair(dfn[now],now));
	ans=max(ans,(int)st.size());
	for(int i=0;i<T1[now].size();i++)dfs2(T1[now][i]);
	if(res!=-2){
		st.erase(make_pair(dfn[now],now));
		if(res!=-1)st.insert(make_pair(dfn[res],res));
	}
}
int main(){
	scanf("%d",&T);
	while(T--){st.clear();
		memset(low,0,sizeof(low));
		memset(dfn,0,sizeof(dfn));
		dfs_num=0;ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)T1[i].clear(),T2[i].clear();
		for(int i=2;i<=n;i++)scanf("%d",&x),T1[x].push_back(i);
		for(int i=2;i<=n;i++)scanf("%d",&x),T2[x].push_back(i);
		dfs1(1);dfs2(1);
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：peterwuyihong (赞：2)

### 首先我们整理思路
显然点集在树 $A$ 上是在一条链上，那我们考虑在 $A$ 上 $dfs$ ，深搜时统计

那我们单单考虑在一条链上添加的情况

首先令每个点有一个颜色 $c_i$ ，初始时都是 $0$

那我们有一个大致的思路，搜到 $x$ 点时，如果颜色为 $0$ ，就占领，再把 $x$ 到根与 $x$ 子树都标记一下，再搜时就可以处理冲突

考虑冲突，如果在$B$上有两个位置 $x,y$ ，令 $x$ 是 $y$ 的祖宗。那么 $y$ 标记的颜色一定比 $x$ 标记的颜色多

![](https://cdn.luogu.com.cn/upload/image_hosting/7ylylylr.png)

所以我们尽可能地保留下面的节点

于是我们这么染色，把 $x$ 到根的颜色都涂成 $-1$ ，把 $x$ 子树都染上 $x$ 的颜色。

$Case1$ ：当我们搜到颜色为 $-1$ 的点时，不管了，因为$B$树下面有更深的点

$Case2$ ：当我们搜到颜色为 $0$ 的点时，占领这个点并涂色

$Case3$ ：当我们搜到其他颜色为 $y$ 的 $x$ 点时，颜色就代表什么点在 $x$ 上面，于是把颜色代表的 $y$ 点和它染出来的颜色删去，增加 $x$ ，涂子树，涂到根

然后考虑回溯，因为回溯时要消除影响，定义一个$eat$数组，当我们进入 $Case3$ 时，记录 $eat_x=y$ ，代表 $x$ 把 $y$ 吃了，回溯时把 $y$ 增加回来，待选集合大小加 $1$ 即可（但有可能 $eat_x=0$ ，就代表 $x$ 没吃，就不用加回来）然后再把 $x$ 和它染出来的颜色删去，待选集合大小减$1$
### 处理染色问题
树上到根，子树区间操作，而且是区间推平

珂朵莉树！！！！

然而过不去，草，键盘上的拳头硬了
### 各种坑
多测且 $1\le t\le3*10^5$ ，使用 $memset$ 见祖宗

线段树染色时 $tag$ 不能默认为 $0$ ，因为染色可能会刻意染成 $0$ ，也不能是 $-1$ ，于是我把 $tag$ 刻意设成了 $-114514$ （
```cpp
#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<' '<<x<<endl
#ifndef ONLINE_JUDGE
	#define pia getchar
#else
	#define pia nc
#endif
char nc(){
  	static char buf[1<<25],*p=buf,*q=buf;
  	if(p==q&&(q=(p=buf)+fread(buf,1,1<<25,stdin),p==q))return EOF;
  	return *p++;
}
template<class T>void rd(T&x){
	short f=1;x=0;
	char ch=pia();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=pia();
	}while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=pia();
	}x*=f;
}
template<class T>void wr(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)wr(x/10);
	putchar(x%10+48);
}

#define maxn 300010
int n,x,T;
struct G{
	int head[maxn],Next[maxn<<1],ver[maxn<<1],tot;
	inline void add(int x,int y){
		ver[++tot]=y;
		Next[tot]=head[x];
		head[x]=tot;
	}	
	inline void clear(){
		tot=0;
	//	memset(head,0,sizeof (n+1)*sizeof(head));
	}
}A,B;
int dep[maxn],fa[maxn],son[maxn],siz[maxn];
int dfn[maxn],top[maxn],cnt;
inline void dfs1(int x){
	siz[x]=1;
	for(int i=B.head[x];i;i=B.Next[i]){
		int y=B.ver[i];
		if(dep[y])continue;
		dep[y]=dep[x]+1;
		fa[y]=x;
		dfs1(y);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]])son[x]=y;
	}
}
inline void dfs2(int x,int t){
	dfn[x]=++cnt;
	top[x]=t;
	if(!son[x])return;
	dfs2(son[x],t);
	for(int i=B.head[x];i;i=B.Next[i])
	if(B.ver[i]!=fa[x]&&B.ver[i]!=son[x])dfs2(B.ver[i],B.ver[i]);
}/*
struct point{
	int l,r;
	mutable int v;
	point(int ll,int rr,int vv):l(ll),r(rr),v(vv){}
	inline bool operator<(point x)const{return l<x.l;}
};
#define Iter set<point>::iterator
struct ST{
	set<point>s;
	void init(){
		s.clear();
		s.insert(point(1,n,0));
	}
	inline Iter split(int x){
		if(x>n)return s.end();
		Iter it=--s.upper_bound(point(x,0,0));
		if(it->l==x)return it;
		int l=it->l,r=it->r,v=it->v;
		s.erase(it),s.insert(point(l,x-1,v));
		return s.insert(point(x,r,v)).first;
	}
	inline void assign(int l,int r,int v){
		Iter itr=split(r+1),itl=split(l);
		s.erase(itl,itr);
		s.insert(point(l,r,v));
	}
}st;*/
struct ST{
	struct TR{
		int l,r,x,tag;
	}tree[maxn<<2];
	void build(int x,int l,int r){
		tree[x]=(TR){l,r,0,-114514};
		int mid=(tree[x].l+tree[x].r)>>1;
		if(l==r)return;
		build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	}
	void pushdown(int x){
		if(tree[x].tag!=-114514){
			tree[x<<1].tag=tree[x<<1|1].tag=tree[x<<1].x=tree[x<<1|1].x=tree[x].tag;
			tree[x].tag=-114514;
		}
	}
	void insert(int x,int l,int r,int d){
		if(tree[x].l>=l&&tree[x].r<=r){
			tree[x].x=tree[x].tag=d;
			return;
		}
		pushdown(x);
		int mid=(tree[x].l+tree[x].r)>>1;
		if(l<=mid)insert(x<<1,l,r,d);
		if(r>mid)insert(x<<1|1,l,r,d);
	}
	int ask(int x,int pos){
		if(tree[x].l==tree[x].r)return tree[x].x;
		pushdown(x);
		int mid=(tree[x].l+tree[x].r)>>1;
		if(pos<=mid)return ask(x<<1,pos);
		else return ask(x<<1|1,pos);
	}
	void CHECK(){
		build(1,1,10);
		insert(1,2,5,3);
		for(int i=1;i<=10;i++)cout<<ask(1,i)<<' ';puts("");
		insert(1,4,6,4);
		for(int i=1;i<=10;i++)cout<<ask(1,i)<<' ';puts("");
		insert(1,4,6,0);
		for(int i=1;i<=10;i++)cout<<ask(1,i)<<' ';puts("");
		
		exit(0);
	}
}st;
inline void toroot(int x,int d){
	while(x){
	//	st.assign(dfn[top[x]],dfn[x],d);
		st.insert(1,dfn[top[x]],dfn[x],d);
		x=fa[top[x]];
	}
}
inline void sontree(int x,int d){
	st.insert(1,dfn[x],dfn[x]+siz[x]-1,d);
//	st.assign(dfn[x],dfn[x]+siz[x]-1,d);
}
inline void del(int x){
	toroot(x,0),sontree(x,0);
}
inline void add(int x){
	toroot(x,-1),sontree(x,x);
}
int ans,res;
int eat[maxn];
inline void dfs(int x,int fa){
//	int tmp=(--st.s.upper_bound(point(dfn[x],0,0)))->v;
	int tmp=st.ask(1,dfn[x]);
	if(tmp==0)res++,add(x);
	else if(tmp!=-1)eat[x]=tmp,del(tmp),add(x);
//puts("__________________");
//	cout<<x<<endl;
//	cout<<tmp<<endl;
//	st.print();
//puts("__________________");
	ans=max(ans,res);
	for(int i=A.head[x];i;i=A.Next[i]){
		int y=A.ver[i];
		if(y==fa)continue;
		dfs(y,x);
	}
	del(x);
	if(eat[x])add(eat[x]);
	else res--;
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	for(rd(T);T;T--){
		rd(n);
		for(int i=1;i<=n;i++)A.head[i]=B.head[i]=son[i]=dep[i]=eat[i]=0;
		st.build(1,1,n);
		A.clear(),B.clear();
		for(int i=2;i<=n;i++)rd(x),A.add(x,i),A.add(i,x);
		for(int i=2;i<=n;i++)rd(x),B.add(x,i),B.add(i,x);
		cnt=0;
	//	memset(dep,0,sizeof (n+1)*sizeof(int));
	//	memset(son,0,sizeof (n+1)*sizeof(int));
		dep[1]=1;dfs1(1);
		dfs2(1,1);
		ans=res=0;
	//	for(int i=1;i<=n;i++)cout<<dfn[i]<<' ';puts("");
		dfs(1,-1);
		wr(ans),putchar('\n');
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}

```


---

## 作者：FutaRimeWoawaSete (赞：1)

赛时被 D 给卡了很久，赛后也没想到贪心……我是不是真的没辙了。             

首先我们考虑我们选出来的点集：            

- 在A树上所有点都互相成祖先关系；          

- 在B树上所有点都不互相成祖先关系。               

我们考虑 dfs A树时动态维护一个合法点集，并且每次加点时尽可能的加进去。            

可以证明这么贪心加点是最优的：            

- 在 dfs 到一个新点时，根据父亲得到的合法点集考虑当前点怎么加入；           

- 如果当前点在 B树中与一个及以上的点构成祖先关系，那么直接把这个点弃了。此时选上它覆盖的所有点明显比选上它没有覆盖的所有点更优，也可以理解成在B树里，我选你这个点在B树的子树里的点更优；（有点小绕）           

- 如果当前点在 B树中没覆盖点，我们就看它有没有被其它点覆盖。由于上一个状态是合法状态，所以此时至多只会有一个点在B树上覆盖它。那么这个覆盖它的点必然是它在 B树上的祖先，直接把这个祖先找出来杀掉就好了；         

- 否则，它没有任何冲突，直接加。            

这个每一步都是不劣的，所以贪心无误。           

在 dfs 回溯的时候我们直接对应着加进来的方式进行回溯就好了，用线段树实现时间复杂度 $O(n \log n)$ 。         


```cpp
#include "bits/stdc++.h"
using namespace std;//如果有一个人是我的祖先，那么我直接把你换掉就好了，否则我换你显然更不优 
const int Len = 3e5 + 5;
int n,m,ans[Len << 2][2],tag[Len << 2][2],head[Len][2],cnt[2],id[Len],siz[Len],tot;
struct node
{
	int next,to;
}edge[Len << 1][2];
void add(int from,int to,int sim)
{
	edge[++ cnt[sim]][sim].to = to;
	edge[cnt[sim]][sim].next = head[from][sim];
	head[from][sim] = cnt[sim];
}
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x){ans[x][1] = ans[ls(x)][1] + ans[rs(x)][1];}
void build(int p,int l,int r)
{
	ans[p][0] = -1;ans[p][1] = tag[p][0] = tag[p][1] = 0;
	if(l == r) return;int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
}
void push_down(int p,int l,int r)
{
	if(tag[p][0]) tag[ls(p)][0] = tag[rs(p)][0] = ans[ls(p)][0] = ans[rs(p)][0] = tag[p][0];
	tag[p][0] = 0;
}
void update1(int p,int l,int r,int nl,int nr,int CH)
{
	if(nl <= l && nr >= r) 
	{
		ans[p][0] = CH;
		tag[p][0] = CH;
		return;
	}
	push_down(p , l , r);
	int mid = (l + r) >> 1;
	if(nl <= mid) update1(ls(p) , l , mid , nl , nr , CH);
	if(nr > mid) update1(rs(p) , mid + 1 , r , nl , nr , CH);
}
int query1(int p,int l,int r,int idx)
{
	if(l == r) return max(ans[p][0] , 0);
	int mid = (l + r) >> 1;push_down(p , l , r);
	if(idx <= mid) return query1(ls(p) , l , mid , idx);
	else return query1(rs(p) , mid + 1 , r , idx); 
}
void update2(int p,int l,int r,int idx,int w)
{
	if(l == r){ans[p][1] += w ; return;}
	int mid = (l + r) >> 1;
	if(idx <= mid) update2(ls(p) , l , mid , idx , w);
	else update2(rs(p) , mid + 1 , r , idx , w);
	push_up(p); 
}
int query2(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return ans[p][1];
	int mid = (l + r) >> 1 , res = 0;
	if(nl <= mid) res += query2(ls(p) , l , mid , nl , nr);
	if(nr > mid) res += query2(rs(p) , mid + 1 , r , nl , nr);
	return res; 
}
void dfs1(int x,int f)
{
	id[x] = ++ tot;
	siz[x] = 1;
	for(int e = head[x][1] ; e ; e = edge[e][1].next)
	{
		int to = edge[e][1].to;
		if(to == f) continue;
		dfs1(to , x);
		siz[x] += siz[to];
	}
}
int anss , Ans;
void dfs2(int x,int f)
{
	int f1 = 0 , Fd = 0;
	if(!query2(1 , 1 , n , id[x] , id[x] + siz[x] - 1)) //如果加进去的点会覆盖其他点也就是说这个点在B树中是现在已有点的祖先，那么加进去一定会更不优 
	{
		f1 = 1;
		Fd = query1(1 , 1 , n , id[x]);
		if(!Fd)//说明此时并没有覆盖到这里来
		{
			update1(1 , 1 , n , id[x] , id[x] + siz[x] - 1 , x);
			update2(1 , 1 , n , id[x] , 1);	
			anss ++;
		} 
		else//此时说明我们新加进去的点被覆盖了，此时这个已有点一定在B树中是当前点的祖先，考虑换掉它 
		{
			update1(1 , 1 , n , id[Fd] , id[Fd] + siz[Fd] - 1 , -1);
			update2(1 , 1 , n , id[Fd] , -1);
			update1(1 , 1 , n , id[x] , id[x] + siz[x] - 1 , x);
			update2(1 , 1 , n , id[x] , 1);	
		}
	}
	Ans = max(Ans , anss);
	for(int e = head[x][0] ; e ; e = edge[e][0].next)
	{
		int to = edge[e][0].to;
		if(to == f) continue;
		dfs2(to , x);
	}
	if(f1)
	{
		if(!Fd)
		{
			update1(1 , 1 , n , id[x] , id[x] + siz[x] - 1 , -1);
			update2(1 , 1 , n , id[x] , -1);
			anss --;	
		}
		else
		{
			update1(1 , 1 , n , id[x] , id[x] + siz[x] - 1 , -1);//这里需要注意为了完全还原，我们得先还原x再还原Fd 
			update2(1 , 1 , n , id[x] , -1);
			update1(1 , 1 , n , id[Fd] , id[Fd] + siz[Fd] - 1 , Fd);
			update2(1 , 1 , n , id[Fd] , 1);		
		}
	}
}
signed main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d",&n);
		cnt[0] = cnt[1] = tot = Ans = anss = 0;memset(head , 0 , sizeof head);
		for(int i = 2 ; i <= n ; i ++)
		{
			int x;scanf("%d",&x);
			add(x , i , 0);
		}
		for(int i = 2 ; i <= n ; i ++)
		{
			int x;scanf("%d",&x);
			add(x , i , 1);
		}
		build(1 , 1 , n);
		dfs1(1 , 0);
		//for(int i = 1 ; i <= n ; i ++) printf("%d %d\n",id[i],siz[i]);
		dfs2(1 , 0);
		printf("%d\n",Ans);
	}
	return 0;
}
```

---

## 作者：忘怀星 (赞：1)

考虑最大团的实际意义。我们可以发现，最大团的点在 A 树上必然是从根开始的一条链上，而在 B 树上，必然是没有任何的祖先后代关系。

我们考虑在 A 树的一条链，如何求出最多多少个点在 B 中无祖先-后代关系。

我们贪心的想，一个点自然是深度越大越好。也就是对于一个新的点 $u$ ，若他的子树内有被选中的点 $v$ ，那必然是选择不选择 $u$ 为好。

若 $v$ 的子树内无选中点，那么我们看一下从 $v$ 到根的路径上是否有选中点，若有的话将其删掉，然后选中 $u$ 。该操作就相当于将选中点贪心的向下移。

我们可以使用线段树，将选中点赋值为 1 ，未选中点赋值为 0 。那么使用树剖维护子树中以及到根路径上有无选中点。

现在我们将树 B 搞一下树剖，然后 DFS 树 A ，每 DFS 一个点，用它更新最大团， DFS 出去的时候将修改撤销即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#define mid (l+r>>1)

using namespace std;

namespace model{
	const int N = 1e6+7,P=998244353;
	int read()
	{
		int a = 0,x = 1;char ch = getchar();
		while(ch > '9' || ch < '0') {if(ch == '-') x = -1;ch = getchar();}
		while(ch >= '0' && ch <= '9'){a = a*10 + ch-'0';ch = getchar();}
		return a*x;
	}
	int fpow(int a,int x,int p) 
	{
		if(x == 1) return a;
		if(x == 0) return 1;
		int t = fpow(a,x>>1,p);
		if(x&1) return t*t%p*a%p;
		return t*t%p;
	}
	void Mod(int &a) {if(a >= P) a %= P;}
}

using model::read;
using model::N;

int n,a[N],fa[N],siz[N],son[N],str[N],dep[N],dfn[N],pos[N];

int head[N],go[N],nxt[N],cnt;
void add(int u,int v)
{
	go[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}

void dfs1(int u)
{
	dep[u] = dep[fa[u]] + 1,siz[u] = 1,son[u] = 0;
	for(int e = head[u];e;e = nxt[e]) {
		int v = go[e];
		dfs1(v);siz[u] += siz[v];if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

void dfs2(int u,int h)
{
	str[u] = h;dfn[u] = ++cnt;pos[cnt] = u;
	if(son[u]) dfs2(son[u],h);
	for(int e = head[u];e;e = nxt[e]) {
		int v = go[e];if(v == son[u]) continue;
		dfs2(v,v);
	}
}

int tot,tre[N*6],ls[N*6],rs[N*6],rt,tre1[N*6],ans;
int Newnode() {++tot;ls[tot] = rs[tot] = tre[tot] = tre1[tot] = 0;return tot;}

void push_up(int root)
{
	tre[root] = tre[ls[root]] + tre[rs[root]];
	tre1[root] = tre1[ls[root]] ? tre1[ls[root]] : tre1[rs[root]];
}

void modify(int &root,int l,int r,int p,int x)
{
	if(!root) root = Newnode();
	if(l == r && l == p) {tre[root] = x,tre1[root] = x*pos[l];return ;}
	if(p <= mid) modify(ls[root],l,mid,p,x);
	else modify(rs[root],mid+1,r,p,x);
	push_up(root);
}

int query(int root,int l,int r,int ql,int qr)
{
	if(l > qr || r < ql || !root) return 0;
	if(l >= ql && r <= qr) return tre[root];
	return query(ls[root],l,mid,ql,qr) + query(rs[root],mid+1,r,ql,qr);
}

int query_p(int root,int l,int r,int ql,int qr)
{
	if(l > qr || r < ql || !root) return 0;
	if(l >= ql && r <= qr) return tre1[root];
	int tmp = query_p(ls[root],l,mid,ql,qr);
	if(tmp) return tmp;
	else return query_p(rs[root],mid+1,r,ql,qr);
}

int getplace(int a)
{
	int tmp = 0;
	while(a) {
		if(tmp = query_p(rt,1,n,dfn[str[a]],dfn[a])) return tmp;
		a = fa[str[a]];
	}
	return 0;
}

void dfs(int u)
{
	int tmp1=0,tmp2=0;
	if(query(rt,1,n,dfn[u],dfn[u]+siz[u]-1)) tmp2 = 0;
	else {
		tmp2 = 1,tmp1 = getplace(u);
		if(tmp1) modify(rt,1,n,dfn[tmp1],0);
		modify(rt,1,n,dfn[u],1);
	}
	ans = max(ans,tre[rt]);
	for(int e = head[u];e;e = nxt[e]) {
		int v = go[e];dfs(v);
	}
	if(tmp2) {
		if(tmp1) modify(rt,1,n,dfn[tmp1],1);
		modify(rt,1,n,dfn[u],0);
	}
}

void solve()
{
	n = read();head[1] = cnt = rt = ans = 0;
	for(int i = 2;i <= n;i ++) a[i] = read(),head[i] = 0;
	for(int i = 2;i <= n;i ++) fa[i] = read(),add(fa[i],i);
	dfs1(1);cnt=0;dfs2(1,1);tot = 0;cnt = 0;
	for(int i = 1;i <= n;i ++) head[i] = 0;
	for(int i = 2;i <= n;i ++) add(a[i],i);
	dfs(1);printf("%d\n",ans);
}

int main()
{
	int t = read();
	while(t --) solve();
}
```

---

