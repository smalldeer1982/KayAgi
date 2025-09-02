# Kefa and Company

## 题目描述

Kefa 想要去餐馆庆祝一下，他有 $n$ 个朋友，每个朋友有一定的友谊值和工资。没人想觉得自己穷，所以 Kefa 邀请的朋友中两两工资差小于 $d$。现在给出朋友的信息，请求出最大友谊值是多少。

## 样例 #1

### 输入

```
4 5
75 5
0 100
150 20
75 1
```

### 输出

```
100
```

## 样例 #2

### 输入

```
5 100
0 7
11 32
99 10
46 8
87 54
```

### 输出

```
111
```

# 题解

## 作者：hank0402 (赞：6)

### 思路简述：

如果要切掉这题，对于答案区间 $[l,r]$ 首先要解决两个问题：

- 如何快速求出友谊值总和。
- 如何快速求出最大的工资差。

对于第一个问题，前缀和即可。

对于第二个问题，对工资进行排序，直接做减法即可。

>这里需要注意的是，必须排完序后做前缀和，否则数组下标不对应会WA.

最后，只要运用[尺取法](https://baijiahao.baidu.com/s?id=1615129382322508344&wfr=spider&for=pc)来**优化枚举**就行了。

这题很明显是**同向尺取法**，即双指针往一个方向移动。

枚举左端点。

当 $\text{sum}[r] - \text{sum}[l-1] <d$ 时，符合条件，更新答案，将右端点右移，探查是否有更长的符合条件的区间。

否则退出 $\text{while}$ 循环，进行下一次 $\text{for}$ 循环，即将左端点右移，表示用刚才的左端点已经枚举完毕。

最后输出答案即可。

>尺取法优化的方法是如果该区间 $[l,r]$ 不满足，那么 $[l,l\to r-1]$ 的所有区间一定不满足，所以可以不用把右端点从头枚举。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //不开longlong见祖宗
const int maxn = 1e5 + 10;
int n, d, ans, sum[maxn];
struct node {
	int x, y; // x is money;
}a[maxn]; 
bool cmp(node _x, node _y) {
	return _x.x < _y.x;
} 
signed main(){
	cin >> n >> d;
	for(int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i].y; //获取前缀和，注意一定要在排序之后
	int r = 1;
	for(int l = 1; l <= n; ++l) {
		while(r <= n && a[r].x - a[l].x < d) { //不满足退出
			ans = max(ans, sum[r] - sum[l - 1]);
			r ++; //满足条件，继续寻找
		}
	}
	cout << ans;
	return 0;
}

```

---

## 作者：信息向阳花木 (赞：4)


~~楼上大佬题解写得太深奥了，像我这样的小蒟蒻看不懂啊。所以我来写一篇题解，让和我一样弱的人都能够看懂。~~

------------

> 没人想觉得自己穷，所以 Kefa 邀请的朋友中两两工资差小于 $d$。

针对这个问题，我们要对 $n$ 个人的 **工资** 排序。接下来我们对工资差的问题就很好控制了。

由于还要求友谊和，所以我们还要对友谊值算前缀和。

接下来就是滑动窗口了。

滑动窗口这个算法十分简单，拿这道题来说：

首先有两个指针 $l$ 和 $r$。

然后 $l,r$ 移动过程中分两种情况：

* $r$ 和 $l$ 的工资差小于 $d$，那么 $r \gets r + 1$。

* $r$ 和 $l$ 的工资差大于等于 $d$，那么 $l \gets l + 1$。

那么这个算法的时间复杂度是多少？它为什么是正确的？

这题滑动窗口对于每一个点 $l$，极限的 $r$ 就是 $l$ 的最优值（就是说从 $l$ 开始选，最多只能选到 $r$）。等到 $r$ 和 $l$ 的工资差大于等于 $d$， 马上开始算的就是 $l + 1$ 的最优值了。这也有一点点贪心的思想（能选的朋友尽量选）。

这题滑动窗口的时间复杂度是 $O(n)$，因为每个数最多进窗口一次、出窗口一次（众所周知，时间复杂度是忽略常数的）。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,d,l=1,r=1;
long long s[100010],ans;
struct node{
	int m,s;
}a[100010];
bool cmp(node x,node y){ //按工资升序排序。 
	return x.m<y.m;
}
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i].m>>a[i].s;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+a[i].s;//友谊值算前缀和。 
	}
	while(l<=n&&r<=n){//滑动窗口。 
		if(a[r].m-a[l].m<d){ans=max(ans,s[r]-s[l-1]);r++;}//如果可以从 l 选到 r 的话，就可以那它们的友谊和跟 ans 取 max。
		else l++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：JimmyQ (赞：2)

# CF580B Kefa and Company

### 前言。

其实本题与[这道题](https://www.luogu.com.cn/problem/P1147)极为相似，所以建议降橙。

## 思路

因为输入顺序不影响就结果，所以可以先给 $a$ 按照工资从小到打排序一下序（这里 $a$ 使用 MAP）。然后再使用尺取法，只要 $a_{r+1}$ 的值减 $a_l$ 的值 $\lt k$ 就将 $r$ 加 $1$。然后发现每次都暴力统计友谊值会超时，所以可以用前缀和：$sum_i$ 用来记录前 $i$ 个数的和。

## AC 代码

```
#include<bit/stdc++.h>
using namespace std
#define N 100005
long long t,mx,n,k,x,sum[N];
struct node{
	long long num,val;
}a[N];
void two_pointer(){
    for(long long l=1,r=0;l<=n;l++){
        while(r<n&&a[r+1].num-a[l].num<k){
        	r++;
		}
		mx=max(mx,sum[r]-sum[l-1]);
    }
    return;
}
bool cmp(node a,node b){
	return a.num<b.num;
}
void read(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i].num>>a[i].val;	
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i].val;
}
void init(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
}
int mian(){
	init();
	read();
	two_pointer();
	cout<<mx<<endl;	
}
```

珍爱生命，请勿抄袭（抄抄试试？）。

[AC 记录](https://codeforces.com/contest/580/submission/301587565)

---

## 作者：墨舞灵纯 (赞：2)

==作为本题的翻译者我觉得我有义务发表本题的第一篇题解==

本题的题意比较清晰，就是给定一些人的钱和贡献，选取一些人让他们的钱之差不超过d，使贡献最大。开始我想到了dp，看到n<=10^5放弃了，然后写了个无脑二分发现T了。于是我就开始认真思考正解到底怎么写。

首先让这些人两两钱数差小于d，说明最大-最小值<d，那么显然想到按照钱数排序，选取一段区间，让这段区间的贡献最大。仔细分析一下我们可以采用尺取法。关于尺取法请戳[这里](https://www.luogu.org/blog/Nero-Yuzurizaki/chi-qu-fa-xiao-jie)，我就不在此赘述了。

那么这题用尺取法怎么做呢？肯定是维护一个区间[l,r]，让这段区间的最大值-最小值维护在d以内。所以把每个人的钱排个序，每次移动[l,r]的时候计算这一段区间的贡献。显然由于线性扫一遍，所以贡献可以提前用前缀和求好，这样会减少不必要的工作量，时间复杂度就被降下来了。

最后一个小细节，就是开longlong。第一次实现的时候没开，然后第7个点就WA了。

Code如下:

```
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN=1000005;
int n,d,l,r;
long long ans,s[MaxN];
struct node{
	int s,m;
}a[MaxN];
bool cmp(node p,node q)
{
	return p.m<q.m;
}
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].m,&a[i].s);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+a[i].s;
	l=1,r=1;
	while(r<=n)
    {
		if(a[r].m-a[l].m<d)
        {
        		ans=max(s[r]-s[l-1],ans);
                ++r;
         }
       	 else ++l;
    }
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Little09 (赞：2)

