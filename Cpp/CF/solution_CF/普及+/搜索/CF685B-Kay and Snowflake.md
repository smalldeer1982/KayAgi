# Kay and Snowflake

## 题目描述

After the piece of a devilish mirror hit the Kay's eye, he is no longer interested in the beauty of the roses. Now he likes to watch snowflakes.

Once upon a time, he found a huge snowflake that has a form of the tree (connected acyclic graph) consisting of $ n $ nodes. The root of tree has index $ 1 $ . Kay is very interested in the structure of this tree.

After doing some research he formed $ q $ queries he is interested in. The $ i $ -th query asks to find a centroid of the subtree of the node $ v_{i} $ . Your goal is to answer all queries.

Subtree of a node is a part of tree consisting of this node and all it's descendants (direct or not). In other words, subtree of node $ v $ is formed by nodes $ u $ , such that node $ v $ is present on the path from $ u $ to root.

Centroid of a tree (or a subtree) is a node, such that if we erase it from the tree, the maximum size of the connected component will be at least two times smaller than the size of the initial tree (or a subtree).

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)The first query asks for a centroid of the whole tree — this is node $ 3 $ . If we delete node $ 3 $ the tree will split in four components, two of size $ 1 $ and two of size $ 2 $ .

The subtree of the second node consists of this node only, so the answer is $ 2 $ .

Node $ 3 $ is centroid of its own subtree.

The centroids of the subtree of the node $ 5 $ are nodes $ 5 $ and $ 6 $ — both answers are considered correct.

## 样例 #1

### 输入

```
7 4
1 1 3 3 5 3
1
2
3
5
```

### 输出

```
3
2
3
6
```

# 题解

## 作者：mrsrz (赞：25)

首先确保你知道什么是树的重心。

询问次数和节点个数同个级别，显然可以一遍跑出所有点为根的子树的答案。

考虑节点$x$和其每个儿子节点$y$，若$x$子树的重心在$y$子树内，则$x$子树的重心一定在$y$子树的重心的上方，因为往下移动显然不优。

这样的话，我们枚举每个$x$的儿子$y$，$z$为当前考虑的节点，初始为$y$子树的重心。

我们每次让$z$往上跳，并更新当前最优解。

如果$z$往上跳的结果比当前优，则继续，否则，$z$再往上跳显然答案会更加劣，所以结束即可。

这样做，$z$只会跳到每个点1次（下次再跳只会从这次$z$跳到的终点开始跳，因为保证了每次往上跳更优，最上方的才可能成为答案），所以时间复杂度是$O(n)$的。

## Code：
```cpp
#include<cstdio>
#include<algorithm>
#define N 300005
int n,m,fa[N],head[N],rt[N],sz[N],mx[N],cnt;
struct edge{
	int to,nxt;
}e[N];
void dfs(int now,int pre){
	sz[now]=1;
	for(int i=head[now];i;i=e[i].nxt){
		dfs(e[i].to,now);
		sz[now]+=sz[e[i].to];
		mx[now]=std::max(mx[now],sz[e[i].to]);
	}
	int id=now,me=mx[now];
	for(int i=head[now];i;i=e[i].nxt){
		int it=rt[e[i].to],pre=std::max(mx[it],sz[now]-sz[it]),p=it;
		while(fa[it]!=now){
			it=fa[it];
			int New=std::max(mx[it],sz[now]-sz[it]);
			if(New<pre)pre=New,p=it;else break;
		}
		if(me>pre){
			me=pre;
			id=p;
		}
	}
	rt[now]=id;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;++i){
		scanf("%d",fa+i);
		e[++cnt]=(edge){i,head[fa[i]]};head[fa[i]]=cnt;
	}
	dfs(1,0);
	while(m--){
		int x;
		scanf("%d",&x);
		printf("%d\n",rt[x]);
	}
	return 0;
}
```

---

## 作者：Ryan_ (赞：11)

**题目描述：给出n个数，n-1个数的父亲节点，共q个询问，求以ai为根节点的子树的重心**

$size[i]$表示以i为根节点的子树节点个数，

有树的重心的性质可知，当某节点u的最大子树节点v的size的两倍小于$size[u]$

该点为重心

即$size[v]*2< size[u]$

不然暴力往上走，时间复杂度$O(n)$

