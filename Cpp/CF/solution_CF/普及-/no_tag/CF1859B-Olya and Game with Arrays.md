# Olya and Game with Arrays

## 题目描述

Artem suggested a game to the girl Olya. There is a list of $ n $ arrays, where the $ i $ -th array contains $ m_i \ge 2 $ positive integers $ a_{i,1}, a_{i,2}, \ldots, a_{i,m_i} $ .

Olya can move at most one (possibly $ 0 $ ) integer from each array to another array. Note that integers can be moved from one array only once, but integers can be added to one array multiple times, and all the movements are done at the same time.

The beauty of the list of arrays is defined as the sum $ \sum_{i=1}^n \min_{j=1}^{m_i} a_{i,j} $ . In other words, for each array, we find the minimum value in it and then sum up these values.

The goal of the game is to maximize the beauty of the list of arrays. Help Olya win this challenging game!

## 说明/提示

In the first test case, we can move the integer $ 3 $ from the second array to the first array. Then the beauty is $ \min(1, 2, 3) + \min(4) = 5 $ . It can be shown that this is the maximum possible beauty.

In the second test case, there is only one array, so regardless of the movements, the beauty will be $ \min(100, 1, 6) = 1 $ .

## 样例 #1

### 输入

```
3
2
2
1 2
2
4 3
1
3
100 1 6
3
4
1001 7 1007 5
3
8 11 6
2
2 9```

### 输出

```
5
1
19```

# 题解

## 作者：Iniaugoty (赞：5)

大意：有 $n$ 个长度为 $m _ i$ 的序列 $a_i$，可以把一个序列的最多一个数移到另一个序列，最大化每个序列的最小值之和。

很简单的题，~~但我未知原因写了 40min 才写出来~~。

容易发现，只有每个序列的最小值和次小值（非严格）才有可能产生贡献。因为次小值是相对大的，所以就要尽可能地增加次小值的贡献，也就是减少最小值的贡献（~~废话~~）。这时可以把所有序列的最小值挪到和最小值的最小值在一个序列，答案就是其它序列的次小值与最小值的最小值之和。设 $a _ i$ 最小值 $f _ i$，次小值 $g _ i$，则答案为 $\displaystyle (\sum _ {i = 1} ^ n g _ i) + \min _ {i = 1} ^ n \{ f _ i \} - \min _ {i = 1} ^ n \{ g _i \}$。

