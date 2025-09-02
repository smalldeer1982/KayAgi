# Petya and Array

## 题目描述

Petya 有一个包含 $n$ 个整数的数组 $a$。他最近学会了前缀和，现在可以非常快速地计算数组中任意一段连续区间的元素和。区间指的是数组中一段连续的非空元素序列。

现在他想知道，数组中有多少个区间的元素和小于 $t$。请你帮助 Petya 计算这个数量。

更正式地说，你需要计算有多少对 $l, r$（$l \le r$）满足 $a_l + a_{l+1} + \dots + a_{r-1} + a_r < t$。

## 说明/提示

在第一个样例中，以下区间的元素和小于 $4$：

- $[2, 2]$，元素和为 $-1$
- $[2, 3]$，元素和为 $2$
- $[3, 3]$，元素和为 $3$
- $[4, 5]$，元素和为 $3$
- $[5, 5]$，元素和为 $-1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 4
5 -1 3 4 -1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 0
-1 2 -3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
4 -1
-2 1 -2 3
```

### 输出

```
3
```

# 题解

## 作者：PanH (赞：15)

emm...虽然已经有权值线段树做法了，但这种做法其实是不用离散化的，因为权值线段树可以动态开点。对于线段树的操作也只要 $insert$ 和 $query$ 就可以了。

或许我的代码会更简洁一点？（雾）。

- 由于存在负数，线段树处理不了，于是可以加上一个很大的数 $(1e15)$ 。

具体操作看代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
const int MAXN=1e7+5,N=2e5+5,G=1e15;
int tree[MAXN],lson[MAXN],rson[MAXN],tot,n,t,a[N],rt,ans;
#define mid (l+r>>1)
inline void make(int &k){if(!k)	k=++tot;}
void insert(int l,int r,int &k,int x)
{
	make(k);
	if(l==r)	return tree[k]++,void();
	if(x<=mid)	insert(l,mid,lson[k],x);
	else	insert(mid+1,r,rson[k],x);
	tree[k]=tree[lson[k]]+tree[rson[k]];
}
int query(int l,int r,int k,int x,int y)
{
	if(l>=x&&r<=y)	return tree[k];
	int res=0;
	if(x<=mid)	res+=query(l,mid,lson[k],x,y);
	if(y>mid)	res+=query(mid+1,r,rson[k],x,y);
	return res;
}
#undef mid
signed main()
{
	read(n),read(t);
	for(int i=1;i<=n;i++)	read(a[i]),a[i]+=a[i-1];
	for(int i=n;i;i--)	insert(1,G<<1,rt,a[i]+G),ans+=query(1,G<<1,rt,1,a[i-1]+t+G-1);//插入以i为右端点的前缀和，求出以i为左端点有多少区间。
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：_byta (赞：12)

萌新初学 cdq 分治，发一篇题解加深一下印象。

题目要求区间和小于 t 的区间数量，首先肯定想到预处理前缀和，接下来我们考虑

分治，分治区间为 0 到 n，类似于归并排序，在分治过程中我们先分治 l 到 mid，

再分治 $mid+1$ 到 r，最后我们处理跨越区间的问题。对于跨区间我们用队列

维护答案，若答案大于 t，队头指针加加，最后整个队列队总答案的贡献即为队列

长度。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int L,R,ans,s[210000];
void cdq(int l,int r)
{
    if(l==r)return ;
    int mid=(l+r)/2;
    cdq(l,mid),cdq(mid+1,r);
    int head=l,tail=mid;
    for(int i=mid+1;i<=r;i++)
    {
        //while(tail+1<=mid && s[i]>=s[tail+1]+L)tail++;
        while(head<=mid && s[i]>=s[head]+R)head++;
        ans+=tail-head+1;
    }
    sort(s+l,s+r+1);
}//cdq分治
signed main()
{
    int n;
    scanf("%lld%lld",&n,&R);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%lld",&x);
        s[i]=s[i-1]+x;
    }
    cdq(0,n);
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：little_sun (赞：10)

# 题解 CF1042D 【Petya and Array】

这道题其实要求的就是$$\sum^n_{r=1}\sum^{r-1}_{l=1}\sum^r_{i=l}a[i] < t$$
的$(l,r)$对数量

时间复杂度$O(n^3)$

可以用前缀和优化到$O(n^2)$

可是还是无法AC

怎么办呢？

我们可以这样：

* 由于$|t|\leq10^{14}$，所以离散化

* 扫一遍$1-n$，对于每个i,使用树状数组统计前面的有多少个位置满足$sum[j-1]\leq sum[i]-t$的，将$i-cnt$计入答案

* 将$sum[i]$加入树状数组

注意：开始时要把$0$扔进树状数组！！！（原因：$sum[0]=0$）

**Code:**

```cpp
#include <bits/stdc++.h>

