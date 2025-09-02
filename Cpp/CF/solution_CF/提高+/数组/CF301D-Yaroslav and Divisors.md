# Yaroslav and Divisors

## 题目描述

给定一个 $1\sim n$ 的排列 $p$。有 $m$ 个询问，每个询问给定 $l,r$，询问有多少对 $i,j(l\leq i,j\leq r)$ 使得 $p_i$ 是 $p_j$ 的倍数。

## 样例 #1

### 输入

```
1 1
1
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 9
1 2 3 4 5 6 7 8 9 10
1 10
2 9
3 8
4 7
5 6
2 2
9 10
5 10
4 10
```

### 输出

```
27
14
8
4
2
1
2
7
9
```

# 题解

## 作者：龙水流深 (赞：23)

## 前言

这道题大体的思路是离线树状数组+单指针，但本体重点是思维。最重要的是知道**我们要求什么，怎么求**。知道这两个东西，这道题就解出了一半。

## 思路

我们可以把 $p_i$ 与其倍数看作点对，要求的值看作满足 $p_j=p_i\times k(l\le i,j\le r,k\in N^*)$ 的数量

**这题的本质是求 $p_i,p_j(i,j\in[l,r])$ 之间的点对数**。

但这个东西不好求，考虑转化一下。

边有如下几种种情况：

1. $i\in [1,l)$ 对答案无影响。

2. $i\in [l,r]$ 在 $j\in [l,r]$ 时对答案有影响，在 $j\in [1,l)$ 时对答案无影响。

3. $i\in (r,n]$ 对答案无影响。



其中，第三种情况对答案的影响可以这样去除：

1. 预处理每个数的倍数，并记录较前的点出现的位置。

2. 考虑把询问按右端点从小到大排序，把询问离线下来，并用单指针 $i$ 枚举 $1$~$n$，每次统计加入 $p_i$ 产生的贡献，在区间右端点等于 $i$ 时记录答案。

这样，我们就得到了第一、二两种情况的答案。由连边方式得，第一种要消去的点对满足 $j\in [1,l)$。而第二种要消去的点对也满足 $j\in [1,l)$。

**综上，考虑消去 $j\in [1,l)$ 的点对对答案影响。**

由于存图时保存了 $j$，所以就把 $j$ 扔进树状数组，维护区间和（前缀和），然后把一、二两种情况的答案减去 $j\in [1,l)$ 的答案，就是最终答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/3na0eu4c.png)

**注：本图中的“有向边”的“起点”为枚举的指针 $i$，“终点”为点对的另一端 $j$，画成边仅是代表这是有序点对，不是图论中的边，这题与边没有关系！**

如果不理解试着看图，并手玩代码，加深理解。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<=b;i++)

char buf[4300005],*p1=buf;
#define gc() *p1++
inline void read(int &x)
{
	char ch=gc();
	while(!isdigit(ch)) ch=gc();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=gc();
}
const int N=200005;

