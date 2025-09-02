# The Destruction of the Universe (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, $ n \leq 10^6 $ . You can only make hacks if both versions of the problem are solved.

Orangutans are powerful beings—so powerful that they only need $ 1 $ unit of time to destroy every vulnerable planet in the universe!

There are $ n $ planets in the universe. Each planet has an interval of vulnerability $ [l, r] $ , during which it will be exposed to destruction by orangutans. Orangutans can also expand the interval of vulnerability of any planet by $ 1 $ unit.

Specifically, suppose the expansion is performed on planet $ p $ with interval of vulnerability $ [l_p, r_p] $ . Then, the resulting interval of vulnerability may be either $ [l_p - 1, r_p] $ or $ [l_p, r_p + 1] $ .

Given a set of planets, orangutans can destroy all planets if the intervals of vulnerability of all planets in the set intersect at least one common point. Let the score of such a set denote the minimum number of expansions that must be performed.

Orangutans are interested in the sum of scores of all non-empty subsets of the planets in the universe. As the answer can be large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, there are seven non-empty subsets of planets we must consider:

- For each of the subsets $ \{[1,1]\}, \{[2,3]\}, \{[3,3]\} $ , the score is $ 0 $ .
- For the subset $ \{[2,3], [3,3]\} $ , the score is $ 0 $ , because the point $ 3 $ is already contained in both planets' interval of vulnerability.
- For the subset $ \{[1,1], [2,3]\} $ , the score is $ 1 $ . By using one operation on changing the interval of vulnerability of the second planet to be $ [1,3] $ , the two planets now both have the point $ 1 $ in their interval.
- For the subset $ \{[1,1], [3,3]\} $ , the score is $ 2 $ . By using two operations on changing the interval of vulnerability of the first planet to be $ [1,3] $ , the two planets now both have the point $ 3 $ in their interval.
- For the subset $ \{[1,1], [2,3], [3,3]\} $ , the score is $ 2 $ . By using one operation on changing the interval of vulnerability of the first planet to be $ [1,2] $ and one operation on changing the interval of vulnerability of the third planet to $ [2,3] $ , all three planets will have the point $ 2 $ in their interval.

