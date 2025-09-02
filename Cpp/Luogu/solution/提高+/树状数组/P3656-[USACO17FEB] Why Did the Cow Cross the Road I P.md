# [USACO17FEB] Why Did the Cow Cross the Road I P

## 题目描述

为什么奶牛要过马路？我们可能永远无法知道完整的原因，但可以肯定的是，Farmer John 的奶牛确实经常过马路。事实上，它们过马路的频率如此之高，以至于它们的路径交叉时经常会撞到彼此，这种情况 Farmer John 希望能够改善。

Farmer John 饲养了 $N$ 种奶牛（$1 \leq N \leq 100,000$），他的每一块田地都专门用于放牧某一种特定的奶牛品种；例如，专门用于品种 12 的田地只能用于品种 12 的奶牛，而不能用于其他品种。一条长长的马路贯穿他的农场。马路的一侧有一系列 $N$ 块田地（每块田地对应一种品种），马路的另一侧也有一系列 $N$ 块田地（同样每块田地对应一种品种）。当一头奶牛过马路时，它会在为其特定品种指定的两块田地之间穿行。

如果 Farmer John 当初计划得更仔细，他可能会在马路两侧按相同的品种顺序排列田地，这样每块品种的田地就会直接相对。这将使奶牛过马路时，不同品种的奶牛不会撞到彼此。然而，马路两侧的田地顺序可能不同，因此 Farmer John 观察到可能存在一些品种对会交叉。一对不同的品种 $(a,b)$ 是“交叉的”，如果品种 $a$ 的任何过马路路径都必须与品种 $b$ 的任何过马路路径相交。

Farmer John 希望最小化交叉品种对的数量。出于物流原因，他决定可以通过对马路一侧的田地进行“循环移位”来重新安排奶牛的位置。也就是说，对于某个 $0 \leq k < N$，每头奶牛都会移动到其前方 $k$ 块田地，最后 $k$ 块田地的奶牛会移动到前 $k$ 块田地。例如，如果马路一侧的田地最初按品种顺序为 3, 7, 1, 2, 5, 4, 6，并进行 $k=2$ 的循环移位，新的顺序将为 4, 6, 3, 7, 1, 2, 5。请确定在对马路一侧的田地进行适当的循环移位后，可能存在的交叉品种对的最小数量。

## 样例 #1

### 输入

```
5
5
4
1
3
2
1
3
2
5
4```

### 输出

```
0```

# 题解

## 作者：elijahqi (赞：3)

看到这道题，我们可以想到2013年提高组火柴排队那道题，这道题其实同理，利用离散化的原理，预处理一个数组然后我们求逆序对就可以 最后求转完逆序对个数最小就可以

题目说两个都可以转，我一开始认为转一个就可以了，后来ly的提醒下发现转一个无论如何也不能满足转第二个产生的情况

比如我们观察这样一个序列

5 3 2 4 1   我们强制对第一行进行编号，1 2 3 4 5

2 1 4 3 5 根据第一行的编号，我们可以生成第二行 3 5 4 2 1

这时候我们去转动第二行，发现只是顺序改变了 比如变成5 4 2 1 3

假如我们转动第一行 3 2 4 1 5 再重新编号 1 2 3 4 5

这时候对应第二行 2 4 3 1 5  我们对比这两个红色的发现他们按照大小重新交换了一遍，相当于每个都减了一 所以只旋转一个是不可以的

1、用树状数组求初始数列的逆序对

2、不停旋转这个序列， 加入5 4 2 1 3 中3换到前面，那么因为交换3而导致的改变就是减去3前面比3大的数加上前面比3小的数就是3交换到前面对答案贡献的改变量

