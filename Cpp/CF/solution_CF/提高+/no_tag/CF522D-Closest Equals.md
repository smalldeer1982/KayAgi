# Closest Equals

## 题目描述

You are given sequence $ a_{1},a_{2},...,a_{n} $ and $ m $ queries $ l_{j},r_{j} $ ( $ 1<=l_{j}<=r_{j}<=n $ ). For each query you need to print the minimum distance between such pair of elements $ a_{x} $ and $ a_{y} $ ( $ x≠y $ ), that:

- both indexes of the elements lie within range \[ $ l_{j},r_{j} $ \], that is, $ l_{j}<=x,y<=r_{j} $ ;
- the values of the elements are equal, that is $ a_{x}=a_{y} $ .

The text above understands distance as $ |x-y| $ .

## 样例 #1

### 输入

```
5 3
1 1 2 3 2
1 5
2 4
3 5
```

### 输出

```
1
-1
2
```

## 样例 #2

### 输入

```
6 5
1 2 1 3 2 3
4 6
1 3
2 5
2 4
1 6
```

### 输出

```
2
2
3
-1
2
```

# 题解

## 作者：Owen_codeisking (赞：38)

这题有黑题难度？？？~~紫题都嫌高~~

怎么都是 $RMQ$ + 二分？那么我给一篇线段树的好了

先离散一下序列，然后记录 $pre[i]$ 表示在 $1\sim i-1$ 中跟 $a[i]$ 相同最近的位置。考虑离线，把询问按右端点排序，如果 $pre[i]\not =0$ 就把 $pre[i]$ 的位置修改为 $i-pre[i]$，然后就是区间求最小值了

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=500000+10;
const int inf=0x3f3f3f3f;
int n,m,a[maxn],mp[maxn],pre[maxn],pos[maxn],sum[maxn<<2],ans[maxn];

struct Query{
	int l,id;
};
vector<Query> q[maxn];

inline int read(){
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

void pushup(int rt){
	sum[rt]=min(sum[rt<<1],sum[rt<<1|1]);
}

void modify(int x,int v,int l,int r,int rt){
	if(l == r){
		sum[rt]=v;
		return ;
	}
	int mid=(l+r)>>1;
	if(x <= mid) modify(x,v,l,mid,rt<<1);
	else modify(x,v,mid+1,r,rt<<1|1);
	pushup(rt);
}

int query(int L,int R,int l,int r,int rt){
	if(L <= l && r <= R){
		return sum[rt];
	}
	int mid=(l+r)>>1,ans=inf;
	if(L <= mid) ans=min(ans,query(L,R,l,mid,rt<<1));
	if(R > mid) ans=min(ans,query(L,R,mid+1,r,rt<<1|1));
	return ans;
}

int main()
{
	
	n=read(),m=read();
	for(int i=1;i<=n;i++) mp[i]=a[i]=read();
	sort(mp+1,mp+n+1);
	int cnt=unique(mp+1,mp+n+1)-mp-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(mp+1,mp+cnt+1,a[i])-mp;
		pre[i]=pos[a[i]];pos[a[i]]=i;
	}
	int l,r;
	for(int i=1;i<=m;i++){
		l=read(),r=read();
		q[r].push_back((Query){l,i});
	}
	memset(sum,inf,sizeof(sum));
	for(int i=1;i<=n;i++){
		if(pre[i]) modify(pre[i],i-pre[i],1,n,1);
		for(int j=0;j<q[i].size();j++)
			ans[q[i][j].id]=query(q[i][j].l,i,1,n,1);
	}
	for(int i=1;i<=m;i++) printf("%d\n",(ans[i]==inf)?-1:ans[i]);
	return 0;
}
```

---

## 作者：wsyhb (赞：17)

## 分析 + 题解

首先，设某种数值出现在 $p_1<p_2<\cdots<p_k$ 这 $k$ 个位置，则我们只需用所有满足 $1 \le i < k$ 且 $l \le p_i < p_{i+1} \le r$ 的 $i$ 的 $p_{i+1}-p_i$ 去更新答案。因此这转化成了一个**查询区间内最短线段长度**的问题。（线段左端点为 $p_i$，右端点为 $p_{i+1}$）

显然这些线段的个数不超过 $n-1$，因此我们可以对这些线段进行**排序**，**二分查找**处理掉左端点这一维，但是如何处理右端点这一维呢？

考虑**去重**，即若线段 $i$ 完全覆盖线段 $j$，我们可以将线段 $i$ 删除，因为包含线段 $i$ 的区间一定包含更短的线段 $j$。

去重后**线段的右端点一定会随着线段的左端点增大而增大**，因此我们可以对左右端点的限制分别进行二分查找，即可求得该区间所包含的线段组成的区间，使用 **ST 表**即可求区间最小值。

代码实现时，线段的生成方式可以保证右端点递增，我们只需考虑当前线段是否包含上一条线段，以此决定是否加入这条线段，即可保证有序。（即无需另外排序+去重）

时间复杂度：$O(n \log n)$（ST 表预处理带一个 $\log$）

## 代码

还有什么不清楚的就看代码吧。

``` cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> pos;//pos[i] 记录 i 最后一次出现的位置 
const int max_n=5e5+5;
int l[max_n],r[max_n];//线段的左右端点 
int Log[max_n],f[20][max_n]; 
inline void init(int n)//ST 表预处理 
{
	Log[0]=-1;
	for(int i=1;i<=n;++i)
	{
		Log[i]=Log[i>>1]+1;
		f[0][i]=r[i]-l[i];//值为线段长度 
	}
	for(int i=1;i<=Log[n];++i)
		for(int j=1;j+(1<<i)-1<=n;++j)
			f[i][j]=min(f[i-1][j],f[i-1][j+(1<<i-1)]);
}
inline int query(int l,int r)//ST 表查询区间最小值 
{
	int k=Log[r-l+1];
	return min(f[k][l],f[k][r-(1<<k)+1]);
}
int main()
{
	int n,m,cnt=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		int id=pos[x];
		if(id!=0)
		{
			if(id>l[cnt])//判断是否包含 
				l[++cnt]=id,r[cnt]=i;
		}
		pos[x]=i;
	}
	init(cnt);
	for(int i=1;i<=m;++i)
	{
		int L,R;
		scanf("%d%d",&L,&R);
		int x=lower_bound(l+1,l+cnt+1,L)-l;
		int y=upper_bound(r+1,r+cnt+1,R)-r-1;
		if(x<=y)
			printf("%d\n",query(x,y));
		else//若 x>y 则无解 
			puts("-1");
	}
	return 0;
}
```

---

## 作者：Karry5307 (赞：8)

### 题意

给定长度为 $n$ 的序列 $a$，$m$ 次询问，每次询问给定 $l,r$，在满足 $a_x=a_y,l\leq x,y\leq r$ 的前提下求 $\vert a_x-a_y\vert$ 的最小值。

$\texttt{Data Range:}1\leq n,m\leq 5\times 10^5$

### 题解

不算很难的题。

首先注意到对于某个位置来说，只有第一个在这个位置左边且值相同的位置才可能造成贡献（右边的话会在下一个位置枚举到），所以预处理一个 $prv_i$ 表示这个位置可能的贡献，也即这个位置与第一个在它左边的位置的距离。

接下来有一个非常暴力的做法：对于每个询问，取所有满足 $i-prv_i\geq l $ 位置上的 $prv_i$ 的最小值。但是这个东西在线做没法做（也有可能是我不会），于是考虑将所有询问离线下来按照左端点排序，每一次处理左端点相同的所有询问。

注意到当左端点往右移一个位置的时候，有一个位置会失效，所以把它改成 $+\infty$ 就好了，这个时候每个询问可以直接查询对应区间最小值，写个线段树即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=5e5+51,inf=0x3f3f3f3f;
struct SegmentTree{
	ll l,r,mn;
};
struct Query{
	ll l,r,id;
	inline bool operator <(const Query &rhs)const
	{
		return l<rhs.l;
	} 
};
SegmentTree tree[MAXN<<2];
Query qry[MAXN];
unordered_map<ll,ll>mp;
ll n,m,l,r;
ll x[MAXN],d[MAXN],nxt[MAXN],res[MAXN];
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
#define ls node<<1
#define rs (node<<1)|1
inline void update(ll node)
{
	tree[node].mn=min(tree[ls].mn,tree[rs].mn);
}
inline void create(ll l,ll r,ll node)
{
	tree[node]=(SegmentTree){l,r};
	if(l==r)
	{
		return (void)(tree[node].mn=d[l]);
	}
	ll mid=(l+r)>>1;
	create(l,mid,ls),create(mid+1,r,rs),update(node);
}
inline void change(ll pos,ll val,ll node)
{
	if(tree[node].l==tree[node].r)
	{
		return (void)(tree[node].mn=val);
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	change(pos,val,pos<=mid?ls:rs),update(node);
}
inline ll query(ll l,ll r,ll node)
{
	if(l<=tree[node].l&&r>=tree[node].r)
	{
		return tree[node].mn;
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	return min((l<=mid?query(l,r,ls):inf),(r>mid?query(l,r,rs):inf));
}
int main()
{
    n=read(),m=read();
    for(register int i=1;i<=n;i++)
    {
    	x[i]=read(),d[i]=mp.find(x[i])==mp.end()?inf:i-mp[x[i]];
    	mp.find(x[i])!=mp.end()?nxt[mp[x[i]]]=i:1,mp[x[i]]=i; 
	}
	create(1,n,1);
	for(register int i=1;i<=m;i++)
	{
		l=read(),r=read(),qry[i]=(Query){l,r,i};
	}
	sort(qry+1,qry+m+1),l=1;
	for(register int i=1;i<=m;i++)
	{
		while(l<qry[i].l)
		{
			change(nxt[l++],inf,1);
		}
		res[qry[i].id]=query(qry[i].l,qry[i].r,1);
	}
	for(register int i=1;i<=m;i++)
	{
		printf("%d\n",res[i]==inf?-1:res[i]);
	}
}
```

