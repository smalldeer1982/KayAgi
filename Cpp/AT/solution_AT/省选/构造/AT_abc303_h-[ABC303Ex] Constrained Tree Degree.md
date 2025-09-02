# [ABC303Ex] Constrained Tree Degree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc303/tasks/abc303_h

整数 $ N $ 及び $ 1 $ 以上 $ N-1 $ 以下の整数からなる集合 $ S=\lbrace\ S_1,S_2,\ldots,S_K\rbrace $ が与えられます。

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点の木 $ T $ のうち、以下の条件を満たすものの個数を $ 998244353 $ で割った余りを答えてください。

- 任意の $ i\ (1\leq\ i\ \leq\ N) $ について、$ T $ の頂点 $ i $ の次数を $ d_i $ としたとき、 $ d_i\in\ S $

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ K\ \leq\ N-1 $
- $ 1\leq\ S_1\ <\ S_2\ <\ \ldots\ <\ S_K\ \leq\ N-1 $
- 入力は全て整数

### Sample Explanation 1

ある $ 1 $ つの頂点の次数が $ 3 $ であり、ほかの頂点の次数が $ 1 $ であるような木が条件を満たします。よって答えは $ 4 $ 個です。

### Sample Explanation 3

個数を $ 998244353 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
4 2
1 3```

### 输出

```
4```

## 样例 #2

### 输入

```
10 5
1 2 3 5 6```

### 输出

```
68521950```

## 样例 #3

### 输入

```
100 5
1 2 3 14 15```

### 输出

```
888770956```

# 题解

## 作者：SError_ (赞：2)

给定正整数集合 $S$，问有多少 $n$ 个点的树使得 $\forall i\in[1,n],d_i\in S$，其中 $d_i$ 为 $i$ 的度数。

$2\le n\le 2\times10^5$，$S$ 中的元素在 $[1,n-1]$ 之间。

---

十分显然的 prufer 计数。

根据结论，若 $d_1,d_2,\dots,d_n$ 已确定，合法的生成树的个数为 $\displaystyle \binom{n-2}{d_1-1,d_2-1,\dots,d_n-1}$.

方便地，我们把 $S$ 中所有元素的值减去 $1$。

设 $e_i=d_i-1$，容易列出答案式

$$\large\sum_{e_1+e_2+\dots+e_n=n-2,\forall i\in[1,n],e_i\in S}\binom{n-2}{e_1,e_2,\dots e_n}$$

把多重排列拆成 $\displaystyle \frac{(n-2)!}{\prod_{i=1}^{n}e_i!}$，再把 $(n-2)!$ 提到前面：

$$(n-2)!\cdot \sum_{\{e_n\}}\prod_{i=1}^{n}\frac{1}{e_i!}$$

由于 $e_1+e_2+\dots+e_n=n-2$，所以右半边的和式是可以写成卷积的形式的。

即对于每个 $S_i$，将多项式 $f(x)$ 在 $x^{S_i}$ 处的系数设为 $\displaystyle \frac{1}{S_i!}$，答案即

$$(n-2)!\cdot [x^{n-2}]f(x)^n$$

多项式快速幂可以做到时间复杂度 $O(n\log^2 n)$ 或 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define N (1<<19)
#define P 998244353
using namespace std;
int read(){
	int x=0,w=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*w;
}
int qpow(int k,int b){
	int ret=1;
	while(b){
		if(b&1)ret=1ll*ret*k%P;
		k=1ll*k*k%P,b>>=1;
	}
	return ret;
}
int lim,r[N],gn,tp,inv;
void init_r(int n){
	lim=1;while(lim<(n<<1))lim<<=1;
	for(int i=0;i<lim;i++)
		r[i]=(r[i>>1]>>1)+(i&1)*(lim>>1);
}
void ntt(int *x,int opt){
	for(int i=0;i<lim;i++)
		if(r[i]<i)swap(x[i],x[r[i]]);
	for(int p=2,k=1;p<=lim;p<<=1,k<<=1){
		gn=qpow(3,(P-1)/p);
		for(int i=0;i<lim;i+=p)
			for(int j=0,g=1;j<k;j++,g=1ll*g*gn%P){
				tp=1ll*x[i+j+k]*g%P;
				x[i+j+k]=(x[i+j]-tp+P)%P;
				x[i+j]=(x[i+j]+tp)%P;
			}
	}
	if(opt==-1){
		reverse(x+1,x+lim),inv=qpow(lim,P-2);
		for(int i=0;i<lim;i++)
			x[i]=1ll*x[i]*inv%P;
	}
}
int ta[N],tb[N],f[N],g[N];
void Mul(int *a,int *b,int *c,int n){
	init_r(n);
	for(int i=0;i<n;i++)ta[i]=a[i],tb[i]=b[i];
	for(int i=n;i<lim;i++)ta[i]=tb[i]=0;
	ntt(ta,1),ntt(tb,1);
	for(int i=0;i<lim;i++)
		c[i]=1ll*ta[i]*tb[i]%P;
	ntt(c,-1);
	for(int i=n;i<lim;i++)c[i]=0;
}
int n,m,s[N];
int fac[N],ifac[N];
void fpow(int b){
	g[0]=1;
	while(b){
		if(b&1)Mul(g,f,g,n-1);
		Mul(f,f,f,n-1),b>>=1;
	}
}
int calc(){
	for(int i=1;i<=m;i++)f[s[i]]=ifac[s[i]];
	fpow(n);
	return 1ll*fac[n-2]*g[n-2]%P;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++)s[i]=read()-1;
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=1ll*fac[i-1]*i%P;
	ifac[n]=qpow(fac[n],P-2);
	for(int i=n-1;i;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%P;
	printf("%d\n",calc());
	
	return 0;
}
```

