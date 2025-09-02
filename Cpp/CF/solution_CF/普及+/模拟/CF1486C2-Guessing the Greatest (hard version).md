# Guessing the Greatest (hard version)

## 题目描述

The only difference between the easy and the hard version is the limit to the number of queries.

This is an interactive problem.

There is an array $ a $ of $ n $ different numbers. In one query you can ask the position of the second maximum element in a subsegment $ a[l..r] $ . Find the position of the maximum element in the array in no more than 20 queries.

A subsegment $ a[l..r] $ is all the elements $ a_l, a_{l + 1}, ..., a_r $ . After asking this subsegment you will be given the position of the second maximum from this subsegment in the whole array.

## 说明/提示

In the sample suppose $ a $ is $ [5, 1, 4, 2, 3] $ . So after asking the $ [1..5] $ subsegment $ 4 $ is second to max value, and it's position is $ 3 $ . After asking the $ [4..5] $ subsegment $ 2 $ is second to max value and it's position in the whole array is $ 4 $ .

Note that there are other arrays $ a $ that would produce the same interaction, and the answer for them might be different. Example output is given in purpose of understanding the interaction.

## 样例 #1

### 输入

```
5

3

4```

### 输出

```
? 1 5

? 4 5

! 1```

# 题解

## 作者：pomelo_nene (赞：5)

考虑到只有 $20$ 次询问，第一反应显然是二分。

因为题目中有一个信息是所有的数互不相同，那么这个数列有且只有一个数是大于整个序列的次大值。找到这个次大值，设其位置为 $p$。

那么，我们要找到最大值所在的相对位置——在 $p$ 左边还是右边。

考虑这个问题的时候再反顾这个性质：有且只有一个数是大于整个序列的次大值。

那么只有在包含这个最大值和 $p$ 的时候，$p$ 才会作为次大值。

知道这个位置的方法是再进行一次询问。询问 $[1,p]$ 的次大值是多少。如果询问的结果还是 $p$，那么说明 $[1,p-1]$ 存在最大值；否则 $[p+1,n]$ 存在最大值。

注意有一个小坑点是，如果 $p$ 是 $1$，那么不能够查询 $[1,p]$。但是我们可以直接确定最大值所在区间在 $[2,n]$。

那么考虑二分最大值所在，因为上面提到的性质，如果同时包含 $p$ 和最大值，查询的结果就是 $p$。

那么，假设最大值所在区间是 $[1,p-1]$，那么每次二分查询 $[mid,p]$。如果查询结果是 $p$，就将 $l$ 往右移；否则将 $r$ 往左移。同理解决 $[p+1,n]$。查询次数是 $O(\log n)$ 的，可以通过此题。

所以谁告诉我 C1 C2 有什么区别？？？？？

```cpp
#include<bits/stdc++.h>
using namespace std;
#define F fflush(stdout)
int n;
int main(){
	scanf("%d",&n);
	int p;
	printf("? 1 %d\n",n);
	F;
	scanf("%d",&p);
	int l=1,r=n;
	if(p==1)
	{
		l=2;
	}
	else
	{
		int dk;
		printf("? %d %d\n",1,p);
		F;
		scanf("%d",&dk);
		if(dk==p)	r=p-1;
		else	l=p+1;
	}
	if(l==p+1)
	{
		while(l<r)
		{
			int mid=(l+r)>>1;
			printf("? %d %d\n",p,mid);
			F;
			int sp;
			scanf("%d",&sp);
			if(sp==p)	r=mid;
			else	l=mid+1;
		}
	}
	else
	{
		while(l<r)
		{
			int mid=(l+r+1)>>1;
			printf("? %d %d\n",mid,p);
			F;
			int sp;
			scanf("%d",&sp);
			if(sp==p)	l=mid;
			else	r=mid-1;
		}
	}
	printf("! %d",l);
	F;
	return 0;
}
```

---

## 作者：Binary_Lee (赞：4)

## [题面传送门](https://www.luogu.com.cn/problem/CF1486C2)

### 解决思路

看到 $10^5$ 的范围和 $20$ 次询问，容易想到二分。

所以考虑如何来二分。

首先，可以询问一次 $[1,n]$，得到所有数中的次小值位置 $x$ ，然后可以问一次 $[1,x]$ 得出最大值在 $x$ 的左侧还是右侧。

然后再确定的区间里进行二分。以左边为例，初始 $l=1,r=x$，每次询问 $[mid,x]$，若次大值仍是 $x$，则说明最大值在 $[mid,x]$ 区间内，将 $l$ 更新，反之则在另一边，将 $r$ 更新。右边同理，每次询问每 $[x,mid]$ 即可。同时，每当 $x$ 仍是次大值时，将 $ans$ 更新成 $mid$，最后得到的就是答案了。

