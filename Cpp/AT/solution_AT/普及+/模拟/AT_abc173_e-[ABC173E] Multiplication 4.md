# [ABC173E] Multiplication 4

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc173/tasks/abc173_e

$ N $ 個の整数 $ A_1,\ldots,A_N $ が与えられます。

このなかからちょうど $ K $ 個の要素を選ぶとき、選んだ要素の積としてありえる最大値を求めてください。

そして、答えを $ (10^9+7) $ で割った余りを $ 0 $ 以上 $ 10^9+6 $ 以下の整数として出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ |A_i|\ \leq\ 10^9 $

### Sample Explanation 1

要素を $ 2 $ 個選んだときの積としてありえる値は $ 2,-3,-4,-6,-8,12 $ なので、最大値は $ 12 $ です。

### Sample Explanation 2

要素を $ 3 $ 個選んだときの積としてありえる値は $ -24,-12,-8,-6 $ なので、最大値は $ -6 $ です。 これを $ (10^9+7) $ で割った余りである $ 1000000001 $ を出力します。

### Sample Explanation 3

要素を $ 1 $ 個選んだときの積としてありえる値は $ -1,1000000000 $ なので、最大値は $ 1000000000 $ です。

### Sample Explanation 4

答えを $ (10^9+7) $ で割った余りを出力してください。

## 样例 #1

### 输入

```
4 2
1 2 -3 -4```

### 输出

```
12```

## 样例 #2

### 输入

```
4 3
-1 -2 -3 -4```

### 输出

```
1000000001```

## 样例 #3

### 输入

```
2 1
-1 1000000000```

### 输出

```
1000000000```

## 样例 #4

### 输入

```
10 10
1000000000 100000000 10000000 1000000 100000 10000 1000 100 10 1```

### 输出

```
999983200```

# 题解

## 作者：UperFicial (赞：11)

提供一个不需要脑子的做法。

答案肯定是从小到大排序后一段前缀和一段后缀。

我们发现比较两个数的大小可以比较他们 $\log$ 的大小，而 $\log(ab)=\log(a)+\log(b)$，所以我们可以记录前缀 $\log$ 的和与后缀 $\log$ 的和，枚举前缀即可。

重中之重：$\texttt{long double}$。

---

## 作者：XYQ_102 (赞：3)

贪心，先对数组排序，讨论 $k$ 的奇偶性，再两个两个的取。因为两个负数和两个整数的乘积都是正数。

1. $k$ 是奇数，我们先去最大的数作为初始答案，然后特判一下最大数是否为负数，如果最大的数都为负数，且 $k$ 是奇数，显然答案只能为负，这时候我们取最小的正数是最优的，若初始答案为正数，我们就贪心取分别设置两个指针，从左边和右边，贪心地取，谁大取谁即可。
2. $k$ 是偶数同理，直接开始从左边和右边贪心地取，这样肯定保证取 $k$ 个。

此处贪心是可以把 $0$ 的情况计算的。需要注意的时乘的时候要取模，避免爆 long long。

时间复杂度 $\Theta(n\times\log n)$
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5,M=1e6+5,inf=0x3f3f3f3f,mod=1e9+7;
#define mst(a) memset(a,0,sizeof a)
#define lx x<<1
#define rx x<<1|1
#define reg register
#define PII pair<int,int>
#define fi first 
#define se second
ll a[N];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++) scanf("%lld",&a[i]);
	sort(a,a+n);
	int l=0,r=n-1,w=1; 
	ll ans=1;
	if(k&1) ans=a[r--],k--,w=(ans<0?-1:1);
	while(k){
		ll x=a[l]*a[l+1],y=a[r]*a[r-1];
		if(x*w>y*w) ans=(ans*(x%mod))%mod,l+=2;
		else ans=(ans*(y%mod))%mod,r-=2;
		k-=2;
	}
	printf("%lld\n",(ans%mod+mod)%mod);
	return 0;
}
```

---

## 作者：2012_Zhang_ (赞：1)

## 解题思路
首先分类讨论：
1. 当 $K$ 为偶数时，我们可以将正数与负数两个两个取最大值选出，保证乘积为正数，若剩余一正一负，则全部选出。
2. 当 $K$ 为奇数时，我们可以先判断所有数中的最大值是否为负。若为负，则输出绝对值较小的数的乘积。否则将最大值选出，此时 $K$ 为偶数，按偶数处理。

**温馨提示：本题数值极大，建议在合适处取余。**

奉上代码：

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,x[1000000],sum=1;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>x[i];
	sort(x+1,x+n+1);
	int l=1,r=n;
	if(k%2==1){
		if(x[n]<0){
			for(int i=n;i>=n-k+1;i--) sum*=x[i],sum=((sum%1000000007)+1000000007)%1000000007;
			cout<<sum;
			return 0;
		}
		sum=x[n];
		r--,k--,n--;
	}\\处理奇数情况
	while(k>0){
		long long a,b;
		a=x[l]*x[l+1],b=x[r]*x[r-1];
		if(a>b) sum=(sum*(a%1000000007))%1000000007,l+=2,k-=2;
		else sum=(sum*(b%1000000007))%1000000007,r-=2,k-=2;
	}\\处理偶数情况
	cout<<(sum%1000000007+1000000007)%1000000007;\\别忘了取余本人因此卡了3次
    return 0;
}

---

## 作者：StayAlone (赞：1)

先按绝对值从大到小排序，记 $prd = \prod_{i = 1}^k a_i$。

若 $prd\geq 0$，显然答案就是此时的 $prd$。

否则，考虑将其调整为正数。

要变为正数，有两种方法：

1. 除以一个负数，再乘上一个正数；

2. 除以一个正数，再乘上一个负数。

除去的数的下标应在 $[1,k]$ 之间，乘上的数的下标应在 $[k+1,n]$ 之间。

容易证明，若这两种情况都都无法将其变为正数，则答案一定是负数。那么只需要重新按照绝对值从小到大排序，答案为 $ans = \prod_{i = 1}^k a_i$。

下面着重讨论调整为正数的部分。

为了最终答案尽量大，需要让除去的数绝对值尽量小，乘上的数绝对值尽量大。详细地：

1. 对于情况 1，除去 $\max\limits_{i=1\land a_i<0}^k a_i$，乘上 $\max\limits_{i=k+1\land a_i>0}^n a_i$；

1. 对于情况 2，除去 $\min\limits_{i=1\land a_i>0}^k a_i$，乘上 $\min\limits_{i=k+1\land a_i<0}^n a_i$。

取两个答案的较大值即可。注意不要取模之后再判断。

[submission](https://atcoder.jp/contests/abc173/submissions/39594849)

```cpp
int n, k, a[MAXN]; ll ans;
const int mod = 1e9 + 7;
 
