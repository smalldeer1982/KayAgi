# [BalticOI 2020] 村庄 (Day2)

## 题目背景

# 请用 C++14/C++17 提交以避免不必要的 CE

## 题目描述

村庄有 $N$ 个房子，之间有 $N-1$ 条道路连接，每条道路长度为 $1$。

在最开始，第 $i$ 个村民就在第 $i$ 号房子里，房子从 $1$ 到 $N$ 编号。

有一天，村民们突然突发奇想，想搬到别的房子中，村民们希望，在搬迁过后，不存在一位村民住在他原来居住的房子中。

求所有村民在新旧房屋之间的最小总距离值和最大总距离值。

## 说明/提示

#### 评分方式

本题分为两个任务：

- 求解最小距离和，并给出一种相应的合法方案；
- 求解最大距离和，并给出一种相应的合法方案；

每成功完成一个任务，您就可以获得该测试点 $50\%$ 的分数。

您在一个子任务的得分，等于你在该子任务所有测试点的最低得分。

请注意，即使您不会求解某个子任务，也请按照要求的输出格式进行输出，否则 checker 将无法正确评分。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（12 pts）：$N \le 10$。
- Subtask 2（38 pts）：$N \le 1000$。
- Subtask 3（50 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N \le 10^5$，$1 \le a,b \le N$。

**本题使用 Special Judge。**

## 样例 #1

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
4 8
2 1 4 3
4 3 2 1```

## 样例 #2

### 输入

```
7
4 2
5 7
3 4
6 3
1 3
4 5```

### 输出

```
8 18
6 4 1 2 7 3 5
7 3 4 1 2 5 6```

# 题解

## 作者：王奕清 (赞：6)

提供一种**十分简单**的做法：

我们先把村庄看成一个个节点，然后就是对每个点找一个不同的节点去移动，贡献是两个节点之间的距离，问可能贡献的**最大值**和**最小值**，以及方案。

首先考虑最小值：

对于一个子树的根节点，他的每个儿子最多只会上传自己这一个节点来请求移动，原因等下再说，然后：

1.如果我的儿子中有需要匹配的，那么就把我和他们放到一个环上，第$i$个需要匹配的儿子向第$i+1$个要匹配的儿子移动，然后最后一个儿子向根移动，根向第一个儿子移动。贡献+=2\*儿子数

2.如果没有要匹配的，就把我上传。

所以每个儿子最多上传一个节点，但是，根节点不能上传，那我们就判断一下，如果他没有移动过，就把他放到他第一个儿子的环中，具体实现细节可以看代码

```
void dfs1(int x,int y)
{
	vector<int>p;
	for(int i=0;i<v[x].size();i++)
	{
		int h=v[x][i];
		if(h==y)continue;
		dfs1(h,x);
		if(!a1[h])p.push_back(h);//需要上传
	}
	if(p.empty())return;//情况2
	for(int i=0;i<p.size()-1;i++)a1[p[i]]=p[i+1];
	a1[p.back()]=x,a1[x]=p.front(),s1+=2*p.size();
}
void work1()
{
	dfs1(1,0);
	if(!a1[1])a1[1]=a1[v[1][0]],a1[v[1][0]]=1,s1+=2;
}
```

再考虑最大值：

一句话，以任一点为根，求出dfs序，然后每个节点向dfs序比自己大n/2的节点移动。
```
void dfs2(int x,int y)
{	
	dfn[++*dfn]=x;
	sz[x]=1;
	for(int i=0;i<v[x].size();i++)
	{
		int h=v[x][i];
		if(h==y)continue;
		dfs2(h,x);
		sz[x]+=sz[h];
	}
	s2+=2*min(n-sz[x],sz[x]);
}
void work2()
{
	dfs2(1,0);
	for(int i=1;i<=n;i++)a2[dfn[i]]=dfn[(i+n/2-1)%n+1];
}
```
为什么这么简单呢，具体原因有点玄学，因为树中必定有一个重心，
而贡献要最大，那么对于以重心为根的树来说，每个点一定要向和自己不在一个子树的点移动（这里的子树是指重心的子树，即失去重心后，树会被分成几个联通块），那么如果当前我选的这个根不是重心，那么对于一个重心来说，他的父亲以上的那些点一定<n/2个，所以我的dfs序+n/2后，一定不在某一个同样的子树中。

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 100005
int n,x,y,a1[N],s1,a2[N],dfn[N],sz[N],s2;
vector<int>v[N];
void dfs1(int x,int y)
{
	vector<int>p;
	for(int i=0;i<v[x].size();i++)
	{
		int h=v[x][i];
		if(h==y)continue;
		dfs1(h,x);
		if(!a1[h])p.push_back(h);
	}
	if(p.empty())return;
	for(int i=0;i<p.size()-1;i++)a1[p[i]]=p[i+1];
	a1[p.back()]=x,a1[x]=p.front(),s1+=2*p.size();
}
void work1()
{
	dfs1(1,0);
	if(!a1[1])a1[1]=a1[v[1][0]],a1[v[1][0]]=1,s1+=2;
}
void dfs2(int x,int y)
{	
	dfn[++*dfn]=x;
	sz[x]=1;
	for(int i=0;i<v[x].size();i++)
	{
		int h=v[x][i];
		if(h==y)continue;
		dfs2(h,x);
		sz[x]+=sz[h];
	}
	s2+=2*min(n-sz[x],sz[x]);
}
void work2()
{
	dfs2(1,0);
	for(int i=1;i<=n;i++)a2[dfn[i]]=dfn[(i+n/2-1)%n+1];
}
signed main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	work1(),work2();
	printf("%lld %lld\n",s1,s2);
	for(int i=1;i<=n;i++)printf("%lld ",a1[i]);puts("");
	for(int i=1;i<=n;i++)printf("%lld ",a2[i]);
}
```

