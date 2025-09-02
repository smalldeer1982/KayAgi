# [XRCOI Round 1] B. 稻花香里说丰年

## 题目背景

**增加形式化题意。**
> 稻花香里说丰年，听取蛙声一片。

## 题目描述

稻田里有 $0$, $1$ 两种类型的青蛙。他们排成了 $a,b$ 两列。

Genius_Star 发现了这些青蛙，所以他决定将这两个青蛙队列分别划分为**起止点相同的**任意段，定义某一段的整齐度 $T$ 为：

$$
T(l,r) = \sum_{i=l}^r [a_i \ne b_i]
$$
其中 ：$[A]$ 表示若 $A$ 命题为真则为 $1$，否则为 $0$。


则对于段 $[l,r]$ 的带给 Genius_Star 的开心值为

$$
W(l,r) = T(l,r) \times \Big(A(l,r) + B(l,r) \Big)
$$

其中：

$A(l,r)$ 表示在 $a$ 序列的 $[l,r]$ 区间中包含的 $01$ 类型的子序列数量。

$B(l,r)$ 表示在 $b$ 序列的 $[l,r]$ 区间中包含的 $10$ 类型的子序列数量。

一个分段方案带给 Genius_Star 的开心值是所有小段带给他的开心值之和，你需要求出所有的分段方案带给他的开心值之和 $s$。

设分为了 $k$ 段，第 $i$ 段为 $[l_i, r_i](l_i \le r_i)$，需要满足：

- $l_1 = 1, r_k = n$。

- $\forall i \in[1, k), r_i + 1 = l_{i + 1}$。

则若两个分段的方案不同，当且仅当两个方案分的段数不同或者存在一个 $i$ 使得 $[l_i, r_i] \ne[l'_i, r'_i]$。

由于 Genius_Star 不能过于开心，你还需要将答案对 $10^9+7$ 取模。

### 形式化题意

给定一个两个序列 $a,b$ 。定义

-  $T(l,r)$ 为在区间 $[l,r]$ 中 $a_i\neq b_i$ 的个数。

-  $A(l,r)$ 表示 $a$ 序列在 $[l,r]$ 区间中的 $01$ 类型子序列个数。

-  $B(l,r)$ 表示 $b$ 序列在 $[l,r]$ 区间中的 $10$ 类型子序列个数。

-  $
   W(l,r) = T(l,r) \times \Big(A(l,r) + B(l,r) \Big)
   $。

其中：$xy$ 类型子序列表示从区间左端点开始向右顺次选择两个元素（**不要求连续**），其中，第一个数是 $x$ ，第二个数是 $y$。两个子序列不同当且仅当 $x$ 或 $y$ 所在位置不同。

现在你需要将两个序列划分成**起止点相同的**任意段，求所有划分方式的每段的 $W$ 之和。

由于答案可能很大，你需要将答案对 $10^9+7$ 取模。

## 说明/提示

### 样例解释 #1：

只有按照 $[1,3]$ 分段时，$W(1,3)=1$。

### 样例解释 #4：

可以得到：

$$f_1=1,f_2=1,f_3=2$$

$$g_1=1,g_2=1,g_3=3$$

得到：

$$(f_3)_2 = (00010)_2$$

$$(g_3)_2 = (00011)_2$$

则：

$$a = \{0,1,0,0,0\}$$

$$b = \{1,1,0,0,0\}$$

故答案为 $22$。

### 数据范围：

**本题采用捆绑测试。**

其中子任务 $0$ 为样例，记 $0$ 分。


| Subtask 编号 |         $n$         | $op$ | 特殊性质 | 得分 |
| :----------: | :-----------------: | :--: | :------: | :--: |
|     $1$      |     $\leq 100$      | $=0$ |    无    | $5$  |
|     $2$      |     $\leq 10^4$     | $=0$ |    无    | $10$ |
|     $3$      |     $\leq 10^6$     | $=0$ |   $A$    | $10$ |
|     $4$      |     $\leq 10^6$     | $=0$ |   $B$    | $10$ |
|     $5$      |     $\leq 10^6$     | $=1$ |    无    | $25$ |
|     $6$      | $\leq 5\times 10^7$ | $=1$ |    无    | $40$ |

