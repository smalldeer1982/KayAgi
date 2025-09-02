# Array Partition

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

Let $ min(l, r) $ be the minimum value among $ a_l, a_{l + 1}, \ldots, a_r $ and $ max(l, r) $ be the maximum value among $ a_l, a_{l + 1}, \ldots, a_r $ .

Your task is to choose three positive (greater than $ 0 $ ) integers $ x $ , $ y $ and $ z $ such that:

- $ x + y + z = n $ ;
- $ max(1, x) = min(x + 1, x + y) = max(x + y + 1, n) $ .

In other words, you have to split the array $ a $ into three consecutive non-empty parts that cover the whole array and the maximum in the first part equals the minimum in the second part and equals the maximum in the third part (or determine it is impossible to find such a partition).

Among all such triples (partitions), you can choose any.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
11
1 2 3 3 3 4 4 3 4 2 1
8
2 9 1 7 3 9 4 1
9
2 1 4 2 4 3 3 1 2
7
4 2 1 1 4 1 4
5
1 1 1 1 1
7
4 3 4 3 3 3 4```

### 输出

```
YES
6 1 4
NO
YES
2 5 2
YES
4 1 2
YES
1 1 3
YES
2 1 4```

# 题解

## 作者：引领天下 (赞：6)

考场状态：从F开始倒序开题，一眼看出是ST表+二分，然后调了1.5h始终WA2，于是找了个神仙去确认了下思路是对的，重新码了一遍就过了。

思路：

首先可以发现这个东西需要多次查询区间最值，而又不需要支持修改，于是自然而然的想到了ST表。

然后进一步的，我们改设 $y$ 为 $x+y$，那么我们会发现一些有趣的结论：

- 若当前的 $max\{1,x\} < min\{x+1,y\}$，则显然我们需要将 $y$ 向后移动以使得他能包含到值为 $max\{1,x\}$ 的元素。

- 若当前的 $max\{1,x\} > min\{x+1,y\}$，则我们需要将 $y$ 向前移动以使得他能把值 $<max\{1,x\}$ 的元素从区间 $[x+1,y]$ 中踢出去。

- 若当前满足了 $max\{1,x\} = min\{x+1,y\}$，则我们可以进一步检查 $max\{x+1,n\}$ 与 $max\{1,x\}$ 的关系，然后进一步调整 $y$ 的大小：小了就往前，大了就往后。

关键代码：

```cpp
pre[n]=a[n];//pre:后缀最大值
for(int i=n-1;i>=1;i--)pre[i]=max(pre[i+1],a[i]);
mx=0;b=0;
for(int i=1;i<=n-2;i++){
	mx=max(mx,a[i]);//mx即为max{1,x}
	int l=i+1,r=n,ans=-1,mid;//对我们重新定义的y进行二分
	while(l<=r){
		mid=(l+r)>>1;
		int num=query(i+1,mid);//查询min{x+1,mid}
		if(num>mx)l=mid+1;//调大y
		else if(num<mx)r=mid-1;//调小y
		else if(num==mx){//可能是答案，进一步调整y
			if(pre[mid+1]>mx)l=mid+1;//max{mid+1,n}太大了，只能将y后移
			else if(pre[mid+1]<mx)r=mid-1;//太小了，将y前移
			else if(pre[mid+1]==mx)break;//找到答案
		}
	}
	if(query(i+1,mid)==mx&&pre[mid+1]==mx){//对答案进行检查，确认是否为非正常退出（即找到了解）
		b=1;
		puts("YES");
		write(i,mid-i,n-mid);puts("");
		break;
	}
}
if(!b)puts("NO");
```

---

## 作者：wmrqwq (赞：3)

# 题目链接

[CF1454F Array Partition](https://www.luogu.com.cn/problem/CF1454F)

# 解题思路

我们发现显然第一个和第三个区间的值区间随着长度的增大而增大。

于是我们就可以枚举第一个区间的右端点位置，然后现在问题就转化成了找到一个断点来确定第二，三个区间的长度，由于前文提到的**第三个区间的值区间随着长度的增大而增大**，于是我们就可以通过二分来找出这个断点。

这里我使用了分块来查询区间最小值，时间复杂度 $O(n \times \sqrt n \times \log n)$，常数小的话能过。

如果使用其它数据结构可以有更好的复杂度。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
ll t;
ll n;
ll a[200010];
ll sq,b[200010],maxn[200010],minn[200010],L[200010],R[200010];
ll summax[200010];
ll querymax(ll l,ll r)
{
	ll ma=-1e18;
	if(b[l]==b[r])
	{
		forl(i,l,r)
			ma=max(ma,a[i]);
		return ma;
	}
	forl(i,l,R[b[l]])
		ma=max(ma,a[i]);
	forl(i,L[b[r]],r)
		ma=max(ma,a[i]);
	forl(i,b[l]+1,b[r]-1)
		ma=max(ma,maxn[i]);
	return ma;
}
ll querymin(ll l,ll r)
{
	ll mi=1e18;
	if(b[l]==b[r])
	{
		forl(i,l,r)
			mi=min(mi,a[i]);
		return mi;
	}
	forl(i,l,R[b[l]])
		mi=min(mi,a[i]);
	forl(i,L[b[r]],r)
		mi=min(mi,a[i]);
	forl(i,b[l]+1,b[r]-1)
		mi=min(mi,minn[i]);
	return mi;
}
void solve()
{
	cin>>n;
	forl(i,1,n+1)
		summax[i]=0;
	forl(i,1,n)
		cin>>a[i];
	forr(i,n,1)
		summax[i]=max(summax[i+1],a[i]);
	sq=pow(sqrt(n),1);
	forl(i,1,n)
	{
		L[i]=R[i-1]+1;
		R[i]=min(n,sq*i);
		minn[i]=1e18;
		forl(j,L[i],R[i])
			b[j]=i,minn[i]=min(minn[i],a[j]),maxn[i]=max(maxn[i],a[j]);
		if(R[i]==n)
			break;
	}
	ll ma1=-1e18,ma2=-1e18;
	forl(i,1,n-2)
	{
		ma1=max(ma1,a[i]);
		ll L=i+1,R=n-1;
		while(L<=R)
		{
			ll Mid=(L+R)/2;
			ll mi1=querymin(i+1,Mid);
			ma2=summax[Mid+1];
			if(mi1==ma1 && mi1==ma2)
			{
				cfy;
				cout<<i<<' '<<Mid-i<<' '<<n-Mid<<endl;
				return ;
			}
			if(mi1<=ma1 && ma2<=ma1)
				R=Mid-1;
			else
				L=Mid+1; 
		}
	}
	cfn;
}
int main()
{
	IOS;
	t=1;
 	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：胖头鱼学员 (赞：3)

# CF1454F

[CF传送门](http://codeforces.com/problemset/problem/1454/F)
[洛谷传送门](https://www.luogu.com.cn/problem/CF1454F)

## $QuestionMeaning$

给定序列$a$，找出任意一组$x$、$y$和$z$（$x$、$y$和$z$为非空字段长度），满足：
$$
\max\limits_{i=1}^x a_i = \min\limits_{i=x+1}^{x+y} a_i = \max\limits_{i=x+y+1}^n a_i 
$$

## $Solution$

考虑暴力及优化：

### 暴力

枚举$x$和$y$，暴力计算三个值，时间复杂度为$O(n^5)$。

### 优化1

$\max\limits_{i=1}^x a_i$可以用**前缀最大值**优化。

时间复杂度为$O(n^4)$

### 优化2

$\max\limits_{i=x+y+1}^n a_i$可以用**后缀最大值**优化。

时间复杂度为$O(n^3)$

### 优化3

$\min\limits_{i=x+1}^{x+y} a_i$可以用**ST表**优化。

时间复杂度为$O(n^2 \log n)$

### 优化4

因为后缀最大值在$x$固定的时候，再从小到大枚举$y$时，它是非递减的，所以可以用**二分查找**优化。

总时间复杂度为$O(n \log^2 n)$。

## $Code$
```
#include <cstdio>
#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b

