# [ARC154F] Dice Game

## 题目描述

有一个 $N$ 面的骰子，每一面的出现概率都相等。你需要不断掷骰子，直到所有的面都至少出现过一次为止。

对于满足 $1 \le i \le M$ 的每个整数 $i$，请你求出“掷骰子的次数的 $i$ 次幂”的期望值，并对 $998244353$ 取模。

期望值 $\bmod\ 998244353$ 的定义：可以证明，所求的期望值一定是有理数。在本题的约束下，将其表示为最简分数 $\frac{P}{Q}$ 时，$Q \not\equiv 0 \pmod{998244353}$ 也成立。因此，存在唯一的整数 $R$ 满足 $R \times Q \equiv P \pmod{998244353},\ 0 \le R < 998244353$。请输出这个 $R$。

## 说明/提示

### 限制条件

- $1 \le N, M \le 2 \times 10^5$
- 输入均为整数。

### 样例解释 1

当 $i=1$ 时，所求的期望值是所有面都出现所需的操作次数。这个值是 $\frac{11}{2}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3```

### 输出

```
499122182
37
748683574```

## 样例 #2

### 输入

```
7 8```

### 输出

```
449209977
705980975
631316005
119321168
62397541
596241562
584585746
378338599```

## 样例 #3

### 输入

```
2023 7```

### 输出

```
442614988
884066164
757979000
548628857
593993207
780067557
524115712```

# 题解

## 作者：Kubic (赞：6)

口胡题解，有错误欢迎指出。

设 $F(x)$ 为恰好 $i$ 轮满足条件的概率生成函数。可以发现我们需要求的是 $F(e^x)$ 的前 $m$ 次项系数。

那么可以得到：

$$\operatorname{EGF}(F(x))=x(e^{\frac{x}{n}}-1)^{n-1}$$

其意义是最后一个数一定是第一次被随机到，统计剩下的 $n-1$ 种数的方案数。

$$\operatorname{EGF}(F(x))=x(e^{\frac{x}{n}}-1)^{n-1}$$

$$\sum\limits_{i=0}^{n-1}(-1)^{n-i-1}\dbinom{n-1}{i}xe^{\frac{ix}{n}}$$

我们考虑通过 $\operatorname{EGF}(F(x))$ 推出 $F(x)$：

关注其中一部分的 $\operatorname{EGF}$ 为：

$$xe^{\frac{ix}{n}}=\sum\limits_{j=0}^{\infty}\dfrac{\left(\dfrac{i}{n}\right)^jx^{j+1}}{j!}$$

那么它的 $\operatorname{OGF}$ 为：

$$\sum\limits_{j=0}^{\infty}\left(\dfrac{i}{n}\right)^j(j+1)x^{j+1}$$

$$=\dfrac{n}{i}\sum\limits_{j=0}^{\infty}j\left(\dfrac{ix}{n}\right)^j$$

$$=\dfrac{x}{(1-\dfrac{ix}{n})^2}$$

因此可以推出 $F(x)$ 的表达式：

$$\sum\limits_{i=0}^{n-1}(-1)^{n-i-1}\dbinom{n-1}{i}\dfrac{x}{(1-\dfrac{ix}{n})^2}$$

因为 $e^x$ 的常数项为 $1$，所以我们可以只保留 $F(x+1)$ 的前 $m$ 次项系数。

而 $F(x+1)$ 是 $O(n)$ 个分子分母的次数不超过 $2$ 的有理分式的线性组合，所以它的分子分母的次数是 $O(n)$ 的。可以通过分治 FFT 计算得到分子分母，进而通过多项式求逆得到它的前 $m$ 次项系数。设为 $\mathcal{F}(x+1)$。

有了 $\mathcal{F}(x+1)$，我们可以通过一次卷积得到 $\mathcal{F}(x)$。只需要求出 $\mathcal{F}(e^x)$ 即可。

显然 $\mathcal{F}(x)$ 的次数不超过 $m$。设 $\mathcal{F}(x)=\sum\limits_{i=0}^{\infty}a_ix^i$。

我们相当于要求出：

$$\sum\limits_{i=0}^m\dfrac{a_i}{1-ix}$$

而这与上面一部分类似，也可以通过分治 FFT 解决。

时间复杂度 $O(n\log^2 n)$。

---

## 作者：Otomachi_Una_ (赞：5)

**[ARC154F] Dice Game（9）**

本篇题解部分译自 Atcoder 的 [另解](https://atcoder.jp/contests/arc154/editorial/5566)。翻译有问题请私信联系修改。

我们先介绍矩母函数：对于一个随机非负实数变量 $X$，定义其矩母函数 

$$
M_X(x)=\sum_{i=0}^\infty\dfrac{E(X^i)}{i!}x^i
$$

（性质 1）$M_{X+Y}=M_X\times M_Y$。

> 证明：
> $$
 E[(x+y)^n]=E[\sum_{i=0}^n\binom ni x^iy^{n-i}]=\sum_{i=0}^n\binom ni E[x^i]E[y^{n-i}]
 $$

下面我们讲讲从概率生成函数转矩母函数的方法：

（性质2）$X$ 的概率生成函数 $P(x)$，那么矩母函数就是 $P(e^x)$。

> 证明：假设 $P(x)=\sum_{i=0}^\infty p_ix^i$。则 
> $$
 P(e^x)=\sum_{i=0}^\infty p_i\sum_{j=0}^\infty \frac{(ix)^j}{j!}
 $$
> 则
> $$
 [x^n]P(e^x)=\dfrac{\sum_{i=0}^\infty i^n\times p_i}{n!}
 $$

我们知道了矩母函数，那么这道题是简单的。假设随机变量 $X_i$ 表示从当前已经选过 $i$ 种面值，选新的一种的个数。那么 $X_i$ 的概率生成函数是 $F_i(x)=p_ix+(1-p_i)p_ix^2+(1-p_i)^2p_ix^3\dots=\dfrac{p_ix}{1-(1-p_i)x}$。其中 $p_i=\dfrac{n-i}{n}$。

我们相当于求 
$$
\prod_{i=0}^{n-1} F_i(e^x)=\prod \dfrac{p_ie^x}{1-(1-p_i)e^x}
$$
的前 $m$ 项。这个式子显然可以写成 $\frac{G(e^x)}{H(e^x)}$ 的形式。其中 $G,H$ 都只有有限项。我们直接把 $G(x),H(x)$ 转成 $G(e^x),H(e^x)$，截取前 $m$ 项，直接多项式求逆即可。

> 关于 $F(x)$ 转 $F(e^x)$：
>
> 假设 $F(x)=\sum_{i=0}^n f_ix_i$。则：
> $$
 F(e^x)=\sum_{i=0}^n f_i e^{ix}=\sum_{i=0}^n f_i\sum_{j=0}^\infty \dfrac{(ix)^j}{j!}=\sum_{j=0}^\infty \dfrac{\sum_{i=0}^n f_i\times i^j}{j!}·x^j
 $$
> 于是我们只要快速对每个 $j$ 求出 $\sum_{i=0}^n f_i\times i^j$ 即可。我们发现这个对 $j$ 的生成函数写出来就是 $\sum_{i=0}^n \frac{f_i}{1-ix}$。直接分治 NTT 即可。

下面给出完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define LL __int128
#define MP make_pair
#define vll vector<long long>
const int MAXN=1e6+5;
const int MOD=998244353;
const ll inv2=(MOD+1)/2;
ll fac[MAXN],inf[MAXN]; 
namespace polynomial{// yjl poly plank 5.0 ver
int bfly[MAXN];ll inver[MAXN];
int clogg(int x){return (int)ceil(log2(x));} 
ll ksm(ll a,int b){ll res=1;while(b){if(b&1)res=res*a%MOD;a=a*a%MOD,b>>=1;}return res;}
void butterfly(int l){
	static int las;
	if(las!=l){
		las=l; 
		for(int i=1;i<(1<<l);i++)
			bfly[i]=(bfly[i>>1]>>1)|((i&1)<<l-1);
	} 
}
void NTT(vll &f,int l,int typ){
	butterfly(l);f.resize(1<<l);
	for(int i=0;i<(1<<l);i++)
		if(bfly[i]<i) swap(f[i],f[bfly[i]]);
	for(int i=0;i<l;i++){
		ll step=ksm(3,MOD-1+(MOD-1>>i+1)*typ);
		for(int j=0;j<(1<<l);j+=(1<<i+1)){
			ll cur=1,l=j+(1<<i);
			for(int k=j;k<l;k++){
				ll u=f[k],v=f[k|(1<<i)]*cur%MOD;
				f[k]=(u+v>MOD?u+v-MOD:u+v);
				f[k|(1<<i)]=(u>=v?u-v:u-v+MOD);
				cur=cur*step%MOD;
			}
		}
	}
	if(typ==-1){
		ll val=ksm(1<<l,MOD-2);
		for(int i=0;i<(1<<l);i++)
			f[i]=val*f[i]%MOD;
	}
	return;
}
vll operator *(vll f,vll g){
	int n=f.size()+g.size(),l=clogg(f.size()+g.size());
	if(n<=64){
		vll h(n-1);
		for(int i=0;i<f.size();i++)
			for(int j=0;j<g.size();j++)
				h[i+j]+=f[i]*g[j]%MOD;
		for(ll &i:h) i%=MOD;
		return h;
	}
	NTT(f,l,1);NTT(g,l,1);
	for(int i=0;i<(1<<l);i++)
		f[i]=f[i]*g[i]%MOD;
	NTT(f,l,-1);f.resize(n-1);
	return f;
}
vll operator +(vll f,vll g){
	int n=max(f.size(),g.size());
	f.resize(n);g.resize(n);
	for(int i=0;i<n;i++)
		f[i]=(f[i]+g[i]>=MOD?f[i]+g[i]-MOD:f[i]+g[i]);
	return f;
}
vll inv(vll f,int st=1){
	int n=f.size(),l=clogg(n);
	f.resize(1<<l);
	vll g{ksm(f[0],MOD-2)},_f;
	for(int i=st;i<=l;i++){
		_f=vll(begin(f),begin(f)+(1<<i));
		NTT(g,i+1,1);NTT(_f,i+1,1);
		for(int j=0;j<(1<<i+1);j++)
			g[j]=(2*g[j]-g[j]*g[j]%MOD*_f[j]%MOD+MOD)%MOD;
		NTT(g,i+1,-1);
		fill(begin(g)+(1<<i),end(g),0);
	}
	g.resize(n);
	return g;
}
vll integ(vll f){
	int n=f.size();f.resize(n+1);
	if(!inver[1]){
		for(int i=1;i<MAXN;i++) inver[i]=ksm(i,MOD-2);
	}
	for(int i=n;i>=1;i--) f[i]=f[i-1]*inver[i]%MOD;
	f[0]=0;
	return f;
}
vll diff(vll f){
	int n=f.size();
	for(int i=0;i<n-1;i++)
		f[i]=f[i+1]*(i+1)%MOD;
	f.pop_back();
	return f;
} 
vll ln(vll f){
	vll f_=diff(f),_f=inv(f);
	int n=f_.size(),m=_f.size();
	int l=clogg(n+m);
	NTT(f_,l,1);NTT(_f,l,1);
	for(int i=0;i<(1<<l);i++)
		f_[i]=f_[i]*_f[i]%MOD;
	NTT(f_,l,-1);
	f_=integ(f_);
	f_.resize(f.size());
	return f_;
}
vll exp(vll f){
	vll g{1},_f,_g;
	int n=f.size(),l=clogg(n);
	f.resize(1<<l);
	for(int i=1;i<=l;i++){
		_f=vll(begin(f),begin(f)+(1<<i));
		_g=ln(g);
		NTT(g,i+1,1);NTT(_f,i+1,1);NTT(_g,i+1,1);
		for(int j=0;j<(1<<i+1);j++)
			g[j]=g[j]*(1-_g[j]+_f[j]+MOD)%MOD;
		NTT(g,i+1,-1);
		fill(begin(g)+(1<<i),end(g),0);
	}
	g.resize(n);
	return g;
}
vll sqrt(vll f){
	vll g{1},_f,_g;
	int n=f.size(),l=clogg(n);
	f.resize(1<<l);
	for(int i=1;i<=l;i++){
		_f=vll(begin(f),begin(f)+(1<<i));
		_g=inv(g);
		NTT(_f,i+1,1);NTT(_g,i+1,1);NTT(g,i+1,1);
		for(int j=0;j<(1<<i+1);j++)
			g[j]=(_f[j]+g[j]*g[j]%MOD)*inv2%MOD*_g[j]%MOD;
		NTT(g,i+1,-1);
		fill(begin(g)+(1<<i),end(g),0);
	}
	g.resize(n);
	return g;
} 
void div(vll f,vll g,vll &q,vll &r){// 构造 p,q 使得 f=g*q+r; 
	int n=f.size()-1,m=g.size()-1;
	reverse(f.begin(),f.end());
	reverse(g.begin(),g.end());
	g.resize(n+1);
	q=(f*inv(g));q.resize(n-m+1);
	reverse(q.begin(),q.end());
	g.resize(m+1);
	reverse(g.begin(),g.end());
	reverse(f.begin(),f.end());
	vll h=q*g;
	r.resize(m);
	for(int i=0;i<m;i++) r[i]=(f[i]-h[i]+MOD)%MOD;
	return;
}
vll eval(vll f,vll x){
	vector<vll> func; map<pair<int,int>,int> mp;
	function<vll(int,int)> prod=[&](int l,int r){
		vll ans;
		if(l==r) ans=(vll){MOD-x[l],1};
		else {
			int mid=l+r>>1;
			ans=prod(l,mid)*prod(mid+1,r);
		} 
		func.push_back(ans);
		mp[MP(l,r)]=func.size()-1;
		return ans;
	};prod(0,x.size()-1);
	int t=-1;
	function<vll(vll,int,int)> solve=[&](vll f,int l,int r){
		if(l==r){
			ll val=0;
			for(int i=f.size()-1;i>=0;i--)
				val=(val*x[l]+f[i])%MOD;
			return (vll){val};
		}
		int mid=l+r>>1;
		vll p0=func[mp[MP(l,mid)]],p1=func[mp[MP(mid+1,r)]];
		vll d,q;
		div(f,p0,d,q);
		vll ans=solve(q,l,mid);
		div(f,p1,d,q);
		vll _ans=solve(q,mid+1,r);
		for(int i:_ans) ans.push_back(i);
		return ans;
	};
	return solve(f,0,x.size()-1);
}
}using namespace polynomial;
mt19937 rnd(time(0));
void init(){
	fac[0]=inf[0]=1;
	for(int i=1;i<MAXN;i++)
		inf[i]=ksm(fac[i]=fac[i-1]*i%MOD,MOD-2);
}
int n,m;ll p[MAXN];
vll solve(int l,int r){
	if(l==r) return vll{1,p[l]-1};
	int mid=l+r>>1;
	return solve(l,mid)*solve(mid+1,r);
}
vll to_ex(vll f){
	int n=f.size();
	function<pair<vll,vll>(int,int)> solve=[&](int l,int r){
		if(l==r) return MP(vll{f[l]},vll{1,MOD-l});
		int mid=l+r>>1;
		auto ls=solve(l,mid),rs=solve(mid+1,r);
		return MP(ls.first*rs.second+ls.second*rs.first,ls.second*rs.second);
	};
	auto ans=solve(0,n-1);
	vll g=ans.first*inv(ans.second);
	g.resize(n);
	for(int i=0;i<n;i++) g[i]=g[i]*inf[i]%MOD; 
	return g;
}
int main(){
	ios::sync_with_stdio(false);
	init();
	cin>>n>>m;
	for(int i=0;i<n;i++) p[i]=(n-i)*ksm(n,MOD-2)%MOD;
	vll fq=solve(0,n-1);fq.resize(max(n+10,m+10));
	vll fp(m+10);fp[0]=1;
	for(int i=0;i<n;i++) fp[0]=fp[0]*p[i]%MOD;
	for(int i=1;i<m+10;i++) fp[i]=fp[0]*ksm(n,i)%MOD*inf[i]%MOD;
	fq=to_ex(fq);
	fp=fp*inv(fq);
	for(int i=1;i<=m;i++) cout<<fp[i]*fac[i]%MOD<<endl;
	return 0;
}
```



