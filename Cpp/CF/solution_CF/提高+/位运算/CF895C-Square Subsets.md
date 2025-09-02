# Square Subsets

## 题目描述

Petya was late for the lesson too. The teacher gave him an additional task. For some array $ a $ Petya should find the number of different ways to select non-empty subset of elements from it in such a way that their product is equal to a square of some integer.

Two ways are considered different if sets of indexes of elements chosen by these ways are different.

Since the answer can be very large, you should find the answer modulo $ 10^{9}+7 $ .

## 说明/提示

In first sample product of elements chosen by any way is $ 1 $ and $ 1=1^{2} $ . So the answer is $ 2^{4}-1=15 $ .

In second sample there are six different ways to choose elements so that their product is $ 4 $ , and only one way so that their product is $ 16 $ . So the answer is $ 6+1=7 $ .

## 样例 #1

### 输入

```
4
1 1 1 1
```

### 输出

```
15
```

## 样例 #2

### 输入

```
4
2 2 2 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
5
1 2 4 5 8
```

### 输出

```
7
```

# 题解

## 作者：pmt2018 (赞：32)

一道状压$dp$好题。

注意到此题$a_i\leq70$，
并且一个数是否为完全平方数只与它的质因子奇偶性有关，~~所以$n\leq10^5$是废话~~，我们只需要用一个桶统计每个数出现的个数就好了。

另外，打表发现$70$以内质数只有$19$个，所以想到状压$dp$。

令$dp_{i,mask}$表示考虑到$1-70$中的第i个数。并且因为一个数是否为完全平方数只与它的质因子奇偶性有关，$mask$表示这$19$个数的奇偶性，若第$j$个质数的因数个数为奇数则mask第j位为1。

考虑$dp$方程的转移。

先从$1-70$枚举$i$，若$cnt_i$(即数$i$在数组中出现次数)不为零，则枚举$mask$

显然，当选奇数个数$i$时，$mask$会发生改变，我们将$i$分解质因数，$mask$变为$mask1$,$dp_{i,mask1}$可以从$dp_{i-1,mask}$转移。

当选偶数个$i$时,$mask$不会改变,$dp_{i,mask}$可以从$dp_{i-1,mask}$转移。

让我们令当前的$cnt_i= k$，选奇数个的情况$C_k^1+C_k^3+C_k^5+\cdot\cdot\cdot=\sum\limits_{i\leq k,i\equiv1(mod2)}^iC_k^i=2^{k-1}$种

选偶数个的情况有$C_k^0+C_k^2+C_k^4+\cdot\cdot\cdot=\sum\limits_{i\leq k,i\equiv0(mod2)}^iC_k^i=2^{k-1}$种

这两个式子可以用二项式定理证明。

所以$dp_{i,mask1}+=dp_{i-1,mask}*2^{k-1}$

$dp_{i,mask}+=dp_{i-1,mask}*2^{k-1}$

如果$cnt_i==0$我们就将$dp_{i-1}$赋值给$dp_{i}$

我们可以看到，任$dp_{i,mask}$只需从$dp_{i-1}$中的数转移，我们可以用滚动数组滚掉一维。

这样我们就做完了。

注意开$long long $

code:
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back

#define y0 pmt
#define y1 pmtpmt
#define x0 pmtQAQ
#define x1 pmtQwQ

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int > vi;
typedef pair<int ,int > pii;
typedef vector<pii> vii;
const int inf=0x3f3f3f3f, maxn=100007, mod=1e9+7;
const ll linf=0x3f3f3f3f3f3f3f3fLL;
const ll P=19260817;
const int p[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};//质数表
int n;
ll dp[2][1<<19];
ll cnt[75];
int I=0;
ll h[maxn];//2^k的表
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int rt;
		scanf("%d",&rt);
		cnt[rt]++;
	}
	h[0]=1;
	dp[0][0]=1; 
	for(int i=1;i<=n;i++)h[i]=(h[i-1]<<1)%mod;
	for(int i=1;i<=70;i++){
		if(cnt[i]==0)continue;
		I^=1;//滚动数组
		memset(dp[I],0,sizeof(dp[I]));//注意初始化
		for(int mask=0 ; mask< (1<<19) ; mask++){
			int mask1=mask;
			int x=i;
			for(int j=0;j<19&&x>=p[j];j++){
				while(x%p[j]==0)x/=p[j],mask1^=(1<<j);
			}
			(dp[I][mask1]+=1LL*dp[I^1][mask]*h[cnt[i]-1]%mod)%=mod;
			(dp[I][mask]+=1LL*dp[I^1][mask]*h[cnt[i]-1]%mod)%=mod;
		}
	}
	printf("%I64d\n",(dp[I][0]-1+mod)%mod);
    return 0;
}