using namespace std;

const int kMaxN = 5e5 + 1;

int T, n, k, ma;
int log[kMaxN], st[kMaxN][20];
int suf[kMaxN], a[kMaxN];

void CalcSuf() {
  suf[n] = a[n];
  for (int i = n - 1; i; --i) {
    suf[i] = max(suf[i + 1], a[i]);
  }
}

void CalcSt() {
  for (int j = 1; j <= 18; j++) {
    for (int i = 1; i <= n; i++) {
      st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
}

void CalcLog() {
  for (int i = 2; i < kMaxN; i++) {
    log[i] = log[i - 1];
    if (!(i % 2)) {
      log[i] = log[i >> 1] + 1;
    }
  }
}

int Min(int l, int r) {
  int k = log[r - l + 1];
  return min(st[l][k], st[r - (1 << k) + 1][k]);
}

int Find(int le, int ri) {
  int l = le, r = ri;
  while (l + 1 < r) {
    int mid = l + r >> 1;
    int mi = Min(le + 1, mid);
    if (ma > mi) {
      r = mid;
    } else if (ma < mi) {
      l = mid;
    } else {
      if (ma > suf[mid + 1]) {
        r = mid;
      } else if (ma < suf[mid + 1]) {
        l = mid;
      } else {
        return mid;
      }
    }
  }
  return 0;
}

void Solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    st[i][0] = a[i];
  }
  CalcSt();
  CalcSuf();
  k = ma = 0;
  for (int i = 1; i < n; ++i) {
    ma = max(ma, a[i]);
    k = Find(i, n);
    if (k) {
      puts("YES");
      printf("%d %d %d\n", i, k - i, n - k);
      return;
    }
  }
  puts("NO");
}

