# K Integers

## 题目描述

You are given a permutation $ p_1, p_2, \ldots, p_n $ .

In one move you can swap two adjacent values.

You want to perform a minimum number of moves, such that in the end there will exist a subsegment $ 1,2,\ldots, k $ , in other words in the end there should be an integer $ i $ , $ 1 \leq i \leq n-k+1 $ such that $ p_i = 1, p_{i+1} = 2, \ldots, p_{i+k-1}=k $ .

Let $ f(k) $ be the minimum number of moves that you need to make a subsegment with values $ 1,2,\ldots,k $ appear in the permutation.

You need to find $ f(1), f(2), \ldots, f(n) $ .

## 样例 #1

### 输入

```
5
5 4 3 2 1
```

### 输出

```
0 1 3 6 10 
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
0 0 0 
```

# 题解

## 作者：zhengjinyi (赞：6)

###### 难得场切一个紫调了半天 qwq
对顶堆做法。\
考虑已经选出 $k$ 后的决策。\
如果需要将所有数移动到一个点，显然应该移动到中位数（位置上的中位数，而不是 $\lceil\frac{k}{2}\rceil$）。移动步数为所有数的位置到中位数的距离和。\
然而题目要求是将 $1\sim k$ 移动到连续段中。所以考虑先移动到中位数，再从中位数移动为长为 $k$ 的连续段。设 $x=\lfloor\frac{x}{2}\rfloor$，$y=\lfloor\frac{x-1}{2}\rfloor$，则左半部分距离为 $1\sim x$，右半部分同理。显然移动步数为 $\frac{x(x+1)+y(y+1)}{2}$，将答案减去这个值即可。所以只需维护所有数到中位数的距离和。\
移动到连续段中之后，还需要将其变为正序。根据最小交换次数等于逆序对数量的定理，用树状数组维护逆序对数即可。具体地，设正在处理的数下标为 $x$，则将已处理过的，下标大于 $x$ 的数的个数，加入新逆序对个数。\
动态维护中位数的部分参考 [这题](https://www.luogu.com.cn/problem/P1168)，用两个对顶堆维护。令大根堆顶为中位数，每次移动中位数时，若大根堆大小比小根堆小 $1$，移动中位数使得大根堆中数距离增加，小根堆中距离减少，需要将距离和减去两个中位数的差。否则不需要改变距离和。\
$O(n\log n)$。

Code：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define R read()
#define pq priority_queue
using namespace std;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}
const int INF=0x3f3f3f3f,N=500005;
int n,a[N],p[N];
ll c[N],sum,dt;
void add(int x,ll w){ for(;x<=n;x+=x&-x) c[x]+=w; }
ll ask(int x){ //树状数组维护逆序对个数 
	ll res=0;
	for(;x;x-=x&-x) res+=c[x];
	return res;
}
pq<int> q1; //大根堆维护较小的数，q1.top() 是中位数 
pq<int,vector<int>,greater<int> > q2; //小根堆维护较大的数 
void push(int w){ //对顶堆中插入一个数 
	if(w>q1.top()){
		sum+=w-q1.top(),q2.push(w);
		if(q2.size()>q1.size()){
			int x=q1.top(),y=q2.top();
			sum-=y-x; //更新距离和 
			q2.pop(),q1.push(y);
		}
	}else{
		sum+=q1.top()-w,q1.push(w);
		if(q1.size()==2&&!q2.size()){ q2.push(q1.top()),q1.pop(),sum=q2.top()-q1.top();return; }
		if(q1.size()-1>q2.size()){
			int x=q1.top(),y=q2.top();
			q1.pop(),q2.push(x);
		}
	}
}
int main(){
	n=R;
	for(int i=1;i<=n;i++)
		a[i]=R,p[a[i]]=i;
	q1.push(p[1]),printf("0 "),add(p[1],1);
	for(int i=2;i<=n;i++){
		push(p[i]);
		add(p[i],1);
		dt+=i-ask(p[i]);
		ll x=i/2,y=(i-1)/2;
		printf("%lld ",sum+dt-x*(x+1)/2-y*(y+1)/2); //减去差值 
	}
	return 0;
}
```

---

## 作者：皎月半洒花 (赞：6)

然而似乎另一篇题解是两只 $\log$ 的，这个地方说一种一个 $\log$ 的做法：善用 $\rm BIT$ .

发现似乎最终 $1\sim k$ 肯定会被合并到一起，所以把代价分为两个部分，求逆序对的 $\&$ 合并的。考虑合并的代价。发现对于每个大于 $k$ 的位置，要么把它向前移，要么把它向后移，所以答案就是 $\min(s_i,k-s_i)$，其中 $s_i$ 表示 $i-$前缀 中 $\leq k$ 的数的个数。

于是就得到一个 $n^2$ 的做法。但考虑其实 $\min(s_i,k-s_i)$ 这东西某个临界点的左右分别单调，所以考虑二分出这个中间点，然后直接拿等差数列求和公式做。

那么显然这东西只需要求一个中位数即可。而 $\rm BIT$ 本身支持二分，所以用树状数组可以做到小常数的 $n\log n$，比线段树不知道要快到哪里去了.jpg

```cpp
    LL ans1, ans2 ;
    int N, base[MAXN], pos[MAXN] ;
    struct BIT{
        LL _bit[MAXN] ;
        void ins(int x, int v){
            for ( ; x <= N ; x += (x & -x)) _bit[x] += v ;
        }
        LL ask(int x){
            LL res = 0 ;
            for ( ; x ; x -= (x & -x)) res += _bit[x] ;
            return res ;
        }
        int find_k(int k){
            int res = 0 ;
            for (int j = 20 ; j >= 0 ; -- j)
                if ((res | 1 << j) <= N)
                    if (_bit[res | (1 << j)] <= k)
                        res |= (1 << j), k -= _bit[res] ;
            return res ;
        }
    }A, B ;
     
     
    int main(){
        cin >> N ; int i, j ;
        for (int i = 1 ; i <= N ; ++ i)
            scanf("%d", &base[i]), pos[base[i]] = i ;
        for (int i = 1 ; i <= N ; ++ i){
            A.ins(pos[i], 1), B.ins(pos[i], pos[i]) ;
            ans1 += i - A.ask(pos[i]), j = A.find_k(i / 2) + 1 ;
            int median1 = i >> 1, median2 = i - 1 - median1 ;
            ans2 = 1ll * median1 * j - B.ask(j - 1) - (1ll * median1 * (median1 + 1) >> 1) ;
            ans2 += B.ask(N) - B.ask(j) - 1ll * median2 * j - (1ll * median2 * (median2 + 1) >> 1) ;
            printf("%lld\n", ans1 + ans2), ans2 = 0 ;
        }
    }
