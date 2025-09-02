# [ARC158D] Equation

## 题目描述

给定正整数 $n$ 和一个不小于 $5$ 的素数 $p$。

请你找到一组整数 $(x, y, z)$，满足以下所有条件：

- $1 \leq x < y < z \leq p - 1$。
- $(x+y+z)(x^n+y^n+z^n)(x^{2n}+y^{2n}+z^{2n}) \equiv x^{3n}+y^{3n}+z^{3n} \pmod{p}$。

可以证明，总是存在满足条件的三元组 $(x, y, z)$。

有 $T$ 组测试数据，请分别给出每组的答案。

## 说明/提示

### 数据范围

- $1 \leq T \leq 10^5$
- $1 \leq n \leq 10^9$
- $p$ 是满足 $5 \leq p \leq 10^9$ 的素数

### 样例解释 1

对于第一组测试数据：

- $(x+y+z)(x^n+y^n+z^n)(x^{2n}+y^{2n}+z^{2n}) = (1+4+6)(1+4+6)(1+16+36) = 6413$
- $x^{3n}+y^{3n}+z^{3n} = 1 + 64 + 216 = 281$

由于 $6413 \equiv 281 \pmod{7}$，所以满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 7
2 7
10 998244353```

### 输出

```
1 4 6
1 2 5
20380119 21549656 279594297```

# 题解

## 作者：PrincessQi (赞：31)

随机 $x,y,z$，取 $t$ 满足

$$(x+y+z)(x^{n}+y^{n}+z^{n})(x^{2n}+y^{2n}+z^{2n})\equiv t(x^{3n}+y^{3n}+z^{3n})$$

则有

$$(\frac xt+\frac yt+\frac zt)((\frac xt)^{n}+(\frac yt)^{n}+(\frac zt)^{n})((\frac xt)^{2n}+(\frac yt)^{2n}+(\frac zt)^{2n})\equiv ((\frac xt)^{3n}+(\frac yt)^{3n}+(\frac zt)^{3n})$$

如果因为各种意外情况导致上面的东西出现问题（比如 $x=y$ 或者某一项是 $0$），好的办法是多随几次。

---

## 作者：Leasier (赞：7)

下面 $x, y, z$ 无序。

首先是赛时想法：

- 打表发现一定存在一组解使得 $x + y = p$。
- 当 $n$ 为偶数，设 $r = \frac{x}{z}$，则 $z = \frac{2r^{3n} + 1}{(2r^n + 1)(2r^{2n} + 1)}$；当 $n$ 为奇数，同样设 $r = \frac{x}{z}$，则 $z = \frac{1}{2r^{2n} + 1}$。
- 随机化 $r$ 直到解合法即可。

现在我们来考虑如何不随机化。

1. $n$ 为奇数

考虑钦定 $r = 2$，但是你会发现有时候 $2^{2n} \equiv -\frac{1}{2} \pmod p$ 导致无解。

考虑在无解时改 $r = 2$ 为 $r = 4$，由于 $4^{2n} \equiv \frac{1}{4} \not\equiv -\frac{1}{2} \equiv 2^{2n} \pmod p$，则此时一定有解。

2. $n$ 为偶数

首先给出结论：

- 首先判掉 $p = 5, 11$ 的情况。
- 令 $r = 2$，每次按照前述方法求出对应的 $x, y, z$，如果解不合法则令 $r \leftarrow r^2$ 并继续。
- 可以证明一定有解，且尝试的 $r$ 的个数 $\leq 3$。

证明：首先，失败只可能有两种情况 $z$ 的某个分子或分母为 $0$ 或 $r = p - 1$。

对于第二种情况，由于 $r$ 可以表示成 $2^{2^k}$ 的形式，则 $p$ 此时只可能为费马质数。对三个需要检验的费马质数 $17, 257, 65537$ 进行了验证，均满足上述条件。

对于第一种情况，考虑在失败时分类讨论 $2r^n + 1, 2r^{2n} + 1, 2r^{3n} + 1$ 中哪个为 $0$。下面设 $r' = r^2$。

- $2r^n + 1 = 0$

于是有 $(r')^n \equiv \frac{1}{4} \pmod p$，则 $2(r')^n + 1 \equiv \frac{3}{2} \not\equiv 0 \pmod p$，$2(r')^{2n} + 1 \equiv \frac{5}{4} \not\equiv 0 \pmod p$（注意我们判掉了 $p = 5$），$2(r')^{3n} + 1 \equiv \frac{33}{32} \not\equiv 0 \pmod p$（注意我们判掉了 $p = 11$）。于是自乘一次后一定合法。

- $2r^{2n} + 1 = 0$

于是有 $(r')^{2n} \equiv \frac{1}{4} \pmod p$，则 $2(r')^{2n} + 1 \equiv \frac{3}{2} \not\equiv 0 \pmod p$；因为 $(r')^n \equiv \pm \frac{1}{2} \pmod p$，则 $2(r')^n + 1 \equiv 0 \operatorname{or} 2 \pmod p$，$2(r')^{3n} + 1 \equiv \frac{3}{4} \operatorname{or} \frac{5}{4} \not\equiv 0 \pmod p$。于是自乘一次后要么合法，要么转化为 $2r^n + 1 = 0$ 的情况。

- $2r^{3n} + 1 = 0$

于是有 $(r')^{3n} \equiv \frac{1}{4} \pmod p$，则 $2(r')^{3n} + 1 \equiv \frac{3}{2} \not\equiv 0 \pmod p$；假定 $(r')^n = -\frac{1}{2}$，则 $(r')^{3n} \equiv -\frac{1}{8} \not\equiv \frac{1}{4} \pmod p$；假定 $(r')^{2n} = -\frac{1}{2}$，则 $(r')^{6n} \equiv -\frac{1}{8} \not\equiv \frac{1}{16} \pmod p$。于是自乘一次后一定合法。

综上，把 $n$ 分别为奇数和偶数的两种情况拼起来即可。

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll ans[7];

inline ll quick_pow(ll x, ll p, ll mod){
    ll ans = 1;
    while (p){
        if (p & 1) ans = ans * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return ans;
}

inline bool check(){
    sort(ans + 1, ans + 4);
    return ans[1] != ans[2] && ans[2] != ans[3];
}

int main(){
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++){
        int n, p;
        cin >> n >> p;
        n %= p - 1;
        if (n % 2 == 0){
        	if (p == 5 || p == 11){
        		for (int j = 2; ; j++){
        			ans[1] = (quick_pow(j, (ll)n * 3, p) * 2 % p + 1) % p * quick_pow((quick_pow(j, n, p) * 2 % p + 1) % p * (quick_pow(j, n * 2, p) * 2 % p + 1) % p, p - 2, p) % p;
                	ans[2] = ans[1] * j % p;
                	ans[3] = p - ans[2];
                	if (check()) break;
				}
			} else {
				ll r = 2;
	            do {
	                ans[1] = (quick_pow(r, (ll)n * 3, p) * 2 % p + 1) % p * quick_pow((quick_pow(r, n, p) * 2 % p + 1) % p * (quick_pow(r, n * 2, p) * 2 % p + 1) % p, p - 2, p) % p;
	                ans[2] = ans[1] * r % p;
	                ans[3] = p - ans[2];
	                r = r * r % p;
	            } while (!check());
			}
        } else {
            ans[1] = quick_pow((quick_pow(2, n * 2, p) * 2 % p + 1) % p, p - 2, p);
            if (ans[1] == 0){
                ans[1] = quick_pow((quick_pow(4, n * 2, p) * 2 % p + 1) % p, p - 2, p);
                ans[2] = ans[1] * 4 % p;
            } else {
                ans[2] = ans[1] * 2 % p;
            }
            ans[3] = p - ans[2];
            check();
        }
        for (int j = 1; j <= 3; j++){
            cout << ans[j] << " ";
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：云浅知处 (赞：5)

**注意到等式两边都是齐次的，且次数恰好差 $1$。**

记左边是 $F(x,y,z)$，右边是 $G(x,y,z)$。

那么如果我们随一组 $x,y,z$，发现 $F(x,y,z)=tG(x,y,z)$，那么就有 

$$
F(x/t,y/t,z/t)=G(x/t,y/t,z/t)
$$
因此只要能随到一组 $x,y,z$ 使得 $G(x,y,z)$ 存在逆元，且 $F(x,y,z)\neq 0$ 即可。

注意 $p$ 是素数，因此只需要 $G(x,y,z)\neq 0$。这个概率是相当大的，[官方题解](https://atcoder.jp/contests/arc158/editorial/5983)证得概率至少为 $\frac{3}{4}$，从而期望步数为 $\frac{5}{3}$。

时间复杂度 $O(T\log n)$，$\log$ 来自快速幂。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

int mod=1e9+7;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

int n,p;
int F(int x,int y,int z){
	int xn=ksm(x,n),yn=ksm(y,n),zn=ksm(z,n);
	return (x+y+z)*(xn+yn+zn)%p*(xn*xn%p+yn*yn%p+zn*zn%p)%p;
}
int G(int x,int y,int z){
	return (ksm(x,3*n)+ksm(y,3*n)+ksm(z,3*n))%p;
}

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	int tt=read();while(tt--){
		n=read(),p=read();mod=p;
		int x=randint(1,p-1),y=randint(1,p-1),z=randint(1,p-1);
		do{x=randint(1,p-1),y=randint(1,p-1),z=randint(1,p-1);}while(x==y||y==z||z==x||F(x,y,z)==0||G(x,y,z)==0);
		int t=G(x,y,z)*inv(F(x,y,z))%p;
		x=x*t%p,y=y*t%p,z=z*t%p;
		if(x>y)swap(x,y);
		if(x>z)swap(x,z);
		if(y>z)swap(y,z);
		cout<<x<<" "<<y<<" "<<z<<endl;
	}

	return 0;
}

```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc158_d)

