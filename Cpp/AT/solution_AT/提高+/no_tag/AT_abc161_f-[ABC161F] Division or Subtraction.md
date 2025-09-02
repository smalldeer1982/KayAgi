# [ABC161F] Division or Subtraction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc161/tasks/abc161_f

正整数 $ N $ が与えられます。

$ 2 $ 以上 $ N $ 以下の整数 $ K $ を決めて、$ N $ が $ K $ 未満になるまで次の操作を繰り返し行います。

- 操作：$ N $ が $ K $ で割り切れるとき、$ N $ を $ N/K $ に置き換える。そうでないとき、$ N $ を $ N-K $ に置き換える。

最終的に $ N $ が $ 1 $ になるような $ K $ の決め方は何通りありますか？

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^{12} $
- $ N $ は整数

### Sample Explanation 1

最終的に $ N $ が $ 1 $ になるような $ K $ は $ 2,5,6 $ の $ 3 $ 通りです。 それぞれのとき、$ N $ は次のように変化します。 - $ K=2 $ のとき：$ 6\ \to\ 3\ \to\ 1 $ - $ K=5 $ のとき：$ 6\ \to\ 1 $ - $ K=6 $ のとき：$ 6\ \to\ 1 $

## 样例 #1

### 输入

```
6```

### 输出

```
3```

## 样例 #2

### 输入

```
3141```

### 输出

```
13```

## 样例 #3

### 输入

```
314159265358```

### 输出

```
9```

# 题解

## 作者：喵仔牛奶 (赞：9)

首先找一下性质，发现对于所有 $k$，$n$ 必定可以写成 $k^x\times(y\times k+1)$ 的形式。因为显而易见的，操作是先做 $x$ 次除，再做 $y$ 次减。因为当除法做完时，$\gcd(n,k)=1$，无论 $n$ 再怎么减，一定不会 $\gcd(n,k)>1$。 

所以可以枚举一下 $k$，连除除去 $k^x$，判断 $\dfrac{n}{k^x}\mod k\equiv1$。但是这样是 $O(n)$ 的，显然跑不过 $10^{12}$。

然后发现，对于 $k>\sqrt n$，有 $x=0$ （这不废话吗） 。这样 $k>\sqrt n$ 的部分式子不用连除就可以写成 $n\mod k\equiv1$，转换成 $k|(n-1)$ ，$\sqrt n$ 找一下因数即可。但是注意 $y=0$，即 $n$ ，它可以写成 $k^1\times(0\times k+1)$ 的形式，最后答案 $+1$ 就可以了。

对于剩下 $\sqrt n$ 的 $x>0$，前面的暴力跑一下即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, ans; // 十年OI一场空，不开long long见祖宗！
int main() {
	cin >> n;
	for (long long i = 1; i * i < n; i ++)
		if ((n - 1) % i == 0) ans += (i * i != n - 1) + (i != 1);
	for (long long i = 2; i * i <= n; i ++) {
		long long m = n;
		while (m % i == 0) m /= i;
		if (m != n && m % i == 1) ans ++;
	}
	cout << ans + 1 << '\n';
	return 0;
}

```


---

## 作者：SpeedStar (赞：3)

## 算法分析
注意到，如果从未执行除法运算，则$N\ mod\ K$通过该运算保持恒定。因此，当且仅当$N\ mod\ K = 1$时，它才最终变为$1$。

而对于这样的$K$是$N -1$的除了$1$以外的所有约数，并且统计它们的数量可以在$O(\sqrt N\ )$时间内完成。

如果除法运算执行不止一次，则该$K$是$N$的约数，执行该运算直到被K整除并检查$N\ mod\ K = 1$是否可以$O(logN)$时间内检查 对于每个除数。

此题的瓶颈部分是找到$N$和$N-1$的约数，总的时间复杂度为$O(\sqrt N)$。


## C++代码
```cpp
#include <iostream>
#define int long long

