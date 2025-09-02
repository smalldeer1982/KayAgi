# [AGC050E] Three Traffic Lights

## 题目描述

有 $3$ 台信号灯，编号为 $1,\ 2,\ 3$。信号灯 $i$ 的工作模式为：“绿灯持续 $g_i$ 秒，红灯持续 $r_i$ 秒，绿灯持续 $g_i$ 秒，红灯持续 $r_i$ 秒，\ldots”，如此无限循环。

现在，$3$ 台信号灯同时变为绿灯。在接下来的 $ (g_1 + r_1)(g_2 + r_2)(g_3 + r_3) $ 秒内，所有信号灯同时为绿灯的总时间是多少秒？请将答案对 $998,244,353$ 取模后输出。

## 说明/提示

## 限制

- $1 \leq g_1, r_1, g_2, r_2, g_3, r_3 \leq 10^{12}$
- 输入中的所有值均为整数。

## 样例解释 1

在接下来的 $24$ 秒内：
- 信号灯 $1$ 绿灯的时间段为 $[0, 1],\ [2, 3],\ [4, 5],\ [6, 7],\ [8, 9],\ [10, 11],\ [12, 13],\ [14, 15],\ [16, 17],\ [18, 19],\ [20, 21],\ [22, 23]$。
- 信号灯 $2$ 绿灯的时间段为 $[0, 2],\ [3, 5],\ [6, 8],\ [9, 11],\ [12, 14],\ [15, 17],\ [18, 20],\ [21, 23]$。
- 信号灯 $3$ 绿灯的时间段为 $[0, 3],\ [4, 7],\ [8, 11],\ [12, 15],\ [16, 19],\ [20, 23]$。