#define lowbit(x) (x & (-x))

const int MaxN = 200010;

int n;
int cnt;
long long t;
int c[MaxN << 2];
long long a[MaxN], s[MaxN];
std::map<long long, int>m;

int query(int x)
{
    int ans = 0;
    while(x)
        ans += c[x], x -= lowbit(x);
    return ans;
}

void add(int x, int val)
{
    while(x <= cnt)
        c[x] += val, x += lowbit(x);
}

int main()
{
    scanf("%d%lld", &n, &t);
    m[0] = 1;
    for(int i = 1; i <= n; i++)
        scanf("%lld", &a[i]), s[i] = s[i - 1] + a[i], m[s[i] - t] = m[s[i]] = 1;//前缀和
    for(std::map<long long, int>::iterator it = m.begin(); it != m.end(); it++)
        it -> second = ++cnt;//离散化
    long long ans = 0;
    add(m[0], 1);
    for(int i = 1; i <= n; i++)
    {
        ans += i - query(m[s[i] - t]);//计入答案
        add(m[s[i]], 1);//更新
    }  
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：CreeperLordVader (赞：8)

### 居然没有权值线段树解法！！！

那我来一个

本题细节真的巨多，思路1分钟，代码5小时。。。

首先，为了能$O(1)$求出区间和，我们对原序列前缀和并记为序列$a$

然后考虑题设限制

求有多少个区间$[l,r]$满足$sum(l,r)<t$

由于前缀和的存在,$sum(l,r)=a(r)-a(l-1)<t$

### 于是变成了$a(r)<a(l-1)+t$

### 于是可以扫描一遍$a$,在每个前缀$l$处我们只需求出有多少数$r$满足上式

可以用权值线段树来维护,只需求出$a(l-1)+t$的排名即可,对应到线段树上就是求出区间和

由于求的前缀不包括l-1自身,所以还要在进入下一个前缀前删除下一个前缀

因为数很大,需要离散化,具体实现略微复杂

我最开始的时候右儿子打成左儿子,调了一小时,后来离散化以后没开long long又花了几小时...

```cpp
#include<bits/stdc++.h>
#define ll long long
#define update(o) sz[o]=sz[o<<1]+sz[o<<1|1]
using namespace std;
const int MAXN=200005;
ll val[200005];
int cnt[200005];
int n,m;;
ll ans;
ll pref;
ll t,a[200005];
ll num[200005];
int id[200005];
int sz[MAXN<<2];
map<ll,int>times;
template<typename type>
void read(type& x)
{
    char c=getchar();
    int f=1;x=0;
    while(c<'0'||c>'9')
    {
        if(c=='-')f*=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    x*=f;
}
void build(int o,int l,int r)
{
    if(l==r)
    {
        sz[o]=cnt[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    update(o);
}
int query(int o,int l,int r,int k)
{
    if(!k)return 0;
    if(r<=k)
    {
        return sz[o];
    }
    int mid=(l+r)>>1,sum=0;
    sum+=query(o<<1,l,mid,k);
    if(k>mid)sum+=query(o<<1|1,mid+1,r,k);
    return sum;
}
void remove(int o,int l,int r,int k)
{
    if(l==r)
    {
        sz[o]--;
        return ;
    }
    int mid=(l+r)>>1;
    if(k<=mid)remove(o<<1,l,mid,k);
    else remove(o<<1|1,mid+1,r,k);
    update(o);
}
int main()
{
    read(n);
    read(t);
    for(int i=1;i<=n;i++)
    {
        read(num[i]);
        a[i]=a[i-1]+num[i];
        times[a[i]]++;
    }
    sort(a+1,a+n+1);
    m=unique(a+1,a+n+1)-a-1;
    for(int i=0;i<m;i++)
    {
        val[i+1]=a[i+1];
        cnt[i+1]=times[a[i+1]];
    }
    build(1,1,m);
    for(int i=0;i<n;i++)
    {
        pref+=num[i];
        int k=lower_bound(val+1,val+m+1,pref+t-1)-val;
        if(k>m)k=m;
        if(val[k]>=pref+t)k--;
        if(k)ans+=(ll)query(1,1,m,k);
        int p=lower_bound(val+1,val+m+1,pref+num[i+1])-val;
        remove(1,1,m,p);
    }
    printf("%lld\n",ans);
}
```


---

## 作者：Kevin_James (赞：5)

本人的第一篇题解，若有不妥的地方请指出。

提供一种不用离散化的做法。

看到连续的区间 $[l,r]$ ，可以考虑前缀和，将题目所给式子变形为：
 $sum(r)-sum(l-1) < t$

于是有： $sum(l-1)>sum(r)-t$

其等价为 $sum(l) \geq\ sum(r)-t+1$ 的形式。

我们可以采用动态开点的方法，将 $sum$ 的数值插入权值线段树中，于是问题变成扫描到一个点 $r$ 时进行单点加一操作，并对其前面的所有 $sum$ 值进行区间查询，即查询下标为 $[1,r)$ ，值域为 $[sum(r)-t+1,inf]$ 的区间和。

注意此处的差可能为负数，所以需要加上一个较大的数，根据题目条件， $\Delta$ 可取 $2e14$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

const long long M=2e14;

int n,newp,sum[10000005],ls[10000005],rs[10000005],rt;
long long a[200005],t,ans;

void pushup(int k){
	sum[k]=sum[ls[k]]+sum[rs[k]];
}

void doUpdate(int &k,long long l,long long r,long long x){
	if(!k) k=++newp;
	if(l==r){
		sum[k]++;
		return ;
	}
	long long mid=(l+r)>>1;
	if(x<=mid) doUpdate(ls[k],l,mid,x);
	else doUpdate(rs[k],mid+1,r,x);
	pushup(k);
}

long long doQuery(int k,long long L,long long R,long long l,long long r){ 
    if(l<=L&&R<=r) return sum[k];
    if(L>r||R<l) return 0;
    long long mid=(L+R)>>1;
    return doQuery(ls[k],L,mid,l,r)+doQuery(rs[k],mid+1,R,l,r);
}

int main(){
	scanf("%d%lld",&n,&t);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) a[i]+=a[i-1];
	for(int i=1;i<=n;i++){
	    doUpdate(rt,0,M<<1,a[i-1]+M); 
		ans=ans+doQuery(rt,0,M<<1,a[i]-t+1+M,M<<1);
	}
	printf("%lld\n",ans);
	return 0;
}
```




---

## 作者：5k_sync_closer (赞：4)

比较典的一个题。

经验题：[P2717](https://www.luogu.com.cn/problem/P2717) [P5459](https://www.luogu.com.cn/problem/P5459)

题意：给定 $\{a_n\},t$，求 $\sum\limits_{l=1}^n\sum\limits_{r=l}^n[\sum\limits_{i=l}^ra_i<t]$。
# 思路
令 $s_x=\sum\limits_{i=1}^xa_i$，则原式等于 $\sum\limits_{l=1}^n\sum\limits_{r=l}^n[s_r-s_{l-1}<t]$。

考虑枚举 $r$，统计 $l-1<r\bigwedge s_{l-1}>s_r-t$ 的 $l-1$ 的个数。

发现是个二维偏序，用权值树状数组维护之，复杂度 $O(n\log n)$。
# 代码
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define F(x) v[m++] = x
#define H(x) lower_bound(v, v + m, x) - v + 1
using namespace std;
inline long long R()
{
    long long r = 0;bool b = 0;char c = getchar();
    while(!isdigit(c)) b = c == '-', c = getchar();
    while(isdigit(c)) r = r * 10 + c - '0', c = getchar();
    return b ? -r : r;
}
int n, m = 1, c[400050];long long t, q, a[200050], v[400050];
void C(int x) {for(;x <= m;x += x & -x) ++c[x];}
int Q(int x)
{
    int q = 0, y = m;for(--x;y > x;y &= y - 1) q += c[y];
    for(;x > y;x &= x - 1) q -= c[x];return q;
}
int main()
{
    n = R();t = R();for(int i = 1;i <= n;++i)
    F(a[i] = a[i - 1] + R()), F(a[i] - t + 1);
    sort(v, v + m);m = unique(v, v + m) - v;C(H(0));
    for(int i = 1;i <= n;++i) q += Q(H(a[i] - t + 1)), C(H(a[i]));
    return printf("%lld", q), 0;
}
```


