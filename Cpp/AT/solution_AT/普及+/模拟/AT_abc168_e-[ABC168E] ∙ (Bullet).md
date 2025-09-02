# [ABC168E] ∙ (Bullet)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc168/tasks/abc168_e

$ N $ 匹のイワシが釣れました。$ i $ 匹目のイワシの美味しさは $ A_i $、香り高さは $ B_i $ です。

この中から $ 1 $ 匹以上のイワシを選んで同じクーラーボックスに入れますが、互いに仲が悪い $ 2 $ 匹を同時に選ぶことはできません。

$ i $ 匹目と $ j\ (\neq\ i) $ 匹目のイワシは、$ A_i\ \cdot\ A_j\ +\ B_i\ \cdot\ B_j\ =\ 0 $ を満たすとき(また、その時に限り)仲が悪いです。

イワシの選び方は何通りあるでしょう？答えは非常に大きくなる可能性があるので、$ 1000000007 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ -10^{18}\ \leq\ A_i,\ B_i\ \leq\ 10^{18} $

### Sample Explanation 1

条件を満たす選び方は以下の $ 5 $ 通りです。 - $ 1 $ 匹目 - $ 1,\ 2 $ 匹目 - $ 2 $ 匹目 - $ 2,\ 3 $ 匹目 - $ 3 $ 匹目

## 样例 #1

### 输入

```
3
1 2
-1 1
2 -1```

### 输出

```
5```

## 样例 #2

### 输入

```
10
3 2
3 2
-1 1
2 -1
-3 -9
-8 12
7 7
8 1
8 2
8 4```

### 输出

```
479```

# 题解

## 作者：hyxgg (赞：3)

