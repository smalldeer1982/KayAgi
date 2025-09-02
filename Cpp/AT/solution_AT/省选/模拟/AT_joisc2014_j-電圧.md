# 電圧

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_j



# 题解

## 作者：Starlight_Glimmer (赞：5)

[My Blog](https://www.cnblogs.com/lyttt/p/14068976.html)

[题目链接](https://loj.ac/p/2881)

### 题目解析

如果对每一条边都尝试染色的话，复杂度显然不可过。

考虑从宏观上大局考虑。~~（这句话怎么这么别扭，是我语文太菜了~~

如果图中有奇环，那么奇环上的边必须被选，否则如果选了其它的边，奇环上的边就一定有一条左右端点颜色一样。

同样考虑偶环，我们发现偶环上的边必须不被选，否则如果选了偶环上的边，那么偶环上一定有一条边左右端点颜色一样。

总结一下，就是：
如果没有奇环，那么偶环以外的边可以随便选。

如果有奇环，那么能选的边就是所有奇环上的边的交集，并且不在偶环上。

不过，在偶环上的边一定不在奇环上，因为如果一条边既在偶环上，又在奇环上，那通过这条边相连的奇环和偶环可以组成一个更大的奇环（可以画图看一下），而这条边不在这个更大的奇环上。（当然，我的做法判不了这个更大的奇环，所以需要判偶环）

算了，还是画个图：（这个图可能要先看一下下面的具体做法再来看





![](https://img2020.cnblogs.com/blog/1472744/202012/1472744-20201201161803110-519198521.png)

![](https://img2020.cnblogs.com/blog/1472744/202012/1472744-20201201161812271-375876117.png)



（可以看到从树上下下来长这样，可以更直观地看到$2-3$边一定不在大奇环$1-2-5-4-3-1$上

可以用$dfs$序解决这个问题，如果搜到一条返祖边就说明成环了，而我们可以通过$Δdep$判断是偶环还是奇环，然后树上差分就可以算出这条边在多少个奇环/偶环上。

最后统计答案找到所有奇环覆盖数$==$奇环总数，并且不在偶环上的边的总数。

注意一下，我们在算答案的时候是没有考虑返祖边的，因为如果有$2$个以上的奇环，那么这两条返祖边都不在一起，肯定不在交集里面。但是，如果只有一个奇环的话，这条返祖边是可行的，所以答案要$+1$。

最后再注意一下程序写法，是差分边，不是差分点，注意一下细节。

------

### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
#define N 100005
#define M 200005
#define MOD 998244353
#define INF 0x3f3f3f3f
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48); c=getchar();}
	return f*x;
}
struct node{
	int nxt,v;
}e[M<<1];
int hd[N],cnt=1;
void add(int u,int v)
{
	e[++cnt].nxt=hd[u],e[cnt].v=v;
	hd[u]=cnt;
}

int n,m;
bool vis[N],rt[N];
int dep[N],sum[N][2]/*差分数组 标记这个点头上的那条边 注意是边*/,tot/*奇环个数*/;
int f[N];//记录这个点头上的边的编号 
void dfs(int u)
{
	vis[u]=1;
	for(int i=hd[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		//if(v==fa) continue;
		if(i==f[u]||(i^1)==f[u]) continue;
		if(vis[v])//返祖边
		{
			if(dep[v]>dep[u]) continue;//走到了返祖边的反向边 
			int d=(dep[u]-dep[v])&1;
			sum[u][d]++,sum[v][d]--;
			if(!d) tot++;
		} 
		else
		{
			f[v]=i;
			dep[v]=dep[u]+1;
			dfs(v);
			sum[u][0]+=sum[v][0],sum[u][1]+=sum[v][1];//差分合并 
		}
	}
}
int main()
{
	n=rd(),m=rd();
	for(int i=1;i<=m;i++)
	{
		int u=rd(),v=rd();
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]) 
		{
			rt[i]=1;
			dfs(i);
		}
	int ans=0;
	//printf("%d\n",tot);
	//for(int i=1;i<=n;i++)
	//	printf("%d\n",sum[i][1]);
	for(int i=1;i<=n;i++)
		if(sum[i][0]==tot&&!sum[i][1]&&!rt[i])//在所有奇环上 不在任何偶环上 并且不是根(根头顶上没有边
			ans++;
	if(tot==1) ans++;//只有一个奇环 那么那条返祖边也要算上 
	printf("%d\n",ans); 
	return 0;
}
/*
因为这道题是按边算 可能会有重边 所以只能写前向星 按边来
主要是v==fa那里的判断 不能判断是不是父节点 而要判是不是当初来的那条边或它的反向边 
样例2就可以帮助理解这种情况 
*/
```

---

## 作者：Azazеl (赞：4)

#### 题意

> 给定了一张图，求该图有多少条边满足删掉它后图变为二分图，且删去的边的两点在二分图中要在同一部中。  

#### 题解

$~~~~$ 首先二分图的判定条件是图中没有 **奇环**，因此我们首先需要删去某条边后图上没有奇环。   

$~~~~$ 那么我们求出所有奇环的边的交即可，然后还要使得这些边不能在偶环上，因为若一个奇环与偶环有交那么它们即使删去相交的边也还是有一个更大的奇环；或者原图没有奇环，即原图就是二分图，那么删去这条边后二分图的染色方案仍和原来一样，此时删去的边的两端分属两部，这也是不合法的。

$~~~~$ 那我们如何求出每条边在多少奇环和偶环上？

$~~~~$ 考虑建出原图的DFS树，然后考虑每条返祖边的贡献

- 若环上只有一条返祖边：

  - 若该环为奇环，这个环上所有树边都是在奇环中的。（由于有多个返祖边）
   - 若该环为偶环，那么同上。

- 若环上有2+返祖边，显然两条返祖边有两个小环，且两条返祖边的点经过的树边一定**有交**，否则就会有一条树边被经过两次，这样就没有简单环了。而两条返祖边形成的大环可以再与其他返祖变组成环，因此我们证两条返祖边的情况然后进行归纳即可。

  - 若两个环分别为奇环和偶环，那么它们形成了一个大奇环，此时大奇环上的树边全部少统计了一遍，但我们也没有数这个奇环，所以不统计小奇环上的树边没有影响，而偶环上的统计过显然也不会成为答案，因此对答案没有影响。
  - 若两个都是奇环，那么它们的交是不在形成的大偶环上的，而其他在大偶环上的边至少不在一个奇环上，本身就不会被统计入答案里面，因此对答案没有影响。
  - 若两个都是偶环，那么显然本身都不会被计入答案，自然形成大偶环也对答案没有影响。

  ~~综上，做题当时少考虑这种情况但对答案没有影响。.~~

$~~~~$ 然后只有一条返祖边的情况边差分做即可，一遍DFS即可。

$~~~~$ 注意只有一个奇环时那条返祖边也是合法的。

$~~~~$ 时间复杂度 $\mathcal{O(n)}$ 。

#### 代码

```cpp
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>
#define mp(a,b) make_pair(a,b)
using namespace std;
bool vis[100005];
int fa[1000005],cnt[100005][2],dep[100005],jh;
vector < pair<int,int> >G[100005];
void dfs(int u,int d)
{
	dep[u]=d;
	vis[u]=true;
	for(int i=0;i<G[u].size();i++)
	{
		int v=G[u][i].first,w=G[u][i].second;
		if(w==fa[u]) continue;
		if(vis[v])
		{
			if(dep[v]>dep[u]) continue;
			int k=(dep[u]-dep[v])&1;
			if(k==0) jh++; 
			cnt[u][k]++;
			cnt[v][k]--;
		}
		else
		{
			fa[v]=w;
			dfs(v,d+1);
			cnt[u][0]+=cnt[v][0];cnt[u][1]+=cnt[v][1];
		}
	}
} 
int main() {
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d %d",&u,&v);
		G[u].push_back(mp(v,i));
		G[v].push_back(mp(u,i));
	}
	for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,0);
	int Ans=0;