il ll qpow(ll a, int b) {
	ll ans = 1, base = a % mod;
	while (b) {
		if (b & 1) (ans *= base) %= mod;
		(base *= base) %= mod; b >>= 1;
	} return ans;
}
int main() {
	read(n, k); rer(i, 1, n, a);
	sort(a + 1, a + 1 + n, [&](const int &x, const int &y){return abs(x) > abs(y);});
	ll ans = 1;
	rep1(i, 1, k) (ans *= a[i]) %= mod;
	if (ans >= 0) return printf("%lld", ans), 0;
	int s1 = -inf, s2 = -inf, t1 = inf, t2 = inf;
	rep1(i, 1, k) if (a[i] < 0) s1 = max(s1, a[i]);
	rep1(i, k + 1, n) if (a[i] > 0) s2 = max(s2, a[i]);
	rep1(i, 1, k) if (a[i] > 0) t1 = min(t1, a[i]);
	rep1(i, k + 1, n) if (a[i] < 0) t2 = min(t2, a[i]);
	long double p1 = s1 != -inf && s2 != inf ? (long double)s2 / s1 : inf;
	long double p2 = t1 != -inf && t2 != inf ? (long double)t2 / t1 : inf;
	ll q = -1;
	if (s1 != -inf && s2 != -inf) q = ans * qpow(s1, mod - 2) % mod * s2 % mod;
	if (t1 != inf && t2 != inf && p2 < p1) q = ans * qpow(t1, mod - 2) % mod * t2 % mod;
	if (~q) ans = q;
	if (ans < 0) {
		sort(a + 1, a + 1 + n, [&](const int &x, const int &y){return abs(x) < abs(y);});
		ans = 1;
		rep1(i, 1, k) (ans *= a[i]) %= mod;
	} printf("%lld", (ans + mod) % mod);
	rout;
}
```

----------

upd 2023/3/12：修改一处有歧义的表述。

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc173_e)
## 思路
首先，如果要将答案最大化，我们可以将数列 $a$ 从小到大排序，然后两两配对（避免乘上一个负数）。然后就可以贪心。每次选择最前面两个数的乘积和最后面两个数的乘积，哪个大就选哪个。

注意，算答案时带上取模。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, mod = 1e9 + 7;

int n, k;
int a[N];

bool cmp(int x, int y)
{
	return x > y;
}

int main()
{
 	scanf("%d%d", &n, &k);
 	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1, cmp);
	int l = 1, r = n, m = 1; // 双指针
	long long ans = 1;
	if (k % 2 == 1)
	{
 		ans = a[1];
		if (ans < 0) m = -1;
 		l++;
		k--;
	}
	while (k > 0) 
	{
		long long a_ = 1ll * a[l] * a[l + 1], b_ = 1ll * a[r] * a[r - 1]; 
		if (a_ * m > b_ * m)
		{
			ans = ((a_ % mod) * ans) % mod; // 带上取模
			l += 2;
		}
		else
		{
			ans = ((b_ % mod) * ans) % mod;
			r -= 2;
		}
		k -= 2;
	}
	printf("%lld\n", (ans % mod + mod) % mod); // 最后输出时，小心取模顺序
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

## 思路

首先注意到最好的情况就是有偶数个负数，否则算出来的乘积是负的，并不好。因此我们要极力避免选择奇数个负数的情况。

注意到当 $k$ 为奇数的时候，只要存在至少一个正数，我就一定可以成功选择偶数个负数，而 $k$ 为偶数的时候并不需要有正数。所以我们可以先按照是否有正数分类，再按照 $k$ 的奇偶性分类。

### 关于零

注意到当 $0$ 的个数加上 $k$ 大于 $n$ 时，我们无论怎么选择 $k$ 个数总会选择到 $0$，因此此时答案为 $0$。

### 不存在任何正数

对于 $k$ 为偶数的情况，显然从绝对值最大的数开始，向绝对值更小的数选择 $k$ 个。答案即为这些数的乘积。

对于 $k$ 为奇数的情况，显然从绝对值最小的数开始，向绝对值更大的数选择 $k$ 个。然而这样做并不完全对，如果数列中存在 $0$，那么 $0$ 显然大于这些数的乘积。因此如果数列中存在 $0$ 答案就是 $0$，否则输出这些数的乘积。

### 存在正数

考虑 $k$ 为奇数的情况，显然选择奇数个正数、偶数个负数更优，因此我必然会选择最大的正数。选择最大的正数并删掉它后，问题归纳为 $k$ 为偶数。

对于 $k$ 为偶数，选择偶数个正数、偶数个负数显然也更优，因此我们将所有正数从大到小排序，负数按照绝对值从大到小排序，然后相邻的两两组合：最大的正数和次大的正数组合，第三大和第四大组合，并以此类推。负数类似。

然后问题转变为选择乘积最大的 $\frac{k}{2}$ 个组，贪心地将所有组处理出来按乘积从大到小排序即可。

但是这样做是有问题的。注意到负数和正数的数量可能是奇数，因此最后可能会剩余 $1$ 个正数或负数，或者各 $1$ 个没有成功分组。如果总的组数不足 $\frac{k}{2}$ 那么这些剩下的数我们也必须拿来用。

剩余 $1$ 个正数或负数是不会影响答案的，如果剩余 $1$ 个数我们却还需要一个组，那么就说明 $k>n$，怎么选都选不够。

但是如果剩下的是 $2$ 个数，那我可能必须选择这两个数来填上差的一个组。可以注意到这种情况其实就是 $k=n$，所以特判 $k=n$ 即可。

对于一般情况，选择乘积最大的 $\frac{k}{2}$ 个组时，需要注意排序组的乘积的时候不能取模后再排序，但算乘积的时候必须先模再乘，否则会爆 `long long`。

## 代码

```
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
#define ll long long
#define ull unsigned long long
#define inf INT_MAX
#define uinf INT_MIN
#define pii pair<int,int>
#define pll pair<ll,ll>
#define debug puts("--------Chery AK IOI--------");
#define Yes cout<<"Yes"<<endl;
#define No cout<<"No"<<endl;
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define ptc putchar
using namespace std;
int n,k;
vector <ll> pos,uos;
ll ans=1;
ll x;
int cnt;
const ll M=1e9+7;
vector <ll> up;
int main(){
	cin>>n>>k;
	fr1(i,1,n){
		cin>>x;
		ans*=x;
		ans%=M;
		if(x>0){
			pos.pb(x);
		}
		else if(x<0){
			uos.pb(x);
		}
		else{
			cnt++;
		}
	}
	if(cnt+k>n){//特判0太多了
		cout<<"0"<<endl;
		ET;
	}
	if(k==n){//特判k=n
		cout<<(ans+M)%M<<endl;
		ET;
	}
	sort(pos.begin(),pos.end());//正数从小到大排序
	sort(uos.begin(),uos.end());//负数从小到大排序
	if(pos.size()==0){//没有正数
		ans=1;
		if(k%2){
			if(cnt){//有0就选择0
				cout<<"0"<<endl;
				ET;
			}
			reverse(uos.begin(),uos.end());//把负数反转过来，让绝对值小的数在前面
			fr1(i,0,k-1){
				ans*=uos[i];
				ans%=M;
			}
			cout<<(ans+M)%M<<endl;
		}
		else{
			fr1(i,0,k-1){//直接从绝对值大的开始选
				ans*=-uos[i];
				ans%=M;
			}
			cout<<ans%M<<endl;
		}
	}
	else{
		ans=1;
		if(k%2){
			ans=pos[pos.size()-1];//取走最大的正数
			pos.pop_back();
			k--;
		}
		reverse(pos.begin(),pos.end());//把正数反转过来，让绝对值大的数放在前面
		fv(i,pos){
			up.pb(pos[i]*pos[i+1]);
			i++;
		}
		fv(i,uos){
			up.pb(uos[i]*uos[i+1]);
			i++;
		}//两两分组
		sort(up.begin(),up.end());
		reverse(up.begin(),up.end());//让组按乘积从大到小排序
		int l=0;
		while(k){
			ans*=up[l]%M;
			ans%=M;
			l++;
			k-=2;
		}//暴力选择前k/2个即可
		cout<<ans<<endl;
	}
	ET;
}
```

[AC 记录](https://www.luogu.com.cn/record/104291197)

---