[题目](https://www.luogu.com.cn/problem/AT_abc168_e)

## 思路
$A_iA_j+B_iB_j=0$ 化简得 $\frac{A_i}{B_i}=-\frac{B_j}{A_j}$。

那么我们将所有的 $\frac{A_i}{B_i}$ 化成最简分数，开个 `map` 存个数，$\frac{A_i}{B_i}$ 的个数为 $mp_{A_i,B_i}$。

为保证统一，如果 $\frac{A_i}{B_i}$ 为负，则让 $A_i$ 为负，$B_i$ 为正（反之亦可）。

那么对于每个 $\frac{A_i}{B_i}=-\frac{B_j}{A_j}$，其总方案数就是 $2^{mp_{A_i,B_i}}+2^{mp_{-B_i,A_i}}$。

答案则为所有上面的东西的乘积，最后减去 $1$（不能全不选）。

## 特判
对于 $A_i$，$B_i$ 均为 $0$ 的情况，则他不能和其他另外任何一只鱼一起，答案最后加上其个数即可。

对于 $A_i$，$B_i$ 中有且仅有一个为 $0$ 的情况，我们直接将 $A_i$ 和 $B_i$ 为零的情况分别塞进 $mp_{0,1}$ 或 $mp_{1,0}$ 里，然后和上面一起处理就行了。

## 代码
代码如下，有问题评论区见。
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
#define ll long long
using namespace std;
const ll mod=1000000007;
ll gcd(ll a,ll b){
	while(b!=0){
		ll t=b;
		b=a%b;
		a=t;
	}
	return a;
}
map<pair<ll,ll>,ll>mp;
ll n,a[200005],b[200005];
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		ll dg=gcd(a[i],b[i]);
		if(a[i]==0||b[i]==0){
			if(a[i]==0&&b[i]==0){
				mp[{0,0}]++;
				continue;
			}
			else if(a[i]==0){
				mp[{0,1}]++;
			}
			else mp[{1,0}]++;
			continue;
		}
		if(dg!=0)a[i]/=dg,b[i]/=dg;
		if(b[i]<0)b[i]=-b[i],a[i]=-a[i];
		mp[{a[i],b[i]}]++;
	}
	
	ll ans=1;
	
	for(ll i=1;i<=n;i++){
		ll da=0,tt=1,ds=mp[{a[i],b[i]}];
		if(a[i]==0||b[i]==0)continue;
		if(ds){
			for(ll i=1;i<=ds;i++)tt*=2,tt%=mod;
			mp[{a[i],b[i]}]=0;
		}
		da+=tt;
		da%=mod;
		ll nb=a[i],na=-b[i];
		if(nb<0)na=-na,nb=-nb;
		ds=mp[{na,nb}],tt=1;
		if(ds){
			for(ll i=1;i<=ds;i++)tt*=2,tt%=mod;
			mp[{na,nb}]=0;
		}
		if(da)da--;
		
		da+=tt;
		ans*=da%mod;
		ans%=mod;
	}
	
	ll da=1;
	for(ll i=1;i<=mp[{1,0}];i++){
		da*=2;
		da%=mod;
	}
	da--;
	ll dda=da;
	da=1;
	for(ll i=1;i<=mp[{0,1}];i++){
		da*=2;
		da%=mod;
	}
	ans*=(da%mod+dda%mod)%mod;
	ans%=mod;
	ans+=mp[{0,0}];
	ans%=mod;
	ans--;
	ans+=mod;
	ans%=mod;
	printf("%lld",ans); 
	return 0;
}
```

---

## 作者：buowen123 (赞：3)

## 题目大意：

- 给定 $n$ 个二元组 $(a_i,b_i)$。
- 要求至少选一组数，并且对于任意两组 $(a_i,b_i)$ 和 $(a_j,b_j)$ 都不会有 $a_ia_j+b_ib_j=0$。
- 求选法数量对 $10^9+7$ 取模的值。

## 题目解决：

我们考虑对式子变形得到 $\dfrac {a_i} {b_i}=-\dfrac{b_j}{a_j}$，因此我们开一个 map，统计 $\dfrac{a_i}{b_i}$ 出现的次数。（map 里开一个 pair，存储分数**约分后**的分子和分母，然后强制其中一个非负，不能用 double，会掉精）

那么对于两个的分数 $a,b$，满足 $a=-\dfrac {1}{b}$，假设 $a$ 出现了 $x$ 次，$b$ 出现了 $y$ 次，那么对于这两组二元组而言，方案数为 $2^x+2^y-1$ 种。

为什么是这个数呢？因为每一个 $a$ 都可选可不选，有 $2^x$ 种，$b$ 也是，两个数加起来（注意不是乘起来）。但是所有二元组都不选这一种情况在 $a$，$b$ 都算过了一遍，所以减去 $1$。

而如果 $a$ 对应的 $b$ 没有出现，假设 $a$ 出现了 $x$ 次，方案数就是 $2^x$。

我们利用乘法原理求出答案，最后的答案需要减去一条都不选这一种非法情况即可。

~~然后你也许会发现你怎么调也 AC 不了。~~

原因是，如果题目输入出现 $(0,0)$，那么带入我们最开始的算式，会得到 $0\times a_j+0\times b_j=0$ 恒成立，所以**如果选了 $(0,0)$，我们就不能再选其他二元组了**，注意特判。

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define minus(x) x = -x
#define mpr make_pair
using namespace std;
using ll = long long;
const ll N = 2e5 + 5, mod = 1e9 + 7;
ll n, s, a, b, ans = 1;
map <pair <ll, ll>, ll> mp;
ll qpow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
	
int main() {
	cin >> n;
	for (ll i = 1; i <= n; ++i) {
		cin >> a >> b;
		ll d = __gcd (a, b);
		if (d == 0) {//d为0相当于a，b都是0，直接统计数量特判
			++s;
			continue;
		}
		a /= d, b /= d;
		if (a < 0) minus (a), minus (b);//强制分子非负
		++mp[mpr (a, b)];
	}
	for (auto i : mp) {
		if (i.y == 0) continue;
		ll a = i.x.x, b = i.x.y;
		ll d = qpow (2, mp[mpr (a, b)]);
		if (b > 0) minus (a); else minus (b);//注意要变成负数，这一步同样强制分子非负
		if (mp.count (mpr (b, a))) {
			d = (d + qpow (2, mp[mpr (b, a)]) - 1) % mod;
			mp[mpr (b, a)] = 0;
		}
		ans = ans * d % mod;
	}
	ans = ((ans + s - 1) % mod + mod) % mod;
	//最后的答案要加上s，表示s种选择(0,0)的情况，然后减去1
	cout << ans;
	return 0;
}
```

---

## 作者：方123456 (赞：3)

还是挺简单的一道题。

题目就是给定若干二元组 $(a_i,b_i)$，然后选出一个集合使得 $a_i \times a_j + b_i \times b_j=0$ 这样的 $i$ 和 $j$ 不存在，并且 $i \not = j$。

先处理柿子 $a_i \times a_j = - b_i \times b_j$，然后变成了 $\dfrac{a_i}{b_i} = - \dfrac{b_j}{a_j}$，然后我们把一个数变成了一个二元组 $(\dfrac{a_i}{b_i},-\dfrac{b_i}{a_i})=(A_i,B_i)$，两个数不能在同一个集合里面当且仅当 $A_i \not = B_j$ 并且 $A_j \not = B_i$，然后我们再把二元组相同的数当成本质相同的数字。

然后会发现，如果把二元组看成点，这张图对于不能在一个集合的连边，会产生很多的连通块，连通块点数是 $2$ 或者 $1$。

