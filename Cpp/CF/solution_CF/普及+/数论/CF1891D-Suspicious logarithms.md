# Suspicious logarithms

## 题目描述

Let $ f $ ( $ x $ ) be the floor of the binary logarithm of $ x $ . In other words, $ f $ ( $ x $ ) is largest non-negative integer $ y $ , such that $ 2^y $ does not exceed $ x $ .

Let $ g $ ( $ x $ ) be the floor of the logarithm of $ x $ with base $ f $ ( $ x $ ). In other words, $ g $ ( $ x $ ) is the largest non-negative integer $ z $ , such that $ {f(x)}^{z} $ does not exceed $ x $ .

You are given $ q $ queries. The $ i $ -th query consists of two integers $ l_i $ and $ r_i $ . The answer to the query is the sum of $ g $ ( $ k $ ) across all integers $ k $ , such that $ l_i \leq k \leq r_i $ . Since the answers might be large, print them modulo $ {10^9 + 7} $ .

## 说明/提示

The table below contains the values of the functions $ f $ ( $ x $ ) and $ g $ ( $ x $ ) for all $ x $ such that $ 1 \leq x \leq 8 $ .

  $ x $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 7 $  $ 8 $  $ f $  $ 0 $  $ 1 $  $ 1 $  $ 2 $  $ 2 $  $ 2 $  $ 2 $  $ 3 $  $ g $  $ - $  $ - $  $ - $  $ 2 $  $ 2 $  $ 2 $  $ 2 $  $ 1 $

## 样例 #1

### 输入

```
12
4 6
4 7
4 8
4 100000
179 1000000000000000000
57 179
4 201018959
7 201018960
729 50624
728 50624
728 50625
729 50625```

### 输出

```
6
8
9
348641
41949982
246
1
0
149688
149690
149694
149692```

# 题解

## 作者：Neil_Qian (赞：6)

# CF1891D Suspicious logarithms 题解

## 题目描述

记 $f(x) = \lfloor \log_2(x) \rfloor,g(x) = \lfloor \log_{f(x)}x\rfloor$，$q$ 组询问，每个询问给定 $l,r$，求 $\sum \limits_{i=l}^r g(i)$。答案对 $10^9+7$ 取模。$q\le 10^5,l,r\le10^{18}$。

## 解决方案