//	for(int i=1;i<=n;i++) printf("odd=%d even=%d\n",cnt[i][0],cnt[i][1]);
	for(int i=1;i<=n;i++)
	{
		if(fa[i]&&cnt[i][0]==jh&&!cnt[i][1]) Ans++;
	}
	printf("%d\n",Ans+(jh==1));//AT上记得换行
	return 0;
}
```



---

## 作者：GoPoux4 (赞：1)

_推销博客：https://www.cnblogs.com/syc233/p/13647723.html_

---

#### 题意

给定$n$ 个点 $m$ 条边的无向图，现在要对每个点黑白染色。

若能够使一条边连接的两点颜色相同，其他边连接的两点颜色不同，则这条边合法。

求合法的边数。

$2 \leq n \leq 10^5,1 \leq m \leq 2 \cdot 10^5$

图可能不连通，不保证没有重边。

---

#### 题解

删去边后图能够二染色，则这条边合法的必要条件是删边后的图是二分图，即没有奇环。那么合法的边必然在所有奇环上。

又因为偶环上的点一定是黑白交替出现，所以合法边必然不在偶环上。

不难想到对这个无向图求 DFS 树，再进行树上差分即可求出每一条树边在几个奇环和偶环中出现。

对于非树边（返祖边），分类讨论：

* 若图中只有一个奇环，则这个奇环对应的非树边合法。

* 若图中有不止一个奇环，再分类讨论：
  * 若有两个奇环相交，则这两个环会构成一个大环，并且这个大环一定是偶环，则两个奇环的返祖边均不合法。
  * 若有两个奇环不相交，则没有边同时处于这两个奇环，返祖边显然也不合法。

所以求出树边上合法边的总数，再判断奇环是否只有一个即可。

---

$\text{Code}:$

```cpp
#include <cstdio>
#define maxn 100005
#define maxm 200005
#define Rint register int
#define INF 0x3f3f3f3f
using namespace std;
typedef long long lxl;

template <typename T>
inline void read(T &x)
{
	x=0;T f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	x*=f;
}

struct edge
{
	int u,v,next;
	edge(int u,int v,int next):u(u),v(v),next(next){}
	edge(){}
}e[maxm<<1];

int head[maxn],k;

inline void add(int u,int v)
{
	e[k]=edge(u,v,head[u]);
	head[u]=k++;
}

int n,m;
int dep[maxn];
bool vis[maxm];
int odd[maxn],oddcnt;
int eve[maxn],evecnt;

inline void dfs(int u,int fa)
{
	vis[u]=true;
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if((i^1)==fa) continue;
		if(!vis[v])
		{
			dep[v]=dep[u]+1;
			dfs(v,i);
			eve[u]+=eve[v];
			odd[u]+=odd[v];
		}
		else if(dep[v]<dep[u])
		{
			if((dep[u]-dep[v])&1)
				++evecnt,++eve[u],--eve[v];
			else
				++oddcnt,++odd[u],--odd[v];
		}
	}
}

int main()
{
	// freopen("AT1226.in","r",stdin);
	read(n),read(m);
	for(int i=1;i<=n;++i) head[i]=-1;
	for(int i=1,u,v;i<=m;++i)
	{
		read(u),read(v);
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;++i)
		if(!vis[i]) dfs(i,-1);
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		if(!dep[i]) continue;
		ans+=(!eve[i]&&odd[i]==oddcnt);
	}
	ans+=(oddcnt==1);
	printf("%d\n",ans);
	return 0;
}
```


---