---

## 作者：鲤鱼江 (赞：3)

也是奇怪概论题。

考虑使用比较 Bot 的做法，记 $f_{i,j}$ 表示抛了 $j$ 次抛出了 $i$ 种数的概率，有 $f_{i,j}=\frac inf_{i,j-1}+\frac{n-i+1}nf_{i-1,j-1}$，记 $F_i(x)=\sum\limits_{j=0}^\infty f_{i,j}x^j$。

有 $F_i(x)=x(\frac inF_i(x)+\frac{n-i+1}nF_{i-1}(x))$，得到 $F_i(x)=\frac{x(n-i+1)F_{i-1}(x)}{n-ix}=\frac{x^i n^{\underline{i}}}{\prod\limits_{j=1}^{i}(n-jx)}$。

有 $F_n(x)=\frac xnF_{n-1}(x)=\frac{(n-1)!x^n}{\prod\limits_{j=1}^{n-1}(n-ix)}$。

这个可以分治的过程中 NTT 一下，即可求出 $F_n(x)$，$F_n(e^x)$ 就是答案的 EGF。

思考为什么 $F_n(e^x)$ 是答案的 EGF，将之展开：

$$
\begin{aligned}
F_n(e^x)&=\sum_{i=0}^\infty f_{n,i}e^{ix}\\
&=\sum_{i=0}^\infty f_{n,i}\sum_{j=0}^\infty \frac{(ix)^j}{j!}\\
&=\sum_{j=0}^\infty \frac {x^j}{j!}\sum_{i=0}^\infty i^jf_{n,i}\\
\end{aligned}
$$

