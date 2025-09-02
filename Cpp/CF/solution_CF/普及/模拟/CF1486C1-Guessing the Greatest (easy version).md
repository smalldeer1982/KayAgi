# Guessing the Greatest (easy version)

## 题目描述

The only difference between the easy and the hard version is the limit to the number of queries.

This is an interactive problem.

There is an array $ a $ of $ n $ different numbers. In one query you can ask the position of the second maximum element in a subsegment $ a[l..r] $ . Find the position of the maximum element in the array in no more than 40 queries.

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

## 作者：pomelo_nene (赞：3)

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

## 作者：封禁用户 (赞：2)

## 题解：CF1486C1 Guessing the Greatest (easy version)

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

**双倍经验：[CF1486C2](https://www.luogu.com.cn/problem/CF1486C2)**。

---

## 作者：ubsan (赞：1)

看到询问次数是 log 级别的肯定是想二分，$20$ 可以允许每一次二分询问一次,$40$ 可以询问两次。

考虑目前已知道当前区间最大值的位置，要确定最大值所在的子区间的次大值的位置，于是我们可以先询问出  $[l,mid]$ 和 $[mid+1,r]$ 的次大值位置，而我们目前知道的次大值一定是在这两个区间之中的。

我们发现如果子区间的次大值就是目前区间的次大值，那么最大值也一定在这个区间之中（因为没有数比这个还大了），否则它一定是这个区间的最大值，那么全局最大值一定在另一个子区间之中。

询问次数大概是 $2*log_2 n$。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100001];
int query(int l, int r) {
  cout << "? " << l << " " << r << endl;
  cout.flush();
  int idx;
  cin >> idx;
  return idx;
}
void answer(int x) {
  cout << "! " << x << endl;
  cout.flush();
}
int main() {
  cin >> n;
  int l = 1, r = n;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    int v = query(l, r);
    if (v <= mid) {
      if (l == mid) {
        l = mid + 1;
        continue;
      }
      if (query(l, mid) != v) {
        l = mid + 1;
      } else {
        r = mid;
      }
    } else {
      if (mid + 1 == r) {
        r = mid;
        continue;
      }
      if (query(mid + 1, r) != v) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
  }
  if (l == r) {
    answer(l);
    return 0;
  }
  if (query(l, r) == r)
    answer(l);
  else
    answer(r);
  return 0;
}
```

---

## 作者：信守天下 (赞：1)

## [CF传送门](https://codeforces.ml/contest/1486/problem/C1)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF1486C1)
# 思路
## 题意看上去是可以在任意区间询问。

但仔细分析题目，你可以发现，第一步只能在整个区间进行查询。

因为在子区间查询是没有意义的，还浪费了一次查询。

此时我们可以设查到的数为 $m$。

在查询到了后，我们可以根据 $m$ 进行二分查找。

## 这时又有两个选择，在左区间查或在右区间查

其实这时在 $m$ 所在的区间查是最值的。

因为如果查询结果和 $m$ 一样，那么最大数就在当前区间。

否则就在另一个区间，因为当前区间的最大值成了 $m$。

那么我们可以继续对分到的区间进行同样的操作，这是一个**同类子问题**。

所以我们可以直接运用**分治**的思想，**递归调用**处理

## 细节

刚好在中间的点在处理时两边区间都要有。

因为有时刚好点会在当前序列的中间点上。

查询一定要查当前区间，不是查左或查右。

递归边界在区间长度为 $1$ 或 $2$。
# $code$
~~~cpp
#include <iostream>
using namespace std;
int n;
inline int fout(int a, int b) {  //交互询问
  cout << "?" << " " << a << " " << b << endl;
  cout.flush();
  int m;
  cin >> m;
  return m;
}
void Find(int l, int r) {
  if (l == r) {
    cout << "!" << " " << l;  //就是当前数
    cout.flush();
    return;
  }
  if (l + 1 == r) {         //长度为二
    if (l == fout(l, r)) {  //查找较小值,另一个就是答案
      cout << "!" << " " << r;
      cout.flush();
    } else {
      cout << "!" << " " << l;
      cout.flush();
    }
    return;
  }
  int m = fout(l, r);      //查询当前区间
  int k = (l + r) / 2;     //取中点
  if (l <= m && m <= k) {  //在左右哪个区间
    if (fout(l, k) == m) {//k两边都要有
      Find(l, k);          //递归子任务
    } else {
      Find(k, r);
    }
  } else {
    if (fout(k, r) == m) {
      Find(k, r);
    } else {
      Find(l, k);
    }
  }
}
int main() {
  cin >> n;
  Find(1, n);  //查找整个区间
  return 0;
}
~~~

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

## 作者：meyi (赞：0)

题目大意：给定一个 $n$ 个元素的数组，你可以查询任意一个子区间中所有元素的次大值的位置，试在不超过 $40$ 次查询中确定所有元素的最大值的位置。

思路：对于区间 $[l,r]$，设 $mid$ 为 $\lfloor\frac{l+r}{2}\rfloor$，先查询 $[l,r]$ 的次大值的位置，设为 $m$，为了方便说明，我们假设 $l\leq m\leq mid$，然后查询 $[l,mid]$ 的次大值的位置，若其与 $m$ 相等，则说明 $[l,r]$ 的最大值在 $[l,mid]$ 中，否则 $[l,r]$ 的最大值在 $[mid,r]$ 中。继续递归到相应子区间，直到该区间中的元素数量不多于两个，若只有一个元素，显然该元素的位置为答案，若有两个元素，则 $m$ 之外的位置为答案。查询次数为 $O(2\log n)\leq40$，可以通过本题。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline void print(int k){
	cout<<"! "<<k<<endl;
	cout.flush();
	exit(0);
}
inline int query(int l,int r){
	cout<<"? "<<l<<" "<<r<<endl;
	cout.flush();
	int tmp;
	cin>>tmp;
	return tmp;
}
void dfs(int l,int r,int m){
	if(l+1>=r)print(l==m?r:l);
	int mid=l+r>>1,tmp;
	if(m<=mid){
		tmp=query(l,mid);
		if(tmp==m)dfs(l,mid,m);
		else dfs(mid,r,m==mid?m:query(mid,r));
	}
	else{
		tmp=query(mid,r);
		if(tmp==m)dfs(mid,r,m);
		else dfs(l,mid,query(l,mid));
	}
}
int n;
int main(){
	cin>>n;
	dfs(1,n,query(1,n));
	return 0;
}
```


---

