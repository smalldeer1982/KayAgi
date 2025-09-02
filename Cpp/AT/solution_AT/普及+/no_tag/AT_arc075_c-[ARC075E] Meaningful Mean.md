# [ARC075E] Meaningful Mean

## 题目描述

**题目大意：**
给一个长度为N的整数序列{a},对于其一共N*(N+1)/2个的非空区间，求有多少个区间的平均数大于等于K。

## 说明/提示

输入的全部为整数

1 ≤ N ≤ 2×10^5

1 ≤ K ≤ 10^9

1 ≤ a[i] ≤ 10^9

## 样例 #1

### 输入

```
3 6
7
5
7```

### 输出

```
5```

## 样例 #2

### 输入

```
1 2
1```

### 输出

```
0```

## 样例 #3

### 输入

```
7 26
10
20
30
40
30
20
10```

### 输出

```
13```

# 题解

## 作者：NinT_W (赞：5)

# [ARC075E] Meaningful Mean

## 杂项

[传送门](https://www.luogu.com.cn/problem/AT_arc075_c)

## 思路

给你好几个数，然后对于这个序列的所有区间，让你求其平均值大于等于k的区间个数

先用前缀和预处理一下，对于某个区间[l,r]的平均值为$\frac{sum_r-sum_{l-1}}{r-l+1}\geq k$

$sum_r-sum_{l-1}\geq k\times(r-l+1)$,我们可以通过一些操作使k变成零(输入$a_i$时都减去k就好啦)，可以得到$sum_r-sum_{l-1}\geq 0$,即$sum_r\geq sum_{l-1}$,然后就变成了二维偏序（数点），用树状数组处理即可

还有就是sum数组要进行离散化 预处理时要记得把l=1时的贡献统计进去（树状数组会统计不到)

AC code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#define int long long

using namespace std;

const int maxn=2e5+5;

inline int read()
{
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}

int n,k,ans;
int a[maxn];
int sum[maxn];
int cop[maxn];
int tree[maxn];

int lowbit(int x){ return x&-x; }

void update(int x,int y)
{
	for(;x<=n;x+=lowbit(x))
	{
		tree[x]+=y;
	}
}

int query(int x)
{
	int ans=0;
	for(;x;x-=lowbit(x))
	{
		ans+=tree[x];
	}
	return ans;
}

signed main()
{
	n=read();
	k=read();
	
	for(int i=1;i<=n;i++)
	{
		a[i]=read()-k;
	}
	
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i];
		cop[i]=sum[i-1]+a[i];
		if(sum[i]>=0) ans++;
	}
	
	sort(cop+1,cop+n+1);
	int num=unique(cop+1,cop+n+1)-cop-1;
	for(int i=1;i<=n;i++)
	{
		sum[i]=lower_bound(cop+1,cop+n+1,sum[i])-cop;
	}
	for(int i=1;i<=n;i++)
	{
		ans+=query(sum[i]);
		update(sum[i],1);
	}
	
	cout<<ans;
	
	return 0;
}
```


---

## 作者：qinmingze (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/AT_arc075_c)

## 思路

- 题目要求的是在数列中有多少个区间的和的平均数大于等于 $m$ 。所以我们可以先**将数列的每一个数都将去一个 $m$**，并**计算减去 $m$ 之后数列的前缀和**存在 $a$ 数组里。

- 这时，我们就不难发现 当 $j \ge i$ 时，且保证 $a_j \ge a_i$ 时，那么这个序列的平均数就一定大于等于 $m$。也就是**求前缀和数组 $a$ 的顺序对**。

- 确定完题目所求之后，我们需要确定算法，这时我们不难想到用**归并排序求逆序对**，而本题所求的是顺序对，所以我们只需要**将前者大时更新答案改成前者小于等于时更新答案**，就可以成功地输出顺序对的个数了。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

long long a[N], b[N], ans;

void merge(int p, int q){
	if(p >= q)return ;//如果当前左端点大于等于右端点，跳出循环
	int mid = p + q >> 1;
	merge(p, mid); merge(mid + 1, q);//遍历左半部分和右半部分
	int l = p, r = mid + 1, cnt = l;
	while(l <= mid && r <= q){
		if(a[l] <= a[r]){//当小于等于时更新答案
			b[cnt++] = a[r++];
			ans = ans + mid - l + 1;
		}else b[cnt++] = a[l++];
	}
	while(l <= mid)b[cnt++] = a[l++];//左半部分更改
	while(r <= q)b[cnt++] = a[r++];//右半部分更改
	for(int i = p; i <= q; i++)a[i] = b[i];//更新数组
}

int main(){
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		a[i] = a[i - 1] + a[i] - k;//保存前缀和
	}
	merge(0, n);
	cout << ans << endl;
}
```

