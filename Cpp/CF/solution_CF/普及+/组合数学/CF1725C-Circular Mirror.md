# Circular Mirror

## 题目描述

Pak Chanek has a mirror in the shape of a circle. There are $ N $ lamps on the circumference numbered from $ 1 $ to $ N $ in clockwise order. The length of the arc from lamp $ i $ to lamp $ i+1 $ is $ D_i $ for $ 1 \leq i \leq N-1 $ . Meanwhile, the length of the arc between lamp $ N $ and lamp $ 1 $ is $ D_N $ .

Pak Chanek wants to colour the lamps with $ M $ different colours. Each lamp can be coloured with one of the $ M $ colours. However, there cannot be three different lamps such that the colours of the three lamps are the same and the triangle made by considering the three lamps as vertices is a right triangle (triangle with one of its angles being exactly $ 90 $ degrees).

The following are examples of lamp colouring configurations on the circular mirror.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/f662b018d5c25548ad3c12ebf7297c4fe9cddb27.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/d15118feff1296e48df6066dea2761fdbf3bbba3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/904b8c54d18751fcd9444e012c7c141ddaf812b7.png)Figure 1. an example of an incorrect colouring because lamps $ 1 $ , $ 2 $ , and $ 3 $ form a right triangleFigure 2. an example of a correct colouringFigure 3. an example of a correct colouringBefore colouring the lamps, Pak Chanek wants to know the number of distinct colouring configurations he can make. Count the number of distinct possible lamp colouring configurations, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, all correct lamp colouring configurations are $ [1, 1, 2, 1] $ , $ [1, 1, 2, 2] $ , $ [1, 2, 1, 2] $ , $ [1, 2, 2, 1] $ , $ [1, 2, 2, 2] $ , $ [2, 1, 1, 1] $ , $ [2, 1, 1, 2] $ , $ [2, 1, 2, 1] $ , $ [2, 2, 1, 1] $ , and $ [2, 2, 1, 2] $ .

## 样例 #1

### 输入

```
4 2
10 10 6 14```

### 输出

```
10```

## 样例 #2

### 输入

```
1 2
10```

### 输出

```
2```

# 题解

## 作者：yingkeqian9217 (赞：8)

## 前言

简单数学题，但是笔（蒟）者（蒻）调了好久（（

## 题目描述

一个圆上有 $N$ 个可染色的点，编号 $1$ 至 $N$。$N$ 号点和 $1$ 号点相邻。

你可以用 $M$ 种颜色将这些点染色。要求不能出现有三个同色点围成直角三角形。

请求出全部合法方案的总数，输出它模 $998\ 244\ 353$ 的值。

## 分析

首先考虑圆内接直角三角形的性质，可以发现直角三角形的斜边必定落在一条直径上，而且另一点可以任取。也就是说，只要有一条直径的两端点颜色均为 $c$，那么只要再有一点的颜色为 $c$，就能出现一对直角三角形。显然，在这种情况下，颜色 $c$ 就不能用了。

既然这题最重要的是直径，那么我们就可以考虑记录下可以连出直径的点对（即相对点对）的数量 $cnt$。一对点 $x,y$ 相对的充要条件是它们中间的弧长为圆周长的一半，即它们之间的区间和为总和的一半。当然，圆周长为奇数时时不存在这样的点的，注意特判。我们前缀和即可，用 `map` 记录一个前缀是否存在。几何意义就是计算这个点与点 $1$ 所夹的弧的长度。

此时，共有两类点——可以构成直径的 $2\times cnt$ 个，不可以构成直径的 $n-2\times cnt$ 个。

还是一样，既然最重要的是直径，那我们就枚举我们取的直径个数 $i$。即对于其中 $i$ 对直径点对，我们使它们颜色一样（同点对间相同，不同点对间不同），其他的 $cnt-i$ 个点对，颜色不同。那么我们要保证没有直角三角形，就要保证剩余点没有使用选中点对的 $i$ 种颜色的。

于是我们可以列出公式：

$ans_i=C_{cnt}^i\times A_m^{i}\times((m-i)\times(m-i-1))^{cnt-i}\times(m-i)^{n-2\times cnt}$

其中 $ans_i$ 表示取 $i$ 对点对对答案的贡献。

首先，先从 $cnt$ 对点对中选出 $i$ 对作为颜色一样的点对，再从 $m$ 种颜色中取出 $i$ 种，分别对应到 $i$ 对点对上，注意此处顺序有关，所以是选中点对的贡献是 $C_{cnt}^i\times A_m^{i}$。

然后，考虑未选中的 $cnt-i$ 对点对，每一对颜色不能一样，且不能和选中点对一样，所以是 $((m-i)\times(m-i-1))^{cnt-i}$。

最后是剩下的 $n-2\times cnt$ 对，也是不能和选中的 $i$ 对一样，是 $(m-i)^{n-2\times cnt}$。

这里还要注意一下 $i$ 的取值范围，下界是 $0$，因为能不取，注意上界应该是 $\min(m,cnt)$，因为一共只有 $m$ 种颜色，不然代入式子也是不合法的。

最后的最后，我们把式子简化，就得到了最终算式：