上代码


```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,q;
const int N=600001;
int nxt[N],first[N],go[N],tot,size[N],f[N],ans[N],fa[N];
void add(int x,int y) {
	nxt[++tot]=first[x];
	first[x]=tot;
	go[tot]=y;
}
void dfs(int x) {
	ans[x]=x;
	size[x]=1;
	int maxn=0,t=0;
	for(int i=first[x]; i; i=nxt[i]) {
		int v=go[i];
		dfs(v);
		size[x]+=size[v];
		if(size[v]>maxn) {
			maxn=size[v];
			t=v;
		}
	}
	f[x]=maxn;
	if(f[x]*2<size[x])ans[x]=x;
	else {
		int now=ans[t];
		while(fa[now]&&max(f[now],size[x]-size[now])>max(f[fa[now]],size[x]-size[fa[now]]))now=fa[now];
		ans[x]=now;
	}
}
int main() {
	cin>>n>>q;
	for(int i=2; i<=n; i++) {
		int k;
		cin>>k;
		fa[i]=k;
		add(k,i);
	}
	dfs(1);
	for(int i=1; i<=q; i++) {
		int k;
		cin>>k;
		cout<<ans[k]<<endl;
	}
}
```


---

## 作者：くろねこ (赞：9)

这个题居然没有题解的吗

~~果然CF在洛谷没人做~~

蒟蒻小心的献上题解报告qwq

(建议先看代码再看上面的做题过程,否则您可能看不懂我在说什么qwq)

------------


本题大意就是**给你一颗树和几次查询,询问给定查询点的子树的重心是哪一个点**

本蒟蒻一看题面非常高兴,这不直接跑几次DFS就过了吗

开开心心的提交了代码
```cpp
	for (rg int i = 1;i <= n;++i)
	{
		bigsize = 0x7f7f7f7f;
		dfs(i,fa[i]);
		ans[i] = bignode;
	}
```
然后这就是结果