```

---

## 作者：Soulist (赞：6)

~~被这道题气到了，人生目前唯一一次可能的 div2 的 AK 机会没了~~

讲一下本题做法

容易发现分开交换和连续交换等价，所以我们不妨先进行连续的交换在交换别的

考虑连续的交换，可以发现连续的交换 $i$ 和 $i+1$，从 $x$ 交换到 $y$，可以看作将 $x$ 移动到 $y$ ，代价为 $|y-x|$

考虑移动，我们显然可以分成两步：

考虑排列$1,2,...x$，我们先把这段区间内的其他数移出去，使其内部形成$1\to x$的某个排列

第二步则是把$1\to x$的这个无序组合挪成$1,2...x$的排列

考虑第二步，其移动次数可以通过模拟/手玩发现其移动次数为这个序列的逆序对数

第一步则应当为，将$1\to x$这段序列中不属于$1\to x$中的数移出去

假设这个区间在$1\to x$这段区间内的数为$0$，不为的是$1$

则可以看作区间$[L,R]$形如：

$$0,1,0,0,0,1,0,0...,0$$

考虑一个$1$往左挪，其往左挪则其左边的数必然均往左挪，假设其往右挪，则其右边的数均往右挪

于是一个数往左挪的代价为其下标$i$减去区间的左端点$L$，减去其左边的$1$数量

即：$i-L-pre_i$

往右的代价则为：$R-i-nxt_i$

显然往左的代价单调增，往右的代价单调减，所以必然存在一个分界点满足其左边的往左，右边的往右，如果知道此点为谁，则答案显然很容易统计

即$[L,x]$区间的下标和$-[L,x]$的数量$\times L-pre_i$之和

右边的类似

如何求此点？显然可以二分其位置。。。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long 
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 3e5 + 5 ; 
int n, a[N], g[N], sum[N], f[N], tree[N], tree2[N], vis[N] ; 
int lowbit( int x ) {
	return x & ( -x ) ;
}
int query( int x ) {
	int sum = 0 ;
	for( re int i = x; i; i -= lowbit(i) ) sum += tree[i] ;
	return sum ; 
}
void Add( int x, int k ) {
	for( re int i = x; i <= n; i += lowbit(i) ) tree[i] += k ;
}
int query2( int x ) {
	int sum = 0 ;
	for( re int i = x; i; i -= lowbit(i) ) sum += tree2[i] ;
	return sum ; 
}
void Add2( int x, int k ) {
	for( re int i = x; i <= n; i += lowbit(i) ) tree2[i] += k ;
}
int Get( int l, int r, int L, int R ) {
	int ans = l, m = query( r ) - query( l ) ; 
	while( l <= r ) {
		int mid = ( l + r ) >> 1 ; 
		int lkid = query( mid - 1 ) - query(L) ;
		int rkid = query(R) - query(mid) ;
		lkid = mid - L - lkid, rkid = R - mid - rkid ; 
		if( lkid <= rkid ) ans = mid, l = mid + 1 ;
		else r = mid - 1 ; 
	}
	return ans ; 
}
signed main()
{
	n = gi() ; rep( i, 1, n ) a[i] = gi(), g[a[i]] = i ; 
	for( re int i = 1; i <= n; ++ i ) {
		int u = i - 1 - query( g[i] ) ;
		f[i] = f[i - 1] + u, Add( g[i], 1 ) ; 
	}
	memset( tree, 0, sizeof(tree) ) ;
	int L = n, R = 1 ;
	for( re int i = 1; i <= n; ++ i ) Add( i, 1 ), Add2( i, i ), vis[i] = 1 ;
	for( re int i = 1; i <= n; ++ i ) {
		L = min( L, g[i] ), R = max( R, g[i] ) ;
		Add( g[i], -1 ), Add2( g[i], -g[i] ), vis[g[i]] = 0 ;
		int mid = Get( L, R, L, R ) ; 
		int k1 = query2( mid ) - query2( L ), kk1 = query( mid ) - query( L ) ;
		int k2 = query2( R ) - query2( mid ), kk2 = query( R ) - query( mid ) ;
		sum[i] = ( k1 - kk1 * L - ( kk1 * ( kk1 - 1 ) ) / 2 ) + ( kk2 * R - k2 - ( kk2 * ( kk2 - 1 ) ) / 2 ) ;
	}
	rep( i, 1, n ) printf("%I64d ", sum[i] + f[i] ) ;
	return 0 ;
}
```