```cpp
#include<cstdio>
#define N 110000
inline int read(){
    int x=0;char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int s[N],map[N],c[N],a[N],b[N],n;
inline void add(int x){while (x<=n){s[x]++;x+=x&(-x);}}
inline int query(int x){
    int sum=0;
    while (x){
        sum+=s[x];x-=x&(-x);
    }
    return sum;
}
inline long long min(long long x,long long y){return x<y?x:y;}
int main(){
    freopen("3656.in","r",stdin);
    n=read();
    for (int i=1;i<=n;++i) a[i]=read();for (int i=1;i<=n;++i) b[i]=read();
    for (int i=1;i<=n;++i) map[a[i]]=i;
    for (int i=1;i<=n;++i) c[i]=map[b[i]];
    long long ans=0;
    for (int i=1;i<=n;++i)add(c[i]),ans+=(long long)(i)-(long long)query(c[i]);
    long long tmp=ans;
    for (int i=n;i;--i) {
        tmp+=(long long)(c[i]-1);tmp-=(long long) (n-c[i]);
        ans=min(ans,tmp);
    } 
    for (int i=1;i<=n;++i)s[i]=0;
    for (int i=1;i<=n;++i) map[b[i]]=i;
    for (int i=1;i<=n;++i) c[i]=map[a[i]];
    long long ans1=0;
    for (int i=1;i<=n;++i)add(c[i]),ans1+=(long long)(i)-(long long)query(c[i]);
    tmp=ans1;
    for (int i=n;i;--i) {
        tmp+=(long long)(c[i]-1);tmp-=(long long) (n-c[i]);
        ans1=min(ans1,tmp);
    } 
    printf("%lld",min(ans1,ans));
    return 0;
}
```

---

## 作者：KSToki (赞：2)

# 题目大意
给出两个大小为n的排列a、b，在a、b间每个相同数字间连一条边，现在对a或者b进行“循环转移”操作，求操作后这些边最小的相交的次数。

什么情况下两条线会交叉？稍微推一推就可以知道，当存在两个数$x,y$，$x$在a中对应的位置先于$y$，而在b中对应的位置后于$y$，这样就会产生一次相交。

这让我们很容易就想到了逆序对求解，分别针对a和b，将值映射到map中（这里用数组就够了），枚举每次“循环转移”操作后的序列，求逆序对数，复杂度为$O(n^2logn)$，会TLE的。

针对每次“循环转移”操作，我们都只将第一个元素移到了最后，操作量很小，而我们每次都要重新求逆序对，显然很浪费。我们研究将第一个元素移到最后产生的影响：

设这个元素为x，因为它是最前面的，所以所有比它小的元素都与它组成逆序对，有（x-1）个；当它移到最后时，这些逆序对不再存在，而比x大的元素与其成为新的逆序对，有（n-x）个。所以我们只需要一开始求一次逆序对，每次仅用$O(1)$的时间来更新逆序对数量，时间复杂度$O(n log n)$，来源于第一次求逆序对。

代码需要注意两点，一是要开long long，二是记得清零

接下来就是代码了：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	char ch=getchar();
	while(ch<'0'||ch>'9')
	    ch=getchar();
	long long res=0;
	while(ch>='0'&&ch<='9')
	{
		res=(res<<1)+(res<<3)+ch-'0';
		ch=getchar();
	}
	return res;
}
long long t[100001],q[100001];
long long nxd;
void qsort(long long l,long long r)
{
	if(l==r) return;
	long long mid=(l+r)/2;
	qsort(l,mid);
	qsort(mid+1,r);
	long long i=l,j=mid+1,k=0;
	while(i<=mid&&j<=r)
	{
		if(q[j]<q[i])
		{
			t[++k]=q[j];
			++j;
			nxd+=mid-i+1;
		}
		else
		{
			t[++k]=q[i];
			++i;
		}
	}
	while(i<=mid)
	{
	    t[++k]=q[i];
	    ++i;
	}
	while(j<=r)
	{
		t[++k]=q[j];
		++j;
	}
	for(i=l,j=1;i<=r;++i,++j)
	    q[i]=t[j];
}
long long n,a[100001],ta[100001],To[100001],b[100001],tb[100001];
long long ans=0x7ffffffffff;//蒟蒻习惯性只打了7个f，调了半天
void solve(long long A[],long long B[])
{
	for(register long long i=1;i<=n;++i)
	    To[A[i]]=i;
	for(register long long i=1;i<=n;++i)
	    B[i]=q[i]=To[B[i]];
	nxd=0;//清零
	qsort(1,n);
	ans=min(ans,nxd);
	for(register long long i=1;i<n;++i)
	{
		nxd+=n-B[i]-B[i]+1;
		ans=min(ans,nxd);
	}
}
int main()
{
	n=read();
	for(register long long i=1;i<=n;++i)	    
		ta[i]=a[i]=read();
	for(register long long i=1;i<=n;++i)
	    tb[i]=b[i]=read();
	solve(ta,tb);//分别对a、b进行“循环转移”操作，求min
	solve(b,a);
	printf("%lld\n",ans);
	return 0;
}
```

完！

---

## 作者：kczno1 (赞：2)

吐槽一下这题翻译挺烂的，还是看英文好。

题意:

给两个排列a,b。

两个数x,y交叉就是类似这样:

a:...x...y..

b:.....y...x

也就是 (x在a的位置<y在a中的位置)!=(x在b中的位置<y在b中的位置)

你可以选一个排列进行任意长度循环位移，

求最少交叉数对个数。

题解:

定义qi为ai在b中的位置，交叉对就是q的逆序对。

只要求出逆序对，之后每次把最后的移到最前面，并维护逆序对个数。

如何维护?

考虑把一个x从最后面移到最前面，本来贡献是n-x，后来贡献是x-1。

因为有可能移动b，所以把a,b交换了再做一次就可以了。

```cpp
#include<bits/stdc++.h>
using std::min;