int main() {
  CalcLog();
  scanf("%d", &T);
  while (T--) {
    Solve();
  }
  return 0;
}
```

---

## 作者：Eibon (赞：2)

发现要维护区间最大值与最小值，于是钦定 st 表。

因为区间扩大时，最大值一定不会变小，最小值一定不会变大，因此区间最大值或者区间最小值会随着区间长度变化变得更大或者更小。

因此可以二分。

不妨从小到大枚举第一个区间。对后两个区间进行二分。

判断第三个区间的最大值、第二个区间的最小值是否都小于或者大于 $a_{i}$。等于的时候返回答案。

如果二者不符合，则无解。因为再接着增大或减少区间长度，都不会使最大值变小，最小值变大。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
const int mod=998244353;
int T,n;
int a[maxn],mx[maxn][20],mn[maxn][20];
int VIP1(int l,int r)
{
	int num=__lg(r-l+1);
	return min(mn[l][num],mn[r-(1<<num)+1][num]);
}
int VIP2(int l,int r)
{
	int num=__lg(r-l+1);
	return max(mx[l][num],mx[r-(1<<num)+1][num]);
}
void SVIP()
{
	for(int i=1;i<=n;i++){
		mn[i][0]=mx[i][0]=a[i];
	}
	for(int x=1;x<=20;x++){
		for(int i=1;i+(1<<x)-1<=n;i++){
			mn[i][x]=min(mn[i][x-1],mn[i+(1<<(x-1))][x-1]);
			mx[i][x]=max(mx[i][x-1],mx[i+(1<<(x-1))][x-1]);
		}
	}
}
void solve()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	SVIP();
	for(int i=1;i<=n-2;i++){
		int mx1=VIP2(1,i);
		int l=i+1,r=n-1;
		while(l<=r){
			int mid=(l+r)>>1;
			int mn1=VIP1(i+1,mid);
			int mx2=VIP2(mid+1,n);
			//cout<<i<<" "<<l<<" "<<r<<" "<<mx1<<" "<<mn1<<" "<<mx2<<endl;
			if(mx1==mx2&&mn1==mx2){
				printf("YES\n%lld %lld %lld\n",i,mid-i,n-mid);
				return;
			}
			else if(mx1>=mx2&&mx1>=mn1){
				r=mid-1;
			}
			else if(mx2>=mx1&&mn1>=mx1){
				l=mid+1;
			}
			else{
				break;
			}
		}
	}
	puts("NO");
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Graphcity (赞：2)

### 思路

首先可以用 $O(n \log n)$ 的时间复杂度 **离散化**  $a$ 数组。

接着，我们可以求出每个前后缀的最大值，并保存在 $pre$ 和 $suf$ 数组中。用这两个数组，我们可以解出每个数字在 $pre$ 和 $suf$ 数组中最晚出现的位置。（ 代码中用数组 $tf,\ tb$ 表示 ）同时还可以求出每个数字在 $a$ 数组中最早出现和最晚出现的位置。（ 代码中用数组 $pf,\ pb$ 表示 ）时间复杂度 $O(n)$ 。

利用 **单调栈** 还可以求出当某个位置的数为最小值时，它前后最长能够延展到哪里。（ 代码中用数组 $fnt,\ nxt$ 表示 ）时间复杂度 $O(n)$ 。

最后，我们依次扫描每个位置。假设扫描到了位置 $i$ ，如果区间 $[1,tf(a_i)]$，$[fnt(i),nxt(i)]$，$[tb(a_i),n]$ 能够相互拼接或者套住，而且 $i$ 在区间 $(pf(a_i),pb(a_i))$ 中，就会有一个合法的解。

下面是一种合法解的演示：

![](https://cdn.luogu.com.cn/upload/image_hosting/3f3iz0f8.png)

选取区间时，只要注意一下这些区间的重叠即可。总时间复杂度 $O(n \log n)$ 。

**思考** / 本题中离散化的作用只是给每个数一个索引，并不需要指示大小关系。也就是说，如果离散化使用哈希，即可将离散化的时间复杂度降至 $O(n)$ ，总时间复杂度也将降至 $O(n)$ 。

这里给出哈希 $O(n)$ 的解法：[There](https://www.luogu.com.cn/paste/qxpwrf54)

### 关键代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=2e5;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int T,n,num[Maxn+5];
int pre[Maxn+5],suf[Maxn+5]; // 最大前后缀
int tf[Maxn+5],tb[Maxn+5]; // 每个数最高能到达的前后缀位置
int pf[Maxn+5],pb[Maxn+5]; // 每个数前后出现的最小位置
int fnt[Maxn+5],nxt[Maxn+5]; // 每个位置的数作为最小值前后能延展到的位置
int st[Maxn+5],top;
vector<int> v;

inline void Solve1() // 求出 pre,suf,tf,tb,pf,pb
{
    for(int i=1;i<=n;++i) pre[i]=max(pre[i-1],num[i]);
    for(int i=n;i>=1;--i) suf[i]=max(suf[i+1],num[i]);
    for(int i=1;i<=n;++i) tf[pre[i]]=i;
    for(int i=n;i>=1;--i) tb[suf[i]]=i;
    for(int i=1;i<=n;++i) if(!pf[num[i]]) pf[num[i]]=i;
    for(int i=n;i>=1;--i) if(!pb[num[i]]) pb[num[i]]=i;
}
inline void Solve2() // 求出 fnt,nxt
{
    for(int i=1;i<=n;++i)
    {
        while(top && num[st[top]]>num[i])
            nxt[st[top--]]=i-1;
        st[++top]=i;
    }
    while(top) nxt[st[top--]]=n;
    for(int i=n;i>=1;--i)
    {
        while(top && num[st[top]]>num[i])
            fnt[st[top--]]=i+1;
        st[++top]=i;
    }
    while(top) fnt[st[top--]]=1;
}
inline int Solve3() // 求解
{
    for(int i=1;i<=n;++i)
    {
        if(!pf[num[i]] || !pb[num[i]]) continue;
        if(!tf[num[i]] || !tb[num[i]]) continue;
        if(i==pf[num[i]] || i==pb[num[i]]) continue;
        if(tf[num[i]]>=fnt[i]-1 && nxt[i]>=tb[num[i]]-1)
        {
            int a,b;
            a=max(pf[num[i]],fnt[i]-1);
            b=max(n-pb[num[i]]+1,n-nxt[i]);
            printf("YES\n%d %d %d\n",a,n-a-b,b);
            return 1;
        }
    }
    return 0;
}
inline void Clear()
{
    v.clear();
    for(int i=1;i<=n;++i)
        pre[i]=suf[i]=tf[i]=tb[i]=0,
        pf[i]=pb[i]=fnt[i]=nxt[i]=0;
}

int main()
{
    T=read();
    while(T--)
    {
        n=read();
        for(int i=1;i<=n;++i)
            v.push_back(num[i]=read());
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        for(int i=1;i<=n;++i)
            num[i]=lower_bound(v.begin(),v.end(),num[i])-v.begin()+1;
        Solve1(),Solve2();
        if(!Solve3()) printf("NO\n");
        Clear();
    }
    return 0;
}
```