![不对劲啊居然过了两个点](https://s1.ax1x.com/2018/10/18/iwa7dA.png)

~~不对劲啊居然过了两个点~~

然后本蒟蒻就懵逼了

认真想了想 30w的最大数据跑dfs~~除了天河一号~~怎么可能不炸

于是决定修改dfs

```cpp
	res = max(res,n - son[x]);
	if (res < bigsize)
	{
		bigsize = res;
		bignode = x;
	}
	ans[x] = bignode;
```
嗯..果然输出结果都是0

最后经过认(fan)真(bo)研(ke)究

发现这个题可以用**树的重心的特性**来求解

树的重心的特性:以这个点为根,那么其所有的子树的大小都不超过整个树的一半.

那么我们可以在每次dfs回溯的时候加一些特判

```cpp
if ((son[res] << 1) > son[x])
{
	rg int temp = ans[res];
	while (((son[x] - son[temp]) << 1) > son[x]) temp = fa[temp];
	ans[x] = temp;
}
```
然后就能开开心心的AC啦


------------

这个题其实只用建立单向边,因为这棵树根本不会回到他的father节点,时空更加优秀

~~我的最优解啊qaq~~

------------

**上!代!码!**

------------

```cpp
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
#define rg register
template <typename qwq> inline void read(qwq & x)//读入优化 
{
	x = 0;
	rg int f = 1;
	rg char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + (c ^ 48);//位运算优化 
		c = getchar();
	}
	x *= f;
}
template <typename qaq> inline void print(qaq x)//输出优化 
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int maxn = 300005;
struct edge
{
	int v,next;
}e[maxn << 1];
int head[maxn],tot,son[maxn],n,q,fa[maxn];
inline void add(int x,int y)
{
	++tot;
	e[tot].v = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int bignode,bigsize = 0x7f7f7f7f;
int ans[maxn];
inline void dfs(int x,int f)//离线预处理 
{
	rg int res = 0;//保证第一次能够合法查询且有一个极小值,那么直接把他设为0 
	son[x] = 1;
	ans[x] = x;//先默认该点是其子树的根节点 
	for (rg int i = head[x];i;i = e[i].next)//前向星遍历树 
	{
		if (e[i].v == f) continue;
		dfs(e[i].v,x);
		son[x] += son[e[i].v];
		if (son[e[i].v] > son[res]) res = e[i].v;//发现较大子树,更新 
//		res = max(res,son[e[i].v]);
	}
	if ((son[res] << 1) > son[x])//树的重心的定义:以这个点为根,那么其所有的子树的大小都不超过整个树的一半.
	//说明x并不是该子树重心 
	{
		rg int temp = ans[res];
		//位运算优化,左移1位相当于乘2 
		while (((son[x] - son[temp]) << 1) > son[x]) temp = fa[temp];//反复枚举直到找到其重心 
		ans[x] = temp;
	}
//	res = max(res,n - son[x]);//这个方法ans果然为0 
//	if (res < bigsize)
//	{
//		bigsize = res;
//		bignode = x;
//	}
//	ans[x] = bignode;
}
int x,y,z;
int main()
{
	read(n),read(q);
	for (rg int i = 2;i <= n;++i)
	{
		read(x),add(i,x),add(x,i),fa[i] = x;
	}
//	for (rg int i = 1;i <= n;++i)//暴力算法果断TLE 
//	{
//		bigsize = 0x7f7f7f7f;
//		dfs(i,fa[i]);
//		ans[i] = bignode;
//	}
	dfs(1,0);
	for (rg int i = 1;i <= q;++i)
	{
		read(x);
		print(ans[x]),puts("");
	}
}
```


---

## 作者：CYZZ (赞：5)

# [Kay and Snowflake](https://www.luogu.com.cn/problem/CF685B)
这是一道树的重心板子题。首先，我们要认识树的重心是什么。

## 定义
对于树上的每一个点，计算其所有子树中最大的子树节点数，使这个值最小的点就是这棵树的**重心**。
## 性质
- 以树的重心为**根**时，所有子树的大小都不超过整棵树大小的**一半**。
- 树中所有点到某个点的距离和中，到重心的距离和是**最小**的；如果有两个重心，那么到它们的距离和**一样**。
- 把两棵树通过一条边相连得到一棵新的树，那么新的树的重心在连接原来两棵树的重心的路径上。
- 在一棵树上添加或删除一个**叶子**，那么它的重心最多只移动一条边的距离。
- 当某节点 $u$ 的最大子树节点 $v$ 的 $size$ 的**两倍**小于 $size_u$，则该点为重心。

根据性质 5，直接 dfs 往上跳即可。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,tot,q,size1[300005],size2[300005],head[300005],ans[300005],fa[300005];
struct edge
{
	int nxt,to;
}e[600005];
void add_edge(int u,int v)
{
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}
void dfs(int u,int fa1)
{
	fa[u]=fa1;
	size1[u]=1;
	for(int i=head[u];i!=0;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa1)
			continue;
		dfs(v,u);
		size1[u]+=size1[v];
		if(size1[v]>size1[size2[u]])
			size2[u]=v;
	}
	if(!size2[u])
	{
		ans[u]=u;
		return ;
	}
	ans[u]=ans[size2[u]];
	while(size1[ans[u]]*2<size1[u])
	{
		ans[u]=fa[ans[u]];
	}
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++)
	{
		int t;
		scanf("%d",&t);
		add_edge(i,t);
		add_edge(t,i);  
	}
	dfs(1,0);
	for(int i=1;i<=q;i++)
	{
		int t;
		scanf("%d",&t);
		printf("%d\n",ans[t]);
	}
	return 0;
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：chihik (赞：4)

这道题应该算是 $\text{CSP2019 树的重心}$ 的前置知识了吧。~~可惜之前我并没有做过。~~

对于一棵以 $u$ 为根的子树，它的重心只可能在点 $u$ 或 以点 $u$ 的重儿子为根的子树中。

那么类比 $\text{lca}$ 倍增父亲，树的重心倍增重儿子。

查询时保证倍增时的子树大小不小于原子树大小的一半（重心的定义）。

最后它和它的父节点都可能是重心，随便判一下就可以了。