---

## 作者：tzc_wk (赞：4)

> ### AT2581

> 题意：给出一个数列 $a$，求有多少个子区间平均值 $\geq k$

> $1 \leq n \leq 2 \times 10^5$

很显然可以将子区间转化为前缀和相减，记前缀和为 $sum$，那么算术平均值不超过 $k$ 就可以变为

$$\frac{sum_r-sum_{l-1}}{r-l+1} \geq k$$

进一步转化为

$$k \times (r-l+1) \leq sum_r-sum_{l-1}$$

即

$$sum_r - r \times k \geq sum_{l-1} - (l-1) \times k$$

令 ${sum'}_x=sum_x-x \times k$，离散化了之后二维数点就可以了。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),k=read(),ans=0,a[200005],sum[200005],key[200005],hs[200005],cnt=0;
int bit[200005];
inline void add(int x,int v){
	for(int i=x;i<=200000;i+=(i&(-i)))
		bit[i]+=v;
}
inline int query(int x){
	if(x==0)	return 0;
	int sum=0;
	for(int i=x;i;i-=(i&(-i)))
		sum+=bit[i];
	return sum;
}
signed main(){
	key[0]=-0x3f3f3f3f;
	fz(i,1,n)	a[i]=read();
	fz(i,1,n)	sum[i]=sum[i-1]+a[i];
	fz(i,1,n)	sum[i]-=k*i,key[i]=sum[i];
	sort(key+1,key+n+1);
	fz(i,1,n+1){
		if(key[i]!=key[i-1]){
			hs[++cnt]=key[i];
		}
	}
	add(lower_bound(hs+1,hs+cnt+1,0)-hs,1);
	fz(i,1,n){
//		cout<<sum[i]<<endl;
		int ind=lower_bound(hs+1,hs+cnt+1,sum[i])-hs;
		ans+=query(ind);
		add(ind,1);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：2c_s (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc075_c)

## 思路

这道题题目中要求求出区间平均数大于 $K$ 的区间，于是我们可以通过求顺序对并计算个数来实现。

**求顺序对：** 输入完成后进行[归并排序](https://oi.wiki/basic/merge-sort/)。排序时，每次找到一个 $a_i \le a_j$ 的一对数时，存储结果的 $ans$ 变量就加上一个当前区间 $[l,r]$ 的中间数 $mid$，再减去 $i$ 并 $+1$（这是因为当前位置要再算一遍）。归并排序后输出 $ans$ 即可。


- 别忘开 long long。

## AC 代码

- 这里的 $l,r$ 分别对应上文中的 $i,j$。

- 这里的 $le,ri$ 分别对应上文中的 $l,r$。

- 这里的 $m$ 对应上文中的 $K$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
long long n,m,a[N],tmp[N],l,r,ans,cnt;
void msort(int le,int ri){
	if(le>=ri)return ;
	int mid=(le+ri)>>1;
	msort(le,mid);
	msort(mid+1,ri);
	l=le,r=mid+1,cnt=l;
	while(l<=mid&&r<=ri){
		if(a[l]<=a[r]){
			tmp[cnt++]=a[r++];//注意下标与普通的归并不同。
			ans+=mid-l+1;
		}
		else tmp[cnt++]=a[l++];
	}
	while(l<=mid)tmp[cnt++]=a[l++];
	while(r<=ri)tmp[cnt++]=a[r++];
	for(int i=le;i<=ri;++i)a[i]=tmp[i];
	return ;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
		a[i]+=a[i-1]-m;
	}
	msort(0,n);
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/112637734)

---

## 作者：旋转卡壳 (赞：2)

用sum[i]代表a序列的[1,i]的和

对于一个区间(l,r] 只有当(sum[r]-sum[l])/(r-l)>=k时才对答案有贡献

转换一下就是 sum[r]-rk>=sum[l]-lk

再转换一下 在读入a[i]的时候减去k 那就变成了sum[r]>=sum[l]

所以用树状数组 枚举r 看它前面有多少个l符合要求

然后因为区间是左开右闭的 [1,i]这样的区间没有考虑到 一开始直接算就完事了 

还有一点细节就是sum可能太大了 离散化一下就行了 具体的看代码吧

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn=2e5+50;

int n,k,N,r[maxn];
ll ans,a[maxn],sum[maxn];

inline int read(int x=0,char c=getchar()) {
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}

ll c[maxn];

inline void add(int x,int v){for(;x<=N;x+=x&-x)c[x]+=v;}
inline int ask(int x){int y=0;for(;x;x-=x&-x)y+=c[x];return y;}

int main() {
	n=read();k=read();
	for(register int i=1;i<=n;++i) a[i]=read()-k; //转换为区间和大于等于0 
	for(register int i=1;i<=n;++i) if((sum[i]=(a[i]+=a[i-1]))>=0) ++ans;
	//处理前缀和的同时把区间左端点为1的情况直接算了 
	sort(sum+1,sum+1+n); N=unique(sum+1,sum+1+n)-sum-1; //不同前缀和的个数 
	for(register int i=1;i<=n;++i) r[i]=lower_bound(sum+1,sum+1+N,a[i])-sum; //离散化 
	for(register int i=1;i<=n;++i) ans+=ask(r[i]),add(r[i],1);
	//枚举右端点 看有多少个左端点满足要求 
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：_JF_ (赞：1)

## [ARC075E] Meaningful Mean 

好题。

首先显然有一个暴力做法，也就是 $O(n^2)$ 的，考虑暴力枚举每一个区间，查询区间和显然可以考虑预处理前缀和。判断一下这个和是否大于等于 $k$ 即可。

核心的一行是：

```cpp
if(s[i]-s[j-1]>=k*(i-j+1))
```
然后考虑把这个式子拆开。

$$k \times i-k \times(j-1)\le s_i-s_{j-1}$$

$$  s_{j-1}-k\times (j-1)\le s_i-k \times i$$

显然我们可以预处理 $1\le i\le n$ 的所有 $i$，所以就变成了在 $1\le j < i$ 中找小于等于 $s_i -k\times i$ 的值。显然可以用一个树状数组去维护，类似于求逆序对，开一个值域大小的树状数组，按照逆序对的求法来就好了。

注意，当 $j=1$ 时，$j-1$ 为 $0$，在 $1\le i\le n$ 的预处理中是处理不到的，所以我们要把第一个位置留出来给 $0$，后面整体挪一个位置即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long	
int n,k;
struct node
{
	int val,num;
}a[N];
bool cmp(node a,node b)
{
	if(a.val==b.val)
		return a.num<b.num;
	return a.val<b.val;
}
int ranks[N],c[N],s[N];
int lowbit(int x)
{
	return x&-x;
}
void update(int x,int change)
{
	for(int i=x;i<=n+1;i+=lowbit(i))
		c[i]+=change;
}
int Query(int x)
{
	int sum=0;
	for(int i=x;i>0;i-=lowbit(i))
		sum+=c[i];
	return sum;
}
signed main()
{
	cin>>n>>k;
	for(int i=1,x;i<=n;i++)
		cin>>x,s[i]=s[i-1]+x;
	a[1].val=0,a[1].num=1;
	for(int i=2;i<=n+1;i++)
		a[i].val=s[i-1]-k*(i-1),a[i].num=i;
	sort(a+1,a+n+2,cmp);
	for(int i=0;i<=n+1;i++)	
		ranks[a[i].num]=i;
	int ans=0;
	for(int i=1;i<=n+1;i++)
		ans+=Query(ranks[i]),update(ranks[i],1);
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：SoyTony (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT2581)

[前排广告](https://www.luogu.com.cn/blog/Tony-ZhuJialiang/)

题意：求一个数列 $A$ 中平均数大于等于 $K$ 的连续子序列个数。

不难想到的是，本题可以维护一个前缀和，而 $n$ 的范围是 $n\le 2\times {10}^5$ 的，不能直接对前缀和暴力处理，先将平均数的式子写下，对于区间 $[l,r]$ 来说，平均数大于等于 $K$ 满足：
$$sum_r-sum_{l-1}\ge (r-l+1)\times K$$
移项也就有：
$$sum_r-r\times K\ge sum_{l-1}-(l-1)\times K$$
不能发现左右两边分别是关于 $r$ 和 $l-1$ 的一个式子且完全相同，不妨设 $b_i=sum_i-i\times K$，接下来我们只需要找到所有 $b_i\le b_j\ (0\le i<j\le n)$，因为前缀和可能取 $sum_0$，所以我们的范围是包含 $0$ 的。

观察这个条件，发现和求逆序对很相似。只需要将归并排序中“如果前者更大就更新答案”，改为“如果前者更小或相等就更新答案”，之后输出这样“顺序对”的个数即可。

```cpp
int n;
ll ans;
ll a[maxm],b[maxm],p;
inline void msort(int l,int r){
	if(l==r) return;
    int mid=(l+r)>>1;
    msort(l,mid);
    msort(mid+1,r);
    int i=l,j=mid+1,k=i;
    while(i<=mid&&j<=r){
        if(a[i]>a[j]){
            b[k++]=a[i++];
        }
        else{
            b[k++]=a[j++];
            ans+=mid-i+1;
        }
    }
    while(i<=mid){
        b[k++]=a[i++];
    }
    while(j<=r){
        b[k++]=a[j++];
    }
    for(i=l;i<=r;i++){
        a[i]=b[i];
    }
}
int main(){
    n=read(),p=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        a[i]+=a[i-1]-p;
    }
    msort(0,n);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Iam1789 (赞：1)

之前发现有句话表述不清，管理大大给重过一下谢谢qwq

将所有的 $a_i$ 都变为 $a_i-k$，则 $\frac{\sum_{i=l}^ra_i}{r-l+1}$ 即变为 $\frac{\sum_{i=l}^ra_i}{r-l+1}-k$。

那么问题就转变为了对于数列 $b_i=a_i-k$，有多少段的平均值即和 $\geq0$。

对数列 $b$ 做前缀和，$\sum_{i=l}^rb_i\geq0$ 等价于 $\text{sum}_r-\text{sum}_{l-1} \geq 0$。

以 $r$ 为结尾的符合要求的区间数即为 $0$ 到 $r-1$ 之间小于等于
$\text{sum}_r$ 的 $\text{sum}$ 个数。

对 $\text{sum}$ 进行离散化，开一个桶记录前 $i$ 个数中小于等于该数的数的数量。用树状数组或者线段树维护即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
int num[200007];
long long sum[200007];
long long jl[200007];
map <long long,int> p;
struct Tree{
	struct nodee{
		int l,r,num,lazy;
	}a[1600007];
	void build(int x,int l,int r)
	{
		a[x].l=l;
		a[x].r=r;
		if(l==r)
		return;
		int mid=(l+r)/2;
		int lc=x*2,rc=x*2+1;
		build(lc,l,mid);
		build(rc,mid+1,r);
		a[x].num=a[lc].num+a[rc].num;
	}
	inline void pushdown(int x)
	{
		int lc=x*2,rc=x*2+1;
		a[lc].lazy+=a[x].lazy;
		a[rc].lazy+=a[x].lazy;
		a[lc].num+=a[x].lazy*(a[lc].r-a[lc].l+1);
		a[rc].num+=a[x].lazy*(a[rc].r-a[rc].l+1);
		a[x].lazy=0;
	}
	inline void Add(int x,int l,int r,int k)
	{
		pushdown(x);
		if(l<=a[x].l&&a[x].r<=r)
		{
			a[x].lazy+=k;
			a[x].num+=k*(a[x].r-a[x].l+1);
			return;
		}
		int lc=x*2,rc=x*2+1;
		if(l<=a[lc].r)
		Add(lc,l,r,k);
		if(r>=a[rc].l)
		Add(rc,l,r,k);
		a[x].num=a[lc].num+a[rc].num;
	}
	inline int Sum(int x,int l,int r)
	{
		pushdown(x);
		if(l<=a[x].l&&a[x].r<=r)
		return a[x].num;
		int lc=x*2,rc=x*2+1,ans=0;
		if(l<=a[lc].r)
		ans+=Sum(lc,l,r);
		if(r>=a[rc].l)
		ans+=Sum(rc,l,r);
		return ans;
	}
}Tre;
long long ans=0;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
	scanf("%d",&num[i]),num[i]-=k,sum[i]=sum[i-1]+num[i],jl[i]=sum[i];
	jl[n+1]=0;
	sort(jl+1,jl+n+2);
	int maxn=unique(jl+1,jl+n+2)-jl-1;
	for(int i=1;i<=maxn;++i)
	p[jl[i]]=i;
	for(int i=1;i<=n;++i)
	num[i]=p[sum[i]];
	Tre.build(1,1,maxn);
	Tre.Add(1,p[0],maxn,1);
	for(int i=1;i<=n;++i)
	{
		ans+=Tre.Sum(1,num[i],num[i]);
		Tre.Add(1,num[i],maxn,1);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：rhyyy1 (赞：1)

CDQ分治的板子题。

目标求区间的平均数大于等于 $K$ 的个数，按照惯例，同时减去 $K$，即求区间和非负的个数。

具体思路：

CDQ分治做法，设现在统计的区间为 $\left[l,r\right]$ ,分治统计出 $\left[l,mid\right],\left[mid+1,r\right]$ 区间中的答案个数，其中 $mid=(l+r)/2$。

接下来主要的问题就是如何计算一个区间 $\left[l,r\right]$ 内的答案个数。

注意此处统计的答案区间必须经过 $mid$。

以 $mid$ 为中心分别向两边做后缀和与前缀和。

将两边分别从小到大排序，两指针的方式统计出合法的答案数。

$i$ 指针指向 $mid+1$，$j$ 指针指向 $mid$。$j$ 向左扫，$i$ 向右扫。

具体实现见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+50;
ll a[N],s[N],ans;
void cdq(int l,int r){
	if(l==r){
		if(a[l]>=0) ans++;
		return ;
	}
	int mid=(l+r)>>1;
	cdq(l,mid); cdq(mid+1,r);
	s[mid]=a[mid];
	for(int i=mid-1;i>=l;i--) s[i]=s[i+1]+a[i];
	s[mid+1]=a[mid+1];
	for(int i=mid+2;i<=r;i++) s[i]=s[i-1]+a[i];
	sort(s+l,s+mid+1);
	sort(s+mid+1,s+r+1);
	int j=mid;
	for(int i=mid+1;i<=r;i++){
		while(s[i]+s[j]>=0&&j>=l) j--;
		ans+=mid-j;
	}
}
int main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]-=m;
	cdq(1,n);
	printf("%lld\n",ans);
}
```



~~码风还行，凑合着看吧。~~

---

## 作者：Krimson (赞：1)

对于以$r$为右端点的区间,只要满足$\sum^{r}_{i=l} a_i>=(r-l+1)k$就满足了区间平均数大于k  
也就是说满足$a_r>(r-l+1)k-\sum^{r-1}_{i=l} a_i$  
于是转而去维护$(r-l+1)k-\sum^{r-1}_{i=l} a_i$  
每次新加入一个元素都相当于给所有元素加上一个$k-a_r$,并加入一个新元素$k$  
比如当维护到2的时候,有
$$
2k-a_1\\
k
$$   
而加入一个2之后就变成了  
$$
3k-a_1-a_2  \\
2k-a_2 \\
k
$$  
于是把每次加上的$k-a_r$作为类似线段树的lazytag一样,(以下称为$sum$)  
每次加入的时候就直接加入$k-sum$,而查询的时候直接查询小于$a_r-sum$的就可以了  
关于维护这个东西的方法有很多,这里讲两种比较暴力的方法  

1.vector  
关于查询,只要upper_bound就可以了,而插入可以选择upper_bound找到插入位置之后insert  
insert的复杂度是$O(\frac{n}{w})$,所以整体复杂度是$O(\frac{n^2}{w})$,如果是1e5能卡过,但2e5似乎有些困难~~开O2能过~~  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
vector<ll> s;
int n;
ll k;
ll a,sum,ans;
int main(){
	// freopen("rand.in","r",stdin);
	// freopen("2.out","w",stdout);
    n=read(),k=read();
    s.push_back(k);
    sum=0;
    for(ri i=1;i<=n;++i){
        a=read();
        ans+=upper_bound(s.begin(),s.end(),a-sum)-s.begin();
        sum+=k-a;
        s.insert(upper_bound(s.begin(),s.end(),k-sum),k-sum);
    }
    print(ans);
	// printf("%lf",clock()/1000.0);
    return 0;
}
```


2.平衡树  
单点插入,查找rank,都是平衡树能维护的最基本的东西  
复杂度$O(nlogn)$  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
int n;
ll k;
const int MAXN=4e5+7;
ll a,sum,ans;
struct FHQ
{
    int cnt=0;
    struct T{
        ll val,key;
        int l,r,size;
    }tree[MAXN];
    void update(int tmp){
        tree[tmp].size=tree[tree[tmp].l].size+tree[tree[tmp].r].size+1;
    }
    void split(int now,int k,int &l,int &r){
        if(!now){
            l=r=0;
            return;
        }
        if(tree[now].val<=k){
            l=now;
            split(tree[now].r,k,tree[now].r,r);
        }
        if(tree[now].val>k){
            r=now;
            split(tree[now].l,k,l,tree[now].l);
        }
        update(now);
    }
    int add(int val){
        tree[++cnt].val=val,tree[cnt].l=tree[cnt].r=0,tree[cnt].size=1,tree[cnt].key=rand();
        return cnt;
    }
    int merge(int l,int r){
        if(!l||!r) return l+r;
        if(tree[l].key>tree[r].key){
            tree[l].r=merge(tree[l].r,r);
            update(l);
            return l;
        }
        else{
            tree[r].l=merge(l,tree[r].l);
            update(r);
            return r;
        }
    }
    int kth(int now,int k){
        if(tree[tree[now].l].size+1==k) return now;
        if(tree[tree[now].l].size+1>k) return kth(tree[now].l,k);
        return kth(tree[now].r,k-tree[tree[now].l].size-1);
    }
    int root=0,l=0,r=0,p=0;
    void insert(ll x){
        split(root,x,l,r);
        p=add(x);
        root=merge(merge(l,p),r);
    }
    il ll bound(ll x){
        ll ans=0;
        split(root,x,l,r);
        ans=tree[l].size;
        root=merge(l,r);
        return ans;
    }
}s;
int main(){
    n=read(),k=read();
    s.insert(k);
    for(ri i=1;i<=n;++i){
        a=read();
        ans+=s.bound(a-sum);
        sum+=k-a;
        s.insert(k-sum);
    }
    print(ans);
    return 0;
}
```


---

## 作者：DarkMoon_Dragon (赞：1)

# $AT2581$ `Meaningful Mean`
来自@Wen_kr大爷的题目推荐
## 题意
+ 给定一串长度为 $n$ 的数列，询问有多少个区间的算数平均数大于等于 $K$.
+ $n \leq 2* 10^5, K,a_i\leq 10^9$

## $Solution$
+ 这种题一般都考虑推一下式子
+ 区间和转化为前缀和
+ 对于区间$(l,r)$，转化成前缀和
+ $$\frac{sum[r]-sum[l-1]}{r-l+1}\geq K$$
+ $$sum[r]-sum[l-1]\geq(r-l+1)\times K$$
+ 原式等价于
+ $$sum[r]-K\times r\geq sum[l-1]-(l-1)\times K$$
+ 化简思路？寻找通项，或者说左右移项搞一搞
+ 问题转化成了$C[i]=sum[i]-K\times i$前面比后面小于等于的对数
+ 树状数组离散化搞搞，或者归并搞搞即可
+ 注意这里并不是逆序对，所以理论上来说树状数组瞎搞好做一些
+ $yy$一遍顺序对过了（其实可以总对数减去逆序对个数）

```cpp

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#define rr int
using namespace std;
typedef long long ll;
ll read() {
    char i = getchar();
    ll f = 1, res = 0;
    while (i < '0' || i > '9') {
        if (i == '-') f = -1;
        i = getchar();
    }
    while (i >= '0' && i <= '9') {
        res = res * 10 + i - '0';
        i = getchar();
    }
    return f * res;
}
int n;
ll K;
const int N = 3e5 + 50;
ll a[N];
ll sum[N], c[N];
ll ans = 0;
inline void merge(int l, int r) {
    if (l < r) {
        int mid = (l + r) >> 1;
        merge(l, mid);
        merge(mid + 1, r);
        int i = l, j = mid + 1, now = l;
        while (i <= mid && j <= r) {
            if (a[i] <= a[j]) {
                c[now++] = a[i++];
                ans += r - j + 1; //这里注意不能重复计算，每次取得取单独更新贡献
            } else
                c[now++] = a[j++];
        }
        while (i <= mid) c[now++] = a[i++];
        while (j <= r) c[now++] = a[j++];
        for (rr i = l; i <= r; ++i) a[i] = c[i];
    }
}
int main() {
    n = read() + 1, K = read();
    for (rr i = 2; i <= n; ++i) {
        a[i] = read();
        sum[i] = sum[i - 1] + a[i];
        a[i] = sum[i] - K * ll(i - 1);
    }
    // for (rr i = 1; i <= n; ++i) cout << a[i] << ' ';
    merge(1, n);
    // for (rr i = 1; i <= n; ++i) cout << a[i] << endl;
    cout << ans;
}


```

---

## 作者：Mortidesperatslav (赞：0)

本题我们可以想出，我们把每一个 $a_i$ 减去 $K$，然后平均数大于等于 $0$ 的区间数量就是答案。

那么我们怎么求区间平均数呢？我们可以推出，当 $[1,n]$ 的区间和大于 $[1,m]$ 的区间和，并且 $n>m$，那么 $[m,n]$ 的区间和一定不小于 $0$。

我们可以用反证法证明：假设 $[m,n]$ 区间和 $<0$，那么 $[1,m]$ 的区间和就是 $[1,n]$ 的区间和减去 $[m,n]$ 的区间和，由于 $[m,n]$ 的区间和 $<0$，$[1,m]$ 的区间和一定大于 $[1,n]$ 的区间和，所以上述推论成立。

因此，我们可以采用归并排序统计正序对。

顺带介绍下归并排序：归并排序是把一个数列拆分再合并，时间复杂度 $O(n\log_2n)$，有一种优化叫 Timsort，被认为是“世界上最快的排序”，另有一种基于队列和线段树的排序也是这个时间复杂度，但未得到广泛认可。

代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long tmp[500005],a[500005],b[500005];
long long ans=0;
void msort(int l,int r){//归并模板，参考《信息学奥赛一本通》
	if(l==r)return;
	register int m=(l+r)/2,i=l,j=m+1,k=l;
	msort(l,m),msort(m+1,r);//递归调用
	while(i<=m&&j<=r)
		if(a[i]>a[j])b[k++]=a[i++];
		else b[k++]=a[j++],ans=(ans+m-i+1);//求正序对个数
	while(i<=m)b[k++]=a[i++];
	while(j<=r)b[k++]=a[j++];
	for(register int ii=l;ii<=r;ii++)a[ii]=b[ii];
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	long long n,k;
	cin>>n>>k;
	for(register int i=1;i<=n;i++){
		cin>>tmp[i];
		tmp[i]-=k;
	}
	a[1]=tmp[1];
	for(register int i=2;i<=n;i++)a[i]=a[i-1]+tmp[i];//a数组记录前缀和
	msort(0,n);
	cout<<ans;
}
```

再推荐几道逆序对的题：

[P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

[P1774 最接近神的人](https://www.luogu.com.cn/problem/P1774)

[P2717 寒假作业](https://www.luogu.com.cn/problem/P2717)

[P2804 神秘数字](https://www.luogu.com.cn/problem/P2804)

[P7868 VUDU](https://www.luogu.com.cn/problem/P7868)

管理员辛苦了，求管理过审~

---

## 作者：geven (赞：0)

# [ARC075E] Meaningful Mean 题解
## 题意
给一个长度为 $N$ 的整数序列 ${a}$，对于其一共 $\frac{N\times (N+1)}{2}$ 个的非空区间，求有多少个区间的平均数大于等于 $k$。
## 暴力做法
显然，可以直接枚举区间左端点 $j$ 与区间右端点 $i$，检查区间平均值是否大于等于 $k$ 即可，用代码实现即为：

```cpp
for(int i=1;i<=n;i++){
	for(int j=1;j<=i;j++){
		if(sum[i]-sum[j-1]>=k*(i-j+1)){//乘法避免丢精度
			ans++;
		}
	}
}
```
用前缀和数组 $sum$ 优化，时间复杂度为 $O(n^2)$。显然，对于 $2 \times 10^5$ 的数据，该程序会超时。
## 正解
只要对暴力算法的不等式稍加改变，我们就能得到正解。

对于代码中的不等式，我们可以将不等式转化为：$sum_i - k \times i - k \geq sum_{j-1} - k \times j$。 

再结合 $j \leq i$，就显然可以看出公式可以用树状数组优化。

对于每一个 $i$，我们都将 $sum_{j-1} - k \times j$ 插入进树状数组中，再将树状数组中小于等于 $sum_i - k \times i - k$ 的元素个数查询并累加，就可以得到最终答案。

时间复杂度为 $O(n \log n)$。

__注意__：由于不等式中的左右两项可能很大，所以在操作前需要先对其离散化。
## 代码
```cpp
#include<stdio.h>
#include<algorithm>
typedef long long ll;
const ll N=1e6+5;
int n,cnt;
ll k,sum[N],a[N],b[N],p[N],c[N];
int lowbit(int x){return x&~x+1;}
void add(int x,ll v){while(x<=cnt) c[x]+=v,x+=lowbit(x);}
ll query(int x){
	ll ans=0;
	while(x) ans+=c[x],x-=lowbit(x);
	return ans;
}
int main(){
	scanf("%d%lld",&n,&k);
	ll x;
	for(int i=1;i<=n;i++){
		scanf("%lld",&x);
		sum[i]=sum[i-1]+x;
		a[i]=sum[i]-k-k*i;//不等式左边项
		b[i]=sum[i-1]-k*i;//不等式右边项
		p[++cnt]=a[i],p[++cnt]=b[i];
	}
	std::sort(p+1,p+cnt+1);//离散化排序
	cnt=std::unique(p+1,p+cnt+1)-p-1;
	ll ans=0;
	for(int i=1;i<=n;i++){
		int x=std::lower_bound(p+1,p+cnt+1,a[i])-p;
		int y=std::lower_bound(p+1,p+cnt+1,b[i])-p;//离散化
		add(y,1);
		ans+=query(x);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：STUDYING0601 (赞：0)

**看了一眼发现还没有用平衡树的题解，于是自己写一篇。**

~~也是蒟蒻的第一篇题解~~

------
### AT2581


首先思考将每一个 $a_i$ 都写成 $k+b_i$ 的形式，那么一个长度为 $len$ 的区间的平均数 $x$ 为

$$x=\frac{len\times k+\sum b_i}{len}=k+\frac{\sum b_i}{len}$$

若 $\sum b_i\ge0$，则此区间平均数 $x\ge k$，所以我们将每一个 $a_i$ 都减去 $k$ 后，再考虑有多少子区间的和大于等于 $0$，这样就避免了区间长度的影响。

既然是区间和，不难想到做一遍前缀和，在前缀和数组上寻找差大于等于 $0$ 的两点。

那我们枚举每一个左端点，在右边计算大于等于左端点的值的数量。

既然枚举是 $O(n)$ 的，那我们想到可不可以使用一些数据结构在 $\log{n}$ 的时间内完成一次计算，在一个数组中找到大于等于一个值的数的数量。

嗯，我们想到有一个叫做平衡树的东西,（不会的同学可以转去P3396）似乎可以找到一个值在序列中的排名。真是不错。

我们从第 $n$ 个位置往回遍历，记 $sum$ 为 $b_i$ 的前缀和数组。对于位置 $i$，
我们将 $sum_i$ 丢进平衡树中，同时计算大于等于 $sum_{i-1}$ 的值的数量，并加进答案中。单次插入与查询都是 $O(\log{n})$ 的。所以总复杂度为 $O(n\log{n})$。

这里我用的是 `FHQ`，注意要开 `long long` 哦。
                            
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int Mx=2e5+5;
int n,k,a[Mx],s[Mx];
int val[Mx],key[Mx],tot=0,ls[Mx],rs[Mx],siz[Mx],root;
//以下为FHQ
void push_up(int p){siz[p]=siz[ls[p]]+siz[rs[p]]+1;}
int add(int w){
    ++tot;val[tot]=w;key[tot]=rand();siz[tot]=1;
    return tot;
}
//加点
void spl(int p,int v,int &x,int &y){
    if(!p)return x=y=0,void();
    if(val[p]<=v)spl(rs[p],v,rs[x=p],y);
    else spl(ls[p],v,x,ls[y=p]);
    push_up(p);
}
//分裂
int mer(int x,int y){
    if(!x||!y)return x|y;
    if(key[x]<key[y])return ls[y]=mer(x,ls[y]),push_up(y),y;
    else return rs[x]=mer(rs[x],y),push_up(x),x;
}
//合并
void insert(int v){
    int x=0,y=0;
    spl(root,v-1,x,y);
    root=mer(mer(x,add(v)),y);
}
//插入
int query_val(int v){
    int x=0,y=0,ans;
    spl(root,v-1,x,y);
    ans=siz[y];
    root=mer(x,y);
    return ans;
}
//查询比v大的值的数量
//以上为FHQ
signed main(){
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[i]-=k;
    for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
    int ans=0;
    for(int i=n;i>=1;i--){
        insert(s[i]);
        int res=query_val(s[i-1]);
        ans+=res;
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Yansuan_HCl (赞：0)

可以把 $a$ 的每个数减去 $k$，那么*平均值大于 $k$* 就可以转化为**和 $\ge 0$**，也就是前缀和 $s[i]-s[j]\ge 0(i>j)$。

做前缀和，用树状数组数出有多少个 $s[j]\le s[i](i>j)$ 即可。

值域很大，可以用 `unordered_map` 作为树状数组。时间复杂度 $O(n \log V)$，$V$ 为值域。常数较大，但可以通过。

```cpp
const int N = 200005;
const ll B = 2e14 + 5, V = B << 1; // +B 避免负数。
int n; ll k, a[N];
unordered_map<ll, int> tr;
ll lowbit(ll x) { return x & -x; }
void add(ll p, int v) { while (p <= V) tr[p] += v, p += lowbit(p); }
int access(ll p) { auto it = tr.find(p); return (it == tr.end()) ? 0 : it->second; }
int query(ll p) { ll v = 0; while (p) v += access(p), p ^= lowbit(p); return v; }

int main() {
    rd(n, k);
    U (i, 1, n) rd(a[i]), a[i] -= k, a[i] += a[i - 1];
    ll ans = 0;
    U (i, 1, n) {
        add(a[i - 1] + B, 1);
        ans += query(a[i] + B);
    }
    printf("%lld", ans);
    return 0;
}
```

---