struct Query{
	int l,r;
	int* ans;
	bool operator < (Query p) const {return r<p.r;}
}q[N];
vector<int>ver[N];
int n,m,tre[N],id[N],a[N],ans[N],sum;
//sum：第一、二种边的总和
//tre：树状数组，记录不合法的情况
void add(int x) {for(;x<=n;x+= x&-x) tre[x]++;}
int query(int x)
{
	int res=0;
	for(;x;x-= x&-x) res+=tre[x];
	return res;
}
int main()
{
	fread(buf,1,4300000,stdin);
	ios::sync_with_stdio(0);
	cout.tie(nullptr);
	
	read(n); read(m);
	rep(i,1,n)
	{
		read(a[i]);
		id[a[i]]=i;
	}
	rep(i,1,n)
		for(int j=a[i];j<=n;j+=a[i])
			if(i>id[j]) ver[i].push_back(id[j]);
			else ver[id[j]].push_back(i);//从后往前连边

	rep(i,1,m)
	{
		read(q[i].l),read(q[i].r);
		q[i].ans=&ans[i];
	}
	sort(q+1,q+m+1);
	int p=1;
	rep(i,1,m)
	{
		for(;p<=q[i].r;p++)
			for(int j:ver[p])
				add(j),sum++;
		*q[i].ans=sum-query(q[i].l-1);
	}
	rep(i,1,m) cout<<ans[i]<<'\n';
	return 0;
}
```
## 后记

一个下午就写了这么一篇题解。这也是我写的最认真的。看在我这么努力的份上，能不能给我一个赞qwq？

---

## 作者：Limit (赞：6)

# 题目大意

给出一个**排列**,每次询问一个区间中满足一个数为另一个数倍数的数对个数.

# 分析

首先可以发现整个排列的合法数对数为 $\mathcal{O}(n\log n)$ 级别,所以可以想到直接去维护这些数对.一个数对由两个数组成,这就不容易处理,可以想到离线去处理.对查询的右端点排序.显然可以在右端点移动时将新加入的数的贡献加入.那么现在就变成了一个后缀查询的形式,既然是后缀,不妨将一个数对的贡献放在靠前的数中,这样在查询中只有当两个数都在这个后缀中的时候才会产生贡献.于是问题变成了单点加,区间查询,可以用树状数组轻松维护.

时间复杂度 $\mathcal{O}(n\log^2n)$.如果您有低于这个复杂度的做法可以私信我/kel.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(register int i=(first);i<=(last);++i)
#define DOW(i,first,last) for(register int i=(first);(last)<=i;--i)
#define LL long long
#define UI unsigned int
#define ULL unsigned long long
#define PII pair<int,int>
#define PIL pair<int,long long>
#define PLI pair<long long,int>
#define PLL pair<long long,long long>
#define MPR(a,b) make_pair(a,b)
namespace IO
//快读模板
using namespace IO;
using namespace std;
const int MAXN=2e5+5;
int n,m;
int arr[MAXN];
int id[MAXN];
vector<int>link[MAXN];
class Query
{
public:
	int left,right,id;
	inline bool operator <(const Query &a)const
	{
		return right<a.right;
	}
}q[MAXN];
int answer[MAXN];
namespace BIT//单点修改+区间查询的树状数组
{
	int tree[MAXN];
	inline int Lowbit(const int now)
	{
		return now&-now;
	}
	inline void Updata(const int place)
	{
		for(register int now=place;now<=n;now+=Lowbit(now))
		{
			++tree[now];
		}
	}
	inline int Query(const int left,const int right)
	{
		register int result=0;
		for(register int now=right;now;now-=Lowbit(now))
		{
			result+=tree[now];
		}
		for(register int now=left-1;now;now-=Lowbit(now))
		{
			result-=tree[now];
		}
		return result+right-left+1;
	}
}
int main()
{
	Read(n,m);
	REP(i,1,n)
	{
		Read(arr[i]);
		id[arr[i]]=i;
	}
	REP(i,1,n)//将数对的贡献放在靠前的数中
	{
		int top=n/arr[i];
		REP(j,2,top)
		{
			if(id[arr[i]*j]<i)
			{
				link[i].push_back(id[arr[i]*j]);
			}
			else
			{
				link[id[arr[i]*j]].push_back(i);
			}
		}
	}
	REP(i,1,m)
	{
		Read(q[i].left,q[i].right);
		q[i].id=i;
	}
	sort(q+1,q+1+m);
	int now=1;
	REP(i,1,n)
	{
		if(link[i].size())
		{
			REP(j,0,link[i].size()-1)//将新加入的数的贡献放入
			{
				BIT::Updata(link[i][j]);
			}
		}
		while(q[now].right==i)
		{
			answer[q[now].id]=BIT::Query(q[now].left,q[now].right);
			++now;
		}
	}
	REP(i,1,m)
	{
		Writeln(answer[i]);
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：4)

[CF301D Yaroslav and Divisors](https://www.luogu.com.cn/problem/CF301D)

本题解参考于[这位大佬](https://www.luogu.com.cn/blog/hugocaicai/solution-cf301d)的题解，由于觉得有些地方没有说的太明白，将这些地方详细说了一下。

**题意：**

找出 $[l,r]$ 中满足 $a_i$ 与 $a_j$ 是倍数关系的 $(i,j)$ 对数。

小细节：由于每个数互不相同并都不超过 $n$，因此一定是 $1\dots n$ 的一种排列，无需考虑重复。

**思路：**

一、记录每个数**后面**和他能组成倍数关系的数。

枚举 $1\dots n$，暴力算出 $a_i$ 的所有倍数，并开桶判断是否有这个数。

```cpp
if(id[j]!=0) g[min(i,id[j])].push_back(max(i,id[j]));
```

这句很绕，需要仔细想想。每次都是给编号小的数添加编号比他大的数，所以 $g$ 实际上记录的是对于数 $x$，它的**后面**和他能组成倍数关系的数的编号。这样做来防止重复计算。

二、计算答案。

因为我们是记录了每一个数后面和他能组成倍数关系的数的编号，所以我们需要将询问以 $l$ 从大到小逆序处理，才能让 $\operatorname{add}$ 时不重复计算，并且最后的循环也要逆序。

```cpp
for(int j=0;j<g[i].size();++j) add(g[i][j],1);
```

首先将第 $i$ 个数后的所有和他能组成倍数关系的数计入树状数组。这样树状数组就可以记录 $[i,n]$ 的满足关系的 $(i,j)$ 对数。

```cpp
while(q[p].l==i) ans[q[p].id]=sum(q[p].r),p++;
```

对于每一个 $l=i$ 的询问，我们可以直接调用 $\operatorname{sum}(r)$ 回答，去掉 $[r+1,n]$ 的部分，因为在上一步的操作中，我们计入树状数组的是 $i\dots n$ **后面**和他能组成倍数关系的数，因此 $i$ 前的树状数组查询时是没有任何值的，可以放心用。

**代码：**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,m,id[N],a[N];
ll ans[N],t[N];
int lowbit(int x){return x&-x;}
void add(int x,int k){for(int i=x;i<=n;i+=lowbit(i)) t[i]+=k;}
ll sum(int x){ll res=0;for(int i=x;i;i-=lowbit(i)) res+=t[i];return res;}
struct node{
	int l,r,id;
}q[N];
bool cmp(node a,node b){
	return a.l>b.l;
}
vector<int> g[N]; 
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),id[a[i]]=i;
	for(int i=1;i<=m;++i){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	for(int i=1;i<=n;++i){
		for(int j=a[i];j<=n;j+=a[i]){
			if(id[j]!=0) g[min(i,id[j])].push_back(max(i,id[j]));
		}
	}
	sort(q+1,q+m+1,cmp);
	int p=1;
	for(int i=n;i>=1;--i){
		for(int j=0;j<g[i].size();++j) add(g[i][j],1);
		while(q[p].l==i) ans[q[p].id]=sum(q[p].r),p++;
	}
	for(int i=1;i<=m;++i) printf("%lld\n",ans[i]);
	return 0;
} 
```