```

---

## 作者：1saunoya (赞：27)

线性基的题…

考虑平方数只和拆解质因子的个数的奇偶性有关系

比如说你 $4$ 和 $16$ 的贡献都是一样的。因为

$4 = 2^2 , 16 = 2^4$

$2$ 和 $4$ 奇偶性相同

然后考虑如何线性基，不难想到，二进制可以表示奇偶性，
所以异或和每一位是0的时候就是一个平方数了。

我们考虑把 线性基的元素设为 $|S|$ 个

那么你手头只剩下 $n-|S|$ 个数字还可以被线性基表示的。

如果可以表示，那么说明了这些 $2^{n-|S|}-1$ 个子集异或和都可以和线性基拼凑成0

所以目标答案就是 $2^{n-|S|}-1$

```cpp

// by Isaunoya
#include <bits/stdc++.h>
using namespace std;

#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)
#define int long long

const int _ = 1 << 21;
struct I {
	char fin[_], *p1 = fin, *p2 = fin;
	inline char gc() {
		return (p1 == p2) && (p2 = (p1 = fin) + fread(fin, 1, _, stdin), p1 == p2) ? EOF : *p1++;
	}
	inline I& operator>>(int& x) {
		bool sign = 1;
		char c = 0;
		while (c < 48) ((c = gc()) == 45) && (sign = 0);
		x = (c & 15);
		while ((c = gc()) > 47) x = (x << 1) + (x << 3) + (c & 15);
		x = sign ? x : -x;
		return *this;
	}
	inline I& operator>>(double& x) {
		bool sign = 1;
		char c = 0;
		while (c < 48) ((c = gc()) == 45) && (sign = 0);
		x = (c - 48);
		while ((c = gc()) > 47) x = x * 10 + (c - 48);
		if (c == '.') {
			double d = 1.0;
			while ((c = gc()) > 47) d = d * 0.1, x = x + (d * (c - 48));
		}
		x = sign ? x : -x;
		return *this;
	}
	inline I& operator>>(char& x) {
		do
			x = gc();
		while (isspace(x));
		return *this;
	}
	inline I& operator>>(string& s) {
		s = "";
		char c = gc();
		while (isspace(c)) c = gc();
		while (!isspace(c) && c != EOF) s += c, c = gc();
		return *this;
	}
} in;
struct O {
	char st[100], fout[_];
	signed stk = 0, top = 0;
	inline void flush() {
		fwrite(fout, 1, top, stdout), fflush(stdout), top = 0;
	}
	inline O& operator<<(int x) {
		if (top > (1 << 20)) flush();
		if (x < 0) fout[top++] = 45, x = -x;
		do
			st[++stk] = x % 10 ^ 48, x /= 10;
		while (x);
		while (stk) fout[top++] = st[stk--];
		return *this;
	}
	inline O& operator<<(char x) {
		fout[top++] = x;
		return *this;
	}
	inline O& operator<<(string s) {
		if (top > (1 << 20)) flush();
		for (char x : s) fout[top++] = x;
		return *this;
	}
} out;
#define pb emplace_back
#define fir first
#define sec second

template < class T > inline void cmax(T & x , const T & y) {
	(x < y) && (x = y) ;
}
template < class T > inline void cmin(T & x , const T & y) {
	(x > y) && (x = y) ;
}

