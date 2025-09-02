# Jeremy Bearimy

## 题目描述

Welcome! Everything is fine.

You have arrived in The Medium Place, the place between The Good Place and The Bad Place. You are assigned a task that will either make people happier or torture them for eternity.

You have a list of $ k $ pairs of people who have arrived in a new inhabited neighborhood. You need to assign each of the $ 2k $ people into one of the $ 2k $ houses. Each person will be the resident of exactly one house, and each house will have exactly one resident.

Of course, in the neighborhood, it is possible to visit friends. There are $ 2k - 1 $ roads, each of which connects two houses. It takes some time to traverse a road. We will specify the amount of time it takes in the input. The neighborhood is designed in such a way that from anyone's house, there is exactly one sequence of distinct roads you can take to any other house. In other words, the graph with the houses as vertices and the roads as edges is a tree.

The truth is, these $ k $ pairs of people are actually soulmates. We index them from $ 1 $ to $ k $ . We denote by $ f(i) $ the amount of time it takes for the $ i $ -th pair of soulmates to go to each other's houses.

As we have said before, you will need to assign each of the $ 2k $ people into one of the $ 2k $ houses. You have two missions, one from the entities in The Good Place and one from the entities of The Bad Place. Here they are:

- The first mission, from The Good Place, is to assign the people into the houses such that the sum of $ f(i) $ over all pairs $ i $ is minimized. Let's define this minimized sum as $ G $ . This makes sure that soulmates can easily and efficiently visit each other;
- The second mission, from The Bad Place, is to assign the people into the houses such that the sum of $ f(i) $ over all pairs $ i $ is maximized. Let's define this maximized sum as $ B $ . This makes sure that soulmates will have a difficult time to visit each other.

What are the values of $ G $ and $ B $ ?

## 说明/提示

For the sample test case, we have a minimum sum equal to $ G = 15 $ . One way this can be achieved is with the following assignment:

- The first pair of people get assigned to houses $ 5 $ and $ 6 $ , giving us $ f(1) = 5 $ ;
- The second pair of people get assigned to houses $ 1 $ and $ 4 $ , giving us $ f(2) = 6 $ ;
- The third pair of people get assigned to houses $ 3 $ and $ 2 $ , giving us $ f(3) = 4 $ .

Note that the sum of the $ f(i) $ is $ 5 + 6 + 4 = 15 $ .

We also have a maximum sum equal to $ B = 33 $ . One way this can be achieved is with the following assignment:

- The first pair of people get assigned to houses $ 1 $ and $ 4 $ , giving us $ f(1) = 6 $ ;
- The second pair of people get assigned to houses $ 6 $ and $ 2 $ , giving us $ f(2) = 14 $ ;
- The third pair of people get assigned to houses $ 3 $ and $ 5 $ , giving us $ f(3) = 13 $ .

Note that the sum of the $ f(i) $ is $ 6 + 14 + 13 = 33 $ .

## 样例 #1

### 输入

```
2
3
1 2 3
3 2 4
2 4 3
4 5 6
5 6 5
2
1 2 1
1 3 2
1 4 3
```

### 输出

```
15 33
6 6
```

# 题解

## 作者：万弘 (赞：10)