using namespace std;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	int res = 1;
	for (int i = 1; i * i <= (n - 1); i++) {
		int m = n - 1;
		if (m % i == 0) {
			if (i != 1) res++;
			if (i * i != m) res++;
		}
	}
	for (int i = 2; i * i <= n; i++) {
		int m = n;
		while (m % i == 0) m /= i;
		if (m != n && m % i == 1) res++;
	}
	 
	cout << res << '\n';
	
	return 0;
}
```


---

## 作者：Rannio (赞：2)

### 题意
ABC 的题面还是太简洁了。

### 思路
分情况讨论一下：
- 只使用减法操作时，$n-1$ 及它的因数显然是可以的。
- 对于任意 $n$ 的大于 $1$ 的因数 $k$，$n$ 一定能表示为 $k^x+y$，此时我们判断 $y \mod k$ 是否等于 $1$ 即可。
- 对于其他的 $k$，都不满足 $n \mod k =1$ 或 $n=k^x+y$，显然此时无法使 $n$ 变为 $1$。

然后枚举 $n$ 的因数和 $n-1$ 的因数即可，时间复杂度 $O(\sqrt n)$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
signed main(){
	scanf("%lld",&n);
	if(n==2){
		printf("1");
		return 0;
	}
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			int x=n;
			while(x>1){
				if(x%i==0) x/=i;
				else{
					if(x>i) x=x%i;
					else break;
				}
			}
			if(x==1) m++;
		}
	}
	n--;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			if(i*i==n) m++;
			else m+=2;
		}
	}
	printf("%lld",m+2);
	return 0;
}
```

---

## 作者：大眼仔Happy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc161_f)

随便 vp 的一场，DE 两个黄题都不会但是 F 给我秒了。

首先看题目发现是 $N\le 10^{12}$，我们很容易就想到了正解应该是一个根号做法。

考虑从这个突破口出发，我们结合除法的那个操作，显然可以将 $K$ 分成两类：

- $K\le \sqrt{N}$，这个部分暴力一下就行了。具体一点，我们发现若 $K\nmid N$，则 $K\nmid N-K$，所以说我们先把所有的因子 $K$ 全部除完，剩下的就肯定不需要除法了。于是直接一个取模就完事了。时间复杂度为 $O(\sqrt{N}\log N)$。

