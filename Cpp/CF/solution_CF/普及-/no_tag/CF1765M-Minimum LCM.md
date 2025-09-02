# Minimum LCM

## 题目描述

You are given an integer $ n $ .

Your task is to find two positive (greater than $ 0 $ ) integers $ a $ and $ b $ such that $ a+b=n $ and the least common multiple (LCM) of $ a $ and $ b $ is the minimum among all possible values of $ a $ and $ b $ . If there are multiple answers, you can print any of them.

## 说明/提示

In the second example, there are $ 8 $ possible pairs of $ a $ and $ b $ :

- $ a = 1 $ , $ b = 8 $ , $ LCM(1, 8) = 8 $ ;
- $ a = 2 $ , $ b = 7 $ , $ LCM(2, 7) = 14 $ ;
- $ a = 3 $ , $ b = 6 $ , $ LCM(3, 6) = 6 $ ;
- $ a = 4 $ , $ b = 5 $ , $ LCM(4, 5) = 20 $ ;
- $ a = 5 $ , $ b = 4 $ , $ LCM(5, 4) = 20 $ ;
- $ a = 6 $ , $ b = 3 $ , $ LCM(6, 3) = 6 $ ;
- $ a = 7 $ , $ b = 2 $ , $ LCM(7, 2) = 14 $ ;
- $ a = 8 $ , $ b = 1 $ , $ LCM(8, 1) = 8 $ .

In the third example, there are $ 5 $ possible pairs of $ a $ and $ b $ :

- $ a = 1 $ , $ b = 4 $ , $ LCM(1, 4) = 4 $ ;
- $ a = 2 $ , $ b = 3 $ , $ LCM(2, 3) = 6 $ ;
- $ a = 3 $ , $ b = 2 $ , $ LCM(3, 2) = 6 $ ;
- $ a = 4 $ , $ b = 1 $ , $ LCM(4, 1) = 4 $ .

## 样例 #1

### 输入

```
4
2
9
5
10```

### 输出

```
1 1
3 6
1 4
5 5```

# 题解

## 作者：LegendaryGrandmaster (赞：3)

期望 $a,b$ 的最小公倍数为 $a$，则 $a,b$ 互质。

要求 $b$ 要尽可能小，则 $a$ 尽可能大。

当其中有一个数是 $n$ 的因数时，则 $n$ 与它的差和这个因数为倍数关系。

找到 $n$ 的最大因数，在用 $n$ 与其因数相减可得答案。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int cnt(int x)
{
	for(int i=2;i<=x/i;i++)
		if(x%i==0)return x/i;
	return 1;
}
void slove()
{
	int n;
	cin>>n;
	cout<<cnt(n)<<' '<<n-cnt(n)<<'\n';
}
signed main()
{
	int t;
	cin>>t;
	while(t--)slove();
}
```

---

## 作者：Sukii (赞：3)

# 题意描述：
给出一个整数 $n$ ，找出两个正整数 $a,b$ 使其满足 $a+b=n$ 且 $a,b$ 的最小公倍数为 $a,b$ 的所有可能值中最小的一组。如有多解，输出任意一组。
# ~~好现在开始分析.~~
设求得的最小 $\operatorname{lcm}$ 值为 $ans.$


(~~着急的话直接跳到第三种情况看吧，前面在说废话.~~)

先考虑n为偶数的情况.

显然，若 $n$ 为偶数，则找出的 $a,b$ 的值均为 $n/2$ ,   此时有 $ ans=\operatorname{lcm}(a,b)=n/2 $.

 再考虑n为质数的情况.
 
容易得到, $\operatorname{gcd}(a,b)=1.$

~~还是简单证一下:~~


若 $\operatorname{gcd}(a,b)!=1$ ,则 $a,b$ 均为合数，显然此时 $n=a+b$ 也为合数，矛盾.故结论成立.

所以此时 $ans=\operatorname{lcm}(a,b)=a\times b.$

又因为 $a+b$ 为定值，故运用一下~~小学学过的长方形面积与周长的相关知识~~，可知在 $a=1,b=n-1$ 时 $ans$ 有最小值为 $n-1$. (当然这个理论的成立当且仅当所有数都为正整数)

 好现在说说最后一种n为奇合数的情况.
 
~~(前面似乎都在说废话,因为这种情况是通解，上面的只是小优化)~~

先说结论：$ans=n-p,$ 其中 $p$ 为 $n$ 的最大非 $n$ 因子.

现在我们来证明结论的正确性.

由题意知 $a+b=n.$

设 $\operatorname{gcd}(a,b)=x,a=c\times x,b=d\times x$ ,所以有:

$\operatorname{gcd}(c,d)=1,\operatorname{lcm}(a,b)=\operatorname{lcm}(c\times x,d\times x)=c\times d\times x.$

因为 $n=a+b=(c+d)\times x$,故 $c+d=n/x$.

再次运用~~万能小学知识~~，  $c\times d>=n/x-1,c\times d\times x>=n-x$,其中 $x$ 为 $ a,b$ 的因子即为 $n$ 的因子之一.(当然这个理论的成立当且仅当所有数都为正整数)

故为了使 $ans$ 取最小，$x$ 就需要取最大,即为 $n$ 的最大非 $n$ 因子.

求 $x$ 的话,一种显然的方法是用 $n$ 除以 $n$ 的最小非1因子.

三种情况合并即为本题正解之一.

最坏情况时间复杂度： $O(t\times\operatorname{sqrt}(n))$ 

~~(?)管他的反正也不超时~~
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int f(int x)//都看得懂吧()
{
	for(int i=2;i<=sqrt(x);i++)if(x%i==0)return i;
	return 0;
}
int main()
{
	cin>>a;
	for(int i=1;i<=a;i++)
	{
		cin>>b;
		if(b%2==0){cout<<b/2<<' '<<b/2<<endl;continue;}
		else if(f(b)==0)cout<<1<<' '<<b-1<<endl;
		else cout<<b/f(b)<<' '<<b-b/f(b)<<endl;
	}
	return 0;//数据太水(也不那么水)所以就偷懒用cin,cout了
}
```