---

## 作者：Fan_Tuan (赞：2)

# 题意
给定长度为$n$ 的序列 $a$,寻找$x, y, z$, 使得区间 $[1, x]_{max} = [x + 1, x + y]_{min} = [x + y + 1, n]_{max}$, 若存在输出$YES以及 x ,   y ,   z 。否则输出NO。
# 思路
区间查询最值的话可以用线段树， 枚举每个点，确定$x$, 将剩下的部分进行二分，求出$y, z$ 。判断$x, y, z$ 是否满足条件。

# 代码
```c
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#define INF 100000000
#define int long long
// #define d lld
using namespace std;

const int maxn = 2e5 + 20;
int t, n, a[maxn];

struct node {
    int sum, l, r, minn, maxx;
}tree[maxn << 2];

void pushup (int rt) {
    tree[rt].maxx = max (tree[rt << 1].maxx, tree[rt << 1 | 1].maxx);
    tree[rt].minn = min (tree[rt << 1].minn, tree[rt << 1 | 1].minn);
}

void build (int rt, int l, int r) {
    tree[rt].l = l;
    tree[rt].r = r;
    if (l == r) {
        tree[rt].maxx = a[l];
        tree[rt].minn = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build (rt << 1, l, mid);
    build (rt << 1 | 1, mid + 1, r);
    pushup (rt);
}

int Max (int rt, int L, int R) {
    int l = tree[rt].l;
    int r = tree[rt].r;
    if (l >= L && r <= R) {
        return tree[rt].maxx; 
    }
    int mid = (l + r) >> 1, ans = -1;
    if (L <= mid) ans = max (ans, Max (rt << 1, L, R));
    if (R > mid) ans = max (ans, Max (rt << 1 | 1, L, R));
    return ans;
}

int Min (int rt, int L, int R) {
    int l = tree[rt].l;
    int r = tree[rt].r;
    if (l >= L && r <= R) {
        return tree[rt].minn; 
    }
    int mid = (l + r) >> 1, ans = INF;
    if (L <= mid) ans = min (ans, Min (rt << 1, L, R));
    if (R > mid) ans = min (ans, Min (rt << 1 | 1, L, R));
    return ans;
}

signed main () {
    scanf ("%d", &t);
    while(t--)
    {
        memset (a, 0, sizeof a);
        scanf ("%d", &n);
        for (int i = 1; i <= n; i++) scanf ("%d", &a[i]);
        build(1, 1, n);
        int maxx1, maxx2, minn1, l, r, flag = 0;
        for(int i = n - 2; i >= 1; i--)
        {
            maxx1 = Max(1, 1, i);
            l = i + 1, r = n - 1;
            while(l <= r)
            {
                int mid = (l + r) >> 1;
                maxx2 = Max(1, mid + 1, n), minn1 = Min(1, i + 1, mid);
                if(maxx1 == maxx2 && maxx1 == minn1)
                {
                    l = mid;
                    break;
                }
                if(maxx1 >= maxx2 && maxx1 >= minn1)
                    r = mid - 1;
                else if(maxx1 <= maxx2 && maxx1 <= minn1)
                    l = mid + 1;
                else
                    r = 0;
            }
            if(l <= r)
            {
                puts ("YES");
                printf("%d %d %d\n", i, l - i, n - l);
                flag = 1;
                break;
            }
        }
        if(flag == 0) puts("NO");
    }
    return 0;
}
```