[本场比赛完整题解](https://www.luogu.com.cn/blog/c2522943959/cf1281round-607-div-2-ti-xie)
### E - Jeremy Bearimy
题意:给一棵有边权树,树上有$2k$个点.  
定义$G=$任意选k组无重复的点(每组点两个点),每组点的距离和的**最小值**,$B=$任意选k组无重复的点(每组点两个点),每组点的距离和的**最大值**.求$G,B$  
$k\le 10^5$

考虑贪心.首先$G,B$分开求没有任何问题.

求$G$:举个例子:

![](https://cdn.luogu.com.cn/upload/image_hosting/b1jxronm.png)

图示是最优的方案(之一).  
我们得到结论:要尽可能的让没有的使用过的儿子们互相匹配,有剩余的和当前点匹配,没有剩余就把当前点留给以后的点,因为点有$2k$个所以最后恰好匹配完.  
证明:反证法.假设我们明明能匹配却要留给上面,比如在上面的图中,把2,6都留给上面,那么我们得到:
![](https://cdn.luogu.com.cn/upload/image_hosting/vwzhrbqv.png)

两种选法的唯一区别是,下面的选法中,边(2,5)被选择了两次,而上面的选法没有用到(2,5)所以更优
代码:
```cpp
ll n,ans,size[MAXN];//size[u]表示u的子树大小
void dfs1(ll u,ll fa=0)
{
	size[u]=1;
	for(ll i=last[u];i;i=e[i].nxt)
	{
		ll v=e[i].v;
		if(v==fa)continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]&1)ans+=e[i].w;//size[v]&1那么v就会被剩下,这一次就要选上
	}
}
```
接下来求$B$.与$G$不同,我们要求最大值,那么就让每一条边都经过尽可能多次.
而对于$(fa[u],u)$,下面有$size[u]$个点,上面有$n-size[u]$个点,这条边就最多被经过$min(size[u],n-size[u])$次(理解也可以看上面那个图,我就不展开讲了)
```cpp
void dfs2(ll u,ll fa=0)
{
	for(ll i=last[u];i;i=e[i].nxt)
	{
		ll v=e[i].v;
		if(v==fa)continue;
		dfs2(v,u);
		ans+=min(size[v],n-size[v])*e[i].w;//这条边的贡献
	}
}
```
时间复杂度显然$O(k)$  
最后完整代码奉上(其实也不完整,省略了快读之类)
```cpp
/**********/
#define MAXN 200011
struct Edge
{
	ll v,w,nxt;
}e[MAXN<<1|1];
ll cnt=0,last[MAXN];
void adde(ll u,ll v,ll w)
{
	++cnt;
	e[cnt].v=v,e[cnt].w=w;
	e[cnt].nxt=last[u],last[u]=cnt;
}
 
ll n,ans,size[MAXN];
void dfs1(ll u,ll fa=0)
{
	size[u]=1;
	for(ll i=last[u];i;i=e[i].nxt)
	{
		ll v=e[i].v;
		if(v==fa)continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]&1)ans+=e[i].w;
	}
}
void dfs2(ll u,ll fa=0)
{
	for(ll i=last[u];i;i=e[i].nxt)
	{
		ll v=e[i].v;
		if(v==fa)continue;
		dfs2(v,u);
		ans+=min(size[v],n-size[v])*e[i].w;
	}
}
int main()
{
	ll task=read();
	while(task--)
	{
		n=read()<<1;//有2k个点
		for(ll i=1;i<n;++i)
		{
			ll u=read(),v=read(),w=read();
			adde(u,v,w),adde(v,u,w);
		}
		ans=0;
		dfs1(1);
		printf("%lld ",ans);
		ans=0;//注意ans要清零
		dfs2(1);
		printf("%lld\n",ans);
		for(ll i=1;i<=n;++i)last[i]=0,size[i]=0;//多测不清空..咳咳
		cnt=0;
	}
	return 0;
}
```

---

## 作者：Caicz (赞：6)

### [在博客食用体验更佳](https://www.luogu.com.cn/blog/224229/solution-cf1280c)
### [题目链接](https://www.luogu.com.cn/problem/CF1280C)

------------
题目是求在一棵树上，选取的每一对点之间的路径的和的**最大值**和**最小值**，所以我们先分开讨论

#### 最小值
对于最小值，即每条边的使用次数最小，那么对于以$u$为根节点的一棵树,设$v$是与它相连的子树的根，那么可以得到： **当子树的size为偶数时，我们完全可以让子树自己内部消化，而当子树的size为奇数时，则边$(u,v)$,一定会被经过**,所以我们可以得到对于最小值的计算方法

代码:
~~~cpp
void dfs_min(int u,int fa)
{
	si[u]=1;
	for(register int i=head[u];i;i=e[i].last)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dfs_min(v,u);
		si[u]+=si[v];
		if(si[v]&1)
			ans+=e[i].w;
	}
}
~~~
#### 最大值
对于最大值，我们不能单纯的取反后再按最小值的方法做，我们可以对于每一条边为单位，让这一条边尽可能多的被通过，**那么，对于边$(u,v)$,我们的最多经过次数即为$min(size[v],n-size[v])$，换成语言说明即为这条边连接的两个子树的size最小值**
既然知道最多贡献次数了之后，那么其对于答案的贡献就为$min(size[v],n-size[v]) *  e[i].val$

代码:
~~~cpp
void dfs_max(int u,int fa)
{
	si[u]=1;
	for(register int i=head[u];i;i=e[i].last)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dfs_max(v,u);
		si[u]+=si[v];
		ans+=(ll)min(si[v],n-si[v])*e[i].w;
	}
}
~~~
>> **_Talk is cheap, show you the code_**

~~~cpp
#include<touwenjian.h>//MMM的头文件，悄悄偷过来用
#define ll long long
#define maxn 200005
using namespace std;
int T,n,k,head[maxn],si[maxn];
struct eage
{
	int v,w,last;
}e[maxn<<1];
ll ans;

int read()
{
	int num,sign=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')sign=-1;
	num=c-'0';
	while((c=getchar())>='0'&&c<='9')
		num=(num<<1)+(num<<3)+c-'0';
	return num*sign;
}

inline void addeage(int u,int v,int w)
{
	e[++k].last=head[u];
	e[k].v=v;
	e[k].w=w;
	head[u]=k;
}

void dfs_min(int u,int fa)
{
	si[u]=1;
	for(register int i=head[u];i;i=e[i].last)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dfs_min(v,u);
		si[u]+=si[v];
		if(si[v]&1)
			ans+=e[i].w;
	}
}