The sum of scores of all non-empty subsets of the first testcase is $ 0 \cdot 4 + 1 \cdot 1 + 2\cdot2 = 5 $ .

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5```

### 输出

```
5
6
24```

# 题解

## 作者：_abcd_ (赞：3)

## [[CF2030G2] The Destruction of the Universe](https://codeforces.com/problemset/problem/2030/G2)

考虑对于一个给定的集合，如何求出他的权值。一个很自然的方案是将左右端点离散化，然后枚举最后的交点，并求出一共需要多少步才能使得所有线段都包含这个点，并取最小值，即 $ \min\limits_{x} \sum\limits_{i=1}^n [ r_i \le x ] ( x - r_i ) + [ x < l_i ] ( l_i - x ) $。比较显然的是这个值取最小当且仅当 $ x $ 左边的线段的数量等于 $ x $ 右边线段的数量，但是由于一些线段的左端点可能重合，导致这两个数无法取等，因此考虑在离散化的时候错开这些端点。对右端点也一样。

现在回到这道题。我们考虑枚举点 $ x $，并枚举其左右有多少线段，并算出贡献。考虑将贡献拆到每个线段上，即钦定一个线段，然后枚举有多少种情况下会取到这个线段。而包含点 $ x $ 的线段就能随意取或不取。设 $ x $ 左边有 $ cnt_1 $ 条线段，右边有 $ cnt_2 $ 条线段，则答案为
$$ \sum\limits_{l_i > x} \sum\limits_{j \ge 1} \binom{cnt_1}{j} \binom{cnt_2 - 1}{j - 1} 2^{n - cnt_1 - cnt_2} l_i - \sum\limits_{r_i \le x} \sum\limits_{j \ge 1} \binom{cnt_1}{j} \binom{cnt_2 - 1}{j - 1} 2^{n - cnt_1 - cnt_2} r_i $$

$$ = 2^{n - cnt_1 - cnt_2} \left( \sum\limits_{l_i > x} l_i \sum\limits_{j \ge 1} \binom{cnt_1}{j} \binom{cnt_2 - 1}{j - 1} - \sum\limits_{r_i \le x} r_i \sum\limits_{j \ge 1} \binom{cnt_1 - 1}{j - 1} \binom{cnt_2}{j} \right) $$

注意到
$$ \sum\limits_{j \ge 1} \binom{cnt_1}{j} \binom{cnt_2 - 1}{j - 1} = \sum\limits_{j \ge 1} \binom{cnt_1}{j} \binom{cnt_2 - 1}{cnt_2 - j} = \binom{cnt_1 + cnt_2 - 1}{cnt_2} $$

因此上式
$$ = 2^{n - cnt_1 - cnt_2} \left( \sum\limits_{l_i > x} l_i \binom{cnt_1 + cnt_2 - 1}{cnt_2} - \sum\limits_{r_i \le x} r_i \binom{cnt_1 + cnt_2 - 1}{cnt_1} \right) $$

维护前缀后缀和就能 $ O(1) $ 算出。

但是这样会算重。因为对一个子集，可能有多个点使得他左右线段数量相等，考虑取最小的那个点，即存在一个线段，其左端点或右端点为 $ x $，这样当 $ x $ 继续减小时，会使左边的线段数 $ - 1 $，或右边的线段树 $ + 1 $。因此，只要钦定不选这样的线段，然后减去这样的方案数即可。复杂度为 $ O(n \log n) $，瓶颈在离散化。

---

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define fls() fflush(stdout)
#define maxn 2000005
#define int ll
#define mod 998244353
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
int ksm(int x,int y)
{
    int ret=1;
    while(y)
    {
        if(y&1)ret=ret*x%mod;
        x=x*x%mod,y>>=1;
    }
    return ret;
}
int n=2e6;
int jc[maxn],inv[maxn],mi[maxn];
int d1[maxn],d2[maxn],cnt[maxn];
pair<int,int>a[maxn];
void zh_init()
{
    jc[0]=1;
    for(int i=1;i<=n;i++)
        jc[i]=jc[i-1]*i%mod;
    inv[n]=ksm(jc[n],mod-2);
    for(int i=n;i;i--)
        inv[i-1]=inv[i]*i%mod;
    mi[0]=1;
    for(int i=1;i<=n;i++)
        mi[i]=mi[i-1]*2%mod;
}
int A(int x,int y)
{
    if(x<y)return 0;
    return jc[x]*inv[x-y]%mod;
}
int C(int x,int y)
{
    if(x<0)
        return 1;
    return A(x,y)*inv[y]%mod;
}
void solve()
{
    n=re();
    vector<int>tmp;
    for(int i=1;i<=n;i++)
    {
        int l=re(),r=re();
        tmp.push_back(l);
        tmp.push_back(r);
        a[i]={l,r};
    }
    sort(tmp.begin(),tmp.end());
    for(int i=0;i<tmp.size();i++)
    {
        d1[i]=d2[i]=0;
        cnt[i]=-1;
    }
    int cnt1=0,cnt2=n;
    int sum1=0,sum2=0;
    for(int i=1;i<=n;i++)
    {
        auto [l,r]=a[i];
        sum2+=l;
        l=lower_bound(tmp.begin(),tmp.end(),l)-tmp.begin();
        cnt[l]++;
        l+=cnt[l];
        r=lower_bound(tmp.begin(),tmp.end(),r)-tmp.begin();
        cnt[r]++;
        r+=cnt[r];
        d1[l]++,d2[r]++;
    }
    int ans=0;
    for(int i=0;i<tmp.size();i++)
    {
        cnt2-=d1[i];
        (sum2-=tmp[i]*d1[i])%=mod;
        (ans-=(C(cnt1+cnt2-1,cnt2)*sum2-C(cnt1+cnt2-1,cnt1)*sum1)%mod*mi[n-cnt1-cnt2-1])%=mod;
        cnt1+=d2[i];
        (sum1+=tmp[i]*d2[i])%=mod;
        (ans+=(C(cnt1+cnt2-1,cnt2)*sum2-C(cnt1+cnt2-1,cnt1)*sum1)%mod*mi[n-cnt1-cnt2])%=mod;
    }
    if(ans<0)
        ans+=mod;
    printf("%lld\n",ans);
}
signed main()
{
    zh_init();
    int T=re();
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：ForgotMe (赞：2)

场切了，爽！

首先得观察出如何快速求出一个集合的最小操作次数。

第一反应是可以建立一个函数 $f(x)=\sum_{i=1}^n [r_i\le x]x-r_i +\sum_{i=1}^n [x\le l_i] l_i-x$，表示所有线段都包含 $x$ 的最小操作次数。那么最小操作次数就是 $f(x)$ 的 min，这非常的不优美，根本没法计数。

考虑一个天才的想法：令 $g(x)=\sum_{i=1}^n |x-r_i|+|x-l_i|$，注意到 $g(x)-\sum_{i=1}^n (r_i-l_i)=2\times f(x)$，也就是说 $f(x)$ 取最小时，$g(x)$ 也取最小。而 $g(x)$ 具有非常明显的几何意义。那么结论就出来了，当 $f(x)$ 最小时，$x$ 一定取集合 $\{l_i,r_i\}$ 的中位数。

于是直接考虑枚举中位数进行计数，可惜非常恶心的一点是，集合 $\{l_i,r_i\}$ 中可能会存在相同的数，导致无法以一个简单的条件保证枚举的这个数是中位数。考虑对区间重编号：

```cpp
for(int i=1;i<=n;i++){
  G1[l[i]].push_back(i);
  G2[r[i]].push_back(i);
}
for(int i=1;i<=n;i++){
  for(auto x:G1[i])l2[x]=++cnt;
  for(auto x:G2[i])r2[x]=++cnt;
}
```
重编号的目的只是为了区分相同的数，对正确性并不会造成影响。那么剩下的问题就很简单了，枚举中位数 $x$ 后因为重编号的原因，只会存在一个区间以 $x$ 作为端点，其他区间一定是 $l^{'}_i<x<r^{'}_i$ 或 $r^{'}_i<x$ 或 $l^{'}_i>x$ 三种情况，显然包含 $x$ 的区间可以随便选，唯一的要求就是选的 $l^{'}_i<x$ 的区间个数与 $r^{'}_i>x$ 区间个数应相同（其实也不能这么说，因为还存在一个以 $x$ 作为端点的区间，需要分类讨论两者选择区间个数的限制）。

计算贡献是简单的，显然每个区间的贡献是独立的，可以分开计算，枚举一个 $l^{'}_i<x$ 的区间，表示其强制选，其造成的贡献就是 $y-l_i$（$y$ 表示 $x$ 的真实值，显然不能用重编号的值进行贡献的计算），然后只需计算合法的方案种数，这个方案数的计算可以发现是一个范德蒙德卷积（对下指标进行翻转就是标准形式了）。那么现在就可以做到 $\mathcal{O}(n^2)$。

给个 G1 的代码
```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define LL long long
#define pp pair<int,int>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
	//	return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
		return getchar();
	}
	template<class T> void gi(T& x){
		x=0; int f=1;char c=gc();
		if(c=='-')f=-1;
		for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
		x=x*f;
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x<0)pc('-'),x=-x;
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=998244353;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
	return 1ll*x*y%mod;
}
inline int qkpow(int a,int b){
	if(b<0)return 0;
	int ans=1,base=a%mod;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[1000005],inv[1000005],Invn[600005];
inline int binom(int n,int m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[n]=qkpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	Invn[0]=Invn[1]=1;
	for(int i=1;i<=200000;i++)Invn[i]=(LL)(mod-mod/i)*Invn[mod%i]%mod;
}
int t,n,cnt,l[1000005],r[1000005],l2[1000005],r2[1000005],rev[2000005],mi[1000005],res,fk[2000005];
vector<int>G1[1000005],G2[1000005]; 
inline void solve(){
	cnt=0;
	gi(n);
	mi[0]=1;
	for(int i=1;i<=n;i++)mi[i]=1ll*mi[i-1]*2%mod;
	for(int i=1;i<=n;i++)G1[i].clear(),G2[i].clear();
	for(int i=1;i<=n;i++)
		gi(l[i]),gi(r[i]);
	for(int i=1;i<=n;i++){
	    G1[l[i]].push_back(i);
	    G2[r[i]].push_back(i);
	}
	cnt=0;
	for(int i=1;i<=n;i++){
	    for(auto x:G1[i])l2[x]=++cnt,rev[cnt]=l[x],fk[cnt]=1;
	    for(auto x:G2[i])r2[x]=++cnt,rev[cnt]=r[x],fk[cnt]=2;
	}
	res=0;
	for(int i=1;i<=2*n;i++){
		int val=rev[i],pro=0,c1=0,c2=0,op=fk[i];
		for(int j=1;j<=n;j++){
			if(l2[j]<=i&&i<=r2[j])pro++;
			else{
				if(r2[j]<i)c1++;
				else if(l2[j]>i)c2++; 
			}
		}
		for(int j=1;j<=n;j++){
			if(l2[j]<=i&&i<=r2[j])continue;
			if(r2[j]<i){
				int val2=val-r[j];
				if(op==1)res=add(res,1ll*val2*mi[pro-1]%mod*binom(c1+c2-1,c1)%mod);
				else res=add(res,1ll*val2*mi[pro-1]%mod*binom(c1+c2-1,c1+1)%mod);
			}else if(l2[j]>i){
				int val2=l[j]-val;
				if(op==1)res=add(res,1ll*val2*mi[pro-1]%mod*binom(c1+c2-1,c2)%mod);
				else res=add(res,1ll*val2*mi[pro-1]%mod*binom(c1+c2-1,c2-1)%mod);
			}
		}
	}
	pi(res);
}
signed main(){
	srand(time(0));
	init_C(200000);
	gi(t);
	while(t--)solve();
	return 0;
} 
```

优化到 G2 是容易的，观察到方案数其实是固定的，跟强制选的区间是啥没什么关系，滚个前缀和即可。

G2 代码

```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define LL long long
#define pp pair<int,int>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
	//	return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
		return getchar();
	}
	template<class T> void gi(T& x){
		x=0; int f=1;char c=gc();
		if(c=='-')f=-1;
		for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
		x=x*f;
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x<0)pc('-'),x=-x;
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=998244353;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
	return 1ll*x*y%mod;
}
inline int qkpow(int a,int b){
	if(b<0)return 0;
	int ans=1,base=a%mod;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[2000005],inv[2000005],Invn[600005];
inline int binom(int n,int m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[n]=qkpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
//	Invn[0]=Invn[1]=1;
//	for(int i=1;i<=200000;i++)Invn[i]=(LL)(mod-mod/i)*Invn[mod%i]%mod;
}
int t,n,cnt,l[1000005],r[1000005],l2[1000005],r2[1000005],rev[2000005],mi[1000005],res,fk[2000005];
int s1[2000005],s2[2000005];
LL s3[2000005],s4[2000005];
vector<int>G1[1000005],G2[1000005]; 
inline void solve(){
	cnt=0;
	gi(n);
	mi[0]=1;
	for(int i=1;i<=n;i++)mi[i]=1ll*mi[i-1]*2%mod;
	for(int i=1;i<=n;i++)G1[i].clear(),G2[i].clear();
	for(int i=0;i<=2*n+1;i++)s1[i]=s2[i]=s3[i]=s4[i]=0;
	for(int i=1;i<=n;i++)
		gi(l[i]),gi(r[i]);
	for(int i=1;i<=n;i++){
	    G1[l[i]].push_back(i);
	    G2[r[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
	    for(auto x:G1[i])l2[x]=++cnt,rev[cnt]=l[x],fk[cnt]=1;
	    for(auto x:G2[i])r2[x]=++cnt,rev[cnt]=r[x],fk[cnt]=2;
	}
	for(int i=1;i<=n;i++){
		s1[r2[i]]++;
		s2[l2[i]]++;
		s3[r2[i]]=add(s3[r2[i]],r[i]);
		s4[l2[i]]=add(s4[l2[i]],l[i]);
	}
	for(int i=1;i<=2*n;i++)s1[i]+=s1[i-1],s3[i]=add(s3[i],s3[i-1]);
	for(int i=2*n-1;i>=1;i--)s2[i]+=s2[i+1],s4[i]=add(s4[i],s4[i+1]);
	res=0;
	for(int i=1;i<=2*n;i++){
		int val=rev[i],pro=0,c1=0,c2=0,op=fk[i];
		c1=s1[i-1],c2=s2[i+1];
		pro=n-c1-c2;
		int val2=dec(1ll*val*c1%mod,s3[i-1]);
		if(op==1)res=add(res,1ll*val2*mi[pro-1]%mod*binom(c1+c2-1,c1)%mod);
		else res=add(res,1ll*val2*mi[pro-1]%mod*binom(c1+c2-1,c1+1)%mod);
		val2=dec(s4[i+1],1ll*val*c2%mod);
		if(op==1)res=add(res,1ll*val2*mi[pro-1]%mod*binom(c1+c2-1,c2)%mod);
		else res=add(res,1ll*val2*mi[pro-1]%mod*binom(c1+c2-1,c2-1)%mod);
	}
	pi(res);
}
signed main(){
	srand(time(0));
	init_C(2000000);
	gi(t);
	while(t--)solve();
	return 0;
} 
```

---

## 作者：Deep_Kevin (赞：0)

首先我们可以先考虑如何求出一个集合的最小操作次数，发现是一个类似于中位数的东西，不妨建立一个函数 $f(x)=\sum_{i=1}^n [r_i\leq x](x-r_i)+\sum[x\leq l_i](l_i-x)$ 表示中位数为 x 时的代价。

经典转化：将单个 $i$ 的 $f(x)$  画出来可以发现是类似于两个距离相加的形式，令 $g(x)=\sum_{i=1}^{n}|x-r_i|+|x-l_i|$ ，注意到 $g(x)-\sum_{i=1}^n(r_i-l_i)=2f(x)$ ，所以只要最小化 $g(x)$ 就可以最小化 $f(x)$。

最小化 $g(x)$ 很简单，只要把 $x$ 取成 $\{l_i,r_i | 1\leq i\leq n\}$ 的中位数即可。

由于题目不保证端点不重合，所以我们先将其离散化，并对相同权值的端点赋予先后顺序，那么端点之间就被我们钦定了大小关系（值不变），为了保证每个集合选取 中位数 的唯一性，我们不妨假设 中位数 就是在 $\{l_i,r_i | 1\leq i\leq n\}$ 中，满足钦定大小关系的第 $n$ 个元素。

接下来我们就可以枚举 $x$ 来计算以它为中位数的集合的答案之和了。

除去 $x$ 所在的区间外，设 $r_i<x$ 的区间个数为 $cnt_1$，$x<l_i$ 的区间个数为 $cnt_2$，注意这里的大于和小于是我们钦定的大小关系。

分类讨论：

1. 假设 $x$ 是某个区间的左端点，那么 $cnt_1$ 中选取的区间 和 $cnt_2$ 中选取的区间应该相等。其他区间无所谓，随便选。
2. 假设 $x$ 是某个区间的右端点，那么 $cnt_1$ 中选取的区间应该要比 $cnt_2$ 中选取的区间少一个。其他区间无所谓，随便选。

那么就可以轻松写出下面的式子：

1. 

$$
\sum_{l_i > x} \sum_{j \geq 1} \binom{cnt_1}{j} \binom{cnt_2 - 1}{j - 1} 2^{n - cnt_1 - cnt_2-1} l_i 
\\- \sum_{r_i \leq x} \sum_{j \geq 1} \binom{cnt_1-1}{j-1} \binom{cnt_2}{j} 2^{n - cnt_1 - cnt_2-1} r_i
\\= 2^{n - cnt_1 - cnt_2-1} \left(
\sum_{l_i > x} l_i \sum_{j \geq 1} \binom{cnt_1}{j} \binom{cnt_2 - 1}{j - 1}
- \sum_{r_i \leq x} r_i \sum_{j \geq 1} \binom{cnt_1 - 1}{j-1} \binom{cnt_2}{j}
\right)
\\= 2^{n - cnt_1 - cnt_2-1} \left( \sum_{l_i > x} l_i \binom{cnt_1 + cnt_2 - 1}{cnt_2} - \sum_{r_i \leq x} r_i \binom{cnt_1 + cnt_2 - 1}{cnt_1} \right)
$$

2. 

$$
\sum_{l_i > x} \sum_{j \geq 1} \binom{cnt_1}{j-1} \binom{cnt_2 - 1}{j - 1} 2^{n - cnt_1 - cnt_2-1} l_i 
\\- \sum_{r_i \leq x} \sum_{j \geq 2} \binom{cnt_1-1}{j-2} \binom{cnt_2}{j} 2^{n - cnt_1 - cnt_2-1} r_i
\\-\sum_{j\geq1} \binom{cnt_1}{j-1} \binom{cnt_2}{j}2^{n-cnt_1-cn_2-1}x
\\= 2^{n - cnt_1 - cnt_2-1} \left(
\sum_{l_i > x} l_i \sum_{j \geq 1} \binom{cnt_1}{j} \binom{cnt_2 - 1}{j - 1}
\\- \sum_{r_i \leq x} r_i \sum_{j \geq 2} \binom{cnt_1 - 1}{j-2} \binom{cnt_2}{j}-\sum_{j\geq1} \binom{cnt_1}{j-1} \binom{cnt_2}{j}x
\right)

\\= 2^{n - cnt_1 - cnt_2-1} \left( \sum_{l_i > x} l_i \binom{cnt_1 + cnt_2 - 1}{cnt_2} \\- \sum_{r_i \leq x} r_i \binom{cnt_1 + cnt_2 - 1}{cnt_1+1} -x\binom{cnt_1 + cnt_2}{cnt_1+1}\right)
$$

就可以 $O(n)$ 完成这个任务，离散化可以桶排序。

---