---

## 作者：kouylan (赞：4)

这道题说要求出对于每一个 $k$，在数列中得到 $1-k$ 的连续排列的最小交换次数。

想要得到这样一个排列，我们肯定是把它分成两步。首先先让 $1-k$ 这 $k$ 个数移到连续的一段，然后再进行排序。

对于排序，我们只需要求出逆序对即可。因为冒泡排序告诉我们，每次交换两个数，逆序对个数都会减一。

所以关键问题是如何把它们并在一起。我们大家应该都容易想到，固定最中间一个数不动，让左右两边的数朝中间靠拢，这种方法肯定是最优的。所以我们可以先用二分找出最中间那个不动点 $pos$，然后左右分别计算。

我们先来看左边，假设包含上 $pos$ 的位置，共有 $s$ 个数，那么移到最后，位置肯定是 $pos-s+1,pos-s+2\ ...\ pos$。移动的距离就是最终位置的和减去初始位置的和的差。最终位置的和可以用等差数列求出，即 $pos\times s-s(s+1)/2$，初始位置的和可以用树状数组维护得到。

对于右边也是类似，只不过是用初始位置和减去最终位置的和罢了。

最后，对于每一个 $f(k)$，就是把上述三个值相加起来就行了。

下面是 AC 代码

```cpp
/*
Codeforces 1268C
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define lowbit(x) (x&-x)

int n,a[200005],p[200005];
int c1[200005],c2[200005];
int siv;

void fix1(int x,int v)
{
	for(int i=x;i<=n;i+=lowbit(i))
		c1[i] += v;
}

int ask1(int x)
{
	int res=0;
	for(int i=x;i>=1;i-=lowbit(i))
		res += c1[i];
	return res;
}

void fix2(int x,int v)
{
	for(int i=x;i<=n;i+=lowbit(i))
		c2[i] += v;
}

int ask2(int x)
{
	int res=0;
	for(int i=x;i>=1;i-=lowbit(i))
		res += c2[i];
	return res;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n&&cin>>a[i];i++)
		p[a[i]] = i;
	for(int k=1;k<=n;k++)
	{
		siv += k-ask1(p[k])-1;
		fix1(p[k],1), fix2(p[k],p[k]);
		int l=1,r=n,pos=0;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(ask1(mid-1)<=k/2)
				pos = mid, l = mid+1;
			else
				r = mid-1;
		}
		int ls1=ask1(pos),ls2=ask2(pos);
		int rs1=k-ls1,rs2=ask2(n)-ls2;
		int resl=pos*ls1-ls2-ls1*(ls1-1)/2;
		int resr=rs2-pos*rs1-rs1*(rs1+1)/2;
		cout<<siv+resl+resr<<' ';
	}
	
	return puts(""), 0;
}
```