void dfs_max(int u,int fa)
{
	si[u]=1;
	for(register int i=head[u];i;i=e[i].last)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dfs_max(v,u);
		si[u]+=si[v];
		ans+=(ll)min(si[v],n-si[v])*e[i].w;
	}
}

int main()
{
	T=read();
	while(T--)
	{
		n=read()<<1;
		k=0;
		for(register int i=1;i<=n;++i)head[i]=0;
		for(register int u,v,w,i=1;i<n;++i)
		{
			u=read(),v=read(),w=read();
			addeage(u,v,w);
			addeage(v,u,w);
		}
		ans=0;
		dfs_min(1,0);
		printf("%lld ",ans);
		ans=0;
		dfs_max(1,0);
		printf("%lld\n",ans);
	}
	return 0;
}
~~~

---

## 作者：EXODUS (赞：3)

# Part 1：前言

从 agc018_d 跑过来的，这个题算是那个题的弱化版，做完这个题可以考虑去 agc018_d 练手。

下文中，定义 $sub(u)$ 表示 $u$ 的子树中的点所形成的点集，$siz(u)$ 表示 $u$ 的子树大小，即 $siz(u)=\vert sub(u)\vert$。令 $\overline{sub(u)}$ 表示 $u$ 子树外的点形成的点集。令 $n=2k$。

# Part 2：正文

我们难以直接去维护路径，因此考虑每条边被经过的次数。

先考虑最小值。注意到一个点 $u$ 上面的边 $e$ 会被经过当且仅当子树内不能形成一组完美匹配。换言之，即 $siz(u)\bmod 2\equiv 1$。充分性是显然的，因为不经过这条边子树内匹配必定会余下一个点，这个点不经过这条边无法形成匹配，因此我们只考虑必要性。

证明考虑反证。假定对于一种最优方案，存在一组匹配 $(u,v)$ 和一个点 $w$ 满足 $u\in sub(w),v\in \overline{sub(w)}$ 且 $siz(w)\bmod 2\equiv 0$。仍然称 $e$ 表示由 $w$ 到父亲的边。由于 $w$ 的子树大小为偶数，则 $w$ 子树内一定存在另一个点 $u'$ 和另一个不在 $w$ 子树内的点 $v'$ 匹配。且这两组匹配形成的路径一定在 $e$ 处相交，考虑交换 $u'$ 和 $v$，则其它边经过次数不增且 $e$ 的经过次数减小 $2$，答案一定变小，这和我们的最优假设不同。

那么最小值就好算了。枚举每一个点，计算子树大小是否为 $2$ 的倍数，不是的话就把答案加上向上的边的边权大小。

然后考虑最大值。我们仿照上面的技巧，考虑边最多被经过多少次。仿照上面的技巧，我们猜测对于一个点 $u$，其上面的边 $e$ 被经过的次数一定是 $\min(siz(u),n-siz(u))$。容易证明上界一定是这个，因此我们考虑是否能够达到。依然仿照上面的技巧，我们假设对于一种最优方案，存在一个点 $w$ 其上的边 $e$ 经过次数未达到上界。这意味着存在两组匹配 $(u,v)$ 和 $(u',v')$，满足 $u,v\in sub(u),u',v'\in \overline{sub(u)}$。依然考虑交换 $u'$ 和 $v$。此时 $e$ 经过次数增加 $2$ 且其它过次数不降。和我们的最优假设不同。

因此最大值也好算了。枚举每一个点，然后将答案加上其向上的边的边权乘上子树大小和子树外大小的较小值即可。

# Part 3：代码

尝试了一下带空格的码风。

```cpp
void solve() {
	int n;
	read(n);
	n <<= 1;
	
	vector<vector<pair<int, int>>> g(2 * n);
	vector<int> siz(n), val(n);
	
	for (int i = 1, u, v, w; i < n; i++) {
		read(u, v, w); --u, --v;
		g[u].eb(v, w), g[v].eb(u, w);
	}
	
	function<void(int)> dfs = [&](int u) {
		siz[u] = 1;
		for(auto [v, w] : g[u]) {
			val[v] = w;
			g[v].erase(find(g[v].begin(), g[v].end(), make_pair(u, w)));
			dfs(v); siz[u] += siz[v];
		}
	};
	
	dfs(0);
	
	ll maxans = 0, minans = 0;
	
	for (int i = 0; i < n; i++) {
		maxans += (ll)min(siz[i], n - siz[i]) * val[i];
		minans += (siz[i] & 1) * val[i];
	}
	
	printf("%lld %lld\n", minans, maxans);
	
	return;
}
```

---