#define rep(i,n) for(int i=1;i<=n;++i)
#define gc getchar()
typedef long long ll;

int read()
{
    char c;
    while((c=gc)<'0');
    int x=c-'0';
    while((c=gc)>='0')x=x*10+c-'0';
    return x;
}

void chmin(ll &x,ll y)
{
    if(x>y)x=y;
}

const int N=1e5+5;
int n,a[N],b[N],dy[N],q[N];

int c[N];
int qiu(int i)
{
    int ans=0;
    for(;i<=n;i+=i&-i)ans+=c[i];
    return ans;
}
void add(int i)
{
    for(;i;i-=i&-i)++c[i];
}
ll solve(int *a,int *b)
{
    rep(i,n)dy[b[i]]=i;
    rep(i,n)q[i]=dy[a[i]];
    
    rep(i,n)c[i]=0;
    ll ans=0;
    rep(i,n)
    {
        ans+=qiu(q[i]);
        add(q[i]);
    }
    ll now=ans;
    for(int i=n;i;--i)
    {
        now-=n-q[i];
        now+=q[i]-1;
        chmin(ans,now);
    }
    return ans;
}

int main()
{
    freopen("1.in","r",stdin);
    n=read();
    rep(i,n)a[i]=read();
    rep(i,n)b[i]=read();
    printf("%lld\n",min(solve(a,b),solve(b,a)));
}
```

---

## 作者：Guizy (赞：1)

我们可以发现可以把操作转化成每次向前移一个田地，并且最优答案一定可以通过只转一个序列得到。

我们考虑怎么求。首先我们要求出一开始的不做任何操作的答案。设两个序列分别为 $a,b$。

两条线会产生交点当且仅当 $posa_x<posb_x$ 且 $posa_y>posb_y$（$posa_i$ 表示 $i$ 这个数在 $a$ 中的位置，$posb_i$ 同理）。

现在以旋转 $a$ 举例。

我们从左到右枚举 $a$ 的每个位置 $i$，我们在 $b$ 序列上查询 $posb_i$ 右边有多少条线被连接了，直接加到答案上（因为是从左到右枚举所以 $posb_i$ 右边的位置都是从 $i$ 之前连接过来的，一定会产生交点），最后更新这个位置被连接。可以用线段树或者树状数组实现。

```cpp
void update(int x,int l,int r,int p){
	if(l==r&&x==l){
		tree[p]++;
		return;
	}int mid=(l+r)>>1;
	if(x<=mid) update(x,l,mid,p<<1);
	else update(x,mid+1,r,p<<1|1);
	tree[p]=tree[p<<1]+tree[p<<1|1];
}
int query(int l,int r,int nowl,int nowr,int p){
	if(l<=nowl&&nowr<=r) return tree[p];
	if(nowl>r||nowr<l) return 0;
	int mid=(nowl+nowr)>>1;
	return query(l,r,nowl,mid,p<<1)+
      query(l,r,mid+1,nowr,p<<1|1);
}