int ans = 0 ;
int p[30] ;
int pri[30] = { 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37 , 41 , 43 , 47 , 53 , 59 , 61 , 67 } ;
void ins(int x) {
	for(int i = 19 ; ~ i ; i --) {
		if(x & (1 << i)) {
			if(! p[i]) {
				p[i] = x ;
			}
			x ^= p[i] ;
		}
	}
}
const int mod = 1e9 + 7 ;
int qpow(int x , int y) {
	int ans = 1 ;
	for( ; y ; y >>= 1 , x = x * x % mod) 
		if(y & 1) ans = ans * x % mod ;
	return ans ;
}
signed main() {
#ifdef _WIN64
	freopen("testdata.in" , "r" , stdin) ;
#endif
	int n ;
	in >> n;
	rep(i , 1 , n) {
		int x ;
		in >> x ;
		int res = 0 ;
		rep(j , 0 , 18) {
			if(x % pri[j] == 0) {
				int now = 0 ; 
				while(x % pri[j] == 0) {
					x /= pri[j] ;
					now ^= 1 ;
				}
				res ^= (now << j) ;
			}
		}
		ins(res) ;
	}
	for(int i = 19 ; ~ i ; i --) if(p[i]) n -- ;
	out << ( qpow(2 , n) - 1 ) % mod << '\n' ;
	return out.flush(), 0;
}

```

---

## 作者：bztMinamoto (赞：10)

更好的阅读体验->[这里](https://www.cnblogs.com/bztMinamoto/p/9715413.html)

楼下的状压其实很麻烦……而且跑得很慢……这里介绍一下线性基的做法……

不知道什么是线性基的可以看看->[这里](https://blog.sengxian.com/algorithms/linear-basis)

完全看不出这玩意儿和线性基有什么关系……我可能太菜了……

首先，一个完全平方数分解质因数之后每个质因子都出现偶数次

又因为小于等于$70$的质数总共18个，可以用18位的二进制表示，0表示偶数次，1表示奇数次

那么两个数相乘就是每一个质因子表示的位的异或

那么就是求有多少种方法相乘得0

首先求出原数组的线性基，设$cnt$表示线性基内数的个数

那么答案就是$2^{n-cnt}-1$

证明：线性基内的数是最小线性无关组

那么除了线性基内的所有数的子集都能被线性基内的数张成（就是表示出来）

那么上面的所有子集和张成相等，两者异或起来为0

所以把线性基内的数除去，剩下的数的所有子集都能与线性基内的数异或成0

那么答案就是真子集个数
```
//minamoto
#include<iostream>
#include<cstdio>
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=1e5+5,M=20,mod=1e9+7;
int p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int b[M],a[N],n,cnt;
inline int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return res;
}
void insert(int x){
	for(int i=18;i>=0;--i){
		if(x>>i&1){
			if(!b[i]){b[i]=x;break;}
			x^=b[i];
		}
	}
}
int main(){
//	freopen("testdata.in","r",stdin);
	n=read();
	for(int i=1;i<=n;++i){
		int x=read();
		for(int j=0;j<=18;++j){
			if(x%p[j]==0){
				int now=0;
				while(x%p[j]==0) x/=p[j],now^=1;
				a[i]|=now<<j;
			}
		}
	}
	for(int i=1;i<=n;++i) insert(a[i]);
	for(int i=0;i<=18;++i)
	if(b[i]) --n;
	printf("%d\n",ksm(2,n)-1);
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：5)

# 线性基板子题
由于$a_i\leq 70$,因此所有的$a_i$一定可以表示为
$a_i=\Pi p_i^{k_i}$的形式，由于70以内的质数有限，只有``` 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37 , 41 , 43 , 47 , 53 , 59 , 61 , 67```,完全可以打表~~写暴力也完全OK~~

把$a_i$进行质因子分解后，我们考虑：
$a_i=\Pi p_i^{k_i}$对答案的贡献与$a_i=\Pi p_i^{k_imod2}$对答案的贡献有神马差别

很明显，一个数如果除以一个平方因子，对答案木有任何影响，因此上面二式是等价的

由于$i$的值很小，我们可以用一个二进制数来表示$a_i$,若$k_imod2=0$,则二进制位下的$i$位就为0,反之为1

考虑相乘的操作，假设有两个二进制数
$$a_{(2)}=a_0a_1...a_{18}$$
$$b_{(2)}=b_0b_1...b_{18}$$
辣么这两数经过某种运算后得到$c$
$$c_{(2)}=c_0c_1...c_{18}$$
经肉眼观察可得$c_i=(a_i+b_i)mod2$,显然$a_i=b_i$时值为0，反之为1

