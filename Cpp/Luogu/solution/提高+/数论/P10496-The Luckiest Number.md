# The Luckiest Number

## 题目描述

中国人认为“8”是幸运数字。Bob 也喜欢数字“8”。此外，Bob 有自己的幸运数字 $L$。现在，他想构造出自己的最幸运的数字，即所有仅由数字“8”组成且是 $L$ 的倍数的正整数中的最小值。

## 样例 #1

### 输入

```
8
11
16
0```

### 输出

```
Case 1: 1
Case 2: 2
Case 3: 0```

# 题解

## 作者：LostKeyToReach (赞：16)

upd：修改了时间复杂度。

这是一道数论好题，我介绍一下蓝书的做法。

不难发现，$x$ 个 $8$ 连起来的正整数等价于 $8 \times \frac{10^x-1}{9}$，那么题目转换为，给出 $L$，让我们求一个最小的正整数 $x$，使得：
$$
L\mid8\times \frac{10^x-1}{9}
$$

我们先把两边乘上 $9$，得：
$$
9L\mid8 \times (10^x-1)
$$

我们不妨再设 $d=\gcd(L,8)$，又可以把原式化为：
$$
\frac{9L}{d}\mid10^x-1
$$

再改写为同余式：
$$
10^x \equiv 1\pmod{\frac{9L}{d}}
$$

此时，我们再引入一个引理：若 $a,n$ 互质，则满足 $a^x \equiv 1\pmod{n}$ 的最小正整数解为 $\varphi(n)$ 的约数。

证明过程（摘录自蓝书）：

反证法。假设满足 $a^x \equiv 1 \pmod{n}$ 的最小正整数解 $x_0$ 不能整除 $\varphi(n)$。

设 $\varphi(n)=qx_0+r(0 < r < x_0)$。因为 $a^{x_0} \equiv 1 \pmod{n}$，所以 $a^{qx_0} \equiv 1 \pmod{n}$。根据欧拉定理，有 $a^{\varphi(n)} \equiv 1 \pmod{n}$，所以 $a^r \equiv 1 \pmod{n}$。这与 $x_0$ 最小矛盾，故假设不成立，原命题成立。

证毕。

那么我们就可以轻松地解决这道题了，根据引理，我们先求出 $\varphi(\frac{9L}{d})$，然后枚举它的所有约数 $x$，当 $10^x \equiv 1 \pmod{\frac{9L}{d}}$ 时，直接输出即可。

如何判断无解呢？只需判断 $\gcd(10,\frac{9L}{d})$ 是否不等于 $1$ 即可。

这样，我们就完成了这道题目，时间复杂度 $O(\sqrt{n}\log n)$（排序后）。

主体部分代码如下：
```cpp
vector <ll> t;
ll phi(ll x) {
	ll ans = x;
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			ans = ans * (i - 1) / i;
			while (x % i == 0) x /= i;
		}
	}
	if (x > 1) ans = ans * (x - 1) / x;
	return ans;
}
int main() {
	ll n;
	int cnt = 0;
	while (read(n), n) {
		t.clear();
		n = 9 * n / gcd(n, 8ll);
		cout << "Case " << ++cnt << ": ";
		if (gcd(n, 10ll) != 1) {
			cout << "0\n";
		}
		else {
			ll x = phi(n);
			for (ll i = 1; i * i <= x; i++) {
				if (x % i == 0) {
					t.push_back(i);
					if (x / i != i) {
						t.push_back(x / i);
					}
				}
			}
			sort(t.begin(), t.end());
			int i;
			for (i = 0; i < t.size(); i++) {
				if (quick_pow(10ll, t[i], n) == 1) {
					break;
				}
			}
			writeln(t[i]);
		}
	}
}
```

---

## 作者：Starrykiller (赞：8)

题目条件转化为 $\displaystyle L\mid \frac{8(10^n-1)}{9}$，即 $9L\mid 8(10^n-1)$。其中 $n$ 为构造出来的数字的长度，满足 $n\ge 1$。

原式可以转化为

$$8(10^n-1)\equiv 0\pmod {9L}$$

记 $d=\gcd(8,L)$，由同余式的性质得

$$\frac{8}{d}(10^n-1)\equiv 0\pmod {\frac{9L}{d}}$$

两边同时乘以 $\dfrac{8}{d}$（因为此时 $\gcd\left(d,\frac{9L}{d}\right)=0$，所以是合法的），得到 $10^n-1\equiv 0\pmod {\frac{9L}{d}}$，即 $10^n\equiv 1\pmod {\frac{9L}{d}}$。

记 $p=\dfrac{9L}{d}$。这是一个经典的 BSGS 问题，可以用 BSGS 求解。然而，注意到这等效于让我们求 **$10$ 在模 $p$ 意义下的阶**。

我们说模 $p$ 下**元素 $a$ 的阶为 $n$**，当且仅当 $n$ 是最小的**正整数**，满足 $a^n\equiv 1\pmod p$，记为 $\mathrm{ord}_p(a)=1$。如果满足条件的 $n$ 不存在，我们就说 **$a$ 的阶为无穷**。一个很显然的 Observation 是，当且仅当 $\gcd(a,p)=1$ 时，$a$ 的阶不为无穷。



> **Proof.**
> 
> - 充分性。由 Euler 定理知，当 $\gcd(a,p)=1$ 时，$a^{\varphi(p)}\equiv 1\pmod p$。
> - 必要性。假设 $\gcd(a,p)\gt 1$，$a^n=1$（$n\ge 1$）。那么 $a^{n-1}$ 就是 $a$ 在模 $p$ 意义下的逆元。由 Bezout 定理知，当且仅当 $\gcd(a,p)=1$ 时，$a$ 在模 $p$ 意义下有逆元，矛盾。
> 
> 证毕。

显然在此题中，当 $\gcd(10,p)\gt 1$ 时，$a$ 的阶为无穷，即无解。

那么，我们给出几个引理。

> **Lemma 1**
> 
> $$a^n=1\pmod p\iff \mathrm{ord}_p(a)\mid n$$
> 
> > **Proof.**
> > 
> > - 充分性。记 $q=\mathrm{ord}_p(a)$，设 $n=kq+r$，其中 $0\lt r\lt q$。
> > 那么 $a^{n}\equiv a^{kq+r}\equiv a^{r}\equiv 1\pmod p$。注意到 $r\lt q$，这与 $q$ 的最小性矛盾。
> > - 必要性。显然。
> > 
> > 证毕。

