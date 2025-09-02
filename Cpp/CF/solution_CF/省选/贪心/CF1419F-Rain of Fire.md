# Rain of Fire

## 题目描述

There are $ n $ detachments on the surface, numbered from $ 1 $ to $ n $ , the $ i $ -th detachment is placed in a point with coordinates $ (x_i, y_i) $ . All detachments are placed in different points.

Brimstone should visit each detachment at least once. You can choose the detachment where Brimstone starts.

To move from one detachment to another he should first choose one of four directions of movement (up, right, left or down) and then start moving with the constant speed of one unit interval in a second until he comes to a detachment. After he reaches an arbitrary detachment, he can repeat the same process.

Each $ t $ seconds an orbital strike covers the whole surface, so at that moment Brimstone should be in a point where some detachment is located. He can stay with any detachment as long as needed.

Brimstone is a good commander, that's why he can create at most one detachment and place it in any empty point with integer coordinates he wants before his trip. Keep in mind that Brimstone will need to visit this detachment, too.

Help Brimstone and find such minimal $ t $ that it is possible to check each detachment. If there is no such $ t $ report about it.

## 说明/提示

In the first test it is possible to place a detachment in $ (0, 0) $ , so that it is possible to check all the detachments for $ t = 100 $ . It can be proven that it is impossible to check all detachments for $ t < 100 $ ; thus the answer is $ 100 $ .

In the second test, there is no such $ t $ that it is possible to check all detachments, even with adding at most one new detachment, so the answer is $ -1 $ .

In the third test, it is possible to place a detachment in $ (1, 0) $ , so that Brimstone can check all the detachments for $ t = 2 $ . It can be proven that it is the minimal such $ t $ .

In the fourth test, there is no need to add any detachments, because the answer will not get better ( $ t = 2 $ ). It can be proven that it is the minimal such $ t $ .

## 样例 #1

### 输入

```
4
100 0
0 100
-100 0
0 -100```

### 输出

```
100```

## 样例 #2

### 输入

```
7
0 2
1 0
-3 0
0 -2
-1 -1
-1 -3
-2 -3```

### 输出

```
-1```

## 样例 #3

### 输入

```
5
0 0
0 -1
3 0
-2 0
-2 1```

### 输出

```
2```

## 样例 #4

### 输入

```
5
0 0
2 0
0 -1
-2 0
-2 1```

### 输出

```
2```

# 题解

## 作者：YLWang (赞：31)

## 1. 算法 1

因为可以在任意位置停留，$T$ 显然满足可二分性。

那么问题就变成了判定性问题。

我们对于每一行和每一列中的距离小于 $mid$ 的点连边。具体可以使用并查集实现。

如果最后仅有一个连通块则不用加入点 $T = mid$ 可行。

关于加入一个点，官方 sol 给出了一个 $O(n^2)$ 的基于目前连通块个数分类讨论的方法。我写的是一种相对暴力的方法。

考虑到一个点可能且仅可能落在 $a_i - mid, a_i, a_i+mid$ 三个位置，我们把它们全部离散化。然后枚举每一个点，并把当前点所在的行和列暴力的 merge 到一个可撤销并查集中，每次加入后检查即可。这个做法是**大常数**的 $O(n^2\log n)$，但还是可以通过。