---

## 作者：Lyrella (赞：1)

# 题意
给你一个数 $n$，求出 $a,b$，使 $a+b=n$ 并且 $\text{lcm(a,b)}$ 最小。
# 题解
如果两个数不是整倍数关系，那么两个数的乘积一定会超过 $n$。（假设 $a\le b$）

### 证明：
设：$a=p_1\times k,b=p_2\times k,s=lcm(a,b)$（$p_1p_2$ 互质）

$\because a+b=n,\therefore (p_1+p_2)\times k=n$

$\because a\times b=s,\therefore p_1\times p_2\times k=s$

当 $s<n$ 时，$p_1\times p_2<p_1+p_2$，很容易发现：只有 $\min(p_1,p_2)=1$ 时才成立。

### 所以
设：$a=m,b=K\times m,S=b$

$\because a+b=n \therefore m\times(K+1)=n$

$\because a\times b=S,\therefore m\times K=S$

$\therefore S=n-m$

这时，为了让 $\text{S}$ 最小，我们就直接让 $\text{m}$ 最大，$\text{K}$ 最小。而这时 $\text{K+1}$ 就是 $\text{n}$ 除一以外的最小的因数，求出 $\text{K+1}$ 即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	int a = 1, n; cin >> n;
	for(int i = 2; i * i <= n; i++)if(n % i == 0){a = n / i; break;}
	cout << a << ' ' << n - a << '\n';
}
signed main(){
	int T; cin >> T;
	while(T--)solve(); return 0;
}
```

---

## 作者：loser_seele (赞：1)

一个很显然的观察是 $ n $ 为偶数时直接输出两个 $ \frac{n}{2} $ 即可，因为无论怎么构造 $\operatorname{lcm}$ 一定不小于两个数的较大值，而较大值显然至少为 $ \frac{n}{2} $。

否则如果 $ n $ 为素数，那么拆分成的两个数一定互质，否则这个素数就可以整除他们的 $ \gcd $，不符合条件。所以直接输出 $ 1 $ 和 $ n-1 $ 一定是最优的。

考虑剩下的情况，只需要从中取出最大的真因子，然后就回到了第二种情况，于是暴力找到最大质因子 $ p $ 后输出 $ p $ 和 $ n-p $ 即可。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		int maxn=1;
		for(int i=2;i<=sqrt(n);i++)
			if(n%i==0)
			{
				maxn=i;
				break;
			}
		if(maxn!=1)
		maxn=n/maxn;
		if(n%2==0)
			cout<<n/2<<' '<<n/2<<'\n';
		else
			cout<<maxn<<' '<<n-maxn<<'\n';
	}
}
```


---

## 作者：cosf (赞：0)

## [CF1765M](https://codeforces.com/problemset/problem/1765/M) [Minimum LCM](https://www.luogu.com.cn/problem/CF1765M)

思路
---

首先，我们对于每一个 $n$，我们可以对他进行因数分解，即

$$
n=\prod p_i^{q_i}
$$

~~先别管他有什么用。~~

---

然后呢，我们来分析一下 LCM。假设有一个**质数** $p$，那么，对于所有的 $1\le i < p$，都有 $(i, p-i)=1$，其中 $()$ 表示最大公因数。证明：假设 $(i, p-i)=k$，那么 $k|i, k|p-i$，两式相加得 $k|p$，又因为 $p$ 是质数，所以 $k$ 只能是 $1$ 或 $p$。如果 $k=p$，则 $p|p-i$，显然矛盾。故 $(i, p-i)=1$。然后呢，有一个公式：

$$
ab=(a, b)[a, b]
$$

没错，大家都会推。我们把 $i, p-i$ 代进去得 $i(p-i)=[i, p-i]$。那么我们为了使 $[i, p-i]$ 最小，我们就要使 $i
(p-i)$ 最小。然后，大家应该都知道：**和一样，差小积大，差大积小。** 所以，当 $i=1$ 时，$i(p-i)$ 最小，即 $p-1$。（~~这么简单的就不证了~~）。

---

