# Tree Factory

## 题目描述

Bytelandian Tree Factory 生产各种工业用途的树，你的任务是为一个特别大的重要订单优化生产。

问题中的树是一棵 $n$ 个节点的有根树，每个顶点用不同的整数编号为 $[0,1,...,n-1]$，其中 $0$ 是根节点，且对于任何非根节点 $v$，它的父节点的编号 $p(v)$ 比它的编号 $v$ 小。

工厂里所有的树都是用竹子做的（可能不准确但不影响题意理解），这种竹子是有根的树，且每个节点只有一个子节点（除了叶子节点没有子节点），也就是说，它是一条链。加工前，竹子的节点可以随意编号。

要加工竹子为一棵树，可以进行这样的操作：选择任意一个不是根节点且父节点也不是根节点的节点 $v$，将它的父节点变成原先父节点的父节点即 $p(p(v))$，而其它节点的父节点都保持不变，$v$ 的子树也不会改变。

效率是至关重要的，所以在加工出所需要的树的前提下你应当最小化操作数。现在请你构造任何最优的操作序列以生成所需要的树。

注意：加工出的结果树的编号必须和所需要的树的编号一致，即根节点编号相同，其它所有具有相同编号的节点 $v$，其父节点编号 $p(v)$ 也应相同。

数据保证任何输入都至少有一种可行的方案，且最优操作序列最多包含 $10^6$ 个操作。而不符合这些条件的 hack 数据都是无效的（codeforce 允许 hack 其它人，洛谷上现在可以无视这句）。

## 样例 #1

### 输入

```
5
0 0 1 1
```

### 输出

```
0 2 1 4 3
2
1 3
```

## 样例 #2

### 输入

```
4
0 1 2
```

### 输出

```
0 1 2 3
0

```

# 题解

## 作者：Kelin (赞：5)

## [题意](https://blog.csdn.net/BeNoble_/article/details/102876036)
一条链，每次可以选择一个节点$u$使得其$fa[fa[u]]$变成$fa[u]$

其中$u$和$fa[u]$都不是根节点，并且操作后其他节点父亲节点都不变

你可以通过若干次这样的操作使得这一条链变成一棵树

现在给你一棵$n$个节点的树，求能用最少的操作变出这棵树的链

$2\le n\le10^5,0\le$操作数$k\le10^6$

---

## 题解

考虑一次对$w$的操作

![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102203020113.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JlTm9ibGVf,size_5,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102211559542.png)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102203106385.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JlTm9ibGVf,size_16,color_FFFFFF,t_70,=250x240)

那么把树变回链的逆操作就是当前节点变成兄弟节点的父亲

考虑合并一个节点的两个子节点的子链的代价

由于每次都只能将一个点并到链上，那么把一条子链并到另外一条子链上的代价就是链长

形象一点就是这样

![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102205419399.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JlTm9ibGVf,size_5,color_FFFFFF,t_7,=170x200)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102211559542.png)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102205755507.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JlTm9ibGVf,size_5,color_FFFFFF,t_70,=170x200)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102211559542.png)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102205844707.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JlTm9ibGVf,size_5,color_FFFFFF,t_70,=170x200)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102211559542.png)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191102211045135.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JlTm9ibGVf,size_16,color_FFFFFF,t_70,=170x200)

所以可以考虑贪心每次把短链合并到长链上

可以发现把短链并到长链上后长链上的点一定是最终链上最后的那一部分点

由于短链去合并的顺序并不影响答案，所以最终的链其实就是整棵树的$dfn$，其中长链节点是最后一步$dfs$的

