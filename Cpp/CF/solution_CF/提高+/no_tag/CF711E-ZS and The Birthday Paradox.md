# ZS and The Birthday Paradox

## 题目描述

ZS the Coder has recently found an interesting concept called the Birthday Paradox. It states that given a random set of $ 23 $ people, there is around $ 50% $ chance that some two of them share the same birthday. ZS the Coder finds this very interesting, and decides to test this with the inhabitants of Udayland.

In Udayland, there are $ 2^{n} $ days in a year. ZS the Coder wants to interview $ k $ people from Udayland, each of them has birthday in one of $ 2^{n} $ days (each day with equal probability). He is interested in the probability of at least two of them have the birthday at the same day.

ZS the Coder knows that the answer can be written as an irreducible fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711E/8121bfbd453525218681493c31a89b9966c63f4e.png). He wants to find the values of $ A $ and $ B $ (he does not like to deal with floating point numbers). Can you help him?

## 说明/提示

In the first sample case, there are $ 2^{3}=8 $ days in Udayland. The probability that $ 2 $ people have the same birthday among $ 2 $ people is clearly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711E/a5402656ef77947511a2ab2caa912cd84e1c36c2.png), so $ A=1 $ , $ B=8 $ .

In the second sample case, there are only $ 2^{1}=2 $ days in Udayland, but there are $ 3 $ people, so it is guaranteed that two of them have the same birthday. Thus, the probability is $ 1 $ and $ A=B=1 $ .

## 样例 #1

### 输入

```
3 2
```

### 输出

```
1 8```

## 样例 #2

### 输入

```
1 3
```

### 输出

```
1 1```

## 样例 #3

### 输入

```
4 3
```

### 输出

```
23 128```

# 题解

## 作者：是个汉子 (赞：3)

### Solution

原题最后的答案比较难求，所以我们可以反方向思考：只需要求出所有人生日不同的概率。

显然这个概率为 $\dfrac{A_{2^n}^m}{2^{nm}}=\dfrac{\prod_{i=2^n-m+1}^{2^n-1}}{2^{n(m-1)}}$ 。

分母部分用快速幂即可，而分子部分需要我们思考一下，因为模数为 $10^6+3$ ，当 $m$ 大于模数时，分子的因数必有一项为模数的倍数，答案可输出 $0$ ，其他情况暴力求解即可。

但是，这个题还有一个需要注意的地方是分数的约分。因为分母为 $2$ 的幂，所以找出分子中 $2$ 的幂次即可。这里用到了 $Legendre's~formula$ 。因为对于所有 $1\leq a\leq 2^n$ ，都有 $a$ 与 $2^n-a$ 的 $2$ 的幂次相同，所以求出 $(m-1)!$ 中的 $2$ 的次数就好了。

时间复杂度： $O(\log k+\log n)$ 

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long

using namespace std;
const int mod=1e6+3;
ll n,k,num=0,fz=1,fm=1;

ll fpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

int main(){
    scanf("%lld%lld",&n,&k);
    num=1;
    while((1LL<<num)<k)  num++;
    if(num>n){
        printf("1 1");
        return 0;
    }
    num=0;
    for(ll i=k-1;i>=1;i>>=1) num+=(i>>1);
    ll a=fpow(2,n);
    fz=1;
    for(int i=1;i<k;i++){
        fz=(ll)fz*(a-i+mod)%mod;
        if(fz==0) break;
    }
    fm=fpow(a,k-1);
    int inv=fpow(fpow(2,num),mod-2);
    fz=(ll)fz*inv%mod,fm=(ll)fm*inv%mod;
    fz=(fm-fz+mod)%mod;
    printf("%lld %lld",fz,fm);
    return 0;
}
```



---

## 作者：Register_int (赞：1)

首先可以算出所有人生日都不相同的概率，在从所有情况中减掉即可。答案为：

$$1-\prod^{k-1}_i\dfrac{2^n-i}{2^n}$$

也就是：

$$1-\dfrac{(2^n)!/(2^n-k)!}{2^{nk}}$$

先特判掉天数都不够 $k$ 的情况。此时，如果 $k$ 大于等于模数，则两个阶乘的商算出来后必有一个因数是模数，此时分子取模后必定为 $0$，后面都不用算了。对于小于模数的情况，我们可以直接暴力算出分子。

但是我们仍然需要进行约分。容易发现，分母上是一个 $2^m$ 的形式，所以我们只需要找出分子中的所有 $2$ 因子。考虑翻转分子的值域，这样分子的因子个数就是 $[1,k)$ 中的个数加上 $2^n$ 的个数，计算后用逆元从分子、分母除掉。时间复杂度 $O(\log n+\log k)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e6 + 3;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; p >>= 1, b = b * b % mod) if (p & 1) res = res * b % mod;
	return res;
}

ll n, k, t, x, y;

int main() {
	scanf("%lld%lld", &n, &k);
	if (__lg(k - 1) >= n) return puts("1 1"), 0;
	for (ll i = k - 1; i; i >>= 1) t += i >> 1; t += n, n = qpow(2, n);
	if (k >= mod) x = 0;
	else { x = 1; for (int i = 0; i < k; i++) x = x * (n - i + mod) % mod; }
	y = qpow(n, k), t = qpow(qpow(2, t), mod - 2), x = x * t % mod, y = y * t % mod;
	printf("%lld %lld", (y - x + mod) % mod, y);
}
```