int ans=0;
memset(tree,0,sizeof tree);
rep(i,1,n) pos[y[i]]=i;//对应上文 posb
rep(i,1,n){
	ans+=query(pos[x[i]]+1,n,1,n,1);
	update(pos[x[i]],1,n,1);
}
```

“循环转移”的话，每次一个数从最后变到最前面，对答案的贡献为（设 $i$ 是 $a$ 的最后一个位置）：

$$
(posb_i-1)-(n-posb_i)
$$

因为 $i$ 是最后一个位置，在 $b_{posb_i}$ 后面的点连的线肯定会与 $(i,posb_i)$ 产生交点（即减少 $n-posb_i$ 个交点）。而“循环转移”后 $i$ 变成第一个位置，$b_{posb_i}$ 前面的点也会与这条 $(1,posb_i)$ 产生交点（即新增 $posb_i-1$ 个交点）。

```cpp
tmp=ans;
for(int i=n;i;i--){//一直循环转移
	ans=ans-n+pos[x[i]]*2-1;//化简可得
	tmp=min(tmp,ans);//取最小值
}
```

$tmp$ 就是答案，旋转 $b$ 序列同理。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int Max=200001;
int n,a[Max],b[Max],pos[Max],tree[Max<<2];

void update(int x,int l,int r,int p){
	if(l==r&&x==l){
		tree[p]++;
		return;
	}int mid=(l+r)>>1;
	if(x<=mid) update(x,l,mid,p<<1);
	else update(x,mid+1,r,p<<1|1);
	tree[p]=tree[p<<1]+tree[p<<1|1];
}
int query(int l,int r,int nowl,int nowr,int p){
	if(l<=nowl&&nowr<=r) return tree[p];
	if(nowl>r||nowr<l) return 0;
	int mid=(nowl+nowr)>>1;
	return query(l,r,nowl,mid,p<<1)+
      query(l,r,mid+1,nowr,p<<1|1);
}

int solve(int*x,int*y){
	int tmp,ans=0;
	memset(tree,0,sizeof tree);
	rep(i,1,n) pos[y[i]]=i;
	rep(i,1,n){
		ans+=query(pos[x[i]]+1,n,1,n,1);
		update(pos[x[i]],1,n,1);
	}tmp=ans;
	for(int i=n;i;i--){
		ans=ans-n+pos[x[i]]*2-1;
		tmp=min(tmp,ans);
	}
	return tmp;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	rep(i,1,n) cin>>a[i];
	rep(i,1,n) cin>>b[i];
	cout<<min(solve(a,b),solve(b,a));
}
```

---

## 作者：WaterSun (赞：1)

# 思路

首先，$A$ 和 $B$ 只会移动一个，那么，我们分开来算，我们先假定 $B$ 会动。

不妨令 $A$ 与 $b$ 连边的端点为 $x,y$。如果有线段 $pq$ 能与 $xy$ 相交，一定满足如下其中一条规律：

1. $p < x \wedge q > y$
2. $p > x \wedge q < y$

发现每一次循环右移一次，只会影响一条端点在 $B_n$ 的位置的线段，其余线段相对位置不变。

令 $B_n$ 在 $A$ 中的位置为 $x$。因为 $B_n$ 是在 $B$ 中的最后一个元素，所以如果有线段能与其所在线段相交，那么只能是满足上述规律中的第 2 种。所以所有以 $A_{x + 1 \sim n}$ 为端点的线段一定与 $B_n$ 所在线段相交。

那么，如果我们将 $B$ 循环右移一位后，可以发现原本与 $B_n$ 相交的线段都不会相交了，即将数量 $res$ 变为了 $res - (n - x)$。

再来考虑 $B_n$ 循环右移到 $B_1$ 时会产生新的数量。因为 $B_1$ 是 $B$ 中的第一个元素，所以如果有线段能与其所在线段相交，那么只能是满足上述条件中的第 1 种。所以，所有以 $A_{1 \sim x - 1}$ 为端点的线段一定与其相交。

那么，我们将 $B$ 循环右移一位后，可以发现能新产生 $x - 1$ 条线段，即将数量 $res$ 变为了 $res + (x - 1)$。

那么结果 $res$ 将变为 $res - (n - x) + (x - 1) = res - n + 2x - 1$。

接下来只需要处理出 $res$ 在不动时的结果即可。

我们将 $pos_i$ 表示 $B$ 在 $A$ 中的位置，可以发现当 $i < j \wedge pos_i > pos_j$ 时就会产生一条相交的线段对。然后发现本质上就是求 $pos$ 的逆序对数量，用树状数组算一下即可。

