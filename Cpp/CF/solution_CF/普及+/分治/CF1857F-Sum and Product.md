# Sum and Product

## 题目描述

You have an array $ a $ of length $ n $ .

Your task is to answer $ q $ queries: given $ x,y $ , find the number of pairs $ i $ and $ j $ ( $ 1 \le i < j \le n $ ) that both $ a_i + a_j = x $ and $ a_i \cdot a_j = y $ .

That is, for the array $ [1,3,2] $ and asking for $ x=3,y=2 $ the answer is $ 1 $ :

- $ i=1 $ and $ j=2 $ fail because $ 1 + 3 = 4 $ and not $ 3, $ also $ 1 \cdot 3=3 $ and not $ 2 $ ;
- $ i=1 $ and $ j=3 $ satisfies both conditions;
- $ i=2 $ and $ j=3 $ fail because $ 3 + 2 = 5 $ and not $ 3, $ also $ 3 \cdot 2=6 $ and not $ 2 $ ;

## 说明/提示

For the first test case, let's analyze each pair of numbers separately:

- pair $ (a_1,a_2) $ : $ a_1 + a_2 = 4 $ , $ a_1 \cdot a_2 = 3 $
- pair $ (a_1,a_3) $ : $ a_1 + a_3 = 3 $ , $ a_1 \cdot a_3 = 2 $
- pair $ (a_2,a_3) $ : $ a_2 + a_3 = 5 $ , $ a_2 \cdot a_3 = 6 $

 From this, we can see that for the first query, the pair $ (a_1,a_3) $ is suitable, for the second query, it is $ (a_2,a_3) $ , and there are no suitable pairs for the third and fourth queries.In the second test case, all combinations of pairs are suitable.

## 样例 #1

### 输入

```
3
3
1 3 2
4
3 2
5 6
3 1
5 5
4
1 1 1 1
1
2 1
6
1 4 -2 3 3 3
3
2 -8
-1 -2
7 12```

### 输出

```
1 1 0 0 
6 
1 1 3```

# 题解

## 作者：luqyou (赞：13)

# solution

将 $a_i+a_j=x$ 变形，得 $a_j=x-a_i$。

代入 $a_i\times a_j = y$ 得 $a_i \times(x-a_i) =y$。

整理得 $-a_i^2+xa_i-y=0$。

解方程得到解为 $\dfrac{-x \pm \sqrt{x^2-4y}}{-2}$。将两个解在序列中出现的个数乘起来就是答案。

注意判断 $x^2-4y=0$ 的情况，此时若解在序列中出现了 $k$ 次，则答案为 $\dfrac{k(k-1)}{2}$。

原方程无解则为 $0$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
int n,a[maxn],q,ans;
void solve(){
	map<int,int> mp;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]]++;
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		int num=x*x-4*y;
		if(num<0){
			cout<<0<<" ";
			continue;
		}
		int sq=sqrt(num);
		if(sq*sq!=num){
			cout<<0<<" ";
			continue;
		}
		if(num==0){
			cout<<mp[(x-sq)/2]*(mp[(x-sq)/2]-1)/2<<" ";
			continue;
		}
		int n1=x-sq,n2=x+sq;
		int ans=0;
		cout<<mp[n1/2]*mp[n2/2]<<" ";
	}
	cout<<endl;
}
signed main(){
 	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}


