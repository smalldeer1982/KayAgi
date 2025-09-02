# Enemy is weak

## 题目描述

The Romans have attacked again. This time they are much more than the Persians but Shapur is ready to defeat them. He says: "A lion is never afraid of a hundred sheep".

Nevertheless Shapur has to find weaknesses in the Roman army to defeat them. So he gives the army a weakness number.

In Shapur's opinion the weakness of an army is equal to the number of triplets $ i,j,k $ such that $ i&lt;j&lt;k $ and $ a_{i}&gt;a_{j}&gt;a_{k} $ where $ a_{x} $ is the power of man standing at position $ x $ . The Roman army has one special trait — powers of all the people in it are distinct.

Help Shapur find out how weak the Romans are.

## 样例 #1

### 输入

```
3
3 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 3 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
10 8 3 1
```

### 输出

```
4
```

## 样例 #4

### 输入

```
4
1 5 4 3
```

### 输出

```
1
```

# 题解

## 作者：George1123 (赞：13)

[$\Huge\texttt{In Cnblogs}$](https://www.cnblogs.com/Wendigo/p/12812951.html)

---
> [Enemy is weak](https://www.luogu.com.cn/problem/CF61E)

> 求序列 $a\{n\}$ 中的三元逆序对数量。

> 数据范围：$3\le n\le 1e6$。

---
这题真是一道又好又水的题，可是我看别人的题解做法真是玄学难懂，于是蒟蒻要写一篇简单易懂的。

---
考虑到**二元逆序对**的做法：**离散化后动态维护一个权值树状数组。**

其中对于每个当做逆序对后一元的 $i$，当做逆序对前一元的 $j(j<i,a_j>a_i)$ 的贡献为 $1$，$i$ 为总答案的贡献为 $s_i=\sum_{j=1}^{i-1}[a_j>a_i]$。

其实求**三元逆序对**同样可以**离散化后动态维护一个权值树状数组。**

其中对于每个当做逆序对后一元的 $i$，当做逆序对前一元的 $j(j<i,a_j>a_i)$ 的贡献为 $s_j$，$i$ 为总答案的贡献为 $S_i=\sum_{j=1}^{i-1}[a_j>a_i]s_j$。

所以总共维护**两个权值树状数组**即可。

---
**空间复杂度 $\Theta(n)$，时间复杂度 $\Theta(n\log n)$。**

---
小蒟蒻讲不清楚，小蒟蒻还是太蒻了 $/kk$。小蒟蒻放个代码吧，记得树状数组要开 $\texttt{long long}$：

```cpp
//Data
const int N=1e6;
int n,a[N+7],b[N+7];
lng ans;

//Bittree
typedef vector<lng> bit;
bit c1(N+7),c2(N+7);
void add(bit&c,int x,lng y){for(;x<=n;x+=x&-x) c[x]+=y;}
lng sum(bit&c,int x){lng res=0;for(;x;x-=x&-x) res+=c[x];return res;}
lng sum(bit&c,int x,int y){return sum(c,y)-sum(c,x-1);}

//Main
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	for(int i=1;i<=n;i++) ans+=sum(c2,a[i]+1,n),add(c2,a[i],sum(c1,a[i]+1,n)),add(c1,a[i],1);
	printf("%lld\n",ans);
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：jdsb (赞：4)

## 题意
- 给定一个$n$个数的序列，求出满足$i<j<k$ 且 $a_i>a_j>a_k$ 的三元组 $(i,j,k)$ 的数量。
- $1\le n \le 10^6,1\le a_i \le 10^9$

## 分析
- 首先我们可以将 $a_i$ 取反，即将题目转化成求三元上升子序列的数量。我们可以用动态规划来解决这道问题。首先设 $f[i][j]$ 表示以 第$j$ 个数结尾的长度为 $i$ 的子序列数量。转移方程为 $f[i][j]=\sum\limits_{k=1}^{i-1}f[i-1][k]\ (a_j>a_k)$，表示将第 $j$ 个数接到第 $k$ 个数后面，且子序列长度加 $1$，最后答案即为$\sum_{i=1}^{n} f[3][i]$。这个总的时间复杂度为 $O(n^2)$。
- 考虑用树状数组进行优化，每次直接将 $f[i][j]$ 的值存在下标为 $a_j$ 的地方，每次修改时直接查询 $a_j-1$ 的前缀和即可。这样就满足了 $i<j$ 且 $a_i<a_j$ 的条件。因为$a_i$ 的值域很大，考虑离散化，最后即可通过此题。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return x*f;
}
const int N=1e6+5;
int n;
ll a[N],b[N],f[4][N],tr[N],ans;
void add(int x,ll v)
{
	while(x<=n)
	{
		tr[x]+=v;
		x+=x&-x;
	}
}
ll query(int x)
{
	ll s=0;
	while(x)
	{
		s+=tr[x];
		x-=x&-x;
	}
	return s;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=-read(),b[i]=a[i];
	sort(b+1,b+n+1);
	int len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=1;i<=n;i++) f[1][i]=1;
	for(int i=2;i<=3;i++)
	{
		memset(tr,0,sizeof(tr));
		for(int j=1;j<=n;j++)
		{
			f[i][j]=query(a[j]-1);
			add(a[j],f[i-1][j]);
		}
	}
	for(int i=1;i<=n;i++) ans+=f[3][i];
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：peterwuyihong (赞：3)

题意：给一个序列，求有多少 $i<j<k,a_i>a_j>a_k$。

对每个位置，求它前面有多少个大于它的数与后面有多少小于它的数，乘起来，就是以这个点为中间的大三元（雾，把所有大三元加起来即可。

现在是 $10:50$，我看我什么时候写完。

现在是 $10:56$，我写完了。

```cpp
#define maxn 1000010
int n;
int a[maxn],b[maxn],cnt;
int c[maxn];
void add(int x,int y){
	for(;x<=cnt;x+=x&-x)c[x]+=y;
}
int ask(int x){
	int ans=0;
	for(;x;x-=x&-x)ans+=c[x];
	return ans;
}
int up[maxn],down[maxn];
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	cnt=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	for(int i=1;i<=n;i++){
		up[i]=ask(cnt)-ask(a[i]);
		add(a[i],1);
	}
	memset(c,0,sizeof c);
	for(int i=n;i;i--){
		down[i]=ask(a[i]-1);
		add(a[i],1);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)ans+=(long long)up[i]*down[i];
	cout<<ans;
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
其实实现不够精细，注意到我一共用了三个 $\text{ask}$，但是可以写反向树状数组做到只用两个 $\text{ask}$ 的，离散化也写的不大优美，可以写一个常数更小的用 $\text{struct}$ 实现的离散化，但是跑 $10^6$ 的数据还是绰绰有余了。

---

## 作者：LJC00118 (赞：2)

这题看起来是个原题

先离散化一波

我们枚举 $ j $，用两个树状数组分别维护左边有几个数比它大，右边有几个数比它小即可

```cpp
#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 1e6 + 5;

struct fenwick {
    int f[N], n;

    inline int lowbit(int x) { return x & -x; }

    void add(int x, int y) {
        for(register int i = x; i <= n; i += lowbit(i))
            f[i] += y;
    }

    int query(int x) {
        int ans = 0;
        for(register int i = x; i; i -= lowbit(i))
            ans += f[i];
        return ans;
    }
} tr[2];

int a[N], b[N], n;
ll ans;

int main() {
    read(n); tr[0].n = tr[1].n = n;
    for(register int i = 1; i <= n; i++) read(a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    for(register int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
    for(register int i = 2; i <= n; i++) tr[1].add(a[i], 1);
    for(register int i = 2; i <= n; i++) {
        tr[0].add(a[i - 1], 1);
        tr[1].add(a[i], -1);
        ans += 1ll * tr[1].query(a[i] - 1) * (i - 1 - tr[0].query(a[i]));
    }
    print(ans, '\n');
    return 0;
}
```

---

## 作者：阔睡王子 (赞：1)

求解三元逆序对，对于 $i<j<k , a_i>a_j>a_k$ ，枚举 $a_j$ 然后用两次树状数组求出 $a_i$ 与 $a_k$ 的数量，利用乘法原理求出对答案的贡献，建议切掉[逆序对](https://www.luogu.com.cn/problem/P1908)与[三元上升子序列](https://www.luogu.com.cn/problem/P1637)之后来做。

```记得开longlong```

```
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define int long long
using namespace std;
int n;
int c[1000010],m[1000010],L[1000010],R[1000010];
struct node
{
	int loc,val;
}a[1000010];
bool cmp1(node x,node y)
{
	return x.val<y.val;
}
bool cmp2(node x,node y)
{
	return x.loc<y.loc;
}
int seach(int k)
{
	int cnt=0;
	while(k>0)
	{
		cnt+=c[k];
		k-=k&(-k);
	}
	return cnt;
}
void putin(int k)
{
	while(k<=n)
	{
		c[k]++;
		k+=k&(-k);
	}
}
main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[n-i+1].val);
		a[n-i+1].loc=n-i+1;
	}
	sort(a+1,a+n+1,cmp1);
	int num=0,past=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].val!=past)
		{
			past=a[i].val;
			a[i].val=++num;
		}
		if(a[i].val==past)
		{
			past=a[i].val;
			a[i].val=num;
		}
	}
	sort(a+1,a+n+1,cmp2);
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=seach(a[i].val)-m[a[i].val];
		L[i]=ans;
		m[a[i].val]++;
		putin(a[i].val);
	}
	for(int i=1;i<=n;i++)
	{
		m[i]=0;
		c[i]=0;
	}
	for(int i=n;i>=1;i--)
	{
		ans=seach(a[i].val)-m[a[i].val];
		R[i]=(n-i)-ans-m[a[i].val];
		m[a[i].val]++;
		putin(a[i].val);
	}
	ans=0;
	for(int i=1;i<=n;i++)
	ans+=L[i]*R[i];
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：星空舞涵 (赞：1)

我看题解都是树状数组，所以发一篇归并来造福人类

### 此题题意有问题

## 题意：

给定  $n~(3\leq n\leq 10^6)$ 个数的序列  $a$  $(a_i \leq 10^9)$，问满足  $i<j<k$ 且  $a_i>a_j>a_k$ 的三元组  $(i,j,k)$ 数目。

~~从讨论区粘的~~

## 分析：
很显然我们对于第$i$个数我们只需要求出从$1$到$i-1$中有多少个数比他大，从$i-1$到$n$中有多少个数比他小就可以了。


求$i+1$到$n$中有多少个数比$i$大很简单，就是求逆序对嘛，把归并排序稍微改一下就行了。

对于求$1$到$i-1$中有多少个数有多少个数比他大，我们可以把数组中的所有数乘以$-1$，这样就转换成了求$1$到$i-1$中有多少个数比他小了，然后我们再把数组的顺序前后置换一下，再求一次逆序对就阔以了。

### 注意：
翻转以后，第$i$个数转换成了第$n-i+1$个数，所以第二次求逆序对时第$n-i+1$个数的逆序对的数量实际上是，原数组中在$1$到$i-1$中比第$i$个数大的数的个数


```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,a[1000001],ni[1000001],anss[1000001];long long  n;
struct cxk{
	int zhi,xv;
}e[1000001];
cxk ee[1000001];
void guibing(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)/2;
	guibing(l,mid);
	guibing(mid+1,r);
	int i=l;
	int j=mid+1;
	int k=l;
	ans=0;
	while(i<=mid&&j<=r)
	{
		if(e[i].zhi<=e[j].zhi)
		{
			ee[k].zhi=e[i].zhi;
			ee[k].xv=e[i].xv;
			ni[e[i].xv]=ni[e[i].xv]+ans;
			k++;
			i++;
		}
		else 
		{
			ee[k].zhi=e[j].zhi;
			ee[k].xv=e[j].xv;
			ans++;
			k++;
			j++;
		}
	}
	while(i<=mid)
	{
		ee[k].zhi=e[i].zhi;
		ee[k].xv=e[i].xv;
		ni[e[i].xv]=ni[e[i].xv]+ans;
		k++;
		i++;
	}
	while(j<=r)
	{
		ee[k].zhi=e[j].zhi;
		ee[k].xv=e[j].xv;
		k++;
		j++;
	}
	for(int i=l;i<=r;i++)
	{
		e[i].zhi=ee[i].zhi;
		e[i].xv=ee[i].xv;
	 } 
}
int main()
{
	
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		e[i].zhi=a[i];
		e[i].xv=i;
	}
	guibing(1,n);
	for(int i=1;i<=n;i++)
	{
		anss[i]=ni[i];
	}
	memset(ni,0,sizeof(ni));
	for(int i=1;i<=n;i++)
	{
		e[n-i+1].zhi=-1*a[i];
		e[n-i+1].xv=i;
	}
	guibing(1,n);
	ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=anss[i]*ni[i]+ans;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：qiyue7 (赞：1)

写个应该是最简单的做法，离线转在线降维操作，我们考虑传统二重逆序对中，每一位的贡献应该是（左边比这个位置的数大的个数） + （右边比这个位置的数小的个数），三重逆序对则应该是（左边比这个位置的数大的个数） * （右边比这个位置的数小的个数）（乘法原理）  如果我们用平衡树在线模拟那么就不用离散化直接写个小模拟就可以直接得到答案了。
以下为用pb_ds的AC代码：
```cpp
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
#include <ext/rope>
using namespace __gnu_cxx;
#include<bits/stdc++.h>
using namespace std;
tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update> bbt;
long long W1[1100000],W2[1100000],b[1100000];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,L=1;
    memset(W1,0,sizeof(W1));
    memset(W2,0,sizeof(W2));
    long long sum=0;
    cin>>n;
    cin>>b[1];
    bbt.insert({b[1],1});
    for(int i=2;i<=n;++i)
    {
        cin>>b[i];
        W1[i]=(i-bbt.order_of_key({b[i]+1,0})-1);
        bbt.insert({b[i],i});
    }
    bbt.clear();
    bbt.insert({b[n],1});
    L=2;
     for(int i=n-1;i>=2;--i)
    {
        W2[i]=(bbt.order_of_key({b[i],0}));
        bbt.insert({b[i],++L});
    }
    for(int i=1;i<=n;++i)
        {
            //cout<<W1[i]<<" "<<W2[i]<<endl;
            sum+=W1[i]*W2[i];
        }
    cout<<sum<<endl;
    return 0;
}

```



---

## 作者：rEdWhitE_uMbrElla (赞：1)

这题就是求三重逆序对...

用树状数组求出每个位置左边有几个比它大，右边有几个比它小，最后乘起来就好惹。。

我也不知到这道题是怎么紫的。。

```cpp
#include<bits/stdc++.h>
#define S second
#define F first
using namespace std;

typedef long long ll;
const int N = 1e6+5;

pair<int, int> a[N];
ll xyz[N];
int arr[N],BIT[N];

int getSum(int index){
	int ret = 0;
	while(index > 0){
		ret += BIT[index];
		index -= index & (-index);
	}
	return ret;
}

void update(int index, int n){
	while(index <= n){
		BIT[index] ++;
		index += index & (-index);
	}
}

int main(){
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	for(int i = 1; i <= n; ++i) a[i].S = i,cin >> a[i].F;
	sort(a+1, a+n+1);
	for(int i = 1; i <= n; ++i) arr[a[i].S] = i;
	for(int i = n; i > 0; --i){
		xyz[i] = getSum(arr[i]-1);
		update(arr[i], n);
	}
	memset(BIT, 0, sizeof BIT);
	for(int i = 1; i <= n; ++i){
		xyz[i] *= (getSum(n) - getSum(arr[i]));
		update(arr[i], n);
	}
	ll ans = 0;
	for(int i = 1; i <= n; ++i){
		ans += xyz[i];
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：年华天地 (赞：0)

这道题非常的好做，~~不愧是水黑题~~。
首先，一看是三个数，我们可以转化成一个数的答案的贡献，就是中间这个数，我们可以算出每一个数它左边有多少个比他大的数以及它右边有多少个比他小的数，再根据乘法原理乘起来就是这个数对于答案的贡献了。那么怎么算一个数右边有多少个比它大的个数呢？我们可以先离散化，在用树状数组计算，具体来说就是一个个的把数加进去，并且边加边询问。

代码（我是倒着算的，把数组倒过来，算它左边比它小的，右边比它大的）

细节看注释吧。

```
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1e6+10000;
long long n,a[maxn],tree[maxn],mi[maxn],ma[maxn],b[maxn],c[maxn],top=0,d[maxn];
long long ans[maxn],anss,ans1[maxn];
int cmp(int a,int b)
{
	return a<b;
}
void add(int x,int y)
{
	if (x==0)x=1;
	int p=x;
	while (p<=n)
	{
		tree[p]+=y;
		p+=p&-p;
	}
}
int ask(int x,int cnt)
{
	int p=x;
	while(p>0)
	{
		cnt+=tree[p];
		p-=p&-p;
	}
	return cnt;
}
void ls()//离散化
{
	sort(b+1,b+n+1,cmp);
	for (int i=1;i<=n;i++)
		if (b[i]!=b[i-1])
			c[++top]=b[i];
	for (int i=1;i<=n;i++)
	{
		int p=lower_bound(c+1,c+top+1,a[i])-c;
		a[i]=p;
	}
}
void nxd()右边大的
{
	for(int i=1;i<=n;i++)
		d[i]=top-a[i]+1;
	for (int i=1;i<=n;i++)
		b[i]=d[n-i+1];
	for (int i=1;i<=n;i++)
	{
		ans[n-i+1]=ask(b[i],0);
		add(b[i]+1,1);
	}
}
void qxd()//左边小的
{
	for (int i=1;i<=n;i++)
	{
		ans1[i]=ask(a[i],0);
		add(a[i]+1,1);//注意要+1
	}
}
int main()
{
	scanf("%lld",&n);
	for (int i=n;i>=1;i--)
	{
		scanf("%lld",&a[i]);
		b[i]=a[i];
	}
	ls();
	for (int i=1;i<=n;i++)
		b[i]=a[n-i+1];
	nxd();
	memset(tree,0,sizeof(tree));
	qxd();
	for (int i=1;i<=n;i++)
		anss+=(long long)ans[i]*ans1[i];
	printf("%lld",anss);
	return 0;
}
```


---

## 作者：NuoCarter (赞：0)

这篇题的意思很简单？

就是三元逆序对的个数：

众所周知，利用一些简单的知识，珂以得出一个简单的结论：

每一个数的三元逆序对个数=左边比它大的数 * 右边比它小的个数

因为这道题的范围 $n \leq 10^6$,且$a_i \leq 10^9$

所以单纯的值域树状数组无法开下 $a_i$ 那么大的空间，

这个简单，简简单单离散化即可：

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll c1[1000005],c2[1000005],ans1[1000005],ans2[1000005],a[1000005];
ll tmp[1000005];
int la[1000005];
inline bool cmp(int x,int y){return x>y;}
inline int lowbit(int x){return x&(-x);}
inline void add1(int x,ll d){while(x<=n){c1[x]+=d;x+=lowbit(x);}return;}
inline ll query1(int x){ll res=0;while(x){res+=c1[x];x-=lowbit(x);}return res;}
inline void add2(int x,ll d){while(x<=n){c2[x]+=d;x+=lowbit(x);}return;}
inline ll query2(int x){ll res=0;while(x){res+=c2[x];x-=lowbit(x);}return res;}
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;++i){
    scanf("%lld",&a[i]);
    tmp[i]=a[i];
  }
  sort(tmp+1,tmp+n+1);
  int len=unique(tmp+1,tmp+n+1)-(tmp+1);
  for(int i=1;i<=n;++i){la[i]=lower_bound(tmp+1,tmp+len+1,a[i])-tmp;}
  for(int i=n;i>=1;--i){
    ans1[i]=query1(la[i]-1);
    add1(la[i],1);
  }
  for(int i=1;i<=n;++i){
    ans2[i]=query2(n)-query2(la[i]);
    add2(la[i],1);
  }
  ll resu=0;
  for(int i=1;i<=n;++i){
    resu+=ans1[i]*ans2[i];
  }
  printf("%lld\n",resu);
  return 0;
}

```

---

## 作者：cirnovsky (赞：0)

## 题意简述

求三元逆序对数量。

## 题解

参考求二元逆序对的过程，将统计结果的加法改为乘法即可。

~~真的就这么点东西不要说我说明过少啊~~

```cpp
#include <bits/stdc++.h>

const int N = 1e6 + 5;
int n, bit[N], rnk[N];
long long ans, apr[N];
struct st{
	int id, val;
	friend bool operator < (st x, st y) {
		if (x.val == y.val) return x.id < y.id;
		else return x.val < y.val;
	}
} a[N];

void add(int x, int y) {
	for (; x <= n; x += x & -x)
		bit[x] += y;
}

int ask(int x) {
	int res = 0;
	for (; x; x -= x & -x)
		res += bit[x];
	return res;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i].val), a[i].id = i;
	std::sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++i) rnk[a[i].id] = i;
	for (int i = n; i >= 1; --i) apr[i] = ask(rnk[i] - 1), add(rnk[i], 1);
	for (int i = 1; i <= n; ++i) bit[i] = 0;
	for (int i = 1; i <= n; ++i) ans += apr[i] *= (ask(n) - ask(rnk[i])), add(rnk[i], 1);
	return printf("%lld\n", ans) & 0;
}
```

---

## 作者：YinyuDream (赞：0)

# 题解：

本题是在数列$a_i$中，求满足$i<j<k$且$a_i>a_j>a_k$的三元组的个数。对于本题，我们可以枚举三元组的中间位置$i$，在其左边求得比他小的数的数的数量$a_i$，在其右边求得比他大的数的数量$b_i$，则最终答案为 $\sum_{i=1}^na_ib_i$。具体地，我们可以用权值树状数组维护出$1-i$的数字出现的数量，我们从左往右遍历，对于数$a_i$，我们首先查询小于$a_i$的数的数量，并在树状数组中更新该数字。按照同样的方法可以求出$c_i$。本题数据较大，需注意离散化。

# 代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e6+10;
int n;
long long ans;
int a[maxn],l[maxn],r[maxn],tree[maxn],b[maxn];
void lsh()
{
	for(int i=1;i<=n;i++)
		b[i]=a[i];
	sort(b+1,b+n+1);
	int m=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)
	a[i]=lower_bound(b+1,b+m+1,a[i])-b;
}
inline int lowbit(int x)
{
	return x&-x;
}
void update(int x,int val)
{
	for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;
}
int query(int x)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))ans+=tree[i];
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	lsh();
	for(int i=1;i<=n;i++)
	l[i]=(query(n)-query(a[i])),update(a[i],1);
	memset(tree,0,sizeof tree);
	for(int i=n;i>=1;i--)
	r[i]=query(a[i]-1),update(a[i],1);
	for(int i=1;i<=n;i++)
		ans+=1ll*l[i]*r[i];
	printf("%lld",ans);
	return 0;
}
```


---