祝大家 AC 愉快！

---

## 作者：liuyz11 (赞：4)

# 题解 CF1268C 【K Integers】

该场比赛的题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12177652.html)

题解我都看不懂，来一篇详细一点的

题目大意：有一数列p，长度为n。求最少的交换两个相邻数字的操作，使得数列$p$中存在连续子序列$1$,$2$,$...$, $i$ 。其中$i$为$1$,$2$,...,$n$。

这题大概一看就和逆序对有关，因为这个交换相邻操作和冒泡排序一模一样，而冒泡需要的操作就是逆序对的个数。

不难得出，当 $i$ = $n$ 时，答案就是逆序对个数。

对于其它的 $i$ 来说，我们也可以得到这样一个贪心思想，先将1..i 放到一起，然后再将它们变成有序的。

变成有序的需要的操作很显然也可以按照 $i$ = $n$ 来做，但是将$1$..$i$ 要放到哪里去呢？

根据初中学习的零点分段法，不知道的可以去看百度百科（传送门）了解一下。

最后将它们移到$1$..$n$在原数列中的中间一个位置（为了方便，后文用 $mid$ 表示），一定是最优的，这可以用二分查找来实现。

至于它们需要移动多少呢？这要分成左右两段来算。

首先 mid 左边的全部移到中点，我们假设它们一共有 $x$ 个，那么它们分别会被移到 $mid - x$ ， $mid - x + 1$ ，...， $mid - 1$ 。需要移动的操作个数分别要减去它们在数列中的位置，总答案就是要减去它们的总和 $sum$ ，这可以用线段树或树状数组维护。得出以下的式子。

$ans = mid - x + mid - x + 1 + ... + mid - 1 - sum = mid · x - sum - x · (x + 1) / 2$

注意，在代码中为了方便x包含了在 mid 点上的点，所以变成了 $mid· x - sum - x · (x - 1) / 2 $。

另外在右边也是差不多，得出式子为 $ans = sum - mid · x - x · (x + 1) / 2 $。

代码中还有以下几个注意点：
1.其实当 $i$ = $n$ 的时候也是可以用上一个式子算的，后面两个值都为$0$，你可以手算一下。

2.需要两个树状数组，一个维护前缀和（当然也可以用归并排序并加一些记录，但是比较长），一个维护上述的 $sum$ 。

3.要开longlong！要开longlong！！要开longlong！！！重要的事情说三遍。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 200005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int n;
int a[MAXN], pos[MAXN];
ll tree0[MAXN], tree1[MAXN];

void update0(int x, int y){
	for(int i = x; i <= n; i += lowbit(i)) tree0[i] += y;
}

void update1(int x, int y){
	for(int i = x; i <= n; i += lowbit(i)) tree1[i] += y;
}

ll query0(int x){
	ll res = 0;
	for(int i = x; i > 0; i -= lowbit(i)) res += tree0[i];
	return res;
}

ll query1(int x){
	ll res = 0;
	for(int i = x; i > 0; i -= lowbit(i)) res += tree1[i];
	return res;
}