特殊性质 $A$： $T(l,r) = r-l+1$。

特殊性质 $B$：有且仅有一个 $x$ 满足 $a_x \ne b_x$。

对于 $100 \%$ 的数据，保证 $1 \le n \le 5\times 10^7,1 \le x_1,x_2,y_1,y_2,z_1,z_2,f_1,f_2,g_1,g_2 \le 10^{18}$。

## 样例 #1

### 输入

```
3 0
1 0
1 1
0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 0
0 1
1 0
0 1
1 1
1 1
```

### 输出

```
70
```

## 样例 #3

### 输入

```
4 0
0 1
1 0
0 1
1 0
```

### 输出

```
52
```

## 样例 #4

### 输入

```
5 1
1 1 0 1 1
1 1 1 1 1
```

### 输出

```
22
```

## 样例 #5

### 输入

```
10000 1
1 1 0 1 1
1 1 1 1 1
```

### 输出

```
559297012```

# 题解

## 作者：gcx114514 (赞：3)

考虑将其拆分，$W(l,r)=T(l,r)*A(l,r)+T(l,r)*B(l,r)$。

然后将 $B$ 反转，也变成求 $01$，$T(l,r)$ 变成求相同，方便一些。

然后考虑求：对于每个 $[a_i=b_i]$，求与之匹配的 $01$ 子序列个数。

方便起见，我们正反跑两遍，分三类讨论（常数要大一些，不过好写很多）。

+ $01$ 全在 $[a_i=b_i]$ 前面。
+ $01$ 全在 $[a_i=b_i]$ 后面。
+ $0$ 在左边，$1$ 在右边。

先考虑第一种，其余的同理可以知道怎么做。

$01$ 全在左边时产生贡献当且仅当其与 $[a_i=b_i]$ 分在了同一个段，也就是 $0$ 的位置与 $i$ 在同一个段，假设 $0$ 在位置 $j$，则对答案的贡献是 $2^{j-1}\times 2^{n-i}$。

然后用 $res$ 把 $\sum 2^{j-1}$ 存下来，这个是容易的，出现 $0$ 时与出现 $1$ 时分开讨论。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define cin Fastio :: cin
#define cout Fastio :: cout
typedef unsigned long long ull;

