# Mike and Geometry Problem

## 题目描述

Mike wants to prepare for IMO but he doesn't know geometry, so his teacher gave him an interesting geometry problem. Let's define $ f([l,r])=r-l+1 $ to be the number of integer points in the segment $ [l,r] $ with $ l<=r $ (say that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/eeb8344fc6181df63840b4617c77d0b7d8f368f7.png)). You are given two integers $ n $ and $ k $ and $ n $ closed intervals $ [l_{i},r_{i}] $ on $ OX $ axis and you have to find:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/babb2cf528ef0c11f1d2962e2d5be706b0377f3a.png)In other words, you should find the sum of the number of integer points in the intersection of any $ k $ of the segments.

As the answer may be very large, output it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

Mike can't solve this problem so he needs your help. You will help him, won't you?

## 说明/提示

In the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/7f9f6f2b3fe972c0968e2bbe39c55090c69a5e96.png);

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/0c85a7c8eabbf8ea75307cc85322cc7194a52b51.png);

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/05a4f7cd13ee1be29210f871f739a0914a5c363f.png).

So the answer is $ 2+1+2=5 $ .

## 样例 #1

### 输入

```
3 2
1 2
1 3
2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 3
1 3
1 3
1 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 1
1 2
2 3
3 4
```

### 输出

```
6
```

# 题解

## 作者：Adove (赞：4)

这题统计每段子区间被多少条线段覆盖然后套组合数就行了

子区间的线段覆盖数可以用差分求得，不需要数据结构

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=2e5+5;
const int MOD=1e9+7;

int n,m,ans,cnt;
int fac[MAXN],inv[MAXN];
struct rpg{
	int x,kd;
}a[MAXN<<1];

int read()
{
	int x=0;bool fl=0;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-') fl=1;ch=getchar();}
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return fl?-x:x;
}

bool cmp(rpg a,rpg b){return a.x<b.x;}
int C(int n,int m){return n<m?0:(long long)fac[n]*inv[m]%MOD*inv[n-m]%MOD;}