---

## 作者：7KByte (赞：0)

有删减，原文见[**我的博客**](https://www.cnblogs.com/SharpnessV/p/14872855.html)。

值得一想的构造题（评分虚低？

先考虑第一问，求总代价最小。

对于叶子节点，它可以和它的父节点交换。

但是它有的兄弟节点是叶子，而父节点只有一个。

我们将所有兄弟节点排成一行，那么第 $i$ 个点移动到第 $i+1$ 个节点，父节点移动到第 $1$ 个节点，最后一个节点移动到父节点。这正好是一个满足条件的偏序。手算一下也不难得到如果有节点移动到父节点和兄弟节点之外的节点，一定不会使答案更优。

第二问，求总代价最大。

考虑对每条边计算贡献，假设一条边两侧的子树大小分别为 $sz_a,sz_b$ ，那么对这条边对答案的最大贡献为 $2\times \min\{sz_a,sz_b\}$ 。

很好理解，如果两侧子树相等，则两两互换可以卡满上线。否则最多互换 $\min$ 对，贡献为两倍 $\min$ 。

所以我们想着构造一种方案使得每条边都达到上线。

如果存在一条边，两侧子树大小都是 $\dfrac{n}{2}$ ，那么两两配对即可。

但是这样的边不一定存在。$\dfrac{n}{2}$ 这个数提供了一个新的思路，我们可以考虑割掉一个点，那么重心无疑是最优的选择，对于割掉重心后每棵子树的大小都不大于 $\dfrac{n}{2}$ 。

那么这就是一个经典问题！我们一定可以两两配对使得每一对的两个点属于不同的子树。

用堆维护当前最大的子树，每次选择最大的子树和次大的子树中个一个点配对即可。注意 $n$ 为奇数时需要特判。

时间复杂度 $\mathcal{O}(N\log N)$ 。

---

## 作者：极寒神冰 (赞：0)

**求最小总距离**：

因为每个村民都需要搬到一个新的地方，考虑从叶子上开始移动。

如果当前叶子上的村民还没有移动过，就将其与他的邻居交换上，答案+2并将其从树上删除（打标记即可）。如果最后还剩下一个村民，随便找他旁边的一个邻居交换即可。

**求最大总距离**：

首先考虑每条边两个方向上有多少村民可以穿过这条边。

考虑一条边$(u,v)$，则能通过的最大人数为$\min(subtreeSize(u),subtreeSize(v))$

而理论上的最大值即对于每条边计算最大人数之和。

考虑找出树的重心，只需要排列邻居子树中的所有节点的重心本身就不会再有节点位于以前的子树中了。（具体就是将每个节点向dfs序比自己大n/2的节点移动。）因为此时因为没有一个子树大于其他子树的总和，并保证了最大数量的村民将通过每条边。

```c++
ll nebs[N];
int deg[N];
int n;
int siz[N],place[N];
int lef[N],tot_lef;
int hson[N];
namespace mindis
{
	int ans=0;
	int mian()
	{
		R(i,0,n-1)
		{
			int v=lef[i];					
			if(place[v]==v) 
			{			
				ans+=2;
				int u=nebs[v];
				if(u>0) 
				{
					place[v]=place[u];
					place[u]=v;
				}
				else
				{
					int j=i,z;
					do
					{
						j--;
						z=lef[j];
					}while(j>0&&nebs[z]^v);
					place[v]=place[z];
					place[z]=v;
				}
			} 
		}
		return ans;
	}
	inline void print() {R(i,1,n)writesp(place[i]);puts("");}
}
namespace maxdis
{
	int ans=0;
	int groupSiz[N],group[N],place2[N],cnt[N],ord[N];
	int mian() 
	{
   		R(i,1,n) ans+=2*min(siz[i],n-siz[i]);
		int u=1,uu=1;
		//R(i,1,n) printf("hson:%d\n",hson[i]);
		do
		{
			u=uu;
			if(siz[u]<(n+1)/2) uu=nebs[u];
			else if(siz[u]>n/2&&hson[u]&&siz[hson[u]]>n/2) uu=hson[u]; 
			//printf("u:%d %d\n",u,uu);
		}while(u^uu);
		//printf("u:%d uu:%d\n",u,uu);
		int nextGroup=1;
		L(i,0,n-1) 
		{
			int v=lef[i];//printf("v:%d\n",v);
			if((v==u)||(nebs[v]==u)) group[v]=++nextGroup;
			else if(nebs[v]>0) group[v]=group[nebs[v]];
			else group[v]=1;
			groupSiz[group[v]]++;
		}	
		//R(i,0,n) printf("g:%d\n",group[i]);
		R(i,1,nextGroup) groupSiz[i]+=groupSiz[i-1]/*,printf("f:%d\n",groupSiz[i])*/;
		R(i,1,n) ord[groupSiz[group[i]-1]+cnt[group[i]]]=i,cnt[group[i]]++;
		R(i,0,n-1) place2[ord[i]]=ord[(i+n/2)%n];
		return ans;
	}
	inline void print() {R(i,1,n)writesp(place2[i]);puts("");}
}
signed main()
{
	n=read();
	int u,v;
	R(i,2,n) 
	{
		u=read(),v=read();
		deg[u]++,deg[v]++;
		nebs[u]+=v,nebs[v]+=u;
	}	
	R(i,1,n) 
	{
		siz[i]=1;place[i]=i;
		if(deg[i]==1) lef[tot_lef++]=i;
	}
	siz[0]=-inf;
	for(int i=0;i<tot_lef;i++) 
	{
		int v=lef[i];
		int u=nebs[v];
		if(u>0) 
		{
			hson[u]=(siz[hson[u]]<siz[v])?v:hson[u];
			siz[u]+=siz[v];
			deg[u]--;
			nebs[u]-=v;
			if(deg[u]==1) lef[tot_lef++]=u;
		}
	}
	writesp(mindis::mian());
	writeln(maxdis::mian());
	mindis::print(),maxdis::print();
}
```



---

