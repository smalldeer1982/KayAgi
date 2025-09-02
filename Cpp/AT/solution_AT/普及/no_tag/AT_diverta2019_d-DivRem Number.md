# DivRem Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/diverta2019/tasks/diverta2019_d

すぬけ君は高橋君から正の整数 $ N $ をもらいました。 正の整数 $ m $ が以下の条件を満たすとき、 *お気に入りの数* と呼ばれます。

- $ N $ を $ m $ で割った商とあまりが等しい、すなわち $ \lfloor\ \frac{N}{m}\ \rfloor\ =\ N\ \bmod\ m $ が成立する

お気に入りの数を全て求め、その総和を出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 10^{12} $

### Sample Explanation 1

\- お気に入りの数は $ 3 $ と $ 7 $ の $ 2 $ つです。これらの総和である $ 10 $ を出力してください。

### Sample Explanation 2

\- オーバーフローに注意してください。

## 样例 #1

### 输入

```
8```

### 输出

```
10```

## 样例 #2

### 输入

```
1000000000000```

### 输出

```
2499686339916```

# 题解

## 作者：chl090410 (赞：5)

## The Solution to AT_diverta2019_d DivRem Number

### Description

给出正整数 $n$，求出所有的满足 $n$ 除以 $m$ 的商等于 $n$ 除以 $m$ 的余数的 $m$ 的和。

### Solution

我们设这个商为 $x$，那么余数也为 $x$，而被除数 $=$ 商 $\times$ 除数 $+$ 余数，于是就有 $n=mx+x=x(m+1)$，所以我们只需枚举 $x$ 即可求出 $m$。

又因为除数 $>$ 余数，所以 $m>x$，于是就有 $n=x(m+1)>x(x+1)$，所以，我们枚举到 $x\times(x+1)\ge n$ 时就要退出循环。

总时间复杂度约为 $O(\sqrt n)$，可以通过本题。

### AC code 如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
signed main(){
	cin>>n;
	for(int i=1;i*(i+1)<n;i++){
		if(n%i==0) m+=(n/i-1);
	}
	cout<<m; 
	return 0;
}

---

## 作者：囧仙 (赞：2)

## 题目大意

给定正整数 $n$，计算：

$$\sum_{m\in\Bbb{N^+}}\left[\left\lfloor\frac{n}{m}\right\rfloor=(n\bmod m)\right]m$$

## 题解

容易发现，

$$\begin{aligned}
&&\left\lfloor\frac{n}{m}\right\rfloor&=(n\bmod m)\cr
\iff&& \left\lfloor\frac{n}{m}\right\rfloor&=n-m\left\lfloor\frac{n}{m}\right\rfloor \cr
\iff &&n&=(m+1)\left\lfloor\frac{n}{m}\right\rfloor \cr
\end{aligned}$$

于是有，

$$(m+1) \mid n$$

所以我们枚举 $n$ 的因子，可以得到所有**可能**合法的 $m$。然后判断一下是否符合题目给出的条件就行了。又因为对于每个大于 $\sqrt n$ 的因子，用 $n$ 除以它的结果必然小于 $\sqrt n$，因此我们只要枚举 $[1,\lfloor\sqrt n\rfloor]$ 当中 $n$ 的因子就能得到 $n$ 所有的因子。

时间复杂度为 $\mathcal O(\sqrt n)$，可以通过本题。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
i64 n,x,ans;
int main(){
    scanf("%lld",&n);
    if(n==1) puts("0"),exit(0);
    for(x=1;1ll*x*x<n;++x) if(n%x==0){
        if(x!=1&&n%(  x-1)==n/(  x-1)) ans+=  x-1;
        if(      n%(n/x-1)==n/(n/x-1)) ans+=n/x-1;
    }
    if(n%x==0&&n%(x-1)==n/(x-1)) ans+=x-1; 
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：1)

小学数学有一个关系式：$n=\lfloor\dfrac nm \rfloor \times m + n \bmod m = \lfloor\dfrac nm \rfloor \times(m+1)$  
于是 "favorite" 数一定是 $n$ 的因数 $-1$，只需要判断一下即可。  
```python
def read(): return list(map(int, input().strip().split()))

def all_factors(n):
    small, large = [], []
    for i in range(1, int(n**0.5) + 1, 2 if n & 1 else 1):
        if not n % i:
            small.append(i)
            large.append(n // i)
    if small[-1] == large[-1]:
        large.pop()
    large.reverse()
    small.extend(large)
    return small

ans = 0
n = int(input())
for j in all_factors(n)[1:]: // 除零错误
    i=j-1
    if n//i == n%i:
        ans+=i
print(ans)
```



