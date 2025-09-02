# Bear and Drawing

## 题目描述

Limak is a little bear who learns to draw. People usually start with houses, fences and flowers but why would bears do it? Limak lives in the forest and he decides to draw a tree.

Recall that tree is a connected graph consisting of $ n $ vertices and $ n-1 $ edges.

Limak chose a tree with $ n $ vertices. He has infinite strip of paper with two parallel rows of dots. Little bear wants to assign vertices of a tree to some $ n $ distinct dots on a paper so that edges would intersect only at their endpoints — drawn tree must be planar. Below you can see one of correct drawings for the first sample test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573C/3e1f6bfb27269bc2d4c98e1421026d340bfdb0da.png)Is it possible for Limak to draw chosen tree?

## 样例 #1

### 输入

```
8
1 2
1 3
1 6
6 4
6 7
6 5
7 8
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
13
1 2
1 3
1 4
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
No
```

# 题解

## 作者：FreeTimeLove (赞：5)

## 一、结论

设 $P_0=\{p~|~\mathrm{deg}_p\le 2\},P_1=\{p~|~\mathrm{deg}_p=3\},P_2=\{p~|~\mathrm{deg}_p\ge 4\}$。

有合法方案的充要条件是：

存在一条链 $s$ 包含 $P_2$，且 $s$ 的大小为 $1$ 的邻域包含 $P_1$。

等价于存在一条链 $s$ 使得删去 $s$ 后剩下的点构成一个链的集合。

## 二、证明

### 1.充分性

将 $s$ 上的点排在第一行，其邻域上的点排在第二行，邻域上度数为 $3$ 的点的另外两条边分别向左右延伸。可以发现这是一种合法构造。

### 2.必要性

#### I.存在一条链 $s$ 包含 $P_2$

考虑反证法，若不构成一条链，则取一条链放在第一行后仍存在 $p\in P_2$ 与非端点的链上一点相连，而 $p$ 只能向左右延伸两条边，因此不合法。

#### II.$s$ 的大小为 $1$ 的邻域包含 $P_1$

由上可知，$P_2$ 应放在第一行上的链上。若存在 $p\in P_1$ 不在 $s$ 的邻域上，则 $p$ 在第二行上且不与第一行直接相连，因此度数至多为 $2$，不合法。

## 三、实现

首先拎出 $P_2$，判断是否在一条链上，求出链的端点；再从两个端点分别扩展，以最深的 $P_1\cup P_2$ 中的点为新的端点，最后判断其邻域是否包含 $P_1$ 即可。时间复杂度 $O(n)$。

### code

