# Alternating Sum

## 题目描述

You are given two integers $ a $ and $ b $ . Moreover, you are given a sequence $ s_0, s_1, \dots, s_{n} $ . All values in $ s $ are integers $ 1 $ or $ -1 $ . It's known that sequence is $ k $ -periodic and $ k $ divides $ n+1 $ . In other words, for each $ k \leq i \leq n $ it's satisfied that $ s_{i} = s_{i - k} $ .

Find out the non-negative remainder of division of $ \sum \limits_{i=0}^{n} s_{i} a^{n - i} b^{i} $ by $ 10^{9} + 9 $ .

Note that the modulo is unusual!

## 说明/提示

In the first example:

 $ (\sum \limits_{i=0}^{n} s_{i} a^{n - i} b^{i}) $ = $ 2^{2} 3^{0} - 2^{1} 3^{1} + 2^{0} 3^{2} $ = 7

In the second example:

 $ (\sum \limits_{i=0}^{n} s_{i} a^{n - i} b^{i}) = -1^{4} 5^{0} - 1^{3} 5^{1} - 1^{2} 5^{2} - 1^{1} 5^{3} - 1^{0} 5^{4} = -781 \equiv 999999228 \pmod{10^{9} + 9} $ .

## 样例 #1

### 输入

```
2 2 3 3
+-+
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 1 5 1
-
```

### 输出

```
999999228
```

# 题解

## 作者：Public_leda_team (赞：2)

这是一道非常简单的题目，同时纪念自己第一次独立切*1800。

考虑将式子拆成 $\frac{n + 1}{k}$ 段去处理。假设当前这一段的起点为 $x$，那么这一段的和为：

$$
\sum_{i = x} ^ {x + k - 1} s_{i - x}a^{n - i}b^i
$$

下一段即为：