---

## 作者：zifanwang (赞：1)

* [AtCoder 题面](https://atcoder.jp/contests/abc303/tasks/abc303_h)
* [洛谷 题面](https://www.luogu.com.cn/problem/AT_abc303_h)

如果每个点的度数都知道了，那问题就转化成了 [P2290 [HNOI2004]树的计数](https://www.luogu.com.cn/problem/P2290)，直接求 Prufer 序列的个数即可，因为一个度数为 $d_i$ 的点在 Prufer 序列中的出现次数是 $d_i-1$，所以答案是：$\frac{(n-2)!}{\prod_{i=1}^{n}(d_i-1)!}$。

可以把 $(n-2)!$ 放到最后再乘，变一下：

$$\prod_{i=1}^{n}\frac{1}{(d_i-1)!}\times (n-2)!$$

这题要求 $d_i\in S$，发现前面这个东西可以用母函数来做。

令 $F(x)=a_0+a_1x+a_2x^2+\dots+a_{n-2}x^{n-2}$，对于每个 $i\in S$，令 $a_{i-1}=\frac{1}{(i-1)!}$，其余的 $a_i=0$。

可以用多项式快速幂求出 $F(x)^n$，然后答案就是 $x^{n-2}$ 对应的系数乘上 $(n-2)!$。

时间复杂度：$O(n\log^2 n)$，可以通过本题。

**注意清空多余的系数**

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mxn 1000003
#define md 998244353
#define pb push_back
#define mkp make_pair
#define ld long double
#define umap unordered_map
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
#define pq priority_queue
using namespace std;
int n,k,c,s,a[mxn],f[mxn],g[mxn],fac[mxn],ifac[mxn],rev[mxn];
int power(int x,int y){
	int ans=1;
	for(;y;y>>=1){
		if(y&1)ans=ans*x%md;
		x=x*x%md;
	}
	return ans;
}
void ntt(int *a,int n,int flag){
	rept(i,0,n)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int h=1;h<n;h<<=1){
		int x,y,s=power(3,499122176/h);
		for(int j=0;j<n;j+=h<<1){
			int w=1;
			for(int k=j;k<j+h;++k){
				x=a[k],y=w*a[k+h]%md;
				a[k]=(x+y)%md;
				a[k+h]=(x-y+md)%md;
				w=w*s%md;
			}
		}
	}
	if(flag==-1){
		int p=power(n,md-2);
		reverse(a+1,a+n);
		rept(i,0,n)a[i]=a[i]*p%md;
	}
}
void power(int x){
	g[0]=1;
	for(;x;x>>=1){
		if(x&1){
			ntt(f,s,1);
			ntt(g,s,1);
			rept(i,0,s)g[i]=g[i]*f[i]%md;
			ntt(g,s,-1);
			ntt(f,s,-1);
			rept(i,n-1,s)g[i]=0;
		}
		ntt(f,s,1);
		rept(i,0,s)f[i]=f[i]*f[i]%md; 
		ntt(f,s,-1);
		rept(i,n-1,s)f[i]=0;
	}
}
signed main(){
	scanf("%lld%lld",&n,&k);
	fac[0]=1;
	rep(i,1,n)fac[i]=fac[i-1]*i%md;
	ifac[n]=power(fac[n],md-2);
	drep(i,n,1)ifac[i-1]=ifac[i]*i%md; 
	rep(i,1,k)scanf("%lld",&a[i]),f[a[i]-1]+=ifac[a[i]-1];
	for(c=0,s=1;s<=n<<1;s<<=1,++c);
	rept(i,0,s)rev[i]=(rev[i>>1]>>1)|((i&1)<<(c-1));
	power(n);
	cout<<g[n-2]*fac[n-2]%md;
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：0)

## 6. [[ABC303Ex] Constrained Tree Degree](https://www.luogu.com.cn/problem/AT_abc303_h)

先考虑一个比较弱的做法。

首先 DP 包治百病（不是，这怎么成为数数题的口头禅了），设 $f[i][j]$ 为前 $i$ 个点有 $j$ 个根的方案数。考虑往后推。

先想暴力，暴力好写。先统一把 $S$ 中所有元素减一。

那么理所当然地，枚举一个 $k\in S$，若 $k=0$ 则 $f[i][j]\to f[i+1][j+1]$ 就多一个根。

否则就有 

$$f[i][j]\times \binom{j}{k}\to f[i+1][j-k+1]$$

其中 $k\le j$。

这里已经很像卷积了。考虑简单拆一下式子。

$$\sum (f[i][j]\times j!)\times (k!)\times (j-k)!\to f[i+1][j-k+1]$$

可以把那个 $(j-k)!$ 分离出来，关注一下 $j-k+1$

卷积的形式是 

$$c_{i+j}=\sum_{i}\sum _{j} a_ib_j$$

这里我们设 $a_j=f[i][j]\times j!,b_{1-k}=k!$。

于是我们就能用 ATcoder convolution $O(n^2\log n)$ 解决问题了，但是还不够。

然后发现想错方向了，式子比较复杂……

---

[P2290 [HNOI2004] 树的计数](https://www.luogu.com.cn/problem/P2290)

发现可以直接 `prufer` 序列做。它有性质：这是个 $n-2$ 长的序列，每个点出现 $(d_i-1)$ 次。于是使用这个性质，多重集排列数搞一搞就可以过掉这道题。

---

回到 `prufer` 序列求解这个题上面。显然预处理的时候也要减一，然后一个 $n-2$ 的序列，点出现次数仅能在 $S$ 集合中选一个，出现次数直接多重集排列数算就行了，方案数是 $\dfrac{(n-2)!}{\prod (d_i-1)!}$，注意 $0!=1$。

显然分子最后乘上去，分母用有理数取模化简一下，然后要求 $\sum (d_i-1)=n-2$。

体验一波小小的 OGF 生成函数震撼，具体而言，就是对于 $S$ 序列全部减一，$i$ 次项系数上存 $\dfrac{1}{i!}$，然后卷积，调取 $n-2$ 位置上就行了。

$n$ 次相同多项式的卷积的过程可以直接使用多项式快速幂算法做到 $O(n\log^2 n)$（当然也可以 $O(n\log n)$ 做）。于是我们就解决了这个问题。

另外，感谢 AtCoder 送的 `convoluton` 和 `modint998244353`。

```cpp
#include<bits/stdc++.h>
#include<atcoder/convolution>
#include<atcoder/modint>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
using vi=vector<I>;using mi=atcoder::modint998244353;
vi mul(vi&a,vi&b){return atcoder::convolution(a,b);}
vi ksm(vi&x,I y){vi a(1,1);
	for(;y;y>>=1,x=mul(x,x))if(y&1)a=mul(a,x);
	return a;}
const I N=2e5+10;
mi fac[N],ifac[N];I n,k,a;
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;vi x(n-1,0);fac[0]=ifac[0]=1;
	fo(i,1,n)fac[i]=fac[i-1]*i,ifac[i]=ifac[i-1]/i;
	fo(i,1,k)cin>>a,x[a-1]=ifac[a-1].val();
	vi ans=ksm(x,n);
	printf("%d\n",(fac[n-2]*ans[n-2]).val());
	return 0;}
```



---

## 作者：chroneZ (赞：0)

前置知识：[Prüfer 序列](https://oi-wiki.org/graph/prufer/) 与 [指数生成函数](https://oi-wiki.org/math/poly/egf/)

对于这类与点度数相关的树计数问题，考虑运用 Prüfer 序列的相关性质求解。

我们知道一个编号在 Prüfer 序列中的出现次数等同于该编号所对应的结点在树上的度数减一。又由于 Prüfer 序列与带标号无根树成双射关系，所以直接对 Prüfer 序列计数即可。

具体来说，我们要求长度为 $n - 2$，值域为 $[1, n]$ 的序列的数量，满足对于所有 $x \in [1, n]$，$x$ 在序列中的出现次数 $ + 1 \in S$。

这就是比较典的一个 EGF 了，记 $f(x) = \sum \limits_{i = 0} ^ \infty \frac{a_i}{i!} x ^ i$，其中 $a_i = \left \{ \begin{array}{ll} 0, a_i + 1\notin S \\ 1, a_i + 1 \in S \end{array}\right.$，答案即为 $(n - 2)! [x ^ {n - 2}]f^n(x)$。

NTT 的复杂度是 $\mathcal{O}(n \log n)$ 的，快速幂是 $\mathcal{O}(\log n)$ 的，因此总复杂度 $\mathcal{O}(n \log ^ 2 n)$。还有一种 $\mathcal{O}(n \log n)$ 的做法，可以参考官方题解。

```cpp
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace atcoder;
using namespace std;

using mint = modint998244353;

int main(){
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); cout.tie(nullptr);
	int n, k; cin >> n >> k;
	vector<mint> fact(n - 1, 1);
	for(int i = 1; i < n - 1; i++)
		fact[i] = fact[i - 1] * i;
	vector<mint> p(n - 1, 0);
	for(int i = 0; i < k; i++){
		int x; cin >> x;
		p[x - 1] = fact[x - 1].inv();
	}
	int b = n;
	vector<mint> res = {1};
	while(b){
		if(b & 1) res = convolution(res, p), res.resize(n - 1);
		p = convolution(p, p); p.resize(n - 1); b >>= 1;
	}
	cout << (fact[n - 2] * res[n - 2]).val();
}
```

---

## 作者：honglan0301 (赞：0)

## 题目分析

题意是给你一个集合 $S$，求对于每个点都有度数 $d_i\in S$ 的有标号无根树个数。首先可以想到给定每个点度数 $d_i$ 时无根树个数是容易求的，即 $\text{prufer}$ 序列的结论：

$$p=\frac{(n-2)!}{\prod (d_i-1)!}=(n-2)!\frac{1}{\prod (d_i-1)!}$$

而我们要求的是：

$$ans=\sum p=\sum (n-2)!\frac{1}{\prod (d_i-1)!}=(n-2)!\sum\frac{1}{\prod (d_i-1)!}$$

前者是常数，后者我们从每个点度数的生成函数角度考虑，度数为 $j$ 则需要配一个 $\displaystyle\frac{1}{(j-1)!}$ 的系数，于是生成函数是 $F(x)=\sum\limits_{i\in S} \displaystyle\frac{1}{(i-1)!}x^i$，把 $F(x)$ 全都卷起来得到 $F^n(x)$ 后 $x^{2n-2}$ 次项的系数就是 $\sum\displaystyle\frac{1}{\prod (d_i-1)!}$，因为当且仅当 $\sum d_i=2n-2$ 才能构成树。

于是有：

$$ans=(n-2)![x^{2n-2}](\sum_{i\in S}\displaystyle\frac{1}{(i-1)!}x^i)^n$$

后者我不会多项式快速幂，倍增地用 $\text{NTT}$ 卷出来就能过，时间复杂度 $O(n\log^2n)$。附个粘板子的 [**提交记录**](https://atcoder.jp/contests/abc303/submissions/41771550) 吧，不放代码了。

---