```cpp
/*FreeTimeLove's code.
Love has a nasty habit of disappearing over night.*/
#include<bits/stdc++.h>
namespace chiptune{
#define ll long long
#define LD long double
#define i7 __int128
#define re return
#define con continue
using namespace std;
template<class T>inline bool ckmin(T &a,T b){re b<a?a=b,1:0;}
template<class T>inline bool ckmax(T &a,T b){re a<b?a=b,1:0;}
const int N=1e5+5;
inline ll rd(){
	ll ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
int n,c[N],cnt,a[N],nw;
int nd[N],tt=1;
struct edge{int v,nxt;}e[N<<1];
void add(int u,int v){e[++tt]={v,nd[u]};nd[u]=tt;}
int f[N],d[N];
int clr[N],bk[N];
void dfs(int u,int fa){
	f[u]=fa,d[u]=d[fa]+1;
	for(int i=nd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa)dfs(v,u);
	}
}
void dfs2(int u,int fa,int t){
	bk[u]=t;
	for(int i=nd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa)con;
		dfs2(v,u,t);
	}
}
void dfs3(int u,int fa){
	if(d[u]>d[nw])nw=u;
	for(int i=nd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa)con;
		dfs3(v,u); 
	}
}
int main(){
	n=rd();
	for(int i=1;i<n;i++){
		int u=rd(),v=rd();
		add(u,v),add(v,u),++c[u],++c[v];
	}
	for(int i=1;i<=n;i++)c[i]=c[i]==3?1:(c[i]>3?2:0);
	int rt1=1;
	for(int i=1;i<=n;i++)
		if(c[i]>c[rt1])rt1=i;
	dfs(rt1,0);
	for(int i=1;i<=n;i++)
		if(c[i]==c[rt1]&&d[i]>d[rt1])rt1=i;
	dfs(rt1,0);
	int rt2=rt1;
	for(int i=1;i<=n;i++)
		if(c[i]==c[rt2]&&d[i]>d[rt2])rt2=i;
	dfs(rt2,0);
	{
		int u=rt1;
		while(u)clr[u]=1,u=f[u];//clr
		for(int i=1;i<=n;i++)
			if(c[i]==2&&!clr[i]){puts("No");re 0;}
	}
	if(rt1==rt2){
		for(int i=nd[rt1];i;i=e[i].nxt){
			int v=e[i].v;
			nw=v,dfs3(v,rt1);
			a[++cnt]=nw;
		}
		a[++cnt]=rt1;
		sort(a+1,a+cnt+1,[](int x,int y){re d[x]>d[y];});
		rt1=a[1],rt2=a[2];
	}
	else{
		for(int i=nd[rt1];i;i=e[i].nxt){
			int v=e[i].v;
			if(clr[v])con;
			dfs2(v,rt1,1);
		}
		for(int i=1;i<=n;i++)
			if(bk[i]==1&&c[i]&&d[i]>d[rt1])rt1=i;
		for(int i=nd[rt2];i;i=e[i].nxt){
			int v=e[i].v;
			if(clr[v])con;
			dfs2(v,rt2,2);
		}
		for(int i=1;i<=n;i++)
			if(bk[i]==2&&c[i]&&d[i]>d[rt2])rt2=i;	
	}
	dfs(rt1,0);
	int u=rt2;
	while(u){
		clr[u]=1;
		for(int i=nd[u];i;i=e[i].nxt)clr[e[i].v]=1;
		u=f[u];
	}
	for(int i=1;i<=n;i++)
		if(c[i]&&!clr[i]){puts("No");re 0;}
	puts("Yes");
	re 0;
}
/*


*/
}int main(){re chiptune::main();}
```

> Love has a nasty habit of disappearing over night.




---

## 作者：木xx木大 (赞：3)

[CF573C Bear and Drawing](https://www.luogu.com.cn/problem/CF573C)

**Solution1：**

我们记叶子节点和只有1个①子节点的点为①。

记有且仅有2个①子节点的点为②。

记有且仅有1个③或至少有1个②或至少有3个①的节点为③。

记恰好有2个③和若干小于③的子节点的点为④。记其他的子树为⑤。

只有当根不超过④时，才合法。复杂度是 $O(n)$。

注意：还需要进行一次类似换根的操作，只要有一个点为根时成立就有解。

**Solution2：**（思路来自网上）

通过找规律可以发现,最终的方案一定是一条主干+一些枝条,且这些枝条的分杈一定小于等于2。主干为最左边的节点和最右边的节点之间的路径。

从叶子节点开始，把链剪下来，剩下的不是主干就是分杈点

如果一个点没有被剪下来的邻居只有一个，它就是分叉点或者主干点的两端

如果所有主干点的邻居主干点数都小于等于2就有解


好想但长的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct edg{
	int to,nxt;
}e[N<<1];
int cnt,head[N],n,c[N],sum[N][5],fl;
void add(int u,int v)
{
	cnt++;
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int calc(int u)
{
	if(sum[u][4]||sum[u][5]||sum[u][3]>2)return 5;
	if(sum[u][3]>1)return 4;
	if(sum[u][3]||sum[u][1]>2||sum[u][2])return 3;
	if(sum[u][1]>1) return 2;
	return 1;
}
void dfs1(int u,int f)
{
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f)continue;
		dfs1(v,u);
		sum[u][c[v]]++;
	}
	c[u]=calc(u);
}
void dfs2(int u,int f,int x)
{
	if(fl)return;
	sum[u][x]++;
	if(calc(u)<5)
	{
		fl=1;
		return;
	}
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f)continue;
		sum[u][c[v]]--;
		dfs2(v,u,calc(u));
		sum[u][c[v]]++;
	}
	sum[u][x]--;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	dfs2(1,0,0);
	if(fl)puts("Yes");
	else puts("No");
	return 0;
 } 