**注意：不要忘了讨论 $A$ 动的情况。**

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 1e5 + 10;
int n,ans,t;
int arr[N],brr[N],vis[N],pos[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

struct BIT{
	int tr[N];
	
	inline int lowbit(int x){
		return x & -x;
	}
	
	inline void modify(int x,int k){
		for (re int i = x;i <= n;i += lowbit(i)) tr[i] += k;
	}
	
	inline int query(int x){
		int res = 0;
		for (re int i = x;i;i -= lowbit(i)) res += tr[i];
		return res;
	}
}tree;

inline int f(int *arr,int *brr){
	for (re int i = 1;i <= n;i++) vis[arr[i]] = i;
	for (re int i = 1;i <= n;i++) pos[i] = vis[brr[i]];
	int res = 0,ans = 0;
	memset(tree.tr,0,sizeof(tree.tr));
	for (re int i = n;i;i--){
		res += tree.query(pos[i]);
		tree.modify(pos[i],1);
	}
	ans = res;
	for (re int i = n;i;i--){
		res = res - n + 2 * pos[i] - 1;
		ans = min(ans,res);
	}
	return ans;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	for (re int i = 1;i <= n;i++) brr[i] = read();
	printf("%lld",min(f(arr,brr),f(brr,arr)));
	return 0;
}
```

---

## 作者：白鲟 (赞：1)

## 题意简述
给出两个 $1$ 到 $n$ 的排列 $\{a\},\{b\}$，可以选择其中一个进行若干次循环移位，移位后将两个排列中相同元素连线，求线段交叉对数的最小值。

## 题目分析
首先分析什么情况下线段会交叉：设 $a_i$ 与 $b_j$ 对应，$a_p$ 与 $b_q$ 对应，且 $i<p$，则当 $j>q$ 时满足这两组数的连线相交。而很巧的是，这个条件与逆序对的条件十分相似。那么我们可以尝试着把交叉对数转化为逆序对数。  

如何转化呢？我们记录 $b_i$ 在数列 $\{a\}$ 中出现的位置 $pos_i$ ，可以顺利地发现，当 $pos_i>pos_j,i<j$ 时，会出现一对交叉。于是我们发现交叉对数即为数列 $\{pos\}$ 的逆序对数。  

于是我们可以想到求出每一次循环移位的逆序对数并记录其中的最小值。但每次移位都统计一遍是不现实的，我们需要快速使用上一次的结果来得到这一次的结果。可以发现，由于每次都是把最后一个元素提到第一个元素，之前由它产生的逆序对会变成顺序对，而之前由它产生的顺序对会变成逆序对，对答案的贡献即为小于它的数的数量减去大于它的数的数量。而由于 $\{pos\}$ 也一定是 $1$ 到 $n$ 的排列，这一贡献便很好求出了。此外，我们直接从后往前枚举来找到每一次移位后的末位置即可，而不必真正模拟一遍。  

注意，由于可以选择其中一个进行移位，我们需要对两个数列分别做一次同样的计算。时间复杂度显然即为求逆序对的时间复杂度，$\operatorname{O}(n \log n)$。

## 代码
注意 `long long`！
```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int n,x,a[100001],b[100001],pos[100001],target[100001];
long long sum,ans,s[100001];
inline int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int value)
{
	for(int i=x;i<=n;i+=lowbit(i))
		s[i]+=value;
	return;
}
long long query(int x)
{
	long long result=0;
	for(int i=x;i;i-=lowbit(i))
		result+=s[i];
	return result;
}
long long solve(int *t1,int *t2)
{
	for(int i=1;i<=n;++i)
		pos[t1[i]]=i;
	for(int i=1;i<=n;++i)
		target[i]=pos[t2[i]];
	sum=0;
	memset(s,0,sizeof s);
	for(int i=n;i>0;--i)
	{
		sum+=query(target[i]);
		add(target[i],1);
	}
	ans=sum;
	for(int i=n;i>0;--i)
		ans=min(ans,sum-=n-(target[i]<<1)+1);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&b[i]);
	solve(a,b);
	solve(b,a);
	printf("%lld",min(solve(a,b),solve(b,a)));
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：1)

## 题目大意

给定两个长为 $N$ 的序列 $a,b$，这两个序列中 $[1,N]$ 有且仅有出现一次。可以对任意一个序列 $P$ 进行任意次操作：将 $P_N\leftarrow P_1$，同时对于每个 $2\le i\le N$ 将 $P_{i-1}\leftarrow P_i$。若将 $a,b$ 中相同的数字连线，则求出所有线段的最小交叉对数。

## 解题思路

以样例为例，先考虑怎么计算**不进行操作**时的交叉对数。首先一开始的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/l00bu7k6.png)

接着我们按照 $a$ 序列从左往右连线。首先连接 $5$ 可得

![](https://cdn.luogu.com.cn/upload/image_hosting/poheo2ga.png)

此时因为先前没有线段，所以当前连线对交叉数没有贡献。接着同样连接 $4$，也没有贡献。然后让我们看看连接 $1$ 后的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/wuyeg35u.png)