[code](https://codeforces.com/contest/1859/submission/218548488)

---

## 作者：2huk (赞：3)

# CF1859B

## Description

给定 $n$ 个数组，第 $i$ 个数组长度为 $m_i$。对于每个数组，可以对其进行最多 $1$ 次操作：

- 选择当前数组中的一个数字，并将其移动到其它数组，

求全部操作完后 $\sum_{i = 1}^n \min_{j = 1}^{m_i} a_{i, j}$ 的最小值。

## Solution

如果从当前数组中删除一个最小值，那么这个数组的最小值一定会变大。因此我们首先把所有数组中的最小值取出来。

令第 $i$ 个数组中的最小值记为 $x_i$，那么如果 $x_i < x_j$，并把 $x_i$ 和 $x_j$ 放在同一个数组中，$x_j$ 在计算贡献时相当于无效了。因此我们可以把所有的最小值放在同一个数组中，这样只有最小的一个有贡献，其它的都无效了。

那么把这些最小值放在哪个数组中呢？显然我们需要找到去掉最小值后的最小值（也就是原数组的次小值）最小的数组。

## Code

在代码中，首先我们需要统计出每个数组中的最小值和次小值，然后在次小值数组中把最小的去掉然后求和，最后加上最小值数组中的最小值即可。

```cpp
int T, n;
int k1[N], k2[N]; 	// k1[i] 表示第 i 个数组中的最小值，k2[i] 表示第 i 个数组中的次小值 

int Solve()
{
	n = read();
	
	int res = 0;
	
	fup (i, 1, n)
	{
		int len = read();
		k1[i] = k2[i] = INF;
		while (len -- )
		{
			int a = read();
			if (a < k1[i])
				k2[i] = k1[i], k1[i] = a;
			else if (a < k2[i])
				k2[i] = a;
		}
		res += k2[i];
	}
	
	int mn1 = INF, mn2 = INF;
	fup (i, 1, n)
		mn1 = min(mn1, k1[i]);
	fup (i, 1, n)
		mn2 = min(mn2, k2[i]);
	
	return res - mn2 + mn1;
}
```

---

## 作者：zgy_123 (赞：3)

题目非常好理解，思路也很好想，建议橙 / 黄。

首先我们可以将每个数组的最小值都取出来，这样是最优的。但是，不能只取不放。这时肯定只将一个数组的最小值改变，也就是全放进一个数组是最佳的。但是放进哪个数组呢？首先，取出的数的最小值是确定的，如果放进某个数组，那么那个数组的最小值就会变成取出数的最小值。这样，我们只需要知道当前的每个数组最小值的最小值。

上面这段话有些难懂，让我们用最后一个样例解释一下。

先读入所有数组：
```
1001 7 1007 5
8 11 6
2 9
```
取出数组最小值并记录取出的最小值：
```
1001 7 1007
8 11
9
minn=2
```
计算每个数组的最小值并取最小：
```
7
8
9
最小：7
```
就得到了最优解：将所有取出的数均放入第一个数组中，最小值 $2+8+9=19$。

实际操作时，第二步和第三步可以同时进行。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[50005];
int main(){
	int t,n,m;
	cin>>t;
	while(t--){
		ll min_1=2e9,min_2=2e9,sum=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>m;
			for(int j=1;j<=m;j++) cin>>a[j];
			sort(a+1,a+m+1);
			min_1=min(min_1,a[1]);//min_1表示取出数的最小值
			min_2=min(min_2,a[2]);//min_2表示次小数的最小值
			sum+=a[2];//sum即样例中的9+8+7
		}
		cout<<sum-min_2+min_1<<endl;
	} 
	return 0;
}
```

---

## 作者：SunnyYuan (赞：3)

## 题意

给定 $n$ 个长度为 $m$ 的数组，每个数组可以向别的数组转移**最多**一个数字，任意一个数组都可以接受无穷多的数字，最大化每个数组的最小值之和。

## 做法

考虑贪心。

我们记第 $i$ 个数组的第 $j$ 个数字为 $a_{i, j}$。

我们先对每一个数组按照**升序**进行排序，那我们最不愿意看到的就是 $a_{i, 1}$，因为整个数组的最小值取决于 $a_{i, 1}$。

那我们就把 $n$ 个数组的最小值全部转移到一个数组里面去，假如这个“受害者”是第 $r$ 个数组 $a_r$，让它保存所有的最小值 $a_{i, 1}$。

这样就让除 $a_r$ 以外的数组的第 $2$ 项 $a_{i, 2}$ 重见光明。

那我们也要榨干第 $2$ 项，所以我们选择第 $2$ 项最小的数组作为 $a_r$。

最后计算结果为 $\min\limits_{i = 1}^{n}a_{i, 1} + \sum\limits_{i = 1}^{sz[i]}[i \ne r]a_{i, 2}$。

可以证明这是最优解。

## 代码

注意要开 `long long`。

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 25010;

int n;
vector<int> a[N];

void solve() {
	cin >> n;
	int minn = 0x3f3f3f3f3f3f3f3f, mins = 0x3f3f3f3f3f3f3f3f, ans = 0;
	for (int i = 1; i <= n; i++) {
		int sz;
		cin >> sz;
		a[i].resize(sz);
		for (int& x : a[i]) cin >> x;
		sort(a[i].begin(), a[i].end());
		minn = min(minn, a[i][0]);
		mins = min(mins, a[i][1]);
		ans += a[i][1];
	}
	ans += minn;
	ans -= mins;
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int T;
	cin >> T;
	while (T--) solve();
	return 0; 
} 
```



---

## 作者：ax_by_c (赞：1)

首先，式子是 $ \sum_{i=1}^n \min_{j=1}^{m_i} a_{i,j} $，也就是每一个数组内的最小值的和。

那么因为答案是和最小值有关，所以向一个数组里面加数不可能会让答案变大，能够让答案变大的只有去掉数。

那么去掉什么数呢？

显然，需要去掉最小值。

因为如果不去掉最小值的话是没有办法增加答案的。

所以先把所有数组的最小值都取出来。