```
更简洁但有点抽象的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5; 
int del[N],nei[N],n,mn[N];
vector<int> G[N];
void dfs(int u,int f)
{
	if(G[u].size()<=2)
	{
		del[u]=1;
		for(int i=0;i<G[u].size();i++)
		{
			int v=G[u][i];
			if(v!=f)dfs(v,u);
		}	
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
		if(G[i].size()==1)
			dfs(i,0);
	for(int u=1;u<=n;u++) 
	{
		if(del[u])continue;
		for(int i=0;i<G[u].size();i++)
			if(del[G[u][i]])nei[u]++;
		if(G[u].size()-min(nei[u],2)>1)mn[u]=1;
	}	
	for(int u=1;u<=n;u++) 
	{
		if(mn[u])
		{
			int cnt=0;
			for(int i=0;i<G[u].size();i++)
			{
				int v=G[u][i];
				if(mn[v])cnt++;	
			}
			if(cnt>2)
			{	
				puts("No");
				return 0;
			}
		}	
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：洛谷の老豆 (赞：1)

先考虑确定根，可以发现子树如果是一条链或者子树的根有且仅有两条链，无论如何都可以放在中间，两侧各放不满足上述条件的子树，如果这样的子树超过 $2$ 个则不符合；然后往下遍历两个子树，重复上述操作，但此后只能在一侧放不满足上述条件的子树了。

暴力时间复杂度为 $O(n^2)$，无法接受。

考虑换根，除了根和儿子，其他点都不会变动，于是可以换根来做。

时间复杂度为 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define inf 1000000007
#define N 200005
using namespace std;
long long read()
{
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1ll)+(x<<3ll)+ch-48,ch=getchar();
	return x*f;
}
void write(long long x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int n,m,sz[N],lk[N],sp[N],ok[N],numok[N],fa[N],son[N],r[N],ans,cld[N][3],lll[N];
int h[N],cnt;
struct node
{
	int next,to;
}e[N<<1];
void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].next=h[x];
	h[x]=cnt;
}
void dfs(int x)
{
	//cld[x][3]={0,0};
	ok[x]=1;
	for(int i=h[x];i;i=e[i].next)
	{
		r[x]++;
		int y=e[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		dfs(y);
		son[x]++;
		if(!cld[x][0])cld[x][0]=y;
		else if(!cld[x][1])cld[x][1]=y;
		else if(!cld[x][2])cld[x][2]=y;
		sp[x]+=(!lk[y]);
		ok[x]&=ok[y];
		numok[x]+=ok[y];
	}
	if(x==1)ok[x]&=(sp[x]<=2);
	else ok[x]&=(sp[x]<=1);
	if(!son[x]||(son[x]==1&&lll[cld[x][0]])||(son[x]==2&&lll[cld[x][0]]&&lll[cld[x][1]]))
	{
		lk[x]=1;
	}
	if(!son[x]||(son[x]==1&&lll[cld[x][0]]))
	{
		lll[x]=1;
	}
}
void dp(int x)
{
	int tempx=sp[x],okx=ok[x],numokx=numok[x],lkx=lk[x],lllx=lll[x];
	if(ok[x])
	{
		ans=1;return;
	}
	int child[3]={0,0,0};
	for(int i=h[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if(!child[0])child[0]=y;
		else if(!child[1])child[1]=y;
		else if(!child[2])child[2]=y;
		else break;
	}
	for(int i=h[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if(y==fa[x])continue;
		int tempy=sp[y],oky=ok[y],numoky=numok[y],lky=lk[y],llly=lll[y];
		numok[x]-=ok[y];sp[x]-=(!lk[y]);
		if(numok[x]==r[x]-1&&sp[x]<=1)ok[x]=1;
		if(r[x]==1)lk[x]=1;
		else if(r[x]<=3)
		{
			lk[x]=1;
			if(child[0]&&child[0]!=y)lk[x]&=lll[child[0]];
			if(child[1]&&child[1]!=y)lk[x]&=lll[child[1]];
			if(child[2]&&child[2]!=y)lk[x]&=lll[child[2]];
		}
		else lk[x]=0;
		if(r[x]==1)lll[x]=1;
		else if(r[x]==2)
		{
			int k=child[0]==y?child[1]:child[0];
			lll[x]=lll[k];
		}else lll[x]=0;
		numok[y]+=ok[x];sp[y]+=(!lk[x]);
		if(numok[y]==r[y]&&sp[y]<=2)ok[y]=1;
		else ok[y]=0;
		if(!son[y])lk[y]=1;
		else if(son[y]==1)
		{
			lk[y]=lll[x]&lll[cld[y][0]];
		}
		else lk[y]=0;
		if(!son[y])lll[y]=1;
		else lll[y]=0;
		dp(y);
		sp[x]=tempx,ok[x]=okx,numok[x]=numokx,lk[x]=lkx,lll[x]=lllx;
		sp[y]=tempy,ok[y]=oky,numok[y]=numoky,lk[y]=lky,lll[y]=llly;
		if(ans)return;
	}
}
int main()
{
	n=read();
	for(int i=1,x,y;i<n;i++)
	{
		x=read(),y=read();
		add(x,y);add(y,x);
	}	
	dfs(1);
	dp(1);
	if(ans)printf("Yes\n");
	else printf("No\n");
	return 0;
}

```