- $K> \sqrt{N}$，可以发现这里除了 $K = N$ 的时候能用除法其他的都不行，因为其他的都会剩下的 $\frac{N}{K}<K$。所以说剩下的就只能减法了，即要满足 $N\equiv 1\pmod K$，也就是求所有的 $N-1$ 的因数。时间复杂度为 $O(\sqrt{N})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
ll N,k,d,ans;
int solve(ll x)
{
	ll n=N;
	while(n%x==0)n/=x;
	if(n%x==1)return 1;
	else return 0;
}
int main(){
	N=read();
	for(k=2;k*k<=N;k++)ans+=solve(k);
	for(d=1;d*d<=N-1;d++)
	{
		if((N-1)%d)continue;
		if((N-1)/d>=k)ans++;
	}
	printf("%lld",ans+1);
	return 0;
}
```

---

## 作者：Walrus (赞：2)

# ABC161F

一道简单的数学题，其实想想也能做，我觉得蓝可能都有点过了。



## 题意

给定一个正整数 $n$，问有多少个 $k(2\leq k \leq n)$，满足进行一些操作后，可以使 $n$ 变为 $1$。操作的定义如下：

- 若 $k \mid n$，则将 $n$ 的值除以 $k$。
- 否则将 $n$ 的值减去 $k$。



## 分析

观察到 $2\leq n \leq 10^{12}$，肯定不能直接枚举，考虑观察性质。

我们将 $k$ 分为两类，一类是 $n$ 的因数，一类不是 $n$ 的因数。为什么可以这么干呢？我们发现，如果 $k$ 不是 $n$ 的因数，则肯定会一直进行减法操作，通过简单同余性质可以证明。所以我们大概可以发现一个很重要的东西：

- 当 $k$ 不是 $n$ 的因数时，只有当 $k$ 是 $n-1$ 的因数时，这个 $k$ 才符合要求。为什么呢？因为我们既然会一直进行减法操作，如果要符合要求，则我们需要减掉 $n-1$。所以此结论显然得证。

这里给出代码：

```cpp
void init() {
	int x = n - 1;
	for(int i = 2;i <= sqrt(x);i++) {
		if(!(x % i))
			ans += 2;
	}
	if((int)sqrt(x) * (int)sqrt(x) == x)
		--ans;
	++ans;
}
```



当然，如果 $k=n$ 时，显然满足要求，这个值随便在哪加上都无所谓。



继续考虑另一类，发现一定会先进行除法操作，到某一个值时，会开始进行减法操作。大家手动模拟一下便可以发现，结论同样好理解，当然，也只有想到这里，才能大概解出这道题。所以，如果 $k$ 是 $n$ 的因数，直接模拟操作，当开始进行减法操作时，直接判断这个数可不可以通过接下来的减法操作得到 $1$。时间复杂度大概为 $\log$ 级别。

这里给出判断方法：

```cpp
for(auto x : T) {
	int y = n;
	while(!(y % x))
		y /= x;
	if(!((y - 1) % x))
		++ans;
}
```

这里的 $T$ 存储 $n$ 的所有因数。



最后再总结补充一下。

- 为什么可以分成两类且答案不冲突？因为对于任意正整数 $i$，有 $\gcd(i,i+1)=1$。
- 为什么可以直接进行除法操作？因为除完后是 $O(1)$ 判断的，所以大致复杂度为 $O(\log{N})$。
- 总时间复杂度为 $O(\sqrt{N}+\log{N})$。

代码大概都有了，这里就不放全了。



---

## 作者：Xdl_rp (赞：2)

solution
------------

- 第一种情况 $n = k \times t + 1$

$ \Rightarrow n - 1 = k \times t$

这时只需要求出 $n - 1$ 除 $1$ 外的所有因数即可，因为 $k$ 不能是 $1$，如果 $k$ 为 $1$ 的话，则 $k | n$，与题意不符，时间复杂度是 $O( \sqrt{n})$ 的。

- 第二种情况 $n = k ^ a \times (k \times t + 1)$

$ \Rightarrow \frac{n}{k ^ a} = k \times t + 1$

这时的话我们只需要枚举从 $2$ 到 $\sqrt{n}$ 的数，如果 $n$ 可以整除的话，就除到不能整除为止，在判断与原来的 $n$ 相不相同，如果不相同，且 $n \bmod k = 1$，说明这个 $k$ 是符合条件的，加到总和里。

- 第三种情况 $n = k ^ a$

除了 $a = 1$，也就是说 $k = n$，其他的在条件二中已经考虑过了（当 $\frac{n}{k ^ a} = 1$ 时），这里就不用再考虑了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	int n, ans = 1;//答案一开始就加上k=n时的结果
	scanf("%lld", &n);
	//以下是考虑n=kt + 1时
	for (int i = 1; i * i <= (n - 1); i++) {
		int k = n - 1;//找个替身
		if (k % i == 0) {//如果整除
			if (i * i != k) ans++;//不是完全平方数时
			if (i != 1) ans++;//不是1时
		}
	}
	//以下是考虑条件2
	for (int i = 2; i * i <= n; i++) {
		int k = n;//替身
		while (k % i == 0) k /= i;//一直除，除到除不尽为止
		if (k != n && k % i == 1) ans++;//如果有变化，也就是除掉了一部分，且剩下的摸i余1，这个i一定是符合条件的
	}
	//以下是输出
	printf("%lld\n", ans);//记得打换行！！！
	return 0;
}
```


---