然后对于点数为 $2$ 的连通块就在两个点随便选一个要选的，然后那个点里面每个点都有两种决策。

设第一个点的个数是 $d$ 个，然后第二个点的个数是 $c$ 个，然后就变成了 $2^{c}+2^{d}-1$，具体的，就是两个都不选的情况被算了两次然后减去了一个。

然后我们对于一个二元组扔到一个 map 里面，然后我们把连通块的给拿出来，计算答案即可。

然后会发现这个稍微有点小问题，double 类型会被卡精度，于是我们存的是分数，然后我们强行把负数移到第一个，这个各位处理的时候稍微注意一下即可。

然后还有一个坑点是 $(0,0)$，这种情况下只能取这个数一个，特判一下即可。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=5e5+5;
const int Mod=1e9+7;
int n,X[INF],Y[INF];
map <int , map <int,map<int,map<int,int> > > >Map;
int ksm(int x,int y) {
    int ba=x%Mod,ans=1;
    while (y) {
        if (y&1) ans=(ans*ba)%Mod;
        ba=(ba*ba)%Mod;y>>=1;
    } 
    return ans;
}
void solve(int x,int y) {
    int kkx=x,kky=y;
    int g=__gcd(kkx,kky);
    kkx/=g;kky/=g;
    if (kky<0) kkx=-kkx,kky=-kky;

    int kkx1=-y,kky1=x;
    g=__gcd(kkx1,kky1);
    kkx1/=g;kky1/=g;
    if (kky1<0) kkx1=-kkx1,kky1=-kky1;

    Map[kkx][kky][kkx1][kky1]++;
}
signed main()
{
    // freopen("sub1_15.txt","r",stdin);
    ios::sync_with_stdio(false);
    cin>>n;int K=0,cnt=0;
    for (int i=1;i<=n;i++) {
        int x=0,y=0;
        cin>>x>>y;X[i]=x;Y[i]=y;
        if (x==0 || y==0) 
            K++;    
        if (x==0 && y==0) cnt++,K--;
        // long double xx=(long double)(1.0)*x/y;
        // long double yy=-(long double)(1.0)*y/x;
        solve(x,y);
    }
    int ans=1;
    for (int i=1;i<=n;i++) {
        int x=X[i],y=Y[i];
        // long double xx=(long double)(1.0)*x/y;
        // long double yy=-(long double)(1.0)*y/x ; 2333123
        if (x==0 && y==0) continue;
        int kkx=x,kky=y;
        int g=__gcd(kkx,kky);
        kkx/=g;kky/=g;
        if (kky<0) kkx=-kkx,kky=-kky;

        int kkx1=-y,kky1=x;
        g=__gcd(kkx1,kky1);
        kkx1/=g;kky1/=g;
        if (kky1<0) kkx1=-kkx1,kky1=-kky1;

        ans*=(ksm(2,Map[kkx][kky][kkx1][kky1])%Mod+ksm(2,Map[kkx1][kky1][kkx][kky])-1);
        Map[kkx][kky][kkx1][kky1]=Map[kkx1][kky1][kkx][kky]=0;ans%=Mod;
    }
    // cout<<ans<<" "<<K<<" "<<cnt<<" ?\n";
    ans%=Mod;
    cout<<((ans-1+cnt)%Mod+Mod)%Mod<<"\n";
    return 0;
}
```


---

## 作者：Super_Cube (赞：1)

# Solution

对限制进行变形得到 $\dfrac{A_i}{B_i}=-\dfrac{B_j}{A_j}$，因为限制间互不影响，考虑把每一种分数拿出来单独计算。

设分数 $\dfrac{A_i}{B_i}=c$ 有 $x$ 个，$-\dfrac{1}{c}$ 有 $y$ 个，那单看这一种分类方案为 $2^x+2^y-1$（去掉空集），最终答案即用乘法原理把这些组内相互限制的方案乘起来。因为可能同时存在 $c$ 与 $-\dfrac{1}{c}$，就会算重，要注意一下（比如打标记）。

别忘了至少选出一条鱼的限制！所以还要减去不选鱼的方案。

除法统计分数的个数好像会炸精度，所以用 `std::map<std::pair<long,long>,int>` 进行统计就好了。

不过 $\dfrac{-a}{b}=\dfrac{a}{-b}$，要记得钦定分子或分母非负进行统计，还有当分母为 $0$ 时的特殊情况。

最重要的是 $\dfrac{0}{0}$，它们不能与任何其它鱼放一起，要单独计算。

# Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
const int mod=1e9+7;
int base[200005];
std::map<std::pair<ll,ll>,int>mp;
int n,ans,c0;
int main(){
	scanf("%d",&n);
	base[0]=1;
	for(int i=1;i<=n;++i){
		if((base[i]=base[i-1]<<1)>=mod)base[i]-=mod;
		static ll x,y,d;
		scanf("%lld%lld",&x,&y);
		if(!x&&!y){
			++c0;
			continue;
		}
		d=std::__gcd(x,y);
		x/=d;y/=d;
		if(y<0)x=-x,y=-y;
		if(!y&&x<0)x=-x;
		++mp[std::pair<ll,ll>(x,y)];
	}
	ans=1;
	for(const auto&i:mp){
		static int res;res=base[i.second];
		static ll x,y;
		x=-i.first.second;y=i.first.first;
		if(y<0)x=-x,y=-y;
		if(!y&&x<0)x=-x;
		if(mp.count(std::pair<ll,ll>(x,y))){
			if((res+=base[mp[std::pair<ll,ll>(x,y)]]-1)>=mod)res-=mod;
			mp.erase(std::pair<ll,ll>(x,y));
		}
		ans=1ll*ans*res%mod;
	}
	if((ans+=c0-1)>=mod)ans-=mod;
	if(ans<0)ans+=mod;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

#### 思路

将式子化简一下，变为如果 $\frac{a_i}{b_i} = -\frac{b_j}{a_j} $，那么 $i$ 和 $j$ 就不能一起选。

将不能一起取的两个位置赋成不同的颜色，如果第 $i$ 个位置前面的位置都可以和它一起取，那么将 $i$ 这个位置的颜色赋成新的与前面不同的颜色。

令 $o$ 表示 $a_i,b_i$ 的 `gcd`  具体实现就是开 `map` 存 $-\frac{b_i/o}{a_i/o}$ 中的分子和分母。

每次看  $mp_{a_i/o,b_i/o}$ 是否有颜色，若有则取对应相反的颜色，否则看 $mp_{b_i/o,a_i/o}$ 是否有颜色，若有则取相同的颜色。

注意如果 $a_i=0,b_i=0$ 则要分开算，因为选了后其他的都不能选，所以最后答案加上 $a_i=0,b_i=0$ 的个数即可。

最后会发现有很多对应的颜色，对应的颜色不能一起选，但对其他的没影响，对于每一个颜色，可选可不选，是 $2^{v_i}-1$，因为不全不选，$v_i$ 表示颜色为 $i$ 的有几个，$ans = ans \times \left(2^{v_i}-1 + 2^{v_{i-1}}-1 +1 \right)$，其中 $i$ 和 $i-1$ 是对应的颜色，$+1$ 是因为不是对应的颜色可以一起选也可以不用，然后加上 $a_i=0,b_i=0$ 的个数就是答案了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
const int N = 1e6+10,mod = 1e9+7;
int n,cnt,v[N],ans,o,o1,sum;
struct w
{
	int a,b;
}c[N];
map<pair<int,int>,int>mp1;
map<int,int>mp;
inline int ksm(int x,int y)
{
	int ans = 1;
	while(y)
	{
		if(y % 2 == 1) ans = (ans * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return ans;
}
inline int check(int x)
{
	if(x == 0) return 0;
	else 
	{
		if(x % 2 == 0) return x+1;
		else return x-1;
	}
}
signed main()
{
	read(n);
	for(int i = 1;i <= n;i++) read(c[i].a),read(c[i].b);
	cnt = 1;
	for(int i = 1;i <= n;i++) 
	{
		if(c[i].a == 0 && c[i].b == 0)
		{
			sum++;
			continue;
		}
		o = __gcd(c[i].a,c[i].b),v[i] = max(check(mp1[make_pair(c[i].a/o,-c[i].b/o)]),check(mp1[make_pair(-c[i].a/o,c[i].b/o)]));
		if(!v[i])
		{
			o = __gcd(c[i].a,c[i].b),v[i] = max(mp1[make_pair(c[i].b/o,c[i].a/o)],mp1[make_pair(-c[i].b/o,-c[i].a/o)]);
			if(!v[i]) cnt += 2,v[i] = cnt;
		}
	    o = __gcd(c[i].a,c[i].b),mp1[make_pair(c[i].b/o,c[i].a/o)] = mp1[make_pair(-c[i].b/o,-c[i].a/o)] = v[i];
		mp[v[i]]++;
	}
	o1 = 1;
	for(int i = 3;i <= cnt;i += 2) 
		o1 = (o1 * ((ksm(2,mp[i])+ksm(2,mp[i-1])-1+mod) % mod) % mod) % mod;
	ans = (o1-1+mod+sum)%mod; 
	print(ans);
	flush();
	return 0;
}
```

---

