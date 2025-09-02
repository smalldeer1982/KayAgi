# Another Permutation Problem

## 题目描述

Andrey is just starting to come up with problems, and it's difficult for him. That's why he came up with a strange problem about permutations $ ^{\dagger} $ and asks you to solve it. Can you do it?

Let's call the cost of a permutation $ p $ of length $ n $ the value of the expression:

  $ (\sum_{i = 1}^{n} p_i \cdot i) - (\max_{j = 1}^{n} p_j \cdot j) $ . Find the maximum cost among all permutations of length $ n $ .

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the permutation with the maximum cost is $ [2, 1] $ . The cost is equal to $ 2 \cdot 1 + 1 \cdot 2 - \max (2 \cdot 1, 1 \cdot 2)= 2 + 2 - 2 = 2 $ .

In the second test case, the permutation with the maximum cost is $ [1, 2, 4, 3] $ . The cost is equal to $ 1 \cdot 1 + 2 \cdot 2 + 4 \cdot 3 + 3 \cdot 4 - 4 \cdot 3 = 17 $ .

## 样例 #1

### 输入

```
5
2
4
3
10
20```

### 输出

```
2
17
7
303
2529```

# 题解

## 作者：vanishingloser (赞：6)

~~想了好久才发现规律，我好菜~~


------------

这是一道找规律的题目。

首先先手玩数据。发现当 $N=1,2,3,4$ 时的最优解如下:
```
n=1:1
n=2:1 2
n=3:1 3 2
n=4:1 2 4 3
```
这不就是翻转后缀吗？

然后再考虑 $n=8,n=10$ 时的情况，发现依旧符合此规律。