int main(){
	scanf("%d", &n);
	rep(i, 1, n){
		scanf("%d", &a[i]);
		pos[a[i]] = i;
	}
	ll res0 = 0;
	rep(i, 1, n){
		res0 += i - 1 - query0(pos[i]);
		update0(pos[i], 1);
		update1(pos[i], pos[i]);
		int l = 1, r = n, s;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(query0(mid - 1) * 2 <= i){
				s = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		ll left_sum0 = query0(s), left_sum1 = query1(s);
		ll res1 = left_sum0 * s - left_sum1 - left_sum0 * (left_sum0 - 1) / 2;
		ll right_sum0 = i - left_sum0, right_sum1 = query1(n) - left_sum1;
		res1 += right_sum1 - right_sum0 * s - right_sum0 * (right_sum0 + 1) / 2;
		printf("%lld ", res0 + res1);
	}
	puts("");
    return 0;
}
```

---

## 作者：_ZSR_ (赞：1)

### [CF1268C K Integers](https://www.luogu.com.cn/problem/CF1268C)

考虑拆分贡献。满足条件的交换次数由两部分构成，一是把 $1$ 到 $k$ 移动到一起的交换次数，二是使得 $1$ 到 $k$ 有序的交换次数。第二种很好求，就是逆序对数，考虑怎么求第一种。因为要让总交换次数尽可能少，那么根据贪心不难想到，我们肯定是选定某一个位置，然后所有数都向这个位置靠近。那这个位置选在哪里最优呢？显然是中位数嘛。因此我们只要二分找到中位数，然后计算每个数到它的距离之和，再加上逆序对个数就是最终的答案了。这可以分别用一个树状数组维护。枚举 $k$ 的复杂度是 $O(n)$ 的，二分的复杂度是 $O(\log n)$ 的，所以总的复杂度是 $O(n\log n)$ 的。

code
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int n;
int a[N],p[N];
inline int lowbit(int x)
{
    return x & -x;
}
struct Tree{
    ll tr[N];
    inline void add(int x,int k)
    {
        for (int i=x;i<=n;i+=lowbit(i)) tr[i]+=k;
    }
    inline ll query(int x)
    {
        ll res=0;
        for (int i=x;i;i-=lowbit(i)) res+=tr[i];
        return res;
    }
}A,B;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("zsr.in","r",stdin);
    freopen("zsr.out","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for (int i=1;i<=n;++i)
    {
        cin>>a[i];
        p[a[i]]=i;
    }
    ll rev=0;
    for (int i=1;i<=n;++i)
    {
        rev+=i-A.query(p[i])-1;
        A.add(p[i],1),B.add(p[i],p[i]);
        int l=1,r=n,pos=0;
        while (l<=r)
        {
            int mid=l+r>>1;
            if (A.query(mid-1)*2<=i) l=mid+1,pos=mid;
            else r=mid-1;
        }
        int cntl=A.query(pos),cntr=i-cntl;
        ll suml=B.query(pos),sumr=B.query(n)-suml;
        ll wl=1ll*pos*cntl-suml-1ll*cntl*(cntl-1)/2;
        ll wr=sumr-1ll*pos*cntr-1ll*cntr*(cntr+1)/2;
        cout<<wl+wr+rev<<" ";
    }
    return 0;
}

```


---

## 作者：Ginger_he (赞：1)

首先将一个长度为 $m$ 的排列还原为 $1,2,\dots,m$ 需要的操作次数为这个排列的逆序对数。结合到这题可以得出 $f(i)$ 就是只考虑 $1,2,\dots,i$ 的逆序对数加上将它们靠在一起需要的步数。

前半部分可以由只考虑 $1,2,\dots,i+1$ 的逆序对数减去 $i+1$ 作为较大值的逆序对数。比如一个长度为 $5$ 的排列 $[1,4,5,3,2]$，全局的逆序对有 $[4,3][4,2][5,3][5,2][3,2]$，$5$ 作为较大值的逆序对有 $[5,3][5,2]$，那么前后两者的数量之差恰好为只考虑 $1,2,3,4$ 的逆序对数。

接下来考虑后半部分，显然是靠到中位数的位置最优，由于每次从 $i+1$ 到 $i$ 只删除 $1$ 个数，所以中位数移动的次数是 $O(1)$ 的，用指针和链表维护即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
struct node
{
	int x;
	ll s;
}u,t[N<<2];
int n,m,k,a[N],p[N],c[N],f[N],lst[N],nxt[N];
ll tmp,s,ans;
vector<ll> v;
inline void add(int x)
{
	for(;x<=n;x+=x&-x) c[x]++;
}
inline int query(int x)
{
	int res=0;
	for(;x;x-=x&-x) res+=c[x];
	return res;
}
inline void del(int x)
{
	s-=x;
	if(x<=k) tmp-=x;
	lst[nxt[x]]=lst[x];
	nxt[lst[x]]=nxt[x];
}
inline ll calc(int l,int r)
{
	return 1ll*(l+r)*(r-l+1)/2;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		p[a[i]=read()]=i;
	for(int i=n;i>=1;i--)
	{
		ans+=(f[a[i]]=query(a[i]));
		add(a[i]);
	}
	v.push_back(ans);
	nxt[0]=1,lst[n+1]=n;
	for(int i=1;i<=n;i++)
		lst[i]=i-1,nxt[i]=i+1;
	k=n+1>>1,tmp=calc(1,k),s=calc(1,n);
	for(int i=n;i>=2;i--)
	{
		ans-=f[i],del(p[i]);
		if(i&1)
		{
			if(p[i]>k) tmp-=k;
			if(p[i]>=k) k=lst[k];
		}
		else if(p[i]<=k) k=nxt[k],tmp+=k;
		m=i>>1;
		v.push_back(ans+calc(k-m+1,k)-tmp+s-tmp-calc(k+1,k+i-m-1));
	}
	reverse(v.begin(),v.end());
	for(auto i:v)
		printf("%lld ",i);
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

闲话：@wz20201136 好强啊，秒了这道题Orz。

upd：有一个地方等差数列求和公式忘了除 2 了，丢人（

---



看起来非常棘手，不是吗？

首先我们发现这 $1\sim k$ 共 $k$ 个数只要相对位置不变那么影响结果的就只有它们之间的距离。因此考虑把这个操作分成两步，第一步是把所有 $1 \sim k$ 的归到中间，第二步是把这个排列变成有序的。

第二步很明显是一个典题，答案等于排列的逆序对数。

于是就剩下怎么处理第一步了。首先根据初中的数学知识，我们可以得到在奇数的时候归并到中位数、偶数的时候归并到最中间两个点的时候最优。

为了便于写程序我们肯定不会分讨，所以对于 $k$ 个数，我们直接选定 $mid=\left\lfloor \dfrac{k}{2} \right\rfloor$ 这个位置作为归并的点。假设这个点是 $y$，那么我们的范围就是 $y-\left\lfloor \dfrac{k}{2} \right\rfloor+1$ 到 $y+\left\lceil \dfrac{k}{2} \right\rceil$ 这段范围。

于是我们需要求出每个点到这些对应位置的距离。容易发现，假设这些点坐标是 $p_1,p_2,\dots,p_k$。由于绝对值很烦，我们可以左右拆开来，绝对值就没有了。

那么我们要求的答案即两部分：

$$\begin{cases}y-mid+1-p_1+y-mid+2-p_2+\dots+y-p_{mid}\\p_{mid+1}-\left(y+1\right)+p_{mid+2}-\left(y+2\right)+\dots+p_k-(y+k-mid)\end{cases}$$

化简得到：

$$\begin{cases}\dfrac{mid\left(2y-mid\right)}{2}-\sum\limits_{i=1}^{mid}p_i\\\sum\limits_{i=mid+1}^kp_i-\dfrac{(k-mid)\left(2y+k-mid+1\right)}{2}\end{cases}$$

可能不够简洁，可以进一步拆开：

$$\begin{cases}mid \cdot (y-mid)+\dfrac{mid \cdot (mid-1)}{2}-\sum\limits_{i=1}^{mid} p_i\\\sum\limits_{i=mid+1}^{k}p_i-(k-mid)\cdot y-\dfrac{(k-mid)(k-mid+1)}{2}\end{cases}$$

~~但是有一说一感觉这俩没啥区别，都挺复杂。~~

容易发现用树状数组或者线段树维护一下两个 $p$ 的和，每次插入单点然后区间求和，单次复杂度 $\mathcal{O}(\log n)$。

然后我们只需要知道 $mid$ 和 $y$，容易发现这个用一个线段树或者树状数组维护一下就能得到中位数（二分查找好像也可以吧），就可以知道 $mid$ 以及 $y$ 了，单次复杂度 $\mathcal{O}(\log n)$。

然后考虑怎么弄逆序对的问题，容易发现这就是一个二维偏序板子题，弄一个线段树每次插进来新的数就更新一下答案即可，然后全局求个和，单次复杂度 $\mathcal{O}(\log n)$。

由于要求 $n$ 次，最后复杂度即 $\mathcal{O}(n \log n)$。

---

## 作者：Hoks (赞：0)

## 前言
挺好的一道 DS 题。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
首先因为要输出 $n$ 个数，所以枚举这 $n$ 的情况是肯定少不了了。

接着来考虑问题，其实就是：
![](https://cdn.luogu.com.cn/upload/image_hosting/4e2nvaur.png)
这样一个情况，其中黑框表示 $1\sim n$ 所有数，蓝框表示包住 $1\sim k$ 所有数的最小框，而红框是我们最后把数移进去的样子。

那么这个题就被切割为了两个部分：
1. 把这些数移动进去。
2. 进行排序。

套路的考虑把这两部分分开考虑。

首先我们知道的是，在 $1$ 中如果多用了步数去交换两个需要的数而不是单纯的移动到一起，这一步交换就可以放进 $2$ 中。

也就是 $1\sim k$ 这些数的偏序关系是不变的。

那么根据冒泡排序的结论，交换次数就是逆序对个数。

数逆序对当然很擅长，直接考虑用 BIT 维护即可。

因为动态插入数，就相当于是一个区间加，数一下即可。

接着来考虑处理比较不熟悉的部分 $1$。

其实也还算比较简单，考虑数学中应该都曾做过一类题：

> 求 $|x-a_1|+|x-a_2|+|x-a_3|(a_1\le a_2\le a_3)$ 最小值。

这种题的结论也是显而易见的：
1. 如果奇数个，$x$ 就取最中间的那个 $a$ 的值。
2. 如果偶数个，$x$ 就取中间相邻两个数的任意一个值。

这两个问题相似却又有不同，在这个问题中，我们的 $x$ 只能取到一个存在点的值。

类似的思考，不难发现最优决策即是固定最中间一个数不动，让左右两边的数朝中间靠拢。

那怎么找出这个最中间的数呢？

因为有单调性，所以直接二分即可。

check 也用 BIT 就可以轻松实现了。

因为左右相同，所以这边只讲左边。

考虑固定的点是 $a_x$，那么左边的数就有 $a_1,\dots,a_{x-1}$。

而他们应该移到的位置是 $a_x-(x-1),\dots,a_x-1$。

移动的代价就是两两作差，交换律一下就是下面之和减上面之和。

上面的那个和可以直接用 BIT 维护出来，只需要考虑下面的和。

先给 $a_x$ 有关部分都提出来，剩下的就是个等差数列，然后就做完了。
## 代码
```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    int query(int x){int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
}tt[2];
int n,a[N],pos[N];
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
    inline bool chk(char c) { return !(c=='('||c==')'); }
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
signed main()
{
    tt[0].n=tt[1].n=n=read();for(int i=1;i<=n;i++) pos[a[i]=read()]=i;
    for(int k=1,s=0;k<=n;k++)
    {
        s+=k-tt[0].query(pos[k])-1;int l=1,r=n,ans=0;
        tt[0].modify(pos[k],1),tt[1].modify(pos[k],pos[k]);
        while(l<=r) if(tt[0].query(mid-1)<=k/2) ans=mid,l=mid+1;else r=mid-1;
        int l1=tt[0].query(ans),l2=tt[1].query(ans),r1=k-l1,r2=tt[1].query(n)-l2;
        print(s+ans*l1-l2-l1*(l1-1)/2+r2-ans*r1-r1*(r1+1)/2);put(' ');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：tkdqmx (赞：0)

#### 0.前言

具体做法其它题解已经讲过，本文仅详解平衡树做法。

update on 2023.12.8：添加了注释。

#### 1.逆序对

对于每个数，加上它的排名减 1 即可。

#### 2.合拢

我们考虑添加一个数后对原数的影响：

1.原来有奇数个数，添加到原中位数 $^1$ 左边。

![](https://cdn.luogu.com.cn/upload/image_hosting/i9nj90i8.png)

发现此时中位数会往左走一个。

原来左边的两个数到中位数的距离会减小，但右三个会增大。

所以答案会增加原第 2、3 个数中的距离。

2.原来有偶数个数，添加到原中位数右边。

3.原来有奇数个数，添加到原中位数左边。

![](https://cdn.luogu.com.cn/upload/image_hosting/x3k4h7ue.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/qrtbjxb8.png)

中位数没有发生改变，不影响答案。

4.原来有偶数个数，添加到原中位数右边。

![](https://cdn.luogu.com.cn/upload/image_hosting/kag260vx.png)

发现此时中位数会往右走一个。

原来左边的三个数到中位数的距离会减小，但右三个会增大。

所以答案不会变化。

#### 3.其它影响

![](https://cdn.luogu.com.cn/upload/image_hosting/yt29malv.png)

添加数后，左边的两个数要移动的距离，因为到中位数的中间增加了一个数，就可以移动一个位置需要降低。

#### 4.做法

使用平衡树，找到需要添加的数的排名并加上，并进行以上处理即可。

#### 5.代码
用到了 pb_ds 库 $^2$，详见代码。

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define LL long long
tree<LL,null_type,less<LL>,rb_tree_tag,tree_order_statistics_node_update> tr;    //平衡树
LL n,zws,ans,dy[200005];
int main(){
    scanf("%d",&n);
    for(int i=1,p;i<=n;i++) scanf("%d",&p),dy[p]=i;
    printf("0 "),tr.insert(dy[1]),zws=dy[1];
    for(int i=2;i<=n;i++){
        tr.insert(dy[i]);    //求逆序对
        LL ikey=tr.order_of_key(dy[i]);    //找排名
        ans+=i-ikey-1;
        LL now=*tr.find_by_order(i>>1);    //找现在的中位数
        if(now!=zws&&!(i&1))   ans+=now-zws-1;    //处理情况2
        zws=now,ans+=abs(zws-dy[i])-abs(ikey-(i>>1));    //处理这个数本身要交换的次数
        if(dy[i]<zws)    ans-=ikey;    //处理情况3
        else    ans-=i-ikey-1;
        printf("%lld ",ans);
    }
}
```
$^1$：本文所述中位数，指的是第 $\lceil \frac{n}{2} \rceil$ 个数。

$^2$：详见 [NOI系列竞赛可用的非主流技巧](https://www.luogu.com.cn/blog/liutianyou/CPP-Killer#:~:text=0x1B)。

---

## 作者：do_while_true (赞：0)

对于 $f(k)$ 的计算，先计算把 $1\sim k$ 移成连续段，然后再计算逆序对数（最小交换次数使得一个排列排好序）。

至于为什么是对的？感性理解一下，首先排好序一定要有个逆序对的代价，假如两个数之间没有相邻，则交换它们需要一步一步走过去，这样的花费就高了。

考虑 $f(k-1)\to f(k)$ 新增的代价，计算逆序对数是容易的，$k$ 只可能作为逆序对的第一个数，而第二个数可能的取值 $[1,k-1]$ 都已经出现过，所以直接计算全局中以 $k$ 为开头的逆序对数，树状数组易做到。

计算把 $1\sim k$ 移成连续段的代价，有个经典结论就是移到中位数处，如果长度为偶数，移到中间两个的哪个都行。

因为每个数不能移动到同一位置，所以代价计算会很麻烦，那就钦点让每个数可以移动到同一位置，最后再减去多余代价也就是两个等差数列即可。

现在计算每个数移动到中位数处的距离，注意到每加入一个 $k$ 之后中位数的最多会移动 $1$ 个位置，且移动之后除了 $k$ 以外的值对总代价的贡献不变，直接用 `set` 维护 $1\sim k$ 出现的位置然后移动就可以了。

其实可以不用维护中位数，直接用树状数组记录哪些位置出现了数然后倍增找中位数也可以，常数更小。

代码可能不大像说人话的样子，看看思路就好了。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<set>
#define pb push_back
#define mp std::make_pair
#define fir first
#define sec second
typedef std::pair<int, int> pii;
typedef std::vector<int> veci;
typedef std::vector<pii> vecpii;
typedef long long ll;
ll Abs(ll x) { return x < 0 ? -x : x; }
template <typename T>
T& read(T& r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
inline int lowbit(int x) { return x & (-x); }
const int N = 2000100;
int n, a[N], pos[N];
struct BIT {
	int tree[N];
	int sumq(int x) { int sum = 0; for(; x; x -= lowbit(x)) sum += tree[x]; return sum; }
	void modify(int x, int v) { for(; x <= n; x += lowbit(x)) tree[x] += v; }
}tr;
ll ans[N], c[N];
std::set<int>st;
ll calc(ll x) { return x * (x + 1) / 2; } 
signed main() {
	read(n);
	for(int i = 1; i <= n; ++i) read(a[i]), pos[a[i]] = i;
	for(int i = n; i; --i) {
		c[a[i]] = tr.sumq(a[i]);
		tr.modify(a[i], 1);
	}
	int p = 1, num = 1; st.insert(pos[1]);
	for(int i = 2; i <= n; ++i) {
		ans[i] = ans[i-1] + c[i];
		if(!(i&1)) {
			ans[i] += Abs(pos[num] - pos[i]);
			if(pos[i] < pos[num]) ++p;
			st.insert(pos[i]);
			continue ;
		}
		st.insert(pos[i]);
		if(pos[i] < pos[num]) ++p;
		if(p != (i+1)/2) {
			auto it = st.lower_bound(pos[num]);
			if(pos[i] < pos[num]) --it, --p;
			else ++it, ++p;
			num = a[*it];
		}
		ans[i] += Abs(pos[num] - pos[i]);
	}
	for(int i = 1; i <= n; ++i) printf("%lld ", ans[i] - calc((i-1)/2) - calc(i/2));
	return 0;
}
```

---