const int mod=1e9+7;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    inline int Mod(const int& x){return x>=mod?x-mod:x;}
    modint() : val(0) {}
    modint(const int& m) : val(m) {}
    modint& operator-=(const modint& o) { return val = norm(val - o.val), *this; }
    modint& operator+=(const modint& o) { return val = Mod(val + o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator+(const modint& o) { return Mod(val+o.val); }
    modint operator*(const modint& o) const { return 1ll*val*o.val%mod; }
    inline void Mul(){val=Mod(val<<1);}
};
const modint inv2=(mod+1)/2;

const int N=1e5+10;
modint sum1,sum2,res,ans,pref,preg,suff,sufg;
bitset < 100000001 > f,g;
int n,op;

inline modint expow(modint x,int y){
	modint res=1;
	for(;y;y>>=1){if(y&1) res*=x;x*=x;}
	return res;
}

int main(){
	cin>>n>>op;register ull f1,f2,g1,g2,x1,y1,x2,y2,z1,z2,nowf,nowg;
	if(op==0){for(int i=1;i<=n;++i){cin>>x1>>y1;f[i]=x1;g[i]=!y1;}}
	else {
		cin>>x1>>y1>>z1>>f1>>f2;
		cin>>x2>>y2>>z2>>g1>>g2;
		int cnt=0;
		while(cnt+64<=n){
			nowf=f2*y1+f1*x1+z1;
			nowg=g2*y2+g1*x2+z2;
			f1=f2;f2=nowf;g1=g2;g2=nowg;
			for(int i=1;i<=64;++i){
				++cnt;
				f[cnt]=nowf&1;
				g[cnt]=(nowg&1)^1;
				nowf>>=1;nowg>>=1;
			}
		}
		nowf=f2*y1+f1*x1+z1;
		nowg=g2*y2+g1*x2+z2;
		f1=f2;f2=nowf;g1=g2;g2=nowg;
		for(int i=cnt+1;i<=n;++i){
			f[i]=nowf&1;
			g[i]=(nowg&1)^1;
			nowf>>=1;nowg>>=1;
		}
	}
	modint p1=expow(2,n),p2=inv2;
	for(int i=n;i;--i){
		p1*=inv2;p2.Mul();
		f[i]?sum1+=p2,suff+=p2:res+=sum1;
		g[i]?sum2+=p2,sufg+=p2:res+=sum2;
		ans+=(f[i]==g[i])?res*p1:0;
	}
	sum1=sum2=res=0;
	p1=expow(2,n);p2=inv2;
	for(int i=1;i<=n;++i){
		p1*=inv2;p2.Mul();
		f[i]?res+=sum1,suff-=p1:sum1+=p2;
		g[i]?res+=sum2,sufg-=p1:sum2+=p2;
		ans+=(f[i]==g[i])?res*p1+suff*pref+sufg*preg:0;
		(!f[i])?pref+=p2:0;
		(!g[i])?preg+=p2:0;
	}
	cout<<ans.val<<endl;
	return 0;
}
```

---

## 作者：CQ_Bab (赞：2)

# 前言
这题出得太好了，下次别出了。
# 思路
首先很能得出一个 dp，我们定义 $f_i$ 表示前 $i$ 个的开心值之和，然后转移为 $f_i=\sum f_j+(s_j-s_i)\times 2^{j-1}\times(sa_i-sa_j-(ca1_i-ca1_j)\times ca0_j)\times (sb_i-sb_j-(cb0_i-cb0_j)\times cb1_j)$，其中 $s_i$ 表示 $1\sim i$ 中 $a_i\neq b_i$ 的数量和，$sa_i$ 表示 $1\sim i$ 中 $01$ 子序列的数量，$ca1_i,ca0_i$ 分别表示 $1\sim i$ 中 $a_i=1/0$ 的数量，$sb_i$ 表示 $b$ 数组中 $10$ 子序列的数量，$cb_0$ 和 $cb_1$ 与 $ca0$ 和 $ca1$ 的意义相似。

然后我们考虑优化这个东西，当然只能拆开柿子了，拆开之后一共有 $16$ 个多项式，然后每一个带 $j$ 的多项式都维护一个前缀和即可，这个就不讲了。

但是，这道题还要卡空间所以我们只能开一个 $5\times 10^7$ 的数组，那么我们要将 $s,sa,sb,ca0,ca1,cb0,cb1$ 都在遍历到 $i$ 的时候计算，可是我们发现对于 $op=1$ 的情况 $f,g$ 数组都要开到 $n$，那不是炸了吗，但是我们发现对于 $n$ 会用到的 $f,g$ 下标只到 $\lfloor \frac{n}{64} \rfloor+3$ 也就只用算到这个位置了，然后就能开下了。
# 代码
简直就是~~石山~~，注意卡常。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;++i)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
}
int T=1;
int n,op;
const int N=5e7+10,mod=1e9+7;
unsigned long long ff[N],g[N];
int sum,f;
#define pl(x,y) (x=(x+y)%mod)
#define pl1(x,y) (x=(x+((y)%mod+mod))%mod)
fire main() {
	in(n),in(op);
	if(op==1) {
		unsigned long long x1,y1,z1,x2,y2,z2;
		in(x1),in(y1),in(z1),in(ff[1]),in(ff[2]);
		in(x2),in(y2),in(z2);
		in(g[1]),in(g[2]);
		rep(i,3,782000) {
			ff[i]=(ff[i-2]*x1+ff[i-1]*y1+z1);
			g[i]=(g[i-2]*x2+g[i-1]*y2+z2);
		}
	}else {
		rep(i,1,n) in(ff[i]),in(g[i]);
	}
	int s=0,cb0=0,cb1=0,ca0=0,ca1=0,sa=0,sb=0,jc=1,f=0;
	int saj=0,sbj=0,ca01=0,ca1ca0=0,cb11=0,sj=0,cb0cb1=0;
	int sas=0,sbs=0,sca0=0,sca1ca0=0,cb1s=0,cb0cb1s=0,s2j=1;
	rep(i,1,n) {
		int a=0,b=0;
		if(op==0) {
			a=ff[i],b=g[i];
		}else {
			a=((ff[((i-1)>>6)+3]>>((i-1)&63))&1);
			b=((g[((i-1)>>6)+3]>>((i-1)&63))&1);
		}
		s=(s+(a!=b));
		cb0=(cb0+(b==0));
		cb1=i-cb0;
		ca0=(ca0+(a==0));
		ca1=i-ca0;
		sa=(sa+(a==1)*ca0)%mod;
		sb=(sb+(b==0)*cb1)%mod;
		f=sum;
		int gg=sa+sb;
		gg=(gg*s2j);
		pl1(gg,-saj-sbj);
		pl1(gg,ca1ca0-(ca1*ca01));
		pl1(gg,cb0cb1-(cb0*cb11));
		pl(f,gg*s);
		
		pl(s2j,jc);
		pl(saj,sa*jc);
		pl(sbj,sb*jc);
		pl(ca01,ca0*jc);
		pl(ca1ca0,ca1*ca0%mod*jc);
		pl(cb11,cb1*jc);
		pl(cb0cb1,cb0*cb1%mod*jc);
		
		int gg1=0;
		pl(gg1,(sa+sb)*sj);
		pl1(gg1,-sas-sbs);
		pl1(gg1,sca1ca0-(ca1*sca0));
		pl1(gg1,cb0cb1s-(cb0*cb1s));
		pl1(f,-gg1);
		
		
		pl(sj,s*jc);
		pl(sas,s*sa%mod*jc);
		pl(sbs,s*sb%mod*jc);
		pl(sca0,ca0*s%mod*jc);
		pl(sca1ca0,s*ca1%mod*ca0%mod*jc);
		pl(cb1s,cb1*s%mod*jc);
		pl(cb0cb1s,cb1*cb0%mod*s%mod*jc);
		sum=(sum+f)%mod;
		jc=jc*2%mod;
	}
	print(f);
	return false;
}
```

---

## 作者：UniGravity (赞：2)

一种思维难度小但比难写的做法。

考虑钦定一段区间然后统计区间被算多少次。发现 $[l,r]$ 一共会被算 $2^{l-2}2^{n-r-1}$ 次。注意这里把 $2^{-1}$ 看作 $1$。

首先考虑如何算出 $A(l,r)$，考虑 $c_{i,k}$ 表示 $\sum_{j=1}^i[a_j=k]$，然后记 $s_i$ 表示 $\sum_{j=1}^i[a_j=1]c_{j,0}$，即 $s_i=A(1,i)$。

则 $A(l,r)=s_r-s_{l-1}-(c_{r,1}-c_{l-1,1})c_{l-1,0}$，代表把 $s_i$ 中多出的 $c_{l-1,0}$ 扣出去。

那么区间 $[l,r]$ 只算 $A$ 的答案即为 $2^{l-2}2^{n-r-1}(t_r-t_{l-1})[s_r-s_{l-1}-(c_{r,1}-c_{l-1,1})c_{l-1,0}]$。这里 $t_i=\sum_{j=1}^i[a_j=b_j]$。发现贡献对于 $l,r$ 是独立的，因此可以通过前缀和 $O(1)$ 统计。$B$ 的做法和 $A$ 一样。

难写的地方是要对拆开上面的式子然后每一项分别前缀和。同时这个做法常数比较大，卡常的方法是把相同的几项并在一起并且 $A,B$ 一起做。时间复杂度 $O(n)$。

```cpp
const int N=50000005,P=1000000007;
int n,a[N],b[N];ll ans=0;
ll pwn,i2;
il ll fpow(ll x,ll n){ll a=1;while(n){if(n&1)a=a*x%P;x=x*x%P,n>>=1;}return a;}
il void addto(ll &x,ll y){x+=y;if(x>=P)x-=P;}
il void delto(ll &x,ll y){x-=y;if(x<0)x+=P;}

il void solve(){
    ll s1=0,s2=0,s3=0,s4=0,s5=0,s6=0,s7=0,s8=0,t=0,s=0,c0=0,c1=0,c2=0,c3=0,res,pw1=1,pw2=pwn;
    forto(i,1,n){
        addto(s1,pw1);
        addto(s2,pw1*c0%P);
        addto(s3,pw1*c2%P);
        addto(s4,pw1*(c1*c0%P+c3*c2%P-s+P)%P);
        addto(s5,pw1*t%P);
        addto(s6,pw1*t%P*c0%P);
        addto(s7,pw1*t%P*c2%P);
        addto(s8,pw1*t%P*(c1*c0%P+c3*c2%P-s+P)%P);
        t+=(a[i]!=b[i]);
        if(a[i])addto(s,c0),c1++;else c0++;
        if(!b[i])addto(s,c2),c3++;else c2++;
        res=0;
        addto(res,s1*t%P*s%P);
        delto(res,s2*t%P*c1%P);
        delto(res,s3*t%P*c3%P);
        addto(res,s4*t%P);
        delto(res,s5*s%P);
        addto(res,s6*c1%P);
        addto(res,s7*c3%P);
        delto(res,s8);
        addto(ans,res*pw2%P);
        if(i>1)pw1=2*pw1%P;
        if(i<n-1)pw2=i2*pw2%P;
    }
}

unsigned ll f[800005];
il void init(int a[]){
    unsigned ll x=read(),y=read(),z=read();f[1]=read(),f[2]=read();
    forto(i,3,(n-1)/64+3)f[i]=f[i-2]*x+f[i-1]*y+z;
    forto(i,1,n)a[i]=(f[(i-1)/64+3]>>((i-1)%64))&1;
}

signed main(){
    n=read();int op=read();
    pwn=1;forto(i,1,n-2)pwn=2*pwn%P;
    i2=fpow(2,P-2);
    if(!op)forto(i,1,n)a[i]=read(),b[i]=read();
    else init(a),init(b);
    solve();
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：2672434062xzl (赞：1)

## $O(n^2)$ 15pts
对于 $T(l,r)$ 可采用前缀和的方法。

设 $sum_n=\sum_{i=1}^{n} [a_i\ne b_i]$,$T(l,r)=sum_r-sum_{l-1}$。

对于 $A(l,r)$ 在 $[l,r]$ 中的 $0$ 统计其后有多少 $1$，所以 $A(l,r)=\sum_{i=l}^{r} \left (  [a_i=0]\times \sum_{j=i+1}^{r}[a_j=1] \right )$。

同理可得 $B(l,r)=\sum_{i=l}^{r} \left (  [b_i=1]\times \sum_{j=i+1}^{r}[b_j=0] \right )$。

二者皆可以用前缀和优化，设 $s1_n=\sum_{i=1}^{n}[a_i=0]$，则 $A(l,r)=\sum_{i=l}^{r} \left (  [a_i=0]\times (r-s1_r-i+s1_i) \right )$。

$$A(l,r)=(r-s1_r)\sum_{i=l}^{r}   [a_i=0]-\sum_{i=l}^{r}[a_i=0]\times(i-s1_i)\\
=(r-s1_r)(s1_r-s1_{l-1})-\sum_{i=l}^{r}[a_i=0]\times(i-s1_i)$$。

对后半部分再用一次前缀和，设 $s3_n=\sum_{i=1}^{n}[a_i=0]\times(i-s1_i)$，则 $A(l,r)=(r-s1_r)(s1_r-s1_{l-1})-(s3_r-s3_{l-1})$。

同理可得，设 $s2_n=\sum_{i=1}^{n}[b_i=1]$，$s3_n=\sum_{i=1}^{n}[b_i=1]\times(i-s2_i)$，$B(l,r)=(r-s2_r)(s2_r-s2_{l-1})-(s4_r-s4_{l-1})$。

考虑区间 $[l,r]$，左边 $l-1$ 个数，会有 $l-2$ 个空隙，每个空隙可以隔开空隙两边，所以左边方案数为 $2^{\max(l-2,0)}$，同理可得右边为 $2^{\max(n-r-1,0)}$。

所以答案为 $\sum_{l=1}^{n}\sum_{r=l}^{n} 2^{\max(l-2,0)}2^{\max(n-r-1,0)}((r-s1_r)(s1_r-s1_{l-1})-(s3_r-s3_{l-1})+(r-s2_r)(s2_r-s2_{l-1})-(s4_r-s4_{l-1}))$。

对 $s3,s4$ 合并, $s3_n=\sum_{i=1}^{n} [a_i=0]\times (i-s1_i)+[b_i=1]\times (i-s2_i)$。

答案为 $\sum_{l=1}^{n}\sum_{r=l}^{n} 2^{\max(l-2,0)}2^{\max(n-r-1,0)}((r-s1_r)(s1_r-s1_{l-1})+(r-s2_r)(s2_r-s2_{l-1})-(s3_r-s3_{l-1})$。

参考程序：
```cpp
#include<iostream>
using namespace std;
using ll=long long;
const ll N=1e4+10,mod=1e9+7;
ll sum[N],s1[N],s2[N],s3[N];
ll p[N];
bool a[N],b[N];
int main(){
	int n,op;
	cin>>n>>op;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&a[i],&b[i]);
		sum[i]=sum[i-1]+(a[i]!=b[i]);
	}
	for(int i=1;i<=n;++i)s1[i]=s1[i-1]+(a[i]==0); 
	for(int i=1;i<=n;++i)s2[i]=s2[i-1]+(b[i]==1); 
	for(int i=1;i<=n;++i)s3[i]=(s3[i-1]+(a[i]==0)*(i-s1[i])+(b[i]==1)*(i-s2[i]))%mod;
	ll ans=0;
	p[0]=1;
	for(int i=1;i<=n;++i)p[i]=p[i-1]*2%mod;
	for(int l=1;l<=n;++l)
		for(int r=l;r<=n;++r){
			ans+=p[max(n-r-1,0)]*p[max(l-2,0)]%mod*(sum[r]-sum[l-1])%mod
			*((r-s1[r])*(s1[r]-s1[l-1])%mod+(r-s2[r])*(s2[r]-s2[l-1])%mod-(s3[r]-s3[l-1]))%mod;
			ans%=mod;
		}
	cout<<ans;
	return 0;
}
```
## $O(n)$ 60pts

考虑再次使用前缀和优化。

对于每个 r，求出 $2^{\max(n-r-1,0)}\times \sum_{l=1}^r2^{\max (l-2,0)}\times (sum_r-sum_{l-1})\times 
[(r-s1_r)(s1_r-s1_{l-1})+(r-s2_r)(s2_r-s2_{l-1})-(s3_r-s3_{l-1})]$。

对上式后半部分整理得

$
(r-s1_r)(s1_r-s1_{l-1})+(r-s2_r)(s2_r-s2_{l-1})-(s3_r-s3_{l-1})=
(r-s1_r)s1_r+(r-s2_r)s2_r-s3_r-(r-s1_r)s1_{l-1}-(r-s2_r)s2_{l-1}+s3_{l-1}\\
$。

再乘上 $(sum_r-sum_{l-1})$ 这一项

$$(sum_r-sum_{l-1})\times ((r-s1_r)s1_r+(r-s2_r)s2_r-s3_r-(r-s1_r)s1_{l-1}-(r-s2_r)s2_{l-1}+s3_{l-1})=\\
((r-s1_r)s1_r+(r-s2_r)s2_r-s3_r)sum_r-(r-s1_r)sum_r\times s1_{l-1}-(r-s2_r)sum_r\times s2_{l-1}+sum_r\times s3_{l-1}\\
-((r-s1_r)s1_r+(r-s2_r)s2_r-s3_r)sum_{l-1}+(r-s1_r)sum_{l-1}\times s1_{l-1}+(r-s2_r)sum_{l-1}\times s2_{l-1}-sum_{l-1}\times s3_{l-1}$$。

乘上 $2^{\max (i-2,0)}$ 后对每一部分进行前缀和

$$sump_n=\sum_{i=1}^{n}2^{\max (i-2,0)} \\
s4_n=\sum_{i=1}^{n} 2^{\max (i-2,0)}sum_{i-1}\\
s5_n=\sum_{i=1}^{n} 2^{\max (i-2,0)}s1_{i-1}\\
s6_n=\sum_{i=1}^{n} 2^{\max (i-2,0)}s2_{i-1}\\
s7_n=\sum_{i=1}^{n} 2^{\max (i-2,0)}s3_{i-1}\\
s8_n=\sum_{i=1}^{n} 2^{\max (i-2,0)}sum_{i-1}\times s1_{i-1}\\
s9_n=\sum_{i=1}^{n} 2^{\max (i-2,0)}sum_{i-1}\times s2_{i-1}\\
s10_n=\sum_{i=1}^{n} 2^{\max (i-2,0)}sum_{i-1}\times s3_{i-1}\\
\\
$$


答案即为
$\sum_{i=1}^n
((i-s1_i)s1_i+(i-s2_i)s2_i-s3_i)sum_i\times sump_i-(i-s1_i)sum_i\times s5_{i}-(i-s2_i)sum_i\times s6_{i}+sum_i\times s7_{i}
-((i-s1_i)s1_i+(i-s2_i)s2_i-s3_i)s4_{i}+(i-s1_i)s8_{i}+(i-s2_i)s9_{i}-s10_{i}
\\
$。

至于特殊输入的部分, 对 $2^{64}$ 取模可以用`unsigned long long` 自然溢出代替。

参考程序：

```cpp
#include<iostream>
using namespace std;
using ll=long long;
const ll N=1e6+10,mod=1e9+7;
ll sum[N],s1[N],s2[N],s3[N],s4[N],s5[N],s6[N],s7[N],s8[N],s9[N],s10[N];
ll p[N],sump[N];
bool a[N],b[N];
int n;
void init(bool op){
    if(!op){
        for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i],&b[i]);
        return;
    }
    unsigned long long x1,y1,z1,f1,f2;
    unsigned long long x2,y2,z2,g1,g2,tmp;
    scanf("%llu%llu%llu%llu%llu",&x1,&y1,&z1,&f1,&f2);
    scanf("%llu%llu%llu%llu%llu",&x2,&y2,&z2,&g1,&g2);
    for(int i=0;i<=n/64;++i){
        f1=f1*x1+f2*y1+z1;
        swap(f1,f2);
        for(int j=0;j<64;++j)
            a[i*64+j+1]=(f2>>j)&1ull;
    }
    for(int i=0;i<=n/64;++i){
        g1=g1*x2+g2*y2+z2;
        swap(g1,g2);
        for(int j=0;j<64;++j)
            b[i*64+j+1]=(g2>>j)&1ull;
    }
}
int main(){
	int op;
	cin>>n>>op;
    init(op);
	for(int i=1;i<=n;++i)sum[i]=sum[i-1]+(a[i]!=b[i]);
	for(int i=1;i<=n;++i)s1[i]=s1[i-1]+(a[i]==0);
	for(int i=1;i<=n;++i)s2[i]=s2[i-1]+(b[i]==1); 
	for(int i=1;i<=n;++i)s3[i]=(s3[i-1]+(b[i]==1)*(i-s2[i])+(a[i]==0)*(i-s1[i]))%mod;
    p[0]=1;
	for(int i=1;i<=n;++i)p[i]=p[i-1]*2ll%mod;
	for(int i=1;i<=n;++i)sump[i]=(sump[i-1]+p[max(i-2,0)])%mod;
	for(int i=1;i<=n;++i)s4[i]=(s4[i-1]+p[max(i-2,0)]*sum[i-1]%mod)%mod;
	for(int i=1;i<=n;++i)s5[i]=(s5[i-1]+p[max(i-2,0)]*s1[i-1]%mod)%mod;
	for(int i=1;i<=n;++i)s6[i]=(s6[i-1]+p[max(i-2,0)]*s2[i-1]%mod)%mod;
	for(int i=1;i<=n;++i)s7[i]=(s7[i-1]+p[max(i-2,0)]*s3[i-1]%mod)%mod;
	for(int i=1;i<=n;++i)s8[i]=(s8[i-1]+p[max(i-2,0)]*s1[i-1]%mod*sum[i-1]%mod)%mod;
	for(int i=1;i<=n;++i)s9[i]=(s9[i-1]+p[max(i-2,0)]*s2[i-1]%mod*sum[i-1]%mod)%mod;
	for(int i=1;i<=n;++i)s10[i]=(s10[i-1]+p[max(i-2,0)]*s3[i-1]%mod*sum[i-1]%mod)%mod;
	ll ans=0;
	for(ll i=1;i<=n;++i){
		ll tmp=0;
		tmp+=sump[i]*((i-s1[i])*s1[i]%mod+(i-s2[i])*s2[i]%mod-s3[i]+mod)%mod*sum[i];
		tmp=(tmp-((i-s1[i])*s1[i]%mod+(i-s2[i])*s2[i]%mod-s3[i]+mod)%mod*s4[i]%mod+mod)%mod;
		tmp=(tmp-(i-s1[i])*sum[i]%mod*s5[i]%mod+mod)%mod;
		tmp=(tmp-(i-s2[i])*sum[i]%mod*s6[i]%mod+mod)%mod;
		tmp=(tmp+sum[i]*s7[i]%mod)%mod;
		tmp=(tmp+(i-s1[i])*s8[i]%mod)%mod;
		tmp=(tmp+(i-s2[i])*s9[i]%mod)%mod;
		tmp=(tmp-s10[i]%mod+mod)%mod;
		ans+=p[max(n-i-1,0ll)]*tmp%mod;
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

## $O(n)$ 100pts

显然开 $13$ 个 $5\times 10^7$ 的数组是会 CE，即使只开 $5$ 个也会 MLE，因此这里要用数代替数组，在统计的同时，更新前缀和数组。

上面代码中取模运算较多，需卡常，否则会 TLE，要合并一些取模运算。

参考程序：

```cpp
#include<iostream>
using namespace std;
using ll=long long;
const ll N=5e7+10,mod=1e9+7;
ll sum,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
ll p[N],sump;
bool a[N],b[N];
int n;
bool read(){
    char ch=getchar();
    while(ch<'0'||ch>'1')ch=getchar();
    return ch-'0';
}
void init(bool op){
    if(!op){
        for(int i=1;i<=n;++i){
            a[i]=read();
            b[i]=read();
        }
        return;
    }
    unsigned long long x1,y1,z1,f1,f2;
    unsigned long long x2,y2,z2,g1,g2;
    scanf("%llu%llu%llu%llu%llu",&x1,&y1,&z1,&f1,&f2);
    scanf("%llu%llu%llu%llu%llu",&x2,&y2,&z2,&g1,&g2);
    for(int i=0;i<=n/64;++i){
        f1=f1*x1+f2*y1+z1;
        swap(f1,f2);
        for(int j=0;j<64;++j)
            a[i*64+j+1]=(f2>>j)&1ull;
    }
    for(int i=0;i<=n/64;++i){
        g1=g1*x2+g2*y2+z2;
        swap(g1,g2);
        for(int j=0;j<64;++j)
            b[i*64+j+1]=(g2>>j)&1ull;
    }
}
int main(){
	int op;
	cin>>n>>op;
    init(op);
    p[0]=1;
	for(ll i=1;i<=n;++i)p[i]=(p[i-1]<<1ll)%mod;
	ll ans=0;
	for(ll i=1;i<=n;++i){
		ll p1=p[max(i-2,0ll)],p2=p[max(i-2,0ll)]*sum%mod;
	    sump=(sump+p1)%mod;
	    s4=(s4+p2)%mod;
	    s5=(s5+p1*s1%mod)%mod;
	    s6=(s6+p1*s2%mod)%mod;
	    s7=(s7+p1*s3%mod)%mod;
	    s8=(s8+p2*s1%mod)%mod;
	    s9=(s9+p2*s2%mod)%mod;
	    s10=(s10+p2*s3%mod)%mod;
        s1+=!a[i];
        s2+=b[i];
        s3=(s3+b[i]*(i-s2)+(!a[i])*(i-s1))%mod;
        sum=sum+(a[i]!=b[i]);
		ans+=p[max(n-i-1,0ll)]*(((i-s1)*s1%mod+(i-s2)*s2%mod-s3+mod)%mod*(sump*sum%mod-s4+mod)%mod+(sum*s7%mod-s10+mod)+(i-s1)*(s8-sum*s5%mod+mod)%mod+(i-s2)*(s9-sum*s6%mod+mod)%mod)%mod;
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