---

## 作者：Star_Cried (赞：1)

## CF573C Bear and Drawing

思维题。码量很小。

考虑一个决定性的节点$x$，这棵树无解当且仅当这个节点$x$有多于2个至少满足以下条件之一的相邻节点：

* 含有不少于3个除了x节点其他相邻节点。
* 含有至少一个除了x节点其他相邻的**子树不为一条链**的节点。

有亿点点绕，我们考虑将每个具有特殊性质的点分类标号。

******************

我们定义：

* **一类节点** 度为1的节点（即只有一个节点与之连边）和**度不多于2且至少有一个相邻节点为一类节点的节点**为一类节点。
* **二类节点** 度多于2或**度为2且至少有一个相邻节点为二类节点的节点**为二类节点。
* **三类节点** 度多于3或**度为3且至少有两个相邻节点为二类节点的节点**为三类节点。
* **四类节点** 相邻节点含有多于2个三类节点的节点。

其中当且仅当图中有四类节点时无解。

****

### 正确性证明

考虑对于一个节点x，我们想象一下x无解的情况：为什么有多于两个三类节点就无解？

参考三类节点的定义，三类节点无法仅在一行内存在，即必须向两边延伸。因为这个纸条的特性，只能向两个方向无限延伸，所以对于每个节点x都最多支持与两个三类节点相邻。

而对于二类节点，发现这种节点是可以在仅一行中存在的。又因为纸条是无限的，所以含多少个二类节点并不会造成影响。

### 充分性证明

~~我找不到更多的无解条件了~~

发现如果对于每个节点都满足不为四类节点上面就一定有解。

### 实现

因为高级节点是由低级节点定义转移而来，我们每次从低级到高级找节点就行了。

~每个点dfs一遍显然爆炸~

具体细节请查看代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<vector>
using namespace std;
inline int read(){
	int x=0,w=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e5+10;
	int del[maxn],nei[maxn],n;
	vector<int> G[maxn];
	void dfs(int x,int f){
		if(G[x].size()<=2){
			del[x]=1;
			for(int i=0;i<G[x].size();i++){
				int u=G[x][i];
				if(u==f)continue;
				dfs(u,x);
			}
		}
	}
	inline void work(){
		n=read();
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for(int i=1;i<=n;i++)
			if(G[i].size()==1)dfs(i,0);//找到所有一类节点
		for(int x=1;x<=n;x++)
			for(int i=0;i<G[x].size();i++)
				if(del[G[x][i]])nei[x]++;//nei是neighbor的意思XD记录相邻节点为一类节点的个数
		for(int x=1;x<=n;x++){
			int cnt=0;
			for(int i=0;i<G[x].size();i++){
				int u=G[x][i];
				if(!del[u] and G[u].size()-min(nei[u],2)>1)cnt++;//找三类节点
                //这一段其实将两个条件同时判断了：连接至少一个二类节点条件为G[u].siz-nei[u]>1
                //或连接多于两个一号节点条件为G[u].siz-2>1
                //所以两个条件并起来就是G[u].size()-min(nei[u],2)>1
			}
			if(cnt>2)return (void)puts("No");//发现了四类节点
		}
		puts("Yes");
	}
}
signed main(){
	star::work();
	return 0;
}
```

鸣谢：@[**木xx木大** ](https://www.luogu.com.cn/user/224403)提供思路



---

