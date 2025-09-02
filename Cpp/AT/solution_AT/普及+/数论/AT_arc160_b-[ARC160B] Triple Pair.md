# [ARC160B] Triple Pair

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc160/tasks/arc160_b

正整数 $ N $ が与えられます。

以下の条件を満たす $ 3 $ 個の正整数の組 $ (x,y,z) $ の個数を $ 998244353 $ で割ったあまりを求めてください。

- $ xy,yz,zx $ が全て $ N $ 以下である。
 
$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 100 $
- $ 1\ \le\ N\ \le\ 10^9 $
 
### Sample Explanation 1

$ 1 $ 個目のテストケースでは、$ N=1 $ です。条件を満たす $ (x,y,z) $ は $ (1,1,1) $ の $ 1 $ 個です。 $ 2 $ 個目のテストケースでは、$ N=2 $ です。条件を満たす $ (x,y,z) $ は、$ (1,1,1),(2,1,1),(1,2,1),(1,1,2) $ の $ 4 $ 個です。

## 样例 #1

### 输入

```
4
1
2
5
998244353```

### 输出

```
1
4
17
727512986```

# 题解

## 作者：c20231020 (赞：6)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/AT_arc160_b)

[atcoder](https://atcoder.jp/contests/arc160/tasks/arc160_b)

### 题目大意

给出一个正整数 $n$。

求出满足以下条件的正整数三元组 $(x,y,z)$ 的数量，取模 $998244353$：

- $xy,yz,zx$ 都小于或等于 $n$。

多组数据。$1 \le T \le 100,1 \le n \le 10^9$。

### 思路

令 $m=\lfloor \sqrt{n} \rfloor$。

对 $x,y,z$ 的值分类讨论：

1. $\max(x,y,z) \le m$。

   此时 $x,y,z$ 两两乘积一定都小于 $n$。
   
   每个值都可以取 $[1,m]$ 中的整数，方案数为 $m^3$。
   
2. $\max(x,y,z) > m$。
   
   若 $\max(x,y,z)=x$，那么因为 $xy \le n,xz \le n$，所以 $y$ 和 $z$ 一定都小于 $m$。这就同时满足了 $yz \le n$。
   
   考虑枚举 $x$。那么 $y,z \in[1,\lfloor \frac{n}{x} \rfloor ]$。所以 $y,z$ 的取值方案数为 $\lfloor \frac{n}{x} \rfloor ^2$。不考虑 $x$ 在三元组中的位置，则 $x$ 三个位置都可以放，剩下两个位置就有上述方案，所以总方案数就是 $3 \cdot \lfloor \frac{n}{x} \rfloor ^2$。
   
   显然这个式子[数论分块](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)一下就做完了，注意 $x \in (\sqrt{n},n]$。
   
时间复杂度 $O(T\sqrt{n})$。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define ll long long
ll n;
void solve(){
	cin>>n;
	ll m=sqrt(n),ans=0;
	ans+=m*m*m%mod;//分类1
	for(ll l=m+1,r;l<=n;l=r+1){//分类2，枚举x
		r=n/(n/l);
		ll lim=n/l;
		ans+=lim*lim*3%mod*(r-l+1)%mod;
		ans%=mod;
	}
	cout<<ans<<'\n';
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：iPhoneSX (赞：4)

## 题解
提供一个五分钟搞定的巨简单做法，思路和代码都非常简洁。

要找三元组个数，一定不可能枚举每一个元素，考虑只枚举最中间的元素。设 $x \ge y \ge z$，我们只枚举 $y$。

有一个大于等于 $y$ 的数和它相乘小于等于 $n$，说明 $y \le \sqrt{n}$。对于确定的 $y$，$x$ 的取值范围是 $[y,\lfloor\frac{n}{y}\rfloor]$，设共有 $l$ 个元素。$z$ 的取值范围是 $[1,y]$，设共有 $r$ 个元素。因为较大的两个数乘积都小于等于 $n$，最小的数就无所谓了。

下面考虑排列，当三个数互不相同时，有 $6$ 种排列，当三个数中有两个相同时，有 $3$ 种排列，三个数都相同只有 $1$ 种排列，所以答案累加 $(l-1)\times (r-1) \times 6+(l-1) \times 3+(r-1) \times 3+1$ 即可。

代码如下：
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<iomanip>
#include<iostream>
#define ll long long
#define mod 998244353
using namespace std;
ll t,n,m,ans;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		m=sqrt(n);
		for(int i=1;i<=m;i++){
			ll l=n/i-i+1;
			ll r=i;
			ans=(ans+(l-1)*(r-1)*6%mod+(l-1)*3%mod+(r-1)*3%mod+1)%mod;
		}
		cout<<ans;
		putchar('\n');
	}
	return 0;
}
``````

