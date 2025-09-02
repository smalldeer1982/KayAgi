# [ABC346C] Σ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc346/tasks/abc346_c

長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N) $ および正整数 $ K $ が与えられます。

$ 1 $ 以上 $ K $ 以下の整数のうち、$ A $ の中に一度も現れないものの総和を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ K\ \leq\ 2\times\ 10^9 $
- $ 1\leq\ A_i\ \leq\ 2\times\ 10^9 $
- 入力は全て整数
 
### Sample Explanation 1

$ 1 $ 以上 $ 5 $ 以下の整数のうち、$ A $ の中に一度も現れないものは $ 2,4,5 $ の $ 3 $ つです。 よって、それらの総和である $ 2+4+5=11 $ を出力します。

## 样例 #1

### 输入

```
4 5
1 6 3 1```

### 输出

```
11```

## 样例 #2

### 输入

```
1 3
346```

### 输出

```
6```

## 样例 #3

### 输入

```
10 158260522
877914575 24979445 623690081 262703497 24979445 1822804784 1430302156 1161735902 923078537 1189330739```

### 输出

```
12523196466007058```

# 题解

## 作者：_KHIN (赞：8)

### 题意描述
给你一个长度为 $N$ 的正整数序列 $A$ 和一个正整数 $K$，求在 $1$ 与 $K$ 之间，未出现在序列 $A$ 中的整数之和。
### 思路描述
显然，最终答案一定为 $1+2+\cdots+K$ 减去所有出现过且在 $1$ 与 $K$ 之间的 $A_i$（数值相同的话，只计算一次），（因为去掉了出现在 $A$ 中的数，剩下的就是未出现的了）。
### 具体实现
我们先用高斯求和公式求出 $1+2+\cdots+K$，然后我们维护一个数组 $cnt$（因为 $K$ 过大，所以要用 map）。$cnt_i$ 表示 $i$ 是否在 $A$ 中出现过，统计答案时减去所有在原数组中出现过的数即可。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[200005],ans;
map <int,int> cnt;//map
signed main()
{
	cin>>n>>k;
	ans=(k+1)*k/2;//高斯求和公式
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]<=k)//在1到K范围内
		{
			if(!cnt[a[i]])//以前出现过
			{
				ans-=a[i];//修改答案
				cnt[a[i]]=1;//标记
			}
		}
	}
	cout<<ans;
   	return 0;
}
```

---

## 作者：Little_x_starTYJ (赞：4)

### 题目大意
给你一个序列 $A$，请求出 $1\sim K$ 中，没有在 $A$ 中出现过的数的总和。

### 解题思路
首先，这道题目不能够使用桶，因为 $K$ 的范围太大，会超时，因此，我们可以计算出 $1\sim K$ 中的所有数的总和，再减去在 $A$ 中出现过的数的总和就可以快速地得到答案。

**注意：**

1. 为了快速计算出 $1\sim K$ 中的数的总和，我们可以使用等差数列求和公式。
2. 在减去在 $A$ 中出现过的数的总和时，$A_i$ 可能重复，又因为 $A_i$ 范围太大不能使用数组标记，所以我们需用 `map` 标记，避免重复减去 $A_i$。
3. 由于 $K$ 和 $A_i$ 的范围太大，答案需使用 `long long` 类型存储。

CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[200010];
map<long long, bool> m;
int main() {
	long long n, k;
	cin >> n >> k;
	long long sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] <= k && !m[a[i]])
			sum -= a[i], m[a[i]] = 1;
	}
	sum += (1 + k) * k / 2;
	cout << sum;
	return 0;
}
```

---

## 作者：Melo_DDD (赞：2)

来一发详细一点的题解，~~这么水的题居然没人抢。~~

# 题目大意

建议你谷把翻译加进社贡里面。

给定一个长度为 $n$ 的数列，求没有在这个数列中出现过的 $[1 ,k]$ 中的整数之和。

# 实现方法

数据范围 $2\times10^9$，这就注定了我原先想的枚举模拟是失败的。

难点在于如何找是否出现，逐一比较肯定不行，突然想到 set 自带去重。

