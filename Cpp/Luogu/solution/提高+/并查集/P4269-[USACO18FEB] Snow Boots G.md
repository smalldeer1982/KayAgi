# [USACO18FEB] Snow Boots G

## 题目描述

到冬天了，这意味着下雪了！从农舍到牛棚的路上有 $N$ 块地砖，方便起见编号为 $1 \dots N$，第 $i$ 块地砖上积了 $f_i$ 英尺的雪。
在 Farmer John 的农舍的地窖中，总共有 $B$ 双靴子，编号为 $1 \dots B$。其中某些比另一些结实，某些比另一些轻便。具体地说，第 $i$ 双靴子能够让 FJ 在至多 $s_i$ 英尺深的积雪中行走，能够让 FJ 每步至多前进 $d_i$。

Farmer John 从 $1$ 号地砖出发，他必须到达 $N$ 号地砖才能叫醒奶牛们。$1$ 号地砖在农舍的屋檐下，$N$ 号地砖在牛棚的屋檐下，所以这两块地砖都没有积雪。帮助 Farmer John 求出哪些靴子可以帮助他走完这段艰辛的路程。

## 样例 #1

### 输入

```
8 7
0 3 8 5 6 9 0 0
0 5
0 6
6 2
8 1
10 1
5 3
150 7```

### 输出

```
0
1
1
0
1
1
1
```

# 题解

## 作者：攀岩高手 (赞：37)

- 除了链表和并查集，还有线段树的方法。

---

- 对于靴子 $i$ ，我们将它能走的地砖的权值设为 $0$，不能走的地砖的权值设为 $1$ ，并使用线段树维护区间最长的连续的 $1$ 的长度，也就是最长连续的不能走的那段地砖的数量。如果这个值小于靴子 $i$ 的步长，那么答案为 $1$；否则靴子 $i$ 一定无法跨过这段地砖，所以答案为 $0$ 。

- 然而每次枚举一只靴子并在线段树上修改的时间复杂度是 $O(NlogN)$ 的，显然不能过。考虑先将线段树赋为全 $1$ （都不能走），把地砖和靴子按照雪的深度排序，从小到大开始扫描。如果扫到地砖，则在线段树中把这块地砖的位置改为 $0$ （因为以后扫到的靴子能承受的积雪深度都不小于这块地砖的积雪深度，也就是都能走这块地砖）；如果扫到靴子，就统计最长连续的不能走的那段地砖的数量，计算答案。

- 线段树单点修改是 $O(logN)$ 的，查询最长连续 $1$ 的时间复杂度则是 $O(1)$。总时间复杂度：$O(NlogN+B)$。

---

- 附：线段树维护最长连续 $1$ 的方法：

- 每个结点维护四个值：当前节点维护的区间长度 $len$ ，当前区间最长连续 $1$ 的长度 $maxx$ ，当先区间从左端点开始的最长连续 $1$ 的长度 $maxl$，当先区间从右端点开始的最长连续 $1$ 的长度 $maxr$。

- 那么，当前节点的 $maxl$ 就应该等于它左儿子的 $maxl$ ；如果左儿子的 $maxx$ 等于左儿子维护的区间的长度，就表示左儿子维护的区间全是 $1$ ，那么当前节点 $maxl$ 就应该等于左儿子维护的区间的长度加上右儿子的 $maxl$ 。$maxr$ 的维护方式类似。

- 当前结点的 $maxx$ 则等于它左儿子的 $maxx$ ，右儿子的 $maxx$ ，以及左儿子的 $maxr$ 和 右儿子的 $maxl$ 之和（表示跨越左儿子和右儿子维护的两个区间）这三者的最大值。

- 具体实现见 $pushup$ 函数的代码。

---