```cpp
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 300000 , MAXK = 20;
int n , q;
vector< int > Graph[ MAXN + 5 ];

int Fa[ MAXN + 5 ] , Size[ MAXN + 5 ] , Hson[ MAXN + 5 ] , Anc[ MAXN + 5 ][ MAXK + 1 ];
void dfs( int u ) {
    Size[ u ] = 1;
    for( int i = 0 ; i < Graph[ u ].size() ; i ++ ) {
        int v = Graph[ u ][ i ];
        dfs( v ); Size[ u ] += Size[ v ];
        if( Size[ v ] > Size[ Hson[ u ] ] ) Hson[ u ] = v;
    }
    Anc[ u ][ 0 ] = Hson[ u ];
    for( int i = 1 ; i <= MAXK ; i ++ ) Anc[ u ][ i ] = Anc[ Anc[ u ][ i - 1 ] ][ i - 1 ];
}

bool chk( int u , int v ) { //以u为根的子树，v是否为重心
    return max( Size[ Hson[ v ] ] , Size[ u ] - Size[ v ] ) <= Size[ u ] / 2;
}
int Query( int rt ) {
    int u = rt;
    for( int i = MAXK ; i >= 0 ; i -- )
        if( Anc[ u ][ i ] && Size[ Anc[ u ][ i ] ] >= Size[ rt ] / 2 ) u = Anc[ u ][ i ];
    if( chk( rt , u ) ) return u;
    if( chk( rt , Fa[ u ] ) ) return Fa[ u ];
}

int main( ) {
    scanf("%d %d",&n,&q);
    for( int i = 2 ; i <= n ; i ++ ) {
        scanf("%d",&Fa[ i ]);
        Graph[ Fa[ i ] ].push_back( i );
    }
    dfs( 1 );
    for( int i = 1 , rt ; i <= q ; i ++ ) {
        scanf("%d",&rt);
        printf("%d\n", Query( rt ) );   
    }
    return 0;
}
```

---

## 作者：cujam (赞：3)

~~本蒟蒻的第一篇题解~~