有任何问题欢迎提出。


---

## 作者：chlchl (赞：3)

## 题意简化
给定一个 $1\sim n$ 的排列 $a$，每次给定 $\lbrack l,r\rbrack$，问该区间内有多少个数对 $(x,y)$，使得 $a_x$ 是 $a_y$ 的正整数倍（下文简称倍数数对）。

## 做法
~~通过看标签~~容易知道，这是一道树状数组的题。这确实是一道好题，思维难度不小，大家可以看完前半部分的思路后试着自己打打代码。

首先，这个东西我们肯定是无法直接用树状数组维护的。但是，一个数的因数个数是 $\log n$ 级别的，所以整个序列的答案不会超过 $n\log n$。也就是说，我们可以考虑把**所有倍数数对**存下来。


存下来之后如何求答案呢？这里给出一种与其他题解有点类似但不完全相同的思路。

以某个询问 $\lbrack l,r\rbrack$ 为例。我们的答案其实是 $\lbrack 1,r\rbrack$ 这个区间的答案，减去 $\lbrack 1,l-1\rbrack$ 的答案，再减去所有左端点在 $\lbrack 1,l-1\rbrack$，右端点在 $\lbrack l,r\rbrack$ 的倍数数对。

注意到上面出现了一些前缀答案，使用树状数组维护前缀答案。现在最关键的问题是，左端点在 $\lbrack 1,l-1\rbrack$ 时答案是多余的，不可以计算。

所以，我们需要倒序枚举 $n$ 个数，从大到小地插入每个数的倍数，再把询问离线，按左端点从大到小在插入数的过程中求答案。

这样有什么好处呢？当前插入的数 $i$ 不会小于待求答案的左端点（这个是可以控制的）。这样，我们直接查询 $\lbrack 1,r\rbrack$，因为 $a_1\sim a_{i-1}$ 及其倍数都还没被插入，自然答案也不含它们，查出来的直接就是最终答案。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5 + 10;
int n, m, a[N], id[N];
ll ans[N], sum[N];
struct query{
	int l, r, id;
	bool operator < (const query &p) const {return l > p.l;}//左端点从大到小 
} q[N];
vector<int> g[N];

void update(int i, int x){for(;i<=n;i+=i&-i)	sum[i] += x;}