当然，这些数是一定要加回去的，那么要加到哪里呢？

其实只需要全部加到当前最小值（次小值）最小的那一个数组即可，因为这些数无论加到哪里都会减小答案，而且原来的答案越小减少的肯定也越小，所以只要加到当前最小值（次小值）最小的那一个数组里即可。

---

## 作者：EricWan (赞：1)

~~一开始读错题了，以为只让移动一个数，没想到是每组只让移动一个数。~~

所有组的所有数的最小值肯定会被计算，那就不如让所有数组的最小值跑到一个数组去，这样计算时就可以加上次小值了，枚举到底跑到那个数组就结束了！

[赛时提交记录](https://codeforces.com/contest/1859/submission/218562704)

---

## 作者：Drind (赞：0)

这题给定 $n$ 个数组，我们可以把每个数组中一个数挪到任意别的数组里，也可以不挪，要使每个数组最小值和最大。

容易发现，每个数组只有最小的两个数是需要保存的，其他数没有意义。

我们很容易想出一个策略，把所有数组的最小值全部挪到一个数组里，然后最大值就变成了其余数组的次小值之和加上所有数组的最小值，那么我们要挪到哪个数组里呢？显然是挪到次小值最小的数组里，找到最小最小值和最小次小值的两个数即可。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int c[N];

void fake_main(){
	long long n,ans=0,tmn1,tmn2; cin>>n; tmn1=tmn2=1e15;
	for(int i=1;i<=n;i++){
		int tmp; cin>>tmp;
		long long mn1,mn2; mn1=mn2=1e15;
		for(int j=1;j<=tmp;j++){
			int k; cin>>k;
			if(k<mn1) mn2=mn1,mn1=k;
			else if(k<mn2) mn2=k; //统计每个数组最小值和次小值
		}
		ans+=mn2;
		tmn1=min(tmn1,mn1);
		tmn2=min(tmn2,mn2);//全局最小最小值和最小次小值
	}
	ans+=tmn1-tmn2;
	cout<<ans<<endl;
}

int main(){
	int t;
	cin>>t;
	while(t--) fake_main();
}

```



---

## 作者：_Only_this (赞：0)

### CF1859B Olya and Game with Arrays 题解

------------

明明很水，却写了 $45$ 分钟。

------------

$t$ 组数据，给定 $n$ 个数组，每个数组的长度为 $m_i$。

对于每个数组，最多只能移到别的数组一个数，求操作后每个数组最小值的和的最小值。

------------

若当前数组的最小值被移出，那么最后统计到的就是次小值，因此考虑预处理每个数组的次小值和所有数的最小值。

然后就是枚举一个数组 $x$，将所有其他数组的最小值全都移到 $x$ 中，最后更新答案即可。

放个代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 5e4+5;
const ll inf = 7e18;
ll T,z,n,minn=inf;
ll minnn[maxn];
vector<ll>a[maxn],A;
inline void Solve(){
	A.clear();
	for(ll i=1;i<=z;i++){
		minnn[i]=inf;
	}
	for(ll i=1;i<=z;i++){
		ll minn=inf;
		for(ll j=0;j<a[i].size();j++){
			if(a[i][j]<minn){
				minnn[i]=minn,minn=a[i][j];
			}
			else{
				if(a[i][j]<minnn[i]){
					minnn[i]=a[i][j];
				}
			}
		}
	}
	ll ans=-inf,sum=0;
	for(ll i=1;i<=z;i++){
		sum+=minnn[i];
	}
//	printf("sum=%lld minn=%lld\n",sum,minn);
//	for(int i=1;i<=z;i++){
//		printf("%lld ",minnn[i]);
//	}
//	printf("\n");
	for(ll i=1;i<=z;i++){
		ans=max(ans,sum-minnn[i]+minn);
	}
	printf("%lld\n",ans);
	minn=inf;
	return ;
}
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&z);
		for(ll i=1;i<=z;i++){
			a[i].clear();
		}
		for(ll i=1;i<=z;i++){
			scanf("%lld",&n);
			for(ll x,j=1;j<=n;j++){
				scanf("%lld",&x);
				a[i].push_back(x);
				minn=min(minn,x);
			}
		}
		Solve();
	}
	return 0;
}
```


---

## 作者：Hisaishi_Kanade (赞：0)

发现全局最小值必然作为某个组的最小值。我们设这个组是 $i$，那么对于 $j\not = i$ 我们将它的最小值放入 $i$，使其取得次小值即可构造。

显然的会有一组不能取到次小值，贪心的将全局最小值放入**次小值最小**的那一组，然后将其他组的最小值也放入这组。

不难发现这就是最优的。

场上拼速度写了一个糟糕的实现。读入每一组对其排序，然后取出第二个值，再排序，将最小的次小值改成全局最小值即可。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
int t, n, i, x, j; long long ret;
const int N=1e5+5;
int a[N], b[N];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		int mn=1<<30;
		ret=0; scanf("%d", &n);
		rep(i, 1, n)
		{
			scanf("%d", &x);
			rep(j, 1, x)
				scanf("%d", a+j), mn=min(a[j], mn);
			sort(a+1, a+x+1);
			b[i]=a[2];
		}
		sort(b+1, b+n+1);
		b[1]=mn; rep(i, 1, n) ret+=b[i];
		printf("%lld\n", ret);
	}
	return 0;
}
```

---

## 作者：FwbAway (赞：0)

## Part 1. 题意简述：

有一个长度为 $n$ 的数组 $m$，数组元素 $m_i \geq 2$，$m_i$ 代表着一个数组 $a$ 的长度，每一个 $a$ 数组都可以被移动一次，移动的规则如下：

- 将 $a$ 数组里的任意一个元素移动到另一个数组中，并在此数组中删除该元素。

- 可以不进行任何元素的移动操作。

现在要使得每个 $a$ 数组的最小值最大，问你这个最大值是多少。

**本题为多组测试数据。**

数据保证数据组数 $t \le 25000$。

对于 $100\%$ 的数据保证 $t,n \le 25000$，$m_i \le 50000$。

## Part 2. 题目分析 + 做法

要使得每个数组的最小值最大，也就是求最值问题，很多人会想到二分，但其实没有那么复杂。

只需要考虑是否可以将此数组的**最小值**转换到其他**最小值小于当前数组的最小值**的数组中去。

```c++
//a[i]为multiset
if (a[i][0] < a[j][0]) {
   //删除a[i][0]，添加至a[j][0]
   f[i] = 1;
}
```

用数学语言表示就是找一个 $\min{\{a\}}$ 放到 $\min{\{b\}}$ 中去使得价值最大。

当然有同时判断如果当前已经数组已经放过了，就可以跳过该数组，访问下一数组了。

```c++
if (f[i] == true) {
	continue;
}
```

综合分析难度：入门。

## Part 3. 题目总结

是一道不错的思维题，可以开拓思维，也可以用来练习手速。

也可以用 vector 或者 priority_queue 这些数据结构来存下巨大的 $a$ 数组。

---

## 作者：Light_az (赞：0)

## 结论题

简化题意：现在有 $n$ 个数组，第 $i$ 个数组有 $m_i$ 个数字，对于每一个数组你可以拿或者不拿 $1$ 个数字放到另外一个数组中，现在求每个数组的最小值的和的最大值是多少。

首先我们发现，每个数组只有最小值和次小值有可能对答案造成贡献，证明如下：

设 $k$ 是某数组中的一个数且不是该数组的最小值或者次小值。

想让 $k$ 有贡献，有两种方式：

- 将该数组删除一些数，使 $k$ 成为最小值。

- 将 $k$ 拿到其他数组，变成其他数组的最小值。

但是由于 $k$ 不是最小值或者次小值，因此我们至少拿走 $2$ 个数才可以让 $k$ 变成当前数组的最小值，因此第一种方式不可能。

设把 $k$ 拿到其他数组数组的最小值是 $x$。 

$k$ 拿到其他数组有两种可能：

- $x \leq k$ ，对答案没有贡献。

- $x > k$，此时 $k$ 变成了最小值，但是答案的贡献由于从 $x$ 变成了 $k$，就会减小了。

因此我们得到了结论：每个数组只有最小值和次小值有可能对答案造成贡献。

然后我们继续推理，首先无论怎么变化，$n$ 个数组中的最小值一定会被选中，因为无论到哪个数组，它永远是最小值。

那么既然最小值一定会加入贡献，而我们又想让贡献尽可能的大，我们可以将其他数组的最小值加入这个最小值所在的数组，这样的话其他数组的贡献从最小值变成了次小值，增加了，而这个最小值所在的数组的贡献没有变化。

但是我们想到，最小值有可能会在一个次大值非常大的数组中，如果我们把最小值拿到另一个数组中，贡献会增加，那么最小值应该放在哪一个数组中？显然是次大值最小的数组，因为最小值的出现会占用一个数组次大值的贡献，因此我们尽可能让这个贡献最小，所以选择次大值最小的数组。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
struct Node{
	ll f,s;//f是最小值,s是次小值
}a[N];
ll b[N];
bool cmp(Node a,Node b){
	return a.s<b.s;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		mn=INT_MAX,ans=0;
		F(i,1,n){
			cin>>m;
			F(j,1,m) cin>>b[j];
			sort(b+1,b+1+m);//排序选次大值最小值
			a[i].f=b[1];
			a[i].s=b[2];
			mn=min(mn,b[1]);//选全部数组最小值
		}
		sort(a+1,a+1+n,cmp);
		F(i,2,n) ans+=a[i].s;//不加入次大值最小的数组
		cout<<ans+mn<<"\n";
	}
 
	return 0;
}
```