## 作者：_Gabriel_ (赞：1)

### 思路

这题分两种情况讨论。

1. 当 $k|n$ 时，此时会先进行除法，每次除以 $k$ 的次幂，除到不能除时，会进行减法，判断一下开始进行减法时，这个数是否可以通过接下来的减法得到 $1$。

2. 当 $n$ 不是 $k$ 的倍数时，即 $n-kt=1$，所以 $kt=n-1$，可知 $k|(n-1)$，枚举即可。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n, ans = 1, k;

int main() {
    cin >> n;
    k = n - 1;
    for (ll i = 1; i * i <= k; i++) {
        if (k % i == 0) {
            if (i != 1) ans++;
            if (i * i != k) ans++;
        }
    }
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 1) continue;
        ll t = n;
        while (t % i == 0) t /= i;
        if (t % i == 1) ans++;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Leaper_lyc (赞：0)

难度顶多绿吧？

## 分析

一个简单的做法是直接枚举 $k$，然后模拟。这种办法对于较小的 $k$ 可以直接搞，但对于较大的 $k$ 是枚举不来的。

显然，只有当 $n=k^x\times(yk+1)$ 时，$k$ 才满足条件。

对于 $n$ 的约数，直接 $O(\sqrt{n})$ 枚举+模拟即可。

当 $k> \sqrt{n}$ 时，发现 $k^2>n$，即 $\frac{n}{k}<k$，也就是 $n$ 至多除一次 $k$。

这时候可以将 $n$ 表达为 $n=yk+1$，移项就是 $n-1=yk$，即 $n-1\equiv 0\pmod k$，也就是 $n-1$ 的约数。