注意到，此时连接的线段和之前的两条线段都有相交，因此产生 $2$ 的贡献。为什么会这样？因为之前的 $5,4$ 在 $a$ 序列的位置在 $1$ 的左边，而在 $b$ 序列的位置却在 $1$ 的右边，因此肯定会有相交。最后我们将完整的图画出来，可以发现交叉数就是 $2+2+2=6$。于是可得，如果当前连接的数 $i$ 在 $b$ 序列中的位置为 $y_i$，那么当前这条线段所产生的贡献就是 $y_i$ **右边被连的点数**，然后我们就可以用**树状数组**维护这个“求逆序对”的过程。

接着我们想，如果把 $a$ 中的 $5$ 移到最右边会对答案有多少贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/j1600d4c.png)

可以发现，移动后线段 $5$ 和线段 $1,3,2$ 都失去了一个相交，而和线段 $4$ 相交，于是贡献就是 $-3+1=-2$。可以发现，如果当前移动的数 $i$ 在 $b$ 序列中的位置为 $y_i$，那么在 $y_i$ 左边的点都会和线段 $i$ 失去一个相交，而在右边的点都会多一个相交，**对答案的贡献即为** $-(y_i-1)+(n-y_i)=n+1-2y_i$。

于是我们就可以对 $a$ 中的每个数都移动，按照上面的公式计算出答案的最小值即可。要注意的是，$a$ 的移动与 $b$ 的移动**不等价**，所以需要对两个序列都进行移动并求值，时间复杂度 $O(N\log N)$，完结撒花ヾ(≧▽≦*)o！！！

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
#define lowbit(x) x&-x
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,x[100001],y[100001],p[100001],q[100001],res,ans1,ans2,ans,t[100001];
void add(ll x, ll y) {while(x<=n) t[x]+=y, x+=lowbit(x);}
ll find(ll x) {ll sum=0; while(x) sum+=t[x], x-=lowbit(x); return sum;}

int main()
{
    n=read();
    for(R int i=1; i<=n; ++i) x[i]=read(), p[x[i]]=i;
    for(R int i=1; i<=n; ++i) y[i]=read(), q[y[i]]=i;
    for(R int i=1; i<=n; ++i) res+=find(n)-find(q[x[i]]), add(q[x[i]],1);
    ans1=res; ans2=res; ans=res;

    for(R int i=1; i<=n; ++i)
    {
        ans1-=(p[y[i]]<<1)-n-1;
        ans2-=(q[x[i]]<<1)-n-1;
        ans=min(ans,min(ans1,ans2));
    }

    write(ans);
    return 0;
}
```

---

## 作者：2023lpx (赞：0)

## 题意

~~最难的其实是读懂题。~~

给两个序列，求对任意序列转动任意次后，两个序列相同元素连线后最少有多少对相交的线。

## 思路

设 $c_i$ 为 $a_i=j\ \land\  b_j=a_i$。

显然，求有多少对相交的线实质是求 $c$ 数组的逆序对数量。

现假设只移动 $a$ 数组（为什么自己脑补）。

可以发现每一次将 $a$ 数组向前移一位实质是将 $a_1$ 移到最后。

这个操作的实质是减掉 $c_i$ 的逆序对，在加上不是 $c_i$ 的逆序对的个数。

扫一遍即可得出答案。

注意：移动 $a$ 数组与移动 $b$ 数组并不等价，需要分别求。

## code

```cpp
#include<bits/stdc++.h>
using ll=long long;
using namespace std;
ll n;
ll const maxn=100000;
ll a[maxn+1];
ll b[maxn+1];
ll aa[maxn+1];
ll bb[maxn+1];
ll ans=maxn*maxn;
ll q[maxn+1];
ll t[maxn+1];
ll nxd;
void qsort(ll l,ll r){
	if(l==r){
		return;
	}
	ll mid=(l+r)>>1;
	qsort(l,mid);
	qsort(mid+1,r);
	ll i=l,j=mid+1,k=0;
	while(i<=mid&&j<=r){
		if(q[j]<q[i]){
			k++;
			t[k]=q[j];
			j++;
			nxd+=mid-i+1;
		}
		else{
			k++;
			t[k]=q[i];
			i++;
		}
	}
	while(i<=mid){
		k++;
		t[k]=q[i];
		i++;
	}
	while(j<=r){
		k++;
		t[k]=q[j];
		j++;
	}
	for(i=l,j=1;i<=r;i++,j++){
		q[i]=t[j];
	}
}
ll to[maxn+1];
void slove(ll *a,ll *b){
	for(ll i=1;i<=n;i++){
		to[a[i]]=i;
	}
	for(ll i=1;i<=n;i++){
		b[i]=q[i]=to[b[i]];
	}
	nxd=0;
	qsort(1,n);
	ans=min(ans,nxd);
	for(ll i=1;i<=n;i++){
		nxd+=n-b[i]-b[i]+1;
		ans=min(ans,nxd);
	}
}
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(ll i=1;i<=n;i++){
		scanf("%lld",&b[i]);
	}
	for(ll i=1;i<=n;i++){
		aa[i]=a[i];
		bb[i]=b[i];
	}
	slove(aa,bb);
	for(ll i=1;i<=n;i++){
		aa[i]=a[i];
		bb[i]=b[i];
	}
	slove(bb,aa);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Purslane (赞：0)