$ans=C_{cnt}^i\times A_m^{i}\times(m-i)^{n-cnt-i}\times(m-i-1))^{cnt-i}$

## AC CODE
```
#include<bits/stdc++.h>
#define maxn 2900001
#define A(x,y) fac[x]%Mod*inv[x-y]%Mod
#define C(x,y) fac[x]%Mod*inv[x-y]%Mod*inv[y]%Mod
#define len a[n]
const int Mod=998244353;
using namespace std;
typedef unsigned long long ll;
int n,m,cnt;
map<ll,ll>mp;
ll a[maxn],ans,inv[maxn],fac[maxn];
ll qpow(ll x,ll y){
	ll sum=1;
	while(y){
		if(y&1) sum=sum*x%Mod;
		x=x*x%Mod;
		y>>=1;
	}
	return sum;
}
void init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=m;i++) fac[i]=fac[i-1]*i%Mod;
	for(int i=1;i<=m;i++) inv[i]=qpow(fac[i],Mod-2);
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%u",&a[i]);
		mp[a[i]+=a[i-1]]=i;
	}
	init();
	if(len&1) goto Calc;
	for(int i=1;i<=n;i++)
	 if(mp[a[i]-len/2])
	  cnt++;
	Calc:for(int i=0;i<=min(m,cnt);i++)
	 ans=(ans+qpow(m-i,n-cnt-i)*qpow(m-i-1,cnt-i)%Mod*C(cnt,i)*A(m,i))%Mod;
	printf("%u\n",ans);
	return 0;
}`
```

---

## 作者：江户川·萝卜 (赞：2)

题意：

给定圆周上 $n$ 个点之间的距离，将这 $n$ 个点用 $m$ 中颜色染色，使得其中没有同色直角三角形的方案数，对 $998244353$ 取模。

---
我们在小学二年级就学过，圆中直角对直径，因此题意转化为不存在三个同色点，且其中两个同色点相对的情况的方案数。（相对即相连成直径。）

首先求出相对的点的对数，记为 $k$。

考虑其中有 $i$ 对点是同色（点对与点对之间互不同色），则这 $i$ 对点共 $\begin{pmatrix}k\\i\end{pmatrix}$ 种选择方法，$\begin{pmatrix}m\\i\end{pmatrix}$ 种选色方法，剩余点对有 $(m-i)^{k-i}(m-i-1)^{k-i}$ 种选色方法，剩余点有 $(m-i)^{n-2i}$ 种选色方法。

所以：

$$\text{ans}=\sum_{i=0}^{\operatorname{min}(m,k)}\begin{pmatrix}k\\i\end{pmatrix}\begin{pmatrix}m\\i\end{pmatrix}(m-i)^{k+n-2i}(m-i-1)^{k-i}$$

```cpp
#include<bits/stdc++.h>
#include<queue>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
#define mod 998244353ll
#define Mod 1000000007ll
#define pii pair<int,int>
#define ll long long
#define ull long long
using namespace std;
ll n,m;
ll d[300005],sum[300005];
ll qpow(ll a,int b){
	if(b==0) return 1;
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;b>>=1;
	}
	return ans;
}
ll facc[300005],inv[300005];
void solve(){
	cin>>n>>m;
	facc[0]=1;
	for(int i=1;i<=n;i++) facc[i]=facc[i-1]*i%mod;
	inv[n]=qpow(facc[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++) cin>>d[i],sum[i]=sum[i-1]+d[i];
	int j=1;
	if(sum[n]&1){
		cout<<qpow(m,n)<<'\n';
		return;
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		while(j<=n&&sum[j]-sum[i]<sum[n]/2) j++;
		if(sum[j]-sum[i]==sum[n]/2) cnt++;
	}
	ll ans=0;
	ll fac=1;
	for(int i=0;i<=cnt;i++){
		ans=(ans+fac*qpow(m-i,n-cnt*2)%mod*qpow(m-i,cnt-i)%mod*qpow(m-i-1,cnt-i)%mod*facc[cnt]%mod*inv[cnt-i]%mod*inv[i]%mod)%mod;
		//cout<<ans<<'\n';
		fac=(fac*(m-i))%mod;
	}
	cout<<ans<<'\n';
}
int main(){
	std::ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;T=1; 
	while(T--){
		solve();
	} 
}
```

---

## 作者：Siteyava_145 (赞：0)

想了四个小时才想出来。。。我菜啊。。。

题意：

给定圆上的 $n$ 个点，给这些点染上 $m$ 种颜色，使里面没有三顶点同色直角三角形的染色方法有几种？

圆的直径与圆周上一点可围成一个直角三角形，且圆内只有这一种内接直角三角形，所以我们只用考虑这种三角形。很显然当直径的两端点异色时，它产生的所有直角三角形都不同色。所以我们把目光放在端点同色的直径。

这时所有的点被分成了三类：同色直径（两个点），异色直径，单点。

我们先统计出所有直径的条数 $zj$。很简单，将他们距离 $1$ 号点
的距离存进 `map` 里（时间复杂度低，`map` 可以通过）。若有两点的距离之差 $\bmod \frac{C}{2}=0$，那么这两点就在一条直径上，计数器加 $1$。最终计数器的值即为 $zj$。

再枚举同色直径的条数。设其为 $eq$.

---

先求染同色直径的方案数：$C_{zj}^{eq}\times A_m^{eq}$，$C_{zj}^{eq}$ 表示从所有直径里面选同色直径的方案数；$A_m^{eq}$ 表示选择颜色的方法数。

再求染异色直径的方法数：可染颜色还剩下 $m-eq$ 种，每条直径上有两个点，所以单条直径染色方法数为 $(m-eq)(m-eq-1)$，共有 $zj-eq$ 条异色直径，所以总方法数为 $[(m-eq)(m-eq-1)]^{zj-eq}$。

最后染单点，同样可染颜色有 $m-eq$ 种，有 $n-2zj$ 个点，所以方案数为 $(m-eq)^{n-2zj}$。

将他们乘起来得到 $C_{zj}^{eq}\times A_m^{eq}\times[(m-eq)(m-eq-1)]^{zj-eq}\times (m-eq)^{n-2zj}$。

所以方案总数为 $\sum\limits_{eq=0}^{zj}C_{zj}^{eq}\times A_m^{eq}\times[(m-eq)(m-eq-1)]^{zj-eq}\times (m-eq)^{n-2zj}$.

代码：（`lucas` 定理求组合数快忘了，这里是用的这种方法求的）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
map<ll,int>mp;
ll p=998244353;
ll a[300005],fac[300005];
ll sum=0,ans;
ll fp(ll a,ll b,ll c){
	ll ans=1;
	while(b){
		if(b&1){
			ans=ans*a%c;
		}
		a=a*a%c;
		b>>=1;
	}
	return ans;
}
ll C(ll n,ll m){
	if(m>n)return 0;
	return (fac[n]*fp(fac[m],p-2,p)%p*fp(fac[n-m],p-2,p)%p)%p;
}
ll lucas(ll n,ll m){
	if(m==0)return 1;
	else return C(n%p,m%p)*lucas(n/p,m/p)%p;
}
int main(){
	fac[0]=1;
	for(int i=1;i<=300000;i++)fac[i]=(fac[i-1]*i)%998244353;
	int n,m;
	cin>>n>>m;
	
	ll zj=0,dis=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",a+i);
		sum+=a[i];
	} 
	if(sum%2==0){
		for(int i=1;i<=n;i++){
			if(mp[dis%(sum/2)]){
				zj++;
			}else mp[dis%(sum/2)]=1;
			dis+=a[i];
		}
	}
	ll aans=0;
	for(ll eq=0;eq<=zj;eq++){
		aans=(aans+lucas(zj,eq)%p*lucas(m,eq)%p*fac[eq]%p*fp((m-eq)*(m-eq-1)%p,zj-eq,p)%p*fp(m-eq,n-zj*2,p)%p)%p;
	}
	cout<<aans;
	return 0;
}
 
```


---

## 作者：Mariposa (赞：0)

题意：

给定圆上的 $n$ 个点，用 $m$ 种颜色染色，使得不存在同色直角，求方案数。

题解：

直径产生直角，则转化为若一种颜色若包含直径则只包含直径。

显然一个点最多只在一条直径上，则我们枚举有多少个只包含颜色的直径，计算剩下的方案数。

对于剩下的点：

- 对于一条不同色的直径，方案数为 $m(m-1)$；

- 对于不在直径上的点，没有任何限制，方案数位 $m$;

综上，设直径数为 $c$，则答案为 $\sum\limits_{i=0}^c \dbinom{m}{i} \dbinom{c}{i}i!((m-i)(m-i-1))^{c-i}(m-i)^{n-2c}$。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
#define ll long long
const int maxn=5e5+10;
const int mod=998244353;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,d[maxn];ll Sum,S[maxn];
map<ll,int>mp;
inline int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1ll*res*x%mod;
		y>>=1;x=1ll*x*x%mod;
	}return res;
}
int fac[maxn],ifc[maxn],inv[maxn],cnt,ans;
inline int com(int x,int y){return 1ll*fac[x]*ifc[y]%mod*ifc[x-y]%mod;} 
int main(){
	n=read(),m=read();
	fac[0]=ifc[0]=inv[1]=1;
	for(int i=2;i<=max(n,m);i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=max(n,m);i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=1;i<=max(n,m);i++)ifc[i]=1ll*ifc[i-1]*inv[i]%mod;
	for(int i=1;i<=n;i++)d[i]=read(),Sum+=d[i],S[i]=Sum,mp[Sum]=1;
	if(Sum%2==0){
		for(int i=1;i<=n;i++)
			cnt+=mp[S[i]+Sum/2];
	}//printf("cnt=%d\n",cnt);
	for(int i=0;i<=cnt;i++)
		ans=(ans+1ll*com(cnt,i)*com(m,i)%mod*fac[i]%mod*ksm(1ll*(m-i)*(m-i-1)%mod,cnt-i)%mod*ksm(m-i,n-2*cnt))%mod;
	printf("%d\n",ans);
    return 0;
}
```

---

