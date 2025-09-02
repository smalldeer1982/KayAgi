# Intersection and Union

## 题目描述

You are given $ n $ segments on the coordinate axis. The $ i $ -th segment is $ [l_i, r_i] $ . Let's denote the set of all integer points belonging to the $ i $ -th segment as $ S_i $ .

Let $ A \cup B $ be the union of two sets $ A $ and $ B $ , $ A \cap B $ be the intersection of two sets $ A $ and $ B $ , and $ A \oplus B $ be the symmetric difference of $ A $ and $ B $ (a set which contains all elements of $ A $ and all elements of $ B $ , except for the ones that belong to both sets).

Let $ [\mathbin{op}_1, \mathbin{op}_2, \dots, \mathbin{op}_{n-1}] $ be an array where each element is either $ \cup $ , $ \oplus $ , or $ \cap $ . Over all $ 3^{n-1} $ ways to choose this array, calculate the sum of the following values:

 $ $$$|(((S_1\ \mathbin{op}_1\ S_2)\ \mathbin{op}_2\ S_3)\ \mathbin{op}_3\ S_4)\ \dots\ \mathbin{op}_{n-1}\ S_n| $ $ </p><p>In this expression,  $ |S| $  denotes the size of the set  $ S$$$.

## 样例 #1

### 输入

```
4
3 5
4 8
2 2
1 9```

### 输出

```
162```

## 样例 #2

### 输入

```
4
1 9
3 5
4 8
2 2```

### 输出

```
102```

# 题解

## 作者：_Life_ (赞：7)

### 题意

有 $n$ 个集合 $S_1,S_2,\cdots,S_n$。

$S_i=\left\{ x|x\in [L_i,R_i],x\in \N \right\}$

有三种集合间的二元运算，分别为交（ $\cap$ ）、并（ $\cup$ ）、对称差（ $\oplus$ ）。

规定每种运算优先级相同，运算顺序从左向右。

$a \cap b=\left\{ x| x \in a \operatorname{and} x \in b \right\}$

$a \cup b=\left\{ x| x \in a \operatorname{or} x \in b \right\}$

$a \oplus b=\left\{ x| x \in a, x \not \in b \operatorname{or} x \not \in a, x \in b \right\}$

有 $n-1$ 个运算符 $op_1,op_2,\cdots,op_{n-1}(op_i\in \left\{ \cap,\cup,\oplus \right\})$。

对于 $op_i$ 的 $3^{n-1}$ 种方案，求出：

$$\left| S_1\ op_1\ S_2  \ op_2 \ \cdots \ op_{n-1} \ S_n \right|$$

之和。

$1 \leq n \leq 3\times 10^5$

$0 \leq L_i,R_i \leq 3\times 10^5$

### 题解

前置知识：乘法逆元、线段树懒标记。

---

可以把原问题转化成以下的形式：

有 $n$ 个 $\texttt{01}$ 串 $S_1,S_2,\cdots,S_n$。

$S_i$ 第 $[L_i,R_i]$ 位为 $\texttt{1}$，其余位为 $\texttt{0}$。

有三种运算，分别为与（ $\land$ ），或（ $\lor$ ），异或（ $\oplus$ ）。

规定每种运算优先级相同，运算顺序从左向右。

有 $n-1$ 个运算符 $op_1,op_2,\cdots,op_{n-1}(op_i\in \left\{ \land,\lor,\oplus \right\})$。

求出：

$$S_1\ op_1\ S_2  \ op_2 \ \cdots \ op_{n-1} \ S_n$$

中 $\texttt{1}$ 的期望个数，乘以 $3^{n-1}$。

---

考虑把每一位拆开分别计算贡献。

$p_i$ 表示 $\texttt{01}$ 串第 $i$ 位为 $\texttt{1}$ 的概率。

$p_i$ 与 $\texttt{1}$ 后，$p_i'=1$。

$p_i$ 或 $\texttt{1}$ 后，$p_i'=p_i$。

$p_i$ 异或 $\texttt{1}$ 后，$p_i'=1-p_i$。

$p_i$ 与 $\texttt{0}$ 后，$p_i'=0$。

$p_i$ 或 $\texttt{0}$ 后，$p_i'=p_i$。

$p_i$ 异或 $\texttt{0}$ 后，$p_i'=p_i$。

$p_i$ 和 $\texttt{1}$ 进行一次随机操作后，$p_i'=\dfrac{(1)+(p_i)+(1-p_i)}{3}=\dfrac{2}{3}$。

$p_i$ 和 $\texttt{0}$ 进行一次随机操作后，$p_i'=\dfrac{(0)+(p_i)+(p_i)}{3}=\dfrac{2}{3}p_i$。

---

$E_i$ 表示 $\texttt{01}$ 串第 $i$ 位为 $\texttt{1}$ 的期望，$E_i=p_i$。

$E$ 表示 $\texttt{01}$ 串中 $\texttt{1}$ 的期望个数，$E=\sum E_i=\sum p_i$。

只要能够高效维护 $p_i$ 的变动，就可以快速计算 $E$。

发现所有的 $\texttt{01}$ 串中 $\texttt{1}$ 都是连续的，并且只有一段，看上去非常的线段树。

和 $\texttt{1}$ 的随机操作可以看作区间推平成 $\dfrac{2}{3}$。

和 $\texttt{0}$ 的随机操作可以看作区间乘 $\dfrac{2}{3}$。

区间 $[1,L_i-1]$ 和 $\texttt{0}$ 随机操作，区间 $[L_i,R_i]$ 和 $\texttt{1}$ 随机操作，区间 $[R_i+1,V]$ 和 $\texttt{0}$ 随机操作。

用懒标记维护就好啦！

---