$$
\sum_{i' = x + k} ^ {x + 2k - 1} s_{i - x - k}a^{n - i'}b^{i'}
$$

$s$ 始终相等，我们就先跳过。然后我们发现 $i' = i + k$，那么 $a$ 和 $b$ 在当前段对下一段的贡献即为 $\frac{b^k}{a^k}$。

这样式子就好推了，直接可以化为：

$$
\sum_{i = 0} ^ {\frac{n + 1}{k} - 1} (\frac{b^k}{a^k})^i\sum_{i = 0} ^ {k - 1}s_ia^{n - i}b^i
$$

发现第一项是一个等比数列形式，完全可以 $O(\log n)$ 地去求，因此考虑公比：

- 公比为 $1$：显然为：

  $$
  \frac{n + 1}{k}\sum_{i = 0} ^ {k - 1} s_ia^{n - i}b^i
  $$

- 公比不为 $1$：先设 $x = \frac{b^k}{a^k}$，然后动用幼儿园学过的等比数列求和公式，转换为：

  $$
  \frac{x ^ {\frac{n + 1}{k}} - 1}{x - 1}\sum_{i = 0} ^{k - 1}s_ia^{n - i}b^i
  $$

这样就很简单了，时间复杂度 $O(k \log P)$。

奉上代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int P = 1e9 + 9;
int n, k, a, b;
string s;
int power(int a, int b) {
  int ans = 1;
  for (; b; b >>= 1, a = a * a % P) {
    if (b & 1) ans = ans * a % P;
  }
  return ans;
}
int32_t main() {
  cin >> n >> a >> b >> k;
  cin >> s;
  int sum = 0;
  for (int i = 0; i < k; ++i) {
    sum += (s[i] == '-' ? -1 : 1) * power(a, n - i) % P * power(b, i) % P;
    sum %= P; 
    sum = (sum + P) % P;
  }
  sum = (sum + P) % P;
  int bases = power(b, k) * power(power(a, k), P - 2) % P;
  int x = (n + 1) / k;
  int ans;
  if (bases != 1) ans = (power(bases, x) % P - 1) % P * power(bases - 1, P - 2) % P;
  else ans = (n + 1) / k;
  ans %= P;
  cout << ans * sum % P;
}
```

---

## 作者：Dawn_cx (赞：2)

首先推一下本蒟蒻的博客[传送门](blog.csdn.net/dhdhdhx)

这个题是我们考前集训的题 想看完整三道题的请点右边[传送门](blog.csdn.net/dhdhdhx/article/details/102875877)

广告植入完毕 ~~(逃~~

本题由于$s$是循环的，所以我们从循环入手

注意到当下标$i$对于$k$的余数是一样的时候，$s$数组的值也是一样的，并且二者之间相差$(\frac{b}{a})^k$倍，所以我们可以直接用等比数列求和来做。

等比数列求和公式:
>数列共有$n$项，首项为$a_1$，公比为$q$，那么等比数列的和为$S_n=a_1\frac{1-q^n}{1-q}$

所以我们只需要枚举$0-k$中的数就行了，复杂度$O(klog_n)$

注意:

$1.$我小学从学这个公式到现在都不知道为什么要把$1$放前面..写公式时候这么写行，但是写代码咱别上头。

$2.$这个数列之和是$s_i$倍的等比数列和，不要把$s_i$乘到$a_1$里！！！！！！网站上这个可以过但是$cf$上不行！！！！

$3.$公比为$1$的时候公式炸了，所以公比为$1$时得直接算，就是$s_i×a^n$

上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N int(1e5+10)
typedef long long ll;
const ll mod=1e9+9;
inline ll quickpow(ll x, ll y){
	while(x<0)x+=mod;
	ll ret=1;
	while(y){
		if(y&1)(ret*=x)%=mod;
		(x*=x)%=mod,y>>=1;
	}
	return ret;
}
ll n,a,b,k,ans,sum[N],s[N];
char ch;
int main(){
	scanf("%lld%lld%lld%lld",&n,&a,&b,&k);
	for(ll i=1;i<=k;i++){
		ch=getchar();
		while(ch!='+'&&ch!='-')ch=getchar();
		if(ch=='+')s[i-1]=1;
		else s[i-1]=mod-1;
	}
	for(ll i=0;i<k;i++){
		ll a1=quickpow(a,n-i)%mod*quickpow(b,i)%mod;
		ll q=quickpow(b,k)*quickpow(quickpow(a,k),mod-2)%mod;
		ll nown=(n+1)/k;
		if(q==1)(ans+=s[i]*a1%mod*((n+1)/k)%mod)%=mod;
		else (ans+=s[i]*(a1*(quickpow(q,nown)-1)%mod*quickpow(q-1,mod-2)%mod)%mod)%=mod;
	}
	printf("%lld\n",ans);
}
```


---

## 作者：DLYdly1105 (赞：1)

### CF963A Alternating Sum

数论题。

发现我数学好菜所以补一补（

题意： $\sum_{i = 0}^{n} s_i a^{n - i}b^i$ 求这个式子模 $10^9+9$ 的值，$s_i$ 的周期为 $k$。

$k\le10^5$，所以 $0\sim k-1$ 直接求，对于后面的，你发现前一个周期的和，假设是 $sum$，那么下一个周期的和就是 $sum\times b^k\div a^k$。

那么转化成等比数列求和了，注意公比是 $1$ 时要特判，不然就会wa on #9了。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,mod=1e9+9;
int n,a,b,k,sum;
char s[N];
int kasumi(int a,int b)
{
    a%=mod;
    int res=1;
    while(b)
    {
        if(b&1)res=1ll*res*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return res;
}
int main()
{
    scanf("%d%d%d%d",&n,&a,&b,&k);
    scanf("%s",s);
    for(int i=0;i<k;i++)
    {
        if(s[i]=='+')sum=1ll*(sum+1ll*kasumi(a,n-i)*kasumi(b,i)%mod)%mod;
        else sum=1ll*(sum+mod-1ll*kasumi(a,n-i)*kasumi(b,i)%mod)%mod;
    }
    int d=1ll*kasumi(b,k)*kasumi(kasumi(a,k),mod-2)%mod;
    if(d==1)printf("%d",1ll*sum*(n+1)%mod*kasumi(k,mod-2)%mod);
    else printf("%d",1ll*sum*(kasumi(d,(n+1)/k)+mod-1)%mod*kasumi(d-1,mod-2)%mod);
    return 0;
}
```

---

## 作者：Self_Killer (赞：1)

好久没写题解了，顺手切一道数论水题吧

[题目传送门](https://www.luogu.com.cn/problem/CF963A)

题目大意不解释了，自己去看翻译吧

------------

## 主要知识点

- ### 快速幂

在这道题中，普通的一个一个乘肯定是会超时的，这就需要用到快速幂了。

快速幂主要代码如下：

```cpp
int qpow(int x,int y){
	int c = 1;
	while(y){
		if(y & 1) (c *= x) %= mod;
		(x *= x) %= mod;
		y >>= 1;
	}
	return c;		
}
```

快速幂本质其实是**二进制拆分**。

------------

- ### 费马小定理

费马小定理：
如果 $p$ 是一个质数

而整数 $a$ 不是 $p$ 的倍数

则有$a ^ {p-1} ≡ 1 \pmod p$

**如何证明？**

对于质数 $p$，$p$ 的完全剩余系为 $\{1,2,3,…,p-1\}$

因为 $a$ 和 $p$ 互质,所以 $\{a,2a,3a,…,(p-1)a\}$ 也是 $p$ 的完全剩余系

$a \times 2a \times 3a \times \cdots \times (p-1)a ≡ 1 \times 2 \times 3 \times \cdots \times (p-1) \pmod p$

$(p-1)! \times a^{n-1} ≡ (p-1)! \pmod p$

因为 $(p-1)!$ 和 $p$ 互质，两边同时除以  $(p-1)!$，得证。

------------

## 解题

可以发现题目中有一个等比数列求和，公比为 $\dfrac{b^n}{a^n}$。

那么我们就可以算出每一项进行累加，要注意判断负数。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 9;
int qpow(int x,int y){//快速幂 
	int c = 1;
	while(y){
		if(y & 1) (c *= x) %= mod;
		(x *= x) %= mod;
		y >>= 1;
	}
	return c;		
}
int n,a,b,k,sum,ans;string s;
signed main(){
	cin >> n >> a >> b >> k;
	int gb = (qpow(b,k) * qpow(qpow(a,k),mod - 2)) % mod;//公比 
	int bb = (b * qpow(a,mod - 2)) % mod;//小项的公比 
	int first = qpow(a,n);//第一个小项
	cin >> s;
	for(int i = 0;i < k;i++){
		(sum += (s[i] == '+'?1:-1) * first) %= mod;//算出第一大项 
		(first *= bb) %= mod;//每次乘上小项的公比 
	}
	for(int i = 1;i <= (n + 1) / k;i++){
		(ans += sum) %= mod;//算出结果 
		(sum *= gb) %= mod;//每次乘上大项的公比 
	}
	cout << (ans + mod) % mod;//输出注意负数 
	return 0;
}
```

时间复杂度 $O(k \log n + n \div k \log k)$。

但还是TLE了，所以我们要用到等比数列求和公式：$S_n = \dfrac{a_1 \times (q^n - 1)}{q - 1}$，其中 $a_1$ 为首项，$q$为公比，$n$ 为项数。

要注意特判 $q = 1$ 的情况，带入即可。

最终代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 9;
int qpow(int x,int y){//快速幂 
	int c = 1;
	while(y){
		if(y & 1) (c *= x) %= mod;
		(x *= x) %= mod;
		y >>= 1;
	}
	return c;		
}
int n,a,b,k,sum,ans;string s;
signed main(){
	cin >> n >> a >> b >> k;
	int gb = (qpow(b,k) * qpow(qpow(a,k),mod - 2)) % mod;//公比 
	int bb = (b * qpow(a,mod - 2)) % mod;//小项的公比 
	int first = qpow(a,n);//第一个小项
	cin >> s;
	for(int i = 0;i < k;i++){
		(sum += (s[i] == '+'?1:-1) * first) %= mod;//算出第一大项 
		(first *= bb) %= mod;//每次乘上小项的公比 
	}
	if(gb == 1){//特判 
		ans = (((n + 1) / k) * sum) % mod;//每一项相同，乘起来即可 
		cout << (ans + mod) % mod << endl;//输出注意负数 
		return 0;
	}
	ans = (((sum * (qpow(gb,(n + 1) / k) - 1)) % mod) * qpow(gb - 1,mod - 2)) % mod;//等比数列求和公式 
	cout << (ans + mod) % mod;//输出注意负数 
	return 0;
}
```

时间复杂度 $O(k \log n)$。

---

## 作者：Tachibana_Kimika (赞：0)

### 题目解析
本题要求
$$\sum_{i=0}^na^{n-i}b^it_i$$
其中 $t$ 为只包含 1 或 -1 的数组，由原题中的 $s$ 转化得来，并且 $t_i=t_{i+k}$。

因为 $t$ 有周期性，我们考虑把原题划分为 $k$ 个不同的子问题求解。对于第 $i$ 个子问题，我们要求
$$\sum_{j=0}^{\left\lfloor\frac{n+1}{k}\right\rfloor}a^{n-i-jk}b^{i+jk}$$
显然这个东西是一个等比数列，公比为 $\frac{b^k}{a^k}$，那么我们直接套用等比数列求和公式 $S_n=\frac{a_1(q^n-1)}{q-1}$，其中 $a_1$ 为首项，$q$ 为公比，$n$ 为项数。

带回原式，式子变化成
$$\sum_{i=0}^{k-1}t_ia^{n-i}b^i\frac{\left(\frac{b^k}{a^k}\right)^\frac{n+1}{k}-1}{\frac{b^k}{a^k}-1}$$
看着真的好恶心，但是我们发现右边那一坨和 $i$ 无关，可以预处理。

本题要求对 $10^9+9$ 取模，因为模数是质数，所以除法逆元我们考虑用费马小定理解决。

对了对了，当 $q=1$，也就是公比为 1 的时候我们的等比数列公式就寄了（除数为 0）,所以需要特判 $q=1$ 的情况。代码微压行。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
const long long p=1e9+9;
long long qpow(long long a,long long index){
	long long ans=1;
	while(index){
		if(index&1) ans=(ans*a)%p;
		a=(a*a)%p;
		index>>=1;
	}
	return ans;
}
char s[N];

int main(){
	long long n,a,b,k,tmp,q,ans=0;
	cin>>n>>a>>b>>k;
	q=qpow(b,k)*qpow(qpow(a,k),p-2)%p;//求公比
	tmp=(qpow(q,(n+1)/k)-1)*(qpow(q-1,p-2))%p;//预处理等比数列
	if(q==1) tmp=(n+1)/k;//特判，因为公比为1时等比数列每项均相同，所以等比数列的和相当于首项乘项数          
	for(int i=0;i<k;i++) cin>>s[i];
	for(int i=0;i<k;i++)//求答案，注意取模
		ans=(ans+((s[i]=='+')?1:-1)*qpow(a,n-i)*qpow(b,i)%p*tmp%p+p)%p;
	cout<<ans<<endl;
}
```

---

## 作者：狂风之息 (赞：0)

前置知识：逆元&快速幂

题意：求 
$$\sum_{i=0}^{n}s_ia^{n-i}b^i$$

其中 $s_{i+xk}=s_i~~(0\le x < \frac{n+1}{k})$

记 $\frac{b^k}{a^k}$ 为 $S$，$s_ia^{n-i}b^i=f(i)$。

对于本题，显然有 $f(i+xk)=f(i)\times S^x$

故原式等于 

$$\sum^{k-1}_{i=0}\sum_{j=0}^{\frac{n+1}{k}}f(i)S^j$$

提取出 $f(i)$：

$$\sum^{k-1}_{i=0}f(i)\sum_{j=0}^{\frac{n+1}{k}}S^j$$

此时右侧是一个等比数列求和：

$$\sum^{k-1}_{i=0}f(i)\frac{S^{\frac{n+1}{k}}-1}{S-1}$$

显然可以预处理出右侧的值，枚举 $i$ 的值快速幂算 $f(i)$ 即可。

注意特判 $S\bmod p=1$ 的情况，此时就是对于每个 $f(i)$ 都是取 $\frac{n+1}{k}$ 次，用同样方法计算即可。

时间复杂度 $O(k\log n)$。

注意开 long long 和取模。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000009
using namespace std;
int n,a,b,k;
char s[100005];

int fpow(int a,int b){
	if (!b) return 1;
	int tmp=fpow(a,b>>1);
	if (b&1) return (tmp*tmp%mod*a%mod+mod)%mod;
	return (tmp*tmp%mod+mod)%mod;
}

signed main(){
	scanf("%lld %lld %lld %lld",&n,&a,&b,&k);
	int S=fpow(fpow(a,mod-2),k)*fpow(b,k)%mod;
	int num=(fpow(S,(n+1)/k)-1)*fpow(S-1,mod-2)%mod;
	if (!num) num=(n+1)/k;
	int ans=0;
	scanf("%s",s+1);
	for (int i=1;i<=k;i++)
		ans=(ans+(s[i]=='+'?1:-1)*fpow(a,n-i+1)*fpow(b,i-1)%mod*num%mod)%mod;
	printf("%lld",(ans%mod+mod)%mod);
} 
```


---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF963A)

duel bot.duel bot.duel bot.

有循环节先看每节之间的关系。显然这是一个长度为 $\frac{n+1}{k}$ 的等比数列，比值是 $(\frac{b}{a})^k$，于是只需要求出第一个循环节的值，然后等比数列求和即可。

答案即为 $(\sum_{i=1}^{k}s_ia^{n-i}b^{i-1})\frac{1-(\frac{b}{a})^k}{1-\frac{b}{a}}$，除法用费马小定理求逆元，特判公比为 $1$ 的情况，当然写代码时略有不同。

Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,mod=1e9+9;
int n,m,s[N],a,b,res,q,ans;
int qpow(int x,int y){
    if(x<0)x+=mod;
    int ret=1;
    while(y){
        if(y&1)ret=1ll*ret*x%mod;
        y>>=1;x=1ll*x*x%mod;
    }
    return ret;
}
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%lld%lld%lld%lld",&n,&a,&b,&m);
    n++;
    for(int i=1;i<=m;i++){
        char ch;cin>>ch;
        if(ch=='-')s[i]=mod-1;else s[i]=1;
    }
    q=1ll*qpow(b,m)*qpow(qpow(a,m),mod-2)%mod;
    for(int i=1;i<=m;i++)res=(res+1ll*s[i]*qpow(a,n-i)%mod*qpow(b,i-1)%mod)%mod;
    if(q==1)ans=1ll*res*n/m%mod;
    else ans=1ll*res*(qpow(q,n/m)-1)%mod*qpow(q-1,mod-2)%mod;
    printf("%lld\n",ans);
    system("pause");
    return 0;
}

```

[record](https://www.luogu.com.cn/record/123761096)

---