---

## 作者：Unordered_OIer (赞：1)

# CF1454F 题解
一道思维难度比较简单的 F？

## Description
问能否能够将序列 $a_1...a_n$ 切割成三段，使得

$$\max\limits_{i=1}^xa_i=\min\limits_{i=x+1}^{x+y}a_i=\max\limits_{i=x+y+1}^na_i$$

说人话：使得第一段的最大值=第二段的最小值=第三段的最大值。

如果能够成立，则构造方案。

## Solution
首先看到三个最大值最小值，并且数据范围是 $2 \times 10^5$，我们就直接想到了 $\text{ST}$ 表来求最大值和最小值。

### Algorithm 1

先考虑暴力，直接暴力枚举 $x,y$，然后根据 $\text{ST}$ 表验证即可，复杂度 $\mathcal O(n^2 \log n)$。

### Algorithm 2

首先我们很难不枚举 $x,y$ 就算出答案，所以我们不可避免地要花 $\mathcal O(n)$ 的时间枚举一个 $x$，所以我们的思路就是要降低枚举 $y$ 的复杂度。

然后我们观察到，无论是 $\min$ 的序列长度增加，还是 $\max$ 的序列长度增加，$\min$ 值一定更小，$\max$ 值一定更大。换句话说，它们都满足单调性。

于是我们就想到了**二分**，在 $\mathcal O(\log n)$ 的时间内把这个 $y$ 二分出来即可。

那么总复杂度就是 $\mathcal O(n \log^2 n)$。

## Code
```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(ll x){write(x),putchar('\n');}
ll T,n,a[N],lg[N],mx[30][N],mn[30][N],nowmx,nowmn;
inline void LOG(){
	lg[1]=0;
	for(ll i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
}
inline void ST(){
	for(ll i=1;i<=n;i++)mx[0][i]=mn[0][i]=a[i];
	ll h=lg[n];
	for(ll i=1;i<=h;i++)
		for(ll j=1;j<=n-(1<<i)+1;j++){
			mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<(i-1))]);
			mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<(i-1))]);
		}
}
inline ll qmax(ll l,ll r){
	ll p=lg[r-l+1];
	return max(mx[p][l],mx[p][r-(1<<p)+1]);
}
inline ll qmin(ll l,ll r){
	ll p=lg[r-l+1];
	return min(mn[p][l],mn[p][r-(1<<p)+1]);
}
inline ll binsearch(ll nl,ll nr){
	ll l=nl,r=nr;
	while(l+1<r){
		ll mid=(l+r)>>1;
		nowmn=qmin(nl+1,mid);
		if(nowmn<nowmx)r=mid;
		else if(nowmx<nowmn)l=mid;
		//不等
		else{
			ll tmp=qmax(mid+1,n);
			if(nowmx>tmp)r=mid;
			else if(nowmx<tmp)l=mid;
			else return mid;//=
		}
	}
	return -1;//no result
}
inline void solve(){
	n=read();nowmx=nowmn=0;
	for(ll i=1;i<=n;i++)a[i]=read();
	LOG();ST();
	for(ll i=1,nowres=0;i<n;i++){
		nowmx=max(nowmx,a[i]);
		nowres=binsearch(i,n);
		if(nowres!=-1){
			puts("YES");
			ll x=i,y=nowres-i,z=n-nowres;
			write(x),putchar(' '),write(y),putchar(' '),writeln(z);
			return;
		}
	}
	puts("NO");
}
int main(){
	T=read();
	while(T--)solve();
	return 0;
}
```

快来和我一起膜拜 $\mathsf{\color{black}R\color{red}olling\_Code}$ 吧，虽然这篇题解除了名字和 T♂A♀ 没有任何关系。

---

## 作者：H6_6Q (赞：1)

#### 题目大意

把一个数列划分成三段，使得 第一段的 $\max=$ 第二段的 $\min=$ 第三段的 $\max$

#### 解题思路

我们假设第一段和第二段的分解点是 $x$，第二段和第三段的分解点是 $y$。

我们可以枚举第一段和第二段的分界点 $x$ ，这样就知道了要使第二段的 $\min$ 和第三段的 $\max$ 要等于的值。

可以先考虑如何让第二段的 $\min$ 与 第一段的 $\max$ 相等。

由于第二段区间 $[x,y]$ 的 $\min$ 一定是单调不升的，所以可以二分这个位置，这样就能在找到一个区间 $[p,q]$ ，在这个区间选第二段和第三段的分界点，就能保证第二段的 $\min$ 与 第一段的 $\max$ 相等。

再考虑如何保证第三段的 $\min$ 与 第一段的 $\max$ 相等。

其实刚才求出的区间 $[p,q]$ 的 $\max$ 也是单调不降的，所以依旧可以二分。

如果能找到，那么直接输出这个方案就行了。

二分的时候要维护区间极值，可以直接套一个 st表 或 线段树。

时间复杂度 $\text{O}(n\ \log^2n)$