---

## 作者：xiaomuyun (赞：0)

- [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1859B)
- [CodeForces 题目传送门](http://codeforces.com/problemset/problem/1859/B)

## 题意理解

$t$ 组数据。每组数据包含 $n$ 个序列，对于每个序列你可以将序列中的 **一个** 数移动到另一个序列中（也可以不做）。求移动后每个序列的最小值之和。

## 思路分析

不难发现：

1. 全部 $\sum\limits_{i=1}^n m_i$ 个数的最小值 $x$ 是一定会被作为某个序列的最小值加入答案的；
2. 对于每个序列的操作肯定是移动最小值。

因此我们可以将每个序列的最小值移动到序列 $i$ 中。那移动到哪个序列呢？

考虑到最终的答案为 $x$ 加上除 $i$ 之外其他序列 **移走最小值之后的最小值**，即 **次小值**。首先我们发现 $x$ 是可以求的定值，其次为了使除了 $i$ 之外其他序列的次小值之和尽可能大，我们不妨让序列 $i$ 为 **次小值最小的那个序列**。然后就非常简单了。

## 代码实现

对于每个序列维护两个数组分别记录最小值和次小值，维护也非常简单，遍历一遍每个数然后判断一下即可。

设遍历到第 $i$ 个序列的数 $v$，且数组 $f_1$ 表示最小值，$f_2$ 表示次小值。则代码如下：

```cpp
if(v<=f1[i]) f2[i]=f1[i],f1[i]=v;
else if(v<f2[i]) f2[i]=v;
```

[AC code](https://codeforces.com/contest/1859/submission/218527219)

无法理解代码的可以私信问我。

---

## 作者：zct_sky (赞：0)

### Description
-----
给定 $n$ 个数组，每个数组有且仅有一个数能移动到别的数组中（也可以不移动）。

最终使得每个数组的最小值总和最大。

求该值。
### Solution
-----

贪心。

将每个数组最小值都移动到同个数组中，该数组最小值为 $n$ 个数组中的最小值，剩余数组的最小值为原数组的次小值。

因此，可将每个数组最小值都移动到次小值最小的数组中，则剩余数组次小值之和最大。

最终答案为：所有次小值之和减去最小的次小值加上 $n$ 个数组中的最小值。
### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
const int N=25e3+7;
int t,n;
int a[N],b[N];
ll ans;
int main(){
	t=read();
	while(t--){
		n=read();ans=0;
		for(int i=1;i<=n;i++){
			int m=read();
			a[i]=b[i]=1e9+7;
			for(int j=1;j<=m;j++){
				int x=read();
				if(x<a[i])b[i]=a[i],a[i]=x;
				else if(x<b[i])b[i]=x;
			}
			ans+=b[i];
		}
		sort(a+1,a+1+n);
		sort(b+1,b+1+n);
		ans-=b[1];
		ans+=a[1];
		printf("%lld\n",ans);
	} 
	return 0;
}
```

---