这是一道树的重心，不知道的建议先去做做模板题 [P1395 会议](https://www.luogu.com.cn/problem/P1395) 

很容易想到的做法就是暴力地直接对每个询问进行的        dfs,找到这棵子树得重心 ， 但是显而易见会超时，考虑预先求出每棵子树的重心，查询时 O（1）输出该子树重心，这道题就可以 AC 了。

那么如何求每棵子树的重心呢 ？

#### **对于一颗树它的重心在初始根节点或者最重子树上**

------------
依据树的重心的性质，所有点到重心的距离和最小。换言之以重心为根时，所有点的深度和最小。若把根节点定在任意节点时，则该节点的所有子节点深度都减小，相应的其他子树的节点的深度会增加。最大子树子节点最多，所以深度和减小就最多，所以把根节点放在最大子树上会优于放在其他子树上，所以一棵树的重心不在初始根节点上就在初始根节点的最大子树上。

#### 把两棵树通过一条边相连，新的树的重心在原来两颗树重心的连线上
在搜索一颗子树时可以看做把这颗子树和之前的节点与根节点形成的数之间通过一条边相连


------------
由此可得一颗树的重心在这颗树的最重子树的重心与根节点的连线上。

所以对于每一个根节点，我们找到它的最重子树从最重子树的重心往上跳，从而找到这个根节点下的子树的重心。

往上跳时还有一个结论，如果此时结果不如上一个节点更优，则继续跳下去也不会更优。因为此时深度增加的点的个数已经多于深度减小的点的个数，再跳下去这个差值会更大，故不可能更优。

优劣判断用输的重心的性质：以树的重心为根时，所有子树的大小都不超过整棵树大小的一半

下面是我的 AC 代码

```c
#include <bits/stdc++.h>
using namespace std;
const int N=6e5+9,MAX=0x3f3f3f3f;
int n,q,cnt,fa[N],ans[N],pre[N],last[N],other[N],size[N];
void add(int x,int y)
{
	pre[++cnt]=last[x];
	last[x]=cnt;
	other[cnt]=y;
}
void dfs(int x)
{
	int maxs=0;//初始化最大子树的大小为0 
	int an=0;//用于记录最大子树所在的子节点 
	ans[x]=x;//初始化每棵子树的重心为这棵子树的初始根 
	size[x]=1;
	for(int i=last[x];i;i=pre[i])
	{
		int y=other[i];
		dfs(y);
		size[x]+=size[y];//计算子树大小 
		if(size[y]>maxs) //比较最大子树并记录 
		{
			maxs=size[y];
			an=y;
		}
	}
	if(2*size[an]>size[x])//以树的重心为根时，所有子树的大小都不超过整棵树大小的一半
	{
		int temp=ans[an];
		while(2*(size[x]-size[temp])>size[x])
		{
			temp=fa[temp];
		}
		ans[x]=temp;
	}
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		fa[i]=x;
		add(x,i);
	}
	dfs(1);
	for(int i=1;i<=q;i++)
	{
		int x;
		scanf("%d",&x);
//		cout<<"ans: ";
		cout<<ans[x]<<endl;
	}
}
```


---

## 作者：chen_z (赞：2)

前置芝士：重链剖分。

这里来一个个人认为很好理解的新做法。

重心有一个比较典的性质是：一棵树的重心是根节点所在重链上，深度最大的满足 $sz_u \times 2>sz_{root}$ 的点（$sz$ 是子树大小，$u$ 是当前点，$root$ 是这棵树的根）。

知道了这个性质之后我们考虑剖出重链然后如何快速求出这个深度最大的 $u$。一个比较自然的思路是在重链上向下二分，直接在树上二分显然是不行的，但是发现重链上的点拍到 $dfn$ 序列上是连续的，那么就支持我们在 $dfn$ 序列上二分了。

每次二分的右界需要单独处理一下，在预处理的时候求出每个点所在重链向下的长度还有多少。

时间复杂度 $O(n+q \log n)$，虽然理论上比 $O(n)$ 的慢一些但是可能因为常数问题，它的速度遥遥领先于大部分 $O(n)$ 的解法。

笔者认为在重链上二分的思路可能不需要动脑子，且在更强问题上更有前途。

AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300010;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,q,fa[N],len[N],sz[N],son[N],dfn[N],rnk[N],cnt;
vector<int> e[N];
void dfs1(int now){
    sz[now]=1;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        dfs1(to);
        sz[now]+=sz[to];
        if(sz[to]>sz[son[now]])son[now]=to;
    }
}
void dfs2(int now){
    dfn[now]=++cnt,rnk[cnt]=now;
    if(son[now]==0){
        len[now]=1;
        return;
    }
    dfs2(son[now]);
    len[now]=len[son[now]]+1;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(son[now]==to)continue;
        dfs2(to);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    n=read(),q=read();
    for(int i=2;i<=n;i++)fa[i]=read(),e[fa[i]].push_back(i);
    dfs1(1);dfs2(1);
    for(int i=1;i<=q;i++){
        int a=read();
        int l=dfn[a],r=dfn[a]+len[a]-1,ans=l;
        while(l<=r){
            int mid=(l+r)>>1;
            if(2*sz[rnk[mid]]>sz[a])l=mid+1,ans=mid;
            else r=mid-1;
        }
        cout<<rnk[ans]<<'\n';
    }
    return 0;
}
```

---

## 作者：shao0320 (赞：2)

#### CF685B Kay and Snowflake

因为询问很多，因此可以考虑就先处理出每棵子树的重心之后回答即可。

考虑一棵子树的重心，要么是在他的重儿子那棵子树中，要么是它本身。

感性理解一下就是如果这棵子树的中心不是根的话，那么一定离重儿子的重心不远，于是直接从重儿子的重心往上暴跳即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 300005
#define pb push_back
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,q,fa[N],ans[N],siz[N],son[N];
vector<int>G[N];
void dfs(int x)
{
	//cout<<x<<endl;
	int sizz=G[x].size();siz[x]=1;
	for(int i=0;i<sizz;i++)
	{
		//cout<<x<<" "<<i<<endl;
		int v=G[x][i];
		if(v==fa[x])continue;
		dfs(v);siz[x]+=siz[v];
		if(siz[v]>siz[son[x]])son[x]=v;
	}
	if(siz[son[x]]*2<=siz[x])
	{
		ans[x]=x;
		//cout<<"!!!!!!!!!!!!!!"<<x<<endl;
	}
	else
	{
		//cout<<x<<" "<<son[x]<<" "<<fa[x]<<" "<<siz[son[x]]<<" "<<ans[son[x]]<<endl;
		//return;
		int xx=ans[son[x]];
		while(max(siz[son[xx]],siz[x]-siz[xx])*2>siz[x])xx=fa[xx];//,printf("%d\n",xx);
		ans[x]=xx;
	}
}
int main()
{
	n=read();q=read();
	for(int i=2;i<=n;i++){fa[i]=read();G[fa[i]].pb(i);}
	dfs(1);
	while(q--)printf("%d\n",ans[read()]);
	return 0;
}
```



