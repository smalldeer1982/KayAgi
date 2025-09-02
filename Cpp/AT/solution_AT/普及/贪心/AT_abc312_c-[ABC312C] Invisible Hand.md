# [ABC312C] Invisible Hand

## 题目描述

**题意简述**

在苹果市场中，有 $N$ 个卖家和 $M$ 个买家。第 $i$ 个卖家愿意出售的最低价格为 $A_i$ 日元，第 $j$ 个买家愿意购买的最高价格为 $B_i$ 日元。

请求出一个最低价格 $x$，使愿意以 $x$ 日元出售的卖家数量大于等于愿意以 $x$ 元购买的买家。

## 说明/提示

- $1 \le N,M \le 2 \times 10^5$
- $1 \le A_i,B_i \le 10^9$

## 样例 #1

### 输入

```
3 4
110 90 120
100 80 120 10000```

### 输出

```
110```

## 样例 #2

### 输入

```
5 2
100000 100000 100000 100000 100000
100 200```

### 输出

```
201```

## 样例 #3

### 输入

```
3 2
100 100 100
80 120```

### 输出

```
100```

# 题解

## 作者：hjfjwl (赞：4)

题目说有 $n$ 个商人和 $m$ 个买家,其中第 $i$ 个商人卖出的价格大于等于 $a[i]$，第 $i$ 个买家买入的价格小于等于 $b[i]$，我们可以用二分来进行判断，我们判断这个 $mid$ 是否可行也就是 $mid$ 大于等于 $a[i]$ 个数如果大于 $mid$ 小于等于 $b[i]$ 的个数。