问题迎刃而解，之后用迭代器遍历即可，注意迭代器不支持大小比较操作，只能用 $\ne$。

求答案，正难则反，既然直接统计不好求，不如用总和减去出现在数列中的整数的和。

## 上代码

```cpp
#include <bits/stdc++.h>
#define int long long //范围过大开 long long
#define rep(i ,m ,n) for (int i = (m) ;i <= (n) ;i ++)
#define IOS ios :: sync_with_stdio(0) ;cin.tie (0) ;cout.tie (0)
using namespace std ;
int n ,k ,sum ,num ;
set <int> s ;
signed main () {
	cin >> n >> k ;
	sum = (k + 1) * k / 2 ; //等差数列求和公式不讲
	rep (i ,1 ,n) {
		int x ;
		cin >> x ;
		if (x <= k) {
			s.insert (x) ; //插入操作
		}
	}
	set <int> :: iterator it ; //声明迭代器
	it = s.begin () ; //从第一项开始
	for ( ;it != s.end () ;it ++) { //下表是从 0 开始存的所以枚举到结尾往前一个
		num += *it ; //返回迭代器指向的值
	}
	cout << sum - num << endl ;
	return 0 ;
}
```

你是否承认卡芙卡的美貌举世无双？

---

## 作者：CEFqwq (赞：2)

我们发现 $k$ 很大 $n$ 很小，所以我们直接用公式求出 $1 + 2 + \dots + k$（这里没有用 $\Sigma$ 是为了便于萌新理解），然后用 `map` 去重，减去所有出现的 $1 \sim k$ 的数即可。

注意 $k$ 要开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long k;
__int128 ans;
long long a[400005];
map<long long, bool> mp;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> k;
	if (k & 1)
		ans = (k + 1) / 2 * k;
	else
		ans = k / 2 * (k + 1);//公式，防止乘积过大分类讨论
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		if (mp[a[i]])
			continue;
		mp[a[i]] = 1;
		if (a[i] <= k)//没减过的不大于 k 的数
			ans -= a[i];
	}
	cout << (long long)ans;
}
```

---

## 作者：fengzhaoyu (赞：1)

## 题意
输入一个长 $n$ 数组$A$， $1$ 到 $k$ 中哪些数没有出现在数组 $A$ 中，求他们的和。例如，当数组 $a$ 中有 $1$，$2$，$4$，$k=5$，则 $3$，$5$ 没有出现在 $a$，所以答案为 $3+5=8$。
## 思路
1，本蒟蒻在比赛中想不出有什么好方法，所以用暴力。

2，为了使程序不爆，此处用一个优化：先排序，等差数列求 $1$ 到 $k$ 之和，再去重与减去在 $a$ 中出现了的，即可。
注意：不开 long long 见祖宗。
 
听不懂的可以看代码理解。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[10000009];
int main()
{
	long long n,k;
	cin>>n>>k;
	for(long long i=1;i<=n;i++) //读入
	{
	  cin>>a[i];
	}
	sort(a+1,a+1+n);//快排，方便去重
	long long sum=(1+k)*k/2;//等差数列求和
	for(long long i=1;i<=n;i++)
	{
		if(a[i]!=a[i-1]&&a[i]<=k)//判断是否重复或已出现
		sum-=a[i];//减掉
	}
	cout<<sum;//输出
	return 0;
}
```

---

## 作者：maokaiyu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc346_chttps://www.luogu.com.cn/problem/AT_abc346_c)
## 思路
可以发现，如果只是遍历 $1$ 到 $k$ 的正整数，时间复杂度是很大的。我们不妨倒着思考，先将 $1$ 到 $k$ 的和求出来。对于每个读入，我们只需要将第一次出现的 $a_i$ 从和中减去就好。  
**注意**：要满足 $a_i \leq k$。
## 细节
* 求和：应当使用高斯求和，不然会超时。
* 存储：把出现的元素丢进 map 中，使用查找函数判断是否出现。 
* 输出：答案要开 longlong。