这不就是Xor吗，当值为零是，就一定是平方数

于是我们高兴地掏出了线性基，每次把处理过的$a_i$放进去。然而这怎么得到答案呢

经过观察我们发现，除了线性基里面的值，外面的可以随便取，经过线性基里面的数异或后一定有办法变成0

因此$Ans=2^{n-|S|}-1$
```cpp
#pragma optimize(2)
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
vector<int>p;
void init(int maxn){
	for(int i=2;i<=maxn;i++){
		for(int j=2;j<i;j++)
			if(i%j==0)
				goto loop;
		p.push_back(i);
		loop:;
	}
}
int n,a;
const int maxn_wei=20;
struct node{
	//线性基板子
	int b[maxn_wei];
	void insert(int x){
		for(int i=maxn_wei-1;i>=0;i--){
			if(!(x&(1<<i)))continue;
			if(!b[i]){
				b[i]=x;
				return ;
			}
			x^=b[i];
		}
	}
}Base;
long long qpow(int x){
	int ret=1,mod=1e9+7,a=2;
	while(x){
		if(x&1)ret=ret*a%mod;
		a=a*a%mod,x>>=1;
	}
	return ret;
}
signed main(){
	read(n);init(70);
	for(int i=1;i<=n;i++){
		read(a);int now=0;
		for(int j=0;j<p.size();j++){
			now<<=1;
			while(a%p[j]==0)
				a/=p[j],now^=1;
		}
		Base.insert(now);
	}
	for(int i=maxn_wei-1;i>=0;i--)
		n-=Base.b[i]!=0;
	cout<<qpow(n)-1; 
}
```

---

## 作者：splendore (赞：4)

### 题意
在一个数组 $a$ 中取一个非空子集，使它的乘积等于一个平方数的取法的数量。

### 思路
一个数是否是平方数，只和其质因子的指数的奇偶性有关，所以题目可以转换为：原序列有多少个非空子集的乘积的质因子均为偶数。

又因为奇偶性有异或性质，那么我们就可以用线性基维护这个问题了。

若线性基内有 $cnt$ 个元素，则原序列只有 $n-cnt$ 个数可选，题目问的是取法的数量，所以要排除全不取的情况，答案为  $2^{n-cnt}-1$。

代码如下:

```
#include<cstdio>
using namespace std;
typedef long long LL;
const int N=100005,mod=1000000007;
const int p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int a[32];
bool zero;
int getpow(int a,int b){
	int s=1;a%=mod;
	while(b){
		if(b&1)s=(LL)s*a%mod;
		a=(LL)a*a%mod;b>>=1;
	}
	return s;
}
void ins(int x){
	for(int i=19;~i;--i)
		if(x>>i&1){
			if(!a[i])return a[i]=x,void();
			else x^=a[i];
		}
	zero=1;
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1,x,s;i<=n;++i){
		scanf("%d",&x);s=0;
		for(int j=0;j<=18;++j)
			if(x%p[j]==0){
				bool t=0;
				while(x%p[j]==0)x/=p[j],t=!t;
				if(t)s|=1<<j;
			}
		ins(s);
	}
	for(int i=0;i<=18;++i)if(a[i])--n;
	printf("%d\n",getpow(2,n)-1);
	return 0;
}
```

---

## 作者：rui_er (赞：4)

我们设 $x=\prod p_i^{k_i}$，考虑什么时候 $x$ 是完全平方数。容易发现如果所有 $k_i$ 都是偶数，此时 $\sqrt{x}=\prod p_i^{\frac{k_i}{2}}$ 为整数，即 $x$ 是完全平方数；否则 $x$ 不是完全平方数。

题目转换为原序列 $\{a_i\}$ 有多少个非空子集乘积质因数分解后质数均为偶数。

发现奇偶性是满足异或性质的，奇数对应 $1$，偶数对应 $0$。考虑将原序列的每一个 $a_i$ 进行质因数分解，将分解后每个质因数的指数奇偶性二进制压位成一个整数，存到线性基中。

假设线性基中有 $cnt$ 个元素，那么剩下的 $n-cnt$ 个数可以用线性基的元素异或表示，可以任意取，共有 $2^{n-cnt}$ 种取法，注意减掉全都不取的一种就是答案。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 1e5+5, mod = 1e9+7;
const int pm[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};