#### Code
```cpp
const int N=2e5+5;
int t,n,a[N],val[N*4],suc[N],flag;
 
void build(int x,int l,int r);
int query(int x,int l,int r,int L,int R);
inline int binary1(int x,int p);
inline int binary2(int x,int l,int r);
 
signed main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;++i)
			a[i]=read();
		build(1,1,n);
		for(int i=n;i>=1;--i)
			suc[i]=max(suc[i+1],a[i]);
		int now=0;flag=0;
		for(int i=1;i<=n;++i)
		{
			now=max(now,a[i]);
			int pos1=binary1(now,i+1)+1;
			int pos2=binary1(now+1,i+1)+2;
			if(pos1==-1) continue;
			if(pos2==0) pos2=i+2;
			if(pos1>n) pos1=n; 
			if(pos2>n) pos2=n;
			int pos3=binary2(now,pos2,pos1);
			if(pos3==-1) continue;
			if(i<=0||pos3-1-i<=0||n-(pos3-1-i)-i<=0) continue;
			if(suc[pos3]!=now||query(1,1,n,i+1,pos3-1)!=now)
				continue;
			printf("YES\n%lld %lld %lld\n",i,pos3-1-i,n-(pos3-1-i)-i);
			flag=1;break;
		}
		if(flag==0) printf("NO\n");
		for(int i=1;i<=n;++i)
			suc[i]=0;
	}
	return 0;
}
 
void build(int x,int l,int r)
{
	if(l==r)
	{
		val[x]=a[l];
		return;
	}
	build(lc,l,mid);
	build(rc,mid+1,r);
	val[x]=min(val[lc],val[rc]);
}
 
int query(int x,int l,int r,int L,int R)
{
	if(L<=l&&r<=R) return val[x];
	int res=1e18;
	if(L<=mid) res=min(res,query(lc,l,mid,L,R));
	if(mid+1<=R) res=min(res,query(rc,mid+1,r,L,R));
	return res;
}
 
inline int binary1(int x,int p)
{
	int l=p,r=n,res=-2;
	while(l<=r)
	{
		if(query(1,1,n,p,mid)>=x)
		{
			res=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return res;
}
 
inline int binary2(int x,int l,int r)
{
	int res=-1;
	while(l<=r)
	{
		if(suc[mid]<=x)
		{
			res=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return res;
}
```

---

## 作者：yr409892525 (赞：0)