---

## 作者：LawrenceSivan (赞：7)

# CF522D Closest Equals

updated：修改了部分细节，删除了冗余描述

## 前言

这个题看着非常像回滚莫队的板子，于是高兴地敲上去发现 WA 了。

于是在题解区找啊找啊只找到了一篇，但是不太能看懂 /kk

应该是太弱了。

回滚莫队学习戳[这里](https://lawrencesivan.github.io/2021/04/22/莫队全家桶/)

## 题目概述

> 给定一个序列，每次询问一个区间，求区间中相同元素的最近距离

稍加思考可以发现，本题中的插入操作可以在 $\mathcal{O(1)}$ 复杂度内完成。

删除操作就没有那么容易。

每次删除需要找到次小，之后又要找到次次小，如果全都存下来空间是 $\mathcal{O(n^2)}$ 的。

需要另辟蹊径。

发现和板子题貌似就是相对的，那个是最大，这个是最小。

可以使用类似的手段处理。

注意到答案只可能有以下来源：

- 左半区间。

- 右半区间。

- 跨越了左右两区间，如下图：

  ![](https://i.loli.net/2021/08/27/kO31c9nYqLH7lNb.png)

分别考虑：

- 来自左半区间：随着左指针的扫描过程，我们可以使用记录 $last$ 的方法快速得出当前答案。这里的手段比较像 [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)，是一种比较常见的套路。

  具体手段是每次扫入一个位置，如果颜色还没有出现过那么就记录下来，如果出现过了说明现在出现了两种相同的颜色，于是可能会对答案产生贡献，所以与答案取 `min` 。

  之后更改 $last$ 的值。原因是要求最小的距离，所以更远的就没有用了。

- 右半区间同理。

- 问题在于跨越两个区间的情况：

  可以看出，情况只会来自于右边区间第一次出现的位置与左边区间第一次出现的位置。

  这个也是好统计的，记录下来就好了，处理左区间的时候同步处理一下。

要记得离散化！

```cpp
// #define LawrenceSivan

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define INF 0x3f3f3f3f
#define re register

const int maxn=5e5+5;

int n,m,ans;

int belong[maxn],block,tot;

int a[maxn],b[maxn]/*离散化数组*/,tmp;

namespace Mo_Captain{
	struct MOCAP{
		int l,r,id;
		inline bool operator < (const MOCAP &x)const{
			return belong[l]^belong[x.l]?belong[l]<belong[x.l]:r<x.r;
		}
	}mocap[maxn];

	inline void Discretization(){//记得离散化
		sort(b+1,b+1+n);
		tmp=unique(b+1,b+1+n)-b-1;
		for(re int i=1;i<=n;i++){
			a[i]=lower_bound(b+1,b+1+tmp,a[i])-b;
		}
	}

	int last[maxn];

	inline int calc(int l,int r){
		int res=INF,cntt[maxn];
		for(re int i=l;i<=r;i++){
			cntt[a[i]]=0;
		}
		for(re int i=l;i<=r;i++){
			if(!cntt[a[i]])cntt[a[i]]=i;
			else res=min(res,i-cntt[a[i]]),cntt[a[i]]=i;
		}
		
		return res^INF?res:-1;
	}

	int pl[maxn],pr[maxn];//伴随着扫描我们记录的 last 值，用于处理只在左区间和只在右区间的情况

	int maxl[maxn],minr[maxn];//左区间出现的最大位置和右区间出现的最小位置

	int Ans[maxn];
}

using namespace Mo_Captain;

namespace IO{
	template<typename T>
	inline void read(T &x){
		x=0;T f=1;char ch=getchar();
		while (!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
		while (isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
		x*=f;
	}

	template <typename T, typename... Args>
	inline void read(T& t, Args&... args){
		read(t); read(args...);
	}

	template<typename T>
	void write(T x){
		if(x<0)putchar('-'),x=-x;
		if(x>9)write(x/10);
		putchar(x%10+'0');
	}

	template<typename T,typename... Args>
	void write(T t,Args... args){
		write(t);putchar(' ');write(args...);
	}
}

using namespace IO;

signed main(){
#ifdef LawrenceSivan
	freopen("D1.in","r", stdin);
	freopen("aa.out","w", stdout);
#endif
	read(n,m);
	block=sqrt(n);

	for(re int i=1;i<=n;i++){
		belong[i]=(i-1)/block+1;
	}
	tot=belong[n];

	for(re int i=1;i<=n;i++){
		read(a[i]);b[i]=a[i];
	}

	Discretization();

	// for(re int i=1;i<=n;i++){cout<<a[i]<< " ";}

	for(re int i=1;i<=m;i++){
		read(mocap[i].l,mocap[i].r);
		mocap[i].id=i;
	}

	sort(mocap+1,mocap+1+m);

	//  for(int i=1;i<=m;i++){
 //    	cout<<mocap[i].l<<" "<<mocap[i].r<<" "<<mocap[i].id<<endl;
	// }

	for(re int i=1,j=1;j<=tot;j++){
		int nowr=min(n,j*block),l=nowr+1,r=nowr,ans=INF;
		memset(pl,0,sizeof(pl));memset(pr,0,sizeof(pr));//别骂了别骂了，memset不咋吃常数的（确信）
		memset(maxl,0,sizeof(maxl));memset(minr,0,sizeof(minr));
		for(;belong[mocap[i].l]==j;i++){
			if(belong[mocap[i].r]==j){//同一个块内暴力做
				Ans[mocap[i].id]=calc(mocap[i].l,mocap[i].r);
				continue;
			}

			while(r<mocap[i].r){//右区间走
				r++;
				if(!minr[a[r]])minr[a[r]]=r;//记录第一次出现的位置
				else ans=min(ans,r-pr[a[r]]);
				pr[a[r]]=r;
			}

			int tmpp=ans;

			while(l>mocap[i].l){//左区间走
				l--;
				if(!pl[a[l]]){
					if(minr[a[l]])ans=min(ans,minr[a[l]]-l);//处理跨越区间的情况
				}
				else ans=min(ans,pl[a[l]]-l);//处理左区间
				pl[a[l]]=l;
			} 

			if(ans^INF)Ans[mocap[i].id]=ans;
			else Ans[mocap[i].id]=-1;

			while(l<=nowr){//滚回来！
				pl[a[l]]=0;
				l++;
			}
			ans=tmpp;
		}
	}

	for(re int i=1;i<=m;i++){
		write(Ans[i]),puts("");
	}


	return 0;
}

```



---

## 作者：封禁用户 (赞：6)

# 终于过了，发篇题解庆祝一下
~~实际上是为了不让后人没一篇优秀的题解看~~

### 进入正题

[翻译](https://www.luogu.org/discuss/show/50529) ~~实际上是我懒得打了~~

emmmm，怎么这么多实际上QAQ？

不管啦，看题，我们将相同的数作为一个区间存下来

将两个的坐标分别作为区间的左右端点

然后我们发现

如果有一个区间包含了另一个区间，那么！！！

就可以删掉那个较大的区间，是不是很神奇！是不是！是不是！

咳咳，言归正传，那么我们们在边读边做时就会自动的将区间按左端点从小到大排序

由上可知，右端点也是有序的

在每次询问时，我们可以二分一个查找，找到可以得出答案的范围

在其中找最小的区间长度，就可以啦~~~

上面的一步可以用RMQ哦QAQ

注意：当我们找出的l和r有l>r时，就输出-1啦

丢代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[500001],d[500001],cnt;
int logg[500001];
int f[500001][40];
int l[500001],r[500001];
map <int,int> mp;//第一个是原值，第二个是原值的位置
inline int min(int a,int b)
{
	return a<b? a:b;
}
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!(ch>='0'&&ch<='9'))
    {
        if(ch=='-') w=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return w?-x:x;
}
int main(){
	n=read();
	m=read();
	for(register int i=1;i<=n;++i)
	{
		a[i]=read();
		if(mp.count(a[i]))
		{
			int j=mp.find(a[i])->second;
			mp[a[i]]=i;
			if(!cnt) l[++cnt]=j,r[cnt]=i,d[cnt]=i-j;
			else if(l[cnt]>=j) continue;
			else l[++cnt]=j,r[cnt]=i,d[cnt]=i-j;
		}
		else mp.insert(make_pair(a[i],i));
	}
	logg[0]=-1;
    for(register int i=1;i<=cnt;++i)
      f[i][0]=d[i],logg[i]=logg[i>>1]+1;
    for(register int j=1;(1<<j)<=cnt;++j)
      for(register int i=1;i+(1<<j)-1<=cnt;++i)
      	f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
    for(register int i=1;i<=m;++i)
    {
        int x,y;
        x=read();
		y=read();
        x=lower_bound(l+1,l+cnt+1,x)-l;
        y=upper_bound(r+1,r+cnt+1,y)-r-1;
		if(y<x) {cout<<-1<<endl; continue;}
        int s=logg[y-x+1];
        printf("%d\n",min(f[x][s],f[y-(1<<s)+1][s]));
    }
}
```

---

## 作者：Limit (赞：5)

# 题目大意

给出一个序列,每次查询一段区间内距离最近的相同元素之间的距离.

# 分析

RMQ+二分的做法好妙啊,我就根本想不出来.

考虑一个数对只有当两个数相等且都在区间内才可能会产生贡献.

记录一个 $pre_i$ 表示第 $i$ 个数相同的数上一次出现的位置

这个东西就很像区间取 $\min$ 了,将 $i$ 与 $pre_i$ 的贡献放在 $pre_i$ 的位置,那么这个区间查询的答案就是 $l\sim r$ 中记录的贡献的最小值了.

可是直接这样搞可能会导致 $i$ 在区间外 $pre_i$ 在区间内的情况出现,那么就考虑将查询离线下来,按右端点排序,只有当 $i\leq right$ 时才将贡献放在 $pre_i$ 上.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=5e5+5;
const int INF=1e9;
int n,m;
int arr[MAXN];
struct Sor
{
	int num,id;
}sor[MAXN];
bool Cmp(Sor a,Sor b)
{
	return a.num>b.num;
}
struct SegmentTree//一颗维护区间 min 的线段树
{
	int min;
}sgt[MAXN*4];
#define LSON (now<<1)
#define RSON (now<<1|1)
#define MIDDLE ((left+right)>>1)
#define LEFT LSON,left,MIDDLE
#define RIGHT RSON,MIDDLE+1,right
#define NOW now_left,now_right
void PushUp(int now)
{
	sgt[now].min=min(sgt[LSON].min,sgt[RSON].min);
}
void Build(int now=1,int left=1,int right=n)
{
	if(left==right)
	{
		sgt[now].min=INF;
		return;
	}
	Build(LEFT);
	Build(RIGHT);
	PushUp(now);
}
void Updata(int place,int num,int now=1,int left=1,int right=n)//单点修改
{
	if(right<place||place<left)
	{
		return;
	}
	if(left==right)
	{
		sgt[now].min=num;
		return;
	}
	Updata(place,num,LEFT);
	Updata(place,num,RIGHT);
	PushUp(now);
}
int Query(int now_left,int now_right,int now=1,int left=1,int right=n)//区间查询 min
{
	if(now_right<left||right<now_left)
	{
		return INF;
	}
	if(now_left<=left&&right<=now_right)
	{
		return sgt[now].min;
	}
	return min(Query(NOW,LEFT),Query(NOW,RIGHT));
}
#undef LSON
#undef RSON
#undef MIDDLE
#undef LEFT
#undef RIGHT
#undef NOW
int pre[MAXN];
int last[MAXN];
int answer[MAXN];
struct Range
{
	int left,right,id;
}range[MAXN];
bool Cmp2(Range a,Range b)
{
	return a.right<b.right;
}
int main()
{
	scanf("%d%d",&n,&m);
	REP(i,1,n)//离散化
	{
		scanf("%d",&sor[i].num);
		sor[i].id=i;
	}
	sort(sor+1,sor+1+n,Cmp);
	sor[0].num=sor[1].num-1;
	int tot=0;
	REP(i,1,n)
	{
		if(sor[i].num^sor[i-1].num)
		{
			++tot;
		}
		arr[sor[i].id]=tot;
	}
	REP(i,1,n)//处理 pre 数组
	{
		pre[i]=last[arr[i]];
		last[arr[i]]=i;
	}
	REP(i,1,m)
	{
		scanf("%d%d",&range[i].left,&range[i].right);
		range[i].id=i;
	}
	sort(range+1,range+1+m,Cmp2);//将查询的区间按右端点排序
	int now=1;
	Build();
	REP(i,1,m)
	{
		while(now<=range[i].right)//将小于右端点的贡献放上
		{
			if(pre[now])
			{
				Updata(pre[now],now-pre[now]);
			}
			++now;
		}
		answer[range[i].id]=Query(range[i].left,range[i].right);
		if(answer[range[i].id]==INF)
		{
			answer[range[i].id]=-1;
		}
	}
	REP(i,1,m)//输出
	{
		printf("%d\n",answer[i]);
	}
	return 0;
}
```

~~这个东西怎么搞在线 $\mathcal{O}(m\log n)$ 啊~~

建可持久化线段树就好了.

---

## 作者：critnos (赞：4)

一个常数大，复杂度高，但是好想好写的 $\log^2n$ 在线做法。

一开始想的是莫队套一个值域分块，对于每个数用双端队列维护下标的做法，但是鉴于其常数和 $5\times 10^5$ 的数据范围被抛弃了。

然后是这样思考的：

尝试用 $pre$ 数组，即上一个数出现位置的数组来做。这样看起来就变成了 RMQ 问题，即求区间 $x-pre_x$ 的最小值。但其实还有一个限制条件，就是 $l\le pre_x$ 的 $x$ 才能做贡献，因为如果 $l>pre_x$ 上一个数就不在这个区间内了。

那么对于这个诡异的东西，考虑线段树的每个节点都维护这个区间的一些信息（废话），将一个大区间拆分成 $\log n$ 个区间。相应的，也变成了整体问题，即对于一个序列，每次求满足 $l\le pre_x$ 的 $\min(x-pre_x)$。

这个问题就十分简单了，按 $pre$ 排序，预处理 $x-pre_x$ 的后缀 $\min$ 每次二分即可。

代码不到 70 行，这里只给出线段树的代码。

```cpp
struct seg
{
	int l,r;
	vector<pair<int,int> > a;
}t[2000005];
void build(int w,int l,int r)
{
	int i,mid=l+r>>1;
	for(i=l;i<=r;i++)
		t[w].a.push_back({pre[i],i-pre[i]});
	sort(t[w].a.begin(),t[w].a.end());
	t[w].l=l,t[w].r=r;
	for(i=t[w].a.size()-2;i>=0;i--)
		t[w].a[i].second=min(t[w].a[i].second,t[w].a[i+1].second);
	if(l<r)
	{
		build(ls,l,mid);
		build(rs,mid+1,r);
	}
}
int ask(int w,int l,int r)
{
	if(t[w].l>=l&&t[w].r<=r)
	{
		if(t[w].a.back().first<l) return 2e9;
		return (*lower_bound(t[w].a.begin(),t[w].a.end(),make_pair(l,0))).second;
	}
	int mn=2e9;
	if(t[ls].r>=l) mn=ask(ls,l,r);
	if(t[rs].l<=r) mn=min(mn,ask(rs,l,r));
	return mn;
}
```


---

## 作者：vectorwyx (赞：2)

定义 $v_x$ 为 $a_x$ 与 $a_x$ 前最近的与其相同的元素的距离，那么每次询问的答案就是 $\min_{x\in[l,r]}v_x$ ……吗？

并不，如果 $x-v_x<l$，也就是说如果离 $x$ 最近的与其相同的元素不在询问区间内，$v_x$ 就不能计入答案。但上面那个式子显然没考虑这一点。

注意到询问不强制在线，因此我们可以把询问离线后按 $l$ 从小到大排序。然后 $l$ 每增大 $1$，就把原来 $a_l$ 的贡献抹去。经过这番处理后询问的答案即为区间最小值，问题转为单点修改区间查 min，套一棵线段树就能做到 $O(n\log n)$。

什么？你问怎么求 $v$ 数组？离散化一下呗qwq。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define ll long long
#define ls(p) p<<1
#define rs(p) p<<1|1
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}

const int N=5e5+5,inf=1e9;
int a[N],b[N],v[N],ql[N],qr[N],m,n,od[N],pre[N],suf[N],ans[N];
struct Node{
	int L,R,val;
}tree[N<<2];

void push_up(int x){tree[x].val=min(tree[ls(x)].val,tree[rs(x)].val);}
void build(int x,int L,int R){
	tree[x].L=L,tree[x].R=R;
	if(L==R){
		tree[x].val=v[L];
		return;
	} 
	int mid=(L+R)>>1;
	build(ls(x),L,mid);
	build(rs(x),mid+1,R);
	push_up(x);
} 

void update(int x,int aim,int k){
	if(tree[x].L==tree[x].R){
		tree[x].val=k;
		return;
	}
	int mid=(tree[x].L+tree[x].R)>>1;
	if(aim<=mid) update(ls(x),aim,k);
	else update(rs(x),aim,k);
	push_up(x);
}

int ask(int x,int L,int R){
	//printf("ask(%d,%d,%d)\n",x,L,R);
	if(tree[x].L>=L&&tree[x].R<=R) return tree[x].val;
	int mid=(tree[x].L+tree[x].R)>>1,ans=inf;
	if(L<=mid) ans=min(ans,ask(ls(x),L,R));
	if(R>mid) ans=min(ans,ask(rs(x),L,R));
	return ans;
}

bool cmp1(int x,int y){return a[x]<a[y];} 
bool cmp2(int x,int y){return ql[x]<ql[y];} 

void _order(){//离散化 
	int rp=1;
	fo(i,1,n) od[i]=i;
	sort(od+1,od+1+n,cmp1);
	fo(i,1,n){
		b[od[i]]=rp;
		if(a[od[i]]!=a[od[i+1]]) rp++;
	}
	fo(i,1,n) a[i]=b[i];
	fo(i,1,m) od[i]=i;
	sort(od+1,od+1+m,cmp2);
	//fo(i,1,n) printf("%d ",a[i]);puts("");
	//fo(i,1,m) printf("%d %d\n",ql[od[i]],qr[od[i]]); 
}

void get_v(){
	fo(i,1,n) pre[i]=-inf;
	fo(i,1,n){
		v[i]=i-pre[a[i]];
		if(pre[a[i]]>0)suf[pre[a[i]]]=i;
		pre[a[i]]=i;
	}
	//fo(i,1,n) printf("%d ",v[i]);puts("");
	//fo(i,1,n) printf("%d ",suf[i]);puts(""); 
}

int main(){
	cin>>n>>m;
	fo(i,1,n) a[i]=read();
	fo(i,1,m) ql[i]=read(),qr[i]=read();
	_order();
	get_v();
	build(1,1,n); 
	fo(i,1,m){
		int p=od[i];
		fo(j,ql[od[i-1]],ql[p]-1) if(suf[j]) update(1,suf[j],inf);
		ans[p]=ask(1,ql[p],qr[p]);
		if(ans[p]>=inf-5) ans[p]=-1;
	}
	fo(i,1,m) printf("%d\n",ans[i]);
	return 0;
}
/*
-------------------------------------------------
*/
```


---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

补一个题解~

~~一看到 5e5 直接想根号算法。~~

首先对每一个位置 $i$ 预处理出来上一个等于它的位置 $pre[i]$ 与下一个等于它的位置 $nxt[i]$。从这些值就可以计算出来每一个位置对一个区间的答案贡献，因为显然贡献只可能是 $(pre[i],i)$ 这一对或者是 $(i,nxt[i])$ 这一对。

分块，设块长为 $B$。预处理出来所有块区间的答案；$O(B^2)$ 个块 $O(N^2/B)$ 时间。每一个询问显然是（块内答案，左边的贡献，右边的东线）的最大值；左边和右边分别最多有 $O(B)$ 个元素，可以暴力计算贡献。

于是得到一个 $O(N^2/B+QB)$ 的一个小常数解，取 $B=O(\sqrt N)$ 得到 $O((N+Q)\sqrt N)$ ~~轻松跑过（大雾~~

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

// begin fast read template by CYJian (source: https://www.luogu.com.cn/paste/i11c3ppx)

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

// end fast read template by CYJian

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

map<int, int> oc;
int ar[500005];
int pre[500005], nxt[500005];
constexpr int csize = 716;

int cnk[705][705];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; gi(n), gi(m);
	rep(i, n) gi(ar[i]);
	rep(i, n) {
		if(oc.count(ar[i])) pre[i] = oc[ar[i]];
		else pre[i] = -1000000000;
		oc[ar[i]] = i;
	}
	oc.clear();
	for(int i=n-1; i>=0; i--) {
		if(oc.count(ar[i])) nxt[i] = oc[ar[i]];
		else nxt[i] = 1000000000;
		oc[ar[i]] = i;
	}
	for(int i=0,c=0; i<n; i+=csize,c++) {
		int cur = 0x3f3f3f3f;
		for(int j=i; j<n; j++) {
			if(i <= pre[j]) cur = min(cur, j-pre[j]);	
			if(j%csize == csize-1) cnk[c][j/csize] = cur;
		}
	}
	while(m--) {
		int l, r; gi(l), gi(r); l--, r--;
		int cl = l/csize, cr = r/csize;
		if(cl == cr) {
			if(l % csize == 0 && r % csize == csize - 1) 
				print(cnk[cl][cr] == 0x3f3f3f3f ? -1 : cnk[cl][cr]);
			else {
				int cur = 0x3f3f3f3f;
				iter(i, l, r+1) if(l <= pre[i]) cur = min(cur, i-pre[i]);
				print(cur == 0x3f3f3f3f ? -1 : cur);
			}
		} else {
			int cl1 = cl+1, cr1 = cr-1;
			if(l % csize == 0) cl1--;
			if(r % csize == (csize-1)) cr1++;
			assert(l <= cl1*csize);
			assert((cr1+1)*csize-1 <= r);
			int cur = (cl1 <= cr1) ? cnk[cl1][cr1] : 0x3f3f3f3f;
			iter(i, l, cl1*csize) {
				if(l <= pre[i]) cur = min(cur, i-pre[i]);
				if(nxt[i] <= r) cur = min(cur, nxt[i]-i);
			}
			iter(i, (cr1+1)*csize, r+1) {
				if(l <= pre[i]) cur = min(cur, i-pre[i]);
				if(nxt[i] <= r) cur = min(cur, nxt[i]-i);
			}
			print(cur == 0x3f3f3f3f ? -1 : cur);
		}
		pc('\n');
	}
}
```

---

## 作者：cirnovsky (赞：1)

## 题意简述

不带修区间 Closest Equals。

## 题解

~~就这能黑？~~

可谓是非常套路的一道题。

开始打了个回滚莫队打算交上去 T 了卡常。

结果 WA 了（雾。

先把询问离线，按照右端点排序。

然后考虑维护一个数组 `pre[x]` 表示数 $x$ 的上一个位置。

然后我们遍历每一个询问（有序），并整一个原序列的指针 `ptr`，从一开始。

然后我们设当前遍历到的询问是第 $i$ 个，把 `ptr` 从当前的位置一直移到询问的右端点。

`ptr` 的移动的过程中我们维护一个前缀信息，把当前的贡献 `ptr-pre[a[ptr]]` （即当前 `ptr` 指针指到的数的最近一个相等的数）加到 `pre[a[ptr]]` 里。

移动完成后，这个询问的答案就是这个询问的左右端点代表区间的区间最小值。

综上，我们需要一个支持单点加，区间查极值的数据结构，线段树即可。

做完这题后可以去做一下 CF703D。

```cpp
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int Maxn = 5e5 + 5;
int n, m, isa[Maxn], pre[Maxn], ans[Maxn], sgt[Maxn << 2];
vector < int > disc;
struct Queries
{
	int l, r, id;
	bool operator < (const Queries& rhs) const
	{
		return r < rhs.r;
	}
} Q[Maxn];

void ins(int p, int l, int r, int x, int v)
{
	if (l == r)
	{
		sgt[p] = v;
		return ;
	}
	int mid = (l + r) >> 1;
	if (mid >= x)	ins(p << 1, l, mid, x, v);
	else	ins(p << 1 | 1, mid + 1, r, x ,v);
	sgt[p] = min(sgt[p << 1], sgt[p << 1 | 1]);
}

int find(int p, int l, int r, int x, int y)
{
	if (l > y || r < x) 	return 2e9;
	if (l >= x && r <= y)	return sgt[p];
	int mid = (l + r) >> 1, ret = 2e9;
	if (mid >= x)	ret = min(ret, find(p << 1, l, mid, x, y));
	if (mid < y)	ret = min(ret, find(p << 1 | 1, mid + 1, r, x, y));
	return ret;
}

// 以上的部分不需要解释吧

signed main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &isa[i]);
		disc.push_back(isa[i]);
	}
	sort(disc.begin(), disc.end());
	disc.erase(unique(disc.begin(), disc.end()), disc.end());
	for (int i = 1; i <= n; ++i)	isa[i] = lower_bound(disc.begin(), disc.end(), isa[i]) - disc.begin() + 1;
	for (int i = 0; i < (Maxn << 2); ++i)	sgt[i] = 2e9; // 离散化 & 线段树赋初值（懒得建树）
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d %d", &Q[i].l, &Q[i].r);
		Q[i].id = i;
	}
	sort(Q + 1, Q + 1 + m);
	int ptr = 1;
	for (int i = 1; i <= m; ++i)
	{
		while (ptr <= Q[i].r) // 移动 ptr 指针到询问右端点
		{
			if (pre[isa[ptr]])	ins(1, 1, n, pre[isa[ptr]], ptr - pre[isa[ptr]]); // 把当前这个数的贡献加到上一个出现这个数的位置
			pre[isa[ptr]] = ptr; // 顺手维护 pre 数组，顺带一提如果你要预处理 pre 数组的话定义会有区别
			++ptr;
		}
		ans[Q[i].id] = find(1, 1, n, Q[i].l, Q[i].r);
		if (ans[Q[i].id] == 2e9)	ans[Q[i].id] = -1;
	}
	for (int i = 1; i <= m; ++i)	printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：yyrwlj (赞：0)

记上一个与 $a_i$ 相同的数的位置是 $pre_i$。

只考虑 $y$，容易发现满足题目要求即 $y \le r$ 且 $pre_y \ge l$，再加上这些数在询问前面，凑成三维偏序。

然后就可以愉快的使用 cdq 分治了。

将代码中的 sort 换成手动归并排序即可使复杂度从 $O(n\log^2n)$ 变为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define lowbit(o) o & -o
#define pb push_back
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int N = 1000005;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const LL INF = 2e18;
struct Node{
	int pos, pre, op, id, ans;
}q[N];
int a[N], ans[N];
bool cmpA(Node A,Node B)
{
	if (A.pos != B.pos)
		return A.pos < B.pos;
	if (A.pre != B.pre)
		return A.pre > B.pre;
	return A.op < B.op;
}
bool cmpB(Node A,Node B)
{
	if (A.pre != B.pre)
		return A.pre > B.pre;
	return A.op < B.op;
}
void cdq(int l,int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	cdq(l, mid), cdq(mid + 1, r);
	sort(q + l, q + mid + 1, cmpB);
	sort(q + mid + 1, q + r + 1, cmpB);
	int j = l, mn = 1e9;
	for (int i=mid+1;i<=r;i++)
	{
		while (j <= mid && q[j].pre >= q[i].pre)
			if (!q[j].op)
				mn = min(mn, q[j].pos - q[j].pre), j ++;
			else
				j ++;
		q[i].ans = min(q[i].ans, mn);
	}
}
void work()
{
	int n, m;
	cin>>n>>m;
	map<int, int> mp;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		q[i] = {i, mp[a[i]], 0, 0, (int)1e9};
		mp[a[i]] = i;
	}
	for (int i=1;i<=m;i++)
	{
		int l, r;
		cin>>l>>r;
		q[n + i] = {r, l, 1, i, (int)1e9};
	}
	sort(q + 1, q + n + m + 1, cmpA);
	cdq(1, n + m);
	for (int i=1;i<=n+m;i++)
		ans[q[i].id] = q[i].ans;
	for (int i=1;i<=m;i++)
		if (ans[i] > 1e8)
			cout << "-1\n";
		else
			cout << ans[i] << '\n';
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int _T = 1;
	//cin >> _T;
	while (_T--)
		work();
	return 0;
}
```

---

## 作者：ExplodingKonjac (赞：0)

### [原题链接](https://www.luogu.com.cn/problem/CF522D)

## 解题思路

看到这题没有修改，于是就想到使用离线操作：将询问区间按照右端点排序。

对于每一个位置 $i$，记录它与**下一个**和 $a_i$ 相同的数字的距离，记为 $min_i$，如果 $i$ 后面没有找到相同的数字，则 $min_i=\mathrm{INF}$。因为我们是按照右端点有序进行离线操作的，所以 $min_i$ 不会受到 $r$ 右边数字的影响，查询的时候可以直接找出 $[l,r]$ 中 $min_i$ 的最小值。每次枚举到一个位置 $p$ 时都更新一下 $min_{pos_{a_p}}\gets i-pos_{a_p}$，其中 $pos_{a_p}$ 为数字 $a_p$ 上一次出现的位置。

这其实是单点修改与区间最值的问题，使用线段树维护。

整个流程是：

$\begin{aligned}
&\texttt{for }i\texttt{ in }[1,n]:\\
&\qquad \texttt{if }pos[i]:\\
&\qquad\qquad \text{modify}(pos[i],i-pos[i])\\
&\qquad pos[i]\gets i\\
&\qquad\texttt{for }j\texttt{ with }r[j]=i:\\
&\qquad\qquad ans[j]\gets\text{query}(l[j],i)
\end{aligned}$

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF=0x7fffffff;
int n,m,a[500005],b[500005],pos[500005],ans[500005];
int read()
{
    char ch=getchar();
    int res=0,sym=1;
    for(;isspace(ch);ch=getchar());
    if(ch=='-') sym=-1,ch=getchar();
    for(;isdigit(ch);ch=getchar())  res=res*10+ch-'0';
    return res*sym;
}
struct TreeNode
{
    int val;
    TreeNode *lc,*rc;
    TreeNode(int v): val(v)
        { lc=rc=nullptr; }
}*rt;
typedef TreeNode *pNode;
void build(int l=1,int r=n,pNode &i=rt)
{
    i=new TreeNode(INF);
    if(l!=r)
    {
        int mid=(l+r)>>1;
        build(l,mid,i->lc),build(mid+1,r,i->rc);
    }
}
void modify(int p,int x,pNode i=rt,int l=1,int r=n)
{
    if(l==r)    return i->val=x,void();
    int mid=(l+r)>>1;
    if(mid>=p)  modify(p,x,i->lc,l,mid);
    else    modify(p,x,i->rc,mid+1,r);
    i->val=min(i->lc->val,i->rc->val);
}
int query(int lq,int rq,pNode i=rt,int l=1,int r=n)
{
    if(l>=lq && r<=rq)	return i->val;
    int mid=(l+r)>>1,res=INF;
    if(mid>=lq) res=min(res,query(lq,rq,i->lc,l,mid));
    if(mid<rq)  res=min(res,query(lq,rq,i->rc,mid+1,r));
    return res;
}
struct Edge{ int to,w,nxt; }e[500005];
int cnt,head[500005];
inline void addEdge(int u,int v,int w)
{
    e[++cnt]=(Edge){v,w,head[u]};
    head[u]=cnt;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)   b[i]=a[i]=read();
    sort(b+1,b+n+1);
    int siz=unique(b+1,b+n+1)-b;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+siz,a[i])-b;
    for(int i=1;i<=m;i++)
    {
        int l=read(),r=read();
        addEdge(r,l,i);
    }
    build(1,n);
    for(int i=1;i<=n;i++)
    {
        int x=a[i];
        if(pos[x])
            modify(pos[x],i-pos[x]);
        pos[x]=i;
        for(int j=head[i];j;j=e[j].nxt)
            ans[e[j].w]=query(e[j].to,i);
    }
    for(int i=1;i<=m;i++)
        if(ans[i]==INF)	puts("-1");
        else    printf("%d\n",ans[i]);
    return 0;
}
```


---

## 作者：tommymio (赞：0)

好题，不会很难，省选之前帮菜鸡复习了一下离线数据结构的套路（

这题的思想和 $\texttt{SDOI2009}$ HH的项链挺像的。处理出 $pre_i$ 为最近一次 $a_i$ 这种权值出现的位置。那么对于一个询问 $[L,R]$，答案即为：

$$
\min\limits_{L\leq i\leq R}\{i-pre_i\}(pre_i\geq L)
$$

这个 $pre_i\geq L$ 的限制能不能去掉呢？当然可以。对于一个 $i-pre_i$，我们只在 $pre_i$ 处统计贡献，对询问右端点排序离线处理，就可以保证出现贡献的 $i$ 和 $pre_i$ 都出现在询问 $[L,R]$ 内了。

当然我们也有其他更简单粗暴的在线处理方法。对每个节点维护一个以 $pre_i$ 为关键字的 $i-pre_i$ 的后缀 $\min$，然后查询的时候直接二分。时间复杂度为 $O(Q\log^2 n)$。

这里给出第一种做法的实现awa

```cpp
/* stuff you should look for
	* int overflow, array bounds, uppercase/lowercase
	* special cases (n=1?)
	* do sth. instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
#include<cstdio>
#include<algorithm>
const int inf=0x3f3f3f3f;
int num=0;
struct node {int l,r,id;}q[500005];
inline bool cmp(const node &x,const node &y) {return x.r<y.r;}
struct SegmentTree {
	#define ls p<<1
	#define rs p<<1|1
	int n,mn[1600005];
	inline int min(const int &x,const int &y) {return x<y? x:y;}
	inline void init(int n) {this->n=n; for(register int i=1;i<=4*n;++i) mn[i]=inf;}
//	inline void print(int p,int l,int r) {printf("%d %d %d\n",l,r,mn[p]); if(l==r) return; int mid=l+r>>1; print(ls,l,mid); print(rs,mid+1,r);}
//	inline void show() {print(1,1,n);}
	inline void _modify(int p,int l,int r,int x,int val) {
		if(l==r) {mn[p]=val; return;}
		int mid=l+r>>1;
		if(x<=mid) _modify(ls,l,mid,x,val);
		else _modify(rs,mid+1,r,x,val);
		mn[p]=min(mn[ls],mn[rs]);
//		printf("mod=%d %d %d\n",l,r,mn[p]);
	}
	inline int _ask(int p,int l,int r,int L,int R) {
//		printf("ask=%d %d\n",l,r);
		if(L<=l&&r<=R) return mn[p];
		int mid=l+r>>1;
		if(R<=mid) return _ask(ls,l,mid,L,R);
		if(L>mid) return _ask(rs,mid+1,r,L,R);
		return min(_ask(ls,l,mid,L,mid),_ask(rs,mid+1,r,mid+1,R));
	}
	inline void modify(int pos,int v) {_modify(1,1,n,pos,v);}
	inline int ask(int L,int R) {return _ask(1,1,n,L,R);}
}SGT;
int res[500005],a[500005],b[500005],pre[500005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
int main() {
	int n=read(),Q=read(); SGT.init(n);
	for(register int i=1;i<=n;++i) b[++num]=a[i]=read();
	std::sort(b+1,b+1+num); num=std::unique(b+1,b+1+num)-b-1;
	for(register int i=1;i<=n;++i) a[i]=std::lower_bound(b+1,b+1+num,a[i])-b;
//	for(register int i=1;i<=n;++i) printf("%d ",a[i]); printf("\n"); 
	for(register int i=1;i<=Q;++i) {q[i].l=read();q[i].r=read();q[i].id=i;}
	std::sort(q+1,q+1+Q,cmp); int cur=1;
	for(register int i=1;i<=Q;++i) {
		while(cur<=q[i].r) {
			if(pre[a[cur]]) SGT.modify(pre[a[cur]],cur-pre[a[cur]]);//printf("?=%d %d\n",pre[a[cur]],cur-pre[a[cur]]);
//			printf("%d %d %d\n",cur,pre[a[cur]],cur-pre[a[cur]]);
			pre[a[cur]]=cur; ++cur; 
		}
		int tmp=SGT.ask(q[i].l,q[i].r);
		if(tmp==inf) res[q[i].id]=-1;
		else res[q[i].id]=tmp;  
//		SGT.show();
//		printf("L,R=%d %d %d ans=%d\n",cur,q[i].l,q[i].r,tmp);
		
	}
	for(register int i=1;i<=Q;++i) printf("%d\n",res[i]);
	return 0;
}

```



---

## 作者：Suzt_ilymtics (赞：0)

## 写在前面

注：因为变量名中有下划线，所以有些地方使用的是代码块而没有使用 $\text{LateX}$ 渲染，恳请管理大大原谅。

转了一圈题解发现没有用莫队的？

~~唯一一个涉及到的貌似还被卡了？~~

那么我就来一发回滚莫队吧。

题面：[CF522D Closest Equals](https://www.luogu.com.cn/problem/CF522D)

## Solution

一开始把题目读错了，以为求的是一段区间内最远的两个相同的数的距离，

~~这不就回滚莫队板子嘛~~。

调半天发现是求最近的两个相同的数的距离，想想怎么用莫队维护。

跟着回滚莫队的做法，先进行离散化、分块、排序这一类基本操作。

然后每次轮到一个新块时，我们不是要移动两端点到块的右端嘛。

我们要查询的区间因此就分成了两块，暂且称作左块和右块。

题目要求是求最近的，那么只需统计相邻的两个相同的数的贡献。

开四个数组 ```cntr[x], cntr_pre[x], cntl_t[x], cntl_pre_t[x]```，分别表示一个数 $x$ 在右块的最小的位置，$x$ 在右块中上一次出现的位置，$x$ 在左块中的最大位置，$x$ 在左块中上一次出现的位置。

画成图大体是这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/t5agh6xs.png)

假设图中标记的都是一个数：

- 如果在左块中又枚举到一个数 $pos_1$，它对答案的贡献显然是 ```cntl_pre_t - pos1```。
- 如果在右块中又枚举到一个数 $pos_2$，它对答案的贡献显然是
```pos2 - cntr_pre```。
- 因为左块和右块之间可能也会有贡献，所以还需要统计 ```cntr - cntl_t```。


#### 一些小细节：

- 注意没有相同的数时要输出 $-1$；
- 在左块或者右块中统计答案时，如果其中某一个值不存在就不要统计答案了。


## Code


```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 5e5+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

struct Ques{
    int l, r, bh;
}q[MAXN];

int n, m; 
int L = 1, R = n, preL = 0, Ans, Res, _L;
int a[MAXN], date[MAXN], date_num = 0;
int lef[MAXN], rig[MAXN], bel[MAXN];
int cntr[MAXN], cntr_pre[MAXN], cntl_t[MAXN], cntl_pre_t[MAXN];
int ans[MAXN];

int read(){
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
    return f ? -s : s;
}

bool cmp(Ques x, Ques y) { return bel[x.l] == bel[y.l] ? x.r < y.r : x.l < y.l; } //按块排序 

void Init() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) a[i] = date[i] = read();
    sort(date + 1, date + n + 1); date[0] = -INF; //离散化 
    for(int i = 1; i <= n; ++i) if(date[i] != date[i - 1]) date[++date_num] = date[i];
    for(int i = 1; i <= n; ++i) a[i] = lower_bound(date + 1, date + date_num + 1, a[i]) - date;
    for(int i = 1; i <= date_num; ++i) cntr[i] = cntr_pre[i] = ans[i] = INF; 
    for(int i = date_num + 1; i <= m; ++i) ans[i] = INF; //初始化为极大值 
    
    int len = sqrt(n + 0.5);//分块 
    int block_num = n / len;
    for(int i = 1; i <= block_num; ++i) lef[i] = rig[i - 1] + 1, rig[i] = rig[i - 1] + len; 
    if(rig[block_num] < n) {
        ++ block_num;
        lef[block_num] = rig[block_num - 1] + 1;
        rig[block_num] = n;
    }
    for(int i = 1; i <= block_num; ++i) 
        for(int j = lef[i]; j <= rig[i]; ++j) 
            bel[j] = i;
}

void Add(int pos, int &ans_) {
    int x = a[pos];
    cntr[x] = min(cntr[x], pos); //更新右块中x的最小的位置
    if(cntr_pre[x] != INF) ans_ = min(ans_, pos - cntr_pre[x]); // 只有x在右块中出现过才统计答案
    cntr_pre[x] = pos; // 更新
}
void Add_tem(int pos, int &ans_, int type) {
    int x = a[pos];
    cntl_t[x] = max(cntl_t[x], pos); // 更新左块中x的最大位置
    if(cntl_pre_t[x]) ans_ = min(ans_, cntl_pre_t[x] - pos); //只有x在左块中出现过才统计答案
    cntl_pre_t[x] = pos; //更新
    if(cntr[x] != INF && cntl_t[x] && type) ans_ = min(ans_, cntr[x] - cntl_t[x]); //统计左右块之间的贡献
}

void Del(int pos) { cntr[a[pos]] = cntr_pre[a[pos]] = INF; }
void Del_tem(int pos) { cntl_t[a[pos]] = cntl_pre_t[a[pos]] = 0; }

int main()
{
    Init();
    for(int i = 1; i <= m; ++i) q[i].l = read(), q[i].r = read(), q[i].bh = i;
    sort(q + 1, q + m + 1, cmp);
    for(int i = 1; i <= m; ++i) { //回滚莫队基操？
        if(preL != bel[q[i].l]) {
            while(R > rig[bel[q[i].l]]) Del(R--);
            while(L <= rig[bel[q[i].l]]) Del(L++);
            Ans = INF, R = rig[bel[q[i].l]], preL = bel[q[i].l];
        }
        if(bel[q[i].l] == bel[q[i].r]) {
            for(int j = q[i].r; j >= q[i].l; --j) Add_tem(j, ans[q[i].bh], 0); //倒序枚举方便统计答案 
            for(int j = q[i].r; j >= q[i].l; --j) Del_tem(j);
        } else {
            while(R < q[i].r) Add(++R, Ans);
            _L = L, Res = Ans;
            while(_L > q[i].l) Add_tem(--_L, Res, 1);
            ans[q[i].bh] = Res;
            while(_L < L) Del_tem(_L++);
        }
    }
    for(int i = 1; i <= m; ++i) printf("%d\n", ans[i] == INF ? -1 : ans[i]);
    return 0;
}
```

---