[提交记录](https://codeforces.com/contest/1419/submission/93295033)


---

## 2. 算法 2


看了 Loveti 的题解觉得很有意思于是去实现了一个两只 log 的做法。~~实在不会一只log，有会的大佬麻烦教教我~~

首先我们考虑最后的问题等价于是否存在一个被四个联通块均覆盖的点。那么问题就变成了一个二维平面上线段增加一种颜色，并查询全局有没有一个被四个颜色覆盖的点。

那么第一思路就是扫描线。然后发现我们并不会维护每个位置上有没有四个数。因为我们要支持删除，于是不能进行区间或一类的不可逆操作。

于是考虑对 $x$ 轴进行线段树分治。分治以后只有插入了可以进行区间或了。

然而我们还是不能简单地维护最大值。读者自证不难。~~也有可能是我naive~~了。

于是我们状压每个区间内每个颜色的出现次数或者是否出现，用 $0-15$ 之间的整数表示状态。这是容易 pushup 和 pushdown 的。

那么总复杂度就是 $O(2^m n\log^2 n\log T)$ 再带一个离散化的常数，其中 $m \leqslant 4$，有点跑不过 $n^2$ 老哥。

[代码](http://codeforces.com/contest/1419/submission/93602185)还是很好写的，不算恶心。

---

## 3. 算法 3


Loveti 给出了一个 log 的做法。其实挺 naive 的但我没有注意到。菜得真实。

我们考虑这个线段加具有的特殊性质。

- 单点加。可能会持续很久。

- 区间加。只会持续 1。

这就启示我们不要往线段树上 apply 区间加，只 apply 单点加。而区间加则可以通过处理之后查询来判断是否合法。容易发现，这样的复杂度是 $O(2^m n\log n\log T)$。

[提交记录在这儿。](https://codeforces.com/contest/1419/submission/93640848)

这玩意还是跑不过暴力老哥，但已经跑得飞快了。或许是我的实现过于奔放而没有任何卡常的原因吧。

---

## 4. 总结
本文给出的三个算法涉及了不同方面的数据结构知识，思维难度由浅入深，如能仔细研究一遍并自己实现应该能大有收获。

若有任何问题请私信 YLWang。

本文的第三个代码实现同时作为 Loveti 的题解的代码实现。~~工具人 YLWang~~。

最后，本题解前后耗时两天写成。希望觉得有帮助的同学们给一个赞让更多人看到。（其实这是我第一次在博内求赞，因为觉得这篇文章确实很有价值，还请帮个忙。）



---

## 作者：Erusel (赞：6)

Upd3 on 2020/9/25:

恭喜 YL·工具人·鸽子·Wang 成功使用 $O(2^4nlog nlogT)$ 的复杂度通过了本题，这也证明了我下面描述的算法的正确性。

大家可以去[他的博客](https://www.luogu.com.cn/blog/YLWang/solution-cf1419f#)里帮他点个赞，也非常感谢他所做出的贡献（

在 $n=1000$ 的情况下上面的做法被暴力老哥按在地上捶，所以我们要把 $n$ 开到 $10^5$（

Upd2 on 2020/9/24:

YLWang 神仙说这东西有一部分假掉了，修了一下部分内容

Upd1 on 2020/9/24:

看到了 YLWang 神仙用线段树分治把我那个转化后的数据结构题（雾）切掉了，特别开心，因为这可能是本题唯一的一个优化复杂度的方向了。但是他的做法是 $2$ 只 $log$ 的（除去二分的部分），个人认为应该可以做到 $1$ 只 $log$，这里详细说明一下。

之前没看过这篇题解的可以先看完原答案

考虑这样一个问题：

现在你有 $n$ 次操作 $(n\le 1000)$，每次操作给定一个点的坐标 $(x,y)$ 和两个正整数 $t,id$，$(|x|,|y|\le 10^9)$且均为整点

对于 $id=1$，每次操作你需要把所有距离 $(x,y)$ 为 $t$ 的整点全部染成红色。

对于 $id=2$，每次操作你需要把所有距离 $(x,y)$ 为 $t$ 的整点全部染成蓝色。

对于 $id=3$，每次操作你需要把所有距离 $(x,y)$ 为 $t$ 的整点全部染成紫色。

对于 $id=4$，每次操作你需要把所有距离 $(x,y)$ 为 $t$ 的整点全部染成绿色。

求最后平面上是否存在一个点是四色的。

考虑扫描线，随便找个维度扫，比如说从上往下扫吧

考虑维护列的线段树，

每次扫到一列就把那列的那个颜色单点 $+1$，那列结束后就单点 $-1$

每次扫到一行，就把那一行分成 $k$ 段，每一段对应的颜色补集是相同的。然后对于每一段，查询一下是否存在操作颜色的补集就好了。

还要注意的是扫到列的时候也要判断是否达成目标（可能一个点被列扫了 $4$ 次之类的

时间复杂度大概是 $O(nlogn*2^4)$，空间复杂度是 $O(n*2^4)$

---

原答案：

这里给一种比较蠢的做法。

首先二分答案 $t$，把距离每个点小于 $t$ 的点 $\text{merge}$ 进一个并查集，那么这样就有 $k$ 个集合

如果 $k=1$ 那么就不需要加点

如果 $k>4$ 那么不管怎么加点都不可能成立，这个可以用反证法证明：我们考虑存在一个点 $(x,y)$ 满足这个点到 $k$ 个集合的最近距离 $\le t$，那么根据咕巢原理，至少有 $k-3$ 个与添加点匹配的点在同一个方向上，那么这些在同一个方向上的点应该在一个集合里，与 $k>4$ 矛盾

具体的，上个图 ![](https://cdn.luogu.com.cn/upload/image_hosting/ywm7j2os.png)

比如说上幅图中，$(0,2)$就是我们要添加的点，$k=5$

你会发现下面两个点在同一个方向上，如果更远的那个点距离 $(0.2)\le t$ 那么这些在同一个方向上的点之间的距离全都 $\le t$，这些点就都应该被 $\text{merge}$ 到一个集合里，推出矛盾。

然后就是数据结构学傻综合症的患者给大家带来的无脑做法了，我们不需要分类讨论 $k$，反正 $k$ 最大也就 $4$，我们考虑对于每一个不同的集合的点$(id,x,y)$（$id$ 表示集合编号），把所有距离 $(x,y)\le t$ 的点全部染成 $id$ 色，那么对于一个点如果存在 $k$ 种颜色，这个方案就是可行的。

具体的话可以直接把点离散化，如果暴力染色的话染色部分的复杂度是 $O(n^2)$ 的，当然也可以用数据结构优化到 $O(nlogn)$(或许可能可以 $O(n)$)


---

## 作者：Karry5307 (赞：3)

### 题意

不想写。

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13720976.html)

场上想了 1h+ 无果，一到场外就口胡出来了，我真是个 sb。

首先注意到如果 $t$ 满足条件那么 $t+1$ 也会满足，所以答案具有单调性，可以二分，于是现在只需要考虑对于某个特定的 $t$ 能否满足。

注意到对于平面上的 $u,v,w$ 三个点来说，如果 $u$ 能到 $v$，$v$ 能到 $w$ 那么 $u$ 一定能到 $w$。

既然这个可达性是可以传递的，那么可以用一个并查集来将相互到的点缩成一个连通块。

如果连通块个数为 $1$ 那么一定可以，大于 $4$ 就一定不行，剩下的情况讨论一下。

如果连通块个数为 $2$，那么只需要找出两个分属不同连通块的点，然后看看加一个点能不能使得这两个点互相可达即可。

如果连通块个数为 $3$，那么只需要找出一条线段和一个点，线段的两个端点和选出来的点分属三个不同的连通块。这个时候注意到加的那个点是已经确定了的，所以直接判断一下即可。

如果连通块个数为 $4$，那么只需要找出两条相交的线段，四个端点分属不同的连通块。这个时候新加的那个点就是线段的端点。简单判断一下可达性即可。

本题代码细节比较多，建议配合代码理解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=1e3+51;
struct Tuple{
	ll x,y;
	inline bool operator <(const Tuple &rhs)const
	{
		return this->x==rhs.x?this->y<rhs.y:this->x<rhs.x;
	}
};
map<ll,vector<Tuple>>row,col;
ll n,totr,totc,l,r,mid,res=-1;
ll ffa[MAXN],x[MAXN],y[MAXN],bel[MAXN],rows[MAXN],cols[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll find(ll x)
{
	return x==ffa[x]?x:ffa[x]=find(ffa[x]);
}
inline void merge(ll x,ll y)
{
	ll fx=find(x),fy=find(y);
	if(fx!=fy)
	{
		ffa[fy]=fx;
	}
}
inline ll check(ll mid)
{
	ll blk=0,p,q,r,s,lx,rx;
	for(register int i=1;i<=n;i++)
	{
		ffa[i]=i;
	}
	for(register int i=1;i<=n;i++)
	{
		for(register int j=i+1;j<=n;j++)
		{
			if(x[i]==x[j]&&abs(y[i]-y[j])<=mid)
			{
				merge(i,j);
			}
			if(y[i]==y[j]&&abs(x[i]-x[j])<=mid)
			{
				merge(i,j);
			}
		}
	}
	for(register int i=1;i<=n;i++)
	{
		blk+=(find(i)==i);
	}
	if(blk==1)
	{
		return 1;
	}
	if(blk>4)
	{
		return 0;
	}
	for(register int i=1;i<=n;i++)
	{
		bel[i]=ffa[i];
	}
	if(blk==2)
	{
		for(register int i=1;i<=n;i++)
		{
			for(register int j=1;j<=n;j++)
			{
				if(bel[i]==bel[j])
				{
					continue;
				}
				if(x[i]==x[j]&&abs(y[i]-y[j])<=2*mid)
				{
					return 1;
				}
				if(y[i]==y[j]&&abs(x[i]-x[j])<=2*mid)
				{
					return 1;
				}
				if(abs(x[i]-x[j])<=mid&&abs(y[i]-y[j])<=mid)
				{
					return 1;
				}
			}
		}
		return 0;
	}
	if(blk==3)
	{
		vector<Tuple>v;
		for(register int i=1;i<=totr;i++)
		{
			for(register int j=1;j<row[rows[i]].size();j++)
			{
				p=row[rows[i]][j-1].y,q=row[rows[i]][j].y;
				bel[p]!=bel[q]?v.push_back((Tuple){p,q}):(void)1;
			}
		}
		for(register int i=1;i<=totc;i++)
		{
			for(register int j=1;j<col[cols[i]].size();j++)
			{
				p=col[cols[i]][j-1].y,q=col[cols[i]][j].y;
				bel[p]!=bel[q]?v.push_back((Tuple){p,q}):(void)1;
			}
		}
		for(register int i=0;i<v.size();i++)
		{
			p=v[i].x,q=v[i].y;
			for(register int j=1;j<=n;j++)
			{
				if(bel[p]==bel[j]||bel[q]==bel[j])
				{
					continue;
				}
				if(x[p]==x[q])
				{
					lx=min(y[p],y[q]),rx=max(y[p],y[q]);
					if(y[j]>lx&&y[j]<rx&&abs(x[j]-x[p])<=mid)
					{
						if(abs(y[j]-y[p]<=mid)&&abs(y[j]-y[q])<=mid)
						{
							return 1;
						}
					}
				}
				else
				{
					lx=min(x[p],x[q]),rx=max(x[p],x[q]);
					if(x[j]>lx&&x[j]<rx&&abs(y[j]-y[p])<=mid)
					{
						if(abs(x[j]-x[p]<=mid)&&abs(x[j]-x[q])<=mid)
						{
							return 1;
						}
					}
				}
			}
		}
		return 0;
	}
	if(blk==4)
	{
		vector<Tuple>vx,vy;
		for(register int i=1;i<=totr;i++)
		{
			for(register int j=1;j<row[rows[i]].size();j++)
			{
				p=row[rows[i]][j-1].y,q=row[rows[i]][j].y;
				bel[p]!=bel[q]?vx.push_back((Tuple){p,q}):(void)1;
			}
		}
		for(register int i=1;i<=totc;i++)
		{
			for(register int j=1;j<col[cols[i]].size();j++)
			{
				p=col[cols[i]][j-1].y,q=col[cols[i]][j].y;
				bel[p]!=bel[q]?vy.push_back((Tuple){p,q}):(void)1;
			}
		}
		for(register int i=0;i<vx.size();i++)
		{
			for(register int j=0;j<vy.size();j++)
			{
				p=vx[i].x,q=vx[i].y,r=vy[j].x,s=vy[j].y,lx=x[p],rx=y[r];
				if(bel[p]==bel[r]||bel[p]==bel[s])
				{
					continue;
				}
				if(bel[q]==bel[r]||bel[q]==bel[s])
				{
					continue;
				}
				if(y[r]<=min(y[p],y[q])||y[r]>=max(y[p],y[q]))
				{
					continue;
				}
				if(x[p]<=min(x[r],x[s])||x[p]>=max(x[r],x[s]))
				{
					continue;
				}
				if(abs(rx-y[p])<=mid&&abs(rx-y[q])<=mid)
				{
					if(abs(lx-x[r])<=mid&&abs(lx-x[s])<=mid)
					{
						return 1;
					}
				}
			}
		}
		return 0;
	}
}
int main()
{
	n=read(),r=2e9;
	for(register int i=1;i<=n;i++)
	{
		rows[++totr]=x[i]=read(),cols[++totc]=y[i]=read();
		row[x[i]].push_back((Tuple){y[i],i});
		col[y[i]].push_back((Tuple){x[i],i});
	} 
	sort(rows+1,rows+totr+1),sort(cols+1,cols+totc+1);
	totr=unique(rows+1,rows+totr+1)-rows-1;
	totc=unique(cols+1,cols+totc+1)-cols-1;
	for(register int i=1;i<=totr;i++)
	{
		sort(row[rows[i]].begin(),row[rows[i]].end());
	}
	for(register int i=1;i<=totc;i++)
	{
		sort(col[cols[i]].begin(),col[cols[i]].end());
	}
	while(l<=r)
	{
		mid=(l+r)>>1;
		check(mid)?res=mid,r=mid-1:l=mid+1;
	}
	printf("%d\n",res);
}
```

---

## 作者：lzqy_ (赞：2)

其实可以暴力一点。

二分答案 $T$，暴力 $O(n^2)$ 合并可达的点，形成了若干个连通块。

显然是要加一个点让连通块个数降到 $1$，考虑哪些点是有用的，可接受范围为 $O(n^2)$。

首先每一个 $x$ 和每一个 $y$ 两两配对的坐标有可能有用，这是 $O(n^2)$ 个，可以接受。

如果一个点 $(x,y)$ 都没出现过，显然是无用的。

如果一个点的 $x$ 出现过 $y$ 没出现过（反之同理），那它必定是加在两个点之间，此时显然中点最优。

这大概有 $2n^2$ 个决策点，直接做是 $O(n\log n\log V)$ 的，把决策点上下左右的四个点在二分外面处理即可做到 $O(n\log n+n\log V)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
#define il inline
using namespace std;
const int maxn=1010;
const int maxs=4000010;
const int inf=1<<30;
il int read(){
	int x=0,f=1;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x*f;
}
struct node{
	int x,y;
}a[maxn];
struct info{
	int f1,f2,f3,f4;
	int x,y;
}b[maxs];
map<int,int>X,Y;
set<pair<int,int> >s1[maxn];
set<pair<int,int> >s2[maxn]; 
int n,m,tot,cnt,f[maxn];
bool Vis[maxn],vis[maxn];
int Find(int x){return f[x]==x?x:f[x]=Find(f[x]);}
int up(int x,int y){
	if(!(x=X[x])) return 0;
	if((--s2[x].end())->first<=y) return 0;
	return s2[x].upper_bound(mp(y+1,-inf))->second;
}
int down(int x,int y){
	if(!(x=X[x])) return 0;
	if(s2[x].begin()->first>=y) return 0;
	return (--s2[x].upper_bound(mp(y,-inf)))->second;
}
int right(int x,int y){
	if(!(y=Y[y])) return 0;
	if((--s1[y].end())->first<=x) return 0;
	return s1[y].upper_bound(mp(x+1,-inf))->second;
}
int left(int x,int y){
	if(!(y=Y[y])) return 0;
	if(s1[y].begin()->first>=x) return 0;
	return (--s1[y].upper_bound(mp(x,-inf)))->second;
} 
void calc(int x,int y){
	b[++cnt].x=x,b[cnt].y=y;
	b[cnt].f1=up(x,y),b[cnt].f2=down(x,y);
	b[cnt].f3=left(x,y),b[cnt].f4=right(x,y);
}
bool chk(int d){
	if(d==1)
		d++,d--;
	tot=0;
	for(int i=1;i<=n;i++) f[i]=i,vis[i]=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(a[i].x==a[j].x&&abs(a[i].y-a[j].y)<=d)
				f[Find(i)]=Find(j);
			else if(a[i].y==a[j].y&&abs(a[i].x-a[j].x)<=d)
				f[Find(i)]=Find(j);
	for(int i=1;i<=n;i++)
		if(!vis[Find(i)]) tot++,vis[Find(i)]=1;
	if(tot==1) return 1;
	if(tot>4) return 0;
	for(int i=1,f1,f2,f3,f4,Cnt;i<=cnt;i++){
		Cnt=0,Vis[0]=1,f1=b[i].f1,f2=b[i].f2,f3=b[i].f3,f4=b[i].f4;
		if(!Vis[Find(f1)]&&abs(a[f1].y-b[i].y)<=d) Cnt++,Vis[Find(f1)]=1;
		if(!Vis[Find(f2)]&&abs(a[f2].y-b[i].y)<=d) Cnt++,Vis[Find(f2)]=1;
		if(!Vis[Find(f3)]&&abs(a[f3].x-b[i].x)<=d) Cnt++,Vis[Find(f3)]=1;
		if(!Vis[Find(f4)]&&abs(a[f4].x-b[i].x)<=d) Cnt++,Vis[Find(f4)]=1;
		Vis[Find(f1)]=Vis[Find(f2)]=Vis[Find(f3)]=Vis[Find(f4)]=0;
		if(Cnt==tot) return 1;
	}
	return 0; 
}
int hx[maxn],hy[maxn];
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i].x=read(),a[i].y=read();
	for(int i=1;i<=n;i++)
		hx[i]=a[i].x,hy[i]=a[i].y;
	sort(hx+1,hx+1+n);
	sort(hy+1,hy+1+n);
	for(int i=1,vx=0,vy=0;i<=n;i++){
		if(i==1||hx[i]!=hx[i-1]) vx++;
		if(i==1||hy[i]!=hy[i-1]) vy++;
		X[hx[i]]=vx,Y[hy[i]]=vy;
	}
	for(int i=1;i<=n;i++){
		s1[Y[a[i].y]].insert(mp(a[i].x,i));
		s2[X[a[i].x]].insert(mp(a[i].y,i));
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			calc(a[i].x,a[j].y);
			calc(a[j].x,a[i].y);
			calc(a[i].x,a[i].y+a[j].y>>1);
			calc(a[i].x+a[j].x>>1,a[i].y);
		}
//	chk(2);
//	return 0;
	if(!chk(2e9)){
		printf("-1\n");
		return 0;
	}
	int l=0,r=2e9,mid;
	while(r>l){
		mid=((ll)l+r)>>1;
		if(chk(mid)) r=mid;
		else l=mid+1;
	}printf("%d\n",l);
	return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
[题目传送门](https://www.luogu.com.cn/problem/CF1419F)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf1419f)内食用应该不会更佳。
## 题意分析
首先因为求的是 $T$ 的最小值，而且简单观察得到比最小值更大的 $T$ 一定能满足题目的意思，所以考虑二分。

二分出每一步最长的行走距离 $T$ 后，就应该判断这种情况是否成立了，画个图发现我们可以用并查集将许多能互相连通的点缩为一个联通块，接下去只需要考虑加上一个点的情况了。

考虑一个极端情况，即为 $4$ 个联通块时，这种情况下的 $T$ 才是最小的。
![](https://cdn.luogu.com.cn/upload/image_hosting/e6017ke1.png)

这种情况下，所有的点之间的距离都被拉到了极限，所以由此可以得出当块数大于 $4$ 时是不可能有解的。

分别考虑块数为 $1,2,3,4$ 时。

首先是 $1$，所有的点已经连成联通块，不必考虑。

对于 $2$，枚举两个联通块每一个点，暴力查询是否有点的横坐标和纵坐标只差都小于等于 $T$。

对于 $3$，先枚举一个联通块中的点，然后由这个点向上下或者左右连线直到碰到联通块，暴力枚举最后一个联通块中的点尝试用一个点将这三个点连起来。

对于 $4$，先枚举一个联通块的点，然后由这个点向上下或者左右连线直到碰到联通块，再枚举另一个联通块中的点，然后由这个点向上下或者左右连线直到碰到联通块，即可得到 $4$ 个来自于不同联通块中的点，暴力判断是否能用一个点将 $4$ 个点连起即可。

时间较优，位于最优解第一页。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{int x,y;}a[1010];
int n,cnt;
int fa[1010],cx[1010],cy[1010];
vector<pair<int,int> >h[1010],l[1010];
int fabs(int x){return x<0?-x:x;}
int find(int x){return x==fa[x]? x:fa[x]=find(fa[x]);}
void merge(int x,int y){int fx=find(x),fy=find(y);if(fx!=fy) --cnt,fa[fy]=fx;}
bool check1(int x,int y,int x2,int y2,int mid)
{
    if(x==x2&&fabs(y-y2)<=2*mid) return 1;
    if(y==y2&&fabs(x-x2)<=2*mid) return 1;
    if(fabs(x-x2)<=mid&&fabs(y-y2)<=mid) return 1;
    return 0;
}
bool check(int mid)
{
    cnt=n;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            if(a[i].x==a[j].x&&fabs(a[i].y-a[j].y)<=mid) merge(i,j);
            if(a[i].y==a[j].y&&fabs(a[i].x-a[j].x)<=mid) merge(i,j);
        }
    if(cnt>4) return 0;
    for(int i=1,x;i<=n;i++) x=find(i);
    if(cnt==1) return 1;
    else if(cnt==2)
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
            {
                if(fa[i]==fa[j]) continue;
                if(check1(a[i].x,a[i].y,a[j].x,a[j].y,mid)) return 1;
            }
    else if(cnt==3)
    {
        for(int i=1;i<=cx[0];i++)
        {
            int pos1=cx[i];
            for(int j=1;j<h[i].size();j++)
            {
                int l1=h[i][j-1].second,r1=h[i][j].second;
                int yl=h[i][j-1].first,yr=h[i][j].first;
                if(fa[l1]!=fa[r1]&&yr-yl<=2*mid)
                {
                    for(int k=1;k<=n;k++)
                    {
                        if(fa[l1]==fa[k]||fa[r1]==fa[k]) continue;
                        if(!(yr-mid<=a[k].y&&a[k].y<=yl+mid)) continue;
                        if(fabs(a[k].x-pos1)<=mid) return 1;
                    }
                }
            }
        }
        for(int i=1;i<=cy[0];i++)
        {
            int pos2=cy[i];
            for(int j=1;j<l[i].size();j++)
            {
                int l1=l[i][j-1].second,r1=l[i][j].second;
                int xl=l[i][j-1].first,xr=l[i][j].first;
                if(fa[l1]!=fa[r1]&&xr-xl<=2*mid)
                    for(int k=1;k<=n;k++)
                    {   
                        if(fa[l1]==fa[k]||fa[r1]==fa[k]) continue;
                        if(!(xr-mid<=a[k].x&&a[k].x<=xl+mid)) continue;
                        if(fabs(a[k].y-pos2)<=mid) return 1;
                    }
            }
        }
    }
    else
        for(int i=1;i<=cx[0];i++)
        {
            int pos1=cx[i];
            for(int j=1;j<h[i].size();j++)
            {
                int l1=h[i][j-1].second,r1=h[i][j].second;
                int yl=h[i][j-1].first,yr=h[i][j].first;
                if(fa[l1]==fa[r1]) continue;
                for(int k=1;k<=cy[0];k++)
                {
                    int pos2=cy[k];
                    for(int r=1;r<l[k].size();r++)
                    {
                        int l2=l[k][r-1].second,r2=l[k][r].second;
                        int xl=l[k][r-1].first,xr=l[k][r].first;
                        if(fa[l2]==fa[r2]) continue;
                        if(fa[l2]==fa[l1]||fa[l2]==fa[r1]) continue;
                        if(fa[r2]==fa[l1]||fa[r2]==fa[r1]) continue;
                        if(!(xr-mid<=pos1&&pos1<=xl+mid)) continue;
                        if(!(yr-mid<=pos2&&pos2<=yr+mid)) continue;
                        if(fabs(pos1-xl)>mid||fabs(pos1-xr)>mid) continue;
                        if(fabs(pos2-yl)>mid||fabs(pos2-yr)>mid) continue;
                        return 1;
                    }
                }
            }
        }
    return 0;
}
int read()
{
    char c=getchar();int x=0,f=1;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        a[i].x=read();a[i].y=read();
        cx[++cx[0]]=a[i].x;cy[++cy[0]]=a[i].y;
    }
    sort(cx+1,cx+1+cx[0]);sort(cy+1,cy+1+cy[0]);
    cx[0]=unique(cx+1,cx+1+cx[0])-cx-1; cy[0]=unique(cy+1,cy+1+cy[0])-cy-1;
    for(int i=1;i<=n;i++)
    {
        int pos1=lower_bound(cx+1,cx+1+cx[0],a[i].x)-cx,pos2=lower_bound(cy+1,cy+1+cy[0],a[i].y)-cy;
        h[pos1].push_back(make_pair(a[i].y,i));
        l[pos2].push_back(make_pair(a[i].x,i));
    }
    for(int i=1;i<=cx[0];i++) sort(h[i].begin(),h[i].end());
    for(int i=1;i<=cy[0];i++) sort(l[i].begin(),l[i].end());	
    int l=0,r=2e9,ans=-1;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%lld",ans);
    return 0;
}
```
完结撒花！

---

## 作者：tommymio (赞：2)

果然 $\rm{CF}$ 道道都是结论题（雾

赛时题意理解错了，根本没开。

不难想到二分最大距离 $mid$，那么不大于最大距离的点能够相互到达，就构成了一个连通块。现在考虑判断能否加一个点将这些连通块全部连通为一个，其实就是二分的 $\text{check}$ 函数。根据鸽巢原理，再适当的使用反证法，可以证出当连通块个数 $> 4$ 时一定无解。此处就不证了（逃

那么对于连通块个数分类讨论即可，此处将连通块个数记作 $cnt$。

- $cnt=1$ 时，只存在一个连通块，显然有解
- $cnt=2$ 时，枚举两个点判断
- $cnt=3$ 时，枚举一条线段和一个点，线段的两个端点分属不同的连通块，因为不会存在三个点中任意两点不共线的情况，这样的情况一定是不合法的，所以不用考虑
- $cnt=4$ 时，枚举两条线段，两条线段的四个端点都分属不同的连通块，分析同上

因为 $2 \leq cnt\leq 4$ 时的枚举都是 $O(n^2)$ 的。

所以可以在 $O(n^2 \log 2\times 10^9)$ 的时间复杂度内解决该问题。

这个代码写的有点生草，随便看看就好（（（

```cpp
#include<cstdio>
#include<algorithm>
#include<functional>
typedef long long ll;
int n,block_cnt;
int fa[1005],bel[1005],cx[1005],cy[1005];
struct position {int x,y;} a[1005];
std::vector<std::pair<int,int> > row[1005],col[1005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int abs(int x) {return x<0? -x:x;}
inline int find(int x) {return x==fa[x]? x:fa[x]=find(fa[x]);}
inline void merge(int x,int y) {int fx=find(x),fy=find(y); if(fx!=fy) {--block_cnt;fa[fy]=fx;}}
inline bool CheckPoint(int x1,int y1,int x2,int y2,int lim) {
	if(x1==x2&&abs(y1-y2)<=2ll*lim) return 1;
	if(y1==y2&&abs(x1-x2)<=2ll*lim) return 1;
	if(abs(x1-x2)<=lim&&abs(y1-y2)<=lim) return 1;
	return 0;
}
inline bool check(ll lim) {
	block_cnt=n;
	for(register int i=1;i<=n;++i) fa[i]=i;
	for(register int i=1;i<=n;++i) {
		for(register int j=i+1;j<=n;++j) {
			if(a[i].x==a[j].x&&abs(a[i].y-a[j].y)<=lim) merge(i,j);
			if(a[i].y==a[j].y&&abs(a[i].x-a[j].x)<=lim) merge(i,j);
		}
	}
	if(block_cnt>4) return 0;
	for(register int i=1;i<=n;++i) bel[i]=find(i);
	if(block_cnt==1) return 1;
	else if(block_cnt==2) {//point and point
		for(register int i=1;i<=n;++i) { 
			for(register int j=i+1;j<=n;++j) {
				if(bel[i]==bel[j]) continue;
				if(CheckPoint(a[i].x,a[i].y,a[j].x,a[j].y,lim)) return 1;
			}
		}
	}
	else if(block_cnt==3) {
		for(register int i=1;i<=cx[0];++i) {
			ll curx=cx[i];
			for(register int j=1;j<row[i].size();++j) {
				int index_L=row[i][j-1].second,index_R=row[i][j].second;
				ll yL=row[i][j-1].first,yR=row[i][j].first;
				if(bel[index_L]!=bel[index_R]&&yR-yL<=2ll*lim) {
					for(register int k=1;k<=n;++k) {
						if(bel[index_L]==bel[k]||bel[index_R]==bel[k]) continue;
						if(!(yR-lim<=a[k].y&&a[k].y<=yL+lim)) continue;
						if(abs(a[k].x-curx)<=lim) return 1;
					}
				}
			}
		}
		for(register int i=1;i<=cy[0];++i) {
			ll cury=cy[i];
			for(register int j=1;j<col[i].size();++j) {
				int index_L=col[i][j-1].second,index_R=col[i][j].second;
				ll xL=col[i][j-1].first,xR=col[i][j].first;
				if(bel[index_L]!=bel[index_R]&&xR-xL<=2ll*lim) {
					for(register int k=1;k<=n;++k) {
						if(bel[index_L]==bel[k]||bel[index_R]==bel[k]) continue;
						if(!(xR-lim<=a[k].x&&a[k].x<=xL+lim)) continue;
						if(abs(a[k].y-cury)<=lim) return 1;
					}
				}
			}
		}
	}
	else {//Successful
		for(register int i=1;i<=cx[0];++i) {
			ll curx=cx[i];
			for(register int j=1;j<row[i].size();++j) {
				int index_L_1=row[i][j-1].second,index_R_1=row[i][j].second;
				ll yL=row[i][j-1].first,yR=row[i][j].first;
				if(bel[index_L_1]==bel[index_R_1]) continue;
				for(register int k=1;k<=cy[0];++k) {
					ll cury=cy[k];
					for(register int l=1;l<col[k].size();++l) {
						int index_L_2=col[k][l-1].second,index_R_2=col[k][l].second;
						ll xL=col[k][l-1].first,xR=col[k][l].first;
						if(bel[index_L_2]==bel[index_R_2]) continue;
						if(bel[index_L_2]==bel[index_L_1]||bel[index_L_2]==bel[index_R_1]) continue;
						if(bel[index_R_2]==bel[index_L_1]||bel[index_R_2]==bel[index_R_1]) continue;
						if(!(xR-lim<=curx&&curx<=xL+lim)) continue;
						if(!(yR-lim<=cury&&cury<=yR+lim)) continue;
						if(abs(curx-xL)>lim||abs(curx-xR)>lim) continue;
						if(abs(cury-yL)>lim||abs(cury-yR)>lim) continue;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
int main() {
	n=read();
	for(register int i=1;i<=n;++i) {
		a[i].x=read();a[i].y=read();
		cx[++cx[0]]=a[i].x;cy[++cy[0]]=a[i].y;
	}
	std::sort(cx+1,cx+1+cx[0]); std::sort(cy+1,cy+1+cy[0]);
	cx[0]=std::unique(cx+1,cx+1+cx[0])-cx-1; cy[0]=std::unique(cy+1,cy+1+cy[0])-cy-1;
	for(register int i=1;i<=n;++i) {
		int curx=std::lower_bound(cx+1,cx+1+cx[0],a[i].x)-cx,cury=std::lower_bound(cy+1,cy+1+cy[0],a[i].y)-cy;
		row[curx].push_back(std::make_pair(a[i].y,i));
		col[cury].push_back(std::make_pair(a[i].x,i));
	}
	for(register int i=1;i<=cx[0];++i) std::sort(row[i].begin(),row[i].end());
	for(register int i=1;i<=cy[0];++i) std::sort(col[i].begin(),col[i].end());	
	int l=0,r=2e9,res=-1;
	while(l<=r) {
		int mid=1ll*l+1ll*r>>1;
		if(check(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：ycyaw (赞：1)

若$t+1$时连通，显然$t$也连通，考虑二分答案。

二分答案后，先并查集找一下连通块（即把同行或同列且距离小于$mid$的归为一个块，设连通块数$cnt$。

先处理掉最简单的情况，$cnt=1$时合法，$cnt>4$不合法。

当$cnt=2$时，在两个连通块里各找一个点，判断是否能加一个点连通这两个点（即连通这两个连通块），复杂度$O(n^2)$。

当$cnt=3$时，先找出同一行或同一列的相邻的点构成的线段，然后再枚举点，判断是否能加一个点连通这三个点。线段的数量级为$O(n)$，所以复杂度仍为$O(n^2)$。

当$cnt=4$，找出横的线段和竖的线段，枚举判断线段交点能否连通四个点，复杂度$O(n^2)$。

上述枚举时，要先判断点或线段是否已经在同一连通块内。

整体复杂度$O(n^2\ log\ n)$。

不太会用$STL$，代码写的有点炸裂。

$Code\ Below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define int long long
#define hh puts("")
#define pc putchar
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
const int N=1005;
int n,x[N],y[N],ans=-1,f[N],cnt,hang[N],lie[N],gs1,gs2,bel[N];
struct node{
    int val,id;
    friend bool operator < (node A,node B){
        return A.val<B.val;
    }
};
map<int,vector<node>> u,v;
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-1;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+(ch^48);ch=getchar();}
    return ret*ff;
}
void write(int x){if(x<0){x=-x,pc('-');}if(x>9) write(x/10);pc(x%10+48);}
void writeln(int x){write(x),hh;}
void writesp(int x){write(x),pc(' ');}
int find(int A){
    return f[A]==A?A:f[A]=find(f[A]);
}
void uni(int A,int B){
    int tx=find(A),ty=find(B);
    if(tx!=ty) f[tx]=ty,cnt--;
}
bool check(int len){
    cnt=n;
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            if(x[i]==x[j]||y[i]==y[j]){
                int dis=abs(x[i]-x[j])+abs(y[i]-y[j]);
                if(dis<=len) uni(i,j);
            }
        }
    if(cnt==1) return 1;
    if(cnt>4) return 0;
    for(int i=1;i<=n;i++) bel[i]=find(i);
    if(cnt==2){//O(n) point and O(n) point
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(bel[i]==bel[j]) continue;
                if(x[i]==x[j]&&abs(y[i]-y[j])<=2*len) return 1;
                if(y[i]==y[j]&&abs(x[i]-x[j])<=2*len) return 1;
                if(abs(x[i]-x[j])<=len&&abs(y[i]-y[j])<=len) return 1; 
            }
        }
        return 0;
    }
    if(cnt==3){//O(n) segment and O(n) point
        vector<pii> seg;
        for(int i=1;i<=gs1;i++){
            for(int j=1;j<u[hang[i]].size();j++){
                if(bel[u[hang[i]][j-1].id]!=bel[u[hang[i]][j].id]){
                    seg.push_back(mp(u[hang[i]][j-1].id,u[hang[i]][j].id));
                }
            }
        }
        for(int i=1;i<=gs2;i++){
            for(int j=1;j<v[lie[i]].size();j++){
                if(bel[v[lie[i]][j-1].id]!=bel[v[lie[i]][j].id]){
                    seg.push_back(mp(v[lie[i]][j-1].id,v[lie[i]][j].id));
                }
            }
        }
        for(int t=0;t<seg.size();t++){
            int i=seg[t].fi,j=seg[t].se;
            for(int k=1;k<=n;k++){
                if(bel[i]==bel[k]||bel[j]==bel[k]) continue;
                if(x[i]==x[j]){
                    int L=min(y[i],y[j]),R=max(y[i],y[j]);
                    if(y[k]>L&&y[k]<R)
                        if(abs(x[k]-x[i])<=len&&abs(y[k]-y[i])<=len&&abs(y[k]-y[j])<=len)
                            return 1;
                }
                else{
                    int L=min(x[i],x[j]),R=max(x[i],x[j]);
                    if(x[k]>L&&x[k]<R)
                        if(abs(y[k]-y[i])<=len&&abs(x[k]-x[i])<=len&&abs(x[k]-x[j])<=len)
                            return 1;
                }
            }
        }
        return 0;
    }
    if(cnt==4){//O(n) segment and O(n) segment
        vector<pii> segx,segy;
        for(int i=1;i<=gs1;i++){
            for(int j=1;j<u[hang[i]].size();j++){
                if(bel[u[hang[i]][j-1].id]!=bel[u[hang[i]][j].id]){
                    segx.push_back(mp(u[hang[i]][j-1].id,u[hang[i]][j].id));
                }
            }
        }
        for(int i=1;i<=gs2;i++){
            for(int j=1;j<v[lie[i]].size();j++){
                if(bel[v[lie[i]][j-1].id]!=bel[v[lie[i]][j].id]){
                    segy.push_back(mp(v[lie[i]][j-1].id,v[lie[i]][j].id));
                }
            }
        }
        for(int t1=0;t1<segx.size();t1++){
            for(int t2=0;t2<segy.size();t2++){
                int i=segx[t1].fi,j=segx[t1].se;//i!=j
                int p=segy[t2].fi,q=segy[t2].se;//p!=q
                if(bel[i]==bel[p]||bel[i]==bel[q]||bel[j]==bel[p]||bel[j]==bel[q]) continue;
                if(y[p]<=min(y[i],y[j])||y[p]>=max(y[i],y[j])) continue;
                if(x[i]<=min(x[p],x[q])||x[i]>=max(x[p],x[q])) continue;
                int X=x[i],Y=y[p];
                if(abs(Y-y[i])<=len&&abs(Y-y[j])<=len&&abs(X-x[p])<=len&&abs(X-x[q])<=len) return 1;
            }
        }
        return 0;
    }
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++){
        x[i]=read();
        y[i]=read();
        u[x[i]].push_back((node){y[i],i});
        v[y[i]].push_back((node){x[i],i});
        hang[++gs1]=x[i];
        lie[++gs2]=y[i];
    }
    int tt;
    sort(hang+1,hang+gs1+1);
    tt=unique(hang+1,hang+gs1+1)-hang-1;
    gs1=tt;
    sort(lie+1,lie+gs2+1);
    tt=unique(lie+1,lie+gs2+1)-lie-1;
    gs2=tt;
    for(int i=1;i<=gs1;i++) sort(u[hang[i]].begin(),u[hang[i]].end());
    for(int i=1;i<=gs2;i++) sort(v[lie[i]].begin(),v[lie[i]].end());
    int l=0,r=2e9;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    write(ans);
    return 0;
}
```


---

## 作者：_edge_ (赞：0)

题解区是什么东西，除了那个扫描线以外是不是都做麻烦了。

容易发现题目可以二分，于是我们先二分，然后连通那不妨就用并查集。

连通块最多 $4$ 个，这个是很好证明的，然后我们只需要将点需要染色的矩形离散化一下，做个差分后判断是否存在一个点满足四种颜色都覆盖它即可，复杂度 $O(n^2 \log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define pb push_back
using namespace std;
const int INF=1e6+5;
const int INFN=3e3+5;
int n,a[INF],b[INF],fa_set[INF],s[INF],vis[INF];
char vis6[INFN][INFN];
short f2[INFN][INFN],f1[INFN][INFN];
vector <int> cntx,cnty,id[INF],id2[INF],cnt;
int find_set(int x) {return fa_set[x]==x?x:fa_set[x]=find_set(fa_set[x]);}
int Getx(int x) {return lower_bound(cntx.begin(),cntx.end(),x)-cntx.begin();}
int Gety(int x) {return lower_bound(cnty.begin(),cnty.end(),x)-cnty.begin();}
int check(int t) {
	cntx.clear();cnty.clear();
	for (int i=1;i<=n;i++) fa_set[i]=i;
	for (int i=1;i<=n;i++) {
		for (int j=i+1;j<=n;j++) {
			if (a[i]==a[j] && abs(b[i]-b[j])<=t) fa_set[find_set(i)]=find_set(j);
			if (b[i]==b[j] && abs(a[i]-a[j])<=t) fa_set[find_set(i)]=find_set(j);
		}
	}
	int sum=0;
	for (int i=1;i<=n;i++)
		if (fa_set[i]==i) sum++;
	if (sum>4) return 0;
	for (int i=1;i<=n;i++) {
		cntx.pb(a[i]-t);cntx.pb(a[i]+t);
		cnty.pb(b[i]-t);cnty.pb(b[i]+t);
		cntx.pb(a[i]);cnty.pb(b[i]);
	}
	sort(cntx.begin(),cntx.end());
	cntx.erase(unique(cntx.begin(),cntx.end()),cntx.end());
	sort(cnty.begin(),cnty.end());
	cnty.erase(unique(cnty.begin(),cnty.end()),cnty.end());
	int len6=cntx.size(),len7=cnty.size();
	for (int i=1;i<=n;i++) vis[i]=0;
	for (int i=0;i<=len6;i++)
		for (int j=0;j<=len7;j++)
			vis6[i][j]=0;
	for (int i=1;i<=n;i++) {
		if (vis[i]) continue;
		for (int i=0;i<=len6;i++)
			for (int j=0;j<=len7;j++)
				f1[i][j]=f2[i][j]=0;
		for (int j=i;j<=n;j++) {
			if (vis[j]) continue;
			if (find_set(i)==find_set(j)) {
				f1[Getx(a[j]-t)][Gety(b[j])]++;
				f1[Getx(a[j]+t)+1][Gety(b[j])]--;
				f2[Getx(a[j])][Gety(b[j]-t)]++;
				f2[Getx(a[j])][Gety(b[j]+t)+1]--;
				vis[j]=1;
			}
		}
		for (int i=1;i<=len6;i++)
			for (int j=1;j<=len7;j++) {
				f1[i][j]+=f1[i-1][j];
				f2[i][j]+=f2[i][j-1];
			}
		for (int i=1;i<=len6;i++)
			for (int j=1;j<=len7;j++)
				if (f1[i][j] || f2[i][j]) vis6[i][j]++;
	}
	for (int i=1;i<=len6;i++)
		for (int j=1;j<=len7;j++)
			if (vis6[i][j]==sum) 
				return 1;
			
	return 0;
}
signed main()
{
//	freopen("data.in","r",stdin);
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i]>>b[i];
	int l=1,r=2e9,ans=-1;
	while (l<=r) {
		int Mid=(l+r)>>1;
		if (check(Mid)) r=(ans=Mid)-1;
		else l=Mid+1;
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：little_sun (赞：0)

显然这题答案具有单调性性，现在我们考虑给定一个$T$怎么check

首先我们可以把所有不通过新点就可以互达的点合并成一个联通块。

容易发现当联通块个数$=1$时有解，$>4$时无解，剩下情况我们进行分类讨论

#### 1. 有两个联通块

	如果我们能找到两个点位于不同的联通块，并且他们在一条直线上且曼哈顿距离<=2T 或 两点的x,y坐标绝对值之差均小于T则有解
    
#### 2. 有三个联通块

	首先我们把所有在一条直线上相邻并且不属于一个联通块的点对(a, b)处理出来，对于每个点对可以找到点c与这两个点所属联通块都不同，若c到直线距离，a、b到c在线段上的投影距离均小于T，则合法
    
#### 3. 有四个联通块

	将找点c换成找点对(c,d)满足线段(a,b),(c,d)垂直，且a,b,c,d分属四个不同的联通块，接下来做法与3个联通块类似
    
时间复杂度O($n^2\log_2{2\times 10^9}$)

``` cpp
#include <bits/stdc++.h>
 
#define R register
#define ll long long
#define pir std::pair<ll, ll>
#define mp(i, j) std::make_pair(i, j)
#define sum(a, b, mod) (((a) + (b)) % mod)
#define It std::map<ll, std::vector<ll>>::iterator
 
const ll MaxN = 1e3 + 10;
 
ll n, x[MaxN], y[MaxN], f[MaxN];
std::unordered_map<ll, ll> trash;
std::map<ll, std::vector<ll>> lx, ly;
std::vector<std::pair<ll, ll>> X, Y, line;
 
ll Abs(ll x) { return (x < 0) ? (-x) : x; }
ll cmpx(ll a, ll b) { return x[a] < x[b]; }
ll cmpy(ll a, ll b) { return y[a] < y[b]; }
 
ll getf(ll x)
{
    if (x != f[x])
        f[x] = getf(f[x]);
    return f[x];
}
 
void merge(ll x, ll y)
{
    ll fx = getf(x), fy = getf(y);
    if (fx != fy) f[fx] = fy;
}
 
inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = 0;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? x : (-x);
}
 
ll check(ll mid)
{
    trash.clear();
    for (ll i = 1; i <= n; i++)
        f[i] = i;
    for (It it = lx.begin(); it != lx.end(); it++)
    {
        std::vector<ll> &v = it->second;
        for (ll i = 1; i < v.size(); i++)
            if (Abs(y[v[i]] - y[v[i - 1]]) <= mid)
                merge(v[i], v[i - 1]);
    }
    for (It it = ly.begin(); it != ly.end(); it++)
    {
        std::vector<ll> &v = it->second;
        for (ll i = 1; i < v.size(); i++)
            if (Abs(x[v[i]] - x[v[i - 1]]) <= mid)
                merge(v[i], v[i - 1]);
    }
    ll siz = 0;
    for (ll i = 1; i <= n; i++)
        // getf(i), printf("%lld ", f[i]),
        siz += (trash[getf(i)] == 0), trash[getf(i)] = 1;
    // printf("# %lld %lld\n", mid, siz);
    if (siz == 1)
        return 1;
    else if (siz == 2)
    {
        for (ll i = 1; i <= n; i++)
            for (ll j = i + 1; j <= n; j++)
                if (f[i] != f[j])
                {
                    if (Abs(x[i] - x[j]) == 0 && Abs(y[i] - y[j]) <= 2 * mid)
                            return 1;
                    if (Abs(y[i] - y[j]) == 0 && Abs(x[i] - x[j]) <= 2 * mid)
                            return 1;
                    if (Abs(x[i] - x[j]) <= mid && Abs(y[i] - y[j]) <= mid)
                            return 1;
                }
    }
    else if (siz == 3)
    {
        line.clear();
        for (It it = lx.begin(); it != lx.end(); it++)
        {
            std::vector<ll> &v = it->second;
            for (ll i = 1; i < v.size(); i++)
                if (f[v[i]] != f[v[i - 1]])
                    line.push_back(mp(v[i], v[i - 1]));
        }
        for (It it = ly.begin(); it != ly.end(); it++)
        {
            std::vector<ll> &v = it->second;
            for (ll i = 1; i < v.size(); i++)
                if (f[v[i]] != f[v[i - 1]])
                    line.push_back(mp(v[i], v[i - 1]));
        }
        for (auto li : line)
        {
            ll l = li.first, r = li.second;
            for (ll i = 1; i <= n; i++)
            {
                if (f[l] != f[i] && f[i] != f[r])
                {
                    if (x[l] == x[r])
                    {
                        if (Abs(y[l] - y[i]) <= mid && Abs(y[r] - y[i]) <= mid)
                            if (Abs(x[l] - x[i]) <= mid)
                                return 1;
                    }
                    else if (Abs(x[l] - x[i]) <= mid && Abs(x[r] - x[i]) <= mid)
                        if (Abs(y[l] - y[i]) <= mid)
                            return 1;
                }
            }
        }
    }
    else if (siz == 4)
    {
        X.clear(), Y.clear();
        for (It it = lx.begin(); it != lx.end(); it++)
        {
            std::vector<ll> &v = it->second;
            for (ll i = 1; i < v.size(); i++)
                if (f[v[i]] != f[v[i - 1]])
                    X.push_back(mp(v[i], v[i - 1]));
        }
        for (It it = ly.begin(); it != ly.end(); it++)
        {
            std::vector<ll> &v = it->second;
            for (ll i = 1; i < v.size(); i++)
                if (f[v[i]] != f[v[i - 1]])
                    Y.push_back(mp(v[i], v[i - 1]));
        }
        for (auto x1 : X)
        {
            for (auto y1 : Y)
            {
                ll a = x1.first, b = x1.second;
                ll c = y1.first, d = y1.second;
                if (f[a] != f[c] && f[a] != f[d])
                    if (f[b] != f[c] && f[b] != f[d])
                        if (Abs(x[a] - x[c]) <= mid && Abs(x[a] - x[d]) <= mid)
                            if (Abs(y[c] - y[a]) <= mid && Abs(y[c] - y[b]) <= mid)
                                return 1;
            }
        }
    }
    return 0;
}
 
signed main()
{
    n = read();
    for (ll i = 1; i <= n; i++)
    {
        x[i] = read(), y[i] = read();
        lx[x[i]].push_back(i);
        ly[y[i]].push_back(i);
    }
    for (It it = lx.begin(); it != lx.end(); it++)
    {
        std::vector<ll> &v = it->second;
        std::sort(v.begin(), v.end(), cmpy);
    }
    for (It it = ly.begin(); it != ly.end(); it++)
    {
        std::vector<ll> &v = it->second;
        std::sort(v.begin(), v.end(), cmpx);
    }
    ll l = 1, r = 0x7f7f7f7f;
    while (l < r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    if (l == 0x7f7f7f7f)
        l = -1;
    printf("%lld\n", l);
    return 0;
}  
```

---

## 作者：chenxia25 (赞：0)

这分明是个中等题嘛……不知道现场为啥没啥人过，导致我直接放弃去逛 room 了，也不知道是如何评到 2800 的。

> ### [洛谷题目页面传送门]( https://www.luogu.com.cn/problem/CF1419F ) & [CF 题目页面传送门]( https://codeforces.com/contest/1419/problem/F )
>
> 给定平面上 $n$ 个点 $(x_i,y_i)$，你可以任选出发点，每次可以走到本行或本列距离不超过 $t$ 的点，要求最终每个点至少走一遍。你可以随意在空白位置放一个附加点（这个点也要走），或者不放，求最小 $t$ 或报告无解。
>
> $n\in[2,1000],|x_i|,|y_i|\leq 10^9$。

首先显而易见的，$t$ 具有可二分性。于是我们二分答案，转化为判定当前 $t$ 是否可行。

注意到这个可以转化为图论模型：对于每个点，让它和所有本行或本列距离不超过 $t$ 的点连边，然后可以加点或不加点使得图连通就 ok。

注意到这里有一个很显然并且很有用的建图优化，即每个点只需要往上下左右四个方向各连最近的一个符合要求的点即可（没有符合要求的则不连），而不需要真的连「所有」符合要求的点，这样连通性显然不变，并且每个点连边数量是常数，总边数线性。

那么接下来的任务是如何高效的判断加点是否可以。考虑将加的点分为 $2$ 类。

1. 只在横向或纵向上做桥梁。这种点的数量显然是线性的，枚举行 / 列，再枚举本行 / 列所有相邻点对即可；
2. 两个方向上都做桥梁的。这个看起来数量不好控制，其实不然。注意到它显然要满足它所在行有点且所在列有点，那么所在行和所在列的数量各是线性的（离散化预处理即可）。直接枚举，是平方的。

然后考虑对于每个可能的加点的位置，如何判是否可行。显然可以先 DFS 连通分解，然后对于每个点就暴力 merge 即可。可撤销并查集的话是平方对数的，那么总复杂度就是平方二次对数，受不了。注意到每个点的 merge 量都是常数，所以完全可以直接暴力 set 或其他什么东西乱搞，看是否能把所有连通分量合并即可，随便怎么搞只要跟 $n$ 无关就是常数的。

还有一个需要思考的问题，就是第 $2$ 类点如何快速找到它两个方向上连的点对呢？sb 都会的是 `lower_bound`，可是那样会炸。可以 two-pointers 控制到均摊常数。

那么现在一次 check 就控制到平方了。于是总复杂度平方对数。

然后各种笔误 WA 了 2 发，wssb5448。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define X first
#define Y second
#define pb push_back
const int N=1000;
int n; 
pair<int,int> a[N+1];
vector<int> nei[N+1];
vector<int> nums_x,nums_y;
void discrete(){
	sort(nums_x.begin(),nums_x.end());
	nums_x.resize(unique(nums_x.begin(),nums_x.end())-nums_x.begin());
	sort(nums_y.begin(),nums_y.end());
	nums_y.resize(unique(nums_y.begin(),nums_y.end())-nums_y.begin());
}
int cnt,cid[N+1];
void dfs(int x){
	cid[x]=cnt;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(!cid[y])dfs(y);
	}
}
vector<pair<int,int> > row[N],col[N];
int now_r[N],now_c[N];
bool chk(int x){
	for(int i=1;i<=n;i++)nei[i].clear();
	for(int i=0;i<nums_x.size();i++){
		for(int j=0;j+1<row[i].size();j++)
			if(abs(row[i][j].X-row[i][j+1].X)<=x)
				nei[row[i][j].Y].pb(row[i][j+1].Y),nei[row[i][j+1].Y].pb(row[i][j].Y);
	}
	for(int i=0;i<nums_y.size();i++){
		for(int j=0;j+1<col[i].size();j++)
			if(abs(col[i][j].X-col[i][j+1].X)<=x)
				nei[col[i][j].Y].pb(col[i][j+1].Y),nei[col[i][j+1].Y].pb(col[i][j].Y);
	}
	cnt=0,memset(cid,0,sizeof(cid));
	for(int i=1;i<=n;i++)if(!cid[i])cnt++,dfs(i);
	if(cnt==1)return true;
	if(cnt<=2){
		for(int i=0;i<nums_x.size();i++){
			for(int j=0;j+1<row[i].size();j++)
				if(cid[row[i][j].Y]!=cid[row[i][j+1].Y]&&abs(row[i][j].X-row[i][j+1].X)+1>>1<=x)return true;
		}
		for(int i=0;i<nums_y.size();i++){
			for(int j=0;j+1<col[i].size();j++)
				if(cid[col[i][j].Y]!=cid[col[i][j+1].Y]&&abs(col[i][j].X-col[i][j+1].X)+1>>1<=x)return true;
		}
	}
	memset(now_r,0,sizeof(now_r)),memset(now_c,0,sizeof(now_c));
	if(cnt<=4)for(int i=0;i<nums_x.size();i++)for(int j=0;j<nums_y.size();j++){
		int xx=nums_x[i],yy=nums_y[j];
		while(now_r[i]<row[i].size()&&row[i][now_r[i]].X<yy)now_r[i]++;
		while(now_c[j]<col[j].size()&&col[j][now_c[j]].X<xx)now_c[j]++;
		if(now_r[i]<row[i].size()&&row[i][now_r[i]].X==yy)continue;
		set<int> st;
		if(now_r[i]&&abs(row[i][now_r[i]-1].X-yy)<=x)st.insert(cid[row[i][now_r[i]-1].Y]);
		if(now_r[i]<row[i].size()&&abs(row[i][now_r[i]].X-yy)<=x)st.insert(cid[row[i][now_r[i]].Y]);
		if(now_c[j]&&abs(col[j][now_c[j]-1].X-xx)<=x)st.insert(cid[col[j][now_c[j]-1].Y]);
		if(now_c[j]<col[j].size()&&abs(col[j][now_c[j]].X-xx)<=x)st.insert(cid[col[j][now_c[j]].Y]);
		if(st.size()==cnt&&*st.begin()==1&&*--st.end()==cnt)return true;
	}
	return false;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].X>>a[i].Y,nums_x.pb(a[i].X),nums_y.pb(a[i].Y);
	discrete();
	for(int i=1;i<=n;i++){
		row[lower_bound(nums_x.begin(),nums_x.end(),a[i].X)-nums_x.begin()].pb(mp(a[i].Y,i));
		col[lower_bound(nums_y.begin(),nums_y.end(),a[i].Y)-nums_y.begin()].pb(mp(a[i].X,i));
	}
	for(int i=0;i<nums_x.size();i++)sort(row[i].begin(),row[i].end());
	for(int i=0;i<nums_y.size();i++)sort(col[i].begin(),col[i].end());
	int ans=4e9;
	for(int i=32;~i;i--)if(ans-(1ll<<i)>=0&&chk(ans-(1ll<<i)))ans-=1ll<<i;
	cout<<(ans==4e9?-1:ans);
	return 0;
}
```

---

## 作者：Chinese_zjc_ (赞：0)

本题只要稍加思考,即可发现:若 $ T $ 是可行的, $ T+1 $ 也是可行的.

那么我们考虑使用二分来求出最小的 $ T $ .

然后我们就开始二分答案了.

二分的步骤显然是判断 $ T=mid $ 时是否可行,若可行则 $ r=mid $ ,否则 $ l=mid+1 $ .

关键在于如何判断 $ T=mid $ 时是否可行.

我们先看不加点的情况.

显然若 $ a $ 点能到 $ c $ 点,而 $ b $ 点能到 $ c $ 点,则 $ a $ 点也能到 $ b $ 点.

这不是明显的 $ dsu $ (并查集)模板吗?

直接 $ n^2 $ 枚举一下边然后连接就可以了( $O(n^2)$ ).

在这之后,就只剩下了 $ cnt $ 个联通块,我们分类讨论 $ T $ 可行的情况(下面的 $ A,B,C,D $ 点均不在同一联通块中, $ ANS $ 表示可加的点,下面假设 $ T=4 $ ).

首先看 $ cnt=1 $ 的情况,显然 $ n $ 个点已经联通,说明 $ T $ 可行.

再看 $ cnt=2 $ 的情况,显然只有下面两种情况:

![cnt=2,1](https://cdn.luogu.com.cn/upload/image_hosting/nuh79bpx.png)

 $ |x_A-x_B|\leq T $ 且 $ |y_A-y_B|\leq T $ .

![cnt=2,2](https://cdn.luogu.com.cn/upload/image_hosting/tqwfq724.png)

 $ |x_A-x_B|\leq T+T $ 且 $ y_A=y_B $ 或 $ x_A=x_B $ 且 $ |y_A-y_B|\leq T+T $ .

然后再看 $ cnt=3 $ 的情况,无论如何,旋转之后必定是类似这样:

![cnt=3](https://cdn.luogu.com.cn/upload/image_hosting/epejf2kb.png)

即同时满足两个条件: $ |x_A-x_B|\leq T $ 且 $ |y_A-y_B|\leq T $ 和 $ |x_B-x_C|\leq T $ 且 $ |y_B-y_C|\leq T $ .

接下来, $ cnt=4 $ 的情况也是类似:

![cnt=4](https://cdn.luogu.com.cn/upload/image_hosting/difpmyfk.png)

即同时满足四个条件: $ |x_A-x_B|\leq T $ 且 $ |y_A-y_B|\leq T $ , $ |x_B-x_C|\leq T $ 且 $ |y_B-y_C|\leq T $ , $ |x_C-x_D|\leq T $ 且 $ |y_C-y_D|\leq T $ 和 $ |x_D-x_A|\leq T $ 且 $ |y_D-y_A|\leq T $ .

然后 $ cnt>4 $ 的情况,因为加一个点只能向四个方向运动,即最多只能连 $ 4 $ 条边,合并 $ 4 $ 个联通块,因此 $ cnt>4 $ 时加一个点并不能解决问题,故没有可行的情况.

那我们就可以直接大力分类讨论了.

用 $ g[i][j] $ 表示联通块 $ i $ 与联通块 $ j $ 相连的可行点集合,检查一个点是否同时在几个集合内即可.

使用 $ STL $ $set$ 的代码: [Time Limit Exceeded on test 131](https://codeforces.com/contest/1419/submission/93320253).

看来这样并不太行,我们需要使用别的方法.

不难发现数据范围 $ n\leq1000 $ 也就是说最多只会有 $ n $ 种 $ x $ 坐标, $ n $ 种 $ y $ 坐标.

那我们可以离散化坐标,然后就只剩下 $ n^2 $ 个坐标了,最后用二维数组维护即可.

具体见代码.

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
//头文件已省略
#define int long long
#define double long double
using namespace std;
const double PI = acos(-1);
const double eps = 0.0000000001;
const int INF = 0x3fffffffffffffff;
int n, x[1005], y[1005], cntx, cnty, LOWLIM = 0, HIGHLIM = INF, fa[1005], name[1005], cnt;
const int g[5][5] = {//预处理出状压矩阵
    {0, 0, 0, 0, 0},
    {0, 0, 1, 2, 3},
    {0, 1, 0, 4, 5},
    {0, 2, 4, 0, 6},
    {0, 3, 5, 6, 0}};
int connect[1005][1005];
//注意这个数组,是用状压来存(x[i],y[i])这个位置可以连接哪几个联通块的.
struct L
{
    int x, y;
} a[1005];
set<int> tmpx, tmpy;//离散化用的
int find(int now)//并查集
{
    return now == fa[now] ? now : fa[now] = find(fa[now]);
}
int lowbit(int now)//这个不多说了吧
{
    return now & (-now);
}
int has(int now)//求一个数字的二进制有多少个1
{
    return now ? has(now ^ lowbit(now)) + 1 : 0;
}
bool check(int now)//now即mid
{
    for (int i = 1; i <= n; ++i) //初始化
    {
        fa[i] = i;
        name[i] = 0;
    }
    memset(connect, 0, sizeof connect);
    cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            if (find(i) != find(j))
            {
                if (abs(x[a[i].x] - x[a[j].x]) <= now && a[i].y == a[j].y)
                {
                    fa[find(i)] = find(j);
                }
                if (a[i].x == a[j].x && abs(y[a[i].y] - y[a[j].y]) <= now)
                {
                    fa[find(i)] = find(j);
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) //name是find(i)的新编号(离散化)
    {
        if (!name[find(i)])
        {
            name[find(i)] = ++cnt;
        }
    }
    if (cnt == 1)
    {
        return true;
    }
    if (cnt == 2)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i + 1; j <= n; ++j)
            {
                if (find(i) != find(j))
                {
                    if (a[i].x == a[j].x && abs(y[a[i].y] - y[a[j].y]) <= now << 1)
                    {
                        return true;
                    }
                    if (abs(x[a[i].x] - x[a[j].x]) <= now << 1 && a[i].y == a[j].y)
                    {
                        return true;
                    }
                    if (abs(x[a[i].x] - x[a[j].x]) <= now && abs(y[a[i].y] - y[a[j].y]) <= now)
                    {
                        return true;
                    }
                }
            }
        }
    }
    if (cnt == 3)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i + 1; j <= n; ++j)
            {
                if (find(i) != find(j))
                {
                    if (abs(x[a[i].x] - x[a[j].x]) <= now && abs(y[a[i].y] - y[a[j].y]) <= now)
                    {
                        connect[a[i].x][a[j].y] |= 1 << g[name[find(i)]][name[find(j)]];
                        connect[a[j].x][a[i].y] |= 1 << g[name[find(i)]][name[find(j)]];
                    }
                }
            }
        }
        for (int i = 1; i <= cntx; ++i)
        {
            for (int j = 1; j <= cnty; ++j)
            {
                if (has(connect[i][j]) >= 2)
                {
                    return true;
                }
            }
        }
    }
    if (cnt == 4)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i + 1; j <= n; ++j)
            {
                if (find(i) != find(j))
                {
                    if (abs(x[a[i].x] - x[a[j].x]) <= now && abs(y[a[i].y] - y[a[j].y]) <= now)
                    {
                        connect[a[i].x][a[j].y] |= 1 << g[name[find(i)]][name[find(j)]];
                        connect[a[j].x][a[i].y] |= 1 << g[name[find(i)]][name[find(j)]];
                    }
                }
            }
        }
        for (int i = 1; i <= cntx; ++i)
        {
            for (int j = 1; j <= cnty; ++j)
            {
                if (has(connect[i][j]) >= 4)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i].x >> a[i].y;
        tmpx.insert(a[i].x);
        tmpy.insert(a[i].y);
    }
    for (auto i : tmpx)
    {
        x[++cntx] = i;
    }
    for (auto i : tmpy)
    {
        y[++cnty] = i;
    }
    //使用了auto来离散化
    //for(auto i:sth){...}意义同
    //for(typename<sth>::iterator ii=sth.begin();ii!=sth.end();++ii)
    //{typename i=*ii;...}
    //注意:auto仅限C++11以上版本可用,之前的版本是无意义的
    for (int i = 1; i <= n; ++i) //把a数组的x,y重编号
    //(x[a[i].x],y[a[i].y])即a[i]原来的坐标
    {
        a[i].x = find(x + 1, x + 1 + cntx, a[i].x) - x;
        a[i].y = find(y + 1, y + 1 + cnty, a[i].y) - y;
    }
    while (LOWLIM < HIGHLIM) //二分答案
    {
        int mid = (LOWLIM + HIGHLIM) >> 1;
        if (check(mid))
        {
            HIGHLIM = mid;
        }
        else
        {
            LOWLIM = mid + 1;
        }
    }
    cout << (LOWLIM < INF ? LOWLIM : -1) << endl;
    return 0;
}
```


---