不难发现，$f(x)$ 的取值并不多，只有 $60$ 种，不妨先枚举 $f(x)$，在计算贡献。显然，它的取值范围是 $2^{f(x)}\sim 2^{f(x)+1}-1$。而 $g(x)$ 的取值也不多，因为 $log_{f(x)}x$ 显然不会很大，打表发现最多只有 $10$ 种，再次枚举 $g(x)$，每个数的贡献为 $g(x)$，范围是 $l\sim r$，$2^{f(x)}\sim 2^{f(x)+1}-1$，$f(x)^{g(x)}\sim f(x)^{g(x)+1}-1$ 三条线段的交集，记长度为 $len$，则对答案的总贡献为 $len\times g(x)$。这样计算周期数量为 $600n$，注意有的地方要用`__int128`。实测加了快读后比 $O(q\log^2r)$ 要快一些。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;typedef __int128 i128;typedef long long ll;
const ll MOD=1e9+7;ll Q,l,r,L,R,fx,ans,p2[102];char c;
inline ll lenth(ll X1,ll X2,ll Y1,ll Y2,ll Z1,ll Z2){
	return max(min(min(X2,Y2),Z2)-max(max(X1,Y1),Z1)+1,(ll)0);
}
inline void read(ll &x){
	x=0,c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
inline void write(ll x){
	if(x>9)write(x/10);
	putchar((x%10)^48);
}
int main(){
	read(Q),p2[0]=1;
	for(int i=1;i<=60;i++)p2[i]=p2[i-1]*2;
	while(Q--){
		read(l),read(r),fx=1,ans=0;
		for(int i=1;i<=60;i++){
			fx=i;
			for(int j=1;j<=10;j++){
				L=fx,fx=min((i128)fx*i,(i128)1e18+1),R=fx-1,
				(ans+=j*lenth(L,R,p2[i],p2[i+1]-1,l,r)%MOD)%=MOD;
				if(fx>p2[i+1]-1||fx>r)break;
			}
		}
		write(ans),putchar('\n');
	}
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：3)

提供一种不需要差分，不需要二分的做法。

一个显然的结论是：设 $l=2^k,r = 2^{k+1}-1$，那么 $g(r) - g(l) \le 1$。证明非常简单：因为 $f(l)=f(r),g(l) \ge 2$，而 $r < 2l$，对于固定的底数 $y(y \ge 2)$ 区间内最多存在一个 $y$ 的正整数次幂 $y^k$，那么 $g(l) \to g(r)$ 的增量就显然不超过 $1$ 了。

我们枚举 $i=\log_2(x)$，记输入的 $l,r$ 为 $L,R$，我们首先计算 $l=\max(L,2^i),r = \min(R,2^{i+1}-1)$，并计算 $g(l) = \log_{i}l$。然后计算 $p = i^{g(l)+1}$，判断是否在该区间内。如果在，那么 $[l,p)$ 的答案为 $g(l)$，$[p,r]$ 的答案为 $g(l)+1$。时间复杂度 $\mathcal O(q \log^2V)$。

注意一些地方可能需要开 `__int128`。
```cpp
/**
 *    author: sunkuangzheng
 *    created: 01.11.2023 10:38:55
**/
#include<bits/stdc++.h>
using namespace std;
#define int __int128
#define ll long long
const int mod = 1e9+7;
ll t,ql,qr;int n,l,r;
int qp(int a,int b){
    int r = 1;
    for(;b;b >>= 1,a = a * a) if(b & 1) r = r * a;
    return r;
}int lg(int x,int y){
    int p = 0,s = 1;
    while(s <= y) s *= x,p ++;
    return p - 1;
}signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t --){
        cin >> ql >> qr,l = ql,r = qr;int ans = 0;
        for(int i = lg(2,l);i <= lg(2,r);i ++){
            int tl = max(l,(int)(1ll << i)),tr = min(r,(int)((1ll << (i + 1)) - 1));
            // cout << (ll)tl << " " << (ll)tr << " " << (ll)i << "\n";
            int rp = lg(i,tl),tp = qp(i,rp+1);
            if(tp > tr) ans = (ans + (tr - tl + 1) % mod * rp) % mod;
            else ans = (ans + (tp - tl) % mod * rp + (tr - tp + 1) % mod * (rp + 1)) % mod;
        }cout << (ll)(ans)  << "\n";
    }
}
```

---

## 作者：2020kanade (赞：2)

我们充分发扬人类智慧，由于 $f(x)$ 的性质过于优秀，只有不超过 $60$ 个不同的取值，我们直接按照这个性质对 $g(x)$ 进行一个表的打。

打表算法的设计依据：$f(x)^{g(x)}=x$，由两个函数的向下取整特性，我们可以将 $f(x)$ 与 $g(x)$ 视为分段函数，直接枚举二者的值即可不重不漏地完成打表，打表的时间复杂度是 $\Theta(\log V+B(g(x)))$，其中 $B(f(x))$ 是 $f(x)$ 在本题值域下的段数。

打表部分代码如下，其中 $\operatorname{spm}$ 是龟速幂：
```cpp
vector<pair<ll,ll> > gs;
void g(ll _x)
{
	i128 x=_x;
	ll p1=__lg(_x),p2=0;
	while(spm(p1,p2+1)<x) ++p2;
	if(spm(p1,p2+1)>x) gs.push_back(make_pair(x,p2));++p2;
	while(spm(p1,p2)<x*2ll) gs.push_back(make_pair(spm(p1,p2),p2)),++p2;
}
```
可以发现 $g(x)$ 在本题值域下只有 $72$ 段，可以直接暴力跳段进行前缀和计算，对每个段的值和起点、段长等信息在打表时可以直接预处理。

当然，如果想追求极致效率，二分 $x$ 落在哪一段也不是不行。

暴力跳段且预处理直接用龟速幂硬乘时间复杂度可以视为 $\Theta(\log^2 V+72q)$，如果真的闲可以求和时上二分以及预处理上快速幂，做到可以视为 $\Theta(2\log V+q\log \log V)$ 的时间复杂度。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=55;
using ll=long long;
using ull=unsigned ll;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
ll maxn=1e18;
int a[N];
i128 spm(i128 x,i128 y)
{
	i128 ret=1;
	while(y>0) ret*=x,y--;
	return ret;
}
vector<pair<ll,ll> > gs;
void g(ll _x)
{
	i128 x=_x;
	ll p1=__lg(_x),p2=0;
	while(spm(p1,p2+1)<x) ++p2;
	if(spm(p1,p2+1)>x) gs.push_back(make_pair(x,p2));++p2;
	while(spm(p1,p2)<x*2ll) gs.push_back(make_pair(spm(p1,p2),p2)),++p2;
}
ll sumg(ll x)
{
	int p=0;ll ans=0;
	if(x<=3) return 0;
	while(p<=71&&gs[p+1].first-1ll<=x)
	{
		ans=(ans+1ll*(((gs[p+1].first-gs[p].first+GEH)%GEH)*gs[p].second)%GEH)%GEH;
		++p;
	}
	ans=(ans+1ll*(((x-gs[p].first+1+GEH)%GEH)*gs[p].second)%GEH)%GEH;
	return ans;
}
ll ql,qr;
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.ans","w",stdout); 
	syncoff();
	for(int i=2;i<=60;++i) g(1ll<<i);
	cin>>q;
	while(q--) cin>>ql>>qr,cout<<(sumg(qr)-sumg(ql-1)+GEH)%GEH<<endl;
	return 0;
}
/*
1
999999999999999999 1000000000000000000
*/
```

---

## 作者：licn (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1891D)

打个表会发现 $f_i$ 最大是 $59$，$g_i$ 最大是 $10$。我们对区间进行分段，先按 $f_i$ 的值进行分段，因为 $f_i$ 是单调不增的所以可以将其分成 $59$ 段。对于每一段再按它的 $g_i$ 分，相同的 $f_i$ 最多有两种不同的 $g_i$（这个可以打表看出来也，也可以用数学证明：因为以 $2$ 为底 $i$ 的对数都是一样的，而 $f_i$ 都是大于等于 $2$ 的）。我们找到每个区间的分界点，最后将询问的区间拆分成不同的段，最多有 $118$ 个段。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int q,mult[100][100],k[100],s[100],w[100],z[100];
int cal(int x,int y){
	int num=0;
	for(int i=k[x];i;i--){
		if(num+i<=k[x]&&mult[x][num+i]<=y)num+=i;
	}
	return num;
}
signed main(){
	scanf("%lld",&q);
	for(int i=2;i<=60;i++){
		mult[i][0]=1,k[i]=60;
		for(int j=1;j<=60;j++){
			mult[i][j]=mult[i][j-1]*i;
			if(mult[i][j]<mult[i][j-1]){
				k[i]=j-1;
				break;
			}
		}
	}
	for(int i=2;i<=59;i++){
		for(int j=0;j<=k[i];j++){
			if(mult[i][j]>=mult[2][i]&&mult[i][j]<=mult[2][i+1]-1){
				s[i]=mult[i][j];
				break;
			}
		}
		w[i]=cal(i,mult[2][i]);
		if(s[i]==0)s[i]=mult[i][k[i]];
		if(w[i]==cal(i,mult[2][i+1]-1))s[i]=mult[2][i+1];
		z[i]=(s[i]-mult[2][i])*w[i]+(mult[2][i+1]-s[i])*(w[i]+1); 
	}
	while(q--){
		int l,r;
		scanf("%lld%lld",&l,&r);
		if(l<=3&&r<=3){
			printf("0\n");
			continue;
		}
		if(l<=3)l=4;
		int ans=0;
		for(int i=2;i<=59;i++){
			if(l<=mult[2][i]&&r>=mult[2][i+1]-1)ans+=z[i],ans%=mod;
			else if(l<=mult[2][i]&&r>=mult[2][i]){
				if(r<s[i]){
					ans+=(r-mult[2][i]+1)*w[i];
					ans%=mod;
				}
				else{
					ans+=(r-s[i]+1)*(w[i]+1);
					ans%=mod;
					ans+=(s[i]-mult[2][i])*w[i];
					ans%=mod;
				}
			}
			else if(r>=mult[2][i+1]-1&&l<=mult[2][i+1]-1){
				if(l<s[i]){
					ans+=(mult[2][i+1]-s[i])*(w[i]+1);
					ans%=mod;
					ans+=(s[i]-l)*w[i];
					ans%=mod;
				}
				else{
					ans+=(mult[2][i+1]-l)*(w[i]+1);
					ans%=mod;
				}
			}
			else if(l>=mult[2][i]&&r<mult[2][i+1]){
				if(l<s[i]&&r>=s[i]){
					ans+=(r-s[i]+1)*(w[i]+1);
					ans%=mod;
					ans+=(s[i]-l)*w[i];
					ans%=mod;
				}
				else if(l>=s[i])ans+=(r-l+1)*(w[i]+1),ans%=mod;
				else if(r<s[i])ans+=(r-l+1)*w[i],ans%=mod;
			}
		}
		printf("%lld\n",ans%mod);
	}
	return 0;
}
```


---