---

## 作者：shicj (赞：0)

# CF711E ZS and The Birthday Paradox题解

1. 题意

   求一年有 $2^n$ 天，$m$ 个人出现两人生日相同的概率。**答案输出对 $10^6+3$ 的取模分子和分母（约分后）**。

2. 思路

   - 首先想不进行优化的数学计算方法，求出两人生日相同的概率不容易，但我们可以求出所有人生日不同的概率（也就是[排列数](https://oi.wiki/math/combinatorics/combination/)除以所有情况数），再用 $1$ 减掉，即得公式
     $$
     p=1-\frac{A_{2^n}^{m}}{2^{nm}}
     $$
     展开 $A^m_{2^n}$ 得到
     $$
     p=1-\frac{\left(2^{n}\right)\left(2^{n}-1\right)\left(2^{n}-2\right)\cdots\left(2^{n}-m+1\right)}{2^{nm}}
     $$
     
   - 然后可以很容易想到用快速幂进行进行计算，求得分子和分母。
   
   - 但是，题目要求约分。容易看出，分数线上下同除的数一定是 $2^k$（因为分母是$2^{nm}$），且分子一定有剩余（不然答案就是 $0$ 了），因此只要知道分子中可以分解出几个 $2$ 就可以了。
   
   - 于是，可以使用勒让德定理（但我不会证明）。
     $$
     {v_p\left(n!\right)=\underset{i=1}{\overset{\infty}{\sum}}\lfloor\frac{n}{p^{i}}\rfloor}
     $$
     （$v_p(x)$ 表示 $x$ 质因数分解后 $p$ 的指数）
   
   - 这样，分子中可以分解出几个 $2$ 就可以用勒让德定理求出。
   
     下面讲一下具体的方法：
   
     - 首先想到的是用 $v_2(2^n!)-v_2((2^n-m)!)$ 算出结果，但 $1\le n \le 10^{18}$，显然TLE。
   
     - 然后想到分类讨论分子的各个组成部分，首先， $2^n$ 中一定有 $n$ 个 $2$，然后考虑之后每一项，可知每一项中 $2$ 的个数取决于减去的数中 $2$ 的个数，即而所有除 $2^n$ 之外的项中 $2$ 的个数就是每次减去的数中 $2$ 的个数的和，也就是它们乘积中 $2$ 的个数，即
       $$
       num=n+v_2(1 \times 2 \times 3 \times \cdots \times m-1))=n+v_2((m-1)!)
       $$
       此时可以计算。
   
   - 所以，约分除去的数就是
     $$
     2^{n+v_2((m-1)!)}
     $$
     可用快速幂求出。
   
   - 最后一步，分子和分母同时乘需要除去的数的乘法逆元，答案就出来了。
   
3. 注意

   - 注意数据规模，要开 ```long long```，计算 $nm$ 时需要 ```__int128```。
   - 可以 ```#define int __int128``` 这时主函数类型要改，且注意输出时要强制转换为 ```long long```（```cout<<(long long)(......)<<......```），或者写输出函数（因为标准输入输出不支持 ```__int128```），也要注意选择合适的编译器版本。
   - 注意当 $2^n\le m$ 时直接输出 ```1 1``` 退出。
   - 注意计算 $2^i$ 时写成 ```1LL<<i```，不写 ```LL``` 会炸。

4. 代码

   ```cpp
   #include<bits/stdc++.h>
   #define int __int128
   #define ll long long
   using namespace std;
   const int mod=1e6+3;
   int n，m;
   bool check(){
   	int x=1;
   	for(int i=1;i<=n;i++){
   		x=x*2ll;
   		if(x>=m)
   			return false;
   	}
   	return true;
   }
   int qpow(int _n，int _k){
   	int ans=1ll;
   	while(_k) {
   		if(_k&1ll)
   			ans=ans*_n%mod;
   		_n=_n*_n%mod;
   		_k>>=1ll;
   	}
   	return ans;
   }
   int jian(int _a，int _b){
   	return (_a%mod-_b%mod+mod)%mod;
   }
   int getk(int _n){
   	int sum=0;
   	for(int i=1;_n/(1ll<<i)>0;i++){
   		sum+=_n/(1ll<<i);
   	}
   	return sum;
   }
   main(){
   	ll t_n，t_m;
   	cin>>t_n>>t_m;
   	n=t_n;m=t_m;
   	if(check()){
   		cout<<1<<" "<<1<<endl;
   		return 0;
   	}
   	int a=1;
   	for(int i=1;i<=m;i++){
   		a=a*jian(qpow(2，n)，i-1)%mod;
   		if(a==0)break;
   	}
   	int b=qpow(2，n*m);
   	int k1=n;
   	int k2=getk(m-1);
   	int k=k1+k2;
   	int inv_k=qpow(k，mod-2);
   	cout<<(ll)((b*qpow(500002，k)%mod-a*qpow(500002，k)%mod+mod)%mod)<<" "<<(ll)(b*qpow(500002，k)%mod)<<endl;
   	return 0;
   }
   ```

---