int main()
{
	n=read(),m=read();fac[0]=inv[1]=inv[0]=1;
	for(int i=1;i<=n;++i) fac[i]=(long long)fac[i-1]*i%MOD;
	for(int i=2;i<=n;++i) inv[i]=(long long)(MOD-MOD/i)*inv[MOD%i]%MOD;
	for(int i=2;i<=n;++i) inv[i]=(long long)inv[i]*inv[i-1]%MOD;
	for(int i=1;i<=n;++i){
		a[i].x=read(),a[i+n].x=read()+1;
		a[i].kd=1,a[i+n].kd=-1;
	}sort(a+1,a+(n<<1)+1,cmp);
	for(int i=1;i<=n<<1;++i){
		ans+=(long long)C(cnt,m)*(a[i].x-a[i-1].x)%MOD;
		ans%=MOD;cnt+=a[i].kd;
	}printf("%d\n",ans);
	return 0;
}
```

---

## 作者：_H17_ (赞：1)

## 题目大意

给你 $n$ 个区间，取 $k$ 个区间，所有情况求交集包含的点数和。

## 题目分析

我们转换一下问题的思考角度，**从每种情况的点数和，转换为每个点在取 $k$ 个区间时全都包含的情况数和**（原因是只有 $k$ 个区间全部包含这个点，这个点才是交集的一部分）。

这样一来，我们需要求的就是**当前点被多少区间包含**，假设它被 $x$ 个区间包含，它对答案的贡献就是 $C_x^k$。

显然点有 $2\times 10^9$ 个，但并不是每个点都是**关键点**，只有一个**区间开始、结束**才会和相邻的点被不同数量的区间包含。所以显然我们需要离散化（使用 `map` 即可，这里不详细解读）。

如何离散化？**关键点**是和旁边有比 ***变化*** 的点（注意斜粗体字），既然是变化量，那我们就可以使用**差分**，最后不要忘记乘上这段区间长度（也就是到下一个关键点之前的这一段区间，原因是每个点被相同数量的区间包含，贡献相同）。

最后，预处理组合数，$C_n^k=\frac{A_n^k}{A_k^k}=\frac{n!}{k!\times(n-k)!}=\frac{n}{n-k}\times\frac{(n-1)!}{k!\times(n-k-1)!}=\frac{n}{n-k}\times\frac{A_{n-1}^k}{A_{k}^k}=\frac{n}{n-k}\times C_{n-1}^k$。

由于**涉及取模和除法**，这会导致 $a\mid b$ 但是 $(a\bmod p)\nmid (b \bmod p)$，所以我们要乘**逆元**（大部分大佬认为这很简单，但我比较菜，所以详细讲一下）。

关于 $a$ 在摸 $p$ 意义下的逆元是 $x$，当 $ax\equiv 1\pmod{p}$，记为 $a^{-1}$。根据这个式子，$x$ 在摸 $p$ 意义下类似于 $\frac{1}{a}$（移项即可）。最终我们得出 $\frac{a}{b}=a\times b^{-1} \pmod{p}$。

如何求逆元？$ax\equiv 1\pmod{p}$，根据费马小定理得到 $ax\equiv a^{b-1}\pmod{p}$。把 $a$ 移项得到 $x\equiv a^{b-2} \pmod{p}$。

当然需要满足费马小定理的条件 $p$ 是素数且 $\gcd(a,p)=1$。

然而题目中模数是 $10^9+7$ 可以验证，是素数。

设 $p=10^9+7$，时间复杂度 $O(n \log p)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ALL(x) x.begin(),x.end()
using namespace std;
const int mod=1e9+7;
int n,k,val,ans,c[200001];
map<int,int>mp;
int qp(int a,int b){
    int ret=1;
    a%=mod;
    while(b){
        if(b&1)
            ret*=a,ret%=mod;
        a*=a,a%=mod,b>>=1;
    }
    return ret;
}
void init(){
    c[k]=1;
    for(int i=k+1;i<=n;i++)
        c[i]=(c[i-1]*(i%mod))%mod*qp(i-k,mod-2),c[i]%=mod;
    return;
}
signed main(){
    cin>>n>>k;
    init();
    for(int i=1,a,b;i<=n;i++){
        cin>>a>>b;
        mp[a]++,mp[b+1]--;//差分
    }
	auto lit=mp.begin(),it=mp.begin();
    it++;
    for(;it!=mp.end()&&lit!=mp.end();it++,lit++)//[lit,it)区间
        val+=(lit->second),//当被多少区间包含
        ans+=(((it->first)-(lit->first))%mod)*c[val],ans%=mod;
    cout<<ans;
    return 0;
}
```

PS:本题目其实 1s 差不多，~~卡常这道题可以很快~~，根本不需要 3s，不要被时间限制误导。

---

## 作者：ifffer_2137 (赞：1)

翻译里对交集内整点数的解释还不如不解释……容易让人思路被误导。
### 题意
给定 $n$ 条线段，每次选 $k$ 条求交集内整点数，求所有选 $k$ 条线段的方案答案之和对 $10^9+7$ 取模。
### 分析
考虑每个点的贡献。

设该点有 $x$ 条线段覆盖，则它对答案的贡献为 $\tbinom{x}{k}$。然后发现只有在经过线段端点时 $x$ 才会改变，所以离散化以后差分求出每个端点变化完的答案，乘上这一段点数即可。