### 题解：CF1454F Array Partition
我们可以枚举 $x$。          
这样子就可以得到 $\max(1,x)$ 的值。           
发现固定左端点，长度越长，最小值越小。           
所以，我们可以二分 $y$，再用 ST 表维护区间最小值和区间最大值。            
当 $\min(x+1,x+y) \ge \max(1,x)$ 且 $\min(x+y+1,n) \ge \max(1,x)$，说明最小值太大，最大值又太小了，增加最小值的长度，减小最大值的长度。              
当 $\min(x+1,x+y) \le \max(1,x)$ 且 $\min(x+y+1,n) \le \max(1,x)$，说明最小值太小，最大值又太大了，减小最小值的长度，增加最大值的长度。              

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,M=30,inf=1e9;
int n;
int a[N],b[N];
int dp[2][N][M];
int lg[N],pw[M];
void init(){
	lg[0]=-1;
	for(int i=1;i<N;i++){
		lg[i]=lg[i/2]+1;
	}
	pw[0]=1;
	for(int i=1;i<M;i++){
		pw[i]=pw[i-1]*2;
	}
	return ;
}
void st_init(){
	int len=lg[n];
	for(int j=1;j<=len;j++){
		for(int i=1;i+pw[j]-1<=n;i++){
			dp[0][i][j]=min(dp[0][i][j-1],dp[0][i+pw[j-1]][j-1]);
			dp[1][i][j]=max(dp[1][i][j-1],dp[1][i+pw[j-1]][j-1]);
		}
	}
	return ;
}
int Min(int l,int r){
	int x=lg[r-l+1];
	return min(dp[0][l][x],dp[0][r-pw[x]+1][x]);
}
int Max(int l,int r){
	int x=lg[r-l+1];
	return max(dp[1][l][x],dp[1][r-pw[x]+1][x]);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    int q;
    cin>>q;
    init();
    while(q--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            dp[0][i][0]=dp[1][i][0]=a[i];
        }
        st_init();
        bool f=0;
        for(int i=1;i<=n-2 && !f;i++){
            int l=i,r=n;
            while(l+1<r && !f){
                int mid=(l+r)/2;
                int x=Max(1,i),y=Min(i+1,mid),z=Max(mid+1,n);
                if(x==y && y==z){
                    f=1;
                    cout<<"YES\n"<<i<<" "<<mid-i<<" "<<n-mid<<"\n";
                }
                // cout<<i<<" "<<x<<" "<<y<<" "<<z<<" "<<mid<<"\n";
                if(y>=x && z>=x) l=mid;
                else if(y<=x && z<=x) r=mid;
                else break;
            }
        }
        if(!f) cout<<"NO\n";
    }
	return 0;
}
```

---

## 作者：Svemit (赞：0)

[link](https://www.luogu.com.cn/problem/CF1454F)

[更好的阅读体验](https://www.cnblogs.com/Svemit/p/17802573.html)

# Soltion：

有一个比较显然的 $O(n^2)$ 做法，枚举中间区间的左右端点，然后用前后缀 $\max$ 和 st 表查询中间的 $\min$,其实不用 st 表也行，确定左端点枚举右端点的时候顺便求一下就好。

考虑枚举左端点，以一个较快的方法求出右端点。

发现后缀 $\max$ 和 确定左端点后的 $\min_{i=l}^{r} a_i$ 都是具有单调递减的，可以二分来做。

我们设前缀 $\max$ 为 $a$，$\min_{i=l}^{r} a_i$ 为 $b$，以及后缀 $\max$ 为 $c$。

如果 $a = b = c$ 时直接输出即可。

如果 $a > b, a < c$ 或者 $a < b, a > c$ 这样的话是无解的，因为一个需要变大而一个需要变小，但是 $b,c$ 都是单调递减的，所以不可能有三者相等的情况了。

对于 $b,c$ 在 $a$ 的同一侧的情况比较简单，直接缩小二分区间就好。

```cpp
void solve() {
	int n;
	cin >> n;
	vector<int> a(n + 1), pre(n + 1), suf(n + 1);
	vector<vector<int> > f(n + 1, vector<int>(__lg(n) + 1));
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n)
		pre[i] = (i == 1 ? a[1] : max(pre[i - 1], a[i]));
	per(i, n, 1)
		suf[i] = (i == n ? a[n] : max(suf[i + 1], a[i]));
	rep(i, 1, n) 
		f[i][0] = a[i];
	rep(j, 1, __lg(n)) 
		rep(i, 1, n - (1 << j) + 1) 
			f[i][j] = min(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
	auto query = [&](int l, int r) {
		int k = __lg(r - l + 1);
		return min(f[l][k], f[r - (1 << k) + 1][k]);
	};
	rep(i, 1, n - 2) {
		int a = pre[i];
		int l = i + 1, r = n - 1, res = -1;
		while(l <= r) {
			int mid = l + r >> 1;
			int b = query(i + 1, mid), c = suf[mid + 1];
			if((b < a && c > a) && (b > a && c < a)) break;
			if(b == a && c == a) {
				cout << "YES\n";
				cout << i << ' ' << mid - i << ' ' << n - mid << '\n';
				return;
			}
			if(b <= a && c <= a) r = mid - 1;
			else l = mid + 1;
		}
	}
	cout << "NO\n";
}
```


---

## 作者：QQH08 (赞：0)

首先有 $1$ 个很显然的性质。在一个端点固定的时候：

长度越长，max 越大，min 越小。

然后，我们记 $\max(l,r)$ 为 $l\to r$ 的最大值。

所以，我们对这道题先枚举 $x$（即第一个子串的右端点），记 $\max(1,x)$ 为 $val$。那么，肯定有一段连续区间的 $i$ 满足 $\max(i,n)$ 都等于 $val$。所以我们预处理后缀最大值，二分这段区间的左右端点，记为 $ql$,$qr$。

可以发现，第二段的子串的右端点必须在 $[ql-1,qr-1]$ 之间。而由于它的左端点固定为 $x+1$，所以它的最小值也是单调的。再考虑二分即可。

前缀最大值和后缀最大值都可以预处理，那么中间一段的最小值怎么办呢？这么多询问当然用 st 表预处理啦。

完结撒花。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500005;
int T,n,flag,a[N],lg[N],s1[N],s2[N],Min[N][20];
int calc(int l,int r){
    int x=lg[r-l+1];
    return min(Min[l][x],Min[r-(1<<x)+1][x]);
}
int main(){
    scanf("%d",&T);
    while(T--){
        lg[0]=-1;flag=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
		    lg[i]=lg[i/2]+1;
        }
        s1[1]=a[1],s2[n]=a[n];
        for(int i=2;i<=n;i++)
            s1[i]=max(s1[i-1],a[i]);
        for(int i=n-1;i>=1;i--)
            s2[i]=max(s2[i+1],a[i]);
        for(int i=1;i<=n;i++)Min[i][0]=a[i];
        for(int i=1;i<=lg[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)
                Min[j][i]=min(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
        for(int i=1;i<=n;i++){
            int l=i+2,r=n,pl=-1,pr=-1,res=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(s2[mid]==s1[i]){
                    pl=mid;
                    r=mid-1;
                }
                else if(s2[mid]<s1[i])r=mid-1;
                else l=mid+1;
            }
            if(pl==-1)continue;
            l=i+2,r=n;
            while(l<=r){
                int mid=(l+r)>>1;
                if(s2[mid]==s1[i]){
                    pr=mid;
                    l=mid+1;
                }
                else if(s2[mid]<s1[i])r=mid-1;
                else l=mid+1;
            }
            // cout<<i<<":"<<pl<<" "<<pr<<endl;
            l=pl-1,r=pr-1;
            if(l==i)continue;
            while(l<=r){
                int mid=(l+r)>>1;
                if(calc(i+1,mid)==s1[i]){
                    res=mid;
                    break;
                }
                else if(calc(i+1,mid)<s1[i])r=mid-1;
                else l=mid+1;
            }
            if(res!=-1){
                flag=1;
                puts("YES");
                printf("%d %d %d\n",i,res-i,n-res);
                break;
            }
        }
        if(!flag)puts("NO");
    }
    return 0;
}
```


