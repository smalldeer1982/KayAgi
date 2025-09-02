# Two Snuke

## 题目描述

给你一个整数 $N$。你的任务是选择整数 $s_1, s_2, n_1, n_2, u_1, u_2, k_1, k_2, e_1, e_2$，这些整数需要满足以下六个条件：

1. $0 \leq s_1 < s_2$
2. $0 \leq n_1 < n_2$
3. $0 \leq u_1 < u_2$
4. $0 \leq k_1 < k_2$
5. $0 \leq e_1 < e_2$
6. $s_1 + s_2 + n_1 + n_2 + u_1 + u_2 + k_1 + k_2 + e_1 + e_2 \leq N$

对于所有满足以上条件的 $(s_1, s_2, n_1, n_2, u_1, u_2, k_1, k_2, e_1, e_2)$ 组合，计算 $(s_2 - s_1)(n_2 - n_1)(u_2 - u_1)(k_2 - k_1)(e_2 - e_1)$ 的值，并将这些结果的总和对 $10^9 + 7$ 取模。

问题涉及 $T$ 个测试用例，请分别计算每个测试用例的结果。

## 说明/提示

- 所有输入均为整数。
- $1 \leq T \leq 100$
- $1 \leq N \leq 10^9$

### 示例解释

- 当 $N = 4$ 时，没有满足条件的整数组合，因此结果为 $0$。
- 当 $N = 6$ 时，满足条件的整数组合有以下 $6$ 种：
  - $(0, 1, 0, 1, 0, 1, 0, 1, 0, 1)$
  - $(0, 2, 0, 1, 0, 1, 0, 1, 0, 1)$
  - $(0, 1, 0, 2, 0, 1, 0, 1, 0, 1)$
  - $(0, 1, 0, 1, 0, 2, 0, 1, 0, 1)$
  - $(0, 1, 0, 1, 0, 1, 0, 2, 0, 1)$
  - $(0, 1, 0, 1, 0, 1, 0, 1, 0, 2)$

其中，$(s_2 - s_1)(n_2 - n_1)(u_2 - u_1)(k_2 - k_1)(e_2 - e_1)$ 的结果为 $1$ 的组合有 $1$ 种，结果为 $2$ 的组合有 $5$ 种，故答案为 $11$。

注意结果需对 $10^9 + 7$ 取模。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
4
6
10
1000000000```

### 输出

```
0
11
4598
257255556```

# 题解

## 作者：STARSczy (赞：16)

乱搞题解，但是很无脑。因为是模拟赛时想到的，发篇题解以纪念。

通过大样例大概可以看出答案是关于 $n$ 的多项式量级的，于是想去直接拉格朗日插值，但是好像插不出来。

然后推一下，发现答案和 $n$ 的奇偶性有关系，然后就对奇偶去插，发现高次项一堆 $0$，代表我们插出来了。因为考场上会有大样例，所以可以这样插。

关于拉格朗日插值，因为插的是多项式 $\sum_{i=1}^{n} y_i\prod_{j=1,j\neq i}^{n}\frac{x-x_j}{x_i-x_j}$，所以要算 $\prod (x-x_i)$，用背包算即可。然后每次使用背包撤销抠出 $x-x_i$ 即可。

拉格朗日插值代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/rope>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define per(i,r,l) for(int i=(r),i##end=(l);i>=i##end;--i)
#define int long long
#define double long double
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define rbtree(way) tree<way,null_type,less<way>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
const int maxn=1e6+10,maxm=1e6+10,mod=1e9+7,inf=INT_MAX;
inline int ksm(int x,int k,int mod=mod){
	int ans=1;
	for(;k;k>>=1,x=x*x%mod) if(k&1) ans=ans*x%mod;
	return ans;
}

int n,ans[maxn],t[maxn];
pii a[maxn];

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,t[0]=1;
	rep(i,1,n) cin>>a[i].fi;
	rep(i,1,n) cin>>a[i].se
//	rep(i,1,n) if(a[i].fi%2==0) a[i]=a[i-1];
//	rep(i,1,n) if(a[i].fi%2==1) a[i]=a[i+1];
//  如果求奇数就是取消注释第一行，反之就是第二行。
	sort(a+1,a+n+1),n=unique(a+1,a+n+1)-a-1;
	rep(i,1,n){
		per(j,n,1) t[j]=(t[j-1]+(mod-a[i].fi)*t[j])%mod;
		(t[0]*=mod-a[i].fi)%=mod;
	}
	rep(i,1,n){
		int ni=ksm(mod-a[i].fi,mod-2),add=a[i].se;
		(t[0]*=ni)%=mod;
		rep(j,1,n) t[j]=(t[j]+mod-t[j-1])*ni%mod;
		rep(j,1,n) if(j!=i) (add*=ksm(a[i].fi+mod-a[j].fi,mod-2))%=mod;
		rep(j,0,n) (ans[j]+=t[j]*add)%=mod;
		per(j,n,1) t[j]=(t[j-1]+(mod-a[i].fi)*t[j])%mod;
		(t[0]*=mod-a[i].fi)%=mod;
	}
	rep(i,0,n) cout<<ans[i]<<',';
	return 0;
}
```