组合数预处理一下，总时间 $O(n\log_2n)$。
### 代码
```cpp
int pw(int a,int x){
	int s=1;a%=mod;
	while(x){
		if(x&1) s=s*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return s;
}
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		if(i<k) C[i]=0;
		else if(i==k) C[i]=1;
		else C[i]=C[i-1]*i%mod*pw(i-k,mod-2)%mod;
		a[i].l=read(),a[i].r=read()+1;
		t[++tot]=a[i].l,t[++tot]=a[i].r;
	}
	sort(t+1,t+tot+1);
	tot=unique(t+1,t+tot+1)-t-1;
	for(int i=1;i<=n;i++){
		a[i].l=lower_bound(t+1,t+tot+1,a[i].l)-t;
		a[i].r=lower_bound(t+1,t+tot+1,a[i].r)-t;
		c[a[i].l]++,c[a[i].r]--;
	}
	t[tot+1]=t[tot]+1;
	for(int i=1;i<=tot;i++){
		c[i]+=c[i-1];
		ans=(ans+C[c[i]]*(t[i+1]-t[i])%mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：yyyuuu (赞：1)

一道组合计数的好题。

直接对每个区间进行计算非常困难，不如把每个区间贡献(r-l+1)中的r与l-1拆开，分别进行统计。

因为取的是区间交集，所以l是所有K个区间中的最大值，先把所有线段按l从小到大排序，那么对于线段i来说，它的l[i]要有贡献，其余的线段j必须从1-(i-1)中选，并且r[j]不能小于l[i] (否则区间长度将为负数)。

所以要知道的是有多少线段的$r[j]>=l[i]$且$j<i$，离散化r后树状数组即可，设查询结果为cnt，则从cnt条线段中任选K-1条，与i取交集形成的区间的l都为l[i]，统计答案。

对于r的统计是一样的。

这样得到了所有长度不为负的区间的(l-1)的和与r的和,相减即可。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ; 
#define L 1ll * 
int N , K ;  
struct Sg {
	int l , r ; 
} p[200005] ; 
const int mod = 1e9 + 7 ; 

int jc[200005] , vjc[200005] ;
int fp ( int x , int k ) 
{
	int yl = 1 ; 
	while ( k )
	{
		if ( k % 2 ) yl = L yl * x % mod ; 
		x = L x * x % mod ;  
		k = k / 2 ; 
	} 
	return yl ; 
} 

void init ( ) 
{
	jc[0] = vjc[0] = 1 ; 
	for ( int i = 1 ; i <= 200000 ; i++ ) jc[i] = L jc[i - 1] * i % mod ; 
	vjc[200000] = fp ( jc[200000] , mod - 2 ) ; 
	for ( int i = 200000 ; i >= 2 ; i-- ) vjc[i - 1] = L vjc[i] * i % mod ; 
}

int group ( int big , int small ) { if ( big < small ) return 0 ; return L jc[big] * vjc[small] % mod * vjc[big - small] % mod ; } 

bool cmpl ( const Sg &a , const Sg &b ) { return a.l < b.l ; }
bool cmpr ( const Sg &a , const Sg &b ) { return a.r > b.r ; }

int disc[400005] , dd ; 
int GPS ( int x ) { return lower_bound ( disc + 1 , disc + dd + 1 , x ) - disc ; }

int ans = 0 , tr[400005] ;
int lowbit ( int x ) { return x & ( -x ) ; } 

void insert ( int pos ) 
{
	for ( ; pos <= dd ; pos += lowbit ( pos ) ) tr[pos]++ ; 
} 

int query ( int pos ) 
{
	int yl = 0 ; 
	for ( ; pos ; pos -= lowbit ( pos ) ) yl += tr[pos] ; 
	return yl ; 
}
   
int main ( ) 
{
	init ( ) ; 
	scanf ( "%d%d" , &N , &K ) ; 
	for ( int i = 1 ; i <= N ; i++ ) 
	    scanf ( "%d%d" , &p[i].l , &p[i].r ) ;
	for ( int i = 1 ; i <= N ; i++ ) disc[++dd] = p[i].l , disc[++dd] = p[i].r ; 
	sort ( disc + 1 , disc + dd + 1 ) ; 
	dd = unique ( disc + 1 , disc + dd + 1 ) - disc - 1 ;  
	sort ( p + 1 , p + N + 1 , cmpl ) ;
	for ( int i = 1 ; i <= N ; i++ ) 
	{
		int cnt = i - 1 - query ( GPS ( p[i].l ) - 1 ) ; 
		if ( cnt >= K - 1 ) ans = ( ans - L ( p[i].l - 1 ) * group ( cnt , K - 1 ) ) % mod ;
		insert ( GPS ( p[i].r ) ) ;  
	}
    sort ( p + 1 , p + N + 1 , cmpr ) ;
	memset ( tr , 0 , sizeof ( tr ) ) ;   
	for ( int i = 1 ; i <= N ; i++ ) 
	{
		int cnt = query ( GPS ( p[i].r ) ) ; 
		if ( cnt >= K - 1 ) ans = ( ans + L p[i].r * group ( cnt , K - 1 ) ) % mod ; 
		insert ( GPS ( p[i].l ) ) ;
	}
	printf ( "%d\n" , ( ans + mod ) % mod ) ;  
}

```