```

---

## 作者：hanjinghao (赞：2)

# 题意

给定一个长度为 $ n $ 的序列 $ a $。有 $ q $ 次询问，每次给定 $ x $ 和 $ y $，你需要求出序列中有多少个点对 $ (i,j) $，满足 $ i \lt j $，$ a_i + a_j = x $ 且 $ a_i \times a_j = y $。

数据范围：$ 1 \lt n,q \le 2 \cdot 10 ^ 5 $，$ 1 \le |a_i| \le 10 ^ 9 $，$ 1 \le |x| \le 2 \cdot 10 ^ 9 $，$ 1 \le |y| \le 10 ^ {18} $。

# 思路

先把式子转化一下：$ a_i ^ 2 - x \cdot a_i + y = 0 $，$ a_j = x - a_i $。接下来就是解一元二次方程，用求根公式即可。

注意：如果求出来解不是整数，直接输出 $ 0 $。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline const void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline const void writesp(const T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline const void writeln(const T x)
{
	write(x);
	putchar(10);
}

const int N = 2e5 + 5;
int T, n, q, a[N];
map < int, int > mp;

signed main()
{
	read(T);
	while (T--)
	{
		read(n);
		mp.clear();
		for (int i = 1; i <= n; ++i)
		{
			read(a[i]);
			++mp[a[i]];
		}
		read(q);
		while (q--)
		{
			int x, y;
			read(x);
			read(y);
			int delta = x * x - 4ll * y;
			if (delta < 0)
			{
				writesp(0);
				continue;
			}
			if (!delta)
			{
				if (mp.find(x >> 1) == mp.end())
				{
					writesp(0);
					continue;
				}
				int tmp = mp[x >> 1];
				writesp(tmp * (tmp - 1) / 2);
				continue;
			}
			int t = sqrtl(delta);
			while (t * t > delta)
				--t;
			while ((t + 1) * (t + 1) <= delta)
				++t;
			if (t * t != delta)
			{
				writesp(0);
				continue;
			}
			int X1 = (x + t) / 2;
			int X2 = x - X1;
			if (mp.find(X1) == mp.end())
			{
				writesp(0);
				continue;
			}
			if (mp.find(X2) == mp.end())
			{
				writesp(0);
				continue;
			}
			writesp(mp[X1] * mp[X2]);
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：BFSDFS123 (赞：1)

初二数学题，不知道为什么会放在 F。

这和 CSP-J2022 T2 有区别吗。

考虑 $a_i=x-a_j$，带入 2 式则有 $(x-a_j)\times a_j=y$，即 $x\times a_j-a_j^2=y$。

进行移项，得 $a_j^2-x\times a_j+y=0$，以 $a_j$ 为主元，利用初二数学课上的一元二次方程公式，得 $a_j=\frac{x\pm\sqrt{x^2-4y}}{2}$。因为所有数都是正整数，不难想到，若 $x^2-4y$ 不是一个完全平方数的话，应该输出 0。同理，若 $x\pm\sqrt{x^2-4y}$ 不能被 2 整除，则也要输出 0。

进而可以想到，我们需要计算 $a_j$ 的两种情况（需要特判 $x^2-4y=0$ 的情况，此时只进行一次计算）。对于每次计算，我们可以开一个 map 存下所有的数。

我们在计算时，利用公式，计算出 $a_i,a_j$ 的值，在 map 中查询数出现的次数并进行计算。注意需要特判。

[代码](https://www.luogu.com.cn/paste/22iulpzg)。

---

## 作者：LHLeisus (赞：1)

根据题意我们有：$b=a_i+a_j$，$c=a_i\times a_j$。

可以发现 $a_i$ 和 $a_j$ 是一元二次方程 $x^2-bx+c=0$ 的根。

那么就可以根据求根公式 $x=\dfrac{-b\pm \sqrt{b^2-4ac}}{2a}$ 来求出 $a_i$ 和 $a_j$ 的值，再将它们的数量相乘即为答案。需要注意的是 $b^2-4ac<0$ 和 $=0$ 的情况需要处理，前者无解，后者有两个相等的根。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<utility>
#include<vector>
#include<queue>
#include<bitset>
#include<map>
#define FOR(i,a,b) for(register int i=a;i<=b;i++)
#define ROF(i,a,b) for(register int i=a;i>=b;i--)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int N=1e5+5;
const int INF=0x3f3f3f3f;
int n,m,k;
map<ll,int>mapi;
ll calc(ll b,ll c){
	ll a1,a2;
	ll delta=b*b-4*c;
	if(delta<0){
		return 0;
	}
	a1=(b-sqrt(delta))/2;
	a2=(b+sqrt(delta))/2;
	if(a1+a2!=b||a1*a2!=c) return 0;
	if(delta==0){
		return (ll)mapi[a1]*(mapi[a1]-1)/2;
	}
	return (ll)mapi[a1]*mapi[a2];
}
vector<ll>vec;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		mapi.clear();
		vec.clear();
		FOR(i,1,n){
			ll t;
			scanf("%lld",&t);
			mapi[t]++;
		}
		scanf("%d",&k);
		while(k--){
			ll x,y;
			scanf("%lld%lld",&x,&y);
			vec.push_back(calc(x,y));
		}
		for(int i=0;i<vec.size();i++) printf("%lld ",vec[i]);
		puts("");
	}
	return 0;
}
```


---

## 作者：ProzacPainkiller (赞：0)

我们将 $a_i+a_j=x$ 化成 $a_j=x-a_i$，代入 $a_i\cdot a_j=y$ 得 $a_i(x-a_i)=y$，我们就得到了一个关于 $a_i$ 的一元二次方程。化简成 $a_i^2-xa_i+y=0$，假设 $a_i\le a_j$ 就得到 $a_i=\frac{x-\sqrt{x^2-4y}}{2},a_j=\frac{x+\sqrt{x^2-4y}}{2}$。

先判断是否方程是否有整数解，然后如果 $a_i=a_j$ 就输出 $a_i$ 的数量和 $a_i$ 的数量减一的积再除以二的值（也就是同时选两个 $a_i$ 的方法数），如果 $a_i\not = a_j$ 就输出 $a_i$ 的数量乘 $a_j$ 的数量的值。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
map<ll,ll> mp;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		mp.clear();
		int n,q;
		cin>>n;
		ll a,x,y;
		for(int i=0;i<n;++i)
		{
			cin>>a;
			++mp[a];
		}
		cin>>q;
		for(int i=0;i<q;++i)
		{
			cin>>x>>y;
			ll delta=x*x-4*y,sqrdelta;
			long double sd;
			sd=sqrtl(delta);
			sqrdelta=sd;
			if((sqrdelta+1ll)*(sqrdelta+1ll)==delta)	++sqrdelta;
			if(delta<0ll||sqrdelta*sqrdelta!=delta)
			{
				cout<<"0 ";
				continue;
			}
			if(!delta)	cout<<mp[x/2ll]*(mp[x/2ll]-1)/2<<' ';
			else
			{
				ll t1=(x-sqrdelta)/2ll,t2=(x+sqrdelta)/2ll;
				cout<<mp[t1]*mp[t2]<<' ';
			}
		}
		cout<<'\n';
	}
	return 0;
}
```

---