---

## 作者：Carey2012 (赞：0)

## 传送门
>[传送门](/problem/AT_diverta2019_d)
## 思路
因为 $\left \lfloor \frac{N}{m} \right \rfloor = N \bmod m$，\
所以我们可以设 $k$，其值为 $\left \lfloor \frac{N}{m} \right \rfloor$，\
然后条件可转换为 $N=km+k$，即 $N=k(m+1)$。\
最后暴力求解 $m$ 即可。
### 注意事项
其中 $m$ 和 $k$ 不能相等！
## data([AC_link](https://atcoder.jp/contests/diverta2019/submissions/61892216))
```CPP
//#pragma GCC optimize(2)
#include<bits/stdc++.h>
//#define gets(S) fgets(S,sizeof(S),stdin);
//#define a first
//#define c second
using namespace std;
const int MAX=1e5+10,mod=1e9+7;
typedef long long ll;
typedef pair<int,int> pii;
ll n,m;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<n/i;i++){
		if(n%i==0 && n/i-1!=i){m+=n/i-1;}
	}printf("%lld",m);
	return 0;
}
```

---

## 作者：opzc35 (赞：0)

## 题意

给定一个 $N$，求所有的 $M$ 满足 $\lfloor \frac{N}{M}\rfloor = N \bmod M$。

## 分析

众所周知，除法的一般形式都是这样的：

$$N \div M = Q \cdots R$$

放入题中式子可得

$$N \div M = M \cdots M$$

$$\therefore N = M\times M + M$$

所以时间复杂度在 $O(\sqrt N)$ 左右，枚举 $M$ 能够通过。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int ans;
signed main(){
    int n;
    cin>>n;
    for(int i=1;i*i+i<=n;i++){
        if(n%i==0){
            ans+=(n/i)-1;
        }
    }
    cout<<ans;
    return 0;
}
```

## TIPS

使用

```cpp
#define int long long
```

可将整个程序所有的 `int` 变为 `long long`，可是这样做有一个弊端，就是 `main()` 的返回值会变成 `long long`，可是 `C++` 中不允许这么做。

为了解决这个问题，我们可以将 `main()` 的返回值变为 `signed`（即无符号整数）也可以正常编译。

---

## 作者：FISH酱 (赞：0)

## 思路

设 $r$ 为余数，因除数与余数相等，所以除数为 $r$，被除数除以除数等于商，那么 $N\bmod r=r$，可以变为 $N = r \times r + r = r \times (r + 1)$，直接暴力枚举 $r$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define endl '\n'

ll n,ans;

int main(){
	scanf("%lld",&n);

	for(ll i=1;i*i+i<=n-1;i++){
		if(n%i==0){
			ans = ans+n/i-1;
		}
	}

	printf("%lld",ans);

	return 0;
}
```

---

## 作者：Rainbow_SYX (赞：0)

## 题意
给出正整数 $n$，求出所有的满足 $n$ 除以 $m$ 的商等于 $n$ 除以 $m$ 的余数的 $m$ 的和。
## 思路
一眼瞪出其中含有一个小学数学关系式：$n = \lfloor \frac{n}{m} \rfloor \times m + {n \bmod m} = \lfloor \frac{n}{m} \rfloor \times (m+1)$。

翻译一下就是被除数 $=$ 商 $\times$ 除数 $+$ 余数，因为余数又等于商，所以商 $ \times \ (m+1) =$ 被除数，所以我们只需枚举 $x$ 即可求出 $m$。

但是又因为余数小于除数，所以我们又可以得出 $N=x \times (m+1) < x \times (x+1)$。