---

## 作者：Mashu77 (赞：0)

题意：已知 $n(n\le200000)$ 个区间，从这 $n$ 个区间中取出 $k(k\le n)$ 个区间，取这 $k$ 个区间的交集，问所有情况下区间交集的数据个数之和？（对答案 $\bmod 10^9+7$）

程序使用到数论，组合，树状数组。

Fermat's Small Theorem：如果 $n$ 是素数， $a^{n−1}=1 \bmod n$，那么 $a$ 关于 $n$ 的逆元就是 $a^{n−2}$。

每个点和小区间分开考虑，对于某个点和小区间被覆盖的次数 $x\ge k$，则贡献为 $(x, k)$，即  $x$ 个元素中取 $k$ 个元素的组合。

```cpp
#include<iostream>
#include<cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>

typedef  long long LL;
const LL  MOD = 1000000007;
const int N = 2e5+15;

using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,k;
int b[N*2];
int f[N*2];
LL F[N],Fn[N];
inline LL fpow(LL a,LL b,LL m)//快速幂
{
    LL ans = 1;
    a %= m;
    while(b > 0)
    {	//将b转换成二进制， 从低向高检查其非零bit位，然后ans乘以对应a的方幂
        if(b & 1)
           ans = (ans * a) % m;
        a = a * a % m;

        b >>= 1;
		//cout<<"a="<<a<<", b="<<b<<endl;
    }
    return ans;
}
LL Fermat(LL a,LL p)//求a关于p的逆元，前提p是质数
{
    return qpow(a,p-2,p);
}


inline void init(){
	// F[i] 为i的阶乘,  Fn[i]为其逆元
    F[1]=F[0]=Fn[0]=Fn[1]=1;
    for(LL i =2;i < N;i++){
        F[i] = F[i-1]*i % (MOD);
        Fn[i]=Fermat(F[i],MOD);
		if(i<6)
			cout<<"i="<<i<<", F[i]="<<F[i]<<", Fn[i]="<<Fn[i]<<endl;
    }
}
// n个元素中取m个元素的组合 c(n,m)=n!/(m!(n-m)!)
LL c(LL n,LL m){
    if(n<m)return 0ll;
	//cout<<", F[n]="<<F[n]<<", Fn[m]="<<Fn[m]<<endl;
    return 1ll*F[n]*Fn[m]%MOD*Fn[n-m]%MOD;// c(n,m)=n!/(m!(n-m)!)
}
struct node{
    int l,r;
    bool operator <(const node& p)const{
        return l<p.l;
    }
}a[N];

// 位置为端点下标，最大为 2*n，树状数组中保存包含该端点的区间个数
void update(int x,int val){
    while(x<2*n){f[x]+=val,x+=x&(-x);}
}
int get(int x){
    int sum=0;
    while(x>0){sum+=f[x],x&=x-1;}
    return sum;
}
int main(){

	cout<<Fermat(4,17)<<endl;
    init();
    scanf_s("%d%d",&n,&k);
    int cnt=0;
    for(int i=1;i<=n;i++)
        scanf_s("%d%d",&a[i].l,&a[i].r),b[++cnt]=a[i].l,b[++cnt]=a[i].r;
    sort(a+1,a+n+1);
    sort(b+1,b+cnt+1);
	for(int i=1;i<=cnt;i++)
		  cout<<"  "<<b[i];
	cout<<",  cnt="<<cnt<<endl;


    cnt=unique(b+1,b+cnt+1)-(b+1);
	for(int i=1;i<=cnt;i++)
		  cout<<"  "<<b[i];
	cout<<",  cnt="<<cnt<<endl;
    int num=0;
    LL sum=0;
    for(int i=1;i<=cnt;i++){
        while(num<n  &&  a[num+1].l<=b[i]){
            int vs=lower_bound(b+1,b+cnt+1,a[++num].r)-b;
			cout<<"i="<<i<<", b[i]="<<b[i]<<",  a[num].r="<<a[num].r<<", vs="<<vs<<endl;
            update(vs,1);// 右端位置上传
        }
        int px=num-get(i-1);// 包含b[i]的区间个数。
        sum+=c(px,k)%MOD,sum%=MOD;// 包含b[i]的交集个数。 若3个集合包含b[i]，k=2, 则c(3,2)=3
		cout<<"i="<<i<<"  sum="<<sum<<", num="<<num<<", px="<<px<<", c(px,k)="<<c(px,k)<<endl;
		if(i==cnt)break;
        int l=b[i]+1,r=b[i+1]-1;
        if(l>r) continue;
        px=num-get(i);//包含[b[i]+1, b[i+1]-1] 的区间个数。
        sum+=c(px,k)*(r-l+1)%MOD,sum%=MOD;// 包含[b[i]+1, b[i+1]-1] 的交集个数。
 		cout<<"i="<<i<<"  sum="<<sum<<endl;
    }
   printf("%I64d\n",sum);
    return 0;
}

---

## 作者：analysis (赞：0)

很无语。

一开始脑抽，把交集和并集的概念搞混了。

后面猛然一想：并集？这不是大水题么。

然后 coding，ans 还忘记取模了。

---

回归正题，求的是

在 $n$ 条线段中取 $k$ 条线段，其中有多少个点被 $k$ 条线段覆盖，求所有方案的答案和。

规约为贡献计算。

考虑点的贡献，假设本点被 $x$ 条线段覆盖，贡献显然为

$$
\begin{pmatrix}
 x\\k
\end{pmatrix}
$$

用一个 `map` 处理下差分，然后直接做就好了。

预处理下组合数：

$$
\begin{pmatrix}n\\k\end{pmatrix} = \frac{n!}{k!(n-k)!} = \frac{(n-1)!}{k!(n-k)!} \times n = \frac{(n-1)!}{k!(n-k-1)!} \times \frac{n}{(n-k)} = \begin{pmatrix}n-1\\k\end{pmatrix} \times \frac{n}{(n-k)}
$$

然后没了。

---

## 作者：C6H14 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF689E)

## 题目大意

给你 $n$ 条线段，第 $i$ 条为 $[l_i,r_i]$，求在这些线段中选任意 $k$ 条线段出来交集包含的整点数的和，对 $10^9+7$ 取模。

## 分析

（不）有趣的计数题。

考虑某个整点对答案什么时候有贡献，显然当且仅当我们所选的所有线段都包含这个整点时这个整点才会对答案做出贡献。

假设经过某个整点的线段数为 $x$，那么这个整点一共会有 $\dbinom{x}{k}$ 次贡献的机会。

那么我们可以将所有区间转化为区间加 $1$ 后扫描数轴的简单问题，维护差分数组，将 $l_i$ 和 $r_i+1$ 放进同一个数组排序，扫一遍这个数组，假设是左端点就将计数器加 $1$，否则减 $1$，同时更新答案即可。

总时间复杂度为 $O(n \log n)$。

## 代码

```cpp
void exgcd(ll a,ll b,ll &x,ll &y)
{
	if (b==0)
	{
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}
const ll N=200005,p=1e9+7;
ll rev(ll x)
{
	ll ans,tmp;
	x=(x%p+p)%p;
	exgcd(x,p,ans,tmp);
	return (ans%p+p)%p;
}
ll n,k,ans,fac[N],inv[N],cnt,sz;
pair<ll,int> a[N<<1];
ll c(ll n,ll m)
{
	if (m<0 || m>n)
		return 0;
	return fac[n]*inv[m]%p*inv[n-m]%p;
}
int main()
{
	n=read(),k=read();
	fac[0]=inv[0]=1;
	for (int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i%p,inv[i]=rev(fac[i]);
	for (int i=1;i<=n;++i)
		a[i*2-1]={read(),1},a[i<<1]={read()+1,-1};
	sort(a+1,a+1+n*2);
	for (int i=1;i<=n*2;++i)
	{
		ans=(ans+(a[i].first-a[i-1].first)*c(cnt,k)%p)%p;
		cnt+=a[i].second;
	}
	write(ans);
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：0)

## 思路

考虑转化一下，把计算选出 $k$ 条线段转化这个点被多少组 $k$ 个的线段所覆盖。

那么就有一个显然的思路，计算这个点被几个线段覆盖，可以差分来做，然后将每个点的 $\binom{x}{k}$ 求和即可。

这题值域很大，考虑将每个线段的端点离散化即可。

复杂度 $O(n\log n)$，瓶颈在于离散化。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[10000005],inv[10000005];
void init(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[10000000]=qp(fac[10000000],mod-2);
	for(int i=9999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
int a[400005],cf[400005];
signed main(){
	init();
	int n,k;
	cin>>n>>k;
	int l[n+1],r[n+1];
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
		a[i*2-1]=l[i];
		a[i*2]=r[i]+1;
	}
	sort(a+1,a+2*n+1);
	int m=0;
	for(int i=1;i<=2*n;i++){
		m++;
		a[m]=a[i];
		while(a[i+1]==a[i]){
			i++;
		} 
	}
	int dist[m+1];
	for(int i=1;i<m;i++){
		dist[i]=a[i+1]-a[i];
	}
	for(int i=1;i<=n;i++){
		l[i]=lower_bound(a+1,a+m+1,l[i])-a;
		r[i]=lower_bound(a+1,a+m+1,r[i]+1)-a;
		cf[l[i]]++;
		cf[r[i]]--;
	}
	int ans=0,now=0;
	for(int i=1;i<m;i++){
		now+=cf[i];
		ans=(ans+dist[i]*C(now,k))%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Elma_ (赞：0)

> [CF689E Mike and Geometry Problem](https://www.luogu.com.cn/problem/CF689E)

每一种方案的贡献都暴力算的话，复杂度显然会爆炸。考虑把所有方案的总贡献拆成每一个点的贡献之和。

但是你会发现如果每个点的贡献都算一遍的话复杂度还是会爆炸。考虑这些线段的交有什么样的性质。如果将所有区间的 $l_i$ 和 $r_i$ 在数轴上从小到大排序，那么整个数轴就会被这若干个点分成几个小的区间。对于相邻两个点组成的区间，有一个比较显然的结论，这个区间内的点要么同时对答案有相同贡献，或是同时对答案没有贡献，因为覆盖在这个区间内整点上的线段数量是一个定值。

所以就可以将整个小区间内的贡献一起计算。可以差分出每个小区间被多少条线段覆盖，然后组合数计算贡献。需要注意的是，如果一个区间上覆盖的线段数量不足 $k$ 条，那么这个区间的贡献就为 $0$。时间复杂度为 $O(n \log n)$，瓶颈在于排序。


```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}

const int maxn = 200005;
const int mod = 1e9 + 7;

struct segment {
	int pos, mark;
}a[maxn << 1];
int n, m, cnt;ll ans;
int fac[maxn], inv[maxn];

inline bool cmp(segment a, segment b) {
	return a.pos < b.pos;
}
inline int qpow(int a, int b) {
	int res = 1;
	for (;b;b >>= 1, a = 1ll * a * a % mod) {
		if (b & 1) res = 1ll * res * a % mod;
	}
	return res;
}
inline void init(int n) {
	fac[0] = 1;
	for (int i = 1;i <= n;i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[n] = qpow(fac[n], mod - 2);
	for (int i = n;i >= 1;i--) inv[i - 1] = 1ll * inv[i] * i % mod;
}
inline int C(int n, int m) {
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main(void) {
	init(maxn);
	n = read(), m = read();
	for (int i = 1;i <= n;i++) {
		a[i].pos = read(), a[i + n].pos = read() + 1;
		a[i].mark = 1, a[i + n].mark = -1;		
	}
	sort(a + 1, a + (n << 1) + 1, cmp);
	for (int i = 1;i <= (n << 1);i++) {
		ans += 1ll * C(cnt, m) * (a[i].pos - a[i - 1].pos) % mod;
		ans %= mod, cnt += a[i].mark;
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