---

## 作者：zhengrunzhe (赞：2)

提供一个数据结构做法

有一个定理就是 对于一条树边连接的两个连同块 重心会在大的那块 如果两块大小相同 那么这条边的两个端点都是重心

所以一个点$v$要是子树$u$的重心的条件是：

首先要满足$v$在子树$u$中:$1.v\in subtree_u$

$2.\forall w\in son_v \ \ size_u-size_w\geq size_w$

代表重心不能往下移(可以v和v的某个儿子同时是重心)

这个任意可以通过取个最大值化掉

$2.\max_{w\in son_v} \{2size[w]\}\leq size_u$

这个最大的子树大小可以直接预处理出来，记作$maxw$

即 $2.\ \ \ \ \ 2maxw_v \leq size_u$


$3.size_v\geq size_u-size_v$

代表重心不能往上移(可以v和v的父亲同时为重心)

然后如果是枚举u看哪些v满足条件的话 发现是个三维偏序(v在u的子树中 $maxw_v$和$size_v$)

非常阴间 考虑反过来对于每个$v$看它能成为哪些$u$的答案

发现只剩二维了($size_u$ u是v的祖先)

祖先这个维度我们可以通过访问插入、回溯删除的方法轻松规避掉

剩下一维是$2maxw_v\leq size_u \leq 2size_v$

这个可以轻松用线段树维护

我们要修改这些u的答案 我们就需要知道size满足这个限制的的编号

因为这个线段树维护了一条祖孙树链 所以size与点一一对应

我们可以直接对每个线段树节点开个vector装编号 查询的时候直接访问一整个vector一个个改答案

这样复杂度是没有问题的 首先空间复杂度每个点只会插入到$O(log)$个点里，时间复杂度的话，因为一棵树最多有两颗重心，所以每个满足条件的u最多被询问两次

回溯的时候需要删除 用vector可能不太好删 我就换成了set 多一个log但是其实挺快的

空间复杂度$O(n\log n)$，时间复杂度$O(n \log^2 n)$

总之是个非常暴力的做法，数据范围也没有大到一定要那种聪明的$O(n)$做法
```cpp
#include<set>
#include<cstdio>
#include<vector>
using std::set;
using std::max;
using std::vector;
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
typedef vector<int>Vector;
typedef set<int>Set;
const int N(3e5+5);
int n,m,ans[N],size[N],maxw[N];
Vector son[N];
struct tree
{
	Set id;
	tree *lson,*rson;
	void *operator new(size_t size);
	inline tree(){}
	inline const void insert(const int &l,const int &r,const int &k,const int &v)
	{
		id.insert(v);
		if (l==r)return;
		const int mid(l+r>>1);
		if (k<=mid)lson->insert(l,mid,k,v);
		else rson->insert(mid+1,r,k,v);
	}
	inline const void remove(const int &l,const int &r,const int &k,const int &v)
	{
		id.erase(v);
		if (l==r)return;
		const int mid(l+r>>1);
		if (k<=mid)lson->remove(l,mid,k,v);
		else rson->remove(mid+1,r,k,v);
	}
	inline const void query(const int &l,const int &r,const int &L,const int &R,const int &k)
	{
		if (l>R||r<L)return;
		if (l>=L&&r<=R)
		{
			for (Set::iterator i(id.begin());i!=id.end();i++)ans[*i]=k;
			return;
		}
		const int mid(l+r>>1);
		lson->query(l,mid,L,R,k);
		rson->query(mid+1,r,L,R,k);
	}
}*root;
char memory_pool[N*sizeof(tree)<<1],*tail(memory_pool+sizeof(memory_pool));
inline void *tree::operator new(size_t size){return tail-=size;}
inline const void build(tree *&p,const int &l,const int &r)
{
	p=new tree;
	if (l==r)return;
	const int mid(l+r>>1);
	build(p->lson,l,mid);
	build(p->rson,mid+1,r);
}
inline const void get_size(const int &p)
{
	size[p]=1;
	for (Vector::iterator i(son[p].begin());i!=son[p].end();i++)
		get_size(*i),
		size[p]+=size[*i],
		maxw[p]=max(maxw[p],size[*i]);
}
inline const void dfs(const int &p)
{
	root->insert(1,n,size[p],p);
	root->query(1,n,maxw[p]<<1,size[p]<<1,p);
	for (Vector::iterator i(son[p].begin());i!=son[p].end();i++)dfs(*i);
	root->remove(1,n,size[p],p);
}
int main()
{
	read(n);read(m);
	for (int fa,i(2);i<=n;i++)read(fa),son[fa].push_back(i);
	get_size(1);build(root,1,n);dfs(1);
	for (int x;m--;)read(x),printf("%d\n",ans[x]);
	return 0;
}
```