这是考场大样例：https://www.luogu.com.cn/paste/vmc8gktm 。

插出来 $n$ 为偶数多项式系数从低到高就是

```0,765144583,346175634,347662323,5655049,184117322,927321758,444014759,542573865,237315285,417297686,471090892,183023413,660103155,727008098,869418286```

奇数则为：

```539588932,729548371,700407153,404391958,962779130,184117322,927321758,444014759,542573865,237315285,417297686,471090892,183023413,660103155,727008098,869418286```

故最终代码为：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/rope>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define per(i,r,l) for(int i=(r),i##end=(l);i>=i##end;--i)
//#define int long long
#define double long double
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define rbtree(way) tree<way,null_type,less<way>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
const int maxn=1e6+10,maxm=1e6+10,mod=1e9+7,inf=INT_MAX;
inline int ksm(int x,int k,int mod=mod){
	int ans=1;
	for(;k;k>>=1,x=x*x%mod) if(k&1) ans=ans*x%mod;
	return ans;
}


inline char gc(){
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int sum=0,f=0;
	char ch=gc();
	for(;!isdigit(ch);ch=gc())f|=(ch=='-');
	for(;isdigit(ch);ch=gc()) sum=((sum<<1)+(sum<<3)+(ch^48));
	return f?-sum:sum;
}
int tot,nw;
char iotp[maxn*30],tmp[100];
inline void write(int x){
	if(tot>=3e7) fwrite(iotp,1,tot,stdout),tot=0;
	if(x==0) iotp[tot++]='0';
	for(;x;tmp[++nw]=x%10+'0',x/=10);
	for(;nw;iotp[tot++]=tmp[nw--]);
	iotp[tot++]='\n';
}

int T,n,
	a0[20]={0,765144583,346175634,347662323,5655049,184117322,927321758,444014759,
			542573865,237315285,417297686,471090892,183023413,660103155,727008098,869418286},
	a1[20]={539588932,729548371,700407153,404391958,962779130,184117322,927321758,444014759,
			542573865,237315285,417297686,471090892,183023413,660103155,727008098,869418286};
inline int get0(int x){
	long long k=1,ans=0;
	rep(i,0,15) (ans+=k*a0[i]),k=k*x%mod;
	return ans%mod;
}
inline int get1(int x){
	long long k=1,ans=0;
	rep(i,0,15) (ans+=k*a1[i]),k=k*x%mod;
	return ans%mod;
}

signed main(){
	T=read();
	rep(o,1,T) n=read(),write(n&1?get1(n):get0(n));
	fwrite(iotp,1,tot,stdout);
	return 0;
}
```

---

## 作者：win114514 (赞：11)

很好的题。

### 思路

首先分析条件。

我们需要满足：$s_1<s_2$ 等不等关系。

我们不想要处理复杂的不等关系，那么我们可以转化枚举的东西。

令 $sf=s_1\times 2,sg=s_2-s_1$。

相对应的，我们会有：$nf,ng,uf,ug,kf,kg,ef,eg$。

我们现在的问题就转化为了：

$$
\sum_{sf,sg,nf,ng,uf,ug,kf,kg,ef,eg}sg\times ng\times ug\times kg\times eg
$$

如何处理乘法，一个常见技巧是用分配律拆开，可以知道它的组合意义是每一段中选一个代表的东西。

考虑选一个代表的东西会是什么影响。

你本来的一堆东西，相当于产生了一个分界处，所以它的方案与选两堆是一样的。

那么我们可以再来审视一下这些条件了。

我们要把小于等于 $n$ 个无标号小球放到 $15$ 个有标号的盒子里，可以为空，前 $5$ 个盒子里的小球数量要求是偶数个。

这个怎么做呢？

首先，小于等于 $n$ 个是好处理的。

我们只要再多加一个盒子来放其余的小球就可以了。

偶数怎么处理？

我们可以枚举有多少个奇数个球的盒子，由于除了前五个盒子里必须要是偶数，后面十一个都可能是奇数。

其余的就可以隔板法统计了。

另外最后的细节就是，$sg,ng,ug,kg,eg$ 这 $5$ 个盒子不能为空，这个就只需要在最开始把 $n$ 减五就可以了。

式子是：

$$
\sum_{i=0}^{11}[(n-i)\bmod 2=0]\binom{\frac{n-i}{2}+15}{15}\binom{11}i{}
$$

注意，$n$ 是减了五的。

组合数暴力计算即可。

~~复杂度把上面看作常数就是 $O(T)$ 的。~~

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9 + 7;

inline int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod, y /= 2;
  }
  return res;
}
inline int C(int n, int m) {
  int res = 1;
  for (int i = n; i > n - m; i--) res = res * i % mod;
  for (int i = 1; i < m + 1; i++) res = res * power(i, mod - 2) % mod;
  return res;
}
inline void solve() {
  int n, ans = 0;
  cin >> n, n -= 5;
  for (int i = 0; i <= 11; i++) {
    int m = n - i;
    if (m < 0 || m & 1) continue;
    (ans += C(m / 2 + 15, 15) * C(11, i)) %= mod;
  }
  cout << ans << "\n";
}

signed main() {
  int t;
  cin >> t;
  while (t--) solve();
  return 0;
}
```

---

## 作者：kkxacj (赞：10)

#### 思路

直接令 $A = s_2-s_1,B = n_2-n_1,C = u_2-u_1,D = k_2-k_1,E = e_2-e_1$，这样只需要 $2\times\left(s_1+n_1+u_1+k_1+e_1\right)+A+B+C+D+E \le n$ 就满足条件，不过要求 $A,B,C,D,E > 0,s_1,n_1,u_1,k_1,e_1 \ge 0$，所以可以先让 $n-5$，当然若 $n<5$ 输出 $0$，这样就转化为了 $A,B,C,D,E,s_1,n_1,u_1,k_1,e_1 \ge 0$，显然暴力计算复杂度为 $n+t$，考虑优化。

我们肯定希望能快速求出结果，考虑其组合意义，当然如果读者想不出来也可以考虑打一个暴力 `dp` 观察每一个的输出发现是组合数，如和转化捏，我们可以给 $A,B,C,D,E$ 复制一份，然后记 $X$ 为剩下的没用到的数，因为是 $\le n$ 的都要计入贡献，所以题目转化为，**有 $n$ 个无编号小球，放入 $16$ 个有编号盒子里的方案数**。

为什么给 $A,B,C,D,E$ 复制一份就是对的？本来一组的贡献是 $A \times B \times C \times D \times E$，单独看每一组，容易发现，往两个盒子里放 $A-1$ 个球有 $A$ 种放法，盒子可以为空，所以对于每个数开两个盒子，由于乘法原理，合一起肯定也是对的。

最后，还有一个问题是我们要保证前 $5$ 个盒子放的都得是偶数个，可以直接枚举后面 $11$ 个有几个放了奇数个即可，然后用隔板法对答案的贡献即为 $\binom{\frac{n-i}{2}+15}{15}\binom{11}{i}$，注意要保证 $n-i$ 是偶数且 $i\le n$。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int mod = 1e9+7;
int t,n,ans,fac[30],inv[30],o;
inline int ksm(int x,int p)
{
	int ans = 1;
	while(p)
	{
		if((p&1)) ans = ans*x%mod;
		x = x*x%mod;
		p>>=1;
	}
	return ans;
} 
inline int C(int x,int y)
{
	o = 1;
	for(int i = x;i >= x-y+1;i--) o = o*i%mod;
	return o*inv[y]%mod;
} 
signed main()
{
	read(t); fac[0] = 1;
	for(int i = 1;i <= 20;i++) fac[i] = fac[i-1]*i%mod;
	inv[20] = ksm(fac[20],mod-2);
	for(int i = 19;i >= 0;i--) inv[i] = inv[i+1]*(i+1)%mod; 
	while(t--)
	{
		read(n); ans = 0;
		if(n < 5){print(0),pc('\n'); continue;}
		n -= 5;
		for(int i = 0;i <= 11;i++)//由于要保证前5个盒子都是偶数，枚举后面有i个盒子是偶数 
		{
			if(n < i || (n-i)%2==1) continue;
			o = 1;
			ans = (ans+fac[11]*inv[i]%mod*inv[11-i]%mod*C((n-i)/2+15,15)%mod)%mod;
		}
		print(ans),pc('\n');
	}
	flush();
	return 0;
}
/*
9->8
开始全部赋值为1，n-=siz，然后在把这些复制一份 
0 *1
1 *2
2 *3
3 *4
4 *5
5 *6
6 *7
7 *8
8 *9
通过实践发现是对的，尝试证明一下
对于一个点x，值为y，则贡献为i,ans*=i
考虑一个点的值为原点x和复制点x`的值相加得到，即为(y+y`)，这样就恰好有(y+y`+1)种选法，所以是对的 
*/
```

---

## 作者：Re_Star (赞：6)

## [AT_aising2020_f Two Snuke](https://www.luogu.com.cn/problem/AT_aising2020_f)

[更好的阅读体验](https://www.cnblogs.com/Re-Star/p/18664789)

题意：对于一个十元组 $(a_1,a_2,b_1,b_2,c_1,c_2,d_1,d_2,e_1,e_2)$，定义它合法当且仅当满足下列条件：

- $0\le a_1<a_2$。

- $0\le b_1<b_2$。

- $0\le c_1<c_2$。

- $0\le d_1<d_2$。

- $0\le e_1<e_2$。

- $a_1+a_2+b_1+b_2+c_1+c_2+d_1+d_2+e_1+e_2\le n$。
  
  现在有 $T$ 组数据，每次对于给定的 $n$ 求所有合法十元组 $(a_2-a_1)(b_2-b_1)(c_2-c_1)(d_2-d_1)(e_2-e_1)$ 之和对 $10^9+7$ 取模的结果。
  
  $1\le T\le 100,1\le n\le 10^9$。

$sol$：首先考虑两两分组，我们定义 $a_1+a_2=n_1,a_2-a_1=m_1\dots e_1+e_2=n_5,e_2-e_1=m_5$。然后考虑 DP，我们令 $f_{i,j}$ 表示前 $i$ 组数和为 $j$ 的所有合法情况的 $\prod\limits_{k=1}^i m_k$ 的和，最终答案就是 $\sum\limits_{i=1}^n f_{5,i}$。

现在我们考虑一组数和为 $n_i$，可以分成 $0$ 和 $n_i$ 此时 $m_i$ 为 $n_i$，也可以分成 $1$ 和 $n_i-1$，此时 $m_i$ 为 $n_i-2$。

以此类推，我们可以发现一组数的和 $n_i$ 确定时所有情况的 $m_i$ 呈现等差数列的形式，我们设 $g_i$ 为一组数和为 $i$ 时所有情况 $m$ 的和。需要分两种情况，如果 $i$ 为奇数，$g_i=\frac{(i+1)^2}{4}$，$i$ 为偶数时 $g_i=\frac{i(i+2)}{4}$。

然后我们就可以得到一个状态转移式：
$$
f_{i,j}=\sum\limits_{i=0}^j f_{i-1,j-k}\times g_k
$$
可以观察到如果把 $f_{i-1}$ 和 $g$ 看作生成函数的话，这个转移就是让 $f_i$ 等于它们的卷积，并且很显然 $f_1$ 和 $g$ 是等价的，所以 $f_5$ 就相当于 $g^5$，最后答案就是这个生成函数的前缀和。

我们可以求出 $g$ 的封闭形式：
$$
\frac{x}{(1-x)^2(1-x^2)}
$$ 
所以 $g^5$ 是: 
$$
\frac{x^5}{(1-x)^{10}(1-x^2)^{5}}
$$
因为要求前缀和所以再乘上 $\frac1{1-x}$ 最终生成函数卷积出的形式就是 $\frac{x^5}{(1-x)^{11}(1-x^2)^{5}}$（有一篇题解似乎也得到了类似的形式，但我没看懂推导过程）。

<!-- $x^5$ 相当于平移 $5$ 位比较简单先不管。而 $\frac1{(1-x)^{11}(1-x^2)^{5}}$ 这玩意第 $n$ 项系数就是:
$$
\sum\limits_{k=0}^{\lfloor\frac{n}{2}\rfloor} {k+4\choose4}\times{n-2k+10\choose 10}
$$ 
现在 $n$ 给定了，$\sum$ 后面那坨就是关于 $k$ 的 $14$ 次函数，求前缀和就是 $15$ 次函数，直接拉格朗日插值求前 $\lfloor\frac{n}{2}\rfloor$ 项的和就做完了。

复杂度 $O(k^2T)$ 这里 $k$ 为函数次数加一，其实可以做到 $O(kT)$，但 $T$ 不是很大所以没什么影响。

一个小问题：

为什么不能直接对 $f_5$ 做拉插，这里我之前也没想通。其实是因为 $g$ 要分奇偶所以不是二次函数，而是:
$$
g_i=\frac{(i+1)^2\times((-1)^{i+1}+1)}{8}+\frac{i(i+2)\times((-1)^i+1)}{8}
$$ 
这样指数函数乘二次函数的形式，所以最后卷积出的 $f_5$ 不是多项式做不了拉插。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
ll fac[100]={1},sum[100],n=50;
inline ll rd()
{
    char c;ll f=1;
    while(!isdigit(c=getchar()))if(c=='-')f=-1;
    ll x=c-'0';
    while(isdigit(c=getchar()))x=x*10+(c^48);
    return x*f;
}
inline ll qp(ll x,ll y)
{
    ll res=1;
    while(y)
    {
        if(y&1) (res*=x)%=mod;
        (x*=x)%=mod,y>>=1;
    }
    return res;
}
ll C(ll n,ll m)
{
    ll s=1;
    for(int i=1;i<=m;i++) (s*=(n-i+1))%=mod;
    return s*qp(fac[m],mod-2)%mod;
}
ll ans(ll k)
{
    if(k<5) return 0;k-=5;
    n=min(50ll,k/2);
    for(int j=0;j<=n;j++)
        sum[j]=C(j+4,4)*C(k-2*j+10,10)%mod;
    k/=2;ll s=0;
    for(int j=1;j<=n;j++) (sum[j]+=sum[j-1])%=mod;
    if(k<=n) return (sum[k]+mod)%mod;
    for(int i=0;i<=n;i++)
    {
        ll s1=sum[i],s2=1;
        for(int j=0;j<=n;j++) if(j!=i)
            s1=s1*(k-j)%mod,s2=s2*(i-j)%mod;
        (s+=s1*qp(s2,mod-2)%mod)%=mod;
    }
    return (s+mod)%mod;
}
int main()
{
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    for(ll t=rd();t--;) printf("%lld\n",ans(rd()));
    return 0;
}
```

---

## 作者：小超手123 (赞：3)

##### 题意：

对于一个十元组 $(a_1, a_2, b_1, b_2, c_1, c_2, d_1, d_2, e_1, e_2)$，我们定义合法的十元组需要满足：

- $0 \leq a_1 < a_2$
- $0 \leq b_1 < b_2$
- $0 \leq c_1 < c_2$
- $0 \leq d_1 < d_2$
- $0 \leq e_1 < e_2$
- $a_1 + a_2 + b_1 + b_2 + c_1 + c_2 + d_1 + d_2 + e_1 + e_2 \leq n$

现在，给定 $n$，你需要计算出所有合法的十元组的 $(a_2 - a_1) \times (b_2 - b_1) \times (c_2 - c_1) \times (d_2 - d_1) \times (e_2 - e_1)$ 之和。

##### 分析：

一道考验基本功的题。

为了将 $<$ 这个条件消去，设

-  $\Delta a=a_{2}-a_{1},\Delta b=b_{2}-b_{1},\Delta c =c_{2}-c_{1},\Delta d=d_{2}-d_{1},\Delta e=e_{2}-e_{1}$

- $A=2a_{1},B=2b_{1},C=2c_{1},d=2d_{1},e=2e_{1}$

其中

- $\Delta a,\Delta b\dots\ge1$
- $A,B,\dots \ge 0$ 且全为偶数。

- $A+B+\dots+\Delta a+\Delta b\dots \le n$。

很明显需要转化成小球放盒子的问题。

要求 $\Delta a,\Delta b\dots\ge1$，把 $n$ 减掉 $5$（后文默认 $n$ 都要减 $5$），该条件就变成了 $\Delta a,\Delta b\dots\ge0$。

所以我们完成了一个映射：有 $n$ 个**无标号**的小球，$16$ 个**有标号**的盒子。前 $5$ 个盒子里的球的个数分别表示 $A,B,C,D,E$ 的值。第 $6 \sim15$ 个盒子的球的个数分别为 $\Delta a,\Delta b\dots\ge1$ 掰成两份的值（求的是 $\Delta a\Delta b\dots$，这是个经典的组合意义）。第 $16$ 个盒子的球的个数表示 $n$ 没分完的（$A+B+\dots+\Delta a+\Delta b\dots \le n$）。注意每个盒子都**可以为空**。

最后一个问题，如何保证前 $5$ 个盒子里球的个数均是偶数呢？直接枚举后面 $11$ 个盒子有 $i$ 个盒子是偶数。

那么对答案的贡献就是：
$$
\binom{x+16-1}{15} \binom{11}{i}
$$
其中 $x= \frac{n-(11-i)}{2}$。且 $n-(11-i)$ 是偶数。

时间复杂度 $O(T)$。带点常数。

##### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;


namespace Fastio {
const int L = 1 << 20;
inline char gc() {
    static char buf[L], *l = buf, *r = buf;
    if (l == r)
        r = (l = buf) + fread(buf, 1, L, stdin);
    return (l == r) ? EOF : *l++;
}
char obuf[L], *p = obuf;
inline void pc(char c) {
    if (p == obuf + L)
        fwrite(obuf, 1, L, stdout), p = obuf;
    *p++ = c;
}
inline void flush() { fwrite(obuf, 1, p - obuf, stdout); }
struct Reader {
    template <typename T>
    inline Reader& operator>>(T& x) {
        x = 0;
        short f = 1;
        char c = gc();
        while (!isdigit(c)) {
            if (c == '-')
                f = -1;
            c = gc();
        }
        while (isdigit(c)) x = 10 * x + (c - '0'), c = gc();
        x *= f;
        return *this;
    }
    Reader() {}
} cin;
struct Writer {
    template <typename T>
    inline Writer& operator<<(T x) {
        if (x < 0)
            pc('-'), x = -x;
        static short tp = 0, s[40];
        do
            s[++tp] = x % 10, x /= 10;
        while (x);
        while (tp) pc(s[tp--] + '0');
        return *this;
    }
    inline Writer& operator<<(const char* s) {
        int i = 0;
        while (s[i]) pc(s[i++]);
        return *this;
    }
    inline Writer& operator<<(char c) {
        pc(c);
        return *this;
    }
    Writer() {}
    ~Writer() { flush(); }
} cout;
#define cin Fastio::cin


#define cout Fastio::cout


}


int T, n, ans;

int Pow(int a, int n) {
	if(n == 0) return 1;
	if(n == 1) return a;
	int x = Pow(a, n / 2);
	if(n % 2 == 0) return x * x % mod;
	else return x * x % mod * a % mod;
}

int inv(int x) {
	return Pow((x + mod) % mod, mod - 2);
}

int cc[20], Inv[20];

int C(int n, int m) {
	if(n < 0 || m < 0 || n < m) return 0;
	int res = 1;
	for(int i = n; i >= n - m + 1; i--) res = res * i % mod;
	return res * Inv[m] % mod;
}

int CC(int n, int m) {
	if(n < 0 || m < 0 || n < m) return 0;
	int res = 1;
	for(int i = n; i >= n - m + 1; i--) res = res * i % mod;
	int t = 1;
	for(int i = 1; i <= m; i++) t = t * i % mod;
	return res * inv(t) % mod;
}

signed main() {

	for(int i = 0; i <= 15; i++) cc[i] = CC(11, i);
	Inv[0] = 1;
	for(int i = 1; i <= 15; i++) Inv[i] = Inv[i - 1] * i % mod;
	for(int i = 0; i <= 15; i++) Inv[i] = inv(Inv[i]);
	
	cin >> T;
	while(T--) {
		cin >> n; ans = 0;
		if(n < 5) {
			cout << 0 << "\n";
			continue;
		}
		n -= 5;
		for(int i = 0; i <= 11; i++) {
			if(n < (11 - i)) continue;
			int x = (n - (11 - i)) / 2;
			if((n - (11 - i)) % 2 == 1) continue;
			ans += CC(x + 16 - 1, 16 - 1) * cc[i] % mod;
			ans %= mod;
		}
		cout << ans << "\n";
	}

	return 0;
}
```

---

## 作者：luogu_gza (赞：2)

注意到 $f(i)=\lfloor \frac{(i+1)^2}{4} \rfloor$ 的差分序列为 `1 1 2 2 3 3 4 4...`。

不难推得其 gf 为 $\frac x{(1-x)^2(1-x^2)}$。

https://www.luogu.com.cn/article/6odmc7qq 已经清楚地指出 $$g(n)=\displaystyle{\sum_{i=1}^{n}\sum_{j=1}^{n-i}\sum_{k=1}^{n-i-j}\sum_{l=1}^{n-i-j-k}f(i)f(j)f(k)f(l)f(n-i-j-k-l)}$$ 的前缀和就是答案。

考虑答案的 gf 是 $f(i)$ 的 gf 的五次方的乘 $\frac1{1-x}$（具体意义是一次前缀和），也就是 $\frac{x^5}{(1-x)^{11}(1-x^2)^5}$。

一个无脑的想法是往上堆 bostan-mori 算法，因为模数不太对所以多项式乘法使用暴力，复杂度 $O(T \log n)$。

---

## 作者：analysis (赞：0)

啄题。

---

感觉上 limit 都用指数来限制。

对于一个 $(x,x+\Delta)$，贡献是 $\Delta$，代价是 $2x+\Delta$。枚举：
$$
\sum_{x \geq 0}\sum_{\Delta > 0}\Delta t^{2x+\Delta}=\sum_{x \geq 0}t^{2x}\sum_{\Delta > 0}\Delta t^{\Delta}\\
=\frac{t}{(1-t^2)(1-t)^2}
$$
事实上，要选 $5$ 对。然后有一个前缀和：
$$
[t^{N}]\frac{t^5}{(1-t^2)^5(1-t)^{11}}
$$
直接上 bostan-mori 就好了，$O(k^2\log{N})$，$k$ 大概二十左右。

---

```cpp
//begin 20:44
#include<bits/stdc++.h>
const int mod=1e9+7;
int fpow(int a,int b=mod-2){
    int r=1;
    while(b){
        if(b&1)r=1ll*r*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return r;
}
using namespace std;
#define poly vector<int>
poly mul(poly a,poly b){
    int n=(int)a.size()+(int)b.size()-1;
    poly r;r.clear();r.resize(n);
    for(int i=0;i<(int)a.size();i++){
        for(int j=0;j<(int)b.size();j++){
            r[i+j]=(r[i+j]+1ll*a[i]*b[j]%mod)%mod;
        }
    }
    return r;
}
int mori(poly f,poly g,int n){
    for(;n;n>>=1){
        poly gn=g;
        for(int i=1;i<(int)gn.size();i+=2)gn[i]=(mod-gn[i])%mod;
        f=mul(f,gn);g=mul(g,gn);
        int i;
        for(i=n&1;i<(int)f.size();i+=2)f[i>>1]=f[i];
        f.resize(i>>1);
        for(i=0;i<(int)g.size();i+=2)g[i>>1]=g[i];
        g.resize(i>>1);
    }
    if(f.empty())return 0;
    return 1ll*f[0]*fpow(g[0])%mod;
}
int T,n;
poly up,dn,tmp1,tmp2;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    up=poly(1,1);dn=poly(1,1);
    tmp1.resize(3),tmp2.resize(2);
    tmp1[0]=1,tmp1[2]=mod-1;tmp2[0]=1,tmp2[1]=mod-1;
    for(int i=1;i<=5;i++)dn=mul(dn,tmp1);
    for(int i=1;i<=11;i++)dn=mul(dn,tmp2);
    cin>>T;
    while(T--){
        cin>>n;
        if(n<5){cout<<"0\n";continue;}
        n-=5;
        cout<<mori(up,dn,n)<<'\n';
    }
}
//20:50
```

下播。

---