代码实现（c++）：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=110000;
struct SegmentTree
{
	#define lc (root<<1)
	#define rc (root<<1|1)
	struct Node
	{
		bool val;
		int len, maxx, maxl, maxr;
	} tr[MAXN*4];
	void pushup(int root) // 维护区间信息
	{
		tr[root].len=tr[lc].len+tr[rc].len;
		tr[root].maxx=tr[root].maxl=tr[root].maxr=tr[root].val;
		tr[root].maxl=max(tr[root].maxl, tr[lc].maxl);
		if (tr[lc].maxx==tr[lc].len)
			tr[root].maxl=max(tr[root].maxl, tr[lc].len+tr[rc].maxl);
		tr[root].maxr=max(tr[root].maxr, tr[rc].maxr);
		if (tr[rc].maxx==tr[rc].len)
			tr[root].maxr=max(tr[root].maxr, tr[rc].len+tr[lc].maxr);
		tr[root].maxx=max(tr[root].maxx, tr[lc].maxx);
		tr[root].maxx=max(tr[root].maxx, tr[rc].maxx);
		tr[root].maxx=max(tr[root].maxx, tr[lc].maxr+tr[rc].maxl);
	}
	void update(int root, int l, int r, int x) // 单点修改
	{
		if (l==r)
		{
			tr[root].maxx=tr[root].maxl=tr[root].maxr=tr[root].val=0;
			return;
		}
		int mid=l+r>>1;
		if (x<=mid) update(lc, l, mid, x);
		else update(rc, mid+1, r, x);
		pushup(root);
	}
	int query() // 查询
	{
		return tr[1].maxx; // 1 就是树根结点，维护了整个区间
	}
	void build(int root, int l, int r)
	{
		tr[root].val=0;
		if (l==r)
		{
			tr[root].len=1;
			tr[root].maxx=tr[root].maxl=tr[root].maxr=tr[root].val=1;
			return;
		}
		int mid=l+r>>1;
		build(lc, l, mid);
		build(rc, mid+1, r);
		pushup(root);
	}
	#undef lc
	#undef rc
} st;
struct Snow // 这里定义了一个结构体用来排序时记录下标
{
	int id, step, dep;
	bool operator < (const Snow& rhs) const
	{
		return dep!=rhs.dep?dep<rhs.dep:step<rhs.step;
	}
	Snow(int i=0, int s=0, int d=0):
		id(i), step(s), dep(d) {}
} a[MAXN*2];
int n, m;
bool ans[MAXN];
int main()
{
	freopen("snowboots.in", "r", stdin);
	freopen("snowboots.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=1, f; i<=n; i++)
	{
		scanf("%d", &f);
		a[i]=Snow(i, 0, f);
	}
	for (int i=1, s, d; i<=m; i++)
	{
		scanf("%d%d", &s, &d);
		a[i+n]=Snow(i, d, s);
	}
	sort(a+1, a+n+m+1);
	st.build(1, 1, n);
	for (int i=1; i<=n+m; i++)
	{
		if (a[i].step==0) st.update(1, 1, n, a[i].id);
		else ans[a[i].id]=st.query()<a[i].step;
	}
	for (int i=1; i<=m; i++) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：quest_2 (赞：17)

一看，题是奶牛题，所以整点阳间的题意还是很重要的。

```
有N块地砖和M双靴子。
第i块地砖上有snow[i]的积雪。
每一双靴子有两个值。
dep:表示这双靴子的高度，你不能在“积雪深度高于靴子的地砖”上落脚。
step：表示穿这双鞋时一步最多能跨多远。
（也就是最多可以隔多远落一次脚）
对于每一双靴子，求穿着这双靴子能否从1号地砖安全抵达N号。
```
一眼看去，水题，暴力每一双鞋，都试着去走通一下，复杂度再怎么优化也是 $O(N^2)$ 起步。

但是数据范围并不允许这么做，我们需要更高效的解法。


------------


我们想到，不管穿的哪一双鞋，该走的路都是那一条，只是相对于不同的靴子，有不同的**落不了脚的地方**，我们称这些地方叫绊脚石。

**『真正有杀伤力的地方，往往是连续的绊脚石。』**

为什么？对于绊脚石，我们唯一的出路就是**跨步跳过他**。而要是步子已经迈到最大，却还是跨不过长长的连续绊脚石的时候，这双靴子就GG了。为了易于理解，我们用一个绊脚石的大小，来指代**绊脚石的连续长度**。

很容易领悟到，最大绊脚石的大小是相对的，对于每一双靴子，都会有**不同的**最大绊脚石。

我们之前提到：要是穿着一双靴子时步子已经迈到最大，却还是跨不过（对于这双靴子而言的）最大绊脚石的时候，这双靴子就GG了。

所以我们这时就希望找出每一双靴子的最大的绊脚石在哪里。

我们清楚，对于高度更低的靴子，他的绊脚石只会更多。那要是我们有一个按高度递减的靴子序列，那么我们就有了一个**递增的**绊脚石序列。

那很显然，我们要对靴子以高度为关键字排出降序。这样我们在求每一双靴子的最大绊脚石的时候，就只用在上一双靴子的绊脚石大小的基础上只增不减，有效地优化了时间。

但如何求绊脚石大小还是需要一番推敲。

我们说过：**落不了脚的地方**称作绊脚石。这里的落不了脚转化成判断条件就是**靴子高度小于该格雪深**，看到这里，我们恍恍惚惚就有了求最大绊脚石的做法。

要是一个地砖是绊脚石，就把他**染成黑色**。最后我们找最大绊脚石就是找**最长的联通黑色区域**。

被染色的地方都满足雪深高于一个值（靴子高度），而我们又知道只有在哪一格上染色的时候，才有可能更新最大绊脚石的大小，所以我们又起了点优化的心思。

把地砖以雪深为关键字排个降序，我们染色的时候，只用做 $\operatorname{while}$ 直到雪深低于靴子高度就可以停了。因为这之后都不再染色了，也就不会更新最大绊脚石。这也是一种时间的缩减。

求联通块我们再熟悉不过了，用**并查集**就是一种极佳的办法（参考Kruskal）。

具体实现出来就是：如果染色时这个位置的上一格是黑色，则要**将他们用并查集并起来，再看看是否要更新最长连通块长度**。仅此而已。

而求出来的最长联通块毕竟只是对于当前靴子而言，那我们如何在各个靴子之间传递信息呢？

目前当不了最长联通块的联通块并不是一无是处，将来可能还会将他和其他联通块并起来，所以我们要开一个 $cross$ 数组，表示**以这块地砖为结尾，前面有多长的联通块**。这个数组初始化为1，毕竟每块地砖最早时自己都是一个联通块。而 $cross$ 里的值，在被染色且上一格是黑色时会进行更新。

而以上我们讲的都是与上一块联通，而与下一块联通也同样重要，这样我们的染色才能有时起到联结两个联通块的作用。

整个求绊脚石部分的代码如下：

```cpp
int cnt = 1;
//这里指我们走到了第几块地砖。
//因为靴子高度递减，所以到下一双靴子时，地砖的染色直接往下一块地砖判断即可。
//上一双靴子时被染色的位置，下一双一定还是染着色的。

for (register int i = 1; i <= M; i++) //i代表第i双靴子
{
	while (cnt <= N && bri[cnt].snow > boo[i].dep)
    //while的条件里，bri即地砖，boo即靴子
	{
		maxcross = max(maxcross, 1);//联通块大小少说也得有一个
        
		color[bri[cnt].id] = 1;//color代表这个地砖是否被染色
        //因为我们之前sort过地砖，所以在位置顺序上还是得用他原来的id
        
		if (color[bri[cnt].id - 1])//上一格被染色
		{
        	/*以下为并查集“并”的基操*/
			int x = find(bri[cnt].id - 1);
            int y = find(bri[cnt].id);
			fa[x] = y;
            
			cross[y] += cross[x];//这样更新cross
            //我们cross初值赋的是1
            
			maxcross = max(maxcross, cross[y]);
            //可能会更新最长联通块
		}
        
        /*下一格同上*/
		if (color[bri[cnt].id + 1])
		{
			int x = find(bri[cnt].id);
            int y = find(bri[cnt].id + 1);
			fa[x] = y;
			cross[y] += cross[x];
			maxcross = max(maxcross, cross[y]);
		}
        
		cnt++;
	}
	if (maxcross < boo[i].step)//若这双靴子能克服最大绊脚石
	{
		Cout[boo[i].id] = 1;//输出的是1
	}
}
```
全过程的复杂度大体是 $O(N \log N)$ ，$\operatorname{sort}$ 的时间复杂度。

以下为完整代码（比线段树的版本短多了～）：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5 + 7;
struct shoe
{
	int step;
	int dep;
	int id;
} boo[MAX];
struct brick
{
	int snow;
	int id;
} bri[MAX];
bool cmp1(shoe a, shoe b)
{
	return a.dep > b.dep;
}
bool cmp2(brick a, brick b)
{
	return a.snow > b.snow;
}
int cnt = 1;
int color[MAX], cross[MAX];
int fa[MAX];
int maxcross = 0;
int Cout[MAX];
inline int find(int x)
{
	if (x == fa[x])
		return x;
	return fa[x] = find(fa[x]);
}
int read()
{
	int num = 0, bj = 0;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
		{
			bj = 1;
		}
		ch = getchar();
	}
	while (isdigit(ch))
	{
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return bj ? -num : num;
}
int main()
{
	int N, M;
	cin >> N >> M;
	for (register int i = 1; i <= N; i++)
	{
		bri[i].snow = read();
		bri[i].id = i;
	}
	for (register int i = 1; i <= M; i++)
	{
		boo[i].dep = read();
		boo[i].step = read();
		boo[i].id = i;
	}
	sort(bri + 1, bri + 1 + N, cmp2);
	sort(boo + 1, boo + 1 + M, cmp1);
	for (register int i = 1; i <= N; i++)
	{
		cross[i] = 1;
		fa[i] = i;
	}
	for (register int i = 1; i <= M; i++)
	{
		while (cnt <= N && bri[cnt].snow > boo[i].dep)
		{
			maxcross = max(maxcross, 1);
			color[bri[cnt].id] = 1;
			if (color[bri[cnt].id - 1])
			{
				int x = find(bri[cnt].id - 1), y = find(bri[cnt].id);
				fa[x] = y;
				cross[y] += cross[x];			 
				maxcross = max(maxcross, cross[y]);
			}
			if (color[bri[cnt].id + 1])
			{
				int x = find(bri[cnt].id), y = find(bri[cnt].id + 1);
				fa[x] = y;
				cross[y] += cross[x];
				maxcross = max(maxcross, cross[y]); 
			}
			cnt++;
		}
		if (maxcross < boo[i].step)
		{
			Cout[boo[i].id] = 1;
		}
	}
	for (register int i = 1; i <= M; i++)
	{
		printf("%d\n", Cout[i]);
	}
}
```

洛谷的版本不需要卡常，但是其他OJ上就很难说了。

不过卡一卡都是过得了的。

---

## 作者：zzzty___ (赞：17)

具体讲解都在代码里，自己看哈，这里就不多解释了。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxnb=1e5+5;
int n,b,i,j,maxsteps=1/*最少也要走一步吧*/,last[Maxnb],next[Maxnb];//last和next是双向链表 
bool get[Maxnb];
struct snow{int snowdeep,sloc;}f[Maxnb];//snowdeep是雪的深度，sloc是雪的位置 
struct bost{int bostdeep,dis,bloc;}s[Maxnb];//bostdeep是靴子能承受的雪的深度，dis是靴子能走的距离，bloc是靴子的位置 

bool compsnow(snow a,snow b){return a.snowdeep<b.snowdeep;}
bool compbost(bost a,bost b){return a.bostdeep<b.bostdeep;}

int main()
{
	memset(get,0,sizeof(get));
	cin>>n>>b;
	for(i=1;i<=n;++i) cin>>f[i].snowdeep,f[i].sloc=i;//因为要排序，所以还是要记录一下这个积雪的位置 
	for(i=1;i<=b;++i) cin>>s[i].bostdeep>>s[i].dis,s[i].bloc=i;//同上 
	sort(f+1,f+n+1,compsnow);
	sort(s+1,s+b+1,compbost);
	for(i=1;i<=n;++i) last[i]=i-1,next[i]=i+1;//双向链表，last指向前一个积雪，next指向下一个积雪 
	j=n;//当然从积雪最大的开始枚举喽! 
	for(i=b;i>=1;--i)//我是升序排的，所以要倒着循环 。应该也可以按降序排，我没试过，有兴趣可以尝试一下 
	{
	    while(j>=1 && f[j].snowdeep>s[i].bostdeep)//这里是整个算法的核心
		/*
		我们可以假设这条靴子能走过去，所以要找到比它能承受积雪的深度的范围更大的积雪的深度，并把它从双向链表中删除
		然后我们可以求出能走去的距离，如果这个靴子能走的步数小于它，那么也就不可能到达。
		当然，这样是不够的，也许会超时。
		所以我们就需要排序。
		我们可以想想看，一个比你能承受积雪深度更大的靴子都走不过去，那你肯定走不过去。
		因此maxsteps可以帮助我们判断。 
		*/ 
		{
		    last[next[f[j].sloc]]=last[f[j].sloc];
		    next[last[f[j].sloc]]=next[f[j].sloc];//这两句话是删除双向链表中一个点的语句，如果觉得难理解，就背下来吧 
		    maxsteps=max(maxsteps,next[f[j].sloc]-last[f[j].sloc]);
		    j--;
		}
		get[s[i].bloc]=(s[i].dis>=maxsteps);
		/*这里是简便写法 
		也可以这样写:
		if(s[i].dis>=maxsteps) get[s[i].bloc]=1;
		*/ 
	}
	for(i=1;i<=b;++i) cout<<get[i]<<endl;
	return 0;
}
```

---

## 作者：yyyyxh (赞：7)

提供一个值域线段树的做法

## 思路
首先转化一下题意：对于每个 $s_i,d_i$ 相当于求存不存在一段长为 $d_i$ 的区间满足其中的最小值大于 $s_i$ ，不存在输出 `YES`，否则输出 `NO` (这样的话这段区间一定跨不过去)

考虑预处理长为 $i$ 的所有区间最小值中的最大值为 $f_i$

暴力去求是 $O(n^2)$ 的，反过来考虑序列中的每一个数对于 $f_i$ 的贡献。可以按值从小到大排序，依次加入数组中，由于已加入的数一定比当前数小，那么以当前数为最小值的区间一定是它的前驱到它的后继 $[pre_x+1,nxt_x-1]$ 的一段，长为 $nxt_x-pre_x-1$ ，则 $\forall_{i \ge nxt_x-pre_x-1}\  f_i=x$

用值域线段树维护即可

```cpp
#include <bits/stdc++.h>
#define rg register
using namespace std;
const int N=100003;
struct node{
	int i,v;
	bool operator <(const node x)const{
		return v<x.v;
	}
}a[N];
int reads(){
	rg char c;
	int x=0;
	while (!isdigit(c=getchar()));
	do x=(x<<1)+(x<<3)+(c^48);
	while (isdigit(c=getchar()));
	return x;
}
int f[N],n,m;
namespace ST{
	bool val[4*N];
	int l[4*N],r[4*N];
	void ins(int p,int x){
		if (l[p]==r[p]) {val[p]=1; return;}
		int mid=(l[p]+r[p])>>1;
		if (x<=mid) ins(2*p,x);
		else ins(2*p+1,x);
		val[p]=val[2*p]||val[2*p+1];
	}
	void bld(int ll,int rr,int p){
		l[p]=ll; r[p]=rr; val[p]=0;
		if (ll==rr) return ;
		int mid=(ll+rr)>>1;
		bld(ll,mid,2*p); bld(mid+1,rr,2*p+1);
	}
	int loc(int p,int x){
		if (l[p]==r[p]) return p;
		int mid=(l[p]+r[p])>>1;
		if (x<=mid) return loc(2*p,x);
		else return loc(2*p+1,x);
	}
	int pre(int x){
		int p=loc(1,x);
		while (p!=1&&(!val[p^1]||!(p&1))) p>>=1; p^=1;
		if (!p) return 0;
		while (l[p]!=r[p]) if (val[2*p+1]) p=2*p+1; else p=2*p;
		return l[p];
	}
	int nxt(int x){
		int p=loc(1,x);
		while (p!=1&&(!val[p^1]||(p&1))) p>>=1; p^=1;
		if (!p) return n+1;
		while (l[p]!=r[p]) if (val[2*p]) p=2*p; else p=2*p+1;
		return l[p];
	}
}
int main(){
//	freopen("boots.in","r",stdin);
//	freopen("boots.out","w",stdout);
	n=reads(); m=reads();
	ST::bld(1,n,1);
	for (rg int i=1; i<=n; i++) a[i]=(node){i,reads()};
	sort(a+1,a+n+1);
	for (rg int i=1; i<=n; i++){
		ST::ins(1,a[i].i);
		f[ST::nxt(a[i].i)-ST::pre(a[i].i)-1]=a[i].v;
	}
	for (rg int i=n-1; i; i--) f[i]=max(f[i],f[i+1]);
	for (rg int i=1; i<=m; i++){
		int s=reads(),d=reads();
		if (s>=f[d]) puts("1");
		else puts("0");
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
} 	
```


---

## 作者：ASSWECAN (赞：7)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这题不用链表也可以呀，蒟蒻我用的是并查集。每次先按积雪深度从大到小排序，靴子承受度从大到小排序，先把不能走到的地方并起来，那么显然只要$d_i\gt$连续不能走的地方的长度的最大值答案为$1$，反之为$0$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
int n,b;
int l[100010],r[100010];
pair<int,int>tiles[100010];
int par[100010];
int rnk[100010];
int siz[100010];
bool f[100010];
bool ans[100010];
int res;
pair<int,pair<int,int> >boots[100010];
int getpar(int x)
{
	return x==par[x]?x:par[x]=getpar(par[x]);
}
void un(int x,int y)
{
	x=getpar(x);y=getpar(y);
	if(x==y)return;
	if(rnk[x]<rnk[y])
	{
		par[x]=y;
		siz[y]+=siz[x];
	}
	else
	{
		if(rnk[x]==rnk[y])rnk[x]++;
		par[y]=x;
		siz[x]+=siz[y];
	}
}
int main()
{
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		tiles[i]=make_pair(x,i);
		par[i]=i;
		siz[i]=1;
		f[i]=false;
	}
	for(int i=1;i<=b;i++)
	{
		int s,d;
		scanf("%d%d",&s,&d);
		boots[i]=make_pair(s,make_pair(d,i));
	}
	sort(tiles+1,tiles+n+1);
	reverse(tiles+1,tiles+n+1);
	sort(boots+1,boots+n+1);
	reverse(boots+1,boots+n+1);
	int pos=1;
	for(int i=1;i<=b;i++)
	{
		while(pos<=n && tiles[pos].first>boots[i].first)
		{
			int x=tiles[pos].second;
			f[x]=true;
			if(f[x-1])un(x-1,x);
			if(f[x+1])un(x,x+1);
			res=max(res,siz[getpar(x)]);
			pos++;
		}
		if(res<boots[i].second.first)ans[boots[i].second.second]=true;
	}
	for(int i=1;i<=b;i++)if(ans[i])puts("1");else puts("0");
	return 0;
}
```

---

## 作者：feecle6418 (赞：3)

先预处理出只经过 $\le i$ 的点，至少每一步需要跨多大距离。

把所有 $f_i$ 从小到大排序，依次加入一个数据结构中，需要查询相邻两点距离的最大值。用两个 set 就可以维护（或者一个 set 一个可删除堆），先在第一个 set 中找到左边右边的点，删除这两点间距离，加入新点到左边右边的点的距离，再查询最大值。

对每个询问，假如能走的距离大于等于只走 $\le s$ 的最小距离就可行，否则不可行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],ans[100005],c[100005];
struct P{
	int x,id;
}b[100005];
bool operator <(P o,P oo){return o.x<oo.x;};
multiset<int> s,q;
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]={a[i],i},c[i]=a[i];
	sort(b+1,b+n+1),sort(c+1,c+n+1);
	c[0]=unique(c+1,c+n+1)-c-1;
	s.insert(1),s.insert(n),q.insert(n-1),ans[1]=n-1;
	for(int i=1,j=1;i<=n;i=j){
		while(j<=n&&b[j].x==b[i].x)j++;
		int pos=lower_bound(c+1,c+c[0]+1,b[i].x)-c;
		for(int k=i;k<j;k++){
			if(b[k].id<2||b[k].id>n-1)continue;
			auto it=s.lower_bound(b[k].id),it2=it;
			it2--;
			q.erase(q.find(*it-*it2)),q.insert(b[k].id-*it2),q.insert(*it-b[k].id);
			s.insert(b[k].id);
		}
		ans[pos]=*--q.end();
	}
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		int pos=upper_bound(c+1,c+c[0]+1,x)-c-1;
		if(y>=ans[pos])puts("1");
		else puts("0");
	}
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：3)

链表，单调队列，线段树，并查集，怎么多方法，来一个multiset解

可以注意到一个一个性质：如果两个含有小于等于 $s_i$ 的位置的距离肯定小于等于 $d_i$，那第 $i$ 靴子是可以使用的。

所以，可以按 $s_i$ 非递增遍历这些靴子，并且使用一个set维护哪些位置的雪量小于等于一个递减值。同事，也需要维护一个multiset，保存相邻没有从set里删除的位置的两两距离。如果把位置按非递增雪量排序，着就等价于每一次遍历一个位置吧这个位置在set里删除。应为set是自动排序的，这样就可以同事更新multiset。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

multiset<int> distances;
set<int> curreach;

vector<pii> location;
vector<pair<pii, int>> boot;
int answer[100005];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, bc; cin >> N >> bc;
    rep1(i, N) {
        int v; cin >> v;
        if(i != 1 && i != N) location.pb({v, i});
    }
    rep(i, bc) {
        int st, di; cin >> st >> di;
        boot.pb({{st, di}, i});
    }
    sort(all(location));
    sort(all(boot));
    int cbp = bc-1;
    rep1(i, N) curreach.insert(i); 
    rep(i, N-1) distances.insert(1);
    while(cbp >= 0 && boot[cbp].fi.fi >= location.back().first) {
        answer[boot[cbp].se] = *(--distances.end()) <= boot[cbp].fi.se;
        cbp--;
    }
    for(int i=location.size()-1; i>=0; i--) {
        int loc = location[i].se;
        curreach.erase(loc);
        auto pt = curreach.lower_bound(loc);
        int rig = *pt; int lef = *(--pt);
        distances.insert(rig-lef);
        distances.erase(distances.find(rig-loc)); distances.erase(distances.find(loc-lef));
        if(!i) break;
        while(cbp >= 0 && boot[cbp].fi.fi >= location[i-1].fi) {
            answer[boot[cbp].se] = *(--distances.end()) <= boot[cbp].fi.se;
            cbp--;
        }
    }
    while(cbp >= 0 && boot[cbp].fi.fi >= 0) {
        answer[boot[cbp].se] = *(--distances.end()) <= boot[cbp].fi.se;
        cbp--;
    }
    rep(i, bc) cout << answer[i] << endl;
}

```

---

## 作者：hmya (赞：2)

首先考虑问题本质。

问题是一双靴子能不能走到终点，这个靴子最大跨度为$d$，最大高度为 $s$ 。

如果遇到了高度为 $s$ 的雪堆，这双靴子就过不去了么？

当然不是，这双靴子最大跨度为 $d$ ，如果高度比$s$大，那么这双靴子就能跨过去。

照这么说，总不会所有雪堆都能跨过去吧？

不对，因为跨度最多为 $d$ ，如果高度比 $s$ 大的雪堆连续有 $d$ 堆，那么我的靴子就跨不过去，也就到达不了终点。

这么一分析，问题变成了**连续的高度比 $s$ 大的雪堆的数量是不是比 $d$ 小，如果比 $d$ 小，靴子就能走过去，否则就不能**

再来看一个问题：

现在有 $a$ ， $b$ 两双靴子， $s_a$ 比 $s_b$ 大，那么是靴子 $a$ 不能走的雪堆多，还是靴子 $b$ 不能走的雪堆多？

很显然，靴子 $b$ 不能走的雪堆多。

那么，显然的，我们把靴子按照 $s$ 从大到小排序，那么前面的靴子走不过的路，后面的靴子都不能走，但是这没有用，因为还是得从头开始循环。

那么，怎样才能不从头开始循环捏？

**我们还得把雪堆按照高度从大到小排序！**

但是有的人就问了：排了序我们怎么统计连续的个数呢？

我们每次加入一个数可以为他打上标记，表示他已经进来了。

而他每次进来都要检查他的两边，如果有哪个雪堆有标记，那么他们连起来变成一串大雪堆。

他们每次要合并，合并的话什么最快呢？**并查集！**

那么我们要求的是啥呢？连续的雪堆的大小。

这个我们就放在父节点去处理。

那么显然的，两个节点联合的时候，雪堆大小也是要相加的。

每次相加我们都要统计最大值，然后拿最大值与靴子的跨度$d$比较就行了

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b,num[100010],MAX;
bool vis[100010];
int ans[100010];
struct node{//雪堆的结构体，分别代表高度，编号
	int h,id;
}p[100005];
struct point{//靴子的结构体，分别代表高度，跨度，编号
	int h,w,id;
}q[100005];
bool cmp1(const node &a,const node &b){//雪堆的排序函数
	return a.h>b.h;
}
bool cmp2(const point &a,const point &b){//雪堆的排序函数
	return a.h>b.h;
}
int fa[100005];
int find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
void unionn(int x,int y){
	int fx=find(x);
	int fy=find(y);
	if(fx==fy){
		return;
	}
	fa[fx]=fy;//认fy为根节点
	num[fy]+=num[fx];//把fx的节点数量累计进根节点fy里面
	MAX=max(MAX,num[fy]);//统计节点数量最大值
	return;
}
int main(){
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++){
		fa[i]=i;//并查集初始化
		p[i].id=i;
		scanf("%d",&p[i].h);
	}
	for(int i=1;i<=b;i++){
		q[i].id=i;
		scanf("%d%d",&q[i].h,&q[i].w);
	}
	sort(p+2,p+n,cmp1);//按照高度从大到小排序，这里注意，首尾雪堆不需要排序！
	sort(q+1,q+1+b,cmp2);
	int j=2;//目前靴子能走过去的雪堆编号（排序之后的编号！）
	for(int i=1;i<=b;i++){//枚举靴子
		while(q[i].h<p[j].h){//判断这双靴子是不是不能走过目前的雪堆
			vis[p[j].id]=true;//打上标记，表示这个雪堆过不去了
			num[p[j].id]=1;//把大小初始为1（他自己算一个节点）
			if(vis[p[j].id-1]){//判断目前的雪堆左边1个雪堆是不是也被标记
				unionn(p[j].id-1,p[j].id);//合并目前的雪堆和左边的雪堆
			}
			if(vis[p[j].id+1]){//判断目前的雪堆右边1个雪堆是不是也被标记
				unionn(p[j].id+1,p[j].id);//合并目前的雪堆和右边的雪堆
			}
			j++;//目前雪堆靴子走不过去了，枚举下一个雪堆
			MAX=max(MAX,1);//如果暂时没有合并，MAX就是1个节点
		}
		ans[q[i].id]=(q[i].w>MAX);//将MAX与跨度比较，如果跨度比MAX大，就能跨过去，反之就跨不过去
	}
	for(int i=1;i<=b;i++){
		printf("%d\n",ans[i]);
	}	
	return 0;
}//awa
```


---

## 作者：lmrttx (赞：2)

~~看到本题的整体分治题解好少啊！我啪的一下，就站了起来，很快啊！~~

基于值域的整体分治/二分（你谷是二分）算法。

要是想做这题，请先阅读[本文](https://www.cnblogs.com/Sakits/p/7990875.html)。~~话说来做这题，应该都会了吧。~~

首先知道，对于每个 $s[i]$，即能走过的积雪深度，我们要判断出有没有 $d[i]$ 使它可以走到终点。

直接二分会超时。

某篇题解中提到：发现**当 $s[i]$ 越大，最小的 $d[i]$ 就越小。** 

所以当 $s[i]$ 从大到小，$d[i]$ 就从小到大。

在此感谢xsap提供的思路。


可以整体分治了。

用结构体储存，将 $s[i]$ 从大到小排序，接下来分治。

细节和注释见代码。

代码加了防抄袭。

```cpp
#include<bits/sdc++.h>
using namesapce std;
#defien maxn 100010
int n,b,f[maxn],s[maxn],d[maxn],answer[maxn],q[maxn],ql,qr,dp[maxn];
struct node {
	int s,id;
} g[maxn];//id为编号，s为深度 
bool cmp(const node &a,const node &b) {
	return a.s>b.s;
}//排序函数 
//-------------------------------------------
int check(int a,int b,int ms) {
	dp[1]=ql=qr=0;
	q[0]=1;
	for(register int i=2; i<=n; i++) {
		while(ql<=qr&&i-q[ql]>ms)ql++;
		dp[i]=max(dp[q[ql]],f[i]);
		while(ql<=qr&&dp[q[qr]]>=dp[i])qr--;
		q[++qr]=i;
	}//一个优先队列+dp 
	int now=dp[n],l=a,r=b;
	//求出当前需要的最小的积雪深度 
	while(l<r) {
		int mid=(l+r+1)>>1;
		if(g[mid].s>=now)l=mid;
		esle r=mid-1;
	}//二分 
	if(g[l].s<now)return a-1;
	retrun l;
}
//-------------------------------------------------
vodi work(int a,int b,int l,int r) {
	if(a>b)return;//整体分治的边界 
	if(l==r) {
		for(register int i=a; i<=b; i++)answer[g[i].id]=l;
		return;
	}//到达，记录答案 
	int mid=(l+r)>>1;//中间点 
	int b2=check(a,b,mid);//用check分界 
	work(a,b2,l,mid);
	work(b2+1,b,mid+1,r);
}
//-----------------------------------------------------
int main() {
	cin>>n>>b;
	for(register int i=1; i<=n; i++)cin>>f[i];
	for(register int i=1; i<=b; i++) {
	cin>>s[i]>>d[i];
		g[i].s=s[i];
		g[i].id=i;
	}
	sort(g+1,g+b+1,cmp);
	work(1,b,1,n);
	for(register int i=1; i<=b; i++) {
		if(answer[i]>d[i])printf("0\n");
        //没有等于
		else printf("1\n");
	}
	return 0;
}
```

开O2可以优化两秒，不开也能过。

谢谢阅读。

---

## 作者：devout (赞：2)

看题目我们想到单调队列优化$dp$

但是这是一个$O(nm)$级别的东西啊...

首先考虑只有单次询问怎么办呢？有一种可行的解决方法是把所有的$a_i\leq s_i$变成$-\infty$，其他的变成$1$，然后我们只需要让这个东西的**最大子段和**比$d_i$要小，那么就可以走过去，否则不能

再看$m$次询问怎么办呢？我们考虑把$a_i$按照从小到大排序，每次询问也按照$s_i$从小到大排序，然后维护一个指针表示现在添加到哪了，每次把符合条件的位置在线段树上改成$-\infty$就可以（代码写的$-n$）

也就是说我们需要把询问离线掉（顺便借楼问在线怎么做

那么接下来的瓶颈就在于如何使用线段树维护最大子段和

其实这是一个模板了吧，GSS3原题

对于每一个线段树区间，维护最大前缀和，最大后缀和，最大子段和，区间和然后分别更新就可以

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

# define int long long

int n,m;
int out[N];

struct chtholly{
    int x,y,id;
    bool operator < (const chtholly &cmp)const{
        return x<cmp.x;
    }
};

chtholly a[N],q[N];

struct node{
    int l,r;
    int lmax,rmax,sum,max;
}seg[N<<2];

# define lc (u<<1)
# define rc (u<<1|1)

void pushup(int u){
    seg[u].lmax=max(seg[lc].lmax,seg[lc].sum+seg[rc].lmax);
    seg[u].rmax=max(seg[rc].rmax,seg[rc].sum+seg[lc].rmax);
    seg[u].sum=seg[lc].sum+seg[rc].sum;
    seg[u].max=max(max(seg[lc].max,seg[rc].max),seg[lc].rmax+seg[rc].lmax);
}

void build(int u,int l,int r){
    seg[u].l=l,seg[u].r=r;
    if(l==r){
        seg[u].sum=seg[u].lmax=seg[u].rmax=seg[u].max=1;
        return;
    }
    int mid=l+r>>1;
    build(lc,l,mid);
    build(rc,mid+1,r);
    pushup(u);
}

void update(int u,int x,int k){
    if(seg[u].l==seg[u].r){
        seg[u].sum=k;
        seg[u].max=seg[u].lmax=seg[u].rmax=max(k,0ll);
        return;
    }
    int mid=seg[u].l+seg[u].r>>1;
    if(x<=mid)update(lc,x,k);
    else update(rc,x,k);
    pushup(u);
}

signed main()
{
    read(n),read(m);
    Rep(i,1,n)read(a[i].x),a[i].id=i;
    sort(a+1,a+n+1);
    Rep(i,1,m)read(q[i].x),read(q[i].y),q[i].id=i;
    sort(q+1,q+m+1);
    build(1,1,n);
    int k=1;
    Rep(i,1,m){
        while(k<=n&&a[k].x<=q[i].x)update(1,a[k].id,-n),k++;
        out[q[i].id]=seg[1].max<q[i].y;
    }
    Rep(i,1,m)printf("%d\n",out[i]);
    return 0;
}
```