---

## 作者：luyan (赞：2)

首先关于重心：定义：一棵树将某个点去掉，会把这棵树分为好几块，以最大的一块的结点个数作为max_size，这样的话每一个点都对应着一个max_size，这些值当中最小的那个所对应的结点即为树的重心。

定义：son[i]表示以i为根的子树中size最大的子树
性质：如果一棵树的某个子树的size*2>size[root]那么这个顶点是这些子树中size最大的子树的根
**重点**：若x为根节点，这颗子树的重心一定在根节点（x）上或者是son[x]为根的子树上。
				一个树的重心的dep一定小于等于它的子树的重心
				这就有了我们的核心代码：	

```
	if(size[son[x]]*2>size[x]){//如果这个儿子的结点数超过整个的两倍 
		k=son[x];//找到第一个没超过两倍的子树根节点 
		while((size[x]-size[k])*2>size[x])k=fa[k];
		ans[x]=k;//以它为答案 
	}
	else{
		ans[x]=x;
	}
```
以上就是寻找重心的过程，加上深度优先搜索就好了。

下附AC代码：

```
#include<iostream>
#include<cstring>
using namespace std;
struct edge{
	int to,next;
}e[300010];//邻接表建图
int eid=0;
int head[300010];
int ans[300010];
void insert(int u,int v){
	eid++;
	e[eid].to=v;
	e[eid].next=head[u];
	head[u]=eid;
}
int fa[300010],son[300010],size[300010];//父亲结点
int n,m;
void dfs(int x){//普通的dfs
	size[x]=1;
	for(int i=head[x];i+1;i=e[i].next){
		int k=e[i].to;
		dfs(k);
		size[x]+=size[k];
		if(size[k]>size[son[x]])son[x]=k;
	}
	int k;
	if(size[son[x]]*2>size[x]){//如果这个儿子的结点数超过整个的两倍 
		k=son[x];//找到第一个没超过两倍的子树根节点 
		while((size[x]-size[k])*2>size[x])k=fa[k];
		ans[x]=k;//以它为答案 
	}
	else{
		ans[x]=x;
	}
	return ;
}
int main(){
	memset(head,-1,sizeof(head));
	cin>>n>>m;
	for(int i=2;i<=n;i++){
		cin>>fa[i];
		insert(fa[i],i);
	}
	dfs(1);
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		cout<<ans[x]<<endl;
	}
}
```
一些说明：下文中我的dfs一般会有两个形参，dfs(int x,int fa)分别代表结点与其父节点，两种均可但是下文的更加通用，因为上文中我们并不需要沿着边向上查找，所以说我是建了一个有向树，只能从父亲访问儿子，因此我就不需要在枚举边的时候判断我要去的点是否是父亲，是的话还要跳过。



---

## 作者：BoAn (赞：1)

先来看数据，$q≤3×10^5$，显然不可能边问边搜，所以我们需要预处理出 $focus_x$ 表示以 $x$ 为根的子树的重心。

用 DFS 预处理出 $size_x$，即遍历一遍整棵树求出以 $x$ 为根的子树大小。

从贪心的策略出发，显然以 $x$ 为根的子树的重心只能在其最重的子树上或者 $x$ 本身。定义 $deep_i$ 表示节点 $i$ 的深度，一定有：

$deep_{focus_x}≤deep_{focus_y}$