## AC 代码：
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
I n,a[200010];
LL k,s;
map<I,I>r;
I main(){
	scanf("%d%lld",&n,&k);
	s = (1 + k) * k / 2;
	for(I i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		if(!r[a[i]] && a[i] <= k){
			r[a[i]] = true;
			s -= a[i];
		}
	}
	printf("%lld\n",s);
	return 0;
}
```

---

## 作者：xxboyxx (赞：1)

### 翻译

给一个长度为 $N$ 的序列 $A$，求小于等于 $K$ 的数中没有出现在序列 $A$ 中的数的和是多少。

### 思路

$K$ 是很大的，但是 $N$ 并不大，那么完全可以先算出 $1 \sim K$，然后再减去在 $A$ 中小于等于 $K$ 且**相同的数仅减一次**。

### 注意

因为相同的数仅减一次，所以需要使用一个桶进行判重。$1$ 至 $K$ 求和则可以使用求和公式 $\frac{(K+1)\times K}{2}$ 求出。

### 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,ans;
int a[1000005];
map<int,int> p;//判重的桶 
signed main()
{
	cin>>n>>k;
	ans=k*(k+1)/2;//求和 
	for (int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if (x<=k && p[x]==0)//未出现过 
			ans-=x;
		p[x]=1;//标记 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：OIer_Tan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc346_c)

## 题意

给你一个长度为 $N$ 的正整数序列 $A=(A_1,A_2,\dots,A_N)$ 和一个正整数 $K$。

求序列 $A$ 中没有出现的介于 $1$ 与 $K$ 之间的整数之和。

## 思路

显然，直接暴力统计没有出现的数会爆空间。但是我们可以想到将 $1\sim K$ 的和先算出来（$\sum^{K}_{i=1}{i}=\frac {(K+1)K}{2}$），然后再减掉 $A$ 中出现的数。前半部分明显为 $O(1)$，后半部分求和应为 $O(N)$ 的。

## 注意

要开 `long long`。

减去 $A$ 中的数时要去重，相同的数只能减一次。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n , k , a [N] ;

ll sum = 0 ;

unordered_set <ll> cnt ;

int main ()
{
	// freopen ( ".in" , "r" , stdin ) ;
	// freopen ( ".out" , "w" , stdout ) ;
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> k ;
	sum = ( k + 1 ) * k / 2 ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> a [i] ;
		if ( 1 <= a [i] && a [i] <= k )
		{
			if ( cnt.find ( a [i] ) == cnt.end () )
			{
				sum -= a [i] ;
			}
		}
		cnt.insert ( a [i] ) ;
	}
	cout << sum << endl ;
	return 0 ;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## AT_abc346_c [ABC346C] Σ 题解
### 题意

给你一个长度为 $N$ 的正整数序列 $A$ 和一个正整数 $K$ 。

求在 $1$ 与 $K$ 之间，未出现在序列 $A$ 中的整数之和。

### 分析
由于数据范围较大，我们可以先利用等差数列求和公式求出 $1$ 到 $K$ 的和，用变量 $cnt$ 存，然后枚举 $A_i$，若 $1\le A_i \le K$，则用 $cnt$ 减去 $A_i$，代表这个数出现过了，不能算在答案里。枚举完后 $cnt$ 即为 $1$ 到 $K$ 之间未出现在序列 $A$ 中的整数之和。

注意：如果 $A$ 序列中有重复出现的数，要把重复出现的那些数设为极大值或 $K+1$，避免统计答案时减多了。

等差数列求和公式：设首项为 $x$，末项为 $y$，项数为 $k$，则这个公差为 $1$的等差数列的和为 $\frac{(x+y)\times k}{2}$。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k, a[200005], b[200005];
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=a[i];//复制数组，避免有多于2个的重复数字
	}
	sort(a+1,a+1+n);//排序，便于统计重复数字
	sort(b+1,b+1+n);
	for(int i=1;i<n;i++)
	{
		if(a[i+1]==a[i])//拿原数组判断
		{
			b[i+1]=k+1;
		}
	}
	int tmp=k*(1+k)/2;
	for(int i=1;i<=n;i++)
	{
		if(b[i]<=k)
		{
			tmp-=b[i];
		}
	}
	cout<<tmp;
	return 0;
}

```