## $\tt Code$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, t, ans = 1;
signed main() {
	cin >> n;
	for (int i = 1; i * i < n; i++)
		if ((n - 1) % i == 0)
			ans += 1 + (i * i != n - 1);
	for (int i = 2; i * i <= n; i++) {
		t = n;
		while (t % i == 0) t /= i;
		if (t != n && t % i == 1) ans++;
	}
	cout << ans - 1;
}
```

---

## 作者：SpringFullGarden (赞：0)

## 题意

给定正整数 $n$。求有多少个 $k$ 满足：如果 $k | n$，那么 $n \gets \frac{n}{k}$，否则 $n \gets n - k$，操作若干次后得到 $1$。

## 思路

可以发现，需要满足的条件可以表示成 $\frac{n}{k ^ a} - bk = 1$。

先考虑第二种情况，即 $k$ 与 $n$ 互质的时候，那么 $bk = n - 1$，所以 $k | n - 1$。只需要枚举 $n - 1$ 的因子，是 $O(\sqrt{n})$ 的。

再考虑第一种情况，发现 $bk = \frac{n}{k ^ a} - 1$，且 $\frac{n}{k ^ a}$ 与 $k$ 互质，所以 $k | n$，且 $\frac{n}{k ^ a}\equiv 1 \pmod k$。只需要枚举 $n$ 的因子，然后判断是否符合条件，是 $O(\sqrt{n})$ 的。

## 代码

```cpp
signed main() {
	ll n = rd(), ans = 0;
	for(ll i = 1; i * i < n; i++) {
		if((n - 1) % i) continue;
		ans++;
		if(i * i != (n - 1)) ans++;  
	}
	for(ll i = 2; i * i <= n; i++) {
		if(n % i) continue;
		ll tmp = n;
		while(tmp % i == 0) tmp /= i;
		if(tmp % i == 1 && tmp != n) ans++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Suare_Pi (赞：0)

题意：给定一个正整数 $N$，然后你可以选择一个正整数 $K$ 并执行以下两种操作：

1. 如果 $ N \bmod K=0 $ 则可以将当前的 $N$ 替换为 $N÷K$;
  
2. 将 $N$ 替换为 $N-K$;
 
 
询问能将 $N$ 转化为 $1$ 的正整数 $K$ 的数量。

**分析**：分成两部分考虑：一是 $N$ 直接减去 $N−1$，这种情况下的 $K$ 就是 $N−1$ 的所有因子；二是除了情况一以外的所有情况（就是需要考虑操作 $1$ 的情况，情况一我们只考虑了操作 $2$），这些情况下的 $K$ 不难发现必定是 $N$ 的因子，因此我们取出所有 $N$ 的因子模拟即可。

> 这两种情况不存在相同的因子，因为相邻自然数互质。




```
#include <bits/stdc++.h>
using namespace std;
long long n;

int main() {
	cin >> n;
	int ans = 1;
	for (long long i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			long long tmp = n;
			while (tmp % i == 0)
				tmp /= i;
			if ((tmp - 1) % i == 0)
				ans++;
			tmp = n;
			if (i * i == n)
				continue;
			long long x = n / i;
			while (tmp % x == 0)
				tmp /= x;
			if ((tmp - 1) % x == 0)
				ans++;
		}
	}
	if (--n > 1)
		++ans;
	for (long long i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			ans += 2;
			if (i * i == n)
				--ans;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：LJB00131 (赞：0)

[blog](https://www.cnblogs.com/LJB00131/p/12634775.html)内食用更佳

考虑答案可能是哪些数。第一是n的约数，第二是(n - 1)的约数。全部枚举一下判断即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, ans = 0;

map <ll, bool> used;

void check(ll x)
{
	// cout << x << endl;
	if(x == 1) return;
	ll m = n;
	while(m % x == 0) m /= x;
	m %= x;
	if(m == 1) 
	{
		if(!used[x])
		{
			ans++;
			used[x] = 1;
		}
	}
}

int main()
{
	cin >> n;
	for(ll i = 1; i * i <= n; i++)
	{
		if(n % i == 0)
		{
			check(i); check(n / i);
		}
	}
	ll m = n - 1;
	for(ll i = 1; i * i <= m; i++)
	{
		if(m % i == 0)
		{
			check(i), check(m / i);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：QiFeng233 (赞：0)

# [F] Division or Substraction

看到 $n \leq 10^{12}$ 和除法，不难想到做法应该是 $O(\sqrt n)$ 的。我把这一大类方法统称为根号折半优化。主要思路是枚举 $1$ 到 $\sqrt n$，然后根据一些性质来解决 $\sqrt n$ 到 $n$ 的部分。

首先我们看到 $k \geq \sqrt n$ 时，除法最多做一次，并且剩下部分在 $1$ 到 $\sqrt n$ 以内。

那么我们枚举 $x \in [1,\sqrt n]$，然后当 $x \mid (n-1)$ 时增加答案。

但是对于$k \in [2,\sqrt n]$，好像就只能直接判断了。但是这个模拟过程其实有一点要注意，就是你一但除到除不了了，那之后是不会出现减减又能除的。证明也很简单：

设当前数字是 $a$，如果减减又能除，也就是 $k \nmid a$，但是又 $a-xk=yk$ 即 $a = (x+y)k$ 即 $k \mid a$，二者互相矛盾，故不成立。

那么这样检查的时候就简单多了。

总复杂度 $O(\sqrt n(1 + \log_k\sqrt n))$，实际到不了这个上界。

对了，因为 $n$ 是显然成立的，所以最后输出的是答案加一。

注意一点，当 $n$ 是形如 $x^2+1$ 的整数时会重复计数，要减一。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace QiFeng233{
	ll n,sn,ans;
	bool chk(ll x){
		ll tmp=n;
		while(tmp>1){
			if(tmp%x==0)tmp/=x;
			else{
				if((tmp-1)%x==0)return 1;
				else return 0;
			}
		}
		if(tmp==1)return true;
		else return false;
	}
	void solve(){
		scanf("%lld",&n);
		sn=(ll)sqrt((double)n);
		for(ll i=2;i<=sn;++i){
			if(chk(i))++ans;
		}
		for(ll i=1;i<=sn;++i)if((n-1)%i==0)++ans;
		if(n-1==sn*sn)--ans;
		printf("%lld",ans+1);
	}
}
signed main(){
	QiFeng233::solve();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

~~看到题目第一眼，不是思考而是打表找规律。~~

我们打个 $O(n)$ 的纯暴力枚举，输出满足条件的 $k$。

然后不难发现，$n-1$ 的因数都是答案。

简单的证明：若 $k\mid n-1$，那么我们知道 $k$ 与 $n$ 就是互质的。

根据打表结果，我们还能发现其他符合条件的 $k$ 都是 $n$ 的因数。

经分析，当 $x$ 不能整除 $k$，不管减去几次 $k$ 都无法再得到能整除 $k$ 的数（因为因数里没有 $k$ ）。

所以操作只能是先将 $n$ 一直除以 $k$ 直到其因子不含 $k$，然后一直减去 $k$（等价于 $\bmod k$ ）。

所以我们只要找到符合 $\left ( 1+k \times t \right )  \times k^p=n$ 的 $k$ 即可。

## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,s,ans;
int main(){
	scanf("%lld",&n);
	m=n-1;
	for(long long i=1;i*i<=m;i++){
		if(m%i==0)s+=2;
		if(i*i==m)s--;
	}
	ans+=s;
	for(long long i=2;i*i<=n;i++){
		if(n%i==0){
			m=n;
			while(m%i==0)m/=i;
			if(m%i==1)ans++;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：君のNOIP。 (赞：0)

~~看到题目第一眼，不是思考而是打表找规律。~~

我们打个 $O(n)$ 的纯暴力枚举，输出满足条件的 $k$ 。

然后不难发现， $n-1$ 的因数都是答案。

简单的证明： 若 $k\mid n-1$ ，那么我们知道 $k$ 与 $n$ 就是互质的。


根据打表结果，我们还能发现其他符合条件的 $k$ 都是 $n$ 的因数。

经分析，当 $x$ 不能整除 $k$，不管减去几次 $k$ 都无法再得到能整除 $k$ 的数（因为因数里没有 $k$）。

所以操作只能是先将 $n$ 一直除以 $k$ 直到其因子不含 $k$ ，然后一直减去 $k$ （等价于 $\%k$）

所以我们只要找到符合 $(1+k\times t) \times k^p = n $ 的 $k$。

**根据上式，我们知道 $k^p$ 一定是 $n$ 的因数。**

- 若 $p=0$ ，则 $k\mid n-1$

- 若 $p \ne 0$，则  $k^p\mid n$，所以也肯定有 $k\mid n$

那么我们只需加上 $n-1$ 因数个数，再枚举 $n$ 的因子，然后直接模拟判断其是否是符合条件的 $k$。

一些细节：

- 可能会找到重复的数，很显然答案不会很大，直接 map 维护就好。

- 在 $O(n^{0.5})$ 枚举 $n$ 的因数时，我们并不用判断 $n/i$ 符不符合，因为此时 $n/i < i$ ，肯定不符合。

Code：



------------
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
using namespace std;
#define LL long long
LL n, ans;
map<LL,bool>mp;

bool check(LL y){
	LL x = n;
	while(x > 1){
		if(x % y == 0) x /= y;
		else{
			x %= y;
			break;
		}
		
	}
	if(x == 1) return 1;
	return 0;
}

int main(){ 
	cin>>n;
	for(LL i = 1; i * i <= n-1; i++) if((n - 1) % i == 0) ans += 2, mp[i] = mp[(n-1)/i] = 1;
	if( (LL)sqrt(n-1) * (LL)sqrt(n-1) == n - 1) ans--;
	for(LL i = 2; i * i <= n; i++) if(check(i) && mp[i] == 0) ans++;
	cout<<ans;
}
```


---