AC code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long
int n,m;
int a[200005];
int b[200005];
bool check(int x)
{
	int ca = 0;
	for(int i = 1;i <= n;i++)
	{
		if(x >= a[i])
		{
			ca++;
		}
	}
   //有多少个商家会卖
	int cb = 0;
	for(int i = 1;i <= m;i++)
	{
		if(x <= b[i])
		{
			cb++;
		}
	}
   //有多少个买家会买
	return ca >= cb;
}
signed main(){
	cin >>n >>m;
	for(int i = 1;i <= n;i++)cin >> a[i];
	for(int i = 1;i <= m;i++)cin >> b[i];
	int l = 1,r = 1000000001;//最小为1，最大为1e9+1
	int ans;
	while(l <= r)//二分
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			r = mid - 1;
			ans = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：szhqwq (赞：3)

## $\tt{Solution}$

考虑二分答案。

因为要求以 $x$ 日元卖出的卖家要**大于等于**以 $x$ 日元买入的买家，所以去二分此处的 $x$，统计出 $x \geq a_i$ 的数量以及 $x \leq b_i$ 的数量，然后返回比较结果。

正常写二分即可。

**注意：因为 $1 \leq a_i,b_i \leq 10^9$，所以二分时的右边界尽量开大些。**

~~赛事就这样吃了罚时。~~

```cpp
#include <bits/stdc++.h>

#define int long long
#define rep(i,l,r) for (int i = l; i <= (int)r; ++ i )
#define rep1(i,l,r) for (int i = l; i >= (int)r; -- i )
#define rep_r(i,l,r) rep(i,l,r) a[i] = read()
#define il inline
#define fst first
#define snd second
#define pb push_back
#define Yes cout << "Yes" << '\n'
#define No cout << "No" << '\n'
#define YES cout << "YES" << '\n'
#define NO cout << "NO" << '\n'
#define lcm(x,y) x * y / __gcd(x,y)

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
const int N = 2e5 + 10,inf = 1e9,inff = 1e18;
//int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
int n,m;
int a[N],b[N];

inline void read(int &x) {
	x = 0;
	short flag = true;
	char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') flag = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
	x *= flag;
}

il bool check(int x) {
	int cnt = 0,sum = 0;
	rep(i,1,n) if (x >= a[i]) ++ cnt;
	rep(i,1,m) if (x <= b[i]) ++ sum;
	return cnt >= sum;
}

signed main() {
	read(n); read(m);
	rep(i,1,n) read(a[i]);
	rep(i,1,m) read(b[i]);
	int l = 0,r = inff,res;
	while (l < r) {
		int mid = l + r >> 1;
		if (check(mid)) res = mid,r = mid;
		else l = mid + 1;
	}
	cout << res << '\n';
	return 0;
}

```

---

## 作者：lrx___ (赞：3)

**题意简述**

在苹果市场中，有 $N$ 个卖家和 $M$ 个买家。第 $i$ 个卖家愿意出售的最低价格为 $A_i$ 日元，第 $j$ 个买家愿意购买的最高价格为 $B_i$ 日元。

请求出一个最低价格 $x$，使愿意以 $x$ 日元出售的卖家数量大于等于愿意以 $x$ 元购买的买家，并且卖家数量不为 $0$。

**思路**

先对输入的所有 $A_i$ 与 $B_i$ 进行排序，最后用二分查找答案即可。

**代码**
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m,a[200005],b[200005];
bool check(int x){
	int s=0,i;
	for(i=1;i<=n;i++){
		s+=(a[i]<=x);
	}
	for(i=1;i<=m;i++){
		s-=(b[i]>=x);
	}
	return s>=0;
}
int main(){
	int mx=0,i,s,l=1,r=1e9,mid;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(i=1;i<=m;i++){
		scanf("%d",&b[i]);
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)){
			s=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	printf("%d\n",s);
	return 0;
}
```

---

## 作者：Walter_Fang (赞：3)

二分答案好题。

### 大致题意

有 $n$ 个卖家和 $m$ 个买家。第 $i$ 个卖家愿意卖价格大于等于 $a_i$ 的苹果，第 $i$ 个买家愿意买价格小于等于 $b_i$ 的苹果。令愿意卖价格为 $x$ 商品的卖家和愿意买价格为 $x$ 商品的买家一样多，求出最小的 $x$。

### 思路

二分答案， `check` 函数跑两边循环，分别计算卖家人数和买家人数，若卖家人数大于买家人数，则答案可行。时间复杂度是 $O(n+m)$，可以通过该题。

因为 $x$ 越大卖家越多，买家越少，即卖家减去买家之差越大，具有单调性。如果答案可行就减小答案，直到找到最小的答案为止。不可行就增加答案。最后二分的值就一定就是最优解，即要求的价钱的最小值。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+10;
ll n,m,i,l,r,mid,ans,a[N],b[N];
bool check(ll x){
	ll i,s1=0,s2=0;
	for(i=1;i<=n;i++)if(x>=a[i])s1++;
	for(i=1;i<=m;i++)if(x<=b[i])s2++;
	return s1>=s2;
}
int main(){
	cin>>n>>m;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<=m;i++)cin>>b[i];
	r=1e18;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}
```

---

## 作者：God_Max_Me (赞：2)

## 题意
有一些卖家，每个人愿意用大于等于 $a_i$ 的价格出售苹果。

还有一些买家，每个人愿意用小于等于 $b_i$ 的价格购买苹果。

现在要求你给定苹果的价格，满足愿意出售的人大于等于愿意购买的人的情况下，苹果的价钱尽量小。

## 思路
很显然的一道二分答案，由于我们不需要考虑人选的方案，只需考虑有多少人愿意卖或买，所以可以直接对 $a$ 数组和 $b$ 数组进行排序。

而后二分答案，每次用 $mid$ 在 $a$ 和 $b$ 数组中记录出有多少人，由于数组已经排序，所以这个可以使用 `lower_bound` 和 `upper_bound` 函数去查找有多少人在苹果价钱为 $mid$ 的情况下愿意买或卖。

因为当 $mid$ 越大时，愿意买的人越少，卖的人越多，所以满足单调性，可以二分。

至于为什么要使用 `upper_bound`，显然，如果我们在判断有多少人愿意买的时候只是用 `lower_bound`，那如果 $a$ 数组中不含 $mid$，那么 `lower_bound` 会查找到大于等于 $mid$ 的第一个数，其下标设为 $k$，那么愿意买的人就为 $k-1$，但如果 $a$ 含有 $mid$，则会找到 $mid$ 本身的下标，最后愿意买的人为 $k$，所以不妨直接使用 `upper_bound`，这样最后愿意买的人数都为 $k-1$。

注意 $1 \le a_i,b_i \le 10^9$，赛时死磕半天没看出来哪错了，结果...是因为 $r$ 的初始值开小了，开成 $10^9+100$ 即可，警钟长鸣。

## 代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n" 
using namespace std;
template<typename P>
inline void read(P &x){
   	P res=0,f=1;
   	char ch=getchar();
   	while(ch<'0' || ch>'9'){
   		if(ch=='-') f=-1;
   		ch=getchar();
   	}
   	while(ch>='0' && ch<='9'){
   		res=res*10+ch-'0';
   		ch=getchar();
	}
	x=res*f;
}
int n,m;
int a[200010];
int b[200010];
bool check(int x){
	int sel=upper_bound(a+1,a+n+1,x)-a-1;
	int bou=m-(lower_bound(b+1,b+m+1,x)-b)+1;
	if(sel>=bou) return 0;
	return 1;
}
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;++i) read(a[i]);
	for(int i=1;i<=m;++i) read(b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	int l=0,r=1e9+100,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1,ans=mid;
	};
	cout<<ans<<endl;
	return 0;
}
~~~