ll query(int i){
	ll res = 0;
	for(;i;i-=i&-i)	res += sum[i];
	return res;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++)	scanf("%d", &a[i]), id[a[i]] = i;
	for(int i=1;i<=m;i++)	scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	for(int i=1;i<=n;i++){
		for(int j=a[i];j<=n;j+=a[i]){
			g[min(i, id[j])].push_back(max(i, id[j]));
			//在编号小的插入编号大的，这样可以保证后面插入的数编号不会小于 i 
		}
	}
	sort(q + 1, q + 1 + m);
	int p = 1;
	for(int i=n;i;i--){
		for(int v: g[i])	update(v, 1);//将这个数及其倍数插入 
		while(q[p].l == i)	ans[q[p].id] = query(q[p].r), p++;//查询答案 
	}
	for(int i=1;i<=m;i++)	printf("%lld\n", ans[i]);
	return 0;
} 
```


---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF301D)
## 思路
套路题，可以想到除了 $1$ 以外，其它数在 $n$ 以内倍数最多只有 $\log n$ 个，而 $1$ 在区间 $l$ 至 $r$ 中有 $r-l+1$ 个倍数，所以对于 $1$ 的情况直接一个前缀和搞掉即可。

对于另外的数，记录下是这些数倍数的数，然后记录下点对 ${i,j}$ 表示标号为 $i$ 的数是标号为 $j$ 的数的倍数，然后把询问离线，按照右端点大小排序，每次在左端点处 $\verb!update!$ 一个 $1$ 即可。

时间复杂度大约 $O(n \log^2 n)$，实际远远跑不满。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=2e5+10;
int p[N],sum[N],n,ans[N];
vector<int>vis[N];
vector< pair<int,int> >d;
struct Tree_Array{
	int c[N];
	inline int lowbit(int x){return x&-x;}
	inline void update(int x,int v){while (x<=n) c[x]+=v,x+=lowbit(x);}
	inline int query(int x){int res=0;while (x) res+=c[x],x-=lowbit(x);return res;}
}T;//树状数组板子
struct node{int l,r,id;}a[N];
inline bool cmp(node x,node y){return x.r<y.r;}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int m;cin>>n>>m;
    for (int i=1;i<=n;++i) cin>>p[i],sum[i]=sum[i-1]+(p[i]==1),vis[p[i]].push_back(i);
	for (int i=1;i<=n;++i){
		if (p[i]==1) continue;//是 1 就跳过，不然会被全是 1 的数据卡成 n 方
		for (int j=1;j*p[i]<=n;++j)
		    for (auto v:vis[j*p[i]])
		        d.push_back({max(i,v),min(i,v)});
	}
	sort(d.begin(),d.end());
	for (int i=1;i<=m;++i) cin>>a[i].l>>a[i].r,a[i].id=i;
    sort(a+1,a+m+1,cmp);
    int tail=-1;
    for (int i=1;i<=m;++i){
    	while (tail+1<d.size() && d[tail+1].first<=a[i].r) ++tail,T.update(d[tail].second,1);
		ans[a[i].id]=(tail+1-T.query(a[i].l-1))+(sum[a[i].r]-sum[a[i].l-1])*(a[i].r-a[i].l+1);//区间内不为 1 的数与 1 对答案的贡献之和
	}
	for (int i=1;i<=m;++i) cout<<ans[i]<<'\n';
	return 0;
}
```


---

## 作者：1234567890sjx (赞：1)

看不到是排列。鉴定为【】。

~~首先这个东西一眼莫队。~~ 因为 $a$ 是一个排列，所以若询问整个数组则答案级别是调和级数的，因此考虑离线然后直接暴力枚举每一对 $(i,j)$ 对答案的贡献（$i\mid j$ 且 $i\neq j$）。考虑找出 $i$ 所在位置 $p_i$，$j$ 所在位置 $p_j$。则令最小的同时覆盖这两个点的区间为 $[L,R]$，则对于一组询问 $l,r$ 若满足 $l\le L\le R\le r$ 则 $(i,j)$ 对询问 $l,r$ 做了 $1$ 的贡献。

然后考虑离线应付询问。套路的按照右端点从小到大排序。然后使用一个可以兹磁单点修改和区间询问的 ds 搞一下就可以了。时间复杂度是 $O(n\log^2n)$ 的。

---

## 作者：Erica_N_Contina (赞：1)

## 思路

本题中对于数字 $i,j$ 有两个约束关系，即 $l≤i,j≤r$ 和 $\gcd(p_i,p_j)=p_i$。那么我们可以考虑使用二维偏序的做法。

但我们想想二维偏序是怎么做的——我们要求 $i≤j$，然后我们在按顺序不断加入 $j$ 的过程中计算前面的 $i$ 对当前加入的 $j$ 的影响。那么本题我们也应该有一个类似的顺序。

可是我们都询问是每次给出的 $l,r$，那 $l,r$ 也没有说说明单调性……那我们就把询问排序，采用离线的做法。

我们把询问按 $r$ 从小到大排序。每次遍历到一个询问 $l,r$，就把 $r$ 前面的加入到树状数组中（或者是加入到一个我们用来维护数据的东西中），然后更新答案。

现在我们来考虑一下 $i,j$ 的性质。我们按 $i$ 来考虑。实际上，$i,j$ 是等效的，即可以互相替换的。

- $i<l$ 没有贡献

- $l≤i≤r$ 假设满足 $\gcd(p_i,p_j)=p_i$ 的 $j$ 也是 $l≤j≤r$，那么有贡献。否则没有贡献。

- $r<i$ 没有贡献