即以 $x$ 为根的子树重心的深度一定小于等于以 $y$ 为根的子树重心的深度。其中 $y$ 是 $x$ 的重儿子。

为了更方便，再用 $size_x$ 预处理出以 $x$ 为根的子树中最大子树的大小。

以上遍历了整棵树，效率是 $O(n)$。

接下来再从根节点 $1$ 开始，递归求出 $x$ 每一颗子树的重心。但是注意求 $x$ 重心，只从 $x$ 最大的那棵子树的重心开始往上跳，当继续往上跳不如当下的时候停下来，不然可能超时。

特别地，每一个叶子结点的重心是它自己。

因为每次只从重子树的重心往上跳，所以每个点只遍历一次，复杂度是 $O(n)$。

注意是无向图，数组开双倍。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,q,tot,max_part,pos;
int ver[600001],Next[600001],head[300001],size[300001],fa[300001],max_sontree[300001],focus[300001];
bool mark[300001];
void add(int x,int y){
	ver[++tot]=y;
	Next[tot]=head[x],head[x]=tot;
}
void dfs(int x){
	if(size[x])return ;
	size[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(fa[x]==y)continue;
		dfs(y);
		size[x]+=size[y];
	}
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(fa[x]==y)continue;
		max_sontree[x]=max(max_sontree[x],size[y]);
		//求最大子树的大小 
	}
}
void find(int x){
	if(focus[x])return ;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(fa[x]==y)continue;
		find(y);
		//求每颗子树的重心 
		if(size[y]!=max_sontree[x])continue;
		//如果不是重儿子就退出 
		int cnt=focus[y];
		while(cnt){
			int s=max(max_sontree[cnt],size[x]-size[cnt]);
			int t=max(max_sontree[focus[x]],size[x]-size[focus[x]]);
			if(s<t||!focus[x])focus[x]=cnt,cnt=fa[cnt];
			else break;
			//继续往上跳结果更差，退出循环 
		}
	}
}
int main(){
	cin>>n>>q;
	for(int i=2;i<=n;i++){
		int x;
		cin>>x;
		add(x,i);
		add(i,x);
		fa[i]=x; mark[x]=1;
	}
	for(int i=1;i<=n;i++)
		if(!mark[i])focus[i]=i;
		//叶子结点重心是本身 
	dfs(1);
	//预处理 
	find(1);
	for(int i=1;i<=q;i++){
		int root;
		cin>>root;
		cout<<focus[root]<<endl;
	}
	return 0;
}
```


---

## 作者：极寒神冰 (赞：1)

**一个树的重心一定在他所有儿子的子树的重心的连线上。**（可以自己多画几个图来证明

那么先dfs从深度最深的点开始往上爬并更新最优解。如果往上跳的大小反而增大，便可以直接结束。ans[u]记录u为根的重心位置。显然每个点只会被经过一次时间为o(n)

```
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}

const int N=300010;
struct edge
{
	int nxt,to;
}e[N];
int n,m,cnt;
int Fa[N],head[N],sz[N],mx[N],ans[N];
inline void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
inline void dfs(int u,int fa)
{
	
	sz[u]=1;//就自己一个点大小为1
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		dfs(v,u);
		sz[u]+=sz[v];//求子树大小
		mx[u]=max(mx[u],sz[v]);//最大子树的大小
	}
	
	int id=u,famax=mx[u];//起点
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;//当前点儿子
		int bsz=ans[v];//子树的重心
		int pre=max(mx[bsz],sz[u]-sz[bsz]),idd=bsz;
		while(Fa[bsz]!=u)//不能爬到自己
		{
			//往上一直爬
			bsz=Fa[bsz];
			int noww=max(mx[bsz],sz[u]-sz[bsz]);
			if(noww<pre){pre=noww;idd=bsz;}
			else break;//如果大小反而变大了那么这个点一定不是重心了
		}
		//更新
		if(famax>pre)
		{
			famax=pre;
			id=idd;
		}
	}	
	ans[u]=id;//记录u为根的重心
	
}
int main()
{
	init();
	n=read(),m=read();
	for(int i=2;i<=n;i++)
	{
		Fa[i]=read();
		add_edge(Fa[i],i);
	}
	dfs(1,0);
	while(m--)
	{
		int x=read();
		cout<<ans[x]<<endl;
	}
}
```


---