---

## 作者：hellolin (赞：1)

## AtCoder Beginner Contest 312 - C - Invisible Hand

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc312_c) | [AtCoder 题面](https://atcoder.jp/contests/abc312/tasks/abc312_c) | [前往 blog.hellolin.cf 获取更好的阅读体验](https://blog.hellolin.cf/articles/59301d78.html)

手玩一下样例或者打个暴力就很容易发现，答案是这个序列：$A_1, A_2, \dots, A_n, B_1+1, B_2+1,\dots, B_m+1$ 排序后的第 $m$ 项（下面记这个排序后的序列为 $C$）。

下面来证明一下这个答案是正确的。

首先，如果我要以 $0$ 日元定价，我们发现卖的都不愿意卖，买的都愿意买，如果我要以 $10^9+1$ 日元定价，那么卖的都愿意卖，买的都不愿意买。

我们不妨记以 $x$ 日元定价时卖家数与买家数的差值是 $D_x$，这个问题就转化成了求满足 $D_x\ge 0$ 的最小 $x$。显然的，$D_0 = -m$。

当我们令 $x$ 为 $C$ 序列中的值时，我们发现，如果 $C$ 序列中这个值是 $B$ 序列中某个值加 $1$ 的结果，那么此时买家就会少一个（因为此时定价刚好比这个买家给的价格高 $1$ 日元）；如果这个值是 $A$ 序列中某个值，那么此时卖家就会多一个。显然的，$x$ 的增加只会让买家减少或卖家增多。因此，我们可以推断 $D_{C_1} = -m+1,\ D_{C_2} = -m+2,\ \dots,\ D_{C_m} = -m+m = 0$。

[参考代码](https://pastebin.com/TLskqSAX)

---

## 作者：luogu_gza (赞：0)

我们考虑二分，问题的可行性明显是有单调性的，至于 check 怎么办呢？我们考虑暴力统计 $a$ 中大于等于 $x$ 的数与 $b$ 中小于等于 $x$ 的数的差，看这个值是否大于等于 $0$ 就好了。

记得将两个数组排序，注意二分边界条件。

[record](https://www.luogu.com.cn/record/118538394)

---

## 作者：CheZiHe929 (赞：0)

## 原题链接
[Atcoder](https://atcoder.jp/contests/abc312/tasks/abc312_c)

[洛谷](https://www.luogu.com.cn/problem/AT_abc312_c)

## 题目大意
有 $n$ 个卖家和 $m$ 个买家。第 $i$ 个卖家只有当价钱大于等于 $a_i$ 时才愿意卖出商品，第 $i$ 个买家只有当价钱小于等于 $b_i$ 时才愿意买进商品。问使得愿意卖出商品的卖家大于等于愿意买进商品的买家的最小价钱。

## 思路分析
考虑二分答案。每次二分到的答案对其进行判断，如果满足题目给定的条件，说明答案在左区间并记录下答案，否则说明答案在右区间。

**证明：**
- 单调性

我们要使得愿意卖出商品的卖家大于等于愿意买进商品的买家，其实就是保证卖家的数量减去买家的数量的值是一个非负数。

价钱越高，愿意卖出商品的卖家就越多，同理，愿意买进商品的买家就越少。所以卖家的数量减去买家的数量所得的值就越大，这样就保证了单调性。

- 正确性

如果答案可行就会减小答案的值，以为寻求最小的可行的答案。不可行就会增大答案的值。重复以上操作直至最后二分到一个值，这个值就一定就是最优解，也就是本题中要求的价钱的最小值。

## 完整代码（含注释）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m;
int a[200005],b[200005];

bool check(int x){
	int cnta=0,cntb=0;//记录愿意卖出商品的卖家和愿意买进商品的买家的数量
	for(int i=1;i<=n;i++)
		if(x>=a[i])cnta++;//>=
	for(int i=1;i<=m;i++)
		if(x<=b[i])cntb++;//<=
	if(cnta>=cntb)return true;//符合题目条件
	else return false;//不符合
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
		cin>>b[i];
	int l=1,r=1e9+5;//二分初始值，注意 l 初始值为 1
	int ans;
	while(l<r){
		int mid=(l+r)/2;
		if(check(mid)){//满足：答案在左区间
			ans=mid;
			r=mid;
		}
		else l=mid+1;//不满足：答案在右区间
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：yuheng_wang080904 (赞：0)

## 题意

有 $n(1\le n\le 2\times 10^5)$ 个卖家和 $m(1\le m\le 2\times 10^5)$ 个买家。卖家 $i$ 愿意卖价格大于等于 $a_i(1\le a_i\le 10^9)$ 的商品，买家 $i$ 愿意买价格小于等于 $b_i(1\le b_i\le 10^9)$ 的商品。求最小的 $x$ 满足：愿意卖价格为 $x$ 商品的卖家和愿意买价格为 $x$ 商品的买家一样多。

## 思路

赛时知道该题有结论但没去想，直接写了二分跑路。

一看到数据范围直接二分答案 $x$，暴力 $O(n+m)$ 分别求出卖家和买家的人数，返回比大小结果，复杂度完全来得及。

为什么可以二分呢？因为 $x$ 越大卖家人数越多，买家人数越少，即卖家人数减去买家人数之差越大，具有单调性。

小注意点，答案可能达到 $10^9$，因此右边界要满足 $r\ge 10^9+1$。

## 代码

```cpp
ll n,m,a[200005],b[200005];
bool check(ll x){
	ll cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++){
		if(x>=a[i])cnt1++;
	}
	for(int i=1;i<=m;i++){
		if(x<=b[i])cnt2++;
	}
	return cnt1>=cnt2;
}
int main(){
	IOS
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	ll l=1,r=1e9+1,mid,ans;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Esperance (赞：0)

### 题意

第 $i$ 个商人会以 $A_i$ 或更高的价钱卖出一个商品。

第 $i$ 个顾客会以 $B_i$ 或更少的价钱购买一个商品。

求一个价钱 $x$，保证以 $x$ 元卖出该商品的商人人数大于等于以 $x$ 元买该商品的顾客的人数。

### 思路

题目是要寻找最小可能的答案，果断二分答案。

设 $l$ 为 $1$，$r$ 为 $\max\{a[i]\}$。

```Check``` 函数内可以写两个二分查找。
 
愿意卖商品的商人的个数为第一个大于答案 $x$ 的 $A_i$ 的下标 $i$ 减 $1$。愿意购买商品的顾客的个数为 $M - j$，$j$ 是第一个大于等于 $x$ 的 $B_j$ 的下标。


注意题目没有保证 $A$, $B$ 有序，因此二分查找前需要先排序。

代码不贴了。

---

## 作者：Genius_Star (赞：0)

### 题意：

有 $n$ 个卖家，和 $m$ 个买家，第 $i$ 个卖家可以以 $a_i$ 或者更高的价钱卖东西，第 $i$ 个买家可以以 $b_i$ 或者更低的价钱买东西。

请找出一个最少的价钱，使得愿意卖的卖家人数是大于等于愿意买的买家的人数。

### 思路：

~~二分答案的模板题~~

看到数据范围，我们第一眼就会想到二分答案，答案的范围一开始想的是 $1$ 到 $10^9$ 之间（包括），提交之后 WA 了一个点，才发现，虽然题目范围是 $1 \le A_i,B_i \le 10^9$，但是如果 $A$ 和 $B$ 中全都是 $10^9$，并且 $n<m$，我们算出来的答案应该是 $10^9+1$，所以二分的右端点应该是 $10^9+1$。

现在，我们要想一下 check 函数怎么写。

发现我们可以用 $O(n)$ 的时间扫一遍 $A,B$ 数组，计算出 $A$ 数组中小于等于 $mid$ 的数的个数 $t_1$，然后计算出 $B$ 数组中大于等于 $mid$ 的数个数 $t_2$，判断一下，如果 $t_1 \le t_2$，符合题目答案，那么答案肯定在左边区域，所以将 $r=mid$，否则将 $l=mid+1$。

这样直到 $l=r$ 时就可以得到最终的答案，输出 $l$ 或者 $r$ 都可以。

### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200;
inline ll read(){ //快读 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){ //快输 
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m;
ll a[N],b[N];
ll l,r;
int main(){
	n=read(),m=read();
	for(int i=0;i<n;i++)
	  a[i]=read();
	for(int i=0;i<m;i++)
	  b[i]=read();
	sort(a,a+n);
	sort(b,b+m);
	l=1,r=1e9+1;
	while(l<r){
		ll mid=(l+r)>>1;
		ll t1=0,t2=0;
		for(int i=0;i<n;i++){
			if(a[i]<=mid)
			  t1++;
			else
			  break;
		}
		for(int i=(m-1);i>=0;i--){
			if(b[i]>=mid)
			  t2++;
			else
			  break;
		}
		if(t1>=t2)
		  r=mid;
		else
		  l=mid+1;
	}
	write(l);
	return 0;
}
```


---