> **Lemma 2**
> 
> $$\mathrm{ord}_a(p)\mid \varphi(p)$$
> 
> > **Proof.**（勾勒）
> > 
> > 由群论的 Lagrange 定理可知，子群的阶必为母群阶的因子，而母群 $(\mathbb{Z}/p\mathbb{Z})^*$ 的阶为 $\varphi(p)$，直接套用即可。

这启示我们，直接枚举 $\varphi(p)$ 的所有因数进行计算即可。当 $p\le 10^{10}$ 时，$\sigma_0(p)\le 2304$，应该能够通过。代码很好写，就不放了。

推荐相关练习题目：[[ABC335G] Discrete Logarithm Problems](https://www.luogu.com.cn/problem/AT_abc335_g) 和 [P5605 小 A 与两位神仙 ](https://www.luogu.com.cn/problem/P5605)。这两题本质相同，这是我的 [ABC335G 的题解](https://www.luogu.com.cn/article/bv8v4sfl)。


其实本题和 [P4884](https://www.luogu.com.cn/problem/P4884)，[[ABC222G] 222](https://www.luogu.com.cn/problem/AT_abc222_g) 很类似。

---

## 作者：nytyq (赞：5)

## 思路

有 $x$ 位的“8”数，则用权值法可以代替这个数，即：

$$

\displaystyle \frac{8*(10^x-1)}{9}

$$

如果满足题意，及以下式子：

$$  
\displaystyle L \mid \frac{8*(10^x-1)}{9}
$$

化简过程如下：

$$  
\displaystyle 9*L \mid {8*(10^x-1)}
$$

令 $d=\gcd(8,L)$，则：

$$  
\displaystyle \frac{9*L}{d} \mid {\frac{8}{d}*(10^x-1)}
$$

因为 $\frac{8}{d}$ 一定是一个常数，而 $9*\frac{L}{d}$ 和 $\frac{8}{d}$ 一定没有因数关系，则有以下式子：

$$
\displaystyle \frac{9*L}{d} \mid (10^x-1)
$$

则有：

$$
\displaystyle 10^x \equiv 1 \pmod {\frac{9*L}{d}}
$$

此处反证法易证 $x$ 为 $\phi(\frac{9*L}{d})$ 的因子。

枚举即可。

时间复杂度 $O(\sqrt{L}\log L)$。

---

## 作者：Link_1314 (赞：4)

# 思路：
先读题目，最幸运的数字是所有仅由数字 $8$ 组成且是 $L$ 的倍数的正整数中的最小值。

这道题的核心思想就是数论中的**欧拉定理**。

换句人话来说，就是给定一个正整数 $L$，求要有多少个 $8$ 连在一起形成的正整数是 $L$ 的倍数。

$x$ 个 $8$ 连在一起组成的正整数可写作：

$$8(10^x-1)\div9$$

题目就是让我们求出一个最小的 $x$，满足：

$$L\mid\frac{10^x-1}{9}\times8$$

我们先设 $d= \gcd(L,8)$，原式左右两边同时乘以 $9$ 得到：

$$9L\mid8\times(10^x-1)$$ 

继续化简，因为 $\gcd(L,8)~$ 一定整除 $(10^x-1)$，所以我们左右两边同时除以 $\gcd(L,8)$，最后改成同余式子得到：

$$10^x\equiv1\pmod{\frac{9L}{d}} $$

引理：若正整数 $a ,n$ 互质，则满足 $a^x\equiv1\pmod n$ 的最小正整数 $x_0$ 是 $\operatorname{\varphi (n)}$ 的约数。

~~证明略。~~

根据以上引理，我们只需求出欧拉函数 $\operatorname{\varphi (\Large\frac{9L}{d}\normalsize) }$，枚举它的所有约数，用快速幂逐一检查是否满足条件即可。时间复杂度为 $O(\sqrt{L}\log L)$。

# 补充：

快速幂的模数很大，所以我们就加上慢速乘，再做一点点优化，就可以 AC 这道题目，就不会被 hack 了，感谢大佬[Jerrywang09](https://www.luogu.com.cn/user/535063)，膜拜膜拜。

贴上我的 AC 代码。
# 代码：

```cpp
#include<bits/stdc++.h>
#define int long long//记得开long long 
using namespace std;

const int N=2e9;
int l,mod;//输入的幸运数字，模数 


int fm(int a,int b,int mod){//慢速乘 
    if(b==0) return 0;
    int tot=fm(a,b>>1,mod);
    if(b & 1) return ((tot+tot)%mod+a)%mod;
    else return (tot+tot)%mod;
}


int phi(int n){//求欧拉函数 
	int ans=n;
	for(int i=2;i<=n/i;i++){
		if(n%i==0){
			ans=ans/i*(i-1);
			while(n%i==0) n/=i;
		}
	}
	if(n>1) ans=ans/n*(n-1);
	return ans;
}


int fpow(int a,int b,int mod){//快速幂 
	if(b==0) return 1;
	int tot=fpow(a,b>>1,mod);
	if(b&1) return fm(a,fm(tot,tot,mod),mod);
	else return fm(tot,tot,mod);
}


int gcd(int a,int b){//求最大公因数 
	return b?gcd(b,a%b):a;
}


signed main(){
	int cnt=0;//统计输入了几次 
	while(cin>>l && l!=0){//循环输入，若输入零就停止 
		if(l==0) return 0;
		cnt++;//计算次数+1 
		int d=9*l/gcd(l,8),p=phi(d),ans=N;//利用从题目中推导出的公式求解 
		mod=d;
		for(int i=1;i*i<=p;++i){
			if(p%i){
				continue;	
			}
			if(fpow(10,i,mod)==1){
				ans=min(ans,i);	
			}
			if(fpow(10,p/i,mod)==1){
				ans=min(ans,p/i);	
			}
		}
		if(ans>=N){
			ans=0;	
		}
		cout<<"Case "<<cnt<<": "<<ans<<endl;
	} 
}
```
~~第一次写题解，写的一般，求大佬多多关照。~~

---

## 作者：Silence_nk_zht (赞：2)

## 题意
至少多少个 $ 8 $ 连在一起组成的正整数是 $ L $ 的倍数。
## 分析

首先， $ x $ 个 $ 8 $ 连在一起，组成的正整数可以表示为$ 8(10^x - 1) / 9 $，根据题意，我们可以知道 $ L \mid 8(10^x - 1) / 9 $ 。我们假设 $ d = gcd ( L , 8 ) $。

$ L \mid 8(10^x - 1) / 9 $ 将两边同时成 $ 9 $ 得到 $ 9L \mid 8(10^x - 1) $ 接着将两边的式子同时除以 $ d $ 式子依然成立，$ \frac{9L}{d} \mid 10^x - 1 $ ，得到这个式子后我们就易知 $ {10^x} \equiv 1 \pmod{\frac{9L}{d}} $。

我们提出猜想若正整数 $ a,n $ 互质时，则满足  $ {a^x} \equiv 1 \pmod{n} $ 的最小正整数 $ x_0 $ 是 $ \varphi(n) $ 的约数。

我们可以采用反证法，假设猜想不成立，那么就可以得知 $ \varphi(n) = qx_0 + r $ 其中 $ r $ 为 $ \varphi(n) /x_0 $ 的余数，因此 $ r < x_0 $，因为  $ {a^{x_0}} \equiv 1 \pmod{n} $ ，所以  $ {a^{qx_0}} \equiv 1 \pmod{n} $ ,根据欧拉函数  $ {a^{\varphi(n)}} \equiv 1 \pmod{n} $ ，所以  $ {a^{\varphi(n)-qx_0}} \equiv 1 \pmod{n} $ 成立，得到 $ {a^{r}} \equiv 1 \pmod{n} $，这个式子与原命题 $ r < x_0 $ 违背了，证明完成。

我们将证明出来的结果带入本题中就可以得知 $ x $ 是 $ \varphi(\frac{9L}{d}) $ 的因数，所以我们就可以直接枚举。
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,min1=LONG_LONG_MAX;
ll fan(ll x) {
	ll ans=x;
	for(ll i=2;i*i<=x;i++){
		if(x%i==0){
			ans=ans*(i-1)/i;
			while(x%i==0){
				x/=i;
			}
		}
	}
	if(x>1){
		ans=ans*(x-1)/x;
	}
	return ans;
}
ll fm(ll a,ll b,ll mod){
	ll ans=0;
	while(b){
		if(b&1)ans=(ans+a)%mod;
		b=b>>1;
		a=(a<<1)%mod;
	}
	return ans;
}
ll fp(ll a,ll b,ll mod){
	ll sum=1;
	while(b>0){
		if(b&1)sum=fm(sum,a,mod);
		a=fm(a,a,mod);
		b>>=1;
	}
	return sum%mod;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int l=1;;l++){
		ll min1=LONG_LONG_MAX;
		cin>>n;
		if(n==0)break;
		ll d=__gcd(n,(ll)(8));
		ll p=fan(9*n/d);
		bool flag=1;
		for(ll i=1;i*i<=p;i++){
			ll j=p/i;
			if(p%i==0){
				if(fp(10,i,(9*n/d))==1){
					cout<<"Case "<<l<<": "<<i<<'\n';
					flag=0;
					break;
				}
			}
			if(p%j==0){
				if(fp(10,j,(9*n/d))==1){
					min1=min(j,min1);
				}
			}
		}
		if(!flag)continue;
		if(min1==LONG_LONG_MAX)cout<<"Case "<<l<<": "<<0<<'\n';
		else cout<<"Case "<<l<<": "<<min1<<'\n';		
	}

	return 0;
}
```

---

## 作者：w9095 (赞：2)

[P10496 The Luckiest Number](https://www.luogu.com.cn/problem/P10496)

UPD：[被叉了](https://www.luogu.com.cn/discuss/855906)，原因是快速幂可能模数很大会爆 `long long`，改成 `__int128` 就好了。

考虑用一种比较方便表达的方式表示全是 $8$ 的数字。我们发现，长度为 $x$ 的全是 $8$ 的数字可以表示为 $\frac{10^x-1}{9}\times 8$。

根据题目要求，这个数字是 $L$ 的倍数，所以有下面式子：

$$L\mid\frac{10^x-1}{9}\times 8$$

两边同时乘以 $9$ 得到：

$$9L\mid8(10^x-1)$$

这个式子可以继续化简，考虑到 $\gcd(L,8)$ 一定整除 $8(10^x-1)$，我们考虑在左边除以 $\gcd(L,8)$，右边消去常数 $8$：

$$\frac{9L}{\gcd(L,8)}\mid10^x-1$$

由于没有什么关于这种式子的算法，所以我们改变式子的形式，把它变成同余式：

$$10^x-1\equiv 0\pmod {\frac{9L}{\gcd(L,8)}}$$

移项得：

$$10^x\equiv 1\pmod {\frac{9L}{\gcd(L,8)}}$$

转化为了高次不定方程，直接使用 exBSGS 解决。注意这题需要求出的是最小正整数解，所以 exBSGS 返回的答案必须大于 $0$。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,a,p,x,y,now=0;
map<long long,long long>h;
long long gcd(long long a,long long b)
{
	if(b==0)return a;
	else return gcd(b,a%b);
}

long long exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	   {
	   	x=1,y=0;
	   	return a;
	   }
	long long r=exgcd(b,a%b,x,y),d=x;
	x=y,y=d-a/b*y;
	return r;
}

long long power(long long a,long long p,long long mod)
{
	long long ans=1,x=a;
	while(p)
	   {
	   	if(p&1)ans=(__int128)ans*x%mod;
	   	p>>=1;
	   	x=(__int128)x*x%mod;
	   }
	return ans; 
}

long long bsgs(long long a,long long b,long long mod)
{
	h.clear();
	long long t=sqrt(mod)+1,now=1,inc=power(a,t,mod);
	if(a==0)
	   {
	   	if(b==0)return 1;
	   	else return -1;
	   }
	for(int i=0;i<=t-1;i++)h[(__int128)now*b%mod]=i+1,now=(__int128)now*a%mod;
	now=1;
	for(int i=1;i<=t;i++)
	    {
	    now=(__int128)now*inc%mod;
		if(h.count(now)>0&&((__int128)i*t-h[now]+1))return (__int128)i*t-h[now]+1;
		}
	return -1;
}

long long exbsgs(long long a,long long b)
{
	long long d=gcd(a,p),cnt=0,sum=1,ans=0;
	a%=p,b%=p;
	if(a==0)
	   {
	   	if(b==0)return 1;
	   	else return -1;
	   }
	while(d!=1)
	   {
	   	if(b%d!=0)return -1;
	   	cnt++,p/=d,sum=(__int128)sum*(a/d)%p,b/=d;
	   	d=gcd(a,p);
	   	if(sum==b&&cnt!=0)return cnt;
	   }
	exgcd(sum%p,p,x,y);
	x=(x%p+p)%p;
	ans=bsgs(a,(__int128)x*b%p,p);
	if(ans==-1)return -1;
    else return ans+cnt;
}

int main()
{
	while(1)
	    {
	    	scanf("%lld",&a);
	    	if(a==0)break;
	    	p=9*a/gcd(a,8),now++;
	    	long long ans=exbsgs(10,1);
	    	if(ans==-1)printf("Case %lld: 0\n",now);
	    	else printf("Case %lld: %lld\n",now,ans);
		}
	return 0;
}
```

---

## 作者：___Furina___ (赞：2)

### 这里提供一份 BSGS 的代码：

题解区的各位 dalao 已经把过程写的很详细了，我们直接列出要求解的式子：
$$
10^n\equiv1\pmod{\frac{9L}{d}} 
$$
其中 $d$ 是 $\gcd(L,8)$。

我们直接使用 BSGS 算法，但这里的余数是 $1$，所以要特殊处理一下。

时间复杂度是 $O(\sqrt n)$，但是用了 unordered_map，复杂度变大了一点。

代码如下：
```cpp
/*Life is too long to end at a grave*/
#include<bits/stdc++.h>
#define N ?
#define I_love_Furina return
#define forever 0
#define foreverr 1
#define endl '\n'
#define FIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
int n,T,m,mod;
signed main(){
    IOS;//FIO("");
    for(int k=1;;k++){
        cin>>n;
        if(n==0)break;
        cout<<"Case "<<k<<": ";
        unordered_map<int,int> q;
        n=n*9/__gcd(n,8ll);
        int sum=1,ans=1e18,sk=(ceil)(sqrt(n)),x;
        // cout<<n<<endl;
        if(__gcd(n,10ll)!=1ll){cout<<0<<endl;continue;}
        for(int i=1;i<sk;i++){
            sum=sum*10%n;
            q[sum]=i;
        }
        sum=sum*10%n;
        if(sum==1)ans=min(ans,sk);
        x=sum;
        for(int i=1;i<=sk;i++){
            if(q[sum])ans=min(ans,sk*i-q[sum]);//,cout<<ans<<" ";
            sum=sum*x%n;
        }
        cout<<ans<<endl;
    }
    I_love_Furina forever;
}

```

---

## 作者：MoonCake2011 (赞：2)

先转化成数学公式。

设答案为 $x$。

那么 $8888\dots8888=\dfrac{8(10^x-1)}{9}$（$x$ 个 $8$）。

因为 $10^x-1$ 为 $9999\dots9999$，这样就好说了。

由题意，要让 $L\mid\dfrac{8(10^x-1)}{9}$。

那就是 $9L\mid8(10^x-1)$。

接着，我们发现 $10^x$ 用欧拉定理最好解决，并且还有一个 $1$，所以尝试化为欧拉定理好做的形式（$a$，$n$ 互质，同余方程，把那个 $8$ 弄掉）。

化为同余方程最简单，最后再弄。

如果直接 $\dfrac{9L}{8}\mid 10^x-1$，会出现小数。

可以这样，设 $d=\gcd(L,8)$。

又转化为 $\dfrac{9L}{d}\mid10^x-1$。

这样既满足了不出现小数，又有 $a$，$n$ 互质。

同余方程自己化吧（作者 LaTex 功夫太差，模分数不会打）。

引理：若 $a,n$ 互质，满足最小的 $a^x \equiv 1 \pmod n$ 的 $x$ 必定是 $\varphi(n)$ 的因子。

可以使用反证法，设最小的 $x$ 满足 $\varphi(n)=qx+r(r>0)$。

$a^r \equiv a^{\varphi(n)-qx} \equiv \dfrac{a^\varphi(n)}{(a^x)^q} \equiv \dfrac{1}{1} \equiv 1 \pmod n$。

一顿操作猛如虎，显然 $r$ 比 $x$ 更优，与条件矛盾，故成立。

根据引理，我们可以求出 $\varphi(\dfrac{9L}{d})$ 的所有因子并用快速幂判断答案。

时复：$O(T\sqrt{n}\log n)$。

能过。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int mul(int a,int b,int mod){
    if(b==0) return 0;
    int tot=mul(a,b>>1,mod);
    if(b & 1) return ((tot+tot)%mod+a)%mod;
    else return (tot+tot)%mod;
}
inline int euler(int x){
	int sum=x;
	for(int i=2;i*i<=x;i++){
		if(x%i!=0) continue;
		sum=sum/i*(i-1);
		while(x%i==0) x/=i;
	}
	if(x!=1) sum=sum/x*(x-1);
	return sum;
}
inline int power(int x,int y,int mod){
	if(y==0) return 1;
	int tot=power(x,y>>1,mod);
	if(y & 1) return mul(x,mul(tot,tot,mod),mod);
	else return mul(tot,tot,mod);
}
inline void solve(int numb){
	int l;
	cin>>l;
	if(l==0) exit(0);
	int d=__gcd(l,8ll);
	int g=l/d*9ll;
	int cnt=1,b=euler(g);
	for(int i=1;i*i<=b;i++){
		if(b%i!=0) continue;
		if(power(10ll,i,g)==1){
			cout<<"Case "<<numb<<": "<<i<<"\n";
			return;
		}
	}
	int m=sqrt(b);
	for(int i=m;i>=1;i--){
		if(b%i==0 && power(10ll,b/i,g)==1){
			cout<<"Case "<<numb<<": "<<b/i<<"\n";
			return;
		}
	}
	cout<<"Case "<<numb<<": "<<0<<"\n";
}
signed main() {
    ios::sync_with_stdio(0);
	for(int i=1; ;i++) solve(i);
	return 0;
} 
```

---

## 作者：Rose_Melody (赞：1)

## Solution - The Luckist Mumber

[题目传送门](https://www.luogu.com.cn/problem/P10496)

### 前言

**调了这么久，写篇题解纪念一下。**

一眼数论题，对于这个蒟蒻数竞生来说是再好不过了。

然后呢，调了快 $2.5$ hour ……

### 题目分析

显然，$x$ 个 $8$ 组成的正整数等于 $8 \times \frac{10^{x} - 1}{9}$。便可以得到同余式：

$$8\times(10^{x}-1) \equiv 0 (\bmod 9L)$$

令 $d = \gcd(8 , L)$，得

$$10^{x}-1 \equiv 0 (\bmod \frac{9L}{d})$$

记 $m = \frac{9L}{d}$，上式等价于

$$10^{x}\equiv 1 (\bmod m)$$

我们要做的就是求出 **$x$ 的最小值，也就是 $10$ 模 $m$ 的阶。**

我们引入**欧拉定理：**

$$a^{\varphi(m)} \equiv 1 (\bmod m)$$

这里 $\gcd(a , m) = 1$。由阶的性质得：**若 $x$ 为 $a$ 模 $m$ 的阶，则 $x$ $|$ $\varphi(m)$**。证明详见小蓝本或 [OI-wiki](https://oi-wiki.org/math/number-theory/fermat/)。

只需枚举 $\varphi(m)$ 的因数，带入同余式验证即可。由上面推导，**在 $\gcd(10 , m) \neq 1$ 时无解**。

**注：设 $m = p_{1}^{\alpha_{1}} \times p_{2}^{\alpha_{2}} \times...\times p_{k}^{\alpha_{k}}$，则** 

$$\varphi(m) = m \times (1 - \frac{1}{p_{1}}) \times (1 - \frac{1}{p_{2}}) \times...\times (1 - \frac{1}{p_{k}})$$

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std ;
int n , u = 0 ;
__int128 qpow(__int128 a , int b , int Mod){  //快速幂
	__int128 ret = 1 ;
	while(b){
		if(b & 1){
			ret = ret * a % Mod ;
		}
		a = a * a % Mod ;
		b >>= 1 ;
	}
	return ret ;
}
int phi(int x){//求欧拉函数
	int k = x ;
	for(int i = 2;i * i <= x;i ++){
		if(x % i == 0){
			k = (k * (i - 1)) / i ;
			x /= i ;
		}
		while(x % i == 0){
			x /= i ;
		}
	}
	if(x > 1) k = (k * (x - 1)) / x ;  //若 x 为素数
	return k ;
} 

signed main(){
//	freopen(".in" , "r" , stdin) ;
//	freopen(".out" , "w" , stdout) ;
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	while(cin >> n && n != 0){
		cout << "Case " << ++u << ": " ;
		int m = (9 * n) / __gcd(8ll , n) ;
		if(__gcd(m , 10ll) != 1){
			cout << '0' << '\n' ;
			continue ;
		}
		int pi = phi(m) ;
		int ans = pi ;
		for(int i = 1;i * i <= pi;i ++){
			if(pi % i == 0){
				if(qpow((__int128)10ll , i , m) == 1){
					ans = i ; //肯定是最小的那个，退出循环
					break ;
				}
				if(qpow((__int128)10ll , pi / i , m) == 1 && i != 1){
					ans = (pi / i) ;
				}
			}
		}
		cout << ans << '\n' ;
	}
	return 0 ;
}
```


### 后记

至于为什么调了那么久，解释一下：

$m$ 最大是可达到 $10^{10}$ 的范围的，这导致以 $10$ 为底的快速幂在相乘时由于模数过大，**会爆 long long，所以快速幂开 __int128 才能过**。

---

## 作者：_HCl_ (赞：1)

有趣的数论题。
# P10496 题解

**题意简述**

给定一个正整数 $L$。问至少多少个 $8$ 连在一起组成的正整数是 $L$ 的倍数？

**思路引导**

我们先将 $n-1$ 个 $8$ 连成的数表达出来。

众所周知 $10^{n}-1=\overline{99\dots9}$, 故 $\overline{11\dots1}=\frac{10^{n}-1}{9}$, 则 $\overline{88\dots8}=\frac{8}{9}(10^{n}-1)$。

然后有
$$\begin{aligned}
L\mid\frac{8}{9}(10^{n}-1)
&\Leftrightarrow9L\mid8(10^{n}-1)
\\&\Leftrightarrow\dfrac{9L}{\gcd(8,L)}\mid(10^n-1)
\\&\Leftrightarrow10^n\equiv1\pmod{\dfrac{9L}{\gcd(8,L)}}
\end{aligned} $$

我们将问题转化为了求解最小的 $n$，可以使用 BSGS 进行求解，但是我不会。所以考虑欧拉定理。方便表述，记 $d=\frac{9L}{\gcd(8,L)}$。

根据欧拉定理，$n=\varphi(d)$ 显然是其中的一个解，但是这不是最小的。观察发现最小的 $n$ 一定是 $\varphi(d)$ 的因数。下证成立。

假设 $a^x\equiv1\pmod d$ 的最小解 $x_0$ 不是 $p=\varphi(d)$ 的因数。设 $x_0=qp+r$, 其中 $0<r<p$。那么有（为方便书写，以下同余式 $\pmod d$ 均省略）：
$$
a^{qp+r}\equiv1\Rightarrow (a^p)^q\cdot a^r\equiv 1\Rightarrow a^r\equiv 1
$$

由于 $r<x_0$，所以 $x_0$ 不是最小的解，与假设矛盾。故原命题得证。

因此，只需要枚举 $\varphi(d)$ 的每一个因数，计算是否满足 $10^n\equiv 1\pmod d$，找出最小值即可。

时间复杂度 $\mathcal{O}(\sqrt n)$。

**代码**

感觉自己代码写的算是比较清楚，就不写注释了，应该都看的懂的。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int L,MOD;
int phi(int x){
	int res=x;
	for(int i=2;i*i<=x;++i)
		if(x%i==0){
			res=res-res/i;
			while(x%i==0)x/=i;
		}
	if(x!=1)return res-res/x;
	else return res;
}
int qpow(int x,int y){
	int res=1;
	for(;y;y>>=1,x=(x*x)%MOD)if(y&1)res=res*x%MOD;
	return res;
}
signed main(){
	int L,id=0;
	cin>>L;
	while(L!=0){
		id++;
		int d=9ll*L/__gcd(L,8ll),p=phi(d),ans=1e9;
		MOD=d;
		for(int i=1;i*i<=p;++i){
			if(p%i)continue;
			if(qpow(10,i)==1)ans=min(ans,i);
			if(qpow(10,p/i)==1)ans=min(ans,p/i);
		}
		if(ans>=1e9)ans=0;
		cout<<"Case "<<id<<": "<<ans<<"\n";
		cin>>L;
	} 
}
```

---

## 作者：liuliucy (赞：1)

## 思路
首先，我们先把 lucky number 表示出来。

$$ \text{lucky number}=\sum^{n-1}_{i=0}8\times 10^i=8\times \frac{10^{n}-1}{9}$$

那根据题目条件，也就是 $9L|8\times (10^{n}-1)$。

因为 $\gcd(9,8)=1$ ，

所以另 $d=\gcd(L,8)$。

那我们可以有 $\frac{9L}{d}|10^{n}-1$，

另 $x=\frac{9L}{d}$，

我们有 $10^{n}\equiv 1(\mod x)$，这里其实可以直接用 BSGS 求解了，但这里我们也可以用另外一种方法。

根据欧拉定理，我们可以知道 $\varphi(x)$ 是一个解，但我们要求最小的 $n$，我们可以知道 $n|\varphi(n)$ ，因为假如存在最小的 $n$ 使得 $10^n\equiv10^{\varphi(x)}\equiv 1(\mod x)$，则 $10^{\varphi(x)\mod n}\equiv1(\mod x)$，显然 $\varphi(x)\mod n< n$，我们找到了一个更小的，所以假设不成立，命题得证。

我们只需要先求出 $\varphi(x)$ 再枚举他的因数进行判断即可，复杂度 $\mathcal{O}(\sqrt n \log n)$

# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
const int N=1e6;
int phi(int x){
	int ans=x,t=x;
	for(int i=2;i*i<=x;i++){	
		if(t%i!=0)continue;
		ans=ans/i*(i-1);
		while(t%i==0)t/=i;
	}
	if(t>1)ans=ans/t*(t-1);
	return ans;
}//求欧拉函数
int qw(int a,int b,int md){
	if(b==0)return 1;
	int res=qw(a,b/2,n);
	res=res*res%md;
	if(b%2==1)res=res*a%md;
	return res;
}
signed main(){
	int t=0;
	while(scanf("%lld",&n)){
		t++;
		if(n==0)return 0;
		int d=__gcd(8ll,n),ans=1e18;
		n=9*n/d;
		if(n%2==0||n%5==0){
			printf("Case %lld: 0\n",t);
			continue;
		}//答案不存在
		int x=phi(n);
		ans=x;
		for(int i=1;i*i<=x;i++){
			if(x%i!=0)continue;
			if(qw(10,i,n)%n==1)ans=min(ans,i);
			if(qw(10,x/i,n)%n==1)ans=min(ans,x/i);//枚举phi(x)的因子
		}
		if(ans==1e18)ans=0;
		printf("Case %lld: %lld\n",t,ans);
	}
	return 0;
}
```

---

## 作者：Expert_Dreamer (赞：1)

### 题意

给定 $L$，求 $\min\limits_{L\mid\dfrac{8}{9}(10^x-1)}\{x\}$。

### 题解

先推式子：

$$
L\mid\dfrac{8}{9}(10^x-1)
$$

$$9L\mid8(10^x-1)$$

$$\frac{9L}{\gcd(L,8)}\mid10^x-1$$

$$10^x\equiv1\pmod{\frac{9L}{\gcd(L,8)}}$$

根据小学二年级知识，若 $a,n$ 互质，则 $\varphi(n)\mid\left(\min\limits_{a^x\equiv1\pmod{n}}\{x\}\right)$。

证明可以用反证法。

所以只需求 $\varphi\left(\dfrac{9L}{\gcd(L,8)}\right)$，枚举其因数，判断是否满足条件即可，时间复杂度 $O(\sqrt{L}\log L)$。

---

## 作者：内拉组里 (赞：0)

一道数论~~水~~题 

不过洛谷数据有点水，可以去[HDU2462](https://acm.hdu.edu.cn/showproblem.php?pid=2462)试试 

# Thoughts :

> 题意 : 给定 $ L $ 求 $ L $ 的倍数 $ L' = 8888 \cdots 8888 $ 的最小长度，无解输出 $ 0 $ 。
>
> 易得 : $ L' = kL = \frac89(10^n - 1) $ 
>
> 将右式移项可得 $ \frac{9kL}8 = 10^n - 1 $ 
>
> 将左式化为最简真分数得到 $ \frac{9kL/\gcd(L,8)}{8/\gcd(L,8)} $ 
>
> 令 $ k' = \frac{k}{8/\gcd(L,8)} $，$ m = \frac{9L}{\gcd(L,8)} $ 
>
> 则原式化为 $ k'm = 10^n - 1 $ 
>
> 即 $ 10^n \equiv 1 \pmod m $ 

这里可以使用一个欧拉定理进行求解。

#### 欧拉定理

> 对于互质的正整数 $ a,n $ 有 $ a^{\varphi(n)} \equiv 1 \pmod n $ 
>
> 其中 $ \varphi(n) $ 为欧拉函数。

#### 欧拉函数

> 定义 : $ \varphi(n) $ 表示在 $ [1,n] $ 中与 $ n $ 互质的数的个数
>
> 性质 : 
>
> 1. 通项公式 : $ \varphi(n) = n\prod\limits^s_{i = 1}(1 - \frac1{p_i}) $ 
> 2. $ n = \sum\limits_{x|n}\varphi(x) $ 
> 3. 积性函数
>
>    - $ \varphi(1) = 1 $ 
>
>    - $ \varphi(p) = p - 1 $ &emsp;&emsp;&emsp; $ p $ 为素数 
>
>    - $ \varphi(ab) \varphi(\gcd (a,b)) = \varphi(a) \varphi(b) \gcd(a,b) $ 
>      - 特别地, 当 $ a, b $ 互质时,  $ \varphi(ab) = \varphi(a) \varphi(b) $ 
> 4. 欧拉定理

根据以上内容我们可以得到一个结论：

当 $ \gcd(10,m) \neq 1 $ 时, 数据无解；

否则一定有 $ n \le \varphi(m) $。

但显然 $ n = \varphi(m) $ 不一定是最优解，

故寻找 $ \varphi(m) $ 最小的因子 $ i $ 

使得 $ 10^i \equiv 1 \pmod m $ デス～

# Analyses :

> 单组时间复杂度 $ \Theta (\sqrt L) $ 
>
> 单组空间复杂度 $ \Theta (\log_2{L}) $ 

# Details :

1. **多测不清空, 爆零两行泪** 
2. 龟速幂请搭配龟速乘

# Code :

```cpp
#include	<algorithm>
#include	<iostream>
#include	<vector>
#define		int		long long
using namespace std;

int l, m, ans;
vector<int> fac;

void get_fac (int x)
{
	fac.clear();
	for (int i = 2; i * i <= x; i++)
	{
		while (x % i == 0)
		{
			x /= i;
			fac.push_back(i);
		}
	}
	if (x > 1) fac.push_back(x);
}

inline int phi (int x)
{
	int ans = x;
	for (int i = 2; i * i <= x; i++)
	{
		if (x % i == 0)
		{
			ans = ans / i * (i - 1);
			while (x % i == 0) x /= i;
		}
	}
	if (x > 1) ans = ans / x * (x - 1);
	return ans;
}

inline int mul (int x, int y)
{
	int ans = 0;
	while (y)
	{
		if (y & 1) ans = (ans + x) % m;
		y >>= 1;
		x = (x + x) % m;
	}
	return ans;
}

inline int qpow (int x, int y)
{
	int ans = 1;
	while (y)
	{
		if (y & 1) ans = mul (ans, x);
		y >>= 1;
		x = mul (x, x);
	}
	return ans;
}

signed main (void)
{
	for (int i = 1; i; i++)
	{
		cin >> l;
		if (!l) return 0;
		printf ("Case %lld: ", i);
		m = l / __gcd (l, 8ll) * 9;
		if (__gcd (m, 10ll) != 1) cout << 0 << endl;
		else
		{
			int ans = phi (m);
			get_fac (ans);
			for (auto i : fac)
			{
				if (qpow (10, ans / i) == 1)
					ans /= i;
			}
			cout << ans << endl;
		}
	}
	return 0;
}
```

---

## 作者：wflhx2011 (赞：0)

## Solution

是 $L$ 的倍数，即对 $L$ 取余的模数为 $0$。

于是问题出在仅由数字 $8$ 构成，考虑将其换一种形式表示，不难发现 $88......88=8 \times 11......11=8 \times \frac{10^n-1}{9}$。原问题就变为求一个最小的正整数 $n$ 使  $8\times\frac{10^n-1}{9} \bmod L=0$。

出现乘方，考虑用欧拉定理，先对原式进行变形，可化为 $10^n \equiv 1 \pmod {\frac{9\times L}{\gcd(8,L)}}$。

欧拉定理：若 $a,p$ 互质，则 $a^{\phi(p)} \equiv 1 \pmod p$。于是考虑，使 $a^n \equiv 1 \pmod p$ 最小的 $n$ 是否与 $\phi(p)$ 有关系呢？

一个较为显然的思路是 $n$ 是 $\phi(p)$ 的因数，这样 $a^{\phi(p)}=a^{n^{\phi(p)/n}}$，在模 $p$ 意义下就是 $1=1^{\phi(p)/n}$。

那能否对此进行严谨证明呢？

证明（以下内容摘自李煜东《算法竞赛进阶指南》）：

反证法。假设满足 $a^n \equiv 1 \pmod p$ 的最小正整数 $n$ 不能整除 $\phi(p)$。

设 $\phi(p)=q \times n+r (0<r<n)$，因为 $a^n \equiv 1 \pmod p$，所以 $a^{q \times n} \equiv 1 \pmod p$。根据欧拉定理，$a^{\phi(p)} \equiv 1 \pmod p$，则 $a^r \equiv 1 \pmod p$。因为 $r<n$，这与 $n$ 为最小正整数解矛盾。故假设不成立，原命题成立。

证毕。

回到原题，设 $p={\frac{9\times L}{\gcd(8,L)}}$，我们就可以求出 $\phi(p)$，之后暴力枚举因数。

无解的情况显然是 $10,p$ 不互质，但也不需要特判。

值得注意的是，快速幂模数有可能很大，导致在过程中爆  long long，虽然本题数据水也能卡过去，但建议使用更大的数据类型。

时间复杂度对于一组数据是 $O(\sqrt n \log n)$。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long euler(long long n)
{
	long long ans=n;
	for(int i=2;i*i<=n;i++)
	{
		if(n%i==0)
		{
			ans=ans/i*(i-1);
			while(n%i==0)
				n/=i;
		}
	}
	if(n>1)
		ans=ans/n*(n-1);
	return ans;
}
__int128 ksm(__int128 a,__int128 b,__int128 mo)
{
	__int128 res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mo;
		a=a*a%mo;
		b>>=1;
	}
	return res%mo;
}
int tot;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long l;
	while(cin>>l&&l)
	{
		long long ans=1e18; 
		long long d=9*l/__gcd(l,8ll);
		long long k=euler(d);
		for(long long i=1;i*i<=k;i++)
		{
			if(k%i==0)
			{
				__int128 f=ksm(10,i,d);
				if(f%d==1)
					ans=min(ans,i);
			}
			if(k%(k/i)==0)
			{
				__int128 f=ksm(10,k/i,d);
				if(f%d==1)
					ans=min(ans,k/i);
			}	
		}
		printf("Case %d: %d\n",++tot,ans==1e18?0:ans);
	}
	return 0;
}
```

---

## 作者：block_in_mc (赞：0)

## 解题思路

由 $x$ 个 $8$ 构成的正整数为 $\dfrac{8\times(10^x-1)}{9}$，答案即为满足 $L\mid\dfrac{8\times(10^x-1)}{9}$ 的最小正整数 $x$，即

$$9L\mid8\times(10^x-1)$$

设 $d=\gcd(L,8)$，则有

$$\dfrac{9L}{d}\mid10^x-1$$

为什么呢？先考虑 $d=1$ 即 $L$ 与 $8$ 互质的情况，这时右侧的 $8$ 对这个 $9L$ 能被 $8\times(10^x-1)$ 整除没有贡献，因此可以直接删去。一般地，右侧的 $8$ 对这个式子做出了 $d$ 的贡献，因此想要删除右侧的 $8$，左侧要除以 $d$。

将其转化为同余方程即

$$10^x-1\equiv0\pmod{\dfrac{9L}{d}}$$

即

$$10^x\equiv1\pmod{\dfrac{9L}{d}}$$

只需找到满足这个式子的最小的正整数 $x$ 即可。

> 先证明一个引理：若正整数 $a,n$ 互质，则满足 $a^x\equiv1\pmod{n}$ 的最小正整数 $x_0$ 是 $\varphi(n)$ 的约数。
>
> 考虑反证法。假设满足 $a^x\equiv1\pmod{n}$ 的最小正整数 $x_0$ 不是 $\varphi(n)$ 的约数，则 $x_0$ 可以表示为 $qx_0+r$ 的形式，其中 $0<r<x_0$。
> 
> 由于 $1^q=1$，可以推出
> 
> $$(a^x)^q\equiv1\pmod{n}$$
> 
> 根据欧拉定理，又有
> 
> $$a^{\varphi(n)}\equiv1\pmod{n}$$
> 
> 两式相除可以得到
> 
> $$a^r\equiv1\pmod{n}$$
> 
> 由于 $r<x_0$，与 $x_0$ 的最小性矛盾，结论成立。

因此，我们可以从小到大枚举 $\dfrac{9L}{d}$ 的每一个因数 $x$，并通过快速幂计算 $10^x\bmod\dfrac{9L}{d}$ 的值是否为 $1$ 判断 $x$ 是否合法。

需要注意的是，$\dfrac{9L}{d}$ 可能超出 `int` 范围，计算快速幂时需要使用 `__int128`。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k, phi, ans;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll fpow(ll a, ll b, ll p) {
	if (b <= 0) return 1;
	ll tmp = fpow(a, b / 2, p);
	if (b % 2 == 0) return (ll) (((__int128) tmp * tmp) % p);
	else return (ll) (((__int128) a * tmp * tmp) % p);
}
void calc(ll p) {
	phi = p;
	for (int i = 2; i * i <= p; i++) {
		if (p % i == 0) {
			while (p % i == 0) p /= i;
			phi = phi * (i - 1) / i;
		}
	}
	if (p != 1) phi = phi * (p - 1) / p;
}
int main() {
	for (int id = 1; ; id++) {
		scanf("%lld", &n);
		if (n == 0) break;
		k = n / gcd(8, n) * 9, ans = 0;
		calc(k);
		for (ll i = 1; i * i <= phi; i++)
			if (ans == 0 && phi % i == 0 && fpow(10, i, k) == 1)
				ans = i;
		ll m = sqrt(phi);
		for (ll i = m; i >= 1; i--) 
			if (ans == 0 && phi % i == 0 && fpow(10, phi / i, k) == 1)
				ans = phi / i;
		printf("Case %d: %lld\n", id, ans);
	}
    return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：0)

一道欧拉定理的好题。

### 题意

询问至少多少个 $8$ 组成的正整数是 $L$ 的倍数。

### 分析

对于 $n$ 个 $8$ 组成的正整数，这个幸运数就是 $\sum\limits_{i=0}^{n-1}8 \times 10^{i} = 8 \times \frac{10^{n}-1}{9}$。

因为幸运数是 $L$ 的倍数，所以 $L \mid 8 \times \frac{10^{n}-1}{9}$。

不难得到 $9L \mid 8 \times (10^{n}-1)$。

设 $d= \gcd(L,8)$。

所以 $\frac{9L}{d} \mid 10^{n}-1$。

改为模算术式子 $10^{n}\equiv1\pmod{\frac{9L}{d}}$。

由欧拉定理的推论得到 $n$ 是 $\varphi(\frac{9L}{d})$ 的约数。

所以我们现在只需要筛出 $\varphi(\frac{9L}{d})$ 的所有约数，挨个判断是否符合 $10^{i} \bmod \frac{9L}{d} = 1$ 即可。

### 代码

我们在代码中设 $dex= \frac{9L}{d}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define ls ((now<<1))
#define rs ((now<<1)|1)
#define mid ((l+r)>>1)
const int maxn=1e6+10;
const int inf=1e9;
const int maxa=2e3+10;
int ksm(int a,int b,int modd){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%modd;
		a=a*a%modd;b>>=1;
	}
	return ans;
}
int phi(int n){
	int ans=n;
	for(int i=2;i<=sqrt(n);i++){
		if(n%i==0){
			ans=ans/i*(i-1);
			while(n%i==0)n/=i;
		}
	}
	if(n>1)ans=ans/n*(n-1);
	return ans;
}
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int L,ans=inf,dex;
signed main(){
	int id=0;
	while(cin >> L){
        id++;ans=inf;
		if(L==0)return 0;	
		int d=gcd(8,L);
		dex=9*L/d;
		if(dex%2==0||dex%5==0){
			cout << "Case " << id << ": 0" << endl;
			continue;
		}
		int x=phi(dex);
		ans=x;
		for(int i=1;i<=sqrt(x);i++){
			if(x%i!=0)continue;
			if(ksm(10,i,dex)%dex==1)ans=min(ans,i);
			if(ksm(10,x/i,dex)%dex==1)ans=min(ans,x/i);
		}
		if(ans==inf)ans=0;
		cout << "Case " << id <<": " << ans <<endl;
	}
	return 0;
}
```

---