那么，如果 $n$ 是质数的话，我们就解决了。但问题是 $n$ 有可能不是质数。我们从简单的方向入手，假设 $n=p_1\times p_2\times P$，设 $p_1<p_2$。那么如果我们选择把 $p_1$ 拆了，那么结果就是 $(p_1-1)p_2\times P$，如果拆 $p_2$，则结果是 $p_1(p_2-1)\times P$。显然 $(p_1-1)p_2\times P<p_1(p_2-1)\times P$。所以拆 $p_1$ 更好。如果~~你和我一样好奇心强~~，那么一定会想到如果把 $p_1$ 和 $p_2$ 合在一起拆怎么样？结果就是 $(p_1p_2-1)\times P$，明显比 $p_1(p_2-1)\times P$ 大。

---

那么，大家因该知道为什么要因式分解了吧。我们就取 $n$ 的最小的质因数，然后把它拆了。其实也不需要因式分解，我们从质数中依次枚上去就可以了。根据因数的性质，除非他是质数，否则一定会有一个质因数小于或等于他的平方根。所以我们只需要枚到 $\sqrt{10^9}$ 的质数就可以了。时间是明显够的。

---

## [Code](https://www.luogu.com.cn/record/96675370)

```cpp
#include <iostream>
using namespace std;

#define int long long // <-不开long long见祖宗（亲测）

int primes[10005];
int dct[50005];

void init_prime() // 生成质数，当时看成 2*10^9了，所以写了50000，其实只要35000应该就够了。
{
    for (int i = 2; i <= 50000; i++)
    {
        if (!dct[i])
        {
            primes[++primes[0]] = i;
            for (int j = i; i * j <= 50000; j++)
            {
                dct[i * j] = 1;
            }
        }
    }
}

signed main()
{
    int n;
    cin >> n;
    init_prime();
    while (n--)
    {
        int c;
        cin >> c;
        int e = 0;
        for (int i = 1; i <= primes[0]; i++)
        {
            if (c % primes[i] == 0)
            {
                cout << c / primes[i] << ' ' << c / primes[i] * (primes[i] - 1) << endl;
                e = 1;
                break;
            }
        }
        if (e)
        {
            continue;
        }
        cout << "1 " << c - 1 << endl;
    }
    return 0;
}

```

---

~~注：代码加了防复制工作，直接复制可能会CE（开头改了一下）。~~

---

致审核员：第一次写这么长的题解，求过审～


---

## 作者：qwerasdasd1 (赞：0)

## 原题

给出一个整数 $n$，找出两个正整数 $a,b$，使其满足 $a+b=n$ 且 $\operatorname{lcm}(a,b)$ 要尽可能小。

## 分析

+ 如何求 $\operatorname{lcm}(a,b)$ ？

—— $\operatorname{lcm}(a,b)=a\times b \div \gcd(a,b)$

—— $\gcd(a,b)=\gcd(b,a\bmod b)$

+ 考虑每个询问 $O(n)$ 枚举，总时间复杂度为 $O(tn\log n)$ ~~（必定炸裂）~~；因此考虑优化每次询问的时间复杂度

+ 若 $a,b$ 互质，即  $\gcd(a,b)=1$，此时 $\operatorname{lcm}(a,b)=a \times b$，当 $n$ 不是质数时显然不是最优选择，以下给出证明：

当 $a=1,b=n-1$ 时，$\operatorname{lcm}(a,b)=n-1$；

当 $a>1,b<n-1$ 时，

$\operatorname{lcm}(a,b)=ab=a(n-a)$

要证此时不是最优选择，只需证：

$a(n-a)=-a^2+an>n-1$

只需证：

$a^2-an+n-1<0$

整理得：

$(a-1)(a-n+1)=(a-1)(1-b)<0$

因此，只需枚举 $n$ 的因数即可，总时间复杂度 $O(t\sqrt n \log n)$

p.s 记得开 longlong，不然会炸~

## AC Code

```cpp
#include<stdio.h>
using namespace std;
typedef long long ll;
int t;
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
ll min(ll x,ll y){return x<y?x:y;}
int main(){
//	freopen("CF1765M.in","r",stdin);
//	freopen("CF1765M1.out","w",stdout);
	scanf("%d",&t);
	while(t--){
		ll n,ans=1145141919810,ansi;
		scanf("%lld",&n);
		if(n%2==0){//可考虑特判，这个简单想想就好了
			printf("%lld %lld\n",n/2,n/2);
			continue;
		}
		else if(n%3==0){//这个也可以特判，也很简单（懒得证了）
			printf("%lld %lld\n",n/3,n/3*2);
			continue;
		}
		for(ll i=1;i*i<=n;i++){//枚举因数
			ll j=n-i;
			if(ans>i*j/gcd(i,j)) ans=1ll*i*j/gcd(i,j),ansi=i;
			if(n%i==0){//如果是因数，考虑更新答案
				ll p=n/i,q=n-p;
				if(q==0) continue;
				if(ans>p*q/gcd(p,q)) ans=1ll*p*q/gcd(p,q),ansi=p;
			}
		}
		printf("%lld %lld\n",ansi,n-ansi);
	}
}
```


---

