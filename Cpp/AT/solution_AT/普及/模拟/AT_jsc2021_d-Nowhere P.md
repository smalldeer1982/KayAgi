# Nowhere P

## 题目描述

给你一个大于或等于 $2$ 的整数 $P$。 

如果一个整数序列 $A_1, A_2, ..., A_N$ 满足以下条件，那么它被称为一个非常好的序列。

对于 $1$ 到 $N$ 之间的任何整数 $i$，$A_1+A_2+\dots+A_i$ 不是 $P$ 的倍数

总共有 $(P-1)^N$ 个长度为 $N$ 的整数序列，其中每个元素都在 $1$ 和 $P-1$ 之间，这些序列中有多少个是非常好的？

答案可能非常大，所以输出对 $10^9+7$ 取模后的答案。

## 样例 #1

### 输入

```
3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
3 2```

### 输出

```
0```

## 样例 #3

### 输入

```
45108 2571593```

### 输出

```
224219544```

# 题解

## 作者：Wf_yjqd (赞：4)

嗯……快速幂板子？结果我还写错了

------------

显然，第一个有 $p-1$ 种取值。

后面的只用避开比前一个大的最小的 $p$ 的倍数即可。

这个倍数 $a$ 的取值范围是 $last+1\le a\le last+p$，其中 $last$ 表示前一个数。

而后一个数 $next$ 的取值范围是 $1\le next\le p-1$。

所以，所有可能的 $next$ 中，最多只有 $1$ 个前缀和是 $p$ 的倍数。

于是得出，后 $n-1$ 个各有 $p-2$ 种取值范围。

最后，用快速幂维护每个数取值个数的乘积即可。

------------

给练板子的同学放个代码吧。。

不要学我，递归快速幂常数很大。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
ll n,p;
ll poww(ll x,ll y){
    if(!y)
        return 1;
    if(y&1)
        return x*poww(x,y-1)%mod;
    ll zjx=poww(x,y>>1);
    return zjx*zjx%mod;
}
int main(){
    scanf("%lld%lld",&n,&p);
    printf("%lld",(p-1)*poww(p-2,n-1)%mod);
    return 0;
}
//tjn&lyy
```


---

## 作者：CYZZ (赞：4)

# [Nowhere P](https://www.luogu.com.cn/problem/AT_jsc2021_d)
## 题意
给你两个数 $n$ 和 $p$，求长度为 $n$，对于任意 $\forall i\in[1,n]$ 满足 $a_i\in [1,p-1]$ 且 $p\nmid\sum_{j=1}^{i}a_i$ 的数组有多少个。
## 思路
一位一位考虑。对于 $a_1$，它可以选 $[1,p-1]$ 中的任意一个数，有 $p-1$ 种选法。对于 $a_i$，假设 $\sum_{j=1}^{i-1}a_i\equiv k\pmod p$，则 $[1,p-1]$ 中除了 $k$ 以外其他都能选，共 $p-2$ 种选法。根据乘法原理，总共的方法数就是 $(p-1)\times (p-2)^{n-1}$，次方用快速幂计算即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,p,mod=1e9+7;
int qpow(int x,int y)
{
    int ret=1;
    for(;y;y>>=1,x=x*x%mod)
    {
        if(y&1)
            ret=ret*x%mod;
    }
    return ret;
}
signed main()
{
    scanf("%lld%lld",&n,&p);
    printf("%lld",(p-1)*qpow(p-2,n-1)%mod);
}
```
希望本篇题解能帮到大家！！！

---

## 作者：WOL_GO (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_jsc2021_d)

这就是一个快速幂版子题。