int n, a[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
struct LinearBasis {
	int p[19];
	LinearBasis() {memset(p, 0, sizeof(p));}
	~LinearBasis() {}
	void insert(int x) {
		per(i, 18, 0) {
			if(!((x >> i) & 1)) continue;
			if(!p[i]) {p[i] = x; return;}
			x ^= p[i];
		}
	}
	int qmax() {
		int ans = 0; 
		per(i, 18, 0) chkmax(ans, ans^p[i]);
		return ans;
	}
	int cnt() {
		int ans = 0;
		per(i, 18, 0) ans += !!p[i];
		return ans;
	}
}LB;
int qpow(int x, int y) {
	int ans = 1;
	for(;y;y>>=1,x=1LL*x*x%mod) if(y & 1) ans = 1LL * ans * x % mod;
	return ans;
}

int main() {
	scanf("%d", &n);
	rep(i, 1, n) {
		scanf("%d", &a[i]);
		int now = 0;
		per(j, 18, 0) {
			now <<= 1;
			while(!(a[i] % pm[j])) {
				now ^= 1;
				a[i] /= pm[j];
			}
		}
		LB.insert(now);
	}
	printf("%d\n", (qpow(2, n-LB.cnt())+mod-1)%mod);
    return 0;
}
```

---

## 作者：__usingnamespace__ (赞：3)

## 题意
给定长度为n的数组a，求a的子集中乘积为完全平方数的子集个数。两子集不同当且仅当选取的数在数组中位置不同。
答案对1e9+7取模。

$1≤n≤10^5 ;1 ≤ a_i ≤70$


## sol
从$a_i≤70$很容易想到状压$dp$。

判断乘积是否是完全平方可以用质因数指数是否全为偶确定。

70以内只有19个质数，可以状压每个质数的指数的奇偶性。

如果直接第一层暴力枚举$a_i$的话时间复杂度。为$O(n*2^{19})$明显会炸

因为$a_i≤70$，所以可以用桶记录数组中每个数出现的次数。

$dp[i][now]$表示选择i时使状态为now的情况数。

选奇数个i时，$dp[i][now]+=dp[i-1][now1]$；

选偶数个i时，$dp[i][now]+=dp[i-1][now]$

$now1$就是$now$对$i$的质因数分解后的每项取异或。

所以若a中有k个i，那么
$$ dp[i][now]=\sum_{j=1}^k (j\%2=1)C_j^k*dp[i][now1]+\sum_{j=1}^k (j\%2=0)C_j^k*dp[i][now] $$
$$ =2^{k-1}*dp[i][now1]+2^{k-1}*dp[i][now]\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\ $$

那么$ans=dp[70][0]$,即最后一次的质数指数全为偶数的情况数。

由于最终结果多算了一个什么也不取的情况，所以最后要将$ans-1$。

- 由于这个题卡空间，所以要开滚动数组。
- 由于这个题还卡时间，所以要在枚举$i$的时候预处理好$i$的质因数分解异或值，即$now$的状态转移方程。
- 由于还是卡时间，所以$2^k$不能用快速幂而是要打一个幂表。

~~我是不会告诉你这三条卡了我一个小时的。~~
## code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1000000007,N=524287;
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+c-'0',c=getchar();
    return x*f;
}
int dp[2][530000];
int t[80],n;
int pri[30]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int mi[100007];
inline int get(int x,int now)
{
    for(int i=0;i<=18;i++)
    {
        if(x==1)return now;
        while(x%pri[i]==0)
        {
            now^=(1<<i);
            x/=pri[i];
        }
    }
    return now;
}
signed main()
{
//    freopen("sample.in","r",stdin);
    n=read();
    int x;
    mi[0]=1;
    for(int i=1;i<=n;i++)
    {
        x=read();
        t[x]++;
        mi[i]=mi[i-1]*2%mod;
    }
    dp[0][0]=1;
    int ans=0,bol=0;
    for(int i=1;i<=70;i++)
    {
        if(t[i]==0)continue;bol^=1;
        int chan=get(i,0);
        for(int now=0;now<=N;now++)
        {
            int now1=chan^now;
            dp[bol][now]=(dp[bol^1][now]+dp[bol^1][now1])%mod*mi[t[i]-1]%mod;
        }
        ans=dp[bol][0]%mod;
    }
    printf("%lld\n",(ans-1)%mod);
    return 0;
}
```

---

## 作者：漠寒 (赞：1)

## 分析

题意就是对于一个数组，有多少个子集中的各项乘起来为完全平方数，记录个数并取模。

首先观察数据范围，发现数的大小很小，又想到平方数可以进行质因数分解，分解后，每一组相同项的个数都应为偶数。

于是第一步就想到了，因为70内的质数只有19个，于是我们状态压缩，用19位的二进制数，每一位表示对应位置的质数在乘积分解后有偶数个还是奇数个，对于每一个读取的数，计算它的质因数分解，异或转移，这样的复杂度为 $n*2^{19}$。

很明显，这样超时了，我们再次注意，数的大小真的很小，于是我们可以统计1到70数的个数，那对于每一个数如何处理呢？假设某一位数有 $k$ 个，那么从中选择偶数个时，根本不会造成影响，因为每两个乘起来就是一个平方数，这种情况就是直接由上一个同样的状态转移过来即可，而如果奇数个，则是异或状态转移，而由题目中索引不同方案不同，再加入组合数，很容易证得，每一个奇数的组合加起来为 $2^{k-1}$，偶数一样，转移时乘上该数即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
inline int qpow(int ds,int zs){
	int x=1;
	while(zs){
		if(zs&1)x=(x*ds)%mod;
		ds=(ds*ds)%mod;zs>>=1;
	}
	return x;
}
inline void read(int &res){
	res=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
}
int n,a,p,now,d;
int cnt[75],pri[20]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};//质数 
int f[2][(1<<19)+5];
signed main()
{
	read(n);
	f[0][0]=1;
	for(int i=1;i<=n;i++)read(a),cnt[a]++;//计数 
	for(int i=1;i<=70;i++){
		if(!cnt[i])continue;//没有该数，跳过 
		d^=1;//第一维为2，否则炸空间 
		memset(f[d],0,sizeof(f[d]));
		int x=i;
		p=qpow(2,cnt[i]-1);//计算转移乘数 
		now=0;
		for(int j=1;j<=19;j++){
			while((x%pri[j])==0){
				now^=1<<(j-1);//每查到一次，改变一次奇偶性 
				x/=pri[j];
			}
		}
		for(int j=0;j<=(1<<19)-1;j++){
			f[d][j]=p*f[d^1][j]%mod+p*f[d^1][j^now]%mod;
			if(f[d][j]>=mod)f[d][j]-=mod;//小优化 
		}
	}
	if(f[d][0])cout<<f[d][0]-1;//减去一个都不选的情况 
	else cout<<mod-1;
	return 0;
}
```


---

## 作者：eee_hoho (赞：1)

考虑到完全平方数只和质因子次幂的奇偶性相关，那么我们可以把乘积转化为二进制下的异或。

于是题目变成选择若干个数异或起来为$0$的方案数。

那么考虑把所有元素插入到线性基中，于是不在线性基里的元素一定可以被线性基里的元素表示，相异或就可以为$0$。

而在线性基里的元素一定不会其他元素表示，相异或一定不为$0$。

所以方案数就是不在线性基中的元素个数组成的非空子集数：$2^{n-cnt}-1$

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 1e5;
const int P = 1e9 + 7;
using namespace std;
int n,a[N + 5],prime[N + 5],pcnt,vis[N + 5],val[N + 5],p[N + 5],cnt;
int mypow(int a,int x){int s = 1;for (;x;x & 1 ? s = 1ll * s * a % P : 0,a = 1ll * a * a % P,x >>= 1);return s;}
void prework()
{
    for (int i = 2;i <= 70;i++)
    {
        if (!vis[i])
            prime[++pcnt] = i;
        for (int j = 1;prime[j] * i <= 70 && j <= pcnt;j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
void ins(int x)
{
    for (int i = 22;i >= 0;i--)
        if (x >> i & 1)
        {
            if (!p[i])
            {
                p[i] = x;
                cnt++;
                break;
            }
            x ^= p[i];
        }
}
int main()
{
    scanf("%d",&n);
    for (int i = 1;i <= n;i++)
        scanf("%d",&a[i]);
    prework();
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= pcnt;j++)
            while (a[i] % prime[j] == 0)
                val[i] ^= 1 << j - 1,a[i] /= prime[j];
        ins(val[i]);
    }
    int ans = mypow(2,n - cnt) - 1;
    cout<<(ans + P) % P<<endl;
    return 0;
}
```