## Solution

> Why did the chicken cross the road ? To get to the other side .

这种类似于 " 过河 " 的问题 , 可以考虑将一遍的点对应在另一边的编号记录下来 , 就成了一个序列问题 .

设两个序列是 $\{a\}$ 和 $\{b\}$ , $\{a\}$ 元素对应编号为 $\{c\}$ .

如果两条线段有交点 , 也就是 $i>j$ 且 $c_i<c_j$ . 那么就相当于求 $\{c\}$ 中的逆序对 .

然后模拟平移操作 , 一个一个平移 . 考虑到每次平移是最前面的移到最后面 , 那么第一维的逆序显然满足 . 那么设平移时序列第一个数的值是 $p$ , 那会减少 $p-1$ 的数 , 但是增加 $n-p$ . 复杂度 $\text{O(n log n)}$ .

注意两个序列都可以平移 . 那么需要做两次 .

code :

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
struct BIT {
	int n;vector<int> tr;
	void init(int N) {tr.clear();return tr.resize(N+1),n=N,void();}
	int lowbit(int k) {return k&-k;}
	void update(int pos,int val) {while(pos<=n) tr[pos]+=val,pos+=lowbit(pos);return;}
	int Query(int pos) {int ans=0;while(pos) ans+=tr[pos],pos-=lowbit(pos);return ans;}
	int query(int l,int r) {return Query(r)-Query(l-1);}
}bit;
int n,ans=LONG_LONG_MAX,tmp,a[MAXN],b[MAXN],pos[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i];ffor(i,1,n) cin>>b[i];
	ffor(i,1,n) pos[b[i]]=i;
	bit.init(n);roff(i,n,1) tmp+=bit.Query(pos[a[i]]),bit.update(pos[a[i]],1);
	ans=tmp;
	ffor(i,1,n) {
		tmp-=pos[a[i]]-1,tmp+=n-pos[a[i]];
		ans=min(ans,tmp);
	}
	ffor(i,1,n) swap(a[i],b[i]);
	ffor(i,1,n) pos[b[i]]=i;
	tmp=0;
	bit.init(n);roff(i,n,1) tmp+=bit.Query(pos[a[i]]),bit.update(pos[a[i]],1);
	ans=min(ans,tmp);
	ffor(i,1,n) {
		tmp-=pos[a[i]]-1,tmp+=n-pos[a[i]];
		ans=min(ans,tmp);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：raincity (赞：0)

## 分析
很巧妙的转化题。

首先这道题的翻译非常生草，读一下英文题面，发现题目意思其实是：

给定两个 $1\sim n$ 的排列 $a$ 和 $b$，如果存在两个 $1\sim n$ 之间的整数 $x$ 和 $y$ 满足 $x$ 比 $y$ 在 $a$ 中早出现，在 $b$ 中晚出现，那么 $(x,y)$ 是一个交叉对。可以任意循环移动序列 $a$ 或 $b$（但是只可以移动一个序列），求交叉对数的最小值。

想了 30min 没思路，看了题解发现一个很妙的做法：

考虑移动 $a$。设 $p_i$ 是 $a_i$ 在 $b$ 中出现的位置，那么 $(a_i,a_j)(1\le i<j\le n)$ 是一个交叉对当且仅当 $p_i>p_j$。

然后转化成了一个逆序对问题。

考虑循环移动的问题。

把原来的 $a_n$ 移动到 $a_1$，会产生 $(p_n-1)-(n-p_n)=2p_n-n-1$，所以可以 $O(1)$ 进行移动。

给 $b$ 排序算出 $p$，树状数组或者归并排序求逆序对，然后枚举循环移动长度即可。

时间复杂度 $O(n\log n)$。

根据逆序对模板题的经验，归并排序常数方面吊打树状数组（不对啊，树状数组常数不应该很小吗）？

**注意开 long long**。

## 解决
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;
int n, a[N], b[N], p[N], tmp[N];
long long res, ans;
struct element {
	int val, id;
	bool operator <(const element &nxt) const { return val < nxt.val; }
}c[N];

void mergesort(int l, int r) {
	if (l == r)
		return;
	register int mid = (l + r) >> 1, i = l, j = mid + 1, k = l;
	mergesort(l, mid), mergesort(mid + 1, r);
	while (i <= mid && j <= r)
		if (p[i] <= p[j])
			tmp[k++] = p[i++];
		else
			res = res + mid - i + 1, tmp[k++] = p[j++];
	while (i <= mid) tmp[k++] = p[i++];
	while (j <= r) tmp[k++] = p[j++];
	for (register int i = l; i <= r; i++) p[i] = tmp[i];
}

inline void read(int &ret) {
	ret = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
}

int main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1; i <= n; i++) read(c[i].val), c[i].id = i, b[i] = c[i].val;
	sort(c + 1, c + n + 1);
	for (int i = 1; i <= n; i++) p[i] = c[a[i]].id;
	mergesort(1, n);
	ans = res;
	for (int i = 1; i <= n; i++) p[i] = c[a[i]].id;
	for (int i = n; i > 1; i--) {
		res = res + p[i] + p[i] - n - 1;
		if (res < ans)
			ans = res;
	}
	res = 0;
	for (int i = 1; i <= n; i++) c[i].val = a[i], a[i] = b[i], c[i].id = i;
	sort(c + 1, c + n + 1);
	mergesort(1, n);
	for (int i = 1; i <= n; i++) p[i] = c[a[i]].id;
	ans = min(ans, res);
	for (int i = 1; i <= n; i++) p[i] = c[a[i]].id;
	for (int i = n; i > 1; i--) {
		res = res + p[i] + p[i] - n - 1;
		if (res < ans)
			ans = res;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：liuhongyang123 (赞：0)

# 题意

给两个序列，求转动若干次任意序列后，两个序列相同元素连线后**最少有**多少对相交的线。

# 解法

设，这两个数组分别为 $a$ 数组和 $b$ 数组，$x$ 元素在 $b$ 数组里第 $B_i$ 位，$y$ 元素在 $a$ 数组里第 $A_i$ 位。

我们考虑每次向前旋转 $a$ 数组一位所产生的贡献，不妨令当前答案为 $ans$。

模拟一下样例就可以发现旋转后的答案为 $ans-(n-B_{a_i})+(B_{a_i}-1)$，减去原来的贡献，加上现在的贡献。

每次向前旋转 $b$ 数组同上（$ans-(n-A_{b_i})+(A_{b_i}-1)$）。

所以只需要求出原始的方案答案就可以 $O(n)$ 求出答案了。

至于原始的方案，就从 $1$ 到 $n$ 依次连边，然后把后面的已经连了边的点的个数加到答案中，这里我用的是树状数组。

最后输出所有方案的最小值即可。

# Code

结合代码，跟好理解。

```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(g) g&(-g)
using namespace std;
const int MAXN=1e5+10;
int n,m,aa[MAXN],bb[MAXN],B[MAXN],A[MAXN],tree[MAXN],minn,ans,Ans;
//树状数组
void update(int id){
	while(id<=n) ++tree[id],id+=lowbit(id);
} 
int query(int id){
	int Ans=0;
	while(id) Ans+=tree[id],id-=lowbit(id);
	return Ans;
}
//----------------------------------------------
void ycl(int a[],int b[]){//处理原始答案
	ans=0;
	for(int i=1;i<=n;i++) tree[i]=0;
	for(int i=1;i<=n;i++) ans+=query(n)-query(b[a[i]]),update(b[a[i]]);
	minn=ans;
}
int work(int a[],int b[]){//枚举方案
	ycl(a,b);
	for(int i=n;i>=2;i--){//枚举把谁转到最后一个
		ans-=(n-b[a[i]]),ans+=b[a[i]]-1;//公式
		minn=min(ans,minn);//记录最小
	}
	return minn;
}
signed main(){
	freopen("mincross.in","r",stdin);
	freopen("mincross.out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&aa[i]),A[aa[i]]=i;
	for(int i=1;i<=n;i++) scanf("%lld",&B[i]),bb[B[i]]=i;
	printf("%lld",min(work(aa,bb),work(B,A)));
	return 0;
}

```

---