显然的，第一个数只有 $p-1$ 种取值，后面的 $n-1$ 个数则有 $p-2$ 种取值，所以答案为 $(p-1) \times (p-2)^{n-1}$，别忘了还有模数，用快速幂处理一下就好了。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=1e9+7;
int n,m;
ll qpow(ll a,int b){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}
int main(){
	cin>>n>>m;
	cout<<qpow(m-2,n-1)*(m-1)%mod;
	return 0;
} 
```

 

---

## 作者：Zhao_daodao (赞：1)

# [Nowhere P 题目传送门](https://www.luogu.com.cn/problem/AT_jsc2021_d)

## 题目思路

显然第一个数有 $p-1$ 种可能的取值。对于后面的数，每一个书都需要避开比上一个数大的最小的 $p$ 的倍数。~~显然~~，后面的每一个数只有 $p-2$ 种取值。只需要用 _**快速幂**_ 求出这个数就可以直接输出啦。


## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,p;
const int MOD=1e9+7;
int ksm(int x,int y)
{
    int ans=1;
    while(y)
    {
        if(y&1)
            ans=ans*x%MOD;
        y=y/2;
        x=x*x%MOD;
    }
    return ans;
}
signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>p;
    cout<<(p-1)*ksm(p-2,n-1)%MOD;
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：1)

## [Nowhere P](https://www.luogu.com.cn/problem/AT_jsc2021_d)

## 题意
给你两个数 $N$，$P$。输出用小于 $P$ 的正整数组成的有 $N$ 个数的序列，满足 $\forall i,\sum_{j=1}^{i} a_j $ 不为 $P$ 的倍数，有多少个。
## 思路分析
定义：$S_i=\sum_{j=1}^{i}a_j$.

对第一个数来说，怎么取都满足 $a_1 \neq P$，所以有 $P-1$ 种取法。

对第 $2$ 到第 $N$ 个数来说，只要满足 $S_i \neq P \times k(k\in Z^+)$ 即可，而对于 $S_{i-1}$ 来说，只有一个数能让它满足 $s_{i-1}+x$ 为 $P$ 的倍数，所以有 $P-2$ 种取法。

故答案为 $(P-1)*(P-2)^{N-1}$ .

---
PS：要对 $10^9+7$ 取模，要开 $\verb|long long|$。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int mod=1e9+7;
int n,p;
ll qpow(ll a,int b){
	ll res=1;
	while(b){
		if(b&1)res=res*a%mod;
		b>>=1,a=a*a%mod;
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>p;
	cout<<qpow(p-2,n-1)*(p-1)%mod;
	return 0;
} 
```

---

## 作者：_DeepBlue_ (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_jsc2021_d)

这就是一个快速幂版子题。

显然的，第一个数只有 $p-1$ 种取值，后面的 $n-1$ 个数则有 $p-2$ 种取值，所以答案为 $(p-1) \times (p-2)^{n-1}$，别忘了还有模数，用快速幂处理一下就好了。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=1e9+7;
int n,m;
ll qpow(ll a,int b){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}
int main(){
	cin>>n>>m;
	cout<<qpow(m-2,n-1)*(m-1)%mod;
	return 0;
} 
```

 

---

## 作者：ztntonny (赞：0)

## 解法

楼上叙述的相当的清楚了，这里主要向大家深入介绍一下快速幂~~大佬跳过即可~~。

快速幂，就是在 $\mathcal{O(\log(n))}$ 的时间复杂度内算出 $m^n$。其原理在于一组基本的递推式：

$$m^{2\times k}=m^k\times m^k$$

$$m^{2\times k+1}=m^k\times m^k\times m$$

然后就可以通过许多方法求解了，个人认为用递归写比较方便，放一个板子在下面。

## 正解

现在我们分析一下，对于第 $i$ 个数，设前 $i-1$ 个数的和对 $P$ 取模为 $S_{i-1}$，那么第 $i$ 个数就有除 $P-S_{i-1}$ 的 $p-2$ 种取法。又因为第一个数有 $n-1$ 种取法，根据乘法原理，推出式子：

$$ans=(p-1)\times(p-2)^{n-1}$$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;
ll n , p;

ll fpow( ll m , ll k )
{
	if ( k == 0 )	return 1;//m^{0} = 1
	ll s = fpow( m , k / 2 );
	if ( k % 2 == 0 )	return s * s % mod;
	else	return s * s % mod * m % mod;
}

int main()
{
	cin >> n >> p;
	cout << ( p - 1 ) * fpow( p - 2 , n - 1 ) % mod;
	return 0;
}
```

---