---

## 作者：_QyGyQ_ (赞：1)

我们可以在一开始就算出 $1,2,3,\dots,k$ 的和，随后遍历数组，把小于等于 $k$ 的数减掉就行了。但是要注意，数组需要去重。否则可能会重复减掉同一个数。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
int a[N];
set<int>s;
signed main(){
	int n,k;
	cin>>n>>k;
	int ans=(1+k)*k/2;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s.insert(a[i]);
	}
	for(auto i:s){
		if(i<=k){
			ans-=i;
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：kczw (赞：0)

# 题意
给定 $N,K$ 和长 $N$ 的序列 $A$。

求出 $[1,K]$ 中未在 $A$ 出现的数之和
# 思路
先求出 $[1,K]$ 内数的和 $sum$，然后遍历 $A$，并用 set 记录每次遍历的元素是否出现过。每次遇到在 $[1,K]$ 中且是新元素的就在 $sum$ 中减去这个元素的计数。

最后输出 $sum$ 即可。
# 代码
```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N=400;

int t,n,m,k,ans;

set<int> s;

main(){
    
    scanf("%lld%lld",&n,&k);

    ans=(k+1)*k/2ll;

    for(int i=1,a;i<=n;i++){

        scanf("%lld",&a);

        if(a<=k&&!s.count(a)){
            s.insert(a);
            ans-=a;
        }
    }
    printf("%lld",ans);
}
```

---

## 作者：Programming_Konjac (赞：0)

# 赛时思路
用一个映射数组 $m$ 存储大于等于 $1$ 并且小于等于 $k$ 的数是否存储过，然后定义 $sum$ 为 $1$ 到 $k$ 的和，再循环遍历，如果 $1\le a_i \le k(1\le i \le n)$，那么 $m_{a_i}$ 就加 $1$，如果加完之后 $m_{a_i}=1$，那么 $sum$ 要减去 $a_i$，最后输出 $sum$ 即可。
# 赛时代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	ll n,k;
	cin>>n>>k;
	unsigned ll sum=k*(k+1)/2;
	int a[200005];
	map<ll,int> m;
	for(int i=1; i<=n; i++){
		cin>>a[i];
		if(a[i]>=1&&a[i]<=k){
			m[a[i]]++;
			if(m[a[i]]==1) sum-=a[i];
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：fuxiheng (赞：0)

### 题意
给你一个序列，求在序列里 $1$ 到 $k$ 之间没出现过的数的和。
### 分析
显然不能枚举值域，所以我们用一个桶，枚举每一个 $A_i$ 的时候，如果它在 $1$ 到 $k$ 之间且没有在桶里出现过，就用答案减去它，并把它放进桶里。答案初始化为 $1$ 到 $k$ 的和。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 200005;
	map<int, int> t;
	int main(){
		int n, k;
		scanf("%d%d", &n, &k);
		long long ans = 1ll * (k + 1) * k / 2;
		for(int i = 1, a;i <= n;i++){
			scanf("%d", &a);
			if(!t[a] && a <= k) ans -= a;
			t[a] = 1;
		}
		printf("%lld", ans);
		return 0;
	}
} 
signed main(){
	return Luo_ty::main();
}
```

---

## 作者：smart_kai (赞：0)

### C - Σ 题解

#### 思路

---

用**等差数列**求出 $1$ 到 $K$ 的和，然后每加进来一个数字，就减去这个数字。

**注意**：

- 对于重复出现的数字，可以用一个 `set` 维护。
  
- 对于每一个数字，如果这个数小于 $1$ 或大于 $K$，就应该直接跳过这个数字。
  

#### 代码

---
核心代码如下。
```cpp
#define ll long long

ll n,k,sum,x;
set<ll> a;

void solve()
{

    cin >> n >> k;
    sum = (1+k)*k/2;
    for (int i=1; i<=n; i++)
    {
        cin >> x;

        if (a.find(x)==a.end() && 1<=x && x <= k) sum -= x;
        a.emplace(x);
    }
    cout << sum << "\n";
}
```

---

## 作者：Ivan422 (赞：0)

思路分析：直接枚举 $1$ 到 $k$ 肯定不行的，但是我们可以反其道而行之，统计在 $1$ 到 $k$ 范围内的 $a_i$，注意每个数只统计一次，最后再用这个和与 $1$ 到 $k$ 的和相减，减出没有的数的和即可。

```cpp
//2022tysc0819
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=2e5+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,k,a[N],cnt,su;
map<int,bool>mp;
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!mp[a[i]]&&a[i]<=k)su+=a[i]; // 统计和
        mp[a[i]]=1; // 标记数字
    }
    cout<<(1+k)*k/2-su; // 1 到 k 的和减去包含的和
    return 0;
}
//note:
```

---

## 作者：yegengghost (赞：0)

求出 $1$ 到 $k$ 所有数的和，再倒着遍历排序和去重后的数组，把数组中不大于 $k$ 的数字给减掉。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,k;
int a[N];
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);
	int sum=k*(k+1)/2;//求和 
	int num=unique(a+1,a+1+n)-a-1;//去重（必要） 
	for(int i=num;i>=1;i--)
		if(a[i]<=k)
			sum-=a[i];
	printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：int_stl (赞：0)

这道题很简单。

我们先求出这个：

$$
\sum_{i=1}^K i
$$


也就是 $\frac{1}{2}K(K+1)$，$1$ 加到 $K$ 的和。

在输入 $A_i$ 的时候，我们判断 $A_i$ 是否小于等于 $K$ 且 $A_i$ 没有出现过，如果满足，那么将结果减去 $A_i$。  

这样我们就计算出了结果，时间复杂度 $O(N)$。

代码：
```cpp
#include <iostream>
#include <map>
#define int long long
using namespace std;
map <int, bool> vis;
signed main() {
	int n, k;
	cin >> n >> k;
	/*__*/int/*128*/ as = (1 + k) * k / 2;
	int ans = as;
	for (int i = 1; i <= n; i++) {
		int t;
		cin >> t;
		if (t <= k && !vis[t]) vis[t] = 1, ans -= t;
	}
	cout << ans;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc346_c)