我们先来考虑怎么样去掉情况 $3$。

我们使用一个动态数组 $e_i$ 来维护数字 $i$ 的与之有倍数关系的 $j$ 有哪些（记录 $j$ 的下标），注意我们这里不是 $i$ 一定小于 $j$，后面我们会进行说明。

然后我们对于每一个 $i$，我们都去暴力枚举其倍数。因为本题中是一个 $1\sim n$ 的全排列，所以经过计算，当 $n=200000$ 时，我们会枚举到 $2472113$ 个数。

当我们枚举到一个 $p_i$ 和 $k\times p_i(k\in \N^+,k>1)$ 时，我们就要考虑连边了（这里的连边即用动态数组标记倍数关系）。但是为了去掉情况 $3$，我们要做一点修改。 设数字 $x$ 在序列中的位置为 $loc_x$。那么如果 $loc_{p_i}>loc_{k\times p_i}$，那么我们就让 $p_i$ 连向 $k\times p_i$。我们要保证我们在枚举 $e_{p_i}$ 的元素 $x$ 时都满足 $loc_{p_i}>loc_x$，这样因为我们枚举的 $i$ 满足 $i≤r$，所以才能保证 $loc_x$ 也 $≤r$。同时，这样我们也可以确保不会重复计算。

于是我们在从小到大枚举 $i$ 时，就把 $p_i$ 的倍数丢进树状数组里，这样我们就能记录 $[1,i]$ 中满足关系的 $i,j$ 的对数。

然后对于每个 $r=i$ 的询问，我们用当前所有对数减去 $[1,l-1]$ 中满足关系的对数（我们用树状数组记录了）即可。

还有一种情况就是 $l≤i≤r $ 但是 $j≤l$，这种情况我们不会被计算到，因为还记得吗，我们在连边的时候是高位连向低位的。距离来说，我们先后查询了两个区间 $[1,p][1,q](p<q)$，那么在我们查询 $[1,p]$ 时，对于满足要求的 $i,j(i≤p,j>p)$ 是没有记录在 $[1,p]$ 中的。当我们查询 $[1,q]$ 时，假设我们实际上要询问的是区间 $[p+1,q]$，那么我们就拿 $[1,q]$ 的答案减去 $[1,p]$ 的答案，此时 $[1,p]$ 中是记录了满足要求的 $i,j(i≤p,j>p)$ 的。但是对于 $i≤p,j>q$ 的情况，因为我们的 $i$ 都没有遍历到，所以就没有被记录了。

这一段要仔细思考哦。

## 代码

注意本题卡 `cin`。

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//
#include<bits/stdc++.h>

//
#define int long long
#define uint unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<double,int>
#define pf first
#define ps second
#define pb push_back
//*/

//
using namespace std;
//
const int N=2e5+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
const int IINF=1e18;
const db eps=1e-9;
//
int n,m,p[N],b,s[N],op,idx=1,len[N],ans[N],res,tmp,loc[N],id[N];

vector<int> e[N];

struct node{
	int l,r,id;
}q[N];

bool cmp(node a,node b){
	return a.l>b.l;
}

void init(){
	for(int i=1;i<=n;i++){
		for(int j=p[i];j<=n;j+=p[i]){
			if(loc[p[j]])e[min(i,loc[j])].pb(max(i,loc[j]));
		}
	}
}

int c[N];

int lowbit(int x) {
	return x&-x;
}


void add(int i,int x) {//在位置i加上x
	while(i<=n) {
		c[i]+=x;
		i+=lowbit(i);
	}
}