---

## 作者：SkyRainWind (赞：1)

题解：
状压dp+组合数学

代码中的注释说的很清楚了，但还是要强调几点：

（1）位运算优先级：注意位运算优先级比等于号还小，所以有位运算的表达式为了保险起见，最好都打上括号

（2）爆int，最后的结果$mod\ 1e9+7$，然后状转方程中有类似$dp[i][j]*2^{j}$的操作，会爆int，需要用longlong，注意longlong的转化一定要彻底！坑了我好长时间。。

（3）初始化，$dp[0][0]=1$，表示空集的方案数。

（4）结果，注意到空集其实不符合方案，所以需要在最终的$dp[70][0]$中减掉1（空集的方案数）

（5）别忘了取模

代码：
```
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
typedef long long LL;
const int inf=1<<26;
const LL mod=(LL)1e9+7;

/*
注意到 ai<=70，我们以这个为突破口
打表发现<=70的质数只有19个，以这个作为n的质因子
*/
// 有个0为下标问题
const int prime[20]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int n;
int a[100005];
int s[75];
int cnt[1005];
int dp[75][(1<<19)+5],p2[100005];
// dp[i][S] 表示处理到第 i 个数，质因子情况为S的方案数
/*
S处理：如果第 i 位为1，说明当前结果中有奇数个相同的质因子（这个质因子是prime[i]）
转移：dp[i][j^s[i]]=dp[i][j^s[i]]+power_2[cnt[i]-1]*dp[i-1][j]
      dp[i][j]=dp[i][j]+power_2[cnt[i]-1]*dp[i-1][j]
其中 C(n,0)+C(n,2)+C(n,4)+...=2^(n-1)
     C(n,1)+C(n,2)+C(n,4)+...=2^(n-1)
证明：首先根据二项式定理整除C(n,0)+C(n,1)+...=2^n （网上有）
C(n,0)=A(n,0)/A(0,0)=1 C(n,n)=1 C(n,0)=C(n,n)  C(n,1)=C(n,n-1)....
所以均等于2^(n-1) 
*/

int main(){
	scanf("%d",&n);
	for(int i=1;i<=70;i++){
		int tmp=i;
		for(int j=1;j<=19;j++){
			while(tmp%prime[j]==0){
				s[i]^=(1<<(j-1));
				tmp/=prime[j];
			}
		}
	}
	p2[0]=1;
	for(int i=1;i<=n;i++)p2[i]=(p2[i-1]*2)%mod;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),++cnt[a[i]];
	dp[0][0]=1;	// 初始化：空集 
	for(int i=1;i<=70;i++){
		if(cnt[i]){
			for(int j=0;j<(1<<19);j++){
				// 选奇数个数 
				dp[i][j^s[i]]=((LL)dp[i][j^s[i]]+((LL)p2[cnt[i]-1]*(LL)dp[i-1][j]))%mod;
				// 第 i 个数有2^(n-1)种情况，乘法原理乘上前 i-1 个数的方案 
				dp[i][j]=((LL)dp[i][j]+(LL)p2[cnt[i]-1]*dp[i-1][j])%mod;
			}
		}else{
			for(int j=0;j<(1<<19);j++)dp[i][j]=dp[i-1][j];
		}
	}
	printf("%d\n",(dp[70][0]-1+mod)%mod);
	
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

感觉状压比较显然。$1$ 到 $70$ 只有很少个质数，于是我们考虑状压。

首先可以状压 DP。$f(i,s)$ 表示前 $i$ 个数，质因数的次数模2的状态为 $s$。$O(n2^p)$，应该会炸。

设 $x$ 的状态为 $s_x$，显然地，我们有 $s(x\times y)=s_x\operatorname{xor}s_y$，$s_{x^2}=0$。于是我们相当于要找到有多少个集合使得集合内的 $s_x$ 的异或和为 $0$。

这玩意儿直接上线性基就行了。在线性基外的所有元素组成的集合的异或和都能被线性基内的元素的异或和所表示，并且能证明这样算出来的答案即原题所求的答案。所以答案为 $2^{n-sz}-1$（减一为去除空集）。

质数表别打错。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=1e5+9,mod=1e9+7;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,a,lb[N],sz,p[20]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};

void insert(int x) {
	per(i,18,0) if((1<<i)&x) {
		if(!lb[i]) {lb[i]=x; sz++; return;}
		x^=lb[i];
	}
}

int main() {
	n=read();
	rep(i,1,n) {
		a=read();
		int s=0;
		rep(i,0,18) {
			int c=0;
			while(a%p[i]==0) a/=p[i],c^=1;
			s+=c*(1<<i);
		}
		insert(s);
	}
	int ans=1;
	rep(i,sz+1,n) ans=1ll*ans*2%mod;
	printf("%d\n",ans-1);
	return 0;
}
```