---

## 作者：djh123 (赞：3)

## 题目大意

给你一个长度为$n$的数组$a$，求出有多少对$l, r$满足$\sum_{i=l}^r a[i] < k$

## solution
求出原数组的前缀和$sum[i]$，那么原式可以转化为$sum[r]-sum[l-1]<k$

移项得$sum[r]<k+sum[l-1]$，那么就可以对于每一个$sum[l-1]$，在$sum$数组里找所有合法的解

直接求解是$O(n^2)$的，考虑优化找合法解的过程

发现可以对$sum$数组排序后进行二分查找，对于每一个已经查找过的$sum$标记一下，这样就不会重复，标记的过程可以用树状数组来进行

复杂度$O(nlogn)$

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

struct FastIO {
    inline FastIO& operator >> (int& x) {
        x = 0; char f = 0, ch = getchar();
        while(ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
        while(ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
        return x = (f ? -x : x), *this;
    }
    inline FastIO& operator >> (long long& x) {
        x = 0; char f = 0, ch = getchar();
        while(ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
        while(ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
        return x = (f ? -x : x), *this;
    }
    inline FastIO& operator >> (double& x) {
        x = 0; char f = 0, ch = getchar();
        double d = 0.1;
        while(ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
        while(ch <= '9' && ch >= '0') x=x * 10 + ch - 48, ch = getchar();
        if(ch == '.') {
            ch = getchar();
            while(ch <= '9' && ch >= '0') x += d * (ch ^ 48), d *= 0.1, ch = getchar();
        }
        return x = (f ? -x : x), *this;
    }
}rin;
const int N = 1e6 + 50;
int n, to[N];
long long K, f[N], sum[N]; 
struct tree_array {
	int t[N];
	void insert(int x) {for(int i = x ; i <= n ; i += i & -i) t[i] ++;}
	int query(int x) {int ans = 0; for(int i = x ; i ; i &= i - 1) ans += t[i]; return ans;}
}T;
struct node {long long v; int p;}k[N];
bool operator < (const node &a, const node &b) {return a.v < b.v;}
int main() {
	rin >> n >> K;
	long long ans = 0;
	for(int i = 1 ; i <= n ; ++ i) rin >> f[i], sum[i] = sum[i - 1] + f[i];
	for(int i = 1 ; i <= n ; ++ i) k[i].v = sum[i], k[i].p = i;
	sort(k + 1, k + 1 + n);
	for(int i = 1 ; i <= n ; ++ i) to[k[i].p] = i;
	for(int i = 1 ; i <= n ; ++ i) {
		long long p = K + sum[i - 1];
		int l = 0, r = n;
		while(l < r) {
			int mid = (l + r + 1) >> 1;
			if(k[mid].v < p) l = mid;
			else r = mid - 1;
		}
		ans += l - T.query(l);
		T.insert(to[i]);
	}
	printf("%I64d\n", ans);
	return 0;
}


```


---

## 作者：shs_ryf (赞：3)

看到第一眼就觉得是数据结构题, 确切地说就是线段树树状数组这类的(因为我也只会这俩?), 再看一下十万级别的数据范围, 就想到用树状数组做.

那么具体怎么做呢? 显然我们要先求一个前缀和, 记作 sum[] , 那么问题就转变成了求

sum[r] - sum[l - 1] < t

的(l, r)数对的数量, 也就是对于每一个 r, 要求所有的 l, 使得

sum[l - 1] > sum[r] - t

我们先对所有的前缀和排一个降序, 然后去重, 并建立一棵与之序号一一对应的树状数组. 在这里要小心有一个 sum[0] = 0 , 然而树状数组一般都是从下标 1 开始的, 所以我们要把整个数组向右平移一格. 维护一个树状数组, 初值均为 0 . 然后记录一个前缀和prer, 从左往右扫一遍, 二分查找 prer - t 的位置, 把这个位置左边的和加起来加进 ans , 然后把 prer 这个位置加上 1 . 这是因为这个位置左边的全部都是比 sum[r] - t 大的 sum[l - 1] , 我们每扫过一个 sum 就记录一个 1 , 加起来便是对于这个 r 的答案. 这样扫的时间是 O(n) , 每一次求和和加一的时间用树状数组即可完成, 是 O(lgn) 的, 所以总共是 O(nlgn) 的时间, 可以通过此题.

不过要注意两点, 一是在开始扫之前就要把 0 这个位置给记录一下, 另一个是要注意使用 lower_bound 还是 upper_bound .

讲起来比较吃力, 对树状数组比较熟的同学可能会理解得快一些, 具体可以看代码.

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

int n, f[200902], ls;
ll a[200902], sum[200902];

inline int lowbit(int x){
    return x & -x;
}

void add(int x){
    for(int i = x; i <= ls; i += lowbit(i)){
        ++f[i];
    }
}

int get(int x){
    int ret = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        ret += f[i];
    }
    return ret;
}

inline bool cmp(ll x, ll y){
    return x > y;
}

int main(){
    ll t;
    cin >> n >> t;
    for(register int i = 1; i <= n; ++i){
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    sort(sum, sum + n + 1, cmp);
    int rs = 1;
    ls = 0;
    while(rs <= n){
        if(sum[ls] != sum[rs])
            sum[++ls] = sum[rs];
        ++rs;
    }
    for(register int i = ls; i >= 0; --i){
        sum[i + 1] = sum[i];
    }
    ++ls;
    ll ans = 0ll, prer = 0;
    add(lower_bound(sum + 1, sum + ls + 1, 0ll, cmp) - sum);
    for(register int i = 1; i <= n; ++i){
        prer += a[i];
        int npos = lower_bound(sum + 1, sum + ls + 1, prer - t, cmp) - sum;
        ans += get(npos - 1);
        int k = lower_bound(sum + 1, sum + ls + 1, prer, cmp) - sum;
        add(k);
    }
    cout << ans << endl;
    return 0;
}


```

---

## 作者：Ofnoname (赞：2)

**步骤一**：多次统计区间和且不修改，所以要用前缀和来获取区间和

**步骤二**：求有多少对 $ [l,r] $ 满足条件，就是在问“对每一个 $ r $， 有几个 $ l $ 满足 $ (0\le l<r)\wedge (S_r-S_l<t) $ ”。也就是满足 $ S_l>S_r-t $ 的所有 $ l $。

**步骤三**：可以用很多数据结构维护上面的 $ S_i $，权值线段树是其中一种。我的做法是维护最大范围（$ [-T,T]$ ）内所有数出现的次数，添加值时从最大区间开始，选择左右区间的一个往下递归（如果没有出现过就新建节点），每个节点记录区间内所有节点出现的次数。

递归是从上往下的一条链，如果从上往下都是没有之前出现过的区间，也至多新增 $ \log_2(T) =\log_2(2\times 10^{14})\approx 41$个节点。空间完全可以承受。

另外 $ S_i $ 的最大值是 $a_iN=2\times 10^{14}$，与 $ T $ 相等。因此也不用担心查询时越界。

```cpp
#include <cstdio>
using i64 = long long;

constexpr int MAXN = 2e5 + 5;
constexpr i64 MAXT = 2e14 + 5;

int N;
i64 T, ans, a[MAXN];

class Segtree
{
    struct Node{
        i64 num;
        Node *ls, *rs;
    }pool[MAXN * 42], *null = pool;//空间是N*log(T)的

    Node* NEW() {
        static Node *p = pool;
        *(++p) = Node{0, null, null};
        return p;
    }

    public:
    Node *root = NEW();
    i64 sum(Node *p, i64 l, i64 r, const i64 val) {
        if (p == null) return 0;
        if (l > val) return p->num;
        if (r < val) return 0;

        i64 mid = l + r >> 1;
        return sum(p->ls, l, mid, val) + sum(p->rs, mid+1, r, val);
    }
    void add(Node *&p, i64 l, i64 r, const i64 val) {
        if (p == null) p = NEW();
        if (l == r) {
            p->num++;
            return;
        }
        i64 mid = l + r >> 1;
        val>mid ? add(p->rs, mid+1, r, val) : add(p->ls, l, mid, val);
        p->num = p->ls->num + p->rs->num;
    }
}Seg;

int main() {  
    #define INILIST Seg.root, -MAXT, MAXT //! add和sum入口的参数
    
    scanf("%d%lld", &N, &T);    
    Seg.add(INILIST, 0);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &a[i]), a[i] += a[i-1];

        ans += Seg.sum(INILIST, a[i]-T); //! 之前的S[0..i-1]有哪些满足S[i] - S[j] < T的
        Seg.add(INILIST, a[i]);//! 统计完答案后加入自己
    } printf("%lld\n", ans);
}
```

---

## 作者：iodwad (赞：1)

其实可以 CDQ 分治。。

将题目中的限制写成前缀和的形式 $sum[r]-sum[l]<t\ (l<r)$ （这里为了方便省去了 $-1$）

然后移项得到 $sum[l]+t>sum[r]$

这个就可以很方便的用 CDQ 来计算了

```cpp
#include <iostream>
#include <cstdio>

typedef long long LL;

const int MAXN = 200000;

LL ans, m;
LL a[MAXN | 1], tmp[MAXN | 1];
int n;

inline int read() {
	register int x = 0, v = 1;
	register char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') v = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * v;
}

void CDQ(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	CDQ(l, mid);
	CDQ(mid + 1, r);
	int pl = l, pr = mid + 1, tot = l - 1;
	while (pl <= mid && pr <= r) {
		if (a[pl] > a[pr]) {
			tmp[++tot] = a[pl];
			++pl;
		} else {
			tmp[++tot] = a[pr];
			++pr;
		}
	}
	while (pl <= mid) tmp[++tot] = a[pl++];
	while (pr <= r) tmp[++tot] = a[pr++];
	pl = l; 
	pr = mid + 1;
	int cnt = 0;
	while (pl <= mid && pr <= r) {
		if (a[pl] + m > a[pr]) {
			++cnt;
			++pl;
		} else {
			ans += cnt;
			++pr;
		}
	}
	// while (pr <= r) ans += cnt, ++pr;
	ans += 1LL * cnt * (r - pr + 1);
	for (int i = l; i <= r; ++i) a[i] = tmp[i];
}

int main() {
	n = read();
	scanf("%lld", &m);
	for (int i = 1; i <= n; ++i) a[i] = a[i - 1] + read();
	CDQ(0, n);
	printf("%lld\n", ans);
	return 0;
}
```








---