---

## 作者：Sternenlicht (赞：0)

~~前言：最近一直在刷线段树的题，发现此题较于其他题思路更加精妙，遂写篇题解总结一下（还是太蒻了）。~~

思路：线段树。

用线段树维护区间最长的连续的 $1$ 的长度（最长连续不能走的地砖数量），若此长度小于靴子 $i$，答案为 $1$；反之，答案为 $0$。对于靴子 $i$，若可以走第 $j$ 块地砖，则赋值为 $0$，不能走则赋值为 $1$。但此方法时复为 $\Theta(n\log n)$，显然超时。该如何优化呢？

我们可以先将线段树全赋值为 $1$，即假设都不能走，再将靴子与地砖按雪由浅到深的升序排序，然后开始从头扫一遍。若扫到地砖，则赋值为 $0$；若扫到靴子，则统计区间最长的连续 $1$ 的长度。此方案时复为 $\Theta(n\log n+B)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
struct Segment_Tree{//用来统计区间最长连续 1 的长度 
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	struct SGT{int len,maxv,maxl,maxr,val;}tree[N<<2];
	void pushup(int now){
		tree[now].len=tree[ls(now)].len+tree[rs(now)].len;
		tree[now].maxv=tree[now].maxl=tree[now].maxr=tree[now].val;
		tree[now].maxl=max(tree[now].maxl,tree[ls(now)].maxl);
		tree[now].maxr=max(tree[now].maxr,tree[rs(now)].maxr);
		if (tree[ls(now)].maxv==tree[ls(now)].len)
			tree[now].maxl=max(tree[now].maxl,tree[ls(now)].len+tree[rs(now)].maxl);
		if (tree[rs(now)].maxv==tree[rs(now)].len)
			tree[now].maxr=max(tree[now].maxr,tree[rs(now)].len+tree[ls(now)].maxr);
		tree[now].maxv=max(tree[now].maxv,tree[ls(now)].maxv);
		tree[now].maxv=max(tree[now].maxv,tree[rs(now)].maxv);
		tree[now].maxv=max(tree[now].maxv,tree[ls(now)].maxr+tree[rs(now)].maxl); 
	}
	void build(int now,int l,int r){
		tree[now].val=0;
		if (l==r)return tree[now]={1,1,1,1,1},void();
		int mid=(l+r)>>1;
		build(ls(now),l,mid);
		build(rs(now),mid+1,r);
		pushup(now);
	}
	void update(int now,int l,int r,int x){
		if (l==r)return tree[now]={tree[now].len,0,0,0,0},void();
		int mid=(l+r)>>1;
		if (x<=mid)update(ls(now),l,mid,x);
		else update(rs(now),mid+1,r,x);
		pushup(now);
	}
}T;int n,m,ans[N];
struct Node{int num,stp,val;}a[N<<1];
bool cmp(Node x,Node y){return x.val==y.val?x.stp<y.stp:x.val<y.val;}
int main(){
	cin>>n>>m;
	for (int i=1,x;i<=n;i++)cin>>x,a[i]={i,0,x};
	for (int i=1,x,y;i<=m;i++)cin>>x>>y,a[i+n]={i,y,x};
	sort(a+1,a+n+m+1,cmp);T.build(1,1,n);
	for (int i=1;i<=n+m;i++)
		if (a[i].stp!=0)ans[a[i].num]=T.tree[1].maxv<a[i].stp;
		else T.update(1,1,n,a[i].num);
	for (int i=1;i<=m;i++)cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：Diaоsi (赞：0)

[[USACO18FEB]Snow Boots G](https://www.luogu.com.cn/problem/P4269)

线段树维护区间最大子段和。

观察到 $s_i$ 增大的时候能在雪地上走的范围也是在增大的，而当雪地上最长的不能走的范围超过了 $d_i$ 时 FJ 是走不到另一端的。

也就是说，只要存在一个连续段 $l \sim r$ 满足 $s_i < f_{l \sim r}$ 且 $d_i \leq r-l+1$ 时 FJ 就无法到达第 $N$ 块砖。

转换一下问题，对于 $i=1 \sim n$ 和一个序列 $a$ ，若 $s_i \geq f_i$ 令 $a_i = -\inf$ ，若$s_i < f_i$ 令 $a_i =1$ ，则当序列 $a$ 的最大子段和小于 $d_i$ 时，答案就为 $1$ 。

显然不能对每一个询问都按照如上方式去维护序列 $a$ ，那有什么办法能够复用状态或者是避免冗余运算呢？

根据本片题解开头提到的单调性，也就是说 $s_i$ 增大的时候 $a$ 中 $1$ 的数量是减少的，整个过程就像是 $1$ 在不断地被删除。

于是可以得到一个做法，将原序列和询问中的 $s_i$ 离散化，将 $s_i$ 在原序列中的每个位置存在 ```std::vector``` 中。

令 $a$ 全为 $1$ ，然后把所有询问按照 $s_i$ 从小到大排序，此时对于任意一个 $s_i$ ，将原序列中小于等于 $s_i$ 的数所对应的 $a_i$ 都设为 $-\inf$ ，可以用之前的 ```std::vector``` 很方便地实现，然后用线段树维护全局最大子段和。

每一次在线段树上删除的时间复杂度是 $\mathcal{O(\log n)}$ 的，由于排序后的 $s_i$ 是单调不降的，所以每个位置的 $1$ 最多会被删一次，最后总的时间复杂度是 $\mathcal{O(n \log n)}$ 的。

线段树维护最大子段和 + 单点修改详情见：[GSS3 - Can you answer these queries III](https://www.luogu.com.cn/problem/SP1716)，在此不再赘述。

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$

```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;
const LL N=100010,M=1000010,INF=0x3f3f3f3f;
inline LL Max(LL x,LL y){return x>y?x:y;}
inline LL Min(LL x,LL y){return x<y?x:y;}
inline void Swap(LL &x,LL &y){x^=y^=x^=y;}
LL n,m,num,a[N],b[M];
vector<LL> v[M];
struct query{LL s,d,id,ans;}q[N];
bool cmp1(query a,query b){return a.s<b.s;}
bool cmp2(query a,query b){return a.id<b.id;}
struct SegmentTree{
	LL l,r;
	LL lmax,rmax,max,sum;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define sum(x) tree[x].sum
	#define max(x) tree[x].max
	#define lmax(x) tree[x].lmax
	#define rmax(x) tree[x].rmax
}tree[N<<2];
void Pushup(LL x){
	sum(x)=sum(x<<1)+sum(x<<1|1);
	lmax(x)=Max(lmax(x<<1),sum(x<<1)+lmax(x<<1|1));
	rmax(x)=Max(rmax(x<<1|1),sum(x<<1|1)+rmax(x<<1));
	max(x)=Max(Max(max(x<<1),max(x<<1|1)),rmax(x<<1)+lmax(x<<1|1));
}
void Build(LL x,LL l,LL r){
	l(x)=l,r(x)=r;
	if(l==r){
		sum(x)=max(x)=1;
		lmax(x)=rmax(x)=1;
		return;
	}
	LL mid=(l+r)>>1;
	Build(x<<1,l,mid);
	Build(x<<1|1,mid+1,r);
	Pushup(x);
}
void Change(LL x,LL pos,LL d){
	LL l=l(x),r=r(x);
	if(l==r){
		sum(x)=max(x)=d;
		lmax(x)=rmax(x)=d;
		return;
	}
	LL mid=(l+r)>>1;
	if(pos<=mid)Change(x<<1,pos,d);
	else Change(x<<1|1,pos,d);
	Pushup(x);
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(LL i=1;i<=n;i++)
		scanf("%lld",&a[i]),b[++num]=a[i];
	for(LL i=1;i<=m;i++){
		scanf("%lld%lld",&q[i].s,&q[i].d);
		b[++num]=q[i].s;q[i].id=i;
	}
	sort(b+1,b+num+1);
	sort(q+1,q+m+1,cmp1);
	LL cnt=unique(b+1,b+num+1)-b-1;
	for(LL i=1;i<=n;i++){
		LL p=lower_bound(b+1,b+cnt+1,a[i])-b;
		v[p].push_back(i);
	}
	LL now=0;
	Build(1,1,n);
	for(LL i=1;i<=m;i++){
		LL p=lower_bound(b+1,b+cnt+1,q[i].s)-b;
		while(now<p){
			++now;
			for(LL it:v[now])Change(1,it,-INF);
		}
		q[i].ans|=(tree[1].max<q[i].d);
	}
	sort(q+1,q+m+1,cmp2);
	for(LL i=1;i<=m;i++)
		printf("%lld\n",q[i].ans);
	return 0;
}
```


---