---

## 作者：Arghariza (赞：0)

经典套路了属于是（

首先看到 $a_i\le 70$，并且平方数仅考虑质因数个数的奇偶性，所以考虑压缩质因数状态。打表发现 $70$ 以内只有 $19$ 个质数，于是可做。

令 $dp_{i,st}(i\in\{1,2,...,70\},st\in\{0,1,...,2^{19}-1\})$ 表示当前考虑到 $i$，且选完质因数个数奇偶状态变为 $st$ 的方案数。

于是如果选奇数个 $i$，则 $dp_{i,st}\gets dp_{lt,st\ xor\ st(i)}\times(C_{c(i)}^{1}+C_{c(i)}^{3}+C_{c(i)}^{5}+...)$；如果选偶数个 $i$，那么 $dp_{i,st}\gets dp_{lt,st}\times(C_{c(i)}^{2}+C_{c(i)}^{4}+C_{c(i)}^{6}+...)$

$st(i)$ 表示 $i$ 的质因数个数奇偶状态，$lt$ 表示上一个在原数列中存在的 $i$，$c(i)$ 表示原数列中 $i$ 的个数，这些都是转移前可以求出来的。

注意到 $C_{c(i)}^{1}+C_{c(i)}^{3}+C_{c(i)}^{5}+...=C_{c(i)}^{2}+C_{c(i)}^{4}+C_{c(i)}^{6}+...=2^{c(i)-1}$，于是：