---

## 作者：Pengzt (赞：3)

[ARC160B](https://www.luogu.com.cn/problem/AT_arc160_b)

不妨令 $x\ge y\ge z$。

发现当 $x$ 很大时，$y$ 和 $z$ 会很小。当 $x > \sqrt{n}$ 时，因为 $y, z\le \lfloor\dfrac{n}{x}\rfloor$，则 $yz$ 显然小于 $n$。

考虑以值域分界，令 $B = \lfloor \sqrt{n}\rfloor$。

当 $x\le B$ 时，贡献显然为 $\sum\limits_{i = 1}^{T} i^2$。

当 $x > B$ 时，对于每个 $x$，贡献为 $\lfloor \dfrac{n}{x}\rfloor ^2$（此时 $yz$ 恒小于 $n$）。

则当 $x > B$ 时，总贡献为 $\sum\limits_{i = B + 1}^{n} \lfloor\dfrac{n}{i}\rfloor$，使用数论分块可以做到单次询问 $\mathcal{O}(\sqrt{n})$。

时间复杂度：$\mathcal{O}(T\sqrt{n})$

[评测记录](https://atcoder.jp/contests/arc160/submissions/41691738)

---

## 作者：zhangzihang (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/AT_arc160_b)
## 题意分析
- 给定一个 $n$ 求满足使 $xy,yz,zx\le n$ 的三元组 $(x,y,z)$ 的个数，答案对 $998244353$ 取模。
- 多组测试数据。

------------
## 算法分析
不妨假设 $x\le y\le z$，因为 $yz\le n$ 且 $y\le z$ 不难得到 $1\le y\le \sqrt n $。

然后 $1\le x\le y$ 且 $y\le z\le \left\lfloor\dfrac{n}{y}\right\rfloor$。

因此我们可以枚举 $y$ 的大小，对于每一个 $y$ 我们可以得到 $y\times (\left\lfloor\dfrac{n}{y}\right\rfloor-y+1)$ 个有序三元组 $(x,y,z)$。

但是题目要求的三元数组是无序的。我们要对 $(x,y,z)$ 中重复元素个数进行分类讨论。

- 若 $x,y,z$ 均相等那么只有一个无序数组 $(x,y,z)$。
- 若 $x,y,z$ 中有两个元素相等则无序数组 $(x,y,z)$ 有三个。
- 若 $x,y,z$ 互不相同则无序数组 $(x,y,z)$ 有六个。

所以最终的答案为 
$\sum\limits_{y=1}^{\left\lfloor\sqrt n\right\rfloor} (1+3\times (\left\lfloor\dfrac{n}{y}\right\rfloor-1)+6\times(y-1)(\left\lfloor\dfrac{n}{y}\right\rfloor-y)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int MOD=998244353;
using namespace std;
main(){
	int T;cin>>T;
	while(T--){
		int n,cnt=0;cin>>n;
		for(int y=1;y*y<=n;y++){
			cnt+=1;
			cnt+=3*(n/y-y);
			cnt%=MOD;
			cnt+=3*(y-1);
			cnt%=MOD;
			cnt+=6*(y-1)*(n/y-y);
			cnt%=MOD;
		}
		cout<<cnt<<"\n";
	}
	return 0;
}
```

---

## 作者：abensyl (赞：2)

## 思路

古话说得好：“由俭入奢易，由奢入俭难”！在写这道题时，看到数据范围，很容易看出这道题目需要一个 $O(T\times \sqrt N)$ 或者 $O(T\times \log N)$ 的做法，但是，在无法很快想到简便的做法的时候，我们可以先考虑打一个 $O(N)$ 的朴素做法，再慢慢优化。

我们枚举每个三元组 $\{x,y,z\}$ 的最大值 $i$，然后就可以得到一个次大值的取值上限 $pt$，易得 $pt=\min(i,\lfloor{N\over i}\rfloor)$，在这里，很容易错写为 $pt=\lfloor{N\over i}\rfloor$，但是要记住，次大值是肯定不能超过最大值的。

这样的话就会出现一个排列组合，非常简单，大家可以自己思考一下：

- 一个三元组 $\{a,a,a\}$（相同字母代表相同元素）有多少种不同的排列方式？  
> 很显然，答案为 $1$ 种，就是 $(a,a,a)$。  
- 一个三元组 $\{a,b,b\}$ 或 $\{a,a,b\}$（同上，$a\neq b$）有多少种不同的排列方式？  
> 枚举可得答案为 $3$ 种，分别是 $(a,b,b)$、$(b,a,b)$、$(b,b,a)$。  
- 一个三元组 $\{a,b,c\}$（$a\neq b\neq c$）有多少种不同的排列方式？  
> 经排列组合，答案为 $A^3_3=6$ 种。

那么我们只要枚举这三种三元组的个数即可。

当 $pt=i$ 时，那么可能会出现四种情况：

1. 三元组 $\{i,i,i\}$，只有 $1$ 个。  
2. 三元组 $\{i,j,j\}$（$i>j$），一共 $(i-1)\times 3$ 种。  
3. 三元组 $\{i,i,j\}$（$i>j$），一共 $(i-1)\times 3$ 种。  
4. 三元组 $\{i,j,k\}$（$i>k,j$，$j\neq k$），一共 ${(i-1)\times(i-2)\over 2}\times 6$ 种，化简可得 ${(i-1)\times(i-2)}\times 3$。  

当 $pt<i$ 时，会出现两种情况：

1. 三元组 $\{i,j,j\}$（$j\leq pt$），一共 $pt\times 3$ 种。  
2. 三元组 $\{i,j,k\}$（$k,j\leq pt$，$j\neq k$），一共 ${pt\times(pt-1)\over 2}\times 6$ 种，化简可得 ${pt\times(pt-1)}\times 3$。

于是我们可以做出一个 $O(T\times N)$ 的做法（不能通过所有测试点）：

对上述代码进行优化，我们很容易想到，当 $i$ 较大时，对于很多的 $i$，$pt=\lfloor{N\over i}\rfloor$ 的值是相同的，那么，我们将 $pt$ 相同的值进行合并计算即可。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int mod = 998244353;

void solve() {
	ll N;
	cin>>N;
	ll pt=1;
	ll res=0;
	int ed=0;
	for(ll i=N;i>=1;) {
		pt=N/i;
		//cout<<i<<' '<<pt<<' ';
		if(pt>=i) {
			//cout<<(i-1)*(i-2)*6+(i-1)*3+(i-1)*3+1<<'\n';
			res+=(i-1)*(i-2)*3+(i-1)*6+1;
			res%=mod;
			--i;
		} else {
			//cout<<N/pt<<' '<<N/(pt+1)<<' ';
			ll zp=(pt*(pt-1)*3+pt*3)*(N/pt-N/(pt+1));
			//cout<<zp<<'\n';
			i=N/(pt+1);
			res+=zp;
			res%=mod;
		}
	} cout<<res<<'\n';
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	cin>>t;
	while (t--) solve();
	return 0;
}
```

时间复杂度 $O(T\times \sqrt n)$，可过。

---

## 作者：Lawrenceling (赞：1)

## 前言 
前几天刚学了数论分块，来一题试试水，~~结果发现好难~~。

由于作者也是初学数论分块，于是本题解可能会对萌新比较友好。

## 题意
给定 $t$ 个询问，每个询问给出 $n$，求满足 $xy,xz,yz\le n$ 的正整数有序三元组 $(x,y,z)$ 的个数。

## 前置知识
最基本的数论分块，实际上是就是求： 
$$\sum^{n}_{i=1}\lfloor \frac{n}{i}\rfloor $$
在之后的的数论分块中会有更加高深的操作，不过我们先不需要。来看看这个式子怎么求，以 $6$ 为例子：

|$i=$|$1$|$2$|$3$|$4$|$5$|$6$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$\lfloor \frac{n}{i} \rfloor=$|$6$|$3$|$2$|$1$|$1$|$1$|

我们发现，$O(n)$ 去算过于冗余了，因为 $\lfloor \frac{n}{i} \rfloor$ 在后期会有大批重复，浪费时间。如果可以直接跳到下一个跟此数不一样的数就好了。

于是就可以玩一下式子了，设 $\lfloor \frac{n}{i} \rfloor i\le n$，数 $r$ 要满足它且使其最大，移一下项就可以得到 $r=\lfloor \frac{n}{\lfloor \frac{n}{r} \rfloor}\rfloor$。下一个跟此数不一样的数就是 $r+1$。此数的个数就是 $(r-i+1)\cdot \lfloor \frac{n}{i} \rfloor $ 了。

## 解法
考虑分类讨论，令 $rt=\sqrt{n}$。

如果 $max(x,y,z)\le rt$，显然答案贡献了 $rt^3$。

那如果 $max(x,y,z)> rt$ 呢？
作者止步于此，看完题解恍然大悟了：不妨设 $x>rt$，由约束可得 $y,z\le rt$。

令 $w=\lfloor \frac{n}{x} \rfloor$，这个时候可以枚举 $x$。

**容易发现 $y,z$ 都在 $[1,w]$ 范围内，所以对于每一个 $x \in (rt,n]$，取值方案为 $w^2$。**

由于是有序的三元组，所以最后答案要变成 $3w^2$。

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD=998244353;
signed main()
{
	int t,n,rt;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		rt=sqrt(n);
		long long ans=1ll*rt*rt*rt%MOD;
		for(int l=rt+1,r;l<=n;l=r+1)
		{
			r=n/(n/l);
			long long sum=3ll*(n/l)*(n/l)%MOD;
			ans=(ans+sum*(r-l+1)%MOD)%MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：0)

我 naive 了，有更不吃操作的做法，在后面补充了。

简单数论分块加推式子，话说应该不止绿题吧？

记 $f_j$ 为有多少个 $i$ 使得 $j\in(i,\lfloor \frac ni\rfloor]$，发现 $i>\sqrt n$ 直接不会产生贡献，所以只有根号种取值。

可以简单地求出。

$$
\begin{aligned}
Ans&=\sum_{i=1}^n\sum_{j=1}^{\lfloor \frac ni\rfloor}\min(\lfloor \frac ni\rfloor,\lfloor \frac nj\rfloor)\\
&=\sum_{i=1}^ni\lfloor \frac ni\rfloor+\sum_{j=i+1}^{\lfloor \frac ni\rfloor}\lfloor \frac nj\rfloor\\
&=\sum_{i=1}^n i\lfloor \frac ni\rfloor+\sum_{j=1}^{n}f_{j}\lfloor \frac nj\rfloor
\end{aligned}
$$

前后都可以数论分块，$O(T\sqrt n)$。

感觉我的做法好复杂。可以直接假定 $x\le y\le z$，然后枚举 $y$，显然 $y\le \sqrt n$，如果 $z\le \lfloor \frac ny\rfloor$，那么三元组一定合法。

分讨一下相对大小就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

const int mod=998244353;
int T,n,ans;

inline void add(int x){ans=(ans+x)%mod;}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>T;
	while(T--){
		cin>>n;ans=0;
		for(int i=1;i<=n;++i){
			int x=i,z=(n/i)-i+1;if(z<=0) break;
			add((x-1)*(z-1)*6%mod+(x-1)*3+(z-1)*3+1);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

讨论 $x$ 与 $\sqrt n$ 的大小关系，令 $k=\sqrt n$。

+ 若 $\max(x,y,z) \le \sqrt n$，那么对于任意 $x,y,z$ 必定成立，方案数为 $k^3$。
+ 否则，钦定 $x$ 为最大值，那么 $y,z \le k$，然后做整除分块，由于 $x,y,z$ 地位相等，所以答案需要 $\times 3$。

时间 $O(\sqrt n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb push_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vec vector <int>
#define fv inline void
#define fn inline static
using u16 = unsigned short; using u32 = unsigned; using u64 = unsigned ll; using u128 = __uint128_t;
using i16 = short; using i32 = int; using i64 = ll; using i128 = __int128_t;
using namespace std;
const i32 mod = 998244353;
i32 n;
fv sol() {
  cin >> n;
  i32 m = sqrt(n), ans = 0;
  ans = 1ll * m * m % mod * m % mod;
  for (i32 l = m + 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    i32 k = n / l;
    ans = (ans + 1ll * k * k % mod * 3 % mod * (r - l + 1) % mod) % mod;
  }
  cout << ans << "\n";
}
int main() {
  IOS;
  i32 T = 1;
  cin >> T;
  while (T--) sol();
}
```

---

## 作者：queenbee (赞：0)

# AT_arc160_b [ARC160B] Triple Pair 题解
## 思路
[题目传送门](https://www.luogu.com.cn/problem/AT_arc160_b)，因为 $x$、$y$、$z$ 彼此无差别，所以在不考虑相同的情况下，求出一组三元组 $(x,y,z)$ ，交换其中元素位置会得到六组符合条件的三元组。元素之间互相的约束条件为 $x \times y \le n$ 且 $z \le \min(x,y)$ 。考虑当最大元素确定时，另外两个元素取值相同，所以对最大元素进行讨论。

令 $x$ 为三元组中最大元素，满足 $z \le y \le x$。

当 $x \le \lfloor \sqrt n \rfloor$ 时，此时 $x$、$y$、$z$ 取值均为 $[1,\lfloor \sqrt n \rfloor]$，此时三元组数量为 ${\lfloor \sqrt n \rfloor}^3$。

当 $x > \lfloor \sqrt n \rfloor$ 时，$x$ 取值为 $(\lfloor \sqrt n \rfloor,t]$ ，$y$、$z$ 取值为 $[1 ,\lfloor \frac n t \rfloor]$，满足 $t \in (\lfloor \sqrt n \rfloor,n]$。此时三元组的数量为$3 \times x_{max} \times {y_{max}}^2$。当有 $x_1<x_2$ 时，$x_1$ 的部分三元组数会被添加两次，所以考虑从小到大遍历 $y_{max}$，每次三元组数量增加 $3 \times(x_{max}-\lfloor \frac n {y_{max}+1} \rfloor]) \times {y_{max}}^2$ 可避免重复增加。

## 程序
```cpp
#include<bits/stdc++.h>   //我爱万能头
using namespace std;
#define int long long
const int Mod=998244353;
int t;
int n;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		int res=0,sq=sqrt(n);
		res+=(sq*sq*sq)%Mod;	//x<=floor(sqrt(n))的三元组数 
		res%=Mod;
		for(int i=1;i<=sq;i++){	//x>floor(sqrt(n))的三元组数 
			int y=i,x=n/i;	
			if(x==y){
				continue;
			}
			res+=3*y*y*(x-n/(i+1));		
			res%=Mod;
		}
		cout<<res%Mod<<endl;
	}
	return 0;	//完结撒花 
}
```

---

## 作者：cosf (赞：0)

我们令 $x \le y \le z$，则容易发现，$y^2 \le yz \le N \implies y \le \sqrt{N}$。

于是可以枚举 $y$，则 $x \in [1, y], z \in [y, \frac{N}{y}]$，都可以很容易地算出来。

注意判别什么时候有数相等，以及对应轮换的系数是 $6$ 还是 $3$ 还是 $1$。

因此复杂度为 $O(T\sqrt{N})$

```cpp
#include <iostream>
#include "atcoder/modint"
using namespace std;

using ll = long long;
using mint = atcoder::modint998244353;

void solve()
{
    ll n;
    cin >> n;
    mint res = 0;
    for (ll y = 1; y * y <= n; y++)
    {
        res++; // x = y = z
        res += mint(3) * (y - 1); // y = z
        res += mint(3) * (n / y - y); // x = y
        res += mint(6) * (y - 1) * (n / y - y);
    }
    cout << res.val() << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

```

---

## 作者：xiazha (赞：0)

我们理一下思路：

首先，此题关于平方，很容易想到根号，考虑各种硬搞过不去，于是根号分治。

- 对于 $\max(x,y,z)\le \sqrt n$

由于他们两两之积一定小于 $n$，则对于每个数都可以取 $1$ 到 $\sqrt n$ 之间任意值，对答案贡献为 $(\sqrt n)^3$。

- 对于 $\max(x,y,z) > \sqrt n$

设 $x\le y\le z$，则 $x$ 与 $y$ 必然小于 $\lfloor\frac{n}{z}\rfloor$。于是 $xy\le n$。所以现在对答案贡献为 $\sum_{z=m+1}^{n} 3\times \lfloor\frac{n}{z}\rfloor^2$。为了优化时间复杂度，整除分块即可。



------------


这时读者也许会有这个疑问：

如果 $x$，$y$，$z$ 三数相等，为什么不去重呢？

这里有解答：若有数相等，则一定会是 $\max(x,y,z)\le \sqrt n$，所以计算时并没有重复的三元组。

代码简单，但还是放一下吧。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
int t,n,ans,m;
signed main()
{
	cin>>t;
	while(t--)
	{
		scanf("%lld",&n);
		int m=sqrt(n);
		ans=m*m%mod*m%mod;
		int l=m+1,r=0;
		while(l<=n)
		{
			r=n/(n/l);
			ans=(ans+(r-l+1)*(n/l)%mod*(n/l)%mod*3ll%mod)%mod;
			l=r+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