于是就可以暴力枚举翻转后缀的长度，然后将后缀翻转求出每一种情况的结果，再求出最大值即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=255;
int t,n,m,x,a[N];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		int ans=0,maxn=0;
		for(int i=1;i<=n;++i)a[i]=i;
		for(int i=1;i<=n;++i)
		{
			int sum=0;
			reverse(a+i,a+n+1);
			for(int j=1;j<=n;++j)
			{
				sum+=j*a[j];
				maxn=max(maxn,j*a[j]);
			}
			ans=max(ans,sum-maxn);
			reverse(a+i,a+n+1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：4)

简单题，但有个奇怪做法。

我们不妨用枚举全排列的方式去打个 $n \in [1, 10]$ 的表，代码很好写。

```cpp
void solve(int n) {
  vector<int> a(n);
  int mx = -1;
  _rep(i, 0, n) a[i] = i + 1;
  do {
    auto calc = [&]() {
      int cnt = 0, mx = 0;
      _rep (i, 0, n) cnt += a[i] * (i + 1);
      _rep (i, 0, n) mx = max(a[i] * (i + 1), mx);
      return cnt - mx;
    };
    int k = calc();
    if (k > mx) {
      mx = k;
    }
  } while (next_permutation(a.begin(), a.end()));
  _rep(i, 0, n) a[i] = i + 1;
  do {
    auto calc = [&]() {
      int cnt = 0, mx = 0;
      _rep (i, 0, n) cnt += a[i] * (i + 1);
      _rep (i, 0, n) mx = max(a[i] * (i + 1), mx);
      return cnt - mx;
    };
    int k = calc();
    if (k == mx) {
      for (auto i : a) cout << i << ' ';
      cout << '\n';
    }
  } while (next_permutation(a.begin(), a.end()));
  
  cout << '\n';
}
```

这个代码的输出是

```
1

2 1

1 3 2

1 2 4 3
1 4 3 2

1 2 5 4 3

1 2 3 6 5 4

1 2 3 4 7 6 5
1 2 3 7 6 5 4

1 2 3 4 8 7 6 5

1 2 3 4 5 9 8 7 6

1 2 3 4 5 6 10 9 8 7
```

然后你可以观察到，这些排列都是将一个形如 $1, 2, 3, \cdots, n$ 的排列的一个后缀翻转得到的。

枚举从哪里开始翻转后缀，依次计算每一种情况的答案即可。


```cpp
void solve() {
  int n; cin >> n;
  rep (i, 1, n) {
    a[i] = i;
  }
  int ans = 0;
  auto calc = [&]() {
    int cnt = 0, mx = 0;
    rep (i, 1, n) cnt += a[i] * i;
    rep (i, 1, n) mx = max(a[i] * i, mx);
    return cnt - mx;
  };
  rep (i, 1, n) {
    reverse(a + i, a + n + 1);
    ans = max(calc(), ans);
    reverse(a + i, a + n + 1);
  }
  cout << ans << '\n';
}
```

---

## 作者：SunnyYuan (赞：3)

## 思路

我们实际上发现它计算的就是 $p_i \cdot i$ 的和再减去一个 $p_i \cdot i$ 中的最大值。

那我们可以枚举这个最大值 $p_x \cdot x$，这个值就是最后和中需要删除的数值。

这里我们可以使用贪心。

我们可以从 $n \sim 1$ 枚举除 $p_i$ 的每个数字需要配的数字。

当然，越大的数字 $p_i$，配的数字 $i$ 也应该越大，这样才能使和最大。

我们还要注意选最大的 $p_i \cdot i$ 一定不能超过 $p_x \cdot x$。

加一些剪枝就过了。

最坏时间复杂度：$O(n^4)$，最多需要跑 $4.6 \times 10^9$ 次。

因为时间限制有 $3$ 秒（不要质疑 CF 的机子），所以放心跑。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 260;

bool vis[N];

void solve() {
	int n, ans = 0;
	cin >> n;
	int res = 0;
	for (int a = 1; a <= n; a++) {
		for (int b = 1; b <= n; b++) {
			int maxx = a * b, ans = 0;
			if (maxx < n) continue;
			if (a * b * n <= res) continue;
			memset(vis, 0, sizeof(int) * (n + 10));
			vis[b] = true;
			for (int i = n; i >= 1; i--) {
				if (i == a) continue;
				int maxp = min(n, maxx / i);
				while (maxp >= 1 && vis[maxp]) maxp--;
				if (maxp == 0) {
					ans = -0x3f3f3f3f;
					break;
				}
				vis[maxp] = true;
				ans += maxp * i;
			}
//			cout << a << ' ' << b << ' ' << ans << endl;
			res = max(res, ans);
		}
	}
	cout << res << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int T;
	cin >> T;
	while (T--) solve();
	return 0; 
} 
```



---

## 作者：masonpop (赞：2)

讲一讲此题的 $O(n^2)$ 做法。其通过了正式测试但是我不会证明。貌似官方题解也没有很好的证明。如果有会证明的大佬可以私信我做法。

我们首先考虑爆搜出所有可能的情况寻找最优解。这部分我的参考程序如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=510;
const int inf=1e15;
int t,n,a[maxn],ans;
int p[maxn];
inline int calc()
{
	int maxx=0,res=0;
	for(int i=1;i<=n;i++)res=(res+a[i]*i),maxx=max(maxx,a[i]*i);
	return res-maxx;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)a[i]=i;
	int ans=0;
	do{
		int val=calc();
		if(val>ans)
		{
			ans=val;
			for(int i=1;i<=n;i++)p[i]=a[i];
		}
	}while(next_permutation(a+1,a+n+1));
	for(int i=1;i<=n;i++)printf("%lld ",p[i]);
	puts("");
	return 0;
}
```

通过把 $n=1,2,\cdots, 10$ 塞进去跑一遍，我们得到了规律。如 $n=8$ 时最优解是 `1 2 3 4 8 7 6 5`。而 $n=10$ 时最优解是 ` 1 2 3 4 5 6 10 9 8 7`。于是我们猜测，最优解一定形如 $1,2,\cdots ,k,n,n-1,\cdots, k+1$。枚举所有的 $k$ 并计算答案便通过了此题，复杂度 $O(n^2)$。[代码](https://codeforces.com/contest/1859/submission/218739981)。

---

## 作者：Hoks (赞：1)

## 前言
[传送门](https://www.luogu.com.cn/blog/Hok/solution-cf1859c)，个人博客内使用更佳哦！[题目链接](https://www.luogu.com.cn/problem/CF1859C)

------------
## 题意
给定序列长度 $n$ ，求排列中去掉 $p_i\cdot i$ 的最大值后的最大 $p_i\cdot i$ 和。

------------
## 思路分析
首先我们考虑最容易想到的情况，$1,2,\cdots n$，这时我们会发现这种情况在 $n\ge3$ 时肯定不是最大，因为 $n^2-(n-1)^2$ 太大了。

由此我们得出第一种尝试：$1,2,\cdots n,n-1$。

结果一试，没过样例中 $n=10$ 的情况，输出所有 $p_i\cdot i$ 的结果发现是 $n\cdot(n-1)-(n-2)^2$ 太大了，由此我们得出最终的方法。

从 $n-1$ 开始枚举断点 $k$，前面的正序排，后面的倒序排，暴力计算结果，如果结果比目前答案还大就结束枚举。

------------
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int a[510];
int ans;
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
signed main()
{
	t=read();
	while(t--)
	{
		n=read();ans=0;
		for(int i=1;i<=n;i++) a[i]=i;
		for(int k=n-1;k>=1;k--)
		{
			int num=0,maxx=0;
			reverse(a+k,a+1+n);
			for(int i=1;i<=n;i++) num+=a[i]*i,maxx=max(maxx,a[i]*i);
			reverse(a+k,a+1+n);num-=maxx;
			if(num<ans) break;
			ans=num;
		}
		printf("%lld\n",ans);
	}
    return 0;
}
```


---

## 作者：lwx20211103 (赞：0)

## 题意

翻译已经有了，这里不赘述。

## 解法

我在做这题的时候最开始没什么头绪，先写个暴力枚举排列打表找规律。

```cpp
int n, maxn = 0, nums[114514], now[114514];
bool mark[114514];

void dfs(int p)
{
	if (p > n)
	{
		int sum = 0, x = 0;
		for (int i = 1; i <= n; i++)
		{
			sum += nums[i] * i;
			x = max(x, nums[i] * i);
		}
		sum -= x;
		if (sum > maxn)
		{
			maxn = sum;
			for (int i = 1; i <= n; i++)
				now[i] = nums[i];
		}
		return ;
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			if (!mark[i])
			{
				mark[i] = 1;
				nums[p] = i;
				dfs(p + 1);
				mark[i] = 0;
			}
		}
	}
}

int main()
{
	cin >> n;
	dfs(1);
	cout << maxn << "\n";
	for (int i = 1; i <= n; i++)
		cout << now[i] << " ";
	return 0;
}
```
结果：
```
#2
2
2 1

#3
7
1 3 2

#5
35
1 2 5 3 4

#8
152
1 2 3 4 8 7 6 5

```

明白了，只要枚举每一个 $i \in [1,n]$，那么反转 $i$ 到 $n$ 的数字，统计答案就行了。tag 里面有 dp 和数学，但是我这个蒟蒻没有观察到。

平方求和的公式：

$$\sum_{i=1}^{n}=\frac{n(n+1)(2n+1)}{6}$$

## 代码
核心代码：
```cpp
int nums[114514];

void solve()
{
	ll ans = 0;
	int n, pos;
	cin >> n;
	for (int i = 1; i <= n; i++)
		nums[i] = i;
	for (int i = 1; i <= n; i++)
	{
		ll sum = 0, maxn = 0;
		vector<ll> v;
		for (int j = i; j <= n; j++)
			v.p_b(j);
		reverse(v.begin(), v.end());
		int a = i - 1;
		sum += a * (a + 1) * (a << 1 | 1) / 6;
		for (auto j : v)
			sum += (++a) * j, maxn = max(maxn, a * j);
		ans = max(sum - maxn, ans);
	}
	cout << ans << "\n";
}
```


---

## 作者：Drind (赞：0)

这道题显然的我们要构造几个差不多大的数，使得去掉一个最大值之后另外几个也和他差不多大，所以我们的排列可以是这样的：
$$1,2,\dots,k,n,n-1,\dots,k+2,k+1$$
这样，从第 $k+1$ 项到第 $n$ 项倒过来，这样后面几项的大小就差不多了，枚举 $k$ 的位置即可。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;

long long fake_main(int x){
	long long tot=0;
	for(int i=1;i<=x;i++){//枚举k
		long long ans=0,mx=0;
		for(int j=1;j<x-i+1;j++) ans+=j*j;//前面几项都是平方和，相加即可
		for(int j=x-i+1;j<=x;j++){//后面几项是反过来的，计算每个数应该乘上多少
			ans+=j*(2*x-i+1-j);
			mx=max(mx,j*(2ll*x-i+1ll-j));//统计最大值
		} 
		ans-=mx;
		tot=max(tot,ans);
	}
	return tot;
} 

int main(){
	int t; cin>>t;
	while(t--){
		int n; cin>>n;
		cout<<fake_main(n)<<endl;
	}
}
```

---

## 作者：EricWan (赞：0)

~~第一次猜结论猜错了，赛时吃了一个罚分。好像猜对了，写挂了？不知道。~~

时间充裕，数据急小。这题我们一看，不知道正解，不如猜一猜结论：**如果一个序列不可能出现 $a_i\times i$ 的最大值，不妨把这个区间的数升序排列**，所以最后的产生答案的数组肯定是 $\{1,2,\dots,n\}$ **翻转某个子区间**得到的，于是我们枚举每个可能被翻转的区间计算答案即可，时间复杂度为 $O(n^3)$，[AC](https://codeforces.com/contest/1859/submission/218565102)。

虽然这个方法好像不是最优解，但这个解法保准没错，因为数据量小于是也可以快活地通过。

---

## 作者：Wf_yjqd (赞：0)

一个很神奇的结论，反正比正解简单多了。

------------

考虑枚举最终最大的数和位置乘积所在的位置，一定要放最大数，这样浪费的位置最小。

在不破坏最大的乘积的情况下，剩下的数如何摆放呢？

考虑先按数的大小排序，这样位置在最大乘积前的一定能达到和的最大值。

而后面的数需要考虑可能超过最大数的情况，为了避免这种情况，大的位置要匹配小的数。

同时为了使总和最大，最大要匹配最小，转换问题为一个 $1$ 到 $n$ 从小到大的排列翻转一个后缀后答案的最大值。

枚举后缀计算即可。

复杂度 $\operatorname{O}(n^2)$。

------------

这题真挺有趣的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,ans,res,mx,a[584];
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        ans=-0x3f3f3f3f3f3f3f3f;
        for(ll i=n;i>=1;i--){
            for(int j=1;j<=n;j++)
                a[j]=j;
            for(int j=1;i+j-1<=n-j+1;j++)
                swap(a[i+j-1],a[n-j+1]);
            mx=-0x3f3f3f3f3f3f3f3f;
            res=0;
            for(ll j=1;j<=n;j++){
                res+=j*a[j];
                mx=max(mx,j*a[j]);
            }
            ans=max(ans,res-mx);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：SusieRain (赞：0)

~~这是本人第一次写题解能不能给个机会（~~
------------
看到基本上都是 $n^2$ 写法居然没有人写 $n\log n$ 做法，这个写法也是我打表找出来的。构造方法就是前面是从 $1$ 开始递增然后在某一个点翻转从 $n$ 开始递减，暴力写法是枚举翻转点，但是实际上这个点是可以三分求的，（打表发现）反转点从 $1 - n$ 求出来的 $cost$ 是先增后减的~~但是证明我不会~~。代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll ;
int n , m , k , l ;
int a[260] ;
ll check(int idx) {
    ll res = 0 ;
    for(int i=1;i<idx;i++) {
        a[i] = i ;
    }
    a[idx] = n ;
    for(int i=idx+1;i<=n;i++){
        a[i] = n - i + idx ;
    }
    ll mx = 0 ;
    for(int i=1;i<=n;i++){
        res += i * a[i] ;
        mx = max(mx,i*a[i]) ;
    }
    return res - mx ;
}
void solve(){
    cin >> n;
    if(n==2) {
        cout<<2<<'\n';
        return;
    }
    int l = 1 , r = n ;
    int ans = 0 ;
    while (l<=r){
        int mid = ( l + r ) >> 1 ;
        if(check(mid)< check(mid+1)) {
            l = mid + 1 ;
            ans = l ;
        }
        else r = mid - 1 ; // check(mid) > check(mid+1)
    }
    cout<<check(ans)<<'\n';
}
signed main(){
    ios::sync_with_stdio(false) ;
    cin.tie(0) ;
    int tt = 1 ;
    cin >> tt ;
    while (tt--) solve() ;
    return 0 ;
}
```


---