这题有的唯一的题解是尺取法做的，其实这题也可以简单地二分查找。（然而其实不比尺取法实现容易）

先说明，翻译有误：`两两工资差不超过d` 应为 `工资差值小于d`。

两两的差其实转化为最大和最小的差。那么我们先对所有人按工资排序，然后枚举最小的人是谁，在他工资上加 $d$，然后找到小于这个值的人并求和。这可以用二分查找找到小于这个值的最大工资的人，求和的话可以前缀和。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long d;
struct point
{
	long long x,y;
}a[100005];
long long s[100005],ans;
bool cmp(point x,point y)
{
	return x.x<y.x;
}
int find(long long x)
{
	int l=1,r=n;
	while (l<=r)
	{
		int mid=(l+r)/2;
		if (a[mid].x>=x) 
		{
			r=mid-1;
		}
		else l=mid+1;
	}
	return r;
} 
int main()
{
	cin >> n >> d;
	for (int i=1;i<=n;i++) cin >> a[i].x >> a[i].y;
	sort(a+1,a+n+1,cmp);
	for (int i=1;i<=n;i++) s[i]=a[i].y+s[i-1];
	for (int i=1;i<=n;i++)
	{
		long long p=a[i].x+d;
		int u=find(p);
		ans=max(ans,s[u]-s[i-1]);
	}
	cout << ans;
 	return 0;
}
```


---

## 作者：Mine_King (赞：1)

这题的条件其实就是在说，选的朋友中，工资最大的和工资最小的差要**小于** $d$。那么就很容易想到尺取法。  
我们根据工资把这些朋友排序，然后用尺取法来统计答案。也就是，每次右指针 $r$ 往右移，如果 $m_r-m_l>=d$，我们就把左指针 $l$ 往右移，$l$ 右移结束后统计答案即可。

code：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,d,l=1,r;
long long sum,ans;
struct node
{
	int m,s;
}a[100005];
bool cmp(node x,node y){return x.m<y.m;}
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].m,&a[i].s);
	sort(a+1,a+n+1,cmp);
	while(r<n)
	{
		r++;
		sum+=a[r].s;
		while(a[r].m-a[l].m>=d) sum-=a[l].s,l++;
		if(sum>ans) ans=sum;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：songtaoran (赞：0)

我有两个时间复杂度通过本题，于是我分别说明。  
### $O(n \times \log n)$  
**二分+前缀和**  
枚举最低工资，二分最大工资。如果最大工资减去最小工资 $< d$，则与答案取最大值即可，这里此时的答案要用一个前缀和来维护。注意要先对拥有的钱数排序。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n, d, sum[100010];
struct node{
	ll money, fri; // 注意不能取名为 "friend"
	bool operator < (const node &t)const{ // 排序 
		return money < t.money;
	}
}a[100010];
/*
bool cmp(node x, node y){
	return x.money < y.money;
}
*/
int main(){
	cin >> n >> d;
	for(ll i = 1; i <= n; i++) scanf("%lld %lld", &a[i].money, &a[i].fri);
	sort(a + 1, a + n + 1); // 排序
	for(ll i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i].fri; // 前缀和
	ll ans = 0;
	for(ll i = 1; i <= n; i++){ // 枚举钱数最小值 
		ll l = i, r = n;
		while(l < r){
			ll mid = (l + r + 1) >> 1; // 注意 +1 
			if(a[mid].money - a[i].money < d) l = mid;
			else r = mid - 1;
		} // 枚举钱数最大的位置  
		ans = max(ans, sum[l] - sum[i - 1]); // 取 max 
	}
	cout << ans << endl; // 输出 
	return 0;
}
```
[提交记录 - $280026575$](https://codeforces.com/problemset/submission/580/280026575)
### $O(n)$  
**双指针+前缀和**  
枚举左端点，如果此时右端点满足条件，则对答案取最大值，也需要维护一个前缀和。如果不满足条件，直接移动左端点即可。  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n, d, sum[100010];
struct node{
	ll money, fri;
	bool operator < (const node &t)const{
		return money < t.money;
	}
}a[100010];
int main(){
	cin >> n >> d;
	for(ll i = 1; i <= n; i++) scanf("%lld %lld", &a[i].money, &a[i].fri);
	sort(a + 1, a + n + 1);
	for(ll i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i].fri;
	ll l = 1, r = 1, ans = 0;
	while(l <= n && r <= n){ // 注意两端点都不能出界
		if(a[r].money - a[l].money >= d) l++;
		else{
			ans = max(ans, sum[r] - sum[l - 1]);
			r++;
		}
	}
	cout << ans << endl;
	return 0;
}
```
[提交记录 - $280027660$](https://codeforces.com/problemset/submission/580/280027660)

---

## 作者：ttq012 (赞：0)

大水题。

容易发现在最低工资确定的情况下，一定是能多人就多人。所以考虑枚举最低的工资的人是谁，然后二分找出可以选择的最高的工资的人，用一个前缀和求出答案即可。

时间复杂度为 $O(n\log n)$。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define em emplace_back
#define F(i,x,y) for(int i=x;i<=y;i++)
#define G(i,x,y) for(int i=x;i>=y;i--)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
#ifdef int
#define inf (7611257611378358090ll/2)
#else
#define inf 0x3f3f3f3f
#endif
using namespace std;
const int N = 1000100;
struct Node {
    int m, s;
} z[N];
int su[N];
auto main() [[O3]] -> signed {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    T = 1;
    while (T--) {
        int n, d;
        cin >> n >> d;
        F(i, 1, n) {
            cin >> z[i].m >> z[i].s;
        }
        stable_sort(z + 1, z + n + 1, [&](auto l, auto r) {
            return l.m < r.m;
        });
        F(i, 1, n) { 
            su[i] = su[i - 1] + z[i].s;
        }
        int mx = 0;
        F(i, 1, n) {
            int l = i + 1, r = n, best = i;
            while (l <= r) {
                int mid = l + r >> 1;
                if (z[mid].m - z[i].m < d) {
                    best = mid, l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            mx = max(mx, su[best] - su[i - 1]);
        }
        cout << mx << '\n';
    }
}
```

---

## 作者：Loser_Syx (赞：0)

考虑需要选出的人两两工资差小于 $d$，因为工资最多的人减去工资最少的人的差值一定是最大的，所以我们仅需变相检查 $\max-\min$ 是否 $<d$ 即可。

因为选出来的一定是一段 $m_i$ 连续的区间，且 $\max-\min<d$，我们不妨枚举一个 $\min$ 值，然后再在排序后的数组中查询最后一个 $< \min +\ d$ 的数，由于 $s_i \geq 0$，所以区间总是越长越好（固定左端点的情况下长度越长 $s_i$ 总和越大）。可以二分决定。

二分完右端点，考虑查询 $[l,r]$ 中的值总和，显然不能暴力看，但是发现可以使用前缀和预处理，做完了。

复杂度 $O(n \log n)$。

二分最后一个 $< \min+\ d$ 的数等价于第一个 $\geq \min +\ d$ 的数的前一个。

```cpp
pair<int, int> p[101010];
int sum[101010], a[101010]; 
signed main() {
	int n, d; read(n, d);
	for (int i=1;i<=n;++i) read(p[i].first, p[i].second);
	sort(p+1,p+1+n);
	int ans=0;
	for (int i=1;i<=n;++i) {
		sum[i]=sum[i-1]+p[i].second;
		a[i]=p[i].first;
	}
	for (int i=1;i<=n;++i) {
		int w=lower_bound(a+i,a+n+1,a[i]+d)-a-1;
		smax(ans,sum[w]-sum[i-1]);
	}
	write(ans,'\n');
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路

先按价值排序，这样保证每一个人财富合法。
接着枚举每一个子串，求最大值。


记得使用前缀和优化，否则会超时。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,d,ans=-1;
struct node{int m,s;}a[100010];
bool cmp1(node x,node y)
{return x.m<y.m;}
int qzh[100010];//前缀和优化


inline int read(){
    
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}


signed main()
{
	n=read(),d=read();
	for(int i=1;i<=n;i++)
		a[i].m=read(),a[i].s=read();
	sort(a+1,a+n+1,cmp1);
	int l=1,r;
	qzh[0]=0;
	for(int i=1;i<=n;i++)//排序完前缀和
		qzh[i]=qzh[i-1]+a[i].s;
	for(l=1;l<=n;l++)
	{
		for(;r<=n&&abs(a[r].m-a[l].m)<d;r++)
		{//枚举每一个串
      //不需要重置 r 否则 TLE
			ans=max(ans,qzh[r]-qzh[l-1]);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：osfly (赞：0)

见到有单调性、有限制的区间问题，很自然地就会想到用尺取去做。

先按工资升序排序，然后套上尺取就行了。

[不会尺取的可以根据这道题去学。](https://www.luogu.com.cn/problem/P1638)

时间复杂度 $O(n\log n)$。

```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1e5+10;
int n,d;
struct Friend
{
	int m,s;
}f[N];
bool cmp(Friend a,Friend b)
{
	return a.m<b.m;
}
ll sum[N];
ll ans;
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++) scanf("%d%d",&f[i].m,&f[i].s);
	sort(f+1,f+1+n,cmp);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+f[i].s;
	int l=1,r=1;
	while(l<=n)
	{
		while(f[r].m-f[l].m<d&&r<=n) r++;
		r--;
		ans=max(ans,sum[r]-sum[l-1]);
		l++;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：

选择  $n$  个朋友，满足以下条件：  

- 工资差异 $<d$
- 友谊和最大(题目翻译不太清楚)    

现在面临两个问题  
1. 求差异值  
2. 求友谊和  

所以我们理应想到~~线段树~~双指针。   

排序后满足工资从小到大，友谊和可以用前缀和实现。 

每次往后加一个人。    
用 while 循环，增加左端点，使得工资差异满足。     
并且每次取最大值最后输出。  

两个指针，如果一直满足就增加右端点，否则增加左端点，可以保证差异值并且长度最大，然后每次在此区间打擂台即可。



### Solution:
```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e5+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

ll n,d;
struct node{
	ll m,s;
}a[N];
ll ans;
ll s[N];
bool cmp(node a,node b){
	return a.m<b.m;
}

int main()
{
	n=read(),d=read();
	for(int i=1;i<=n;++i){
		a[i].m=read(),a[i].s=read();
	}
	sort(a+1,a+n+1,cmp);
	ll l=1;
	for(int i=1;i<=n;++i){
		s[i]=s[i-1]+a[i].s;
		while(a[i].m-a[l].m>=d) ++l;
		ans=max(ans,s[i]-s[l-1]);
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：wangyi_c (赞：0)

## 1.思路阐述

对这道题来说，**快速求友谊和 以及 快速求工资差** 是最大的问题。

- 对于第一个问题，我们可以使用 [前缀和](https://blog.csdn.net/qq_45914558/article/details/107385862) 来求解。

- 对于第二个问题，我们可以用 [Two Pointers/尺取法](https://blog.csdn.net/lxt_Lucia/article/details/81091597) 来解决，注意这里是同向尺取哦~

忘记提了，要先对数组以工资为关键字进行排序，否则下标不对应会导致答案错误。

先枚举左端点，再将右端点 $ e $ 往右不断移，当 $ d \leq r_m - r_l $ 的时候，再右移 $ l $，移完之后再算答案就行了。

## 2. AC Code

```cpp
#include<bits/stdc++.h>
#define int long long//注意要开 long long 哦
using namespace std;
int n,d,b=1,e;
long long sum,ans;
struct node{
	int m,s;
}a[100005];//结构体
bool cmp(node x,node y){
	return x.m<y.m;//sort自定义规则
}
signed main(){
	scanf("%lld %lld",&n,&d);
	for(int i=1;i<=n;i++) scanf("%d %d",&a[i].m,&a[i].s);
	sort(a+1,a+n+1,cmp);//排序
	while(e<n){//尺取
		sum+=a[++e].s;
		while(a[e].m-a[b].m>=d) sum-=a[b++].s;//右移左端点
		ans=max(sum,ans);//取答案最大值
	}
	printf("%lld",ans);//输出答案QWQ
	return 0;
}
```
_THE END_

谢谢观看！

By wangyi

---

## 作者：Dr_Gilbert (赞：0)

# CF580B Kefa and Company

【题目大意】[传送门](https://www.luogu.com.cn/problem/CF580B)

一道比较套路的双指针问题。首先由于题目要求两两间工资的差小于 $d$，所以先把每个朋友按工资从小到大排序。然后可以对排序后的朋友的友谊值做前缀和预处理，方便后续代码实现。接着按照双指针套路，先从 $1$ 到 $n$ 枚举左端点，再根据最大工资差值找到最靠右的可行点。由于友谊值全部非负，所以序列一定越长越好，在每次找到右端点后直接计算区间和统计答案即可。由于工资从小到大排序，所以整个过程中右端点只会向右移动，所以时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
	int m,f;
	bool operator <(const node& a) const{
		return m<a.m;
	}
}fri[N];
int s[N];
signed main(){
	int n,d;cin>>n>>d;
	for (int i=1;i<=n;i++){
		cin>>fri[i].m>>fri[i].f;
	}
	sort(fri+1,fri+1+n);
	fri[n+1].m=0x7f7f7f7f;
	int ans=0;
	for (int i=1;i<=n;i++) s[i]=s[i-1]+fri[i].f;
	for (int l=1,r=1;l<=n;l++){
		while (fri[r].m-fri[l].m<d) r++;
		r--;
		ans=max(ans,s[r]-s[l-1]);
	}
	cout<<ans;
	return 0;
}
```

当然，本题也可以进行二分，枚举左端点时二分出右端点即可，时间复杂度 $O(n\log n)$，本题也可以通过。

---

## 作者：zhmzhuhanming (赞：0)

又不难又不简单的一道题
1. 本题可能有人写了半天后，求友谊值的和时超时了。于是就要用到——前缀和！
2. 求工资差的时候，为了再次避免超时，还得让工资排序

总结一下，本题要用到 前缀和 与 排序

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long  //long long!!  long long!!  没long long就去见阎王吧
int n,d,b[100010]; 
struct T{
	int m,s;//工资和友谊值
}a[100010];

bool cmp(T a,T b){
	return a.m<b.m;
}
signed main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i].m>>a[i].s;
	} 
	sort(a+1,a+1+n,cmp);  //排序
	for(int i=1;i<=n;i++){
		b[i]=b[i-1]+a[i].s;  //前缀和（注意排序后进行，否则会乱掉）
	}
	int l=1,r=1,ans=0;  //l，r两个指针
	for(;l<=n;l++){
		for(;r<=n&&a[r].m-a[l].m<d;r++){   //如果最大工资差小于d，就可以判断友谊值和了
			ans=max(ans,b[r]-b[l-1]);  //前缀和派上用场了（不用循环统计）
		}
		
	}
	cout<<ans<<endl;
	return 0;
}
```


---