明显 $[\frac{x^k}{k!}]F_n(e^x)$ 是次数的 $k$ 方和的期望值。

然后考虑求 $F_n(e^x)$，是套路的，再来一次 NTT 分治，需要会 EGF 转 OGF。

具体地，记 $G(x)=\prod\limits_{j=1}^{n-1}(n-ix)$，那么 $F(e^x)=\frac{(n-1)!e^{nx}}{G(e^x)}$。

考虑在知晓 $G(x)$ 的情况下如何求 $G(e^x)$。

可以使用 EGF 转 OGF 的 trick。

再 NTT 分治一下就行了。

NTT 分治合并分子分母有一个[经典题](https://www.luogu.com.cn/problem/P7431)。

---

## 作者：Fido_Puppy (赞：2)

题目链接：[[ARC154F] Dice Game](https://www.luogu.com.cn/problem/AT_arc154_f)

令 $X$ 为骰出所有面的次数。

容斥后可得：

$$P(X>t)=\sum_{i=0}^{n-1} {(-1)}^{n-1-i}\binom{n}{i}{\left(\frac{i}{n}\right)}^t$$

考虑 $\forall k \in [1, m]$，计算 $E(X^{\underline{k}})$。

由于 $\Delta x^{\underline{k}}=kx^{\underline{k-1}}$，故 $\displaystyle x^{\underline{k}}=k\sum_{i=0}^{x-1} i^{\underline{k-1}}$。

则

$$E(X^{\underline{k}})=\sum_{i=0}^{n-1}{(-1)}^{n-1-i}\binom{n}{i}k\sum_{t=0}^{\infty} {\left(\frac{i}{n}\right)}^tt^{\underline{k-1}}$$

而 $\displaystyle \sum_{i=0}^{\infty} p^i i^{\underline{k}}=\frac{k!\cdot p^k}{{(1-p)}^{k+1}}$，具体可以类比求生成函数封闭形式。

那么

$$E(X^{\underline{k}})=k!\cdot n\sum_{i=0}^{n-1}{(-1)}^{n-1-i}\binom{n}{i}\cdot\frac{1}{n-i}\cdot{\left(\frac{i}{n-i}\right)}^{k-1}$$

令 $\displaystyle c_i = n\cdot{(-1)}^{n-1-i}\binom{n}{i}\cdot\frac{1}{n-i},p_i=\frac{i}{n-i}$，则 $\displaystyle E(X^{\underline{k}})=k!\sum_{i=0}^{n-1}c_i\cdot{p_i}^{k-1}=k![x^{k-1}]\sum_{i=0}^{n-1}\frac{c_i}{1-p_ix}$，可以通过分治 NTT 在 $\mathrm{O}(n\log^2 n)$ 的复杂度内，$\forall k \in [1, m]$ 求出 $E(X^{\underline{k}})$。

接下来考虑 $\forall k \in [1, m]$，求出 $E(X^k)$。

显然 $\displaystyle E(X^k)=\sum_{i=0}^k\begin{Bmatrix}k\\i\end{Bmatrix}E(X^{\underline{i}})$，令 $a_i=E(X^{\underline{i}}),b_i=E(X^i)$，则

$$b_i=\sum_{j=0}^m \begin{Bmatrix}i\\j\end{Bmatrix}a_j$$

$$=\sum_{j=0}^m a_j \sum_{k=0}^j \frac{{(-1)}^{j-k}k^i}{k!(j-k)!}$$

$$=\sum_{k=0}^m \frac{k^i}{k!} \sum_{j=k}^m a_j \frac{{(-1)}^{j-k}}{(j-k)!}$$

一次差卷积预处理出 $\displaystyle g_k=\frac{1}{k!}\sum_{j=k}^m a_j\frac{{(-1)}^{j-k}}{(j-k)!}$，则 $\displaystyle b_i=[x^i]\sum_{j=0}^m \frac{g_j}{1-jx}$。

同样可以通过分治 NTT 在 $\mathrm{O}(m \log^2 m)$ 的时间复杂度内解决。

```cpp
#include <bits/stdc++.h>
#include <atcoder/modint>
#include <atcoder/convolution>
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define MP make_pair
#define MT make_tuple
#define IT iterator
#define fi first
#define se second
#define For(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define Rep(i, a, b) for (int i = (int)(a); i >= (int)(b); --i)
#define CLR(a, v) memset(a, v, sizeof(a))
#define CPY(a, b) memcpy(a, b, sizeof(a))
#define debug cerr << "ztxakking\n"
#define y0 ztxaknoi
#define y1 ztxakioi
using namespace std;
using namespace atcoder;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using uint = unsigned int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pli = pair<ll, int>;
using pil = pair<int, ll>;
using vi = vector<int>;
template<typename T>
using V = vector<T>;
using mint = modint998244353;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int N = 5e5 + 7;
int n, m;
mint fac[N], ifac[N], inv[N];
mint qpow(mint x, int p) {
  mint ans = 1;
  for (; p; p /= 2, x *= x) {
    if (p & 1) ans *= x;
  }
  return ans;
}
mint C(int m, int n) {
  if (n > m) return 0;
  return fac[m] * ifac[n] * ifac[m - n];
}
mint a[N], b[N];
pair<V<mint>, V<mint>> solve(int l, int r) {
  if (l == r) {
    V<mint> f(2, 0), g(2, 0);
    f[0] = a[l], g[0] = 1, g[1] = -b[l];
    return {f, g};
  }
  int mid = (l + r) / 2;
  auto [fl, gl] = solve(l, mid);
  auto [fr, gr] = solve(mid + 1, r);
  V<mint> g = convolution(gl, gr);
  V<mint> A = convolution(fl, gr), B = convolution(gl, fr), f(r - l + 2);
  For(i, 0, r - l + 1) f[i] = A[i] + B[i];
  return {f, g};
}
V<mint> inverse(V<mint> f) {
  int n = f.size();
  if (n == 1) return V<mint>(1, f[0].inv());
  int n0 = (n + 1) / 2;
  V<mint> A = f; A.resize(n0);
  V<mint> g0 = inverse(A);
  V<mint> g = convolution(convolution(g0, g0), f);
  g.resize(n, 0);
  For(i, 0, n - 1) g[i] = -g[i];
  For(i, 0, n0 - 1) g[i] += g0[i] * 2;
  return g;
}
void init() {
  cin >> n >> m;
  fac[0] = 1;
  For(i, 1, N - 1) fac[i] = fac[i - 1] * i;
  ifac[N - 1] = fac[N - 1].inv();
  Rep(i, N - 1, 1) ifac[i - 1] = ifac[i] * i;
  For(i, 1, N - 1) inv[i] = ifac[i] * fac[i - 1];
}
V<mint> f;
void slv1() {
  For(i, 0, n - 1) {
    a[i] = C(n, i) * n * inv[n - i];
    if (n - 1 - i & 1) a[i] = -a[i];
    b[i] = i * inv[n - i];
  }
  auto [A, B] = solve(0, n - 1);
  A.resize(m, 0), B.resize(m, 0);
  A = convolution(A, inverse(B)), A.resize(m);
  f = A, f.insert(f.begin(), 1);
  For(i, 1, m) f[i] *= fac[i];
}
V<mint> g;
void slv2() {
  V<mint> A(m + 1), B(m + 1);
  For(i, 0, m) A[i] = f[i];
  For(i, 0, m) {
    B[i] = ifac[i];
    if (i & 1) B[i] = -B[i];
  }
  reverse(all(A));
  A = convolution(A, B);
  A.resize(m + 1);
  reverse(all(A));
  For(i, 0, m) A[i] *= ifac[i];
  For(i, 0, m) a[i] = A[i], b[i] = i;
  tie(A, B) = solve(0, m);
  A.resize(m + 1), B.resize(m + 1);
  g = convolution(A, inverse(B));
  For(i, 1, m) cout << g[i].val() << '\n';
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  init(), slv1(), slv2();
  return 0;
}
```

---

## 作者：warzone (赞：2)

## 题目大意
有一个 $N$ 面的骰子（抛掷一次每个面朝上的概率均相等），  
连续抛掷它直到每一面朝上的结果都出现过。  
设抛掷次数为 $X$，对于任意的 $1\le i\le M$，求解 $E(X^i)\bmod 998244353$ 。

$\texttt{Data Range:}1\le N,M\le 2\times 10^5$ 。

## 题解

首先我们考虑求出 $X$ 的概率生成函数 $f_X(x)=\displaystyle\sum_{k}P(X=k)x^k$ 。  
设 $f_{n,k}$ 表示抛掷骰子 $k$ 次，有且仅有 $n$ 面朝上的结果出现过的概率。  
又设 $f_n(x)=\displaystyle\sum_k f_{n,k}x^k$，则

$$f_0(x)=1,f_n(x)=x\left(\dfrac{N-n+1}{N}f_{n-1}(x)+\dfrac{n}{N}f_n(x)\right)\ (1\le n<N)$$
$$\Rightarrow f_0(x)=1,f_n(x)=\dfrac{(N-n+1)x}{N-nx}f_{n-1}(x)\ (1\le n<N)$$
$$\Rightarrow f_{N-1}(x)=\prod_{n=1}^{N-1}\dfrac{(N-n+1)x}{N-nx}=\dfrac{N!x^{N-1}}{\displaystyle\prod_{n=1}^{N-1}(N-nx)}$$

于是

$$f_X(x)=\dfrac{x}{N}f_{N-1}(x)=\dfrac{(N-1)!x^{N-1}}{\displaystyle\prod_{n-1}^{N-1}(N-nx)}$$

又注意到对于任意生成函数 $g(x)=\displaystyle\sum_k g_kx^k$，有

$$\sum_{i=0}^{+\infty}x^i\sum_kg_kk^i=\sum_kg_k\sum_{i=0}^{+\infty}k^ix^i=\sum_k\dfrac{g_k}{1-kx}$$

$$\sum_{i=0}^{+\infty}\dfrac{x^i}{i!}\sum_kg_kk^i=\sum_kg_k\sum_{i=0}^{+\infty}\dfrac{k^ix^i}{i!}=\sum_kg_ke^{kx}=g(e^x)$$

于是答案的指数生成函数为

$$\sum_{i=0}^{+\infty}\dfrac{x^i}{i!}E(X^i)=\sum_{i=0}^{+\infty}\dfrac{x^i}{i!}\sum_kP(X=k)k^i=f_X(e^x)=\dfrac{(N-1)!e^{(N-1)x}}{\displaystyle\prod_{n-1}^{N-1}(N-ne^x)}$$

分治 NTT 求出 $h(x)=\displaystyle\prod_{n-1}^{N-1}(N-nx)$，则可分治 NTT 求出

$$h(e^x)=\operatorname{EGF}\sum_k\dfrac{h_k}{1-kx}$$

多项式求逆即可求出 $f_X(e^x)=\dfrac{(N-1)!e^{(N-1)x}}{h(e^x)}$ 。

时间复杂度 $\Theta(n\log^2n+m\log m)$ 。

### Code(1167 ms,23372 KB)

```cpp
/* 
this code is made by warzone
2023.8.28 17:30
*/
#include<stdio.h>
#include<string.h>
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int word;
typedef unsigned short hword;
typedef unsigned char byte;
#define mx 19
#define mx_ 18
word realid[1<<(mx+1)];
#define id(size,i) realid[(i)|(size)]
#define FOR(size) for(word i=0;i<(size);++i)
#define fftfor(size)								\
	for(word floor=1;floor<(size);floor<<=1)		\
		for(word head=0;head<(size);head+=floor<<1)	\
			for(word i=0;i<floor;++i)
const word mod=998244353;
inline word qpow(word a,word b){
	word ans=1;
	for(;b;b>>=1){
		if(b&1) ans=1ull*ans*a%mod;
		a=1ull*a*a%mod;
	}
	return ans;
}
word root[1<<mx],inv[1<<mx];
struct READ{
	char c;
	inline READ(){
		c=getchar();
		for(word floor=1,i=2;floor<=mx;++floor)
			for(;i<(1u<<(floor+1));++i)
				realid[i]=(i&1)<<(floor-1)|realid[i>>1];
		const word num1=qpow(3,(mod-1)>>mx);
		const word num2=qpow(num1,mod-2);
		root[1<<mx_]=inv[1<<mx_]=1;
		for(word i=(1<<mx_)+1;i<(1<<mx);++i){
			root[i]=1ull*num1*root[i-1]%mod;
			inv[i]=1ull*num2*inv[i-1]%mod;
		}
		for(word i=(1u<<mx_)-1;i;--i)
			root[i]=root[i<<1],inv[i]=inv[i<<1];
	}
	template<typename type>
	inline READ& operator >>(type& num){
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
#define ntt(num,root) [&](){						\
	word num1=num[head|i],num2=num[head|i|floor];	\
    num1+=(num2=1ull*num2*root[i|floor]%mod);		\
	num[head|i]=num1>=mod? num1-mod:num1;			\
	num1-=num2,num1+=mod-num2;						\
	num[head|i|floor]=num1>=mod? num1-mod:num1;}()
struct fftreg{
	word num[1<<mx];
	template<typename type>
	inline void operator()(const word size,const type& f,word end=0){//DFT
		FOR(size>>1){
			num[id(size,i)]=f[i];
			num[id(size,size>>1|i)]=0;
		}
		if(end) num[id(size,size>>1)]=end;
		fftfor(size) ntt(num,root);
	}
};
inline void conv(const word size,const fftreg &f,
	const fftreg &g,word *const f_times_g){//IDFT
	FOR(size) f_times_g[id(size,i)]=1ull*f.num[i]*g.num[i]%mod;
	fftfor(size) ntt(f_times_g,inv);
	const word num=qpow(size,mod-2);
	FOR(size) f_times_g[i]=1ull*num*f_times_g[i]%mod;
}
word in[1<<mx],eax[1<<mx],ebx[1<<mx];
fftreg ecx,edx,eex,efx;
#define newton(size_)   \
    word size=2;   		\
    while(size<<=1,(size>>2)<(size_))

inline void _1(const word size_){//多项式求逆
	ebx[0]=qpow(eax[0],mod-2);
	newton(size_){
		ecx(size,eax),edx(size,ebx);
		conv(size,ecx,edx,ebx);
		FOR(size) ebx[i]=(mod-ebx[i])%mod;
		ebx[0]=(2+ebx[0])%mod;
		ecx(size,ebx);
		conv(size,ecx,edx,ebx);
	}
}
word n,m,size;
inline word cdq1(word begin,word size){//求 h(x)
	if(size==1){
		if(begin&&begin<n)
			return in[begin]=n,mod-begin;
		return in[begin]=1,0;
	}
	word end1=cdq1(begin,size>>1);
	word end2=cdq1(size>>1|begin,size>>1);
	word *const l=in+begin,*const r=l+(size>>1);
	ecx(size,l,end1),edx(size,r,end2);
	conv(size,ecx,edx,l);
	end1=1ull*end1*end2%mod;
	if((l[0]+=mod-end1)>=mod) l[0]-=mod;
	return end1;
}
inline word cdq2(word begin,word size){//求 h(e^x)
	if(size==1){
		eax[begin]=1;
		return in[begin]? mod-begin:0;  
	}
	word end1=cdq2(begin,size>>1);
	word end2=cdq2(size>>1|begin,size>>1);
	word *const l=eax+begin,*const r=l+(size>>1);
	ecx(size,l,end1),edx(size,r,end2);
	conv(size,ecx,edx,l);
	end1=1ull*end1*end2%mod;
	if((l[0]+=mod-end1)>=mod) l[0]-=mod;
	word *const fl=in+begin,*const fr=fl+(size>>1);
	eex(size,fl),efx(size,fr);
	FOR(size) fl[id(size,i)]=(
		1ull*ecx.num[i]*efx.num[i]+
		1ull*edx.num[i]*eex.num[i])%mod;
	fftfor(size) ntt(fl,inv);
	end2=qpow(size,mod-2);
	FOR(size) fl[i]=1ull*end2*fl[i]%mod;
	return end1;
}
word fact[1u<<mx_],rev[1u<<mx_];
int main(){
	cin>>n>>m;
	for(size=1;size<n;size<<=1);
	cdq1(0,size),in[size]=cdq2(0,size);
	//求解阶乘及其逆元
	size=n>m? n:m;
	fact[0]=rev[0]=1;
	for(word i=1;i<=size;++i)
		fact[i]=1ull*i*fact[i-1]%mod;
	rev[size]=qpow(fact[size],mod-2);
	for(word i=size;i;--i)
		rev[i-1]=1ull*i*rev[i]%mod;
	//求解 f_X(x)
	for(size=1;size<=m;size<<=1);
	_1(size),size<<=1;
	ecx(size,in),edx(size,ebx);
	conv(size,ecx,edx,eax),size>>=1;
	FOR(size) eax[i]=1ull*rev[i]*eax[i]%mod;
	_1(size);
	for(word i=0,num=1;i<size;++i){
		in[i]=1ull*num*rev[i]%mod*fact[n-1]%mod;
		num=1ull*num*n%mod;
	}
	size<<=1,ecx(size,in),edx(size,ebx);
	conv(size,ecx,edx,eax),size>>=1;
	for(word i=1;i<=m;++i)
		printf("%llu\n",1ull*fact[i]*eax[i]%mod);
	return 0;
}
```

---

## 作者：dead_X (赞：2)

## 题解
和官方题解好像不一样，呜呜呜。

考虑大力 DP，记 $F_d(x)$ 为 $d$ 到 $n$ 步数期望的 EGF，$[x^m]F_d(x)$ 为 $d$ 到 $n$ 步数 $m$ 次方的期望。

我们发现 $F_d(x)=F_{d+1}(x)\dfrac{e^x}{1-\frac{d}{n-d}(e^x-1)}$，令 $y=e^x$，我们可以得到 $F_1(e^x)$，边界条件为 $F_n(x)=1$。

考虑将 $F_1(e^x)$ 转回 $F_1(x)$，我不会。

神 Alpha 告诉我 $n![x^n]e^{ix}=[x^n]\frac{1}{1-ix}$，因此我们现在只需要求 $\sum\frac{F[i]}{1-ix}$ 就可以了。但是注意到分式展开之后有无穷项而每一项都有贡献，所以不能直接转。

神 JV 告诉我我们可以求 $F(e^x-1)$，这样就只用求前 $m$ 项了，然后展开到 $F(e^x)$，此时还是只有 $m$ 项，再用上面的方法即可。

这个可以分治 NTT 做，时间复杂度 $O(n\log^2n+m\log^2m)$。
## 代码
在高速公路上写的，我认为这是我写过最丑的代码之一，能不参考就不参考。

```cpp
//不回家了，我们去鸟巢！
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
using namespace std;
inline int read(){
   int s=0;
   char ch=getchar();
   while(ch<'0') ch=getchar();
   while(ch>='0') s=s*10+(ch&15),ch=getchar();
   return s;
}
#define ll long long
#define ull unsigned long long
inline ull calc(const ull&x){return x-(__uint128_t(x)*9920937979283557439ull>>93)*998244353;}
const ll p=998244353;
inline ll qp(ll x,int y)
{
    ll res=1;
    for(ll t=x; y; t=calc(t*t),y>>=1) 
    	if(y&1) res=calc(res*t);
    return res;
}
ll A[1<<20],B[1<<20],tmp[1<<20];
int rev[1<<20],N=1;
inline void init()
{
    rev[0]=0,rev[1]=N>>1;
    for(int i=2,d=N>>2; i<N; i<<=1,d>>=1)
        for(int j=0; j<i; ++j) rev[i+j]=rev[j]+d;
    return ;
}
inline void NTT(ll* F,int op)
{
    for(int i=0; i<N; ++i) if(rev[i]>i) F[i]^=F[rev[i]]^=F[i]^=F[rev[i]];
    for(int len=2,M=1; len<=N; len<<=1,M<<=1)
    {
        ll w=qp(op?3:332748118,998244352/len);
        for(int l=0; l<N; l+=len)
        {
            ll w0=1;
            for(int i=l; i<l+M; ++i)
            {
                ll x=F[i],y=calc(w0*F[i+M]);
                ((F[i]=x+y)>=p)&&(F[i]-=p),((F[i+M]=x-y)<0)&&(F[i+M]+=p),w0=calc(w0*w);
            }
        }
    }
}
ll *f[1<<21],*g[1<<21];
int len[1<<21];
int n=read(),m=read();
void solve(int l,int r,int x)
{
	if(l==r)
	{
		f[x]=new ll[2],f[x][0]=1,
		f[x][1]=(p-1ll*(l-1)*qp(n-l+1,p-2)%p)%p,len[x]=1;
		return ;
	}
	int mid=(l+r)>>1;
	solve(l,mid,x<<1),solve(mid+1,r,(x<<1)+1);
	len[x]=len[x<<1]+len[(x<<1)+1],f[x]=new ll[len[x]+1];
	for(N=1;N<=len[x];N<<=1);
	init();
	for(int i=0; i<=len[x<<1]; ++i) A[i]=f[x<<1][i];
	for(int i=0; i<=len[(x<<1)+1]; ++i) B[i]=f[(x<<1)+1][i];
	NTT(A,1),NTT(B,1);
	for(int i=0; i<N; ++i) A[i]=calc(A[i]*B[i]);
	NTT(A,0);
	int inv=qp(N,p-2);
	for(int i=0; i<=len[x]; ++i) f[x][i]=calc(A[i]*inv);
	memset(A,0,N<<3),memset(B,0,N<<3);
	delete f[x<<1],delete f[(x<<1)+1];
	return ;
}
ll x[1<<20],y[1<<20];
void getinv(ll const *f,ll *g,int n)
{
    g[0]=y[0]=qp(f[0],p-2);
    ll inv;
    for(int lim=1; lim<n; lim<<=1)
    {
        memcpy(x,f,lim<<4);
        memset(y+(lim<<1),0,lim<<4);
        N=lim<<1,init(),inv=qp(N,p-2);
        NTT(x,1),NTT(y,1);
        for(int i=0; i<N; ++i) x[i]=calc(x[i]*y[i]);
        NTT(x,0);
        for(int i=0; i<N; ++i) x[i]=calc(x[i]*inv);
        memset(x,0,lim<<3);
        NTT(x,1);
        for(int i=0; i<N; ++i) x[i]=calc(x[i]*y[i]);
        NTT(x,0);
        for(int i=0; i<N; ++i) x[i]=calc(x[i]*inv);
        for(int i=lim; i<N; ++i) g[i]=(p-x[i])%p;
        if(N<n) memcpy(y,g,lim<<4);
    }
}
int fac[500003],ifac[500003],ans[500003];
inline int C(int n,int m)
{return 1ll*fac[n]*ifac[m]%p*ifac[n-m]%p;}
void calc(int l,int r,int x)
{
	if(l==r)
	{
		f[x]=new ll[2],f[x][0]=tmp[l],f[x][1]=0,len[x]=1,
		g[x]=new ll[2],g[x][0]=1,g[x][1]=(p-l-n)%p;
		return ;
	}
	int mid=(l+r)>>1;
	calc(l,mid,x<<1),calc(mid+1,r,(x<<1)+1);
	len[x]=len[x<<1]+len[(x<<1)+1],
	f[x]=new ll[len[x]+1],
	g[x]=new ll[len[x]+1];
	for(N=1;N<=len[x];N<<=1);
	int inv=qp(N,p-2);
	memset(A,0,N<<3),memset(B,0,N<<3);
	
	init();
	for(int i=0; i<=len[x<<1]; ++i) A[i]=g[x<<1][i];
	for(int i=0; i<=len[(x<<1)+1]; ++i) B[i]=g[(x<<1)+1][i];
	NTT(A,1),NTT(B,1);
	for(int i=0; i<N; ++i) A[i]=calc(A[i]*B[i]);
	NTT(A,0);
	for(int i=0; i<=len[x]; ++i) g[x][i]=calc(A[i]*inv);
	memset(A,0,N<<3),memset(B,0,N<<3);
	
	for(int i=0; i<=len[x<<1]; ++i) A[i]=f[x<<1][i];
	for(int i=0; i<=len[(x<<1)+1]; ++i) B[i]=g[(x<<1)+1][i];
	NTT(A,1),NTT(B,1);
	for(int i=0; i<N; ++i) A[i]=calc(A[i]*B[i]);
	NTT(A,0);
	for(int i=0; i<=len[x]; ++i) f[x][i]=calc(A[i]*inv);
	memset(A,0,N<<3),memset(B,0,N<<3);
	
	for(int i=0; i<=len[x<<1]; ++i) A[i]=g[x<<1][i];
	for(int i=0; i<=len[(x<<1)+1]; ++i) B[i]=f[(x<<1)+1][i];
	NTT(A,1),NTT(B,1);
	for(int i=0; i<N; ++i) A[i]=calc(A[i]*B[i]);
	NTT(A,0);
	for(int i=0; i<=len[x]; ++i)
		f[x][i]=(calc(A[i]*inv)+f[x][i])%p;
	memset(A,0,N<<3),memset(B,0,N<<3);
	
	delete f[x<<1],delete f[(x<<1)+1],
	delete g[x<<1],delete g[(x<<1)+1];
	return ;
}
signed main()
{
	const int M=2e5;
	fac[0]=ifac[0]=1;
	for(int i=1; i<=M; ++i)
		fac[i]=1ll*fac[i-1]*i%p;
	ifac[M]=qp(fac[M],p-2);
	for(int i=M-1; i>=1; --i)
		ifac[i]=1ll*ifac[i+1]*(i+1)%p;
	solve(1,n,1),
	memcpy(A,f[1],(n+1)<<3),
	delete f[1],
	getinv(A,B,m+1),
	memset(A,0,sizeof(A));
	
	for(int i=1; i<=m; i+=2) B[i]=(p-B[i])%p;
	for(int i=1; i<=m; ++i) B[i]=1ll*B[i]*fac[i]%p;
	for(int i=0; i<=m; ++i) tmp[i]=ifac[i];
	reverse(B,B+m+1);
	for(N=1;N<=(m<<1);N<<=1);
	init(),NTT(B,1),NTT(tmp,1);
	for(int i=0; i<N; ++i)
		A[i]=1ll*B[i]*tmp[i]%p;
	NTT(A,0);
	int qwq=qp(N,p-2);
	for(int i=0; i<N; ++i) A[i]=1ll*A[i]*qwq%p;
	reverse(A,A+m+1);
	for(int i=1; i<=m; i+=2) A[i]=(p-A[i])%p;
	for(int i=1; i<=m; ++i) A[i]=1ll*A[i]*ifac[i]%p;
	
	
	memset(tmp,0,sizeof(tmp)),
	swap(A,tmp),
	calc(0,m,1),
	memset(A,0,sizeof(A)),
	memset(B,0,sizeof(B)),
	memcpy(A,g[1],(m+2)<<3),
	memset(x,0,sizeof(x)),
	memset(y,0,sizeof(y)),
	getinv(A,B,m+2),
	memset(A,0,sizeof(A)),
	memcpy(A,f[1],(m+2)<<3);
	for(N=1; N<=(m<<1)+2; N<<=1);
	init(),NTT(A,1),NTT(B,1);
	for(int i=0; i<N; ++i) A[i]=1ll*A[i]*B[i]%p;
	NTT(A,0);
	int inv=qp(N,p-2);
	for(int i=1; i<=m; ++i)
		printf("%lld\n",1ll*A[i]*inv%p);
	return 0;
}
```

---

## 作者：苹果蓝17 (赞：1)


提供一种不使用生成函数的暴力做法。

考虑扔 $i$ 次已经扔出所有面的概率为 $n! \dfrac{S2(i,n)}{n^i}$，于是期望时间的 $k$ 次方为：

$$s_k =n!\sum\limits_{i \geq 0} (\dfrac{S2(i,n)}{n^i}-\dfrac{S2(i-1,n)}{n^{i-1}}) i^k$$

为了方便计算，取一个趋近于无穷大的整数 $m$，只计算和式中 $i \leq m$ 的部分。

下面用 $\epsilon(m)$ 表示当 $m$ 趋近于无穷大时值趋近于 $0$ 的部分（于是在最终答案的计算中可以忽略）。结论：对于非负整数 $k$ 与实数 $a \in (0,1)$，$\lim\limits_{x \rightarrow \infty} x^k a^x=0$。

$$
\begin{aligned}
s_k(m) &=n!\sum\limits_{i=0}^m (\dfrac{S2(i,n)}{n^i}-\dfrac{S2(i-1,n)}{n^{i-1}}) i^k\\
&=n! m^k \dfrac{S2(m,n)}{n^m}-n! \sum\limits_{i=0}^{m-1} \dfrac{S2(i,n)}{n^{i}} [(i+1)^k-i^k]\\
\end{aligned}
$$

设 $k-1$ 次下降幂多项式 $\sum\limits_{p=0}^{k-1} c_p x^{\underline{p}}=(x+1)^k-x^k$。系数 $c_p$ 稍后再进行推导，下面继续计算上式：

$$
\begin{aligned}
s_k(m) &=n! m^k \dfrac{S2(m,n)}{n^m}-n! \sum\limits_{p=0}^{k-1} c_p \sum\limits_{i=0}^{m-1} \dfrac{S2(i,n)}{n^{i}} i^{\underline{p}}\\
&=\dfrac{m^k}{n^m} \sum\limits_{t=0}^n (-1)^t \dbinom{n}{t} (n-t)^m -\sum\limits_{p=0}^{k-1} c_p \sum\limits_{i=0}^{m-1} i^{\underline{p}} \sum\limits_{t=0}^n (-1)^t \dbinom{n}{t}  \dfrac{(n-t)^i}{n^{i}}\\

&=m^k \sum\limits_{t=0}^n (-1)^t \dbinom{n}{t} (\dfrac{n-t}{n})^m -\sum\limits_{p=0}^{k-1} c_p \sum\limits_{t=0}^n (-1)^t \dbinom{n}{t} \sum\limits_{i=0}^{m-1} (\dfrac{n-t}{n})^i i^{\underline{p}}\\

\end{aligned}
$$

第一个和式中，当 $t \neq 0$ 时均趋近于 $0$，故其等于 $m^k+\epsilon(m)$。

第二个和式中，考虑求 $\sum\limits_{i=0}^{m-1} (\dfrac{n-t}{n})^i i^{\underline{p}}$：

- 当 $t=0$ 时，其等于 $\sum\limits_{i=0}^{m-1} i^{\underline{p}}=\dfrac{1}{p+1} m^{\underline{p+1}}$。

- 当 $t \neq 0$ 时，记 $a=\dfrac{n-t}{n}$，$f(x)=\sum\limits_{i=0}^{m-1} a^i x^i=\dfrac{1-(ax)^m}{1-ax}$，所求即：

$$f^{(p)}(1)=p!\dfrac{a^p}{(1-ax)^{p+1}}+\epsilon(m)=p! \dfrac{n}{t} (\dfrac{n-t}{t})^p+\epsilon(m)$$

于是带入得：

$$
s_k(m) =m^k+\epsilon(m) -\sum\limits_{p=0}^{k-1} c_p \dfrac{1}{p+1} m^{\underline{p+1}} - \sum\limits_{p=0}^{k-1} c_p \sum\limits_{t=1}^n (-1)^t \dbinom{n}{t} [p! \dfrac{n}{t} (\dfrac{n-t}{t})^p+\epsilon(m)]
$$

接下来先推导 $c_t$：

$$
\begin{aligned}
\sum\limits_{p=0}^{k-1} \dbinom{k}{p} x^p &= \sum\limits_{p=0}^{k-1} \dbinom{k}{p} \sum\limits_{t=0}^p S2(p,t) x^{\underline{t}}\\
&= \sum\limits_{t=0}^{k-1} x^{\underline{t}} \sum\limits_{p=t}^{k-1} \dbinom{k}{p} S2(p,t) \\
\end{aligned}
$$

$$
\begin{aligned}
c_p &=\sum\limits_{t=p}^{k-1} \dbinom{k}{t} S2(t,p)\\
&=\sum\limits_{t=p}^{k} \dbinom{k}{t} S2(t,p) -S2(k,t)\\
&=S2(k+1,t+1)-S2(k,t)\\
&=(t+1) S2(k,t+1)\\
\end{aligned}
$$

$$
s_k(m) =m^k+\epsilon(m) -\sum\limits_{p=0}^{k-1} S2(k,p+1) m^{\underline{p+1}} - \sum\limits_{p=0}^{k-1} (p+1) S2(k,p+1) \sum\limits_{t=1}^n (-1)^t \dbinom{n}{t} [p! \dfrac{n}{t} (\dfrac{n-t}{t})^p+\epsilon(m)]
$$

可以发现关于 $m$ 的部分全部消掉了。

$$
s_k=- \sum\limits_{p=0}^{k-1} (p+1)! S2(k,p+1) \sum\limits_{t=1}^n (-1)^t \dbinom{n}{t} \dfrac{n}{t} (\dfrac{n-t}{t})^p
$$

$$
s_k=\sum\limits_{p=1}^{k} p! S2(k,p) \sum\limits_{t=1}^n (-1)^{t+1} \dbinom{n}{t} \dfrac{n}{t} (\dfrac{n-t}{t})^{p-1}
$$

可以分两步计算：

- $$f_p=\sum\limits_{t=1}^n (-1)^{t+1} \dbinom{n}{t} \dfrac{n}{t} (\dfrac{n-t}{t})^{p-1}$$

- $$s_k=\sum\limits_{p=1}^{k} p! S2(k,p) f_p$$

第一步即计算数列 $k$ 次幂和，使用分治乘做到 $O(n \log^2 n+m \log m)$。具体做法可见 [P4705 玩游戏](https://www.luogu.com.cn/problem/P4705).

第二步，将第二类斯特林数拆开：

$$
\begin{aligned}
s_k &= \sum\limits_{p=1}^{k} f_p \sum\limits_{t=0}^p (-1)^t \dbinom{p}{t} (p-t)^k\\
&= \sum\limits_{p=1}^{k} f_p \sum\limits_{t=0}^p (-1)^{p-t} \dbinom{p}{t} t^k\\
&= \sum\limits_{p=1}^{m} (-1)^p f_p \sum\limits_{t=0}^m (-1)^t \dbinom{p}{t} t^k\\
&= \sum\limits_{t=0}^m (-1)^t t^k \sum\limits_{p=1}^{m} (-1)^p \dbinom{p}{t} f_p \\
\end{aligned}
$$

同样分两步计算：

- $$g_t=\sum\limits_{p=1}^{m} (-1)^p \dbinom{p}{t} f_p$$

- $$s_k=\sum\limits_{t=0}^m (-1)^t t^k g_t$$

第一步可以直接 NTT 计算，复杂度 $O(m \log m)$。

第二步同样是计算数列 $k$ 次幂和，复杂度 $O(m \log^2 m)$。

综上，总时间复杂度 $O(n \log^2 n+m \log^2 m)$。

#### Code

```cpp
...
namespace task{
	int A[N],B[N],tmp[N];
	vector <int> P[N],Q[N];

	void solve(int o,int l,int r,int *a,int *b){
		int len=r-l+1;
		P[o].clear(); Q[o].clear();
		P[o].resize(len+2);
		Q[o].resize(len+2);
		
		if(l==r){
			P[o]={b[l]};
			Q[o]={1,mod-a[l]};
			return ;
		}
		int mid=(l+r)>>1;
		solve(o<<1,l,mid,a,b);
		solve(o<<1|1,mid+1,r,a,b);
		
		NTT::solve(P[o].data(),P[o<<1].data(),Q[o<<1|1].data(),mid-l+1,r-mid);
		NTT::solve(tmp,Q[o<<1].data(),P[o<<1|1].data(),mid-l+1,r-mid);
		for(int i=0;i<=len;i++) gmod(P[o][i]+=tmp[i]);
		
		NTT::solve(Q[o].data(),Q[o<<1].data(),Q[o<<1|1].data(),mid-l+1,r-mid);
	}
	void sol(int *s,int *a,int *b,int n,int m){
		solve(1,1,n,a,b);
		for(int i=0;i<=m;i++) A[i]=B[i]=0;
		for(long long i=0;i<=n;i++) A[i]=P[1][i],B[i]=Q[1][i];
		INV::solve(B,B,m);
		NTT::solve(s,A,B,m,m);
	}
}

int n,m;
int a[N],b[N];
int F[N],G[N],H[N],s[N];

int main(){
	init(N-5);
	cin>>n>>m;
	if(n==1){
		for(int i=1;i<=m;i++) cout<<1<<'\n';
		return 0;
	}
	
	for(int i=1;i<n;i++) a[i]=1ll*(n-i)*invv[i]%mod,b[i]=1ll*ID(i)*C(n,i)%mod*invv[n-i]%mod;
	task::sol(F,a,b,n-1,m);
	gmod(F[1]+=1ll*ID(n)*invv[n]%mod);
	
	for(int i=0;i<=m;i++) F[i]=1ll*F[i]*mul[i]%mod;
	for(int i=0;i<=m;i++) H[m-i]=1ll*ID(i)*inv[i]%mod;
	NTT::solve(H,F,H,m,m);
	for(int i=0;i<=m;i++) G[i]=1ll*H[i+m]*inv[i]%mod;
	
	for(int i=1;i<=m;i++) a[i]=i,b[i]=G[i];
	task::sol(s,a,b,m,m);
	
	for(int k=1;k<=m;k++) cout<<1ll*(mod-s[k])*n%mod<<'\n';
}
```

---

## 作者：Coward2008 (赞：1)

考虑计算丢第 $t$ 次时刚好合法的概率：$[x^{t-1}](t-1)!\frac{n}{n}(e^{\frac{x}{n}}-1)^{n-1}=[x^t]t!x\frac{(e^{\frac{x}{n}}-1)^{n-1}}{t}$ 。

如果令 $h_t=[x^t]t!x(e^{\frac{x}{n}}-1)^{n-1}$ ，则等同于要求 $\sum h_tt^{k-1}$ 。

考虑计算出 $F(x)$ 为 $x(e^{\frac{x}{n}}-1)^{n-1}$ 转 OGF 的结果，则 $k+1$ 的答案是 $[x^k]k!F(e^x)$ 。

考虑 $x(e^{\frac{x}{n}}-1)^{n-1}$ 转 OGF 为 $\sum\tbinom{n-1}{i}(-1)^{n-1-i}\sum\limits_{o=0}^{+\infty}x^{o+1}(\frac{i}{n})^o\frac{(o+1)!}{o!}=\sum\tbinom{n-1}{i}(-1)^{n-1-i}\frac{x}{(1-\frac{i}{n}x)^2}$ 。

则通过分治 NTT ，可以把 $F(x)$ 算成一个 $\frac{H(x)}{G(x)}$ 的形式。

接下来我们想求 $F(e^x)$ 的前 $m$ 项，直接先算 $F(x)$ ，$x^m$ 处截断，再算 $F(e^x)$ 是错的，因为 $F$ 有无限项。

先算 $H(e^x)$ 和 $G(e^x)$ ，从 $m$ 处截断，再算 $F(e^x)=\frac{H(e^x)}{G(e^x)}$ ，可以发现就对了。

计算一个 $F(e^x)$ 的方式是算 $\sum \frac{f_i}{1-ix}$ ，这也能分治 NTT。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc154_f)

**题目大意**

> 给定一个 $[1,n]$ 的随机变量，对于 $i\in [1,m]$ 求随机出 $1\sim n$ 每个数至少一次的随机次数的 $i$ 次方的期望。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

假设 $F(z)$ 为对应的 PGF，即 $[z^k]F(z)$ 表示随机恰好 $k$ 次后得到所有面的概率，那么考察 $F(e^z)$ 得到：
$$
[z^i]F(e^z)=[z^i]\sum_{k=0}^{\infty} f_k\sum_{i=0}^\infty \dfrac{(kz)^i}{i!}=\sum_{k=0}^\infty \dfrac{k^if_k}{i!}
$$
因此 $F(e^z)$ 就是答案的 EGF。

先考虑求 $F(z)$，从朴素 dp 开始：设 $f_{i,j}$ 表示随机 $j$ 次后已经得到 $i$ 个数的概率，那么：$f_{i,j}=\dfrac inf_{i,j-1}+\dfrac{n-i+1}n f_{i-1,j-1}$，用 $F_i(z)$ 表示 $\sum z^jf_{i,j}$ 得到：
$$
F_i(z)=z\left(\dfrac in F_i(z)+\dfrac{n-i+1}n F_{i-1}(z)\right)=\dfrac{z(n-i+1)}{n-iz}F_{i-1}(z)=\dfrac{z^in^{\underline i}}{\prod_{j=1}^i(n-jz)}
$$
那么最终的 $F(z)=\dfrac{z}nF_{n-1}(z)=\dfrac{z^n(n-1)!}{\prod^{n-1}_{i=1}(n-iz)}$，不妨设分母为 $G(z)$，可以通过分治 NTT 算出。

由于 $F(z)$ 为无穷级数，并不方便直接带入 $F(e^z)$，那么我们可以把 $e^z$ 带入右侧得到 $F(e^z)=\dfrac{e^{zn}(n-1)!}{G(e^z)}$。

而 $G(z)$ 为 $n-1$ 次多项式，求 $G(e^z)\bmod {z^{m+1}}$ 可以这样推导：
$$
G(e^z)=\sum_{i=0}^{n-1} g_i\sum_{j=0}^m\dfrac{(iz)^j}{j!}=\mathrm{EGF}\sum_{i=0}^{n-1}\dfrac{g_i}{1-iz}
$$
 其中 $\mathrm{EGF}$ 算子表示把 $i$ 次项系数除以 $i!$。

而这个函数也可以通过分治 NTT 维护通分后的分子分母。

最后多项式求逆除一下得到 $G(e^z)$，再求逆除一下得到 $F(e^z)$ 即可。

时间复杂度 $\mathcal O(n\log^2n+m\log^2m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace P {
const int MOD=998244353,N=1<<19,G=3;
int rev[N],inv[N],w[N<<1];
int ksm(int a,int b=MOD-2,int p=MOD) {
	int ret=1;
	for(;b;a=1ll*a*a%p,b=b>>1) if(b&1) ret=1ll*ret*a%p;
	return ret;
}
void poly_init() {
	inv[1]=1;
	for(int i=2;i<N;++i) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
	for(int k=1;k<=N;k<<=1) {
		int x=ksm(G,(MOD-1)/k); w[k]=1;
		for(int i=1;i<k;++i) w[i+k]=1ll*x*w[i+k-1]%MOD;
	}
}
int plen(int x) { int y=1; for(;y<x;y<<=1); return y;  }
void ntt(int *f,bool idft,int n) {
	for(int i=0;i<n;++i) {
		rev[i]=(rev[i>>1]>>1);
		if(i&1) rev[i]|=n>>1;
	}
	for(int i=0;i<n;++i) if(rev[i]<i) swap(f[i],f[rev[i]]);
	for(int k=2,x,y;k<=n;k<<=1) {
		for(int i=0;i<n;i+=k) {
			for(int j=i;j<i+k/2;++j) {
				x=f[j],y=1ll*f[j+k/2]*w[k+j-i]%MOD;
				f[j]=(x+y>=MOD)?x+y-MOD:x+y,f[j+k/2]=(x>=y)?x-y:x+MOD-y;
			}
		}
	}
	if(idft) {
		reverse(f+1,f+n);
		for(int i=0,x=ksm(n);i<n;++i) f[i]=1ll*f[i]*x%MOD;
	}
}
void poly_mul(const int *f,const int *g,int *h,int n,int m) {
	static int a[N],b[N];
	for(int i=0;i<n;++i) a[i]=f[i];
	for(int i=0;i<m;++i) b[i]=g[i];
	int len=plen(n+m-1);
	ntt(a,0,len),ntt(b,0,len);
	for(int i=0;i<len;++i) h[i]=1ll*a[i]*b[i]%MOD;
	ntt(h,1,len);
	memset(a,0,sizeof(int)*len);
	memset(b,0,sizeof(int)*len);
}
void poly_inv(const int *f,int *g,int n) {
	static int a[N];
	g[0]=ksm(f[0]);
	int k=2;
	for(;k<(n<<1);k<<=1) {
		for(int i=0;i<k;++i) a[i]=f[i];
		ntt(g,0,k<<1),ntt(a,0,k<<1);
		for(int i=0;i<(k<<1);++i) {
			g[i]=(2-1ll*a[i]*g[i]%MOD)*g[i]%MOD;
			if(g[i]<0) g[i]+=MOD;
		}
		ntt(g,1,k<<1);
		memset(g+k,0,sizeof(int)*k);
	}
	memset(g+n,0,sizeof(int)*(k-n));
	memset(a,0,sizeof(int)*k);
}
}
using P::ntt;
using P::plen;
using P::ksm;
const int N=1<<19,MOD=998244353;
vector <int> p[N],q[N];
int n,m,fac[N],ifac[N],a[N],b[N],c[N],d[N],f[N],g[N],h[N];
void cdq1(int l,int r) {
	if(l==r) return p[l]={n,MOD-l},void();
	int mid=(l+r)>>1,len=plen(r-l+2);
	cdq1(l,mid),cdq1(mid+1,r);
	memset(a,0,sizeof(int)*len);
	memset(b,0,sizeof(int)*len);
	for(int i=0;i<=mid-l+1;++i) a[i]=p[l][i];
	for(int i=0;i<=r-mid;++i) b[i]=p[mid+1][i];
	ntt(a,0,len),ntt(b,0,len);
	for(int i=0;i<len;++i) a[i]=1ll*a[i]*b[i]%MOD;
	ntt(a,1,len);
	p[l].resize(r-l+2);
	for(int i=0;i<=r-l+1;++i) p[l][i]=a[i];
}
void cdq2(int l,int r) {
	if(l==r) {
		p[l]={h[l],0},q[l]={1,l?MOD-l:0};
		return ;
	}
	int mid=(l+r)>>1,len=plen(r-l+2);
	cdq2(l,mid),cdq2(mid+1,r);
	memset(a,0,sizeof(int)*len);
	memset(b,0,sizeof(int)*len);
	memset(c,0,sizeof(int)*len);
	memset(d,0,sizeof(int)*len);
	for(int i=0;i<=mid-l+1;++i) a[i]=p[l][i],b[i]=q[l][i];
	for(int i=0;i<=r-mid;++i) c[i]=p[mid+1][i],d[i]=q[mid+1][i];
	ntt(a,0,len),ntt(b,0,len),ntt(c,0,len),ntt(d,0,len);
	for(int i=0;i<len;++i) {
		a[i]=(1ll*a[i]*d[i]+1ll*b[i]*c[i])%MOD;
		b[i]=1ll*b[i]*d[i]%MOD;
	}
	ntt(a,1,len),ntt(b,1,len);
	p[l].resize(r-l+2),q[l].resize(r-l+2);
	for(int i=0;i<=r-l+1;++i) p[l][i]=a[i],q[l][i]=b[i];
}
signed main() {
	P::poly_init();
	for(int i=fac[0]=ifac[0]=1;i<N;++i) ifac[i]=ksm(fac[i]=1ll*fac[i-1]*i%MOD);
	scanf("%d%d",&n,&m);
	if(n==1) {
		for(int i=1;i<=m;++i) puts("1");
		return 0;
	}
	cdq1(1,n-1);
	for(int i=0;i<n;++i) h[i]=p[1][i];
	for(int i=0;i<N;++i) p[i].clear();
	cdq2(0,n-1),p[0].resize(m+1),q[0].resize(m+1);
	for(int i=0;i<=m;++i) f[i]=p[0][i];
	for(int i=0;i<=m;++i) g[i]=q[0][i];
	memset(h,0,sizeof(h));
	P::poly_inv(g,h,m+1);
	ntt(f,0,N),ntt(h,0,N);
	for(int i=0;i<N;++i) f[i]=1ll*f[i]*h[i]%MOD;
	ntt(f,1,N);
	for(int i=0;i<=m;++i) f[i]=1ll*f[i]*ifac[i]%MOD;
	for(int i=m+1;i<N;++i) f[i]=0;
	memset(g,0,sizeof(g));
	memset(h,0,sizeof(h));
	for(int i=0;i<=m;++i) g[i]=1ll*ksm(n,i)*fac[n-1]%MOD*ifac[i]%MOD;
	P::poly_inv(f,h,m+1);
	ntt(g,0,N),ntt(h,0,N);
	for(int i=0;i<N;++i) f[i]=1ll*g[i]*h[i]%MOD;
	ntt(f,1,N);
	for(int i=1;i<=m;++i) printf("%lld\n",1ll*fac[i]*f[i]%MOD);
	return 0;
}
```

---