因此，所有信号灯同时为绿灯的时间段为 $[0, 1],\ [4, 5],\ [6, 7],\ [10, 11],\ [12, 13],\ [16, 17],\ [18, 19],\ [22, 23]$，总共 $8$ 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 1 2 1 3 1```

### 输出

```
8```

## 样例 #2

### 输入

```
7 3 5 7 11 4```

### 输出

```
420```

## 样例 #3

### 输入

```
999999999991 999999999992 999999999993 999999999994 999999999995 999999999996```

### 输出

```
120938286```

# 题解

## 作者：jun头吉吉 (赞：4)

## 题意
给定 $g_1,r_1,g_2,r_2,g_3,r_3$，求：

$$
\sum_{i=0}^{(g_1+r_1)(g_2+r_2)(g_3+r_3)-1}\prod_{j=1}^3
[i\bmod (g_j+r_j)<g_j]$$

值域 $10^{12}$。

## 题解

令 $t_i=g_i,l_i=g_i+r_i$。

然后 $T=l_1l_2l_3,L=\mathrm{lcm}(l_1,l_2,l_3)$。我们只计算 $[0,L)$ 内的答案，最后乘上 $T/L$。

我们记 $(m_1,x_1,m_2,x_2,m_3,x_3)$ 合法当且仅当 $\exist t\in[0,\mathrm{lcm}(m_1,m_2,m_3)),\forall i\in\{1,2,3\},t\equiv x_i\bmod m_i$。

$[0,L)$ 内的答案实际上就是：
$$
\sum_{\forall i\in\{1,2,3\},x_i<t_i}[(l_1,x_1,l_2,x_2,l_3,x_3)\ \text{合法}]
$$
这个还是不好做。记 $\mathrm{ord}_pn$ 表示最大的 $a$ 满足 $p^a|n$，有结论：

> 若 $\mathrm{ord}_pm_1>\max(\mathrm{ord}_pm_2,\mathrm{ord}_pm_3)$，则 $(m_1,x_1,m_2,x_2,m_3,x_3)$ 合法当且仅当 $(m_1/p,x_1,m_2,x_2,m_3,x_3)$ 合法。

考虑证明。首先一个显然的结论是，如果对于任意素数 $p$，$(p^{\mathrm{ord}_pm_1},x_1,p^{\mathrm{ord}_pm_2},x_2,p^{\mathrm{ord}_pm_3},x_3)$ 合法，则 $(m_1,x_1,m_2,x_2,m_3,x_3)$ 合法。只需要用中国剩余定理合并一下即可。

然后 $(p^{a_1},x_1,p^{a_2},x_2,p^{a_3},x_3)$ 合法的充要条件是 $\forall i,j\in\{1,2,3\},x_i\equiv x_j\bmod p^{\min(a_i,a_j)}$。

那么如果 $\mathrm{ord}_pm_1>\max(\mathrm{ord}_pm_2,\mathrm{ord}_pm_3)$，那么让 $m_1$ 除 $p$ 合法性显然不变。

然后我们就能通过这个得到一组 $l_1',l_2',l_3'$ 使得对于任意 $x_1,x_2,x_3$，$(l_1,x_1,l_2,x_2,l_3,x_3)$ 合法性和 $(l_1',x_1,l_2',x_2,l_3',x_3)$ 相同。并且 $\mathrm{ord}_pm_i\le\max_{j\ne i}\mathrm{ord}_pm_j$。

这个有什么用呢。手玩一下发现，我们可以找到一组 $g,a,b,c$ 满足 $l_1'=gab,l_2'=gac,l_3'=gbc,n=\mathrm{lcm}(l_1',l_2',l_3')=gabc$。不妨设 $l_1'\le l_2'\le l_3'$，即 $a\le b\le c$，最后的答案就是：
$$
\sum_{i\in[0,n)}\prod_{j=1}^3\sum_{k\in[0,t_j)}[k\equiv i\bmod l_j']
$$
化简一下就是：
$$
\sum_{i\in[0,n)}\prod_{j=1}^3\left\lfloor\frac{t_j}{l_j'}\right\rfloor+[i\bmod l_j'<t_j\bmod l_j']
$$
拆项。考虑：
$$
\sum_{i\in[0,n)}\prod_{j=1}^3[i\bmod l_j'<t_j\bmod l_j']
$$
的项。其他项难度显然严格低于此部分。

满足 $i\bmod l_2'<t_2\bmod l_2'$ 的 $i$ 是 $a$ 个区间，$i\bmod l_3'<t_3\bmod l_3'$ 的是 $b$ 个区间，所以满足这两个条件的是 $\mathcal O(a+b)$ 个区间，对于每个区间可以 $\mathcal O(1)$ 计算有多少个满足 $i\bmod l_1'<t_1\bmod l_1'$。

$a\le b\le \sqrt{bc}\le \sqrt{2\times 10^{12}}$，可以通过。

## 代码

```cpp
mint L=1,T=1,val[3];
ll t[3],l[3],g,a,b,c,n;
map<ll,array<int,3>>cnt;
vector<pair<ll,ll>>pos1,pos2,pos;
inline mint calc(ll n){
	// i∈[0,n),i%l[0]<t[0]%l[0]
	ll bel=n/l[0],kk=n%l[0],tt=t[0]%l[0];
	return mint(bel)*tt+min(kk,tt);
}
inline mint calc(ll ql,ll qr){
	// i∈[ql,qr),i%l[0]<t[0]%l[0]
	return calc(qr)-calc(ql);
}
signed main(){
	L=T=1;
	for(int i=0;i<3;i++){
		read(t[i],l[i]),l[i]+=t[i];
		for(int j=2;j<N;j++)while(l[i]%j==0)cnt[j][i]++,l[i]/=j;
		if(l[i]>1)cnt[l[i]][i]++,l[i]=1;
	}
	for(auto[v,c]:cnt){
		T*=mint(v)^(c[0]+c[1]+c[2]);
		L*=mint(v)^max({c[0],c[1],c[2]});
		for(int i=0;i<3;i++)while(c[i]>max(c[(i+1)%3],c[(i+2)%3]))c[i]--;
		for(int i=0;i<3;i++)while(c[i]--)l[i]*=v;
	}
	for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(l[j]<l[i])swap(l[i],l[j]),swap(t[i],t[j]);
	g=__gcd(__gcd(l[0],l[1]),l[2]);
	a=__gcd(l[0],l[1])/g,b=__gcd(l[0],l[2])/g,c=__gcd(l[1],l[2])/g;
	n=g*a*b*c;
	for(ll i=0;i<n;i+=l[1])pos1.eb(i,i+t[1]%l[1]);
	for(ll i=0;i<n;i+=l[2])pos2.eb(i,i+t[2]%l[2]);
	for(int i=0,j=0;i<(int)pos1.size();i++){
		if(j)j--;
		while(j<(int)pos2.size()&&pos2[j].fi<pos1[i].se){
			ll ql=max(pos1[i].fi,pos2[j].fi);
			ll qr=min(pos1[i].se,pos2[j].se);
			if(ql<qr)pos.eb(ql,qr);
			j++;
		}
	}
	for(int i=0;i<3;i++)val[i]=t[i]/l[i];
	mint ans=n*val[0]*val[1]*val[2];
	for(int i=0;i<3;i++)ans+=val[(i+1)%3]*val[(i+2)%3]*(n/l[i])*(t[i]%l[i]);
	for(auto s:pos)ans+=val[0]*(s.se-s.fi);
	for(auto s:pos2)ans+=val[1]*calc(s.fi,s.se);
	for(auto s:pos1)ans+=val[2]*calc(s.fi,s.se);
	for(auto s:pos)ans+=calc(s.fi,s.se);
	writeln((ans*T/L).x);
}
```

---

## 作者：UltiMadow (赞：1)

记 $l_i=g_i+r_i$，$L=\operatorname{lcm}(l_1,l_2,l_3)$，则路灯经过 $L$ 单位时间会循环一次，我们只用考虑计算一次循环的答案，最后乘上 $\frac TL$ 即可

称六元组 $(m_1,x_1,m_2,x_2,m_3,x_3)$ 合法当且仅当存在时间 $t$ 满足 $t\equiv x_i\pmod {m_i}$

记 $f_p(x)$ 为质因子 $p$ 在 $x$ 中出现的次数

性质 1：若存在 $p|m_1\land p\not|m_2\land p\not|m_3$，则 $(m_1,x_1,m_2,x_2,m_3,x_3)$ 合法与 $(\frac{m_1}{p^k},x_1,m_2,x_2,m_3,x_3)$ 等价（其中 $k\le f_p(m_1)$）

证明：对于原六元组的合法时间 $t_0$，容易得到 $t_0\equiv x_1\pmod {m_1}\Rightarrow t_0\equiv x_1\pmod {\frac{m_1}{p^k}}$，即新六元组合法

对于新六元组的合法时间 $t_1$，容易得到 $t_1\equiv x_1\pmod {\frac{m_1}{p^k}}$，取 $t_1=x_1+p^k\frac{m_1}{p^k}$ 即可满足 $t_1\equiv x_1\pmod{m_1}$，即原六元组合法

性质 2：若存在 $p|m_1\land p|m_2$ 且 $k_1\le k_2$（其中 $k_1=f_p(m_1),k_2=f_p(m_2)$），则 $(m_1,x_1,m_2,x_2,m_3,x_3)$ 合法与 $(\frac{m_1}{p^{k_1}},x_1,m_2,x_2,m_3,x_3)$ 合法且 $x_1\equiv x_2\pmod {p^{k_1}}$ 等价

证明：若原六元组合法，则显然要求 $x_1\equiv x_2\pmod {p^{k_1}}$

对于原六元组的合法时间 $t_0$，容易得到 $t_0\equiv x_1\pmod {m_1}\Rightarrow t_0\equiv x_1\pmod {\frac{m_1}{p^{k_1}}}$，即新六元组合法

对于新六元组的合法时间 $t_1$，容易得到 $t_1\equiv x_1\pmod {\frac{m_1}{p^{k_1}}}$，由于 $\gcd(p^{k_1},\frac{m_1}{p^{k_1}})=1$，可得一定存在满足条件的 $t_1$ 使得 $t_1\equiv x_1\pmod{p^{k_1}}$，此时一定有 $t_1\equiv x_1\pmod {m_1}$，即原六元组合法

但是性质 2 中 $x_1\equiv x_2\pmod {p^{k_1}}$ 的限制太麻烦了，考虑把它去掉

性质 3：若存在 $p$ 使得 $k_1>\max\{k_2,k_3\}$（其中 $k_i=f_p(m_i)$），则 $(m_1,x_1,m_2,x_2,m_3,x_3)$ 合法与 $(\frac{m_1}{p^{k_1-\max\{k_2,k_3\}}},x_1,m_2,x_2,m_3,x_3)$ 合法等价

证明：由性质 2 可得 $(m_1,x_1,m_2,x_2,m_3,x_3)$ 合法与 $(m_1,x_1,\frac{m_2}{p^{k_2}},x_2,\frac{m_3}{p^{k_3}},x_3)$ 合法且 $x_1\equiv x_2\pmod {p^{k_2}}\land x_1\equiv x_3\pmod{p^{k_3}}$ 等价

由性质 1 可得 $(m_1,x_1,\frac{m_2}{p^{k_2}},x_2,\frac{m_3}{p^{k_3}},x_3)$ 合法与 $(\frac{m_1}{p^{k_1-\max\{k_2,k_3\}}},x_1,\frac{m_2}{p^{k_2}},x_2,\frac{m_3}{p^{k_3}},x_3)$ 合法等价

逆用一下性质 2 可得 $(\frac{m_1}{p^{k_1-\max{k_2,k_3}}},x_1,\frac{m_2}{p^{k_2}},x_2,\frac{m_3}{p^{k_3}},x_3)$ 合法且 $x_1\equiv x_2\pmod {p^{k_2}}\land x_1\equiv x_3\pmod{p^{k_3}}$ 与 $(\frac{m_1}{p^{k_1-\max{k_2,k_3}}},x_1,m_2,x_2,m_3,x_3)$ 合法等价

回到原题，考虑计算合法六元组 $(l_1,x_1,l_2,x_2,l_3,x_3)$ 的数量

先根据性质 3 调整一下 $l_1,l_2,l_3$，调整之后一定有 $l_1=gab,l_2=gac,l_3=gbc$，不妨设 $l_1\le l_2\le l_3$，记 $n=gabc$

由于一个合法六元组和一个在 $[0,L)$ 中的时间一一对应，则考虑枚举这个时间

容易发现答案等于这一个式子：$\sum\limits_{t\in [0,n)}\prod\limits_{i=1}^3\sum\limits_{t\equiv j\pmod {l_i}\land j\in[0,g_i)}1$

化简一下可得： $\sum\limits_{t\in [0,n)}\prod\limits_{i=1}^3(\lfloor\frac{g_i}{l_i}\rfloor+[t\bmod l_i< g_i\bmod l_i])$

把后面的连乘展开成 $8$ 项相加，其中 $\lfloor \frac{g_i}{l_i}\rfloor$ 容易处理，主要是处理 $[t\bmod l_i<g_i\bmod l_i]$

考虑对于 $l_2,l_3$ 在 $[0,n)$ 中枚举符合 $[t\bmod l_i<g_i\bmod l_i]$ 的区间，容易发现有 $\mathcal O(a+b)$ 个区间；同样地，它们的并也有 $\mathcal O(a+b)$ 个区间

考虑暴力枚举这些区间，即可算出最终的答案

记值域为 $w$，则 $a\le b\le \sqrt{bc}\le\sqrt{l_3}\le \sqrt w$，所以总复杂度 $\mathcal O(\sqrt w)$

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define p 998244353
#define MAXN 2000010
#define pii pair<int,int>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
const int N=2000000; 
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
int qpow(int x,int y){
	int ret=1;
	for(;y;y>>=1,x=x*x%p)if(y&1)ret=ret*x%p;
	return ret;
}
int n,T,L,ans;
int t[3],l[3],rest[3];
int cnt[3],val[3];
int g,a,b,c;
vector<pii>pos1,pos2,pos;
int pri[MAXN],tag[MAXN],tot;
void euler(){
	for(int i=2;i<=N;i++){
		if(!tag[i])pri[++tot]=i;
		for(int j=1;j<=tot&&pri[j]*i<=N;j++){
			tag[pri[j]*i]=1;
			if(!(i%pri[j]))break;
		}
	}
}
int calc(int ql,int qr){
	int kl=ql/l[0],kr=qr/l[0];
	int pl=ql%l[0],pr=qr%l[0],pt=t[0]%l[0];
	if(kl==kr)return ((min(pr,pt)-min(pl,pt))%p+p)%p;
	return ((min(pr,pt)-min(pl,pt)+pt%p*((kr-kl)%p))%p+p)%p;
}
signed main(){
	euler();
	for(int i=0;i<3;i++){
		scanf("%lld%lld",&t[i],&l[i]);
		l[i]+=t[i];rest[i]=l[i];
		for(int j=1;j<=tot;j++)
			while(!(rest[i]%pri[j]))rest[i]/=pri[j];
	}
	T=L=1;for(int i=0;i<3;i++)T=l[i]%p*T%p;
	for(int i=0;i<3;i++){
		bool fl=0;
		for(int j=0;j<i;j++)fl|=(rest[i]==rest[j]);
		if(!fl)L=rest[i]%p*L%p;
		for(int j=i+1;j<3;j++)fl|=(rest[i]==rest[j]);
		if(!fl)l[i]/=rest[i];
	}
	for(int i=1;i<=tot;i++){
		memset(cnt,0,sizeof(cnt));
		for(int j=0;j<3;j++){
			int now=l[j];
			while(!(now%pri[i]))now/=pri[i],cnt[j]++;
		}
		L=L*qpow(pri[i],max(cnt[0],max(cnt[1],cnt[2])))%p;
		while(cnt[0]>max(cnt[1],cnt[2]))l[0]/=pri[i],cnt[0]--;
		while(cnt[1]>max(cnt[0],cnt[2]))l[1]/=pri[i],cnt[1]--;
		while(cnt[2]>max(cnt[0],cnt[1]))l[2]/=pri[i],cnt[2]--;
	}
	if(l[0]>l[1])swap(l[0],l[1]),swap(t[0],t[1]);
	if(l[1]>l[2])swap(l[1],l[2]),swap(t[1],t[2]);
	if(l[0]>l[1])swap(l[0],l[1]),swap(t[0],t[1]);
	g=gcd(gcd(l[0],l[1]),l[2]);a=gcd(l[0],l[1])/g;b=gcd(l[0],l[2])/g;c=gcd(l[1],l[2])/g;
	n=g*a*b*c;
	for(int i=0;i<n;i+=l[1])pos1.pb(mp(i,i+t[1]%l[1]));
	for(int i=0;i<n;i+=l[2])pos2.pb(mp(i,i+t[2]%l[2]));
	int s1=pos1.size(),s2=pos2.size();
	for(int i=0,j=0;i<(int)s1;i++){
		if(j)j--;
		for(;j<s2&&pos2[j].fi<pos1[i].se;j++){
			int ql=max(pos1[i].fi,pos2[j].fi);
			int qr=min(pos1[i].se,pos2[j].se);
			if(ql<qr)pos.pb(mp(ql,qr));
		}
	}
	for(int i=0;i<3;i++)val[i]=t[i]/l[i]%p;
	ans=n%p*val[0]%p*val[1]%p*val[2]%p;
	ans=(ans+val[0]*val[1]%p*(n/l[2]%p*(t[2]%l[2]%p)%p))%p;
	ans=(ans+val[0]*val[2]%p*(n/l[1]%p*(t[1]%l[1]%p)%p))%p;
	ans=(ans+val[1]*val[2]%p*(n/l[0]%p*(t[0]%l[0]%p)%p))%p;
	int sum=0;
	for(auto i:pos)sum=(sum+i.se-i.fi)%p;
	ans=(ans+sum*val[0])%p;sum=0;
	for(auto i:pos2)sum=(sum+calc(i.fi,i.se))%p;
	ans=(ans+sum*val[1])%p;sum=0;
	for(auto i:pos1)sum=(sum+calc(i.fi,i.se))%p;
	ans=(ans+sum*val[2])%p;
	for(auto i:pos)ans=(ans+calc(i.fi,i.se))%p;
	printf("%lld",ans*T%p*qpow(L,p-2)%p);
	return 0;
}
```

---