没看见 $L_i,R_i$ 可以取到 $0$，被数据创思了。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
using namespace std;
typedef pair<int,int> pii;
void setIn(string s){freopen(s.c_str(),"r",stdin);}
void setOu(string s){freopen(s.c_str(),"w",stdout);}
void setIO(string s){setIn(s+".in"),setOu(s+".out");}
template<class T>void chkmax(T &a,T b){a=max(a,b);}
template<class T>void chkmin(T &a,T b){a=min(a,b);}
template<class T>T read(T &x)
{
	x=0;T f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*=f;
}
template<class T,class ...L>void read(T &x,L &...l){read(x),read(l...);}
template<class T>void write(T x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);}putchar(x%10+'0');
}
template<class T>void write(T x,char c){write(x),putchar(c);}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;a=a*a%mod,b>>=1)
		if(b&1)ans=ans*a%mod;
	return ans;
}
int inv(int x){return qpow(x,mod-2);}
const int QwQ=2*inv(3)%mod;
const int V=300005;
#define ls (pos<<1)
#define rs (pos<<1|1)
#define mid ((l+r)>>1)
int sum[300015<<2],tag1[300015<<2],tag2[300015<<2];
// tag1 区间推平成 2/3 的 tag2 次幂
// tag2 区间乘 2/3
void pushup(int pos)
{
	sum[pos]=(sum[ls]+sum[rs])%mod;
}
void pushdown(int pos,int l,int r)
{
	if(tag1[pos])
	{
		tag1[ls]=1,tag2[ls]=tag2[pos];
		tag1[rs]=1,tag2[rs]=tag2[pos];
		sum[ls]=qpow(QwQ,tag2[pos])*(mid-l+1)%mod;
		sum[rs]=qpow(QwQ,tag2[pos])*(r-mid)%mod;
	}
	else if(tag2[pos])
	{
		tag2[ls]+=tag2[pos];
		tag2[rs]+=tag2[pos];
		sum[ls]=qpow(QwQ,tag2[pos])*sum[ls]%mod;
		sum[rs]=qpow(QwQ,tag2[pos])*sum[rs]%mod;
	}
	tag1[pos]=0,tag2[pos]=0;
	pushup(pos);
}
void build(int lx,int rx,int pos=1,int l=1,int r=V)
{
	if(l==r){sum[pos]=(lx<=l&&r<=rx);return;}
	build(lx,rx,ls,l,mid),build(lx,rx,rs,mid+1,r);
	pushup(pos);
}
void upd1(int lx,int rx,int pos=1,int l=1,int r=V)
{
	if(lx<=l&&r<=rx)
	{
		sum[pos]=(r-l+1)*QwQ%mod;
		tag1[pos]=1,tag2[pos]=1;
		return;
	}
	pushdown(pos,l,r);
	if(lx<=mid)upd1(lx,rx,ls,l,mid);
	if(rx>mid)upd1(lx,rx,rs,mid+1,r);
	pushup(pos);
}
void upd2(int lx,int rx,int pos=1,int l=1,int r=V)
{
	if(lx<=l&&r<=rx)
	{
		tag2[pos]++;
		sum[pos]=sum[pos]*QwQ%mod;
		return;
	}
	pushdown(pos,l,r);
	if(lx<=mid)upd2(lx,rx,ls,l,mid);
	if(rx>mid)upd2(lx,rx,rs,mid+1,r);
	pushup(pos);
}
int n,l,r;
signed main()
{
	read(n);
	read(l,r);l++,r++;
	build(l,r);
	rep(i,2,n)
	{
		read(l,r);l++;r++;
		upd1(l,r);
		if(l!=1)upd2(1,l-1);
		if(r!=V)upd2(r+1,V);
	}
	write(sum[1]*qpow(3,n-1)%mod);
}
```

---

## 作者：uid_310801 (赞：4)

#### 题意   
给定若干个线段 $S_i=[L_i,R_i]$，两个线段之间有交，并和异或 $3$ 种操作。   

对于  

$$|(((S_1\space opt_1\space S_2)\space opt_2\space S_3)\space ...\space opt_{n-1}\space S_n)|$$

求所有 $3^{n-1}$ 种操作序列的结果的总和。$|S|$表示被 $S$ 覆盖的点的个数。

#### 解析

考虑每个值对答案的贡献。

若一个值 $i$ 最后一次被包含是在 $S_n$，那么对于从 $S_{1}$ 到 $S_{n-1}$ 的任意操作序列，若当前的答案包含 $i$，可以选择交上 $S_n$ 或者并上 $S_n$ ；若不包含 $i$ 可以选择异或上 $S_n$ 或者并上 $S_n$ 。包含或者不包含都只有两种选择。所以 $i$ 对答案的贡献是 $3^{n-2}\times 2$.

类似地，若一个值 $i$ 最后一次被包含是在 $S_k$，那么从 $S_1$ 到 $S_{k-1}$ 的任意操作序列，$(((S_1\space opt_1\space S_2)\space opt_2\space S_3)\space ...\space opt_{k-1}\space S_k)$ 包含i的操作序列的数量为 $3^{k-2}\times 2$.对于从 $S_k+1$ 到 $S_n$ 的所有线段，因为它们每个都不包含 $i$，要让答案包含 $i$，需要每次的操作都必须是并或者异或。所以最终 $i$ 对答案的贡献就是 $3^{k-2}\times 2^{n-k+1}$。   
另外 $S_1$,$S_2$贡献都是 $2^{n-1}$.

要求 $k$，可以写一个支持区间赋 $1$ 和区间查询的数据结构，做法就是从后往前枚举线段，每次查询$[L,R]$中有多少位是 $0$，算出贡献直接加到答案中，然后把区间赋 $1$。使用线段树即可。

时间复杂度 $O(n\log V)$，其中 $V$ 是值域，可以动态开点或离散化扩展到 $10^9$ 的级别。

#### 代码

```cpp
/********************
  *author:Spouter_27
  *place:spst Alego
  *with:marmoreal_777
********************/
#include<bits/stdc++.h>
#define ls (nw<<1)
#define rs ((nw<<1)|1)
#define mid ((l+r)>>1)
using namespace std;
typedef long long ll;
const ll N=3e5+10,mod=998244353;
ll n,l[N],r[N],p[N],t[N<<2],tg[N<<2],ans;
ll qpow(ll a,ll b){//贡献可以改用预处理，其实不需要求快速幂。
	ll ans=1,base=a;
	while(b){
		if(b&1)	ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans;
}
void update(ll nw,ll l,ll r,ll x,ll y){
	if(x<=l&&y>=r){
		tg[nw]=1;
		t[nw]=r-l+1;
		return;
	}
	if(tg[nw])	return;
	if(x<=mid)	update(ls,l,mid,x,y);
	if(y>mid)	update(rs,mid+1,r,x,y);
	t[nw]=t[ls]+t[rs];
} 
ll query(ll nw,ll l,ll r,ll x,ll y){
	if(x<=l&&y>=r){
		return t[nw];
	}
	if(tg[nw]){
		tg[ls]=tg[rs]=1;
		t[ls]=mid-l+1;
		t[rs]=r-mid;
	}
	ll ans=0;
	if(x<=mid)	ans+=query(ls,l,mid,x,y);
	if(y>mid)	ans+=query(rs,mid+1,r,x,y);
	return ans;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld %lld",&l[i],&r[i]);
	}
	ll p1=1;
	for(int i=2;i<=n;i++){
		p1=p1*2%mod;
	}
	p[1]=p[2]=p1;
	for(int i=3;i<=n;i++){
		p[i]=p[i-1]*qpow(2,mod-2)%mod*3%mod;//这个**赛时用了逆元。。
	}
	for(int i=n;i>=1;i--){
		ans=(ans+((r[i]-l[i]+1)-query(1,0,3e5,l[i],r[i]))*p[i]%mod)%mod;//注意这里要从0开始。
		update(1,0,3e5,l[i],r[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：LinkWish (赞：3)

看题解区的大佬们好多都用了线段树维护矩阵qwq，但是我太菜了不会，所以提供一种纯线段树区间修改（不需要查询）的方法。

我们使用一颗线段树来维护当前所有经过运算后的线段，那么设当前待运算线段为 $[l,r]$，那么我们有三种运算：

### 与运算

两条线段的与就是他们重叠的那一部分，也就是说，在值域中，除了 $[l,r]$ 区间内的所有值都应该清零，因为他们没有重叠部分。

### 异或运算

两条线段的异或就是他们不重叠的那一部分，也就是说，我们应该将 $[l,r]$ 中所有值都清零，以为它们有重叠部分。

之所以把与运算和异或运算放到一起说，是因为我们发现，与运算的结果与异或运算的结果加起来等于或运算的结果。因为两个运算是互补的，所以说我们实际上只用进行一次或运算，然后乘二即可。

### 或运算

两条线段的或就是两条线段一共覆盖的地方，只要一个地方被覆盖了至少一次，那么这个地方就在这两条线段的或中。

那么如何维护这个操作呢？

首先，我们知道，在经历 $i(i>1)$ 次操作后已经形成了 $3^{i-2}$ 条线段，也就是说，我们要给所有的线段都或上 $[l,r]$，体现在具体操作中就是将 $[l,r]$ 区间赋值为 $3^{i-2}$，因为它被所有线段都算了一次。

### code

```cpp
//Linkwish's code
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
typedef const int ci;
typedef long long ll;
typedef pair<int,int> pii;
const int iinf=0x7ffffff;
const ll linf=4e18;
using namespace std;
namespace _Fast_IO{
	char ch;
	int _stack[55],_top,_sign,_strlen;
	inline int read_str(char *_s,const int _index){
		ch=getchar();
		while((ch<'a'||ch>'z')&&(ch<'0'||ch>'9')&&(ch<'A'||ch>'Z'))ch=getchar();
		for(_strlen=_index;(ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')||(ch>='A'&&ch<='Z');ch=getchar(),_strlen++)_s[_strlen]=ch;
		return _strlen-1;
	}
	inline int get_01(char *_s,const int _index){
		ch=getchar();
		while(ch!='0'&&ch!='1')ch=getchar();
		for(_strlen=_index;ch=='0'||ch=='1';ch=getchar(),_strlen++)_s[_strlen]=ch;
		return _strlen-1;
	}
	inline int get_01(int *_s,const int _index){
		ch=getchar();
		while(ch!='0'&&ch!='1')ch=getchar();
		for(_strlen=_index;ch=='0'||ch=='1';ch=getchar(),_strlen++)_s[_strlen]=ch^48;
		return _strlen-1;
	}
	template<typename _T>inline void read(_T &x){
		ch=getchar(),_sign=1;
		for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')_sign=-1;
		for(x=0;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
		x*=_sign;
	}
	template<typename _T>inline void write(_T x){
		_sign=_top=0;
		if(x<0)_sign=1,x=-x;
		if(!x)_stack[++_top]=0;
		while(x){
			_stack[++_top]=x%10;
			x/=10;
		}
		if(_sign)putchar('-');
		while(_top)putchar(_stack[_top--]+48);
	}
	template<typename _T>inline void writeln(_T x){
		write(x);
		puts("");
	}
	template<typename _T>inline void writesp(_T x){
		write(x);
		putchar(' ');
	}
}
using namespace _Fast_IO;
namespace Mod_Int{
	int mod=998244353;
	struct modint{
		int val;
		inline int qpow(int x,int y){
			int res=1;
			while(y){
				if(y&1)res=x*res%mod;
				x=x*x%mod;
				y>>=1;
			}
			return res;
		}
		int get_mod(long long x){return (x%mod+mod)%mod;}		
		bool operator ! (){return !val;}
		modint operator + (const int b){return {get_mod(1ll*val+1ll*b)};}
		modint operator - (const int b){return {get_mod(1ll*val-1ll*b)};}
		modint operator * (const int b){return {get_mod(1ll*val*b)};}
		modint operator / (const int b){return {get_mod(val*qpow(b,mod-2))};}
		modint operator + (const modint b){return {get_mod(1ll*val+1ll*b.val)};}
		modint operator - (const modint b){return {get_mod(1ll*val-1ll*b.val)};}
		modint operator * (const modint b){return {get_mod(1ll*val*b.val)};}
		modint operator / (const modint b){return {get_mod(val*qpow(b.val,mod-2))};}
		void operator += (const int b){val=get_mod(1ll*val+1ll*b);}
		void operator -= (const int b){val=get_mod(1ll*val-1ll*b);}
		void operator *= (const int b){val=get_mod(1ll*val*b);}
		void operator /= (const int b){val=get_mod(val*qpow(b,mod-2));}
		void operator += (const modint b){val=get_mod(1ll*val+1ll*b.val);}
		void operator -= (const modint b){val=get_mod(1ll*val-1ll*b.val);}
		void operator *= (const modint b){val=get_mod(1ll*val*b.val);}
		void operator /= (const modint b){val=get_mod(val*qpow(b.val,mod-2));}
	};
}
using namespace Mod_Int;
const int N=5000005,MX=300001;
modint sum[N],mul[N],tag[N];
modint pw[N];
int n;
inline int ls(int x){return x<<1;}
inline int rs(int x){return x<<1|1;}
inline void push_up(int x){sum[x]=sum[ls(x)]+sum[rs(x)];}
inline void push_down(int x,int l,int r){
	if(mul[x].val==1&&!tag[x])return ;
	int lc=ls(x),rc=rs(x),mid=(l+r)>>1;
	if(tag[x].val){
		tag[lc]=tag[rc]=tag[x];
		mul[lc]=mul[rc]={1};
		sum[lc]=tag[x]*(mid-l+1);
		sum[rc]=tag[x]*(r-mid);
		tag[x]={0};
	}
	if(mul[x].val!=1){
		sum[lc]=sum[lc]*mul[x];
		sum[rc]=sum[rc]*mul[x];
		mul[lc]=mul[lc]*mul[x];
		mul[rc]=mul[rc]*mul[x];
		mul[x]={1};
	}
}
void build(int x,int l,int r){
	mul[x]={1};
	if(l==r)return ;
	int mid=(l+r)>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
}
void change(int x,int l,int r,int L,int R,modint val){
	if(l>=L&&r<=R){
		sum[x]=val*(r-l+1);
		tag[x]=val,mul[x]={1};
		return ;
	}
	push_down(x,l,r);
	int mid=(l+r)>>1;
	if(L<=mid)change(ls(x),l,mid,L,R,val);
	if(R>mid)change(rs(x),mid+1,r,L,R,val);
	push_up(x);
}
signed main(){
	read(n);
	pw[0]={1};
	for(int i=1;i<=MX;i++)pw[i]=pw[i-1]*3;
	int l,r;
	read(l),read(r);
	l++,r++;
	change(1,1,MX,l,r,{1});
	for(int i=2;i<=n;i++){
		read(l),read(r);
		l++,r++;
		change(1,1,MX,l,r,pw[i-2]);
		mul[1]=mul[1]*2,sum[1]=sum[1]*2;
	}
	cout<<sum[1].val;
	return 0;
}
```


---

## 作者：ningago (赞：1)

等一波洛谷爬CF

显然的是每一位只和自己那一位有关：（样例2）

![](https://cdn.luogu.com.cn/upload/image_hosting/wbrdvxgg.png)

因为答案求的是集合大小，所以珂以将答案分解为：$\sum_{i=0}^{300000} \text{第i位被填充的方案数}$

于是我们挖出每一位来DP：

记 $dp_{i,0/1}$ 表示考虑到第 $i$ 个区间，不被填充/被填充 的方案数。

初始状态 $dp_{1,0/1} = 0/1$，取决于被不被第一个区间包含。

转移如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/fmfv2ix1.png)

（等号左边表示 $dp_{i,0/1}$，中间表示这个点被不被区间 $l_i,r_i$ 覆盖，右边红色表示 $dp_{i-1,0/1}$）

综上，在这个点被覆盖的情况下，转移为：

$$dp_{i,0}=dp_{i-1,0}+dp_{i-1,1}$$

$$dp_{i,1}=2\times dp_{i-1,0}+2\times dp_{i-1,1}$$

![](https://cdn.luogu.com.cn/upload/image_hosting/dyqdi8d9.png)

综上，在这个点没被覆盖的情况下，转移为：

$$dp_{i,0}=3\times dp_{i-1,0}+ dp_{i-1,1}$$

$$dp_{i,1}=2\times dp_{i-1,1}$$

然而这样的时间复杂度显然是 $O(3\times 10^5 \times n)$ 的。

然后我们考虑有哪些区间的状态的重复的。

观察样例，如果称这个点的状态（称之为 $a_{i,j}$）与上一个点（对应 $a_{i,j-1}$）的状态不同，就称之为 _珂爱点_，容易发现，影响 dp 状态的只有这些点：

![](https://cdn.luogu.com.cn/upload/image_hosting/for1fdqp.png)

因为 _珂爱点_ 个数不超过 $O(n)$ ，于是做法非常显然了，把 $dp_{i,0/1}$ 设置成二元矩阵：

$$dp_i=\begin{bmatrix}dp_{i,0}&dp_{i,1}\end{bmatrix}$$

更新一下我们的转移：

初始状态：

$$dp_1=\begin{bmatrix}\text{是不是不被区间1覆盖}&\text{是不是被区间1覆盖}\end{bmatrix}$$

如果被 $i$ 区间覆盖，转移为：

$$dp_i=dp_{i-1}\times \begin{bmatrix}1&2\\1&2\end{bmatrix}$$

如果未被 $i$ 区间覆盖，转移为：

$$dp_i=dp_{i-1}\times \begin{bmatrix}3&0\\1&2\end{bmatrix}$$

于是我们现在需要干的就是：

- 区间矩阵乘
- 单点修改（_珂爱点_）

显然的，扔进线段树上即可。

```cpp
#include <cstdio>
#include <cstring>
#include <vector>

#define mod 998244353
#define int long long

#define N 300010
int n;

struct matrix
{
	int x,y;
	int a[3][3];
	void make_unit()
	{
		for(int i = 0;i < x;i++)
			for(int j = 0;j < y;j++)
				a[i][j] = (i == j);
	}
	inline int* operator [](const int &x)
	{
		return a[x];
	}
	inline void out()
	{
		for(int i = 0;i < x;i++)
		{
			for(int j = 0;j < y;j++)
				printf("%lld ",a[i][j]);
			putchar('\n');
		}
	}
};

inline matrix mul(matrix p,matrix q)
{
	matrix res;
	res.x = p.x;
	res.y = q.y;
	for(int i = 0;i < res.x;i++)
		for(int j = 0;j < res.y;j++)
			res.a[i][j] = 0;
	for(int i = 0;i < p.x;i++)
	{
		for(int j = 0;j < q.x;j++)
		{
			for(int k = 0;k < q.y;k++)
			{
				res.a[i][j] = (res.a[i][j] + p.a[i][k] * q.a[k][j] % mod) % mod;
			}
		}
	}
	return res;
}

struct Tree
{
	int l,r;
	matrix sum;
}tr[N << 2];

#define lson k << 1
#define rson k << 1 | 1
int a[N];

matrix get_mat(bool v)
{
	matrix res;
	res.x = 2,res.y = 2;
	if(v == 0)
	{
		res[0][0] = 3;
		res[0][1] = 0;
		res[1][0] = 1;
		res[1][1] = 2;
	}
	else
	{
		res[0][0] = 1;
		res[0][1] = 2;
		res[1][0] = 1;
		res[1][1] = 2;
	}
	return res;
}

void build(int k,int l,int r)
{
	tr[k].l = l,tr[k].r = r;
	tr[k].sum.x = 2;
	tr[k].sum.y = 2;
	if(l == r)
	{
		tr[k].sum = get_mat(a[l]);
		return;
	}
	int mid = l + r >> 1;
	build(lson,l,mid);
	build(rson,mid + 1,r);
	tr[k].sum = mul(tr[lson].sum,tr[rson].sum);
}

void change(int k,int q,bool z)
{
	int l = tr[k].l,r = tr[k].r;
	if(l == r)
	{
		tr[k].sum = get_mat(z);
		return;
	}
	int mid = l + r >> 1;
	if(q <= mid)
		change(lson,q,z);
	else
		change(rson,q,z);
	tr[k].sum = mul(tr[lson].sum,tr[rson].sum);	
}
std::vector <int> l[N];
std::vector <int> r[N];

int ans;
int mx;

signed main()
{
	scanf("%lld",&n);
	for(int i = 1,x,y;i <= n;i++)
	{
		scanf("%lld%lld",&x,&y);
		if(x > mx)
			mx = x;
		if(y > mx)
			mx = y;
		l[x].push_back(i);
		r[y].push_back(i);
	}
	build(1,2,n);
	for(int i = 0;i <= mx;i++)
	{
		int sz = l[i].size();	
		for(int j = 0;j < sz;j++)
		{
			a[l[i][j]] = 1;
			change(1,l[i][j],1);
		}
		matrix base;
		base.x = 1;
		base.y = 2;
		base[0][0] = (a[1] == 0);
		base[0][1] = (a[1] == 1);
		ans += mul(base,tr[1].sum).a[0][1];
		ans %= mod;
		sz = r[i].size();	
		for(int j = 0;j < sz;j++)
		{
			a[r[i][j]] = 0;
			change(1,r[i][j],0);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：蒟蒻丁 (赞：1)

[更好体验](https://www.cnblogs.com/caijiLYC/p/16890460.html)  
线段的贡献不好统计，考虑统计每一个点在不同情况中的被覆盖次数，那么每个点的被覆盖次数总和即为答案。  
设 $f_{i,j,0/1}$ 表示 $i$ 点在扫描到线段 $j$ 时是否被覆盖的情况数量，朴素的转移是暴力枚举每一条线段，方程如下。

当线段 $j$ 可覆盖点 $i$ 时
$$f_{i,j,0}=f_{i,j-1,0}+f_{i,j-1,1}$$
$$f_{i,j,1}=2\times f_{i,j-1,0}+2\times f_{i,j-1,1}$$  
第一条柿子中，如果 $i$ 尚未被覆盖，那么必须使用且运算，如果已被覆盖，那么就必须用取反。第二条柿子同理，当 $i$ 尚未被覆盖，那么可以用或和取反，如果被覆盖，则可以用且和或。

当线段不覆盖 $i$ 时
$$f_{i,j,0}=3\times f_{i,j-1,0}+f_{i,j-1,1}$$
$$f_{i,j,1}=2\times f_{i,j-1,1}$$  
在第一个柿子中，如果 $i$ 尚未覆盖，三种运算都合法，如果被覆盖就必须且运算。在第二个柿子中只能从已覆盖中转移而来，此时可以用或和取反。

---
此时留意到这个柿子转移方式一定，符合动态 dp 的形式，考虑用动态 dp 维护。去掉第二维，可将 dp 方程改写为矩阵形式。

 $$\begin{bmatrix} f_{i,0}&f_{i,1}\end{bmatrix} =\begin{bmatrix} f_{i-1,0}&f_{i-1,1}\end{bmatrix} \times  \begin{bmatrix}1&2\\1&2\\\end{bmatrix} $$
 $$\begin{bmatrix} f_{i,0}&f_{i,1}\end{bmatrix} =\begin{bmatrix} f_{i-1,0}&f_{i-1,1}\end{bmatrix} \times  \begin{bmatrix}3&0\\1&2\\\end{bmatrix} $$
 其中第一个是点被覆盖，第二个是点不被覆盖，
用一个类似差分的方式记录线段的覆盖情况，在端点处修改对应线段的矩阵即可，具体可看代码。
```c++11
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
typedef long long ll;
using namespace std;
const ll mod=998244353,N=3e5+100;
vector<ll>inc[N],decd[N];
ll n,m,nn,ans,t1,t2;

struct matrix{
	ll a[3][3];
	void clear(){memset(a,0,sizeof(a));}
	void one(){
		for(ll i=1;i<=2;i++){
			for(ll j=1;j<=2;j++){
				if(i==j)a[i][j]=1;
				else a[i][j]=0;
			}
		}
	}
	
	matrix operator *(const matrix&tmp )const{
		matrix c;
		c.clear();
		for(ll i=1;i<=2;i++)
			for(ll j=1;j<=2;j++)
				for(ll k=1;k<=2;k++)
					(c.a[i][j]+=a[i][k]*tmp.a[k][j]%mod)%=mod;
		return c;
	}
}D,ini;

struct EX_segment_tree{
	matrix f[N<<2];
	
	void modify(ll l,ll r,ll o,const ll &x,const matrix &d){
		if(l==r)f[o]=d;
		else {
			ll mid=(l+r)>>1;
			if(mid>=x)modify(l,mid,o<<1,x,d);
			else modify(mid+1,r,o<<1|1,x,d);
			f[o]=f[o<<1]*f[o<<1|1];
		}
	}
}T;

void non(){
	D.a[1][1]=3,D.a[1][2]=0;
	D.a[2][1]=1,D.a[2][2]=2;
}

void yeh(){
	D.a[1][1]=1,D.a[1][2]=2;
	D.a[2][1]=1,D.a[2][2]=2;
}

int main(){
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll a1,a2;
		scanf("%lld%lld",&a1,&a2);
		if(i==1)t1=a1,t2=a2;
		else {
			inc[a1].push_back(i-1);
			decd[a2+1].push_back(i-1);
		}
		nn=max(nn,a2);
	}
	non();
	for(ll i=1;i<n;i++)T.modify(1,n-1,1,i,D);
	for(ll i=0;i<=nn;i++){
		ini.clear();
		if(i>=t1&&i<=t2)ini.a[1][2]=1;
		else ini.a[1][1]=1;
		yeh();
		for(ll j=0;j<inc[i].size();j++){
			ll x=inc[i][j];
			T.modify(1,n-1,1,x,D);
		}
		non();
		for(ll j=0;j<decd[i].size();j++){
			ll x=decd[i][j];
			T.modify(1,n-1,1,x,D);
		}
		ini=ini*T.f[1];
		(ans+=ini.a[1][2])%=mod;
	}
	cout<<ans;
}
```

---

## 作者：NXYorz (赞：1)

[题目链接](https://codeforces.com/contest/1743/problem/F)

----
### 写在前面

高中时便听说过动态dp，NOIP 2018 d2t3 也考过一次，但是由于那道题是在树上，需要用树剖来处理，于是当时跑去学了树剖，但是却把动态 dp 遗忘到脑后，这次又遇到了，特地来写一篇博客记录一下，算是填补一下高中时没学的遗憾,~~非常感谢wygg一步一步的引导~~

**该篇博客适合没有接触过动态dp的初学者，因此前面的简单dp将不会详细给出推导过程**


-----
### 题目大意
有 $n$ 个线段，线段 $i$ 所覆盖的点组成集合$S_i$，定义 $op_i$ 为 $∪$，$∩$，$⊕$的其中一种，(其中 $⊕$ 为对称差，即一个包含 $A$ 的所有元素和 $B$ 的所有元素的集合，但不包括同时属于这两个集合的元素)

对于所有可能的 $3^{n-1}$ 种情况，对以下式子求和: 
$$|(((S_1\ op_1\ S_2)\ op_2\ S_3)\ op_3\ S_4)...\ op_{n-1}\ S_n|$$


其中 $|S|$ 为集合 $S$ 的大小

--------
### 分析

首先考虑 $n$ 个线段对一个单独的点的贡献，假设该点的坐标为 $x$，容易想到有两种情况：

- 点在线段内
- 点在线段外

对于上述每种情况，又可以分成三种小情况：

- 这次运算符为 $∪$
- 这次运算符为 $∩$
- 这次运算符为 $⊕$

根据上述情况，令 $f(i,1)$ 表示经过运算 $(S_1\ op_1\  S_2)...op_{i-1}\ S_i$ 之后，点 $x$ 可以做出贡献的方案数。类似地， $f(i,0)$ 表示不能做出贡献的方案数。

因此可以得到状态转移方程：

- 点 $x$ 在线段 $i$ 内时
$$f(i,0) = f(i-1,0)+f(i-1,1)$$
$$f(i,1) = 2\times f(i-1,0)+2\times f(i-1,1)$$

- 点 $x$ 在线段 $i$ 外时
$$f(i,0) = 3\times f(i-1,0)+f(i-1,1)$$
$$f(i,1) = 2\times f(i-1,1)$$

这样一来，对于每一个点我们就可以通过 $O(n)$ 来求出，但是复杂度不能接受，下面考虑优化。

-------

发现对于 $f(i)$ 来说，他的状态只和 $f(i-1)$有关

考虑矩阵：
$
\left[
\begin{matrix}
f(i,0) & f(i,1)
\end{matrix}
\right]
$ ，关于它怎么由上个状态得到，还是要分类讨论：

- 点 $x$ 在线段 $i$ 内时 ：
$
\left[
\begin{matrix}
f(i,0) & f(i,1)
\end{matrix}
\right]
 = 
\left[
\begin{matrix}
f(i - 1,0) & f(i - 1,1)
\end{matrix}
\right]
\times \left[
\begin{matrix}
1 & 2\\
1 & 2
\end{matrix}
\right]
$ 
- 点 $x$ 在线段 $i$ 外时 ：
$
\left[
\begin{matrix}
f(i,0) & f(i,1)
\end{matrix}
\right]
 = 
\left[
\begin{matrix}
f(i - 1,0) & f(i - 1,1)
\end{matrix}
\right]
\times \left[
\begin{matrix}
3 & 0\\
1 & 2
\end{matrix}
\right]
$ 

然后我们考虑，对于每个点，可以根据他的所在位置，每个 $op_i$ 可以得到一个唯一的矩阵，因此我们可以在得到 $n - 1$ 个矩阵之后，$
\left[
\begin{matrix}
f(1,0) & f(1,1)
\end{matrix}
\right]
\times $ 他们的乘积就是我们所要的答案，但是这样复杂度仍然是 $O(n)$ 的，甚至常数还增大了。

但是通过观察可以发现，如果我们知道了点 $x$ 的答案之后，那么对于点 $x + 1$，如果他们同时在某线段内，或者同时不在某线段内，那么该线段对他们的影响是相同的，换句话说，也就是该线段前面对应的符号所对应的矩阵是不变的，再次观察可以发现，只有左端点在 $x + 1$ 处的线段和右端点在 $x$ 处的线段所对应的符号对应的矩阵才会改变，因此对于每次 $x$ 的改变，我们只需要改变这两个位置的若干个矩阵然后用线段树维护乘积即可。

显然，由于每个线段只有两个端点，所以每个线段所在位置矩阵最多改变 2 次，复杂度是 $O(n\log n)$

可以发现 动态dp 是在 普通dp 的基础上增加了修改操作，这种情况我们可以把状态转移方程写成矩阵的形式，对于每次修改我们只修改矩阵，然后对于矩阵用数据结构维护我们所要的信息即可。

### $\texttt{Code}$
```cpp
#include<bits/stdc++.h>

typedef long long ll;

template<class T>
char prt(T x) {
	if(!x) return '\n';
	if(x < 0) printf("-") , x = -x;
	prt(x / 10); printf("%d",x % 10);
	return '\n';
}

template<class T>
void pr(T x) {
	printf("%c",prt(x));
}

void debug() {

}

const int p = 998244353;
const int N = 3e5 + 10;
int n; 
struct JZ {
    int a[3][3];

    JZ operator * (JZ B) {
        JZ ans;
        for(int i = 1; i <= 2; i++)
            for(int j = 1; j <= 2; j++)
                ans.a[i][j] = 0;
        
        for(int k = 1; k <= 2; k++)
            for(int i = 1; i <= 2; i++)
                for(int j = 1; j <= 2; j++)
                    ans.a[i][j] = (ans.a[i][j] + (1ll * a[i][k] * B.a[k][j]) % p) % p;
        return ans;
    }
}A,C;

std::vector<JZ> b(N);

struct NO {
    int l;
    int r;
    JZ w;
};

struct SigmentT {
    NO t[N * 4];

    void Pushup(int p) {
        t[p].w = t[p << 1].w * t[p << 1 | 1].w;
    }

    void Build(int p , int l , int r) {
        t[p].l = l; t[p].r = r;
        if(l == r) {
            t[p].w = b[l];
            return;
        }
        int mid = (l + r) >> 1;
        Build(p << 1 , l , mid); Build(p << 1 | 1 , mid + 1 , r);
        Pushup(p);
    }

    void Updata(int p , int l , int r , JZ w) {
        if(l <= t[p].l && r >= t[p].r) {
            t[p].w = w;
            return;
        }
        int mid = (t[p].l + t[p].r) >> 1;
        if(l <= mid) Updata(p << 1 , l , r , w);
        if(r > mid) Updata(p << 1 | 1 , l , r , w);
        Pushup(p);
    }

}tr;

std::vector<int> L[N],R[N];
int main() {
#ifdef LOCAL
    freopen("aa.in","r",stdin);
    freopen("aa.out","w",stdout);
#endif
    scanf("%d",&n);
    struct El {
        int l;
        int r;
        bool operator < (const El &B) const {
            if(l != B.l) return l < B.l;
            return r < B.r;
        }
    }a[n + 1];
    
    for(int i = 1; i <= n; i++)
        scanf("%d%d",&a[i].l,&a[i].r) , L[a[i].l].push_back(i) , R[a[i].r].push_back(i);
    //std::sort(a + 2 , a + 1 + n);

    A.a[1][1] = 1 , A.a[1][2] = 2;
    A.a[2][1] = 1 , A.a[2][2] = 2;
    C.a[1][1] = 3 , C.a[1][2] = 0;
    C.a[2][1] = 1 , C.a[2][2] = 2;


    int ans = 0;
    for(int j = 2; j <= n; j++) 
        if(0 <= a[j].r && 0 >= a[j].l)  b[j - 1] = A;
        else  b[j - 1] = C;
    tr.Build(1 , 1 , n - 1);
    for(int i = 0; i <= N - 10; i++) {
        JZ f; memset(f.a , 0 , sizeof(f.a));    
        if(i <= a[1].r && i >= a[1].l) f.a[1][2]++;
        else f.a[1][1]++;

        // if(i)
        // for(int j = 2; j <= n; j++) {
        //     int l = a[j].l , r = a[j].r;
        //     std::function<bool(int)> check = [l , r](int x) {
        //         if(x <= r && x >= l) return true;
        //         return false;
        //     };
        //     if(!((check(i) && check(i - 1)) || ((!check(i)) && (!check(i - 1))))) 
        //         if(check(i)) tr.Updata(1 , j - 1 , j - 1 , A);
        //         else tr.Updata(1 , j - 1 , j - 1 , C);
                
        // }
        if(i) {
            for(auto x:L[i]) {
                if(x == 1) continue;
                tr.Updata(1 , x - 1 , x - 1 , A);
            }
            for(auto x:R[i - 1]) {
                if(x == 1) continue;
                tr.Updata(1 , x - 1 , x - 1 , C);
            }
        }


        f = f * tr.t[1].w;
        ans = (ans + f.a[1][2]) % p;
        //printf("%d\n",f.a[1][2]);
    }
    printf("%lld",ans);
}


```

---

## 作者：_zdc_ (赞：1)

第一次独立做出 div2D+ 的题，但是没在 VP 时写完。

题目条件 $0\le l\le r\le 3\times 10^5$，提示我们对于每个数 $x$ 算贡献，即 $x$ 在最后的集合中的方案数。

令 $S_{pos}$ 为 $x$ 最后出现的集合，则 $op_{\max\{1,pos-1\}}$ 是有关这个集合的运算符。设 $p=\max\{1,pos-1\}$。

假设这次操作后 $x$ 还在集合中。考虑这个运算符后的操作，因为 $x$ 不会再出现，所以后面的运算只能是并或者对称差，这里有 $2^{(n-1)-p+1}=2^{n-p}$ 种方案。

再来看 $op_p$ 这个运算符，讨论与 $S_{pos}$ 运算的集合是否存在 $x$。

如果存在，这个运算符就是并或交；否则是并或对称差。因此 $op_p$ 无论之前的值是多少，都有两种选择使 $x$ 对答案有贡献。也可以发现前 $p-1$ 个运算怎么选都合法。方案数 $2\times 3^{p-1}$。

于是只要求出 $pos$，用线段树维护区间覆盖即可，复杂度 $O(n\log V)$，$V$ 为值域。

```cpp
#include<bits/stdc++.h>
#define ls (cur<<1)
#define rs (cur<<1|1)
#define fir first
#define sec second
#define pii pair<int,int>
#define Mp make_pair
using namespace std;
typedef long long ll;
const int N=3e5+5,K=1.3e6+5,mod=998244353;
int n,pos[N],ans;
pii op[N];
struct SegmentTree{//线段树维护区间覆盖，单点查询
    int tag[K];
    SegmentTree(){
        memset(tag,0,sizeof(tag));
    }
    void addtg(int cur,int val){
        if(!tag[cur]) tag[cur]=val;
    }
    void pd(int cur){
        if(!tag[cur]) return;
        int t=tag[cur];
        addtg(ls,t);
        addtg(rs,t);
        return;
    }
    void upd(int cur,int l,int r,int qx,int qy,int val){
        if(l>qy || r<qx || tag[cur]) return;
        if(l>=qx && r<=qy){
            addtg(cur,val);
            return;
        }
        pd(cur);
        int mid=l+r>>1;
        upd(ls,l,mid,qx,qy,val);
        upd(rs,mid+1,r,qx,qy,val);
        return;
    }
    int qry(int cur,int l,int r,int qx){
        if(l==r) return tag[cur];
        pd(cur);
        int mid=l+r>>1;
        if(qx<=mid) return qry(ls,l,mid,qx);
        return qry(rs,mid+1,r,qx);
    }
}T;
int qp(int x,int y){
    if(!y) return 1;
    int tm=qp(x,y>>1);
    if(y&1) return 1ll*tm*tm%mod*x%mod;
    return 1ll*tm*tm%mod;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        op[i]=Mp(l,r);
    }
    for(int i=n;i;i--)
        T.upd(1,0,N-5,op[i].fir,op[i].sec,i);
    for(int i=0;i<=N-5;i++)//求出 pos
        pos[i]=T.qry(1,0,N-5,i);
    for(int i=0;i<=N-5;i++){
        int x=pos[i];
        if(!x) continue;
        if(x==1){
            ans=(ans+qp(2,n-1)%mod)%mod;continue;
        }
        ans=(ans+1ll*qp(2,n-x+1)*qp(3,x-2)%mod)%mod;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Y2y7m (赞：0)

发现 $0\leq l_i,r_i\leq3\times10^5$，十分的有趣。

整体计算有一点恶心，所以把每一个单独拆出来算贡献。

现在假设数 $x$ 最后一次出现在集合 $s_i$ 中，看看有多少种情况他是会有贡献的。

假设我们进行操作进行到第 $i-1$ 的集合时，他不含有 $x$ 这个元素，则可以通过并或者对称差使进行完第 $i-1$ 次操作后存在 $x$；同理，当进行到第 $i-1$ 个集合时含有 $x$ 这个元素，第 $i-1$ 次操作为交或并都可以。

由于 $s_i$ 集合是最后一个含有该元素的集合，所以后面就都没有了，所以只能选择并或者对称差，因此有贡献情况为 $3^{i-2}\times 2\times 2^{n-i}$ 种。

我们可以使用线段树来维护每种元素的最后一次出现的集合的位置，只需要区间覆盖和单点查询即可，时间复杂度 $O(\max{r_i}\times \log{\max{r_i}})$。

---

## 作者：Leasier (赞：0)

考虑每个位置 $i$ 的贡献。

注意到对于每次操作 $[l_j, r_j]$，我们根据 $i$ 的位置及之前的值 $v = 0/1$ 可以分为以下两种情况。

1. $i \in [0, l_j) \cup (r_j, N]$

- 求并：$v = 0 \to v = 0$，$v = 1 \to v = 1$。
- 求交：$v = 0 \to v = 0$，$v = 1 \to v = 0$。
- 求异或（也就是 symmetric difference 在一个位置的表现）：$v = 0 \to v = 0$，$v = 1 \to v = 1$。

2. $i \in [l_j, r_j]$

- 求并：$v = 0 \to v = 1$，$v = 1 \to v = 1$。
- 求交：$v = 0 \to v = 0$，$v = 1 \to v = 1$。
- 求异或（也就是 symmetric difference 在一个位置的表现）：$v = 0 \to v = 1$，$v = 1 \to v = 0$。

这是容易用一个 $2 \times 2$ 的矩阵描述的，于是我们上线段树维护区间乘矩阵即可。时间复杂度为 $O(N + n \log N)$。

代码：
```cpp
#include <stdio.h>
#include <string.h>

typedef struct Matrix_tag {
	int n;
	int m;
	int a[3][3];
	
	Matrix_tag(){}
	
	inline void clear(int n_, int m_){
		n = n_;
		m = m_;
		memset(a, 0, sizeof(a));
	}
	
	Matrix_tag(int n_, int m_){
		clear(n_, m_);
	}
} Matrix;

typedef struct {
	int l;
	int r;
	Matrix tag;
} Node;

const int N = 3e5, M = 1.2e6 + 7, mod = 998244353;
Matrix a(2, 2), b(2, 2), e(2, 2);
bool vis[N + 7];
Node tree[M];

inline void add(int &x, int y){
	if ((x += y) >= mod) x -= mod;
}

Matrix operator *(const Matrix a, const Matrix b){
	Matrix ans(a.n, b.m);
	for (register int i = 1; i <= a.n; i++){
		for (register int j = 1; j <= a.m; j++){
			for (register int k = 1; k <= b.m; k++){
				add(ans.a[i][j], 1ll * a.a[i][k] * b.a[k][j] % mod);
			}
		}
	}
	return ans;
}

Matrix operator *=(Matrix &a, const Matrix b){
	return a = a * b;
}

inline void init(){
	a.a[1][1] = a.a[2][1] = 1;
	a.a[1][2] = a.a[2][2] = 2;
	b.a[1][1] = 3;
	b.a[2][1] = 1;
	b.a[2][2] = 2;
	for (register int i = 1; i <= 2; i++){
		e.a[i][i] = 1;
	}
}

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	tree[x].tag = e;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
}

inline void pushdown(int x){
	tree[x * 2].tag *= tree[x].tag;
	tree[x * 2 + 1].tag *= tree[x].tag;
	tree[x].tag = e;
}

void mul(int x, int l, int r, Matrix &mat){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].tag *= mat;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) mul(x * 2, l, r, mat);
	if (r > mid) mul(x * 2 + 1, l, r, mat);
}

int dfs(int x){
	if (tree[x].l == tree[x].r) return !vis[tree[x].l] ? tree[x].tag.a[1][2] : tree[x].tag.a[2][2];
	pushdown(x);
	return (dfs(x * 2) + dfs(x * 2 + 1)) % mod;
}

int main(){
	int n;
	scanf("%d", &n);
	init();
	build(1, 0, N);
	for (register int i = 1; i <= n; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		if (i == 1){
			for (register int j = l; j <= r; j++){
				vis[j] = true;
			}
		} else {
			mul(1, l, r, a);
			if (l > 0) mul(1, 0, l - 1, b);
			if (r < N) mul(1, r + 1, N, b);
		}
	}
	printf("%d", dfs(1));
	return 0;
}
```

---