int query(int x) {
	int res=0;
	while(x) {
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}

signed main(){

//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".txt","w",stderr);
	
	scanf("%lld%lld",&n,&m);

	for(int i=1;i<=n;i++)scanf("%lld",&p[i]),loc[p[i]]=i;
	for(int i=1;i<=m;i++)scanf("%lld%lld",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	
	init();
	
	for(int i=n;i;i--){
		for(auto v:e[i])add(v,1);
		while(q[idx].l==i)ans[q[idx].id]=query(q[idx].r),idx++;
	}
	
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
	return 0;
}

//check your long long and the size of memery!!!

```




---

## 作者：Crazyouth (赞：0)

## 分析

这种倍数关系一看就不能太多啊，仔细一看就是调和级数对，约为 $O(n\log n)$。我们处理出 $pos_i$ 表示 $i$ 在排列中的位置。然后枚举 $j,k$ 满足 $j |k$，这样 $pos_j,pos_k$ 就是一对倍数关系（如果 $pos_j>pos_k$ 就交换一下）。在求出某一对 $(s,t)$ 是倍数关系后它能对所有满足 $l\le s$，$t\le r$ 的询问做贡献，所以这是一个二维数点问题：我们把每个倍数关系 $(s,t)$ 看成一个点 $s,t$，因为有 $s\le t$，所以询问 $(l,r)$ 中有多少对倍数关系相当于问矩形 $x\in[l,n],y\in[1,r]$ 内有多少点，离线下来就可以了。

总复杂度 $O(n\log^2n)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int p[200010],pos[200010],ans[200010];
struct node
{
	int x,y,ans=0,id;
	bool operator<(const node &b)const
	{
		return x>b.x;
	}
}qry[200010],nd[3000010];
int t[200010],n;
void upd(int k)
{
	while(k<=n)
	{
		t[k]++;
		k+=k&-k;
	}
}
int sum(int k)
{
	int ret=0;
	while(k)
	{
		ret+=t[k];
		k-=k&-k;
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>p[i],pos[p[i]]=i;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j+=i)
		{
			nd[++cnt]={min(pos[i],pos[j]),max(pos[i],pos[j])};
		}
	}
	sort(nd+1,nd+cnt+1);
	for(int i=1;i<=q;i++) cin>>qry[i].x>>qry[i].y,qry[i].id=i;
	sort(qry+1,qry+q+1);
	int pt=1;
	for(int i=1;i<=q;i++)
	{
		while(pt<=cnt&&nd[pt].x>=qry[i].x)
		{
			upd(nd[pt].y);
			pt++;
		}
		qry[i].ans=sum(qry[i].y);
	}
	for(int i=1;i<=q;i++) ans[qry[i].id]=qry[i].ans;
	for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
}
```

---

## 作者：wusixuan (赞：0)

一看到“倍数关系”的字样，根据平日写题的直觉，以及 $n,m \le 10^5$ 的数据范围，这道题很有可能就是用调和级数进行优化的。

所以我们考虑用调和级数进行优化。由于给出的数列是一个排列，所以里面每一项都是不同而且 $\le n$ 的；就可以用调和级数预处理出来所有的倍数关系，这样会形成一个个的区间。

对于每次询问，答案显然就是包含的区间个数。所以我们可以采用离线做法，先把询问的区间加入然后排一个序，最后就是用树状数组维护区间包含的老套路。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 200010;
int a[N];
int pos[N];

struct range {
	int l, r;
	int f;
} q[6000010];
int cnt = 0;
int ans[N];

bool cmp(range a, range b) {
	if (a.r != b.r)
		return a.r < b.r;
	if (a.l != b.l)
		return a.l < b.l;
	return a.f < b.f;
}//实际上我们最主要的是维护r的次序，l和f的次序可以不管。
int tree[N];

void add(int x, int v) {
	for (; x <= n; x += x & -x)
		tree[x] += v;
}

int query(int x) {
	int ans = 0;
	for (; x; x -= x & -x)
		ans += tree[x];
	return ans;
}//树状数组

int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		s = (s * 10 + ch - '0');
		ch = getchar();
	}
	return s * w;
}//快读

int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read(), pos[a[i]] = i;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i)
			q[++cnt] = {min(pos[i], pos[j]), max(pos[j], pos[i]), 0};//预处理出来所有具有倍数关系的区间，注意左端点一定要比右端点小。
	for (int _ = 1; _ <= m; _++) {
		int l = read(), r = read();
		q[++cnt] = {l, r, _};//离线。
	}
	sort(q + 1, q + cnt + 1, cmp);
	int mq = 1;
	for (int i = 1; i <= n; i++) {
		int lmq = mq;
		while (mq <= cnt && q[mq].r == i) {
			if (q[mq].f == 0)
				add(q[mq].l, 1);//老套路。
			mq++;
		}//一定是先加入然后才处理查询的情况。
		for (int j = lmq; j <= mq; j++)
			if (q[j].f)
				ans[q[j].f] = query(q[j].r) - query(q[j].l - 1);//获得答案。
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);//这里要用printf，笔者因为写了cinTLE了。
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较套路的题。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先看到了倍数关系和排列，这种东西因为每次至少要乘 $2$，所以直接暴力做每次乘 $2$ 复杂度都只是一只 $\log$。

接着发现多次询问每次询问一个区间，好像不是很好做？

经典 trick，给询问先剥下来右端点排序（其实正常来说要左右端点拆开差分，但这题并不用）。

考虑一个单指针 $i$ 一路扫过去，碰到一个新的数就加入他的倍数的贡献。

好像不太好处理？

把一个数对的贡献都放在前面那个数里，也就是后面那个数向前面那个数连边，每次碰到一个点给他前面的数字单点加即可。