## 思路

考虑去重。

我们定义小于等于 $K$ 的所有自然数之和 $\sum_{i=1}^K i$ 为 $C$。 

读入数据后排序，**去重后**用 $C$ 减去所有小于等于 $K$ 的数后的结果即为答案。

去重时可以用 ``unique()`` 函数。

- 最大可能值为 $2\times 10^{18}$ 级别，记得开 long long。

## 核心代码

```cpp
const int N=2e5+10;
ll n,k,a[N],C;
signed main(){
	cin>>n>>k;
	C=k*(k+1)/2;
	for(int i=1;i<=n;++i)cin>>a[i];
	sort(a+1,a+1+n);
	n=unique(a+1,a+1+n)-a-1;//去重并记录新的数组长度。
	for(int i=1;i<=n;++i){
		if(a[i]>k)break;//大于 k，说明之后不会符合条件，跳出。
		C-=a[i];
	}
	cout<<C;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/152409433)

---

## 作者：2023lpx (赞：0)

# AT_abc346_c [ABC346C] Σ 题解

## 题目大意

给你 $N$ 个数的集合 $S$，让你求出 $1$ 到 $K$ 之间不在 $S$ 中的数的和。

## 思路

看数据范围，很明显，要 $O(N)$ 求出来。

我们总不能一个一个试吧。

众所周知，$1+2+3+\cdots+n=\frac{n(n+1)}{2}$

然后我们运用整体减空白思想，减去**去重后的** $S$ 集合里的**不大于** $K$ 的数即可。

## code

```cpp
#include<cstdio>
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int const maxn=200000;
int a[maxn+1];
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+1+n);//方便去重
	long long ans=k*(k+1)/2;
	int lst=0;
	for(int i=1;i<=n;i++){
		if(a[i]<=k){
			if(a[i]!=lst){
				ans-=a[i];
			}
		}
		lst=a[i];
	}
	printf("%lld",ans);
	return 0;
}
```

---