---

## 作者：little_sun (赞：0)

### 题目大意

给定一个长度为 $n$ 的序列 $a$ ，要求将其划分为三个非空字串，长度分别为 $x, y, z$ ，满足：
$$
\max_{i=1}^x a_i = \min_{i=x+1}^{x+y}a_i = \max_{i=x+y+1}^n a_i
$$
若存在方案，输出 $\texttt{YES}$ 和任意一组  $x, y, z$  的值；若不存在，输出 $\texttt{NO}$。

$3 \leq n \leq 2 * 10^5, 1 \leq a_i \leq 10^9$

### 题目分析

已经有很多题解做法是枚举 $x$ 了，这里提供一种另类的做法。

我们考虑对于 $\forall i \in [2,n-1]$ 的$i$，检测 $a_i$ 作为 $\min_{i=x+1}^{x+y}a_i$ 是否可行。

首先我们可以预处理出每个 $i$ 左右比他小的第一个数，可在 $ \Theta(n) $ 时间内使用单调栈处理出。

接着我们预处理出前缀和后缀最大值，这样就可以用二分处理出以 $a_i$ 为最大值的最长/最短前/后缀长度。

在处理出这些东西后，我们就可以根据这些信息来快速判断一个位置是否可行（具体实现参见代码）。

由于我们只要输出任意一组答案，故我们可以在找到可行的 $i$ 之后枚举 $x, y$ ，总时间复杂度  $\Theta(n \log n)$。

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)
#define meow(cat...) fprintf(stderr, cat)

const int MaxN = 4e5 + 10;

std::vector<int> v;
std::unordered_map<int, int> cnt;
int premax[MaxN], sufmax[MaxN];
int n, flag, a[MaxN], l[MaxN], r[MaxN];

void init()
{
    cnt.clear();
    for(int i = 0; i <= n + 9; i++)
        l[i] = r[i] = premax[i] = sufmax[i] = 0;
}

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}

signed main()
{
    int T = read();
    while (T--)
    {
        n = read(), flag = 0, init();
        for (int i = 1; i <= n; i++)
            a[i] = read(), cnt[a[i]] += 1, 
                premax[i] = std::max(premax[i - 1], a[i]);
        v.clear(), v.push_back(0);
        for(int i = 1; i <= n; i++)
        {
            while(v.size() && a[v.back()] >= a[i])
                 v.pop_back();
            l[i] = v.back(), v.push_back(i);
        }
        v.clear(), v.push_back(n + 1);
        for(int i = n; i; i--)
        {
            while(v.size() && a[v.back()] >= a[i])
                v.pop_back();
            r[i] = v.back(), v.push_back(i);
        }
        for(int i = n; i; i--)
            sufmax[i] = std::max(sufmax[i + 1], a[i]);
        std::reverse(sufmax + 1, sufmax + n + 1);
        for(int i = 2; i < n; i++)
        {
            int l1 = std::lower_bound(premax + 1, premax + n + 1, a[i]) - premax;
            int r1 = std::upper_bound(premax + 1, premax + n + 1, a[i]) - premax - 1;
            int r2 = n + 1 - (std::lower_bound(sufmax + 1, sufmax + n + 1, a[i]) - sufmax);
            int l2 = n + 1 - (std::upper_bound(sufmax + 1, sufmax + n + 1, a[i]) - sufmax) + 1;
            // meow("$ %d %d %d %d %d %d %d %d\n", i, a[i], l1, r1, l2, r2, l[i], r[i]);
            if(l[i] > r1 || l1 > r[i] || l[i] > r2 || l2 > r[i] || l1 >= i || r2 <= i
                || l1 > r1 || l2 > r2 || cnt[a[i]] < 3) { /*meow("-1\n");*/ continue; }
            // if(premax[l1] != a[i] || premax[r1] != a[i] || 
            //     sufmax[l2] != a[i] || sufmax[r2] != a[i]) { meow("-2\n"); continue; }
            int a = 0, b = 0;
            for(int j = i - 1; j >= l[i]; j--)
                if(l1 <= j && j <= r1)
                    if(l[i] <= j + 1 && j + 1 <= r[i]) { a = j; break; }
            for(int j = i - a; a + j <= r[i]; j++)
                if(l2 <= j + a + 1 && j + a + 1 <= r2)
                    if(l[i] <= j + a && j + a <= r[i]) { b = j; break; }
            // if((!(a < i && i <= a + b)) || a == 0 || b == 0) { /*meow("%d %d -3\n", a, b);*/ continue; }
            printf("YES\n%d %d %d\n", a, b, n - a - b), flag = 1; break;
        }
        if(!flag) puts("NO");
    }
    return 0;
}
```



---