注意一个细节：当第一次询问结果为 $1$ 时，可以直接判定最大值在右区间，否则询问 $[1,1]$ 会出错。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
using namespace std;
int n,l,r,x,y,mid,ans;
bool fl;
void binary(int l,int r,int typ){
	while(l<=r){
		mid=(l+r)>>1;
		int _1=min(x,mid),_2=x+mid-_1;
		cout<<"? "<<_1<<" "<<_2<<endl;
		cin>>y;
		if((x==y)^typ) l=mid+1;   //两种情况放一起了
		else r=mid-1;
		if(x==y) ans=mid;  //更新ans
	}
}
signed main(){
	cin>>n;
	cout<<"? 1 "<<n<<endl;
	cin>>x;
	if(x!=1){
		cout<<"? 1 "<<x<<endl;
		cin>>y;
		if(y!=x) fl=1;
	}
	else fl=1;
	if(fl) binary(x+1,n,1);
	else binary(1,x-1,0);
	cout<<"! "<<ans<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

## 题解：CF1486C2 Guessing the Greatest (hard version)

### 题意简述

有一个值均不同的数组，每次你可以询问一个子段次大值的位置，请你在 $20$ 次询问之内找到最大值的位置。

### 解题思路

首先，我们**确定全局次大值的位置**，询问 $(1 , n)$，记为 $q$。

- 若 $q = 1$，则答案区间为 $(2 , n)$。
- 若 $q = n$，则答案区间为 $(1 , n - 1)$。
- 若 $1 < q < n$ 且询问 $(1 , q) = q$，则答案区间为 $(1 , q - 1)$。
- 若 $1 < q < n$ 且询问 $(1 , q) \ne q$，则答案区间为 $(q + 1 , n)$。

此时我们在答案区间中**二分**，为避免区间只有一个数的情况：

- 若 $\frac{l + r}{2} < q$，则 $mid \gets \frac{l + r}{2} + 1$。
- 若 $\frac{l + r}{2} > q$，则 $mid \gets \frac{l + r}{2}$。
- 可以证明不存在 $\frac{l + r}{2} = q$ 的情况。

如果询问 $(\min(mid , q) , \max(mid , q)) = q$，那么最大值就在这个区间，反之不在。

### 参考代码

因为四种情况打了四个不太相同的二分，所以马蜂有点史，请见谅。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n , l , r , mid , ans , sec;
inline bool ask(int q)
{
	int x;
	cout << "? " << min(sec , q) << ' ' << max(sec , q) << endl;
	cin >> x;
	return x == sec;
}
int main()
{
	cin >> n;
	cout << "? 1 " << n << endl;
	cin >> sec;
	if(sec == 1)
	{
		l = 2;
		r = n;
		while(l <= r)
		{
			if(l == r)
			{
				ans = l;
				l++;
				continue;
			}
			mid = (l + r) / 2;
			if(mid == r)
			{
				mid--;
			}
			if(ask(mid))
			{
				ans = mid;
				r = mid;
			}
			else
			{
				l = mid + 1;
			}
		}
	}
	else if(sec == n)
	{
		l = 1;
		r = n - 1;
		while(l <= r)
		{
			if(l == r)
			{
				ans = l;
				l++;
				continue;
			}
			mid = (l + r + 1) / 2;
			if(mid == l)
			{
				mid++;
			}
			if(ask(mid))
			{
				ans = mid;
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
	}
	else
	{
		cout << "? 1 " << sec << endl;
		cin >> ans;
		if(ans == sec)
		{
			l = 1;
			r = sec - 1;
			while(l <= r)
			{
				if(l == r)
				{
					ans = l;
					l++;
					continue;
				}
				mid = (l + r + 1) / 2;
				if(mid == l)
				{
					mid++;
				}
				if(ask(mid))
				{
					ans = mid;
					l = mid;
				}
				else
				{
					r = mid - 1;
				}
			}
		}
		else
		{
			l = sec + 1;
			r = n;
			while(l <= r)
			{
				if(l == r)
				{
					ans = l;
					l++;
					continue;
				}
				mid = (l + r) / 2;
				if(mid == r)
				{
					mid--;
				}
				if(ask(mid))
				{
					ans = mid;
					r = mid;
				}
				else
				{
					l = mid + 1;
				}
			}
		}
	}
	cout << "! " << ans;
	return 0;
}
```

**双倍经验：[CF1486C1](https://www.luogu.com.cn/problem/CF1486C1)**。

---

## 作者：Sora1336 (赞：3)

值得一想的题。对于整个序列，我们发现一开始根本无法下手，只能询问整个序列，得到一个答案 $x$ 。

现在在 $x$ 的左边尝试询问即 $[1,x]$。假如次大值还是 $x$ ，那么易证最大值就在区间 $[1,x-1]$ 里（即 $\text{ans}<x$）；假如次大值不是 $x$ ，那么最大值就在 $[x+ 1,n]$ 里（即 $\text{ans}>x$）。

我们先定义一个函数 $f(a,b)$ 返回的是区间 $[a,b]$ 的次大值。

考虑二分最大值。若 $f(\text{mid},x)=x$，那 $\text{ans}>\text{mid}$ 。然后再在可能出现 $\text{ans}$ 的地方二分。另一种情况也差不多，读者可以自行推导。

这题对我来说比较难写，所以建议把代码模块化一下， $f(a,b)$ 单独封装成一个 `int` 类型的函数会比较好写。

---

## 作者：grass8cow (赞：1)

看到 $20$ 次，应该是 $\log n$ 算法。

不难想到，通过 $ask(1,n)$ 找出全局次大的位置 $x$ 。

那么一个包含 $x$ 的区间内，如果次大位置就是 $x$ ,说明最大值也在这个区间里。

于是可以考虑二分：先通过 $ask(1,x)$ 判断 $ans<x$ 还是 $ans>x$ 。

以 $ans<x$ 为例，若 $ask(mid,x)=x$ 说明 $ans\ge mid$ ,因此有单调性，然后以此二分答案，没了。

$ans>x$ 同理。

赛时 code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ask(int l,int r){
	int x;
	printf("? %d %d\n",l,r);
	fflush(stdout);scanf("%d",&x);
	return x;
}
int main(){
	scanf("%d",&n);int ans,x=ask(1,n);
	if(x==1||ask(1,x)!=x){
		int l=x+1,r=n;
		while(l<=r){
			int mid=(l+r)>>1,pp=ask(x,mid);
			if(pp==x)ans=mid,r=mid-1;
			else l=mid+1;
		}
	}
	else{
		int l=1,r=x-1;
		while(l<=r){
			int mid=(l+r)>>1,pp=ask(mid,x);
			if(pp==x)ans=mid,l=mid+1;
			else r=mid-1;
		}
	}
	printf("! %d\n",ans);
	return 0;
}

```
很想吐槽会 $C1$ 却不会 $C2$ 的人。

---

## 作者：liruizhou_lihui (赞：0)

先问 $[1,n]$ 这个区间，得到次小值 $s$，然后二分。


看左边：$l=1$，$r=x$，设 $mid=\frac{l+r}{2}$，那么如果 $[mid ,x]$ 区间次小值还是 $x$ 那么最大值在 $[mid , x]$ 更新 $l$，反之是更新 $r$。右边同理。最后区间一直缩小直到确定最大值。
```cpp
#include<bits/stdc++.h>
using namespace std;

int ask(int l,int r)
{
	if(l>=r)
	{
		return-1;
	}
	cout<<"? "<<l+1<<' '<<r+1<<'\n';
	int ans;
	cin>>ans;
	return ans-1;
}
int main()
{
	int n;
	cin>>n;
	int smax=ask(0,n-1);
	if(smax==0||ask(0,smax)!=smax)
	{
		int l=smax,r=n-1;
		while(r-l>1)
		{
			int mid=l+r>>1;
			if(ask(smax,mid)==smax)
			{
				r=mid;
			}
			else
			{
				l=mid;
			}
		}
		cout<<"! "<<r+1<<'\n';
	}
	else
	{
		int l=0,r=smax;
		while(r-l>1)
		{
			int mid=l+r>>1;
			if(ask(mid,smax)==smax)
			{
				l=mid;
			}
			else
			{
				r=mid;
			}
		}
		cout<<"! "<<l+1<<'\n';
	}
	return 0;
}
```

---

## 作者：liruizhou_lihui (赞：0)

先问 $[1 \sim n]$ 这个区间，得到次小值 $s$，然后二分。


看左边：$l=1$，$r=x$，设 $mid=\frac{l+r}{2}$，那么如果 $[mid \sim x]$ 区间次小值还是 $x$ 那么最大值在 $[mid \sim x]$ 更新 $l$，反之是更新 $r$。右边同理。最后区间一直缩小直到确定最大值。
```cpp
#include<bits/stdc++.h>
using namespace std;

int ask(int l,int r)
{
	if(l>=r)
	{
		return-1;
	}
	cout<<"? "<<l+1<<' '<<r+1<<'\n';
	int ans;
	cin>>ans;
	return ans-1;
}
int main()
{
	int n;
	cin>>n;
	int smax=ask(0,n-1);
	if(smax==0||ask(0,smax)!=smax)
	{
		int l=smax,r=n-1;
		while(r-l>1)
		{
			int mid=l+r>>1;
			if(ask(smax,mid)==smax)
			{
				r=mid;
			}
			else
			{
				l=mid;
			}
		}
		cout<<"! "<<r+1<<'\n';
	}
	else
	{
		int l=0,r=smax;
		while(r-l>1)
		{
			int mid=l+r>>1;
			if(ask(mid,smax)==smax)
			{
				l=mid;
			}
			else
			{
				r=mid;
			}
		}
		cout<<"! "<<l+1<<'\n';
	}
	return 0;
}
```

---

## 作者：liruizhou_lihui (赞：0)

先问 $[1 \sim n]$ 这个区间，得到次小值 $s$，然后二分。


看左边：$l=1$，$r=x$，设 $mid=\frac{l+r}{2}$，那么如果 $[mid \sim x]$ 区间次小值还是 $x$ 那么最大值在 $[mid \sim x]$ 更新 $l$，反之是更新 $r$。右边同理。最后区间一直缩小直到确定最大值。
```cpp
#include<bits/stdc++.h>
using namespace std;

int ask(int l,int r)
{
	if(l>=r)
	{
		return-1;
	}
	cout<<"? "<<l+1<<' '<<r+1<<'\n';
	int ans;
	cin>>ans;
	return ans-1;
}
int main()
{
	int n;
	cin>>n;
	int smax=ask(0,n-1);
	if(smax==0||ask(0,smax)!=smax)
	{
		int l=smax,r=n-1;
		while(r-l>1)
		{
			int mid=l+r>>1;
			if(ask(smax,mid)==smax)
			{
				r=mid;
			}
			else
			{
				l=mid;
			}
		}
		cout<<"! "<<r+1<<'\n';
	}
	else
	{
		int l=0,r=smax;
		while(r-l>1)
		{
			int mid=l+r>>1;
			if(ask(mid,smax)==smax)
			{
				l=mid;
			}
			else
			{
				r=mid;
			}
		}
		cout<<"! "<<l+1<<'\n';
	}
	return 0;
}
```

---

## 作者：__ikun__horro__ (赞：0)

## Solution

由于 $n$ 很大，而且最多只有 $20$ 次查询，所以可以考虑用二分来解决。

每次二分，我们先求出 $l \sim r$ 的次小值的位置 $x$。

- 如果 $x \le mid$，我们查询 $l \sim mid$ 中的最小值 $y$。
  - 如果 $x = y$，那么最大值在区间 $\left[ l, mid \right]$ 里面。
  - 否则，也就是说 $x$ 成了区间 $\left[ l, mid \right]$ 的最大值，所以区间 $\left[ l, r \right]$ 的最大值在区间 $\left[ mid+1, r \right]$ 里面。
- 如果 $x > mid$，反过来就好了，详见代码。

还有一个小细节，就是如果查询的区间左端点和右端点重合时会错误，所以我们可以返回一个比较恶臭的值。

## Code

```cpp
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#define int long long

using namespace std;

int n, x;

inline int query(int l, int r) {
	if (l == r) return -114514;
	cout << "? " << l << " " << r << "\n";
	int tmp;
	cin >> tmp;
	return tmp;
}

inline void sol() {
	cin >> n;
	int l = 1, r = n, mid;
	x = query(l, r);
	while (l < r) {
		mid = (l + r) >> 1;
		if (x <= mid) {
			if (query(1, mid) == x) r = mid;
			else l = mid + 1;
		} else {
			if (query(mid + 1, n) == x) l = mid + 1;
			else r = mid;
		}
	}
	cout << "! " << l << "\n";
}

signed main() {
	// ios::sync_with_stdio(0);
	// cin.tie(0); cout.tie(0);
	// init();
	int T = 1;
	// cin >> T;
	while (T--) sol();
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1486C1](https://www.luogu.com.cn/problem/CF1486C1)

[CF1486C2](https://www.luogu.com.cn/problem/CF1486C2)

# 解题思路

提供一个比较显然的思路。

我们发现我们可以先求出整体的最小值，然后设整体最小值所在的位置为 $id$，则我们可以通过 $1$ 次询问 $[1,id]$ 来求出最大值的位置是在 $[1,id)$ 还是在 $(id,n]$。然后我们就有了整体最大值在一个前缀或后缀时的情况，此时直接二分出第一个次大值位置为 $id$ 的位置即为最大值所在的位置。

询问次数 $1 + \log n$ 次，可以通过 C1 和 C2。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
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
//ll pw(ll x,ll y,ll mod){if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
ll n;
ll id;
ll ask(ll l,ll r)
{
	if(l==r)
		return -1;
	cout<<"? "<<l<<' '<<r<<endl;
	ll z;
	cin>>z;
	return z;
}
/*
1 2 3 4 5
*/
void solve()
{
	_clear();
	cin>>n;
	id=ask(1,n);
	if(ask(1,id)==id)
	{
		ll L=1,R=id;
		while(L<R)
		{
			ll Mid=(L+R+1)/2;
			if(ask(Mid,id)==id)
				L=Mid;
			else
				R=Mid-1;
		}
		cout<<"! "<<L<<endl;
		return ;
	}
	else
	{
	//	cout<<"??? "<<id<<endl;
		ll L=id,R=n;
		while(L<R)
		{
			ll Mid=(L+R)/2;
			if(ask(id,Mid)!=id)
				L=Mid+1;
			else
				R=Mid;
		}
		cout<<"! "<<L<<endl;
		return ;		
	}
}
int main()
{
	IOS;
	_t_=1;
 //	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：Xiphi (赞：0)

考虑到 $\log 10^5=16.6096 \dots$，可以偏向 $\log$ 级别且常数不大的算法，不难想到二分。见询问 $[1,n]$，找到全局最大值。再询问 $[1,x]$，确定最大值的下标在 $[1,x]$ 还是 $[x+1,n]$，进而就可以确定二分的左界和右界（可以想一想为什么要确定这一步）。

接下来就是很板子的二分了，若当前区间次小值为 $[1,n]$ 的次小值，就找更小的区间，否则就在更大的区间内（这里不是很严谨，具体见代码罢）。注意如果是交互题的话，要用 endl 换行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int query(int l,int r){
	cout<<"? "<<l<<' '<<r<<endl;
	int x;
	cin>>x;
	return x;
}
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
//    ios::sync_with_stdio(false);
//    cin.tie(0);
		int n;
		cin>>n;
		int t=query(1,n);
		int x=t,ans;
		if(t==1||query(1,t)!=t){
			int l=x+1,r=n;
			while(l<=r){
				int mid=l+r>>1;
				if(query(x,mid)==x) ans=mid,r=mid-1;
				else l=mid+1;
			}
		}else{
			int l=1,r=x-1;
			while(l<=r){
				int mid=l+r>>1;
				if(query(mid,x)==x) ans=mid,l=mid+1;
				else r=mid-1;
			}
		}
		cout<<'!'<<' '<<ans<<endl;
	return 0;
}

```

---

## 作者：Exber (赞：0)

介绍一种倍增做法。

首先可以用一次询问确定次大值的位置 $x$。

观察到区间只有同时包含最大值和 $a_x$ 交互库才会返回 $x$，所以再用一次询问确定最大值在 $[1,x-1]$ 内还是在 $[x+1,n]$ 内。

接下来倍增：

- 若最大值在 $[1,x-1]$ 内，那么找到一个最小的 $y$ 满足 $2\le y\le x-1$ 且 $[y,x]$ 内的次大值不是 $a_x$，这时最大值就是 $a_{y-1}$；
- 若最大值在 $[x+1,n]$ 内，那么找到一个最大的 $y$ 满足 $x+1\le y\le n-1$ 且 $[x,y]$ 内的次大值不是 $a_x$，这时最大值就是 $a_{y+1}$。

倍增最多用 $18$ 次询问，找到 $x$ 和确定最大值所在区间最多用两次询问，也就是说一共只会用 $20$ 次询问，可以通过此题。

代码如下：

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int MXBIT=17;

int n;

inline int que(int l,int r)
{
	printf("? %d %d\n",l,r);
	fflush(stdout);
	int res;
	scanf("%d",&res);
	return res;
}

int main()
{
	scanf("%d",&n);
	int pos=que(1,n);
	if(pos!=1&&que(1,pos)==pos)
	{
		int pre=pos;
		for(int i=MXBIT;i>=0;i--) if(pre-(1<<i)>=2&&que(pre-(1<<i),pos)!=pos) pre-=1<<i;
		printf("! %d\n",pre-1);
		fflush(stdout);
	}
	else
	{
		int pre=pos;
		for(int i=MXBIT;i>=0;i--) if(pre+(1<<i)<=n-1&&que(pos,pre+(1<<i))!=pos) pre+=1<<i;
		printf("! %d\n",pre+1);
		fflush(stdout);
	}
	return 0;
}
```



---

