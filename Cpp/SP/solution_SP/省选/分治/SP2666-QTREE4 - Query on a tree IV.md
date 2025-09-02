# QTREE4 - Query on a tree IV

## 题目描述

You are given a tree (an acyclic undirected connected graph) with $N$ nodes, and nodes numbered $1,2,3\ldots,N$. Each edge has an integer value assigned to it (note that the value can be negative). Each node has a color, white or black. We define $dist(a, b)$ as the sum of the value of the edges on the path from node $a$ to node $b$.

All the nodes are white initially.

We will ask you to perfrom some instructions of the following form:

- `C a` : change the color of node $a$.(from black to white or from white to black)
- `A` : ask for the maximum $dist(a, b)$, both of node a and node $b$ must be white ($a$ can be equal to $b$). Obviously, as long as there is a white node, the result will alway be non negative.

## 样例 #1

### 输入

```
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A```

### 输出

```
2
2
0
They have disappeared.```

# 题解

## 作者：xtx1092515503 (赞：117)

本题与[[ZJOI2007]捉迷藏](https://www.luogu.com.cn/problem/P2056)几乎是重题，只不过是带边权或是不带边权的区别罢了。这里所有代码都是**不带边权**的写法，也即上方link中的那题的写法。

这里介绍$5$种写法，在复杂度方面有所差别，并且难度**依次递增**。

------------

法一：直径的性质+线段树

根据直径的性质，当你合并两个点集时，新点集的直径，必定来自于**被合并的两个点集直径四个端点中的某两个**。

换句话说，设集合$\mathbb{S}$的直径端点集合为$f(\mathbb{S})$，则应有

$$f(\mathbb{S}\cup\mathbb{T})\subseteq f(\mathbb{S})\cup f(\mathbb{T})$$

则我们可以用线段树维护区间直径。对于白点（关灯点），直径初始化为$(x,x)$；对于黑点（开灯点），直径初始化为$(-1,-1)$。然后直接在线段树上维护即可。

因为维护直径的过程中需要计算两点间距离，所以我们需要求LCA。如果使用倍增/树剖，总复杂度就是$O(n\log^2n)$的；如果使用ST表，复杂度则为$O(n\log n)$。

代码（ST表）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
int n,m,DEP[200100][20],dep[100100],in[100100],LG[200100],cnt;
bool on[100100];
vector<int>v[100100];
void dfs(int x,int fa){
	dep[x]=dep[fa]+1;
	DEP[in[x]=++cnt][0]=dep[x];
	for(auto y:v[x])if(y!=fa)dfs(y,x),DEP[++cnt][0]=dep[x];
}
int LCADEP(int x,int y){
	x=in[x],y=in[y];
	if(x>y)swap(x,y);
	int k=LG[y-x+1];
	return min(DEP[x][k],DEP[y-(1<<k)+1][k]);
}
int DIS(int x,int y){
	if(x==-1||y==-1)return -1;
	return dep[x]+dep[y]-2*LCADEP(x,y);
}
struct SegTree{
	int u,v;
}seg[1200100];
void pushup(int x){
	if(seg[lson].u==-1&&seg[lson].v==-1){seg[x]=seg[rson];return;}
	if(seg[rson].u==-1&&seg[rson].v==-1){seg[x]=seg[lson];return;}
	if(DIS(seg[lson].u,seg[lson].v)>DIS(seg[rson].u,seg[rson].v))seg[x]=seg[lson];else seg[x]=seg[rson];
	if(DIS(seg[lson].u,seg[rson].u)>DIS(seg[x].u,seg[x].v))seg[x].u=seg[lson].u,seg[x].v=seg[rson].u;
	if(DIS(seg[lson].u,seg[rson].v)>DIS(seg[x].u,seg[x].v))seg[x].u=seg[lson].u,seg[x].v=seg[rson].v;
	if(DIS(seg[lson].v,seg[rson].u)>DIS(seg[x].u,seg[x].v))seg[x].u=seg[lson].v,seg[x].v=seg[rson].u;
	if(DIS(seg[lson].v,seg[rson].v)>DIS(seg[x].u,seg[x].v))seg[x].u=seg[lson].v,seg[x].v=seg[rson].v;
}
void modify(int x,int l,int r,int P){
	if(l>P||r<P)return;
	if(l==r){
		if(seg[x].u==-1&&seg[x].v==-1)seg[x].u=seg[x].v=P;
		else seg[x].u=seg[x].v=-1;
		return;
	}
	modify(lson,l,mid,P),modify(rson,mid+1,r,P),pushup(x);
}
void build(int x,int l,int r){
	if(l==r)seg[x].u=seg[x].v=l;
	else build(lson,l,mid),build(rson,mid+1,r),pushup(x);
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
	dfs(1,0);
//	for(int i=1;i<=n;i++)printf("%d ",dep[i]);puts("");
//	for(int i=1;i<=n;i++)printf("%d ",in[i]);puts("");
//	for(int i=1;i<=cnt;i++)printf("%d ",DEP[i][0]);puts("");
	for(int i=2;i<=cnt;i++)LG[i]=LG[i>>1]+1;
	for(int j=1;j<=LG[cnt];j++)for(int i=1;i+(1<<j)-1<=cnt;i++)DEP[i][j]=min(DEP[i][j-1],DEP[i+(1<<(j-1))][j-1]);
	build(1,1,n);
	scanf("%d",&m);
	for(int i=1,x;i<=m;i++){
		char s[10];
		scanf("%s",s);
		if(s[0]=='G')printf("%d\n",DIS(seg[1].u,seg[1].v));
		else scanf("%d",&x),modify(1,1,n,x);
	}
	return 0;
} 
```

------------

法二：动态淀粉质/点分树（理论上的正解）

我们考虑点分树上一个点的子树。我们可以从子树上扒出任意两条**以当前子树树根为端点**的路径，并将它们拼成一条完整的路径。但显然，这两条路径的另一端，不能来自于树根的同一棵子树（注意这里是**原树上的子树**），不然它们的LCA就不是树根了。

那怎么办呢？

我们想到，点分树上树根的某一棵子树，就对应着原树上的那棵子树。

因此，我们可以在儿子节点维护儿子子树中所有节点**到树根的距离**，用一个数据结构维护，记作$self_x$。

我们再在父亲节点，维护其**所有（点分树上）儿子$self_x$中最大值**，用一个记作$son_x$的数据结构来维护。则树根的答案就是$son_x$中的最大值与次大值之和。我们将这个和再扔进一个全局数据结构维护，记作$globe$。

则最终答案**即为$globe$中的最大值**。

再来梳理一遍在节点$x$要干点什么：

1. 维护子树中所有节点到$x$的父亲的距离，并存入$self_x$；

2. 维护所有儿子的$self_y$中的最大值，并存入$son_x$；

3. 维护$son_x$中最大与次大之和，存入$globe$。

最后，我们要考虑这三个数据结构应该使用什么来维护比较好。

显然，因为要支持修改，一个naive的想法就是使用一个```std::multiset```维护，可删可加。但是```multiset```的常数太大，不太保险。

注意到一共只是求最大和次大值。这样我们就可以使用**两个堆**来维护。一个堆维护加入的元素，另一个维护删除的，如果两个堆的堆顶相同，则一起弹出。这种维护方式常数较小，优于```multiset```。

对于白点，我们只需要在$self_x$中加入一个$DIS(x,fa_x)$，在$son_x$中加入一个$0$即可，这代表了白点本身。

最后是复杂度分析。显然，因为点分树是$\log n$高度的，套上了堆就是$n\log^2n$的。我们最好采取$O(1)$的ST表来求LCA——尽管求LCA的动作是与堆平行的，即就算是$O(\log n)$求LCA，总复杂度仍为$O(n\log^2n)$，但是常数能小一点就小一点吧。

~~为什么我这么强调复杂度呢？因为我自己就是因为常数原因死活没卡过去~~

TLE80的代码:

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[100100],dfn[200100][20],dep[200100],in[200100],tot,LG[200100],col[200100],On;
namespace Tree{
	vector<int>v[100100];
	int ROOT,SZ,sz[100100],msz[100100];
	bool vis[100100];
	void getsz(int x,int fa){
		sz[x]=1;
		for(auto y:v[x])if(!vis[y]&&y!=fa)getsz(y,x),sz[x]+=sz[y];
	}
	void getroot(int x,int fa){
		sz[x]=1,msz[x]=0;
		for(auto y:v[x])if(!vis[y]&&y!=fa)getroot(y,x),sz[x]+=sz[y],msz[x]=max(msz[x],sz[y]);
		msz[x]=max(msz[x],SZ-sz[x]);
		if(msz[x]<msz[ROOT])ROOT=x;
	}
	void solve(int x){
		vis[x]=true,getsz(x,0);
		for(auto y:v[x]){
			if(vis[y])continue;
			SZ=sz[y],ROOT=0,getroot(y,0),fa[ROOT]=x,solve(ROOT);
		}
	}
	void getural(int x,int fa){
		dfn[++tot][0]=x,in[x]=tot;
		for(auto y:v[x])if(y!=fa)dep[y]=dep[x]+1,getural(y,x),dfn[++tot][0]=x;
	}
}
int MIN(int i,int j){
	return dep[i]<dep[j]?i:j;
}
int LCA(int i,int j){
	if(i>j)swap(i,j);
	int k=LG[j-i+1];
	return MIN(dfn[i][k],dfn[j-(1<<k)+1][k]);
}
int DIS(int i,int j){
	return dep[i]+dep[j]-2*dep[LCA(in[i],in[j])];
}
namespace CDT{
	vector<int>v[100100];
	struct Insert_And_Delete_Heap{
		priority_queue<int>all,era;
		void Push(int x){all.push(x);}
		void Delete(int x){if(all.top()==x)all.pop();else era.push(x);}
		void Flush(){while(!all.empty()&&!era.empty()&&all.top()==era.top())all.pop(),era.pop();}
		int Top(){Flush();return all.top();}
		int Size(){
			return all.size()-era.size();
		}
		int Calc(){
			int x=Top();
			all.pop();
			int y=Top();
			Push(x);
			return x+y;
		}
		void Print(){
			vector<int>v;
			Flush();
			while(!all.empty())v.push_back(all.top()),all.pop(),Flush();
			for(auto x:v)printf("%d ",x);puts("");
			while(!v.empty())Push(v.back()),v.pop_back();
		}
	}self[100100],sons[100100],globe;
	void GlobalDelete(int x){if(sons[x].Size()>=2)globe.Delete(sons[x].Calc());}
	void GlobalInsert(int x){if(sons[x].Size()>=2)globe.Push(sons[x].Calc());}
	void SonDelete(int x){if(self[x].Size()>=1)sons[fa[x]].Delete(self[x].Top());}
	void SonInsert(int x){if(self[x].Size()>=1)sons[fa[x]].Push(self[x].Top());}
	void Reverse(int x){
		int u=x;
		if(!col[x]){
			GlobalDelete(x),sons[x].Delete(0),GlobalInsert(x);
			while(fa[u]){
				GlobalDelete(fa[u]),SonDelete(u);
				self[u].Delete(DIS(fa[u],x));
				SonInsert(u),GlobalInsert(fa[u]);
				u=fa[u];
			}
			On--;
		}else{
			GlobalDelete(x),sons[x].Push(0),GlobalInsert(x);
			while(fa[u]){
				GlobalDelete(fa[u]),SonDelete(u);
				self[u].Push(DIS(fa[u],x));
				SonInsert(u),GlobalInsert(fa[u]);
				u=fa[u];
			}
			On++;
		}
		col[x]^=1;
	}
	void Init(int x,int z){
//		printf("%d:(%d,%d):%d\n",z,fa[z],x,DIS(fa[z],x));
		self[z].Push(DIS(fa[z],x));
		for(auto y:v[x])Init(y,z);
	}
	void Prepare(){
		for(int i=1;i<=n;i++)if(fa[i])v[fa[i]].push_back(i);
		for(int i=1;i<=n;i++)if(fa[i])Init(i,i);
//		for(int i=1;i<=n;i++)if(fa[i])printf("%d:",i),self[i].Print();
		for(int i=1;i<=n;i++)sons[i].Push(0);
		for(int i=1;i<=n;i++)if(fa[i])SonInsert(i);
		for(int i=1;i<=n;i++)GlobalInsert(i);
//		for(int i=1;i<=n;i++)printf("%d:",i),self[i].Print(),putchar(';'),sons[i].Print(),putchar('\n');
	}
}
void read(int &x){
	x=0;
	char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
}
int main(){
	read(n),On=n;
	for(int i=1,x,y;i<n;i++)read(x),read(y),Tree::v[x].push_back(y),Tree::v[y].push_back(x);
	Tree::msz[0]=0x3f3f3f3f,Tree::SZ=n,Tree::getroot(1,0),Tree::solve(Tree::ROOT);
//	for(int i=1;i<=n;i++)printf("%d ",fa[i]);puts("");
	Tree::getural(1,0);
//	for(int i=1;i<=tot;i++)printf("%d ",dfn[i][0]);puts("");
//	for(int i=1;i<=n;i++)printf("%d ",dep[i]);puts("");
	for(int i=2;i<=tot;i++)LG[i]=LG[i>>1]+1;
	for(int j=1;j<=LG[tot];j++)for(int i=1;i+(1<<j)-1<=tot;i++)dfn[i][j]=MIN(dfn[i][j-1],dfn[i+(1<<(j-1))][j-1]);
	CDT::Prepare();
	read(m);
	for(int i=1,x;i<=m;i++){
		char s[10];
		scanf("%s",s);
		if(s[0]=='G')printf("%d\n",(On<=1)?On-1:CDT::globe.Top());
		else read(x),CDT::Reverse(x);
	}
	return 0;
}
```

------------

法三：括号序列+线段树

我们定义一个叫做“括号序列”的东西，它是这样生成的：

当你访问到一个节点时：

1. 在序列中加入一个左括号和节点本身编号；

2. 递归它的子树；

3. 在递归完子树后，加入一个右括号。

例如这张图是[[ZJOI2007]捉迷藏](https://www.luogu.com.cn/problem/P2056)的样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/0l5roryh.png)

它的括号序列长这样（括号大小被人工对齐了）：

$\Bigg(1\bigg(2\Big(3\big(4\big)\big(5\big)\big(6(7)(8)\big)\Big)\bigg)\Bigg)$

下面我们抽出一段序列出来，比如就抽$2\sim7$这一段。

$2(3(4)(5)(6(7$

删去编号：

$(()()(($

删去匹配的括号：

$((($

我们发现操作完后的括号序列长度刚好等于$2\sim7$的路径长度。是巧合吗？似乎不是吧？

首先，在$2$前面的任何括号，**要么属于$2$的祖先，要么属于$2$的兄弟们**，反正与$2\sim7$无关，直接扔掉。

其次，在$7$后面的任何括号，类似地也无关，可以扔掉。

然后，所有匹配成功的括号，都意味着一个**被走完的子树**，换句话说，这个子树里的所有点，都与$2\sim7$无关，也可以扔掉。

则最后我们保留在序列里的，都是些什么东西呢？

**是$2$和$7$中有且只有一个位于其子树中的所有节点**。放在图中，就是节点$3,6,7$，即路径所途经的那些节点（除去LCA）。

因此我们就证明了，**括号序列的长度等于两点距离**。

我们可以建出线段树来维护这个序列。

因为任何匹配完成的序列，最终都会得到：一堆右括号，跟着一堆左括号，即$)))\dots))(((\dots(($。

所以我们可以用一个二元组$(ribr,lebr)$表示它，其中$ribr$表示右括号数量，$lebr$表示左括号数量。

则我们在线段树上就可以维护节点所代表区间的$(ribr,lebr)$出来。具体而言，就按照匹配的定义：

```cpp
seg[x].ribr=seg[lson].ribr+max(seg[rson].ribr-seg[lson].lebr,0);
seg[x].lebr=max(seg[lson].lebr-seg[rson].ribr,0)+seg[rson].lebr;
```

左儿子的右括号同右儿子的左括号抵掉，然后没抵完的括号再合并即可。

我们接下来就要求出节点所代表区间中，**任意两个白点间的最长距离**，记为$mx_x$。

我们考虑两个区间合并后，新序列的**长度**会是什么：

$$(ribr_1,lebr_1)+(ribr_2,lebr_2)=ribr_1+|lebr_1-ribr_2|+lebr_2$$

因为$|lebr_1-ribr_2|=\max(lebr_1-ribr_2,ribr_2-lebr_1)$

所以

$$ribr_1+|lebr_1-ribr_2|+lebr_2=ribr_1+\max(lebr_1-ribr_2,ribr_2-lebr_1)+lebr_2$$

调整一下，我们就得到了

$$\max\Big((ribr_1+lebr_1)-(ribr_2-lebr_2),(ribr_1-lebr_1)+(ribr_2+lebr_2)\Big)$$

括号里面的四项，都是**只与一个子区间有关的**。

因此我们可以设：

$preplu$表示**前缀**的$\max(ribr_1+lebr_1)$

$premin$表示**前缀**的$\max(ribr_1-lebr_1)$

$sufplu$表示**后缀**的$\max(ribr_2+lebr_2)$

$sufmin$表示**后缀**的$\max(lebr_2-libr_2)$（因为在上式中这个前面是负号）

以两个$pre$为例，它们都是要么**从左儿子直接转移过来**，要么是**从右儿子延伸过整个左儿子转移过来**。两个$suf$同理。

再以两个$plu$为例，因为它们中间牵扯到**匹配**的关系，所以会出现**绝对值的形式**。将绝对值拆成取$\max$后，我们发现在从另一个儿子转移过来时，是可以从$plu$转移过来，也可以从$min$转移过来的。然后从两种转移方式中取$\max$即可。

但是对于$min$，就不同了。它们的式子中都是$X-Y$的形式，不牵扯到匹配，因此不涉及到绝对值，也就无从取$\max$了。

最后我们可以写出如下的转移方程

```cpp
seg[x].preplu=max(seg[lson].preplu,max(seg[lson].ribr-seg[lson].lebr+seg[rson].preplu,seg[lson].ribr+seg[lson].lebr+seg[rson].premin));
seg[x].premin=max(seg[lson].premin,-seg[lson].ribr+seg[lson].lebr+seg[rson].premin);
seg[x].sufplu=max(seg[rson].sufplu,max(seg[lson].sufplu-seg[rson].ribr+seg[rson].lebr,seg[lson].sufmin+seg[rson].ribr+seg[rson].lebr));
seg[x].sufmin=max(seg[rson].sufmin,seg[lson].sufmin+seg[rson].ribr-seg[rson].lebr);
```
然后就是维护$mx_x$，即任意两个白点间的最长距离了。

它可以从$3$个地方来：

1. 左儿子的$mx$；

2. 右儿子的$mx$；

3. 左右儿子拼一起，即一个$min$拼上一个$plu$。

即这样：

```cpp
seg[x].mx=max(max(seg[lson].sufmin+seg[rson].preplu,seg[lson].sufplu+seg[rson].premin),max(seg[lson].mx,seg[rson].mx));
```

这就是我们要维护的所有东西了。

在叶子节点上：

1. 如果它是括号，则相应的$ribr$或者$lebr$为$1$，其它东西都赋成$-\infty$。

2. 如果它是编号，$ribr$与$lebr$均为$0$。如果是白点的编号，其它东西赋成$0$，因为它自己到自己就算一条路径；否则，即它是黑点编号，赋成$-\infty$。

以上讨论的是**无边权的情况**。至于有边权的情况，上文中叶子节点的地方，括号处$ribr$或$lebr$处赋成**对应节点到其父亲的距离**即可。你可以把它看作是**将一条带权边拆成了相同数量的无权边**——仅仅只是括号数量增多了罢了。

复杂度$O(n\log n)$。

（另外再附赠一道括号序列的例题：[【模板】树同构（[BJOI2015]树的同构）](https://www.luogu.com.cn/problem/P5043)，可以使用括号序列或者单纯的树哈希完成）

代码（无边权，AC）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
int n,m,bac[300100],pos[100100],tot,cnt;
bool on[100100];
vector<int>v[100100];
void dfs(int x,int fa){
	bac[++tot]=-1;
	bac[pos[x]=++tot]=x;
	for(auto y:v[x])if(y!=fa)dfs(y,x);
	bac[++tot]=-2;
}
struct SegTree{
	int ribr,lebr,preplu,premin,sufplu,sufmin,mx;
}seg[1200100];
void pushup(int x){
	seg[x].ribr=seg[lson].ribr+max(seg[rson].ribr-seg[lson].lebr,0);//the right brackets in the prefix
	seg[x].lebr=max(seg[lson].lebr-seg[rson].ribr,0)+seg[rson].lebr;//the left brackets in the suffix
	seg[x].mx=max(max(seg[lson].sufmin+seg[rson].preplu,seg[lson].sufplu+seg[rson].premin),max(seg[lson].mx,seg[rson].mx));
	seg[x].preplu=max(seg[lson].preplu,max(seg[lson].ribr-seg[lson].lebr+seg[rson].preplu,seg[lson].ribr+seg[lson].lebr+seg[rson].premin));
	seg[x].premin=max(seg[lson].premin,-seg[lson].ribr+seg[lson].lebr+seg[rson].premin);
	seg[x].sufplu=max(seg[rson].sufplu,max(seg[lson].sufplu-seg[rson].ribr+seg[rson].lebr,seg[lson].sufmin+seg[rson].ribr+seg[rson].lebr));
	seg[x].sufmin=max(seg[rson].sufmin,seg[lson].sufmin+seg[rson].ribr-seg[rson].lebr);
}
void Switch(int x,int P){
	seg[x].lebr=seg[x].ribr=0,seg[x].mx=seg[x].premin=seg[x].preplu=seg[x].sufmin=seg[x].sufplu=-0x3f3f3f3f;
	if(bac[P]==-1)seg[x].lebr++;
	else if(bac[P]==-2)seg[x].ribr++;
	else if(!on[bac[P]])seg[x].premin=seg[x].preplu=seg[x].sufmin=seg[x].sufplu=0;
}
void modify(int x,int l,int r,int P){
	if(l>P||r<P)return;
	if(l==r)Switch(x,P);
	else modify(lson,l,mid,P),modify(rson,mid+1,r,P),pushup(x);
}
void build(int x,int l,int r){
	if(l==r)Switch(x,l);
	else build(lson,l,mid),build(rson,mid+1,r),pushup(x);
}
int main(){
	scanf("%d",&n),cnt=n;
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
	dfs(1,0),build(1,1,tot);
	scanf("%d",&m);
	for(int i=1,x;i<=m;i++){
		char s[10];
		scanf("%s",s);
		if(s[0]=='G')printf("%d\n",cnt<=1?cnt-1:seg[1].mx);
		else scanf("%d",&x),cnt+=(on[x]?1:-1),on[x]^=1,modify(1,1,tot,pos[x]);
	}
	return 0;
} 
```

------------

法四：树剖

我们将原树剖作很多重链，并在每条重链上**各建一颗线段树**。（注意这里是**各建**，而非常规树剖里面建一颗大线段树——原因之一是树高更低，常数更小，而原因之二之后会讲到）。

我们对于线段树上一个节点，维护：

$lmx$，表示区间**左端点**所能到达**最远的白点的距离**。

$rmx$，表示区间**右端点**所能到达**最远的白点的距离**。

$mx$，表示任意两个**LCA在区间中**的白点（这两个点并不一定在区间内）间的最大距离。

我们便可以这样维护：

```cpp
void pushup(int x,int l,int r){
	seg[x].mx=max(max(seg[seg[x].lson].mx,seg[seg[x].rson].mx),seg[seg[x].lson].rmx+1+seg[seg[x].rson].lmx);
	seg[x].lmx=max(seg[seg[x].lson].lmx,seg[seg[x].rson].lmx+(mid-l+1));
	seg[x].rmx=max(seg[seg[x].rson].rmx,seg[seg[x].lson].rmx+(r-mid));
}
```
$mx$可以从左右儿子转移过来，也可以左右儿子拼一起转移过来。

$lmx$可以从左儿子转移过来，也可以从右儿子**延伸经过整个左儿子**转移过来。

$rmx$类似。

则最终答案就是**所有重链的$mx$的最大值**。

听上去很simple，是不是？接下来就是重点了。

**叶子节点应该怎么赋值？**

你可能会想像动态淀粉质一样，在每个节点上维护子树中所有节点到它的距离——这个想法思路正确，但是方式错误。**没有点分树保证子树大小的总和是$n\log n$，是不能这么维护的**。

正确的做法依然是使用堆来维护。

对于**线段树上**的叶子节点$x$，我们找到它在**原树上**对应的节点$p$。显然，它连向了很多节点。**对于$p$的父亲和重儿子，它们处于同一条重链中，故不需要考虑**。因此我们只需要考虑轻儿子即可。设该轻儿子为$q$。

显然，**一个轻儿子，必然是一条重链的链头**。所以，$p$所在重链的线段树根的$lmx$，便是$q$子树中最长的一条路径——**这和我们在淀粉质时维护的$self$数据结构的意义相同**！因此，我们可以直接将$lmx$加上$1$（在有边权时即为$p$到$q$的边权）后，扔进一个堆里面，设为$hp_p$。

如果$x$是白点，它自身应该也算进去，故再往堆里扔一个$0$。

$x$（线段树上节点）的$lmx$应与$rmx$相等，都等于$hp$的堆顶；$mx$则等于堆中最大与次大值拼一起。如果找不到这样的堆顶或是次大值，对应赋成$-\infty$即可。

我们这时便看出对于重链分开建树的好处了——**一条重链要想建树，它所有的儿子链必须全部建好，因为要利用里面的$lmx$赋给叶节点**。所以我们不得不分开建树。

则答案即为全部重链的$mx$的最大值，我们可以仍使用一个名叫$globe$的堆维护，这里不再赘述。

最后是修改。显然，对于节点本身，只不过是往$hp_x$中加入或删除$0$罢了。但是，对于节点本身的修改会**影响到整条重链的值**，然后重链的修改又会影响到**重链链顶的父亲**……

因此我们需要不断跳链并修改线段树的值。

复杂度$O(n\log^2n)$，其中一个$\log$来自于树剖，另一个来自于线段树/堆。

因为常数较小（线段树跑不满），可以通过。

代码（无边权，AC）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mid ((l+r)>>1)
struct Insert_And_Delete_Heap{
	priority_queue<int>all,era;
	int Size(){
		return all.size()-era.size();
	}
	void Insert(int x){all.push(x);}
	void Delete(int x){if(all.top()==x)all.pop();else era.push(x);}
	void Flush(){while(!all.empty()&&!era.empty()&&all.top()==era.top())all.pop(),era.pop();}
	int Top(){if(Size()<1)return -0x3f3f3f3f;Flush();return all.top();}
	int Calc(){
		if(Size()==1&&Top()==0)return 0;
		if(Size()<2)return -0x3f3f3f3f;
		int x=Top();
		all.pop();
		int y=Top();
		Insert(x);
		return x+y;
	}
//	void Print(){
//		vector<int>v;
//		Flush();
//		while(!all.empty())v.push_back(all.top()),all.pop(),Flush();
//		for(auto x:v)printf("%d ",x);puts("");
//		while(!v.empty())Insert(v.back()),v.pop_back();
//	}
}hp[100100],globe;
int n,m,sz[100100],son[100100],fa[100100],top[100100],dfn[100100],rev[100100],tot,rt[100100],cnt,chsz[100100];
bool col[100100];
vector<int>v[100100];
struct node{
	int lson,rson,lmx,rmx,mx;
}seg[400100];
void pushup(int x,int l,int r){
	seg[x].mx=max(max(seg[seg[x].lson].mx,seg[seg[x].rson].mx),seg[seg[x].lson].rmx+1+seg[seg[x].rson].lmx);
	seg[x].lmx=max(seg[seg[x].lson].lmx,seg[seg[x].rson].lmx+(mid-l+1));//directly from lson, or rson's top enlarging through the whole lson
	seg[x].rmx=max(seg[seg[x].rson].rmx,seg[seg[x].lson].rmx+(r-mid));//likelywise.
}
void build(int &x,int l,int r){
	if(!x)x=++cnt;
	if(l==r){
		int p=dfn[l];
		for(auto q:v[p]){
			if(q==fa[p]||q==son[p])continue;//q must be the top of a heavy chain
			hp[p].Insert(seg[rt[top[q]]].lmx+1);
		}
		hp[p].Insert(0);
		seg[x].lmx=seg[x].rmx=hp[p].Top(),seg[x].mx=hp[p].Calc();
		return;
	}
	build(seg[x].lson,l,mid),build(seg[x].rson,mid+1,r),pushup(x,l,r);
}
void refresh(int &x,int l,int r,int P){
	if(l>P||r<P)return;
	if(!x)x=++cnt;
	if(l==r){
		int p=dfn[l];
		seg[x].lmx=seg[x].rmx=hp[p].Top(),seg[x].mx=hp[p].Calc();
		return;
	}
	refresh(seg[x].lson,l,mid,P),refresh(seg[x].rson,mid+1,r,P),pushup(x,l,r);
}
void dfs1(int x,int FA){
	fa[x]=FA,sz[x]=1;
	for(auto y:v[x]){
		if(y==FA)continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[son[x]]<sz[y])son[x]=y;
	}
}
void dfs2(int x){
	if(son[x]){
		dfn[++tot]=son[x],rev[son[x]]=tot,top[son[x]]=top[x],chsz[top[x]]++;
		dfs2(son[x]);
	}
	for(auto y:v[x]){
		if(y==fa[x]||y==son[x])continue;
		dfn[++tot]=y,rev[y]=tot,top[y]=y,chsz[top[y]]++;
		dfs2(y);
	}
	if(top[x]==x)build(rt[x],rev[x],rev[x]+chsz[x]-1),globe.Insert(seg[rt[x]].mx);
}
void change(int x){
	if(!col[x])hp[x].Delete(0);
	else hp[x].Insert(0);
	col[x]^=1;
	while(x){
		if(fa[top[x]])hp[fa[top[x]]].Delete(seg[rt[top[x]]].lmx+1);
		globe.Delete(seg[rt[top[x]]].mx);
		refresh(rt[top[x]],rev[top[x]],rev[top[x]]+chsz[top[x]]-1,rev[x]);
		globe.Insert(seg[rt[top[x]]].mx);
		if(fa[top[x]])hp[fa[top[x]]].Insert(seg[rt[top[x]]].lmx+1);
		x=fa[top[x]];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
	dfs1(1,0),dfn[1]=rev[1]=top[1]=tot=chsz[1]=1,dfs2(1),scanf("%d",&m);
//	for(int x=1;x<=n;x++)printf("%d::FA:%d SN:%d SZ:%d DF:%d RV:%d TP:%d CZ:%d\n",x,fa[x],son[x],sz[x],dfn[x],rev[x],top[x],chsz[x]);
	for(int i=1,x;i<=m;i++){
		char s[10];
		scanf("%s",s);
		if(s[0]=='C')scanf("%d",&x),change(x);
		else printf("%d\n",max(globe.Top(),-1));
	}
	return 0;
}
```

------------

法五：LCT（理论正解II）

树剖和LCT各有利弊。比如这题，树剖的思路就要比LCT简单——毕竟LCT在```pushup```时是左儿子，自己，右儿子三部分合并，而树剖就只有左右儿子。另外，树剖的左右儿子是真正的左右儿子（原树上的），而LCT的左右儿子不一定是真正的左右儿子，这就使得写起来比较恶心。

首先，这题因为不需要连边删边，所以LCT就可以写**定根LCT**，即**不支持```makeroot```操作的LCT**。我们固定根为$1$，然后将边权下放到点权。则有无边权的区别仅仅在于点权不同。我们令$val$表示点权。

与树剖类似，我们令一个$up$表示LCT的链顶（即最左端的点）到白点的最远距离，再令一个$dn$表示链底（最右端的点）到白点的最远距离。显然，这两者可以使用与树剖类似的方法```pushup```出来。但是，因为LCT的子树大小不固定，我们需要令一个$sum$表示子树大小，即$\sum val$。

显然，这题需要应用到**虚子树**的trick。我们用一个名叫$isup$的堆维护所有虚儿子距离白点的最远距离（即虚儿子的$up$）。这时，我们就可以令一个$mx$表示**子树（包括虚子树和实子树）中的最长路径**，再令一个叫做$ismx$的堆维护所有虚儿子的$mx$。

则$mx$可以：

1. 从某个儿子转移过来（左儿子/右儿子/虚儿子）

2. 由两条路径拼一起（左儿子的$dn$/右儿子的$up$/$isup$的堆顶），当然也有可能两条全部来自$isup$。

这个代码比较别扭，加上蹩脚的英文注释后放出来：

```cpp
void pushup(int x){
	int im=t[x].isup.Top();//the maximum route on the imagined subtree
	if(!col[x])im=max(im,0);//count x itself in
	int lsmx=max(im,t[lson].dn+t[x].val),rsmx=max(im,t[rson].up)+t[x].val;//as the value of the edge is stored on nodes, transferring from father to son need to add val[x],while vice visa doesn't
	t[x].up=max(t[lson].up,rsmx+t[lson].sum);
	t[x].dn=max(t[rson].dn,lsmx+t[rson].sum);
	t[x].mx=max({
		t[lson].mx,
		t[rson].mx,//answer from the two real sons
		t[lson].dn+rsmx,
		t[rson].up+lsmx,//merge one route from a real son with another route from the other real son or imagined sons
		t[x].ismx.Top(),//answer from the imagined subtree
		t[x].isup.Calc()//two imagined sons' routes merge together
	});
	if(!col[x])t[x].mx=max(t[x].mx,max(t[x].isup.Top(),0));
	t[x].sum=t[lson].sum+t[x].val+t[rson].sum;
}
```
白点和黑点的区别就在于那两处特判——它算入了$x$自己。

总复杂度为$O(n\log^2n)$（LCT是$n\log n$的，因为splay的复杂度可以被均摊证明出来；但是这里不仅有splay，还有堆，但是堆是均摊不了的，因此总复杂度为$O(n\log^2n)$）。因为实现时没注意常数，所以TLE90。

代码（无边权，TLE）：

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define lson t[x].ch[0]
#define rson t[x].ch[1]
int n,m,res;
bool col[100100];
struct Insert_And_Delete_Heap{
	priority_queue<int>all,era;
	int Size(){
		return all.size()-era.size();
	}
	void Insert(int x){all.push(x);}
	void Delete(int x){if(all.top()==x)all.pop();else era.push(x);}
	void Flush(){while(!all.empty()&&!era.empty()&&all.top()==era.top())all.pop(),era.pop();}
	int Top(){if(Size()<1)return -0x3f3f3f3f;Flush();return all.top();}
	int Calc(){
		if(Size()<2)return -0x3f3f3f3f;
		int x=Top();
		all.pop();
		int y=Top();
		Insert(x);
		return x+y;
	}
//	void Print(){
//		vector<int>v;
//		Flush();
//		while(!all.empty())v.push_back(all.top()),all.pop(),Flush();
//		for(auto x:v)printf("%d ",x);puts("");
//		while(!v.empty())Insert(v.back()),v.pop_back();
//	}
};
struct LCT{
	int ch[2],mx,dn,up,fa,sum,val;//up:the top of the chain's maximum distance towards an offed room; dn: that of the bottom of the chain; mx: the maximum distance between any two offed rooms inside the subtree
	Insert_And_Delete_Heap ismx,isup;
}t[100100];
int identify(int x){
	if(x==t[t[x].fa].ch[0])return 0;
	if(x==t[t[x].fa].ch[1])return 1;
	return -1;
}
void pushup(int x){
	int im=t[x].isup.Top();//the maximum route on the imagined subtree
	if(!col[x])im=max(im,0);//count x itself in
	int lsmx=max(im,t[lson].dn+t[x].val),rsmx=max(im,t[rson].up)+t[x].val;//as the value of the edge is stored on nodes, transferring from father to son need to add val[x],while vice visa doesn't
	t[x].up=max(t[lson].up,rsmx+t[lson].sum);
	t[x].dn=max(t[rson].dn,lsmx+t[rson].sum);
	t[x].mx=max({
		t[lson].mx,
		t[rson].mx,//answer from the two real sons
		t[lson].dn+rsmx,
		t[rson].up+lsmx,//merge one route from a real son with another route from the other real son or imagined sons
		t[x].ismx.Top(),//answer from the imagined subtree
		t[x].isup.Calc()//two imagined sons' routes merge together
	});
	if(!col[x])t[x].mx=max(t[x].mx,max(t[x].isup.Top(),0));
	t[x].sum=t[lson].sum+t[x].val+t[rson].sum;
}
void rotate(int x){
	int y=t[x].fa;
	int z=t[y].fa;
	int dirx=identify(x);
	int diry=identify(y);
	int b=t[x].ch[!dirx];
	if(diry!=-1)t[z].ch[diry]=x;t[x].fa=z;
	if(b)t[b].fa=y;t[y].ch[dirx]=b;
	t[y].fa=x,t[x].ch[!dirx]=y;
	pushup(y),pushup(x);
}
void splay(int x){
	while(identify(x)!=-1){
		int fa=t[x].fa;
		if(identify(fa)==-1)rotate(x);
		else if(identify(x)==identify(fa))rotate(fa),rotate(x);
		else rotate(x),rotate(x);
	}
}
void access(int x){
	for(int y=0;x;x=t[y=x].fa){
		splay(x);
		if(rson)t[x].ismx.Insert(t[rson].mx),t[x].isup.Insert(t[rson].up);
		rson=y;
		if(y)t[x].ismx.Delete(t[y].mx),t[x].isup.Delete(t[y].up);
		pushup(x);
	}
}
vector<int>v[100100];
void dfs(int x,int fa){
	t[x].fa=fa;
	for(auto y:v[x]){
		if(y==fa)continue;
		t[y].val=t[y].sum=1;
		dfs(y,x);
		t[x].ismx.Insert(t[y].mx),t[x].isup.Insert(t[y].up);
	}
	pushup(x);
}
void read(int &x){
	x=0;
	char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
}
int main(){
	read(n);
	for(int i=0;i<=n;i++)t[i].mx=t[i].dn=t[i].up=-0x3f3f3f3f;
	for(int i=1,x,y;i<n;i++)read(x),read(y),v[x].push_back(y),v[y].push_back(x);
	dfs(1,0),res=t[1].mx;
	read(m);
	for(int i=1,x;i<=m;i++){
		char s[10];
		scanf("%s",s);
		if(s[0]=='C')read(x),access(x),splay(x),col[x]^=1,pushup(x),res=t[x].mx;
		else printf("%d\n",max(-1,res));
	}
	return 0;
}
```

------------

作为一道经典的例题，本题有五种解法并不稀奇。还是希望大家能够在平时做题中拓宽思路，多想几种解法。

~~才不会告诉你是因为我一开始看不懂动态淀粉质的做法然后不得不寻找其他解法的~~

~~这篇题解一共写了31K，看在这么多字的份上，点个赞吧~~


---

## 作者：bztMinamoto (赞：19)

打个广告：[blog](https://www.cnblogs.com/bztMinamoto/p/9426822.html)

似乎没人写LCT的……明明跑的挺快的……来一发好了……

本来打算用捉迷藏一样做的……但发现我那一道写的时候是用括号表示做的……这题有边权不能做……楼下那位用边分和点分的好强……

~~我已经想到了一个很好的LCT的思路，可惜这里空白太小写不下~~

说下思路吧

LCT只能维护点权，但本题中是边权

我们可以指定一个根（比如1），然后令所有的边权变成它指向的儿子的点权，记为$len$

ps：这样做之后会有很多细节，需要一一注意

然后在考虑一下如何求出两个相邻最远的白点的距离呢？

因为LCT上面有实边和虚边，所以实儿子和虚儿子的信息要用不同的方法维护

实边构成了一个splay，我们定义几个数组，$lmx$表示splay中深度最浅的点能够到达的最远的白点的距离，$rmx$表示splay中深度最深的点能够到达的最远的白点的距离，$mxs$表示splay中距离最远的两个白点的距离，也就是答案，$sum$表示整棵splay的长度和

ps：LCT中的splay在原树中是一条链！所以$sum$维护的是整条链的长度和，同理$lmx$表示这条链的顶端距离白点的最远距离，$rmx$表示这条链的底端距离白点的最远距离

虚儿子的信息怎么维护？虚儿子我们需要记录的只有到白点的最远距离，以及虚儿子中的$mxs$，直接开两个$set$丢进去就好了

那么，这些信息够了吗？

当然已经够了，因为已经足够将信息不断向上传递了

先考虑一下虚子树对$mxs$的影响，实边太复杂了待会儿再说

因为在$access$的时候，会有换边的操作

对于由实变虚的原右儿子，把$mx[rs]$丢进路径的$set$里，把$lx[rs]$丢进链的$set$里

同理，把由虚变实的新右儿子$mx[y]$和$lx[y]$从对应的$set$里删除就行

$mx$丢进去我们可以理解，因为要维护答案，但为什么链的长度只要把$lx$丢进$set$就行了呢？

考虑一下，$set$里维护的是这一个顶点到其虚子树中的白点的最大距离，而$lx[rs]$代表的是$x$的右子树中深度最浅的点到白点的最大距离，如果回到原树上，这就是$x$的儿子到白点的最大距离！！又因为我们将边权给了儿子，所以，只需要记录虚边的$ls$即可

然后期待已久（写到吐血）pushup操作了

这部分还是具体看代码好了……细节太多了……我这里简单提几嘴

$lmx$要过子树的最低点，所以等于$max(lmx[ls],max(虚链中最长+整个左子树，右子树中最长+整个左子树))$

$rmx$同理

然后$mxs$就是把所有可能的链给接起来以及子树的答案都弄出来更新就好了

ps：如果$x$也是白点，他自己也得拿出来更新$mxs$

时间复杂度$O(n log^2 n)$

然而如果$set$的$size$大说明虚边多，深度不大，LCT操作次数少一点

如果树的深度深，$set$的$size$又不会太大，所以时间复杂度不是很严格

ps：请务必详细看看注解，这题细节多的要命
```
//minamoto
#include<bits/stdc++.h>
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while((ch=getc())<'0'||ch>'9')
    (ch=='-')&&(flag=true);
    for(res=num;(ch=getc())>='0'&&ch<='9';res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=200005,inf=0x3f3f3f3f;
int n,ver[N],Next[N],head[N],edge[N],tot,ans=-inf,col[N];
inline void add(int u,int v,int e){ver[++tot]=v,Next[tot]=head[u],head[u]=tot,edge[tot]=e;}
inline int fir(multiset<int> &s){return s.size()?*s.rbegin():-inf;}
inline int sec(multiset<int> &s){return s.size()>1?*(++s.rbegin()):-inf;}
/*分别是查询set里的最大和次大*/
#define ls ch[x][0]
#define rs ch[x][1]
int ch[N][2],fa[N],lmx[N],rmx[N],mxs[N],sum[N],len[N],w[N];
/*w表示这个点是否是白点，如果是赋值为0，否则赋值为-inf*/ 
multiset<int> chain[N],path[N];
/*chain存链长，path存路径长*/
inline bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
void init(){for(int i=0;i<=n;++i) lmx[i]=rmx[i]=mxs[i]=-inf;}
void pushup(int x){
    sum[x]=sum[ls]+sum[rs]+len[x];
    /*sum表示整棵splay的长度和*/ 
    int cha=max(w[x],fir(chain[x]));
    /*找最远的虚边上的白点的距离*/ 
    int L=max(cha,rmx[ls]+len[x]);
    /*向左子树或向虚边最远能走多远
	ps：这里len要加上去，因为左子树在原树中是x的祖先
	要加上x到父亲的距离（已经被转化为点权了）*/
    int R=max(cha,lmx[rs]);
    /*向右子树或向虚边最远能走多远*/
    lmx[x]=max(lmx[ls],sum[ls]+len[x]+R);
    /*不经过x，或经过x并走到最远
	注意左子树在原树中是一条链！不存在路径重叠问题*/
    rmx[x]=max(rmx[rs],sum[rs]+L);
    /*同理*/ 
    mxs[x]=max(rmx[ls]+len[x]+R,lmx[rs]+L);
    cmax(mxs[x],max(mxs[ls],mxs[rs]));
    cmax(mxs[x],fir(path[x]));
    cmax(mxs[x],fir(chain[x])+sec(chain[x]));
    /*最长链和次长链可以形成一条路径*/ 
    if(w[x]==0) cmax(mxs[x],max(fir(chain[x]),0));
    /*用一堆东西来更新答案*/
}
void rotate(int x){
    int y=fa[x],z=fa[y],d=ch[y][1]==x;
    if(!isroot(y)) ch[z][ch[z][1]==y]=x;
    fa[x]=z,fa[y]=x,fa[ch[x][d^1]]=y,ch[y][d]=ch[x][d^1],ch[x][d^1]=y,pushup(y);
}
void splay(int x){
    for(int y=fa[x],z=fa[y];!isroot(x);y=fa[x],z=fa[y]){
        if(!isroot(y))
        ((ch[y][1]==x)^(ch[z][1]==y))?rotate(x):rotate(y);
        rotate(x);
    }
    pushup(x);
}
void access(int x){
    for(int y=0;x;x=fa[y=x]){
        splay(x);
        if(rs) path[x].insert(mxs[rs]),chain[x].insert(lmx[rs]);
        if(y) path[x].erase(path[x].find(mxs[y])),chain[x].erase(chain[x].find(lmx[y]));
        rs=y,pushup(x);
        /*注意虚实子树变换时要更新path和chain*/
    }
}
void modify(int x){
	/*改变点的颜色，col为1表示黑，0表示白*/
    access(x),splay(x);
    col[x]^=1,w[x]=col[x]?(-inf):0;
    pushup(x),ans=mxs[x];
}
void dfs(int u){
    for(int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if(v==fa[u]) continue;
        fa[v]=u,len[v]=edge[i],dfs(v);
        /*把边的权值给儿子*/
        chain[u].insert(lmx[v]),path[u].insert(mxs[v]);
    }
    pushup(u);
}
int main(){
    //freopen("testdata.in","r",stdin);
    n=read();init();
    for(int i=1;i<n;++i){
        int u=read(),v=read(),e=read();
        add(u,v,e),add(v,u,e);
    }
    dfs(1),ans=mxs[1];int q=read();
    while(q--){
        char op=getc();int x;
        getc();
        if(op=='A'){
            ans<0?puts("They have disappeared."):printf("%d\n",ans);
        }
        else x=read(),modify(x);
    }
    return 0;
}
```

---

## 作者：KSkun (赞：12)

本题解同步发布在我的博客：[[SPOJ-QTREE4]Query on a tree IV 题解 | KSkun's Blog](https://ksmeow.moe/qtree4_spoj_sol/)
# 题解
本题也可以用点分治的做法解决，做法类似[【P2056】[ZJOI2007]捉迷藏 - 洛谷](https://www.luogu.org/problemnew/show/P2056)一题。这里只介绍边分治的做法。

我们在中心边位置维护两个堆，一个表示左边子树的各个白点距离，一个表示右边子树的。单独维护每个分治结构的答案，我们可以在一个统计最大值的时候顺带把子分治结构的最大值也计算进来，这样询问的时候只需要询问根分支结构的答案即可。在加点的的过程中，记录下这个点会影响到的堆的数据。变白要把这个点放进堆里，变黑只需要打标记。而每一次更新答案的时候，从堆顶把黑点全扔掉就好。如果用数组/vector来存的话，这个更新要根据倒序，因此倒序才是分治结构从底向根的顺序。

# 代码
```cpp
// Code by KSkun, 2018/3
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>
#include <queue>

typedef long long LL;

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline LL readint() {
	register LL res = 0, neg = 1;
	register char c = fgc();
	while(c < '0' || c > '9') {
		if(c == '-') neg = -1;
		c = fgc();
	}
	while(c >= '0' && c <= '9') {
		res = res * 10 + c - '0';
		c = fgc();
	}
	return res * neg;
}

inline bool isop(char c) {
	return c == 'A' || c == 'C';
}

inline char readop() {
	char c;
	while(!isop(c = fgc()));
	return c;
}

const int MAXN = 200005, INF = 2e9;

int n, q, col[MAXN], ans;

struct Edge {
	int to, w, nxt;
} gra[MAXN << 1], grao[MAXN << 1];
int head[MAXN], heado[MAXN], ecnt, ecnto;

inline void addedge(int u, int v, int w) {
	gra[ecnt] = Edge {v, w, head[u]}; head[u] = ecnt++;
}

inline void addedgeo(int u, int v, int w) {
	grao[ecnto] = Edge {v, w, heado[u]}; heado[u] = ecnto++;
}

// 重构树，使得树的结构有利于边分治
inline void rebuild(int u, int fa) {
	int ff = 0;
	for(int i = heado[u]; ~i; i = grao[i].nxt) {
		int v = grao[i].to, w = grao[i].w;
		if(v == fa) continue;
		if(!ff) {
			addedge(u, v, w);
			addedge(v, u, w);
			ff = u;
		} else {
			int k = ++n;
			col[k] = 1;
			addedge(ff, k, 0);
			addedge(k, ff, 0);
			addedge(k, v, w);
			addedge(v, k, w);
			ff = k;
		}
		rebuild(v, u);
	}
}

bool del[MAXN << 1];
int ct, ctsiz, sum;
int siz[MAXN], msz[MAXN];

// 计算子树大小
inline void calsiz(int u, int fa) {
	siz[u] = 1;
	for(int i = head[u]; ~i; i = gra[i].nxt) {
		int v = gra[i].to;
		if(del[i >> 1] || v == fa) continue;
		calsiz(v, u);
		siz[u] += siz[v];
	}
}

// 找到子树的中心边
inline void findct(int u, int fa) {
	for(int i = head[u]; ~i; i = gra[i].nxt) {
		int v = gra[i].to;
		if(del[i >> 1] || v == fa) continue;
		findct(v, u);
		int vsiz = std::max(siz[v], sum - siz[v]);
		if(vsiz < ctsiz) {
			ct = i;
			ctsiz = vsiz;
		}
	}
}

struct DisData {
	int u, d; // 节点，节点到根的距离
	inline bool operator<(const DisData &rhs) const {
		return d < rhs.d;
	}
};

std::priority_queue<DisData> s[MAXN][2];
int cnt;

struct NodeData {
	int bel, side, dis; // 子分治结构的编号，中心边的左侧或右侧，到根的距离
};
std::vector<NodeData> ndata[MAXN];

// 把整棵子树的点到根的距离全部求出来，并记下每个点都属于哪些子树
inline void caldis(int u, int fa, int d, int t, int l) {
	if(!col[u]) {
		s[t][l].push(DisData {u, d}); ndata[u].push_back(NodeData {t, l, d});
	}
	for(int i = head[u]; ~i; i = gra[i].nxt) {
		int v = gra[i].to, w = gra[i].w;
		if(del[i >> 1] || v == fa) continue;
		caldis(v, u, d + w, t, l);
	}
}

int mx[MAXN], lch[MAXN], rch[MAXN], ctw[MAXN];

// 用于更新某个中心边的信息
inline void update(int p) {
	while(!s[p][0].empty() && col[s[p][0].top().u]) s[p][0].pop();
	while(!s[p][1].empty() && col[s[p][1].top().u]) s[p][1].pop();
	if(s[p][0].empty() || s[p][1].empty()) mx[p] = 0;
	else mx[p] = s[p][0].top().d + ctw[p] + s[p][1].top().d; // 统计经过中心边的路径最大值
    // 统计子分治结构的最大值
	if(lch[p]) mx[p] = std::max(mx[p], mx[lch[p]]);
	if(rch[p]) mx[p] = std::max(mx[p], mx[rch[p]]);
}

// 边分的divide函数
inline int divide(int u) {
	calsiz(u, 0);
	ct = -1; ctsiz = INF; sum = siz[u]; findct(u, 0);
	if(ct == -1) return 0;
	int x = gra[ct].to, y = gra[ct ^ 1].to;
	del[ct >> 1] = true; // 要先删边再递归
	int t = ++cnt;
	ctw[t] = gra[ct].w;
    // 递归解决子分治结构问题
	caldis(x, 0, 0, t, 0); caldis(y, 0, 0, t, 1);
	lch[t] = divide(x); rch[t] = divide(y); 
    // 合并答案
	update(t);
	return t;
}

// 设为白点，需要把这个点的距离信息加入它属于的所有子分治结构中
inline void setwhite(int u) {
	for(int i = ndata[u].size() - 1; i >= 0; i--) {
		NodeData d = ndata[u][i];
		s[d.bel][d.side].push(DisData {u, d.dis});
		update(d.bel);
	}
}

// 设为黑点，需要把这个点的距离信息从它属于的所有子分治结构中删除
inline void setblack(int u) {
	for(int i = ndata[u].size() - 1; i >= 0; i--) {
		NodeData d = ndata[u][i];
		update(d.bel);
	}
}

int ut, vt, wt;
char op;

int main() {
	memset(head, -1, sizeof(head));
	memset(heado, -1, sizeof(heado));
	n = readint();
	int white = n;
	for(int i = 1; i < n; i++) {
		ut = readint(); vt = readint(); wt = readint();
		addedgeo(ut, vt, wt);
		addedgeo(vt, ut, wt);
	}
	rebuild(1, 0);
	divide(1);
	q = readint();
	while(q--) {
		op = readop();
		if(op == 'A') {
			if(!white) {
				puts("They have disappeared.");
			} else if(white == 1) {
				puts("0");
			} else {
				printf("%d\n", mx[1]);
			}
		} else {
			ut = readint(); 
			col[ut] ^= 1;
			if(col[ut]) {
				setblack(ut);
				white--;
			} else {
				setwhite(ut);
				white++;
			}
		}
	}
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：4)

目前唯一能过的动态点分治题解。

在点分树的每个点上维护 $C_u$ 表示 $u$ 子树内的点到 $fa_u$ 的距离集合，

$P_u$ 表示 $u$ 到其每个子树的距离最大值集合。特别地，若 $u$ 是白点，还要在 $P_u$ 中加入 $0$，

即 $P_u=\begin{cases}\{\max\{C_v\}|fa_v=u\}&u\text{ 是黑点}\\\{\max\{C_v\}|fa_v=u\}\cup\{0\}&u\text{ 是白点}\end{cases}$。

维护 $S$ 表示以每个点为 LCA 的最长路径长度集合，即 $S=\{\max\{P_u\}+\operatorname{secondmax}\{P_u\}\}$。

反转点 $u$ 的颜色时更新 $u$ 到根上的 $C_i$，用 $C_i$ 更新 $P_{fa_i}$，用 $P_{fa_i}$ 更新 $S$。

一共要更新 $O(\log n)$ 个 集合，用 `multiset` 维护这些集合，总复杂度 $O(m\log^2n)$。

然后你就会发现这东西常数太大很难过题，所以用可删堆代替 `multiset`。

具体地，维护原堆 $S$ 和删除堆 $D$，删除 $x$ 时在 $D$ 中加入 $x$，

查询堆顶时若两堆堆顶相同就一直弹出两堆堆顶，直到两堆堆顶不同时输出 $S$ 的堆顶即可。

这样如果写的好的话可以直接过，写的不好也能过掉 P2056 和 P4115 了。

发现求原树两点距离比较频繁，用欧拉序求 LCA 可以显著减小常数。

发现用 $C_i$ 更新 $P_{fa_i}$，用 $P_{fa_i}$ 更新 $S$ 这一步，$P_{fa_i}$ 和 $S$ 很多情况下不会发生变化，所以判一下需不需要更新。

然后可能还有概率过不去，加火车头或者加 fread/fwrite 快读快写都可以稳过。

```cpp
#include <queue>
#include <cstdio>
using namespace std;
struct E
{
    int v, w, t;
} e[200050];
struct multiset
{
    priority_queue<int> S, D;
    int R() { return S.size() - D.size(); }
    void I(int x) { S.push(x); }
    void O(int x) { D.push(x); }
    int T()
    {
        if (!R())
            return 1e9;
        while (D.size() && S.top() == D.top())
            S.pop(), D.pop();
        return S.top();
    }
    int C()
    {
        if (R() < 2)
            return 1e9;
        int x = T(), y;
        O(x);
        y = T();
        I(x);
        return x + y;
    }
} S, C[100050], P[100050];
bool b[100050];
char V;
int n, m, c, R, pR, z, o, a[100050], s[100050], g[100050], d[100050], k[100050], f[32][200050], H[100050], h[100050];
void A(int u, int v, int w)
{
    e[++c] = {v, w, h[u]};
    h[u] = c;
}
void D(int u)
{
    ++o;
    k[f[0][o] = u] = o;
    for (int i = h[u], v; i; i = e[i].t)
        if (!d[v = e[i].v])
        {
            d[v] = d[u] + 1;
            H[v] = H[u] + e[i].w;
            D(v);
            f[0][++o] = u;
        }
}
int L(int x, int y)
{
    if ((x = k[x]) > (y = k[y]))
        swap(x, y);
    int k = __lg(y - x + 1);
    return d[f[k][x]] < d[f[k][y - (1 << k) + 1]] ? f[k][x] : f[k][y - (1 << k) + 1];
}
int D(int x, int y) { return H[x] + H[y] - (H[L(x, y)] << 1); }
void X(int u, int k, int t)
{
    s[u] = 1;
    int p = 0;
    for (int i = h[u], v; i; i = e[i].t)
        if (!b[v = e[i].v] && v != k)
            X(v, u, t), s[u] += s[v], p = max(p, s[v]);
    if (pR > (p = max(p, t - s[u])))
        R = u, pR = p;
}
void B(int u, int k)
{
    b[u] = 1;
    for (int i = h[u], v; i; i = e[i].t)
        if (!b[v = e[i].v] && v != k)
            pR = 1e9, X(v, u, s[v]), X(R, 0, s[v]), B(R, g[R] = u);
}
int main()
{
    S.I(0);
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; ++i)
        scanf("%d%d%d", &u, &v, &w), A(u, v, w), A(v, u, w);
    D(d[1] = 1);
    for (int i = 1; 1 << i <= o; ++i)
        for (int j = 1; j + (1 << i) - 1 <= o; ++j)
            f[i][j] = d[f[i - 1][j]] < d[f[i - 1][j + (1 << i - 1)]] ? f[i - 1][j] : f[i - 1][j + (1 << i - 1)];
    pR = 1e9;
    X(1, 0, n);
    X(R, 0, n);
    B(R, 0);
    for (int i = 1; i <= n; ++i)
    {
        for (int u = i; u; u = g[u])
            if (g[u])
                C[u].I(D(g[u], i));
        P[i].I(0);
    }
    for (int i = 1; i <= n; ++i)
        if (g[i])
            P[g[i]].I(C[i].T());
    for (int i = 1; i <= n; ++i)
        if (P[i].R() >= 2)
            S.I(P[i].C());
    scanf("%d", &m);
    z = n;
    for (int i = 0, x, p, q; i < m; ++i)
    {
        scanf(" %c", &V);
        if (V == 'C')
        {
            scanf("%d", &x);
            p = P[x].C();
            if (a[x])
                P[x].I(0);
            else
                P[x].O(0);
            q = P[x].C();
            if (p != q)
            {
                if (p != 1e9)
                    S.O(p);
                if (q != 1e9)
                    S.I(q);
            }
            for (int u = x, o, p, q, c, d; u; u = g[u])
                if (g[u])
                {
                    o = D(g[u], x);
                    c = P[g[u]].C();
                    p = C[u].T();
                    if (a[x])
                        C[u].I(o);
                    else
                        C[u].O(o);
                    q = C[u].T();
                    if (p != q)
                    {
                        if (p != 1e9)
                            P[g[u]].O(p);
                        if (q != 1e9)
                            P[g[u]].I(q);
                    }
                    d = P[g[u]].C();
                    if (c != d)
                    {
                        if (c != 1e9)
                            S.O(c);
                        if (d != 1e9)
                            S.I(d);
                    }
                }
            z += a[x];
            z -= a[x] ^= 1;
        }
        else if (!z)
            puts("They have disappeared.");
        else if (z == 1)
            puts("0");
        else
            printf("%d\n", S.T());
    }
    return 0;
}
```


---

## 作者：Acee (赞：4)

~~点分治应该都会了吧，我就不写了。~~

### 长链剖分

我们将原树剖作很多重链，并在每条重链上各建一颗线段树，而不是整体建一棵线段树。

我们规定对于一条重链上的一条子链，其左端点为这条子链上 $dfn$ 最小的点，右端点为这条子链上 $\text{dfn}$ 最大的点。

对于线段树上一个节点，维护：

$\text{LmaxDis}$，表示区间左端点所能到达最远的白点的距离。

$\text{RmaxDis}$，表示区间右端点所能到达最远的白点的距离。

$\text{MaxDis}$，表示任意两个 LCA 在区间中的白点（这两个点并不一定在区间内）间的最大距离。

`pushup` 就可以这样写:

```cpp
void pushup(int p, int l, int r) {
	int mid = (l + r) >> 1;
	t[p].lmax = max(t[t[p].ls].lmax, dep[dfn[mid + 1]] - dep[dfn[l]] + t[t[p].rs].lmax);
	t[p].rmax = max(t[t[p].rs].rmax, dep[dfn[r]] - dep[dfn[mid]] + t[t[p].ls].rmax);
	t[p].maxx = max(max(t[t[p].ls].maxx, t[t[p].rs].maxx), t[t[p].ls].rmax + t[t[p].rs].lmax + dep[dfn[mid + 1]] - dep[dfn[mid]]);
}
```

跟最大子段和比较类似。

再对于每个点 $x$ 都用一个数据结构维护 $x$ 向下第一步不走重边能到的所有白点的极大距离，可以使用 $lmax$ + 深度距离差来求。

这个数据结构需要支持插入、删除、求最大值，所以选择堆。

线段树维护好了。

然后在考虑修改。设修改点为 $x$，先修改它所在的链上，再一直向上跳更新。

我们用一个大根堆 $heapans$ 维护每条重链线段树的 $MaxDis$，便可 $O(1)$ 查询。

代码：

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
namespace Main {
	const int N = 100000 + 5; 
	int n, m;
	struct edge {
		int nxt, to, val;
	} e[N * 2];
	int col[N];
	int h[N], num;
	void addedge(int x, int y, int z) {
		e[++num].nxt = h[x];
		e[num].to = y;
		e[num].val = z;
		h[x] = num;
	}
	
	int fa[N], top[N], son[N], dep[N];
	int len[N], cnt, sz[N];
	int id[N], dfn[N];
	
	void dfs1(int x, int f) {
		fa[x] = f;
		sz[x] = 1;
		for (int i = h[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if (y == f) continue;
			dep[y] = dep[x] + e[i].val;
			dfs1(y, x);
			sz[x] += sz[y];
			if (sz[y] > sz[son[x]]) son[x] = y;
		}
	}
	void dfs2(int x, int f) {
		top[x] = f;
		++len[top[x]];
		id[x] = ++cnt;
		dfn[cnt] = x;
		if (son[x]) dfs2(son[x], f);
		for (int i = h[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if (y == fa[x] || y == son[x]) continue;
			dfs2(y, y);
		}
	}
	struct Heap {
		multiset<int,greater<int> > s;
		void insert(int v) {
			s.insert(v);
		}
		void del(int v) {
			multiset<int, greater<int> > :: iterator it=s.lower_bound(v);
			if(it!=s.end()) s.erase(it);
		}
		int top() {
			if(s.empty()) return -0x3f3f3f3f;
			return *s.begin();
		}
	};
	Heap ans, stk[N];
	
	struct tree {
		int ls, rs;
		int maxx, lmax, rmax;
	} t[N << 2];
	int TreeCnt;
	int rt[N];
	void pushup(int p, int l, int r) {
		int mid = (l + r) >> 1;
		t[p].lmax = max(t[t[p].ls].lmax, dep[dfn[mid + 1]] - dep[dfn[l]] + t[t[p].rs].lmax);
		t[p].rmax = max(t[t[p].rs].rmax, dep[dfn[r]] - dep[dfn[mid]] + t[t[p].ls].rmax);
		t[p].maxx = max(max(t[t[p].ls].maxx, t[t[p].rs].maxx), t[t[p].ls].rmax + t[t[p].rs].lmax + dep[dfn[mid + 1]] - dep[dfn[mid]]);
	}
	void build(int p, int l, int r) {
		if (l == r) {
			int x = dfn[l];
			for (int i = h[x]; i; i = e[i].nxt) {
				int y = e[i].to;
				if (y == fa[x] || y == son[x]) continue;
				stk[x].insert(t[rt[y]].lmax + e[i].val);
			} 
		//	int jk = 0;
		//	while (stk[x].s.lower_bound(1) != stk[x].s.end()) ++jk, stk[x].s.erase(1);
		//	cout << "jk = " << jk << '\n';
			int max1 = stk[x].top();
			stk[x].del(max1);
			int max2 = stk[x].top();
			stk[x].insert(max1);
			t[p].lmax = t[p].rmax = max(max1, 0);
			t[p].maxx = max(0, max(max1, max1 + max2));
		//	cout << "#####" << max1 << ' ' << max2 << '\n';
			return;
		}
		int mid = (l + r) >> 1;
		if (!t[p].ls)t[p].ls = ++TreeCnt;
		build(t[p].ls, l, mid);
		if (!t[p].rs)t[p].rs = ++TreeCnt;
		build(t[p].rs, mid + 1, r);
		pushup(p, l, r);
	}
	void change(int p, int l, int r, int x, int y) {
		if (l == r) {
			if (x != y) stk[x].insert(t[rt[y]].lmax + dep[y] - dep[x]);
			int max1 = stk[x].top();
			stk[x].del(max1);
			int max2 = stk[x].top();
			stk[x].insert(max1);
			if (col[x]) {
				t[p].lmax = t[p].rmax = max1;
				t[p].maxx = max1 + max2;
			}
			else {
				t[p].lmax = t[p].rmax = max(max1, 0);
				t[p].maxx = max(0, max(max1, max1 + max2));
			}
			return;
		}
		int mid = (l + r) >> 1;
		if (id[x] <= mid) change(t[p].ls, l, mid, x, y);
		else change(t[p].rs, mid + 1, r, x, y);
		pushup(p, l, r); 
	}
	void update(int x) {
		int lst = x;
		while (x) {
			int top_max1 = t[rt[top[x]]].maxx;
			if (fa[top[x]]) {
				stk[fa[top[x]]].del(t[rt[top[x]]].lmax + dep[top[x]] - dep[fa[top[x]]]);
			}
			change(rt[top[x]], id[top[x]], id[top[x]] + len[top[x]] - 1, x, lst);
			int top_max2 = t[rt[top[x]]].maxx;
			//	cout << "Del = " << top_max2 <<'\n'; 
			if (top_max1 != top_max2) {
				ans.del(top_max1);
				ans.insert(top_max2);
			}
			lst = top[x];
			x = fa[top[x]];
		}
	}
	int main() {
		ios::sync_with_stdio(false);
		cin.tie(0), cout.tie(0);
		cin >> n;
		for (int i = 1, x, y, z; i < n; ++i) {
			cin >> x >> y >> z;
			addedge(x, y, z);
			addedge(y, x, z);
		}
		dfs1(1, 0);
		dfs2(1, 1);
//		return 0;
//		for (int i = 1; i <= n; ++i)	 {
//			cout << id[i] << '\n';
//		}
//		return 0;
		for (int i = n; i >= 1; --i) {
			int x = dfn[i];
			if (x == top[x]) {
				if (!rt[x]) rt[x] = ++TreeCnt;
				build(rt[x], id[x], id[x] + len[x] - 1);
				ans.insert(t[rt[x]].maxx);
			}
		} 
//		return 0;
		cin >> m;
		char op;
		int Cnt = n;
		for (int ti = 1, x; ti <= m; ++ti) {
			cin >> op;
			if (op == 'C') {
				cin >> x;
				col[x] ^= 1;
				if (col[x] == 0) ++Cnt;
				else --Cnt;
				update(x);
			}
			else {
				if (Cnt == 0) cout << "They have disappeared.\n";
				else cout << ans.top() << '\n';
			}
		}
		return 0;
	}
}
int main() {
	Main :: main();
	return 0;
}
```

---

## 作者：TBSF_0207 (赞：1)

# 全局平衡二叉树

本文可能较长，但请相信仅仅是因为较详细的缘故，而不是有多复杂。

这是一种（较）纯正的全局平衡二叉树解法。

刚学这个东西，这里主要借鉴了[hehezhou大佬的题解](https://www.luogu.com.cn/article/xz5zpquh)。该题解末尾提到，作者的全局平衡二叉树融入了**宗法树**的特征，即**数字都存储在叶子结点**里的一种类线段树。那么本篇题解将有所不同，提供一个较为普适的全局平衡二叉树写法，顺便详细展开一些自己关于该结构适用性与这题细节的一些想法（顺便修一下之前题解可能出现的一些笔误）。如有差错，敬请指出。

## 朴素解法

我们都知道（？）存在这么一种解法，对原树进行重链剖分，然后对每条重链维护一个线段树，每个点维护一个堆。线段树内由于是链状结构，可以直接对信息进行合并。堆维护的是每个节点到自己**轻子树**内所有节点的所有距离。这样每次修改需要向上跳 $O(\log n)$ 条链，线段树修改每次为 $O(\log n)$，每次对堆内（仅需修改每条链链顶的父亲）信息的修改为 $O(\log n)$，总共就是 $O(n\log^2 n)$ 的。

这里我们可以展开讲一下线段树的维护（可删堆就不讲了）。对于一个线段树上节点 $u$ 及其代表的区间 $[u_l,u_r]$，它的左儿子 $ls$，右儿子 $rs$，分别维护三个信息。

- $u_{lmax}$ 表示 $[u_l,u_r]$ 内白点到 $u_l$ 的最大距离。
- $u_{rmax}$ 表示 $[u_l,u_r]$ 内白点到 $u_r$ 的最大距离。
- $u_{ans}$ 表示 $[u_l,u_r]$ 内白点两两最大距离。

那么就有合并：

$$
\begin{aligned}
u_{lmax}&=\max\{ls_{lmax},dis(ls_l,rs_l)+rs_{lmax}\}
\\ u_{rmax}&=\max\{rs_{rmax},dis(ls_r,rs_r)+ls_{rmax}\}
\\ u_{ans}&=\max\{ls_{ans},rs_{ans},ls_{rmax}+rs_{lmax}+dis(ls_r,rs_l)\}
\end{aligned}
$$

显然对于一条链上的维护是容易的。

## 全局平衡二叉树的应用

这里我们降复杂度主要有几个阻碍。

1.  一个节点可能有**多个轻儿子**，导致需要开一个堆来维护，这让我们非常不悦。
2.  我们在树剖的时候居然要跳 $O(\log n)$ 次并且每次进行 $O(\log n)$ 的操作，这让我们非常不悦。

第一个的解决方法就是@[hehezhou](https://www.luogu.com.cn/user/67371) 大佬提到的一般树二叉化。

![原树](https://cdn.luogu.com.cn/upload/image_hosting/bkd0bcym.png)

![新二叉树](https://cdn.luogu.com.cn/upload/image_hosting/hit4yi9l.png)

具体地，对于每个节点 $u$，我们将它的每个儿子 $v$ 都复制一个节点 $rep(v)$，然后分类讨论，用 $dep$ 记录距离。如果 $v$ 是第一个儿子，连接 $u\rightarrow rep(v)$ 和 $rep(v)\rightarrow v$。否则，令上一个儿子为 $pre$，连接 $rep(v)\rightarrow rep(pre),v\rightarrow rep(v)$。

这样就完成了一般树向二叉树的转化。

第二个问题的解决方法就是**全局平衡二叉树**。这个东西实际上是一个静态的 LCT，要对一棵树进行重链剖分。对转化成的二叉树，先进行重链剖分。对于每条重链，每次 `build` 求它的加权重心（每个点的点权是轻儿子 $siz+1$），然后递归建树。

树高是 $O(\log n)$ 的，这是全局平衡二叉树的复杂度保证。证明分类讨论即可，无论是跳重边还是跳轻边，子树大小至少都会翻倍。

我们建出了一颗全局平衡二叉树。由于第一个问题提供的解决方法，这棵树上的每一个节点至多有一个轻儿子，这是一个很好的性质。

下面就是和一般全局平衡二叉树和原有题解不同的地方。原有题解由于叶子节点没有儿子，可以直接把轻儿子接在二叉树的任意儿子上变成一个**伪儿子**，目的仅是便利访问和更新信息。但是我不想写宗法树！（这样我们就可以少开一半的节点）于是对每个节点额外开了一个 $u_{vt}$，记录它的**轻（虚）儿子所在二叉搜索树的根**。

接下来的合并也有所不同。对于一个节点 $u$，我们要先合并 $ls,u$，再用合并过的 $u$ 与 $rs$ 合并，具体实现如下：


```cpp
void merge(Node &ls,Node &rs,bool tf){//线段树的合并
	Node u;
	if(!tf)u=ls;
	else u=rs;
	u.lmax=max(ls.lmax,dep[rs.L]-dep[ls.L]+rs.lmax);
	u.rmax=max(rs.rmax,dep[rs.R]-dep[ls.R]+ls.rmax);
	u.ans=max(max(ls.ans,rs.ans),dep[rs.L]-dep[ls.R]+ls.rmax+rs.lmax);
	if(!tf)u.R=rs.R,ls=u;
	else u.L=ls.L,rs=u;
}

u.L=u.R=p;u.ans=u.lmax=u.rmax=(col[p]?0:-INF);
if(u.ch[0])merge(t[u.ch[0]],u,1);//先合并左儿子
if(u.ch[1])merge(u,t[u.ch[1]],0);//再合并右儿子
```

然后就是关于轻儿子的问题。这里我们要对线段树的信息定义做一些稍微的变形，$u_{lmax}$ 表示 $u_l$ 到当前所处集合中的距离最大值，$u_{rmax},u_{ans}$ 同理。这样我们维护的就不再是一条链，但是由于每次合并都是在链首或者链尾进行的，所以只需要保证链首链尾信息的正确性，这个做法就是对的。

我们要怎么维护它们呢？令 $lson_u$ 表示 $u$ 的轻儿子。

$$
\begin{aligned}
D&=u_{vt_{lmax}}+dis(lson_u,u)
\\u_{lmax}&=\max\{u_{lmax},D+dis(u,u_l)\}
\\u_{rmax}&=\max\{u_{rmax},D+dis(u,u_r)\}
\\D_1&=ls_{rmax}+D+dis(u,ls_r)
\\D_2&=rs_{lmax}+D+dis(u,rs_l)
\\u_{ans}&=\max\{u_{ans},D_1,D_2,vt_{ans}\}
\end{aligned}
$$

实现如下：


```cpp
if(u.vt){
		int D=t[u.vt].lmax+dep[lson[p]]-dep[p];
		u.ans=max(u.ans,t[u.vt].ans);
		u.lmax=max(u.lmax,D+dep[p]-dep[u.L]);
		u.rmax=max(u.rmax,D+dep[u.R]-dep[p]);
		int D1=(t[u.ch[0]].rmax)+dep[p]-dep[t[u.ch[0]].R]+D,
			D2=(t[u.ch[1]].lmax)+dep[t[u.ch[1]].L]-dep[p]+D;
		u.ans=max(u.ans,max(D1,D2));
	}
```

另外还要注意叶子节点的分讨，这里就不作详细展开了。

最后需要注意的是，本篇题解着重强调了 $lson_u$ 和 $u_{vt}$ 的区别，希望没有人像我一样混淆。

完整代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,INF=1e9;
int n,head[N],idx,lson[N],rson[N],dep[N];
int siz[N],lsiz[N],root;
struct Node{int ch[2],L,R,fa,lmax,rmax,ans,vt;}t[N];
struct Edge{int v,next,w;}e[N<<1];
void ins(int x,int y,int z){
	e[++idx].v=y;
	e[idx].next=head[x];
	e[idx].w=z;
	head[x]=idx;
}
void ins1(int x,int y){
	if(!lson[y])lson[y]=x;
	else rson[y]=x;
}
void dfs(int u,int fa){
	int lst=0;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w=e[i].w;
		if(v==fa)continue;
		dep[v]=dep[u]+w;
		dep[v+n]=dep[u];
		if(!lst){
			ins1(v+n,u);
			ins1(v,v+n);
		}
		else {
			ins1(v+n,lst);
			ins1(v,v+n);
		}
		dfs(v,u);
		lst=v+n;
	}
}
void dfs0(int u){
	siz[u]=1;
	if(lson[u])dfs0(lson[u]);
	siz[u]+=siz[lson[u]];
	if(rson[u])dfs0(rson[u]);
	siz[u]+=siz[rson[u]];
	if(siz[lson[u]]>siz[rson[u]])
		swap(lson[u],rson[u]);
	lsiz[u]=siz[lson[u]]+1;
}
int stk[N],tp,pre[N];
int ef(int l,int r,int &sum){
	int res=r;
	while(l<=r){
		int mid=(l+r)>>1;
		if(pre[mid]>=sum)res=mid,r=mid-1;
		else l=mid+1;
	}
	return res;
}
int build(int l,int r){
	if(l>r)return 0;
	if(l==r)return t[stk[l]].L=t[stk[l]].R=stk[l];
	int sum=((pre[r]-pre[l-1])>>1)+pre[l-1];
	int i=ef(l,r,sum);
	t[stk[i]].ch[0]=build(l,i-1);
	t[stk[i]].ch[1]=build(i+1,r);
	t[t[stk[i]].ch[0]].fa=t[t[stk[i]].ch[1]].fa=stk[i];
	t[stk[i]].L=stk[l],t[stk[i]].R=stk[r];
	return stk[i];
}
void dfs1(int u){
	stk[++tp]=u;
	if(rson[u])dfs1(rson[u]);
	else {
		for(int i=1;i<=tp;i++)pre[i]=pre[i-1]+lsiz[stk[i]];
		int rt=build(1,tp);
		if(!stk[0])root=rt;
		else t[rt].fa=stk[0],t[stk[0]].vt=rt;
		tp=0;
	}
	stk[0]=u;
	if(lson[u])dfs1(lson[u]);
}
int cntw;
bool col[N];
void merge(Node &ls,Node &rs,bool tf){
	Node u;
	if(!tf)u=ls;
	else u=rs;
	u.lmax=max(ls.lmax,dep[rs.L]-dep[ls.L]+rs.lmax);
	u.rmax=max(rs.rmax,dep[rs.R]-dep[ls.R]+ls.rmax);
	u.ans=max(max(ls.ans,rs.ans),dep[rs.L]-dep[ls.R]+ls.rmax+rs.lmax);
	if(!tf)u.R=rs.R,ls=u;
	else u.L=ls.L,rs=u;
}
void pushup(int p){
	Node &u=t[p];
	if(u.L==u.R){
		int D=t[u.vt].lmax+dep[lson[p]]-dep[p];
		u.ans=t[u.vt].ans;
		if(col[p])u.ans=max(u.ans,u.lmax=u.rmax=max(D,0));
		else u.lmax=u.rmax=D;
		return ;
	}
	u.L=u.R=p;u.ans=u.lmax=u.rmax=(col[p]?0:-INF);
	if(u.ch[0])merge(t[u.ch[0]],u,1);
	if(u.ch[1])merge(u,t[u.ch[1]],0);
	if(u.vt){
		int D=t[u.vt].lmax+dep[lson[p]]-dep[p];
		u.ans=max(u.ans,t[u.vt].ans);
		u.lmax=max(u.lmax,D+dep[p]-dep[u.L]);
		u.rmax=max(u.rmax,D+dep[u.R]-dep[p]);
		int D1=(t[u.ch[0]].rmax)+dep[p]-dep[t[u.ch[0]].R]+D,
			D2=(t[u.ch[1]].lmax)+dep[t[u.ch[1]].L]-dep[p]+D;
		u.ans=max(u.ans,max(D1,D2));
	}
}
void init(int p){
	if(!p)return ;
	init(t[p].vt);
	init(t[p].ch[0]),init(t[p].ch[1]);
	pushup(p);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;cntw=n;
	t[0].lmax=t[0].rmax=t[0].ans=-INF;
	for(int i=1;i<n;i++){
		int a,b,c;
		cin>>a>>b>>c;
		ins(a,b,c);
		ins(b,a,c);
	}
	dfs(1,0);
	dfs0(1);
	dfs1(1);
	for(int i=1;i<=n;i++)col[i]=1;
	init(root);
	int Q;cin>>Q;
	while(Q--){
		char c;cin>>c;
		if(c=='C'){
			int x;cin>>x;
			col[x]^=1;
			if(!col[x])cntw--;
			else cntw++;
			for(;x;x=t[x].fa)pushup(x);
		}
		else {
			if(cntw)cout<<t[root].ans<<'\n';
			else cout<<"They have disappeared.\n";
		}
	}
	return 0;
}
```

经过实测，由于每个节点两次合并的常数原因，本做法虽然比原做法少开一半的节点，但在评测时间上并无优势甚至更劣，读者可自行选择。

---

## 作者：lfxxx (赞：0)

来个严格单 $\log n$ 做法。

首先建出静态 Top tree。

如何建出这个玩意呢？

仿照全局平衡二叉树的建法，先重链剖分一下，然后对于一个点的所有轻儿子全部收缩成一个簇，然后按照簇的大小带权分治，每次把左右区间的簇 rake 成一个，然后 rake 到重儿子所在簇上，再对重链按照簇大小（子树大小减去重儿子子树大小）带权分治，每次把左右区间 compress 成一个簇，再向上递归。由于这个过程中总是重量平衡的，所以建立出来的 Top tree 树高是 $O(\log n)$。

然后在 Top tree 上 dp。

具体而言，每个簇包含的点信息就是代表的联通子图中除了界点外的所有点，然后记录簇内白点最大距离与白点到两个界点最大距离，每次 compress 或者 rake 时将被删去的界点的信息合并到簇内，并将两个簇的路径合并起来，再将这个簇与被删去的界点关联起来，关于这个点的修改就从这个簇开始向上更新父亲的 dp 数组。

总复杂度是 $O(q \log n + n \log n)$ 的。

```cpp
#include<bits/stdc++.h>
#define int long long
//#define lowbit(x) (x&(-x))
using namespace std;
const int maxn = 2e5+114;
const int inf = 1e13+114;
struct node{
	int u,v,ans,maxu,maxv,id,dis;//簇内答案（不包括界点） 到界定的距离最大的白点的距离
	char type;
	//u 在上面 v 在下面
}cluster[maxn];
int n,m,col[maxn];
int pos[maxn],fa[maxn],ls[maxn],rs[maxn];
char type[maxn];//P 是边点 C 是 compress 点 R 是 rake 点
int root=1;//根簇
void compress(node x,node y,node &w){
    if(x.id==0||y.id==0) assert(0);
	//x 在上面 y 在下面
	w.ans=w.maxu=w.maxv=-inf;
	w.u=x.u,w.v=y.v;
	w.dis=x.dis+y.dis;
	w.ans=max(x.ans,y.ans);
	w.ans=max(w.ans,x.maxv+y.maxu);
    w.maxu=max(x.maxu,y.maxu+x.dis);
    w.maxv=max(x.maxv+y.dis,y.maxv);
    if(col[x.v]==0){
        w.ans=max(w.ans,max(x.maxv,y.maxu));
        w.ans=max(w.ans,0*1ll);
        w.maxu=max(w.maxu,x.dis);
        w.maxv=max(w.maxv,y.dis);
    }
	pos[x.v]=w.id;
	fa[x.id]=fa[y.id]=w.id;
	ls[w.id]=x.id;
	rs[w.id]=y.id;
	//cout<<"compress"<<w.u<<" "<<w.v<<" "<<w.ans<<'\n';
	w.type='C';
	root=w.id;
}
void rake(node x,node y,node &w){
    if(x.id==0||y.id==0) assert(0);
	//把 x rake 到 y 上
	w.ans=w.maxu=w.maxv=-inf;
	w.u=y.u,w.v=y.v;
	w.dis=y.dis;
	w.ans=max(x.ans,y.ans);
	w.ans=max(w.ans,x.maxu+y.maxu);
    w.maxu=max(x.maxu,y.maxu);
    w.maxv=max(x.maxu+y.dis,y.maxv);
    if(col[x.v]==0){
        w.ans=max(w.ans,max(x.maxv,y.maxu+x.dis));
        w.ans=max(w.ans,0*1ll);
        w.maxu=max(w.maxu,x.dis);
        w.maxv=max(w.maxv,x.dis+y.dis);
    }
	pos[x.v]=w.id;
	fa[x.id]=fa[y.id]=w.id;
	ls[w.id]=x.id;
	rs[w.id]=y.id;
	//cout<<"rake"<<w.u<<' '<<w.v<<' '<<w.ans<<'\n';
	w.type='R';
	root=w.id;
}
void update(int u){
    if(u==0) return ;
    if(cluster[u].type=='C'){
        compress(cluster[ls[u]],cluster[rs[u]],cluster[u]);
        update(fa[u]);
    }else{
        rake(cluster[ls[u]],cluster[rs[u]],cluster[u]);
        update(fa[u]);
    }
}
vector< pair<int,int> > E[maxn];
int father_pos[maxn];//一个点到其父亲的边的簇编号
int father[maxn];
int son[maxn],sz[maxn],tot;
vector<int> st[maxn];//重链上的点存到链顶
void dfs1(int u){
	sz[u]=1;
	for(pair<int,int> nxt:E[u]){
	    int v=nxt.first,w=nxt.second;
		if(v==father[u]) continue;
		father[v]=u;
		father_pos[v]=++tot;
		cluster[tot].u=u,cluster[tot].v=v,cluster[tot].id=tot,cluster[tot].dis=w,cluster[tot].ans=cluster[tot].maxu=cluster[tot].maxv=-inf;
		dfs1(v);
		if(sz[v]>sz[son[u]]) son[u]=v;
		sz[u]+=sz[v];
	}
}
void dfs2(int u,int tp){
	st[tp].push_back(u);
	if(son[u]!=0) dfs2(son[u],tp);
	for(pair<int,int> nxt:E[u]){
	    int v=nxt.first;
		if(v==father[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
//需要虚拟节点 n+1 作为根 只在第一次 dfs 以及最后根簇时调用
vector<int> vec[maxn];
vector<int> pre[maxn];
int solve(int l,int r,int u){
    if(l>r) return 0;
	if(l==r) return father_pos[vec[u][l]];
	int L=l,R=r;
	while(L+1<R){
		int mid=(L+R)>>1;
		if((pre[u][mid]-pre[u][l-1])*2<=(pre[u][r]-pre[u][l-1])) L=mid;
		else R=mid;
	}
	int mid=L;
	int lson=solve(l,mid,u);
	int rson=solve(mid+1,r,u);
	int res=++tot;
	cluster[tot].id=tot;
	rake(cluster[lson],cluster[rson],cluster[res]);
	return res;
}
int calc(int l,int r,int u){
    if(l>r) return 0;
    if(l==r) return father_pos[vec[u][l]];
	int L=l,R=r;
	while(L+1<R){
		int mid=(L+R)>>1;
		if((pre[u][mid]-pre[u][l-1])*2<=(pre[u][r]-pre[u][l-1])) L=mid;
		else R=mid;
	}
	int mid=L;
	int lson=calc(l,mid,u);
	int rson=calc(mid+1,r,u);
	int res=++tot;
    cluster[tot].id=tot;
	compress(cluster[lson],cluster[rson],cluster[res]);
	return res;
}
void dfs3(int u){
	for(int x:st[u]){
        if(son[x]==0) continue;
		pre[x].push_back(0);
		vec[x].push_back(0);
		for(pair<int,int> nxt:E[x]){
		    int v=nxt.first;
			if(v!=son[x]&&v!=father[x]){
				dfs3(v);
				//收缩 (x,v) 一个簇
				vec[x].push_back(v);
			}
		}
		//在对这些轻儿子簇按中点分治的方法合并起来
		for(int i=1;i<=vec[x].size()-1;i++){
			pre[x].push_back(pre[x][i-1]+sz[vec[x][i]]);
		}
		int rt=solve(1,vec[x].size()-1,x);
		if(rt!=0){
		    tot++;
		    cluster[tot].id=tot;
            rake(cluster[rt],cluster[father_pos[son[x]]],cluster[tot]);
            father_pos[son[x]]=tot;//rake 到重链上		    
		}
	}
	vec[u].clear();
	pre[u].clear();
	pre[u].push_back(0);
	vec[u].push_back(0);
	for(int x:st[u]){
		vec[u].push_back(x);
	}
	for(int i=1;i<=vec[u].size()-1;i++){
		pre[u].push_back(pre[u][i-1]+sz[father[vec[u][i]]]-sz[vec[u][i]]);
	}
	if(u!=1) father_pos[u]=calc(1,vec[u].size()-1,u);//把重链上的边 compress 成一条
	else father_pos[u]=calc(2,vec[u].size()-1,u);
	E[u].clear();
	E[u].push_back(make_pair(father[u],0));
	return ;
}
int sum;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++){
        int u,v,c;
        cin>>u>>v>>c;
        E[u].push_back(make_pair(v,c));
        E[v].push_back(make_pair(u,c));
    }
    cin>>m;
    dfs1(1);
    dfs2(1,1);
    dfs3(1);
    while(m--){
        char opt;
        cin>>opt;
        if(opt=='C'){
            int x;
            cin>>x;
            sum-=col[x];
            col[x]^=1;
            sum+=col[x];
            update(pos[x]);
        }else{
            if(sum<n) cout<<max(max(cluster[root].ans,max((col[cluster[root].u]==0?max(0*1ll,cluster[root].maxu):-inf),(col[cluster[root].v]==0?max(0*1ll,cluster[root].maxv):-inf))),((col[cluster[root].u]==0&&col[cluster[root].v]==0)?cluster[root].dis:-inf))<<'\n';
            else cout<<"They have disappeared.\n";
        }
    }
	return 0;
}
```

---

## 作者：SrsgPrince_ (赞：0)

# QTREE4 - Query on a tree IV Solution

题面传送门：[QTREE4 - Query on a tree IV](https://www.luogu.com.cn/problem/SP2666)。

推荐在 [博客](https://www.luogu.com.cn/blog/fy123333/SP2666Solution) 中查看。

## 题目分析 Hint

题目中让我们进行两个操作：

1. `C a` 将点 $a$ 的颜色反转。（黑变白，白变黑）

2. `A` 询问 $dist(a,b)$ 的最大值。$a,b$ 点都必须为白色（$a$ 与 $b$ 可以相同），显然如果树上仍存在白点，查询得到的值一定是个非负数。特别地，如果 `A` 操作时树上没有白点，输出 `They have disappeared.`。

第一个操作是修改颜色，第二个操作是维护边权。考虑用树链剖分做。

## 思路 Solution

先对原树进行树链剖分，并且对重链建树。建树的方法很简单，先令 $dep_u$ 为 点 $u$ 到根节点的距离，$dist(u, v)$ 为点 $u$ 到点 $v$ 的距离，$mx1_u$ 为点 $u$ 向下第一步不走重边能走到的最远的白点的距离，$mx2_u$ 为点 $u$ 向下第一步不走重边能走到的次远的白点的距离。我们用堆来维护 $mx1_u$，求出 $u$ 的轻儿子在重链线段树的 $lmax$ 就可以了。$\operatorname{pushUp()}$ 需要维护三个值 $lmax$，$rmax$ 和 $mx$，分别是 $$lmax = \max{(lson_{lmax}, rson_{lmax} + dep_{rnk_{mid+1}} - dep_{rnk_{l}})}$$ $$rmax = \max{(rson_{rmax}, lson_{rmax} + dep_{rnk_{r}} - dep_{rnk_{mid}})}$$ $$mx = \max{(\max(lson_{mx}, rson_{mx}), lson_{rmax} + rson_{lmax} + dep_{rnk_{mid + 1}} - dep_{rnk_{mid}})}$$

也就是如下代码。

```cpp
inline void pushUp(int p, int lft, int rgt) {
    int ls = tr[p].lson, rs = tr[p].rson, mid = (lft + rgt) >> 1;
    tr[p].lmax = max(tr[ls].lmax, tr[rs].lmax + dep[rnk[mid + 1]] - dep[rnk[lft]]);
    tr[p].rmax = max(tr[rs].rmax, tr[ls].rmax + dep[rnk[rgt]] - dep[rnk[mid]]);
    tr[p].mx = max(max(tr[ls].mx, tr[rs].mx), tr[ls].rmax + tr[rs].lmax + dep[rnk[mid + 1]] - dep[rnk[mid]]);
}
```

接下来是修改点的颜色。修改一个点的颜色，要先修改当前点所在的重链线段树上进行修改。我们还是用一个堆来进行维护，可以 $O(1)$ 查询，线段树的复杂度 $O(\log n)$，堆的复杂度 $O(\log n)$。那么整体就是 $O(q \log ^ 2 n)$，其中 $q$ 为询问次数。

这里给出代码。

```cpp
struct Edge {
    int des, w;
};
vector<Edge> ed[maxn];
inline void dfs1(int x, int fth) {
    siz[x] = 1, son[x] = -1;
    for (auto y : ed[x]) {
        if (y.des == fth) continue;
        dep[y.des] = dep[x] + y.w, fa[y.des] = x, dfs1(y.des, x), siz[x] += siz[y.des];
        if (son[x] < 0 || siz[y.des] > siz[son[x]]) son[x] = y.des;
    }
}
inline void dfs2(int x, int tp) {
    top[x] = tp, dfn[x] = ++tme, rnk[tme] = x, len[tp]++;
    if (son[x] < 0) return;
    dfs2(son[x], tp);
    for (auto y : ed[x])
        if (y.des != son[x] && y.des != fa[x])
            dfs2(y.des, y.des);
}
struct Queue {
    priority_queue<int> q1, q2;
    inline void insert(int v) {if (v != -inf) q1.push(v);}
    inline void erase(int v) {if (v != -inf) q2.push(v);}
    inline int top() {
        while (1) {
            if (q1.empty()) return -inf;
            if (q2.empty() || q1.top() != q2.top()) return q1.top();
            q1.pop(), q2.pop();
        }
    }
}hp[maxn], res;
struct SegmentTree {
    int lson, rson, lmax, rmax, mx;
} tr[maxn << 2];
int tot, rt[maxn];
// 这里不在重复 pushUp
inline void buildTree(int &p, int lft, int rgt) {
    if (!p) p = ++tot;
    if (lft == rgt) {
        int x = rnk[lft];
        for (auto y : ed[x]) {
            if (y.des == fa[x] || y.des == son[x]) continue;
            hp[x].insert(tr[rt[y.des]].lmax + dep[y.des] - dep[x]);
        }
        int mx1 = hp[x].top(); hp[x].erase(mx1);
        int mx2 = hp[x].top(); hp[x].insert(mx1);
        tr[p].lmax = tr[p].rmax = max(0, mx1), tr[p].mx = max(0, max(mx1, mx1 + mx2));
        return;
    }
    int mid = (lft + rgt) >> 1;
    buildTree(tr[p].lson, lft, mid), buildTree(tr[p].rson, mid + 1, rgt);
    pushUp(p, lft, rgt);
}
inline void update(int p, int lft, int rgt, int id) {
    if (lft == rgt) {
        int x = rnk[lft];
        int mx1 = hp[x].top(); hp[x].erase(mx1);
        int mx2 = hp[x].top(); hp[x].insert(mx1);
        if (col[x]) tr[p].lmax = tr[p].rmax = mx1, tr[p].mx = mx1 + mx2;
        else tr[p].lmax = tr[p].rmax = max(0, mx1), tr[p].mx = max(0, max(mx1, mx1 + mx2));
        return;
    }
    int mid = (lft + rgt) >> 1;
    if (id <= mid) update(tr[p].lson, lft, mid, id);
    else update(tr[p].rson, mid + 1, rgt, id);
    pushUp(p, lft, rgt);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        ed[u].push_back({v, w});
        ed[v].push_back({u, w});
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = n; i; --i) {
        int x = rnk[i];
        if (x != top[x]) continue;
        buildTree(rt[x], dfn[x], dfn[x] + len[x] - 1);
        res.insert(tr[rt[x]].mx);
    }
    int m;
    cin >> m;
    int cnt = n;
    while (m--) {
        char ch;
        cin >> ch;
        if (ch == 'A') {
            if (!cnt) cout << "They have disappeared.\n";
            else cout << res.top() << "\n";
            continue;
        }
        int x;
        cin >> x;
        col[x] ^= 1;
        if (!col[x]) cnt++; else cnt--;
        while (x) {
            int tp = top[x];
            res.erase(tr[rt[tp]].mx);
            if (fa[tp]) hp[fa[tp]].erase(tr[rt[tp]].lmax + dep[tp] - dep[fa[tp]]);
            update(rt[tp], dfn[tp], dfn[tp] + len[tp] - 1, dfn[x]);
            if (fa[tp]) hp[fa[tp]].insert(tr[rt[tp]].lmax + dep[tp] - dep[fa[tp]]);
            res.insert(tr[rt[tp]].mx);
            x = fa[tp];
        }
    }
    return 0;
}
```

也不知道为什么，我一开始 TLE 了两次，查过了所有的地方，都没问题，自造数据也没问题，最后不知道为什么改了输入输出，用了 cin/cout 然后就过了，快读快写反而没过，感觉是 putchar 在 SPOJ 里面寄了。


---