**题目大意**

> $T$ 次询问给定 $n,p$，构造 $(x,y,z)$ 使得：
> $$
> (x+y+z)(x^n+y^n+z^n)(x^{2n}+y^{2n}+z^{2n})\equiv x^{3n}+y^{3n}+z^{3n} \pmod p
> $$
> 数据范围：$n,p\le 10^9,p\ge 5$。

**思路分析**

注意到左右均为齐次多项式，那么我们假设 $\mathrm{LHS}=k\times \mathrm{RHS}$，那么取 $\left(\dfrac xk,\dfrac yk,\dfrac zk\right)$ 就能满足题意。

不断随机 $x,y,z$ 直到 $x\ne y\ne z,\mathrm{LHS}\ne 0,\mathrm{RHS}\ne 0$。

感性理解不合法的 $x,y,z$ 远小于 $\mathcal O(p^3)$ 量级，应该期望 $\mathcal O(1)$ 此操作就能得到解（可以证明成功率 $\ge 75\%$）。

时间复杂度 $\mathcal O(T\log p)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,p;
ll ksm(ll a,ll b=p-2) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
mt19937 R(135);
int rnd(int l,int r) { return R()%(r-l+1)+l; }
ll F(ll x,ll y,ll z) {
	return (x+y+z)%p*(ksm(x,n)+ksm(y,n)+ksm(z,n))%p*(ksm(x,2*n)+ksm(y,2*n)+ksm(z,2*n))%p;
}
ll G(ll x,ll y,ll z) {
	return (ksm(x,3*n)+ksm(y,3*n)+ksm(z,3*n))%p;
}
void solve() {
	ll x,y,z,f,g;
	scanf("%lld%lld",&n,&p);
	do x=rnd(1,p-1),y=rnd(1,p-1),z=rnd(1,p-1),f=F(x,y,z),g=G(x,y,z);
	while(!f||!g||x==y||y==z||z==x);
	f=ksm(f)*g%p,x=x*f%p,y=y*f%p,z=z*f%p;
	array<ll,3>q={x,y,z}; sort(q.begin(),q.end());
	printf("%lld %lld %lld\n",q[0],q[1],q[2]);
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：洛浔 (赞：1)

## hint
注意到两边的式子是齐次的，并且两边的次数相差 $1$。

## sol

首先我们将 $x$ 设为主元，随机 $a$ 和 $b$，令 $y \equiv  a\times x \pmod{p}$，$z \equiv  b\times x \pmod{p}$。

然后将 $y$ 和 $z$ 代入原式，展开。会得到一个 $u\times x^{3\times n +1}\pmod{p} = v\times x^{3\times n}\pmod{p}$ 的形式，移项求解即可。

得出 $x$ 之后需要排序和判断解的合法性。如果不合法就再随一组 $a,b$。

可以证明每次随机化的正确率在 $\frac{1}{4}$ 左右。

[EN](https://atcoder.jp/contests/arc158/editorial/5983)，[JP](https://atcoder.jp/contests/arc158/editorial/5905)。日语允许的化建议阅读日语证明。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int quick_pow(int a,int b,int mod){
    int ret=1;
    for(;b;b>>=1,a=a*a%mod)
    if(b&1) ret=ret*a%mod;
    return ret;
}
int getl(int a,int b,int n,int p){
    int A=quick_pow(a,n,p),B=quick_pow(b,n,p);
    return (a+b+1)*(A+B+1)%p*(A*A%p+B*B%p+1)%p;
}
int getr(int a, int b, int n,int p) {
    int A = quick_pow(a, n*3, p), B = quick_pow(b, n*3, p);
    return (A+B+1)%p;
}
void work(){
    int n,p;
    cin>>n>>p;
    mt19937 srand(time(0));
    int s[5];
    while(1){
        int a=rand()%p,b=rand()%p;
        int L=getl(a,b,n,p);
        int R=getr(a,b,n,p);
        s[0]=R*quick_pow(L,p-2,p)%p;
        s[1]=s[0]*a%p,s[2]=s[0]*b%p;
        sort(s,s+3);
        if(s[0]!=s[1]&&s[2]!=s[1]&&s[0]!=s[2]){
            if(s[0]&&s[1]&&s[2]){
                cout<<s[0]<<" "<<s[1]<<" "<<s[2]<<endl;
                return ;
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)
        work();
    return 0;
}
```

---