区间查询直接用树状数组维护即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,V=2e5,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    inline void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    inline int query(int x){int res=x;for(;x;x-=x&-x) res+=c[x];return res;}
}tt;
struct query{int l,r,id;}q[N<<1];
int n,m,a[N],ans[N],id[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='#'||c=='.'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline bool cmp(query x,query y){return x.r<y.r;}
signed main()
{
    tt.n=n=read(),m=read();for(int i=1;i<=n;i++) id[a[i]=read()]=i;
    for(int i=1;i<=m;i++) q[i].id=i,q[i].l=read(),q[i].r=read();
    for(int i=1;i<=n;i++)
        for(int j=2;j*a[i]<=n;j++)
            if(id[a[i]*j]<i) e[i].emplace_back(id[a[i]*j]);
            else e[id[a[i]*j]].emplace_back(i);
    sort(q+1,q+1+m,cmp);int cur=1;
    for(int i=1;i<=n;i++)
    {
        for(auto v:e[i]) tt.modify(v,1);
        while(q[cur].r==i) ans[q[cur].id]=tt.query(q[cur].r)-tt.query(q[cur].l-1),cur++;
    }
    for(int i=1;i<=m;i++) print(ans[i]),put('\n');
    genshin:;flush();return 0;
}
```

---

## 作者：Daidly (赞：0)

可以先 $O(n\log n)$ 预处理出所有满足整除关系的有序数对。

可以莫队 $O(n\sqrt{n}\log n)$ 做，太大考虑 polylog 做法。

考虑询问的本质就是查询有多少个预处理的区间被 $[l_i,r_i]$ 完全包含，类似二位偏序，用排序处理一维，用树状数组处理一维。

把询问离线，和原来预处理的区间合在一起，标好记号，按照：区间左端点，是否为询问，区间右端点，为第一二三关键字排序。

使用树状数组维护，把贡献放在右端点，我们遍历到询问区间 $[l_i,r_i]$ 时需要满足左端点小于 $l_i$ 的区间贡献消失，用树状数组查询 $r_i$ 前缀和即可。

时间复杂度 $O(n\log^2n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=2e5+5;
int n,m,p[N],pos[N],num,ans[N];
struct node{
	int l,r,id;
	bool operator<(const node &p)const{
		if(l!=p.l)return l<p.l;
		if(id!=p.id)return id>p.id;
		return r<p.r;
	}
}a[N*22];

struct BIT{
	int c[N];
	
	void add(int x,int k){
		for(int i=x;i<=n;i+=i&-i)c[i]+=k;
	}
	
	int qry(int x){
		int sum=0;
		for(int i=x;i>=1;i-=i&-i)sum+=c[i];
		return sum;
	}
}T;

int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)p[i]=read(),pos[p[i]]=i;
	for(int i=1;i<=n;++i){
		for(int j=p[i];j<=n;j+=p[i]){
			if(pos[j]<i)a[++num]=(node){pos[j],i,0};
			else a[++num]=(node){i,pos[j],0};
			T.add(a[num].r,1);
		}
	}
	for(int i=1;i<=m;++i){
		int l=read(),r=read();
		a[++num]=(node){l,r,i};
	}
	sort(a+1,a+num+1);
	for(int i=1;i<=num;++i){
		if(a[i].id)ans[a[i].id]=T.qry(a[i].r);
		else T.add(a[i].r,-1);
	}
	for(int i=1;i<=m;++i)print(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：xyf007 (赞：0)

~~一开始题意看错，问了一下 DPair 发现是[第十四分块](https://www.luogu.com.cn/problem/P5398)。实际上他是第十四分块的严格弱化版，你可以直接用第十四分块过去。~~  
因为保证了 $\{p_i\}$ 是一个排列，所以总共的答案只有 $O(n \ln n)$ 种。考虑每一对 $(i,k \times i)$ 的贡献。不放设它们在 $l_i,r_i(l_i \leq r_i)$ 两个位置上，则会对所有满足 $L_i \leq l_i,r_i \leq R_i$ 的查询 $L_i,R_i$ 产生贡献。因此将查询按照右端点排序，用树状数组维护答案即可。
```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <numeric>
#include <vector>
char Gc() {
  static char now[1 << 20], *S, *T;
  if (T == S) {
    T = (S = now) + std::fread(now, 1, 1 << 20, stdin);
    if (T == S) return EOF;
  }
  return *S++;
}
template <typename T>
void Read(T &x) {
  x = 0;
  int f = 1;
  char c;
  while ((c = Gc()) < '0' || c > '9')
    if (c == '-') f = -1;
  x = c - '0';
  while ((c = Gc()) >= '0' && c <= '9') x = x * 10 + c - '0';
  x *= f;
}
template <typename T, typename... Args>
void Read(T &x, Args &...args) {
  Read(x);
  Read(args...);
}
template <typename T>
void checkmax(T &x, T y) {
  if (x < y) x = y;
}
template <typename T>
void checkmin(T &x, T y) {
  if (x > y) x = y;
}
struct Query {
  int l, r, id;
} b[200001];
int n, m, a[200001], pos[200001], ans[200001];
std::vector<int> v[200001];
class FenwickTree {
 public:
  FenwickTree() {}
  void Add(int x) {
    while (x <= n) {
      t_[x]++;
      x += x & -x;
    }
  }
  int Query(int x) {
    int s = 0;
    while (x) {
      s += t_[x];
      x -= x & -x;
    }
    return s;
  }
  ~FenwickTree() {}

 private:
  int t_[200001];
} T;
int main(int argc, char const *argv[]) {
  Read(n, m);
  for (int i = 1; i <= n; i++) {
    Read(a[i]);
    pos[a[i]] = i;
  }
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j += i) {
      int l = pos[i], r = pos[j];
      if (l > r) std::swap(l, r);
      v[r].emplace_back(l);
    }
  for (int i = 1; i <= m; i++) {
    Read(b[i].l, b[i].r);
    b[i].id = i;
  }
  std::sort(b + 1, b + m + 1, [](const Query &lhs, const Query &rhs) -> bool {
    return lhs.r < rhs.r;
  });
  int p = 1;
  for (int i = 1; i <= m; i++) {
    while (p <= b[i].r) {
      for (auto &&j : v[p]) T.Add(j);
      p++;
    }
    ans[b[i].id] = T.Query(b[i].r) - T.Query(b[i].l - 1);
  }
  for (int i = 1; i <= m; i++) std::printf("%d\n", ans[i]);
  return 0;
}
```

---

## 作者：Nylch (赞：0)

首先记 $sum_i$ 表示 $[1,i]$ 中整除对的数量，那么每次询问的答案就是 $sum_r-sum_l-$ 左端点在 $[1,l]$，右端点在 $[l,r]$ 的整除对。那么考虑离线处理，对于每个询问 $[l,r]$，当 $l=i$，$sum_r-sum_{l-1}=$ 左端点在 $[1,l]$，右端点在 $[l,r]$ 的整除对，然后更新一下 $sum_i$。$sum_i$ 可以用树状数组或者线段树维护一下就好了。

```cpp
#include <bits/stdc++.h>
#define reg register
#define ll long long
#define ull unsigned long long
#define db double
#define pi pair<int, int>
#define pl pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vpi vector<pi>
#define vpl vector<pl>
#define pb push_back
#define er erase
#define SZ(x) (int) x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mkp make_pair
using namespace std;
char ch, B[1 << 20], *S = B, *T = B;
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 20, stdin), S == T) ? 0 : *S++)
#define isd(c) (c >= '0' && c <= '9')
int aa, bb;
int rd() {
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
const int MAXN = 2e5 + 10;
int n, m, p[MAXN], tr[MAXN], ans[MAXN], pos[MAXN];
struct Node {
  int l, r, id;
} a[MAXN], b[MAXN];
bool cmp1(Node a, Node b) {
  return a.l == b.l ? a.r < b.r : a.l < b.l;
}
bool cmp2(Node a, Node b) {
  return a.r == b.r ? a.l < b.l : a.r < b.r;
}
inline void add(int x, int c) {
  while(x <= n) {
    tr[x] += c;
    x += (x & (-x));
  }
}
int sum(int x) {
  int ret = 0;
  while(x) {
    ret += tr[x];
    x -= (x & (-x));
  }
  return ret;
}
inline void work() {
  n = rd();
  m = rd();
  for(reg int i = 1; i <= n; ++i) {
    p[i] = rd();
    pos[p[i]] = i;
  }
  for(reg int i = 1; i <= m; ++i) {
    int l = rd(), r = rd();
    a[i].l = l;
    a[i].r = r;
    a[i].id = i;
    b[i] = a[i];
  }
  sort(a + 1, a + m + 1, cmp1);
  sort(b + 1, b + m + 1, cmp2);
  int j = 1, k = 1;
  for(reg int i = 1; i <= n; ++i) {
    while(a[j].l == i && j <= m) {
      ans[a[j].id] -= sum(a[j].r) - sum(a[j].l - 1);
      ++j;
    }
    for(reg int l = 1; l * p[i] <= n; ++l)
      add(pos[l * p[i]], 1);
    while(b[k].r == i && k <= m) {
      ans[b[k].id] += sum(b[k].r) - sum(b[k].l - 1);
      ++k;
    }
  }
  for(reg int i = 1; i <= m; ++i)
    // printf("%d %d\n", ans[i], tr[i]);
    printf("%d\n", ans[i]);
}
int main() {
  // freopen("input.txt", "r", stdin);
  work();
  return 0;
}
```

---