$dp_{i,st}\gets (dp_{lt,st\ xor\ st(i)}+dp_{lt,st})\times 2^{c(i)-1}$

然后答案就是 $dp_{lt, 0}-1$，去掉全都不取的情况。

滚一滚，空间 $O(2^w+n)$，时间 $O(w2^w)$，$w=19$。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e5 + 100;
const int mxst = 6e5 + 600;
const int mod = 1e9 + 7;
int n, tot, s[maxn], dp[2][mxst], c[75], st[75], pw2[maxn];
int v[75], pr[75];

signed main() {
	n = read();
	for (int i = 2; i <= 70; i++) {
		if (!v[i]) pr[++tot] = i;
		for (int j = 1; j <= tot && i * pr[j] <= 70; j++) {
			v[i * pr[j]] = 1;
			if (i % pr[j] == 0) break;
		}
	}
	pw2[0] = 1;
	for (int i = 1; i <= n; i++) c[s[i] = read()]++, pw2[i] = pw2[i - 1] * 2 % mod;
	for (int i = 1; i <= 70; i++) {
		int tp = i;
		for (int j = 1; j <= tot; j++) {
			int res = 0;
			while (tp % pr[j] == 0) {
				tp /= pr[j];
				res ^= 1;
			}
			st[i] = st[i] | (res << (j - 1));
		}
	}
	dp[0][0] = 1;
	int k = 0;
	for (int i = 1; i <= 70; i++) {
		if (!c[i]) continue;
		k ^= 1;
		for (int j = 0; j <= (1 << 19) - 1; j++) {
			dp[k][j] = (dp[k ^ 1][j] + dp[k ^ 1][j ^ st[i]]) % mod * pw2[c[i] - 1] % mod;
		}
	}
	write(((dp[k][0] - 1) % mod + mod) % mod);
	return 0;
}
```

---