所以我们循环到 $x \times (x + 1) \ge n$ 时就退出循环。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int n,m;
signed main() 
{
    scanf("%lld",&n);
	for(int i=1;i*(i+1)<n;i++)
		if(n%i==0) 
			m=m+(n/i-1);
	printf("%lld",m);
    return 0;
}
```

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/AT_diverta2019_d)

我们假设被除数就是 $n$，商是 $x$，除数是 $m$，那么余数根据题意也是 $x$。

由小学数学可以得知，存在有 $N = x \times m + x = x \times (m+1)$。

由于余数小于除数，那么就是 $x < m$。

将 $x < m$ 带入到第一个式子，可以得到 $N = x \times (m+1) < x \times (x+1)$。

那么我们就可以知道 $x$ 的取值范围：$x \times (x+1) < N$。

那么，暴力枚举 $x$ 即可。

AC Code：

```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;++i)
#define rp(i,x,y) for(register int i=x;i>=y;--i)
#define N 100005
#define MAX 1145141919810
using namespace std;
int n,ans;
inline void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n;
	for(int x=1;(x+1)*x<n;++x)
		if(n%x==0)ans+=n/x-1;
	cout<<ans;
}
signed main(){Enchanted();return 0;}




```

---

## 作者：Lvlinxi2010 (赞：0)

### 题目大意
给定正整数 $n$，求满足 $n$ 除以 $m$ 商为 $q$，余数为 $r$ 且 $q=r$ 的 $m$ 的和。

### 解题思路
$n=q \times m + r$，因为 $q=r$，则 $n=r \times (m+1)$，$r$ 是余数满足 $r<m$，枚举判断是否满足即可。

附上代码：
```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(ll i=(a);i<=(b);i++)
#define FR(i,a,b) for(ll i=(a);i>=(b);i--)
#define ll long long
using namespace std;
int main(){
	ll n,ans=0;
    scanf("%lld",&n);
    FL(i,1,n){
        ll p=n/(n/i),q=n/i;
        if(n%q==0){
            ll k=n/q-1;
            if(k>=i&&k<=p) ans+=k;
        }
        i=p;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：__Creeper__ (赞：0)

### 题意

给出正整数 $n ( 1 \le n \le 10^{12} )$，求出所有的满足 $n$ 除以 $m$ 的商等于 $n$ 除以 $m$ 的余数的 $m$ 的和。

### 思路

设 $n \bmod m = i$，化简得 $n = i + i \cdot m = i \cdot ( 1 + m )$。因为 $i < m$，所以 $i \cdot ( i + 1 ) < i \cdot ( m + 1 ) = n $， for 循环枚举即可，当 $i \cdot ( i + 1 ) \le n$ 就退出循环，时间复杂度为 $O (\sqrt{n})$，$n$ 最大为 $10^{12}$，可以通过此题。

### Code
```cpp
#include <bits/stdc++.h>
#define int long long //n会爆int，要开long long
using namespace std;

signed main()
{
	int n, m = 0;
	cin >> n;
	for ( int i = 1; i * ( i + 1 ) < n; i++ )
	{
		if ( n % i == 0 ) 
		{
			m += ( n / i - 1 );
		}
	}
	cout << m; 
	return 0;
}
```

---

## 作者：cosf (赞：0)

转换题意，假设 $N \bmod m = r$，则 $N = r + rm = r(m + 1)$。因为 $r < m$，所以 $r(r + 1) \lt r(m + 1) = N$，枚举即可。

```cpp
#include <iostream>
using namespace std;

using ll = long long;

int main()
{
    ll n;
    cin >> n;
    ll s = 0;
    for (ll r = 1; r * (r + 1) < n; r++)
    {
        if (n % r == 0)
        {
            s += (n / r) - 1;
        }
    }
    cout << s << endl;
    return 0;
}

```

---

## 作者：Practice_Account (赞：0)

### 题目大意

[DivRem Number](https://www.luogu.com.cn/problem/AT_diverta2019_d)

### 解题方法

$\left\lfloor\dfrac{N}{i}\right\rfloor$ 有 $\sqrt{N}$ 种取值方式，挨个枚举出 $m$ 并 判断 $m$ 是否在对应区间即可。

时间复杂度：$\mathcal{O(\sqrt{N})}$

### 参考代码

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<class T>
void func(T x){
    if(x < 0){
		x = -x;
		std::cout << "-";
	}
    if(x >= 10){
		func(x / 10);
    }
    putchar('0' + x % 10);
}
ll N;
void Solve(){
	std::cin >> N;
    ll ans = 0;
    for(ll i = 1; i <= N; ++ i){
        ll r = N / (N / i);
        ll t = N / i;
        if(N % t == 0) {
            ll k = N / t - 1;
            if(k >= i && k <= r) ans += k;
        }
        i = r;
    }
    func(ans);
}
int main(){
    Solve();
    return 0;
}

```


---