时间复杂度$O(n+k)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
using arr=int[N];
int n,m,Ans;
arr f,fa,dep,dfn,Son;
vector<int>G[N];
void dfs(int u){
	dfn[++m]=u;
	for(auto v:G[u])
		if(v!=Son[u])
			dfs(v);
	if(Son[u])dfs(Son[u]);
}
int main(){
	scanf("%d",&n);
	for(int i=2,u;i<=n;++i){
		scanf("%d",&u);
		fa[i]=++u;
		G[u].push_back(i);
		dep[i]=dep[u]+1;
	}
	for(int i=n;i>1;--i)
		if(f[i]+1>=f[fa[i]]){
			f[fa[i]]=f[i]+1;
			Son[fa[i]]=i;
		}
	dfs(1);
	for(int i=1;i<=n;++i)printf("%d%c",dfn[i]-1," \n"[i==n]);
	for(int i=2;i<=n;++i)Ans+=dep[dfn[i-1]]-dep[fa[dfn[i]]];
	printf("%d\n",Ans);
	for(int i=2;i<=n;++i)
		for(int j=dep[dfn[i-1]]-dep[fa[dfn[i]]];j;--j)
			printf("%d ",dfn[i]-1);
return 0;
}
```




---

## 作者：Lucifer_Bartholomew (赞：2)

# 模拟+贪心
题意简述:给出一棵树,每次操作可以将一个节点从它的父亲节点重新连到它的兄弟节点上,求将这棵树退化成链的最少步数,输出操作后遍历链的编号,最少操作次数,及每次操作的节点编号。

按照题意模拟。观察这个操作,为了退化成链,对于每个节点,它的子节点只能保留一个,其它子节点依次连到另一个子节点的子树中的叶子节点上,最后连到保留的子节点子树中的叶子节点上,即如图所示:
![](https://cdn.luogu.com.cn/upload/image_hosting/hhjd33e2.png)

每次将一个节点移动到其兄弟节点的子树中的叶子节点上且保证操作次数尽量少还不对其子树中的节点造成影响,就要将其连到叶子节点中到其兄弟节点距离最大的点上,即其兄弟节点的主链的叶子节点上。

我们可以发现对于每个节点,如果要将其所有子节点全操作完且保证操作次数尽量少,最后显然不能将其移动到主链长度最大的子树上,所以贪心每次取当前子树主链长度最大的子节点连到其它子节点上。

具体实现细节见代码。

```cpp
#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct edge{
	int v,next;
}e[200001];
int cnt,head[100001],fa[100001],maxn[100001];
vector<int> ord,up;
inline void add(int u,int v)//前向星存图
{
	e[++cnt]=(edge){v,head[u]};
	head[u]=cnt;
}
inline void dfs(int u)//预处理主链
{
	maxn[u]=0;
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if(fa[u]!=v)
		{
			dfs(v);
			maxn[u]=max(maxn[u],maxn[v]);//处理主链
		}
	}
	maxn[u]+=1;
}
typedef pair<int,int> p;
inline void check(int u)//操作
{
	multiset<p> s;//存子节点的主链长度
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if(fa[u]!=v)s.insert(make_pair(maxn[v],v));//插入
	}
	if(s.empty())return;//没有子节点
	for(multiset<p>::iterator it=s.begin();it!=s.end();++it)
	{
		ord.push_back(it->second);//存链的输出
		check(it->second);//先处理子节点
	}
	int pre=s.begin()->first;//上一个子节点的主链长度就是下一个子节点的操作次数,可以保证主链最长的子节点不会被其它子节点操作
	for(multiset<p>::iterator it=s.begin();it!=s.end();++it)
		if(it!=s.begin())
		{
			for(int i=1;i<=pre;++i)
				up.push_back(it->second);//存操作节点编号
			pre=it->first;
		}
}
int main()
{
	memset(head,-1,sizeof head);
	int n=read();
	for(int i=1;i<n;++i)
	{
		int u=read();
		fa[i]=u;
		add(u,i);
		add(i,u);
	}
	ord.push_back(0);
	dfs(0);
	check(0);
	for(int i=0;i<ord.size();++i)//输出链
		printf("%d ",ord[i]);
	printf("\n%d\n",up.size());//存了几个操作节点编号就操作了几次
	for(int i=0;i<up.size();++i)//输出操作节点编号
		printf("%d ",up[i]);
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：caidzh (赞：1)

这里是一个由链$->$树的正向考虑的做法，与官方题解有一定区别，但实际上是一个东西

题意简述：给出一棵树，给出一种操作：**将一个节点的父亲变成一个节点父亲的父亲，其他点的父亲保持不变**。请构造出一条链，使得可以在最小的操作次数下将这条链变成这棵树

### $Step.1$ 问题一定有解的证明

首先来考虑这样一件事情：**这个问题一定有解**

我们通过一定的构造可以说明这个问题：现在我们有一棵有根树，我们去掉根，剩下一个森林，我们不妨假设：**每一棵子树内的点在链上均是相邻的。**

在链上的操作可以如下实现：对于每棵子树所在的一个“子链”，我们单独将其分裂出去，方法是通过不断地跳父亲，**跳出这个“子链”上方的那条“子链”**，接下来可以对这个“子链”下方的“子链”进行这样的操作，这样就可以把所有子树分割出来

我们发现对于去掉根后的每个链，**都是原问题的一个子问题**，因为原问题有解，那么子问题一定也可以通过这样的方式出解，因此整个问题一定存在一种解

接下来我们可以发现上面的假设：**每一棵子树内的点在链上均是相邻的**是正确的，这个可以通过手玩和感性理解得到，这里不证了

### $Step.2$ 构造最小操作次数方案

现在考虑怎么最小化操作次数，一个$naive$的想法是：在上面的构造中，每次跳的时候我们可以发现，跳的次数是这个“子链”上方的“子链”大小，我们可以贪心考虑将子树大小最大的链放在最后面，这样就不会被计入答案了，时间复杂度$O(n)$

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=100010;
int n,head[maxn],cnt,fa[maxn];
struct Edge{int nxt,to;}edge[maxn];
void add_edge(int x,int y){edge[++cnt].nxt=head[x];edge[cnt].to=y;head[x]=cnt;}
int size[maxn];
void dfs(int x){
	size[x]=1;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;dfs(v);size[x]+=size[v];
	}
}
int line[maxn],opt[maxn*10],top,ID[maxn];
void solve(int x,int id){
	line[id]=x;if(size[x]==1)return;int maxson=-1,son=0;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(maxson<size[v])maxson=size[v],son=v;
	}int pl=0,pre=0,sum=id+1;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(son!=v){pl=v;pre=size[v];ID[v]=id+1;sum=ID[v]+size[v];break;}
	}
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(pl!=v&&v!=son){
			ID[v]=sum;
			for(int j=1;j<=pre;j++)opt[++top]=v;
			pre=size[v];sum=ID[v]+size[v];
		}
	}
	if(son!=0){ID[son]=sum;for(int i=1;i<=pre;i++)opt[++top]=son;}
	if(pl!=0)solve(pl,ID[pl]);
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v!=son&&v!=pl)solve(v,ID[v]);
	}if(son!=0)solve(son,ID[son]);
}
int main()
{
	n=read();
	for(int i=2;i<=n;i++){
		int v=read()+1;add_edge(v,i);fa[i]=v;
	}dfs(1);solve(1,1);
	for(int i=1;i<=n;i++)printf("%d ",line[i]-1);printf("\n%d\n",top);
	for(int i=1;i<=top;i++)printf("%d ",opt[i]-1);return 0;
}
```
这是我最开始的想法，但是它错误了，其错误之处在于，上面证明有解其本身的构造就是有问题的，这种暴力的跳法本身就会多出一些操作次数，而我们的想法就是针对这种跳法的贪心，自然是错误的，具体可以见下图的说明

![](https://cdn.luogu.com.cn/upload/image_hosting/3rqrxsup.png)

上图的简要意思是：我们可以先操作一个子树内的点，使接下来的另一棵子树上跳减少次数，然而我们上面的递归分治法总是先分裂子树，再对子树进行操作，所以出现了操作不优的问题

因此：子树内的上跳操作优先级大于分裂子树的上跳操作的优先级

这么考虑后，我们大胆猜一个结论：**处理时子树内能跳就跳**

我们可以考虑不使用递归分治的方法来构造方案，**即我们考虑得到这棵树的一个$dfs$序后进行单点暴力上跳来得到答案**，这样子树内的上跳操作的优先级就大于了分裂子树的上跳操作的优先级，操作自然会比上面构造的优

现在的问题是：我们怎么贪心得到最优的$dfs$序

简单的想法还是利用上面类似于重链剖分的方式，但是我可以通过实际操作告诉你这假了

通过一定的手玩我们可以发现：一棵子树内最深的点的深度越小，将其放在越前面最优（当然你也可以通过意识到与深度有关，然后尝试四种情况进行对拍得到）

一种感性的理解方式是：我把其他点接在最深的点下面，然后进行上面的分割子树的方式，根据上面说明一定有解的构造中分割子树的经验：当然不考虑最深的那个好！因为要排序这里的时间复杂度为$O(nlogn)$

猜测：如果只把最深的那个放在最后，其他随便排，是否正确？如果正确，复杂度将降为$O(n)$，这个我没有进行尝试，因此仅是猜测

代码比原来的还要好写：
```
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=100010;
int n,head[maxn],cnt,size[maxn],total,fa[maxn],p[maxn],dep[maxn],f[maxn];
struct Edge{int nxt,to;}edge[maxn];
void add_edge(int x,int y){edge[++cnt].nxt=head[x];edge[cnt].to=y;head[x]=cnt;}
void dfs(int x){
	dep[x]=dep[fa[x]]+1;size[x]=1;int flag=1;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;dfs(v);
		flag=0;f[x]=max(f[v],f[x]);size[x]+=size[v];
	}if(flag)f[x]=dep[x];
}
struct Node{int val,id;}A[maxn];
int line[maxn],opt[maxn*10],top,ID[maxn];
bool cmp(Node x,Node y){return x.val<y.val;}
void solve(int x,int id){
	line[id]=x;if(size[x]==1)return;int tot=0;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;A[++tot].val=f[v];A[tot].id=v;
	}int sum=id+1;sort(A+1,A+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		int v=A[i].id;ID[v]=sum;sum=ID[v]+size[v];
	}Node B[tot+1];for(int i=1;i<=tot;i++)B[i]=A[i];
	for(int i=1;i<=tot;i++){int v=B[i].id;solve(v,ID[v]);}
}
void Getopt(int x){
	if(x==n+1)return;
	while(fa[line[x]]!=p[line[x]]){p[line[x]]=fa[p[line[x]]];opt[++top]=line[x];}
	Getopt(x+1);
}
int main()
{
	n=read();
	for(int i=2;i<=n;i++){int v=read()+1;add_edge(v,i);fa[i]=v;}dfs(1);solve(1,1);
	for(int i=2;i<=n;i++)p[line[i]]=line[i-1];Getopt(2);
	for(int i=1;i<=n;i++)printf("%d ",line[i]-1);printf("\n%d\n",top);
	for(int i=1;i<=top;i++)printf("%d ",opt[i]-1);return 0;
}
```


---

## 作者：tzc_wk (赞：0)

~~没有人给出证明吗？qwq~~

首先答案下界显然是 $n-\max\limits_{i=0}^{n-1}dep_i$​，其中 $dep_i$​ 表示 $i$​ 到根节点路径上的点数，因为每次操作最多使整棵树深度最深的节点的深度减少 $1$。考虑构造使其达到这个下界。

我们对整棵树进行一遍 DFS，当我们 DFS 到点 $u$ 时，我们将每个节点所有儿子按照其 $mxdep$ 从小到大排序，然后每次按 $mxdep$ 从小到大的顺序依次遍历每个儿子，假设当前遍历到节点 $v$，那么我们就将当前链上端的 $siz_v$ 个节点做成 $v$ 子树的形态，如果 $v$ 不是最后一个儿子，那么我们就不断执行操作上推这条链上第 $siz_v+1$ 个节点下端的链直到这个点的父亲为 $u$ 为止，不难发现该做法的时间复杂度与长链剖分复杂度类似，具体来说，对于一条链，假设其链顶节点为 $u$，其父亲为 $f$，那么当我们 DFS 到 $f$ 时，会进行 $mxdep_u$ 次上推操作，因此操作次数就是所有长链的长度之和，根据长链剖分那套理论可知所有长链的长度之和为 $n$。特别地，$1$​ 所在的长链是不会产生贡献的，因此需减去 $mxdep_1$，由此可知操作次数为 $n-mxdep_1$。

```cpp
const int MAXN=1e5;
int n,siz[MAXN+5],mxdep[MAXN+5];vector<int> g[MAXN+5];
void dfs0(int x){
	siz[x]=1;mxdep[x]=0;
	for(int y:g[x]) dfs0(y),siz[x]+=siz[y],chkmax(mxdep[x],mxdep[y]+1);
}
int seq[MAXN+5],slen=0;vector<int> res;
void dfs1(int x){seq[++slen]=x;for(int y:g[x]) dfs1(y);}
void dfs2(int x,int l,int r){
	++l;
	for(int y:g[x]){
		dfs2(y,l,l+siz[y]-1);
		if(l+siz[y]<=r){
//			printf("%d %d\n",y,l);
			for(int i=1;i<=mxdep[y]+1;i++)
				res.pb(seq[l+siz[y]]);
		} l+=siz[y];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,f;i<n;i++) scanf("%d",&f),g[f].pb(i);dfs0(0);
	for(int i=0;i<n;i++) sort(g[i].begin(),g[i].end(),[&](int x,int y){return mxdep[x]<mxdep[y];});
	dfs1(0);for(int i=1;i<=n;i++) printf("%d%c",seq[i]," \n"[i==n]);
	dfs2(0,1,n);printf("%d\n",res.size());
	for(int x:res) printf("%d ",x);
	return 0;
}
```

---

