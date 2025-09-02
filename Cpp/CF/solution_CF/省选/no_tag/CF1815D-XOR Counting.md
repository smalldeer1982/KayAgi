# XOR Counting

## 题目描述

记 $\bigoplus$ 表示按位异或运算。  
给定整数 $n,m$。  
记一个序列 $a$ 是好的，当且仅当它是一个长度为 $m$ 的非负整数序列，且其元素之和恰好为 $n$。  
求在好的序列 $a$ 中，$\bigoplus_{i=1}^ma_i$ 的所有可能取值之和对 $998244353$ 取模后的值。  
**对于一个 $\bm{\bigoplus_{i=1}^ma_i}$ 的可能取值，无论有多少个可以取得这个值的好的序列 $\bm{a}$，这个值都应只被计入所求之和一次。**    
每个测试点包含 $t$ 组数据。

## 样例 #1

### 输入

```
7
69 1
5 2
0 10
420 69
12 26
73 34
1000000000000000000 10```

### 输出

```
69
6
0
44310
42
1369
216734648```

# 题解

## 作者：SkyRainWind (赞：8)

**UPD：更新了一个错误，感谢指出**

[更好的阅读体验](https://www.cnblogs.com/SkyRainWind/p/17322823.html)

一道有趣的题。

首先发现 $m=1$ 和 $m\geq 3$ 时结论是平凡的。$m=1$ 时结论显然，下面讨论一下 $m\geq 3$ 时：

首先可以构造 $[x, (n-x)/2, (n-x)/2, \cdots]$，其中 $x$ 和 $n$ 同奇偶，显然此时异或值可以取到 $1\cdots n$ 的所有和 $n$ 奇偶性相同的值。另一方面，一个重要观察是 $a_1 \oplus \cdots \oplus a_n$ 的奇偶性和 $a_1+\cdots+a_n$ 相同，因此异或值至多取到所有和 $n$ 奇偶性相同的值。因此这块可以 $O(1)$ 求出。

下面我们讨论一下 $m=2$ 的情况。
设 $f_n$ 表示 $a_1+a_2=n$ 时的答案，考虑分治：
如果 $n$ 为奇数，那么 $a_1, a_2$ 一奇一偶，不失一般性设 $a_1, a_2$ 分别为奇数 偶数，如果令 $b_1=(a_1-1)/2, b_2=a_2/2$，那么 $b_1+b_2=(n-1)/2, a_1\oplus a_2=2\times(b_1\oplus b_2)+1$，因此我们还需要记一个 $g_n$ 表示有多少种不同的异或值（因为这个 +1 是对于所有不同的异或值都要算的），$g_n$ 此时的转移也很简单。综上我们有 $n$ 为奇数时 $f_n=2\times f_{n/2-1}+g_{n}$ 以及 $g_n=g_{(n-1)/2}$
如果 $n$ 为偶数，那么 $a_1, a_2$ 要么都是奇数，要么都是偶数，还是考虑分治，此时由于 $n$ 奇数，所以没有 $+1$ 的项，因此和上一种情况完全相同的推导我们有 $f_n=2\times (f_{n/2}+f_{n/2-1})$ 以及 $g_n=g_{n/2}+g_{n/2-1}$。

直接递推实现即可，复杂度 $O(\log n)$。

代码：
```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define pii pair<int,int>
#define pb push_back

using namespace std;

typedef long long ll;
typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f, mod = 998244353;

map<ll,ll>f,g;
void solve(ll n){
	if(n == 0){
		f[n] = 0, g[n] = 1;
		return ;
	}
	if(f.count(n))return ;
	if(n%2 == 1){
		solve(n/2);
		(f[n] = 2ll*f[n/2]%mod + g[n/2])%=mod;
		g[n] = g[n/2];
	}else{
		solve(n/2);solve(n/2-1);
		f[n] = 2ll * (f[n/2] + f[n/2-1]) % mod;
		g[n] = (g[n/2] + g[n/2-1]) % mod;
	}
}

signed main(){
	int te;scanf("%d",&te);
	while(te --){
		f.clear(), g.clear();
		ll n,m;cin >> n >> m;
		if(m == 1){
			cout << n%mod << '\n';
		}else if(m >= 3){
			if(n%2 == 1)cout << (n+1)/2%mod*((n+1)/2%mod)%mod << '\n';
			else cout << (1+n/2%mod)*(n/2%mod) % mod << '\n';
		}else{
			solve(n);
			cout << f[n] << '\n';
		}
	}

	return 0;
}
```

---

## 作者：Nuisdete (赞：7)

首先我们需要观察到一个性质，那就是当 $m > 2$ 时，答案是特殊的。

具体的，我们可以将 $n$ 分解为 $x, \frac{n - x}{2}, \frac{n - x}{2}, 0, 0, 0, \cdots$ 。

不难发现，此时我们可以取到所有与 $n$ 奇偶性相同的异或值 $x$，并且我们还可以证明所有与 $n$ 奇偶性不同的异或值是取不到的。

具体的，加法的奇偶性和 $\operatorname{xor}$ 运算的奇偶性相同，因此，对于和为偶数的 $a_1, a_2, a_3, \cdots$ 它们的异或值也必为偶数，奇数情况同理。

$m = 1$ 的答案也是简单的，因此问题就变为了求非负整数对 $(a, b)$ 满足 $a + b = n$ 且 $a \operatorname{xor} b$ 的值两两不同的 $a \operatorname{xor} b$ 的和。

二进制运算是位位独立的，因此我们考虑按位填 $a + b$ 。

设 $g_{i,0/1}$ 表示第 $i$ 位是否向后进位，填了前 $i$ 位的方案数，$f_{i, 0/1}$ 表示答案。

因此我们分别按照 $n$ 的第 $i$ 位为 $0/1$ 分别转移即可，方程比较简单。

注意开 `long long` 和求的是 $a \operatorname{xor} b $ 的和不是 $a + b$ 的和。

Code：[https://codeforc.es/problemset/submission/1815/202145783](https://codeforc.es/problemset/submission/1815/202145783)。

---

## 作者：EXODUS (赞：5)

# Part 1：前言
上来看到觉得这个题一脸无敌，然后看了题解恍然大悟。感觉自己还是只有类人智慧。

# Part 2：正文

上来感觉这个题不能做，那么我们考虑从序列长度入手分析题目性质。

首先对于 $m=1$ 的情况是平凡的，那么这个数字只能填 $n$，故答案为 $n$。

接下来我们试图说明，对于 $m\ge 3$ 的情况与 $m=3$ 的情况是等价的。

注意到我们在任意一个合法序列后补若干个 $0$ 对答案是不造成影响的，因为 $x\oplus 0=x$，那么也就是说，我们只需要说明 $m=3$ 可以构造出足够多的解，使得增加任意多个空位均不会影响到答案。

首先，我们构造一个整数序列 $a,b,b$，满足 $a+b+b=n$，那么此时即有异或值 $a$。不难发现此时序列合法的充要条件是 $a$ 与 $n$ 同奇偶，那么我们现在即能说明对于 $m=3$，我们可以取到与 $n$ 同奇偶的情况。

然后，对于一个序列，考虑其二进制下最后一位 $1$ 的个数的奇偶性一定与 $n$ 的奇偶性相同，故异或值奇偶性一定与 $n$ 相同。

综上，$m\ge 3$ 的情况与 $m=3$ 的情况是等价的。


那么现在问题就简单的变成了 $m=2$ 的情况。

考虑此时应当怎么把 $n$ 划分成两个数，按位考虑异或值。令 $f(n)$ 表示所有可能异或的和，$g(n)$ 表示不同异或值的个数。若 $n$ 为奇数，我们考虑到该位的异或值一定是 $1$，剩下的本质上是一个去掉最后一位 $1$ 的子问题，那么有 $f(n)=2f(\dfrac{n}{2})+1,g(n)=g(\dfrac{n}{2})$。若 $n$ 为偶数，分类讨论是划分成两个奇数还是两个偶数，那么转移为 $f(n)=2f(\dfrac{n}{2})+2f(\dfrac{n}{2}-1),g(n)=g(\dfrac{n}{2})+g(\dfrac{n}{2}-1)$。


但是有一个问题是复杂度的分析，注意到第一类的复杂度是自然的 $O(\log n)$，但第二类需要一点思考。考虑到 $\dfrac{n}{2}$ 和 $\dfrac{n}{2}-1$ 有一个为奇数，若为前者则与下一层中 $\dfrac{\dfrac{n}{2}-1}{2}$ 的递归等同，若为后者则与下一层中 $\dfrac{n}{4}-1$ 的递归等同，故不影响时间复杂度为 $O(\log n)$ 的分析。

总时间复杂度为 $O(T\log n)$，当然使用 map 记忆化会多 $O(\log (T\log n))$ 的复杂度。


# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int mod=998244353;
int T,m,ans=0;

unordered_map<ll,int>f,g;

void add(int &x,int y){x+=y-mod,x+=x>>31&mod;}

void solve(ll n){
	if(f.count(n))return;
	if(!n)return f[n]=0,g[n]=1,void();
	ll suf=0;
	if(n&1)solve(suf=(n>>1)),add(f[n]=f[suf]*2%mod,g[suf]),g[n]=g[suf];
	else solve(suf=(n>>1)),solve(suf-1),add(f[n]=f[suf],f[suf-1]),add(f[n],f[n]),add(g[n]=g[suf],g[suf-1]);
}

ll n;

void solve(){
	read(n,m);
	if(m==1)ans=n%mod;
	else if(m>=3)ans=(n&1)?((__int128)(n+1)*((n-1)/2+1)/2)%mod:((__int128)(n+2)*((n-2)/2+1)/2)%mod;
	else if(m==2)solve(n),ans=f[n];
	printf("%d\n",ans);
}

int main(){
	read(T);
	while(T--)solve();
	return 0;
}
```



---

## 作者：honglan0301 (赞：3)

## 题目分析

[题目传送门](https://www.luogu.com.cn/problem/CF1815D)。感觉这个想法挺自然的。

$m=1$ 的答案显然是 $n$，因为只有一种放法。其余情况首先我们感性理解 $m$ 比较大的时候一定是诈骗（因为限制太少了），事实上也确实好发现可以随便找出两个位置填相等的数，让第三个位置填剩下的数，这样能使得异或和成为任意一个 $\equiv n\pmod 2$ 的数。并且可以发现不可能异或出与 $n$ 奇偶性不同的数，所以 $m>2$ 时的答案就是所有 $\leq n$ 且与 $n$ 奇偶性相同的数的和，即：

$$ans=\left \{
\begin{aligned}
& \frac{(n+1)^2}{4}\ \ \ (n\equiv 1\pmod 2)\\
& \frac{n(n+2)}{4}\ \ \ (n\equiv 0\pmod 2)\\
\end{aligned}
\right.
$$

于是下面我们只需考虑 $m=2$ 的情况，即 $a+b$ 固定时求 $a\bigoplus b$ 的所有可能值之和。考虑类似数位 $\text{dp}$ 的过程，从高位往低位填数，注意到每一位至多会给下一位留下 $1$，原因是 $2\sum\limits_{i=0}^{i}2^i<2\cdot2^{i+1}$，于是分别从高向低和从低向高地 $dp$ 一下，$f_{i,0/1}$ 表示第 $i$ 位是否给下一位留数时低位能填出多少种异或值，$g_{i,0/1}$ 表示高位能填出多少种异或值。那么有显然的转移是：

$$\left \{
\begin{aligned}
& f_{i,0}=f_{i-1,0}+f_{i-1,1},f_{i,1}=f_{i-1,1}\ \ \ (n\And 2^{i-1}=2^{i-1})\\
& f_{i,0}=f_{i-1,0},f_{i,1}=f_{i-1,0}+f_{i-1,1}\ \ \ (n\And 2^{i-1}=0)\\
\end{aligned}
\right.
$$

$$\left \{
\begin{aligned}
& g_{i,0}=g_{i+1,0},g_{i,1}=g_{i+1,0}+g_{i+1,1}\ \ \ (n\And 2^{i}=2^{i})\\
& g_{i,0}=g_{i+1,0}+g_{i+1,1},g_{i,1}=g_{i+1,1}\ \ \ (n\And 2^{i}=0)\\
\end{aligned}
\right.
$$

此时再考虑每一位的贡献，容易发现有：

$$ans\leftarrow ans+\left \{
\begin{aligned}
& 2^i\times f_{i,0}\times g_{i+1,0}\ \ \ (n\And 2^{i}=2^{i})\\
& 2^i\times f_{i,1}\times g_{i+1,1}\ \ \ (n\And 2^{i}=0)\\
\end{aligned}
\right.
$$

故直接计算即可，时间复杂度 $O(T\log n)$，可以通过。

## 代码

```cpp
/*
  author: PEKKA_l  
 */
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
#define mod 998244353

int t,n,m,f[65][2],g[65][2],cf[65],ans;

signed main()
{
	cin>>t; cf[0]=1; for(int i=1;i<=62;i++) cf[i]=cf[i-1]*2;
	while(t--)
	{
		cin>>n>>m; ans=0;
		if(m==1) {cout<<n%mod<<endl; continue;}
		else if(m>2)
		{
			if(n&1) {cout<<((n+1)/2%mod)*((n+1)/2%mod)%mod<<endl; continue;}
			else {cout<<(n/2%mod)*((n+2)/2%mod)%mod<<endl; continue;}
		}
		f[0][0]=1,f[0][1]=0;
		for(int i=1;i<=60;i++)
		{
			if(n&cf[i-1]) {f[i][0]=(f[i-1][0]+f[i-1][1])%mod; f[i][1]=f[i-1][1];}
			else {f[i][0]=f[i-1][0]; f[i][1]=(f[i-1][0]+f[i-1][1])%mod;}
		}
		g[60][0]=1; g[60][1]=0;
		for(int i=59;i>=0;i--)
		{
			if(n&cf[i]) {g[i][0]=g[i+1][0]; g[i][1]=(g[i+1][0]+g[i+1][1])%mod;}
			else {g[i][0]=(g[i+1][0]+g[i+1][1])%mod; g[i][1]=g[i+1][1]%mod;}
		}
		for(int i=0;i<=59;i++)
		{	
			if(n&cf[i]) ans+=cf[i]%mod*f[i][0]%mod*g[i+1][0]%mod;
			else ans+=cf[i]%mod*f[i][1]%mod*g[i+1][1]%mod;
		}
		cout<<ans%mod<<endl;
	}
}
```


---

## 作者：cwfxlh (赞：3)

## [CF1815D](https://www.luogu.com.cn/problem/CF1815D)    
容易发现，当 $m$ 大于 $2$ 的时候有 $k,\frac{n-k}{2},\frac{n-k}{2},0,0,0...$ 一类的构造，也就是说 $m$ 大于 $2$ 的时候答案就是一个等差数列求和（至于为什么是充要条件是很好证明的）。$m$ 等于 $1$ 的时候答案也很明显。    
考虑 $m=2$ 的情况。对于 $n$ 的奇偶性来讨论一下，$n$ 为奇数的时候，最后一位一定为 $1$，那么不妨消掉最后一位，就有：$ans_n=ans_{\frac{n-1}{2}}\times +num_{\frac{n-1}{2}},num_n=num_{\frac{n-1}{2}}$，$num$ 表示答案种数，$ans$ 表示答案之和。     
如果是奇数，可得：$ans_n=2\times(ans_{\frac{n}{2}}+ans_{\frac{n-2}{2}}),num_n=num_{\frac{n}{2}}+num_{\frac{n-2}{2}}$，对于这个式子的正确性有个补充，因为 $\frac{n}{2}$与$\frac{n-2}{2}$ 的奇偶性不同，所以二者异或产生的答案是不交的。     
用 map 记忆化一下，就可以过了。     

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int t,n,m,ans;
struct ret{
    int f;
    int g;
};
map<int,ret>mp;
ret dfs(int X){
    if(X==1){
        return {1,1};
    }
    if(X==0)return {0,1};
    if(mp[X].f!=0)return mp[X];
    register ret k1,k2;
    if(X%2==1){
        k1=dfs(X/2);
        mp[X]={(k1.f*2+k1.g)%MOD,k1.g};
        return mp[X];
    }
    k1=dfs(X/2);
    k2=dfs((X-2)/2);
    mp[X]={(2*(k1.f+k2.f))%MOD,(k1.g+k2.g)%MOD};
    return mp[X];
}
signed main(){
    //freopen("CF1815D.in","r",stdin);
    scanf("%lld",&t);
    while(t--){
        scanf("%lld%lld",&n,&m);
        if(m==1){
            printf("%lld\n",(n)%MOD);
            continue;
        }
        if(m>2){
            if(n%2==0){
                ans=(((n+2)/2)%MOD)*((n/2)%MOD);
            }
            else{
                ans=(((n+1)/2)%MOD)*(((n+1)/2)%MOD);
            }
            ans%=MOD;
            printf("%lld\n",ans);
            continue;
        }
        ans=dfs(n).f;
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：qczrz6v4nhp6u (赞：2)

似乎是不一样的做法 /jy

### Solution

大力感受一下发现 $m\ge 3$ 是诈骗：首先奇偶性与 $n$ 不同的异或和是构造不出来的，而我们可以通过形如 $\{x,\frac{n-x}{2},\frac{n-x}{2},0,0,\cdots\}$ 的序列构造出任意一个奇偶性与 $n$ 相同的 $x$。再把 $m=1$ 判掉，接下来就只用考虑 $m=2$ 的情况。

拆位考虑，分类讨论第 $i$ 位是 $a_1,a_2$ 都没有 / $a_1,a_2$ 有一个有 / $a_1,a_2$ 都有的情况。第一种对于总和以及异或和都没有贡献，第二种会对总和以及异或和均产生 $2^i$ 的贡献，第三种会对总和产生 $2^{i+1}$ 的贡献。

考虑将上述过程揉进 dp 中。设 $f_{k,i}/g_{k,i}$ 表示填到了从高到低的第 $k$ 位，当前总和为 $i$ 的方案数 / 答案。转移按照上面的三种情况转移到 $(k-1,i)/(k-1,i+2^k)/(k-1,i+2^{k+1})$ 即可。由于这是单点求值，可以折半做到 $O(\sqrt n\log n)$ 的复杂度。

但是这个复杂度面对 $n\le 10^{18}$ 还是太吃操作了，有没有更强势的做法呢？有的兄弟有的，注意到对于每个 $k$，有用（能从初态转移到且能转移到终态）的状态数至多只有 $2$ 个。这是因为我们是从高到低填的，能从初态转移到的 $(k,i)$ 必然满足 $2^{k+1}|i$；同时，一个 $i$ 能转移到的 $i'$ 的范围是 $[i,i+2^{k+2}-2]$，不难说明合法的状态数最多有 $2$ 个。所以直接记搜即可做到 $O(\log n)$ 的复杂度。

### Code

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int mod=998244353;
inline ll add(ll x,ll y){return (x+=y)>=mod&&(x-=mod),x;}
inline ll Add(ll &x,ll y){return x=add(x,y);}
inline ll sub(ll x,ll y){return (x-=y)<0&&(x+=mod),x;}
inline ll Sub(ll &x,ll y){return x=sub(x,y);}
ll n;int m;
struct node{
	ll f,g;
	node(){f=g=0;}
	node(ll _f,ll _g){f=_f,g=_g;}
	inline node operator +(const node &_)const{return node(add(f,_.f),add(g,_.g));}
	inline node operator *(const node &_)const{return node(f*_.f%mod,(f*_.g+g*_.f)%mod);}
};
node coef[64],Ans[64][2];bool vis[64][2];
node calc(int k,ll i){
	if(n<i||n>i+(1ll<<(k+2))-2)return node(0,0);
	if(!~k)return node(1,0);
	bool c=n-i>=(1ll<<(k+1));
	if(vis[k][c])return Ans[k][c];
	vis[k][c]=1;
	return Ans[k][c]=calc(k-1,i)+coef[k]*calc(k-1,i+(1ll<<k))+calc(k-1,i+(1ll<<(k+1)));
}
void solve(){
	cin>>n>>m;
	if(!n||m==1)cout<<n%mod<<'\n';
	else if(m==2){
		for(int i=0;i<60;i++)
			vis[i][0]=vis[i][1]=0;
		cout<<calc(__lg(n),0).g<<'\n';
	}
	else{
		ll tmp=((n+1)>>1)%mod;
		if(n&1)cout<<tmp*tmp%mod<<'\n';
		else cout<<tmp*(tmp+1)%mod<<'\n';
	}
}
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	for(int i=0;i<60;i++)coef[i]=node(1,(1ll<<i)%mod);
	int _Test;cin>>_Test;
	while(_Test--)solve();
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

刚开始感觉这个东西不能做到 $O(m \log^2 V)$ 之下，后来发现每种答案只计算一遍。。

考虑 $m=1$，显然只有 $n$；$m \ge 3$，注意到最终结果 $s$ 满足 $s \equiv n \pmod 2$，且显然 $\le n$，所以所有 $0 \le x \le n$ 且 $2 \mid n-x$ 都可以被构造出来 $(x,\dfrac{n-x}{2},\dfrac{n-x}{2},0,\cdots)$。

考虑 $m=2$，即 $a + b = n$ 的 $a \oplus b$ 的所有可能性。

不妨设 $a \oplus b = t$，则 $a+b=n$ 需要满足：$\dfrac{n-t}{2} \cap t = \varnothing$，也就是 $n-t \cap (2t+1) = \varnothing$。这里交的是二进制位 $1$ 集合的交。

这玩意看着就很好数位 DP。因为你依次枚举 $t$ 的位，在 $n-t$ 中维护借位的操作，同时记录一下上一位即可。

这是代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MOD=998244353;
int T,n,m;
struct INFO {int res,cnt;}dp[100][2][2];
INFO operator +(INFO A,INFO B) {return {(A.res+B.res)%MOD,(A.cnt+B.cnt)%MOD};}
INFO operator -(INFO A,INFO B) {return {(A.res-B.res)%MOD,(A.cnt-B.cnt)%MOD};}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>m;
		if(m==1) {cout<<n%MOD<<'\n';continue ;}
		if(m>=3) {
			int l=n%2,r=n;
			int v1=l+r,v2=(r-l)/2+1;
			if(v1%2==0) v1/=2;
			else v2/=2;
			v1%=MOD,v2%=MOD;
			cout<<v1*v2%MOD<<'\n';
			continue ;	
		}
		memset(dp,0,sizeof(dp));
		dp[0][1][0]={0,1};
		ffor(i,0,63) {
			int col=(n>>i)&1,mul=(1ll<<i)%MOD;
			ffor(lst,0,1) ffor(jw,0,1) ffor(nt,0,1) {
				int v=col-nt-jw,nj=0;
				if(v<0) v+=2,nj=1;
				if(v&&lst) continue ;
				dp[i+1][nt][nj]=(dp[i+1][nt][nj]+INFO{(dp[i][lst][jw].res+nt*dp[i][lst][jw].cnt*mul)%MOD,dp[i][lst][jw].cnt});
			}
		}
		cout<<((dp[64][0][0]+dp[64][1][0]).res%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

很有趣的计数题。

首先 $m=1$ 是简单的，接下来你感觉 $m \geq 3$ 时应该可以构造出非常多的数，具体而言，你发现 $n = x + 2 \times y$，可以构造 $x,y,y,0,...,0$，异或和就是 $x$，于是可以构造出与 $n$ 模 $2$ 同余的所有数，由于异或是模 $2$ 意义下的加法，所以最后异或和必定与 $n$ 模二同余，于是你构造到了所有数。

关键是 $m=2$ 怎么做，形式化的说，$x+y=n$，求所有不同的 $x \oplus y$ 之和。

由于有异或的存在，肯定是在二进制下考虑，但是有加法存在说明要考虑进位问题，于是我们从低位到高位考虑问题，因为这样一来考虑高位是低位有没有进位已经确定。

不妨令 $solve(i,0/1)$ 表示只考虑 $x,y,n$ 二进制下最低的 $i$ 位，是否对第 $i+1$ 位产生了进位的前提下，所有可能的异或和，不妨令 $ch(u,v)$ 表示这一位上 $x,y$ 分别的取值，有 $n$ 第 $i$ 位是 $0$ 的情况下有 $solve(i,0) = solve(i-1,0) + ch(0,0),solve(i,1) = solve(i-1,1) + ch(1,0) / solve(i-1,0) + ch(1,1)$，否则有 $solve(i,0) = solve(i-1,0) + ch(1,0) / solve(i-1,1) + ch(0,0),solve(i,1) = solve(i-1,1) + ch(1,1)$，你发现在多个子状态合并到一个状态的过程中，各个子问题的答案加上第 $i$ 位的取值后互不相同，于是可以直接 dp，将每个子状态的方案数和答案都记下来即可。

时间复杂度 $O(T \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
int f[62][2],g[62][2];//方案数 和 
//solve(i,0/1)
//n 这位是 0:
/*
solve(i,0) = solve(i-1,0) + ch(0,0)
solve(i,1) = solve(i-1,1) + ch(1,0) / solve(i-1,0) + ch(1,1)
*/ 
//n 这位是 1:
/*
solve(i,0) = solve(i-1,0) + ch(1,0) / solve(i-1,1) + ch(0,0)
solve(i,1) = solve(i-1,1) + ch(1,1)
*/ 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		if(m==1){
			cout<<n%mod<<'\n';
		}else if(m>=3){
			int a=n%2,b=n;
			int q=(b-a)/2+1;
			q%=mod;
			a%=mod;
			b%=mod;
			cout<<(a+b)%mod*q%mod*((mod+1)/2)%mod<<'\n';
		}else{
			memset(f,0,sizeof(f));
			memset(g,0,sizeof(g));
			if(1&n){
				f[0][0]=1;
				g[0][0]=1;
				f[0][1]=0;
				g[0][1]=0;				
			}else{
				f[0][0]=1;
				g[0][0]=0;
				f[0][1]=1;
				g[0][1]=0;				
			}
			for(int i=1;i<62;i++){
				if((1ll<<i)&n){
					f[i][0]=(f[i-1][0]+f[i-1][1])%mod;
					g[i][0]=(g[i-1][0]+f[i-1][0]*((1ll<<i)%mod)%mod+g[i-1][1])%mod;
					f[i][1]=f[i-1][1];
					g[i][1]=g[i-1][1];
				}else{
					f[i][0]=f[i-1][0];
					g[i][0]=g[i-1][0];
					f[i][1]=(f[i-1][1]+f[i-1][0])%mod;
					g[i][1]=(g[i-1][1]+f[i-1][1]*((1ll<<i)%mod)%mod+g[i-1][0])%mod;
				}
			}
			cout<<g[61][0]<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1815D)

可以发现 $m \ge 3$ 是诈骗，因为我们可以进行类似这样的构造：$x,\frac{n-x}{2},\frac{n-x}{2},0,\dots,0$，那么它的异或和就是 $x$。~~所以 CF 其实可以把 m 也出到 10^18~~

发现这个 $x$ 是一个公差为 $2$ 的等差数列形式，所以它的和就是 $\frac{(a_1 + a_n) \cdot n}{2}$。

当 $n$ 为奇数，$a_1 = 1,a_n = n,n = \frac{n + 1}{2}$，即 $\frac{(n + 1)^2}{4}$。

同理易得当 $n$ 为偶数，公式也类似，为 $\frac{n(n + 2)}{4}$。

于是你可以提前处理下 $4$ 的逆元，$O(1)$ 求出答案。

---

考虑 $m < 3$。

当 $m = 1$ 时，显然 $n \bmod 998244353$ 是答案。

当 $m = 2$，此时只有两个数。

直接枚举肯定会 $\text{TLE}$，因为 $x \le 10^{18}$。

我们考虑数位 $\text{dp}$。

设 $f(i,j)$ 表示从高到低第 $i$ 位两数该位置之和为 $j$ 的不同异或值总和，$g(i,j)$ 是不同异或值的个数。

显然，$j$ 只有 $4$ 种取值：

- $j = 0$：两个都是 $0$。

- $j = 1$：一个 $0$ 一个 $1$。

- $j = 2$：两个都是 $1$。

- $j = 3$：两个都是 $1$，还多一个 $1$ 用来退位。

显然答案是 $f(len,0)+f(len,1)+f(len,2)$。接下来我们考虑怎么转移。

首先考虑 $g$。

如果没有退位，即 $g(i,a_i)$，可以从 $g(i - 1,0),g(i - 1,1),g(i - 1,2)$ 转移来。

如果有退位，即 $g(i,a_i + 2)$，那么肯定不能从 $g(i - 1,0)$ 转移来，可以从 $g(i - 1,1),g(i - 1,2),g(i - 1,3)$ 转移来。

再考虑 $f$。

如果没有退位，即 $f(i,a_i)$，首先要继承上一位的贡献，即 $(f(i - 1,0) + f(i - 1,1) + f(i - 1,2)) \times 2$，因为没有退位所以不用改动；再是这位的贡献，如果这一位是 $1$，那么每一种方案的贡献都可以 $+1$（异或相当于不进位加法，所以加起来为 $1$ 异或起来也是 $1$），所以是 $g(i,1) \times 1$；如果是 $0$ 则没有贡献。所以可以写成 $f(i,a_i) = (f(i - 1,0) + f(i - 1,1) + f(i - 1,2)) \times 2 + g(i,a_i) \cdot a_i$。

如果有退位，即 $f(i,a_i + 2)$，那么上一位肯定会受到影响：

- 从 $f(i - 1,1)$ 转移，那么退位后上一位会变成两个 $0$，每种方案异或值减少 $1$，所以答案应该减少 $g(i - 1,1)$。

- 从 $f(i - 1,2)$ 转移，那么退位后上一位会从两个 $1$ 变成一个 $0$ 一个 $1$，相当于每种方案异或值增加 $1$ 的贡献，要增加 $g(i - 1,2)$。

- 从 $f(i - 1,3)$ 转移，那么退位后上一位会从三个 $1$ 变成两个 $1$，每种方案异或值减少 $1$，所以答案应该减少 $g(i - 1,3)$。

最后这些贡献要乘上 $2$。

然后还要加上这一位的贡献 $g(i,a_i + 2) \cdot a_i$，类似没有退位的贡献。

所以 $f(i,a_i + 2) = (f(i - 1,1) - g(i - 1,1) + f(i - 1,2) + g(i - 1,2) + f(i - 1,3) - g(i - 1,3)) \times 2 + g(i,a_i + 2) \cdot a_i$。

$g(0,0)$ 的初值要赋为 $1$，因为第 $0$ 位两个数都是 $0$ 的方案数是 $1$。

---

在边做 $\text{dp}$ 的时候要边记得取模。$\text{dp}$ 中可能出现负数，可以在输出的时候一并处理。

$m \ge 3$ 的时候直接算会爆 `long long`，需要先取模再算取模之前要判奇偶性，取模之后不能直接除 $4$（要乘 $4$ 的逆元）。

代码：

```cpp
#include<bits/stdc++.h>
#define mode(i) \
{\
    f[i][0] %= mod, f[i][1] %= mod, f[i][2] %= mod, f[i][3] %= mod;\
    g[i][0] %= mod, g[i][1] %= mod, g[i][2] %= mod, g[i][3] %= mod;\
}
#define debug printf( "i:%d\nf:%d %d %d %d\ng:%d %d %d %d\n", i, f[i][0], f[i][1], f[i][2], f[i][3], g[i][0], g[i][1], g[i][2], g[i][3] );
using namespace std;

const int mod = 998244353;

typedef long long ll;

ll f[64][4], g[64][4], a[64];

ll solve( ll n, ll m ){
    if( m == 1 ) return n % mod;
    if( m == 2 ){
        //多测不清空，__________
        memset( f, 0, sizeof f );
        memset( g, 0, sizeof g );
        memset( a, 0, sizeof a );
        ll now = n, cnt = 0;
        while( now ) a[++cnt] = ( now & 1 ), now >>= 1;
        g[cnt + 1][0] = 1;
        //由于高低顺序换了一下，所以用 i+1 转移
        for( int i = cnt; i >= 1; --i ){
            g[i][a[i]] = g[i + 1][0] + g[i + 1][1] + g[i + 1][2];
            g[i][a[i] + 2] = g[i + 1][1] + g[i + 1][2] + g[i + 1][3];
            f[i][a[i]] = ( f[i + 1][0] + f[i + 1][1] + f[i + 1][2] ) * 2 % mod + a[i] * g[i][a[i]];
            f[i][a[i] + 2] = ( f[i + 1][1] - g[i + 1][1] + f[i + 1][2] + g[i + 1][2] + f[i + 1][3] - g[i + 1][3] ) * 2 % mod + a[i] * g[i][a[i] + 2];
            mode(i);
        }
        return ( f[1][1] + f[1][0] + f[1][2] ) % mod;
    }
    bool and1 = ( n & 1 );
    n %= mod;
    if( and1 ){
        return ( 1ll + n ) % mod * ( n + 1ll ) % mod * 499122177ll % mod * 499122177ll % mod;
    }
    return ( 2ll + n ) % mod * n % mod * 499122177ll % mod * 499122177ll % mod;
}

struct IO{
    ll n, m, ans;
    IO(){ //构建时输入
        scanf( "%lld%lld", &n, &m );
    }
    ~IO(){ //清除时输出
        printf( "%lld\n", ( ans % mod + mod ) % mod );
    }
};

struct work{
    int t;
    work(){
        scanf( "%d", &t );
        while(t--){
            IO io;
            io.ans = solve( io.n, io.m );
        }
    }
} w; //在主函数之前的结构体可以构建的

int main(){
    //一个没用的主函数
    return 0;
}
```

---

## 作者：pyiming (赞：0)

# 题意简述

题目要求计算所有可能的情况，其中 $a_1,a_2,\ldots,a_m$ 是非负整数，且它们的和为 $n$，求这些数的异或和的总和（相同的异或和只计算一次），并输出结果对 $998244353$ 取模后的值。

# 解题思路

因为相同的异或和只计算一次，所以考虑对于异或和 $x$，其是否出现。

可以在 $a_1$ 填入 $x$，那么若能使 $\oplus_{i=2}^m=0$ 且 $\sum_{i=2}^m=n-x$，则异或和 $x$ 会出现，只要让 $a_2=\frac{n-x}2,a_3=\frac{n-x}2$ 即可。但是，这只有 $n-x$ 为偶数的情况成立；当 $n-x$ 为奇数时，由于 $\oplus_{i=2}^m=0$，所以每一位的 $1$ 都会出现偶数次，和必然为偶数，所以 $n-x$ 为奇数时 $x$ 无法出现。所以我们只需要求出令 $n-x$ 为偶数的 $x$ 的总和即可，那就做一遍等差数列求和。

好像这题就做完了？显然不是，注意到以上的构造方法仅在 $m>=3$ 时存在，所以我们还需考虑 $m<=2$ 时的解法。

显然，$m=1$ 时 $x=n$，取模后输出即可。

考虑 $m=2$ 的情况。注意到数只有两个，显然很少，可以考虑在二进制下一位位确定 $x$，不难想到数位 $\text{dp}$。先将 $n$ 进行二进制拆分，从高到低第 $i$ 位为 $a_i$。从高往低解决，设 $f(i,0/1/2/3)$ 表示第 $i$ 位时，两个数该位分别为两个 $0$ / 一个 $1$ 个 $0$ / 两个 $1$ / 两个 $1$ 还多 $1$（用于向下退位）的所有不同异或和之和。发现不好转移，考虑先计数后求和。

设辅助函数 $g(i,0/1/2/3)$ 表示第 $i$ 位时，两个数该位分别为两个 $0$ / 一个 $1$ 个 $0$ / 两个 $1$ / 两个 $1$ 还多 $1$（用于向下退位）的不同异或和个数。显然 $g$ 很好转移：

1. $g(i,a_i)=g(i-1,0)+g(i-1,1)+g(i-1,2)$
2. $g(i,a_i+2)=g(i-1,1)+g(i-1,2)+g(i-1,3)$

以上两个式子分别表示：

1. 第 $i$ 位不从上一位退位，所以不能由用于退位的 $3$ 状态转移
2. 第 $i$ 位从上一位退位，所以不能由不退位的 $0$ 状态转移

类似地，也可以列出 $f$ 的转移方程：

1. $f(i,a_i)=(f(i-1,0)+f(i-1,1)+f(i-1,2))\times2+g(i,a_i)\times a_i$
2. $f(i,a_i+2)=(f(i-1,1)-g(i-1,1)+f(i-1,2)+g(i-1,2)+f(i-1,3)-g(i-1,3))\times2+g(i,a_i+2)\times a_i$

分别表示：

1. 第 $i$ 位不从上一位退位，所以不能由用于退位的 $3$ 状态转移。由于上一位是高位，所以之前的贡献乘上 $2$，并加上这一位的贡献即该状态的方案数乘该为的值。
2. 第 $i$ 位从上一位退位，所以不能由不退位的 $0$ 状态转移。由于上一位退位，所以之前的贡献改变，$0$ 变 $1$ 的加上方案数，$1$ 变 $0$ 的减去方案数，并按同上处理。

这样就解决了 $m=2$ 的情况。

时间复杂度 $O(t\log n)$。

# 参考代码

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998'244'353;
const int len=60;
struct IO{
    ll n,m;
    ll ans;
    IO(){
        cin>>n>>m;
    }
    ~IO(){
        cout<<ans<<"\n";
    }
};
struct solution{
    ll f[len+2][4],g[len+2][4];
    ll solve(int a[]){//记得取模(a从高到低)
        memset(f,0,sizeof f);
        memset(g,0,sizeof g);
        g[0][0]=1;
        for(int i=1;i<=len;i++){
            g[i][a[i]]=(g[i-1][0]+g[i-1][1]+g[i-1][2])%mod;
            g[i][2+a[i]]=(g[i-1][1]+g[i-1][2]+g[i-1][3])%mod;
            // cout<<g[i][0]<<" "<<g[i][1]<<" "<<g[i][2]<<"\n";
        }
        for(int i=1;i<=len;i++){
            f[i][a[i]]=(((f[i-1][0]+f[i-1][1]+f[i-1][2])<<1)+g[i][a[i]]*a[i])%mod;
            f[i][2+a[i]]=(((f[i-1][1]-g[i-1][1]+f[i-1][2]+g[i-1][2]+f[i-1][3]-g[i-1][3]+2*mod)<<1)+g[i][2+a[i]]*a[i])%mod;
            // cout<<f[i][0]<<" "<<f[i][1]<<" "<<f[i][2]<<"\n";
        }
        return (f[len][0]+f[len][1]+f[len][2])%mod;
    }
};
ll pow(ll a,ll b,ll p){
    ll ans=1;
    while(b){
        if(b&1){
            ans=ans*a%p;
        }
        a=a*a%p;
        b>>=1;
    }
    return ans;
}
int main(){
    // freopen("data.in","r",stdin);
    // freopen("data.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--){
        IO io;
        if(io.m==1){
            io.ans=io.n%mod;
        }
        else if(io.m>=3){
            if(io.n&1){
                ll len=((io.n+1)>>1)%mod;
                io.ans=((1+io.n)%mod*len)%mod*pow(2,mod-2,mod)%mod;;
            }
            else{
                ll len=(io.n>>1)%mod;
                io.ans=((2+io.n)%mod*len)%mod*pow(2,mod-2,mod)%mod;
            }
        }
        else{
            solution sol;
            int a[len+2];
            for(int i=len;i>=1;i--){
                a[i]=io.n&1;
                io.n>>=1;
            }
            io.ans=sol.solve(a);
        }
    }
    return 0;
}
```

---

## 作者：Nine_Suns (赞：0)

第一眼感觉非常神秘！直接考虑找性质！

考虑如何拼凑出异或和 $x$，直接令 $a_1=x$，则我们要把 $n-x$ 分配到剩下的 $m-1$ 个数中，让它们异或和为 $0$，如果 $n-x$ 是奇数，显然无解，否则可以构造 $2$ 个 $\frac{n-x}{2}$，剩下的 $a$ 直接取 $0$。

发现这个方法的前提是 $m\ge3$，答案为小于等于 $n$ 的数中所有与 $n$ 模 $2$ 同余的数之和，可以 $O(1)$ 计算。

然后发现当 $m=1$ 时显然答案为 $n$。

所以只需考虑 $m=2$ 时的情况。

考虑 dp，令 $f_{i,j},g_{i,j}$ 分别表示在前 $i$ 个二进制位中满足向 $i+1$ 位进位为 $j$ 的答案和方案数。记按照 $n$ 在二进制下第 $i$ 位的数值为 $o_i$，则可以根据 $o_i$ 分讨转移。具体地，若 $o_{i+1}=j$，此时在 $i+1$ 位可以都放 $1$ 或都放 $0$，进位分别为 $1,0$，有转移 $g_{i+1,1}\gets g_{i+1,1}+g_{i,j},g_{i,0}\gets g_{i+1,0}+g_{i,j}$，$f$ 的转移同理，另一种情况类似，不再赘述。需要注意的是，当 $o_{i+1}\neq j$ 时，放 $1$ 会使 $f$ 增加 $2^{i+1}g_{i,j}$ 的贡献。最终答案即为 $f_{60,0}$（$2^{60}>10^{18}$）。

复杂度 $O(T\log n)$。

[Code](https://codeforces.com/contest/1815/submission/230180415)

---

## 作者：User_Authorized (赞：0)

## 题意

给定 $n, m$，对于所有满足 $\displaystyle \left(\sum\limits_{i = 1}^{m}a_i\right) = n$ 的非负整数序列 $a_m$，求所有可能的 $\displaystyle \bigoplus\limits_{i = 1}^{m} a_i$ 的值的和，相同的异或和值只计算一次。

（$1 \le n \le 10^{18}, 1 \le m \le 10^5, 1 \le T \le 10^4$）。

## 题解

**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solution-CF1815D.html)**

对 $m$ 分类讨论。

---

### $m = 1$

直接输出 $n$ 即可。

### $m \ge 3$

考虑将 $n$ 划为形如 $x, \dfrac{n - x}{2}, \dfrac{n - x}{2}, 0, 0, \cdots$ 的若干整数，可以发现 $x$ 这个序列的和为 $n$，异或和为 $x$，同时 $x$ 可以取到所有与 $n$ 奇偶性相同且不大于 $n$ 的非负整数。最终答案为所有可能的 $x$ 的和，即

$$\sum\limits_{x \le n} \left[x \equiv n \bmod 2\right] x$$

下面论证不存在与 $n$ 奇偶性不同且符合条件的 $x$。

观察到

- 奇数与奇数相加为偶数，奇数与奇数相异或也为偶数；
- 偶数与奇数相加为奇数，偶数与奇数相异或也为奇数；
- 偶数与偶数相加为偶数，偶数与偶数相异或也为偶数；

也就是加法运算和异或运算奇偶性相同，故最终异或和不可能与 $n$ 奇偶性不同。

### $m = 2$

考虑减小问题规模，设 $x, y$ 为符合要求的一组解， $f(n)$ 表示 $n$ 的答案，$g(n)$ 表示 $n$ 的答案数，即可能的异或值数量。因为 $n$ 的奇偶性确定后，两个数的奇偶性也会确定，故按 $n$ 的奇偶性分类讨论。

#### $n$ 为奇数

$x, y$ 中必定有一个奇数和一个偶数，假定 $x$ 为奇数，$y$ 为偶数，设 $x^{\prime} = \dfrac{x - 1}{2}, y^{\prime} = \dfrac{y}{2}$，那么有 

$$\begin{aligned}
x^{\prime} + y^{\prime} &= \dfrac{n - 1}{2}\\
x \oplus y &= 2 \times \left(x^{\prime} \oplus y^{\prime}\right) + 1
\end{aligned}$$

那么有转移

$$\begin{aligned}
f(n) &= 2 \times f(\dfrac{n - 1}{2}) + g(\dfrac{n - 1}{2})\\
g(n) &= g(\dfrac{n - 1}{2})
\end{aligned}$$

#### $n$ 为偶数

$x, y$ 奇偶性一定相同。

若 $x, y$ 均为偶数，那么设 $x^{\prime} = \dfrac{x}{2}, y^{\prime} = \dfrac{y}{2}$，有

$$\begin{aligned}
x^{\prime} + y^{\prime} &= \dfrac{n}{2}\\
x \oplus y &= 2 \times \left(x^{\prime} \oplus y^{\prime}\right)
\end{aligned}$$

若 $x, y$ 均为偶数，那么设 $x^{\prime} = \dfrac{x - 1}{2}, y^{\prime} = \dfrac{y - 1}{2}$，有

$$\begin{aligned}
x^{\prime} + y^{\prime} &= \dfrac{n}{2} - 1\\
x \oplus y &= 2 \times \left(x^{\prime} \oplus y^{\prime}\right)
\end{aligned}$$

综合两种情况，有转移

$$\begin{aligned}
f(n) &= 2 \times f(\dfrac{n}{2}) + 2 \times f(\dfrac{n}{2} - 1)\\
g(n) &= 2 \times g(\dfrac{n}{2}) + 2 \times g(\dfrac{n}{2} - 1)
\end{aligned}$$

递归处理即可，总复杂度 $\mathcal{O}(\log n)$，可以通过本题。

## Code

```cpp
//Codeforces - 1815D
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::map<valueType, ValuePair> Memory;

constexpr valueType MOD = 998244353;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

Memory memory;

ValuePair solve(valueType n) {
    if (memory.count(n))
        return memory[n];

    if (n == 0)
        return memory[n] = std::make_pair(0, 1);

    if (n == 1)
        return memory[n] = std::make_pair(1, 1);

    if (n & 1) {
        auto const result = solve(n >> 1);

        return memory[n] = std::make_pair(sum(mul(result.first, 2), result.second), result.second);
    } else {
        auto const A = solve(n / 2), B = solve(n / 2 - 1);

        return memory[n] = std::make_pair(mul(sum(A.first, B.first), 2), sum(A.second, B.second));
    }
}

constexpr valueType Inv2 = 499122177;

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N, M;

        std::cin >> N >> M;

        if (N == 0) {
            std::cout << 0 << '\n';
        } else if (M == 1) {
            std::cout << (N % MOD) << '\n';
        } else if (M == 2) {
            memory.clear();

            std::cout << (solve(N).first % MOD) << '\n';
        } else {
            if (N & 1) {
                std::cout << (mul((N + 1) % MOD, mul(((N + 1) / 2) % MOD, Inv2))) << '\n';
            } else {
                std::cout << (mul((N + 2) % MOD, mul((N / 2) % MOD, Inv2))) << '\n';
            }
        }
    }

    std::cout << std::flush;

    return 0;
}
```

---

